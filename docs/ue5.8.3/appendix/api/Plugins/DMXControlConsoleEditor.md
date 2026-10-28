# Plugins / DMXControlConsoleEditor

- module root: `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor`
- headers: 70; symbols: 1585
- symbol kinds: class=71, delegate=11, enum=7, enumerator=23, function=160, member=336, namespace=143, prototype=826, struct=7, typedef=1
- PrivateDependencyModuleNames: AppFramework, AssetDefinition, AssetRegistry, ContentBrowser, CoreUObject, DMXControlConsole, DMXEditor, DMXProtocol, DMXProtocolEditor, DMXRuntime, Engine, InputCore, LevelEditor, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/AssetDefinitions/AssetDefinition_DMXControlConsole.h` (Private)


#### class `UAssetDefinition_DMXControlConsole`  
`class UAssetDefinition_DMXControlConsole : public UAssetDefinitionDefault`  
_L14-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L21 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L22 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L23 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L24 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L26 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L27 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Commands/DMXControlConsoleEditorCommands.h` (Private)


#### class `FDMXControlConsoleEditorCommands`  
`class FDMXControlConsoleEditorCommands : public TCommands<FDMXControlConsoleEditorCommands>`  
_L9-51_
- inherits: `TCommands<FDMXControlConsoleEditorCommands>`
- desc: Defines commands for the DMX Control Console.
- L14 _public prototype_ `FDMXControlConsoleEditorCommands();` — Constructor
- L17 _public prototype_ `virtual void RegisterCommands() override;` — Registers commands for DMX Control Console
- L19 _public member_ `TSharedPtr<FUICommandInfo> OpenControlConsole;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> PlayDMX;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> PauseDMX;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ResumeDMX;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> StopDMX;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayPauseDMX;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayStopDMX;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> EditorStopSendsDefaultValues;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> EditorStopSendsZeroValues;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> EditorStopKeepsLastValues;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> RemoveElements;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> SelectAll;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ClearAll;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ResetToDefault;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ResetToZero;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> Reload;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> Enable;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> EnableAll;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> Disable;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> DisableAll;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> AddPatchRight;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> AddPatchNextRow;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> AddPatchToSelection;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> GroupPatchRight;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> GroupPatchNextRow;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> AddEmptyGroupRight;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> AddEmptyGroupNextRow;`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Customizations/DMXControlConsoleDataDetails.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleDataDetails`  
`class FDMXControlConsoleDataDetails : public IDetailCustomization`  
_L14-32_
- inherits: `IDetailCustomization`
- desc: Details Customization for DMX Control Console
- L19 _public prototype_ `FDMXControlConsoleDataDetails(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Constructor
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Makes an instance of this Details Customization
- L26 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L31 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Customizations/DMXControlConsoleElementControllerDetails.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleElementControllerDetails`  
`class FDMXControlConsoleElementControllerDetails : public IDetailCustomization`  
_L16-51_
- inherits: `IDetailCustomization`
- desc: Details Customization for DMX Control Console element controllers
- L21 _public prototype_ `FDMXControlConsoleElementControllerDetails(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Constructor
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Makes an instance of this Details Customization
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L32 _private prototype_ `void OnSelectedElementControllersValueChanged() const;` — Called when the Value property of the selected element controllers is changed
- L35 _private prototype_ `void OnSelectedElementControllersMinValueChanged() const;` — Called when the Min Value property of the selected element controllers is changed
- L38 _private prototype_ `void OnSelectedElementControllersMaxValueChanged() const;` — Called when the Max Value property of the selected element controllers is changed
- L41 _private prototype_ `void OnSelectedElementControllersLockStateChanged() const;` — Called when the Lock state of the selected element controllers is changed
- L44 _private prototype_ `TArray<UDMXControlConsoleElementController*> GetValidElementControllersBeingEdited() const;` — Returns the element controllers being edited in these details. Only returns currently valid objects.
- L47 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property Utilities for this Details Customization layout
- L50 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Customizations/DMXControlConsoleFaderDetails.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleFaderDetails`  
`class FDMXControlConsoleFaderDetails : public IDetailCustomization`  
_L17-67_
- inherits: `IDetailCustomization`
- desc: Details Customization for DMX Control Console faders
- L22 _public prototype_ `FDMXControlConsoleFaderDetails(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Constructor
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Makes an instance of this Details Customization
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L33 _private prototype_ `bool HasOnlyRawFadersSelected() const;` — True if all selected Faders are Raw Faders
- L36 _private prototype_ `void OnSelectedFadersValueChanged() const;` — Called when selected faders Value property value is changed
- L39 _private prototype_ `void OnSelectedFadersMinValueChanged() const;` — Called when selected faders Min Value property value is changed
- L42 _private prototype_ `void OnSelectedFadersMaxValueChanged() const;` — Called when selected faders Max Value property value is changed
- L45 _private prototype_ `bool GetMaxValueResetToDefaultVisibility() const;` — Returns the visibility of the MaxValue property's reset to default button
- L48 _private prototype_ `void OnMaxValueResetToDefaultClicked();` — Called when the MaxValue property's reset to default button was clicked
- L51 _private prototype_ `void OnSelectedFadersUniverseIDChanged() const;` — Called when selected faders UniverseID property value is changed
- L54 _private prototype_ `void OnSelectedFadersDataTypeChanged() const;` — Called when selected faders DataType property value is changed
- L57 _private prototype_ `uint32 GetMaxValueForSignalFormat(EDMXFixtureSignalFormat SignalFormat) const;` — Returns the max value for specified signal format
- L60 _private prototype_ `TArray<UDMXControlConsoleFaderBase*> GetValidFadersBeingEdited() const;` — Returns the faders being edited in these details. Only returns currently valid objects.
- L63 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property Utilities for this Details Customization layout
- L66 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMX` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Customizations/DMXControlConsoleFaderGroupControllerDetails.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleFaderGroupControllerDetails`  
`class FDMXControlConsoleFaderGroupControllerDetails : public IDetailCustomization`  
_L19-63_
- inherits: `IDetailCustomization`
- desc: Details Customization for DMX Control Console fader group controllers
- L24 _public prototype_ `FDMXControlConsoleFaderGroupControllerDetails(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Constructor
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Makes an instance of this Details Customization
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L35 _private prototype_ `bool AreAllFaderGroupControllersUnpatched() const;` — True if all the selected controllers have only unpatched fader groups
- L38 _private prototype_ `bool IsFaderGroupControllersColorEditable() const;` — True if the editor color of the selected controllers can be edited
- L41 _private prototype_ `void OnLockToggleChanged(ECheckBoxState CheckState);` — Called to toggle the lock state of the selected fader group controllers
- L44 _private prototype_ `ECheckBoxState IsLockChecked() const;` — Gets the current lock state of the selected fader group controllers
- L47 _private prototype_ `FReply OnClearButtonClicked();` — Called when Clear button is clicked
- L50 _private prototype_ `EVisibility GetEditorColorVisibility() const;` — Gets the visibility of the Editor Color Property
- L53 _private prototype_ `EVisibility GetClearButtonVisibility() const;` — Gets the visibility of the Clear button
- L56 _private prototype_ `TArray<UDMXControlConsoleFaderGroupController*> GetValidFaderGroupControllersBeingEdited() const;` — Returns the fader gorup controllers being edited in these details. Only returns currently valid objects.
- L59 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property Utilities for this Details Customization layout
- L62 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Customizations/DMXControlConsoleFaderGroupDetails.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleFaderGroupDetails`  
`class FDMXControlConsoleFaderGroupDetails : public IDetailCustomization`  
_L16-45_
- inherits: `IDetailCustomization`
- desc: Details Customization for DMX Control Console fader groups
- L21 _public prototype_ `FDMXControlConsoleFaderGroupDetails(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Constructor
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Makes an instance of this Details Customization
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L32 _private prototype_ `bool IsAnyFaderGroupPatched() const;` — True if at least one selected fader group has any fixture patch bound
- L35 _private prototype_ `FText GetFixturePatchText() const;` — Gets the name of the current selected fader group's Fixture Patch
- L38 _private prototype_ `TArray<UDMXControlConsoleFaderGroup*> GetValidFaderGroupsBeingEdited() const;` — Returns the fader groups being edited in these details. Only returns currently valid objects.
- L41 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property Utilities for this Details Customization layout
- L44 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/DMXControlConsoleCompactEditorMenuContext.h` (Private)


#### class `UDMXControlConsoleCompactEditorMenuContext`  
`class UDMXControlConsoleCompactEditorMenuContext : public UObject`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Menu context for the compact editor toolbar
- L19 _public member_ `TWeakPtr<UE::DMX::Private::SDMXControlConsoleCompactEditorView> WeakCompactEditorView;` — The compact editor view that uses this menu context

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/DMXControlConsoleEditorData.h` (Private)


#### enum `EDMXControlConsoleEditorControlMode`  
`enum class EDMXControlConsoleEditorControlMode : uint8`  
_L16-20_
- reflection: `UENUM()`
- desc: Enum for DMX Control Console control modes
- L18 _public enumerator_ `Relative`
- L19 _public enumerator_ `Absolute`

#### enum `EDMXControlConsoleEditorViewMode`  
`enum class EDMXControlConsoleEditorViewMode : uint8`  
_L24-28_
- reflection: `UENUM()`
- desc: Enum for DMX Control Console view modes
- L26 _public enumerator_ `Collapsed`
- L27 _public enumerator_ `Expanded`

#### enum `EDMXControlConsoleEditorValueType`  
`enum class EDMXControlConsoleEditorValueType : uint8`  
_L32-37_
- reflection: `UENUM()`
- desc: Enum for DMX Control Console value types
- L34 _public enumerator_ `DMX`
- L35 _public enumerator_ `Normalized`
- L36 _public enumerator_ `Physical`

#### struct `FDMXControlConsoleEditorUserFilter`  
`struct FDMXControlConsoleEditorUserFilter`  
_L41-60_
- reflection: `USTRUCT()`
- desc: Struct which describes a User Filter
- L47 _public member_ `FString FilterLabel;` — `UPROPERTY()` — The filter name displayed in the editor
- L51 _public member_ `FString FilterString;` — `UPROPERTY()` — The filter string used in the filtering system
- L55 _public member_ `FLinearColor FilterColor = FLinearColor::White;` — `UPROPERTY()` — The color showed by the filter in the editor
- L59 _public member_ `bool bIsEnabled = false;` — `UPROPERTY()` — True if the filter is enabled

#### struct `FDMXControlConsoleEditorFiltersCollection`  
`struct FDMXControlConsoleEditorFiltersCollection`  
_L64-83_
- reflection: `USTRUCT()`
- desc: Struct for collecting DMX Control Console filter strings
- L70 _public member_ `TArray<FDMXControlConsoleEditorUserFilter> UserFilters;` — `UPROPERTY()` — The array of custom filters created by the user
- L74 _public member_ `TArray<FString> AttributeNameFilterStrings;` — `UPROPERTY()` — The array of attribute name filter strings based on the current Control Console Data
- L78 _public member_ `TArray<FString> UniverseIDFilterStrings;` — `UPROPERTY()` — The array of universe id filter strings based on the current Control Console Data
- L82 _public member_ `TArray<FString> FixtureIDFilterStrings;` — `UPROPERTY()` — The array of fixture id filter strings based on the current Control Console Data

#### class `UDMXControlConsoleEditorData`  
`class UDMXControlConsoleEditorData : public UDMXControlConsoleEditorDataBase`  
_L87-223_
- reflection: `UCLASS()`
- inherits: `UDMXControlConsoleEditorDataBase`
- desc: Control Console container class for editor data
- L94 _public prototype_ `void AddUserFilter(const FString& FilterLabel, const FString& FilterString, const FLinearColor FilterColor, bool bIsEnabled);` — Adds a new User Filter with the given parameters
- L97 _public prototype_ `void RemoveUserFilter(const FString& FilterLabel);` — Removes all the User Filters with the given filter name
- L100 _public prototype_ `FDMXControlConsoleEditorUserFilter* FindUserFilter(const FString& FilterLabel);` — Finds the User Filter which matches the given filter label, or nullptr if none exists
- L103 _public prototype_ `void UpdateFilters(UDMXControlConsoleData* ControlConsoleData);` — Updates the filters collection based on the given Control Console Data
- L106 _public prototype_ `const TArray<FDMXControlConsoleEditorUserFilter>& GetUserFilters() const;` — Gets the array of the User created filter strings.
- L109 _public prototype_ `const TArray<FString>& GetAttributeNameFilters() const;` — Gets the array of Attribute Name filter strings besed on the current Control Console Data
- L112 _public prototype_ `const TArray<FString>& GetUniverseIDFilters() const;` — Gets the array of Universe ID filter strings besed on the current Control Console Data
- L115 _public prototype_ `const TArray<FString>& GetFixtureIDFilters() const;` — Gets the array of Fixture ID filter strings besed on the current Control Console Data
- L118 _public function_ `EDMXControlConsoleEditorControlMode GetControlMode() const` — Gets the current Control Mode for Faders
- L121 _public function_ `void SetControlMode(EDMXControlConsoleEditorControlMode NewControlMode)` — Sets the current Control Mode for Faders
- L124 _public function_ `EDMXControlConsoleEditorViewMode GetFaderGroupsViewMode() const` — Gets the current View Mode for Fader Groups
- L127 _public prototype_ `void SetFaderGroupsViewMode(EDMXControlConsoleEditorViewMode ViewMode);` — Sets the current View Mode for Fader Groups
- L130 _public function_ `EDMXControlConsoleEditorViewMode GetFadersViewMode() const` — Gets the current View Mode for Faders
- L133 _public prototype_ `void SetFadersViewMode(EDMXControlConsoleEditorViewMode ViewMode);` — Sets the current View Mode for Faders
- L136 _public function_ `EDMXControlConsoleEditorValueType GetValueType() const` — Gets the current Value Type for Faders
- L139 _public function_ `void SetValueType(EDMXControlConsoleEditorValueType NewValueType)` — Sets the current Value Type for Faders
- L142 _public function_ `bool GetAutoGroupActivePatches() const` — Gets the current auto-grouping state for the activated Fader Groups
- L145 _public function_ `bool GetAutoSelectActivePatches() const` — Gets the current auto-selection state for the activated Fader Groups
- L148 _public function_ `bool GetAutoSelectFilteredElements() const` — Gets the current auto-selection state for the filtered Elements
- L151 _public prototype_ `void ToggleAutoGroupActivePatches();` — Toggles the auto-grouping state for the activated Fader Groups
- L154 _public prototype_ `void ToggleAutoSelectActivePatches();` — Toggles the auto-selection state for the activated Fader Groups
- L157 _public prototype_ `void ToggleAutoSelectFilteredElements();` — Toggles the auto-selection state for the filtered Elements
- L160 _public function_ `FSimpleMulticastDelegate& GetOnUserFiltersChanged()` — Returns a delegate broadcast whenever the list of User Filters has been changed
- L163 _public function_ `FSimpleMulticastDelegate& GetOnFaderGroupsViewModeChanged()` — Returns a delegate broadcast whenever the Fader Groups view mode is changed
- L166 _public function_ `FSimpleMulticastDelegate& GetOnFadersViewModeChanged()` — Returns a delegate broadcast whenever the Faders view mode is changed
- L169 _public function_ `FSimpleMulticastDelegate& GetOnAutoGroupStateChanged()` — Returns a delegate broadcast whenever the auto-group state is changed
- L173 _public member_ `FDMXReadOnlyFixturePatchListDescriptor FixturePatchListDescriptor;` — `UPROPERTY()` — Fixture Patch List default descriptor
- L177 _public member_ `FDMXControlConsoleCue LoadedCue;` — `UPROPERTY()` — The current loaded control console cue
- L181 _private member_ `FSimpleMulticastDelegate OnUserFiltersChanged;` — Called when the list of User Filters has changed
- L184 _private member_ `FSimpleMulticastDelegate OnFaderGroupsViewModeChanged;` — Called when the Fader Groups view mode is changed
- L187 _private member_ `FSimpleMulticastDelegate OnFadersViewModeChanged;` — Called when the Faders view mode is changed
- L190 _private member_ `FSimpleMulticastDelegate OnAutoGroupStateChanged;` — Called when the auto-gorup state has changed
- L194 _private member_ `FDMXControlConsoleEditorFiltersCollection FiltersCollection;` — `UPROPERTY()` — Collection of filters based on the Control Console Data
- L198 _private member_ `EDMXControlConsoleEditorControlMode ControlMode = EDMXControlConsoleEditorControlMode::Absolute;` — `UPROPERTY()` — Current control mode for Faders widgets
- L202 _private member_ `EDMXControlConsoleEditorViewMode FaderGroupsViewMode = EDMXControlConsoleEditorViewMode::Expanded;` — `UPROPERTY()` — Current view mode for FaderGroupView widgets
- L206 _private member_ `EDMXControlConsoleEditorViewMode FadersViewMode = EDMXControlConsoleEditorViewMode::Collapsed;` — `UPROPERTY()` — Current view mode for Faders widgets
- L210 _private member_ `EDMXControlConsoleEditorValueType ValueType = EDMXControlConsoleEditorValueType::DMX;` — `UPROPERTY()` — Current value type for Faders widgets
- L214 _private member_ `bool bAutoGroupActivePatches = false;` — True if the Fader Groups from activated Fixture Patches must be grouped by default
- L218 _private member_ `bool bAutoSelectActivePatches = false;` — True if the Fader Groups from activated Fixture Patches must be selected by default
- L222 _private member_ `bool bAutoSelectFilteredElements = false;` — True if the filtered Elements must be selected by default

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/DMXControlConsoleEditorFromLegacyUpgradeHandler.h` (Private)


#### class `FDMXControlConsoleEditorFromLegacyUpgradeHandler`  
`class FDMXControlConsoleEditorFromLegacyUpgradeHandler`  
_L15-33_
- desc: Handler to upgrade path from Control Console previous versions
- L19 _public prototype_ `static bool TryUpgradePathFromLegacy();` — Tries to upgrade configuration settings from previous DMXControlConsole versions. Returns true if the upgrade path was taken.
- L23 _private prototype_ `static UDMXControlConsoleData* CreateControlConsoleDataFromFaderDescriptorArray(const TArray<FDMXOutputConsoleFaderDescriptor>& FaderDescriptorArray);` — Creates Fader Groups based on FaderDescriptor array. Used only for compatibility with DMXControlConsole previous versions
- L26 _private prototype_ `static UDMXControlConsoleRawFader* CreateRawFaderFromFaderDescriptor(UDMXControlConsoleFaderGroup* FaderGroup, const FDMXOutputConsoleFaderDescriptor& FaderDescriptor);` — Creates a raw fader for the given Fader Group based on a FaderDescriptor. Used only for compatibility with DMXControlConsole previous versions
- L29 _private prototype_ `static void OnUpgradePathControlConsoleSaved(const UDMXControlConsole* ControlConsole);` — Called when UpgradePathControlConsole asset is saved
- L32 _private member_ `static TWeakObjectPtr<UDMXControlConsole> UpgradePathControlConsole;` — Weak reference to the Control Console created by upgrade path process

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/DMXControlConsoleEditorModule.h` (Private)


#### class `FDMXControlConsoleEditorModule`  
`class FDMXControlConsoleEditorModule : public IDMXControlConsoleEditorModule`  
_L16-84_
- inherits: `IDMXControlConsoleEditorModule`
- desc: Editor Module for DMXControlConsole
- L21 _public prototype_ `FDMXControlConsoleEditorModule();` — Constructor
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public function_ `virtual FAssetCategoryPath GetControlConsoleCategory() const override`
- L33 _public function_ `static EAssetTypeCategories::Type GetDMXEditorAssetCategory()` — Gets the DMX Editor asset category
- L36 _public prototype_ `static void OpenControlConsole();` — Opens the ControlConsole
- L39 _public function_ `TSharedPtr<SDockTab> GetCompactEditorTab() const` — Returns the compact editor tab, or nullptr if the compact editor tab is closed
- L42 _public member_ `static const FName ControlConsoleEditorAppIdentifier;` — Name identifier for the Control Console Editor app
- L45 _public member_ `static const FName CompactEditorTabId;` — Tab Id for the compact editor tab
- L49 _private prototype_ `void RegisterLevelEditorCommands();` — Registers Control Console commands in the Level Editor
- L52 _private prototype_ `static void RegisterDMXMenuExtender();` — Registers an extender for the Level Editor Toolbar DMX Menu
- L55 _private prototype_ `static void ExtendDMXMenu(FMenuBuilder& MenuBuilder);` — Extends the Level Editor Toolbar DMX Menu
- L58 _private prototype_ `void RegisterCompactEditorTabSpawner();` — Registers a tab spawner for the compact editor
- L61 _private prototype_ `static TSharedRef<SDockTab> OnSpawnCompactEditorTab(const FSpawnTabArgs& InSpawnTabArgs);` — Called when the compact editor tab is spawned
- L64 _private prototype_ `static void OnCompactEditorTabClosed(TSharedRef<SDockTab> Tab);` — Called when the compact editor tab was closed
- L67 _private prototype_ `void OnPostEnginInit();` — Called at the end of UEngine::Init, right before loading PostEngineInit modules for both normal execution and commandlets
- L74 _private member_ `TSharedPtr<SDockTab> CompactEditorTab;` — The compact control console editor tab, or nullptr if the tab is closed. Mind we explicitly hold the active tab here, as it may be assigned to any tab manager, not just the global or the level editor tab manager.
- L77 _private member_ `FAssetCategoryPath ControlConsoleCategory;` — The category path under which Control Console assets are nested.
- L80 _private member_ `static EAssetTypeCategories::Type DMXEditorAssetCategory;` — The DMX Editor asset category
- L83 _private member_ `static const FName ControlConsoleEditorTabName;` — Name of the Control Console Editor Tab

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/DMXControlConsoleEditorSelection.h` (Private)


#### class `FDMXControlConsoleEditorSelection`  
`class FDMXControlConsoleEditorSelection final : public TSharedFromThis<FDMXControlConsoleEditorSelection>`  
_L15-114_
- inherits: `TSharedFromThis<FDMXControlConsoleEditorSelection>`
- desc: Class for handling the selection in the DMX Control Console
- L19 _public prototype_ `DECLARE_EVENT(FDMXControlConsoleEditorSelection, FDMXControlConsoleSelectionEvent) FDMXControlConsoleEditorSelection(UDMXControlConsoleEditorModel* InEditorModel);`
- L25 _public prototype_ `void AddToSelection(UDMXControlConsoleFaderGroupController* FaderGroupController, bool bNotifySelectionChange = true);` — Adds the given Fader Group Controller to the selection
- L28 _public prototype_ `void AddToSelection(UDMXControlConsoleElementController* ElementController, bool bNotifySelectionChange = true);` — Adds the given Element Controller to the selection
- L31 _public prototype_ `void AddToSelection(const TArray<UObject*> Objects, bool bNotifySelectionChange = true);` — Adds the objects in the given array to the selection
- L34 _public prototype_ `void AddAllElementControllersFromFaderGroupControllerToSelection(UDMXControlConsoleFaderGroupController* FaderGroupController, bool bOnlyMatchingFilter = false, bool bNotifySelectionChange = true);` — Adds to the selection all the Element Controllers from the given Fader Group Controller
- L37 _public prototype_ `void RemoveFromSelection(UDMXControlConsoleFaderGroupController* FaderGroupController, bool bNotifySelectionChange = true);` — Removes the given Fader Group Controller from selection
- L40 _public prototype_ `void RemoveFromSelection(UDMXControlConsoleElementController* ElementController, bool bNotifySelectionChange = true);` — Removes the given Element Controller from selection
- L43 _public prototype_ `void RemoveFromSelection(const TArray<UObject*> Objects, bool bNotifySelectionChange = true);` — Removes the objects in the given array from selection
- L46 _public prototype_ `void Multiselect(UObject* ElementControllerOrFaderGroupControllerObject);` — Multiselects the Element Controller or Fader Group Controller in the current selection
- L49 _public prototype_ `void ReplaceInSelection(UDMXControlConsoleFaderGroupController* FaderGroupController);` — Replaces the given selected Fader Group Controller with the next available one
- L52 _public prototype_ `void ReplaceInSelection(UDMXControlConsoleElementController* ElementController);` — Replaces the given selected Element Controller with the next available one
- L55 _public prototype_ `bool IsSelected(UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Gets wheter the given Fader Group Controller is selected or not
- L58 _public prototype_ `bool IsSelected(UDMXControlConsoleElementController* ElementController) const;` — Gets wheter the given Element Controller is selected or not
- L61 _public prototype_ `void SelectAll(bool bOnlyMatchingFilter = false);` — Selects all the Fader Group Controllers and Element Controllers in the current layout
- L64 _public prototype_ `void RemoveInvalidObjectsFromSelection(bool bNotifySelectionChange = true);` — Removes all the invalid object in the selected objects arrays
- L67 _public prototype_ `void ClearElementControllersSelection(UDMXControlConsoleFaderGroupController* FaderGroupController, bool bNotifySelectionChange = true);` — Clears all Element Controllers owned by the given Fader Group Controller from the selection
- L70 _public prototype_ `void ClearSelection(bool bNotifySelectionChange = true);` — Clears all the selected objects arrays
- L73 _public function_ `TArray<TWeakObjectPtr<UObject>> GetSelectedFaderGroupControllers() const` — Gets the SelectedFaderGorupControllers array
- L76 _public prototype_ `UDMXControlConsoleFaderGroupController* GetFirstSelectedFaderGroupController(bool bReverse = false) const;` — Gets the first selected Fader Group Controller sorted by index
- L79 _public function_ `TArray<TWeakObjectPtr<UObject>> GetSelectedElementControllers() const` — Gets the SelectedElementControllers array
- L82 _public prototype_ `UDMXControlConsoleElementController* GetFirstSelectedElementController(bool bReverse = false) const;` — Gets the first selected Element Controller sorted by index
- L85 _public prototype_ `TArray<UDMXControlConsoleElementController*> GetSelectedElementControllersFromFaderGroupController(UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Gets all the selected Element Controller from the given Fader Group Controller
- L88 _public prototype_ `TArray<TWeakObjectPtr<UDMXControlConsoleFaderGroup>> GetSelectedFaderGroups(bool bSort = false) const;` — Gets all the selected Fader Groups from the selected Fader Group Controllers array
- L91 _public prototype_ `TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> GetSelectedElements(bool bSort = false) const;` — Gets all the selected Elements from the selected Element Controllers array
- L94 _public function_ `FDMXControlConsoleSelectionEvent& GetOnSelectionChanged()` — Returns an event raised when the selection has changed
- L98 _private prototype_ `void UpdateMultiSelectAnchor(UClass* PreferedClass);` — Updates the multi select anchor
- L101 _private member_ `FDMXControlConsoleSelectionEvent OnSelectionChanged;` — Called whenever the current selection changes
- L104 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedFaderGroupControllers;` — Array of the current selected Fader Group Controllers
- L107 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedElementControllers;` — Array of the current selected Element Controllers
- L110 _private member_ `TWeakObjectPtr<UObject> MultiSelectAnchor;` — Anchor while multi selecting
- L113 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_EVENT(FDMXControlConsoleEditorSelection, FDMXControlConsoleSelectionEvent) FDMXControlConsoleEditorSelection(UDMXControlConsoleEditorModel* InEditorModel);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/DMXControlConsoleEditorToolbar.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleEditorToolbar`  
`class FDMXControlConsoleEditorToolbar : public TSharedFromThis<FDMXControlConsoleEditorToolbar>`  
_L27-115_
- inherits: `TSharedFromThis<FDMXControlConsoleEditorToolbar>`
- desc: Custom toolbar for the DMX Control Console editor
- L32 _public prototype_ `FDMXControlConsoleEditorToolbar(TSharedPtr<FDMXControlConsoleEditorToolkit> InToolkit);` — Constructor
- L35 _public prototype_ `void BuildToolbar(TSharedPtr<FExtender> Extender);` — Builds the toolbar
- L38 _public function_ `const TSharedPtr<SFilterSearchBox>& GetFilterSearchBox() const` — Gets the toolbar's global filter searchbox widget
- L42 _private prototype_ `void BuildToolbarCallback(FToolBarBuilder& ToolbarBuilder);` — Callback, raised when the menu extender requests to build the toolbar
- L45 _private prototype_ `TSharedRef<SWidget> GenerateClearMenuWidget();` — Generates a widget for the clear options
- L48 _private prototype_ `TSharedRef<SWidget> GenerateControlModeMenuWidget();` — Generates a widget to select the current control mode
- L51 _private prototype_ `TSharedRef<SWidget> GenerateViewModeMenuWidget();` — Generates a widget to select the current view mode
- L54 _private prototype_ `TSharedRef<SWidget> GenerateSelectionMenuWidget();` — Generates a widget for the selection options
- L57 _private prototype_ `TSharedRef<SWidget> GenerateLayoutModeMenuWidget();` — Generates a widget to select the current layout mode
- L60 _private prototype_ `void RestoreGlobalFilter();` — Restores the global search filter text from Constrol Console Data
- L63 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);` — Called when the search text has changed
- L66 _private prototype_ `void OnSaveSearchButtonClicked(const FText& InSearchText);` — Called when the save search button is clicked
- L69 _private prototype_ `void OnCreateCustomTextFilter(const FCustomTextFilterData& InFilterData, bool bApplyFilter);` — Called to create a custom filter from the filtering data
- L72 _private prototype_ `void OnCancelCustomFilterWindowClicked();` — Called when the cancel button in the custom filter window is clicked
- L75 _private prototype_ `void OnSelectedPortsChanged();` — Called when the Port selection has changed
- L78 _private prototype_ `ECheckBoxState IsFilteredElementsAutoSelectChecked() const;` — Called to get the filtered Elements auto-selection state
- L81 _private prototype_ `void OnFilteredElementsAutoSelectStateChanged(ECheckBoxState CheckBoxState);` — Called to set the filtered Elements auto-selection state
- L84 _private prototype_ `void OnFaderGroupsViewModeSelected(const EDMXControlConsoleEditorViewMode ViewMode) const;` — Called when a Fader Groups view mode is selected
- L87 _private prototype_ `void OnFadersViewModeSelected(const EDMXControlConsoleEditorViewMode ViewMode) const;` — Called when a Faders view mode is selected
- L90 _private prototype_ `void OnLayoutModeSelected(const EDMXControlConsoleLayoutMode LayoutMode) const;` — Called when a Layout mode is selected
- L93 _private prototype_ `bool IsCurrentLayoutMode(const EDMXControlConsoleLayoutMode LayoutMode) const;` — True if the current layout mode matches the given one
- L96 _private prototype_ `void OnSelectAll(bool bOnlyMatchingFilter = false) const;` — Called when a Selection option is selected
- L99 _private prototype_ `void OnClearAll();` — Called when the Control Console gets cleared
- L102 _private prototype_ `FReply OnShowCompactEditorButtonClicked();` — Called when the show compact editor button was clicked
- L105 _private member_ `TSharedPtr<SFilterSearchBox> GlobalFilterSearchBox;` — Reference to the Control Console's searchbox used for global filtering
- L108 _private member_ `TSharedPtr<SDMXControlConsoleEditorPortSelector> PortSelector;` — Widget to handle the Port selection
- L111 _private member_ `TWeakPtr<SWindow> WeakCustomTextFilterWindow;` — Weak reference to the window containing the custom text filter dialog
- L114 _private member_ `TWeakPtr<FDMXControlConsoleEditorToolkit> WeakToolkit;` — Weak reference to the Control Console editor toolkit

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DMX` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/DMXControlConsolePhysicalUnitToUnitNameLabel.h` (Private)


#### struct `UE::DMX::FDMXControlConsolePhysicalUnitToUnitNameLabel`  
`struct FDMXControlConsolePhysicalUnitToUnitNameLabel`  
_L10-18_
- L13 _public prototype_ `static const FName& GetNameLabel(EDMXGDTFPhysicalUnit PhysicalUnit);` — Returns the name label for the specified physical unit
- L17 _private member_ `static const TMap<EDMXGDTFPhysicalUnit, FName> PhysicalUnitToUnitNameLabelMap;` — A map to list all GDTF compliant Physical Units and their matching Physical Value default ranges.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Factories/DMXControlConsoleActorFactory.h` (Private)


#### class `UDMXControlConsoleActorFactory`  
`class UDMXControlConsoleActorFactory : public UActorFactory`  
_L17-30_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- desc: Actor Factory for DMX Control Console Actor
- L24 _public prototype_ `UDMXControlConsoleActorFactory();` — Constructor
- L27 _public prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L28 _public prototype_ `virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Factories/DMXControlConsoleFactory.h` (Private)


#### class `UDMXControlConsoleFactory`  
`class UDMXControlConsoleFactory : public UFactory`  
_L15-40_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Factory for DMX Control Console
- L22 _public prototype_ `UDMXControlConsoleFactory();` — Constructor
- L25 _public function_ `virtual FText GetDisplayName() const override`
- L26 _public prototype_ `virtual FName GetNewAssetThumbnailOverride() const override;`
- L27 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L28 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L39 _public prototype_ `UDMXControlConsole* CreateConsoleAssetFromData(const FString& SavePackagePath, const FString& SaveAssetName, UDMXControlConsoleData* SourceConsoleData) const;` — Creates a new Control Console asset from provided source control console in desired package name. @param SavePackagePath				The package path @param SaveAssetName					The desired asset name @param SourceControlConsole			The control console copied into the new console @return								The newly created console, or nullptr if no console could be created

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Controllers/DMXControlConsoleCellAttributeController.h` (Private)


#### class `UDMXControlConsoleCellAttributeController`  
`class UDMXControlConsoleCellAttributeController : public UDMXControlConsoleElementController`  
_L15-29_
- reflection: `UCLASS()`
- inherits: `UDMXControlConsoleElementController`
- desc: A controller for handling one or more faders at once in a matrix cell
- L22 _public prototype_ `virtual UDMXControlConsoleFaderGroupController& GetOwnerFaderGroupControllerChecked() const override;`
- L23 _public prototype_ `virtual int32 GetIndex() const override;`
- L24 _public prototype_ `virtual void Destroy() override;`
- L28 _public prototype_ `UDMXControlConsoleMatrixCellController& GetOwnerMatrixCellControllerChecked() const;` — Returns the Matrix Cell Controller this Controller resides in

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Controllers/DMXControlConsoleElementController.h` (Private)


#### class `UDMXControlConsoleElementController`  
`class UDMXControlConsoleElementController : public UDMXControlConsoleControllerBase , public FTickableGameObject`  
_L22-158_
- reflection: `UCLASS(AutoExpandCategories = ("DMX Element Controller", "DMX Element Controller|Oscillator"))`
- inherits: `UDMXControlConsoleControllerBase,FTickableGameObject`
- desc: A controller for handling one or more elements at once. An element can be possessed by one controller at a time.
- L30 _public prototype_ `virtual void Possess(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement);` — Possesses the given Element. An Element Controller can possess more than one Element at once.
- L33 _public prototype_ `virtual void Possess(TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> InElements);` — Possesses the given array of Elements. An Element Controller can possess more than one Element at once.
- L36 _public prototype_ `virtual void UnPossess(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement);` — Unpossesses the given Element, if valid
- L39 _public prototype_ `void ClearElements();` — Clears all the Elements in this Controller
- L42 _public prototype_ `void SortElementsByStartingAddress();` — Sorts all the Elements in this Controller by their starting address
- L45 _public prototype_ `virtual UDMXControlConsoleFaderGroupController& GetOwnerFaderGroupControllerChecked() const;` — Returns the Fader Group Controller this Controller resides in
- L48 _public prototype_ `virtual int32 GetIndex() const;` — Returns the index of the Controller in the owner Fader Group Controller
- L51 _public function_ `const TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>>& GetElements() const` — Gets the array of Elements in this Controller
- L54 _public prototype_ `TArray<UDMXControlConsoleFaderBase*> GetFaders() const;` — Gets the array of Faders in this Controller
- L57 _public function_ `const FString& GetUserName() const` — Gets the name of the Controller
- L60 _public prototype_ `FString GenerateUserNameByElementsNames() const;` — Generates a string using the names of all the Elements in the Controller
- L63 _public prototype_ `void SetUserName(const FString& NewName);` — Sets the name of the Controller
- L66 _public function_ `float GetValue() const` — Returns the value of the Controller
- L69 _public prototype_ `void SetValue(float NewValue, bool bSyncElements = true);` — Sets the value of the Controller and all its Elements
- L72 _public function_ `float GetMinValue() const` — Returns the min value of the Controller
- L75 _public prototype_ `virtual void SetMinValue(float NewMinValue, bool bSyncElements = true);` — Sets the min value of the Controller and all its Elements
- L78 _public function_ `float GetMaxValue() const` — Returns the max value of the Controller
- L81 _public prototype_ `virtual void SetMaxValue(float NewMaxValue, bool bSyncElements = true);` — Sets the max value of the Controller and all its Elements
- L84 _public prototype_ `void ResetToDefault();` — Resets all the Elements in this Controller to their default attribute values
- L87 _public prototype_ `void SetLocked(bool bLock);` — Sets the lock state of this Controller
- L90 _public prototype_ `bool IsActive() const;` — Gets the activity state of the Controller
- L93 _public prototype_ `bool IsMatchingFilter() const;` — True if any of the Elements in the Controller matches the Control Console filtering system
- L96 _public prototype_ `bool IsInActiveLayout() const;` — True if the Controller is in the currently active layout
- L99 _public prototype_ `ECheckBoxState GetEnabledState() const;` — Gets the enable state of the controller according to the possesed fader groups
- L102 _public prototype_ `virtual void Destroy();` — Destroys the Controller
- L105 _public prototype_ `virtual void PostInitProperties() override;`
- L106 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L110 _public function_ `static FName GetUserNamePropertyName()` — Property Name getters
- L111 _public function_ `static FName GetValuePropertyName()`
- L112 _public function_ `static FName GetMinValuePropertyName()`
- L113 _public function_ `static FName GetMaxValuePropertyName()`
- L114 _public function_ `static FName GetElementsPropertyName()`
- L115 _public function_ `static FName GetFloatOscillatorClassPropertyName()`
- L116 _public function_ `static FName GetFloatOscillatorPropertyName()`
- L120 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L121 _protected prototype_ `virtual bool IsTickable() const override;`
- L122 _protected function_ `virtual bool IsTickableInEditor() const override`
- L123 _protected prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L124 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L129 _protected member_ `FString UserName;` — `UPROPERTY(EditAnywhere, Category = "DMX Element Controller")` — The current name of this Controller
- L133 _protected member_ `TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> Elements;` — `UPROPERTY()` — The array of Elements in this Controller
- L137 _private prototype_ `void UpdateControllerValueByElements();` — Updates the value of the Controller according to its Elements
- L141 _private member_ `float Value = 0.f;` — `UPROPERTY(EditAnywhere, meta = (HideEditConditionToggle, EditCondition = "!bIsLocked", UIMin = 0, UIMax = 1), Category = "DMX Element Controller")` — The current value of the Controller
- L145 _private member_ `float MinValue = 0.f;` — `UPROPERTY(EditAnywhere, meta = (EditCondition = "!bIsLocked", UIMin = 0, UIMax = 1), Category = "DMX Element Controller")` — The minimum Controller Value
- L149 _private member_ `float MaxValue = 1.f;` — `UPROPERTY(EditAnywhere, meta = (EditCondition = "!bIsLocked", UIMin = 0, UIMax = 1), Category = "DMX Element Controller")` — The maximum Controller Value
- L153 _private member_ `TSoftClassPtr<UDMXControlConsoleFloatOscillator> FloatOscillatorClass;` — `UPROPERTY(EditAnywhere, meta = (DisplayName = "Oscillator Class", ShowDisplayNames), Category = "DMX Element Controller|Oscillator")` — Oscillator that is used for this Controller
- L157 _private member_ `TObjectPtr<UDMXControlConsoleFloatOscillator> FloatOscillator;` — `UPROPERTY(VisibleAnywhere, Instanced, Meta = (DisplayName = "Oscillator"), Category = "DMX Element Controller|Oscillator")` — Float Oscillator applied to this Controller

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Controllers/DMXControlConsoleFaderGroupController.h` (Private)


#### class `UDMXControlConsoleFaderGroupController`  
`class UDMXControlConsoleFaderGroupController : public UDMXControlConsoleControllerBase`  
_L24-188_
- reflection: `UCLASS(AutoExpandCategories = ("DMX Fader Group Controller"))`
- inherits: `UDMXControlConsoleControllerBase`
- desc: A controller for handling one or more fader groups at once. A fader group can be possessed by one controller at a time.
- L31 _public prototype_ `void Possess(UDMXControlConsoleFaderGroup* InFaderGroup);` — Possesses the given Fader Group. A Fader Group Controller can possess more than one Fader Group at once.
- L34 _public prototype_ `void Possess(TArray<UDMXControlConsoleFaderGroup*> InFaderGroups);` — Possesses the given array of Fader Groups. A Fader Group Controller can possess more than one Fader Group at once.
- L37 _public prototype_ `void UnPossess(UDMXControlConsoleFaderGroup* InFaderGroup);` — Unpossesses the given Fader Group, if valid
- L40 _public prototype_ `void Group();` — Groups all the possessed Fader Groups to minimize the number of Element Controllers
- L43 _public prototype_ `void SortFaderGroupsByAbsoluteAddress();` — Sorts the array of Fader Groups by their absolute address
- L46 _public prototype_ `UDMXControlConsoleEditorGlobalLayoutRow& GetOwnerLayoutRowChecked() const;` — Returns the Layout Row this Controller resides in
- L49 _public prototype_ `UDMXControlConsoleElementController* CreateElementController(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement, const FString& InControllerName = "");` — Creates a Controller for the given Element
- L52 _public prototype_ `UDMXControlConsoleElementController* CreateElementController(const TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> InElements, const FString& InControllerName = "");` — Creates a Controller for the given array of Elements
- L55 _public prototype_ `void GenerateElementControllers();` — Generates an Element Controller for each Element of each Fader Group possesed by the Controller
- L58 _public prototype_ `void DeleteElementController(UDMXControlConsoleElementController* ElementController);` — Deletes the given Element Controller
- L61 _public prototype_ `void SortElementControllersByStartingAddress() const;` — Sorts the array of Element Controllers by the starting address of their Elements
- L64 _public function_ `TArray<UDMXControlConsoleElementController*> GetElementControllers() const` — Gets the array of Element Controllers for this Fader Group Controller
- L67 _public prototype_ `TArray<UDMXControlConsoleElementController*> GetAllElementControllers() const;` — Gets all single (even nested) Element Controllers for this Fader Group Controller
- L70 _public prototype_ `TArray<UDMXControlConsoleElementController*> GetAllElementControllersFromFaderGroup(UDMXControlConsoleFaderGroup* FaderGroup) const;` — Gets an array of all Element Controllers which posses Elements of the given Fader Group Controller
- L73 _public function_ `const TArray<TWeakObjectPtr<UDMXControlConsoleFaderGroup>>& GetFaderGroups() const` — Gets the array of Fader Groups in this Controller
- L76 _public function_ `const FString& GetUserName() const` — Gets the name of the Controller
- L79 _public prototype_ `FString GenerateUserNameByFaderGroupsNames() const;` — Generates a string using the names of all the Fader Groups in the Controller
- L82 _public prototype_ `void SetUserName(const FString& NewName);` — Sets the name of the Controller
- L85 _public prototype_ `bool HasFixturePatch() const;` — True if the Controller has any patched Fader Group
- L88 _public prototype_ `void SetLocked(bool bLock);` — Sets the lock state of this Controller
- L91 _public function_ `const FLinearColor& GetEditorColor() const` — Gets Fader Group Controller color for Editor representation
- L94 _public function_ `bool IsExpanded() const` — Gets the expansion state of the Fader Group Controller
- L97 _public prototype_ `void SetIsExpanded(bool bExpanded, bool bNotify = true);` — Sets the expansion state of the Fader Group Controller
- L100 _public prototype_ `bool IsActive() const;` — Gets the activity state of the Fader Group Controller
- L103 _public function_ `void SetIsActive(bool bActive)` — Sets the activity state of the Fader Group Controller
- L106 _public prototype_ `bool IsMatchingFilter() const;` — True if any of the Fader Groups in the Controller matches the Control Console filtering system
- L109 _public prototype_ `bool IsInActiveLayout() const;` — True if the Controller is in the currently active layout
- L112 _public prototype_ `ECheckBoxState GetEnabledState() const;` — Gets the enable state of the controller according to the possesed fader groups
- L115 _public prototype_ `virtual void Destroy();` — Destroys the Controller
- L118 _public prototype_ `virtual void PostLoad() override;`
- L119 _public prototype_ `virtual void PostInitProperties() override;`
- L123 _public function_ `FSimpleMulticastDelegate& GetOnControllerGrouped()` — Called when all the Fader Groups in this Controller have been grouped
- L126 _public function_ `FSimpleMulticastDelegate& GetOnFixturePatchChanged()` — Called after the Fixture Patch of a Fader Group in the Controller has changed
- L129 _public function_ `FSimpleMulticastDelegate& GetOnFaderGroupControllerExpanded()` — Called when the Controller expansion state changes
- L132 _public function_ `static FName GetUserNamePropertyName()` — Property Name getters
- L133 _public function_ `static FName GetFaderGroupsPropertyName()`
- L134 _public function_ `static FName GetElementControllersPropertyName()`
- L135 _public function_ `static FName GetEditorColorPropertyName()`
- L139 _private prototype_ `void ClearFaderGroups();` — Clears all the Fader Groups in this Controller
- L142 _private prototype_ `void ClearElementControllers();` — Clears all the Element Controllers in this Controller
- L145 _private prototype_ `void GenerateElementControllers(UDMXControlConsoleFaderGroup* FaderGroup);` — Generates an Element Controller for each Element of the given Fader Group
- L148 _private prototype_ `void UpdateElementControllers();` — Updates the Element Controllers array to ensure that each Element has its own Controller
- L151 _private prototype_ `void OnFaderGroupFixturePatchChanged(UDMXControlConsoleFaderGroup* FaderGroup, UDMXEntityFixturePatch* FixturePatch);` — Called when the Fixture Patch of a Fader Group possessed by the Controller has changed
- L154 _private prototype_ `void SyncControllerEditorColor();` — Syncs the Controller's Editor Color according to its patched Fader Groups
- L157 _private member_ `FSimpleMulticastDelegate OnControllerGrouped;` — Called when the Controller has been grouped
- L160 _private member_ `FSimpleMulticastDelegate OnFixturePatchChanged;` — Called after the Fixture Patch of a Fader Group in the Controller has changed
- L163 _private member_ `FSimpleMulticastDelegate OnFaderGroupControllerExpanded;` — Called when the Controller expansion state changes
- L167 _private member_ `FString UserName;` — `UPROPERTY(EditAnywhere, Category = "DMX Fader Group Controller")` — The current name of this Controller
- L171 _private member_ `TArray<TWeakObjectPtr<UDMXControlConsoleFaderGroup>> FaderGroups;` — `UPROPERTY()` — The array of Fader Groups in this Controller
- L175 _private member_ `TArray<TObjectPtr<UDMXControlConsoleElementController>> ElementControllers;` — `UPROPERTY()` — The array of Controllers for the Elements in this Fader Group Controllers
- L179 _private member_ `FLinearColor EditorColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = "DMX Fader Group Controller")` — Color for Fader Group Controller representation on the Editor
- L183 _private member_ `bool bIsExpanded = true;` — `UPROPERTY()` — Fader Group Controller expansion state saved from the Editor
- L187 _private member_ `bool bIsActive = false;` — `UPROPERTY()` — In Editor activity state of the Fader Group Controller

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Controllers/DMXControlConsoleMatrixCellController.h` (Private)


#### class `UDMXControlConsoleMatrixCellController`  
`class UDMXControlConsoleMatrixCellController : public UDMXControlConsoleElementController`  
_L17-70_
- reflection: `UCLASS(AutoExpandCategories = ("DMX Element Controller", "DMX Element Controller|Oscillator"))`
- inherits: `UDMXControlConsoleElementController`
- desc: A controller for handling one or more matrix cells at once. A matrix cell can be possessed by one controller at a time.
- L24 _public prototype_ `virtual void Possess(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement) override;`
- L25 _public prototype_ `virtual void Possess(TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> InElements) override;`
- L26 _public prototype_ `virtual void UnPossess(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement) override;`
- L27 _public prototype_ `virtual void Destroy() override;`
- L31 _public prototype_ `void Group();` — Groups all the possessed Elements to minimize the number of Cell Attribute Controllers
- L34 _public prototype_ `UDMXControlConsoleCellAttributeController* CreateCellAttributeController(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement, const FString& InControllerName = "");` — Creates a Cell Attribute Controller for the given Element
- L37 _public prototype_ `UDMXControlConsoleCellAttributeController* CreateCellAttributeController(const TArray<TScriptInterface<IDMXControlConsoleFaderGroupElement>> InElements, const FString& InControllerName = "");` — Creates a Cell Attribute Controller for the given array of Elements
- L40 _public prototype_ `void GenerateCellAttributeControllers();` — Generates a Cell Attribute Controller for each Element of each Matrix Cell possesed by the Controller
- L43 _public prototype_ `void DeleteCellAttributeController(UDMXControlConsoleCellAttributeController* CellAttributeController);` — Deletes the given Cell Attribute Controller
- L46 _public prototype_ `void ClearCellAttributeControllers();` — Clears all the Cell Attribute Controllers in this Controller
- L49 _public prototype_ `void SortCellAttributeControllersByStartingAddress() const;` — Sorts the array of Cell Attribute Controllers by the starting address of their Elements
- L52 _public function_ `TArray<UDMXControlConsoleCellAttributeController*> GetCellAttributeControllers() const` — Gets the array of Cell Attribute Controllers for this Matrix Cell Controller
- L55 _public prototype_ `TArray<UDMXControlConsoleCellAttributeController*> GetAllCellAttributeControllersFromElement(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement) const;` — Gets an array of all Cell Attribute Controllers which posses Faders of the given Element
- L58 _public function_ `static FName GetCellAttributeControllersPropertyName()` — Property Name getters
- L62 _private prototype_ `void GenerateCellAttributeControllers(const TScriptInterface<IDMXControlConsoleFaderGroupElement>& InElement);` — Generates a Cell Attribute Controller for each Fader of the given Element
- L65 _private prototype_ `void UpdateCellAttributeControllers();` — Updates the Cell Attribute Controllers array to ensure that each Element has its own Controller
- L69 _private member_ `TArray<TObjectPtr<UDMXControlConsoleCellAttributeController>> CellAttributeControllers;` — `UPROPERTY()` — The array of Cell Attribute Controllers for this Matrix Cell Controller

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/DMXControlConsoleEditorGlobalLayoutBase.h` (Private)


#### enum `EDMXControlConsoleLayoutMode`  
`enum class EDMXControlConsoleLayoutMode : uint8`  
_L22-28_
- reflection: `UENUM()`
- desc: Enum for DMX Control Console layout modes
- L24 _public enumerator_ `Horizontal`
- L25 _public enumerator_ `Vertical`
- L26 _public enumerator_ `Grid`
- L27 _public enumerator_ `None`

#### class `UDMXControlConsoleEditorGlobalLayoutBase`  
`class UDMXControlConsoleEditorGlobalLayoutBase : public UObject`  
_L32-169_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Base class for the Control Console layout
- L39 _public prototype_ `UDMXControlConsoleFaderGroupController* AddToLayout(UDMXControlConsoleFaderGroup* InFaderGroup, const FString& ControllerName = "", const int32 RowIndex = INDEX_NONE, const int32 ColumnIndex = INDEX_NONE);` — Adds a new Controller for the given Fader Group to the layout, at the given row/column index
- L42 _public prototype_ `UDMXControlConsoleFaderGroupController* AddToLayout(const TArray<UDMXControlConsoleFaderGroup*> InFaderGroups, const FString& ControllerName = "", const int32 RowIndex = INDEX_NONE, const int32 ColumnIndex = INDEX_NONE);` — Adds a new Controller for the given array of Fader Groups to the layout, at the given row/column index
- L45 _public prototype_ `UDMXControlConsoleEditorGlobalLayoutRow* AddNewRowToLayout(const int32 RowIndex = INDEX_NONE);` — Adds a new Layout Row at the given index
- L48 _public prototype_ `UDMXControlConsoleEditorLayouts& GetOwnerEditorLayoutsChecked() const;` — Gets the editor layouts object which owns this layout
- L51 _public function_ `const TArray<UDMXControlConsoleEditorGlobalLayoutRow*>& GetLayoutRows() const` — Gets an array of all the Layout Rows in this layout
- L54 _public prototype_ `UDMXControlConsoleEditorGlobalLayoutRow* GetLayoutRow(const UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Gets the Layout Row which owns the given Fader Group Controller, if valid
- L57 _public prototype_ `TArray<UDMXControlConsoleFaderGroupController*> GetAllFaderGroupControllers() const;` — Gets an array of all the Fader Group Controllers in this layout
- L60 _public prototype_ `void AddToActiveFaderGroupControllers(UDMXControlConsoleFaderGroupController* FaderGroupController);` — Adds the given Fader Group Controller to the array of active Controllers
- L63 _public prototype_ `void RemoveFromActiveFaderGroupControllers(UDMXControlConsoleFaderGroupController* FaderGroupController);` — Removes the given Fader Group Controller form the array of active Controllers
- L66 _public prototype_ `TArray<UDMXControlConsoleFaderGroupController*> GetAllActiveFaderGroupControllers() const;` — Gets an array of all the active Fader Group Controllers in this layout
- L69 _public prototype_ `void SetActiveFaderGroupControllersInLayout(bool bActive);` — Sets the activity state of all the Fader Group Controllers in the layout
- L72 _public prototype_ `int32 GetFaderGroupControllerRowIndex(const UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Gets the row index of the given Fader Group Controller, if valid
- L75 _public prototype_ `int32 GetFaderGroupControllerColumnIndex(const UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Gets the column index of the given Fader Group Controller, if valid
- L78 _public function_ `EDMXControlConsoleLayoutMode GetLayoutMode() const` — Gets the current layout mode
- L81 _public prototype_ `void SetLayoutMode(const EDMXControlConsoleLayoutMode NewLayoutMode);` — Sets the current layout mode
- L84 _public prototype_ `bool ContainsFaderGroupController(const UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — True if the layout contains the given Fader Group Controller
- L87 _public prototype_ `bool ContainsFaderGroup(const UDMXControlConsoleFaderGroup* FaderGroup) const;` — True if one of the Controllers in the layout possesses the given Fader Group
- L90 _public prototype_ `UDMXControlConsoleFaderGroupController* FindFaderGroupControllerByFixturePatch(const UDMXEntityFixturePatch* InFixturePatch) const;` — Finds the Fader Group Controller matching the given Fixture Patch in the layout, if valid
- L93 _public prototype_ `void GenerateLayoutByControlConsoleData(const UDMXControlConsoleData* ControlConsoleData);` — Generates Layout Rows by the given Control Console Data
- L96 _public prototype_ `void SortLayoutByUniverseID();` — Sorts the the Controllers in the layout by their universe id
- L104 _public prototype_ `void ClearAll(const bool bPatchedControllers, const bool bUnpatchedControllers);` — Clears all Layout Rows @param bPatchedControllers True to clear all patched Fader Group Controllers @param bUnpatchedControllers True to clear all unpatched Fader Group Controllers
- L107 _public prototype_ `void ClearEmptyLayoutRows();` — Clears all empty Layout Rows in the layout
- L110 _public prototype_ `void Register(UDMXControlConsoleData* ControlConsoleData);` — Registers this layout
- L113 _public prototype_ `void Unregister(UDMXControlConsoleData* ControlConsoleData);` — Unregisters this layout
- L116 _public function_ `bool IsRegistered() const` — True if this layout is registered to the DMX Library delegates
- L119 _public prototype_ `virtual void PostLoad() override;`
- L123 _public function_ `static FName GetLayoutModePropertyName()` — Property Name getters
- L124 _public function_ `static FName GetLayoutNamePropertyName()`
- L128 _public member_ `FString LayoutName;` — `UPROPERTY()` — Name identifier of this Layout
- L132 _private prototype_ `bool IsDefaultLayout() const;` — True if this layout is the Default Layout
- L135 _private prototype_ `TMap<int32, TArray<UDMXControlConsoleFaderGroupController*>> GetUniverseIDToControllersMap() const;` — Gets a map where each Fader Group Controllers in this layout is sorted by universe id
- L138 _private prototype_ `void UpdateActiveLayoutByControllersData() const;` — Updates this layout according to its Controllers data, if it's the active layout
- L141 _private prototype_ `void OnActiveLayoutChanged(const UDMXControlConsoleEditorGlobalLayoutBase* ActiveLayout);` — Called when the active layout has changed
- L144 _private prototype_ `void OnFixturePatchRemovedFromLibrary(UDMXLibrary* Library, TArray<UDMXEntity*> Entities);` — Called when a Fixture Patch was removed from a DMX Library
- L147 _private prototype_ `void OnFaderGroupAddedToData(const UDMXControlConsoleFaderGroup* FaderGroup);` — Called when a Fader Group was added to the Control Console Data
- L150 _private prototype_ `void CleanLayoutFromFaderGroupControllers(const bool bHasFixturePatch);` — Called to clean this layout from specified Fader Group Controllers
- L153 _private prototype_ `void CleanDefaultLayoutFromUnpatchedFaderGroups();` — Called to clean the default layout from unpatched Fader Groups
- L157 _private member_ `TArray<TObjectPtr<UDMXControlConsoleEditorGlobalLayoutRow>> LayoutRows;` — `UPROPERTY()` — Reference to the Layout Rows array
- L161 _private member_ `TArray<TWeakObjectPtr<UDMXControlConsoleFaderGroupController>> ActiveFaderGroupControllers;` — `UPROPERTY()` — Array of the currently active Fader Group Controllers in the layout
- L165 _private member_ `EDMXControlConsoleLayoutMode LayoutMode = EDMXControlConsoleLayoutMode::Grid;` — `UPROPERTY()` — Current layout sorting method for this layout
- L168 _private member_ `bool bIsRegistered = false;` — True if the layout is registered to the DMX Library delegates

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/DMXControlConsoleEditorGlobalLayoutRow.h` (Private)


#### class `UDMXControlConsoleEditorGlobalLayoutRow`  
`class UDMXControlConsoleEditorGlobalLayoutRow : public UObject`  
_L17-54_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A row of Fader Group Controllers in the Control Console Global Layout
- L24 _public prototype_ `UDMXControlConsoleFaderGroupController* CreateFaderGroupController(UDMXControlConsoleFaderGroup* InFaderGroup, const FString& ControllerName = "", const int32 Index = INDEX_NONE);` — Creates a Controller for the given Fader Group
- L27 _public prototype_ `UDMXControlConsoleFaderGroupController* CreateFaderGroupController(const TArray<UDMXControlConsoleFaderGroup*> InFaderGroups, const FString& ControllerName = "", const int32 Index = INDEX_NONE);` — Creates a Controller for the given array of Fader Groups
- L30 _public prototype_ `void DeleteFaderGroupController(UDMXControlConsoleFaderGroupController* FaderGroupController);` — Deletes the given Fader Group Controller
- L33 _public function_ `const TArray<UDMXControlConsoleFaderGroupController*>& GetFaderGroupControllers() const` — Gets Fader Group Controllers array for this row
- L36 _public prototype_ `int32 GetRowIndex() const;` — Gets the Index of this row according to the owner layout
- L39 _public prototype_ `UDMXControlConsoleEditorGlobalLayoutBase& GetOwnerLayoutChecked() const;` — Gets the layout that owns this row
- L42 _public prototype_ `UDMXControlConsoleFaderGroupController* GetFaderGroupControllerAt(int32 Index) const;` — Gets the Fader Group Controller at the given index, if valid
- L45 _public prototype_ `int32 GetIndex(const UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Gets index of the given Fader Group Controller, if valid
- L48 _public function_ `static FName GetFaderGroupControllersPropertyName()` — Property Name getters
- L53 _private member_ `TArray<TObjectPtr<UDMXControlConsoleFaderGroupController>> FaderGroupControllers;` — `UPROPERTY()` — Reference to the Fader Group Controllers array

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/DMXControlConsoleEditorLayouts.h` (Private)


#### class `UDMXControlConsoleEditorLayouts`  
`class UDMXControlConsoleEditorLayouts : public UDMXControlConsoleEditorLayoutsBase`  
_L15-94_
- reflection: `UCLASS()`
- inherits: `UDMXControlConsoleEditorLayoutsBase`
- desc: Control Console container class for layouts data
- L20 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleEditorLayoutDelegate, const UDMXControlConsoleEditorGlobalLayoutBase*);`
- L27 _public prototype_ `UDMXControlConsoleEditorLayouts();` — Constructor
- L30 _public prototype_ `UDMXControlConsoleEditorGlobalLayoutBase* AddUserLayout(const FString& LayoutName);` — Adds a new User Layout
- L33 _public prototype_ `void DeleteUserLayout(UDMXControlConsoleEditorGlobalLayoutBase* UserLayout);` — Deletes the given User Layout
- L36 _public prototype_ `UDMXControlConsoleEditorGlobalLayoutBase* FindUserLayoutByName(const FString& LayoutName) const;` — Finds the User Layout with the given name, if valid
- L39 _public prototype_ `void ClearUserLayouts();` — Clears UserLayouts array
- L42 _public prototype_ `UDMXControlConsoleEditorGlobalLayoutBase& GetDefaultLayoutChecked() const;` — Gets a reference to the Default Layout
- L45 _public function_ `const TArray<UDMXControlConsoleEditorGlobalLayoutBase*>& GetUserLayouts() const` — Gets User Layouts array
- L48 _public function_ `UDMXControlConsoleEditorGlobalLayoutBase* GetActiveLayout() const` — Gets reference to the active Layout
- L51 _public prototype_ `void SetActiveLayout(UDMXControlConsoleEditorGlobalLayoutBase* InLayout);` — Sets the active Layout
- L54 _public prototype_ `void UpdateDefaultLayout();` — Updates the default Layout to Control Console Data
- L57 _public prototype_ `void Register(UDMXControlConsoleData* ControlConsoleData);` — Registers all the layouts
- L60 _public prototype_ `void Unregister(UDMXControlConsoleData* ControlConsoleData);` — Unregisters all the layouts
- L63 _public prototype_ `virtual void BeginDestroy() override;`
- L64 _public prototype_ `virtual void PostLoad() override;`
- L68 _public function_ `FDMXControlConsoleEditorLayoutDelegate& GetOnActiveLayoutChanged()` — Called after the Active Layout has been changed
- L71 _public function_ `FSimpleMulticastDelegate& GetOnLayoutModeChanged()` — Called after the Active Layouts's layout mode has been changed
- L75 _private prototype_ `FString GenerateUniqueUserLayoutName(const FString& LayoutName);` — Generates a unique name for a user layout
- L78 _private member_ `FDMXControlConsoleEditorLayoutDelegate OnActiveLayoutChanged;` — Called after the Active Layout has been changed
- L81 _private member_ `FSimpleMulticastDelegate OnLayoutModeChanged;` — Called after the Active Layouts's layout mode has been changed
- L85 _private member_ `TObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase> DefaultLayout;` — `UPROPERTY()` — Reference to the Default Layout
- L89 _private member_ `TArray<TObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase>> UserLayouts;` — `UPROPERTY()` — Array of User Layouts
- L93 _private member_ `TObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase> ActiveLayout;` — `UPROPERTY()` — Reference to the active Layout in use

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleEditorLayoutDelegate, const UDMXControlConsoleEditorGlobalLayoutBase*);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Widgets/SDMXControlConsoleEditorGridLayout.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorGridLayout`  
`class SDMXControlConsoleEditorGridLayout : public SDMXControlConsoleEditorLayout`  
_L19-61_
- inherits: `SDMXControlConsoleEditorLayout`
- desc: Draws the fader groups of a control console in a grid
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorGridLayout)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorGlobalLayoutBase* InLayout, UDMXControlConsoleEditorModel* InEditorModel);`
- L32 _protected prototype_ `virtual bool CanRefresh() const override;`
- L33 _protected prototype_ `virtual void OnLayoutElementAdded() override;`
- L34 _protected prototype_ `virtual void OnLayoutElementRemoved() override;`
- L39 _private prototype_ `bool IsLayoutRowContained(UDMXControlConsoleEditorGlobalLayoutRow* LayoutRow);` — Checks if the LayoutRowViews array contains a reference to the given
- L42 _private prototype_ `TSharedPtr<SDMXControlConsoleEditorLayoutRowView> FindLayoutRowView(const UDMXControlConsoleEditorGlobalLayoutRow* LayoutRow);` — Finds LayoutRowView by the given LayoutRow, if valid
- L45 _private prototype_ `void OnScrollIntoView(const UDMXControlConsoleFaderGroupController* FaderGroupController);` — Called when a LayoutRowView needs to be scrolled into view
- L48 _private prototype_ `EVisibility GetLayoutRowViewVisibility(TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutRow> LayoutRow) const;` — Gets visibility for each LayoutRowView widget
- L51 _private member_ `TSharedPtr<SVerticalBox> LayoutRowsVerticalBox;` — Reference to the container widget of this DMX Control Console's Layout Rows slots
- L54 _private member_ `TSharedPtr<SScrollBox> HorizontalScrollBox;` — Reference to the horizontal ScrollBox widget
- L57 _private member_ `TSharedPtr<SScrollBox> VerticalScrollBox;` — Reference to the vertical ScrollBox widget
- L60 _private member_ `TArray<TWeakPtr<SDMXControlConsoleEditorLayoutRowView>> LayoutRowViews;` — Array of weak references to the Layout Row widgets

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMX` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Widgets/SDMXControlConsoleEditorHorizontalLayout.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorHorizontalLayout`  
`class SDMXControlConsoleEditorHorizontalLayout : public SDMXControlConsoleEditorLayout`  
_L18-55_
- inherits: `SDMXControlConsoleEditorLayout`
- desc: Draws the fader groups of a control console horizontally
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorHorizontalLayout)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorGlobalLayoutBase* InLayout, UDMXControlConsoleEditorModel* InEditorModel);`
- L32 _protected prototype_ `virtual bool CanRefresh() const override;`
- L33 _protected prototype_ `virtual void OnLayoutElementAdded() override;`
- L34 _protected prototype_ `virtual void OnLayoutElementRemoved() override;`
- L39 _private prototype_ `bool IsFaderGroupControllerContained(UDMXControlConsoleFaderGroupController* FaderGroupController);` — Return true if the Fader Group Controllers array contains a reference to the given Controller
- L42 _private prototype_ `void OnScrollIntoView(const UDMXControlConsoleFaderGroupController* FaderGroupController);` — Called when a Fader Group Controller needs to be scrolled into view
- L45 _private prototype_ `EVisibility GetFaderGroupControllerViewVisibility(TWeakObjectPtr<UDMXControlConsoleFaderGroupController> FaderGroupController) const;` — Gets the visibility for each Fader Group Controller view in this layout
- L48 _private member_ `TSharedPtr<SHorizontalBox> FaderGroupControllersHorizontalBox;` — The widget containing the Fader Group Controller views
- L51 _private member_ `TSharedPtr<SScrollBox> HorizontalScrollBox;` — The horizontal ScrollBox widget
- L54 _private member_ `TArray<TWeakPtr<SDMXControlConsoleEditorFaderGroupControllerView>> FaderGroupControllerViews;` — Array of weak references to the Fader Group Controller views

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Widgets/SDMXControlConsoleEditorLayout.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorLayout`  
`class SDMXControlConsoleEditorLayout : public SCompoundWidget`  
_L15-54_
- inherits: `SCompoundWidget`
- desc: Base widget for Control Console layout
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorLayout)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorGlobalLayoutBase* InLayout, UDMXControlConsoleEditorModel* InEditorModel);`
- L28 _public function_ `UDMXControlConsoleEditorGlobalLayoutBase* GetEditorLayout() const` — Gets the Layout this view is based on
- L31 _public prototype_ `virtual void RequestRefresh();` — Requests this layout to be refreshed
- L35 _protected function_ `virtual bool CanRefresh() const` — True if refreshing layout is allowed
- L38 _protected prototype_ `virtual void Refresh();` — Refreshes layout
- L41 _protected prototype_ `virtual void OnLayoutElementAdded() = 0;` — Called when an Element is added to this layout
- L44 _protected prototype_ `virtual void OnLayoutElementRemoved() = 0;` — Should be called when a Fader Group was deleted from the this view displays
- L47 _protected member_ `FTimerHandle RefreshLayoutTimerHandle;` — Timer handle in use while refreshing layout is requested but not carried out yet
- L50 _protected member_ `TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase> EditorLayout;` — Weak Reference to the Editor Layout
- L53 _protected member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Layouts/Widgets/SDMXControlConsoleEditorVerticalLayout.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorVerticalLayout`  
`class SDMXControlConsoleEditorVerticalLayout : public SDMXControlConsoleEditorLayout`  
_L18-55_
- inherits: `SDMXControlConsoleEditorLayout`
- desc: Draws the fader groups of a control console vertically
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorVerticalLayout)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorGlobalLayoutBase* InLayout, UDMXControlConsoleEditorModel* InEditorModel);`
- L32 _protected prototype_ `virtual bool CanRefresh() const override;`
- L33 _protected prototype_ `virtual void OnLayoutElementAdded() override;`
- L34 _protected prototype_ `virtual void OnLayoutElementRemoved() override;`
- L39 _private prototype_ `bool IsFaderGroupControllerContained(UDMXControlConsoleFaderGroupController* FaderGroupController);` — Checks if the Fader Group Controllers array contains a reference to the given Controller
- L42 _private prototype_ `void OnScrollIntoView(const UDMXControlConsoleFaderGroupController* FaderGroupController);` — Called when a Fader Group Controller view needs to be scrolled into view
- L45 _private prototype_ `EVisibility GetFaderGroupControllerViewVisibility(TWeakObjectPtr<UDMXControlConsoleFaderGroupController> FaderGroupController) const;` — Gets the visibility for each Fader Group Controller view in this layout
- L48 _private member_ `TSharedPtr<SVerticalBox> FaderGroupControllersVerticalBox;` — The widget containing the Fader Group Controller views
- L51 _private member_ `TSharedPtr<SScrollBox> VerticalScrollBox;` — The vertical ScrollBox widget
- L54 _private member_ `TArray<TWeakPtr<SDMXControlConsoleEditorFaderGroupControllerView>> FaderGroupControllerViews;` — Array of weak references to the Fader Group Controller views

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleCompactEditorModel.h` (Private)


