# Runtime / DumpPackageToJson

- module root: `Source/Runtime/Experimental/DumpPackageToJson`
- headers: 5; symbols: 77
- symbol kinds: class=5, delegate=1, function=11, member=16, namespace=10, prototype=34
- PrivateDependencyModuleNames: Core, CoreUObject, JsonObjectGraph, StorageServerClient
- PrivateIncludePathModuleNames: StorageServerClient

### `Source/Runtime/Experimental/DumpPackageToJson/Private/DetachedStorageServerIoDispatcherBackend.h` (Private)


#### class `UE::DumpPackageToJson::FDetachedStorageServerIoDispatcherBackend`  
`class FDetachedStorageServerIoDispatcherBackend final : public IIoDispatcherBackend`  
_L17-52_
- inherits: `IIoDispatcherBackend`
- desc: io dispatcher backend that remaps incoming chunk id's to inner chunk id's and back
- L20 _public function_ `FDetachedStorageServerIoDispatcherBackend(TSharedRef<FPackageNameRemapping> InRemapping) : Remapping(InRemapping)`
- L24 _public prototype_ `~FDetachedStorageServerIoDispatcherBackend() = default;`
- L26 _public prototype_ `void SetInner(TSharedPtr<IIoDispatcherBackend> InInner);`
- L28 _public prototype_ `virtual void Initialize(TSharedRef<const FIoDispatcherBackendContext> Context) override;`
- L29 _public prototype_ `virtual void Shutdown() override;`
- L30 _public prototype_ `virtual void ResolveIoRequests(FIoRequestList Requests, FIoRequestList& OutUnresolved) override;`
- L31 _public function_ `virtual void CancelIoRequest(FIoRequestImpl* Request) override`
- L32 _public function_ `virtual void UpdatePriorityForIoRequest(FIoRequestImpl* Request) override`
- L33 _public prototype_ `virtual bool DoesChunkExist(const FIoChunkId& ChunkId) const override;`
- L34 _public prototype_ `virtual TIoStatusOr<uint64> GetSizeForChunk(const FIoChunkId& ChunkId) const override;`
- L35 _public prototype_ `virtual FIoRequestImpl* GetCompletedIoRequests() override;`
- L37 _public function_ `virtual TIoStatusOr<FIoMappedRegion> OpenMapped(const FIoChunkId& ChunkId, const FIoReadOptions& Options) override`
- L41 _public function_ `virtual const TCHAR* GetName() const override`
- L47 _private member_ `TSharedPtr<IIoDispatcherBackend> Inner;`
- L48 _private member_ `TSharedRef<FPackageNameRemapping> Remapping;`
- L49 _private member_ `TSharedPtr<const FIoDispatcherBackendContext> SavedContext;`
- L51 _private prototype_ `void PatchPackageNameInZenPackageHeader(FIoBuffer& Buffer);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DumpPackageToJson` (scope `UE`)

### `Source/Runtime/Experimental/DumpPackageToJson/Private/DetachedStorageServerPackageStoreBackend.h` (Private)


#### class `UE::DumpPackageToJson::FDetachedStorageServerPackageStoreBackend`  
`class FDetachedStorageServerPackageStoreBackend : public IPackageStoreBackend`  
_L17-41_
- inherits: `IPackageStoreBackend`
- desc: package store backend that remaps incoming chunk id's to inner chunk id's and back
- L20 _public function_ `FDetachedStorageServerPackageStoreBackend(TSharedRef<FPackageNameRemapping> InRemapping) : Remapping(InRemapping)`
- L24 _public prototype_ `virtual ~FDetachedStorageServerPackageStoreBackend() = default;`
- L26 _public prototype_ `void SetInner(TSharedPtr<IPackageStoreBackend> InInner);`
- L28 _public function_ `virtual void OnMounted(TSharedRef<const FPackageStoreBackendContext> Context) override`
- L29 _public function_ `virtual void BeginRead() override`
- L30 _public function_ `virtual void EndRead() override`
- L32 _public prototype_ `virtual EPackageStoreEntryStatus GetPackageStoreEntry(FPackageId PackageId, FName PackageName, FPackageStoreEntry& OutPackageStoreEntry) override;`
- L33 _public function_ `virtual bool GetPackageRedirectInfo(FPackageId PackageId, FName& OutSourcePackageName, FPackageId& OutRedirectedToPackageId) override`
- L39 _private member_ `TSharedPtr<IPackageStoreBackend> Inner;`
- L40 _private member_ `TSharedRef<FPackageNameRemapping> Remapping;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DumpPackageToJson` (scope `UE`)

