# Plugins / AESHandlerComponent

- module root: `Plugins/Runtime/PacketHandlers/AESHandlerComponent/Source`
- headers: 1; symbols: 20
- symbol kinds: class=2, member=6, prototype=12
- PublicDependencyModuleNames: Core, PacketHandler, PlatformCrypto, PlatformCryptoContext

### `Plugins/Runtime/PacketHandlers/AESHandlerComponent/Source/Public/AESHandlerComponent.h` (Public)


#### class `FAESHandlerComponent`  
`class UE_DEPRECATED(5.1, "No longer supported, please use FAESGCMHandlerComponent instead.") FAESHandlerComponent : public FEncryptionComponent`  
_L13-57_
- inherits: `FEncryptionComponent`
- desc: AES256 ECB block encryption component.
- L21 _public prototype_ `FAESHandlerComponent();` — Default constructor that leaves the Key empty, and encryption disabled. You must set the key before enabling encryption, or before receiving encrypted packets, or those operations will fail.
- L24 _public member_ `static const int32 KeySizeInBytes = 32;` — This handler uses AES256, which has 32-byte keys.
- L27 _public member_ `static const int32 BlockSizeInBytes = 16;` — This handler uses AES256, which has 32-byte keys.
- L30 _public prototype_ `virtual void SetEncryptionData(const FEncryptionData& EncryptionData) override;` — Replace the key used for encryption with NewKey if NewKey is exactly KeySizeInBytes long.
- L33 _public prototype_ `virtual void EnableEncryption() override;` — After calling this, future outgoing packets will be encrypted (until a call to DisableEncryption).
- L36 _public prototype_ `virtual void DisableEncryption() override;` — After calling this, future outgoing packets will not be encrypted (until a call to DisableEncryption).
- L39 _public prototype_ `virtual bool IsEncryptionEnabled() const override;` — Returns true if encryption is currently enabled.
- L42 _public prototype_ `virtual void Initialize() override;` — HandlerComponent interface
- L43 _public prototype_ `virtual bool IsValid() const override;`
- L44 _public prototype_ `virtual void Incoming(FBitReader& Packet) override;`
- L45 _public prototype_ `virtual void Outgoing(FBitWriter& Packet, FOutPacketTraits& Traits) override;`
- L46 _public prototype_ `virtual int32 GetReservedPacketBits() const override;`
- L47 _public prototype_ `virtual void CountBytes(FArchive& Ar) const override;`
- L50 _private member_ `TUniquePtr<FEncryptionContext> EncryptionContext;`
- L52 _private member_ `TArray<uint8> Key;`
- L54 _private member_ `TArray<uint8> Ciphertext;`
- L56 _private member_ `bool bEncryptionEnabled;`

#### class `FAESHandlerComponentModule`  
`class UE_DEPRECATED(5.1, "No longer supported, please use FAESGCMHandlerComponentModule instead.") FAESHandlerComponentModule : public FPacketHandlerComponentModuleInterface`  
_L63-68_
- inherits: `FPacketHandlerComponentModuleInterface`
- desc: The public interface to this module.
- L67 _public prototype_ `virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options) override;` — Creates an instance of this component
