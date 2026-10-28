# Developer / LegacyProjectLauncher

- module root: `Source/Developer/LegacyProjectLauncher`
- headers: 51; symbols: 802
- symbol kinds: class=49, delegate=8, enum=3, enumerator=14, function=194, macro=16, member=176, namespace=3, prototype=337, struct=2
- PrivateDependencyModuleNames: ApplicationCore, DesktopPlatform, InputCore, Slate, SlateCore, ToolWidgets, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: TargetDeviceServices
- PublicDependencyModuleNames: Core, CoreUObject, LauncherServices
- PublicIncludePathModuleNames: TargetPlatform

### `Source/Developer/LegacyProjectLauncher/Private/Models/LegacyProjectLauncherModel.h` (Private)


#### enum `ELauncherPanels::Type`  
`enum Type`  
_L26-33_
- desc: Enumerates available launcher panels.
- L28 _public enumerator_ `NoTask = 0`
- L29 _public enumerator_ `Launch`
- L30 _public enumerator_ `ProfileEditor`
- L31 _public enumerator_ `Progress`
- L32 _public enumerator_ `End`

#### class `FProjectLauncherModel`  
`class FProjectLauncherModel`  
_L49-264_
- desc: Implements the data model for the session launcher.
- L60 _public function_ `FProjectLauncherModel(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const TSharedRef<ILauncher>& InLauncher, const TSharedRef<ILauncherProfileManager>& InProfileManager) : DeviceProxyManager(InDeviceProxyManager) , SLegacyProjectLauncher(InLauncher) , ProfileManager(InProfileManager)` — Creates and initializes a new instance. @param InDeviceProxyManager The device proxy manager to use. @param InLauncher The launcher to use. @param InProfileManager The profile manager to use.
- L72 _public function_ `~FProjectLauncherModel()` — Destructor.
- L87 _public function_ `const TSharedRef<ITargetDeviceProxyManager>& GetDeviceProxyManager() const` — Gets the model's device proxy manager. @return Device proxy manager.
- L97 _public function_ `const TSharedRef<ILauncher>& GetSProjectLauncher() const` — Gets the model's launcher. @return SLegacyProjectLauncher.
- L108 _public function_ `const TSharedRef<ILauncherProfileManager>& GetProfileManager() const` — Get the model's profile manager. @return Profile manager. @see GetProfiles
- L119 _public function_ `const TSharedPtr<ILauncherProfile>& GetSelectedProfile() const` — Gets the active profile. @return The active profile. @see GetProfiles, GetProfileManager, SelectProfile
- L130 _public function_ `void SelectProfile(const TSharedPtr<ILauncherProfile>& Profile)` — Sets the active profile. @param InProfile The profile to assign as active,, or nullptr to deselect all. @see GetSelectedProfile
- L152 _public function_ `FSimpleMulticastDelegate& OnProfileListChanged()` — Returns a delegate to be invoked when the profile list has been modified. @return The delegate. @see OnProfileSelected
- L163 _public function_ `FOnSelectedSProjectLauncherProfileChanged& OnProfileSelected()` — Returns a delegate to be invoked when the selected profile changed. @return The delegate. @see OnProfileListChanged
- L175 _protected function_ `void LoadConfig()` — Load all profiles from disk. @see SaveConfig
- L201 _protected function_ `void SaveConfig()` — Saves all profiles to disk. @see LoadConfig
- L213 _private function_ `void HandleProfileManagerProfileAdded(const TSharedRef<ILauncherProfile>& Profile)` — Callback for when a profile was added to the profile manager.
- L221 _private function_ `void HandleProfileManagerProfileRemoved(const TSharedRef<ILauncherProfile>& Profile)` — Callback for when a profile was removed from the profile manager.
- L243 _private member_ `TSharedRef<ITargetDeviceProxyManager> DeviceProxyManager;` — Pointer to the device proxy manager.
- L246 _private member_ `TSharedRef<ILauncher> SLegacyProjectLauncher;` — Pointer to the launcher.
- L249 _private member_ `TSharedRef<ILauncherProfileManager> ProfileManager;` — Pointer to the profile manager.
- L252 _private member_ `TSharedPtr<ILauncherProfile> SelectedProfile;` — Pointer to active profile.
- L257 _private member_ `FSimpleMulticastDelegate ProjectPathChangedDelegate;` — A delegate to be invoked when the project path has been modified.
- L260 _private member_ `FSimpleMulticastDelegate ProfileListChangedDelegate;` — A delegate to be invoked when the profile list has been modified.
- L263 _private member_ `FOnSelectedSProjectLauncherProfileChanged ProfileSelectedDelegate;` — A delegate to be invoked when the selected profile changed.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace ELauncherPanels`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedSProjectLauncherProfileChanged, const ILauncherProfilePtr&, const ILauncherProfilePtr&) class FProjectLauncherModel { public: FProjectLauncherModel(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const TSharedRef<ILauncher>& InLauncher, const TSharedRef<ILauncherProfileManager>& InProfileManager) : DeviceProxyManager(InDeviceProxyManager) , SLegacyProjectLauncher(InLauncher) , ProfileManager(InProfileManager) { ProfileManager->OnProfileAdded().AddRaw(this, &FProjectLauncherModel::HandleProfileManagerProfileAdded); ProfileManager->OnProfileRemoved().AddRaw(this, &FProjectLauncherModel::HandleProfileManagerProfileRemoved); LoadConfig(); } ~FProjectLauncherModel() { ProfileManager->OnProfileAdded().RemoveAll(this); ProfileManager->OnProfileRemoved().RemoveAll(this); SaveConfig(); } public: /**` — Delegate type for launcher profile selection changes. The first parameter is the newly selected profile (or nullptr if none was selected). The second parameter is the old selected profile (or nullptr if none was previous selected).

### `Source/Developer/LegacyProjectLauncher/Private/Models/ProjectLauncherCommands.h` (Private)


#### class `FProjectLauncherCommands`  
`class FProjectLauncherCommands : public TCommands<FProjectLauncherCommands>`  
_L18-61_
- inherits: `TCommands<FProjectLauncherCommands>`
- desc: The project launcher UI commands
- L24 _public function_ `FProjectLauncherCommands() : TCommands<FProjectLauncherCommands>( "LauncherCommand", NSLOCTEXT("Contexts", "LauncherCommand", "Project Launcher Command"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Default constructor.
- L38 _public function_ `virtual void RegisterCommands() override`
- L53 _public member_ `TSharedPtr<FUICommandInfo> CreateBuild;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> DeployBuild;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> QuickLaunch;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> AdvancedBuild;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> CloseSettings;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> RenameProfile;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> DuplicateProfile;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> DeleteProfile;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "ProjectLauncherCommands"`

### `Source/Developer/LegacyProjectLauncher/Private/ProjectLauncherHelpers.h` (Private)


#### Free symbols / members of external scopes

- L19 _function_ `static TSharedRef<SButton> MakeImageButton(const FSlateBrush* ButtonImage, const FText& ButtonTip, const FOnClicked& OnClickedDelegate)` — @todo gmp: move this into a shared library or create a SImageButton widget.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Archive/SProjectLauncherArchivePage.h` (Private)


