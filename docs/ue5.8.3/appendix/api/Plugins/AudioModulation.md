# Plugins / AudioModulation

- module root: `Plugins/Runtime/AudioModulation/Source/AudioModulation`
- headers: 34; symbols: 940
- symbol kinds: class=53, delegate=3, enum=4, enumerator=19, externvar=9, function=155, macro=12, member=224, namespace=23, prototype=390, struct=27, typedef=20, variable=1
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, CoreUObject, DeveloperSettings, Engine, MetasoundEngine, MetasoundFrontend, MetasoundGraphCore, Projects, SignalProcessing, Slate, SlateCore, TraceLog
- PublicDependencyModuleNames: AudioExtensions, AudioMixer, Core, LevelSequence, MovieScene, MovieSceneTracks, WaveTable

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationDebugger.h` (Private)


#### struct `AudioModulation::FGeneratorSort`  
`struct FGeneratorSort`  
_L21-27_
- L23 _public function_ `FORCEINLINE bool operator()(const FString& A, const FString& B) const`

#### struct `AudioModulation::FGeneratorDebugInfo`  
`struct FGeneratorDebugInfo`  
_L29-47_
- L31 _public function_ `FGeneratorDebugInfo()`
- L35 _public function_ `FGeneratorDebugInfo(const TArray<FString>& InCategories) : Categories(InCategories)`
- L40 _public member_ `bool bEnabled = false;`
- L41 _public member_ `TArray<FString> Categories;`
- L43 _public member_ `FString NameFilter;`
- L45 _public typedef_ `using FInstanceValues = TArray<FString>;`
- L46 _public member_ `TArray<FInstanceValues> FilteredInstances;`

#### class `AudioModulation::FAudioModulationDebugger`  
`class FAudioModulationDebugger : public IDebugDataProvider, public TSharedFromThis<FAudioModulationDebugger, ESPMode::ThreadSafe>`  
_L49-101_
- inherits: `IDebugDataProvider,TSharedFromThis<FAudioModulationDebugger,ESPMode::ThreadSafe>`
- L52 _public prototype_ `FAudioModulationDebugger();`
- L53 _public prototype_ `virtual ~FAudioModulationDebugger();`
- L55 _public prototype_ `void UpdateDebugData(double InElapsed, const FReferencedProxies& InRefProxies, Audio::FDeviceId DeviceId);`
- L56 _public prototype_ `void SetDebugBusFilter(const FString* InNameFilter);`
- L57 _public prototype_ `void SetDebugMatrixEnabled(bool bInIsEnabled);`
- L58 _public prototype_ `void SetDebugMixFilter(const FString* InNameFilter);`
- L59 _public prototype_ `void SetDebugGeneratorsEnabled(bool bInIsEnabled);`
- L60 _public prototype_ `void SetDebugGeneratorFilter(const FString* InFilter);`
- L61 _public prototype_ `void SetDebugGeneratorTypeFilter(const FString* InFilter, bool bInIsEnabled);`
- L62 _public prototype_ `void SetDebugActiveMixesEnabled(bool bInIsEnabled);`
- L63 _public prototype_ `void SetDebugActiveGlobalMixesEnabled(bool bInIsEnabled);`
- L64 _public prototype_ `bool OnPostHelp(FCommonViewportClient& ViewportClient, const TCHAR* Stream);`
- L65 _public prototype_ `int32 OnRenderStat(FCanvas& Canvas, int32 X, int32 Y, const UFont& Font);`
- L66 _public prototype_ `bool OnToggleStat(FCommonViewportClient& ViewportClient, const TCHAR* Stream);`
- L68 _public prototype_ `void ResetGeneratorStats();`
- L71 _public prototype_ `virtual Audio::FDeviceId GetAssociatedDeviceID() override;` — IdebugDataProviderInterface
- L72 _public prototype_ `virtual void GetControlBusDebugInfo(TArray<FControlBusDebugInfo>& OutDebugInfo) override;`
- L73 _public prototype_ `virtual void GetControlBusMixDebugInfo(TArray<FControlBusMixDebugInfo>& OutDebugInfo) override;`
- L77 _private member_ `uint8 bActive : 1;`
- L78 _private member_ `uint8 bShowRenderStatMix : 1;`
- L79 _private member_ `uint8 bShowGenerators : 1;`
- L80 _private member_ `uint8 bEnableAllGenerators : 1;`
- L81 _private member_ `uint8 bShowActiveMixes : 1;`
- L82 _private member_ `uint8 bShowGlobalMixes : 1;`
- L84 _private member_ `Audio::FDeviceId AssociatedDeviceId;`
- L86 _private member_ `TArray<FControlBusDebugInfo> UnfilteredBuses;`
- L87 _private member_ `TArray<FControlBusDebugInfo> FilteredBuses;`
- L88 _private member_ `TArray<FControlBusMixDebugInfo> UnfilteredMixes;`
- L89 _private member_ `TArray<FControlBusMixDebugInfo> FilteredMixes;`
- L91 _private typedef_ `using FGeneratorSortMap = TSortedMap<FString, FGeneratorDebugInfo, FDefaultAllocator, FGeneratorSort>;`
- L92 _private member_ `FGeneratorSortMap FilteredGeneratorsMap;`
- L94 _private member_ `TMap<FString, bool> RequestedGeneratorUpdate;`
- L96 _private member_ `FString BusStringFilter;`
- L97 _private member_ `FString GeneratorStringFilter;`
- L98 _private member_ `FString MixStringFilter;`
- L100 _private member_ `float ElapsedSinceLastUpdate;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AudioModulation`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationLogging.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioModulation, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioModulation, Log, All);`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationProfileSerializer.h` (Private)


#### class `AudioModulation::FProfileSerializer`  
`class FProfileSerializer`  
_L19-238_
- L21 _private function_ `static bool StageValueToFloat(const FConfigSection& InSection, const FName& InMember, float& OutValue)`
- L32 _private function_ `static FString GetConfigDir()`
- L37 _private function_ `static bool GetConfigDirectory(const FString& InDir, bool bCreateDirIfMissing)`
- L67 _private function_ `static bool GetMixProfileConfigPath(const FString& Name, const FString& Path, const int32 InProfileIndex, bool bInCreateDirIfMissing, FString& OutMixProfileConfig)`
- L97 _public function_ `static bool Serialize(const USoundControlBusMix& InBusMix, const int32 InProfileIndex, const FString* InMixPathOverride = nullptr)`
- L137 _public function_ `static bool Deserialize(int32 InProfileIndex, USoundControlBusMix& InOutBusMix, const FString* InMixPathOverride = nullptr)`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace AudioModulation`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationSystem.h` (Private)


#### struct `AudioModulation::FReferencedProxies`  
`struct FReferencedProxies`  
_L45-51_
- L47 _public member_ `FBusMixProxyMap BusMixes;`
- L48 _public member_ `FBusProxyMap Buses;`
- L49 _public member_ `FGeneratorProxyMap Generators;`
- L50 _public member_ `FPatchProxyMap Patches;`

#### struct `AudioModulation::FReferencedModulators`  
`struct FReferencedModulators`  
_L55-60_
- L57 _public member_ `TMap<FPatchHandle, FModulatorHandleSet> PatchMap;`
- L58 _public member_ `TMap<FBusHandle, FModulatorHandleSet> BusMap;`
- L59 _public member_ `TMap<FGeneratorHandle, FModulatorHandleSet> GeneratorMap;`

#### class `AudioModulation::FAudioModulationSystem`  
`class FAudioModulationSystem : public FGCObject`  
_L66-358_
- inherits: `FGCObject`
- L69 _public prototype_ `~FAudioModulationSystem();`
- L71 _public prototype_ `void Initialize(const FAudioPluginInitializationParams& InitializationParams);`
- L74 _public prototype_ `void ActivateBus(const USoundControlBus& InBus);` — `UE_DEPRECATED(5.4, "Activation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L76 _public prototype_ `void ActivateBusMix(FModulatorBusMixSettings&& InSettings);`
- L77 _public prototype_ `void ActivateBusMix(const USoundControlBusMix& InBusMix);`
- L80 _public prototype_ `void ActivateGenerator(const USoundModulationGenerator& InGenerator);` — `UE_DEPRECATED(5.4, "Activation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L83 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L84 _public prototype_ `virtual FString GetReferencerName() const override;`
- L88 _public prototype_ `void DeactivateBus(const USoundControlBus& InBus);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L91 _public prototype_ `void DeactivateBusMix(const USoundControlBusMix& InBusMix);` — Deactivates given bus mix
- L92 _public prototype_ `void DeactivateBusMixByID(const uint32 ID);`
- L95 _public prototype_ `void DeactivateAllBusMixes();` — Deactivates all bus mixes
- L98 _public prototype_ `void DeactivateGenerator(const USoundModulationGenerator& InGenerator);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L100 _public prototype_ `void ProcessModulators(const double InElapsed);`
- L101 _public prototype_ `void SoloBusMix(const USoundControlBusMix& InBusMix);`
- L103 _public prototype_ `Audio::FDeviceId GetAudioDeviceId() const;`
- L108 _public prototype_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FControlBusSettings& InSettings);` — Register new handle with given a given modulator that may or may not already be active (i.e. registered). If already registered, depending on modulator type, may or may not refresh proxy based on provided settings.
- L109 _public prototype_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationGeneratorSettings& InSettings);`
- L110 _public prototype_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationPatchSettings& InSettings);`
- L113 _public prototype_ `void RegisterModulator(Audio::FModulatorHandleId InHandleId, Audio::FModulatorId InModulatorId);` — Register new handle with given Id with a modulator that is already active (i.e. registered). Used primarily for copying modulation handles.
- L116 _public prototype_ `bool GetModulatorValue(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const;` — Attempts to get the modulator value from the AudioRender Thread.
- L119 _public prototype_ `bool GetModulatorValueThreadSafe(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const;` — Attempts to get the modulator value from any thread (lock contentious).
- L122 _public prototype_ `bool GetModulatorValueThreadSafe(uint32 ModulatorID, float& OutValue) const;` — Attempts to get the modulator value from any thread (lock contentious).
- L124 _public prototype_ `void UnregisterModulator(const Audio::FModulatorHandle& InHandle);`
- L126 _public prototype_ `bool IsControlBusMixActive(const USoundControlBusMix& InBusMix);`
- L129 _public prototype_ `void SaveMixToProfile(const USoundControlBusMix& InBusMix, const int32 InProfileIndex);` — Saves mix to .ini profile for fast iterative development that does not require re-cooking a mix
- L133 _public prototype_ `TArray<FSoundControlBusMixStage> LoadMixFromProfile(const int32 InProfileIndex, USoundControlBusMix& OutBusMix);` — Loads mix from .ini profile for iterative development that does not require re-cooking a mix. Returns copy of mix stage values saved in profile.
- L139 _public prototype_ `void UpdateMix(const TArray<FSoundControlBusMixStage>& InStages, USoundControlBusMix& InOutMix, bool bInUpdateObject = false, float InFadeTime = -1.0f, double Duration = -1.0, bool bRetriggerOnActivation = false);` — Updates mix/mix by filter, modifying the mix instance if it is active. If bInUpdateObject is true, updates UObject definition in addition to proxy.
- L140 _public prototype_ `void UpdateMixByFilter(const FString& InAddressFilter, const TSubclassOf<USoundModulationParameter>& InParamClassFilter, USoundModulationParameter* InParamFilter, float Value, float FadeTime, USoundControlBusMix& InOutMix, bool bInUpdateObject = false);`
- L145 _public prototype_ `void UpdateMix(const USoundControlBusMix& InMix, float InFadeTime = -1.0f);` — Commits any changes from a mix applied to a UObject definition to mix instance if active.
- L148 _public prototype_ `void SetGlobalBusMixValue(USoundControlBus& Bus, float Value, float FadeTime = -1.0f);` — Sets the global bus mix value if over the prescribed time. If FadeTime is non-positive, applies the value immediately.
- L151 _public prototype_ `void ClearGlobalBusMixValue(const USoundControlBus& InBus, float FadeTime = -1.0f);` — Clears the global bus mix value over the prescribed FadeTime. If FadeTime is non-positive, returns to the bus's respective parameter default immediately.
- L154 _public prototype_ `void ClearAllGlobalBusMixValues(float FadeTime = -1.0f);` — Clears all global bus mix values over the prescribed FadeTime. If FadeTime is non-positive, returns to the bus's respective parameter default immediately.
- L157 _public prototype_ `bool IsBusMixGlobal(FBusMixId InBusMixId) const;` — Returns whether the given bus Mix is a Global Bus Mix, created using the SetGlobalBusMixValue function.
- L163 _public prototype_ `USoundControlBusMix* CreateBusMixFromValue(FName Name, const TArray<USoundControlBus*>& Buses, float Value, float AttackTime = -1.0f, float ReleaseTime = -1.0f, UObject* InOuter = nullptr);` — Create a mix from an array of buses where a supplied default value and associated timing parameters are applied for each bus's stage. InOuter, when supplied, is used as the new mix's outer object so its lifetime tracks the caller's scope (typically the supplied world); the transient package is used otherwise.
- L169 _public prototype_ `void UpdateModulator(const USoundModulatorBase& InModulator);` — Commits any changes from a modulator type applied to a UObject definition to modulator instance if active (i.e. Control Bus, Control Bus Modulator)
- L171 _public prototype_ `void OnAuditionEnd();`
- L175 _private prototype_ `bool CalculateModulationValue(FModulationPatchProxy& OutProxy, float& OutValue) const;` — Calculates modulation value, storing it in the provided float reference and returns if value changed
- L178 _private prototype_ `bool IsInProcessingThread() const;` — Whether or not caller is in processing thread or not
- L181 _private prototype_ `void RunCommandOnProcessingThread(TUniqueFunction<void()> Cmd);` — Runs the provided command on the audio render thread (at the beginning of the ProcessModulators call)
- L196 _private function_ `template <typename THandleType, typename TModSettings, typename TMapType, typename TInitFunction = TUniqueFunction<void(THandleType)>> void RegisterModulator(Audio::FModulatorHandleId InHandleId, TModSettings&& InModSettings, TMapType& OutProxyMap, TMap<THandleType, FModulatorHandleSet>& OutModMap, TInitFunction InInitFunction = [](THandleType){ })` — Template for register calls that move the modulator settings objects onto the Audio Processing Thread & create proxies. If the proxy is already found, adds provided HandleId as reference to given proxy. Does *not* update the proxy with the given settings.  If update is desired on an existing proxy, UpdateModulator must be explicitly called. @tparam THandleType Type of modulator handle used to access the proxy on the Processing Thread @tparam TModSettings Modulation settings to move and use if proxy construction is required on the Audio Processing Thread @tparam TMapType MapType used to cache the corresponding proxy id & proxy @tparam TInitFunction (Optional) Function type used to call on the AudioProcessingThread immediately following proxy construction @param InHandleId HandleId associated with the proxy to be retrieved/generated. @param InModSettings ModulatorSettings to be used if construction of proxy is required on Audio Processing Thread @param OutProxyMap Map to find or add proxy to if constructed @param InInitFunction Function type used to call on the AudioProcessingThread immediately following proxy generation
- L196 _private function_ `template <typename THandleType, typename TModSettings, typename TMapType, typename TInitFunction = TUniqueFunction<void(THandleType)>> void RegisterModulator(Audio::FModulatorHandleId InHandleId, TModSettings&& InModSettings, TMapType& OutProxyMap, TMap<THandleType, FModulatorHandleSet>& OutModMap, TInitFunction InInitFunction = [](THandleType){ })` — Template for register calls that move the modulator settings objects onto the Audio Processing Thread & create proxies. If the proxy is already found, adds provided HandleId as reference to given proxy. Does *not* update the proxy with the given settings.  If update is desired on an existing proxy, UpdateModulator must be explicitly called. @tparam THandleType Type of modulator handle used to access the proxy on the Processing Thread @tparam TModSettings Modulation settings to move and use if proxy construction is required on the Audio Processing Thread @tparam TMapType MapType used to cache the corresponding proxy id & proxy @tparam TInitFunction (Optional) Function type used to call on the AudioProcessingThread immediately following proxy construction @param InHandleId HandleId associated with the proxy to be retrieved/generated. @param InModSettings ModulatorSettings to be used if construction of proxy is required on Audio Processing Thread @param OutProxyMap Map to find or add proxy to if constructed @param InInitFunction Function type used to call on the AudioProcessingThread immediately following proxy generation
- L220 _private function_ `template <typename THandleType> bool UnregisterModulator(THandleType InModHandle, TMap<THandleType, FModulatorHandleSet>& OutHandleMap, const Audio::FModulatorHandleId InHandleId)`
- L241 _private member_ `FReferencedProxies RefProxies;`
- L245 _private member_ `mutable FCriticalSection ThreadSafeModValueCritSection;` — Critical section & map of copied, computed modulation values for use from the decoder threads & respective MetaSound getter nodes.
- L246 _private member_ `TMap<Audio::FModulatorId, float> ThreadSafeModValueMap;`
- L248 _private member_ `TSet<FBusMixId> ActiveBusMixIds;`
- L250 _private member_ `TSet<FBusHandle> ManuallyActivatedBuses;`
- L251 _private member_ `TSet<FBusMixHandle> ManuallyActivatedBusMixes;`
- L252 _private member_ `TSet<FGeneratorHandle> ManuallyActivatedGenerators;`
- L256 _private member_ `TMap<uint32, TObjectPtr<USoundControlBusMix>> ActiveGlobalBusValueMixes;` — Global mixes each containing a single stage for any globally manipulated bus stage value. the key in this map is the Bus's unique ID, not the Control Bus Mix's.
- L259 _private member_ `TQueue<TUniqueFunction<void()>, EQueueMode::Mpsc> ProcessingThreadCommandQueue;` — Command queue to be consumed on processing thread
- L262 _private member_ `TAtomic<uint32> ProcessingThreadId { 0 };` — Thread modulators are processed on
- L265 _private member_ `FReferencedModulators RefModulators;` — Collection of maps with modulator handles to referencing object ids used by externally managing objects
- L267 _private member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L297 _private prototype_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L299 _private prototype_ `void UpdateAudioInsightsTraceMessages(const double InElapsed);`
- L301 _private prototype_ `void TraceActivateModulatorMessage(const Audio::FModulatorId InModulatorId, const EModulatorTraceType InModulatorTraceType, const FString& InModulatorName);`
- L306 _private prototype_ `template <typename TModulatorProxy> void TraceUpdateModulatorMessage(const Audio::FModulatorId InModulatorId, const TModulatorProxy& InModulatorProxy, const EModulatorTraceType InModulatorTraceType, TArrayView<const Audio::FModulatorId> InContributingModulatorIds = TArrayView<const Audio::FModulatorId>(), TArrayView<const float> InContributingModulatorValues = TArrayView<const float>());`
- L312 _private prototype_ `void TraceDeactivateModulatorMessage(const Audio::FModulatorId InModulatorId);`
- L314 _private member_ `bool bIsAudioModulationInsightsPluginEnabled { false };`
- L316 _private member_ `float ModulatorActivePingTimeSec { 0.0f };`
- L317 _private member_ `static constexpr float ModulatorActivePingIntervalTimeSec { 1.0f };`
- L326 _private member_ `TArray<Audio::FModulatorId, TInlineAllocator<32>> CurrentlyActiveModulatorIds;`
- L327 _private member_ `TArray<Audio::FModulatorId, TInlineAllocator<32>> PreviouslyActiveModulatorIds;`
- L328 _private member_ `TMap<Audio::FModulatorId, FString> ActiveModulatorPaths;`
- L330 _private member_ `TArray<float, TInlineAllocator<32>> ContributingModulatorValues;`
- L331 _private member_ `TArray<Audio::FModulatorId, TInlineAllocator<32>> ContributingModulatorIds;`
- L332 _private member_ `TArray<AudioInsightsControlBusMixData, TInlineAllocator<32>> ControlBusMixContributingDataContainer;`
- L337 _public prototype_ `void SetDebugBusFilter(const FString* InFilter);`
- L338 _public prototype_ `void SetDebugMixFilter(const FString* InFilter);`
- L339 _public prototype_ `void SetDebugMatrixEnabled(bool bInIsEnabled);`
- L340 _public prototype_ `void SetDebugGeneratorsEnabled(bool bInIsEnabled);`
- L341 _public prototype_ `void SetDebugGeneratorFilter(const FString* InFilter);`
- L342 _public prototype_ `void SetDebugGeneratorTypeFilter(const FString* InFilter, bool bInIsEnabled);`
- L343 _public prototype_ `virtual void SetDebugActiveMixesEnabled(bool bInIsEnabled);`
- L344 _public prototype_ `virtual void SetDebugActiveGlobalMixesEnabled(bool bInIsEnabled);`
- L345 _public prototype_ `bool OnPostHelp(FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L346 _public prototype_ `int OnRenderStat(FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const UFont& Font, const FVector* ViewLocation, const FRotator* ViewRotation);`
- L347 _public prototype_ `bool OnToggleStat(FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L350 _private member_ `TSharedPtr<FAudioModulationDebugger> Debugger;`
- L371 _public function_ `void Initialize(const FAudioPluginInitializationParams& InitializationParams)`
- L373 _public function_ `void OnAuditionEnd()`
- L376 _public function_ `void SetDebugBusFilter(const FString* InFilter)`
- L377 _public function_ `void SetDebugMixFilter(const FString* InFilter)`
- L378 _public function_ `void SetDebugMatrixEnabled(bool bInIsEnabled)`
- L379 _public function_ `void SetDebugGeneratorsEnabled(bool bInIsEnabled)`
- L380 _public function_ `void SetDebugGeneratorFilter(const FString* InFilter)`
- L381 _public function_ `void SetDebugGeneratorTypeFilter(const FString* InFilter, bool bInIsEnabled)`
- L382 _public function_ `bool OnPostHelp(FCommonViewportClient* ViewportClient, const TCHAR* Stream)`
- L383 _public function_ `int OnRenderStat(FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const UFont& Font, const FVector* ViewLocation, const FRotator* ViewRotation)`
- L384 _public function_ `bool OnToggleStat(FCommonViewportClient* ViewportClient, const TCHAR* Stream)`
- L387 _public function_ `void ActivateBus(const USoundControlBus& InBus)`
- L388 _public function_ `void ActivateBusMix(FModulatorBusMixSettings&& InSettings)`
- L389 _public function_ `void ActivateBusMix(const USoundControlBusMix& InBusMix)`
- L390 _public function_ `void ActivateGenerator(const USoundModulationGenerator& InGenerator)`
- L392 _public function_ `void DeactivateAllBusMixes()`
- L393 _public function_ `void DeactivateBus(const USoundControlBus& InBus)`
- L394 _public function_ `void DeactivateBusMix(const USoundControlBusMix& InBusMix)`
- L395 _public function_ `void DeactivateBusMixByID(const uint32 ID)`
- L396 _public function_ `void DeactivateGenerator(const USoundModulationGenerator& InGenerator)`
- L398 _public function_ `Audio::FDeviceId GetAudioDeviceId() const`
- L400 _public function_ `bool IsControlBusMixActive(const USoundControlBusMix& InBusMix)`
- L402 _public function_ `void SaveMixToProfile(const USoundControlBusMix& InBusMix, const int32 InProfileIndex)`
- L403 _public function_ `TArray<FSoundControlBusMixStage> LoadMixFromProfile(const int32 InProfileIndex, USoundControlBusMix& OutBusMix)`
- L405 _public function_ `void SetGlobalBusMixValue(USoundControlBus& Bus, float Value, float FadeTime)`
- L406 _public function_ `void ClearGlobalBusMixValue(const USoundControlBus& InBus, float FadeTime)`
- L407 _public function_ `void ClearAllGlobalBusMixValues(float FadeTime)`
- L409 _public function_ `USoundControlBusMix* CreateBusMixFromValue(FName Name, const TArray<USoundControlBus*>& Buses, float Value, float AttackTime = -1.0f, float ReleaseTime = -1.0f, UObject* InOuter = nullptr)`
- L411 _public function_ `void ProcessModulators(const double InElapsed)`
- L412 _public function_ `void SoloBusMix(const USoundControlBusMix& InBusMix)`
- L414 _public function_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FControlBusSettings& InSettings)`
- L415 _public function_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationGeneratorSettings& InSettings)`
- L416 _public function_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationPatchSettings& InSettings)`
- L418 _public function_ `void RegisterModulator(Audio::FModulatorHandleId InHandleId, Audio::FModulatorId InModulatorId)`
- L419 _public function_ `bool GetModulatorValue(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const`
- L420 _public function_ `bool GetModulatorValueThreadSafe(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const`
- L421 _public function_ `bool GetModulatorValueThreadSafe(uint32 ModulatorID, float& OutValue) const`
- L422 _public function_ `void UnregisterModulator(const Audio::FModulatorHandle& InHandle)`
- L429 _public function_ `void UpdateMix(const USoundControlBusMix& InMix, float InFadeTime = -1.0f)`
- L430 _public function_ `void UpdateMix(const TArray<FSoundControlBusMixStage>& InStages, USoundControlBusMix& InOutMix, bool bUpdateObject = false, float InFadeTime = -1.0f)`
- L431 _public function_ `void UpdateMixByFilter(const FString& InAddressFilter, const TSubclassOf<USoundModulationParameter>& InParamClassFilter, USoundModulationParameter* InParamFilter, float InValue, float InFadeTime, USoundControlBusMix& InOutMix, bool bUpdateObject = false)`
- L432 _public function_ `void UpdateModulator(const USoundModulatorBase& InModulator)`

#### enum `AudioModulation::FAudioModulationSystem::EModulatorTraceType`  
`enum class EModulatorTraceType : Audio::FModulatorTypeId`  
_L287-295_
- desc: Mirrors EModulatorTraceType: Engine/Plugins/Runtime/AudioModulationInsights/Source/AudioModulationInsights/Private/AudioModulationDataTypes.h
- L289 _public enumerator_ `ControlBus`
- L290 _public enumerator_ `ControlBusMix`
- L291 _public enumerator_ `Generator`
- L292 _public enumerator_ `ParameterPatch`
- L294 _public enumerator_ `COUNT`

#### struct `AudioModulation::FAudioModulationSystem::AudioInsightsControlBusMixData`  
`struct AudioInsightsControlBusMixData`  
_L319-324_
- L321 _public member_ `Audio::FModulatorId ControlBusMixId;`
- L322 _public member_ `Audio::FModulatorId ControlBusId;`
- L323 _public member_ `float Value;`

#### class `AudioModulation::FAudioModulationSystem`  
`class FAudioModulationSystem`  
_L366-442_
- desc: Null implementation for compiler
- L69 _public prototype_ `~FAudioModulationSystem();`
- L71 _public prototype_ `void Initialize(const FAudioPluginInitializationParams& InitializationParams);`
- L74 _public prototype_ `void ActivateBus(const USoundControlBus& InBus);` — `UE_DEPRECATED(5.4, "Activation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L76 _public prototype_ `void ActivateBusMix(FModulatorBusMixSettings&& InSettings);`
- L77 _public prototype_ `void ActivateBusMix(const USoundControlBusMix& InBusMix);`
- L80 _public prototype_ `void ActivateGenerator(const USoundModulationGenerator& InGenerator);` — `UE_DEPRECATED(5.4, "Activation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L83 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L84 _public prototype_ `virtual FString GetReferencerName() const override;`
- L88 _public prototype_ `void DeactivateBus(const USoundControlBus& InBus);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L91 _public prototype_ `void DeactivateBusMix(const USoundControlBusMix& InBusMix);` — Deactivates given bus mix
- L92 _public prototype_ `void DeactivateBusMixByID(const uint32 ID);`
- L95 _public prototype_ `void DeactivateAllBusMixes();` — Deactivates all bus mixes
- L98 _public prototype_ `void DeactivateGenerator(const USoundModulationGenerator& InGenerator);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestinations to safely activate and track a given modulator")`
- L100 _public prototype_ `void ProcessModulators(const double InElapsed);`
- L101 _public prototype_ `void SoloBusMix(const USoundControlBusMix& InBusMix);`
- L103 _public prototype_ `Audio::FDeviceId GetAudioDeviceId() const;`
- L108 _public prototype_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FControlBusSettings& InSettings);` — Register new handle with given a given modulator that may or may not already be active (i.e. registered). If already registered, depending on modulator type, may or may not refresh proxy based on provided settings.
- L109 _public prototype_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationGeneratorSettings& InSettings);`
- L110 _public prototype_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationPatchSettings& InSettings);`
- L113 _public prototype_ `void RegisterModulator(Audio::FModulatorHandleId InHandleId, Audio::FModulatorId InModulatorId);` — Register new handle with given Id with a modulator that is already active (i.e. registered). Used primarily for copying modulation handles.
- L116 _public prototype_ `bool GetModulatorValue(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const;` — Attempts to get the modulator value from the AudioRender Thread.
- L119 _public prototype_ `bool GetModulatorValueThreadSafe(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const;` — Attempts to get the modulator value from any thread (lock contentious).
- L122 _public prototype_ `bool GetModulatorValueThreadSafe(uint32 ModulatorID, float& OutValue) const;` — Attempts to get the modulator value from any thread (lock contentious).
- L124 _public prototype_ `void UnregisterModulator(const Audio::FModulatorHandle& InHandle);`
- L126 _public prototype_ `bool IsControlBusMixActive(const USoundControlBusMix& InBusMix);`
- L129 _public prototype_ `void SaveMixToProfile(const USoundControlBusMix& InBusMix, const int32 InProfileIndex);` — Saves mix to .ini profile for fast iterative development that does not require re-cooking a mix
- L133 _public prototype_ `TArray<FSoundControlBusMixStage> LoadMixFromProfile(const int32 InProfileIndex, USoundControlBusMix& OutBusMix);` — Loads mix from .ini profile for iterative development that does not require re-cooking a mix. Returns copy of mix stage values saved in profile.
- L139 _public prototype_ `void UpdateMix(const TArray<FSoundControlBusMixStage>& InStages, USoundControlBusMix& InOutMix, bool bInUpdateObject = false, float InFadeTime = -1.0f, double Duration = -1.0, bool bRetriggerOnActivation = false);` — Updates mix/mix by filter, modifying the mix instance if it is active. If bInUpdateObject is true, updates UObject definition in addition to proxy.
- L140 _public prototype_ `void UpdateMixByFilter(const FString& InAddressFilter, const TSubclassOf<USoundModulationParameter>& InParamClassFilter, USoundModulationParameter* InParamFilter, float Value, float FadeTime, USoundControlBusMix& InOutMix, bool bInUpdateObject = false);`
- L145 _public prototype_ `void UpdateMix(const USoundControlBusMix& InMix, float InFadeTime = -1.0f);` — Commits any changes from a mix applied to a UObject definition to mix instance if active.
- L148 _public prototype_ `void SetGlobalBusMixValue(USoundControlBus& Bus, float Value, float FadeTime = -1.0f);` — Sets the global bus mix value if over the prescribed time. If FadeTime is non-positive, applies the value immediately.
- L151 _public prototype_ `void ClearGlobalBusMixValue(const USoundControlBus& InBus, float FadeTime = -1.0f);` — Clears the global bus mix value over the prescribed FadeTime. If FadeTime is non-positive, returns to the bus's respective parameter default immediately.
- L154 _public prototype_ `void ClearAllGlobalBusMixValues(float FadeTime = -1.0f);` — Clears all global bus mix values over the prescribed FadeTime. If FadeTime is non-positive, returns to the bus's respective parameter default immediately.
- L157 _public prototype_ `bool IsBusMixGlobal(FBusMixId InBusMixId) const;` — Returns whether the given bus Mix is a Global Bus Mix, created using the SetGlobalBusMixValue function.
- L163 _public prototype_ `USoundControlBusMix* CreateBusMixFromValue(FName Name, const TArray<USoundControlBus*>& Buses, float Value, float AttackTime = -1.0f, float ReleaseTime = -1.0f, UObject* InOuter = nullptr);` — Create a mix from an array of buses where a supplied default value and associated timing parameters are applied for each bus's stage. InOuter, when supplied, is used as the new mix's outer object so its lifetime tracks the caller's scope (typically the supplied world); the transient package is used otherwise.
- L169 _public prototype_ `void UpdateModulator(const USoundModulatorBase& InModulator);` — Commits any changes from a modulator type applied to a UObject definition to modulator instance if active (i.e. Control Bus, Control Bus Modulator)
- L171 _public prototype_ `void OnAuditionEnd();`
- L175 _private prototype_ `bool CalculateModulationValue(FModulationPatchProxy& OutProxy, float& OutValue) const;` — Calculates modulation value, storing it in the provided float reference and returns if value changed
- L178 _private prototype_ `bool IsInProcessingThread() const;` — Whether or not caller is in processing thread or not
- L181 _private prototype_ `void RunCommandOnProcessingThread(TUniqueFunction<void()> Cmd);` — Runs the provided command on the audio render thread (at the beginning of the ProcessModulators call)
- L196 _private function_ `template <typename THandleType, typename TModSettings, typename TMapType, typename TInitFunction = TUniqueFunction<void(THandleType)>> void RegisterModulator(Audio::FModulatorHandleId InHandleId, TModSettings&& InModSettings, TMapType& OutProxyMap, TMap<THandleType, FModulatorHandleSet>& OutModMap, TInitFunction InInitFunction = [](THandleType){ })` — Template for register calls that move the modulator settings objects onto the Audio Processing Thread & create proxies. If the proxy is already found, adds provided HandleId as reference to given proxy. Does *not* update the proxy with the given settings.  If update is desired on an existing proxy, UpdateModulator must be explicitly called. @tparam THandleType Type of modulator handle used to access the proxy on the Processing Thread @tparam TModSettings Modulation settings to move and use if proxy construction is required on the Audio Processing Thread @tparam TMapType MapType used to cache the corresponding proxy id & proxy @tparam TInitFunction (Optional) Function type used to call on the AudioProcessingThread immediately following proxy construction @param InHandleId HandleId associated with the proxy to be retrieved/generated. @param InModSettings ModulatorSettings to be used if construction of proxy is required on Audio Processing Thread @param OutProxyMap Map to find or add proxy to if constructed @param InInitFunction Function type used to call on the AudioProcessingThread immediately following proxy generation
- L196 _private function_ `template <typename THandleType, typename TModSettings, typename TMapType, typename TInitFunction = TUniqueFunction<void(THandleType)>> void RegisterModulator(Audio::FModulatorHandleId InHandleId, TModSettings&& InModSettings, TMapType& OutProxyMap, TMap<THandleType, FModulatorHandleSet>& OutModMap, TInitFunction InInitFunction = [](THandleType){ })` — Template for register calls that move the modulator settings objects onto the Audio Processing Thread & create proxies. If the proxy is already found, adds provided HandleId as reference to given proxy. Does *not* update the proxy with the given settings.  If update is desired on an existing proxy, UpdateModulator must be explicitly called. @tparam THandleType Type of modulator handle used to access the proxy on the Processing Thread @tparam TModSettings Modulation settings to move and use if proxy construction is required on the Audio Processing Thread @tparam TMapType MapType used to cache the corresponding proxy id & proxy @tparam TInitFunction (Optional) Function type used to call on the AudioProcessingThread immediately following proxy construction @param InHandleId HandleId associated with the proxy to be retrieved/generated. @param InModSettings ModulatorSettings to be used if construction of proxy is required on Audio Processing Thread @param OutProxyMap Map to find or add proxy to if constructed @param InInitFunction Function type used to call on the AudioProcessingThread immediately following proxy generation
- L220 _private function_ `template <typename THandleType> bool UnregisterModulator(THandleType InModHandle, TMap<THandleType, FModulatorHandleSet>& OutHandleMap, const Audio::FModulatorHandleId InHandleId)`
- L241 _private member_ `FReferencedProxies RefProxies;`
- L245 _private member_ `mutable FCriticalSection ThreadSafeModValueCritSection;` — Critical section & map of copied, computed modulation values for use from the decoder threads & respective MetaSound getter nodes.
- L246 _private member_ `TMap<Audio::FModulatorId, float> ThreadSafeModValueMap;`
- L248 _private member_ `TSet<FBusMixId> ActiveBusMixIds;`
- L250 _private member_ `TSet<FBusHandle> ManuallyActivatedBuses;`
- L251 _private member_ `TSet<FBusMixHandle> ManuallyActivatedBusMixes;`
- L252 _private member_ `TSet<FGeneratorHandle> ManuallyActivatedGenerators;`
- L256 _private member_ `TMap<uint32, TObjectPtr<USoundControlBusMix>> ActiveGlobalBusValueMixes;` — Global mixes each containing a single stage for any globally manipulated bus stage value. the key in this map is the Bus's unique ID, not the Control Bus Mix's.
- L259 _private member_ `TQueue<TUniqueFunction<void()>, EQueueMode::Mpsc> ProcessingThreadCommandQueue;` — Command queue to be consumed on processing thread
- L262 _private member_ `TAtomic<uint32> ProcessingThreadId { 0 };` — Thread modulators are processed on
- L265 _private member_ `FReferencedModulators RefModulators;` — Collection of maps with modulator handles to referencing object ids used by externally managing objects
- L267 _private member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L297 _private prototype_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L299 _private prototype_ `void UpdateAudioInsightsTraceMessages(const double InElapsed);`
- L301 _private prototype_ `void TraceActivateModulatorMessage(const Audio::FModulatorId InModulatorId, const EModulatorTraceType InModulatorTraceType, const FString& InModulatorName);`
- L306 _private prototype_ `template <typename TModulatorProxy> void TraceUpdateModulatorMessage(const Audio::FModulatorId InModulatorId, const TModulatorProxy& InModulatorProxy, const EModulatorTraceType InModulatorTraceType, TArrayView<const Audio::FModulatorId> InContributingModulatorIds = TArrayView<const Audio::FModulatorId>(), TArrayView<const float> InContributingModulatorValues = TArrayView<const float>());`
- L312 _private prototype_ `void TraceDeactivateModulatorMessage(const Audio::FModulatorId InModulatorId);`
- L314 _private member_ `bool bIsAudioModulationInsightsPluginEnabled { false };`
- L316 _private member_ `float ModulatorActivePingTimeSec { 0.0f };`
- L317 _private member_ `static constexpr float ModulatorActivePingIntervalTimeSec { 1.0f };`
- L326 _private member_ `TArray<Audio::FModulatorId, TInlineAllocator<32>> CurrentlyActiveModulatorIds;`
- L327 _private member_ `TArray<Audio::FModulatorId, TInlineAllocator<32>> PreviouslyActiveModulatorIds;`
- L328 _private member_ `TMap<Audio::FModulatorId, FString> ActiveModulatorPaths;`
- L330 _private member_ `TArray<float, TInlineAllocator<32>> ContributingModulatorValues;`
- L331 _private member_ `TArray<Audio::FModulatorId, TInlineAllocator<32>> ContributingModulatorIds;`
- L332 _private member_ `TArray<AudioInsightsControlBusMixData, TInlineAllocator<32>> ControlBusMixContributingDataContainer;`
- L337 _public prototype_ `void SetDebugBusFilter(const FString* InFilter);`
- L338 _public prototype_ `void SetDebugMixFilter(const FString* InFilter);`
- L339 _public prototype_ `void SetDebugMatrixEnabled(bool bInIsEnabled);`
- L340 _public prototype_ `void SetDebugGeneratorsEnabled(bool bInIsEnabled);`
- L341 _public prototype_ `void SetDebugGeneratorFilter(const FString* InFilter);`
- L342 _public prototype_ `void SetDebugGeneratorTypeFilter(const FString* InFilter, bool bInIsEnabled);`
- L343 _public prototype_ `virtual void SetDebugActiveMixesEnabled(bool bInIsEnabled);`
- L344 _public prototype_ `virtual void SetDebugActiveGlobalMixesEnabled(bool bInIsEnabled);`
- L345 _public prototype_ `bool OnPostHelp(FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L346 _public prototype_ `int OnRenderStat(FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const UFont& Font, const FVector* ViewLocation, const FRotator* ViewRotation);`
- L347 _public prototype_ `bool OnToggleStat(FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L350 _private member_ `TSharedPtr<FAudioModulationDebugger> Debugger;`
- L371 _public function_ `void Initialize(const FAudioPluginInitializationParams& InitializationParams)`
- L373 _public function_ `void OnAuditionEnd()`
- L376 _public function_ `void SetDebugBusFilter(const FString* InFilter)`
- L377 _public function_ `void SetDebugMixFilter(const FString* InFilter)`
- L378 _public function_ `void SetDebugMatrixEnabled(bool bInIsEnabled)`
- L379 _public function_ `void SetDebugGeneratorsEnabled(bool bInIsEnabled)`
- L380 _public function_ `void SetDebugGeneratorFilter(const FString* InFilter)`
- L381 _public function_ `void SetDebugGeneratorTypeFilter(const FString* InFilter, bool bInIsEnabled)`
- L382 _public function_ `bool OnPostHelp(FCommonViewportClient* ViewportClient, const TCHAR* Stream)`
- L383 _public function_ `int OnRenderStat(FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const UFont& Font, const FVector* ViewLocation, const FRotator* ViewRotation)`
- L384 _public function_ `bool OnToggleStat(FCommonViewportClient* ViewportClient, const TCHAR* Stream)`
- L387 _public function_ `void ActivateBus(const USoundControlBus& InBus)`
- L388 _public function_ `void ActivateBusMix(FModulatorBusMixSettings&& InSettings)`
- L389 _public function_ `void ActivateBusMix(const USoundControlBusMix& InBusMix)`
- L390 _public function_ `void ActivateGenerator(const USoundModulationGenerator& InGenerator)`
- L392 _public function_ `void DeactivateAllBusMixes()`
- L393 _public function_ `void DeactivateBus(const USoundControlBus& InBus)`
- L394 _public function_ `void DeactivateBusMix(const USoundControlBusMix& InBusMix)`
- L395 _public function_ `void DeactivateBusMixByID(const uint32 ID)`
- L396 _public function_ `void DeactivateGenerator(const USoundModulationGenerator& InGenerator)`
- L398 _public function_ `Audio::FDeviceId GetAudioDeviceId() const`
- L400 _public function_ `bool IsControlBusMixActive(const USoundControlBusMix& InBusMix)`
- L402 _public function_ `void SaveMixToProfile(const USoundControlBusMix& InBusMix, const int32 InProfileIndex)`
- L403 _public function_ `TArray<FSoundControlBusMixStage> LoadMixFromProfile(const int32 InProfileIndex, USoundControlBusMix& OutBusMix)`
- L405 _public function_ `void SetGlobalBusMixValue(USoundControlBus& Bus, float Value, float FadeTime)`
- L406 _public function_ `void ClearGlobalBusMixValue(const USoundControlBus& InBus, float FadeTime)`
- L407 _public function_ `void ClearAllGlobalBusMixValues(float FadeTime)`
- L409 _public function_ `USoundControlBusMix* CreateBusMixFromValue(FName Name, const TArray<USoundControlBus*>& Buses, float Value, float AttackTime = -1.0f, float ReleaseTime = -1.0f, UObject* InOuter = nullptr)`
- L411 _public function_ `void ProcessModulators(const double InElapsed)`
- L412 _public function_ `void SoloBusMix(const USoundControlBusMix& InBusMix)`
- L414 _public function_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FControlBusSettings& InSettings)`
- L415 _public function_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationGeneratorSettings& InSettings)`
- L416 _public function_ `Audio::FModulatorTypeId RegisterModulator(Audio::FModulatorHandleId InHandleId, const FModulationPatchSettings& InSettings)`
- L418 _public function_ `void RegisterModulator(Audio::FModulatorHandleId InHandleId, Audio::FModulatorId InModulatorId)`
- L419 _public function_ `bool GetModulatorValue(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const`
- L420 _public function_ `bool GetModulatorValueThreadSafe(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const`
- L421 _public function_ `bool GetModulatorValueThreadSafe(uint32 ModulatorID, float& OutValue) const`
- L422 _public function_ `void UnregisterModulator(const Audio::FModulatorHandle& InHandle)`
- L429 _public function_ `void UpdateMix(const USoundControlBusMix& InMix, float InFadeTime = -1.0f)`
- L430 _public function_ `void UpdateMix(const TArray<FSoundControlBusMixStage>& InStages, USoundControlBusMix& InOutMix, bool bUpdateObject = false, float InFadeTime = -1.0f)`
- L431 _public function_ `void UpdateMixByFilter(const FString& InAddressFilter, const TSubclassOf<USoundModulationParameter>& InParamClassFilter, USoundModulationParameter* InParamFilter, float InValue, float InFadeTime, USoundControlBusMix& InOutMix, bool bUpdateObject = false)`
- L432 _public function_ `void UpdateModulator(const USoundModulatorBase& InModulator)`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace AudioModulation`
- L53 _typedef_ `using FModulatorHandleSet = TSet<Audio::FModulatorHandleId>;` (scope `AudioModulation`)
- L64 _namespace_ `namespace AudioModulation`
- L208 _function_ `` (scope `AudioModulation::FAudioModulationSystem::RegisterModulator`)
- L363 _namespace_ `namespace AudioModulation`
- L424 _function_ `inline bool FAudioModulationSystem::IsControlBusMixActive(const USoundControlBusMix* InBusMix)` (scope `AudioModulation::FAudioModulationSystem::FAudioModulationSystem`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/MovieSceneAudioControlBusMixSystem.h` (Private)


#### struct `UE::MovieScene::AudioControlBusMixSectionData`  
`struct AudioControlBusMixSectionData`  
_L19-23_
- L21 _public member_ `TObjectPtr<USoundControlBusMix> ControlBusMix;`
- L22 _public member_ `bool ControlBusMixActive;`

#### class `UMovieSceneAudioControlBusMixSystem`  
`class UMovieSceneAudioControlBusMixSystem : public UMovieSceneEntitySystem`  
_L27-50_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- L32 _public typedef_ `using FInstanceHandle = UE::MovieScene::FInstanceHandle;`
- L33 _public typedef_ `using AudioControlBusMixSectionData = UE::MovieScene::AudioControlBusMixSectionData;`
- L35 _public prototype_ `UMovieSceneAudioControlBusMixSystem(const FObjectInitializer& ObjInit);`
- L37 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L38 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L40 _public prototype_ `virtual void OnLink() override;`
- L41 _public prototype_ `virtual void OnUnlink() override;`
- L43 _public prototype_ `const AudioControlBusMixSectionData* GetSectionData(FObjectKey Key) const;`
- L44 _public prototype_ `AudioControlBusMixSectionData* AddSectionData(FObjectKey Key, TObjectPtr<USoundControlBusMix> ControlBusMix, bool bIsActive);`
- L47 _public member_ `TSharedPtr<UE::MovieScene::FPreAnimatedAudioControlBusMixStorage> PreAnimatedStorage;` — Pre-animated state
- L49 _public member_ `TMap<FObjectKey, AudioControlBusMixSectionData> EvaluatedBusMixes;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/MovieSceneAudioControlBusSystem.h` (Private)


#### struct `FAudioControlBusSectionData`  
`struct FAudioControlBusSectionData`  
_L19-26_
- reflection: `USTRUCT()`
- L24 _public member_ `TObjectPtr<USoundControlBusMix> ControlBusMix;` — `UPROPERTY(Transient)`
- L25 _public member_ `uint32 BusMixID;`

#### class `UMovieSceneAudioControlBusSystem`  
`class UMovieSceneAudioControlBusSystem : public UMovieSceneEntitySystem`  
_L29-53_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- L34 _public typedef_ `using FInstanceHandle = UE::MovieScene::FInstanceHandle;`
- L36 _public prototype_ `UMovieSceneAudioControlBusSystem(const FObjectInitializer& ObjInit);`
- L38 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L39 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L41 _public prototype_ `virtual void OnLink() override;`
- L42 _public prototype_ `virtual void OnUnlink() override;`
- L44 _public prototype_ `void ClearBusMixes();`
- L46 _public prototype_ `const FAudioControlBusSectionData* GetAudioControlBusComponentEvaluationData(const TObjectPtr<UMovieSceneAudioControlBusSection> SectionKey) const;`
- L47 _public prototype_ `FAudioControlBusSectionData* AddAudioControlBusComponentEvaluationData(FInstanceHandle InstanceHandle, TObjectPtr<UMovieSceneAudioControlBusSection> SectionKey, USoundModulatorBase* SectionData, USoundControlBusMix* Mix);`
- L48 _public prototype_ `void RemoveAudioControlBusComponentEvaluationData(TObjectPtr<UMovieSceneAudioControlBusSection> SectionKey);`
- L52 _protected member_ `TMap<TObjectPtr<UMovieSceneAudioControlBusSection>, FAudioControlBusSectionData> ModulatorsByObjectKey;` — `UPROPERTY(Transient)`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/SoundControlBusMixProxy.h` (Private)


#### class `AudioModulation::FModulatorBusMixStageSettings`  
`class FModulatorBusMixStageSettings : public TModulatorBase<FBusId>`  
_L24-34_
- inherits: `TModulatorBase<FBusId>`
- L27 _public prototype_ `FModulatorBusMixStageSettings(const FSoundControlBusMixStage& InStage);`
- L29 _public member_ `FString Address;`
- L30 _public member_ `uint32 ParamClassId = INDEX_NONE;`
- L31 _public member_ `uint32 ParamId = INDEX_NONE;`
- L32 _public member_ `FSoundModulationMixValue Value;`
- L33 _public member_ `FControlBusSettings BusSettings;`

#### class `AudioModulation::FModulatorBusMixSettings`  
`class FModulatorBusMixSettings : public TModulatorBase<FBusMixId>`  
_L36-46_
- inherits: `TModulatorBase<FBusMixId>`
- L39 _public prototype_ `FModulatorBusMixSettings(const USoundControlBusMix& InBusMix);`
- L40 _public prototype_ `FModulatorBusMixSettings(FModulatorBusMixSettings&& InSettings);`
- L42 _public member_ `TArray<FModulatorBusMixStageSettings> Stages;`
- L44 _public member_ `double Duration = -1.0;`
- L45 _public member_ `bool bRetriggerOnActivation = false;`

#### class `AudioModulation::FModulatorBusMixStageProxy`  
`class FModulatorBusMixStageProxy : public TModulatorBase<FBusId>`  
_L48-59_
- inherits: `TModulatorBase<FBusId>`
- L52 _public prototype_ `FModulatorBusMixStageProxy(FModulatorBusMixStageSettings&& InSettings, FAudioModulationSystem& OutModSystem);`
- L54 _public member_ `FString Address;`
- L55 _public member_ `uint32 ParamClassId = INDEX_NONE;`
- L56 _public member_ `uint32 ParamId = INDEX_NONE;`
- L57 _public member_ `FSoundModulationMixValue Value;`
- L58 _public member_ `FBusHandle BusHandle;`

#### class `AudioModulation::FModulatorBusMixProxy`  
`class FModulatorBusMixProxy : public TModulatorProxyRefType<FBusMixId, FModulatorBusMixProxy, FModulatorBusMixSettings>`  
_L61-107_
- inherits: `TModulatorProxyRefType<FBusMixId,FModulatorBusMixProxy,FModulatorBusMixSettings>`
- L71 _public prototype_ `FModulatorBusMixProxy(FModulatorBusMixSettings&& InMix, FAudioModulationSystem& InModSystem);`
- L73 _public prototype_ `FModulatorBusMixProxy& operator=(FModulatorBusMixSettings&& InSettings);`
- L75 _public prototype_ `EStatus GetStatus() const;`
- L78 _public prototype_ `void Reset();` — Resets stage map
- L80 _public prototype_ `void SetEnabled();`
- L81 _public prototype_ `void SetStopping();`
- L83 _public prototype_ `void SetMixData(const TArray<FModulatorBusMixStageSettings>& InStages, float InFadeTime, const FString& BusMixName, double InDuration, bool bInRetriggerOnActivation);` — Set stage and Mix Config settings. This does not enable/activate the mix; for that, use SetEnabled
- L85 _public prototype_ `void SetMixDataAndEnable(FModulatorBusMixSettings&& InSettings);`
- L88 _public prototype_ `void SetMixByFilter(const FString& InAddressFilter, uint32 InParamClassId, uint32 InParamId, float InValue, float InFadeTime);` — Set the stage values of all buses which satisfy the input filter data. If any of the filters (Address, Parameter type, or specific parameter) are satisfied, that stage's value will be set
- L90 _public prototype_ `void Update(const double Elapsed, FBusProxyMap& ProxyMap);`
- L93 _public prototype_ `double GetTimeRemaining() const;` — If the Control Bus Mix is using a timer, returns the amount of time left before deactivation (seconds). Otherwise returns -1.
- L95 _public typedef_ `using FStageMap = TMap<FBusId, FModulatorBusMixStageProxy>;`
- L96 _public member_ `FStageMap Stages;`
- L99 _private member_ `EStatus Status = EStatus::Stopped;`
- L100 _private member_ `double Duration = -1.0;`
- L101 _private member_ `double TimeRemaining = 0.0;`
- L102 _private member_ `bool bRetriggerOnActivation = false;`
- L104 _private member_ `TArray<float> StageValues;`
- L106 _private prototype_ `void SetMixData(FModulatorBusMixSettings&& InSettings);`

#### enum `AudioModulation::FModulatorBusMixProxy::EStatus`  
`enum class EStatus : uint8`  
_L64-69_
- L66 _public enumerator_ `Enabled`
- L67 _public enumerator_ `Stopping`
- L68 _public enumerator_ `Stopped`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AudioModulation`
- L21 _typedef_ `using FBusMixId = uint32;` (scope `AudioModulation`)
- L22 _externvar_ `extern const FBusMixId InvalidBusMixId;` (scope `AudioModulation`)
- L109 _typedef_ `using FBusMixProxyMap = TMap<FBusMixId, FModulatorBusMixProxy>;` (scope `AudioModulation`)
- L110 _typedef_ `using FBusMixHandle = TProxyHandle<FBusMixId, FModulatorBusMixProxy, FModulatorBusMixSettings>;` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/SoundControlBusProxy.h` (Private)


#### struct `AudioModulation::FControlBusSettings`  
`struct FControlBusSettings : public TModulatorBase<FBusId>, public Audio::IModulatorSettings`  
_L20-62_
- inherits: `TModulatorBase<FBusId>,Audio::IModulatorSettings`
- L22 _public member_ `bool bBypass;`
- L23 _public member_ `float DefaultValue;`
- L25 _public member_ `TArray<FModulationGeneratorSettings> GeneratorSettings;`
- L26 _public member_ `Audio::FModulationMixFunction MixFunction;`
- L27 _public member_ `Audio::FModulationParameter OutputParameter;`
- L29 _public function_ `FControlBusSettings(const USoundControlBus& InBus) : TModulatorBase<FBusId>(InBus.GetPathName(), InBus.GetUniqueID()) , bBypass(InBus.bBypass) , DefaultValue(InBus.GetDefaultNormalizedValue()) , MixFunction(InBus.GetMixFunction()) , OutputParameter(InBus.GetOutputParameter())`
- L46 _public function_ `virtual TUniquePtr<IModulatorSettings> Clone() const override`
- L51 _public function_ `virtual Audio::FModulatorId GetModulatorId() const override`
- L56 _public function_ `virtual const Audio::FModulationParameter& GetOutputParameter() const override`
- L61 _public prototype_ `virtual Audio::FModulatorTypeId Register(Audio::FModulatorHandleId HandleId, IAudioModulationManager& InModulation) const override;`

#### class `AudioModulation::FControlBusProxy`  
`class FControlBusProxy : public TModulatorProxyRefType<FBusId, FControlBusProxy, FControlBusSettings>`  
_L64-105_
- inherits: `TModulatorProxyRefType<FBusId,FControlBusProxy,FControlBusSettings>`
- L67 _public prototype_ `FControlBusProxy();`
- L68 _public prototype_ `FControlBusProxy(FControlBusSettings&& InSettings, FAudioModulationSystem& InModSystem);`
- L70 _public prototype_ `FControlBusProxy& operator =(FControlBusSettings&& InSettings);`
- L72 _public prototype_ `float GetDefaultValue() const;`
- L73 _public prototype_ `const TArray<FGeneratorHandle>& GetGeneratorHandles() const;`
- L74 _public prototype_ `float GetGeneratorValue() const;`
- L75 _public prototype_ `float GetMixValue() const;`
- L76 _public prototype_ `float GetValue() const;`
- L77 _public prototype_ `FName GetParameterName() const;`
- L78 _public prototype_ `bool IsBypassed() const;`
- L79 _public prototype_ `void MixIn(const float InValue);`
- L80 _public prototype_ `void MixGenerators();`
- L81 _public prototype_ `void Reset();`
- L84 _private prototype_ `void Init(FControlBusSettings&& InSettings);`
- L85 _private prototype_ `float Mix(float ValueA) const;`
- L86 _private prototype_ `bool IsParameterClamped() const;`
- L88 _private member_ `float DefaultValue = 0.0f;`
- L91 _private member_ `float GeneratorValue = 1.0f;` — Cached values
- L92 _private member_ `float MixValue = NAN;`
- L94 _private member_ `bool bBypass = false;`
- L96 _private member_ `bool bClampToNormalizedRange = true;`
- L98 _private member_ `Audio::FModulationMixFunction MixFunction;`
- L99 _private member_ `TArray<FGeneratorHandle> GeneratorHandles;`
- L102 _private member_ `FName ParameterName;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AudioModulation`
- L17 _typedef_ `using FBusId = uint32;` (scope `AudioModulation`)
- L18 _externvar_ `extern const FBusId InvalidBusId;` (scope `AudioModulation`)
- L107 _typedef_ `using FBusProxyMap = TMap<FBusId, FControlBusProxy>;` (scope `AudioModulation`)
- L108 _typedef_ `using FBusHandle = TProxyHandle<FBusId, FControlBusProxy, FControlBusSettings>;` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/SoundModulationGeneratorProxy.h` (Private)


#### struct `AudioModulation::FModulationGeneratorSettings`  
`struct FModulationGeneratorSettings : public TModulatorBase<FGeneratorId>, public Audio::IModulatorSettings`  
_L26-63_
- inherits: `TModulatorBase<FGeneratorId>,Audio::IModulatorSettings`
- L28 _public member_ `FGeneratorPtr Generator;`
- L30 _public prototype_ `FModulationGeneratorSettings() = default;`
- L32 _public function_ `FModulationGeneratorSettings(const USoundModulationGenerator& InGenerator) : TModulatorBase<FGeneratorId>(InGenerator.GetPathName(), InGenerator.GetUniqueID()) , Generator(InGenerator.CreateInstance())`
- L38 _public function_ `FModulationGeneratorSettings(const FModulationGeneratorSettings& InSettings) : TModulatorBase<FGeneratorId>(InSettings.GetPath(), InSettings.GetId()) , Generator(InSettings.Generator.IsValid() ? InSettings.Generator->Clone() : nullptr)`
- L44 _public function_ `FModulationGeneratorSettings(FModulationGeneratorSettings&& InSettings) : TModulatorBase<FGeneratorId>(InSettings.GetPath(), InSettings.GetId()) , Generator(MoveTemp(InSettings.Generator))`
- L50 _public function_ `virtual TUniquePtr<IModulatorSettings> Clone() const override`
- L56 _public function_ `virtual Audio::FModulatorId GetModulatorId() const override`
- L61 _public prototype_ `virtual const Audio::FModulationParameter& GetOutputParameter() const override;`
- L62 _public prototype_ `virtual Audio::FModulatorTypeId Register(Audio::FModulatorHandleId HandleId, IAudioModulationManager& InModulation) const override;`

#### class `AudioModulation::FModulatorGeneratorProxy`  
`class FModulatorGeneratorProxy : public TModulatorProxyRefType<FGeneratorId, FModulatorGeneratorProxy, FModulationGeneratorSettings>`  
_L65-130_
- inherits: `TModulatorProxyRefType<FGeneratorId,FModulatorGeneratorProxy,FModulationGeneratorSettings>`
- L67 _private member_ `FGeneratorPtr Generator;`
- L70 _public prototype_ `FModulatorGeneratorProxy() = default;`
- L71 _public prototype_ `FModulatorGeneratorProxy(FModulationGeneratorSettings&& InSettings, FAudioModulationSystem& InModSystem);`
- L73 _public prototype_ `FModulatorGeneratorProxy& operator =(FModulationGeneratorSettings&& InSettings);`
- L75 _public function_ `float GetValue() const`
- L80 _public function_ `void Init(Audio::FDeviceId InDeviceId)`
- L85 _public function_ `bool IsBypassed() const`
- L90 _public function_ `void Update(double InElapsed)`
- L95 _public function_ `void PumpCommands()`
- L101 _public function_ `TArray<FString> GetDebugCategories() const`
- L114 _public function_ `TArray<FString> GetDebugValues() const`
- L125 _public function_ `const FString& GetDebugName() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AudioModulation`
- L20 _typedef_ `using FGeneratorId = uint32;` (scope `AudioModulation`) — Modulator Ids
- L21 _externvar_ `extern const FGeneratorId InvalidGeneratorId;` (scope `AudioModulation`)
- L23 _typedef_ `using FGeneratorProxyMap = TMap<FGeneratorId, FModulatorGeneratorProxy>;` (scope `AudioModulation`)
- L24 _typedef_ `using FGeneratorHandle = TProxyHandle<FGeneratorId, FModulatorGeneratorProxy, FModulationGeneratorSettings>;` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/SoundModulationPatchProxy.h` (Private)


#### struct `AudioModulation::FModulationInputSettings`  
`struct FModulationInputSettings`  
_L22-41_
- L24 _public member_ `FControlBusSettings BusSettings;`
- L25 _public member_ `FSoundModulationTransform Transform;`
- L26 _public member_ `uint8 bSampleAndHold : 1;`
- L28 _public function_ `FModulationInputSettings(const FSoundControlModulationInput& InInput) : BusSettings(InInput.GetBusChecked()) , Transform(InInput.Transform) , bSampleAndHold(InInput.bSampleAndHold)`
- L35 _public function_ `FModulationInputSettings(FSoundControlModulationInput&& InInput) : BusSettings(InInput.GetBusChecked()) , Transform(MoveTemp(InInput.Transform)) , bSampleAndHold(InInput.bSampleAndHold)`

#### class `AudioModulation::FModulationInputProxy`  
`class FModulationInputProxy`  
_L44-57_
- desc: Modulation input instance
- L47 _public prototype_ `FModulationInputProxy() = default;`
- L48 _public prototype_ `FModulationInputProxy(FModulationInputSettings&& InSettings, FAudioModulationSystem& OutModSystem);`
- L50 _public member_ `FBusHandle BusHandle;`
- L52 _public member_ `FSoundModulationTransform Transform;`
- L54 _public member_ `float ModStageValue = 1.0f;`
- L56 _public member_ `bool bSampleAndHold = false;`

#### struct `AudioModulation::FModulationOutputProxy`  
`struct FModulationOutputProxy`  
_L60-76_
- desc: Patch applied as the final stage of a modulation chain prior to output on the sound level (Always active, never removed)
- L62 _public prototype_ `FModulationOutputProxy() = default;`
- L63 _public prototype_ `FModulationOutputProxy(float InDefaultValue, const Audio::FModulationMixFunction& InMixFunction);`
- L66 _public member_ `bool bInitialized = false;` — Whether patch has been initialized or not
- L69 _public member_ `float SampleAndHoldValue = 1.0f;` — Cached value of sample-and-hold input values
- L72 _public member_ `Audio::FModulationMixFunction MixFunction;` — Function used to mix values together
- L75 _public member_ `float DefaultValue = 1.0f;` — Default value if no inputs are provided

#### struct `AudioModulation::FModulationPatchSettings`  
`struct FModulationPatchSettings : public TModulatorBase<FPatchId>, public Audio::IModulatorSettings`  
_L78-123_
- inherits: `TModulatorBase<FPatchId>,Audio::IModulatorSettings`
- L80 _public member_ `TArray<FModulationInputSettings> InputSettings;`
- L81 _public member_ `bool bBypass = true;`
- L83 _public member_ `Audio::FModulationParameter OutputParameter;`
- L85 _public prototype_ `FModulationPatchSettings() = default;`
- L86 _public prototype_ `FModulationPatchSettings(const FModulationPatchSettings& InPatchSettings) = default;`
- L88 _public function_ `FModulationPatchSettings(const USoundModulationPatch& InPatch) : TModulatorBase<FPatchId>(InPatch.GetPathName(), InPatch.GetUniqueID()) , bBypass(InPatch.PatchSettings.bBypass) , OutputParameter(InPatch.GetOutputParameter())`
- L107 _public function_ `virtual TUniquePtr<IModulatorSettings> Clone() const override`
- L112 _public function_ `virtual Audio::FModulatorId GetModulatorId() const override`
- L117 _public function_ `virtual const Audio::FModulationParameter& GetOutputParameter() const override`
- L122 _public prototype_ `virtual Audio::FModulatorTypeId Register(Audio::FModulatorHandleId HandleId, IAudioModulationManager& InAudioModulation) const override;`

#### class `AudioModulation::FModulationPatchProxy`  
`class FModulationPatchProxy`  
_L125-163_
- L128 _public prototype_ `FModulationPatchProxy() = default;`
- L129 _public prototype_ `FModulationPatchProxy(FModulationPatchSettings&& InSettings, FAudioModulationSystem& InModSystem);`
- L132 _public prototype_ `bool IsBypassed() const;` — Whether or not the patch is bypassed (effectively just returning the default value)
- L135 _public prototype_ `float GetValue() const;` — Returns the value of the patch
- L138 _public prototype_ `void Update();` — Updates the patch value
- L141 _protected prototype_ `void Init(FModulationPatchSettings&& InSettings, FAudioModulationSystem& InModSystem);`
- L145 _private member_ `float DefaultValue = 1.0f;` — Default value of patch
- L148 _private member_ `float Value = 1.0f;` — Current value of the patch
- L151 _private member_ `TArray<FModulationInputProxy> InputProxies;` — Optional modulation inputs
- L154 _private member_ `FModulationOutputProxy OutputProxy;` — Final output modulation post input combination
- L157 _private member_ `bool bBypass = true;` — Bypasses the patch and doesn't update modulation value
- L160 _private member_ `bool bClampOutputToNormalizedRange = true;` — Whether or not the final output should be clamped to [0,1], based on the Parameter passed in from FModulationPatchSettings

#### class `AudioModulation::FModulationPatchRefProxy`  
`class FModulationPatchRefProxy : public TModulatorProxyRefType<FPatchId, FModulationPatchRefProxy, FModulationPatchSettings>, public FModulationPatchProxy`  
_L165-172_
- inherits: `TModulatorProxyRefType<FPatchId,FModulationPatchRefProxy,FModulationPatchSettings>,FModulationPatchProxy`
- L168 _public prototype_ `FModulationPatchRefProxy();`
- L169 _public prototype_ `FModulationPatchRefProxy(FModulationPatchSettings&& InSettings, FAudioModulationSystem& OutModSystem);`
- L171 _public prototype_ `FModulationPatchRefProxy& operator=(FModulationPatchSettings&& InSettings);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AudioModulation`
- L19 _typedef_ `using FPatchId = uint32;` (scope `AudioModulation`)
- L20 _externvar_ `extern const FPatchId InvalidPatchId;` (scope `AudioModulation`)
- L174 _typedef_ `using FPatchProxyMap = TMap<FPatchId, FModulationPatchRefProxy>;` (scope `AudioModulation`)
- L175 _typedef_ `using FPatchHandle = TProxyHandle<FPatchId, FModulationPatchRefProxy, FModulationPatchSettings>;` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/SoundModulationProxy.h` (Private)


#### class `AudioModulation::TProxyHandle`  
`template<typename IdType, typename ProxyType, typename ProxySettings> class TProxyHandle`  
_L18-230_
- desc: Handle for all ref-counted proxy types, to be used only on the modulator processing thread (not thread safe).
- L20 _private member_ `IdType Id;`
- L21 _private member_ `TMap<IdType, ProxyType>* ProxyMap;`
- L24 _public function_ `FORCEINLINE bool IsValid() const`
- L29 _public function_ `FORCEINLINE IdType GetId() const`
- L34 _public function_ `FORCEINLINE ProxyType& FindProxy()`
- L42 _public function_ `FORCEINLINE const ProxyType& FindProxy() const`
- L55 _public function_ `TProxyHandle() : Id(static_cast<IdType>(INDEX_NONE)) , ProxyMap(nullptr)`
- L61 _public function_ `TProxyHandle(IdType InId, TMap<IdType, ProxyType>& InProxyMap) : Id(InId) , ProxyMap(&InProxyMap)`
- L72 _public function_ `TProxyHandle(const TProxyHandle& InHandle) : Id(InHandle.Id) , ProxyMap(InHandle.ProxyMap)`
- L83 _public function_ `TProxyHandle(TProxyHandle&& InHandle) : Id(InHandle.Id) , ProxyMap(InHandle.ProxyMap)`
- L92 _public function_ `~TProxyHandle()`
- L115 _public function_ `static TProxyHandle<IdType, ProxyType, ProxySettings> Get(const IdType ObjectId, TMap<IdType, ProxyType>& OutProxyMap)` — Creates a handle to a proxy modulation object tracked in the provided InProxyMap if it exists, otherwise returns invalid handle.
- L129 _public function_ `static TProxyHandle<IdType, ProxyType, ProxySettings> Create(ProxySettings&& InSettings, TMap<IdType, ProxyType>& OutProxyMap, FAudioModulationSystem& OutModSystem)` — Creates a handle to a proxy modulation object tracked in the provided InProxyMap.  Creates new proxy if it doesn't exist.
- L144 _public function_ `static TProxyHandle<IdType, ProxyType, ProxySettings> Create(ProxySettings&& InSettings, TMap<IdType, ProxyType>& OutProxyMap, FAudioModulationSystem& OutModSystem, TFunction<void(ProxyType&)> OnCreateProxy)`
- L159 _public function_ `FORCEINLINE bool operator ==(const TProxyHandle<IdType, ProxyType, ProxySettings>& InHandle) const`
- L164 _public function_ `FORCEINLINE TProxyHandle<IdType, ProxyType, ProxySettings>& operator =(const TProxyHandle<IdType, ProxyType, ProxySettings>& InHandle)`
- L193 _public function_ `FORCEINLINE TProxyHandle<IdType, ProxyType, ProxySettings>& operator =(TProxyHandle<IdType, ProxyType, ProxySettings>&& InHandle)`

#### class `AudioModulation::TModulatorBase`  
`template <typename IdType> class TModulatorBase`  
_L234-319_
- desc: Modulator Proxy Templates
- L238 _private function_ `FString ResolveName(const FString& InNamePath)`
- L260 _private member_ `IdType Id;`
- L263 _private member_ `FName Name;`
- L264 _private member_ `FName Path;`
- L268 _public function_ `TModulatorBase() : Id(static_cast<IdType>(INDEX_NONE))`
- L273 _public function_ `TModulatorBase(const FName InPath, const uint32 InId) : Id(static_cast<IdType>(InId)) #if !UE_BUILD_SHIPPING , Name(ResolveName(InPath.ToString())) , Path(InPath) #endif`
- L282 _public function_ `TModulatorBase(const FString& InPath, const uint32 InId) : Id(static_cast<IdType>(InId)) #if !UE_BUILD_SHIPPING , Name(ResolveName(InPath)) , Path(InPath) #endif`
- L291 _public prototype_ `virtual ~TModulatorBase() = default;`
- L293 _public function_ `IdType GetId() const`
- L300 _public function_ `const FName& GetName() const` — FOR DEBUG USE ONLY (Not available in shipped builds): Provides name of object that generated proxy.
- L311 _public function_ `const FName& GetPath() const` — FOR DEBUG USE ONLY (Not available in shipped builds): Provides path of object that generated proxy.

#### class `AudioModulation::TModulatorProxyRefType`  
`template<typename IdType, typename ProxyType, typename ProxySettings> class TModulatorProxyRefType : public TModulatorBase<IdType>`  
_L322-403_
- inherits: `TModulatorBase<IdType>`
- L325 _protected member_ `uint32 RefCount;`
- L326 _protected member_ `FAudioModulationSystem* ModSystem;`
- L329 _public function_ `TModulatorProxyRefType() : TModulatorBase<IdType>() , RefCount(0) , ModSystem(nullptr)`
- L336 _public function_ `TModulatorProxyRefType(const FName& InPath, const uint32 InId, FAudioModulationSystem& OutModSystem) : TModulatorBase<IdType>(InPath, InId) , RefCount(0) , ModSystem(&OutModSystem)`
- L343 _public function_ `TModulatorProxyRefType(const TModulatorProxyRefType& InProxyRef) : TModulatorBase<IdType>(InProxyRef.GetPath(), InProxyRef.GetId()) , RefCount(InProxyRef.RefCount) , ModSystem(InProxyRef.ModSystem)`
- L350 _public function_ `TModulatorProxyRefType(TModulatorProxyRefType&& InProxyRef) : TModulatorBase<IdType>(InProxyRef.GetPath(), InProxyRef.GetId()) , RefCount(InProxyRef.RefCount) , ModSystem(InProxyRef.ModSystem)`
- L359 _public function_ `TModulatorProxyRefType& operator=(const TModulatorProxyRefType& InOther)`
- L366 _public function_ `TModulatorProxyRefType& operator=(TModulatorProxyRefType&& InOther)`
- L377 _public function_ `virtual ~TModulatorProxyRefType()`
- L382 _public function_ `uint32 GetRefCount() const`
- L388 _protected function_ `FORCEINLINE void IncRef()`
- L393 _protected function_ `FORCEINLINE uint32 DecRef()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AudioModulation`
- L50 _function_ `friend FORCEINLINE uint32 GetTypeHash(const TProxyHandle<IdType, ProxyType, ProxySettings>& InHandle)` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulation.h` (Public)


#### class `AudioModulation::FAudioModulationManager`  
`class FAudioModulationManager : public IAudioModulationManager`  
_L31-110_
- inherits: `IAudioModulationManager`
- L34 _public prototype_ `FAudioModulationManager();`
- L35 _public prototype_ `virtual ~FAudioModulationManager();`
- L38 _public prototype_ `virtual void Initialize(const FAudioPluginInitializationParams& InitializationParams) override;`
- L39 _public prototype_ `virtual void OnAuditionEnd() override;`
- L41 _public prototype_ `virtual void GetControlBusAssetPath(TArray<FTopLevelAssetPath>& OutClassNames) override;`
- L44 _public prototype_ `virtual void SetDebugBusFilter(const FString* InFilter);`
- L45 _public prototype_ `virtual void SetDebugMixFilter(const FString* InFilter);`
- L46 _public prototype_ `virtual void SetDebugMatrixEnabled(bool bInIsEnabled);`
- L47 _public prototype_ `virtual void SetDebugGeneratorsEnabled(bool bInIsEnabled);`
- L48 _public prototype_ `virtual void SetDebugGeneratorFilter(const FString* InFilter);`
- L49 _public prototype_ `virtual void SetDebugGeneratorTypeFilter(const FString* InFilter, bool bInIsEnabled);`
- L50 _public prototype_ `virtual void SetDebugActiveMixesEnabled(bool bInIsEnabled);`
- L51 _public prototype_ `virtual void SetDebugActiveGlobalMixesEnabled(bool bInIsEnabled);`
- L53 _public prototype_ `virtual bool OnPostHelp(FCommonViewportClient* ViewportClient, const TCHAR* Stream) override;`
- L54 _public prototype_ `virtual int32 OnRenderStat(FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const UFont& Font, const FVector* ViewLocation, const FRotator* ViewRotation) override;`
- L55 _public prototype_ `virtual bool OnToggleStat(FCommonViewportClient* ViewportClient, const TCHAR* Stream) override;`
- L58 _public prototype_ `virtual void ProcessModulators(const double InElapsed) override;`
- L59 _public prototype_ `virtual void UpdateModulator(const USoundModulatorBase& InModulator) override;`
- L62 _protected prototype_ `virtual void RegisterModulator(Audio::FModulatorHandleId InHandleId, Audio::FModulatorId InModulatorId) override;`
- L63 _protected prototype_ `virtual bool GetModulatorValue(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const override;`
- L64 _protected prototype_ `virtual bool GetModulatorValueThreadSafe(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const override;`
- L65 _protected prototype_ `virtual void UnregisterModulator(const Audio::FModulatorHandle& InHandle) override;`
- L70 _public prototype_ `void ActivateBus(const USoundControlBus& InBus);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestination to safety activate and track a given modulator")`
- L72 _public prototype_ `void ActivateBusMix(const USoundControlBusMix& InBusMix);`
- L75 _public prototype_ `void ActivateGenerator(const USoundModulationGenerator& InGenerator);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestination to safety activate and track a given modulator")`
- L77 _public prototype_ `USoundControlBusMix* CreateBusMixFromValue(FName Name, const TArray<USoundControlBus*>& Buses, float Value, float AttackTime = -1.0f, float ReleaseTime = -1.0f, UObject* InOuter = nullptr);`
- L80 _public prototype_ `void DeactivateBus(const USoundControlBus& InBus);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestination to safety activate and track a given modulator")`
- L82 _public prototype_ `void DeactivateBusMix(const USoundControlBusMix& InBusMix);`
- L83 _public prototype_ `void DeactivateBusMixByID(const uint32 ID);`
- L84 _public prototype_ `void DeactivateAllBusMixes();`
- L87 _public prototype_ `void DeactivateGenerator(const USoundModulationGenerator& InGenerator);` — `UE_DEPRECATED(5.4, "Deactivation of modulators in this manner is now deprecated. Use USoundModulationDestination to safety activate and track a given modulator")`
- L89 _public prototype_ `bool IsBusMixActive(const USoundControlBusMix& InBusMix);`
- L91 _public prototype_ `void SaveMixToProfile(const USoundControlBusMix& InBusMix, const int32 InProfileIndex);`
- L92 _public prototype_ `TArray<FSoundControlBusMixStage> LoadMixFromProfile(const int32 InProfileIndex, USoundControlBusMix& OutBusMix);`
- L94 _public prototype_ `void UpdateMix(const TArray<FSoundControlBusMixStage>& InStages, USoundControlBusMix& InOutMix, bool bInUpdateObject = false, float InFadeTime = -1.0f, double Duration = -1.0, bool bRetriggerOnActivation = false);`
- L95 _public prototype_ `void UpdateMix(const USoundControlBusMix& InMix, float InFadeTime = -1.0f);`
- L96 _public prototype_ `void UpdateMixByFilter(const FString& InAddressFilter, const TSubclassOf<USoundModulationParameter>& InParamClassFilter, USoundModulationParameter* InParamFilter, float Value, float FadeTime, USoundControlBusMix& InOutMix, bool bInUpdateObject = false);`
- L98 _public prototype_ `void SoloBusMix(const USoundControlBusMix& InBusMix);`
- L100 _public prototype_ `void SetGlobalBusMixValue(USoundControlBus& InBus, float InValue, float InFadeTime);`
- L101 _public prototype_ `void ClearGlobalBusMixValue(const USoundControlBus& InBus, float InFadeTime);`
- L102 _public prototype_ `void ClearAllGlobalBusMixValues(float InFadeTime);`
- L104 _public prototype_ `float GetModulatorValueThreadSafe(uint32 ModulationID);`
- L106 _public prototype_ `FAudioModulationSystem& GetSystem();`
- L109 _private member_ `FAudioModulationSystem* ModSystem = nullptr;`

#### class `FAudioModulationPluginFactory`  
`class FAudioModulationPluginFactory : public IAudioModulationFactory`  
_L117-127_
- inherits: `IAudioModulationFactory`
- L120 _public function_ `virtual const FName& GetDisplayName() const override`
- L126 _public prototype_ `virtual TAudioModulationPtr CreateNewModulationPlugin(FAudioDevice* OwningDevice) override;`

#### class `FAudioModulationModule`  
`class FAudioModulationModule : public IModuleInterface`  
_L129-137_
- inherits: `IModuleInterface`
- L132 _public prototype_ `virtual void StartupModule() override;`
- L133 _public prototype_ `virtual void ShutdownModule() override;`
- L136 _private member_ `FAudioModulationPluginFactory ModulationPluginFactory;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API AUDIOMODULATION_API`
- L21 _delegate_ `DECLARE_STATS_GROUP(TEXT("AudioModulation"), STATGROUP_AudioModulation, STA` — Cycle stats for audio mixer
- L24 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Process Modulators"), STAT_AudioModulationProcessModulators, STATGROUP_AudioModulation, AUD` — Tracks the time for the full render block
- L26 _namespace_ `namespace AudioModulation`
- L112 _prototype_ `FAudioModulationManager* GetDeviceModulationManager(Audio::FDeviceId InDeviceId);` (scope `AudioModulation`)
- L114 _prototype_ `void IterateModulationManagers(TFunctionRef<void(FAudioModulationManager&)> InFunction);` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationDestination.h` (Public)


#### class `UAudioModulationDestination`  
`class UAudioModulationDestination : public UObject`  
_L15-43_
- reflection: `UCLASS(MinimalAPI, config = Engine, editinlinenew, BlueprintType)`
- inherits: `UObject`
- L21 _private member_ `TObjectPtr<const USoundModulatorBase> Modulator;` — `UPROPERTY()`
- L23 _private member_ `Audio::FModulationDestination Destination;`
- L26 _public prototype_ `virtual void PostInitProperties() override;`
- L30 _public prototype_ `UPARAM(DisplayName = "Modulator Cleared") bool` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Clear Modulator")` — Returns true if a modulator was set and has been cleared.
- L34 _public prototype_ `UPARAM(DisplayName = "Modulator") const USoundModulatorBase* GetModulator` — `UFUNCTION(BlueprintPure, Category = "Audio|Modulation")` — Returns currently set modulator.
- L38 _public prototype_ `UPARAM(DisplayName = "Value") float GetValue() c` — `UFUNCTION(BlueprintPure, Category = "Audio|Modulation", DisplayName = "Get Watched Modulator Value")` — Returns the last calculated modulator value sampled from the thread controls are processed on.
- L42 _public prototype_ `UPARAM(DisplayName = "Modulator Set") bool SetModulator(const USoundModulatorBase*` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Set Watched Modulator")` — Returns true if modulator was set to new value or was already set to provided value.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOMODULATION_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationSettings.h` (Public)


#### class `UAudioModulationSettings`  
`class UAudioModulationSettings : public UDeveloperSettings`  
_L17-35_
- reflection: `UCLASS(MinimalAPI, config=AudioModulation, defaultconfig, meta = (DisplayName = "Audio Modulation"))`
- inherits: `UDeveloperSettings`
- L24 _public member_ `TArray<FSoftObjectPath> Parameters;` — `UPROPERTY(config, EditAnywhere, Category = "Parameters", meta = (AllowedClasses = "/Script/AudioModulation.SoundModulationParameter"))` — Array of Modulation Parameters that are loaded on plugin startup
- L26 _public prototype_ `void RegisterParameters() const;`
- L28 _public prototype_ `TObjectPtr<USoundModulationParameter> GetModulationParameter(const FString& InName) const;`
- L30 _public function_ `virtual FName GetCategoryName() const override`
- L33 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOMODULATION_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationStatics.h` (Public)


#### class `UAudioModulationStatics`  
`class UAudioModulationStatics : public UBlueprintFunctionLibrary`  
_L29-421_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L37 _public prototype_ `static UWorld* GetAudioWorld(const UObject* WorldContextObject);` — Returns world associated with provided context object
- L42 _public prototype_ `static AudioModulation::FAudioModulationManager* GetModulation(UWorld* World);` — Returns modulation implementation associated with the provided world
- L53 _public prototype_ `static void ActivateBus(const UObject* WorldContextObject, USoundControlBus* Bus);` — `UE_DEPRECATED(5.6, "To manually control the activation state of a modulator, use CreateModulationDestination.")` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Activate Control Bus", meta = ( WorldContext = "WorldContextObject", DeprecatedFunction="Note", DeprecationMessage="To manually control the activation state of a modulator, use CreateModulationDestination."))` — Manually activates a modulation bus. If called, deactivation will only occur if bus is manually deactivated or destroyed (i.e. will not deactivate when all references become inactive).
- L64 _public prototype_ `static void ActivateBusMix(const UObject* WorldContextObject, USoundControlBusMix* Mix);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Activate Control Bus Mix", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation modulator"))` — Manually activates a bus modulator mix. If called, deactivation will only occur if mix is manually deactivated and not referenced or destroyed (i.e. will not deactivate when all references become inactive). @param BusMix - Mix to activate
- L76 _public prototype_ `static void ActivateGenerator(const UObject* WorldContextObject, USoundModulationGenerator* Generator);` — `UE_DEPRECATED(5.6, "To manually control the activation state of a modulator, use CreateModulationDestination.")` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Activate Modulation Generator", meta = ( WorldContext = "WorldContextObject", DeprecatedFunction="Note", DeprecationMessage="To manually control the activation state of a modulator, use CreateModulationDestination."))` — Manually activates a modulation generator. If called, deactivation will only occur if generator is manually deactivated and not referenced or destroyed (i.e. will not deactivate when all references become inactive). @param Generator - Generator to activate
- L91 _public prototype_ `static UPARAM(DisplayName = "Bus") USoundControlBus* CreateBus(UObject* WorldContextObject, FName Name, USoundModulationParameter* Parameter, bool Activate = fals` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Create Control Bus", meta = ( AdvancedDisplay = "3", WorldContext = "WorldContextObject", Keywords = "make modulation LPF modulator"))` — Creates a modulation bus with the provided default value. @param Name - Name of bus @param Parameter - Default value for created bus @param Activate - (DEPRECATED in 5.4: Use UAudioModulationDestination) Whether or not to activate bus on creation. If true, deactivation will only occur if returned bus is manually deactivated and not referenced or destroyed (i.e. will not deactivate when all references become inactive). @return ControlBus created.  This should be stored (eg. by a Blueprint as a variable) to prevent it from being garbage collected.
- L104 _public prototype_ `static UPARAM(DisplayName = "Mix") USoundControlBusMix* CreateBusMixFromValue( const UObject* WorldContextObject, FName Name, const TArray<USoundControlBus*>& Buses, float Value = 1.0f, float AttackTime = 0.1f, float ReleaseTime = 0.1f, bool bActivate = true);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", meta = ( AdvancedDisplay = "3", WorldContext = "WorldContextObject", Keywords = "make modulation modulator stage"))` — Create a mix with stages created for each provided bus that are initialized to the supplied value and timing parameters. @param Buses - Buses to assign stages within new mix to @param Value - Initial value for all stages created within the new mix. @param AttackTime - Fade time to user when mix activates. @param ReleaseTime - Fade time to user when mix deactivates.
- L124 _public prototype_ `static UPARAM(DisplayName = "Stage") FSoundControlBusMixStage CreateBusMixStage( const UObject* WorldContextObject, USoundControlBus* Bus, float Value, float AttackTime = 0.1f, float ReleaseTime = 0.1f);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Create Control Bus Mix Stage", meta = ( AdvancedDisplay = "3", WorldContext = "WorldContextObject", Keywords = "make modulation modulator stage"))` — Creates a stage used to mix a control bus. @param Bus - Bus stage is in charge of applying mix value to. @param Value - Value for added bus stage to target when mix is active. @param AttackTime - Time in seconds for stage to mix in. @param ReleaseTime - Time in seconds for stage to mix out.
- L148 _public prototype_ `static UPARAM(DisplayName = "BusMix") USoundControlBusMix* CreateBusMix( UObject* WorldContextObject, FName Name, TArray<FSoundControlBusMixStage> Stages, bool Activate, double Duration = -1.0, bool bRetriggerOnActivation = false);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Create Control Bus Mix", meta = ( WorldContext = "WorldContextObject", AdvancedDisplay = "3", Keywords = "make modulation modulator"))` — Creates a Control Bus Mix with the given stage configuration. @param Name - Name of mix. @param Stages - Stages mix is responsible for. @param Activate - Whether or not to activate mix on creation. If true, deactivation will only occur if returned mix is manually deactivated and not referenced or destroyed (i.e. will not deactivate when all references become inactive). It will also still deactivate based on the Duration value. @param Duration - Amount of time the Mix will stay active for before deactivating itself. When less than 0, the mix will stay active until manually deactivated. @param bRetriggerOnActivation - If true, if this mix is already active when Activate is called, stages will return to their default values before activating. @return Capture this in a Blueprint variable to prevent it from being garbage collected.
- L166 _public prototype_ `static UPARAM(DisplayName = "Parameter") USoundModulationParameter* CreateModulationParameter( UObject* WorldContextObject, FName Name, TSubclassOf<USoundModulationParameter> ParamClass, float DefaultValue);` — `UFUNCTION(Category = "Audio|Modulation", DisplayName = "Create Modulation Parameter", meta = ( WorldContext = "WorldContextObject", Keywords = "make modulator"))` — Creates a modulation parameter of a given class. @param Name - Name of parameter. @param ParamClass - The type of Modulation Parameter to create. @param DefaultValue - The default normalized value of the parameter (range 0-1). @return Capture this in a Blueprint variable to prevent it from being garbage collected.
- L181 _public prototype_ `static UPARAM(DisplayName = "Generator") USoundModulationGeneratorEnvelopeFollower* CreateEnvelopeFollowerGenerator( UObject* WorldContextObject, FName Name, FEnvelopeFollowerGeneratorParams Params);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Create Envelope Follower Generator", meta = ( WorldContext = "WorldContextObject", Keywords = "make modulator"))` — Creates a modulation generator based on an Envelope Follower with the given parameters. @param Name - Name of generator. @param Params - The Envelope Follower settings, including what data to follow. @return Capture this in a Blueprint variable to prevent it from being garbage collected.
- L195 _public prototype_ `static UPARAM(DisplayName = "Generator") USoundModulationGeneratorLFO* CreateLFOGenerator( UObject* WorldContextObject, FName Name, FSoundModulationLFOParams Params);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Create LFO Generator", meta = ( WorldContext = "WorldContextObject", Keywords = "make modulator"))` — Creates a modulation generator based on an LFO with the given parameters. @param Name - Name of generator. @param Params - The LFO Settings. @return Capture this in a Blueprint variable to prevent it from being garbage collected.
- L209 _public prototype_ `static UPARAM(DisplayName = "Generator") USoundModulationGeneratorADEnvelope* CreateADEnvelopeGenerator( UObject* WorldContextObject, FName Name, const FSoundModulationADEnvelopeParams& Params);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Create AD Envelope Generator", meta = ( WorldContext = "WorldContextObject", Keywords = "make modulator"))` — Creates a modulation generator based on an Attack/Decay Envelope. @param Name - Name of generator. @param Params - The AD Envelope Settings. @return Capture this in a Blueprint variable to prevent it from being garbage collected.
- L219 _public prototype_ `static UPARAM(DisplayName = "Destination") UAudioModulationDestination* CreateModulationDestination( UObject* WorldContextObject, FName Name, USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", meta = (WorldContext = "WorldContextObject", Keywords = "modulator watch watcher"))` — Creates a modulation destination, which activates the given modulator (if not already active) and provides a function to retrieve the last value computed of the given modulator on the modulation processing thread.
- L232 _public prototype_ `static void DeactivateBus(const UObject* WorldContextObject, USoundControlBus* Bus);` — `UE_DEPRECATED(5.6, "To manually control the activation state of a modulator, use CreateModulationDestination.")` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Deactivate Control Bus", meta = ( WorldContext = "WorldContextObject", DeprecatedFunction="Note", DeprecationMessage="To manually control the activation state of a modulator, use CreateModulationDestination."))` — Deactivates a bus. Does nothing if the provided bus is already inactive. @param Bus - Scope of modulator
- L241 _public prototype_ `static void DeactivateBusMix(const UObject* WorldContextObject, USoundControlBusMix* Mix);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Deactivate Control Bus Mix", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation modulator"))` — Deactivates a modulation bus mix. Does nothing if an instance of the provided bus mix is already inactive. @param Mix - Mix to deactivate
- L246 _public prototype_ `static void DeactivateBusMixByID(const UObject* WorldContextObject, uint32 MixID);` — Deactivates a modulation bus mix. Does nothing if an instance of the provided bus mix is already inactive. * @param MixID - Mix to deactivate
- L256 _public prototype_ `static void DeactivateGenerator(const UObject* WorldContextObject, USoundModulationGenerator* Generator);` — `UE_DEPRECATED(5.6, "To manually control the activation state of a modulator, use CreateModulationDestination.")` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Deactivate Modulation Generator (Deprecated - 5.4)", meta = ( WorldContext = "WorldContextObject", DeprecatedFunction="Note", DeprecationMessage="To manually control the activation state of a modulator, use CreateModulationDestination."))` — Deactivates a modulation generator. Does nothing if an instance of the provided generator is already inactive. @param Generator - Generator to activate
- L266 _public prototype_ `static UPARAM(DisplayName = "Is Active") bool IsControlBusMixActive(const UObject * WorldContextObject, USoundControlBusMi` — `UFUNCTION(BlueprintPure, Category = "Audio|Modulation", DisplayName = "Is Control Bus Mix Active", meta = ( WorldContext = "WorldContextObject", Keywords = "bus modulation modulator generator"))` — Returns whether or not a Control Bus Mix is currently active. @param Mix - the Control Bus Mix to check. @return Whether or not the Bus Mix is currently active.
- L278 _public prototype_ `static void SaveMixToProfile(const UObject* WorldContextObject, USoundControlBusMix* Mix, int32 ProfileIndex = 0);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Save Control Bus Mix to Profile", meta = ( WorldContext = "WorldContextObject", AdvancedDisplay = "2", Keywords = "serialize modulation modulator ini"))` — Saves control bus mix to a profile, serialized to an ini file.  If mix is loaded, uses current proxy's state. If not, uses default UObject representation. @param Mix - Mix object to serialize to profile .ini. @param ProfileIndex - Index of profile, allowing multiple profiles can be saved for single mix object. If 0, saves to default ini profile (no suffix).
- L291 _public prototype_ `static UPARAM(DisplayName = "Stages") TArray<FSoundControlBusMixStage> LoadMixFromProfile(const UObject* WorldContextObject, USoundControlBusMix* Mix, bool bActivate = true, int32 ProfileIndex` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Load Control Bus Mix From Profile", meta = ( WorldContext = "WorldContextObject", AdvancedDisplay = "2", Keywords = "deserialize modulation modulator ini"))` — Loads control bus mix from a profile into UObject mix definition, deserialized from an ini file. @param Mix - Mix object to deserialize profile .ini to. @param bActivate - If true, activate mix upon loading from profile. @param ProfileIndex - Index of profile, allowing multiple profiles to be loaded to single mix object. If <= 0, loads from default profile (no suffix). @return Stages - Stage values loaded from profile (empty if profile did not exist or had no values serialized).
- L312 _public prototype_ `static void UpdateMix(const UObject* WorldContextObject, USoundControlBusMix* Mix, TArray<FSoundControlBusMixStage> Stages, float FadeTime = -1.0f, double Duration = -1.0, bool bRetriggerOnActivation = false);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Set Control Bus Mix", meta = ( WorldContext = "WorldContextObject", AdvancedDisplay = "3", Keywords = "modulation modulator stage"))` — Sets a Control Bus Mix with the provided stage data, if the stages are provided in an active instance proxy of the mix. Does not update UObject definition of the mix. @param Mix - Mix to update @param Stages - Stages to set.  If stage's bus is not referenced by mix, stage's update request is ignored. @param FadeTime - Fade time to user when interpolating between current value and new values. If negative, falls back to last fade time set on stage. If fade time never set on stage, uses attack time set on stage in mix asset. @param Duration - Amount of time the Mix is activated for. When the Mix has been active for the given time, automatically deactivates itself. When less than 0, the duration is infinite (i.e. mix will stay active until manually deactivated). @param bRetriggerOnActivation - If true, if this mix is already active when Activate is called, stages will return to their default values before activating.
- L326 _public prototype_ `static void SetGlobalBusMixValue(const UObject* WorldContextObject, USoundControlBus* Bus, float Value, float FadeTime = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Set Global Control Bus Mix Value", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation modulator stage"))` — Sets a Global Control Bus Mix with a single stage associated with the provided Bus to the given float value.  This call should be reserved for buses that are to be always active. It is *NOT* recommended for transient buses, as not calling clear can keep buses active indefinitely. @param Bus - Bus associated with mix to update @param Value - Value to set global stage to. @param FadeTime - Fade time to user when interpolating between current value and new value. If negative, falls back to last fade time set on stage. If fade time never set on stage, defaults to 100ms.
- L337 _public prototype_ `static void ClearGlobalBusMixValue(const UObject* WorldContextObject, USoundControlBus* Bus, float FadeTime = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Clear Global Control Bus Mix Value", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation modulator stage"))` — Clears global control bus mix if set, using the applied fade time to return to the provided bus's parameter default value. @param Bus - Bus associated with mix to update @param FadeTime - Fade time to user when interpolating between current value and new values. If non-positive, change is immediate.
- L347 _public prototype_ `static void ClearAllGlobalBusMixValues(const UObject* WorldContextObject, float FadeTime = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Clear All Global Control Bus Mix Values", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation modulator stage"))` — Clears all global control bus mix values if set, using the applied fade time to return all to their respective bus's parameter default value. @param FadeTime - Fade time to user when interpolating between current value and new values. If non-positive, change is immediate.
- L355 _public prototype_ `static void DeactivateAllBusMixes(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Deactivate All Control Bus Mixes", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation modulator stage"))` — Deactivates all currently active Control Bus Mixes. This includes the Global Control Bus Mixes.
- L371 _public prototype_ `static void UpdateMixByFilter( const UObject* WorldContextObject, USoundControlBusMix* Mix, FString AddressFilter, TSubclassOf<USoundModulationParameter> ParamClassFilter, USoundModulationParameter* ParamFilter, float Value = 1.0f, float FadeTime = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Set Control Bus Mix By Filter", meta = ( AdvancedDisplay = "6", WorldContext = "WorldContextObject", Keywords = "control class modulation modulator stage value"))` — Sets filtered stages of a given class to a provided target value for active instance of mix. Does not update UObject definition of mix. @param Mix - Mix to modify @param AddressFilter - (Optional) Address filter to apply to provided mix's stages. @param ParamClassFilter - (Optional) Filters buses by parameter class. @param ParamFilter - (Optional) Filters buses by parameter. @param Value - Target value to mix filtered stages to. @param FadeTime - If non-negative, updates the fade time for the resulting bus stages found matching the provided filter.
- L391 _public prototype_ `static void UpdateMixFromObject(const UObject* WorldContextObject, USoundControlBusMix* Mix, float FadeTime = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Update Control Bus Mix", meta = ( WorldContext = "WorldContextObject", Keywords = "set modulation modulator"))` — Commits updates from a UObject definition of a bus mix to active instance in audio thread (ignored if mix has not been activated). @param Mix - Mix to update @param FadeTime - Fade time to user when interpolating between current value and new values. If negative, falls back to last fade time set on stage. If fade time never set on stage, uses attack time set on stage in mix asset.
- L401 _public prototype_ `static void UpdateModulator(const UObject* WorldContextObject, USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation", DisplayName = "Update Modulator", meta = ( WorldContext = "WorldContextObject", Keywords = "set control bus mix modulation modulator generator"))` — Commits updates from a UObject definition of a modulator (e.g. Bus, Bus Mix, Generator) to active instance in audio thread (ignored if modulator type has not been activated). @param Modulator - Modulator to update
- L410 _public prototype_ `static UPARAM(DisplayName = "Value") float GetModulatorValue(const UObject* WorldContextObject, USoundModulatorBase* Modula` — `UFUNCTION(BlueprintPure, Category = "Audio|Modulation", DisplayName = "Get Modulator Value", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation generator bus"))` — Gets the (normalized) value of the given modulator. @return Value - The current value of the modulator. If the modulator is not active, returns 1.0.
- L420 _public prototype_ `static UPARAM(DisplayName = "Modulators") TSet<USoundModulatorBase*> GetModulatorsFromDestination(const FSoundModulationDestinationSettings& Des` — `UFUNCTION(BlueprintPure, Category = "Audio|Modulation", DisplayName = "Get Modulators From Destination", meta = ( WorldContext = "WorldContextObject", Keywords = "modulation generator bus"))` — Gets the list of modulators currently applied to a Modulation Destination. @param Destination - The Modulation Destination. @return Modulators - The set of Modulators.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AUDIOMODULATION_API`
- L21 _namespace_ `namespace AudioModulation`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationStyle.h` (Public)


#### class `UAudioModulationStyle`  
`class UAudioModulationStyle : public UBlueprintFunctionLibrary`  
_L11-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public function_ `static const FColor GetModulationGeneratorColor()` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation|Style")`
- L20 _public function_ `static const FColor GetControlBusColor()` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation|Style")`
- L23 _public function_ `static const FColor GetControlBusMixColor()` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation|Style")`
- L26 _public function_ `static const FColor GetPatchColor()` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation|Style")`
- L29 _public function_ `static const FColor GetParameterColor()` — `UFUNCTION(BlueprintCallable, Category = "Audio|Modulation|Style")`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationSubsystem.h` (Public)


#### class `UAudioModulationSubsystem`  
`class UAudioModulationSubsystem : public UAudioEngineSubsystem`  
_L15-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioEngineSubsystem`
- desc: UAudioModulationSubsystem
- L20 _public prototype_ `UAudioModulationSubsystem() = default;`
- L21 _public prototype_ `virtual ~UAudioModulationSubsystem() override = default;`
- L24 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L25 _public prototype_ `virtual void Deinitialize() override;`
- L29 _public prototype_ `void SetModulationParameterClampOverride(const FString& ParameterName, bool bClamp) const;` — Modulation Parameter Overrides
- L30 _public prototype_ `void ClearModulationParameterClampOverride(const FString& ParameterName) const;`
- L31 _public prototype_ `void ClearAllModulationParameterClampOverrides() const;`
- L34 _private member_ `TMap<FString, bool> ModulationParameterClampOverrides;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOMODULATION_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationTrace.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Audio`
- L6 _namespace_ `namespace Modulation` (scope `Audio`)
- L6 _namespace_ `namespace Trace` (scope `Audio::Modulation`)
- L6 _namespace_ `namespace EventLog` (scope `Audio::Modulation::Trace`)
- L6 _namespace_ `namespace ID` (scope `Audio::Modulation::Trace::EventLog`)
- L8 _externvar_ `extern const FString ModulatorActivated;` (scope `Audio::Modulation::Trace::EventLog::ID`)
- L9 _externvar_ `extern const FString ModulatorDeactivated;` (scope `Audio::Modulation::Trace::EventLog::ID`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/Generators/SoundModulationADEnvelope.h` (Public)


#### struct `FSoundModulationADEnvelopeParams`  
`struct FSoundModulationADEnvelopeParams`  
_L14-41_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `float AttackTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 20, EditCondition = "!bBypass", UIMin = "0", ClampMin = "0"))` — Attack time of the envelope (seconds).
- L24 _public member_ `float DecayTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 30, EditCondition = "!bBypass", UIMin = "0", ClampMin = "0"))` — Decay time of the envelope (seconds).
- L28 _public member_ `float AttackCurve = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 40, EditCondition = "!bBypass", UIMin = "0", ClampMin = "0"))` — The exponential curve factor of the attack. 1.0 = linear growth, < 1.0 logorithmic growth, > 1.0 exponential growth.
- L32 _public member_ `float DecayCurve = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 50, EditCondition = "!bBypass", UIMin = "0", ClampMin = "0"))` — The exponential curve factor of the decay. 1.0 = linear decay, < 1.0 exponential decay, > 1.0 logarithmic decay.
- L36 _public member_ `bool bLooping = true;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 60, EditCondition = "!bBypass"))` — Whether or not to loop the envelope.
- L40 _public member_ `bool bBypass = false;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 10))` — If true, bypasses envelope bus from being modulated by parameters, patches, or mixed (Envelope remains active and computed).

#### class `USoundModulationGeneratorADEnvelope`  
`class USoundModulationGeneratorADEnvelope : public USoundModulationGenerator`  
_L45-54_
- reflection: `UCLASS(BlueprintType, hidecategories = Object, editinlinenew, MinimalAPI)`
- inherits: `USoundModulationGenerator`
- L51 _public member_ `FSoundModulationADEnvelopeParams Params;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))`
- L53 _public prototype_ `virtual AudioModulation::FGeneratorPtr CreateInstance() const override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/Generators/SoundModulationEnvelopeFollower.h` (Public)


#### struct `FEnvelopeFollowerGeneratorParams`  
`struct FEnvelopeFollowerGeneratorParams`  
_L26-53_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public member_ `bool bBypass = false;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite)` — If true, bypasses generator from being modulated by parameters, patches, or mixed (remains active and computed).
- L36 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (EditCondition = "!bBypass", DisplayAfter = "ReleaseTime"))` — If true, inverts output
- L40 _public member_ `TObjectPtr<UAudioBus> AudioBus = nullptr;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (EditCondition = "!bBypass"))` — AudioBus to follow amplitude of and generate modulation control signal from.
- L44 _public member_ `float Gain = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (EditCondition = "!bBypass", ClampMin = 0.0f))` — Gain to apply to amplitude signal.
- L48 _public member_ `float AttackTime = 0.010f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (EditCondition = "!bBypass", ClampMin = 0.0f))` — Attack time of envelope response (in sec)
- L52 _public member_ `float ReleaseTime = 0.100f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (EditCondition = "!bBypass", ClampMin = 0.0f))` — Release time of envelope response (in sec)

