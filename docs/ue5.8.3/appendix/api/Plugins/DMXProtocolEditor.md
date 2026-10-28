# Plugins / DMXProtocolEditor

- module root: `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor`
- headers: 13; symbols: 227
- symbol kinds: class=14, enum=2, enumerator=6, function=13, member=71, prototype=121
- PrivateDependencyModuleNames: CoreUObject, Engine, InputCore, Projects, Slate, SlateCore, TimeManagement, UnrealEd
- PublicDependencyModuleNames: Core, DMXProtocol, Networking, PropertyEditor, Sockets

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/DMXInputPortConfigCustomization.h` (Private)


#### class `FDMXInputPortConfigCustomization`  
`class FDMXInputPortConfigCustomization : public IPropertyTypeCustomization`  
_L23-128_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for input and output port configs.
- L27 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L32 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L37 _private prototype_ `void GenerateProtocolNameRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Protocol Name row
- L40 _private prototype_ `void GenerateCommunicationTypeRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Communication Type row
- L43 _private prototype_ `void GenerateDeviceAddressRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Device Address row
- L46 _private prototype_ `void GenerateAutoCompleteDeviceAddressRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Auto Complete Device Address row
- L49 _private prototype_ `void UpdateAutoCompleteDeviceAddressTextBox();` — Updates the Auto Complete Device Address Text Box
- L52 _private prototype_ `void GenerateExternUniverseStartRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Extern Universe Start row
- L55 _private prototype_ `void OnLocalUniverseStartChanged();` — Called when the LocalUniverseStart property changed
- L58 _private prototype_ `void OnIsExternUniverseStartEditableChanged();` — Called when the bIsExternUniverseStartEditable property changed
- L61 _private prototype_ `void OnProtocolNameSelected();` — Called when a Protocol Name was selected
- L64 _private prototype_ `void OnCommunicationTypeSelected();` — Called when a Communication Type was selected
- L67 _private prototype_ `void OnDeviceAddressSelected();` — Called when a local IP Address was selected
- L70 _private prototype_ `IDMXProtocolPtr GetProtocol() const;` — Gets the protocol, checks if it is valid
- L73 _private prototype_ `FGuid GetPortGuid() const;` — Helper function that gets the Guid of the edited port
- L76 _private prototype_ `const TArray<EDMXCommunicationType> GetSupportedCommunicationTypes() const;` — Returns an array of supported communication types
- L79 _private prototype_ `EDMXCommunicationType GetCommunicationType() const;` — Gets the communication type
- L82 _private prototype_ `bool IsAutoCompleteDeviceAddressEnabled() const;` — Returns the value of the AutoCompleteDeviceAddressEnabled property
- L85 _private prototype_ `FString GetIPAddress() const;` — Gets the IP Address
- L88 _private member_ `TSharedPtr<IPropertyHandle> ProtocolNameHandle;` — Property handle to the ProtocolName property
- L91 _private member_ `TSharedPtr<IPropertyHandle> AutoCompleteDeviceAddressEnabledHandle;` — Property handle to the bAutoCompleteDeviceAddressEnabled property
- L94 _private member_ `TSharedPtr<IPropertyHandle> AutoCompleteDeviceAddressHandle;` — Property handle to the AutoCompleteDeviceAddress property
- L97 _private member_ `TSharedPtr<IPropertyHandle> DeviceAddressHandle;` — Property handle to the IPAddress property
- L100 _private member_ `TSharedPtr<IPropertyHandle> CommunicationTypeHandle;` — Property handle to the CommunicationType property
- L103 _private member_ `TSharedPtr<IPropertyHandle> LocalUniverseStartHandle;` — Property handle to the LocalUniverseStart property
- L106 _private member_ `TSharedPtr<IPropertyHandle> ExternUniverseStartHandle;` — Property handle to the ExternUniverseStart property
- L109 _private member_ `TSharedPtr<IPropertyHandle> IsExternUniverseStartEditableHandle;` — Property handle to the IsExternUniverseStartEditable property
- L112 _private member_ `TSharedPtr<IPropertyHandle> PortGuidHandle;` — Property handle to the PortGuid property
- L115 _private member_ `TSharedPtr<SDMXCommunicationTypeComboBox> CommunicationTypeComboBox;` — ComboBox that exposes a selection of communication types to the user
- L118 _private member_ `TSharedPtr<SDMXProtocolNameComboBox> ProtocolNameComboBox;` — ComboBox to select a protocol name
- L121 _private member_ `TSharedPtr<SDMXIPAddressEditWidget> IPAddressEditWidget;` — ComboBox that displays the device address when it is editable
- L124 _private member_ `TSharedPtr<STextBlock> AutoCompletedDeviceAddressTextBlock;` — Text Block that displays the device address when it is auto completed
- L127 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/DMXInputPortReferenceCustomization.h` (Private)


#### class `FDMXInputPortReferenceCustomization`  
`class FDMXInputPortReferenceCustomization : public FDMXPortReferenceCustomizationBase`  
_L19-38_
- inherits: `FDMXPortReferenceCustomizationBase`
- desc: Details customization for input and Input port references.
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L27 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L32 _protected function_ `virtual bool IsInputPort() const override`
- L33 _protected prototype_ `virtual const TSharedPtr<IPropertyHandle>& GetPortGuidHandle() const override;`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> PortGuidHandle;` — Property handle to the PortGuid property

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/DMXOutputPortConfigCustomization.h` (Private)


#### class `FDMXOutputPortConfigCustomization`  
`class FDMXOutputPortConfigCustomization : public IPropertyTypeCustomization`  
_L25-160_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for input and output port configs.
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L33 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L34 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L39 _private prototype_ `void GenerateProtocolNameRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Protocol Name row
- L42 _private prototype_ `void GenerateCommunicationTypeRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Communication Type row
- L45 _private prototype_ `void GenerateDeviceAddressRow(IDetailPropertyRow& PropertyRow);` — Generates the customized IP Address row
- L48 _private prototype_ `void GenerateAutoCompleteDeviceAddressRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Auto Complete Device Address row
- L51 _private prototype_ `void UpdateAutoCompleteDeviceAddressTextBox();` — Updates the Auto Complete Device Address Text Box
- L54 _private prototype_ `void GenerateExternUniverseStartRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Extern Universe Start row
- L57 _private prototype_ `void OnLocalUniverseStartChanged();` — Called when the LocalUniverseStart property changed
- L60 _private prototype_ `void OnIsExternUniverseStartEditableChanged();` — Called when the bIsExternUniverseStartEditable property changed
- L63 _private prototype_ `void GenerateDelayRow(IDetailPropertyRow& PropertyRow);` — Generates the customized Delay Seconds row
- L66 _private prototype_ `void OnProtocolNameSelected();` — Called when a Protocol Name was selected
- L69 _private prototype_ `void OnCommunicationTypeSelected();` — Called when a Communication Type was selected
- L72 _private prototype_ `void OnDeviceAddressSelected();` — Called when a Device Address was selected
- L75 _private prototype_ `void UpdateDestinationAddressesVisibility();` — Called when the Destination Addresses Array visibility needs to be updated
- L78 _private prototype_ `void OnDelayChanged();` — Called when the Delay Seconds changed in the Delay Edit Widget
- L81 _private prototype_ `void OnDelayFrameRateChanged();` — Called when the Delay Frame Rate changed in the Delay Edit Widget
- L84 _private prototype_ `double GetDelay() const;` — Returns the delay of the port
- L87 _private prototype_ `TArray<FFrameRate> GetDelayFrameRates() const;` — Returns the delay frame rate of the port
- L90 _private prototype_ `IDMXProtocolPtr GetProtocol() const;` — Gets the protocol, checks if it is valid
- L93 _private prototype_ `FGuid GetPortGuid() const;` — Helper function that gets the Guid of the edited port
- L96 _private prototype_ `const TArray<EDMXCommunicationType> GetSupportedCommunicationTypes() const;` — Returns an array of supported communication types
- L99 _private prototype_ `EDMXCommunicationType GetCommunicationType() const;` — Gets the communication type
- L102 _private prototype_ `bool IsAutoCompleteDeviceAddressEnabled() const;` — Returns the value of the AutoCompleteDeviceAddressEnabled property
- L105 _private prototype_ `FString GetIPAddress() const;` — Gets the IP Address
- L108 _private member_ `TSharedPtr<IPropertyHandle> ProtocolNameHandle;` — Property handle to the ProtocolName property
- L111 _private member_ `TSharedPtr<IPropertyHandle> AutoCompleteDeviceAddressEnabledHandle;` — Property handle to the bAutoCompleteDeviceAddressEnabled property
- L114 _private member_ `TSharedPtr<IPropertyHandle> AutoCompleteDeviceAddressHandle;` — Property handle to the AutoCompleteDeviceAddress property
- L117 _private member_ `TSharedPtr<IPropertyHandle> DeviceAddressHandle;` — Property handle to the IPAddress property
- L120 _private member_ `TSharedPtr<IPropertyHandle> CommunicationTypeHandle;` — Property handle to the CommunicationType property
- L123 _private member_ `TSharedPtr<IPropertyHandle> LocalUniverseStartHandle;` — Property handle to the LocalUniverseStart property
- L126 _private member_ `TSharedPtr<IPropertyHandle> ExternUniverseStartHandle;` — Property handle to the ExternUniverseStart property
- L129 _private member_ `TSharedPtr<IPropertyHandle> IsExternUniverseStartEditableHandle;` — Property handle to the IsExternUniverseStartEditable property
- L132 _private member_ `TSharedPtr<IPropertyHandle> DelayHandle;` — Property handle to the Delay property
- L135 _private member_ `TSharedPtr<IPropertyHandle> DelayFrameRateHandle;` — Property handle to the DelayFrameRate property
- L138 _private member_ `TSharedPtr<IPropertyHandle> PortGuidHandle;` — Property handle to the PortGuid property
- L141 _private member_ `EVisibility DestinationAddressesVisibility;` — Visibility of the destination addresses array
- L144 _private member_ `TSharedPtr<SDMXProtocolNameComboBox> ProtocolNameComboBox;` — ComboBox to select a protocol name
- L147 _private member_ `TSharedPtr<SDMXCommunicationTypeComboBox> CommunicationTypeComboBox;` — ComboBox that exposes a selection of communication types to the user
- L150 _private member_ `TSharedPtr<STextBlock> AutoCompletedDeviceAddressTextBlock;` — Text Block that displays the device address when it is auto completed
- L153 _private member_ `TSharedPtr<SDMXIPAddressEditWidget> IPAddressEditWidget;` — ComboBox that displays local ip addresses
- L156 _private member_ `TSharedPtr<SDMXDelayEditWidget> DelayEditWidget;` — Custom widget that lets the user set the delay
- L159 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/DMXOutputPortDestinationAddressCustomization.h` (Private)


