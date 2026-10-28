# Runtime / IoStoreOnDemandCore

- module root: `Source/Runtime/Experimental/IoStore/OnDemandCore`
- headers: 9; symbols: 961
- symbol kinds: class=25, delegate=1, enum=22, enumerator=90, function=157, macro=14, member=251, namespace=31, prototype=273, struct=56, typedef=41
- PrivateDependencyModuleNames: CoreUObject, Json
- PublicDependencyModuleNames: Core

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Internal/IO/GenericHash.h` (Internal)


#### struct `UE::THash`  
`template<SIZE_T BitCount> struct THash`  
_L30-88_
- L32 _public member_ `static constexpr SIZE_T Size = BitCount >> 3;`
- L33 _public typedef_ `using ByteArray = uint8[Size];`
- L35 _public prototype_ `THash() = default;`
- L36 _public function_ `const uint8* GetData() const`
- L37 _public function_ `SIZE_T GetSize() const`
- L38 _public function_ `FMemoryView GetView() const`
- L40 _public prototype_ `static THash HashBuffer(FMemoryView Memory);`
- L41 _public prototype_ `static void HashBuffer(FMemoryView Memory, THash& Out);`
- L43 _public prototype_ `static THash From(FMemoryView Memory);`
- L44 _public prototype_ `static THash From(const uint8* Data, SIZE_T DataSize);`
- L45 _public prototype_ `static THash From(const FIoHash& IoHash);`
- L46 _public member_ `static const THash Zero;`
- L85 _private function_ `FMutableMemoryView GetMutableView()`
- L87 _private member_ `alignas(uint32) ByteArray Hash{};`
- L94 _function_ `template<SIZE_T BitCount> THash<BitCount> THash<BitCount>::From(FMemoryView Memory)`
- L102 _function_ `template<SIZE_T BitCount> THash<BitCount> THash<BitCount>::From(const uint8* Data, SIZE_T DataSize)`
- L108 _function_ `template<SIZE_T BitCount> THash<BitCount> THash<BitCount>::From(const FIoHash& IoHash)`
- L116 _function_ `template<SIZE_T BitCount> void THash<BitCount>::HashBuffer(FMemoryView Memory, THash<BitCount>& Out)`
- L122 _function_ `template<SIZE_T BitCount> THash<BitCount> THash<BitCount>::HashBuffer(FMemoryView Memory)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L17 _namespace_ `namespace UE`
- L20 _namespace_ `namespace GenericHash` (scope `UE`)
- L23 _prototype_ `FString ToHex(FMemoryView Memory);` (scope `UE::GenericHash`)
- L24 _prototype_ `FStringBuilderBase& ToHex(FMemoryView Memory, FStringBuilderBase& Out);` (scope `UE::GenericHash`)
- L25 _prototype_ `void HashBuffer(FMutableMemoryView Dst, FMemoryView Src);` (scope `UE::GenericHash`)
- L48 _function_ `friend inline bool operator==(const THash& A, const THash& B)` (scope `UE`)
- L53 _function_ `friend inline bool operator!=(const THash& A, const THash& B)` (scope `UE`)
- L58 _function_ `friend inline bool operator<(const THash& A, const THash& B)` (scope `UE`)
- L63 _function_ `friend inline uint32 GetTypeHash(const THash& H)` (scope `UE`)
- L68 _function_ `friend inline FString LexToString(const THash& H)` (scope `UE`)
- L73 _function_ `friend inline FStringBuilderBase& LexToString(const THash& H, FStringBuilderBase& Out)` (scope `UE`)
- L78 _function_ `friend FArchive& operator<<(FArchive& Ar, THash& H)` (scope `UE`)
- L91 _member_ `template<SIZE_T BitCount> const THash<BitCount> THash<BitCount>::Zero;` (scope `UE::THash<BitCount>`)
- L129 _typedef_ `using FHash32 = THash<32>;` (scope `UE`)
- L130 _typedef_ `using FHash64 = THash<64>;` (scope `UE`)
- L131 _typedef_ `using FHash96 = THash<96>;` (scope `UE`)
- L132 _typedef_ `using FHash128 = THash<128>;` (scope `UE`)
- L133 _typedef_ `using FHash160 = THash<160>;` (scope `UE`)
- L134 _typedef_ `using FHash256 = THash<256>;` (scope `UE`)

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Internal/IO/IoStoreOnDemandInternals.h` (Internal)


#### struct `UE::IoStore::FOnDemandWeakContentHandle`  
`struct FOnDemandWeakContentHandle`  
_L19-44_
- L21 _public function_ `bool IsValid() const`
- L23 _public function_ `inline bool operator==(const FOnDemandWeakContentHandle& Other) const`
- L28 _public function_ `inline bool operator!=(const FOnDemandWeakContentHandle& Other) const`
- L33 _public function_ `inline operator bool() const`
- L40 _public prototype_ `static FOnDemandWeakContentHandle FromUnsafeHandle(UPTRINT HandleId);`
- L42 _public member_ `UPTRINT HandleId = 0;`
- L43 _public member_ `FSharedString DebugName;`

#### class `UE::IoStore::FOnDemandInternalContentHandle`  
`class FOnDemandInternalContentHandle`  
_L47-69_
- L50 _public prototype_ `FOnDemandInternalContentHandle();`
- L52 _public prototype_ `FOnDemandInternalContentHandle(FSharedString InDebugName);`
- L54 _public prototype_ `~FOnDemandInternalContentHandle();`
- L56 _public prototype_ `FOnDemandInternalContentHandle(const FOnDemandInternalContentHandle& Other) = default;`
- L57 _public prototype_ `FOnDemandInternalContentHandle(FOnDemandInternalContentHandle&& Other) = default;`
- L59 _public prototype_ `FOnDemandInternalContentHandle& operator=(const FOnDemandInternalContentHandle& Other) = default;`
- L60 _public prototype_ `FOnDemandInternalContentHandle& operator=(FOnDemandInternalContentHandle&& Other) = default;`
- L62 _public function_ `UPTRINT HandleId() const`
- L64 _public member_ `FSharedString DebugName;`
- L68 _private member_ `FWeakOnDemandIoStore IoStore;` — This needs additional syncronization if its read outside the destructor

#### class `UE::IoStore::FOnDemandInternalInstallRequest`  
`class FOnDemandInternalInstallRequest`  
_L72-83_
- L75 _public typedef_ `using EStatus = FOnDemandRequest::EStatus;`
- L77 _public function_ `explicit FOnDemandInternalInstallRequest(UPTRINT InInstallerRequest) : InstallerRequest(InInstallerRequest)`
- L80 _public member_ `FWeakOnDemandIoStore IoStore;`
- L81 _public member_ `UPTRINT InstallerRequest = 0;`
- L82 _public member_ `std::atomic<EStatus> Status{EStatus::Pending};`

#### class `UE::IoStore::IOnDemandInternalHttpStats`  
`class IOnDemandInternalHttpStats`  
_L86-95_
- L90 _public prototype_ `virtual ~IOnDemandInternalHttpStats() = default;`
- L91 _public prototype_ `virtual uint32 GetRecvKiBps() const = 0;`
- L92 _public prototype_ `virtual void GetRecvKiBps(uint32 (&Out)[SAMPLE_COUNT]) const = 0;`
- L93 _public prototype_ `virtual uint32 GetTotalRecvKiB() const = 0;`
- L94 _public prototype_ `virtual uint32 GetTimeToFirstByteMs() const = 0;`

#### enum `UE::IoStore::IOnDemandInternalHttpStats::(anonymous)`  
`enum`  
_L89-89_

#### Free symbols / members of external scopes

- L10 _macro_ `#define WITH_IOSTORE_ONDEMAND_TESTS 0`
- L13 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace IoStore` (scope `UE`)
- L35 _function_ `inline friend uint32 GetTypeHash(const FOnDemandWeakContentHandle& Handle)` (scope `UE::IoStore`)
- L89 _enumerator_ `enum { SAMPLE_COUNT = FOnDemandHttpStats::SAMPLE_COUNT }; virtual ~IOnDemandInternalHttpStats() = default; virtual uint32 GetRecvKiBps() const = 0; virtual void GetRecvKiBps(uint32 (&Out)[SAMPLE_COUNT]) const = 0; virtual uint32 GetTotalRecvKiB() const = 0; virtual uint32 GetTimeToFirstByteMs() const = 0;` (scope `UE::IoStore::IOnDemandInternalHttpStats::__anon1b2d205c0103`)
- L100 _prototype_ `FString LexToString(const UE::IoStore::FOnDemandInternalContentHandle& Handle);`

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Internal/IO/Serialization/OnDemandContainerToc.h` (Internal)


#### struct `UE::IoStore::Serialization::FOnDemandFileExt`  
`struct FOnDemandFileExt`  
_L34-40_
- L36 _public member_ `static constexpr const TCHAR* Toc = TEXT(".uo`
- L37 _public member_ `static constexpr const TCHAR* Chunk = TEXT(".io`
- L38 _public member_ `static constexpr const TCHAR* PartitionToc = TEXT(".io`
- L39 _public member_ `static constexpr const TCHAR* Partition = TEXT(".io`

#### struct `UE::IoStore::Serialization::FOnDemandTocSignature`  
`struct FOnDemandTocSignature`  
_L43-58_
- L45 _public member_ `static constexpr inline ANSICHAR ExpectedSignature[] = "UE`
- L47 _public function_ `FOnDemandTocSignature()`
- L52 _public function_ `bool IsValid() const`
- L57 _public member_ `ANSICHAR Signature[16];`

#### enum `UE::IoStore::Serialization::EOnDemandTocMajorVersion`  
`enum class EOnDemandTocMajorVersion : uint16`  
_L62-69_
- L64 _public enumerator_ `Invalid = 0`
- L65 _public enumerator_ `One = 1`
- L67 _public enumerator_ `LatestPlusOne`
- L68 _public enumerator_ `Latest = (LatestPlusOne - 1)`

#### enum `UE::IoStore::Serialization::EOnDemandTocMinorVersion`  
`enum class EOnDemandTocMinorVersion : uint16`  
_L72-80_
- L74 _public enumerator_ `Invalid = 0`
- L75 _public enumerator_ `MemoryMapped = 1`
- L76 _public enumerator_ `Partitions = 2`
- L78 _public enumerator_ `LatestPlusOne`
- L79 _public enumerator_ `Latest = (LatestPlusOne - 1)`

#### struct `UE::IoStore::Serialization::FOnDemandTocVersion`  
`struct alignas(4) FOnDemandTocVersion`  
_L83-89_
- L85 _public function_ `bool IsValid() const`
- L87 _public member_ `uint16 Major = uint16(EOnDemandTocMajorVersion::Latest);`
- L88 _public member_ `uint16 Minor = uint16(EOnDemandTocMinorVersion::Latest);`

#### struct `UE::IoStore::Serialization::FOnDemandTocFooter`  
`struct FOnDemandTocFooter`  
_L93-96_
- L95 _public member_ `FOnDemandTocSignature Signature;`

#### enum `UE::IoStore::Serialization::FOnDemandTocStorageType`  
`enum class FOnDemandTocStorageType : uint8`  
_L100-105_
- L102 _public enumerator_ `Invalid = 0`
- L103 _public enumerator_ `Memory`
- L104 _public enumerator_ `MemoryMapped`

#### class `UE::IoStore::Serialization::FOnDemandTocStorage`  
`class FOnDemandTocStorage`  
_L108-142_
- L121 _private typedef_ `using FStorage = TVariant<FEmptyVariantState, FMemoryStorage, FMappedFileStorage>;`
- L124 _public prototype_ `FOnDemandTocStorage();`
- L125 _public prototype_ `FOnDemandTocStorage(FIoBuffer HeaderData, FIoBuffer ContainerData);`
- L126 _public prototype_ `FOnDemandTocStorage(FIoBuffer HeaderData, TUniquePtr<IMappedFileHandle>&& File, TUniquePtr<IMappedFileRegion>&& Region);`
- L127 _public prototype_ `FOnDemandTocStorage(FOnDemandTocStorage&& Other);`
- L128 _public prototype_ `~FOnDemandTocStorage();`
- L130 _public prototype_ `FOnDemandTocStorage& operator=(FOnDemandTocStorage&&);`
- L132 _public prototype_ `FMemoryView GetView() const;`
- L133 _public prototype_ `FOnDemandTocStorageType StorageType() const;`
- L134 _public function_ `bool IsEmpty() const`
- L137 _private prototype_ `FOnDemandTocStorage(const FOnDemandTocStorage&) = delete;`
- L138 _private prototype_ `FOnDemandTocStorage& operator=(const FOnDemandTocStorage&) = delete;`
- L140 _private member_ `FIoBuffer HeaderData;`
- L141 _private member_ `FStorage ContainerData;`

#### struct `UE::IoStore::Serialization::FOnDemandTocStorage::FMappedFileStorage`  
`struct FMappedFileStorage`  
_L110-114_
- L112 _public member_ `TUniquePtr<IMappedFileHandle> MappedFile;`
- L113 _public member_ `TUniquePtr<IMappedFileRegion> MappedRegion;`

