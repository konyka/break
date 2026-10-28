# Runtime / AssetRegistry

- module root: `Source/Runtime/AssetRegistry`
- headers: 30; symbols: 3390
- symbol kinds: class=57, delegate=45, enum=37, enumerator=162, externvar=10, function=394, macro=10, member=850, namespace=195, prototype=1491, struct=96, typedef=38, union=2, variable=3
- DynamicallyLoadedModuleNames: DirectoryWatcher, TargetPlatform
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, PakFile, Projects, TelemetryUtils, TraceLog
- PrivateIncludePathModuleNames: DirectoryWatcher, TargetPlatform

### `Source/Runtime/AssetRegistry/Internal/AssetRegistry/PackageReader.h` (Internal)


#### class `FPackageReader`  
`class FPackageReader : public FArchiveUObject`  
_L24-223_
- inherits: `FArchiveUObject`
- L27 _public prototype_ `FPackageReader();`
- L28 _public prototype_ `~FPackageReader();`
- L59 _public prototype_ `bool OpenPackageFile(FStringView PackageFilename, EOpenPackageResult* OutErrorCode = nullptr);` — Creates a loader for the filename
- L60 _public prototype_ `bool OpenPackageFile(FStringView LongPackageName, FStringView PackageFilename, EOpenPackageResult* OutErrorCode = nullptr);`
- L62 _public prototype_ `bool OpenPackageFile(FArchive* Loader, FStringView LongPackageName = FStringView(), EOpenPackageResult* OutErrorCode = nullptr);`
- L64 _public prototype_ `bool OpenPackageFile(TUniquePtr<FArchive> Loader, EOpenPackageResult* OutErrorCode = nullptr);`
- L65 _public prototype_ `bool OpenPackageFile(EOpenPackageResult& OutErrorCode);`
- L71 _public prototype_ `bool TryGetLongPackageName(FString& OutLongPackageName) const;` — Returns the LongPackageName from constructor if provided, otherwise calculates it from FPackageName::TryConvertFilenameToLongPackageName.
- L73 _public prototype_ `FString GetLongPackageName() const;` — Returns the LongPackageName as in TryGetPackageName; asserts if not found.
- L76 _public prototype_ `const FPackageFileSummary& GetPackageFileSummary() const;` — Returns the Summary that was ready by OpenPackageFile.
- L78 _public prototype_ `bool GetNames(TArray<FName>& OutNames);` — Reads Names if not already read and returns a copy.
- L80 _public prototype_ `bool GetImports(TArray<FObjectImport>& OutImportMap);` — Reads Imports if not already read and returns a copy.
- L82 _public prototype_ `bool GetExports(TArray<FObjectExport>& OutExportMap);` — Reads Exports if not already read and returns a copy.
- L84 _public prototype_ `bool GetDependsMap(TArray<TArray<FPackageIndex>>& OutDependsMap);` — Reads DependsMap if not already read and returns a copy.
- L86 _public prototype_ `bool GetSoftPackageReferenceList(TArray<FName>& OutSoftPackageReferenceList);` — Reads the list of SoftPackageDependencies if not already read and returns a copy.
- L88 _public prototype_ `bool GetSoftObjectPaths(TArray<FSoftObjectPath>& OutSoftObjectPaths);` — Reads the list of SoftObjectPaths if not already read and returns a copy.
- L90 _public prototype_ `bool ReadEditorOnlyFlags(TBitArray<>& OutImportUsedInGame, TBitArray<>& OutSoftPackageUsedInGame);` — Reads the EditorOnly flags for Imports and Exports and returns them. not cached, reparsed each call.
- L92 _public prototype_ `bool GetGatherableTextData(TArray<FGatherableTextData>& OutText);` — Reads the list of GatherableTextData if not already read and returns a copy.
- L94 _public prototype_ `bool GetThumbnails(TArray<FObjectFullNameAndThumbnail>& OutThumbnails);` — Reads the list of thumbnails if not already read and returns a copy.
- L97 _public prototype_ `bool ReadSearchableNames(TMap<FTopLevelAssetPath, TArray<FName>>& OutSearchableNames);` — Reads the searchable names and returns them. Not cached, reparsed each call.
- L99 _public prototype_ `bool ReadAssetRegistryData(TArray<FAssetData*>& AssetDataList, bool& bOutIsCookedWithoutAssetData);` — Reads information from the AR section and converts it to FAssetData. Not cached, reparsed each call.
- L106 _public prototype_ `bool ReadMetaData(FMetaData& OutMetaData);` — Reads information from the metadata section. Not cached, reparsed each call. Note that metadata redirects are not applied here, what's in the file is returned as-is.
- L110 _public prototype_ `bool ReadImportedClasses(TArray<FName>& OutClassNames);` — Reads Imports if not already read and parses the names of imported classes out of the Imports.
- L113 _public prototype_ `bool ReadImportTypeHierarchies(TMap<FSoftObjectPath, UE::Serialization::Private::FImportTypeHierarchy>& OutTypeHierarchies);` — Reads import type hierarchy information. Not cached, reparsed each call.
- L116 _public prototype_ `bool ReadCellExports(TArray<FCellExport>& OutExports);` — Reads VCell exports. Not cached, reparsed each call.
- L119 _public prototype_ `bool ReadCellImports(TArray<FCellImport>& OutImports);` — Reads VCell imports. Not cached, reparsed each call.
- L122 _public prototype_ `bool ReadWorldTileInfo(FWorldTileInfo& OutInfo);` — Reads FWorldTileInfo. Not cached, reparsed each call.
- L125 _public prototype_ `bool ReadPackageTrailer(UE::FPackageTrailer& OutTrailer);` — Reads the package trailer. Not cached, reparsed each call.
- L128 _public prototype_ `bool ReadDataResourceMap(TArray<TTuple<FSoftObjectPath, FObjectDataResource>>& OutDataResources);` — Reads the data resource map. Parses export indices in FObjectDataResource into FSoftObjectPath. Not cached, reparsed each call.
- L137 _public prototype_ `bool ReadLinkerObjects(TMap<FSoftObjectPath, FObjectData>& OutExports, TMap<FSoftObjectPath, FObjectData>& OutImports, TMap<FName, bool>& OutSoftPackageReferences);` — Reads LinkerTables if not already read, reads the Editor-Only flags (not cached, reparsed each call), And constructs a Map from ObjectPath -> ObjectData for each import, export, and SoftPackageReference. @param OutExports[SoftObjectPath].Value == FObjectData @param OutImports[SoftObjectPath].Value == FObjectData @param OutSoftPackageReferences[PackageName].Value == bUsedInGame
- L149 _public prototype_ `bool ReadDependencyData(FPackageDependencyData& OutDependencyData, EReadOptions Options);` — Reads information used by the dependency graph. Not cached, reparsed each call.
- L152 _public prototype_ `virtual void Serialize( void* V, int64 Length ) override;` — Farchive implementation to redirect requests to the Loader
- L153 _public prototype_ `virtual bool Precache( int64 PrecacheOffset, int64 PrecacheSize ) override;`
- L154 _public prototype_ `virtual void Seek( int64 InPos ) override;`
- L155 _public prototype_ `virtual int64 Tell() override;`
- L156 _public prototype_ `virtual int64 TotalSize() override;`
- L157 _public prototype_ `virtual FArchive& operator<<( FName& Name ) override;`
- L158 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& Name) override;`
- L159 _public function_ `virtual FString GetArchiveName() const override`
- L166 _private prototype_ `bool ReadAssetDataFromThumbnailCache(TArray<FAssetData*>& AssetDataList);` — Attempts to get object class name from the thumbnail cache for packages older than VER_UE4_ASSET_REGISTRY_TAGS
- L168 _private prototype_ `bool ReadAssetRegistryDataFromCookedPackage(TArray<FAssetData*>& AssetDataList, bool& bOutIsCookedWithoutAssetData);` — Creates asset data reconstructing all the required data from cooked package info
- L169 _private prototype_ `bool StartSerializeSection(int64 Offset);`
- L172 _private prototype_ `bool SerializeNameMap();` — Serializers for different package maps
- L173 _private prototype_ `bool SerializeImportMap();`
- L174 _private prototype_ `bool SerializeExportMap();`
- L175 _private prototype_ `bool SerializeDependsMap();`
- L176 _private prototype_ `bool SerializeImportedClasses(const TArray<FObjectImport>& InImportMap, TArray<FName>& OutClassNames);`
- L177 _private prototype_ `bool SerializeSoftPackageReferenceList();`
- L178 _private prototype_ `bool SerializeSoftObjectPathMap();`
- L179 _private prototype_ `bool SerializeGatherableTextDataMap();`
- L180 _private prototype_ `bool SerializeThumbnailMap();`
- L181 _private prototype_ `bool SerializeEditorOnlyFlags(TBitArray<>& OutImportUsedInGame, TBitArray<>& OutSoftPackageUsedInGame);`
- L182 _private prototype_ `bool SerializeSearchableNamesMap(FLinkerTables& OutSearchableNames);`
- L183 _private prototype_ `bool SerializeAssetRegistryDependencyData(TBitArray<>& OutImportUsedInGame, TBitArray<>& OutSoftPackageUsedInGame, TArray<TPair<FName, UE::AssetRegistry::EExtraDependencyFlags>>& OutExtraPackageDependencies);`
- L185 _private prototype_ `bool SerializePackageTrailer(FAssetPackageData& PackageData);`
- L191 _private prototype_ `TOptional<FSoftObjectPath> LinkerIndexToSoftObjectPath(FPackageIndex Index);` — Convert an index into the linker tables to a full object path. Requires ImportMap and ExportMap to have been serialized. Less efficient than ConvertLinkerTableToPaths.
- L193 _private prototype_ `void ApplyRelocationToImportMapAndSoftPackageReferenceList(FStringView LoadedPackageName, TArray<FName>& InOutSoftPackageReferenceList, TArray<TPair<FName, UE::AssetRegistry::EExtraDependencyFlags>>& InOutExtraPackageDependencies);`
- L196 _private prototype_ `static void ConvertLinkerTableToPaths(FName PackageName, TArray<FObjectExport>& ExportMap, TArray<FObjectImport>& ImportMap, TArray<FSoftObjectPath>& OutExports, TArray<FSoftObjectPath>& OutImports);`
- L200 _private prototype_ `uint32 GetPackageFlags() const;` — Returns flags the asset package was saved with
- L202 _private member_ `FString LongPackageName;`
- L203 _private member_ `FString PackageFilename;`
- L208 _private member_ `FArchive* Loader = nullptr;` — Loader is the interface used to read the bytes from the package's repository. All interpretation of the bytes is done by serializing into *this, which is also an FArchive.
- L209 _private member_ `FPackageFileSummary PackageFileSummary;`
- L210 _private member_ `TArray<FName> NameMap;`
- L211 _private member_ `TArray<FObjectImport> ImportMap;`
- L212 _private member_ `TArray<FObjectExport> ExportMap;`
- L213 _private member_ `TArray<TArray<FPackageIndex>> DependsMap;`
- L214 _private member_ `TArray<FName> SoftPackageReferenceList;`
- L215 _private member_ `TArray<FSoftObjectPath> SoftObjectPathMap;`
- L216 _private member_ `TArray<FGatherableTextData> GatherableTextDataMap;`
- L217 _private member_ `TArray<FObjectFullNameAndThumbnail> ThumbnailMap;`
- L218 _private member_ `int64 PackageFileSize = 0;`
- L219 _private member_ `int64 AssetRegistryDependencyDataOffset = INDEX_NONE;`
- L221 _private member_ `uint32 AssetRegistryVersion = static_cast<uint32>(~0);` — Defined as uint32 to avoid including AssetData.h in this header
- L222 _private member_ `bool bLoaderOwner = false;`

#### enum `FPackageReader::EOpenPackageResult`  
`enum class EOpenPackageResult : uint8`  
_L31-49_
- desc: Note: Keep up to date with LexToString implementation
- L34 _public enumerator_ `Success` — The package summary loaded successfully
- L36 _public enumerator_ `NoLoader` — The package reader was not given a valid archive to load from
- L38 _public enumerator_ `MalformedTag` — The package tag could not be found, the package is probably corrupted
- L40 _public enumerator_ `VersionTooOld` — The package is too old to be loaded
- L42 _public enumerator_ `VersionTooNew` — The package is from a newer version of the engine
- L44 _public enumerator_ `CustomVersionMissing` — The package contains an unknown custom version
- L46 _public enumerator_ `CustomVersionInvalid` — The package contains a custom version that failed it's validator
- L48 _public enumerator_ `Unversioned` — Package was unversioned but the process cannot load unversioned packages

#### struct `FPackageReader::FObjectData`  
`struct FObjectData`  
_L52-56_
- desc: Information provided by PackageReader about a parsed Import or Export.
- L54 _public member_ `FSoftObjectPath ClassPath;`
- L55 _public member_ `bool bUsedInGame = true;`

#### enum `FPackageReader::EReadOptions`  
`enum class EReadOptions`  
_L141-147_
- desc: Options for what to read in functions that read multiple things at once.
- L143 _public enumerator_ `None = 0`
- L144 _public enumerator_ `PackageData = 1 << 0`
- L145 _public enumerator_ `Dependencies = 1 << 1`
- L146 _public enumerator_ `Default = PackageData | Dependencies`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Serialization` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Serialization`)
- L224 _prototype_ `ENUM_CLASS_FLAGS(FPackageReader::EReadOptions);`
- L226 _prototype_ `const TCHAR* LexToString(FPackageReader::EOpenPackageResult Result);`

### `Source/Runtime/AssetRegistry/Internal/AssetRegistry/ParallelSort.h` (Internal)


#### struct `Algo::MergeSort::TMergeBuffer`  
`template <typename T> struct TMergeBuffer`  
_L43-51_
- L45 _public member_ `TRingBuffer<T> Buffer;`
- L46 _public member_ `int32 AllocatedSize = 0;`
- L47 _public member_ `int32 ConstructorSite = 0;`
- L48 _public member_ `int32 InputNum = 0;`
- L49 _public member_ `int32 BatchSize = 0;`
- L50 _public member_ `int32 Round = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Algo`
- L27 _prototype_ `template <typename RangeType, typename PredicateType> void ParallelSort(RangeType&& Range, PredicateType Predicate);` (scope `Algo`) — Sort a range of elements using a user-defined predicate class.  The sort is stable. The sort operation will be distributed to task threads using UE::Tasks::Launch, and the Predicate will be called on elements in the input range in parallel (possibly even the same element being read from multiple threads at the same time); the Predicate must be thread safe. bool Predicate(const T& A, const T& B) -> true if A < B. @param  Range      The range to sort. @param  Predicate  A binary predicate object used to specify if one element should precede another.
- L31 _prototype_ `template <typename RangeType, typename PredicateType> void ParallelSortForceSingleThreaded(RangeType&& Range, PredicateType Predicate);` (scope `Algo`) — Debug version of ParallelSort that shares implementation but is single threaded.
- L40 _namespace_ `namespace Algo`
- L40 _namespace_ `namespace MergeSort` (scope `Algo`)
- L53 _prototype_ `template <typename T, typename IndexType, typename PredicateType> void ParallelMergeSortPointerAndNum(T* First, IndexType Num, PredicateType Predicate);` (scope `Algo::MergeSort`)
- L55 _prototype_ `template <typename T, typename IndexType, typename PredicateType> void MergeSortPointerAndNum(T* First, IndexType Num, PredicateType Predicate);` (scope `Algo::MergeSort`)
- L57 _prototype_ `template <typename T, typename IndexType, typename PredicateType> void MergeSortRecursive(T* First, IndexType Num, PredicateType Predicate, TMergeBuffer<T>& MergeBuffer);` (scope `Algo::MergeSort`)
- L59 _prototype_ `template <typename T, typename IndexType, typename PredicateType> void Merge(T* First, IndexType Num, IndexType FloorMidIndex, PredicateType Predicate, TMergeBuffer<T>& MergeBuffer);` (scope `Algo::MergeSort`)
- L61 _prototype_ `template <typename T, typename IndexType, typename PredicateType> void SmallSort(T* First, IndexType Num, PredicateType Predicate);` (scope `Algo::MergeSort`)
- L71 _namespace_ `namespace Algo`
- L75 _function_ `template <typename RangeType, typename PredicateType> void ParallelSort(RangeType&& Range, PredicateType Predicate)` (scope `Algo`)
- L81 _function_ `template <typename RangeType> void ParallelSort(RangeType&& Range)` (scope `Algo`)
- L87 _function_ `template <typename RangeType, typename PredicateType> void ParallelSortForceSingleThreaded(RangeType&& Range, PredicateType Predicate)` (scope `Algo`)
- L93 _function_ `template <typename RangeType, typename PredicateType> void ParallelSortForceSingleThreaded(RangeType&& Range)` (scope `Algo`)
- L100 _namespace_ `namespace Algo`
- L100 _namespace_ `namespace MergeSort` (scope `Algo`)
- L104 _function_ `template <typename T, typename IndexType, typename PredicateType> void ParallelMergeSortPointerAndNum(T* First, IndexType Num, PredicateType Predicate)` (scope `Algo::MergeSort`)
- L154 _function_ `` (scope `Algo::MergeSort::ParallelMergeSortPointerAndNum`)
- L200 _function_ `` (scope `Algo::MergeSort::ParallelMergeSortPointerAndNum::__anon597a6f100402`)
- L222 _function_ `template <typename T, typename IndexType, typename PredicateType> void MergeSortPointerAndNum(T* First, IndexType Num, PredicateType Predicate)` (scope `Algo::MergeSort`)
- L236 _function_ `template <typename T, typename IndexType, typename PredicateType> void MergeSortRecursive(T* First, IndexType Num, PredicateType Predicate, TMergeBuffer<T>& MergeBuffer)` (scope `Algo::MergeSort`)
- L252 _function_ `template <typename T, typename IndexType, typename PredicateType> void Merge(T* First, IndexType Num, IndexType FloorMidIndex, PredicateType Predicate, TMergeBuffer<T>& InMergeBuffer)` (scope `Algo::MergeSort`)
- L343 _function_ `template <typename T, typename IndexType, typename PredicateType> void SmallSort(T* First, IndexType Num, PredicateType Predicate)` (scope `Algo::MergeSort`)

### `Source/Runtime/AssetRegistry/Internal/Verse/VersePathRegistry.h` (Internal)


#### enum `UE::VersePathRegistry::EAccess`  
`enum class UE_INTERNAL EAccess : uint8`  
_L29-39_
- L31 _public enumerator_ `EpicInternal = 0`
- L32 _public enumerator_ `Scoped`
- L33 _public enumerator_ `Private`
- L34 _public enumerator_ `Protected`
- L35 _public enumerator_ `Internal`
- L36 _public enumerator_ `Public`
- L38 _public enumerator_ `Count`

#### enum `UE::VersePathRegistry::EPathKind`  
`enum class UE_INTERNAL EPathKind : uint8`  
_L42-53_
- L44 _public enumerator_ `Unknown = 0`
- L45 _public enumerator_ `Module`
- L46 _public enumerator_ `Interface`
- L47 _public enumerator_ `Class`
- L48 _public enumerator_ `Function`
- L49 _public enumerator_ `Data`
- L50 _public enumerator_ `Alias`
- L52 _public enumerator_ `Count`

#### enum `UE::VersePathRegistry::EFlags`  
`enum class UE_INTERNAL EFlags : uint8`  
_L56-63_
- L58 _public enumerator_ `None = 0`
- L59 _public enumerator_ `Var = 1 << 0`
- L60 _public enumerator_ `Abstract = 1 << 1`
- L62 _public enumerator_ `Count = 3`

#### struct `UE::VersePathRegistry::FPathHandle`  
`struct UE_INTERNAL FPathHandle`  
_L68-92_
- desc: To consider: We can likely remove this / convert it into an interned FVersePath type
- L71 _public member_ `static constexpr uint32 GenerationMask = ~0u;` — Todo: Pack path type in the generation
- L72 _public member_ `static const FPathHandle Null;`
- L74 _public member_ `uint32 Index = 0;`
- L75 _public member_ `uint32 Generation = 0;`
- L77 _public function_ `[[nodiscard]] bool UEOpEquals(const FPathHandle& Rhs) const`
- L81 _public function_ `[[nodiscard]] bool UEOpLessThan(const FPathHandle& Rhs) const`
- L91 _public prototype_ `[[nodiscard]] bool IsNull() const;`
- L512 _function_ `inline bool FPathHandle::IsNull() const`

#### struct `UE::VersePathRegistry::FPathData`  
`struct UE_INTERNAL FPathData`  
_L97-121_
- desc: to consider: Partition this data into separate arrays based on Kind[Index] or embed the kind in the handle to consider: If we don't use multiple tables, we can union more of the data here but we will need to handle default constructability for cases like the TArrays to consider: Since handles <-> pathdata are immutable we can likely embed a decent bit of info into the handle and avoid PathDatas queries
- L99 _public member_ `FString Path;` — Move to interned handle
- L100 _public member_ `TArray<FPathHandle> ReadScopeAccessPaths;`
- L101 _public member_ `TArray<FPathHandle> WriteScopeAccessPaths;`
- L102 _public member_ `TArray<FPathHandle> ConstructorScopeAccessPaths;`
- L103 _public member_ `TArray<FPathHandle> Interfaces;`
- L104 _public member_ `FPathHandle Parent = FPathHandle::Null;`
- L110 _public member_ `EPathKind Kind = EPathKind::Unknown;`
- L111 _public member_ `EAccess ReadAccess = EAccess::Private;`
- L112 _public member_ `EAccess WriteAccess = EAccess::Private;`
- L113 _public member_ `EAccess ConstructorAccess = EAccess::Private;`
- L114 _public member_ `EFlags Flags = EFlags::None;`
- L116 _public prototype_ `[[nodiscard]] bool IsVar() const;`
- L117 _public prototype_ `[[nodiscard]] bool IsAbstract() const;`
- L120 _private member_ `uint32 Generation = 0;`
- L517 _function_ `inline bool FPathData::IsVar() const`
- L522 _function_ `inline bool FPathData::IsAbstract() const`

#### union `UE::VersePathRegistry::FPathData::(anonymous)`  
``  
_L106-109_

#### struct `UE::VersePathRegistry::FRegistryEvents`  
`struct UE_INTERNAL FRegistryEvents`  
_L123-140_
- L126 _public member_ `TMap<FPathHandle, FString> RemovedPaths;` — Maps the old handle removed from the registry to the path string the old handle was registered to
- L129 _public member_ `TArray<FPathHandle> AddedPaths;` — Holds all new handles added to the registry. The added path strings can be looked up in the registry using these handles.
- L136 _public member_ `TMap<FPathHandle, FPathHandle> UpdatedPaths;` — Maps the old handles removed from the registry that have been replaced by a new handle. The path strings for the updated paths can be looked up in the registry using the new handles (i.e. Pair.Value). This map contains the parent chain of paths to the path that was updated. e.g. When updating /Module/Class/Data: /Module, /Module/Class and /Module/Class/Data will be marked as updated. This map does not include paths whose FPathData FPathHandle members have changed.
- L138 _public prototype_ `[[nodiscard]] int32 Num() const;`
- L139 _public prototype_ `void Reset();`

#### class `UE::VersePathRegistry::FVersePathRegistry`  
`class UE_INTERNAL FVersePathRegistry`  
_L158-375_
- desc: Global registry holding type information for all compiled verse paths. The registry can be used to determine if a path can be read/written/constructed (if appropriate) when given a context path in which such an operation would be performed. e.g. CanRead("/Verse.org/ModuleA", "/Verse.org/ModuleB/InternalClass") can return false indicating that it would be invalid to access an internal class from another module (as long as ModuleB and InternalClass haven't provided scoped access to ModuleA -- something this registry would also track and account for). The Registry is almost entirely read-only as it is not expected to change often. A FRegistryBuilder can be used under special circumstances (i.e. verse compilation) to modify the global registry. Upon load of compiled verse packages, or the compilation of source verse packages, the registry will be populated with the path information for those packages.
- L160 _private prototype_ `FVersePathRegistry();`
- L163 _public prototype_ `FVersePathRegistry(const FVersePathRegistry&) = delete;`
- L164 _public prototype_ `FVersePathRegistry(FVersePathRegistry&&) = delete;`
- L165 _public prototype_ `FVersePathRegistry& operator=(const FVersePathRegistry&) = delete;`
- L166 _public prototype_ `FVersePathRegistry& operator=(FVersePathRegistry&&) = delete;`
- L169 _public prototype_ `static FVersePathRegistry& Get();` — Returns singleton instance to the global registry.
- L170 _public prototype_ `~FVersePathRegistry();`
- L176 _public prototype_ `[[nodiscard]] FOnVersePathRegistryUpdated& OnRegistryUpdated();` — Broadcasts the changes to the registry after each call to FVersePathRegistry::Append(). Listeners can safely read from the registry during a broadcast, but write operations will deadlock.
- L182 _public prototype_ `[[nodiscard]] bool CanConstruct(const FStringView ContextVersePath, const FStringView TargetVersePath) const;` — Determines if the type at the target path is constructable from within the context path. If either the context or target are not registered, false is returned.
- L188 _public prototype_ `[[nodiscard]] bool CanConstruct(const FPathHandle ContextHandle, const FPathHandle TargetHandle) const;` — Determines if the type at the target path is constructable from within the context path. If either the context or target handles are invalid, false is returned.
- L194 _public prototype_ `[[nodiscard]] bool CanRead(const FStringView ContextVersePath, const FStringView TargetVersePath) const;` — Determines if the target path is readable from the context path. If either the context or target are not registered, false is returned.
- L200 _public prototype_ `[[nodiscard]] bool CanRead(const FPathHandle ContextHandle, const FPathHandle TargetHandle) const;` — Determines if the target path is readable from the context path. If either the context or target handles are invalid, false is returned.
- L206 _public prototype_ `[[nodiscard]] bool CanWrite(const FStringView ContextVersePath, const FStringView TargetVersePath) const;` — Determines if the target path is writable from the context path. If either the context or target are not registered, false is returned.
- L212 _public prototype_ `[[nodiscard]] bool CanWrite(const FPathHandle ContextHandle, const FPathHandle TargetHandle) const;` — Determines if the target path is writable from the context path. If either the context or target handles are invalid, false is returned.
- L215 _public prototype_ `bool TryGetPathData(const FStringView VersePath, FPathData& OutPathData) const;` — Returns a copy of the registered FPathData for the provided path. If the path is not registered, false is returned.
- L218 _public prototype_ `bool TryGetPathData(const FPathHandle Handle, FPathData& OutPathData) const;` — Returns a copy of the registered FPathData for the provided handle. If the handle is not valid, false is returned.
- L221 _public prototype_ `[[nodiscard]] FPathHandle FindPath(const FStringView VersePath) const;` — Returns handle for the provided verse path. Otherwise FPathHandle::Null is returned.
- L224 _public prototype_ `[[nodiscard]] bool IsValidHandle(FPathHandle Handle) const;` — Returns whether the provided handle is valid for use in the registry.
- L227 _public prototype_ `[[nodiscard]] int32 Num() const;` — Returns the number of paths registered with the registry.
- L234 _public prototype_ `void Dump(const FStringView DumpPath = {}, bool bPrintChildren = true, TUniquePtr<FArchive> Ar = nullptr) const;` — Logs the string representation of the provided path in the registry. If no path is provided, all paths are dumped. Provided paths can optionally specify if child paths should also be dumped (default, true). An archive can be provided to write the results to the archive rather than to the console.
- L237 _public prototype_ `void Empty();` — Removes all registered paths
- L243 _public prototype_ `void ForEachPath(TFunctionRef<void(FPathHandle, const FPathData&)> Visitor) const;` — Invokes Visitor(FPathHandle, const FPathData&) for every path currently registered in the registry. The visitor is called under a read lock, so it must not perform any write operations on the registry.
- L260 _private prototype_ `void Append(FRegistryBuilder& Builder, FRegistryEvents* OutEvents = nullptr);` — Appends the paths from the provided builder into the registry. Paths in the builder that are in the registry already are overwritten, causing all paths under the overwritten path to be removed. The builder can append to existing nodes in the registry by referring to those paths via FPathHandle directly. Overwritten paths are marked as UpdatedPaths in the FRegistryEvents if provided. Similarly, any removed paths or newly added paths are recorded in the FRegistryEvents as well.
- L263 _private prototype_ `FPathHandle FindOrAddPath(const FStringView Path, bool* bAlreadyExisted = nullptr);` — Finds or adds a handle for the provided verse path.
- L270 _private prototype_ `template<typename CharType> void NormalizeVersePath(TStringBuilderBase<CharType>& Builder, const FStringView VersePath) const;` — Normalizes provided paths to ensure they meet the expectations of the registry's path to path handle mapping.
- L276 _private prototype_ `const bool TryGetContextAndTargetIndicesNoLock(const FStringView ContextVersePath, const FStringView TargetVersePath, uint32& OutContextIndex, uint32& OutTargetIndex) const;` — Converts verse paths to their FPathHandle index if the paths are valid. If either path is invalid, returns false, otherwise true.
- L288 _private prototype_ `[[nodiscard]] bool CanAccessNoLock(const uint32 ContextIndex, const uint32 TargetIndex, EAccessType AccessType) const;`
- L291 _private prototype_ `[[nodiscard]] bool IsModuleSameOrChildOfNoLock(const uint32 ContextIndex, const uint32 TargetIndex) const;` — Is the target module the same or a child of the context module (e.g. is target /A/B/C a child of context /A/B).
- L294 _private prototype_ `[[nodiscard]] uint32 GetModuleNoLock(const uint32 Index) const;` — Walk up the parent chain looking for the nearest module.
- L297 _private prototype_ `[[nodiscard]] uint32 GetScopeClassOrInterfaceNoLock(const uint32 Index) const;` — Walk up the parent chain looking for the nearest class or interface
- L303 _private prototype_ `[[nodiscard]] uint32 GetLogicalScopeNoLock(const uint32 Index) const;` — Return the index for the path that represents the logical scope for Index. If Index points to a path that is already a logical scope, Index is returned, otherwise the parent scope is returned.
- L306 _private prototype_ `[[nodiscard]] bool IsClassNoLock(uint32 ContextIndex, uint32 TargetIndex) const;` — Is Context the same class or a child class of Target.
- L309 _private prototype_ `[[nodiscard]] bool IsInterfaceNoLock(uint32 ContextIndex, uint32 TargetIndex) const;` — Is Context the same interface or a child interface of Target.
- L312 _private prototype_ `[[nodiscard]] bool IsInterfaceImplementorNoLock(uint32 ContextIndex, uint32 TargetIndex) const;` — Does path at ContextIndex implement the interface at TargetIndex.
- L318 _private prototype_ `[[nodiscard]] bool IsValidHandleNoLock(FPathHandle Handle) const;` — Returns whether the provided handle is valid for use in the registry.
- L321 _private prototype_ `void ShrinkNoLock();` — Shrinks the registry's internal storage to the smallest storage required for the elements being stored.
- L324 _private prototype_ `FPathHandle AllocateHandleNoLock();` — Allocates a FPathHandle. Thread-safety must be handled by the caller.
- L327 _private prototype_ `void FreeHandleNoLock(const uint32 Index);` — Frees an allocated FPathHandle for recycling. Thread-safety must be handled by the caller.
- L330 _private prototype_ `[[nodiscard]] FPathHandle FindPathNoLock(const FStringView VersePath) const;` — Returns the handle for the provided verse path. Thread-safety must be handled by the caller.
- L333 _private prototype_ `void FixupAddedPathInternalReferencesNoLock(const FRegistryBuilder& Builder, FPathHandle AddedHandle);` — When adding paths from a builder, any internal references via path string are set to the equivalent handle reference from the registry.
- L336 _private prototype_ `void FixupInternalReferencesNoLock(const uint32 IndexToFixup, const TMap<FPathHandle, FPathHandle>& UpdatedHandles);` — After manipulating the registry, call this method to correct internal FPathHandle references that may have become stale.
- L341 _private prototype_ `uint32 AddSubtreeNoLock(const FRegistryBuilder& Builder, const FSetElementId BuilderParentId, TMap<FString, TPair<FPathHandle, FPathHandle>>& PathToUpdatedHandles, TArray<FPathHandle>& AddedHandles);` — Adds the path in the builder at the BuilderRootIndex and all paths in the builder that have a parent chain that leads back to BuilderRootIndex to the registry. If provided, all new paths are added to the OutEvents.AddedPaths list, and paths that were removed knowing they will later be added are added as the pair key in the PathToUpdateHandles map. Returns the index of the newly added root of the subtree (which is not necessarily a registry root)
- L350 _private prototype_ `bool RemoveSubtreeNoLock(const uint32 Parent, TMap<FString, TPair<FPathHandle, FPathHandle>>& PathToUpdatedHandles, TMap<FPathHandle, FString>& RemovedHandlesToPath);` — Removes the path at index Parent and all paths that have a FPathData.Parent chain that leads back to Parent from the registry. If provided, removed nodes will be appended to the OutEvents.RemovedPaths list, and the old handle for nodes that we know will be removed and later replaced will be added as the pair key in the PathToUpdateHandles map. Returns true when the Parent was removed.
- L355 _private prototype_ `void CollectPackageRoots(const FRegistryBuilder& Builder, TSet<uint32>& OutPackageRoots);` — Collects all modules and all roots of non-module sub-trees (e.g. a class but not its data members).
- L359 _private member_ `mutable FTransactionallySafeRWLock Lock;` — Consider: we can partition subtrees to avoid contention if necessary
- L361 _private member_ `FOnVersePathRegistryUpdated OnRegistryUpdatedEvent;`
- L364 _private member_ `TMap<FString, uint32> PathToPathDataIndex;` — Todo: Replace with FString with proper interned FVersePath type
- L365 _private member_ `TArray<FPathData> PathDatas;`
- L366 _private member_ `TArray<uint32> FreeList;`
- L369 _private member_ `TSet<uint32> Roots;` — Hierarchy maintenance
- L370 _private member_ `TMap<uint32, TSet<uint32>> ParentToChildren;`
- L373 _private member_ `TMap<FString, int32> ModuleToRefCount;` — Used for package maintenance
- L374 _private member_ `TMap<FString, TSet<uint32>> PackageToRoots;`
- L527 _function_ `inline FOnVersePathRegistryUpdated& FVersePathRegistry::OnRegistryUpdated()`
- L532 _function_ `inline int32 FVersePathRegistry::Num() const`
- L538 _function_ `inline FPathHandle FVersePathRegistry::FindPathNoLock(const FStringView VersePath) const`
- L549 _function_ `inline void FVersePathRegistry::ShrinkNoLock()`
- L557 _function_ `inline FPathHandle FVersePathRegistry::AllocateHandleNoLock()`
- L573 _function_ `inline void FVersePathRegistry::FreeHandleNoLock(const uint32 Index)`
- L581 _function_ `inline bool FVersePathRegistry::IsValidHandleNoLock(FPathHandle Handle) const`
- L598 _function_ `inline bool FVersePathRegistry::IsValidHandle(FPathHandle Handle) const`

#### enum `UE::VersePathRegistry::FVersePathRegistry::EAccessType`  
`enum class EAccessType`  
_L282-287_
- L284 _public enumerator_ `Read` — Read Access. By default, all fields are immutable in Verse unless marked as IsVar
- L285 _public enumerator_ `Write` — Write access. Only applicable to Targets that are IsVar()
- L286 _public enumerator_ `Construct` — Type construction access. Only applicable to Targets that are EPathKind::Class

#### class `UE::VersePathRegistry::FRegistryBuilder`  
`class UE_INTERNAL FRegistryBuilder`  
_L380-507_
- desc: Builder allowing for a FVersePathRegistry to be constructed for later appending to the global registry.
- L400 _public prototype_ `FRegistryBuilder() = delete;`
- L401 _public prototype_ `explicit FRegistryBuilder(const FStringView InPackageName);`
- L404 _public prototype_ `bool RegisterPath(const FPathDesc& PathDesc);` — Registers a path description with the builder. Overwrites any previously registered description with the same path.
- L407 _public prototype_ `bool Find(const FStringView VersePath, FPathDesc& OutPathDesc) const;` — Returns true and populates OutPathDesc if the provided verse path has been registered.
- L410 _public prototype_ `[[nodiscard]] const FPathDesc& FindChecked(const FStringView VersePath) const;` — Returns the FPathDesc for the provided verse path. The path must exist.
- L413 _public prototype_ `[[nodiscard]] bool Contains(const FStringView VersePath) const;` — Returns true if the provided verse path has been registered with the builder. Returns false otherwise.
- L415 _public prototype_ `void Reserve(const int32 Num);`
- L418 _public prototype_ `[[nodiscard]] int32 Num() const;` — Returns the number of paths registered with the builder.
- L421 _public prototype_ `void Empty();` — Removes all registered paths from the builder
- L424 _public prototype_ `[[nodiscard]] const FString& GetPackageName() const;` — Returns the package name of the registry builder, indicating the source package used to generate the builder paths.
- L427 _public prototype_ `void SetPackageName(const FString& InPackageName);` — Sets the package name of the registry builder, indicating the source package used to generate the builder paths.
- L430 _private prototype_ `bool ValidatePath(const FPathDesc& PathDesc);`
- L431 _private prototype_ `void BuildHierarchy();`
- L502 _private member_ `FString PackageName;`
- L503 _private member_ `TSet<FPathDesc, FPathDescKeyFuncs> PathDescs;`
- L504 _private member_ `TSet<FSetElementId, FSetElementIdFuncs> Roots;`
- L505 _private member_ `TMap<FSetElementId, TSet<FSetElementId, FSetElementIdFuncs>, FDefaultSetAllocator, FSetElementIdMapFuncs> ParentToChildren;`
- L506 _private member_ `bool bRebuildHierarchy = false;`
- L604 _function_ `inline bool FRegistryBuilder::Find(const FStringView VersePath, FPathDesc& OutPathDesc) const`
- L615 _function_ `inline const FRegistryBuilder::FPathDesc& FRegistryBuilder::FindChecked(const FStringView VersePath) const`
- L622 _function_ `inline bool FRegistryBuilder::Contains(const FStringView VersePath) const`
- L627 _function_ `inline void FRegistryBuilder::Reserve(const int32 Num)`
- L632 _function_ `inline int32 FRegistryBuilder::Num() const`
- L637 _function_ `inline void FRegistryBuilder::Empty()`
- L645 _function_ `inline const FString& FRegistryBuilder::GetPackageName() const`
- L650 _function_ `inline void FRegistryBuilder::SetPackageName(const FString& InPackageName)`

#### struct `UE::VersePathRegistry::FRegistryBuilder::FPathDesc`  
`struct FPathDesc`  
_L383-398_
- L385 _public member_ `FString Path;`
- L386 _public member_ `FString Parent;`
- L387 _public member_ `EPathKind Kind = EPathKind::Unknown;`
- L388 _public member_ `EAccess ReadAccess = EAccess::Private;`
- L389 _public member_ `EAccess WriteAccess = EAccess::Private;`
- L390 _public member_ `EAccess ConstructorAccess = EAccess::Private;`
- L391 _public member_ `TArray<FString> ReadScopeAccessPaths;`
- L392 _public member_ `TArray<FString> WriteScopeAccessPaths;`
- L393 _public member_ `TArray<FString> ConstructorScopeAccessPaths;`
- L394 _public member_ `FString ClassSuper;`
- L395 _public member_ `FString TypeAliasTarget;`
- L396 _public member_ `TArray<FString> Interfaces;`
- L397 _public member_ `EFlags Flags;`

#### struct `UE::VersePathRegistry::FRegistryBuilder::FPathDescKeyFuncs`  
`struct FPathDescKeyFuncs : BaseKeyFuncs<FPathDesc, FString, false>`  
_L438-464_
- inherits: `BaseKeyFuncs<FPathDesc,FString,false>`
- L440 _public function_ `static const FString& GetSetKey(const FPathDesc& Element)`
- L445 _public function_ `static bool Matches(const FString& A, const FString& B)`
- L450 _public function_ `static bool Matches(const FString& A, const FStringView B)`
- L455 _public function_ `static uint32 GetKeyHash(const FString& Key)`
- L460 _public function_ `static uint32 GetKeyHash(const FStringView Key)`

#### struct `UE::VersePathRegistry::FRegistryBuilder::FSetElementIdFuncs`  
`struct FSetElementIdFuncs : BaseKeyFuncs<FSetElementId, FSetElementId, false>`  
_L466-482_
- inherits: `BaseKeyFuncs<FSetElementId,FSetElementId,false>`
- L468 _public function_ `static FSetElementId GetSetKey(FSetElementId Element)`
- L473 _public function_ `static bool Matches(FSetElementId A, FSetElementId B)`
- L478 _public function_ `static uint32 GetKeyHash(FSetElementId Key)`

#### struct `UE::VersePathRegistry::FRegistryBuilder::FSetElementIdMapFuncs`  
`struct FSetElementIdMapFuncs : BaseKeyFuncs<TPair<FSetElementId, TSet<FSetElementId, FSetElementIdFuncs>>, FSetElementId, false>`  
_L484-500_
- inherits: `BaseKeyFuncs<TPair<FSetElementId,TSet<FSetElementId,FSetElementIdFuncs>>,FSetElementId,false>`
- L486 _public function_ `static FSetElementId GetSetKey(TPair<FSetElementId, TSet<FSetElementId, FSetElementIdFuncs>> Element)`
- L491 _public function_ `static bool Matches(FSetElementId A, FSetElementId B)`
- L496 _public function_ `static uint32 GetKeyHash(FSetElementId Key)`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVersePathRegistry, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVersePathRegistry, Log, All);`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace VersePathRegistry` (scope `UE`)
- L40 _prototype_ `const TCHAR* LexToString(EAccess Access);` (scope `UE::VersePathRegistry`)
- L54 _prototype_ `const TCHAR* LexToString(EPathKind Kind);` (scope `UE::VersePathRegistry`)
- L64 _prototype_ `ENUM_CLASS_FLAGS(EFlags);` (scope `UE::VersePathRegistry`)
- L65 _prototype_ `const TCHAR* LexToString(EFlags Flags);` (scope `UE::VersePathRegistry`)
- L86 _function_ `[[nodiscard]] friend uint32 GetTypeHash(FPathHandle Handle)` (scope `UE::VersePathRegistry`)
- L107 _member_ `FPathHandle ClassSuper = FPathHandle::Null;` (scope `UE::VersePathRegistry::FPathData::__anonb5dae8f2010a`)
- L108 _member_ `FPathHandle TypeAliasTarget;` (scope `UE::VersePathRegistry::FPathData::__anonb5dae8f2010a`)
- L141 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVersePathRegistryUpdated, const FRegistryEvents&);`
- L141 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVersePathRegistryUpdated, const FRegistryEvents&);` (scope `UE::VersePathRegistry`)

### `Source/Runtime/AssetRegistry/Private/ARLoader.h` (Private)


#### struct `UE::AssetRegistry::Impl::FAssetProviderInitData`  
`struct FAssetProviderInitData`  
_L47-59_
- desc: Data about the premade AssetRegistryState passed through from its load into LoadPremadeAssetRegistry and the ActiveMountsLoader
- L49 _public prototype_ `FAssetProviderInitData() = default;`
- L50 _public prototype_ `FAssetProviderInitData(const FAssetProviderInitData& Other) = delete;`
- L51 _public prototype_ `FAssetProviderInitData(FAssetProviderInitData&& Other);`
- L52 _public prototype_ `FAssetProviderInitData& operator=(const FAssetProviderInitData& Other) = delete;`
- L53 _public prototype_ `FAssetProviderInitData& operator=(FAssetProviderInitData&& Other);`
- L54 _public prototype_ `void Reset();`
- L56 _public member_ `FAssetRegistryState ARState;`
- L57 _public member_ `FString StateFilePath;`
- L58 _public member_ `FixedTagPrivate::FWeakStorePtr StoreUsedByState;`

#### enum `UE::AssetRegistry::Premade::ELoadResult`  
`enum class ELoadResult : uint8`  
_L66-74_
- L68 _public enumerator_ `Succeeded = 0`
- L69 _public enumerator_ `NotFound = 1`
- L70 _public enumerator_ `FailedToLoad = 2`
- L71 _public enumerator_ `Inactive = 3`
- L72 _public enumerator_ `AlreadyConsumed = 4`
- L73 _public enumerator_ `UninitializedMemberLoadResult = 5`

#### class `UE::AssetRegistry::Premade::FPreloader`  
`class FPreloader`  
_L77-165_
- desc: Loads AssetRegistry.bin during engine startup, using an async preload task if available and sync otherwise.
- L86 _public typedef_ `using FConsumeFunction = TFunction<void(ELoadResult LoadResult, UE::AssetRegistry::Impl::FAssetProviderInitData&& StateInitData)>;`
- L89 _public prototype_ `FPreloader();`
- L90 _public prototype_ `~FPreloader();`
- L98 _public prototype_ `bool Consume(FConsumeFunction&& ConsumeFunction);` — Block on any pending async load, load if synchronous, and call ConsumeFunction with the results before returning. If Consume has been called previously, the current ConsumeFunction is ignored and this call returns false. @return Whether the load succeeded (this information is also passed to the ConsumeFunction).
- L109 _public prototype_ `EConsumeResult ConsumeOrDefer(FConsumeFunction&& ConsumeSynchronous, FConsumeFunction&& ConsumeAsynchronous);` — If a load is pending, store ConsumeAsynchronous for later calling and return EConsumeResult::Deferred. If load is complete, or failed, or needs to run synchronously, load if necessary and call ConsumeSynchronous with results before returning. Note if this function returns EConsumeResult::Deferred, the ConsumeAsynchronous will be called from another thread, possibly before this call returns. If Consume has been called previously, this call is ignored and returns EConsumeResult::Failed. @return Whether the load succeeded (this information is also passed to the ConsumeFunction).
- L124 _private prototype_ `bool TrySetPath();`
- L125 _private prototype_ `bool TrySetPath(const IPakFile& Pak);`
- L126 _private prototype_ `ELoadResult TryLoad();`
- L127 _private prototype_ `void DelayedInitialize();`
- L128 _private prototype_ `void KickPreloadOrDelayIfConfigNotReady();`
- L129 _private prototype_ `void KickPreload();`
- L130 _private prototype_ `void TryLoadAsync();`
- L131 _private prototype_ `EConsumeResult ConsumeInternal(FConsumeFunction&& ConsumeSynchronous, FConsumeFunction&& ConsumeAsynchronous);`
- L133 _private prototype_ `void Shutdown(bool bFromGlobalDestructor = false);` — Called when the Preloader has no further work to do, to free resources early since destruction occurs at end of process.
- L136 _private member_ `TOptional<FDelayedAutoRegisterHelper> OnTaskGraphReady;` — simple way to trigger a callback at a specific time that TaskGraph is usable.
- L139 _private member_ `FCriticalSection StateLock;` — Lock that guards members on this (see notes on each member).
- L141 _private member_ `FEvent* PreloadReady = nullptr;` — Trigger for blocking Consume to wait upon TryLoadAsync. This Trigger is only allocated when in the states NotFound, Loaded, Loading.
- L144 _private member_ `FString ARPath;` — Path discovered for the AssetRegistry; Read/Write only within the Lock.
- L153 _private member_ `UE::AssetRegistry::Impl::FAssetProviderInitData Payload;` — The set of (ARState, AssetRegistryLoadResults, and other metadata) that was loaded from disk. Owned exclusively by either the first Consume or by TryAsyncLoad. If LoadState is never set to Loading, this state is read/written only by the first thread to call Consume. If LoadState is set to Loading (which happens before threading starts), the thread running TryAsyncLoad owns this payload until it triggers PreloadReady, after which ownership returns to the first thread to call Consume.
- L155 _private member_ `FDelegateHandle PakMountedDelegate;`
- L158 _private member_ `FConsumeFunction ConsumeCallback;` — Callback from ConsumeOrDefer that is set so TryLoadAsync can trigger the Consume when it completes.Read / Write only within the lock.
- L161 _private member_ `EState LoadState = EState::WillNeverPreload;` — State machine state. Read/Write only within the lock (or before threading starts).
- L164 _private member_ `ELoadResult LoadResult = ELoadResult::UninitializedMemberLoadResult;` — Result of TryLoad.Thread ownership rules are the same as the rules for Payload.

#### enum `UE::AssetRegistry::Premade::FPreloader::EConsumeResult`  
`enum class EConsumeResult`  
_L80-85_
- L82 _public enumerator_ `Succeeded`
- L83 _public enumerator_ `Failed`
- L84 _public enumerator_ `Deferred`

#### enum `UE::AssetRegistry::Premade::FPreloader::EState`  
`enum class EState : uint8`  
_L112-121_
- L114 _public enumerator_ `WillNeverPreload`
- L115 _public enumerator_ `LoadSynchronous`
- L116 _public enumerator_ `NotFound`
- L117 _public enumerator_ `ConfigNotReady`
- L118 _public enumerator_ `Loading`
- L119 _public enumerator_ `Loaded`
- L120 _public enumerator_ `Consumed`

#### struct `UE::AssetRegistry::Premade::FAsyncConsumer`  
`struct FAsyncConsumer`  
_L179-203_
- desc: A struct to consume a Premade asset registry on an async thread. It supports a cheap Wait() call so that it can be Waited on by frequent AssetRegistry interface calls for the rest of the process.
- L181 _public prototype_ `~FAsyncConsumer();`
- L183 _public prototype_ `void PrepareForConsume();` — Sets the Consumer into need-to-wait mode; Wait will block until Consume is called.
- L189 _public prototype_ `void Wait(FInterfaceWriteScopeLock& ScopeLock);` — Does not return until after the Premade AssetRegistryState has been added into the target AssetRegistry, or it has been decided not to be used. For performance reasons, this must be called within the WriteScopeLock, and the caller must handle the possibility that it leaves and reenters the lock.
- L191 _public prototype_ `void Consume(UAssetRegistryImpl& UARI, UE::AssetRegistry::Impl::FEventContext& EventContext, UE::AssetRegistry::Impl::FActiveMountEvents& ActiveMountEventContext, UE::AssetRegistry::FInterfaceWriteScopeLock& ProofOfWriteLock, ELoadResult LoadResult, UE::AssetRegistry::Impl::FAssetProviderInitData&& StateInitData);` — Callback from the async thread to consume the Premade ARState
- L200 _private member_ `int32 ReferenceCount = 0;` — ReferenceCounter for the Consumed event. Also used to decide whether Waiting is necessary. Read/Write only inside the lock.
- L202 _private member_ `FEvent* Consumed = nullptr;` — Event used to Wait for Consume. Allocated/deallocated within the lock. Can be waited on outside the lock if RefCount is held.

#### enum `UE::AssetRegistry::Impl::EInitialProviderRegisterReason`  
`enum class EInitialProviderRegisterReason`  
_L217-225_
- desc: Which event triggered our need to register the premade AssetRegistry with the ActiveMountsLoading.
- L220 _public enumerator_ `ActiveMountsInitialize` — Expected case, OnActiveMountsInitialize was called.
- L222 _public enumerator_ `AppendState` — Allowed case, AppendState was called before OnActiveMountsInitialize.
- L224 _public enumerator_ `EarlierState` — Error case, some other data was added to global AssetRegistry before the premade.

#### class `UE::AssetRegistry::Impl::FActiveMountEvents`  
`class FActiveMountEvents`  
_L231-252_
- desc: Holds callbacks and events triggered during ActiveMountsLoading functions that need to be broadcast outside of the AssetRegistry's locks.
- L238 _public prototype_ `void AddCompletion(TFunction<void(bool bCanceled)> InOnComplete, bool bInCanceled);` — Add a completion callback from ActiveMountsLoadAsync or ActiveMountsUnloadAsync, and the value of its bCanceled parameter.
- L240 _public prototype_ `void AddIdle(TFunction<void()> InOnIdle);` — Add an OnIdle callback from ActiveMountsReportWhenIdle.
- L242 _public prototype_ `void Broadcast();` — Send all of the added events. Must be called outside of the AssetRegistry's locks.
- L250 _private member_ `TArray<FCompletionData> CompletionEvents;`
- L251 _private member_ `TArray<TFunction<void()>> IdleCallbacks;`

#### struct `UE::AssetRegistry::Impl::FActiveMountEvents::FCompletionData`  
`struct FCompletionData`  
_L245-249_
- L247 _public member_ `TFunction<void(bool bCanceled)> OnComplete;`
- L248 _public member_ `bool bCanceled = false;`

#### class `UE::AssetRegistry::Impl::FActiveMountsLoaderWrapper`  
`class FActiveMountsLoaderWrapper`  
_L269-403_
- desc: The interface into the ActiveMountsLoader used by the rest of the AssetRegistry. The ActiveMountsLoader stores filepaths for AssetRegistry.bin files that provide assets to the AssetRegistry, and it manages a state machine to unload and reload the AssetDatas for mountpoints (such as plugin Content directories) when those mountpoints are loaded and unloaded. @see the comment on ActiveMountsLoading in IAssetRegistry.h. The ActiveMountsLoader has some minor performance costs and so should only be enabled in configurations and projects that need the memory savings and that can behave correctly when AssetDatas are unloaded for inactive plugins. This interface object exists in all configurations, but it only creates the full ActiveMountsLoader when enabled. When not enabled it implements only the side effects that are required by the rest of the AssetRegistry, such as calling AppendState for filenames passed to TryRegisterAndAppendState. This wrapper also manages the separate critical section(s) used by the ActiveMountsLoader; ActiveMountsLoader functions are always called inside of its lock.
- L276 _public prototype_ `void InitializeConfig();` — Called during AssetRegistry initialization. Reads configuration settings such as enable flags and creates the full FActiveMountsLoader if enabled.
- L281 _public prototype_ `void Shutdown(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext);` — Called during AssetRegistry shutdown. Signals any active ActiveMountsLoader threads to terminate, waits for them, and shuts down the ActiveMountsLoader.
- L283 _public prototype_ `bool IsEnabled();` — Report whether the full ActiveMountsLoader is currently enabled.
- L286 _public prototype_ `void LoadAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints, TFunction<void(bool bCanceled)>&& OnComplete);` — @see IAssetRegistry::ActiveMountsLoadAsync. Calls OnComplete(bCanceled=true) immediately if disabled.
- L290 _public prototype_ `void ReloadAllAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TFunction<void(bool bCanceled)>&& OnComplete);` — @see IAssetRegistry::ActiveMountsReloadAllAsync. Calls OnComplete(bCanceled=true) immediately if disabled.
- L293 _public prototype_ `void UnloadAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints, TFunction<void(bool bCanceled)>&& OnComplete);` — @see IAssetRegistry::ActiveMountsUnloadAsync. Calls OnComplete(bCanceled=true) immediately if disabled.
- L297 _public prototype_ `void UnloadAllUnmountedAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TFunction<void(bool bCanceled)>&& OnComplete);` — @see IAssetRegistry::ActiveMountsUnloadAllUnmountedAsync. Calls OnComplete(bCanceled=true) immediately if disabled.
- L300 _public prototype_ `bool IsLoaded(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, const TRefCountPtr<UE::PackageName::IMountPoint>& MountPoint);` — @see IAssetRegistry::ActiveMountsIsLoaded.
- L303 _public prototype_ `bool IsInProgress(UAssetRegistryImpl& UARI);` — @see IAssetRegistry::ActiveMountsIsInProgress.
- L305 _public prototype_ `void ReportWhenIdle(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TFunction<void()> OnIdle);` — @see IAssetRegistry::ActiveMountsReportWhenIdle.
- L308 _public prototype_ `void OnActiveMountsInitialize(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FInterfaceWriteScopeLock& ProofOfWriteLock);` — @see IAssetRegistry::ActiveMountsInitialize.
- L311 _public prototype_ `bool TryRegisterAssetProviderAndAppendStateOutsideARLock(UAssetRegistryImpl& UARI, FEventContext& AREventContext, FActiveMountEvents& EventContext, FStringView InStateFilePath);` — @see IAssetRegistry::ActiveMountsRegisterAndLoadFilePathSynchronous.
- L318 _public prototype_ `bool TryLoadStateAndRegisterAssetProvider(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FInterfaceWriteScopeLock& ProofOfWriteLock, FPakPlatformFile* PakPlatformFile, FStringView InStateFilePath, FAssetRegistryState& OutLoadedState);` — Called by internal AssetRegistry code to load and register the AssetRegistry files for built-in plugins, called immediately after the initial premade AssetRegistry is loaded. If successful, this function also triggers the immediate registration of the premade AssetRegistry.
- L326 _public prototype_ `void UnregisterAssetProvider(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FStringView InStateFilePath);` — Deactivate a file as an AssetProvider, clearing the data about it from memory. AssetDatas in MountPoints provided by the AssetProvider can no longer be unloaded or reloaded (until the AssetProvider is registered again). Invalid to call on the premade initial provider.
- L334 _public prototype_ `void InitialProviderReport(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FAssetProviderInitData& StateInitData);` — Called when the premade AssetRegistryState has finished loading and is added to the AssetRegistry. We do not yet try to identify the MountPoints used by the AssetDatas within the AssetRegistryState, because identifying them might rely on the registration of MountPoints with FPackageName and some projects might not be immediately ready for that. This function just stores the filename and marks that the AssetProvider exists.
- L340 _public prototype_ `void InitialProviderOnReadyForRegister(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, EInitialProviderRegisterReason Reason);` — Called when ActiveMountsInitialize or some other event signals that we are ready to identify MountPoints within the initial provider. Just sets a flag, takes no other action.
- L346 _public prototype_ `void InitialProviderConditionalRegister(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FAssetRegistryState& InitialProviderState);` — Checks whether InitialProviderReport and InitialProviderOnReadyForRegister have both been called and if so parses the initial provider's AssetRegistry state to identify its MountPoints.
- L353 _public prototype_ `void OnMountPointsMounted(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints);` — Called when FPackageName reports one or more OnMountPointMounted; triggers the automatic async batched reloading of AssetDatas for the MountPoint, if autounload is enabled.
- L359 _public prototype_ `void OnMountPointsDismounted(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FInterfaceWriteScopeLock& ProofOfWriteLock, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints);` — Called when FPackageName reports one or more OnMountPointDismounted; triggers the automatic async batched unloading of AssetDatas for the MountPoint, if autounload is enabled.
- L368 _public prototype_ `static bool IsEnabledByConfig();` — Report whether the configuration settings specify that the full ActiveMountsLoader should be enabled. Should only be used during InitializeConfig or by functions that need to execute before it, such as UE::AssetRegistry::Premade::FPreloader.
- L375 _private prototype_ `FActiveMountsLoader* LockIfEnabled();` — Called by all public functions, even when the full ActiveMountsLoader is enabled. When disabled, operates as cheaply as possible, does not lock, and returns nullptr. When enabled, locks and returns a pointer to this->Inner.
- L377 _private prototype_ `void Lock();` — Lock ActiveMountsLock, the lock that must be entered around any full ActiveMountsLoader functions.
- L379 _private prototype_ `void Unlock();` — Unlock ActiveMountsLock.
- L384 _private prototype_ `TSharedPtr<UE::FRecursiveMutex> GetRegistrationLock();` — Return the lock that must be entered around AssetDataProvider register/deregister functions. Returns nullptr if full ActiveMountsLoader is not enabled.
- L392 _private member_ `UE::FRecursiveMutex ActiveMountsLock;` — Lock that guards the ActiveMountsLoader's data, separate from the AssetRegistry's data so that we do not block AssetRegistry queries when doing some long operations inside the lock. This lock is allowed to be held at the same time as the AssetRegistry's interface lock (avoid when possible). When both are held, the AssetRegistry's interface lock must be entered first.
- L398 _private member_ `std::atomic<FActiveMountsLoader*> Inner{ nullptr };` — Null if ActiveMounts are disabled. This is an atomic only because it can be set to null during Shutdown and the reader might be checking it for null outside the lock when that happens. The reader must always enter the lock and check for null again before dereferencing it.

#### Free symbols / members of external scopes

- L25 _macro_ `#define ASSETREGISTRY_FORCE_PREMADE_REGISTRY_IN_EDITOR 0`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L33 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L34 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L35 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L36 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L37 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L40 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L63 _namespace_ `namespace Premade` (scope `UE::AssetRegistry`)
- L168 _prototype_ `extern bool IsEnabled();` (scope `UE::AssetRegistry::Premade`) — Returns whether the given executable configuration supports AssetRegistry Preloading. Called before Main.
- L169 _prototype_ `extern bool CanLoadAsync();` (scope `UE::AssetRegistry::Premade`)
- L171 _prototype_ `FAssetRegistryLoadOptions GetLoadOptions();` (scope `UE::AssetRegistry::Premade`) — Returns the LoadOptions used to load the premade AssetRegistry.bin.
- L173 _externvar_ `extern FPreloader GPreloader;` (scope `UE::AssetRegistry::Premade`)
- L207 _namespace_ `namespace UE`
- L207 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L207 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L214 _prototype_ `TUniquePtr<FArchive> OpenReadStateFileArchive(FStringView FilePath, uint32 BufferSize=0);` (scope `UE::AssetRegistry::Impl`) — Open the given AssetRegistry.bin file using the performant archive we use for loading it. If BufferSize == 0 or is greater than filesize, reads the entire file into an in-memory archive.

### `Source/Runtime/AssetRegistry/Private/ARTypes.h` (Private)


#### class `UE::AssetRegistry::Private::FRWLockWithPriority`  
`class FRWLockWithPriority`  
_L31-80_
- desc: Custom lock class that can prioritize waiters upon request. This is used to allow threads with critical requests to request that the gatherer thread pause its work and allow the higher pri threads to jump in. Note that for this to work correctly it must be used with the associated TPriorityScopeLock types (TScopeLockWithPriority and FRWScopeLockWithPriority)
- L34 _public function_ `FORCEINLINE void WriteLock()`
- L39 _public function_ `FORCEINLINE bool TryWriteLock()`
- L44 _public function_ `FORCEINLINE void WriteUnlock()`
- L49 _public function_ `FORCEINLINE void ReadLock()`
- L54 _public function_ `FORCEINLINE bool TryReadLock()`
- L59 _public function_ `FORCEINLINE void ReadUnlock()`
- L64 _public function_ `bool HasWaiters() const`
- L78 _private member_ `FTransactionallySafeRWLock Mutex;`
- L79 _private member_ `std::atomic<int32> HighPriorityWaitersCount { 0 };`

#### class `UE::AssetRegistry::Private::TTracingReadScopeLock`  
`template<typename MutexType> class TTracingReadScopeLock`  
_L84-116_
- desc: Custom lock scopes to allow measuring lock contention
- L89 _public function_ `UE_NODISCARD_CTOR TTracingReadScopeLock(MutexType& InMutex) : Mutex(&InMutex)`
- L100 _public function_ `~TTracingReadScopeLock()`
- L105 _public function_ `void ReadUnlock()`
- L115 _private member_ `MutexType* Mutex;`

#### class `UE::AssetRegistry::Private::TTracingWriteScopeLock`  
`template<typename MutexType> class TTracingWriteScopeLock`  
_L119-151_
- L124 _public function_ `UE_NODISCARD_CTOR TTracingWriteScopeLock(MutexType& InMutex) : Mutex(&InMutex)`
- L135 _public function_ `~TTracingWriteScopeLock()`
- L140 _public function_ `void WriteUnlock()`
- L150 _private member_ `MutexType* Mutex;`

#### enum `UE::AssetRegistry::Private::ELockPriority`  
`enum ELockPriority : uint8`  
_L153-157_
- L155 _public enumerator_ `PriorityLow`
- L156 _public enumerator_ `PriorityHigh`

#### class `UE::AssetRegistry::FScopedHighPriorityWaitTracker`  
`class FScopedHighPriorityWaitTracker`  
_L165-198_
- desc: Tracks high-priority waiters on a lock, in an thread- and transactionally-safe manner.
- L168 _public function_ `FScopedHighPriorityWaitTracker(std::atomic<int32>* InCounter, Private::ELockPriority InPriority) : Counter((InPriority == Private::PriorityHigh) ? InCounter : nullptr)`
- L184 _public function_ `~FScopedHighPriorityWaitTracker()`
- L197 _private member_ `std::atomic<int32>* Counter = nullptr;`

#### class `UE::AssetRegistry::TRWScopeLockWithPriority`  
`template <typename TScopeLockType> class TRWScopeLockWithPriority`  
_L207-222_
- desc: Keeps an FRWLock read-locked while this scope lives. This is almost a clone of the existing FReadScopeLock and similar types however this adds an extra flag to help the background processing thread know when a higher priority thread would like to gain access to the protected data
- L210 _public function_ `UE_NODISCARD_CTOR explicit TRWScopeLockWithPriority(Private::FRWLockWithPriority& InLock, Private::ELockPriority InPriority = Private::PriorityHigh) : Lock(InLock) , Priority(InPriority)`
- L219 _public member_ `TOptional<TScopeLockType> GuardWrapper;`
- L220 _public member_ `UE::AssetRegistry::Private::FRWLockWithPriority& Lock;`
- L221 _public member_ `UE::AssetRegistry::Private::ELockPriority Priority;`

#### class `UE::AssetRegistry::FRWScopeLockWithPriority`  
`class FRWScopeLockWithPriority`  
_L224-258_
- L227 _public function_ `UE_NODISCARD_CTOR explicit FRWScopeLockWithPriority(Private::FRWLockWithPriority& InLockObject, FRWScopeLockType InLockType, Private::ELockPriority InPriority = Private::PriorityHigh) : Lock(InLockObject) , Priority(InPriority) , LockType(InLockType)`
- L241 _public function_ `void ReleaseReadOnlyLockAndAcquireWriteLock_USE_WITH_CAUTION()` — NOTE: As the name suggests, this function should be used with caution. It releases the read lock _before_ acquiring a new write lock. This is not an atomic operation and the caller should not treat it as such. E.g. Pointers read from protected data structures prior to this call may be invalid after the function is called.
- L254 _public member_ `Private::FRWLockWithPriority& Lock;`
- L255 _public member_ `TOptional<TRWScopeLock<Private::FRWLockWithPriority>> GuardWrapper;`
- L256 _public member_ `Private::ELockPriority Priority;`
- L257 _public member_ `FRWScopeLockType LockType;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L14 _typedef_ `namespace UE::AssetRegistry::Private { using FInterfaceRWLock = FRWLockWithPriority; } namespace UE::AssetRegistry::Private { template <typename TMutexType> class TTracingWriteScopeLock; } namespace UE::AssetRegistry::Private { template <typename TMutexType> class TTracingReadScopeLock; } namespace UE::AssetRegistry { template <typename TScopeLockType> class TRWScopeLockWithPriority; } namespace UE::AssetRegistry { using FInterfaceReadScopeLock = TRWScopeLockWithPriority<Private::TTracingReadScopeLock<Private::FRWLockWithPriority>>; } namespace UE::AssetRegistry { using FInterfaceWriteScopeLock = TRWScopeLockWithPriority<Private::TTracingWriteScopeLock<Private::FRWLockWithPriority>>; } namespace UE::AssetRegistry { using FInterfaceRWScopeLock = class FRWScopeLockWithPriority; } namespace UE::AssetRegistry::Private { class FRWLockWithPriority { public: FORCEINLINE void WriteLock() { Mutex.WriteLock(); } FORCEINLINE bool TryWriteLock() { return Mutex.TryWriteLock(); } FORCEINLINE void WriteUnlock() { Mutex.WriteUnlock(); } FORCEINLINE void ReadLock() { Mutex.ReadLock(); }` (scope `UE::AssetRegistry::Private`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L18 _typedef_ `namespace UE::AssetRegistry { using FInterfaceReadScopeLock = TRWScopeLockWithPriority<Private::TTracingReadScopeLock<Private::FRWLockWithPriority>>; } namespace UE::AssetRegistry { using FInterfaceWriteScopeLock = TRWScopeLockWithPriority<Private::TTracingWriteScopeLock<Private::FRWLockWithPriority>>; } namespace UE::AssetRegistry { using FInterfaceRWScopeLock = class FRWScopeLockWithPriority; } namespace UE::AssetRegistry::Private { class FRWLockWithPriority { public: FORCEINLINE void WriteLock() { Mutex.WriteLock(); } FORCEINLINE bool TryWriteLock() { return Mutex.TryWriteLock(); } FORCEINLINE void WriteUnlock() { Mutex.WriteUnlock(); } FORCEINLINE void ReadLock() { Mutex.ReadLock(); } FORCEINLINE bool TryReadLock() { return Mutex.TryReadLock(); }` (scope `UE::AssetRegistry`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L19 _typedef_ `namespace UE::AssetRegistry { using FInterfaceWriteScopeLock = TRWScopeLockWithPriority<Private::TTracingWriteScopeLock<Private::FRWLockWithPriority>>; } namespace UE::AssetRegistry { using FInterfaceRWScopeLock = class FRWScopeLockWithPriority; } namespace UE::AssetRegistry::Private { class FRWLockWithPriority { public: FORCEINLINE void WriteLock() { Mutex.WriteLock(); } FORCEINLINE bool TryWriteLock() { return Mutex.TryWriteLock(); } FORCEINLINE void WriteUnlock() { Mutex.WriteUnlock(); } FORCEINLINE void ReadLock() { Mutex.ReadLock(); } FORCEINLINE bool TryReadLock() { return Mutex.TryReadLock(); }` (scope `UE::AssetRegistry`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L20 _typedef_ `namespace UE::AssetRegistry { using FInterfaceRWScopeLock = class FRWScopeLockWithPriority; } namespace UE::AssetRegistry::Private { class FRWLockWithPriority { public: FORCEINLINE void WriteLock() { Mutex.WriteLock(); } FORCEINLINE bool TryWriteLock() { return Mutex.TryWriteLock(); } FORCEINLINE void WriteUnlock() { Mutex.WriteUnlock(); } FORCEINLINE void ReadLock() { Mutex.ReadLock(); } FORCEINLINE bool TryReadLock() { return Mutex.TryReadLock(); } FORCEINLINE void ReadUnlock()` (scope `UE::AssetRegistry`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L161 _namespace_ `namespace UE`
- L161 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L178 _function_ `` (scope `UE::AssetRegistry::FScopedHighPriorityWaitTracker::FScopedHighPriorityWaitTracker`)

### `Source/Runtime/AssetRegistry/Private/ActiveMountsLoader.h` (Private)


#### enum `UE::AssetRegistry::Impl::EMountState`  
`enum class EMountState : uint8`  
_L19-27_
- desc: Loading states of MountPoints managed by the ActiveMountsLoader state machine.
- L21 _public enumerator_ `Unloaded`
- L22 _public enumerator_ `Loading`
- L23 _public enumerator_ `Loaded`
- L24 _public enumerator_ `Unloading`
- L25 _public enumerator_ `Count`
- L26 _public enumerator_ `NumBits = FPlatformMath::ConstExprCeilLogTwo(EMountState::Count)`

#### class `UE::AssetRegistry::Impl::FAssetProvider`  
`class FAssetProvider`  
_L37-104_
- desc: A source of AssetDatas for the ActiveMountsLoader to apply to the AssetRegistry. Currently the only such source is a cooked AssetRegistry.bin file on disk. The filepath for a registered AssetRegistry.bin file is stored in an AssetProvider, and a record of the MountPoints that contain the AssetData paths within the AssetProvider are stored in the ActiveMountsLoader and associated with the AssetProvider.  The ActiveMountsLoader launches an async task to serialize the file from disk whenever it needs to reload AssetDatas under any of the MountPoints that contain the AssetData paths within the AssetProvider.
- L40 _public prototype_ `explicit FAssetProvider(FStringView InFilePath);`
- L43 _public prototype_ `FStringView GetFilePath() const;` — Return this provider's AssetRegistry.bin filepath that can be deserialized from disk to load the AssetDatas.
- L49 _public prototype_ `bool IsInitialProvider() const;` — Report whether this provider is global AssetRegistry's premade AssetRegistry. That AssetRegistry is notable because it is the first and the largest, and we have special handling to manage it performantly. It can not be unregistered.
- L50 _public prototype_ `void SetIsInitialProvider(bool bValue);`
- L60 _public prototype_ `const FixedTagPrivate::FWeakStorePtr& GetStore() const;` — Return a weak pointer to the opaque FixedTagPrivate::FStore that was created or referenced by FAssetRegistryState::Load when this provider was last deserialized from disk. FStore holds deduplicated FAssetData.TagsAndValues data for all AssetDatas in the AssetRegistryState. We record this FStore and pass it into the FAssetRegistryState::Load when we reload, which then reuses it rather than creating a new one. Other than passing it into FAssetRegistryState::Load, we do not interpret it. The pointer is weak and will be set to null if all AssetDatas using it are dismounted, in which case it will be recreated during Load.
- L61 _public prototype_ `void SetStore(FixedTagPrivate::FWeakStorePtr InStore);`
- L67 _public prototype_ `uint32& GetLoadRefCountPtr();` — A count of how many FMountPoints have been requested to reload and not yet reloaded. Used to manage the async task that loads them. This value contractually equals the number of FMountPointDatas associated with this AssetProvider that are in the loading state.
- L72 _public prototype_ `UE::Tasks::FTask& GetLoadTask();` — Return a mutable reference to the LoadTask; we create it on demand if not yet created and it will keep running until it finds no more work to do and exits. When the task exits it clears this reference to itself.
- L79 _public prototype_ `bool IsShutdown() const;` — Whether this AssetProvider is shutting down, which happens when it is unregistered by the game project to save on memory, or when the ActiveMountsLoader is shutting down. This field is used to block new activity while we wait for async tasks to shutdown.
- L80 _public prototype_ `void SetIsShutdown(bool bValue);`
- L86 _public prototype_ `bool HasMissingMountPoints() const;` — Information discovered during parsing of this provider's AssetRegistryState: true if there are AssetDatas in this provider for which we could not find the FPackageName::IMountPoint and therefore cannot unload/reload.
- L87 _public prototype_ `void SetHasMissingMountPoints(bool bValue);`
- L92 _public prototype_ `bool IsErrorNoUnload() const;` — Whether this AssetProvider encountered an error on load of its AssetRegistryState and therefore we should not unload AssetDatas in any of its MountPoints.
- L93 _public prototype_ `void SetIsErrorNoUnload(bool bValue);`
- L96 _private member_ `const FString FilePath;`
- L97 _private member_ `UE::Tasks::FTask LoadTask;`
- L98 _private member_ `FixedTagPrivate::FWeakStorePtr Store;`
- L99 _private member_ `uint32 LoadRefCount = 0;`
- L100 _private member_ `bool bInitialProvider : 1 = false;`
- L101 _private member_ `bool bShutdown : 1 = false;`
- L102 _private member_ `bool bHasMissingMountPoints : 1 = false;`
- L103 _private member_ `bool bErrorNoUnload : 1 = false;`

#### class `UE::AssetRegistry::Impl::FAssetProviderSetKey`  
`class FAssetProviderSetKey`  
_L111-123_
- desc: A wrapper structure for FAssetProviders in a TSet that allow them to be looked up by FilePath. This structure also maintains the TUniquePtr for the FAssetProvider, which need to be at a fixed pointer over their lifetime and therefore must be TUniquePtr rather than direct elements in the TSet.
- L114 _public prototype_ `explicit FAssetProviderSetKey(TUniquePtr<FAssetProvider>&& InAssetProvider);`
- L116 _public prototype_ `bool operator==(const FAssetProviderSetKey& Other) const;`
- L117 _public prototype_ `bool operator==(FStringView OtherProviderFilePath) const;`
- L119 _public prototype_ `FAssetProvider& GetAssetProvider() const;`
- L122 _private member_ `TUniquePtr<FAssetProvider> AssetProvider;`

#### class `UE::AssetRegistry::Impl::FMountPointData`  
`class FMountPointData`  
_L131-192_
- desc: Data held by the ActiveMountsLoader about a MountPoint that contains AssetDatas in one of its registered AssetProviders. This data includes the associated AssetProvider for the MountPoint and the state machine data for the unload/reload of the assets in the MountPoint.
- L134 _public prototype_ `explicit FMountPointData(TRefCountPtr<UE::PackageName::IMountPoint> InMountPoint, EMountState InInitialState);`
- L136 _public prototype_ `bool operator==(const FMountPointData& Other) const;`
- L137 _public prototype_ `bool operator==(UE::PackageName::IMountPoint* MountPoint) const;`
- L139 _public prototype_ `const TRefCountPtr<UE::PackageName::IMountPoint>& GetMountPoint() const;`
- L140 _public prototype_ `FAssetProvider* GetAssetProvider() const;`
- L141 _public prototype_ `void SetAssetProvider(FAssetProvider* InAssetProvider);`
- L146 _public prototype_ `EMountState GetCurrentState() const;` — The current state of the MountPoints unload/reload. This only changes when a request changes it into a transition state or when a completed unload/reload changes it back to a stable state.
- L147 _public prototype_ `void SetCurrentState(EMountState InState);`
- L152 _public prototype_ `EMountState GetTargetState() const;` — The currently requested unloaded or loaded state of the MountPoint. We track this requested state so that we can handle new requests that override old requests that are still in progress.
- L153 _public prototype_ `void SetTargetState(EMountState InState);`
- L160 _public prototype_ `bool IsErrorNoUnload() const;` — Whether this MountPoint encountered an error on load of (any of) its associated AssetProviders and therefore we should not unload AssetDatas under it. Notably, being associated with multiple AssetProviders is an error itself; @see HasMultipleProviders.
- L161 _public prototype_ `void SetIsErrorNoUnload(bool bValue);`
- L166 _public prototype_ `bool IsMultiSegmentName() const;` — Whether this MountPoint has a multisegment IMountPoint->GetLongPackageName(), such as /Game/Weapons/, and so requires more expensive calculations to determine whether a given AssetData LongPackageName is under it.
- L167 _public prototype_ `void SetIsMultiSegmentName(bool bValue);`
- L173 _public prototype_ `bool IsParentOrChild() const;` — Whether this MountPoint is a either a child or parent of another existing IMountPoint (e.g. /Game/Weapons/ is a child of /Game/, and /Game/ is a parent of /Game/Weapons/) and so we don't currently support unload AssetDatas under it.
- L174 _public prototype_ `void SetIsParentOrChild(bool bValue);`
- L180 _public prototype_ `bool HasMultipleProviders() const;` — Whether AssetDatas under this MountPoint exist in multiple AssetProviders, and therefore we should not unload AssetDatas under it. We do not currently support MountPoints in multiple AssetProviders because we want to save memory by avoiding tracking multiple providers.
- L181 _public prototype_ `void SetHasMultipleProviders(bool bValue);`
- L184 _private member_ `TRefCountPtr<UE::PackageName::IMountPoint> MountPoint;`
- L185 _private member_ `FAssetProvider* AssetProvider = nullptr;`
- L186 _private member_ `uint32 ErrorNoUnloadBit : 1 = false;`
- L187 _private member_ `uint32 MultiSegmentNameBit : 1 = false;`
- L188 _private member_ `uint32 IsParentOrChildBit : 1 = false;`
- L189 _private member_ `uint32 HasMultipleProvidersBit : 1 = false;`

#### struct `UE::AssetRegistry::Impl::FMountLoadEventSubscriber`  
`struct FMountLoadEventSubscriber : public FRefCountedObject`  
_L200-214_
- inherits: `FRefCountedObject`
- desc: Storage of an OnComplete function that was passed into LoadAsync or UnloadAsync. We hold this storage until all requests in the batch have completed and we can therefore call the OnComplete function. This struct is updated every time we complete a request for one of its MountPoints.
- L202 _public member_ `TFunction<void(bool bCanceled)> OnComplete;`
- L207 _public member_ `int32 RemainingCount = 0;` — We don't store the list of remaining MountPoints to save memory/time on storing it, and we can do that but still be able to debug if it ever gets stuck at non-zero value because that information already is present (stored in the other direction) in FActiveMountsLoader.Subscribers. If RemainingCount > 0, there should be a pointer to this somewhere in LoadSubscribers or UnloadSubscribers.
- L208 _public member_ `bool bWasCanceled = false;`
- L213 _public member_ `bool bIsLoadSubscriber = true;` — True if listening to loads (and referenced from LoadSubscribers), false if listening to unloads (and referenced from UnloadSubscribers).

#### class `UE::AssetRegistry::Impl::FActiveMountsLoader`  
`class FActiveMountsLoader`  
_L221-360_
- desc: The implementation of ActiveMountsLoading. This implementation class is created only when the feature is enabled in the current process. It holds data about how to reload each mountpoint and manages their state in an unload/reload state machine.
- L232 _public prototype_ `void StartShutdown(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TArray<UE::Tasks::FTask>& OutWaitOnAsync);` — Called by FActiveMountsLoaderWrapper::Shutdown. Signals threads to shutdown and reports all EventRefs that must be waited on for those threads to terminate. Followed by a call to FinishShutdown after waiting.
- L238 _public prototype_ `void FinishShutdown(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext);` — Called by FActiveMountsLoaderWrapper::Shutdown after waiting on EventRefs from StartShutdown. Clears all internal data, FActiveMountsLoader can now be deleted.
- L240 _public prototype_ `void LoadAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints, TFunction<void(bool bCanceled)>&& OnComplete);`
- L243 _public prototype_ `void ReloadAllAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TFunction<void(bool bCanceled)>&& OnComplete);`
- L245 _public prototype_ `void UnloadAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints, TFunction<void(bool bCanceled)>&& OnComplete);`
- L248 _public prototype_ `void UnloadAllUnmountedAsync(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TFunction<void(bool bCanceled)>&& OnComplete);`
- L250 _public prototype_ `bool IsLoaded(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, const TRefCountPtr<UE::PackageName::IMountPoint>& MountPoint);`
- L252 _public prototype_ `bool IsInProgress(UAssetRegistryImpl& UARI);`
- L253 _public prototype_ `void ReportWhenIdle(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TFunction<void()> OnIdle);`
- L255 _public prototype_ `void OnActiveMountsInitialize(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FInterfaceWriteScopeLock& ProofOfWriteLock);`
- L257 _public prototype_ `bool TryRegisterAssetProviderAndAppendStateOutsideARLock(UAssetRegistryImpl& UARI, FEventContext& AREventContext, FActiveMountEvents& EventContext, FStringView StateFilePath);`
- L259 _public prototype_ `bool TryLoadStateAndRegisterAssetProvider(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FInterfaceWriteScopeLock& ProofOfWriteLock, FPakPlatformFile* PakPlatformFile, FStringView StateFilePath, FAssetRegistryState& OutLoadedState);`
- L268 _public prototype_ `bool TryStartUnregisterAssetProvider(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TArray<UE::Tasks::FTask>& OutWaitOnAsync, FStringView StateFilePath);` — Called by FActiveMountsLoaderWrapper::UnregisterAssetProvider. Signals the AssetProvider's load thread to shutdown if it exists and reports the EventRefs that must be waited on for it to terminate. Followed by a call to FinishUnregisterAssetProvider after waiting. Returns false if the AssetProvider does not exist; FinishUnregisterAssetProvider should not be called in that case.
- L274 _public prototype_ `void FinishUnregisterAssetProvider(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FStringView StateFilePath);` — Called by FActiveMountsLoaderWrapper::UnregisterAssetProvider after waiting on EventRefs from StartShutdown. Clears the AssetProvider's data and the data of any MountPoints it owned.
- L277 _public prototype_ `void InitialProviderReport(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FAssetProviderInitData& StateInitData);`
- L279 _public prototype_ `void InitialProviderOnReadyForRegister(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, EInitialProviderRegisterReason Reason);`
- L281 _public prototype_ `void InitialProviderConditionalRegister(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FAssetRegistryState& AppendedState);`
- L284 _public prototype_ `void OnMountPointsMounted(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints);`
- L286 _public prototype_ `void OnMountPointsDismounted(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext, FInterfaceWriteScopeLock& ProofOfWriteLock, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> InMountPoints);`
- L295 _private prototype_ `void ParseInitialState(FAssetProvider& AssetProvider, const FAssetRegistryState& State);` — Inspect all of the AssetDatas in the AssetRegistryState loaded by an AssetProvider to find which MountPoints should be associated with it.
- L296 _private prototype_ `FMountPointData& FindOrAddMountPointData(UE::PackageName::IMountPoint* MountPoint, EMountState InitialState);`
- L297 _private prototype_ `FMountPointData* FindMountPointData(UE::PackageName::IMountPoint* MountPoint);`
- L298 _private prototype_ `void NotifyMountPointLoadComplete(FActiveMountEvents& EventContext, const TRefCountPtr<UE::PackageName::IMountPoint>& MountPoint, bool bCanceled);`
- L300 _private prototype_ `void NotifyMountPointUnloadComplete(FActiveMountEvents& EventContext, const TRefCountPtr<UE::PackageName::IMountPoint>& MountPoint, bool bCanceled);`
- L302 _private prototype_ `void ConditionalNotifyIdle(UAssetRegistryImpl& UARI, FActiveMountEvents& EventContext);`
- L303 _private prototype_ `void AddRefMountPointLoad(UAssetRegistryImpl& UARI, FMountPointData* MountPointData);`
- L304 _private prototype_ `void ReleaseMountPointLoad(UAssetRegistryImpl& UARI, FMountPointData* MountPointData);`
- L305 _private prototype_ `void AddRefMountPointUnload(UAssetRegistryImpl& UARI, FMountPointData* MountPointData);`
- L306 _private prototype_ `void ReleaseMountPointUnload(UAssetRegistryImpl& UARI, FMountPointData* MountPointData);`
- L308 _private prototype_ `void RunAssetProviderLoadTask(UAssetRegistryImpl& UARI, FAssetProvider& AssetProvider);` — The DoTask function for an AssetProvider's LoadTask for any requested MountPoint loads in it.
- L310 _private prototype_ `void RunMountPointUnloadTask(UAssetRegistryImpl& UARI);` — The DoTask function for the UnloadTask for any requested MountPoint unloads.
- L312 _private member_ `TSet<FAssetProviderSetKey> AssetProviders;`
- L313 _private member_ `TSet<FMountPointData> MountPoints;`
- L315 _private member_ `TMap<TRefCountPtr<UE::PackageName::IMountPoint>, TArray<TRefCountPtr<FMountLoadEventSubscriber>>> LoadSubscribers;` — The list of OnComplete functions that are waiting on a MountPoint to load.
- L317 _private member_ `TMap<TRefCountPtr<UE::PackageName::IMountPoint>, TArray<TRefCountPtr<FMountLoadEventSubscriber>>> UnloadSubscribers;` — The list of OnComplete functions that are waiting on a MountPoint to unload.
- L319 _private member_ `TArray<TFunction<void()>> OnIdleSubscribers;` — The list of callbacks that are waiting on ReportWhenIdle.
- L329 _private member_ `TSharedPtr<UE::FRecursiveMutex> RegistrationLock;` — An additional lock entered into by registration and unregistration functions. Unregistration functions have to wait outside of the usual ActiveMountsLoader lock on FActiveMountsLoaderWrapper::ActiveMountsLock because the tasks they wait on need to enter that lock. But we need to force only a single register/unregister to happen at once, so we have this lock. This lock must always be entered before entering the ActiveMountsLock. That creates a complex detail since it is possible the FActiveMountsLoader pointer holding this RegistrationLock is deleted during shutdown while we are about to try entering the RegistrationLock. We handle that detail by storing a shared pointer to the lock that might outlive the FActiveMountsLoader that created it.
- L334 _private member_ `UE::Tasks::FTask UnloadTask;` — The UnloadTask is created on demand if not yet created and it will keep running until it finds no more work to do and exits. When the task exits it clears this reference to itself.
- L340 _private member_ `uint32 MountPointUnloadRefCount = 0;` — A count of how many FMountPoints have been requested to unload and not yet unloaded. Used to manage the async task that unloads them. This value contractually equals the number of FMountPointDatas that are in the unloading state.
- L345 _private member_ `bool bAutoUnload : 1 = false;` — Configuration-specified variable for whether we should automatically request unload/reload when FPackageName::IMountPoints are dismounted/mounted.
- L347 _private member_ `bool bLoaderIsActive : 1 = false;` — True only after ActiveMountsInitialize is called and so we are allowed to service Unload/Load requests.
- L349 _private member_ `bool bInitialProviderReadyForRegister : 1 = false;` — InitialProviderOnReadyForRegister has been called.
- L351 _private member_ `bool bInitialProviderReported : 1 = false;` — InitialProviderReport has been called.
- L353 _private member_ `bool bInitialProviderRegistered : 1 = false;` — Gate value to ensure Call_Once on the initial provider's registration.
- L355 _private member_ `bool bAutoUnloadInitialUnloadTriggered : 1 = false;` — Gate value to ensure Call_Once on bAutoUnload's trigger of UnloadAllUnmountedAsync.
- L357 _private member_ `bool bShutdown : 1 = false;` — Set to true when AssetRegistry is shutting down and we are waiting for async; blocks any external requests.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L15 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L124 _prototype_ `extern uint32 GetTypeHash(const FAssetProviderSetKey& Key);` (scope `UE::AssetRegistry::Impl`)
- L193 _prototype_ `extern uint32 GetTypeHash(const FMountPointData& Key);` (scope `UE::AssetRegistry::Impl`)

### `Source/Runtime/AssetRegistry/Private/AssetDataGatherer.h` (Private)


#### struct `UE::AssetDataGather::Private::FWaitBatchDirectory`  
`struct FWaitBatchDirectory`  
_L50-65_
- L52 _public function_ `FWaitBatchDirectory(const FStringView InPath, const bool InIsRecursive) : Path(InPath) , bIsRecursive(InIsRecursive)`
- L63 _public member_ `FString Path;`
- L64 _public member_ `bool bIsRecursive;`

#### struct `UE::AssetDataGather::Private::FWaitBatchDirectorySetFuncs`  
`struct FWaitBatchDirectorySetFuncs : BaseKeyFuncs<FWaitBatchDirectory, FString>`  
_L67-81_
- inherits: `BaseKeyFuncs<FWaitBatchDirectory,FString>`
- L69 _public function_ `static FORCEINLINE const FString& GetSetKey(const FWaitBatchDirectory& Element)`
- L73 _public function_ `static FORCEINLINE bool Matches(const FString& A, const FString& B)`
- L77 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FString& Key)`

#### struct `FAssetGatherDiagnostics`  
`struct FAssetGatherDiagnostics`  
_L102-118_
- L105 _public member_ `float DiscoveryTimeSeconds;` — Time spent identifying asset files on disk
- L107 _public member_ `float GatherTimeSeconds;` — Time spent reading asset files on disk / from cache
- L109 _public member_ `float WallTimeSeconds;` — Time in between gatherer start and the call to GetDiagnostics.
- L111 _public member_ `int32 NumCachedDirectories;` — How many directories in the search results were read from the cache.
- L113 _public member_ `int32 NumUncachedDirectories;` — How many directories in the search results were not in the cache and were read by scanning the disk.
- L115 _public member_ `int32 NumCachedAssetFiles;` — How many files in the search results were read from the cache.
- L117 _public member_ `int32 NumUncachedAssetFiles;` — How many files in the search results were not in the cache and were read by parsing the file.

#### struct `UE::AssetDataGather::FResults`  
`struct FResults`  
_L124-152_
- desc: Structure to accumulate the results of the gather. Appended to from calls to FAssetDataGatherer::GetAndTrimSearchResults.
- L126 _public member_ `TMultiMap<FName, TUniquePtr<FAssetData>> Assets;`
- L127 _public member_ `TMultiMap<FName, TUniquePtr<FAssetData>> AssetsForGameThread;`
- L128 _public member_ `TRingBuffer<FString> Paths;`
- L129 _public member_ `TMultiMap<FName, FPackageDependencyData> Dependencies;`
- L130 _public member_ `TMultiMap<FName, FPackageDependencyData> DependenciesForGameThread;`
- L131 _public member_ `TRingBuffer<FString> CookedPackageNamesWithoutAssetData;`
- L132 _public member_ `TRingBuffer<FName> VerseFiles;`
- L133 _public member_ `TArray<FString> BlockedFiles;`
- L135 _public function_ `SIZE_T GetAllocatedSize() const`
- L141 _public function_ `void Shrink()`

#### struct `UE::AssetDataGather::FResultContext`  
`struct FResultContext`  
_L158-166_
- desc: Structure to receive transient data about the current state of the gather. Repopulated during every call to FAssetDataGatherer::GetAndTrimSearchResults.
- L160 _public member_ `bool bIsSearching = false;`
- L161 _public member_ `bool bAbleToProgress = false;`
- L162 _public member_ `TArray<double> SearchTimes;`
- L163 _public member_ `int32 NumFilesToSearch = 0;`
- L164 _public member_ `int32 NumPathsToSearch = 0;`
- L165 _public member_ `bool bIsDiscoveringFiles = false;`

#### class `FAssetDataGatherer`  
`class FAssetDataGatherer : public FRunnable`  
_L174-621_
- inherits: `FRunnable`
- desc: Async task for gathering asset data from from the file list in FAssetRegistry
- L177 _public prototype_ `FAssetDataGatherer(UAssetRegistryImpl& InRegistryImpl);`
- L178 _public prototype_ `virtual ~FAssetDataGatherer();`
- L184 _public prototype_ `void UpdateCacheForSaving();` — Update the the Gatherer's cache using in-memory state information before serializing. This method must be called while owning the InterfaceLock.
- L185 _public prototype_ `void OnInitialSearchCompleted();`
- L186 _public prototype_ `void OnAdditionalMountSearchCompleted();`
- L188 _public prototype_ `void RequestAsyncCacheSave();` — Requests a save of the cache as soon as possible.
- L190 _public prototype_ `void RequestDelayedAsyncCacheSave();` — Requests a delayed save of the cache. If a delayed save has already been requested, the delayed save timer is not reset.
- L192 _public prototype_ `void ClearRequestAsyncCacheSave();` — Removes any existing request to save the cache.
- L198 _public prototype_ `bool IsCacheSaveRequested(double* OutSaveRequestTime = nullptr) const;` — Returns true if an immediate or delayed save has been requested. Sets OutSaveRequestTime to the time the save was requested (value may be negative to indicate a save should occur immediately), zero otherwise.
- L203 _public prototype_ `bool IsCacheSaveReady() const;` — Returns true when a save has been requested and is ready to be handled. Delayed save requests are ready once FGatherSettings::MinSecondsToElapseBeforeCacheWrite seconds have elapsed since the time of the save request.
- L208 _public prototype_ `void StartAsync();` — Start the async thread, if this Gatherer was created async. Does nothing if not async or already started.
- L211 _public prototype_ `virtual bool Init() override;` — FRunnable implementation
- L212 _public prototype_ `virtual uint32 Run() override;`
- L213 _public prototype_ `virtual void Stop() override;`
- L214 _public prototype_ `virtual void Exit() override;`
- L216 _public prototype_ `bool IsAsyncEnabled() const;`
- L217 _public prototype_ `bool IsSynchronous() const;`
- L219 _public prototype_ `void EnsureCompletion();` — Signals to end the thread and waits for it to close before returning
- L222 _public prototype_ `FGatheredResultsEvent& GetGatheredResultsEvent();` — Returns reference to delegate invoked when search results have been gathered in GetAndTrimSearchResults.
- L225 _public prototype_ `void GetAndTrimSearchResults(UE::AssetDataGather::FResults& InOutResults, UE::AssetDataGather::FResultContext& OutContext);` — Gets search results from the data gatherer.
- L228 _public prototype_ `FAssetGatherDiagnostics GetDiagnostics();` — Get diagnostics for telemetry or logging.
- L230 _public prototype_ `void GetPackageResults(UE::AssetDataGather::FResults& InOutResults);` — Gets just the Assets, AssetsForGameThread, Dependencies, and DependenciesForGameThread from the data gatherer.
- L235 _public prototype_ `void WaitOnPath(FStringView LocalPath);` — Wait for all monitored assets under the given path to be added to search results. Returns immediately if the given path is not monitored.
- L241 _public prototype_ `void ClearCache();` — Saves the current cache state to disk, then empties the caches holding data read from disk and new data to be written to disk. Disables further caching. Used to save memory when cooking after the scan is complete. Saving is best-effort and may fail if the cache files are open for read on the system.
- L248 _public prototype_ `void ScanPathsSynchronous(const TArray<FString>& InPaths, bool bForceRescan, bool bIgnoreDenyListScanFilters);` — Add a set of paths to the allow list, optionally force rescanning and ignore deny list on them, and wait for all assets in the paths to be added to search results. Wait time is minimized by prioritizing the paths and transferring async scanning to the current thread.
- L250 _public prototype_ `void WaitForIdle(float TimeoutSeconds = -1.0f);` — Wait for all monitored assets to be added to search results.
- L256 _public prototype_ `bool IsComplete() const;` — Report whether all monitored assets have been added to search results, AND these results have been gathered through a GetAndTrimSearchResults call. This function can be used to check whether there is any work to be done on the gatherer.
- L260 _public prototype_ `bool HasSerializedDiscoveryCache() const;` — Returns true if the asset registry has written out the discovery cache after discovery has completed. This function will return false if discovery is not yet complete, discovery caching isn't supported by the current platform or cache writing has been disabled such as when using -NoAssetRegistryCacheWrite.
- L265 _public prototype_ `void SetInitialPluginsLoaded();` — Set after initial plugins have loaded and we should not retry failed loads with missing custom versions.
- L267 _public prototype_ `bool IsGatheringDependencies() const;` — Report whether the gatherer is configured to load depends data in addition to asset data.
- L269 _public prototype_ `bool IsCacheReadEnabled() const;` — Return whether the current process enables reading AssetDataGatherer cache files.
- L271 _public prototype_ `bool IsCacheWriteEnabled() const;` — Return whether the current process enables writing AssetDataGatherer cache files.
- L273 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Return the memory used by the gatherer. Used for performance metrics.
- L279 _public prototype_ `void AddMountPoint(FStringView LocalPath, FStringView LongPackageName);` — Add a mountpoint to the gatherer after it has been registered with FPackageName .
- L281 _public prototype_ `void RemoveMountPoint(FStringView LocalPath);` — Remove a previously added mountpoint.
- L283 _public prototype_ `void AddRequiredMountPoints(TArrayView<FString> LocalPaths);` — Add MountPoints in LocalPaths to the gatherer.
- L289 _public prototype_ `void OnDirectoryCreated(FStringView LocalPath);` — Called from DirectoryWatcher. Update the directory for reporting in future search results.
- L291 _public prototype_ `void OnFilesCreated(TConstArrayView<FString> LocalPaths);` — Called from DirectoryWatcher. Update the files for reporting in future search results.
- L293 _public prototype_ `void PrioritizeSearchPath(const FString& PathToPrioritize);` — Mark a file or directory to be scanned before unprioritized assets.
- L303 _public prototype_ `void SetIsOnAllowList(FStringView LocalPath, bool bIsAllowed);` — Mark whether a given path is in the scanning allow list. By default no paths are scanned; adding a path to the allow list causes it and its subdirectories to be scanned. Note that the deny list (InLongPackageNameDenyList) overrides the allow list. Allow list settings are recursive. Attempting to mark a path as allowed if a parent path is on the allow list will have no effect. This means the scenario ((1) add allow list A (2) add allow list A/Child (3) remove allow list A) will therefore not result in A/Child being allowed.
- L305 _public prototype_ `bool IsOnAllowList(FStringView LocalPath) const;` — Report whether the path is in the allow list. Only paths in AllowList AND not in DenyList will be scanned.
- L307 _public prototype_ `bool IsOnDenyList(FStringView LocalPath) const;` — Report whether the path is in the deny list. Paths in DenyList are not scanned.
- L309 _public prototype_ `bool IsMonitored(FStringView LocalPath) const;` — Report whether the path is both in the allow list and not in the deny list.
- L312 _public prototype_ `static bool IsVerseFile(FStringView FilePath);` — Determine, based on the file extension, if the given file path is a Verse file
- L314 _public prototype_ `static TConstArrayView<const TCHAR*> GetVerseFileExtensions();` — Return the list of extensions that indicate verse files.
- L325 _public prototype_ `static bool ReadAssetFile(FPackageReader& PackageReader, TArray<FAssetData*>& AssetDataList, FPackageDependencyData& DependencyData, TArray<FString>& CookedPackagesToLoadUponDiscovery, FPackageReader::EReadOptions Options);` — Reads FAssetData information out of a previously initialized package reader @param PackageReader the previously opened package reader @param AssetDataList the FAssetData for every asset found in the file @param DependencyData the FPackageDependencyData for every asset found in the file @param CookedPackagesToLoadUponDiscovery the list of cooked packages to be loaded if any @param Options Which bits of data to read
- L332 _public function_ `void PauseProcessing()` — Callable by the main thread to request that this thread pause/resume processing data. Gathering can still proceed during this time.
- L333 _public function_ `void ResumeProcessing()`
- L334 _public function_ `bool IsProcessingPauseRequested() const`
- L336 _public prototype_ `void SetGatherOnGameThreadOnly(bool bValue);`
- L337 _public prototype_ `bool IsGatherOnGameThreadOnly() const;`
- L342 _public prototype_ `void SetIsAdditionalMountSearchInProgress(bool bIsInProgress);` — Mark that the gatherer is in the process of handling an additional search.
- L356 _private prototype_ `ETickResult InnerTickLoop(bool bInSynchronousTick, bool bContributeToCacheSave, double EndTimeSeconds, bool* bShouldRequestAssetRegistryTick = nullptr);` — Helper function to run the tick in a loop-within-a-loop to minimize critical section entry, and to move expensive operations out of the critical section
- L361 _private prototype_ `ETickResult TickInternal(double& TickStartTime, bool bPollDiscovery, bool* bShouldRequestAssetRegistryTick = nullptr);` — Tick function to pump scanning and push results into the search results structure. May be called from devoted thread or inline from synchronous functions on other threads.
- L366 _private prototype_ `UE::AssetRegistry::Impl::EGatherStatus TryTickOnBackgroundThread();` — Conditionally Ticks the AssetRegistry from the background thread returning the result of gathering. Return the new status of the AssetRegistry's gather. If the background thread should not currently perfom ticking, EGatherStatus::Complete is returned.
- L369 _private prototype_ `bool ShouldBackgroundGatherThreadPauseGathering(bool& bOutGathererIsIdle);` — Called outside the TickLock or ResultLock; it takes the ResultLock internally.
- L372 _private prototype_ `void IngestDiscoveryResults();` — Add any new package files from the background directory scan to our work list
- L375 _private prototype_ `void OnFileCreated(FStringView LocalPath);` — Helper for OnFilesCreated. Update the file for reporting in future search results.
- L382 _private prototype_ `void SetDirectoryProperties(FStringView LocalPath, const UE::AssetDataGather::Private::FSetPathProperties& Properties);` — Set a selection of directory-scanning properties on a given LocalPath. This function is used when multiple properties need to be set on the path and we want to avoid redundant tree-traversal costs.
- L388 _private prototype_ `void WaitOnPathsInternal(TArrayView<UE::AssetDataGather::Private::FPathExistence> QueryPaths);` — Wait for all monitored assets under the given path to be added to search results. Returns immediately if the given path are not monitored.
- L391 _private prototype_ `void SortPathsByPriority(TArrayView<UE::AssetDataGather::Private::FPathExistence> QueryPaths, UE::AssetDataGather::Private::EPriority Priority, int32& OutNumPaths);` — Sort the pending list of filepaths so that assets under the given directory/filename are processed first.
- L405 _private prototype_ `bool ReadAssetFile(const FString& AssetLongPackageName, const FString& AssetFilename, TArray<FAssetData*>& AssetDataList, FPackageDependencyData& DependencyData, TArray<FString>& CookedPackagesToLoadUponDiscovery, bool& OutCanRetry) const;` — Reads FAssetData information out of a file @param AssetLongPackageName the package name of the file to read @param AssetFilename the local path of the file to read @param AssetDataList the FAssetData for every asset found in the file @param DependencyData the FPackageDependencyData for every asset found in the file @param CookedPackagesToLoadUponDiscovery the list of cooked packages to be loaded if any @param OutCanRetry Set to true if this file failed to load, but might be loadable later (due to missing modules) @return true if the file was successfully read
- L410 _private prototype_ `void ConsumeCacheFiles(TArray<UE::AssetDataGather::Private::FCachePayload> Payloads);` — Add the given AssetDatas into DiskCachedAssetDataMap and DiskCachedAssetBlocks.
- L415 _private prototype_ `void TryReserveSaveCache(bool& bOutShouldSave, TArray<TPair<FName,FDiskCachedAssetData*>>& AssetsToSave);` — If a cache save has been triggered, get the cache filename and pointers to all elements that should be saved, for later saving outside of the critical section.
- L421 _private prototype_ `bool TrySaveCacheFile(const TArray<TPair<FName,FDiskCachedAssetData*>>& AssetsToSave, bool bRequestSaveOnFailure = false);` — Tries to save the cache file for the assetdatas read from package headers, possibly sharded into multiple files. If the save fails, bRequestSaveOnFailure specifies whether a save will be requested again to be handled in a future gatherer tick. Returns whether the save was successful or not.
- L428 _private prototype_ `int64 SaveCacheFileInternal(const FString& CacheFilename, const TArray<TPair<FName,FDiskCachedAssetData*>>& AssetsToSave);` — If the CacheFilename/AssetsToSave are non empty, save the cache file. This function reads the read-only-after-creation data from each FDiskCachedAssetData*, but otherwise does not use data from this Gatherer and so can be run outside any critical section. Returns the size of the saved file, or 0 if nothing was saved for any reason.
- L434 _private prototype_ `void GetCacheAssetsToSave(TArray<TPair<FName,FDiskCachedAssetData*>>& OutAssetsToSave);` — Get the list of FDiskCachedAssetData* for saving into the cache. Includes both assets that were loaded in the gatherer and assets which were loaded from the cache and have not been pruned.
- L437 _private prototype_ `void AddToCache(FName PackageName, FDiskCachedAssetData* DiskCachedAssetData);` — Adds the given pair into NewCachedAssetDataMap. Detects collisions for multiple files with the same PackageName
- L443 _private prototype_ `void SetIsIdle(bool IsIdle);` — Mark that the gatherer has become idle or has become active. Called from tick function and configuration functions when they note a possible state change. Caller is responsible for holding the ResultsLock.
- L444 _private prototype_ `void SetIsIdle(bool IsIdle, double& TickStartTime);`
- L447 _private prototype_ `void Shrink();` — Minimize memory usage in the buffers used during gathering.
- L458 _private prototype_ `static FString NormalizeLocalPath(FStringView LocalPath);` — Convert the LocalPath into our normalized version.
- L460 _private prototype_ `static FStringView NormalizeLongPackageName(FStringView LongPackageName);` — Convert the LongPackageName into our normalized version.
- L468 _private member_ `mutable FGathererCriticalSection TickLock;` — Critical section to allow Tick to be called from worker thread or from synchronous functions on other threads. To prevent DeadLocks, TickLock can not be entered from within any of the other locks on this class.
- L473 _private member_ `mutable FGathererCriticalSection ResultsLock;` — A critical section to protect data transfer to GetAndTrimSearchResults. ResultsLock can be entered while holding TickLock.
- L476 _private member_ `FGatheredResultsEvent GatheredResultsEvent;` — Delegates invoked when results are gathered in GetAndTrimSearchResults
- L479 _private member_ `UAssetRegistryImpl& AssetRegistry;` — Variable section for variables that are constant during threading.
- L486 _private member_ `FRunnableThread* Thread;` — Thread to run async Ticks on. Constant during threading. Activated when StartAsync is called and bAsyncEnabled is true. If null, results will only be added when Wait functions are called. Constant during threading.
- L492 _private member_ `bool bAsyncEnabled;` — True if async gathering is enabled, false if e.g. singlethreaded or disabled by commandline. Even when enabled, gathering is still synchronous until StartAsync is called.
- L494 _private member_ `bool bGatherAssetPackageData;` — True if AssetPackageData should be gathered. Constant during threading.
- L496 _private member_ `bool bGatherDependsData;` — True if dependency data should be gathered. Constant during threading.
- L499 _private member_ `FDateTime GatherStartTime;` — Timestamp of the start of the gather for consistent marking of 'last discovered' time in caching
- L504 _private member_ `std::atomic<uint32> IsStopped;` — > 0 if we've been asked to abort gathering work in progress at the next opportunity.
- L506 _private member_ `mutable std::atomic<uint32> IsGatheringPaused;` — > 0 if we've been asked to pause the worker thread gathering work so a synchronous function can take over the tick.
- L509 _private member_ `mutable std::atomic<uint32> IsProcessingPaused;` — > 0 if we've been asked to pause processing work (but not gathering work) at the next opportunity
- L515 _private member_ `TUniquePtr<UE::AssetDataGather::Private::FAssetDataDiscovery> Discovery;` — Discovery subsystem; decides which paths to search and queries the FileManager to search directories. Pointer is constant during threading. Object pointed to internally provides threadsafety.
- L521 _private member_ `std::atomic<double> DelayedSaveAsyncCacheStartTime;` — Start time a delayed request to save the async cache was made. A save will be triggered after FGatherSettings::MinSecondsToElapseBeforeCacheWrite have elapsed. When an immediate save request is made this time will be negative.
- L523 _private member_ `std::atomic<bool> bCacheReadEnabled;` — True if the current process allows reading of AssetDataGatherer cache files.
- L525 _private member_ `std::atomic<bool> bCacheWriteEnabled;` — True if the current process allows writing of AssetDataGatherer cache files.
- L530 _private member_ `TUniquePtr<UE::AssetDataGather::Private::FFilesToSearch> FilesToSearch;` — List of files that need to be processed by the search.
- L533 _private member_ `TArray<TUniquePtr<FAssetData>> AssetResults;` — The asset data gathered from the searched files.
- L535 _private member_ `TArray<TUniquePtr<FAssetData>> AssetResultsForGameThread;` — Like AssetResults but for assets that must be processed on the game thread
- L537 _private member_ `TArray<FPackageDependencyData> DependencyResults;` — Dependency data gathered from the searched files packages.
- L539 _private member_ `TArray<FPackageDependencyData> DependencyResultsForGameThread;` — Like DependencyResults but for assets that must be processed on the game thread
- L544 _private member_ `TArray<FString> CookedPackageNamesWithoutAssetDataResults;` — A list of cooked packages that did not have asset data in them. These assets may still contain assets (if they were older for example).
- L546 _private member_ `TArray<FName> VerseResults;` — File paths (in UE LongPackagePath notation) of the Verse source code gathered from the searched files.
- L548 _private member_ `TArray<FString> BlockedResults;` — File paths (in regular filesystem notation) of blocked packages from the searched files.
- L551 _private member_ `TArray<double> SearchTimes;` — All the search times since the last call to GetAndTrimSearchResults.
- L553 _private member_ `float CumulativeGatherTime = 0.f;` — Sum of all SearchTimes.
- L556 _private member_ `TArray<FString> DiscoveredPaths;` — The directories found during the search.
- L559 _private member_ `double CurrentSearchTime = 0.;` — The time spent in TickInternal since the last idle time. Used for performance metrics when reporting results.
- L561 _private member_ `double LastCacheWriteTime;` — The last time at which the cache file was written, used to periodically update the cache.
- L563 _private member_ `int32 NumPathsToSearchAtLastSyncPoint;` — The cached value of the NumPathsToSearch returned by Discovery the last time we synchronized with it.
- L565 _private member_ `int32 NumCachedAssetFiles = 0;` — The total number of files in the search results that were read from the cache.
- L567 _private member_ `int32 NumUncachedAssetFiles = 0;` — The total number of files in the search results that were not in the cache and were read by parsing the file.
- L569 _private member_ `int32 NumUncachedAssetFilesOutstanding = 0;` — The total number of files in the search results that were not in the cache and are currently being read off disk.
- L571 _private member_ `bool bHasLoadedCache;` — Track whether the cache has been loaded.
- L573 _private member_ `bool bDiscoveryIsComplete;` — Track whether the Discovery subsystem has gone idle and we have read all filenames from it.
- L575 _private member_ `bool bIsComplete;` — Track whether this Gather has gone idle and a caller has read all search data from it.
- L577 _private member_ `bool bIsIdle;` — Track whether this Gatherer has gone idle, either it has no more work or it's blocked on external events.
- L579 _private member_ `bool bFirstTickAfterIdle;` — Track the first tick after idle to set up e.g. timing data.
- L581 _private member_ `bool bFinishedInitialDiscovery;` — True if we have finished discovering our first wave of files, to report metrics for that most-important wave.
- L583 _private member_ `std::atomic<bool> bIsInitialSearchCompleted;` — True if OnInitialSearchCompleted has been called.
- L585 _private member_ `std::atomic<bool> bIsAdditionalMountSearchInProgress;` — True if we have begun discovering files after the initial search.
- L586 _private member_ `std::atomic<bool> bGatherOnGameThreadOnly;`
- L594 _private member_ `TArray<FDiskCachedAssetData*> NewCachedAssetData;` — An array of all cached data that was newly discovered this run. This array is just used to make sure they are all deleted at shutdown.
- L595 _private member_ `TArray<TPair<int32, FDiskCachedAssetData*>> DiskCachedAssetBlocks;`
- L600 _private member_ `TMap<FName, FDiskCachedAssetData*> DiskCachedAssetDataMap;` — Map of PackageName to cached discovered assets that were loaded from disk. This should only be modified by ConsumeCacheFiles.
- L602 _private member_ `TMap<FName, FDiskCachedAssetData*> NewCachedAssetDataMap;` — Map of PackageName to cached discovered assets that will be written to disk at shutdown.
- L604 _private member_ `int32 LastCacheSaveNumUncachedAssetFiles;` — How many uncached asset files had been discovered at the last async cache save
- L609 _private member_ `bool bSynchronousTick;` — True if the current TickInternal is synchronous, which may be because !IsSynchronous or because the game thread has taken over the tick for a synchronous function.
- L614 _private member_ `bool bIsSavingAsyncCache;` — True when a thread is saving an async cache and therefore the cache cannot be deleted. This value resets after the save attempt has completed regardless of whether it was successful or not.
- L616 _private member_ `bool bFlushedRetryFiles;` — Packages can be marked for retry up until bInitialPluginsLoaded is set. After it is set, we retry them once.
- L618 _private member_ `TOptional<UE::AssetDataGather::Private::FWaitBatchDirectorySet> WaitBatchDirectories;` — Directories to explicitly wait for all files under it to be gatherered the next time we tick.
- L620 _private member_ `TUniquePtr<UE::AssetDataGather::Private::FFileReadScheduler> FileReadScheduler;` — Used to manage the async task for reading gathered files.
- L628 _function_ `inline bool FAssetDataGatherer::IsCacheSaveRequested(double* OutSaveRequestTime) const`
- L638 _function_ `inline void FAssetDataGatherer::RequestAsyncCacheSave()`
- L643 _function_ `inline void FAssetDataGatherer::RequestDelayedAsyncCacheSave()`
- L651 _function_ `inline void FAssetDataGatherer::ClearRequestAsyncCacheSave()`
- L656 _function_ `inline FGatheredResultsEvent& FAssetDataGatherer::GetGatheredResultsEvent()`
- L661 _function_ `inline void FAssetDataGatherer::SetGatherOnGameThreadOnly(bool bValue)`
- L666 _function_ `inline bool FAssetDataGatherer::IsGatherOnGameThreadOnly() const`
- L671 _function_ `inline void FAssetDataGatherer::SetIsAdditionalMountSearchInProgress(bool bIsInProgress)`

#### enum `FAssetDataGatherer::ETickResult`  
`enum class ETickResult`  
_L345-351_
- L347 _public enumerator_ `KeepTicking`
- L348 _public enumerator_ `PollDiscovery`
- L349 _public enumerator_ `Idle`
- L350 _public enumerator_ `Interrupt`

#### struct `FAssetDataGatherer::FScopedGatheringPause`  
`struct FScopedGatheringPause`  
_L450-455_
- desc: Scoped guard for pausing the asynchronous tick.
- L452 _public prototype_ `FScopedGatheringPause(const FAssetDataGatherer& InOwner);`
- L453 _public prototype_ `~FScopedGatheringPause();`
- L454 _public member_ `const FAssetDataGatherer& Owner;`

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L38 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L39 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L40 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L41 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L42 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L43 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L44 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L45 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L46 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L47 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L48 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L58 _function_ `friend int32 GetTypeHash(const FWaitBatchDirectory& WaitBatchDirectory)` (scope `UE::AssetDataGather::Private`)
- L83 _typedef_ `typedef TSet<FWaitBatchDirectory, FWaitBatchDirectorySetFuncs> FWaitBatchDirectorySet;` (scope `UE::AssetDataGather::Private`)
- L85 _namespace_ `namespace UE`
- L85 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L86 _namespace_ `namespace UE`
- L86 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L86 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L89 _typedef_ `typedef FCriticalSectionQueryable FGathererCriticalSection;`
- L90 _typedef_ `typedef FScopeLockQueryable FGathererScopeLock;`
- L91 _macro_ `#define CHECK_IS_LOCKED_CURRENT_THREAD(CritSec) check(CritSec.IsLockedOnCurrentThread())`
- L92 _macro_ `#define CHECK_IS_NOT_LOCKED_CURRENT_THREAD(CritSec) check(!CritSec.IsLockedOnCurrentThread())`
- L94 _typedef_ `typedef FCriticalSection FGathererCriticalSection;`
- L95 _typedef_ `typedef FScopeLock FGathererScopeLock;`
- L96 _macro_ `#define CHECK_IS_LOCKED_CURRENT_THREAD(CritSec) do {} while (false)`
- L97 _macro_ `#define CHECK_IS_NOT_LOCKED_CURRENT_THREAD(CritSec) do {} while (false)`
- L100 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FGatheredResultsEvent, const UE::AssetDataGather::FResults&);`
- L100 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FGatheredResultsEvent, const UE::AssetDataGather::FResults&);`
- L120 _namespace_ `namespace UE`
- L120 _namespace_ `namespace AssetDataGather` (scope `UE`)

### `Source/Runtime/AssetRegistry/Private/AssetDataGathererDiscoveryCache.h` (Private)


#### enum `UE::AssetDataGather::Private::EFeatureEnabled`  
`enum class EFeatureEnabled : uint8`  
_L19-24_
- L21 _public enumerator_ `Never`
- L22 _public enumerator_ `IfPlatformSupported`
- L23 _public enumerator_ `Always`

#### enum `UE::AssetDataGather::Private::EFeatureEnabledReadWrite`  
`enum class EFeatureEnabledReadWrite : uint32`  
_L26-47_
- L28 _public enumerator_ `NeverRead = 0x00`
- L29 _public enumerator_ `DefaultRead = 0x01`
- L30 _public enumerator_ `AlwaysRead = 0x02`
- L31 _public enumerator_ `ReadMask = 0x0f`
- L32 _public enumerator_ `NeverWrite = 0x00`
- L33 _public enumerator_ `DefaultWrite = 0x10`
- L34 _public enumerator_ `AlwaysWrite = 0x20`
- L35 _public enumerator_ `WriteMask = 0xf0`
- L36 _public enumerator_ `Invalid = 0xffffffff`
- L37 _public enumerator_ `NeverWriteNeverRead = NeverWrite | NeverRead` — aka Never
- L38 _public enumerator_ `NeverWriteDefaultRead = NeverWrite | DefaultRead`
- L39 _public enumerator_ `NeverWriteAlwaysRead = NeverWrite | AlwaysRead`
- L40 _public enumerator_ `DefaultWriteNeverRead = DefaultWrite | NeverRead`
- L41 _public enumerator_ `DefaultWriteDefaultRead = DefaultWrite | DefaultRead` — aka Default
- L42 _public enumerator_ `DefaultWriteAlwaysRead = DefaultWrite | AlwaysRead`
- L43 _public enumerator_ `AlwaysWriteNeverRead = AlwaysWrite | NeverRead`
- L44 _public enumerator_ `AlwaysWriteDefaultRead = AlwaysWrite | DefaultRead` — aka AlwaysWrite
- L46 _public enumerator_ `AlwaysWriteAlwaysRead = AlwaysWrite | AlwaysRead` — NOT given the nickname "Always", because skipping invalidation is not what users would expect from "Always"

#### struct `UE::AssetDataGather::Private::FCachedDirScanFile`  
`struct FCachedDirScanFile`  
_L52-57_
- desc: Data about a file in a cached directory used by FAssetDataDiscoveryCache to avoid the IO cost of rescanning.
- L54 _public member_ `FString RelPath;`
- L55 _public member_ `FDateTime ModificationTime;`
- L56 _public member_ `bool bIsReadOnly = false;`

#### struct `UE::AssetDataGather::Private::FCachedDirScanDir`  
`struct FCachedDirScanDir`  
_L61-78_
- desc: Data about a directory used by FAssetDataDiscoveryCache to avoid the IO cost of rescanning.
- L63 _public member_ `TArray<FString> SubDirRelPaths;`
- L64 _public member_ `TArray<FCachedDirScanFile> Files;`
- L65 _public member_ `FFileJournalFileHandle JournalHandle = FileJournalFileHandleInvalid;`
- L66 _public member_ `bool bCacheValid = false;`
- L72 _public member_ `TOptional<bool> bIsReparsePoint;` — bIsReparse True when this directory is a reparse point (symlink/junction/etc) It is optionally set to true or false when found during a directory scan If it is never found or set we will have to do an explicit IsSymLink on this directory
- L77 _public member_ `TOptional<bool> bIsInsideReparsePoint;` — bIsInsideReparsePoint True when this directory, or one of its parent directories are a ReparsePoint It is optional set when checking if this directory contains any ReparsePoints, Parent directories included

#### struct `UE::AssetDataGather::Private::FDiscoveredSubDirData`  
`struct FDiscoveredSubDirData`  
_L82-87_
- desc: Stores data from QueueAdd for subdirectories discovered during the directory scan, to be read during QueueConsume.
- L84 _public member_ `FString DirNameAbsPath;`
- L85 _public member_ `FFileJournalFileHandle JournalHandle;`
- L86 _public member_ `TOptional<bool> bIsReparsePoint;`

#### class `UE::AssetDataGather::Private::FCachedVolumeInfo`  
`class FCachedVolumeInfo`  
_L90-119_
- desc: Data about a volume used by FAssetDataDiscoveryCache to avoid the IO cost of rescanning directories on the volume.
- L93 _public prototype_ `void ConditionalConstruct(const FString& InVolumeName);`
- L94 _public prototype_ `void PreSave();`
- L95 _public prototype_ `void InitializePlatformData();`
- L98 _public prototype_ `FCachedDirScanDir& FindOrAddDir(FStringView InPath);` — Assumes Path has already been normalized.
- L99 _public prototype_ `FCachedDirScanDir& FindOrAddDir(FStringView InPath, bool& bOutAdded);`
- L100 _public prototype_ `void RemoveDirs(TArray<FString>&& InPaths);`
- L101 _public prototype_ `void RemoveInvalidDirs();`
- L103 _public prototype_ `FCachedDirScanDir* FindDir(FStringView Path);` — Assumes Path has already been normalized.
- L106 _public member_ `TMap<FString, FCachedDirScanDir> Dirs;`
- L107 _public member_ `FString VolumeName;`
- L108 _public member_ `FFileJournalId JournalId = FileJournalIdInvalid;`
- L109 _public member_ `FFileJournalEntryHandle NextJournalEntryToScan = FileJournalEntryHandleInvalid;`
- L113 _public member_ `TArray<FString> DirsToRemove;` — Directories that we marked for recursive removal from CachedVolumes; we consume this during WriteCacheFile.
- L114 _public member_ `FString LastError;`
- L115 _public member_ `FFileJournalId JournalIdOnDisk = FileJournalIdInvalid;`
- L116 _public member_ `FFileJournalEntryHandle NextJournalEntryOnDisk = FileJournalEntryHandleInvalid;`
- L117 _public member_ `uint64 JournalMaximumSize = 0;`
- L118 _public member_ `bool bJournalAvailable = false;`

#### class `UE::AssetDataGather::Private::FAssetDataDiscoveryCache`  
`class FAssetDataDiscoveryCache`  
_L131-175_
- desc: Keeps a record of the directories, files, and file timestamps that were found by the directory scan the last time it ran, and invalidates the records that have been reported modified by the PlatformFileJournal. ThreadSafety: Not threadsafe, with the exception of QueueAdd functions, which can be called at any time from any thread.
- L134 _public prototype_ `FString GetCacheFileName() const;`
- L136 _public function_ `bool IsInitialized() const`
- L137 _public function_ `EFeatureEnabled IsWriteEnabled() const`
- L138 _public prototype_ `void Shutdown();`
- L140 _public prototype_ `void LoadAndUpdateCache();`
- L141 _public prototype_ `void SaveCache();`
- L143 _public prototype_ `FCachedVolumeInfo& FindOrAddVolume(FStringView PathOrVolumeName);`
- L145 _public prototype_ `FCachedDirScanDir& FindOrAddDir(FStringView Path, FCachedVolumeInfo** OutVolume = nullptr);` — Assumes Path has already been normalized.
- L146 _public prototype_ `void RemoveDir(FStringView Path);`
- L148 _public prototype_ `FCachedVolumeInfo* FindVolume(FStringView PathOrVolumeName);`
- L150 _public prototype_ `FCachedDirScanDir* FindDir(FStringView Path, FCachedVolumeInfo** OutVolume = nullptr);` — Assumes Path has already been normalized.
- L152 _public prototype_ `void QueueConsume();`
- L153 _public prototype_ `void QueueAdd(FString DirName, FCachedDirScanDir DirData);`
- L154 _public prototype_ `void QueueAdd(FString DirName, FFileJournalFileHandle JournalHandle, bool bIsReparsePoint);`
- L157 _private prototype_ `bool TryReadCacheFile();`
- L158 _private prototype_ `void SerializeReadCacheFile(FArchive& Ar, bool& bOutCacheVersionMismatch);`
- L159 _private prototype_ `void SerializeWriteCacheFile(FArchive& Ar);`
- L161 _private prototype_ `bool FindOrAddIsReparsePoint(FStringView DirName, FCachedVolumeInfo& CachedVolume);`
- L165 _private member_ `TSortedMap<FString, FCachedVolumeInfo> CachedVolumes;` — Cached information about each volume on disk that has mounted directories.
- L167 _private member_ `TMpscQueue<TPair<FString, FCachedDirScanDir>> ScanQueueDirFullDatas;` — Childpath information about directories collected from ParallelFor during scanning.
- L169 _private member_ `TMpscQueue<FDiscoveredSubDirData> ScanQueueDirHandles;` — JournalHandle information about directories collected during ParallelFor during scanning.
- L172 _private member_ `bool bInitialized = false;` — Used to implement initialization on demand.
- L174 _private member_ `EFeatureEnabled WriteEnabled = EFeatureEnabled::Never;` — Whether writing the cache is enabled for no volumes, all volumes, or ones with journal available.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L48 _prototype_ `ENUM_CLASS_FLAGS(EFeatureEnabledReadWrite);` (scope `UE::AssetDataGather::Private`)
- L49 _prototype_ `void LexFromString(EFeatureEnabledReadWrite& OutValue, FStringView Text);` (scope `UE::AssetDataGather::Private`)
- L58 _prototype_ `FArchive& operator<<(FArchive& Ar, FCachedDirScanFile& Data);` (scope `UE::AssetDataGather::Private`)
- L79 _prototype_ `FArchive& operator<<(FArchive& Ar, FCachedDirScanDir& Data);` (scope `UE::AssetDataGather::Private`)
- L120 _prototype_ `FArchive& operator<<(FArchive& Ar, FCachedVolumeInfo& Data);` (scope `UE::AssetDataGather::Private`)
- L177 _variable_ `constexpr const TCHAR* GEmptyVolumeName = TEXT("<Em` (scope `UE::AssetDataGather::Private`)

### `Source/Runtime/AssetRegistry/Private/AssetDataGathererPrivate.h` (Private)


#### enum `UE::AssetDataGather::Private::EPriority`  
`enum class EPriority : uint8`  
_L25-36_
- desc: Enum to specify files and directories that should be completed earlier than others
- L28 _public enumerator_ `Blocking` — Game thread is blocked until the file/directory is completed
- L30 _public enumerator_ `High` — Optional information (e.g. use of the ReferenceViewer) is unavailable until the file/directory is completed
- L32 _public enumerator_ `Normal` — Nothing has requested the file/directory yet
- L34 _public enumerator_ `Highest = Blocking`
- L35 _public enumerator_ `Lowest = Normal`

#### struct `UE::AssetDataGather::Private::FSetPathProperties`  
`struct FSetPathProperties`  
_L39-63_
- desc: Fields being set in a call to SetProperty
- L42 _public member_ `TOptional<bool> IsOnAllowList;` — The path (usually a plugin's root content path) was requested for scanning through e.g. ScanPathsSynchronous
- L46 _public member_ `TOptional<bool> MatchesDenyList;` — Set whether the given directory matches a deny list entry.
- L50 _public member_ `TOptional<bool> IgnoreDenyList;` — Set whether the given directory should ignore the deny list, even if it or its parent matches a deny list entry.
- L55 _public member_ `TOptional<bool> HasScanned;` — The directory's list of direct file/subdirectory children has been scanned through a call to IFileManager::IterateDirectoryStat after process start or the last request to rescan it
- L58 _public function_ `bool IsSet() const` — Used to early-exit from tree traversal when all properties have finished being handled

#### enum `UE::AssetDataGather::Private::EGatherableFileType`  
`enum class EGatherableFileType : uint8`  
_L66-73_
- desc: To distinguish between assets and Verse source code
- L68 _public enumerator_ `Invalid`
- L69 _public enumerator_ `Directory`
- L70 _public enumerator_ `PackageFile`
- L71 _public enumerator_ `VerseFile`
- L72 _public enumerator_ `VerseModule`

#### struct `UE::AssetDataGather::Private::FDiscoveredPathData`  
`struct FDiscoveredPathData`  
_L78-105_
- desc: Information needed about a discovered asset file or path that is needed by the Discoverer
- L81 _public member_ `FString LocalAbsPath;` — The absolute path to the file on disk, relative to the directory that issued the scan
- L83 _public member_ `FString LongPackageName;` — The LongPackageName of the path (inherited from the MountDir)
- L85 _public member_ `FString RelPath;` — The relative path from the path's parent directory
- L87 _public member_ `FDateTime PackageTimestamp;` — If the path is a file, the modification timestamp of the package file (that it had when it was discovered).
- L89 _public member_ `bool bIsReadOnly;` — If the file is readonly
- L91 _public member_ `EGatherableFileType Type = EGatherableFileType::Invalid;` — The type of file that was found
- L93 _public prototype_ `FDiscoveredPathData() = default;`
- L94 _public prototype_ `FDiscoveredPathData(FStringView InLocalAbsPath, FStringView InLongPackageName, FStringView InRelPath, const FDateTime& InPackageTimestamp, bool InIsReadonly, EGatherableFileType InType);`
- L96 _public prototype_ `FDiscoveredPathData(FStringView InLocalAbsPath, FStringView InLongPackageName, FStringView InRelPath, EGatherableFileType InType);`
- L98 _public prototype_ `void Assign(FStringView InLocalAbsPath, FStringView InLongPackageName, FStringView InRelPath, const FDateTime& InPackageTimestamp, bool InIsReadOnly, EGatherableFileType InType);`
- L100 _public prototype_ `void Assign(FStringView InLocalAbsPath, FStringView InLongPackageName, FStringView InRelPath, EGatherableFileType InType);`
- L104 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Return the total amount of heap memory used by the gatherer (including not-yet-claimed search results).

#### struct `UE::AssetDataGather::Private::FGatheredPathData`  
`struct FGatheredPathData`  
_L108-135_
- desc: Information needed about a discovered asset file or path that is needed by the Gatherer
- L111 _public member_ `FString LocalAbsPath;` — The absolute path to the file on disk, relative to the directory that issued the scan
- L113 _public member_ `FString LongPackageName;` — The LongPackageName of the path (inherited from the MountDir)
- L115 _public member_ `FDateTime PackageTimestamp;` — The modification timestamp of the package file (that it had when it was discovered)
- L117 _public member_ `bool bIsReadOnly;` — If the file is readonly
- L119 _public member_ `EGatherableFileType Type = EGatherableFileType::Invalid;` — The type of file that was found
- L121 _public prototype_ `FGatheredPathData() = default;`
- L122 _public prototype_ `FGatheredPathData(FStringView InLocalAbsPath, FStringView InLongPackageName, const FDateTime& InPackageTimestamp, bool InIsReadOnly, EGatherableFileType InType);`
- L124 _public prototype_ `explicit FGatheredPathData(const FDiscoveredPathData& DiscoveredData);`
- L125 _public prototype_ `explicit FGatheredPathData(FDiscoveredPathData&& DiscoveredData);`
- L126 _public prototype_ `void Assign(FStringView InLocalAbsPath, FStringView InLongPackageName, const FDateTime& InPackageTimestamp, bool InIsReadOnly, EGatherableFileType InType);`
- L128 _public prototype_ `void Assign(const FDiscoveredPathData& DiscoveredData);`
- L134 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Return the total amount of heap memory used by the gatherer (including not-yet-claimed search results). Used for performance metrics.

#### struct `UE::AssetDataGather::Private::FDirectoryReadTaskData`  
`struct FDirectoryReadTaskData`  
_L138-160_
- desc: Holds scheduling context reading assets during gathering defined in a ReadContext
- L140 _public function_ `FDirectoryReadTaskData() : UnblockRead(TEXT("UnblockingDirectoryReadTaskEvent")) , LastScheduledReadTask()`
- L146 _public function_ `~FDirectoryReadTaskData()`
- L155 _public member_ `UE::Tasks::FTaskEvent UnblockRead;`
- L156 _public member_ `UE::Tasks::FTask LastScheduledReadTask;`
- L157 _public member_ `int32 OutstandingReads = 0;`
- L159 _public member_ `bool bHasCanceledRead = false;` — Indicates a read for this directory was cancelled, implying that the directory will be rescheduled in a later gather.

#### struct `UE::AssetDataGather::Private::FReadContext`  
`struct FReadContext`  
_L163-196_
- desc: Holds data gathered from a package file on disk that is ingested into the cache and the AssetRegistry.
- L165 _public member_ `FName PackageName;`
- L166 _public member_ `FName Extension;`
- L167 _public member_ `FGatheredPathData AssetFileData;`
- L168 _public member_ `TArray<FAssetData*> AssetDataFromFile;`
- L169 _public member_ `FPackageDependencyData DependencyData;`
- L170 _public member_ `TArray<FString> CookedPackageNamesWithoutAssetData;`
- L171 _public member_ `TSharedPtr<FDirectoryReadTaskData> DirectoryReadTaskData;`
- L172 _public member_ `UE::AssetRegistry::Private::EOptionalBool HasMarkOfTheWeb = UE::AssetRegistry::Private::EOptionalBool::Unset;`
- L173 _public member_ `bool bCanAttemptAssetRetry = false;`
- L174 _public member_ `bool bResult = false;`
- L175 _public member_ `bool bCanceled = false;`
- L177 _public function_ `FReadContext(FName InPackageName, FName InExtension, FGatheredPathData&& InAssetFileData, TSharedPtr<FDirectoryReadTaskData> InDirectoryReadTaskData) : PackageName(InPackageName) , Extension(InExtension) , AssetFileData(MoveTemp(InAssetFileData)) , DirectoryReadTaskData(MoveTemp(InDirectoryReadTaskData))`
- L190 _public function_ `~FReadContext()`

#### class `UE::AssetDataGather::Private::FFileReadScheduler`  
`class FFileReadScheduler`  
_L199-281_
- desc: Manages the scheduling of FReadContexts
- L202 _public prototype_ `FFileReadScheduler(int32 InNumReadThreads, bool InGatherAssetPackageData, bool InGatherDependsData);`
- L203 _public prototype_ `~FFileReadScheduler();`
- L206 _public prototype_ `bool IsAssetPackageDataGatherEnabled() const;` — Returns true if AssetPackageData should be gathered. Constant during threading.
- L208 _public prototype_ `bool IsDependsDataGatherEnabled() const;` — Returns true if dependency data should be gathered. Constant during threading.
- L210 _public prototype_ `void AddFile(const FName PackageName, FGatheredPathData&& AssetData);` — Add file to be scheduled for reading asynchronously.
- L215 _public prototype_ `bool Wait(FTimespan Timeout = FTimespan::MaxValue());` — Waits for all scheduled directories to be completed or until the given timeout is elapsed (default: wait for all directories). Returns true if all scheduled directories have been completed, false otherwise.
- L220 _public prototype_ `void WaitOnDirectoriesAndUpdateWaitList(FWaitBatchDirectorySet& WaitBatchDirectories);` — Schedule immediately and waits for all reads for the directories listed in WaitBatchDirectories. The list will be updated with all child directories waited on if the passed in directory was listed as recursive.
- L226 _public prototype_ `void Schedule(const TArray<FString>& PriorityDirectories);` — Schedules all added files since the last call to Schedule to be picked up by the task system such that up to NumReadTaskThreads normal priority tasks may be in-flight at once. Existing or newly added directories in the given list of PriorityDirectories will be scheduled immediately and not bound by the schedulers NumReadTaskThreads limit.
- L231 _public prototype_ `void CollectCompletedReads(TArray<TUniquePtr<FReadContext>>& OutReadyContexts);` — Populates the provided array with all completed reads (completed means read context is no longer being processed. One must still check for success/failure/cancellation).
- L236 _public prototype_ `void RemoveScheduledDirectory(const FString& Directory);` — Removes a scheduled directory from the scheduler. When all added files for a directory have been scheduled and completed, the directory should be removed to avoid overhead should a wait batch directory attempt to wait on the empty, still scheduled, directory.
- L242 _public prototype_ `void ProcessReadContexts(TArray<TUniquePtr<UE::AssetDataGather::Private::FReadContext>>&& ReadContexts, bool bIsTimeSliced);` — Reads and stores gather results for asset files in the provided array. If time slicing is used this method may exit before all read contexts are processed, and if so, will mark unprocessed read contexts as cancelled so they may be rescheduled in another gatherer tick.
- L247 _public prototype_ `void FreeReadTaskLoaders();` — Releases all allocated read task loaders created during gathering. Must be called while gathering is not in progress.
- L249 _public prototype_ `void Shrink();` — Frees unnecessary allocations the scheduler may have accrued.
- L255 _private prototype_ `void ScheduleDirectory(UE::Tasks::FTaskConcurrencyLimiter& TaskLimiter, const FString& DirectoryPath, TArray<TUniquePtr<FReadContext>>&& ReadContexts, bool bUnblockImmediately);` — Schedules the specified directory and read contexts for reading inside of the provided Task Limiter. If bUnblockImmediately is true, the limiter is not used.
- L259 _private member_ `TMap<FString, TArray<TUniquePtr<FReadContext>>> DirectoryReadsToSchedule;` — Map of directories to the files within that directory (non-recursive) needing scheduling.
- L261 _private member_ `TMpscQueue<TUniquePtr<UE::AssetDataGather::Private::FReadContext>> ReadyReadContexts;` — List of FReadContexts that have been populated (or cancelled) from worker threads requiring processing.
- L263 _private member_ `TLockFreePointerListFIFO<FNonBufferingReadOnlyArchive, 0> ReadTaskLoaderFreeList;` — Freelist of loaders created on task threads during gathering.
- L265 _private member_ `UE::Tasks::FTaskConcurrencyLimiter ReadConcurrencyLimiter;` — Used to control how parallel background asset file reading can be.
- L271 _private member_ `TUniquePtr<TDirectoryTree<TSharedPtr<UE::AssetDataGather::Private::FDirectoryReadTaskData>>> ScheduledDirectories;` — Tree of directories being gathered asynchronously. The FDirectoryReadTaskData is used to trigger and track the FTask performing file reads for that directory. We scheduled file reads by the directory they reside in to avoid contention caused by the OS filesystem.
- L276 _private member_ `int32 NumReadTaskThreads;` — Number of parallel read tasks allowed while gathering (wait batches are allowed to run in parallel to these tasks allowing for > NumReadTaskThreads to possibly be in flight at once.)
- L278 _private member_ `bool bGatherAssetPackageData;` — True if AssetPackageData should be gathered. Constant during threading.
- L280 _private member_ `bool bGatherDependsData;` — True if dependency data should be gathered. Constant during threading.
- L1127 _function_ `inline bool FFileReadScheduler::IsAssetPackageDataGatherEnabled() const`
- L1131 _function_ `inline bool FFileReadScheduler::IsDependsDataGatherEnabled() const`

#### class `UE::AssetDataGather::Private::FFilesToSearch`  
`class FFilesToSearch`  
_L284-330_
- desc: A container to efficiently receive files from discovery and search the container to raise priority of a path
- L288 _public prototype_ `void AddPriorityFile(FGatheredPathData&& FilePath);` — Add the given FilePath as a single file with blocking priority.
- L290 _public prototype_ `void AddFiles(TArray<FGatheredPathData>&& FilePaths);` — Add the given FilePaths with normal priority.
- L292 _public prototype_ `void AddFileAgainAfterTimeout(FGatheredPathData&& FilePath);` — Re-add a file from PopFront that we didn't have time to process.
- L297 _public prototype_ `void AddFileForLaterRetry(FGatheredPathData&& FilePath);` — Re-add a file from PopFront that uses a not-yet-loaded class for later retry. Later retry files are not returned from PopFront until RetryLaterRetryFiles is called.
- L299 _public prototype_ `void RetryLaterRetryFiles();` — Move all of the LaterRetry files into the main list so that they are once again visible to PopFront.
- L303 _public prototype_ `template <typename AllocatorType> void PopFront(TArray<FGatheredPathData, AllocatorType>& Out, int32 NumToPop);` — In coarse priority order, pop the given number of files out of the container.
- L309 _public prototype_ `void PrioritizePath(FPathExistence& QueryPath, EPriority Priority);` — Search the container for all files at or under the given path and set their priority. Path might be a directory name or a file BaseNameWithPath, or a file BaseNameWithPath.Extension.
- L311 _public prototype_ `void PopPriorityDirectories(TArray<FString>& OutPriorityDirectories);`
- L314 _public prototype_ `int32 NumBlockingFiles() const;` — How many files with blocking priority are in the container.
- L317 _public prototype_ `void Shrink();` — Reduce memory used in buffers.
- L319 _public prototype_ `int32 Num() const;` — How many files are in the container, including unavailable files.
- L321 _public prototype_ `int32 GetNumAvailable() const;` — How many files are returnable from PopFront.
- L323 _public prototype_ `SIZE_T GetAllocatedSize() const;` — How much memory is used by the container, not counting sizeof(*this).
- L325 _private member_ `TRingBuffer<FString> PriorityDirectories;`
- L326 _private member_ `TRingBuffer<UE::AssetDataGather::Private::FGatheredPathData> NormalPriorityFiles;`
- L327 _private member_ `TRingBuffer<UE::AssetDataGather::Private::FGatheredPathData> BlockingFiles;`
- L328 _private member_ `TRingBuffer<UE::AssetDataGather::Private::FGatheredPathData> LaterRetryFiles;`
- L329 _private member_ `int32 AvailableFilesNum = 0;`

#### struct `UE::AssetDataGather::Private::FPathExistence`  
`struct FPathExistence`  
_L334-365_
- desc: Stores a LocalAbsPath and existence information. A file system query is issued the first time the data is needed.
- L345 _public prototype_ `explicit FPathExistence(FStringView InLocalAbsPath);`
- L346 _public prototype_ `const FString& GetLocalAbsPath() const;`
- L347 _public prototype_ `EType GetType();`
- L348 _public prototype_ `FDateTime GetModificationTime();`
- L349 _public prototype_ `bool IsReadOnly();`
- L352 _public prototype_ `FStringView GetLowestExistingPath();` — If the path is a directory or file, return the path. Otherwise return the parent directory, if it exists.
- L355 _public prototype_ `void LoadExistenceData();` — Issue the file system query if not already done.
- L356 _public prototype_ `bool HasExistenceData() const;`
- L357 _public prototype_ `void SetConfirmedExists(bool bValue);`
- L360 _private member_ `FString LocalAbsPath;`
- L361 _private member_ `FDateTime ModificationTime;`
- L362 _private member_ `EType PathType = EType::MissingParentDir;`
- L363 _private member_ `bool bIsReadOnly = false;`
- L364 _private member_ `bool bHasExistenceData = false;`

#### enum `UE::AssetDataGather::Private::FPathExistence::EType`  
`enum EType`  
_L337-343_
- desc: What kind of thing we found at the given path
- L339 _public enumerator_ `Directory`
- L340 _public enumerator_ `File`
- L341 _public enumerator_ `MissingButDirExists`
- L342 _public enumerator_ `MissingParentDir`

#### class `UE::AssetDataGather::Private::FScanDir`  
`class FScanDir : public FRefCountedObject`  
_L374-543_
- inherits: `FRefCountedObject`
- desc: Tree data node representing a directory in the scan; direct subdirectories are stored as other FScanDir instances referenced from the SubDirs array. Directories are removed from the tree once their scans are finished to save memory. Queries take into account that deleted nodes have been completed. This class is not ThreadSafe; The FAssetDataDiscovery reads/writes its data only while holding TreeLock.
- L396 _public prototype_ `FScanDir(FMountDir& InMountDir, FScanDir* InParent, FStringView RelPath);`
- L397 _public prototype_ `~FScanDir();`
- L403 _public prototype_ `void Shutdown();` — Marks that this ScanDir is no longer in use and clear its data. The ScanDir will remain allocated until all threads have dropped their reference to it.
- L406 _public prototype_ `bool IsValid() const;` — Check whether this ScanDir is alive; it may have been marked for destruction and cleared on another thread.
- L408 _public prototype_ `FMountDir* GetMountDir() const;`
- L411 _public prototype_ `FStringView GetRelPath() const;` — Get this ScanDir's RelPath from its Parent
- L414 _public prototype_ `void AppendLocalAbsPath(FStringBuilderBase& OutFullPath) const;` — Calculate this ScanDir's full absolute path by accumulating RelPaths from parents and append it.
- L416 _public prototype_ `FString GetLocalAbsPath() const;` — Calculate this ScanDir's full absolute path by accumulating RelPaths from parents and return it as a string.
- L418 _public prototype_ `void AppendMountRelPath(FStringBuilderBase& OutRelPath) const;` — Calculate the relative path from the MountPoint to this ScanDir and append it to OutRelPath.
- L420 _public prototype_ `FString GetMountRelPath() const;` — Calculate the relative path from the MountPoint to this ScanDir and return it as a string.
- L426 _public prototype_ `void GetMonitorData(FStringView InRelPath, const FInherited& ParentData, FInherited& OutData) const;` — Report whether the given RelPath is allow listed and not deny listed, based on parent data and on the discovered settings on Stem ScanDirs between *this and the leaf path.
- L428 _public prototype_ `bool IsMonitored(const FInherited& ParentData) const;` — Return whether this scandir is allow listed and not deny listed and hence needs to be or has been scanned.
- L431 _public prototype_ `bool ShouldScan(const FInherited& ParentData) const;` — Report whether this ScanDir will be scanned in the current or future Tick.
- L433 _public prototype_ `bool HasScanned() const;` — Report whether this ScanDir has been scanned.
- L435 _public prototype_ `bool IsComplete() const;` — Report whether this ScanDir is complete: has scanned or should not scan, and all subdirs have completed.
- L438 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Return the memory used by the tree under this ScanDir; excludes sizeof(*this).
- L444 _public prototype_ `FScanDir* GetControllingDir(FStringView InRelPath, bool bIsDirectory, const FInherited& ParentData, FInherited& OutData, FString& OutRelPath);` — Find the Direct parent of InRelPath, or a fallback. Will return null only if !bIsDirectory and InRelPath is empty. The fallback is returned if InRelPath has already completed and been deleted, or if InRelPath is not monitored. The fallback is the lowest existing parent directory of InRelPath.
- L451 _public prototype_ `void TrySetDirectoryProperties(FPathExistence& QueryPath, FStringView InRelPath, FInherited& ParentData, const FSetPathProperties& InProperties, FScanDirAndParentData& OutControllingDir, FStringView& OutControllingDirRelPath, bool& bInOutMadeChanges);` — Set values of fields on the given directory indicated by InRelPath for all properties existing on InProperties. @param bInOutMadeChanges Set to true if any changes are made. Caller is responsible for initializing to false.
- L458 _public prototype_ `void MarkFileAlreadyScanned(FStringView BaseName);` — Mark that the given file has already been scanned, so that it will not be double reporting in the upcoming directory scan, if one is upcoming.
- L464 _public prototype_ `void SetScanResults(FStringView LocalAbsPath, const FInherited& ParentData, TArrayView<FDiscoveredPathData>& InOutSubDirs, TArrayView<FDiscoveredPathData>& InOutFiles);` — Called from the Tick; handle the list of subdirs and files that were found from IterateDirectoryStat called on this ScanDir, reporting discovered files and updating status variables.
- L470 _public prototype_ `void Update(TArray<FScanDirAndParentData>& OutScanRequests, const FScanDir::FInherited& ParentData);` — Update the completion state of this ScanDir and all ScanDirs under it based on each dir's scan status and its child dirs' completion state. Add any ScanDirs that need to be scanned to OutScanRequests.
- L472 _public prototype_ `FScanDir* GetFirstIncompleteScanDir();`
- L475 _public prototype_ `bool IsScanInFlight() const;` — Thread-synchronization helper - return true if the Tick thread is in the middle of scanning this directory.
- L477 _public prototype_ `void SetScanInFlight(bool bInScanInFlight);` — Thread-synchronization helper - set that the Tick thread is starting/done with the scan of this directory.
- L482 _public prototype_ `bool IsScanInFlightInvalidated() const;` — Thread-synchronization helper - report whether a non tick thread has marked that this directory is changed or invalidated and the scan should be thrown out.
- L487 _public prototype_ `void SetScanInFlightInvalidated(bool bInValidated);` — Thread-synchronization helper - set that the current ongoing scan is invalidated, or clear the marker from the tick thread once it has been consumed.
- L490 _public prototype_ `void MarkDirty(bool bMarkDescendents);` — Set completion flags on this and its parents (and optionally its descendents) so that it will be updated again.
- L493 _public prototype_ `void Shrink();` — Minimize data in internal buffers.
- L502 _protected prototype_ `void SetComplete(bool bInIsComplete);` — Setting to complete marks that this directory has been scanned, and all of its subdirectories have scanned as well, so it can be skipped when it or its parent is waited on. Setting back to incomplete can occur when a AssetDataGatherer client wants to rescan the directory.
- L507 _protected prototype_ `bool HasPersistentSettings() const;` — Return whether this ScanDir has direct settings (allow list, deny list, etc) that we need to preserve on it even if has finished scanning.
- L510 _protected prototype_ `FScanDir* FindSubDir(FStringView SubDirBaseName);` — Find the ScanDir subdirectory for the given basename, or return nullptr.
- L511 _protected prototype_ `const FScanDir* FindSubDir(FStringView SubDirBaseName) const;`
- L513 _protected prototype_ `FScanDir& FindOrAddSubDir(FStringView SubDirBaseName);` — Find the ScanDir subdirectory for the given basename, and add it if it does not exist.
- L518 _protected prototype_ `void RemoveSubDir(FStringView SubDirBaseName);` — Find the ScanDir subdirectory for the given basename, and if it exists, Shutdown and remove it from SubDirs, which will eventually delete it.
- L521 _protected prototype_ `int32 FindLowerBoundSubDir(FStringView SubDirBaseName);` — Find the index of the subdir with the given Relative path.
- L524 _protected prototype_ `template <typename CallbackType> void ForEachSubDir(const CallbackType& Callback);` — Call the given lambda void(FScanDir&) on each existing SubDir.
- L530 _protected prototype_ `template <typename CallbackType> void ForEachDescendent(const CallbackType& Callback);` — Call the given lambda void(FScanDir&) on each present-in-memory descedent ScanDir of this. Does not look for directories on disk, only the ones that have already been created in memory. Depth-first-search traversal, called on parents before children.
- L532 _protected member_ `TArray<TRefCountPtr<FScanDir>> SubDirs;` — Sorted
- L533 _protected member_ `TArray<FString> AlreadyScannedFiles;` — Unsorted
- L534 _protected member_ `FMountDir* MountDir = nullptr;`
- L535 _protected member_ `FScanDir* Parent = nullptr;`
- L536 _protected member_ `FString RelPath;`
- L538 _protected member_ `FInherited DirectData;` — Whether each piece of the inherited data has been set directly on this directory
- L539 _protected member_ `bool bHasScanned = false;`
- L540 _protected member_ `bool bScanInFlight = false;`
- L541 _protected member_ `bool bScanInFlightInvalidated = false;`
- L542 _protected member_ `bool bIsComplete = false;`

#### struct `UE::AssetDataGather::Private::FScanDir::FInherited`  
`struct FInherited`  
_L378-394_
- desc: Holder for fields on FScanDir that are inherited from parents
- L380 _public prototype_ `FInherited() = default;`
- L383 _public member_ `bool bIsOnAllowList = false;` — Whether the ScanDir is in the allow list.
- L385 _public member_ `bool bMatchesDenyList = false;` — Whether the ScanDir is under one of the folders on the deny list.
- L387 _public member_ `bool bIgnoreDenyList = false;` — Whether the ScanDir has been set to ignore the deny list.
- L389 _public prototype_ `bool IsMonitored() const;`
- L390 _public prototype_ `bool IsOnDenyList() const;`
- L391 _public prototype_ `bool IsOnAllowList() const;`
- L392 _public prototype_ `bool HasSetting() const;`
- L393 _public prototype_ `FInherited(const FInherited& Parent, const FInherited& Child);`

#### struct `UE::AssetDataGather::Private::FScanDirAndParentData`  
`struct FScanDirAndParentData`  
_L549-553_
- desc: A refcounted pointer to a ScanDir, along with the ParentData found when tracing down from the root path to the ScanDir. Used to return list of directories needing scanning from Update.
- L551 _public member_ `TRefCountPtr<FScanDir> ScanDir;`
- L552 _public member_ `FScanDir::FInherited ParentData;`

#### class `UE::AssetDataGather::Private::FMountDir`  
`class FMountDir`  
_L564-669_
- desc: Gather data about a MountPoint that has been registered with FPackageName The FMountDir holds a FScanTree with information about each directory (that is pruned when not in use). It also holds data that is needed only per MountPoint, such as the packagename. It also holds data per subdirectory that is more performant to hold in a map rather than to require the FScanTrees to be kept. This class is not ThreadSafe; The FAssetDataDiscovery reads/writes its data only while holding TreeLock.
- L567 _public prototype_ `FMountDir(FAssetDataDiscovery& InDiscovery, FStringView LocalAbsPath, FStringView PackagePath);`
- L568 _public prototype_ `~FMountDir();`
- L571 _public prototype_ `FStringView GetLocalAbsPath() const;` — The local path from FPackageName, absolute d:\root\Engine\Content rather relative ../../../Engine/Content.
- L573 _public prototype_ `FStringView GetLongPackageName() const;` — The package path from FPackageName.
- L576 _public prototype_ `FAssetDataDiscovery& GetDiscovery() const;` — Return the FAssetDataDiscovery that owns this FMountDir.
- L579 _public prototype_ `FScanDir* GetControllingDir(FStringView LocalAbsPath, bool bIsDirectory, FScanDir::FInherited& OutParentData, FString& OutRelPath);` — Find the direct parent of InRelPath, or the lowest fallback. See FScanDir::GetControllingDir.
- L582 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Return the memory used by the tree under this MountDir, except that sizeof(*this) is excluded.
- L585 _public prototype_ `bool IsComplete() const;` — Report whether this MountDir is complete: all ScanDirs under it either have scanned or should not scan.
- L588 _public prototype_ `void GetMonitorData(FStringView InLocalAbsPath, FScanDir::FInherited& OutData) const;` — Report the collapsed data for the scandir - allow list, deny list, etc. Returns false data for non child paths.
- L593 _public prototype_ `bool IsMonitored(FStringView InLocalAbsPath) const;` — Return whether the given path is a child path of *this and is allow listed and is not deny listed, which means it will be or has been scanned.
- L598 _public prototype_ `void TrySetDirectoryProperties(FPathExistence& QueryPath, const FSetPathProperties& InProperties, FScanDirAndParentData* OutControllingDir = nullptr, FStringView* OutControllingDirRelPath = nullptr, bool* bOutMadeChanges = nullptr);` — Set values of fields on the given directory for all of the properties existing on InProperties.
- L603 _public prototype_ `void Update(TArray<FScanDirAndParentData>& OutScanRequests);` — Update all incomplete ScanDirs under this MountDir and add any that need to be scanned to OutScanRequests.
- L605 _public prototype_ `FScanDir* GetFirstIncompleteScanDir();`
- L608 _public prototype_ `void SetHasStartedScanning();` — Record a directory under the MountDir has been scanned, used to detect if configuration occurs after scanning.
- L610 _public prototype_ `void Shrink();` — Minimize data in internal buffers.
- L613 _public prototype_ `void AddChildMount(FMountDir* ChildMount);` — Record that the MountDir is rooted at a childpath of this. The childpath will not be scanned by this.
- L615 _public prototype_ `void RemoveChildMount(FMountDir* ChildMount);` — Mark that a childpath MountDir is being deleted and the childpath should be scanned again by this.
- L620 _public prototype_ `void OnDestroyClearChildMounts();` — Remove all childmounts. Does not handle properly updating the MountDir to reown those paths; this is used during destruction all MountDirs.
- L625 _public prototype_ `void SetParentMount(FMountDir* ParentMount);` — Record the backpointer to the parent mountdir that this mountdir's path is a child path of, or null if the parent no longer exists.
- L627 _public prototype_ `FMountDir* GetParentMount() const;` — Return the parent MountDir.
- L629 _public prototype_ `TArray<FMountDir*> GetChildMounts() const;` — Return the MountDirs that have been recorded as ChildMounts.
- L633 _protected prototype_ `void UpdateDenyList();` — Inspect the Discovery's DenyLists and add the ones applicable to this into this MountDir's set of DenyLists.
- L635 _protected prototype_ `void MarkDirty(FStringView MountRelPath);` — Mark that given path needs to be reconsidered by Update.
- L638 _protected prototype_ `void AddChildMountPath(FStringView MountRelPath);` — Add a ChildMountPath, which indicates that another MountPoint owns that path and this Mount should not scan it.
- L640 _protected prototype_ `bool RemoveChildMountPath(FStringView MountRelPath);` — Remove a ChildMountPath, return whether there was a match to be removed.
- L642 _protected prototype_ `bool IsChildMountPath(FStringView MountRelPath) const;` — Report whether the given Path is equal to or a child of an existing ChildMountPath.
- L645 _protected member_ `TArray<FString> ChildMountPaths;` — Child mount paths; these directories should not be scanned by this MountDir.
- L650 _protected member_ `TSet<FString> RelPathsDenyList;` — Set of relative path from the MountDir paths that should not be scanned, because they were requested deny listed by clients or because a childmount owns them.
- L652 _protected member_ `FString LocalAbsPath;` — Absolute path to the root of the MountDir in the local file system.
- L654 _protected member_ `FString LongPackageName;` — LongPackageName that was assigned to the MountDir in FPackageName.
- L659 _protected member_ `TRefCountPtr<FScanDir> Root;` — ScanDir for the root directory of this MountDir; child paths to scan will be created (and destroyed after use) as children of the ScanDir (with the exception of childmounts).
- L661 _protected member_ `FAssetDataDiscovery& Discovery;` — Backpointer to the Discovery that owns this MountDir.
- L666 _protected member_ `FMountDir* ParentMount = nullptr;` — If this is a nested MountDir (a nested path was registered with FPackageName) ParentMount is a pointer to the FMountDir that corresponds to the registered parent directory.
- L668 _protected member_ `bool bHasStartedScanning = false;` — Records whether any directory at or under the MountDir's root has been scanned.

#### class `UE::AssetDataGather::Private::FAssetDataDiscovery`  
`class FAssetDataDiscovery : public FRunnable`  
_L673-940_
- inherits: `FRunnable`
- desc: Subsystem that discovers the files that FAssetDataGatherer should process.
- L676 _public prototype_ `FAssetDataDiscovery();`
- L677 _public prototype_ `virtual ~FAssetDataDiscovery();`
- L683 _public prototype_ `void StartAsync();` — Start the async thread, if this Gatherer was created async. Does nothing if not async or already started.
- L686 _public prototype_ `virtual bool Init() override;` — FRunnable implementation
- L687 _public prototype_ `virtual uint32 Run() override;`
- L688 _public prototype_ `virtual void Stop() override;`
- L689 _public prototype_ `virtual void Exit() override;`
- L692 _public prototype_ `void EnsureCompletion();` — Signals to end the thread and waits for it to close before returning
- L694 _public prototype_ `bool IsSynchronous() const;`
- L698 _public prototype_ `void GetAndTrimSearchResults(bool& bOutIsComplete, TArray<FString>& OutDiscoveredPaths, FFilesToSearch& OutFilesToSearch, int32& OutNumPathsToSearch);` — Gets search results from the file discovery.
- L701 _public prototype_ `void GetDiagnostics(float& OutCumulativeDiscoveryTime, int32& OutNumCachedDirectories, int32& OutNumUncachedDirectories);` — Get diagnostics for telemetry or logging.
- L704 _public prototype_ `void WaitForIdle(double EndTimeSeconds);` — Wait (joining in on the tick) until all currently monitored paths have been scanned.
- L705 _public prototype_ `bool IsIdle() const;`
- L706 _public prototype_ `void OnInitialSearchCompleted();`
- L707 _public prototype_ `void OnAdditionalMountSearchCompleted();`
- L710 _public prototype_ `void SetPropertiesAndWait(TArrayView<FPathExistence> QueryPaths, bool bAddToAllowList, bool bForceRescan, bool bIgnoreDenyListScanFilters);` — Optionally set some scan properties for the given paths and then wait for their scans to finish.
- L713 _public prototype_ `bool IsOnAllowList(FStringView LocalAbsPath) const;` — Return whether the given path is allowed due to e.g. TrySetDirectoryProperties with IsOnAllowList.
- L715 _public prototype_ `bool IsOnDenyList(FStringView LocalAbsPath) const;` — Return whether the given path matches the deny list and has not been marked IgnoreDenyList.
- L717 _public prototype_ `bool IsMonitored(FStringView LocalAbsPath) const;` — Return whether the path should or has been scanned because it is on the AllowList and not on the DenyList.
- L719 _public prototype_ `bool IsCacheWriteEnabled() const;` — Return whether the discovery cache can be written.
- L721 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Return the memory used by *this. sizeof(*this) is not included.
- L728 _public prototype_ `void AddMountPoint(const FString& LocalAbsPath, FStringView LongPackageName, bool& bOutAlreadyExisted);` — Register the given LocalAbsPath/LongPackageName pair that came from FPackageName's list of mount points as a mountpoint to track. Will not be scanned until allow listed.
- L730 _public prototype_ `void RemoveMountPoint(const FString& LocalAbsPath);` — Remove the mountpoint because FPackageName has removed it.
- L732 _public prototype_ `void PrioritizeSearchPath(const FString& LocalAbsPath, EPriority Priority);` — Raise the priority until completion of scans of the given path and its subdirs.
- L734 _public prototype_ `void TrySetDirectoryProperties(const FString& LocalAbsPath, const FSetPathProperties& Properties, bool bConfirmedExists);` — Set properties on the directory, called when files are requested to be on an allow/deny list or rescanned.
- L737 _public prototype_ `void OnDirectoryCreated(FStringView LocalAbsPath);` — Event called from the directory watcher when a directory is created. It will be scanned if IsMonitored.
- L739 _public prototype_ `void OnFilesCreated(TConstArrayView<FString> LocalAbsPaths);` — Event called from the directory watcher when files are created. Each will be reported if IsMonitored.
- L743 _private prototype_ `FMountDir* FindContainingMountPoint(FStringView LocalAbsPath);` — Find the MountDir with a root that contains LocalAbsPath, finding the lowest child if there are multiple.
- L744 _private prototype_ `const FMountDir* FindContainingMountPoint(FStringView LocalAbsPath) const;`
- L746 _private prototype_ `FMountDir* FindMountPoint(FStringView LocalAbsPath);` — Find the mountpoint with the given root.
- L751 _private prototype_ `FMountDir& FindOrAddMountPoint(FStringView LocalAbsPath, FStringView LongPackageName);` — Find the mountpoint with the given root, creating it if it does not already exist. Handle registration of child mountdirs.
- L753 _private prototype_ `int32 FindLowerBoundMountPoint(FStringView LocalAbsPath) const;` — Execute the search on the sorted-by-path mountdirs, returning the first mountdir with root >= the given path.
- L756 _private prototype_ `void TickInternal(bool bTickAll);` — Run the tick, either called from the async Run or called on thread from a thread executing a synchronous wait.
- L758 _private prototype_ `void UpdateAll(TArray<FScanDirAndParentData>& OutScanRequests);` — Update all incomplete ScanDirs under all MountDirs and add any that need to be scanned to OutScanRequests.
- L760 _private prototype_ `void SetIsIdle(bool bInIdle);` — Mark whether this discoverer has finished and is idle. Update properties dependent upon the idle state.
- L761 _private prototype_ `void SetIsIdle(bool bInIdle, double& TickStartTime);`
- L764 _private prototype_ `void AddDiscovered(FStringView DirAbsPath, FStringView DirPackagePath, TConstArrayView<FDiscoveredPathData> SubDirs, TConstArrayView<FDiscoveredPathData> Files);` — Store the given discovered files and directories in the results.
- L767 _private prototype_ `void AddDiscoveredFile(FDiscoveredPathData&& File);` — Store the given specially reported single file in the results.
- L774 _private prototype_ `static EGatherableFileType GetFileType(FStringView FilePath);` — For a given file path, determine the type it should be gathered as. For Verse files, this does _not_ verify the file matches Verse naming conventions, and you probably want to call `DoesPathContainInvalidCharacters` instead.
- L777 _private prototype_ `void OnFileCreated(const FString& LocalPaths);` — Handle the actions necessary for a single created file.
- L779 _private prototype_ `void TrySetDirectoryPropertiesInternal(FPathExistence& QueryPath, const FSetPathProperties& Properties);` — Helper for TrySetDirectoryProperties, called from within the critical section.
- L782 _private prototype_ `void AddMountPointInternal(const FString& LocalAbsPath, FStringView LongPackageName, bool& bOutAlreadyExisted);` — Add the given path as a MountPoint and update child registrations.
- L784 _private prototype_ `void RemoveMountPointInternal(const FString& LocalAbsPath);` — Remove the given path as a MountPoint and update child registrations.
- L787 _private prototype_ `void Shrink();` — Minimize memory usage in the buffers used during gathering.
- L802 _private member_ `mutable FGathererCriticalSection TreeLock;` — Protect access to data in the ScanDir tree which can be read/write from the tick or from SetProperties. To prevent DeadLocks, TreeLock must not be entered while holding ResultsLock.
- L807 _private member_ `mutable FThreadOwnerSection TickOwner;` — Prevent simultaneous ticks from two different threads and protect access to Tick-specific data. Can only be queried or taken while holding TreeLock, but can continue to be held after exiting TreeLock.
- L812 _private member_ `mutable FGathererCriticalSection ResultsLock;` — Protect access to the data written from tick and read/written from GetAndTrimSearchResults. ResultsLock can be entered while holding TreeLock.
- L818 _private member_ `TArray<FString> LongPackageNamesDenyList;` — Deny list of full absolute paths. Child paths will not be scanned unless requested to ignore DenyLists.
- L820 _private member_ `TArray<FString> MountRelativePathsDenyList;` — DenyList of relative paths in each mount. Child paths will not be scanned unless requested to ignore DenyLists.
- L822 _private member_ `FRunnableThread* Thread;` — Thread to run the discovery FRunnable on. Read-only while threading is possible.
- L827 _private member_ `bool bAsyncEnabled;` — True if async discovery is enabled, false if e.g. singlethreaded or disabled by commandline. Even when enabled, discovery is still synchronous until StartAsync is called.
- L836 _private member_ `std::atomic<bool> bIsIdle;` — Whether this Discoverer has finished all work (may be still present in the results.) Readable anywhere. Writable only within TreeLock.
- L841 _private member_ `std::atomic<bool> bPriorityDirty;` — Set to true after editing PriorityScanDirs to inform a running Tick that it should abort its current batch to reduce latency in handling the new priorities.
- L843 _private member_ `std::atomic<uint32> IsStopped;` — > 0 if we've been asked to abort work in progress at the next opportunity.
- L845 _private member_ `mutable std::atomic<uint32> IsPaused;` — > 0 if we've been asked to pause the worker thread so a synchronous function can take over the tick.
- L850 _private member_ `FThreadSafeCounter NumDirectoriesToScan;` — Number of directories that have been discovered and IsMonitored but have not yet been scanned. Used for progress tracking.
- L852 _private member_ `FEventRef PriorityDataUpdated{ EEventMode::ManualReset };` — Triggered after scanning PriorityDirs to inform threads waiting on a PriorityDir to recheck conditions.
- L857 _private member_ `TArray<FString> DiscoveredDirectories;` — Directories found in the scan; may be empty.
- L867 _private member_ `TArray<FDirectoryResult> DiscoveredFiles;`
- L868 _private member_ `TArray<FGatheredPathData> DiscoveredSingleFiles;`
- L870 _private member_ `double CurrentDiscoveryTime = 0.;` — Time spent in TickInternal since the last time cook was idle. Used for logging.
- L872 _private member_ `int32 NumDiscoveredFiles = 0;` — Number of files discovered during scanning since start or resumed from idle. Used for logging.
- L874 _private member_ `int32 CumulativeDiscoveredFiles = 0;` — Cumulative total of NumDiscoveredFiles across all non-idle periods.
- L876 _private member_ `float CumulativeDiscoveryTime = 0.f;` — Cumulative total of time spent in all non-idle periods.
- L878 _private member_ `int32 NumCachedDirectories = 0;` — The total number of directories in the search results that were read from the cache.
- L880 _private member_ `int32 NumUncachedDirectories = 0;` — The total number of directories in the search results that were not in the cache and were read by iterating the disk.
- L889 _private member_ `TArray<TUniquePtr<FMountDir>> MountDirs;` — Sorted list of MountDirs, sorted by FPackagePath::Less on the absolute paths. Each MountDir contains a ScanDir tree and other data that configures the scanning within that MountPoint. Read/writable only with TreeLock, both the list and all data owned by each MountDir.
- L903 _private member_ `TArray<FPriorityScanDirData> PriorityScanDirs;`
- L925 _private member_ `TArray<FDirToScanData> DirToScanDatas;`
- L934 _private member_ `TArray<FDirToScanBuffer> DirToScanBuffers;`
- L936 _private member_ `FAssetDataDiscoveryCache Cache;`

#### struct `UE::AssetDataGather::Private::FAssetDataDiscovery::FScopedPause`  
`struct FScopedPause`  
_L790-795_
- desc: Scoped guard for pausing the asynchronous tick.
- L792 _public prototype_ `FScopedPause(const FAssetDataDiscovery& InOwner);`
- L793 _public prototype_ `~FScopedPause();`
- L794 _public member_ `const FAssetDataDiscovery& Owner;`

#### struct `UE::AssetDataGather::Private::FAssetDataDiscovery::FDirectoryResult`  
`struct FDirectoryResult`  
_L860-866_
- desc: Files found found in the scan.
- L862 _public prototype_ `FDirectoryResult(FStringView InDirAbsPath, TConstArrayView<FDiscoveredPathData> InFiles);`
- L863 _public member_ `FString DirAbsPath;`
- L864 _public member_ `TArray<FGatheredPathData> Files;`
- L865 _public prototype_ `SIZE_T GetAllocatedSize() const;`

#### struct `UE::AssetDataGather::Private::FAssetDataDiscovery::FPriorityScanDirData`  
`struct FPriorityScanDirData`  
_L892-902_
- desc: A ScanDir and referencecount for directories that have been prioritized by ScanPathsSynchronous.
- L894 _public member_ `TRefCountPtr<FScanDir> ScanDir;`
- L895 _public member_ `FScanDir::FInherited ParentData;`
- L896 _public member_ `int32 RequestCount = 0;`
- L901 _public member_ `bool bReleaseWhenComplete = false;` — Fire and forget prioritization increments RequestCount without ever decrementing it, and sets bReleaseWhenComplete to have it be decremented by TickInternal.

#### struct `UE::AssetDataGather::Private::FAssetDataDiscovery::FDirToScanData`  
`struct FDirToScanData`  
_L908-924_
- desc: Scratch space to store scan results during the tick to avoid allocations.
- L910 _public member_ `TRefCountPtr<FScanDir> ScanDir;`
- L911 _public member_ `FScanDir::FInherited ParentData;`
- L914 _public member_ `TStringBuilder<0> DirLocalAbsPath;` — This type is used in a TArray, and TArray assumes elements can be memmoved. TStringBuilder<N> cannot be memmoved, so use TStringBuilder<0> without a buffer.
- L915 _public member_ `TStringBuilder<0> DirLongPackageName;`
- L916 _public member_ `TArray<FDiscoveredPathData> IteratedSubDirs;`
- L917 _public member_ `TArray<FDiscoveredPathData> IteratedFiles;`
- L918 _public member_ `int32 NumIteratedDirs = 0;`
- L919 _public member_ `int32 NumIteratedFiles = 0;`
- L920 _public member_ `bool bScanned = false;`
- L922 _public prototype_ `void Reset();`
- L923 _public prototype_ `SIZE_T GetAllocatedSize() const;`

#### struct `UE::AssetDataGather::Private::FAssetDataDiscovery::FDirToScanBuffer`  
`struct FDirToScanBuffer`  
_L928-933_
- desc: Scratch space used per helper thread in the forloop to avoid allocations.
- L930 _public member_ `bool bAbort = false;`
- L932 _public prototype_ `void Reset();`

#### enum `UE::AssetDataGather::Private::EEditorGameScanMode`  
`enum class EEditorGameScanMode : uint8`  
_L945-950_
- desc: How the editor, when run with -game or (under more limited circumstances) -server, performs its asset registry scan
- L947 _public enumerator_ `Sync`
- L948 _public enumerator_ `Async`
- L949 _public enumerator_ `None`

#### struct `UE::AssetDataGather::Private::FGatherSettings`  
`struct FGatherSettings`  
_L956-1031_
- desc: Settings about whether to use cache data for the AssetDataGatherer; these settings are shared by FPreloader, FAssetDataGatherer, and FAssetDataDiscovery.
- L959 _public member_ `static constexpr int32 ExpectedMaxBatchSize = 100;`
- L960 _public member_ `static constexpr int32 MinSecondsToElapseBeforeCacheWrite = 300;`
- L961 _public member_ `static constexpr int32 MinAssetReadsBeforeCacheWrite = 100000;`
- L962 _public member_ `static constexpr int32 CacheShardAssetCount = 250000;`
- L963 _public member_ `static constexpr uint32 CacheSerializationMagic = 0xC2832E98;` — Versioning and integrity checking
- L964 _public member_ `static constexpr uint64 CurrentVersion = FAssetRegistryVersion::LatestVersion | (uint64(CacheSerializationMagic) << 32);`
- L965 _public member_ `static inline const FTimespan CachePruneAge = FTimespan(7, 0, 0, 0);`
- L968 _public member_ `static constexpr float PollDiscoveryPeriodSeconds = .005f;` — How long we wait on the gatherer thread between asking the discovery thread for no results.
- L975 _public member_ `static inline int32 GARDiscoverThreads = 15;` — The maximum number of threads used in the ParallelFor in FAssetDataDiscovery::TickInternal. Higher values cause more time spent waking up workers. Lower values cause more time spent running the DirectoryEnumeration on each thread. Current value was chosen based on experiments on an SSD drive with a warm disk cache.
- L980 _public member_ `static inline int32 GARDiscoverMinBatchSize = 1;` — Minimum batch sized used used in the ParallelFor in FAssetDataDiscovery::TickInternal. In theory higher minimum values could reduce the cost of waking up workers, but in practice it does not have a significant effect.
- L987 _public member_ `static inline int32 GARGatherThreads = 0;` — The maximum number of threads used in the ParallelFor around ReadAssetFile in FAssetDataGatherer::TickInternal. Very high numbers of threads does not reduce wall time of the gather because the threads become IO limited. Capping the number of threads allows those threads to be used in other async operations in Engine startup. A value of <= 0 will let the system decide how many threads to use.
- L994 _public member_ `static inline int32 GARGatherCacheParallelism = 16;` — The maximum number of the gatherer's cache files that can be loaded in parallel in LoadCacheFiles. The amount of memory used when reading the cache rises proportional to this value. Other than the memory cost, it should be set as high as possible to load the cache faster.
- L996 _public prototype_ `void Initialize();`
- L997 _public prototype_ `bool IsInitialized() const;`
- L998 _public prototype_ `bool IsAsyncEnabled() const;`
- L999 _public prototype_ `bool IsGatherCacheReadEnabled() const;`
- L1000 _public prototype_ `bool IsGatherCacheWriteEnabled() const;`
- L1001 _public prototype_ `bool IsDiscoveryCacheReadEnabled() const;`
- L1002 _public prototype_ `EFeatureEnabled IsDiscoveryCacheWriteEnabled() const;`
- L1003 _public prototype_ `bool IsDiscoveryCacheInvalidateEnabled() const;`
- L1004 _public prototype_ `bool IsPreloadGatherCache() const;`
- L1005 _public prototype_ `bool IsPreloadDiscoveryCache() const;`
- L1006 _public prototype_ `bool IsGatherDependsData() const;`
- L1007 _public prototype_ `bool IsForceDependsGathering() const;`
- L1008 _public prototype_ `EEditorGameScanMode GetEditorGameScanMode() const;`
- L1009 _public prototype_ `FString GetCacheDirectory() const;`
- L1010 _public prototype_ `const FString& GetCacheBaseFilename() const;`
- L1011 _public prototype_ `const FString& GetLegacyCacheBaseFilename() const;`
- L1012 _public prototype_ `const FString& GetAssetRegistryCacheRootFolder() const;`
- L1013 _public prototype_ `TArray<FString> FindShardedCacheFiles() const;`
- L1014 _public prototype_ `TArray<FString> FindLegacyShardedCacheFiles() const;`
- L1017 _private member_ `FString CacheBaseFilename;`
- L1018 _private member_ `FString LegacyCacheBaseFilename;`
- L1019 _private member_ `FString AssetRegistryCacheRootFolder;`
- L1020 _private member_ `bool bForceDependsGathering = false;`
- L1021 _private member_ `bool bGatherDependsData = false;`
- L1022 _private member_ `bool bGatherCacheReadEnabled = false;`
- L1023 _private member_ `bool bGatherCacheWriteEnabled = false;`
- L1024 _private member_ `bool bDiscoveryCacheReadEnabled = false;`
- L1025 _private member_ `EFeatureEnabled DiscoveryCacheWriteEnabled = EFeatureEnabled::Never;`
- L1026 _private member_ `bool bDiscoveryCacheInvalidateEnabled = false;`
- L1027 _private member_ `bool bPreloadGatherCache = false;`
- L1028 _private member_ `bool bAsyncEnabled = false;`
- L1029 _private member_ `bool bInitialized = false;`
- L1030 _private member_ `EEditorGameScanMode EditorGameScanMode = EEditorGameScanMode::None;`
- L1048 _function_ `inline bool FGatherSettings::IsInitialized() const`
- L1053 _function_ `inline bool FGatherSettings::IsAsyncEnabled() const`
- L1058 _function_ `inline bool FGatherSettings::IsGatherCacheReadEnabled() const`
- L1063 _function_ `inline bool FGatherSettings::IsGatherCacheWriteEnabled() const`
- L1068 _function_ `inline bool FGatherSettings::IsDiscoveryCacheReadEnabled() const`
- L1073 _function_ `inline EFeatureEnabled FGatherSettings::IsDiscoveryCacheWriteEnabled() const`
- L1078 _function_ `inline bool FGatherSettings::IsDiscoveryCacheInvalidateEnabled() const`
- L1083 _function_ `inline bool FGatherSettings::IsPreloadGatherCache() const`
- L1088 _function_ `inline bool FGatherSettings::IsPreloadDiscoveryCache() const`
- L1093 _function_ `inline bool FGatherSettings::IsGatherDependsData() const`
- L1098 _function_ `inline bool FGatherSettings::IsForceDependsGathering() const`
- L1103 _function_ `inline EEditorGameScanMode FGatherSettings::GetEditorGameScanMode() const`
- L1108 _function_ `inline FString FGatherSettings::GetCacheDirectory() const`
- L1113 _function_ `inline const FString& FGatherSettings::GetCacheBaseFilename() const`
- L1118 _function_ `inline const FString& FGatherSettings::GetLegacyCacheBaseFilename() const`
- L1123 _function_ `inline const FString& FGatherSettings::GetAssetRegistryCacheRootFolder() const`

#### enum `UE::AssetDataGather::Private::ECacheCleanupContext`  
`enum class ECacheCleanupContext`  
_L1034-1038_
- L1036 _public enumerator_ `PreLoad`
- L1037 _public enumerator_ `PostWrite`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace AssetDataGather` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::AssetDataGather`)
- L75 _prototype_ `bool IsVerseFile(const EGatherableFileType FileType);` (scope `UE::AssetDataGather::Private`)
- L1032 _externvar_ `extern FGatherSettings GGatherSettings;` (scope `UE::AssetDataGather::Private`)
- L1039 _prototype_ `void CleanupOrphanedCacheFiles(const FString& CacheBaseFilename, ECacheCleanupContext Context);` (scope `UE::AssetDataGather::Private`)
- L1042 _prototype_ `bool DoesPathContainInvalidCharacters(const EGatherableFileType FileType, FStringView FilePath);` (scope `UE::AssetDataGather::Private`) — Checks if the given path, for a given file type, matches the naming conventions for said type.

### `Source/Runtime/AssetRegistry/Private/AssetRegistry.h` (Private)


#### class `UAssetRegistryImpl`  
`class UAssetRegistryImpl : public UObject, public IAssetRegistry`  
_L24-489_
- reflection: `UCLASS(transient)`
- inherits: `UObject,IAssetRegistry`
- L28 _public prototype_ `UAssetRegistryImpl(const FObjectInitializer& ObjectInitializer);`
- L29 _public prototype_ `UAssetRegistryImpl(FVTableHelper& Helper);`
- L30 _public prototype_ `virtual ~UAssetRegistryImpl();`
- L31 _public prototype_ `virtual void FinishDestroy() override;`
- L34 _public prototype_ `static UAssetRegistryImpl& Get();` — Gets the asset registry singleton for asset registry module use
- L37 _public prototype_ `virtual bool HasAssets(const FName PackagePath, const bool bRecursive = false) const override;` — IAssetRegistry implementation
- L38 _public prototype_ `virtual bool GetAssetsByPackageName(FName PackageName, TArray<FAssetData>& OutAssetData, bool bIncludeOnlyOnDiskAssets = false, bool bSkipARFilteredAssets=true) const override;`
- L39 _public prototype_ `virtual bool GetAssetsByPath(FName PackagePath, TArray<FAssetData>& OutAssetData, bool bRecursive = false, bool bIncludeOnlyOnDiskAssets = false) const override;`
- L40 _public prototype_ `virtual bool GetAssetsByPaths(TArray<FName> PackagePath, TArray<FAssetData>& OutAssetData, bool bRecursive = false, bool bIncludeOnlyOnDiskAssets = false) const override;`
- L41 _public prototype_ `virtual bool GetAssetsByClass(FTopLevelAssetPath ClassPathName, TArray<FAssetData>& OutAssetData, bool bSearchSubClasses = false) const override;`
- L42 _public prototype_ `virtual bool GetAssetsByTags(const TArray<FName>& AssetTags, TArray<FAssetData>& OutAssetData) const override;`
- L43 _public prototype_ `virtual bool GetAssetsByTagValues(const TMultiMap<FName, FString>& AssetTagsAndValues, TArray<FAssetData>& OutAssetData) const override;`
- L44 _public prototype_ `virtual bool GetAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets = true) const override;`
- L45 _public prototype_ `virtual bool GetAssets(const FARCompiledFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets = true) const override;`
- L46 _public prototype_ `virtual bool GetInMemoryAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets=true) const override;`
- L47 _public prototype_ `virtual bool GetInMemoryAssets(const FARCompiledFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets=true) const override;`
- L48 _public prototype_ `virtual bool EnumerateAssets(const FARFilter& Filter, TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const override;`
- L50 _public prototype_ `virtual bool EnumerateAssets(const FARCompiledFilter& Filter, TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const override;`
- L53 _public prototype_ `virtual FAssetData GetAssetByObjectPath( const FName ObjectPath, bool bIncludeOnlyOnDiskAssets = false ) const override;` — `UE_DEPRECATED(5.1, "Asset path FNames have been deprecated, use FSoftObjectPath instead.")`
- L54 _public prototype_ `virtual FAssetData GetAssetByObjectPath(const FSoftObjectPath& ObjectPath, bool bIncludeOnlyOnDiskAssets = false, bool bSkipARFilteredAssets = true) const override;`
- L55 _public prototype_ `virtual UE::AssetRegistry::EExists TryGetAssetByObjectPath(const FSoftObjectPath& ObjectPath, FAssetData& OutAssetData) const override;`
- L56 _public prototype_ `virtual UE::AssetRegistry::EExists TryGetAssetPackageData(const FName PackageName, FAssetPackageData& OutAssetPackageData, bool bFailIfLockHeld = false) const override;`
- L57 _public prototype_ `virtual UE::AssetRegistry::EExists TryGetAssetPackageData(const FName PackageName, FAssetPackageData& OutAssetPackageData, FName& OutCorrectCasePackageName, bool bFailIfLockHeld = false) const override;`
- L58 _public prototype_ `virtual bool GetAllAssets(TArray<FAssetData>& OutAssetData, bool bIncludeOnlyOnDiskAssets = false) const override;`
- L59 _public prototype_ `virtual bool EnumerateAllAssets(TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const override;`
- L61 _public prototype_ `virtual void GetPackagesByName(FStringView PackageName, TArray<FName>& OutPackageNames) const override;`
- L62 _public prototype_ `virtual FName GetFirstPackageByName(FStringView PackageName) const override;`
- L63 _public prototype_ `virtual bool GetDependencies(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const override;`
- L64 _public prototype_ `virtual bool GetDependencies(const FAssetIdentifier& AssetIdentifier, TArray<FAssetDependency>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const override;`
- L65 _public prototype_ `virtual bool GetDependencies(FName PackageName, TArray<FName>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::Package, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const override;`
- L66 _public prototype_ `virtual bool ContainsDependency(FName PackageName, FName QueryDependencyName, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::Package, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const override;`
- L67 _public prototype_ `virtual bool GetReferencers(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const override;`
- L68 _public prototype_ `virtual bool GetReferencers(const FAssetIdentifier& AssetIdentifier, TArray<FAssetDependency>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const override;`
- L69 _public prototype_ `virtual bool GetReferencers(FName PackageName, TArray<FName>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::Package, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const override;`
- L70 _public prototype_ `virtual TOptional<FAssetPackageData> GetAssetPackageDataCopy(FName PackageName) const override;`
- L71 _public prototype_ `virtual TArray<TOptional<FAssetPackageData>> GetAssetPackageDatasCopy(TArrayView<FName> PackageNames) const override;`
- L72 _public prototype_ `virtual void EnumerateAllPackages(TFunctionRef<void(FName PackageName, const FAssetPackageData& PackageData)> Callback, UE::AssetRegistry::EEnumeratePackagesFlags InEnumerateFlags) const override;`
- L73 _public prototype_ `virtual bool DoesPackageExistOnDisk(FName PackageName, FString* OutCorrectCasePackageName = nullptr, FString* OutExtension = nullptr) const override;`
- L74 _public prototype_ `virtual FSoftObjectPath GetRedirectedObjectPath(const FSoftObjectPath& ObjectPath) override;`
- L75 _public prototype_ `virtual bool GetAncestorClassNames(FTopLevelAssetPath ClassName, TArray<FTopLevelAssetPath>& OutAncestorClassNames) const override;`
- L76 _public prototype_ `virtual void GetDerivedClassNames(const TArray<FTopLevelAssetPath>& ClassNames, const TSet<FTopLevelAssetPath>& ExcludedClassNames, TSet<FTopLevelAssetPath>& OutDerivedClassNames) const override;`
- L77 _public prototype_ `virtual void GetAllCachedPaths(TArray<FString>& OutPathList) const override;`
- L78 _public prototype_ `virtual void EnumerateAllCachedPaths(TFunctionRef<bool(FString)> Callback) const override;`
- L79 _public prototype_ `virtual void EnumerateAllCachedPaths(TFunctionRef<bool(FName)> Callback) const override;`
- L80 _public prototype_ `virtual void GetSubPaths(const FString& InBasePath, TArray<FString>& OutPathList, bool bInRecurse) const override;`
- L81 _public prototype_ `virtual void GetSubPaths(const FName& InBasePath, TArray<FName>& OutPathList, bool bInRecurse) const override;`
- L82 _public prototype_ `virtual void EnumerateSubPaths(const FString& InBasePath, TFunctionRef<bool(FString)> Callback, bool bInRecurse) const override;`
- L83 _public prototype_ `virtual void EnumerateSubPaths(const FName InBasePath, TFunctionRef<bool(FName)> Callback, bool bInRecurse) const override;`
- L84 _public prototype_ `virtual void RunAssetsThroughFilter (TArray<FAssetData>& AssetDataList, const FARFilter& Filter) const override;`
- L85 _public prototype_ `virtual void UseFilterToExcludeAssets(TArray<FAssetData>& AssetDataList, const FARFilter& Filter) const override;`
- L86 _public prototype_ `virtual void UseFilterToExcludeAssets(TArray<FAssetData>& AssetDataList, const FARCompiledFilter& CompiledFilter) const override;`
- L87 _public prototype_ `virtual bool IsAssetIncludedByFilter(const FAssetData& AssetData, const FARCompiledFilter& Filter) const override;`
- L88 _public prototype_ `virtual bool IsAssetExcludedByFilter(const FAssetData& AssetData, const FARCompiledFilter& Filter) const override;`
- L89 _public prototype_ `virtual void CompileFilter(const FARFilter& InFilter, FARCompiledFilter& OutCompiledFilter) const override;`
- L90 _public prototype_ `virtual void SetTemporaryCachingMode(bool bEnable) override;`
- L91 _public prototype_ `virtual void SetTemporaryCachingModeInvalidated() override;`
- L92 _public prototype_ `virtual bool GetTemporaryCachingMode() const override;`
- L93 _public prototype_ `virtual EAssetAvailability::Type GetAssetAvailability(const FAssetData& AssetData) const override;`
- L94 _public prototype_ `virtual float GetAssetAvailabilityProgress(const FAssetData& AssetData, EAssetAvailabilityProgressReportingType::Type ReportType) const override;`
- L95 _public prototype_ `virtual bool GetAssetAvailabilityProgressTypeSupported(EAssetAvailabilityProgressReportingType::Type ReportType) const override;`
- L96 _public prototype_ `virtual void PrioritizeAssetInstall(const FAssetData& AssetData) const override;`
- L97 _public prototype_ `virtual bool HasVerseFiles(FName PackagePath, bool bRecursive = false) const override;`
- L98 _public prototype_ `virtual bool GetVerseFilesByPath(FName PackagePath, TArray<FName>& OutFilePaths, bool bRecursive = false) const override;`
- L99 _public prototype_ `virtual bool AddPath(const FString& PathToAdd) override;`
- L100 _public prototype_ `virtual bool RemovePath(const FString& PathToRemove) override;`
- L101 _public prototype_ `virtual bool PathExists(const FString& PathToTest) const override;`
- L102 _public prototype_ `virtual bool PathExists(const FName PathToTest) const override;`
- L103 _public prototype_ `virtual void SearchAllAssets(bool bSynchronousSearch) override;`
- L104 _public prototype_ `virtual bool IsSearchAllAssets() const override;`
- L105 _public prototype_ `virtual bool IsSearchAsync() const override;`
- L106 _public prototype_ `virtual void WaitForCompletion() override;`
- L107 _public prototype_ `virtual void WaitForPremadeAssetRegistry() override;`
- L108 _public prototype_ `virtual void ClearGathererCache() override;`
- L109 _public prototype_ `virtual void WaitForPackage(const FString& PackageName) override;`
- L110 _public prototype_ `virtual void ScanSynchronous(const TArray<FString>& InPaths, const TArray<FString>& InFilePaths, UE::AssetRegistry::EScanFlags InScanFlags = UE::AssetRegistry::EScanFlags::None) override;`
- L111 _public prototype_ `virtual void ScanPathsSynchronous(const TArray<FString>& InPaths, bool bForceRescan = false, bool bIgnoreDenyListScanFilters = false) override;`
- L112 _public prototype_ `virtual void ScanFilesSynchronous(const TArray<FString>& InFilePaths, bool bForceRescan = false) override;`
- L113 _public prototype_ `virtual void PrioritizeSearchPath(const FString& PathToPrioritize) override;`
- L114 _public prototype_ `virtual void ScanModifiedAssetFiles(const TArray<FString>& InFilePaths) override;`
- L115 _public prototype_ `virtual void ScanModifiedAssetFiles(const TArray<FString>& InFilePaths, UE::AssetRegistry::EScanFlags ScanFlags) override;`
- L116 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L117 _public prototype_ `virtual void AppendState(const FAssetRegistryState& InState, UE::AssetRegistry::EAppendMode AppendMode = UE::AssetRegistry::EAppendMode::Append) override;`
- L119 _public prototype_ `virtual bool ActiveMountsIsEnabled() override;`
- L120 _public prototype_ `virtual void ActiveMountsInitialize() override;`
- L121 _public prototype_ `virtual bool ActiveMountsRegisterAndLoadFilePathSynchronous(FStringView StateFilePath) override;`
- L122 _public prototype_ `virtual void ActiveMountsRegisterAndLoadFilePathAsync(FStringView StateFilePath, TFunction<void(bool bSucceeded)> OnComplete = TFunction<void(bool bSucceeded)>(), UE::Tasks::ETaskPriority TaskPriority = UE::Tasks::ETaskPriority::Default) override;`
- L125 _public prototype_ `virtual void ActiveMountsLoadAsync(TConstArrayView<FStringView> MountPointLongPackageNames, TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) override;`
- L127 _public prototype_ `virtual void ActiveMountsReloadAllAsync( TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) override;`
- L129 _public prototype_ `virtual void ActiveMountsUnloadAsync(TConstArrayView<FStringView> MountPointLongPackageNames, TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) override;`
- L131 _public prototype_ `virtual void ActiveMountsUnloadAllUnmountedAsync( TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) override;`
- L133 _public prototype_ `virtual bool ActiveMountsIsLoaded(FStringView MountPointLongPackageName) override;`
- L134 _public prototype_ `virtual bool ActiveMountsIsInProgress() override;`
- L135 _public prototype_ `virtual void ActiveMountsReportWhenIdle(TFunction<void()> OnIdle) override;`
- L136 _public prototype_ `virtual SIZE_T GetAllocatedSize(bool bLogDetailed = false) const override;`
- L137 _public prototype_ `virtual void LoadPackageRegistryData(FArchive& Ar, FLoadPackageRegistryData& InOutData) const override;`
- L138 _public prototype_ `virtual void LoadPackageRegistryData(const FString& PackageFilename, FLoadPackageRegistryData& InOutData) const override;`
- L139 _public prototype_ `virtual void InitializeTemporaryAssetRegistryState(FAssetRegistryState& OutState, const FAssetRegistrySerializationOptions& Options, bool bRefreshExisting = false, const TSet<FName>& RequiredPackages = TSet<FName>(), const TSet<FName>& RemovePackages = TSet<FName>()) const override;`
- L143 _public prototype_ `virtual void DumpState(const TArray<FString>& Arguments, TArray<FString>& OutPages, int32 LinesPerPage = 1) const override;`
- L145 _public prototype_ `virtual TSet<FName> GetCachedEmptyPackagesCopy() const override;`
- L146 _public prototype_ `virtual bool ContainsTag(FName TagName) const override;`
- L147 _public prototype_ `virtual void InitializeSerializationOptions(FAssetRegistrySerializationOptions& Options, const ITargetPlatform* TargetPlatform = nullptr, UE::AssetRegistry::ESerializationTarget Target = UE::AssetRegistry::ESerializationTarget::ForGame) const override;`
- L149 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FFilesBlockedEvent, FFilesBlockedEvent);`
- L150 _public prototype_ `virtual FFilesBlockedEvent& OnFilesBlocked() override;`
- L152 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FPathsEvent, FPathsEvent);`
- L153 _public prototype_ `virtual FPathsEvent& OnPathsAdded() override;`
- L154 _public prototype_ `virtual FPathsEvent& OnPathsRemoved() override;`
- L156 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FPathAddedEvent, FPathAddedEvent);`
- L157 _public prototype_ `virtual FPathAddedEvent& OnPathAdded() override;`
- L159 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FPathRemovedEvent, FPathRemovedEvent);`
- L160 _public prototype_ `virtual FPathRemovedEvent& OnPathRemoved() override;`
- L162 _public prototype_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FScanStartedEvent, FScanStartedEvent);`
- L163 _public prototype_ `virtual FScanStartedEvent& OnScanStarted() override;`
- L165 _public prototype_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FScanEndedEvent, FScanEndedEvent);`
- L166 _public prototype_ `virtual FScanEndedEvent& OnScanEnded() override;`
- L168 _public prototype_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FKnownGathersCompleteEvent, FKnownGathersCompleteEvent);`
- L169 _public prototype_ `virtual FKnownGathersCompleteEvent& OnKnownGathersComplete() override;`
- L171 _public prototype_ `virtual void AssetCreated(UObject* NewAsset) override;`
- L172 _public prototype_ `virtual void AssetDeleted(UObject* DeletedAsset) override;`
- L173 _public prototype_ `virtual void AssetRenamed(const UObject* RenamedAsset, const FString& OldObjectPath) override;`
- L174 _public prototype_ `virtual void AssetsSaved(TArray<FAssetData>&& SavedAssets) override;`
- L175 _public prototype_ `virtual void AssetUpdateTags(UObject* Object, EAssetRegistryTagsCaller Caller) override;`
- L176 _public prototype_ `virtual void AssetTagsFinalized(const UObject& FinalizedAsset) override;`
- L178 _public prototype_ `virtual bool VerseCreated(const FString& FilePath) override;`
- L179 _public prototype_ `virtual bool VerseDeleted(const FString& FilePath) override;`
- L181 _public prototype_ `virtual void PackageDeleted(UPackage* DeletedPackage) override;`
- L183 _public prototype_ `virtual IAssetRegistry::FAssetCollisionEvent& OnAssetCollision_Private() override;`
- L185 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetAddedEvent, FAssetAddedEvent);`
- L186 _public prototype_ `virtual FAssetAddedEvent& OnAssetAdded() override;`
- L188 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetRemovedEvent, FAssetRemovedEvent);`
- L189 _public prototype_ `virtual FAssetRemovedEvent& OnAssetRemoved() override;`
- L191 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetRenamedEvent, FAssetRenamedEvent);`
- L192 _public prototype_ `virtual FAssetRenamedEvent& OnAssetRenamed() override;`
- L194 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetUpdatedEvent, FAssetUpdatedEvent );`
- L195 _public prototype_ `virtual FAssetUpdatedEvent& OnAssetUpdated() override;`
- L196 _public prototype_ `virtual FAssetUpdatedEvent& OnAssetUpdatedOnDisk() override;`
- L199 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetsEvent, FAssetsEvent);` — Batch events
- L200 _public prototype_ `virtual FAssetsEvent& OnAssetsAdded() override;`
- L201 _public prototype_ `virtual FAssetsEvent& OnAssetsRemoved() override;`
- L202 _public prototype_ `virtual FAssetsEvent& OnAssetsUpdated() override;`
- L203 _public prototype_ `virtual FAssetsEvent& OnAssetsUpdatedOnDisk() override;`
- L205 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FInMemoryAssetCreatedEvent, FInMemoryAssetCreatedEvent );`
- L206 _public prototype_ `virtual FInMemoryAssetCreatedEvent& OnInMemoryAssetCreated() override;`
- L208 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FInMemoryAssetDeletedEvent, FInMemoryAssetDeletedEvent );`
- L209 _public prototype_ `virtual FInMemoryAssetDeletedEvent& OnInMemoryAssetDeleted() override;`
- L211 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FVerseAddedEvent, FVerseAddedEvent);`
- L212 _public prototype_ `virtual FVerseAddedEvent& OnVerseAdded() override;`
- L214 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FVerseRemovedEvent, FVerseRemovedEvent);`
- L215 _public prototype_ `virtual FVerseRemovedEvent& OnVerseRemoved() override;`
- L217 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FFilesLoadedEvent, FFilesLoadedEvent );`
- L218 _public prototype_ `virtual FFilesLoadedEvent& OnFilesLoaded() override;`
- L220 _public prototype_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FFileLoadProgressUpdatedEvent, FFileLoadProgressUpdatedEvent );`
- L221 _public prototype_ `virtual FFileLoadProgressUpdatedEvent& OnFileLoadProgressUpdated() override;`
- L223 _public prototype_ `virtual bool IsLoadingAssets() const override;`
- L224 _public prototype_ `virtual bool IsGathering() const override;`
- L225 _public prototype_ `virtual bool HasSerializedDiscoveryCache() const override;`
- L226 _public function_ `virtual bool ShouldUpdateDiskCacheAfterLoad() const override`
- L235 _public prototype_ `virtual void Tick (float DeltaTime) override;`
- L237 _public prototype_ `virtual void ReadLockEnumerateAllTagToAssetDatas(TFunctionRef<bool(FName TagName, IAssetRegistry::FEnumerateAssetDatasFunc EnumerateAssets)> Callback) const override;`
- L239 _public prototype_ `virtual bool IsPathBeautificationNeeded(const FString& InAssetPath) const override;`
- L241 _public prototype_ `UE::AssetRegistry::Impl::EGatherStatus TickOnBackgroundThread();`
- L243 _public prototype_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FEnumerateAssetsEvent, FEnumerateAssetsEvent) virtual FEnumerateAssetsEvent& OnEnumerateAssetsEvent() override;`
- L247 _protected prototype_ `virtual void SetManageReferences(const TMultiMap<FAssetIdentifier, FAssetIdentifier>& ManagerMap, bool bClearExisting, UE::AssetRegistry::EDependencyCategory RecurseType, TSet<FDependsNode*>& ExistingManagedNode, ShouldSetManagerPredicate ShouldSetManager = nullptr) override;`
- L250 _protected prototype_ `virtual void SetManageReferences(UE::AssetRegistry::FSetManageReferencesContext& Context) override;`
- L251 _protected prototype_ `virtual bool SetPrimaryAssetIdForObjectPath(const FSoftObjectPath& ObjectPath, FPrimaryAssetId PrimaryAssetId) override;`
- L252 _protected prototype_ `virtual void CopyManageDependenciesToState(FAssetRegistryState& InOutState) const override;`
- L255 _private prototype_ `void OnPreExit();`
- L257 _private prototype_ `void OnFEngineLoopInitCompleteSearchAllAssets();`
- L259 _private prototype_ `void OnAssetDependencyGathererRegistered();` — Called when new gatherer is registered. Requires subsequent call to RebuildAssetDependencyGathererMapIfNeeded
- L261 _private prototype_ `void InitializeEvents(UE::AssetRegistry::Impl::FInitializeContext& Context);`
- L262 _private prototype_ `void Broadcast(UE::AssetRegistry::Impl::FEventContext& EventContext, bool bAllowFileLoadedEvent = false);`
- L263 _private prototype_ `bool CanBroadcastEvents() const;`
- L265 _private prototype_ `bool OnResolveRedirect(const FString& InPackageName, FString& OutPackageName);`
- L269 _private prototype_ `void OnDirectoryChanged(const TArray<struct FFileChangeData>& Files);` — Called when a file in a content directory changes on disk
- L272 _private prototype_ `void OnAssetLoaded(UObject* AssetLoaded);` — Called when an asset is loaded, it will possibly update the cache
- L279 _private prototype_ `void OnMountPointMounted(const TRefCountPtr<UE::PackageName::IMountPoint>& MountPoint);` — Called by the engine core when a new MountPoint is added dynamically at runtime.  This is wired to FPackageName's static delegate.
- L285 _private prototype_ `void OnMountPointDismounted(const TRefCountPtr<UE::PackageName::IMountPoint>& MountPoint);` — Called by the engine core when a MountPoint is removed dynamically at runtime.  This is wired to FPackageName's static delegate.
- L288 _private prototype_ `void OnMultipleMountPointsMounted(TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> MountedMountPoints);` — Batched processing version of OnMountPointMounted.
- L291 _private prototype_ `void OnMultipleMountPointsDismounted(TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> DismountedMountPoints);` — Batched processing version of the OnMountPointDismounted.
- L294 _private prototype_ `void OnPostEngineInit();` — Called to refresh the native classes list, called at end of engine initialization.
- L300 _private prototype_ `void OnInitialPluginLoadingComplete();` — Called from LaunchEngineLoop via SetEngineStartupModuleLoadingComplete after plugins are loaded, used to scan classes that were loaded by plugins, and enable some global multithreaded access.
- L303 _private prototype_ `void ScanPathsSynchronousInternal(const TArray<FString>& InDirs, const TArray<FString>& InFiles, UE::AssetRegistry::EScanFlags InScanFlags);` — Shared helper for Scan*Synchronous function
- L307 _private prototype_ `void AddLoadedAssetToProcess(const UObject& AssetLoaded);`
- L309 _private prototype_ `void ProcessLoadedAssetsToUpdateCache(UE::AssetRegistry::Impl::FEventContext& EventContext, UE::AssetRegistry::Impl::EGatherStatus Status, UE::AssetRegistry::Impl::FInterruptionContext& InOutInterruptionContext);` — Create FAssetData from any loaded UObject assets and store the updated AssetData in the state
- L318 _private prototype_ `void GetInheritanceContextWithRequiredLock(UE::AssetRegistry::FInterfaceRWScopeLock& InOutScopeLock, UE::AssetRegistry::Impl::FClassInheritanceContext& InheritanceContext, UE::AssetRegistry::Impl::FClassInheritanceBuffer& StackBuffer);` — Remain under the given lock and return an InheritanceContext based on the appropriate choice of the persistent caching buffer or the function-scope-only passed in StackBuffer. Mark whether the buffer needs to be updated before being used. If the buffer needs to be updated and its the persistent buffer (which is protected data), convert the given lock to a write lock if not one already.
- L321 _private prototype_ `void GetInheritanceContextWithRequiredLock(UE::AssetRegistry::FInterfaceWriteScopeLock& InOutScopeLock, UE::AssetRegistry::Impl::FClassInheritanceContext& InheritanceContext, UE::AssetRegistry::Impl::FClassInheritanceBuffer& StackBuffer);`
- L331 _private prototype_ `void OnGetExtraObjectTags(FAssetRegistryTagsContext Context);` — Callback for FObject::FAssetRegistryTag::OnGetExtraObjectTags If bAddMetaDataTagsToOnGetExtraObjectTags is true, this function will add missing FMetaData tags to cooked assets
- L337 _private prototype_ `bool IsDirAlreadyWatchedByRootWatchers(const FString& Directory) const;` — Checks whether the given path is already covered by the general directory watches, or whether we need to setup a new directory watcher. The caller must ensure that the Directory parameter is in FPaths::CreateStandardFilename format.
- L341 _private prototype_ `virtual void SuspendPathsMounting() override;` — Implementation methods for FSuspendPathsMounting and FSuspendPathsDismounting
- L342 _private prototype_ `virtual void ResumePathsMounting() override;`
- L343 _private prototype_ `virtual void SuspendPathsDismounting() override;`
- L344 _private prototype_ `virtual void ResumePathsDismounting() override;`
- L350 _private prototype_ `virtual void RequestPauseBackgroundProcessing() override;` — Request to pause or resume background processing of scan results. This can be used to allow a priority thread to perform along sequence of operations without having to contend with the background thread for data access
- L351 _private prototype_ `virtual void RequestResumeBackgroundProcessing() override;`
- L352 _private function_ `bool IsBackgroundProcessingPaused() const`
- L362 _private prototype_ `void RequestTick();` — In engine modes that do not tick regularly, request a tick, to process deferred events.
- L364 _private prototype_ `void ClearRequestTick();` — In engine modes that do not tick regularly, mark the tick was called and clear the request.
- L368 _private member_ `UE::AssetRegistry::FAssetRegistryImpl GuardedData;`
- L369 _private member_ `UE::AssetRegistry::Impl::FActiveMountsLoaderWrapper ActiveMountsLoader;`
- L372 _private member_ `mutable UE::AssetRegistry::Private::FRWLockWithPriority InterfaceLock;` — Lock guarding the GuardedData
- L378 _private member_ `FCriticalSection GatheredDataProcessingLock;` — This lock doesn't strictly protect any data (the InterfaceLock does that). Instead, it is used to let the main thread know when the gatherer thread is doing processing work so that the main thread does not end up blocking on the InterfaceLock in Tick().
- L382 _private member_ `TMap<FString, FDelegateHandle> OnDirectoryChangedDelegateHandles;` — Handles to all registered OnDirectoryChanged delegates
- L383 _private member_ `TArray<FString> DirectoryWatchRoots;`
- L389 _private member_ `TQueue<TWeakObjectPtr<const UObject>, EQueueMode::Mpsc> LoadedAssetsToProcess;` — List of objects that need to be processed because they were loaded or saved. This object lives outside of the GuardedData as it doesn't require the InterfaceLock to be written to. Reads must be coordinated such that only one thread reads at a time.
- L394 _private member_ `bool bAddMetaDataTagsToOnGetExtraObjectTags = true;` — If true, the asset registry will inject missing tags from FMetaData for cooked assets only in GetAssetRegistryTags
- L397 _private member_ `bool bUpdateDiskCacheAfterLoad = true;` — If true, the AssetRegistry updates its on-disk information for an Asset whenever that Asset loads.
- L401 _private member_ `FFilesBlockedEvent FilesBlockedEvent;` — The delegate to execute when one or more files have been blocked from the registry
- L404 _private member_ `FPathsEvent PathsAddedEvent;` — The delegate to execute when a batch of paths are added to the registry
- L407 _private member_ `FPathsEvent PathsRemovedEvent;` — The delegate to execute when a batch of paths are removed from the registry
- L410 _private member_ `FPathAddedEvent PathAddedEvent;` — The delegate to execute when an asset path is added to the registry
- L413 _private member_ `FPathRemovedEvent PathRemovedEvent;` — The delegate to execute when an asset path is removed from the registry
- L416 _private member_ `FAssetAddedEvent AssetAddedEvent;` — The delegate to execute when an asset is added to the registry
- L419 _private member_ `FAssetRemovedEvent AssetRemovedEvent;` — The delegate to execute when an asset is removed from the registry
- L422 _private member_ `FAssetRenamedEvent AssetRenamedEvent;` — The delegate to execute when an asset is renamed in the registry
- L425 _private member_ `FAssetUpdatedEvent AssetUpdatedEvent;` — The delegate to execute when an asset is updated in the registry
- L428 _private member_ `FAssetUpdatedEvent AssetUpdatedOnDiskEvent;` — The delegate to execute when an asset is updated on disk and has been reloaded in assetregistry
- L431 _private member_ `static constexpr SIZE_T NumBatchedEvents = static_cast<SIZE_T>(UE::AssetRegistry::Impl::FEventContext::EEvent::MAX);` — The delegates to execute when assets are added/removed/updated in the registry, indexed by FEventContext::EEvent or returned with public accessors
- L432 _private member_ `FAssetsEvent BatchedAssetEvents[NumBatchedEvents];`
- L435 _private member_ `FInMemoryAssetCreatedEvent InMemoryAssetCreatedEvent;` — The delegate to execute when an in-memory asset was just created
- L438 _private member_ `FInMemoryAssetDeletedEvent InMemoryAssetDeletedEvent;` — The delegate to execute when an in-memory asset was just deleted
- L441 _private member_ `FVerseAddedEvent VerseAddedEvent;` — The delegate to execute when a Verse file is added to the registry
- L444 _private member_ `FVerseRemovedEvent VerseRemovedEvent;` — The delegate to execute when a Verse file is removed from the registry
- L447 _private member_ `FFilesLoadedEvent FileLoadedEvent;` — The delegate to execute when finished loading files
- L450 _private member_ `FFileLoadProgressUpdatedEvent FileLoadProgressUpdatedEvent;` — The delegate to execute while loading files to update progress
- L453 _private member_ `FScanStartedEvent ScanStartedEvent;` — The delegate to execute scanning has begun
- L456 _private member_ `FScanEndedEvent ScanEndedEvent;` — The delegate to execute scanning has ended
- L459 _private member_ `FKnownGathersCompleteEvent KnownGathersCompleteEvent;` — The delegate to execute when each batch of searching/gathering is complete
- L462 _private member_ `FEnumerateAssetsEvent EnumerateAssetsEvent;` — The delegate to execute when a query is made.
- L468 _private member_ `UE::AssetRegistry::Impl::FEventContext DeferredEvents;` — Storage for events that will be broadcast later on the game thread. Only safe to access under the DeferredEventsCriticalSection.
- L473 _private member_ `FTSTicker::FDelegateHandle TickRequestHandle;` — Handle for a currently active tick request. Runtime game only, not used in GIsEditor. Used to process DeferredEvents. Read/Write only within DeferredEventsCriticalSection.
- L474 _private member_ `FCriticalSection DeferredEventsCriticalSection;`
- L478 _private member_ `std::atomic<int32> SuspendMountingCounter = 0;` — Suspension and resuming of paths mounting and dismounting. Used for batching many OnMountPointMounted/OnMountPointDismounted calls together.
- L479 _private member_ `std::atomic<int32> SuspendDismountingCounter = 0;`
- L480 _private member_ `FCriticalSection MountingCriticalSection;`
- L481 _private member_ `TArray<TRefCountPtr<UE::PackageName::IMountPoint>> ListOfMountedMountPoints;`
- L482 _private member_ `TArray<TRefCountPtr<UE::PackageName::IMountPoint>> ListOfDismountedMountPoints;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L14 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L15 _namespace_ `namespace Premade` (scope `UE::AssetRegistry`)
- L149 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FFilesBlockedEvent, FFilesBlockedEvent);`
- L152 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FPathsEvent, FPathsEvent);`
- L156 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FPathAddedEvent, FPathAddedEvent);`
- L159 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FPathRemovedEvent, FPathRemovedEvent);`
- L162 _delegate_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FScanStartedEvent, FScanStartedEvent);`
- L165 _delegate_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FScanEndedEvent, FScanEndedEvent);`
- L168 _delegate_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FKnownGathersCompleteEvent, FKnownGathersCompleteEvent);`
- L185 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetAddedEvent, FAssetAddedEvent);`
- L188 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetRemovedEvent, FAssetRemovedEvent);`
- L191 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetRenamedEvent, FAssetRenamedEvent);`
- L194 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetUpdatedEvent, FAssetUpdatedEvent );`
- L199 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FAssetsEvent, FAssetsEvent);` — Batch events
- L205 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FInMemoryAssetCreatedEvent, FInMemoryAssetCreatedEvent );`
- L208 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FInMemoryAssetDeletedEvent, FInMemoryAssetDeletedEvent );`
- L211 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FVerseAddedEvent, FVerseAddedEvent);`
- L214 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FVerseRemovedEvent, FVerseRemovedEvent);`
- L217 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FFilesLoadedEvent, FFilesLoadedEvent );`
- L220 _delegate_ `DECLARE_DERIVED_EVENT( UAssetRegistryImpl, IAssetRegistry::FFileLoadProgressUpdatedEvent, FFileLoadProgressUpdatedEvent );`
- L243 _delegate_ `DECLARE_DERIVED_EVENT(UAssetRegistryImpl, IAssetRegistry::FEnumerateAssetsEvent, FEnumerateAssetsEvent) virtual FEnumerateAssetsEvent& OnEnumerateAssetsEvent() override;`

### `Source/Runtime/AssetRegistry/Private/AssetRegistryArchive.h` (Private)


#### struct `FAssetRegistryHeader`  
`struct FAssetRegistryHeader`  
_L15-21_
- desc: Header containing versioning & data stripping information for a serialized asset registry state.
- L17 _public member_ `FAssetRegistryVersion::Type Version = FAssetRegistryVersion::LatestVersion;`
- L18 _public member_ `bool bFilterEditorOnlyData = false;` — True if editor only data has been removed/should be removed while saving
- L20 _public prototype_ `void SerializeHeader(FArchive& Ar);`

#### class `FAssetRegistryReader`  
`class FAssetRegistryReader : public FArchiveProxy`  
_L24-47_
- inherits: `FArchiveProxy`
- desc: @see FAssetRegistryWriter
- L29 _public prototype_ `FAssetRegistryReader(FArchive& Inner, TSharedPtr<UE::AssetRegistry::FMemoryMappedFile> InBackingFile, const FixedTagPrivate::FWeakStorePtr& PreviousLoadedStore, int32 NumWorkers, FAssetRegistryHeader Header);` — @param InBackingFile shared pointer to a class that allows mapping the underlying file into memory @param NumWorkers > 0 for parallel loading
- L31 _public prototype_ `~FAssetRegistryReader();`
- L32 _public prototype_ `const TRefCountPtr<const FixedTagPrivate::FStore>& GetTags() const;`
- L34 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L36 _public prototype_ `void SerializeTagsAndBundles(FAssetData& Out);`
- L37 _public prototype_ `void SerializeTagsAndBundlesOldVersion(FAssetData& Out, FAssetRegistryVersion::Type Version);`
- L39 _public prototype_ `void WaitForTasks();`
- L42 _private member_ `TArray<FDisplayNameEntryId> Names;`
- L43 _private member_ `TRefCountPtr<const FixedTagPrivate::FStore> Tags;`
- L44 _private member_ `TFuture<void> Task;`

#### class `FAssetRegistryWriterBase`  
`class FAssetRegistryWriterBase`  
_L51-55_
- L54 _protected member_ `FLargeMemoryWriter MemWriter;`

#### struct `FAssetRegistryWriterOptions`  
`struct FAssetRegistryWriterOptions`  
_L57-63_
- L59 _public prototype_ `FAssetRegistryWriterOptions() = default;`
- L60 _public prototype_ `explicit FAssetRegistryWriterOptions(const FAssetRegistrySerializationOptions& Options);`
- L62 _public member_ `FixedTagPrivate::FOptions Tags;`

#### class `FAssetRegistryWriter`  
`class FAssetRegistryWriter : public FAssetRegistryWriterBase, public FArchiveProxy`  
_L78-94_
- inherits: `FAssetRegistryWriterBase,FArchiveProxy`
- desc: Indexes FName and tag maps and serializes out deduplicated indices instead. Unlike previous FNameTableArchiveWriter: - Name data stored as name batches, which is faster - Name batch is written as a header instead of footer for faster seek-free loading - Numberless FNames are serialized as a single 32-bit int - Deduplicates all tag values, not just names Use in conjunction with FNameBatchReader. Data is written to inner archive in destructor to achieve seek-free loading.
- L81 _public prototype_ `FAssetRegistryWriter(const FAssetRegistryWriterOptions& Options, FArchive& Out);`
- L82 _public prototype_ `~FAssetRegistryWriter();`
- L84 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L86 _public prototype_ `void SerializeTagsAndBundles(const FAssetData& In);`
- L89 _private member_ `TMap<FDisplayNameEntryId, uint32> Names;`
- L90 _private member_ `FixedTagPrivate::FStoreBuilder Tags;`
- L91 _private member_ `FArchive& TargetAr;`

### `Source/Runtime/AssetRegistry/Private/AssetRegistryConsoleCommands.h` (Private)


#### class `FAssetRegistryConsoleCommands`  
`class FAssetRegistryConsoleCommands`  
_L15-333_
- L19 _public member_ `FAutoConsoleCommand GetByNameCommand;`
- L20 _public member_ `FAutoConsoleCommand GetByPathCommand;`
- L21 _public member_ `FAutoConsoleCommand GetByClassCommand;`
- L22 _public member_ `FAutoConsoleCommand GetByTagCommand;`
- L23 _public member_ `FAutoConsoleCommand GetDependenciesCommand;`
- L24 _public member_ `FAutoConsoleCommand GetReferencersCommand;`
- L25 _public member_ `FAutoConsoleCommand FindInvalidUAssetsCommand;`
- L26 _public member_ `FAutoConsoleCommand ScanPathCommand;`
- L27 _public member_ `FAutoConsoleCommand DumpAllocatedSizeCommand;`
- L28 _public member_ `FAutoConsoleCommand DumpStateCommand;`
- L30 _public function_ `FAssetRegistryConsoleCommands() : GetByNameCommand( TEXT( "AssetRegistry.GetByName" ), *LOCTEXT("CommandText_GetByName", "<PackageName>`
- L73 _public function_ `void GetByName(const TArray<FString>& Args)`
- L91 _public function_ `void GetByPath(const TArray<FString>& Args)`
- L109 _public function_ `void GetByClass(const TArray<FString>& Args)`
- L134 _public function_ `void GetByTag(const TArray<FString>& Args)`
- L154 _public function_ `void GetDependencies(const TArray<FString>& Args)`
- L179 _public function_ `void GetReferencers(const TArray<FString>& Args)`
- L204 _public function_ `void FindInvalidUAssets(const TArray<FString>& Args)`
- L229 _public function_ `void ScanPath(const TArray<FString>& Args)`
- L291 _public function_ `void DumpAllocatedSize(const TArray<FString>& Args)`
- L298 _public function_ `void DumpState(const TArray<FString>& Args)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "AssetRegistry"`

### `Source/Runtime/AssetRegistry/Private/AssetRegistryImpl.h` (Private)


#### struct `UE::AssetRegistry::Impl::FClassInheritanceBuffer`  
`struct FClassInheritanceBuffer`  
_L54-71_
- desc: Container for global class inheritance data; the AssetRegistry may use a persistent buffer or a stack local buffer.
- L57 _public member_ `TMap<FTopLevelAssetPath, FTopLevelAssetPath> InheritanceMap;` — Map from Class->SuperClass for all classes including native classes and blueprint classes. Updated on demand.
- L59 _public member_ `TMap<FTopLevelAssetPath, TArray<FTopLevelAssetPath>> ReverseInheritanceMap;` — Map from Class->(All subclasses) for all classes including native classes and blueprint classes. Updated on demand.
- L61 _public member_ `uint64 SavedAllClassesVersionNumber = MAX_uint64;` — Snapshot of GetCurrentAllClassesVersionNumber() at the time of the last update, to invalidate on changes to classes.
- L63 _public member_ `bool bDirty = true;` — Dirty flag to invalidate on other changes requiring a recompute.
- L66 _public prototype_ `bool IsUpToDate(uint64 CurrentAllClassesVersionNumber) const;` — Report whether the dirty flag and other checks indicate this buffer does not need to be updated.
- L68 _public prototype_ `void Clear();` — Delete data and free allocations.
- L70 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Report size of dynamic allocations.

#### enum `UE::AssetRegistry::Impl::EGatherStatus`  
`enum class EGatherStatus : uint8`  
_L74-82_
- desc: Status of gathering, returned from the Tick function
- L76 _public enumerator_ `TickActiveGatherActive`
- L77 _public enumerator_ `TickActiveGatherIdle`
- L78 _public enumerator_ `TickGameThreadActiveGatherIdle`
- L79 _public enumerator_ `Complete`
- L80 _public enumerator_ `UnableToProgress`
- L81 _public enumerator_ `WaitingForEvents`

#### enum `UE::AssetRegistry::Impl::EPerformanceMode`  
`enum EPerformanceMode : uint8`  
_L85-92_
- desc: Affects how rules are applied to improve loading/runtime performance
- L88 _public enumerator_ `BulkLoading` — Handling slow async load
- L91 _public enumerator_ `MostlyStatic` — Not changing, optimize for runtime queries

#### struct `UE::AssetRegistry::Impl::FInterruptionContext`  
`struct FInterruptionContext`  
_L95-141_
- desc: Provides handling for time slicing during TickGatherer
- L98 _public typedef_ `typedef TFunction<bool(void)> ShouldExitEarlyCallbackType;`
- L100 _public prototype_ `FInterruptionContext() = default;`
- L101 _public function_ `explicit FInterruptionContext(double InTickStartTime, double InMaxRunningTime) : TickStartTime(InTickStartTime) , MaxRunningTime(InMaxRunningTime)`
- L107 _public function_ `FInterruptionContext(double InTickStartTime, double InMaxRunningTime, ShouldExitEarlyCallbackType& Callback) : TickStartTime(InTickStartTime) , MaxRunningTime(InMaxRunningTime) , EarlyExitCallback(Callback)`
- L112 _public function_ `void SetEarlyExitCallback(const ShouldExitEarlyCallbackType& InCallback)`
- L116 _public function_ `void SetUnlimitedTickTime()`
- L121 _public function_ `void SetLimitedTickTime(double InTickStartTime, double InMaxRunningTime)`
- L126 _public function_ `double GetTickStartTime() const`
- L127 _public function_ `bool IsTimeSlicingEnabled() const`
- L128 _public function_ `bool WasInterrupted() const`
- L129 _public prototype_ `bool ShouldExitEarly();`
- L130 _public function_ `void RequestEarlyExit()`
- L134 _private member_ `double TickStartTime = -1.;` — A negative value disables time slicing
- L136 _private member_ `double MaxRunningTime = -1.;` — The maximum time should allow before interruption. If TickStartTime is negative, this is ignored
- L138 _private member_ `ShouldExitEarlyCallbackType EarlyExitCallback;` — If provided, this is always checked
- L140 _private member_ `bool OutInterrupted = false;` — True if we ran out of time, EarlyExitCallback returned true, or RequestEarlyExit() was called

#### struct `UE::AssetRegistry::Impl::FParsedFilterTagRules`  
`struct FParsedFilterTagRules`  
_L144-155_
- desc: Container holding information for runtime resolution of parsed filter tag rules
- L153 _public member_ `TArray<FFilterTagsRule> OrderedList;`
- L154 _public member_ `bool bContainsAnyUnresolvedRule = false;`

#### struct `UE::AssetRegistry::Impl::FParsedFilterTagRules::FFilterTagsRule`  
`struct FFilterTagsRule`  
_L146-152_
- L148 _public member_ `FTopLevelAssetPath ClassPath;`
- L149 _public member_ `const UClass* ClassPtr = nullptr;`
- L150 _public member_ `int32 InheritanceDepth = 0;` — used as a sorting criteria to order classes from base to leaf.
- L151 _public member_ `bool bInclude = false;`

#### struct `UE::AssetRegistry::Impl::FFilterTagRules`  
`struct FFilterTagRules`  
_L157-164_
- L159 _public function_ `SIZE_T GetAllocatedSize() const`
- L161 _public member_ `TMap<FName, FParsedFilterTagRules> Rules;`
- L162 _public member_ `uint64 ClassesFingerprint = 0;`
- L163 _public member_ `bool bContainsAnyUnresolvedRule = false;`

#### enum `UE::AssetRegistry::EDeferFlag`  
`enum class EDeferFlag`  
_L168-181_
- desc: Options for how AssetRegistry functions should handle operations that must only be run on the gamethread.
- L171 _public enumerator_ `CanExecuteGameThread` — The function is running on the gamethread currently, it can execute the operation.
- L173 _public enumerator_ `RetryLater` — The function should mark itself temporarily failed and the caller will try again later.
- L175 _public enumerator_ `QueueToGameThread` — The function should send a message to the game thread to execute the operation there.
- L180 _public enumerator_ `BypassNow` — The function can not execute, can not defer, cannot queue; it has to complete its task now. Skip the operation, and log warnings or errors if the skipping will cause problems.

#### class `UE::AssetRegistry::FAssetRegistryImpl`  
`class FAssetRegistryImpl`  
_L201-749_
- desc: Threading helper class for UAssetRegistryImpl that holds all of the data. This class is not threadsafe; all const functions must be called from within a ReadLock and all non-const from within a WriteLock.
- L203 _private typedef_ `using FAssetDataMap = UE::AssetRegistry::Private::FAssetDataMap;`
- L204 _private typedef_ `using FCachedAssetKey = UE::AssetRegistry::Private::FCachedAssetKey;`
- L208 _public prototype_ `FAssetRegistryImpl();` — Constructor initializes as little as possible; meaningful operations are first done during Initialize.
- L210 _public prototype_ `void Initialize(UE::AssetRegistry::FInterfaceWriteScopeLock& ScopeLock, Impl::FInitializeContext& Context);` — Construct the AssetRegistryImpl, including initial scans if applicable.
- L213 _public prototype_ `IAssetRegistry::FAssetCollisionEvent& OnAssetCollision_Private();` — Event for when duplicated assets are found and needs to be resolved
- L218 _public prototype_ `bool HasAssets(const FName PackagePath, const bool bRecursive) const;`
- L224 _public prototype_ `FSoftObjectPath GetRedirectedObjectPath(FInterfaceReadScopeLock& ScopeLock, const FSoftObjectPath& ObjectPath);` — Returns the redirected object path for the provided soft object path. This function will not attempt to scan the redirected path to ensure it has been registered with the Asset Registry. If it's unclear if the object path is known to the Asset Registry already, call GetAndScanRedirectedObjectPath instead.
- L229 _public prototype_ `FSoftObjectPath GetAndScanRedirectedObjectPath(FInterfaceWriteScopeLock& ScopeLock, const FSoftObjectPath& ObjectPath, UE::AssetRegistry::Impl::FEventContext* EventContext, UE::AssetRegistry::Impl::FClassInheritanceContext* InheritanceContext);` — Returns the redirected object path for the provided soft object path. This function will scan the redirected path to ensure it has been registered with the Asset Registry.
- L231 _public prototype_ `bool GetAncestorClassNames(Impl::FClassInheritanceContext& InheritanceContext, FTopLevelAssetPath ClassName, TArray<FTopLevelAssetPath>& OutAncestorClassNames) const;`
- L233 _public prototype_ `void CompileFilter(Impl::FClassInheritanceContext& InheritanceContext, const FARFilter& InFilter, FARCompiledFilter& OutCompiledFilter) const;`
- L235 _public prototype_ `void SetTemporaryCachingMode(bool bEnable);`
- L236 _public prototype_ `void SetTemporaryCachingModeInvalidated();`
- L237 _public prototype_ `bool AddPath(Impl::FEventContext& EventContext, FStringView PathToAdd);`
- L238 _public prototype_ `void SearchAllAssets(Impl::FEventContext& EventContext, Impl::FClassInheritanceContext& InheritanceContext, bool bSynchronousSearch);`
- L240 _public prototype_ `bool GetVerseFilesByPath(FName PackagePath, TArray<FName>* OutFilePaths, bool bRecursive) const;`
- L241 _public prototype_ `void ScanPathsSynchronous(FInterfaceWriteScopeLock* ScopeLock, Impl::FScanPathContext& Context);`
- L242 _public prototype_ `void PrioritizeSearchPath(const FString& PathToPrioritize);`
- L243 _public prototype_ `void ScanModifiedAssetFiles(FInterfaceWriteScopeLock& ScopeLock, Impl::FEventContext& EventContext, Impl::FClassInheritanceContext& InheritanceContext, const TArray<FString>& InFilePaths, UE::AssetRegistry::EScanFlags ScanFlags);`
- L245 _public prototype_ `void Serialize(FArchive& Ar, Impl::FEventContext& EventContext);`
- L246 _public prototype_ `void AppendState(Impl::FEventContext& EventContext, const FAssetRegistryState& InState, FAssetRegistryState::EInitializationMode Mode = FAssetRegistryState::EInitializationMode::Append, bool bEmitAssetEvents = false);`
- L249 _public prototype_ `void ConsumeState(Impl::FEventContext& EventContext, FAssetRegistryState&& InState, bool bEmitAssetEvents = false);` — Similar to AppendState, but it moves rather than copies. @see FAssetRegistryState::ConsumeExisting.
- L250 _public prototype_ `void GetAllocatedSize(bool bLogDetailed, SIZE_T& StateSize, SIZE_T& StaticSize, SIZE_T& SearchSize) const;`
- L251 _public prototype_ `bool IsLoadingAssets() const;`
- L252 _public prototype_ `bool IsGathering() const;`
- L253 _public prototype_ `bool HasSerializedDiscoveryCache() const;`
- L254 _public prototype_ `void SetManageReferences(FSetManageReferencesContext& Context);`
- L255 _public prototype_ `bool SetPrimaryAssetIdForObjectPath(Impl::FEventContext& EventContext, const FSoftObjectPath& ObjectPath, FPrimaryAssetId PrimaryAssetId);`
- L256 _public prototype_ `bool ResolveRedirect(const FString& InPackageName, FString& OutPackageName) const;`
- L258 _public prototype_ `void OnDirectoryChanged(FInterfaceWriteScopeLock& ScopeLock, Impl::FEventContext& EventContext, Impl::FClassInheritanceContext& InheritanceContext, TArray<FFileChangeData>& FileChangesProcessed);`
- L260 _public prototype_ `void OnDirectoryRescanRequired(FInterfaceWriteScopeLock& ScopeLock, Impl::FEventContext& EventContext, Impl::FClassInheritanceContext& InheritanceContext, FString& DirPath, int64 BeforeTimeStamp);`
- L263 _public prototype_ `void OnMultipleMountPointsMounted(UAssetRegistryImpl& UARI, Impl::FEventContext& EventContext, Impl::FActiveMountEvents& ActiveMountEvents, Impl::FClassInheritanceContext& InheritanceContext, UE::AssetRegistry::FInterfaceWriteScopeLock& ScopeLock, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> MountedMountPoints);`
- L268 _public prototype_ `void OnMultipleMountPointsDismounted(UAssetRegistryImpl& UARI, Impl::FEventContext& EventContext, Impl::FActiveMountEvents& ActiveMountEvents, UE::AssetRegistry::FInterfaceWriteScopeLock& ProofOfWriteLock, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> DismountedMountPoints);`
- L279 _public prototype_ `void OnPluginLoadingComplete(bool bPhaseSuccessful);` — Update cached values about classes, and enable some global multithreaded access, when all startup plugins finish loading.
- L281 _public prototype_ `void RefreshNativeClasses();` — Update cached values about native classes after they have possibly changed.
- L284 _public prototype_ `void EnumerateDiskAssets(const FARCompiledFilter& InFilter, TSet<FName>& PackagesToSkip, TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags) const;` — Enumerate assets in the State, filtering by filter and package not in PackagesToSkip
- L287 _public prototype_ `void EnumerateAllDiskAssets(TSet<FName>& PackageNamesToSkip, TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const;` — Enumerate all assets in the State. PackageNamesToSkip are filtered. EEnumerateAssetsFlags provide additional filtering.
- L290 _public prototype_ `void WaitForGathererIdleIfSynchronous();` — Waits for the gatherer to be idle if it is operating synchronously.
- L292 _public prototype_ `void WaitForGathererIdle(float TimeoutSeconds);` — Waits for the gatherer to be idle.
- L294 _public prototype_ `Impl::EGatherStatus TickGatherer(Impl::FTickContext& TickContext);` — Consume any results from the gatherer and return its status
- L299 _public prototype_ `void ProcessGameThreadRequestedClasses();` — During gamethread tick, if we find that the background thread is active in TickGatherer, process any classes that the background requested from the gamethread tick.
- L304 _public prototype_ `void ConditionalRetryGatherAssetsForGameThread(Impl::FTickContext& TickContext);` — If TickContext is on a background thread and the game thread has executed ProcessGameThreadRequestedClasses, retry all assets in AssetsForGameThread by moving them to the any-thread Assets queue.
- L306 _public prototype_ `void ConditionalClearGameThreadRequestedClasses(Impl::FTickContext& TickContext);` — Clear GameThreadRequestedClasses if AssetsForGameThread is empty.
- L308 _public prototype_ `void RequestGameThreadProcessClass(const FTopLevelAssetPath& RequestedGameThreadClass);` — Add a class to GameThreadRequestedClasses and set the sentry flag to request processing.
- L314 _public prototype_ `bool IsGameThreadTakeOverGatherEachTick() const;` — At some times during editor startup, depending on config settings, we might want to block on the gather, and not tick the rest of the editor. When we want that to happen, we set this flag. This function can be read outside of the lock (we need to do that during Tick).
- L315 _public prototype_ `void SetGameThreadTakeOverGatherEachTick(bool bValue);`
- L320 _public prototype_ `void LogSearchDiagnostics(double StartTime, bool bInitialScan);` — Send a log message with the search statistics. StartTime is used to report wall clock search time in the case of background scan
- L322 _public prototype_ `void TickGatherPackage(UE::AssetRegistry::FInterfaceWriteScopeLock& ScopeLock, Impl::FEventContext& EventContext, const FString& PackageName, const FString& LocalPath);` — Look for and load a single AssetData result from the gatherer.
- L323 _public prototype_ `void ClearGathererCache();`
- L325 _public prototype_ `void AssetsSaved(UE::AssetRegistry::Impl::FEventContext& EventContext, TArray<FAssetData>&& Assets);`
- L326 _public prototype_ `void GetProcessLoadedAssetsBatch(TQueue<TWeakObjectPtr<const UObject>, EQueueMode::Mpsc>& LoadedAssetsToProcess, TArray<const UObject*>& OutLoadedAssets, uint32 BatchSize, bool bUpdateDiskCacheAfterLoad);`
- L328 _public prototype_ `void PushProcessLoadedAssetsBatch(Impl::FEventContext& EventContext, TQueue<TWeakObjectPtr<const UObject>, EQueueMode::Mpsc>& LoadedAssetsToProcess, TArrayView<FAssetData> LoadedAssetDatas, TArrayView<const UObject*> UnprocessedFromBatch);`
- L331 _public prototype_ `bool IsLoadedAndTrackedAsset(const FSoftObjectPath& InObjectPath) const;`
- L333 _public prototype_ `void LoadCalculatedDependencies(TArray<FName>* AssetPackageNamessToCalculate, Impl::FClassInheritanceContext& InheritanceContext, TSet<FName>* InPackagesNeedingDependencyCalculation, Impl::FInterruptionContext& InOutInterruptionContext);` — Call LoadCalculatedDependencies on each Package updated after the last LoadCalculatedDependencies.
- L341 _public prototype_ `void PruneAndCoalescePackagesRequiringDependencyCalculation(TSet<FName>& BackgroundPackages, TSet<FName>& GameThreadPackages, Impl::FInterruptionContext& InOutInterruptionContext);` — For each package in BackgroundPackages, if there is a registered gatherer for its asset class, this function will move the package to GameThreadPackages otherwise it will be removed from the set. Any entries in GameThreadPackages that do not have a corresponding registered gatherer will likewise be removed. The end condition for this function is that BackgroundPackages is empty and GameThreadPackages contains only those packages which require LoadCalculatedDependencies to be called on them
- L348 _public prototype_ `void LoadCalculatedDependencies(FName PackageName, Impl::FClassInheritanceContext& InheritanceContext, bool& bOutHadActivity);` — Look for a CalculatedDependencies function registered for the asset(s) in the given package and call that function to add calculated dependencies. Calculated dependencies are added only after all normal dependencies gathered from the AssetRegistry data stored in the package have been loaded.
- L351 _public prototype_ `void AddDirectoryReferencer(FName PackageName, const FString& DirectoryLocalPathOrLongPackageName);` — Add a watch on a directory that to modify data for a package whenever packages in the directory are modified.
- L353 _public prototype_ `void SetDirectoriesWatchedByPackage(FName PackageName, TConstArrayView<FString> Directories);` — Set the directories watched by PackageName. Removes previous list, call with empty array to clear.
- L356 _public function_ `void OnAssetDependencyGathererRegistered()` — Called when new gatherer is registered. Requires subsequent call to RebuildAssetDependencyGathererMapIfNeeded
- L358 _public prototype_ `void ApplyObjectRedirectsToGatheredAssetDatas();`
- L362 _public prototype_ `void AddEmptyPackage(FName PackageName);` — Adds an asset to the empty package list which contains packages that have no assets left in them
- L364 _public prototype_ `bool RemoveEmptyPackage(FName PackageName);` — Removes an asset from the empty package list because it is no longer empty
- L366 _public prototype_ `bool AddAssetPath(Impl::FEventContext& EventContext, FName PathToAdd);` — Adds a path to the cached paths tree. Returns true if the path was added and did not already exist
- L368 _public prototype_ `bool RemoveAssetPath(Impl::FEventContext& EventContext, FName PathToRemove, bool bEvenIfAssetsStillExist = false);` — Removes a path to the cached paths tree. Returns true if successful.
- L370 _public prototype_ `void RemovePackageData(Impl::FEventContext& EventContext, const FName PackageName);` — Removes the asset data associated with this package from the look-up maps
- L372 _public prototype_ `void AddVerseFile(Impl::FEventContext& EventContext, FName VerseFilePathToAdd);` — Adds the Verse file to the look up maps
- L374 _public prototype_ `void RemoveVerseFile(Impl::FEventContext& EventContext, FName VerseFilePathToRemove);` — Removes the Verse file from the look-up maps
- L377 _public prototype_ `void GetSubClasses(Impl::FClassInheritanceContext& InheritanceContext, const TArray<FTopLevelAssetPath>& InClassNames, const TSet<FTopLevelAssetPath>& ExcludedClassNames, TSet<FTopLevelAssetPath>& SubClassNames) const;` — Returns the names of all subclasses of the class whose name is ClassName
- L380 _public function_ `bool IsInitialSearchCompleted() const`
- L381 _public function_ `bool IsTempCachingEnabled() const`
- L382 _public function_ `bool IsTempCachingAlwaysEnabled() const`
- L383 _public function_ `bool IsInitialSearchStarted() const`
- L384 _public function_ `bool IsAdditionalMountSearchInProgress() const`
- L385 _public function_ `bool IsSearchAllAssets() const`
- L386 _public function_ `Impl::FClassInheritanceBuffer& GetTempCachedInheritanceBuffer()`
- L387 _public function_ `uint64 GetSavedGeneratorClassesVersionNumber() const`
- L388 _public function_ `uint64 GetSavedAllClassesVersionNumber() const`
- L389 _public prototype_ `static uint64 GetCurrentGeneratorClassesVersionNumber();`
- L390 _public prototype_ `static uint64 GetCurrentAllClassesVersionNumber();`
- L393 _public prototype_ `void CopySerializationOptions(FAssetRegistrySerializationOptions& OutOptions, ESerializationTarget Target) const;` — Get a copy of the cached serialization options that were parsed from ini
- L396 _public function_ `Impl::EPerformanceMode GetPerformanceMode() const` — Query the performance mode, which modifies how data structures are loaded
- L397 _public prototype_ `void SetPerformanceMode(Impl::EPerformanceMode NewMode);`
- L398 _public prototype_ `bool ShouldSortDependencies() const;`
- L399 _public prototype_ `bool ShouldSortReferencers() const;`
- L401 _public prototype_ `const FAssetRegistryState& GetState() const;`
- L402 _public prototype_ `const FPathTree& GetCachedPathTree() const;`
- L403 _public prototype_ `const TSet<FName>& GetCachedEmptyPackages() const;`
- L406 _public prototype_ `bool ShouldSkipAsset(FTopLevelAssetPath AssetClass, uint32 PackageFlags) const;` — Same as UE::AssetRegistry::Filtering::ShouldSkipAsset, but can be read from any thread under readlock
- L407 _public prototype_ `bool ShouldSkipAsset(const UObject* InAsset) const;`
- L410 _public prototype_ `void CollectCodeGeneratorClasses();` — Finds all class names of classes capable of generating new UClasses
- L417 _public prototype_ `void ConditionalLoadPremadeAssetRegistry(UE::AssetRegistry::FInterfaceWriteScopeLock& ScopeLock, UE::AssetRegistry::Impl::FEventContext& EventContext);` — Block until the Premade AssetRegistry finishes loading, if there is one still loading. For performance reasons, this must be called within the WriteScopeLock, and the caller must handle the possibility that it leaves and reenters the lock.
- L421 _public prototype_ `void UnloadMountPoints(Impl::FEventContext& EventContext, TConstArrayView<TRefCountPtr<UE::PackageName::IMountPoint>> MountPoints);` — Unload specified MountPoints, helper for OnMultipleMountPointsDismounted and others.
- L429 _public prototype_ `void RequestPauseBackgroundProcessing();` — Request to pause or resume background processing of scan results. This can be used to allow a priority thread to perform along sequence of operations without having to contend with the background thread for data access
- L430 _public prototype_ `void RequestResumeBackgroundProcessing();`
- L431 _public prototype_ `bool IsBackgroundProcessingPaused() const;`
- L432 _public prototype_ `uint32& GetBackgroundTickInterruptionsCount();`
- L438 _private member_ `IAssetRegistry::FAssetCollisionEvent AssetCollisionEvent;` — The delegate to execute when an asset collision is detected
- L442 _private prototype_ `template<typename TScopeLock> FSoftObjectPath GetRedirectedObjectPath(TScopeLock& ScopeLock, const FSoftObjectPath& ObjectPath, UE::AssetRegistry::Impl::FEventContext* EventContext, UE::AssetRegistry::Impl::FClassInheritanceContext* InheritanceContext);` — Helper method for public implementations which vary based on lock type
- L448 _private prototype_ `void EnumerateAssetsByPathNoTags(FName PackagePath, TFunctionRef<bool(const FAssetData&)> Callback, bool bRecursive, bool bIncludeOnlyOnDiskAssets) const;` — Enumerate all AssetData in memory and in the State that match the given path. The returned AssetData for objects present in memory have no AssetRegistryTags calculated
- L451 _private prototype_ `void InitRedirectors(Impl::FEventContext& EventContext, Impl::FClassInheritanceContext& InheritanceContext, bool& bOutRedirectorsNeedSubscribe);` — Create redirectors read by this->GetRedirectedObjectPath, based on plugin settings
- L454 _private prototype_ `void ReadScriptPackages();` — If collecting dependencies, create an FAssetPackageData for every script package, to make sure dependencies can find a data for them.
- L458 _private prototype_ `bool TryConstructGathererIfNeeded();` — Try to construct the gatherer if it does not already exist. If that is not possible (e.g., because we are shutting down) return false. If it was successfully created or already existed, return true.
- L460 _private prototype_ `void SearchAllAssetsInitialAsync(Impl::FEventContext& EventContext, Impl::FClassInheritanceContext& InheritanceContext);` — Called to set up timing variables and launch the on-constructor SearchAllAssets async call
- L466 _private prototype_ `void AssetSearchDataGathered(Impl::FEventContext& EventContext, TMultiMap<FName, TUniquePtr<FAssetData>>& AssetResults, TMultiMap<FName, TUniquePtr<FAssetData>>& OutDeferredResults, Impl::FInterruptionContext& InOutInterruptionContext, TOptional<TSet<FString>>& MountPointsForVerifyAfterGather, EDeferFlag DeferFlag);` — Called every tick to when data is retrieved by the background asset search. If TickStartTime is < 0, the entire list of gathered assets will be cached. Also used in sychronous searches The DeferredResults array receives assets that were not ready for processing due to required UClass's not being loaded.
- L473 _private prototype_ `bool ShouldSkipGatheredAsset(FAssetData& AssetData);` — Validate assets gathered from disk before adding them to the AssetRegistry.
- L479 _private prototype_ `void PathDataGathered(Impl::FEventContext& EventContext, TRingBuffer<FString>& PathResults, Impl::FInterruptionContext& InOutInterruptionContext, TOptional<TSet<FString>>& MountPointsForVerifyAfterGather);` — Called every tick when data is retrieved by the background path search. If TickStartTime is < 0, the entire list of gathered assets will be cached. Also used in sychronous searches
- L484 _private prototype_ `void DependencyDataGathered(TMultiMap<FName, FPackageDependencyData>& DependsResults, TMultiMap<FName, FPackageDependencyData>& OutDeferredDependencyResults, TSet<FName>* OutPackagesNeedingDependencyCalculation, Impl::FInterruptionContext& InOutInterruptionContext, TOptional<TSet<FString>>& MountPointsForVerifyAfterGather);` — Called every tick when data is retrieved by the background dependency search
- L490 _private prototype_ `void CookedPackageNamesWithoutAssetDataGathered(Impl::FEventContext& EventContext, TRingBuffer<FString>& CookedPackageNamesWithoutAssetDataResults, Impl::FInterruptionContext& InOutInterruptionContext);` — Called every tick when data is retrieved by the background search for cooked packages that do not contain asset data
- L494 _private prototype_ `void VerseFilesGathered(Impl::FEventContext& EventContext, TRingBuffer<FName>& VerseResults, Impl::FInterruptionContext& InOutInterruptionContext);` — Called every tick when data is retrieved by the background dependency search
- L497 _private prototype_ `void AddAssetData(Impl::FEventContext& EventContext, FAssetData* AssetData);` — Adds the asset data to the lookup maps
- L500 _private prototype_ `void UpdateAssetData(Impl::FEventContext& EventContext, FAssetData* AssetData, FAssetData&& NewAssetData, bool bKeepDeletedTags);` — Updates an existing asset data with the new value and updates lookup maps
- L503 _private prototype_ `void AddNonOverlappingTags(Impl::FEventContext& EventContext, FAssetData& ExistingAssetData, const FAssetData& NewAssetData);` — Updates the tags on an existing asset data by adding the tags from NewAssetData that do not already exist.
- L507 _private prototype_ `bool RemoveAssetData(Impl::FEventContext& EventContext, FAssetData* AssetData);` — Removes the asset data from the lookup maps. Returns true if it was removed, false if it already did not exist.
- L510 _private prototype_ `bool RemoveAssetDatas(Impl::FEventContext& EventContext, TArrayView<FAssetData*> AssetDatas);` — Removes a set of asset data from the lookup maps. Returns true if any were removed, false if all already did not exist.
- L514 _private prototype_ `FAssetData* ResolveAssetIdCollision(FAssetData& A, FAssetData& B);` — Called when two assets have the same ID but different packages. Logs it and returns which one to keep.
- L522 _private prototype_ `bool TryPostLoadAssetRegistryTags(FAssetData* AssetData, EDeferFlag DeferFlag, FTopLevelAssetPath& OutRequestedGameThreadClass);` — Calls PostLoadAssetRegistryTags on the CDO of the asset class this data represents. @param AssetData Existing asset data @param OutRequestedGameThreadClass If the postload fails because a class needs processing on the gamethread, this variable receives the classname. Otherwise it is empty. @return Returns false if required UClass data is not yet available and we are not forced to complete.
- L526 _private prototype_ `void RebuildAssetDependencyGathererMapIfNeeded();` — If new gatherers were registered, this call will refresh the mapping
- L529 _private prototype_ `void ResolveRedirectionsInCachedBPInheritanceMap();` — When the scan is completed, resolve the redirections in CachedBPInheritanceMap.
- L532 _private prototype_ `void GetSubClasses_Recursive(Impl::FClassInheritanceContext& InheritanceContext, FTopLevelAssetPath InClassName, TSet<FTopLevelAssetPath>& SubClassNames, TSet<FTopLevelAssetPath>& ProcessedClassNames, const TSet<FTopLevelAssetPath>& ExcludedClassNames) const;`
- L536 _private prototype_ `void CachePathsFromState(Impl::FEventContext& EventContext, const FAssetRegistryState& InState, const FAssetRegistrySerializationOptions* Options = nullptr);` — Internal helper which processes a given state and adds its contents to the current registry
- L540 _private prototype_ `void AddCachedBPClassParent(const FTopLevelAssetPath& ClassPath, const FTopLevelAssetPath& NotYetRedirectedParentPath);` — Adds ClassPath-> ParentPath to CachedBPInheritanceMap. Applies CoreRedirects to NotYetRedirectedParentPath.
- L543 _private prototype_ `void UpdateInheritanceBuffer(Impl::FClassInheritanceBuffer& OutBuffer) const;` — Updates OutBuffer from loaded classes and registered-in-CachedBPInheritanceMap blueprint classes
- L546 _private prototype_ `void ConsumeOrDeferPreloadedPremade(UAssetRegistryImpl& UARI, Impl::FEventContext& EventContext, Impl::FActiveMountEvents& ActiveMountEvents, FInterfaceWriteScopeLock& ProofOfWriteLock);` — Conditionally loads the Premade AssetRegistry from disk, or queues it for asynchronous loading if not yet loaded.
- L549 _private prototype_ `void LoadPremadeAssetRegistry(UAssetRegistryImpl& UARI, Impl::FEventContext& Context, Impl::FActiveMountEvents& ActiveMountEvents, FInterfaceWriteScopeLock& ProofOfWriteLock, Premade::ELoadResult LoadResult, Impl::FAssetProviderInitData&& StateInitData);` — Moves a premade asset registry state into this AR
- L553 _private prototype_ `void UpdatePersistentMountPoints();` — Add MountPoints of all AssetDatas currently registered in this->State to the list of PersistentMountPoints.
- L554 _private prototype_ `void OnInitialSearchCompleted(Impl::FEventContext& EventContext);`
- L555 _private prototype_ `void OnAdditionalMountSearchCompleted(Impl::FEventContext& EventContext);`
- L561 _private prototype_ `bool ClassRequiresGameThreadProcessing(const UClass* Class) const;`
- L568 _private function_ `TUniquePtr<FAssetDataGatherer>& AccessGlobalGatherer()` — This exists purely for use during shutdown to enable the UAssetRegistryImpl to avoid waiting for the gatherer to terminate while holding the interface lock. See UAssetRegistryImpl::OnEnginePreExit
- L570 _private prototype_ `void UpdateMaxSecondsPerFrame();`
- L573 _private prototype_ `void Shrink();` — Free slack memory accumulated by the asset registry.
- L577 _private member_ `FAssetRegistryState State;` — Internal state of the cached asset registry
- L580 _private member_ `TSet<FName> CachedVerseFiles;` — Database of known Verse files
- L581 _private member_ `TMap<FName, TArray<FName>> CachedVerseFilesByPath;`
- L584 _private member_ `FAssetRegistrySerializationOptions SerializationOptions;` — Default options used for serialization
- L585 _private member_ `FAssetRegistrySerializationOptions DevelopmentSerializationOptions;`
- L588 _private member_ `TSet<FName> CachedEmptyPackages;` — The set of empty package names (packages which contain no assets but have not yet been saved)
- L591 _private member_ `TMap<FTopLevelAssetPath, FTopLevelAssetPath> CachedBPInheritanceMap;` — The map of classes to their parents, only full for offline blueprints
- L594 _private member_ `Impl::FFilterTagRules CachedParsedFilterRules;` — Helper container to resolve filter rules
- L597 _private member_ `bool bIsTempCachingEnabled;` — If true, search caching is enabled
- L600 _private member_ `bool bIsTempCachingAlwaysEnabled;` — If true, search caching is enabled permanently
- L603 _private member_ `Impl::FClassInheritanceBuffer TempCachedInheritanceBuffer;` — Persistent InheritanceBuffer used when SetTemporaryCachingMode is on
- L605 _private member_ `uint64 SavedGeneratorClassesVersionNumber;`
- L606 _private member_ `uint64 SavedAllClassesVersionNumber;`
- L609 _private member_ `FPathTree CachedPathTree;` — The tree of known cached paths that assets may reside within
- L612 _private member_ `TUniquePtr<FAssetDataGatherer> GlobalGatherer;` — Async task that gathers asset information from disk
- L615 _private member_ `UE::AssetDataGather::FResults BackgroundResults;` — Lists of results from the gatherer thread that are waiting to get processed
- L618 _private member_ `TMultiMap<FName, TUniquePtr<FAssetData>> DeferredAssets;` — Assets and dependencies that are not ready for processing because they can't yet run PostLoadAssetRegistrytags
- L619 _private member_ `TMultiMap<FName, TUniquePtr<FAssetData>> DeferredAssetsForGameThread;`
- L620 _private member_ `TMultiMap<FName, FPackageDependencyData> DeferredDependencies;`
- L621 _private member_ `TMultiMap<FName, FPackageDependencyData> DeferredDependenciesForGameThread;`
- L623 _private member_ `TSet<FTopLevelAssetPath> GameThreadRequestedClasses;` — Classes that some of the AssetsForGameThread need processed on the gamethread before a retry.
- L624 _private member_ `FCriticalSection GameThreadRequestedClassesLock;`
- L626 _private member_ `std::atomic<bool> bGameThreadRequestedClassesShouldRetry{ false };` — Sentry values read by gamethread and gatherthread to performantly coordinate on GameThreadRequestedClasses.
- L627 _private member_ `std::atomic<bool> bGameThreadRequestedClassesShouldProcess{ false };`
- L631 _private member_ `TMap<FTopLevelAssetPath, int64> TagSizeByClass;` — Memory profiling information: How much memory is being used by the tags for each class.
- L638 _private member_ `TSet<FName> PersistentMountPoints;` — MountPoints, in the format of LongPackageName with no trailing slash, that should not have their AssetDatas removed even if the MountPoint is dismounted.
- L641 _private member_ `float StoreGatherResultsTimeSeconds;` — Time spent processing Gather results
- L643 _private member_ `int32 HighestPending = 0;` — The highest number of pending results observed during initial gathering
- L646 _private member_ `double InitialSearchStartTime = 0.0f;` — Time the initial async search was started
- L648 _private member_ `double AdditionalMountSearchStartTime = 0.0f;` — Time the additional mount async search was started
- L650 _private member_ `bool bInitialSearchStarted = false;` — Flag to indicate if we used an initial async search
- L652 _private member_ `bool bInitializationComplete = false;` — Flag to indicate Initialize() has run to completion
- L656 _private member_ `std::atomic<bool> bInitialSearchCompleted;` — Flag to indicate if the initial background search has completed. All access are relaxed because the actual search data can only be accessed under a proper lock.
- L660 _private member_ `std::atomic<bool> bAdditionalMountSearchInProgress;` — Flag to indicate if an additional mount background search has started after the initial search. All access are relaxed because the actual search data can only be accessed under a proper lock.
- L665 _private member_ `bool bPreloadingComplete = false;` — Flag to indicate PreloadingComplete; finishing the background search is blocked until preloading complete because preloading can add assets.
- L667 _private member_ `Impl::EGatherStatus GatherStatus;` — Status of the background search, so we can take actions when it changes to or from idle
- L669 _private member_ `Impl::EPerformanceMode PerformanceMode;` — What kind of performance mode this is in, used to optimize for initial loading vs runtime
- L675 _private member_ `bool bVerifyMountPointAfterGather;` — Enables extra check to make sure path still mounted before adding. Removing mount point can happen between scan (background thread + multiple ticks and the add).
- L678 _private member_ `bool bSearchAllAssets;` — Record whether SearchAllAssets has been called; if so we will also search new mountpoints when added
- L680 _private member_ `bool bVerboseLogging;`
- L682 _private member_ `bool bForceCompletionEvenIfClassNotLoaded = false;`
- L683 _private member_ `bool bForceCompletionEvenIfNotOnGameThread = false;`
- L684 _private member_ `bool bProcessedAnyAssetsAfterRetryDeferred = true;`
- L685 _private member_ `float MaxSecondsPerFrame = 0.04f;`
- L688 _private member_ `TSet<FTopLevelAssetPath> ClassGeneratorNames;` — List of all class names derived from Blueprint (including Blueprint itself)
- L700 _private member_ `TArray<FAssetRegistryPackageRedirect> PackageRedirects;`
- L707 _private member_ `TSet<FName> PackagesNeedingDependencyCalculation;` — The set of object paths that have had their dependencies gathered since the last idle, and that need to check for calculated dependencies at the next idle.
- L708 _private member_ `TSet<FName> PackagesNeedingDependencyCalculationOnGameThread;`
- L711 _private member_ `TSet<FSoftObjectPath> AssetDataObjectPathsUpdatedOnLoad;` — The set of object paths that have had their disk cache updated from the in memory version
- L718 _private member_ `TMap<FString, TSet<FName>> PackagesWatchingDirectory;` — A bidirectional map of which directories are watched by which packages for CalculatedDependencies. When a directory updates we need to rerun CalculatedDependencies for every package watching the directory. When a package runs CalculatedDependencies, we need to clear all of its watched files.
- L719 _private member_ `TMap<FName, TArray<FString>> DirectoriesWatchedByPackage;`
- L725 _private member_ `uint32 BackgroundTickInterruptionsCount = 0;` — Number of times during the startup scan that TickOnBackgroundThread was interrupted by a request for the AssetRegistry's lock from another thread.
- L726 _private member_ `std::atomic<bool> bGameThreadTakeOverGatherEachTick;`
- L729 _private member_ `TMultiMap<FTopLevelAssetPath, UE::AssetDependencyGatherer::Private::FRegisteredAssetDependencyGatherer*> RegisteredDependencyGathererClasses;` — A map of per asset class dependency gatherer called in LoadCalculatedDependencies
- L730 _private member_ `mutable FRWLock RegisteredDependencyGathererClassesLock;`
- L731 _private member_ `bool bRegisteredDependencyGathererClassesDirty;`
- L733 _private member_ `bool bGatherNeedsApplyObjectRedirects = false;`
- L736 _private member_ `mutable FRWLock SkipClassesLock;`
- L738 _private member_ `TSet<FTopLevelAssetPath> SkipUncookedClasses;` — Class names that return true for IsAsset but which should not be treated as assets in uncooked packages
- L740 _private member_ `TSet<FTopLevelAssetPath> SkipCookedClasses;` — Class names that return true for IsAsset but which should not be treated as assets in cooked packages
- L742 _private member_ `UE::AssetRegistry::Premade::FAsyncConsumer AsyncConsumer;`
- L748 _private member_ `TUniquePtr<UE::AssetRegistry::DependsNode::FGatherDependencyDataScratchpad> GatherDependencyDataScratchPad = nullptr;`
- L1049 _function_ `inline uint32& FAssetRegistryImpl::GetBackgroundTickInterruptionsCount()`
- L1054 _function_ `inline bool FAssetRegistryImpl::IsGameThreadTakeOverGatherEachTick() const`
- L1059 _function_ `inline void FAssetRegistryImpl::SetGameThreadTakeOverGatherEachTick(bool bValue)`

#### struct `UE::AssetRegistry::FAssetRegistryImpl::FAssetRegistryPackageRedirect`  
`struct FAssetRegistryPackageRedirect`  
_L690-699_
- L693 _public function_ `FAssetRegistryPackageRedirect(const FString& InSourcePackageName, const FString& InDestPackageName) : SourcePackageName(InSourcePackageName), DestPackageName(InDestPackageName)`
- L697 _public member_ `FString SourcePackageName;`
- L698 _public member_ `FString DestPackageName;`

#### struct `UE::AssetRegistry::Impl::FEventContext`  
`struct FEventContext`  
_L759-787_
- desc: Stores events that need to be broadcasted from the AssetRegistry; these events are added to by functions within a lock, and are broadcast after the lock is dropped. The broadcast is also deferred until on the GameThread.
- L770 _public member_ `TOptional<IAssetRegistry::FFileLoadProgressUpdateData> ProgressUpdateData;`
- L771 _public member_ `TArray<TPair<FString, EEvent>> PathEvents;`
- L772 _public member_ `TArray<TPair<FAssetData, EEvent>> AssetEvents;`
- L773 _public member_ `TArray<TPair<FName, EEvent>> VerseEvents;`
- L774 _public member_ `TArray<FString> RequiredLoads;`
- L775 _public member_ `TArray<FString> BlockedFiles;`
- L776 _public member_ `bool bFileLoadedEventBroadcast = false;`
- L777 _public member_ `bool bScanStartedEventBroadcast = false;`
- L778 _public member_ `bool bHasSentFileLoadedEventBroadcast = false;`
- L779 _public member_ `bool bKnownGathersCompleteEventBroadcast = false;`
- L782 _public prototype_ `void Clear();` — Remove all stored events
- L784 _public prototype_ `bool IsEmpty() const;` — Report whether this context has any stored events
- L786 _public prototype_ `void Append(FEventContext&& Other);` — Add all events from other onto this context's collection of events

#### enum `UE::AssetRegistry::Impl::FEventContext::EEvent`  
`enum class EEvent : uint32`  
_L761-769_
- L763 _public enumerator_ `Added`
- L764 _public enumerator_ `Removed`
- L765 _public enumerator_ `Updated`
- L766 _public enumerator_ `UpdatedOnDisk`
- L768 _public enumerator_ `MAX`

#### struct `UE::AssetRegistry::Impl::FClassInheritanceContext`  
`struct FClassInheritanceContext`  
_L795-817_
- desc: An accessor for the inheritance map and related data for functions that need them; the source of this data is an internal detail unneeded by the functions reading it. Readers of the data call ConditionalUpdate to ensure it is up to date before reading it.
- L798 _public member_ `FClassInheritanceBuffer* Buffer = nullptr;` — The Buffer providing the data for this context.
- L800 _public member_ `FClassInheritanceBuffer* StackBuffer = nullptr;` — The stack allocated Buffer which may be used to provide data for this context.
- L802 _public member_ `FAssetRegistryImpl* AssetRegistryImpl = nullptr;` — Back pointer to the AssetRegistryImpl to update the Buffer if necessary
- L804 _public member_ `bool bInheritanceMapUpToDate = false;` — Whether ConditionalUpdate needs to update inheritance data
- L806 _public member_ `bool bCodeGeneratorClassesUpToDate = false;` — Whether ConditionalUpdate needs to update code generate classes before it can update inheritance data
- L809 _public prototype_ `void BindToBuffer(FClassInheritanceBuffer& InBuffer, FAssetRegistryImpl& InAssetRegistryImpl, bool bInInheritanceMapUpToDate, bool bInCodeGeneratorClassesUpToDate);` — Set the context to use the data from the given buffer
- L812 _public prototype_ `void ConditionalUpdate();` — Update the backing buffer if it is out of date
- L814 _public prototype_ `void SelectBuffer(FAssetRegistryImpl& GuardedData, uint64 CurrentGeneratorClassesVersionNumber, uint64 CurrentAllClassesVersionNumber);` — Selects and binds a FClassInheritanceBuffer buffer to be used by this context.
- L816 _public prototype_ `void OnLockReentered(FAssetRegistryImpl& GuardedData);` — Updates the context after the InterfaceLock has been unlocked and locked while the context is in use.

#### struct `UE::AssetRegistry::Impl::FScanPathContext`  
`struct FScanPathContext`  
_L820-840_
- desc: Context to transform, collect, and pass along ScanPathsSynchronous arguments and results
- L822 _public prototype_ `FScanPathContext(FEventContext& InEventContext, FClassInheritanceContext& InInheritanceContext, const TArray<FString>& InDirs, const TArray<FString>& InFiles, UE::AssetRegistry::EScanFlags InScanFlags = UE::AssetRegistry::EScanFlags::None, TArray<FSoftObjectPath>* FoundAssets = nullptr);`
- L827 _public member_ `TArray<FString> PackageDirs;`
- L828 _public member_ `TArray<FString> LocalDirs;`
- L829 _public member_ `TSet<FString> PackageFiles;`
- L830 _public member_ `TArray<FString> LocalFiles;`
- L831 _public member_ `TArray<FString> LocalPaths;`
- L832 _public member_ `FEventContext& EventContext;`
- L833 _public member_ `FClassInheritanceContext& InheritanceContext;`
- L834 _public member_ `TArray<FSoftObjectPath>* OutFoundAssets = nullptr;`
- L835 _public member_ `int32 NumFoundAssets = 0;`
- L836 _public member_ `bool bForceRescan = false;`
- L837 _public member_ `bool bIgnoreDenyListScanFilters = false;`
- L838 _public member_ `bool bIgnoreInvalidPathWarning = false;`
- L839 _public member_ `EGatherStatus Status = EGatherStatus::TickActiveGatherActive;`

#### struct `UE::AssetRegistry::Impl::FTickContext`  
`struct FTickContext`  
_L843-906_
- desc: Input and output variables for the TickGatherer function.
- L846 _public prototype_ `FTickContext(FAssetRegistryImpl& InGuardedData, Impl::FEventContext& InEventContext, Impl::FClassInheritanceContext& InInheritanceContext);`
- L850 _public prototype_ `void LazyStartTimer();` — Start the timer to measure time spent in the current call to TickGatherer, if not already started.
- L855 _public prototype_ `void RecordTimer();` — Record the time that was spent in the current call to TickGatherer onto the metric for it on GuardedData, if LazyStartTimer has been called and RecordTimer has not already been called.
- L862 _public prototype_ `int32 GetNumPending();` — Return progress-bar metric for how many elements remain in the various lists of work to do. A portion of this calculation is cached (the GetNumGatherFromDiskPending) and it will not get the most up to date data until SetNumGatherFromDiskPendingDirty is called.
- L868 _public prototype_ `int32 GetNumGatherFromDiskPending();` — Return the portion of GetNumPending that is handled during gathering from disk; does not include the calculations that we do once the gather from disk is done. This function is cached, it does not redo the calculation until SetNumPendingDirty is called.
- L870 _public prototype_ `void SetNumGatherFromDiskPendingDirty();` — Invalidate the cache in GetNumGatherFromDiskPending
- L872 _public prototype_ `int32 CalculateNumGatherFromDiskPending();` — Run the expression to calculate the value used in GetNumGatherFromDiskPending.
- L878 _public prototype_ `EGatherStatus SetIntermediateStatus(EGatherStatus Status);` — Store the result of TickGatherer in the AssetRegistry's status variable and send the progress event. Returns the input Status so it can be used in a return line.
- L883 _public prototype_ `EGatherStatus UpdateIntermediateStatus();` — Calculate the result of TickGatherer from the current gather data on the TickContext and call SetIntermediateStatus. Returns the input Status so it can be used in a return line.
- L886 _public prototype_ `void RunAssetSearchDataGathered(TMultiMap<FName, TUniquePtr<FAssetData>>& InAssetResults, TMultiMap<FName, TUniquePtr<FAssetData>>& OutDeferredAssetResults);`
- L888 _public prototype_ `void RunDependencyDataGathered(TMultiMap<FName, FPackageDependencyData>& DependenciesToProcess, TMultiMap<FName, FPackageDependencyData>& OutDeferredDependencies, TSet<FName>* OutPackagesNeedingDependencyCalculation);`
- L893 _public member_ `UE::AssetDataGather::FResultContext ResultContext;`
- L894 _public member_ `Impl::FInterruptionContext InterruptionContext;`
- L895 _public member_ `FAssetRegistryImpl& GuardedData;`
- L896 _public member_ `Impl::FEventContext& EventContext;`
- L897 _public member_ `Impl::FClassInheritanceContext& InheritanceContext;`
- L898 _public member_ `TOptional<TSet<FString>> MountPointsForVerifyAfterGather;`
- L899 _public member_ `double TimingStartTime = -1.;`
- L900 _public member_ `int32 NumGatherFromDiskPending = 0;`
- L901 _public member_ `bool bHandleCompletion = false;`
- L902 _public member_ `bool bHandleDeferred = false;`
- L903 _public member_ `bool bNumGatherFromDiskPendingDirty = true;`
- L904 _public member_ `bool bHadAssetsToProcess = false;`
- L905 _public member_ `bool bIsInGameThread = false;`

#### enum `UE::AssetRegistry::Utils::EFilterMode`  
`enum class EFilterMode : uint8`  
_L914-920_
- desc: Different modes for RunAssetThroughFilter and related filter functions
- L917 _public enumerator_ `Inclusive` — Include things that pass the filter; include everything if the filter is empty
- L919 _public enumerator_ `Exclusive` — Exclude things that pass the filter; exclude nothing if the filter is empty

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L34 _namespace_ `namespace DependsNode` (scope `UE::AssetRegistry`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L35 _namespace_ `namespace Premade` (scope `UE::AssetRegistry`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L36 _namespace_ `namespace Premade` (scope `UE::AssetRegistry`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L37 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L38 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L39 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L40 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L41 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L42 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L43 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace AssetDependencyGatherer` (scope `UE`)
- L45 _namespace_ `namespace Private` (scope `UE::AssetDependencyGatherer`)
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L51 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L186 _function_ `FORCEINLINE bool IsTickActive(UE::AssetRegistry::Impl::EGatherStatus Status)` — Returns true if ANY work remains to be done. This work might require the game thread.
- L193 _namespace_ `namespace UE`
- L193 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L751 _namespace_ `namespace Impl` (scope `UE::AssetRegistry`)
- L910 _namespace_ `namespace Utils` (scope `UE::AssetRegistry`)
- L923 _prototype_ `bool IsFilterValid(const FARCompiledFilter& Filter);` (scope `UE::AssetRegistry::Utils`) — Report whether the external-code-created filter is in a state that is safe to use in filtering
- L925 _prototype_ `bool RunAssetThroughFilter(const FAssetData& AssetData, const FARCompiledFilter& Filter, const EFilterMode FilterMode);` (scope `UE::AssetRegistry::Utils`) — Report whether the given AssetData passes/fails the given filter
- L927 _prototype_ `bool RunAssetThroughFilter_Unchecked(const FAssetData& AssetData, const FARCompiledFilter& Filter, const bool bPassFilterValue);` (scope `UE::AssetRegistry::Utils`) — Helper for RunAssetThroughFilter and RunAssetsThroughFilter that skips validity check
- L933 _prototype_ `void RunAssetsThroughFilter(TArray<FAssetData>& AssetDataList, const FARCompiledFilter& Filter, const EFilterMode FilterMode);` (scope `UE::AssetRegistry::Utils`) — Given an array of asset data, trim the items that fail the filter based on the inclusion/exclusion mode used. - In inclusive mode it will remove all assets that fail the filter, and in exclusive mode it will remove all assets that pass the filter. - If the filter is empty, then the array will be untouched.
- L939 _prototype_ `void InitializeSerializationOptionsFromIni( FAssetRegistrySerializationOptions& Options, Impl::FFilterTagRules* OutRules, const ITargetPlatform* TargetPlatform = nullptr, ESerializationTarget Target = ESerializationTarget::ForGame, bool bSuppressWarnings = false);` (scope `UE::AssetRegistry::Utils`) — This will always read the ini, public version may return cache. if OutRules is nullptr, no tags will be filtered.
- L950 _prototype_ `bool HasEngineModuleLoaded();` (scope `UE::AssetRegistry::Utils`) — Returns the status of Engine module existance. Used to suppress emitting warnings about missing Engine classes.
- L957 _prototype_ `void UpdateSerializationOptions( FAssetRegistrySerializationOptions& InOutOptions, Impl::FFilterTagRules& InOutFilterRules, bool bSuppressWarnings);` (scope `UE::AssetRegistry::Utils`) — Updates FAssetRegistrySerializationOptions filters with the information based on runtime classes. Options are parsed based on class name and need to be resolved using the class hierarchy, and since the class hierarchy can change during startup we may need to reexecute the resolve.
- L966 _prototype_ `TMap<FName, Impl::FParsedFilterTagRules> ParseFilterTags(const TArray<FString>& FilterListItems, bool bIsFilteringDevelopmentAR, bool bUseAllowListInsteadOfDenyList);` (scope `UE::AssetRegistry::Utils`) — Parses the list of CookedTagsBlacklist or CookedTagsWhitelist gathered from the INI. Returns a mapping from a tag to a list of rules. May contain unresolved rules.
- L972 _prototype_ `TMap<FTopLevelAssetPath, TSet<FName>> ResolveFilterTags(Impl::FFilterTagRules& InOutRules, bool bSuppressWarnings);` (scope `UE::AssetRegistry::Utils`) — Resolves and expands the list of rules to list of all derived loaded classes that satisfy those rules. Then transposes rules to a map with a class as a key and a list of tags as value.
- L975 _prototype_ `EAssetAvailability::Type GetAssetAvailability(const FAssetData& AssetData);` (scope `UE::AssetRegistry::Utils`) — Gets the current availability of an asset, primarily for streaming install purposes.
- L977 _prototype_ `float GetAssetAvailabilityProgress(const FAssetData& AssetData, EAssetAvailabilityProgressReportingType::Type ReportType);` (scope `UE::AssetRegistry::Utils`) — Gets an ETA or percentage complete for an asset that is still in the process of being installed.
- L979 _prototype_ `bool GetAssetAvailabilityProgressTypeSupported(EAssetAvailabilityProgressReportingType::Type ReportType);` (scope `UE::AssetRegistry::Utils`) — Returns if a given report type is supported on the current platform
- L981 _prototype_ `void PrioritizeAssetInstall(const FAssetData& AssetData);` (scope `UE::AssetRegistry::Utils`) — Hint the streaming installers to prioritize a specific asset for install.
- L989 _prototype_ `bool ReadAssetFile(FPackageReader& PackageReader, IAssetRegistry::FLoadPackageRegistryData& InOutData);` (scope `UE::AssetRegistry::Utils`) — Reads Asset file from a previously initialized package reader @param PackageReader	Previously initialized package reader that maps to the data to be read @param AssetDataList	List of the read asset data
- L992 _prototype_ `void InitializeMountPoints(TOptional<TSet<FString>>& InOutMountPoints);` (scope `UE::AssetRegistry::Utils`) — If InOutMountPoints is not already set, sets it and reads mount points into it from FPackageName.
- L1001 _prototype_ `bool IsPathMounted(const FString& Path, const TSet<FString>& MountPointsNoTrailingSlashes, FString& StringBuffer);` (scope `UE::AssetRegistry::Utils`) — Returns true if path belongs to one of the mount points provided @param	Path				Path to check if mounted, example "/MyPlugin/SomeAsset" @param	MountPointsNoTrailingSlashes		Mount points without the trailing slash. Example: "/MyPlugin" @param	StringBuffer		String buffer to avoid re-allocation performance hit when searching TSet
- L1008 _prototype_ `void EnumerateAllMemoryAssets(TSet<FName>& OutPackageNamesWithAssets, bool& bOutStopIteration, TFunctionRef<bool(FAssetData&&)> Callback);` (scope `UE::AssetRegistry::Utils`) — Iterate all UObjects where this->IsAsset and !ShouldSkipAsset, create an FAssetData for them and call the callback. Stores packagenames of all assets found in OutPackageNamesWithAssets for later filtering of on-disk assets. Stops iteration and sets bOutStopIteration=true iff the callback returns false.
- L1014 _prototype_ `void EnumerateMemoryAssetsHelper(const FARCompiledFilter& InFilter, TSet<FName>& OutPackageNamesWithAssets, bool& bOutStopIteration, TFunctionRef<bool(const UObject* Object, FAssetData&& PartialAssetData)> Callback, bool bSkipARFilteredAssets);` (scope `UE::AssetRegistry::Utils`) — Helper for EnumerateMemoryAssets* functions. Calls the given callback on all memory assets that pass the portion of the given filter that does not require tags, and passes in an FAssetData constructed from the UObject but missing tags. Fills in OutPackageNamesWithAssets with names of all packages tested.
- L1021 _prototype_ `void EnumerateMemoryAssets(const FARCompiledFilter& InFilter, TSet<FName>& OutPackageNamesWithAssets, bool& bOutStopIteration, UE::AssetRegistry::Private::FInterfaceRWLock& InterfaceLock, const FAssetRegistryState& GuardedDataState, TFunctionRef<bool(FAssetData&&)> Callback, bool bSkipARFilteredAssets);` (scope `UE::AssetRegistry::Utils`) — Call the given callback on all UObjects in memory that pass the given filter. Fills in OutPackageNamesWithAssets with names of all packages tested.
- L1030 _prototype_ `FString CreateStandardFilename(FStringView InPath);` (scope `UE::AssetRegistry`) — Normalization functions for paths. We require that normalized paths are case-insensitively string-identical for the same input path specification. e.g. all slashes must be replaced with forward-slashes. Special case: a leading \\ is left unreplaced, so //share will be seen as different than \\share.
- L1031 _prototype_ `FString CreateStandardFilename(const FString& InFilename);` (scope `UE::AssetRegistry`)
- L1033 _prototype_ `FString CreateStandardLongPackageNameDirectory(FStringView LongPackageName);` (scope `UE::AssetRegistry`) — Normalization for LongPackageNames that identify a directory. Ensures it ends with a trailing forward-slash.
- L1035 _prototype_ `FName CreateStandardLongPackageFNameNoTrailingSlash(FStringView LongPackageName);` (scope `UE::AssetRegistry`) — Normalization for LongPackageNames that should not end in a trailing slash.
- L1045 _namespace_ `namespace UE`
- L1045 _namespace_ `namespace AssetRegistry` (scope `UE`)

### `Source/Runtime/AssetRegistry/Private/AssetRegistryPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetRegistry, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetRegistry, Log, All);`

### `Source/Runtime/AssetRegistry/Private/CriticalSectionQueryable.h` (Private)


#### class `FCriticalSectionQueryable`  
`class FCriticalSectionQueryable`  
_L12-66_
- desc: A Critical Section with additional function to query whether it is locked on the current thread.
- L15 _public prototype_ `FCriticalSectionQueryable(const FCriticalSectionQueryable&) = delete;`
- L16 _public prototype_ `FCriticalSectionQueryable(FCriticalSectionQueryable&&) = delete;`
- L17 _public prototype_ `FCriticalSectionQueryable& operator=(const FCriticalSectionQueryable&) = delete;`
- L18 _public prototype_ `FCriticalSectionQueryable& operator=(FCriticalSectionQueryable&&) = delete;`
- L20 _public function_ `FCriticalSectionQueryable() : OwnerThreadId(0)`
- L25 _public function_ `void Lock()`
- L31 _public function_ `bool TryLock()`
- L41 _public function_ `void Unlock()`
- L48 _public function_ `bool IsLockedOnCurrentThread() const`
- L54 _private function_ `void SetOwner()`
- L59 _private function_ `void ClearOwner()`
- L64 _private member_ `FCriticalSection Inner;`
- L65 _private member_ `std::atomic<uint32> OwnerThreadId;`

#### class `FScopeLockQueryable`  
`class FScopeLockQueryable`  
_L71-106_
- desc: Identical to FScopeLock but works with an FCriticalSectionQueryable
- L74 _public prototype_ `FScopeLockQueryable() = delete;`
- L75 _public prototype_ `FScopeLockQueryable(const FScopeLockQueryable& InScopeLock) = delete;`
- L76 _public prototype_ `FScopeLockQueryable(FScopeLockQueryable&& InScopeLock) = delete;`
- L77 _public prototype_ `FScopeLockQueryable& operator=(FScopeLockQueryable& InScopeLock) = delete;`
- L78 _public prototype_ `FScopeLockQueryable& operator=(FScopeLockQueryable&& InScopeLock) = delete;`
- L80 _public function_ `FScopeLockQueryable(FCriticalSectionQueryable* InSynchObject) : SynchObject(InSynchObject)`
- L88 _public function_ `~FScopeLockQueryable()` — Destructor that performs a release on the synchronization object.
- L93 _public function_ `void Unlock()`
- L105 _private member_ `FCriticalSectionQueryable* SynchObject;` — Holds the synchronization object to aggregate and scope manage.

#### class `FThreadOwnerSection`  
`class FThreadOwnerSection`  
_L115-192_
- desc: Like a critical section: only a single thread can posess it at once. But provides a different API than a critical section to more flexibly interact with another critical section. With multiple normal critical sections they must be entered in the same order to prevent deadlocks. A ThreadOwnerSection is instead tested and claimed for ownership only while inside its collaborating critical section (called the AegisLock), and ownership can then continue to be held even after releasing the AegisLock.
- L118 _public function_ `bool TryTakeOwnership(FCriticalSectionQueryable& NotYetEnteredAegisLock)`
- L123 _public function_ `bool TryTakeOwnership(FCriticalSection& NotYetEnteredAegisLock)`
- L128 _public function_ `bool TryTakeOwnership(FScopeLockQueryable& AlreadyEnteredAegisScopeLock)`
- L132 _public function_ `bool TryTakeOwnership(FScopeLock& AlreadyEnteredAegisScopeLock)`
- L137 _public function_ `void ReleaseOwnershipChecked(FCriticalSectionQueryable& NotYetEnteredAegisLock)`
- L142 _public function_ `void ReleaseOwnershipChecked(FCriticalSection& NotYetEnteredAegisLock)`
- L147 _public function_ `void ReleaseOwnershipChecked(FScopeLockQueryable& AlreadyEnteredAegisScopeLock)`
- L151 _public function_ `void ReleaseOwnershipChecked(FScopeLock& AlreadyEnteredAegisScopeLock)`
- L156 _public function_ `bool IsOwned(FScopeLockQueryable& AlreadyEnteredAegisScopeLock) const`
- L160 _public function_ `bool IsOwned(FScopeLock& AlreadyEnteredAegisScopeLock) const`
- L165 _public function_ `bool IsOwnedByCurrentThread() const`
- L171 _private function_ `bool TryTakeOwnershipWithinLock()`
- L181 _private function_ `void ReleaseOwnershipCheckedWithinLock()`
- L190 _private member_ `std::atomic<uint32> OwnerThreadId{ 0 };` — OwnerThreadId can be checked while outside of the lock so it is an atomic to prevent dataraces.
- L191 _private member_ `bool bHasOwner = false;`

### `Source/Runtime/AssetRegistry/Private/DependsNode.h` (Private)


#### class `FDependsNode`  
`class FDependsNode`  
_L16-256_
- desc: Implementation of IDependsNode
- L19 _public typedef_ `typedef TArray<FDependsNode*> FDependsNodeList;`
- L20 _public member_ `static constexpr uint32 PackageFlagWidth = 3;`
- L21 _public member_ `static constexpr uint32 SearchableNameFlagWidth = 0;`
- L22 _public member_ `static constexpr uint32 ManageFlagWidth = 2;`
- L23 _public typedef_ `typedef TPropertyCombinationSet<PackageFlagWidth> FPackageFlagSet;`
- L24 _public member_ `static constexpr uint32 PackageFlagSetWidth = FPackageFlagSet::StorageBitCount;`
- L25 _public member_ `static constexpr uint32 SearchableNameFlagSetWidth = 0;`
- L26 _public typedef_ `typedef TPropertyCombinationSet<ManageFlagWidth> FManageFlagSet;`
- L27 _public member_ `static constexpr uint32 ManageFlagSetWidth = FManageFlagSet::StorageBitCount;`
- L30 _public prototype_ `FDependsNode();`
- L31 _public prototype_ `FDependsNode(const FAssetIdentifier& InIdentifier);`
- L32 _public prototype_ `void Empty();`
- L35 _public prototype_ `void PrintNode() const;` — Prints the dependencies and referencers for this node to the log
- L37 _public prototype_ `void PrintDependencies() const;` — Prints the dependencies for this node to the log
- L39 _public prototype_ `void PrintReferencers() const;` — Prints the referencers to this node to the log
- L41 _public prototype_ `void GetDependencies(TArray<FDependsNode*>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;` — Gets the list of dependencies for this node
- L45 _public prototype_ `void GetDependencies(TArray<FAssetIdentifier>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;` — Gets the list of dependency names for this node
- L48 _public prototype_ `void GetDependencies(TArray<FAssetDependency>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;`
- L52 _public prototype_ `void GetReferencers(TArray<FDependsNode*>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;` — Gets the list of referencers to this node
- L55 _public prototype_ `void GetReferencers(TArray<FAssetDependency>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;`
- L59 _public prototype_ `FName GetPackageName() const;` — Helper function to return GetIdentifier.PackageName.
- L61 _public prototype_ `const FAssetIdentifier& GetIdentifier() const;` — Returns the entire identifier
- L62 _public prototype_ `bool IsScriptPath() const;`
- L64 _public prototype_ `void SetIdentifier(const FAssetIdentifier& InIdentifier);` — Sets the entire identifier
- L66 _public prototype_ `void AddDependency(FDependsNode* InDependency, UE::AssetRegistry::EDependencyCategory InDependencyType, UE::AssetRegistry::EDependencyProperty InProperties);` — Add a dependency to this node
- L68 _public prototype_ `void GetPackageReferencers(TArray<TPair<FAssetIdentifier, FPackageFlagSet>>& OutReferencers);`
- L69 _public prototype_ `void AddPackageDependencySet(FDependsNode* InDependency, const FPackageFlagSet& PropertyCombinationSet);`
- L71 _public prototype_ `void AddReferencer(FDependsNode* InReferencer);` — Add a referencer to this node
- L73 _public prototype_ `void RemoveDependency(FDependsNode* InDependency, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All);` — Remove a dependency from this node
- L76 _public prototype_ `void RemoveReferencer(FDependsNode* InReferencer);` — Remove a referencer from this node
- L78 _public prototype_ `void RemoveReferencers(const TSet<FDependsNode*>& InReferencers);` — Remove a set of referencers from this node
- L80 _public prototype_ `void RefreshReferencers();` — Removes any referencers that no longer have this node as a dependency
- L81 _public prototype_ `bool ContainsDependency(const FDependsNode* InDependency, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;`
- L85 _public prototype_ `void ClearDependencies(UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All);` — Clear all dependency records from this node
- L86 _public prototype_ `void ClearReferencers();`
- L91 _public prototype_ `void RemoveManageReferencesToNode();` — Removes Manage dependencies on this node and clean up referencers array. Manage references are the only ones safe to remove at runtime.
- L93 _public prototype_ `void RemoveLinks(const TUniqueFunction<bool(const FDependsNode*)>& ShouldRemove);` — Remove all nodes from referencers and dependencies for which ShouldRemove returns true
- L95 _public function_ `void RemapLinks(const TMap<FDependsNode*, FDependsNode*>& OldNodeToNewNode)` — Replace nodes in referencers and dependencies with OldNodeToNewNode[Target]; remove any that remap to null.
- L104 _public prototype_ `void RemapLinks(const TUniqueFunction<FDependsNode* (FDependsNode*)>& Remapper);` — Replace nodes in referencers and dependencies with the Remapper[Target]; remove any that Remap to null.
- L106 _public prototype_ `void RemapDependencies(const TUniqueFunction<FDependsNode* (FDependsNode*)>& Remapper);` — Replace nodes in dependencies with the Remapper[Target]; remove any that Remap to null.
- L108 _public prototype_ `void RemapReferencers(const TUniqueFunction<FDependsNode* (FDependsNode*)>& Remapper);` — Replace nodes in referencers with the Remapper[Target]; remove any that Remap to null.
- L111 _public prototype_ `int32 GetConnectionCount() const;` — Returns number of connections this node has, both references and dependencies
- L113 _public prototype_ `SIZE_T GetAllocatedSize(void) const;` — Returns amount of memory used by the arrays
- L137 _public typedef_ `)> FIterateDependenciesCallback;`
- L142 _public prototype_ `void IterateOverDependencies(const FIterateDependenciesCallback& InCallback, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;` — Iterate over all the dependencies of this node, optionally filtered by the target node, category and query, and call the supplied lambda parameter on the record.
- L145 _public prototype_ `void IterateOverDependencies(const FIterateDependenciesCallback& InCallback, const FDependsNode* DependsNode, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;`
- L152 _public prototype_ `template <class T> void IterateOverReferencers(const T& InCallback) const;` — Iterate over all the referencers of this node and call the supplied lambda parameter on the referencer
- L154 _public prototype_ `void Reserve(int32 InNumPackageDependencies, int32 InNumNameDependencies, int32 InNumManageDependencies, int32 InNumReferencers);`
- L156 _public prototype_ `void Reserve(const FDependsNodeReservations& InReservations);`
- L157 _public prototype_ `void Reserve(const FDependsNode* Other);`
- L159 _public prototype_ `bool GetAllowShrinking() const;`
- L160 _public prototype_ `void SetAllowShrinking(bool bAllowShrinking);`
- L162 _public prototype_ `static uint8 PackagePropertiesToByte(UE::AssetRegistry::EDependencyProperty Properties);`
- L163 _public prototype_ `static UE::AssetRegistry::EDependencyProperty ByteToPackageProperties(uint8 Bits);`
- L164 _public prototype_ `static uint8 ManagePropertiesToByte(UE::AssetRegistry::EDependencyProperty Properties);`
- L165 _public prototype_ `static UE::AssetRegistry::EDependencyProperty ByteToManageProperties(uint8 Bits);`
- L178 _public prototype_ `void SerializeSave(FArchive& Ar, const TUniqueFunction<int32(FDependsNode*, bool)>& GetSerializeIndexFromNode, FSaveScratch& Scratch, const FAssetRegistrySerializationOptions& Options) const;`
- L188 _public prototype_ `template <bool bLatestVersion> void SerializeLoad(FArchive& Ar, const TUniqueFunction<FDependsNode* (int32)>& GetNodeFromSerializeIndex, FLoadScratch& Scratch, FAssetRegistryVersion::Type Version);`
- L192 _public prototype_ `void LegacySerializeLoad_BeforeFlags(FArchive& Ar, FAssetRegistryVersion::Type Version, FDependsNode* PreallocatedDependsNodeDataBuffer, int32 NumDependsNodes, bool bSerializeDependencies);`
- L195 _public prototype_ `bool IsDependencyListSorted(UE::AssetRegistry::EDependencyCategory Category) const;`
- L196 _public prototype_ `void SetIsDependencyListSorted(UE::AssetRegistry::EDependencyCategory Category, bool bValue);`
- L197 _public prototype_ `bool IsReferencersSorted() const;`
- L198 _public prototype_ `void SetIsReferencersSorted(bool bValue);`
- L203 _public prototype_ `bool IsScriptDependenciesInitialized() const;` — Returns true if an IsScriptPath() FDependsNode has been initialized. FDependsNodes that are not IsScriptPath() will always return false.
- L204 _public prototype_ `void SetIsScriptDependenciesInitialized(bool bValue);`
- L212 _private prototype_ `void PrintDependenciesRecursive(const FString& Indent, TSet<const FDependsNode*>& VisitedNodes) const;` — Recursively prints dependencies of the node starting with the specified indent. VisitedNodes should be an empty set at first which is populated recursively.
- L217 _private prototype_ `void PrintReferencersRecursive(const FString& Indent, TSet<const FDependsNode*>& VisitedNodes) const;` — Recursively prints referencers to the node starting with the specified indent. VisitedNodes should be an empty set at first which is populated recursively.
- L220 _private prototype_ `template <bool bLatestVersion> void SerializeLoad_PackageDependencies(FArchive& Ar, const TUniqueFunction<FDependsNode* (int32)>& GetNodeFromSerializeIndex, FLoadScratch& Scratch, FAssetRegistryVersion::Type Version);`
- L224 _private prototype_ `template <bool bLatestVersion> void SerializeLoad_NameDependencies(FArchive& Ar, const TUniqueFunction<FDependsNode* (int32)>& GetNodeFromSerializeIndex, FLoadScratch& Scratch, FAssetRegistryVersion::Type Version);`
- L228 _private prototype_ `template <bool bLatestVersion> void SerializeLoad_ManageDependencies(FArchive& Ar, const TUniqueFunction<FDependsNode* (int32)>& GetNodeFromSerializeIndex, FLoadScratch& Scratch, FAssetRegistryVersion::Type Version);`
- L232 _private prototype_ `template <bool bLatestVersion> void SerializeLoad_Referencers(FArchive& Ar, const TUniqueFunction<FDependsNode* (int32)>& GetNodeFromSerializeIndex, FLoadScratch& Scratch, FAssetRegistryVersion::Type Version);`
- L237 _private member_ `FAssetIdentifier Identifier;` — The name of the package/object this node represents
- L238 _private member_ `FDependsNodeList PackageDependencies;`
- L239 _private member_ `FDependsNodeList NameDependencies;`
- L240 _private member_ `FDependsNodeList ManageDependencies;`
- L241 _private member_ `FDependsNodeList Referencers;`
- L242 _private member_ `TBitArray<> PackageFlags;`
- L243 _private member_ `TBitArray<> ManageFlags;`
- L246 _private member_ `uint32 PackageIsSorted : 1 = 1;` — Transient flags that are not serialized
- L247 _private member_ `uint32 SearchableNameIsSorted : 1 = 1;`
- L248 _private member_ `uint32 ManageIsSorted : 1 = 1;`
- L249 _private member_ `uint32 ReferencersIsSorted : 1 = 1;`
- L250 _private member_ `uint32 DependenciesInitialized : 1 = 0;`
- L251 _private member_ `uint32 bScriptPath : 1 = 0;`
- L253 _private member_ `uint32 bAllowShrinking : 1 = 1;` — Used to control FDependsNodeList shrinking behaviour
- L285 _function_ `inline FDependsNode::FDependsNode()`
- L289 _function_ `inline FDependsNode::FDependsNode(const FAssetIdentifier& InIdentifier)`
- L294 _function_ `inline void FDependsNode::Empty()`
- L301 _function_ `inline FName FDependsNode::GetPackageName() const`
- L306 _function_ `inline const FAssetIdentifier& FDependsNode::GetIdentifier() const`
- L311 _function_ `inline bool FDependsNode::IsScriptPath() const`
- L316 _function_ `inline SIZE_T FDependsNode::GetAllocatedSize(void) const`
- L324 _function_ `template <class T> inline void FDependsNode::IterateOverReferencers(const T& InCallback) const`
- L332 _function_ `inline void FDependsNode::Reserve(int32 InNumPackageDependencies, int32 InNumNameDependencies, int32 InNumManageDependencies, int32 InNumReferencers)`
- L343 _function_ `inline void FDependsNode::Reserve(const FDependsNodeReservations& InReservations)`
- L349 _function_ `inline void FDependsNode::Reserve(const FDependsNode* Other)`
- L355 _function_ `inline bool FDependsNode::GetAllowShrinking() const`
- L360 _function_ `inline void FDependsNode::SetAllowShrinking(bool InAllowShrinking)`
- L365 _function_ `inline uint8 FDependsNode::PackagePropertiesToByte(UE::AssetRegistry::EDependencyProperty Properties)`
- L372 _function_ `inline UE::AssetRegistry::EDependencyProperty FDependsNode::ByteToPackageProperties(uint8 Bits)`
- L380 _function_ `inline uint8 FDependsNode::ManagePropertiesToByte(UE::AssetRegistry::EDependencyProperty Properties)`
- L386 _function_ `inline UE::AssetRegistry::EDependencyProperty FDependsNode::ByteToManageProperties(uint8 Bits)`

#### struct `FDependsNode::FSaveScratch`  
`struct FSaveScratch`  
_L167-177_
- L174 _public member_ `TArray<FSortInfo> SortInfos;`
- L175 _public member_ `TArray<int32> OutDependencies;`
- L176 _public member_ `TBitArray<> OutFlagBits;`

#### struct `FDependsNode::FSaveScratch::FSortInfo`  
`struct FSortInfo`  
_L169-173_
- L171 _public member_ `int32 SerializeIndex;`
- L172 _public member_ `int32 ListIndex;`

#### struct `FDependsNode::FLoadScratch`  
`struct FLoadScratch`  
_L180-186_
- L182 _public member_ `TArray<int32> InDependencies;`
- L183 _public member_ `TArray<uint32> InFlagBits;`
- L184 _public member_ `TArray<FDependsNode*> PointerDependencies;`
- L185 _public member_ `TArray<int32> SortIndexes;`

#### struct `FDependsNodeReservations`  
`struct FDependsNodeReservations`  
_L258-279_
- L260 _public member_ `int32 PackageDependenciesSize = 0;`
- L261 _public member_ `int32 NameDependenciesSize = 0;`
- L262 _public member_ `int32 ManageDependenciesSize = 0;`
- L263 _public member_ `int32 ReferencersSize = 0;`
- L265 _public prototype_ `FDependsNodeReservations() = default;`
- L266 _public function_ `FDependsNodeReservations(const FDependsNode& Node)`

#### Free symbols / members of external scopes

- L98 _function_ `` (scope `FDependsNode::RemapLinks`)
- L274 _function_ `friend FArchive& operator<<(FArchive& Ar, FDependsNodeReservations& Reservations)`

### `Source/Runtime/AssetRegistry/Private/DiskCachedAssetData.h` (Private)


#### enum `UE::AssetRegistry::Private::EOptionalBool`  
`enum class EOptionalBool : uint8`  
_L11-17_
- L13 _public enumerator_ `Unset`
- L14 _public enumerator_ `False`
- L15 _public enumerator_ `True`
- L16 _public enumerator_ `Max = EOptionalBool::True`

#### class `FDiskCachedAssetData`  
`class FDiskCachedAssetData`  
_L23-78_
- L26 _public member_ `FDateTime ModificationTime;` — Modification time of the asset last time it was discovered
- L27 _public member_ `FDateTime LastGatheredTime;` — The last time this asset was discovered during a scan
- L28 _public member_ `FName Extension;`
- L29 _public member_ `UE::AssetRegistry::Private::EOptionalBool HasMarkOfTheWeb = UE::AssetRegistry::Private::EOptionalBool::Unset;`
- L30 _public member_ `TArray<FAssetData> AssetDataList;`
- L31 _public member_ `FPackageDependencyData DependencyData;`
- L33 _public function_ `FDiskCachedAssetData()`
- L36 _public function_ `FDiskCachedAssetData(const FDateTime& InModificationTime, const FDateTime& InLastSeen, FName InExtension) : ModificationTime(InModificationTime) , LastGatheredTime(InLastSeen) , Extension(InExtension)`
- L47 _public function_ `template<class Archive> void SerializeForCache(Archive&& Ar)` — Serialize as part of the registry cache. This is not meant to be serialized as part of a package so  it does not handle versions normally To version this data change FAssetRegistryVersion or AssetDataGathererConstants::CacheSerializationMagic
- L71 _public function_ `SIZE_T GetAllocatedSize() const` — Returns the amount of memory allocated by this container, not including sizeof(*this).

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L20 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::AssetRegistry::Private::EOptionalBool& Value);`
- L21 _prototype_ `UE::AssetRegistry::Private::EOptionalBool BoolToOptionalBool(bool bValue);`
- L80 _function_ `inline FArchive& operator<<(FArchive& Ar, UE::AssetRegistry::Private::EOptionalBool& Value)`
- L92 _function_ `inline UE::AssetRegistry::Private::EOptionalBool BoolToOptionalBool(bool bValue)`

### `Source/Runtime/AssetRegistry/Private/NameTableArchive.h` (Private)


#### class `FNameTableArchiveReader`  
`class FNameTableArchiveReader : public FArchive`  
_L16-42_
- inherits: `FArchive`
- desc: Legacy name table reader replaced by FAssetRegistryReader. Has an FName table and names are serialized as table indices.
- L20 _public prototype_ `FNameTableArchiveReader(FArchive& WrappedArchive);` — Create a reader that wraps around an existing archive. Existing archive must support seek
- L23 _public prototype_ `virtual void Serialize(void* V, int64 Length) override;` — Farchive implementation to redirect requests to the wrapped archive
- L24 _public prototype_ `virtual bool Precache(int64 PrecacheOffset, int64 PrecacheSize) override;`
- L25 _public prototype_ `virtual void Seek(int64 InPos) override;`
- L26 _public prototype_ `virtual int64 Tell() override;`
- L27 _public prototype_ `virtual int64 TotalSize() override;`
- L28 _public prototype_ `virtual const FCustomVersionContainer& GetCustomVersions() const override;`
- L29 _public prototype_ `virtual void SetCustomVersions(const FCustomVersionContainer& NewVersions) override;`
- L30 _public prototype_ `virtual void ResetCustomVersions() override;`
- L31 _public prototype_ `virtual FArchive& operator<<(FName& Name);`
- L33 _public prototype_ `void SerializeTagsAndBundles(FAssetData& Out);`
- L34 _public prototype_ `void SerializeTagsAndBundlesOldVersion(FAssetData& Out, int32 Version);`
- L38 _private prototype_ `bool SerializeNameMap();` — Serializers for different package maps
- L40 _private member_ `FArchive* ProxyAr;`
- L41 _private member_ `TArray<FNameEntryId> NameMap;`

### `Source/Runtime/AssetRegistry/Private/NonBufferingReadOnlyArchive.h` (Private)


#### class `FNonBufferingReadOnlyArchive`  
`class FNonBufferingReadOnlyArchive : public FArchive`  
_L17-81_
- inherits: `FArchive`
- desc: This archive uses non-buffered IO to avoid overhead caused by reading into the OS cache manager rather than not reading into an archive owned buffer (it does that). It is intended to be used when reads will occur in parallel, contention would be caused at an OS level to allocate cache pages, and typically the whole file is not read sequentially but instead only a smaller portion of the file is needed (otherwise OS caching likely performs better since it can predict more accurately without waste). This archive is intended to be re-usable by opening new files on top so the internal buffer can be re-used.
- L20 _public prototype_ `FNonBufferingReadOnlyArchive(int64 InBufferSize = 4096, uint32 InFlags = 0);`
- L21 _public prototype_ `~FNonBufferingReadOnlyArchive();`
- L24 _public prototype_ `virtual void Seek(int64 InPos) override final;` — FArchive API
- L25 _public function_ `virtual int64 Tell() override final`
- L29 _public function_ `virtual int64 TotalSize() override final`
- L33 _public prototype_ `virtual bool Close() override final;`
- L34 _public prototype_ `virtual void Serialize(void* V, int64 Length) override final;`
- L35 _public function_ `virtual FString GetArchiveName() const override`
- L39 _public prototype_ `virtual bool Precache(int64 PrecacheOffset, int64 PrecacheSize) override;`
- L43 _public prototype_ `bool OpenFile(const TCHAR* InFilename);` — Open a new file to read with this archive. Any existing open file is closed and the archive is reset.
- L47 _protected prototype_ `bool InternalPrecache(int64 PrecacheOffset, int64 PrecacheSize);` — Populates the internal buffer to read from during Serialize.
- L54 _protected prototype_ `bool SeekLowLevel(int64 InPos);` — Platform specific seek @param InPos - Offset from beginning of file to seek to @return false on failure
- L57 _protected prototype_ `void OpenFileLowLevel(const TCHAR* InFilename);` — Open the file handle
- L60 _protected prototype_ `void CloseLowLevel();` — Close the file handle
- L63 _protected prototype_ `void ReadLowLevel(uint8* Dest, int64 CountToRead, int64& OutBytesRead);` — Platform specific read
- L66 _protected function_ `bool IsSilent() const` — Returns true if the archive should suppress logging in case of error
- L71 _protected member_ `FString Filename;`
- L72 _protected member_ `int64 Size;`
- L73 _protected member_ `int64 Pos;`
- L74 _protected member_ `int64 BufferBase;`
- L75 _protected member_ `TUniquePtr<IFileHandle> Handle;`
- L77 _protected member_ `uint8* Buffer;`
- L78 _protected member_ `int64 BufferReadAlignment;`
- L79 _protected member_ `int64 BufferSize;`
- L80 _protected member_ `uint32 Flags;`

### `Source/Runtime/AssetRegistry/Private/PackageDependencyData.h` (Private)


#### class `FPackageDependencyData`  
`class FPackageDependencyData`  
_L11-91_
- L18 _public function_ `friend FArchive& operator<<(FArchive& Ar, FPackageDependency& Dependency)`
- L37 _public function_ `friend FArchive& operator<<(FArchive& Ar, FSearchableNamesDependency& Dependency)`
- L45 _public member_ `TArray<FPackageDependency> PackageDependencies;` — Dependency Data
- L46 _public member_ `TArray<FSearchableNamesDependency> SearchableNameDependencies;`
- L48 _public member_ `FDependsNodeReservations DependsNodeReservations;`
- L51 _public member_ `FAssetPackageData PackageData;` — Asset Package data, gathered at the same time as dependency data
- L54 _public member_ `FName PackageName;` — The name of the package that dependency data is gathered from
- L57 _public member_ `bool bHasPackageData = false;` — Transient Flags indicating which types of data have been gathered
- L58 _public member_ `bool bHasDependencyData = false;`
- L64 _public function_ `void SerializeForCache(FArchive& Ar)` — Serialize as part of the registry cache. This is not meant to be serialized as part of a package so it does not handle versions normally To version this data change FAssetRegistryVersion or AssetDataGathererConstants::CacheSerializationMagic
- L73 _public prototype_ `void LoadDependenciesFromPackageHeader(FName PackageName, TConstArrayView<FObjectImport> ImportMap, TArray<FName>& SoftPackageReferenceList, TMap<FPackageIndex, TArray<FName>>& SearchableNames, TBitArray<>& ImportUsedInGame, TBitArray<>& SoftPackageUsedInGame, TArray<TPair<FName, UE::AssetRegistry::EExtraDependencyFlags>>& ExtraPackageDependencies);`
- L79 _public function_ `SIZE_T GetAllocatedSize() const` — Returns the amount of memory allocated by this container, not including sizeof(*this).
- L88 _private prototype_ `FName GetImportPackageName(TConstArrayView<FObjectImport> ImportMap, int32 ImportIndex);`

#### struct `FPackageDependencyData::FPackageDependency`  
`struct FPackageDependency`  
_L14-31_
- L16 _public member_ `FName PackageName;`
- L17 _public member_ `UE::AssetRegistry::EDependencyProperty Property;`
- L27 _public function_ `bool operator==(const FPackageDependency& Other) const`

#### struct `FPackageDependencyData::FSearchableNamesDependency`  
`struct FSearchableNamesDependency`  
_L32-42_
- L34 _public member_ `FName PackageName;`
- L35 _public member_ `FName ObjectName;`
- L36 _public member_ `TArray<FName> ValueNames;`

### `Source/Runtime/AssetRegistry/Private/PropertyCombinationSet.h` (Private)


#### class `TPropertyCombinationSet`  
`template<int BitWidth> class TPropertyCombinationSet`  
_L32-226_
- desc: TPropertyCombinationSet is a set of integers where the integers are bit fields for whether each of n independent properties are present. We refer to each element in the set as a corner; this term is derived from the model of a BitWidth-dimensional hypercube; each corner of the hypercube maps to one of the possible combinations of the bit field. TPropertyCombinationSet has another trait: redundant child corners are culled from the set. Corner B is a redundant child of Corner A if every property present in B is also present in A. The motivations for having a set of property bit fields, and culling the redundant child corners: 1) We need a set of property bit fields when a combination of properties in a single element is important to distinguish from multiple elements with those properties in isolation e.g. it is important to know whether we have (A) [(a not-used-in-game hard dependency) AND (a used-in-game soft dependency)] vs (B) [(a used-in-game hard dependency)] 2) We need to cull redundant child corners for performance, if we are allowed to. Minimizing the number of property combinations necessary to iterate over is important for performance of any calling iteration code We are allowed to eliminate redundant child corners when each property is an increasing superset - the behavior when the property is present is a superset of the behavior when the property is not present e.g. When we have a hard dependency, that means everything that having a soft dependency means, PLUS som
- L35 _public member_ `static constexpr uint32 StorageBitCount = 1 << BitWidth;`
- L36 _public member_ `static constexpr uint32 StorageWordCount = (StorageBitCount + NumBitsPerDWORD - 1) / NumBitsPerDWORD;`
- L37 _public member_ `static constexpr uint32 MaxValue = StorageBitCount - 1;`
- L40 _public function_ `TPropertyCombinationSet()`
- L47 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<BitWidth>& Other)`
- L53 _public function_ `TPropertyCombinationSet(const TBitArray<>& ArchivedBits, uint32 BitOffset = 0)`
- L59 _public function_ `void Load(const TBitArray<>& ArchiveBits, uint32 BitOffset)`
- L64 _public function_ `void Save(TBitArray<>& ArchiveBits, uint32 BitOffset) const`
- L69 _public function_ `void Load(const uint32* ArchiveBits)`
- L74 _public function_ `void Save(uint32* ArchiveBits) const`
- L82 _public function_ `void Add(uint32 PropertyCombination)` — Given a prospective PropertyCombination, add it to the PropertyCombinationSet if it is not a Redundant Combination of a PropertyCombination already in the Set. Once added, remove any now-redundant PropertyCombinations.
- L93 _public function_ `void AddRange(TPropertyCombinationSet<BitWidth>& Other)`
- L101 _public function_ `bool Contains(uint32 Value) const`
- L107 _public function_ `bool operator==(const TPropertyCombinationSet<BitWidth>& Other) const`
- L149 _public function_ `FIterator begin()`
- L153 _public function_ `FIterator end()`
- L159 _private function_ `void Construct()`
- L166 _private function_ `void AddNoCheck(uint32 Value)`
- L171 _private function_ `void RemoveNoCheck(uint32 Value)`
- L176 _private function_ `bool ContainsNoCheck(uint32 Value) const`
- L181 _private function_ `bool IsRedundantPropertyCombinationNoCheck(uint32 PropertyCombination) const`
- L186 _private function_ `bool IsRedundantPropertyCombinationRecursive(uint32 PropertyCombination, uint32 StartBit) const`
- L206 _private function_ `void RemoveRedundantPropertyCombinationsNoCheck(uint32 PropertyCombination)`
- L211 _private function_ `void RemoveRedundantPropertyCombinationsRecursive(uint32 PropertyCombination, uint32 StartBit)`
- L225 _private member_ `uint32 Storage[StorageWordCount];`
- L237 _public member_ `static constexpr uint32 BitWidth = 1;`
- L238 _public member_ `static constexpr uint32 StorageBitCount = 1;`
- L239 _public member_ `static constexpr uint32 StorageWordCount = 1;`
- L240 _public member_ `static constexpr uint32 MaxValue = 1;`
- L241 _public member_ `static constexpr uint32 NumPackedValues = 2;`
- L249 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<1>& Other)`
- L285 _public function_ `void AddRange(TPropertyCombinationSet<1>& Other)`
- L296 _public function_ `bool operator==(const TPropertyCombinationSet<1>& Other) const`
- L336 _private member_ `uint32 Storage;`

#### struct `TPropertyCombinationSet::FIterator`  
`struct FIterator`  
_L120-147_
- L123 _public function_ `FIterator& operator++()`
- L133 _public function_ `uint32 operator*()`
- L134 _public function_ `bool operator!=(const FIterator& Other) const`
- L138 _private function_ `FIterator(TPropertyCombinationSet& InArray, uint32 OneBeforeStart = (uint32)-1) : Array(InArray) , Value(OneBeforeStart)`
- L145 _private member_ `TPropertyCombinationSet& Array;`
- L146 _private member_ `uint32 Value;`
- L314 _private function_ `FIterator(TPropertyCombinationSet& InArray, int32 InIndex) : Array(InArray) , Index(InIndex)`
- L321 _private member_ `int32 Index;`

#### class `TPropertyCombinationSet`  
`template<> class TPropertyCombinationSet<1>`  
_L234-337_
- desc: For a TPropertyCombinationSet over bitfields with only a single bit, the possible sets of non-redundant corners are: [0] - the bit is not set [1] - the bit is set
- L35 _public member_ `static constexpr uint32 StorageBitCount = 1 << BitWidth;`
- L36 _public member_ `static constexpr uint32 StorageWordCount = (StorageBitCount + NumBitsPerDWORD - 1) / NumBitsPerDWORD;`
- L37 _public member_ `static constexpr uint32 MaxValue = StorageBitCount - 1;`
- L40 _public function_ `TPropertyCombinationSet()`
- L47 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<BitWidth>& Other)`
- L53 _public function_ `TPropertyCombinationSet(const TBitArray<>& ArchivedBits, uint32 BitOffset = 0)`
- L59 _public function_ `void Load(const TBitArray<>& ArchiveBits, uint32 BitOffset)`
- L64 _public function_ `void Save(TBitArray<>& ArchiveBits, uint32 BitOffset) const`
- L69 _public function_ `void Load(const uint32* ArchiveBits)`
- L74 _public function_ `void Save(uint32* ArchiveBits) const`
- L82 _public function_ `void Add(uint32 PropertyCombination)` — Given a prospective PropertyCombination, add it to the PropertyCombinationSet if it is not a Redundant Combination of a PropertyCombination already in the Set. Once added, remove any now-redundant PropertyCombinations.
- L93 _public function_ `void AddRange(TPropertyCombinationSet<BitWidth>& Other)`
- L101 _public function_ `bool Contains(uint32 Value) const`
- L107 _public function_ `bool operator==(const TPropertyCombinationSet<BitWidth>& Other) const`
- L149 _public function_ `FIterator begin()`
- L153 _public function_ `FIterator end()`
- L159 _private function_ `void Construct()`
- L166 _private function_ `void AddNoCheck(uint32 Value)`
- L171 _private function_ `void RemoveNoCheck(uint32 Value)`
- L176 _private function_ `bool ContainsNoCheck(uint32 Value) const`
- L181 _private function_ `bool IsRedundantPropertyCombinationNoCheck(uint32 PropertyCombination) const`
- L186 _private function_ `bool IsRedundantPropertyCombinationRecursive(uint32 PropertyCombination, uint32 StartBit) const`
- L206 _private function_ `void RemoveRedundantPropertyCombinationsNoCheck(uint32 PropertyCombination)`
- L211 _private function_ `void RemoveRedundantPropertyCombinationsRecursive(uint32 PropertyCombination, uint32 StartBit)`
- L225 _private member_ `uint32 Storage[StorageWordCount];`
- L237 _public member_ `static constexpr uint32 BitWidth = 1;`
- L238 _public member_ `static constexpr uint32 StorageBitCount = 1;`
- L239 _public member_ `static constexpr uint32 StorageWordCount = 1;`
- L240 _public member_ `static constexpr uint32 MaxValue = 1;`
- L241 _public member_ `static constexpr uint32 NumPackedValues = 2;`
- L249 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<1>& Other)`
- L285 _public function_ `void AddRange(TPropertyCombinationSet<1>& Other)`
- L296 _public function_ `bool operator==(const TPropertyCombinationSet<1>& Other) const`
- L336 _private member_ `uint32 Storage;`

#### struct `TPropertyCombinationSet::FIterator`  
`struct FIterator`  
_L301-322_
- L123 _public function_ `FIterator& operator++()`
- L133 _public function_ `uint32 operator*()`
- L134 _public function_ `bool operator!=(const FIterator& Other) const`
- L138 _private function_ `FIterator(TPropertyCombinationSet& InArray, uint32 OneBeforeStart = (uint32)-1) : Array(InArray) , Value(OneBeforeStart)`
- L145 _private member_ `TPropertyCombinationSet& Array;`
- L146 _private member_ `uint32 Value;`
- L314 _private function_ `FIterator(TPropertyCombinationSet& InArray, int32 InIndex) : Array(InArray) , Index(InIndex)`
- L321 _private member_ `int32 Index;`

#### class `TPropertyCombinationSetHardcoded`  
`template<typename PackerClass> class TPropertyCombinationSetHardcoded`  
_L341-527_
- L344 _public member_ `static constexpr uint32 BitWidth = PackerClass::BitWidth;`
- L345 _public member_ `static constexpr uint32 StorageBitCount = PackerClass::StorageBitCount;`
- L346 _public member_ `static constexpr uint32 StorageWordCount = 1;`
- L347 _public member_ `static constexpr uint32 MaxValue = (1 << BitWidth) - 1;`
- L348 _public member_ `static constexpr uint32 ArrayMax = PackerClass::ArrayMax;` — This value is analytically computable - n choose floor(n/2) - but we manually hardcode it rather than calculating it in the compiler
- L349 _public member_ `static constexpr uint32 NumPackedValues = PackerClass::NumPackedValues;`
- L351 _public function_ `TPropertyCombinationSetHardcoded()`
- L356 _public function_ `TPropertyCombinationSetHardcoded(const TPropertyCombinationSetHardcoded<PackerClass>& Other)`
- L361 _public function_ `TPropertyCombinationSetHardcoded(const TBitArray<>& ArchivedBits, uint32 BitOffset = 0)`
- L367 _public function_ `void Load(const TBitArray<>& ArchiveBits, uint32 BitOffset)`
- L372 _public function_ `void Save(TBitArray<>& ArchiveBits, uint32 BitOffset) const`
- L377 _public function_ `void Load(const uint32* ArchiveBits)`
- L382 _public function_ `void Save(uint32* ArchiveBits) const`
- L387 _public function_ `void Add(uint32 PropertyCombination)`
- L402 _public function_ `void AddRange(TPropertyCombinationSetHardcoded<PackerClass>& Other)`
- L430 _public function_ `bool Contains(uint32 Value) const`
- L446 _public function_ `bool operator==(const TPropertyCombinationSetHardcoded<PackerClass>& Other) const`
- L474 _public function_ `FIterator begin()`
- L481 _public function_ `FIterator end()`
- L492 _private function_ `static bool AddNonRedundant(const uint32* OldValues, const int OldNum, const uint32 AddingValue, uint32* NewValues, int& NewNum)`
- L526 _private member_ `uint32 Storage;`

#### struct `TPropertyCombinationSetHardcoded::FIterator`  
`struct FIterator`  
_L451-472_
- L454 _public function_ `FIterator& operator++()`
- L459 _public function_ `uint32 operator*()`
- L463 _public function_ `bool operator!=(const FIterator& Other) const`
- L467 _private prototype_ `FIterator() = default;`
- L469 _private member_ `const uint32* Values;`
- L470 _private member_ `int Num;`
- L471 _private member_ `int32 Index;`

#### class `FPropertyCombinationPack2`  
`class FPropertyCombinationPack2`  
_L534-574_
- desc: For a TPropertyCombinationSet over bitfields with two bits, there are 5 possible sets of non-redundant corners: { [00], [01], [10], [11], [01, 10] }
- L537 _public member_ `static constexpr uint32 BitWidth = 2;`
- L538 _public member_ `static constexpr uint32 StorageBitCount = 3;`
- L539 _public member_ `static constexpr uint32 ArrayMax = 2;`
- L540 _public member_ `static constexpr uint32 MaxValue = (1 << BitWidth) - 1;`
- L541 _public member_ `static constexpr uint32 NumPackedValues = 5;`
- L543 _public function_ `static void Unpack(const uint32 Compressed, const uint32*& OutValues, int& OutNum)`
- L560 _public function_ `static uint32 Pack(const uint32* Values, const int Num)`

#### class `TPropertyCombinationSet`  
`template<> class TPropertyCombinationSet<2> : public TPropertyCombinationSetHardcoded<FPropertyCombinationPack2>`  
_L576-580_
- inherits: `TPropertyCombinationSetHardcoded<FPropertyCombinationPack2>`
- L35 _public member_ `static constexpr uint32 StorageBitCount = 1 << BitWidth;`
- L36 _public member_ `static constexpr uint32 StorageWordCount = (StorageBitCount + NumBitsPerDWORD - 1) / NumBitsPerDWORD;`
- L37 _public member_ `static constexpr uint32 MaxValue = StorageBitCount - 1;`
- L40 _public function_ `TPropertyCombinationSet()`
- L47 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<BitWidth>& Other)`
- L53 _public function_ `TPropertyCombinationSet(const TBitArray<>& ArchivedBits, uint32 BitOffset = 0)`
- L59 _public function_ `void Load(const TBitArray<>& ArchiveBits, uint32 BitOffset)`
- L64 _public function_ `void Save(TBitArray<>& ArchiveBits, uint32 BitOffset) const`
- L69 _public function_ `void Load(const uint32* ArchiveBits)`
- L74 _public function_ `void Save(uint32* ArchiveBits) const`
- L82 _public function_ `void Add(uint32 PropertyCombination)` — Given a prospective PropertyCombination, add it to the PropertyCombinationSet if it is not a Redundant Combination of a PropertyCombination already in the Set. Once added, remove any now-redundant PropertyCombinations.
- L93 _public function_ `void AddRange(TPropertyCombinationSet<BitWidth>& Other)`
- L101 _public function_ `bool Contains(uint32 Value) const`
- L107 _public function_ `bool operator==(const TPropertyCombinationSet<BitWidth>& Other) const`
- L149 _public function_ `FIterator begin()`
- L153 _public function_ `FIterator end()`
- L159 _private function_ `void Construct()`
- L166 _private function_ `void AddNoCheck(uint32 Value)`
- L171 _private function_ `void RemoveNoCheck(uint32 Value)`
- L176 _private function_ `bool ContainsNoCheck(uint32 Value) const`
- L181 _private function_ `bool IsRedundantPropertyCombinationNoCheck(uint32 PropertyCombination) const`
- L186 _private function_ `bool IsRedundantPropertyCombinationRecursive(uint32 PropertyCombination, uint32 StartBit) const`
- L206 _private function_ `void RemoveRedundantPropertyCombinationsNoCheck(uint32 PropertyCombination)`
- L211 _private function_ `void RemoveRedundantPropertyCombinationsRecursive(uint32 PropertyCombination, uint32 StartBit)`
- L225 _private member_ `uint32 Storage[StorageWordCount];`
- L237 _public member_ `static constexpr uint32 BitWidth = 1;`
- L238 _public member_ `static constexpr uint32 StorageBitCount = 1;`
- L239 _public member_ `static constexpr uint32 StorageWordCount = 1;`
- L240 _public member_ `static constexpr uint32 MaxValue = 1;`
- L241 _public member_ `static constexpr uint32 NumPackedValues = 2;`
- L249 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<1>& Other)`
- L285 _public function_ `void AddRange(TPropertyCombinationSet<1>& Other)`
- L296 _public function_ `bool operator==(const TPropertyCombinationSet<1>& Other) const`
- L336 _private member_ `uint32 Storage;`

#### class `FPropertyCombinationPack3`  
`class FPropertyCombinationPack3`  
_L603-760_
- desc: For a TPropertyCombinationSet over bitfields with three bits, there are 19 possible sets of non-redundant corners: 8 One Corner Lists:   { [000],         [001],         [010],     [011],     [100],     [101],     [110],     [111], Proof there are no more One Corner Lists: this set already contains every possible one-element list, for all legal values from 0 to 2 ^ BitWidth - 1 9 Two Corner Lists:     [001,010],     [001,100],     [001,110], [010,100], [010,101], [011,100], [011,101], [011,110], [101,110], Proof there are no more Two Corner Lists: Each 0-property-set corner (000) is a redundant child of all other corners, 0 two corner lists contain it. Each 1-property-set corner is a redundant child of all other corners on its high-property face. On the low-property face, 000 is a redundant child, and the other 3 corners on the face are nonreundant. This adds 3x3 == 9 corners Each 2-property-set corner is a redundant child of 111. It is further a parent of the two redundant children formed by setting one of its lowbits to 0, plus 000. There are 3 remaining corners it is non-redundant with. This adds 3x3 == 9 corners. Each 3-property-set corner (111) is a redundant parent of all other corners, 0 two corner lists contain it. Divide by 2 since each of our elements above is double-counted for x,y and y,x 2 Three Corner Lists:   [001,010,100], [011,101,110] } Proof there are no more Three Corner Lists: A 1-property-set corner can not be non-redundant with two 2-property-set corners
- L606 _public member_ `static constexpr uint32 BitWidth = 3;`
- L607 _public member_ `static constexpr uint32 StorageBitCount = 5;`
- L608 _public member_ `static constexpr uint32 ArrayMax = 3;`
- L609 _public member_ `static constexpr uint32 MaxValue = (1 << BitWidth) - 1;`
- L610 _public member_ `static constexpr uint32 NumPackedValues = 19;`
- L612 _public function_ `static void Unpack(const uint32 Compressed, const uint32*& OutValues, int& OutNum)`
- L720 _public function_ `static uint32 Pack(const uint32* Values, const int Num)`

#### class `TPropertyCombinationSet`  
`template<> class TPropertyCombinationSet<3> : public TPropertyCombinationSetHardcoded<FPropertyCombinationPack3>`  
_L763-767_
- inherits: `TPropertyCombinationSetHardcoded<FPropertyCombinationPack3>`
- L35 _public member_ `static constexpr uint32 StorageBitCount = 1 << BitWidth;`
- L36 _public member_ `static constexpr uint32 StorageWordCount = (StorageBitCount + NumBitsPerDWORD - 1) / NumBitsPerDWORD;`
- L37 _public member_ `static constexpr uint32 MaxValue = StorageBitCount - 1;`
- L40 _public function_ `TPropertyCombinationSet()`
- L47 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<BitWidth>& Other)`
- L53 _public function_ `TPropertyCombinationSet(const TBitArray<>& ArchivedBits, uint32 BitOffset = 0)`
- L59 _public function_ `void Load(const TBitArray<>& ArchiveBits, uint32 BitOffset)`
- L64 _public function_ `void Save(TBitArray<>& ArchiveBits, uint32 BitOffset) const`
- L69 _public function_ `void Load(const uint32* ArchiveBits)`
- L74 _public function_ `void Save(uint32* ArchiveBits) const`
- L82 _public function_ `void Add(uint32 PropertyCombination)` — Given a prospective PropertyCombination, add it to the PropertyCombinationSet if it is not a Redundant Combination of a PropertyCombination already in the Set. Once added, remove any now-redundant PropertyCombinations.
- L93 _public function_ `void AddRange(TPropertyCombinationSet<BitWidth>& Other)`
- L101 _public function_ `bool Contains(uint32 Value) const`
- L107 _public function_ `bool operator==(const TPropertyCombinationSet<BitWidth>& Other) const`
- L149 _public function_ `FIterator begin()`
- L153 _public function_ `FIterator end()`
- L159 _private function_ `void Construct()`
- L166 _private function_ `void AddNoCheck(uint32 Value)`
- L171 _private function_ `void RemoveNoCheck(uint32 Value)`
- L176 _private function_ `bool ContainsNoCheck(uint32 Value) const`
- L181 _private function_ `bool IsRedundantPropertyCombinationNoCheck(uint32 PropertyCombination) const`
- L186 _private function_ `bool IsRedundantPropertyCombinationRecursive(uint32 PropertyCombination, uint32 StartBit) const`
- L206 _private function_ `void RemoveRedundantPropertyCombinationsNoCheck(uint32 PropertyCombination)`
- L211 _private function_ `void RemoveRedundantPropertyCombinationsRecursive(uint32 PropertyCombination, uint32 StartBit)`
- L225 _private member_ `uint32 Storage[StorageWordCount];`
- L237 _public member_ `static constexpr uint32 BitWidth = 1;`
- L238 _public member_ `static constexpr uint32 StorageBitCount = 1;`
- L239 _public member_ `static constexpr uint32 StorageWordCount = 1;`
- L240 _public member_ `static constexpr uint32 MaxValue = 1;`
- L241 _public member_ `static constexpr uint32 NumPackedValues = 2;`
- L249 _public function_ `TPropertyCombinationSet(const TPropertyCombinationSet<1>& Other)`
- L285 _public function_ `void AddRange(TPropertyCombinationSet<1>& Other)`
- L296 _public function_ `bool operator==(const TPropertyCombinationSet<1>& Other) const`
- L336 _private member_ `uint32 Storage;`

### `Source/Runtime/AssetRegistry/Private/SetKeyFuncs.h` (Private)


#### class `TSetKeyFuncs`  
`template <typename ElementType, typename KeyFuncsType> class TSetKeyFuncs`  
_L43-133_
- desc: Replacement for TSet that takes an instance of KeyFuncs rather than static functions on KeyFuncs. KeyFuncs must support: struct KeyFuncs { ~KeyFuncs(); KeyFuncs(KeyFuncs&& Other); // Used in constructor and SetKeyFuncs KeyFuncs& operator=(const KeyFuncs& Other); // Used in TSetKeyFuncs operator=(const TSetKeyFuncs&) KeyFuncs& operator=(KeyFuncs&& Other); // Used in TSetKeyFuncs operator=(TSetKeyFuncs&&) // Functions needed for ElementType ElementType GetInvalidElement(); bool IsInvalid(const ElementType&); uint32 GetTypeHash(const ElementType&); bool Matches(const ElementType& Element, const ElementType& Comparison); // Functions needed for each ComparisonType passed into Find bool Matches(const ElementType& Element, const ComparisonType& Comparison); uint32 GetTypeHash(const ComparisonType&); }; ElementType must support: ElementType(const ElementType& Other) ElementType(ElementType&& Other)
- L50 _public prototype_ `TSetKeyFuncs(KeyFuncsType KeyFuncs, int32 ExpectedNumElements = 0);`
- L51 _public prototype_ `TSetKeyFuncs(const TSetKeyFuncs<ElementType, KeyFuncsType>& Other);`
- L52 _public prototype_ `TSetKeyFuncs(TSetKeyFuncs<ElementType, KeyFuncsType>&& Other);`
- L53 _public prototype_ `TSetKeyFuncs& operator=(const TSetKeyFuncs<ElementType, KeyFuncsType>& Other);`
- L54 _public prototype_ `TSetKeyFuncs& operator=(TSetKeyFuncs<ElementType, KeyFuncsType>&& Other);`
- L55 _public prototype_ `~TSetKeyFuncs();`
- L57 _public prototype_ `void SetKeyFuncs(KeyFuncsType KeyFuncs);`
- L59 _public prototype_ `void Reset();`
- L60 _public prototype_ `void Empty(int32 ExpectedNumElements = 0);`
- L61 _public prototype_ `void Reserve(int32 ExpectedNumElements);`
- L66 _public prototype_ `void ResizeToTargetSize();` — Shrinks or grows the container to be equal in size to our target hardcoded loadfactor (HashSize == NumValues/TargetLoadFactor).
- L68 _public prototype_ `int32 Num() const;`
- L69 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L70 _public prototype_ `FSetKeyFuncsStats GetStats() const;`
- L73 _public prototype_ `template <typename CompareType> const ElementType* Find(const CompareType& Key) const;`
- L75 _public prototype_ `template <typename CompareType> const ElementType* FindByHash(uint32 TypeHash, const CompareType& Key) const;`
- L77 _public prototype_ `void Add(ElementType Value, bool* bAlreadyExists = nullptr);`
- L78 _public prototype_ `void AddByHash(uint32 TypeHash, ElementType Value, bool* bAlreadyExists = nullptr);`
- L79 _public prototype_ `int32 Remove(const ElementType& Value);`
- L80 _public prototype_ `int32 RemoveByHash(uint32 TypeHash, const ElementType& Value);`
- L112 _private prototype_ `void AddByHashNoReallocate(uint32 TypeHash, ElementType&& Value, bool* bAlreadyExists);`
- L113 _private prototype_ `void Reallocate(uint32 NewHashSize);`
- L114 _private prototype_ `uint32 GetTargetHashSize() const;`
- L115 _private prototype_ `uint32 GetTargetHashSize(uint32 TargetNumValues) const;`
- L120 _private prototype_ `uint32 HashSpaceToBucketSpace(uint32 HashKey) const;` — Convert an integer from GetTypeHash(), or from arithmetic on a Bucket index, by modulus into the [0, HashSize) range of bucket indices.
- L121 _private prototype_ `void DestructHash();`
- L124 _private member_ `constexpr static float MaxLoadFactorDuringAdd = 0.75f;`
- L125 _private member_ `constexpr static float TargetLoadFactor = 0.5f;`
- L126 _private member_ `constexpr static uint32 InitialAllocationSize = 8;`
- L127 _private member_ `constexpr static uint32 MinimumNonZeroSize = 8;`
- L129 _private member_ `mutable KeyFuncsType KeyFuncs;`
- L130 _private member_ `ElementType* Hash = nullptr;`
- L131 _private member_ `uint32 HashSize = 0;`
- L132 _private member_ `uint32 NumValues = 0;`
- L150 _function_ `template <typename ElementType, typename KeyFuncsType> inline TSetKeyFuncs<ElementType, KeyFuncsType>::TSetKeyFuncs(KeyFuncsType InKeyFuncs, int32 ExpectedNumElements) : KeyFuncs(MoveTemp(InKeyFuncs))`
- L157 _function_ `template <typename ElementType, typename KeyFuncsType> inline TSetKeyFuncs<ElementType, KeyFuncsType>::TSetKeyFuncs(const TSetKeyFuncs& Other)`
- L163 _function_ `template <typename ElementType, typename KeyFuncsType> inline TSetKeyFuncs<ElementType, KeyFuncsType>::TSetKeyFuncs(TSetKeyFuncs&& Other)`
- L170 _function_ `TSetKeyFuncs<ElementType, KeyFuncsType>::operator=(const TSetKeyFuncs<ElementType, KeyFuncsType>& Other)`
- L195 _function_ `TSetKeyFuncs<ElementType, KeyFuncsType>::operator=(TSetKeyFuncs&& Other)`
- L215 _function_ `template <typename ElementType, typename KeyFuncsType> inline TSetKeyFuncs<ElementType, KeyFuncsType>::~TSetKeyFuncs()`
- L221 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::SetKeyFuncs(KeyFuncsType InKeyFuncs)`
- L230 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::Reset()`
- L245 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::Empty(int32 ExpectedNumElements)`
- L263 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::Reserve(int32 ExpectedNumElements)`
- L273 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::ResizeToTargetSize()`
- L283 _function_ `template <typename ElementType, typename KeyFuncsType> inline int32 TSetKeyFuncs<ElementType, KeyFuncsType>::Num() const`
- L289 _function_ `template <typename ElementType, typename KeyFuncsType> inline SIZE_T TSetKeyFuncs<ElementType, KeyFuncsType>::GetAllocatedSize() const`
- L296 _function_ `TSetKeyFuncs<ElementType, KeyFuncsType>::GetStats() const`
- L387 _function_ `template <typename ElementType, typename KeyFuncsType> template <typename CompareType> const ElementType* TSetKeyFuncs<ElementType, KeyFuncsType>::Find(const CompareType& Key) const`
- L394 _function_ `template <typename ElementType, typename KeyFuncsType> template <typename CompareType> const ElementType* TSetKeyFuncs<ElementType, KeyFuncsType>::FindByHash(uint32 TypeHash, const CompareType& Key) const`
- L421 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::Add(ElementType Value, bool* bAlreadyExists)`
- L427 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::AddByHash(uint32 TypeHash, ElementType Value, bool* bAlreadyExists)`
- L450 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::AddByHashNoReallocate(uint32 TypeHash, ElementType&& Value, bool* bAlreadyExists)`
- L485 _function_ `template <typename ElementType, typename KeyFuncsType> inline int32 TSetKeyFuncs<ElementType, KeyFuncsType>::Remove(const ElementType& Value)`
- L491 _function_ `template <typename ElementType, typename KeyFuncsType> inline int32 TSetKeyFuncs<ElementType, KeyFuncsType>::RemoveByHash(uint32 TypeHash, const ElementType& Value)`
- L594 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::Reallocate(uint32 NewHashSize)`
- L633 _function_ `template <typename ElementType, typename KeyFuncsType> inline uint32 TSetKeyFuncs<ElementType, KeyFuncsType>::GetTargetHashSize() const`
- L639 _function_ `template <typename ElementType, typename KeyFuncsType> inline uint32 TSetKeyFuncs<ElementType, KeyFuncsType>::GetTargetHashSize(uint32 TargetNumValues) const`
- L652 _function_ `template <typename ElementType, typename KeyFuncsType> inline uint32 TSetKeyFuncs<ElementType, KeyFuncsType>::HashSpaceToBucketSpace(uint32 HashKey) const`
- L658 _function_ `template <typename ElementType, typename KeyFuncsType> inline void TSetKeyFuncs<ElementType, KeyFuncsType>::DestructHash()`

#### struct `TSetKeyFuncs::FIterator`  
`struct FIterator`  
_L84-94_
- desc: Implementation detail for ranged for loops; do not use this type directly.
- L86 _public prototype_ `FIterator(const TSetKeyFuncs<ElementType, KeyFuncsType>& InOwner);`
- L87 _public prototype_ `const ElementType& operator*() const;`
- L88 _public prototype_ `FIterator& operator++();`
- L89 _public prototype_ `bool operator!=(FIterationSentinel) const;`
- L92 _private member_ `const TSetKeyFuncs& Owner;`
- L93 _private member_ `uint32 Bucket;`
- L672 _function_ `template <typename ElementType, typename KeyFuncsType> inline TSetKeyFuncs<ElementType, KeyFuncsType>::FIterator::FIterator(const TSetKeyFuncs& InOwner) : Owner(InOwner) , Bucket(0)`
- L683 _function_ `template <typename ElementType, typename KeyFuncsType> inline const ElementType& TSetKeyFuncs<ElementType, KeyFuncsType>::FIterator::operator*() const`
- L690 _function_ `TSetKeyFuncs<ElementType, KeyFuncsType>::FIterator::operator++()`
- L701 _function_ `template <typename ElementType, typename KeyFuncsType> inline bool TSetKeyFuncs<ElementType, KeyFuncsType>::FIterator::operator!=(FIterationSentinel) const`

#### struct `TSetKeyFuncs::FIterationSentinel`  
`struct FIterationSentinel`  
_L97-99_
- desc: Implementation detail for ranged for loops; do not use this type directly.

#### struct `FSetKeyFuncsStats`  
`struct FSetKeyFuncsStats`  
_L135-141_
- L138 _public member_ `float AverageSearch;` — Average number of compares per Find across all keys in the container.
- L140 _public member_ `int32 LongestSearch;` — The longest number of compares in Find for a key in the container.

#### Free symbols / members of external scopes

- L103 _function_ `friend FIterator begin(const TSetKeyFuncs<ElementType, KeyFuncsType>& Set)` — Hidden friends for ranged for-loops
- L107 _function_ `friend FIterationSentinel end(const TSetKeyFuncs<ElementType, KeyFuncsType>& Set)`

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/AssetDataMap.h` (Public)


#### struct `UE::AssetRegistry::Private::FCachedAssetKey`  
`struct FCachedAssetKey`  
_L60-73_
- desc: Key type for TSet<FAssetData*> in the asset registry. Top level assets are searched for by their asset path as two names (e.g. '/Path/ToPackageName' + 'AssetName') Other assets (e.g. external actors) are searched for by their full path with the whole outer chain as a single name. (e.g. '/Path/To/Package.TopLevel:Subobject' + 'DeeperSubobject')
- L62 _public prototype_ `explicit FCachedAssetKey(const FAssetData* InAssetData);`
- L63 _public prototype_ `explicit FCachedAssetKey(const FAssetData& InAssetData);`
- L64 _public prototype_ `explicit FCachedAssetKey(FTopLevelAssetPath InAssetPath);`
- L65 _public prototype_ `explicit FCachedAssetKey(const FSoftObjectPath& InObjectPath);`
- L67 _public prototype_ `FString ToString() const;`
- L68 _public prototype_ `int32 Compare(const FCachedAssetKey& Other) const;` — Order asset keys with fast non-lexical comparison
- L69 _public prototype_ `void AppendString(FStringBuilderBase& Builder) const;`
- L71 _public member_ `FName OuterPath = NAME_None;`
- L72 _public member_ `FName ObjectName = NAME_None;`
- L411 _function_ `inline FCachedAssetKey::FCachedAssetKey(const FAssetData* InAssetData)`
- L431 _function_ `inline FCachedAssetKey::FCachedAssetKey(const FAssetData& InAssetData) : FCachedAssetKey(&InAssetData)`
- L436 _function_ `inline FCachedAssetKey::FCachedAssetKey(FTopLevelAssetPath InAssetPath) : OuterPath(InAssetPath.GetPackageName()) , ObjectName(InAssetPath.GetAssetName())`
- L442 _function_ `inline FCachedAssetKey::FCachedAssetKey(const FSoftObjectPath& InObjectPath)`
- L471 _function_ `inline FString FCachedAssetKey::ToString() const`
- L478 _function_ `inline int32 FCachedAssetKey::Compare(const FCachedAssetKey& Other) const`
- L490 _function_ `inline void FCachedAssetKey::AppendString(FStringBuilderBase& Builder) const`

#### struct `UE::AssetRegistry::Private::FCachedAssetKeyFuncs`  
`struct FCachedAssetKeyFuncs`  
_L84-105_
- desc: Policy type for TSet<FAssetData*> to use FCachedAssetKey for hashing/equality. This allows us to store just FAssetData* in the map without storing an extra copy of the key fields to save memory.
- L86 _public typedef_ `using KeyInitType = FCachedAssetKey;`
- L87 _public typedef_ `using ElementInitType = void;` — TSet doesn't actually use this type
- L91 _public function_ `static inline KeyInitType GetSetKey(const FAssetData* Element)`
- L96 _public function_ `static inline bool Matches(KeyInitType A, KeyInitType B)`
- L101 _public function_ `static inline uint32 GetKeyHash(KeyInitType Key)`

#### enum `UE::AssetRegistry::Private::FCachedAssetKeyFuncs::(anonymous)`  
`enum`  
_L89-89_

#### class `UE::AssetRegistry::Private::FAssetDataMap`  
`class FAssetDataMap`  
_L131-209_
- desc: Maps FCachedAssetKey to the FAssetDataPtrIndex. Maps FAssetDataPtrIndex to FAssetData*. This indirection is used to save memory in other query structures; @see UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS.
- L136 _public prototype_ `FAssetDataMap();`
- L137 _public prototype_ `FAssetDataMap(FAssetDataMap&& Other);`
- L138 _public prototype_ `FAssetDataMap& operator=(FAssetDataMap&& Other);`
- L139 _public prototype_ `~FAssetDataMap();`
- L141 _public prototype_ `void Empty(int32 ReservedSize = 0);`
- L142 _public prototype_ `void Shrink();`
- L143 _public prototype_ `FAssetDataPtrIndex Add(FAssetData* AssetData, bool* bAlreadyInSet = nullptr);`
- L148 _public prototype_ `void AddKeyLookup(FAssetData* AssetData, FAssetDataPtrIndex AssetIndex, bool* bAlreadyInSet = nullptr);` — Add the given AssetIndex to AssetByObjectName, when it is already in the AssetDatas array. Used for updates of the AssetData that change its name but not its pointer.
- L149 _public prototype_ `int32 Remove(const FCachedAssetKey& Key);`
- L154 _public prototype_ `int32 RemoveOnlyKeyLookup(const FCachedAssetKey& Key);` — Remove the AssetData* with the given key from AssetByObjectName, but keep it in the AssetDatas array. Used for updates of the AssetData that change its name but not its pointer.
- L156 _public prototype_ `int32 Num() const;`
- L157 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L158 _public prototype_ `TArray<FAssetData*> Array() const;`
- L159 _public prototype_ `int32 GetMaxIndex() const;`
- L160 _public prototype_ `bool IsValidId(FSetElementId SetId) const;`
- L161 _public prototype_ `FAssetData* Get(FSetElementId SetId) const;`
- L163 _public prototype_ `bool Contains(const FCachedAssetKey& Key) const;`
- L164 _public prototype_ `FAssetData* const* Find(const FCachedAssetKey& Key) const;`
- L165 _public prototype_ `FAssetDataPtrIndex FindId(const FCachedAssetKey& Key) const;`
- L166 _public prototype_ `FAssetData* operator[](FAssetDataPtrIndex AssetIndex) const;`
- L169 _public prototype_ `void Enumerate(TFunctionRef<bool(FAssetData& AssetData, FAssetDataPtrIndex AssetIndex)> Callback) const;` — Iterator of the FAssetData* that also provides the index of each FAssetData to the calling code.
- L171 _public prototype_ `FIterator begin() const;`
- L172 _public prototype_ `FIterator end() const;`
- L196 _private prototype_ `static bool IsInUse(const FAssetData* DataFromAssetDatas);` — We keep a FreeList of FAssetData* that are no longer in use, because we need to have stable indices for AssetData* in AssetDatas. To save memory, we keep the FreeList as a linked list in the AssetDatas structure; FAssetData* elements that are not in use are in the freelist and we reinterpret them as uint32 NextIndex. They set the low-bit to distinguish them from inuse pointers (which are 4-byte aligned and so have 0 in that bit; IsInUse reads this low bit.
- L197 _private prototype_ `void AddToFreeList(FAssetDataPtrIndex Index);`
- L198 _private prototype_ `FAssetDataPtrIndex PopFreeIndex();`
- L199 _private prototype_ `uint32 AssetByObjectNameValueToTypeHash(FAssetDataPtrIndex Value) const;`
- L200 _private prototype_ `bool AssetByObjectNameValueMatches(FAssetDataPtrIndex Value, const FCachedAssetKey& Key) const;`
- L203 _private member_ `TUniquePtr<FAssetObjectNameSet> AssetByObjectName;` — TUniquePtr for implementation hiding
- L204 _private member_ `TArray<FAssetData*> AssetDatas;`
- L205 _private member_ `FAssetDataPtrIndex FreeIndex = AssetDataPtrIndexInvalid;`
- L206 _private member_ `int32 NumFree = 0;`

#### struct `UE::AssetRegistry::Private::FAssetDataMap::FIterator`  
`struct FIterator`  
_L176-186_
- desc: Ranged for-loop iterator for the FAssetData*, do not use directly.
- L178 _public prototype_ `FIterator(const FAssetDataMap& InOwner, int32 InIndex);`
- L180 _public prototype_ `FAssetData* operator*() const;`
- L181 _public prototype_ `FIterator& operator++();`
- L182 _public prototype_ `bool operator!=(const FIterator& Other) const;`
- L184 _public member_ `const FAssetDataMap& Owner;`
- L185 _public member_ `int32 Index;`

#### struct `UE::AssetRegistry::Private::FAssetDataOrArrayIndex`  
`struct FAssetDataOrArrayIndex`  
_L220-246_
- desc: Used to optimize for memory a container of FAssetDataPtrIndex arrays, where most of the arrays contain only a single element. This type is a union that is either the single FAssetDataPtrIndex, or is an FAssetDataArrayIndex, which indexes into an external array of TArray<FAssetDataPtrIndex> in the same way that an FAssetDataPtrIndex indexes into an external array of FAssetData*.
- L223 _public prototype_ `FAssetDataOrArrayIndex() = default;` — Default constructor returns the same result as CreateEmptyList().
- L224 _public prototype_ `static FAssetDataOrArrayIndex CreateEmptyList();`
- L225 _public prototype_ `static FAssetDataOrArrayIndex CreateAssetDataPtrIndex(FAssetDataPtrIndex AssetIndex);`
- L226 _public prototype_ `static FAssetDataOrArrayIndex CreateArrayIndex(FAssetDataArrayIndex ArrayIndex);`
- L228 _public prototype_ `bool IsEmptyList() const;`
- L229 _public prototype_ `bool IsAssetDataPtrIndex() const;`
- L230 _public prototype_ `bool IsAssetDataArrayIndex() const;`
- L231 _public prototype_ `bool operator==(const FAssetDataOrArrayIndex& Other) const;`
- L232 _public prototype_ `bool operator!=(const FAssetDataOrArrayIndex& Other) const;`
- L234 _public prototype_ `FAssetDataPtrIndex AsAssetDataPtrIndex() const;`
- L235 _public prototype_ `FAssetDataArrayIndex AsAssetDataArrayIndex() const;`
- L239 _public member_ `static constexpr uint32 EmptyList = 0xffff'ffff;` — Implementation details for classes that need to make assumptions about the conversion
- L240 _public member_ `static constexpr uint32 TypeMask = 0x8000'0000;`
- L241 _public member_ `static constexpr uint32 AssetDataType = 0x0000'0000;`
- L242 _public member_ `static constexpr uint32 ArrayType = 0x8000'0000;`
- L245 _private member_ `uint32 Value = EmptyList;`
- L518 _function_ `inline FAssetDataOrArrayIndex FAssetDataOrArrayIndex::CreateEmptyList()`
- L523 _function_ `inline FAssetDataOrArrayIndex FAssetDataOrArrayIndex::CreateAssetDataPtrIndex(FAssetDataPtrIndex AssetIndex)`
- L534 _function_ `inline FAssetDataOrArrayIndex FAssetDataOrArrayIndex::CreateArrayIndex(FAssetDataArrayIndex ArrayIndex)`
- L545 _function_ `inline bool FAssetDataOrArrayIndex::IsEmptyList() const`
- L550 _function_ `inline bool FAssetDataOrArrayIndex::IsAssetDataPtrIndex() const`
- L555 _function_ `inline bool FAssetDataOrArrayIndex::IsAssetDataArrayIndex() const`
- L560 _function_ `inline bool FAssetDataOrArrayIndex::operator==(const FAssetDataOrArrayIndex& Other) const`
- L565 _function_ `inline bool FAssetDataOrArrayIndex::operator!=(const FAssetDataOrArrayIndex& Other) const`
- L570 _function_ `inline FAssetDataPtrIndex FAssetDataOrArrayIndex::AsAssetDataPtrIndex() const`
- L575 _function_ `inline FAssetDataArrayIndex FAssetDataOrArrayIndex::AsAssetDataArrayIndex() const`

#### class `UE::AssetRegistry::Private::FIndirectAssetDataArrays`  
`class FIndirectAssetDataArrays`  
_L254-301_
- desc: Contains arrays of AssetDataPtrIndex that are referred to from the PackageNameMap by an index. Provides an API for editing and reading as a TArrayView an FAssetDataOrArrayIndex, regardless of whether that FAssetDataOrArrayIndex is a single FAssetDataPtrIndex or an FAssetDataArrayIndex that points to an array of FAssetDataPtrIndex.
- L259 _public prototype_ `void AddElement(FAssetDataOrArrayIndex& Array, FAssetDataPtrIndex AssetIndex);`
- L260 _public prototype_ `void RemoveElement(FAssetDataOrArrayIndex& Array, FAssetDataPtrIndex AssetIndex);`
- L261 _public prototype_ `void RemoveAllElements(FAssetDataOrArrayIndex& Array);`
- L262 _public prototype_ `TConstArrayView<FAssetDataPtrIndex> Iterate(const FAssetDataOrArrayIndex* ArrayPtr) const;`
- L264 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L265 _public prototype_ `void Empty();`
- L266 _public prototype_ `void Shrink();`
- L269 _private member_ `static constexpr uint32 UnusedIndex = static_cast<uint32>(~0);`
- L295 _private prototype_ `int32 AllocateArrayIndex();`
- L296 _private prototype_ `void ReleaseArrayIndex(int32 Index);`
- L299 _private member_ `TArray<FArrayOrNextIndex> Arrays;`
- L300 _private member_ `uint32 FreeList = UnusedIndex;`

#### struct `UE::AssetRegistry::Private::FIndirectAssetDataArrays::FArrayOrNextIndex`  
`struct FArrayOrNextIndex`  
_L278-293_
- desc: Since the elements in Arrays need to have a stable index, we keep track of a freelist whenever one of those elements is freed. To store the freelist without a wasteful additional container, we use a linked list, with bytes used in the array reinterpreted as an index of the next element of the freelist. This requires a union that can be either a TArray or a uint32 NextIndex, which is what FArrayOrNextIndex provides.
- L285 _public member_ `bool bArray;`
- L287 _public prototype_ `FArrayOrNextIndex();`
- L288 _public prototype_ `FArrayOrNextIndex(FArrayOrNextIndex&& Other);`
- L289 _public prototype_ `FArrayOrNextIndex(const FArrayOrNextIndex& Other) = delete;`
- L290 _public prototype_ `FArrayOrNextIndex& operator=(const FArrayOrNextIndex& Other) = delete;`
- L291 _public prototype_ `FArrayOrNextIndex& operator=(FArrayOrNextIndex&& Other) = delete;`
- L292 _public prototype_ `~FArrayOrNextIndex();`
- L580 _function_ `inline FIndirectAssetDataArrays::FArrayOrNextIndex::FArrayOrNextIndex() : NextIndex(UnusedIndex) , bArray(false)`
- L586 _function_ `inline FIndirectAssetDataArrays::FArrayOrNextIndex::FArrayOrNextIndex(FArrayOrNextIndex&& Other)`
- L605 _function_ `inline FIndirectAssetDataArrays::FArrayOrNextIndex::~FArrayOrNextIndex()`

#### union `UE::AssetRegistry::Private::FIndirectAssetDataArrays::FArrayOrNextIndex::(anonymous)`  
``  
_L281-284_

#### class `UE::AssetRegistry::Private::FAssetPackageNameMap`  
`class FAssetPackageNameMap`  
_L318-391_
- desc: An API similar to TMap<FName, FAssetData*> that internally handles the compact data representation of actually used for CachedAssetsByPackageName when UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS is on. The actual values in the map in that case are FAssetDataOrArrayIndex, which need to be converted to a TArrayView<FAssetData*>.
- L323 _public typedef_ `using KeyType = FName;`
- L325 _public prototype_ `FAssetPackageNameMap(FAssetDataMap& InAssetDataMap, FIndirectAssetDataArrays& InIndirectAssetDataArrays);`
- L326 _public prototype_ `FAssetPackageNameMap& operator=(FAssetPackageNameMap&& Other);`
- L327 _public prototype_ `~FAssetPackageNameMap();`
- L329 _public prototype_ `void Empty(int32 ReservedSize=0);`
- L330 _public prototype_ `void Add(FName PackageName, FAssetDataPtrIndex AssetIndex);`
- L331 _public prototype_ `int32 Remove(FName PackageName, FAssetDataPtrIndex AssetIndex);`
- L332 _public prototype_ `void Shrink();`
- L334 _public prototype_ `int32 Num() const;`
- L335 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L337 _public prototype_ `void GenerateKeyArray(TArray<FName>& OutKeys) const;`
- L343 _public prototype_ `TOptional<TConstArrayView<FAssetDataPtrIndex>> Find(FName PackageName) const;` — Return an arrayview to the list of FAssetDataPtrIndex stored for the given PackageName, or an empty optional if not found. The memory at the array view can be invalidated if any non-const functions on this, or on IndirectArrays, is called. The arrayview should be no longer used after calling any of those functions.
- L344 _public prototype_ `bool Contains(FName PackageName) const;`
- L345 _public prototype_ `FIterator begin() const;`
- L346 _public prototype_ `FIterationSentinel end() const;`
- L350 _public prototype_ `FAssetPackageNameMap(const FAssetPackageNameMap& Other) = delete;` — We don't handle these copy/moves because we rely on references to some other containers
- L351 _public prototype_ `FAssetPackageNameMap(FAssetPackageNameMap&& Other) = delete;`
- L352 _public prototype_ `FAssetPackageNameMap& operator=(const FAssetPackageNameMap&& Other) = delete;`
- L381 _private prototype_ `uint32 AssetOrArrayByPackageNameValueToTypeHash(FAssetDataOrArrayIndex Value) const;`
- L382 _private prototype_ `bool AssetOrArrayByPackageNameValueMatches(FAssetDataOrArrayIndex Value, FName PackageName) const;`
- L383 _private prototype_ `FAssetData* AssetOrArrayIndexToFirstAssetDataPtr(FAssetDataOrArrayIndex DataOrArrayIndex) const;`
- L386 _private member_ `TUniquePtr<FAssetPackageNameSet> AssetOrArrayByPackageName;` — TUniquePtr for implementation hiding
- L387 _private member_ `FAssetDataMap& AssetDataMap;`
- L388 _private member_ `FIndirectAssetDataArrays& IndirectArrays;`

#### struct `UE::AssetRegistry::Private::FAssetPackageNameMap::FIteratorValue`  
`struct FIteratorValue`  
_L359-362_
- desc: Provides the key in the same API as TPair<FName, TArray<FAssetData*>> returned from a TMap<FName, TArray<FAssetData*>> ranged for loop. The TArray<FAssetData*> value is not provided since it is expensive to create.
- L361 _public member_ `FName Key;`

#### struct `UE::AssetRegistry::Private::FAssetPackageNameMap::FIterator`  
`struct FIterator`  
_L364-375_
- desc: Ranged for-loop iterator, do not use directly.
- L367 _public prototype_ `explicit FIterator(const FAssetPackageNameMap& InOwner);`
- L368 _public prototype_ `~FIterator();`
- L369 _public prototype_ `FIteratorValue operator*() const;`
- L370 _public prototype_ `FIterator& operator++();`
- L371 _public prototype_ `bool operator!=(FIterationSentinel) const;`
- L373 _private member_ `const FAssetPackageNameMap& Owner;`
- L374 _private member_ `FAssetPackageNameSetIteratorBytes HashIterBytes;`

#### struct `UE::AssetRegistry::Private::FAssetPackageNameMap::FIterationSentinel`  
`struct FIterationSentinel`  
_L376-378_

#### Free symbols / members of external scopes

- L48 _macro_ `#define UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS 0`
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L51 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L75 _prototype_ `inline FStringBuilderBase& operator<<(FStringBuilderBase& Builder, const FCachedAssetKey& Key);` (scope `UE::AssetRegistry::Private`)
- L76 _prototype_ `inline bool operator==(const FCachedAssetKey& A, const FCachedAssetKey& B);` (scope `UE::AssetRegistry::Private`)
- L77 _prototype_ `inline bool operator!=(const FCachedAssetKey& A, const FCachedAssetKey& B);` (scope `UE::AssetRegistry::Private`)
- L78 _prototype_ `inline uint32 GetTypeHash(const FCachedAssetKey& A);` (scope `UE::AssetRegistry::Private`)
- L89 _enumerator_ `enum { bAllowDuplicateKeys = false }; static inline KeyInitType GetSetKey(const FAssetData* Element) { return FCachedAssetKey(*Element); } static inline bool Matches(KeyInitType A, KeyInitType B)` (scope `UE::AssetRegistry::Private::FCachedAssetKeyFuncs::__anon150b17750103`)
- L113 _typedef_ `using FAssetDataMap = TSet<FAssetData*, FCachedAssetKeyFuncs>;` (scope `UE::AssetRegistry::Private`) — When not using indirection, an FAssetDataMap is a TSet, but with the complication that it stores pointers to FAssetData while supporting lookup by FCachedAssetKey. @see FCachedAssetKey.
- L114 _typedef_ `using FConstAssetDataMap = TSet<const FAssetData*, FCachedAssetKeyFuncs>;` (scope `UE::AssetRegistry::Private`)
- L119 _typedef_ `using FAssetDataPtrIndex = uint32;` (scope `UE::AssetRegistry::Private`) — A 32-bit index to a 64-bit pointer, to an FAssetData.
- L120 _variable_ `constexpr FAssetDataPtrIndex AssetDataPtrIndexInvalid = MAX_uint32;` (scope `UE::AssetRegistry::Private`)
- L123 _typedef_ `using FAssetObjectNameSet = TSetKeyFuncs<FAssetDataPtrIndex, FAssetObjectNameKeyFuncs>;` (scope `UE::AssetRegistry::Private`)
- L212 _typedef_ `using FAssetDataArrayIndex = uint32;` (scope `UE::AssetRegistry::Private`) — Integer type used to index FAssetRegistryState.AssetDataArrays.
- L282 _member_ `TArray<FAssetDataPtrIndex> Array;` (scope `UE::AssetRegistry::Private::FIndirectAssetDataArrays::FArrayOrNextIndex::__anon150b1775020a`)
- L283 _member_ `uint32 NextIndex;` (scope `UE::AssetRegistry::Private::FIndirectAssetDataArrays::FArrayOrNextIndex::__anon150b1775020a`)
- L304 _typedef_ `using FAssetPackageNameSet = TSetKeyFuncs<FAssetDataOrArrayIndex, FAssetPackageNameKeyFuncs>;` (scope `UE::AssetRegistry::Private`)
- L310 _typedef_ `using FAssetPackageNameSetIteratorBytes = TAlignedBytes<16, 8>;` (scope `UE::AssetRegistry::Private`) — Structure that is the same size as TSetKeyFuncs::FIterator. This allows us to have a copy of TSetKeyFuncs::FIterator with a forward declare rather than needing to include the header. The downside is we have to manually keep the size in sync (which we enforce with a static_assert in cpp).
- L403 _namespace_ `namespace UE`
- L403 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L403 _namespace_ `namespace Private` (scope `UE::AssetRegistry`)
- L406 _function_ `inline uint32 HashCombineQuick(uint32 A, uint32 B)` (scope `UE::AssetRegistry::Private`)
- L495 _function_ `inline FStringBuilderBase& operator<<(FStringBuilderBase& Builder, const FCachedAssetKey& Key)` (scope `UE::AssetRegistry::Private`)
- L501 _function_ `inline bool operator==(const FCachedAssetKey& A, const FCachedAssetKey& B)` (scope `UE::AssetRegistry::Private`)
- L506 _function_ `inline bool operator!=(const FCachedAssetKey& A, const FCachedAssetKey& B)` (scope `UE::AssetRegistry::Private`)
- L511 _function_ `inline uint32 GetTypeHash(const FCachedAssetKey& A)` (scope `UE::AssetRegistry::Private`)

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/AssetDependencyGatherer.h` (Public)


#### class `IAssetDependencyGatherer`  
`class IAssetDependencyGatherer`  
_L39-127_
- desc: Interface class for functions that return extra dependencies to add to Assets of a given Class, to e.g. add dependencies on external Assets in a subdirectory.
- L116 _public prototype_ `virtual void GatherDependencies(FGatherDependenciesContext& Context) const ;` — Return the extra dependencies to add to the given AssetData, which is guaranteed to have ClassType equal to the class for which the Gatherer was registered. WARNING: For high performance these callbacks are called inside the critical section of the AssetRegistry. Attempting to call public functions on the AssetRegistry will deadlock. To send queries about what assets exist, used the passed-in interface functions instead. @param Context the various inputs/outputs provided to/from the gatherer
- L123 _public prototype_ `virtual void GatherDependencies(const FAssetData& AssetData, const FAssetRegistryState& AssetRegistryState, TFunctionRef<FARCompiledFilter(const FARFilter&)> CompileFilterFunc, TArray<IAssetDependencyGatherer::FGathereredDependency>& OutDependencies, TArray<FString>& OutDependencyDirectories) const ;` — `UE_DEPRECATED(5.8, "Implement GatherDependencies(FGatherDependenciesContext& Context) instead")` — Deprecated version of GatherDependencies, provided for code compatibility. Will be removed in UE 5.8.

#### struct `IAssetDependencyGatherer::FGathereredDependency`  
`struct FGathereredDependency`  
_L42-46_
- L44 _public member_ `FName PackageName;`
- L45 _public member_ `UE::AssetRegistry::EDependencyProperty Property;`

#### struct `IAssetDependencyGatherer::FGatherDependenciesContext`  
`struct FGatherDependenciesContext`  
_L63-103_
- desc: The parameters passed to GatherDependencies @param AssetData The Asset to which the dependencies will be added @param AssetRegistryState Helper object: The AssetRegistry's internal state which can be used to run queries in the callback. This must be used instead of the usual interface functions on IAssetRegistry::GetChecked(), because the callback executes inside the critical section. @param CompileFilterFunc Helper object: Used to compile FARFilter into FARCompiledFilter for queries sent to AssetRegistryState. The same functionality that is normally provided by IAssetRegistry::GetChecked().CompileFilter. @param CachedPathTree The path tree cache inside the AssetRegitry can be used to quickly interogate the path hierarchy. @param OutDependencies List of gathered dependencies to add for the asset. @param OutDependencyDirectories List of directories that the callback queried. The AssetRegistry will call the callback again if any assets are added to any of these directories.
- L71 _private member_ `const FAssetData& AssetData;`
- L72 _private member_ `const FAssetRegistryState& AssetRegistryState;`
- L73 _private member_ `const FPathTree& CachedPathTree;`
- L74 _private member_ `const TFunctionRef<FARCompiledFilter(const FARFilter&)> CompileFilterFunc;`
- L75 _private member_ `TArray<FGathereredDependency>& OutDependencies;`
- L76 _private member_ `TArray<FString>& OutDependencyDirectories;`
- L79 _private member_ `bool bInterfaceGatherDependenciesCalled = false;` — helper flag to detect old implementations of IAssetDependencyGatherer
- L83 _public function_ `FGatherDependenciesContext( const FAssetData& InAssetData, const FAssetRegistryState& InAssetRegistryState, const FPathTree& InCachedPathTree, const TFunctionRef<FARCompiledFilter(const FARFilter&)> InCompileFilterFunc, TArray<FGathereredDependency>& InReturnedDependencies, TArray<FString>& InReturnedDependencyDirectories) : AssetData(InAssetData), AssetRegistryState(InAssetRegistryState), CachedPathTree(InCachedPathTree), CompileFilterFunc(InCompileFilterFunc), OutDependencies(InReturnedDependencies), OutDependencyDirectories(InReturnedDependencyDirectories)`
- L95 _public function_ `const FAssetData& GetAssetData() const`
- L96 _public function_ `const FAssetRegistryState& GetAssetRegistryState() const`
- L97 _public function_ `const class FPathTree& GetCachedPathTree() const`
- L98 _public function_ `TFunctionRef<FARCompiledFilter(const FARFilter&)> GetCompileFilterFunc() const`
- L99 _public function_ `FARCompiledFilter CompileFilter(FARFilter& Filter)`
- L101 _public function_ `TArray<FGathereredDependency>& GetOutDependencies()`
- L102 _public function_ `TArray<FString>& GetOutDependencyDirectories()`

#### class `UE::AssetDependencyGatherer::Private::FRegisteredAssetDependencyGatherer`  
`class FRegisteredAssetDependencyGatherer`  
_L131-152_
- L134 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAssetDependencyGathererRegistered);`
- L135 _public member_ `static FOnAssetDependencyGathererRegistered OnAssetDependencyGathererRegistered;`
- L137 _public prototype_ `FRegisteredAssetDependencyGatherer();`
- L138 _public prototype_ `virtual ~FRegisteredAssetDependencyGatherer();`
- L140 _public prototype_ `virtual UClass* GetAssetClass() const = 0;`
- L141 _public prototype_ `virtual void GatherDependencies(IAssetDependencyGatherer::FGatherDependenciesContext& Context) const = 0;`
- L143 _public prototype_ `static void ForEach(TFunctionRef<void(FRegisteredAssetDependencyGatherer*)> Func);`
- L144 _public function_ `static bool IsEmpty()`
- L146 _public prototype_ `void GatherDependenciesForGatherer(IAssetDependencyGatherer* GathererInterface, IAssetDependencyGatherer::FGatherDependenciesContext& Context, const char* InGathererClass) const;`
- L149 _private prototype_ `static TLinkedList<FRegisteredAssetDependencyGatherer*>*& GetRegisteredList();`
- L150 _private member_ `TLinkedList<FRegisteredAssetDependencyGatherer*> GlobalListLink;`
- L151 _private member_ `mutable bool bCalledOnce = false;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace AssetDependencyGatherer` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::AssetDependencyGatherer`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L129 _namespace_ `namespace UE`
- L129 _namespace_ `namespace AssetDependencyGatherer` (scope `UE`)
- L129 _namespace_ `namespace Private` (scope `UE::AssetDependencyGatherer`)
- L134 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAssetDependencyGathererRegistered);`
- L164 _macro_ `#define REGISTER_ASSETDEPENDENCY_GATHERER(GathererClass, AssetClass) \` — Used to Register an IAssetDependencyGatherer for a class Example usage: class FMyAssetDependencyGatherer : public IAssetDependencyGatherer { ... } REGISTER_ASSETDEPENDENCY_GATHERER(FMyAssetDependencyGatherer, UMyAssetClass);

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryHelpers.h` (Public)


#### struct `FTagAndValue`  
`struct FTagAndValue`  
_L27-36_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public member_ `FName Tag;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = AssetData)`
- L35 _public member_ `FString Value;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = AssetData)`

#### enum `EAssetRegistrySortOrder`  
`enum class EAssetRegistrySortOrder : uint8`  
_L39-43_
- reflection: `UENUM(BlueprintType, DisplayName = "Sort Order")`
- L41 _public enumerator_ `Ascending`
- L42 _public enumerator_ `Descending`

#### enum `EAssetsWithOuterForPathsFlags`  
`enum class EAssetsWithOuterForPathsFlags`  
_L45-56_
- L47 _public enumerator_ `None = 0`
- L49 _public enumerator_ `RecursivePaths = (1 << 0)` — If we should scan recursively or not
- L51 _public enumerator_ `IncludeOnlyOnDiskAsset = (1 << 1)` — If we should only include on disk assets
- L53 _public enumerator_ `ExactOuter = (1 << 2)` — If we should only return assets directly outered to the provided outer
- L55 _public enumerator_ `ScanPaths = (1 << 3)` — Scan the AssetRegistry for each path passed in

#### class `UAssetRegistryHelpers`  
`class UAssetRegistryHelpers : public UObject`  
_L60-227_
- reflection: `UCLASS(transient)`
- inherits: `UObject`
- L66 _public prototype_ `static TScriptInterface<IAssetRegistry> GetAssetRegistry();` — `UFUNCTION(BlueprintPure, Category = "Asset Registry")`
- L75 _public prototype_ `static FAssetData CreateAssetData(const UObject* InAsset, bool bAllowBlueprintClass = false);` — `UFUNCTION(BlueprintPure, Category = "Asset Data")` — Creates asset data from a UObject. @param InAsset	The asset to create asset data for @param bAllowBlueprintClass	By default trying to create asset data for a blueprint class will create one for the UBlueprint instead
- L79 _public prototype_ `static bool IsValid(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(DisplayName = "Is Valid Asset Data", ScriptMethod))` — Checks to see if this AssetData refers to an asset or is NULL
- L83 _public prototype_ `static bool IsUAsset(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Returns true if this is the primary asset in a package, true for maps and assets but false for secondary objects like class redirectors
- L87 _public prototype_ `static bool IsRedirector(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Returns true if the this asset is a redirector.
- L91 _public prototype_ `static FString GetFullName(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Returns the full name for the asset in the form: Class ObjectPath
- L95 _public prototype_ `static FSoftObjectPath ToSoftObjectPath(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Convert to a SoftObjectPath for loading
- L98 _public prototype_ `static UClass* GetClass(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))`
- L102 _public prototype_ `static UObject* GetAsset(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Returns the asset UObject if it is loaded or loads the asset if it is unloaded then returns the result
- L106 _public prototype_ `static bool IsAssetLoaded(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Returns true if the asset is loaded
- L111 _public prototype_ `static bool IsAssetCooked(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod="IsCooked"))` — Returns true if the asset is cooked
- L115 _public prototype_ `static bool AssetHasEditorOnlyData(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod="HasEditorOnlyData"))` — Returns true if the asset has its editor-only data
- L120 _public prototype_ `static FString GetExportTextName(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Returns the name for the asset in the form: Class'ObjectPath'
- L124 _public prototype_ `static bool GetTagValue(const FAssetData& InAssetData, const FName& InTagName, FString& OutTagValue);` — `UFUNCTION(BlueprintPure, Category = "Asset Data", meta=(ScriptMethod))` — Gets the value associated with the given tag as a string
- L130 _public prototype_ `static FARFilter SetFilterTagsAndValues(const FARFilter& InFilter, const TArray<FTagAndValue>& InTagsAndValues);` — `UFUNCTION(BlueprintPure, Category = "Asset Registry")` — Populates the FARFilters tags and values map with the passed in tags and values
- L134 _public prototype_ `static void GetBlueprintAssets(const FARFilter& InFilter, TArray<FAssetData>& OutAssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Registry", meta=(ScriptMethod))` — Gets asset data for all blueprint assets that match the filter. ClassPaths in the filter specify the blueprint's parent class.
- L142 _public prototype_ `static void GetDerivedClassAssetData(const TArray<FTopLevelAssetPath>& InBaseClasses, TArray<FAssetData>& OutDerivedClassAssetData);` — `UFUNCTION(BlueprintCallable, Category = "Asset Registry")` — Gets a list of FAssetData for all child classes, loaded or unloaded, if you have a native UClass* convert it to a FTopLevelAssetPath using UClass::GetClassPathName. The list of derived types can be quite large, but this function attempts to be as efficient as possible for large asset sets.
- L150 _public prototype_ `static UClass* FindAssetNativeClass(const FAssetData& AssetData);` — `UFUNCTION(BlueprintPure, Category = "Asset Registry", meta=(ScriptMethod))` — Returns the first native class of the asset type that can be found.  Normally this is just the FAssetData::GetClass(), however if the class is a blueprint generated class it may not be loaded.  In which case GetAncestorClassNames will be used to find the first native super class.  This can be slow if temporary caching mode is not on.
- L152 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FSortingPredicate, const FAssetData&, Left, const FAssetData&, Right);`
- L161 _public prototype_ `static void SortByPredicate(UPARAM(Ref) TArray<FAssetData>& Assets, FSortingPredicate SortingPredicate, EAssetRegistrySortOrder SortOrder);` — `UFUNCTION(BlueprintCallable, Category = "Asset Registry")` — Sorts the assets based on a custom Blueprint delegate. @param Assets The assets to sort @param SortingPredicate Implements a Left <= Right relation @param SortOrder Whether to sort ascending or descending
- L170 _public prototype_ `static void SortByAssetName(UPARAM(Ref) TArray<FAssetData>& Assets, EAssetRegistrySortOrder SortOrder);` — `UFUNCTION(BlueprintCallable, Category = "Asset Registry")` — Sorts the assets by their asset name. @param Assets The assets to sort @param SortOrder Whether to sort ascending or descending
- L175 _public prototype_ `static void FindReferencersOfAssetOfClass(UObject* AssetInstance, TConstArrayView<UClass*> InMatchClasses, TArray<FAssetData>& OutAssetDatas);` — Finds references of the provided asset that are of the a class contained in the InMatchClasses set.
- L180 _public prototype_ `static void FindReferencersOfAssetOfClass(const FAssetIdentifier& InAssetIdentifier, TConstArrayView<UClass*> InMatchClasses, TArray<FAssetData>& OutAssetDatas);` — Finds references of the provided asset that are of the a class contained in the InMatchClasses set.
- L193 _public prototype_ `static bool IsAssetDataBlueprintOfClassSet(const FAssetData& AssetData, const TSet<FTopLevelAssetPath>& ClassNameSet);` — Checks to see if the given asset data is a blueprint with a base class in the ClassNameSet. This checks the parent asset tag
- L199 _public prototype_ `static void FixupRedirectedAssetPath(FName& InOutAssetPath);` — Resolves the provided asset path using asset redirectors. @param	InOutAssetPath	Asset path to resolve [In/Out].
- L205 _public prototype_ `static void FixupRedirectedAssetPath(FSoftObjectPath& InOutSoftObjectPath);` — Resolves the provided soft object asset path using asset redirectors. @param	InOutSoftObjectPath	Asset path to resolve [In/Out].
- L217 _public prototype_ `static TArray<FAssetData> GetAssetsWithOuterForPaths(TConstArrayView<FName> InPackagePaths, FName InOuterPath, bool bInRecursivePaths = false, bool bInIncludeOnlyOnDiskAsset = false, bool bInExactOuter = true);` — `UE_DEPRECATED(5.7, "Please use GetAssetsWithOuterForPaths with enum flags")` — Returns all the corresponding assets from the provided paths that are outered to the provided outer name. @param	InPackagePaths List of package paths to scan for assets. @param	InOuterPath The outer path to filter asset with. @param	bInRecursivePaths If we should scan recursively or not. @param	bInIncludeOnlyOnDiskAsset If we should only include on disk assets. @param	bInExactOuter If we should only return assets directly outered to the provided outer.
- L225 _public prototype_ `static TArray<FAssetData> GetAssetsWithOuterForPaths(TConstArrayView<FName> InPackagePaths, FName InOuterPath, EAssetsWithOuterForPathsFlags InFlags = (EAssetsWithOuterForPathsFlags::ExactOuter | EAssetsWithOuterForPathsFlags::ScanPaths));` — Returns all the corresponding assets from the provided paths that are outered to the provided outer name. @param	InPackagePaths List of package paths to scan for assets. @param	InOuterPath The outer path to filter asset with. @param	InFlags The flags to control the behavior of this function, see EAssetsWithOuterForPathsFlags

#### struct `UAssetRegistryHelpers::FTemporaryCachingModeScope`  
`struct FTemporaryCachingModeScope`  
_L183-190_
- desc: Enable/disable asset registry caching mode for the duration of the scope
- L185 _public prototype_ `FTemporaryCachingModeScope(bool InTempCachingMode);`
- L186 _public prototype_ `~FTemporaryCachingModeScope();`
- L189 _private member_ `bool PreviousCachingMode;`

#### Free symbols / members of external scopes

- L57 _prototype_ `ENUM_CLASS_FLAGS(EAssetsWithOuterForPathsFlags);`
- L152 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FSortingPredicate, const FAssetData&, Left, const FAssetData&, Right);`

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryModule.h` (Public)


#### class `FAssetRegistryModule`  
`class FAssetRegistryModule : public IModuleInterface, public IAssetRegistryInterface`  
_L26-170_
- inherits: `IModuleInterface,IAssetRegistryInterface`
- desc: Asset registry module
- L32 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L34 _public function_ `virtual IAssetRegistry& Get() const`
- L40 _public function_ `bool IsValid() const` — Reports whether Get is valid to call. Will be true except during engine shutdown.
- L46 _public function_ `IAssetRegistry* TryGet() const` — Returns AssetRegistry pointer if valid, or nullptr. Will be non-null except during engine shutdown.
- L51 _public function_ `static IAssetRegistry& GetRegistry()`
- L56 _public function_ `static void TickAssetRegistry(float DeltaTime)`
- L61 _public function_ `static void AssetCreated(UObject* NewAsset)`
- L66 _public function_ `static void AssetDeleted(UObject* DeletedAsset)`
- L71 _public function_ `static void AssetRenamed(const UObject* RenamedAsset, const FString& OldObjectPath)`
- L76 _public function_ `static void AssetsSaved(TArray<FAssetData>&& SavedAssets)`
- L81 _public function_ `static void PackageDeleted(UPackage* DeletedPackage)`
- L87 _public function_ `virtual void GetDependencies(FName InPackageName, TArray<FName>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::Package, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) override` — Access the dependent package names for a given source package
- L92 _public function_ `virtual UE::AssetRegistry::EExists TryGetAssetByObjectPath(const FSoftObjectPath& ObjectPath, FAssetData& OutAssetData) const override`
- L102 _public function_ `virtual UE::AssetRegistry::EExists TryGetAssetPackageData(FName PackageName, FAssetPackageData& OutAssetPackageData, bool bFailIfLockHeld) const override`
- L108 _public function_ `virtual UE::AssetRegistry::EExists TryGetAssetPackageData(FName PackageName, FAssetPackageData& OutAssetPackageData, FName& OutCorrectCasePackageName, bool bFailIfLockHeld) const override`
- L118 _public function_ `virtual bool EnumerateAssets(const FARFilter& Filter, TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const override`
- L129 _public function_ `virtual bool RegisterOnAssetsAddedDelegate(const TFunction<void(TConstArrayView<FAssetData>)>& Function, FDelegateHandle& OutHandle) override`
- L140 _public function_ `virtual bool UnregisterOnAssetsAddedDelegate(const FDelegateHandle& Handle) override`
- L150 _public function_ `virtual bool RegisterOnAssetsRemovedDelegate(const TFunction<void(TConstArrayView<FAssetData>)>& Function, FDelegateHandle& OutHandle) override`
- L161 _public function_ `virtual bool UnregisterOnAssetsRemovedDelegate(const FDelegateHandle& Handle) override`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace AssetRegistryConstants`
- L20 _variable_ `const FName ModuleName("Ass` (scope `AssetRegistryConstants`)

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryState.h` (Public)


#### struct `FAssetRegistrySerializationOptions`  
`struct FAssetRegistrySerializationOptions`  
_L60-124_
- desc: Load/Save options used to modify how the cache is serialized. These are read out of the AssetRegistry section of Engine.ini and can be changed per platform.
- L62 _public prototype_ `FAssetRegistrySerializationOptions( UE::AssetRegistry::ESerializationTarget Target = UE::AssetRegistry::ESerializationTarget::ForGame);`
- L66 _public member_ `bool bSerializeAssetRegistry = false;` — True rather to load/save registry at all
- L69 _public member_ `bool bSerializeDependencies = false;` — True rather to load/save dependency info. If true this will handle hard and soft package references.
- L72 _public member_ `bool bSerializeSearchableNameDependencies = false;` — True rather to load/save dependency info for Name references,
- L75 _public member_ `bool bSerializeManageDependencies = false;` — True rather to load/save dependency info for Manage references,
- L78 _public member_ `bool bSerializePackageData = false;` — If true will read/write FAssetPackageData
- L81 _public member_ `bool bUseAssetRegistryTagsAllowListInsteadOfDenyList = false;` — True if CookFilterlistTagsByClass is an allow list. False if it is a deny list.
- L87 _public member_ `bool bFilterAssetDataWithNoTags = false;` — True if we want to only write out asset data if it has valid tags. This saves memory by not saving data for things like textures.
- L93 _public member_ `bool bFilterDependenciesWithNoTags = false;` — True if we also want to filter out dependency data for assets that have no tags. Only filters if bFilterAssetDataWithNoTags is also true.
- L96 _public member_ `bool bFilterSearchableNames = false;` — Filter out searchable names from dependency data
- L102 _public member_ `bool bKeepDevelopmentAssetRegistryTags = false;` — Keep tags intended for the cooker's output DevelopmentAssetRegistry. This flag defaults to false and is set to true only by the cooker.
- L108 _public member_ `TMap<FTopLevelAssetPath, TSet<FName>> CookFilterlistTagsByClass;` — The map of class pathname to tag set of tags that are allowed in cooked builds. This is either an allow list or deny list depending on bUseAssetRegistryTagsAllowListInsteadOfDenyList.
- L111 _public member_ `TSet<FName> CookTagsAsName;` — Tag keys whose values should be stored as FName in cooked builds.
- L114 _public member_ `TSet<FName> CookTagsAsPath;` — Tag keys whose values should be stored as FRegistryExportPath in cooked builds.
- L117 _public member_ `TSet<FString> AssetBundlesDenyList;` — List of asset bundles (could contain wildcards) that will be removed from the AssetRegistry
- L120 _public prototype_ `void DisableFilters();` — Disable all filters
- L123 _private prototype_ `void InitForDevelopment();`
- L819 _function_ `inline FAssetRegistrySerializationOptions::FAssetRegistrySerializationOptions( UE::AssetRegistry::ESerializationTarget Target)`
- L828 _function_ `inline void FAssetRegistrySerializationOptions::DisableFilters()`
- L837 _function_ `inline void FAssetRegistrySerializationOptions::InitForDevelopment()`

#### struct `FAssetRegistryLoadOptions`  
`struct FAssetRegistryLoadOptions`  
_L126-152_
- L128 _public prototype_ `FAssetRegistryLoadOptions() = default;`
- L129 _public prototype_ `explicit FAssetRegistryLoadOptions(const FAssetRegistrySerializationOptions& Options);`
- L135 _public member_ `TFunction<bool(FName PackageName)> ShouldKeepPackage;` — If non-empty, called on every FAssetData, AssetPackageData, and FDependsNode loaded from disk, keeping them only if ShouldKeepPackage returns true on their packagename.
- L143 _public member_ `FixedTagPrivate::FWeakStorePtr Store;` — Optional pointer to the FStore previously created by Load, in cases where the same AssetRegistry.bin file is being reloaded. Caution: If this Store is not identical to the one that would be loaded from disk, chaotic crashes can occur during loading or afterwards during reading of AsssetDatas. If non-null, this FStore will be used for all TagData lookups and the serialization of the bytes for it on disk will be skipped.
- L144 _public member_ `int32 ParallelWorkers = 0;`
- L145 _public member_ `bool bLoadDependencies = true;`
- L146 _public member_ `bool bLoadPackageData = true;`
- L151 _public member_ `bool bMountPointsRequireSeparateAllocationBlocks = false;` — If true, AssetDatas, AssetPackageDatas and DependsNodes will be individually allocated rather than allocated in a single block, so that they can be individually freed when their mountpoint is unloaded.
- L847 _function_ `inline FAssetRegistryLoadOptions::FAssetRegistryLoadOptions(const FAssetRegistrySerializationOptions& Options) : bLoadDependencies(Options.bSerializeDependencies) , bLoadPackageData(Options.bSerializePackageData)`

#### struct `FAssetRegistryLoadResults`  
`struct FAssetRegistryLoadResults`  
_L155-159_
- desc: Extra data about the load of an AssetRegistryState from disk that is optionally returned from Load.
- L157 _public member_ `FAssetRegistryVersion::Type Version;`
- L158 _public member_ `FixedTagPrivate::FWeakStorePtr Store;`

#### struct `FAssetRegistryPruneOptions`  
`struct FAssetRegistryPruneOptions`  
_L161-173_
- L163 _public member_ `TSet<FName> RequiredPackages;`
- L164 _public member_ `TSet<FName> RemovePackages;`
- L165 _public member_ `TSet<int32> ChunksToKeep;`
- L166 _public member_ `FAssetRegistrySerializationOptions Options;`
- L169 _public member_ `bool bRemoveDependenciesWithoutPackages = false;` — Remove FDependsNodes that do not point to packages
- L172 _public member_ `TSet<FPrimaryAssetType> RemoveDependenciesWithoutPackagesKeepPrimaryAssetTypes;` — List of types that should not be pruned because they do not have a package

#### struct `FAssetRegistryAppendResult`  
`struct FAssetRegistryAppendResult`  
_L175-179_
- L177 _public member_ `TArray<const FAssetData*> AddedAssets;`
- L178 _public member_ `TArray<const FAssetData*> UpdatedAssets;`

#### class `FAssetRegistryState`  
`class FAssetRegistryState`  
_L185-809_
- desc: The state of an asset registry, this is used internally by IAssetRegistry to represent the disk cache, and is also accessed directly to save/load cooked caches.
- L188 _private typedef_ `using FCachedAssetKey = UE::AssetRegistry::Private::FCachedAssetKey;`
- L190 _private typedef_ `using FAssetDataMap = UE::AssetRegistry::Private::FAssetDataMap;`
- L191 _private typedef_ `using FAssetDataPtrIndex = UE::AssetRegistry::Private::FAssetDataPtrIndex;`
- L192 _private typedef_ `using FAssetDataArrayIndex = UE::AssetRegistry::Private::FAssetDataArrayIndex;`
- L193 _private typedef_ `using FAssetDataOrArrayIndex = UE::AssetRegistry::Private::FAssetDataOrArrayIndex;`
- L201 _public typedef_ `using FConstAssetDataMap = UE::AssetRegistry::Private::FConstAssetDataMap;`
- L204 _public prototype_ `FAssetRegistryState();`
- L205 _public prototype_ `FAssetRegistryState(const FAssetRegistryState&) = delete;`
- L206 _public prototype_ `FAssetRegistryState(FAssetRegistryState&& Rhs);`
- L207 _public prototype_ `~FAssetRegistryState();`
- L209 _public prototype_ `FAssetRegistryState& operator=(const FAssetRegistryState&) = delete;`
- L210 _public prototype_ `FAssetRegistryState& operator=(FAssetRegistryState&& O);`
- L212 _public typedef_ `using EInitializationMode = UE::AssetRegistry::EAppendMode;`
- L213 _public typedef_ `using EEnumerateAssetsFlags = UE::AssetRegistry::EEnumerateAssetsFlags;`
- L220 _public prototype_ `bool HasAssets(const FName PackagePath, bool bARFiltering=false) const;` — Does the given path contain assets? @param bARFiltering Whether to apply filtering from UE::AssetRegistry::FFiltering (false by default) @note This function doesn't recurse into sub-paths.
- L233 _public prototype_ `bool GetAssets(const FARCompiledFilter& Filter, const TSet<FName>& PackageNamesToSkip, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets = false) const;` — Gets asset data for all assets that match the filter. Assets returned must satisfy every filter component if there is at least one element in the component's array. Assets will satisfy a component if they match any of the elements in it. @param Filter filter to apply to the assets in the AssetRegistry @param PackageNamesToSkip explicit list of packages to skip, because they were already added @param OutAssetData the list of assets in this path @param bSkipARFilteredAssets If true, skip assets that are skipped by UE::AssetRegistry::FFiltering (false by default)
- L247 _public prototype_ `bool EnumerateAssets(const FARCompiledFilter& Filter, const TSet<FName>& PackageNamesToSkip, TFunctionRef<bool(const FAssetData&)> Callback, EEnumerateAssetsFlags InEnumerateFlags = EEnumerateAssetsFlags::AllowUnfilteredArAssets) const;` — Enumerate asset data for all assets that match the filter. Assets returned must satisfy every filter component if there is at least one element in the component's array. Assets will satisfy a component if they match any of the elements in it. @param Filter filter to apply to the assets in the AssetRegistry @param PackageNamesToSkip explicit list of packages to skip, because they were already added @param Callback function to call for each asset data enumerated @param InEnumerateFlags flags to control enumeration and filtering. Note that the default does not include AllowUnmountedPaths; they will be skipped by default. @see EEnumerateAssetsFlags.
- L258 _public prototype_ `bool GetAllAssets(const TSet<FName>& PackageNamesToSkip, TArray<FAssetData>& OutAssetData, bool bARFiltering = false) const;` — Gets asset data for all assets in the registry state. @param PackageNamesToSkip explicit list of packages to skip, because they were already added @param OutAssetData the list of assets @param bARFiltering Whether to apply filtering from UE::AssetRegistry::FFiltering (false by default)
- L268 _public prototype_ `void EnumerateAllAssets(TFunctionRef<void(const FAssetData&)> Callback, EEnumerateAssetsFlags InEnumerateFlags = EEnumerateAssetsFlags::AllowAll) const;` — Enumerates asset data for all assets in the registry state. @param Callback function to call for each asset data enumerated @param InEnumerateFlags flags to control enumeration and filtering. The default includes all AllowFlags and no assets will be skipped by default. @see EEnumerateAssetsFlags.
- L281 _public prototype_ `bool EnumerateAllAssets(const TSet<FName>& PackageNamesToSkip, TFunctionRef<bool(const FAssetData&)> Callback, EEnumerateAssetsFlags InEnumerateFlags = EEnumerateAssetsFlags::AllowUnfilteredArAssets) const;` — Enumerates asset data for all assets in the registry state, except for assets in packages that are in PackageNamesToSkip. Used by the AssetRegistry for scans after an in-memory scan has already been completed. @param PackageNamesToSkip explicit list of packages to skip, because they were already added @param Callback function to call for each asset data enumerated @param InEnumerateFlags flags to control enumeration and filtering. Note that the default does not include AllowUnmountedPaths; they will be skipped by default. @see EEnumerateAssetsFlags.
- L290 _public prototype_ `void EnumerateAllPaths(TFunctionRef<void(FName PathName)> Callback) const;` — Calls the callback with the LongPackageName of each path that has assets as direct children. Callback will not be called for parent paths that have childpaths with direct children but do not have direct children of their own.
- L299 _public prototype_ `void GetPackagesByName(FStringView PackageName, TArray<FName>& OutPackageNames) const;` — Gets the LongPackageNames for all packages with the given PackageName. Call to check existence of a LongPackageName or find all packages with a ShortPackageName. @param PackageName Name of the package to find, may be a LongPackageName or ShortPackageName. @param OutPackageNames All discovered matching LongPackageNames are appended to this array.
- L309 _public prototype_ `FName GetFirstPackageByName(FStringView PackageName) const;` — Returns the first LongPackageName found for the given PackageName. Issues a warning and returns the first (sorted lexically) if there is more than one. Call to check existence of a LongPackageName or find a package with a ShortPackageName. @param PackageName Name of the package to find, may be a LongPackageName or ShortPackageName. @return The first LongPackageName of the matching package, or NAME_None if not found.
- L322 _public prototype_ `bool GetDependencies(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;` — Appends a list of packages and searchable names that are referenced by the supplied package or name. @param AssetIdentifier	the name of the package/name for which to gather dependencies @param OutDependencies	a list of things that are referenced by AssetIdentifier @param Category	which category(ies) of dependencies to include in the output list. Dependencies matching ANY of the OR'd categories will be returned. @param Flags	which flags are required present or not present on the dependencies. Dependencies matching ALL required and NONE excluded bits will be returned. For each potentially returned dependency, flags not applicable to their category are ignored.
- L326 _public prototype_ `bool GetDependencies(const FAssetIdentifier& AssetIdentifier, TArray<FAssetDependency>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;`
- L342 _public prototype_ `bool ContainsDependency(const FAssetIdentifier& AssetIdentifier, const FAssetIdentifier& QueryAsset, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;` — Return whether the supplied package references the query package. @param PackageName The name of the package for which to inspect dependencies (eg, /Game/MyFolder/MyAsset) @param QueryAsset Which package to look for in PackageName's dependencies @param Category Which category(ies) of dependencies to look in for QueryAsset. Dependencies matching ANY of the OR'd categories will be considered. @param Flags Which flags are required present or not present on the dependencies. Dependencies matching ALL required and NONE excluded bits will be considered. For each potentially considered dependency, flags not applicable to their category are ignored.
- L358 _public prototype_ `bool GetReferencers(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;` — Appends a list of packages and searchable names that reference the supplied package or name. @param AssetIdentifier	the name of the package/name for which to gather dependencies @param OutReferencers	a list of things that reference AssetIdentifier @param Category	which category(ies) of dependencies to include in the output list. Dependencies matching ANY of the OR'd categories will be returned. @param Flags	which flags are required present or not present on the dependencies. Dependencies matching ALL required and NONE excluded bits will be returned. For each potentially returned dependency, flags not applicable to their category are ignored.
- L362 _public prototype_ `bool GetReferencers(const FAssetIdentifier& AssetIdentifier, TArray<FAssetDependency>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const;`
- L373 _public prototype_ `const FAssetData* GetAssetByObjectPath(const FSoftObjectPath& ObjectPath) const;` — Gets the asset data for the specified object path @param ObjectPath the path of the object to be looked up @return the assets data, null if not found
- L375 _public prototype_ `const FAssetData* GetAssetByObjectPath(const UE::AssetRegistry::Private::FCachedAssetKey& Key) const;`
- L383 _public prototype_ `void EnumerateAssetsByPackageName(const FName PackageName, TFunctionRef<bool(const FAssetData* AssetData)> Callback) const;` — Enumerates the asset datas for the specified package name @param PackageName the path of the package to be looked up Calls the callback once for each AssetData* in the package; callback is not called if nothing found.
- L386 _public prototype_ `TArray<const FAssetData*> CopyAssetsByPackageName(const FName PackageName) const;` — Gets the array of AssetData pointers for the package; does not copy the AssetDatas, just the pointers.
- L387 _public prototype_ `int32 NumAssetsByPackageName(const FName PackageName) const;`
- L389 _public prototype_ `void EnumerateAssetsByPackagePath(FName LongPackagePathName, TFunctionRef<bool(const FAssetData* AssetData)> Callback) const;`
- L398 _public prototype_ `void EnumerateAssetsByClassPathName(const FTopLevelAssetPath ClassPathName, TFunctionRef<bool(const FAssetData* AssetData)> Callback) const;` — Enumerates the asset datas for the specified asset class @param ClassPathName the class path name of the assets to look for Calls the callback once with each AssetData*, callback is not called if nothing found
- L406 _public prototype_ `void EnumerateTags(TFunctionRef<bool(FName TagName)> Callback) const;` — Enumerates all tags of any asset in the AssetRegistry @param Callback the function for each tag
- L409 _public prototype_ `bool ContainsTag(FName TagName) const;` — Return whether the given TagName occurs in the tags of any asset in the AssetRegistry
- L417 _public prototype_ `void EnumerateAssetsByTagName(const FName TagName, TFunctionRef<bool(const FAssetData* AssetData)> Callback) const;` — Enumerates the asset datas with the specified asset tag @param TagName the tag name to search for Callst he callback once with each AssetData*, callback is not called if nothing found
- L426 _public prototype_ `void EnumerateTagToAssetDatas( TFunctionRef<bool(FName TagName, IAssetRegistry::FEnumerateAssetDatasFunc EnumerateAssets)> Callback) const;` — Enumerates all tags of any asset in the AssetRegistry including function that can be called to enumerate assets for each tag @param Callback the function for each tag pair
- L430 _public prototype_ `const TMap<FName, const FAssetPackageData*>& GetAssetPackageDataMap() const;` — Returns const version of internal PackageName->PackageData map for fast iteration
- L433 _public prototype_ `void GetPrimaryAssetsIds(TSet<FPrimaryAssetId>& OutPrimaryAssets) const;` — Get the set of primary assets contained in this state
- L436 _public prototype_ `const FAssetPackageData* GetAssetPackageData(FName PackageName) const;` — Returns pointer to the asset package data
- L437 _public prototype_ `const FAssetPackageData* GetAssetPackageData(FName PackageName, FName& OutCorrectCasePackageName) const;`
- L439 _public prototype_ `FAssetPackageData* GetAssetPackageData(FName PackageName);`
- L442 _public prototype_ `void GetPackageNames(TArray<FName>& OutPackageNames) const;` — Returns all package names
- L445 _public prototype_ `FAssetPackageData* CreateOrGetAssetPackageData(FName PackageName);` — Finds an existing package data, or creates a new one to modify
- L448 _public prototype_ `bool RemovePackageData(FName PackageName);` — Removes existing package data
- L451 _public prototype_ `bool RemovePackageDatas(const TSet<FAssetIdentifier>& PackageNames);` — Removes existing package datas, passed in as FAssetIdentifier(PackageName) for internal performance.
- L454 _public prototype_ `void AddAssetData(FAssetData* AssetData);` — Adds the asset data to the lookup maps
- L457 _public prototype_ `void AddTagsToAssetData(const FSoftObjectPath& InObjectPath, FAssetDataTagMap&& InTagsAndValues);` — Add the given tags/values to the asset data associated with the given object path, if it exists
- L460 _public prototype_ `void UpdateAssetData(const FAssetData& NewAssetData, bool bCreateIfNotExists=false);` — Finds an existing asset data based on object path and updates it with the new value and updates lookup maps
- L461 _public prototype_ `void UpdateAssetData(FAssetData&& NewAssetData, bool bCreateIfNotExists = false);`
- L464 _public prototype_ `void UpdateAssetData(FAssetData* AssetData, const FAssetData& NewAssetData, bool* bOutModified = nullptr);` — Updates an existing asset data with the new value and updates lookup maps
- L466 _public prototype_ `void UpdateAssetData(FAssetData* AssetData, FAssetData&& NewAssetData, bool* bOutModified = nullptr);`
- L476 _public prototype_ `bool UpdateAssetDataPackageFlags(FName PackageName, uint32 PackageFlags);` — Updates all asset data package flags in the specified package @param PackageName the package name @param PackageFlags the package flags to set @return True if any assets exists in the package
- L479 _public prototype_ `void RemoveAssetData(FAssetData* AssetData, bool bRemoveDependencyData, bool& bOutRemovedAssetData, bool& bOutRemovedPackageData);` — Removes the asset data from the lookup maps
- L481 _public prototype_ `void RemoveAssetData(const FSoftObjectPath& SoftObjectPath, bool bRemoveDependencyData, bool& bOutRemovedAssetData, bool& bOutRemovedPackageData);`
- L484 _public prototype_ `void RemoveAssetDatas(TArrayView<FAssetData*> AssetDatas, bool bRemoveDependencyData, TBitArray<>& bOutRemovedAssetData, TBitArray<>& bOutRemovedPackageData);` — Removes a set of asset data from the lookup maps.
- L491 _public prototype_ `void ClearDependencies(const FAssetIdentifier& AssetIdentifier, UE::AssetRegistry::EDependencyCategory Category);` — Clear all dependencies of the given category from the given AssetIdentifier (e.g. package). Also clears the referencer link from each of the dependencies.
- L497 _public prototype_ `void AddDependencies(const FAssetIdentifier& AssetIdentifier, TConstArrayView<FAssetDependency> Dependencies);` — Add the given dependencies to the given AssetIdentifier (e.g. package). Also adds a referencer link on each of the dependencies.
- L503 _public prototype_ `void SetDependencies(const FAssetIdentifier& AssetIdentifier, TConstArrayView<FAssetDependency> Dependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All);` — Clears existing dependencies of the given Category(s) and assigns the input Dependencies. Gives an error if any elements of Dependencies are outside of the Category(s).
- L510 _public prototype_ `void ClearReferencers(const FAssetIdentifier& AssetIdentifier, UE::AssetRegistry::EDependencyCategory Category);` — Clear all referencers of the given category from the given AssetIdentifier (e.g. package). Also clears the dependency link from each of the referencers.
- L516 _public prototype_ `void AddReferencers(const FAssetIdentifier& AssetIdentifier, TConstArrayView<FAssetDependency> Referencers);` — Add a dependency on the given AssetIdentifier (e.g. package) from each of the Referencers. Also adds a referencer link to each referencer on the AssetIdentifer's node.
- L522 _public prototype_ `void SetReferencers(const FAssetIdentifier& AssetIdentifier, TConstArrayView<FAssetDependency> Referencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All);` — Clears existing referencers of the given Category(s) and assigns the input Referencers. Gives an error if any elements of Referencers are outside of the Category(s).
- L527 _public prototype_ `void Reset();` — Resets to default state
- L529 _public prototype_ `void InitializeFromExisting(const FAssetRegistryState& Existing, const FAssetRegistrySerializationOptions& Options, EInitializationMode InitializationMode = EInitializationMode::Rebuild, FAssetRegistryAppendResult* OutAppendResult = nullptr);`
- L540 _public prototype_ `void ConsumeExisting(FAssetRegistryState&& Existing, const FAssetRegistrySerializationOptions& Options, FAssetRegistryAppendResult* OutAppendResult = nullptr);` — Similar to InitializeFromExisting, but it moves the allocations over from InState into *this rather than copying them. It also shares the InState's existing FStore (if any) rather than creating a new one. This function is used for faster consumption of states loaded internally by the AssetRegistry. This function is less general than InitializeFromExisting to reduce complexity; it only supports EInitializationMode::OnlyUpdateNew and does not support filter flags on the input Options; all instances of FAssetDatas, FAssetPackageDatas, and FDependsNodes are kept The InState is reset to empty by this function.
- L552 _public prototype_ `void PruneAssetData(const TSet<FName>& RequiredPackages, const TSet<FName>& RemovePackages, const TSet<int32> ChunksToKeep, const FAssetRegistrySerializationOptions& Options);` — Prunes an asset cache, this removes asset data, nodes, and package data that isn't needed. @param RequiredPackages If set, only these packages will be maintained. If empty it will keep all unless filtered by other parameters @param RemovePackages These packages will be removed from the current set @param ChunksToKeep The list of chunks that are allowed to remain. Any assets in other chunks are pruned. If empty, all assets are kept regardless of chunk @param Options Serialization options to read filter info from
- L554 _public prototype_ `void PruneAssetData(const TSet<FName>& RequiredPackages, const TSet<FName>& RemovePackages, const FAssetRegistrySerializationOptions& Options);`
- L556 _public prototype_ `void Prune(const FAssetRegistryPruneOptions& PruneOptions);`
- L571 _public prototype_ `void InitializeFromExistingAndPrune(const FAssetRegistryState& ExistingState, const TSet<FName>& RequiredPackages, const TSet<FName>& RemovePackages, const TSet<int32> ChunksToKeep, const FAssetRegistrySerializationOptions& Options);` — Initializes a cache from an existing using a set of filters. This is more efficient than calling InitializeFromExisting and then PruneAssetData. @param ExistingState State to use initialize from @param RequiredPackages If set, only these packages will be maintained. If empty it will keep all unless filtered by other parameters. @param RemovePackages These packages will be removed from the current set @param ChunksToKeep The list of chunks that are allowed to remain. Any assets in other chunks are pruned. If empty, all assets are kept regardless of chunk @param Options Serialization options to read filter info from
- L576 _public prototype_ `void FilterTags(const FAssetRegistrySerializationOptions& Options);` — Edit every AssetData's Tags to remove Tags that are filtered out by the filtering rules in Options.
- L578 _public prototype_ `static void FilterTags(FAssetData& InOutAssetData, const FAssetRegistrySerializationOptions& Options);` — Filter a given AssetData's Tags to remove Tags that are filtered out by the filtering rules in Options.
- L582 _public prototype_ `bool Serialize(FArchive& Ar, const FAssetRegistrySerializationOptions& Options);` — Serialize the registry to/from a file, skipping editor only data
- L585 _public prototype_ `bool Save(FArchive& Ar, const FAssetRegistrySerializationOptions& Options);` — Save without editor-only data
- L586 _public prototype_ `bool Load(FArchive& Ar, const FAssetRegistryLoadOptions& Options = FAssetRegistryLoadOptions(), FAssetRegistryVersion::Type* OutVersion = nullptr);`
- L589 _public prototype_ `bool Load(FArchive& Ar, const FAssetRegistryLoadOptions& Options, FAssetRegistryLoadResults& OutResults);`
- L598 _public prototype_ `static bool LoadFromDisk(const TCHAR* InPath, const FAssetRegistryLoadOptions& InOptions, FAssetRegistryState& OutState, FAssetRegistryVersion::Type* OutVersion = nullptr);` — Example Usage: FAssetRegistryState AR; bool bSucceeded = FAssetRegistryState::LoadFromDisk(TEXT("Path/To/AR"), FAssetRegistryLoadOptions(), AR);
- L602 _public prototype_ `SIZE_T GetAllocatedSize(bool bLogDetailed = false) const;` — Returns memory size of entire registry, optionally logging sizes
- L605 _public prototype_ `static bool IsFilterValid(const FARCompiledFilter& Filter);` — Checks a filter to make sure there are no illegal entries
- L608 _public prototype_ `int32 GetNumAssets() const;` — Returns the number of assets in this state
- L611 _public prototype_ `int32 GetNumPackages() const;` — Returns the number of packages in this state
- L626 _public prototype_ `void Dump(const TArray<FString>& Arguments, TArray<FString>& OutPages, int32 LinesPerPage=1) const;` — Writes out the state in textual form. Use arguments to control which segments to emit. @param Arguments List of segments to emit. Possible values: 'ObjectPath', 'PackageName', 'Path', 'Class', 'Tag', 'Dependencies' and 'PackageData'. @param OutPages Textual representation will be written to this array; each entry will have LinesPerPage lines of the full dump. @param LinesPerPage - how many lines should be combined into each string element of OutPages, for e.g. breaking up the dump into separate files. To facilitate diffing between similar-but-different registries, the actual number of lines per page will be slightly less than LinesPerPage; we introduce partially deterministic pagebreaks near the end of each page.
- L632 _private prototype_ `void EnumerateAllMutableAssets(TFunctionRef<void(FAssetData&)> Callback, EEnumerateAssetsFlags InEnumerateFlags = EEnumerateAssetsFlags::AllowAll) const;` — Accessors of mutable FAssetData*, for friend classes
- L640 _private prototype_ `TArray<FAssetData*> GetMutableAssetsSortedByObjectPath();` — Copy the results of EnumerateAllMutableAssets into an array of pointers and sort it by the FAssetData's objectpaths. Do not use this unless you need them sorted; it is wasteful to sort. Use EnumerateAllMutableAssets instead, and make your own array. Uses ParallelSort, so do not call this function within functions that are already running in parallel.
- L642 _private prototype_ `FAssetData* GetMutableAssetByObjectPath(const FSoftObjectPath& ObjectPath) const;`
- L643 _private prototype_ `FAssetData* GetMutableAssetByObjectPath(const UE::AssetRegistry::Private::FCachedAssetKey& Key) const;`
- L644 _private prototype_ `void EnumerateMutableAssetsByPackageName(const FName PackageName, TFunctionRef<bool(FAssetData* AssetData)> Callback) const;`
- L646 _private prototype_ `void EnumerateMutableAssetsByPackagePath(FName LongPackagePathName, TFunctionRef<bool(FAssetData* AssetData)> Callback) const;`
- L650 _private prototype_ `void InitializeFromExisting(const FAssetDataMap& AssetDataMap, const TMap<FAssetIdentifier, FDependsNode*>& DependsNodeMap, const TMap<FName, FAssetPackageData*>& AssetPackageDataMap, const FAssetRegistrySerializationOptions& Options, EInitializationMode InitializationMode = EInitializationMode::Rebuild, FAssetRegistryAppendResult* OutAppendResult = nullptr);` — Initializes cache from existing set of asset data and depends nodes
- L658 _private prototype_ `template<class Archive> void Load(Archive&& Ar, const FAssetRegistryHeader& Header, const FAssetRegistryLoadOptions& Options);`
- L661 _private prototype_ `void SetAssetDatas(TConstArrayView<FAssetData*> AssetDatas, const FAssetRegistryLoadOptions& Options);` — Initialize the lookup maps
- L664 _private prototype_ `FDependsNode* ResolveRedirector(FDependsNode* InDependency, const FAssetDataMap& InAllowedAssets, TMap<FDependsNode*, FDependsNode*>& InCache) const;` — Find the first non-redirector dependency node starting from InDependency.
- L668 _private prototype_ `FDependsNode* FindDependsNode(const FAssetIdentifier& Identifier) const;` — Finds an existing node for the given package and returns it, or returns null if one isn't found
- L671 _private prototype_ `FDependsNode* CreateOrFindDependsNode(const FAssetIdentifier& Identifier, bool* bAlreadyExists = nullptr);` — Creates a node in the CachedDependsNodes map or finds the existing node and returns it
- L674 _private prototype_ `bool RemoveDependsNode(const FAssetIdentifier& Identifier);` — Removes the depends node and updates the dependencies to no longer contain it as a referencer.
- L685 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(ERemoveDependsFlags);`
- L688 _private prototype_ `bool RemoveDependsNodes(const TSet<FAssetIdentifier>& Identifiers, ERemoveDependsFlags Flags = ERemoveDependsFlags::None);` — Removes a set of depends nodes and updates their dependencies to no longer contain them as a referencer.
- L693 _private prototype_ `template<typename SetKeyFuncs, typename SetAllocator> bool RemovePackageData(const TSet<FAssetIdentifier, SetKeyFuncs, SetAllocator>& AssetIdentifiers);` — Removes a set of existing package data. Returns true if any were removed, false if all already did not exist.
- L696 _private prototype_ `static void FilterTags(const FAssetDataTagMapSharedView& InTagsAndValues, FAssetDataTagMap& OutTagsAndValues, const TSet<FName>* ClassSpecificFilterList, const FAssetRegistrySerializationOptions & Options);` — Filter a set of tags and output a copy of the filtered set.
- L700 _private prototype_ `static TSharedPtr<FAssetBundleData> FilterBundles(const TSharedPtr<FAssetBundleData>& InAssetBundles, const FAssetRegistrySerializationOptions& Options);` — Filter asset bundles and output a copy of the filtered set or input AssetBundles if nothing was filtered
- L703 _private prototype_ `void LoadDependencies(FArchive& Ar, const FAssetRegistryLoadOptions& Options, FAssetRegistryVersion::Type Version);`
- L705 _private prototype_ `template <bool bLatestVersion> void LoadDependenciesImpl(FArchive& Ar, const FAssetRegistryLoadOptions& Options, FAssetRegistryVersion::Type Version);`
- L706 _private prototype_ `void LegacyLoadDependencies_BeforeFlags(FArchive& Ar, bool bSerializeDependencies, FAssetRegistryVersion::Type Version);`
- L708 _private prototype_ `void SetTagsOnExistingAsset(FAssetData* AssetData, FAssetDataTagMap&& NewTags);`
- L710 _private prototype_ `void SetDependencyNodeSorting(bool bSortDependencies, bool bSortReferencers);`
- L712 _private prototype_ `void RemoveAssetData(FAssetData* AssetData, const FCachedAssetKey& Key, bool bRemoveDependencyData, #if UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS UE::AssetRegistry::Private::FAssetDataPtrIndex AssetIndex, #endif bool& bOutRemovedAssetData, bool& bOutRemovedPackageData );`
- L720 _private prototype_ `template<typename BitArrayAllocator> void RemoveAssetDatasImpl(TArrayView<FAssetData*> AssetDatas, bool bRemoveDependencyData, TBitArray<BitArrayAllocator>& bOutRemovedAssetData, TBitArray<BitArrayAllocator>& bOutRemovedPackageData);`
- L724 _private prototype_ `template<typename BitArrayAllocator> void RemoveAssetDatasImpl(TArrayView<FAssetData*> AssetDatas, TArrayView<const FCachedAssetKey> Keys, bool bRemoveDependencyData, #if UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS TArrayView<UE::AssetRegistry::Private::FAssetDataPtrIndex> AssetIndices, #endif TBitArray<BitArrayAllocator>& bOutRemovedAssetDatas, TBitArray<BitArrayAllocator>& bOutRemovedPackageDatas );`
- L732 _private prototype_ `void Shrink();` — Free slack memory accumulated in cache containers.
- L740 _private prototype_ `bool IsPackageUnmountedAndFiltered(const FName PackageName) const;` — Returns true if the given package should be filtered from the results because the package belongs to an unmounted content path. This can only happen when loading a cooked asset registry (@see bCookedGlobalAssetRegistryState), as it may contain state for plugins that are not currently loaded.
- L746 _private member_ `FAssetDataMap CachedAssets;` — Set of asset data for assets saved to disk. Searched via path name types, implicitly converted to FCachedAssetKey.
- L748 _private member_ `UE::AssetRegistry::Private::FIndirectAssetDataArrays IndirectAssetDataArrays;`
- L753 _private member_ `TMap<FName, TArray<FAssetData*, TInlineAllocator<1>> > CachedAssetsByPackageName;` — The map of package names to asset data for assets saved to disk
- L755 _private member_ `TMap<FName, TArray<FAssetData*> > CachedAssetsByPath;` — The map of long package path to asset data for assets saved to disk
- L757 _private member_ `TMap<FTopLevelAssetPath, TArray<FAssetData*> > CachedAssetsByClass;` — The map of class name to asset data for assets saved to disk
- L760 _private member_ `UE::AssetRegistry::Private::FAssetPackageNameMap CachedAssetsByPackageName;` — The map of package names to asset data for assets saved to disk
- L762 _private member_ `TMap<FName, TArray<FAssetDataPtrIndex> > CachedAssetsByPath;` — The map of long package path to asset data for assets saved to disk
- L764 _private member_ `TMap<FTopLevelAssetPath, TArray<FAssetDataPtrIndex> > CachedAssetsByClass;` — The map of class name to asset data for assets saved to disk
- L770 _private member_ `TMap<FName, TSet<FAssetData*> > CachedAssetsByTag;` — The map of asset tag to asset data for assets saved to disk
- L773 _private member_ `TMap<FName, TSet<FAssetDataPtrIndex> > CachedAssetsByTag;` — The map of asset tag to asset data for assets saved to disk
- L777 _private member_ `TMap<FName, TSet<FTopLevelAssetPath> > CachedClassesByTag;` — The map of asset tag to asset data for assets saved to disk
- L781 _private member_ `TMap<FAssetIdentifier, FDependsNode*> CachedDependsNodes;` — A map of object names to dependency data
- L784 _private member_ `TMap<FName, FAssetPackageData*> CachedPackageData;` — A map of Package Names to Package Data
- L790 _private member_ `TArray<FAssetData*> PreallocatedAssetDataBuffers;` — When loading a registry from disk, we can allocate all the FAssetData objects in one chunk, to save on 10s of thousands of heap allocations.
- L791 _private member_ `TArray<FDependsNode*> PreallocatedDependsNodeDataBuffers;`
- L792 _private member_ `TArray<FAssetPackageData*> PreallocatedPackageDataBuffers;`
- L798 _private member_ `int32 NumAssets = 0;` — Counters for asset/depends data memory allocation to ensure that every FAssetData and FDependsNode created is deleted.
- L799 _private member_ `int32 NumDependsNodes = 0;`
- L800 _private member_ `int32 NumPackageData = 0;`
- L803 _private member_ `bool bCookedGlobalAssetRegistryState = false;` — True if this asset registry state was loaded from a cooked asset registry
- L853 _function_ `inline FAssetRegistryState::FAssetRegistryState() #if UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS : CachedAssetsByPackageName(CachedAssets, IndirectAssetDataArrays) #endif`
- L860 _function_ `inline FAssetRegistryState::FAssetRegistryState(FAssetRegistryState&& Rhs) #if UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS : CachedAssetsByPackageName(CachedAssets, IndirectAssetDataArrays) #endif`
- L868 _function_ `inline const FAssetData* FAssetRegistryState::GetAssetByObjectPath(const FSoftObjectPath& ObjectPath) const`
- L873 _function_ `inline const FAssetData* FAssetRegistryState::GetAssetByObjectPath( const UE::AssetRegistry::Private::FCachedAssetKey& Key) const`
- L879 _function_ `inline FAssetData* FAssetRegistryState::GetMutableAssetByObjectPath(const FSoftObjectPath& ObjectPath) const`
- L884 _function_ `inline FAssetData* FAssetRegistryState::GetMutableAssetByObjectPath( const UE::AssetRegistry::Private::FCachedAssetKey& Key) const`
- L891 _function_ `inline void FAssetRegistryState::EnumerateAssetsByPackageName(const FName PackageName, TFunctionRef<bool(const FAssetData* AssetData)> Callback) const`
- L900 _function_ `inline void FAssetRegistryState::EnumerateMutableAssetsByPackageName(const FName PackageName, TFunctionRef<bool(FAssetData* AssetData)> Callback) const`
- L931 _function_ `inline TArray<const FAssetData*> FAssetRegistryState::CopyAssetsByPackageName(const FName PackageName) const`
- L943 _function_ `inline int32 FAssetRegistryState::NumAssetsByPackageName(const FName PackageName) const`
- L954 _function_ `inline void FAssetRegistryState::EnumerateAssetsByPackagePath(FName LongPackagePathName, TFunctionRef<bool(const FAssetData* AssetData)> Callback) const`
- L963 _function_ `inline void FAssetRegistryState::EnumerateMutableAssetsByPackagePath(FName LongPackagePathName, TFunctionRef<bool(FAssetData* AssetData)> Callback) const`
- L995 _function_ `inline void FAssetRegistryState::EnumerateAssetsByClassPathName( const FTopLevelAssetPath ClassPathName, TFunctionRef<bool(const FAssetData* AssetData)> Callback) const`
- L1022 _function_ `inline void FAssetRegistryState::EnumerateTags(TFunctionRef<bool(FName TagName)> Callback) const`
- L1037 _function_ `inline bool FAssetRegistryState::ContainsTag(FName TagName) const`
- L1046 _function_ `inline const TMap<FName, const FAssetPackageData*>& FAssetRegistryState::GetAssetPackageDataMap() const`
- L1051 _function_ `inline void FAssetRegistryState::GetPackageNames(TArray<FName>& OutPackageNames) const`
- L1060 _function_ `inline int32 FAssetRegistryState::GetNumAssets() const`
- L1065 _function_ `inline int32 FAssetRegistryState::GetNumPackages() const`
- L1070 _function_ `inline void FAssetRegistryState::InitializeFromExisting(const FAssetRegistryState& Existing, const FAssetRegistrySerializationOptions& Options, EInitializationMode InitializationMode, FAssetRegistryAppendResult* OutAppendResult)`

#### enum `FAssetRegistryState::ERemoveDependsFlags`  
`enum class ERemoveDependsFlags`  
_L676-684_
- L678 _public enumerator_ `None`
- L683 _public enumerator_ `RemoveOrphans = 1 << 0` — If passed in, RemoveDependsNode functions will remove nodes that were not in the remove request but that had links to the removed nodes and no longer have any links after the removals.

#### Free symbols / members of external scopes

- L40 _macro_ `#define UE_ASSETREGISTRY_CACHEDASSETSBYTAG WITH_EDITORONLY_DATA`
- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L817 _prototype_ `ENUM_CLASS_FLAGS(FAssetRegistryState::ERemoveDependsFlags);`
- L895 _function_ `` (scope `FAssetRegistryState::EnumerateAssetsByPackageName`)
- L936 _function_ `` (scope `FAssetRegistryState::CopyAssetsByPackageName`)
- L958 _function_ `` (scope `FAssetRegistryState::EnumerateAssetsByPackagePath`)

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryTelemetry.h` (Public)


#### struct `UE::Telemetry::AssetRegistry::FStartupTelemetry`  
`struct FStartupTelemetry`  
_L14-22_
- desc: Information about very early asset registry startup.
- L16 _public member_ `static constexpr inline FGuid TelemetryID = FGuid(0x903732ce, 0x8bd04eb9, 0x92170fde, 0x0a1c1562);`
- L19 _public member_ `double StartupDuration = 0.0;` — Time spent in synchronous initialization
- L21 _public member_ `bool bStartedAsyncGather = false;` — Whether async gather operation was started at this time

#### struct `UE::Telemetry::AssetRegistry::FSynchronousScanTelemetry`  
`struct FSynchronousScanTelemetry`  
_L25-45_
- desc: Information about a synchronous scan that was executed, blocking the calling thread.
- L27 _public member_ `static constexpr inline FGuid TelemetryID = FGuid(0x2b4b9f1a, 0xdcfd4958, 0xbe43ba9d, 0xae309392);`
- L30 _public member_ `TConstArrayView<FString> Directories;` — List of directories that were scanned
- L32 _public member_ `TConstArrayView<FString> Files;` — List of specific files that were scanned
- L34 _public member_ `UE::AssetRegistry::EScanFlags Flags = UE::AssetRegistry::EScanFlags::None;` — Flags controlling scan behavior
- L36 _public member_ `int32 NumFoundAssets = 0;` — Number of assets found by this scan
- L38 _public member_ `double Duration = 0.0;` — Duration of synchronous scan
- L40 _public member_ `bool bInitialSearchStarted = false;` — Whether the main background async gather was started at this time
- L42 _public member_ `bool bInitialSearchCompleted = false;` — Whether the main background async gather was completed at this time
- L44 _public member_ `bool bAdditionalMountSearchInProgress = false;` — Whether an additional main background async gather was started at this time

#### struct `UE::Telemetry::AssetRegistry::FGatherTelemetry`  
`struct FGatherTelemetry`  
_L51-76_
- desc: Information about asset registry scanning either as the initial scan when the process starts, or when an additional mount point is added. See the bIsInitialScan field to disambiguate. Note that for subsequent scans, the times other than TotalSearchDurationSeconds will be cumulative totals including previous work. This is also a good time to gather information about the contents of the asset registry.
- L53 _public member_ `static constexpr inline FGuid TelemetryID = FGuid(0xafcec052, 0x5d2c4850, 0xbfc6d11d, 0x3163ccd5);`
- L56 _public member_ `double TotalSearchDurationSeconds = 0.0;` — Total wall clock time between start of search and completion.
- L58 _public member_ `double TotalWorkTimeSeconds = 0.0;` — Total work time (includes work done in parallel stages)
- L60 _public member_ `double DiscoveryTimeSeconds = 0.0;` — Time spent discovering asset files on disk
- L62 _public member_ `double GatherTimeSeconds = 0.0;` — Time spent gathering asset data from files on disk (or cache)
- L64 _public member_ `double StoreTimeSeconds = 0.0;` — Time spent storing asset data in the asset registry for searching
- L66 _public member_ `int32 NumCachedDirectories = 0;` — Number of directories read from cache
- L68 _public member_ `int32 NumUncachedDirectories = 0;` — Number of directories scanned from disk
- L70 _public member_ `int32 NumCachedAssetFiles = 0;` — Number of asset files read from cache
- L72 _public member_ `int32 NumUncachedAssetFiles = 0;` — Number of asset files read loose from disk
- L75 _public member_ `bool bIsInitialScan = false;` — True if this was the initial startup scan - this should be true only once per process.

#### struct `UE::Telemetry::AssetRegistry::FDirectoryWatcherUpdateTelemetry`  
`struct FDirectoryWatcherUpdateTelemetry`  
_L79-93_
- desc: Information about an asset registry update that was triggered by the directory watcher module.
- L81 _public member_ `static constexpr inline FGuid TelemetryID = FGuid(0xa1da56e1, 0xe1314918, 0xba6fdb24, 0xb8911ce0);`
- L84 _public member_ `TConstArrayView<FFileChangeData> Changes;` — File change data from watcher
- L86 _public member_ `double DurationSeconds = 0.0;` — Total time spent in update handler
- L88 _public member_ `bool bInitialSearchStarted = false;` — Whether the main background async gather was started at this time
- L90 _public member_ `bool bInitialSearchCompleted = false;` — Whether the main background async gather was completed at this time
- L92 _public member_ `bool bAdditionalMountSearchInProgress = false;` — Whether an additional main background async gather was started at this time

#### struct `UE::Telemetry::AssetRegistry::FFileJournalErrorTelemetry`  
`struct FFileJournalErrorTelemetry`  
_L96-105_
- desc: Information about a failure in our FileJournal area
- L98 _public member_ `static constexpr inline FGuid TelemetryID = FGuid(0x761ebe19, 0x2f0c427e, 0xaec0f06d, 0xe116ff82);`
- L101 _public member_ `FString Directory;` — Directory that failed for our FileJournal calls
- L104 _public member_ `FString ErrorString;` — The error string returned from our lower level FileJournal calls

#### struct `UE::Telemetry::AssetRegistry::FFileJournalWrappedTelemetry`  
`struct FFileJournalWrappedTelemetry`  
_L107-114_
- L109 _public member_ `static constexpr inline FGuid TelemetryID = FGuid(0x542713AA, 0x04724D77, 0x8F7E2319, 0xA0204815);`
- L111 _public member_ `FString VolumeName;`
- L113 _public member_ `uint64 JournalMaximumSize;` — Size of journal that wrapped

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Telemetry` (scope `UE`)
- L11 _namespace_ `namespace AssetRegistry` (scope `UE::Telemetry`)

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/IAssetRegistry.h` (Public)


#### enum `EAssetAvailability::Type`  
`enum Type`  
_L41-47_
- L43 _public enumerator_ `DoesNotExist` — asset chunkid does not exist
- L44 _public enumerator_ `NotAvailable` — chunk containing asset has not been installed yet
- L45 _public enumerator_ `LocalSlow` — chunk containing asset is on local slow media (optical)
- L46 _public enumerator_ `LocalFast` — chunk containing asset is on local fast media (HDD)

#### enum `EAssetAvailabilityProgressReportingType::Type`  
`enum Type`  
_L52-56_
- L54 _public enumerator_ `ETA` — time remaining in seconds
- L55 _public enumerator_ `PercentageComplete` — percentage complete in 99.99 format

#### enum `UE::AssetRegistry::EScanFlags`  
`enum class EScanFlags : uint32`  
_L63-70_
- desc: Please update LexToString when modifying this enum
- L65 _public enumerator_ `None = 0`
- L66 _public enumerator_ `ForceRescan = 1 << 0` — the paths will be scanned again, even if they were previously scanned
- L67 _public enumerator_ `IgnoreDenyListScanFilters = 1 << 1` — ignore deny list scan filters
- L68 _public enumerator_ `WaitForInMemoryObjects = 1 << 2` — update the tags of all assets that have loaded into memory before returning from the scan
- L69 _public enumerator_ `IgnoreInvalidPathWarning = 1 << 3` — By default, scans of invalid paths (unmounted, or /Temp) log a warning. Suppress that warning.

#### enum `UE::AssetRegistry::EAssetSetManagerAssetFlags`  
`enum class EAssetSetManagerAssetFlags : uint32`  
_L76-80_
- desc: Properties about each node in the graph search conducted from SetManageReferences.
- L78 _public enumerator_ `None = 0x0`
- L79 _public enumerator_ `ScriptPackage = 0x1`

#### struct `UE::AssetRegistry::FShouldSetManagerContext`  
`struct FShouldSetManagerContext`  
_L84-104_
- desc: Information passed into ShouldSetManager calls from the graph search performed in SetManageReferences.
- L87 _public member_ `const FAssetIdentifier& Manager;` — The top-level manager node for which the search is conducted.
- L89 _public member_ `const FAssetIdentifier& Source;` — The source node of the edge in the graph search that is being asked about in the ShouldSetManager call.
- L91 _public member_ `const FAssetIdentifier& Target;` — The target node of the edge in the graph search that is being asked about in the ShouldSetManager call.
- L93 _public member_ `EAssetSetManagerAssetFlags ManagerAssetFlags;` — Properties of the manager node.
- L95 _public member_ `EAssetSetManagerAssetFlags SourceAssetFlags;` — Properties of the source node.
- L97 _public member_ `EAssetSetManagerAssetFlags TargetAssetFlags;` — Properties of the source node.
- L99 _public member_ `EAssetSetManagerFlags::Type EdgeFlags;` — Properties of the edge, and of the target's status in the current phase of SetManageReferences.
- L101 _public member_ `EDependencyCategory EdgeARCategory;` — AssetRegistry category of the edge: which kind of AssetRegistry dependency the edge comes from.
- L103 _public member_ `EDependencyProperty EdgeARProperties;` — AssetRegistry Properties of the edge: which properties within its category the edge has.

#### struct `UE::AssetRegistry::FSetManageReferencesContext`  
`struct FSetManageReferencesContext`  
_L111-130_
- desc: Information passed into SetManageReferences from ther caller. Includes arguments for the call as well as scratch space data that is shared across multiple SetManageReferences calls conducted by the caller for different priorities of managers.
- L114 _public member_ `const TMultiMap<FAssetIdentifier, FAssetIdentifier>* ManagerMap = nullptr;` — Map from Managing asset to directly-managed assets for the current call to SetManageReferences.
- L116 _public member_ `bool bClearExisting = false;` — If true, will clear any existing manage dependencies. Should be set only for the first call.
- L118 _public member_ `EDependencyCategory RecurseType = EDependencyCategory::None;` — Dependency types to follow during the graph search out from the starting nodes in ManagerMap.
- L123 _public member_ `TOptional<TFunctionRef<EAssetSetManagerResult::Type(FShouldSetManagerContext& Context)>> ShouldSetManager;` — Predicate that is called on recursive dependencies if bound, returns whether the graph search should visit a target node from a source node and whether that visit should be recursive.
- L129 _public member_ `TPimplPtr<FSetManageReferencesScratch> Scratch;` — Scratch variable that will be constructed during the call, and should not be modified by the caller but should be preserved across a series of calls to SetManageReferences for managers of different priorities

#### enum `UE::AssetRegistry::EAppendMode`  
`enum class EAppendMode`  
_L135-141_
- desc: Enum controlling how FAssetRegistryStates are merged during Append functions, e.g. when adding plugin's serialized AssetRegistry into global AssetRegistry.
- L137 _public enumerator_ `Rebuild`
- L138 _public enumerator_ `OnlyUpdateExisting`
- L139 _public enumerator_ `Append`
- L140 _public enumerator_ `OnlyUpdateNew`

#### struct `FAssetRegistryDependencyOptions`  
`struct FAssetRegistryDependencyOptions`  
_L146-181_
- reflection: `USTRUCT(BlueprintType)`
- L150 _public prototype_ `bool GetPackageQuery(UE::AssetRegistry::FDependencyQuery& Flags) const;`
- L151 _public prototype_ `bool GetSearchableNameQuery(UE::AssetRegistry::FDependencyQuery& Flags) const;`
- L152 _public prototype_ `bool GetManageQuery(UE::AssetRegistry::FDependencyQuery& Flags) const;`
- L156 _public member_ `bool bIncludeSoftPackageReferences = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetRegistry")` — Dependencies which don't need to be loaded for the object to be used (i.e. soft object paths)
- L160 _public member_ `bool bIncludeHardPackageReferences = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetRegistry")` — Dependencies which are required for correct usage of the source asset, and must be loaded at the same time
- L164 _public member_ `bool bIncludeGamePackageReferences = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetRegistry")` — Dependencies which are needed in the game as well as the editor.
- L168 _public member_ `bool bIncludeEditorOnlyPackageReferences = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetRegistry")` — Dependencies which are only needed in the editor.
- L172 _public member_ `bool bIncludeSearchableNames = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetRegistry")` — References to specific SearchableNames inside a package
- L176 _public member_ `bool bIncludeSoftManagementReferences = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetRegistry")` — Indirect management references, these are set through recursion for Primary Assets that manage packages or other primary assets
- L180 _public member_ `bool bIncludeHardManagementReferences = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetRegistry")` — Reference that says one object directly manages another object, set when Primary Assets manage things explicitly

#### struct `FAssetDependency`  
`struct FAssetDependency`  
_L184-233_
- desc: An output struct to hold both an AssetIdentifier and the properties of the dependency on that AssetIdentifier
- L186 _public member_ `FAssetIdentifier AssetId;`
- L187 _public member_ `UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::None;`
- L188 _public member_ `UE::AssetRegistry::EDependencyProperty Properties = UE::AssetRegistry::EDependencyProperty::None;`
- L190 _public function_ `bool operator==(const FAssetDependency& Other) const`
- L194 _public function_ `bool LexicalLess(const FAssetDependency& Other) const`
- L207 _public function_ `static FAssetDependency PackageDependency(FName PackageName, UE::AssetRegistry::EDependencyProperty Properties)`
- L223 _public prototype_ `void WriteCompactBinary(FCbWriter& Writer) const;`

#### class `UAssetRegistry`  
`class UAssetRegistry : public UInterface`  
_L236-239_
- reflection: `UINTERFACE(MinimalApi, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IAssetRegistry`  
`class IAssetRegistry`  
_L264-1352_
- desc: Global singleton interface for accessing a catalog of all packages (and some other content file types) that are stored in any mounted directory. In editor this information is gathered from the package files on disk during a gather step at editor startup. In cooked runtimes this information was calculated during cook and is serialized out of a single file (after pruning information not necessary at runtime.) Some API notes: bIncludeOnlyOnDiskAssets Most query functions that return FAssetData take this argument. If true, only data collected from disk and stored in the AssetRegistry will be returned. If false, and the object is loaded in memory, the returned AssetData will be calculated from the object in memory because the InMemoryData is more likely to be up-to-date. The InMemory data will sometimes vary from the DiskGatheredData. When InMemoryData is returned some categories of data that are always missing from the object in memory (e.g. GetAssetRegistryTags(EAssetRegistryTagsCaller::SavePackage)) are read from the DiskGatheredData and added to the InMemoryData. Setting this value to true will always be faster than setting it to false, because the same registry lookups are performed in either case, but the InMemoryData lookup is skipped in the true case. The default is usually false.
- L268 _public function_ `static IAssetRegistry* Get()`
- L272 _public function_ `static IAssetRegistry& GetChecked()`
- L286 _public prototype_ `virtual bool HasAssets(const FName PackagePath, const bool bRecursive = false) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Does the given path contain assets, optionally also testing sub-paths? @param PackagePath the path to query asset data in (eg, /Game/MyFolder) @param bRecursive if true, the supplied path will be tested recursively
- L298 _public prototype_ `virtual bool GetAssetsByPackageName(FName PackageName, TArray<FAssetData>& OutAssetData, bool bIncludeOnlyOnDiskAssets = false, bool bSkipARFilteredAssets=true) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="AssetRegistry")` — Gets asset data for the assets in the package with the specified package name @param PackageName the package name for the requested assets (eg, /Game/MyFolder/MyAsset) @param OutAssetData the list of assets in this path @param bIncludeOnlyOnDiskAssets If true, use only DiskGatheredData, do not calculate from UObjects. @see IAssetRegistry class header for bIncludeOnlyOnDiskAssets. @param bSkipARFilteredAssets If true, skips Objects that return true for IsAsset but are not assets in the current platform.
- L311 _public prototype_ `virtual bool GetAssetsByPath(FName PackagePath, TArray<FAssetData>& OutAssetData, bool bRecursive = false, bool bIncludeOnlyOnDiskAssets = false) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Gets asset data for all assets in the supplied folder path @param PackagePath the path to query asset data in (eg, /Game/MyFolder) @param OutAssetData the list of assets in this path @param bIncludeOnlyOnDiskAssets If true, use only DiskGatheredData, do not calculate from UObjects. @see IAssetRegistry class header for bIncludeOnlyOnDiskAssets. @param bRecursive if true, all supplied paths will be searched recursively
- L324 _public prototype_ `virtual bool GetAssetsByPaths(TArray<FName> PackagePaths, TArray<FAssetData>& OutAssetData, bool bRecursive = false, bool bIncludeOnlyOnDiskAssets = false) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "AssetRegistry")` — Gets asset data for all assets in any of the supplied folder paths @param PackagePaths the paths to query asset data in (eg, /Game/MyFolder) @param OutAssetData the list of assets in this path @param bIncludeOnlyOnDiskAssets If true, use only DiskGatheredData, do not calculate from UObjects. @see IAssetRegistry class header for bIncludeOnlyOnDiskAssets. @param bRecursive if true, all supplied paths will be searched recursively
- L335 _public prototype_ `virtual bool GetAssetsByClass(FTopLevelAssetPath ClassPathName, TArray<FAssetData>& OutAssetData, bool bSearchSubClasses = false) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Gets asset data for all assets with the supplied class @param ClassPathName the full path of the class name of the assets requested, in a TopLevelAssetPath structure. @param OutAssetData the list of assets in this path @param bSearchSubClasses if true, all subclasses of the passed in class will be searched as well
- L343 _public prototype_ `virtual bool GetAssetsByTags(const TArray<FName>& AssetTags, TArray<FAssetData>& OutAssetData) const = 0;` — Gets asset data for all assets with the supplied tags, regardless of their value @param AssetTags the tags associated with the assets requested @param OutAssetData the list of assets with any of the given tags
- L351 _public prototype_ `virtual bool GetAssetsByTagValues(const TMultiMap<FName, FString>& AssetTagsAndValues, TArray<FAssetData>& OutAssetData) const = 0;` — Gets asset data for all assets with the supplied tags and values @param AssetTagsAndValues the tags and values associated with the assets requested @param OutAssetData the list of assets with any of the given tags and values
- L363 _public prototype_ `virtual bool GetAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets=true) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="AssetRegistry")` — Gets asset data for all assets that match the filter. Assets returned must satisfy every filter component if there is at least one element in the component's array. Assets will satisfy a component if they match any of the elements in it. @param Filter filter to apply to the assets in the AssetRegistry @param OutAssetData the list of assets in this path @param bSkipARFilteredAssets If true, skips Objects that return true for IsAsset but are not assets in the current platform.
- L364 _public prototype_ `virtual bool GetAssets(const FARCompiledFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets=true) const = 0;`
- L378 _public prototype_ `virtual bool GetInMemoryAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets=true) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="AssetRegistry")` — Gets asset data for in-memory assets only, that match the filter. Returns assets that would be excluded by calling GetAssets with bIncludeOnlyOnDiskAssets set to true. @note This method IGNORES the value of bIncludeOnlyOnDiskAssets on the provided filter. Assets returned must satisfy every filter component if there is at least one element in the component's array. Assets will satisfy a component if they match any of the elements in it. @param Filter filter to apply to the assets in the AssetRegistry @param OutAssetData the list of assets in this path @param bSkipARFilteredAssets If true, skips Objects that return true for IsAsset but are not assets in the current platform.
- L379 _public prototype_ `virtual bool GetInMemoryAssets(const FARCompiledFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets=true) const = 0;`
- L394 _public prototype_ `virtual bool EnumerateAssets(const FARFilter& Filter, TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const = 0;` — Enumerate asset data for all assets that match the filter. Assets returned must satisfy every filter component if there is at least one element in the component's array. Assets will satisfy a component if they match any of the elements in it. @param Filter filter to apply to the assets in the AssetRegistry @param Callback function to call for each asset data enumerated @param InEnumerateFlags flags to control enumeration and filtering. @see EEnumerateAssetsFlags. EEnumerateAssetsFlags::Parallel note: in-memory assets enumeration ignores the parallel flag and is always single-threaded. @return False if filter is invalid, otherwise true.
- L396 _public prototype_ `virtual bool EnumerateAssets(const FARCompiledFilter& Filter, TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const = 0;`
- L401 _public prototype_ `virtual FAssetData GetAssetByObjectPath( const FName ObjectPath, bool bIncludeOnlyOnDiskAssets = false ) const = 0;` — `UE_DEPRECATED(5.6, "Asset path FNames have been deprecated, use Soft Object Path instead.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="AssetRegistry", meta=(DeprecatedFunction="Note", DeprecationMessage="Use other version that takes a SoftObjectPath"))`
- L413 _public prototype_ `virtual FAssetData K2_GetAssetByObjectPath(const FSoftObjectPath& ObjectPath, bool bIncludeOnlyOnDiskAssets = false, bool bSkipARFilteredAssets = true) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry", DisplayName="Get Asset By Object Path")` — Gets the asset data for the specified object path @param ObjectPath the path of the object to be looked up @param bIncludeOnlyOnDiskAssets If true, use only DiskGatheredData, do not calculate from UObjects. @see IAssetRegistry class header for bIncludeOnlyOnDiskAssets. @param bSkipARFilteredAssets If true, skips Objects that return true for IsAsset but are not assets in the current platform. @return the assets data;Will be invalid if object could not be found
- L425 _public prototype_ `virtual FAssetData GetAssetByObjectPath(const FSoftObjectPath& ObjectPath, bool bIncludeOnlyOnDiskAssets = false, bool bSkipARFilteredAssets = true) const = 0;` — Gets the asset data for the specified object path @param ObjectPath the path of the object to be looked up @param bIncludeOnlyOnDiskAssets If true, use only DiskGatheredData, do not calculate from UObjects. @see IAssetRegistry class header for bIncludeOnlyOnDiskAssets. @param bSkipARFilteredAssets If true, skips Objects that return true for IsAsset but are not assets in the current platform. @return the assets data;Will be invalid if object could not be found
- L435 _public prototype_ `virtual UE::AssetRegistry::EExists TryGetAssetByObjectPath(const FSoftObjectPath& ObjectPath, FAssetData& OutAssetData) const = 0;` — Tries to get the asset data for the specified object path @param ObjectPath the path of the object to be looked up @param OutAssetData out FAssetData @return Enum return code
- L447 _public prototype_ `virtual UE::AssetRegistry::EExists TryGetAssetPackageData(FName PackageName, FAssetPackageData& OutAssetPackageData, bool bFailIfLockHeld = false) const = 0;` — Tries to get the pacakge data for a specified path @param PackageName name of the package @param OutAssetPackageData out FAssetPackageData @param bFailIfLockHeld If the AssetRegistry is currently being written to by another thread this function will return EExists::Unknown rather than waiting for safe read access. @return Enum return code
- L461 _public prototype_ `virtual UE::AssetRegistry::EExists TryGetAssetPackageData(FName PackageName, FAssetPackageData& OutAssetPackageData, FName& OutCorrectCasePackageName, bool bFailIfLockHeld = false) const = 0;` — Tries to get the package data for the specified package name. If found, OutCorrectCasePackageName will be populated with the PackageName that matches the casing used by the filesystem @param PackageName name of the package @param OutAssetPackageData out FAssetPackageData @param OutCorrectCasePackageName out FName matching filesystem casing @param bFailIfLockHeld If the AssetRegistry is currently being written to by another thread this function will return EExists::Unknown rather than waiting for safe read access. @return Return code enum
- L471 _public prototype_ `virtual bool GetAllAssets(TArray<FAssetData>& OutAssetData, bool bIncludeOnlyOnDiskAssets = false) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Gets asset data for all assets in the registry. This method may be slow, use a filter if possible to avoid iterating over the entire registry. @param OutAssetData the list of assets in this path
- L483 _public prototype_ `virtual bool EnumerateAllAssets(TFunctionRef<bool(const FAssetData&)> Callback, UE::AssetRegistry::EEnumerateAssetsFlags InEnumerateFlags = UE::AssetRegistry::EEnumerateAssetsFlags::None) const = 0;` — Enumerate asset data for all assets currently cached in the asset registry. This method may be slow, use a filter if possible to avoid iterating over the entire registry. @param Callback function to call for each asset data enumerated @param InEnumerateFlags flags to control enumeration and filtering. @see IAssetRegistry class header for EEnumerateAssetsFlags. EEnumerateAssetsFlags::Parallel note: in-memory assets enumeration ignores the parallel flag and is always single-threaded.
- L493 _public prototype_ `virtual void GetPackagesByName(FStringView PackageName, TArray<FName>& OutPackageNames) const = 0;` — Gets the LongPackageName for all packages with the given PackageName. Call to check existence of a LongPackageName or find all packages with a ShortPackageName. @param PackageName Name of the package to find, may be a LongPackageName or ShortPackageName. @param OutPackageNames All discovered matching LongPackageNames are appended to this array.
- L503 _public prototype_ `virtual FName GetFirstPackageByName(FStringView PackageName) const = 0;` — Returns the first LongPackageName found for the given PackageName. Issues a warning and returns the first (sorted lexically) if there is more than one. Call to check existence of a LongPackageName or find a package with a ShortPackageName. @param PackageName Name of the package to find, may be a LongPackageName or ShortPackageName. @return The first LongPackageName of the matching package, or NAME_None if not found.
- L517 _public prototype_ `virtual bool GetDependencies(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const = 0;` — Gets a list of AssetIdentifiers or FAssetDependencies that are referenced by the supplied AssetIdentifier. Only returns dependencies reported in the on-disk package. @param AssetIdentifier The name of the package/name for which to gather dependencies. @param OutDependencies A list of things that are referenced by AssetIdentifier. @param Category Which category(ies) of dependencies to include in the output list. Dependencies matching ANY of the OR'd categories will be returned. @param Flags	Which flags are required present or not present on the dependencies. Dependencies matching ALL required and NONE excluded bits will be returned. For each potentially returned dependency, flags not applicable to their category are ignored.
- L520 _public prototype_ `virtual bool GetDependencies(const FAssetIdentifier& AssetIdentifier, TArray<FAssetDependency>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const = 0;`
- L536 _public prototype_ `virtual bool GetDependencies(FName PackageName, TArray<FName>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::Package, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const = 0;` — Gets a list of PackageNames that are referenced by the supplied package. Only returns dependencies reported in the on-disk package. @param PackageName The name of the package for which to gather dependencies (eg, /Game/MyFolder/MyAsset) @param OutDependencies A list of packages that are referenced by the package whose path is PackageName @param Category Which category(ies) of dependencies to include in the output list. Dependencies matching ANY of the OR'd categories will be returned. @param Flags	Which flags are required present or not present on the dependencies. Dependencies matching ALL required and NONE excluded bits will be returned. For each potentially returned dependency, flags not applicable to their category are ignored.
- L552 _public prototype_ `virtual bool ContainsDependency(FName PackageName, FName QueryDependencyName, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::Package, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const = 0;` — Return whether the supplied package references the query package. Only considers dependencies reported in the on-disk package. @param PackageName The name of the package for which to inspect dependencies (eg, /Game/MyFolder/MyAsset) @param QueryDependencyName Which package to look for in PackageName's dependencies @param Category Which category(ies) of dependencies to look in for QueryDependencyName. Dependencies matching ANY of the OR'd categories will be considered. @param Flags Which flags are required present or not present on the dependencies. Dependencies matching ALL required and NONE excluded bits will be considered. For each potentially considered dependency, flags not applicable to their category are ignored.
- L565 _public prototype_ `virtual bool K2_GetDependencies(FName PackageName, const FAssetRegistryDependencyOptions& DependencyOptions, TArray<FName>& OutDependencies) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry", meta=(DisplayName="Get Dependencies", ScriptName="GetDependencies"))` — Gets a list of paths to objects that are referenced by the supplied package. (On disk references ONLY) @param PackageName The name of the package for which to gather dependencies (eg, /Game/MyFolder/MyAsset) @param DependencyOptions Which kinds of dependencies to include in the output list @param OutDependencies A list of packages that are referenced by the package whose path is PackageName
- L580 _public prototype_ `virtual bool GetReferencers(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const = 0;` — Gets a list of AssetIdentifiers or FAssetDependencies that reference the supplied AssetIdentifier. Only returns referencers reported in the on-disk package. @param AssetIdentifier The name of the package/name for which to gather referencers (eg, /Game/MyFolder/MyAsset) @param OutReferencers A list of things that reference AssetIdentifier. @param Category Which category(ies) of referencers to include in the output list. Referencers that have a dependency matching ANY of the OR'd categories will be returned. @param Flags Which flags are required present or not present on the referencer's dependency. Referencers that have a dependency matching ALL required and NONE excluded bits will be returned. For each potentially returned dependency, flags not applicable to their category are ignored.
- L583 _public prototype_ `virtual bool GetReferencers(const FAssetIdentifier& AssetIdentifier, TArray<FAssetDependency>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const = 0;`
- L598 _public prototype_ `virtual bool GetReferencers(FName PackageName, TArray<FName>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::Package, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const = 0;` — Gets a list of PackageNames that reference the supplied package. (On disk references ONLY) @param PackageName The name of the package for which to gather dependencies (eg, /Game/MyFolder/MyAsset) @param OutReferencers A list of packages that reference the package whose path is PackageName @param Category Which category(ies) of referencers to include in the output list. Referencers that have a dependency matching ANY of the OR'd categories will be returned. @param Flags Which flags are required present or not present on the referencer's dependency. Referencers that have a dependency matching ALL required and NONE excluded bits will be returned. For each potentially returned dependency, flags not applicable to their category are ignored.
- L611 _public prototype_ `virtual bool K2_GetReferencers(FName PackageName, const FAssetRegistryDependencyOptions& ReferenceOptions, TArray<FName>& OutReferencers) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry", meta=(DisplayName="Get Referencers", ScriptName="GetReferencers"))` — Gets a list of packages that reference the supplied package. (On disk references ONLY) @param PackageName		the name of the package for which to gather dependencies (eg, /Game/MyFolder/MyAsset) @param ReferenceOptions	which kinds of references to include in the output list @param OutReferencers	a list of packages that reference the package whose path is PackageName
- L615 _public prototype_ `virtual TOptional<FAssetPackageData> GetAssetPackageDataCopy(FName PackageName) const = 0;` — Finds Package data for a package name. This data is only updated on save and can only be accessed for valid packages
- L618 _public prototype_ `virtual TArray<TOptional<FAssetPackageData>> GetAssetPackageDatasCopy(TArrayView<FName> PackageNames) const = 0;` — Find Package Data for the packages name. This data is only updated on save and can only be accessed for valid packages
- L628 _public prototype_ `virtual void EnumerateAllPackages(TFunctionRef<void(FName PackageName, const FAssetPackageData& PackageData)> Callback, UE::AssetRegistry::EEnumeratePackagesFlags InEnumerateFlags = UE::AssetRegistry::EEnumeratePackagesFlags::None) const = 0;` — Enumerate all PackageDatas in the AssetRegistry. The callback is called from within the AssetRegistry's lock, so it must not call arbitrary code that could call back into the AssetRegistry; doing so would deadlock. @param Callback function to call for each package data enumerated @param InEnumerateFlags flags to control enumeration @see EEnumeratePackagesFlags
- L640 _public prototype_ `virtual bool DoesPackageExistOnDisk(FName PackageName, FString* OutCorrectCasePackageName = nullptr, FString* OutExtension = nullptr) const = 0;` — Checks if the specified package exists on disk. If the package exists and the optional parameters are provided, OutCorrectCasePackageName will be populated with the case matching package name found on disk and OutExtension will be populated with the extension for the package (dot included) if the package contains assets @param PackageName				the name of the package to check for existence on disk (eg, /Game/MyFolder/MyAsset) @param OutCorrectCasePackageName 	out package name matching the case on disk @param OutExtension				out extension for packages containing assets (dot included)
- L647 _public prototype_ `virtual FSoftObjectPath GetRedirectedObjectPath(const FSoftObjectPath& ObjectPath) = 0;` — Uses the asset registry to look for ObjectRedirectors. This will follow the chain of redirectors. It will return the original path if no redirectors are found.
- L655 _public prototype_ `virtual bool GetAncestorClassNames(FTopLevelAssetPath ClassPathName, TArray<FTopLevelAssetPath>& OutAncestorClassNames) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "AssetRegistry", meta=(DisplayName = "GetAncestorClassNames", ScriptName = "GetAncestorClassNames"))` — Returns true if the specified ClassName's ancestors could be found. If so, OutAncestorClassNames is a list of all its ancestors. This can be slow if temporary caching mode is not on.
- L664 _public prototype_ `virtual void GetDerivedClassNames(const TArray<FTopLevelAssetPath>& ClassNames, const TSet<FTopLevelAssetPath>& ExcludedClassNames, TSet<FTopLevelAssetPath>& OutDerivedClassNames) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "AssetRegistry", meta=(DisplayName = "GetDerivedClassNames", ScriptName = "GetDerivedClassNames"))` — Returns the names of all classes derived by the supplied class names, excluding any classes matching the excluded class names. This can be slow if temporary caching mode is not on.
- L669 _public prototype_ `virtual void GetAllCachedPaths(TArray<FString>& OutPathList) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Gets a list of all paths that are currently cached
- L672 _public prototype_ `virtual void EnumerateAllCachedPaths(TFunctionRef<bool(FString)> Callback) const = 0;` — Enumerate all the paths that are currently cached
- L675 _public prototype_ `virtual void EnumerateAllCachedPaths(TFunctionRef<bool(FName)> Callback) const = 0;` — Enumerate all the paths that are currently cached
- L679 _public prototype_ `virtual void GetSubPaths(const FString& InBasePath, TArray<FString>& OutPathList, bool bInRecurse) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Gets a list of all paths that are currently cached below the passed-in base path
- L682 _public prototype_ `virtual void GetSubPaths(const FName& InBasePath, TArray<FName>& OutPathList, bool bInRecurse) const = 0;` — Gets a list of all paths by name that are currently cached below the passed-in base path
- L685 _public prototype_ `virtual void EnumerateSubPaths(const FString& InBasePath, TFunctionRef<bool(FString)> Callback, bool bInRecurse) const = 0;` — Enumerate the all paths that are currently cached below the passed-in base path
- L688 _public prototype_ `virtual void EnumerateSubPaths(const FName InBasePath, TFunctionRef<bool(FName)> Callback, bool bInRecurse) const = 0;` — Enumerate the all paths that are currently cached below the passed-in base path
- L692 _public prototype_ `virtual void RunAssetsThroughFilter(UPARAM(ref) TArray<FAssetData>& AssetDataList, const FARFilter& Filter) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Trims items out of the asset data list that do not pass the supplied filter
- L696 _public prototype_ `virtual void UseFilterToExcludeAssets(UPARAM(ref) TArray<FAssetData>& AssetDataList, const FARFilter& Filter) const = 0;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "AssetRegistry")` — Trims items out of the asset data list that pass the supplied filter
- L699 _public prototype_ `virtual void UseFilterToExcludeAssets(TArray<FAssetData>& AssetDataList, const FARCompiledFilter& CompiledFilter) const = 0;` — Trims items out of the asset data list that pass the supplied filter
- L702 _public prototype_ `virtual bool IsAssetIncludedByFilter(const FAssetData& AssetData, const FARCompiledFilter& Filter) const = 0;` — Tests to see whether the given asset would be included (passes) the given filter
- L705 _public prototype_ `virtual bool IsAssetExcludedByFilter(const FAssetData& AssetData, const FARCompiledFilter& Filter) const = 0;` — Tests to see whether the given asset would be excluded (fails) the given filter
- L708 _public prototype_ `virtual void CompileFilter(const FARFilter& InFilter, FARCompiledFilter& OutCompiledFilter) const = 0;` — Modifies passed in filter optimize it for query and expand any recursive paths and classes
- L714 _public prototype_ `virtual void SetTemporaryCachingMode(bool bEnable) = 0;` — Enables or disable temporary search caching, when this is enabled scanning/searching is faster because we assume no objects are loaded between scans. Disabling frees any caches created.
- L719 _public prototype_ `virtual void SetTemporaryCachingModeInvalidated() = 0;` — Mark that the temporary cached needs to be updated before being used again, because e.g. a new class was loaded. Does nothing if TemporaryCachingMode is not enabled
- L722 _public prototype_ `virtual bool GetTemporaryCachingMode() const = 0;` — Returns true if temporary caching mode enabled
- L729 _public prototype_ `virtual EAssetAvailability::Type GetAssetAvailability(const FAssetData& AssetData) const = 0;` — Gets the current availability of an asset, primarily for streaming install purposes. @param FAssetData the asset to check for availability
- L737 _public prototype_ `virtual float GetAssetAvailabilityProgress(const FAssetData& AssetData, EAssetAvailabilityProgressReportingType::Type ReportType) const = 0;` — Gets an ETA or percentage complete for an asset that is still in the process of being installed. @param FAssetData the asset to check for progress status @param ReportType the type of report to query.
- L744 _public prototype_ `virtual bool GetAssetAvailabilityProgressTypeSupported(EAssetAvailabilityProgressReportingType::Type ReportType) const = 0;` — @param ReportType The report type to query. Returns if a given report type is supported on the current platform
- L751 _public prototype_ `virtual void PrioritizeAssetInstall(const FAssetData& AssetData) const = 0;` — Hint the streaming installers to prioritize a specific asset for install. @param FAssetData the asset which needs to have installation prioritized
- L760 _public prototype_ `virtual bool HasVerseFiles(FName PackagePath, bool bRecursive = false) const = 0;` — Returns whether the supplied folder contains any verse file @param PackagePath the path to query asset data in (e.g. /Game/MyFolder) @param bRecursive if true, the supplied path will be searched recursively @return True if any verse file is found under the supplied folder
- L770 _public prototype_ `virtual bool GetVerseFilesByPath(FName PackagePath, TArray<FName>& OutFilePaths, bool bRecursive = false) const = 0;` — Gets paths for all Verse files in the supplied folder @param PackagePath the path to query asset data in (e.g. /Game/MyFolder) @param OutFilePaths the list of Verse files in this path, as pseudo UE LongPackagePaths with extension (e.g. /Game/MyFolder/MyVerseFile.verse) @param bRecursive if true, the supplied path will be searched recursively
- L776 _public prototype_ `virtual bool AddPath(const FString& PathToAdd) = 0;` — Adds the specified path to the set of cached paths. These will be returned by GetAllCachedPaths(). Returns true if the path was actually added and false if it already existed.
- L782 _public prototype_ `virtual bool RemovePath(const FString& PathToRemove) = 0;` — Attempts to remove the specified path to the set of cached paths. This will only succeed if there are no assets left in the specified path.
- L785 _public prototype_ `virtual bool PathExists(const FString& PathToTest) const = 0;` — Queries whether the given path exists in the set of cached paths
- L786 _public prototype_ `virtual bool PathExists(const FName PathToTest) const = 0;`
- L793 _public prototype_ `virtual void ScanPathsSynchronous(const TArray<FString>& InPaths, bool bForceRescan = false, bool bIgnoreDenyListScanFilters = false) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Scan the supplied paths recursively right now and populate the asset registry. If bForceRescan is true, the paths will be scanned again, even if they were previously scanned.
- L801 _public prototype_ `virtual void ScanFilesSynchronous(const TArray<FString>& InFilePaths, bool bForceRescan = false) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Scan the specified individual files right now and populate the asset registry. If bForceRescan is true, the paths will be scanned again, even if they were previously scanned.
- L804 _public prototype_ `virtual void ScanSynchronous(const TArray<FString>& InPaths, const TArray<FString>& InFilePaths, UE::AssetRegistry::EScanFlags InScanFlags = UE::AssetRegistry::EScanFlags::None) = 0;` — Scan the supplied paths and files recursively right now and populate the asset registry.
- L809 _public prototype_ `virtual void SearchAllAssets(bool bSynchronousSearch) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Look for all assets on disk (can be async or synchronous)
- L816 _public prototype_ `virtual bool IsSearchAllAssets() const = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Whether SearchAllAssets has been called, or was auto-called at startup. When async (editor or cooking), if SearchAllAssets has ever been called, any newly-mounted directory will be automatically searched.
- L823 _public prototype_ `virtual bool IsSearchAsync() const = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Whether searching is done async (and was started at startup), or synchronously and on-demand, requiring ScanPathsSynchronous or SearchAllAssets.
- L830 _public prototype_ `virtual void WaitForCompletion() = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Wait for scan to be complete. If called during editor startup before OnPostEngineInit, and there are assets with classes in not-yet-loaded plugin modules, WaitForCompletion returns silently with those assets still ungathered.
- L836 _public prototype_ `virtual void WaitForPremadeAssetRegistry() = 0;` — Wait for premade asset registry load to be completed, for use when querying the asset registry prior to flushing in ScanPathSynchronous. Will no-op if no such asset registry exists.
- L842 _public prototype_ `virtual void ClearGathererCache() = 0;` — Empty the global gatherer's cache and disable further caching of scans from disk. Used to save memory when cooking after the scan is complete.
- L846 _public prototype_ `virtual void WaitForPackage(const FString& PackageName) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Wait for the scan of a specific package to be complete
- L853 _public prototype_ `virtual void PrioritizeSearchPath(const FString& PathToPrioritize) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — If assets are currently being asynchronously scanned in the specified path, this will cause them to be scanned before other assets.
- L857 _public prototype_ `virtual void ScanModifiedAssetFiles(const TArray<FString>& InFilePaths) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Forces a rescan of specific filenames, call this when you need to refresh from disk
- L858 _public prototype_ `virtual void ScanModifiedAssetFiles(const TArray<FString>& InFilePaths, UE::AssetRegistry::EScanFlags ScanFlags) = 0;`
- L861 _public prototype_ `DECLARE_EVENT_OneParam( IAssetRegistry, FFilesBlockedEvent, const TArray<FString>& );` — Event for when one or more files have been blocked from the registry
- L862 _public prototype_ `virtual FFilesBlockedEvent& OnFilesBlocked() = 0;`
- L869 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FPathsEvent, TConstArrayView<FStringView> );` — Events for when paths (folders/directories) are added to and removed from the asset registry. Both batch and singular events will be called for the same set of paths in all cases. Prefer the batched versions as the singular versions will be deprecated in a future release.
- L870 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FPathAddedEvent, const FString& );`
- L871 _public prototype_ `DECLARE_EVENT_OneParam( IAssetRegistry, FPathRemovedEvent, const FString& );`
- L872 _public prototype_ `virtual FPathsEvent& OnPathsAdded() = 0;`
- L873 _public prototype_ `virtual FPathsEvent& OnPathsRemoved() = 0;`
- L874 _public prototype_ `virtual FPathAddedEvent& OnPathAdded() = 0;`
- L875 _public prototype_ `virtual FPathRemovedEvent& OnPathRemoved() = 0;`
- L878 _public prototype_ `virtual void AssetCreated(UObject* NewAsset) = 0;` — Informs the asset registry that an in-memory asset has been created
- L881 _public prototype_ `virtual void AssetDeleted(UObject* DeletedAsset) = 0;` — Informs the asset registry that an in-memory asset has been deleted
- L884 _public prototype_ `virtual void AssetRenamed(const UObject* RenamedAsset, const FString& OldObjectPath) = 0;` — Informs the asset registry that an in-memory asset has been renamed
- L890 _public prototype_ `virtual void AssetsSaved(TArray<FAssetData>&& Assets) = 0;` — Called during SavePackage to update the AssetRegistry's copy of the AssetDatas in the package to match the newly saved values.
- L903 _public prototype_ `virtual void AssetUpdateTags(UObject* Object, EAssetRegistryTagsCaller Caller) = 0;` — Called on demand from systems that need to fully update an AssetData's tags. When an Asset is loaded its tags are updated by calling GetAssetRegistryTags(EAssetRegistryTagsCaller::AssetRegistryLoad), but that version of the function is allowed to skip writing expensive tags, so tags that exist in the old AssetData but not in the results from GetAssetRegistryTags(EAssetRegistryTagsCaller::AssetRegistryLoad) are kept because they might be skipped expensive tags. When an asset is saved, all old tags are deleted and GetAssetRegistryTags(EAssetRegistryTagsCaller::SavePackage) is called. AssetUpdateTags allows a manual trigger of the on-SavePackage behavior: all old tags are deleted and GetAssetRegistryTags(Caller) is called. Pass in EAssetRegistryTagsCaller::FullUpdate to behave the same as SavePackage.
- L906 _public prototype_ `virtual bool VerseCreated(const FString& FilePathOnDisk) = 0;` — Informs the asset registry that a Verse file has been created on disk
- L909 _public prototype_ `virtual bool VerseDeleted(const FString& FilePathOnDisk) = 0;` — Informs the asset registry that a Verse file has been deleted from disk
- L912 _public prototype_ `virtual void PackageDeleted (UPackage* DeletedPackage) = 0;` — Informs the asset registry that an in-memory package has been deleted, and all associated assets should be removed
- L915 _public prototype_ `virtual void AssetTagsFinalized(const UObject& FinalizedAsset) = 0;` — Informs the asset registry that an Asset has finalized its tags after loading. Ignored if the Asset's package has been modified.
- L917 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetsEvent, TConstArrayView<FAssetData> );`
- L924 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams( FAssetCollisionEvent, FAssetData&, FAssetData&, FAssetData*& );` — EXPERIMENTAL: event for when duplicated assets are found and needs to be resolved, this is experimental as it's a counter measure for a situation that shouldn't happen. Also, DO NOT CALL AssetRegistry functions from delegate subscribers; doing so will create a deadlock.
- L925 _public prototype_ `virtual FAssetCollisionEvent& OnAssetCollision_Private() = 0;`
- L928 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetAddedEvent, const FAssetData& );` — Event for when assets are added to the registry
- L929 _public prototype_ `virtual FAssetAddedEvent& OnAssetAdded() = 0;`
- L932 _public prototype_ `virtual FAssetsEvent& OnAssetsAdded() = 0;` — Event for when assets are added to the registry to handle batches more efficiently
- L935 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetRemovedEvent, const FAssetData& );` — Event for when assets are removed from the registry
- L936 _public prototype_ `virtual FAssetRemovedEvent& OnAssetRemoved() = 0;`
- L939 _public prototype_ `virtual FAssetsEvent& OnAssetsRemoved() = 0;` — Event for when assets are removed from the registry
- L942 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams( FAssetRenamedEvent, const FAssetData&, const FString& );` — Event for when assets are renamed in the registry
- L943 _public prototype_ `virtual FAssetRenamedEvent& OnAssetRenamed() = 0;`
- L946 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetUpdatedEvent, const FAssetData&);` — Event for when assets are updated in the registry
- L947 _public prototype_ `virtual FAssetUpdatedEvent& OnAssetUpdated() = 0;`
- L950 _public prototype_ `virtual FAssetsEvent& OnAssetsUpdated() = 0;` — Event for when assets are updated in the registry
- L953 _public prototype_ `virtual FAssetUpdatedEvent& OnAssetUpdatedOnDisk() = 0;` — Event for when assets are updated on disk and have been refreshed in the assetregistry
- L956 _public prototype_ `virtual FAssetsEvent& OnAssetsUpdatedOnDisk() = 0;` — Event for when assets are updated on disk and have been refreshed in the assetregistry
- L959 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FInMemoryAssetCreatedEvent, UObject* );` — Event for when in-memory assets are created
- L960 _public prototype_ `virtual FInMemoryAssetCreatedEvent& OnInMemoryAssetCreated() = 0;`
- L963 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FInMemoryAssetDeletedEvent, UObject* );` — Event for when assets are deleted
- L964 _public prototype_ `virtual FInMemoryAssetDeletedEvent& OnInMemoryAssetDeleted() = 0;`
- L967 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FVerseAddedEvent, const FName );` — Event for when Verse files are added to the registry
- L968 _public prototype_ `virtual FVerseAddedEvent& OnVerseAdded() = 0;`
- L971 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FVerseRemovedEvent, const FName );` — Event for when Verse files are removed from the registry
- L972 _public prototype_ `virtual FVerseRemovedEvent& OnVerseRemoved() = 0;`
- L975 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE( FFilesLoadedEvent );` — Event for when the asset registry is done loading files
- L976 _public prototype_ `virtual FFilesLoadedEvent& OnFilesLoaded() = 0;`
- L978 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FScanStartedEvent);`
- L979 _public prototype_ `virtual FScanStartedEvent& OnScanStarted() = 0;`
- L981 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FScanEndedEvent);`
- L982 _public prototype_ `virtual FScanEndedEvent& OnScanEnded() = 0;`
- L987 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FKnownGathersCompleteEvent);` — Event for when the asset registry is done with all currently known gathers. This will fire after both the initial asset scan and again after each subsequent batch of additional mount searches
- L988 _public prototype_ `virtual FKnownGathersCompleteEvent& OnKnownGathersComplete() = 0;`
- L1017 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FFileLoadProgressUpdatedEvent, const FFileLoadProgressUpdateData& );` — Event to update the progress of the background file load
- L1018 _public prototype_ `virtual FFileLoadProgressUpdatedEvent& OnFileLoadProgressUpdated() = 0;`
- L1025 _public prototype_ `virtual bool IsLoadingAssets() const = 0;` — `UFUNCTION(BlueprintCallable, Category = "AssetRegistry")` — Returns true if the asset registry is currently loading files and does not yet know about all assets. This is a legacy function that only returns true when the asset registry is performing its initial search for assets. Prefer using IsGathering() to know if the asset registry is currently loading files.
- L1030 _public prototype_ `virtual bool IsGathering() const = 0;` — Returns true if the asset registry is currently loading files and does not yet know about all assets. IsGathering() can be used to indicate if the asset registry is scanning during the initial search as well as any subsequent search the registry may perform (e.g. when a new mount point is added)
- L1035 _public prototype_ `virtual bool HasSerializedDiscoveryCache() const = 0;` — Returns true if the asset registry has written out the discovery cache after discovery has completed. This function will return false if discovery is not yet complete, discovery caching isn't supported by the current platform or cache writing has been disabled such as when using -NoAssetRegistryCacheWrite.
- L1038 _public prototype_ `virtual bool ShouldUpdateDiskCacheAfterLoad() const = 0;` — If true, the AssetRegistry updates its on-disk information for an Asset whenever that Asset loads.
- L1041 _public prototype_ `virtual void Tick (float DeltaTime) = 0;` — Tick the asset registry
- L1044 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;` — Serialize the registry to/from a file, skipping editor only data
- L1045 _public prototype_ `virtual void Serialize(FStructuredArchive::FRecord Record) = 0;`
- L1048 _public prototype_ `virtual void AppendState(const FAssetRegistryState& InState, UE::AssetRegistry::EAppendMode AppendMode = UE::AssetRegistry::EAppendMode::Append) = 0;` — Append the assets from the incoming state into our own
- L1068 _public prototype_ `virtual bool ActiveMountsIsEnabled() = 0;` — Returns true if ActiveMountsIsEnabled in the current configuration. Returns true even if ActiveMountsInitialize has not yet been called. If not enabled, functions with AssetRegistry side effects will such as ActiveMountsRegister* will still execute the side-effects, but all behavior specific to unloading and reloading will be skipped by the ActiveMounts functions.
- L1077 _public prototype_ `virtual void ActiveMountsInitialize() = 0;` — Called once per process to activate ActiveMountsLoading. Calls to ActiveMountsLoadAsync/ActiveMountsUnloadAsync before this call are ignored. This function also forces the parsing of the premade AssetRegistry: MountPoints in the premade AssetRegistry state will be searched at this point in FPackageName or FPlugins; any mountpoints used by the premade that are not mounted and not findable as a plugin should be registered before this via FPackageName::FindOrAddMountPoint. Any mountpoints not findable will log an error and AssetDatas under them will always be loaded.
- L1089 _public prototype_ `virtual bool ActiveMountsRegisterAndLoadFilePathSynchronous(FStringView StateFilePath) = 0;` — Registers an AssetRegistry.bin file on disk for ActiveMountsLoading, and also immediately loads its data into the AssetRegistry with AppendState. The default premade AssetRegistry.bin is automatically registered by the AssetRegistry and does not need this call. If ActiveMountsLoading is disabled, this function behaves the same as AppendState. Returns with no action if AssetRegistryState can not be loaded from the given file. This function also forces the parsing of the premade AssetRegistry, @see ActiveMountsInitialize. @return True if the AssetRegistryState could be loaded from the given file, else false.
- L1096 _public prototype_ `virtual void ActiveMountsRegisterAndLoadFilePathAsync(FStringView StateFilePath, TFunction<void(bool bSucceeded)> OnComplete = TFunction<void(bool bSucceeded)>(), UE::Tasks::ETaskPriority TaskPriority = UE::Tasks::ETaskPriority::Default) = 0;` — Runs ActiveMountsRegisterAndLoadFilePathSynchronous on an async thread and calls OnComplete when done. OnComplete is called from an async thread, and in game error cases might be called after IAssetRegistry is shutdown. Caller should handle thread safety and should check for IAssetRegistry::Get != nullptr if it is used in their callback.
- L1111 _public prototype_ `virtual void ActiveMountsLoadAsync(TConstArrayView<FStringView> MountPointLongPackageNames, TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) = 0;` — Requests that AssetDatas under the given MountPoints (looked up via FPackageName::FindOrAddMountPoint) be reloaded into the AssetRegistry. This only affects MountPoints previously unloaded via auto unload or ActiveMountsUnloadAsync, and is only possible for AssetDatas in the premade AssetRegistry or in an AssetRegistry file registered via an ActiveMountsRegister function. Calls OnComplete once the load completes. @param OnComplete Optional delegate: void OnComplete(bool bCanceled). Called when the load is complete. bCanceled is set to true iff ActiveMountsLoading is not enabled or for any requested MountPoint the load failed or was overridden by an unload request. If true, test ActiveMountsIsEnabled and call ActiveMountsIsLoaded to test state of each mountpoint. OnComplete is called from an async thread, caller should handle thread safety in their callback.
- L1122 _public prototype_ `virtual void ActiveMountsReloadAllAsync( TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) = 0;` — Requests that all AssetDatas that have been unloaded by ActiveMounts be reloaded. Calls OnComplete once the load completes. @param OnComplete Optional delegate: void OnComplete(bool bCanceled). Called when the load is complete. bCanceled is set to true iff ActiveMountsLoading is not enabled or for any MountPoint the load failed or was overridden by an unload request. OnComplete is called from an async thread, caller should handle thread safety in their callback.
- L1135 _public prototype_ `virtual void ActiveMountsUnloadAsync(TConstArrayView<FStringView> MountPointLongPackageNames, TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) = 0;` — Requests that AssetDatas under the given MountPoints (looked up via FPackageName::FindOrAddMountPoint) be unloaded from the AssetRegistry. This is only possible for AssetDatas in the premade AssetRegistry or in an AssetRegistry file registered via an ActiveMountsRegister function. Calls OnComplete once the unload completes. @param OnComplete Optional delegate: void OnComplete(bool bCanceled). Called when the unload is complete. bCanceled is set to true iff ActiveMountsLoading is not enabled or for any requested MountPoint the unload failed or was overridden by a load request. If true, test ActiveMountsIsEnabled and call ActiveMountsIsLoaded to test state of each mountpoint. OnComplete is called from an async thread, caller should handle thread safety in their callback.
- L1147 _public prototype_ `virtual void ActiveMountsUnloadAllUnmountedAsync( TFunction<void(bool bCanceled)> OnComplete = TFunction<void(bool bCanceled)>()) = 0;` — Requests that AssetDatas under MountPoints that are available for unloading via the premade AssetRegistry or in an AssetRegistry registered via an ActiveMountsRegister function be unloaded if they are not currently mounted with FPackageName. Calls OnComplete once the unload completes. @param OnComplete Optional delegate: void OnComplete(bool bCanceled). Called when the unload is complete. bCanceled is set to true iff ActiveMountsLoading is not enabled or for any MountPoint the unload failed or was overridden by a load request. OnComplete is called from an async thread, caller should handle thread safety in their callback.
- L1155 _public prototype_ `virtual bool ActiveMountsIsLoaded(FStringView MountPointLongPackageName) = 0;` — Returns whether the given MountPoint (looked up via FPackageName::FindOrAddMountPoint) is loaded in the ActiveMounts system. Returns false if currently loading or unloading or if unloaded. Only valid if ActiveMountsLoader is enabled and the MountPoint is used by the PreMade AssetRegistry or a registered AssetRegistry file. Returns false for all other cases.
- L1160 _public prototype_ `virtual bool ActiveMountsIsInProgress() = 0;` — Returns whether ActiveMountsLoading is in progress for any MountPoint. Returns false if ActiveMountsLoading is not enabled.
- L1170 _public prototype_ `virtual void ActiveMountsReportWhenIdle(TFunction<void()> OnIdle) = 0;` — Call the given callback when all requested ActiveMountsLoading loads and unloads complete and the system becomes idle. The callback is called outside of the lock, so by the time it is called, a new request may have come in and the system might be in progress again. Intended use of this function is to guard entry into a state that relies on AssetRegistry queries after issuing a set of ActiveMounts loads or unloads. If the system is already idle (ActiveMountsIsInProgress returns false), the callback is called immediately. If ActiveMountsLoading is not enabled, the callback is called immediately. The callback might be called from an async thread; caller should handle thread safety in their callback.
- L1173 _public prototype_ `virtual SIZE_T GetAllocatedSize(bool bLogDetailed = false) const = 0;` — Returns memory size of entire registry, optionally logging sizes
- L1184 _public prototype_ `virtual void InitializeTemporaryAssetRegistryState(FAssetRegistryState& OutState, const FAssetRegistrySerializationOptions& Options, bool bRefreshExisting = false, const TSet<FName>& RequiredPackages = TSet<FName>(), const TSet<FName>& RemovePackages = TSet<FName>()) const = 0;` — Fills in a AssetRegistryState with a copy of the data in the internal cache, overriding some @param OutState			This will be filled in with a copy of the asset data, platform data, and dependency data @param Options			Serialization options that will be used to write this later @param bRefreshExisting	If true, will not delete or add packages in OutState and will just update things that already exist @param RequiredPackages  If non-empty, only packages in this set will be kept. @param RemovePackages	If non-empty, packages in this set will not be kept.
- L1200 _public prototype_ `virtual void DumpState(const TArray<FString>& Arguments, TArray<FString>& OutPages, int32 LinesPerPage = 1) const = 0;` — Writes out the state in textual form. Use arguments to control which segments to emit. @param Arguments List of segments to emit. Possible values: 'ObjectPath', 'PackageName', 'Path', 'Class', 'Tag', 'Dependencies' and 'PackageData' @param OutPages Textual representation will be written to this array; each entry will have LinesPerPage lines of the full dump. @param LinesPerPage - how many lines should be combined into each string element of OutPages, for e.g. breaking up the dump into separate files. To facilitate diffing between similar-but-different registries, the actual number of lines per page will be slightly less than LinesPerPage; we introduce partially deterministic pagebreaks near the end of each page.
- L1204 _public prototype_ `virtual TSet<FName> GetCachedEmptyPackagesCopy() const = 0;` — Returns the set of empty package names fast iteration
- L1207 _public prototype_ `virtual bool ContainsTag(FName TagName) const = 0;` — Return whether the given TagName occurs in the tags of any asset in the AssetRegistry
- L1211 _public prototype_ `virtual void InitializeSerializationOptions(FAssetRegistrySerializationOptions& Options, const FString& PlatformIniName, UE::AssetRegistry::ESerializationTarget Target) const;` — `UE_DEPRECATED(5.7, "Use version taking ITargetPlatform parameter instead")` — Fills in FAssetRegistrySerializationOptions from ini, optionally using a target platform ini name
- L1216 _public prototype_ `virtual void InitializeSerializationOptions(FAssetRegistrySerializationOptions& Options, const ITargetPlatform* TargetPlatform = nullptr, UE::AssetRegistry::ESerializationTarget Target = UE::AssetRegistry::ESerializationTarget::ForGame) const = 0;` — Fills in FAssetRegistrySerializationOptions from ini, optionally using a target platform
- L1231 _public prototype_ `virtual void LoadPackageRegistryData(FArchive& Ar, FLoadPackageRegistryData& InOutData) const = 0;` — Load FPackageRegistry data from the supplied package
- L1234 _public prototype_ `virtual void LoadPackageRegistryData(const FString& PackageFilename, FLoadPackageRegistryData& InOutData) const = 0;` — Load FAssetData from the specified package filename
- L1236 _public typedef_ `typedef TFunctionRef<bool(const FAssetData* AssetData)> FAssetDataFunc;`
- L1237 _public typedef_ `typedef TFunctionRef<bool(FAssetDataFunc AssetCallback)> FEnumerateAssetDatasFunc;`
- L1244 _public prototype_ `virtual void ReadLockEnumerateAllTagToAssetDatas(TFunctionRef<bool(FName TagName, FEnumerateAssetDatasFunc EnumerateAssets)> Callback) const = 0;` — Enumerate all pairs in State->TagToAssetDataMapAssetRegistry and call a callback on each pair. To avoid copies, the callback is called from within the ReadLock. DO NOT CALL AssetRegistry functions from the callback; doing so will create a deadlock.
- L1259 _public typedef_ `ShouldSetManagerPredicate;`
- L1266 _public prototype_ `virtual bool IsPathBeautificationNeeded(const FString& InAssetPath) const = 0;` — Indicates if path should be beautified before presented to the user. @param InAssetPath	Path of the asset to check @return True if the path should be beautified
- L1283 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FEnumerateAssetsEvent, const FARCompiledFilter& , UE::AssetRegistry::EEnumerateAssetsFlags ) virtual FEnumerateAssetsEvent& OnEnumerateAssetsEvent() = 0;` — Event triggered when a query of the AssetRegistry's on-disk assets is made. The event is triggered only if the filter is valid. The event is not triggered for queries of in-memory assets only, such as GetInMemoryAssets.
- L1312 _protected function_ `virtual void SuspendPathsMounting()` — Implementation methods for FSuspendPathsMounting and FSuspendPathsDismounting
- L1313 _protected function_ `virtual void ResumePathsMounting()`
- L1314 _protected function_ `virtual void SuspendPathsDismounting()`
- L1315 _protected function_ `virtual void ResumePathsDismounting()`
- L1318 _protected function_ `virtual void RequestPauseBackgroundProcessing()` — Implementation methods for FPauseBackgroundProcessingScope
- L1319 _protected function_ `virtual void RequestResumeBackgroundProcessing()`
- L1325 _protected prototype_ `virtual void SetManageReferences(const TMultiMap<FAssetIdentifier, FAssetIdentifier>& ManagerMap, bool bClearExisting, UE::AssetRegistry::EDependencyCategory RecurseType, TSet<FDependsNode*>& ExistingManagedNodes, ShouldSetManagerPredicate ShouldSetManager = nullptr) = 0;` — `UE_DEPRECATED(5.6, "Use version that takes FSetManageReferencesContext.")`
- L1335 _protected prototype_ `virtual void SetManageReferences(UE::AssetRegistry::FSetManageReferencesContext& Context) = 0;` — Specifies a list of manager mappings, optionally recursing to dependencies. These mappings can then be queried later to see which assets "manage" other assets. This function is only meant to be called by the AssetManager, calls from anywhere else will conflict and lose data. @see UE::AssetRegistry::FSetManageReferencesContext for arguments.
- L1341 _protected prototype_ `virtual bool SetPrimaryAssetIdForObjectPath(const FSoftObjectPath& ObjectPath, FPrimaryAssetId PrimaryAssetId) = 0;` — Sets the PrimaryAssetId for a specific asset. This should only be called by the AssetManager, and is needed when the AssetManager is more up to date than the on disk Registry.
- L1350 _protected prototype_ `virtual void CopyManageDependenciesToState(FAssetRegistryState& InOutState) const = 0;` — Copy all manage dependencies in the global AssetRegistry that target any assets that exist in InOutState into the manage dependencies of InOutState.

#### struct `IAssetRegistry::FFileLoadProgressUpdateData`  
`struct FFileLoadProgressUpdateData`  
_L991-1014_
- desc: Payload data for a file progress update
- L993 _public function_ `FFileLoadProgressUpdateData(int32 InNumTotalAssets, int32 InNumAssetsProcessedByAssetRegistry, int32 InNumAssetsPendingDataLoad, bool InIsDiscoveringAssetFiles) : NumTotalAssets(InNumTotalAssets) , NumAssetsProcessedByAssetRegistry(InNumAssetsProcessedByAssetRegistry) , NumAssetsPendingDataLoad(InNumAssetsPendingDataLoad) , bIsDiscoveringAssetFiles(InIsDiscoveringAssetFiles)`
- L1002 _public function_ `bool operator==(const FFileLoadProgressUpdateData& Other) const`
- L1010 _public member_ `int32 NumTotalAssets;`
- L1011 _public member_ `int32 NumAssetsProcessedByAssetRegistry;`
- L1012 _public member_ `int32 NumAssetsPendingDataLoad;`
- L1013 _public member_ `bool bIsDiscoveringAssetFiles;`

#### struct `IAssetRegistry::FLoadPackageRegistryData`  
`struct FLoadPackageRegistryData`  
_L1220-1228_
- L1222 _public prototype_ `FLoadPackageRegistryData(bool bInGetDependencies = false);`
- L1223 _public prototype_ `~FLoadPackageRegistryData();`
- L1225 _public member_ `TArray<FAssetData> Data;`
- L1226 _public member_ `TArray<FName> DataDependencies;`
- L1227 _public member_ `bool bGetDependencies;`

#### struct `IAssetRegistry::FPauseBackgroundProcessingScope`  
`struct FPauseBackgroundProcessingScope`  
_L1272-1276_
- desc: Request to pause background processing of scan results while this object is in scope This can be used to allow a priority thread to perform along sequence of operations without having to contend with the background thread for data access
- L1274 _public function_ `FPauseBackgroundProcessingScope()`
- L1275 _public function_ `~FPauseBackgroundProcessingScope()`

#### struct `IAssetRegistry::FSuspendPathsMounting`  
`struct FSuspendPathsMounting`  
_L1292-1296_
- desc: Request to pause paths mounting. Can be used by the calling code to temporarily pause loading of data inside the AssetRegistry in response to mounted MountPoints (e.g. ActiveMountsLoading). All mounting requests will be executed in one batch at the end of that scope.
- L1294 _public function_ `UE_NODISCARD_CTOR FSuspendPathsMounting()`
- L1295 _public function_ `~FSuspendPathsMounting()`

#### struct `IAssetRegistry::FSuspendPathsDismounting`  
`struct FSuspendPathsDismounting`  
_L1303-1307_
- desc: Request to pause paths dismounting. Can be used by the calling code to temporarily pause clearing of data inside the AssetRegistry. All unmounting requests will be executed in one batch at the end of that scope.
- L1305 _public function_ `UE_NODISCARD_CTOR FSuspendPathsDismounting()`
- L1306 _public function_ `~FSuspendPathsDismounting()`

#### enum `UE::AssetRegistry::EReadPackageDataMainErrorCode`  
`enum EReadPackageDataMainErrorCode`  
_L1356-1362_
- L1358 _public enumerator_ `Unknown = 0`
- L1359 _public enumerator_ `InvalidObjectCount = 1`
- L1360 _public enumerator_ `InvalidTagCount = 2`
- L1361 _public enumerator_ `InvalidTag = 3`

#### struct `UE::AssetRegistry::FDeserializePackageData`  
`struct FDeserializePackageData`  
_L1364-1371_
- L1366 _public member_ `int64 DependencyDataOffset = INDEX_NONE;`
- L1367 _public member_ `int32 ObjectCount = 0;`
- L1369 _public prototype_ `bool DoSerialize(FArchive& BinaryArchive, const FPackageFileSummary& PackageFileSummary, EReadPackageDataMainErrorCode& OutError);`

#### struct `UE::AssetRegistry::FDeserializeObjectPackageData`  
`struct FDeserializeObjectPackageData`  
_L1373-1380_
- L1375 _public member_ `FString ObjectPath;`
- L1376 _public member_ `FString ObjectClassName;`
- L1377 _public member_ `int32 TagCount = 0;`
- L1379 _public prototype_ `bool DoSerialize(FArchive& BinaryArchive, EReadPackageDataMainErrorCode& OutError);`

#### struct `UE::AssetRegistry::FDeserializeTagData`  
`struct FDeserializeTagData`  
_L1382-1388_
- L1384 _public member_ `FString Key;`
- L1385 _public member_ `FString Value;`
- L1387 _public prototype_ `bool DoSerialize(FArchive& BinaryArchive, EReadPackageDataMainErrorCode& OutError);`

#### struct `UE::AssetRegistry::FReadPackageDataDependenciesArgs`  
`struct FReadPackageDataDependenciesArgs`  
_L1398-1412_
- L1401 _public member_ `FArchive* BinaryNameAwareArchive = nullptr;` — Required inputs, must be initialized and non-null
- L1402 _public member_ `int64 AssetRegistryDependencyDataOffset = -1;`
- L1403 _public member_ `int32 NumImports = -1;`
- L1404 _public member_ `int32 NumSoftPackageReferences = -1;`
- L1405 _public member_ `FPackageFileVersion PackageVersion;`
- L1408 _public member_ `TBitArray<> ImportUsedInGame;` — Outputs
- L1409 _public member_ `TBitArray<> SoftPackageUsedInGame;`
- L1410 _public member_ `TArray<TPair<FName, EExtraDependencyFlags>> ExtraPackageDependencies;`
- L1411 _public member_ `int64 AssetRegistryDependencyDataSize = 0;`

#### enum `UE::AssetRegistry::EGetMostImportantAssetFlags`  
`enum class EGetMostImportantAssetFlags`  
_L1423-1434_
- L1425 _public enumerator_ `None = 0`
- L1428 _public enumerator_ `RequireOneTopLevelAsset = 0x1` — Returns nullptr if there are multiple top level assets.
- L1433 _public enumerator_ `IgnoreSkipClasses = 0x2` — Don't skip AR filtered classes (i.e. BP and BPGC). This is cruicial if you are running in environments where the skip classes can't be initialized (i.e. Programs) as you could get different results in such cases.

#### Free symbols / members of external scopes

- L19 _macro_ `#define ASSET_REGISTRY_STATE_DUMPING_ENABLED !(UE_BUILD_SHIPPING || UE_BUILD_TEST)`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L39 _namespace_ `namespace EAssetAvailability`
- L50 _namespace_ `namespace EAssetAvailabilityProgressReportingType`
- L59 _namespace_ `namespace UE`
- L59 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L71 _prototype_ `ENUM_CLASS_FLAGS(EScanFlags);` (scope `UE::AssetRegistry`)
- L73 _prototype_ `FString LexToString(EScanFlags Flags);` (scope `UE::AssetRegistry`)
- L81 _prototype_ `ENUM_CLASS_FLAGS(EAssetSetManagerAssetFlags);` (scope `UE::AssetRegistry`)
- L213 _function_ `friend inline uint32 GetTypeHash(const FAssetDependency& InHash)`
- L225 _function_ `friend FCbWriter& operator<<(FCbWriter& Writer, const FAssetDependency& Dependency)`
- L861 _delegate_ `DECLARE_EVENT_OneParam( IAssetRegistry, FFilesBlockedEvent, const TArray<FString>& );` — Event for when one or more files have been blocked from the registry
- L869 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FPathsEvent, TConstArrayView<FStringView> );` — Events for when paths (folders/directories) are added to and removed from the asset registry. Both batch and singular events will be called for the same set of paths in all cases. Prefer the batched versions as the singular versions will be deprecated in a future release.
- L870 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FPathAddedEvent, const FString& );`
- L871 _delegate_ `DECLARE_EVENT_OneParam( IAssetRegistry, FPathRemovedEvent, const FString& );`
- L917 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetsEvent, TConstArrayView<FAssetData> );`
- L924 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams( FAssetCollisionEvent, FAssetData&, FAssetData&, FAssetData*& );` — EXPERIMENTAL: event for when duplicated assets are found and needs to be resolved, this is experimental as it's a counter measure for a situation that shouldn't happen. Also, DO NOT CALL AssetRegistry functions from delegate subscribers; doing so will create a deadlock.
- L928 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetAddedEvent, const FAssetData& );` — Event for when assets are added to the registry
- L935 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetRemovedEvent, const FAssetData& );` — Event for when assets are removed from the registry
- L942 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams( FAssetRenamedEvent, const FAssetData&, const FString& );` — Event for when assets are renamed in the registry
- L946 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FAssetUpdatedEvent, const FAssetData&);` — Event for when assets are updated in the registry
- L959 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FInMemoryAssetCreatedEvent, UObject* );` — Event for when in-memory assets are created
- L963 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FInMemoryAssetDeletedEvent, UObject* );` — Event for when assets are deleted
- L967 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FVerseAddedEvent, const FName );` — Event for when Verse files are added to the registry
- L971 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FVerseRemovedEvent, const FName );` — Event for when Verse files are removed from the registry
- L975 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE( FFilesLoadedEvent );` — Event for when the asset registry is done loading files
- L978 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FScanStartedEvent);`
- L981 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FScanEndedEvent);`
- L987 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FKnownGathersCompleteEvent);` — Event for when the asset registry is done with all currently known gathers. This will fire after both the initial asset scan and again after each subsequent batch of additional mount searches
- L1017 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam( FFileLoadProgressUpdatedEvent, const FFileLoadProgressUpdateData& );` — Event to update the progress of the background file load
- L1283 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FEnumerateAssetsEvent, const FARCompiledFilter& , UE::AssetRegistry::EEnumerateAssetsFlags ) virtual FEnumerateAssetsEvent& OnEnumerateAssetsEvent() = 0;` — Event triggered when a query of the AssetRegistry's on-disk assets is made. The event is triggered only if the filter is valid. The event is not triggered for queries of in-memory assets only, such as GetInMemoryAssets.
- L1354 _namespace_ `namespace UE`
- L1354 _namespace_ `namespace AssetRegistry` (scope `UE`)
- L1394 _prototype_ `bool ReadPackageDataMain(FArchive& BinaryArchive, const FString& PackageName, const FPackageFileSummary& PackageFileSummary, int64& OutDependencyDataOffset, TArray<FAssetData*>& OutAssetDataList, EReadPackageDataMainErrorCode& OutError, const TArray<FObjectImport>* InImports = nullptr, const TArray<FObjectExport>* InExports = nullptr);` (scope `UE::AssetRegistry`) — Functions to read and write the data used by the AssetRegistry in each package; the format of this data is separate from the format of the data in the asset registry. WritePackageData is declared in AssetRegistryInterface.h, in the CoreUObject module, because it is needed by SavePackage in CoreUObject
- L1413 _prototype_ `bool ReadPackageDataDependencies(FReadPackageDataDependenciesArgs& Args);` (scope `UE::AssetRegistry`)
- L1420 _prototype_ `void GetAssetForPackages(TConstArrayView<FName> PackageNames, TMap<FName, FAssetData>& OutPackageToAssetData);` (scope `UE::AssetRegistry`) — Given a list of packages, gather the most important assets for each package. If multiple assets are in a package, the most important asset will be added. If a package does not exist or does not have any assets, no entry will be added for that package name.
- L1452 _prototype_ `const FAssetData* GetMostImportantAsset(TConstArrayView<const FAssetData*> PackageAssetDatas, EGetMostImportantAssetFlags InFlags = EGetMostImportantAssetFlags::None);` (scope `UE::AssetRegistry`) — Given a list of asset datas for a specific package, find an asset considered "most important" or "representative". This is distinct from a Primary asset, and is used for user facing representation of a package or other cases where you need to relate information about a package to an asset. Usually there is only 1 asset per package so this is straightforward, however in the multiple asset case it: Tries to find the "UAsset" via the FAssetData::IsUAsset() function. (i.e. asset name matches package name) If none exist, tries to find a "Top Level Asset" using FAssetData::IsToplevelAsset(). (i.e. outer == package) If only one exists, use that. Otherwise, if EGetMostImportantAssetFlags::RequireOneTopLevelAsset isn't set, gather the set of possibles and return the first sorted on asset class then name. If no top level assets, all package assets If multiple top level assets, all top level assets A good source for PackageAssetDatas is FAssetRegistryState::GetAssetsByPackageName.
- L1458 _prototype_ `bool ShouldSearchAllAssetsAtStart();` (scope `UE::AssetRegistry`) — Returns true if the asset registry should start searching all assets on startup
- L1461 _externvar_ `extern const FName WildcardFName;` (scope `UE::AssetRegistry`) — Wildcards (*) used when looking up assets in the asset registry
- L1462 _externvar_ `extern const FTopLevelAssetPath WildcardPathName;` (scope `UE::AssetRegistry`)
- L1482 _externvar_ `extern const FName Stage_ChunkCountFName;` (scope `UE::AssetRegistry`) — Various FNames for asset tags that get added during staging if asset registry writeback is enabled. Note that these sizes refer to the package as a whole, and some packages have more than one asset per package. In that case, the data is stored on the asset returned by GetMostImportantAsset with IgnoreSkipClasses. NOTE some platforms do not compress in UnrealPak. For those platforms, all compressed sizes are actually uncompressed! Stage_ChunkCountFName				Total iostore chunks in the package. Stage_ChunkSizeFName				The total uncompressed size of the chunks in the package. Stage_ChunkCompressedSizeFName	The total compressed size of the chunks in the package. SEE NOTE ABOVE! Stage_ChunkInstalledSizeFName		The compressed size of all chunks that must be installed with the game/plugin. Stage_ChunkStreamingSizeFName		The compressed size of all chunks that are delivered using IAS. Stage_ChunkOptionalSizeFName		The compressed size of all chunks that are placed in an optional container. See CookMetadata.h - UE::Cook::EPluginSizeTypes for more information on size types.
- L1483 _externvar_ `extern const FName Stage_ChunkSizeFName;` (scope `UE::AssetRegistry`)
- L1484 _externvar_ `extern const FName Stage_ChunkCompressedSizeFName;` (scope `UE::AssetRegistry`)
- L1485 _externvar_ `extern const FName Stage_ChunkInstalledSizeFName;` (scope `UE::AssetRegistry`)
- L1486 _externvar_ `extern const FName Stage_ChunkStreamingSizeFName;` (scope `UE::AssetRegistry`)
- L1487 _externvar_ `extern const FName Stage_ChunkOptionalSizeFName;` (scope `UE::AssetRegistry`)
- L1491 _prototype_ `const TCHAR* GetDevelopmentAssetRegistryFilename();` — Returns the filename without filepath for the DevelopmentAssetRegistry written by the cooker.

### `Source/Runtime/AssetRegistry/Public/AssetRegistry/PathTree.h` (Public)


#### class `FPathTree`  
`class FPathTree`  
_L12-71_
- L15 _public prototype_ `FPathTree();`
- L19 _public prototype_ `void EnsureAdditionalCapacity(int32 NumNewPaths);` — Reserve extra space for the expected number of paths that will be added in future. Count is added to the current number of stored paths and not any previous reservation.
- L22 _public prototype_ `bool CachePath(FName Path, TFunctionRef<void(FName)> OnPathAdded);` — Adds the specified path to the tree, creating nodes as needed and calling OnPathAdded for any new paths added. Returns true if the specified path was actually added (as opposed to already existed)
- L25 _public prototype_ `bool RemovePath(FName Path, TFunctionRef<void(FName)> OnPathRemoved);` — Removes the specified path from the tree, calling OnPathRemoved for any existing paths removed. Returns true if the path was found and removed.
- L28 _public prototype_ `bool PathExists(FName Path) const;` — Checks whether the given path is one that we know about
- L31 _public prototype_ `bool GetAllPaths(TSet<FName>& OutPaths) const;` — Get all of the paths we know about
- L34 _public prototype_ `void EnumerateAllPaths(TFunctionRef<bool(FName)> Callback) const;` — Enumerate all of the paths we know about
- L37 _public prototype_ `bool GetSubPaths(FName BasePath, TSet<FName>& OutPaths, bool bRecurse = true) const;` — Recursively gathers all child paths from the specified base path relative to this node
- L40 _public prototype_ `bool EnumerateSubPaths(FName BasePath, TFunctionRef<bool(FName)> Callback, bool bRecurse = true) const;` — Recursively enumerates all child paths from the specified base path relative to this node
- L43 _public prototype_ `void Shrink();` — Shrinks the internal structures reducing the memory they use.
- L45 _public function_ `int32 NumPaths() const`
- L50 _public function_ `SIZE_T GetAllocatedSize(void) const`
- L63 _public prototype_ `static FName NormalizePackagePath(FName In);` — Normalize the given PackagePath (/Game/SubDir) by removing a trailing slash if it exists.
- L67 _private member_ `TMap<FName, TSet<FName>> ParentPathToChildPaths;` — A one-to-many mapping between a parent path and its child paths.
- L70 _private member_ `TMap<FName, FName> ChildPathToParentPath;` — A one-to-one mapping between a child path and its parent path. Paths without a parent (root paths) will not appear in this map.
