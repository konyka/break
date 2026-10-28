# Developer / ZenOplogUtils

- module root: `Source/Developer/ZenOplogUtils`
- headers: 4; symbols: 102
- symbol kinds: enum=3, enumerator=10, macro=4, member=45, namespace=4, prototype=23, struct=12, typedef=1
- PrivateDependencyModuleNames: Core, Json, Zen
- PrivateIncludePathModuleNames: DesktopPlatform

### `Source/Developer/ZenOplogUtils/Public/Experimental/DiffCompactBinary.h` (Public)


#### struct `UE::FCbEntryDifference`  
`struct FCbEntryDifference`  
_L20-25_
- desc: This represents a single value difference in compact binary data Differences are reported with hierarchical names, so they can be found/reconstructed from the compact binary For example, compact binary containing an object named packagedata with differing filename values will return a PropertyName of 'packagedata/filename' Arrays of different sizes are reported as a single diff entry with the name of the array Arrays of equal size with different elements will have each element diff reported separately, with the index appended to the array property name e.g. 'packagestoreentry/importedpackages/2' or 'files/1/serverpath'
- L22 _public member_ `FUtf8String PropertyName;`
- L23 _public member_ `FCbFieldView OldValue;`
- L24 _public member_ `FCbFieldView NewValue;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ZENOPLOGUTILS_API`
- L11 _namespace_ `namespace UE`
- L29 _prototype_ `TArray<FCbEntryDifference> DiffCompactBinary(const FCbFieldView& cb1, const FCbFieldView& cb2);` (scope `UE`) — Recursively diff the contents of a compact binary field/object Important! Arrays are assumed to be sorted!

### `Source/Developer/ZenOplogUtils/Public/Experimental/ZenOplogDiff.h` (Public)


#### struct `UE::FOplogDiffResults`  
`struct FOplogDiffResults`  
_L24-34_
- desc: Represents the full diff of an oplog/manifest Takes shared ownership of the compact binary in a manifest
- L26 _public member_ `TArray<FUtf8String> OpsMissingInManifest1;`
- L27 _public member_ `TArray<FUtf8String> OpsMissingInManifest2;`
- L28 _public member_ `TArray<FUtf8String> IdenticalOps;`
- L29 _public member_ `TArray<FOplogDiffChangedOp> ChangedOpsWithSameOutput;` — Op has differences, but the output data is the same
- L30 _public member_ `TArray<FOplogDiffChangedOp> ChangedOpsWithOutputDifferences;` — Op has cooked output differences
- L32 _public member_ `FCbField Manifest1Data;`
- L33 _public member_ `FCbField Manifest2Data;`

