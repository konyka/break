# Plugins / UAFMass

- module root: `Plugins/Experimental/UAF/UAFMass/Source/UAFMass`
- headers: 10; symbols: 68
- symbol kinds: class=9, delegate=1, enum=3, enumerator=4, member=16, namespace=3, prototype=24, struct=7, variable=1
- PrivateDependencyModuleNames: CoreUObject, Engine, MassCharacterTrajectory, MassCore, MassEntity, MassSimulation, MassSpawner, RigVM
- PublicDependencyModuleNames: Core, MassCommon, UAF

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Fragments/CharacterTrajectoryUAFFragments.h` (Private)


#### struct `FCharacterTrajectoryUAFData`  
`struct FCharacterTrajectoryUAFData : public FMassConstSharedFragment`  
_L11-30_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Variable name references used by UCharacterTrajectoryToUAFProcessor to write trajectory data to UAF components.
- L17 _public member_ `FName PoseVariableName = TEXT("Tra` — `UPROPERTY(EditAnywhere, Category = "UAF")` — The name of the trajectory variable to set on the UAF component
- L21 _public member_ `FName SteeringVariableName = TEXT("Tar` — `UPROPERTY(EditAnywhere, Category = "UAF")` — The name of the target orientation variable to set on the UAF component
- L25 _public member_ `FName RootWorldTransformVariableName = TEXT("Mes` — `UPROPERTY(EditAnywhere, Category = "UAF")` — The name of the root world transform variable to set on the UAF component
- L29 _public member_ `FName DeltaTransformVariableName = TEXT("Del` — `UPROPERTY(EditAnywhere, Category = "UAF")` — The name of the delta transform variable to set on the UAF component

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Fragments/MassUAFFragment.h` (Private)


#### struct `FMassUAFFragment`  
`struct FMassUAFFragment : public FObjectWrapperFragment`  
_L15-23_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- desc: Fragment owning the UAF system associated to the entity.
- L20 _public member_ `TInstancedStruct<FUAFSystemFactoryAsset> Asset;` — `UPROPERTY(transient)` — @TODO: We don't need this data after UAF system creation. Remove this when we figure out the correct init flow i.e. shared/chunk fragment or Subsystem ownership.
- L22 _public member_ `UE::UAF::FSystemReference SystemReference;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMassUAFFragment> : public TStructOpsTypeTraitsBase2<FMassUAFFragment>`  
_L26-32_
- inherits: `TStructOpsTypeTraitsBase2<FMassUAFFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L29-31_

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassUAFFragment> final`  
_L35-41_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L38-40_

#### Free symbols / members of external scopes

- L30 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon8956c8e70103`)
- L39 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon8956c8e70203`)

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Module/RigVMTrait_ModuleEventDependency_MassPhaseProcessor.h` (Private)


