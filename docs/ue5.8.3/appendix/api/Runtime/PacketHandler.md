# Runtime / PacketHandler

- module root: `Source/Runtime/PacketHandlers/PacketHandler`
- headers: 4; symbols: 181
- symbol kinds: class=6, delegate=6, enum=4, enumerator=11, function=38, member=45, namespace=5, prototype=63, struct=3
- PublicDependencyModuleNames: Core, CoreUObject, NetCore, ReliabilityHandlerComponent, Sockets

### `Source/Runtime/PacketHandlers/PacketHandler/Classes/HandlerComponentFactory.h` (Public)


#### class `UHandlerComponentFactory`  
`class UHandlerComponentFactory : public UObject`  
_L17-24_
- reflection: `UCLASS(abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A UObject alternative for loading HandlerComponents without strict module dependency
- L22 _public prototype_ `virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options) PURE_VIRTUAL(UHandlerComponentFactory::CreateComponentInstance, return nullptr;);`

### `Source/Runtime/PacketHandlers/PacketHandler/Classes/PacketHandlerProfileConfig.h` (Public)


#### class `UPacketHandlerProfileConfig`  
`class UPacketHandlerProfileConfig : public UObject`  
_L14-22_
- reflection: `UCLASS(config=Engine, PerObjectConfig)`
- inherits: `UObject`
- desc: PacketHandler Configuration Profiles based on each NetDriver
- L21 _public member_ `TArray<FString> Components;` — `UPROPERTY(config)`

### `Source/Runtime/PacketHandlers/PacketHandler/Public/EncryptionComponent.h` (Public)


#### class `FEncryptionComponent`  
`class FEncryptionComponent : public HandlerComponent`  
_L13-52_
- inherits: `HandlerComponent`
- desc: IEncryptionComponentInterface
- L19 _public function_ `explicit FEncryptionComponent(FName InName) : HandlerComponent(InName)` — Constructor that forwards the name to the base HandlerComponent.
- L24 _public prototype_ `virtual void EnableEncryption() = 0;` — Enable encryption. Future packets that are processed by this component will be encrypted. By default, encryption is disabled.
- L29 _public prototype_ `virtual void DisableEncryption() = 0;` — Disable encryption. Future packets that are processed by this component will not be encrypted.
- L34 _public prototype_ `virtual bool IsEncryptionEnabled() const = 0;` — Returns true if encryption is currently enabled.
- L41 _public function_ `virtual void SetEncryptionKey(TArrayView<const uint8> Key)` — `UE_DEPRECATED(4.24, "Use SetEncryptionData instead")` — Sets the encryption key to be used by this component. The key must be the correct size for the encryption algorithm that the component implements. This should be called before EnableEncryption.
- L51 _public prototype_ `virtual void SetEncryptionData(const FEncryptionData& EncryptionData) = 0;` — Sets the encryption data to be used by this component. This should be called before EnableEncryption.

### `Source/Runtime/PacketHandlers/PacketHandler/Public/PacketHandler.h` (Public)


#### enum `UE::Handler::State`  
`enum class State : uint8`  
_L90-95_
- desc: State of PacketHandler
- L92 _public enumerator_ `Uninitialized` — PacketHandler is uninitialized
- L93 _public enumerator_ `InitializingComponents` — PacketHandler is initializing HandlerComponents
- L94 _public enumerator_ `Initialized` — PacketHandler and all HandlerComponents (if any) are initialized

#### enum `UE::Handler::Mode`  
`enum class Mode : uint8`  
_L100-104_
- desc: Mode of Packet Handler
- L102 _public enumerator_ `Client` — Clientside PacketHandler
- L103 _public enumerator_ `Server` — Serverside PacketHandler

#### enum `UE::Handler::Component::State`  
`enum class State : uint8`  
_L111-117_
- desc: HandlerComponent State
- L113 _public enumerator_ `UnInitialized` — HandlerComponent not yet initialized
- L114 _public enumerator_ `InitializedOnLocal` — Initialized on local instance
- L115 _public enumerator_ `InitializeOnRemote` — Initialized on remote instance, not on local instance
- L116 _public enumerator_ `Initialized` — Initialized on both local and remote instances

#### struct `ProcessedPacket`  
`struct ProcessedPacket`  
_L125-153_
- desc: The result of calling Incoming and Outgoing in the PacketHandler
- L128 _public member_ `uint8* Data;` — Pointer to the returned packet data
- L131 _public member_ `int32 CountBits;` — Size of the returned packet data in bits
- L134 _public member_ `bool bError;` — Whether or not there was an error processing the packet
- L137 _public function_ `ProcessedPacket() : Data() , CountBits(0) , bError(false)`
- L147 _public function_ `ProcessedPacket(uint8* InData, int32 InCountBits, bool bInError=false) : Data(InData) , CountBits(InCountBits) , bError(bInError)` — Base constructor

#### struct `BufferedPacket`  
`struct BufferedPacket`  
_L158-227_
- desc: PacketHandler will buffer packets, this struct is used to buffer such packets while handler components are initialized
- L161 _public member_ `uint8* Data;` — Buffered packet data
- L164 _public member_ `uint32 CountBits;` — Size of buffered packet in bits
- L167 _public member_ `FOutPacketTraits Traits;` — Traits applied to the packet, if applicable
- L170 _public member_ `double ResendTime;` — Used by ReliabilityHandlerComponent, to mark a packet for resending
- L173 _public member_ `uint32 Id;` — Used by ReliabilityHandlerComponent, to track packet id's
- L176 _public member_ `TSharedPtr<const FInternetAddr> Address;` — For connectionless packets, the address to send to
- L179 _public member_ `HandlerComponent* FromComponent;` — If buffering a packet through 'SendHandlerPacket', track the originating component
- L185 _private function_ `BufferedPacket() : Data(nullptr) , CountBits(0) , Traits() , ResendTime(0.0) , Id(0) , Address(nullptr) , FromComponent(nullptr)` — Base constructor
- L197 _public function_ `BufferedPacket(uint8* InCopyData, uint32 InCountBits, FOutPacketTraits& InTraits, double InResendTime=0.0, uint32 InId=0) : CountBits(InCountBits) , Traits(InTraits) , ResendTime(InResendTime) , Id(InId) , Address(nullptr) , FromComponent(nullptr)`
- L211 _public function_ `BufferedPacket(TSharedPtr<const FInternetAddr> InAddress, uint8* InCopyData, uint32 InCountBits, FOutPacketTraits& InTraits, double InResendTime=0.0, uint32 InId=0) : BufferedPacket(InCopyData, InCountBits, InTraits, InResendTime, InId)`
- L220 _public prototype_ `~BufferedPacket();` — Base destructor
- L222 _public function_ `void CountBytes(FArchive& Ar) const`

#### struct `FIncomingPacketRef`  
`struct FIncomingPacketRef`  
_L232-242_
- desc: Parameters for HandlerComponent Incoming/IncomingConnectionless functions
- L235 _public member_ `FBitReader& Packet;` — Incoming packet data being processed
- L238 _public member_ `const TSharedPtr<const FInternetAddr>& Address;` — For IncomingConnectionless, the address of the received packet
- L241 _public member_ `FInPacketTraits& Traits;` — Metadata and flags for the received packet, indicating what it contains and how to process it

#### enum `EIncomingResult`  
`enum class EIncomingResult : uint8`  
_L246-250_
- desc: Result for PacketHandler.Incoming
- L248 _public enumerator_ `Success`
- L249 _public enumerator_ `Error`

#### class `PacketHandler`  
`class PacketHandler`  
_L255-734_
- desc: This class maintains an array of all PacketHandler Components and forwards incoming and outgoing packets the each component
- L263 _public prototype_ `PacketHandler(FDDoSDetection* InDDoS=nullptr);` — Base constructor @param InDDoS			Reference to the owning net drivers DDoS detection handler
- L275 _public prototype_ `void Initialize(UE::Handler::Mode Mode, uint32 InMaxPacketBits, bool bConnectionlessOnly=false, TSharedPtr<class IAnalyticsProvider> InProvider=nullptr, FDDoSDetection* InDDoS=nullptr, FName InDriverProfile=NAME_None);` — Handles initialization of manager @param Mode					The mode the manager should be initialized in @param InMaxPacketBits		The maximum supported packet size @param bConnectionlessOnly	Whether or not this is a connectionless-only manager (ignores .ini components) @param InProvider			The analytics provider @param InDDoS				Reference to the owning net drivers DDoS detection handler @param InDriverProfile		The PacketHandler configuration profile to use
- L284 _public prototype_ `void InitializeDelegates(FPacketHandlerLowLevelSendTraits InLowLevelSendDel, FPacketHandlerNotifyAddHandler InAddHandlerDel=FPacketHandlerNotifyAddHandler());` — Used for external initialization of delegates @param InLowLevelSendDel		The delegate the PacketHandler should use for triggering packet sends @param InAddHandlerDel		Callback for notifying of new HandlerComponent's
- L292 _public prototype_ `void InitFaultRecovery(UE::Net::FNetConnectionFaultRecoveryBase* InFaultRecovery);` — Initializes a reference to the NetConnection fault recovery interface (does not require Engine dependency) @param InFaultRecovery	A reference to the fault recovery interface
- L301 _public prototype_ `void NotifyAnalyticsProvider(TSharedPtr<IAnalyticsProvider> InProvider, TSharedPtr<FNetAnalyticsAggregator> InAggregator);` — Notification that the NetDriver analytics provider has been updated (NOT called on first initialization) NOTE: Can also mean disabled, e.g. during hotfix @param InProvider		The analytics provider @param InAggregator		The net analytics aggregator
- L306 _public prototype_ `void InitializeComponents();` — Triggers initialization of HandlerComponents.
- L312 _public prototype_ `void BeginHandshaking(FPacketHandlerHandshakeComplete InHandshakeDel=FPacketHandlerHandshakeComplete());` — Triggered by the higher level netcode, to begin any required HandlerComponent handshakes
- L315 _public prototype_ `void Tick(float DeltaTime);`
- L323 _public prototype_ `void AddHandler(TSharedPtr<HandlerComponent>& NewHandler, bool bDeferInitialize=false);` — Adds a HandlerComponent to the pipeline, prior to initialization (none can be added after initialization) @param NewHandler		The HandlerComponent to add @param bDeferInitialize	Whether or not to defer triggering Initialize (for batch-adds - code calling this, triggers it instead)
- L331 _public prototype_ `TSharedPtr<HandlerComponent> AddHandler(const FString& ComponentStr, bool bDeferInitialize=false);` — As above, but initializes from a string specifying the component module, and (optionally) additional options @param ComponentStr		The handler component to load @param bDeferInitialize	Whether or not to defer triggering Initialize (for batch-adds - code calling this, triggers it instead)
- L350 _public prototype_ `void IncomingHigh(FBitReader& Reader);` — @todo #JohnB: Work in progress, don't use yet. Processes incoming packets at the UNetConnection level, after uncapping the packet into an FBitReader. Use this for simple data additions to packets, and for maximum compatibility with other HandlerComponent's. @param Reader	The FBitReader for the incoming packet
- L361 _public prototype_ `void OutgoingHigh(FBitWriter& Writer);` — @todo #JohnB: Work in progress, don't use yet. Processes outgoing packets at the UNetConnection level, after game data is written, and just before the packet is capped. Use this for simple data additions to packets, and for maximum compatibility with other HandlerComponent's. @param Writer	The FBitWriter for the outgoing packet
- L365 _public function_ `inline const ProcessedPacket Incoming(uint8* Packet, int32 CountBytes)` — `UE_DEPRECATED(4.26, "Incoming now uses FReceivedPacketView.")` — @todo: Don't deprecate, until after the NetDriver refactor
- L382 _public function_ `inline EIncomingResult Incoming(FReceivedPacketView& PacketView)` — Processes incoming packets at the PacketHandler level, before any UNetConnection processing takes place on the packet. Use this for more complex changes to packets, such as compression/encryption, but be aware that compatibility problems with other HandlerComponent's are more likely. @param PacketView	View of the packet being processed - PacketView.Data should be used to return the result @return				Returns Success/Failure
- L398 _public function_ `inline const ProcessedPacket Outgoing(uint8* Packet, int32 CountBits, FOutPacketTraits& Traits)` — Processes outgoing packets at the PacketHandler level, after all UNetConnection processing. Use this for more complex changes to packets, such as compression/encryption, but be aware that compatibility problems with other HandlerComponent's are more likely. @param Packet		The packet data to be processed @param CountBits		The size of the packet data in bits @param Traits		Traits for the packet, passed down from the NetConnection @return				Returns the final packet
- L407 _public function_ `inline const ProcessedPacket IncomingConnectionless(const TSharedPtr<const FInternetAddr>& Address, uint8* Packet, int32 CountBytes)` — `UE_DEPRECATED(4.26, "IncomingConnectionless now uses FReceivedPacketView.")` — @todo: Don't deprecate, until after the NetDriver refactor
- L422 _public function_ `inline EIncomingResult IncomingConnectionless(FReceivedPacketView& PacketView)` — Processes incoming packets without a UNetConnection, in the same manner as 'Incoming' above IMPORTANT: Net drivers triggering this, should call 'UNetDriver::FlushHandler' shortly afterwards, to minimize packet buffering NOTE: Connectionless packets are unreliable. @param PacketView	View of the packet being processed - PacketView.Data should be used to return the result @return				Returns Success/Failure
- L439 _public function_ `inline const ProcessedPacket OutgoingConnectionless(const TSharedPtr<const FInternetAddr>& Address, uint8* Packet, int32 CountBits, FOutPacketTraits& Traits)` — Processes outgoing packets without a UNetConnection, in the same manner as 'Outgoing' above NOTE: Connectionless packets are unreliable. @param Address		The address the packet is being sent to @param Packet		The packet data to be processed @param CountBits		The size of the packet data in bits @param Traits		Traits for the packet, if applicable @return				Returns the final packet
- L445 _public prototype_ `TSharedPtr<FEncryptionComponent> GetEncryptionComponent();` — Returns a pointer to the component set as the encryption handler, if any.
- L448 _public prototype_ `TSharedPtr<HandlerComponent> GetComponentByName(FName ComponentName) const;` — Returns a pointer to the first component in the HandlerComponents array with the specified name.
- L450 _public prototype_ `void CountBytes(FArchive& Ar) const;`
- L454 _protected function_ `const ProcessedPacket Incoming_Internal(uint8* Packet, int32 CountBytes, bool bConnectionless, const TSharedPtr<const FInternetAddr>& Address)` — `UE_DEPRECATED(4.26, "Incoming_Internal now uses FReceivedPacketView")`
- L480 _protected prototype_ `EIncomingResult Incoming_Internal(FReceivedPacketView& PacketView);` — Internal handling for Incoming/IncomingConnectionless @param PacketView	View of the packet being processed - PacketView.Data should be used to return the result @return				Returns Success/Failure
- L492 _protected prototype_ `const ProcessedPacket Outgoing_Internal(uint8* Packet, int32 CountBits, FOutPacketTraits& Traits, bool bConnectionless, const TSharedPtr<const FInternetAddr>& Address);` — Internal handling for Outgoing/OutgoingConnectionless @param Packet			The packet data to be processed @param CountBits			The size of the packet data in bits @param Traits			Traits for the packet, passed down from the NetConnection, if applicable @param bConnectionless	Whether or not this should be sent as a connectionless packet @param Address			The address the packet is being sent to @return					Returns the final packet
- L505 _public prototype_ `void SendHandlerPacket(HandlerComponent* InComponent, FBitWriter& Writer, FOutPacketTraits& Traits);` — Send a packet originating from a HandlerComponent - will process through the HandlerComponents chain, starting after the triggering component. NOTE: Requires that InitializeDelegates is called, with a valid LowLevelSend delegate. @param Component		The HandlerComponent sending the packet @param Writer		The packet being sent @param Traits		The traits applied to the packet, if applicable
- L511 _public prototype_ `void HandlerComponentInitialized(HandlerComponent* InComponent);` — Triggered when a child HandlerComponent has been initialized
- L518 _public function_ `inline void QueuePacketForRawSending(BufferedPacket* PacketToQueue)` — Queue's a packet to be sent when the handler is ticked (as a raw packet, since it's already been processed) @param PacketToQueue		The packet to be queued
- L528 _public function_ `inline void QueueHandlerPacketForSending(BufferedPacket* PacketToQueue)` — Queue's a packet to be sent through 'SendHandlerPacket' @param PacketToQueue		The packet to be queued
- L539 _public prototype_ `static bool DoesAnyProfileHaveComponent(const FString& InComponentName);` — Searches the PacketHandler profile configurations to find if a component is listed. @param InComponentName	The PacketHandler Component to search for @return if there is a profile that has the component included.
- L548 _public prototype_ `static bool DoesProfileHaveComponent(const FName InNetDriverName, const FString& InComponentName);` — Searches the PacketHandler profile configuration for the given netdriver to find if a component is listed. @param InNetDriverName	The name of the netdriver to search configuration for @param InComponentName	The component to search for @return if the component is listed in the profile configuration.
- L555 _public prototype_ `BufferedPacket* GetQueuedPacket();` — Gets a packet from the buffered packet queue for sending @return		The packet to be sent, or nullptr if none are to be sent
- L562 _public prototype_ `BufferedPacket* GetQueuedRawPacket();` — Gets a packet from the buffered packet queue for sending (as a raw packet) @return		The packet to be sent, or nullptr if none are to be sent
- L569 _public prototype_ `BufferedPacket* GetQueuedConnectionlessPacket();` — Gets a packet from the buffered connectionless packet queue for sending @return		The packet to be sent, or nullptr if none are to be sent
- L576 _public prototype_ `int32 GetTotalReservedPacketBits();` — Gets the combined reserved packet/protocol bits from all handlers, for reserving space in the parent connections packets @return	The combined reserved packet/protocol bits
- L581 _public prototype_ `bool CanRunHandlerComponentsOnParallelOutgoingConnections();` — Whether or not all the HandlerComponents can support parallel Outgoing Connections
- L586 _public prototype_ `void LogHandlerComponentList();` — Output names of HandlerComponents to PacketHandlerLog
- L594 _public function_ `inline void SetRawSend(bool bInEnabled)` — Sets whether or not outgoing packets should bypass this handler - used when raw packet sends are necessary (such as for the stateless handshake) @param bInEnabled	Whether or not raw sends are enabled
- L602 _public function_ `inline bool GetRawSend()` — Whether or not raw packet sends are enabled
- L610 _public function_ `inline bool IsFullyInitialized()` — Whether or not the packet handler is fully initialized, post-handshake etc.
- L616 _public function_ `FDDoSDetection* GetDDoS() const` — Returns a pointer to the DDoS detection handler
- L619 _public function_ `TSharedPtr<IAnalyticsProvider> GetProvider() const` — Returns the analytics provider
- L622 _public function_ `TSharedPtr<FNetAnalyticsAggregator> GetAggregator() const` — Returns the analytics aggregator
- L631 _private prototype_ `void SetState(UE::Handler::State InState);` — Set state of handler @param InState	The new state for the handler
- L636 _private prototype_ `void UpdateInitialState();` — Called when net send/receive functions are triggered, when the handler is still uninitialized - to set a valid initial state
- L641 _private prototype_ `void HandlerInitialized();` — Called when handler is finished initializing
- L648 _private prototype_ `void ReplaceIncomingPacket(FBitReader& ReplacementPacket);` — Replaces IncomingPacket with all unread data from ReplacementPacket @param ReplacementPacket		The packet whose unread data should replace IncomingPacket
- L655 _private prototype_ `void RealignPacket(FBitReader& Packet);` — Takes a Packet whose position is not at bit 0, and shifts/aligns all packet data to place the current bit at position 0 @param Packet	The packet to realign
- L660 _public member_ `UE::Handler::Mode Mode;` — Mode of the handler, Client or Server
- L663 _public prototype_ `static FPacketHandlerAddComponentByNameDelegate& GetAddComponentByNameDelegate();` — `UE_DEPRECATED(5.6, "PacketHandler AddComponent delegates are deprecated, use [PacketHandlerComponents] section in .ini file")`
- L665 _public prototype_ `static FPacketHandlerAddComponentDelegate& GetAddComponentDelegate();` — `UE_DEPRECATED(5.6, "PacketHandler AddComponent delegates are deprecated, use [PacketHandlerComponents] section in .ini file")`
- L670 _private member_ `UE::Handler::State State;` — State of the handler
- L673 _private member_ `uint8 bRawSend:1;` — Whether or not outgoing packets bypass the handler
- L676 _private member_ `uint8 bBeganHandshaking:1;` — Whether or not component handshaking has begun
- L679 _private member_ `uint8 bConnectionlessHandler:1;` — Whether or not this PacketHandler handles connectionless (i.e. non-UNetConnection) data
- L682 _private member_ `uint32 MaxPacketBits;` — The maximum supported packet size (reflects UNetConnection::MaxPacket)
- L685 _private member_ `FDDoSDetection* DDoS;` — Mirroring UNetDriver.DDoS
- L688 _private member_ `FPacketHandlerLowLevelSendTraits LowLevelSendDel;` — Delegate used for triggering PacketHandler/HandlerComponent-sourced sends
- L691 _private member_ `FPacketHandlerHandshakeComplete HandshakeCompleteDel;` — Delegate used for notifying that handshaking has completed
- L694 _private member_ `FPacketHandlerNotifyAddHandler AddHandlerDel;` — Delegate used for notifying that a new HandlerComponent has been added
- L697 _private member_ `FBitWriter OutgoingPacket;` — Used for packing outgoing packets
- L700 _private member_ `FBitReader IncomingPacket;` — Used for unpacking incoming packets
- L703 _private member_ `TArray<TSharedPtr<HandlerComponent>> HandlerComponents;` — The HandlerComponent pipeline, for processing incoming/outgoing packets
- L706 _private member_ `TSharedPtr<FEncryptionComponent> EncryptionComponent;` — A direct pointer to the component configured as the encryption component. Will also be present in the HandlerComponents array.
- L709 _private member_ `TArray<BufferedPacket*> BufferedPackets;` — Packets that are buffered while HandlerComponents are being initialized
- L712 _private member_ `TQueue<BufferedPacket*> QueuedPackets;` — Packets that are queued to be sent when handler is ticked
- L715 _private member_ `TQueue<BufferedPacket*> QueuedRawPackets;` — Packets that are queued to be sent when handler is ticked (as a raw packet)
- L718 _private member_ `TQueue<BufferedPacket*> QueuedHandlerPackets;` — Packets that are queued to be sent through 'SendHandlerPacket'
- L721 _private member_ `TArray<BufferedPacket*> BufferedConnectionlessPackets;` — Packets that are buffered while HandlerComponents are being initialized
- L724 _private member_ `TQueue<BufferedPacket*> QueuedConnectionlessPackets;` — Packets that are queued to be sent when handler is ticked
- L727 _private member_ `TSharedPtr<ReliabilityHandlerComponent> ReliabilityComponent;` — Reliability Handler Component
- L730 _private member_ `TSharedPtr<IAnalyticsProvider> Provider;` — The analytics provider
- L733 _private member_ `TSharedPtr<FNetAnalyticsAggregator> Aggregator;` — The NetDriver level aggregator for the analytics provider

#### class `HandlerComponent`  
`class HandlerComponent`  
_L739-956_
- desc: This class appends or modifies incoming and outgoing packets on a connection
- L747 _public prototype_ `HandlerComponent();` — Base constructor
- L752 _public prototype_ `explicit HandlerComponent(FName InName);` — Constructor that accepts a name
- L757 _public prototype_ `virtual ~HandlerComponent();` — Base destructor
- L762 _public prototype_ `virtual bool IsActive() const;` — Returns whether this handler is currently active
- L767 _public prototype_ `virtual bool IsValid() const = 0;` — Return whether this handler is valid
- L772 _public prototype_ `bool IsInitialized() const;` — Returns whether this handler is initialized
- L777 _public function_ `bool RequiresHandshake() const` — Returns whether this handler perform a network handshake during initialization
- L785 _public function_ `bool RequiresReliability() const` — Returns whether this handler perform a network handshake during initialization
- L792 _public function_ `virtual void Incoming(FBitReader& Packet)` — `UE_DEPRECATED(5.0, "Use the version of 'HandlerComponent::Incoming' which takes 'FIncomingPacketRef' instead")` — Delay deprecation for initial checkin
- L801 _public function_ `virtual void Incoming(FIncomingPacketRef PacketRef)` — Handles incoming packets @param PacketRef		Reference of the packet being processed
- L815 _public function_ `virtual void Outgoing(FBitWriter& Packet, FOutPacketTraits& Traits)` — Handles any outgoing packets @param Packet	The packet to be handled @param Traits	Traits for the packet, passed down through the packet pipeline (likely from the NetConnection)
- L824 _public function_ `virtual void IncomingConnectionless(FIncomingPacketRef PacketRef)` — Handles incoming packets not associated with a UNetConnection @param PacketRef		Reference of the packet being processed
- L835 _public function_ `virtual void OutgoingConnectionless(const TSharedPtr<const FInternetAddr>& Address, FBitWriter& Packet, FOutPacketTraits& Traits)` — Handles any outgoing packets not associated with a UNetConnection @param Address	The address the packet is being sent to @param Packet	The packet to be handled @param Traits	Traits for the packet, passed down through the packet pipeline (if applicable)
- L846 _public function_ `virtual bool CanReadUnaligned() const` — Whether or not the Incoming/IncomingConnectionless implementations, support reading Packets that aren't aligned at bit position 0 (i.e. whether or not this handler supports bit-level, rather than byte-level, reads) @return	Whether or not the above is supported
- L857 _public function_ `virtual bool SupportsParallelConnectionOutgoing() const` — Whether or not this HandlerComponent supports running its Outgoing logic on multiple separate connections simultaneously. Any accesses on a per-connection basis are safe, but writing to Global/NetDriver properties are not @return	Whether or not the above is supported
- L865 _public prototype_ `virtual void Initialize() = 0;` — Initialization functionality should be placed here
- L872 _public function_ `virtual void InitFaultRecovery(UE::Net::FNetConnectionFaultRecoveryBase* InFaultRecovery)` — Initializes a reference to the NetConnection fault recovery interface (does not require Engine dependency) @param InFaultRecovery	A reference to the fault recovery interface
- L879 _public function_ `virtual void NotifyHandshakeBegin()` — Notification to this component that it is ready to begin handshaking
- L886 _public function_ `virtual void Tick(float DeltaTime)` — Tick functionality should be placed here
- L893 _public prototype_ `virtual void SetActive(bool Active);` — Sets whether this handler is currently active @param Active	Whether or not the handled should be active
- L903 _public prototype_ `virtual int32 GetReservedPacketBits() const = 0;` — Returns the amount of reserved packet/protocol bits expected from this component. IMPORTANT: This MUST be accurate, and should represent the worst-case number of reserved bits expected from the component. If this is inaccurate, packets will randomly fail to send, in rare cases which are extremely hard to trace. @return	The worst-case reserved packet bits for the component
- L906 _public function_ `FName GetName() const` — Returns the name of this component.
- L912 _public function_ `virtual void NotifyAnalyticsProvider()` — Notification that the analytics provider has been updated NOTE: Can also mean disabled, e.g. during hotfix
- L914 _public prototype_ `virtual void CountBytes(FArchive& Ar) const;`
- L922 _protected prototype_ `void SetState(UE::Handler::Component::State State);` — Sets the state of the handler @param State		The new state for the handler
- L927 _protected prototype_ `void Initialized();` — Should be called when the handler is fully initialized on both remote and local
- L932 _public member_ `PacketHandler* Handler;` — The manager of the handler, set in initialization
- L936 _protected member_ `UE::Handler::Component::State State;` — The state of this handler
- L939 _protected member_ `uint32 MaxOutgoingBits;` — Maximum number of Outgoing packet bits supported (automatically calculated to factor in other HandlerComponent reserved bits)
- L942 _protected member_ `bool bRequiresHandshake;` — Whether this handler has to perform a network handshake during initialization (requires waiting on other HandlerComponent's)
- L945 _protected member_ `bool bRequiresReliability;` — Whether this handler depends upon the ReliabilityHandlerComponent being enabled
- L949 _private member_ `bool bActive;` — Whether this handler is active, which dictates whether it will receive incoming and outgoing packets.
- L952 _private member_ `bool bInitialized;` — Whether this handler is fully initialized on both remote and local
- L955 _private member_ `FName Name;` — The name of this component

#### class `FPacketHandlerComponentModuleInterface`  
`class FPacketHandlerComponentModuleInterface : public IModuleInterface`  
_L961-973_
- inherits: `IModuleInterface`
- desc: PacketHandler Module Interface
- L965 _public function_ `virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options)` — Creates an instance of this component
- L970 _public prototype_ `virtual void StartupModule() override;`
- L972 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(PacketHandlerLog, Log, All);`
- L38 _namespace_ `namespace UE`
- L40 _namespace_ `namespace Net` (scope `UE`)
- L47 _prototype_ `void SetDiscardTimeguardMeasurement(const bool bShouldDiscard);` (scope `UE::Net`) — bShouldDiscard=true will prevent the log warning from firing when calling NET_LIGHTWEIGHT_TIME_GUARD_END If called in a parallel thread, this will only apply to the current thread of execution
- L48 _prototype_ `bool GetDiscardTimeguardMeasurement();` (scope `UE::Net`)
- L58 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPacketHandlerLowLevelSendTraits, void* , int32 , FOutPacketTraits& );` — Delegate for allowing access to LowLevelSend, without a dependency upon Engine
- L58 _prototype_ `DECLARE_DELEGATE_ThreeParams(FPacketHandlerLowLevelSendTraits, void* , int32 , FOutPacketTraits& );` — Delegate for allowing access to LowLevelSend, without a dependency upon Engine
- L60 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPacketHandlerLowLevelSend, void* , int32 , int32 );`
- L60 _prototype_ `DECLARE_DELEGATE_ThreeParams(FPacketHandlerLowLevelSend, void* , int32 , int32 );`
- L63 _delegate_ `DECLARE_DELEGATE_OneParam(FPacketHandlerAddComponentByNameDelegate, TArray<FString>& );` — Delegate for allowing adding of packet handlers without defining them in an ini file
- L63 _prototype_ `DECLARE_DELEGATE_OneParam(FPacketHandlerAddComponentByNameDelegate, TArray<FString>& );` — Delegate for allowing adding of packet handlers without defining them in an ini file
- L64 _delegate_ `DECLARE_DELEGATE_OneParam(FPacketHandlerAddComponentDelegate, TArray<TSharedPtr<HandlerComponent>>& );`
- L64 _prototype_ `DECLARE_DELEGATE_OneParam(FPacketHandlerAddComponentDelegate, TArray<TSharedPtr<HandlerComponent>>& );`
- L71 _delegate_ `DECLARE_DELEGATE_OneParam(FPacketHandlerNotifyAddHandler, TSharedPtr<HandlerComponent>& );` — Callback for notifying that a new HandlerComponent was added (to e.g. perform additional initialization) @param NewHandler	The newly added HandlerComponent
- L71 _prototype_ `DECLARE_DELEGATE_OneParam(FPacketHandlerNotifyAddHandler, TSharedPtr<HandlerComponent>& );` — Callback for notifying that a new HandlerComponent was added (to e.g. perform additional initialization) @param NewHandler	The newly added HandlerComponent
- L76 _delegate_ `DECLARE_DELEGATE(FPacketHandlerHandshakeComplete);` — Callback for notifying higher-level code that handshaking has completed, and that packets are now ready to send without buffering
- L76 _prototype_ `DECLARE_DELEGATE(FPacketHandlerHandshakeComplete);` — Callback for notifying higher-level code that handshaking has completed, and that packets are now ready to send without buffering
- L83 _namespace_ `namespace UE`
- L85 _namespace_ `namespace Handler` (scope `UE`)
- L106 _namespace_ `namespace Component` (scope `UE::Handler`)
