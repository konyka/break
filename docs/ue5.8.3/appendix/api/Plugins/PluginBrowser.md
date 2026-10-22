# Plugins / PluginBrowser

- module root: `Plugins/Editor/PluginBrowser/Source/PluginBrowser`
- headers: 19; symbols: 354
- symbol kinds: class=19, delegate=6, enum=1, enumerator=3, function=27, member=112, namespace=4, prototype=178, struct=3, typedef=1
- DynamicallyLoadedModuleNames: GameProjectGeneration
- PrivateDependencyModuleNames: AssetTools, ContentBrowser, ContentBrowserData, DirectoryWatcher, EditorFramework, EditorWidgets, GameProjectGeneration, Json, MainFrame, PluginUtils, Projects, PropertyEditor, SharedSettingsWidgets, ToolMenus, ToolWidgets, UATHelper, UnrealEd
- PrivateIncludePathModuleNames: DesktopPlatform
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore
- PublicIncludePathModuleNames: UnrealEd

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/DefaultPluginWizardDefinition.h` (Private)


#### class `FDefaultPluginWizardDefinition`  
`class FDefaultPluginWizardDefinition : public IPluginWizardDefinition`  
_L8-56_
- inherits: `IPluginWizardDefinition`
- L11 _public prototype_ `FDefaultPluginWizardDefinition(bool bIsContentOnlyProject = false);`
- L14 _public prototype_ `virtual const TArray<TSharedRef<FPluginTemplateDescription>>& GetTemplatesSource() const override;`
- L15 _public prototype_ `virtual void OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InSelectedItem, ESelectInfo::Type SelectInfo) override;`
- L16 _public prototype_ `virtual TSharedPtr<FPluginTemplateDescription> GetSelectedTemplate() const override;`
- L17 _public prototype_ `virtual void ClearTemplateSelection() override;`
- L18 _public prototype_ `virtual bool HasValidTemplateSelection() const override;`
- L20 _public function_ `virtual bool CanShowOnStartup() const override`
- L21 _public prototype_ `virtual bool HasModules() const override;`
- L22 _public prototype_ `virtual bool IsMod() const override;`
- L23 _public function_ `virtual void OnShowOnStartupCheckboxChanged(ECheckBoxState CheckBoxState) override`
- L24 _public function_ `virtual ECheckBoxState GetShowOnStartupCheckBoxState() const override`
- L25 _public function_ `virtual TSharedPtr<class SWidget> GetCustomHeaderWidget() override`
- L26 _public prototype_ `virtual FText GetInstructions() const override;`
- L28 _public prototype_ `virtual bool GetPluginIconPath(FString& OutIconPath) const override;`
- L29 _public prototype_ `virtual EHostType::Type GetPluginModuleDescriptor() const override;`
- L30 _public prototype_ `virtual ELoadingPhase::Type GetPluginLoadingPhase() const override;`
- L31 _public prototype_ `virtual bool GetTemplateIconPath(TSharedRef<FPluginTemplateDescription> InTemplate, FString& OutIconPath) const override;`
- L32 _public prototype_ `virtual FString GetPluginFolderPath() const override;`
- L33 _public prototype_ `virtual TArray<FString> GetFoldersForSelection() const override;`
- L34 _public prototype_ `virtual void PluginCreated(const FString& PluginName, bool bWasSuccessful) const override;`
- L39 _private prototype_ `void PopulateTemplatesSource();` — Creates the templates that can be used by the plugin manager to generate the plugin
- L42 _private prototype_ `FString GetFolderForTemplate(TSharedRef<FPluginTemplateDescription> InTemplate) const;` — Gets the folder for the specified template.
- L46 _private member_ `TArray<TSharedRef<FPluginTemplateDescription>> TemplateDefinitions;` — The templates available to this definition
- L49 _private member_ `TSharedPtr<FPluginTemplateDescription> CurrentTemplateDefinition;` — The currently selected template definition
- L52 _private member_ `FString PluginBaseDir;` — Base directory of the plugin templates
- L55 _private member_ `bool bIsContentOnlyProject;` — If true, this definition is for a project that can only contain content

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/NewPluginDescriptorData.h` (Private)


#### class `UNewPluginDescriptorData`  
`class UNewPluginDescriptorData : public UObject`  
_L12-36_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: An object used internally by the New Plugin Wizard to set user-defined plugin descriptor information. This should not be used outside of the New Plugin Wizard dialog
- L18 _public prototype_ `UNewPluginDescriptorData(const FObjectInitializer& ObjectInitializer);`
- L22 _public member_ `FString CreatedBy;` — `UPROPERTY(EditAnywhere, Category="Descriptor Data", meta=(DisplayName="Author"))` — The author of this content
- L26 _public member_ `FString CreatedByURL;` — `UPROPERTY(EditAnywhere, Category="Descriptor Data", AdvancedDisplay, meta=(DisplayName="Author URL"))` — Optional hyperlink for the author's website
- L30 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category="Descriptor Data")` — A description for this content
- L34 _public member_ `bool bIsBetaVersion;` — `UPROPERTY(EditAnywhere, Category="Descriptor Data", AdvancedDisplay)` — Marks this content as being in beta

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/NewPluginPythonOptionsData.h` (Private)


#### class `UNewPluginPythonOptionsData`  
`class UNewPluginPythonOptionsData : public UObject`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: An object used internally by the New Plugin Wizard to set the post-create python script options. This should not be used outside of the New Plugin Wizard dialog
- L19 _public prototype_ `UNewPluginPythonOptionsData(const FObjectInitializer& ObjectInitializer);`
- L23 _public member_ `FString AdditionalArguments;` — `UPROPERTY(EditAnywhere, Category="Post Create Python Script")` — Optional additional arguments for the python post-create script

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/PluginActions.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PluginActions`
- L12 _prototype_ `void PackagePlugin(TSharedRef<IPlugin> Plugin, TSharedPtr<SWidget> ParentWidget);` (scope `PluginActions`)

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/PluginBrowserModule.h` (Private)


