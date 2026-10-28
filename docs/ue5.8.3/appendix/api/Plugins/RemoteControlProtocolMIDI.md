# Plugins / RemoteControlProtocolMIDI

- module root: `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDI`
- headers: 4; symbols: 68
- symbol kinds: class=4, delegate=1, enum=1, enumerator=3, function=12, member=19, prototype=25, struct=2, typedef=1
- PrivateDependencyModuleNames: InputCore, RemoteControl, RemoteControlProtocol, RemoteControlProtocolWidgets
- PublicDependencyModuleNames: Core, CoreUObject, MIDIDevice

### `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDI/Private/RemoteControlProtocolMIDIModule.h` (Private)


#### class `FRemoteControlProtocolMIDIModule`  
`class FRemoteControlProtocolMIDIModule : public IRemoteControlProtocolMIDIModule`  
_L17-52_
- inherits: `IRemoteControlProtocolMIDIModule`
- desc: MIDI remote control module
- L20 _public function_ `FRemoteControlProtocolMIDIModule() : bIsUpdatingDevices(false)`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `virtual TFuture<TSharedPtr<TArray<FFoundMIDIDevice>, ESPMode::ThreadSafe>> GetMIDIDevices(bool bRefresh = false) override;` — Get MIDI devices asynchronously. If bRefresh is true, device info is flushed and re-initialized.
- L34 _public function_ `virtual bool IsUpdatingDevices() const override` — Checks if MIDI devices are currently being refreshed/updated.
- L37 _public function_ `virtual FOnMIDIDevicesUpdated& GetOnMIDIDevicesUpdated() override` — Get MIDI Devices Updated callback.
- L41 _private prototype_ `void HandleMIDIDevicesUpdated(FMIDIDeviceCollection& InDevices);` — Called when MIDI devices are updated, to attempt rebind.
- L45 _private member_ `TSharedPtr<TArray<FFoundMIDIDevice>, ESPMode::ThreadSafe> MIDIDeviceCache;` — Maintain a list of MIDI devices until they're updated.
- L48 _private member_ `std::atomic<bool> bIsUpdatingDevices;` — Flag to indicate if MIDI devices are being updating, to prevent redundant update requests.
- L51 _private member_ `FOnMIDIDevicesUpdated OnMIDIDevicesUpdated;` — Callback to indicate when MIDI devices are updated.

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteControlProtocolMIDI, Log, All);`

### `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDI/Public/IRemoteControlProtocolMIDIModule.h` (Public)


#### class `IRemoteControlProtocolMIDIModule`  
`class IRemoteControlProtocolMIDIModule : public IModuleInterface`  
_L21-32_
- inherits: `IModuleInterface`
- desc: MIDI remote control module interface
- L25 _public prototype_ `virtual TFuture<TSharedPtr<TArray<FFoundMIDIDevice>, ESPMode::ThreadSafe>> GetMIDIDevices(bool bRefresh = false) = 0;` — Get MIDI devices asynchronously. If bRefresh is true, device info is flushed and re-initialized.
- L28 _public prototype_ `virtual bool IsUpdatingDevices() const = 0;` — Checks if MIDI devices are currently being refreshed/updated.
- L31 _public prototype_ `virtual FOnMIDIDevicesUpdated& GetOnMIDIDevicesUpdated() = 0;` — Get MIDI Devices Updated callback.

#### Free symbols / members of external scopes

- L11 _typedef_ `using FMIDIDeviceCollection = TSharedPtr<TArray<FFoundMIDIDevice>, ESPMode::ThreadSafe>;`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMIDIDevicesUpdated, FMIDIDeviceCollection& );` — Callback called when MIDI devices are updated.
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMIDIDevicesUpdated, FMIDIDeviceCollection& );` — Callback called when MIDI devices are updated.

### `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDI/Public/RemoteControlProtocolMIDI.h` (Public)


#### enum `ERemoteControlMIDIDeviceSelector`  
`enum class ERemoteControlMIDIDeviceSelector`  
_L21-26_
- reflection: `UENUM()`
- desc: MIDI protocol device selector type
- L23 _public enumerator_ `ProjectSettings = 0 UMETA(DisplayName = "Use Project Settings", ToolTip = "Uses the Default MIDI Device specified in Project Settings.")`
- L24 _public enumerator_ `DeviceName = 1 UMETA(DisplayName = "Device Name", ToolTip = "User-specified device name.")`
- L25 _public enumerator_ `DeviceId = 2 UMETA(DisplayName = "Device Id", ToolTip = "User-specified device id.")`

#### struct `FRemoteControlMIDIDevice`  
`struct FRemoteControlMIDIDevice`  
_L32-90_
- reflection: `USTRUCT()`
- desc: MIDI protocol device identifier
- L38 _public prototype_ `FRemoteControlMIDIDevice() = default;` — Default constructor
- L41 _public function_ `FRemoteControlMIDIDevice(const int32 DeviceId, const FName& DeviceName) : DeviceSelector(ERemoteControlMIDIDeviceSelector::ProjectSettings) , ResolvedDeviceId(DeviceId) , DeviceName(DeviceName)` — Construct for the given DeviceId and DeviceName
- L49 _public function_ `FRemoteControlMIDIDevice(const int32 DeviceId) : DeviceSelector(ERemoteControlMIDIDeviceSelector::DeviceId) , ResolvedDeviceId(DeviceId) , DeviceId(DeviceId)` — Construct for the given DeviceId
- L58 _public member_ `ERemoteControlMIDIDeviceSelector DeviceSelector = ERemoteControlMIDIDeviceSelector::ProjectSettings;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — Midi Device Selector
- L62 _public member_ `int32 ResolvedDeviceId = -1;` — `UPROPERTY(VisibleAnywhere, Category = Mapping, meta = (ClampMin = 0, UIMin = 0))` — Midi Resolved Device Id. Distinct from the user specified Device Id.
- L66 _public member_ `FName DeviceName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — Midi Device Name. If specified, takes priority over DeviceId.
- L70 _public member_ `int32 DeviceId = 1;` — `UPROPERTY(EditAnywhere, Category = Mapping, meta = (ClampMin = 0, UIMin = 0))` — User-specified Midi Device Id
- L74 _public member_ `bool bDeviceIsAvailable = false;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — If device available for use.
- L77 _public prototype_ `int32 ResolveDeviceId(const TArray<FFoundMIDIDevice>& InFoundDevices);` — Resolves the actual Midi Device Id given the FRemoteControlMIDIDevice configuration. Returns INDEX_NONE if device not found or invalid.
- L80 _public prototype_ `void SetDevice(const int32 InDeviceId, const FName& InDeviceName);` — Sets DeviceId and DeviceName, disables bUseProjectSettings and bUseUserDeviceId.
- L83 _public prototype_ `void SetUseProjectSettings();` — Sets bUseProjectSettings = true, clears bUseUserDeviceId.
- L86 _public prototype_ `void SetUserDeviceId();` — Sets bUseUserDeviceId = true, clears bUseProjectSettings.
- L89 _public prototype_ `FText ToDisplayName() const;` — Creates a formatted string to display in the combobox