#### class `SProjectLauncherArchivePage`  
`class SProjectLauncherArchivePage : public SCompoundWidget`  
_L17-67_
- inherits: `SCompoundWidget`
- desc: Implements the profile page for the session launcher wizard.
- L22 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherArchivePage)`
- L28 _public prototype_ `~SProjectLauncherArchivePage( );` — Destructor.
- L38 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L43 _private prototype_ `void HandleArchiveCheckedStateChanged( ECheckBoxState CheckState );` — Callback for changing the checked state of an archive option.
- L46 _private prototype_ `ECheckBoxState HandleArchiveIsChecked() const;` — Callback for determining whether an archive option is checked.
- L49 _private prototype_ `EVisibility HandleArchiveVisibility( ) const;` — Callback for determining if the archive options should be displayed.
- L52 _private prototype_ `FText GetDirectoryPathText() const;` — Get archive directory text
- L55 _private prototype_ `FReply HandleBrowseButtonClicked();` — Handle browse button for archive directory
- L58 _private prototype_ `bool IsDirectoryEditable() const;` — Whether archive directory is editable
- L61 _private prototype_ `void OnDirectoryTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Handle commit event for archive directory text
- L66 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Build/SProjectLauncherBuildPage.h` (Private)


#### class `SProjectLauncherBuildPage`  
`class SProjectLauncherBuildPage : public SCompoundWidget`  
_L19-103_
- inherits: `SCompoundWidget`
- desc: Implements the profile page for the session launcher wizard.
- L24 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherBuildPage)`
- L30 _public prototype_ `~SProjectLauncherBuildPage( );` — Destructor.
- L40 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L51 _protected prototype_ `bool GenerateDSYMForProject( const FString& ProjectName, const FString& Configuration );` — Generates the DSYM for the project. @param ProjectName The name of the project. @param Configuration The build configuration name. @return true on success, false otherwise.
- L56 _private prototype_ `FText HandleBuildModeComboButtonContentText() const;` — Callback for getting the content text of the 'Build Mode' combo button.
- L59 _private prototype_ `void HandleBuildModeMenuEntryClicked(ELauncherProfileBuildModes::Type BuildMode);` — Callback for clicking an item in the 'Build Mode' menu.
- L62 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L65 _private prototype_ `EVisibility HandleBuildPlatformVisibility( ) const;` — Callback for determining if the build platform list should be displayed.
- L68 _private prototype_ `FReply HandleGenDSYMClicked();` — Callback for pressing the Advanced Setting - Generate DSYM button.
- L71 _private prototype_ `bool HandleGenDSYMButtonEnabled() const;` — Callback for getting the enabled state of the Generate DSYM button.
- L74 _private prototype_ `EVisibility ShowBuildConfiguration() const;` — Callback for determining if the build configuration should be shown
- L77 _private prototype_ `void HandleBuildConfigurationSelectorConfigurationSelected(EBuildConfiguration Configuration);` — Callback for selecting a build configuration.
- L80 _private prototype_ `FText HandleBuildConfigurationSelectorText() const;` — Callback for getting the content text of the build configuration selector.
- L83 _private prototype_ `EVisibility HandleValidationErrorIconVisibility(ELauncherProfileValidationErrors::Type Error) const;` — Callback for determining the visibility of a validation error icon.
- L86 _private prototype_ `void HandleUATCheckedStateChanged( ECheckBoxState CheckState );` — Callback for changing the checked state of a platform menu check box.
- L89 _private prototype_ `ECheckBoxState HandleUATIsChecked() const;` — Callback for determining whether a platform menu entry is checked.
- L92 _private prototype_ `FText GetCommandLineText() const;` — Callback for retrieving the current command line params for the profile
- L95 _private prototype_ `void HandleCommandLineTextBoxChanged(const FText& InText);` — Callback for changing the additional command line params
- L100 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L102 _private member_ `TSharedPtr<class SEditableTextBox> CommandLineTextBox;`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Build/SProjectLauncherBuildTaskSettings.h` (Private)


#### class `SProjectLauncherBuildTaskSettings`  
`class SProjectLauncherBuildTaskSettings : public SCompoundWidget`  
_L13-42_
- inherits: `SCompoundWidget`
- desc: Implements the launcher settings widget.
- L18 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherBuildTaskSettings)`
- L26 _public prototype_ `~SProjectLauncherBuildTaskSettings( );` — Destructor.
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L41 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherCookByTheBookSettings.h` (Private)


#### enum `EShowMapsChoices::Type`  
`enum Type`  
_L20-30_
- L23 _public enumerator_ `ShowAllMaps` — Show all available maps.
- L26 _public enumerator_ `ShowCookedMaps` — Only show maps that are to be cooked.
- L29 _public enumerator_ `ShowMissingMaps` — Only show maps that are to be cooked but missing.

#### class `SProjectLauncherCookByTheBookSettings`  
`class SProjectLauncherCookByTheBookSettings : public SCompoundWidget`  
_L37-248_
- inherits: `SCompoundWidget`
- desc: Implements the cook-by-the-book settings panel.
- L42 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherCookByTheBookSettings)`
- L48 _public prototype_ `~SProjectLauncherCookByTheBookSettings();` — Destructor.
- L58 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel, bool InShowSimple = false);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L63 _protected prototype_ `void RefreshMapList();` — Refreshes the list of available maps.
- L66 _protected prototype_ `void RefreshCultureList();` — Refreshes the list of available cultures.
- L71 _private prototype_ `void HandleAllCulturesHyperlinkNavigate(bool AllPlatforms);` — Handles clicking the 'Select All Cultures' button.
- L74 _private prototype_ `EVisibility HandleAllCulturesHyperlinkVisibility() const;` — Handles determining the visibility of the 'Select All Cultures' button.
- L77 _private prototype_ `void HandleAllMapsHyperlinkNavigate(bool AllPlatforms);` — Handles clicking the 'Select All Maps' button.
- L80 _private prototype_ `void HandleCookConfigurationSelectorConfigurationSelected(EBuildConfiguration);` — Handles selecting a build configuration for the cooker.
- L83 _private prototype_ `FText HandleCookConfigurationSelectorText() const;` — Handles getting the content text of the cooker build configuration selector.
- L86 _private prototype_ `void HandleIncrementalCheckBoxCheckStateChanged(ECheckBoxState NewState);` — Handles check state changes of the 'Incremental' check box.
- L89 _private prototype_ `ECheckBoxState HandleIncrementalCheckBoxIsChecked() const;` — Handles determining the checked state of the 'Incremental' check box.
- L91 _private prototype_ `void HandleSharedCookedBuildCheckBoxCheckStateChanged(ECheckBoxState NewState);`
- L92 _private prototype_ `ECheckBoxState HandleSharedCookedBuildCheckBoxIsChecked() const;`
- L95 _private prototype_ `void HandleCompressedCheckBoxCheckStateChanged(ECheckBoxState NewState);`
- L96 _private prototype_ `void HandleEncryptIniFilesCheckBoxCheckStateChanged(ECheckBoxState NewState);`
- L98 _private prototype_ `ECheckBoxState HandleCompressedCheckBoxIsChecked() const;`
- L99 _private prototype_ `ECheckBoxState HandleEncryptIniFilesCheckBoxIsChecked() const;`
- L105 _private prototype_ `TSharedRef<ITableRow> HandleMapListViewGenerateRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Handles generating a row widget in the map list view.
- L108 _private prototype_ `TSharedRef<ITableRow> HandleCultureListViewGenerateRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Handles generating a row widget in the culture list view.
- L111 _private prototype_ `EVisibility HandleMapSelectionHyperlinkVisibility() const;` — Handles determining the visibility of the 'Select All Maps' button.
- L114 _private prototype_ `EVisibility HandleNoMapSelectedBoxVisibility() const;` — Handles getting the visibility of the map selection warning message.
- L117 _private prototype_ `FText HandleNoMapsTextBlockText() const;` — Handles getting the text in the 'No maps' text block.
- L120 _private prototype_ `void HandleProfileManagerProfileSelected(const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile);` — Handles changing the selected profile in the profile manager.
- L123 _private prototype_ `void HandleShowCheckBoxCheckStateChanged(ECheckBoxState NewState, EShowMapsChoices::Type Choice);` — Handles checking the specified 'Show maps' check box.
- L126 _private prototype_ `ECheckBoxState HandleShowCheckBoxIsChecked(EShowMapsChoices::Type Choice) const;` — Handles determining the checked state of the specified 'Show maps' check box.
- L129 _private prototype_ `void HandleUnversionedCheckBoxCheckStateChanged(ECheckBoxState NewState);` — Handles checking the specified 'Unversioned' check box.
- L132 _private prototype_ `ECheckBoxState HandleUnversionedCheckBoxIsChecked() const;` — Handles determining the checked state of the specified 'Unversioned' check box.
- L135 _private prototype_ `EVisibility HandleValidationErrorIconVisibility(ELauncherProfileValidationErrors::Type Error) const;` — Handles determining the visibility of a validation error icon.
- L138 _private prototype_ `FText HandleCookOptionsTextBlockText() const;` — Callback for getting the cookers additional options.
- L140 _private prototype_ `void HandleCookerOptionsCommitted(const FText& NewText, ETextCommit::Type CommitType);` — Callback for changing the cookers additional options
- L143 _private prototype_ `void HandleProfileProjectChanged();` — Callback for updating any settings after the selected project has changed in the profile.
- L146 _private prototype_ `void HandleUnrealPakCheckBoxCheckStateChanged(ECheckBoxState NewState);` — Callback for check state changes of the 'UnrealPak' check box.
- L149 _private prototype_ `ECheckBoxState HandleUnrealPakCheckBoxIsChecked() const;` — Callback for determining the checked state of the 'UnrealPak' check box.
- L151 _private prototype_ `void HandleGenerateChunksCheckBoxCheckStateChanged(ECheckBoxState NewState);`
- L152 _private prototype_ `ECheckBoxState HandleGenerateChunksCheckBoxIsChecked() const;`
- L155 _private prototype_ `void HandleDontIncludeEditorContentCheckBoxCheckStateChanged(ECheckBoxState NewState);` — callbacks for including editor content checkbox
- L156 _private prototype_ `ECheckBoxState HandleDontIncludeEditorContentCheckBoxIsChecked() const;`
- L163 _private prototype_ `void HandleCreateReleaseVersionCheckBoxCheckStateChanged(ECheckBoxState NewState);` — creating release version related functions Callback for check state changes of the 'GeneratePatch' check box.
- L165 _private prototype_ `ECheckBoxState HandleCreateReleaseVersionCheckBoxIsChecked() const;` — Callback for determining the checked state of the 'GeneratePatch' check box.
- L167 _private prototype_ `void HandleCreateReleaseVersionNameCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L168 _private prototype_ `FText HandleCreateReleaseVersionNameTextBlockText() const;`
- L170 _private prototype_ `void HandleBasedOnReleaseVersionNameCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L171 _private prototype_ `FText HandleBasedOnReleaseVersionNameTextBlockText() const;`
- L173 _private prototype_ `void HandleOriginalReleaseVersionNameCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L174 _private prototype_ `FText HandleOriginalReleaseVersionNameTextBlockText() const;`
- L175 _private prototype_ `EVisibility HandleOriginalReleaseVersionVisibility() const;`
- L180 _private prototype_ `void HandleGeneratePatchCheckBoxCheckStateChanged(ECheckBoxState NewState);` — patch generation related functions Callback for check state changes of the 'GeneratePatch' check box.
- L182 _private prototype_ `ECheckBoxState HandleGeneratePatchCheckBoxIsChecked() const;` — Callback for determining the checked state of the 'GeneratePatch' check box.
- L185 _private prototype_ `void HandleAddPatchLevelCheckBoxCheckStateChanged( ECheckBoxState NewState );` — Callback for check state changes of the 'AddPatchLevel' check box.
- L187 _private prototype_ `ECheckBoxState HandleAddPatchLevelCheckBoxIsChecked( ) const;` — Callback for determining the checked state of the 'AddPatchLevel' check box.
- L190 _private prototype_ `FText HandlePatchSourceContentPathTextBlockText() const;` — Callback for changing patchSourceContent path (should be the path of a pak file)
- L192 _private prototype_ `void HandlePatchSourceContentPathCommitted(const FText& NewText, ETextCommit::Type CommitType);` — Callback for getting the PatchSourceContentPath
- L196 _private prototype_ `void HandleBuildDLCCheckBoxCheckStateChanged(ECheckBoxState NewState);` — dlc check box related functions
- L197 _private prototype_ `ECheckBoxState HandleBuildDLCCheckBoxIsChecked() const;`
- L198 _private prototype_ `void HandleDLCNameCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L199 _private prototype_ `FText HandleDLCNameTextBlockText() const;`
- L200 _private prototype_ `void HandleDLCIncludeEngineContentCheckBoxCheckStateChanged(ECheckBoxState NewState);`
- L201 _private prototype_ `ECheckBoxState HandleDLCIncludeEngineContentCheckBoxIsChecked() const;`
- L205 _private prototype_ `FReply HandleHtppChunkInstallBrowseButtonClicked();` — Http Chunk Installer options & functions
- L206 _private prototype_ `FText HandleHtppChunkInstallDirectoryText() const;`
- L207 _private prototype_ `void HandleHtppChunkInstallDirectoryTextChanged(const FText& InText);`
- L208 _private prototype_ `void HandleHtppChunkInstallDirectoryTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L209 _private prototype_ `void HandleHttpChunkInstallCheckBoxCheckStateChanged(ECheckBoxState NewState);`
- L210 _private prototype_ `ECheckBoxState HandleHttpChunkInstallCheckBoxIsChecked() const;`
- L211 _private prototype_ `FText HandleHttpChunkInstallNameTextBlockText() const;`
- L212 _private prototype_ `void HandleHtppChunkInstallNameCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L215 _private prototype_ `TSharedRef<SWidget> MakeComplexWidget();` — creates the complex widget.
- L218 _private prototype_ `TSharedRef<SWidget> MakeSimpleWidget();` — creates the simple widget.
- L223 _private member_ `TSharedPtr<SEditableTextBox> PatchSourceContentPath;` — Textbox which holds the PatchSourceContentPath
- L226 _private member_ `TSharedPtr<SEditableTextBox> DLCBasedOnReleaseVersionName;` — Textbox which holds the DLCBasedOnReleaseVersion
- L229 _private member_ `TArray<TSharedPtr<FString> > CultureList;` — Holds the culture list.
- L232 _private member_ `TSharedPtr<SListView<TSharedPtr<FString> > > CultureListView;` — Holds the map list view.
- L235 _private member_ `TArray<TSharedPtr<FString> > MapList;` — Holds the map list.
- L238 _private member_ `TSharedPtr<SListView<TSharedPtr<FString> > > MapListView;` — Holds the map list view.
- L241 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L244 _private member_ `EShowMapsChoices::Type ShowMapsChoice;` — Holds the current 'Show maps' check box choice.
- L247 _private member_ `TSharedPtr<SEditableTextBox> HttpChunkInstallDirectoryTextBox;` — Holds the Http Chunk Install directory path text box.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace EShowMapsChoices`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherCookOnTheFlySettings.h` (Private)


#### class `SProjectLauncherCookOnTheFlySettings`  
`class SProjectLauncherCookOnTheFlySettings : public SCompoundWidget`  
_L17-66_
- inherits: `SCompoundWidget`
- desc: Implements the cook-by-the-book settings panel.
- L22 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherCookOnTheFlySettings)`
- L30 _public prototype_ `~SProjectLauncherCookOnTheFlySettings( );` — Destructor.
- L40 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L45 _private prototype_ `void HandleIncrementalCheckBoxCheckStateChanged( ECheckBoxState NewState );` — Callback for check state changes of the 'Incremental' check box.
- L48 _private prototype_ `ECheckBoxState HandleIncrementalCheckBoxIsChecked( ) const;` — Callback for determining the checked state of the 'Incremental' check box.
- L51 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L54 _private prototype_ `EVisibility HandleValidationErrorIconVisibility( ELauncherProfileValidationErrors::Type Error ) const;` — Callback for determining the visibility of a validation error icon.
- L57 _private prototype_ `FText HandleCookOptionsTextBlockText() const;` — Callback for getting the cookers additional options
- L60 _private prototype_ `void HandleCookerOptionsCommitted(const FText& NewText, ETextCommit::Type CommitType);` — Callback for changing the cookers additional options
- L65 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherCookPage.h` (Private)


#### class `SProjectLauncherCookPage`  
`class SProjectLauncherCookPage : public SCompoundWidget`  
_L16-71_
- inherits: `SCompoundWidget`
- desc: Implements the profile page for the session launcher wizard.
- L21 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherCookPage)`
- L29 _public prototype_ `~SProjectLauncherCookPage( );` — Destructor.
- L39 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L44 _private prototype_ `EVisibility HandleCookByTheBookSettingsVisibility( ) const;` — Callback for getting the visibility of the cook-by-the-book settings area.
- L47 _private prototype_ `FText HandleCookModeComboButtonContentText( ) const;` — Callback for getting the content text of the 'Cook Mode' combo button.
- L50 _private prototype_ `void HandleCookModeMenuEntryClicked( ELauncherProfileCookModes::Type CookMode );` — Callback for clicking an item in the 'Cook Mode' menu.
- L53 _private prototype_ `EVisibility HandleCookOnTheFlySettingsVisibility( ) const;` — Callback for getting the visibility of the cook-on-the-fly settings area.
- L56 _private prototype_ `void HandleProfileManagerProfileListChanged( );` — Callback for changing the list of profiles in the profile manager.
- L59 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L64 _private member_ `TSharedPtr<SEditableTextBox> CookerOptionsTextBox;` — Holds the cooker options text box.
- L67 _private member_ `TArray<TSharedPtr<FString> > CookModeList;` — Holds the list of available cook modes.
- L70 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherCookedPlatforms.h` (Private)