#### struct `UE::IoStore::Serialization::FOnDemandTocStorage::FMemoryStorage`  
`struct FMemoryStorage`  
_L116-119_
- L118 _public member_ `FIoBuffer Buffer;`

#### enum `UE::IoStore::Serialization::EOnDemandContainerEntryFlags`  
`enum class EOnDemandContainerEntryFlags : uint32`  
_L145-152_
- L147 _public enumerator_ `None = 0`
- L148 _public enumerator_ `InstallOnDemand = (1 << 0)`
- L149 _public enumerator_ `StreamOnDemand = (1 << 1)`
- L151 _public enumerator_ `Last = StreamOnDemand`

#### class `UE::IoStore::Serialization::FOnDemandTocWriter`  
`class FOnDemandTocWriter`  
_L156-201_
- L159 _public prototype_ `FOnDemandTocWriter();`
- L160 _public prototype_ `FOnDemandTocWriter(FOnDemandTocWriter&&);`
- L161 _public prototype_ `~FOnDemandTocWriter();`
- L163 _public prototype_ `FOnDemandTocWriter& operator=(FOnDemandTocWriter&&);`
- L165 _public prototype_ `bool IsEmpty() const;`
- L166 _public prototype_ `void SetMetadata( const FString& BuildVersion, const FString& TargetPlatform);`
- L169 _public prototype_ `void SetHostGroup(const FString& HostGroupName);`
- L170 _public prototype_ `void SetChunksDirectory(const FString& ChunksDirectory);`
- L171 _public prototype_ `void BeginContainer( const FString& ContainerName, const FIoContainerId& ContainerId, const FIoHash& UTocHash, const FGuid& EncryptionKeyGuid, uint32 CompressionBlockSize, uint32 FileContainerFlags, EOnDemandContainerEntryFlags ContainerFlags, FIoBuffer ContainerHeader);`
- L180 _public prototype_ `int32 BeginPartition();`
- L181 _public prototype_ `uint64 AddChunk( int32 Partition, const FIoChunkId& ChunkId, FIoBuffer EncodedChunk, TConstArrayView<uint32> BlockSizes, TConstArrayView<FIoBlockHash> BlockHashes, uint64 RawChunkSize);`
- L188 _public prototype_ `void AddTagSet(FStringView Tag, TConstArrayView<uint32> PackageIndices);`
- L189 _public prototype_ `FIoBuffer EndPartition(int32 Partition, FIoHash& OutHash);`
- L190 _public prototype_ `void EndContainer(FName CompressionFormat);`
- L192 _public prototype_ `TIoStatusOr<uint64> Write(FArchive& Ar);`
- L193 _public prototype_ `TIoStatusOr<uint64> Write(const FString& Filename);`
- L196 _private prototype_ `FOnDemandTocWriter(const FOnDemandTocWriter&) = delete;`
- L197 _private prototype_ `FOnDemandTocWriter& operator=(const FOnDemandTocWriter&) = delete;`
- L200 _private member_ `TUniquePtr<FImpl> Impl;`

#### struct `UE::IoStore::Serialization::V1::FOnDemandStringEntry`  
`struct FOnDemandStringEntry`  
_L207-211_
- L209 _public member_ `uint32 Offset = 0;`
- L210 _public member_ `uint32 Len = 0;`

#### struct `UE::IoStore::Serialization::V1::FOnDemandTocHeader`  
`struct FOnDemandTocHeader`  
_L214-228_
- L216 _public member_ `FOnDemandTocSignature Signature;`
- L217 _public member_ `FOnDemandTocVersion Version;`
- L218 _public member_ `uint32 Pad = 0;`
- L219 _public member_ `int64 EpochTimestamp = 0;`
- L220 _public member_ `FOnDemandStringEntry BuildVersion;`
- L221 _public member_ `FOnDemandStringEntry TargetPlatform;`
- L222 _public member_ `FOnDemandStringEntry ChunksDirectory;`
- L223 _public member_ `FOnDemandStringEntry HostGroupName;`
- L224 _public member_ `FOnDemandStringEntry CompressionFormat;`
- L225 _public member_ `uint32 StringTableLen = 0;`
- L226 _public member_ `uint32 ContainerCount = 0;`
- L227 _public member_ `uint8 Pad2[48] = {0};`

#### struct `UE::IoStore::Serialization::V1::FOnDemandContainerEntry`  
`struct FOnDemandContainerEntry`  
_L231-249_
- L233 _public member_ `FGuid EncryptionKeyGuid;`
- L234 _public member_ `FIoContainerId ContainerId;`
- L235 _public member_ `FOnDemandStringEntry ContainerName;`
- L236 _public member_ `uint32 ContainerHeaderSize = 0;`
- L237 _public member_ `uint32 DataOffset = 0;`
- L238 _public member_ `uint32 DataSize = 0;`
- L239 _public member_ `uint32 ChunkCount = 0;`
- L240 _public member_ `uint32 BlockCount = 0;`
- L241 _public member_ `uint32 BlockSize = 0;`
- L242 _public member_ `uint32 TagSetCount = 0;`
- L243 _public member_ `uint32 TagSetIndicesCount = 0;`
- L244 _public member_ `FIoHash UTocHash = FIoHash::Zero;`
- L245 _public member_ `uint32 ContainerFlags = 0;` — EOnDemandContainerEntryFlags
- L246 _public member_ `uint32 FileContainerFlags = 0;` — EIoContainerFlags
- L247 _public member_ `uint32 PartitionCount = 0;`
- L248 _public member_ `int8 Pad[32] = {0};`

#### struct `UE::IoStore::Serialization::V1::FOnDemandChunkBlockInfo`  
`struct FOnDemandChunkBlockInfo`  
_L252-287_
- L254 _public function_ `FOnDemandChunkBlockInfo()`
- L259 _public function_ `uint32 Offset() const`
- L260 _public function_ `uint32 Count() const`
- L261 _public function_ `uint32 Size() const`
- L262 _public function_ `uint32 Hash() const`
- L263 _public function_ `const uint32* Data() const`
- L265 _public function_ `static FOnDemandChunkBlockInfo FromOffsetAndCount(uint32 BlockOffset, uint32 BlockCount)`
- L274 _public function_ `static FOnDemandChunkBlockInfo FromSizeAndHash(uint32 BlockSize, uint32 BlockHash)`
- L284 _private member_ `uint32 OffsetOrSize: 31;`
- L285 _private member_ `uint32 bHasOffset: 1;`
- L286 _private member_ `uint32 CountOrHash;`

#### struct `UE::IoStore::Serialization::V1::FOnDemandChunkEntry`  
`struct FOnDemandChunkEntry`  
_L290-298_
- L292 _public function_ `uint32 GetDiskSize() const`
- L294 _public member_ `FIoHash Hash = FIoHash::Zero;`
- L295 _public member_ `uint32 RawSize = 0;`
- L296 _public member_ `uint32 EncodedSize = 0;`
- L297 _public member_ `FOnDemandChunkBlockInfo BlockInfo;`

#### struct `UE::IoStore::Serialization::V1::FOnDemandTagSetEntry`  
`struct FOnDemandTagSetEntry`  
_L301-306_
- L303 _public member_ `FOnDemandStringEntry Tag;`
- L304 _public member_ `uint32 Offset = 0;`
- L305 _public member_ `uint32 Count = 0;`

#### struct `UE::IoStore::Serialization::V1::FOnDemandContainerTocHeaderView`  
`struct FOnDemandContainerTocHeaderView`  
_L310-339_
- L312 _public typedef_ `using EContainerFlags = EOnDemandContainerEntryFlags;`
- L314 _public prototype_ `FOnDemandContainerTocHeaderView() = default;`
- L315 _public function_ `FOnDemandContainerTocHeaderView( const FOnDemandTocHeader* InHeader, const UTF8CHAR* InStringTable, const FOnDemandContainerEntry* InContainerEntry) : Header(InHeader) , StringTable(InStringTable) , ContainerEntry(InContainerEntry)`
- L324 _public function_ `FUtf8StringView ContainerName() const`
- L325 _public function_ `FIoContainerId ContainerId() const`
- L326 _public function_ `EContainerFlags ContainerFlags() const`
- L327 _public prototype_ `EIoContainerFlags FileContainerFlags() const;`
- L328 _public function_ `const FGuid& EncryptionKeyGuid() const`
- L329 _public function_ `uint32 BlockSize() const`
- L330 _public prototype_ `FUtf8StringView GetString(FOnDemandStringEntry StringEntry) const;`
- L332 _public function_ `bool IsValid() const`
- L333 _public function_ `operator bool() const`
- L336 _private member_ `const FOnDemandTocHeader* Header = nullptr;`
- L337 _private member_ `const UTF8CHAR* StringTable = nullptr;`
- L338 _private member_ `const FOnDemandContainerEntry* ContainerEntry = nullptr;`

#### struct `UE::IoStore::Serialization::V1::FOnDemandContainerTocView`  
`struct FOnDemandContainerTocView`  
_L342-352_
- L344 _public member_ `FOnDemandContainerTocHeaderView Header;`
- L345 _public member_ `TConstArrayView<FIoChunkId> ChunkIds;`
- L346 _public member_ `TConstArrayView<FOnDemandChunkEntry> ChunkEntries;`
- L347 _public member_ `TConstArrayView<uint32> BlockSizes;`
- L348 _public member_ `TConstArrayView<FIoBlockHash> BlockHashes;`
- L349 _public member_ `TConstArrayView<FOnDemandTagSetEntry> TagSets;`
- L350 _public member_ `TConstArrayView<uint32> TagSetIndices;`
- L351 _public member_ `FIoBuffer ContainerHeaderChunk;` — FIoContainerHeader

#### enum `UE::IoStore::Serialization::V1::EOnDemandTocReaderOptions`  
`enum class EOnDemandTocReaderOptions : uint32`  
_L355-359_
- L357 _public enumerator_ `None = 0`
- L358 _public enumerator_ `MemoryMap = (1 << 0)`

#### class `UE::IoStore::Serialization::V1::FOnDemandTocReader`  
`class FOnDemandTocReader`  
_L363-396_
- L366 _public prototype_ `FOnDemandTocReader() = default;`
- L367 _public prototype_ `FOnDemandTocReader(FOnDemandTocReader&&) = default;`
- L368 _public prototype_ `FOnDemandTocReader& operator=(FOnDemandTocReader&&) = default;`
- L370 _public function_ `FDateTime CreationTime() const`
- L371 _public function_ `FUtf8StringView BuildVersion() const`
- L372 _public function_ `FUtf8StringView TargetPlatform() const`
- L373 _public function_ `FUtf8StringView ChunksDirectory() const`
- L374 _public function_ `FUtf8StringView HostGroupName() const`
- L375 _public function_ `FUtf8StringView CompressionFormat() const`
- L376 _public prototype_ `FUtf8StringView GetString(FOnDemandStringEntry StringEntry) const;`
- L378 _public function_ `TConstArrayView<FOnDemandContainerEntry> Containers() const`
- L380 _public prototype_ `TIoStatusOr<FOnDemandContainerTocView> ReadContainer( const FOnDemandContainerEntry& Container, FOnDemandTocStorage& Storage, EOnDemandTocReaderOptions Options) const;`
- L384 _public prototype_ `static TIoStatusOr<FOnDemandTocReader> Read(const FString& Filename);`
- L387 _private prototype_ `FOnDemandTocReader(const FString& Filename, FIoBuffer Buffer);`
- L388 _private prototype_ `FOnDemandTocReader(const FOnDemandTocReader&) = delete;`
- L389 _private prototype_ `FOnDemandTocReader& operator=(const FOnDemandTocReader&) = delete;`
- L391 _private member_ `FString Filename;`
- L392 _private member_ `FIoBuffer Buffer;`
- L393 _private member_ `const FOnDemandTocHeader* Header = nullptr;`
- L394 _private member_ `const UTF8CHAR* StringTable = nullptr;`
- L395 _private member_ `TConstArrayView<FOnDemandContainerEntry> ContainerEntries;`

#### struct `UE::IoStore::Serialization::V2::FOnDemandPartitionEntry`  
`struct FOnDemandPartitionEntry`  
_L416-420_
- L418 _public member_ `FIoHash Hash = FIoHash::Zero;`
- L419 _public member_ `uint32 Size = 0;`

#### struct `UE::IoStore::Serialization::V2::FOnDemandChunkEntry`  
`struct FOnDemandChunkEntry`  
_L424-434_
- L426 _public function_ `uint32 GetDiskSize() const`
- L428 _public member_ `FOnDemandChunkHash Hash;`
- L429 _public member_ `uint32 PartitionIndex = 0;`
- L430 _public member_ `uint32 PartitionOffset = 0;`
- L431 _public member_ `uint32 RawSize = 0;`
- L432 _public member_ `uint32 EncodedSize = 0;`
- L433 _public member_ `FOnDemandChunkBlockInfo BlockInfo;`

