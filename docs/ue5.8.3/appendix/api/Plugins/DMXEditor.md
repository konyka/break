# Plugins / DMXEditor

- module root: `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor`
- headers: 123; symbols: 2410
- symbol kinds: class=124, delegate=25, enum=12, enumerator=42, function=201, macro=5, member=705, namespace=62, prototype=1202, struct=27, typedef=5
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, ContentBrowser, CoreUObject, DMXGDTF, DMXZip, DesktopPlatform, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, Json, JsonUtilities, Kismet, KismetWidgets, MainFrame, MovieScene, Projects, PropertyEditor, SequencerCore, Slate, SlateCore, TakeRecorder, TakeTrackRecorders, TakesCore, ToolMenus, ToolWidgets, UnrealEd, XmlParser
- PublicDependencyModuleNames: Core, DMXProtocol, DMXProtocolEditor, DMXRuntime, Sequencer, ToolMenus

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Internal/Analytics/DMXEditorToolAnalyticsProvider.h` (Internal)


#### class `UE::DMX::FDMXEditorToolAnalyticsProvider`  
`class FDMXEditorToolAnalyticsProvider`  
_L13-45_
- desc: Can be implemented in tools that want to provide engine analytics
- L16 _public prototype_ `FDMXEditorToolAnalyticsProvider(const FName& InToolName);`
- L17 _public prototype_ `virtual ~FDMXEditorToolAnalyticsProvider();`
- L25 _public prototype_ `void RecordEvent(const FName& Name, const TArray<FAnalyticsEventAttribute>& InAttributes);` — Records a telemetry event. @param Name						The name of the specific event. Will be appended to the tool specific event name. @param Attributes				The attributes recorded with this event.
- L29 _private prototype_ `void RecordToolStarted();` — Records analytics for when the tool started.
- L32 _private prototype_ `void RecordToolEnded();` — Records analytics for when the tool ended.
- L35 _private member_ `FDateTime ToolStartTimestamp;` — The time when the tool was started
- L38 _private member_ `bool bEnded = false;` — True after RecordToolEnded was called, either on engine pre exit or on destruction
- L41 _private member_ `const FName ToolName;` — Name of the tool we are providing analytics for
- L44 _private member_ `static const FString DMXToolEventName;` — Event name for DMX telemetry events

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Internal/Widgets/DMXReadOnlyFixturePatchListItem.h` (Internal)


#### class `FDMXReadOnlyFixturePatchListItem`  
`class FDMXReadOnlyFixturePatchListItem : public FGCObject , public TSharedFromThis<FDMXReadOnlyFixturePatchListItem>`  
_L15-55_
- inherits: `FGCObject,TSharedFromThis<FDMXReadOnlyFixturePatchListItem>`
- desc: An item in the read only fixture patch list
- L20 _public prototype_ `FDMXReadOnlyFixturePatchListItem(const FDMXEntityFixturePatchRef& FixturePatchReference);`
- L23 _public function_ `UDMXEntityFixturePatch* GetFixturePatch() const` — Returns the fixture patch this item uses
- L26 _public prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the dmx library this item uses
- L29 _public prototype_ `FText GetNameText() const;` — Returns the name of the patch this item uses, as text
- L32 _public prototype_ `FText GetUniverseChannelText() const;` — Returns universe and channel of the patch this item uses, as text
- L35 _public prototype_ `FText GetFixtureIDText() const;` — Returns fixture ID of the patch this item uses, as text
- L38 _public prototype_ `FText GetFixtureTypeText() const;` — Returns fixture type name of the patch this item uses, as text
- L41 _public prototype_ `FText GetModeText() const;` — Returns mode name of the patch this item uses, as text
- L44 _public prototype_ `FSlateColor GetEditorColor() const;` — Returns the editor color of the patch this item uses
- L48 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L49 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L54 _private member_ `TObjectPtr<UDMXEntityFixturePatch> FixturePatch;` — The fixture patch this item uses

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/AssetDefinition/AssetDefinition_DMXEditorLibrary.h` (Private)


#### class `UAssetDefinition_DMXEditorLibrary`  
`class UAssetDefinition_DMXEditorLibrary : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Commands/DMXConflictMonitorCommands.h` (Private)


#### class `FDMXConflictMonitorCommands`  
`class FDMXConflictMonitorCommands : public TCommands<FDMXConflictMonitorCommands>`  
_L9-27_
- inherits: `TCommands<FDMXConflictMonitorCommands>`
- L13 _public prototype_ `FDMXConflictMonitorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> StartScan;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> PauseScan;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ResumeScan;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> StopScan;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoPause;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> TogglePrintToLog;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleRunWhenOpened;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXAttributeNameCustomization.h` (Private)


#### class `FDMXAttributeNameCustomization`  
`class FDMXAttributeNameCustomization : public IPropertyTypeCustomization`  
_L20-59_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for FDMXAttributeName struct
- L25 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L28 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L34 _private prototype_ `FName GetValue() const;` — Returns the value as FName
- L37 _private prototype_ `void SetValue(FName NewValue);` — Sets the value
- L40 _private prototype_ `bool HasMultipleValues() const;` — True if the customization displays multiple values
- L43 _private prototype_ `void RequestRefresh();` — Requests a refresh of the customization
- L46 _private prototype_ `void Refresh();` — Refreshes instantly
- L49 _private member_ `TSharedPtr<IPropertyHandle> NameHandle;` — Property handle for the Name property
- L52 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle for the FDMXAttributeName struct self
- L55 _private member_ `FTimerHandle RefreshHandle;` — Timer handle set when refresh is requested but not carried out yet
- L58 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utlities for this customization

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXAutoExpandedStructCustomization.h` (Private)


#### class `FDMXAutoExpandedStructCustomization`  
`class FDMXAutoExpandedStructCustomization : public IPropertyTypeCustomization`  
_L10-21_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for DMX auto expanded structs
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of the property type customization
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXEntityFixturePatchDetails.h` (Private)


#### class `FDMXEntityFixturePatchDetails`  
`class FDMXEntityFixturePatchDetails : public IDetailCustomization`  
_L21-90_
- inherits: `IDetailCustomization`
- desc: Details customization for the DMMXFixturePatch class
- L26 _public prototype_ `FDMXEntityFixturePatchDetails(TWeakPtr<FDMXEditor> InDMXEditorPtr);` — Constructor
- L29 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<FDMXEditor> InDMXEditorPtr);` — Creates a detail customization instance
- L33 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L38 _private prototype_ `TSharedRef<SWidget> GenerateActiveModeWidget(const TSharedPtr<uint32> InMode) const;` — Generates the customized ActiveMode property widget
- L41 _private prototype_ `void OnParentFixtureTypeChanged(UDMXEntity* NewTemplate) const;` — Called when the ParentFixtureType property changed
- L44 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a Mode in the Modes Array property changed
- L47 _private prototype_ `void OnUniverseIDChanged();` — Called when the UniverseID property changed
- L50 _private prototype_ `void OnActiveModeChanged(const TSharedPtr<uint32> InSelectedMode, ESelectInfo::Type SelectInfo);` — Called when the ActiveMode property changed
- L53 _private prototype_ `void GenerateActiveModesSource();` — Generates the Array of available mode in the ActiveModeSource member array
- L56 _private prototype_ `TWeakObjectPtr<UDMXEntityFixtureType> GetParentFixtureType() const;` — Returns the Fixture Type the patch uses
- L59 _private prototype_ `bool IsParentFixtureTypeMultipleValues() const;` — Returns true if the ParentFixtureType property has multiple values
- L62 _private prototype_ `bool IsActiveModeEditable() const;` — Returns true if the ActiveMode property is editable
- L65 _private prototype_ `FText GetCurrentActiveModeLabel() const;` — Returns a label for the currently active mode
- L68 _private prototype_ `void SetActiveMode(int32 ModeIndex);` — Sets the ActiveMode to specified value
- L71 _private member_ `TSharedPtr<IPropertyHandle> ParentFixtureTypeHandle;` — Handle for the ParentFixtureType property
- L74 _private member_ `TSharedPtr<IPropertyHandle> UniverseIDHandle;` — Handle for the UniverseID property
- L77 _private member_ `TSharedPtr<IPropertyHandle> ActiveModeHandle;` — Handle for the ActiveMode property
- L80 _private member_ `TSharedPtr<SComboBox<TSharedPtr<uint32>>> ActiveModeComboBox;` — ComboBox that displays the ActiveMode property
- L83 _private member_ `TArray<TSharedPtr<uint32>> ActiveModesSource;` — Array of available mode indicies
- L86 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — The property utilities for the customization
- L89 _private member_ `TWeakPtr<FDMXEditor> DMXEditorPtr;` — Weak reference to the DMX editor

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXEntityFixtureTypeDetails.h` (Private)


#### class `FDMXEntityFixtureTypeDetails`  
`class FDMXEntityFixtureTypeDetails : public IDetailCustomization`  
_L14-41_
- inherits: `IDetailCustomization`
- desc: Details customization for the 'FixtureType FunctionProperties' details view
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this details customization
- L23 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _private prototype_ `void OnGDTFSourceChanged();` — Called when the GDTFSource property changed
- L31 _private prototype_ `FReply OnResetToGDTFClicked();` — Called when the Reset To GDTF button was clicked
- L34 _private prototype_ `EVisibility GetGDTFOptionsVisibility() const;` — Returns the visibility of the GDTF options, they're only visible if there is a GDTF
- L37 _private member_ `TSharedPtr<IPropertyHandle> GDTFSourceHandle;` — Handle to the GDTFSource property
- L40 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXEntityReferenceCustomization.h` (Private)


#### class `FDMXEntityReferenceCustomization`  
`class FDMXEntityReferenceCustomization : public IPropertyTypeCustomization`  
_L17-60_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for Entity Reference structs
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of the property type customization
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _private prototype_ `bool ShouldDisplayLibrary() const;` — Returns whether the library field should be displayed
- L34 _private prototype_ `TSharedRef<SWidget> CreateEntityPickerWidget(TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Creates the widget where the entity can be picked
- L37 _private prototype_ `FText GetPickerPropertyLabel() const;` — Returns the label of the entity property
- L40 _private prototype_ `bool GetPickerEnabled() const;` — Returns true if the picker is enabled
- L43 _private prototype_ `TWeakObjectPtr<UDMXEntity> GetCurrentEntity() const;` — Returns the currently selected entity
- L46 _private prototype_ `bool GetEntityIsMultipleValues() const;` — Returns true if multiple values are customized
- L49 _private prototype_ `void OnEntitySelected(UDMXEntity* NewEntity) const;` — Called when an entity was selected
- L52 _private prototype_ `TSubclassOf<UDMXEntity> GetEntityType() const;` — Returns the type of entities that can be selected
- L55 _private prototype_ `TWeakObjectPtr<UDMXLibrary> GetDMXLibrary() const;` — Returns the DMX library where the entity resides
- L59 _private member_ `TSharedPtr<IPropertyHandle> StructHandle;` — Handle for the entity struct that is customized

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXFixtureCategoryCustomization.h` (Private)


#### class `FDMXFixtureCategoryCustomization`  
`class FDMXFixtureCategoryCustomization : public IPropertyTypeCustomization`  
_L17-42_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the FDMXFixtureCategory struct
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _private prototype_ `FName GetValue() const;` — Returns the value as FName
- L34 _private prototype_ `void SetValue(FName NewValue);` — Sets the value
- L37 _private prototype_ `bool HasMultipleValues() const;` — True if the customization displays multiple values
- L41 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle for the FDMXFixtureCategory struct self

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXFixtureFunctionCustomization.h` (Private)


#### class `UE::DMX::FDMXFixtureFunctionCustomization`  
`class FDMXFixtureFunctionCustomization : public IPropertyTypeCustomization`  
_L12-23_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the FDMXFixtureFunction struct
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L20 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXFixtureSignalFormatCustomization.h` (Private)


#### class `FDMXFixtureSignalFormatCustomization`  
`class FDMXFixtureSignalFormatCustomization : public IPropertyTypeCustomization`  
_L15-39_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for the EDMXFixtureSignalFromat enum
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of the property type customization
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override`
- L29 _private prototype_ `TArray<EDMXFixtureSignalFormat> GetSignalFormats() const;` — Returns the Signal Formats currently being edited
- L32 _private prototype_ `void SetSignalFormats(EDMXFixtureSignalFormat NewSignalFormat) const;` — Sets the Signal Format
- L35 _private member_ `TSharedPtr<SDMXSignalFormatSelector> SignalFormatSelector;` — The widget to select a Signal Format from
- L38 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Property handle for the enum property

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXLibraryDetails.h` (Private)


#### class `FDMXLibraryDetails`  
`class FDMXLibraryDetails : public IDetailCustomization`  
_L13-28_
- inherits: `IDetailCustomization`
- desc: Details customization for the 'FixtureType FunctionProperties' details view
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this details customization
- L22 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L27 _private prototype_ `void OnPortReferencesChanged();` — Called when port references changed

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXLibraryFromMVRImportOptionsDetails.h` (Private)


#### class `FDMXLibraryFromMVRImportOptionsDetails`  
`class FDMXLibraryFromMVRImportOptionsDetails final : public IDetailCustomization`  
_L15-39_
- inherits: `IDetailCustomization`
- desc: Details customization fro the MVR Scene Actor Factory Import Options
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this details customization
- L24 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L29 _private prototype_ `bool HasAnyInputPorts() const;` — Returns true if the project has any input ports defined
- L32 _private prototype_ `bool HasAnyOutputPorts() const;` — Returns true if the project has any output ports defined
- L35 _private member_ `UDMXLibrary* TempDMXLibrary = nullptr;` — For comparison when merging, create a temporary DMX Library from the imported MVR before actually merging changes when reimporting
- L38 _private member_ `UDMXLibraryFromMVRImportOptions* ImportOptions = nullptr;` — Import Options Object

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXLibraryPortReferencesCustomization.h` (Private)


#### class `FDMXLibraryPortReferencesCustomization`  
`class FDMXLibraryPortReferencesCustomization : public IPropertyTypeCustomization`  
_L17-56_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for the Library Port References struct
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of the property type customization
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L31 _protected prototype_ `void OnPortsChanged();` — Called when ports changed
- L34 _protected prototype_ `void RefreshPortReferenceWidgets();` — Generates an port row given the PortReferenceHandles
- L37 _protected prototype_ `TSharedRef<SWidget> GeneratePortInfoWidget(const FDMXPortSharedPtr& Port) const;` — Generates infos about the port
- L40 _protected prototype_ `FDMXInputPortSharedPtr GetInputPort(const TSharedPtr<IPropertyHandle>& InputPortReferenceHandle);` — Returns the input port from the port refernce handle
- L43 _protected prototype_ `FDMXOutputPortSharedPtr GetOutputPort(const TSharedPtr<IPropertyHandle>& OutputPortReferenceHandle);` — Returns the output port from the port refernce handle
- L46 _protected member_ `TSharedPtr<IPropertyHandle> LibraryPortReferencesHandle;` — The PortReferences property handle (the outermost StructPropertyHandle that is being customized)
- L49 _protected member_ `TSharedPtr<SBorder> InputPortReferenceContentBorder;` — Input port reference content border
- L52 _protected member_ `TSharedPtr<SBorder> OutputPortReferenceContentBorder;` — Output port reference content border
- L55 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXMVRSceneActorDetails.h` (Private)


#### class `FDMXMVRSceneActorDetails`  
`class FDMXMVRSceneActorDetails : public IDetailCustomization`  
_L16-73_
- inherits: `IDetailCustomization`
- desc: Details customization for the 'FixtureType FunctionProperties' details view
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this details customization
- L25 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L30 _private prototype_ `void CreateDMXLibrarySection(IDetailLayoutBuilder& DetailBuilder);` — Creates the DMX Library related section
- L33 _private prototype_ `void CreateFixtureTypeToActorClassSection(IDetailLayoutBuilder& DetailBuilder);` — Creates the section where the user can select an actor class for each Fixture Type in the MVR Scene
- L36 _private prototype_ `UDMXEntityFixturePatch* GetFixturePatchFromActor(AActor* Actor) const;` — Returns the Fixture Patch from an Actor, or nullptr if the Actor has no Fixture Patch set
- L39 _private prototype_ `FReply OnRefreshActorsFromDMXLibraryClicked();` — Called when the Refresh Actors from DMX Library button was clicked
- L42 _private prototype_ `FReply OnWriteTransformsToDMXLibraryClicked();` — Called when the Write Transforms To DMX Library button was clicked
- L45 _private prototype_ `FReply OnFixtureTypeToActorClassGroupSelected(UObject* FixtureTypeObject);` — Called when a Fixture Type to Actor Class Group was selected
- L48 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when a Fixture Patch changed
- L51 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a Fixture Type changed
- L54 _private prototype_ `void OnMapChange(uint32 MapChangeFlags);` — Called when a sub-level is loaded
- L57 _private prototype_ `void OnActorDeleted(AActor* DeletedActor);` — Called when an actor got deleted in editor
- L60 _private prototype_ `void OnPreEditChangeActorClassInFixtureTypeToActorClasses();` — Called before an Actor Class changed in the FixtureTypeToActorClasses member of the Actor
- L63 _private prototype_ `void OnPostEditChangeActorClassInFixtureTypeToActorClasses();` — Called after an Actor Class changed in the FixtureTypeToActorClasses member of the Actor
- L66 _private prototype_ `void RequestRefresh();` — Requests this Details Customization to refresh
- L69 _private member_ `TArray<TWeakObjectPtr<ADMXMVRSceneActor>> OuterSceneActors;` — The Actors being customized in this Detais Customization
- L72 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property Utilities for this Details Customization

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/DMXPixelMappingDistributionCustomization.h` (Private)


#### class `FDMXPixelMappingDistributionCustomization`  
`class FDMXPixelMappingDistributionCustomization : public IPropertyTypeCustomization`  
_L14-42_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the DMXPixelMappingDistribution enum
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L23 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override`
- L28 _protected prototype_ `FSlateColor GetButtonColorAndOpacity(int32 GridIndexX, int32 GridIndexY);` — Gets the color and opacity of the enum value buttons
- L31 _protected prototype_ `FReply OnGridButtonClicked(int32 GridIndexX, int32 GridIndexY);` — Called when an enum value button in the grid was clicked
- L35 _private member_ `static const uint8 DistributionGridNumXPanels = 4;` — Number of panels in X direction
- L38 _private member_ `static const uint8 DistributionGridNumYPanels = 4;` — Number of buttons in Y direction
- L41 _private member_ `TSharedPtr<IPropertyHandle> EnumPropertyHandle;` — Handle for the enum property that is customized

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Customizations/TakeRecorderDMXLibrarySourceEditorCustomization.h` (Private)


#### class `FTakeRecorderDMXLibrarySourceEditorCustomization`  
`class FTakeRecorderDMXLibrarySourceEditorCustomization : public IPropertyTypeCustomization`  
_L13-40_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L27 _private prototype_ `bool GetAddAllEnabled() const;` — Checks whether all selected DMX Take Recorders have valid DMX Libraries
- L29 _private prototype_ `FReply HandleOnClicked();` — Add all Patches to be recorded on each DMX Take Recorder
- L36 _private member_ `TArray<TWeakObjectPtr<UTakeRecorderDMXLibrarySource>> CustomizedDMXRecorders;` — Cache of the TakeRecorder sources being customized by the DetailsView that created this customization
- L39 _private member_ `TSharedPtr<IPropertyHandle> StructHandle;` — Used to generate Change events on the root DMX Take Recorder objects

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DMXEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXEditor, Log, All);`
- L9 _macro_ `#define UE_LOG_DMXEDITOR(Verbosity, Format, ...) \`
- L14 _macro_ `#define UE_CLOG_DMXEDITOR(Conditional, Verbosity, Format, ...) \`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DMXEditorMacros.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define DMXEDITOR_GETENUMSTRING(ETypeName, EnumVal) StaticEnum<ETypeName>()->GetNameStringByValue(static_cast<int64>(EnumVal))`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DMXEditorTabNames.h` (Private)


#### struct `UE::DMX::FDMXEditorTabNames`  
`struct FDMXEditorTabNames`  
_L11-36_
- desc: DMX editor tabs identifiers
- L14 _public member_ `static const FName ChannelsMonitor;` — The tab id for the channels monitor tab
- L17 _public member_ `static const FName ActivityMonitor;` — The tab id for the activity monitor tab
- L20 _public member_ `static const FName ConflictMonitor;` — The tab id for the conflict monitor tab
- L23 _public member_ `static const FName PatchTool;` — The tab id for the patch tool tab
- L26 _public member_ `static const FName DMXLibraryEditor;` — The tab id for the dmx library editor tab
- L29 _public member_ `static const FName DMXFixtureTypesEditor;` — The tab id for the dmx fixture types tab
- L32 _public member_ `static const FName DMXFixturePatchEditor;` — The tab id for the dmx fixture patch tab
- L35 _public prototype_ `FDMXEditorTabNames() = delete;` — Disable default constructor

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DMXPhysicalUnitToDefaultValueRange.h` (Private)


#### struct `UE::DMX::FDMXPhysicalUnitToDefaultValueRange`  
`struct FDMXPhysicalUnitToDefaultValueRange`  
_L10-18_
- L13 _public prototype_ `static const TPair<double, double>& GetValueRange(EDMXGDTFPhysicalUnit PhysicalUnit);` — Returns the value range for specified physical unit
- L17 _private member_ `static const TMap<EDMXGDTFPhysicalUnit, TPair<double, double>> PhysicalUnitToValueRangeMap;` — A map to list all GDTF compliant Physical Units and their matching Physical Value default ranges.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DragDrop/DMXEntityDragDropOp.h` (Private)


#### class `FDMXEntityDragDropOperation`  
`class FDMXEntityDragDropOperation : public FDragDropOperation , public FGCObject`  
_L20-73_
- inherits: `FDragDropOperation,FGCObject`
- L25 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMXEntityDragDropOperation, FDragDropOperation) FDMXEntityDragDropOperation(UDMXLibrary* InLibrary, const TArray<TWeakObjectPtr<UDMXEntity>>& InEntities);`
- L32 _protected prototype_ `virtual void Construct() override;` — Constructs the tooltip widget that follows the mouse
- L35 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L36 _protected function_ `virtual FString GetReferencerName() const override`
- L44 _public function_ `const TArray<TWeakObjectPtr<UDMXEntity>>& GetDraggedEntities() const` — Returns the entities dragged with this drag drop op
- L47 _public function_ `const FText& GetDraggedEntitiesName() const` — Returns the dragged entity's names or the first of the dragged entities names
- L50 _public prototype_ `TArray<UClass*> GetDraggedEntityTypes() const;` — Returns the types of the entities
- L53 _public prototype_ `void SetFeedbackMessageError(const FText& Message);` — Sets the cursor decorrator to show an error sign and a message
- L56 _public prototype_ `void SetFeedbackMessageOK(const FText& Message);` — Sets the cursor decorrator to show an ok sign and a message
- L59 _public prototype_ `void SetFeedbackMessage(const FSlateBrush* Icon, const FText& Message);` — Sets the cursor decorator to show an icon and a message
- L62 _public prototype_ `void SetCustomFeedbackWidget(const TSharedRef<SWidget>& Widget);` — Sets a custom cursor decorator
- L66 _private member_ `TObjectPtr<UDMXLibrary> DraggedFromLibrary;` — The library that the entites were dragged out from
- L69 _private member_ `TArray<TWeakObjectPtr<UDMXEntity>> DraggedEntities;` — The entities being draged with this drag drop op
- L72 _private member_ `FText DraggedEntitiesName;` — Name of the entity being dragged or entities type for several ones

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DragDrop/DMXEntityFixturePatchDragDropOp.h` (Private)


#### class `FDMXEntityFixturePatchDragDropOperation`  
`class FDMXEntityFixturePatchDragDropOperation : public FDragDropOperation`  
_L10-33_
- inherits: `FDragDropOperation`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMXEntityDragDropOperation, FDragDropOperation) FDMXEntityFixturePatchDragDropOperation(const TMap<TWeakObjectPtr<UDMXEntityFixturePatch>, int64>& FixturePatchToAbsoluteChannelOffsetMap);`
- L25 _public prototype_ `virtual ~FDMXEntityFixturePatchDragDropOperation();` — Destructor
- L28 _public function_ `const TMap<TWeakObjectPtr<UDMXEntityFixturePatch>, int64>& GetFixturePatchToAbsoluteChannelOffsetMap() const` — Returns Each Fixture Patch being dragged, along with it's channel offset from the anchor position.
- L32 _protected member_ `TMap<TWeakObjectPtr<UDMXEntityFixturePatch>, int64> FixturePatchToAbsoluteChannelOffsetMap;` — Each Fixture Patch being dragged, along with it's channel offset from the anchor position.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DragDrop/DMXFixtureFunctionDragDropOp.h` (Private)


#### class `FDMXFixtureFunctionDragDropOp`  
`class FDMXFixtureFunctionDragDropOp : public FDecoratedDragDropOp`  
_L12-30_
- inherits: `FDecoratedDragDropOp`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMXFixtureFunctionDragDropOp, FDecoratedDragDropOp) FDMXFixtureFunctionDragDropOp(TSharedPtr<SDMXFixtureTypeFunctionsEditorFunctionRow> InRow);`
- L20 _public prototype_ `void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent);`
- L22 _public member_ `TSharedPtr<SWidget> DecoratorWidget;`
- L24 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L29 _public member_ `TWeakPtr<SDMXFixtureTypeFunctionsEditorFunctionRow> Row;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/DragDrop/DMXFixtureMatrixDragDropOp.h` (Private)


#### class `FDMXFixtureMatrixDragDropOp`  
`class FDMXFixtureMatrixDragDropOp : public FDecoratedDragDropOp`  
_L12-30_
- inherits: `FDecoratedDragDropOp`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMXFixtureMatrixDragDropOp, FDecoratedDragDropOp) FDMXFixtureMatrixDragDropOp(TSharedPtr<SDMXFixtureTypeFunctionsEditorMatrixRow> InRow);`
- L20 _public prototype_ `void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent);`
- L22 _public member_ `TSharedPtr<SWidget> DecoratorWidget;`
- L24 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L29 _public member_ `TWeakPtr<SDMXFixtureTypeFunctionsEditorMatrixRow> Row;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Exporters/DMXFixtureTypeToGDTFConverter.h` (Private)