#### class `SProjectLauncherCookedPlatforms`  
`class SProjectLauncherCookedPlatforms : public SCompoundWidget`  
_L21-135_
- inherits: `SCompoundWidget`
- desc: Implements the cooked platforms panel.
- L26 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherCookedPlatforms)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Construct the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L46 _protected function_ `void MakePlatformMenu()` — Build the platform menu. @return Platform menu widget.
- L65 _private function_ `void HandleAllPlatformsHyperlinkNavigate(bool AllPlatforms)` — Callback for clicking the 'Select All Platforms' button.
- L90 _private function_ `EVisibility HandleAllPlatformsHyperlinkVisibility() const` — Callback for determining the visibility of the 'Select All Platforms' button.
- L101 _private function_ `FSlateColor HandlePlatformMenuEntryColorAndOpacity(FString PlatformName) const` — Callback for getting the color of a platform menu check box.
- L122 _private prototype_ `TSharedRef<ITableRow> HandlePlatformListViewGenerateRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget in the map list view.
- L127 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Pointer to the data model.
- L130 _private member_ `TArray<TSharedPtr<FString> > PlatformList;` — The platform list.
- L133 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> PlatformListView;` — The platform list view.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherCultureListRow.h` (Private)


#### class `SProjectLauncherCultureListRow`  
`class SProjectLauncherCultureListRow : public SMultiColumnTableRow<TSharedPtr<FString> >`  
_L23-124_
- inherits: `SMultiColumnTableRow<TSharedPtr<FString>>`
- desc: Implements a row widget for map list.
- L28 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherCultureListRow)`
- L42 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel )` — Constructs the widget. @param InArgs The construction arguments. @param InProfileManager The profile manager to use.
- L60 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override` — Generates the widget for the specified column. @param ColumnName The name of the column to generate the widget for. @return The widget.
- L82 _private function_ `void HandleCheckBoxCheckStateChanged( ECheckBoxState NewState )` — Callback for changing the checked state of the check box.
- L100 _private function_ `ECheckBoxState HandleCheckBoxIsChecked( ) const` — Callback for determining the checked state of the check box.
- L117 _private member_ `TAttribute<FString> HighlightString;` — Holds the highlight string for the log message.
- L120 _private member_ `TSharedPtr<FString> CultureName;` — Holds the map's name.
- L123 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherCultureListRow"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherMapListRow.h` (Private)


#### class `SProjectLauncherMapListRow`  
`class SProjectLauncherMapListRow : public SMultiColumnTableRow<TSharedPtr<FString> >`  
_L23-123_
- inherits: `SMultiColumnTableRow<TSharedPtr<FString>>`
- desc: Implements a row widget for map list.
- L28 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherMapListRow)`
- L42 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel )` — Constructs the widget. @param InArgs The construction arguments. @param InProfileManager The profile manager to use.
- L59 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override` — Generates the widget for the specified column. @param ColumnName The name of the column to generate the widget for. @return The widget.
- L81 _private function_ `void HandleCheckBoxCheckStateChanged( ECheckBoxState NewState )` — Callback for changing the checked state of the check box.
- L99 _private function_ `ECheckBoxState HandleCheckBoxIsChecked( ) const` — Callback for determining the checked state of the check box.
- L116 _private member_ `TAttribute<FString> HighlightString;` — Holds the highlight string for the log message.
- L119 _private member_ `TSharedPtr<FString> MapName;` — Holds the map's name.
- L122 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherMapListRow"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherPlatformListRow.h` (Private)


#### class `SProjectLauncherPlatformListRow`  
`class SProjectLauncherPlatformListRow : public SMultiColumnTableRow<TSharedPtr<FString> >`  
_L23-127_
- inherits: `SMultiColumnTableRow<TSharedPtr<FString>>`
- desc: Implements a row widget for map list.
- L28 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherPlatformListRow)`
- L42 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel )` — Constructs the widget. @param InArgs The construction arguments. @param InProfileManager The profile manager to use.
- L59 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override` — Generates the widget for the specified column. @param ColumnName The name of the column to generate the widget for. @return The widget.
- L81 _private function_ `void HandleCheckBoxCheckStateChanged( ECheckBoxState NewState )` — Callback for changing the checked state of the check box.
- L99 _private function_ `ECheckBoxState HandleCheckBoxIsChecked( ) const` — Callback for determining the checked state of the check box.
- L120 _private member_ `TAttribute<FString> HighlightString;` — Holds the highlight string for the log message.
- L123 _private member_ `TSharedPtr<FString> PlatformName;` — Holds the platform's name.
- L126 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherPlatformListRow"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Cook/SProjectLauncherSimpleCookPage.h` (Private)


#### class `SProjectLauncherSimpleCookPage`  
`class SProjectLauncherSimpleCookPage : public SCompoundWidget`  
_L16-71_
- inherits: `SCompoundWidget`
- desc: Implements the profile page for the session launcher wizard.
- L21 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherSimpleCookPage)`
- L29 _public prototype_ `~SProjectLauncherSimpleCookPage( );` — Destructor.
- L39 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L44 _private prototype_ `EVisibility HandleCookByTheBookSettingsVisibility( ) const;` — Callback for getting the visibility of the cook-by-the-book settings area.
- L47 _private prototype_ `FText HandleCookModeComboButtonContentText( ) const;` — Callback for getting the content text of the 'Cook Mode' combo button.
- L50 _private prototype_ `void HandleCookModeMenuEntryClicked( ELauncherProfileCookModes::Type CookMode );` — Callback for clicking an item in the 'Cook Mode' menu.
- L53 _private prototype_ `EVisibility HandleCookOnTheFlySettingsVisibility( ) const;` — Callback for getting the visibility of the cook-on-the-fly settings area.
- L56 _private prototype_ `void HandleProfileManagerProfileListChanged( );` — Callback for changing the list of profiles in the profile manager.
- L59 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L64 _private member_ `TSharedPtr<SEditableTextBox> CookerOptionsTextBox;` — Holds the cooker options text box.
- L67 _private member_ `TArray<TSharedPtr<FString> > CookModeList;` — Holds the list of available cook modes.
- L70 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeployFileServerSettings.h` (Private)


#### class `SProjectLauncherDeployFileServerSettings`  
`class SProjectLauncherDeployFileServerSettings : public SCompoundWidget`  
_L17-53_
- inherits: `SCompoundWidget`
- desc: Implements the deploy-to-device settings panel.
- L22 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeployFileServerSettings)`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L38 _private prototype_ `void HandleHideWindowCheckBoxCheckStateChanged(ECheckBoxState NewState);` — Callback for check state changes of the 'Hide Window' check box.
- L41 _private prototype_ `ECheckBoxState HandleHideWindowCheckBoxIsChecked() const;` — Callback for determining the checked state of the 'Hide Window' check box.
- L44 _private prototype_ `void HandleStreamingServerCheckBoxCheckStateChanged(ECheckBoxState NewState);` — Callback for check state changes of the 'Streaming Server' check box.
- L47 _private prototype_ `ECheckBoxState HandleStreamingServerCheckBoxIsChecked() const;` — Callback for determining the checked state of the 'Streaming Server' check box.
- L52 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeployPage.h` (Private)


#### class `SProjectLauncherDeployPage`  
`class SProjectLauncherDeployPage : public SCompoundWidget`  
_L16-68_
- inherits: `SCompoundWidget`
- desc: Implements the devices page for the session launcher wizard.
- L21 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeployPage)`
- L29 _public prototype_ `~SProjectLauncherDeployPage( );` — Destructor.
- L39 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel, bool IsFromRepository = false );` — Constructs the widget. @param InArgs - The Slate argument list. @param InModel - The data model.
- L44 _private prototype_ `FText HandleDeploymentModeComboButtonContentText( ) const;` — Callback for getting the content text of the 'Deployment Mode' combo button.
- L47 _private prototype_ `void HandleDeploymentModeMenuEntryClicked( ELauncherProfileDeploymentModes::Type DeploymentMode );` — Callback for clicking an item in the 'Deployment Mode' menu.
- L50 _private prototype_ `EVisibility HandleDeployFileServerSettingsVisibility( ) const;` — Callback for getting the visibility of the deployment targets area.
- L53 _private prototype_ `EVisibility HandleDeployToDeviceSettingsVisibility( ) const;` — Callback for getting the visibility of the deployment targets area.
- L56 _private prototype_ `EVisibility HandleDeployRepositorySettingsVisibility( ) const;` — Callback for getting the visibility of the deployment repository area.
- L59 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L62 _private prototype_ `EVisibility HandleValidationErrorIconVisibility( ELauncherProfileValidationErrors::Type Error ) const;` — Callback for determining the visibility of a validation error icon.
- L67 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeployRepositorySettings.h` (Private)


#### class `SProjectLauncherDeployRepositorySettings`  
`class SProjectLauncherDeployRepositorySettings : public SCompoundWidget`  
_L16-50_
- inherits: `SCompoundWidget`
- desc: Implements the deploy-to-device settings panel.
- L21 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeployRepositorySettings)`
- L32 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs - The Slate argument list. @param InModel - The data model.
- L36 _private prototype_ `FReply HandleBrowseButtonClicked( );`
- L39 _private prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Handles entering in a command
- L41 _private prototype_ `void OnTextChanged(const FText& InText);`
- L46 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L49 _private member_ `TSharedPtr<SEditableTextBox> RepositoryPathTextBox;` — Holds the repository path text box.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeployTargetListRow.h` (Private)


#### class `SProjectLauncherDeployTargetListRow`  
`class SProjectLauncherDeployTargetListRow : public SMultiColumnTableRow<TSharedPtr<ITargetDeviceProxy>>`  
_L32-339_
- inherits: `SMultiColumnTableRow<TSharedPtr<ITargetDeviceProxy>>`
- desc: Implements a row widget for the launcher's device proxy list.
- L37 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeployTargetListRow)`
- L64 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs - The construction arguments. @param InDeviceGroup - The device group that is being edited.
- L100 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override` — Generates the widget for the specified column. @param ColumnName - The name of the column to generate the widget for. @return The widget.
- L195 _private function_ `void HandleCheckBoxStateChanged(ECheckBoxState NewState)` — Callback for changing this row's check box state.
- L214 _private function_ `ECheckBoxState HandleCheckBoxIsChecked() const` — Callback for determining this row's check box state.
- L231 _private function_ `FText HandleVariantSelectorText() const` — Callback for getting the text of the current variant
- L247 _private function_ `void HandleVariantSelectorVariantSelected(FName InVariant)` — Callback for changing the selected variant
- L270 _private function_ `const FSlateBrush* HandleDeviceImage() const` — Callback for getting the icon image of the device.
- L284 _private function_ `FText HandleDeviceNameText() const` — Callback for getting the friendly name.
- L297 _private function_ `FText HandleHostNameText() const` — Callback for getting the host name.
- L303 _private function_ `FText HandleHostUserText() const` — Callback for getting the host user name.
- L309 _private function_ `FText HandleHostPlatformText() const` — Callback for getting the host platform name.
- L319 _private function_ `FText HandleHostNoVariantText() const` — Callback for getting the default variant name in the case where
- L327 _private member_ `TAttribute<ILauncherDeviceGroupPtr> DeviceGroup;` — Holds a pointer to the device group that is being edited.
- L330 _private member_ `TSharedPtr<ITargetDeviceProxy> DeviceProxy;` — Holds a reference to the device proxy that is displayed in this row.
- L332 _private member_ `TSharedPtr<SCheckBox> DeviceCheckbox;`
- L335 _private member_ `FName SelectedVariant;` — Holds the name of the selected variant.
- L338 _private member_ `TAttribute<FText> HighlightText;` — Holds the highlight string for the log message.

#### Free symbols / members of external scopes

- L27 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherDeployTargetListRow"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeployTargets.h` (Private)


