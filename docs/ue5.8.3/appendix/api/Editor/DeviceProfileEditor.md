# Editor / DeviceProfileEditor

- module root: `Source/Editor/DeviceProfileEditor`
- headers: 9; symbols: 106
- symbol kinds: class=8, delegate=5, function=7, macro=5, member=34, prototype=47
- DynamicallyLoadedModuleNames: MainFrame
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, PropertyEditor, SharedSettingsWidgets, Slate, SlateCore, SourceControl, TargetPlatform, WorkspaceMenuStructure
- PublicIncludePathModuleNames: UnrealEd

### `Source/Editor/DeviceProfileEditor/Private/DetailsPanel/SDeviceProfileDetailsPanel.h` (Private)


#### class `SDeviceProfileDetailsPanel`  
`class SDeviceProfileDetailsPanel : public SCompoundWidget`  
_L22-58_
- inherits: `SCompoundWidget`
- desc: Slate widget to display details of a device profile
- L26 _public function_ `SLATE_BEGIN_ARGS( SDeviceProfileDetailsPanel )`
- L27 _public prototype_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L41 _public prototype_ `void UpdateUIForProfile( const TWeakObjectPtr< UDeviceProfile > InProfile );` — Update the UI of the details panel with the provided device profile @param In Profile The profile which the details panel should reflect
- L46 _private prototype_ `void RefreshUI();` — Refresh the UI of the details panel.
- L51 _private member_ `TWeakObjectPtr< UDeviceProfile > ViewingProfile;` — The profile this panel is showing details for.
- L54 _private member_ `TSharedPtr< SVerticalBox > DetailsViewBox;` — The widget which hosts the details content if a profile is provided.
- L57 _private member_ `TSharedPtr<IDetailsView> SettingsView;` — Holds the details view.

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "DeviceProfileDetailsPanel"`

### `Source/Editor/DeviceProfileEditor/Private/DeviceProfileConsoleVariableColumn.h` (Private)


#### class `FDeviceProfileConsoleVariableColumn`  
`class FDeviceProfileConsoleVariableColumn : public IPropertyTableCustomColumn`  
_L26-55_
- inherits: `IPropertyTableCustomColumn`
- desc: A property table custom column used to bring the user to an editor which will manage the list of Console Variables associated with the device profile
- L29 _public prototype_ `FDeviceProfileConsoleVariableColumn();`
- L35 _public prototype_ `virtual bool Supports( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities ) const override;`
- L36 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L37 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter( const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L46 _public function_ `FOnEditDeviceProfileCVarsRequestDelegate& OnEditCVarsRequest()` — Delegate used to notify listeners that an edit request was triggered from the property table. @return The delegate.
- L54 _private member_ `FOnEditDeviceProfileCVarsRequestDelegate OnEditCVarsRequestDelegate;` — Delegate triggered when user opts to edit CVars.

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEditDeviceProfileCVarsRequestDelegate, const TWeakObjectPtr<UDeviceProfile>&);` — Delegate triggered when user opts to edit CVars
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnEditDeviceProfileCVarsRequestDelegate, const TWeakObjectPtr<UDeviceProfile>&);` — Delegate triggered when user opts to edit CVars

### `Source/Editor/DeviceProfileEditor/Private/DeviceProfileTextureLODSettingsColumn.h` (Private)


#### class `FDeviceProfileTextureLODSettingsColumn`  
`class FDeviceProfileTextureLODSettingsColumn : public IPropertyTableCustomColumn`  
_L26-55_
- inherits: `IPropertyTableCustomColumn`
- desc: A property table custom column used to bring the user to an editor which will manage the Texture LOD Settings associated with the device profile
- L29 _public prototype_ `FDeviceProfileTextureLODSettingsColumn();`
- L35 _public prototype_ `virtual bool Supports( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities ) const override;`
- L36 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L37 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter( const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L46 _public function_ `FOnEditDeviceProfileTextureLODSettingsRequestDelegate& OnEditTextureLODSettingsRequest()` — Delegate used to notify listeners that an edit request was triggered from the property table. @return The delegate.
- L54 _private member_ `FOnEditDeviceProfileTextureLODSettingsRequestDelegate OnEditTextureLODSettingsRequestDelegate;` — Delegate triggered when user opts to edit TextureLODSettings.

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEditDeviceProfileTextureLODSettingsRequestDelegate, const TWeakObjectPtr<UDeviceProfile>&);` — Delegate triggered when user opts to edit TextureLODSettings
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnEditDeviceProfileTextureLODSettingsRequestDelegate, const TWeakObjectPtr<UDeviceProfile>&);` — Delegate triggered when user opts to edit TextureLODSettings

### `Source/Editor/DeviceProfileEditor/Private/SDeviceProfileCreateProfilePanel.h` (Private)


#### class `SDeviceProfileCreateProfilePanel`  
`class SDeviceProfileCreateProfilePanel : public SCompoundWidget`  
_L39-162_
- inherits: `SCompoundWidget`
- desc: Slate widget to allow users to create a new device profile
- L43 _public function_ `SLATE_BEGIN_ARGS( SDeviceProfileCreateProfilePanel )`
- L44 _public prototype_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TWeakObjectPtr< UDeviceProfileManager > InDeviceProfileManager );`
- L57 _public prototype_ `bool IsCreateProfileButtonEnabled() const;` — Is the create profile button enabled. @return True if enabled, false otherwise
- L64 _public prototype_ `FReply HandleCreateDeviceProfileButtonClicked();` — Handle create device profile button clicked. @return whether the click was handled.
- L73 _public prototype_ `bool IsBaseProfileComboBoxEnabled() const;` — Is the select a base profile selection available @return true if enabled, false otherwise.
- L81 _public prototype_ `void HandleBaseProfileSelectionChanged( UDeviceProfile* NewSelection, ESelectInfo::Type SelectInfo );` — Handle base selection changed. @param NewSelection The newly selected device profile to use as a parent. @param SelectionInfo The selection type.
- L88 _public prototype_ `FText SetBaseProfileComboBoxContent() const;` — Set the base combo box content. @return The device profile parent name.
- L96 _public prototype_ `TSharedRef<SWidget> HandleBaseComboBoxGenerateWidget( UDeviceProfile* InItem );` — Handle base combo box generate widget. @param InItem The device profile. @return A text box holding the device profile name.
- L106 _public prototype_ `void HandleProfileTypeChanged( TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo );` — Handle profile type changed. @param NewSelection The newly selected device profile type. @param SelectionInfoThe selection type.
- L113 _public prototype_ `FText SetProfileTypeComboBoxContent() const;` — Set the profile type combo box content. @return The name of the class the created profile will be.
- L121 _public prototype_ `TSharedRef<SWidget> HandleProfileTypeComboBoxGenarateWidget( TSharedPtr<FString> InItem );` — Handle profile type combo box generate widget. @param The type of this in string format. @return A text box holding the device profile name.
- L126 _private prototype_ `void ResetComponentsState();` — Reset the components state.
- L131 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> DeviceProfileTypesComboBox;` — Holds the Device Profile Class types combo box.
- L134 _private member_ `TArray<TSharedPtr<FString>> DeviceProfileTypes;` — The collection of available types you can create a profile for.
- L137 _private member_ `TSharedPtr<SComboBox<UDeviceProfile*>> ParentObjectComboBox;` — Holds the Device Profile Class types combo box.
- L140 _private member_ `TArray<UDeviceProfile*> AvailableBaseObjects;` — The collection of device profiles available for you to copy properties from that matches the profile type.
- L143 _private member_ `TSharedPtr< SComboBox< UDeviceProfile* > > DeviceProfileBaseComboBox;` — Holds the device profile combo box.
- L146 _private member_ `TSharedPtr< SCheckBox > DeviceProfileBaseCheckBox;` — Holds the device profile check box.
- L149 _private member_ `TWeakObjectPtr< UDeviceProfileManager > DeviceProfileManager;` — Holds the device profile manager.
- L152 _private member_ `TSharedPtr< SEditableTextBox > DeviceProfileNameTextBox;` — Holds the device profile name text box.
- L155 _private member_ `TSharedPtr< SEditableTextBox > DeviceProfileParentNameTextBox;` — Holds the device profile name text box.
- L158 _private member_ `TWeakObjectPtr< UDeviceProfile > SelectedDeviceProfileParent;` — Holds the selected device profile parent.
- L161 _private member_ `TSharedPtr< FString > SelectedDeviceProfileType;` — Holds the selected device profile parent.

#### Free symbols / members of external scopes

- L30 _macro_ `#define LOCTEXT_NAMESPACE "DeviceProfileCreateProfilePanel"`

