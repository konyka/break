# Plugins / MoverEditor

- module root: `Plugins/Experimental/Mover/Source/MoverEditor`
- headers: 1; symbols: 5
- symbol kinds: class=1, prototype=4
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: BlueprintGraph, Core, Mover

### `Plugins/Experimental/Mover/Source/MoverEditor/Public/K2Node_PlayMontageOnMoverActor.h` (Public)


#### class `UK2Node_PlayMontageOnMoverActor`  
`class UK2Node_PlayMontageOnMoverActor : public UK2Node_BaseAsyncTask`  
_L19-32_
- reflection: `UCLASS()`
- inherits: `UK2Node_BaseAsyncTask`
- desc: PlayMontageOnMoverActor: used for playing montages on Mover-based actors. Handles the montage's root motion separately from the animation pose.
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L30 _private prototype_ `virtual FText GetMenuCategory() const override;`
