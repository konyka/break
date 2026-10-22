# Plugins / OnlineServicesEpicCommon

- module root: `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon`
- headers: 7; symbols: 86
- symbol kinds: class=6, enum=1, enumerator=4, function=7, macro=1, member=10, namespace=15, prototype=36, struct=2, typedef=4
- PrivateDependencyModuleNames: EOSSDK, EOSShared, OnlineServicesInterface
- PublicDependencyModuleNames: Core, OnlineServicesCommon

### `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon/Private/Online/OnlineServicesEpicCommonPlatformFactory.h` (Private)


#### class `UE::Online::FOnlineServicesEpicCommonPlatformFactory`  
`class FOnlineServicesEpicCommonPlatformFactory`  
_L16-44_
- desc: Factory class to create EOS Platforms for online services
- L23 _public prototype_ `static FOnlineServicesEpicCommonPlatformFactory& Get();` — Get the platform factory @return the platform factory singleton
- L27 _public prototype_ `static void TearDown();` — Tear down the singleton instance. This only cleans up the singleton and has no impact on any platform handles created by this (aside from DefaultEOSPlatformHandle's ref count decreasing).
- L36 _public prototype_ `IEOSPlatformHandlePtr CreatePlatform(FName InstanceName, FName InstanceConfigName);` — Create a new platform instance for the given Instance/Config pair. Note If InstanceConfigName = NAME_None, this will attempt to resolve a config to use from various sources, including OnlineServices config, and EOSSDKManager cached configs. @param InstanceName the "instance", typically a WorldContextHandle @param InstanceConfigName the named EOS platform config to use @return a new platform, or null on failure
- L39 _private prototype_ `FOnlineServicesEpicCommonPlatformFactory() = default;`
- L41 _private prototype_ `FString LoadEOSPlatformConfig(IEOSSDKManager* const SDKManager);`

#### Free symbols / members of external scopes

- L9 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle>;`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon/Public/Online/EOSAuthLoginOptionsCommon.h` (Public)


#### enum `UE::Online::EEOSAuthTranslationFlags`  
`enum class EEOSAuthTranslationFlags : uint8`  
_L16-22_
- L18 _public enumerator_ `None = 0`
- L19 _public enumerator_ `SetId = 1 << 0`
- L20 _public enumerator_ `SetTokenFromString = 1 << 1`
- L21 _public enumerator_ `SetTokenFromExternalAuth = 1 << 2`

#### struct `UE::Online::FEOSAuthTranslationTraits`  
`struct FEOSAuthTranslationTraits`  
_L25-29_
- L27 _public member_ `EOS_ELoginCredentialType Type = EOS_ELoginCredentialType::EOS_LCT_Password;`
- L28 _public member_ `EEOSAuthTranslationFlags Flags = EEOSAuthTranslationFlags::None;`

#### struct `UE::Online::FEOSExternalAuthTranslationTraits`  
`struct FEOSExternalAuthTranslationTraits`  
_L31-35_
- L33 _public member_ `EOS_EExternalCredentialType Type = EOS_EExternalCredentialType::EOS_ECT_EPIC;`
- L34 _public member_ `EOS_ELinkAccountFlags LinkAccountFlags = EOS_ELinkAccountFlags::EOS_LA_NoFlags;`

#### class `UE::Online::FEOSAuthLoginOptionsCommon`  
`class FEOSAuthLoginOptionsCommon : public EOS_Auth_LoginOptions`  
_L37-59_
- inherits: `EOS_Auth_LoginOptions`
- L40 _public prototype_ `FEOSAuthLoginOptionsCommon(const FEOSAuthLoginOptionsCommon&) = delete;`
- L41 _public prototype_ `FEOSAuthLoginOptionsCommon& operator=(const FEOSAuthLoginOptionsCommon&) = delete;`
- L42 _public prototype_ `FEOSAuthLoginOptionsCommon(FEOSAuthLoginOptionsCommon&&);`
- L43 _public prototype_ `FEOSAuthLoginOptionsCommon& operator=(FEOSAuthLoginOptionsCommon&&);`
- L45 _public function_ `EOS_ELinkAccountFlags GetLinkAccountFlags() const`
- L48 _protected prototype_ `FEOSAuthLoginOptionsCommon();`
- L50 _protected prototype_ `static const FEOSAuthTranslationTraits* GetLoginTranslatorTraits(FName Name);`
- L51 _protected prototype_ `static const FEOSExternalAuthTranslationTraits* GetExternalAuthTranslationTraits(FName ExternalAuthType);`
- L53 _protected function_ `static bool InitSystemAuthCredentialOptions(FEOSAuthLoginOptionsCommon& Options)`
- L55 _protected member_ `EOS_Auth_Credentials CredentialsData;`
- L56 _protected member_ `EOS_ELinkAccountFlags LinkAccountFlags = EOS_ELinkAccountFlags::EOS_LA_NoFlags;`
- L57 _protected member_ `TArray<char> IdUtf8;`
- L58 _protected member_ `TArray<char> TokenUtf8;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L23 _prototype_ `ENUM_CLASS_FLAGS(EEOSAuthTranslationFlags);` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon/Public/Online/EpicAccountIdResolver.h` (Public)


#### class `UE::Online::IEpicAccountIdResolver`  
`class IEpicAccountIdResolver`  
_L14-22_
- desc: Exists to provide components that are instantiated in both OnlineServicesEOS and OnlineServicesEpicAccount a resolve path that works in both.
- L17 _public prototype_ `virtual TFuture<FAccountId> ResolveAccountId(const FAccountId LocalAccountId, const EOS_EpicAccountId EpicAccountId) = 0;`
- L18 _public prototype_ `virtual TFuture<TArray<FAccountId>> ResolveAccountIds(const FAccountId LocalAccountId, const TArray<EOS_EpicAccountId>& EpicAccountIds) = 0;`
- L20 _public prototype_ `TFunction<TFuture<FAccountId>(class FOnlineAsyncOp& InAsyncOp, const EOS_EpicAccountId EpicAccountId)> ResolveEpicAccountIdFn();`
- L21 _public prototype_ `TFunction<TFuture<TArray<FAccountId>>(class FOnlineAsyncOp& InAsyncOp, const TArray<EOS_EpicAccountId>& EpicAccountIds)> ResolveEpicAccountIdsFn();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon/Public/Online/EpicProductUserIdResolver.h` (Public)


#### class `UE::Online::IEpicProductUserIdResolver`  
`class IEpicProductUserIdResolver`  
_L14-22_
- desc: Exists to provide components that are instantiated in both OnlineServicesEOSGS and OnlineServicesEpicGame a resolve path that works in both.
- L17 _public prototype_ `virtual TFuture<FAccountId> ResolveAccountId(const FAccountId LocalAccountId, const EOS_ProductUserId ProductUserId) = 0;`
- L18 _public prototype_ `virtual TFuture<TArray<FAccountId>> ResolveAccountIds(const FAccountId LocalAccountId, const TArray<EOS_ProductUserId>& ProductUserIds) = 0;`
- L20 _public prototype_ `TFunction<TFuture<FAccountId>(class FOnlineAsyncOp& InAsyncOp, const EOS_ProductUserId ProductUserId)> ResolveProductUserIdFn();`
- L21 _public prototype_ `TFunction<TFuture<TArray<FAccountId>>(class FOnlineAsyncOp& InAsyncOp, const TArray<EOS_ProductUserId>& ProductUserIds)> ResolveProductUserIdsFn();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon/Public/Online/OnlineErrorEpicCommon.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L15 _namespace_ `namespace Errors` (scope `UE::Online`)
- L19 _typedef_ `typedef TFunction<FOnlineError(FOnlineError&& Error, EOS_EResult Result)> FErrorMapperEosFn;` (scope `UE::Online::Errors`)
- L21 _prototype_ `FOnlineError MapCommonEOSError(FOnlineError&& Error, EOS_EResult Result);` (scope `UE::Online::Errors`)
- L22 _prototype_ `ErrorCodeType ErrorCodeFromEOSResult(EOS_EResult Result);` (scope `UE::Online::Errors`)
- L23 _prototype_ `FOnlineError FromEOSResult(EOS_EResult Result, FErrorMapperEosFn&& MapperFn = &MapCommonEOSError);` (scope `UE::Online::Errors`)
- L28 _function_ `inline bool operator==(const UE::Online::FOnlineError& OnlineError, EOS_EResult EosResult)` — These are extern'd out of the namespace for some of the Catch API that can't see these operators if they are inside
- L33 _function_ `inline bool operator==(EOS_EResult EosResult, const UE::Online::FOnlineError& OnlineError)`
- L38 _function_ `inline bool operator!=(const UE::Online::FOnlineError& OnlineError, EOS_EResult EosResult)`
- L43 _function_ `inline bool operator!=(EOS_EResult EosResult, const UE::Online::FOnlineError& OnlineError)`

### `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon/Public/Online/OnlineServicesEpicCommon.h` (Public)


#### class `UE::Online::FOnlineServicesEpicCommon`  
`class FOnlineServicesEpicCommon : public FOnlineServicesCommon`  
_L18-44_
- inherits: `FOnlineServicesCommon`
- L21 _public typedef_ `using Super = FOnlineServicesCommon;`
- L23 _public prototype_ `FOnlineServicesEpicCommon(const FString& InServiceConfigName, FName InInstanceName, FName InInstanceConfigName);`
- L24 _public prototype_ `virtual ~FOnlineServicesEpicCommon() = default;`
- L26 _public prototype_ `virtual bool PreInit();`
- L27 _public prototype_ `virtual void UpdateConfig() override;`
- L29 _public function_ `IEOSPlatformHandlePtr GetEOSPlatformHandle() const`
- L32 _public prototype_ `void AddEOSSDKFastTick(FOnlineAsyncOp& InAsyncOp);` — Enable EOSSDK to tick as fast as it can while this operation is outstanding. Expected usage is to call this before calling an SDK function.
- L34 _public prototype_ `void RemoveEOSSDKFastTick(FOnlineAsyncOp& InAsyncOp);` — Remove fast ticking of EOSSDK for an operation. Expected usage is to call this after an SDK function's completion delegate triggers. If this is not called, the fast tick will be removed when the operation destructs.
- L37 _protected prototype_ `void WarnIfEncryptionKeyMissing(const FString& InterfaceName) const;`
- L39 _protected prototype_ `virtual void FlushTick(float DeltaSeconds) override;`
- L41 _protected member_ `IEOSPlatformHandlePtr EOSPlatformHandle;`
- L43 _protected member_ `bool bEnableAsyncOpFastTick = true;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ONLINESERVICESEPICCOMMON_API`
- L14 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle>;`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Online` (scope `UE`)
- L46 _prototype_ `EOS_OnlinePlatformType EOnlinePlatformType_To_EOS_OnlinePlatformType(const EOnlinePlatformType& InType);` (scope `UE::Online`)
- L47 _prototype_ `EOnlinePlatformType EOS_OnlinePlatformType_To_EOnlinePlatformType(const EOS_OnlinePlatformType& InType);` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEpicCommon/Source/OnlineServicesEpicCommon/Public/Online/OnlineServicesEpicCommonModule.h` (Public)


#### class `UE::Online::FOnlineServicesEpicCommonModule`  
`class FOnlineServicesEpicCommonModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L13 _private prototype_ `virtual void StartupModule() override;`
- L14 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