#### class `SProjectLauncherDeployTargets`  
`class SProjectLauncherDeployTargets : public SCompoundWidget`  
_L21-118_
- inherits: `SCompoundWidget`
- desc: Implements the deployment targets panel.
- L26 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeployTargets)`
- L34 _public prototype_ `~SProjectLauncherDeployTargets( );` — Destructor.
- L44 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L51 _protected prototype_ `void RefreshDeviceProxyList( );` — Refreshes the list of device proxies.
- L56 _private prototype_ `void HandleDeviceGroupSelectorGroupSelected(const ILauncherDeviceGroupPtr& SelectedGroup);` — Callback for selecting a different device group in the device group selector.
- L59 _private prototype_ `ILauncherDeviceGroupPtr HandleDeviceListRowDeviceGroup() const;` — Callback for getting the currently selected device group for a device list row.
- L62 _private prototype_ `bool HandleDeviceListRowIsEnabled(TSharedPtr<ITargetDeviceProxy> DeviceProxy) const;` — Callback for getting the enabled state of a device proxy list row.
- L65 _private prototype_ `FText HandleDeviceListRowToolTipText(TSharedPtr<ITargetDeviceProxy> DeviceProxy) const;` — Callback for getting the tool tip text of a device proxy list row.
- L68 _private prototype_ `TSharedRef<ITableRow> HandleDeviceProxyListViewGenerateRow(TSharedPtr<ITargetDeviceProxy> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback for generating a row in the device list view.
- L71 _private prototype_ `EVisibility HandleDeviceProxyListViewVisibility() const;` — Callback for determining the visibility of the device list view.
- L74 _private prototype_ `EVisibility HandleDeviceSelectorVisibility() const;` — Callback for getting a flag indicating whether a valid device group is currently selected.
- L77 _private prototype_ `EVisibility HandleNoDevicesBoxVisibility() const;` — Callback for getting the visibility of the 'No devices detected' text block.
- L80 _private prototype_ `FText HandleNoDevicesTextBlockText() const;` — Callback for getting the text in the 'no devices' text block.
- L83 _private prototype_ `EVisibility HandleSelectDeviceGroupWarningVisibility() const;` — Callback for determining the visibility of the 'Select a device group' text block.
- L86 _private prototype_ `void HandleDeviceProxyManagerProxyAdded(const TSharedRef<ITargetDeviceProxy>& AddedProxy);` — Callback for when a device proxy has been added to the device proxy manager.
- L89 _private prototype_ `void HandleDeviceProxyManagerProxyRemoved(const TSharedRef<ITargetDeviceProxy>& RemovedProxy);` — Callback for when a device proxy has been removed from the device proxy manager.
- L92 _private prototype_ `FText HandlePlatformComboBoxContentText() const;` — Callback for getting the name of the selected default platform.
- L95 _private prototype_ `TSharedRef<SWidget> HandlePlatformComboBoxGenerateWidget(TSharedPtr<FName> StringItem);` — Callback for generating widgets for the platforms combo box.
- L98 _private prototype_ `void HandlePlatformComboBoxSelectionChanged(TSharedPtr<FName> StringItem, ESelectInfo::Type SelectInfo);` — Callback for handling default platform selection changes.
- L103 _private member_ `TArray<TSharedPtr<ITargetDeviceProxy>> DeviceProxyList;` — Holds the list of available device proxies.
- L106 _private member_ `TArray<TSharedPtr<FName>> VanillaPlatformList;` — Holds the list of vanilla platforms.
- L109 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> PlatformComboBox;` — Holds the list of vanilla platform options.
- L110 _private member_ `mutable FText DefaultPlatformText;`
- L113 _private member_ `TSharedPtr<SListView<TSharedPtr<ITargetDeviceProxy>> > DeviceProxyListView;` — Holds the device proxy list view .
- L116 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeployTaskSettings.h` (Private)


#### class `SProjectLauncherDeployTaskSettings`  
`class SProjectLauncherDeployTaskSettings : public SCompoundWidget`  
_L13-42_
- inherits: `SCompoundWidget`
- desc: Implements the launcher settings widget.
- L18 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeployTaskSettings)`
- L26 _public prototype_ `~SProjectLauncherDeployTaskSettings( );` — Destructor.
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L41 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeployToDeviceSettings.h` (Private)


#### class `SProjectLauncherDeployToDeviceSettings`  
`class SProjectLauncherDeployToDeviceSettings : public SCompoundWidget`  
_L16-46_
- inherits: `SCompoundWidget`
- desc: Implements the deploy-to-device settings panel.
- L21 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeployToDeviceSettings)`
- L32 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel, EVisibility InShowAdvanced = EVisibility::Visible );` — Constructs the widget. @param InArgs - The Slate argument list. @param InModel - The data model.
- L39 _private prototype_ `void HandleIncrementalCheckBoxCheckStateChanged( ECheckBoxState NewState );` — Handles check state changes of the 'Incremental' check box.
- L42 _private prototype_ `ECheckBoxState HandleIncrementalCheckBoxIsChecked( ) const;` — Handles determining the checked state of the 'Incremental' check box.
- L45 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherDeviceGroupSelector.h` (Private)


#### class `SProjectLauncherDeviceGroupSelector`  
`class SProjectLauncherDeviceGroupSelector : public SCompoundWidget`  
_L24-129_
- inherits: `SCompoundWidget`
- desc: Implements a widget for device group selection.
- L29 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherDeviceGroupSelector)`
- L48 _public function_ `~SProjectLauncherDeviceGroupSelector( )` — Destructor.
- L65 _public prototype_ `void Construct( const FArguments& InArgs, const ILauncherProfileManagerRef& InProfileManager );` — Constructs the widget. @param InArgs - The Slate argument list. @param InProfileManager - The profile manager to use.
- L74 _public prototype_ `ILauncherDeviceGroupPtr GetSelectedGroup( ) const;` — Gets the currently selected device group. @return The selected group, or NULL if no group is selected. @see SetSelectedGroup
- L83 _public prototype_ `void SetSelectedGroup( const ILauncherDeviceGroupPtr& DeviceGroup );` — Sets the selected device group. @param DeviceGroup - The device group to select. @see GetSelectedGroup
- L88 _private prototype_ `FReply HandleDeviceGroupComboBoxAddClicked( );` — Callback for clicking the 'Add device group' button
- L91 _private prototype_ `FText HandleDeviceGroupComboBoxContent() const;` — Callback for getting the device group combo box content.
- L94 _private prototype_ `TSharedRef<SWidget> HandleDeviceGroupComboBoxGenerateWidget( ILauncherDeviceGroupPtr InItem );` — Callback for generating a row for the device group combo box.
- L97 _private prototype_ `FString HandleDeviceGroupComboBoxGetEditableText( );` — Callback for getting the editable text of the currently selected device group.
- L100 _private prototype_ `FReply HandleDeviceGroupComboBoxRemoveClicked( );` — Callback for clicking the 'Delete device group' button
- L103 _private function_ `void HandleDeviceGroupComboBoxSelectionChanged( ILauncherDeviceGroupPtr Selection, ESelectInfo::Type SelectInfo )` — Callback for changing the selected device group in the device group combo box.
- L109 _private prototype_ `void HandleDeviceGroupComboBoxSelectionRenamed( const FText& CommittedText, ETextCommit::Type );` — Callback for when the selected item in the device group combo box has been renamed.
- L112 _private prototype_ `FText HandleDeviceGroupComboBoxWidgetText( ILauncherDeviceGroupPtr Group ) const;` — Callback for getting the text of a device group combo box widget.
- L115 _private prototype_ `void HandleProfileManagerDeviceGroupsChanged( const ILauncherDeviceGroupRef& );` — Callback for changing the list of groups in the profile manager.
- L120 _private member_ `TSharedPtr<SEditableComboBox<ILauncherDeviceGroupPtr> > DeviceGroupComboBox;` — Holds the device group combo box.
- L123 _private member_ `ILauncherProfileManagerPtr ProfileManager;` — Holds the profile manager.
- L128 _private member_ `FOnProjectLauncherDeviceGroupSelected OnGroupSelected;` — Holds a delegate to be invoked when a different device group has been selected.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProjectLauncherDeviceGroupSelected, const ILauncherDeviceGroupPtr&) class SProjectLauncherDeviceGroupSelector : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SProjectLauncherDeviceGroupSelector) { } SLATE_ARGUMENT(ILauncherDeviceGroupPtr, InitiallySelectedGroup) SLATE_EVENT(FOnProjectLauncherDeviceGroupSelected, OnGroupSelected) SLATE_END_ARGS() public: ~SProjectLauncherDeviceGroupSelector( ) { if (ProfileManager.IsValid()) { ProfileManager->OnDeviceGroupAdded().RemoveAll(this); ProfileManager->OnDeviceGroupRemoved().RemoveAll(this); } } public:` — Delegate type for device group selection changes. The first parameter is the selected device group (or NULL if the previously selected group was unselected).

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherSimpleDeviceListRow.h` (Private)


#### class `SProjectLauncherSimpleDeviceListRow`  
`class SProjectLauncherSimpleDeviceListRow : public STableRow<TSharedPtr<ITargetDeviceProxy>>`  
_L36-510_
- inherits: `STableRow<TSharedPtr<ITargetDeviceProxy>>`
- desc: Implements a row widget for the launcher's device proxy list.
- L41 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherSimpleDeviceListRow)`
- L61 _public function_ `~SProjectLauncherSimpleDeviceListRow()`
- L75 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs - The construction arguments. @param InModel - The launcher model this list uses.
- L209 _private function_ `void MakeSimpleSettings(TSharedRef<SUniformGridPanel> InNameColumn, TSharedRef<SUniformGridPanel> InValueColumn)`
- L220 _private function_ `void MakeAdvancedSettings(TSharedRef<SUniformGridPanel> InNameColumn, TSharedRef<SUniformGridPanel> InValueColumn)`
- L233 _private function_ `void MakeVariantRow(TSharedRef<SUniformGridPanel> InNameColumn, TSharedRef<SUniformGridPanel> InValueColumn, int InRowIndex)`
- L252 _private function_ `FText HandleVariantSelectorText() const`
- L267 _private function_ `void HandleVariantSelectorVariantSelected(FName InVariant)`
- L278 _private function_ `void MakeBuildConfigurationRow(TSharedRef<SUniformGridPanel> InNameColumn, TSharedRef<SUniformGridPanel> InValueColumn, int InRowIndex)`
- L299 _private function_ `FText HandleBuildConfigurationSelectorText() const`
- L309 _private function_ `void HandleBuildConfigurationSelectorConfigurationSelected(EBuildConfiguration Configuration)`
- L320 _private function_ `void MakeCookModeRow(TSharedRef<SUniformGridPanel> InNameColumn, TSharedRef<SUniformGridPanel> InValueColumn, int InRowIndex)`
- L341 _private function_ `FText HandleCookModeSelectorText() const`
- L361 _private function_ `void HandleCookModeSelectorConfigurationSelected(ELauncherProfileCookModes::Type CookMode)`
- L371 _private function_ `void UpdateProfile()`
- L420 _private function_ `ILauncherProfilePtr GetLaunchProfile() const`
- L425 _private function_ `FReply OnLaunchClicked()`
- L436 _private function_ `EVisibility IsAdvancedVisible() const` — Callback for whether advanced options are shown.
- L443 _private function_ `const FSlateBrush* HandleDeviceImage( ) const` — Callback for getting the icon image of the device.
- L457 _private function_ `FText HandleDeviceNameText() const` — Callback for getting the friendly name.
- L470 _private function_ `FText HandleHostNameText( ) const` — Callback for getting the host name.
- L476 _private function_ `FText HandleHostUserText( ) const` — Callback for getting the host user name.
- L482 _private function_ `FText HandleHostPlatformText( ) const` — Callback for getting the host platform name.
- L494 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L497 _private member_ `TSharedPtr<ITargetDeviceProxy> DeviceProxy;` — Holds a reference to the device proxy that is displayed in this row.
- L500 _private member_ `ILauncherSimpleProfilePtr SimpleProfile;` — Holds a reference to the simple profile for this device
- L503 _private member_ `ILauncherProfilePtr LaunchProfile;` — Holds a reference to the generated full launch profile for this device.
- L506 _private member_ `TAttribute<bool> IsAdvanced;` — Specifies that whether options are shown.
- L509 _private member_ `FOnProfileRun OnProfileRun;` — Holds a delegate to be invoked when a profile is run.

#### Free symbols / members of external scopes

- L31 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherSimpleDeviceListRow"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Deploy/SProjectLauncherSimpleDeviceListView.h` (Private)