#### class `FDMXOutputPortDestinationAddressCustomization`  
`class FDMXOutputPortDestinationAddressCustomization : public IPropertyTypeCustomization`  
_L14-44_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the DMXOutputPortConfigCustomization struct
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _private prototype_ `FString GetIPAddress() const;` — Gets the IP Address currently set
- L31 _private prototype_ `void SetIPAddress(const FString& NewIPAddress);` — Sets the IP Adderss
- L34 _private prototype_ `void OnDestinationAddressSelected();` — Called when a destination Address was selected
- L37 _private prototype_ `FReply OnDeleteDestinationAddressClicked();` — Called when a destination address wants to be deleted
- L40 _private member_ `TSharedPtr<SDMXIPAddressEditWidget> IPAddressEditWidget;` — Widget to enter an IP address
- L43 _private member_ `TSharedPtr<IPropertyHandle> DestinationAddressStringHandle;` — Property handle for the DestinationAddressString property

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/DMXOutputPortReferenceCustomization.h` (Private)


#### class `FDMXOutputPortReferenceCustomization`  
`class FDMXOutputPortReferenceCustomization : public FDMXPortReferenceCustomizationBase`  
_L20-39_
- inherits: `FDMXPortReferenceCustomizationBase`
- desc: Details customization for input and output port references.
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L28 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L29 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L33 _protected function_ `virtual bool IsInputPort() const override`
- L34 _protected prototype_ `virtual const TSharedPtr<IPropertyHandle>& GetPortGuidHandle() const override;`
- L38 _protected member_ `TSharedPtr<IPropertyHandle> PortGuidHandle;` — Property handle to the PortGuid property

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/DMXPortReferenceCustomizationBase.h` (Private)