#### class `UDMXControlConsoleCompactEditorModel`  
`class UDMXControlConsoleCompactEditorModel : public UObject`  
_L17-45_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Model for the compact view of a control console
- L24 _public prototype_ `void SetControlConsole(UDMXControlConsole* ControlConsole);` — Sets the control console for the compact editor. Opens the editor if it is closed.
- L27 _public prototype_ `void RestoreFullEditor();` — Restores the full editor for the current console.
- L30 _public prototype_ `void StopPlayingDMX();` — Stops playing DMX if the compact editor is currently playing DMX
- L33 _public prototype_ `bool IsUsingControlConsole(const UDMXControlConsole* ControlConsole) const;` — Returns true if the specified control console is currently displayed in the compact editor, without loading the console
- L36 _public prototype_ `UDMXControlConsole* LoadControlConsoleSynchronous() const;` — Loads the current control console, or gets it if it's already loaded. Returns nullptr if no control console is set.
- L39 _public member_ `FSimpleMulticastDelegate OnModelChanged;` — Delegate broadcast when the model changed
- L44 _private member_ `TSoftObjectPtr<UDMXControlConsole> SoftControlConsole;` — `UPROPERTY(Config)` — The control console currently in use in the compact editor

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleCueStackModel.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleCueStackModel`  
`class FDMXControlConsoleCueStackModel : public TSharedFromThis<FDMXControlConsoleCueStackModel>`  
_L19-59_
- inherits: `TSharedFromThis<FDMXControlConsoleCueStackModel>`
- desc: Model for the control console cue stack
- L24 _public prototype_ `FDMXControlConsoleCueStackModel(UDMXControlConsole* InControlConsole);` — Constructor
- L27 _public prototype_ `UDMXControlConsoleData* GetControlConsoleData() const;` — Gets a reference to the control console data
- L30 _public prototype_ `UDMXControlConsoleEditorData* GetControlConsoleEditorData() const;` — Gets a reference to the control console editor data
- L33 _public prototype_ `UDMXControlConsoleEditorLayouts* GetControlConsoleEditorLayouts() const;` — Gets a reference to the control console editor layouts
- L36 _public prototype_ `UDMXControlConsoleCueStack* GetControlConsoleCueStack() const;` — Gets a reference to the control console cue stack
- L39 _public prototype_ `bool IsAddNewCueButtonEnabled() const;` — True if it is possible to add a new cue to the cue stack
- L42 _public prototype_ `bool IsStoreCueButtonEnabled(const FDMXControlConsoleCue& Cue) const;` — True if the cue stack is ready to store new cue data
- L45 _public prototype_ `void AddNewCue() const;` — Adds a new cue to the control console cue stack
- L48 _public prototype_ `void StoreCue(const FDMXControlConsoleCue& Cue) const;` — Stores the given cue in the control console cue stack
- L51 _public prototype_ `void RecallCue(const FDMXControlConsoleCue& Cue) const;` — Recalls the given cue
- L54 _public prototype_ `void ClearCueStack() const;` — Clears the control console cue stack
- L58 _private member_ `const TWeakObjectPtr<UDMXControlConsole> WeakControlConsole;` — The control console used with this model

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleEditorModel.h` (Private)


