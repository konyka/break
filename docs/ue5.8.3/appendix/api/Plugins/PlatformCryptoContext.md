# Plugins / PlatformCryptoContext

- module root: `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext`
- headers: 7; symbols: 197
- symbol kinds: class=17, delegate=1, enum=2, enumerator=6, function=15, macro=1, member=17, prototype=129, struct=1, typedef=5, variable=3
- PublicDependencyModuleNames: Core, PlatformCryptoTypes

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext/Private/PlatformCryptoAesDecryptorsOpenSSL.h` (Private)


#### class `FPlatformCryptoDecryptor_AES_Base_OpenSSL`  
`class FPlatformCryptoDecryptor_AES_Base_OpenSSL : public IPlatformCryptoDecryptor`  
_L8-55_
- inherits: `IPlatformCryptoDecryptor`
- L12 _public prototype_ `virtual ~FPlatformCryptoDecryptor_AES_Base_OpenSSL() = default;`
- L31 _public prototype_ `EPlatformCryptoResult Initialize(const EVP_CIPHER* Cipher, const TArrayView<const uint8> Key, const TOptional<TArrayView<const uint8>> InitializationVector = TOptional<TArrayView<const uint8>>());` — Initialize our decryptor with a specific Cipher, Key, and (optionally) an Initialization Vector. @param Cipher OpenSSL Cipher to use @param Key Key to use.  Must be the correct amount of bits for the Cipher value @param InitializationVector Optional Initialization Vector if the Cipher requires one. Must be the correct amount of bits for the Cipher value if set
- L34 _public prototype_ `virtual EPlatformCryptoResult SetAuthTag(const TArrayView<const uint8> AuthTag) override final;`
- L35 _public prototype_ `virtual int32 GetCipherBlockSizeBytes() const override final;`
- L36 _public prototype_ `virtual int32 GetCipherInitializationVectorSizeBytes() const override final;`
- L37 _public prototype_ `virtual EPlatformCryptoResult Update(const TArrayView<const uint8> Ciphertext, const TArrayView<uint8> OutPlaintext, int32& OutPlaintextBytesWritten) override final;`
- L38 _public prototype_ `virtual EPlatformCryptoResult Finalize(const TArrayView<uint8> OutPlaintext, int32& OutPlaintextBytesWritten) override final;`
- L39 _public prototype_ `virtual EPlatformCryptoResult Reset(const TArrayView<const uint8> InitializationVector) override final;`
- L47 _public prototype_ `EPlatformCryptoResult Reset();` — Resets our context, requiring Initialize to be called again before it may be used. @return Success if our context was successfully reset, Failure otherwise
- L50 _protected prototype_ `FPlatformCryptoDecryptor_AES_Base_OpenSSL() = default;`
- L53 _protected member_ `FScopedEVPContext EVPContext;`
- L54 _protected member_ `EDecryptorState State = EDecryptorState::Uninitialized;`

#### enum `FPlatformCryptoDecryptor_AES_Base_OpenSSL::EDecryptorState`  
`enum class EDecryptorState`  
_L14-22_
- L17 _public enumerator_ `Uninitialized` — Initialize needs to be called before data may be decrypted successfully
- L19 _public enumerator_ `Initialized` — Initialize succeeded and is currently able to decrypt data
- L21 _public enumerator_ `Finalized` — Finalize has been called, and Initialize must be called before it may be re-used

#### class `FPlatformCryptoDecryptor_AES_256_ECB_OpenSSL`  
`class FPlatformCryptoDecryptor_AES_256_ECB_OpenSSL : public FPlatformCryptoDecryptor_AES_Base_OpenSSL`  
_L57-74_
- inherits: `FPlatformCryptoDecryptor_AES_Base_OpenSSL`
- L61 _public prototype_ `virtual ~FPlatformCryptoDecryptor_AES_256_ECB_OpenSSL() = default;`
- L63 _public prototype_ `static TUniquePtr<IPlatformCryptoDecryptor> Create(const TArrayView<const uint8> Key);`
- L66 _public prototype_ `virtual FName GetCipherName() const override final;`
- L67 _public prototype_ `virtual int32 GetCipherAuthTagSizeBytes() const override final;`
- L68 _public prototype_ `virtual int32 GetUpdateBufferSizeBytes(const TArrayView<const uint8> Ciphertext) const override final;`
- L69 _public prototype_ `virtual int32 GetFinalizeBufferSizeBytes() const override final;`
- L73 _private prototype_ `FPlatformCryptoDecryptor_AES_256_ECB_OpenSSL() = default;`

#### class `FPlatformCryptoDecryptor_AES_256_CBC_OpenSSL`  
`class FPlatformCryptoDecryptor_AES_256_CBC_OpenSSL : public FPlatformCryptoDecryptor_AES_Base_OpenSSL`  
_L76-93_
- inherits: `FPlatformCryptoDecryptor_AES_Base_OpenSSL`
- L80 _public prototype_ `virtual ~FPlatformCryptoDecryptor_AES_256_CBC_OpenSSL() = default;`
- L82 _public prototype_ `static TUniquePtr<IPlatformCryptoDecryptor> Create(const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector);`
- L85 _public prototype_ `virtual FName GetCipherName() const override final;`
- L86 _public prototype_ `virtual int32 GetCipherAuthTagSizeBytes() const override final;`
- L87 _public prototype_ `virtual int32 GetUpdateBufferSizeBytes(const TArrayView<const uint8> Ciphertext) const override final;`
- L88 _public prototype_ `virtual int32 GetFinalizeBufferSizeBytes() const override final;`
- L92 _private prototype_ `FPlatformCryptoDecryptor_AES_256_CBC_OpenSSL() = default;`

#### class `FPlatformCryptoDecryptor_AES_256_GCM_OpenSSL`  
`class FPlatformCryptoDecryptor_AES_256_GCM_OpenSSL : public FPlatformCryptoDecryptor_AES_Base_OpenSSL`  
_L95-112_
- inherits: `FPlatformCryptoDecryptor_AES_Base_OpenSSL`
- L99 _public prototype_ `virtual ~FPlatformCryptoDecryptor_AES_256_GCM_OpenSSL() = default;`
- L101 _public prototype_ `static TUniquePtr<IPlatformCryptoDecryptor> Create(const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector, const TArrayView<const uint8> AuthTag);`
- L104 _public prototype_ `virtual FName GetCipherName() const override final;`
- L105 _public prototype_ `virtual int32 GetCipherAuthTagSizeBytes() const override final;`
- L106 _public prototype_ `virtual int32 GetUpdateBufferSizeBytes(const TArrayView<const uint8> Ciphertext) const override final;`
- L107 _public prototype_ `virtual int32 GetFinalizeBufferSizeBytes() const override final;`
- L111 _private prototype_ `FPlatformCryptoDecryptor_AES_256_GCM_OpenSSL() = default;`

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext/Private/PlatformCryptoAesEncryptorsOpenSSL.h` (Private)


