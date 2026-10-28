# Plugins / StormSyncEditor

- module root: `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor`
- headers: 14; symbols: 271
- symbol kinds: class=14, delegate=3, enum=1, enumerator=2, function=15, member=68, namespace=2, prototype=151, struct=4, typedef=1, variable=10
- PrivateDependencyModuleNames: AppFramework, AssetTools, ContentBrowserAssetDataSource, ContentBrowserData, CoreUObject, DesktopPlatform, EditorFramework, EditorSubsystem, Engine, InputCore, MessageLog, RenderCore, Slate, SlateCore, Sockets, StormSyncCore, StormSyncTransportClient, StormSyncTransportCore, StormSyncTransportServer, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/ContextMenu/StormSyncAssetFolderContextMenu.h` (Private)


#### class `FStormSyncAssetFolderContextMenu`  
`class FStormSyncAssetFolderContextMenu : public TSharedFromThis<FStormSyncAssetFolderContextMenu>`  
_L14-141_
- inherits: `TSharedFromThis<FStormSyncAssetFolderContextMenu>`
- L17 _public prototype_ `void Initialize();`
- L18 _public prototype_ `void Shutdown();`
- L29 _public prototype_ `void BuildPushAssetsMenuSection(FMenuBuilder& InMenuBuilder, const TArray<FName> InPackageNames, const bool bInIsPushing);` — Submenu extension delegate to build submenu for Push and Pull actions This will create a new section and forward entries building to `BuildPushAssetsMenuEntries` @param InMenuBuilder Instance of MenuBuilder provided by the top level menu extension @param InPackageNames List of package names built from the selected assets (FAssetData) menu extensions provides @param bInIsPushing Whether the delegate should build the submenu for Push (true) or Pull (false) action
- L37 _public prototype_ `void BuildCompareWithMenuSection(FMenuBuilder& MenuBuilder, TArray<FName> InPackageNames) const;` — Submenu extension delegate to build submenu for compare actions @param MenuBuilder Instance of MenuBuilder provided by the top level menu extension @param InPackageNames List of package names built from the selected assets (FAssetData) menu extensions provides
- L46 _public prototype_ `static TArray<FAssetData> GetDirtyAssets(const TArray<FName>& InPackageNames);` — Static helper to check if a set of PackageNames contains any unsaved (dirty) assets @param InPackageNames List of package names to check for dirty state @return List of FAssetData with assets in dirty states, empty list otherwise
- L58 _public prototype_ `static TArray<FAssetData> GetDirtyAssets(const TArray<FName>& InPackageNames, FText& OutDisabledReason);` — Static helper to check if a set of PackageNames contains any unsaved (dirty) assets, additionally returning a disabled reason (useful for UI extensions and display tooltips) if there is any package names in dirty state. @param InPackageNames List of package names to check for dirty state @param OutDisabledReason FText with disabled reason and list of dirty package names displayed as a bullet list, separated by new lines. @return List of FAssetData with assets in dirty states, empty list otherwise
- L62 _private prototype_ `void RegisterMenus();` — Delegate handler to delay execution of menu extension until slate is ready
- L65 _private prototype_ `void PopulateAssetFolderContextMenu(UToolMenu* InMenu) const;` — Delegate to extend the content browser asset context menu
- L68 _private prototype_ `void PopulateAssetFileContextMenu(UToolMenu* InMenu);` — Delegate to extend the content browser asset context menu
- L71 _private prototype_ `void AddFileMenuOptions(UToolMenu* InMenu, const TArray<FName>& InSelectedPackageNames);` — Extends menu with storm sync actions (when only files are selected)
- L74 _private prototype_ `static void AddFolderMenuOptions(UToolMenu* InMenu, const TArray<FString>& InSelectedPackagePaths, const TArray<FString>& InSelectedAssetPackages);` — Extends menu with storm sync actions (when folders are selected)
- L77 _private prototype_ `static void GetSelectedAssetsInPaths(const TArray<FString>& InPaths, TArray<FName>& OutSelectedPackageNames);` — Asks asset registry for all the discovered files in the passed in paths (eg. folders)
- L80 _private prototype_ `void GetSelectedFilesAndFolders(const UToolMenu* InMenu, TArray<FString>& OutSelectedPackagePaths, TArray<FString>& OutSelectedAssetPackages) const;` — Helper to return the list of selected assets and folders
- L83 _private prototype_ `void GetSelectedFiles(const UToolMenu* InMenu, TArray<FString>& OutSelectedAssetPackages) const;` — Helper to return the list of selected assets
- L86 _private prototype_ `void GetSelectedFiles(const UToolMenu* InMenu, TArray<FName>& OutSelectedAssetPackages) const;` — Helper to return the list of selected assets (as FNames)
- L106 _private prototype_ `void BuildPushAssetsMenuEntries(FMenuBuilder& InMenuBuilder, TArray<FName> InPackageNames, const bool bInIsPushing) const;` — Context menu builder helper to build submenu entries for Push and Pull actions This will create a single menu entry if no registered connection is currently detected with a "No valid connections currently detected on the network." message. And create a menu entry for each registered connection if we have any. Both the UIAction delegate for the entry and their label depends on bInIsPushing value. The enabled / disabled state of each entry depends on their active state (see FStormSyncConnectedDevice::bIsValid). If a connection becomes unresponsive, the entry for it will be disabled until it reaches the MessageBusTimeBeforeRemovingInactiveSource value defined in StormSyncTransportSettings (in which case, the connection is cleaned up and removed from submenu) or becomes responsive again @param InMenuBuilder Instance of MenuBuilder provided by the top level menu extension @param InPackageNames List of package names built from the selected assets (FAssetData) menu extensions provides @param bInIsPushing Whether the delegate should build the submenu for Push (true) or Pull (false) action
- L109 _private prototype_ `static void ExecuteSyncAssetsAction(TArray<FName> InPackageNames);` — Synchronize a list of assets over storm sync connected devices
- L112 _private prototype_ `static void ExecutePushAssetsAction(TArray<FName> InPackageNames, FString InMessageAddressId);` — Action handler for Push Assets action in context menu for a given connected device
- L115 _private prototype_ `static void ExecutePullAssetsAction(TArray<FName> InPackageNames, FString InMessageAddressId);` — Action handler for Pull Assets action in context menu for a given connected device
- L118 _private prototype_ `static void ExecuteCompareWithAction(const TArray<FName> InPackageNames, const FString InMessageAddressId);` — Action handler for Push Assets action in context menu for a given connected device
- L121 _private prototype_ `static void ExecuteExportAction(TArray<FName> InPackageNames);` — Export a list of assets locally as a storm sync archive file
- L126 _private prototype_ `static void OnExportWizardCompleted(const TArray<FName>& InPackageNames, const FString& InFilepath);` — Handler for wizard completion, passing down the list of package to include and filepath destination for the buffer to create.
- L137 _private prototype_ `static bool WarnOnInvalidPackages(const TArray<FName>& InPackageNames, const FText& InHeadingText, const FSlateBrush* InBrush = nullptr);` — Helper validating a list of package names, checking if they exist on disk and display as an in-editor notification warning @param InPackageNames List of package names to validate and check on file system @param InHeadingText Message text displayed as a heading before the list of invalid files @param InBrush Optional slate brush override. If not passed in, will use a default warning icon @return true is all package names are valid (eg. exists on disk), false otherwise (meaning a warning notification has been displayed)
- L140 _private prototype_ `static FText GetEntryTooltipForRemote(const FMessageAddress& InRemoteAddress, const FStormSyncConnectedDevice& InConnection);` — Static helper to return a formatted text to display as tooltip

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Customization/SStormSyncIpAddressComboBox.h` (Private)


