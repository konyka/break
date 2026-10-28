# Plugins / ChaosFleshGenerator

- module root: `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator`
- headers: 8; symbols: 152
- symbol kinds: class=10, delegate=4, enum=2, enumerator=5, function=8, member=46, namespace=19, prototype=50, struct=4, typedef=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ChaosFlesh, ChaosFleshEngine, ChaosFleshNodes, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowSimulation, Engine, GeometryCache, MLDeformerFramework, MLDeformerFrameworkEditor, PropertyEditor, RenderCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Chaos, ChaosCore, Core

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/ChaosFleshGenerator.h` (Private)


#### enum `UE::Chaos::FleshGenerator::EFleshGeneratorActions`  
`enum class EFleshGeneratorActions`  
_L19-24_
- L21 _public enumerator_ `NoAction`
- L22 _public enumerator_ `StartGenerate`
- L23 _public enumerator_ `TickGenerate`

#### class `UE::Chaos::FleshGenerator::FChaosFleshGenerator`  
`class FChaosFleshGenerator : public FTickableEditorObject`  
_L26-50_
- inherits: `FTickableEditorObject`
- L29 _public prototype_ `FChaosFleshGenerator();`
- L30 _public prototype_ `virtual ~FChaosFleshGenerator();`
- L33 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L34 _public prototype_ `virtual TStatId GetStatId() const override;`
- L35 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L38 _public prototype_ `UFleshGeneratorProperties& GetProperties() const;`
- L39 _public prototype_ `void RequestAction(EFleshGeneratorActions Action);`
- L42 _private prototype_ `void StartGenerate();`
- L43 _private prototype_ `void TickGenerate();`
- L44 _private prototype_ `void FreeTaskResource(bool bCancelled);`
- L45 _private prototype_ `UGeometryCache* GetCache() const;`
- L47 _private member_ `TObjectPtr<UFleshGeneratorProperties> Properties;`
- L48 _private member_ `EFleshGeneratorActions PendingAction = EFleshGeneratorActions::NoAction;`
- L49 _private member_ `TSharedPtr<FTaskResource> TaskResource;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGenerator, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGenerator, Log, All);`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Chaos` (scope `UE`)
- L15 _namespace_ `namespace FleshGenerator` (scope `UE::Chaos`)

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/ChaosFleshGeneratorPrivate.h` (Private)


#### class `UE::Chaos::FleshGenerator::Private::FTimeScope`  
`class FTimeScope`  
_L23-30_
- L25 _private member_ `FString Name;`
- L26 _private member_ `FDateTime StartTime;`
- L28 _public prototype_ `explicit FTimeScope(FString InName);`
- L29 _public prototype_ `~FTimeScope();`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGeneratorPrivate, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGeneratorPrivate, Log, All);`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Chaos` (scope `UE`)
- L19 _namespace_ `namespace FleshGenerator` (scope `UE::Chaos`)
- L21 _namespace_ `namespace Private` (scope `UE::Chaos::FleshGenerator`)
- L32 _prototype_ `TArray<int32> ParseFrames(const FString& FramesString);` (scope `UE::Chaos::FleshGenerator::Private`)
- L34 _prototype_ `TArray<int32> Range(int32 End);` (scope `UE::Chaos::FleshGenerator::Private`)
- L36 _prototype_ `TArray<uint32> Range(uint32 Start, uint32 End);` (scope `UE::Chaos::FleshGenerator::Private`)
- L38 _prototype_ `TOptional<TArray<int32>> GetMeshImportVertexMap(const USkinnedAsset& SkinnedMeshAsset, const UFleshAsset& FleshAsset);` (scope `UE::Chaos::FleshGenerator::Private`)

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/ChaosFleshGeneratorSimulation.h` (Private)


#### class `UE::Chaos::FleshGenerator::TTaskRunner`  
`template<typename TaskType> class TTaskRunner : public FNonAbandonableTask`  
_L27-55_
- inherits: `FNonAbandonableTask`
- L30 _public function_ `TTaskRunner(TUniquePtr<TaskType> InTask) : Task(MoveTemp(InTask))`
- L35 _public function_ `void DoWork()`
- L43 _public function_ `bool CanAbandon()`
- L48 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L54 _private member_ `TUniquePtr<TaskType> Task;`

#### struct `UE::Chaos::FleshGenerator::FSimResource`  
`struct FSimResource`  
_L57-79_
- L59 _public member_ `TObjectPtr<UFleshGeneratorComponent> FleshComponent = nullptr;`
- L60 _public member_ `TObjectPtr<USkeletalGeneratorComponent> SkeletalComponent = nullptr;`
- L61 _public member_ `TObjectPtr<UDeformableSolverComponent> SolverComponent = nullptr;`
- L63 _public member_ `TArrayView<TArray<FVector3f>> SimulatedPositions;`
- L64 _public member_ `std::atomic<int32>* NumSimulatedFrames = nullptr;`
- L66 _public member_ `std::atomic<bool>* bCancelled = nullptr;`
- L68 _public function_ `bool IsCancelled() const`
- L72 _public function_ `void FinishFrame()`

