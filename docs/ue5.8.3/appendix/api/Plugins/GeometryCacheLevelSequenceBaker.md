# Plugins / GeometryCacheLevelSequenceBaker

- module root: `Plugins/Experimental/GeometryCacheLevelSequenceBaker/Source/GeometryCacheLevelSequenceBaker`
- headers: 5; symbols: 121
- symbol kinds: class=6, delegate=1, enum=1, enumerator=4, function=1, member=56, prototype=42, struct=8, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, GeometryCache, InputCore, LevelSequence, LevelSequenceEditor, MeshDescription, MovieScene, Sequencer, SequencerCore, Slate, SlateCore, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/GeometryCacheLevelSequenceBaker/Source/GeometryCacheLevelSequenceBaker/Private/FGeometryCacheLevelSequenceBakerCustomization.h` (Private)


#### class `FGeometryCacheLevelSequenceBakerCustomization`  
`class FGeometryCacheLevelSequenceBakerCustomization : public ISequencerCustomization`  
_L5-18_
- inherits: `ISequencerCustomization`
- L8 _public prototype_ `void RegisterSequencerCustomization(FSequencerCustomizationBuilder& Builder) override;`
- L9 _public prototype_ `void UnregisterSequencerCustomization() override;`
- L11 _public prototype_ `void ExtendActionsMenu(FMenuBuilder& MenuBuilder);`
- L12 _public prototype_ `void BakeGeometryCache();`
- L14 _public member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L16 _public member_ `TSharedPtr<FUICommandList> ActionsMenuCommandList;`
- L17 _public member_ `TSharedPtr<FExtender> ActionsMenuExtender;`

### `Plugins/Experimental/GeometryCacheLevelSequenceBaker/Source/GeometryCacheLevelSequenceBaker/Private/GeometryCacheLevelSequenceBaker.h` (Private)


#### class `ULevelSequenceGeometryCacheBakerOption`  
`class ULevelSequenceGeometryCacheBakerOption : public UObject`  
_L19-28_
- reflection: `UCLASS()`
- inherits: `UObject`
- L24 _public member_ `int32 NumSamplesPerFrame = 1;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L27 _public member_ `bool bShouldBake = false;` — `UPROPERTY()`

#### class `FGeometryCacheLevelSequenceBaker`  
`class FGeometryCacheLevelSequenceBaker : public FTickableEditorObject`  
_L32-185_
- inherits: `FTickableEditorObject`
- L36 _public prototype_ `static void Bake(TSharedRef<ISequencer> InSequencer );`
- L37 _public prototype_ `static TArray<FGuid> GetBindingsToBake(TSharedRef<ISequencer> InSequencer);`
- L38 _public prototype_ `static bool GetGeometryCacheAssetPathFromUser(FString& OutPackageName, FString& OutAssetName);`
- L40 _public prototype_ `void Tick(float DeltaTime) override;`
- L41 _public prototype_ `void OnWorldTickEnd(UWorld*, ELevelTick, float);`
- L42 _public prototype_ `bool IsTickable() const override;`
- L43 _public function_ `TStatId GetStatId() const override`
- L46 _private prototype_ `FGeometryCacheLevelSequenceBaker() = default;`
- L47 _private prototype_ `static FGeometryCacheLevelSequenceBaker& Get();`
- L49 _private prototype_ `void SetupComponentBakeTasks();`
- L50 _private prototype_ `void Gather();`
- L51 _private prototype_ `void RequestReadback();`
- L52 _private prototype_ `void WriteToAsset();`
- L56 _private member_ `static const int32 LODIndexToBake;`
- L57 _private member_ `static const float TotalAmountOfWork;`
- L58 _private member_ `static const float AmountOfWorkGatherStage;`
- L59 _private member_ `static const float AmountOfWorkBakeStage;`
- L73 _private typedef_ `using FFrameData = UE::GeometryCacheHelpers::FGeometryCacheConstantTopologyWriter::FFrameData;`
- L74 _private typedef_ `using FVisibilitySample = UE::GeometryCacheHelpers::FGeometryCacheConstantTopologyWriter::FVisibilitySample;`
- L97 _private prototype_ `static void OnReadbackResultConfirmed(FComponentTask& Task, int32 SampleIndex, bool bMeshAvailable);`
- L181 _private prototype_ `void EndTask();`
- L183 _private member_ `FCriticalSection CurrentBakeTaskLifeTimeCriticalSection;`
- L184 _private member_ `TUniquePtr<FBakeTask> CurrentBakeTask;`