#### class `UE::DMX::GDTF::FDMXFixtureTypeToGDTFConverter`  
`class FDMXFixtureTypeToGDTFConverter`  
_L27-69_
- desc: Converts a Fixture Type to a GDTF. Internally caches of each collect, and finally assembles the GDTF.
- L31 _public prototype_ `static TSharedPtr<FXmlFile> Convert(const UDMXEntityFixtureType* UnrealFixtureType);` — Converts the Fixture Type to a GDTF description
- L35 _private prototype_ `TSharedRef<FDMXGDTFFixtureType> CreateFixtureType(const UDMXEntityFixtureType& UnrealFixtureType);` — Creates the GDTF Fixture Type
- L38 _private prototype_ `void CreateAttributeDefinitions(const UDMXEntityFixtureType& UnrealFixtureType, const TSharedRef<FDMXGDTFFixtureType>& GDTFFixtureType);` — Creates Attribute Aefinitions
- L41 _private prototype_ `void CreateModels(const UDMXEntityFixtureType& UnrealFixtureType, const TSharedRef<FDMXGDTFFixtureType>& GDTFFixtureType);` — Creates Models
- L44 _private prototype_ `void CreateGeometryCollect(const UDMXEntityFixtureType& UnrealFixtureType, const TSharedRef<FDMXGDTFFixtureType>& GDTFFixtureType);` — Creates the Geometry Collect
- L47 _private prototype_ `void CreateDMXModes(const UDMXEntityFixtureType& UnrealFixtureType, const TSharedRef<FDMXGDTFFixtureType>& GDTFFixtureType);` — Creates DMX Modes
- L50 _private prototype_ `void CreateDMXChannels(const FDMXFixtureMode& UnrealMode, const TSharedRef<FDMXGDTFDMXMode>& GDTFDMXMode);` — Creates DMX Channels for specified mode
- L53 _private prototype_ `void CreateLogicalChannel(const FDMXFixtureFunction& UnrealFunction, const TSharedRef<FDMXGDTFDMXChannel>& GDTFDMXChannel, const FString& GDTFAttribute);` — Creates a Logical Channel for the DMX Channel, using an Unreal Function for as input
- L56 _private prototype_ `void CreateLogicalChannel(const FDMXFixtureCellAttribute& UnrealCellAttribute, const TSharedRef<FDMXGDTFDMXChannel>& GDTFDMXChannel, const FString& GDTFAttribute);` — Creates a Logical Channel for the DMX Channel, using an Unreal Cell Attribute as the input
- L59 _private prototype_ `void CrateChannelFunction(const FDMXFixtureFunction& UnrealFunction, const TSharedRef<FDMXGDTFLogicalChannel>& GDTFLogicalChannel, const FString& GDTFAttribute);` — Creates a Channel Function for the Logical Channel, using an Unreal Function for as input
- L62 _private prototype_ `void CrateChannelFunction(const FDMXFixtureCellAttribute& UnrealCellAttribute, const TSharedRef<FDMXGDTFLogicalChannel>& GDTFLogicalChannel, const FString& GDTFAttribute);` — Creates a Channel Function for the Logical Channel, using an Unreal Cell Attribute as the input
- L65 _private member_ `TArray<FDMXFixtureModeWithBaseGeometry> ModesWithBaseGeometry;` — Map of Modes with their base geometry
- L68 _private member_ `TArray<FDMXFixtureFunctionWithControlledGeometry> FunctionsWithControlledGeometry;` — Map of Functions with the geometry they control

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Exporters/DMXFixtureTypeToGDTFGeometryFactory.h` (Private)


#### struct `UE::DMX::GDTF::Internal::FDMXUniqueModeGeometry`  
`struct FDMXUniqueModeGeometry`  
_L21-47_
- L23 _public prototype_ `FDMXUniqueModeGeometry(const FDMXFixtureMode& Mode);`
- L25 _public member_ `uint32 TotalNumChannels = 0;`
- L27 _public member_ `bool bIsMatrix = false;`
- L28 _public member_ `bool bWithPan = false;`
- L29 _public member_ `bool bWithTilt = false;`
- L31 _public function_ `bool operator==(const FDMXUniqueModeGeometry& Other) const`

#### struct `UE::DMX::GDTF::FDMXFixtureModeWithBaseGeometry`  
`struct FDMXFixtureModeWithBaseGeometry`  
_L51-57_
- desc: A struct that links a mode to its base geometry
- L53 _public prototype_ `FDMXFixtureModeWithBaseGeometry(const FDMXFixtureMode* InModePtr, TSharedRef<const FDMXGDTFGeometry> InBaseGeometry);`
- L55 _public member_ `const FDMXFixtureMode* ModePtr = nullptr;`
- L56 _public member_ `const TSharedRef<const FDMXGDTFGeometry> BaseGeometry;`

#### struct `UE::DMX::GDTF::FDMXFixtureFunctionWithControlledGeometry`  
`struct FDMXFixtureFunctionWithControlledGeometry`  
_L60-67_
- desc: A struct that links a function to its controlled geometry
- L62 _public prototype_ `FDMXFixtureFunctionWithControlledGeometry(const FDMXFixtureMode* InModePtr, const FDMXFixtureFunction* InFunctionPtr, TSharedRef<const FDMXGDTFGeometry> InControlledGeometry);`
- L64 _public member_ `const FDMXFixtureMode* ModePtr = nullptr;`
- L65 _public member_ `const FDMXFixtureFunction* FunctionPtr = nullptr;`
- L66 _public member_ `const TSharedRef<const FDMXGDTFGeometry> ControlledGeometry;`

#### class `UE::DMX::GDTF::FDMXFixtureTypeToGDTFGeometryFactory`  
`class FDMXFixtureTypeToGDTFGeometryFactory : public FNoncopyable`  
_L70-122_
- inherits: `FNoncopyable`
- desc: Helper to build geometries for the Fixture Type
- L73 _private typedef_ `using FDMXUniqueModeGeometry = Internal::FDMXUniqueModeGeometry;`
- L76 _public prototype_ `FDMXFixtureTypeToGDTFGeometryFactory(const UDMXEntityFixtureType& InFixtureType, const TSharedRef<FDMXGDTFGeometryCollect>& InBaseGeometryCollect);`
- L79 _public prototype_ `TArray<FDMXFixtureModeWithBaseGeometry> GetModesWithBaseGeometry() const;` — Returns an array of functions with their linked geometry
- L82 _public prototype_ `TArray<FDMXFixtureFunctionWithControlledGeometry> GetFunctionsWithControlledGeometry() const;` — Returns an array of functions with their linked geometry
- L84 _public member_ `static const FName CellsModelName;`
- L86 _public member_ `static const FName BaseGeometryName;`
- L87 _public member_ `static const FName PanGeometryName;`
- L88 _public member_ `static const FName HeadGeometryName;`
- L89 _public member_ `static const FName BeamGeometryName;`
- L90 _public member_ `static const FName MatrixBeamGeometryName;`
- L92 _public member_ `static const FName PanAttributeName;`
- L93 _public member_ `static const FName TiltAttributeName;`
- L97 _private prototype_ `void BuildGeometries();` — Builds all geometries
- L100 _private prototype_ `void BuildGeometry(const FDMXFixtureMode& Mode);` — Builds the geometry for a mode
- L103 _private prototype_ `TSharedRef<FDMXGDTFGeometry> GetOrCreateMatrixBeamGeometryInstance() const;` — Gets the matrix beam instance, creates it if it doesn't exist yet
- L106 _private prototype_ `TSharedRef<FDMXGDTFAxisGeometry> AddYoke(const TSharedRef<FDMXGDTFGeometry>& OuterGeometry);` — Adds a yoke geometry child to the outer geometry
- L109 _private prototype_ `TSharedRef<FDMXGDTFAxisGeometry> AddHead(const TSharedRef<FDMXGDTFGeometry>& OuterGeometry);` — Adds a head geometry child to the outer geometry
- L112 _private prototype_ `TSharedRef<FDMXGDTFBeamGeometry> AddBeam(const TSharedRef<FDMXGDTFGeometry>& OuterGeometry);` — Adds a beam geometry child to the outer geometry
- L115 _private prototype_ `void BuildMatrixGeometryReferences(const FDMXFixtureMode& Mode, const TSharedRef<FDMXGDTFGeometry>& OuterGeometry);` — Builds geometry references for a matrix
- L118 _private member_ `TMap<FDMXUniqueModeGeometry, TSharedRef<FDMXGDTFGeometry>> UniqueModeGeometryToGeometryMap;` — A map unique matrix definitions with teir base geometry, to reuse.
- L120 _private member_ `const UDMXEntityFixtureType& FixtureType;`
- L121 _private member_ `const TSharedRef<FDMXGDTFGeometryCollect>& BaseGeometryCollect;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L19 _namespace_ `namespace Internal` (scope `UE::DMX::GDTF`)
- L40 _function_ `friend uint32 GetTypeHash(const FDMXUniqueModeGeometry& UniqueMatrixDefinition)` (scope `UE::DMX::GDTF::Internal`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Exporters/DMXMVRExportOptions.h` (Private)


#### class `UDMXMVRExportOptions`  
`class UDMXMVRExportOptions : public UObject`  
_L10-35_
- reflection: `UCLASS(Config = DMXEditor)`
- inherits: `UObject`
- L18 _public member_ `bool bConsiderLevel = true;` — `UPROPERTY(EditAnywhere, Category = "Level Options")` — If checked, exports the fixtures with transforms as in the current level
- L22 _public member_ `bool bExportPatchesNotPresentInWorld = true;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bConsiderLevel", HideEditConditionToggle, EditConditionHides), Category = "Level Options")` — If checked, exports patches that are not in use in the level
- L26 _public member_ `bool bUseTransformsFromLevel = true;` — `UPROPERTY(EditAnywhere, Meta = (EditCondition = "bConsiderLevel", HideEditConditionToggle, EditConditionHides), Category = "Level Options")` — If checked, exports the fixtures with transforms as in the current level
- L30 _public member_ `bool bCreateMultiPatchFixtures = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Meta = (EditCondition = "bConsiderLevel", HideEditConditionToggle, EditConditionHides, DisplayName = "Create Multi Patch Fixtures (experimental)"), Category = "Level Options")` — If checked, creates individual MVR Fixtures for each Fixture that uses the same Patch in the Level.
- L34 _public member_ `bool bCanceled = false;` — `UPROPERTY(Transient)` — If set to true, the import was canceled

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Exporters/DMXMVRExporter.h` (Private)


#### class `UE::DMX::FDMXMVRExporter`  
`class FDMXMVRExporter`  
_L22-55_
- desc: Helper class to export a DMX Library as MVR file
- L26 _public prototype_ `static void Export(UDMXLibrary* DMXLibrary, const FString& DesiredName = TEXT(""));` — Exports the DMX Library as MVR File
- L30 _private prototype_ `void ExportInternal(UDMXLibrary* InDMXLibrary, const FString& InDesiredName, FText& OutErrorReason, FString& OutFilePathAndName);` — Exports the DMX Library as MVR File. If OutErrorReason is not empty there were issues with the export.
- L33 _private prototype_ `void UpdateExportOptions(const UDMXLibrary& DMXLibrary) const;` — Updates the MVR export options. Returns false if the import was canceled
- L36 _private prototype_ `TMap<const UDMXComponent*, const AActor*> GetDMXComponentToActorMap() const;` — Builds the DMX component to actor map
- L39 _private prototype_ `[[nodiscard]] bool ZipGeneralSceneDescription(const TSharedRef<FDMXZipper>& Zip, const UDMXMVRGeneralSceneDescription* GeneralSceneDescription, FText& OutErrorReason);` — Zips the GeneralSceneDescription.xml
- L42 _private prototype_ `[[nodiscard]] bool ZipGDTFs(const TSharedRef<FDMXZipper>& Zip, UDMXLibrary* DMXLibrary);` — Zips the GDTFs from the Library
- L45 _private prototype_ `void ZipThirdPartyData(const TSharedRef<FDMXZipper>& Zip, const UDMXMVRGeneralSceneDescription* GeneralSceneDescription);` — Zips 3rd Party Data from the MVR Asset Import Data
- L48 _private prototype_ `const TSharedPtr<FXmlFile> CreateSourceGeneralSceneDescriptionXmlFile(const UDMXMVRGeneralSceneDescription* GeneralSceneDescription) const;` — Creates an General Scene Description Xml File from the MVR Source, as it was imported
- L54 _private prototype_ `const TArray64<uint8>& RefreshSourceDataAndFixtureType(UDMXEntityFixtureType& FixtureType, UDMXGDTFAssetImportData& InOutGDTFAssetImportData) const;` — Gets raw source data or creates (possibly empty) source data where the source data is not present. Prior 5.1 there was no source data stored. Offers a dialog to load missing data

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Exporters/DMXMVRXmlMergeUtility.h` (Private)


#### class `FDMXXmlMergeUtility`  
`class FDMXXmlMergeUtility`  
_L15-45_
- desc: Utility to merge two General Scene Description Xmls, prefers primary for duplicate entries. Not a generic xml merger.
- L19 _public prototype_ `static TSharedPtr<FXmlFile> Merge(const UDMXMVRGeneralSceneDescription* GeneralSceneDescription, const TSharedRef<FXmlFile>& OtherXml);` — Merges the secondary General Scene Description Xml into the GeneralSceneDescription from engine. Returns an Xml File of the merged files or nullptr if data couldn't be merged.
- L23 _private prototype_ `TSharedPtr<FXmlFile> MergeInternal(const UDMXMVRGeneralSceneDescription* GeneralSceneDescription, const TSharedRef<FXmlFile>& OtherXml);` — Merges two General Scene Description Xmls
- L26 _private prototype_ `TArray<FXmlNode*> AcquireAdditionalData(const TSharedRef<FXmlFile>& Xml);` — Acquires additional Data nodes, considering the UnrealEngineDataNode already being present
- L29 _private prototype_ `const FXmlNode* AcquireAdditionalAUXData(const TSharedRef<FXmlFile>& Xml);` — Acquires additional AUXData nodes (child of Scene)
- L32 _private prototype_ `void MergeScenes(const UDMXMVRGeneralSceneDescription* GeneralSceneDescription, FXmlNode* InOutPrimarySceneNode, const FXmlNode* InSecondarySceneNode);` — Merges the secondary scene into the primary
- L35 _private prototype_ `TArray<FGuid> GetFixtureUUIDs(const UDMXMVRGeneralSceneDescription* GeneralSceneDescription);` — Acquires additional AUXData nodes (child of Scene)
- L38 _private prototype_ `FXmlNode* GetSceneNode(const TSharedRef<FXmlFile>& Xml);` — Returns the scene node of the GeneralSceneDescription Xml File
- L41 _private prototype_ `void AddXmlNodeWithChildren(FXmlNode* ParentTarget, const FXmlNode* ChildToAdd, const FString& IgnoredTag = FString());` — Adds source node to target with all its children. Optionaly ignores Nodes that specify a Tag
- L44 _private prototype_ `FXmlNode* FindMatchingMVRNode(const FXmlNode* ParentNode, const FXmlNode* Child);` — Tries ot find a Node in Parent (of Xml File A) that matches Child (of Xml File B)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Exporters/DMXUnrealToGDTFAttributeConversion.h` (Private)


#### class `UE::DMX::GDTF::FDMXUnrealToGDTFAttributeConversion`  
`class FDMXUnrealToGDTFAttributeConversion`  
_L11-98_
- L15 _public function_ `static FName ConvertUnrealToGDTFAttribute(const FName& InUnrealAttribute)` — Creates a GDTF attribute from an unreal attribute
- L44 _public function_ `static FName GetPrettyFromGDTFAttribute(const FName& InGDTFAttribute)`
- L58 _public function_ `static FName GetFeatureGroupForGDTFAttribute(const FName& InGDTFAttribute)` — Creates a GDTF feature group for a GDTF Attribute
- L72 _public function_ `static FName GetFeatureForGDTFAttribute(const FName& InGDTFAttribute)` — Creates a GDTF feature for a GDTF Attribute
- L87 _private member_ `static const TMap<FName, FName> UnrealToGDTFAttributeMap;` — Conversion from Unreal attributes to GDTF attributes. See also how UDMXProtocolSettings::Attributes is initialized and applied.
- L90 _private member_ `static const TMap<FName, FName> GDTFAttributeToPrettyMap;` — Defines pretty attribute names for GDTF attribute names
- L97 _private member_ `static const TMap<FName, TPair<FName, FName>> GDTFAttributeToFeatureMap;` — Defines attributes that should be assigned to a specific feature group. Assumes that GDTF and not Unreal attributes are used.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXGDTFFactory.h` (Private)


#### class `UDMXGDTFFactory`  
`class UDMXGDTFFactory : public UFactory , public FReimportHandler`  
_L15-52_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory,FReimportHandler`
- L22 _public prototype_ `UDMXGDTFFactory();`
- L25 _public prototype_ `virtual bool DoesSupportClass(UClass * Class) override;`
- L26 _public prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L27 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled);`
- L28 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L32 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L33 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L34 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L39 _private prototype_ `[[nodiscard]] bool GetOptionsFromDialog(UObject* Parent);` — Shows an options dialog that initializes members. If false is returned, the import should be canceled
- L42 _private member_ `bool bShowOptions = false;` — If true, shows an options dialog. Can be false for example when reimporting
- L45 _private member_ `bool bImportAll = false;` — If true, all content of the GDTF should be imported
- L48 _private member_ `bool bOperationCanceled = false;` — If true, importing was canceled
- L51 _private member_ `TObjectPtr<UDMXGDTFImportUI> ImportUI;` — `UPROPERTY(transient)`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXGDTFImportUI.h` (Private)


#### class `UDMXGDTFImportUI`  
`class UDMXGDTFImportUI : public UObject`  
_L11-33_
- reflection: `UCLASS(config = Editor, HideCategories=Object, MinimalAPI)`
- inherits: `UObject`
- L17 _public prototype_ `UDMXGDTFImportUI();`
- L19 _public prototype_ `void ResetToDefault();`
- L23 _public member_ `bool bUseSubDirectory = true;` — `UPROPERTY(EditAnywhere, Config, Category = "DMX")`
- L26 _public member_ `bool bImportXML = true;` — `UPROPERTY(EditAnywhere, Config, Category = "DMX")`
- L29 _public member_ `bool bImportTextures = true;` — `UPROPERTY(EditAnywhere, Config, Category = "DMX")`
- L32 _public member_ `bool bImportModels = true;` — `UPROPERTY(EditAnywhere, Config, Category = "DMX")`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXGDTFImporter.h` (Private)


#### struct `UE::DMX::FDMXGDTFImportArgs`  
`struct FDMXGDTFImportArgs`  
_L16-29_
- L19 _public function_ `FDMXGDTFImportArgs() : Parent(nullptr) , Name(NAME_None) , Flags(RF_NoFlags)`
- L25 _public member_ `TWeakObjectPtr<UObject> Parent;`
- L26 _public member_ `FName Name;`
- L27 _public member_ `FString Filename;`
- L28 _public member_ `EObjectFlags Flags;`

#### class `UE::DMX::FDMXGDTFImporter`  
`class FDMXGDTFImporter`  
_L33-54_
- desc: Imports a GDTF asset.
- L37 _public prototype_ `[[nodiscard]] static UDMXImportGDTF* Import(const UDMXGDTFFactory& InImportFactory, const FDMXGDTFImportArgs& InImportArgs, FText& OutErrorReason);` — Tries to import a GDTF, using params from the import factory. Returns the resulting GDTF object or nullptr if no GDTF asset could be created.
- L41 _private prototype_ `FDMXGDTFImporter(const FDMXGDTFImportArgs& InImportArgs);` — Private constructor
- L44 _private prototype_ `UDMXImportGDTF* ImportInternal(const UDMXGDTFFactory& InImportFactory, FText& OutErrorReason);` — Non-static implementation
- L47 _private prototype_ `UDMXImportGDTF* CreateGDTF(const UDMXGDTFFactory& InImportFactory, FText& OutErrorReason) const;` — Creates the GDTF asset
- L50 _private member_ `const FDMXGDTFImportArgs& ImportArgs;` — Args for this importer
- L53 _private member_ `TSharedPtr<FDMXZipper> Zip;` — The GDTF File as zip

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXGDTFToFixtureTypeConverter.h` (Private)


#### class `UE::DMX::GDTF::FDMXGDTFToFixtureTypeConverter`  
`class FDMXGDTFToFixtureTypeConverter`  
_L27-48_
- desc: This is a 5.1 private editor only workaround to initialize Fixture Types from GDTF assets. Required since DMXImportGDTF does not hold required data, hence UDMXEntityFixtureType::SetModesFromDMXImport cannot create matrix fixture types. Opeted for this workaround since it would require to rework the entirety of the GDTF implementation to hold its data correctly. This exceeds planed features of 5.1 and is a planned feature for 5.2.
- L31 _public prototype_ `static bool ConvertGDTF(UDMXEntityFixtureType& FixtureType, const UDMXImportGDTF& InGDTF, const bool bUpdateFixtureTypeName);` — Imports the modes directly from the asset import data
- L35 _private prototype_ `bool ConvertGDTFInternal(UDMXEntityFixtureType& InOutFixtureType, const UDMXImportGDTF& InGDTF, const bool bUpdateFixtureTypeName) const;` — Imports the modes directly from the asset import data. Non-static implementation
- L38 _private prototype_ `bool GenerateMode(const TSharedPtr<FDMXGDTFFixtureType>& InFixtureTypeNode, const TSharedPtr<FDMXGDTFDMXMode>& InDMXModeNode, FDMXFixtureMode& OutMode) const;` — Generates a Mode from specified Nodes. Returns true on success.
- L41 _private prototype_ `void CleanupMode(FDMXFixtureMode& InOutMode) const;` — Makes sure the mode can be used by the engine
- L44 _private prototype_ `void CleanupAttributes(UDMXEntityFixtureType& InOutFixtureType) const;` — Makes sure that attributes are replaced with attributes specified in protocol settings where possible
- L47 _private prototype_ `TArray<const FXmlNode*> GetChildrenRecursive(const FXmlNode& ParentNode) const;` — Returns all nodes that are decendants of the node

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMX` (scope `UE`)
- L14 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXLibraryFromMVRImportOptions.h` (Private)


#### class `UDMXLibraryFromMVRImportOptions`  
`class UDMXLibraryFromMVRImportOptions : public UObject`  
_L24-70_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Import Options when importing an MVR File as DMX Library. Note: - A MVR File Path and Name is expected to be set. - bCancelled has to be set to true when the user cancels import while Options here are presented.
- L31 _public prototype_ `void ApplyOptions(UDMXLibrary* DMXLibrary);` — Applies the options to the project (e.g. port changes).
- L35 _public member_ `bool bIsReimport = false;` — `UPROPERTY()` — If true, show options for Reimport
- L38 _public member_ `bool bCancelled = false;` — Set to true if the user decided to cancel the import while being presented Options here
- L41 _public member_ `FString Filename;` — File Path and Name of the MVR file for which these options are displayed
- L45 _public member_ `bool bCreateNewDMXLibrary = true;` — `UPROPERTY(EditAnywhere, Category = "Reimport")` — If checked, creates a new DMX Library
- L49 _public member_ `TObjectPtr<UDMXLibrary> ImportIntoDMXLibrary;` — `UPROPERTY(EditAnywhere, Category = "Reimport", Meta = (DisplayName = "Import into DMX Library", EditCondition = "!bCreateNewDMXLibrary", EditConditionHides))` — Imports the MVR into the specified DMX Library. Note this will not merge, but clear Patches in the DMX Library.
- L53 _public member_ `bool bReimportExisitingGDTFs = true;` — `UPROPERTY(EditAnywhere, Category = "Reimport")` — If checked, reimports GDTF that were previously imported
- L57 _public member_ `bool bUpdateInputPort = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Ports")` — If checked, updates the specified Input Port to span the Universe range of all Patches in the MVR file, or creates a new Input Port if none exist.
- L61 _public member_ `FDMXInputPortReference InputPortToUpdate;` — `UPROPERTY(EditAnywhere, Category = "Ports", Meta = (ShowOnlyInnerProperties, EditCondition = "bUpdateInputPort", EditConditionHides))` — The Input Port which is updated
- L65 _public member_ `bool bUpdateOutputPort = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Ports")` — If checked, updates the specified Ouput Port to span the Universe range of all Patches in the MVR file, or creates a new Output Port if none exist.
- L69 _public member_ `FDMXOutputPortReference OutputPortToUpdate;` — `UPROPERTY(EditAnywhere, Category = "Ports", Meta = (ShowOnlyInnerProperties, EditCondition = "bUpdateOutputPort", EditConditionHides))` — The Output Port which is updated

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXLibraryFromMVRImporter.h` (Private)


#### class `FDMXLibraryFromMVRImporter`  
`class FDMXLibraryFromMVRImporter : public FGCObject`  
_L28-92_
- inherits: `FGCObject`
- desc: Imports an MVR file into a DMX Library. 1. LoadMVRFile. 2. CreateGDTFs 3. InitializeDMXLibrary Does not offer any merge options with an existing DMX Library. To merge an MVR file into an existing DMX Library, import the MVR file into a new DMX Library, then merge it with the existing.
- L33 _public prototype_ `[[nodiscard]] bool LoadMVRFile(const FString& InFilename);` — Loads the MVR File
- L36 _public prototype_ `void UpdateImportOptionsFromModalWindow(UDMXLibraryFromMVRImportOptions* InOutImportOptions, bool& bOutCancelled);` — Creates a modal window that allows the user to change import options.
- L49 _public prototype_ `void Import(UObject* InOuter, const FName& InName, EObjectFlags InFlags, UDMXLibraryFromMVRImportOptions* ImportOptions, UDMXLibrary*& OutDMXLibrary, TArray<UDMXImportGDTF*>& OutGDTFs, bool& bOutCancelled);` — Imports an MVR File into a newly created DMX Library. Creates GDTF assets and reimports if specified so in ImportOptions. @param InOuter			The outer in which the new objects will be created @param InName			The name of the DMX Library (GDTFs will be auto named) @param InFlag			Flags with which the new objects are constructed @param ImportOptions		Can be null. If set, displays a dialog where the user can configure the import. @param OutDMXLibrary		The resulting DMX Library @param OutGDTFs			The resulting GDTFs #param bOutCancelled		True if the import was cancelled
- L63 _public prototype_ `void Reimport(UDMXLibrary* InDMXLibrary, UDMXLibraryFromMVRImportOptions* InImportOptions, TArray<UDMXImportGDTF*>& OutGDTFs);`
- L67 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L68 _protected function_ `virtual FString GetReferencerName() const override`
- L76 _private prototype_ `UDMXMVRGeneralSceneDescription* CreateGeneralSceneDescription(UObject* Outer) const;` — Creates a General Scene Description from the MVR zip. Returns the General Scene Description or nullptr if not a valid MVR zip.
- L79 _private prototype_ `TArray<UDMXImportGDTF*> CreateGDTFs(UObject* InParent, EObjectFlags InFlags, bool bReimportExisting);` — Creates GDTF assets from the MVR
- L82 _private prototype_ `void InitializeDMXLibrary(UDMXLibrary* DMXLibrary, const TArray<UDMXImportGDTF*>& GDTFs);` — Initializes the DMX Library from the MVR data present and specified GDTFs
- L85 _private member_ `TObjectPtr<UDMXMVRGeneralSceneDescription> GeneralSceneDescription = nullptr;` — Temporary General Scene Description of the MVR File, or nullptr if not a valid MVR
- L88 _private member_ `TSharedPtr<FDMXZipper> Zip;` — Zip that holds the data
- L91 _private member_ `FString Filename;` — File name of the MVR File

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXMVRSceneActorFactory.h` (Private)


#### class `UDMXMVRSceneActorFactory`  
`class UDMXMVRSceneActorFactory : public UActorFactory`  
_L21-43_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L27 _public prototype_ `UDMXMVRSceneActorFactory();`
- L30 _public prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L31 _public prototype_ `virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;`
- L36 _private prototype_ `bool IsDMXLibraryAlreadySpawned(UWorld* World, UDMXLibrary* DMXLibrary) const;` — Returns true if the DMX Library is already spawned as an MVR Scene Actor in the world
- L39 _private prototype_ `void NotifyDMXLibraryAlreadySpawned();` — Creates a notification that the DMX Library is already spawned as an MVR Scene Actor in the world
- L42 _private member_ `TWeakPtr<SNotificationItem> DMXLibraryAlreadySpawnedNotification;` — Notification displayed when a DMX Library was already spawned

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/FixturePatchAutoAssignUtility.h` (Private)


#### struct `UE::DMXEditor::AutoAssign::Private::FAutoAssignElement`  
`struct FAutoAssignElement`  
_L22-61_
- desc: An element to auto assign. Uses absolute DMX space, e.g. Universe 1 Channel 1 == 512.
- L24 _public prototype_ `FAutoAssignElement(int64 LowerBoundInclusive, int64 UpperBoundExclusive);`
- L25 _public prototype_ `FAutoAssignElement(const TRange<int64>& InAbsoluteRange);`
- L26 _public prototype_ `FAutoAssignElement(UDMXEntityFixturePatch& FixturePatch);`
- L29 _public prototype_ `int64 GetLowerBoundValue() const;` — Returns the lower bound value, inclusive
- L32 _public prototype_ `int64 GetUpperBoundValue() const;` — Returns the upper bound value, exclusive
- L35 _public prototype_ `int64 GetSize() const;` — Returns the size
- L38 _public function_ `const TRange<int64>& GetRange() const` — Returns the element as range
- L41 _public prototype_ `void SetAbsoluteStartingChannel(int64 NewStartingAddress);` — Sets the absolute starting channel
- L44 _public prototype_ `void AlignAfter(const TSharedRef<FAutoAssignElement>& Other);` — Aligns this element after the other
- L47 _public prototype_ `void ApplyToPatch();` — If the element has a patch, writes the current range to the patch
- L50 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — Returns the fixture patch, or nullptr if the element has no patch
- L53 _private prototype_ `int32 GetUniverse() const;`
- L54 _private prototype_ `int32 GetChannel() const;`
- L57 _private member_ `TRange<int64> AbsoluteRange;` — The absolute range, starting from universe 0 absolute channel 0
- L60 _private member_ `TWeakObjectPtr<UDMXEntityFixturePatch> WeakFixturePatch;` — The corresponding fixture patch

#### class `UE::DMXEditor::AutoAssign::Private::FAutoAssignElementsUtility`  
`class FAutoAssignElementsUtility`  
_L69-93_
- desc: Auto-assigns elements to free ranges. Uses absolute channel values, e.g. Universe 1 Channel 1 == 512 resp. DMX_UNIVERSE_SIZE. Applies results to patches on success.
- L73 _public prototype_ `static int32 Assign(TArray<TSharedRef<FAutoAssignElement>> ElementsToAssign, int32 AssignToUniverse, int32 AssignToChannel);` — Assigns the elements. Returns the universe of the first assigned patch
- L76 _public prototype_ `static void Align(TArray<TSharedRef<FAutoAssignElement>> ElementsToAlign, bool bRetainStacks);` — Aligns the elements. If bRetainStacks is true, retains stacks instead of aligning them too.
- L79 _public prototype_ `static void Stack(TArray<TSharedRef<FAutoAssignElement>> ElementsToStack);` — Stacks the elements
- L82 _public prototype_ `static void SpreadOverUniverses(TArray<TSharedRef<FAutoAssignElement>> ElementsToSpread);` — Spreads the elements over universes
- L85 _public prototype_ `static void AutoAssign(const TArray<TSharedRef<FAutoAssignElement>>& FreeElements, TArray<TSharedRef<FAutoAssignElement>> AutoAssignElements);` — Auto-assigns a set of elements to free elements. Note, free elements need be in the range of { DMX_UNIVERSE_SIZE, std::numeric_limits<int64>::Max() ), ensured.
- L89 _private prototype_ `static bool AreElementsStacked(const TSharedRef<FAutoAssignElement>& FirstElement, const TSharedRef<FAutoAssignElement>& SecondElement);` — Returns true if the elements are stacked.
- L92 _private prototype_ `static bool EnsureValidPatchElements(const TArray<TSharedRef<FAutoAssignElement>>& Elements);` — Returns true if elments are in valid DMX range. Hits an ensure condition if elements are not valid.

#### enum `UE::DMXEditor::AutoAssign::EAutoAssignMode`  
`enum class EAutoAssignMode : uint8`  
_L99-105_
- L101 _public enumerator_ `UserDefinedChannel`
- L102 _public enumerator_ `SelectedUniverse`
- L103 _public enumerator_ `FirstReachableUniverse`
- L104 _public enumerator_ `AfterLastPatchedUniverse`

#### class `UE::DMXEditor::AutoAssign::FAutoAssignUtility`  
`class FAutoAssignUtility`  
_L108-144_
- desc: Utility to auto assign fixture patches.
- L112 _public prototype_ `static int32 Assign(TArray<UDMXEntityFixturePatch*> FixturePatches, int32 AssignToUniverse, int32 AssignToChannel);` — Aligns FixturePatches
- L115 _public prototype_ `static void Align(TArray<UDMXEntityFixturePatch*> FixturePatches);` — Aligns FixturePatches
- L118 _public prototype_ `static void Stack(TArray<UDMXEntityFixturePatch*> FixturePatches);` — Stacks FixturePatches
- L121 _public prototype_ `static void SpreadOverUniverses(TArray<UDMXEntityFixturePatch*> FixturePatches);` — Auto assigns FixturePatches, one patch per Universe. Returns the Universe the first patch was auto assigned to.
- L124 _public prototype_ `static int32 AutoAssign(EAutoAssignMode Mode, const TSharedRef<FDMXEditor>& DMXEditor, TArray<UDMXEntityFixturePatch*> FixturePatches, int32 UniverseUnderMouse = 0, int32 UserDefinedChannel = 0);` — Auto assigns FixturePatches. Returns the Universe the first patch was auto assigned to.
- L128 _private prototype_ `int32 AutoAssignInternal(EAutoAssignMode Mode, const TSharedRef<FDMXEditor>& DMXEditor, TArray<UDMXEntityFixturePatch*> FixturePatches, int32 UniverseUnderMouse = 0, int32 UserDefinedChannel = 0);` — Non-static implementation of auto assign
- L131 _private prototype_ `int64 FindAbsoluteStartingChannel(EAutoAssignMode Mode, const TSharedRef<FDMXEditor>& DMXEditor, const UDMXLibrary& DMXLibrary, const TArray<UDMXEntityFixturePatch*>& FixturePatches, int32 UniverseUnderMouse, int32 UserDefinedChannel) const;` — Finds the absolute starting channel from options
- L134 _private prototype_ `UDMXLibrary* GetDMXLibrary(TArray<UDMXEntityFixturePatch*> FixturePatches) const;` — Gets the DMX Library from the patches, or returns nullptr if a valid DMX Library cannot be deduced from patches
- L137 _private prototype_ `TArray<TSharedRef<Private::FAutoAssignElement>> CreateFreeElements(UDMXLibrary& DMXLibrary, const TArray<UDMXEntityFixturePatch*>& FixturePatches, int64 AbsoluteStartingChannel) const;` — Creates elements for ranges that are not patched in the DMX Library
- L140 _private prototype_ `TArray<TSharedRef<Private::FAutoAssignElement>> CreatePatchElements(TArray<UDMXEntityFixturePatch*> FixturePatches) const;` — Creates elements from patches. Note also creates elements for gaps between the patches to remember offsets
- L143 _private prototype_ `TArray<UDMXEntityFixturePatch*> FindOtherPatchesInLibrary(const UDMXLibrary& DMXLibrary, const TArray<UDMXEntityFixturePatch*>& FixturePatches) const;` — Helper to find other patches in the library

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMXEditor` (scope `UE`)
- L16 _namespace_ `namespace AutoAssign` (scope `UE::DMXEditor`)
- L16 _namespace_ `namespace Private` (scope `UE::DMXEditor::AutoAssign`)
- L97 _namespace_ `namespace UE`
- L97 _namespace_ `namespace DMXEditor` (scope `UE`)
- L97 _namespace_ `namespace AutoAssign` (scope `UE::DMXEditor`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Modes/DMXEditorApplicationMode.h` (Private)


#### struct `FDMXEditorApplicationMode`  
`struct FDMXEditorApplicationMode`  
_L15-24_
- desc: Holds different DMX Editor modes identifiers It could be more than one different layout for the editor
- L18 _public member_ `static const FName DefaultsMode;` — Default layout for DMX editor
- L20 _public prototype_ `static FText GetLocalizedMode(const FName InMode);`
- L23 _public prototype_ `FDMXEditorApplicationMode() = delete;` — No default constructor

#### class `FDMXEditorDefaultApplicationMode`  
`class FDMXEditorDefaultApplicationMode : public FApplicationMode`  
_L27-41_
- inherits: `FApplicationMode`
- desc: Holds tabs layout and configuration for DMX default application mode
- L30 _public prototype_ `FDMXEditorDefaultApplicationMode(TSharedPtr<FDMXEditor> InDMXEditor);`
- L33 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L37 _protected member_ `TWeakPtr<FDMXEditor> DMXEditorCachedPtr;`
- L40 _protected member_ `FWorkflowAllowedTabSet DefaultsTabFactories;` — Set of spawnable tabs in Class Defaults mode

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Sequencer/DMXAsyncDMXRecorder.h` (Private)


#### struct `FDMXFunctionChannelData`  
`struct FDMXFunctionChannelData`  
_L28-74_
- desc: Can hold data for a specific channel from the FDMXRecorder. Does not rely on the channel remaining valid Note, it is required to do this by channel so we can set all keyframes at once via SetKeys method
- L31 _public prototype_ `FDMXFunctionChannelData() = delete;`
- L33 _public prototype_ `FDMXFunctionChannelData(UDMXEntityFixturePatch* InFixturePatch, FDMXFixtureFunctionChannel* InFunctionChannel);`
- L38 _public member_ `TArray<FFrameNumber> Times;` — Time of each keyframe
- L41 _public member_ `TArray<FMovieSceneFloatValue> Values;` — Value of each keyframe
- L44 _public prototype_ `FDMXFixtureFunctionChannel* TryGetFunctionChannel(const UMovieSceneDMXLibrarySection* InMovieSceneDMXLibrarySection);` — Returns a ptr to the function channel if it still exists, or nullptr if it turned invalid
- L46 _public function_ `int32 GetLocalUniverseID() const`
- L48 _public function_ `const TWeakObjectPtr<UDMXEntityFixturePatch> GetFixturePatch() const`
- L50 _public function_ `const FName& GetAttributeName() const`
- L52 _public function_ `bool IsCellChannel() const`
- L54 _public function_ `FIntPoint GetCellCoordinate() const`
- L58 _private member_ `TWeakObjectPtr<UDMXEntityFixturePatch> FixturePatch;` — Raw ptr to the fixture patch of the channel, not guaranteed to remain valid
- L61 _private member_ `FDMXFixtureFunctionChannel* FunctionChannel;` — Raw ptr to the function channel, not guaranteed to remain valid
- L64 _private member_ `int32 LocalUniverseID;` — The local universe ID of the patch
- L67 _private member_ `FName AttributeName;` — The attribute name of teh function channel
- L70 _private member_ `bool bCellChannel;` — True if the channel is a matrix cell channel
- L73 _private member_ `FIntPoint CellCoordinate;` — The cell coordinate

#### class `FDMXAsyncDMXRecorder`  
`class FDMXAsyncDMXRecorder : public FRunnable , public FSingleThreadRunnable , public FGCObject , public TSharedFromThis<FDMXAsyncDMXRecorder>`  
_L78-171_
- inherits: `FRunnable,FSingleThreadRunnable,FGCObject,TSharedFromThis<FDMXAsyncDMXRecorder>`
- desc: Records DMX asynchronously to optimize performance yet minimize processing of data after recroding
- L85 _public prototype_ `FDMXAsyncDMXRecorder(UDMXLibrary* InDMXLibrary, UMovieSceneDMXLibrarySection* InMovieSceneDMXLibrarySection);`
- L87 _public prototype_ `virtual ~FDMXAsyncDMXRecorder();`
- L91 _protected prototype_ `virtual bool Init() override;`
- L92 _protected prototype_ `virtual uint32 Run() override;`
- L93 _protected prototype_ `virtual void Stop() override;`
- L97 _protected prototype_ `virtual void Tick() override;`
- L98 _protected prototype_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L102 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector & Collector) override;`
- L103 _protected function_ `virtual FString GetReferencerName() const override`
- L111 _public prototype_ `void StartRecording(double InRecordStartTime, FFrameNumber InRecordStartFrame, FFrameRate InTickResolution);` — Starts to record incoming DMX
- L114 _public prototype_ `void StopRecording();` — Stops the recording
- L117 _public prototype_ `int32 GetNumSignalsToProccess() const;` — Returns the number of signals that remain to be proccessed.
- L120 _public prototype_ `TArray<FDMXFunctionChannelData> GetRecordedData() const;` — Returns the recorded data.
- L124 _private member_ `TArray<FDMXFunctionChannelData> FunctionChannelDataArr;` — The actual recording, per fixutre function channel
- L128 _private prototype_ `FFrameNumber GetFrameNumberFromSignal(const FDMXSignalSharedRef& Signal) const;` — Returns the frame number from a signal
- L131 _private prototype_ `void Update();` — Processes newly received data
- L134 _private member_ `TSet<TSharedRef<FDMXRawListener>> RawListeners;` — Raw listener for the relevant ports
- L137 _private member_ `TMap<FDMXSignalSharedRef, int32 > SignalToLocalUniverseMap;` — Cache used during recording
- L140 _private member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — The library of the patches, gc'ed
- L143 _private member_ `TObjectPtr<UMovieSceneDMXLibrarySection> MovieSceneDMXLibrarySection;` — The library section to record, gc'ed
- L146 _private member_ `bool bRecordNormalizedValues;` — If true, records normalized values
- L149 _private member_ `double RecordStartTime;` — The time the recording started
- L152 _private member_ `FFrameNumber RecordStartFrame;` — The frame the recording started
- L155 _private member_ `FFrameRate TickResolution;` — The tick resolution of the recording
- L158 _private member_ `bool bStartAtCurrentTimecode;` — True if recording needs to start at the current time code
- L161 _private member_ `TAtomic<int32> NumSignalsToProccess;` — The number of signals to proccess
- L164 _private member_ `FRunnableThread* Thread;` — Thread that processes the data
- L167 _private member_ `bool bThreadStopping;` — True while the thread wasn't stopped
- L170 _private member_ `bool bListenersStopped;` — True when all listeners are stopped

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Sequencer/DMXLibrarySection.h` (Private)


#### class `FDMXLibrarySection`  
`class FDMXLibrarySection : public FSequencerSection`  
_L14-40_
- inherits: `FSequencerSection`
- desc: Editor implementation of DMX Library track sections
- L19 _public prototype_ `FDMXLibrarySection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);`
- L26 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& InObjectBinding) override;` — Called when the user right clicks the keyframes area of the track
- L29 _public prototype_ `virtual bool RequestDeleteCategory(const TArray<FName>& CategoryNamePath) override;` — Called when the user deletes a Patch section
- L32 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;` — Called when the user deletes a Patch's Function Channel section
- L39 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;` — The sequencer which is controlling this section

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Sequencer/DMXLibraryTrackEditor.h` (Private)


#### class `FDMXLibraryTrackEditor`  
`class FDMXLibraryTrackEditor : public FMovieSceneTrackEditor`  
_L15-68_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor for DMX Libraries.
- L21 _public prototype_ `FDMXLibraryTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor.
- L24 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Factory function
- L31 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;` — Provides the context menu custom options when right-clicking a DMX Library track
- L34 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;` — Adds the DMX Library track option to Sequencer's "Add Track" menu
- L37 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;` — Returns whether this track editor is suitable for the passed in type of track
- L40 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;` — Returns what types of Sequence the DMX Library track can be added to
- L43 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;` — Gets the icon for the DMX Library track
- L46 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;` — Builds the widget that goes on the right of the track node. In this case, the "+ Patch" menu.
- L49 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;` — Handles when a DMX Library asset is dragged into the Sequence editor
- L52 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;` — Returns editor customization of the sections
- L57 _private prototype_ `TSharedRef<SWidget> OnGetAddPatchMenuContent(UMovieSceneDMXLibraryTrack* DMXTrack);` — Provides the contents of the add Patch menu, displaying all Patches from this DMX Library.
- L60 _private prototype_ `void HandlePatchSelectedFromAddMenu(UMovieSceneDMXLibraryTrack* Track, UDMXEntityFixturePatch* Patch);` — Creates a Patch section using the selected Fixture Patch from the "+ Patch" menu
- L63 _private prototype_ `void HandleAddAllPatchesClicked(UMovieSceneDMXLibraryTrack* Track);` — Adds all Library's Patches as channels of the DMX Library track
- L66 _private prototype_ `void AddDMXLibraryTrackToSequence(const FAssetData& InAssetData);` — Creates a new DMX Library track on the active Sequence, using the selected DMX Library asset
- L67 _private prototype_ `void AddDMXLibraryTrackToSequenceEnterPressed(const TArray<FAssetData>& InAssetData);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Sequencer/MovieSceneDMXLibraryTrackRecorder.h` (Private)


#### class `UMovieSceneDMXLibraryTrackRecorder`  
`class UMovieSceneDMXLibraryTrackRecorder : public UMovieSceneTrackRecorder`  
_L32-78_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- desc: Track recorder implementation for DMX libraries Reuses logic of Animation/LiveLink Plugin in many areas.
- L39 _public prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentFrameTime) override;` — UMovieSceneTrackRecorder Interface
- L40 _public prototype_ `virtual void FinalizeTrackImpl() override;`
- L41 _public prototype_ `virtual void SetSectionStartTimecodeImpl(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) override;`
- L42 _public prototype_ `virtual UMovieSceneSection* GetMovieSceneSection() const override;`
- L43 _public prototype_ `virtual void StopRecordingImpl() override;`
- L44 _public prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L49 _public prototype_ `TWeakObjectPtr<UMovieSceneDMXLibraryTrack> CreateTrack(UMovieScene* InMovieScene, UDMXLibrary* Library, const TArray<FDMXEntityFixturePatchRef>& InFixturePatchRefs, bool bDiscardSamplesBeforeStart, bool bRecordNormalizedValues);` — Creates a track. We don't call UMovieSceneTrackRecorder::CreateTrack or CreateTrackImpl since that expects an  ObjectToRecord and a GUID which isn't needed.
- L53 _private member_ `TSharedPtr<FDMXAsyncDMXRecorder> AsyncDMXRecorder;` — Asnyc Recorder for DMX
- L56 _private member_ `TSet<TSharedPtr<FDMXRawListener>> RawListeners;` — The raw listeners for the ports of the library
- L59 _private member_ `bool bUseSourceTimecode;` — Whether or not we use timecode time or world time
- L62 _private member_ `TArray<FDMXEntityFixturePatchRef> FixturePatchRefs;` — `UPROPERTY()`
- L65 _private member_ `TWeakObjectPtr<UMovieSceneDMXLibraryTrack> DMXLibraryTrack;` — The DMXLibrary Track to record onto
- L68 _private member_ `TWeakObjectPtr<UMovieSceneDMXLibrarySection> DMXLibrarySection;` — Sections to record to on each track
- L71 _private member_ `double RecordStartTime;` — The time at the start of this recording section
- L74 _private member_ `FFrameNumber RecordStartFrame;` — The frame at the start of this recording section
- L77 _private member_ `bool bDiscardSamplesBeforeStart;` — If true, discards samples that were recorded before the actual recording start frame

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Sequencer/TakeRecorderDMXLibrarySource.h` (Private)


#### struct `FAddAllPatchesButton`  
`struct FAddAllPatchesButton`  
_L25-28_
- reflection: `USTRUCT()`
- desc: Empty struct to have it customized in DetailsView to display a button on the DMX Take Recorder properties. This is a required hack to customize the properties in the TakeRecorder DetailsView because it has a customization that overrides any class customization. So we need to tackle individual property types instead.

#### class `UTakeRecorderDMXLibrarySource`  
`class UTakeRecorderDMXLibrarySource : public UTakeRecorderSource`  
_L32-110_
- reflection: `UCLASS(Category = "DMX")`
- inherits: `UTakeRecorderSource`
- desc: A recording source for DMX data related to a DMX Library
- L38 _public prototype_ `UTakeRecorderDMXLibrarySource(const FObjectInitializer& ObjInit);`
- L42 _public member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (DisplayName = "DMX Library"))` — DMX Library to record Patches' Fixture Functions from
- L49 _public member_ `FAddAllPatchesButton AddAllPatchesDummy;` — `UPROPERTY(EditAnywhere, Transient, Category = "My Category", meta = (DisplayName = ""))` — Dummy property to be replaced with the "Add all patches" button. @see FAddAllPatchesButton
- L53 _public member_ `TArray<FDMXEntityFixturePatchRef> FixturePatchRefs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (DisplayName = "Fixture Patches"))` — The Fixture Patches to record from the selected Library
- L62 _public member_ `bool bRecordNormalizedValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Scene")` — If true, all values are recorded as normalized values (0.0 to 1.0). If false, values are recorded as absolute values, depending on the data type of a patch: 0-255 for 8bit, 0-65'536 for 16bit, 0-16'777'215 for 24bit. 32bit is not fully supported in this mode.
- L66 _protected function_ `virtual bool SupportsSubscenes() const override`
- L72 _public prototype_ `void AddAllPatches();` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Adds all Patches from the active DMX Library as recording sources
- L76 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;`
- L77 _private prototype_ `virtual void StartRecording(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame, class ULevelSequence* InSequence) override;`
- L78 _private prototype_ `virtual void StopRecording(class ULevelSequence* InSequence) override;`
- L79 _private prototype_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentTime) override;`
- L80 _private prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L81 _private prototype_ `virtual void AddContentsToFolder(UMovieSceneFolder* InFolder) override;`
- L82 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L83 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L87 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L88 _private prototype_ `virtual void PostLoad() override;`
- L95 _private prototype_ `void ResetPatchesLibrary();` — Make sure all EntityRefs don't display their Library property and that they use this source's DMX Library as their library.
- L99 _private member_ `bool bDiscardSamplesBeforeStart;` — Whether to discard samples with timecode that occurs before the start of recording
- L103 _private member_ `TObjectPtr<UMovieSceneDMXLibraryTrackRecorder> TrackRecorder;` — `UPROPERTY()` — Track recorder used by this source
- L109 _private member_ `TWeakObjectPtr<UMovieSceneDMXLibraryTrack> CachedDMXLibraryTrack;` — Stores an existing DMX Library track in the Sequence to be recorded or a new one created for recording. Set during PreRecording.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Tabs/DMXEditorTabFactories.h` (Private)


#### struct `FDMXEditorPropertyTabSummoner`  
`struct FDMXEditorPropertyTabSummoner : public FWorkflowTabFactory`  
_L16-25_
- inherits: `FWorkflowTabFactory`
- L19 _public function_ `FDMXEditorPropertyTabSummoner(const FName& InIdentifier, TSharedPtr<class FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(InIdentifier, InHostingApp)`
- L24 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`

#### struct `FDMXLibraryEditorTabSummoner`  
`struct FDMXLibraryEditorTabSummoner : public FDMXEditorPropertyTabSummoner`  
_L27-35_
- inherits: `FDMXEditorPropertyTabSummoner`
- L30 _public prototype_ `FDMXLibraryEditorTabSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp);`
- L32 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L34 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`

#### struct `FDMXEditorFixtureTypesSummoner`  
`struct FDMXEditorFixtureTypesSummoner : public FDMXEditorPropertyTabSummoner`  
_L37-48_
- inherits: `FDMXEditorPropertyTabSummoner`
- L40 _public prototype_ `FDMXEditorFixtureTypesSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp);`
- L42 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L44 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FDMXEditorFixturePatchSummoner`  
`struct FDMXEditorFixturePatchSummoner : public FDMXEditorPropertyTabSummoner`  
_L50-61_
- inherits: `FDMXEditorPropertyTabSummoner`
- L53 _public prototype_ `FDMXEditorFixturePatchSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp);`
- L55 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L57 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "DMXEditorTabFactories"`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Toolbars/DMXEditorToolbar.h` (Private)


