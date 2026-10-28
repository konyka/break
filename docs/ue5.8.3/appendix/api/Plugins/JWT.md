# Plugins / JWT

- module root: `Plugins/Experimental/JWT/Source/JWT`
- headers: 7; symbols: 70
- symbol kinds: class=5, function=5, macro=2, member=17, namespace=2, prototype=39
- PublicDependencyModuleNames: Core, Json, PlatformCrypto, PlatformCryptoContext

### `Plugins/Experimental/JWT/Source/JWT/Public/IJwt.h` (Public)


#### class `IJwt`  
`class IJwt : public IModuleInterface`  
_L15-45_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IJwt& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace JWT` (scope `UE`)
- L49 _prototype_ `TOptional<FJsonWebToken> FromString(const FStringView InEncodedJsonWebToken);` (scope `UE::JWT`)
- L51 _prototype_ `bool FromString(const FStringView InEncodedJWT, FJsonWebToken& OutJsonWebToken);` (scope `UE::JWT`)

### `Plugins/Experimental/JWT/Source/JWT/Public/JsonWebToken.h` (Public)


#### class `FJsonWebToken`  
`class FJsonWebToken`  
_L15-213_
- L28 _public prototype_ `static TOptional<FJsonWebToken> FromString(const FStringView InEncodedJsonWebToken);` — Creates a JWT from the provided string. The string must consist of 3 base64 url encoded parts: a header, payload, and signature. The parts must be split by a period character. The signature part is optional. If the signature is excluded, the string must still contain a period character in its place. Valid formats: "header.payload.signature" and "header.payload." @param InJsonWebTokenString The string to decode. @return An optional set with a FJsonWebToken if the JWT was successfully decoded.
- L30 _public prototype_ `static bool FromString(const FStringView InEncodedJsonWebToken, FJsonWebToken& OutJsonWebToken);`
- L37 _public function_ `const TSharedRef<FJsonObject>& GetPayload() const` — Get raw JSON object for payload, allowing for custom claim parsing with FJsonSerializable classes. @return reference to FJsonObject for the payload.
- L45 _public prototype_ `bool GetType(FString& OutValue) const;` — Gets the type. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L53 _public prototype_ `bool GetKeyId(FString& OutValue) const;` — Gets the key id. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L61 _public prototype_ `bool GetAlgorithm(FString& OutValue) const;` — Gets the algorithm that was used to construct the signature. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L69 _public prototype_ `bool GetIssuer(FString& OutValue) const;` — Gets the issuer domain. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L77 _public prototype_ `bool GetIssuedAt(int64& OutValue) const;` — Gets the issued at timestamp. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L85 _public prototype_ `bool GetExpiration(int64& OutValue) const;` — Gets the expiration timestamp. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L93 _public prototype_ `bool GetNotBefore(int64& OutValue) const;` — Gets the not valid before timestamp. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L101 _public prototype_ `bool GetSubject(FString& OutValue) const;` — Gets the subject. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L109 _public prototype_ `bool GetAudience(FString& OutValue) const;` — Gets the audience. @param OutValue The value to output on success. @return Whether the value exists and was successfully outputted.
- L118 _public prototype_ `bool GetStringClaim(const FString& InName, FString& OutValue) const;` — Get a custom claim by name. @param InName The name of the claim. @param OutValue The value to output on success. @return Whether the claim exists and was successfully outputted.
- L128 _public prototype_ `bool GetClaim(const FStringView InName, TSharedPtr<FJsonValue>& OutClaim) const;` — Gets a claim by name. This method can be used to get custom claims that are not reserved as part of the JWT specification. @param InName The name of the claim. @param OutClaim The json value to output on success. @return Whether the claim exists and was successfully outputted.
- L138 _public function_ `template<EJson JsonType> TSharedPtr<FJsonValue> GetClaim(const FStringView InName) const` — Gets a claim by name. This method can be used to get custom claims that are not reserved as part of the JWT specification. @param InName The name of the claim. @return The json value to output on success, or an invalid shared pointer on failure.
- L148 _public prototype_ `bool HasExpired() const;` — Checks whether the tokens expiration timestamp is in the past. @return Whether the token has expired
- L156 _public prototype_ `bool Verify() const;` — `UE_DEPRECATED(5.3, "Verify() without arguments is deprecated. Please use Verify(Algorithm, ExpectedIssuer) instead.")` — Deprecated method to signature validate the JWT. @return False
- L169 _public prototype_ `bool Verify( const IJwtAlgorithm& Algorithm, const FStringView ExpectedIssuer) const;` — Signature validate and verify the JWT. - Validates the signature against the encoded header and encoded payload - Verifies the basic claims of the JWT - Ensures the issuers match @param Algorithm Implementation of the cryptographic algorithm used for signature validation @param ExpectedIssuer The expected issuer @return Whether the JWT was successfully verified
- L173 _private prototype_ `FJsonWebToken( const FStringView InEncodedHeaderPayload, const TSharedRef<FJsonObject>& InHeaderPtr, const TSharedRef<FJsonObject>& InPayloadPtr, const TOptional<TArray<uint8>>& InSignature);`
- L177 _private prototype_ `static void DumpJsonObject(const FJsonObject& InJsonObject);`
- L179 _private prototype_ `static TSharedPtr<FJsonObject> FromJson(const FString& InJsonStr);`
- L181 _private prototype_ `static TSharedPtr<FJsonObject> ParseEncodedJson(const FStringView InEncodedJson);`
- L185 _public member_ `static const TCHAR *const CLAIM_ISSUER;` — JWT payload registered claim field names
- L186 _public member_ `static const TCHAR *const CLAIM_ISSUED_AT;`
- L187 _public member_ `static const TCHAR *const CLAIM_EXPIRATION;`
- L188 _public member_ `static const TCHAR* const CLAIM_NOT_BEFORE;`
- L189 _public member_ `static const TCHAR *const CLAIM_SUBJECT;`
- L190 _public member_ `static const TCHAR *const CLAIM_AUDIENCE;`
- L193 _public member_ `static const TCHAR* const HEADER_TYPE;` — JWT header field names
- L194 _public member_ `static const TCHAR* const HEADER_KEY_ID;`
- L195 _public member_ `static const TCHAR* const HEADER_ALGORITHM;`
- L198 _public member_ `static const TCHAR* const TYPE_VALUE_JWT;` — JWT header expected values
- L203 _private member_ `FString EncodedHeaderPayload;` — The encoded header and payload parts.
- L206 _private member_ `TSharedRef<FJsonObject> Header;` — The decoded and parsed header.
- L209 _private member_ `TSharedRef<FJsonObject> Payload;` — The decoded and parsed payload.
- L212 _private member_ `TOptional<TArray<uint8>> Signature;` — The decoded signature.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API JWT_API`

