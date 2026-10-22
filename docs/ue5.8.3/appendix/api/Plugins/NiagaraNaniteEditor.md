# Plugins / NiagaraNaniteEditor

- module root: `Plugins/FX/NiagaraNanite/Source/NiagaraNaniteEditor`
- headers: 2; symbols: 6
- symbol kinds: class=1, member=1, namespace=1, prototype=3
- PublicDependencyModuleNames: AssetTools, Core, CoreUObject, EditorFramework, Engine, GraphEditor, InputCore, Niagara, NiagaraEditor, NiagaraNanite, RHI, RenderCore, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/FX/NiagaraNanite/Source/NiagaraNaniteEditor/Private/Customizations/NiagaraParameterComponentBindingCustomization.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace FNiagaraFloatParameterComponentBindingCustomization`
- L9 _prototype_ `TSharedRef<IPropertyTypeCustomization> MakeInstance();` (scope `FNiagaraFloatParameterComponentBindingCustomization`)

### `Plugins/FX/NiagaraNanite/Source/NiagaraNaniteEditor/Private/NiagaraNaniteEditorModule.h` (Private)


#### class `FNiagaraNaniteEditorModule`  
`class FNiagaraNaniteEditorModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FName NiagaraFloatParameterComponentBindingName;`
