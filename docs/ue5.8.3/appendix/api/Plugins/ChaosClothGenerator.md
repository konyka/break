# Plugins / ChaosClothGenerator

- module root: `Plugins/Animation/MLDeformer/ChaosClothGenerator/Source/ChaosClothGenerator`
- headers: 5; symbols: 83
- symbol kinds: class=7, delegate=1, enum=1, enumerator=3, function=2, member=18, namespace=12, prototype=32, struct=1, typedef=6
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ChaosClothAssetEngine, CoreUObject, DataflowSimulation, Engine, GeometryCache, MLDeformerFramework, MLDeformerFrameworkEditor, MeshDescription, PropertyEditor, RenderCore, SkeletalMeshDescription, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/ChaosClothGenerator/Source/ChaosClothGenerator/Private/ChaosClothGenerator.h` (Private)


#### enum `UE::Chaos::ClothGenerator::EClothGeneratorActions`  
`enum class EClothGeneratorActions`  
_L18-23_
- L20 _public enumerator_ `NoAction`
- L21 _public enumerator_ `StartGenerate`
- L22 _public enumerator_ `TickGenerate`

#### class `UE::Chaos::ClothGenerator::FChaosClothGenerator`  
`class FChaosClothGenerator : public FTickableEditorObject`  
_L25-58_
- inherits: `FTickableEditorObject`
- L28 _public prototype_ `FChaosClothGenerator();`
- L29 _public prototype_ `virtual ~FChaosClothGenerator();`
- L32 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L33 _public prototype_ `virtual TStatId GetStatId() const override;`
- L34 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L37 _public prototype_ `UClothGeneratorProperties& GetProperties() const;`
- L38 _public prototype_ `void RequestAction(EClothGeneratorActions Action);`
- L47 _private typedef_ `using FProxy = FClothGeneratorProxy;`
- L48 _private typedef_ `using FExecuterType = FAsyncTask<TTaskRunner<FLaunchSimsTask>>;`
- L50 _private prototype_ `void StartGenerate();`
- L51 _private prototype_ `void TickGenerate();`
- L52 _private prototype_ `void FreeTaskResource(bool bCancelled);`
- L53 _private prototype_ `UGeometryCache* GetCache() const;`
- L55 _private member_ `TStrongObjectPtr<UClothGeneratorProperties> Properties;`
- L56 _private member_ `EClothGeneratorActions PendingAction = EClothGeneratorActions::NoAction;`
- L57 _private member_ `TUniquePtr<FTaskResource> TaskResource;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothGenerator, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothGenerator, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Chaos` (scope `UE`)
- L14 _namespace_ `namespace ClothGenerator` (scope `UE::Chaos`)

### `Plugins/Animation/MLDeformer/ChaosClothGenerator/Source/ChaosClothGenerator/Private/ChaosClothGeneratorToolsMenuExtender.h` (Private)


#### struct `UE::Chaos::ClothGenerator::FChaosClothGeneratorTabSummoner`  
`struct FChaosClothGeneratorTabSummoner : public FWorkflowTabFactory`  
_L11-20_
- inherits: `FWorkflowTabFactory`
- L14 _public member_ `static const FName TabID;`
- L15 _public typedef_ `using FMLDeformerEditorToolkit = UE::MLDeformer::FMLDeformerEditorToolkit;`
- L17 _public prototype_ `FChaosClothGeneratorTabSummoner(const TSharedRef<FMLDeformerEditorToolkit>& InEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L19 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`

#### class `UE::Chaos::ClothGenerator::FChaosClothGeneratorToolsMenuExtender`  
`class FChaosClothGeneratorToolsMenuExtender : public UE::MLDeformer::FToolsMenuExtender`  
_L22-29_
- inherits: `UE::MLDeformer::FToolsMenuExtender`
- L25 _public typedef_ `using FMLDeformerEditorToolkit = UE::MLDeformer::FMLDeformerEditorToolkit;`
- L26 _public prototype_ `~FChaosClothGeneratorToolsMenuExtender() override = default;`
- L27 _public prototype_ `virtual FMenuEntryParams GetMenuEntry(FMLDeformerEditorToolkit& Toolkit) const override;`
- L28 _public prototype_ `virtual TSharedPtr<FWorkflowTabFactory> GetTabSummoner(const TSharedRef<FMLDeformerEditorToolkit>& Toolkit) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothGenerator` (scope `UE::Chaos`)
- L31 _prototype_ `TUniquePtr<FChaosClothGeneratorToolsMenuExtender> CreateToolsMenuExtender();` (scope `UE::Chaos::ClothGenerator`)

### `Plugins/Animation/MLDeformer/ChaosClothGenerator/Source/ChaosClothGenerator/Private/ClothGeneratorComponent.h` (Private)


#### class `UE::Chaos::ClothGenerator::FClothGeneratorProxy`  
`class FClothGeneratorProxy : public UE::Chaos::ClothAsset::FClothSimulationProxy`  
_L12-25_
- inherits: `UE::Chaos::ClothAsset::FClothSimulationProxy`
- L15 _public typedef_ `using FClothSimulationProxy = UE::Chaos::ClothAsset::FClothSimulationProxy;`
- L16 _public prototype_ `explicit FClothGeneratorProxy(const UChaosClothComponent& InClothComponent);`
- L17 _public prototype_ `~FClothGeneratorProxy();`
- L19 _public prototype_ `virtual void PostConstructor() override;`

#### class `UClothGeneratorComponent`  
`class UClothGeneratorComponent : public UChaosClothComponent`  
_L32-55_
- reflection: `UCLASS()`
- inherits: `UChaosClothComponent`
- desc: Cloth data generation component.
- L36 _public prototype_ `UClothGeneratorComponent(const FObjectInitializer& ObjectInitializer);`
- L37 _public prototype_ `UClothGeneratorComponent(FVTableHelper& Helper);`
- L38 _public prototype_ `~UClothGeneratorComponent();`
- L40 _public typedef_ `using FProxy = UE::Chaos::ClothGenerator::FClothGeneratorProxy;`
- L41 _public prototype_ `TWeakPtr<FProxy> GetProxy() const;`
- L44 _public prototype_ `void Pose(const TArray<FTransform>& InComponentSpaceTransforms);` — Pose the cloth component using component space transforms.
- L47 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L51 _protected prototype_ `virtual TSharedPtr<UE::Chaos::ClothAsset::FClothSimulationProxy> CreateClothSimulationProxy() override;` — Begin UChaosClothComponent Interface
- L54 _private member_ `TWeakPtr<FProxy> Proxy;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Chaos` (scope `UE`)
- L10 _namespace_ `namespace ClothGenerator` (scope `UE::Chaos`)

### `Plugins/Animation/MLDeformer/ChaosClothGenerator/Source/ChaosClothGenerator/Private/ClothGeneratorProperties.h` (Private)


#### class `UClothGeneratorProperties`  
`class UClothGeneratorProperties : public UObject`  
_L15-59_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public member_ `TObjectPtr<USkinnedAsset> SkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, Category = Input)` — Skeletal mesh that will be used in MLDeformer
- L25 _public member_ `TObjectPtr<UChaosClothAsset> ClothAsset;` — `UPROPERTY(EditAnywhere, Category = Input)` — Chaos cloth asset used in simulation. This should be different from the skeletal mesh asset.
- L29 _public member_ `TObjectPtr<UAnimSequence> AnimationSequence;` — `UPROPERTY(EditAnywhere, Category = Input)` — Training poses.
- L33 _public member_ `FString FramesToSimulate;` — `UPROPERTY(EditAnywhere, Category = Input)` — e.g. "0, 2, 5-10, 12-15". If left empty, all frames will be used
- L37 _public member_ `TObjectPtr<UGeometryCache> SimulatedCache;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (EditCondition = "!bDebug"))` — Output meshes
- L41 _public member_ `bool bDebug = false;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Debug a single pose
- L45 _public member_ `uint32 DebugFrame = 0;` — `UPROPERTY(EditAnywhere, Category = Debug, meta = (Min = 0, EditCondition = "bDebug"))` — The frame to inspect
- L49 _public member_ `TObjectPtr<UGeometryCache> DebugCache;` — `UPROPERTY(EditAnywhere, Category = Debug, meta = (EditCondition = "bDebug"))` — The output sequence
- L52 _public member_ `float TimeStep = 1.f / 30;` — `UPROPERTY(EditAnywhere, Category = "Simulation Settings", meta = (Min = 0))`
- L55 _public member_ `int32 NumSteps = 200;` — `UPROPERTY(EditAnywhere, Category = "Simulation Settings", meta = (Min = 0))`
- L58 _public member_ `int32 NumThreads = 1;` — `UPROPERTY(EditAnywhere, Category = "Simulation Settings", meta = (Min = 1, EditCondition = "!bDebug"))`

### `Plugins/Animation/MLDeformer/ChaosClothGenerator/Source/ChaosClothGenerator/Private/SClothGeneratorWidget.h` (Private)


#### class `UE::Chaos::ClothGenerator::SClothGeneratorWidget`  
`class SClothGeneratorWidget : public SCompoundWidget`  
_L14-27_
- inherits: `SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(SClothGeneratorWidget)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `TWeakObjectPtr<UClothGeneratorProperties> GetProperties() const;`
- L25 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L26 _private member_ `TSharedPtr<FChaosClothGenerator> ChaosClothGenerator;`

#### class `UE::Chaos::ClothGenerator::FClothGeneratorDetails`  
`class FClothGeneratorDetails : public IDetailCustomization`  
_L29-34_
- inherits: `IDetailCustomization`
- L32 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Chaos` (scope `UE`)
- L10 _namespace_ `namespace ClothGenerator` (scope `UE::Chaos`)
