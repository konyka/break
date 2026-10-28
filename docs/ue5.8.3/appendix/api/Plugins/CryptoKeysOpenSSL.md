# Plugins / CryptoKeysOpenSSL

- module root: `Plugins/Editor/CryptoKeys/Source/CryptoKeysOpenSSL`
- headers: 1; symbols: 3
- symbol kinds: namespace=1, prototype=2
- PrivateDependencyModuleNames: OpenSSL
- PrivateIncludePathModuleNames: CryptoKeys
- PublicDependencyModuleNames: Core

### `Plugins/Editor/CryptoKeys/Source/CryptoKeysOpenSSL/Public/CryptoKeysOpenSSL.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace CryptoKeysOpenSSL`
- L8 _prototype_ `bool GenerateNewEncryptionKey(TArray<uint8>& OutKey);` (scope `CryptoKeysOpenSSL`)
- L9 _prototype_ `bool GenerateNewSigningKey(TArray<uint8>& OutPublicExponent, TArray<uint8>& OutPrivateExponent, TArray<uint8>& OutModulus, int32 InNumKeyBits = 2048);` (scope `CryptoKeysOpenSSL`)
