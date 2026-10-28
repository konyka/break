# Plugins / AvalancheSVGEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheSVGEditor`
- headers: 2; symbols: 8
- symbol kinds: class=2, prototype=6
- PrivateDependencyModuleNames: ActorModifierCore, AvalancheInteractiveTools, AvalancheModifiers, Core, CoreUObject, Engine, InteractiveToolsFramework, SVGImporter, SVGImporterEditor, Slate, SlateCore, ToolMenus

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSVGEditor/Private/AvaSVGEditorModule.h` (Private)


#### class `FAvaSVGEditorModule`  
`class FAvaSVGEditorModule : public IModuleInterface`  
_L15-24_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private prototype_ `void OnSVGActorSplit(ASVGShapesParentActor* InSVGShapesParent);`
- L23 _private prototype_ `void OnSVGShapesUpdated(AActor* InActor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSVGEditor/Private/Tool/AvaSVGActorTool.h` (Private)


#### class `UAvaSVGActorTool`  
`class UAvaSVGActorTool : public UAvaInteractiveToolsActorPointToolBase`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L14 _public prototype_ `UAvaSVGActorTool();`
- L17 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`
