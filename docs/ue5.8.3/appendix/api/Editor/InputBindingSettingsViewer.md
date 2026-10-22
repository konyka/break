# Editor / InputBindingSettingsViewer

- module root: `Source/Editor/InputBindingSettingsViewer`
- headers: 1; symbols: 9
- symbol kinds: class=1, member=3, prototype=5
- PrivateDependencyModuleNames: CoreUObject, EditorFramework, Engine, SettingsEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Source/Editor/InputBindingSettingsViewer/Private/InputBindingSettingsViewerModule.h` (Private)


#### class `FInputBindingSettingsViewerModule`  
`class FInputBindingSettingsViewerModule : public IModuleInterface , public ISettingsViewer`  
_L15-37_
- inherits: `IModuleInterface,ISettingsViewer`
- desc: Used for all editor inputs (keyboard shortcuts, ...)
- L20 _public member_ `static const FLazyName SettingsTabName;`
- L21 _public member_ `static const FLazyName ContainerName;`
- L24 _public prototype_ `virtual void ShowSettings(const FName& InCategoryName, const FName& InSectionName) override;`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L34 _private prototype_ `TSharedRef<SDockTab> HandleSpawnSettingsTab(const FSpawnTabArgs& InSpawnTabArgs);`
- L36 _private member_ `TWeakPtr<ISettingsEditorModel> SettingsEditorModelWeak;`