#### class `FDMXEditorToolbar`  
`class FDMXEditorToolbar : public TSharedFromThis<FDMXEditorToolbar>`  
_L16-33_
- inherits: `TSharedFromThis<FDMXEditorToolbar>`
- L19 _public function_ `FDMXEditorToolbar(TSharedPtr<FDMXEditor> InDMXEditor) : DMXEditor(InDMXEditor)`
- L22 _public prototype_ `void AddCompileToolbar(TSharedPtr<FExtender> Extender);`
- L25 _public prototype_ `FSlateIcon GetStatusImage() const;` — Returns the current status icon for the blueprint being edited
- L28 _private prototype_ `void FillDMXLibraryToolbar(FToolBarBuilder& ToolbarBuilder);`
- L32 _protected member_ `TWeakPtr<FDMXEditor> DMXEditor;` — Pointer back to the blueprint editor tool that owns us

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/DMXEntityTreeNode.h` (Private)


#### class `FDMXEntityTreeNodeBase`  
`class FDMXEntityTreeNodeBase : public TSharedFromThis<FDMXEntityTreeNodeBase>`  
_L17-134_
- inherits: `TSharedFromThis<FDMXEntityTreeNodeBase>`
- desc: Abstract base class for nodes in a list of entities
- L21 _private prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L32 _public prototype_ `FDMXEntityTreeNodeBase(FDMXEntityTreeNodeBase::ENodeType InNodeType);` — Constructor
- L35 _public function_ `virtual ~FDMXEntityTreeNodeBase()` — Destructor
- L38 _public prototype_ `virtual bool CanRename() const = 0;` — @return Whether or not this object represents a node that can be renamed from the entities tree.
- L41 _public prototype_ `virtual FString GetDisplayNameString() const = 0;` — @return The string to be used in the tree display.
- L44 _public prototype_ `virtual FText GetDisplayNameText() const = 0;` — @return The name of this node in text.
- L47 _public prototype_ `virtual ENodeType GetNodeType() const;` — @return The type of this node.
- L50 _public prototype_ `virtual void AddChild(TSharedPtr<FDMXEntityTreeNodeBase> InChildPtr);` — Add a child node to this node
- L53 _public prototype_ `virtual void RemoveChild(TSharedPtr<FDMXEntityTreeNodeBase> InChildPtr);` — Remove a child node from this node
- L56 _public prototype_ `virtual void RemoveFromParent();` — Remove this node from its parent one
- L59 _public prototype_ `virtual const TArray<TSharedPtr<FDMXEntityTreeNodeBase>>& GetChildren() const;` — @return Child nodes for this object.
- L62 _public prototype_ `virtual void ClearChildren();` — Remove all child nodes from this node.
- L65 _public prototype_ `virtual void SortChildren();` — Sort children by name
- L68 _public prototype_ `virtual void SortChildren(TFunction<bool (const TSharedPtr<FDMXEntityTreeNodeBase>&, const TSharedPtr<FDMXEntityTreeNodeBase>&)> Predicate);` — Sort children using custom predicate
- L71 _public function_ `virtual TWeakPtr<FDMXEntityTreeNodeBase> GetParent() const` — @return This object's parent node (or an invalid reference if no parent is assigned).
- L74 _public prototype_ `virtual bool IsFlaggedForFiltration() const;` — Query that determines if this item should be filtered out or not
- L77 _public prototype_ `void UpdateCachedFilterState(bool bMatchesFilter, bool bUpdateParent);` — Refreshes this item's filtration state. Use bUpdateParent to make sure the parent's EFilteredState::ChildMatches flag is properly updated based off the new state
- L80 _public prototype_ `void SetExpansionState(bool bNewExpansionState);` — Update this node's desired expansion state for when there're no filters
- L83 _public function_ `bool GetExpansionState() const` — This node's desired expansion state for when there're no filters
- L86 _public prototype_ `void SetWarningStatus(const FText& InWarningToolTip);` — If the warning tool tip is not empty, the node will display a warning icon with said tool tip.
- L88 _public function_ `const FText& GetWarningStatus() const`
- L91 _public prototype_ `void SetErrorStatus(const FText& InErrorToolTip);` — If the error tool tip is not empty, the node will display an error icon with said tool tip.
- L93 _public function_ `const FText& GetErrorStatus() const`
- L96 _public prototype_ `bool operator<(const FDMXEntityTreeNodeBase& Other) const;` — Operator used when sorting categories by name/number
- L100 _protected prototype_ `void RefreshCachedChildFilterState(bool bUpdateParent);` — Updates the EFilteredState::ChildMatches flag, based off of children's current state
- L103 _protected prototype_ `void ApplyFilteredStateToParent();` — Used to update the EFilteredState::ChildMatches flag for parent nodes, when this item's filtration state has changed
- L105 _protected member_ `FText WarningToolTip;`
- L107 _protected member_ `FText ErrorToolTip;`
- L111 _private member_ `ENodeType NodeType;` — The type of the node
- L114 _private member_ `TWeakPtr<FDMXEntityTreeNodeBase> ParentNodePtr;` — Actual tree structure
- L117 _private member_ `TArray<TSharedPtr<FDMXEntityTreeNodeBase>> Children;` — The children of the node
- L120 _private member_ `bool bShouldBeExpanded = false;` — Register whether the node should be expanded when there's no search filter text
- L133 _private member_ `uint8 FilterFlags = static_cast<uint8>(EFilteredState::Unknown);`

#### enum `FDMXEntityTreeNodeBase::ENodeType`  
`enum class ENodeType : uint8`  
_L24-29_
- L26 _public enumerator_ `CategoryNode`
- L27 _public enumerator_ `EntityNode`
- L28 _public enumerator_ `RootNode`

#### enum `FDMXEntityTreeNodeBase::EFilteredState`  
`enum EFilteredState`  
_L123-131_
- desc: Filtered states the node can take
- L125 _public enumerator_ `FilteredOut = 0x00`
- L126 _public enumerator_ `MatchesFilter = (1 << 0)`
- L127 _public enumerator_ `ChildMatches = (1 << 1)`
- L129 _public enumerator_ `FilteredInMask = (MatchesFilter | ChildMatches)`
- L130 _public enumerator_ `Unknown = 0xFC` — ~FilteredInMask

#### class `FDMXEntityTreeRootNode`  
`class FDMXEntityTreeRootNode : public FDMXEntityTreeNodeBase`  
_L138-149_
- inherits: `FDMXEntityTreeNodeBase`
- desc: A root node in an an entity list
- L142 _public prototype_ `FDMXEntityTreeRootNode();`
- L145 _public function_ `virtual bool CanRename() const override`
- L146 _public prototype_ `virtual FString GetDisplayNameString() const override;`
- L147 _public prototype_ `virtual FText GetDisplayNameText() const override;`

#### class `FDMXEntityTreeEntityNode`  
`class FDMXEntityTreeEntityNode : public FDMXEntityTreeNodeBase`  
_L153-171_
- inherits: `FDMXEntityTreeNodeBase`
- desc: An entity node in an an entity list
- L157 _public prototype_ `FDMXEntityTreeEntityNode(UDMXEntity* InEntity);`
- L160 _public function_ `virtual bool CanRename() const override`
- L161 _public prototype_ `virtual FString GetDisplayNameString() const override;`
- L162 _public prototype_ `virtual FText GetDisplayNameText() const override;`
- L166 _public prototype_ `virtual UDMXEntity* GetEntity() const;` — Returns the entity of this node
- L170 _private member_ `TWeakObjectPtr<UDMXEntity> DMXEntity;` — The DMXEntity of the node

#### class `FDMXEntityTreeCategoryNode`  
`class FDMXEntityTreeCategoryNode : public FDMXEntityTreeNodeBase`  
_L175-217_
- inherits: `FDMXEntityTreeNodeBase`
- desc: A category node in an an entity list
- L187 _public prototype_ `FDMXEntityTreeCategoryNode(ECategoryType InCategoryType, FText InCategoryName, const FText& ToolTip = FText::GetEmpty());`
- L188 _public prototype_ `FDMXEntityTreeCategoryNode(ECategoryType InCategoryType, FText InCategoryName, int32 Value, const FText& ToolTip = FText::GetEmpty());`
- L189 _public prototype_ `FDMXEntityTreeCategoryNode(ECategoryType InCategoryType, FText InCategoryName, const FDMXFixtureCategory& Value, const FText& ToolTip = FText::GetEmpty());`
- L192 _public function_ `virtual bool CanRename() const override`
- L193 _public prototype_ `virtual FString GetDisplayNameString() const override;`
- L194 _public prototype_ `virtual FText GetDisplayNameText() const override;`
- L195 _public prototype_ `ECategoryType GetCategoryType() const;`
- L198 _public function_ `const FText& GetToolTip() const`
- L200 _public function_ `bool CanDropOntoCategory() const`
- L201 _public function_ `int32 GetIntValue() const`
- L202 _public function_ `const FDMXFixtureCategory& GetCategoryValue()`
- L206 _private member_ `ECategoryType CategoryType;` — This node's category type
- L207 _private member_ `FText CategoryName;`
- L208 _private member_ `FText ToolTip;`
- L210 _private member_ `bool bCanDropOntoCategory;`
- L213 _private member_ `int32 IntValue = 0;` — The int value, if of UniverseID type
- L216 _private member_ `FDMXFixtureCategory CategoryValue;` — The fixture category, if of FixtureCategory type

#### enum `FDMXEntityTreeCategoryNode::ECategoryType`  
`enum class ECategoryType : uint8`  
_L179-185_
- L181 _public enumerator_ `DMXCategory`
- L182 _public enumerator_ `FixtureAssignmentState`
- L183 _public enumerator_ `UniverseID`
- L184 _public enumerator_ `NONE`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/DMXAddFixturePatchMenuData.h` (Private)


#### class `UDMXAddFixturePatchMenuData`  
`class UDMXAddFixturePatchMenuData : public UObject`  
_L14-31_
- reflection: `UCLASS(Config = DMXEditor)`
- inherits: `UObject`
- L21 _public member_ `TSoftObjectPtr<UDMXEntityFixtureType> SoftFixtureType;` — `UPROPERTY(Config)`
- L24 _public member_ `int32 ActiveModeIndex = 0;` — `UPROPERTY(Config)`
- L27 _public member_ `int32 NumPatches = 0;` — `UPROPERTY(Config)`
- L30 _public member_ `bool bIncrementChannelAfterPatching = true;` — `UPROPERTY(Config)`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/DMXFixturePatchEditorDefinitions.h` (Private)


#### struct `FDMXChannelGridSpecs`  
`struct FDMXChannelGridSpecs`  
_L9-16_
- desc: Specifications of channels in a universe displayed in UI
- L12 _public member_ `static const int32 NumColumns;` — Num Columns in the grid
- L15 _public member_ `static const int32 ChannelIDOffset;` — The offset of the Channel ID, from 0 to the first channel ID

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/DMXFixturePatchListItem.h` (Private)


#### class `FDMXFixturePatchListItem`  
`class FDMXFixturePatchListItem : public TSharedFromThis<FDMXFixturePatchListItem>`  
_L15-94_
- inherits: `TSharedFromThis<FDMXFixturePatchListItem>`
- desc: An MVR Fixture as an Item in a List. A Primary Items is the first MVR Fixture in a Patch. Secondary Items are subsequent MVR Fixtures
- L20 _public prototype_ `FDMXFixturePatchListItem(TWeakPtr<FDMXEditor> InDMXEditor, UDMXEntityFixturePatch* InFixturePatch);` — Constructor
- L23 _public prototype_ `FGuid GetMVRUUID() const;` — Returns the MVR UUID of the MVR Fixture
- L26 _public prototype_ `FLinearColor GetBackgroundColor() const;` — Returns the background color of this Item
- L29 _public prototype_ `FString GetFixturePatchName() const;` — Returns the Name of the Fixture Patch
- L32 _public prototype_ `void SetFixturePatchName(const FString& InDesiredName, FString& OutNewName);` — Sets the Name of the Fixture Patch
- L35 _public prototype_ `FString GetFixtureID() const;` — Returns the Fixture ID
- L38 _public prototype_ `void SetFixtureID(int32 InFixtureID);` — Sets the Fixture ID. Note, as other hard- and software, we allow to set integer values only.
- L41 _public prototype_ `UDMXEntityFixtureType* GetFixtureType() const;` — Returns the Fixture Type of the MVR Fixture
- L44 _public prototype_ `void SetFixtureType(UDMXEntityFixtureType* FixtureType);` — Sets the fixture type of the MVR Fixture
- L47 _public prototype_ `int32 GetModeIndex() const;` — Returns the Mode Index of the MVR Fixture
- L50 _public prototype_ `void SetModeIndex(int32 ModeIndex);` — Sets the Mode Index for the MVR
- L53 _public prototype_ `bool GetActiveModeName(FString& OutModeName) const;` — Gets the name of the active mode. Returns false if there is no active mode for this patch.
- L56 _public prototype_ `int32 GetUniverse() const;` — Returns the Universe the MVR Fixture resides in
- L59 _public prototype_ `int32 GetAddress() const;` — Returns the Address of the MVR Fixture
- L62 _public prototype_ `void SetAddresses(int32 Universe, int32 Address);` — Sets the Addresses of the MVR Fixture
- L65 _public prototype_ `int32 GetNumChannels() const;` — Returns Num Channels the MVR Fixture spans
- L68 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — Returns the Fixture Patch. Const on purpose, should be edited via this class's methods
- L71 _public prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the DMX Library in which the MVR Fixture resides
- L74 _public function_ `bool IsChangingFixturePatch() const` — Returns true if this item is changing its Fixture Patch
- L77 _public member_ `FText WarningStatusText;` — Warning Status Text of the Item
- L80 _public member_ `FText ErrorStatusText;` — Error Status Text of the Item
- L84 _private member_ `bool bIsEvenGroup = false;` — True if this is in an even group
- L87 _private member_ `bool bChangingFixturePatch = false;` — True while this item is changing the DMX Library
- L90 _private member_ `TWeakObjectPtr<UDMXEntityFixturePatch> WeakFixturePatch;` — The fixture patch the MVR Fixture UUID is assigned to
- L93 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this Item

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/DMXFixturePatchNode.h` (Private)


#### class `FDMXFixturePatchNode`  
`class FDMXFixturePatchNode : public TSharedFromThis<FDMXFixturePatchNode>`  
_L18-82_
- inherits: `TSharedFromThis<FDMXFixturePatchNode>`
- desc: A fixture patch in a grid, consists of several fragments, displayed as SDMXFixturePatchNodes (see GenerateWidgets). The patch node does not necessarily have to present the state of the object, e.g. when dragged or when containing an occuppied universe/channel.
- L23 _public prototype_ `static TSharedPtr<FDMXFixturePatchNode> Create(TWeakPtr<FDMXEditor> InDMXEditor, const TWeakObjectPtr<UDMXEntityFixturePatch>& InFixturePatch);` — Creates a new node from Patch
- L26 _public prototype_ `void SetAddresses(int32 UniverseID, int32 NewStartingChannel, int32 NewChannelSpan);` — Sets the Addresses of the Node
- L29 _public prototype_ `TArray<TSharedRef<SDMXFixturePatchFragment>> GenerateWidgets(const TSharedRef<SDMXPatchedUniverse>& OwningUniverse, const TArray<TSharedPtr<FDMXFixturePatchNode>>& FixturePatchNodeGroup);` — Generates widgets. Requires Addresses to be set via SetAddresses
- L32 _public prototype_ `bool OccupiesChannels(int32 Channel, int32 Span) const;` — Returns wether the patch uses specified channels
- L35 _public prototype_ `bool IsSelected() const;` — Returns true if the node is selected
- L38 _public function_ `void SetIsHovered(bool bNewIsHovered)` — Sets if the patch is hovered
- L41 _public function_ `bool IsHovered() const` — Returns true if this patch is hovered
- L44 _public function_ `TWeakObjectPtr<UDMXEntityFixturePatch> GetFixturePatch() const` — Returns the fixture patches this node holds
- L47 _public prototype_ `FString GetFixtureID() const;` — Returns the Fixture ID of the patch
- L50 _public prototype_ `int32 GetUniverseID() const;` — Returns the Universe ID the Node currently resides in. Returns a negative Value if not assigned to a Universe.
- L53 _public prototype_ `int32 GetStartingChannel() const;` — Returns the Starting Channel of the Patch
- L56 _public prototype_ `int32 GetChannelSpan() const;` — Returns the Channel Span of the Patch
- L59 _public function_ `void SetZOrder(int32 NewZOrder)` — Sets the ZOrder of the Node
- L62 _public function_ `int32 GetZOrder() const` — Gets the ZOrder of the Node
- L66 _private prototype_ `void UpdateIsSelected();` — Updates if the node is selected
- L69 _private member_ `bool bSelected = false;` — If true the node is selected
- L72 _private member_ `bool bHovered = false;` — True if the node is hovered
- L75 _private member_ `int32 ZOrder = 0;` — ZOrder of this node
- L78 _private member_ `TWeakObjectPtr<UDMXEntityFixturePatch> FixturePatch;` — The Fixture Patch this Node stands for
- L81 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — Weak DMXEditor refrence

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXAddFixturePatchMenu.h` (Private)


#### class `UE::DMXEditor::FixturePatchEditor::SDMXAddFixturePatchMenu`  
`class SDMXAddFixturePatchMenu final : public SCompoundWidget`  
_L23-123_
- inherits: `SCompoundWidget`
- desc: Editor for Fixture Patches
- L27 _public function_ `SLATE_BEGIN_ARGS(SDMXAddFixturePatchMenu)`
- L31 _public prototype_ `virtual ~SDMXAddFixturePatchMenu();`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FDMXEditor> InWeakDMXEditor);` — Constructs this widget
- L37 _public prototype_ `void RequestRefresh();` — Refreshes the widget on the next tick
- L41 _private prototype_ `void Refresh();` — Refreshes the widget
- L44 _private prototype_ `TSharedRef<SWidget> MakeFixtureTypeSelectWidget();` — Creates a widget to select a fixture type
- L47 _private prototype_ `TSharedRef<SWidget> MakeModeSelectWidget();` — Creates a widget to select a mode
- L50 _private prototype_ `TSharedRef<SWidget> MakeUniverseChannelSelectWidget();` — Creates an widget to select the Universe and Channel
- L53 _private prototype_ `TSharedRef<SWidget> MakeAutoIncrementChannelCheckBox();` — Creates a widget to toggle if the channels should be auto-incremented after patching
- L56 _private prototype_ `TSharedRef<SWidget> MakeNumFixturePatchesEditableTextBox();` — Creates an editable text box to specify the number of patches
- L59 _private prototype_ `TSharedRef<SWidget> MakeAddFixturePatchesButton();` — Creates a button that adds the fixture patches when clicked
- L62 _private prototype_ `TSharedRef<SWidget> GenerateModeComboBoxEntry(const TSharedPtr<uint32> InMode) const;` — Generates an entry in the mode combo box
- L65 _private prototype_ `void OnEntityAddedOrRemoved(UDMXLibrary* DMXLibrary, TArray<UDMXEntity*> Entities);` — Called when an entity was added or removed from the DMX Library
- L68 _private prototype_ `void OnFixtureTypeSelected(UDMXEntity* InSelectedFixtureType);` — Called when a fixture type was selected
- L71 _private prototype_ `void OnModeSelected(TSharedPtr<uint32> InSelectedMode, ESelectInfo::Type SelectInfo);` — Called when a mode was selected
- L74 _private prototype_ `FText GetUniverseChannelText() const;` — Returns the current universe channel text
- L77 _private prototype_ `void OnUniverseChannelTextChanged(const FText& InText);` — Called when the universe channel text changed
- L80 _private prototype_ `void OnUniverseChannelTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when the universe channel text was committed
- L83 _private prototype_ `FReply OnAddFixturePatchButtonClicked();` — Called when the 'Add' button was clicked
- L86 _private prototype_ `FText GetActiveModeText() const;` — Returns the text of the active mode
- L89 _private prototype_ `bool HasValidFixtureTypeAndMode() const;` — Returns if a valid fixture type with a mode is selected
- L92 _private member_ `TWeakObjectPtr<UDMXEntityFixtureType> WeakFixtureType;` — Current fixture type
- L95 _private member_ `TOptional<int32> Universe;` — Universe where the patches will be added
- L98 _private member_ `TOptional<int32> Channel;` — Channel where the patches will be added
- L101 _private member_ `uint32 NumFixturePatchesToAdd = 1;` — The number of fixture patches to add
- L104 _private member_ `FTimerHandle RequestRefreshModeComboBoxTimerHandle;` — Timer handle for the request refresh combo box timer
- L107 _private member_ `TSharedPtr<SDMXEntityPickerButton<UDMXEntityFixtureType>> FixtureTypeSelector;` — Widget to select the fixture type
- L110 _private member_ `TSharedPtr<SEditableTextBox> UniverseChannelEditableTextBox;` — Text boxt to set the channel where the patch will be spawned
- L113 _private member_ `TArray<TSharedPtr<uint32>> ModeSources;` — Sources for the mode combo box
- L116 _private member_ `TSharedPtr<SComboBox<TSharedPtr<uint32>>> ModeComboBox;` — Combo box to selected the mode
- L119 _private member_ `TSharedPtr<FDMXFixturePatchSharedData> SharedData;` — Shared data for fixture patches
- L122 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX editor this widget displays

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DMXEditor` (scope `UE`)
- L20 _namespace_ `namespace FixturePatchEditor` (scope `UE::DMXEditor`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXChannelConnector.h` (Private)


#### class `SDMXChannelConnector`  
`class SDMXChannelConnector : public SCompoundWidget`  
_L15-125_
- inherits: `SCompoundWidget`
- desc: Visual representation of a connection to a channel in a dmx universe
- L18 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnMouseEventWithReply, uint32 , const FPointerEvent&);`
- L20 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnDragEvent, uint32 , const FDragDropEvent&);`
- L22 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDragEventWithReply, uint32 , const FDragDropEvent&);`
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMXChannelConnector) : _ChannelID(0) , _UniverseID(-1) , _Value(0.0f) , _OnDragEnterChannel() , _OnDragLeaveChannel() , _OnDropOntoChannel()`
- L34 _public prototype_ `SLATE_ARGUMENT(int32, ChannelID) SLATE_ARGUMENT(int32, UniverseID) SLATE_ARGUMENT(uint8, Value) SLATE_EVENT(FSimpleDelegate, OnHovered) SLATE_EVENT(FSimpleDelegate, OnUnhovered) SLATE_EVENT(FOnMouseEventWithReply, OnMouseButtonDownOnChannel) SLATE_EVENT(FOnMouseEventWithReply, OnMouseButtonUpOnChannel) SLATE_EVENT(FOnMouseEventWithReply, OnDragDetectedOnChannel) SLATE_EVENT(FOnDragEvent, OnDragEnterChannel) SLATE_EVENT(FOnDragEvent, OnDragLeaveChannel) SLATE_EVENT(FOnDragEventWithReply, OnDropOntoChannel) SLATE_ATTRIBUTE(FSlateColor, ChannelIDTextColor) SLATE_ATTRIBUTE(FSlateColor, ValueTextColor) SLATE_END_ARGS()` — The channel ID this widget stands for
- L78 _public function_ `int32 GetChannelID() const` — Returns the ChannelID of this connector
- L81 _public function_ `int32 GetUniverseID() const` — Returns the UniverseID of this connector
- L84 _public function_ `void SetUniverseID(int32 InUniverseID)` — Sets the UniverseID of this connector
- L87 _public prototype_ `void SetValue(uint8 Value);` — Sets the displayed value
- L91 _protected prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L92 _protected prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L93 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L94 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent) override;`
- L95 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L96 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L97 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L98 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L103 _private prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the DMXLibrary or nullptr if not available
- L105 _private member_ `int32 Column = INDEX_NONE;`
- L106 _private member_ `int32 Row = INDEX_NONE;`
- L108 _private member_ `TSharedPtr<class SDMXChannel> ChannelValueWidget;`
- L110 _private member_ `int32 ChannelID;`
- L112 _private member_ `int32 UniverseID;`
- L114 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;`
- L117 _private member_ `FSimpleDelegate OnHovered;` — Slate Arguments
- L118 _private member_ `FSimpleDelegate OnUnhovered;`
- L119 _private member_ `FOnMouseEventWithReply OnMouseButtonDownOnChannel;`
- L120 _private member_ `FOnMouseEventWithReply OnMouseButtonUpOnChannel;`
- L121 _private member_ `FOnMouseEventWithReply OnDragDetectedOnChannel;`
- L122 _private member_ `FOnDragEvent OnDragEnterChannel;`
- L123 _private member_ `FOnDragEvent OnDragLeaveChannel;`
- L124 _private member_ `FOnDragEventWithReply OnDropOntoChannel;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnMouseEventWithReply, uint32 , const FPointerEvent&);`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDragEvent, uint32 , const FDragDropEvent&);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDragEventWithReply, uint32 , const FDragDropEvent&);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXFixturePatchEditor.h` (Private)


#### class `SDMXFixturePatchEditor`  
`class SDMXFixturePatchEditor final : public SDMXEntityEditor`  
_L20-94_
- inherits: `SDMXEntityEditor`
- desc: Editor for Fixture Patches
- L24 _public function_ `SLATE_BEGIN_ARGS(SDMXFixturePatchEditor) : _DMXEditor(nullptr)`
- L34 _public prototype_ `~SDMXFixturePatchEditor();` — Destructor
- L37 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget
- L41 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L42 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L46 _public prototype_ `void RequestRenameOnNewEntity(const UDMXEntity* InEntity, ESelectInfo::Type SelectionType);`
- L47 _public prototype_ `void SelectEntity(UDMXEntity* InEntity, ESelectInfo::Type InSelectionType = ESelectInfo::Type::Direct);`
- L48 _public prototype_ `void SelectEntities(const TArray<UDMXEntity*>& InEntities, ESelectInfo::Type SelectionType = ESelectInfo::Type::Direct);`
- L49 _public prototype_ `TArray<UDMXEntity*> GetSelectedEntities() const;`
- L54 _private prototype_ `TSharedRef<IDetailsView> GenerateFixturePatchDetailsView() const;` — Generates a Detail View for the edited Fixture Patch
- L57 _private prototype_ `void SelectUniverse(int32 UniverseID);` — Selects the patch
- L60 _private prototype_ `void OnFixturePatchesSelected();` — Called whewn Fixture Patches were selected in Fixture Patch Shared Data
- L63 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* ChangedFixtureType);` — Called when a Fixture Type changed
- L66 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* ChangedFixturePatch);` — Called when a Fixture Patch changed
- L69 _private prototype_ `void RequestRefreshFixturePatchDetailsView();` — Refreshes the Fixture Patch Details View on the next tick
- L72 _private prototype_ `void RefreshFixturePatchDetailsView();` — Refreshes the Fixture Patch Details View
- L75 _private member_ `TSharedPtr<SDMXFixturePatchList> FixturePatchList;` — List of Fixture Patches as MVR Fixtures
- L78 _private member_ `TSharedPtr<IDetailsView> FixturePatchDetailsView;` — Details View for the selected Fixture Patches
- L81 _private member_ `TSharedPtr<SSplitter> LhsRhsSplitter;` — The main splitter that divides the view in an left and right side
- L84 _private member_ `TSharedPtr<SDMXFixturePatcher> FixturePatcher;` — Widget where the user can drag drop fixture patches
- L87 _private member_ `TSharedPtr<FDMXFixturePatchSharedData> FixturePatchSharedData;` — Shared data for Fixture Patches
- L90 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — Pointer back to the DMXEditor tool that owns us
- L93 _private member_ `FTimerHandle RefreshFixturePatchDetailsViewTimerHandle;` — Timer handle to refresh the fixture patch details view

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXFixturePatchFragment.h` (Private)


#### class `SDMXFixturePatchFragment`  
`class SDMXFixturePatchFragment : public SCompoundWidget`  
_L15-128_
- inherits: `SCompoundWidget`
- L18 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnMouseEventWithReply, uint32 , const FPointerEvent&);`
- L20 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnDragEvent, uint32 , const FDragDropEvent&);`
- L22 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDragEventWithReply, uint32 , const FDragDropEvent&);`
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMXFixturePatchFragment) : _bIsHead(true) , _bIsTail(true) , _bIsConflicting(false) , _Column(-1) , _Row(-1) , _ColumnSpan(1)`
- L34 _public prototype_ `SLATE_ARGUMENT(bool, bIsHead) SLATE_ARGUMENT(bool, bIsTail) SLATE_ARGUMENT(bool, bIsConflicting) SLATE_ARGUMENT(int32, StartingChannel) SLATE_ARGUMENT(int32, Column) SLATE_ARGUMENT(int32, Row) SLATE_ARGUMENT(int32, ColumnSpan) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXFixturePatchNode>& InFixturePatchNode, const TArray<TSharedPtr<FDMXFixturePatchNode>>& InFixturePatchNodeGroup);` — If true displays as head of a patch
- L60 _public function_ `void SetConflicting(bool bConflicting)` — Sets if the fragment is conflicting with others
- L63 _public prototype_ `void SetChannelVisibility(EVisibility NewVisibility);` — Sets the visibility of the channels of the fragment
- L66 _public function_ `const TSharedPtr<FDMXFixturePatchNode>& GetFixturePatchNode() const` — Gets the fixture patch node this widget refers to
- L69 _public member_ `int32 StartingChannel = -1;` — Starting Channel of the Fragment
- L72 _public member_ `int32 Column = -1;` — Column of the Fragment
- L75 _public member_ `int32 Row = -1;` — Row of the Fragment
- L78 _public member_ `int32 ColumnSpan = 1;` — Column span of the Fragment
- L82 _private prototype_ `void InitializeBorderPadding();` — Updates the Padding of the outermost Border
- L85 _private prototype_ `void InitializeIsTopmost();` — Updates the bTopmost member from the ZOrder of the node
- L88 _private prototype_ `const FSlateBrush* GetBorderBrush() const;` — Returns the brush for the border around the widget
- L91 _private prototype_ `FSlateColor GetBorderColor() const;` — Returns the border color of the border around the widget
- L94 _private prototype_ `FSlateColor GetChannelIDTextColor() const;` — Returns the color of the channel ID texts
- L97 _private prototype_ `FSlateColor GetValueTextColor() const;` — Returns the color of the Value texts
- L100 _private member_ `bool bIsTopmost = false;` — If true, the patch has the highest ZOrder in its node group
- L103 _private member_ `bool bIsHead = false;` — If true this is the Head of the Fixture Patch
- L106 _private member_ `bool bIsTail = false;` — If true this is the Tail of the Fixture Patch
- L109 _private member_ `bool bIsConflicting = false;` — If true, the Widget displays a conflict background
- L112 _private member_ `FMargin BorderPadding;` — The padding of the outermost border
- L115 _private member_ `TSharedPtr<SHorizontalBox> ChannelsHorizontalBox;` — Horizontal box containing the channels of this fragment
- L118 _private member_ `TSharedPtr<SOverlay> ContentOverlay;` — Overlay for content
- L121 _private member_ `TSharedPtr<FDMXFixturePatchNode> FixturePatchNode;` — Fixture Patch Node being displayed by this widget
- L124 _private member_ `TArray<TSharedPtr<FDMXFixturePatchNode>> FixturePatchNodeGroup;` — The group of nodes (same Universe, same Channel) this widget belongs to
- L127 _private member_ `TWeakPtr<FDMXEditor> DMXEditorPtr;` — Weak DMXEditor refrence

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnMouseEventWithReply, uint32 , const FPointerEvent&);`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDragEvent, uint32 , const FDragDropEvent&);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnDragEventWithReply, uint32 , const FDragDropEvent&);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXFixturePatchList.h` (Private)


#### struct `FDMXFixturePatchListCollumnID`  
`struct FDMXFixturePatchListCollumnID`  
_L29-38_
- desc: Collumn IDs in the Fixture Patch List
- L31 _public member_ `static const FName EditorColor;`
- L32 _public member_ `static const FName FixturePatchName;`
- L33 _public member_ `static const FName Status;`
- L34 _public member_ `static const FName FixtureID;`
- L35 _public member_ `static const FName FixtureType;`
- L36 _public member_ `static const FName Mode;`
- L37 _public member_ `static const FName Patch;`

