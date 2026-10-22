# Plugins / ElectraCDM

- module root: `Plugins/Media/ElectraCDM/Source/ElectraCDM`
- headers: 12; symbols: 180
- symbol kinds: class=10, delegate=1, enum=6, enumerator=29, macro=7, member=19, namespace=10, prototype=92, struct=6
- PublicDependencyModuleNames: Core, Json

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Private/3rdParty/tiny-AES-c/aes.h` (Private)


#### struct `TinyAES128::AES_ctx`  
`struct AES_ctx`  
_L46-52_
- L48 _public member_ `uint8_t RoundKey[TINYAES_AES_keyExpSize];`
- L50 _public member_ `uint8_t Iv[TINYAES_AES_BLOCKLEN];`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace TinyAES128`
- L17 _macro_ `#define TINYAES_CBC 1`
- L29 _macro_ `#define TINYAES_AES128 1`
- L33 _macro_ `#define TINYAES_AES_BLOCKLEN 16 //Block length in bytes AES is 128b block only`
- L36 _macro_ `#define TINYAES_AES_KEYLEN 32`
- L37 _macro_ `#define TINYAES_AES_keyExpSize 240`
- L54 _prototype_ `void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);` (scope `TinyAES128`)
- L56 _prototype_ `void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);` (scope `TinyAES128`)
- L57 _prototype_ `void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv);` (scope `TinyAES128`)
- L64 _prototype_ `void AES_ECB_encrypt(const struct AES_ctx* ctx, uint8_t* buf);` (scope `TinyAES128`) — buffer size is exactly TINYAES_AES_BLOCKLEN bytes; you need only AES_init_ctx as IV is not used in ECB NB: ECB is considered insecure for most uses
- L65 _prototype_ `void AES_ECB_decrypt(const struct AES_ctx* ctx, uint8_t* buf);` (scope `TinyAES128`)
- L75 _prototype_ `void AES_CBC_encrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);` (scope `TinyAES128`) — buffer size MUST be mutile of TINYAES_AES_BLOCKLEN; Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme NOTES: you need to set IV in ctx via AES_init_ctx_iv() or AES_ctx_set_iv() no IV should ever be reused with the same key
- L76 _prototype_ `void AES_CBC_decrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);` (scope `TinyAES128`)
- L88 _prototype_ `void AES_CTR_xcrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);` (scope `TinyAES128`) — Same function for encrypting as for decrypting. IV is incremented for every block, and used after encryption as XOR-compliment for output Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme NOTES: you need to set IV in ctx with AES_init_ctx_iv() or AES_ctx_set_iv() no IV should ever be reused with the same key

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Private/ClearKey/ClearKeyCDM.h` (Private)


#### class `ElectraCDM::IClearKeyCDM`  
`class IClearKeyCDM : public IMediaCDMSystem`  
_L11-46_
- inherits: `IMediaCDMSystem`
- L14 _public prototype_ `static void RegisterWith(IMediaCDM& InDRMManager);`
- L15 _public prototype_ `virtual ~IClearKeyCDM() = default;`
- L16 _public prototype_ `virtual FString GetLastErrorMessage() = 0;`
- L17 _public prototype_ `virtual const TArray<FString>& GetSchemeIDs() = 0;`
- L41 _public prototype_ `virtual void GetCDMCustomJSONPrefixes(FString& OutAttributePrefix, FString& OutTextPropertyName, bool& bOutNoNamespaces) = 0;` — Elements that are parsed from a XML document, like: <ContentProtection schemeIdUri="urn:uuid:e2719d58-a985-b3c9-781a-b030af78d30e" value="ClearKey1.0"> <clearkey:Laurl Lic_type="EME-1.0">https://clearkey.example.com/AcquireLicense</clearkey:Laurl> <dashif:laurl>https://clearkey2.example.com/AcquireLicense</dashif:laurl> <cenc:pssh>YmFzZTY0IGVuY29kZWQgY29udGVudHMgb2YgkXBzc2iSIGJveCB3aXRoIHRoaXMgU3lzdGVtSUQ=</cenc:pssh> <ContentProtection> have these elements converted into JSON like: { "Laurl": { "Lic_type": "EME-1.0", "#text": "https://clearkey.example.com/AcquireLicense" }, "laurl": "https://clearkey2.example.com/AcquireLicense", "pssh": "YmFzZTY0IGVuY29kZWQgY29udGVudHMgb2YgkXBzc2iSIGJveCB3aXRoIHRoaXMgU3lzdGVtSUQ=" } where the text of the XML element is put into a property named "#text". XML namespaces are removed in this example (bOutNoNamespaces returned 'true') and no attribute prefix was set.
- L43 _public prototype_ `virtual TSharedPtr<IMediaCDMCapabilities, ESPMode::ThreadSafe> GetCDMCapabilities(const FString& InValue, const FString& InAdditionalElements) = 0;`
- L44 _public prototype_ `virtual ECDMError CreateDRMClient(TSharedPtr<IMediaCDMClient, ESPMode::ThreadSafe>& OutClient, IMediaCDM::IPlayerSession* InForPlayerSession, const TArray<IMediaCDM::FCDMCandidate>& InCandidates) = 0;`
- L45 _public prototype_ `virtual ECDMError ReleasePlayerSessionKeys(IMediaCDM::IPlayerSession* PlayerSession) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Private/ElectraCDMModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraCDM, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraCDM, Log, All);`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Private/ElectraCDMUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ElectraCDMUtils`
- L9 _prototype_ `FString Base64UrlEncode(const TArray<uint8>& InData);` (scope `ElectraCDMUtils`)
- L10 _prototype_ `bool Base64UrlDecode(TArray<uint8>& OutData, FString InString);` (scope `ElectraCDMUtils`)
- L11 _prototype_ `FString StripDashesFromKID(const FString& InKID);` (scope `ElectraCDMUtils`)
- L12 _prototype_ `void ConvertKIDToBin(TArray<uint8>& OutBinKID, const FString& InKID);` (scope `ElectraCDMUtils`)
- L13 _prototype_ `FString ConvertKIDToBase64(const FString& InKID);` (scope `ElectraCDMUtils`)
- L14 _prototype_ `void StringToArray(TArray<uint8>& OutArray, const FString& InString);` (scope `ElectraCDMUtils`)
- L15 _prototype_ `FString ArrayToString(const TArray<uint8>& InArray, int32 InStartAt=0);` (scope `ElectraCDMUtils`)

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Private/HLS_AES128/HLS_AES128CDM.h` (Private)


#### class `ElectraCDM::IHLS_AES128_CDM`  
`class IHLS_AES128_CDM : public IMediaCDMSystem`  
_L11-24_
- inherits: `IMediaCDMSystem`
- L14 _public prototype_ `static void RegisterWith(IMediaCDM& InDRMManager);`
- L15 _public prototype_ `virtual ~IHLS_AES128_CDM() = default;`
- L16 _public prototype_ `virtual FString GetLastErrorMessage() = 0;`
- L17 _public prototype_ `virtual const TArray<FString>& GetSchemeIDs() = 0;`
- L19 _public prototype_ `virtual void GetCDMCustomJSONPrefixes(FString& OutAttributePrefix, FString& OutTextPropertyName, bool& bOutNoNamespaces) = 0;`
- L21 _public prototype_ `virtual TSharedPtr<IMediaCDMCapabilities, ESPMode::ThreadSafe> GetCDMCapabilities(const FString& InValue, const FString& InAdditionalElements) = 0;`
- L22 _public prototype_ `virtual ECDMError CreateDRMClient(TSharedPtr<IMediaCDMClient, ESPMode::ThreadSafe>& OutClient, IMediaCDM::IPlayerSession* InForPlayerSession, const TArray<IMediaCDM::FCDMCandidate>& InCandidates) = 0;`
- L23 _public prototype_ `virtual ECDMError ReleasePlayerSessionKeys(IMediaCDM::IPlayerSession* PlayerSession) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Public/Crypto/StreamCryptoAES128.h` (Public)


#### class `ElectraCDM::IStreamDecrypterAES128`  
`class IStreamDecrypterAES128`  
_L16-46_
- L19 _public prototype_ `static TSharedPtr<IStreamDecrypterAES128, ESPMode::ThreadSafe> Create();`
- L20 _public prototype_ `virtual ~IStreamDecrypterAES128() = default;`
- L32 _public prototype_ `static const TCHAR* GetResultText(EResult ResultCode);`
- L34 _public prototype_ `static EResult ConvHexStringToBin(TArray<uint8>& OutBinData, const char* InHexString);`
- L35 _public prototype_ `static void MakePaddedIVFromUInt64(TArray<uint8>& OutBinData, uint64 lower64Bits);`
- L37 _public prototype_ `virtual EResult CBCInit(const TArray<uint8>& Key, const TArray<uint8>* OptionalIV=nullptr) = 0;`
- L38 _public prototype_ `virtual EResult CBCDecryptInPlace(int32& OutNumBytes, uint8* InOutData, int32 NumBytes16, bool bIsFinalBlock) = 0;`
- L39 _public prototype_ `virtual int32 CBCGetEncryptionDataSize(int32 PlaintextSize) = 0;`
- L40 _public prototype_ `virtual EResult CBCEncryptInPlace(int32& OutNumBytes, uint8* InOutData, int32 NumBytes, bool bIsFinalData) = 0;`
- L42 _public prototype_ `virtual EResult CTRInit(const TArray<uint8>& Key) = 0;`
- L43 _public prototype_ `virtual EResult CTRSetKey(const TArray<uint8>& Key) = 0;`
- L44 _public prototype_ `virtual EResult CTRSetIV(const TArray<uint8>& IV) = 0;`
- L45 _public prototype_ `virtual EResult CTRDecryptInPlace(uint8* InOutData, int32 InNumBytes) = 0;`

#### enum `ElectraCDM::IStreamDecrypterAES128::EResult`  
`enum class EResult`  
_L22-31_
- L24 _public enumerator_ `Ok`
- L25 _public enumerator_ `NotInitialized`
- L26 _public enumerator_ `BadKeyLength`
- L27 _public enumerator_ `BadIVLength`
- L28 _public enumerator_ `BadDataLength`
- L29 _public enumerator_ `InvalidArg`
- L30 _public enumerator_ `BadHexChar`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ELECTRACDM_API`
- L9 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Public/ElectraCDM.h` (Public)


#### class `ElectraCDM::IMediaCDMCapabilities`  
`class IMediaCDMCapabilities`  
_L34-70_
- L37 _public prototype_ `virtual ~IMediaCDMCapabilities() = default;`
- L61 _public prototype_ `virtual ESupportResult SupportsCipher(const FString& InCipherType) = 0;` — Returns if a specified cipher (eg. "cenc" or "cbcs") is supported by this CDM.
- L64 _public prototype_ `virtual ESupportResult SupportsType(const FString& InMimeType) = 0;` — Returns if a specified media type is supported by this CDM.
- L69 _public prototype_ `virtual ESupportResult RequiresSecureDecoder(const FString& InMimeType) = 0;` — Returns if a secure decoder is required for the specified media type. This SHOULD be able to return the proper answer WITHOUT having acquired a license since this is may be used to select/deselect streams upfront.

#### enum `ElectraCDM::IMediaCDMCapabilities::ESupportResult`  
`enum class ESupportResult`  
_L39-58_
- L42 _public enumerator_ `Supported` — The media type is supported.
- L44 _public enumerator_ `NotSupported` — The media type is not supported.
- L47 _public enumerator_ `CodecRequired` — The specified MIME type needs to provide the "codecs" information to determine whether or not the type is supported.
- L50 _public enumerator_ `FeatureRequired` — The specified MIME type needs to provide feature information to determine whether or not the type is supported. (eg.: resolution=WxH)
- L52 _public enumerator_ `BadMIMEType` — Failed to parse the MIME type string. Check if it is of correct syntax.
- L55 _public enumerator_ `SecureDecoderRequired` — Secure decoder required.
- L57 _public enumerator_ `SecureDecoderNotRequired` — Secure decoder not required.

#### class `ElectraCDM::IMediaCDM`  
`class IMediaCDM`  
_L73-134_
- L76 _public prototype_ `static IMediaCDM& Get();`
- L81 _public prototype_ `virtual void RegisterCDM(TWeakPtr<IMediaCDMSystem, ESPMode::ThreadSafe> InCDMSystem) = 0;` — CDM registration
- L87 _public prototype_ `virtual void GetCDMCustomJSONPrefixes(const FString& InCDMScheme, const FString& InValue, FString& OutAttributePrefix, FString& OutTextPropertyName, bool& bOutNoNamespaces) = 0;` — Obtains the CDM system's preference on how attributes and text properties should be prefixed in the JSON string passed to GetCDMCapabilitiesForScheme(..., InAdditionalElements) or in the FCDMCandidate.AdditionalElements.
- L95 _public prototype_ `virtual TSharedPtr<IMediaCDMCapabilities, ESPMode::ThreadSafe> GetCDMCapabilitiesForScheme(const FString& InCDMScheme, const FString& InValue, const FString& InAdditionalElements) = 0;` — CDM system capabilities Returns an interface to a CDM system's capabilities. The system is identified through its unique scheme id (a UUID). If there is no CDM system for the given scheme a nullptr is returned.
- L101 _public prototype_ `virtual FString GetLastErrorMessage() = 0;` — State
- L111 _public prototype_ `virtual IPlayerSession* CreatePlayerSessionID() = 0;`
- L113 _public prototype_ `virtual void ReleasePlayerSessionID(IPlayerSession* InPlayerSessionToRelease) = 0;` — Releases the specified player session and its associated keys.
- L126 _public prototype_ `virtual ECDMError CreateDRMClient(TSharedPtr<IMediaCDMClient, ESPMode::ThreadSafe>& OutClient, IPlayerSession* InForPlayerSession, const TArray<FCDMCandidate>& InCandidates) = 0;` — Create a single client from all the given candidates. Candidates are those whose capabilities said they are able to decrypt a particular stream. The object of this method is to settle on one CDM system (in case several claimed capability to decrypt). Returns Success or Failure if different types of streams would be using a different type of CDM.
- L130 _public prototype_ `virtual ECDMError ReleasePlayerSessionKeys(IPlayerSession* InPlayerSession) = 0;` — Releases all license keys associated by the specified session. Must be called before calling ReleasePlayerSessionID().
- L133 _protected prototype_ `virtual ~IMediaCDM() = default;`

#### struct `ElectraCDM::IMediaCDM::FCDMCandidate`  
`struct FCDMCandidate`  
_L115-122_
- L117 _public member_ `FString SchemeId;`
- L118 _public member_ `FString Value;`
- L119 _public member_ `FString CommonScheme;`
- L120 _public member_ `FString AdditionalElements;`
- L121 _public member_ `TArray<FString> DefaultKIDs;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ELECTRACDM_API`
- L11 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Public/ElectraCDMClient.h` (Public)