#### enum `UE::EOutputManifestDiffOptions`  
`enum class EOutputManifestDiffOptions : int32`  
_L49-54_
- L51 _public enumerator_ `None = 0`
- L52 _public enumerator_ `OutputDifferences = 1` — Output the values of any different properties
- L53 _public enumerator_ `OutputIdenticalOps = 2` — Output the list of identical ops

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ZENOPLOGUTILS_API`
- L14 _namespace_ `namespace UE`
- L20 _typedef_ `using FOplogDiffChangedOp = TPair<FUtf8String, TArray<FCbEntryDifference>>;` (scope `UE`) — Represents a changed Op and the properties with different values
- L37 _prototype_ `FOplogDiffResults DiffManifests(const FOplogManifest& Manifest1, const FOplogManifest& Manifest2);` (scope `UE`) — Diff all ops, reports all changes in each op. Results are unsorted
- L40 _prototype_ `void SortDiffResults(FOplogDiffResults& FullResults);` (scope `UE`) — Sorts the results of the diff
- L45 _prototype_ `bool OpDiffContainsArrayValueChange(const FOplogDiffChangedOp& Op, FUtf8StringView ArrayName, FUtf8StringView PropertyName);` (scope `UE`) — Returns true if any diff entry describes an array modification (array sizes different), or if an entry in that array contains a change of a specific property i.e. if changed property name == 'ArrayName' or 'ArrayName/.../PropertyName'
- L55 _prototype_ `ENUM_CLASS_FLAGS(EOutputManifestDiffOptions);` (scope `UE`)
- L58 _prototype_ `void OutputManifestDiffResultsToJson(TSharedRef<TJsonWriter<>>& Writer, const FOplogDiffResults& Results, EOutputManifestDiffOptions Flags );` (scope `UE`) — Flags = a combination of EOutputManifestDiffOptions
- L61 _prototype_ `void OutputManifestDiffResultsToCompactBinary(FCbWriter& Writer, const FOplogDiffResults& Results, EOutputManifestDiffOptions Flags);` (scope `UE`) — Flags = a combination of EOutputManifestDiffOptions

### `Source/Developer/ZenOplogUtils/Public/Experimental/ZenOplogManifest.h` (Public)


#### struct `UE::FOplogManifest`  
`struct FOplogManifest`  
_L17-84_
- desc: A manifest is a chunk of compact binary representing the cooked output of a build.
- L78 _public prototype_ `bool RebuildCachedData();` — Caches op keys + hashes, and populates OpKeyToIndex. Call after loading. Returns false on unexpected data
- L80 _public member_ `FCbField AllOpsCbData;`
- L81 _public member_ `TArray<FOp> Ops;`
- L82 _public member_ `TArray<TPair<FUtf8String, uint32>> OpKeysAndHashes;`
- L83 _public member_ `TMap<FUtf8String, int32> OpKeyToIndex;` — Op key -> index into Ops array

#### struct `UE::FOplogManifest::FOp`  
`struct FOp`  
_L20-75_
- desc: Caches a view of an op in the compact binary and provides accessors to known values
- L22 _public prototype_ `FUtf8String GetKey() const;`
- L23 _public prototype_ `FIoHash GetArtifactHash() const;`
- L24 _public prototype_ `FIoHash CookImportExport() const;`
- L25 _public prototype_ `FIoHash GetLogs() const;`
- L34 _public prototype_ `FPackageStoreEntry GetPackageStoreEntry() const;`
- L44 _public prototype_ `TArray<FPackageData> GetPackageDatas() const;`
- L55 _public prototype_ `TArray<FBulkData> GetBulkDatas() const;`
- L64 _public prototype_ `TArray<FFile> GetFiles() const;`
- L72 _public prototype_ `TArray<FMeta> GetMetas() const;`
- L74 _public member_ `FCbFieldView CbData;` — Cache a field view to the op data in the manifest compact binary

#### struct `UE::FOplogManifest::FOp::FPackageStoreEntry`  
`struct FPackageStoreEntry`  
_L27-33_
- L29 _public member_ `uint32 Flags = 0;`
- L30 _public member_ `FUtf8String PackageName;`
- L31 _public member_ `TArray<uint64> ImportedPackages;`
- L32 _public member_ `TArray<uint64> SoftPackageReferences;`

#### struct `UE::FOplogManifest::FOp::FPackageData`  
`struct FPackageData`  
_L36-43_
- L38 _public member_ `FCbObjectId ID;`
- L39 _public member_ `int64 Size = 0;`
- L40 _public member_ `int64 RawSize = 0;`
- L41 _public member_ `FIoHash DataHash;`
- L42 _public member_ `FUtf8String Filename;`

#### struct `UE::FOplogManifest::FOp::FBulkData`  
`struct FBulkData`  
_L46-54_
- L48 _public member_ `FCbObjectId ID;`
- L49 _public member_ `FUtf8String TypeStr;`
- L50 _public member_ `int64 Size = 0;`
- L51 _public member_ `int64 RawSize = 0;`
- L52 _public member_ `FIoHash DataHash;`
- L53 _public member_ `FUtf8String Filename;`

#### struct `UE::FOplogManifest::FOp::FFile`  
`struct FFile`  
_L57-63_
- L59 _public member_ `FCbObjectId ID;`
- L60 _public member_ `FUtf8String ServerPath;`
- L61 _public member_ `FUtf8String ClientPath;`
- L62 _public member_ `FIoHash DataHash;`

#### struct `UE::FOplogManifest::FOp::FMeta`  
`struct FMeta`  
_L66-71_
- L68 _public member_ `FCbObjectId ID;`
- L69 _public member_ `FUtf8String Name;`
- L70 _public member_ `FIoHash DataHash;`

#### struct `UE::FLoadOplogManifestResult`  
`struct FLoadOplogManifestResult`  
_L86-100_
- L96 _public prototype_ `FLoadOplogManifestResult(EStatus Status, TOptional<FOplogManifest>&& Manifest = {});`
- L98 _public member_ `EStatus Result;`
- L99 _public member_ `TOptional<FOplogManifest> Manifest;`

#### enum `UE::FLoadOplogManifestResult::EStatus`  
`enum class EStatus`  
_L88-95_
- L90 _public enumerator_ `Ok`
- L91 _public enumerator_ `ErrorFileNotFound`
- L92 _public enumerator_ `ErrorUnsupportedFormat`
- L93 _public enumerator_ `ErrorMalformedCompactBinary`
- L94 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ZENOPLOGUTILS_API`
- L13 _namespace_ `namespace UE`
- L102 _prototype_ `FLoadOplogManifestResult LoadOplogManifestFromCompactBinary(const FCbObject& CompactBinary);` (scope `UE`)
- L103 _prototype_ `FLoadOplogManifestResult LoadOplogManifestFromFile(FString Path);` (scope `UE`)