#### struct `FGeometryCacheLevelSequenceBaker::FSkeletalMeshComponentSettingScope`  
`struct FSkeletalMeshComponentSettingScope`  
_L61-71_
- L63 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> Component;`
- L65 _public member_ `bool bPreviousAlwaysUseMeshDeformer = false;`
- L66 _public member_ `bool bPreviousUpdateAnimationInEditor = false;`
- L67 _public member_ `int32 PreviousForcedLOD = 0;`
- L69 _public prototype_ `FSkeletalMeshComponentSettingScope(USkeletalMeshComponent* InComponent);`
- L70 _public prototype_ `~FSkeletalMeshComponentSettingScope();`

#### struct `FGeometryCacheLevelSequenceBaker::FComponentInfo`  
`struct FComponentInfo`  
_L76-81_
- L78 _public member_ `FName Name;`
- L79 _public member_ `USkeletalMesh* SkeletalMeshAsset;`
- L80 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;`

#### struct `FGeometryCacheLevelSequenceBaker::FComponentTask`  
`struct FComponentTask`  
_L83-95_
- L85 _public member_ `FGuid Binding;`
- L87 _public member_ `FComponentInfo ComponentInfo;`
- L89 _public member_ `int32 ActualLODIndexBaked = INDEX_NONE;`
- L90 _public member_ `TArray<FFrameData> GeometrySamples;`
- L91 _public member_ `std::atomic<uint32> NumSamplesPending = 0;`
- L92 _public member_ `TArray<FVisibilitySample> VisibilitySamples;`
- L94 _public member_ `TUniquePtr<FSkeletalMeshComponentSettingScope> ComponentSettingScope;`

#### struct `FGeometryCacheLevelSequenceBaker::FEngineFixedDeltaTimeScope`  
`struct FEngineFixedDeltaTimeScope`  
_L99-105_
- L101 _public member_ `bool bPreviousUseFixedDeltaTime = false;`
- L102 _public member_ `double PreviousFixedDeltaTime = 0;`
- L103 _public prototype_ `FEngineFixedDeltaTimeScope(double NewFixedDeltaTime);`
- L104 _public prototype_ `~FEngineFixedDeltaTimeScope();`

#### struct `FGeometryCacheLevelSequenceBaker::FSequencerSettingScope`  
`struct FSequencerSettingScope`  
_L107-116_
- L109 _public member_ `TWeakPtr<ISequencer> Sequencer;`
- L110 _public member_ `FQualifiedFrameTime PreviousLocalTime;`
- L111 _public member_ `ESequencerLoopMode PreviousLoopMode;`
- L112 _public member_ `EUpdateClockSource PreviousClockSource;`
- L114 _public prototype_ `FSequencerSettingScope(TSharedPtr<ISequencer> InSequencer);`
- L115 _public prototype_ `~FSequencerSettingScope();`

#### struct `FGeometryCacheLevelSequenceBaker::FConsoleVariableOverrideScope`  
`struct FConsoleVariableOverrideScope`  
_L118-124_
- L120 _public member_ `int32 PreviousForceLOD = 0;`
- L121 _public member_ `int32 PreviousSkeletalMeshLODBias = 0;`
- L122 _public prototype_ `FConsoleVariableOverrideScope();`
- L123 _public prototype_ `~FConsoleVariableOverrideScope();`

#### struct `FGeometryCacheLevelSequenceBaker::FWorldTickEndDelegateScope`  
`struct FWorldTickEndDelegateScope`  
_L126-131_
- L128 _public member_ `FDelegateHandle OnWorldTickEndDelegate;`
- L129 _public prototype_ `FWorldTickEndDelegateScope();`
- L130 _public prototype_ `~FWorldTickEndDelegateScope();`

#### enum `FGeometryCacheLevelSequenceBaker::EStage`  
`enum class EStage`  
_L133-139_
- L135 _public enumerator_ `Gather`
- L136 _public enumerator_ `RequestReadback`
- L137 _public enumerator_ `WriteToAsset`
- L138 _public enumerator_ `End`