#### class `FPlatformCryptoEncryptor_AES_Base_OpenSSL`  
`class FPlatformCryptoEncryptor_AES_Base_OpenSSL : public IPlatformCryptoEncryptor`  
_L10-57_
- inherits: `IPlatformCryptoEncryptor`
- L14 _public prototype_ `virtual ~FPlatformCryptoEncryptor_AES_Base_OpenSSL() = default;`
- L33 _public prototype_ `EPlatformCryptoResult Initialize(const EVP_CIPHER* Cipher, const TArrayView<const uint8> Key, const TOptional<TArrayView<const uint8>> InitializationVector);` — Initialize our encryptor with a specific Cipher, Key, and (optionally) an Initialization Vector. @param Cipher OpenSSL Cipher to use @param Key Key to use.  Must be the correct amount of bits for the Cipher value @param InitializationVector Optional Initialization Vector if the Cipher requires one. Must be the correct amount of bits for the Cipher value if set
- L36 _public prototype_ `virtual int32 GetCipherBlockSizeBytes() const override final;`
- L37 _public prototype_ `virtual int32 GetCipherInitializationVectorSizeBytes() const override final;`
- L38 _public prototype_ `virtual EPlatformCryptoResult GenerateAuthTag(const TArrayView<uint8> OutAuthTag, int32& OutAuthTagBytesWritten) const override final;`
- L39 _public prototype_ `virtual EPlatformCryptoResult Update(const TArrayView<const uint8> Plaintext, const TArrayView<uint8> OutCiphertext, int32& OutCiphertextBytesWritten) override final;`
- L40 _public prototype_ `virtual EPlatformCryptoResult Finalize(const TArrayView<uint8> OutCiphertext, int32& OutCiphertextBytesWritten) override final;`
- L41 _public prototype_ `virtual EPlatformCryptoResult Reset(const TArrayView<const uint8> InitializationVector) override final;`
- L49 _public prototype_ `EPlatformCryptoResult Reset();` — Resets our context, requiring Initialize to be called again before it may be used. @return Success if our context was successfully reset, Failure otherwise
- L52 _protected prototype_ `FPlatformCryptoEncryptor_AES_Base_OpenSSL() = default;`
- L55 _protected member_ `FScopedEVPContext EVPContext;`
- L56 _protected member_ `EEncryptorState State = EEncryptorState::Uninitialized;`