#### class `SDMXFixturePatchList`  
`class SDMXFixturePatchList : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L43-194_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Sortable, editable List of Fixture Patches in the library
- L48 _public function_ `SLATE_BEGIN_ARGS(SDMXFixturePatchList)`
- L53 _public prototype_ `SDMXFixturePatchList();`
- L54 _public prototype_ `virtual ~SDMXFixturePatchList();`
- L57 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L58 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L62 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FDMXEditor> InDMXEditor);` — Constructs this widget
- L65 _public prototype_ `void RequestListRefresh();` — Updates the List on the next tick
- L68 _public prototype_ `void EnterFixturePatchNameEditingMode();` — If a single Row is selected, enters Editing Mode for the Fixture Patch Name of the selected Row
- L71 _public prototype_ `FReply ProcessCommandBindings(const FKeyEvent& InKeyEvent);` — Processes command bindings for the Key Event
- L75 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L76 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L81 _private prototype_ `void OnSearchChanged();` — Called when the search changed
- L84 _private prototype_ `void RefreshList();` — Refreshes the List
- L87 _private prototype_ `void GenereateStatusText();` — Generates Status Text for each Item and sets it
- L90 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXFixturePatchListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a row in the List gets generated
- L93 _private prototype_ `void OnSelectionChanged(TSharedPtr<FDMXFixturePatchListItem> InItem, ESelectInfo::Type SelectInfo);` — Called when the Selection in the list changed
- L96 _private prototype_ `void OnEntityAddedOrRemoved(UDMXLibrary* DMXLibrary, TArray<UDMXEntity*> Entities);` — Called when entities were added or removed from the DMX Library
- L99 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when a Fixture Patch changed
- L102 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a Fixture Type changed
- L105 _private prototype_ `void OnFixturePatchSharedDataSelectedFixturePatches();` — Called when Fixture Patch Shared Data selected Fixture Patches
- L108 _private prototype_ `void AdoptSelectionFromFixturePatchSharedData();` — Selects what is selected in Fixture Patch Shared Data
- L111 _private prototype_ `void AutoAssignFixturePatches(UE::DMXEditor::AutoAssign::EAutoAssignMode Mode);` — Auto assigns selected Fixture Patches
- L114 _private prototype_ `bool DoesDMXLibraryHaveReachableUniverses() const;` — Returns true if the DMX Library has reachable Universes
- L117 _private prototype_ `void SetKeyboardFocus();` — Sets keyboard focus on this widget
- L120 _private prototype_ `TSharedRef<SHeaderRow> GenerateHeaderRow();` — Generates the Header Row of the List
- L123 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Returns the column sort mode for the list
- L126 _private prototype_ `void SortListSource(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Sorts the list source
- L129 _private prototype_ `void SortList(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Sort the list
- L132 _private member_ `EColumnSortMode::Type SortMode;` — The current Sort Mode
- L135 _private member_ `FName SortedByColumnID;` — By which column ID the List is sorted
- L138 _private member_ `bool bChangingDMXLibrary = false;` — Set to true while changing the DMX Library and only redraw the list when this is false, e.g. for Duplicate, Paste etc.
- L141 _private member_ `TArray<TSharedPtr<FDMXFixturePatchListItem>> ListSource;` — Source array for the Fixture Patch List
- L144 _private member_ `TArray<TSharedPtr<FDMXFixturePatchListItem>> FilteredListSource;` — List source when filtered by search
- L147 _private member_ `TSharedPtr<FDMXFixturePatchListItem> LastSelectedItem;` — The item that was last selected in the list
- L150 _private member_ `TSharedPtr<SDMXFixturePatchListToolbar> Toolbar;` — The Search Bar for the List
- L153 _private member_ `TSharedPtr<SDMXFixturePatchListType> ListView;` — The the list of Fixture Patches
- L156 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;` — The Header Row of the List
- L159 _private member_ `TArray<TSharedPtr<SDMXFixturePatchListRow>> Rows;` — Rows of Mode widgets in the List
- L162 _private member_ `TSharedPtr<SBorder> ListContentBorder;` — The border that holds the list
- L165 _private member_ `FTimerHandle RequestListRefreshTimerHandle;` — Timer handle for the Request List Refresh method
- L168 _private member_ `TSharedPtr<FDMXFixturePatchSharedData> FixturePatchSharedData;` — Shared Data for Fixture Patch Editors
- L171 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The Fixture Type Editor that owns this widget
- L177 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L180 _private prototype_ `void RegisterCommands();` — Registers the commands
- L182 _private prototype_ `bool CanCutItems() const;`
- L183 _private prototype_ `void OnCutSelectedItems();`
- L184 _private prototype_ `bool CanCopyItems() const;`
- L185 _private prototype_ `void OnCopySelectedItems();`
- L186 _private prototype_ `bool CanPasteItems() const;`
- L187 _private prototype_ `void OnPasteItems();`
- L188 _private prototype_ `bool CanDuplicateItems() const;`
- L189 _private prototype_ `void OnDuplicateItems();`
- L190 _private prototype_ `bool CanDeleteItems() const;`
- L191 _private prototype_ `void OnDeleteItems();`
- L193 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DMXEditor` (scope `UE`)
- L26 _namespace_ `namespace AutoAssign` (scope `UE::DMXEditor`)
- L40 _typedef_ `using SDMXFixturePatchListType = SListView<TSharedPtr<FDMXFixturePatchListItem>>;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXFixturePatchListRow.h` (Private)


#### class `SDMXFixturePatchListRow`  
`class SDMXFixturePatchListRow : public SMultiColumnTableRow<TSharedPtr<FDMXFixturePatchListItem>>`  
_L15-111_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXFixturePatchListItem>>`
- desc: MVR Fixture view as a row in a list
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXFixturePatchListRow)`
- L22 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnRowRequestsStatusRefresh) SLATE_EVENT(FSimpleDelegate, OnRowRequestsListRefresh) SLATE_EVENT(FIsSelected, IsSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedRef<FDMXFixturePatchListItem>& InItem);` — Delegate executed when the row requests to refresh the statuses
- L36 _public prototype_ `void EnterFixturePatchNameEditingMode();` — Enters editing mode for the Fixture Patch Name
- L39 _public function_ `TSharedPtr<FDMXFixturePatchListItem> GetItem() const` — Returns the Item of this row
- L43 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L48 _private prototype_ `TSharedRef<SWidget> GenerateEditorColorWidget();` — Generates the Widget that displays the Editor Color
- L51 _private prototype_ `TSharedRef<SWidget> GenerateFixturePatchNameWidget();` — Generates the Widget that displays the Fixture Patch Name
- L54 _private prototype_ `FReply OnFixturePatchNameBorderDoubleClicked(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);` — Called when the Fixture Patch Name Border was double-clicked
- L57 _private prototype_ `void OnFixturePatchNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when a Fixture Patch Name was committed
- L60 _private prototype_ `TSharedRef<SWidget> GenerateStatusWidget();` — Generates the widget that displays the Status
- L63 _private prototype_ `TSharedRef<SWidget> GenerateFixtureIDWidget();` — Generates the Widget that displays the Fixture ID
- L66 _private prototype_ `FReply OnFixtureIDBorderDoubleClicked(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);` — Called when the Fixture ID Border was double-clicked
- L69 _private prototype_ `void OnFixtureIDCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when a Fixture ID was committed
- L72 _private prototype_ `TSharedRef<SWidget> GenerateFixtureTypeWidget();` — Generates the Widget that displays the Fixture Type
- L75 _private prototype_ `TSharedRef<SWidget> GenerateModeWidget();` — Generates the Widget that displays the Mode
- L78 _private prototype_ `TSharedRef<SWidget> GeneratePatchWidget();` — Generates the Widget that displays the Patch
- L81 _private prototype_ `FReply OnPatchBorderDoubleClicked(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);` — Called when the Patch Border was double-clicked
- L84 _private prototype_ `void OnPatchNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when a Patch was committed
- L87 _private member_ `EDMXFixturePatchListEditMode EditMode;` — The Edit Mode the Widget should present
- L90 _private member_ `TSharedPtr<SBorder> FixturePatchNameBorder;` — The outermost border around the the Fixture Patch Name Column
- L93 _private member_ `TSharedPtr<SInlineEditableTextBlock> FixturePatchNameTextBlock;` — The text block to edit the Fixture Patch Name
- L96 _private member_ `TSharedPtr<SInlineEditableTextBlock> FixtureIDTextBlocK;` — The text block to edit the Fixture ID
- L99 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameTextBlock;` — The text block to edit the Name
- L102 _private member_ `TSharedPtr<SInlineEditableTextBlock> PatchTextBlock;` — The text block to edit the Name
- L105 _private member_ `TSharedPtr<FDMXFixturePatchListItem> Item;` — The MVR Fixture List Item this row displays
- L108 _private member_ `FSimpleDelegate OnRowRequestsStatusRefresh;` — Slate arguments
- L109 _private member_ `FSimpleDelegate OnRowRequestsListRefresh;`
- L110 _private member_ `FIsSelected IsSelected;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXFixturePatchListToolbar.h` (Private)


#### class `SDMXFixturePatchListToolbar`  
`class SDMXFixturePatchListToolbar : public SCompoundWidget`  
_L18-60_
- inherits: `SCompoundWidget`
- desc: Search bar for the MVR Fixture List
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXFixturePatchListToolbar)`
- L26 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnSearchChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FDMXEditor> InDMXEditor);` — Executed when the search changed
- L34 _public prototype_ `[[nodiscard]] TArray<TSharedPtr<FDMXFixturePatchListItem>> FilterItems(const TArray<TSharedPtr<FDMXFixturePatchListItem>>& Items);` — Filters items according to the state of the search bar
- L38 _private prototype_ `TSharedRef<SWidget> GenerateFixtureTypeDropdownMenu();` — Generates the 'Add MVR Fixture' Dropdown Menu
- L41 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);` — Called when the Search Text changed
- L44 _private prototype_ `void OnShowConflictsOnlyCheckStateChanged(const ECheckBoxState NewCheckState);` — Called when the Check State of the 'Show Conflicts Only' Check Box changed
- L47 _private member_ `FString SearchString;` — Current Search String
- L50 _private member_ `bool bShowConfictsOnly = false;` — True if only conflicts are searched for
- L53 _private member_ `TSharedPtr<UE::DMXEditor::FixturePatchEditor::SDMXAddFixturePatchMenu> AddFixturePatchMenu;` — Menu displayed to add fixture patches
- L56 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget
- L59 _private member_ `FSimpleDelegate OnSearchChanged;` — Slate Args

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMXEditor` (scope `UE`)
- L14 _namespace_ `namespace FixturePatchEditor` (scope `UE::DMXEditor`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXFixturePatcher.h` (Private)


#### class `SDMXFixturePatcher`  
`class SDMXFixturePatcher : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L31-179_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Widget to assign fixture patches to universes and their channels
- L36 _public function_ `SLATE_BEGIN_ARGS(SDMXFixturePatcher) : _DMXEditor(nullptr)`
- L40 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FDMXEditor>, DMXEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `void RefreshFromProperties();` — Refreshes the whole view from properties, does not consider changes in the library
- L51 _public prototype_ `void RefreshFromLibrary();` — Refreshes the whole view from the library, considers library changes
- L55 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L56 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L61 _private prototype_ `TSharedRef<SWidget> CreateToolbar();`
- L64 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenu();` — Creates the settings menu
- L67 _private prototype_ `void SelectFixturePatchNameDisplayMode(EDMXFixturePatcherNameDisplayMode DisplayMode);` — Selects the fixture patch name display mode
- L70 _private prototype_ `bool IsUsingFixturePatchNameDisplayMode(EDMXFixturePatcherNameDisplayMode DisplayMode) const;` — Returns true if the widget is currently using specified name display mode
- L73 _private prototype_ `void OnDragEnterChannel(int32 UniverseID, int32 ChannelID, const FDragDropEvent& DragDropEvent);` — Called when drag enters a channel
- L76 _private prototype_ `FReply OnDropOntoChannel(int32 UniverseID, int32 ChannelID, const FDragDropEvent& DragDropEvent);` — Called when drag dropped onto a channel
- L79 _private prototype_ `TMap<TSharedRef<FDMXFixturePatchNode>, int64> GetDraggedNodesToAbsoluteChannelOffsetMap(const FDragDropEvent& DragDropEvent) const;` — Returns a map of nodes being dragged along with their absolute channel offset from the Drag Drop Event
- L82 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L83 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L87 _private prototype_ `TSharedPtr<FDMXFixturePatchNode> FindPatchNode(const TWeakObjectPtr<UDMXEntityFixturePatch> FixturePatch) const;` — Finds specified fixture patch in all universes
- L90 _private prototype_ `TSharedPtr<FDMXFixturePatchNode> FindPatchNodeOfType(UDMXEntityFixtureType* Type, const TSharedPtr<FDMXFixturePatchNode>& IgoredNode) const;` — Returns first node with same fixture type
- L93 _private prototype_ `void OnEntitiesAddedOrRemoved(UDMXLibrary* DMXLibrary, TArray<UDMXEntity*> Entities);` — Called when entities were added to or removed from a DMX Library
- L96 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a fixture type changed
- L99 _private prototype_ `void OnFixturePatchSelectionChanged();` — Called when a fixture patch was selected
- L102 _private prototype_ `void OnUniverseSelectionChanged();` — Called when a universe was selected
- L105 _private prototype_ `void SelectUniverse(int32 NewUniverseID);` — Selects a universe
- L108 _private prototype_ `int32 GetSelectedUniverse() const;` — Returns the selected universe
- L111 _private prototype_ `void ShowSelectedUniverse();` — Shows the selected universe only
- L114 _private prototype_ `void ShowAllPatchedUniverses(bool bForceReconstructWidgets = false);` — Shows all universes
- L117 _private prototype_ `void AddUniverse(int32 UniverseID);` — Adds a universe widget
- L120 _private prototype_ `void OnToggleDisplayAllUniverses(ECheckBoxState CheckboxState);` — Called when the display all universe option is turned on or off
- L123 _private prototype_ `void SetDMXMonitorEnabled(bool bEnabled);` — Sets if the DMX Monitor feature is enabled
- L126 _private prototype_ `void OnToggleDMXMonitorEnabled(ECheckBoxState CheckboxState);` — Called when the monitor feature is turned on or off
- L129 _private prototype_ `bool IsUniverseSelectionEnabled() const;` — Returns true if the patcher allows for the selection of a single universe and show only that
- L132 _private prototype_ `bool HasAnyPorts() const;` — Returns true if the library has any ports
- L143 _private member_ `EDMXRefreshFixturePatcherState RefreshFixturePatchState = EDMXRefreshFixturePatcherState::NoRefreshRequested;` — True when a refresh was requested
- L146 _private member_ `int32 UniverseToSetNextTick = INDEX_NONE;` — If true updates selection once during tick and resets
- L150 _protected prototype_ `FText GetTooltipText() const;` — Returns a tooltip for the whole widget, used to hint why patching is not possible
- L154 _protected prototype_ `int32 ClampStartingChannel(int32 StartingChannel, int32 ChannelSpan) const;` — Creates a valid address given Universe, Starting Channel and Channel Span. Returns false if no valid Address can be found.
- L157 _protected prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the DMXLibrary or nullptr if not available
- L160 _protected member_ `TSharedPtr<SCheckBox> ShowAllUniversesCheckBox;` — Checkbox to determine if all patched Universes should be displayed
- L163 _protected member_ `TSharedPtr<SCheckBox> EnableDMXMonitorCheckBox;` — Checkbox to determine if the DMX Monitor functionality should be enabled
- L166 _protected member_ `TSharedPtr<SScrollBox> PatchedUniverseHorizontalScrollBox;` — Horizontal scrollbox containing all the patched universes
- L169 _protected member_ `TSharedPtr<SScrollBox> PatchedUniverseVerticalScrollBox;` — Vertical scrollbox containing all the patched universes
- L172 _protected member_ `TMap<int32, TSharedPtr<SDMXPatchedUniverse>> PatchedUniversesByID;` — Universe widgets by ID
- L175 _protected member_ `TSharedPtr<FDMXFixturePatchSharedData> SharedData;` — Shared data for fixture patch editors
- L178 _protected member_ `TWeakPtr<FDMXEditor> DMXEditorPtr;` — The owning editor

#### enum `SDMXFixturePatcher::EDMXRefreshFixturePatcherState`  
`enum class EDMXRefreshFixturePatcherState : uint8`  
_L135-140_
- desc: Enum for states of refreshing required
- L137 _public enumerator_ `RefreshFromProperties`
- L138 _public enumerator_ `RefreshFromLibrary`
- L139 _public enumerator_ `NoRefreshRequested`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/SDMXPatchedUniverse.h` (Private)


#### enum `EDMXPatchedUniverseReachability`  
`enum class EDMXPatchedUniverseReachability`  
_L29-35_
- L31 _public enumerator_ `Reachable`
- L32 _public enumerator_ `UnreachableForInputPorts`
- L33 _public enumerator_ `UnreachableForOutputPorts`
- L34 _public enumerator_ `UnreachableForInputAndOutputPorts`

#### class `SDMXPatchedUniverse`  
`class SDMXPatchedUniverse : public SCompoundWidget`  
_L39-271_
- inherits: `SCompoundWidget`
- desc: A universe with assigned patches
- L42 _private prototype_ `DECLARE_DELEGATE_ThreeParams(FOnDragOverChannel, int32 , int32 , const FDragDropEvent&);`
- L44 _private prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnDropOntoChannel, int32 , int32 , const FDragDropEvent&);`
- L47 _public function_ `SDMXPatchedUniverse() : PatchedUniverseReachability(EDMXPatchedUniverseReachability::UnreachableForInputAndOutputPorts)`
- L51 _public function_ `SLATE_BEGIN_ARGS(SDMXPatchedUniverse) : _UniverseID(0) , _DMXEditor(nullptr) , _OnDragEnterChannel() , _OnDragLeaveChannel() , _OnDropOntoChannel()`
- L58 _public prototype_ `SLATE_ARGUMENT(int32, UniverseID) SLATE_ARGUMENT(TWeakPtr<FDMXEditor>, DMXEditor) SLATE_EVENT(FOnDragOverChannel, OnDragEnterChannel) SLATE_EVENT(FOnDragOverChannel, OnDragLeaveChannel) SLATE_EVENT(FOnDropOntoChannel, OnDropOntoChannel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L77 _public prototype_ `void RequestRefresh();` — Requests to refresh the Widget on the next tick
- L80 _public prototype_ `void SetMonitorInputsEnabled(bool bEnabled);` — Sets if this universe should monitor inputs
- L83 _public prototype_ `bool FindOrAdd(const TSharedRef<FDMXFixturePatchNode>& Node);` — Finds or adds a Node to this Universe
- L86 _public prototype_ `void Remove(const TSharedRef<FDMXFixturePatchNode>& Node);` — Removes a Node from this Universe
- L89 _public prototype_ `bool CanAssignFixturePatch(TWeakObjectPtr<UDMXEntityFixturePatch> TestedPatch) const;` — Returns wether the patch can be patched to its current channels
- L92 _public prototype_ `bool CanAssignFixturePatch(TWeakObjectPtr<UDMXEntityFixturePatch> TestedPatch, int32 StartingChannel) const;` — Returns wether the patch can be patched to specified channel
- L95 _public prototype_ `bool CanAssignNode(const TSharedPtr<FDMXFixturePatchNode>& TestedNode, int32 StartingChannel) const;` — Returns wether the node can be patched to specified channel
- L98 _public prototype_ `TSharedPtr<FDMXFixturePatchNode> FindPatchNode(TWeakObjectPtr<UDMXEntityFixturePatch> FixturePatch) const;` — Returns if the node is patched in the unvierse
- L101 _public prototype_ `TSharedPtr<FDMXFixturePatchNode> FindPatchNodeOfType(UDMXEntityFixtureType* Type, const TSharedPtr<FDMXFixturePatchNode>& IgoredNode) const;` — Returns first node with same fixture type as specified node
- L104 _public function_ `int32 GetUniverseID() const` — Returns the ID of the universe
- L107 _public function_ `const TArray<TSharedRef<FDMXFixturePatchNode>>& GetPatchedNodes() const` — Gets all nodes patched to this universe
- L111 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L116 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when a Fixture Patch changed
- L119 _private prototype_ `void OnReceiveDMXEnabledChanged(bool bNewEnabled);` — Called when receive DMX was enabled or disabled
- L122 _private prototype_ `void SetUniverseIDInternal(int32 NewUniverseID);` — Shows the universe directly
- L125 _private prototype_ `void RefreshInternal();` — Refreshes the widget directly
- L128 _private prototype_ `void UpdateNodesHoveredState();` — Updates the hover state of all nodes
- L131 _private prototype_ `void UpdateMonitor();` — Updates the monitor
- L134 _private prototype_ `void ResetMonitor();` — Resets the Monitor
- L137 _private prototype_ `void CreateChannelConnectors();` — Creates a a new grid of channels
- L140 _private prototype_ `FText GetHeaderText() const;` — Returns the name of the universe displayed
- L143 _private prototype_ `void HandleOnChannelHovered(int32 Channel);` — Called when a channel is hovered
- L146 _private prototype_ `void HandleOnChannelUnhovered(int32 Channel);` — Called when a channel is unhovered
- L149 _private prototype_ `FReply HandleOnMouseButtonDownOnChannel(uint32 Channel, const FPointerEvent& PointerEvent);` — Handles when a mouse button was pressed on a Channel
- L152 _private prototype_ `FReply HandleOnMouseButtonUpOnChannel(uint32 Channel, const FPointerEvent& PointerEvent);` — Handles when a mouse button was released on a Channel
- L155 _private prototype_ `FReply HandleOnDragDetectedOnChannel(uint32 Channel, const FPointerEvent& PointerEvent);` — Handles when a Channel was dragged
- L158 _private prototype_ `void HandleDragEnterChannel(uint32 Channel, const FDragDropEvent& DragDropEvent);` — Handles when drag enters a channel
- L161 _private prototype_ `void HandleDragLeaveChannel(uint32 Channel, const FDragDropEvent& DragDropEvent);` — Handles when drag leaves a channel
- L164 _private prototype_ `FReply HandleDropOntoChannel(uint32 Channel, const FDragDropEvent& DragDropEvent);` — Handles when drag dropped onto a channel
- L167 _private prototype_ `void UpdateZOrderOfNodes();` — Updates the ZOrder of all Nodes
- L170 _private prototype_ `EVisibility GetPatchedUniverseReachabilityBannerVisibility() const;` — Returns wether the out of controllers' ranges banner should be visible
- L173 _private prototype_ `void UpdatePatchedUniverseReachability();` — Updates bOutOfControllersRanges member
- L176 _private prototype_ `void OnSelectionChanged();` — Called when selection changed
- L179 _private prototype_ `void AutoAssignFixturePatches(UE::DMXEditor::AutoAssign::EAutoAssignMode AutoAssignMode);` — Auto assigns selected Fixture Patches
- L182 _private prototype_ `void AssignFixturePatches();` — Assign selected Fixture Patches
- L185 _private prototype_ `void AlignFixturePatches();` — Aligns selected Fixture Patches
- L188 _private prototype_ `void StackFixturePatches();` — Stacks selected Fixture Patches
- L191 _private prototype_ `void SpreadFixturePatchesOverUniverses();` — Spreads selected Fixture Patches over Universes
- L194 _private prototype_ `bool GetSelectedFixturePatches(TArray<UDMXEntityFixturePatch*>& OutFixturePatchArray) const;` — Gets selected fixture patches. Returns false if no patches are selected
- L197 _private prototype_ `bool DoesDMXLibraryHaveReachableUniverses() const;` — Returns true if the DMX Library has reachable Universes
- L200 _private prototype_ `UDMXEntityFixturePatch* GetTopmostFixturePatchOnChannel(uint32 Channel) const;` — Returns the Fixture Patch that is topmost under Channel
- L203 _private prototype_ `TArray<UDMXEntityFixturePatch*> GetFixturePatchesOnChannel(uint32 Channel) const;` — Returns all Fixture Patches on a Channel ID
- L206 _private prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the DMXLibrary or nullptr if not available
- L209 _private member_ `int32 UniverseID;` — The universe being displayed
- L212 _private member_ `TSharedPtr<SDMXChannelConnector> HoveredChannel;` — The hovered channel, or unset if no channel is hovered
- L215 _private member_ `int32 LastHoveredChannel = 1;` — The channel that was last hovered
- L218 _private member_ `bool bMonitorInputs = false;` — If true, monitors inputs
- L221 _private member_ `EDMXPatchedUniverseReachability PatchedUniverseReachability;` — If true the universe ID is out of controllers' ranges
- L224 _private member_ `TSharedPtr<SBorder> UniverseName;` — Widget showing the Name of the Universe
- L227 _private member_ `TSharedPtr<SGridPanel> Grid;` — Grid laying out available channels
- L230 _private member_ `TArray<TSharedRef<FDMXFixturePatchNode>> PatchedNodes;` — Patches in the grid
- L233 _private member_ `TArray<TSharedRef<SDMXChannelConnector>> ChannelConnectors;` — The Channel connectors in this universe
- L236 _private member_ `FOnDragOverChannel OnDragEnterChannel;` — Delegate executed when drag enters a Channel
- L239 _private member_ `FOnDragOverChannel OnDragLeaveChannel;` — Delegate executed when drag leaves a Channel
- L242 _private member_ `FOnDropOntoChannel OnDropOntoChannel;` — Delegate executed when a Drag Drop event was dropped onto a Channel
- L245 _private member_ `TWeakObjectPtr<UDMXEntityFixturePatch> ShiftSelectAnchorPatch;` — Anchor of Shift-Select while shift select is ongoing
- L248 _private member_ `TArray<TSharedRef<SDMXFixturePatchFragment>> FixturePatchFragmentWidgets;` — The Fixture Patch Widgets that are currently being displalyed
- L251 _private member_ `FTimerHandle RequestRefreshTimerHandle;` — Timer handle for the Request Refresh method
- L254 _private member_ `TSharedPtr<FDMXFixturePatchSharedData> SharedData;` — Shared data for fixture patch editors
- L257 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The owning editor
- L264 _private prototype_ `void RegisterCommands();` — Registers commands for this widget
- L267 _private prototype_ `TSharedRef<SWidget> CreateContextMenu(int32 Channel);` — Creates the right click context menu
- L270 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for this widget

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DMXEditor` (scope `UE`)
- L27 _namespace_ `namespace AutoAssign` (scope `UE::DMXEditor`)
- L42 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnDragOverChannel, int32 , int32 , const FDragDropEvent&);`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnDropOntoChannel, int32 , int32 , const FDragDropEvent&);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/DMXFixtureTypeFunctionsEditorFunctionItem.h` (Private)


#### class `FDMXFixtureTypeFunctionsEditorFunctionItem`  
`class FDMXFixtureTypeFunctionsEditorFunctionItem : public FDMXFixtureTypeFunctionsEditorItemBase`  
_L12-66_
- inherits: `FDMXFixtureTypeFunctionsEditorItemBase`
- desc: A Function as an item in a list
- L17 _public prototype_ `FDMXFixtureTypeFunctionsEditorFunctionItem(const TSharedRef<FDMXEditor>& InDMXEditor, TWeakObjectPtr<UDMXEntityFixtureType> InFixtureType, int32 InModeIndex, int32 InFunctionIndex);` — Constructor for Normal Functions
- L20 _public function_ `virtual EItemType GetType() const`
- L21 _public prototype_ `virtual FText GetDisplayName() const;`
- L25 _public prototype_ `int32 GetFunctionIndex() const;` — Returns the Index of the Function in the Functions array
- L28 _public prototype_ `bool HasValidAttribute() const;` — Returns true if the function has a valid Attribute
- L31 _public prototype_ `FText GetFunctionName() const;` — Returns the Function Name as Text
- L34 _public prototype_ `int32 GetStartingChannel() const;` — Returns the Starting Channel of the Function
- L37 _public prototype_ `void SetStartingChannel(int32 NewStartingChannel);` — Sets the Starting Channel of the Function
- L40 _public prototype_ `int32 GetNumChannels() const;` — Returns the Number of Channels of the Function
- L43 _public prototype_ `FDMXAttributeName GetAttributeName() const;` — Returns the Attribut Name
- L46 _public prototype_ `void SetAttributeName(const FDMXAttributeName& AttributeName) const;` — Sets the Attribut Name
- L49 _public prototype_ `bool IsValidFunctionName(const FText& InFunctionName, FText& OutInvalidReason);` — Returns if the Name is valid for the Function. If the Function Name is not valid, returns a non-empty OutInvalidReason
- L52 _public prototype_ `void SetFunctionName(const FText& DesiredFunctionName, FText& OutUniqueFunctionName);` — Sets a Function Name, makes it unique. Returns the OutUniqueFunctionName as output argument
- L55 _public prototype_ `void DeleteFunction();` — Deletes the function this item stands for
- L58 _public prototype_ `TSharedPtr<FDMXFixtureTypeSharedData> GetFixtureTypeSharedData() const;` — Returns the Fixture Type Shared Data for the editor that makes use of this Item
- L62 _private member_ `int32 ModeIndex = INDEX_NONE;` — The index of the Mode the Function resides in, in the Fixture Type's Modes array
- L65 _private member_ `int32 FunctionIndex = INDEX_NONE;` — The index of the Function in the Mode

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/DMXFixtureTypeFunctionsEditorItemBase.h` (Private)


#### class `FDMXFixtureTypeFunctionsEditorItemBase`  
`class FDMXFixtureTypeFunctionsEditorItemBase : public TSharedFromThis<FDMXFixtureTypeFunctionsEditorItemBase>`  
_L14-63_
- inherits: `TSharedFromThis<FDMXFixtureTypeFunctionsEditorItemBase>`
- desc: An item in a Functions list
- L19 _public prototype_ `FDMXFixtureTypeFunctionsEditorItemBase(const TSharedRef<FDMXEditor>& InDMXEditor, TWeakObjectPtr<UDMXEntityFixtureType> InFixtureType, int32 InModeIndex);` — Constructor
- L22 _public function_ `virtual ~FDMXFixtureTypeFunctionsEditorItemBase()` — Destructor
- L31 _public prototype_ `virtual EItemType GetType() const = 0;` — Returns the type of the item
- L34 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns a display name for the icon, for example to use it with the warning and error status
- L37 _public function_ `TSharedPtr<FDMXEditor> GetDMXEditor() const` — Returns the DMX Editor this item is used in
- L40 _public function_ `TWeakObjectPtr<UDMXEntityFixtureType> GetFixtureType() const` — Returns the Fixture Type of the Item
- L43 _public prototype_ `int32 GetModeIndex() const;` — Returns the Index of the Mode in the Modes array
- L46 _public member_ `FText WarningStatus;` — The warning status of the item. If an empty text is set it means there is no warning.
- L49 _public member_ `FText ErrorStatus;` — The error status of the item. If an empty text is set it means there is no error.
- L53 _protected member_ `TWeakObjectPtr<UDMXEntityFixtureType> FixtureType;` — The Fixture Type which owns the Function
- L56 _protected member_ `int32 ModeIndex = INDEX_NONE;` — The index of the Mode the Function resides in, in the Fixture Type's Modes array
- L59 _protected member_ `TSharedPtr<FDMXFixtureTypeSharedData> SharedData;` — Fixture type shared data
- L62 _protected member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget

#### enum `FDMXFixtureTypeFunctionsEditorItemBase::EItemType`  
`enum class EItemType : uint8`  
_L24-28_
- L26 _public enumerator_ `Function`
- L27 _public enumerator_ `Matrix`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/DMXFixtureTypeFunctionsEditorMatrixItem.h` (Private)


#### class `FDMXFixtureTypeFunctionsEditorMatrixItem`  
`class FDMXFixtureTypeFunctionsEditorMatrixItem : public FDMXFixtureTypeFunctionsEditorItemBase`  
_L12-35_
- inherits: `FDMXFixtureTypeFunctionsEditorItemBase`
- desc: The Matrix as an item in a list of Functions
- L17 _public prototype_ `FDMXFixtureTypeFunctionsEditorMatrixItem(const TSharedRef<FDMXEditor>& InDMXEditor, TWeakObjectPtr<UDMXEntityFixtureType> InFixtureType, int32 InModeIndex);` — Constructor for Normal Functions
- L20 _public function_ `virtual EItemType GetType() const`
- L21 _public prototype_ `virtual FText GetDisplayName() const;`
- L25 _public prototype_ `int32 GetStartingChannel() const;` — Returns the Starting Channel of the Matrix
- L28 _public prototype_ `void SetStartingChannel(int32 NewStartingChannel);` — Sets the Starting Channel of the Matrix
- L31 _public prototype_ `const FDMXFixtureMatrix& GetFixtureMatrix() const;` — Returns the FixtureMatrix
- L34 _public prototype_ `int32 GetNumChannels() const;` — Returns the Number of Channels of the Matrix

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/DMXFixtureTypeMatrixFunctionsEditorItem.h` (Private)


#### class `FDMXFixtureTypeMatrixFunctionsEditorItem`  
`class FDMXFixtureTypeMatrixFunctionsEditorItem : public TSharedFromThis<FDMXFixtureTypeMatrixFunctionsEditorItem>`  
_L16-56_
- inherits: `TSharedFromThis<FDMXFixtureTypeMatrixFunctionsEditorItem>`
- desc: A Cell Attribute item in a list
- L21 _public prototype_ `FDMXFixtureTypeMatrixFunctionsEditorItem(const TSharedRef<FDMXEditor>& InDMXEditor, TWeakObjectPtr<UDMXEntityFixtureType> InFixtureType, int32 InModeIndex, int32 InCellAttributeIndex);` — Constructor
- L24 _public prototype_ `FDMXAttributeName GetCellAttributeName() const;` — Returns the Attribut Name
- L27 _public prototype_ `void SetCellAttributeName(const FDMXAttributeName& CellAtributeName);` — Sets the Attribut Name
- L30 _public prototype_ `void RemoveFromFixtureType();` — Removes the Cell Attribute from the Fixture type
- L33 _public member_ `FText ChannelNumberText;` — The channel number displayed for the row
- L36 _public member_ `FText WarningStatus;` — The warning status of the row. If an empty text is set it means there is no warning.
- L39 _public member_ `FText ErrorStatus;` — The error status of the row. If an empty text is set it means there is no error.
- L43 _private member_ `int32 ModeIndex = INDEX_NONE;` — The index of the mode in the Fixture Type's Modes array
- L46 _private member_ `int32 CellAttributeIndex = INDEX_NONE;` — The index of the mode in the Fixture Type's Modes array
- L49 _private member_ `TWeakObjectPtr<UDMXEntityFixtureType> FixtureType;` — The Fixture Type which owns the Mode
- L52 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> SharedData;` — Fixture type shared data
- L55 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this item

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/DMXFixtureTypeModesEditorModeItem.h` (Private)


#### class `FDMXFixtureTypeModesEditorModeItem`  
`class FDMXFixtureTypeModesEditorModeItem : public TSharedFromThis<FDMXFixtureTypeModesEditorModeItem>`  
_L14-54_
- inherits: `TSharedFromThis<FDMXFixtureTypeModesEditorModeItem>`
- desc: A Mode as an item in a list
- L19 _public prototype_ `FDMXFixtureTypeModesEditorModeItem(const TSharedRef<FDMXEditor>& InDMXEditor, TWeakObjectPtr<UDMXEntityFixtureType> InFixtureType, int32 InModeIndex);` — Constructor
- L22 _public prototype_ `int32 GetModeIndex() const;` — Returns the Index of the Mode in the Modes array
- L25 _public prototype_ `FText GetModeName() const;` — Returns the Mode Name as Text
- L31 _public function_ `int32 GetGDTFModeNumber() const` — GDTF modes typically start with "Mode" and a number, e.g. "Mode 3", the latest revision is the last entry. This function returns the number of the mode or INDEX_NONE if the mode is not enumerated.
- L34 _public prototype_ `bool IsValidModeName(const FText& InModeName, FText& OutInvalidReason);` — Returns if the Name is valid for the Mode. If the Mode Name is not valid, returns a non-empty OutInvalidReason
- L37 _public prototype_ `void SetModeName(const FText& DesiredModeName, FText& OutUniqueModeName);` — Sets a Mode Name, makes it unique. Returns the OutUniqueModeName as output argument
- L41 _private member_ `int32 ModeIndex = INDEX_NONE;` — The index of the mode in the Fixture Type's Modes array
- L44 _private member_ `int32 GDTFModeNumber = INDEX_NONE;` — The number of the mode or INDEX_NONE if the mode is not enumerated. See GetGDTFModeNumber.
- L47 _private member_ `TWeakObjectPtr<UDMXEntityFixtureType> FixtureType;` — The Fixture Type which owns the Mode
- L50 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> SharedData;` — Fixture type shared data
- L53 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureFunctionEditor.h` (Private)


#### class `SDMXFixtureFunctionEditor`  
`class SDMXFixtureFunctionEditor : public SCompoundWidget , public FNotifyHook`  
_L20-84_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Editor for a single Function struct inside a UDMXEntityFixtureType.
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureFunctionEditor)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);`
- L35 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L36 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent & PropertyChangedEvent, FProperty * PropertyThatChanged) override;`
- L41 _private prototype_ `void Refresh();` — Refereshes the Mode displayed
- L44 _private prototype_ `void SetFunction(UDMXEntityFixtureType* InFixtureType, int32 InModeIndex, int32 InFunctionIndex);` — Sets the Mode that is being edited
- L47 _private prototype_ `void OnFixtureTypePropertiesChanged(const UDMXEntityFixtureType* FixtureType);` — Called when the properties of the fixture type changed
- L50 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;` — Returns true if the properties are visible
- L53 _private prototype_ `FDMXFixtureMode* GetModeBeingEdited() const;` — Returns the Mode currently being edited, or nullptr if the current selection cannot be resolved.
- L56 _private prototype_ `FDMXFixtureFunction* GetFunctionBeingEdited() const;` — Returns the Function currently being edited
- L59 _private member_ `TWeakObjectPtr<UDMXEntityFixtureType> WeakFixtureType;` — Fixture type of the Function currently being edited
- L62 _private member_ `int32 ModeIndex;` — Mode Index currently being edited
- L65 _private member_ `int32 FunctionIndex;` — Function Index currently being edited
- L68 _private member_ `TUniquePtr<FScopedTransaction> Transaction;` — The current transaction or nullptr if there's no transaction ongoing
- L71 _private member_ `TSharedPtr<IStructureDetailsView> StructDetailsView;` — Details view for the Function Struct being edited
- L74 _private member_ `TSharedPtr<SWidget> StructDetailsViewWidget;` — Widget of the Details view
- L77 _private member_ `TSharedPtr<STextBlock> InfoTextBlock;` — Text block that displays info in case the struct details view cannot be shown
- L80 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> FixtureTypeSharedData;` — Shared Data for
- L83 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureModeEditor.h` (Private)


#### class `SDMXFixtureModeEditor`  
`class SDMXFixtureModeEditor : public SCompoundWidget , public FNotifyHook`  
_L24-88_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Editor for a single Mode struct inside a UDMXEntityFixtureType.
- L29 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureModeEditor)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);`
- L38 _public prototype_ `void RequestRefresh();` — Requests to refresh the widget on the next tick
- L42 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L43 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent & PropertyChangedEvent, FProperty * PropertyThatChanged) override;`
- L48 _private prototype_ `void RefreshInternal();` — Refereshes the Mode displayed instantly
- L51 _private prototype_ `void SetMode(UDMXEntityFixtureType* InFixtureType, int32 InModeIndex);` — Sets the Mode that is being edited
- L54 _private prototype_ `void OnFixtureTypePropertiesChanged(const UDMXEntityFixtureType* FixtureType);` — Called when the properties of the fixture type changed
- L57 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;` — Returns true if the properties are visible
- L60 _private prototype_ `FDMXFixtureMode* GetModeBeingEdited() const;` — Returns the Mode currently being edited
- L63 _private member_ `TWeakObjectPtr<UDMXEntityFixtureType> WeakFixtureType;` — Fixture type of the Mode currently being edited
- L66 _private member_ `int32 ModeIndex;` — Mode Index currently being edited
- L69 _private member_ `TUniquePtr<FScopedTransaction> Transaction;` — The current transaction or nullptr if there's no transaction ongoing
- L72 _private member_ `TSharedPtr<IStructureDetailsView> StructDetailsView;` — Details view for the Mode Struct being edited
- L75 _private member_ `TSharedPtr<SWidget> StructDetailsViewWidget;` — Widget of the Details view
- L78 _private member_ `TSharedPtr<STextBlock> InfoTextBlock;` — Text block that displays info in case the struct details view cannot be shown
- L81 _private member_ `FTimerHandle RefreshHandle;` — Timer handle set while refresh is requested but not carried out yet
- L84 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> FixtureTypeSharedData;` — Shared Data for
- L87 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeEditor.h` (Private)


#### class `SDMXFixtureTypeEditor`  
`class SDMXFixtureTypeEditor : public SDMXEntityEditor`  
_L18-56_
- inherits: `SDMXEntityEditor`
- desc: The whole editor for Fixture Types
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeEditor)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);` — Constructs this widget
- L32 _public prototype_ `void RequestRenameOnNewEntity(const UDMXEntity* InEntity, ESelectInfo::Type SelectionType);` — Begin SDMXEntityEditorTab interface
- L33 _public prototype_ `void SelectEntity(UDMXEntity* InEntity, ESelectInfo::Type InSelectionType = ESelectInfo::Type::Direct);`
- L34 _public prototype_ `void SelectEntities(const TArray<UDMXEntity*>& InEntities, ESelectInfo::Type SelectionType = ESelectInfo::Type::Direct);`
- L35 _public prototype_ `TArray<UDMXEntity*> GetSelectedEntities() const;`
- L40 _private prototype_ `void OnFixtureTypesSelected();` — Called when fixture types were selected
- L43 _private prototype_ `TSharedRef<IDetailsView> GenerateFixtureTypeDetailsView() const;` — Generates a details view for the Fixture Type Details
- L46 _private member_ `TSharedPtr<SDMXFixtureTypeTree> FixtureTypeTree;` — Tree of Fixture Types
- L49 _private member_ `TSharedPtr<IDetailsView> FixtureTypeDetailsView;` — Details View for the selected Fixture Type
- L52 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> FixtureTypeSharedData;` — Shared Data for Fixture Types
- L55 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — Pointer back to the DMXEditor tool that owns us

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeFunctionsEditor.h` (Private)