#### class `ElectraCDM::IMediaCDMEventListener`  
`class IMediaCDMEventListener`  
_L22-43_
- desc: Event listener to be registered with a CDM client. This must be implemented by the application to be notified about the CDM client's needs that need to be satisfied, like performing license acquisition.
- L25 _public prototype_ `virtual ~IMediaCDMEventListener() = default;`
- L42 _public prototype_ `virtual void OnCDMEvent(ECDMEventType InEventType, TSharedPtr<ElectraCDM::IMediaCDMClient, ESPMode::ThreadSafe> InDrmClient, void* InEventId, const TArray<uint8>& InCustomData) = 0;` — An event triggered by a CDM system that needs to be processed by the applicate. Please note that the InDrmClient may be an intermediate client your application did NOT create! Do not perform checks on the client pointer. Also do not use this client to perform any operation other than to return the requested data, if the event is a data request. You have to return the opaque InEventId in the reply (see SetLicenseKeyResponseData()).

#### enum `ElectraCDM::IMediaCDMEventListener::ECDMEventType`  
`enum class ECDMEventType`  
_L27-32_
- L29 _public enumerator_ `ProvisionRequired`
- L30 _public enumerator_ `KeyRequired`
- L31 _public enumerator_ `KeyExpired`

#### class `ElectraCDM::IMediaCDMClient`  
`class IMediaCDMClient`  
_L54-105_
- desc: CDM client This interfaces the application with the CDM system. An application can use multiple clients if necessary.
- L57 _public prototype_ `virtual ~IMediaCDMClient() = default;`
- L64 _public prototype_ `virtual void RegisterEventListener(TWeakPtr<IMediaCDMEventListener, ESPMode::ThreadSafe> InEventListener) = 0;` — Application event listener methods. Registers an application event listener to receive OnCDMEvent() messages.
- L66 _public prototype_ `virtual void UnregisterEventListener(TWeakPtr<IMediaCDMEventListener, ESPMode::ThreadSafe> InEventListener) = 0;` — Unregisters a previously registered event listener.
- L72 _public prototype_ `virtual ECDMState GetState() = 0;` — State
- L74 _public prototype_ `virtual FString GetLastErrorMessage() = 0;`
- L81 _public prototype_ `virtual void PrepareLicenses() = 0;` — License acquisition Prepares the client for license acquisition based on the configuration passed in IMediaCDM::CreateDRMClient()
- L90 _public prototype_ `virtual void SetLicenseServerURL(const FString& InLicenseServerURL) = 0;` — Overrides the URL to the license server that may have been set in the initial configuration data.
- L92 _public prototype_ `virtual void GetLicenseKeyURL(FString& OutLicenseURL) = 0;` — Returns the URL to the license server, either from configuration data or the overrride.
- L94 _public prototype_ `virtual void GetLicenseKeyRequestData(TArray<uint8>& OutKeyRequestData, FString& OutHttpMethod, TArray<FString>& OutHttpHeaders, uint32& OutFlags) = 0;` — Returns the data to send to the license server as well as the HTTP method and additional HTTP headers.
- L97 _public prototype_ `virtual ECDMError SetLicenseKeyResponseData(void* InEventId, int32 HttpResponseCode, const TArray<uint8>& InKeyResponseData) = 0;` — Sets the license server's response data. This will, if successful, also update any already existing decrypters with the keys. The EventId must be the one received in OnCDMEvent().
- L104 _public prototype_ `virtual ECDMError CreateDecrypter(TSharedPtr<IMediaCDMDecrypter, ESPMode::ThreadSafe>& OutDecrypter, const FString& InMimeType) = 0;` — Decrypter Creates a decrypter for the specified MIME type.

