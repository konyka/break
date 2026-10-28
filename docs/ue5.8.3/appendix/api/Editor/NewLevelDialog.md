# Editor / NewLevelDialog

- module root: `Source/Editor/NewLevelDialog`
- headers: 1; symbols: 9
- symbol kinds: class=1, enum=1, enumerator=2, member=1, prototype=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore, ToolWidgets, UnrealEd

### `Source/Editor/NewLevelDialog/Public/NewLevelDialogModule.h` (Public)


#### class `FNewLevelDialogModule`  
`class FNewLevelDialogModule : public IModuleInterface`  
_L15-69_
- inherits: `IModuleInterface`
- desc: New Level Dialog module
- L31 _public prototype_ `virtual void StartupModule();` — Called right after the plugin DLL has been loaded and the plugin object has been created
- L36 _public prototype_ `virtual void ShutdownModule();` — Called before the plugin is unloaded, right before the plugin object is destroyed.
- L49 _public prototype_ `virtual bool CreateAndShowNewLevelDialog( const TSharedPtr<const SWidget> ParentWidget, FString& OutTemplateMapPackageName, bool bShowPartitionedTemplates, bool& bOutPartitionedWorld, FTemplateMapInfo* OutTemplateMapInfo = nullptr, EShowEmptyTemplate ShowEmptyTemplate = EShowEmptyTemplate::Show);` — Creates and show a window with an SNewLevelDialog @param	ParentWidget - The parent widget for the modal window showing the dialog @param	OutTemplateName	- (out) The package name of the template map selected by the user. Empty if blank map selected. @param	bShowPartitionedTemplates - If true, we allow partitioned world templates to be shown in the dialog. @param	bOutPartitionedWorld - (out) If true and OutTemplateName is empty, the empty map should be partitioned. @param	OutTemplateMapInfo - (out) If not null, will be set to the template map selected by the user. @param	ShowEmptyTemplate - Control if 'Empty Level' template should appear or not @return	true if the user selected a valid item, false if the user canceled
- L64 _public prototype_ `virtual bool CreateAndShowTemplateDialog(const TSharedPtr<const SWidget> ParentWidget, const FText& Title, const TArray<FTemplateMapInfo>& Templates, FString& OutTemplateMapPackageName, bool bShowPartitionedTemplates, bool& bOutPartitionedWorld, FTemplateMapInfo* OutTemplateMapInfo = nullptr, EShowEmptyTemplate ShowEmptyTemplate = EShowEmptyTemplate::Show);` — Creates and show a window with an SNewLevelDialog @param	ParentWidget - The parent widget for the modal window showing the dialog @param   Title - The dialog's title @param   Templates - The list of template to be shown in the dialog @param	OutTemplateName	- (out) The package name of the template map selected by the user. Empty if blank map selected. @param	bShowPartitionedTemplates - If true, we allow partitioned world templates to be shown in the dialog. @param	bOutPartitionedWorld - (out) If true and OutTemplateName is empty, the empty map should be partitioned. @param	OutTemplateMapInfo - (out) If not null, will be set to the template map selected by the user. @param	ShowEmptyTemplate - Control if 'Empty Level' template should appear or not @return	true if the user selected a valid item, false if the user canceled
- L67 _public member_ `static const FName NewLevelDialogAppIdentifier;` — New Level Dialog app identifier string

#### enum `FNewLevelDialogModule::EShowEmptyTemplate`  
`enum class EShowEmptyTemplate : uint8`  
_L22-26_
- desc: Control if 'Empty Level' template should appear or not
- L24 _public enumerator_ `Show`
- L25 _public enumerator_ `Hide`