#### class `USoundModulationGeneratorEnvelopeFollower`  
`class USoundModulationGeneratorEnvelopeFollower : public USoundModulationGenerator`  
_L56-65_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object, BlueprintType, editinlinenew, meta = (DisplayName = "Envelope Follower Generator"))`
- inherits: `USoundModulationGenerator`
- L62 _public member_ `FEnvelopeFollowerGeneratorParams Params;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))`
- L64 _public prototype_ `virtual AudioModulation::FGeneratorPtr CreateInstance() const override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API AUDIOMODULATION_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/Generators/SoundModulationLFO.h` (Public)


#### enum `ESoundModulationLFOShape`  
`enum class ESoundModulationLFOShape : uint8`  
_L16-27_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Sine UMETA(DisplayName = "Sine")`
- L19 _public enumerator_ `UpSaw UMETA(DisplayName = "Saw (Up)")`
- L20 _public enumerator_ `DownSaw UMETA(DisplayName = "Saw (Down)")`
- L21 _public enumerator_ `Square UMETA(DisplayName = "Square")`
- L22 _public enumerator_ `Triangle UMETA(DisplayName = "Triangle")`
- L23 _public enumerator_ `Exponential UMETA(DisplayName = "Exponential")`
- L24 _public enumerator_ `RandomSampleHold UMETA(DisplayName = "Random")`
- L26 _public enumerator_ `COUNT UMETA(Hidden)`

