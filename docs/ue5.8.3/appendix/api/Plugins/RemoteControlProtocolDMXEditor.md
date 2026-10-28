# Plugins / RemoteControlProtocolDMXEditor

- module root: `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor`
- headers: 13; symbols: 148
- symbol kinds: class=12, delegate=1, function=8, member=18, namespace=33, prototype=76
- PrivateDependencyModuleNames: Core, CoreUObject, DMXEditor, DMXProtocol, DMXProtocolEditor, DMXRuntime, Engine, InputCore, PropertyEditor, RemoteControl, RemoteControlProtocol, RemoteControlProtocolDMX, RemoteControlProtocolWidgets, RemoteControlUI, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/Customizations/RemoteControlProtocolDMXPresetUserDataDetails.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlProtocolDMXPresetUserDataDetails`  
`class FRemoteControlProtocolDMXPresetUserDataDetails final : public IDetailCustomization`  
_L12-25_
- inherits: `IDetailCustomization`
- desc: Details customization for URemoteControlDMXPresetUserData
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates a new instance of this details customization.
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> DMXLibraryHandle;` — Property handle for the DMXLibrary property

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RemoteControl` (scope `UE`)
- L9 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/Library/RemoteControlDMXLibraryBuilder.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXLibraryBuilder`  
`class FRemoteControlDMXLibraryBuilder : public TSharedFromThis<FRemoteControlDMXLibraryBuilder>`  
_L16-65_
- inherits: `TSharedFromThis<FRemoteControlDMXLibraryBuilder>`
- desc: Builds a DMX Library for a Remote Control Preset
- L21 _public prototype_ `static void Register();` — Creates an instance of the DMX Library builder
- L24 _public prototype_ `URemoteControlDMXUserData* GetDMXUserData() const;` — Returns the DMX User Data of the Remote Control Preset
- L27 _public prototype_ `URemoteControlDMXLibraryProxy* GetDMXLibraryProxy() const;` — Returns the DMX Library Proxy of the Remote Control Preset
- L30 _public prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the DMX Library of used with this Remote Control Preset
- L34 _private prototype_ `void PrePropertyPatchesChanged(URemoteControlPreset* InOutPreset);` — Called before property patches are being changed
- L37 _private prototype_ `void PostPropertyPatchesChanged();` — Called after property patches were changed
- L40 _private prototype_ `void RemoveObsoleteFixturesFromDMXLibrary(const TArray<TSharedRef<FRemoteControlDMXControlledPropertyPatch>>& PostEditChangePropertyPatches);` — Removes unused Fixture Types and Fixture Patches from the DMX Library
- L43 _private prototype_ `void AutoAssignFixturePatches(const TArray<TSharedRef<FRemoteControlDMXControlledPropertyPatch>>& PostEditChangePropertyPatches);` — Auto assigns fixture patches in the DMX Library
- L46 _private prototype_ `TMap<int32, TArray<UDMXEntityFixturePatch*>> GetGroupIndexToRCFixturePatchesMap(const UDMXLibrary& DMXLibrary) const;` — Returns all Remote Control related Fixture Patches in the DMX Library, grouped by group index
- L49 _private prototype_ `int32 GetOrCreateGroupIndex(const UDMXLibrary& DMXLibrary, const TArray<UDMXEntityFixturePatch*>& FixturePatches) const;` — Gets or creates a Group Index for a group of Fixture Patches.
- L52 _private prototype_ `int32 ExtractGroupIndex(const FName& Tag) const;` — Extracts a group index from a Fixture Patch tag
- L55 _private member_ `TArray<UDMXEntityFixtureType*> PreviousFixtureTypes;` — Fixture types used before property patches changed
- L58 _private member_ `TArray<UDMXEntityFixturePatch*> PreviousFixturePatches;` — Fixture patches used before property patches changed
- L61 _private member_ `URemoteControlPreset* Preset = nullptr;` — The remote control preset for which the Library is built
- L64 _private member_ `static const FString RCFixtureGroupTag;` — Tag for RC Fixture Groups

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RemoteControl` (scope `UE`)
- L13 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/Library/RemoteControlDMXPatchBuilder.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXPatchBuilder`  
`class FRemoteControlDMXPatchBuilder`  
_L13-20_
- desc: Builds fixture patches for a DMX Library Builder
- L17 _public prototype_ `static void BuildFixturePatches( const TSharedRef<FRemoteControlDMXLibraryBuilder>& InDMXLibraryBuilder, const TArray<TSharedRef<FRemoteControlDMXControlledPropertyPatch>>& InDMXControlledPropertyPatches);` — Builds fixture patches from property patches. Updates both the DMX Library and Remote Control Protocol DMX Entities.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RemoteControl` (scope `UE`)
- L7 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/RemoteControlDMXAutoBindHandler.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXAutoBindHandler`  
`class FRemoteControlDMXAutoBindHandler : public FTickableGameObject`  
_L17-43_
- inherits: `FTickableGameObject`
- desc: Handles auto binding DMX values and maintains the related list
- L22 _public prototype_ `static void Register();` — Registers the auto-bind handler with the engine
- L26 _private function_ `virtual bool IsTickable() const override`
- L27 _private function_ `virtual bool IsTickableInEditor() const override`
- L28 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L29 _private prototype_ `virtual TStatId GetStatId() const override;`
- L36 _private prototype_ `void ProcessAutoBinding(const TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>>& ProtocolEntity);` — Processes auto binding @param InProtocolEntityPtr	Protocol entity pointer
- L39 _private member_ `TMap<TSharedRef<FDMXInputPort>, TArray<TSharedRef<FDMXSignal>>> LastInputPortToSignalsMap;` — Last received DMX Signals with their input ports
- L42 _private member_ `bool bIsAutoPatch = true;` — Caches if auto patch mode is enabled

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RemoteControl` (scope `UE`)
- L14 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/RemoteControlDMXEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogRemoteControlDMXEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogRemoteControlDMXEditor, Log, All);`

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/RemoteControlDMXExposedEntitiesGroupPatchWidgetFactory.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXExposedEntitiesGroupPatchWidgetFactory`  
`class FRemoteControlDMXExposedEntitiesGroupPatchWidgetFactory : public IRCPanelExposedEntitiesGroupWidgetFactory , public TSharedFromThis<FRemoteControlDMXExposedEntitiesGroupPatchWidgetFactory>`  
_L14-30_
- inherits: `IRCPanelExposedEntitiesGroupWidgetFactory,TSharedFromThis<FRemoteControlDMXExposedEntitiesGroupPatchWidgetFactory>`
- desc: Widget factory the patch column in an exposed entities group row
- L19 _public function_ `virtual ~FRemoteControlDMXExposedEntitiesGroupPatchWidgetFactory()`
- L22 _public prototype_ `static void Register();` — Registers this factory with the engine
- L26 _protected prototype_ `virtual FName GetColumnName() const override;`
- L27 _protected prototype_ `virtual FName GetProtocolName() const override;`
- L28 _protected prototype_ `virtual TSharedRef<SWidget> MakeWidget(const FRCPanelExposedEntitiesGroupWidgetFactoryArgs& Args) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RemoteControl` (scope `UE`)
- L11 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/RemoteControlDMXExposedEntitiesListSettings.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXExposedEntitiesListSettings`  
`class FRemoteControlDMXExposedEntitiesListSettings : public IRCPanelExposedEntitiesListSettingsForProtocol , public TSharedFromThis<FRemoteControlDMXExposedEntitiesListSettings>`  
_L13-32_
- inherits: `IRCPanelExposedEntitiesListSettingsForProtocol,TSharedFromThis<FRemoteControlDMXExposedEntitiesListSettings>`
- desc: Settings for the DMX exposed entities list
- L18 _public prototype_ `virtual ~FRemoteControlDMXExposedEntitiesListSettings() = default;`
- L21 _public prototype_ `static void Register();` — Registers the exposed entities list settings with the engine
- L24 _public prototype_ `virtual FName GetProtocolName() const override;`
- L25 _public prototype_ `virtual FRCPanelExposedEntitiesListSettingsData GetListSettings(URemoteControlPreset* Preset) const override;`
- L26 _public prototype_ `virtual void OnSettingsChanged(URemoteControlPreset* Preset, const FRCPanelExposedEntitiesListSettingsData& ListSettings) override;`
- L31 _private prototype_ `URemoteControlDMXUserData* GetUserData(URemoteControlPreset* Preset) const;` — Returns the DMX user data of the preset

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RemoteControl` (scope `UE`)
- L10 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/RemoteControlDMXExposedEntitiesPanelExtender.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXExposedEntitiesPanelExtender`  
`class FRemoteControlDMXExposedEntitiesPanelExtender : public IRCExposedEntitiesPanelExtender , public TSharedFromThis<FRemoteControlDMXExposedEntitiesPanelExtender>`  
_L13-27_
- inherits: `IRCExposedEntitiesPanelExtender,TSharedFromThis<FRemoteControlDMXExposedEntitiesPanelExtender>`
- desc: Handles extending the exposed entities panel for DMX
- L18 _public function_ `virtual ~FRemoteControlDMXExposedEntitiesPanelExtender()`
- L21 _public prototype_ `static void Register();` — Registers the extender with the engine
- L25 _protected prototype_ `virtual TSharedRef<SWidget> MakeWidget(URemoteControlPreset* Preset, const IRCExposedEntitiesPanelExtender::FArgs& Args) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RemoteControl` (scope `UE`)
- L10 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/RemoteControlDMXExposedEntityPatchWidgetFactory.h` (Private)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXExposedEntityPatchWidgetFactory`  
`class FRemoteControlDMXExposedEntityPatchWidgetFactory : public IRCPanelExposedEntityWidgetFactory , public TSharedFromThis<FRemoteControlDMXExposedEntityPatchWidgetFactory>`  
_L10-26_
- inherits: `IRCPanelExposedEntityWidgetFactory,TSharedFromThis<FRemoteControlDMXExposedEntityPatchWidgetFactory>`
- desc: Widget factory the patch column in an exposed entities group row
- L15 _public function_ `virtual ~FRemoteControlDMXExposedEntityPatchWidgetFactory()`
- L18 _public prototype_ `static void Register();` — Registers the factory with the engine
- L22 _protected prototype_ `virtual FName GetColumnName() const override;`
- L23 _protected prototype_ `virtual FName GetProtocolName() const override;`
- L24 _protected prototype_ `virtual TSharedRef<SWidget> MakePropertyWidget(const FRCPanelExposedPropertyWidgetArgs& Args) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RemoteControl` (scope `UE`)
- L7 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/RemoteControlDMXPerPresetEditorSettings.h` (Private)


#### class `URemoteControlDMXPerPresetEditorSettings`  
`class URemoteControlDMXPerPresetEditorSettings : public UObject`  
_L14-25_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: UObject to hold entities list settings data
- L21 _public prototype_ `static URemoteControlDMXPerPresetEditorSettings* GetOrCreatePerPresetEditorSettings(URemoteControlPreset* Preset);` — Returns the remote control DMX editor settings for the specified preset
- L24 _public member_ `FRCPanelExposedEntitiesListSettingsData ExposedEntitiesListSettings;` — `UPROPERTY()`

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/UI/SRemoteControlDMXExposedEntitiesGroupPatch.h` (Private)