### `Source/Editor/DeviceProfileEditor/Private/SDeviceProfileEditor.h` (Private)


#### class `SDeviceProfileEditor`  
`class SDeviceProfileEditor : public SCompoundWidget`  
_L30-145_
- inherits: `SCompoundWidget`
- desc: Slate widget to allow users to edit Device Profiles
- L35 _public function_ `SLATE_BEGIN_ARGS( SDeviceProfileEditor )`
- L36 _public prototype_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L45 _public prototype_ `~SDeviceProfileEditor();` — Destructor
- L55 _public prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab( const FSpawnTabArgs& Args, FName TabIdentifier );` — Callback for spawning tabs. @param Args The arguments used for the tab that is spawned. @param TabIdentifier The ID of the tab we want to spawn.
- L64 _public prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnSingleProfileTab(const FSpawnTabArgs& Args, TWeakObjectPtr<UDeviceProfile> InDeviceProfile);` — Callback for spawning tabs. @param Args The arguments used for the tab that is spawned. @param InDeviceProfile The device profile the single editor is displaying information for.
- L73 _public prototype_ `void HandleDeviceProfilePinned( const TWeakObjectPtr< UDeviceProfile >& DeviceProfile );` — Handle a device being pinned to the grid. @param DeviceProfile The selected profile.
- L81 _public prototype_ `void HandleDeviceProfileUnpinned( const TWeakObjectPtr< UDeviceProfile >& DeviceProfile );` — Handle the device being unpinned from the grid. @param DeviceProfile The deselected profile.
- L89 _public prototype_ `void HandleDeviceProfileViewAlone(const TWeakObjectPtr< UDeviceProfile >& DeviceProfile);` — Handle the device being unpinned from the grid. @param DeviceProfile The profile that is to be viewed alone.
- L97 _public prototype_ `EVisibility GetEmptyDeviceProfileGridNotificationVisibility() const;` — Get whether the notification which indicates that no profiles currently being viewed in the grid, should be visible. @return Whether the Notification is visible or not.
- L105 _public prototype_ `TSharedRef< SWidget > SetupPropertyEditor();` — Setup the device profile property grid. @return The widget containing the property grid.
- L114 _private prototype_ `TSharedPtr< SWidget > CreateMainDeviceProfilePanel();` — Create the device profile panel which hosts the functionality to edit device profiles in the editor. @return The slate widget which hosts the device profile manipulator.
- L118 _private prototype_ `void RebuildPropertyTable();` — Rebuild the device profile property table.
- L123 _private member_ `TWeakObjectPtr<UDeviceProfileManager> DeviceProfileManager;` — Hold a reference to the device profile manager.
- L126 _private member_ `TArray<UObject*> DeviceProfiles;` — The collection of device profile ptrs for the selection process.
- L129 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L132 _private member_ `TSharedPtr<SDeviceProfileSelectionPanel> DeviceProfileSelectionPanel;` — The widget which allows the user to select profiles.
- L135 _private member_ `TSharedPtr<IPropertyTable> PropertyTable;` — Holds the property table.
- L138 _private member_ `TArray<FName> RegisteredTabIds;` — The list of Single Profile Editor ID's which have already been spawned/registered.
- L141 _private member_ `TSharedPtr<FWorkspaceItem> DeviceManagerMenuGroup;` — Access to the "Window" menu to add our spawned tabs of single profile editors.
- L144 _private member_ `TSharedPtr<FTabManager::FStack> EditorTabStack;` — Holds the tab stack where single profiles and the device profile editor will be spawned to.

