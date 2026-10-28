# Plugins / DTLSHandlerComponent

- module root: `Plugins/Runtime/PacketHandlers/DTLSHandlerComponent/Source`
- headers: 5; symbols: 121
- symbol kinds: class=2, delegate=1, enum=2, enumerator=5, externvar=1, function=18, macro=3, member=25, prototype=52, struct=6, typedef=6
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, NetCore, PacketHandler
- PublicDependencyModuleNames: SSL

### `Plugins/Runtime/PacketHandlers/DTLSHandlerComponent/Source/Public/DTLSCertStore.h` (Public)


#### struct `FDTLSCertStore`  
`struct FDTLSCertStore`  
_L15-85_
- desc: Certificate store that can generate self-signed X509 certificates for DTLS
- L23 _public prototype_ `static FDTLSCertStore& Get();` — Retrieve cert store @return singleton cert store reference
- L32 _public prototype_ `TSharedPtr<FDTLSCertificate> CreateCert(const FTimespan& Lifetime);` — Create a new certificate @Param Lifetime time in seconds until expiration of certificate @return shared pointer to certificate, valid if creation succeeded
- L42 _public prototype_ `TSharedPtr<FDTLSCertificate> CreateCert(const FTimespan& Lifetime, const FString& Identifier);` — Create a new certificate and store internally @Param Lifetime time in seconds until expiration of certificate @Param Identifier name to use when storing certificate for later use @return shared pointer to certificate, valid if creation succeeded
- L51 _public prototype_ `TSharedPtr<FDTLSCertificate> GetCert(const FString& Identifier) const;` — Retrieve a certificate using unique identifier @Param Identifier unique identifier used when cert was added @return shared pointer to certificate, valid if it was found
- L60 _public prototype_ `TSharedPtr<FDTLSCertificate> ImportCert(const FString& CertPath) const;` — Import a certificate from file @Param CertPath path to certificate file @return shared pointer to certificate, valid if import succeeded
- L70 _public prototype_ `TSharedPtr<FDTLSCertificate> ImportCert(const FString& CertPath, const FString& Identifier);` — Import a certificate from file and store internally @Param CertPath path to certificate file @Param Identifier name to use when storing certificate for later use @return shared pointer to certificate, valid if import succeeded
- L79 _public prototype_ `bool RemoveCert(const FString& Identifier);` — Remove a certificate using unique identifier @Param Identifier unique identifier used when cert was added @return true if a certificate was removed
- L82 _private member_ `TMap<FString, TSharedPtr<FDTLSCertificate>> CertMap;`
- L84 _private member_ `static TUniquePtr<FDTLSCertStore> Instance;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DTLSHANDLERCOMPONENT_API`

### `Plugins/Runtime/PacketHandlers/DTLSHandlerComponent/Source/Public/DTLSCertificate.h` (Public)


#### struct `FDTLSFingerprint`  
`struct FDTLSFingerprint`  
_L15-39_
- desc: Wrapper for a fingerprint (SHA256 hash) of an X509 certificate
- L19 _public member_ `static constexpr uint32 Length = 32;` — SHA256 hash length in bytes
- L21 _public function_ `FDTLSFingerprint()`
- L26 _public prototype_ `FDTLSFingerprint(const FDTLSFingerprint&) = delete;`
- L27 _public prototype_ `FDTLSFingerprint& operator=(const FDTLSFingerprint&) = delete;`
- L30 _public function_ `void Reset()` — Zero the fingerprint
- L36 _public function_ `TArrayView<const uint8> GetData() const` — Get array view of fingerprint data
- L38 _public member_ `uint8 Data[Length];`