#### struct `UE::IoStore::Serialization::V2::FOnDemandContainerTocView`  
`struct FOnDemandContainerTocView`  
_L438-449_
- L440 _public member_ `FOnDemandContainerTocHeaderView Header;`
- L441 _public member_ `TConstArrayView<FOnDemandPartitionEntry> PartitionEntries;`
- L442 _public member_ `TConstArrayView<FIoChunkId> ChunkIds;`
- L443 _public member_ `TConstArrayView<FOnDemandChunkEntry> ChunkEntries;`
- L444 _public member_ `TConstArrayView<uint32> BlockSizes;`
- L445 _public member_ `TConstArrayView<FIoBlockHash> BlockHashes;`
- L446 _public member_ `TConstArrayView<FOnDemandTagSetEntry> TagSets;`
- L447 _public member_ `TConstArrayView<uint32> TagSetIndices;`
- L448 _public member_ `FIoBuffer ContainerHeaderChunk;` — FIoContainerHeader

#### class `UE::IoStore::Serialization::V2::FOnDemandTocReader`  
`class FOnDemandTocReader`  
_L452-485_
- L455 _public prototype_ `FOnDemandTocReader() = default;`
- L456 _public prototype_ `FOnDemandTocReader(FOnDemandTocReader&&) = default;`
- L457 _public prototype_ `FOnDemandTocReader& operator=(FOnDemandTocReader&&) = default;`
- L459 _public function_ `FDateTime CreationTime() const`
- L460 _public function_ `FUtf8StringView BuildVersion() const`
- L461 _public function_ `FUtf8StringView TargetPlatform() const`
- L462 _public function_ `FUtf8StringView ChunksDirectory() const`
- L463 _public function_ `FUtf8StringView HostGroupName() const`
- L464 _public function_ `FUtf8StringView CompressionFormat() const`
- L465 _public prototype_ `FUtf8StringView GetString(FOnDemandStringEntry StringEntry) const;`
- L467 _public function_ `TConstArrayView<FOnDemandContainerEntry> Containers() const`
- L469 _public prototype_ `TIoStatusOr<FOnDemandContainerTocView> ReadContainer( const FOnDemandContainerEntry& Container, FOnDemandTocStorage& Storage, EOnDemandTocReaderOptions Options) const;`
- L473 _public prototype_ `static TIoStatusOr<FOnDemandTocReader> Read(const FString& Filename);`
- L476 _private prototype_ `FOnDemandTocReader(const FString& Filename, FIoBuffer Buffer);`
- L477 _private prototype_ `FOnDemandTocReader(const FOnDemandTocReader&) = delete;`
- L478 _private prototype_ `FOnDemandTocReader& operator=(const FOnDemandTocReader&) = delete;`
- L480 _private member_ `FString Filename;`
- L481 _private member_ `FIoBuffer Buffer;`
- L482 _private member_ `const FOnDemandTocHeader* Header = nullptr;`
- L483 _private member_ `const UTF8CHAR* StringTable = nullptr;`
- L484 _private member_ `TConstArrayView<FOnDemandContainerEntry> ContainerEntries;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L24 _typedef_ `using FIoBlockHash = uint32;`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace IoStore` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace IoStore` (scope `UE`)
- L30 _namespace_ `namespace Serialization` (scope `UE::IoStore`)
- L153 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandContainerEntryFlags);` (scope `UE::IoStore::Serialization`)
- L204 _namespace_ `namespace V1` (scope `UE::IoStore::Serialization`)
- L360 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandTocReaderOptions);` (scope `UE::IoStore::Serialization::V1`)
- L401 _namespace_ `namespace V2` (scope `UE::IoStore::Serialization`)
- L405 _typedef_ `using FOnDemandStringEntry = V1::FOnDemandStringEntry;` (scope `UE::IoStore::Serialization::V2`)
- L406 _typedef_ `using FOnDemandTocHeader = V1::FOnDemandTocHeader;` (scope `UE::IoStore::Serialization::V2`)
- L407 _typedef_ `using FOnDemandContainerEntry = V1::FOnDemandContainerEntry;` (scope `UE::IoStore::Serialization::V2`)
- L408 _typedef_ `using FOnDemandChunkBlockInfo = V1::FOnDemandChunkBlockInfo;` (scope `UE::IoStore::Serialization::V2`)
- L409 _typedef_ `using FOnDemandTagSetEntry = V1::FOnDemandTagSetEntry;` (scope `UE::IoStore::Serialization::V2`)
- L410 _typedef_ `using FOnDemandContainerTocHeaderView = V1::FOnDemandContainerTocHeaderView;` (scope `UE::IoStore::Serialization::V2`)
- L411 _typedef_ `using EOnDemandTocReaderOptions = V1::EOnDemandTocReaderOptions;` (scope `UE::IoStore::Serialization::V2`)
- L412 _typedef_ `using FOnDemandChunkHash = FHash96;` (scope `UE::IoStore::Serialization::V2`)
- L413 _typedef_ `using FOnDemandPartitionHash = FIoHash;` (scope `UE::IoStore::Serialization::V2`)
- L492 _prototype_ `FStringBuilderBase& operator<<(FStringBuilderBase& Sb, UE::IoStore::Serialization::EOnDemandContainerEntryFlags Flags);`
- L493 _prototype_ `FString LexToString(UE::IoStore::Serialization::EOnDemandContainerEntryFlags Flags);`

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Public/IO/HttpIoDispatcher.h` (Public)


#### enum `UE::EIoHttpFlags`  
`enum class EIoHttpFlags`  
_L41-51_
- desc: Flags for controlling the behavior of an HTTP request.
- L44 _public enumerator_ `None = 0` — No additional flags.
- L46 _public enumerator_ `ReadCache = (1 << 0)` — Whether to read from the HTTP cache.
- L48 _public enumerator_ `ResponseHeaders = (1 << 1)` — Whether to include response headers.
- L50 _public enumerator_ `Default = ReadCache` — Default flags.

#### struct `UE::FIoHttpRange`  
`struct FIoHttpRange`  
_L55-78_
- desc: Represents a range within a resource.
- L57 _public prototype_ `FIoHttpRange() = default;`
- L58 _public prototype_ `explicit inline FIoHttpRange(uint32 InMin, uint32 InMax);`
- L60 _public function_ `[[nodiscard]] bool IsValid() const`
- L61 _public function_ `[[nodiscard]] uint32 GetMin() const`
- L62 _public function_ `[[nodiscard]] uint32 GetMax() const`
- L63 _public function_ `[[nodiscard]] uint32 GetSize() const`
- L64 _public prototype_ `[[nodiscard]] inline FIoHttpRange Expand(const FIoHttpRange& Other) const;`
- L65 _public prototype_ `inline FIoHttpRange& ExpandInline(const FIoHttpRange& Other);`
- L67 _public prototype_ `[[nodiscard]] inline FIoOffsetAndLength ToOffsetAndLength() const;`
- L68 _public prototype_ `static inline FIoHttpRange FromOffsetAndLength(const FIoOffsetAndLength& OffsetAndLength);`
- L70 _public function_ `[[nodiscard]] bool operator==(const FIoHttpRange& Other) const`
- L71 _public function_ `[[nodiscard]] bool operator!=(const FIoHttpRange& Other) const`
- L72 _public function_ `[[nodiscard]] FIoHttpRange operator+(const FIoHttpRange& Other) const`
- L73 _public function_ `FIoHttpRange& operator+=(const FIoHttpRange& Other)`
- L76 _private member_ `uint32 Min = MAX_uint32;`
- L77 _private member_ `uint32 Max = MIN_uint32;`
- L80 _function_ `FIoHttpRange::FIoHttpRange(uint32 InMin, uint32 InMax) : Min(InMin) , Max(InMax)`
- L86 _function_ `FIoHttpRange& FIoHttpRange::ExpandInline(const FIoHttpRange& Other)`
- L102 _function_ `FIoHttpRange FIoHttpRange::Expand(const FIoHttpRange& Other) const`
- L109 _function_ `FIoOffsetAndLength FIoHttpRange::ToOffsetAndLength() const`
- L114 _function_ `FIoHttpRange FIoHttpRange::FromOffsetAndLength(const FIoOffsetAndLength& OffsetAndLength)`

#### class `UE::FIoHttpMetadata`  
`class FIoHttpMetadata`  
_L127-141_
- desc: Non shipping metadata about an HTTP request.
- L130 _public prototype_ `FIoHttpMetadata();`
- L131 _public prototype_ `FIoHttpMetadata(const FIoChunkId& ChunkId);`
- L132 _public prototype_ `~FIoHttpMetadata();`
- L133 _public prototype_ `void SetChunkId(const FIoChunkId& ChunkId);`
- L134 _public prototype_ `const FIoChunkId& GetChunkId() const;`
- L139 _private member_ `TSharedPtr<FMetadata> Metadata;`

#### struct `UE::FIoHttpOptions`  
`struct FIoHttpOptions`  
_L144-180_
- desc: Options for controlling the behavior of an HTTP request.
- L147 _public prototype_ `inline FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags, const FIoHttpRange& InRange, const FIoHash& CacheKey, FIoHttpMetadata Metadata);`
- L148 _public prototype_ `inline FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags, const FIoHttpRange& InRange, const FIoHash& CacheKey);`
- L149 _public prototype_ `inline FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags, const FIoHttpRange& InRange);`
- L150 _public prototype_ `inline FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags);`
- L151 _public prototype_ `inline FIoHttpOptions(int32 InPriority, int32 InRetryCount);`
- L152 _public prototype_ `inline explicit FIoHttpOptions(int32 InPriority);`
- L153 _public prototype_ `FIoHttpOptions() = default;`
- L155 _public function_ `const FIoHash GetCacheKey() const`
- L156 _public function_ `const FIoHttpRange& GetRange() const`
- L157 _public function_ `int32 GetPriority() const`
- L158 _public function_ `int32 GetRetryCount() const`
- L159 _public function_ `EIoHttpFlags GetFlags() const`
- L160 _public function_ `uint8 GetCategory() const`
- L161 _public function_ `const FIoHttpMetadata& GetMetadata() const`
- L163 _public function_ `void SetCacheKey(const FIoHash& InCacheKey)`
- L164 _public function_ `void SetRange(const FIoHttpRange InRange)`
- L165 _public function_ `void SetPriority(int32 InPriority)`
- L166 _public function_ `void SetRetryCount(int32 InRetryCount)`
- L167 _public function_ `void SetCategory(uint8 InCategory)`
- L168 _public function_ `void SetMetadata(FIoHttpMetadata&& InMeta)`
- L170 _public member_ `static const FIoHttpOptions Default;`
- L173 _private member_ `FIoHash CacheKey = FIoHash::Zero;`
- L174 _private member_ `FIoHttpRange Range;`
- L175 _private member_ `int32 Priority = 0;`
- L176 _private member_ `int32 RetryCount = 0;`
- L177 _private member_ `EIoHttpFlags Flags = EIoHttpFlags::Default;`
- L178 _private member_ `uint8 Category = 0;`
- L179 _private member_ `FIoHttpMetadata Metadata;`
- L182 _function_ `FIoHttpOptions::FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags, const FIoHttpRange& InRange, const FIoHash& InCacheKey, FIoHttpMetadata InMetadata) : CacheKey(InCacheKey) , Range(InRange) , Priority(InPriority) , RetryCount(InRetryCount) , Flags(InFlags) , Metadata(InMetadata)`
- L192 _function_ `FIoHttpOptions::FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags, const FIoHttpRange& InRange, const FIoHash& InCacheKey) : CacheKey(InCacheKey) , Range(InRange) , Priority(InPriority) , RetryCount(InRetryCount) , Flags(InFlags)`
- L201 _function_ `FIoHttpOptions::FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags, const FIoHttpRange& InRange) : Range(InRange) , Priority(InPriority) , RetryCount(InRetryCount) , Flags(InFlags)`
- L209 _function_ `FIoHttpOptions::FIoHttpOptions(int32 InPriority, int32 InRetryCount, EIoHttpFlags InFlags) : Priority(InPriority) , RetryCount(InRetryCount) , Flags(InFlags)`
- L216 _function_ `FIoHttpOptions::FIoHttpOptions(int32 InPriority, int32 InRetryCount) : Priority(InPriority) , RetryCount(InRetryCount)`
- L222 _function_ `FIoHttpOptions::FIoHttpOptions(int32 InPriority) : Priority(InPriority)`

#### class `UE::FIoHttpHeaders`  
`class FIoHttpHeaders`  
_L228-254_
- desc: HTTP headers.
- L231 _public prototype_ `FIoHttpHeaders() = default;`
- L232 _public prototype_ `FIoHttpHeaders(const FIoHttpHeaders&) = default;`
- L233 _public prototype_ `FIoHttpHeaders(FIoHttpHeaders&&) = default;`
- L234 _public prototype_ `FIoHttpHeaders& Add(FAnsiString&& HeaderName, FAnsiString&& HeaderValue);`
- L235 _public prototype_ `FIoHttpHeaders& Add(FAnsiStringView HeaderName, FAnsiStringView HeaderValue);`
- L236 _public prototype_ `FAnsiStringView Get(FAnsiStringView Key) const;`
- L237 _public prototype_ `FAnsiStringView Get(const FAnsiString& Key) const;`
- L238 _public prototype_ `TArray<FAnsiString> ToArray() &&;`
- L239 _public function_ `TConstArrayView<FAnsiString> ToArrayView() const`
- L241 _public prototype_ `static FIoHttpHeaders Create(FAnsiString&& HeaderName, FAnsiString&& HeaderValue);`
- L242 _public prototype_ `static FIoHttpHeaders Create(FAnsiStringView HeaderName, FAnsiStringView HeaderValue);`
- L243 _public prototype_ `static FIoHttpHeaders Create(TArray<FAnsiString>&& Headers);`
- L245 _public function_ `FIoHttpHeaders& operator=(const FIoHttpHeaders& Other)`
- L246 _public function_ `FIoHttpHeaders& operator=(FIoHttpHeaders&& Other)`
- L249 _private function_ `FIoHttpHeaders(TArray<FAnsiString>&& InHeaders) : Headers(MoveTemp(InHeaders))`
- L253 _private member_ `TArray<FAnsiString> Headers;` — TODO: Make this better

