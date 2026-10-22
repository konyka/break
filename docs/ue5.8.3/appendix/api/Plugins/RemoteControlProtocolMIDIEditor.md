# Plugins / RemoteControlProtocolMIDIEditor

- module root: `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDIEditor`
- headers: 1; symbols: 19
- symbol kinds: class=1, function=2, member=8, prototype=7, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorStyle, EditorWidgets, InputCore, PropertyEditor, RemoteControl, RemoteControlProtocol, RemoteControlProtocolMIDI, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, MIDIDevice

### `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDIEditor/Private/DetailCustomizations/RemoteControlMIDIDeviceCustomization.h` (Private)


#### struct `FMIDIDeviceItem`  
`struct FMIDIDeviceItem`  
_L19-38_
- desc: Menu item for a MIDI Device
- L23 _public function_ `FMIDIDeviceItem(const int32 InDeviceId, const FText& InDeviceName, const bool bInIsAvailable) : DeviceId(InDeviceId) , DeviceName(InDeviceName) , bIsAvailable(bInIsAvailable)`
- L31 _public member_ `int32 DeviceId;` — The unique ID of this MIDI device
- L34 _public member_ `FText DeviceName;` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L37 _public member_ `bool bIsAvailable;` — Whether the device is available

#### class `FRemoteControlMIDIDeviceCustomization`  
`class FRemoteControlMIDIDeviceCustomization : public IPropertyTypeCustomization`  
_L41-81_
- inherits: `IPropertyTypeCustomization`
- desc: Property customization for RemoteControlMIDIDevice
- L44 _public prototype_ `FRemoteControlMIDIDeviceCustomization();`
- L45 _public prototype_ `~FRemoteControlMIDIDeviceCustomization();`
- L48 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L54 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L55 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L60 _private prototype_ `TSharedRef<SWidget> MakeRefreshButton() const;` — Creates a button to refresh MIDI devices
- L63 _private prototype_ `void OnMIDIDevicesUpdated(TSharedPtr<TArray<FFoundMIDIDevice>, ESPMode::ThreadSafe>& InMIDIDevices);` — Called when MIDI devices are updated
- L66 _private member_ `TArray<TSharedPtr<FMIDIDeviceItem, ESPMode::ThreadSafe>> DeviceSource;` — A list of all devices to choose from
- L69 _private member_ `TSharedPtr<SComboButton> DeviceNameComboButton;` — Widgets for the device names
- L70 _private member_ `TSharedPtr<SListView<TSharedPtr<FMIDIDeviceItem, ESPMode::ThreadSafe>>> DeviceNameListView;`
- L73 _private prototype_ `void GetProjectDeviceWidgets(TSharedPtr<SWidget>& OutNameWidget, TSharedPtr<SWidget>& OutValueWidget);` — Get widgets for project device
- L77 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Root property handle
- L80 _private member_ `TSharedPtr<ISinglePropertyView> CachedProjectDevicePropertyView;` — Cached Project Device property view