#### enum `ElectraCDM::IMediaCDMClient::EDRMClientFlags`  
`enum EDRMClientFlags`  
_L83-87_
- L85 _public enumerator_ `EDRMFlg_None = 0`
- L86 _public enumerator_ `EDRMFlg_AllowCustomKeyStorage = 1U << 31`

#### class `ElectraCDM::IMediaCDMDecrypter`  
`class IMediaCDMDecrypter`  
_L112-157_
- desc: Decrypter instance.
- L115 _public prototype_ `virtual ~IMediaCDMDecrypter() = default;`
- L120 _public prototype_ `virtual ECDMState GetState() = 0;` — State
- L121 _public prototype_ `virtual FString GetLastErrorMessage() = 0;`
- L128 _public prototype_ `virtual ECDMError UpdateInitDataFromPSSH(const TArray<uint8>& InPSSHData) = 0;` — License update Update from PSSH boxes encountered in the stream.
- L129 _public prototype_ `virtual ECDMError UpdateInitDataFromMultiplePSSH(const TArray<TArray<uint8>>& InPSSHData) = 0;`
- L132 _public prototype_ `virtual ECDMError UpdateFromURL(const FString& InURL, const FString& InAdditionalElements) = 0;` — Update from a URL and additional scheme specific elements.
- L140 _public prototype_ `virtual bool IsBlockStreamDecrypter() = 0;` — Returns if this decrypter needs to work in block streaming mode (based on the encryption settings).
- L143 _public prototype_ `virtual void Reinitialize() = 0;` — Reinitializes the decrypter to its starting state. This should not normally be called unless an error occurred.
- L146 _public prototype_ `virtual ECDMError DecryptInPlace(uint8* InOutData, int32 InNumDataBytes, const FMediaCDMSampleInfo& InSampleInfo) = 0;` — Decrypt a non-block oriented cipher (eg. AES 128 CTR) in place.
- L154 _public prototype_ `virtual ECDMError BlockStreamDecryptStart(IStreamDecryptHandle*& OutStreamDecryptContext, const FMediaCDMSampleInfo& InSampleInfo) = 0;`
- L155 _public prototype_ `virtual ECDMError BlockStreamDecryptInPlace(IStreamDecryptHandle* InOutStreamDecryptContext, int32& OutNumBytesDecrypted, uint8* InOutData, int32 InNumDataBytes, bool bIsLastBlock) = 0;`
- L156 _public prototype_ `virtual ECDMError BlockStreamDecryptEnd(IStreamDecryptHandle* InStreamDecryptContext) = 0;`

