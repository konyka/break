# Developer / SettingsEditor

- module root: `Source/Developer/SettingsEditor`
- headers: 11; symbols: 193
- symbol kinds: class=11, delegate=4, function=15, member=51, namespace=4, prototype=104, struct=2, typedef=2
- PrivateDependencyModuleNames: Analytics, CoreUObject, DesktopPlatform, DeveloperSettings, EditorWidgets, Engine, InputCore, PropertyEditor, SharedSettingsWidgets, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: Settings

### `Source/Developer/SettingsEditor/Private/Customizations/PerPlatformSettingsCustomization.h` (Private)


#### class `FPerPlatformSettingsCustomization`  
`class FPerPlatformSettingsCustomization : public IPropertyTypeCustomization`  
_L14-25_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _private prototype_ `FPerPlatformSettingsCustomization();`

### `Source/Developer/SettingsEditor/Private/Customizations/SettingsEditorCustomization.h` (Private)


#### class `FSettingsEditorCustomization`  
`class FSettingsEditorCustomization : public IDetailCustomization`  
_L13-32_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `static void ClearObjectDefaultPropertyValues();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayoutBuilder) override;`
- L25 _private member_ `static TMap<FString, TMap<FName, FString>> ObjectDefaultPropertyValues;` — Stores all settings object default property values ObjectPath->PropertyName->Value
- L26 _private prototype_ `static bool GetValueFromObject(const TSharedPtr<IPropertyHandle>& InPropertyHandle, UObject* InValueSource, FString& OutValue);`
- L29 _private prototype_ `void CacheResetDefaultPropertyValues(const IDetailLayoutBuilder& InDetailLayoutBuilder, UObject* InSettingsObject);` — Saves once at startup all settings object default property values
- L30 _private prototype_ `void OnResetToDefault(TSharedPtr<IPropertyHandle> InHandle);`
- L31 _private prototype_ `bool IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> InHandle);`

### `Source/Developer/SettingsEditor/Private/Models/SettingsEditorMenuContext.h` (Private)


#### class `USettingsEditorMenuContext`  
`class USettingsEditorMenuContext : public UObject`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Context passed in UToolMenu when generating menu entries for settings editor search toolbar
- L18 _public function_ `TSharedPtr<SSettingsEditor> GetSettingsEditor() const`
- L23 _public member_ `TWeakPtr<SSettingsEditor> SettingsEditorWeak;`

### `Source/Developer/SettingsEditor/Private/Models/SettingsEditorModel.h` (Private)


#### class `FSettingsEditorModel`  
`class FSettingsEditorModel : public ISettingsEditorModel`  
_L15-112_
- inherits: `ISettingsEditorModel`
- desc: Implements a view model for the settings editor widget.
- L25 _public function_ `FSettingsEditorModel( const ISettingsContainerRef& InSettingsContainer ) : SettingsContainer(InSettingsContainer)` — Creates and initializes a new instance. @param InSettingsContainer The settings container to use.
- L32 _public function_ `virtual ~FSettingsEditorModel()` — Virtual destructor.
- L41 _public function_ `virtual const ISettingsSectionPtr& GetSelectedSection() const override`
- L46 _public function_ `virtual const ISettingsContainerRef& GetSettingsContainer() const override`
- L51 _public function_ `virtual FSimpleMulticastDelegate& OnSelectionChanged() override`
- L56 _public function_ `virtual void SelectSection( const ISettingsSectionPtr& Section ) override`
- L67 _public function_ `virtual ISettingsSectionPtr GetSectionFromSectionObject(const UObject* SectionObject) const override`
- L92 _private function_ `void HandleSettingsContainerSectionRemoved( const ISettingsSectionRef& Section )` — Handles the removal of sections from the settings container.
- L103 _private member_ `ISettingsSectionPtr SelectedSection;` — Holds the currently selected settings section.
- L106 _private member_ `ISettingsContainerRef SettingsContainer;` — Holds a reference to the settings container.
- L111 _private member_ `FSimpleMulticastDelegate OnSelectionChangedDelegate;` — Holds a delegate that is executed when the selected settings section has changed.

### `Source/Developer/SettingsEditor/Private/SettingsEditorLogs.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSettingsEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSettingsEditor, Log, All);`

### `Source/Developer/SettingsEditor/Private/Widgets/SSettingsEditor.h` (Private)


