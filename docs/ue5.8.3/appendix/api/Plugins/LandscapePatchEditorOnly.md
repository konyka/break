# Plugins / LandscapePatchEditorOnly

- module root: `Plugins/Editor/LandscapePatch/Source/LandscapePatchEditorOnly`
- headers: 3; symbols: 14
- symbol kinds: class=3, macro=1, member=3, prototype=7
- PrivateDependencyModuleNames: Engine, LandscapePatch, Projects, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Editor/LandscapePatch/Source/LandscapePatchEditorOnly/Private/LandscapePatchUIStyle.h` (Private)


#### class `FLandscapePatchUIStyle`  
`class FLandscapePatchUIStyle`  
_L7-20_
- L10 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L19 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;`

### `Plugins/Editor/LandscapePatch/Source/LandscapePatchEditorOnly/Private/LandscapeTexturePatchVisualizer.h` (Private)


#### class `FLandscapeTexturePatchVisualizer`  
`class FLandscapeTexturePatchVisualizer : public FComponentVisualizer`  
_L13-17_
- inherits: `FComponentVisualizer`
- desc: Adds a rectangle denoting the area covered by a landscape texture patch when it is selected in editor.
- L16 _private prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LANDSCAPEPATCHEDITORONLY_API`

### `Plugins/Editor/LandscapePatch/Source/LandscapePatchEditorOnly/Public/LandscapePatchEditorOnlyModule.h` (Public)


#### class `FLandscapePatchEditorOnlyModule`  
`class FLandscapePatchEditorOnlyModule : public IModuleInterface`  
_L8-20_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L19 _private member_ `TArray<FName> VisualizersToUnregisterOnShutdown;`