### `Plugins/Experimental/JWT/Source/JWT/Public/JwtAlgorithm.h` (Public)


#### class `IJwtAlgorithm`  
`class IJwtAlgorithm`  
_L10-36_
- L15 _public prototype_ `virtual ~IJwtAlgorithm() = default;`
- L22 _public prototype_ `virtual inline const FString& GetAlgString() const = 0;` — Gets the algorithm's string representation.
- L32 _public prototype_ `virtual bool VerifySignature( const TArrayView<const uint8> EncodedMessage, const TArrayView<const uint8> DecodedSignature) const = 0;` — Verifies the decoded signature with the encoded message. @param EncodedMessage The base64 encoded message {header}.{payload} @param DecodedSignature The decoded JWT signature @return Whether the signature was successfully verified.

### `Plugins/Experimental/JWT/Source/JWT/Public/JwtAlgorithms.h` (Public)


#### class `FJwtAlgorithm_RS256`  
`class FJwtAlgorithm_RS256 : public IJwtAlgorithm`  
_L12-72_
- inherits: `IJwtAlgorithm`
- L18 _public prototype_ `FJwtAlgorithm_RS256();`
- L20 _public prototype_ `FJwtAlgorithm_RS256(const FJwtAlgorithm_RS256&) = delete;`
- L22 _public prototype_ `FJwtAlgorithm_RS256& operator=(const FJwtAlgorithm_RS256&) = delete;`
- L24 _public prototype_ `~FJwtAlgorithm_RS256();`
- L30 _public function_ `virtual inline const FString& GetAlgString() const override`
- L35 _public prototype_ `virtual bool VerifySignature( const TArrayView<const uint8> EncodedMessage, const TArrayView<const uint8> DecodedSignature) const override;`
- L48 _public prototype_ `bool SetPublicKey(const FStringView InPemKey);` — Set the public RSA key from PEM. @param InPemKey Key in PEM format as string view @return Whether the operation was successful
- L57 _private prototype_ `void DestroyKey(void* Key);` — Free the RSA key. @param Key The key pointer
- L62 _protected member_ `const FString AlgorithmString = "RS` — Holds the algorithm string.
- L67 _private member_ `TUniquePtr<FEncryptionContext> EncryptionContext = nullptr;` — Holds the unique pointer to the encryption context (OpenSSL/SwitchSSL).
- L70 _private member_ `void* PublicKey = nullptr;` — Holds the public key pointer.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API JWT_API`

### `Plugins/Experimental/JWT/Source/JWT/Public/JwtGlobals.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogJwt, Log, All);`

### `Plugins/Experimental/JWT/Source/JWT/Public/JwtIncludes.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/JWT/Source/JWT/Public/JwtUtils.h` (Public)


#### class `FJwtUtils`  
`class FJwtUtils`  
_L10-79_
- L21 _public prototype_ `static TUniquePtr<FEncryptionContext> GetEncryptionContext();` — Get the pointer to the current platform encryption context (e.g. OpenSSL or SwitchSSL). @return Pointer to the encryption context
- L33 _public prototype_ `static bool SplitStringView( const FStringView InSource, const TCHAR InDelimiter, FStringView& OutLeft, FStringView& OutRight);` — Split a StringView on a delimiter. @param InSource The source string view @param InDelimiter The delimiter @param OutLeft Out string view for the left part @param OutRight Out string view for the right part @return Whether the string view could be split
- L47 _public prototype_ `static bool SplitEncodedJsonWebTokenString( const FStringView InEncodedJsonWebTokenString, FStringView& OutEncodedHeaderPart, FStringView& OutEncodedPayloadPart, FStringView& OutEncodedSignaturePart);` — Split an encoded JWT string into the 3 header, payload, and signature parts. @param InEncodedJsonWebTokenString The JWT string @param OutEncodedHeaderPart Out string for the header part @param OutEncodedPayloadPart Out string for the payload part @param OutEncodedSignaturePart Out string for the signature part @return Whether the JWT string could be split
- L59 _public prototype_ `static bool Base64UrlDecode(const FStringView InSource, FString& OutDest);` — Decode base64 in url-safe mode from string to string. @param InSource The source string @param OutDest The destination string @return Whether the string could be decoded
- L69 _public prototype_ `static bool Base64UrlDecode(const FStringView InSource, TArray<uint8>& OutDest);` — Decode base64 in url-safe mode from string to byte array. @param InSource The source string @param OutDest The destination byte array @return Whether the string could be decoded
- L77 _public prototype_ `static void StringViewToBytes(const FStringView InSource, TArray<uint8>& OutBytes);` — Convert a StringView to a byte array. @param InSource The source string @param OutBytes The destination byte array