#### class `UDMXControlConsoleEditorModel`  
`class UDMXControlConsoleEditorModel : public UObject`  
_L24-118_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Model of the console currently being edited in the control console editor.
- L29 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleFaderGroupControllerDelegate, const UDMXControlConsoleFaderGroupController*);`
- L33 _public prototype_ `void Initialize(UDMXControlConsole* InControlConsole);` — Initializes the model
- L36 _public function_ `UDMXControlConsole* GetControlConsole() const` — Returns the edited Control Console
- L39 _public prototype_ `UDMXControlConsoleData* GetControlConsoleData() const;` — Returns the edited Control Console data
- L42 _public prototype_ `UDMXControlConsoleEditorData* GetControlConsoleEditorData() const;` — Returns the edited Control Console editor data
- L45 _public prototype_ `UDMXControlConsoleEditorLayouts* GetControlConsoleLayouts() const;` — Returns the edited Control Console layouts
- L48 _public prototype_ `TSharedRef<FDMXControlConsoleEditorSelection> GetSelectionHandler();` — Gets a reference to the Selection Handler
- L51 _public prototype_ `TSharedRef<UE::DMX::Private::FDMXControlConsoleGlobalFilterModel> GetGlobalFilterModel();` — Gets a reference to the Filter Model
- L54 _public prototype_ `void ScrollIntoView(const UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Scrolls the given Fader Group Controller into view
- L57 _public prototype_ `void RequestUpdateEditorModel();` — Requests the Editor Model to be updated
- L60 _public prototype_ `virtual void PostInitProperties() override;`
- L61 _public prototype_ `virtual void BeginDestroy() override;`
- L65 _public function_ `FDMXControlConsoleFaderGroupControllerDelegate& GetOnScrollFaderGroupControllerIntoView()` — Returns a delegate broadcast whenever a Fader Group Controller needs to be scrolled into view
- L68 _public function_ `FSimpleMulticastDelegate& GetOnEditorModelUpdated()` — Returns a delegate broadcast whenever Editor Model has changed
- L72 _private prototype_ `void UpdateEditorModel();` — Updates the Editor Model
- L75 _private prototype_ `void BindToDMXLibraryChanges();` — Binds Editor Model to the current DMX Library changes
- L78 _private prototype_ `void UnbindFromDMXLibraryChanges();` — Unbinds Editor Model from the current DMX Library changes
- L81 _private prototype_ `void InitializeEditorData() const;` — Initializes current Control Console's Editor Data, if not valid
- L84 _private prototype_ `void InitializeEditorLayouts() const;` — Initializes current Control Console's Editor Layouts, if not valid
- L87 _private prototype_ `void RegisterEditorLayouts() const;` — Registers current Editor Layouts to delegates
- L90 _private prototype_ `void UnregisterEditorLayouts() const;` — Unregisters current Editor Layouts from delegates
- L93 _private prototype_ `void OnDMXLibraryChanged();` — Called when the DMX Library of the current Control Console has been changed
- L96 _private prototype_ `void OnFaderGroupAddedToData(const UDMXControlConsoleFaderGroup* FaderGroup);` — Called when a new Fader Group is added to the Control Console Data
- L99 _private prototype_ `void OnEnginePreExit() const;` — Called before the engine is shut down
- L102 _private member_ `FDMXControlConsoleFaderGroupControllerDelegate OnScrollFaderGroupControllerIntoView;` — Called when a Fader Group Controller needs to be scrolled into view
- L105 _private member_ `FSimpleMulticastDelegate OnEditorModelUpdated;` — Called when Editor Model has been updated
- L108 _private member_ `FTimerHandle UpdateEditorModelTimerHandle;` — Timer handle in use while updating Editor Model is requested but not carried out yet
- L111 _private member_ `TSharedPtr<UE::DMX::Private::FDMXControlConsoleGlobalFilterModel> GlobalFilterModel;` — The global filter model for the current edited Control Console
- L114 _private member_ `TSharedPtr<FDMXControlConsoleEditorSelection> SelectionHandler;` — Selection handler for the current edited Control Console
- L117 _private member_ `TWeakObjectPtr<UDMXControlConsole> ControlConsole;` — Weak reference to the current edited Control Console

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DMX` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::DMX`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DMX` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::DMX`)
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXControlConsoleFaderGroupControllerDelegate, const UDMXControlConsoleFaderGroupController*);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleEditorPlayMenuModel.h` (Private)


#### class `UDMXControlConsoleEditorPlayMenuModel`  
`class UDMXControlConsoleEditorPlayMenuModel : public UObject`  
_L18-83_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Model for the control console play menu
- L25 _public prototype_ `void Initialize(UDMXControlConsole* InControlConsole, const TSharedRef<FUICommandList>& InCommandList);` — Inits the PlayMenuModel from a control console and a command list. The PlayMenuModels actions are mapped to the specified command list
- L28 _public prototype_ `void CreatePlayMenu(UToolMenu& InMenu);` — Creates a play menu to the provided tool menu
- L31 _public function_ `const TSharedPtr<FUICommandList>& GetCommandList() const` — Returns the command list, or nullptr if no command list was set
- L34 _public prototype_ `bool CanPlayDMX() const;` — Returns true if DMX can be played
- L37 _public prototype_ `bool CanResumeDMX() const;` — Returns true if playing DMX can be resumed (requires the console to be paused and CanPlayDMX).
- L40 _public prototype_ `void PlayDMX();` — Starts to play DMX
- L43 _public prototype_ `bool CanPauseDMX() const;` — Returns true if playing DMX can be paused
- L46 _public prototype_ `void PauseDMX();` — Pauses playing DMX. Current DMX values will still be sent at a lower rate.
- L49 _public prototype_ `bool CanStopPlayingDMX() const;` — Returns true if playing DMX can be stopped
- L52 _public prototype_ `void StopPlayingDMX();` — Stops playing DMX
- L55 _public prototype_ `void TogglePlayPauseDMX();` — Toggles between playing and pausing DMX
- L58 _public prototype_ `void TogglePlayStopDMX();` — Toggles between playing and stopping DMX
- L61 _public prototype_ `void SetStopDMXMode(EDMXControlConsoleStopDMXMode StopDMXMode);` — Sets the stop mode for the asset being edited
- L64 _public prototype_ `bool IsUsingStopDMXMode(EDMXControlConsoleStopDMXMode TestStopMode) const;` — Returns true if the console uses the tested stop mode
- L67 _public prototype_ `bool IsPlayingDMX() const;` — Returns true if the console is playing DMX
- L70 _public prototype_ `bool IsPausedDMX() const;` — Returns true if the console is paused sending DMX
- L75 _private member_ `TObjectPtr<UDMXControlConsole> ControlConsole;` — `UPROPERTY(NonTransactional)` — The control console data used with this model
- L79 _private member_ `TObjectPtr<UDMXControlConsoleData> ControlConsoleData;` — `UPROPERTY(NonTransactional)` — The control console data used with this model
- L82 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list for this PlayMenuModel

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleElementControllerModel.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleElementControllerModel`  
`class FDMXControlConsoleElementControllerModel : public TSharedFromThis<FDMXControlConsoleElementControllerModel>`  
_L19-92_
- inherits: `TSharedFromThis<FDMXControlConsoleElementControllerModel>`
- desc: Model for an element controller in the Control Console
- L24 _public prototype_ `FDMXControlConsoleElementControllerModel(const TWeakObjectPtr<UDMXControlConsoleElementController> InWeakElementController, const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Constructor
- L27 _public prototype_ `UDMXControlConsoleElementController* GetElementController() const;` — Gets the Element Controller this model is based on
- L30 _public prototype_ `UDMXControlConsoleFaderBase* GetFirstAvailableFader() const;` — Gets the first available Fader in the Element Controller, if valid
- L33 _public prototype_ `UDMXControlConsoleFixturePatchMatrixCell* GetMatrixCellElement() const;` — Gets the first Matrix Cell Element in the Controller, if valid
- L36 _public prototype_ `TArray<UDMXControlConsoleElementController*> GetMatchingAttributeElementControllers(bool bSameOwnerControllerOnly = false) const;` — Gets all Element Controllers in the active layout matching this Element Controller's attribute (or name, if attribute is not valid)
- L39 _public prototype_ `FString GetRelativeControllerName() const;` — Gets the name of the Element Controller, relative to the contained Elements
- L42 _public prototype_ `float GetRelativeValue() const;` — Gets the value of the Element Controller, relative to the contained Elements
- L45 _public prototype_ `float GetRelativeMinValue() const;` — Gets the min value of the Element Controller, relative to the contained Elements
- L48 _public prototype_ `float GetRelativeMaxValue() const;` — Gets the max value of the Element Controller, relative to the contained Elements
- L51 _public prototype_ `EDMXGDTFPhysicalUnit GetPhysicalUnit() const;` — Gets the physical unit of the Element Controller, relative to the contained Elements
- L54 _public prototype_ `double GetPhysicalValue() const;` — Gets the physical value of the Element Controller, relative to the contained Elements
- L57 _public prototype_ `double GetPhysicalFrom() const;` — Gets the physical from value of the Element Controller, relative to the contained Elements
- L60 _public prototype_ `double GetPhysicalTo() const;` — Gets the physical to value of the Element Controller, relative to the contained Elements
- L63 _public prototype_ `bool HasSingleElement() const;` — True if the Controller has just one Element
- L66 _public prototype_ `bool HasUniformDataType() const;` — True if the Controller has Elements with the same data type
- L69 _public prototype_ `bool HasUniformPhysicalUnit() const;` — True if the Controller has Elements with the same physical unit
- L72 _public prototype_ `bool HasUniformValue() const;` — True if the Controller has Elements with the same value
- L75 _public prototype_ `bool HasUniformMinValue() const;` — True if the Controller has Elements with the same min value
- L78 _public prototype_ `bool HasUniformMaxValue() const;` — True if the Controller has Elements with the same max value
- L81 _public prototype_ `bool HasOnlyRawFaders() const;` — True if all Elements in the controller are raw faders
- L84 _public prototype_ `bool IsLocked() const;` — True if all the Elements in the Controller are locked
- L88 _private member_ `TWeakObjectPtr<UDMXControlConsoleElementController> WeakElementController;` — Weak reference to the Element Controller this model is based on
- L91 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console edior model

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleFaderGroupControllerModel.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleFaderGroupControllerModel`  
`class FDMXControlConsoleFaderGroupControllerModel : public TSharedFromThis<FDMXControlConsoleFaderGroupControllerModel>`  
_L18-58_
- inherits: `TSharedFromThis<FDMXControlConsoleFaderGroupControllerModel>`
- desc: Model for a fader group controller in a Control Console
- L23 _public prototype_ `FDMXControlConsoleFaderGroupControllerModel(const TWeakObjectPtr<UDMXControlConsoleFaderGroupController> InWeakFaderGroupController, const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Constructor
- L26 _public prototype_ `UDMXControlConsoleFaderGroupController* GetFaderGroupController() const;` — Gets the Fader Group Controller this model is based on
- L29 _public prototype_ `UDMXControlConsoleFaderGroup* GetFirstAvailableFaderGroup() const;` — Gets the first available Fader Group in the Fader Group Controller, if valid
- L32 _public prototype_ `TArray<UDMXControlConsoleElementController*> GetMatchingFilterElementControllersOnly() const;` — Gets an array with only Element Controllers that match the current filter
- L35 _public prototype_ `FString GetRelativeControllerName() const;` — Gets the name of the Fader Group Controller, relative to the contained Fader Groups
- L38 _public prototype_ `bool HasSingleFaderGroup() const;` — True if the Controller has just one Fader Group
- L41 _public prototype_ `bool CanAddFaderGroupController() const;` — True if a new Fader Group Controller can be added next to this
- L44 _public prototype_ `bool CanAddFaderGroupControllerOnNewRow() const;` — True if a new Fader Group Controller can be added on next row
- L47 _public prototype_ `bool CanAddElementController() const;` — True if a new Element Controller can be added
- L50 _public prototype_ `bool IsLocked() const;` — True if all the Fader Groups in the Controller are locked
- L54 _private member_ `TWeakObjectPtr<UDMXControlConsoleFaderGroupController> WeakFaderGroupController;` — Weak reference to the Fader Group Controller this model is based on
- L57 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console edior model

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMX` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleFilterModel.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleFilterModel`  
`class FDMXControlConsoleFilterModel : public TSharedFromThis<FDMXControlConsoleFilterModel>`  
_L14-68_
- inherits: `TSharedFromThis<FDMXControlConsoleFilterModel>`
- desc: Model for a filter in a DMX Control Console
- L21 _public prototype_ `FDMXControlConsoleFilterModel(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel, const FString& InFilterLabel, const FString& InFilterString, const FLinearColor InFilterColor, bool bInIsUserFilter = false);` — Constructor
- L24 _public function_ `FString GetFilterLabel() const` — Gets the name label of the filter
- L27 _public function_ `FString GetFilterString() const` — Gets the string associated with this filter
- L30 _public function_ `FLinearColor GetFilterColor() const` — Gets the color of the filter
- L33 _public function_ `bool IsUserFilter() const` — Gets wether this is a user created filter or not
- L36 _public function_ `bool IsEnabled() const` — Gets the enable state of the filter
- L39 _public prototype_ `void SetIsEnabled(bool bEnable);` — Sets the enable state of the filter
- L42 _public prototype_ `void RemoveFilter() const;` — Removes the filter described by this model from the control console editor data
- L45 _public function_ `FDMXControlConsoleFilterModelDelegate& GetOnEnableStateChanged()` — Called when the enable state of this filter has changed
- L49 _private member_ `FString FilterLabel;` — The displayed name label of the filter
- L52 _private member_ `FString FilterString;` — The filter string associated with the filter
- L55 _private member_ `FLinearColor FilterColor;` — The color showed by the filter in the editor
- L58 _private member_ `bool bIsUserFilter = false;` — True if the filter is created by the user
- L61 _private member_ `bool bIsEnabled = false;` — True if the filter is enabled
- L64 _private member_ `FDMXControlConsoleFilterModelDelegate OnEnableStateChanged;` — The delegate to execute when the enable state of this filter has changed
- L67 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console edior model

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DMX`)
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FDMXControlConsoleFilterModelDelegate, TSharedPtr<FDMXControlConsoleFilterModel>) public: FDMXControlConsoleFilterModel(const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel, const FString& InFilterLabel, const FString& InFilterString, const FLinearColor InFilterColor, bool bInIsUserFilter = false);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleFixturePatchListRowModel.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleFixturePatchListRowModel`  
`class FDMXControlConsoleFixturePatchListRowModel : public TSharedFromThis<FDMXControlConsoleFixturePatchListRowModel>`  
_L16-37_
- inherits: `TSharedFromThis<FDMXControlConsoleFixturePatchListRowModel>`
- desc: Model for a row in the control console fixture patch list
- L20 _public prototype_ `FDMXControlConsoleFixturePatchListRowModel(const TWeakObjectPtr<UDMXEntityFixturePatch> InWeakFixturePatch, const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);`
- L23 _public prototype_ `bool IsRowEnabled() const;` — Returns true if the row widget is enabled
- L26 _public prototype_ `ECheckBoxState GetFaderGroupEnabledState() const;` — Returns the fader group enable state. Checked means it is enabled.
- L29 _public prototype_ `void SetFaderGroupEnabled(bool bEnable);` — Sets if the fader group is enabled.
- L33 _private member_ `TWeakObjectPtr<UDMXEntityFixturePatch> WeakFixturePatch;` — The fixture patch of this row
- L36 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console edior model

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/Filter/DMXControlConsoleFaderFilterModel.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleFaderFilterModel`  
`class FDMXControlConsoleFaderFilterModel : public TSharedFromThis<FDMXControlConsoleFaderFilterModel>`  
_L20-42_
- inherits: `TSharedFromThis<FDMXControlConsoleFaderFilterModel>`
- desc: Filter model for a single fader
- L24 _public prototype_ `FDMXControlConsoleFaderFilterModel() = delete;`
- L25 _public prototype_ `FDMXControlConsoleFaderFilterModel(UDMXControlConsoleFaderBase* InFader);`
- L28 _public prototype_ `[[nodiscard]] bool MatchesAnyName(const TArray<FString>& Names) const;` — returns true if the fader name contains one of the names in the Names array
- L31 _public prototype_ `[[nodiscard]] bool MatchesGlobalFilter(const FGlobalFilter& GlobalFilter, ENameFilterMode NameFilterMode);` — Returns true if the fader matches the global filter
- L34 _public prototype_ `[[nodiscard]] bool MatchesFaderGroupFilter(const FFaderGroupFilter& FaderGroupFilter);` — Returns true if the fader matches the fader group filter
- L37 _public prototype_ `UDMXControlConsoleFaderBase* GetFader() const;` — Gets the fader this model uses
- L41 _private member_ `TWeakObjectPtr<UDMXControlConsoleFaderBase> WeakFader;` — The fader this model uses

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/Filter/DMXControlConsoleFaderGroupFilterModel.h` (Private)


#### struct `UE::DMX::Private::FFaderGroupFilter`  
`struct FFaderGroupFilter`  
_L19-26_
- desc: Filter of a fader group
- L21 _public prototype_ `void Parse(const FString& InString);`
- L22 _public prototype_ `void Reset();`
- L24 _public member_ `FString String;`
- L25 _public member_ `TArray<FString> Names;`

#### class `UE::DMX::Private::FDMXControlConsoleFaderGroupFilterModel`  
`class FDMXControlConsoleFaderGroupFilterModel : public TSharedFromThis<FDMXControlConsoleFaderGroupFilterModel>`  
_L29-78_
- inherits: `TSharedFromThis<FDMXControlConsoleFaderGroupFilterModel>`
- desc: Filter model for a single fader group
- L33 _public prototype_ `FDMXControlConsoleFaderGroupFilterModel() = delete;`
- L34 _public prototype_ `FDMXControlConsoleFaderGroupFilterModel(UDMXControlConsoleFaderGroup* InFaderGroup);`
- L37 _public prototype_ `UDMXControlConsoleFaderGroup* GetFaderGroup() const;` — Returns the fader group of this model
- L40 _public prototype_ `void SetFilter(const FString& InString);` — Sets the fader group filter
- L43 _public prototype_ `[[nodiscard]] bool MatchesGlobalFilterUniverseAndAddress(const FGlobalFilter& GlobalFilter) const;` — Returns true if this group matches the global filter universes and address
- L46 _public prototype_ `[[nodiscard]] bool MatchesGlobalFilterNames(const FGlobalFilter& GlobalFilter) const;` — Returns true if this group matches the global filter names  (e.g. "MovingHead")
- L49 _public prototype_ `[[nodiscard]] bool MatchesGlobalFilterFixtureIDs(const FGlobalFilter& GlobalFilter) const;` — Returns true if this group matches the global filter fixture ids
- L52 _public prototype_ `[[nodiscard]] bool HasFadersMatchingGlobalFilterNames(const FGlobalFilter& GlobalFilter) const;` — Returns true if this group has faders that match the global filter names (e.g. "R, G, Blue")
- L55 _public prototype_ `void Apply(const FGlobalFilter& GlobalFilter, ENameFilterMode NameFilterMode);` — Applies the filters
- L58 _public prototype_ `void UpdateFaderModels();` — Updates the array of fader models
- L62 _private prototype_ `bool IsMatchingGlobalFilterUniverseAndAddress(const FGlobalFilter& GlobalFilter) const;` — Returns true if this group matches one of the universes and the absolute address in the global filter
- L65 _private prototype_ `bool IsMatchingGlobalFilterNames(const FGlobalFilter& GlobalFilter) const;` — Returns true if this group matches one of the names in the global filter
- L68 _private prototype_ `bool IsMatchingGlobalFilterFixtureIDs(const FGlobalFilter& GlobalFilter) const;` — Returns true if this group matches one of the fixture ids in the global filter
- L71 _private member_ `FFaderGroupFilter FaderGroupFilter;` — The filter of this group
- L74 _private member_ `TArray<TSharedRef<FDMXControlConsoleFaderFilterModel>> FaderModels;` — Fader Filter Models used in this model
- L77 _private member_ `TWeakObjectPtr<UDMXControlConsoleFaderGroup> WeakFaderGroup;` — Fader group of this model

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/Filter/DMXControlConsoleGlobalFilterModel.h` (Private)


