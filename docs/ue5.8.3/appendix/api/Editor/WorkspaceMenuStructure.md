# Editor / WorkspaceMenuStructure

- module root: `Source/Editor/WorkspaceMenuStructure`
- headers: 2; symbols: 32
- symbol kinds: class=2, function=2, member=1, namespace=1, prototype=26
- PrivateDependencyModuleNames: Core, Slate, SlateCore
- PublicDependencyModuleNames: EditorStyle

### `Source/Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h` (Public)


#### class `IWorkspaceMenuStructure`  
`class IWorkspaceMenuStructure`  
_L28-90_
- L32 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetStructureRoot() const = 0;` — Get the root of the menu structure. Pass this into PopulateTabSpawnerMenu()
- L35 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetToolsStructureRoot() const = 0;` — Alternate root for the Tools menu
- L38 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorCategory() const = 0;` — See diagram above
- L41 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorViewportsCategory() const = 0;` — See diagram above
- L44 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorDetailsCategory() const = 0;` — See diagram above
- L47 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorCinematicsCategory() const = 0;` — See diagram above
- L50 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorMediaCategory() const = 0;` — See diagram above
- L53 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorVirtualProductionCategory() const = 0;` — See diagram above
- L56 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorWorldPartitionCategory() const = 0;` — See diagram above
- L59 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorOutlinerCategory() const = 0;` — See diagram above
- L62 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetLevelEditorModesCategory() const = 0;` — See diagram above
- L65 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetToolsCategory() const = 0;` — See diagram above
- L68 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetDeveloperToolsDebugCategory() const = 0;` — See diagram above
- L71 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetDeveloperToolsLogCategory() const = 0;` — See diagram above
- L74 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetDeveloperToolsProfilingCategory() const = 0;` — See diagram above
- L77 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetDeveloperToolsAuditCategory() const = 0;` — See diagram above
- L80 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetDeveloperToolsPlatformsCategory() const = 0;` — See diagram above
- L83 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetDeveloperToolsMiscCategory() const = 0;` — See diagram above
- L86 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetAutomationToolsCategory() const = 0;` — See diagram above
- L89 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetEditOptions() const = 0;` — Get the root of the edit menu structure. Pass this into PopulateTabSpawnerMenu()

### `Source/Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h` (Public)


#### class `FWorkspaceMenuStructureModule`  
`class FWorkspaceMenuStructureModule : public IModuleInterface`  
_L17-39_
- inherits: `IModuleInterface`
- desc: The module that defines a structure of the workspace menu. Tab spawners place themselves into one of the categories/groups in this structure upon registration.
- L22 _public prototype_ `virtual ~FWorkspaceMenuStructureModule() = default;`
- L24 _public prototype_ `virtual void StartupModule();`
- L26 _public prototype_ `virtual void ShutdownModule();`
- L29 _public prototype_ `virtual const IWorkspaceMenuStructure& GetWorkspaceMenuStructure() const;` — @return The menu structure that is populated by tab spawners
- L32 _public prototype_ `virtual void ResetLevelEditorCategory();` — Reset the "Level Editor" category to its default state
- L35 _public prototype_ `virtual void ResetToolsCategory();` — Reset the "Tools" category to its default state
- L38 _private member_ `TSharedPtr<class FWorkspaceMenuStructure> WorkspaceMenuStructure;`

#### Free symbols / members of external scopes

- L42 _namespace_ `namespace WorkspaceMenu`
- L44 _function_ `inline FWorkspaceMenuStructureModule& GetModule()` (scope `WorkspaceMenu`)
- L49 _function_ `inline const IWorkspaceMenuStructure& GetMenuStructure()` (scope `WorkspaceMenu`)
