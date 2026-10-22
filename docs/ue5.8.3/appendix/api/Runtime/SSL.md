# Runtime / SSL

- module root: `Source/Runtime/Online/SSL`
- headers: 11; symbols: 87
- symbol kinds: class=9, enum=1, enumerator=7, function=2, member=17, prototype=40, struct=2, typedef=9
- PrivateDependencyModuleNames: Core

### `Source/Runtime/Online/SSL/Private/Android/AndroidPlatformSslCertificateManager.h` (Private)


#### class `FAndroidPlatformSslCertificateManager`  
`class FAndroidPlatformSslCertificateManager : public FSslCertificateManager`  
_L11-15_
- inherits: `FSslCertificateManager`
- L14 _public prototype_ `virtual void BuildRootCertificateArray() override;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FPlatformSslCertificateManager = FAndroidPlatformSslCertificateManager;`

### `Source/Runtime/Online/SSL/Private/PlatformSslCertificateManager.h` (Private)


#### Free symbols / members of external scopes

- L19 _typedef_ `using FPlatformSslCertificateManager = FSslCertificateManager;`

### `Source/Runtime/Online/SSL/Private/SslCertificateManager.h` (Private)


#### class `FSslCertificateManager`  
`class FSslCertificateManager : public ISslCertificateManager`  
_L14-36_
- inherits: `ISslCertificateManager`
- L17 _public prototype_ `virtual void AddCertificatesToSslContext(SSL_CTX* SslContextPtr) const override;`
- L18 _public prototype_ `virtual bool HasCertificatesAvailable() const override;`
- L20 _public prototype_ `virtual void ClearAllPinnedPublicKeys() override;`
- L21 _public prototype_ `virtual bool HasPinnedPublicKeys() const override;`
- L22 _public prototype_ `virtual bool IsDomainPinned(const FString& Domain) override;`
- L23 _public prototype_ `virtual void SetPinnedPublicKeys(const FString& Domain, const FString& PinnedKeyDigests) override;`
- L24 _public prototype_ `virtual bool VerifySslCertificates(X509_STORE_CTX* Context, const FString& Domain) const override;`
- L25 _public prototype_ `virtual bool VerifySslCertificates(TArray<TArray<uint8, TFixedAllocator<PUBLIC_KEY_DIGEST_SIZE>>>& Digests, const FString& Domain) const override;`
- L27 _public prototype_ `virtual void BuildRootCertificateArray();`
- L28 _public prototype_ `virtual void EmptyRootCertificateArray();`
- L31 _protected prototype_ `void AddPEMFileToRootCertificateArray(const FString& Path);`
- L32 _protected prototype_ `void AddCertificateToRootCertificateArray(X509* Certificate);`
- L34 _protected member_ `TArray<X509*> RootCertificateArray;`
- L35 _protected member_ `TArray<TPair<FString, TArray<TArray<uint8, TFixedAllocator<PUBLIC_KEY_DIGEST_SIZE>>>>> PinnedPublicKeys;`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef struct x509_st X509;`

### `Source/Runtime/Online/SSL/Private/SslError.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `FString GetSslErrorString();` — Helper to get ssl/crypto error string

### `Source/Runtime/Online/SSL/Private/SslManager.h` (Private)


#### class `FSslManager`  
`class FSslManager : ISslManager`  
_L15-35_
- inherits: `ISslManager`
- desc: Manager of the ssl library
- L20 _public prototype_ `virtual bool InitializeSsl() override;`
- L21 _public prototype_ `virtual void ShutdownSsl() override;`
- L22 _public prototype_ `virtual SSL_CTX* CreateSslContext(const FSslContextCreateOptions& CreateOptions) override;`
- L23 _public prototype_ `virtual void DestroySslContext(SSL_CTX* SslContext) override;`
- L28 _protected prototype_ `FSslManager();` — Default constructor
- L32 _protected member_ `int32 InitCount;` — SSL ref count

### `Source/Runtime/Online/SSL/Private/Unix/UnixPlatformSslCertificateManager.h` (Private)