#### class `SDMXFixtureTypeFunctionsEditor`  
`class SDMXFixtureTypeFunctionsEditor : public SCompoundWidget`  
_L28-147_
- inherits: `SCompoundWidget`
- desc: Editor for the Functions Array of the Modes in a Fixture Type
- L42 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeFunctionsEditor)`
- L48 _public prototype_ `virtual ~SDMXFixtureTypeFunctionsEditor();` — Destructor
- L51 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);` — Constructs this widget
- L55 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L60 _private prototype_ `void RebuildList();` — Rebuilds the Functions List
- L63 _private prototype_ `void RebuildListSource();` — Rebuilds the List Source
- L66 _private prototype_ `void UpdateItemsStatus();` — Updates the Status of each Item
- L69 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* ChangedFixtureType);` — Called when a fixture type changed
- L72 _private prototype_ `TSharedRef<SHeaderRow> GenerateHeaderRow();` — Generates a heaer row for the Function List
- L75 _private prototype_ `void SaveHeaderRowSettings();` — Saves header row settings in project settings
- L78 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row in the List of Functions
- L81 _private prototype_ `bool IsItemSelectedExclusively(TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase> InItem) const;` — Returns true if the item is selected
- L84 _private prototype_ `void OnListSelectionChanged(TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase> NewlySelectedItem, ESelectInfo::Type SelectInfo);` — Called when the selelction in the list changed
- L87 _private prototype_ `void OnSharedDataFunctionOrMatrixSelectionChanged();` — Called when the selected Function or Matrix in Fixture Type Shared Data Changed
- L90 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);` — Called when the Search Text changed
- L93 _private prototype_ `TArray<int32> GetSelectionAsFunctionIndices() const;` — Returns the selected Function Indices in the Mode's Function array
- L96 _private prototype_ `bool IsMatrixSelected() const;` — Returns true if the Matrix is selected
- L99 _private prototype_ `TSharedPtr<SWidget> OnListContextMenuOpening();` — Called when the context menu of the list is opening
- L102 _private member_ `TSharedPtr<SBorder> ListContentBorder;` — Border that holds the list content, or widgets showing reasons why no list can be drawn
- L105 _private member_ `TSharedPtr<FDMXFixtureTypeFunctionsEditorFunctionListType> ListView;` — The the list of Functions
- L108 _private member_ `TArray<TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase>> ListSource;` — Source array for the Functions List
- L111 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;` — The Header Row of the List
- L114 _private member_ `TArray<TSharedPtr<SDMXFixtureTypeFunctionsEditorFunctionRow>> FunctionRows;` — Rows of Mode widgets in the List
- L117 _private member_ `FText SearchText;` — Search Text entered in the Category Row
- L120 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> FixtureTypeSharedData;` — Shared data for Fixture Types
- L123 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The Fixture Type Editor that owns this widget
- L131 _private prototype_ `void RegisterCommands();` — Registers the commands
- L133 _private prototype_ `bool CanCutItems() const;`
- L134 _private prototype_ `void OnCutSelectedItems();`
- L135 _private prototype_ `bool CanCopyItems() const;`
- L136 _private prototype_ `void OnCopySelectedItems();`
- L137 _private prototype_ `bool CanPasteItems() const;`
- L138 _private prototype_ `void OnPasteItems();`
- L139 _private prototype_ `bool CanDuplicateItems() const;`
- L140 _private prototype_ `void OnDuplicateItems();`
- L141 _private prototype_ `bool CanDeleteItems() const;`
- L142 _private prototype_ `void OnDeleteItems();`
- L143 _private prototype_ `bool CanRenameItem() const;`
- L144 _private prototype_ `void OnRenameItem();`
- L146 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### struct `SDMXFixtureTypeFunctionsEditor::FCollumnID`  
`struct FCollumnID`  
_L33-40_
- desc: Collumn IDs in the Functions Editor
- L35 _public member_ `static const FName Status;`
- L36 _public member_ `static const FName Channel;`
- L37 _public member_ `static const FName Name;`
- L38 _public member_ `static const FName Attribute;`
- L39 _public member_ `static const FName DeleteAttribute;`

#### Free symbols / members of external scopes

- L25 _typedef_ `using FDMXFixtureTypeFunctionsEditorFunctionListType = SListView<TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase>>;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeFunctionsEditorCategoryRow.h` (Private)


#### class `SDMXFixtureTypeFunctionsEditorCategoryRow`  
`class SDMXFixtureTypeFunctionsEditorCategoryRow : public SCompoundWidget`  
_L14-47_
- inherits: `SCompoundWidget`
- desc: The Category Row for the Functions Editor. Note, not a TableRow, but just the topmost widget.
- L18 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeFunctionsEditorCategoryRow)`
- L22 _public prototype_ `SLATE_EVENT(FOnTextChanged, OnSearchTextChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);` — Called when the search text changed
- L31 _private prototype_ `bool GetIsAddFunctionButtonEnabled() const;` — Called to determine wether the 'Add New Mode' button is enabled
- L34 _private prototype_ `FText GetAddFunctionButtonTooltipText() const;` — Called to get the tooltip text of the 'Add New Mode' button
- L37 _private prototype_ `FReply OnAddFunctionButtonClicked() const;` — Called when the 'Add New Mode' button was clicked
- L40 _private prototype_ `FText GetAddFunctionButtonText() const;` — Called to get the text of the 'Add New Mode' button
- L43 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> SharedData;` — Fixture type shared data
- L46 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeFunctionsEditorFunctionRow.h` (Private)


#### class `SDMXFixtureTypeFunctionsEditorFunctionRow`  
`class SDMXFixtureTypeFunctionsEditorFunctionRow : public SMultiColumnTableRow<TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase>>`  
_L21-105_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase>>`
- desc: Function as a row in a list
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeFunctionsEditorFunctionRow)`
- L29 _public prototype_ `SLATE_EVENT(FIsSelected, IsSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FDMXFixtureTypeFunctionsEditorFunctionItem>& InFunctionItem);` — Callback to check if the row is selected (should be hooked up if a parent widget is handling selection or focus)
- L37 _public prototype_ `void EnterFunctionNameEditingMode();` — Enters editing the Function name in its text box
- L40 _public function_ `const TSharedPtr<FDMXFixtureTypeFunctionsEditorFunctionItem> GetFunctionItem() const` — Returns the Function Item
- L43 _public function_ `bool IsBeginDragged() const` — Returns true if the row is being dragged
- L46 _public function_ `void SetIsBeingDragged(bool bDragged)` — Sets if the row is being dragged in a drag drop op
- L50 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L54 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L59 _private prototype_ `FReply OnRowDrop(const FDragDropEvent& DragDropEvent);` — Called when a dragged row is dropped onto this row
- L62 _private prototype_ `void OnRowDragEnter(const FDragDropEvent& DragDropEvent);` — Called when a dragged row enters this row
- L65 _private prototype_ `void OnRowDragLeave(const FDragDropEvent& DragDropEvent);` — Called when a dragged row leaves this row
- L68 _private prototype_ `bool OnVerifyStartingChannelChanged(const FText& InNewText, FText& OutErrorMessage);` — Called to verify the Starting Channel when the User is interactively changing it
- L71 _private prototype_ `void OnStartingChannelCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when the Starting Channel was comitted
- L74 _private prototype_ `bool OnVerifyFunctionNameChanged(const FText& InNewText, FText& OutErrorMessage);` — Called to verify the Function Name when the User is interactively changing it
- L77 _private prototype_ `void OnFunctionNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when Function Name was comitted
- L80 _private prototype_ `FName GetAttributeName() const;` — Gets the Attribute Name of the Function
- L83 _private prototype_ `void OnUserChangedAttributeName(FName NewValue);` — Called when the Attribute Name changed
- L86 _private prototype_ `FReply OnDeleteAttributeClicked();` — Called when the delete attribute button was clicked
- L89 _private member_ `bool bIsBeingDragged = false;` — True while this is being dragged in a drag drop op
- L92 _private member_ `bool bIsDragDropTarget = false;` — True while this is hoverd in a drag drop op
- L95 _private member_ `TSharedPtr<SInlineEditableTextBlock> StartingChannelEditableTextBlock;` — The mode name edit widget
- L98 _private member_ `TSharedPtr<SInlineEditableTextBlock> FunctionNameEditableTextBlock;` — The mode name edit widget
- L101 _private member_ `TSharedPtr<FDMXFixtureTypeFunctionsEditorFunctionItem> FunctionItem;` — The Function Item this row displays
- L104 _private member_ `FIsSelected IsSelected;` — Slate arguments

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeFunctionsEditorMatrixRow.h` (Private)


#### class `SDMXFixtureTypeFunctionsEditorMatrixRow`  
`class SDMXFixtureTypeFunctionsEditorMatrixRow : public SMultiColumnTableRow<TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase>>`  
_L17-79_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXFixtureTypeFunctionsEditorItemBase>>`
- desc: The Matrix as row in a list of Functions and the Matrix row
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeFunctionsEditorMatrixRow)`
- L24 _public prototype_ `SLATE_EVENT(FIsSelected, IsSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FDMXFixtureTypeFunctionsEditorMatrixItem>& InMatrixItem);` — Callback to check if the row is selected (should be hooked up if a parent widget is handling selection or focus)
- L32 _public function_ `const TSharedPtr<FDMXFixtureTypeFunctionsEditorMatrixItem> GetMatrixItem() const` — Returns the Matrix Item
- L35 _public function_ `bool IsBeginDragged() const` — Returns true if the row is being dragged
- L38 _public function_ `void SetIsBeingDragged(bool bDragged)` — Sets if the row is being dragged in a drag drop op
- L42 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L51 _private prototype_ `FReply OnRowDrop(const FDragDropEvent& DragDropEvent);` — Called when a dragged row is dropped onto this row
- L54 _private prototype_ `void OnRowDragEnter(const FDragDropEvent& DragDropEvent);` — Called when a dragged row enters this row
- L57 _private prototype_ `void OnRowDragLeave(const FDragDropEvent& DragDropEvent);` — Called when a dragged row leaves this row
- L60 _private prototype_ `bool OnVerifyStartingChannelChanged(const FText& InNewText, FText& OutErrorMessage);` — Called to verify the Starting Channel when the User is interactively changing it
- L63 _private prototype_ `void OnStartingChannelCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when the Starting Channel was comitted
- L66 _private member_ `bool bIsBeingDragged = false;` — True while this is being dragged in a drag drop op
- L69 _private member_ `bool bIsDragDropTarget = false;` — True while this is hoverd in a drag drop op
- L72 _private member_ `TSharedPtr<FDMXFixtureTypeFunctionsEditorMatrixItem> MatrixItem;` — The Mode Item this row displays
- L75 _private member_ `TSharedPtr<SInlineEditableTextBlock> StartingChannelEditableTextBlock;` — Text block to display and edit the matrix starting channel
- L78 _private member_ `FIsSelected IsSelected;` — Slate arguments

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeMatrixFunctionsEditor.h` (Private)


#### struct `FDMXFixtureTypeMatrixFunctionsEditorCollumnIDs`  
`struct FDMXFixtureTypeMatrixFunctionsEditorCollumnIDs`  
_L20-26_
- desc: Collumn IDs in the Matrix Functions Editor
- L22 _public member_ `static const FName Status;`
- L23 _public member_ `static const FName Channel;`
- L24 _public member_ `static const FName Attribute;`
- L25 _public member_ `static const FName DeleteAttribute;`

#### class `SDMXFixtureTypeMatrixFunctionsEditor`  
`class SDMXFixtureTypeMatrixFunctionsEditor : public SCompoundWidget`  
_L30-72_
- inherits: `SCompoundWidget`
- desc: Editor for the Cell Attributes Array of the Modes in a Fixture Type
- L34 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeMatrixFunctionsEditor)`
- L37 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor, TWeakObjectPtr<UDMXEntityFixtureType> InFixtureType, int32 InModeIndex);`
- L44 _private prototype_ `TSharedRef<SHeaderRow> GenerateHeaderRow();` — Generates a heaer row for the Function List
- L47 _private prototype_ `TSharedRef<ITableRow> OnGenerateCellAttributeRow(TSharedPtr<FDMXFixtureTypeMatrixFunctionsEditorItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a Cell Attributes List View row is generated
- L50 _private prototype_ `void OnCellAttributeRowRequestDelete(TSharedPtr<FDMXFixtureTypeMatrixFunctionsEditorItem> RowItem);` — Called when a Cell Attribute Row wants to be deleted
- L53 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* ChangedFixtureType);` — Called when a fixture type changed
- L56 _private prototype_ `void RefreshList();` — Refreshes the List of Matrix Functions
- L59 _private member_ `int32 ModeIndex = INDEX_NONE;` — The index of the mode in the Fixture Type's Modes array
- L62 _private member_ `TWeakObjectPtr<UDMXEntityFixtureType> FixtureType;` — The Fixture Type which owns the Mode
- L65 _private member_ `TSharedPtr<SListView<TSharedPtr<FDMXFixtureTypeMatrixFunctionsEditorItem>>> CellAttributesListView;` — List View of Cell Attributes
- L68 _private member_ `TArray<TSharedPtr<FDMXFixtureTypeMatrixFunctionsEditorItem>> CellAttributesListSource;` — Source for the Cell Attributes List View
- L71 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — Pointer back to the DMXEditor tool that owns this widget

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeMatrixFunctionsEditorCategoryRow.h` (Private)


#### class `SDMXFixtureTypeMatrixFunctionsEditorCategoryRow`  
`class SDMXFixtureTypeMatrixFunctionsEditorCategoryRow : public SCompoundWidget`  
_L13-43_
- inherits: `SCompoundWidget`
- desc: The Category Row for the Cell Attributes Editor. Note, not a TableRow, but just the topmost widget.
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeMatrixFunctionsEditorCategoryRow)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);`
- L27 _private prototype_ `bool GetIsAddCellAttributeButtonEnabled() const;` — Called to determine wether the 'Add New Mode' button is enabled
- L30 _private prototype_ `FText GetAddCellAttributeButtonTooltipText() const;` — Called to get the tooltip text of the 'Add New Mode' button
- L33 _private prototype_ `FReply OnAddCellAttributeButtonClicked() const;` — Called when the 'Add New Mode' button was clicked
- L36 _private prototype_ `FText GetAddCellAttributeButtonText() const;` — Called to get the text of the 'Add New Mode' button
- L39 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> SharedData;` — Fixture type shared data
- L42 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeMatrixFunctionsEditorMatrixRow.h` (Private)


#### class `SDMXFixtureTypeMatrixFunctionsEditorMatrixRow`  
`class SDMXFixtureTypeMatrixFunctionsEditorMatrixRow : public SMultiColumnTableRow<TSharedPtr<FDMXFixtureTypeMatrixFunctionsEditorItem>>`  
_L19-56_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXFixtureTypeMatrixFunctionsEditorItem>>`
- desc: A Matrix Function as a row in a list
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeMatrixFunctionsEditorMatrixRow)`
- L26 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnRequestDelete) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FDMXFixtureTypeMatrixFunctionsEditorItem> InCellAttributeItem);`
- L35 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L40 _private prototype_ `FReply OnDeleteCellAttributeClicked();` — Called when the delete Cell Attribute Button was clicked
- L43 _private prototype_ `FName GetCellAttributeName() const;` — Returns the Name of the Cell Attribute
- L46 _private prototype_ `void SetCellAttributeName(FName NewValue);` — Sets the Cell Attribute of the Matrix
- L49 _private member_ `TSharedPtr<SPopupErrorText> PopupErrorText;` — The popup error displayed when an invalid name is set
- L52 _private member_ `TSharedPtr<FDMXFixtureTypeMatrixFunctionsEditorItem> CellAttributeItem;` — The Mode Item this row displays
- L55 _private member_ `FSimpleDelegate OnRequestDelete;` — Delegate executed when the Matrix Row requests to be deleted

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeModesEditor.h` (Private)


#### class `SDMXFixtureTypeModesEditor`  
`class SDMXFixtureTypeModesEditor : public SCompoundWidget`  
_L24-130_
- inherits: `SCompoundWidget`
- desc: The editor for the Fixure Type Modes array
- L28 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeModesEditor)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);`
- L38 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L43 _private prototype_ `void RebuildList();` — Rebuilds the List of Modes
- L46 _private prototype_ `void RebuildSelection();` — Rebuilds selection from what's selected in Fixture Type Shared Data
- L49 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* ChangedFixtureType);` — Called when a fixture type changed
- L52 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);` — Called when the Search Text changed
- L55 _private prototype_ `TSharedRef<ITableRow> OnGenerateModeRow(TSharedPtr<FDMXFixtureTypeModesEditorModeItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row in the List of Modes
- L58 _private prototype_ `bool IsItemSelectedExclusively(TSharedPtr<FDMXFixtureTypeModesEditorModeItem> InItem) const;` — Returns true if the item is selected
- L61 _private prototype_ `void OnListSelectionChanged(TSharedPtr<FDMXFixtureTypeModesEditorModeItem> NewlySelectedItem, ESelectInfo::Type SelectInfo);` — Called when the selelction in the list changed
- L64 _private prototype_ `void OnFixtureTypeSharedDataSelectedModes();` — Called when modes were selected in Fixture Type Shared Data
- L67 _private prototype_ `void OnRevisionCheckBoxStateChanged(ECheckBoxState NewCheckState);` — Called when the show all revisions check box state changed
- L70 _private prototype_ `EVisibility GetRevisionCheckBoxVisibility() const;` — Returns the visibility of the Revisions section
- L73 _private prototype_ `TArray<int32> GetListSelectionAsModeIndices() const;` — Returns the selected Modes in the List as Indices in the Modes array
- L76 _private prototype_ `TSharedPtr<SWidget> OnListContextMenuOpening();` — Called when the context menu of the list is opening
- L79 _private member_ `TArray<FDMXFixtureMode> CachedModes;` — Cached modes for comparison
- L82 _private member_ `TSharedPtr<SBorder> ListContentBorder;` — Border that holds the list content, or widgets showing reasons why no list can be drawn
- L85 _private member_ `TSharedPtr<SListView<TSharedPtr<FDMXFixtureTypeModesEditorModeItem>>> ListView;` — The the list of Modes
- L88 _private member_ `TArray<TSharedPtr<FDMXFixtureTypeModesEditorModeItem>> ListSource;` — Source array for the Modes List
- L91 _private member_ `TArray<TSharedPtr<SDMXFixtureTypeModesEditorModeRow>> ModeRows;` — Rows of Mode widgets in the list
- L94 _private member_ `TSharedPtr<SCheckBox> RevisionCheckBox;` — The revision check box
- L97 _private member_ `bool bHasModeRevisions = false;` — True if mode revisions are available
- L100 _private member_ `FText SearchText;` — Search Text entered in the header row
- L103 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> FixtureTypeSharedData;` — Shared data for Fixture Types
- L106 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The Fixture Type Editor that owns this widget
- L114 _private prototype_ `void RegisterCommands();` — Registers the commands
- L116 _private prototype_ `bool CanCutItems() const;`
- L117 _private prototype_ `void OnCutSelectedItems();`
- L118 _private prototype_ `bool CanCopyItems() const;`
- L119 _private prototype_ `void OnCopySelectedItems();`
- L120 _private prototype_ `bool CanPasteItems() const;`
- L121 _private prototype_ `void OnPasteItems();`
- L122 _private prototype_ `bool CanDuplicateItems() const;`
- L123 _private prototype_ `void OnDuplicateItems();`
- L124 _private prototype_ `bool CanDeleteItems() const;`
- L125 _private prototype_ `void OnDeleteItems();`
- L126 _private prototype_ `bool CanRenameItem() const;`
- L127 _private prototype_ `void OnRenameItem();`
- L129 _private member_ `TSharedPtr<FUICommandList> CommandList;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeModesEditorCategoryRow.h` (Private)


#### class `SDMXFixtureTypeModesEditorCategoryRow`  
`class SDMXFixtureTypeModesEditorCategoryRow : public SCompoundWidget`  
_L14-47_
- inherits: `SCompoundWidget`
- desc: The Category Row for the Modes Editor. Note, not a TableRow, but just the topmost widget.
- L18 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeModesEditorCategoryRow)`
- L22 _public prototype_ `SLATE_EVENT(FOnTextChanged, OnSearchTextChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXEditor>& InDMXEditor);` — Called when the search text changed
- L31 _private prototype_ `bool GetIsAddModeButtonEnabled() const;` — Called to determine wether the 'Add New Mode' button is enabled
- L34 _private prototype_ `FText GetAddModeButtonTooltipText() const;` — Called to get the tooltip text of the 'Add New Mode' button
- L37 _private prototype_ `FReply OnAddModeButtonClicked() const;` — Called when the 'Add New Mode' button was clicked
- L40 _private prototype_ `FText GetAddModeButtonText() const;` — Called to get the text of the 'Add New Mode' button
- L43 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> SharedData;` — Fixture type shared data
- L46 _private member_ `TWeakPtr<FDMXEditor> WeakDMXEditor;` — The DMX Editor that owns this widget

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeModesEditorModeRow.h` (Private)


#### class `SDMXFixtureTypeModesEditorModeRow`  
`class SDMXFixtureTypeModesEditorModeRow : public STableRow<TSharedPtr<FDMXFixtureTypeModesEditorModeItem>>`  
_L19-58_
- inherits: `STableRow<TSharedPtr<FDMXFixtureTypeModesEditorModeItem>>`
- desc: Mode as a row in a list
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeModesEditorModeRow)`
- L27 _public prototype_ `SLATE_EVENT(FIsSelected, IsSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FDMXFixtureTypeModesEditorModeItem> InModeItem);` — Callback to check if the row is selected (should be hooked up if a parent widget is handling selection or focus)
- L35 _public prototype_ `void EnterModeNameEditingMode();` — Enters editing the Mode name in its text box
- L38 _public function_ `const TSharedPtr<FDMXFixtureTypeModesEditorModeItem> GetModeItem() const` — Returns the Mode Item
- L42 _private prototype_ `bool OnVerifyModeNameChanged(const FText& InNewText, FText& OutErrorMessage);` — Called to verify the Mode Name when the User is interactively changing it
- L45 _private prototype_ `void OnModeNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when Mode Name was comitted
- L48 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableTextBlock;` — The mode name edit widget
- L51 _private member_ `TSharedPtr<SPopupErrorText> PopupErrorText;` — The popup error displayed when an invalid name is set
- L54 _private member_ `TSharedPtr<FDMXFixtureTypeModesEditorModeItem> ModeItem;` — The Mode Item this row displays
- L57 _private member_ `FIsSelected IsSelected;` — Slate arguments

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeTree.h` (Private)


#### class `SDMXFixtureTypeTree`  
`class SDMXFixtureTypeTree : public SDMXEntityTreeViewBase`  
_L18-92_
- inherits: `SDMXEntityTreeViewBase`
- desc: A tree of Fixture Types in a DMX Library.
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeTree)`
- L25 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FDMXEditor>, DMXEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The DMX Editor that owns this widget
- L33 _public function_ `virtual ~SDMXFixtureTypeTree()` — Destructor
- L36 _public prototype_ `TSharedPtr<FDMXEntityTreeEntityNode> CreateEntityNode(UDMXEntity* Entity);` — Creates a Node for the entity
- L40 _protected prototype_ `virtual TSharedRef<SWidget> GenerateAddNewEntityButton();`
- L41 _protected prototype_ `virtual void RebuildNodes(const TSharedPtr<FDMXEntityTreeRootNode>& InRootNode);`
- L42 _protected prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXEntityTreeNodeBase> Node, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _protected prototype_ `virtual TSharedPtr<SWidget> OnContextMenuOpen();`
- L44 _protected prototype_ `virtual void OnSelectionChanged(TSharedPtr<FDMXEntityTreeNodeBase> InSelectedNodePtr, ESelectInfo::Type SelectInfo);`
- L45 _protected prototype_ `virtual void OnCutSelectedNodes();`
- L46 _protected prototype_ `virtual bool CanCutNodes() const;`
- L47 _protected prototype_ `virtual void OnCopySelectedNodes();`
- L48 _protected prototype_ `virtual bool CanCopyNodes() const;`
- L49 _protected prototype_ `virtual void OnPasteNodes();`
- L50 _protected prototype_ `virtual bool CanPasteNodes() const;`
- L51 _protected prototype_ `virtual bool CanDuplicateNodes() const;`
- L52 _protected prototype_ `virtual void OnDuplicateNodes();`
- L53 _protected prototype_ `virtual void OnDeleteNodes();`
- L54 _protected prototype_ `virtual bool CanDeleteNodes() const;`
- L55 _protected prototype_ `virtual void OnRenameNode();`
- L56 _protected prototype_ `virtual bool CanRenameNode() const;`
- L61 _private prototype_ `void OnFixtureTypesSelected();` — Called when Fixture Types were selected in Fixture Type Shared Data
- L64 _private prototype_ `void OnFixturePatchesSelected();` — Called when Fixture Patches were selected in Fixture Patch Shared Data
- L67 _private prototype_ `void OnEntitiesAdded(UDMXLibrary* Library, TArray<UDMXEntity*> Entities);` — Called when an Entity was added from the edited DMX Library
- L70 _private prototype_ `void OnEntitiesRemoved(UDMXLibrary* Library, TArray<UDMXEntity*> Entities);` — Called when an Entity was removed from the edited DMX Library
- L73 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a Fixture Type changed
- L76 _private prototype_ `FReply OnAddNewFixtureTypeClicked();` — Called when the Add button was clicked
- L79 _private prototype_ `void AddNewFixtureType();` — Adds a new Fixture Type to the Library
- L82 _private prototype_ `TSharedPtr<SDMXFixtureTypeTreeFixtureTypeRow> FindEntityRowByNode(const TSharedRef<FDMXEntityTreeEntityNode>& EntityNode);` — Returns the row that corresponds to the node
- L85 _private member_ `bool bChangingSelection = false;` — True while the widget is changing the selection
- L88 _private member_ `TMap<TSharedRef<FDMXEntityTreeEntityNode>, TSharedRef<SDMXFixtureTypeTreeFixtureTypeRow>> EntityNodeToEntityRowMap;` — Map of entity nodes and their row in the tree
- L91 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> FixtureTypeSharedData;` — Shared Data for Fixture Types

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeTreeCategoryRow.h` (Private)


#### class `SDMXFixtureTypeTreeCategoryRow`  
`class SDMXFixtureTypeTreeCategoryRow : public STableRow<TSharedPtr<FDMXEntityTreeCategoryNode>>`  
_L19-64_
- inherits: `STableRow<TSharedPtr<FDMXEntityTreeCategoryNode>>`
- desc: A row displaying a Category in a Fixture Type Tree
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeTreeCategoryRow)`
- L25 _public prototype_ `SLATE_DEFAULT_SLOT(typename SDMXFixtureTypeTreeCategoryRow::FArguments, Content) SLATE_EVENT(FSimpleDelegate, OnFixtureTypeOrderChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<FDMXEntityTreeCategoryNode> InCategoryNode, bool bInIsRootCategory, TWeakPtr<SDMXFixtureTypeTree> InFixtureTypeTree);`
- L36 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L37 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L42 _private prototype_ `bool TestCanDropWithFeedback(const TSharedRef<FDMXEntityDragDropOperation>& EntityDragDropOp) const;` — Returns true if the drag drop op can be dropped on this row
- L45 _private prototype_ `TArray<TSharedRef<FDMXEntityTreeCategoryNode>> GetCategoryNodesFromDragDropOp(const TSharedRef<FDMXEntityDragDropOperation>& DragDropOp) const;` — Returns the categories nodes the entities were dragged out from
- L48 _private prototype_ `const FSlateBrush* GetBackgroundImageBrush() const;` — Returns the background image brush
- L51 _private prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the DMXLibrary of this row
- L54 _private member_ `TWeakPtr<FDMXEntityTreeCategoryNode> WeakCategoryNode;` — Pointer to the node this row displays
- L57 _private member_ `TWeakPtr<SDMXFixtureTypeTree> WeakFixtureTypeTree;` — The owning Fixture Patch List
- L60 _private member_ `TSharedPtr<SBorder> ContentBorder;` — Border that holds the content
- L63 _private member_ `FSimpleDelegate OnFixtureTypeOrderChanged;` — Broadcast when the order of fixture types in the library changed

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixtureType/SDMXFixtureTypeTreeFixtureTypeRow.h` (Private)


#### class `SDMXFixtureTypeTreeFixtureTypeRow`  
`class SDMXFixtureTypeTreeFixtureTypeRow : public STableRow<TSharedPtr<FDMXEntityTreeEntityNode>>`  
_L20-103_
- inherits: `STableRow<TSharedPtr<FDMXEntityTreeEntityNode>>`
- desc: A fixture type row in a fixture patch tree
- L23 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnEntityDragged, TSharedPtr<FDMXEntityTreeNodeBase>, const FPointerEvent&);`
- L24 _private prototype_ `DECLARE_DELEGATE_RetVal(FText, FOnGetFilterText);`
- L25 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnAutoAssignChannelStateChanged, bool);`
- L28 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureTypeTreeFixtureTypeRow)`
- L30 _public prototype_ `SLATE_DEFAULT_SLOT(typename SDMXFixtureTypeTreeFixtureTypeRow::FArguments, Content) SLATE_EVENT(FOnEntityDragged, OnEntityDragged) SLATE_EVENT(FOnGetFilterText, OnGetFilterText) SLATE_EVENT(FOnAutoAssignChannelStateChanged, OnAutoAssignChannelStateChanged) SLATE_EVENT(FSimpleDelegate, OnFixtureTypeOrderChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FDMXEntityTreeEntityNode> InEntityNode, TSharedPtr<STableViewBase> InOwnerTableView, TWeakPtr<SDMXFixtureTypeTree> InFixtureTypeTree);`
- L46 _public prototype_ `void EnterRenameMode();` — Starts renaming the widget (enters editing mode on its Editable Text Block)
- L50 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L51 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L52 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L57 _private prototype_ `bool TestCanDropWithFeedback(const TSharedRef<FDMXEntityDragDropOperation>& EntityDragDropOp) const;` — Returns true if the drag drop op can be dropped on this row
- L60 _private prototype_ `FReply HandleOnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the row is being dragged
- L63 _private prototype_ `FText GetFilterText() const;` — Get the current filter text from the search box
- L66 _private prototype_ `bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage);` — Verifies the name of the component when changing it
- L69 _private prototype_ `void OnNameTextCommit(const FText& InNewName, ETextCommit::Type InTextCommit);` — Commits the new name of the component
- L72 _private prototype_ `FText GetFixtureTypeName() const;` — Returns the name of the patch as text
- L75 _private prototype_ `const FSlateBrush* GetStatusIcon() const;` — Get the icon for the Entity usability status. If it's all good, it's an emtpy image.
- L78 _private prototype_ `FText GetStatusToolTip() const;` — Get the tool tip text for the status icon
- L81 _private prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Returns the DMXLibrary of this row
- L84 _private member_ `TWeakPtr<FDMXEntityTreeEntityNode> WeakEntityNode;` — The node this row displays
- L87 _private member_ `TWeakPtr<SDMXFixtureTypeTree> WeakFixtureTypeTree;` — The fixture type tree widget that owns this row
- L90 _private member_ `FOnAutoAssignChannelStateChanged OnAutoAssignChannelStateChanged;` — Called when the entity list changed auto assign channel state
- L93 _private member_ `FOnEntityDragged OnEntityDragged;` — Delegate broadcast when an entity was dragged
- L96 _private member_ `FOnGetFilterText OnGetFilterText;` — Delegate broadcast when the filter text is requested
- L99 _private member_ `FSimpleDelegate OnFixtureTypeOrderChanged;` — Called when the entity list changed order of the library's entity array
- L102 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableFixtureTypeNameWidget;` — The editable text block to display and change the name of the fixture type

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnEntityDragged, TSharedPtr<FDMXEntityTreeNodeBase>, const FPointerEvent&);`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FOnGetFilterText);`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAutoAssignChannelStateChanged, bool);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/LibrarySettings/SDMXLibraryEditorTab.h` (Private)


#### class `SDMXLibraryEditorTab`  
`class SDMXLibraryEditorTab : public SCompoundWidget`  
_L17-37_
- inherits: `SCompoundWidget`
- desc: Editor for Fixture Patches
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXLibraryEditorTab)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget
- L36 _private member_ `TWeakPtr<FDMXEditor> DMXEditor;` — The DMXEditor that owns this tab

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/DMXConflictMonitorActiveObjectItem.h` (Private)


