# Plugins / StormSyncAvaBridgeEditor

- module root: `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridgeEditor`
- headers: 3; symbols: 28
- symbol kinds: class=2, delegate=1, member=5, prototype=20
- PrivateDependencyModuleNames: AvalancheMedia, AvalancheMediaEditor, CoreUObject, EditorFramework, Engine, Slate, SlateCore, StormSyncAvaBridge, StormSyncCore, StormSyncEditor, StormSyncTransportClient, StormSyncTransportCore, StormSyncTransportServer
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridgeEditor/Private/StormSyncAvaBridgeEditor.h` (Private)


#### class `FStormSyncAvaBridgeEditorModule`  
`class FStormSyncAvaBridgeEditorModule : public IModuleInterface`  
_L10-19_
- inherits: `IModuleInterface`
- L13 _private prototype_ `virtual void StartupModule() override;`
- L14 _private prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `TSharedPtr<FStormSyncAvaRundownExtender> RundownExtender;` — UI extender for Storm Sync view and commands.

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridgeEditor/Private/StormSyncAvaBridgeEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncAvaBridgeEditor, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncAvaBridgeEditor, Display, All);`

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridgeEditor/Private/StormSyncAvaRundownExtender.h` (Private)


#### class `FStormSyncAvaRundownExtender`  
`class FStormSyncAvaRundownExtender : public TSharedFromThis<FStormSyncAvaRundownExtender>`  
_L15-100_
- inherits: `TSharedFromThis<FStormSyncAvaRundownExtender>`
- desc: This class handles Motion Design Rundown assets UI extensions for context menu / toolbars
- L18 _public prototype_ `FStormSyncAvaRundownExtender();`
- L19 _public prototype_ `~FStormSyncAvaRundownExtender();`
- L23 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the messaging endpoint.
- L26 _private member_ `static constexpr const TCHAR* MenuExtensionHook = TEXT("Pag` — Name of the extension point we're providing extension next to
- L29 _private member_ `FDelegateHandle MenuExtenderHandle;` — Menu extender for motion design rundown editor context menu
- L32 _private member_ `FDelegateHandle ToolbarExtenderHandle;` — Toolbar extender for motion design rundown editor
- L35 _private prototype_ `void OnPostEngineInit();` — Register Context menu / toolbar extensions when editor is fully loaded
- L38 _private prototype_ `void RegisterMenuExtensions();` — Startup module handler for UI extensions
- L41 _private prototype_ `static FDelegateHandle RegisterExtension(const TSharedPtr<FExtensibilityManager> InExtensibilityManager, const FAssetEditorExtender& InExtenderDelegate);` — Startup module handler to register an UI extensions from one of Motion Design exposed extensibility hooks
- L44 _private prototype_ `static void UnregisterExtension(const TSharedPtr<FExtensibilityManager> InExtensibilityManager, const FDelegateHandle& InHandleToRemove);` — Shutdown module handler to unregister any UI extensions added here
- L47 _private prototype_ `TSharedRef<FExtender> AddMenuExtender(const TSharedRef<FUICommandList> InCommandList, const TArray<UObject*> ContextSensitiveObjects);` — Gets the extender to use for rundown context sensitive menus
- L50 _private prototype_ `void CreateTemplateContextMenu(FMenuBuilder& MenuBuilder, const UAvaRundown* InRundown, TWeakPtr<FAvaRundownEditor> InRundownEditor);` — UI Menu Extension handler for template panel
- L53 _private prototype_ `void HandleInitializeAction(const UAvaRundown* InRundown, TArray<FAvaRundownPage> InSelectedTemplatePages);` — Context menu handler for initialize action
- L56 _private prototype_ `TSharedRef<FExtender> AddToolbarExtender(const TSharedRef<FUICommandList> InCommandList, const TArray<UObject*> ContextSensitiveObjects);` — Gets the extender to use for rundown context sensitive menus
- L59 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder, TWeakPtr<FAvaRundownEditor> InRundownEditor);` — Construct toolbar widgets for rundown sync actions
- L62 _private prototype_ `TSharedRef<SWidget> GenerateToolbarMenu(TWeakPtr<FAvaRundownEditor> InRundownEditor);` — Creates widget for toolbar content
- L65 _private prototype_ `static void PushPackagesToRemote(const FString& RemoteAddressId, const TArray<FName>& InPackageNames);` — Storm sync push a list of package names to a remote address ID
- L68 _private prototype_ `static TArray<FName> GetSelectedPackagesNames(const UAvaRundown* InRundown, const TWeakPtr<FAvaRundownEditor>& InRundownEditor);` — Gather a list of package names from currently selected pages in editor
- L75 _private prototype_ `static TArray<FAvaRundownPage> GetSelectedPages(const UAvaRundown* InRundown, const TWeakPtr<FAvaRundownEditor>& InRundownEditor);` — Returns the list of currently selected pages in editor It will only return selection if the page is referencing a valid Motion Design Asset (not "None" path)
- L78 _private prototype_ `static TArray<FString> GetChannelNamesForTemplatePage(const UAvaRundown* InRundown, const FAvaRundownPage& InTemplatePage);` — Returns a unique list of channel names, gather from instanced pages, that are matching the passed in template page selection and selected asset name
- L92 _private prototype_ `static bool GetContextMenuSelectionInfos( const UAvaRundown* InRundown, const TWeakPtr<FAvaRundownEditor>& InRundownEditor, bool& bOutIsValidSelection, FText& OutDisabledReasonTooltip, TArray<FName>& OutSelectedPackageNames, FCanExecuteAction& OutCanExecuteAction );` — Provides a way for context menu builders to gather information about current selection. @param InRundown The rundown UObject we're working with @param InRundownEditor The rundown asset editor we're working with @param bOutIsValidSelection Output indicating whether selection is valid - eg. current selection returns a list of valid package names @param OutDisabledReasonTooltip Output holding the tooltip to use in case the action is disabled - eg. in case the selection contains unsaved dirty assets @param OutSelectedPackageNames Output list of package names of the selection, as returned by GetSelectedPackagesNames() @param OutCanExecuteAction Output delegate to use as a default CanExecuteAction - eg. disabling the action if selection is invalid @return false if StormSyncEditor module is not available, and we failed to determine selection state
