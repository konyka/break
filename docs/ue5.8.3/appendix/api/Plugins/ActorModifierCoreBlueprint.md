# Plugins / ActorModifierCoreBlueprint

- module root: `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreBlueprint`
- headers: 1; symbols: 4
- symbol kinds: class=1, prototype=3
- PrivateDependencyModuleNames: ActorModifierCore
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, SlateCore

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCoreBlueprint/Public/ActorModifierCoreBlueprint.h` (Public)


#### class `UActorModifierCoreBlueprint`  
`class UActorModifierCoreBlueprint : public UBlueprint`  
_L12-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprint`
- desc: Blueprint object that defines a user modifier
- L18 _private prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L19 _private prototype_ `virtual void GetReparentingRules(TSet<const UClass*>& OutAllowedChildrenOfClasses, TSet<const UClass*>& OutDisallowedChildrenOfClasses) const override;`
- L20 _private prototype_ `virtual bool SupportedByDefaultBlueprintFactory() const override;`
