# Plugins / MIDIDevice

- module root: `Plugins/Runtime/MIDIDevice/Source/MIDIDevice`
- headers: 6; symbols: 119
- symbol kinds: class=5, delegate=10, enum=1, enumerator=8, function=8, macro=5, member=34, namespace=1, prototype=45, struct=2
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/MIDIDevice/Source/MIDIDevice/Private/MIDIDeviceLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMIDIDevice, Verbose, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMIDIDevice, Verbose, All);`
- L10 _namespace_ `namespace MIDIDeviceInternal`
- L13 _function_ `static FString ParsePmError(const PmError& InError)` (scope `MIDIDeviceInternal`) — Returns error text for the given PmError

### `Plugins/Runtime/MIDIDevice/Source/MIDIDevice/Public/MIDIDeviceController.h` (Public)


#### enum `EMIDIEventType`  
`enum class EMIDIEventType : uint8`  
_L17-43_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Unknown UMETA(Hidden)` — Unrecognized MIDI event type.  You can look at Raw Event Type to see what it is.
- L23 _public enumerator_ `NoteOff = 8` — Note is released.  Velocity will contain the key pressure for devices that support that.
- L26 _public enumerator_ `NoteOn = 9` — Note is pressed down.  Velocity will contain the key pressure for devices that support that.
- L29 _public enumerator_ `NoteAfterTouch = 10` — Polyphonic key pressure.  This is sent after a key 'bottoms out' for devices that support it.  Velocity will contain the pressure value.
- L32 _public enumerator_ `ControlChange = 11` — This is sent for things like pedals when their controller state changes.  Velocity will contain the new value for the controller.  This event also is used for 'Channel Mode Changes' (Channels between 120-127), which encompass a variety of different features.  For those events, you'll need to interpret the values yourself.
- L35 _public enumerator_ `ProgramChange = 12` — This is sent for some devices that support changing patches.  Velocity is usually ignored
- L38 _public enumerator_ `ChannelAfterTouch = 13` — Channel pressure value.  This is sent after a channel button 'bottoms out' for devices that support it.  Velocity will contain the pressure value.
- L42 _public enumerator_ `PitchBend = 14` — @todo midi: Ideally set velocity to correct values in this case so Blueprints don't have to

#### class `UMIDIDeviceController`  
`class UMIDIDeviceController : public UMIDIDeviceControllerBase`  
_L51-93_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMIDIDeviceControllerBase`
- L58 _public prototype_ `virtual ~UMIDIDeviceController();` — Destructor that shuts down the device if it's still in use
- L62 _public member_ `FOnMIDIEvent OnMIDIEvent;` — `UPROPERTY(BlueprintAssignable, Category="MIDI Device Controller")` — Register with this to find out about incoming MIDI events from this device
- L65 _public prototype_ `virtual void StartupDevice(const int32 InitDeviceID, const int32 InitMIDIBufferSize, bool& bOutWasSuccessful) override;` — Called from UMIDIDeviceManager after the controller is created to get it ready to use.  Don't call this directly.
- L68 _public prototype_ `virtual void ProcessIncomingMIDIEvents() override;` — Called every frame by UMIDIDeviceManager to poll for new MIDI events and broadcast them out to subscribers of OnMIDIEvent.  Don't call this directly.
- L71 _public prototype_ `virtual void ShutdownDevice() override;` — Called during destruction to clean up this device.  Don't call this directly.
- L74 _public function_ `virtual FString GetDeviceName() const override` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L77 _public function_ `virtual int32 GetMIDIBufferSize() const override` — Size of the MIDI buffer in bytes
- L82 _protected member_ `int32 DeviceID;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Controller")` — The unique ID of this device
- L86 _protected member_ `FString DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "MIDI Device Controller")` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L89 _protected member_ `void* PMMIDIInputStream;` — The PortMidi stream used for MIDI input for this device
- L92 _protected member_ `int32 MIDIBufferSize;` — Size of the MIDI buffer in bytes

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MIDIDEVICE_API`
- L47 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnMIDIEvent, class UMIDIDeviceController*, MIDIDeviceController, int32, Timestamp, EMIDIEventType, EventType, int32, Channel, int32, ControlID, int32, Velocity, int32, RawEventType);` — Callback function for received MIDI events
- L47 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnMIDIEvent, class UMIDIDeviceController*, MIDIDeviceController, int32, Timestamp, EMIDIEventType, EventType, int32, Channel, int32, ControlID, int32, Velocity, int32, RawEventType);` — Callback function for received MIDI events

### `Plugins/Runtime/MIDIDevice/Source/MIDIDevice/Public/MIDIDeviceControllerBase.h` (Public)


#### class `UMIDIDeviceControllerBase`  
`class UMIDIDeviceControllerBase : public UObject`  
_L13-32_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Common functionality for the different MIDI Device Controllers.
- L19 _public function_ `virtual void StartupDevice(const int32 InitDeviceID, const int32 InitMIDIBufferSize, bool& bOutWasSuccessful) PURE_VIRTUAL(UMIDIDeviceControllerBase::StartupDevice,;) virtual void ProcessIncomingMIDIEvents()` — Called from UMIDIDeviceManager after the controller is created to get it ready to use.  Don't call this directly.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MIDIDEVICE_API`

