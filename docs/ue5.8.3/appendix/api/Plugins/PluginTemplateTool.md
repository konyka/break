# Plugins / PluginTemplateTool

- module root: `Plugins/Experimental/PluginTemplateTool/Source`
- headers: 1; symbols: 18
- symbol kinds: class=1, function=1, member=5, prototype=9, struct=1, typedef=1
- PrivateDependencyModuleNames: EditorFramework, EditorWidgets, PluginBrowser, ToolWidgets, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore

### `Plugins/Experimental/PluginTemplateTool/Source/PluginTemplateTool/Private/SPluginTemplateBrowser.h` (Private)


#### class `SPluginTemplateBrowser`  
`class SPluginTemplateBrowser : public SCompoundWidget`  
_L15-57_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SPluginTemplateBrowser)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L47 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForTemplateListView(TSharedPtr<FPluginTemplateListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L50 _private typedef_ `typedef SListView<TSharedPtr<FPluginTemplateListItem>> SPluginTemplateListView;`
- L53 _private member_ `TArray<TSharedPtr<FPluginTemplateListItem>> PluginTemplateListItems;` — List items for the plugin template list
- L56 _private member_ `TSharedPtr<SPluginTemplateListView> PluginTemplateListView;` — List of all known plugin templates

#### struct `SPluginTemplateBrowser::FPluginTemplateListItem`  
`struct FPluginTemplateListItem`  
_L26-45_
- desc: An item in the plugin template list
- L28 _public prototype_ `FPluginTemplateListItem(FText InTemplateName, FString InOnDiskPath);`
- L30 _public member_ `FText TemplateName;`
- L31 _public member_ `FString OnDiskPath;`
- L32 _public member_ `bool bIsMounted =false;`
- L34 _public prototype_ `FString GetRootPath() const;`
- L35 _public prototype_ `FString GetContentPath() const;`
- L37 _public prototype_ `FReply OnMountClicked();`
- L38 _public prototype_ `FReply OnUnmountClicked();`
- L41 _public prototype_ `EVisibility GetVisibilityBasedOnMountedState() const;` — Returns Visible for templates that are currently mounted, otherwise Hidden
- L44 _public prototype_ `EVisibility GetVisibilityBasedOnUnmountedState() const;` — Returns Hidden for a template that are currently mounted, otherwise Visible