#### class `UE::Chaos::FleshGenerator::FLaunchSimsTask`  
`class FLaunchSimsTask`  
_L81-107_
- L84 _public prototype_ `FLaunchSimsTask(TSharedPtr<FTaskResource> InTaskResource, TObjectPtr<UFleshGeneratorProperties> InProperties);`
- L86 _public prototype_ `void DoWork();`
- L89 _private typedef_ `using FPipe = ::UE::Tasks::FPipe;`
- L97 _private prototype_ `void Simulate(FSimResource& SimResource, int32 AnimFrame, int32 CacheFrame) const;`
- L98 _private prototype_ `void PrepareAnimationSequence();`
- L99 _private prototype_ `void RestoreAnimationSequence();`
- L100 _private prototype_ `TArray<FTransform> GetBoneTransforms(USkeletalMeshComponent& InSkeletalComponent, int32 Frame) const;`
- L101 _private prototype_ `TArray<FVector3f> GetRenderPositions(FSimResource& SimResource) const;`
- L103 _private member_ `TSharedPtr<FTaskResource> TaskResource;`
- L104 _private member_ `TArray< TSharedPtr<FSimResource> >& SimResources;`
- L105 _private member_ `TObjectPtr<UFleshGeneratorProperties> Properties;`
- L106 _private member_ `EAnimInterpolationType InterpolationTypeBackup = EAnimInterpolationType::Linear;`

#### enum `UE::Chaos::FleshGenerator::FLaunchSimsTask::ESaveType`  
`enum class ESaveType`  
_L91-95_
- L93 _public enumerator_ `LastStep`
- L94 _public enumerator_ `EveryStep`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGeneratorSimulation, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGeneratorSimulation, Log, All);`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Chaos` (scope `UE`)
- L22 _namespace_ `namespace FleshGenerator` (scope `UE::Chaos`)

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/ChaosFleshGeneratorThreading.h` (Private)


#### struct `UE::Chaos::FleshGenerator::FTaskResource`  
`struct FTaskResource`  
_L22-47_
- L24 _public typedef_ `using FExecuterType = FAsyncTask<TTaskRunner<FLaunchSimsTask>>;`
- L26 _public member_ `TArray<TSharedPtr<FSimResource>> SimResources;`
- L28 _public member_ `TUniquePtr<FExecuterType> Executer;`
- L29 _public member_ `TUniquePtr<FAsyncTaskNotification> Notification;`
- L30 _public member_ `FDateTime StartTime;`
- L31 _public member_ `FDateTime LastUpdateTime;`
- L33 _public member_ `TArray<int32> FramesToSimulate;`
- L34 _public member_ `TArray<TArray<FVector3f>> SimulatedPositions;`
- L35 _public member_ `TArray<uint32> ImportedVertexNumbers;`
- L36 _public member_ `UGeometryCache* Cache = nullptr;`
- L38 _public member_ `std::atomic<int32> NumSimulatedFrames = 0;`
- L39 _public member_ `std::atomic<bool> bCancelled = false;`
- L41 _public member_ `UWorld* World = nullptr;`
- L43 _public prototype_ `bool AllocateSimResources_GameThread(TObjectPtr<UFleshGeneratorProperties> Properties, int32 Num);`
- L44 _public prototype_ `void FreeSimResources_GameThread();`
- L45 _public prototype_ `void FlushRendering();`
- L46 _public prototype_ `void Cancel();`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGeneratorThreading, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshGeneratorThreading, Log, All);`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Chaos` (scope `UE`)
- L20 _namespace_ `namespace FleshGenerator` (scope `UE::Chaos`)

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/ChaosFleshGeneratorToolsMenuExtender.h` (Private)


#### struct `UE::Chaos::FleshGenerator::FChaosFleshGeneratorTabSummoner`  
`struct FChaosFleshGeneratorTabSummoner : public FWorkflowTabFactory`  
_L11-20_
- inherits: `FWorkflowTabFactory`
- L14 _public member_ `static const FName TabID;`
- L15 _public typedef_ `using FMLDeformerEditorToolkit = UE::MLDeformer::FMLDeformerEditorToolkit;`
- L17 _public prototype_ `FChaosFleshGeneratorTabSummoner(const TSharedRef<FMLDeformerEditorToolkit>& InEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L19 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`