### `Plugins/Runtime/MIDIDevice/Source/MIDIDevice/Public/MIDIDeviceInputController.h` (Public)


#### class `UMIDIDeviceInputController`  
`class UMIDIDeviceInputController : public UMIDIDeviceControllerBase`  
_L42-111_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMIDIDeviceControllerBase`
- L49 _public prototype_ `virtual ~UMIDIDeviceInputController();` — Destructor that shuts down the device if it's still in use
- L53 _public member_ `FOnMIDINoteOn OnMIDINoteOn;` — `UPROPERTY(BlueprintAssignable, Category = "MIDI Device Input Controller")` — Register with this to receive incoming MIDI Note On events from this device
- L57 _public member_ `FOnMIDINoteOff OnMIDINoteOff;` — `UPROPERTY(BlueprintAssignable, Category = "MIDI Device Input Controller")` — Register with this to receive incoming MIDI Note Off events from this device
- L61 _public member_ `FOnMIDIPitchBend OnMIDIPitchBend;` — `UPROPERTY(BlueprintAssignable, Category = "MIDI Device Input Controller")` — Register with this to receive incoming MIDI Pitch Bend events from this device
- L65 _public member_ `FOnMIDIAftertouch OnMIDIAftertouch;` — `UPROPERTY(BlueprintAssignable, Category = "MIDI Device Input Controller")` — Register with this to receive incoming MIDI Aftertouch events from this device
- L69 _public member_ `FOnMIDIControlChange OnMIDIControlChange;` — `UPROPERTY(BlueprintAssignable, Category = "MIDI Device Input Controller")` — Register with this to receive incoming MIDI Control Change events from this device
- L73 _public member_ `FOnMIDIProgramChange OnMIDIProgramChange;` — `UPROPERTY(BlueprintAssignable, Category = "MIDI Device Input Controller")` — Register with this to receive incoming MIDI Program Change events from this device
- L77 _public member_ `FOnMIDIChannelAftertouch OnMIDIChannelAftertouch;` — `UPROPERTY(BlueprintAssignable, Category = "MIDI Device Input Controller")` — Register with this to receive incoming MIDI Channel Aftertouch events from this device
- L80 _public member_ `FOnMIDIRawEvent OnMIDIRawEvent;` — Register with this to receive all of the MIDI events from this device
- L83 _public prototype_ `virtual void StartupDevice(const int32 InitDeviceID, const int32 InitMIDIBufferSize, bool& bOutWasSuccessful) override;` — Called from UMIDIDeviceManager after the controller is created to get it ready to use.  Don't call this directly.
- L86 _public prototype_ `virtual void ProcessIncomingMIDIEvents() override;` — Called every frame by UMIDIDeviceManager to poll for new MIDI events and broadcast them out to subscribers of OnMIDIEvent.  Don't call this directly.
- L89 _public prototype_ `virtual void ShutdownDevice() override;` — Called during destruction to clean up this device.  Don't call this directly.
- L92 _public function_ `virtual FString GetDeviceName() const override` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L95 _public function_ `virtual int32 GetMIDIBufferSize() const override` — Size of the MIDI buffer in bytes
- L100 _protected member_ `int32 DeviceID;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Input Controller")` — The unique ID of this device
- L104 _protected member_ `FString DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "MIDI Device Input Controller")` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L107 _protected member_ `void* PMMIDIStream;` — The PortMidi stream used for MIDI input for this device
- L110 _protected member_ `int32 MIDIBufferSize;` — Size of the MIDI buffer in bytes

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MIDIDEVICE_API`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDINoteOn, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Note, int32, Velocity);` — Callback function for received MIDI Note On event
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDINoteOn, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Note, int32, Velocity);` — Callback function for received MIDI Note On event
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDINoteOff, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Note, int32, Velocity);` — Callback function for received MIDI Note Off event
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDINoteOff, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Note, int32, Velocity);` — Callback function for received MIDI Note Off event
- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMIDIPitchBend, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Pitch);` — Callback function for received MIDI Pitch Bend event
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMIDIPitchBend, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Pitch);` — Callback function for received MIDI Pitch Bend event
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDIAftertouch, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Note, int32, Amount);` — Callback function for received MIDI Aftertouch event
- L26 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDIAftertouch, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Note, int32, Amount);` — Callback function for received MIDI Aftertouch event
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDIControlChange, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Type, int32, Value);` — Callback function for received MIDI Control Change event
- L29 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDIControlChange, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Type, int32, Value);` — Callback function for received MIDI Control Change event
- L32 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDIProgramChange, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, ControlID, int32, Velocity);` — Callback function for received MIDI Program Change event
- L32 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMIDIProgramChange, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, ControlID, int32, Velocity);` — Callback function for received MIDI Program Change event
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMIDIChannelAftertouch, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Amount);` — Callback function for received MIDI Channel Aftertouch event
- L35 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMIDIChannelAftertouch, class UMIDIDeviceInputController*, MIDIDeviceController, int32, Timestamp, int32, Channel, int32, Amount);` — Callback function for received MIDI Channel Aftertouch event
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnMIDIRawEvent, class UMIDIDeviceInputController* , int32 , int32 , int32 , int32 , int32 );` — Callback function for any kind of MIDI Event
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnMIDIRawEvent, class UMIDIDeviceInputController* , int32 , int32 , int32 , int32 , int32 );` — Callback function for any kind of MIDI Event

### `Plugins/Runtime/MIDIDevice/Source/MIDIDevice/Public/MIDIDeviceManager.h` (Public)


#### struct `FFoundMIDIDevice`  
`struct FFoundMIDIDevice`  
_L15-46_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `int32 DeviceID = 0;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Manager")` — The unique ID of this MIDI device
- L25 _public member_ `FString DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Manager")` — The name of this device.  This name comes from the MIDI hardware, and might not be unique
- L29 _public member_ `bool bCanReceiveFrom = false;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Manager")` — True if the device supports sending events to us
- L33 _public member_ `bool bCanSendTo = false;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Manager")` — True if the device supports receiving events from us
- L37 _public member_ `bool bIsAlreadyInUse = false;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Manager")` — Whether the device is already in use.  You might not want to create a controller for devices that are busy.  Someone else could be using it.
- L41 _public member_ `bool bIsDefaultInputDevice = false;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Manager")` — True if this is the default MIDI device for input on this system
- L45 _public member_ `bool bIsDefaultOutputDevice = false;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Manager")` — True if this is the default MIDI device for output on this system