#### enum `FPlatformCryptoEncryptor_AES_Base_OpenSSL::EEncryptorState`  
`enum class EEncryptorState`  
_L16-24_
- L19 _public enumerator_ `Uninitialized` — Initialize needs to be called before data may be encrypted successfully
- L21 _public enumerator_ `Initialized` — Initialize succeeded and is currently able to encrypt data
- L23 _public enumerator_ `Finalized` — Finalize has been called, and Initialize must be called before it may be re-used

#### class `FPlatformCryptoEncryptor_AES_256_ECB_OpenSSL`  
`class FPlatformCryptoEncryptor_AES_256_ECB_OpenSSL : public FPlatformCryptoEncryptor_AES_Base_OpenSSL`  
_L59-76_
- inherits: `FPlatformCryptoEncryptor_AES_Base_OpenSSL`
- L63 _public prototype_ `virtual ~FPlatformCryptoEncryptor_AES_256_ECB_OpenSSL() = default;`
- L65 _public prototype_ `static TUniquePtr<IPlatformCryptoEncryptor> Create(const TArrayView<const uint8> Key);`
- L68 _public prototype_ `virtual FName GetCipherName() const override final;`
- L69 _public prototype_ `virtual int32 GetCipherAuthTagSizeBytes() const override final;`
- L70 _public prototype_ `virtual int32 GetUpdateBufferSizeBytes(const TArrayView<const uint8> Plaintext) const override final;`
- L71 _public prototype_ `virtual int32 GetFinalizeBufferSizeBytes() const override final;`
- L75 _private prototype_ `FPlatformCryptoEncryptor_AES_256_ECB_OpenSSL() = default;`

#### class `FPlatformCryptoEncryptor_AES_256_CBC_OpenSSL`  
`class FPlatformCryptoEncryptor_AES_256_CBC_OpenSSL : public FPlatformCryptoEncryptor_AES_Base_OpenSSL`  
_L78-95_
- inherits: `FPlatformCryptoEncryptor_AES_Base_OpenSSL`
- L82 _public prototype_ `virtual ~FPlatformCryptoEncryptor_AES_256_CBC_OpenSSL() = default;`
- L84 _public prototype_ `static TUniquePtr<IPlatformCryptoEncryptor> Create(const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector);`
- L87 _public prototype_ `virtual FName GetCipherName() const override final;`
- L88 _public prototype_ `virtual int32 GetCipherAuthTagSizeBytes() const override final;`
- L89 _public prototype_ `virtual int32 GetUpdateBufferSizeBytes(const TArrayView<const uint8> Plaintext) const override final;`
- L90 _public prototype_ `virtual int32 GetFinalizeBufferSizeBytes() const override final;`
- L94 _private prototype_ `FPlatformCryptoEncryptor_AES_256_CBC_OpenSSL() = default;`