#### enum `UE::DMX::Private::ENameFilterMode`  
`enum class ENameFilterMode : uint8`  
_L27-33_
- desc: Defines if the model fitlers for fader group names, fader names or both.
- L29 _public enumerator_ `MatchFaderGroupNames`
- L30 _public enumerator_ `MatchFaderNames`
- L31 _public enumerator_ `MatchFaderAndFaderGroupNames`
- L32 _public enumerator_ `None`

#### struct `UE::DMX::Private::FGlobalFilter`  
`struct FGlobalFilter`  
_L36-50_
- desc: Global filter
- L38 _public prototype_ `void Parse(const FString& InString);`
- L39 _public prototype_ `void Reset();`
- L41 _public prototype_ `TOptional<int32> GetUniverse() const;`
- L42 _public prototype_ `TOptional<int32> GetChannel() const;`
- L44 _public member_ `FString String;`
- L45 _public member_ `TArray<int32> Universes;`
- L46 _public member_ `TArray<int32> FixtureIDs;`
- L47 _public member_ `TOptional<int32> AbsoluteAddress;`
- L48 _public member_ `TArray<FString> Names;`

#### class `UE::DMX::Private::FDMXControlConsoleGlobalFilterModel`  
`class FDMXControlConsoleGlobalFilterModel : public TSharedFromThis<FDMXControlConsoleGlobalFilterModel> , public FSelfRegisteringEditorUndoClient`  
_L54-124_
- inherits: `TSharedFromThis<FDMXControlConsoleGlobalFilterModel>,FSelfRegisteringEditorUndoClient`
- desc: Model for the global control console filtering
- L64 _public prototype_ `FDMXControlConsoleGlobalFilterModel(UDMXControlConsoleEditorModel* InEditorModel);` — Constructor
- L67 _public prototype_ `void Initialize();` — Initializes the model
- L70 _public prototype_ `void SetGlobalFilter(const FString& FilterString);` — Sets a filter that is applied to the model
- L73 _public prototype_ `void SetFaderGroupFilter(UDMXControlConsoleFaderGroup* FaderGroup, const FString& FilterString);` — Sets a filter to the specified fader group
- L76 _public member_ `FSimpleMulticastDelegate OnFilterChanged;` — Delegate broadcast when the filter changed
- L80 _protected prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L81 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L82 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L87 _private prototype_ `void UpdateNameFilterMode();` — Updates the name filter mode to use
- L90 _private prototype_ `void InitializeInternal();` — Initializes the model from the current editor control console
- L93 _private prototype_ `void UpdateFaderGroupModels();` — Updates the array of fader group models
- L96 _private prototype_ `void UpdateControlConsoleData();` — Updates the Control Console Data reference
- L99 _private prototype_ `void ApplyFilter();` — Applies filter
- L102 _private prototype_ `void OnEditorConsoleDataChanged(const UDMXControlConsoleFaderGroup* FaderGroup);` — Called when the Control Console Data have been changed by adding/removing Fader Groups
- L105 _private prototype_ `void OnFaderGroupElementsChanged(IDMXControlConsoleFaderGroupElement* Element);` — Called when a Fader Group has been changed by adding/removing Elements
- L108 _private prototype_ `void OnFaderGroupFixturePatchChanged(UDMXControlConsoleFaderGroup* FaderGroup, UDMXEntityFixturePatch* FixturePatch);` — Called when a Fader Group fixture patch has changed
- L111 _private member_ `FGlobalFilter GlobalFilter;` — The global filter used in this model
- L114 _private member_ `ENameFilterMode NameFilterMode = ENameFilterMode::None;` — Mode in which the filter currently should be applied
- L117 _private member_ `TArray<TSharedRef<FDMXControlConsoleFaderGroupFilterModel>> FaderGroupModels;` — Fader Group Models used in this model
- L120 _private member_ `TWeakObjectPtr<UDMXControlConsoleData> WeakControlConsoleData;` — Control console data used in this model
- L123 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DMX` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::DMX`)
- L24 _prototype_ `TArray<FString> ParseStringIntoArray(const FString& InString);` (scope `UE::DMX::Private`) — Utility to parse a filter string into an array

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Style/DMXControlConsoleEditorStyle.h` (Private)


#### class `FDMXControlConsoleEditorStyle`  
`class FDMXControlConsoleEditorStyle : public FSlateStyleSet`  
_L10-22_
- inherits: `FSlateStyleSet`
- desc: DMX Control Console Editor Style
- L15 _public prototype_ `FDMXControlConsoleEditorStyle();` — Constructor
- L18 _public prototype_ `virtual ~FDMXControlConsoleEditorStyle();` — Desonstructor
- L21 _public prototype_ `static const FDMXControlConsoleEditorStyle& Get();` — Returns the style instance

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Toolkits/DMXControlConsoleEditorToolkit.h` (Private)


