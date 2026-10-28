# Plugins / InstancedActorsEditor

- module root: `Plugins/Runtime/InstancedActors/Source/InstancedActorsEditor`
- headers: 2; symbols: 24
- symbol kinds: class=2, delegate=1, macro=2, member=6, prototype=13
- PublicDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, InstancedActors, LevelEditor, MassCore, MassEntity, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/InstancedActors/Source/InstancedActorsEditor/Public/InstancedActorsEditorModule.h` (Public)


#### class `FInstancedActorsEditorModule`  
`class FInstancedActorsEditorModule : public IModuleInterface`  
_L25-71_
- inherits: `IModuleInterface`
- desc: The public interface to this module This module contains logic for converting between AActors and Instanced Actors. @todo move to a dedicated class
- L28 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnConvert, TConstArrayView<AActor*>);`
- L31 _public prototype_ `void CustomizedConvertActorsToIAsUIAction(TConstArrayView<AActor*> InActors, TSubclassOf<UInstancedActorsSubsystem> IASubsystemClass) const;` — Convert selected actors to Instance Actors (IAs) while using the IASubsystemClass
- L38 _public prototype_ `void SetIAToActorDelegate(const FOnConvert& InDelegate, const FTextFormat& ActionFormatLabelOverride = FTextFormat());` — Sets InDelegate as the delegate that will be executed as "Convert Instanced Actors to regular Actors" action. @param ActionFormatLabelOverride if supplied will be used to override the default action label. Note that this is a format string and needs to require one parameter, the Actor's name
- L45 _public prototype_ `void SetActorToIADelegate(const FOnConvert& InDelegate, const FTextFormat& ActionFormatLabelOverride = FTextFormat());` — Sets InDelegate as the delegate that will be executed as "Convert Actors to Instanced Actors" action. @param ActionFormatLabelOverride if supplied will be used to override the default action label. Note that this is a format string and needs to require one parameter, the Actor's name
- L48 _public prototype_ `void ResetConversionDelegates();` — Resets FOnConvert delegates and action labels to their defaults
- L52 _protected prototype_ `virtual void StartupModule() override;`
- L53 _protected prototype_ `virtual void ShutdownModule() override;`
- L56 _protected prototype_ `void ConvertActorsToIAsUIAction(TConstArrayView<AActor*> InActors) const;` — Convert selected actors to Instance Actors (IAs).
- L59 _protected prototype_ `void ConvertIAsToActorsUIAction(TConstArrayView<AActor*> InActors) const;` — Convert selected Instance Actors to Actors.
- L61 _protected prototype_ `TSharedRef<FExtender> CreateLevelViewportContextMenuExtender(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> InActors);`
- L62 _protected prototype_ `void AddLevelViewportMenuExtender();`
- L63 _protected prototype_ `void RemoveLevelViewportMenuExtender();`
- L65 _protected member_ `FDelegateHandle LevelViewportExtenderHandle;`
- L66 _protected member_ `FOnConvert ActorToIADelegate;`
- L67 _protected member_ `FOnConvert IAToActorDelegate;`
- L68 _protected member_ `FText CustomizedLabelPrefix;`
- L69 _protected member_ `FTextFormat ActorToIAFormatLabel;`
- L70 _protected member_ `FTextFormat IAToActorFormatLabel;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INSTANCEDACTORSEDITOR_API`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnConvert, TConstArrayView<AActor*>);`

### `Plugins/Runtime/InstancedActors/Source/InstancedActorsEditor/Public/InstancedActorsEditorSubsystem.h` (Public)


#### class `UInstancedActorsEditorSubsystem`  
`class UInstancedActorsEditorSubsystem : public UEditorSubsystem`  
_L19-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Subsystem for exposing instanced actors functionality to blueprints
- L26 _public prototype_ `static FInstancedActorsInstanceHandle GetInstanceHandle(UInstancedActorsData* InstanceData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "InstancedActors", meta = (DisplayName = "Get Instance Handle (by Index)"))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INSTANCEDACTORSEDITOR_API`