#### struct `FRemoteControlMIDIProtocolEntity`  
`struct FRemoteControlMIDIProtocolEntity : public FRemoteControlProtocolEntity`  
_L121-163_
- reflection: `USTRUCT()`
- inherits: `FRemoteControlProtocolEntity`
- desc: MIDI protocol entity for remote control binding
- L127 _public function_ `virtual FName GetRangePropertyName() const override`
- L133 _public member_ `FRemoteControlMIDIDevice Device;` — `UPROPERTY(EditAnywhere, Category = Mapping, AdvancedDisplay)` — Midi Device
- L137 _public member_ `EMIDIEventType EventType = EMIDIEventType::ControlChange;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — Midi Event type
- L141 _public member_ `int32 MessageData1 = 0;` — `UPROPERTY(EditAnywhere, Category = Mapping, meta = (DisplayName = "Mapped channel Id"))` — Midi button event message data id for binding
- L145 _public member_ `int32 Channel = 1;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — Midi device channel
- L149 _public member_ `uint8 RangeInputTemplate = 0;` — `UPROPERTY(Transient, meta = (ClampMin = 0, ClampMax = 127))` — Midi range input property template, used for binding.
- L155 _public prototype_ `virtual bool IsSame(const FRemoteControlProtocolEntity* InOther) override;` — Checks if this entity has the same values as the Other. Used to check for duplicate inputs.
- L160 _public prototype_ `virtual void RegisterProperties() override;` — Register(s) all the widgets of this protocol entity.