#### struct `FSoundModulationLFOParams`  
`struct FSoundModulationLFOParams`  
_L30-69_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public member_ `ESoundModulationLFOShape Shape = ESoundModulationLFOShape::Sine;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 20, EditCondition = "!bBypass"))` — Shape of oscillating waveform
- L40 _public member_ `float ExponentialFactor = 3.5f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 21, EditCondition = "!bBypass && Shape == ESoundModulationLFOShape::Exponential", EditConditionHides, ClampMin = "0.000001", UIMin = "0.25", UIMax = "10.0"))` — Factor increasing/decreasing curvature of exponential LFO shape.
- L44 _public member_ `float Width = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 21, EditCondition = "!bBypass && Shape == ESoundModulationLFOShape::Square", EditConditionHides, ClampMin = "0.0", ClampMax = "1.0"))` — Pulse width of square LFO shape.
- L48 _public member_ `float Amplitude = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 30, EditCondition = "!bBypass", UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Amplitude of oscillator
- L52 _public member_ `float Frequency = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 40, EditCondition = "!bBypass", UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "20"))` — Frequency of oscillator
- L56 _public member_ `float Offset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 50, EditCondition = "!bBypass", UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Amplitude offset of oscillator
- L60 _public member_ `float Phase = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 60, EditCondition = "!bBypass", UIMin = "0", UIMax = "1", ClampMin = "0"))` — Unit phase offset of oscillator
- L64 _public member_ `bool bLooping = true;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 70, EditCondition = "!bBypass"))` — Whether or not to loop the oscillation more than once
- L68 _public member_ `bool bBypass = false;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayPriority = 10))` — If true, bypasses LFO bus from being modulated by parameters, patches, or mixed (LFO remains active and computed).

