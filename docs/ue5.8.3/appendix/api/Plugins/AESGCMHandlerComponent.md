# Plugins / AESGCMHandlerComponent

- module root: `Plugins/Runtime/PacketHandlers/AESGCMHandlerComponent/Source`
- headers: 2; symbols: 45
- symbol kinds: class=3, enum=1, enumerator=7, member=12, namespace=2, prototype=20
- PublicDependencyModuleNames: Core, CoreUObject, NetCore, PacketHandler, PlatformCrypto, PlatformCryptoContext

### `Plugins/Runtime/PacketHandlers/AESGCMHandlerComponent/Source/Public/AESGCMFaultHandler.h` (Public)


#### enum `EAESGCMNetResult`  
`enum class EAESGCMNetResult : uint8`  
_L24-43_
- reflection: `UENUM()`
- desc: AESGCM net error types, for NetConnection fault handling
- L26 _public enumerator_ `Unknown`
- L27 _public enumerator_ `Success`
- L30 _public enumerator_ `AESMissingIV` — AES GCM Packet missing Initialization Vector
- L33 _public enumerator_ `AESMissingAuthTag` — AES GCM Packet missing Authentication Tag
- L36 _public enumerator_ `AESMissingPayload` — AES GCM Packet missing payload/ciphertext
- L39 _public enumerator_ `AESDecryptionFailed` — AES GCM Packet Decryption failed
- L42 _public enumerator_ `AESZeroLastByte` — AES GCM Packet had zero last byte (no termination bit)

#### class `FAESGCMFaultHandler`  
`class FAESGCMFaultHandler final : public UE::Net::FNetResultHandler`  
_L54-69_
- inherits: `UE::Net::FNetResultHandler`
- desc: AESGCM Fault Handler - implements fault handling for AESGCM net errors, tied to the main NetConnection fault recovery implementation
- L59 _private prototype_ `void InitFaultRecovery(UE::Net::FNetConnectionFaultRecoveryBase* InFaultRecovery);`
- L61 _private prototype_ `virtual UE::Net::EHandleNetResult HandleNetResult(UE::Net::FNetResult&& InResult) override;`
- L65 _private member_ `UE::Net::FNetConnectionFaultRecoveryBase* FaultRecovery = nullptr;` — The NetConnection FaultRecovery instance, which we forward fault counting to
- L68 _private member_ `int32 CounterIndex = INDEX_NONE;` — This fault handlers allocated counter index, within the NetConnection FaultRecovery instance

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)
- L45 _prototype_ `DECLARE_NETRESULT_ENUM(EAESGCMNetResult);`
- L47 _prototype_ `const TCHAR* LexToString(EAESGCMNetResult Enum);`

### `Plugins/Runtime/PacketHandlers/AESGCMHandlerComponent/Source/Public/AESGCMHandlerComponent.h` (Public)


#### class `FAESGCMHandlerComponent`  
`class FAESGCMHandlerComponent : public FEncryptionComponent`  
_L17-77_
- inherits: `FEncryptionComponent`
- desc: AES256 GCM block encryption component.
- L26 _public prototype_ `FAESGCMHandlerComponent();` — Default constructor that leaves the Key empty, and encryption disabled. You must set the key before enabling encryption, or before receiving encrypted packets, or those operations will fail.
- L29 _public member_ `static const int32 KeySizeInBytes = 32;` — This handler uses AES256, which has 32-byte keys.
- L32 _public member_ `static const int32 BlockSizeInBytes = 16;` — This handler uses AES256, which has 32-byte keys.
- L34 _public member_ `static const int32 IVSizeInBytes = 12;`
- L35 _public member_ `static const int32 AuthTagSizeInBytes = 16;`
- L38 _public prototype_ `virtual void SetEncryptionData(const FEncryptionData& EncryptionData) override;` — Replace the key used for encryption with NewKey if NewKey is exactly KeySizeInBytes long.
- L41 _public prototype_ `virtual void EnableEncryption() override;` — After calling this, future outgoing packets will be encrypted (until a call to DisableEncryption).
- L44 _public prototype_ `virtual void DisableEncryption() override;` — After calling this, future outgoing packets will not be encrypted (until a call to DisableEncryption).
- L47 _public prototype_ `virtual bool IsEncryptionEnabled() const override;` — Returns true if encryption is currently enabled.
- L50 _public prototype_ `virtual void Initialize() override;` — HandlerComponent interface
- L51 _public prototype_ `virtual void InitFaultRecovery(UE::Net::FNetConnectionFaultRecoveryBase* InFaultRecovery) override;`
- L52 _public prototype_ `virtual bool IsValid() const override;`
- L53 _public prototype_ `virtual void Incoming(FIncomingPacketRef PacketRef) override;`
- L54 _public prototype_ `virtual void Outgoing(FBitWriter& Packet, FOutPacketTraits& Traits) override;`
- L55 _public prototype_ `virtual int32 GetReservedPacketBits() const override;`
- L56 _public prototype_ `virtual void CountBytes(FArchive& Ar) const override;`
- L59 _public prototype_ `virtual bool SupportsParallelConnectionOutgoing() const override;` — Whether or not this HandlerComponent supports running its Outgoing logic on multiple separate connections simultaneously.
- L62 _private member_ `TUniquePtr<FEncryptionContext> EncryptionContext;`
- L64 _private member_ `TUniquePtr<IPlatformCryptoDecryptor> Decryptor;`
- L65 _private member_ `TUniquePtr<IPlatformCryptoEncryptor> Encryptor;`
- L68 _private member_ `TStaticArray<uint8, IVSizeInBytes> OutIV;` — IV used for encryption
- L70 _private member_ `bool bEncryptionEnabled;`
- L73 _private member_ `FAESGCMFaultHandler AESGCMFaultHandler;` — Fault handler for AESGCM-specific errors, that may trigger NetConnection Close
- L75 _private prototype_ `EPlatformCryptoResult Decrypt(TArrayView<uint8> OutPlainText, const TArrayView<const uint8> InCiphertext, const TArrayView<const uint8> IV, const TArrayView<const uint8> AuthTag);`
- L76 _private prototype_ `EPlatformCryptoResult Encrypt(TArrayView<uint8> OutCipherText, const TArrayView<const uint8> InPlaintext, const TArrayView<const uint8> IV, TArrayView<uint8> OutAuthTag);`

#### class `FAESGCMHandlerComponentModule`  
`class FAESGCMHandlerComponentModule : public FPacketHandlerComponentModuleInterface`  
_L83-88_
- inherits: `FPacketHandlerComponentModuleInterface`
- desc: The public interface to this module.
- L87 _public prototype_ `virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options) override;` — Creates an instance of this component