#### class `UE::FIoRelativeUrl`  
`class FIoRelativeUrl`  
_L257-281_
- desc: A relative URL from the host.
- L260 _public typedef_ `using ElementType = ANSICHAR;`
- L262 _public prototype_ `FIoRelativeUrl() = default;`
- L263 _public function_ `bool IsEmpty() const`
- L264 _public function_ `int32 Len() const`
- L265 _public function_ `const ANSICHAR* ToString() const`
- L266 _public function_ `FAnsiStringView GetView() const`
- L268 _public function_ `const ANSICHAR* operator*() const`
- L274 _public prototype_ `static FIoRelativeUrl From(FAnsiStringView Url);`
- L277 _private function_ `explicit FIoRelativeUrl(FAnsiStringView InUrl) : Url(InUrl)`
- L280 _private member_ `TSharedString<ElementType> Url;`

#### class `UE::FIoHttpRequest`  
`class FIoHttpRequest`  
_L288-311_
- desc: An HTTP request handle. The handle needs to be keept alive until the completion callback has been triggered.
- L291 _public prototype_ `FIoHttpRequest() = default;`
- L292 _public function_ `explicit FIoHttpRequest(IIoHttpRequestHandle* InHandle) : Handle(InHandle)`
- L294 _public function_ `FIoHttpRequest(FIoHttpRequest&& Other) : Handle(MoveTemp(Other.Handle))`
- L297 _public function_ `bool IsValid() const`
- L298 _public prototype_ `void Cancel();`
- L299 _public prototype_ `void UpdatePriorty(int32 NewPriority);`
- L300 _public prototype_ `EIoErrorCode Status() const;`
- L301 _public function_ `IIoHttpRequestHandle* GetHandle()`
- L303 _public prototype_ `FIoHttpRequest& operator=(const FIoHttpRequest&) = delete;`
- L304 _public prototype_ `FIoHttpRequest& operator=(FIoHttpRequest&& Other);`
- L307 _private function_ `FIoHttpRequest(const FIoHttpRequest& Other) : Handle(Other.Handle)`
- L310 _private member_ `TRefCountPtr<IIoHttpRequestHandle> Handle;`

#### enum `UE::EIoHttpResponseFlags`  
`enum class EIoHttpResponseFlags : uint8`  
_L314-320_
- desc: Flags describing a HTTP response.
- L317 _public enumerator_ `None = 0` — No additional flags.
- L319 _public enumerator_ `Cached = (1 << 0)` — The response was retrieved from the cache.

#### class `UE::FIoHttpResponse`  
`class FIoHttpResponse`  
_L324-353_
- desc: A HTTP response.
- L327 _public prototype_ `FIoHttpResponse() = delete;`
- L328 _public prototype_ `~FIoHttpResponse() = default;`
- L330 _public prototype_ `inline FIoHttpResponse(const FIoHash& InCacheKey, const FIoBuffer& InBody, EIoErrorCode InErrorCode, uint32 InStatusCode, EIoHttpResponseFlags InFlags);`
- L331 _public prototype_ `inline FIoHttpResponse(const FIoHash& InCacheKey, FIoHttpHeaders&& InHeaders, FIoBuffer&& InBody, EIoErrorCode InErrorCode, uint32 InStatusCode, EIoHttpResponseFlags InFlags);`
- L332 _public function_ `FIoHttpResponse(EIoErrorCode InErrorCode, uint32 InStatusCode) : ErrorCode(InErrorCode) , StatusCode(InStatusCode)`
- L336 _public function_ `const FIoHttpHeaders& GetHeaders() const`
- L337 _public function_ `const FIoBuffer& GetBody() const`
- L338 _public function_ `const FIoHash& GetCacheKey() const`
- L339 _public function_ `EIoErrorCode GetErrorCode() const`
- L340 _public function_ `uint32 GetStatusCode() const`
- L341 _public function_ `EIoHttpResponseFlags GetFlags() const`
- L342 _public function_ `bool IsOk() const`
- L343 _public function_ `bool IsCancelled() const`
- L344 _public function_ `bool IsCached() const`
- L347 _private member_ `FIoHash CacheKey;`
- L348 _private member_ `FIoHttpHeaders Headers;`
- L349 _private member_ `FIoBuffer Body;`
- L350 _private member_ `EIoErrorCode ErrorCode;`
- L351 _private member_ `uint32 StatusCode = 0;`
- L352 _private member_ `EIoHttpResponseFlags Flags = EIoHttpResponseFlags::None;`
- L355 _function_ `FIoHttpResponse::FIoHttpResponse(const FIoHash& InCacheKey, const FIoBuffer& InBody, EIoErrorCode InErrorCode, uint32 InStatusCode, EIoHttpResponseFlags InFlags) : CacheKey(InCacheKey) , Body(InBody) , ErrorCode(InErrorCode) , StatusCode(InStatusCode) , Flags(InFlags)`
- L364 _function_ `FIoHttpResponse::FIoHttpResponse(const FIoHash& InCacheKey, FIoHttpHeaders&& InHeaders, FIoBuffer&& InBody, EIoErrorCode InErrorCode, uint32 InStatusCode, EIoHttpResponseFlags InFlags) : CacheKey(InCacheKey) , Headers(MoveTemp(InHeaders)) , Body(MoveTemp(InBody)) , ErrorCode(InErrorCode) , StatusCode(InStatusCode) , Flags(InFlags)`

#### class `UE::FIoHttpBatch`  
`class FIoHttpBatch`  
_L378-419_
- desc: Issue one or more HTTP request in a batch.
- L381 _public prototype_ `FIoHttpBatch(const FIoHttpRequest&) = delete;`
- L382 _public function_ `FIoHttpBatch(FIoHttpBatch&& Other) : First(Other.First), Last(Other.Last)`
- L389 _public prototype_ `[[nodiscard]] FIoHttpRequest Get(const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, FIoHttpHeaders&& Headers, const FIoHttpOptions& Options, const FIoHash& ChunkHash, FIoHttpRequestCompleted&& OnCompleted);`
- L395 _public prototype_ `[[nodiscard]] FIoHttpRequest Get(const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, FIoHttpHeaders&& Headers, const FIoHttpOptions& Options, FIoHttpRequestCompleted&& OnCompleted);`
- L400 _public prototype_ `[[nodiscard]] FIoHttpRequest Get(const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, FIoHttpHeaders&& Headers, FIoHttpRequestCompleted&& OnCompleted);`
- L404 _public prototype_ `[[nodiscard]] FIoHttpRequest Get(const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, FIoHttpRequestCompleted&& OnCompleted);`
- L407 _public prototype_ `void Issue();`
- L409 _public prototype_ `FIoHttpBatch& operator=(const FIoHttpBatch&) = delete;`
- L410 _public prototype_ `FIoHttpBatch& operator=(FIoHttpBatch&& Other) = delete;`
- L414 _private prototype_ `FIoHttpBatch() = default;`
- L417 _private member_ `IIoHttpRequestHandle* First = nullptr;` — The batch relies and the caller keeping a reference to each handle
- L418 _private member_ `IIoHttpRequestHandle* Last = nullptr;`

#### class `UE::FHttpIoDispatcher`  
`class FHttpIoDispatcher`  
_L422-456_
- desc: HTTP I/O dispatcher .
- L425 _public prototype_ `[[nodiscard]] static bool IsInitialized();`
- L426 _public prototype_ `[[nodiscard]] static FIoStatus Initialize(TSharedPtr<class IHttpIoDispatcher> Dispatcher);`
- L427 _public prototype_ `[[nodiscard]] static FIoStatus Shutdown();`
- L429 _public prototype_ `static void GetHttpStats(FOnDemandHttpStats& Out);`
- L430 _public prototype_ `[[nodiscard]] static FIoStatus RegisterHostGroup(const FName& HostGroup, TConstArrayView<FAnsiString> HostNames, FAnsiStringView TestUrl);`
- L431 _public prototype_ `[[nodiscard]] static FIoStatus RegisterHostGroup(const FName& HostGroup, TConstArrayView<FAnsiString> HostNames);`
- L432 _public prototype_ `[[nodiscard]] static FIoStatus RegisterHostGroup(const FName& HostGroup, FAnsiStringView HostName, FAnsiStringView TestUrl);`
- L433 _public prototype_ `[[nodiscard]] static FIoStatus RegisterHostGroup(const FName& HostGroup, FAnsiStringView HostName);`
- L434 _public prototype_ `[[nodiscard]] static bool IsHostGroupRegistered(const FName& HostGroup);`
- L435 _public prototype_ `[[nodiscard]] static bool IsHostGroupOk(const FName& HostGroup);`
- L437 _public prototype_ `[[nodiscard]] static FIoHttpBatch NewBatch();`
- L438 _public prototype_ `[[nodiscard]] static FIoHttpRequest Get(const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, FIoHttpHeaders&& Headers, const FIoHttpOptions& Options, FIoHttpRequestCompleted&& OnCompleted);`
- L443 _public prototype_ `[[nodiscard]] static FIoHttpRequest Get(const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, FIoHttpHeaders&& Headers, FIoHttpRequestCompleted&& OnCompleted);`
- L447 _public prototype_ `[[nodiscard]] static FIoHttpRequest Get(const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, FIoHttpRequestCompleted&& OnCompleted);`
- L451 _public prototype_ `[[nodiscard]] static FIoStatus CacheResponse(const FIoHttpResponse& Response);`
- L452 _public prototype_ `[[nodiscard]] static FIoStatus EvictFromCache(const FIoHttpResponse& Response);`
- L454 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FHostGroupRegistered, const FName&);`
- L455 _public prototype_ `static FHostGroupRegistered& OnHostGroupRegistered();`

#### class `UE::IIoHttpRequestHandle`  
`class IIoHttpRequestHandle : public IRefCountedObject`  
_L459-464_
- inherits: `IRefCountedObject`
- desc: A reference counted HTTP I/O dispatcher request handle.
- L463 _public prototype_ `virtual EIoErrorCode GetStatus() const = 0;`

#### class `UE::IHttpIoDispatcher`  
`class IHttpIoDispatcher`  
_L467-496_
- desc: HTTP I/O dispatcher interface.
- L470 _public typedef_ `using FHostGroupRegistered = FHttpIoDispatcher::FHostGroupRegistered;`
- L472 _public prototype_ `virtual ~IHttpIoDispatcher() = default;`
- L473 _public prototype_ `virtual void Shutdown() = 0;`
- L475 _public prototype_ `virtual void GetHttpStats(FOnDemandHttpStats& Out) const = 0;`
- L476 _public prototype_ `virtual FIoStatus RegisterHostGroup(const FName& HostGroup, TConstArrayView<FAnsiString> HostNames, FAnsiStringView TestUrl) = 0;`
- L477 _public prototype_ `virtual bool IsHostGroupRegistered(const FName& HostGroup) = 0;`
- L478 _public prototype_ `virtual bool IsHostGroupOk(const FName& HostGroup) = 0;`
- L479 _public prototype_ `virtual FHostGroupRegistered& OnHostGroupRegistered() = 0;`
- L481 _public prototype_ `virtual FIoHttpRequest CreateRequest( IIoHttpRequestHandle*& First, IIoHttpRequestHandle*& Last, const FName& HostGroup, const FIoRelativeUrl& RelativeUrl, const FIoHttpOptions& Options, FIoHttpHeaders&& Headers, FIoHttpRequestCompleted&& OnCompleted, const FIoHash* ChunkHash = nullptr) = 0;`
- L490 _public prototype_ `virtual void IssueRequest(IIoHttpRequestHandle& Handle) = 0;`
- L491 _public prototype_ `virtual void CancelRequest(FIoHttpRequest Handle) = 0;`
- L492 _public prototype_ `virtual void UpdateRequestPriority(FIoHttpRequest Handle, int32 NewPriority) = 0;`
- L494 _public prototype_ `virtual FIoStatus CacheResponse(const FIoHttpResponse& Response) = 0;`
- L495 _public prototype_ `virtual FIoStatus EvictFromCache(const FIoHttpResponse& Response) = 0;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpIoDispatcher, Log, All);`
- L24 _macro_ `#define UE_HTTP_METADATA_ENABLED UE_TRACE_ENABLED`
- L26 _macro_ `#define UE_HTTP_METADATA_ENABLED 0`
- L32 _namespace_ `namespace UE`
- L35 _namespace_ `namespace IoStore` (scope `UE`)
- L36 _typedef_ `using FOnDemandHttpStats = IoStore::FOnDemandHttpStats;` (scope `UE`)
- L52 _prototype_ `ENUM_CLASS_FLAGS(EIoHttpFlags);` (scope `UE`)
- L269 _function_ `friend inline bool operator==(const FIoRelativeUrl& Lhs, const FIoRelativeUrl& Rhs)` (scope `UE`)
- L270 _function_ `friend inline bool operator!=(const FIoRelativeUrl& Lhs, const FIoRelativeUrl& Rhs)` (scope `UE`)
- L271 _function_ `friend inline bool operator<(const FIoRelativeUrl& Lhs, const FIoRelativeUrl& Rhs)` (scope `UE`)
- L273 _function_ `friend inline uint32 GetTypeHash(const FIoRelativeUrl& RelativeUrl)` (scope `UE`)
- L321 _prototype_ `ENUM_CLASS_FLAGS(EIoHttpResponseFlags);` (scope `UE`)
- L375 _typedef_ `using FIoHttpRequestCompleted = TUniqueFunction<void(FIoHttpResponse&&)>;` (scope `UE`) — HTTP completion callback.
- L454 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FHostGroupRegistered, const FName&);`

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Public/IO/IoStoreOnDemand.h` (Public)