#### class `USoundModulationGeneratorLFO`  
`class USoundModulationGeneratorLFO : public USoundModulationGenerator`  
_L73-82_
- reflection: `UCLASS(BlueprintType, hidecategories = Object, editinlinenew, MinimalAPI)`
- inherits: `USoundModulationGenerator`
- L79 _public member_ `FSoundModulationLFOParams Params;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))`
- L81 _public prototype_ `virtual AudioModulation::FGeneratorPtr CreateInstance() const override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/IAudioModulationDebugDataProvider.h` (Public)


#### struct `AudioModulation::FControlBusMixStageDebugInfo`  
`struct FControlBusMixStageDebugInfo`  
_L21-25_
- L23 _public member_ `float TargetValue;`
- L24 _public member_ `float CurrentValue;`

#### struct `AudioModulation::FControlBusMixDebugInfo`  
`struct FControlBusMixDebugInfo`  
_L27-41_
- L29 _public member_ `FString Name;`
- L30 _public member_ `uint32 Id = -1;`
- L31 _public member_ `uint32 RefCount = 0;`
- L32 _public member_ `bool bIsGlobal = false;`
- L33 _public member_ `double Timer = -1.0;`
- L35 _public member_ `TMap<uint32, FControlBusMixStageDebugInfo> Stages;`
- L37 _public function_ `bool operator==(const FControlBusMixDebugInfo& Other) const`