#### struct `FDTLSCertificate`  
`struct FDTLSCertificate`  
_L44-95_
- desc: Container for an X509 certificate
- L47 _public prototype_ `FDTLSCertificate();`
- L48 _public prototype_ `~FDTLSCertificate();`
- L50 _public prototype_ `FDTLSCertificate(const FDTLSCertificate&) = delete;`
- L51 _public prototype_ `FDTLSCertificate& operator=(const FDTLSCertificate&) = delete;`
- L52 _public prototype_ `FDTLSCertificate(FDTLSCertificate&&) = delete;`
- L53 _public prototype_ `FDTLSCertificate& operator=(FDTLSCertificate&&) = delete;`
- L56 _public function_ `EVP_PKEY* GetPKey() const` — Get OpenSSL private key pointer
- L59 _public function_ `X509* GetCertificate() const` — Get OpenSSL X509 certificate pointer
- L62 _public function_ `TArrayView<const uint8> GetFingerprint() const` — Get array view of fingerprint data
- L70 _public prototype_ `bool GenerateCertificate(const FTimespan& Lifetime);` — Generate a self-signed certificate @param Lifetime number of seconds until the certificate should expire @return true if creation succeeded
- L78 _public prototype_ `bool ExportCertificate(const FString& CertPath);` — Export current certificate to PEM file format @param CertPath path to output file @return true if export succeeded
- L86 _public prototype_ `bool ImportCertificate(const FString& CertPath);` — Import certificate from PEM file format @param CertPath path to input file @return true if import succeeded
- L89 _private prototype_ `void FreeCertificate();`
- L90 _private prototype_ `bool GenerateFingerprint();`
- L92 _private member_ `EVP_PKEY* PKey;`
- L93 _private member_ `X509* Certificate;`
- L94 _private member_ `FDTLSFingerprint Fingerprint;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DTLSHANDLERCOMPONENT_API`

### `Plugins/Runtime/PacketHandlers/DTLSHandlerComponent/Source/Public/DTLSContext.h` (Public)


#### struct `FDTLSPreSharedKey`  
`struct FDTLSPreSharedKey`  
_L15-46_
- desc: Wrapper for a pre-shared key value to be used instead of self-signed certificates
- L18 _public function_ `FDTLSPreSharedKey()`
- L20 _public prototype_ `FDTLSPreSharedKey(const FDTLSPreSharedKey&) = delete;`
- L21 _public prototype_ `FDTLSPreSharedKey& operator=(const FDTLSPreSharedKey&) = delete;`
- L23 _public function_ `TArrayView<const uint8> GetKey() const`
- L28 _public function_ `const FString& GetIdentity() const`
- L33 _public function_ `void SetPreSharedKey(TArrayView<const uint8> KeyView)`
- L38 _public function_ `void SetIdentity(const FString& InIdentity)`
- L44 _private member_ `TArray<uint8> Key;`
- L45 _private member_ `FString Identity;`

#### struct `FMTUFilter`  
`struct FMTUFilter`  
_L51-61_
- desc: OpenSSL BIO applied to SSL connection to enforce MTU for handshake packets
- L54 _public prototype_ `static int Create(BIO* BIOPtr);`
- L55 _public prototype_ `static int Destroy(BIO* BIOPtr);`
- L56 _public prototype_ `static int Write(BIO* BIOPtr, const char* Data, int DataLen);`
- L57 _public prototype_ `static long Ctrl(BIO* BIOPtr, int CtrlCommand, long, void*);`
- L60 _public member_ `TArray<int32, TInlineAllocator<16>> FragmentSizes;`

#### struct `FDTLSContext`  
`struct FDTLSContext`  
_L66-121_
- desc: Context data for OpenSSL connection setup
- L69 _public prototype_ `FDTLSContext() = delete;`
- L70 _public prototype_ `FDTLSContext(EDTLSContextType InContextType);`
- L71 _public prototype_ `~FDTLSContext();`
- L82 _public prototype_ `bool Initialize(const int32 MaxPacketSize, const FString& CertId, FDTLSHandlerComponent* Handler);` — Initialize the context @param MaxPacketSize the MTU to respect when processing handshake packets @param CertId unique identifier of certificate to use, retrieved from FDTLSCertStore @param Handler the packet handler component that owns this context @return false if initialization process failed for any reason
- L85 _public function_ `SSL* GetSSLPtr() const` — Get OpenSSL SSL pointer
- L88 _public function_ `BIO* GetInBIO() const` — Get OpenSSL input BIO pointer
- L91 _public function_ `BIO* GetOutBIO() const` — Get OpenSSL output BIO pointer
- L94 _public function_ `BIO* GetFilterBIO() const` — Get OpenSSL custom filter BIO pointer
- L101 _public function_ `EDTLSContextType GetContextType() const` — Query for context type @return EDTLSContextType context type
- L108 _public prototype_ `bool IsHandshakeComplete() const;` — Query for handshaking status @return true if the DTLS handshake has completed
- L111 _private member_ `EDTLSContextType ContextType;`
- L113 _private member_ `SSL_CTX* SSLContext;`
- L114 _private member_ `SSL* SSLPtr;`
- L115 _private member_ `BIO* InBIO;`
- L116 _private member_ `BIO* OutBIO;`
- L117 _private member_ `BIO* FilterBIO;`
- L118 _private member_ `BIO_METHOD* MTUFilterMethod;`
- L120 _private member_ `TSharedPtr<FDTLSCertificate> Cert;`