#### class `UE::IoStore::FOnDemandRequest`  
`class FOnDemandRequest`  
_L46-86_
- desc: Interface for on-demand request types.
- L66 _public prototype_ `virtual ~FOnDemandRequest() = default;` — Destructor.
- L68 _public prototype_ `virtual EStatus GetStatus() const = 0;` — Returns the current status.
- L70 _public function_ `bool IsNone() const` — Returns true if the request is invalid.
- L72 _public function_ `bool IsPending() const` — Returns true if the request is pending.
- L74 _public function_ `bool IsPendingCallbacks() const` — Returns true if the request is issuing callbacks.
- L76 _public function_ `bool IsOk() const` — Returns true if the request was successful.
- L78 _public function_ `bool IsCancelled() const` — Returns true if the request was cancelled.
- L80 _public function_ `bool IsError() const` — Returns true if the request was unsuccessful.
- L82 _public function_ `bool IsCompleted() const` — Returns true if the request is completed.
- L85 _protected prototype_ `FOnDemandRequest() = default;`

#### enum `UE::IoStore::FOnDemandRequest::EStatus`  
`enum EStatus : uint8`  
_L50-64_
- desc: Request status.
- L53 _public enumerator_ `None` — The request has not been issued.
- L55 _public enumerator_ `Pending` — The request is pending.
- L57 _public enumerator_ `PendingCallbacks` — The request is issuing callbacks.
- L59 _public enumerator_ `Ok` — The request completed successfully.
- L61 _public enumerator_ `Cancelled` — The request was cancelled.
- L63 _public enumerator_ `Error` — The request failed.

#### class `UE::IoStore::FOnDemandContentHandle`  
`class FOnDemandContentHandle`  
_L91-127_
- desc: Keeps referenced data pinned in the cache until released.
- L95 _public prototype_ `FOnDemandContentHandle() = default;` — Creates a new invalid content handle.
- L97 _public prototype_ `~FOnDemandContentHandle() = default;` — Destroy the handle and release any referenced content.
- L99 _public prototype_ `FOnDemandContentHandle(const FOnDemandContentHandle& Other) = default;`
- L100 _public prototype_ `FOnDemandContentHandle(FOnDemandContentHandle&& Other) = default;`
- L102 _public prototype_ `FOnDemandContentHandle& operator=(const FOnDemandContentHandle& Other) = default;`
- L103 _public prototype_ `FOnDemandContentHandle& operator=(FOnDemandContentHandle&& Other) = default;`
- L106 _public function_ `void Reset()` — Destroy the handle and release any referenced content.
- L108 _public function_ `bool IsValid() const` — Returns whether the handle is valid.
- L110 _public prototype_ `static FOnDemandContentHandle Create();` — Create a new content handle .
- L112 _public prototype_ `static FOnDemandContentHandle Create(FSharedString DebugName);` — Create a new content handle with a debug name.
- L114 _public prototype_ `static FOnDemandContentHandle Create(FStringView DebugName);` — Create a new content handle with a debug name.
- L118 _public function_ `bool operator==(FOnDemandContentHandle& Other) const`
- L126 _private member_ `FSharedInternalContentHandle Handle;`

#### struct `UE::IoStore::FOnDemandRegisterHostGroupArgs`  
`struct FOnDemandRegisterHostGroupArgs`  
_L130-140_
- desc: Arguments for registering a new host group.
- L133 _public member_ `FName HostGroupName;` — Name of the host group.
- L135 _public member_ `TArray<FString> HostNames;` — List of host name(s).
- L137 _public member_ `FString TestUrl;` — Test URL.
- L139 _public member_ `bool bUseSecureHttp = false;` — Whether to use secure https.

#### struct `UE::IoStore::FOnDemandRegisterHostGroupResult`  
`struct FOnDemandRegisterHostGroupResult`  
_L143-151_
- desc: Holds the result when registering a host group.
- L146 _public function_ `bool IsOk() const` — Returns True if the request succeeded.
- L148 _public member_ `FOnDemandHostGroup HostGroup;` — The registered host group.
- L150 _public member_ `TOptional<UE::UnifiedError::FError> Error;` — Error information about the request.

#### enum `UE::IoStore::EOnDemandMountOptions`  
`enum class EOnDemandMountOptions : uint8`  
_L154-162_
- desc: Options for controlling the behavior of mounted container(s).
- L157 _public enumerator_ `None = 0` — No additional options.
- L159 _public enumerator_ `CallbackOnGameThread = 1 << 2` — Trigger callback on game thread.
- L161 _public enumerator_ `WithSoftReferences = 1 << 3` — Make soft references available

#### struct `UE::IoStore::FOnDemandMountArgs`  
`struct FOnDemandMountArgs`  
_L183-197_
- desc: Arguments for mounting on-demand container TOC(s). On-demand content can be mounted by providing: 1. a serialized TOC 2. a filepath to a TOC on disk 3. a URL from where to fetch the TOC using HTTP The chunk URLs are derived from the provided TOC URL or from the serialized chunks directory property in the TOC, i.e. if the TocRelativeUrl is not specified the TOC ChunksDirectory property needs to form a qualified path from the host. Example: http(s)://<Host>/<TocRelativePath>/chunks/<1-Byte Hex>/<hash>.iochunk http(s)://<Host>/<TOC.ChunksDirectory>/chunks/<1-Byte Hex>/<hash>.iochunk Host group parameters does not need to be specific when mounting on-demand containers. The containers will be deferred until the specified host group is registered.
- L186 _public member_ `FString MountId;` — Mandatory ID to be used for unmounting all container file(s) included in the TOC.
- L188 _public member_ `FString TocRelativeUrl;` — Relative URL from the primary endpoint from where to download the TOC.
- L190 _public member_ `FString FilePath;` — Serialize the TOC from the specified file path.
- L192 _public member_ `FName HostGroupName = NAME_None;` — Name of a new or existing host group.
- L194 _public member_ `FOnDemandHostGroup HostGroup;` — List of URLs from where to download the chunks.
- L196 _public member_ `EOnDemandMountOptions Options = EOnDemandMountOptions::None;` — Mount options.

#### struct `UE::IoStore::FOnDemandMountResult`  
`struct FOnDemandMountResult`  
_L200-216_
- desc: Holds information about a mount request.
- L203 _public member_ `FString MountId;` — The mount ID used for mounting the container(s).
- L205 _public member_ `FIoStatus Status;` — The status of the mount request.
- L207 _public member_ `double DurationInSeconds = 0.0;` — Duration in seconds.
- L215 _public prototype_ `void LogResult();` — Prints the result to the log. If the result was a success then nothing will be logged. If the mount failed on EIoErrorCode::PendingHostGroup then the result will be printed with 'log' verbosity. All other results will be printed with 'error' verbosity.

#### struct `UE::IoStore::EOnDemandInstallCasTypeNS`  
`struct EOnDemandInstallCasTypeNS`  
_L228-236_
- desc: Specifies a particular CAS Type when relevant

#### enum `UE::IoStore::EOnDemandInstallCasTypeNS::Enum`  
`enum Enum : uint8`  
_L230-235_
- L232 _public enumerator_ `ON_DEMAND_INSTALL_CAS_TYPE_LIST(ON_DEMAND_INSTALL_DECLARE_CAS_TYPE) Count`
- L234 _public enumerator_ `None = 0xff`

#### enum `UE::IoStore::EOnDemandInstallOptions`  
`enum class EOnDemandInstallOptions : uint16`  
_L242-256_
- desc: Options for controlling the behavior of the install request.
- L245 _public enumerator_ `None = 0` — No additional options.
- L247 _public enumerator_ `CallbackOnGameThread = 1 << 0` — Trigger callback on game thread.
- L249 _public enumerator_ `InstallSoftReferences = 1 << 1` — Follow soft references when gathering packages to install.
- L251 _public enumerator_ `InstallOptionalBulkData = 1 << 2` — Install optional bulk data.
- L253 _public enumerator_ `DoNotDownload = 1 << 3` — Do not install any data, only succeed if all data is already cached.
- L255 _public enumerator_ `AllowMissingDependencies = 1 << 4` — Do not return an error if missing iochunk dependencies are missing.

#### struct `UE::IoStore::FOnDemandInstallArgs`  
`struct FOnDemandInstallArgs`  
_L260-276_
- desc: Arguments for installing/downloading on-demand content.
- L263 _public member_ `FString MountId;` — Install all content from containers matching this mount ID.
- L265 _public member_ `TArray<FString> TagSets;` — Install content matching a set of tag(s) and optionally the mount ID.
- L267 _public member_ `TArray<FPackageId> PackageIds;` — Package ID's to install.
- L269 _public member_ `FOnDemandContentHandle ContentHandle;` — Content handle.
- L271 _public member_ `EOnDemandInstallOptions Options = EOnDemandInstallOptions::None;` — Install options.
- L273 _public member_ `int32 Priority = 0;` — Priority.
- L275 _public member_ `FSharedString DebugName;` — Optional debug name .

#### struct `UE::IoStore::FOnDemandInstallProgress`  
`struct FOnDemandInstallProgress`  
_L279-333_
- desc: Holds information about progress for an install request.
- L282 _public member_ `uint64 TotalContentSize = 0;` — The total size of the requested content.
- L284 _public member_ `uint64 TotalInstallSize = 0;` — The total size to be installed/downloaded (<= TotalContentSize).
- L286 _public member_ `uint64 CurrentInstallSize = 0;` — The size currently installed/downloaded (<= TotalInstallSize).
- L288 _public function_ `FOnDemandInstallProgress& Combine(const FOnDemandInstallProgress& Other)`
- L296 _public function_ `uint64 GetTotalDownloadSize() const`
- L301 _public function_ `uint64 GetAlreadyDownloadedSize() const`
- L306 _public function_ `float GetRelativeProgress() const`
- L315 _public function_ `float GetAbsoluteProgress() const`
- L324 _public function_ `uint64 GetCachedSize() const`
- L329 _public function_ `uint64 GetTotalSize() const`

#### struct `UE::IoStore::FOnDemandInstallResult`  
`struct FOnDemandInstallResult`  
_L339-349_
- desc: Holds information about an install request.
- L342 _public function_ `bool IsOk() const` — Returns True if the request succeeded.
- L344 _public member_ `double DurationInSeconds = 0.0;` — Duration in seconds.
- L346 _public member_ `FOnDemandInstallProgress Progress;` — Final progress for the install request.
- L348 _public member_ `TOptional<UE::UnifiedError::FError> Error;` — Error information about the request.

#### class `UE::IoStore::FOnDemandInstallRequest`  
`class FOnDemandInstallRequest final : public FOnDemandRequest`  
_L355-383_
- inherits: `FOnDemandRequest`
- desc: A single-ownership handle to an install request.
- L361 _public prototype_ `FOnDemandInstallRequest() = default;` — Creates an invalid install request.
- L363 _public prototype_ `FOnDemandInstallRequest(FOnDemandInstallRequest&&) = default;`
- L365 _public prototype_ `FOnDemandInstallRequest& operator=(FOnDemandInstallRequest&&) = default;` — Move assignable.
- L367 _public prototype_ `~FOnDemandInstallRequest() = default;` — Destructor.
- L369 _public prototype_ `virtual EStatus GetStatus() const override;` — Returns the current request status.
- L371 _public prototype_ `void Cancel();` — Cancel the install request.
- L373 _public prototype_ `void UpdatePriority(int32 NewPriority);` — Update priority of the install request.
- L376 _private function_ `FOnDemandInstallRequest(FSharedInternalInstallRequest InternalRequest) : Request(InternalRequest)`
- L379 _private prototype_ `FOnDemandInstallRequest(const FOnDemandInstallRequest&) = delete;`
- L380 _private prototype_ `FOnDemandInstallRequest& operator=(const FOnDemandInstallRequest&) = delete;`
- L382 _private member_ `FSharedInternalInstallRequest Request;`

