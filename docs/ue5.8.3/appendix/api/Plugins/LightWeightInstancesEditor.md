# Plugins / LightWeightInstancesEditor

- module root: `Plugins/LightWeightInstancesEditor/Source/LightWeightInstancesEditor`
- headers: 1; symbols: 8
- symbol kinds: class=1, member=1, prototype=6
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DataLayerEditor, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/LightWeightInstancesEditor/Source/LightWeightInstancesEditor/Public/LightWeightInstancesEditor.h` (Public)


#### class `FLightWeightInstancesEditorModule`  
`class FLightWeightInstancesEditorModule : public IModuleInterface`  
_L14-38_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _protected prototype_ `void AddLevelViewportMenuExtender();` — Adds new menu options related to LWIs
- L27 _protected prototype_ `void RemoveLevelViewportMenuExtender();` — Cleanup menu options related to LWIs
- L30 _protected prototype_ `TSharedRef<FExtender> CreateLevelViewportContextMenuExtender(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> InActors);`
- L33 _protected prototype_ `void ConvertActorsToLWIsUIAction(const TArray<AActor*> InActors) const;` — Converts InActors to light weight instances. InActors must all be the same type or conversion won't occur
- L36 _protected member_ `FDelegateHandle LevelViewportExtenderHandle;` — Delegates
