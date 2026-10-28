# Plugins / PluginAudit

- module root: `Plugins/Experimental/PluginAudit/Source`
- headers: 1; symbols: 49
- symbol kinds: class=2, enum=1, enumerator=3, function=2, member=15, prototype=24, struct=1, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetManagerEditor, AssetRegistry, AssetTools, BlueprintGraph, CollectionManager, ContentBrowser, ContentBrowserData, EditorFramework, EditorWidgets, GameFeatures, GameplayTags, GraphEditor, InputCore, Json, KismetCompiler, LevelEditor, MessageLog, PluginReferenceViewer, Projects, PropertyEditor, SandboxFile, Slate, SlateCore, SourceControl, SourceControlWindows, ToolMenus, ToolWidgets, TreeMap, UncontrolledChangelists, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: StatsViewer
- PublicDependencyModuleNames: Core, CoreUObject, Engine, TargetPlatform

### `Plugins/Experimental/PluginAudit/Source/Private/SPluginAuditBrowser.h` (Private)


#### class `SPluginAuditBrowser`  
`class SPluginAuditBrowser : public SCompoundWidget`  
_L26-114_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SPluginAuditBrowser)`
- L34 _public prototype_ `void Construct(const FArguments& InArgs);`
- L37 _private prototype_ `void CreateLogListing();`
- L38 _private prototype_ `void BuildPluginList();`
- L39 _private prototype_ `void RebuildAndFilterPluginList();`
- L40 _private prototype_ `void RefreshToolBar();`
- L42 _private prototype_ `void OnPluginTextFilterChanged();`
- L43 _private prototype_ `void SearchBox_OnPluginSearchTextChanged(const FText& NewText);`
- L44 _private prototype_ `ECheckBoxState GetGlobalDisabledState() const;`
- L45 _private prototype_ `void OnGlobalDisabledStateChanged(ECheckBoxState State);`
- L47 _private prototype_ `FText GetPluginCountText() const;`
- L48 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L49 _private prototype_ `void OnOpenPluginProperties();`
- L50 _private prototype_ `void OnOpenPluginReferenceViewer();`
- L51 _private prototype_ `void OpenPluginProperties(const FString& PluginName);`
- L52 _private prototype_ `void OpenPluginReferenceViewer(const TSharedRef<IPlugin>& Plugin);`
- L66 _private prototype_ `void OnListViewDoubleClick(TSharedRef<FCookedPlugin> Item);`
- L68 _private prototype_ `TSharedRef<ITableRow> MakeCookedPluginRow(TSharedRef<FCookedPlugin> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L85 _private prototype_ `void RefreshViolations();`
- L87 _private prototype_ `static TArray<TSharedRef<FTokenizedMessage>> ScanForViolations(TArray<TSharedRef<IPlugin>> InIncludedGameFeaturePlugins, TArray<TSharedRef<IPlugin>> InExcludedGameFeaturePlugins);`
- L88 _private prototype_ `static TArray<TSharedPtr<IPlugin>> GetTagSourcePlugins(const UGameplayTagsManager& Manager, FName TagName);`
- L89 _private prototype_ `static EDoesPluginDependOnGameplayTagSource DoesPluginDependOnGameplayTagSource(const UGameplayTagsManager& Manager, const TSharedPtr<IPlugin>& DependentPlugin, FName TagName, TArray<TSharedPtr<IPlugin>>& OutPossibleSources);`
- L90 _private prototype_ `static bool IsTagOnlyAvailableFromExcludedSources(const UGameplayTagsManager& Manager, const FGameplayTag& Tag, const TArray<FGameFeaturePlugin>& ExcludedPlugins);`
- L91 _private prototype_ `static void GetGameFeaturePlugins(const TArray<TSharedRef<IPlugin>>& Plugins, TArray<FGameFeaturePlugin>& GameFeaturePlugins);`
- L94 _private typedef_ `typedef TTextFilter<const IPlugin*> FCookedPluginTextFilter;`
- L96 _private member_ `TArray<TSharedRef<IPlugin>> IncludedGameFeaturePlugins;`
- L97 _private member_ `TArray<TSharedRef<IPlugin>> ExcludedGameFeaturePlugins;`
- L99 _private member_ `TArray<TSharedRef<FCookedPlugin>> CookedPlugins;`
- L100 _private member_ `TArray<TSharedRef<FCookedPlugin>> FilteredCookedPlugins;`
- L102 _private member_ `TSharedPtr<IMessageLogListing> LogListing;`
- L105 _private member_ `TSharedPtr<SListView<TSharedRef<FCookedPlugin>>> PluginListView;` — The list view widget for our plugins list
- L108 _private member_ `TSharedPtr<class SSearchBox> SearchBoxPtr;` — The plugin search box widget
- L111 _private member_ `TSharedPtr<FCookedPluginTextFilter> PluginTextFilter;` — Text filter object for typing in filter text to the search box
- L113 _private member_ `bool bGlobalDisabledState = false;`

#### class `SPluginAuditBrowser::FCookedPlugin`  
`class FCookedPlugin`  
_L54-64_
- L57 _public function_ `FCookedPlugin(const TSharedRef<IPlugin>& InPlugin) : Plugin(InPlugin)`
- L60 _public prototype_ `virtual ~FCookedPlugin() = default;`
- L62 _public member_ `TSharedRef<IPlugin> Plugin;`
- L63 _public member_ `bool bSimulateDisabled = false;`

#### struct `SPluginAuditBrowser::FGameFeaturePlugin`  
`struct FGameFeaturePlugin`  
_L70-76_
- L72 _public member_ `TSharedPtr<IPlugin> Plugin;`
- L73 _public member_ `TArray<FString> ModuleNames;`
- L74 _public member_ `TArray<FString> ScriptPackages;`
- L75 _public member_ `FName ContentRoot;`

#### enum `SPluginAuditBrowser::EDoesPluginDependOnGameplayTagSource`  
`enum class EDoesPluginDependOnGameplayTagSource`  
_L78-83_
- L80 _public enumerator_ `Yes`
- L81 _public enumerator_ `No`
- L82 _public enumerator_ `UnknownTag`