#### class `FPluginBrowserModule`  
`class FPluginBrowserModule : public IPluginBrowser`  
_L20-164_
- inherits: `IPluginBrowser`
- L24 _public function_ `static FPluginBrowserModule& Get()` — Accessor for the module interface
- L30 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _public prototype_ `virtual void RegisterPluginTemplate(TSharedRef<FPluginTemplateDescription> Template) override;` — IPluginsEditorFeature implementation
- L35 _public prototype_ `virtual void UnregisterPluginTemplate(TSharedRef<FPluginTemplateDescription> Template) override;`
- L36 _public prototype_ `virtual FPluginEditorExtensionHandle RegisterPluginEditorExtension(FOnPluginBeingEdited Extension) override;`
- L37 _public prototype_ `virtual void UnregisterPluginEditorExtension(FPluginEditorExtensionHandle ExtensionHandle) override;`
- L38 _public function_ `virtual const TArray<TSharedRef<FPluginTemplateDescription>>& GetDefaultPluginTemplates() const override`
- L39 _public prototype_ `virtual void OpenPluginEditor(TSharedRef<IPlugin> PluginToEdit, TSharedPtr<SWidget> ParentWidget, FSimpleDelegate OnEditCommitted) override;`
- L42 _public function_ `FOnNewPluginCreated& OnNewPluginCreated()` — Gets a delegate so that you can register/unregister to receive callbacks when plugins are created
- L45 _public function_ `void BroadcastNewPluginCreated() const` — Broadcasts callback to notify registrants that a plugin has been created
- L47 _public function_ `virtual FOnLaunchReferenceViewer& OnLaunchReferenceViewerDelegate() override`
- L48 _public function_ `virtual FOnPluginDirectoriesChanged& OnPluginDirectoriesChanged() override`
- L49 _public function_ `virtual FSimpleDelegate& OnRestartClicked() override`
- L57 _public prototype_ `void SetPluginPendingEnableState(const FString& PluginName, bool bCurrentlyEnabled, bool bPendingEnabled);` — Sets whether a plugin is pending enable/disable @param PluginName The name of the plugin @param bCurrentlyEnabled The current state of this plugin, so that we can decide whether a change is no longer pending @param bPendingEnabled Whether to set this plugin to pending enable or disable
- L64 _public prototype_ `bool GetPluginPendingEnableState(const FString& PluginName) const;` — Gets whether a plugin is pending enable/disable This should only be used when you know this is the case after using HasPluginPendingEnable @param PluginName The name of the plugin
- L67 _public function_ `bool HasPluginsPendingEnable() const` — Whether there are any plugins pending enable/disable
- L73 _public prototype_ `bool HasPluginPendingEnable(const FString& PluginName) const;` — Whether a specific plugin is pending enable/disable @param PluginName The name of the plugin
- L76 _public prototype_ `bool IsNewlyInstalledPlugin(const FString& PluginName) const;` — Checks whether the given plugin should be displayed with a 'NEW' label
- L79 _public prototype_ `bool ShowPendingRestart() const;` — Whether the restart editor notice should be displayed.
- L82 _public member_ `static const FName PluginsEditorTabName;` — ID name for the plugins editor major tab
- L85 _public member_ `static const FName PluginCreatorTabName;` — ID name for the plugin creator tab
- L88 _public member_ `static const FName ExternalDirectoriesTabName;` — ID name for the external plugin directories tab
- L91 _public prototype_ `virtual TSharedRef<SDockTab> SpawnPluginCreatorTab(const FSpawnTabArgs& SpawnTabArgs, TSharedPtr<IPluginWizardDefinition> PluginWizardDefinition) override;` — Spawns the plugin creator tab with a specific wizard definition
- L93 _public function_ `virtual const TArray<TSharedRef<FPluginTemplateDescription>>& GetAddedPluginTemplates() const override`
- L95 _public function_ `const TArray<TPair<FOnPluginBeingEdited, FPluginEditorExtensionHandle>>& GetCustomizePluginEditingDelegates()`
- L99 _private prototype_ `TSharedRef<SDockTab> HandleSpawnPluginBrowserTab(const FSpawnTabArgs& SpawnTabArgs);` — Called to spawn the plugin browser tab
- L102 _private prototype_ `TSharedRef<SDockTab> HandleSpawnPluginCreatorTab(const FSpawnTabArgs& SpawnTabArgs);` — Called to spawn the plugin creator tab
- L105 _private prototype_ `TSharedRef<SDockTab> HandleSpawnExternalDirectoriesTab(const FSpawnTabArgs& SpawnTabArgs);` — Called to spawn the external directories tab
- L108 _private prototype_ `void OnMainFrameLoaded(TSharedPtr<SWindow> InRootWindow, bool bIsRunningStartupDialog);` — Callback for the main frame finishing load
- L111 _private prototype_ `void OnNewPluginsPopupSettingsClicked();` — Callback for when the user selects to edit installed plugins
- L114 _private prototype_ `void OnNewPluginsPopupDismissClicked();` — Callback for when the user selects to edit installed plugins
- L117 _private prototype_ `void UpdatePreviousInstalledPlugins();` — Updates the user's config file with the list of installed plugins that they've seen.
- L120 _private prototype_ `void AddContentBrowserMenuExtensions();` — Register menu extensions for the content browser
- L123 _private prototype_ `void GenerateDefaultPluginTemplateDescriptions();` — Generate Default Plugin Template Descriptions
- L126 _private member_ `FSimpleDelegate OnRestartClickedDelegate;` — Delegate to call when the restart button in the pending restart notice is clicked.
- L129 _private member_ `TArray<TSharedRef<FPluginTemplateDescription>> DefaultPluginTemplates;` — List of default plugin templates
- L132 _private member_ `TArray<TSharedRef<FPluginTemplateDescription>> AddedPluginTemplates;` — List of added plugin templates
- L135 _private member_ `TArray<TPair<FOnPluginBeingEdited, FPluginEditorExtensionHandle>> CustomizePluginEditingDelegates;` — Additional customizers of plugin editing
- L136 _private member_ `int32 EditorExtensionCounter = 0;`
- L139 _private member_ `TMap<FString, bool> PendingEnablePlugins;` — List of plugins that are pending enable/disable
- L142 _private member_ `TArray<FString> InstalledPlugins;` — List of all the installed plugins (as opposed to built-in engine plugins)
- L145 _private member_ `TSet<FString> NewlyInstalledPlugins;` — List of plugins that have been recently installed
- L148 _private member_ `TSet<FExternalPluginPath> OriginalExternalSources;` — External plugin sources configuration as captured at startup.
- L151 _private member_ `mutable TSet<FExternalPluginPath> LastQueriedExternalSources;` — Most recently queried plugin sources configuration.
- L154 _private member_ `FOnNewPluginCreated NewPluginCreatedDelegate;` — Delegate called when a new plugin is created
- L157 _private member_ `FOnLaunchReferenceViewer LaunchReferenceViewerDelegate;` — Delegate that if bound the Plugin Browser will show the Reference Viewer button. Delegate called when the button is clicked
- L160 _private member_ `FOnPluginDirectoriesChanged OnPluginDirectoriesChangedDelegate;` — Called when the external plugin directories configuration is modified via the browser.
- L163 _private member_ `TWeakPtr<SNotificationItem> NewPluginsNotification;` — Notification popup that new plugins are available

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNewPluginCreated);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNewPluginCreated);`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPluginBrowser, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPluginBrowser, Log, All);`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/PluginBrowserPrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TTextFilter< const IPlugin* > FPluginTextFilter;`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/PluginDescriptorEditor.h` (Private)