#### class `UE::DMX::FDMXConflictMonitorActiveObjectItem`  
`class FDMXConflictMonitorActiveObjectItem : public TSharedFromThis<FDMXConflictMonitorActiveObjectItem>`  
_L12-24_
- inherits: `TSharedFromThis<FDMXConflictMonitorActiveObjectItem>`
- desc: A row in the Conflict Monitor's Active Object list
- L17 _public prototype_ `FDMXConflictMonitorActiveObjectItem(const FName& ObjectName, const FSoftObjectPath& ObjectPath);` — Constructor. Object Path is allowed to be invalid
- L20 _public member_ `const FName ObjectName;` — The name of the object
- L23 _public member_ `const FSoftObjectPath ObjectPath;` — The object path. Can be invalid.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/DMXConflictMonitorConflictModel.h` (Private)


#### class `UE::DMX::FDMXConflictMonitorConflictModel`  
`class FDMXConflictMonitorConflictModel : public TSharedFromThis<FDMXConflictMonitorConflictModel>`  
_L12-47_
- inherits: `TSharedFromThis<FDMXConflictMonitorConflictModel>`
- desc: An item in the pixel mapping conflict list
- L18 _public prototype_ `FDMXConflictMonitorConflictModel(const TArray<TSharedRef<FDMXMonitoredOutboundDMXData>>& InConflicts);`
- L20 _public prototype_ `FString GetConflictAsString(bool bRichTextMarkup = false) const;`
- L24 _private prototype_ `void ParseConflict();` — Parses the conflict as string, stores it in Title and Details members
- L26 _private member_ `FString Title;`
- L27 _private member_ `TArray<FString> Details;`
- L30 _private prototype_ `FString GetPortNameString() const;` — Returns the name of the ports in which a conflict occurs
- L33 _private prototype_ `FString GetUniverseString() const;` — Returns the universe string
- L36 _private prototype_ `FString GetChannelsString() const;` — Returns the channels string
- L39 _private prototype_ `[[nodiscard]] FString StyleString(FString String, FString MarkupString) const;` — Applies the style to the string
- L42 _private prototype_ `FString GetStringNoMarkup(const FString& String) const;` — Returns the string without markup
- L44 _private prototype_ `FDMXConflictMonitorConflictModel() = default;`
- L46 _private member_ `const TArray<TSharedRef<FDMXMonitoredOutboundDMXData>> Conflicts;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/SDMXActivityInUniverse.h` (Private)


#### class `FDMXUniverseMonitorChannelItem`  
`class FDMXUniverseMonitorChannelItem : public TSharedFromThis<FDMXUniverseMonitorChannelItem>`  
_L14-35_
- inherits: `TSharedFromThis<FDMXUniverseMonitorChannelItem>`
- desc: An item that references a channel, potentially along with a UI element
- L18 _public function_ `FDMXUniverseMonitorChannelItem(int32 InChannelID) : ChannelID(InChannelID)`
- L22 _public function_ `int32 GetChannelID() const`
- L23 _public function_ `uint8 GetValue() const`
- L24 _public prototype_ `void SetValue(uint8 NewValue);`
- L26 _public prototype_ `TSharedRef<SDMXChannel> GetWidgetChecked() const;`
- L27 _public function_ `bool HasWidget() const`
- L28 _public prototype_ `void CreateWidget(uint8 InitialValue);`
- L31 _private member_ `int32 ChannelID = 0;`
- L32 _private member_ `uint8 Value = 0;`
- L34 _private member_ `TSharedPtr<SDMXChannel> Widget;`

#### class `SDMXActivityInUniverse`  
`class SDMXActivityInUniverse : public SCompoundWidget`  
_L39-116_
- inherits: `SCompoundWidget`
- desc: Visualization of the DMX activity in a single DMX Universe
- L43 _public function_ `SLATE_BEGIN_ARGS(SDMXActivityInUniverse) : _UniverseID(0)`
- L48 _public prototype_ `SLATE_ATTRIBUTE(uint32, UniverseID) SLATE_END_ARGS() virtual ~SDMXActivityInUniverse();` — The universe ID this widget represents
- L55 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget
- L58 _public prototype_ `void VisualizeBuffer(const TArray<uint8, TFixedAllocator<DMX_UNIVERSE_SIZE>>& Values);` — Visualizes specified buffer
- L61 _public function_ `uint32 GetUniverseID() const` — Gets the universe ID this widget represents
- L65 _protected prototype_ `void UpdateChannels();` — Updates Channels along with their UI representation
- L68 _protected prototype_ `TSharedRef<class ITableRow> GenerateChannelRow(TSharedPtr<class FDMXUniverseMonitorChannelItem> InChannelView, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a widget for the Channels List View
- L72 _private member_ `TAttribute<uint32> UniverseID;` — The universe ID this widget represents
- L75 _private member_ `TArray<uint8, TFixedAllocator<DMX_UNIVERSE_SIZE>> Buffer;` — The buffer currently displayed
- L78 _private member_ `TSharedPtr<SListView<TSharedPtr<class FDMXUniverseMonitorChannelItem>>> ChannelList;` — List view widget that displays current non-zero values for all universes
- L81 _private member_ `TArray<TSharedPtr<class FDMXUniverseMonitorChannelItem>> Channels;` — Array of all channels in the universe, as channel items
- L84 _private member_ `TArray<TSharedPtr<class FDMXUniverseMonitorChannelItem>> ChannelListSource;` — Cached source of channels for the channel list
- L91 _private prototype_ `EActiveTimerReturnType UpdateValueChangedAnim(double InCurrentTime, float InDeltaTime);` — Updates the variable that controls the color animation progress for the Value Bar. This is called by a timer.
- L94 _private prototype_ `FText GetIDLabel() const;` — Returns the universe ID in Text form to display it in the UI
- L97 _private prototype_ `FSlateColor GetBackgroundColor() const;` — Returns the fill color for the ValueBar
- L100 _private member_ `TWeakPtr<FActiveTimerHandle> AnimationTimerHandle;` — Used to stop the animation timer once the animation is completed
- L106 _private member_ `float NewValueFreshness = 0.0f;` — Used to animate the color when the value changes. 0..1 range: 1 = value has just changed, 0 = standard color
- L109 _private member_ `const float NewValueChangedAnimDuration = 0.8f;` — How long it takes to become standard color again after a new value is set
- L112 _private member_ `const FLinearColor IDColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.6f);` — Color of the ID label
- L115 _private member_ `const FLinearColor ValueColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.9f);` — Color of the Value label

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/SDMXActivityMonitor.h` (Private)


#### class `SDMXActivityMonitor`  
`class SDMXActivityMonitor : public SCompoundWidget`  
_L24-119_
- inherits: `SCompoundWidget`
- desc: A Monitor for DMX activity in a range of DMX Universes
- L28 _public prototype_ `SDMXActivityMonitor();`
- L30 _public prototype_ `virtual ~SDMXActivityMonitor();`
- L32 _public function_ `SLATE_BEGIN_ARGS(SDMXActivityMonitor)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _private prototype_ `void ClearAllDMXBuffers();` — Clears all DMX Buffers
- L45 _private prototype_ `void ResizeDataMapToUniverseRange();` — Resizes Latest Data to the Min and Max Universe Range
- L48 _private member_ `TMap<int32, TArray<uint8, TFixedAllocator<DMX_UNIVERSE_SIZE>>> UniverseToDataMap;` — Map of latest data
- L52 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _private prototype_ `void LoadMonitorSettings();` — Initialize values from DMX Editor Settings
- L60 _private prototype_ `void SaveMonitorSettings() const;` — Saves settings of the monitor in config
- L63 _private prototype_ `TSharedRef<SDMXActivityInUniverse> GetOrCreateActivityWidget(int32 UniverseID);` — Returns a view for specified universe ID, creates one if it doesn't exist yet
- L66 _private prototype_ `void OnMinUniverseIDValueCommitted(const FText& InNewText, ETextCommit::Type CommitType);` — Called when a Min Universe ID value was commited
- L69 _private prototype_ `void OnMaxUniverseIDValueCommitted(const FText& InNewText, ETextCommit::Type CommitType);` — Called when a Max Universe ID value was commited
- L72 _private prototype_ `void OnSourceSelected();` — Called when a Source was selected in the Monitor Source Selector
- L75 _private prototype_ `void OnPortsChanged();` — Called when ports changed
- L78 _private prototype_ `void OnPortBuffersCleared();` — Called when port buffers were cleared
- L81 _private prototype_ `FReply OnClearButtonClicked();` — Called when the clear ui values button was clicked
- L84 _private prototype_ `void ClearDisplay();` — Remove all displayed  values on the universes monitor
- L87 _private prototype_ `void UpdateListenerRegistration();` — Reregisters self as Listener to the ports active
- L90 _private member_ `int32 MinUniverseID;` — The min universe ID to recieve
- L93 _private member_ `int32 MaxUniverseID;` — The max universe ID to recieve
- L97 _private prototype_ `TSharedRef<ITableRow> OnGenerateUniverseRow(TSharedPtr<SDMXActivityInUniverse> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Called by SListView to generate custom list table row
- L100 _private member_ `TSet<TSharedRef<FDMXRawListener>> DMXListeners;` — The DMX inputs of the activity monitor
- L103 _private member_ `TSharedPtr<SListView<TSharedPtr<SDMXActivityInUniverse>>> UniverseList;` — ListView for universe counts
- L106 _private member_ `TArray<TSharedPtr<SDMXActivityInUniverse>> UniverseListSource;` — Universe Monitors being displayed
- L109 _private member_ `TSharedPtr<SDMXMonitorSourceSelector> SourceSelector;` — Selector for the source to monitor
- L112 _private member_ `TSharedPtr<SEditableTextBox> MinUniverseIDEditableTextBox;` — Text block to edit the Min Universe ID
- L115 _private member_ `TSharedPtr<SEditableTextBox> MaxUniverseIDEditableTextBox;` — Text block to edit the Max Universe ID
- L118 _private member_ `UE::DMX::FDMXEditorToolAnalyticsProvider AnalyticsProvider;` — The analytics provider for this tool

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/SDMXChannelsMonitor.h` (Private)


#### class `SDMXChannelsMonitor`  
`class SDMXChannelsMonitor : public SCompoundWidget`  
_L21-88_
- inherits: `SCompoundWidget`
- desc: DMX Widget to monitor all the channels in a DMX Universe
- L25 _public prototype_ `SDMXChannelsMonitor();`
- L27 _public function_ `SLATE_BEGIN_ARGS(SDMXChannelsMonitor)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L37 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L42 _private prototype_ `void CreateChannelValueWidgets();` — Creates the channel value widgets
- L45 _private prototype_ `void LoadMonitorSettings();` — Initialize values from DMX Editor Settings
- L48 _private prototype_ `void SaveMonitorSettings() const;` — Saves settings of the monitor in config
- L51 _private prototype_ `void ZeroChannelValues();` — Set the channel widgets to 0
- L54 _private prototype_ `void SetChannelValues(const TArray<uint8>& Buffer);` — Set the channel widgets to the values of the buffer
- L57 _private prototype_ `void OnSourceSelected();` — Called when a source was selected in the Source Selector
- L60 _private prototype_ `void OnUniverseIDValueCommitted(const FText& InNewText, ETextCommit::Type CommitType);` — Called when the universe ID was committed
- L63 _private prototype_ `FReply OnClearButtonClicked();` — Called when the clear bButton was clicked
- L66 _private prototype_ `void OnPortBuffersCleared();` — Called when port buffers were cleared
- L69 _private member_ `TSharedPtr<SHorizontalBox> SourceSelectorBox;` — Horizontal box that contains the Source Selector and its Label
- L72 _private member_ `TSharedPtr<SDMXMonitorSourceSelector> SourceSelector;` — Selector for the source to monitor
- L75 _private member_ `TSharedPtr<class SWrapBox> ChannelValuesBox;` — Container widget for all the channels' values
- L78 _private member_ `TArray<TSharedPtr<class SDMXChannel>, TFixedAllocator<DMX_UNIVERSE_SIZE>> ChannelValueWidgets;` — Widgets for individual channels, length should be same as number of channels in a universe
- L81 _private member_ `TSharedPtr<SEditableTextBox> UniverseIDEditableTextBox;` — Text block to edit the Universe ID
- L84 _private member_ `int32 UniverseID;` — Universe ID value computed using Net, Subnet and Universe values
- L87 _private member_ `UE::DMX::FDMXEditorToolAnalyticsProvider AnalyticsProvider;` — The analytics provider for this tool

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/SDMXConflictMonitor.h` (Private)


#### class `UE::DMX::SDMXConflictMonitor`  
`class SDMXConflictMonitor : public SCompoundWidget`  
_L26-130_
- inherits: `SCompoundWidget`
- desc: Monitors conflicts.
- L30 _public function_ `SLATE_BEGIN_ARGS(SDMXConflictMonitor)`
- L35 _public prototype_ `SDMXConflictMonitor();`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget
- L50 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L51 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _private prototype_ `TSharedRef<SHeaderRow> GenerateActiveObjectHeaderRow();` — Generates the header row of the active objects list
- L59 _private prototype_ `TSharedRef<ITableRow> OnGenerateActiveObjectRow(TSharedPtr<FDMXConflictMonitorActiveObjectItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row for an object that is actively sending DMX
- L62 _private prototype_ `void Refresh();` — Refreshes the widget
- L65 _private prototype_ `void SetupCommandList();` — Initializes the command list for this widget
- L68 _private prototype_ `void UpdateStatusInfo();` — Updates the status info for this monitor
- L71 _private prototype_ `bool IsScanning() const;` — Returns true if the monitor is scanning
- L73 _private prototype_ `void Play();`
- L74 _private prototype_ `void Pause();`
- L75 _private prototype_ `void Stop();`
- L77 _private prototype_ `void SetAutoPause(bool bEnabled);`
- L78 _private prototype_ `void ToggleAutoPause();`
- L79 _private prototype_ `bool IsAutoPause() const;`
- L81 _private prototype_ `void SetPrintToLog(bool bEnabled);`
- L82 _private prototype_ `void TogglePrintToLog();`
- L83 _private prototype_ `bool IsPrintingToLog() const;`
- L85 _private prototype_ `void SetRunWhenOpened(bool bEnabled);`
- L86 _private prototype_ `void ToggleRunWhenOpened();`
- L87 _private prototype_ `bool IsRunWhenOpened() const;`
- L90 _private member_ `TArray<TSharedRef<FDMXMonitoredOutboundDMXData>> CachedOutboundData;` — Cached outbound data
- L93 _private member_ `TMap<FName, TArray<TSharedRef<FDMXMonitoredOutboundDMXData>>> CachedOutboundConflicts;` — Cached outbound conflicts
- L96 _private member_ `TArray<TSharedPtr<FDMXConflictMonitorConflictModel>> Models;` — Items displayed in the list
- L99 _private member_ `TSharedPtr<SRichTextBlock> LogTextBlock;` — Text block displaying outbound conflicts, one conflict per row
- L102 _private member_ `double Timer = 0.0;` — Timer to refresh at refresh period
- L105 _private member_ `bool bIsPaused = false;` — True if paused
- L108 _private member_ `TArray<TSharedPtr<FDMXConflictMonitorActiveObjectItem>> ActiveObjectListSource;` — Source for the Active Object List
- L111 _private member_ `TSharedPtr<SListView<TSharedPtr<FDMXConflictMonitorActiveObjectItem>>> ActiveObjectList;` — The Active Object List
- L114 _private member_ `EDMXConflictMonitorStatusInfo StatusInfo;` — The status of the monitor. Note status info is ment for UI purposes, and not the state of the monitor.
- L117 _private member_ `TSharedPtr<FDMXConflictMonitorUserSession> UserSession;` — The conflict montitor user session used by this widget
- L120 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commandlist specific to this widget (only one can ever be displayed)
- L123 _private member_ `FDMXEditorToolAnalyticsProvider AnalyticsProvider;` — The analytics provider for this tool
- L126 _private member_ `double TimeGameThread = 0.0;` — Time on the game thread
- L129 _private member_ `TAttribute<double> UpdateInterval;` — Slate args

#### struct `UE::DMX::SDMXConflictMonitor::FActiveObjectCollumnID`  
`struct FActiveObjectCollumnID`  
_L41-46_
- L43 _public member_ `static const FName ObjectName;`
- L44 _public member_ `static const FName OpenAsset;`
- L45 _public member_ `static const FName ShowInContentBrowser;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/SDMXConflictMonitorActiveObjectRow.h` (Private)


#### class `UE::DMX::SDMXConflictMonitorActiveObjectRow`  
`class SDMXConflictMonitorActiveObjectRow : public SMultiColumnTableRow<TSharedPtr<FDMXConflictMonitorActiveObjectItem>>`  
_L15-41_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXConflictMonitorActiveObjectItem>>`
- desc: A row in the Conflict Monitor's Active Object list
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXConflictMonitorActiveObjectRow)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FDMXConflictMonitorActiveObjectItem>& InActiveObjectItem);`
- L29 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L34 _private prototype_ `void OnOpenAssetClicked();` — Called when the open asset hyperlink was clicked
- L37 _private prototype_ `FReply OnShowInContentBrowserClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the show in content browser button was clicked
- L40 _private member_ `TSharedPtr<FDMXConflictMonitorActiveObjectItem> ActiveObjectItem;` — The active object item

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/SDMXConflictMonitorToolbar.h` (Private)


#### enum `UE::DMX::EDMXConflictMonitorStatusInfo`  
`enum class EDMXConflictMonitorStatusInfo : uint8`  
_L14-20_
- desc: Possible statuses
- L16 _public enumerator_ `Idle`
- L17 _public enumerator_ `Paused`
- L18 _public enumerator_ `OK`
- L19 _public enumerator_ `Conflict`

#### class `UE::DMX::SDMXConflictMonitorToolbar`  
`class SDMXConflictMonitorToolbar : public SCompoundWidget`  
_L23-74_
- inherits: `SCompoundWidget`
- desc: Monitors conflicts.
- L27 _public function_ `SLATE_BEGIN_ARGS(SDMXConflictMonitorToolbar) : _StatusInfo(EDMXConflictMonitorStatusInfo::Idle) , _TimeGameThread(0.0)`
- L33 _public prototype_ `SLATE_ATTRIBUTE(EDMXConflictMonitorStatusInfo, StatusInfo) SLATE_ATTRIBUTE(double, TimeGameThread) SLATE_EVENT(FSimpleDelegate, OnDepthChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FUICommandList>& InCommandList);` — The status of the monitor
- L48 _private prototype_ `TSharedRef<SWidget> CreateToolbarMenu(const FArguments& InArgs);` — Creates the toolbar menu
- L51 _private prototype_ `FText GetStatusText() const;` — Returns the current status text
- L54 _private prototype_ `FSlateColor GetStatusTextColor() const;` — Returns the current status text color
- L57 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenu();` — Generates the settings menu
- L60 _private prototype_ `void SetDepth(uint8 InDepth);` — Sets a new depth
- L63 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list for this widget
- L66 _private member_ `uint8 Depth = 3;` — The current depth
- L69 _private member_ `double CachedTimeGameThread = 0.0;` — Cached time on game thread
- L72 _private member_ `TAttribute<EDMXConflictMonitorStatusInfo> StatusInfo;` — Slate args
- L73 _private member_ `FSimpleDelegate OnDepthChanged;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/Monitors/SDMXMonitorSourceSelector.h` (Private)


#### class `SDMXMonitorSourceSelector`  
`class SDMXMonitorSourceSelector : public SCompoundWidget`  
_L21-112_
- inherits: `SCompoundWidget`
- desc: Widget to select Ports to monitor. Note, when inputs are selected, loop back outputs are selected too.
- L25 _public function_ `SLATE_BEGIN_ARGS(SDMXMonitorSourceSelector) : _bMonitorAllPorts(true) , _bSelectInput(true) , _PortSelectorMode(EDMXPortSelectorMode::SelectFromAvailableInputsAndOutputs) , _InitiallySelectedGuid(FGuid())`
- L32 _public prototype_ `SLATE_ARGUMENT(bool, bMonitorAllPorts) SLATE_ARGUMENT(bool, bSelectInput) SLATE_ARGUMENT(EDMXPortSelectorMode, PortSelectorMode) SLATE_ARGUMENT(FGuid, InitiallySelectedGuid) SLATE_EVENT(FSimpleDelegate, OnSourceSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `bool IsMonitorAllPorts() const;` — Returns true if the Monitor All Ports CheckBox is checked
- L51 _public prototype_ `void SetMonitorAllPorts(bool bMonitorAllPorts);` — Sets the monitor all ports checkbox to checked or unchecked depending on the bMonitorAllPorts Argument
- L54 _public prototype_ `bool IsMonitorInputPorts() const;` — Returns true if Input is selected in the IODirection ComboBox
- L57 _public prototype_ `void SetMonitorInputPorts(bool bMonitorInputPorts);` — Set the IODirection to Input if bMonitorInputPorts argument is true, else sets it to Output
- L60 _public prototype_ `FGuid GetMonitoredPortGuid() const;` — Returns the Monitored Port Guid from the Port Selector, or an invalid Guid if the Port Selector holds no selection
- L63 _public prototype_ `void SetMonitoredPortGuid(const FGuid& PortGuid);` — Sets the Port Guid to select specified port, if the Guid is valid, else selects the first port if a port is available
- L65 _public function_ `const TArray<FDMXInputPortSharedRef>& GetSelectedInputPorts() const`
- L66 _public function_ `const TArray<FDMXOutputPortSharedRef>& GetSelectedOutputPorts() const`
- L70 _private prototype_ `void UpdateMonitoredPorts();` — Updates the monitored ports
- L73 _private prototype_ `TSharedRef<SWidget> GenerateIODirectionEntry(TSharedPtr<FText> SourceNameToAdd);` — Generates an entry in the monitor source combo box
- L76 _private prototype_ `void OnMonitorAllPortsCheckBoxChanged(const ECheckBoxState NewCheckState);` — Called when the Monitor All Ports Check Box state changed
- L79 _private prototype_ `void OnMonitoredIODirectionChanged(TSharedPtr<FText> SelectedIODirectionName, ESelectInfo::Type SelectInfo);` — Called when an IO Direction to be monitored was selected in related combo box
- L82 _private prototype_ `void OnPortSelected();` — Called when a port was selected in the Port Selector
- L85 _private member_ `TArray<FDMXInputPortSharedRef> SelectedInputPorts;` — The input ports that are currently being monitored
- L88 _private member_ `TArray<FDMXOutputPortSharedRef> SelectedOutputPorts;` — The output ports that are currently being monitored
- L91 _private member_ `TSharedPtr<SCheckBox> MonitorAllPortsCheckBox;` — CheckBox to toggle if all ports should be monitored
- L94 _private member_ `TSharedPtr<SHorizontalBox> PortSelectorWrapper;` — Horizontal box that contains the Port Selector and its Label
- L97 _private member_ `TSharedPtr<SDMXPortSelector> PortSelector;` — Selector for the port to monitor
- L100 _private member_ `TSharedPtr<SHorizontalBox> MonitoredIODirectionWrapper;` — Horizontal box that contains the Monitored IO Direction and its Label
- L103 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FText>>> MonitoredIODirectionComboBox;` — ComboBox to select where monitored DMX signals originate
- L106 _private member_ `TSharedPtr<STextBlock> MonitoredIODirectionTextBlock;` — Text block that is shown on top of the combo box
- L109 _private member_ `static const TArray<TSharedPtr<FText>> IODirectionNames;` — IODirection for the combo box to select where the signals monitored originate
- L111 _private member_ `FSimpleDelegate OnSourceSelected;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/PatchTool/DMXPatchToolItem.h` (Private)


#### class `UE::DMX::FDMXPatchToolItem`  
`class FDMXPatchToolItem : public TSharedFromThis<FDMXPatchToolItem>`  
_L12-21_
- inherits: `TSharedFromThis<FDMXPatchToolItem>`
- L16 _public function_ `FDMXPatchToolItem(TSoftObjectPtr<UDMXLibrary> InDMXLibrary) : SoftDMXLibrary(InDMXLibrary)`
- L20 _public member_ `const TSoftObjectPtr<UDMXLibrary> SoftDMXLibrary;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/PatchTool/SDMXPatchTool.h` (Private)


#### class `UE::DMX::SDMXPatchTool`  
`class SDMXPatchTool : public SCompoundWidget , public FGCObject`  
_L25-103_
- inherits: `SCompoundWidget,FGCObject`
- desc: A Monitor for DMX activity in a range of DMX Universes
- L30 _public function_ `SLATE_BEGIN_ARGS(SDMXPatchTool)`
- L35 _public prototype_ `SDMXPatchTool();`
- L36 _public prototype_ `virtual ~SDMXPatchTool();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget
- L43 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L44 _private prototype_ `virtual FString GetReferencerName() const override;`
- L48 _private prototype_ `void RequestRefresh();` — Refreshes the widget on the next tick
- L51 _private prototype_ `void Refresh();` — Refreshes the widget
- L54 _private prototype_ `FReply OnAddressIncrementalClicked();` — Called when the Address Incremental Button was clicked
- L57 _private prototype_ `FReply OnAddressSameClicked();` — Called when the Address Same Button was clicked
- L60 _private prototype_ `FReply OnAddressAndRenameClicked();` — Called when the Address And Rename Button was clicked
- L63 _private prototype_ `TSharedRef<SWidget> GenerateLibraryComboBoxEntry(TSharedPtr<FDMXPatchToolItem> LibraryToAdd);` — Generates an entry in the library combo box
- L66 _private prototype_ `void OnLibrarySelected(TSharedPtr<FDMXPatchToolItem> SelectedLibrary, ESelectInfo::Type SelectInfo);` — Called when a dmx library was slected
- L69 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FDMXPatchToolItem>>> LibraryComboBox;` — Combobox to select a library
- L72 _private prototype_ `TSharedRef<SWidget> GenerateFixturePatchComboBoxEntry(UDMXEntityFixturePatch* FixturePatchToAdd);` — Generates an entry in the library combo box
- L75 _private prototype_ `void OnFixturePatchSelected(UDMXEntityFixturePatch* SelectedFixturePatch, ESelectInfo::Type SelectInfo);` — Called when a fixture patch was slected
- L78 _private prototype_ `void OnAssetAddedOrRemoved(const FAssetData& AssetData);` — Called when an asset was added or removed
- L81 _private prototype_ `void OnEntitiesAddedOrRemoved(UDMXLibrary* Library, TArray<UDMXEntity*> Entities);` — Called when the library was edited
- L84 _private member_ `TArray<TSharedPtr<FDMXPatchToolItem>> LibrarySource;` — Source for the library combo box
- L87 _private member_ `TSharedPtr<SComboBox<UDMXEntityFixturePatch*>> FixturePatchComboBox;` — Combobox to select a patch within the library
- L90 _private member_ `TArray<TObjectPtr<UDMXEntityFixturePatch>> FixturePatchSource;` — Source for the fixture patch combo box
- L93 _private member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — The currently selected DMX Library. Useful to GC
- L96 _private member_ `TObjectPtr<UDMXEntityFixturePatch> FixturePatch;` — The currently selected fixture patch
- L99 _private member_ `FTimerHandle RefreshTimerHandle;` — Timer handle for the request refresh method
- L102 _private member_ `FDMXEditorToolAnalyticsProvider AnalyticsProvider;` — The analytics provider for this tool

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXChannel.h` (Private)


#### class `SDMXChannel`  
`class SDMXChannel : public SCompoundWidget`  
_L23-116_
- inherits: `SCompoundWidget`
- desc: Shows a channel in a box with the channel value top, the channel ID bottom | Value | | ----- | |  ID   |
- L27 _public function_ `SLATE_BEGIN_ARGS(SDMXChannel) : _ChannelID(0) , _Value(0) , _bShowChannelIDBottom(false) , _ChannelIDTextColor(FLinearColor::White.CopyWithNewOpacity(.6f)) , _ValueTextColor(FLinearColor::White.CopyWithNewOpacity(.9f))`
- L36 _public prototype_ `SLATE_ARGUMENT(uint32, ChannelID) SLATE_ARGUMENT(uint8, Value) SLATE_ARGUMENT(bool, bShowChannelIDBottom) SLATE_ATTRIBUTE(FSlateColor, ChannelIDTextColor) SLATE_ATTRIBUTE(FSlateColor, ValueTextColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The channel ID this widget represents
- L56 _public prototype_ `void SetChannelID(uint32 NewChannelID);` — Sets the channel ID this widget represents
- L59 _public function_ `uint32 GetChannelID() const` — Gets the channel ID this widget represents
- L65 _public prototype_ `void SetValue(uint8 NewValue);` — Sets the current value from the channel
- L68 _public function_ `uint8 GetValue() const` — Gets the current value from the channel
- L77 _public prototype_ `EActiveTimerReturnType UpdateValueChangedAnim(double InCurrentTime, float InDeltaTime);` — Updates the variable that controls the color animation progress for the Value Bar. This is called by a timer.
- L81 _private member_ `uint32 ChannelID;` — The channel ID this widget represents
- L84 _private member_ `uint8 Value;` — The current value from the channel
- L87 _private member_ `TSharedPtr<SImage> BarColorBorder;` — The ProgressBar widget to display the channel value graphically
- L93 _private member_ `float NewValueFreshness;` — Used to animate the color when the value changes. 0..1 range: 1 = value has just changed, 0 = standard color
- L96 _private member_ `static const float NewValueChangedAnimDuration;` — How long it takes to become standard color again after a new value is set
- L99 _private member_ `TWeakPtr<FActiveTimerHandle> AnimationTimerHandle;` — Used to stop the animation timer once the animation is completed
- L103 _private prototype_ `FText GetChannelIDText() const;` — Returns the channel ID in Text form to display it in the UI
- L106 _private prototype_ `FText GetValueText() const;` — Returns the channel value in Text form to display it in the UI
- L109 _private prototype_ `FSlateColor GetBackgroundColor() const;` — Returns the fill color for the ValueBar
- L112 _private member_ `TSharedPtr<STextBlock> ChannelIDTextBlock;` — Textblock that shows the Channel ID
- L115 _private member_ `TSharedPtr<STextBlock> ChannelValueTextBlock;` — Textblock that shows the Value

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXEntityEditor.h` (Private)


#### class `SDMXEntityEditor`  
`class SDMXEntityEditor : public SCompoundWidget`  
_L13-40_
- inherits: `SCompoundWidget`
- desc: Base class for widgets that edit a specific entity
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXEntityEditor)`
- L20 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L30 _public prototype_ `virtual void RequestRenameOnNewEntity(const UDMXEntity* InEntity, ESelectInfo::Type SelectionType) = 0;` — Refreshes the list of entities to display any added entities, select the new entity by name and initiates a rename on the selected Entity node
- L33 _public prototype_ `virtual void SelectEntity(UDMXEntity* InEntity, ESelectInfo::Type InSelectionType = ESelectInfo::Type::Direct) = 0;` — Selects an entity in this editor tab's list
- L36 _public prototype_ `virtual void SelectEntities(const TArray<UDMXEntity*>& InEntities, ESelectInfo::Type SelectionType = ESelectInfo::Type::Direct) = 0;` — Selects Entities in this editor tab's list
- L39 _public prototype_ `virtual TArray<UDMXEntity*> GetSelectedEntities() const = 0;` — Returns the selected entities on this editor tab

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXEntityTreeViewBase.h` (Private)


#### class `SDMXEntityTreeViewBase`  
`class SDMXEntityTreeViewBase : public SCompoundWidget , public FEditorUndoClient`  
_L26-281_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Base class for a tree view of entities, using DMXEntityTreeNode as its Nodes.
- L31 _public prototype_ `DECLARE_DELEGATE_OneParam(FDMXOnSelectionChanged, const TArray<UDMXEntity*>&);`
- L33 _public function_ `SLATE_BEGIN_ARGS(SDMXEntityTreeViewBase)`
- L36 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FDMXEditor>, DMXEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The DMX Editor that owns this widget
- L44 _public prototype_ `virtual ~SDMXEntityTreeViewBase();` — Destructor
- L48 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L52 _protected prototype_ `void UpdateTreeInternal(bool bRegenerateTreeNodes = true);` — Internally refreshes the the tree widget, actually carrying out the update
- L56 _public prototype_ `void UpdateTree(bool bRegenerateTreeNodes = true);` — Updates the Tree Widget
- L64 _public function_ `template <typename ValueType> TSharedRef<FDMXEntityTreeCategoryNode> GetOrCreateCategoryNode(const FDMXEntityTreeCategoryNode::ECategoryType InCategoryType, const FText InCategoryName, ValueType Value, TSharedPtr<FDMXEntityTreeNodeBase> InParentNode = nullptr, const FText& InToolTip = FText::GetEmpty())` — Creates a new category node directly under the passed parent or just retrieves it if existent. If InParentNodePtr is null, a root category node is created/retrieved. Stores a value, so when something is dropped on the category the value can be retrieved.
- L100 _public prototype_ `TArray<TSharedPtr<FDMXEntityTreeEntityNode>> GetEntityNodes(TSharedPtr<FDMXEntityTreeNodeBase> ParentNode = nullptr) const;` — Returns the Entity Nodes in the Tree
- L103 _public prototype_ `TSharedPtr<FDMXEntityTreeCategoryNode> FindCategoryNodeOfEntity(UDMXEntity* Entity) const;` — Returns the category node of the entity, or null if is not in the list
- L106 _public prototype_ `TSharedPtr<FDMXEntityTreeEntityNode> FindNodeByEntity(const UDMXEntity* Entity, TSharedPtr<FDMXEntityTreeNodeBase> StartNode = nullptr) const;` — Helper method to recursively find a tree node for the given DMX Entity starting at the given tree node
- L109 _public prototype_ `TSharedPtr<FDMXEntityTreeNodeBase> FindNodeByName(const FText& Name, TSharedPtr<FDMXEntityTreeNodeBase> StartNode = nullptr) const;` — Helper method to recursively find a tree node with the given name starting at the given tree node
- L112 _public prototype_ `void SelectItemByNode(const TSharedRef<FDMXEntityTreeNodeBase>& Node, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Selects an item
- L115 _public prototype_ `void SelectItemByEntity(const UDMXEntity* InEntity, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Selects an item by Entity
- L118 _public prototype_ `void SelectItemsByEntities(const TArray<UDMXEntity*>& InEntities, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Selects items by an Array of Entites
- L121 _public prototype_ `void SelectItemByName(const FString& ItemName, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Selects an item by name
- L124 _public prototype_ `TArray<UDMXEntity*> GetSelectedEntities() const;` — Get only the valid selected entities
- L127 _public prototype_ `bool IsNodeSelected(const TSharedPtr<FDMXEntityTreeNodeBase>& Node) const;` — Returns true if the node is selected
- L130 _public prototype_ `TArray<TSharedPtr<FDMXEntityTreeNodeBase>> GetSelectedNodes() const;` — Returns the selcted nodes
- L133 _public prototype_ `int32 GetNumExpandedNodes() const;` — Returns the number of expanded nodes
- L136 _public prototype_ `void SetNodeExpansion(TSharedPtr<FDMXEntityTreeNodeBase> Node, bool bExpandItem);` — Sets the node to be expaned or collapsed
- L139 _public prototype_ `void RequestScrollIntoView(TSharedPtr<FDMXEntityTreeNodeBase> Node);` — Requests to scroll the node into view
- L142 _public prototype_ `FText GetFilterText() const;` — Gets current filter from the FilterBox
- L145 _public prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Gets the DMX Library object being edited
- L148 _public function_ `const TSharedPtr<FDMXEntityTreeRootNode>& GetRootNode() const` — Returns the root node of the tree
- L151 _public prototype_ `virtual FReply OnEntitiesDragged(TSharedPtr<FDMXEntityTreeNodeBase> InNodePtr, const FPointerEvent& MouseEvent);` — Handler for when an entity from the list is dragged
- L155 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L159 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L160 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L164 _protected prototype_ `virtual TSharedRef<SWidget> GenerateAddNewEntityButton() = 0;` — Generates the Add New Entity Button that is displayed above the Tree View
- L167 _protected prototype_ `virtual void RebuildNodes(const TSharedPtr<FDMXEntityTreeRootNode>& RootNode) = 0;` — Rebuils of the root node
- L170 _protected prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXEntityTreeNodeBase> Node, const TSharedRef<STableViewBase>& OwnerTable) = 0;` — Generates a row in the tree view
- L173 _protected prototype_ `virtual void OnGetChildren(TSharedPtr<FDMXEntityTreeNodeBase> InNode, TArray<TSharedPtr<FDMXEntityTreeNodeBase>>& OutChildren);` — Gets the children of specified Node
- L176 _protected prototype_ `virtual void OnExpansionChanged(TSharedPtr<FDMXEntityTreeNodeBase> Node, bool bInExpansionState);` — Called when the expansion of a Node changed
- L179 _protected prototype_ `virtual TSharedPtr<SWidget> OnContextMenuOpen() = 0;` — Called to display a context menu when right clicking an Entity
- L182 _protected prototype_ `virtual void OnSelectionChanged(TSharedPtr<FDMXEntityTreeNodeBase> InSelectedNodePtr, ESelectInfo::Type SelectInfo) = 0;` — Called when Entities were selected in the Tree View
- L185 _protected prototype_ `virtual void OnCutSelectedNodes() = 0;` — Cut selected node(s)
- L186 _protected prototype_ `virtual bool CanCutNodes() const = 0;`
- L189 _protected prototype_ `virtual void OnCopySelectedNodes() = 0;` — Copy selected node(s)
- L190 _protected prototype_ `virtual bool CanCopyNodes() const = 0;`
- L193 _protected prototype_ `virtual void OnPasteNodes() = 0;` — Pastes previously copied node(s)
- L194 _protected prototype_ `virtual bool CanPasteNodes() const = 0;`
- L197 _protected prototype_ `virtual bool CanDuplicateNodes() const = 0;` — Callbacks to duplicate the selected component
- L198 _protected prototype_ `virtual void OnDuplicateNodes() = 0;`
- L201 _protected prototype_ `virtual void OnDeleteNodes() = 0;` — Removes existing selected component nodes from the SCS
- L202 _protected prototype_ `virtual bool CanDeleteNodes() const = 0;`
- L205 _protected prototype_ `virtual void OnRenameNode() = 0;` — Requests a rename on the selected Entity.
- L206 _protected prototype_ `virtual bool CanRenameNode() const = 0;`
- L213 _protected prototype_ `bool RefreshFilteredState(TSharedPtr<FDMXEntityTreeNodeBase> Node, bool bRecursive);` — Compares the filter bar's text with the item's component name. Use bRecursive to refresh the state of child nodes as well. Returns true if the node is set to be filtered out
- L216 _protected member_ `FDMXOnSelectionChanged OnSelectionChangedDelegate;` — Broadcast when the selection updated.
- L219 _protected member_ `FSimpleDelegate OnEntitiesAddedDelegate;` — Broadcast when the entity list added an entity to the library
- L222 _protected member_ `FSimpleDelegate OnEntityOrderChangedDelegate;` — Broadcast when the entity list changed order of the library's entity array
- L225 _protected member_ `FSimpleDelegate OnEntitiesRemovedDelegate;` — Broadcast when the entity list deleted an entity from the library
- L228 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for handling actions such as copy and paste
- L231 _protected member_ `TWeakPtr<FDMXEditor> DMXEditor;` — Pointer back to the DMXEditor tool that owns us
- L235 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Callback when the filter is changed, forces the action tree(s) to filter
- L238 _private prototype_ `void GetCollapsedNodes(TSet<TSharedPtr<FDMXEntityTreeNodeBase>>& OutCollapsedNodes, TSharedPtr<FDMXEntityTreeNodeBase> InParentNode = nullptr) const;` — Returns the set of expandable nodes that are currently collapsed in the UI
- L241 _private prototype_ `void OnActiveTabChanged(TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated);` — Called when the active tab in the editor changes
- L244 _private prototype_ `bool IsInTab(TSharedPtr<SDockTab> InDockTab) const;` — Searches this widget's parents to see if it's a child of InDockTab
- L251 _private member_ `TSharedPtr<FDMXEntityTreeRootNode> RootNode;` — The root node. It's not added to the tree, but the main categories and all their children (entity and sub-category nodes) belong to it to make recursive searching algorithms nicer.
- L254 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — The filter box that handles filtering entities
- L257 _private member_ `TMap<TSharedRef<FDMXEntityTreeNodeBase>, bool> PendingExpandItemMap;` — Map of items that should be expanded or collapsed next tick
- L260 _private member_ `bool bUpdatingSelection = false;` — Gate to prevent changing the selection while selection change is being broadcast.
- L271 _private member_ `EDMXRefreshTreeViewState RefreshTreeViewState = EDMXRefreshTreeViewState::NoRefreshRequested;` — True when a tree refresh was requested
- L274 _private member_ `TArray<TSharedPtr<FDMXEntityTreeNodeBase>> PendingSelection;` — Object to select on the next tick
- L277 _private member_ `FDelegateHandle OnActiveTabChangedDelegateHandle;` — Delegate handle bound to the FGlobalTabmanager::OnActiveTabChanged delegate
- L280 _private member_ `TSharedPtr<STreeView<TSharedPtr<FDMXEntityTreeNodeBase>>> EntitiesTreeWidget;` — The actual Tree widget

#### enum `SDMXEntityTreeViewBase::EDMXRefreshTreeViewState`  
`enum class EDMXRefreshTreeViewState : uint8`  
_L263-268_
- desc: Enum for states of refreshing required
- L265 _public enumerator_ `RegenerateNodes`
- L266 _public enumerator_ `UpdateNodes`
- L267 _public enumerator_ `NoRefreshRequested`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FDMXOnSelectionChanged, const TArray<UDMXEntity*>&);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXGDTFOptionWindow.h` (Private)


#### class `UE::DMX::SDMXGDTFOptionWindow`  
`class SDMXGDTFOptionWindow : public SCompoundWidget`  
_L19-63_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXGDTFOptionWindow) : _ImportUI(nullptr) , _WidgetWindow() , _FullPath() , _MaxWindowHeight(0.0f) , _MaxWindowWidth(0.0f)`
- L39 _public prototype_ `void Construct(const FArguments& InArgs);`
- L41 _public function_ `bool ShouldImport() const`
- L43 _public function_ `bool ShouldImportAll() const`
- L47 _private function_ `virtual bool SupportsKeyboardFocus() const override`
- L48 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L51 _private prototype_ `FReply OnImport();`
- L52 _private prototype_ `FReply OnImportAll();`
- L53 _private prototype_ `FReply OnCancel();`
- L54 _private prototype_ `FReply OnResetToDefaultClick() const;`
- L55 _private prototype_ `FText GetImportTypeDisplayText() const;`
- L57 _private member_ `TWeakObjectPtr<UDMXGDTFImportUI> ImportUI;`
- L58 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L59 _private member_ `TWeakPtr< SWindow > WidgetWindow;`
- L60 _private member_ `TSharedPtr< SButton > ImportButton;`
- L61 _private member_ `bool bShouldImport = false;`
- L62 _private member_ `bool bShouldImportAll = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXLibraryFromMVRImportOptions.h` (Private)


#### class `SDMXLibraryFromMVRImportOptions`  
`class SDMXLibraryFromMVRImportOptions : public SCompoundWidget`  
_L14-42_
- inherits: `SCompoundWidget`
- desc: Widget that displays the DMX Library from MVR Import Options
- L18 _public function_ `SLATE_BEGIN_ARGS(SDMXLibraryFromMVRImportOptions)`
- L20 _public prototype_ `SLATE_ARGUMENT(FVector2D, MaxWidgetSize) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SWindow>& ParentWindow, UDMXLibraryFromMVRImportOptions* DMXLibraryFromMVRImportOptions);`
- L29 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L30 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L35 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);` — Sets focus after the widget was constructed (next tick)
- L38 _private member_ `TSharedPtr<SPrimaryButton> ImportButton;` — The Import Button widget
- L41 _private member_ `TWeakObjectPtr<UDMXLibraryFromMVRImportOptions> WeakImportOptions;` — Import options being displayed

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXMVRExportOptions.h` (Private)


#### class `UE::DMX::SDMXMVRExportOptions`  
`class SDMXMVRExportOptions final : public SCompoundWidget`  
_L10-23_
- inherits: `SCompoundWidget`
- desc: The UI presented when exporting MVR files
- L14 _public function_ `SLATE_BEGIN_ARGS(SDMXMVRExportOptions)`
- L19 _public prototype_ `~SDMXMVRExportOptions();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SWindow>& ParentWindow);` — Constructs the widget

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXNamedTypeRow.h` (Private)


#### class `SDMXNamedTypeRow`  
`template <typename NamedType> class SDMXNamedTypeRow : public STableRow<TSharedPtr<NamedType>>`  
_L24-179_
- inherits: `STableRow<TSharedPtr<NamedType>>`
- desc: editable text box for unique strings
- L28 _public function_ `SLATE_BEGIN_ARGS(SDMXNamedTypeRow)`
- L31 _public function_ `SLATE_ARGUMENT(FText, NameEmptyError) SLATE_ARGUMENT(FText, NameDuplicateError) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedPtr<NamedType> InItem)`
- L79 _public function_ `TSharedPtr<NamedType> GetItem() const` — Returns the item
- L82 _public function_ `void EnterEditingMode()` — Enters editing
- L90 _protected function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`
- L100 _protected function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L108 _protected function_ `bool OnVerifyTextChanged(const FText& InNewText, FText& OutErrorMessage)` — Called when text changed
- L140 _protected function_ `void OnTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit)` — Called when text was comitted
- L166 _protected member_ `TSharedPtr<IDMXNamedType> Item;` — item shown in the row
- L169 _protected member_ `FText NameEmptyError;` — Error displayed when the text box is empty
- L172 _protected member_ `FText NameDuplicateError;` — Error displayed when the the  name entered already exists
- L175 _protected member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableTextBlock;` — Text box editing the Name
- L178 _protected member_ `TSharedPtr<SPopupErrorText> ErrorTextWidget;` — Error reporting widget, required as SInlineEditableTextBlock error can't be cleared on commit

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/SDMXSignalFormatSelector.h` (Private)


