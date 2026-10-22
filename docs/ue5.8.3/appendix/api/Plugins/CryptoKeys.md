# Plugins / CryptoKeys

- module root: `Plugins/Editor/CryptoKeys/Source/CryptoKeys`
- headers: 6; symbols: 33
- symbol kinds: class=4, function=2, macro=2, member=13, namespace=2, prototype=9, struct=1
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, CryptoKeysOpenSSL, DeveloperToolSettings, EditorFramework, Engine, GameProjectGeneration, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Editor/CryptoKeys/Source/CryptoKeys/Classes/CryptoKeysCommandlet.h` (Public)


#### class `UCryptoKeysCommandlet`  
`class UCryptoKeysCommandlet : public UCommandlet`  
_L14-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCommandlet`
- desc: Commandlet used to configure project encryption settings
- L19 _private prototype_ `virtual int32 Main(const FString& Params) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CRYPTOKEYS_API`

### `Plugins/Editor/CryptoKeys/Source/CryptoKeys/Classes/CryptoKeysSettings.h` (Public)


#### struct `FCryptoEncryptionKey`  
`struct FCryptoEncryptionKey`  
_L14-26_
- reflection: `USTRUCT()`
- desc: UStruct representing a named encryption key
- L19 _public member_ `FGuid Guid;` — `UPROPERTY(config, VisibleAnywhere, Category = Encryption)`
- L22 _public member_ `FString Name;` — `UPROPERTY(config, EditAnywhere, Category = Encryption)`
- L25 _public member_ `FString Key;` — `UPROPERTY(config, VisibleAnywhere, Category = Encryption)`

#### class `UCryptoKeysSettings`  
`class UCryptoKeysSettings : public UObject`  
_L32-93_
- reflection: `UCLASS(MinimalAPI, config = Crypto, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for imported Paper2D assets, such as sprite sheet textures.
- L38 _public prototype_ `UCryptoKeysSettings();`
- L41 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);`
- L44 _public function_ `bool IsEncryptionEnabled() const`
- L49 _public function_ `bool IsSigningEnabled() const`
- L56 _public member_ `FString EncryptionKey;` — `UPROPERTY(config, VisibleAnywhere, Category = Encryption)` — The default encryption key used to protect pak files
- L60 _public member_ `TArray<FCryptoEncryptionKey> SecondaryEncryptionKeys;` — `UPROPERTY(config, EditAnywhere, Category = Encryption)` — Secondary encryption keys that can be selected for use on different assets. Games are required to make these keys available to the pak platform file at runtime in order to access the data they protect.
- L64 _public member_ `bool bEncryptPakIniFiles;` — `UPROPERTY(config, EditAnywhere, Category = Encryption)` — Encrypts all ini files in the pak. Gives security to the most common sources of mineable information, with minimal runtime IO cost
- L68 _public member_ `bool bEncryptPakIndex;` — `UPROPERTY(config, EditAnywhere, Category = Encryption)` — Encrypt the pak index, making it impossible to use unrealpak to manipulate the pak file without the encryption key
- L72 _public member_ `bool bEncryptUAssetFiles;` — `UPROPERTY(config, EditAnywhere, Category = Encryption)` — Encrypts the uasset file in cooked data. Less runtime IO cost, and protection to package header information, including most string data, but still leaves the bulk of the data unencrypted.
- L76 _public member_ `bool bEncryptAllAssetFiles;` — `UPROPERTY(config, EditAnywhere, Category = Encryption)` — Encrypt all files in the pak file. Secure, but will cause some slowdown to runtime IO performance, and high entropy to packaged data which will be bad for patching
- L80 _public member_ `FString SigningPublicExponent;` — `UPROPERTY(config, VisibleAnywhere, Category = Signing)` — The RSA key public exponent used for signing a pak file
- L84 _public member_ `FString SigningModulus;` — `UPROPERTY(config, VisibleAnywhere, Category = Signing)` — The RSA key modulus used for signing a pak file
- L88 _public member_ `FString SigningPrivateExponent;` — `UPROPERTY(config, VisibleAnywhere, Category = Signing)` — The RSA key private exponent used for signing a pak file
- L92 _public member_ `bool bEnablePakSigning;` — `UPROPERTY(config, EditAnywhere, Category = Signing)` — Enable signing of pak files, to prevent tampering of the data

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CRYPTOKEYS_API`

### `Plugins/Editor/CryptoKeys/Source/CryptoKeys/Private/CryptoKeysHelpers.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace CryptoKeysHelpers`
- L16 _prototype_ `bool GenerateEncryptionKey(FString& OutEncryptionKey);` (scope `CryptoKeysHelpers`) — Generates a new AES key @param OutEncryptionKey - Assigned the base64 encoded representation of the new key @returns true if key generation succeeded, false otherwise
- L26 _prototype_ `bool GenerateSigningKey(FString& OutPublicExponent, FString& OutPrivateExponent, FString& OutModulus, int32 NumKeyBits = 4096);` (scope `CryptoKeysHelpers`) — Generates a new RSA signing key @param OutPublicExponent 	- Assigned the base64 encoded representation of the RSA public exponent @param OutPrivateExponent 	- Assigned the base64 encoded representation of the RSA private exponent @param OutModulus		 Assigned the base64 encoded representation of the RSA modulus @param InNumKeyBits 		- How many bits to use for the RSA key @returns true if key generation succeeded, false otherwise

### `Plugins/Editor/CryptoKeys/Source/CryptoKeys/Private/CryptoKeysProjectBuildMutatorFeature.h` (Private)


#### class `FCryptoKeysProjectBuildMutatorFeature`  
`class FCryptoKeysProjectBuildMutatorFeature : public IProjectBuildMutatorFeature`  
_L7-11_
- inherits: `IProjectBuildMutatorFeature`
- L10 _public prototype_ `virtual bool RequiresProjectBuild(const FName& InPlatformInfoName, FText& OutReason) const override;`

### `Plugins/Editor/CryptoKeys/Source/CryptoKeys/Private/CryptoKeysSettingsDetails.h` (Private)


#### class `FCryptoKeysSettingsDetails`  
`class FCryptoKeysSettingsDetails : public IDetailCustomization`  
_L7-15_
- inherits: `IDetailCustomization`
- L11 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Editor/CryptoKeys/Source/CryptoKeys/Public/CryptoKeys.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace CryptoKeys`
- L11 _prototype_ `void GenerateEncryptionKey(FString& OutBase64Key);` (scope `CryptoKeys`)
