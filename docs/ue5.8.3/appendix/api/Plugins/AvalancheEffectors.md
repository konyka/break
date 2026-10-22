# Plugins / AvalancheEffectors

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectors`
- headers: 2; symbols: 14
- symbol kinds: class=2, member=2, prototype=10
- PrivateDependencyModuleNames: Avalanche, AvalancheCore, AvalancheOutliner, AvalancheSceneTree, ClonerEffector, Core, CoreUObject, Engine, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectors/Private/AvalancheEffectorsModule.h` (Private)


#### class `FAvalancheEffectorsModule`  
`class FAvalancheEffectorsModule : public IModuleInterface`  
_L13-23_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _protected prototype_ `static TSharedPtr<ICEClonerSceneTreeCustomResolver> CreateSceneTreeResolver(ULevel* InLevel);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectors/Private/AvalancheEffectorsSceneTreeResolver.h` (Private)


#### class `FAvaEffectorsSceneTreeResolver`  
`class FAvaEffectorsSceneTreeResolver : public ICEClonerSceneTreeCustomResolver`  
_L13-33_
- inherits: `ICEClonerSceneTreeCustomResolver`
- desc: This allows cloner to retrieve hierarchy of the Motion Design outliner and react accordingly
- L16 _public prototype_ `explicit FAvaEffectorsSceneTreeResolver(ULevel* InLevel);`
- L19 _public prototype_ `virtual void Activate() override;`
- L20 _public prototype_ `virtual void Deactivate() override;`
- L21 _public prototype_ `virtual bool GetDirectChildrenActor(AActor* InActor, TArray<AActor*>& OutActors) const override;`
- L22 _public prototype_ `virtual FOnActorHierarchyChanged::RegistrationType& OnActorHierarchyChanged() override;`
- L27 _private prototype_ `void OnOutlinerLoaded();`
- L28 _private prototype_ `void OnOutlinerHierarchyChanged(AActor* InActor, const AActor* InParent, EAvaOutlinerHierarchyChangeType InChange);`
- L31 _private member_ `FOnActorHierarchyChanged OnHierarchyChangedDelegate;`
- L32 _private member_ `TWeakObjectPtr<ULevel> LevelWeak;`
