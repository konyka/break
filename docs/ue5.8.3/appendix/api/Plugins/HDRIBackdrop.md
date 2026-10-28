# Plugins / HDRIBackdrop

- module root: `Plugins/Runtime/HDRIBackdrop/Source/HDRIBackdrop`
- headers: 3; symbols: 10
- symbol kinds: class=3, function=1, member=1, prototype=5
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/HDRIBackdrop/Source/HDRIBackdrop/Public/HDRIBackdrop.h` (Public)


#### class `FHDRIBackdropModule`  
`class FHDRIBackdropModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/HDRIBackdrop/Source/HDRIBackdrop/Public/HDRIBackdropPlacement.h` (Public)


#### class `FHDRIBackdropPlacement`  
`class FHDRIBackdropPlacement`  
_L7-11_
- L10 _public prototype_ `static void RegisterPlacement();`

### `Plugins/Runtime/HDRIBackdrop/Source/HDRIBackdrop/Public/HDRIBackdropStyle.h` (Public)


#### class `FHDRIBackdropStyle`  
`class FHDRIBackdropStyle`  
_L8-17_
- L11 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L13 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L16 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`