#### class `SProjectLauncherSimpleDeviceListView`  
`class SProjectLauncherSimpleDeviceListView : public SCompoundWidget`  
_L24-91_
- inherits: `SCompoundWidget`
- desc: Implements the deployment targets panel.
- L29 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherSimpleDeviceListView)`
- L37 _public prototype_ `~SProjectLauncherSimpleDeviceListView();` — Destructor.
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model. @param InAdvanced Whether or not the elements should show advanced data.
- L53 _protected prototype_ `void RefreshDeviceProxyList();` — Refresh the list of device proxies.
- L58 _private prototype_ `bool HandleDeviceListRowIsEnabled(TSharedPtr<ITargetDeviceProxy> DeviceProxy) const;` — Callback for getting the enabled state of a device proxy list row.
- L61 _private prototype_ `void HandleDeviceManagerHyperlinkNavigate() const;` — Callback when the user clicks the Device Manager hyperlink.
- L64 _private prototype_ `FText HandleDeviceListRowToolTipText(TSharedPtr<ITargetDeviceProxy> DeviceProxy) const;` — Callback for getting the tool tip text of a device proxy list row.
- L67 _private prototype_ `TSharedRef<ITableRow> HandleDeviceProxyListViewGenerateRow(TSharedPtr<ITargetDeviceProxy> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback for generating a row in the device list view.
- L70 _private prototype_ `void HandleDeviceProxyManagerProxyAdded(const TSharedRef<ITargetDeviceProxy>& AddedProxy);` — Callback for when a device proxy has been added to the device proxy manager.
- L73 _private prototype_ `void HandleDeviceProxyManagerProxyRemoved(const TSharedRef<ITargetDeviceProxy>& RemovedProxy);` — Callback for when a device proxy has been added to the device proxy manager.
- L78 _private member_ `TArray<TSharedPtr<ITargetDeviceProxy>> DeviceProxyList;` — Holds the list of available device proxies.
- L81 _private member_ `TSharedPtr<SListView<TSharedPtr<ITargetDeviceProxy>> > DeviceProxyListView;` — Holds the device proxy list view .
- L84 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L87 _private member_ `TAttribute<bool> IsAdvanced;` — Specifies whether advanced options are shown.
- L90 _private member_ `FOnProfileRun OnProfileRun;` — Holds a delegate to be invoked when a profile is run.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Launch/SProjectLauncherLaunchCustomRoles.h` (Private)


#### class `SProjectLauncherLaunchCustomRoles`  
`class SProjectLauncherLaunchCustomRoles : public SCompoundWidget`  
_L13-42_
- inherits: `SCompoundWidget`
- desc: Implements the settings panel for launching with custom roles.
- L18 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherLaunchCustomRoles)`
- L26 _public prototype_ `~SProjectLauncherLaunchCustomRoles( );` — Destructor.
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs - The Slate argument list. @param InModel - The data model.
- L41 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Launch/SProjectLauncherLaunchPage.h` (Private)


#### class `SProjectLauncherLaunchPage`  
`class SProjectLauncherLaunchPage : public SCompoundWidget`  
_L17-86_
- inherits: `SCompoundWidget`
- desc: Implements the profile page for the session launcher wizard.
- L22 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherLaunchPage)`
- L30 _public prototype_ `~SProjectLauncherLaunchPage( );` — Destructor.
- L40 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L45 _public prototype_ `void Refresh( );` — Refreshes the widget.
- L50 _private prototype_ `EVisibility HandleCannotLaunchTextBlockVisibility( ) const;` — Callback for getting the visibility of the 'Cannot launch' text block.
- L53 _private prototype_ `EVisibility HandleLaunchModeBoxVisibility( ) const;` — Callback for determining the visibility of the 'Launch Mode' box.
- L56 _private prototype_ `FText HandleLaunchModeComboButtonContentText( ) const;` — Callback for getting the content text of the 'Launch Mode' combo button.
- L59 _private prototype_ `void HandleLaunchModeMenuEntryClicked( ELauncherProfileLaunchModes::Type LaunchMode );` — Callback for clicking an item in the 'Launch Mode' menu.
- L62 _private prototype_ `EVisibility HandleLaunchSettingsVisibility( ) const;` — Callback for getting the visibility state of the launch settings area.
- L65 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L68 _private prototype_ `EVisibility HandleValidationErrorIconVisibility( ELauncherProfileValidationErrors::Type Error ) const;` — Callback for determining the visibility of a validation error icon.
- L71 _private prototype_ `void HandleProfileProjectChanged();` — Callback for updating any settings after the selected project has changed in the profile
- L76 _private member_ `TSharedPtr<SProjectLauncherLaunchRoleEditor> DefaultRoleEditor;` — Holds the default role editor.
- L79 _private member_ `TArray<FString> AvailableCultures;` — Holds the list of cultures that are available for the selected game.
- L82 _private member_ `TArray<FString> AvailableMaps;` — Holds the list of maps that are available for the selected game.
- L85 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Launch/SProjectLauncherLaunchRoleEditor.h` (Private)


#### class `SProjectLauncherLaunchRoleEditor`  
`class SProjectLauncherLaunchRoleEditor : public SCompoundWidget`  
_L21-271_
- inherits: `SCompoundWidget`
- desc: Implements the settings panel for a single launch role.
- L26 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherLaunchRoleEditor) : _AvailableCultures() , _AvailableMaps()`
- L50 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs the widget. @param InArgs The Slate argument list. @param InRole The launch role to edit.
- L57 _public prototype_ `void Refresh( const ILauncherProfileLaunchRolePtr& InRole );` — Refreshes the widget. @param InRole The role to edit, or NULL if no role is being edited.
- L62 _private function_ `void HandleCommandLineTextBoxTextChanged( const FText& InText )` — Callback for when the text of the command line text box has changed.
- L73 _private function_ `FText HandleInstanceTypeComboButtonContentText( ) const` — Callback for getting the name of the selected instance type.
- L86 _private function_ `void HandleInstanceTypeMenuEntryClicked( ELauncherProfileRoleInstanceTypes::Type InstanceType )` — Callback for clicking an item in the 'Instance type' menu.
- L97 _private function_ `FSlateColor HandleCultureComboBoxColorAndOpacity( ) const` — Callback for getting the foreground text color of the culture combo box.
- L115 _private function_ `void HandleCultureComboBoxSelectionChanged( TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo )` — Callback for changing the initial culture selection.
- L133 _private function_ `EVisibility HandleCultureValidationErrorIconVisibility( ) const` — Callback for getting the visibility of the validation error icon of the 'Initial Culture' combo box.
- L151 _private function_ `EVisibility HandleLaunchAsValidationErrorIconVisibility( ) const` — Callback for getting the visibility of the validation error icon of the 'Launch As' combo box.
- L157 _private function_ `FSlateColor HandleMapComboBoxColorAndOpacity( ) const` — Callback for getting the foreground text color of the map combo box.
- L175 _private function_ `void HandleMapComboBoxSelectionChanged( TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo )` — Callback for changing the initial map selection.
- L193 _private function_ `EVisibility HandleMapValidationErrorIconVisibility( ) const` — Callback for getting the visibility of the validation error icon of the 'Initial Map' combo box.
- L211 _private function_ `void HandleVsyncCheckBoxCheckStateChanged( ECheckBoxState NewState )` — Callback for checking the specified 'No VSync' check box.
- L222 _private function_ `ECheckBoxState HandleVsyncCheckBoxIsChecked( ) const` — Callback for determining the checked state of the specified 'No VSync' check box.
- L240 _private member_ `const TArray<FString>* AvailableCultures;` — Holds a pointer to the list of available cultures.
- L243 _private member_ `const TArray<FString>* AvailableMaps;` — Holds a pointer to the list of available maps.
- L246 _private member_ `TSharedPtr<SEditableTextBox> CommandLineTextBox;` — Holds the command line text box.
- L249 _private member_ `TSharedPtr<SComboBox<TSharedPtr<ELauncherProfileRoleInstanceTypes::Type> > > InstanceTypeComboBox;` — Holds the instance type combo box.
- L252 _private member_ `TArray<TSharedPtr<ELauncherProfileRoleInstanceTypes::Type> > InstanceTypeList;` — Holds the list of instance types.
- L255 _private member_ `TSharedPtr<STextComboBox> CultureComboBox;` — Holds the culture text box.
- L258 _private member_ `TArray<TSharedPtr<FString> > CultureList;` — Holds the list of cultures that are available for the selected game.
- L261 _private member_ `TSharedPtr<STextComboBox> MapComboBox;` — Holds the map text box.
- L264 _private member_ `TArray<TSharedPtr<FString> > MapList;` — Holds the list of maps that are available for the selected game.
- L267 _private member_ `TWeakPtr<ILauncherProfile> Profile;` — Holds the profile that owns the role being edited.
- L270 _private member_ `TWeakPtr<ILauncherProfileLaunchRole> Role;` — Holds a pointer to the role that is being edited in this widget.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Launch/SProjectLauncherLaunchTaskSettings.h` (Private)


#### class `SProjectLauncherLaunchTaskSettings`  
`class SProjectLauncherLaunchTaskSettings : public SCompoundWidget`  
_L13-42_
- inherits: `SCompoundWidget`
- desc: Implements the launcher settings widget.
- L18 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherLaunchTaskSettings)`
- L26 _public prototype_ `~SProjectLauncherLaunchTaskSettings( );` — Destructor.
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L41 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Package/SProjectLauncherPackagePage.h` (Private)


#### class `SProjectLauncherPackagePage`  
`class SProjectLauncherPackagePage : public SCompoundWidget`  
_L16-61_
- inherits: `SCompoundWidget`
- desc: Implements the profile page for the session launcher wizard.
- L21 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherPackagePage)`
- L29 _public prototype_ `~SProjectLauncherPackagePage( );` — Destructor.
- L39 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L44 _private prototype_ `FText HandlePackagingModeComboButtonContentText( ) const;` — Callback for getting the content text of the 'Cook Mode' combo button.
- L47 _private prototype_ `void HandlePackagingModeMenuEntryClicked( ELauncherProfilePackagingModes::Type PackagingMode );` — Callback for clicking an item in the 'Cook Mode' menu.
- L50 _private prototype_ `EVisibility HandlePackagingSettingsAreaVisibility( ) const;` — Callback for getting the visibility of the packaging settings area.
- L53 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L58 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L60 _private member_ `TSharedPtr<SProjectLauncherPackagingSettings> ProjectLauncherPackagingSettings;`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Package/SProjectLauncherPackagingSettings.h` (Private)


#### class `SProjectLauncherPackagingSettings`  
`class SProjectLauncherPackagingSettings : public SCompoundWidget`  
_L17-98_
- inherits: `SCompoundWidget`
- desc: Implements the packaging settings panel.
- L22 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherPackagingSettings)`
- L30 _public prototype_ `~SProjectLauncherPackagingSettings( );` — Destructor.
- L40 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L43 _public prototype_ `void UpdatePackagingModeWidgets();` — Update any widgets to reflect the change in packaging mode.
- L47 _private prototype_ `void HandleForDistributionCheckBoxCheckStateChanged(ECheckBoxState NewState);`
- L48 _private prototype_ `ECheckBoxState HandleForDistributionCheckBoxIsChecked() const;`
- L50 _private prototype_ `void HandleIncludePrerequisitesCheckStateChanged(ECheckBoxState NewState);`
- L51 _private prototype_ `ECheckBoxState HandleIncludePrerequisitesCheckBoxIsChecked() const;`
- L53 _private prototype_ `void HandleUseIoStoreCheckStateChanged(ECheckBoxState NewState);`
- L54 _private prototype_ `ECheckBoxState HandleUseIoStoreCheckBoxIsChecked() const;`
- L56 _private prototype_ `void HandleMakeBinaryConfigCheckStateChanged(ECheckBoxState NewState);`
- L57 _private prototype_ `ECheckBoxState HandleMakeBinaryConfigCheckBoxIsChecked() const;`
- L60 _private prototype_ `bool IsReferenceChunkDbEditable() const;` — Reference chunk database handlers.
- L61 _private prototype_ `void OnRefChunkDbFileNameTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L62 _private prototype_ `void OnRefChunkDbFileNameTextChanged(const FText& InText);`
- L63 _private prototype_ `FReply HandleRefChunkDbBrowseButtonClicked();`
- L64 _private prototype_ `void OnRefChunkCryptoFileNameTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L65 _private prototype_ `void OnRefChunkCryptoFileNameTextChanged(const FText& InText);`
- L66 _private prototype_ `FReply HandleRefChunkCryptoBrowseButtonClicked();`
- L70 _private prototype_ `FText HandleDirectoryTitleText() const;` — Callback for getting the content text of the 'Directory' label.
- L71 _private prototype_ `FText HandleDirectoryPathText() const;`
- L74 _private prototype_ `FText HandleHintPathText() const;` — Callback for getting the hint text which contains the default project output path
- L77 _private prototype_ `void HandleProfileManagerProfileSelected( const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile );` — Callback for changing the selected profile in the profile manager.
- L79 _private prototype_ `FReply HandleBrowseButtonClicked();`
- L82 _private prototype_ `bool IsEditable() const;` — Handles entering in a command
- L84 _private prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L86 _private prototype_ `void OnTextChanged(const FText& InText);`
- L91 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L94 _private member_ `TSharedPtr<SEditableTextBox> DirectoryPathTextBox;` — Holds the repository path text box.
- L96 _private member_ `TSharedPtr<SEditableTextBox> ReferenceContainerGlobalFileName;`
- L97 _private member_ `TSharedPtr<SEditableTextBox> ReferenceContainerCryptoKeysFileName;`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Preview/SProjectLauncherPreviewPage.h` (Private)


#### class `SProjectLauncherPreviewPage`  
`class SProjectLauncherPreviewPage : public SCompoundWidget`  
_L21-121_
- inherits: `SCompoundWidget`
- desc: Implements the launcher's preview page.
- L26 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherPreviewPage)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L50 _protected prototype_ `void RefreshDeviceProxyList();` — Refreshes the list of device proxies.
- L55 _private prototype_ `FText HandleBuildConfigurationTextBlockText() const;` — Callback for getting the text in the 'Build Configuration' text block.
- L58 _private prototype_ `FText HandleBuildPlatformsTextBlockText() const;` — Callback for getting the list of platforms to build for.
- L61 _private prototype_ `FText HandleCommandLineTextBlockText() const;` — Callback for getting the text in the 'Command Line' text block.
- L64 _private prototype_ `FText HandleCookedCulturesTextBlockText() const;` — Callback for getting the text in the 'Cooked Cultures' text block.
- L67 _private prototype_ `FText HandleCookedMapsTextBlockText() const;` — Callback for getting the text in the 'Cooked Maps' text block.
- L70 _private prototype_ `FText HandleCookerOptionsTextBlockText() const;` — Callback for getting the text in the 'Cooker Options' text block.
- L73 _private prototype_ `EVisibility HandleCookSummaryBoxVisibility(ELauncherProfileCookModes::Type CookMode) const;` — Callback for getting the visibility of the specified cook summary box.
- L76 _private prototype_ `EVisibility HandleDeployDetailsBoxVisibility() const;` — Callback for getting the visibility of the deploy details box.
- L79 _private prototype_ `EVisibility HandleDeploySummaryBoxVisibility(ELauncherProfileDeploymentModes::Type DeploymentMode) const;` — Callback for getting the visibility of the specified deploy summary box.
- L82 _private prototype_ `TSharedRef<ITableRow> HandleDeviceProxyListViewGenerateRow(TSharedPtr<ITargetDeviceProxy> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row for the device list.
- L85 _private prototype_ `FText HandleInitialCultureTextBlockText() const;` — Callback for getting the text in the 'Initial Culture' text block.
- L88 _private prototype_ `FText HandleInitialMapTextBlockText() const;` — Callback for getting the text in the 'Initial Map' text block.
- L91 _private prototype_ `EVisibility HandleLaunchSummaryBoxVisibility(ELauncherProfileLaunchModes::Type LaunchMode) const;` — Callback for getting the visibility of the specified cook summary box.
- L94 _private prototype_ `FText HandleLaunchVsyncTextBlockText() const;` — Callback for getting the text in the 'VSync' text block.
- L97 _private prototype_ `EVisibility HandlePackageSummaryBoxVisibility(ELauncherProfilePackagingModes::Type PackagingMode) const;` — Callback for getting the visibility of the specified cook summary box.
- L100 _private prototype_ `FText HandleProjectTextBlockText() const;` — Callback for getting the text in the 'Game' text block.
- L103 _private prototype_ `FText HandleSelectedDeviceGroupTextBlockText() const;` — Callback for getting the name of the selected device group.
- L106 _private prototype_ `FText HandleSelectedProfileTextBlockText() const;` — Callback for getting the name of the selected profile.
- L109 _private prototype_ `EVisibility HandleValidationErrorIconVisibility(ELauncherProfileValidationErrors::Type Error) const;` — Callback for determining the visibility of a validation error icon.
- L114 _private member_ `TArray<TSharedPtr<ITargetDeviceProxy>> DeviceProxyList;` — The list of available device proxies.
- L117 _private member_ `TSharedPtr<SListView<TSharedPtr<ITargetDeviceProxy>> > DeviceProxyListView;` — The device proxy list view.
- L120 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Profile/SProjectLauncherProfileListRow.h` (Private)


#### class `SProjectLauncherProfileListRow`  
`class SProjectLauncherProfileListRow : public STableRow<ILauncherProfilePtr>`  
_L28-205_
- inherits: `STableRow<ILauncherProfilePtr>`
- desc: Implements a row widget for the launcher's device proxy list.
- L33 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherProfileListRow)`
- L60 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs - The construction arguments. @param InModel - The launcher model this list uses.
- L148 _public function_ `void TriggerNameEdit()` — Triggers a name edit for the profile this row displays.
- L158 _private function_ `FReply OnEditClicked()`
- L168 _private function_ `FReply OnRunClicked()`
- L178 _private function_ `ILauncherProfilePtr GetLaunchProfile() const`
- L184 _private function_ `const FSlateBrush* GetEditIcon() const` — Get the SlateIcon for Launch Button
- L192 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L195 _private member_ `ILauncherProfilePtr LaunchProfile;` — Holds a reference to the launch profile that is displayed in this row.
- L198 _private member_ `FOnProfileRun OnProfileEdit;` — Holds a delegate to be invoked when a profile is to be edited.
- L201 _private member_ `FOnProfileRun OnProfileRun;` — Holds a delegate to be invoked when a profile is run.
- L204 _private member_ `TSharedPtr<SProjectLauncherProfileNameDescEditor> ProfileNameDescEditor;` — Holds a pointer to the name / description editor.

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherSimpleDeviceListRow"`
- L105 _function_ `.IsEnabled_Lambda( [this]() { return LaunchProfile.IsValid() && LaunchProfile->SupportsLegacyProjectLauncher(); } ) ] + SHorizontalBox::Slot() .AutoWidth() .Padding(12, 5, 0, 5) [ SNew(SSeparator) .Orientation(Orient_Vertical) .Thickness(1.f) ] + SHorizontalBox::Slot() .AutoWidth() .VAlign(VAlign_Center) .HAlign(HAlign_Left) .Padding(24, 0, 20, 0) [ SNew(SProjectLauncherProfileLaunchButton, false) .LaunchProfile(this, &SProjectLauncherProfileListRow::GetLaunchProfile) .OnClicked(this, &SProjectLauncherProfileListRow::OnRunClicked) ] ] ] ];` (scope `SProjectLauncherProfileListRow::Construct`)

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Profile/SProjectLauncherProfileListView.h` (Private)


#### class `SProjectLauncherProfileListView`  
`class SProjectLauncherProfileListView : public SCompoundWidget`  
_L21-127_
- inherits: `SCompoundWidget`
- desc: Implements the deployment targets panel.
- L26 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherProfileListView)`
- L46 _public prototype_ `SProjectLauncherProfileListView();` — Constructor.
- L49 _public prototype_ `~SProjectLauncherProfileListView();` — Destructor.
- L59 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Construct the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L64 _protected prototype_ `void RefreshLaunchProfileList();` — Refreshe the list of launch profiles.
- L69 _private prototype_ `void CreateCommands();` — Builds the command list for the context menu on list items.
- L72 _private prototype_ `bool HandleProfileRowIsEnabled(ILauncherProfilePtr LaunchProfile) const;` — Callback for getting the enabled state of a profile list row.
- L75 _private prototype_ `FText HandleDeviceListRowToolTipText(ILauncherProfilePtr LaunchProfile) const;` — Callback for getting the tool tip text of a profile list row.
- L78 _private prototype_ `TSharedRef<ITableRow> HandleProfileListViewGenerateRow(ILauncherProfilePtr InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback for generating a row in the profile list view.
- L81 _private prototype_ `void HandleProfileManagerProfileAdded(const ILauncherProfileRef& AddedProfile);` — Callback for when a launch profile has been added to the profile manager.
- L84 _private prototype_ `void HandleProfileManagerProfileRemoved(const ILauncherProfileRef& RemovedProfile);` — Callback for when a launch profile has been removed to the profile manager.
- L87 _private prototype_ `TSharedPtr<SWidget> MakeProfileContextMenu();` — Callback for creating a context menu for the list.
- L90 _private prototype_ `bool HandleRenameProfileCommandCanExecute() const;` — Callback returns true if the rename command can be executed.
- L93 _private prototype_ `void HandleRenameProfileCommandExecute();` — Callback to execute the rename command from the context menu.
- L96 _private prototype_ `bool HandleDuplicateProfileCommandCanExecute() const;` — Callback returns true if the duplicate command can be executed.
- L99 _private prototype_ `void HandleDuplicateProfileCommandExecute();` — Callback to execute the duplicate command from the context menu.
- L102 _private prototype_ `bool HandleDeleteProfileCommandCanExecute() const;` — Callback returns true if the delete command can be executed.
- L105 _private prototype_ `void HandleDeleteProfileCommandExecute();` — Callback to execute the delete command from the context menu.
- L110 _private member_ `TSharedPtr<SListView<ILauncherProfilePtr> > LaunchProfileListView;` — The launch profile list view.
- L113 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Pointer to the data model.
- L116 _private member_ `FOnProfileRun OnProfileEdit;` — A delegate to be invoked when a profile is to be edited.
- L119 _private member_ `FOnProfileRun OnProfileRun;` — A delegate to be invoked when a profile is run.
- L122 _private member_ `FOnProfileRun OnProfileDelete;` — A delegate to be invoked when a profile is deleted.
- L125 _private member_ `TSharedRef<FUICommandList> CommandList;` — Commands handled by this widget.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Progress/SProjectLauncherMessageListRow.h` (Private)


#### struct `FProjectLauncherMessage`  
`struct FProjectLauncherMessage`  
_L22-31_
- L24 _public member_ `FText Message;`
- L25 _public member_ `ELogVerbosity::Type Verbosity;`
- L27 _public function_ `FProjectLauncherMessage(const FText& NewMessage, ELogVerbosity::Type InVerbosity) : Message(NewMessage) , Verbosity(InVerbosity)`

#### class `SProjectLauncherMessageListRow`  
`class SProjectLauncherMessageListRow : public SMultiColumnTableRow<TSharedPtr<FProjectLauncherMessage>>`  
_L37-112_
- inherits: `SMultiColumnTableRow<TSharedPtr<FProjectLauncherMessage>>`
- desc: Implements a row widget for the launcher's task list.
- L42 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherMessageListRow)`
- L54 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView )` — Constructs the widget. @param InArgs The construction arguments. @param InDeviceProxyManager The device proxy manager to use.
- L70 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L91 _private function_ `FSlateColor HandleGetTextColor( ) const` — Callback for getting the task's status text.
- L111 _private member_ `TSharedPtr<FProjectLauncherMessage> Message;` — Holds a pointer to the task that is displayed in this row.

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherMessageListRow"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Progress/SProjectLauncherProgress.h` (Private)


#### class `SProjectLauncherProgress`  
`class SProjectLauncherProgress : public SCompoundWidget`  
_L47-761_
- inherits: `SCompoundWidget`
- desc: Implements the launcher's progress page.
- L52 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherProgress)`
- L62 _public prototype_ `~SProjectLauncherProgress( ) = default;` — Destructor.
- L71 _public function_ `void Construct( const FArguments& InArgs )` — Constructs the widget. @param InArgs The Slate argument list.
- L333 _public function_ `void SetLauncherWorker( const ILauncherWorkerRef& Worker )` — Sets the launcher worker to track the progress for. @param Worker The launcher worker.
- L346 _public function_ `void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override`
- L371 _private function_ `void HandleOutputReceived(const FString& InMessage)`
- L393 _private function_ `TOptional<float> HandleProgressBarPercent( ) const` — Callback for getting the filled percentage of the progress bar.
- L419 _private function_ `FText HandleProgressTextBlockText( ) const` — Callback for getting the text of the progress text box.
- L465 _private function_ `TSharedRef<ITableRow> HandleTaskListViewGenerateRow( ILauncherTaskPtr InItem, const TSharedRef<STableViewBase>& OwnerTable ) const` — Callback for generating a row in the task list view.
- L473 _private function_ `TSharedRef<ITableRow> HandleMessageListViewGenerateRow( TSharedPtr<FProjectLauncherMessage> InItem, const TSharedRef<STableViewBase>& OwnerTable ) const` — Callback for generating a row in the task list view.
- L480 _private function_ `FReply HandleClearButtonClicked( )`
- L486 _private function_ `FReply HandleCopyButtonClicked( )`
- L492 _private function_ `FReply HandleSaveButtonClicked( )`
- L498 _private function_ `bool IsRerunButtonEnabled() const`
- L511 _private function_ `FReply HandleRerunButtonClicked()`
- L521 _private function_ `FText GetRerunButtonToolTip() const`
- L526 _private function_ `FText GetRerunButtonText() const`
- L531 _private function_ `bool IsDoneButtonEnabled() const`
- L543 _private function_ `FReply HandleDoneButtonClicked()`
- L563 _private function_ `FText GetDoneButtonToolTip() const`
- L580 _private function_ `FText GetDoneButtonText() const`
- L599 _private function_ `void ClearLog()`
- L606 _private function_ `void CopyLog()`
- L624 _private function_ `void SaveLog()`
- L686 _private function_ `FText GetSelectedProfileNameText() const`
- L703 _private member_ `TWeakPtr<ILauncherWorker> LauncherWorker;` — Holds the launcher worker.
- L706 _private member_ `TArray<TSharedPtr<FString>> OutputList;` — Holds the output log.
- L709 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> OutputListView;` — Holds the output list view.
- L712 _private member_ `TSharedPtr<SProgressBar> ProgressBar;` — Holds the progress bar.
- L715 _private member_ `TArray<ILauncherTaskPtr> TaskList;` — Holds the task list.
- L718 _private member_ `TArray< TSharedPtr<FProjectLauncherMessage>> MessageList;` — Holds the message list.
- L721 _private member_ `TArray< TSharedPtr<FProjectLauncherMessage>> FilterMessageList;` — Holds the filtered message list.
- L724 _private member_ `TArray< TSharedPtr<FProjectLauncherMessage>> PendingMessages;` — Holds the pending message list.
- L727 _private member_ `TSharedPtr<SScrollBox> HorizontalScrollBox;` — Horizontal scroll box wrapping the message list view.
- L730 _private member_ `TSharedPtr<SListView<TSharedPtr<FProjectLauncherMessage>>> MessageListView;` — Holds the message list view.
- L733 _private member_ `float MaxMessageListRowWidth;` — Caches the size of the longest row seen in the message list. Should be cleared when message list is cleared.
- L736 _private member_ `TSharedPtr<SListView<ILauncherTaskPtr>> TaskListView;` — Holds the task list view.
- L739 _private member_ `TSharedPtr<SVerticalBox> TaskStatusBox;` — Holds the box of task statuses.
- L742 _private member_ `FCriticalSection CriticalSection;` — Critical section for updating the messages
- L745 _private member_ `FString LastLogFileSaveDirectory;` — Holds the directory where the log file was last saved to.
- L748 _private member_ `TSharedPtr<SButton> CopyButton;` — Holds the copy log button.
- L751 _private member_ `TSharedPtr<SButton> ClearButton;` — Holds the clear button.
- L754 _private member_ `TSharedPtr<SButton> SaveButton;` — Holds the save button.
- L757 _private member_ `FOnClicked OnCloseClicked;` — Holds a delegate to be invoked when this panel is closed.
- L760 _private member_ `FOnClicked OnRerunClicked;` — Holds a delegate to be invoked when we want the launch profile rerun.