#### class `UE::DMX::Private::FDMXControlConsoleEditorToolkit`  
`class FDMXControlConsoleEditorToolkit : public FAssetEditorToolkit , public FGCObject`  
_L33-203_
- inherits: `FAssetEditorToolkit,FGCObject`
- desc: Implements an Editor toolkit for Control Console.
- L37 _private typedef_ `using Super = FAssetEditorToolkit;`
- L40 _public prototype_ `FDMXControlConsoleEditorToolkit();`
- L41 _public prototype_ `~FDMXControlConsoleEditorToolkit();`
- L50 _public prototype_ `void InitControlConsoleEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UDMXControlConsole* InControlConsole);` — Edits the specified control console object. @param Mode The tool kit mode. @param InitToolkitHost @param ObjectToEdit The control console object to edit.
- L53 _public function_ `UDMXControlConsole* GetControlConsole() const` — Returns the edited Control Console
- L56 _public prototype_ `UDMXControlConsoleData* GetControlConsoleData() const;` — Returns the edited Control Console Data
- L59 _public prototype_ `UDMXControlConsoleEditorData* GetControlConsoleEditorData() const;` — Returns the edited Control Console Editor Data
- L62 _public prototype_ `UDMXControlConsoleEditorLayouts* GetControlConsoleLayouts() const;` — Returns the edited Control Console Layouts
- L65 _public function_ `TSharedPtr<FDMXControlConsoleCueStackModel> GetControlConsoleCueStackModel() const` — Returns the Control Console Cue Stack Model, if valid
- L68 _public function_ `UDMXControlConsoleEditorModel* GetControlConsoleEditorModel() const` — Returns the Control Console Editor Model, if valid
- L71 _public prototype_ `void RemoveAllSelectedElements();` — Removes all selected elements from DMX Control Console
- L74 _public prototype_ `void ClearAll();` — Clears the DMX Control Console and all its elements
- L77 _public prototype_ `void ResetToDefault();` — Resets all the elements in the Control Console to their default values
- L80 _public prototype_ `void ResetToZero();` — Resets all the elements in the Control Console to zero
- L83 _public prototype_ `void Reload();` — Reloads the Control Console asset from the disk
- L86 _public prototype_ `void ShowCompactEditor();` — Closes this editor and presents the compact editor instead
- L89 _public member_ `static const FName DMXLibraryViewTabID;` — Name of the DMX Library View Tab
- L92 _public member_ `static const FName LayoutViewTabID;` — Name of the Layout View Tab
- L95 _public member_ `static const FName DetailsViewTabID;` — Name of the Details View Tab
- L98 _public member_ `static const FName FiltersViewTabID;` — Name of the Filters View Tab
- L101 _public member_ `static const FName CueStackViewTabID;` — Name of the Cue Stack View Tab
- L105 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L106 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L107 _protected prototype_ `virtual const FSlateBrush* GetDefaultTabIcon() const override;`
- L111 _protected prototype_ `virtual FText GetBaseToolkitName() const override;`
- L112 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L113 _protected function_ `virtual FLinearColor GetWorldCentricTabColorScale() const override`
- L114 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L118 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L119 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L124 _private prototype_ `void InitializeInternal(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, const FGuid& MessageLogGuid);` — Internally initializes the toolkit
- L127 _private prototype_ `void GenerateInternalViews();` — Generates all the views of the asset toolkit
- L130 _private prototype_ `TSharedRef<SDMXControlConsoleEditorDMXLibraryView> GenerateDMXLibraryView();` — Generates the DMX Library View for this Control Console instance
- L133 _private prototype_ `TSharedRef<SDMXControlConsoleEditorLayoutView> GenerateLayoutView();` — Generates the Layout View for this Control Console instance
- L136 _private prototype_ `TSharedRef<SDMXControlConsoleEditorDetailsView> GenerateDetailsView();` — Generates the Details View for this Control Console instance
- L139 _private prototype_ `TSharedRef<SDMXControlConsoleEditorFiltersView> GenerateFiltersView();` — Generates the Filters View for this Control Console instance
- L142 _private prototype_ `TSharedRef<SDMXControlConsoleEditorCueStackView> GenerateCueStackView();` — Generates the Cue Stack View for this Control Console instance
- L145 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DMXLibraryView(const FSpawnTabArgs& Args);` — Spawns the DMX Library View
- L148 _private prototype_ `TSharedRef<SDockTab> SpawnTab_LayoutView(const FSpawnTabArgs& Args);` — Spawns the Layout View
- L151 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DetailsView(const FSpawnTabArgs& Args);` — Spawns the Details View
- L154 _private prototype_ `TSharedRef<SDockTab> SpawnTab_FiltersView(const FSpawnTabArgs& Args);` — Spawns the Filters View
- L157 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CueStackView(const FSpawnTabArgs& Args);` — Spawns the Cue Stack View
- L160 _private prototype_ `void SetupCommands();` — Setups the asset toolkit's commands
- L163 _private prototype_ `void ExtendToolbar();` — Extends the asset toolkit's toolbar
- L166 _private member_ `bool bStopSendingDMXOnDestruct = true;` — If true, stops the control console when this widget is destructed
- L169 _private member_ `bool bSwitchingToCompactEditor = false;` — True while switching to compact editor
- L172 _private member_ `TSharedPtr<FDMXControlConsoleEditorToolbar> Toolbar;` — The DMX toolbar extension for this toolkit's toolbar
- L175 _private member_ `TSharedPtr<SDMXControlConsoleEditorDMXLibraryView> DMXLibraryView;` — The DMX Library View instance
- L178 _private member_ `TSharedPtr<SDMXControlConsoleEditorLayoutView> LayoutView;` — The Layout View instance
- L181 _private member_ `TSharedPtr<SDMXControlConsoleEditorDetailsView> DetailsView;` — The Details View instance
- L184 _private member_ `TSharedPtr<SDMXControlConsoleEditorFiltersView> FiltersView;` — The Filters View instance
- L187 _private member_ `TSharedPtr<SDMXControlConsoleEditorCueStackView> CueStackView;` — The Cue Stack View instance
- L190 _private member_ `TObjectPtr<UDMXControlConsoleEditorPlayMenuModel> PlayMenuModel;` — The Play Menu Model for the Control Console this toolkit is based on
- L193 _private member_ `TSharedPtr<FDMXControlConsoleCueStackModel> CueStackModel;` — The Cue Stack Model for the Control Console this toolkit is based on
- L196 _private member_ `TObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — The Editor Model for the Control Console this toolkit is based on
- L199 _private member_ `TObjectPtr<UDMXControlConsole> ControlConsole;` — The Control Console object this toolkit is based on
- L202 _private member_ `UE::DMX::FDMXEditorToolAnalyticsProvider AnalyticsProvider;` — The analytics provider for this tool

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DMX` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleCompactEditorView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleCompactEditorView`  
`class SDMXControlConsoleCompactEditorView : public SCompoundWidget , public FGCObject`  
_L23-99_
- inherits: `SCompoundWidget,FGCObject`
- desc: Compact view of a control console
- L28 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleCompactEditorView)`
- L33 _public prototype_ `~SDMXControlConsoleCompactEditorView();`
- L36 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget
- L40 _protected prototype_ `FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L44 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L45 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L50 _private prototype_ `void SetupCommands();` — Sets up commands for this widget
- L53 _private prototype_ `TSharedRef<SWidget> CreateToolbar();` — Creates a toolbar for this view
- L56 _private prototype_ `TSharedRef<SWidget> GenerateCueStackToolbarWidget();` — Generates the toolbar widget for managing the Control Console cue stack
- L59 _private prototype_ `static void PopulateToolbar(UToolMenu* InMenu);` — Populates the toolbar. Useful as it may not be possible to populate at construction, e.g. on engine startup
- L62 _private prototype_ `void OnSaveClicked();` — Called when the 'Save' button was clicked
- L65 _private prototype_ `void OnFindInContentBrowserClicked();` — Called when the 'Find In Content Browser' button was clicked
- L68 _private prototype_ `FReply OnShowFullEditorButtonClicked();` — Called when the 'Show Full Editor' button was clicked
- L71 _private prototype_ `FText GetAssetNameText() const;` — Returns the name of the asset
- L74 _private prototype_ `EVisibility GetCueStackViewVisibility() const;` — Gets the visibility state of the cue stack
- L77 _private member_ `TObjectPtr<UDMXControlConsole> ControlConsole;` — The control console editor model this widget uses
- L80 _private member_ `bool bStopSendingDMXOnDestruct = true;` — If true, stops sending DMX when this widget is destructed
- L83 _private member_ `TObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — The control console editor model this widget uses
- L86 _private member_ `TSharedPtr<FDMXControlConsoleCueStackModel> CueStackModel;` — The Cue Stack Model for the Control Console this toolkit is based on
- L89 _private member_ `TObjectPtr<UDMXControlConsoleEditorPlayMenuModel> PlayMenuModel;` — The play menu model this widget uses
- L92 _private member_ `TSharedPtr<SCheckBox> CueStackCheckBox;` — The check box for showing the cue stack
- L95 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list this widget uses
- L98 _private member_ `static const FName ToolbarMenuName;` — The menu name of the toolbar in this view

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DMX` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorCueStackView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorCueStackView`  
`class SDMXControlConsoleEditorCueStackView : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L19-78_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: View for displaying the cue stack of the edited Control Console
- L24 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorCueStackView)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FDMXControlConsoleCueStackModel> InCueStackModel);`
- L34 _protected prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L35 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L36 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L41 _private prototype_ `TSharedRef<SWidget> GenerateCueListToolbar();` — Generates a toolbar for the Cue List this view displays
- L44 _private prototype_ `TSharedRef<SWidget> GenerateCueListToolbarButtonContent(const FText& Label, const FText& ToolTip, const FSlateBrush* IconBrush, const FSlateColor IconColor);` — Generates the content of a Cue List toolbar button with the given parameters
- L47 _private prototype_ `bool IsAddNewCueButtonEnabled() const;` — True if there's at least one fader group in the current control console
- L50 _private prototype_ `bool IsStoreCueButtonEnabled() const;` — True if there's at least one selected cue item
- L53 _private prototype_ `bool IsRecallCueButtonEnabled() const;` — True if there's at least one selected cue item
- L56 _private prototype_ `bool IsClearAllCuesButtonEnabled() const;` — True if at least one cue exists in the current cue stack
- L59 _private prototype_ `FReply OnAddNewCueClicked();` — Called when the add new cue button is clicked
- L62 _private prototype_ `FReply OnStoreCueClicked();` — Called when the store cue button is clicked
- L65 _private prototype_ `FReply OnRecallCueClicked();` — Called when the recall cue button is clicked
- L68 _private prototype_ `FReply OnClearCueStackClicked();` — Called when the clear cue stack button is clicked
- L71 _private prototype_ `void OnDMXLibraryChanged();` — Called when the DMX Library has been changed
- L74 _private member_ `TSharedPtr<SDMXControlConsoleEditorCueList> CueList;` — Reference to the Cue List this view displays
- L77 _private member_ `TWeakPtr<FDMXControlConsoleCueStackModel> WeakCueStackModel;` — Weak reference to the Control Console Cue Stack Model

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorDMXLibraryView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorDMXLibraryView`  
`class SDMXControlConsoleEditorDMXLibraryView : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L17-58_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: View for displaying the dmx library handler for the edited Control Console
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorDMXLibraryView)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorModel* InEditorModel);`
- L32 _protected prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L33 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L34 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L39 _private prototype_ `void UpdateFixturePatchVerticalBox();` — Updates FixturePatchVerticalBox widget
- L42 _private prototype_ `void OnControlConsoleDataPropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — Called when a Property has changed in current Control Console Data
- L45 _private prototype_ `void OnDMXLibraryChanged();` — Called when the DMX Library in use has been changed
- L48 _private prototype_ `void OnDMXLibraryReloaded();` — Called when the DMX Library in use has been reloaded
- L51 _private member_ `TSharedPtr<SDMXControlConsoleEditorFixturePatchVerticalBox> FixturePatchVerticalBox;` — Reference to FixturePatchRows widgets container
- L54 _private member_ `TSharedPtr<IDetailsView> ControlConsoleDataDetailsView;` — Shows DMX Control Console Data's details
- L57 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console Editor Model

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorDetailsView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorDetailsView`  
`class SDMXControlConsoleEditorDetailsView : public SCompoundWidget`  
_L18-69_
- inherits: `SCompoundWidget`
- desc: View for displaying the details of the elements in the edited Control Console
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorDetailsView)`
- L28 _public prototype_ `~SDMXControlConsoleEditorDetailsView();` — Destructor
- L31 _public prototype_ `void Construct(const FArguments& InArgs, UDMXControlConsoleEditorModel* InEditorModel);` — Constructs the widget
- L35 _private prototype_ `void RequestUpdateDetailsViews();` — Requests to update the Details Views on the next tick
- L38 _private prototype_ `void ForceUpdateDetailsViews();` — Updates the Details Views
- L41 _private prototype_ `void OnActiveTabChanged(TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated);` — Called when the active tab in the editor changes
- L44 _private prototype_ `bool IsWidgetInTab(TSharedPtr<SDockTab> InDockTab, TSharedPtr<SWidget> InWidget) const;` — Searches this widget's parents to see if it's a child of InDockTab
- L47 _private member_ `bool bThrottleDisabled = false;` — True if slate throttling is currently disabled
- L50 _private member_ `FDelegateHandle OnActiveTabChangedDelegateHandle;` — Delegate handle bound to the FGlobalTabmanager::OnActiveTabChanged delegate
- L53 _private member_ `FTimerHandle UpdateDetailsViewTimerHandle;` — Timer handle in use while updating details views is requested but not carried out yet
- L56 _private member_ `TSharedPtr<IDetailsView> FaderGroupControllersDetailsView;` — Shows details of the current selected Fader Group Controllers
- L59 _private member_ `TSharedPtr<IDetailsView> FaderGroupsDetailsView;` — Shows details of the current selected Fader Groups
- L62 _private member_ `TSharedPtr<IDetailsView> ElementControllersDetailsView;` — Shows details of the current selected Element Controllers
- L65 _private member_ `TSharedPtr<IDetailsView> FadersDetailsView;` — Shows details of the current selected Faders
- L68 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMX` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorElementControllerView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorElementControllerView`  
`class SDMXControlConsoleEditorElementControllerView : public SCompoundWidget`  
_L21-137_
- inherits: `SCompoundWidget`
- desc: Individual element controller UI class
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorElementControllerView)`
- L28 _public prototype_ `SLATE_ARGUMENT(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXControlConsoleElementControllerModel>& InElementControllerModel, UDMXControlConsoleEditorModel* InEditorModel);`
- L36 _public prototype_ `UDMXControlConsoleElementController* GetElementController() const;` — Gets the element controller this view is based on
- L40 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _private prototype_ `TSharedRef<SWidget> GenerateLockButtonWidget();` — Generates the lock button widget
- L49 _private prototype_ `TSharedRef<SWidget> GenerateElementControllerContextMenuWidget();` — Generates a context menu widget for element controller options
- L52 _private prototype_ `bool IsSelected() const;` — True if the element controller is selected
- L55 _private prototype_ `FString GetElementControllerName() const;` — Gets the element controller name
- L58 _private prototype_ `FText GetElementControllerNameText() const;` — Gets the current element controller name as text
- L61 _private prototype_ `FText GetValueAsText() const;` — Returns the element controller value as text
- L64 _private prototype_ `void OnValueTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Called when a new text on value editable text box is committed
- L67 _private prototype_ `TOptional<float> GetMinValue() const;` — Gets the element controller minimum value
- L70 _private prototype_ `FText GetMinValueAsText() const;` — Returns the element controller minimum value as text
- L73 _private prototype_ `void OnMinValueTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Called when a new text on minimum value editable text box is committed
- L76 _private prototype_ `TOptional<float> GetMaxValue() const;` — Gets the element controller maximum value
- L79 _private prototype_ `FText GetMaxValueAsText() const;` — Returns the element controller maximum value as text
- L82 _private prototype_ `void OnMaxValueTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Called when a new text on maximum value editable text box is committed
- L85 _private prototype_ `FText GetPhysicalUnitNameLabelText() const;` — Returns the physical unit name label as text
- L88 _private prototype_ `void OnEnableElementController(bool bEnable) const;` — Called when the enable option is selected
- L91 _private prototype_ `void OnRemoveElementController() const;` — Called when the remove option is selected
- L94 _private prototype_ `void OnResetElementController() const;` — Called when the reset option is selected
- L97 _private prototype_ `void OnLockElementController(bool bLock) const;` — Called when the lock option is selected
- L100 _private prototype_ `FReply OnLockClicked();` — Called to lock/unlock this element controller
- L103 _private prototype_ `ECheckBoxState IsEnableChecked() const;` — Checks the current enable state of the element controller
- L106 _private prototype_ `void OnEnableToggleChanged(ECheckBoxState CheckState);` — Called to toggle the enable state of this element controller
- L109 _private prototype_ `FOptionalSize GetElementControllerHeightByViewMode() const;` — Gets the height of the element controller according to the current view mode
- L112 _private prototype_ `FSlateColor GetLockButtonColor() const;` — Gets the correct text for the lock button
- L115 _private prototype_ `EVisibility GetExpandedViewModeVisibility() const;` — Gets the visibility for the toolbar sections only visible in expanded view mode
- L118 _private prototype_ `EVisibility GetLockButtonVisibility() const;` — Gets the visibility for the lock button
- L121 _private prototype_ `EVisibility GetPhysicalUnitLabelVisibility() const;` — Gets the visibility for the physical unit label text
- L124 _private prototype_ `const FSlateBrush* GetBorderImage() const;` — Changes the element controller background color on hover
- L127 _private member_ `TSharedPtr<SButton> LockButton;` — Reference to the lock button widget
- L130 _private member_ `TSharedPtr<SDMXControlConsoleEditorSpinBoxController> SpinBoxControllerWidget;` — Reference to the spin box controller widget
- L133 _private member_ `TSharedPtr<FDMXControlConsoleElementControllerModel> ElementControllerModel;` — Reference to the element controller being displayed
- L136 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the control console editor model

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMX` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorFaderGroupControllerView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorFaderGroupControllerView`  
`class SDMXControlConsoleEditorFaderGroupControllerView : public SCompoundWidget`  
_L25-145_
- inherits: `SCompoundWidget`
- desc: A widget which displays a collection of Element Controllers
- L29 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFaderGroupControllerView)`
- L35 _public prototype_ `SDMXControlConsoleEditorFaderGroupControllerView();` — Constructor
- L38 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FDMXControlConsoleFaderGroupControllerModel>& InFaderGroupControllerModel, UDMXControlConsoleEditorModel* InEditorModel);` — Constructs the widget
- L41 _public prototype_ `UDMXControlConsoleFaderGroupController* GetFaderGroupController() const;` — Gets the Fader Group Controller this view is based on
- L44 _public function_ `EDMXControlConsoleEditorViewMode GetViewMode() const` — Gets current ViewMode
- L48 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L49 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L54 _private prototype_ `TSharedRef<SWidget> GenerateElementControllersWidget();` — Generates ElementControllersHorizontalBox widget
- L57 _private prototype_ `bool IsSelected() const;` — Gets wheter this Fader Group Controller is selected or not
- L60 _private prototype_ `TSharedPtr<SDMXControlConsoleEditorExpandArrowButton> GetExpandArrowButton() const;` — Gets a reference to the toolbar's ExpandArrow button
- L63 _private prototype_ `void OnElementControllerAdded();` — Should be called when an Element Controller was added to the Fader Group Controller this view displays
- L66 _private prototype_ `void AddElementController(UDMXControlConsoleElementController* ElementController);` — Adds an Element Controller slot widget
- L69 _private prototype_ `void OnElementControllerRemoved();` — Should be called when an Element Controller was deleted from the Fader Group Controller this view displays
- L72 _private prototype_ `bool ContainsElementController(const UDMXControlConsoleElementController* InElementController) const;` — Checks if ElementControllers array contains a reference to the given Element Controller
- L75 _private prototype_ `void UpdateExpansionState();` — Updates this widget to the last saved expansion state from the model
- L78 _private prototype_ `void OnExpandArrowClicked(bool bExpand);` — Called when the Expand Arrow button is clicked
- L81 _private prototype_ `void OnFaderGroupControllerGrouped();` — Called when the Fader Group Controller gets grouped
- L84 _private prototype_ `void OnFaderGroupControllerFixturePatchChanged();` — Called when the Fixture Patch of a Fader Group in the Controller has changed
- L87 _private prototype_ `FReply OnAddElementControllerClicked();` — Notifies this Fader Group Controller to add a new Element Controller
- L90 _private prototype_ `void OnViewModeChanged();` — Called when Fader Groups view mode is changed
- L93 _private prototype_ `bool IsCurrentViewMode(EDMXControlConsoleEditorViewMode InViewMode) const;` — True if the given View Mode matches the current one
- L96 _private prototype_ `FOptionalSize GetFaderGroupControllerViewHeightByFadersViewMode() const;` — Gets the height of this view according to the current Faders View Mode
- L99 _private prototype_ `FSlateColor GetFaderGroupControllerViewBorderColor() const;` — Gets the border color of this view
- L102 _private prototype_ `const FSlateBrush* GetFaderGroupControllerViewBorderImage() const;` — Changes the brush when this widget is hovered
- L105 _private prototype_ `const FSlateBrush* GetFaderGroupControllerViewBackgroundBorderImage() const;` — Changes the background brush when this widget is hovered
- L108 _private prototype_ `EVisibility GetViewModeVisibility(EDMXControlConsoleEditorViewMode InViewMode) const;` — Gets the visibility of this view according to the given View Mode
- L111 _private prototype_ `EVisibility GetElementControllerWidgetVisibility(TSharedPtr<FDMXControlConsoleElementControllerModel> ElementControllerModel) const;` — Gets the visibility for each Element Controller widget in this view
- L114 _private prototype_ `EVisibility GetAddButtonVisibility() const;` — Gets the visibility of the horizontal Add Button widget
- L117 _private prototype_ `EVisibility GetAddRowButtonVisibility() const;` — Gets the visibility of the vertical Add Button widget
- L120 _private prototype_ `EVisibility GetElementControllersHorizontalBoxVisibility() const;` — Gets the visibility of the ElementControllersHorizontalBox widget
- L123 _private prototype_ `EVisibility GetAddElementControllerButtonVisibility() const;` — Gets the visibility of the add element controller button
- L126 _private prototype_ `EVisibility GetGroupColorTagImageVisibility() const;` — Gets the visibility of the group color tag image
- L129 _private member_ `EDMXControlConsoleEditorViewMode ViewMode;` — Current view mode
- L132 _private member_ `TSharedPtr<SDMXControlConsoleEditorFaderGroupControllerToolbar> FaderGroupControllerToolbar;` — Reference to the toolbar widget for this view
- L135 _private member_ `TSharedPtr<SHorizontalBox> ElementControllersHorizontalBox;` — Horizontal Box containing the Element Controllers in this Fader Group Controller
- L138 _private member_ `TArray<TWeakPtr<SWidget>> ElementControllerWidgets;` — Array of weak references to Element Controller widgets
- L141 _private member_ `TSharedPtr<FDMXControlConsoleFaderGroupControllerModel> FaderGroupControllerModel;` — Reference to the Fader Group Controller model this view is based on
- L144 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DMX` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorFiltersView.h` (Private)


#### enum `UE::DMX::Private::EDMXControlConsoleFilterCategory`  
`enum class EDMXControlConsoleFilterCategory : uint8`  
_L18-24_
- desc: Enum for DMX Control Console filter categories
- L20 _public enumerator_ `User`
- L21 _public enumerator_ `AttributeName`
- L22 _public enumerator_ `UniverseID`
- L23 _public enumerator_ `FixtureID`

#### class `UE::DMX::Private::SDMXControlConsoleEditorFiltersView`  
`class SDMXControlConsoleEditorFiltersView : public SCompoundWidget`  
_L27-90_
- inherits: `SCompoundWidget`
- desc: View for displaying the filters collection of a DMX Control Console
- L31 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFiltersView)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXControlConsoleEditorToolbar> EditorToolbar, UDMXControlConsoleEditorModel* InEditorModel);`
- L41 _private prototype_ `void RequestRefresh();` — Requests the refreshing of the filters view
- L44 _private prototype_ `void UpdateFilterButtons();` — Updates all the filter models based on the Control Console Editor Data
- L47 _private prototype_ `void UpdateUserFilterButtons();` — Updates the user filter models based on the Control Console Editor Data
- L50 _private prototype_ `void UpdateAttributeNameFilterButtons();` — Updates the attribute name filter models based on the Control Console Editor Data
- L53 _private prototype_ `void UpdateUniverseIDFilterButtons();` — Updates the universe ID filter models based on the Control Console Editor Data
- L56 _private prototype_ `void UpdateFixtureIDFilterButtons();` — Updates the fixture ID filter models based on the Control Console Editor Data
- L59 _private prototype_ `void OnFilterStateChanged(TSharedPtr<FDMXControlConsoleFilterModel> FilterModel);` — Called whenever the state of a filter has changed
- L62 _private prototype_ `void OnDisableAllFilters();` — Called to disable all filters
- L65 _private prototype_ `void OnSetFiltersBoxVisibility(bool bIsNotVisible, EDMXControlConsoleFilterCategory FilterCategory);` — Sets the visibility of a filters box, depending on the given filter category
- L68 _private member_ `FTimerHandle RefreshFiltersViewTimerHandle;` — Timer handle in use while refreshing the filters view is requested but not carried out yet
- L71 _private member_ `TSharedPtr<SWrapBox> UserFiltersBox;` — Container box widget for the User filters
- L74 _private member_ `TSharedPtr<SWrapBox> AttributeNameFiltersBox;` — Container box widget for the Attribute Name filters
- L77 _private member_ `TSharedPtr<SWrapBox> UniverseIDFiltersBox;` — Container box widget for the Universe ID filters
- L80 _private member_ `TSharedPtr<SWrapBox> FixtureIDFiltersBox;` — Container box widget for the Fixture ID filters
- L83 _private member_ `TArray<TSharedPtr<FDMXControlConsoleFilterModel>> FilterModels;` — The array of models used to describe all the filters in the Control Console
- L86 _private member_ `TWeakPtr<FDMXControlConsoleEditorToolbar> WeakToolbarPtr;` — Weak reference to the editor Toolbar
- L89 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console Editor Model

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorLayoutRowView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorLayoutRowView`  
`class SDMXControlConsoleEditorLayoutRowView : public SCompoundWidget`  
_L20-73_
- inherits: `SCompoundWidget`
- desc: A widget which displays a collection of Fader Group Controllers
- L24 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorLayoutRowView)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorGlobalLayoutRow* InLayoutRow, UDMXControlConsoleEditorModel* InEditorModel);`
- L33 _public function_ `UDMXControlConsoleEditorGlobalLayoutRow* GetLayoutRow() const` — Gets the Layout Row this row is based on
- L36 _public prototype_ `TSharedPtr<SDMXControlConsoleEditorFaderGroupControllerView> FindFaderGroupControllerView(const UDMXControlConsoleFaderGroupController* FaderGroupController) const;` — Finds the matching Fader Group Controller view by the given Fader Group Controller, if valid
- L40 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L45 _private prototype_ `void Refresh();` — Refreshes layout row
- L48 _private prototype_ `void OnFaderGroupControllerAdded();` — Should be called when a Fader Group Controller was added to the Layout Row this view displays
- L51 _private prototype_ `void AddFaderGroupController(UDMXControlConsoleFaderGroupController* FaderGroupController);` — Adds a Fader Group Controller slot widget
- L54 _private prototype_ `void OnFaderGroupControllerRemoved();` — Should be called when a Fader Group Controller was deleted from the Layout Row this view displays
- L57 _private prototype_ `bool ContainsFaderGroupController(const UDMXControlConsoleFaderGroupController* FaderGroupController);` — Checks if the FaderGroupControllerViews array contains a reference to the given Fader Group Controller
- L60 _private prototype_ `EVisibility GetFaderGroupControllerViewVisibility(TSharedPtr<FDMXControlConsoleFaderGroupControllerModel> FaderGroupControllerModel) const;` — Gets visibility for each Fader Group Controller view in this row
- L63 _private member_ `TSharedPtr<SHorizontalBox> FaderGroupControllersHorizontalBox;` — Reference to the container widget of this Layout Row's Fader Group Controller slots
- L66 _private member_ `TArray<TWeakPtr<SDMXControlConsoleEditorFaderGroupControllerView>> FaderGroupControllerViews;` — Array of weak references to Fader Group Controller views
- L69 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutRow> LayoutRow;` — Weak Reference to this Layout Row
- L72 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMX` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorLayoutView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorLayoutView`  
`class SDMXControlConsoleEditorLayoutView : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L18-62_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: View for displaying layouts for the edited Control Console
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorLayoutView)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorModel* InEditorModel);`
- L33 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L34 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L35 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L39 _protected prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L40 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L41 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L46 _private prototype_ `void UpdateLayout();` — Updates Control Console layout, according to current layout mode
- L49 _private prototype_ `bool IsCurrentLayoutWidgetType(const FName& InWidgetTypeName) const;` — True if the current layout widget's type name matches the given one
- L52 _private prototype_ `void OnActiveLayoutChanged(const UDMXControlConsoleEditorGlobalLayoutBase* ActiveLayout);` — Called when the current Active Layout has changed
- L55 _private member_ `TSharedPtr<SDMXControlConsoleEditorLayout> Layout;` — Reference to the current layout widget
- L58 _private member_ `TSharedPtr<SHorizontalBox> LayoutBox;` — Reference to the layout container box
- L61 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Views/SDMXControlConsoleEditorMatrixCellControllerView.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorMatrixCellControllerView`  
`class SDMXControlConsoleEditorMatrixCellControllerView : public SCompoundWidget`  
_L23-101_
- inherits: `SCompoundWidget`
- desc: A widget which displays a collection of Cell Attribute Controllers
- L27 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorMatrixCellControllerView)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXControlConsoleElementControllerModel>& InElementControllerModel, UDMXControlConsoleEditorModel* InEditorModel);`
- L36 _public prototype_ `UDMXControlConsoleMatrixCellController* GetMatrixCellController() const;` — Gets the Matrix Cell Controller this widget is based on
- L39 _public prototype_ `UDMXControlConsoleFixturePatchMatrixCell* GetMatrixCell() const;` — Gets a reference to the Matrix Cell showed by this widget
- L42 _public function_ `TSharedPtr<SDMXControlConsoleEditorExpandArrowButton>& GetExpandArrowButton()` — Gets a reference to this widget's ExpandArrow button
- L46 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L47 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L52 _private prototype_ `void OnCellAttributeControllerAdded();` — Should be called when a Cell Attribute Controller was added to the Matrix Cell Controller this widget displays
- L55 _private prototype_ `void AddCellAttributeController(UDMXControlConsoleCellAttributeController* CellAttributeController);` — Adds a Cell Attribute Controller slot widget
- L58 _private prototype_ `void OnCellAttributeControllerRemoved();` — Should be called when a Cell Attribute Controller was deleted from the Matrix Cell Controller this widget displays
- L61 _private prototype_ `bool ContainsCellAttributeController(UDMXControlConsoleCellAttributeController* CellAttributeController);` — Checks if the Cell Attribute Controllers array contains a reference to the given Cell Attribute Controller
- L64 _private prototype_ `bool IsAnyCellAttributeControllerSelected() const;` — Returns true if any of the Cell Attribute Controllers in the Matrix Cell Controller is selected
- L67 _private prototype_ `void OnEditorModelUpdated();` — Called when the editor model is updated
- L70 _private prototype_ `FOptionalSize GetMatrixCellControllerHeightByFadersViewMode() const;` — Gets the height of the Matrix Cell Controller according to the current Faders View Mode
- L73 _private prototype_ `FText GetMatrixCellLabelText() const;` — Gets the Matrix Cell ID as text
- L76 _private prototype_ `FSlateColor GetLabelBorderColor() const;` — Gets the label background color
- L79 _private prototype_ `EVisibility GetCellAttributeControllerWidgetVisibility(TSharedPtr<FDMXControlConsoleElementControllerModel> ControllerModel) const;` — Gets the visibility for each Cell Attribute Controller widget in this view
- L82 _private prototype_ `EVisibility GetCellAttributeControllersHorizontalBoxVisibility() const;` — Gets the visibility of the CellAttributeControllersHorizontalBox widget
- L85 _private prototype_ `const FSlateBrush* GetBorderImage() const;` — Gets the widget border brush
- L88 _private member_ `TSharedPtr<SHorizontalBox> CellAttributeControllersHorizontalBox;` — Reference to the Cell Attribute Controllers main widget
- L91 _private member_ `TArray<TWeakPtr<SDMXControlConsoleEditorElementControllerView>> CellAttributeControllerViews;` — Array of Cell Attribute Controllers views
- L94 _private member_ `TSharedPtr<SDMXControlConsoleEditorExpandArrowButton> ExpandArrowButton;` — Reference to the ExpandArrow button used to show/hide the Cell Attribute Controllers
- L97 _private member_ `TSharedPtr<FDMXControlConsoleElementControllerModel> MatrixCellControllerModel;` — Reference to the Matrix Cell Controller being displayed
- L100 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleAddEmptyFaderGroupMenu.h` (Private)