#### class `FDMXPortReferenceCustomizationBase`  
`class FDMXPortReferenceCustomizationBase : public IPropertyTypeCustomization`  
_L20-64_
- inherits: `IPropertyTypeCustomization`
- desc: Base class for input and output port reference details customizations.
- L24 _protected prototype_ `FDMXPortReferenceCustomizationBase();`
- L26 _protected function_ `virtual ~FDMXPortReferenceCustomizationBase()`
- L30 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L31 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L35 _protected prototype_ `virtual bool IsInputPort() const = 0;` — Called to deduce if the child is an input (or an output)
- L38 _protected prototype_ `virtual const TSharedPtr<IPropertyHandle>& GetPortGuidHandle() const = 0;` — Called to get the PortGuid property handle
- L42 _private prototype_ `void OnPortSelected();` — Called when a port was selected in the port selector
- L45 _private prototype_ `void OnPortsChanged();` — Called when ports changed
- L48 _private prototype_ `TArray<FDMXPortSharedPtr> FindPortItems() const;` — Helper function that finds the corresponding input port, or nullptr if no corresponding port
- L51 _private prototype_ `void ApplySelectedPortGuid();` — Applies the selected port Guid to the customized struct
- L54 _private prototype_ `TArray<FGuid> GetPortGuids() const;` — Helper function that gets the Guid of the edited port(s)
- L57 _private member_ `TSharedPtr<SDMXPortSelector> PortSelector;` — Port selector widget
- L60 _private member_ `FText ErrorText;` — Error text shown when the port couldn't be found, may contain the last error if there is no error - I11t is not a state.
- L63 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Detail customization utils

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/DMXProtocolSettingsDetails.h` (Private)


#### class `FDMXProtocolSettingsDetails`  
`class FDMXProtocolSettingsDetails : public IDetailCustomization`  
_L10-28_
- inherits: `IDetailCustomization`
- desc: Details customization for the DMMXFixturePatch class
- L15 _public prototype_ `FDMXProtocolSettingsDetails();` — Constructor
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates a detail customization instance
- L22 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L27 _private member_ `const bool bIsDMXEnginePluginEnabled;` — True if the DMX Engine Plugin is enabled

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/Widgets/SDMXCommunicationTypeComboBox.h` (Private)