#### enum `UE::IoStore::EOnDemandPurgeOptions`  
`enum class EOnDemandPurgeOptions : uint8`  
_L386-394_
- desc: Options for controlling the behavior of the purge request.
- L389 _public enumerator_ `None = 0` — No additional options.
- L391 _public enumerator_ `CallbackOnGameThread = 1 << 0` — Trigger callback on game thread.
- L393 _public enumerator_ `Defrag = 1 << 1` — Defrag after purging

#### struct `UE::IoStore::FOnDemandPurgeArgs`  
`struct FOnDemandPurgeArgs`  
_L398-406_
- desc: Arguments for purging on-demand content.
- L401 _public member_ `EOnDemandInstallCasType CasType = EOnDemandInstallCasType::General;` — Cas to purge
- L403 _public member_ `EOnDemandPurgeOptions Options = EOnDemandPurgeOptions::None;` — Purge options.
- L405 _public member_ `TOptional<uint64> BytesToPurge;` — Optional Size to purge. If not set will purge all unreferenced blocks.

#### struct `UE::IoStore::FOnDemandPurgeResult`  
`struct FOnDemandPurgeResult`  
_L409-417_
- desc: Holds information about a purge request
- L412 _public function_ `bool IsOk() const` — Returns True if the request succeeded.
- L414 _public member_ `double DurationInSeconds = 0.0;` — Duration in seconds.
- L416 _public member_ `TOptional<UE::UnifiedError::FError> Error;` — Error information about the request.

#### enum `UE::IoStore::EOnDemandDefragOptions`  
`enum class EOnDemandDefragOptions : uint8`  
_L423-429_
- desc: Options for controlling the behavior of the defrag request.
- L426 _public enumerator_ `None = 0` — No additional options.
- L428 _public enumerator_ `CallbackOnGameThread = 1 << 0` — Trigger callback on game thread.

#### struct `UE::IoStore::FOnDemandDefragArgs`  
`struct FOnDemandDefragArgs`  
_L433-441_
- desc: Arguments for defragmenting on-demand content.
- L436 _public member_ `EOnDemandInstallCasType CasType = EOnDemandInstallCasType::General;` — Cas to defrag
- L438 _public member_ `EOnDemandDefragOptions Options = EOnDemandDefragOptions::None;` — Defrag options.
- L440 _public member_ `TOptional<uint64> BytesToFree;` — Optional Size to free. If not set, will defrag all blocks and free all unreferenced chunks.

#### struct `UE::IoStore::FOnDemandDefragResult`  
`struct FOnDemandDefragResult`  
_L444-452_
- desc: Holds information about a defrag request
- L447 _public function_ `bool IsOk() const` — Returns True if the request succeeded.
- L449 _public member_ `double DurationInSeconds = 0.0;` — Duration in seconds.
- L451 _public member_ `TOptional<UE::UnifiedError::FError> Error;` — Error information about the request.

#### enum `UE::IoStore::EOnDemandGetInstallSizeOptions`  
`enum class EOnDemandGetInstallSizeOptions : uint8`  
_L458-466_
- desc: Options for controlling the behavior of the install size request.
- L461 _public enumerator_ `None = 0` — No additional options.
- L463 _public enumerator_ `IncludeSoftReferences = 1 << 0` — Follow soft references when gathering packages to install.
- L465 _public enumerator_ `IncludeOptionalBulkData = 1 << 1` — Include optional bulk data.

#### struct `UE::IoStore::FOnDemandGetInstallSizeArgs`  
`struct FOnDemandGetInstallSizeArgs`  
_L470-480_
- desc: Arguments for getting the size of on-demand content.
- L473 _public member_ `FString MountId;` — Get total install size for containers matching this mount ID.
- L475 _public member_ `TArray<FString> TagSets;` — Get total install size for the specified tag(s) and optionally matching the mount ID.
- L477 _public member_ `TArray<FPackageId> PackageIds;` — Get total install size for the specified package IDs.
- L479 _public member_ `EOnDemandGetInstallSizeOptions Options = EOnDemandGetInstallSizeOptions::None;` — Options

#### struct `UE::IoStore::FOnDemandInstallSizeResult`  
`struct FOnDemandInstallSizeResult`  
_L483-487_
- desc: Holds information about an install size request.
- L486 _public member_ `uint64 InstallSize = 0;` — The total size of the content.

#### enum `UE::IoStore::EOnDemandIsOnDemandOptions`  
`enum class EOnDemandIsOnDemandOptions : uint8`  
_L490-496_
- desc: Options for controlling the behavior of the GetIsOnDemand request.
- L493 _public enumerator_ `None = 0` — No additional options.
- L495 _public enumerator_ `IncludeSoftReferences = 1 << 0` — Follow soft references when gathering packages.

#### struct `UE::IoStore::FOnDemandIsOnDemandArgs`  
`struct FOnDemandIsOnDemandArgs`  
_L500-506_
- desc: Arguments for checking if any on-demand content exists in the dependency graph.
- L503 _public member_ `TArray<FPackageId> PackageIds;` — Return true if any of the specified package IDs has on-demand dependencies.
- L505 _public member_ `EOnDemandIsOnDemandOptions Options = EOnDemandIsOnDemandOptions::None;` — Options

#### struct `UE::IoStore::FOnDemandIsOnDemandResult`  
`struct FOnDemandIsOnDemandResult`  
_L509-512_
- desc: Results for GetIsOnDemand
- L511 _public member_ `bool bIsOnDemand = false;`

#### enum `UE::IoStore::EOnDemandGetCacheUsageOptions`  
`enum class EOnDemandGetCacheUsageOptions : uint8`  
_L515-523_
- desc: Options for controlling the behavior of the install size request.
- L518 _public enumerator_ `None = 0` — No additional options.
- L520 _public enumerator_ `DumpHandlesToLog = 1 << 0` — Dump Handle information to log
- L522 _public enumerator_ `DumpHandlesToResults = 1 << 1` — Dump Handle information to returned FOnDemandInstallCacheUsage

#### struct `UE::IoStore::FOnDemandGetCacheUsageArgs`  
`struct FOnDemandGetCacheUsageArgs`  
_L527-530_
- desc: Arguments for getting the install cache usage.
- L529 _public member_ `EOnDemandGetCacheUsageOptions Options = EOnDemandGetCacheUsageOptions::None;`

#### struct `UE::IoStore::FOnDemandInstallHandleCacheUsage`  
`struct FOnDemandInstallHandleCacheUsage`  
_L532-537_
- L534 _public member_ `UPTRINT HandleId = 0;`
- L535 _public member_ `FSharedString DebugName;`
- L536 _public member_ `uint64 ReferencedBytes = 0;`

#### struct `UE::IoStore::FOnDemandInstallCacheUsage`  
`struct FOnDemandInstallCacheUsage`  
_L540-562_
- desc: Holds information about the install cache usage
- L556 _public member_ `TStaticArray<FCasUsage, EOnDemandInstallCasType::Count> CasUsage;`
- L559 _public member_ `TArray<FOnDemandInstallHandleCacheUsage> ReferencedBytesByHandle;` — Only populated if DumpHandlesToResults is specified

#### struct `UE::IoStore::FOnDemandInstallCacheUsage::FCasUsage`  
`struct FCasUsage`  
_L542-554_
- L544 _public member_ `uint64 MaxSize = 0;`
- L545 _public member_ `uint64 TotalSize = 0;`
- L546 _public member_ `uint64 ReferencedBlockSize = 0;`
- L547 _public member_ `uint64 ReferencedSize = 0;`
- L548 _public member_ `uint64 FragmentedChunksSize = 0;`
- L549 _public member_ `EOnDemandInstallCasType CasType = EOnDemandInstallCasType::None;`
- L551 _public function_ `bool IsValid() const`

#### struct `UE::IoStore::FOnDemandStreamingCacheUsage`  
`struct FOnDemandStreamingCacheUsage`  
_L565-571_
- desc: Holds information about the streaming cache usage
- L567 _public member_ `uint64 MaxSize = 0;`
- L568 _public member_ `uint64 TotalSize = 0;`

#### struct `UE::IoStore::FOnDemandCacheUsage`  
`struct FOnDemandCacheUsage`  
_L574-578_
- desc: Holds information about install and streaming cache usage
- L576 _public member_ `FOnDemandInstallCacheUsage InstallCache;`
- L577 _public member_ `FOnDemandStreamingCacheUsage StreamingCache;`

#### struct `UE::IoStore::FOnDemandVerifyCacheResult`  
`struct FOnDemandVerifyCacheResult`  
_L581-589_
- desc: Result from verifying the install cache.
- L584 _public function_ `bool IsOk() const` — Returns True if the request succeeded.
- L586 _public member_ `double DurationInSeconds = 0.0;` — Duration in seconds.
- L588 _public member_ `TOptional<UE::UnifiedError::FError> Error;` — Error information about the request.

#### class `UE::IoStore::FOnDemandHttpStats`  
`class FOnDemandHttpStats`  
_L595-609_
- desc: Container for http stats
- L599 _public prototype_ `FOnDemandHttpStats();`
- L600 _public prototype_ `~FOnDemandHttpStats();`
- L601 _public prototype_ `uint32 GetRecvKiBps() const;`
- L602 _public prototype_ `void GetRecvKiBps(uint32 (&Out)[SAMPLE_COUNT]) const;`
- L603 _public prototype_ `uint32 GetTotalRecvKiB() const;`
- L604 _public prototype_ `uint32 GetTimeToFirstByteMs() const;`
- L608 _private member_ `TUniquePtr<class IOnDemandInternalHttpStats> Internal;`

#### enum `UE::IoStore::FOnDemandHttpStats::(anonymous)`  
`enum`  
_L598-598_

#### class `UE::IoStore::IAnalyticsRecording`  
`class IAnalyticsRecording`  
_L612-623_
- desc: Interface for recording analytics over a given time period
- L615 _public prototype_ `IAnalyticsRecording() = default;`
- L616 _public prototype_ `virtual ~IAnalyticsRecording() = default;`
- L619 _public prototype_ `virtual void Report(TArray<FAnalyticsEventAttribute>& OutAnalyticsArray) const = 0;` — Writes the current value of the analytics to the output array
- L622 _public prototype_ `virtual void StopRecording() = 0;` — Calling this will stop recording. Any calls to ::Report after this point will return the same data

#### struct `UE::IoStore::FOnDemandImmediateAnalytic`  
`struct FOnDemandImmediateAnalytic`  
_L625-629_
- L627 _public member_ `FString EventName;`
- L628 _public member_ `TArray<FAnalyticsEventAttribute> AnalyticsArray;`

#### struct `UE::IoStore::FOnDemandImmediateAnalyticHandler`  
`struct FOnDemandImmediateAnalyticHandler`  
_L631-634_
- L633 _public member_ `TUniqueFunction<void(FOnDemandImmediateAnalytic)> EventHandler;`

#### enum `UE::IoStore::EOnDemandStreamingOptions`  
`enum class EOnDemandStreamingOptions : uint8`  
_L637-643_
- desc: Streaming options (IAS).
- L640 _public enumerator_ `Default = 0` — No special options enabled.
- L642 _public enumerator_ `OptionalBulkDataDisabled = (1 << 0)` — Optional bulk data disabled.