### `Source/Runtime/Experimental/DumpPackageToJson/Private/DumpPackageToJsonModule.h` (Private)


#### class `UE::DumpPackageToJson::FDumpPackageToJsonModule`  
`class FDumpPackageToJsonModule : public IDumpPackageToJsonModule`  
_L31-55_
- inherits: `IDumpPackageToJsonModule`
- L34 _public prototype_ `virtual bool Connect(FString Host, uint16 Port, FString Project, FString Platform) override;`
- L35 _public prototype_ `virtual void Disconnect() override;`
- L36 _public function_ `virtual bool IsConnected() override`
- L40 _public prototype_ `virtual FString RemotePackageToJson(FString PackageName) override;`
- L41 _public prototype_ `virtual FString LocalPackageToJson(FString PackageName) override;`
- L44 _private member_ `TUniquePtr<IStorageServerPlatformFile> StorageServerPlatformFile;`
- L45 _private member_ `TSharedPtr<IPackageStoreBackend> StorageServerPackageStoreBackend;`
- L46 _private member_ `TSharedPtr<IIoDispatcherBackend> StorageServerIoDispatcherBackend;`
- L48 _private member_ `TSharedPtr<FPackageNameRemapping> Remapper;`
- L49 _private member_ `TSharedPtr<FDetachedStorageServerIoDispatcherBackend> RemappingIoDispatcherBackend;`
- L50 _private member_ `TSharedPtr<FDetachedStorageServerPackageStoreBackend> RemappingPackageStoreBackend;`
- L52 _private member_ `uint32 TempPackageIndex = 0;`
- L54 _private prototype_ `static FString UPackageToJson(UPackage* Package);`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDumpPackageToJson, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDumpPackageToJson, Log, All);`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DumpPackageToJson` (scope `UE`)

### `Source/Runtime/Experimental/DumpPackageToJson/Private/PackageNameRemapping.h` (Private)


#### class `UE::DumpPackageToJson::FPackageNameRemapping`  
`class FPackageNameRemapping`  
_L17-42_
- desc: Helper class to map between temporary package name/id <-> original package name/id
- L20 _public prototype_ `void AddRemap(FString TempName, FString OriginalName);`
- L21 _public prototype_ `void ClearRemaps();`
- L24 _public prototype_ `FString Map(FString TempName) const;` — Temp -> Original
- L25 _public prototype_ `FPackageId Map(FPackageId TempPackageId) const;`
- L26 _public prototype_ `FIoChunkId Map(FIoChunkId TempChunkId) const;`
- L29 _public prototype_ `FString Remap(FString OriginalName) const;` — Original -> Temp
- L30 _public prototype_ `FPackageId Remap(FPackageId OriginalPackageId) const;`
- L31 _public prototype_ `FIoChunkId Remap(FIoChunkId OriginalChunkId) const;`
- L34 _private member_ `TMap<FString, FString> TempNameToOriginal;`
- L35 _private member_ `TMap<FString, FString> OriginalNameToTemp;`
- L36 _private member_ `TMap<FPackageId, FPackageId> TempPackageIdToOriginal;`
- L37 _private member_ `TMap<FPackageId, FPackageId> OriginalPackageIdToName;`
- L39 _private prototype_ `static FPackageId PackageIdFromString(FString String);`
- L40 _private prototype_ `static FPackageId PackageIdFromChunkId(FIoChunkId ChunkId);`
- L41 _private prototype_ `static FIoChunkId ReplaceChunkIdsPackageId(FIoChunkId ChunkId, FPackageId NewPackageId);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DumpPackageToJson` (scope `UE`)

### `Source/Runtime/Experimental/DumpPackageToJson/Public/IDumpPackageToJsonModule.h` (Public)


#### class `UE::DumpPackageToJson::IDumpPackageToJsonModule`  
`class IDumpPackageToJsonModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual bool Connect(FString Host, uint16 Port, FString Project, FString Platform) = 0;`
- L15 _public prototype_ `virtual void Disconnect() = 0;`
- L16 _public prototype_ `virtual bool IsConnected() = 0;`
- L17 _public prototype_ `virtual FString RemotePackageToJson(FString PackageName) = 0;`
- L18 _public prototype_ `virtual FString LocalPackageToJson(FString PackageName) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DumpPackageToJson` (scope `UE`)