#### Free symbols / members of external scopes

- L41 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherProgress"`
- L199 _function_ `` (scope `SProjectLauncherProgress::Construct`)

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Progress/SProjectLauncherTaskListRow.h` (Private)


#### class `SProjectLauncherTaskListRow`  
`class SProjectLauncherTaskListRow : public SMultiColumnTableRow<ILauncherTaskPtr>`  
_L20-209_
- inherits: `SMultiColumnTableRow<ILauncherTaskPtr>`
- desc: Implements a row widget for the launcher's task list.
- L25 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherTaskListRow)`
- L38 _public function_ `void Construct( const FArguments& InArgs )` — Constructs the widget. @param InArgs The construction arguments. @param InDeviceProxyManager The device proxy manager to use.
- L53 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;` — Generates the widget for the specified column. @param ColumnName The name of the column to generate the widget for. @return The widget.
- L58 _private function_ `FText HandleDurationText( ) const` — Callback for getting the duration of the task.
- L73 _private function_ `FSlateColor HandleIconColorAndOpacity( ) const` — Callback for getting the color and opacity of the status icon.
- L99 _private function_ `const FSlateBrush* HandleIconImage( ) const` — Callback for getting the status icon image.
- L125 _private function_ `FText HandleStatusText( ) const` — Callback for getting the task's status text.
- L165 _private function_ `EVisibility HandleThrobberVisibility( ) const` — Callback for determining the throbber's visibility.
- L181 _private function_ `FText HandleWarningCounterText() const`
- L193 _private function_ `FText HandleErrorCounterText() const`
- L208 _private member_ `TWeakPtr<ILauncherTask> Task;` — Holds a pointer to the task that is displayed in this row.

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherTaskListRow"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Project/SProjectLauncherProjectPage.h` (Private)