#### struct `ElectraCDM::IMediaCDMDecrypter::IStreamDecryptHandle`  
`struct IStreamDecryptHandle`  
_L150-153_
- desc: Decrypt a streaming cipher that requires input of fixed cipher block lengths and possibly padding at the end (eg. AES 128 CBC with PKCS#7 padding). This needs a running state during decryption that needs to be created and released.
- L152 _public member_ `int32 BlockSize = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Public/ElectraCDMError.h` (Public)


#### enum `ElectraCDM::ECDMError`  
`enum class ECDMError`  
_L11-17_
- L13 _public enumerator_ `Success`
- L14 _public enumerator_ `Failure`
- L15 _public enumerator_ `NotSupported`
- L16 _public enumerator_ `CipherModeMismatch`

#### enum `ElectraCDM::ECDMState`  
`enum class ECDMState`  
_L20-28_
- L22 _public enumerator_ `Idle`
- L23 _public enumerator_ `WaitingForKey`
- L24 _public enumerator_ `Ready`
- L25 _public enumerator_ `InvalidKey`
- L26 _public enumerator_ `KeyExpired`
- L27 _public enumerator_ `ConfigurationError`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Public/ElectraCDMSystem.h` (Public)


#### class `ElectraCDM::IMediaCDMSystem`  
`class IMediaCDMSystem`  
_L12-28_
- L15 _public prototype_ `virtual FString GetLastErrorMessage() = 0;`
- L17 _public prototype_ `virtual const TArray<FString>& GetSchemeIDs() = 0;`
- L19 _public prototype_ `virtual void GetCDMCustomJSONPrefixes(FString& OutAttributePrefix, FString& OutTextPropertyName, bool& bOutNoNamespaces) = 0;`
- L21 _public prototype_ `virtual TSharedPtr<IMediaCDMCapabilities, ESPMode::ThreadSafe> GetCDMCapabilities(const FString& InValue, const FString& InAdditionalElements) = 0;`
- L23 _public prototype_ `virtual ECDMError CreateDRMClient(TSharedPtr<IMediaCDMClient, ESPMode::ThreadSafe>& OutClient, IMediaCDM::IPlayerSession* InForPlayerSession, const TArray<IMediaCDM::FCDMCandidate>& InCandidates) = 0;`
- L24 _public prototype_ `virtual ECDMError ReleasePlayerSessionKeys(IMediaCDM::IPlayerSession* PlayerSession) = 0;`
- L27 _protected prototype_ `virtual ~IMediaCDMSystem() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Public/ElectraEncryptedSampleInfo.h` (Public)


#### struct `ElectraCDM::FMediaCDMSampleInfo`  
`struct FMediaCDMSampleInfo`  
_L12-31_
- L25 _public member_ `TArray<uint8> DefaultKID;`
- L26 _public member_ `TArray<TArray<uint8>> KIDs;`
- L27 _public member_ `TArray<uint8> IV;`
- L28 _public member_ `TArray<FSubSample> SubSamples;`
- L29 _public member_ `FCryptSkipPattern Pattern;`
- L30 _public member_ `uint32 Scheme4CC = 0;`

#### struct `ElectraCDM::FMediaCDMSampleInfo::FSubSample`  
`struct FSubSample`  
_L14-18_
- L16 _public member_ `uint16 NumClearBytes = 0;`
- L17 _public member_ `uint32 NumEncryptedBytes = 0;`

#### struct `ElectraCDM::FMediaCDMSampleInfo::FCryptSkipPattern`  
`struct FCryptSkipPattern`  
_L19-24_
- L21 _public member_ `uint8 PatternType = 0;`
- L22 _public member_ `uint8 CryptByteBlock = 0;`
- L23 _public member_ `uint8 SkipByteBlock = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ElectraCDM`

### `Plugins/Media/ElectraCDM/Source/ElectraCDM/Public/IElectraCDMModule.h` (Public)


#### class `IElectraCDMModule`  
`class IElectraCDMModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- desc: Interface for the `ElectraCDM` module.
- L16 _public prototype_ `virtual ~IElectraCDMModule() = default;`