#### class `SDMXControlConsoleAddEmptyFaderGroupMenu`  
`class SDMXControlConsoleAddEmptyFaderGroupMenu : public SCompoundWidget`  
_L13-49_
- inherits: `SCompoundWidget`
- desc: A menu to add empty fader groups to the control console.
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleAddEmptyFaderGroupMenu)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorModel* InEditorModel);`
- L27 _private prototype_ `void RegisterCommands();` — Registers commands for the menu
- L30 _private prototype_ `bool CanAddEmptyToTheRight() const;` — Returns true if the 'add empty to right' option is avialable
- L33 _private prototype_ `void AddEmptyToTheRight();` — Adds an empty fader group to the right
- L36 _private prototype_ `bool CanAddEmptyOnNewRow() const;` — Returns true if the 'add empty on a new row' option is avialable
- L39 _private prototype_ `void AddEmptyOnNewRow();` — Adds an empty fader group on a new row
- L42 _private prototype_ `UDMXControlConsoleFaderGroup* AddEmptyFaderGroup() const;` — Adds an empty fader group to the Control Console
- L45 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for this widget
- L48 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleAddFixturePatchMenu.h` (Private)


#### class `SDMXControlConsoleAddFixturePatchMenu`  
`class SDMXControlConsoleAddFixturePatchMenu : public SCompoundWidget`  
_L17-77_
- inherits: `SCompoundWidget`
- desc: A menu to add fixture patches to the control console. Construct or use SetFixturePatches to specify the patches to add.
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleAddFixturePatchMenu)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TArray<TWeakObjectPtr<UDMXEntityFixturePatch>> InFixturePatches, UDMXControlConsoleEditorModel* InEditorModel);`
- L30 _public prototype_ `void SetFixturePatches(TArray<TWeakObjectPtr<UDMXEntityFixturePatch>> FixturePatches);` — Sets the fixture patches which can be added from this widget
- L34 _private prototype_ `void RegisterCommands();` — Registers commands for the menu
- L37 _private prototype_ `bool CanAddPatchesToTheRight() const;` — Returns true if the 'add patches to right' option is avialable
- L40 _private prototype_ `void AddPatchesToTheRight();` — Adds patches as fixture groups to the right
- L43 _private prototype_ `bool CanAddPatchesOnNewRow() const;` — Returns true if the 'add patches on a new row' option is avialable
- L46 _private prototype_ `void AddPatchesOnNewRow();` — Adds patches as fixture groups on a new row
- L49 _private prototype_ `bool CanSetPatchOnFaderGroup() const;` — Returns true if the 'set patch on fader group' option is avialable
- L52 _private prototype_ `void SetPatchOnFaderGroup();` — Sets the fixture patch on the selected fader group
- L55 _private prototype_ `void GroupPatchesToTheRight();` — Groups patches in a fader group controller to the right
- L58 _private prototype_ `bool CanGroupPatchesToTheRight() const;` — Returns true if the 'group patches to right' option is avialable
- L61 _private prototype_ `void GroupPatchesOnNewRow();` — Groups patches in a fader group controller on a new row
- L64 _private prototype_ `bool CanGroupPatchesOnNewRow() const;` — Returns true if the 'group patches on a new row' option is avialable
- L67 _private prototype_ `TArray<UDMXControlConsoleFaderGroup*> GetFaderGroupsFromFixturePatches();` — Gets all available fader groups according to the current selected fixture patches
- L70 _private member_ `TArray<TWeakObjectPtr<UDMXEntityFixturePatch>> FixturePatches;` — Fixture patches available when adding from this menu
- L73 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for this widget
- L76 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorAddButton.h` (Private)


#### class `SDMXControlConsoleEditorAddButton`  
`class SDMXControlConsoleEditorAddButton : public SCompoundWidget`  
_L13-33_
- inherits: `SCompoundWidget`
- desc: A button widget used by DMX Control Console View to manage Fader Groups creation
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorAddButton)`
- L20 _public prototype_ `SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Called when this widget's button is clicked
- L29 _private prototype_ `FSlateColor GetButtonColor() const;` — Manages this widget's button color, according to its hovering state
- L32 _private member_ `FOnClicked OnClicked;` — The delegate to excecute when this widget's button is clicked

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorCueList.h` (Private)


#### struct `UE::DMX::Private::FDMXControlConsoleEditorCueListColumnIDs`  
`struct FDMXControlConsoleEditorCueListColumnIDs`  
_L23-29_
- desc: Collumn ids in the cue list
- L25 _public member_ `static const FName Color;`
- L26 _public member_ `static const FName State;`
- L27 _public member_ `static const FName Name;`
- L28 _public member_ `static const FName Options;`

#### class `UE::DMX::Private::FDMXControlConsoleEditorCueListItem`  
`class FDMXControlConsoleEditorCueListItem : public TSharedFromThis<FDMXControlConsoleEditorCueListItem>`  
_L32-57_
- inherits: `TSharedFromThis<FDMXControlConsoleEditorCueListItem>`
- desc: An item in the Control Console cue list
- L37 _public prototype_ `FDMXControlConsoleEditorCueListItem(const FDMXControlConsoleCue& InCue);` — Constructor
- L40 _public function_ `FDMXControlConsoleCue GetCue() const` — Returns the cue this item uses
- L43 _public prototype_ `FText GetCueNameText() const;` — Returns the name label of the cue this item uses, as text
- L46 _public prototype_ `void SetCueName(const FString& CueLabel);` — Sets the name label of the cue this item uses
- L49 _public prototype_ `FSlateColor GetCueColor() const;` — Returns the color of the cue this item uses
- L52 _public prototype_ `void SetCueColor(const FLinearColor CueColor);` — Sets the color of the cue this item uses
- L56 _private member_ `FDMXControlConsoleCue Cue;` — The cue this item is based on

#### class `UE::DMX::Private::FDMXControlConsoleEditorCueListDragDropOp`  
`class FDMXControlConsoleEditorCueListDragDropOp : public FDecoratedDragDropOp`  
_L60-74_
- inherits: `FDecoratedDragDropOp`
- desc: This drag drop operation allows cues from the cue stack to be rearranged
- L63 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMXControlConsoleEditorCueListDragDropOp, FDecoratedDragDropOp) static TSharedRef<FDMXControlConsoleEditorCueListDragDropOp> New(TWeakPtr<FDMXControlConsoleEditorCueListItem> InItem);`
- L69 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L73 _public member_ `TWeakPtr<FDMXControlConsoleEditorCueListItem> CueItem;` — The item dragged by this operation