#### class `SStormSyncIpAddressComboBox`  
`class SStormSyncIpAddressComboBox : public SCompoundWidget`  
_L12-50_
- inherits: `SCompoundWidget`
- desc: Slate widget to list the addresses associated with the adapters on the local computer
- L15 _public function_ `DECLARE_DELEGATE_OneParam(FOnChooseIP, FString) SLATE_BEGIN_ARGS(SStormSyncIpAddressComboBox)`
- L19 _public prototype_ `SLATE_ARGUMENT(FString, InitialValue) SLATE_EVENT(FOnChooseIP, OnIPAddressSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _private member_ `TArray<TSharedPtr<FString>> LocalAdapterAddressSource;` — Cached list of addresses associated with the adapters on the local computer
- L31 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> LocalAdapterAddressComboBox;` — Cached pointer to combo box of addresses associated with the adapters on the local computer
- L34 _private member_ `TSharedPtr<SEditableText> IPAddressEditableTextBlock;` — Text box shown on top of the local adapter address address combo box
- L37 _private member_ `FOnChooseIP OnIPAddressSelectedDelegate;` — Delegate executed when a local IP address was selected
- L40 _private prototype_ `void OnIpAddressSelected(TSharedPtr<FString> InAddress, ESelectInfo::Type InType) const;` — Handles changes in the local adapter address combo box
- L43 _private prototype_ `void OnIPAddressTextCommited(const FText&, ETextCommit::Type);` — Called when the IP Address was commited in the editable text block
- L46 _private prototype_ `TSharedRef<SWidget> GenerateLocalAdapterAddressComboBoxEntry(TSharedPtr<FString> InAddress) const;` — Generates an entry in the local adapter address combo box
- L49 _private prototype_ `static TArray<TSharedPtr<FString>> GetLocalNetworkInterfaceCardIPs();` — Gets the list of addresses associated with the adapters on the local computer

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChooseIP, FString) SLATE_BEGIN_ARGS(SStormSyncIpAddressComboBox) {} SLATE_ARGUMENT(FString, InitialValue) SLATE_EVENT(FOnChooseIP, OnIPAddressSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Customization/StormSyncTransportSettingsDetailsCustomization.h` (Private)


#### class `FStormSyncTransportSettingsDetailsCustomization`  
`class FStormSyncTransportSettingsDetailsCustomization : public IDetailCustomization`  
_L10-23_
- inherits: `IDetailCustomization`
- desc: Details customization for Storm Sync Transport Settings
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _private prototype_ `void CustomizeStringAsIpDropDown(const FString& InitialValue, TSharedPtr<IPropertyHandle> PropertyHandle, IDetailLayoutBuilder& DetailBuilder);` — Replace standard FString with an ip dropdown combo box

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Factories/StormSyncArchiveFactory.h` (Private)


#### class `UStormSyncArchiveData`  
`class UStormSyncArchiveData : public UObject`  
_L11-18_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Dummy UObject created during import as transient packages
- L17 _public member_ `FString Filename;` — `UPROPERTY(Transient)`

#### class `UStormSyncArchiveFactory`  
`class UStormSyncArchiveFactory : public UFactory, public FReimportHandler`  
_L31-53_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory,FReimportHandler`
- desc: Special Storm Sync Factory to handle import of storm sync archive files and hook into content browser (drag & drop and import from context menu) It differs from usual factories as it operates on a dummy UObject transient package, and forwards handling of package extraction and asset import / update to storm sync import subsystem. When exporting / importing via Storm Sync, we don't operate on an atomic .uasset representing the underlying file it is importing, but more like a "zip" including all assets and their inner dependencies.
- L35 _public prototype_ `explicit UStormSyncArchiveFactory(const FObjectInitializer& ObjectInitializer);`
- L36 _public prototype_ `~UStormSyncArchiveFactory();`
- L39 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L40 _public prototype_ `virtual UObject* ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Params, bool& OutCanceled) override;`
- L41 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Params, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L45 _public prototype_ `virtual bool CanReimport(UObject* InObject, TArray<FString>& OutFilenames) override;`
- L46 _public prototype_ `virtual void SetReimportPaths(UObject* InObject, const TArray<FString>& InNewReimportPaths) override;`
- L47 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* InObject) override;`
- L50 _public prototype_ `void OnFileImported(const FString& InFilename);`
- L52 _public member_ `TMap<FString, FSoftObjectPath> PendingImports;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Slate/SStormSyncExportWizard.h` (Private)