#### class `SDMXCommunicationTypeComboBox`  
`class SDMXCommunicationTypeComboBox : public SCompoundWidget`  
_L22-71_
- inherits: `SCompoundWidget`
- desc: Helper widget to select a Communication Type. Can adjust the types via SetCommunicationTypes after construction. Hides itself if no communication type is available.
- L26 _public function_ `SLATE_BEGIN_ARGS(SDMXCommunicationTypeComboBox) : _InitialCommunicationType(EDMXCommunicationType::InternalOnly)`
- L30 _public prototype_ `SLATE_ARGUMENT(TArray<EDMXCommunicationType>, CommunicationTypes) SLATE_ARGUMENT(EDMXCommunicationType, InitialCommunicationType) SLATE_EVENT(FSimpleDelegate, OnCommunicationTypeSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `EDMXCommunicationType GetSelectedCommunicationType() const;` — Returns the selected Communication Type
- L46 _private prototype_ `void SetCommunicationTypesInternal(const TArray<EDMXCommunicationType>& NewCommunicationTypes);` — Sets the communication type but doesn't raise an external event, useful for initialization
- L49 _private prototype_ `void GenerateOptionsSource(const TArray<EDMXCommunicationType>& CommunicationTypes);` — Generates the CommunicationTypesSource from the provided Communication Types
- L52 _private prototype_ `TSharedRef<SWidget> GenerateCommunicationTypeComboBoxEntry(TSharedPtr<FString> InCommunicationTypeString);` — Called when the combo box creates its entries
- L55 _private prototype_ `void HandleCommunicationTypeSelectionChanged(TSharedPtr<FString> InCommunicationTypeString, ESelectInfo::Type InSelectInfo);` — Called when the communication type in the combo box changed
- L58 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> CommunicationTypeComboBox;` — The actual combo box
- L61 _private member_ `static const TMap<EDMXCommunicationType, TSharedPtr<FString>> CommunicationTypeToStringMap;` — A string for each communication type to ease conversion
- L64 _private member_ `TArray<TSharedPtr<FString>> CommunicationTypesSource;` — Array of Communication Types to serve as combo box source
- L67 _private member_ `TSharedPtr<STextBlock> CommunicationTypeTextBlock;` — Text box shown on top of the Communication Type combo box
- L70 _private member_ `FSimpleDelegate OnCommunicationTypeSelected;` — Delegate executed when a Communication Type was selected

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/Widgets/SDMXDelayEditWidget.h` (Private)


#### class `SDMXDelayEditWidget`  
`class SDMXDelayEditWidget : public SCompoundWidget`  
_L15-78_
- inherits: `SCompoundWidget`
- desc: Helper widget to select a delay either by Seconds or by a Frame Rate
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXDelayEditWidget)`
- L23 _public prototype_ `SLATE_ARGUMENT(double, InitialDelay) SLATE_ARGUMENT(FFrameRate, InitialDelayFrameRate) SLATE_EVENT(FSimpleDelegate, OnDelayChanged) SLATE_EVENT(FSimpleDelegate, OnDelayFrameRateChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The initially displayed delay in seconds
- L40 _public prototype_ `double GetDelay() const;` — Returns the delay in seconds
- L43 _public prototype_ `FFrameRate GetDelayFrameRate() const;` — Returns the delay frame rate
- L47 _private prototype_ `TSharedRef<SWidget> GenerateDelayTypeMenu();` — Generates the menu to select a Type
- L50 _private prototype_ `bool OnVerifyValueTextChanged(const FText& InNewText, FText& OutErrorMessage);` — Called when the value text changed but was not commited
- L53 _private prototype_ `void OnValueTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when the value text was commited
- L56 _private prototype_ `void OnDelayTypeChanged(FFrameRate NewDelayFrameRate);` — Called when the delay Type changed
- L59 _private prototype_ `bool IsSameDelayType(FFrameRate FrameRate) const;` — Called to test if the delay Type is the same as the selected one
- L62 _private prototype_ `bool DisplayAsFramesPerSecond() const;` — Returns true if values should be displayed as frames per second
- L65 _private member_ `TSharedPtr<SEditableTextBox> ValueEditBox;` — Box to enter the Delay value
- L68 _private member_ `FSimpleDelegate OnDelayChanged;` — Delegate executed when the selected delay changed
- L71 _private member_ `FSimpleDelegate OnDelayFrameRateChanged;` — Delegate executed when the selected delay changed
- L74 _private member_ `double Delay = 0.0;` — The currently set delay, in seconds
- L77 _private member_ `FFrameRate DelayFrameRate;` — The frame rate in which the delay is displayed

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/Widgets/SDMXIPAddressEditWidget.h` (Private)


#### class `SDMXIPAddressEditWidget`  
`class SDMXIPAddressEditWidget : public SCompoundWidget`  
_L18-62_
- inherits: `SCompoundWidget`
- desc: Helper widget that draws a local IP address in a combobox.
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXIPAddressEditWidget) : _bShowLocalNICComboBox(false)`
- L26 _public prototype_ `SLATE_ARGUMENT(FString, InitialValue) SLATE_ARGUMENT(bool, bShowLocalNICComboBox) SLATE_EVENT(FSimpleDelegate, OnIPAddressSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L39 _public prototype_ `FString GetSelectedIPAddress() const;` — Returns the selected IP Address
- L43 _private prototype_ `void OnIpAddressSelected(TSharedPtr<FString> InAddress, ESelectInfo::Type InType);` — Handles changes in the local adapter address combo box
- L46 _private prototype_ `void OnIPAddressTextCommmited(const FText&, ETextCommit::Type);` — Called when the IP Address was commited in the editable text block
- L49 _private prototype_ `TSharedRef<SWidget> GenerateLocalAdapterAddressComboBoxEntry(TSharedPtr<FString> InAddress);` — Generates an entry in the local adapter address combo box
- L52 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> LocalAdapterAddressComboBox;` — ComboBox shown when in local adapter mode
- L55 _private member_ `FSimpleDelegate OnIPAddressSelectedDelegate;` — Delegate executed when a local IP address was selected
- L58 _private member_ `TArray<TSharedPtr<FString>> LocalAdapterAddressSource;` — Array of LocalAdapterAddresses available to the system
- L61 _private member_ `TSharedPtr<SEditableTextBox> IPAddressEditableTextBlock;` — Text box shown on top of the local adapter address address combo box

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Private/DetailsCustomizations/Widgets/SDMXProtocolNameComboBox.h` (Private)


#### class `SDMXProtocolNameComboBox`  
`class SDMXProtocolNameComboBox : public SCompoundWidget`  
_L14-51_
- inherits: `SCompoundWidget`
- desc: Helper widget to select a Protocol Name
- L18 _public function_ `SLATE_BEGIN_ARGS(SDMXProtocolNameComboBox)`
- L21 _public prototype_ `SLATE_ARGUMENT(FName, InitiallySelectedProtocolName) SLATE_EVENT(FSimpleDelegate, OnProtocolNameSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `FName GetSelectedProtocolName() const;` — Returns the selected Communication Type
- L34 _private prototype_ `TSharedRef<SWidget> GenerateProtocolNameComboBoxEntry(TSharedRef<FString> InProtocolNameString);`
- L36 _private prototype_ `void HandleProtocolNameSelectionChanged(TSharedPtr<FString> InProtocolNameString, ESelectInfo::Type InSelectInfo);`
- L38 _private member_ `TSharedPtr<SComboBox<TSharedRef<FString>>> ProtocolNameComboBox;`
- L41 _private member_ `TArray<TSharedRef<FString>> ProtocolNamesSource;` — Array of Communication Types to serve as combo box source
- L44 _private member_ `TMap<TSharedRef<FString>, FName> StringToProtocolMap;` — Protocol Names with their string repesentation in the combo box
- L47 _private member_ `TSharedPtr<STextBlock> ProtocolNameTextBlock;` — Text box shown on top of the Communication Type combo box
- L50 _private member_ `FSimpleDelegate OnProtocolNameSelected;` — Delegate executed when a Communication Type was selected

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Public/DMXProtocolEditorModule.h` (Public)


#### class `FDMXProtocolEditorModule`  
`class FDMXProtocolEditorModule : public IModuleInterface`  
_L8-26_
- inherits: `IModuleInterface`
- desc: Implements the DMXProtocolEditor Module
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `static FDMXProtocolEditorModule& Get();` — Get the instance of this module.
- L22 _private prototype_ `void RegisterDetailsCustomizations();` — Registers details customizations
- L25 _private prototype_ `void UnregisterDetailsCustomizations();` — Unregisters details customizations

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolEditor/Public/Widgets/SDMXPortSelector.h` (Public)


#### enum `EDMXPortSelectorMode`  
`enum class EDMXPortSelectorMode : uint8`  
_L21-26_
- L23 _public enumerator_ `SelectFromAvailableInputs`
- L24 _public enumerator_ `SelectFromAvailableOutputs`
- L25 _public enumerator_ `SelectFromAvailableInputsAndOutputs`

#### enum `EDMXPortSelectorItemType`  
`enum class EDMXPortSelectorItemType : uint8`  
_L28-33_
- L30 _public enumerator_ `TitleRow`
- L31 _public enumerator_ `Input`
- L32 _public enumerator_ `Output`

#### class `FDMXPortSelectorItem`  
`class FDMXPortSelectorItem : public TSharedFromThis<FDMXPortSelectorItem>`  
_L36-62_
- inherits: `TSharedFromThis<FDMXPortSelectorItem>`
- desc: An item in the Port Selector Combo Box
- L40 _public prototype_ `static TSharedRef<FDMXPortSelectorItem> CreateTitleRowItem(const FString& TitleString);`
- L42 _public prototype_ `static TSharedRef<FDMXPortSelectorItem> CreateItem(const FDMXInputPortConfig& InPortConfig);`
- L44 _public prototype_ `static TSharedRef<FDMXPortSelectorItem> CreateItem(const FDMXOutputPortConfig& InPortConfig);`
- L46 _public function_ `bool IsTitleRow() const`
- L48 _public function_ `const FGuid& GetGuid() const`
- L50 _public function_ `const FString& GetItemName() const`
- L52 _public function_ `const EDMXPortSelectorItemType GetType() const`
- L55 _private member_ `FString ItemName;`
- L58 _private member_ `FGuid PortGuid;` — Port Guid, invalid if a title row
- L61 _private member_ `EDMXPortSelectorItemType Type;` — The type of the item

#### class `SDMXPortSelector`  
`class SDMXPortSelector : public SCompoundWidget`  
_L69-164_
- inherits: `SCompoundWidget`
- desc: A widget that allows to select a DMX port available in from the DMXPortManager. Directly returns corresponding DMXPort via the GetPort method.
- L73 _public function_ `SLATE_BEGIN_ARGS(SDMXPortSelector) : _Mode(EDMXPortSelectorMode::SelectFromAvailableInputsAndOutputs) , _InitialSelection(FGuid())`
- L78 _public function_ `SLATE_ARGUMENT(EDMXPortSelectorMode, Mode) SLATE_ARGUMENT(FGuid, InitialSelection) SLATE_EVENT(FSimpleDelegate, OnPortSelected) SLATE_END_ARGS() SDMXPortSelector() : bIsUnderConstruction(true)`
- L91 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget
- L94 _public prototype_ `bool IsInputPortSelected() const;` — Returns true if an input port is selected
- L97 _public prototype_ `bool IsOutputPortSelected() const;` — Returns true if an output port is selected
- L100 _public prototype_ `FDMXInputPortSharedPtr GetSelectedInputPort() const;` — Returns the selected input port, or nullptr if no valid input port is selected
- L103 _public prototype_ `FDMXOutputPortSharedPtr GetSelectedOutputPort() const;` — Returns the selected output port, or nullptr if no valid output port is selected
- L106 _public prototype_ `bool HasSelection() const;` — Returns true if a valid port is selected
- L109 _public prototype_ `void SelectPort(const FGuid& PortGuid);` — Selects specified Port by Port Guid. If the Guid is not valid, clears the selection
- L115 _public prototype_ `void SetHasMultipleValues();` — Instead of showing a selected port, the widget displays 'Multiple Values' and no longer returns a selected port. The widget will no longer display 'Multiple Values' when a selection was made.
- L119 _private prototype_ `TSharedRef<SWidget> GenerateComboBoxEntry(TSharedPtr<FDMXPortSelectorItem> Item);` — Called to generate entries in the port name combo box
- L122 _private prototype_ `void OnPortItemSelectionChanged(TSharedPtr<FDMXPortSelectorItem> Item, ESelectInfo::Type InSelectInfo);` — Called when an item was selected in the port name combo box
- L125 _private prototype_ `TArray<TSharedPtr<FDMXPortSelectorItem>> MakeComboBoxSource();` — Creates a a combo box source froma what's currently in settings
- L128 _private prototype_ `void GenerateWidgetsFromPorts();` — Generates new widgets in the selector from currently available port configs
- L131 _private prototype_ `TSharedPtr<FDMXPortSelectorItem> FindPortItem(const FGuid& PortGuid) const;` — Returns the port if it exists, or nullptr if the port doesn't exist
- L134 _private prototype_ `TSharedPtr<FDMXPortSelectorItem> GetFirstPortInComboBoxSource() const;` — Returns the first valid port from the combo box source, or nullptr if there is no valid port
- L137 _private prototype_ `void OnPortsChanged();` — Called when ports changed
- L140 _private member_ `bool bHasMultipleValues = false;` — State where the widget was set to have multiple values
- L143 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FDMXPortSelectorItem>>> PortNameComboBox;` — The combo box that holds all ports
- L146 _private member_ `TArray<TSharedPtr<FDMXPortSelectorItem>> ComboBoxSource;` — Array of Port Selector Items to serve as combo box source
- L149 _private member_ `TSharedPtr<FDMXPortSelectorItem> RestoreItem;` — The last selected item. Use only to restore from selecting a category row.
- L152 _private member_ `TSharedPtr<STextBlock> PortNameTextBlock;` — Text box shown on top of the Port Name Combo Box
- L155 _private member_ `TSharedPtr<SBorder> ContentBorder;` — Border that holds all the arbitrary content, to switch content dynamically
- L158 _private member_ `EDMXPortSelectorMode Mode;` — Defines which ports are shown
- L161 _private member_ `bool bIsUnderConstruction;` — True during Construct, to avoid raising OnPortSelected while the widget is not valid yet
- L163 _private member_ `FSimpleDelegate OnPortSelected;`