#### class `FUnixPlatformSslCertificateManager`  
`class FUnixPlatformSslCertificateManager : public FSslCertificateManager`  
_L11-15_
- inherits: `FSslCertificateManager`
- L14 _public prototype_ `virtual void BuildRootCertificateArray() override;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FPlatformSslCertificateManager = FUnixPlatformSslCertificateManager;`

### `Source/Runtime/Online/SSL/Private/Windows/WindowsPlatformSslCertificateManager.h` (Private)


#### class `FWindowsPlatformSslCertificateManager`  
`class FWindowsPlatformSslCertificateManager : public FSslCertificateManager`  
_L11-15_
- inherits: `FSslCertificateManager`
- L14 _public prototype_ `virtual void BuildRootCertificateArray() override;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FPlatformSslCertificateManager = FWindowsPlatformSslCertificateManager;`

### `Source/Runtime/Online/SSL/Public/Interfaces/ISslCertificateManager.h` (Public)


#### class `ISslCertificateManager`  
`class ISslCertificateManager`  
_L16-77_
- L19 _public prototype_ `virtual ~ISslCertificateManager() = default;`
- L21 _public member_ `static constexpr int PUBLIC_KEY_DIGEST_SIZE = 32;`
- L28 _public prototype_ `virtual void AddCertificatesToSslContext(SSL_CTX* SslContextPtr) const = 0;` — Add trusted root certificates to the SSL context @param SslContextPtr Ssl context
- L33 _public prototype_ `virtual bool HasCertificatesAvailable() const = 0;` — @return true if certificates are available
- L38 _public prototype_ `virtual void ClearAllPinnedPublicKeys() = 0;` — Clear all pinned keys
- L43 _public prototype_ `virtual bool HasPinnedPublicKeys() const = 0;` — Check if keys have been pinned yet
- L48 _public prototype_ `virtual bool IsDomainPinned(const FString& Domain) = 0;` — Check if the domain is currently pinned
- L56 _public prototype_ `virtual void SetPinnedPublicKeys(const FString& Domain, const FString& PinnedKeyDigests) = 0;` — Set digests for pinned certificate public key for a domain @param Domain Domain the pinned keys are valid for. If Domain starts with a '.' it will match any subdomain @param PinnedKeyDigests Semicolon separated base64 encoded SHA256 digests of pinned public keys
- L66 _public prototype_ `virtual bool VerifySslCertificates(X509_STORE_CTX* Context, const FString& Domain) const = 0;` — Performs additional ssl validation (certificate pinning) @param Context Pointer to the x509 context containing a certificate chain @param Domain Domain we are connected to @return false if validation fails
- L76 _public prototype_ `virtual bool VerifySslCertificates(TArray<TArray<uint8, TFixedAllocator<PUBLIC_KEY_DIGEST_SIZE>>>& Digests, const FString& Domain) const = 0;` — Performs additional ssl validation (certificate pinning) @param Digests Array of public key digests to check against pinned key digests @param Domain Domain we are connected to @return false if validation fails

#### class `FSslCertificateDelegates`  
`class FSslCertificateDelegates`  
_L79-94_
- L92 _public typedef_ `using FVerifySslCertificates = TTSDelegate<bool(const FString&, const TArray<FCertInfo>&)>;`
- L93 _public member_ `static FVerifySslCertificates VerifySslCertificates;`