#### class `UE::RemoteControl::DMX::SRemoteControlDMXExposedEntitiesGroupPatch`  
`class SRemoteControlDMXExposedEntitiesGroupPatch : public SCompoundWidget`  
_L22-93_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SRemoteControlDMXExposedEntitiesGroupPatch)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<URemoteControlPreset>& InPreset, const TArray<TSharedRef<FRemoteControlProperty>>& InChildProperties);`
- L35 _private prototype_ `void Refresh();` — Refreshes the widget
- L38 _private prototype_ `void RequestRefresh();` — Refreshes the widget on the next tick
- L41 _private prototype_ `TSharedRef<SWidget> CreateMenu();` — Creates the menu
- L44 _private prototype_ `void ClearPatch();` — Clears the patch for all entities
- L47 _private prototype_ `void GeneratePatch();` — Generates a patch for all entities
- L50 _private prototype_ `void SetAutoPatchEnabled(bool bEnabled);` — Enables or disables auto patching for the entities in this group
- L53 _private prototype_ `void OnFixturePatchSelected(TWeakObjectPtr<UDMXEntityFixturePatch> WeakFixturePatch);` — Called when a fixture patch was selected
- L56 _private prototype_ `bool IsPrimaryFixturePatch() const;` — Returns true if a primary fixture patch is selected
- L59 _private prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — Returns the selected fixture patch or nullptr if no patch is selected
- L62 _private prototype_ `URemoteControlDMXUserData* GetDMXUserData() const;` — Returns the remote control DMX user data
- L65 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when a fixture patch changed
- L68 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a fixture type changed
- L71 _private prototype_ `void OnPostLoadRemoteControlPreset(URemoteControlPreset* Preset);` — Called when the remote control preset was fully loaded
- L74 _private prototype_ `void OnEntityExposedOrUnexposed(URemoteControlPreset* Preset, const FGuid& EntityId);` — Called when an entity was exposed or unexposed
- L77 _private prototype_ `void OnEntityRebind(const FGuid& EntityId);` — Called when an entity was rebound
- L80 _private prototype_ `void OnEntitiesUpdated(URemoteControlPreset* Preset, const TSet<FGuid>& ModifiedEntities);` — Called when entities changed
- L83 _private member_ `TArray<TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>> Entities;` — The entities that are affected by the patch
- L86 _private member_ `TWeakObjectPtr<URemoteControlPreset> WeakPreset;` — The preset for which this widget is displayed
- L89 _private member_ `TArray<TWeakObjectPtr<UDMXEntityFixturePatch>> WeakFixturePatches;` — The fixture patches in this preset
- L92 _private member_ `FTimerHandle RefreshTimerHandle;` — Timer handle for the request refresh method

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RemoteControl` (scope `UE`)
- L18 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/UI/SRemoteControlDMXExposedEntityPatch.h` (Private)


#### class `UE::RemoteControl::DMX::SRemoteControlDMXExposedEntityPatch`  
`class SRemoteControlDMXExposedEntityPatch : public SCompoundWidget`  
_L19-75_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SRemoteControlDMXExposedEntityPatch)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<URemoteControlPreset>& InPreset, const TSharedRef<FRemoteControlProperty>& InProperty);`
- L32 _private prototype_ `void RequestRefresh();` — Refreshes the widget on the next tick
- L35 _private prototype_ `void Refresh();` — Refreshes the widget
- L38 _private prototype_ `FText GetUniverseChannelText() const;` — Returns the current universe channel text
- L41 _private prototype_ `void OnUniverseChannelTextCommitted(const FText& InUniverseChannelText, ETextCommit::Type InCommitType);` — Called when universe channel text was committed
- L44 _private prototype_ `bool IsReadOnly() const;` — Returns true if the text block of this widget is read only
- L47 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when a fixture patch changed
- L50 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a fixture type changed
- L53 _private prototype_ `void OnPostLoadRemoteControlPreset(URemoteControlPreset* Preset);` — Called when the remote control preset was fully loaded
- L56 _private prototype_ `void OnEntityExposedOrUnexposed(URemoteControlPreset* Preset, const FGuid& EntityId);` — Called when an entity was exposed or unexposed
- L59 _private prototype_ `void OnEntityRebind(const FGuid& EntityId);` — Called when an entity was rebound
- L62 _private prototype_ `void OnEntitiesUpdated(URemoteControlPreset* Preset, const TSet<FGuid>& ModifiedEntities);` — Called when entities changed
- L65 _private member_ `TSharedPtr<FRemoteControlProperty> Property;` — The displayed property
- L68 _private member_ `TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> MinEntity;` — The first binding given the DMX universe and channel
- L71 _private member_ `TWeakObjectPtr<URemoteControlPreset> WeakPreset;` — The preset for which this widget is painted
- L74 _private member_ `FTimerHandle RefreshTimerHandle;` — Timer handle for request refresh

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace RemoteControl` (scope `UE`)
- L17 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMXEditor/Private/UI/SRemoteControlDMXPresetUserData.h` (Private)