#### class `SSettingsEditor`  
`class SSettingsEditor : public SCompoundWidget , public FNotifyHook`  
_L36-183_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Implements an editor widget for settings.
- L42 _public member_ `static FLazyName SettingsEditorToolbarName;` — Menu toolbar Identifier
- L43 _public member_ `static FLazyName SettingsEditorSidebarId;`
- L45 _public function_ `SLATE_BEGIN_ARGS(SSettingsEditor)`
- L62 _public prototype_ `void Construct( const FArguments& InArgs, const ISettingsEditorModelRef& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The view model.
- L68 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged ) override;`
- L78 _protected prototype_ `TWeakObjectPtr<UObject> GetSelectedSettingsObject() const;` — Gets the settings object of the selected section, if any. @return The settings object.
- L87 _protected prototype_ `void RecordPreferenceChangedAnalytics( ISettingsSectionPtr SelectedSection, const FProperty* ChangedProperty) const;` — Reports a preference changed event to the analytics system. @param SelectedSection The currently selected settings section. @param ChangedProperty The member property that changed.
- L90 _private member_ `static const FTextFormat TokenCombineFormat;`
- L91 _private member_ `static const FTextFormat TokenDelimiter;`
- L93 _private prototype_ `static void FillSettingsFiltersSection(UToolMenu* InMenu);`
- L94 _private prototype_ `static FToolMenuEntry CreateFiltersCheckboxEntry(const ISettingsEditorModule* InSettingsEditorModule, const USettingsEditorMenuContext* InContext, const FString& InKey, const TSet<FString>& InValues);`
- L96 _private prototype_ `void HandleSettingsPropertyChanged(UObject* InObjectBeingEdited, const FProperty* InMemberProperty, const FProperty* InChangedProperty);`
- L97 _private prototype_ `void HandleObjectTransacted(UObject* InObject, const FTransactionObjectEvent& InTransactionEvent);`
- L100 _private prototype_ `void HandleModelSelectionChanged();` — Callback for changing the selected settings section.
- L103 _private prototype_ `EVisibility HandleSettingsBoxVisibility() const;` — Callback for determining the visibility of the settings box.
- L106 _private prototype_ `bool HandleSettingsViewEnabled() const;` — Callback for checking whether the settings view is enabled.
- L109 _private prototype_ `EVisibility HandleSettingsViewVisibility() const;` — Callback for determining the visibility of the settings view.
- L112 _private prototype_ `FReply HandleExportButtonClicked();` — Callback for exporting all sections as a single ini.
- L115 _private prototype_ `FReply HandleImportButtonClicked();` — Callback for importing all sections from a single ini.
- L117 _private prototype_ `FText GetSearchHintText() const;`
- L118 _private prototype_ `void OnSearchTextChanged(const FText& InText);`
- L119 _private prototype_ `void OnSearchTextCommitted(const FText& InText, ETextCommit::Type InType);`
- L120 _private prototype_ `void OnAssetSearchSuggestionFilter(const FText& InText, TArray<FAssetSearchBoxSuggestion>& OutSuggestion, FText& OutText);`
- L121 _private prototype_ `FText OnAssetSearchSuggestionChosen(const FText& InText, const FString& InSuggestion);`
- L123 _private prototype_ `void ToggleSearchFilterAction(FString InFilter);`
- L124 _private prototype_ `ECheckBoxState IsSearchFilterActive(FString InFilter);`
- L125 _private prototype_ `void SetSearchFilter(const FText& InSearch, bool bInStrict = false);`
- L126 _private prototype_ `bool IsSearchFilterVisible(FString InSearchTerm) const;`
- L127 _private prototype_ `FName GetSelectedSectionName() const;`
- L128 _private prototype_ `FText GetSearchFilterTooltip(const ISettingsEditorModule* InSettingsEditorModule, FString InKey) const;`
- L130 _private prototype_ `void OnSectionSelectionChanged(TSharedPtr<ISettingsSection> InSection);`
- L131 _private prototype_ `FReply OnSearchKeyDownHandler(const FGeometry& InGeometry, const FKeyEvent& InEvent);`
- L132 _private prototype_ `void OnSearchTermsChanged(FName InContainerName, const FString& InKey);`
- L134 _private prototype_ `void UpdateToolbarMenu();`
- L137 _private member_ `TSharedPtr<SSettingsEditorCategoryTree> CategoryTree;` — Holds the settings category tree.
- L140 _private member_ `SOverlay::FOverlaySlot* CustomWidgetSlot = nullptr;` — Holds the overlay slot for custom widgets.
- L143 _private member_ `ISettingsEditorModelPtr Model;` — Holds a pointer to the view model.
- L146 _private member_ `ISettingsContainerPtr SettingsContainer;` — Holds the settings container.
- L149 _private member_ `TSharedPtr<IDetailsView> SettingsView;` — Holds the details view.
- L152 _private member_ `FSimpleDelegate OnApplicationRestartRequiredDelegate;` — Delegate called when this settings editor requests that the user be notified that the application needs to be restarted for some setting changes to take effect
- L155 _private member_ `bool bShowingAllSettings = false;` — Are we showing all settings at once
- L158 _private member_ `TSharedPtr<SAssetSearchBox> SearchBox;` — Actual search box with suggestions
- L161 _private member_ `bool bAutoDetectKeybind = false;` — Used to detect when to listen for key down events
- L164 _private member_ `TSharedPtr<SBox> MenuToolbarBox = nullptr;` — Box for the horizontal menu toolbar
- L167 _private member_ `FTSTicker::FDelegateHandle MenuToolbarUpdateHandle;` — Handle for when an update is planned
- L170 _private member_ `FString SearchKey;` — Used to store active search key
- L178 _private member_ `TSet<TWeakObjectPtr<UObject>> ModifiedObjectCache;` — Cache of modified objects added to when the user changes properties in the details view. Used to filter objects in a FCoreUObjectDelegates::OnObjectTransacted handler and only handle undo/redo events on objects that we've observed the user change a property of in the details view. Note that these objects can be settings objects as well as sub-objects of a settings object.
- L181 _private member_ `TSharedPtr<SSidebar> Sidebar;` — Sidebar (category tree) and sidebar panel (details view)
- L182 _private member_ `TSharedPtr<SWidget> SidebarPanel;`