#### class `FPluginDescriptorEditor`  
`class FPluginDescriptorEditor`  
_L17-24_
- desc: Creates a window to edit a .uplugin file
- L20 _public prototype_ `static void OpenEditorWindow(TSharedRef<IPlugin> PluginToEdit, TSharedPtr<SWidget> ParentWidget, FSimpleDelegate OnEditCommitted);`
- L23 _private prototype_ `static FReply OnEditPluginFinished(UPluginMetadataObject* MetadataObject, TSharedPtr<IPlugin> Plugin, FSimpleDelegate OnEditCommitted, TWeakPtr<SWindow> WeakWindow);`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/PluginMetadataObject.h` (Private)


#### struct `FPluginReferenceMetadata`  
`struct FPluginReferenceMetadata`  
_L19-49_
- reflection: `USTRUCT()`
- desc: We use this object to display plugin reference properties using details view.
- L26 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Plugin Reference", meta=(GetOptions=GetAvailablePluginDependencies))` — Name of the dependency plugin
- L30 _public member_ `bool bOptional = false;` — `UPROPERTY(EditAnywhere, Category = "Plugin Reference")` — Whether the dependency plugin is optional meaning it will be silently ignored if not present
- L34 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Plugin Reference")` — Whether the dependency plugin should be enabled by default
- L38 _public member_ `bool bActivate = false;` — `UPROPERTY(EditAnywhere, Category = "Plugin Reference")` — Whether the dependency plugin should be activated when this plugin is activated. This only works if the dependency is a GameFeaturePlugin
- L43 _public prototype_ `void PopulateFromDescriptor(const FPluginReferenceDescriptor& InDescriptor);` — Populate the fields of this object from an existing descriptor.
- L48 _public prototype_ `void CopyIntoDescriptor(FPluginReferenceDescriptor& OutDescriptor) const;` — Copy the metadata fields into a plugin descriptor.

#### struct `FPluginDisallowedMetadata`  
`struct FPluginDisallowedMetadata`  
_L52-73_
- reflection: `USTRUCT()`
- L59 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = Details, meta = (GetOptions = GetDisallowedPluginsOptions))` — Name of the dependency plugin
- L62 _public member_ `FString Comment;` — `UPROPERTY(EditAnywhere, Category = Details)`
- L67 _public prototype_ `void PopulateFromDescriptor(const FPluginDisallowedDescriptor& InDescriptor);` — Populate the fields of this object from an existing descriptor.
- L72 _public prototype_ `void CopyIntoDescriptor(FPluginDisallowedDescriptor& OutDescriptor) const;` — Copy the metadata fields into a plugin descriptor.

#### class `UPluginMetadataObject`  
`class UPluginMetadataObject : public UObject`  
_L79-193_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: We use this object to display plugin properties using details view.
- L85 _public prototype_ `UPluginMetadataObject(const FObjectInitializer& ObjectInitializer);` — Default constructor
- L88 _public member_ `FString TargetIconPath;` — Path to this this plugin's icon
- L94 _public member_ `int32 Version;` — `UPROPERTY(VisibleAnywhere, Category = Details)` — Version number for the plugin.  The version number must increase with every version of the plugin, so that the system can determine whether one version of a plugin is newer than another, or to enforce other requirements.  This version number is not displayed in front-facing UI.  Use the VersionName for that.
- L99 _public member_ `FString VersionName;` — `UPROPERTY(EditAnywhere, Category = Details)` — Name of the version for this plugin.  This is the front-facing part of the version number.  It doesn't need to match the version number numerically, but should be updated when the version number is increased accordingly.
- L103 _public member_ `FString FriendlyName;` — `UPROPERTY(EditAnywhere, Category = Details)` — Friendly name of the plugin
- L107 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category = Details)` — Description of the plugin
- L111 _public member_ `FString Category;` — `UPROPERTY(EditAnywhere, Category = Details)` — The category that this plugin belongs to
- L115 _public member_ `FString CreatedBy;` — `UPROPERTY(EditAnywhere, Category = Details)` — The company or individual who created this plugin.  This is an optional field that may be displayed in the user interface.
- L119 _public member_ `FString CreatedByURL;` — `UPROPERTY(EditAnywhere, Category = Details)` — Hyperlink URL string for the company or individual who created this plugin.  This is optional.
- L123 _public member_ `FString DocsURL;` — `UPROPERTY(EditAnywhere, Category = Details)` — Documentation URL string.
- L127 _public member_ `FString MarketplaceURL;` — `UPROPERTY(EditAnywhere, Category = Details)` — Marketplace URL string.
- L131 _public member_ `FString SupportURL;` — `UPROPERTY(EditAnywhere, Category = Details)` — Support URL/email for this plugin. Email addresses must be prefixed with 'mailto:'
- L135 _public member_ `FString EditorCustomVirtualPath;` — `UPROPERTY(EditAnywhere, Category = Details)` — Optional custom virtual path to display in editor to better organize. Inserted just before this plugin's directory in the path: /All/Plugins/EditorCustomVirtualPath/PluginName
- L139 _public member_ `bool bCanContainContent;` — `UPROPERTY(EditAnywhere, Category = Details)` — Can this plugin contain content?
- L143 _public member_ `bool bIsBetaVersion;` — `UPROPERTY(EditAnywhere, Category = Details)` — Marks the plugin as beta in the UI
- L147 _public member_ `bool bIsEnabledByDefault;` — `UPROPERTY(VisibleAnywhere, Category = Details)` — If true, the plugin will be enabled by default without needing to modify the project file. This cannot be changed while the editor is running
- L151 _public member_ `bool bExplicitlyLoaded;` — `UPROPERTY(VisibleAnywhere, Category = Details)` — If true, the plugin will not load at startup and must be explicitly loaded. This cannot be changed while the editor is running
- L155 _public member_ `bool bIsSealed;` — `UPROPERTY(EditAnywhere, Category = Details)` — If true, prevents other plugins from depending on this plugin
- L158 _public member_ `bool bNoCode;` — `UPROPERTY(EditAnywhere, Category = Details)`
- L162 _public member_ `TArray<FPluginReferenceMetadata> Plugins;` — `UPROPERTY(EditAnywhere, Category = Dependencies, meta=(TitleProperty=Name))` — Plugins used by this plugin
- L166 _public member_ `TArray<FPluginDisallowedMetadata> DisallowedPlugins;` — `UPROPERTY(EditAnywhere, Category = Dependencies, meta = (DisplayName = "Disallowed"))` — Plugins that cannot be used by this plugin
- L169 _public member_ `TWeakPtr<IPlugin> SourcePlugin;` — Plugin this proxy object was constructed from
- L172 _public member_ `TArray<TSharedPtr<FPluginEditorExtension>> Extensions;` — Editing extensions
- L176 _public prototype_ `void SortDependencies();` — `UFUNCTION(CallInEditor, Category=Dependencies, meta = (DisplayName = "Sort dependencies"))` — Sort the plugins and disallowed plugins references in ascending name order
- L181 _public prototype_ `void PopulateFromPlugin(TSharedPtr<IPlugin> InPlugin);` — Populate the fields of this object from an existing descriptor.
- L186 _public prototype_ `void CopyIntoDescriptor(FPluginDescriptor& OutDescriptor) const;` — Copy the metadata fields into a plugin descriptor.
- L189 _public prototype_ `TArray<FString> GetAvailablePluginDependencies() const;` — `UFUNCTION()`
- L192 _public prototype_ `TArray<FString> GetDisallowedPluginsOptions() const;` — `UFUNCTION()`

