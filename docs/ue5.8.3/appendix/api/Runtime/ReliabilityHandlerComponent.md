# Runtime / ReliabilityHandlerComponent

- module root: `Source/Runtime/PacketHandlers/ReliabilityHandlerComponent`
- headers: 1; symbols: 21
- symbol kinds: class=2, function=2, member=7, prototype=10
- PublicDependencyModuleNames: Core, NetCore, PacketHandler

### `Source/Runtime/PacketHandlers/ReliabilityHandlerComponent/Public/ReliabilityHandlerComponent.h` (Public)


#### class `ReliabilityHandlerComponent`  
`ReliabilityHandlerComponent : public HandlerComponent`  
_L20-84_
- reflection: `UE_DEPRECATED(5.3, "This handler is not supported. For fully-reliable data, use reliable RPCs or a separate connection with a reliable protocol.")`
- inherits: `HandlerComponent`
- L24 _public prototype_ `ReliabilityHandlerComponent();` — Initializes default data
- L26 _public prototype_ `virtual void CountBytes(FArchive& Ar) const;`
- L28 _public prototype_ `virtual void Initialize() override;`
- L30 _public prototype_ `virtual bool IsValid() const override;`
- L32 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L34 _public prototype_ `virtual void Incoming(FBitReader& Packet) override;`
- L35 _public prototype_ `virtual void Outgoing(FBitWriter& Packet, FOutPacketTraits& Traits) override;`
- L38 _public prototype_ `void QueuePacketForResending(uint8* Packet, int32 CountBits, FOutPacketTraits& Traits);` — Queues a packet for resending
- L41 _public function_ `inline void QueueHandlerPacketForResending(HandlerComponent* InComponent, uint8* Packet, int32 CountBits)` — `UE_DEPRECATED(4.21, "Use the PacketTraits version for sending packets with additional flags and options")`
- L54 _public function_ `inline void QueueHandlerPacketForResending(HandlerComponent* InComponent, uint8* Packet, int32 CountBits, FOutPacketTraits& Traits)` — Queues a packet sent through SendHandlerPacket, for resending @param InComponent	The HandlerComponent the packet originated from @param Packet		The packet to be queued @param CountBits		The number of bits in the packet
- L61 _public prototype_ `virtual int32 GetReservedPacketBits() const override;`
- L65 _protected member_ `TArray<BufferedPacket*> BufferedPackets;` — Buffered Packets in case they need to be resent
- L68 _protected member_ `uint32 LocalPacketID;` — Latest Packet ID
- L71 _protected member_ `uint32 LocalPacketIDACKED;` — Latest Packet ID that was ACKED
- L74 _protected member_ `uint32 RemotePacketID;` — Latest Remote Packet ID
- L77 _protected member_ `uint32 RemotePacketIDACKED;` — Latest Remote Packet ID that was ACKED
- L80 _protected member_ `double ResendResolutionTime;` — How long to wait before resending an UNACKED packet
- L83 _protected member_ `double LastResendTime;` — Last time we resent UNACKED packets

#### class `FReliabilityHandlerComponentModuleInterface`  
`class FReliabilityHandlerComponentModuleInterface : public FPacketHandlerComponentModuleInterface`  
_L87-91_
- inherits: `FPacketHandlerComponentModuleInterface`
- desc: Reliability Module Interface
- L90 _public prototype_ `virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options) override;`