#### class `FRemoteControlProtocolMIDI`  
`class FRemoteControlProtocolMIDI : public FRemoteControlProtocol`  
_L168-225_
- inherits: `FRemoteControlProtocol`
- desc: MIDI protocol implementation for Remote Control
- L171 _public function_ `FRemoteControlProtocolMIDI() : FRemoteControlProtocol(ProtocolName)`
- L176 _public prototype_ `virtual void Bind(FRemoteControlProtocolEntityPtr InRemoteControlProtocolEntityPtr) override;`
- L177 _public prototype_ `virtual void Unbind(FRemoteControlProtocolEntityPtr InRemoteControlProtocolEntityPtr) override;`
- L178 _public prototype_ `virtual void UnbindAll() override;`
- L179 _public function_ `virtual UScriptStruct* GetProtocolScriptStruct() const override`
- L191 _private prototype_ `void OnReceiveEvent(UMIDIDeviceInputController* MIDIDeviceController, int32 Timestamp, int32 Type, int32 Channel, int32 MessageData1, int32 MessageData2);` — On receive MIDI buffer callback @param	MIDIDeviceController	The MIDI Input Device Controller @param	Timestamp				The MIDI timestamp @param	Channel					The MIDI channel to send @param	MessageData1			The first part of the MIDI data @param	MessageData2			The second part of the MIDI data
- L200 _private prototype_ `void ProcessAutoBinding(EMIDIEventType MIDIEventType, int32 Channel, int32 MessageData1);` — Process the AutoBinding to the Remote Control Entity @param	MIDIEventType		The event type as specified in the EMIDIEventType struct @param	Channel				The MIDI channel @param	MessageData1		The first part of the MIDI data
- L205 _protected prototype_ `virtual void RegisterColumns() override;` — Populates protocol specific columns.
- L211 _private member_ `TMap<UMIDIDeviceInputController*, TMap<int32, TArray<FRemoteControlProtocolEntityWeakPtr>>> MIDIDeviceBindings_ControlChange;` — Binding for ControlChange (11) MIDI protocol
- L214 _private member_ `TMap<FGuid, FRemoteControlProtocolEntityWeakPtr> MIDIDeviceBindings_NoteOn;` — Binding for NoteOn (9) MIDI protocol
- L217 _private member_ `TMap<FGuid, FRemoteControlProtocolEntityWeakPtr> MIDIDeviceBindings_ChannelAfterTouch;` — Binding for ChannelAfterTouch (13) MIDI protocol
- L220 _private member_ `TMap<int32, TStrongObjectPtr<UMIDIDeviceInputController>> MIDIDevices;` — MIDI devices
- L224 _public member_ `static const FName ProtocolName;` — MIDI protocol name

#### Free symbols / members of external scopes

- L93 _function_ `inline uint64 GetTypeHash(const FRemoteControlMIDIDevice& InValue)` — FRemoteControlMIDIDevice equality, depending on what properties are specified Comparison
- L114 _function_ `inline bool operator==(const FRemoteControlMIDIDevice& Lhs, const FRemoteControlMIDIDevice& Rhs)`
- L115 _function_ `inline bool operator!=(const FRemoteControlMIDIDevice& Lhs, const FRemoteControlMIDIDevice& Rhs)`

### `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDI/Public/RemoteControlProtocolMIDISettings.h` (Public)


#### class `URemoteControlProtocolMIDISettings`  
`class URemoteControlProtocolMIDISettings : public UObject`  
_L16-36_
- reflection: `UCLASS(Config = Engine, DefaultConfig)`
- inherits: `UObject`
- desc: MIDI Remote Control Settings
- L21 _public function_ `URemoteControlProtocolMIDISettings()`
- L29 _public member_ `FRemoteControlMIDIDevice DefaultDevice = {1};` — `UPROPERTY(Config, EditAnywhere, Category = MIDI)` — Midi Default Device
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _public prototype_ `virtual void PostInitProperties() override;`