#### class `UE::DMX::Private::SDMXControlConsoleEditorCueList`  
`class SDMXControlConsoleEditorCueList : public SCompoundWidget`  
_L77-143_
- inherits: `SCompoundWidget`
- desc: List of Cues in a DMX Control Console
- L81 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorCueList)`
- L84 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FDMXControlConsoleCueStackModel> InCueStackModel);`
- L90 _public prototype_ `TArray<TSharedPtr<FDMXControlConsoleEditorCueListItem>> GetSelectedCueItems() const;` — Gets the array of current selected cue items
- L93 _public prototype_ `void RequestRefresh();` — Requests the refresh of the list
- L97 _private prototype_ `void UpdateCueListItems();` — Updates the array of Cue List Items
- L100 _private prototype_ `TSharedRef<SHeaderRow> GenerateHeaderRow();` — Called to generate the header row of the list
- L103 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXControlConsoleEditorCueListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called to generate a row in the list
- L106 _private prototype_ `void OnSelectionChanged(const TSharedPtr<FDMXControlConsoleEditorCueListItem> NewSelection, ESelectInfo::Type SelectInfo);` — Called when selection in the list changed
- L109 _private prototype_ `void OnRowDoubleClicked(const TSharedPtr<FDMXControlConsoleEditorCueListItem> ItemClicked);` — Called when a row was double clicked
- L112 _private prototype_ `FReply OnRowDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when a row in the list was dragged
- L115 _private prototype_ `TOptional<EItemDropZone> OnRowCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDMXControlConsoleEditorCueListItem> TargetItem);` — Called when the row drop operation needs to be accepted
- L118 _private prototype_ `FReply OnRowAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDMXControlConsoleEditorCueListItem> TargetItem);` — Called when the row drop operation is accepted
- L121 _private prototype_ `void OnEditCueItemColor(TSharedPtr<FDMXControlConsoleEditorCueListItem> InItem);` — Called when the color of an item in the list is changed
- L124 _private prototype_ `void OnRenameCueItem(TSharedPtr<FDMXControlConsoleEditorCueListItem> InItem);` — Called when the name label of an item in the list is changed
- L127 _private prototype_ `void OnMoveCueItem(TSharedPtr<FDMXControlConsoleEditorCueListItem> InItem, EItemDropZone DropZone);` — Called when an item in the list is deleted
- L130 _private prototype_ `void OnDeleteCueItem(TSharedPtr<FDMXControlConsoleEditorCueListItem> InItem);` — Called when an item in the list is deleted
- L133 _private member_ `TSharedPtr<SListView<TSharedPtr<FDMXControlConsoleEditorCueListItem>>> CueListView;` — Reference to the Cue List View widget
- L136 _private member_ `TArray<TSharedPtr<FDMXControlConsoleEditorCueListItem>> CueListItems;` — The array of Cue List Items this list is based on
- L139 _private member_ `FDMXControlConsoleCue LastSelectedCue;` — The last selected control console cue
- L142 _private member_ `TWeakPtr<FDMXControlConsoleCueStackModel> WeakCueStackModel;` — Weak reference to the Control Console Cue Stack Model

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DMX` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorCueListRow.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorCueListRow`  
`class SDMXControlConsoleEditorCueListRow : public SMultiColumnTableRow<TSharedPtr<FDMXControlConsoleEditorCueListItem>>`  
_L23-121_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXControlConsoleEditorCueListItem>>`
- desc: A Control Console Cue as a row in a list
- L27 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorCueListRow)`
- L31 _public prototype_ `SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnEditCueItemColor) SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnRenameCueItem) SLATE_EVENT(FDMXControleConsolEditorMoveCueListItemDelegate, OnMoveCueItem) SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnDeleteCueItem) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_EVENT(FOnCanAcceptDrop, OnCanAcceptDrop) SLATE_EVENT(FOnAcceptDrop, OnAcceptDrop) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedRef<FDMXControlConsoleEditorCueListItem>& InItem, TSharedPtr<FDMXControlConsoleCueStackModel> InCueStackModel);` — Executed when the color of a cue list item is edited
- L58 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L63 _private prototype_ `TSharedRef<SWidget> GenerateCueColorRow();` — Generates the row that displays the color of the Cue
- L66 _private prototype_ `TSharedRef<SWidget> GenerateCueStateRow();` — Generates the row that displays the recall state of the Cue
- L69 _private prototype_ `TSharedRef<SWidget> GenerateCueNameRow();` — Generates the row that displays the name label of the Cue
- L72 _private prototype_ `TSharedRef<SWidget> GenerateCueOptionsRow();` — Generates the row that displays the edit options for the Cue
- L75 _private prototype_ `TSharedRef<SWidget> GenerateRowOptionButtonWidget(const FSlateBrush* IconBrush, FOnClicked OnClicked);` — Generates a row option button with the given parameters
- L78 _private prototype_ `FReply OnCueColorMouseButtonClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the color section of this row is clicked
- L81 _private prototype_ `void OnSetCueColorFromColorPicker(FLinearColor NewColor);` — Called when the color picker value is committed
- L84 _private prototype_ `FText GetCueNameAsText() const;` — Gets the current cue name as text
- L87 _private prototype_ `void OnCueNameTextCommitted(const FText& NewName, ETextCommit::Type InCommit);` — Called when the text in the cue name text box is committed
- L90 _private prototype_ `void OnEnterCueLabelTextBlockEditMode();` — Called to enter the edit mode of the cue label text block
- L93 _private prototype_ `FReply OnRenameItemClicked();` — Called when the rename button is clicked
- L96 _private prototype_ `FReply OnMoveItemClicked(EItemDropZone DropZone);` — Called when the move button is clicked
- L99 _private prototype_ `FReply OnDeleteItemClicked();` — Called when the delete button is clicked
- L102 _private prototype_ `EVisibility GetRecalledCueTagVisibility() const;` — Gets the visibility of the recalled cue tag
- L105 _private member_ `FTimerHandle EnterCueLabelTextBlockEditModeTimerHandle;` — Timer handle in use while entering cue label edit mode is requested but not carried out yet
- L108 _private member_ `TSharedPtr<SInlineEditableTextBlock> CueLabelEditableTextBlock;` — The editable text block that shows the name label of the cue item this row is based on
- L111 _private member_ `TSharedPtr<FDMXControlConsoleEditorCueListItem> Item;` — The item this widget draws
- L114 _private member_ `TWeakPtr<FDMXControlConsoleCueStackModel> WeakCueStackModel;` — Weak reference to the Control Console Cue Stack Model
- L117 _private member_ `FDMXControleConsolEditorCueListItemDelegate OnEditCueItemColorDelegate;` — Slate Arguments
- L118 _private member_ `FDMXControleConsolEditorCueListItemDelegate OnRenameCueItemDelegate;`
- L119 _private member_ `FDMXControleConsolEditorMoveCueListItemDelegate OnMoveCueItemDelegate;`
- L120 _private member_ `FDMXControleConsolEditorCueListItemDelegate OnDeleteCueItemDelegate;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMX` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::DMX`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FDMXControleConsolEditorCueListItemDelegate, TSharedPtr<FDMXControlConsoleEditorCueListItem>) DECLARE_DELEGATE_TwoParams(FDMXControleConsolEditorMoveCueListItemDelegate, TSharedPtr<FDMXControlConsoleEditorCueListItem>, EItemDropZone) class SDMXControlConsoleEditorCueListRow : public SMultiColumnTableRow<TSharedPtr<FDMXControlConsoleEditorCueListItem>> { public: SLATE_BEGIN_ARGS(SDMXControlConsoleEditorCueListRow) {} SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnEditCueItemColor) SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnRenameCueItem) SLATE_EVENT(FDMXControleConsolEditorMoveCueListItemDelegate, OnMoveCueItem) SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnDeleteCueItem) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_EVENT(FOnCanAcceptDrop, OnCanAcceptDrop) SLATE_EVENT(FOnAcceptDrop, OnAcceptDrop) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedRef<FDMXControlConsoleEditorCueListItem>& InItem, TSharedPtr<FDMXControlConsoleCueStackModel> InCueStackModel); protected:`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FDMXControleConsolEditorMoveCueListItemDelegate, TSharedPtr<FDMXControlConsoleEditorCueListItem>, EItemDropZone) class SDMXControlConsoleEditorCueListRow : public SMultiColumnTableRow<TSharedPtr<FDMXControlConsoleEditorCueListItem>> { public: SLATE_BEGIN_ARGS(SDMXControlConsoleEditorCueListRow) {} SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnEditCueItemColor) SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnRenameCueItem) SLATE_EVENT(FDMXControleConsolEditorMoveCueListItemDelegate, OnMoveCueItem) SLATE_EVENT(FDMXControleConsolEditorCueListItemDelegate, OnDeleteCueItem) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_EVENT(FOnCanAcceptDrop, OnCanAcceptDrop) SLATE_EVENT(FOnAcceptDrop, OnAcceptDrop) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedRef<FDMXControlConsoleEditorCueListItem>& InItem, TSharedPtr<FDMXControlConsoleCueStackModel> InCueStackModel); protected:`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorCueStackComboBox.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorCueStackComboBox`  
`class SDMXControlConsoleEditorCueStackComboBox : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L18-77_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: A combo box widget for selecting cues in the Control Console cue stack
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorCueStackComboBox)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FDMXControlConsoleCueStackModel> InCueStackModel);`
- L33 _protected prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L34 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L35 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L40 _private prototype_ `TSharedRef<SWidget> GenerateComboBoxContentWidget();` — Generates the content widget for the cue stack combo box
- L43 _private prototype_ `TSharedRef<SWidget> GenerateComboBoxOptionWidget(const TSharedPtr<FDMXControlConsoleEditorCueListItem> CueItem);` — Generates a widget for each element in the cue stack combo box
- L46 _private prototype_ `void UpdateCueStackComboBoxSource();` — Updates the array of combo box source items
- L49 _private prototype_ `void OnCueStackComboBoxSelectionChanged(const TSharedPtr<FDMXControlConsoleEditorCueListItem> NewSelection, ESelectInfo::Type SelectInfo);` — Called when selection in the combo box changed
- L52 _private prototype_ `bool IsAddNewCueButtonEnabled() const;` — True if there's at least one fader group in the current control console
- L55 _private prototype_ `bool IsStoreCueButtonEnabled() const;` — True if there's at least one selected cue item
- L58 _private prototype_ `FReply OnAddNewCueClicked();` — Called when the add new cue button is clicked
- L61 _private prototype_ `FReply OnStoreCueClicked();` — Called when the store cue button is clicked
- L64 _private prototype_ `FSlateColor GetLoadedCueColor() const;` — Gets the color of the loaded cue, if valid
- L67 _private prototype_ `FText GetLoadedCueNameAsText() const;` — Gets the name label of the loaded cue as text, if valid
- L70 _private member_ `TArray<TSharedPtr<FDMXControlConsoleEditorCueListItem>> ComboBoxSource;` — Source items for the CueStackComboBox
- L73 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FDMXControlConsoleEditorCueListItem>>> CueStackComboBox;` — A ComboBox for showing all the cues in the Control Console cue stack
- L76 _private member_ `TWeakPtr<FDMXControlConsoleCueStackModel> WeakCueStackModel;` — Weak reference to the Control Console Cue Stack Model

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorExpandArrowButton.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorExpandArrowButton`  
`class SDMXControlConsoleEditorExpandArrowButton : public SCompoundWidget`  
_L18-57_
- inherits: `SCompoundWidget`
- desc: A button widget used by DMX Control Console Views to expand/collapse widgets
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorExpandArrowButton) : _IsExpanded(true)`
- L26 _public prototype_ `SLATE_ARGUMENT(bool, IsExpanded) SLATE_EVENT(FDMXControleConsolEditorExpandArrowButtonDelegate, OnExpandClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — True if the button is in expand state
- L37 _public prototype_ `void SetExpandArrow(bool bExpand);` — Sets expand state of the button
- L40 _public prototype_ `void ToggleExpandArrow();` — Toggles the expand state of the button
- L43 _public function_ `bool IsExpanded() const` — Gets the button state
- L47 _private prototype_ `FReply OnExpandArrowClicked();` — Called when this widget's button is clicked
- L50 _private prototype_ `const FSlateBrush* GetExpandArrowImage() const;` — Gets brush for the Expander Arrow Button
- L53 _private member_ `bool bIsExpanded = true;` — True if the button is in expand state
- L56 _private member_ `FDMXControleConsolEditorExpandArrowButtonDelegate OnExpandClicked;` — The delegate to excecute when this widget's button is clicked

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FDMXControleConsolEditorExpandArrowButtonDelegate, bool) namespace UE::DMX::Private { class SDMXControlConsoleEditorExpandArrowButton : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SDMXControlConsoleEditorExpandArrowButton) : _IsExpanded(true) {} SLATE_ARGUMENT(bool, IsExpanded) SLATE_EVENT(FDMXControleConsolEditorExpandArrowButtonDelegate, OnExpandClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetExpandArrow(bool bExpand); void ToggleExpandArrow(); bool IsExpanded() const { return bIsExpanded; } private: FReply OnExpandArrowClicked(); const FSlateBrush* GetExpandArrowImage() const;` — Delegate invoked when a user needs to know current ExpandArrowButton expansion state.
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMX` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorFaderGroupControllerComboBox.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorFaderGroupControllerComboBox`  
`class SDMXControlConsoleEditorFaderGroupControllerComboBox : public SCompoundWidget`  
_L21-84_
- inherits: `SCompoundWidget`
- desc: Combo box widget for selecting fixture patches in the Fader Group Controller view toolbar
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFaderGroupControllerComboBox)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FDMXControlConsoleFaderGroupControllerModel>& InFaderGroupControllerModel, UDMXControlConsoleEditorModel* InEditorModel);`
- L35 _private prototype_ `UDMXControlConsoleFaderGroupController* GetFaderGroupController() const;` — Gets reference to the Fader Group Controller
- L38 _private prototype_ `TSharedRef<SWidget> GenerateFixturePatchesComboBoxWidget(const TSharedPtr<FDMXEntityFixturePatchRef> FixturePatchRef);` — Generates a widget for each element in the Fixture Patches Combo Box
- L41 _private prototype_ `bool IsFixturePatchStillAvailable(const UDMXEntityFixturePatch* InFixturePatch) const;` — True if the given Fixture Patch is not used by any other Fader Group Controller
- L44 _private prototype_ `void UpdateComboBoxSource();` — Updates the ComboBoxSource array according to the current DMX Library
- L47 _private prototype_ `void OnComboBoxSelectionChanged(const TSharedPtr<FDMXEntityFixturePatchRef> FixturePatchRef, ESelectInfo::Type SelectInfo);` — Called when a FixturePatchesComboBox element is selected
- L50 _private prototype_ `void OnComboBoxTextCommitted(const FText& NewName, ETextCommit::Type InCommit);` — Called when the text in the combo box text box is committed
- L53 _private prototype_ `FSlateColor GetFaderGroupControllerEditorColor() const;` — Gets the Fader Group Controller's editor color
- L56 _private prototype_ `FText GetFaderGroupControllerFixturePatchNameText() const;` — Gets the Fader Group Controller's fixture patch name as text, if valid
- L59 _private prototype_ `FText GetFaderGroupControllerUserNameText() const;` — Gets the Fader Group Controller user name as text
- L62 _private prototype_ `bool IsUserNameTextBoxReadOnly() const;` — True if the Fader Group Controller user name text box should be read only
- L65 _private prototype_ `EVisibility GetUserNameTextBoxVisibility() const;` — Gets the visibility for the Fader Group Controller user name text box
- L68 _private prototype_ `EVisibility GetComboBoxVisibility() const;` — Gets the visibility for the combo box image
- L71 _private member_ `TWeakObjectPtr<UDMXLibrary> DMXLibrary;` — Reference to the current DMX Library
- L74 _private member_ `TArray<TSharedPtr<FDMXEntityFixturePatchRef>> ComboBoxSource;` — Source items for the FixturePatchesComboBox
- L77 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FDMXEntityFixturePatchRef>>> FixturePatchesComboBox;` — A ComboBox for showing all active Fixture Patches in the current DMX Library
- L80 _private member_ `TWeakPtr<FDMXControlConsoleFaderGroupControllerModel> WeakFaderGroupControllerModel;` — Weak Reference to the Fader Group Controller model
- L83 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorFaderGroupControllerPanel.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorFaderGroupControllerPanel`  
`class SDMXControlConsoleEditorFaderGroupControllerPanel : public SCompoundWidget`  
_L16-52_
- inherits: `SCompoundWidget`
- desc: A widget to display an info panel for the Fader Group Controller view
- L20 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFaderGroupControllerPanel)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FDMXControlConsoleFaderGroupControllerModel>& InFaderGroupControllerModel);`
- L30 _private prototype_ `UDMXControlConsoleFaderGroupController* GetFaderGroupController() const;` — Gets reference to the Fader Group Controller
- L33 _private prototype_ `FText OnGetFaderGroupControllerNameText() const;` — Gets current FaderGroupControllerName
- L36 _private prototype_ `FText OnGetFaderGroupControllerFIDText() const;` — Gets current FID as text, if valid
- L39 _private prototype_ `FText OnGetFaderGroupControllerUniverseText() const;` — Gets current Universe ID range as text
- L42 _private prototype_ `FText OnGetFaderGroupControllerAddressText() const;` — Gets current Address range as text
- L45 _private prototype_ `void OnFaderGroupControllerNameCommitted(const FText& NewName, ETextCommit::Type InCommit);` — Called when the Fader Group Controller name changes
- L48 _private member_ `TSharedPtr<SEditableTextBox> FaderGroupControllerNameTextBox;` — Shows/Modifies Fader Group Controller Name
- L51 _private member_ `TWeakPtr<FDMXControlConsoleFaderGroupControllerModel> WeakFaderGroupControllerModel;` — Weak Reference to the Fader Group Controller model

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorFaderGroupControllerTag.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorFaderGroupControllerTag`  
`class SDMXControlConsoleEditorFaderGroupControllerTag : public SCompoundWidget`  
_L15-39_
- inherits: `SCompoundWidget`
- desc: A widget to display a color tag for the Fader Group Controller view
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFaderGroupControllerTag)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FDMXControlConsoleFaderGroupControllerModel>& InFaderGroupControllerModel);`
- L29 _private prototype_ `FSlateColor GetFaderGroupControllerEditorColor() const;` — Gets the fader group controller's editor color
- L32 _private prototype_ `EVisibility GetSingleSlotTagVisibility() const;` — Gets the visibility state for the single slot tag
- L35 _private prototype_ `EVisibility GetMultiSlotTagVisibility() const;` — Gets the visibility state for the multiple slot tag
- L38 _private member_ `TWeakPtr<FDMXControlConsoleFaderGroupControllerModel> WeakFaderGroupControllerModel;` — Weak Reference to the Fader Group Controller model

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorFaderGroupControllerToolbar.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorFaderGroupControllerToolbar`  
`class SDMXControlConsoleEditorFaderGroupControllerToolbar : public SCompoundWidget`  
_L19-116_
- inherits: `SCompoundWidget`
- desc: Toolbar widget for the Fader Group view
- L23 _public function_ `DECLARE_DELEGATE_RetVal(bool, FDMXFaderGroupControllerToolbarRetValDelegate) SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFaderGroupControllerToolbar)`
- L28 _public prototype_ `SLATE_EVENT(FDMXControleConsolEditorExpandArrowButtonDelegate, OnExpanded) SLATE_EVENT(FDMXFaderGroupControllerToolbarRetValDelegate, IsExpandedViewModeEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FDMXControlConsoleFaderGroupControllerModel>& InFaderGroupControllerModel, UDMXControlConsoleEditorModel* InEditorModel);` — Executed when the Fader Group Controller View is expanded
- L39 _public prototype_ `TSharedRef<SWidget> GenerateSettingsMenuWidget();` — Generates the Fader Group Controller settings menu widget content
- L42 _public function_ `TSharedPtr<SDMXControlConsoleEditorExpandArrowButton> GetExpandArrowButton() const` — Gets a reference to this widget's ExpandArrow button
- L46 _private prototype_ `UDMXControlConsoleFaderGroupController* GetFaderGroupController() const;` — Gets reference to the Fader Group Controller
- L49 _private prototype_ `TSharedRef<SWidget> GenerateFaderGroupControllerInfoMenuWidget();` — Generates a menu widget for the Fader Group Controller info panel
- L52 _private prototype_ `void RestoreFaderGroupControllerFilter();` — Restores the search filter text from the Fader Group Controller
- L55 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);` — Called when the search text changed
- L58 _private prototype_ `void OnGetInfoPanel();` — Called to generate the Fader Group Controller Info Panel
- L61 _private prototype_ `void OnSelectAllElementControllers() const;` — Called to select all Element Controllers in the Fader Group Controller
- L64 _private prototype_ `void OnDuplicateFaderGroupController() const;` — Called when the duplicate option is selected
- L67 _private prototype_ `bool CanDuplicateFaderGroupController() const;` — Gets wheter the duplicate option is allowed or not
- L70 _private prototype_ `void OnRemoveFaderGroupController() const;` — Called when the remove option is selected
- L73 _private prototype_ `bool CanRemoveFaderGroupController() const;` — Gets wheter the remove option is allowed or not
- L76 _private prototype_ `void OnGroupFaderGroupControllers() const;` — Called when the group option is selected
- L79 _private prototype_ `void OnUngroupFaderGroupControllers() const;` — Called when the ungroup option is selected
- L82 _private prototype_ `bool CanGroupFaderGroupControllers() const;` — Gets wheter the selected Fader Group Controllers can be grouped or not
- L85 _private prototype_ `bool CanUngroupFaderGroupControllers() const;` — Gets wheter the selected Fader Group Controllers can be ungrouped or not
- L88 _private prototype_ `void OnResetFaderGroupController() const;` — Called when the reset option is selected
- L91 _private prototype_ `void OnLockFaderGroupController(bool bLock) const;` — Called when the lock option is selected
- L94 _private prototype_ `EVisibility GetExpandedViewModeVisibility() const;` — Gets the visibility for the toolbar sections visible only in expanded view mode
- L97 _private prototype_ `EVisibility GetSearchBoxVisibility() const;` — Gets the visibility for the toolbar serch box
- L100 _private member_ `TSharedPtr<SDMXControlConsoleEditorExpandArrowButton> ExpandArrowButton;` — Expander arrow button for showing/hiding the Element Controller views
- L103 _private member_ `TSharedPtr<SFilterSearchBox> ToolbarSearchBox;` — Reference to the Fader Group Controller toolbar searchbox used for filtering
- L106 _private member_ `TSharedPtr<SDMXControlConsoleEditorFaderGroupControllerComboBox> ControllerComboBox;` — A ComboBox for showing all active Fixture Patches in the current DMX Library
- L109 _private member_ `TWeakPtr<FDMXControlConsoleFaderGroupControllerModel> WeakFaderGroupControllerModel;` — Weak Reference to the Fader Group Controller model
- L112 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model
- L115 _private member_ `FDMXFaderGroupControllerToolbarRetValDelegate IsExpandedViewModeEnabledDelegate;` — Slate Arguments

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FDMXFaderGroupControllerToolbarRetValDelegate) SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFaderGroupControllerToolbar) {} SLATE_EVENT(FDMXControleConsolEditorExpandArrowButtonDelegate, OnExpanded) SLATE_EVENT(FDMXFaderGroupControllerToolbarRetValDelegate, IsExpandedViewModeEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FDMXControlConsoleFaderGroupControllerModel>& InFaderGroupControllerModel, UDMXControlConsoleEditorModel* InEditorModel);`

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorFilterButton.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorFilterButton`  
`class SDMXControlConsoleEditorFilterButton : public SCompoundWidget`  
_L16-75_
- inherits: `SCompoundWidget`
- desc: A button widget to display a filter in a DMX Control Console
- L20 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFilterButton)`
- L24 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnDisableAllFilters) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXControlConsoleFilterModel>& InFilterModel);` — Called when the disable all filters action is performed
- L33 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _private prototype_ `TSharedRef<SWidget> GenerateFilterButtonMenuWidget();` — Generates a context menu widget for filter options
- L41 _private prototype_ `bool IsUserFilter() const;` — True if the filter displayed by this button is a user filter
- L44 _private prototype_ `bool IsFilterEnabled() const;` — True if the filter displayed by this button is enabled
- L47 _private prototype_ `void SetIsFilterEnabled(bool bEnable);` — Sets the enable state of the filter displayed by this button
- L50 _private prototype_ `FText GetFilterLabelAsText() const;` — Gets the label name of the filter displayed by this button as a text
- L53 _private prototype_ `FText GetFilterStringAsText() const;` — Gets the string associated to the filter displayed by this button as a text
- L56 _private prototype_ `FReply OnFilterButtonClicked();` — Called when this widget's button is clicked
- L59 _private prototype_ `void OnRemoveFilter() const;` — Called when the remove filter option is selected
- L62 _private prototype_ `void OnDisableAllFiltersButThis();` — Called when the disable all filters but this option is selected
- L65 _private prototype_ `void OnDisableAllFilters() const;` — Called when the disable all filters option is selected
- L68 _private prototype_ `FSlateColor GetFilterButtonColor() const;` — Gets the editor color of the filter displayed by this button depending on its current state
- L71 _private member_ `TWeakPtr<FDMXControlConsoleFilterModel> WeakFilterModel;` — Reference to the filter model this widget is based on
- L74 _private member_ `FSimpleDelegate OnDisableAllFiltersDelegate;` — The delegate to excecute when the disable all filters action is performed

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorFixturePatchVerticalBox.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorFixturePatchVerticalBox`  
`class SDMXControlConsoleEditorFixturePatchVerticalBox : public SCompoundWidget`  
_L16-63_
- inherits: `SCompoundWidget`
- desc: A container for the Fixture Patch List widget
- L20 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorFixturePatchVerticalBox)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorModel* InEditorModel);`
- L29 _public prototype_ `void ForceRefresh();` — Refreshes the widget
- L33 _protected function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L38 _private prototype_ `TSharedRef<SWidget> GenerateFixturePatchListToolbar();` — Generates a toolbar for the FixturePatchList widget
- L41 _private prototype_ `TSharedRef<SWidget> CreateAddPatchMenu();` — Creates a menu for the Add Patch combo button
- L44 _private prototype_ `TSharedRef<SWidget> CreateAddEmptyMenu();` — Creates a menu for the Add Empty combo button
- L47 _private prototype_ `FReply OnAddAllPatchesClicked();` — Called on Add All Patches button clicked to generate Fader Group Controllers form a Library
- L50 _private prototype_ `bool IsAddPatchesButtonEnabled() const;` — Returns true if the 'Add Patch' buttons are enabled
- L53 _private prototype_ `bool IsAddEmptyButtonEnabled() const;` — Returns true if the 'Add Empty' button is enabled
- L56 _private prototype_ `EVisibility GetFixturePatchListToolbarVisibility() const;` — Gets the visibility for the FixturePatchList toolbar
- L59 _private member_ `TSharedPtr<SDMXControlConsoleFixturePatchList> FixturePatchList;` — Reference to the FixturePatchList widget
- L62 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorLayoutPicker.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorLayoutPicker`  
`class SDMXControlConsoleEditorLayoutPicker : public SCompoundWidget`  
_L17-104_
- inherits: `SCompoundWidget`
- desc: A widget to pick layouts for Control Console
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorLayoutPicker)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDMXControlConsoleEditorModel* InEditorModel);`
- L31 _private prototype_ `TSharedRef<SWidget> GenerateLayoutCheckBoxWidget();` — Generates a widget for selecting layouts
- L34 _private prototype_ `TSharedRef<SWidget> GenerateDefaultLayoutPickerWidget();` — Generates a widget for Default Layout options
- L37 _private prototype_ `TSharedRef<SWidget> GenerateUserLayoutPickerWidget();` — Generates a widget for User Layout options
- L40 _private prototype_ `TSharedRef<SWidget> GenerateUserLayoutComboBoxWidget(const TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase> InLayout);` — Generates a widget for each element in the UserLayoutsComboBox
- L43 _private prototype_ `bool IsDefaultLayoutActive() const;` — True if the active layout is the default layout
- L46 _private prototype_ `void OnDefaultLayoutCheckBoxStateChanged(ECheckBoxState CheckBoxState);` — Called when the Default Layout checkbox state has changed
- L49 _private prototype_ `void OnUserLayoutCheckBoxStateChanged(ECheckBoxState CheckBoxState);` — Called when the UserLayout checkbox state has changed
- L52 _private prototype_ `void UpdateComboBoxSource();` — Updates the ComboBoxSource array according to the current Control Console Layouts
- L55 _private prototype_ `ECheckBoxState IsAutoGroupCheckBoxChecked() const;` — Gets the check box state of the auto-group check box
- L58 _private prototype_ `void OnAutoGroupCheckBoxStateChanged(ECheckBoxState CheckBoxState);` — Called when the auto-group checkbox state has changed
- L61 _private prototype_ `void OnComboBoxSelectionChanged(const TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase> InLayout, ESelectInfo::Type SelectInfo);` — Called when a UserLayoutsComboBox element is selected
- L64 _private prototype_ `void OnLayoutNameTextChanged(const FText& NewText);` — Called when the LayoutNameEditableBox text changes
- L67 _private prototype_ `void OnLayoutNameTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Called when a new text on the LayoutNameEditableBox editable text box is committed
- L70 _private prototype_ `void OnRenameLayout(const FString& NewName);` — Called to rename the active layout
- L73 _private prototype_ `FReply OnAddLayoutClicked();` — Called when the add layout button is clicked
- L76 _private prototype_ `FReply OnRenameLayoutClicked();` — Called when the rename layout button is clicked
- L79 _private prototype_ `FReply OnDeleteLayoutClicked();` — Called when the delete layout button is clicked
- L82 _private prototype_ `EVisibility GetDefaultLayoutVisibility() const;` — Gets the visibility for the Default Layout option widgets
- L85 _private prototype_ `EVisibility GetUserLayoutVisibility() const;` — Gets the visibility for the User Layout option widgets
- L88 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase> LastSelectedItem;` — Reference to the last selected item in the UserLayoutsComboBox
- L91 _private member_ `TArray<TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase>> ComboBoxSource;` — Source items for the UserLayoutsComboBox
- L94 _private member_ `TSharedPtr<SComboBox<TWeakObjectPtr<UDMXControlConsoleEditorGlobalLayoutBase>>> UserLayoutsComboBox;` — A ComboBox for showing all User Layouts in the current Control Console
- L97 _private member_ `TSharedPtr<SEditableTextBox> LayoutNameEditableBox;` — Reference to the text box for editing the layout name
- L100 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model
- L103 _private member_ `FText LayoutNameText;` — Text for editing the layout name

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMX` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorPortSelector.h` (Private)


#### class `SDMXControlConsoleEditorPortSelector`  
`class SDMXControlConsoleEditorPortSelector : public SCompoundWidget`  
_L16-68_
- inherits: `SCompoundWidget`
- desc: Widget to select Ports to monitor
- L20 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorPortSelector) : _bSendToAllPorts(true) , _InitiallySelectedGuid(FGuid())`
- L25 _public prototype_ `SLATE_ARGUMENT(bool, bSendToAllPorts) SLATE_ARGUMENT(FGuid, InitiallySelectedGuid) SLATE_EVENT(FSimpleDelegate, OnPortsSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `bool IsSendToAllPorts() const;` — Returns true if the Sent To All Ports CheckBox is checked
- L40 _public prototype_ `FGuid GetSelectedPortGuid() const;` — Returns the Guid of the selected port
- L42 _public function_ `const TArray<FDMXOutputPortSharedRef>& GetSelectedOutputPorts() const`
- L46 _private prototype_ `void UpdateSelectedPorts();` — Updates the selected ports
- L49 _private prototype_ `void OnSendToAllPortsCheckBoxChanged(const ECheckBoxState NewCheckState);` — Called when the Monitor All Ports Check Box state changed
- L52 _private prototype_ `void HandlePortSelected();` — Called when a port was selected in the Port Selector
- L55 _private member_ `TArray<FDMXOutputPortSharedRef> SelectedOutputPorts;` — The output ports that are currently being monitored
- L58 _private member_ `TSharedPtr<SCheckBox> SendToAllPortsCheckBox;` — CheckBox to toggle if all ports should be monitored
- L61 _private member_ `TSharedPtr<SHorizontalBox> PortSelectorWrapper;` — Horizontal box that contains the Port Selector and its Label
- L64 _private member_ `TSharedPtr<SDMXPortSelector> PortSelector;` — Selector for the port to monitor
- L67 _private member_ `FSimpleDelegate OnPortsSelected;` — Called when port selection changes

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorSpinBoxController.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleEditorSpinBoxController`  
`class SDMXControlConsoleEditorSpinBoxController : public SCompoundWidget`  
_L18-86_
- inherits: `SCompoundWidget`
- desc: A widget to display a spin box which handles inputs for an Element Controller view
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorSpinBoxController)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXControlConsoleElementControllerModel>& InElementControllerModel, UDMXControlConsoleEditorModel* InEditorModel);`
- L31 _public prototype_ `UDMXControlConsoleElementController* GetElementController() const;` — Gets the element controller this widget is based on
- L34 _public prototype_ `void CommitValue(float NewValue);` — Manually commits the given value
- L38 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _private prototype_ `bool IsSelected() const;` — True if the element controller is selected
- L46 _private prototype_ `float GetValue() const;` — Gets the element controller value
- L49 _private prototype_ `FText GetValueAsText() const;` — Returns the element controller value as text
- L52 _private prototype_ `TOptional<float> GetMinValue() const;` — Gets the element controller minimum value
- L55 _private prototype_ `TOptional<float> GetMaxValue() const;` — Gets the element controller maximum value
- L58 _private prototype_ `void HandleValueChanged(float NewValue);` — Handles when the user changes the element controller value
- L61 _private prototype_ `void OnBeginValueChange();` — Called before the element controller value starts to change
- L64 _private prototype_ `void OnValueCommitted(float NewValue, ETextCommit::Type CommitType);` — Called when a new element controller value is committed
- L67 _private prototype_ `bool IsElementControllerSpinBoxActive() const;` — Gets wheter the ElementControllerSpinBox widget should be active or not
- L70 _private prototype_ `FText GetToolTipText() const;` — Returns the element controller parameters as tooltip text
- L73 _private prototype_ `const FSlateBrush* GetSpinBoxBorderImage() const;` — Changes the spin box background color on hover
- L76 _private member_ `TSharedPtr<SDMXControlConsoleEditorSpinBoxVertical<float>> ElementControllerSpinBox;` — The actual editable element controller spin box
- L79 _private member_ `TSharedPtr<FDMXControlConsoleElementControllerModel> ElementControllerModel;` — Reference to the element controller being displayed
- L82 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the control console editor model
- L85 _private member_ `float PreCommittedValue = 0.f;` — The element controller value before committing

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleEditorSpinBoxVertical.h` (Private)