#### class `UE::IoStore::IOnDemandIoStore`  
`class IOnDemandIoStore`  
_L647-766_
- desc: Interface for installing and streaming content on-demand.
- L651 _public prototype_ `virtual ~IOnDemandIoStore() = default;` — Destroy the I/O store.
- L653 _public prototype_ `virtual FIoStatus InitializePostHotfix() = 0;` — Initialize the I/O store. Called after the module feature has been registered.
- L659 _public prototype_ `virtual FOnDemandRegisterHostGroupResult RegisterHostGroup(FOnDemandRegisterHostGroupArgs&& Args) = 0;` — Register a new host group. @param	Args	Request arguments. @return			Error information about the request.
- L665 _public prototype_ `virtual void Mount(FOnDemandMountArgs&& Args, FOnDemandMountCompleted&& OnCompleted) = 0;` — Mount an on-demand container. @param	Args		Mount arguments. @param	OnCompleted	Completion callback.
- L670 _public prototype_ `virtual FIoStatus Unmount(FStringView MountId) = 0;` — Unmount all container(s) associated with the specified mount ID. @param	MountId	The Mount ID passed to the mount call.
- L679 _public prototype_ `virtual FOnDemandInstallRequest Install( FOnDemandInstallArgs&& Args, FOnDemandInstallCompleted&& OnCompleted, FOnDemandInstallProgressed&& OnProgress = nullptr) = 0;` — Install content. @param	Args				The install arguments. @param	OnCompleted			Completion callback. @param	OnProgress			Optional progress callback. @return A handle representing the install request. @see FOnDemandInstallRequest
- L688 _public prototype_ `virtual void Purge(FOnDemandPurgeArgs&& Args, FOnDemandPurgeCompleted&& OnCompleted) = 0;` — Purge the cache. @param	Args		The purge arguments. @param	OnComplete	Completion callback.
- L694 _public prototype_ `virtual void Defrag(FOnDemandDefragArgs&& Args, FOnDemandDefragCompleted&& OnCompleted) = 0;` — Defrag the cache. @param	Args		The defrag arguments. @param	OnComplete	Completion callback.
- L699 _public prototype_ `virtual void Verify(FOnDemandVerifyCacheCompleted&& OnCompleted) = 0;` — Verify the install cache. @param	OnComplete	Completion callback.
- L704 _public prototype_ `virtual TIoStatusOr<FOnDemandInstallSizeResult> GetInstallSize(const FOnDemandGetInstallSizeArgs& Args) const = 0;` — Get the total space in bytes needed to install the specified content. @param Args	Arguments for computing required install size.
- L710 _public prototype_ `virtual FIoStatus GetInstallSizesByMountId(const FOnDemandGetInstallSizeArgs& Args, TMap<FString, uint64>& OutSizesByMountId) const = 0;` — Get the total space in bytes needed to install the specified content. @param Args	Arguments for computing required install size. @return		The total size by mount ID.
- L716 _public prototype_ `virtual FIoStatus GetIsOnDemand(TConstArrayView<FOnDemandIsOnDemandArgs> Args, TArrayView<FOnDemandIsOnDemandResult> OutResults) const = 0;` — Query whether any of the specified packages have on-demand dependencies. @param Args	Array of package sets to query. @return		One result per package set, in the same order as Args.
- L722 _public prototype_ `TIoStatusOr<FOnDemandIsOnDemandResult> GetIsOnDemand(const FOnDemandIsOnDemandArgs& Args) const;` — Query whether any of the specified packages have on-demand dependencies. @param Args	Package set to query. @return		Results indicating whether on-demand dependencies exist.
- L724 _public prototype_ `virtual FOnDemandCacheUsage GetCacheUsage(const FOnDemandGetCacheUsageArgs& Args) const = 0;` — Returns the total cache size in bytes.
- L726 _public prototype_ `virtual void DumpMountedContainersToLog() const = 0;` — Dump information about mounted containers to the log
- L728 _public prototype_ `virtual bool IsOnDemandStreamingEnabled() const = 0;` — Return if the OnDemand streaming system is enabled.
- L730 _public prototype_ `virtual void SetStreamingOptions(EOnDemandStreamingOptions Options) = 0;` — Set streaming options.
- L732 _public prototype_ `virtual void GetHttpStats(FOnDemandHttpStats& Out) const = 0;` — Returns statistics about the network
- L737 _public prototype_ `virtual void ReportAnalytics(TArray<FAnalyticsEventAttribute>& OutAnalyticsArray) const = 0;` — Reports the statistics for the current OnDemandBackend. It will record any events that have occurred from the last time that this was called. This is a legacy method, prefer using StartAnalyticsRecording if possible.
- L742 _public prototype_ `virtual TUniquePtr<IAnalyticsRecording> StartAnalyticsRecording() const = 0;` — Create a new analytics interface for the current OnDemandBackend, can be used to record statistics for a set period of time. This can return a nullptr if the analytics system is not enabled. Currently only supports the streaming backend.
- L747 _public prototype_ `virtual void OnImmediateAnalytic(FOnDemandImmediateAnalyticHandler EventHandler) = 0;` — Report immediate analytics events that are not recorded over a timespan. Useful for analytics that are better reported as single events.
- L749 _public function_ `virtual void SetDevelopmentExtension(FSharedOnDemandDevelopmentExtension Ctx)` — Set the development extension.
- L751 _public function_ `virtual bool IsDevelopmentModeEnabled() const` — Whether development mode is enabled or not.
- L755 _private prototype_ `virtual FIoStatus Initialize() = 0;` — Initialize the I/O store. Called after the I/O store factory module feature has been registered.
- L757 _private prototype_ `virtual void CancelInstallRequest(FSharedInternalInstallRequest InstallRequest) = 0;` — Cancel the install request.
- L759 _private prototype_ `virtual void UpdateInstallRequestPriority(FSharedInternalInstallRequest InstallRequest, int32 NewPriority) = 0;` — Update the priority for the install request.
- L761 _private prototype_ `virtual void ReleaseContent(class FOnDemandInternalContentHandle& ContentHandle) = 0;` — Release all content referenced by the content handle.

#### class `UE::IoStore::IOnDemandIoStoreFactory`  
`class IOnDemandIoStoreFactory : public IModularFeature`  
_L769-779_
- inherits: `IModularFeature`
- desc: Module feature for creating a concrete implementation of the on-demand I/O store.
- L774 _public member_ `static FName FeatureName;` — Feature name.
- L776 _public prototype_ `virtual IOnDemandIoStore* CreateInstance() = 0;` — Create a new instance of the I/O store.  Called once the feature has been registered.
- L778 _public prototype_ `virtual void DestroyInstance(IOnDemandIoStore* Instance) = 0;` — Destroy the instance.

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L29 _macro_ `#define UE_IAS_CUSTOM_INITIALIZATION 0`
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIoStoreOnDemand, Log, All);`
- L33 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIas, Log, All);`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace IoStore` (scope `UE`)
- L38 _typedef_ `using FSharedOnDemandIoStore = TSharedPtr<class IOnDemandIoStore, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L39 _typedef_ `using FWeakOnDemandIoStore = TWeakPtr<class IOnDemandIoStore, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L40 _typedef_ `using FSharedInternalContentHandle = TSharedPtr<class FOnDemandInternalContentHandle, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L41 _typedef_ `using FSharedInternalInstallRequest = TSharedPtr<class FOnDemandInternalInstallRequest, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L42 _typedef_ `using FSharedOnDemandDevelopmentExtension = TSharedPtr<class IOnDemandDevelopmentExtension, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L163 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandMountOptions);` (scope `UE::IoStore`)
- L219 _typedef_ `using FOnDemandMountCompleted = TUniqueFunction<void(FOnDemandMountResult)>;` (scope `UE::IoStore`) — Mount completion callback.
- L221 _macro_ `#define ON_DEMAND_INSTALL_CAS_TYPE_LIST(XCASTYPE) \`
- L225 _macro_ `#define ON_DEMAND_INSTALL_DECLARE_CAS_TYPE(CasType) CasType,`
- L237 _typedef_ `using EOnDemandInstallCasType = EOnDemandInstallCasTypeNS::Enum;` (scope `UE::IoStore`)
- L257 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandInstallOptions);` (scope `UE::IoStore`)
- L336 _typedef_ `using FOnDemandInstallProgressed = TFunction<void(FOnDemandInstallProgress)>;` (scope `UE::IoStore`) — Install Progress callback.
- L352 _typedef_ `using FOnDemandInstallCompleted = TUniqueFunction<void(FOnDemandInstallResult)>;` (scope `UE::IoStore`) — Install completion callback.
- L420 _typedef_ `using FOnDemandPurgeCompleted = TUniqueFunction<void(FOnDemandPurgeResult)>;` (scope `UE::IoStore`) — Purge completion callback
- L455 _typedef_ `using FOnDemandDefragCompleted = TUniqueFunction<void(FOnDemandDefragResult)>;` (scope `UE::IoStore`) — Defrag completion callback
- L467 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandGetInstallSizeOptions);` (scope `UE::IoStore`)
- L497 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandIsOnDemandOptions);` (scope `UE::IoStore`)
- L524 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandGetCacheUsageOptions);` (scope `UE::IoStore`)
- L592 _typedef_ `using FOnDemandVerifyCacheCompleted = TUniqueFunction<void(FOnDemandVerifyCacheResult)>;` (scope `UE::IoStore`) — Verify cache completion callback.
- L598 _enumerator_ `enum { SAMPLE_COUNT = 8 }; UE_API FOnDemandHttpStats(); UE_API ~FOnDemandHttpStats(); UE_API uint32 GetRecvKiBps() const; UE_API void GetRecvKiBps(uint32 (&Out)[SAMPLE_COUNT]) const; UE_API uint32 GetTotalRecvKiB() const; UE_API uint32 GetTimeToFirstByteMs() const;` (scope `UE::IoStore::FOnDemandHttpStats::__anon5dc39c8e0103`)
- L644 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandStreamingOptions);` (scope `UE::IoStore`)
- L782 _prototype_ `IOnDemandIoStore* TryGetOnDemandIoStore();` (scope `UE::IoStore`) — Returns the on-demand I/O store if available.
- L784 _prototype_ `IOnDemandIoStore& GetOnDemandIoStore();` (scope `UE::IoStore`) — Returns the on-demand I/O store.
- L788 _prototype_ `const TCHAR* LexToString(UE::IoStore::EOnDemandInstallCasType CacheType);`
- L789 _prototype_ `void LexFromString(UE::IoStore::EOnDemandInstallCasType& CacheType, FStringView String);`
- L790 _prototype_ `ENUM_RANGE_BY_COUNT(UE::IoStore::EOnDemandInstallCasType, UE::IoStore::EOnDemandInstallCasType::Count);`

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Public/IO/OnDemandDevelopmentExtension.h` (Public)


#### class `UE::IoStore::IOnDemandDevelopmentExtension`  
`class IOnDemandDevelopmentExtension`  
_L27-61_
- desc: An interface for exceptional scenarios. Note: When running in IAX development mode (-Iax.DevMode), the on-demand package store and install cache backends are given higher priority than the file-based (installed content) backend. This allows content that has not yet been installed via an install request to be loaded by returning 'Missing' or 'UnknownChunkID'. If the chunk ID exists in the 'global.umeta' file, the corresponding package and/or filename will be provided.
- L30 _public prototype_ `virtual ~IOnDemandDevelopmentExtension() = default;`
- L41 _public prototype_ `virtual EPackageStoreEntryStatus GetUnreferencedPackageStoreEntryStatus( FName PackageName, const FPackageId& PackageId, const FPackageStoreEntry& Entry, bool bDevMode) = 0;` — Called when the on-demand package store finds an unreferenced package store entry Note: In shipping builds the package store will return 'NotInstalled' for packages not pinned in the on-demand install cache. This currently halts the package store traversel and affectively fails the package load request. Returning 'Missing' will let lower priority package store backends handle the request. Use 'IsInAsyncLoadingThread() || IsInParallelLoadingThread()' to only trigger calls from the LoadPackage/Async.
- L56 _public prototype_ `virtual EIoErrorCode GetUnreferencedIoChunkStatus( const FIoChunkId& ChunkId, FUtf8StringView Filename, FStringView PackageName, bool bDevMode) = 0;` — Called when an unreferenced I/O store chunk is loaded via the I/O dispatcher interface. This happens when the package loader has resolved the package store entry or when requesting unstructed data via FBulkData. Note: In shipping builds the on-demand install cache will return 'NotInstalled' and fail the request when trying to load an unreferenced I/O store chunk. Return 'UnknownChunkID' to let lower priority I/O dispacher backends handle the I/O request.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IoStore` (scope `UE`)

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Public/IO/OnDemandError.h` (Public)


#### enum `UE::IoStore::OnDemand::ECasErrorCode`  
`enum class ECasErrorCode : uint32`  
_L29-44_
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `InitializeFailed`
- L33 _public enumerator_ `VerifyFailed`
- L34 _public enumerator_ `ReadBlockFailed`
- L35 _public enumerator_ `WriteBlockFailed`
- L36 _public enumerator_ `DeleteBlockFailed`
- L37 _public enumerator_ `CreateJournalFailed`
- L38 _public enumerator_ `ReplayJournalFailed`
- L39 _public enumerator_ `CommitJournalFailed`
- L40 _public enumerator_ `CreateSnapshotFailed`
- L41 _public enumerator_ `LoadSnapshotFailed`
- L42 _public enumerator_ `SaveSnapshotFailed`
- L43 _public enumerator_ `OpenMappedFailed`