#### struct `AudioModulation::FControlBusDebugInfo`  
`struct FControlBusDebugInfo`  
_L48-63_
- L50 _public member_ `FString Name;`
- L51 _public member_ `FString ParameterName;`
- L52 _public member_ `float DefaultValue;`
- L53 _public member_ `float GeneratorValue;`
- L54 _public member_ `float MixValue;`
- L55 _public member_ `float Value;`
- L56 _public member_ `uint32 Id;`
- L57 _public member_ `uint32 RefCount;`
- L59 _public function_ `bool operator==(const FControlBusDebugInfo& Other) const`

#### class `AudioModulation::IDebugDataProvider`  
`class IDebugDataProvider : public IModularFeature`  
_L71-77_
- inherits: `IModularFeature`
- L74 _public prototype_ `virtual Audio::FDeviceId GetAssociatedDeviceID() = 0;`
- L75 _public prototype_ `virtual void GetControlBusDebugInfo(TArray<FControlBusDebugInfo>& OutDebugInfo);`
- L76 _public prototype_ `virtual void GetControlBusMixDebugInfo(TArray<FControlBusMixDebugInfo>& OutDebugInfo);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOMODULATION_API`
- L17 _namespace_ `namespace AudioModulation`
- L19 _variable_ `constexpr FLazyName DebugDataModularFeatureName = "Au` (scope `AudioModulation`)
- L43 _function_ `FORCEINLINE uint32 GetTypeHash(const FControlBusMixDebugInfo& DebugInfo)` (scope `AudioModulation`)
- L65 _function_ `FORCEINLINE uint32 GetTypeHash(const FControlBusDebugInfo& DebugInfo)` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/MovieSceneAudioControlBusMixSection.h` (Public)


#### class `UMovieSceneAudioControlBusMixSection`  
`class UMovieSceneAudioControlBusMixSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L16-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L24 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L25 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L27 _public prototype_ `void SetMixBus(USoundControlBusMix* NewMixBus);`
- L30 _public member_ `FMovieSceneBoolChannel BusValue;` — `UPROPERTY()`
- L33 _public member_ `TObjectPtr<USoundControlBusMix> MixBus;` — `UPROPERTY()`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/MovieSceneAudioControlBusMixTrack.h` (Public)


#### class `UMovieSceneAudioControlBusMixTrack`  
`class UMovieSceneAudioControlBusMixTrack : public UMovieSceneNameableTrack`  
_L14-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- L20 _public prototype_ `UMovieSceneSection* AddNewControlBusMix(USoundControlBusMix* BusMix);`
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L25 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L26 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L27 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L28 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L29 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L30 _public prototype_ `virtual bool IsEmpty() const override;`
- L31 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L32 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L33 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L35 _public prototype_ `virtual void GetCompatibleUserDecorationsImpl(TSet<UClass*>& OutClasses) const override;`
- L38 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L45 _private prototype_ `virtual void PostLoad() override;`
- L50 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> MixSections;` — `UPROPERTY()` — List of all root mix bus sections

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/MovieSceneAudioControlBusSection.h` (Public)


#### class `UMovieSceneAudioControlBusSection`  
`class UMovieSceneAudioControlBusSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L16-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L24 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L25 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L28 _public prototype_ `void SetBus(USoundControlBus* NewBus);`
- L31 _public member_ `FMovieSceneFloatChannel BusValue;` — `UPROPERTY()`
- L34 _public member_ `TObjectPtr<USoundControlBus> ControlBus;` — `UPROPERTY()`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/MovieSceneAudioControlBusTrack.h` (Public)


#### class `UMovieSceneAudioControlBusTrack`  
`class UMovieSceneAudioControlBusTrack : public UMovieSceneNameableTrack`  
_L14-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- L21 _public prototype_ `UMovieSceneSection* AddNewControlBus(USoundControlBus* Bus);`
- L25 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L26 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L27 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L28 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L29 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L30 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L31 _public prototype_ `virtual bool IsEmpty() const override;`
- L32 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L33 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L34 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L36 _public prototype_ `virtual void GetCompatibleUserDecorationsImpl(TSet<UClass*>& OutClasses) const override;`
- L39 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L46 _private prototype_ `virtual void PostLoad() override;`
- L51 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> AudioSections;` — `UPROPERTY()` — List of all root audio sections

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/MovieSceneAudioModulationComponentTypes.h` (Public)


#### struct `FMovieSceneAudioControlBusComponentData`  
`struct FMovieSceneAudioControlBusComponentData`  
_L13-19_
- reflection: `USTRUCT()`
- desc: Component data for control bus tracks
- L18 _public member_ `TObjectPtr<UMovieSceneAudioControlBusSection> Section = nullptr;` — `UPROPERTY()`

#### struct `FMovieSceneAudioControlBusMixComponentData`  
`struct FMovieSceneAudioControlBusMixComponentData`  
_L23-29_
- reflection: `USTRUCT()`
- desc: Component data for control bus mix tracks
- L28 _public member_ `TObjectPtr<UMovieSceneAudioControlBusMixSection> Section = nullptr;` — `UPROPERTY()`

#### struct `FMovieSceneAudioModulationComponentTypes`  
`struct FMovieSceneAudioModulationComponentTypes`  
_L31-44_
- L34 _public prototype_ `~FMovieSceneAudioModulationComponentTypes();`
- L36 _public prototype_ `static FMovieSceneAudioModulationComponentTypes* Get();`
- L37 _public prototype_ `static void Destroy();`
- L39 _public member_ `UE::MovieScene::TComponentTypeID<FMovieSceneAudioControlBusComponentData> AudioControlBus;`
- L40 _public member_ `UE::MovieScene::TComponentTypeID<FMovieSceneAudioControlBusMixComponentData> AudioControlBusMix;`
- L43 _private prototype_ `FMovieSceneAudioModulationComponentTypes();`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundControlBus.h` (Public)


