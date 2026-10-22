# Plugins / CompositePlane

- module root: `Plugins/VirtualProduction/CompositePlane/Source/CompositePlane`
- headers: 2; symbols: 6
- symbol kinds: class=2, prototype=4
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore, UnrealEd

### `Plugins/VirtualProduction/CompositePlane/Source/CompositePlane/Private/CompositePlane.h` (Private)


#### class `FCompositePlaneModule`  
`class FCompositePlaneModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/CompositePlane/Source/CompositePlane/Private/CompositePlanePlacement.h` (Private)


#### class `FCompositePlanePlacement`  
`class FCompositePlanePlacement`  
_L5-10_
- L8 _public prototype_ `static void RegisterPlacement();`
- L9 _public prototype_ `static void UnregisterPlacement();`