#### class `FPluginMetadataCustomization`  
`class FPluginMetadataCustomization : public IDetailCustomization`  
_L198-203_
- inherits: `IDetailCustomization`
- desc: Detail customization to allow editing the plugin's icon
- L201 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L202 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/PluginStyle.h` (Private)


#### class `FPluginStyle`  
`class FPluginStyle`  
_L7-23_
- L11 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L18 _private prototype_ `static FString InContent( const FString& RelativePath, const TCHAR* Extension );`
- L22 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SFilePathBlock.h` (Private)


#### class `SFilePathBlock`  
`class SFilePathBlock : public SCompoundWidget`  
_L16-57_
- inherits: `SCompoundWidget`
- desc: Simple widget used to display a folder path, and a name of a file: __________________________  ____________________ | C:\Users\Joe.Bloggs    |  | SomeFile.txt     | |-------- Folder --------|  |------ Name ------|
- L20 _public function_ `SLATE_BEGIN_ARGS( SFilePathBlock ) : _ReadOnlyFolderPath(false)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(FText, FolderPath) SLATE_ATTRIBUTE(FText, Name) SLATE_ATTRIBUTE(FText, NameHint) SLATE_ARGUMENT(bool, ReadOnlyFolderPath) SLATE_EVENT(FOnClicked, OnBrowseForFolder) SLATE_EVENT(FOnTextChanged, OnNameChanged) SLATE_EVENT(FOnTextCommitted, OnNameCommitted) SLATE_EVENT(FOnTextChanged, OnFolderChanged) SLATE_EVENT(FOnTextCommitted, OnFolderCommitted) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Attribute specifying the text to display in the folder input
- L51 _public prototype_ `void SetFolderPathError(const FText& ErrorText);`
- L52 _public prototype_ `void SetNameError(const FText& ErrorText);`
- L55 _private member_ `TSharedPtr<SEditableTextBox> FolderPathTextBox;`
- L56 _private member_ `TSharedPtr<SEditableTextBox> NameTextBox;`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SNewPluginWizard.h` (Private)