#### class `SStormSyncExportWizard`  
`class SStormSyncExportWizard : public SCompoundWidget`  
_L17-151_
- inherits: `SCompoundWidget`
- desc: A modal dialog to collect information needed to export a pak buffer locally
- L20 _public function_ `DECLARE_DELEGATE_TwoParams(FOnExportWizardCompleted, const TArray<FName>&, const FString&) SLATE_BEGIN_ARGS(SStormSyncExportWizard)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<FName>& InInitialPackageNames, const TArray<FName>& InPackageNames, const FOnExportWizardCompleted& InOnExportWizardCompleted);`
- L29 _public prototype_ `static void OpenWizard(const TArray<FName>& InInitialPackageNames, const TArray<FName>& PackageNames, const FOnExportWizardCompleted& InOnExportWizardCompleted);` — Opens the dialog in a new window
- L32 _public prototype_ `void CloseDialog();` — Closes the dialog
- L42 _public prototype_ `static FString GetDefaultNameFromSelectedPackages(const TArray<FName>& InPackageNames);` — Tries to find a default suitable name for the pak name export (based on user selection in content browser) Will either use the package name if only one asset is selected, or use project name if more than one asset is currently selected in content browser. Appends the current date time to the default name.
- L46 _private member_ `FOnExportWizardCompleted OnWizardCompleted;` — Delegate triggered on wizard completion
- L49 _private member_ `TSharedPtr<SWizard> Wizard;` — Main wizard
- L52 _private member_ `TSharedPtr<SStormSyncReportDialog> ReportDialog;` — Report Dialog used in first step (to display packages in a tree view)
- L55 _private member_ `TArray<FName> InitialPackageNames;` — Initial list of selected assets in content browser that were selected by user (without dependencies)
- L58 _private member_ `TArray<FName> SelectedPackageNames;` — Original list of selected assets in content browser (including dependencies)
- L60 _private member_ `TSharedPtr<TArray<FStormSyncReportPackageData>> ReportPackages;`
- L63 _private member_ `TSharedPtr<SListView<TSharedPtr<FStormSyncFileDependency>>> FileDependenciesListView;` — The packages list view in destination page
- L66 _private member_ `TArray<TSharedPtr<FStormSyncFileDependency>> FileDependencyList;` — File dependencies list
- L69 _private member_ `FText ExportFilename;` — The filename of the actual pak buffer (without extension)
- L72 _private member_ `FText ExportDirectory;` — The path to place the file for the pak being generated
- L75 _private member_ `TSharedPtr<SEditableTextBox> FilenameEditBox;` — The editable text box to enter the current name
- L78 _private member_ `bool bLastInputValidityCheckSuccessful = false;` — True if the last validity check returned that the class name/path is valid for creation
- L81 _private member_ `FText LastInputValidityErrorText;` — The error text from the last validity check
- L84 _private member_ `FName ColumnIdToSort;` — Last column id that has been sorted
- L87 _private member_ `EColumnSortMode::Type ActiveSortMode = EColumnSortMode::Type::None;` — Current active sort mode
- L90 _private prototype_ `void OnDestinationPageEntered();` — Handler for when the user enters the "choose file destination" page
- L93 _private prototype_ `TArray<FName> GetPackageNamesFromReportsData() const;` — Filters out reports data for package names to be included and returns a flatten list of Package Names
- L96 _private prototype_ `FText GetExpectedFileSize() const;` — Returns expected file size from selected package names to include
- L99 _private prototype_ `bool CanShowDestinationPage() const;` — Whether wizard can proceed to destination page
- L102 _private prototype_ `TSharedRef<ITableRow> MakeFileDependencyWidget(TSharedPtr<FStormSyncFileDependency> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generate table row for file dependency list view
- L105 _private prototype_ `void OnCancelButtonClicked();` — Handler for cancel button, which closes the dialog
- L111 _private prototype_ `void OnFinish();` — Handler for finish wizard button, which closes the dialog and invokes OnWizardCompleted delegate with selected package names and destination path
- L114 _private prototype_ `bool CanFinish() const;` — Returns whether wizard can be completed
- L117 _private prototype_ `FText GetFileNameText() const;` — Returns the text in the file name edit box
- L120 _private prototype_ `void OnFileNameTextChanged(const FText& InNewText);` — Handler for when the text in the file name edit box has changed
- L123 _private prototype_ `FText GetFilePathText() const;` — Returns the text in the file path edit box
- L126 _private prototype_ `void OnFilePathTextChanged(const FText& InNewText);` — Handler for when the text in the file path edit box has changed
- L129 _private prototype_ `FReply HandleChooseFolderButtonClicked();` — Handler for when the "Choose Folder" button is clicked
- L132 _private prototype_ `EVisibility GetNameErrorLabelVisibility() const;` — Gets the visibility of the name error label
- L135 _private prototype_ `FText GetNameErrorLabelText() const;` — Gets the text to display in the name error label
- L138 _private prototype_ `void UpdateInputValidity();` — Checks the current file name/path for validity and updates cached values accordingly
- L141 _private prototype_ `static bool IsValidFilenameForCreation(const FString& InFilename, FText& OutFailReason);` — Returns true if the project filename is properly formed and does not conflict with another project
- L144 _private prototype_ `static bool NameContainsOnlyLegalCharacters(const FString& TestName, FString& OutIllegalCharacters);` — Checks the name for illegal characters
- L147 _private prototype_ `EColumnSortMode::Type GetSortModeForColumn(FName InColumnId) const;` — Returns last stored sort mode for column id if it matches last column being sorted
- L150 _private prototype_ `void OnSortAttributeEntries(EColumnSortPriority::Type InPriority, const FName& InColumnId, EColumnSortMode::Type InSortMode);` — Updates both ColumnIdToSort and ActiveSortMode before performing the sort

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnExportWizardCompleted, const TArray<FName>&, const FString&) SLATE_BEGIN_ARGS(SStormSyncExportWizard) {} SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<FName>& InInitialPackageNames, const TArray<FName>& InPackageNames, const FOnExportWizardCompleted& InOnExportWizardCompleted);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Slate/SStormSyncFileDependencyWidgetRow.h` (Private)


