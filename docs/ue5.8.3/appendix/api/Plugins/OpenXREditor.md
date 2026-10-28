# Plugins / OpenXREditor

- module root: `Plugins/Runtime/OpenXR/Source/OpenXREditor`
- headers: 2; symbols: 7
- symbol kinds: class=2, function=1, macro=2, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, OpenXRHMD, OpenXRInput, UnrealEd

### `Plugins/Runtime/OpenXR/Source/OpenXREditor/Private/OpenXREditorModule.h` (Private)


#### class `FOpenXREditorModule`  
`class FOpenXREditorModule : public IOpenXREditorModule`  
_L11-19_
- inherits: `IOpenXREditorModule`
- L14 _public function_ `FOpenXREditorModule()`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define OPENXR_EDITOR_MODULE_NAME "OpenXREditor"`

### `Plugins/Runtime/OpenXR/Source/OpenXREditor/Public/IOpenXREditorModule.h` (Public)


#### class `IOpenXREditorModule`  
`class IOpenXREditorModule : public IModuleInterface`  
_L13-15_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _macro_ `#define OPENXR_EDITOR_MODULE_NAME "OpenXREditor"`