#### class `SDMXSignalFormatSelector`  
`class SDMXSignalFormatSelector : public SCompoundWidget`  
_L14-62_
- inherits: `SCompoundWidget`
- desc: Widget to select a Fixture Function Signal Format
- L17 _private prototype_ `DECLARE_DELEGATE_OneParam(FDMXOnSignalFormatSelected, EDMXFixtureSignalFormat);`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDMXSignalFormatSelector) : _InitialSelection()`
- L24 _public prototype_ `SLATE_ATTRIBUTE(bool, HasMultipleValues) SLATE_ARGUMENT(EDMXFixtureSignalFormat, InitialSelection) SLATE_EVENT(FDMXOnSignalFormatSelected, OnSignalFormatSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `EDMXFixtureSignalFormat GetSelectedSignalFormat() const;` — Returns the selected Signal Format
- L42 _private prototype_ `TSharedRef<SWidget> GenerateComboBoxWidget(TSharedPtr<FString> Item);` — Generates the widget displayed on the combo box
- L45 _private prototype_ `void OnSignalFormatSelected(TSharedPtr<FString> SelectedItem, ESelectInfo::Type SelectInfo);` — Called when a Signal Format was selected
- L48 _private member_ `static const TArray<TSharedPtr<FString>> AvailableSignalFormats;` — The available Signal Format (incl. 32bit)
- L51 _private member_ `TArray<TSharedPtr<FString>> SignalFormatsSource;` — The Signal Format available to this specific widget (with or without 32bit, depending on the slate arg)
- L54 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;` — The combo box that draws the options
- L57 _private member_ `TSharedPtr<STextBlock> SelectionTextBlock;` — The Text Block that draws the selection
- L60 _private member_ `TAttribute<bool> HasMultipleValues;` — Slate Arguments
- L61 _private member_ `FDMXOnSignalFormatSelected OnSignalFormatSelectedDelegate;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FDMXOnSignalFormatSelected, EDMXFixtureSignalFormat);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Commands/DMXEditorCommands.h` (Public)


#### class `FDMXEditorCommands`  
`class FDMXEditorCommands : public TCommands<FDMXEditorCommands>`  
_L9-44_
- inherits: `TCommands<FDMXEditorCommands>`
- L13 _public prototype_ `FDMXEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> GoToDocumentation;` — Documentation related
- L23 _public member_ `TSharedPtr<FUICommandInfo> ImportDMXLibrary;` — DMX Library related
- L24 _public member_ `TSharedPtr<FUICommandInfo> ExportDMXLibrary;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> AddNewEntityFixtureType;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> AddNewEntityFixturePatch;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> AddNewFixtureTypeMode;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> AddNewModeFunction;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> OpenChannelsMonitor;` — Level Editor Tool Bar related
- L34 _public member_ `TSharedPtr<FUICommandInfo> OpenActivityMonitor;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> OpenConflictMonitor;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> OpenPatchTool;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ToggleReceiveDMX;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ToggleSendDMX;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> Align;` — Auto assign
- L42 _public member_ `TSharedPtr<FUICommandInfo> Stack;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> AutoAssignSelectedUniverse;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXEditor.h` (Public)


#### class `FDMXEditor`  
`class FDMXEditor : public FWorkflowCentricApplication`  
_L31-156_
- inherits: `FWorkflowCentricApplication,FNotifyHook`
- desc: *** The DMX Library Editor, displayed when opening a DMX Library Asset ***
- L36 _public prototype_ `FDMXEditor();`
- L39 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L40 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L41 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L42 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L46 _public prototype_ `void OnAddNewEntity(TSubclassOf<UDMXEntity> InEntityClass);` — Adds a new Entity to this DMX Library
- L49 _public prototype_ `bool InvokeEditorTabFromEntityType(TSubclassOf<UDMXEntity> InEntityClass);` — Activate the editor tab suited to edit Entities of type InEntityClass
- L51 _public function_ `FReply OnAddNewEntity_OnClick(TSubclassOf<UDMXEntity> InEntityClass)`
- L54 _public function_ `bool CanAddNewEntity(TSubclassOf<UDMXEntity> InEntityClass) const` — `UE_DEPRECATED(5.0, "Deprecated, this always yields true.")`
- L56 _public prototype_ `bool NewEntity_IsVisibleForType(TSubclassOf<UDMXEntity> InEntityClass) const;`
- L59 _public prototype_ `void RenameNewlyAddedEntity(UDMXEntity* InEntity, TSubclassOf<UDMXEntity> InEntityClass);` — Utility function to handle all steps required to rename a newly added Entity
- L62 _public prototype_ `TSharedPtr<SDMXEntityEditor> GetEditorWidgetForEntityType(TSubclassOf<UDMXEntity> InEntityClass) const;` — Gets the content widget for the tab that edits Entities from InEntityClass
- L65 _public prototype_ `void SelectEntityInItsTypeTab(UDMXEntity* InEntity, ESelectInfo::Type InSelectionType = ESelectInfo::Type::Direct);` — Switch to the correct tab to select an Entity for editing
- L67 _public prototype_ `void SelectEntitiesInTypeTab(const TArray<UDMXEntity*>& InEntities, ESelectInfo::Type InSelectionType = ESelectInfo::Type::Direct);` — Switch to the correct tab for the first Entity's type and select the Entities
- L69 _public prototype_ `TArray<UDMXEntity*> GetSelectedEntitiesFromTypeTab(TSubclassOf<UDMXEntity> InEntityClass) const;` — Get the selected entities from the tab that stores the passed in type
- L72 _public function_ `TSharedRef<SDMXLibraryEditorTab> GetDMXLibraryEditorTab() const`
- L73 _public function_ `TSharedRef<SDMXFixturePatchEditor> GetFixturePatchEditor() const`
- L74 _public function_ `TSharedRef<SDMXFixtureTypeEditor> GetFixtureTypeEditor() const`
- L77 _public function_ `FOnGetBaseNameForNewEntity& GetOnGetBaseNameForNewEntity()` — `UE_DEPRECATED(5.0, "Deprecated since naming is now handled consistently when creating new entities via UDMXEntityFixtureType::CreateFixtureType or UDMXEntityFixturePatch::CreateFixturePatch.")`
- L80 _public function_ `FOnSetupNewEntity& GetOnSetupNewEntity()` — `UE_DEPRECATED(5.0, "Deprecated in favor of UDMXLibrary::OnEntitiesAddedOrRemoved")`
- L83 _public prototype_ `virtual void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDMXLibrary* DMXLibrary);` — Edits the specified DMX library
- L86 _public prototype_ `void CommonInitialization(UDMXLibrary* DMXLibrary);` — Should be called when initializing
- L89 _public prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Get the DMX library being edited
- L91 _public function_ `TSharedPtr<FDMXEditorToolbar> GetToolbarBuilder()`
- L93 _public prototype_ `void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);`
- L98 _protected prototype_ `virtual void CreateDefaultTabContents(UDMXLibrary* DMXLibrary);` — Creates the widgets that go into the tabs (note: does not create the tabs themselves)
- L101 _protected prototype_ `virtual void CreateDefaultCommands();` — Create Default Commands
- L104 _protected prototype_ `virtual void InitalizeExtenders();` — Called during initialization of the DMX editor to register commands and extenders.
- L107 _protected prototype_ `virtual void RegisterApplicationModes(UDMXLibrary* DMXLibrary, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false);` — Called during initialization of the DMX editor to register any application modes.
- L111 _private prototype_ `void ImportDMXLibrary() const;` — Imports the DMX Library from an MVR File
- L114 _private prototype_ `void ExportDMXLibrary() const;` — Exports the DMX Library as MVR File
- L117 _private prototype_ `TSharedRef<SDMXLibraryEditorTab> CreateDMXLibraryEditorTab();`
- L118 _private prototype_ `TSharedRef<SDMXFixtureTypeEditor> CreateFixtureTypeEditor();`
- L119 _private prototype_ `TSharedRef<SDMXFixturePatchEditor> CreateFixturePatchEditor();`
- L122 _private member_ `TSharedPtr<FDMXEditorToolbar> Toolbar;` — The toolbar builder class
- L125 _private member_ `static const FName ToolkitFName;` — The name given to all instances of this type of editor
- L128 _private member_ `TSharedPtr<SDMXLibraryEditorTab> DMXLibraryEditorTab;` — UI for the "DMX Library Editor" tab
- L131 _private member_ `TSharedPtr<SDMXFixtureTypeEditor> FixtureTypeEditor;` — UI for the "DMX Fixture Types" tab
- L134 _private member_ `TSharedPtr<SDMXFixturePatchEditor> FixturePatchEditor;` — UI for the "DMX Fixture Patch" tab
- L137 _private member_ `FOnGetBaseNameForNewEntity OnGetBaseNameForNewEntity;`
- L138 _private member_ `FOnSetupNewEntity OnSetupNewEntity;`
- L142 _public prototype_ `TSharedPtr<FDMXFixtureTypeSharedData> GetFixtureTypeSharedData() const;` — Gets the fixture type shared data instance
- L145 _public prototype_ `const TSharedPtr<FDMXFixturePatchSharedData>& GetFixturePatchSharedData() const;` — Gets the Fixture Patch shared Data Instance
- L149 _private member_ `TSharedPtr<FDMXFixtureTypeSharedData> FixtureTypeSharedData;` — Fixture type shared data instance
- L152 _private member_ `TSharedPtr<FDMXFixturePatchSharedData> FixturePatchSharedData;` — Shared Data for Fixture Patch editors
- L155 _private member_ `UE::DMX::FDMXEditorToolAnalyticsProvider AnalyticsProvider;` — The analytics provider for this tool

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetBaseNameForNewEntity, TSubclassOf<UDMXEntity>, FString&);` — Used to enable Entity creator code to inject a base name before the entity creation
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGetBaseNameForNewEntity, TSubclassOf<UDMXEntity>, FString&);` — Used to enable Entity creator code to inject a base name before the entity creation
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetupNewEntity, UDMXEntity*);` — Used to enable Entity creator code to set values in a newly created entity
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetupNewEntity, UDMXEntity*);` — Used to enable Entity creator code to set values in a newly created entity

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXEditorModule.h` (Public)


#### class `FDMXEditorModule`  
`class FDMXEditorModule : public IModuleInterface , public IHasMenuExtensibility , public IHasToolBarExtensibility`  
_L23-217_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Implements the DMX Editor Module.
- L30 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override`
- L39 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L43 _public prototype_ `static FDMXEditorModule& Get();` — Get the instance of this module.
- L56 _public prototype_ `TSharedRef<FDMXEditor> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDMXLibrary* DMXLibrary );` — Creates an instance of a DMX Library editor object. Note: This function should not be called directly. It should be called from AssetTools handler @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	DMXLibrary				The DMX object to start editing @return	Interface to the new DMX editor
- L59 _public prototype_ `void ExportDMXLibraryAsMVRFile(UDMXLibrary* DMXLibrary, const FString& DesiredName = TEXT("")) const;` — Exports a DMX Library as MVR file
- L62 _public function_ `TSharedPtr<FExtender> GetLevelEditorToolbarDMXMenuExtender() const` — Get Level Editor Toolbar Menu extender
- L64 _public function_ `static EAssetTypeCategories::Type GetAssetCategory()`
- L67 _public member_ `static const FName DMXEditorAppIdentifier;` — DataTable Editor app identifier string
- L70 _public member_ `static const FName ModuleName;` — The module DMX Editor Module name
- L73 _public member_ `static EAssetTypeCategories::Type DMXEditorAssetCategory;` — The DMX Editor asset category
- L76 _public member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L77 _public member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L81 _private prototype_ `static void FixGDTFAssetNames();` — Before 5.4, GDTF assets could be stored containing invalid characters such as @ common to most GDTFs. This function mends all asset names.
- L84 _private prototype_ `void BindDMXEditorCommands();` — Binds commands for the DMX editor
- L87 _private prototype_ `void ExtendLevelEditorToolbar();` — Creates the level editor toolbar extender
- L90 _private prototype_ `void CreateLevelEditorToolbarDMXMenuExtender();` — Creates the Extender for the Level Editor Toolbar DMX Menu
- L93 _private prototype_ `static TSharedRef<class SWidget> GenerateDMXLevelEditorToolbarMenu();` — Generates the level editor toolbar DMX Menu
- L97 _protected prototype_ `void RegisterAssetTypeCategories();` — Registers asset types categories
- L100 _protected prototype_ `void RegisterClassCustomizations();` — Registers global class customizations
- L103 _protected prototype_ `void RegisterPropertyTypeCustomizations();` — Registers global property type customizations
- L106 _protected prototype_ `void RegisterSequencerTypes();` — Registers sequencer related types
- L109 _protected prototype_ `void RegisterNomadTabSpawners();` — Registers nomad tab spawners
- L112 _protected prototype_ `void StartupPIEManager();` — Starts up the pie manager
- L116 _private prototype_ `static TSharedRef<class SDockTab> OnSpawnChannelsMonitorTab(const class FSpawnTabArgs& InSpawnTabArgs);` — Called when the nomad tab spawner tries to spawn a channels monitor tab
- L119 _private prototype_ `static TSharedRef<class SDockTab> OnSpawnActivityMonitorTab(const class FSpawnTabArgs& InSpawnTabArgs);` — Called when the nomad tab spawner tries to spawn an activity monitor tab
- L122 _private prototype_ `static TSharedRef<class SDockTab> OnSpawnConflictMonitorTab(const class FSpawnTabArgs& InSpawnTabArgs);` — Called when the nomad tab spawner tries to spawn an activity monitor tab
- L125 _private prototype_ `static TSharedRef<class SDockTab> OnSpawnPatchToolTab(const class FSpawnTabArgs& InSpawnTabArgs);` — Called when the nomad tab spawner tries to spawn a patch tool tab
- L128 _private prototype_ `static void OpenChannelsMonitor();` — Opens the channel monitor
- L131 _private prototype_ `static void OpenActivityMonitor();` — Opens the activity monitor
- L134 _private prototype_ `static void OpenConflictMonitor();` — Opens the conflict monitor
- L137 _private prototype_ `static void OpenPatchTool();` — Opens the patch tool
- L140 _private prototype_ `static void OnToggleSendDMX();` — Called when the Toggle Receive DMX menu command is selected
- L143 _private prototype_ `static bool IsSendDMXEnabled();` — Returns true if send dmx is enabled
- L146 _private prototype_ `static void OnToggleReceiveDMX();` — Called when the Toggle Receive DMX menu command is selected
- L149 _private prototype_ `static bool IsReceiveDMXEnabled();` — Returns true if receive dmx is enabled
- L152 _private member_ `TSharedPtr<class FUICommandList> DMXLevelEditorMenuCommands;` — Command list for the DMX level editor menu
- L161 _private prototype_ `void RegisterCustomClassLayout(FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate);` — Helper to register a custom class layout, to ease unregistering with the corresponding unregister method. @param ClassName					The class name to register for details customization @param DetailLayoutDelegate		The delegate to call to get the custom detail layout instance
- L164 _private prototype_ `void UnregisterCustomClassLayouts();` — Unregisteres all registered custom class layouts
- L172 _private prototype_ `void RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate);` — Helper to register a custom struct, to ease unregistering with the corresponding unregister method. @param StructName				The name of the struct to register for property customization @param StructLayoutDelegate		The delegate to call to get the custom detail layout instance
- L175 _private prototype_ `void UnregisterCustomPropertyTypeLayouts();` — Unregisteres all registered custom property type layouts
- L182 _private prototype_ `void RegisterCustomSequencerTrackType(const FOnCreateTrackEditor& CreateTrackEditorDelegate);` — Helper to register a custom sequencer track type, to ease unregistering with the corresponding unregister method. @param CreateTrackEditorDelegate		Delegate executed to create the custom track type
- L185 _private prototype_ `void UnregisterCustomSequencerTrackTypes();` — Unregisteres all custom sequencer track types
- L195 _private prototype_ `FTabSpawnerEntry& RegisterNomadTabSpawner(const FName TabId, const FOnSpawnTab& OnSpawnTab, const FCanSpawnTab& CanSpawnTab = FCanSpawnTab());` — Helper to register a new normad tab spawner with the tab manager, to ease unregistering with the corresponding unregister method. @param			TabId The TabId to register the spawner for. @param			OnSpawnTab The callback that will be used to spawn the tab. @param			CanSpawnTab The callback that will be used to ask if spawning the tab is allowed @return			The registration entry for the spawner.
- L198 _private prototype_ `void UnregisterNomadTabSpawners();` — Unregisteres all nomad tab spawners
- L201 _private member_ `static TSharedPtr<FExtender> LevelEditorToolbarDMXMenuExtender;` — Extender for the Level Editor Toolbar Menu
- L204 _private member_ `TSet<FName> RegisteredClassNames;` — List of registered class that must be unregistered when the module shuts down
- L207 _private member_ `TSet<FName> RegisteredPropertyTypes;` — List of registered property types that must be unregistered when the module shuts down
- L210 _private member_ `TSet<FDelegateHandle> RegisteredSequencerTrackHandles;` — All custom sequencer track handles
- L213 _private member_ `TSet<FName> RegisteredNomadTabNames;` — Names of all registered nomad tabs
- L216 _private member_ `TUniquePtr<FDMXPIEManager> PIEManager;` — Helper to track when the editor is in PIE

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXEditorSettings.h` (Public)


#### struct `FDMXMVRFixtureListSettings`  
`struct FDMXMVRFixtureListSettings`  
_L14-42_
- reflection: `USTRUCT()`
- desc: Settings for the Fixture Patch List
- L19 _public member_ `float ListWidth = .5f;` — `UPROPERTY()`
- L23 _public member_ `float FixtureIDColumnWidth = .1f;` — `UPROPERTY()` — Width of the Fixture ID column
- L27 _public member_ `float FixtureTypeColumnWidth = .2f;` — `UPROPERTY()` — With of the Fixture Type column
- L31 _public member_ `float ModeColumnWidth = .2f;` — `UPROPERTY()` — With of the Mode column
- L35 _public member_ `float PatchColumnWidth = .2f;` — `UPROPERTY()` — With of the Patch column
- L38 _public member_ `FName SortByCollumnID = NAME_None;` — `UPROPERTY()`
- L41 _public member_ `int32 SortPriorityEnumIndex = 1;` — `UPROPERTY()`

#### enum `EDMXFixturePatcherNameDisplayMode`  
`enum class EDMXFixturePatcherNameDisplayMode : uint8`  
_L45-50_
- reflection: `UENUM()`
- L47 _public enumerator_ `FixtureIDAndFixturePatchName`
- L48 _public enumerator_ `FixtureID`
- L49 _public enumerator_ `FixturePatchName`

#### struct `FDMXMVRFixturePatcherSettings`  
`struct FDMXMVRFixturePatcherSettings`  
_L54-63_
- reflection: `USTRUCT()`
- desc: Settings for the Fixture Patcher
- L59 _public member_ `bool bMonitorEnabled = false;` — `UPROPERTY()`
- L62 _public member_ `EDMXFixturePatcherNameDisplayMode FixturePatchNameDisplayMode = EDMXFixturePatcherNameDisplayMode::FixturePatchName;` — `UPROPERTY()`

#### struct `FDMXFixtureTypeFunctionsEditorSettings`  
`struct FDMXFixtureTypeFunctionsEditorSettings`  
_L68-79_
- reflection: `USTRUCT()`
- desc: Settings for the Fixture Type Functions Editor
- L74 _public member_ `float NameColumnWidth = 0.f;` — `UPROPERTY()` — Width of the function name column
- L78 _public member_ `float AttributeColumnWidth = 0.f;` — `UPROPERTY()` — With of the attribute column

#### struct `FDMXOutputConsoleFaderDescriptor`  
`struct FDMXOutputConsoleFaderDescriptor`  
_L84-120_
- reflection: `UE_DEPRECATED(5.2, "FDMXOutputConsoleFaderDescriptor is no longer supported. Please see FDMXControlConsoleEditorModule")`
- reflection: `USTRUCT()`
- desc: Struct to describe a single fader, so it can be stored in the config
- L88 _public function_ `FDMXOutputConsoleFaderDescriptor() : Value(0) , MaxValue(255) , MinValue(0) , UniversID(1) , StartingAddress(1) , EndingAddress(1)`
- L98 _public member_ `FString FaderName;` — `UPROPERTY()`
- L101 _public member_ `uint8 Value;` — `UPROPERTY()`
- L104 _public member_ `uint8 MaxValue;` — `UPROPERTY()`
- L107 _public member_ `uint8 MinValue;` — `UPROPERTY()`
- L110 _public member_ `int32 UniversID;` — `UPROPERTY()`
- L113 _public member_ `int32 StartingAddress;` — `UPROPERTY()`
- L116 _public member_ `int32 EndingAddress;` — `UPROPERTY()`
- L119 _public member_ `FName ProtocolName;` — `UPROPERTY()`

#### struct `FDMXMonitorSourceDescriptor`  
`struct FDMXMonitorSourceDescriptor`  
_L127-148_
- reflection: `USTRUCT()`
- desc: Struct to describe a monitor source, so it can be stored in settings Defaults to Monitor all Inputs.
- L131 _public function_ `FDMXMonitorSourceDescriptor() : bMonitorAllPorts(true) , bMonitorInputPorts(true) , MonitoredPortGuid(FGuid())`
- L139 _public member_ `bool bMonitorAllPorts;` — `UPROPERTY()` — True if all ports should be monitored
- L143 _public member_ `bool bMonitorInputPorts;` — `UPROPERTY()` — True if Input Ports should be monitored. Only relevant if bMonitorAllPorts
- L147 _public member_ `FGuid MonitoredPortGuid;` — `UPROPERTY()` — The monitored Port Guid. Only relevant if !bMonitorAllPorts

#### struct `FDMXConflictMonitorSettings`  
`struct FDMXConflictMonitorSettings`  
_L152-171_
- reflection: `USTRUCT()`
- desc: Settings for the conflict monitor
- L158 _public member_ `bool bAutoPause = false;` — `UPROPERTY()` — When enabled, the conflict monitor pauses when a conflict occurs
- L162 _public member_ `bool bPrintToLog = false;` — `UPROPERTY()` — When enabled, the the conflict monitor prints conflicts to log
- L166 _public member_ `bool bRunWhenOpened = false;` — `UPROPERTY()` — True if the conflict monitor starts when oppened
- L170 _public member_ `uint8 Depth = 3;` — `UPROPERTY()` — The displayed depth of traces

#### class `UDMXEditorSettings`  
`class UDMXEditorSettings : public UObject`  
_L175-252_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings that holds editor configurations. Not accessible in Project Settings. TODO: Idealy rename to UDMXEditorConfiguration
- L182 _public member_ `FString LastGDTFImportPath;` — `UPROPERTY(Config)`
- L187 _public member_ `FString LastMVRImportPath;` — `UPROPERTY(Config)`
- L190 _public member_ `FString LastMVRExportPath;` — `UPROPERTY(Config)`
- L196 _public member_ `bool bFixturePatcherDMXMonitorEnabled_DEPRECATED = false;` — `UPROPERTY(Config)` — Deprecated 5.3, moved to FDMXMVRFixturePatcherSettings
- L199 _public member_ `FDMXFixtureTypeFunctionsEditorSettings FixtureTypeFunctionsEditorSettings;` — `UPROPERTY(Config)`
- L202 _public member_ `FDMXMVRFixtureListSettings MVRFixtureListSettings;` — `UPROPERTY(Config)`
- L205 _public member_ `FDMXMVRFixturePatcherSettings FixturePatcherSettings;` — `UPROPERTY(Config)`
- L213 _public member_ `TArray<FDMXOutputConsoleFaderDescriptor> OutputConsoleFaders_DEPRECATED;` — `UPROPERTY(Config, Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated since Console is now saved in the new DMXControlConsolePreset, upgrade path is in DMXControlConsoleModule."))` — Stores the faders specified in Output Console
- L221 _public member_ `FString LastOpenedControlConsolePath;` — `UPROPERTY(Config)` — Path to the last control console opened in the editor
- L227 _public member_ `int32 ChannelsMonitorUniverseID = 1;` — `UPROPERTY(Config)` — The Universe ID to be monitored in the Channels Monitor
- L231 _public member_ `FDMXMonitorSourceDescriptor ChannelsMonitorSource;` — `UPROPERTY(Config)` — Source for the channels monitor
- L237 _public member_ `FDMXMonitorSourceDescriptor ActivityMonitorSource;` — `UPROPERTY(Config)` — Source for the DMX Activity Monitor
- L241 _public member_ `int32 ActivityMonitorMinUniverseID = 1;` — `UPROPERTY(Config)` — ID of the first universe to monitor in the DMX Activity Monitor
- L245 _public member_ `int32 ActivityMonitorMaxUniverseID = 100;` — `UPROPERTY(Config)` — ID of the last universe to monitor in the DMX Activity Monitor
- L251 _public member_ `FDMXConflictMonitorSettings ConflictMonitorSettings;` — `UPROPERTY(Config)` — Settings for the conflict monitor

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXEditorStyle.h` (Public)


#### class `FDMXEditorStyle`  
`class FDMXEditorStyle : public FSlateStyleSet`  
_L10-43_
- inherits: `FSlateStyleSet`
- desc: DMX editor style
- L15 _public prototype_ `FDMXEditorStyle();` — Constructor
- L18 _public prototype_ `virtual ~FDMXEditorStyle();` — Desonstructor
- L21 _public prototype_ `static const FDMXEditorStyle& Get();` — Returns the singleton ISlateStyle instance for DMX editor style
- L30 _public prototype_ `static void Initialize();` — `UE_DEPRECATED(5.0, "Deprecated since the public API leaves it unclear if the style is initialized or shut down. The style does not need to be Initialized explicitly anymore. Note, the StyleSetName now needs be accessed via FDMXEditorStyle::Get().GetStyleSetName().")` — DEPRECATED 5.0
- L34 _public prototype_ `static void Shutdown();` — `UE_DEPRECATED(5.0, "Deprecated since the public API leaves it unclear if the style is initialized or shut down. The style does not need to be shut down explicitly anymore. Note, the StyleSetName now needs be accessed via FDMXEditorStyle::Get().GetStyleSetName().")` — DEPRECATED 5.0
- L38 _public prototype_ `static void ReloadTextures();` — `UE_DEPRECATED(5.0, "Deprecated since no clear use (call FSlateApplication::Get().GetRenderer()->ReloadTextureResources() directly where needed).")` — DEPRECATED 5.0
- L42 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance_DEPRECATED;` — Singleton style instance

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXEditorUtils.h` (Public)


#### class `FDMXEditorUtils`  
`class FDMXEditorUtils`  
_L17-113_
- desc: Generic Editor Utilities. for Fixture Type, refer to DMXFixtureTypeSharedData instead.
- L28 _public prototype_ `static bool ValidateEntityName(const FString& NewEntityName, const UDMXLibrary* InLibrary, UClass* InEntityClass, FText& OutReason);` — Validates an Entity name, also checking for uniqueness among others of the same type. @param NewEntityName		The name to validate. @param InLibrary			The DMXLibrary object to check for name uniqueness. @param InEntityClass		The type to check other Entities' names @param OutReason			If false is returned, contains a text with the reason for it. @return True if the name would be a valid one.
- L31 _public prototype_ `static void RenameEntity(UDMXLibrary* InLibrary, UDMXEntity* InEntity, const FString& NewName);` — Renames an Entity
- L34 _public prototype_ `static bool IsEntityUsed(const UDMXLibrary* InLibrary, const UDMXEntity* InEntity);` — Checks if the Entity is being referenced by other objects.
- L37 _public prototype_ `static void CopyEntities(const TArray<UDMXEntity*>&& EntitiesToCopy);` — Copies Entities to the operating system's clipboard.
- L40 _public prototype_ `static bool CanPasteEntities(UDMXLibrary* ParentLibrary);` — Determines whether the current contents of the clipboard contain paste-able DMX Entity information
- L48 _public prototype_ `static TArray<UDMXEntity*> CreateEntitiesFromClipboard(UDMXLibrary* ParentLibrary);` — Creates the copied DMX Entities from the clipboard without attempting to paste/apply them in any way @param ParentLibrary			The library in which the entities are created. @return						The array of newly created enities.
- L55 _public prototype_ `static bool AreFixtureTypesIdentical(const UDMXEntityFixtureType* A, const UDMXEntityFixtureType* B);` — Compares the property values of two Fixture Types, including properties in arrays, and returns true if they are almost all the same. Name, ID and Parent Library are ignored.
- L58 _public prototype_ `static FText GetEntityTypeNameText(TSubclassOf<UDMXEntity> EntityClass, bool bPlural = false);` — Returns the Entity class type name (e.g: Fixture Type for UDMXEntityFixtureType) in singular or plural
- L65 _public prototype_ `static void UpdatePatchColors(UDMXLibrary* Library);` — Creates a unique color for all patches that use the default color FLinearColor(1.0f, 0.0f, 1.0f) @param Library				The library the patches resides in.
- L74 _public prototype_ `static void GetAllAssetsOfClass(UClass* Class, TArray<UObject*>& OutObjects);` — Retrieve all assets for a given class via the asset registry. Will load into memory if needed. @param Class					The class to lookup. @param OutObjects			All found objects.
- L83 _public prototype_ `static bool DoesLibraryHaveUniverseConflicts(UDMXLibrary* Library, FText& OutInputPortConflictMessage, FText& OutOutputPortConflictMessage);` — Locate universe conflicts between libraries @param Library					The library to be tested. @param OutConflictMessage		Message containing found conflicts @return							True if there is at least one conflict found.
- L87 _public prototype_ `static void ClearAllDMXPortBuffers();` — `UE_DEPRECATED(5.5, "Instead use FDMXPortManager::ClearPortBuffers")` — Zeros memory in all active DMX buffers of all protocols
- L91 _public prototype_ `static void ClearFixturePatchCachedData();` — `UE_DEPRECATED(5.5, "Instead use UDMXSubsystem::ClearDMXBuffers.")` — Clears cached data fixture patches received
- L94 _public prototype_ `static UPackage* GetOrCreatePackage(TWeakObjectPtr<UObject> Parent, const FString& DesiredName);` — Gets the package or creates a new one if it doesn't exist
- L97 _public prototype_ `[[nodiscard]] static TArray<FString> ParseAttributeNames(const FString& InputString);` — Parses Attribute Names from a String, format can be 'Dimmer', 'Dimmer, Pan, Tilt''. If no valid Attribute Names  can be parsed, returned Array is empty.
- L100 _public prototype_ `[[nodiscard]] static TArray<int32> ParseUniverses(const FString& InputString);` — Parses Universes from a String, format can be '1.', 'Uni 1', 'Universe 1', 'Uni 1, 3-4'. If no valid Universe can be parsed, returned Array is empty.
- L103 _public prototype_ `[[nodiscard]] static bool ParseAddress(const FString& InputString, int32& OutAddress);` — Parses an Address from a String, exected format is in the form of 'universe.address', e.g. '1.1'
- L106 _public prototype_ `[[nodiscard]] static TArray<int32> ParseFixtureIDs(const FString& InputString);` — Parses Fixture IDs from a String. Format can be '1', '1, 3-4'. If no valid Fixture ID can be parsed, returned Array is empty
- L109 _public prototype_ `[[nodiscard]] static bool ParseFixtureID(const FString& InputString, int32& OutFixtureID);` — Parses a Fixture ID from a String, exected format is an integral value, e.g. '1'
- L112 _public prototype_ `FDMXEditorUtils() = delete;` — can't instantiate this class

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXFixturePatchSharedData.h` (Public)


#### class `FDMXFixturePatchSharedData`  
`class FDMXFixturePatchSharedData : public FGCObject , public FSelfRegisteringEditorUndoClient , public TSharedFromThis<FDMXFixturePatchSharedData>`  
_L20-72_
- inherits: `FGCObject,FSelfRegisteringEditorUndoClient,TSharedFromThis<FDMXFixturePatchSharedData>`
- desc: Shared data for fixture patch editors
- L27 _public prototype_ `FDMXFixturePatchSharedData(TWeakPtr<FDMXEditor> InDMXEditorPtr);` — Constructor
- L30 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L31 _public function_ `virtual FString GetReferencerName() const override`
- L38 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L39 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L43 _public member_ `FSimpleMulticastDelegate OnUniverseSelectionChanged;` — Broadcast when a universe is selected by an editor
- L46 _public member_ `FSimpleMulticastDelegate OnFixturePatchSelectionChanged;` — Broadcast when a patch node is selected by an editor
- L49 _public prototype_ `void SelectUniverse(int32 UniverseID);` — Selects the universe
- L52 _public prototype_ `int32 GetSelectedUniverse();` — Returns the selected universe
- L55 _public prototype_ `void SelectFixturePatch(TWeakObjectPtr<UDMXEntityFixturePatch> Patch);` — Selects the patch node
- L58 _public prototype_ `void AddFixturePatchToSelection(TWeakObjectPtr<UDMXEntityFixturePatch> Patch);` — Selects the patch node, does not clear selection
- L61 _public prototype_ `void SelectFixturePatches(const TArray<TWeakObjectPtr<UDMXEntityFixturePatch>>& Patches);` — Selects the patch nodes
- L64 _public prototype_ `const TArray<TWeakObjectPtr<UDMXEntityFixturePatch>>& GetSelectedFixturePatches() const;` — Returns the selected patch node or nullptr if nothing is selected
- L68 _private member_ `TObjectPtr<UDMXFixturePatchSharedDataSelection> Selection;` — The current selection
- L71 _private member_ `TWeakPtr<FDMXEditor> DMXEditorPtr;` — Weak reference to the DMX editor

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXFixturePatchSharedDataSelection.h` (Public)


#### class `UDMXFixturePatchSharedDataSelection`  
`class UDMXFixturePatchSharedDataSelection : public UObject`  
_L13-26_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: An Array of Fixture Patches that supports a transaction history resp. undo / redo
- L21 _public member_ `TArray<TWeakObjectPtr<UDMXEntityFixturePatch>> SelectedFixturePatches;` — `UPROPERTY()` — Selected Fixture Patches
- L25 _public member_ `int32 SelectedUniverse = 1;` — `UPROPERTY()` — Selected Universe

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXFixtureTypeSharedData.h` (Public)


