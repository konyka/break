# Runtime / IndexedCacheStorage

- module root: `Source/Runtime/Experimental/IndexedCacheStorage`
- headers: 2; symbols: 44
- symbol kinds: class=3, function=2, macro=1, member=5, namespace=2, prototype=30, struct=1
- PublicDependencyModuleNames: Core

### `Source/Runtime/Experimental/IndexedCacheStorage/Private/IndexedCacheStorage.h` (Private)


#### class `Experimental::IIndexedCacheStorage`  
`class IIndexedCacheStorage`  
_L18-98_
- desc: Interface for managing cache storages: some platforms may store user data in different cache storages that may be created / destroyed This allows the title to manage its disk space with a finer granularity. The data put in these caches need to be re-generated/re-obtained if needed.
- L21 _public prototype_ `static IIndexedCacheStorage& Get();`
- L23 _public prototype_ `static IIndexedCacheStorage& GetOrCreateIndexedCacheStorage();`
- L30 _public prototype_ `virtual bool SupportsIndexedCacheStorage() = 0;` — Check if indexed cache storage is available on the current platform. @return True is available, false otherwise.
- L37 _public prototype_ `virtual uint32 GetNumIndexedCacheStorages() = 0;` — Retrieve the number of indexed cache entries available on the platform. @return number of indexed cache entries available on the platform.
- L46 _public prototype_ `virtual bool CreateCacheStorage(uint64 InRequestNumberOfBytes, int32 CacheStorageIndex) = 0;` — Requests a new indexed cache entry, capable of holding up to RequestNumberOfBytes. @param InRequestNumberOfBytes number of bytes this entry needs to hold @param CacheStorageIndex - the index of the entry to create @return True on success, otherwise false
- L54 _public prototype_ `virtual bool DestroyCacheStorage(int32 InCacheStorageIndex) = 0;` — Destroy an indexed cache entry. @param InCacheStorageIndex - the index of the entry @return True on success, otherwise false
- L61 _public prototype_ `virtual void EnumerateCacheStorages(TArray<int32>& OutCacheStorageIndices) = 0;` — Enumerate existing cache entries. @param OutCacheStorageIndices - indices of existing cache storages
- L69 _public prototype_ `virtual void GetCacheStorageInfo(int32 InCacheStorageIndex, uint64& OutCacheStorageDataSize, uint64& OutCacheStorageJournalSize) = 0;` — Queries cache storage. @param InCacheStorageIndex - the index of the cache @param OutCacheStorageSize - How large the cache storage is
- L77 _public prototype_ `virtual void GetCacheStorageMountPath(FString& OutPlatformMountPath, const FString& InMountName) = 0;` — Gets the platform mount path for a cached storage based on its generic Name @param OutPlatformMountPath - the platform specific mount path @param InMountName - the generic mount name
- L86 _public prototype_ `virtual bool MountCacheStorage(FString& OutPlatformMountPath, int32 InCacheStorageIndex, const FString& InMountName) = 0;` — Mounts a cache storage so file operations can be done @param OutPlatformMountPath - the platform specific mount path. Same name as the one returned by GetCacheStorageMountPath @param InCacheStorageIndex - the index of the cache @param InMountName - the generic mount name
- L92 _public prototype_ `virtual void UnmountCacheStorage(const FString& InMountName) = 0;` — Unmounts a cache storage @param InMountName - the generic mount name
- L94 _public prototype_ `virtual uint64 GetPersistentDownloadDirEarlyStartupSize() = 0;`
- L96 _public prototype_ `virtual uint64 GetCacheStorageJournalSize(uint64 CacheDataSize, uint32 CacheIndex) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Experimental`

### `Source/Runtime/Experimental/IndexedCacheStorage/Public/IndexedCacheStorageManager.h` (Public)


#### class `Experimental::FIndexedCacheStorageModule`  
`class FIndexedCacheStorageModule : public IModuleInterface`  
_L17-23_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L22 _public prototype_ `virtual void ShutdownModule() override;`

#### class `Experimental::FIndexedCacheStorageManager`  
`class FIndexedCacheStorageManager`  
_L28-82_
- desc: Manager to handle ref-counting of ICS entries
- L32 _public prototype_ `static FIndexedCacheStorageManager& Get();`
- L35 _public prototype_ `bool SupportsIndexedCacheStorage();` — Returns whether ICS is supported
- L43 _public prototype_ `int32 GetStorageIndex(const FString& CacheStorageName);` — Returns the cache index registered to that storage name. Registration happens in the config section: [IndexedCacheStorage] +Storage=(Name="StorageName",Index=StorageIndex,Mount="StorageMount",EarlyStartup=IniName:[IniSection]:IniKey) The EarlyStartup attribute is optional. It will try to fetch the value from the specified init path The value in the ini file can be written as 512, 512KB, 512MB or 512GB Requires that ones of the entries in the Storage array is called EarlyStartupCache
- L46 _public prototype_ `uint64 GetCacheEarlyStartupSize(int32 CacheIndex);` — Returns 0 if no early startup size configured
- L49 _public prototype_ `void EnumerateCacheStorages(TArray<FString>& OutCacheStorageNames);` — returns all registered storage names. The assoaciated cache storages might not have been created
- L52 _public prototype_ `bool CreateCacheStorage(uint64 RequestNumberOfBytes, int32 CacheIndex);` — Create a new storage at the specified index. Will destroy the previous one if it had a different capacity
- L55 _public prototype_ `void DestroyCacheStorage(int32 CacheIndex);` — Destroy the specified cache storage
- L58 _public prototype_ `uint64 GetCacheStorageCapacity(int32 CacheIndex);` — Returns 0 if no cache currently exists
- L61 _public prototype_ `FString MountCacheStorage(int32 CacheIndex);` — Returns the path of the mounted cache
- L64 _public prototype_ `void UnmountCacheStorage(int32 CacheIndex);` — Requests unmounting for CacheIndex. Actually unmounts if # of UnmountCacheEntry == # of MountCacheStorage for the same index
- L67 _public prototype_ `FString GetMountName(int32 CacheIndex);` — Returns mount name in cache index is mounted, empty if not mounted
- L70 _public prototype_ `FString GetMountPath(int32 CacheIndex);` — Helper to retrieve the mount path. Equivalent to GetCacheStorageMountPath(GetMountName)
- L75 _private prototype_ `void Initialize();`
- L76 _private prototype_ `void EnsureEarlyStartupCache(const TArray<bool>& CacheStorageAlreadyExists);`
- L77 _private prototype_ `FCacheStorageMetaData* GetCacheStorageMetaData(int32 CacheIndex);`
- L79 _private member_ `TUniquePtr<struct FIndexedCacheStorageMetaData> IndexedCacheStorageMetaData;`
- L80 _private member_ `TMap<FString, int32> StorageNameToStorageIndex;`
- L81 _private member_ `bool bHasRegisteredEntries = false;`

#### struct `Experimental::FIndexedCacheStorageScopeMount`  
`struct FIndexedCacheStorageScopeMount`  
_L84-99_
- L86 _public function_ `FIndexedCacheStorageScopeMount(int32 InMountPoint) : MountPoint(InMountPoint)`
- L92 _public function_ `~FIndexedCacheStorageScopeMount()`
- L97 _public member_ `FString MountPath;`
- L98 _public member_ `const int32 MountPoint = 0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INDEXEDCACHESTORAGE_API`
- L14 _namespace_ `namespace Experimental`