### `Source/Developer/SettingsEditor/Private/Widgets/SSettingsEditorCategoryItem.h` (Private)


#### struct `UE::SettingsEditor::Private::FTreeItem`  
`struct FTreeItem`  
_L15-20_
- L17 _public member_ `TSharedPtr<ISettingsCategory> Category;`
- L18 _public member_ `TSharedPtr<ISettingsSection> Section;`
- L19 _public member_ `TArray<TSharedPtr<FTreeItem>> Children;`

#### class `SSettingsEditorCategoryItem`  
`class SSettingsEditorCategoryItem : public STableRow<TSharedPtr<UE::SettingsEditor::Private::FTreeItem>>`  
_L26-37_
- inherits: `STableRow<TSharedPtr<UE::SettingsEditor::Private::FTreeItem>>`
- desc: Widget that represents a single item in SSettingsEditorCategoryTree
- L29 _public function_ `SLATE_BEGIN_ARGS(SSettingsEditorCategoryItem)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner, const TSharedRef<UE::SettingsEditor::Private::FTreeItem>& InItem);`
- L36 _private member_ `TWeakPtr<UE::SettingsEditor::Private::FTreeItem> ItemWeak;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SettingsEditor` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::SettingsEditor`)

### `Source/Developer/SettingsEditor/Private/Widgets/SSettingsEditorCategoryTree.h` (Private)


#### class `SSettingsEditorCategoryTree`  
`class SSettingsEditorCategoryTree : public SCompoundWidget`  
_L20-63_
- inherits: `SCompoundWidget`
- desc: Tree view that displays all the editor settings categories
- L23 _public function_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TSharedPtr<ISettingsSection> ) SLATE_BEGIN_ARGS(SSettingsEditorCategoryTree)`
- L28 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_ARGUMENT(TSharedPtr<ISettingsSection>, InitialSelection) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<ISettingsContainer>& InSettingsContainer);` — Delegate for when selection has changed
- L36 _public prototype_ `void SetSelection(TSharedPtr<ISettingsSection> InSection);`
- L37 _public prototype_ `TSharedPtr<ISettingsSection> GetSelectedSection() const;`
- L39 _public prototype_ `void ForEachSection(TFunctionRef<bool(const TSharedPtr<ISettingsSection>&)> InFunctor);`
- L42 _private prototype_ `TSharedRef<ITableRow> OnTreeGenerateRow(TSharedPtr<UE::SettingsEditor::Private::FTreeItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L43 _private prototype_ `void OnTreeGetChildren(TSharedPtr<UE::SettingsEditor::Private::FTreeItem> InItem, TArray<TSharedPtr<UE::SettingsEditor::Private::FTreeItem>>& OutChildren);`
- L44 _private prototype_ `void OnTreeSelectionChanged(TSharedPtr<UE::SettingsEditor::Private::FTreeItem> InItem, ESelectInfo::Type InSelectInfo);`
- L45 _private prototype_ `bool OnIsSelectable(TSharedPtr<UE::SettingsEditor::Private::FTreeItem> InItem);`
- L46 _private prototype_ `void UpdateTreeItemsSource();`
- L49 _private prototype_ `void OnCultureChanged();` — Callback for when the user's culture has changed.
- L52 _private prototype_ `void OnCategoryModified(const FName& InCategory);` — Callback for the modification of categories in the settings container.
- L54 _private prototype_ `void RefreshTreeItems();`
- L56 _private prototype_ `void SetSelectionInternal(TSharedPtr<ISettingsSection> InSection);`
- L58 _private member_ `TSharedPtr<STreeView<TSharedPtr<UE::SettingsEditor::Private::FTreeItem>>> TreeView;`
- L59 _private member_ `TArray<TSharedPtr<UE::SettingsEditor::Private::FTreeItem>> TreeItemsSource;`
- L60 _private member_ `TSharedPtr<ISettingsContainer> SettingsContainer;`
- L61 _private member_ `FOnSelectionChanged OnSelectionChanged;`
- L62 _private member_ `FTSTicker::FDelegateHandle CategoryUpdateDelegate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ESelectInfo`
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TSharedPtr<ISettingsSection> ) SLATE_BEGIN_ARGS(SSettingsEditorCategoryTree) {} SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_ARGUMENT(TSharedPtr<ISettingsSection>, InitialSelection) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<ISettingsContainer>& InSettingsContainer);`

### `Source/Developer/SettingsEditor/Private/Widgets/SSettingsSectionHeader.h` (Private)


#### class `SSettingsSectionHeader`  
`class SSettingsSectionHeader : public SCompoundWidget`  
_L18-110_
- inherits: `SCompoundWidget`
- L21 _public prototype_ `static void ShowNotification(const FText& InText, SNotificationItem::ECompletionState InCompletionState, FString InNavigateTo = FString());`
- L23 _public function_ `SLATE_BEGIN_ARGS(SSettingsSectionHeader)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UObject* InSettingsObject, ISettingsEditorModelPtr InModel, TSharedPtr<IDetailsView> InDetailsView, const TSharedPtr<ITableRow>& InTableRow);`
- L31 _private prototype_ `FText GetSettingsBoxTitleText() const;`
- L32 _private prototype_ `FText GetSettingsBoxDescriptionText() const;`
- L34 _private prototype_ `FReply HandleExportButtonClicked();`
- L37 _private prototype_ `bool HandleExportButtonEnabled() const;`
- L40 _private prototype_ `FReply HandleImportButtonClicked();`
- L41 _private prototype_ `bool HandleImportButtonEnabled() const;`
- L49 _private prototype_ `FString GetDefaultConfigFilePath() const;` — Gets the absolute path to the Default.ini for the specified object. @return The path to the file.
- L57 _private prototype_ `bool IsDefaultConfigCheckOutNeeded(bool bForceSourceControlUpdate = false) const;` — Checks whether the default config file needs to be checked out for editing. @return true if the file needs to be checked out, false otherwise.
- L59 _private prototype_ `FReply HandleResetDefaultsButtonClicked();`
- L62 _private prototype_ `bool HandleResetToDefaultsButtonEnabled() const;`
- L64 _private prototype_ `EVisibility HandleSetAsDefaultButtonVisibility() const;`
- L66 _private prototype_ `FReply HandleSetAsDefaultButtonClicked();`
- L69 _private prototype_ `bool HandleSetAsDefaultButtonEnabled() const;`
- L76 _private prototype_ `bool CheckOutOrAddDefaultConfigFile(bool bForceSourceControlUpdate = false);` — Checks out the default configuration file for the currently selected settings object. @return true if the check-out succeeded, false otherwise.
- L83 _private prototype_ `bool MakeDefaultConfigFileWritable();` — Makes the default configuration file for the currently selected settings object writable. @return true if it was made writable, false otherwise.
- L86 _private prototype_ `FString HandleCheckoutNoticeConfigFilePath() const;` — Returns the config file name currently being edited.
- L89 _private prototype_ `void HandleCheckoutNoticeFileProbablyModifiedExternally();` — Reloads the configuration object.
- L92 _private prototype_ `EVisibility GetCheckoutNoticeVisibility() const;` — Callback for determining the visibility of the 'Locked' notice.
- L94 _private prototype_ `EVisibility GetButtonRowVisibility() const;`
- L96 _private prototype_ `EVisibility GetContentVisibility() const;`
- L98 _private prototype_ `float GetDescriptionRowMinHeight() const;`
- L100 _private prototype_ `void OnSettingsSelectionChanged();`
- L103 _private member_ `TSharedPtr<SSettingsEditorCheckoutNotice> FileWatcherWidget;` — Watcher widget for the default config file (checks file status / SCC state).
- L104 _private member_ `FString LastExportDir;`
- L105 _private member_ `ISettingsEditorModelPtr Model;`
- L106 _private member_ `ISettingsSectionPtr SettingsSection;`
- L107 _private member_ `TWeakObjectPtr<UObject> SettingsObject;`
- L108 _private member_ `TWeakPtr<IDetailsView> DetailsView;`
- L109 _private member_ `TWeakPtr<ITableRow> TableRow;`

#### class `FSettingsDetailRootObjectCustomization`  
`class FSettingsDetailRootObjectCustomization : public IDetailRootObjectCustomization`  
_L113-133_
- inherits: `IDetailRootObjectCustomization`
- L116 _public prototype_ `FSettingsDetailRootObjectCustomization(ISettingsEditorModelPtr InModel, const TSharedRef<IDetailsView>& InDetailsView);`
- L118 _public prototype_ `void Initialize();`
- L121 _public prototype_ `virtual TSharedPtr<SWidget> CustomizeObjectHeader(const FDetailsObjectSet& InRootObjectSet, const TSharedPtr<ITableRow>& InTableRow) override;` — IDetailRootObjectCustomization interface
- L122 _public prototype_ `virtual bool AreObjectsVisible(const FDetailsObjectSet& InRootObjectSet) const override;`
- L123 _public prototype_ `virtual bool ShouldDisplayHeader(const FDetailsObjectSet& InRootObjectSet) const override;`
- L124 _public function_ `virtual EExpansionArrowUsage GetExpansionArrowUsage() const override`
- L126 _private prototype_ `void OnSelectedSectionChanged();`
- L129 _private member_ `ISettingsEditorModelPtr Model;`
- L130 _private member_ `TWeakObjectPtr<UObject> SelectedSectionObject;`
- L131 _private member_ `TWeakPtr<IDetailsView> DetailsView;`

### `Source/Developer/SettingsEditor/Public/ISettingsEditorModel.h` (Public)


#### class `ISettingsEditorModel`  
`class ISettingsEditorModel`  
_L18-66_
- desc: Interface for settings editor view models. The settings editor view model stores the view state for the Settings Editor UI. Instances of this interface can be passed to Settings Editors in order to provide access to the settings container being added and to perform various user actions, such as setting the currently selected settings section.
- L27 _public prototype_ `virtual const TSharedPtr<ISettingsSection>& GetSelectedSection() const = 0;` — Gets the selected settings section. @return The selected section, if any.
- L34 _public prototype_ `virtual const TSharedRef<ISettingsContainer>& GetSettingsContainer() const = 0;` — Gets the settings container. @return The settings container.
- L43 _public prototype_ `virtual void SelectSection( const TSharedPtr<ISettingsSection>& Section ) = 0;` — Selects the specified settings section to be displayed in the editor. @param Section The section to select. @see SelectPreviousSection
- L52 _public prototype_ `virtual TSharedPtr<ISettingsSection> GetSectionFromSectionObject(const UObject* SectionObject) const = 0;` — Gets the section interface for a specified section object @param SectionObject	The settings section object to get the section interface for @return The section interface for the section object or nullptr if it does not exist
- L60 _public prototype_ `virtual FSimpleMulticastDelegate& OnSelectionChanged() = 0;` — Returns a delegate that is executed when the selected settings section has changed. @return The delegate.
- L65 _public prototype_ `virtual ~ISettingsEditorModel() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L70 _typedef_ `typedef TSharedPtr<ISettingsEditorModel> ISettingsEditorModelPtr;` — Type definition for shared pointers to instances of ISettingsEditorModel.
- L73 _typedef_ `typedef TSharedRef<ISettingsEditorModel> ISettingsEditorModelRef;` — Type definition for shared references to instances of ISettingsEditorModel.