#### class `USoundControlBus`  
`class USoundControlBus : public USoundModulatorBase`  
_L24-73_
- reflection: `UCLASS(BlueprintType, hidecategories = Object, editinlinenew, MinimalAPI)`
- inherits: `USoundModulatorBase`
- L31 _public member_ `bool bBypass;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadWrite)` — If true, bypasses control bus from being modulated by parameters, patches, or mixed (control bus remains active and computed).
- L36 _public member_ `bool bOverrideAddress;` — `UPROPERTY(EditAnywhere, Category = "Advanced|Mix", BlueprintReadWrite)` — If true, Address field is used in place of object name for address used when applying mix changes using filtering.
- L39 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category = General, meta=(MultiLine=true))`
- L44 _public member_ `FString Address;` — `UPROPERTY(EditAnywhere, Category = "Advanced|Mix", BlueprintReadWrite, meta = (EditCondition = "bOverrideAddress"))` — Address to use when applying mix changes.
- L48 _public member_ `TArray<TObjectPtr<USoundModulationGenerator>> Generators;` — `UPROPERTY(EditAnywhere, Category = "Advanced|Generators", BlueprintReadWrite)` — The Modulation Generators which modulate this Control Bus.
- L52 _public member_ `TObjectPtr<USoundModulationParameter> Parameter;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly)` — The Modulation Parameter to use with this Control Bus. This determines how the control bus will be mixed with other modulators as well as its unit range.
- L56 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L57 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L58 _public prototype_ `virtual void PostInitProperties() override;`
- L59 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L62 _public prototype_ `virtual void BeginDestroy() override;`
- L65 _public prototype_ `virtual TUniquePtr<Audio::IModulatorSettings> CreateProxySettings() const override;` — USoundModulatorBase Implementation
- L66 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L67 _public prototype_ `virtual const Audio::FModulationParameter& GetOutputParameter() const override;`
- L69 _public prototype_ `const Audio::FModulationMixFunction GetMixFunction() const;`
- L71 _public function_ `float GetDefaultNormalizedValue() const`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundControlBusMix.h` (Public)


