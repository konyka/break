# Plugins / MassGameplayEditor

- module root: `Plugins/Runtime/MassGameplay/Source/MassGameplayEditor`
- headers: 4; symbols: 43
- symbol kinds: class=5, function=1, macro=2, member=11, namespace=3, prototype=17, struct=3, typedef=1
- PrivateDependencyModuleNames: AIGraph, DataValidation, GraphEditor, KismetWidgets, PropertyEditor, RenderCore, ToolMenus
- PublicDependencyModuleNames: AssetTools, ComponentVisualizers, Core, CoreUObject, DetailCustomizations, EditorSubsystem, Engine, InputCore, MassActors, MassCore, MassEntity, MassEntityEditor, MassSpawner, Projects, PropertyEditor, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/MassGameplay/Source/MassGameplayEditor/Public/IMassGameplayEditor.h` (Public)


#### class `IMassGameplayEditor`  
`class IMassGameplayEditor : public FAssetEditorToolkit`  
_L10-13_
- inherits: `FAssetEditorToolkit`
- desc: Mass Editor public interface

### `Plugins/Runtime/MassGameplay/Source/MassGameplayEditor/Public/MassActorEditorSubsystem.h` (Public)


#### class `UMassActorEditorSubsystem`  
`class UMassActorEditorSubsystem : public UEditorSubsystem`  
_L14-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L19 _public function_ `FMassActorManager& GetMutableActorManager()`
- L22 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L24 _protected member_ `TSharedPtr<FMassActorManager> ActorManager;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSGAMEPLAYEDITOR_API`

### `Plugins/Runtime/MassGameplay/Source/MassGameplayEditor/Public/MassGameplayEditorModule.h` (Public)


#### class `FMassGameplayEditorModule`  
`class FMassGameplayEditorModule : public IModuleInterface`  
_L12-20_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _protected prototype_ `void RegisterSectionMappings();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MASSGAMEPLAYEDITOR_API`

### `Plugins/Runtime/MassGameplay/Source/MassGameplayEditor/Public/MassTraitRepository.h` (Public)


#### struct `FMassTraitInspectionContext`  
`struct FMassTraitInspectionContext`  
_L22-35_
- L31 _public prototype_ `FMassTraitInspectionContext();`
- L33 _public member_ `FMassEntityTemplateData EntityTemplate;`
- L34 _public member_ `FInvestigationContext BuildContext;`

#### struct `FMassTraitInspectionContext::FInvestigationContext`  
`struct FInvestigationContext : public FMassEntityTemplateBuildContext`  
_L24-29_
- inherits: `FMassEntityTemplateBuildContext`
- L26 _public typedef_ `using Super = FMassEntityTemplateBuildContext;`
- L27 _public prototype_ `explicit FInvestigationContext(FMassEntityTemplateData& InTemplate);`
- L28 _public prototype_ `void SetTrait(const UMassEntityTraitBase& Trait);`

#### class `UMassTraitRepository`  
`class UMassTraitRepository : public UEditorSubsystem`  
_L43-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Subsystem to store information about Mass traits so that we can make helpful suggestions to users like which traits supply a fragment they need. It also serves to post trait validation information and fix options to the MessageLog.
- L48 _public prototype_ `static UWorld* GetInvestigationWorld();`
- L50 _public prototype_ `TConstArrayView<FName> GetTraitsNameAddingElements(const FName ElementName);`
- L51 _public prototype_ `TWeakObjectPtr<UClass> GetTraitClass(const FName TraitClassName) const;`
- L54 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L55 _protected prototype_ `virtual void Deinitialize() override;`
- L62 _protected prototype_ `void OnNewTraitType(UMassEntityTraitBase& Trait);` — Note that the function does nothing until InitRepository is called. This is done to avoid collecting trait data until it's actually necessary.
- L64 _protected prototype_ `void OnDebugEvent(const FName EventName, FConstStructView Payload, EMassDebugMessageSeverity SeverityOverride);`
- L71 _protected prototype_ `void InitRepository();` — The method gathers all existing trait classes and processed them. We don't do that on subsystem's init since very often the data won't be needed during the given editor run. We call the function lazily the first time the data is needed.
- L73 _protected member_ `FDelegateHandle OnNewTraitTypeHandle;`
- L79 _protected member_ `TMap<FName, FTraitAndElements> TraitClassNameToDataMap;`
- L80 _protected member_ `TMap<FName, TArray<FName>> ElementTypeToTraitMap;`
- L85 _protected member_ `TObjectPtr<UWorld> InvestigationWorld;` — `UPROPERTY()` — the World we use to host all the subsystems required to process traits
- L88 _protected member_ `bool bIsRepositoryInitialized;` — We initialize the repository's data lazily and this property indicates whether it has been already done.
- L90 _protected member_ `static TWeakObjectPtr<UWorld> GlobalInvestigationWorld;`

#### struct `UMassTraitRepository::FTraitAndElements`  
`struct FTraitAndElements`  
_L74-78_
- L76 _public member_ `TWeakObjectPtr<UClass> TraitClass;`
- L77 _public member_ `TArray<FName> ElementNames;`

#### class `UMassDebugEntitySubsystem`  
`class UMassDebugEntitySubsystem : public UMassEntitySubsystem`  
_L95-100_
- reflection: `UCLASS()`
- inherits: `UMassEntitySubsystem`
- L99 _private prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mass` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::Mass`)
- L19 _prototype_ `extern TConstArrayView<FName> GetTraitsNameAddingElements(const FName ElementName);` (scope `UE::Mass::Editor`)