### `Plugins/Runtime/PacketHandlers/DTLSHandlerComponent/Source/Public/DTLSHandlerComponent.h` (Public)


#### class `FDTLSHandlerComponent`  
`class FDTLSHandlerComponent : public FEncryptionComponent`  
_L21-80_
- inherits: `FEncryptionComponent`
- desc: DTLS encryption component.
- L24 _public prototype_ `FDTLSHandlerComponent();`
- L25 _public prototype_ `virtual ~FDTLSHandlerComponent();`
- L27 _public prototype_ `virtual void SetEncryptionData(const FEncryptionData& EncryptionData) override;`
- L30 _public prototype_ `virtual void EnableEncryption() override;` — After calling this, future outgoing packets will be encrypted (until a call to DisableEncryption).
- L33 _public prototype_ `virtual void DisableEncryption() override;` — After calling this, future outgoing packets will not be encrypted (until a call to DisableEncryption).
- L36 _public prototype_ `virtual bool IsEncryptionEnabled() const override;` — Returns true if encryption is currently enabled.
- L39 _public prototype_ `virtual void Initialize() override;` — HandlerComponent interface
- L40 _public prototype_ `virtual bool IsValid() const override;`
- L41 _public prototype_ `virtual void Incoming(FBitReader& Packet) override;`
- L42 _public prototype_ `virtual void Outgoing(FBitWriter& Packet, FOutPacketTraits& Traits) override;`
- L43 _public prototype_ `virtual int32 GetReservedPacketBits() const override;`
- L44 _public prototype_ `virtual void CountBytes(FArchive& Ar) const override;`
- L46 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L56 _public function_ `const FDTLSPreSharedKey* GetPreSharedKey() const` — Retrieve pre shared key, if set
- L59 _public function_ `const FDTLSFingerprint* GetRemoteFingerprint() const` — Retrieve expected remote certificate fingerprint, if set
- L63 _private prototype_ `void TickHandshake();` — Process DTLS handshake
- L64 _private prototype_ `void DoHandshake();`
- L66 _private prototype_ `void LogError(const TCHAR* Context, int32 Result);`
- L69 _private member_ `EDTLSHandlerState InternalState;`
- L71 _private member_ `TUniquePtr<FDTLSContext> DTLSContext;`
- L72 _private member_ `TUniquePtr<FDTLSPreSharedKey> PreSharedKey;`
- L73 _private member_ `TUniquePtr<FDTLSFingerprint> RemoteFingerprint;`
- L75 _private member_ `FString CertId;`
- L77 _private member_ `uint8 TempBuffer[MAX_PACKET_SIZE];`
- L79 _private member_ `bool bPendingHandshakeData;`

#### enum `FDTLSHandlerComponent::EDTLSHandlerState`  
`enum class EDTLSHandlerState`  
_L48-53_
- L50 _public enumerator_ `Unencrypted`
- L51 _public enumerator_ `Handshaking`
- L52 _public enumerator_ `Encrypted`

#### class `FDTLSHandlerComponentModule`  
`class FDTLSHandlerComponentModule : public FPacketHandlerComponentModuleInterface`  
_L87-95_
- inherits: `FPacketHandlerComponentModuleInterface`
- desc: The public interface to this module.
- L90 _public prototype_ `virtual void StartupModule() override;`
- L91 _public prototype_ `virtual void ShutdownModule() override;`
- L94 _public prototype_ `virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options) override;` — Creates an instance of this component

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DTLSHANDLERCOMPONENT_API`
- L16 _externvar_ `extern TAutoConsoleVariable<int32> CVarPreSharedKeys;`

### `Plugins/Runtime/PacketHandlers/DTLSHandlerComponent/Source/Public/DTLSHandlerTypes.h` (Public)


#### enum `EDTLSContextType`  
`enum class EDTLSContextType`  
_L28-32_
- L30 _public enumerator_ `Server`
- L31 _public enumerator_ `Client`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef struct evp_pkey_st EVP_PKEY;`
- L15 _typedef_ `typedef struct x509_st X509;`
- L18 _typedef_ `typedef struct ssl_ctx_st SSL_CTX;`
- L21 _typedef_ `typedef struct ssl_st SSL;`
- L24 _typedef_ `typedef struct bio_st BIO;`
- L26 _typedef_ `typedef struct bio_method_st BIO_METHOD;`
- L34 _prototype_ `const TCHAR* LexToString(EDTLSContextType ContextType);`
- L38 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDTLSHandler, Log, All);`
- L38 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDTLSHandler, Log, All);`