#### class `FPlatformCryptoEncryptor_AES_256_GCM_OpenSSL`  
`class FPlatformCryptoEncryptor_AES_256_GCM_OpenSSL : public FPlatformCryptoEncryptor_AES_Base_OpenSSL`  
_L97-114_
- inherits: `FPlatformCryptoEncryptor_AES_Base_OpenSSL`
- L101 _public prototype_ `virtual ~FPlatformCryptoEncryptor_AES_256_GCM_OpenSSL() = default;`
- L103 _public prototype_ `static TUniquePtr<IPlatformCryptoEncryptor> Create(const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector);`
- L106 _public prototype_ `virtual FName GetCipherName() const override final;`
- L107 _public prototype_ `virtual int32 GetCipherAuthTagSizeBytes() const override final;`
- L108 _public prototype_ `virtual int32 GetUpdateBufferSizeBytes(const TArrayView<const uint8> Plaintext) const override final;`
- L109 _public prototype_ `virtual int32 GetFinalizeBufferSizeBytes() const override final;`
- L113 _private prototype_ `FPlatformCryptoEncryptor_AES_256_GCM_OpenSSL() = default;`

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext/Private/PlatformCryptoOpenSSLTypes.h` (Private)


#### class `FScopedEVPContext`  
`class FScopedEVPContext`  
_L24-54_
- desc: RAII wrapper for the OpenSSL EVP Cipher context object The EVP cipher context stores state related to OpenSSL encryption/decryption functions, and requires initialization by the user, by use of functions such as EVP_EncryptInit_ex.
- L30 _public function_ `FScopedEVPContext() : Context(EVP_CIPHER_CTX_new())` — Creates our OpenSSL Cipher Context on construction
- L38 _public function_ `~FScopedEVPContext()` — Free our OpenSSL Cipher Context
- L46 _public function_ `EVP_CIPHER_CTX* Get() const` — Get our OpenSSL Cipher Context
- L50 _private prototype_ `FScopedEVPContext(const FScopedEVPContext& Other) = delete;` — Disable copying/assigning
- L51 _private prototype_ `FScopedEVPContext& operator=(const FScopedEVPContext& Other) = delete;`
- L53 _private member_ `EVP_CIPHER_CTX* Context;`

#### class `FScopedEVPMDContext`  
`class FScopedEVPMDContext`  
_L62-92_
- desc: RAII wrapper for the OpenSSL EVP Message Digest context object The EVP message digest context stores state related to OpenSSL digest functions, and requires initialization by the user, by use of functions such as EVP_DigestVerifyInit.
- L68 _public function_ `FScopedEVPMDContext() : Context(EVP_MD_CTX_create())` — Creates our OpenSSL Message Digest Context on construction
- L74 _public prototype_ `FScopedEVPMDContext(FScopedEVPMDContext&) = delete;` — Disable copying/assigning
- L75 _public prototype_ `FScopedEVPMDContext& operator=(FScopedEVPMDContext&) = delete;`
- L80 _public function_ `~FScopedEVPMDContext()` — Free our OpenSSL Message Digest Context
- L88 _public function_ `EVP_MD_CTX* Get() const` — Get our OpenSSL Message Digest Context
- L91 _private member_ `EVP_MD_CTX* Context;`

#### class `FScopedEvpPKeyContext`  
`class FScopedEvpPKeyContext`  
_L97-127_
- desc: RAII wrapper for the OpenSSL EVP public key algorithm context object.
- L103 _public function_ `FScopedEvpPKeyContext(int KeyAlgorithm) : Context(EVP_PKEY_CTX_new_id(KeyAlgorithm, nullptr))` — Creates OpenSSL EVP public key algorithm context on construction.
- L109 _public prototype_ `FScopedEvpPKeyContext(FScopedEvpPKeyContext&) = delete;` — Disable copying/assigning
- L110 _public prototype_ `FScopedEvpPKeyContext& operator=(FScopedEvpPKeyContext&) = delete;`
- L115 _public function_ `~FScopedEvpPKeyContext()` — Releases OpenSSL EVP public key algorithm context.
- L123 _public function_ `EVP_PKEY_CTX* Get() const` — Returns OpenSSL EVP public key algorithm context.
- L126 _private member_ `EVP_PKEY_CTX* Context;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlatformCryptoOpenSSL, Warning, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlatformCryptoOpenSSL, Warning, All);`
- L14 _variable_ `static constexpr const int32 AES256_ECB_AuthTagSizeInBytes = 0;` — Not Supported
- L15 _variable_ `static constexpr const int32 AES256_CBC_AuthTagSizeInBytes = 0;` — Not Supported
- L16 _variable_ `static constexpr const int32 AES256_GCM_AuthTagSizeInBytes = 16;` — 128-bit

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext/Private/PlatformCryptoUtilsOpenSSL.h` (Private)