#### class `SProjectLauncherProjectPage`  
`class SProjectLauncherProjectPage : public SCompoundWidget`  
_L13-36_
- inherits: `SCompoundWidget`
- desc: Implements the profile page for the session launcher wizard.
- L18 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherProjectPage)`
- L30 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel, bool InShowConfig = true );` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L35 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Project/SProjectLauncherProjectPicker.h` (Private)


#### class `SProjectLauncherProjectPicker`  
`class SProjectLauncherProjectPicker : public SCompoundWidget`  
_L18-91_
- inherits: `SCompoundWidget`
- desc: Implements the project loading area for the session launcher wizard.
- L23 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherProjectPicker)`
- L32 _public prototype_ `~SProjectLauncherProjectPicker( );` — Destructor.
- L42 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L51 _protected prototype_ `TSharedRef<SWidget> MakeProjectMenuWidget( );` — Creates the widget for the project menu. @return The widget.
- L58 _protected prototype_ `TSharedRef<SWidget> MakeProjectWidget( );` — Creates the widget for the project selection. @return The widget.
- L63 _private prototype_ `FText HandleProjectComboButtonText( ) const;` — Handles getting the text for the project combo button.
- L66 _private prototype_ `FText HandleProjectComboButtonToolTip( ) const;` — Handles getting the tooltip for the project combo button.
- L69 _private prototype_ `void HandleAnyProjectClicked(FString ProjectPath);` — Handles clicking the "any project" option.
- L72 _private prototype_ `void HandleProjectMenuEntryClicked( FString ProjectPath );` — Handles clicking a project menu entry.
- L75 _private prototype_ `EVisibility HandleValidationErrorIconVisibility( ELauncherProfileValidationErrors::Type Error ) const;` — Handles determining the visibility of a validation error icon.
- L78 _private prototype_ `void SetProjectPath(FString ProjectPath);` — Sets the project in the appropriate place (profile if provided otherwise on the model)
- L83 _private member_ `TAttribute<ILauncherProfilePtr> LaunchProfileAttr;` — Attribute for the launch profile this widget edits, if null it edits the project in the launcher model
- L86 _private member_ `TArray<TSharedPtr<FString>> ProjectList;` — Holds the list of available projects.
- L89 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/SLegacyProjectLauncher.h` (Private)


#### class `SLegacyProjectLauncher`  
`class SLegacyProjectLauncher : public SCompoundWidget`  
_L31-144_
- inherits: `SCompoundWidget`
- desc: Implements a Slate widget for the launcher user interface.
- L36 _public function_ `SLATE_BEGIN_ARGS(SLegacyProjectLauncher)`
- L46 _public prototype_ `SLegacyProjectLauncher();` — Constructor.
- L49 _public prototype_ `~SLegacyProjectLauncher();` — Destructor.
- L61 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed. @param InModel The view model to use.
- L71 _protected prototype_ `static void FillWindowMenu(FMenuBuilder& MenuBuilder, TSharedRef<FWorkspaceItem> RootMenuGroup);` — Fills the Window menu with menu items. @param MenuBuilder The multi-box builder that should be filled with content for this pull-down menu. @param RootMenuGroup The root menu group.
- L76 _private prototype_ `void OnAdvancedChanged(const ECheckBoxState NewCheckedState);` — Callback for toggling the advanced mode.
- L79 _private prototype_ `ECheckBoxState OnIsAdvanced() const;` — Callback to determine if we are in advanced mode.
- L82 _private prototype_ `const FSlateBrush* GetAdvancedToggleBrush() const;` — Get advanced toggle button brush.
- L85 _private prototype_ `bool GetIsAdvanced() const;` — Callback for whether advanced options should be shown.
- L88 _private prototype_ `void OnProfileEdit(const ILauncherProfileRef& Profile);` — Callback for editing a profile.
- L91 _private prototype_ `void OnProfileRun(const ILauncherProfileRef& Profile);` — Callback for running a profile.
- L94 _private prototype_ `void OnProfileDelete(const ILauncherProfileRef& Profile);` — Callback for deleting a profile.
- L97 _private prototype_ `void OnAddCustomLaunchProfileClicked();` — Callback for clicking the Add New Launch Profile.
- L100 _private prototype_ `TSharedRef<SWidget> MakeProfileWizardsMenu();` — Callback for filling profile wizard menu.
- L103 _private prototype_ `void ExecProfileWizard(ILauncherProfileWizardPtr InWizard);` — Execute specified profile wizard.
- L106 _private prototype_ `FReply OnProfileSettingsClose();` — Callback for when the settings panel is closed.
- L109 _private prototype_ `FReply OnProgressClose();` — Callback for when the progress panel is closed.
- L112 _private prototype_ `FReply OnRerunClicked();` — Callback for when the progress panel requests the profile to be re run.
- L117 _private member_ `ILauncherWorkerPtr LauncherWorker;` — The current launcher worker, if any.
- L120 _private member_ `ILauncherProfilePtr LauncherProfile;` — The Launcher profile the launcherWorker is running.
- L123 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the view model.
- L126 _private member_ `TSharedPtr<SProjectLauncherSettings> ProfileSettingsPanel;` — The profile settings panel.
- L129 _private member_ `TSharedPtr<SProjectLauncherProgress> ProgressPanel;` — The progress panel.
- L132 _private member_ `TSharedPtr<SWidgetSwitcher> WidgetSwitcher;` — The widget switcher.
- L137 _private member_ `TSharedPtr<SProjectLauncherSimpleDeviceListView> LaunchList;`
- L140 _private member_ `TSharedPtr<SBorder> ProfileList;` — Contains the profile list widgets.
- L143 _private member_ `bool bAdvanced;` — Whether we are showing advanced options.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Settings/SProjectLauncherSettings.h` (Private)


#### enum `ELauncherWizardPages::Type`  
`enum Type`  
_L25-44_
- desc: Enumerates the session launcher wizard pages.
- L28 _public enumerator_ `BuildPage` — The 'Build' page.
- L31 _public enumerator_ `CookPage` — The 'Cook' page.
- L34 _public enumerator_ `PackagePage` — The 'Package' page.
- L37 _public enumerator_ `DeployPage` — The 'Deploy' page.
- L40 _public enumerator_ `LaunchPage` — The 'Launch' page.
- L43 _public enumerator_ `PreviewPage` — The 'Preview' page.

#### class `SProjectLauncherSettings`  
`class SProjectLauncherSettings : public SCompoundWidget`  
_L51-141_
- inherits: `SCompoundWidget`
- desc: Implements the launcher settings widget.
- L56 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherSettings)`
- L64 _public prototype_ `SProjectLauncherSettings();` — Default constructor.
- L67 _public prototype_ `~SProjectLauncherSettings();` — Destructor.
- L77 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L79 _public prototype_ `void EnterEditMode();`
- L84 _private prototype_ `void CreateCommands();` — Create the menu command list.
- L87 _private prototype_ `TSharedRef<SWidget> MakeToolbar(const TSharedRef<FUICommandList>& InCommandList);` — Make a Toolbar using the command list.
- L92 _private prototype_ `TSharedPtr<ILauncherProfile> GetLaunchProfile()const;` — Callback for getting the launch profile we are currently editing.
- L95 _private prototype_ `EVisibility HandleSelectProfileTextBlockVisibility() const;` — Callback for getting the visibility of the 'Select Profile' text block.
- L98 _private prototype_ `EVisibility HandleSettingsScrollBoxVisibility() const;` — Callback for getting the visibility of the settings scroll box.
- L101 _private prototype_ `FText OnGetNameText() const;` — Callback to get the name of the launch profile.
- L104 _private prototype_ `void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);` — Callback to set the name of the launch profile.
- L107 _private prototype_ `FText OnGetDescriptionText() const;` — Callback to get the description of the launch profile.
- L110 _private prototype_ `void OnDescriptionTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);` — Callback to set the description of the launch profile.
- L113 _private prototype_ `void HandleCloseActionExecute();` — Callbacks for executing the 'Close' action.
- L114 _private prototype_ `bool HandleCloseActionIsChecked() const;`
- L115 _private prototype_ `bool HandleCloseActionCanExecute() const;`
- L118 _private prototype_ `void HandleDeleteActionExecute();` — Callbacks for executing the 'Delete' action.
- L119 _private prototype_ `bool HandleDeleteActionIsChecked() const;`
- L120 _private prototype_ `bool HandleDeleteActionCanExecute() const;`
- L125 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L128 _private member_ `TSharedRef<FUICommandList> CommandList;` — Holds the list of UI commands for the profile settings.
- L131 _private member_ `FOnClicked OnCloseClicked;` — Holds a delegate to be invoked when this panel is closed.
- L134 _private member_ `FOnClicked OnRerunClicked;` — Holds a delegate to be invoked when a rerun of the profile is requested.
- L137 _private member_ `FOnProfileRun OnDeleteClicked;` — Holds a delegate to be invoked when this profile is deleted.
- L140 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameEditBox;` — Hold a pointer to the launch profile name edit box.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace ELauncherWizardPages`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/ProjectLauncherDelegates.h` (Private)


#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProfileRun, const ILauncherProfileRef&)` — Delegate type for SLegacyProjectLauncher Profile running. The first parameter is the SLegacyProjectLauncher Profile that you want to run.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherBuildConfigurationSelector.h` (Private)