#### class `FDMXFixtureTypeSharedData`  
`class FDMXFixtureTypeSharedData : public FGCObject , public FSelfRegisteringEditorUndoClient , public TSharedFromThis<FDMXFixtureTypeSharedData>`  
_L25-149_
- inherits: `FGCObject,FSelfRegisteringEditorUndoClient,TSharedFromThis<FDMXFixtureTypeSharedData>`
- desc: Shared data for Fixture Types in a DMX Editor
- L32 _public prototype_ `FDMXFixtureTypeSharedData(TWeakPtr<FDMXEditor> InDMXEditorPtr);` — Constructor
- L35 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L36 _public function_ `virtual FString GetReferencerName() const override`
- L43 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L44 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L48 _public prototype_ `void SelectFixtureTypes(const TArray<TWeakObjectPtr<UDMXEntityFixtureType>>& InFixtureTypes);` — Selects specified Fixture Types
- L51 _public prototype_ `void SelectModes(const TArray<int32>& InModeIndices);` — Selects specified Modes
- L54 _public prototype_ `void SetFunctionAndMatrixSelection(const TArray<int32>& InFunctionIndices, bool bMatrixSelected);` — Selects specified Functions
- L58 _public prototype_ `void SelectFunctions(const TArray<int32>& InFunctionIndices);` — `UE_DEPRECATED(5.0, "Deprecated in favor of SetFunctionAndMatrixSelection to avoid the unclear state where both need change, but one contains the old state while the other changed.")` — Selects specified Functions
- L60 _public prototype_ `const TArray<TWeakObjectPtr<UDMXEntityFixtureType>>& GetSelectedFixtureTypes() const;`
- L61 _public prototype_ `const TArray<int32>& GetSelectedModeIndices() const;`
- L62 _public prototype_ `const TArray<int32>& GetSelectedFunctionIndices() const;`
- L63 _public prototype_ `bool IsFixtureMatrixSelected() const;`
- L66 _public prototype_ `bool CanCopyModesToClipboard() const;` — Returns true if selected Modes can be copied
- L69 _public prototype_ `void CopyModesToClipboard();` — Copies selected Modes. Only should be called when CanCopyModesToClipboard
- L72 _public prototype_ `bool CanPasteModesFromClipboard() const;` — Returns true if Modes can be pasted
- L75 _public prototype_ `void PasteModesFromClipboard(TArray<int32>& OutNewlyAddedModeIndices);` — Pastes the Modes clipboard to selected Modes, returns the newly added Mode indices. Only should be called when CanPasteModesFromClipboard
- L78 _public prototype_ `bool CanCopyFunctionsToClipboard() const;` — Returns true if selected Functions can be copied
- L81 _public prototype_ `void CopyFunctionsToClipboard();` — Copies selected Functions. Only should be called when CanCopyFunctionsToClipboard
- L84 _public prototype_ `bool CanPasteFunctionsFromClipboard() const;` — Returns true if Functions can be pasted
- L87 _public prototype_ `void PasteFunctionsFromClipboard(TArray<int32>& OutNewlyAddedFunctionIndices);` — Pastes the Modes clipboard to selected Functions, returns the newly added Function indices. Only should be called when CanPasteFunctionsFromClipboard
- L90 _public prototype_ `bool CanAddMode() const;` — `UE_DEPRECATED(5.0, "Removed for a cleaner API. Please make up logic in place where this was used (e.g. instead use GetSelectedModes().Num() == 1 from this class).")`
- L93 _public prototype_ `void AddMode();` — `UE_DEPRECATED(5.0, "Replaced with UDMXEntityFixtureType::AddMode.")`
- L96 _public prototype_ `void DuplicateModes(const TArray<int32>& ModeIndicesToDuplicate);` — `UE_DEPRECATED(5.0, "Replaced with UDMXEntityFixtureType::DuplicateModes.")`
- L99 _public prototype_ `void DeleteModes(const TArray<int32>& ModeIndicesToDelete);` — `UE_DEPRECATED(5.0, "Replaced with UDMXEntityFixtureType::DeleteModes.")`
- L102 _public prototype_ `void PasteClipboardToModes(const TArray<int32>& ModeIndices);` — `UE_DEPRECATED(5.0, "Replaced with FDMXFixtureTypeSharedData::PasteModesFromClipboard.")`
- L105 _public prototype_ `bool CanAddFunction() const;` — `UE_DEPRECATED(5.0, "Removed for a cleaner API. Please make up logic in place where this was used (e.g. instead use GetSelectedFunctions().Num() == 1 from this class).")`
- L108 _public prototype_ `void AddFunctionToSelectedMode();` — `UE_DEPRECATED(5.0, "Replaced with UDMXEntityFixtureType::AddFunction.")`
- L111 _public prototype_ `void DuplicateFunctions(const TArray<int32>& FunctionIndicesToDuplicate);` — `UE_DEPRECATED(5.0, "Replaced with UDMXEntityFixtureType::DuplicateFunctions.")`
- L114 _public prototype_ `void DeleteFunctions(const TArray<int32>& FunctionIndicesToDelete);` — `UE_DEPRECATED(5.0, "Replaced with UDMXEntityFixtureType::DeleteFunctions.")`
- L117 _public prototype_ `void PasteClipboardToFunctions(const TArray<int32>& FunctionIndices);` — `UE_DEPRECATED(5.0, "Replaced with FDMXFixtureTypeSharedData::PasteFunctionsFromClipboard.")`
- L120 _public prototype_ `bool CanAddCellAttribute() const;` — `UE_DEPRECATED(5.0, "Removed for a cleaner API. Please make up logic in place where this was used (e.g. instead use IsMatrixSelected() from this class).")`
- L123 _public prototype_ `void AddCellAttributeToSelectedMode();` — `UE_DEPRECATED(5.0, "Replaced with UDMXEntityFixtureType::AddCellAttribute.")`
- L126 _public member_ `FSimpleMulticastDelegate OnFixtureTypesSelected;` — Broadcasts when selected Fixture Types changed
- L129 _public member_ `FSimpleMulticastDelegate OnModesSelected;` — Broadcasts when selected Modes changed
- L132 _public member_ `FSimpleMulticastDelegate OnFunctionsSelected;` — Broadcasts when selected Functions changed
- L135 _public member_ `FSimpleMulticastDelegate OnMatrixSelectionChanged;` — Broadcasts when the Matrix was selected or unselected
- L139 _private member_ `TObjectPtr<UDMXFixtureTypeSharedDataSelection> Selection;` — The Fixture types being edited
- L142 _private member_ `TArray<FString> ModesClipboard;` — Cache for multi mode copy/paste
- L145 _private member_ `TArray<FString> FunctionsClipboard;` — Cache for multi function copy/paste
- L148 _private member_ `TWeakPtr<FDMXEditor> DMXEditorPtr;` — Weak reference to the DMX editor

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXFixtureTypeSharedDataSelection.h` (Public)


#### class `UDMXFixtureTypeSharedDataSelection`  
`class UDMXFixtureTypeSharedDataSelection : public UObject`  
_L13-34_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: An Array of Fixture Types that supports a transaction history resp. undo / redo
- L21 _public member_ `TArray<TWeakObjectPtr<UDMXEntityFixtureType>> SelectedFixtureTypes;` — `UPROPERTY()` — The Fixture types being edited
- L25 _public member_ `TArray<int32> SelectedModeIndices;` — `UPROPERTY()` — The Mode indices in the Selected Fixture Types currently being selected
- L29 _public member_ `TArray<int32> SelectedFunctionIndices;` — `UPROPERTY()` — The Function indices in the Selected Fixture Types currently being selected
- L33 _public member_ `bool bFixtureMatrixSelected = false;` — `UPROPERTY()` — If true the Fixture Matrices in the currently seleccted Modes are selected

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXPIEManager.h` (Public)


#### class `FDMXPIEManager`  
`class FDMXPIEManager`  
_L8-23_
- L12 _public prototype_ `FDMXPIEManager();` — Constructor
- L15 _public prototype_ `~FDMXPIEManager();` — Destructor
- L19 _private prototype_ `void OnBeginPIE(const bool bIsSimulating);` — Called when play in editor starts
- L22 _private prototype_ `void OnEndPIE(const bool bIsSimulating);` — Called when play in editor ends

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Factories/DMXEditorFactoryNew.h` (Public)


#### class `UDMXEditorFactoryNew`  
`class UDMXEditorFactoryNew : public UFactory`  
_L14-27_
- reflection: `UE_DEPRECATED(5.1, "Deprecated class. Please use DMXLibraryFactory instead.")`
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: DEPRECATED 5.1
- L18 _public prototype_ `UDMXEditorFactoryNew();`
- L21 _public function_ `virtual FText GetDisplayName() const override`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L26 _private prototype_ `UDMXLibrary* MakeNewEditor(UObject* InParent, FName Name, EObjectFlags Flags);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Factories/DMXLibraryFactory.h` (Public)


#### class `UDMXLibraryFactory`  
`class UDMXLibraryFactory : public UFactory`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L18 _public prototype_ `UDMXLibraryFactory();`
- L21 _public function_ `virtual FText GetDisplayName() const override`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Factories/DMXLibraryFromMVRFactory.h` (Public)


#### class `UDMXLibraryFromMVRFactory`  
`class UDMXLibraryFromMVRFactory : public UFactory , public FReimportHandler`  
_L14-43_
- reflection: `UCLASS()`
- inherits: `UFactory,FReimportHandler`
- L22 _public prototype_ `UDMXLibraryFromMVRFactory();` — Constructor
- L25 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* Parent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCancelled);`
- L26 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L30 _public member_ `static const FString MVRFileExtension;` — File extention for MVR files
- L34 _protected prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L35 _protected prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L36 _protected prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L37 _protected prototype_ `virtual int32 GetPriority() const override;`
- L42 _private prototype_ `UDMXMVRAssetImportData* GetMVRAssetImportData(UObject* DMXLibraryObject) const;` — Returns the MVR Asset Import Data for the Object, or nullptr if it cannot be obtained

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/IDMXNamedType.h` (Public)


#### class `IDMXNamedType`  
`class IDMXNamedType : public TSharedFromThis<IDMXNamedType>`  
_L10-25_
- inherits: `TSharedFromThis<IDMXNamedType>`
- desc: Interface for objects that want to define a unique name across a set of objects
- L15 _public function_ `virtual ~IDMXNamedType()`
- L18 _public prototype_ `virtual void GetName(FString& OutUniqueName) const = 0;` — Returns the name
- L21 _public prototype_ `virtual bool IsNameUnique(const FString& TestedName) const = 0;` — Returns if the name is unique
- L24 _public prototype_ `virtual void SetName(const FString& InDesiredName, FString& OutUniqueName) = 0;` — Sets the name, matching desired name as closely as possible

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Widgets/SAssetPickerButton.h` (Public)


#### class `SAssetPickerButton`  
`class SAssetPickerButton : public SCompoundWidget`  
_L17-113_
- inherits: `SCompoundWidget`
- desc: A widget which allows the user to pick a name of a specified list of names.
- L21 _public function_ `SLATE_BEGIN_ARGS(SAssetPickerButton) : _CurrentAssetValue(nullptr) , _AssetClass(UObject::StaticClass()) , _AllowedClasses() , _DisallowedClasses() , _OnParentIsHovered() , _OnAssetSelected()`
- L30 _public prototype_ `SLATE_ATTRIBUTE(TWeakObjectPtr<UObject>, CurrentAssetValue) SLATE_ARGUMENT(TWeakObjectPtr<UClass>, AssetClass) SLATE_ARGUMENT(TArray<FTopLevelAssetPath>, AllowedClasses) SLATE_ARGUMENT(TArray<FTopLevelAssetPath>, DisallowedClasses) SLATE_EVENT(FOnParentIsHovered, OnParentIsHovered) SLATE_EVENT(FOnAssetSelected, OnAssetSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The current asset value for the button label
- L57 _public member_ `TWeakObjectPtr<UClass> AssetClass;` — The class to filter the list of assets in the picker menu
- L59 _public member_ `TArray<FTopLevelAssetPath> AllowedClasses;` — Allows more than a single class. Overrides AssetClass
- L61 _public member_ `TArray<FTopLevelAssetPath> DisallowedClasses;` — Disallows subclasses from the allowed asset class(es)
- L65 _protected prototype_ `virtual FReply OnClickUse();` — Clicked Use button
- L67 _protected prototype_ `virtual FReply OnClickBrowse();` — Clicked Browse button
- L69 _protected prototype_ `FText GetObjectToolTip() const;` — Get text tooltip for object
- L71 _protected prototype_ `virtual FText GetDefaultComboText() const;` — Get default text for the picker combo
- L73 _protected function_ `virtual bool AllowSelfPinWidget() const` — Allow self pin widget
- L75 _protected prototype_ `virtual TSharedRef<SWidget> GenerateAssetPicker();` — Generate asset picker window
- L77 _protected prototype_ `virtual void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);` — Called to validate selection from picker window
- L79 _protected prototype_ `void OnAssetEnterPressedInPicker(const TArray<FAssetData>& InSelectedAssets);` — Called when enter is pressed when items are selected in the picker window
- L82 _protected prototype_ `FText OnGetComboTextValue() const;` — Used to update the combo button text
- L84 _protected prototype_ `bool GetIsParentHovered() const;` — Returns whether the parent widget is hovered to use it's area for hovered state
- L86 _protected prototype_ `FSlateColor OnGetComboForeground() const;` — Combo Button Color and Opacity delegate
- L88 _protected prototype_ `FSlateColor OnGetWidgetForeground() const;` — Button Color and Opacity delegate
- L90 _protected prototype_ `FSlateColor OnGetWidgetBackground() const;` — Button Color and Opacity delegate
- L93 _protected prototype_ `virtual const FAssetData& GetAssetData() const;` — Returns asset data of currently selected object, if bRuntimePath is true this will include _C for blueprint classes, for false it will point to UBlueprint instead
- L97 _protected member_ `TSharedPtr<SButton> UseButton;` — Object manipulator buttons.
- L98 _protected member_ `TSharedPtr<SButton> BrowseButton;`
- L101 _protected member_ `TSharedPtr<class SMenuAnchor> AssetPickerAnchor;` — Menu anchor for opening and closing the asset picker
- L104 _protected member_ `mutable FAssetData CachedAssetData;` — Cached AssetData of object selected
- L107 _protected member_ `TAttribute<TWeakObjectPtr<UObject>> CurrentAssetValue;` — The current asset selected, to display its name
- L110 _protected member_ `FOnParentIsHovered OnParentIsHovered;` — Broadcast when defining hovered state, to use the parent interact able area
- L112 _protected member_ `FOnAssetSelected OnAssetSelected;` — Broadcast when a new asset is selected

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetSelected, const FAssetData&);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetSelected, const FAssetData&);`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnParentIsHovered);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnParentIsHovered);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Widgets/SDMXEntityDropdownMenu.h` (Public)


#### enum `EEntityEntryType`  
`enum class EEntityEntryType : uint8`  
_L30-40_
- L33 _public enumerator_ `NewEntity` — Create a new Entity in the DMX library
- L35 _public enumerator_ `ExistingEntity` — Select existing Entity from the DMX library
- L37 _public enumerator_ `Heading` — Heading entry
- L39 _public enumerator_ `Separator` — Separator bar entry

#### class `FDMXEntityEntry`  
`class FDMXEntityEntry : public TSharedFromThis<FDMXEntityEntry>`  
_L42-93_
- inherits: `TSharedFromThis<FDMXEntityEntry>`
- L47 _public function_ `FDMXEntityEntry(const FText& InLabelText, EEntityEntryType InEntryType = EEntityEntryType::Heading) : Entity(nullptr) , LabelText(InLabelText) , EntryType(InEntryType)` — Constructor for the entry that creates a new Entity or a heading
- L54 _public function_ `FDMXEntityEntry(UDMXEntity* InEntity) : Entity(InEntity) , LabelText(FText::GetEmpty()) , EntryType(EEntityEntryType::ExistingEntity)` — Constructor for existing Entity entry
- L61 _public function_ `FDMXEntityEntry() : Entity(nullptr) , LabelText(FText::GetEmpty()) , EntryType(EEntityEntryType::Separator)` — Constructor for separator entry
- L68 _public function_ `UDMXEntity* GetEntity() const`
- L70 _public function_ `FText GetLabelText() const`
- L79 _public function_ `bool IsHeading() const`
- L81 _public function_ `bool IsSeparator() const`
- L83 _public function_ `bool IsEntity() const`
- L85 _public function_ `bool IsCreateNew() const`
- L87 _public function_ `EEntityEntryType GetEntryType() const`
- L90 _private member_ `UDMXEntity* Entity;`
- L91 _private member_ `FText LabelText;`
- L92 _private member_ `EEntityEntryType EntryType;`

#### class `SDMXEntityDropdownMenu`  
`template<typename TEntityType> class SDMXEntityDropdownMenu : public SListViewSelectorDropdownMenu< TSharedPtr< FDMXEntityEntry > >`  
_L105-551_
- inherits: `SListViewSelectorDropdownMenu<TSharedPtr<FDMXEntityEntry>>`
- desc: Generates a dropdown menu list of Entities from a specific type to be used as a dropdown for a SComboButton's MenuContent.
- L108 _private typedef_ `using SDMXDropdownMenuType = SDMXEntityDropdownMenu<TEntityType>;`
- L111 _public function_ `SLATE_BEGIN_ARGS(SDMXEntityDropdownMenu) : _DMXEditor(nullptr) , _DMXLibrary(nullptr) , _EntityTypeFilter(nullptr) , _OnCreateNewEntitySelected() , _OnEntitySelected()`
- L120 _public function_ `SLATE_ATTRIBUTE(TWeakPtr<FDMXEditor>, DMXEditor) SLATE_ATTRIBUTE(TWeakObjectPtr<UDMXLibrary>, DMXLibrary) SLATE_ATTRIBUTE(TSubclassOf<UDMXEntity>, EntityTypeFilter) SLATE_EVENT(FOnCreateNewEntitySelected, OnCreateNewEntitySelected) SLATE_EVENT(FOnEntitySelected, OnEntitySelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs)` — If valid, enables the option to create a new entity.
- L198 _public function_ `void RefreshEntitiesList()` — Updates the entities list
- L263 _public function_ `void SetComboButton(TSharedPtr<SComboButton> InComboButton)` — Sets the button that opens this dropdown menu. This automates closing the menu when an entry is selected and focusing on the Search Box.
- L273 _public function_ `void ClearSelection()`
- L288 _private function_ `TSubclassOf<UDMXEntity> GetEntityFilterClass() const`
- L299 _private function_ `void UpdateFilteredEntitiesList(const FString& InSearchText )`
- L335 _private function_ `void OnEntrySelectionChanged(TSharedPtr<FDMXEntityEntry> InItem, ESelectInfo::Type SelectInfo)`
- L418 _private function_ `TSharedRef<ITableRow> GenerateEntryRow(TSharedPtr<FDMXEntityEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable) const`
- L485 _private function_ `void OnSearchBoxTextChanged(const FText& InSearchText)`
- L491 _private function_ `void OnSearchBoxTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo)`
- L503 _private function_ `FText GetCurrentSearchString() const`
- L508 _private function_ `TSharedRef<SToolTip> GetToolTipForEntry(TSharedPtr<FDMXEntityEntry> Entry) const`
- L532 _private member_ `TArray<TSharedPtr<FDMXEntityEntry>> EntityEntries;` — All entries that should be displayed in the menu, including headers and separators
- L533 _private member_ `TArray<TSharedPtr<FDMXEntityEntry>> FilteredEntityEntries;`
- L536 _private member_ `TSharedPtr<SListView<TSharedPtr<FDMXEntityEntry>>> EntitiesListView;` — The list widget, with the entries the user will see in the UI
- L537 _private member_ `int32 PrevSelectedIndex;`
- L539 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search box to filter the available Entities
- L541 _private member_ `FOnCreateNewEntitySelected OnCreateNewEntityDelegate;`
- L542 _private member_ `FOnEntitySelected OnEntitySelectedDelegate;`
- L544 _private member_ `TAttribute<TWeakObjectPtr<UDMXLibrary>> DMXLibrary;`
- L545 _private member_ `TAttribute<TSubclassOf<UDMXEntity>> EntityTypeFilter;`
- L546 _private member_ `TAttribute<TWeakPtr<FDMXEditor>> DMXEditor;`
- L547 _private member_ `uint32 CurrentExistingEntitiesNum;`
- L549 _private member_ `TWeakPtr<SComboButton> ComboButtonPtr;`
- L550 _private member_ `FText EntityTypeName;`

#### class `SDMXEntityPickerButton`  
`template<typename TEntityType> class SDMXEntityPickerButton : public SCompoundWidget`  
_L560-785_
- inherits: `SCompoundWidget`
- desc: Generates a dropdown menu list of Entities from a specific type to be used as a dropdown for a SComboButton's MenuContent.
- L563 _private typedef_ `using SDMXEntityPickerType = SDMXEntityPickerButton<TEntityType>;`
- L566 _public function_ `SLATE_BEGIN_ARGS(SDMXEntityPickerButton) : _CurrentEntity(nullptr) , _HasMultipleValues(false) , _DMXEditor(nullptr) , _DMXLibrary(nullptr) , _EntityTypeFilter(nullptr) , _ForegroundColor(FLinearColor::White) , _OnCreateNewEntitySelected() , _OnEntitySelected()`
- L578 _public function_ `SLATE_ATTRIBUTE(TWeakObjectPtr<TEntityType>, CurrentEntity) SLATE_ATTRIBUTE(bool, HasMultipleValues) SLATE_ATTRIBUTE(TWeakPtr<FDMXEditor>, DMXEditor) SLATE_ATTRIBUTE(TWeakObjectPtr<UDMXLibrary>, DMXLibrary) SLATE_ATTRIBUTE(TSubclassOf<UDMXEntity>, EntityTypeFilter) SLATE_ATTRIBUTE(FLinearColor, ForegroundColor) SLATE_EVENT(FOnCreateNewEntitySelected, OnCreateNewEntitySelected) SLATE_EVENT(FOnEntitySelected, OnEntitySelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs)` — The current selected Entity. Only used if EntityPropertyHandle is null
- L704 _protected function_ `TSubclassOf<UDMXEntity> GetEntityFilterClass() const`
- L715 _protected function_ `EVisibility GetEditorButtonsVisibility() const`
- L720 _protected function_ `void OnBrowseEntityClicked() const`
- L731 _protected function_ `void OnUseSelectedEntityClicked()`
- L745 _protected function_ `void OnEntitySelected(UDMXEntity* InEntity)`
- L754 _protected function_ `FText OnGetSelectedEntityName() const`
- L771 _protected function_ `bool GetCanBrowseEntity() const`
- L777 _private member_ `FOnCreateNewEntitySelected OnCreateNewEntityDelegate;`
- L778 _private member_ `FOnEntitySelected OnEntitySelectedDelegate;`
- L780 _private member_ `TAttribute<TWeakPtr<FDMXEditor>> DMXEditor;`
- L781 _private member_ `TAttribute<TWeakObjectPtr<UDMXLibrary>> DMXLibrary;`
- L782 _private member_ `TAttribute<TSubclassOf<UDMXEntity>> EntityTypeFilter;`
- L783 _private member_ `TAttribute<TWeakObjectPtr<TEntityType>> CurrentEntity;`
- L784 _private member_ `TAttribute<bool> HasMultipleValues;`

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "SDMXEntitySelectorDropdownMenu"`
- L97 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEntitySelected, UDMXEntity*);`
- L97 _prototype_ `DECLARE_DELEGATE_OneParam(FOnEntitySelected, UDMXEntity*);`
- L98 _delegate_ `DECLARE_DELEGATE(FOnCreateNewEntitySelected);`
- L98 _prototype_ `DECLARE_DELEGATE(FOnCreateNewEntitySelected);`
- L249 _function_ `` (scope `SDMXEntityDropdownMenu::RefreshEntitiesList`)
- L654 _function_ `` (scope `SDMXEntityPickerButton::SLATE_ATTRIBUTE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Widgets/SDMXReadOnlyFixturePatchList.h` (Public)


#### enum `EDMXReadOnlyFixturePatchListShowMode`  
`enum class EDMXReadOnlyFixturePatchListShowMode : uint8`  
_L26-36_
- L29 _public enumerator_ `All` — Show All Fixture Patches in the list
- L32 _public enumerator_ `Active` — Show Only Active Fixture Patches in the list
- L35 _public enumerator_ `Inactive` — Show Only Inactive Fixture Patches in the list

#### struct `FDMXReadOnlyFixturePatchListCollumnIDs`  
`struct FDMXReadOnlyFixturePatchListCollumnIDs`  
_L39-47_
- desc: Collumn IDs in the Fixture Patch List
- L41 _public member_ `static const FName EditorColor;`
- L42 _public member_ `static const FName FixturePatchName;`
- L43 _public member_ `static const FName FixtureID;`
- L44 _public member_ `static const FName FixtureType;`
- L45 _public member_ `static const FName Mode;`
- L46 _public member_ `static const FName Patch;`

#### struct `FDMXReadOnlyFixturePatchListDescriptor`  
`struct FDMXReadOnlyFixturePatchListDescriptor`  
_L51-74_
- reflection: `USTRUCT()`
- desc: Struct to describe a fixture patch list, so it can be stored in settings
- L55 _public function_ `FDMXReadOnlyFixturePatchListDescriptor() : SortedByColumnID(FDMXReadOnlyFixturePatchListCollumnIDs::Patch) , ColumnIDToShowStateMap(TMap<FName, bool>())`
- L69 _public member_ `FName SortedByColumnID;` — `UPROPERTY()` — By which column ID the List is sorted
- L73 _public member_ `TMap<FName, bool> ColumnIDToShowStateMap;` — `UPROPERTY()` — Map for storing the show state of each column by name ID

#### class `SDMXReadOnlyFixturePatchList`  
`class SDMXReadOnlyFixturePatchList : public SCompoundWidget , public FGCObject`  
_L77-245_
- inherits: `SCompoundWidget,FGCObject`
- desc: Generic list of Fixture Patches in a DMX library for read only purposes
- L82 _public function_ `DECLARE_DELEGATE_OneParam(FDMXFixturePatchListRowDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>) DECLARE_DELEGATE_RetVal_OneParam(bool, FDMXFixturePatchListRowRetValDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>) DECLARE_DELEGATE_TwoParams(FDMXFixturePatchListRowSelectionDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>, ESelectInfo::Type) SLATE_BEGIN_ARGS(SDMXReadOnlyFixturePatchList) : _ListDescriptor(FDMXReadOnlyFixturePatchListDescriptor()) , _DMXLibrary(nullptr)`
- L91 _public prototype_ `SLATE_ARGUMENT(FDMXReadOnlyFixturePatchListDescriptor, ListDescriptor) SLATE_ARGUMENT(UDMXLibrary*, DMXLibrary) SLATE_ARGUMENT(TArray<UDMXEntityFixturePatch*>, ExcludedFixturePatches) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FDMXFixturePatchListRowSelectionDelegate, OnRowSelectionChanged) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowClicked) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowDoubleClicked) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowEnabled) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowVisibile) SLATE_EVENT(FOnDragDetected, OnRowDragDetected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Descriptor of the list, useful for loading and storing the state of the list to disk
- L126 _public prototype_ `void RequestRefresh();` — Updates the List on the next tick
- L129 _public prototype_ `TArray<UDMXEntityFixturePatch*> GetFixturePatchesInDMXLibrary() const;` — Gets all fixture patches in the DMX Library
- L132 _public prototype_ `TArray<UDMXEntityFixturePatch*> GetFixturePatchesInList() const;` — Gets all fixture patches displayed in the list. Note, the result does not contain excluded fixture patches.
- L135 _public prototype_ `TArray<UDMXEntityFixturePatch*> GetSelectedFixturePatches() const;` — Gets current selected fixture patches in the list
- L138 _public prototype_ `void SetDMXLibrary(UDMXLibrary* InDMXLibrary);` — Sets the displayed DMX library. Note, this does not refresh the list. Call RequestRefresh() to update the list.
- L141 _public prototype_ `void SetExcludedFixturePatches(const TArray<UDMXEntityFixturePatch*>& NewExcludedFixturePatches);` — Sets the excluded fixture patches. Note, this does not refresh the list. Call RequestRefresh() to update the list.
- L144 _public prototype_ `void SelectItems(const TArray<TSharedPtr<FDMXReadOnlyFixturePatchListItem>>& ItemsToSelect, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Selects specified items in the list
- L147 _public prototype_ `void SetItemSelection(TSharedPtr<FDMXReadOnlyFixturePatchListItem> SelectedItem, bool bSelected, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Sets the selection state of the given item, if valid
- L150 _public prototype_ `TArray<TSharedPtr<FDMXReadOnlyFixturePatchListItem>> GetSelectedItems() const;` — Returns the selected items
- L153 _public prototype_ `FDMXReadOnlyFixturePatchListDescriptor MakeListDescriptor() const;` — Gets the a descriptor for the current parameters for this list
- L156 _public function_ `UDMXLibrary* GetDMXLibrary() const` — Gets the current displayed DMX library
- L159 _public function_ `TArray<TSharedPtr<FDMXReadOnlyFixturePatchListItem>> GetListItems() const` — Returns the items displayed int his list
- L163 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L164 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L168 _protected prototype_ `virtual FName GetHeaderRowFilterMenuName() const;` — Returns the menu name of the header row filter menu. Useful to override the default menu and extend it only for a specfic inherited class
- L171 _protected prototype_ `virtual void ForceRefresh();` — Refreshes the Fixture Patch List
- L174 _protected prototype_ `virtual TSharedRef<SHeaderRow> GenerateHeaderRow();` — Called to generate the header row of the list
- L177 _protected prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXReadOnlyFixturePatchListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called to generate a row in the list
- L180 _protected prototype_ `virtual void ToggleColumnShowState(const FName ColumnID);` — Toggles show state of the column with the given ID
- L184 _private prototype_ `TSharedRef<SWidget> GenerateHeaderRowFilterMenu();` — Generates a filter menu fot the Header Row of the List
- L187 _private prototype_ `void ApplyListDescriptor(const FDMXReadOnlyFixturePatchListDescriptor& InListDescriptor);` — Applies settings of the list descriptor
- L190 _private prototype_ `TArray<TSharedPtr<FDMXReadOnlyFixturePatchListItem>> FilterListItems(const FText& SearchText);` — Filters ListItems array by the given search text
- L193 _private prototype_ `void SortByColumnID(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Sort the list by ColumnId
- L196 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);` — Called when text from searchbox is changed
- L199 _private prototype_ `void OnEntityAddedOrRemoved(UDMXLibrary* InDMXLibrary, TArray<UDMXEntity*> Entities);` — Called when entities were added or removed from the DMX Library
- L202 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when a Fixture Patch changed
- L205 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a Fixture Type changed
- L208 _private prototype_ `bool IsColumnShown(const FName ColumnID) const;` — Gets show state of the column with the given ID
- L211 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnID) const;` — Returns the column sort mode for the list
- L214 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;` — The current Sort Mode
- L217 _private member_ `FName SortedByColumnID;` — By which column ID the List is sorted
- L220 _private member_ `TMap<FName, bool> ColumnIDToShowStateMap;` — Map for storing the show state of each column by name ID
- L223 _private member_ `FTimerHandle ListRefreshTimerHandle;` — Timer handle for the Request List Refresh method
- L226 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The Header Row of the List
- L229 _private member_ `TSharedPtr<SListView<TSharedPtr<FDMXReadOnlyFixturePatchListItem>>> ListView;` — The actual fixture patch list
- L232 _private member_ `TArray<TSharedRef<SDMXReadOnlyFixturePatchListRow>> ListRows;` — Rows of Mode widgets in the List
- L235 _private member_ `TArray<TSharedPtr<FDMXReadOnlyFixturePatchListItem>> ListItems;` — The list source, an array of read only fixture patch list items
- L238 _private member_ `TWeakObjectPtr<UDMXLibrary> WeakDMXLibrary;` — Current displayed DMX Library
- L241 _private member_ `TArray<TObjectPtr<UDMXEntityFixturePatch>> ExcludedFixturePatches;` — Slate Arguments
- L242 _private member_ `FDMXFixturePatchListRowRetValDelegate IsRowEnabledDelegate;`
- L243 _private member_ `FDMXFixturePatchListRowRetValDelegate IsRowVisibleDelegate;`
- L244 _private member_ `FOnDragDetected OnRowDragDetectedDelegate;`

#### Free symbols / members of external scopes

- L82 _delegate_ `DECLARE_DELEGATE_OneParam(FDMXFixturePatchListRowDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>) DECLARE_DELEGATE_RetVal_OneParam(bool, FDMXFixturePatchListRowRetValDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>) DECLARE_DELEGATE_TwoParams(FDMXFixturePatchListRowSelectionDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>, ESelectInfo::Type) SLATE_BEGIN_ARGS(SDMXReadOnlyFixturePatchList) : _ListDescriptor(FDMXReadOnlyFixturePatchListDescriptor()) , _DMXLibrary(nullptr) {} SLATE_ARGUMENT(FDMXReadOnlyFixturePatchListDescriptor, ListDescriptor) SLATE_ARGUMENT(UDMXLibrary*, DMXLibrary) SLATE_ARGUMENT(TArray<UDMXEntityFixturePatch*>, ExcludedFixturePatches) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FDMXFixturePatchListRowSelectionDelegate, OnRowSelectionChanged) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowClicked) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowDoubleClicked) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowEnabled) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowVisibile) SLATE_EVENT(FOnDragDetected, OnRowDragDetected) SLATE_END_ARGS()`
- L83 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FDMXFixturePatchListRowRetValDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>) DECLARE_DELEGATE_TwoParams(FDMXFixturePatchListRowSelectionDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>, ESelectInfo::Type) SLATE_BEGIN_ARGS(SDMXReadOnlyFixturePatchList) : _ListDescriptor(FDMXReadOnlyFixturePatchListDescriptor()) , _DMXLibrary(nullptr) {} SLATE_ARGUMENT(FDMXReadOnlyFixturePatchListDescriptor, ListDescriptor) SLATE_ARGUMENT(UDMXLibrary*, DMXLibrary) SLATE_ARGUMENT(TArray<UDMXEntityFixturePatch*>, ExcludedFixturePatches) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FDMXFixturePatchListRowSelectionDelegate, OnRowSelectionChanged) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowClicked) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowDoubleClicked) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowEnabled) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowVisibile) SLATE_EVENT(FOnDragDetected, OnRowDragDetected) SLATE_END_ARGS()`
- L84 _delegate_ `DECLARE_DELEGATE_TwoParams(FDMXFixturePatchListRowSelectionDelegate, TSharedPtr<FDMXReadOnlyFixturePatchListItem>, ESelectInfo::Type) SLATE_BEGIN_ARGS(SDMXReadOnlyFixturePatchList) : _ListDescriptor(FDMXReadOnlyFixturePatchListDescriptor()) , _DMXLibrary(nullptr) {} SLATE_ARGUMENT(FDMXReadOnlyFixturePatchListDescriptor, ListDescriptor) SLATE_ARGUMENT(UDMXLibrary*, DMXLibrary) SLATE_ARGUMENT(TArray<UDMXEntityFixturePatch*>, ExcludedFixturePatches) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FDMXFixturePatchListRowSelectionDelegate, OnRowSelectionChanged) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowClicked) SLATE_EVENT(FDMXFixturePatchListRowDelegate, OnRowDoubleClicked) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowEnabled) SLATE_EVENT(FDMXFixturePatchListRowRetValDelegate, IsRowVisibile) SLATE_EVENT(FOnDragDetected, OnRowDragDetected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Widgets/SDMXReadOnlyFixturePatchListRow.h` (Public)


#### class `SDMXReadOnlyFixturePatchListRow`  
`class SDMXReadOnlyFixturePatchListRow : public SMultiColumnTableRow<TSharedPtr<FDMXReadOnlyFixturePatchListItem>>`  
_L13-53_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXReadOnlyFixturePatchListItem>>`
- desc: Entity Fixture Patch as a row in a list
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXReadOnlyFixturePatchListRow)`
- L20 _public prototype_ `SLATE_EVENT(FOnDragDetected, OnRowDragDetected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedPtr<FDMXReadOnlyFixturePatchListItem>& InItem);`
- L29 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L34 _private prototype_ `TSharedRef<SWidget> GenerateEditorColorRow();` — Generates the row that displays the Fixture Patch Editor Color
- L37 _private prototype_ `TSharedRef<SWidget> GenerateFixturePatchNameRow();` — Generates the row that displays the Fixture Patch Name
- L40 _private prototype_ `TSharedRef<SWidget> GenerateFixtureIDRow();` — Generates the row that displays the Fixture ID
- L43 _private prototype_ `TSharedRef<SWidget> GenerateFixtureTypeRow();` — Generates the row that displays the Fixture Type
- L46 _private prototype_ `TSharedRef<SWidget> GenerateModeRow();` — Generates the row that displays the Mode
- L49 _private prototype_ `TSharedRef<SWidget> GeneratePatchRow();` — Generates the row that displays the Patch
- L52 _private member_ `TSharedPtr<FDMXReadOnlyFixturePatchListItem> Item;` — The item this widget draws

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/Widgets/SNameListPicker.h` (Public)


#### class `SNameListPicker`  
`class SNameListPicker : public SCompoundWidget`  
_L21-129_
- inherits: `SCompoundWidget`
- desc: A widget which allows the user to pick a name of a specified list of names.
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FName);`
- L27 _public member_ `static const FText NoneLabel;`
- L29 _public function_ `SLATE_BEGIN_ARGS(SNameListPicker) : _ComboButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FComboButtonStyle >("ComboButton")) , _ButtonStyle(nullptr) , _bDisplayWarningIcon(false) , _bCanBeNone(false) , _ForegroundColor(FCoreStyle::Get().GetSlateColor("InvertedForeground")) , _ContentPadding(FMargin(2.f, 0.f)) , _HasMultipleValues(false) , _Font(FCoreStyle::GetDefaultFontStyle("Regular", 8)) , _MaxVisibleItems(15)`
- L42 _public prototype_ `SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_ATTRIBUTE(TArray<FName>, OptionsSource) SLATE_ARGUMENT(bool, bDisplayWarningIcon) SLATE_ARGUMENT(bool, bCanBeNone) SLATE_ATTRIBUTE(FSlateColor, ForegroundColor) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FName, Value) SLATE_EVENT(FOnValueChanged, OnValueChanged) SLATE_ATTRIBUTE(bool, HasMultipleValues) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ARGUMENT(int32, MaxVisibleItems) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The visual style of the combo button
- L83 _private prototype_ `EVisibility GetSearchBoxVisibility() const;`
- L84 _private prototype_ `void OnSearchBoxTextChanged(const FText& InSearchText);`
- L85 _private prototype_ `void OnSearchBoxTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L86 _private prototype_ `void UpdateFilteredOptions(const FString& Filter);`
- L88 _private prototype_ `FText GetCurrentNameLabel() const;`
- L90 _private prototype_ `void UpdateOptionsSource();`
- L93 _private prototype_ `TSharedRef<ITableRow> GenerateNameItemWidget(TSharedPtr<FName> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Create an option widget for the combo box
- L95 _private prototype_ `void OnSelectionChanged(const TSharedPtr<FName> Item, ESelectInfo::Type SelectInfo);` — Handles a selection change from the combo box
- L96 _private prototype_ `void OnClickItem(const TSharedPtr<FName> Item);`
- L97 _private prototype_ `void OnUserSelectedItem(const TSharedPtr<FName> Item);`
- L99 _private prototype_ `TSharedPtr<FName> GetSelectedItemFromCurrentValue() const;`
- L107 _private prototype_ `void OnMenuOpened();` — Workaround to keep the correct option highlighted in the dropdown menu. When code changes the current value of the property this button represents, it's possible that the button will keep the previous value highlighted. So we set the currently highlighted option every time the menu is opened.
- L110 _private prototype_ `void OnTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when text was commited
- L113 _private member_ `TSharedPtr< SComboButton > PickerComboButton;`
- L114 _private member_ `TSharedPtr< SListView< TSharedPtr<FName> > > OptionsListView;`
- L115 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L116 _private member_ `int32 MaxVisibleItems;`
- L117 _private member_ `TSharedPtr< SListViewSelectorDropdownMenu< TSharedPtr<FName> > > NamesListDropdown;`
- L118 _private member_ `TSharedPtr<SEditableTextBox> EdititableTextBox;`
- L120 _private member_ `TAttribute<TArray<FName>> OptionsSourceAttr;`
- L121 _private member_ `TArray<TSharedPtr<FName>> OptionsSource;`
- L122 _private member_ `TArray<TSharedPtr<FName>> FilteredOptions;`
- L124 _private member_ `TAttribute<FName> ValueAttribute;`
- L125 _private member_ `FOnValueChanged OnValueChangedDelegate;`
- L126 _private member_ `TAttribute<bool> HasMultipleValuesAttribute;`
- L127 _private member_ `bool bCanBeNone;`
- L128 _private member_ `bool bDisplayWarningIcon;`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FName);`