### `Source/Developer/ZenOplogUtils/Public/Experimental/ZenOplogSnapshots.h` (Public)


#### struct `UE::FZenSnapshotDescriptor`  
`struct FZenSnapshotDescriptor`  
_L15-21_
- desc: Contains the data required to get a oplog/snapshot from the cloud servers Can be parsed from exported zen snapshot json, or found from the build service
- L17 _public member_ `FString CloudHost;`
- L18 _public member_ `FString Namespace;`
- L19 _public member_ `FString Bucket;`
- L20 _public member_ `FString BuildID;`

#### struct `UE::FDownloadOplogManifestResult`  
`struct FDownloadOplogManifestResult`  
_L35-44_
- L42 _public member_ `EStatus Result;`
- L43 _public member_ `FString DownloadedFilename;` — Path to the local manifest file after a successful download

#### enum `UE::FDownloadOplogManifestResult::EStatus`  
`enum class EStatus`  
_L37-41_
- L39 _public enumerator_ `Ok`
- L40 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ZENOPLOGUTILS_API`
- L11 _namespace_ `namespace UE`
- L24 _prototype_ `TArray<FZenSnapshotDescriptor> ParseSnapshotDescriptorFromJson(FStringView PathToJson);` (scope `UE`) — Attempt to parse an exported zen snapshot json from horde
- L30 _prototype_ `TFuture<TOptional<FZenSnapshotDescriptor>> FindSnapshotDescriptorForBuild(FStringView ProjectName, FStringView StreamName, FStringView PlatformName, FStringView CommitID, bool bLogAllBuilds = false);` (scope `UE`) — Try to find a snapshot descriptor matching a build from the zen build service Returns an empty TOptional if the build was not found, or any errors occur Note this relies on callbacks being fired on the game thread - do not do a blocking wait/get! bLogAllBuilds - logs all namespaces, buckets, and CLs found
- L47 _prototype_ `FDownloadOplogManifestResult DownloadOplogManifest(const FZenSnapshotDescriptor& Descriptor, FString OutputDirectory = {}, bool bDownloadAsJson = false);` (scope `UE`) — Download an oplog manifest to a local file.
