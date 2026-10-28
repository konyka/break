# Editor / EditorSubsystem

- module root: `Source/Editor/EditorSubsystem`
- headers: 2; symbols: 5
- symbol kinds: class=2, macro=1, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Editor/EditorSubsystem/Public/EditorSubsystem.h` (Public)


#### class `UEditorSubsystem`  
`class UEditorSubsystem : public UDynamicSubsystem`  
_L20-23_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UDynamicSubsystem`
- desc: UEditorSubsystem Base class for auto instanced and initialized systems that share the lifetime of the Editor UEditorSubsystems are dynamic and will be initialized when the module is loaded if necessary. This means that after StartupModule() is called on the module containing a subsystem, the subsystem collection with instantiate and initialize the subsystem automatically. If the subsystem collection is created post module load then the instances will be created at collection initialization time.

### `Source/Editor/EditorSubsystem/Public/EditorSubsystemModule.h` (Public)


#### class `FEditorSubsystemModule`  
`class FEditorSubsystemModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API EDITORSUBSYSTEM_API`
