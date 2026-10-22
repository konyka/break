# Plugins / DataChartsEditor

- module root: `Plugins/VirtualProduction/DataCharts/Source/DataChartsEditor`
- headers: 3; symbols: 11
- symbol kinds: class=3, function=1, member=1, prototype=6
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore, UnrealEd

### `Plugins/VirtualProduction/DataCharts/Source/DataChartsEditor/Private/DataChartsEditor.h` (Private)


#### class `FDataChartsEditorModule`  
`class FDataChartsEditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/DataCharts/Source/DataChartsEditor/Private/DataChartsPlacement.h` (Private)


#### class `FDataChartsPlacement`  
`class FDataChartsPlacement`  
_L6-11_
- L9 _public prototype_ `static void RegisterPlacement();`
- L10 _public prototype_ `static void UnregisterPlacement();`

### `Plugins/VirtualProduction/DataCharts/Source/DataChartsEditor/Private/DataChartsStyle.h` (Private)


#### class `FDataChartsStyle`  
`class FDataChartsStyle`  
_L9-18_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L17 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`