#### struct `FRigVMTrait_ModuleEventDependency_MassPhaseProcessor`  
`struct FRigVMTrait_ModuleEventDependency_MassPhaseProcessor : public FRigVMTrait_ModuleEventDependency`  
_L13-30_
- reflection: `USTRUCT(DisplayName = "Mass Phase Processor", meta = (ShowTooltip = true))`
- inherits: `FRigVMTrait_ModuleEventDependency`
- desc: A dependency on one of a mass phase processors (equates to a tick function)
- L19 _public prototype_ `virtual FString GetDisplayName() const override;`
- L23 _public prototype_ `virtual void OnAddDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;` — FAnimNextModuleEventDependency interface
- L24 _public prototype_ `virtual void OnRemoveDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;`
- L29 _public member_ `EMassProcessingPhase DependentMassPhase = EMassProcessingPhase::PrePhysics;` — `UPROPERTY(EditAnywhere, Category = "Dependency")` — The Mass processing phase that this dependency relates to

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Processors/CharacterTrajectoryToUAFProcessor.h` (Private)


#### class `UCharacterTrajectoryToUAFProcessor`  
`class UCharacterTrajectoryToUAFProcessor : public UMassProcessor`  
_L17-29_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L22 _public prototype_ `UCharacterTrajectoryToUAFProcessor();`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L28 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mass` (scope `UE`)
- L11 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L13 _variable_ `inline const FName CharacterTrajectoryToUAF = FName(TEXT("Char` (scope `UE::Mass::ProcessorGroupNames`)

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Processors/MassUAFProcessor.h` (Private)


#### class `UMassUAFInitializer`  
`class UMassUAFInitializer : public UMassObserverProcessor`  
_L14-26_
- reflection: `UCLASS()`
- inherits: `UMassObserverProcessor`
- L19 _public prototype_ `UMassUAFInitializer();`
- L22 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L23 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L25 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassUAFProcessor`  
`class UMassUAFProcessor : public UMassProcessor`  
_L30-42_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L35 _public prototype_ `UMassUAFProcessor();`
- L38 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L39 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L41 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassAnimPoseDebugProcessor`  
`class UMassAnimPoseDebugProcessor : public UMassProcessor`  
_L45-57_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L50 _public prototype_ `UMassAnimPoseDebugProcessor();`
- L53 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L54 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L56 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassUAFDestructor`  
`class UMassUAFDestructor : public UMassObserverProcessor`  
_L60-72_
- reflection: `UCLASS()`
- inherits: `UMassObserverProcessor`
- L65 _public prototype_ `UMassUAFDestructor();`
- L68 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L69 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L71 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassUAF, Display, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassUAF, Display, All);`

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Subsystems/MassUAFSubsystem.h` (Private)


#### class `UMassUAFSubsystem`  
`class UMassUAFSubsystem : public UMassSubsystemBase`  
_L14-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: @TODO: Dummy subsystem used as UObject owner of Mass - owned UAF systems. Remove this when we have proper ownership of UAF system + per-entity rewind debugger support.

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassUAFSubsystem> final`  
_L20-27_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L23-26_

#### Free symbols / members of external scopes

- L24 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anona69fdd5d0103`)
- L25 _enumerator_ `ThreadSafeWrite = true` (scope `TMassExternalSubsystemTraits::__anona69fdd5d0103`)

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Traits/CharacterTrajectoryUAFTrait.h` (Private)


#### class `UCharacterTrajectoryUAFTrait`  
`class UCharacterTrajectoryUAFTrait : public UMassEntityTraitBase`  
_L14-23_
- reflection: `UCLASS(EditInlineNew, CollapseCategories, meta = (DisplayName = "Character Trajectory UAF Setup"))`
- inherits: `UMassEntityTraitBase`
- desc: This trait adds the UAF component wrapper and configures variable name references used by UCharacterTrajectoryToUAFProcessor. It should be used alongside UCharacterTrajectoryTrait when UAF integration is needed.
- L19 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L22 _protected member_ `FCharacterTrajectoryUAFData UAFData;` — `UPROPERTY(Category = "UAF", EditAnywhere)`

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Private/Traits/MassUAFTrait.h` (Private)


#### class `UMassUAFTrait`  
`class UMassUAFTrait : public UMassEntityTraitBase`  
_L12-32_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Mass UAF Trait"))`
- inherits: `UMassEntityTraitBase`
- L17 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L23 _private member_ `TObjectPtr<const UObject> Asset_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.8, "Use AssetData instead")` — `UPROPERTY()` — The asset that this Mass Entity will run in UAF
- L28 _private member_ `TInstancedStruct<FUAFSystemFactoryAsset> AssetData;` — `UPROPERTY(EditAnywhere, Category = "Asset", DisplayName = "Asset")` — The asset that this Mass Entity will run in UAF
- L31 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Public/Fragments/MassUAFComponentFragment.h` (Public)


#### struct `FMassUAFComponentWrapperFragment`  
`struct FMassUAFComponentWrapperFragment : public FObjectWrapperFragment`  
_L12-16_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L15 _public member_ `TWeakObjectPtr<UUAFComponent> Component;`

### `Plugins/Experimental/UAF/UAFMass/Source/UAFMass/Public/UAFMassModule.h` (Public)


#### class `FUAFMassModule`  
`class FUAFMassModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
