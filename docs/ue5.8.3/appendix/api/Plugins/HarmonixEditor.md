# Plugins / HarmonixEditor

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixEditor`
- headers: 2; symbols: 8
- symbol kinds: class=2, delegate=1, function=1, prototype=4
- PrivateDependencyModuleNames: EditorWidgets, Engine, Harmonix, InputCore, PropertyEditor, Settings, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Runtime/Harmonix/Source/HarmonixEditor/Private/Customization/HarmonixPluginSettingsCustomization.h` (Private)


#### class `FHarmonixPluginSettingsCustomization`  
`class FHarmonixPluginSettingsCustomization : public IDetailCustomization`  
_L11-21_
- inherits: `IDetailCustomization`
- L14 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Runtime/Harmonix/Source/HarmonixEditor/Public/HarmonixEditorModule.h` (Public)


#### class `FHarmonixEditorModule`  
`class FHarmonixEditorModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule();`
- L14 _public prototype_ `virtual void ShutdownModule();`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixEditor, Log, All);`
