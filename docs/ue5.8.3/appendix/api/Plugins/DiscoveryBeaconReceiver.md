# Plugins / DiscoveryBeaconReceiver

- module root: `Plugins/DiscoveryBeaconReceiver/Source/DiscoveryBeaconReceiver`
- headers: 2; symbols: 23
- symbol kinds: class=2, member=7, prototype=13, typedef=1
- PrivateDependencyModuleNames: Engine, Networking, Sockets
- PublicDependencyModuleNames: Core, CoreUObject, Serialization

### `Plugins/DiscoveryBeaconReceiver/Source/DiscoveryBeaconReceiver/Public/DiscoveryBeaconReceiver.h` (Public)


#### class `FDiscoveryBeaconReceiver`  
`class FDiscoveryBeaconReceiver : public FRunnable`  
_L20-101_
- inherits: `FRunnable`
- desc: Receives beacon messages on a multicast endpoint and replies with information to connect to the engine. This allows remote apps to detect compatible Unreal instances on the local network.
- L30 _public prototype_ `FDiscoveryBeaconReceiver(const FString& InDescription, const TArray<uint8>& InProtocolIdentifier, uint8 InProtocolVersion);` — Creates and initializes a new beacon receiver. @param InDescription A short name for this beacon for debugging purposes. @param InProtocolIdentifier A series of bytes that uniquely identify messages intended for this beacon receiver. @param InProtocolVersion The protocol version number with which to reply to beacon messages.
- L33 _public prototype_ `virtual ~FDiscoveryBeaconReceiver() = default;` — Destroy the beacon receiver.
- L39 _public prototype_ `virtual void Startup();` — Open a socket and start a thread listening for beacon messages. If called multiple times without shutting down, all but the first call will be ignored.
- L42 _public prototype_ `virtual void Shutdown();` — Close the socket and kill the listening thread.
- L50 _protected prototype_ `virtual bool GetDiscoveryAddress(FIPv4Address& OutAddress) const = 0;` — Get the IP address on which to listen for beacon messages. @param OutAddress The IP address. @return false if no valid address could be found, else true.
- L56 _protected prototype_ `virtual int32 GetDiscoveryPort() const = 0;` — Get the port on which to listen for beacon messages. @param OutAddress The port, or a negative value if no valid port could be found.
- L65 _protected prototype_ `virtual bool MakeBeaconResponse(uint8 BeaconProtocolVersion, FArrayReader& InMessageData, FArrayWriter& OutResponseData) const = 0;` — Make a response to a beacon message. @param BeaconProtocolVersion The protocol version reported by the beacon message. @param InMessageData Array reader containing additional data after the standard beacon protocol version and identifier. All data in this reader must be consumed or the message will be ignored. @param OutResponseData
- L69 _private prototype_ `virtual bool Init() override;`
- L70 _private prototype_ `virtual uint32 Run() override;`
- L71 _private prototype_ `virtual void Stop() override;`
- L75 _private prototype_ `void ReceiveBeaconMessages();` — Called regularly to receive beacon messages.
- L78 _private prototype_ `void HandleBeaconMessage(FArrayReader& MessageData, TSharedRef<FInternetAddr> Source);` — Handle a message received on the beacon endpoint.
- L82 _private member_ `FString Description;` — A short name for this beacon for debugging purposes.
- L85 _private member_ `TArray<uint8> ProtocolIdentifier;` — A series of bytes that uniquely identify messages intended for this beacon receiver.
- L88 _private member_ `uint8 ProtocolVersion;` — The protocol version number with which to reply to beacon messages.
- L91 _private member_ `FGuid Guid;` — Identifier for this engine instance. Sent in responses to differentiate engine instances even if they're on the same machine.
- L94 _private member_ `FSocket* Socket = nullptr;` — Socket used to listen for and reply to beacon messages.
- L97 _private member_ `TAtomic<bool> bIsRunning = false;` — Flag indicating that the beacon thread should be running.
- L100 _private member_ `TUniquePtr<FRunnableThread> Thread = nullptr;` — The thread to receive beacon messages on.

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef FBufferArchive FArrayWriter;`

### `Plugins/DiscoveryBeaconReceiver/Source/DiscoveryBeaconReceiver/Public/DiscoveryBeaconReceiverModule.h` (Public)


#### class `FDiscoveryBeaconReceiverModule`  
`class FDiscoveryBeaconReceiverModule : public IModuleInterface`  
_L9-11_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDiscoveryBeaconReceiver, Log, All);`