#### struct `FSslCertificateDelegates::FCertInfo`  
`struct FCertInfo`  
_L82-90_
- L84 _public member_ `static constexpr int CERT_DIGEST_SIZE = 20;`
- L86 _public member_ `TArray<uint8, TInlineAllocator<ISslCertificateManager::PUBLIC_KEY_DIGEST_SIZE>> KeyDigest;`
- L87 _public member_ `TArray<uint8, TInlineAllocator<CERT_DIGEST_SIZE>> Thumbprint;`
- L88 _public member_ `FString Issuer;`
- L89 _public member_ `FString Subject;`

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef struct ssl_ctx_st SSL_CTX;`
- L14 _typedef_ `typedef struct x509_store_ctx_st X509_STORE_CTX;`

### `Source/Runtime/Online/SSL/Public/Interfaces/ISslManager.h` (Public)


#### enum `ESslTlsProtocol`  
`enum class ESslTlsProtocol : uint8`  
_L14-33_
- desc: SSL/TLS protocol
- L17 _public enumerator_ `Minimum = 0` — Start (used for specifying a protocol range)
- L19 _public enumerator_ `SSLv2 = Minimum` — SSLv2
- L21 _public enumerator_ `SSLv3` — SSLv3
- L23 _public enumerator_ `TLSv1` — TLSv1
- L25 _public enumerator_ `TLSv1_1` — TLSv1.1
- L27 _public enumerator_ `TLSv1_2` — TLSv1.2
- L32 _public enumerator_ `Maximum = TLSv1_2` — End (used for specifying a protocol range)

#### struct `FSslContextCreateOptions`  
`struct FSslContextCreateOptions`  
_L38-48_
- desc: Options for creating an SSL context using FSslManager::CreateSslContext
- L41 _public member_ `ESslTlsProtocol MinimumProtocol = ESslTlsProtocol::Minimum;` — Minimum version of SSL/TLS to allow
- L43 _public member_ `ESslTlsProtocol MaximumProtocol = ESslTlsProtocol::Maximum;` — Maximum version of SSL/TLS to allow
- L45 _public member_ `bool bAllowCompression = true;` — Do we want to allow compression?
- L47 _public member_ `bool bAddCertificates = true;` — Automatically add certificates from the certificate manager?

#### class `ISslManager`  
`class ISslManager`  
_L53-82_
- desc: Manager of the ssl library
- L57 _public prototype_ `virtual ~ISslManager() = default;` — Destructor
- L64 _public prototype_ `virtual bool InitializeSsl() = 0;` — Initialize the ssl library.  Can be called multiple times (may not do anything beyond first call). ShutdownSsl must be called once for each call to InitializeSsl @return true if ssl was successfully initialized, false if not
- L69 _public prototype_ `virtual void ShutdownSsl() = 0;` — Shutdown the ssl library.  Must be called once per call to InitializeSsl
- L75 _public prototype_ `virtual SSL_CTX* CreateSslContext(const FSslContextCreateOptions& CreateOptions) = 0;` — Create an SSL context @return an SSL context, may be null if an error occurred
- L81 _public prototype_ `virtual void DestroySslContext(SSL_CTX* SslContext) = 0;` — Destroy an SSL context @param SslContext SSL context to be destroyed

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef struct ssl_ctx_st SSL_CTX;`

### `Source/Runtime/Online/SSL/Public/Ssl.h` (Public)


#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSsl, Warning, All);`

### `Source/Runtime/Online/SSL/Public/SslModule.h` (Public)


#### class `FSslModule`  
`class FSslModule : public IModuleInterface`  
_L18-78_
- inherits: `IModuleInterface`
- desc: Module for SSL/TLS certificate management
- L27 _public prototype_ `FSslModule();` — Constructor
- L35 _public prototype_ `static FSslModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L42 _public function_ `inline ISslCertificateManager& GetCertificateManager()` — Accessor for the SSL certificate manager @return SSL certificate manager manager
- L48 _public function_ `inline ISslManager& GetSslManager()`
- L62 _private prototype_ `virtual void StartupModule() override;` — Called when Http module is loaded Initialize platform specific parts of Http handling
- L68 _private prototype_ `virtual void ShutdownModule() override;` — Called when Http module is unloaded Shutdown platform specific parts of Http handling
- L71 _private member_ `ISslCertificateManager* CertificateManagerPtr;` — Keeps track of SSL certificates
- L74 _private member_ `ISslManager* SslManagerPtr;` — Manager of the SSL library
- L77 _private member_ `static FSslModule* Singleton;` — singleton for the module while loaded and available