#### struct `UE::IoStore::OnDemand::FInstallCacheErrorState`  
`struct FInstallCacheErrorState`  
_L91-102_
- desc: Cache-state snapshot taken at the moment an install-cache error is produced. Used as a plain field on errors that carry cache state directly (InstallCachePurgeError, InstallCacheDefragError) and as the sole field of the pushable InstallCacheErrorContext, so the same data can be attached to errors that originate below the cache layer.
- L93 _public member_ `FIoStatus IoError = FIoStatus(EIoErrorCode::Unknown);`
- L94 _public member_ `const TCHAR* CasType = nullptr;`
- L95 _public member_ `uint64 MaxCacheSize = 0;`
- L96 _public member_ `uint64 CacheSize = 0;`
- L97 _public member_ `uint64 RequestedSize = 0;`
- L98 _public member_ `uint64 DiskTotalBytes = 0;`
- L99 _public member_ `uint64 DiskFreeBytes = 0;`
- L100 _public member_ `uint32 LineNo = uint32(__builtin_LINE());`
- L101 _public member_ `bool bDiskQuerySucceeded = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L16 _prototype_ `void SerializeForLog(FCbWriter& Writer, const FIoChunkId& ChunkId);`
- L17 _prototype_ `void SerializeForLog(FCbWriter& Writer, EIoErrorCode ErrorCode);`
- L18 _prototype_ `void SerializeForLog(FCbWriter& Writer, const FFileSystemError& Error);`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace IoStore` (scope `UE`)
- L22 _prototype_ `void SerializeForLog(FCbWriter& Writer, EOnDemandInstallCasType CasType);` (scope `UE::IoStore`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace IoStore` (scope `UE`)
- L26 _namespace_ `namespace OnDemand` (scope `UE::IoStore`)
- L46 _function_ `inline const TCHAR* ToString(ECasErrorCode Code)` (scope `UE::IoStore::OnDemand`)
- L81 _function_ `inline void SerializeForLog(FCbWriter& Writer, ECasErrorCode Code)` (scope `UE::IoStore::OnDemand`)
- L104 _prototype_ `void SerializeForLog(FCbWriter& Writer, const FInstallCacheErrorState& State);` (scope `UE::IoStore::OnDemand`)
- L205 _namespace_ `namespace UE`
- L205 _namespace_ `namespace IoStore` (scope `UE`)
- L208 _typedef_ `using FResult = TValueOrError<void, UE::UnifiedError::FError>;` (scope `UE::IoStore`)
- L211 _typedef_ `template <typename ResultType> using TResult = TValueOrError<ResultType, UE::UnifiedError::FError>;` (scope `UE::IoStore`)
- L216 _namespace_ `namespace UE`
- L216 _namespace_ `namespace IoStore` (scope `UE`)
- L216 _namespace_ `namespace OnDemand` (scope `UE::IoStore`)
- L220 _function_ `template <typename ResultType> inline UE::IoStore::TResult<ResultType> MakeCasError( UE::IoStore::EOnDemandInstallCasType CasType, ECasErrorCode ErrorCode, EIoErrorCode IoErrorCode, FString&& ErrorMessage, FFileSystemError&& FileSystemError = FFileSystemError(FString()), uint32 SystemErrorCode = FPlatformMisc::GetLastError())` (scope `UE::IoStore::OnDemand`)
- L239 _function_ `inline UE::IoStore::FResult MakeJournalError( ECasErrorCode ErrorCode, EIoErrorCode IoErrorCode, FString&& ErrorMessage, FFileSystemError&& FileSystemError = FFileSystemError(FString()), uint32 SystemErrorCode = FPlatformMisc::GetLastError())` (scope `UE::IoStore::OnDemand`)
- L257 _function_ `template <typename ResultType> inline UE::IoStore::TResult<ResultType> MakeSnapshotError( ECasErrorCode ErrorCode, EIoErrorCode IoErrorCode, FString&& ErrorMessage, FFileSystemError&& FileSystemError = FFileSystemError(FString()), uint32 SystemErrorCode = FPlatformMisc::GetLastError())` (scope `UE::IoStore::OnDemand`)
- L275 _function_ `template <typename ResultType> inline UE::IoStore::TResult<ResultType> MakeSnapshotError( ECasErrorCode ErrorCode, EIoErrorCode IoErrorCode, FString&& ErrorMessage, uint32 SystemErrorCode)` (scope `UE::IoStore::OnDemand`)

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Public/IO/OnDemandHostGroup.h` (Public)


#### class `UE::IoStore::FOnDemandHostGroup`  
`class FOnDemandHostGroup`  
_L17-65_
- desc: Holds a set of host URLs.
- L20 _private typedef_ `using FSharedImpl = TSharedPtr<FImpl, ESPMode::ThreadSafe>;`
- L24 _public prototype_ `FOnDemandHostGroup();` — Creates a new empty host group.
- L26 _public prototype_ `~FOnDemandHostGroup();` — Destructor.
- L28 _public prototype_ `TConstArrayView<FAnsiString> Hosts() const;` — Returns the list of available host URLs.
- L30 _public prototype_ `FAnsiStringView Host(int32 Index) const;` — Get the URL at the specified index.
- L32 _public prototype_ `FAnsiStringView CycleHost(int32& InOutIndex) const;` — Get the next available host starting from the specified index.
- L34 _public prototype_ `void SetPrimaryHost(int32 Index);` — Set the primary host URL.
- L36 _public prototype_ `FAnsiStringView PrimaryHost() const;` — Get the primary host URL.
- L38 _public prototype_ `int32 PrimaryHostIndex() const;` — Get the primary host index.
- L40 _public prototype_ `bool IsEmpty() const;` — Returns whether the group is empty or not.
- L42 _public prototype_ `static TIoStatusOr<FOnDemandHostGroup> Create(FStringView Url);` — Create a new host group with the specified URL.
- L44 _public prototype_ `static TIoStatusOr<FOnDemandHostGroup> Create(TConstArrayView<FAnsiString> Urls);` — Create a new host group with the specified URLs.
- L46 _public prototype_ `static TIoStatusOr<FOnDemandHostGroup> Create(TConstArrayView<FString> Urls);` — Create a new host group with the specified URLs.
- L48 _public member_ `static FName DefaultName;` — Default host group name.
- L62 _private prototype_ `FOnDemandHostGroup(FSharedImpl&& Impl);`
- L64 _private member_ `FSharedImpl Impl;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace IoStore` (scope `UE`)
- L51 _function_ `friend inline bool operator==(const FOnDemandHostGroup& Lhs, const FOnDemandHostGroup& Rhs)` (scope `UE::IoStore`) — Returns whether two host group instances are the same or not.
- L56 _function_ `friend inline uint32 GetTypeHash(const FOnDemandHostGroup& HostGroup)` (scope `UE::IoStore`) — Returns the type hash of the host group.

### `Source/Runtime/Experimental/IoStore/OnDemandCore/Public/IO/OnDemandToc.h` (Public)


#### enum `UE::IoStore::EOnDemandTocVersion`  
`enum class EOnDemandTocVersion : uint32`  
_L23-41_
- L25 _public enumerator_ `Invalid = 0`
- L26 _public enumerator_ `Initial = 1`
- L27 _public enumerator_ `UTocHash = 2`
- L28 _public enumerator_ `BlockHash32 = 3`
- L29 _public enumerator_ `NoRawHash = 4`
- L30 _public enumerator_ `Meta = 5`
- L31 _public enumerator_ `ContainerId = 6`
- L32 _public enumerator_ `AdditionalFiles = 7`
- L33 _public enumerator_ `TagSets = 8`
- L34 _public enumerator_ `ContainerFlags = 9`
- L35 _public enumerator_ `TocFlags = 10`
- L36 _public enumerator_ `HostGroupName = 11`
- L37 _public enumerator_ `ContainerHeader = 12`
- L39 _public enumerator_ `LatestPlusOne`
- L40 _public enumerator_ `Latest = (LatestPlusOne - 1)`

#### enum `UE::IoStore::EOnDemandTocFlags`  
`enum class EOnDemandTocFlags : uint32`  
_L44-51_
- L46 _public enumerator_ `None = 0`
- L47 _public enumerator_ `InstallOnDemand = (1 << 0)`
- L48 _public enumerator_ `StreamOnDemand = (1 << 1)`
- L50 _public enumerator_ `Last = StreamOnDemand`

#### struct `UE::IoStore::FTocMeta`  
`struct FTocMeta`  
_L55-63_
- L57 _public member_ `int64 EpochTimestamp = 0;`
- L58 _public member_ `FString BuildVersion;`
- L59 _public member_ `FString TargetPlatform;`

#### struct `UE::IoStore::FOnDemandTocHeader`  
`struct FOnDemandTocHeader`  
_L68-82_
- L70 _public member_ `static constexpr uint64 ExpectedMagic = 0x6f6e64656d616e64;` — ondemand
- L72 _public member_ `uint64 Magic = ExpectedMagic;`
- L73 _public member_ `uint32 Version = uint32(EOnDemandTocVersion::Latest);`
- L74 _public member_ `uint32 Flags = uint32(EOnDemandTocFlags::None);`
- L75 _public member_ `uint32 BlockSize = 0;`
- L76 _public member_ `FString CompressionFormat;`
- L77 _public member_ `FString ChunksDirectory;`
- L78 _public member_ `FString HostGroupName;`

#### struct `UE::IoStore::FOnDemandTocEntry`  
`struct FOnDemandTocEntry`  
_L87-98_
- L89 _public member_ `FIoHash Hash = FIoHash::Zero;`
- L90 _public member_ `FIoChunkId ChunkId = FIoChunkId::InvalidChunkId;`
- L91 _public member_ `uint64 RawSize = 0;`
- L92 _public member_ `uint64 EncodedSize = 0;`
- L93 _public member_ `uint32 BlockOffset = ~uint32(0);`
- L94 _public member_ `uint32 BlockCount = 0;`

#### struct `UE::IoStore::FOnDemandTocContainerEntry`  
`struct FOnDemandTocContainerEntry`  
_L103-119_
- L105 _public member_ `FIoContainerId ContainerId;`
- L106 _public member_ `FString ContainerName;`
- L107 _public member_ `FString EncryptionKeyGuid;`
- L108 _public member_ `TArray<FOnDemandTocEntry> Entries;`
- L109 _public member_ `TArray<uint32> BlockSizes;`
- L110 _public member_ `TArray<FIoBlockHash> BlockHashes;`
- L111 _public member_ `TArray<uint8> Header;`
- L114 _public member_ `FIoHash UTocHash;` — Hash of the .utoc file (on disk) used to generate this data
- L115 _public member_ `uint8 ContainerFlags = 0;`

#### struct `UE::IoStore::FOnDemandTocSentinel`  
`struct FOnDemandTocSentinel`  
_L124-136_
- L127 _public member_ `static constexpr inline char SentinelImg[] = "-[`
- L128 _public member_ `static constexpr uint32 SentinelSize = 16;`
- L130 _public prototype_ `bool IsValid();`
- L135 _private member_ `uint8 Data[SentinelSize] = { 0 };`

#### struct `UE::IoStore::FOnDemandTocAdditionalFile`  
`struct FOnDemandTocAdditionalFile`  
_L138-146_
- L140 _public member_ `FIoHash Hash;`
- L141 _public member_ `FString Filename;`
- L142 _public member_ `uint64 FileSize = 0;`

#### struct `UE::IoStore::FOnDemandTocTagSetPackageList`  
`struct FOnDemandTocTagSetPackageList`  
_L151-158_
- L153 _public member_ `uint32 ContainerIndex = 0;`
- L154 _public member_ `TArray<uint32> PackageIndicies;`

#### struct `UE::IoStore::FOnDemandTocTagSet`  
`struct FOnDemandTocTagSet`  
_L163-172_
- L165 _public typedef_ `using FOnDemandTocTagSetPackageLists = TArray<FOnDemandTocTagSetPackageList>;`
- L167 _public member_ `FString Tag;`
- L168 _public member_ `FOnDemandTocTagSetPackageLists Packages;`

#### struct `UE::IoStore::FOnDemandToc`  
`struct FOnDemandToc`  
_L177-199_
- L179 _public prototype_ `FOnDemandToc() = default;`
- L180 _public prototype_ `~FOnDemandToc() = default;`
- L181 _public prototype_ `FOnDemandToc(FOnDemandToc&&) = default;`
- L182 _public prototype_ `FOnDemandToc& operator= (FOnDemandToc&&) = default;`
- L183 _public prototype_ `FOnDemandToc(const FOnDemandToc&) = delete;`
- L184 _public prototype_ `FOnDemandToc& operator= (const FOnDemandToc&) = delete;`
- L186 _public member_ `FOnDemandTocHeader Header;`
- L187 _public member_ `FTocMeta Meta;`
- L188 _public member_ `TArray<FOnDemandTocContainerEntry> Containers;`
- L189 _public member_ `TArray<FOnDemandTocAdditionalFile> AdditionalFiles;`
- L190 _public member_ `TArray<FOnDemandTocTagSet> TagSets;`
- L195 _public member_ `static const FGuid VersionGuid;`
- L196 _public member_ `static const FString FileExt;`
- L198 _public prototype_ `static TIoStatusOr<FOnDemandToc> LoadFromFile(const FString& FilePath, bool bValidate);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L14 _typedef_ `using FIoBlockHash = uint32;`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace IoStore` (scope `UE`)
- L52 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandTocFlags);` (scope `UE::IoStore`)
- L65 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FTocMeta& OutMeta);` (scope `UE::IoStore`)
- L84 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOnDemandTocHeader& OutTocHeader);` (scope `UE::IoStore`)
- L100 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOnDemandTocEntry& OutTocEntry);` (scope `UE::IoStore`)
- L121 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOnDemandTocContainerEntry& OutContainer);` (scope `UE::IoStore`)
- L148 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOnDemandTocAdditionalFile& AdditionalFile);` (scope `UE::IoStore`)
- L160 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOnDemandTocTagSetPackageList& TagSet);` (scope `UE::IoStore`)
- L174 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOnDemandTocTagSet& TagSet);` (scope `UE::IoStore`)
- L201 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOnDemandToc& OutToc);` (scope `UE::IoStore`)
- L206 _prototype_ `FStringBuilderBase& operator<<(FStringBuilderBase& Sb, UE::IoStore::EOnDemandTocFlags TocFlags);`
- L207 _prototype_ `FString LexToString(UE::IoStore::EOnDemandTocFlags TocFlags);`