#### struct `FSoundControlBusMixStage`  
`struct FSoundControlBusMixStage`  
_L20-34_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public prototype_ `FSoundControlBusMixStage();`
- L25 _public prototype_ `FSoundControlBusMixStage(USoundControlBus* InBus, const float TargetValue);`
- L29 _public member_ `TObjectPtr<USoundControlBus> Bus;` — `UPROPERTY(EditAnywhere, Category = Stage, BlueprintReadWrite)` — Bus controlled by the mix stage.
- L33 _public member_ `FSoundModulationMixValue Value;` — `UPROPERTY(EditAnywhere, Category = Stage, BlueprintReadWrite)` — Value mix is set to.

#### class `USoundControlBusMix`  
`class USoundControlBusMix : public UObject`  
_L37-98_
- reflection: `UCLASS(config = Engine, autoexpandcategories = (Stage, Mix), editinlinenew, BlueprintType, MinimalAPI, meta = (PrioritizeCategories = "Mix Config Stages"))`
- inherits: `UObject`
- L44 _protected prototype_ `void LoadMixFromProfile();` — `UFUNCTION(Category = Mix, meta = (CallInEditor = "true", DisplayPriority = "50"))` — Loads the mix from the provided profile index
- L48 _protected prototype_ `void SaveMixToProfile();` — `UFUNCTION(Category = Mix, meta = (CallInEditor = "true", DisplayPriority = "60"))` — Saves the mix to the provided profile index
- L54 _protected prototype_ `void SoloMix();` — `UFUNCTION(Category = Mix, meta = (CallInEditor = "true", DisplayPriority = "40"))` — Solos this mix, deactivating all others and activating this (if its not already active), while testing in-editor in all active worlds
- L58 _protected prototype_ `void ActivateMix();` — `UFUNCTION(Category = Mix, meta = (CallInEditor = "true", DisplayPriority = "10"))` — Activates this mix in all active worlds.
- L62 _protected prototype_ `void DeactivateMix();` — `UFUNCTION(Category = Mix, meta = (CallInEditor = "true", DisplayPriority = "20"))` — Deactivates this mix in all active worlds. The mix is fully deactivated once all stages have finished their release times.
- L66 _protected prototype_ `void DeactivateAllMixes();` — `UFUNCTION(Category = Mix, meta = (CallInEditor = "true", DisplayPriority = "30"))` — Deactivates all mixes in all active worlds
- L70 _public member_ `uint32 ProfileIndex = 0;` — `UPROPERTY(EditAnywhere, Transient, Category = Config, meta = (DisplayPriority = "30"))`
- L78 _public member_ `double Duration = -1.0;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (DisplayPriority = "10"), BlueprintReadOnly)` — Once activated, the mix will start a timer for the given duration (seconds). When the timer ends, the mix will be deactivated. As a result, the attack time is included in this duration, but not the release time. When set to 0, the mix is activated and then immediately deactivated. If less than 0, the mix will remain activated until manually deactivated.
- L85 _public member_ `bool bRetriggerOnActivation = false;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (DisplayPriority = "20"), BlueprintReadOnly)` — If a Mix is already active and you activate it again, one of two things will happen: If set to true, the stages will all go back to their default values and the mix will activate again, allowing the attack to trigger again. If set to false, calling activate will only reset the timer to deactivate (based on the Duration value).
- L87 _public prototype_ `virtual void BeginDestroy() override;`
- L90 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L91 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L92 _public prototype_ `virtual void OnPropertyChanged(FProperty* Property, EPropertyChangeType::Type ChangeType);`
- L97 _public member_ `TArray<FSoundControlBusMixStage> MixStages;` — `UPROPERTY(EditAnywhere, Category = Stages, BlueprintReadOnly)` — Array of stages controlled by mix.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOMODULATION_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundModulationGenerator.h` (Public)


#### class `AudioModulation::IGeneratorFixLayout`  
`class IGeneratorFixLayout`  
_L25-29_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L28 _public prototype_ `virtual ~IGeneratorFixLayout() = default;`

#### class `AudioModulation::IGenerator`  
`class IGenerator : public IGeneratorFixLayout`  
_L31-78_
- inherits: `IGeneratorFixLayout`
- L34 _public prototype_ `virtual ~IGenerator() = default;`
- L37 _public prototype_ `void PumpCommands();` — Pumps commands from Audio Thread to the generator's modulation processing thread.
- L40 _public prototype_ `virtual FGeneratorPtr Clone() const = 0;` — Clone the generator
- L48 _public prototype_ `virtual void UpdateGenerator(FGeneratorPtr&& InGenerator) = 0;` — Allows child generator class to override default copy/update behavior when receiving an updated generator call from the audio thread. Useful for ignoring updates while a generator is running or deferring the transition to the new generator state to the modulation processing thread.  This enables interpolating between existing and new generator state, properties, avoiding discontinuities, etc. @param InGenerator - The constructed version of the generator being sent from the Audio Thread
- L51 _public prototype_ `virtual float GetValue() const = 0;` — Returns current value of the generator.
- L54 _public function_ `virtual void Init(Audio::FDeviceId InDeviceId)` — (Optional) Initializer step where the generator is provided the associated parent AudioDevice's Id.
- L57 _public prototype_ `virtual bool IsBypassed() const = 0;` — Returns whether or not the generator is bypassed.
- L60 _public prototype_ `virtual void Update(double InElapsed) = 0;` — Updates the generators value at the audio block rate on the modulation processing thread.
- L63 _public prototype_ `virtual void GetDebugValues(TArray<FString>& OutDebugValues) const = 0;`
- L65 _public prototype_ `virtual void GetDebugCategories(TArray<FString>& OutDebugCategories) const = 0;`
- L68 _public prototype_ `virtual const FString& GetDebugName() const = 0;` — Required for instance look-up in factory registration
- L72 _protected prototype_ `void AudioRenderThreadCommand(TUniqueFunction<void()>&& InCommand);`
- L74 _protected member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L77 _private member_ `TQueue<TUniqueFunction<void()>> CommandQueue;`

#### class `USoundModulationGenerator`  
`class USoundModulationGenerator : public USoundModulatorBase`  
_L86-106_
- reflection: `UCLASS(MinimalAPI, hideCategories = Object, abstract)`
- inherits: `USoundModulatorBase`
- desc: Base class for modulators that algorithmically generate values that can effect various endpoints (ex. Control Buses & Parameter Destinations)
- L92 _public function_ `virtual AudioModulation::FGeneratorPtr CreateInstance() const` — Create and return pointer to new instance of generator to be processed on the AudioRenderThread.
- L98 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;` — USoundModulatorBase Implementation
- L99 _public prototype_ `virtual TUniquePtr<Audio::IModulatorSettings> CreateProxySettings() const override;`
- L102 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L105 _public prototype_ `virtual void BeginDestroy() override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AUDIOMODULATION_API`
- L19 _namespace_ `namespace AudioModulation`
- L22 _typedef_ `using FGeneratorPtr = TUniquePtr<IGenerator>;` (scope `AudioModulation`)

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundModulationParameter.h` (Public)


#### struct `FSoundModulationParameterSettings`  
`struct FSoundModulationParameterSettings`  
_L17-46_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `float ValueNormalized = 1.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Default value of modulator (unitless)
- L27 _public member_ `bool bClampToNormalizedRange = true;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly, meta = (EditCondition = "bShowClampOption"))` — Whether or not to clamp values using this parameter to the normalized [0,1] range.
- L32 _public member_ `FText UnitDisplayName;` — `UPROPERTY(EditAnywhere, Category = General)` — (Optional) Text name of parameter's unit
- L41 _public member_ `float ValueUnit = 1.0f;` — `UPROPERTY(Transient, EditAnywhere, Category = General)` — Default value of the modulator. To ensure bypass functionality of mixing, patching, and modulating functions as anticipated, value should be selected such that GetMixFunction (see USoundModulationParameter) reduces to an identity function (i.e. function acts as a "pass-through" for all values in the range [0.0, 1.0]). That is to say, this should be set to the value which has no effect on the sound.
- L44 _public member_ `bool bShowClampOption = false;` — `UPROPERTY()`