#### class `UE::RemoteControl::DMX::SRemoteControlDMXPresetUserData`  
`class SRemoteControlDMXPresetUserData : public SCompoundWidget, public FGCObject`  
_L14-61_
- inherits: `SCompoundWidget,FGCObject`
- L17 _public function_ `SLATE_BEGIN_ARGS(SRemoteControlDMXPresetUserData)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, URemoteControlDMXUserData* InDMXUserData);`
- L27 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L28 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L33 _private prototype_ `TSharedRef<SWidget> GenerateActionsMenu();` — Generates an Actions menu (e.g Export as MVR)
- L36 _private prototype_ `void OnExportAsMVRClicked();` — Called when the export as MVR button was clicked
- L39 _private prototype_ `void OnCreateDMXLibraryClicked();` — Called when the Create DMX Library button was clicked
- L42 _private prototype_ `ECheckBoxState GetAutoPatchCheckState() const;` — Returns true if the auto patch option is checked
- L45 _private prototype_ `void OnAutoPatchCheckStateChanged(ECheckBoxState NewCheckState);` — Called when the auto patch check state changed
- L48 _private prototype_ `EVisibility GetAutoAssignFromUniverseVisibility() const;` — Returns the visibility of the auto assign from universe option
- L51 _private prototype_ `FText GetAutoAssignFromUniverseText() const;` — Returns the auto assign from universe as text
- L54 _private prototype_ `void OnAutoAssignFromUniverseTextCommitted(const FText& InAutoAssignFromUniverseText, ETextCommit::Type InCommitType);` — Called when the auto assign from universe text was committed
- L57 _private member_ `TSharedPtr<SEditableTextBox> AutoAssignFromUniverseEditableTextBox;` — Text box to edit the auto assign from universe
- L60 _private member_ `TObjectPtr<URemoteControlDMXUserData> DMXUserData;` — The preset this widget is editing

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RemoteControl` (scope `UE`)
- L12 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)