#### struct `FMIDIDeviceInfo`  
`struct FMIDIDeviceInfo`  
_L50-69_
- reflection: `USTRUCT(BlueprintType)`
- L56 _public member_ `int32 DeviceID = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MIDI Device Manager")` — The unique ID of this MIDI device
- L60 _public member_ `FString DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "MIDI Device Manager")` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L64 _public member_ `bool bIsAlreadyInUse = false;` — `UPROPERTY(BlueprintReadOnly, Category = "MIDI Device Manager")` — Whether the device is already in use.  You might not want to create a controller for devices that are busy.  Someone else could be using it.
- L68 _public member_ `bool bIsDefaultDevice = false;` — `UPROPERTY(BlueprintReadOnly, Category = "MIDI Device Manager")` — True if this is the default MIDI device for input on this system

#### class `UMIDIDeviceManager`  
`class UMIDIDeviceManager : public UBlueprintFunctionLibrary`  
_L72-198_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L82 _public prototype_ `static void ShutDownAllMIDIDevices();` — `UFUNCTION(BlueprintCallable, Category="MIDI Device Manager")` — Shuts down any existing midi devices to ensure no dangling streams are left, and mark any input or output controller for cleanup
- L90 _public prototype_ `static void FindMIDIDevices(TArray<FFoundMIDIDevice>& OutMIDIDevices);` — `UFUNCTION(BlueprintCallable, Category="MIDI Device Manager")` — Enumerates all of the connected MIDI devices and reports back with the IDs and names of those devices.  This operation is a little expensive so only do it once at startup, or if you think that a new device may have been connected. @param	OutMIDIDevices	A list of available MIDI devices
- L100 _public prototype_ `static void FindAllMIDIDeviceInfo(TArray<FMIDIDeviceInfo>& OutMIDIInputDevices, TArray<FMIDIDeviceInfo>& OutMIDIOutputDevices);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Manager")` — Enumerates all of the MIDI input and output devices and reports back useful infos such as IDs and names of those devices. This operation is a little expensive so only do it once at startup, or if you think that a new device may have been connected. @param 	OutMIDIInputDevices		A list of available MIDI Input devices @param 	OutMIDIOutputDevices	A list of available MIDI Output devices
- L109 _public prototype_ `static void GetMIDIInputDeviceIDByName(const FString DeviceName, int32& DeviceID);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Manager")` — Retrieves the MIDI input device ID by name. Call "Find All MIDI Device Info" beforehand to enumerate the available input devices. @param	DeviceName		The Name of the MIDI device you want to talk to. @param	DeviceID		The Device ID of the MIDI device with that name.
- L117 _public prototype_ `static void GetDefaultMIDIInputDeviceID(int32& DeviceID);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Manager")` — Retrieves the default MIDI input device ID. Call "Find All MIDI Device Info" beforehand to enumerate the available input devices. @param	DeviceID		The Device ID of the MIDI input device with that name.
- L126 _public prototype_ `static void GetMIDIOutputDeviceIDByName(const FString DeviceName, int32& DeviceID);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Manager")` — Retrieves the MIDI output device ID by name. Call "Find All MIDI Device Info" beforehand to enumerate the available output devices. @param	DeviceName		The Name of the MIDI device you want to talk to. @param	DeviceID		The Device ID of the MIDI output device associated with that name.
- L134 _public prototype_ `static void GetDefaultMIDIOutputDeviceID(int32& DeviceID);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Manager")` — Retrieves the default MIDI output device ID. Call "Find All MIDI Device Info" beforehand to enumerate the available input devices. @param	DeviceID		The Device ID of the MIDI output device with that name.
- L145 _public prototype_ `static class UMIDIDeviceController* CreateMIDIDeviceController(const int32 DeviceID, const int32 MIDIBufferSize = 1024);` — `UFUNCTION(BlueprintCallable, Category="MIDI Device Manager")` — Creates an instance of a MIDI device controller that can be used to interact with a connected MIDI device @param	DeviceID		The ID of the MIDI device you want to talk to.  Call "Find MIDI Devices" to enumerate the available devices. @param	MIDIBufferSize	How large the buffer size (in number of MIDI events) should be for incoming MIDI data.  Larger values can incur higher latency costs for incoming events, but don't set it too low or you'll miss events and your stuff will sound bad. @return	If everything goes okay, a valid MIDI device controller object will be returned.  If anything goes wrong, a null reference will be returned.
- L156 _public prototype_ `static class UMIDIDeviceInputController* CreateMIDIDeviceInputController(const int32 DeviceID, const int32 MIDIBufferSize = 1024);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Manager")` — Creates an instance of a MIDI device controller that can be used to interact with a connected MIDI device @param	DeviceID		The ID of the MIDI device you want to talk to.  Call "Find MIDI Devices" to enumerate the available devices. @param	MIDIBufferSize	How large the buffer size (in number of MIDI events) should be for incoming MIDI data.  Larger values can incur higher latency costs for incoming events, but don't set it too low or you'll miss events and your stuff will sound bad. @return	If everything goes okay, a valid MIDI device controller object will be returned.  If anything goes wrong, a null reference will be returned.
- L166 _public prototype_ `static class UMIDIDeviceOutputController* CreateMIDIDeviceOutputController(const int32 DeviceID);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Manager")` — Creates an instance of a MIDI output device controller that can be used to interact with a connected MIDI device @param	DeviceID		The ID of the MIDI device you want to talk to.  Call "Find MIDI Devices" to enumerate the available devices. @return	If everything goes okay, a valid MIDI device controller object will be returned.  If anything goes wrong, a null reference will be returned.
- L169 _public prototype_ `static void StartupMIDIDeviceManager();` — Called from FMIDIDeviceModule to startup the device manager.  Don't call this yourself.
- L172 _public prototype_ `static void ShutdownMIDIDeviceManager();` — Called from FMIDIDeviceModule to shutdown the device manager.  Don't call this yourself.
- L176 _public prototype_ `static void ProcessMIDIEvents();` — Called every frame to look for any new MIDI events that were received, and routes those events to subscribers.  Don't call this yourself. It will be called by FMIDIDeviceModule::Tick().
- L181 _private prototype_ `static void ReinitializeDeviceManager();` — Called internally to update device info.
- L184 _private prototype_ `static void FindMIDIDevicesInternal(TArray<FFoundMIDIDevice>& OutMIDIDevices);` — Implementation of FindMIDIDevices that does't reinitialize the Device Manager.
- L187 _private prototype_ `static void FindAllMIDIDeviceInfoInternal(TArray<FMIDIDeviceInfo>& OutMIDIInputDevices, TArray<FMIDIDeviceInfo>& OutMIDIOutputDevices);` — Implementation of FindMIDIDeviceInfo that does't reinitialize the Device Manager.
- L191 _private member_ `static bool bIsInitialized;` — True if everything is initialized OK
- L194 _private member_ `static TArray<FMIDIDeviceInfo> MIDIInputDevicesInfo;` — MIDI input devices info
- L197 _private member_ `static TArray<FMIDIDeviceInfo> MIDIOutputDevicesInfo;` — MIDI output devices info

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MIDIDEVICE_API`

### `Plugins/Runtime/MIDIDevice/Source/MIDIDevice/Public/MIDIDeviceOutputController.h` (Public)


#### class `UMIDIDeviceOutputController`  
`class UMIDIDeviceOutputController : public UMIDIDeviceControllerBase`  
_L16-128_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMIDIDeviceControllerBase`
- L23 _public prototype_ `virtual ~UMIDIDeviceOutputController();` — Destructor that shuts down the device if it's still in use
- L34 _public prototype_ `void SendMIDIEvent(EMIDIEventType EventType, int32 Channel, int32 data1, int32 data2);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI event raw data for an event type @param	EventType		The event type as specified in the EMIDIEventType struct @param	Channel			The MIDI channel to send @param	Data1			The first part of the MIDI data @param	Data2			The second part of the MIDI data
- L44 _public prototype_ `void SendMIDINoteOn(int32 Channel, int32 Note, int32 Velocity);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI Note On event type @param	Channel			The MIDI channel to send @param	Note			The MIDI Note value @param	Velocity		The MIDI Velocity value
- L54 _public prototype_ `void SendMIDINoteOff(int32 Channel, int32 Note, int32 Velocity);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI Note Off event type @param	Channel			The MIDI channel to send @param	Note			The MIDI Note value @param	Velocity		The MIDI Velocity value
- L63 _public prototype_ `void SendMIDIPitchBend(int32 Channel, int32 Pitch);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI Pitch Bend event type @param	Channel			The MIDI channel to send @param	Pitch			The MIDI Pitch Bend value (0-16383)
- L73 _public prototype_ `void SendMIDINoteAftertouch(int32 Channel, int32 Note, float Amount);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI Note Aftertouch event type @param	Channel			The MIDI channel to send @param	Note			The MIDI Note value @param	Amount			The MIDI aftertouch amount
- L83 _public prototype_ `void SendMIDIControlChange(int32 Channel, int32 Type, int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI Control Change event type @param	Channel			The MIDI channel to send @param	Type			The MIDI control type change @param	Value			The MIDI Value for the control change
- L92 _public prototype_ `void SendMIDIProgramChange(int32 Channel, int32 ProgramNumber);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI Program Change event type @param	Channel				The MIDI channel to send @param	ProgramNumberType	The MIDI Program Number value
- L101 _public prototype_ `void SendMIDIChannelAftertouch(int32 Channel, float Amount);` — `UFUNCTION(BlueprintCallable, Category = "MIDI Device Output Controller")` — Sends MIDI Channel Aftertouch event type @param	Channel				The MIDI channel to send @param	Amount				The MIDI Amount of aftertouch
- L105 _public prototype_ `virtual void StartupDevice(const int32 InitDeviceID, const int32 InitMIDIBufferSize, bool& bOutWasSuccessful) override;` — Called from UMIDIDeviceManager after the controller is created to get it ready to use.  Don't call this directly.
- L108 _public prototype_ `virtual void ShutdownDevice() override;` — Called during destruction to clean up this device.  Don't call this directly.
- L111 _public function_ `virtual FString GetDeviceName() const override` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L114 _public function_ `virtual int32 GetMIDIBufferSize() const override` — Size of the MIDI buffer in bytes
- L120 _protected member_ `int32 DeviceID;` — `UPROPERTY(BlueprintReadOnly, Category="MIDI Device Output Controller")` — The unique ID of this device
- L124 _protected member_ `FString DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "MIDI Device Output Controller")` — The name of this device.  This name comes from the MIDI hardware, any might not be unique
- L127 _protected member_ `void* PMMIDIStream;` — The PortMidi stream used for MIDI output for this device

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MIDIDEVICE_API`