#### class `USoundModulationParameter`  
`class USoundModulationParameter : public UObject, public IAudioProxyDataFactory`  
_L49-136_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IAudioProxyDataFactory`
- L55 _public member_ `FSoundModulationParameterSettings Settings;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly, meta = (DisplayName = "Parameter"))`
- L59 _public function_ `virtual bool RequiresUnitConversion() const` — Whether or not the parameter requires a unit conversion.
- L65 _public function_ `virtual Audio::FModulationMixFunction GetMixFunction() const` — Function used to mix modulator units together
- L71 _public function_ `virtual Audio::FModulationNormalizedConversionFunction GetUnitConversionFunction() const` — Function used to convert normalized, unitless value to unit value
- L77 _public function_ `virtual Audio::FModulationNormalizedConversionFunction GetNormalizedConversionFunction() const` — Function used to convert unit value to normalized, unitless value
- L83 _public function_ `virtual float ConvertNormalizedToUnit(float InNormalizedValue) const final` — Converts normalized, unitless value [0.0f, 1.0f] to unit value.
- L91 _public function_ `virtual float ConvertUnitToNormalized(float InUnitValue) const final` — Converts unit value to unitless, normalized value [0.0f, 1.0f].
- L99 _public function_ `virtual float GetUnitDefault() const final` — Returns default unit value (works with and without editor loaded)
- L104 _public function_ `virtual float GetUnitMin() const`
- L109 _public function_ `virtual float GetUnitMax() const`
- L117 _public function_ `virtual TRange<float> GetNormalizedLimits() const` — Returns the range to use when FSoundModulationParameterSettings::bClampToNormalizedRange is set to false. If overriden, the Unit/Normalized conversion functions must be written in a way to account for this range. Returned range is unitless/"normalized".
- L123 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L127 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L129 _public prototype_ `void RefreshNormalizedValue();`
- L130 _public prototype_ `void RefreshUnitValue();`
- L133 _public prototype_ `Audio::FModulationParameter CreateParameter() const;`
- L135 _public prototype_ `bool IsModulationParameterClamped() const;`

#### class `USoundModulationParameterScaled`  
`class USoundModulationParameterScaled : public USoundModulationParameter`  
_L140-158_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameter`
- desc: Linearly scaled value between unit minimum and maximum.
- L147 _public member_ `float UnitMin = 0.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly)` — Unit minimum of modulator. Minimum is only enforced at modulation destination.
- L151 _public member_ `float UnitMax = 1.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly)` — Unit maximum of modulator. Maximum is only enforced at modulation destination.
- L153 _public prototype_ `virtual bool RequiresUnitConversion() const override;`
- L154 _public prototype_ `virtual Audio::FModulationUnitConversionFunction GetUnitConversionFunction() const override;`
- L155 _public prototype_ `virtual Audio::FModulationNormalizedConversionFunction GetNormalizedConversionFunction() const override;`
- L156 _public prototype_ `virtual float GetUnitMin() const override;`
- L157 _public prototype_ `virtual float GetUnitMax() const override;`

#### class `USoundModulationParameterFrequencyBase`  
`class USoundModulationParameterFrequencyBase : public USoundModulationParameter`  
_L162-170_
- reflection: `UCLASS(BlueprintType, MinimalAPI, abstract)`
- inherits: `USoundModulationParameter`
- desc: Modulation Parameter that scales normalized, unitless value to logarithmic frequency unit space.
- L167 _public prototype_ `virtual bool RequiresUnitConversion() const override;`
- L168 _public prototype_ `virtual Audio::FModulationUnitConversionFunction GetUnitConversionFunction() const override;`
- L169 _public prototype_ `virtual Audio::FModulationNormalizedConversionFunction GetNormalizedConversionFunction() const override;`

#### class `USoundModulationParameterFrequency`  
`class USoundModulationParameterFrequency : public USoundModulationParameterFrequencyBase`  
_L174-196_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameterFrequencyBase`
- desc: Modulation Parameter that scales normalized, unitless value to logarithmic frequency unit space with provided minimum and maximum.
- L181 _public member_ `float UnitMin = MIN_FILTER_FREQUENCY;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly)` — Unit minimum of modulator. Minimum is only enforced at modulation destination.
- L185 _public member_ `float UnitMax = MAX_FILTER_FREQUENCY;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly)` — Unit maximum of modulator. Maximum is only enforced at modulation destination.
- L187 _public function_ `virtual float GetUnitMin() const override`
- L192 _public function_ `virtual float GetUnitMax() const override`

#### class `USoundModulationParameterFilterFrequency`  
`class USoundModulationParameterFilterFrequency : public USoundModulationParameterFrequencyBase`  
_L200-214_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameterFrequencyBase`
- desc: Modulation Parameter that scales normalized, unitless value to logarithmic frequency unit space with standard filter min and max frequency set.
- L205 _public function_ `virtual float GetUnitMin() const override`
- L210 _public function_ `virtual float GetUnitMax() const override`

#### class `USoundModulationParameterLPFFrequency`  
`class USoundModulationParameterLPFFrequency : public USoundModulationParameterFilterFrequency`  
_L219-226_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameterFilterFrequency`
- desc: Modulation Parameter that scales normalized, unitless value to logarithmic frequency unit space with standard filter min and max frequency set. Mixes by taking the minimum (i.e. aggressive) filter frequency of all active modulators.
- L224 _public prototype_ `virtual Audio::FModulationMixFunction GetMixFunction() const override;`
- L225 _public prototype_ `static Audio::FModulationParameter CreateDefaultParameter();`

#### class `USoundModulationParameterHPFFrequency`  
`class USoundModulationParameterHPFFrequency : public USoundModulationParameterFilterFrequency`  
_L231-238_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameterFilterFrequency`
- desc: Modulation Parameter that scales normalized, unitless value to logarithmic frequency unit space with standard filter min and max frequency set. Mixes by taking the maximum (i.e. aggressive) filter frequency of all active modulators.
- L236 _public prototype_ `virtual Audio::FModulationMixFunction GetMixFunction() const override;`
- L237 _public prototype_ `static Audio::FModulationParameter CreateDefaultParameter();`

#### class `USoundModulationParameterBipolar`  
`class USoundModulationParameterBipolar : public USoundModulationParameter`  
_L242-258_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameter`
- desc: Modulation Parameter that scales normalized, unitless value to bipolar range. Mixes additively.
- L249 _public member_ `float UnitRange = 2.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly, meta = (ClampMin = 0.00000001))` — Unit range of modulator. Range is only enforced at modulation destination.
- L251 _public prototype_ `virtual bool RequiresUnitConversion() const override;`
- L252 _public prototype_ `virtual Audio::FModulationMixFunction GetMixFunction() const override;`
- L253 _public prototype_ `virtual Audio::FModulationUnitConversionFunction GetUnitConversionFunction() const override;`
- L254 _public prototype_ `virtual Audio::FModulationNormalizedConversionFunction GetNormalizedConversionFunction() const override;`
- L255 _public prototype_ `virtual float GetUnitMax() const override;`
- L256 _public prototype_ `virtual float GetUnitMin() const override;`
- L257 _public prototype_ `static Audio::FModulationParameter CreateDefaultParameter(float UnitRange = 2.0f);`

#### class `USoundModulationParameterVolume`  
`class USoundModulationParameterVolume : public USoundModulationParameter`  
_L261-285_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameter`
- L268 _public member_ `float MinVolume = -100.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly, meta = (ClampMax = 0.0))` — Minimum volume of parameter (dB). Only enforced at modulation destination.
- L272 _public member_ `float VolumeLimit = 20.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly)` — What the maximum volume (in dB) should be if "Clamp to Normalized Range" is set to false.
- L274 _public prototype_ `virtual bool RequiresUnitConversion() const override;`
- L275 _public prototype_ `virtual Audio::FModulationUnitConversionFunction GetUnitConversionFunction() const override;`
- L276 _public prototype_ `virtual Audio::FModulationNormalizedConversionFunction GetNormalizedConversionFunction() const override;`
- L277 _public prototype_ `virtual float GetUnitMin() const override;`
- L278 _public prototype_ `virtual float GetUnitMax() const override;`
- L279 _public prototype_ `virtual TRange<float> GetNormalizedLimits() const override;`
- L280 _public prototype_ `static Audio::FModulationParameter CreateDefaultParameter(float MinUnitVolume = -100.0f);`
- L283 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`

#### class `USoundModulationParameterAdditive`  
`class USoundModulationParameterAdditive : public USoundModulationParameter`  
_L289-309_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `USoundModulationParameter`
- desc: Modulation Parameter whose values are mixed via addition.
- L297 _public member_ `float UnitMin = 0.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly, meta = (ClampMin = "0.0"))` — Unit minimum of modulator. Minimum is only enforced at modulation destination.
- L301 _public member_ `float UnitMax = 1.0f;` — `UPROPERTY(EditAnywhere, Category = General, BlueprintReadOnly, meta = (ClampMin = "0.0"))` — Unit maximum of modulator. Maximum is only enforced at modulation destination.
- L303 _public prototype_ `virtual bool RequiresUnitConversion() const override;`
- L304 _public prototype_ `virtual Audio::FModulationMixFunction GetMixFunction() const override;`
- L305 _public prototype_ `virtual Audio::FModulationUnitConversionFunction GetUnitConversionFunction() const override;`
- L306 _public prototype_ `virtual Audio::FModulationNormalizedConversionFunction GetNormalizedConversionFunction() const override;`
- L307 _public prototype_ `virtual float GetUnitMax() const override;`
- L308 _public prototype_ `virtual float GetUnitMin() const override;`

#### class `AudioModulation::FSoundModulationPluginParameterAssetProxy`  
`class FSoundModulationPluginParameterAssetProxy : public FSoundModulationParameterAssetProxy`  
_L313-318_
- inherits: `FSoundModulationParameterAssetProxy`
- L316 _public prototype_ `explicit FSoundModulationPluginParameterAssetProxy(USoundModulationParameter* InParameter);`
- L317 _public prototype_ `FSoundModulationPluginParameterAssetProxy(const FSoundModulationPluginParameterAssetProxy& InProxy) = default;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOMODULATION_API`
- L311 _namespace_ `namespace AudioModulation`
- L327 _prototype_ `const Audio::FModulationParameter& GetOrRegisterParameter(const USoundModulationParameter* InParameter, const FString& InName, const FString& InClassName);` (scope `AudioModulation`) — Returns given registered parameter instance reference or creates it from the given asset if not registered. @param InParameter - Parameter asset associated with the pre-existing or to-create parameter @param InName	  - Name of the modulator requesting the parameter. @param InClassName - Name of the modulator class requesting the parameter.

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundModulationPatch.h` (Public)


#### struct `FSoundModulationTransform`  
`struct FSoundModulationTransform : public FWaveTableTransform`  
_L21-27_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FWaveTableTransform`
- L25 _public prototype_ `virtual ~FSoundModulationTransform() override = default;`
- L26 _public function_ `virtual bool ShouldClampToNormalizedRange() const override`

#### struct `FSoundControlModulationInput`  
`struct FSoundControlModulationInput`  
_L32-52_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public prototype_ `FSoundControlModulationInput();`
- L40 _public member_ `uint8 bSampleAndHold : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Sample-And-Hold", DisplayPriority = "30"))` — Get the modulated input value on parent patch initialization and hold that value for its lifetime
- L44 _public member_ `FSoundModulationTransform Transform;` — `UPROPERTY(EditAnywhere, Category = Input, meta = (DisplayPriority = "20"))` — Transform to apply to the input prior to mix phase
- L48 _public member_ `TObjectPtr<USoundControlBus> Bus = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayPriority = "10"))` — The input bus
- L50 _public prototype_ `const USoundControlBus* GetBus() const;`
- L51 _public prototype_ `const USoundControlBus& GetBusChecked() const;`

#### struct `FSoundControlModulationPatch`  
`struct FSoundControlModulationPatch`  
_L55-69_
- reflection: `USTRUCT(BlueprintType)`
- L61 _public member_ `bool bBypass = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inputs)` — Whether or not patch is bypassed (patch is still active, but always returns output parameter default value when modulated)
- L64 _public member_ `TObjectPtr<USoundModulationParameter> OutputParameter = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Output, meta = (DisplayName = "Parameter"))`
- L68 _public member_ `TArray<FSoundControlModulationInput> Inputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inputs)` — Modulation inputs

#### class `USoundModulationPatch`  
`class USoundModulationPatch : public USoundModulatorBase`  
_L72-95_
- reflection: `UCLASS(MinimalAPI, config = Engine, editinlinenew, BlueprintType)`
- inherits: `USoundModulatorBase`
- L78 _public member_ `FSoundControlModulationPatch PatchSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modulation, meta = (ShowOnlyInnerProperties))`
- L81 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;` — USoundModulatorBase Implementation
- L82 _public prototype_ `virtual const Audio::FModulationParameter& GetOutputParameter() const override;`
- L84 _public prototype_ `virtual TUniquePtr<Audio::IModulatorSettings> CreateProxySettings() const override;`
- L87 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L91 _public prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;`
- L92 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L93 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOMODULATION_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundModulationValue.h` (Public)


#### struct `FSoundModulationMixValue`  
`struct FSoundModulationMixValue`  
_L13-68_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public prototype_ `FSoundModulationMixValue() = default;`
- L18 _public prototype_ `FSoundModulationMixValue(float InValue, float InAttackTime, float InReleaseTime);`
- L34 _public member_ `float TargetValue = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayName = "Value"))` — Target value of the modulator.
- L39 _public member_ `float TargetUnitValue = 1.0f;` — `UPROPERTY(Transient, EditAnywhere, Category = General)` — Target value of the modulator (in units if provided).
- L44 _public member_ `float AttackTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayName = "Attack Time (sec)", ClampMin = "0.0", UIMin = "0.0"))` — Time it takes (in sec) to interpolate from the parameter's default value to the mix value.
- L48 _public member_ `float ReleaseTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Modulation, BlueprintReadWrite, meta = (DisplayName = "Release Time (sec)", ClampMin = "0.0", UIMin = "0.0"))` — Time it takes (in sec) to interpolate from the current mix value to the parameter's default value.
- L50 _public prototype_ `void SetActiveFade(EActiveFade InActiveFade, float InFadeTime = -1.0f);`
- L53 _public prototype_ `void SetCurrentValue(float InValue);` — Set current value (for resetting value state only as circumvents lerp, and may result in discontinuity).
- L56 _public prototype_ `float GetCurrentValue() const;` — Current value lerping toward target
- L58 _public prototype_ `void Update(double Elapsed);`
- L61 _private prototype_ `void UpdateDelta();`
- L63 _private member_ `float LerpTime = -1.0f;`
- L64 _private member_ `float Value = 1.0f;`
- L65 _private member_ `float LastTarget = -1.0f;`
- L66 _private member_ `float Delta = 0.0f;`
- L67 _private member_ `EActiveFade ActiveFade = EActiveFade::Attack;`

#### enum `FSoundModulationMixValue::EActiveFade`  
`enum class EActiveFade : uint8`  
_L20-30_
- L23 _public enumerator_ `Attack` — Value interpolating from the parameter's default value to the mix value.
- L26 _public enumerator_ `Release` — Value interpolating from the mix value to the parameter's default value.
- L29 _public enumerator_ `Override` — User-requested fade time to an active mix by filter (ex. from Blueprint) or editor property adjustment

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOMODULATION_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundModulatorAsset.h` (Public)


#### class `AudioModulation::FSoundModulatorAsset`  
`class FSoundModulatorAsset`  
_L17-81_
- L19 _private member_ `FSoundModulatorAssetProxyPtr Proxy;`
- L22 _public prototype_ `FSoundModulatorAsset() = default;`
- L24 _public function_ `FSoundModulatorAsset(const FSoundModulatorAsset& InOther) : Proxy(InOther.Proxy)`
- L29 _public function_ `FSoundModulatorAsset& operator=(const FSoundModulatorAsset& InOther)`
- L35 _public function_ `FSoundModulatorAsset& operator=(FSoundModulatorAsset&& InOther)`
- L41 _public prototype_ `FSoundModulatorAsset(const TSharedPtr<Audio::IProxyData>& InInitData);`
- L43 _public function_ `Audio::FModulatorId GetModulatorId() const`
- L53 _public function_ `bool IsValid() const`
- L58 _public function_ `const FSoundModulatorAssetProxyPtr& GetProxy() const`
- L63 _public function_ `const FSoundModulatorAssetProxy* operator->() const`
- L68 _public function_ `FSoundModulatorAssetProxy* operator->()`

#### class `AudioModulation::FSoundModulationParameterAsset`  
`class FSoundModulationParameterAsset`  
_L83-124_
- L85 _private member_ `FSoundModulationParameterAssetProxyPtr Proxy;`
- L88 _public prototype_ `FSoundModulationParameterAsset() = default;`
- L89 _public prototype_ `FSoundModulationParameterAsset(const FSoundModulationParameterAsset& InOther) = default;`
- L90 _public prototype_ `FSoundModulationParameterAsset(FSoundModulationParameterAsset&& InOther) = default;`
- L91 _public prototype_ `FSoundModulationParameterAsset(const TSharedPtr<Audio::IProxyData>& InInitData);`
- L93 _public prototype_ `FSoundModulationParameterAsset& operator=(const FSoundModulationParameterAsset& InOther) = default;`
- L94 _public prototype_ `FSoundModulationParameterAsset& operator=(FSoundModulationParameterAsset && InOther) = default;`
- L96 _public function_ `bool IsValid() const`
- L101 _public function_ `const FSoundModulationParameterAssetProxyPtr& GetProxy() const`
- L106 _public function_ `const FSoundModulationParameterAssetProxy* operator->() const`
- L111 _public function_ `FSoundModulationParameterAssetProxy* operator->()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AudioModulation`
- L13 _externvar_ `extern const FString PluginAuthor;` (scope `AudioModulation`)
- L14 _externvar_ `extern const FText PluginNodeCategory;` (scope `AudioModulation`)
- L15 _externvar_ `extern const FText PluginNodeMissingPrompt;` (scope `AudioModulation`)
- L73 _function_ `friend inline uint32 GetTypeHash(const AudioModulation::FSoundModulatorAsset& InModulatorAsset)` (scope `AudioModulation`)
- L116 _function_ `friend inline uint32 GetTypeHash(const AudioModulation::FSoundModulationParameterAsset& InModulationParameterAsset)` (scope `AudioModulation`)