#### class `SStormSyncFileDependencyWidgetRow`  
`class SStormSyncFileDependencyWidgetRow : public SMultiColumnTableRow<TSharedPtr<FStormSyncFileDependency>>`  
_L26-44_
- inherits: `SMultiColumnTableRow<TSharedPtr<FStormSyncFileDependency>>`
- desc: Table Row for StormSyncFileDependency list
- L29 _public function_ `SLATE_BEGIN_ARGS(SStormSyncFileDependencyWidgetRow)`
- L31 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FStormSyncImportFileInfo>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L39 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;` — Generates appropriate widget for the given column name ID
- L43 _private member_ `TSharedPtr<FStormSyncImportFileInfo> WidgetItem;` — The underlying item that the TableView is visualizing

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace StormSync`
- L10 _namespace_ `namespace SlateWidgetRow` (scope `StormSync`)
- L12 _variable_ `static FName HeaderRow_PackageName = TEXT("Pac` (scope `StormSync::SlateWidgetRow`)
- L13 _variable_ `static FName HeaderRow_FileSize = TEXT("Fil` (scope `StormSync::SlateWidgetRow`)
- L14 _variable_ `static FName HeaderRow_Timestamp = TEXT("Tim` (scope `StormSync::SlateWidgetRow`)
- L15 _variable_ `static FName HeaderRow_FileHash = TEXT("Fil` (scope `StormSync::SlateWidgetRow`)
- L16 _variable_ `static FName HeaderRow_ImportReason = TEXT("Imp` (scope `StormSync::SlateWidgetRow`)
- L18 _variable_ `static FText DefaultLabel_PackageName = NSLOCTEXT("StormSyncFi` (scope `StormSync::SlateWidgetRow`)
- L19 _variable_ `static FText DefaultLabel_FileSize = NSLOCTEXT("StormSyncFi` (scope `StormSync::SlateWidgetRow`)
- L20 _variable_ `static FText DefaultLabel_Timestamp = NSLOCTEXT("StormSyncFi` (scope `StormSync::SlateWidgetRow`)
- L21 _variable_ `static FText DefaultLabel_FileHash = NSLOCTEXT("StormSyncFi` (scope `StormSync::SlateWidgetRow`)
- L22 _variable_ `static FText DefaultLabel_ImportReason = NSLOCTEXT("StormSyncFi` (scope `StormSync::SlateWidgetRow`)

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Slate/SStormSyncImportWizard.h` (Private)


#### enum `EStormSyncImportWizardActiveTab`  
`enum class EStormSyncImportWizardActiveTab : uint8`  
_L14-18_
- desc: Which tab page are we currently displaying
- L16 _public enumerator_ `FilesToImport`
- L17 _public enumerator_ `BufferFiles`

#### class `SStormSyncImportWizard`  
`class SStormSyncImportWizard : public SCompoundWidget, public IStormSyncImportWizard`  
_L29-109_
- inherits: `SCompoundWidget,IStormSyncImportWizard`
- desc: A modal dialog to collect information about files to import in local project. It is wrapping a wizard with a single-page right now (could argue that it doesn't need to be a wizard in that case), and a tab-like view with segmented control and widget switcher to display either the list of files to import (files with mismatched state between local and buffer) or files in buffer. Note: UCommonTabListWidgetBase from CommonUI seems to implement a tab-like widget that would fit perfectly for that use case.
- L32 _public function_ `SLATE_BEGIN_ARGS(SStormSyncImportWizard)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<FStormSyncImportFileInfo>& InFilesToImport, const TArray<FStormSyncImportFileInfo>& InBufferFiles);`
- L40 _protected prototype_ `virtual bool ShouldImport() const override;`
- L45 _private member_ `TSharedPtr<SWizard> Wizard;` — Main wizard
- L48 _private member_ `TSharedPtr<SListView<TSharedPtr<FStormSyncImportFileInfo>>> ListViewFilesToImport;` — The packages list view in files to import tab
- L51 _private member_ `TSharedPtr<SListView<TSharedPtr<FStormSyncImportFileInfo>>> ListViewBufferFiles;` — The packages list view in files to import tab
- L54 _private member_ `TArray<TSharedPtr<FStormSyncImportFileInfo>> FilesToImportListSource;` — File to import list view data source
- L57 _private member_ `TArray<TSharedPtr<FStormSyncImportFileInfo>> BufferFilesListSource;` — File to import list view data source
- L60 _private member_ `TArray<FStormSyncImportFileInfo> FilesToImport;` — Original list of file infos for files to import (mismatched state between buffer and local files)
- L63 _private member_ `TArray<FStormSyncImportFileInfo> BufferFiles;` — Original list of file infos included in buffer
- L66 _private member_ `TAttribute<EStormSyncImportWizardActiveTab> CurrentTab;` — Current value for the segmented control active view
- L69 _private member_ `TSharedPtr<SWidgetSwitcher> TabContentSwitcher;` — Switcher for active tab view
- L72 _private member_ `bool bShouldImport = false;` — Holds user choice on whether to perform import or cancel
- L75 _private member_ `FName ColumnIdToSort;` — Last column id that has been sorted
- L78 _private member_ `EColumnSortMode::Type ActiveSortMode = EColumnSortMode::Type::None;` — Current active sort mode
- L81 _private prototype_ `void InitListSources();` — Initializes sources for the list views from FilesToImport / BufferFiles
- L84 _private prototype_ `TSharedRef<ITableRow> MakeFileDependencyWidget(TSharedPtr<FStormSyncImportFileInfo> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generate table row for file dependency list view
- L87 _private prototype_ `void OnCancelButtonClicked();` — Handler for cancel button, which closes the dialog
- L90 _private prototype_ `void OnFinish();` — Handler for finish wizard button, which closes the dialog and sets up bShouldImport to true before exiting
- L93 _private prototype_ `bool CanFinish() const;` — Returns whether wizard can be completed
- L96 _private prototype_ `void CloseDialog();` — Closes the dialog
- L99 _private prototype_ `void OnTabViewChanged(EStormSyncImportWizardActiveTab InActiveTab);` — Handler for segmented control tab view changed
- L102 _private prototype_ `FText GetFinishButtonTooltip() const;` — Adjust finish button depending on wizard is able to finish (has files to import)
- L105 _private prototype_ `EColumnSortMode::Type GetSortModeForColumn(FName InColumnId) const;` — Returns last stored sort mode for column id if it matches last column being sorted
- L108 _private prototype_ `void OnSortAttributeEntries(EColumnSortPriority::Type InPriority, const FName& InColumnId, EColumnSortMode::Type InSortMode);` — Updates both ColumnIdToSort and ActiveSortMode before performing the sort

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Slate/SStormSyncProgressBarNotification.h` (Private)


#### class `SStormSyncProgressBarNotification`  
`class SStormSyncProgressBarNotification : public SCompoundWidget, public INotificationWidget`  
_L13-90_
- inherits: `SCompoundWidget,INotificationWidget`
- desc: Simple widget to display progress bar when sending a pak buffer to a remote server. Designed to be used as the content of an SNotificationItem.
- L16 _public function_ `SLATE_BEGIN_ARGS(SStormSyncProgressBarNotification)`
- L19 _public prototype_ `SLATE_ARGUMENT(int32, TotalBytes) SLATE_ARGUMENT(int32, CurrentBytes) SLATE_ARGUMENT(FString, EndpointAddress) SLATE_ARGUMENT(FString, HostName) SLATE_EVENT(FSimpleDelegate, OnDismissClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Represents the total number of bytes for a buffer that is sent to a remote
- L39 _public function_ `virtual void OnSetCompletionState(SNotificationItem::ECompletionState State) override`
- L40 _public function_ `virtual TSharedRef<SWidget> AsWidget() override`
- L47 _public function_ `void SetCurrentBytes(const int32 InCurrentBytes)` — Updates CurrentBytes count
- L53 _public function_ `void SetTotalBytes(const int32 InTotalBytes)` — Updates TotalBytes count
- L59 _public prototype_ `float GetPercent() const;` — Returns the actual progression based on TotalBytes and CurrentBytes, ranging from 0.f to 1.f
- L63 _protected prototype_ `TOptional<float> GetProgressBarPercent() const;` — Returns the actual progression based on TotalBytes and CurrentBytes, ranging from 0.f to 1.f
- L70 _protected prototype_ `FText GetTextContent() const;` — Returns text content for TextBlock heading of the widget If TotalBytes is set (not 0), will return CurrentBytes / TotalBytes in human readable form.
- L73 _protected prototype_ `void OnHyperlinkClicked();` — OnNavigate handler for the "dismiss" hyperlink
- L77 _private member_ `int32 TotalBytes = 0;` — Represents the total number of bytes for a buffer that is sent to a remote
- L80 _private member_ `int32 CurrentBytes = 0;` — Represents the number of bytes received for a buffer on a remote
- L83 _private member_ `FString EndpointAddress;` — Represents the endpoint address we are sending to
- L86 _private member_ `FString HostName;` — Represents the remote hostname we are sending to
- L89 _private member_ `FSimpleDelegate OnDismissClicked;` — Delegates for button clicks

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Slate/SStormSyncReportDialog.h` (Private)


#### struct `FStormSyncReportPackageData`  
`struct FStormSyncReportPackageData`  
_L12-27_
- desc: Struct equivalent of ReportPackageData in Engine/Source/Developer/AssetTools/Private/SPackageReportDialog.h
- L15 _public member_ `FString Name;` — Package name, eg. /Game/Path/File
- L18 _public member_ `bool bShouldIncludePackage = false;` — Whether this package name is selected in the tree view
- L20 _public function_ `FStormSyncReportPackageData(const FString& InName, const bool bInShouldMigratePackage) : Name(InName) , bShouldIncludePackage(bInShouldMigratePackage)`
- L26 _public prototype_ `FString ToString() const;`

#### struct `FStormSyncPackageReportNode`  
`struct FStormSyncPackageReportNode`  
_L30-83_
- desc: Struct equivalent of FPackageReportNode in Engine/Source/Developer/AssetTools/Private/SPackageReportDialog.h
- L33 _public member_ `FString NodeName;` — The name of the tree node without the path
- L36 _public member_ `ECheckBoxState CheckedState;` — A user-exposed flag determining whether the content of this node and its children should be migrated or not.
- L39 _public member_ `bool* bShouldMigratePackage;` — A pointer to an external bool describing whether this node ultimately should be migrated or not. Is only non-null for leaf nodes.
- L42 _public member_ `bool bIsFolder;` — If true, this node is a folder instead of a package
- L45 _public member_ `FStormSyncPackageReportNode* Parent;` — The parent of this node
- L48 _public member_ `TArray<TSharedPtr<FStormSyncPackageReportNode>> Children;` — The children of this node
- L51 _public function_ `FStormSyncPackageReportNode() : CheckedState(ECheckBoxState::Undetermined) , bShouldMigratePackage(nullptr) , bIsFolder(false) , Parent(nullptr)` — Constructor
- L59 _public function_ `FStormSyncPackageReportNode(const FString& InNodeName, bool InIsFolder) : NodeName(InNodeName) , CheckedState(ECheckBoxState::Undetermined) , bShouldMigratePackage(nullptr) , bIsFolder(InIsFolder) , Parent(nullptr)`
- L69 _public prototype_ `void AddPackage(const FString& PackageName, bool* bInShouldMigratePackage);` — Adds the path to the tree relative to this node, creating nodes as needed.
- L72 _public prototype_ `void ExpandChildrenRecursively(const TSharedRef<SStormSyncReportTreeView>& InTreeView);` — Expands this node and all its children
- L82 _private prototype_ `FChildrenState AddPackage_Recursive(TArray<FString>& PathElements, bool* bInShouldMigratePackage);` — Helper function for AddPackage. PathElements is the tokenized path delimited by "/"

#### struct `FStormSyncPackageReportNode::FChildrenState`  
`struct FChildrenState`  
_L75-79_
- L77 _public member_ `bool bAnyChildIsChecked;`
- L78 _public member_ `bool bAllChildrenAreChecked;`

#### class `SStormSyncReportDialog`  
`class SStormSyncReportDialog final : public SCompoundWidget`  
_L91-132_
- inherits: `SCompoundWidget`
- desc: Straight up copy of Engine/Source/Developer/AssetTools/Private/SPackageReportDialog.h which is used in Migrate Packages action. We can't use it directly as it's not exposed to outside modules.
- L94 _public function_ `SLATE_BEGIN_ARGS(SStormSyncReportDialog)`
- L95 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FText& InReportMessage, TArray<FStormSyncReportPackageData>& InPackageNames);`
- L101 _public prototype_ `void CloseDialog();` — Closes the dialog.
- L104 _private member_ `FStormSyncPackageReportNode PackageReportRootNode;`
- L105 _private member_ `TSharedPtr<SStormSyncReportTreeView> ReportTreeView;`
- L108 _private member_ `const FSlateBrush* FolderOpenBrush = nullptr;` — Brushes for the different node states
- L109 _private member_ `const FSlateBrush* FolderClosedBrush = nullptr;`
- L110 _private member_ `const FSlateBrush* PackageBrush = nullptr;`
- L113 _private prototype_ `static void SetStateRecursive(TSharedPtr<FStormSyncPackageReportNode> TreeItem, bool bIsChecked);` — Recursively sets the checked/active state of every child of this node in the tree when a checkbox is toggled.
- L116 _private prototype_ `static ECheckBoxState GetEnabledCheckState(TSharedPtr<FStormSyncPackageReportNode> TreeItem);` — Callback to check whether a checkbox is checked or not.
- L119 _private prototype_ `static void CheckBoxStateChanged(ECheckBoxState InCheckBoxState, TSharedPtr<FStormSyncPackageReportNode> TreeItem, TSharedRef<STableViewBase> OwnerTable);` — Callback called whenever a checkbox is toggled.
- L122 _private prototype_ `void ConstructNodeTree(TArray<FStormSyncReportPackageData>& PackageNames);` — Constructs the node tree given the list of package names
- L125 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow(TSharedPtr<FStormSyncPackageReportNode> TreeItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Handler to generate a row in the report tree
- L128 _private prototype_ `static void GetChildrenForTree(TSharedPtr<FStormSyncPackageReportNode> TreeItem, TArray<TSharedPtr<FStormSyncPackageReportNode>>& OutChildren);` — Gets the children for the specified tree item
- L131 _private prototype_ `const FSlateBrush* GetNodeIcon(const TSharedPtr<FStormSyncPackageReportNode>& ReportNode) const;` — Determines which image to display next to a node

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef STreeView<TSharedPtr<FStormSyncPackageReportNode>> SStormSyncReportTreeView;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/Slate/Status/SStormSyncStatusWidget.h` (Private)


#### class `SStormSyncStatusWidget`  
`class SStormSyncStatusWidget : public SCompoundWidget`  
_L14-79_
- inherits: `SCompoundWidget`
- desc: A modal dialog to show the status of package names file state between two editor instances
- L17 _public function_ `SLATE_BEGIN_ARGS(SStormSyncStatusWidget)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FStormSyncTransportStatusResponse>& InStatusResponse);`
- L24 _public prototype_ `static TSharedRef<SWindow> CreateWindow(const TSharedRef<FStormSyncTransportStatusResponse>& InStatusResponse);` — Create a new SWindow with a single status widget child
- L27 _public prototype_ `static void OpenDialog(const TSharedRef<FStormSyncTransportStatusResponse>& InStatusResponse);` — Creates and opens a new status widget window
- L36 _private member_ `TSharedPtr<SWizard> Wizard;` — Main wizard. Using a wizard widget here even though it's technically not a wizard (only one page) Doing this for visual consistency with other widgets, as well as the buttons utility we get by default with wizards (to close the widget)
- L39 _private member_ `TSharedPtr<SListView<TSharedPtr<FStormSyncImportFileInfo>>> ListView;` — The packages list view in files to import tab
- L42 _private member_ `TArray<TSharedPtr<FStormSyncImportFileInfo>> ListSource;` — File to import list view data source
- L45 _private member_ `FName ColumnIdToSort;` — Last column id that has been sorted
- L48 _private member_ `EColumnSortMode::Type ActiveSortMode = EColumnSortMode::Type::None;` — Current active sort mode
- L51 _private prototype_ `EColumnSortMode::Type GetSortModeForColumn(FName InColumnId) const;` — Returns last stored sort mode for column id if it matches last column being sorted
- L54 _private prototype_ `void OnSortAttributeEntries(EColumnSortPriority::Type InPriority, const FName& InColumnId, EColumnSortMode::Type InSortMode);` — Updates both ColumnIdToSort and ActiveSortMode before performing the sort
- L57 _private prototype_ `TSharedRef<ITableRow> MakeFileDependencyWidget(TSharedPtr<FStormSyncImportFileInfo> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generate table row for file dependency list view
- L60 _private prototype_ `static FText GetModifierOperationTooltip(EStormSyncModifierOperation InModifierOperation);` — Returns the display text for a given modifier operation
- L63 _private prototype_ `TSharedRef<SWidget> CreateModifiersListPanel();` — Create widget panel showing list of modifiers (if response bNeedsSynchronization is true)
- L66 _private prototype_ `static TSharedRef<SWidget> CreateInSyncPanel();` — Create widget panel showing the "In Sync" text (if response bNeedsSynchronization is false)
- L69 _private prototype_ `void OnCancelButtonClicked();` — Handler for cancel button, which closes the dialog
- L72 _private prototype_ `void OnFinish();` — Handler for finish wizard button, which simply closes the dialog
- L75 _private prototype_ `bool CanFinish() const;` — Returns whether wizard can be completed
- L78 _private prototype_ `void CloseDialog();` — Closes the dialog

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Private/StormSyncEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncEditor, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncEditor, Display, All);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Public/IStormSyncImportWizard.h` (Public)


#### class `IStormSyncImportWizard`  
`class IStormSyncImportWizard`  
_L5-10_
- L9 _public prototype_ `virtual bool ShouldImport() const = 0;` — Returns user choice, either import or cancel

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Public/StormSyncEditor.h` (Public)


#### class `FStormSyncEditorModule`  
`class FStormSyncEditorModule : public IModuleInterface`  
_L18-138_
- inherits: `IModuleInterface`
- desc: Main entry point and implementation of StormSync Core Editor module.
- L27 _public function_ `static inline FStormSyncEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public prototype_ `virtual void StartupModule() override;`
- L35 _public prototype_ `virtual void ShutdownModule() override;`
- L39 _public prototype_ `TSharedRef<IStormSyncImportWizard> CreateWizard(const TArray<FStormSyncImportFileInfo>& InFilesToImport, const TArray<FStormSyncImportFileInfo>& InBufferFiles);` — Opens the dialog in a modal new window
- L50 _public prototype_ `void BuildPushAssetsMenuSection(FMenuBuilder& InMenuBuilder, TArray<FName> InPackageNames, const bool bInIsPushing) const;` — Submenu extension delegate to build submenu for Push and Pull actions (useful for UI extensions) This will create a new section and forward entries building to `FStormSyncAssetFolderContextMenu::BuildPushAssetsMenuEntries` @param InMenuBuilder Instance of MenuBuilder provided by the top level menu extension @param InPackageNames List of package names built from the selected assets (FAssetData) menu extensions provides @param bInIsPushing Whether the delegate should build the submenu for Push (true) or Pull (false) action
- L58 _public prototype_ `void BuildCompareWithMenuSection(FMenuBuilder& InMenuBuilder, TArray<FName> InPackageNames) const;` — Submenu extension delegate to build submenu for compare actions (useful for UI extensions) @param InMenuBuilder Instance of MenuBuilder provided by the top level menu extension @param InPackageNames List of package names built from the selected assets (FAssetData) menu extensions provides
- L70 _public prototype_ `TArray<FAssetData> GetDirtyAssets(const TArray<FName>& InPackageNames, FText& OutDisabledReason) const;` — Exposed helper from `FStormSyncAssetFolderContextMenu` utilities to check if a set of PackageNames contains any unsaved (dirty) assets (useful for UI extensions). @param InPackageNames List of package names to check for dirty state @param OutDisabledReason FText with disabled reason and list of dirty package names displayed as a bullet list, separated by new lines. @return List of FAssetData with assets in dirty states, empty list otherwise
- L73 _public prototype_ `TMap<FMessageAddress, FStormSyncConnectedDevice> GetRegisteredConnections();` — Returns a copy of the map of active connections
- L77 _private member_ `TMap<FMessageAddress, FStormSyncConnectedDevice> RegisteredConnections;` — Map of active message bus connections over storm sync network
- L80 _private member_ `FCriticalSection ConnectionsCriticalSection;` — Critical section to allow for ThreadSafe updating of registered connections
- L83 _private member_ `TArray<IConsoleObject*> ConsoleCommands;` — References of registered console commands via IConsoleManager
- L86 _private member_ `TSharedPtr<FStormSyncAssetFolderContextMenu> AssetFolderContextMenu;` — Holds our context menu handler
- L89 _private prototype_ `void RegisterDetailsCustomizations() const;` — Register Storm Sync Details Customizations
- L92 _private prototype_ `void UnregisterDetailsCustomizations() const;` — Unregister Storm Sync Details Customizations
- L95 _private prototype_ `void RegisterConsoleCommands();` — Called from StartupModule and sets up console commands for the plugin via IConsoleManager
- L98 _private prototype_ `void ExecuteDumpConnections(const TArray<FString>& Args);` — Simple debug helper to log to output console the list of active connections
- L101 _private prototype_ `void UnregisterConsoleCommands();` — Called from ShutdownModule and clears out previously registered console commands
- L104 _private prototype_ `void ExecuteRequestStatusCommand(const TArray<FString>& Args) const;` — Command handler for request status command
- L111 _private prototype_ `void OnServiceDiscoveryConnection(const FString& MessageAddressUID, const FStormSyncConnectedDevice& ConnectedDevice);` — Event handler triggered when a new connection on storm sync network is detected. The incoming message address ID will be parsed and added to internal RegisteredConnections map if it doesn't exist yet.
- L119 _private prototype_ `void OnServiceDiscoveryStateChange(const FString& MessageAddressUID, EStormSyncConnectedDeviceState State);` — Event handler when a storm sync connected device changes state (active / inactive). This will update the connection bIsValid value in our internal map, which is used to generate context menu entries enabled / disabled state.
- L127 _private prototype_ `void OnServiceDiscoveryServerStatusChange(const FString& MessageAddressUID, bool bIsServerRunning);` — Event handler when remote server status for storm sync connected device has changed (running and listening or stopped). This will update the connection bIsServerRunning value in our internal map, which is used to generate context menu entries enabled / disabled state.
- L135 _private prototype_ `void OnServiceDiscoveryDisconnection(const FString& MessageAddressUID);` — Event handler triggered when a connection on storm sync network has been inactive for a certain amount of time (configured via MessageBusTimeBeforeRemovingInactiveSource in StormSyncTransportSettings). At this point, the connection is considered lost and cleaned up from our internal RegisteredConnections map.
- L137 _private prototype_ `static FText GetEntryTooltipForRemote(const FMessageAddress& InRemoteAddress, const FStormSyncConnectedDevice& InConnection);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncEditor/Public/Subsystems/StormSyncNotificationSubsystem.h` (Public)


#### struct `FStormSyncNotificationTask`  
`struct FStormSyncNotificationTask`  
_L17-26_
- desc: Data payload for progress bars to handle an active progress notification
- L20 _public member_ `TSharedPtr<SStormSyncProgressBarNotification, ESPMode::ThreadSafe> Widget;` — Our notification widget used as content of the notification item
- L23 _public member_ `TSharedPtr<SNotificationItem, ESPMode::ThreadSafe> Notification;` — Our notification widget
- L25 _public prototype_ `FStormSyncNotificationTask() = default;`

#### class `UStormSyncNotificationSubsystem`  
`class UStormSyncNotificationSubsystem : public UEditorSubsystem`  
_L33-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: This subsystem main purpose is to listen for tcp related events triggered from StormSyncTransport layers and module, to provide in-editor integration and handle UI/UX feedback to the end user.
- L39 _public prototype_ `static UStormSyncNotificationSubsystem& Get();` — Static convenience method to return storm sync notification subsystem
- L41 _public prototype_ `TSharedPtr<SNotificationItem> AddSimpleNotification(const FText& InNotificationText);`
- L42 _public prototype_ `TSharedPtr<SNotificationItem> AddSimpleNotification(const FNotificationInfo& InInfo);`
- L44 _public prototype_ `void NewPage(const FText& InLabel, const bool bInAppendDateTime = true);`
- L45 _public prototype_ `void Info(const FText& InMessageLogText);`
- L46 _public prototype_ `void Warning(const FText& InMessageLogText);`
- L47 _public prototype_ `void Error(const FText& InMessageLogText);`
- L48 _public prototype_ `void Notify(const EMessageSeverity::Type InSeverity, const FText& InMessageLogText, const bool bInForce = true);`
- L50 _public prototype_ `void HandlePushResponse(const TSharedPtr<FStormSyncTransportPushResponse>& InResponse);`
- L51 _public prototype_ `void HandlePullResponse(const TSharedPtr<FStormSyncTransportPullResponse>& InResponse);`
- L53 _public prototype_ `void HandleSyncResponse(const TSharedPtr<FStormSyncTransportSyncResponse>& InResponse, const FText& InSuccessTextFormat, const FText& InErrorTextFormat);`
- L57 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L58 _protected prototype_ `virtual void Deinitialize() override;`
- L62 _protected member_ `TMap<FString, FStormSyncNotificationTask> Notifications;` — Currently active notifications. Key is the remote address.
- L65 _protected prototype_ `void OnPreStartSendingBuffer(const FString& InRemoteAddress, const FString& InRemoteHostname, int32 InFileCount);` — Callback handler for FStormSyncCoreDelegates::OnPreStartSendingBuffer delegate
- L68 _protected prototype_ `void OnStartSendingBuffer(const FString& InRemoteAddress, int32 InBufferSize);` — Callback handler for FStormSyncCoreDelegates::OnStartSendingBuffer delegate
- L71 _protected prototype_ `void OnReceivingBytes(const FString& InRemoteAddress, int32 InBytesCount);` — Callback handler for FStormSyncCoreDelegates::OnPreStartSendingBuffer delegate
- L74 _protected prototype_ `virtual void AddProgressBarNotification(const FString& InRemoteAddress, const FString& InRemoteHostName);` — Called on OnPreStartSendingBuffer(), creates and display a new notification widget, displaying current status of buffer upload.
- L79 _protected prototype_ `virtual void UpdateProgressBarNotificationOnStart(const FString& InRemoteAddress, const int32 InBufferSize);` — Called from OnStartSendingBuffer() right before sending the stream. Used to update the total expected size based on buffer to send.
- L84 _protected prototype_ `virtual void UpdateProgressBarNotificationOnIncomingBytes(const FString& InRemoteAddress, const int32 InReceivedBytes);` — Called from OnReceivingBytes() and updates notification widget with received bytes count
- L87 _protected prototype_ `virtual void OnDismissButtonClicked(const FString InRemoteAddress);` — Dismiss button click handler
- L91 _private member_ `static constexpr const TCHAR* LogName = TEXT("Sto` — The name of the message output log we will send messages to
- L94 _private member_ `TUniquePtr<FMessageLog> MessageLog;` — Unique ptr to our message log