#### class `FPlatformCryptoUtilsOpenSSL`  
`class FPlatformCryptoUtilsOpenSSL`  
_L25-36_
- L30 _public prototype_ `static void BigNumToArray( const BIGNUM* InNum, TArray<uint8>& OutBytes);`
- L33 _public prototype_ `static void LoadBinaryIntoBigNum( const uint8* InData, int32 InDataSize, BIGNUM* InBigNum);`

#### Free symbols / members of external scopes

- L19 _macro_ `#define USE_LEGACY_OPENSSL 1`

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext/Public/EncryptionContextOpenSSL.h` (Public)


#### struct `FSHA256HasherOpenSSL`  
`struct FSHA256HasherOpenSSL final`  
_L16-54_
- desc: Implementation details for SHA256 computation using OpenSSL
- L18 _public prototype_ `FSHA256HasherOpenSSL(FSHA256HasherOpenSSL&&) = default;`
- L19 _public prototype_ `FSHA256HasherOpenSSL& operator=(FSHA256HasherOpenSSL&&) = default;`
- L25 _public prototype_ `EPlatformCryptoResult Init();` — Initialize the necessary state to begin computing a message digest. It is only necessary to call this function if the object is being used to compute multiple hashes, as the constructor will automatically call it the first time.
- L32 _public prototype_ `EPlatformCryptoResult Update(const TArrayView<const uint8> InDataBuffer);` — Update the message digest computation with additional bytes @param InDataBuffer Buffer pointing to the data
- L39 _public prototype_ `EPlatformCryptoResult Finalize(const TArrayView<uint8> OutDataBuffer);` — Finalize the computation of the message digest. After calling this method, Init must be called again if this object is meant to be reused for hashing a new input. @param OutDataBuffer A buffer that can hold the message digest bytes. Call GetOutputByteLength to determine the necessary size.
- L44 _public member_ `static constexpr const uint32 OutputByteLength = 32;` — The final message digest length in bytes.
- L47 _private prototype_ `FSHA256HasherOpenSSL();`
- L48 _private prototype_ `FSHA256HasherOpenSSL(const FSHA256HasherOpenSSL&) = delete;`
- L49 _private prototype_ `FSHA256HasherOpenSSL& operator=(const FSHA256HasherOpenSSL&) = delete;`
- L53 _private member_ `TPimplPtr<FImplDetails> Inner;`

#### class `FSignerEd25519OpenSSL`  
`class FSignerEd25519OpenSSL final`  
_L58-107_
- desc: Implementation details for ed25519 signing using OpenSSL
- L61 _public prototype_ `FSignerEd25519OpenSSL();`
- L63 _public prototype_ `FSignerEd25519OpenSSL(FSignerEd25519OpenSSL&&) = default;`
- L64 _public prototype_ `FSignerEd25519OpenSSL(const FSignerEd25519OpenSSL&) = delete;`
- L65 _public prototype_ `FSignerEd25519OpenSSL& operator=(FSignerEd25519OpenSSL&&) = default;`
- L66 _public prototype_ `FSignerEd25519OpenSSL& operator=(const FSignerEd25519OpenSSL&) = delete;`
- L68 _public prototype_ `~FSignerEd25519OpenSSL();`
- L76 _public prototype_ `bool SetPrivateKey(const TArrayView<const uint8> Key);` — Set private key for signing @param Key Buffer pointing to the private key data @return True if initialized succesfully
- L85 _public prototype_ `bool Sign(const TArrayView<const uint8> Message, const TArrayView<uint8> Signature);` — Signing data block @param Message Buffer pointing to the data @param Signature Buffer pointing to the signature @return True if signed succesfully
- L90 _public prototype_ `bool IsReady() const;` — Check if signer are ready
- L95 _public member_ `static constexpr const uint32 OutputSignatureLength = 64;` — The final signature length in bytes.
- L100 _public member_ `static constexpr const uint32 KeyBufferLength = 32;` — The key length in bytes.
- L106 _private member_ `TPimplPtr<FImplDetails> Inner;`

#### class `FVerifierEd25519OpenSSL`  
`class FVerifierEd25519OpenSSL final`  
_L111-160_
- desc: Implementation details for ed25519 verify signature using OpenSSL
- L114 _public prototype_ `FVerifierEd25519OpenSSL();`
- L116 _public prototype_ `FVerifierEd25519OpenSSL(FVerifierEd25519OpenSSL&&) = default;`
- L117 _public prototype_ `FVerifierEd25519OpenSSL(const FVerifierEd25519OpenSSL&) = delete;`
- L118 _public prototype_ `FVerifierEd25519OpenSSL& operator=(FVerifierEd25519OpenSSL&&) = default;`
- L119 _public prototype_ `FVerifierEd25519OpenSSL& operator=(const FVerifierEd25519OpenSSL&) = delete;`
- L121 _public prototype_ `~FVerifierEd25519OpenSSL();`
- L129 _public prototype_ `bool SetPublicKey(const TArrayView<const uint8> Key);` — Set public key for verify signature @param Key Buffer pointing to the public key data @return True if inited successfully
- L138 _public prototype_ `bool Verify(const TArrayView<const uint8> Message, const TArrayView<const uint8> Signature);` — Verify data block @param Message Buffer pointing to the data @param Signature Buffer pointing to the signature @return True if signature are correct
- L143 _public prototype_ `bool IsReady() const;` — Check if verifier are ready
- L148 _public member_ `static constexpr const uint32 SignatureLength = 64;` — The signature length in bytes.
- L153 _public member_ `static constexpr const uint32 KeyBufferLength = 32;` — The key length in bytes.
- L159 _private member_ `TPimplPtr<FImplDetails> Inner;`

#### class `FCryptoKeyGeneratorOpenSSL`  
`class FCryptoKeyGeneratorOpenSSL final`  
_L164-173_
- desc: Implementation of crypto key generator using OpenSSL.
- L172 _public prototype_ `TOptional<FCryptoKeyPair> GenerateEd25519() const;` — Generates Ed25519 key pair. @return The structure with public/private key pair when success.

#### class `FEncryptionContextOpenSSL`  
`class FEncryptionContextOpenSSL`  
_L179-377_
- desc: Interface to certain cryptographic algorithms, using OpenSSL to implement them.
- L184 _public function_ `static void OnStartup(IPlatformCryptoContext* const Context)`
- L185 _public function_ `static void OnShutdown(IPlatformCryptoContext* const Context)`
- L187 _public prototype_ `TArray<uint8> Encrypt_AES_256_ECB(const TArrayView<const uint8> Plaintext, const TArrayView<const uint8> Key, EPlatformCryptoResult& OutResult);`
- L188 _public prototype_ `TArray<uint8> Encrypt_AES_256_CBC(const TArrayView<const uint8> Plaintext, const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector, EPlatformCryptoResult& OutResult);`
- L189 _public prototype_ `TArray<uint8> Encrypt_AES_256_GCM(const TArrayView<const uint8> Plaintext, const TArrayView<const uint8> Key, const TArrayView<const uint8> Nonce, TArray<uint8>& OutAuthTag, EPlatformCryptoResult& OutResult);`
- L191 _public prototype_ `TArray<uint8> Decrypt_AES_256_ECB(const TArrayView<const uint8> Ciphertext, const TArrayView<const uint8> Key, EPlatformCryptoResult& OutResult);`
- L192 _public prototype_ `TArray<uint8> Decrypt_AES_256_CBC(const TArrayView<const uint8> Ciphertext, const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector, EPlatformCryptoResult& OutResult);`
- L193 _public prototype_ `TArray<uint8> Decrypt_AES_256_GCM(const TArrayView<const uint8> Ciphertext, const TArrayView<const uint8> Key, const TArrayView<const uint8> Nonce, const TArrayView<const uint8> AuthTag, EPlatformCryptoResult& OutResult);`
- L195 _public prototype_ `TUniquePtr<IPlatformCryptoEncryptor> CreateEncryptor_AES_256_ECB(const TArrayView<const uint8> Key);`
- L196 _public prototype_ `TUniquePtr<IPlatformCryptoEncryptor> CreateEncryptor_AES_256_CBC(const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector);`
- L197 _public prototype_ `TUniquePtr<IPlatformCryptoEncryptor> CreateEncryptor_AES_256_GCM(const TArrayView<const uint8> Key, const TArrayView<const uint8> Nonce);`
- L199 _public prototype_ `TUniquePtr<IPlatformCryptoDecryptor> CreateDecryptor_AES_256_ECB(const TArrayView<const uint8> Key);`
- L200 _public prototype_ `TUniquePtr<IPlatformCryptoDecryptor> CreateDecryptor_AES_256_CBC(const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector);`
- L201 _public prototype_ `TUniquePtr<IPlatformCryptoDecryptor> CreateDecryptor_AES_256_GCM(const TArrayView<const uint8> Key, const TArrayView<const uint8> Nonce, const TArrayView<const uint8> AuthTag);`
- L214 _public prototype_ `bool DigestSign_RS256(const TArrayView<const uint8> Message, TArray<uint8>& Signature, FRSAKeyHandle Key);` — Sign a message with RS256. @param Message The message @param Signature The resulting signature @param Key Handle to the RSA key @return Whether the sign operation was successful
- L225 _public prototype_ `bool DigestVerify_PS256(const TArrayView<const char> Message, const TArrayView<const uint8> Signature, const TArrayView<const uint8> PKCS1Key);` — Verify a hashed PS256 message with a signature. @param Message The hashed message @param Signature Signature to verify with @param PKCS1Key Handle to the RSA key in PKCS1 format @return Whether the verify operation was successful
- L236 _public prototype_ `bool DigestVerify_RS256(const TArrayView<const uint8> Message, const TArrayView<const uint8> Signature, FRSAKeyHandle Key);` — Verify a hashed RS256 message with a signature. @param Message The hashed message @param Signature Signature to verify with @param Key Handle to the RSA key @return Whether the verify operation was successful
- L248 _public prototype_ `bool GenerateKey_RSA(const int32 InNumKeyBits, TArray<uint8>& OutPublicExponent, TArray<uint8>& OutPrivateExponent, TArray<uint8>& OutModulus);` — Generate an RSA key with the number of key bits. @param InNumKeyBits Number of key bits @param OutPublicExponent Array for the public exponent @param OutPrivateExponent Array for the private exponent @param OutModulus Array for the modulus @return Whether the generate operation was successful
- L259 _public prototype_ `FRSAKeyHandle CreateKey_RSA(const TArrayView<const uint8> PublicExponent, const TArrayView<const uint8> PrivateExponent, const TArrayView<const uint8> Modulus);` — Create an RSA key from a binary public/private exponent and modulus. @param PublicExponent Binary key public exponent @param PrivateExponent Binary key private exponent @param Modulus Binary key modulus @return The created RSA key
- L268 _public prototype_ `FRSAKeyHandle GetPublicKey_RSA(const FStringView PemSource);` — Get the RSA public key from a PEM format string. @param PemSource Key in PEM format (base64) @return The RSA public key
- L275 _public prototype_ `void DestroyKey_RSA(FRSAKeyHandle Key);` — Destroy and free the RSA key. @param Key Handle to the key
- L284 _public prototype_ `int32 GetKeySize_RSA(FRSAKeyHandle Key);` — Get the RSA key modulus size in bytes. @param Key Handle to the key @return The modulus size in bytes
- L293 _public prototype_ `int32 GetMaxDataSize_RSA(FRSAKeyHandle Key);` — Get the maximum data size. @param Key Handle to the key @return The maximum data size in bytes
- L304 _public prototype_ `int32 EncryptPublic_RSA(TArrayView<const uint8> Source, TArray<uint8>& Dest, FRSAKeyHandle Key);` — Encrypt a source with a public RSA key. @param Source Binary source message @param Dest Array for the encrypted data @param Key Handle to the key @return Number of encrypted bytes
- L315 _public prototype_ `int32 EncryptPrivate_RSA(TArrayView<const uint8> Source, TArray<uint8>& Dest, FRSAKeyHandle Key);` — Encrypt a source with a private RSA key. @param Source Binary source message @param Dest Array for the encrypted data @param Key Handle to the key @return Number of encrypted bytes
- L326 _public prototype_ `int32 DecryptPublic_RSA(TArrayView<const uint8> Source, TArray<uint8>& Dest, FRSAKeyHandle Key);` — Decrypt a source with a public RSA key. @param Source Binary source message @param Dest Array for the encrypted data @param Key Handle to the key @return Number of decrypted bytes
- L337 _public prototype_ `int32 DecryptPrivate_RSA(TArrayView<const uint8> Source, TArray<uint8>& Dest, FRSAKeyHandle Key);` — Decrypt a source with a private RSA key. @param Source Binary source message @param Dest Array for the encrypted data @param Key Handle to the key @return Number of decrypted bytes
- L348 _public prototype_ `EPlatformCryptoResult CreateRandomBytes(const TArrayView<uint8> OutData);` — Create random bytes. @param OutData Array for the random bytes @return The platform crypto result enum
- L357 _public prototype_ `EPlatformCryptoResult CreatePseudoRandomBytes(const TArrayView<uint8> OutData);` — Create pseudo random bytes. @param OutData Array for the pseudo random bytes @return The platform crypto result enum
- L366 _public prototype_ `FSHA256Hasher CreateSHA256Hasher();` — Create a new SHA256 hasher. @return Reference to the hasher
- L376 _public prototype_ `bool CalcSHA256(const TArrayView<const uint8> Source, TArray<uint8>& OutHash);` — Calculate the SHA256 hash of a message. @param Source Binary source data @param OutHash Array to store the hash in @return Whether the hash operation was successful

#### Free symbols / members of external scopes

- L55 _typedef_ `using FSHA256Hasher = FSHA256HasherOpenSSL;`
- L108 _typedef_ `using FSignerEd25519 = FSignerEd25519OpenSSL;`
- L161 _typedef_ `using FVerifierEd25519 = FVerifierEd25519OpenSSL;`
- L174 _typedef_ `using FCryptoKeyGenerator = FCryptoKeyGeneratorOpenSSL;`
- L379 _typedef_ `typedef FEncryptionContextOpenSSL FEncryptionContext;`

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext/Public/IPlatformCryptoContext.h` (Public)


#### class `IPlatformCryptoContext`  
`class IPlatformCryptoContext : public IModuleInterface`  
_L11-62_
- inherits: `IModuleInterface`
- desc: Module interface for cryptographic functionality. Users should generally go through the FEncryptionContext API.
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public function_ `static inline IPlatformCryptoContext& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L45 _public function_ `template<typename T> void SetUserData(TSharedPtr<T>& InUserData)` — User data access.
- L52 _public function_ `template<typename T> TSharedPtr<T> GetUserData() const`
- L60 _protected member_ `mutable FRWLock UserDataLock;`
- L61 _protected member_ `TSharedPtr<void> UserData;`

### `Plugins/Experimental/PlatformCrypto/Source/PlatformCryptoContext/Public/PlatformCryptoContextIncludes.h` (Public)
_(no declarations extracted)_
