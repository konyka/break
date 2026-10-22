# Plugins / RemoteControlProtocolOSC

- module root: `Plugins/VirtualProduction/RemoteControlProtocolOSC/Source/RemoteControlProtocolOSC`
- headers: 2; symbols: 25
- symbol kinds: class=2, function=3, member=7, prototype=11, struct=2
- PrivateDependencyModuleNames: InputCore, Networking, OSC, RemoteControl, RemoteControlProtocol, RemoteControlProtocolWidgets, Settings
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/RemoteControlProtocolOSC/Source/RemoteControlProtocolOSC/Private/RemoteControlProtocolOSC.h` (Private)


#### struct `FRemoteControlOSCProtocolEntity`  
`struct FRemoteControlOSCProtocolEntity : public FRemoteControlProtocolEntity`  
_L17-46_
- reflection: `USTRUCT()`
- inherits: `FRemoteControlProtocolEntity`
- desc: OSC protocol entity for remote control binding
- L23 _public function_ `virtual FName GetRangePropertyName() const override`
- L28 _public member_ `FName PathName;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — OSC address in the form '/Container1/Container2/Method'
- L32 _public member_ `float RangeInputTemplate = 0.0f;` — `UPROPERTY(Transient, meta = (ClampMin = 0.0, ClampMax = 1.0))` — OSC range input property template, used for binding.
- L38 _public prototype_ `virtual bool IsSame(const FRemoteControlProtocolEntity* InOther) override;` — Checks if this entity has the same values as the Other. Used to check for duplicate inputs.
- L43 _public prototype_ `virtual void RegisterProperties() override;` — Register(s) all the widgets of this protocol entity.

#### class `FRemoteControlProtocolOSC`  
`class FRemoteControlProtocolOSC : public FRemoteControlProtocol`  
_L51-88_
- inherits: `FRemoteControlProtocol`
- desc: OSC protocol implementation for Remote Control
- L54 _public function_ `FRemoteControlProtocolOSC() : FRemoteControlProtocol(ProtocolName)`
- L59 _public prototype_ `virtual void Bind(FRemoteControlProtocolEntityPtr InRemoteControlProtocolEntityPtr) override;`
- L60 _public prototype_ `virtual void Unbind(FRemoteControlProtocolEntityPtr InRemoteControlProtocolEntityPtr) override;`
- L61 _public prototype_ `virtual void UnbindAll() override;`
- L62 _public function_ `virtual UScriptStruct* GetProtocolScriptStruct() const override`
- L66 _public prototype_ `void OSCReceivedMessageEvent(const FOSCMessage& Message, const FString& IPAddress, uint16 Port);` — Receive OSC server message handler
- L73 _public prototype_ `void ProcessAutoBinding(const FOSCAddress& InAddress);` — Process the AutoBinding to the Remote Control Entity @param InAddress	OSC address structure
- L78 _protected prototype_ `virtual void RegisterColumns() override;` — Populates protocol specific columns.
- L83 _private member_ `TMap<FName, TArray<FRemoteControlProtocolEntityWeakPtr>> Bindings;` — Map of the OSC bindings
- L87 _public member_ `static const FName ProtocolName;` — OSC protocol name

### `Plugins/VirtualProduction/RemoteControlProtocolOSC/Source/RemoteControlProtocolOSC/Private/RemoteControlProtocolOSCSettings.h` (Private)


#### struct `FRemoteControlOSCServerSettings`  
`struct FRemoteControlOSCServerSettings`  
_L17-36_
- reflection: `USTRUCT()`
- desc: OSC Remote Control server settings
- L23 _public prototype_ `void InitOSCServer();` — Initialize OSC servers from ip address and port
- L32 _public member_ `FString ServerAddress = "12` — `UPROPERTY(EditAnywhere, Category = OSC)` — OSC server IP address The format is IP_ADDRESS:PORT_NUMBER.
- L35 _public member_ `TStrongObjectPtr<UOSCServer> OSCServer;` — Running OSC server instance

#### class `URemoteControlProtocolOSCSettings`  
`class URemoteControlProtocolOSCSettings : public UObject`  
_L42-60_
- reflection: `UCLASS(Config = Engine, DefaultConfig, meta = (Keywords = "OSC"))`
- inherits: `UObject`
- desc: OSC Remote Control settings
- L48 _public prototype_ `void InitOSCServers();` — Initialize all servers from settings at OSCServers map
- L52 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L59 _public member_ `TArray<FRemoteControlOSCServerSettings> ServersSettings = { FRemoteControlOSCServerSettings() };` — `UPROPERTY(Config, EditAnywhere, Category = OSC)` — OSC server pair of server ip and server port