#### class `SNewPluginWizard`  
`class SNewPluginWizard : public SCompoundWidget`  
_L29-184_
- inherits: `SCompoundWidget`
- desc: A wizard to create a new plugin
- L32 _public function_ `SLATE_BEGIN_ARGS(SNewPluginWizard)`
- L36 _public prototype_ `SNewPluginWizard();` — Constructor
- L39 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<SDockTab> InOwnerTab, TSharedPtr<IPluginWizardDefinition> InPluginWizardDefinition = nullptr);` — Constructs this widget with InArgs
- L46 _private prototype_ `void OnFolderPathTextChanged(const FText& InText);` — Called when Folder Path textbox changes value @param InText The new Plugin Folder Path text
- L54 _private prototype_ `TSharedRef<ITableRow> OnGenerateTemplateRow(TSharedRef<FPluginTemplateDescription> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called to generate a widget for the specified list item @param Item The template information for this row @param OwnerTable The table that owns these rows @return The widget for this template
- L62 _private prototype_ `TSharedRef<ITableRow> OnGenerateTemplateTile(TSharedRef<FPluginTemplateDescription> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called to generate a widget for the specified tile item @param Item The template information for this row @param OwnerTable The table that owns these rows @return The widget for this template
- L67 _private prototype_ `void OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InItem, ESelectInfo::Type SelectInfo);` — Called when the template selection changes
- L73 _private prototype_ `void OnPluginNameTextChanged(const FText& InText);` — Called when Plugin Name textbox changes value @param InText The new Plugin name text
- L76 _private prototype_ `FReply OnBrowseButtonClicked();` — Handler for when the Browse button is clicked
- L82 _private prototype_ `void ValidateFullPluginPath();` — Validates both the current path and plugin name as the final step in name validation requires a valid path.
- L87 _private prototype_ `bool CanCreatePlugin() const;` — Whether we are currently able to create a plugin
- L92 _private prototype_ `FText GetPluginDestinationPath() const;` — Get the path where we will create a plugin
- L95 _private prototype_ `FText GetCurrentPluginName() const;` — Get the current name of the plugin
- L102 _private prototype_ `FString GetExpandedPluginName() const;` — Get the actual name of the plugin that will be created, derived from the selected template's .uplugin filename (replacing the PLUGIN_NAME token with the user-entered name). Falls back to the user-entered name if the template does not use the token.
- L107 _private prototype_ `ECheckBoxState IsEnginePlugin() const;` — Whether we will create a plugin in the engine directory
- L113 _private prototype_ `void OnEnginePluginCheckboxChanged(ECheckBoxState NewCheckedState);` — Called when state of Engine plugin checkbox changes @param NewCheckedState New state of the checkbox
- L119 _private prototype_ `FReply OnCreatePluginClicked();` — This is where all the magic happens. Create actual plugin using parameters collected from other widgets
- L124 _private prototype_ `void DiscoveringAssetsCalback();` — Called when asset discovering completes if the user attempts to create a new plugin while asset discovery is still in progress.
- L129 _private prototype_ `void GenerateListViewWidget();` — Generates the expected list view for the plugin wizard, based on the wizard's definition
- L134 _private prototype_ `void GeneratePluginTemplateDynamicBrush(TSharedRef<FPluginTemplateDescription> InItem);` — Generates the dynamic brush resource for a plugin template definition if it has not yet been created
- L138 _private member_ `TWeakObjectPtr<UNewPluginDescriptorData> DescriptorData;` — Additional user-defined descriptor data
- L141 _private member_ `TWeakObjectPtr<UNewPluginPythonOptionsData> PythonOptionsData;` — Additional user-defined descriptor data
- L144 _private member_ `TSharedPtr<IPluginWizardDefinition> PluginWizardDefinition;` — The current plugin wizard definition
- L147 _private member_ `TSharedPtr<SListView<TSharedRef<FPluginTemplateDescription>>> ListView;` — The list view for template selection
- L150 _private member_ `FString AbsoluteGamePluginPath;` — Absolute path to game plugins directory so we don't have to convert it repeatedly
- L153 _private member_ `FString AbsoluteEnginePluginPath;` — Absolute path to engine plugins directory so we don't have to convert it repeatedly
- L156 _private member_ `FString LastBrowsePath;` — Last Path used to browse, so that we know it will open dialog
- L159 _private member_ `FString PluginFolderPath;` — Path where you want to create the plugin
- L162 _private member_ `FText PluginNameText;` — Name of the plugin you want to create
- L165 _private member_ `TSharedPtr<SFilePathBlock> FilePathBlock;` — File Path widget that user will choose plugin location and name with
- L168 _private member_ `TSharedPtr<class SCheckBox> ShowPluginContentDirectoryCheckBox;` — Check box to show a plugin's content directory once a plugin has been successfully created
- L171 _private member_ `bool bIsPluginPathValid;` — Whether the path of the plugin entered is currently valid
- L174 _private member_ `bool bIsPluginNameValid;` — Whether the name of the plugin entered is currently valid
- L177 _private member_ `bool bIsSelectedPathInEngine;` — Whether we want to create a plugin in the engine folder
- L180 _private member_ `bool bIsWaitingForAssetDiscoveryToFinish;` — Whether the asset discovery dialog is open and the user needs to wait on it
- L183 _private member_ `TWeakPtr<SDockTab> OwnerTab;` — Tab that owns this wizard so that we can ask to close after completion

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`
- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPluginWizard, Log, All);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPluginWizard, Log, All);`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SPluginBrowser.h` (Private)