#### Free symbols / members of external scopes

- L20 _macro_ `#define LOCTEXT_NAMESPACE "DeviceProfileEditor"`

### `Source/Editor/DeviceProfileEditor/Private/SDeviceProfileEditorSingleProfileView.h` (Private)


#### class `SDeviceProfileEditorSingleProfileView`  
`class SDeviceProfileEditorSingleProfileView : public SCompoundWidget`  
_L21-43_
- inherits: `SCompoundWidget`
- desc: Slate widget to allow users to select device profiles
- L26 _public function_ `SLATE_BEGIN_ARGS(SDeviceProfileEditorSingleProfileView)`
- L27 _public prototype_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TWeakObjectPtr< UDeviceProfile > InDeviceProfile );`
- L34 _public prototype_ `~SDeviceProfileEditorSingleProfileView()= default;` — Destructor
- L39 _private member_ `TWeakObjectPtr< UDeviceProfile > EditingProfile;` — The profile selected from the current list.
- L42 _private member_ `TSharedPtr<IDetailsView> SettingsView;` — Holds the details view.

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "DeviceProfileEditorSingleProfileView"`

### `Source/Editor/DeviceProfileEditor/Private/SDeviceProfileSelectionPanel.h` (Private)


#### class `SDeviceProfileSelectionPanel`  
`class SDeviceProfileSelectionPanel : public SCompoundWidget`  
_L36-99_
- inherits: `SCompoundWidget`
- desc: Slate widget to allow users to select device profiles
- L41 _public function_ `SLATE_BEGIN_ARGS( SDeviceProfileSelectionPanel ) : _OnDeviceProfilePinned() , _OnDeviceProfileUnpinned() , _OnDeviceProfileViewAlone()`
- L46 _public prototype_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_EVENT( FOnDeviceProfilePinned, OnDeviceProfilePinned ) SLATE_EVENT( FOnDeviceProfileUnpinned, OnDeviceProfileUnpinned ) SLATE_EVENT( FOnDeviceProfileViewAlone, OnDeviceProfileViewAlone ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TWeakObjectPtr< UDeviceProfileManager > InDeviceProfileManager );`
- L58 _public prototype_ `~SDeviceProfileSelectionPanel();` — Destructor.
- L67 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForDeviceProfile( TWeakObjectPtr<UDeviceProfile> InDeviceProfile, const TSharedRef< STableViewBase >& OwnerTable );` — Handle generating the device profile widget. @param InDeviceProfile The selected device profile. @param OwnerTable The Owner table. @return The generated widget.
- L72 _protected prototype_ `void RegenerateProfileList();` — Regenerate the list view widget when the device profiles are recreated
- L77 _private member_ `TWeakObjectPtr< UDeviceProfileManager > DeviceProfileManager;` — Holds the device profile manager.
- L80 _private member_ `TArray< TWeakObjectPtr<UDeviceProfile> > DeviceProfiles;` — The collection of device profiles for the selection process.
- L83 _private member_ `TSharedPtr< SVerticalBox > ListWidget;` — Hold the widget that contains the list view of device profiles.
- L86 _private member_ `FOnDeviceProfilePinned OnDeviceProfilePinned;` — Delegate for handling a profile being pinned to the grid.
- L89 _private member_ `FOnDeviceProfileUnpinned OnDeviceProfileUnpinned;` — Delegate for handling a profile being unpinned from the grid.
- L92 _private member_ `FOnDeviceProfileViewAlone OnDeviceProfileViewAlone;` — Delegate for handling a request to view the profile in it's own editor.
- L95 _private member_ `TWeakObjectPtr< UDeviceProfile > SelectedProfile;` — The profile selected from the current list.
- L98 _private member_ `FDelegateHandle RegenerateProfileListDelegateHandle;` — Handle to the registered RegenerateProfileList delegate

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "DeviceProfileEditorSelectionPanel"`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeviceProfilePinned, const TWeakObjectPtr< UDeviceProfile >&);` — Delegate that is executed when a device profile is pinned
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDeviceProfilePinned, const TWeakObjectPtr< UDeviceProfile >&);` — Delegate that is executed when a device profile is pinned
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeviceProfileUnpinned, const TWeakObjectPtr< UDeviceProfile >&);` — Delegate that is executed when a device profile is unpinned
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDeviceProfileUnpinned, const TWeakObjectPtr< UDeviceProfile >&);` — Delegate that is executed when a device profile is unpinned
- L30 _delegate_ `DECLARE_DELEGATE_OneParam( FOnDeviceProfileViewAlone, const TWeakObjectPtr< UDeviceProfile >& );` — Delegate that is executed when a device profile has been selected to view alone.
- L30 _prototype_ `DECLARE_DELEGATE_OneParam( FOnDeviceProfileViewAlone, const TWeakObjectPtr< UDeviceProfile >& );` — Delegate that is executed when a device profile has been selected to view alone.

### `Source/Editor/DeviceProfileEditor/Public/DeviceProfileEditor.h` (Public)
_(no declarations extracted)_

### `Source/Editor/DeviceProfileEditor/Public/DeviceProfileEditorModule.h` (Public)


#### class `FDeviceProfileEditorModule`  
`class FDeviceProfileEditorModule : public IModuleInterface`  
_L15-31_
- inherits: `IModuleInterface`
- desc: Device Profile Editor module
- L21 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `static TSharedRef<SDockTab> SpawnDeviceProfileEditorTab( const FSpawnTabArgs& SpawnTabArgs );` — Create the slate UI for the Device Profile Editor
