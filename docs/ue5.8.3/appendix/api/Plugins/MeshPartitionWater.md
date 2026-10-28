# Plugins / MeshPartitionWater

- module root: `Plugins/Experimental/MeshPartitionWater/Source/MeshPartitionWater`
- headers: 5; symbols: 47
- symbol kinds: class=5, delegate=1, function=1, macro=3, member=2, namespace=10, prototype=25
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CQTest, CoreUObject, DynamicMesh, Engine, GeometryAlgorithms, GeometryCore, UnrealEd
- PublicDependencyModuleNames: Core, MeshPartition, MeshPartitionEditor, Water

### `Plugins/Experimental/MeshPartitionWater/Source/MeshPartitionWater/Private/MeshPartitionLakeModifier.h` (Private)


#### class `UE::MeshPartition::ULakeModifier`  
`class ULakeModifier : public MeshPartition::UWaterModifier`  
_L26-36_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))`
- inherits: `MeshPartition::UWaterModifier`
- desc: Performs height-based MegaMesh deformation for Lakes
- L31 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L32 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPARTITIONWATER_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)
- L17 _namespace_ `namespace MegaMeshLakeModifierLocals` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartitionWater/Source/MeshPartitionWater/Private/MeshPartitionOceanModifier.h` (Private)


#### class `UE::MeshPartition::UOceanModifier`  
`class UOceanModifier : public MeshPartition::UWaterModifier`  
_L13-20_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))`
- inherits: `MeshPartition::UWaterModifier`
- L18 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartitionWater/Source/MeshPartitionWater/Private/MeshPartitionRiverModifier.h` (Private)


#### class `UE::MeshPartition::URiverModifier`  
`class URiverModifier : public MeshPartition::UWaterModifier`  
_L23-36_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))`
- inherits: `MeshPartition::UWaterModifier`
- desc: Performs height-based MegaMesh deformation for Rivers
- L27 _public prototype_ `URiverModifier();`
- L30 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L31 _public prototype_ `virtual TSharedPtr<const MeshPartition::IModifierBackgroundOp> CreateBackgroundOp(const MeshPartition::EBuildType InBuildType) const override;`
- L32 _public prototype_ `virtual FGuid GetCodeVersionKey() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONWATER_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)
- L14 _namespace_ `namespace MegaMeshRiverModifierLocals` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartitionWater/Source/MeshPartitionWater/Private/MeshPartitionWaterModule.h` (Private)


#### class `FMegaMeshWaterModule`  
`class FMegaMeshWaterModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMeshWater, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMeshWater, Log, All);`

### `Plugins/Experimental/MeshPartitionWater/Source/MeshPartitionWater/Public/MeshPartitionWaterModifier.h` (Public)


#### class `UE::MeshPartition::UWaterModifier`  
`class UWaterModifier : public MeshPartition::UModifierComponent`  
_L22-69_
- reflection: `UCLASS(MinimalAPI, Abstract, meta=(BlueprintSpawnableComponent))`
- inherits: `MeshPartition::UModifierComponent`
- desc: Base MegaMeshModifierComponent for all Water-MegaMesh interactions.
- L27 _public prototype_ `UWaterModifier();`
- L30 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L33 _public prototype_ `virtual void OnRegister() override;` — USceneComponent Implementation
- L34 _public prototype_ `virtual void OnUnregister() override;`
- L35 _public prototype_ `virtual void CheckForErrors() override;`
- L39 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`
- L40 _public prototype_ `virtual void PostProcessSection(AActor* InSection) override;`
- L43 _public prototype_ `bool IsEnabled() const;`
- L45 _public function_ `void SetMaxZDistance(const double InMaxZDistance)`
- L49 _protected prototype_ `void OnWaterBodyChanged(const IWaterBrushActorInterface::FWaterBrushActorChangedEventParams& OnBrushActorChanged);`
- L51 _protected prototype_ `static float CalculateVertexFalloffHeight(float& InOutInternalBlendWeight, bool bIsInside, float WaterHeight, float DistanceFromSpline, float TargetHeight, float MeshZ, const FWaterBodyHeightmapSettings& HeightmapSettings, const FWaterCurveSettings& CurveSettings);`
- L53 _protected prototype_ `static float CalculateVertexWeight(bool bIsInside, float DistanceFromSpline, const FWaterBodyWeightmapSettings& WeightmapSettings);` — helper to calculate basic weightmap alpha (not accounting for ModulationTexture)
- L55 _protected prototype_ `static void RegisterWaterWeightmaps(const TMap<FName, FWaterBodyWeightmapSettings>& WeightMaps, FInstanceInfo& Instance);` — helper to register water weightmaps
- L58 _protected prototype_ `AWaterBody* GetWaterBodyActor() const;` — Utilities functions to retrieve water components from the parent water body actor
- L59 _protected prototype_ `UWaterBodyComponent* GetWaterBodyComponent() const;`
- L60 _protected prototype_ `UWaterSplineComponent* GetWaterSpline() const;`
- L65 _protected member_ `double MaxZDistance = 10000.;` — `UPROPERTY(EditAnywhere, Category = Terrain)` — The maximum vertical distance this modifier will affect the terrain
- L68 _protected member_ `static FName InternalWaterWeightChannelName;` — Name of the weight channel used to pass height blend info between overlapping water modifiers

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONWATER_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)
