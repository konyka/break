# Plugins / GPULightmassEditor

- module root: `Plugins/Experimental/GPULightmass/Source/GPULightmassEditor`
- headers: 1; symbols: 21
- symbol kinds: class=1, member=5, prototype=14, struct=1
- PrivateDependencyModuleNames: CoreUObject, EditorStyle, Engine, GPULightmass, Landscape, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/GPULightmass/Source/GPULightmassEditor/Private/GPULightmassEditorModule.h` (Private)


#### class `FGPULightmassEditorModule`  
`class FGPULightmassEditorModule : public IModuleInterface`  
_L20-53_
- inherits: `IModuleInterface`
- L24 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public member_ `TSharedPtr<IDetailsView> SettingsView;`
- L28 _public prototype_ `TSharedRef<SDockTab> SpawnSettingsTab(const FSpawnTabArgs& Args);`
- L29 _public prototype_ `void UpdateSettingsTab();`
- L30 _public prototype_ `void RegisterTabSpawner();`
- L31 _public prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType MapChangeType);`
- L33 _public prototype_ `TSharedRef<FExtender> OnExtendLevelEditorBuildMenu(const TSharedRef<FUICommandList> CommandList);`
- L34 _public prototype_ `void CreateBuildMenu(FMenuBuilder& Builder);`
- L36 _public prototype_ `static bool IsRealtimeOn();`
- L37 _public prototype_ `static bool IsRunning();`
- L38 _public prototype_ `static bool IsBakeWhatYouSeeMode();`
- L40 _public prototype_ `FReply OnStartClicked();`
- L41 _public prototype_ `FReply OnSaveAndStopClicked();`
- L42 _public prototype_ `FReply OnCancelClicked();`
- L51 _private member_ `FMessage Message = {};`
- L52 _private member_ `TSharedPtr<STextBlock> MessageWidget;`

#### struct `FGPULightmassEditorModule::FMessage`  
`struct FMessage`  
_L45-49_
- L47 _public member_ `ELogVerbosity::Type Severity;`
- L48 _public member_ `FText Text;`