#### struct `FGeometryCacheLevelSequenceBaker::FBakeTask`  
`struct FBakeTask`  
_L143-179_
- L145 _public member_ `FString PackageName;`
- L146 _public member_ `FString AssetName;`
- L148 _public member_ `TWeakPtr<ISequencer> Sequencer;`
- L149 _public member_ `TArray<FGuid> Bindings;`
- L150 _public member_ `TMap<FGuid, TMap<FName, FComponentInfo>> BindingToComponentInfoMap;`
- L151 _public member_ `FFrameTime StartFrame;`
- L152 _public member_ `FFrameTime EndFrame;`
- L154 _public member_ `EStage Stage = EStage::Gather;`
- L156 _public member_ `TArray<FComponentTask> ComponentTasks;`
- L157 _public member_ `std::atomic<uint32> NumComponentTasksPending = 0;`
- L159 _public member_ `uint32 NumSamples = 0;`
- L160 _public member_ `uint32 CurrentSampleIndex = 0;`
- L161 _public member_ `float SamplesPerSecond = 0;`
- L163 _public member_ `TUniquePtr<FScopedSlowTask> SlowTask;`
- L164 _public member_ `TUniquePtr<FEngineFixedDeltaTimeScope> FixedDeltaTimeScope;`
- L165 _public member_ `TUniquePtr<FSequencerSettingScope> SequencerStateScope;`
- L166 _public member_ `TUniquePtr<FConsoleVariableOverrideScope> ConsoleVariableOverrideScope;`
- L167 _public member_ `TUniquePtr<FWorldTickEndDelegateScope> WorldTickEndDelegateScope;`
- L169 _public member_ `FDelegateHandle OnEndFrameDelegateHandle;`
- L171 _public member_ `TMap<TWeakObjectPtr<USkeletalMeshComponent>, TUniquePtr<FSkeletalMeshComponentSettingScope>> GatherStageComponentSettingScopes;`
- L173 _public prototype_ `bool IsSequencerPlaying();`
- L174 _public prototype_ `void PlaySequencer();`
- L176 _public prototype_ `void UpdateGatherProgress();`
- L177 _public prototype_ `void UpdateBakeProgress();`
- L178 _public prototype_ `void TickProgress();`

### `Plugins/Experimental/GeometryCacheLevelSequenceBaker/Source/GeometryCacheLevelSequenceBaker/Private/GeometryCacheLevelSequenceBakerCommands.h` (Private)


#### class `FGeometryCacheLevelSequenceBakerCommands`  
`class FGeometryCacheLevelSequenceBakerCommands : public TCommands<FGeometryCacheLevelSequenceBakerCommands>`  
_L8-17_
- inherits: `TCommands<FGeometryCacheLevelSequenceBakerCommands>`
- L11 _public prototype_ `FGeometryCacheLevelSequenceBakerCommands();`
- L14 _public member_ `TSharedPtr< FUICommandInfo > BakeGeometryCache;` — Exports sequence to geometry cache.
- L16 _public prototype_ `virtual void RegisterCommands() override;`

### `Plugins/Experimental/GeometryCacheLevelSequenceBaker/Source/GeometryCacheLevelSequenceBaker/Private/GeometryCacheLevelSequenceBakerStyle.h` (Private)


#### class `FGeometryCacheLevelSequenceBakerStyle`  
`class FGeometryCacheLevelSequenceBakerStyle : public FSlateStyleSet`  
_L8-22_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `static FGeometryCacheLevelSequenceBakerStyle& Get();`
- L17 _protected prototype_ `static void Register();`
- L18 _protected prototype_ `static void Unregister();`
- L21 _private prototype_ `FGeometryCacheLevelSequenceBakerStyle();`

### `Plugins/Experimental/GeometryCacheLevelSequenceBaker/Source/GeometryCacheLevelSequenceBaker/Public/GeometryCacheLevelSequenceBakerModule.h` (Public)


#### class `FGeometryCacheLevelSequenceBakerModule`  
`class FGeometryCacheLevelSequenceBakerModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public member_ `FGuid CustomizationHandle;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryCacheLevelSequenceBaker, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryCacheLevelSequenceBaker, Log, All);`