#### class `UE::Chaos::FleshGenerator::FChaosFleshGeneratorToolsMenuExtender`  
`class FChaosFleshGeneratorToolsMenuExtender : public UE::MLDeformer::FToolsMenuExtender`  
_L22-29_
- inherits: `UE::MLDeformer::FToolsMenuExtender`
- L25 _public typedef_ `using FMLDeformerEditorToolkit = UE::MLDeformer::FMLDeformerEditorToolkit;`
- L26 _public prototype_ `~FChaosFleshGeneratorToolsMenuExtender() override = default;`
- L27 _public prototype_ `virtual FMenuEntryParams GetMenuEntry(FMLDeformerEditorToolkit& Toolkit) const override;`
- L28 _public prototype_ `virtual TSharedPtr<FWorkflowTabFactory> GetTabSummoner(const TSharedRef<FMLDeformerEditorToolkit>& Toolkit) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace FleshGenerator` (scope `UE::Chaos`)
- L31 _prototype_ `TUniquePtr<FChaosFleshGeneratorToolsMenuExtender> CreateToolsMenuExtender();` (scope `UE::Chaos::FleshGenerator`)

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/FleshGeneratorComponent.h` (Private)


#### class `UFleshGeneratorComponent`  
`class UFleshGeneratorComponent : public UFleshComponent`  
_L20-33_
- reflection: `UCLASS()`
- inherits: `UFleshComponent`
- desc: Flesh data generation component.
- L24 _public prototype_ `UFleshGeneratorComponent(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `~UFleshGeneratorComponent();`
- L28 _public prototype_ `void Pose(USkeletalGeneratorComponent& InSkeletalComponent, const TArray<FTransform>& InComponentSpaceTransforms);` — Pose the cloth component using component space transforms.
- L31 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`

#### class `USkeletalGeneratorComponent`  
`class USkeletalGeneratorComponent : public USkeletalMeshComponent`  
_L40-47_
- reflection: `UCLASS()`
- inherits: `USkeletalMeshComponent`
- desc: USkeletalGeneratorComponent data generation component.
- L44 _public prototype_ `USkeletalGeneratorComponent(const FObjectInitializer& ObjectInitializer);`
- L45 _public prototype_ `~USkeletalGeneratorComponent();`
- L46 _public prototype_ `void FlipSpaceBuffer();`

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/FleshGeneratorProperties.h` (Private)


#### struct `FFleshGeneratorSolverTimingGroup`  
`struct FFleshGeneratorSolverTimingGroup`  
_L17-37_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `float FrameRate = 24.;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming", meta = (Min = 1))` — Frame rate of the training animation (FrameDeltaTime = 1/FrameRate)
- L27 _public member_ `int32 NumFrames = 150;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming", meta = (Min = 0))` — Number of frames to simulate ( the length of the animation)
- L31 _public member_ `int32 NumSubSteps = 2;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming", meta = (Min = 0))` — Number of subdivisions within a time step (SolverStep = FrameDeltaTime/NumSubSteps)
- L35 _public member_ `int32 NumIterations = 5;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming", meta = (Min = 0))` — Number of convergence steps for the constraint solver for each solver step.

#### class `UFleshGeneratorProperties`  
`class UFleshGeneratorProperties : public UObject`  
_L41-82_
- reflection: `UCLASS()`
- inherits: `UObject`
- L47 _public member_ `TObjectPtr<USkinnedAsset> SkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, Category = Input)` — Skeletal mesh that will be used in MLDeformer
- L51 _public member_ `TObjectPtr<UFleshAsset> FleshAsset;` — `UPROPERTY(EditAnywhere, Category = Input)` — Chaos cloth asset used in simulation. This should be different from the skeletal mesh asset.
- L55 _public member_ `TObjectPtr<UAnimSequence> AnimationSequence;` — `UPROPERTY(EditAnywhere, Category = Input)` — Training poses.
- L59 _public member_ `FString FramesToSimulate;` — `UPROPERTY(EditAnywhere, Category = Input)` — e.g. "0, 2, 5-10, 12-15". If left empty, all frames will be used
- L63 _public member_ `TObjectPtr<UGeometryCache> SimulatedCache;` — `UPROPERTY(EditAnywhere, Category = Output)` — Output meshes
- L66 _public member_ `FFleshGeneratorSolverTimingGroup SolverTiming;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SimulationSettings")`
- L69 _public member_ `FSolverEvolutionGroup SolverEvolution;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SimulationSettings")`
- L72 _public member_ `FSolverCollisionsGroup SolverCollisions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SimulationSettings")`
- L75 _public member_ `FSolverConstraintsGroup SolverConstraints;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SimulationSettings")`
- L78 _public member_ `FSolverForcesGroup SolverForces;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SimulationSettings")`
- L81 _public member_ `FSolverDebuggingGroup SolverDebugging;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SimulationSettings")`

### `Plugins/Animation/MLDeformer/ChaosFleshGenerator/Source/ChaosFleshGenerator/Private/SFleshGeneratorWidget.h` (Private)


#### class `UE::Chaos::FleshGenerator::SFleshGeneratorWidget`  
`class SFleshGeneratorWidget : public SCompoundWidget`  
_L14-27_
- inherits: `SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(SFleshGeneratorWidget)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `TWeakObjectPtr<UFleshGeneratorProperties> GetProperties() const;`
- L25 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L26 _private member_ `TSharedPtr<FChaosFleshGenerator> ChaosFleshGenerator;`

#### class `UE::Chaos::FleshGenerator::FFleshGeneratorDetails`  
`class FFleshGeneratorDetails : public IDetailCustomization`  
_L29-36_
- inherits: `IDetailCustomization`
- L32 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L35 _private prototype_ `TWeakObjectPtr<UFleshGeneratorProperties> GetProperties(IDetailLayoutBuilder& DetailBuilder) const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Chaos` (scope `UE`)
- L10 _namespace_ `namespace FleshGenerator` (scope `UE::Chaos`)
