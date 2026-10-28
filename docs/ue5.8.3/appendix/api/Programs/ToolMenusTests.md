# Programs / ToolMenusTests

- module root: `Source/Programs/ToolMenusTests`
- headers: 1; symbols: 5
- symbol kinds: class=1, function=2, member=1, prototype=1
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, Slate, SlateCore, ToolMenus

### `Source/Programs/ToolMenusTests/Private/CheckBoxStateObject.h` (Private)


#### class `UCheckBoxStateObject`  
`class UCheckBoxStateObject : public UObject`  
_L11-31_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public prototype_ `UCheckBoxStateObject() = default;`
- L18 _public function_ `void SetStateToReturn(const ECheckBoxState InState)`
- L24 _public function_ `ECheckBoxState GetActionCheckState(const FToolMenuContext& InContext) const` — `UFUNCTION()`
- L30 _private member_ `ECheckBoxState StateToReturn;`
