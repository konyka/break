# Runtime / GDKSaveGameSystem

- module root: `Source/Runtime/Microsoft/GDKSaveGameSystem`
- headers: 1; symbols: 32
- symbol kinds: class=1, delegate=1, function=2, macro=1, member=5, prototype=22
- PrivateDependencyModuleNames: ApplicationCore, Core, Engine, GDKRuntime, GRDK

### `Source/Runtime/Microsoft/GDKSaveGameSystem/Public/GDKSaveGameSystem.h` (Public)


#### class `FGDKSaveGameSystem`  
`class FGDKSaveGameSystem : public FBaseAsyncSaveGameSystem`  
_L20-91_
- inherits: `FBaseAsyncSaveGameSystem`
- L23 _public prototype_ `FGDKSaveGameSystem();`
- L24 _public prototype_ `virtual ~FGDKSaveGameSystem();`
- L27 _public function_ `virtual bool PlatformHasNativeUI() override` — Returns true if the platform has a native UI (like many consoles)
- L32 _public function_ `virtual bool DoesSaveSystemSupportMultipleUsers() override`
- L38 _public prototype_ `virtual void InitAsync(bool bAttemptToUseUI, FPlatformUserId PlatformUserId, FSaveGameAsyncInitCompleteCallback Callback) override;` — (Optional) initialise the save system for the given user. GDK may display the 'syncing' or 'resolve save' dialog when creating the save provider
- L41 _public prototype_ `virtual void LoadGameIfExistsAsync(bool bAttemptToUseUI, const TCHAR* Name, FPlatformUserId PlatformUserId, FSaveGameAsyncLoadCompleteCallback Callback) override;` — Override as the custom queuing breaks the default implementation and is unnecessary
- L45 _public prototype_ `void DebugListSavesForAllUsers();` — Debugging helper functions
- L46 _public prototype_ `void DebugListSavesForUser( const int32 UserIndex );`
- L49 _private member_ `static const uint32 MaxContainerName;`
- L50 _private member_ `static const char* DefaultBlobName;`
- L51 _private member_ `static const char* XDKCompatibleContainerName;`
- L54 _private prototype_ `virtual UE::Tasks::FTask InternalDoesSaveGameExistAsync(const TCHAR* Name, FPlatformUserId PlatformUserId, FSaveGameAsyncExistsCallback Callback, TSharedPtr<ESaveExistsResult> OutResult = nullptr) override;` — internal async helpers
- L55 _private prototype_ `virtual UE::Tasks::FTask InternalSaveGameAsync(bool bAttemptToUseUI, const TCHAR* Name, FPlatformUserId PlatformUserId, TSharedRef<const TArray<uint8>> Data, FSaveGameAsyncOpCompleteCallback Callback, TSharedPtr<bool> OutResult = nullptr) override;`
- L56 _private prototype_ `virtual UE::Tasks::FTask InternalLoadGameAsync(bool bAttemptToUseUI, const TCHAR* Name, FPlatformUserId PlatformUserId, TSharedRef<TArray<uint8>> Data, FSaveGameAsyncLoadCompleteCallback Callback, TSharedPtr<bool> OutResult = nullptr) override;`
- L57 _private prototype_ `virtual UE::Tasks::FTask InternalDeleteGameAsync(bool bAttemptToUseUI, const TCHAR* Name, FPlatformUserId PlatformUserId, FSaveGameAsyncOpCompleteCallback Callback, TSharedPtr<bool> OutResult = nullptr) override;`
- L58 _private prototype_ `virtual UE::Tasks::FTask InternalGetSaveGameNamesAsync(FPlatformUserId PlatformUserId, TSharedRef<TArray<FString>> FoundSaves, FSaveGameAsyncGetNamesCallback Callback, TSharedPtr<bool> OutResult = nullptr) override;`
- L60 _private prototype_ `UE::Tasks::FTask InitSaveGameProviderAsync(FPlatformUserId PlatformUserId);`
- L62 _private prototype_ `virtual void WaitForAsyncTask(UE::Tasks::FTask AsyncSaveTask) override;`
- L65 _private member_ `XTaskQueueRegistrationToken UserChangeCallbackToken;` — user sign in/out callback
- L66 _private prototype_ `void OnUserChange(XUserLocalId UserLocalId, XUserChangeEvent Event);`
- L69 _private prototype_ `static void GetContainerAndBlobNames( FString& OutContainerName, FString& OutBlobName, const FString& InSaveName );` — get the final blob and container names
- L72 _private prototype_ `static FString SanitizeContainerName(const TCHAR* Name);` — remove invalid characters from the given save container name
- L75 _private prototype_ `static ESaveExistsResult GetBlobInfoByName( XGameSaveContainerHandle InContainer, const FString& InBlobName, uint32& OutDataSize );` — get the info for a particular named blob
- L78 _private prototype_ `static uint32 GetNumBlobsInContainer( XGameSaveContainerHandle InContainer );` — get all blobs in the given container
- L81 _private prototype_ `static bool DoesContainerExist( XGameSaveProviderHandle InProvider, const FString& InContainerName );` — check whether the given container exists
- L84 _private prototype_ `static void ProcessErrorCode( HRESULT Result, const TCHAR* Msg );` — error display helper
- L87 _private prototype_ `XGameSaveProviderHandle GetProviderForUserId(FPlatformUserId UserId);` — get a provider for the user's save provider
- L90 _private member_ `TMap<FGDKUserHandle, XGameSaveProviderHandle> PerUserSaveProviders;` — cache the save providers for each user

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GDKSAVEGAMESYSTEM_API`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGDKSaveGame, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGDKSaveGame, Log, All);`
