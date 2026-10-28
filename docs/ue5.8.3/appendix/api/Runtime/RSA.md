# Runtime / RSA

- module root: `Source/Runtime/RSA`
- headers: 1; symbols: 9
- symbol kinds: prototype=8, struct=1
- PrivateDependencyModuleNames: Core, OpenSSL

### `Source/Runtime/RSA/Public/RSA.h` (Public)


#### struct `FRSA`  
`struct FRSA`  
_L10-52_
- L16 _public prototype_ `static FRSAKeyHandle CreateKey(const TArray<uint8>& InPublicExponent, const TArray<uint8>& InPrivateExponent, const TArray<uint8>& InModulus);` — Create a new RSA public/private key from the supplied exponents and modulus binary data. Each of these arrays should contain a single little endian large integer value
- L21 _public prototype_ `static void DestroyKey(const FRSAKeyHandle InKey);` — Destroy the supplied key
- L26 _public prototype_ `static int32 GetKeySize(const FRSAKeyHandle InKey);` — Returns the size in bytes of the supplied key
- L31 _public prototype_ `static int32 GetMaxDataSize(const FRSAKeyHandle InKey);` — Returns the maximum number of bytes that can be encrypted in a single payload
- L36 _public prototype_ `static int32 EncryptPublic(const TArrayView<const uint8> InSource, TArray<uint8>& OutDestination, const FRSAKeyHandle InKey);` — Encrypt the supplied byte data using the given public key
- L41 _public prototype_ `static int32 EncryptPrivate(const TArrayView<const uint8> InSource, TArray<uint8>& OutDestination, const FRSAKeyHandle InKey);` — Encrypt the supplied byte data using the given private key
- L46 _public prototype_ `static int32 DecryptPublic(const TArrayView<const uint8> InSource, TArray<uint8>& OutDestination, const FRSAKeyHandle InKey);` — Decrypt the supplied byte data using the given public key
- L51 _public prototype_ `static int32 DecryptPrivate(const TArrayView<const uint8> InSource, TArray<uint8>& OutDestination, const FRSAKeyHandle InKey);` — Decrypt the supplied byte data using the given private key