### `Source/Developer/SettingsEditor/Public/ISettingsEditorModule.h` (Public)


#### class `ISettingsEditorModule`  
`class ISettingsEditorModule : public IModuleInterface`  
_L19-150_
- inherits: `IModuleInterface`
- desc: Interface for settings editor modules.
- L31 _public prototype_ `virtual TSharedRef<SWidget> CreateEditor( const TSharedRef<ISettingsEditorModel>& Model ) = 0;` — Creates a settings editor widget. @param Model The view model. @return The new widget. @see CreateModel
- L40 _public prototype_ `virtual TSharedRef<ISettingsEditorModel> CreateModel( const TSharedRef<ISettingsContainer>& SettingsContainer ) = 0;` — Creates a view model for the settings editor widget. @param SettingsContainer The settings container. @return The controller. @see CreateEditor
- L45 _public prototype_ `virtual void OnApplicationRestartRequired() = 0;` — Called when the settings have been changed such that an application restart is required for them to be fully applied
- L52 _public prototype_ `virtual void SetRestartApplicationCallback( FSimpleDelegate InRestartApplicationDelegate ) = 0;` — Set the delegate that should be called when a setting editor needs to restart the application @param InRestartApplicationDelegate The new delegate to call
- L59 _public prototype_ `virtual void SetShouldRegisterSettingCallback(FShouldRegisterSettingsDelegate InShouldRegisterSettingDelegate) = 0;` — Set the delegate that should be called when a setting editor checks whether a settings object should be registered. @param InShouldRegisterSettingDelegate The new delegate to call.
- L66 _public prototype_ `virtual void UpdateSettings(bool bForce = false) = 0;` — Registers any pending auto-discovered settings. @param bForce Forces the registration of settings even if there is no active settings editor.
- L117 _public prototype_ `virtual bool RegisterSearchTerm(FName InContainerName, const FString& InKey) = 0;` — Registers a search term for a specific container and key, does nothing if it already exists @param InContainerName The context for this search term (i.e. project/editor) @param InKey The key used to show filter/suggestions values (i.e. cvar/keybind) @return bool whether the search term is registered
- L122 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSearchTermsChanged, FName , const FString& ) virtual FOnSearchTermsChanged::RegistrationType& OnSearchTermsChanged() = 0;` — Delegate called when new search terms have been registered
- L131 _public prototype_ `virtual FSearchTerm* FindSearchTerm(FName InContainerName, const FString& InKey) = 0;` — Finds existing search term for a specific container and key @param InContainerName The context for this search term (i.e. project/editor) @param InKey The key used to show filter/suggestions values (i.e. cvar/keybind) @return FSearchTerm* The search term for this container and key if any
- L139 _public prototype_ `virtual const FSearchTerm* FindSearchTerm(FName InContainerName, const FString& InKey) const = 0;` — Finds existing search term for a specific container and key (const version) @param InContainerName The context for this search term (i.e. project/editor) @param InKey The key used to show filter/suggestions values (i.e. cvar/keybind) @return const FSearchTerm* The search term for this container and key if any
- L146 _public prototype_ `virtual const TMap<FString, FSearchTerm>* FindSearchTerms(FName InContainerName) const = 0;` — Finds existing search terms for a specific container @param InContainerName The context for this search term (i.e. project/editor) @return TMap<FString, FSearchTerm>* The search terms for this container if any
- L149 _public prototype_ `virtual ~ISettingsEditorModule() override = default;` — Virtual destructor.

#### struct `ISettingsEditorModule::FSearchTerm`  
`struct FSearchTerm`  
_L68-109_
- L71 _public member_ `FText Label;` — Used to show this search term in the UI
- L74 _public member_ `FText Tooltip;` — Tooltip text to show on the filter button
- L77 _public member_ `FName IconStyleSetName;` — Name of the style set to query icon from
- L80 _public member_ `FName IconStyleName;` — Name of the resource to use for the icon
- L83 _public member_ `TSet<FString> Values;` — Results that should be listed and suggested for this search term
- L86 _public member_ `TSet<FName> AllowedSections;` — Only show this search term and filter in those sections
- L89 _public member_ `TSet<FName> DisallowedSections;` — Do not show this search term and filter in those sections
- L92 _public member_ `bool bShowFilter = true;` — Show/hide filter toggle button in the UI or only show suggestions
- L95 _public function_ `bool PassesSectionFilter(FName InSection) const` — Returns whether this search term is allowed in a section

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldRegisterSettingsDelegate , UDeveloperSettings* );`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldRegisterSettingsDelegate , UDeveloperSettings* );`
- L122 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSearchTermsChanged, FName , const FString& ) virtual FOnSearchTermsChanged::RegistrationType& OnSearchTermsChanged() = 0;` — Delegate called when new search terms have been registered
