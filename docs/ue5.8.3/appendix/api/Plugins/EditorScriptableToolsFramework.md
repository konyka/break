# Plugins / EditorScriptableToolsFramework

- module root: `Plugins/Runtime/ScriptableToolsFramework/Source/EditorScriptableToolsFramework`
- headers: 6; symbols: 34
- symbol kinds: class=7, delegate=3, macro=1, member=10, prototype=12, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Engine, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, GeometryCore, InteractiveToolsFramework, PhysicsCore, RenderCore, ScriptableToolsFramework

### `Plugins/Runtime/ScriptableToolsFramework/Source/EditorScriptableToolsFramework/Public/BaseTools/EditorScriptableClickDragTool.h` (Public)


#### class `UEditorScriptableClickDragTool`  
`class UEditorScriptableClickDragTool : public UScriptableClickDragTool`  
_L12-17_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable)`
- inherits: `UScriptableClickDragTool`
- desc: Editor-Only variant of UScriptableClickDragTool, which gives access to Editor-Only BP functions

### `Plugins/Runtime/ScriptableToolsFramework/Source/EditorScriptableToolsFramework/Public/BaseTools/EditorScriptableModularBehaviorTool.h` (Public)


#### class `UEditorScriptableModularBehaviorTool`  
`class UEditorScriptableModularBehaviorTool : public UScriptableModularBehaviorTool`  
_L12-17_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable)`
- inherits: `UScriptableModularBehaviorTool`
- desc: Editor-Only variant of UScriptableModularBehaviorTool, which gives access to Editor-Only BP functions

### `Plugins/Runtime/ScriptableToolsFramework/Source/EditorScriptableToolsFramework/Public/BaseTools/EditorScriptableSingleClickTool.h` (Public)


#### class `UEditorScriptableSingleClickTool`  
`class UEditorScriptableSingleClickTool : public UScriptableSingleClickTool`  
_L12-17_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable)`
- inherits: `UScriptableSingleClickTool`
- desc: Editor-Only variant of UScriptableSingleClickTool, which gives access to Editor-Only BP functions

### `Plugins/Runtime/ScriptableToolsFramework/Source/EditorScriptableToolsFramework/Public/EditorScriptableInteractiveTool.h` (Public)


#### class `UEditorScriptableInteractiveTool`  
`class UEditorScriptableInteractiveTool : public UScriptableInteractiveTool`  
_L12-17_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable)`
- inherits: `UScriptableInteractiveTool`
- desc: Editor-Only variant of UScriptableInteractiveTool, which gives access to Editor-Only BP functions

#### class `UEditorScriptableInteractiveToolPropertySet`  
`class UEditorScriptableInteractiveToolPropertySet : public UScriptableInteractiveToolPropertySet`  
_L21-26_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable)`
- inherits: `UScriptableInteractiveToolPropertySet`

### `Plugins/Runtime/ScriptableToolsFramework/Source/EditorScriptableToolsFramework/Public/EditorScriptableToolsFrameworkModule.h` (Public)


#### class `FEditorScriptableToolsFrameworkModule`  
`class FEditorScriptableToolsFrameworkModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/ScriptableToolsFramework/Source/EditorScriptableToolsFramework/Public/ScriptableToolSet.h` (Public)


#### class `UScriptableToolSet`  
`class UScriptableToolSet : public UObject`  
_L23-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: UScriptableToolSet represents a set of UScriptableInteractiveTool types.
- L29 _public prototype_ `UScriptableToolSet();`
- L31 _public prototype_ `virtual ~UScriptableToolSet();`
- L36 _public prototype_ `void UnloadAllTools();` — Forces the unloading of all tools loaded
- L42 _public prototype_ `void ReinitializeScriptableTools(FPreToolsLoadedDelegate PreDelegate, FToolsLoadedDelegate PostDelegate, FToolsLoadingUpdateDelegate UpdateDelegate, FScriptableToolGroupSet* TagsToFilter = nullptr);` — Find all UScriptableInteractiveTool classes in the current project. (Currently no support for filtering/etc)
- L47 _public prototype_ `void ForEachScriptableTool( TFunctionRef<void(UClass* ToolClass, UBaseScriptableToolBuilder* ToolBuilder)> ProcessToolFunc);` — Allow external code to process each UScriptableInteractiveTool in the current ToolSet
- L52 _private prototype_ `void HandleAssetCanDelete(const TArray<UObject*>& InObjectsToDelete, FCanDeleteAssetResult& OutCanDelete);`
- L54 _private prototype_ `void PostToolLoad(FToolsLoadedDelegate Delegate, TArray< FSoftObjectPath > ObjectsLoaded, TSharedPtr<FScriptableToolGroupSet> TagsToFilter);`
- L56 _private member_ `bool bActiveLoading = false;`
- L57 _private member_ `TSharedPtr<FStreamableHandle> AsyncLoadHandle;`
- L59 _private member_ `FDelegateHandle AssetCanDeleteHandle;`
- L69 _private member_ `TArray<FScriptableToolInfo> Tools;`
- L72 _private member_ `TArray<TObjectPtr<UBaseScriptableToolBuilder>> ToolBuilders;` — `UPROPERTY()`

#### struct `UScriptableToolSet::FScriptableToolInfo`  
`struct FScriptableToolInfo`  
_L61-68_
- L63 _public member_ `FString ToolPath;`
- L64 _public member_ `FString BuilderPath;`
- L65 _public member_ `TWeakObjectPtr<UClass> ToolClass = nullptr;`
- L66 _public member_ `TWeakObjectPtr<UScriptableInteractiveTool> ToolCDO;`
- L67 _public member_ `TWeakObjectPtr<UBaseScriptableToolBuilder> ToolBuilder;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API EDITORSCRIPTABLETOOLSFRAMEWORK_API`
- L16 _delegate_ `DECLARE_DELEGATE(FPreToolsLoadedDelegate);`
- L16 _prototype_ `DECLARE_DELEGATE(FPreToolsLoadedDelegate);`
- L17 _delegate_ `DECLARE_DELEGATE(FToolsLoadedDelegate);`
- L17 _prototype_ `DECLARE_DELEGATE(FToolsLoadedDelegate);`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FToolsLoadingUpdateDelegate, TSharedRef<struct FStreamableHandle>);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FToolsLoadingUpdateDelegate, TSharedRef<struct FStreamableHandle>);`