#### class `SPluginBrowser`  
`class SPluginBrowser : public SCompoundWidget`  
_L18-112_
- inherits: `SCompoundWidget`
- desc: Implementation of main plugin editor Slate widget
- L21 _public prototype_ `DECLARE_DELEGATE_RetVal(FReply, FReplyDelegate);`
- L23 _public function_ `SLATE_BEGIN_ARGS( SPluginBrowser )`
- L27 _public prototype_ `SLATE_EVENT(FReplyDelegate, OnRestartClicked) SLATE_END_ARGS() virtual ~SPluginBrowser();`
- L35 _public prototype_ `void Construct( const FArguments& Args );` — Widget constructor
- L37 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L40 _public function_ `FPluginTextFilter& GetPluginTextFilter()` — @return Returns the plugin text filter object, so that child widgets can subscribe to find out about changes
- L46 _public prototype_ `TSharedPtr< class FPluginCategory > GetSelectedCategory() const;` — @return Returns the currently selected category
- L49 _public prototype_ `void OnCategorySelectionChanged();` — Called when the selected category changes so we can invalidate the list
- L52 _public prototype_ `void SetNeedsRefresh();` — Refresh the whole window
- L57 _private prototype_ `void OnPluginDirectoryChanged(const TArray<struct FFileChangeData>& );` — Called with notification that one of the plugin directories has changed
- L60 _private prototype_ `void OnNewPluginCreated();` — Called with notification that a new plugin has been created
- L63 _private prototype_ `EActiveTimerReturnType UpdatePluginsTimerCallback(double InCurrentTime, float InDeltaTime);` — Timer callback for when
- L66 _private prototype_ `EVisibility HandleRestartNoticeVisibility() const;` — @return Is the "restart required" notice visible?
- L69 _private prototype_ `FReply HandleRestartButtonClicked() const;` — Handle the "restart now" button being clicked
- L72 _private prototype_ `void SearchBox_OnPluginSearchTextChanged( const FText& NewText );` — Called when the text in the search box was changed
- L75 _private prototype_ `void BreadcrumbTrail_OnCrumbClicked( const TSharedPtr<FPluginCategory>& CrumbData );` — Called when a breadcrumb is clicked on the breadcrumb trail
- L78 _private prototype_ `void RefreshBreadcrumbTrail();` — Called to refresh the breadcrumb trail immediately
- L81 _private prototype_ `EActiveTimerReturnType TriggerBreadcrumbRefresh(double InCurrentTime, float InDeltaTime);` — One-off active timer to trigger a refresh of the breadcrumb trail as needed
- L84 _private prototype_ `FReply HandleNewPluginButtonClicked() const;` — Handle the "new plugin" button being clicked
- L88 _private member_ `FReplyDelegate OnRestartClicked;` — Delegate to call when the restart button is clicked.
- L91 _private member_ `TMap<FString, FDelegateHandle> WatchDirectories;` — Handles to the directory changed delegates
- L94 _private member_ `TSharedPtr<FActiveTimerHandle> UpdatePluginsTimerHandle;` — Handles to the directory changed delegates
- L97 _private member_ `TSharedPtr< class SPluginCategoryTree > PluginCategories;` — The plugin categories widget
- L100 _private member_ `TSharedPtr< class SPluginTileList > PluginList;` — The plugin list widget
- L103 _private member_ `TSharedPtr< class SSearchBox > SearchBoxPtr;` — The plugin search box widget
- L106 _private member_ `TSharedPtr< FPluginTextFilter > PluginTextFilter;` — Text filter object for typing in filter text to the search box
- L109 _private member_ `TSharedPtr< SBreadcrumbTrail< TSharedPtr< FPluginCategory > > > BreadcrumbTrail;` — Breadcrumb trail widget for the currently selected category
- L111 _private member_ `bool bInitialFocusTaken = false;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FReplyDelegate);`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SPluginCategory.h` (Private)


#### class `FPluginCategory`  
`class FPluginCategory`  
_L17-55_
- desc: Represents a category in the plugin category tree
- L21 _public member_ `TWeakPtr<FPluginCategory> ParentCategory;` — Parent category item or NULL if this is a root category
- L24 _public member_ `FString Name;` — Name of the category
- L27 _public member_ `FText DisplayName;` — Display name of the category
- L30 _public member_ `TArray<TSharedPtr<FPluginCategory>> SubCategories;` — Child categories
- L33 _public member_ `TArray<TSharedRef<IPlugin>> Plugins;` — Plugins in this category
- L36 _public function_ `FPluginCategory(TSharedPtr<FPluginCategory> InParentCategory, const FString& InName, const FText& InDisplayName) : ParentCategory(InParentCategory), Name(InName), DisplayName(InDisplayName)` — Constructor for FPluginCategory
- L44 _public function_ `TSharedPtr<FPluginCategory> FindSubCategory(const FString& SubCategoryName)` — Finds a sub-category by name

#### class `SPluginCategory`  
`class SPluginCategory : public STableRow< TSharedPtr<FPluginCategory>>`  
_L60-80_
- inherits: `STableRow<TSharedPtr<FPluginCategory>>`
- desc: Widget that represents a single category in the category tree view
- L62 _private function_ `SLATE_BEGIN_ARGS( SPluginCategory )`
- L66 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FPluginCategory>& Item);`
- L74 _private prototype_ `const FSlateBrush* GetIconBrush() const;` — @return Gets the icon brush to use for this item's current state
- L79 _private member_ `TSharedPtr<FPluginCategory> Category;` — The item we're representing the in tree

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SPluginCategoryTree.h` (Private)


#### class `SPluginCategoryTree`  
`class SPluginCategoryTree : public SCompoundWidget`  
_L18-107_
- inherits: `SCompoundWidget`
- desc: Tree view that displays all of the plugin categories and allows the user to switch views
- L29 _public function_ `SLATE_BEGIN_ARGS( SPluginCategoryTree )`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& Args, const TSharedRef< class SPluginBrowser > Owner );`
- L40 _public prototype_ `~SPluginCategoryTree();` — Destructor
- L43 _public prototype_ `SPluginBrowser& GetOwner();` — @return Gets the owner of this categories tree
- L46 _public prototype_ `TSharedPtr<FPluginCategory> GetSelectedCategory() const;` — @return Returns the currently selected category item
- L49 _public prototype_ `void SelectCategory(const TSharedPtr<FPluginCategory>& CategoryToSelect);` — Selects the specified category
- L52 _public prototype_ `bool IsItemExpanded(const TSharedPtr<FPluginCategory> Item) const;` — @return Returns true if the specified item is currently expanded in the tree
- L55 _public prototype_ `void SetNeedsRefresh();` — Signal that the categories list needs to be refreshed
- L57 _public prototype_ `void ToggleFilterType(EFilterType FilterValue);`
- L58 _public prototype_ `bool IsFilterEnabled(EFilterType FilterValue) const;`
- L63 _private prototype_ `TSharedRef<ITableRow> PluginCategoryTreeView_OnGenerateRow(TSharedPtr<FPluginCategory> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Called to generate a widget for the specified tree item
- L66 _private prototype_ `void PluginCategoryTreeView_OnGetChildren(TSharedPtr<FPluginCategory> Item, TArray<TSharedPtr<FPluginCategory>>& OutChildren);` — Given a tree item, fills an array of child items
- L69 _private prototype_ `void PluginCategoryTreeView_OnSelectionChanged(TSharedPtr<FPluginCategory> Item, ESelectInfo::Type SelectInfo);` — Called when the user clicks on a plugin item, or when selection changes by some other means
- L72 _private prototype_ `void RebuildAndFilterCategoryTree();` — Rebuilds the category tree from scratch
- L75 _private prototype_ `EActiveTimerReturnType TriggerCategoriesRefresh(double InCurrentTime, float InDeltaTime);` — Callback for refreshing the tree
- L80 _private member_ `TWeakPtr< class SPluginBrowser > OwnerWeak;` — Weak pointer back to its owner
- L83 _private member_ `TSharedPtr<STreeView<TSharedPtr<FPluginCategory>>> TreeView;` — The tree view widget for our plugin categories tree
- L86 _private member_ `TArray<TSharedPtr<FPluginCategory>> RootCategories;` — Root list of categories
- L89 _private member_ `TSharedPtr<FPluginCategory> AllCategory;` — Category that includes all plugins
- L92 _private member_ `TSharedPtr<FPluginCategory> BuiltInCategory;` — Category for built-in plugins
- L95 _private member_ `TSharedPtr<FPluginCategory> ExternalCategory;` — Category for external plugins
- L98 _private member_ `TSharedPtr<FPluginCategory> InstalledCategory;` — Category for installed plugins
- L101 _private member_ `TSharedPtr<FPluginCategory> ProjectCategory;` — Category for project plugins
- L104 _private member_ `TSharedPtr<FPluginCategory> ModCategory;` — Category for mods
- L106 _private member_ `EFilterType FilterType;`

#### enum `SPluginCategoryTree::EFilterType`  
`enum class EFilterType : uint8`  
_L22-27_
- L24 _public enumerator_ `None`
- L25 _public enumerator_ `OnlyEnabled`
- L26 _public enumerator_ `OnlyDisabled`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ESelectInfo`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SPluginPaths.h` (Private)


#### struct `FPluginPaths_External`  
`struct FPluginPaths_External`  
_L20-38_
- reflection: `USTRUCT()`
- desc: Struct used as a model to expose relevant lists via details view.
- L26 _public member_ `TArray<FDirectoryPath> AdditionalPluginDirectories;` — `UPROPERTY(Category="Plugin Directories", EditAnywhere, meta=( ToolTip="Stored in the .uproject descriptor."))`
- L29 _public member_ `TArray<FDirectoryPath> UserPluginDirectories;` — `UPROPERTY(Category="Plugin Directories", EditAnywhere)`
- L33 _public member_ `TArray<FDirectoryPath> CommandLineDirectories;` — `UPROPERTY(Category="Plugin Directories", VisibleAnywhere, EditFixedSize, meta=(NoResetToDefault, ToolTip="Specified via the -PLUGIN= command line switch; cannot be modified here."))`
- L37 _public member_ `TArray<FDirectoryPath> EnvironmentDirectories;` — `UPROPERTY(Category="Plugin Directories", VisibleAnywhere, EditFixedSize, meta=(NoResetToDefault, ToolTip="Specified via the UE_ADDITIONAL_PLUGIN_PATHS environment variable; cannot be modified here."))`

#### class `SPluginPaths`  
`class SPluginPaths : public SCompoundWidget , public FNotifyHook`  
_L42-93_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Widget that marshals details view to/from project and plugin manager.
- L49 _public function_ `SLATE_BEGIN_ARGS(SPluginPaths)`
- L53 _public prototype_ `void Construct(const FArguments& InArgs);`
- L56 _public prototype_ `virtual void NotifyPreChange(FEditPropertyChain* PropertyAboutToChange) override;`
- L57 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged) override;`
- L62 _private prototype_ `FPluginPaths_External& GetExternalPaths();` — Mutable convenience getter for ExternalPathsStruct TStructOnScope.
- L64 _private prototype_ `const FPluginPaths_External& GetExternalPaths() const;` — Const convenience getter for ExternalPathsStruct TStructOnScope.
- L66 _private prototype_ `bool CanModifyProjectPaths() const;`
- L67 _private prototype_ `bool CanModifyUserPaths() const;`
- L68 _private prototype_ `bool ShouldShowProjectPaths() const;`
- L69 _private prototype_ `bool ShouldShowUserPaths() const;`
- L72 _private prototype_ `bool HandleIsPropertyReadOnly(const FPropertyAndParent& InPropertyAndParent) const;` — Details view read-only delegate.
- L75 _private prototype_ `bool HandleIsPropertyVisible(const FPropertyAndParent& InPropertyAndParent) const;` — Details view visibility delegate.
- L78 _private prototype_ `void DiffAddedAndRemoved( const TArray<FDirectoryPath>& InBefore, const TArray<FDirectoryPath>& InAfter, TSet<FString>& OutAdded, TSet<FString>& OutRemoved );` — Given two FDirectoryPath arrays, indicate what path strings were added/removed from InAfter compared to InBefore.
- L86 _private member_ `TSharedPtr<TStructOnScope<FPluginPaths_External>> ExternalPathsStruct;` — The model being edited in the details view.
- L89 _private member_ `TSharedPtr<IStructureDetailsView> ExternalView;` — The primary editor widget.
- L92 _private member_ `FPluginPaths_External PreviousExternalPathsForDiff;` — Cache that's updated in NotifyPreChange, and diffed against in NotifyPostChange.

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SPluginTile.h` (Private)


#### class `SPluginTile`  
`class SPluginTile : public SCompoundWidget`  
_L16-73_
- inherits: `SCompoundWidget`
- desc: Widget that represents a "tile" for a single plugin in our plugins list
- L18 _private function_ `SLATE_BEGIN_ARGS( SPluginTile )`
- L22 _private prototype_ `SLATE_END_ARGS() void Construct( const FArguments& Args, const TSharedRef< class SPluginTileList > Owner, TSharedRef<IPlugin> Plugin );`
- L31 _private prototype_ `FText GetPluginNameText() const;` — Returns text to display for the plugin name.
- L34 _private prototype_ `void RecreateWidgets();` — Updates the contents of this tile
- L37 _private prototype_ `bool CanModifyPlugins() const;` — Returns whether users are able to modify the enabled/disabled state of plugins from the plugin browser
- L40 _private prototype_ `ECheckBoxState IsPluginEnabled() const;` — Returns the checked state for the enabled checkbox
- L43 _private prototype_ `void OnEnablePluginCheckboxChanged(ECheckBoxState NewCheckedState);` — Called when the enabled checkbox is clicked
- L46 _private prototype_ `EVisibility GetAuthoringButtonsVisibility() const;` — Used to determine whether to show the edit and package buttons for this plugin
- L49 _private prototype_ `void OnEditPlugin();` — Called when the 'edit' hyperlink is clicked
- L52 _private prototype_ `void OnEditPluginFinished();` — Called when the edit window is committed
- L55 _private prototype_ `void OnPackagePlugin();` — Called when the 'package' hyperlink is clicked
- L58 _private prototype_ `void OnOpenPluginReferenceViewer();` — Called when the "reference viewer' hyperlink is clicked
- L61 _private prototype_ `FText GetBetaOrExperimentalHelpText() const;` — Called when the beta or experimental flags are hovered over, or when a beta or experimental plugin is enabled
- L66 _private member_ `TSharedPtr<IPlugin> Plugin;` — The item we're representing the in tree
- L69 _private member_ `TWeakPtr< class SPluginTileList > OwnerWeak;` — Weak pointer back to its owner
- L72 _private member_ `TSharedPtr< FSlateDynamicImageBrush > PluginIconDynamicImageBrush;` — Brush resource for the image that is dynamically loaded

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Private/SPluginTileList.h` (Private)