#### class `SProjectLauncherBuildConfigurationSelector`  
`class SProjectLauncherBuildConfigurationSelector : public SCompoundWidget`  
_L32-116_
- inherits: `SCompoundWidget`
- desc: Implements a build configuration selector widget.
- L37 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherBuildConfigurationSelector)`
- L51 _public function_ `void Construct(const FArguments& InArgs)` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L107 _private function_ `void HandleMenuEntryClicked( EBuildConfiguration Configuration )` — Callback for clicking a menu entry.
- L115 _private member_ `FOnSessionSProjectLauncherBuildConfigurationSelected OnConfigurationSelected;` — Holds a delegate to be invoked when a build configuration has been selected.

#### struct `SProjectLauncherBuildConfigurationSelector::Construct::FConfigInfo`  
`struct FConfigInfo`  
_L55-59_
- L57 _public member_ `FText ToolTip;`
- L58 _public member_ `EBuildConfiguration Configuration;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherBuildConfigurationSelector"`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSessionSProjectLauncherBuildConfigurationSelected, EBuildConfiguration) class SProjectLauncherBuildConfigurationSelector : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SProjectLauncherBuildConfigurationSelector) { } SLATE_EVENT(FOnSessionSProjectLauncherBuildConfigurationSelected, OnConfigurationSelected) SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs) { OnConfigurationSelected = InArgs._OnConfigurationSelected; struct FConfigInfo { FText ToolTip; EBuildConfiguration Configuration; }; const FConfigInfo Configurations[] = { {LOCTEXT("DebugActionHint", "Debug configuration."), EBuildConfiguration::Debug}, {LOCTEXT("DebugGameActionHint", "DebugGame configuration."), EBuildConfiguration::DebugGame}, {LOCTEXT("DevelopmentActionHint", "Development configuration."), EBuildConfiguration::Development},` — Delegate type for build configuration selections. The first parameter is the selected build configuration.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherBuildTargetSelector.h` (Private)


#### class `SProjectLauncherBuildTargetSelector`  
`class SProjectLauncherBuildTargetSelector : public SCompoundWidget`  
_L18-72_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherBuildTargetSelector) : _UseProfile(false)`
- L34 _public prototype_ `~SProjectLauncherBuildTargetSelector();` — Destructor.
- L44 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L49 _private prototype_ `void RefreshBuildTargetList();`
- L51 _private prototype_ `EVisibility IsBuildTargetVisible() const;`
- L52 _private prototype_ `FText HandleBuildTargetComboButtonText() const;`
- L53 _private prototype_ `FText GetBuildTargetText( FString BuildTarget ) const;`
- L54 _private prototype_ `void HandleBuildTargetSelectionChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);`
- L55 _private prototype_ `TSharedRef<SWidget> HandleBuildTargetGenerateWidget(TSharedPtr<FString> Item);`
- L56 _private prototype_ `void HandleProfileManagerProfileSelected(const ILauncherProfilePtr& SelectedProfile, const ILauncherProfilePtr& PreviousProfile);`
- L57 _private prototype_ `void HandleProfileProjectChanged();`
- L58 _private prototype_ `void HandleProfileBuildTargetOptionsChanged();`
- L60 _private prototype_ `void SetBuildTarget(const FString& BuildTarget);`
- L62 _private prototype_ `ILauncherProfilePtr GetProfile() const;`
- L67 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> BuildTargetCombo;`
- L68 _private member_ `TArray<TSharedPtr<FString>> BuildTargetList;`
- L69 _private member_ `bool bUseProfile;`
- L70 _private member_ `TSharedPtr<FProjectLauncherModel> Model;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLauncherProfileChanged, ILauncherProfilePtr);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLauncherProfileChanged, ILauncherProfilePtr);`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherCookModeSelector.h` (Private)


#### class `SProjectLauncherCookModeSelector`  
`class SProjectLauncherCookModeSelector : public SCompoundWidget`  
_L31-97_
- inherits: `SCompoundWidget`
- desc: Implements a build configuration selector widget.
- L36 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherCookModeSelector)`
- L49 _public function_ `void Construct( const FArguments& InArgs )` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L88 _private function_ `void HandleMenuEntryClicked(ELauncherProfileCookModes::Type CookMode)` — Callback for clicking a menu entry.
- L96 _private member_ `FOnSProjectLauncherCookModeSelected OnCookModeSelected;` — Holds a delegate to be invoked when a build configuration has been selected.

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherCookModeSelector"`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSProjectLauncherCookModeSelected, ELauncherProfileCookModes::Type) class SProjectLauncherCookModeSelector : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SProjectLauncherCookModeSelector) { } SLATE_EVENT(FOnSProjectLauncherCookModeSelected, OnCookModeSelected) SLATE_ATTRIBUTE(FText, Text) SLATE_END_ARGS() public: void Construct( const FArguments& InArgs ) { OnCookModeSelected = InArgs._OnCookModeSelected;` — Delegate type for build configuration selections. The first parameter is the selected build configuration.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherFormLabel.h` (Private)


#### class `SProjectLauncherFormLabel`  
`class SProjectLauncherFormLabel : public SCompoundWidget`  
_L17-71_
- inherits: `SCompoundWidget`
- desc: Implements a widget for form input field labels with optional validation errors.
- L22 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherFormLabel) : _ErrorToolTipText() , _ErrorVisibility(EVisibility::Hidden) , _LabelText()`
- L46 _public function_ `void Construct( const FArguments& InArgs )` — Constructs the widget. @param InArgs The Slate argument list.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherInstanceTypeSelector.h` (Private)


#### class `SProjectLauncherInstanceTypeSelector`  
`class SProjectLauncherInstanceTypeSelector : public SCompoundWidget`  
_L33-101_
- inherits: `SCompoundWidget`
- desc: Implements a build configuration selector widget.
- L38 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherInstanceTypeSelector)`
- L51 _public function_ `void Construct( const FArguments& InArgs )` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L92 _private function_ `void HandleMenuEntryClicked(ELauncherProfileRoleInstanceTypes::Type InstanceType)` — Callback for clicking a menu entry.
- L100 _private member_ `FOnSProjectLauncherInstanceTypeSelected OnInstanceTypeSelected;` — Holds a delegate to be invoked when a build configuration has been selected.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherInstanceTypeSelector"`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSProjectLauncherInstanceTypeSelected, ELauncherProfileRoleInstanceTypes::Type) class SProjectLauncherInstanceTypeSelector : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SProjectLauncherInstanceTypeSelector) { } SLATE_EVENT(FOnSProjectLauncherInstanceTypeSelected, OnInstanceTypeSelected) SLATE_ATTRIBUTE(FText, Text) SLATE_END_ARGS() public: void Construct( const FArguments& InArgs ) { OnInstanceTypeSelected = InArgs._OnInstanceTypeSelected;` — Delegate type for build configuration selections. The first parameter is the selected build configuration.

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherProfileLaunchButton.h` (Private)


#### class `SProjectLauncherProfileLaunchButton`  
`class SProjectLauncherProfileLaunchButton : public SCompoundWidget`  
_L26-140_
- inherits: `SCompoundWidget`
- desc: Implements a build configuration selector widget.
- L31 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherProfileLaunchButton)`
- L44 _public function_ `void Construct(const FArguments& InArgs, bool InShowText)` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L79 _public function_ `virtual TSharedPtr<IToolTip> GetToolTip() override`
- L104 _private function_ `bool HasError() const` — @returns true if there is an error in the launch profile, no launch profile is considered an error
- L114 _private function_ `bool IsLegacyProfile() const`
- L121 _private function_ `bool ButtonEnabled() const` — Callback to see if the launch button should be enabled
- L127 _private function_ `const FSlateBrush* GetLaunchIcon() const` — Get the SlateIcon for Launch Button
- L135 _private member_ `TAttribute<ILauncherProfilePtr> LaunchProfileAttr;` — Attribute for the launch profile this widget launches.
- L138 _private member_ `TSharedPtr<SToolTip> ErrorToolTipWidget;` — Holds a pointer to our custom tooltip.

#### Free symbols / members of external scopes

- L20 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherProfileLaunchButton"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherProfileNameDescEditor.h` (Private)


#### class `SProjectLauncherProfileNameDescEditor`  
`class SProjectLauncherProfileNameDescEditor : public SCompoundWidget`  
_L16-119_
- inherits: `SCompoundWidget`
- desc: Implements a build configuration selector widget.
- L21 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherProfileNameDescEditor)`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FProjectLauncherModel>& InModel, bool InShowAddDescriptionText);` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L39 _public prototype_ `void TriggerNameEdit();` — Triggers a name edit for the profile.
- L44 _private function_ `const FSlateBrush* HandleProfileImage() const` — Callback for getting the icon image of the profile.
- L52 _private function_ `FText OnGetNameText() const` — Callback to get the name of the launch profile.
- L63 _private function_ `void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit)` — Callback to set the name of the launch profile.
- L73 _private function_ `FText OnGetDescriptionText() const` — Callback to get the description of the launch profile.
- L88 _private function_ `void OnDescriptionTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit)` — Callback to set the description of the launch profile.
- L107 _private member_ `TSharedPtr<FProjectLauncherModel> Model;` — Holds a pointer to the data model.
- L110 _private member_ `TAttribute<ILauncherProfilePtr> LaunchProfileAttr;` — Attribute for the launch profile this widget edits.
- L113 _private member_ `FText EnterTextDescription;` — Cache the no description enter suggestion text
- L116 _private member_ `bool bShowAddDescriptionText;` — Whether we show an add description blurb when the profile has no description.
- L118 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameEditableTextBlock;`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherValidation.h` (Private)


#### class `SProjectLauncherValidation`  
`class SProjectLauncherValidation : public SCompoundWidget`  
_L24-301_
- inherits: `SCompoundWidget`
- desc: Implements the launcher's profile validation panel.
- L29 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherValidation)`
- L42 _public function_ `void Construct( const FArguments& InArgs)` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L219 _protected function_ `TSharedRef<SWidget> MakeValidationMessage( const TCHAR* IconName, ELauncherProfileValidationErrors::Type Message )` — Creates a widget for a validation message. @param IconName The name of the message icon. @param MessageText The message text. @param MessageType The message type.
- L247 _protected function_ `TSharedRef<SWidget> MakeCallbackMessage( const TCHAR* IconName,ELauncherProfileValidationErrors::Type Message )` — Creates a widget for a validation message. @param IconName The name of the message icon. @param MessageType The message type.
- L272 _private function_ `EVisibility HandleValidationMessageVisibility( ELauncherProfileValidationErrors::Type Error ) const` — Callback for getting the visibility state of a validation message.
- L282 _private function_ `FText HandleValidationMessage( ELauncherProfileValidationErrors::Type Error ) const`
- L300 _private member_ `TAttribute<TSharedPtr<ILauncherProfile>> LaunchProfileAttr;` — Attribute for the launch profile this widget shows validation for.

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherValidation"`

### `Source/Developer/LegacyProjectLauncher/Private/Widgets/Shared/SProjectLauncherVariantSelector.h` (Private)


#### class `SProjectLauncherVariantSelector`  
`class SProjectLauncherVariantSelector : public SCompoundWidget`  
_L31-102_
- inherits: `SCompoundWidget`
- desc: Implements a build configuration selector widget.
- L36 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncherVariantSelector)`
- L49 _public function_ `void Construct(const FArguments& InArgs, TSharedPtr<ITargetDeviceProxy> DeviceProxy)` — Constructs the widget. @param InArgs The Slate argument list. @param InModel The data model.
- L93 _private function_ `void HandleMenuEntryClicked(FName Variant)` — Callback for clicking a menu entry.
- L101 _private member_ `FOnSProjectLauncherVariantSelected OnVariantSelected;` — Holds a delegate to be invoked when a build configuration has been selected.

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "SProjectLauncherVariantSelector"`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSProjectLauncherVariantSelected, FName) class SProjectLauncherVariantSelector : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SProjectLauncherVariantSelector) { } SLATE_EVENT(FOnSProjectLauncherVariantSelected, OnVariantSelected) SLATE_ATTRIBUTE(FText, Text) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs, TSharedPtr<ITargetDeviceProxy> DeviceProxy) { OnVariantSelected = InArgs._OnVariantSelected;` — Delegate type for build configuration selections. The first parameter is the selected build configuration.

### `Source/Developer/LegacyProjectLauncher/Public/IProjectLauncherModule.h` (Public)


#### class `ILegacyProjectLauncherModule`  
`class ILegacyProjectLauncherModule : public IModuleInterface`  
_L11-18_
- inherits: `IModuleInterface`
- desc: Interface for launcher UI modules.
- L17 _public prototype_ `virtual ~ILegacyProjectLauncherModule() = default;` — Virtual destructor.