#### class `SDMXControlConsoleEditorSpinBoxVertical`  
`template<typename NumericType> class SDMXControlConsoleEditorSpinBoxVertical : public SCompoundWidget`  
_L61-964_
- inherits: `SCompoundWidget`
- desc: A Slate SpinBox resembles traditional spin boxes in that it is a widget that provides keyboard-based and mouse-based manipulation of a numeric value. Mouse-based manipulation: drag anywhere on the spinbox to change the value. Keyboard-based manipulation: click on the spinbox to enter text mode.
- L67 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnValueChanged, NumericType );` — Notification for numeric value change
- L70 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L73 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnDynamicSliderMinMaxValueChanged, NumericType, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L75 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleEditorSpinBoxVertical<NumericType>) : _Style(&FCoreStyle::Get().GetWidgetStyle<FSpinBoxStyle>("SpinBox")) , _Value(0) , _MinValue(0) , _MaxValue(10) , _Delta(0) , _ShiftMultiplier(10.f) , _CtrlMultiplier(0.1f) , _IsActive(true) , _SupportDynamicSliderMaxValue(false) , _SupportDynamicSliderMinValue(false) , _SliderExponent(1) , _Font( FCoreStyle::Get().GetFontStyle( TEXT( "NormalFont" ) ) ) , _ContentPadding( FMargin( 2.0f, 1.0f) ) , _OnValueChanged() , _OnValueCommitted() , _ClearKeyboardFocusOnCommit( false ) , _SelectAllTextOnCommit( true ) , _MinDesiredWidth(0.0f)`
- L97 _public function_ `SLATE_STYLE_ARGUMENT( FSpinBoxStyle, Style ) SLATE_ATTRIBUTE( NumericType, Value ) SLATE_ATTRIBUTE( TOptional< NumericType >, MinValue ) SLATE_ATTRIBUTE( TOptional< NumericType >, MaxValue ) SLATE_ATTRIBUTE( TOptional< NumericType >, MinSliderValue ) SLATE_ATTRIBUTE( TOptional< NumericType >, MaxSliderValue ) SLATE_ATTRIBUTE( NumericType, Delta ) SLATE_ATTRIBUTE(float, ShiftMultiplier) SLATE_ATTRIBUTE(float, CtrlMultiplier) SLATE_ATTRIBUTE_DEPRECATED( int32, ShiftMouseMovePixelPerDelta, 5.4, "Shift Mouse Move Pixel Per Delta is deprecated and incrementing by a fixed delta per pixel is no longer supported. Please use ShiftMultiplier and CtrlMultiplier which will multiply the step per mouse move") SLATE_ATTRIBUTE( int32, LinearDeltaSensitivity) SLATE_ATTRIBUTE(bool, IsActive) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMaxValue) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMinValue) SLATE_EVENT(FOnDynamicSliderMinMaxValueChanged, OnDynamicSliderMaxValueChanged) SLATE_EVENT(FOnDynamicSliderMinMaxValueChanged, OnDynamicSliderMinValueChanged) SLATE_ATTRIBUTE( float, SliderExponent ) SLATE_ATTRIBUTE( NumericType, SliderExponentNeutralValue ) SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_ATTRIBUTE(FText, ValueText)` — The style used to draw this spinbox
- L270 _public function_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override`
- L340 _public function_ `const bool CommitWithMultiplier(const FPointerEvent& MouseEvent)`
- L352 _public function_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override` — The system calls this method to notify the widget that a mouse button was pressed within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L377 _public function_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override` — The system calls this method to notify the widget that a mouse button was release within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L417 _public function_ `void ApplySliderMaxValueChanged(float SliderDeltaToAdd, bool UpdateOnlyIfHigher)`
- L444 _public function_ `void ApplySliderMinValueChanged(float SliderDeltaToAdd, bool UpdateOnlyIfLower)`
- L478 _public function_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override` — The system calls this method to notify the widget that a mouse moved within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L627 _public function_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override`
- L634 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L640 _public function_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override`
- L671 _public function_ `TAttribute<NumericType> GetValueAttribute() const` — Return the Value attribute
- L674 _public function_ `float GetValue() const` — See the Value attribute
- L675 _public function_ `void SetValue(const TAttribute<NumericType>& InValueAttribute)`
- L682 _public function_ `NumericType GetMinValue() const` — See the MinValue attribute
- L683 _public function_ `void SetMinValue(const TAttribute<TOptional<NumericType>>& InMinValue)`
- L690 _public function_ `NumericType GetMaxValue() const` — See the MaxValue attribute
- L691 _public function_ `void SetMaxValue(const TAttribute<TOptional<NumericType>>& InMaxValue)`
- L698 _public function_ `bool IsMinSliderValueBound() const` — See the MinSliderValue attribute
- L700 _public function_ `NumericType GetMinSliderValue() const`
- L701 _public function_ `void SetMinSliderValue(const TAttribute<TOptional<NumericType>>& InMinSliderValue)`
- L708 _public function_ `bool IsMaxSliderValueBound() const` — See the MaxSliderValue attribute
- L710 _public function_ `NumericType GetMaxSliderValue() const`
- L711 _public function_ `void SetMaxSliderValue(const TAttribute<TOptional<NumericType>>& InMaxSliderValue)`
- L718 _public function_ `NumericType GetDelta() const` — See the Delta attribute
- L719 _public function_ `void SetDelta(NumericType InDelta)`
- L722 _public function_ `float GetSliderExponent() const` — See the SliderExponent attribute
- L723 _public function_ `void SetSliderExponent(const TAttribute<float>& InSliderExponent)`
- L726 _public function_ `float GetMinDesiredWidth() const` — See the MinDesiredWidth attribute
- L727 _public function_ `void SetMinDesiredWidth(const TAttribute<float>& InMinDesiredWidth)`
- L731 _protected function_ `FString GetValueAsString() const` — @return the value being observed by the spinbox as a string
- L737 _protected function_ `FText GetValueAsText() const` — @return the value being observed by the spinbox as FText - todo: spinbox FText support (reimplement me)
- L747 _protected function_ `void TextField_OnTextChanged( const FText& NewText)` — Invoked when the text in the text field changes @param NewText		The value of the text in the text field
- L784 _protected function_ `void CommitValue( double NewValue, ECommitMethod CommitMethod, ETextCommit::Type OriginalCommitInfo )` — Call this method when the user's interaction has changed the value @param NewValue               Value resulting from the user's interaction @param CommitMethod           Did the user type in the value or spin to it. @param OriginalCommitInfo	 If the user typed in the value, information about the source of the commit
- L851 _protected function_ `void NotifyValueCommitted() const`
- L861 _protected function_ `static float Fraction(double InValue, NumericType InMinValue, NumericType InMaxValue)` — Calculates range fraction. Possible to use on full numeric range
- L871 _protected function_ `static double Snap(double InValue, double InGrid)` — Snaps value to a nearest grid multiple. Clamps value if it's outside numeric range
- L878 _private member_ `TAttribute<NumericType> ValueAttribute;`
- L879 _private member_ `FOnValueChanged OnValueChanged;`
- L880 _private member_ `FOnValueCommitted OnValueCommitted;`
- L881 _private member_ `FSimpleDelegate OnBeginSliderMovement;`
- L882 _private member_ `FOnValueChanged OnEndSliderMovement;`
- L883 _private member_ `TSharedPtr<STextBlock> TextBlock;`
- L886 _private member_ `TSharedPtr< INumericTypeInterface<NumericType> > Interface;` — Interface that defines conversion functionality for the templated type
- L889 _private member_ `bool bUnlimitedSpinRange;` — True when no range is specified, spinner can be spun indefinitely
- L890 _private function_ `void UpdateIsSpinRangeUnlimited()`
- L895 _private member_ `const FSpinBoxStyle* Style;`
- L897 _private member_ `const FSlateBrush* BackgroundHoveredBrush;`
- L898 _private member_ `const FSlateBrush* BackgroundBrush;`
- L899 _private member_ `const FSlateBrush* ActiveFillBrush;`
- L900 _private member_ `const FSlateBrush* InactiveFillBrush;`
- L902 _private member_ `float DistanceDragged;`
- L903 _private member_ `TAttribute<NumericType> Delta;`
- L904 _private member_ `TAttribute<float> ShiftMultiplier;`
- L905 _private member_ `TAttribute<float> CtrlMultiplier;`
- L906 _private member_ `TAttribute<int32> LinearDeltaSensitivity;`
- L907 _private member_ `TAttribute<float> SliderExponent;`
- L908 _private member_ `TAttribute<NumericType> SliderExponentNeutralValue;`
- L909 _private member_ `TAttribute< TOptional<NumericType> > MinValue;`
- L910 _private member_ `TAttribute< TOptional<NumericType> > MaxValue;`
- L911 _private member_ `TAttribute< TOptional<NumericType> > MinSliderValue;`
- L912 _private member_ `TAttribute< TOptional<NumericType> > MaxSliderValue;`
- L913 _private member_ `TAttribute<bool> IsActive;`
- L914 _private member_ `TAttribute<bool> SupportDynamicSliderMaxValue;`
- L915 _private member_ `TAttribute<bool> SupportDynamicSliderMinValue;`
- L916 _private member_ `TAttribute<FText> ValueText;`
- L917 _private member_ `FOnDynamicSliderMinMaxValueChanged OnDynamicSliderMaxValueChanged;`
- L918 _private member_ `FOnDynamicSliderMinMaxValueChanged OnDynamicSliderMinValueChanged;`
- L921 _private member_ `TAttribute<float> MinDesiredWidth;` — Prevents the spinbox from being smaller than desired in certain cases (e.g. when it is empty)
- L922 _private function_ `float GetTextMinDesiredWidth() const`
- L928 _private function_ `bool IsCharacterValid(TCHAR InChar) const` — Check whether a typed character is valid
- L934 _private function_ `NumericType RoundIfIntegerValue( double ValueToRound ) const` — Rounds the submitted value to the correct value if it's an integer.
- L942 _private member_ `bool bDragging;` — Whether the user is dragging the slider
- L945 _private member_ `int32 PointerDraggingSliderIndex;` — Tracks which cursor is currently dragging the slider (e.g., the mouse cursor or a specific finger)
- L948 _private member_ `FIntPoint CachedMousePosition;` — Cached mouse position to restore after scrolling.
- L953 _private member_ `double InternalValue;` — This value represents what the spinbox believes the value to be, regardless of delta and the user binding to an int. The spinbox will always count using floats between values, this is important to keep it flowing smoothly and feeling right, and most importantly not conflicting with the user truncating the value to an int.
- L956 _private member_ `double PreDragValue;` — The state of InternalValue before a drag operation was started
- L960 _private member_ `NumericType CachedExternalValue;` — This is the cached value the user believes it to be (usually different due to truncation to an int). Used for identifying external forces on the spinbox and syncing the internal value to them. Synced when a value is committed to the spinbox.
- L963 _private member_ `bool bIsTextChanging;` — Re-entrant guard for the text changed handler

#### enum `SDMXControlConsoleEditorSpinBoxVertical::ECommitMethod`  
`enum ECommitMethod`  
_L769-775_
- desc: How user changed the value in the spinbox
- L771 _public enumerator_ `CommittedViaSpin`
- L772 _public enumerator_ `CommittedViaTypeIn`
- L773 _public enumerator_ `CommittedViaArrowKey`
- L774 _public enumerator_ `CommittedViaSpinMultiplier`

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace DMX` (scope `UE`)
- L49 _namespace_ `namespace Private` (scope `UE::DMX`)
- L51 _prototype_ `float SpinBoxVertComputeExponentSliderFraction(float FractionFilled, float StartFractionFilled, float SliderExponent);` (scope `UE::DMX::Private`)
- L67 _delegate_ `DECLARE_DELEGATE_OneParam( FOnValueChanged, NumericType );` — Notification for numeric value change
- L70 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L73 _delegate_ `DECLARE_DELEGATE_FourParams(FOnDynamicSliderMinMaxValueChanged, NumericType, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleFixturePatchList.h` (Private)


#### struct `UE::DMX::Private::FDMXControlConsoleReadOnlyFixturePatchListCollumnIDs`  
`struct FDMXControlConsoleReadOnlyFixturePatchListCollumnIDs`  
_L21-24_
- desc: Collumn IDs in the Fixture Patch List
- L23 _public member_ `static const FName FaderGroupEnabled;`

#### class `UE::DMX::Private::SDMXControlConsoleFixturePatchList`  
`class SDMXControlConsoleFixturePatchList : public SDMXReadOnlyFixturePatchList`  
_L27-124_
- inherits: `SDMXReadOnlyFixturePatchList`
- desc: List of Fixture Patches in a DMX library for read only purposes in DMX Control Console
- L31 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleFixturePatchList) : _DMXLibrary(nullptr)`
- L36 _public prototype_ `SLATE_ARGUMENT(UDMXLibrary*, DMXLibrary) SLATE_END_ARGS() ~SDMXControlConsoleFixturePatchList();` — The DMX Library displayed in the list
- L44 _public prototype_ `void Construct(const FArguments& InArgs, UDMXControlConsoleEditorModel* InEditorModel);` — Constructs this widget
- L48 _protected prototype_ `virtual FName GetHeaderRowFilterMenuName() const override;`
- L49 _protected prototype_ `virtual void ForceRefresh() override;`
- L50 _protected prototype_ `virtual TSharedRef<SHeaderRow> GenerateHeaderRow() override;`
- L51 _protected prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXReadOnlyFixturePatchListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable) override;`
- L52 _protected prototype_ `virtual void ToggleColumnShowState(const FName ColumnID) override;`
- L57 _private prototype_ `void ExtendHeaderRowFilterMenu(UToolMenu* InMenu);` — Extends the header row filter menu
- L60 _private prototype_ `void RegisterCommands();` — Registers commands for this widget
- L63 _private prototype_ `void AdoptSelectionFromData();` — Adopts selection from data
- L66 _private prototype_ `void OnFaderGroupAddedOrRemoved(const UDMXControlConsoleFaderGroup* FaderGroup);` — Called when a fader group was added or removed from the console
- L69 _private prototype_ `void OnAutoGroupStateChanged();` — Called when the auto-group option state has changed
- L72 _private prototype_ `void OnActiveLayoutChanged(const UDMXControlConsoleEditorGlobalLayoutBase* ActiveLayout);` — Called when the current active layout has changed
- L75 _private prototype_ `void OnLayoutViewSelectionChanged();` — Called when selection in the layout view of the console has changed
- L78 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Called when the context menu is opening
- L81 _private prototype_ `void OnSelectionChanged(const TSharedPtr<FDMXReadOnlyFixturePatchListItem> NewSelection, ESelectInfo::Type SelectInfo);` — Called when selection in the list changed
- L84 _private prototype_ `void HandleAutoGroupSinglePatchSelection() const;` — Handles selection change when auto-grouping and a single fixture patch is selected
- L87 _private prototype_ `void HandleAutoGroupMultiPatchSelection() const;` — Handles selection change when auto-grouping and multiple fixture patches are selected
- L90 _private prototype_ `void OnRowClicked(const TSharedPtr<FDMXReadOnlyFixturePatchListItem> ItemClicked);` — Called when a row was clicked
- L93 _private prototype_ `void OnRowDoubleClicked(const TSharedPtr<FDMXReadOnlyFixturePatchListItem> ItemClicked);` — Called when a row was double clicked
- L96 _private prototype_ `void OnEnableAllFaderGroups(bool bEnable, bool bOnlyActive) const;` — Called to enable/disable all Fader Groups in the current Control Console
- L99 _private prototype_ `bool IsAnyFaderGroupEnabled(bool bEnable, bool bOnlyActive) const;` — Gets wheter any Fader Group is enabled/disabled
- L102 _private prototype_ `ECheckBoxState GetGlobalFaderGroupsEnabledCheckBoxState() const;` — Called to get wheter the whole list is checked or not
- L105 _private prototype_ `void OnGlobalFaderGroupsEnabledCheckBoxStateChanged(ECheckBoxState CheckBoxState);` — Called when the global fader groups enabled checkbox state changed
- L108 _private prototype_ `void SetShowMode(EDMXReadOnlyFixturePatchListShowMode NewShowMode);` — Sets the show mode to be used
- L111 _private prototype_ `bool IsUsingShowMode(EDMXReadOnlyFixturePatchListShowMode InShowMode) const;` — Returns true if the current show mode matches the specified one
- L114 _private member_ `EDMXReadOnlyFixturePatchListShowMode ShowMode;` — Specifies if active, inactive or all patches are shown in the list
- L117 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for this widget
- L120 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> EditorModel;` — Weak reference to the Control Console editor model
- L123 _private member_ `int32 EditorModelUniqueID;` — Editor Model's unique identifier

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DMX` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Widgets/SDMXControlConsoleFixturePatchListRow.h` (Private)


#### class `UE::DMX::Private::SDMXControlConsoleFixturePatchListRow`  
`class SDMXControlConsoleFixturePatchListRow : public SDMXReadOnlyFixturePatchListRow`  
_L16-47_
- inherits: `SDMXReadOnlyFixturePatchListRow`
- desc: Entity Fixture Patch as a row in a list in DMX Control Console
- L20 _public function_ `SLATE_BEGIN_ARGS(SDMXControlConsoleFixturePatchListRow)`
- L23 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnFaderGroupMutedChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedRef<FDMXReadOnlyFixturePatchListItem>& InItem, const TWeakObjectPtr<UDMXControlConsoleEditorModel> InWeakEditorModel);` — Delegate broadcast when the fader group muted state changed
- L32 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L37 _private prototype_ `TSharedRef<SWidget> GenerateCheckBoxRow();` — Generates the row that displays the check box for Fixture Patch active state
- L40 _private member_ `TSharedPtr<FDMXControlConsoleFixturePatchListRowModel> RowModel;` — Model for this row
- L43 _private member_ `TWeakObjectPtr<UDMXControlConsoleEditorModel> WeakEditorModel;` — Weak reference to the Control Console editor model
- L46 _private member_ `FSimpleDelegate OnFaderGroupMutedChanged;` — Slate arguments

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Public/IDMXControlConsoleEditorModule.h` (Public)


#### class `IDMXControlConsoleEditorModule`  
`class IDMXControlConsoleEditorModule : public IModuleInterface`  
_L13-24_
- inherits: `IModuleInterface`
- L17 _public function_ `static IDMXControlConsoleEditorModule& Get()`
- L23 _public prototype_ `virtual FAssetCategoryPath GetControlConsoleCategory() const = 0;` — Gets the category under which Control Console assets are nested.