#### class `SPluginTileList`  
`class SPluginTileList : public SCompoundWidget`  
_L17-66_
- inherits: `SCompoundWidget`
- desc: A filtered list of plugins, driven by a category selection
- L19 _private function_ `SLATE_BEGIN_ARGS( SPluginTileList )`
- L23 _private prototype_ `SLATE_END_ARGS() void Construct( const FArguments& Args, const TSharedRef< class SPluginBrowser > Owner );`
- L29 _private prototype_ `~SPluginTileList();` — Destructor
- L32 _private prototype_ `SPluginBrowser& GetOwner();` — @return Gets the owner of this list
- L35 _private prototype_ `void SetNeedsRefresh();` — Called to invalidate the list
- L41 _private prototype_ `void OnPluginTextFilterChanged();` — Called when the plugin text filter has changed what its filtering
- L44 _private prototype_ `TSharedRef<ITableRow> PluginListView_OnGenerateRow(TSharedRef<IPlugin> Item, const TSharedRef<STableViewBase>& OwnerTable );` — Called to generate a widget for the specified list item
- L47 _private prototype_ `void RebuildAndFilterPluginList();` — Rebuilds the list of plugins from scratch and applies filtering.
- L50 _private prototype_ `EActiveTimerReturnType TriggerListRebuild(double InCurrentTime, float InDeltaTime);` — One-off active timer to trigger a full refresh when something has changed with either our filtering or the loaded plugin set
- L52 _private prototype_ `FVector2D GetListBorderFadeDistance() const;`
- L56 _private member_ `TWeakPtr< class SPluginBrowser > OwnerWeak;` — Weak pointer back to its owner
- L59 _private member_ `TSharedPtr<SListView<TSharedRef<IPlugin>>> PluginListView;` — The list view widget for our plugins list
- L62 _private member_ `TArray<TSharedRef<IPlugin>> PluginListItems;` — List of everything that we want to display in the plugin list
- L65 _private member_ `bool bIsActiveTimerRegistered;` — Whether the active timer to refresh the list is registered

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Public/IPluginBrowser.h` (Public)


#### class `IPluginBrowser`  
`class IPluginBrowser : public IModuleInterface, public IPluginsEditorFeature`  
_L14-60_
- inherits: `IModuleInterface,IPluginsEditorFeature`
- desc: The public interface to this module
- L25 _public function_ `static inline IPluginBrowser& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L48 _public prototype_ `virtual TSharedRef<class SDockTab> SpawnPluginCreatorTab(const class FSpawnTabArgs& SpawnTabArgs, TSharedPtr<class IPluginWizardDefinition> PluginWizardDefinition) = 0;` — Allows other modules to spawn the new plugin interface with their own definition @param	SpawnTabArgs			Arguments for spawning the new plugin tab @param	PluginWizardDefinition	The definition that drives the functionality of the new plugin tab @return	A shared reference to the dock tab where the new plugin widget is created.
- L53 _public prototype_ `virtual FOnLaunchReferenceViewer& OnLaunchReferenceViewerDelegate() = 0;` — Allows another module that supplies the plugin reference viewer to launch when requested.
- L56 _public prototype_ `virtual FOnPluginDirectoriesChanged& OnPluginDirectoriesChanged() = 0;` — Called when the external plugin directories configuration is modified via the browser.
- L59 _public prototype_ `virtual FSimpleDelegate& OnRestartClicked() = 0;` — Can optionally be bound to override the "restart required" button behavior.

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLaunchReferenceViewer, TSharedPtr<IPlugin>);`
- L8 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLaunchReferenceViewer, TSharedPtr<IPlugin>);`
- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPluginDirectoriesChanged);`
- L9 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPluginDirectoriesChanged);`

### `Plugins/Editor/PluginBrowser/Source/PluginBrowser/Public/IPluginWizardDefinition.h` (Public)


#### class `IPluginWizardDefinition`  
`class IPluginWizardDefinition : public TSharedFromThis<IPluginWizardDefinition>`  
_L11-73_
- inherits: `TSharedFromThis<IPluginWizardDefinition>`
- L15 _public prototype_ `virtual ~IPluginWizardDefinition() = default;`
- L18 _public prototype_ `virtual const TArray<TSharedRef<FPluginTemplateDescription>>& GetTemplatesSource() const = 0;` — Returns the plugin templates available to this definition
- L21 _public prototype_ `virtual void OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InSelectedItem, ESelectInfo::Type SelectInfo) = 0;` — Changes the selection internally to match the supplied items
- L24 _public prototype_ `virtual bool HasValidTemplateSelection() const = 0;` — Returns true if the definition has a valid template selection
- L27 _public prototype_ `virtual TSharedPtr<FPluginTemplateDescription> GetSelectedTemplate() const = 0;` — Returns the currently selected template
- L30 _public prototype_ `virtual void ClearTemplateSelection() = 0;` — Clears the template selection
- L33 _public prototype_ `virtual bool CanShowOnStartup() const = 0;` — Returns true if the wizard for this definition can show on startup
- L36 _public prototype_ `virtual bool HasModules() const = 0;` — Returns true if the selected template will generate code
- L39 _public prototype_ `virtual bool IsMod() const = 0;` — Returns true if the plugin is a mod
- L42 _public prototype_ `virtual void OnShowOnStartupCheckboxChanged(ECheckBoxState CheckBoxState) = 0;` — Callback for when the 'Show on Startup' checkbox changes in the plugin wizard. Only used if the definition allows for game mod plugins
- L45 _public prototype_ `virtual ECheckBoxState GetShowOnStartupCheckBoxState() const = 0;` — Gets the state of the 'Show on Startup' checkbox. Only used if the definition allows for game mod plugins
- L48 _public prototype_ `virtual TSharedPtr<class SWidget> GetCustomHeaderWidget() = 0;` — Returns a custom header widget for the new plugin wizard, if desired.
- L51 _public prototype_ `virtual FText GetInstructions() const = 0;` — Gets the instructions to be shown when creating a new plugin
- L54 _public prototype_ `virtual bool GetPluginIconPath(FString& OutIconPath) const = 0;` — Gets the icon path for the current template selection. Returns true if the plugin requires a default icon
- L57 _public prototype_ `virtual EHostType::Type GetPluginModuleDescriptor() const = 0;` — Gets the ModuleDescriptor for the plugin based on the selection
- L60 _public prototype_ `virtual ELoadingPhase::Type GetPluginLoadingPhase() const = 0;` — Gets the LoadingPhase for the plugin based on the selection
- L63 _public prototype_ `virtual bool GetTemplateIconPath(TSharedRef<FPluginTemplateDescription> InTemplate, FString& OutIconPath) const = 0;` — Gets the icon path for the specified template. Returns true if it requires a default icon
- L66 _public prototype_ `virtual FString GetPluginFolderPath() const = 0;` — Gets the folder path of the current template selection
- L69 _public prototype_ `virtual TArray<FString> GetFoldersForSelection() const = 0;` — Gets the folders for the current template selection
- L72 _public prototype_ `virtual void PluginCreated(const FString& PluginName, bool bWasSuccessful) const = 0;` — Called when a plugin is created, with a bool indicating whether creation was actually successful.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`
