# Developer / IoStoreOnDemandUtilities

- module root: `Source/Developer/IoStore/OnDemandUtilities`
- headers: 5; symbols: 205
- symbol kinds: class=4, function=17, macro=1, member=83, namespace=28, prototype=44, struct=18, typedef=10
- PrivateDependencyModuleNames: CoreUObject, IoStoreHttpClient, IoStoreOnDemand, IoStoreOnDemandCore, Json, RSA, S3Client
- PublicDependencyModuleNames: Core, TraceLog

### `Source/Developer/IoStore/OnDemandUtilities/Private/Command.h` (Private)


#### struct `UE::IoStore::Tool::FArgument`  
`struct FArgument`  
_L15-22_
- L17 _public member_ `static const uint32 ValueAlign = 16;`
- L18 _public member_ `static const uint32 ValueSize = 16;`
- L19 _public member_ `FStringView Name;`
- L20 _public member_ `FStringView Desc;`
- L21 _public member_ `PTRINT Inner;`

#### struct `UE::IoStore::Tool::FArgumentSet`  
`struct FArgumentSet`  
_L27-32_
- L29 _public prototype_ `FArgumentSet(std::initializer_list<FArgument>);`
- L30 _public prototype_ `operator FArgument () const;`
- L31 _public member_ `FArguments Arguments;`

#### class `UE::IoStore::Tool::FContext`  
`class FContext`  
_L59-81_
- L62 _public prototype_ `template <CArgTypes Type> Type Get(FStringView Name) const;`
- L64 _public prototype_ `template <CArgTypes Type> Type Get(FStringView Name) const;`
- L73 _private prototype_ `FContext(const FArguments& InArguments, int32 ArgC, const TCHAR* const* ArgV);`
- L74 _private prototype_ `void SetArguments(const FArguments& Input);`
- L75 _private prototype_ `uint32 FindArgument(FStringView Name) const;`
- L76 _private prototype_ `[[noreturn]] void OnMissingValue(FStringView Name) const;`
- L77 _private function_ `bool IsSet(uint32 Index) const`
- L78 _private member_ `FArguments Arguments;`
- L79 _private member_ `TArray<FValue> Values;`
- L80 _private member_ `uint64 SetMask = 0;`
- L85 _function_ `template <CArgTypes Type> Type FContext::Get(FStringView Name) const`
- L103 _function_ `template <CArgTypes Type> Type FContext::Get(FStringView Name, Type Default) const`

#### struct `UE::IoStore::Tool::FContext::FValue`  
`struct alignas(FArgument::ValueAlign) FValue`  
_L67-70_
- L69 _public member_ `uint8 Buffer[FArgument::ValueSize] = {};`

#### class `UE::IoStore::Tool::FCommand`  
`class FCommand`  
_L112-133_
- L115 _public typedef_ `using EntryFunc = int32 (const FContext&);`
- L116 _public prototype_ `FCommand(EntryFunc* InEntry, FStringView InName, FStringView InDesc, FArguments&& InArguments);`
- L117 _public prototype_ `static int32 Main(int32 ArgC, const TCHAR* const* ArgV);`
- L121 _private prototype_ `FCommand() = default;`
- L122 _private prototype_ `void Initialize(EntryFunc* InEntry, FStringView InName, FStringView InDesc, FArguments&& InArguments);`
- L123 _private prototype_ `FContext GetContext(int32 ArgC, const TCHAR* const* ArgV) const;`
- L124 _private prototype_ `static FCommand*& Head();`
- L125 _private prototype_ `static int32 MainInner(int32 ArgC, const TCHAR* const* ArgV);`
- L126 _private prototype_ `void Usage() const;`
- L127 _private prototype_ `int32 Call(int32 ArgC, const TCHAR* const* ArgV);`
- L128 _private member_ `FCommand* Next = FCommand::Head();`
- L129 _private member_ `FStringView Name;`
- L130 _private member_ `FStringView Desc;`
- L131 _private member_ `FArguments Arguments;`
- L132 _private member_ `EntryFunc* Entry;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IoStore` (scope `UE`)
- L12 _namespace_ `namespace Tool` (scope `UE::IoStore`)
- L24 _typedef_ `using FArguments = TArray<FArgument>;` (scope `UE::IoStore::Tool`)
- L44 _prototype_ `template <CArgTypes Type> FArgument TArgument(FStringView Name, FStringView Desc);` (scope `UE::IoStore::Tool`)
- L46 _macro_ `#define TARGUMENT_DECL(t) \`

### `Source/Developer/IoStore/OnDemandUtilities/Private/Common.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace Tool` (scope `UE::IoStore`)
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace IoStore` (scope `UE`)
- L8 _namespace_ `namespace Tool` (scope `UE::IoStore`)
- L8 _namespace_ `namespace Common` (scope `UE::IoStore::Tool`)
- L12 _prototype_ `FKeyChain LoadCryptoKeys(const FContext& Context);` (scope `UE::IoStore::Tool::Common`)

### `Source/Developer/IoStore/OnDemandUtilities/Private/Graph.h` (Private)


#### class `UE::IoStore::Tool::FPackageGraph`  
`class FPackageGraph`  
_L20-133_
- L26 _public function_ `friend uint32 GetTypeHash(FIndex Node)`
- L33 _public typedef_ `using FNode = FIndex;`
- L34 _public typedef_ `using FEdge = FIndex;`
- L35 _public typedef_ `using FContainerNode = FIndex;`
- L36 _public typedef_ `using FMissingEdge = FIndex;`
- L79 _public function_ `friend uint32 GetTypeHash(const FRedirect &Redirect)`
- L92 _public prototype_ `void Reserve(int32 ContainerCount, int32 PackageCount);`
- L93 _public prototype_ `FContainerNode AddContainerNode(FString&& Name, const FIoContainerId& Id);`
- L94 _public function_ `const FContainerData& GetContainerData(FContainerNode Node) const`
- L95 _public prototype_ `FNode AddNode(FContainerNode ContainerNode, const FPackageId& PackageId, const FString* Filename, uint64 ChunkSize);`
- L96 _public function_ `FNode GetNode(const FPackageId& PackageId) const`
- L97 _public function_ `const FNodeData& GetNodeData(FNode Node) const`
- L98 _public function_ `int32 GetNodeCount() const`
- L99 _public prototype_ `void AddEdge(FNode From, FNode To, bool bSoft);`
- L100 _public function_ `const FEdgeData& GetEdgeData(FEdge Edge) const`
- L101 _public function_ `int32 GetEdgeCount() const`
- L102 _public prototype_ `void AddMissingEdge(FNode From, const FPackageId To, bool bSoft);`
- L103 _public prototype_ `void AddRedirect(const FPackageId& From, const FPackageId& To);`
- L104 _public prototype_ `void AddShaderMapHashes(FNode Node, TConstArrayView<FShaderHash> Hashes);`
- L105 _public prototype_ `TConstArrayView<FShaderHash> GetShaderMapHashes(const FNodeData& Data);`
- L106 _public prototype_ `void GetNodesForShaderMapHash(const FShaderHash& Hash, TArray<FNode>& Out);`
- L108 _public prototype_ `void Traverse(FNode Node, bool bIncoming, bool bSkipSoftRefs, FVisitor& Visitor);`
- L113 _public prototype_ `static void Build( TConstArrayView<FString> ContainerFilenames, const FKeyChain& KeyChain, bool bSkipSoftRefs, bool bShaderMaps, bool bIncludeOnDemand, FPackageGraph& Graph);`
- L120 _public prototype_ `static FIoStatus Save(const FPackageGraph& Graph, const FString& Filename);`
- L123 _private typedef_ `using FShaderHashMap = TMultiMap<FShaderHash, FNode>;`
- L125 _private member_ `TArray<FNodeData> NodeData;`
- L126 _private member_ `TArray<FEdgeData> EdgeData;`
- L127 _private member_ `TArray<FMissingEdgeData> MissingEdgeData;`
- L128 _private member_ `TArray<FShaderHash> ShaderMapHashes;`
- L129 _private member_ `TArray<FContainerData> ContainerNodeData;`
- L130 _private member_ `TSet<FRedirect> Redirects;`
- L131 _private member_ `TMap<FPackageId, FNode> PackageIdToNode;` — Transient
- L132 _private member_ `FShaderHashMap ShaderHashToNode;` — Transient

#### struct `UE::IoStore::Tool::FPackageGraph::FIndex`  
`struct FIndex`  
_L23-31_
- L25 _public function_ `bool IsValid() const`
- L27 _public function_ `explicit operator bool() const`
- L28 _public function_ `bool operator==(FIndex Other) const`
- L30 _public member_ `int32 Index = INDEX_NONE;`

#### struct `UE::IoStore::Tool::FPackageGraph::FConnections`  
`struct FConnections`  
_L38-42_
- L40 _public member_ `TSet<FEdge> In;`
- L41 _public member_ `TSet<FEdge> Out;`

#### struct `UE::IoStore::Tool::FPackageGraph::FNodeData`  
`struct FNodeData`  
_L44-53_
- L46 _public member_ `FConnections Connections;`
- L47 _public member_ `FString Filename;`
- L48 _public member_ `FPackageId PackageId;`
- L49 _public member_ `uint64 Size;`
- L50 _public member_ `FContainerNode ContainerNode;`
- L51 _public member_ `int32 ShaderMapOffset = INDEX_NONE;`
- L52 _public member_ `int32 ShaderMapCount = 0;`

#### struct `UE::IoStore::Tool::FPackageGraph::FEdgeData`  
`struct FEdgeData`  
_L55-60_
- L57 _public member_ `FNode From;`
- L58 _public member_ `FNode To;`
- L59 _public member_ `bool bSoft = false;`

#### struct `UE::IoStore::Tool::FPackageGraph::FMissingEdgeData`  
`struct FMissingEdgeData`  
_L62-67_
- L64 _public member_ `FNode From;`
- L65 _public member_ `FPackageId To;`
- L66 _public member_ `bool bSoft = false;`

#### struct `UE::IoStore::Tool::FPackageGraph::FContainerData`  
`struct FContainerData`  
_L69-75_
- L71 _public member_ `FConnections Connections;`
- L72 _public member_ `TSet<FNode> PackageNodes;` — Transient
- L73 _public member_ `FString Name;`
- L74 _public member_ `FIoContainerId Id;`

#### struct `UE::IoStore::Tool::FPackageGraph::FRedirect`  
`struct FRedirect`  
_L77-85_
- L80 _public function_ `bool operator==(const FRedirect &Other) const`
- L81 _public function_ `bool operator<(const FRedirect &Other) const`
- L83 _public member_ `FPackageId From;`
- L84 _public member_ `FPackageId To;`

#### struct `UE::IoStore::Tool::FPackageGraph::FVisitor`  
`struct FVisitor`  
_L87-90_
- L89 _public prototype_ `virtual bool Visit(const FPackageGraph& Graph, FNode Node, const FNodeData& Data) = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace IoStore` (scope `UE`)
- L16 _namespace_ `namespace Tool` (scope `UE::IoStore`)
- L136 _prototype_ `FIoStatus LoadFromCompactBinary(const FString& Filename, FPackageGraph& OutGraph);` (scope `UE::IoStore::Tool`)

### `Source/Developer/IoStore/OnDemandUtilities/Private/Upload.h` (Private)


#### struct `UE::IoStore::Tool::Upload::FUploadSettings`  
`struct FUploadSettings`  
_L30-38_
- L32 _public member_ `static constexpr int32 MaxConcurrentUploads = 16;`
- L33 _public member_ `static constexpr int32 MinTocListCount = 1000;`
- L34 _public member_ `static constexpr int32 MaxTocListCount = 10000;`
- L35 _public member_ `static constexpr int32 MaxTocDownloadCount = 1000;`
- L36 _public member_ `static constexpr int32 DefaultPartitionSize = 2 << 20;`
- L37 _public member_ `static constexpr int32 MaxPartitionSize = 32 << 20;`

#### struct `UE::IoStore::Tool::Upload::FCountSize`  
`struct FCountSize`  
_L41-45_
- L43 _public member_ `uint64 Count = 0;`
- L44 _public member_ `uint64 Size = 0;`

#### struct `UE::IoStore::Tool::Upload::FContainerStats`  
`struct FContainerStats`  
_L58-63_
- L60 _public member_ `FCountSize Chunks;`
- L61 _public member_ `FCountSize Partitions;`
- L62 _public member_ `FCountSize UploadedPartitions;`

#### struct `UE::IoStore::Tool::Upload::FPartitionInfo`  
`struct FPartitionInfo`  
_L66-70_
- L68 _public member_ `FIoHash Hash = FIoHash::Zero;`
- L69 _public member_ `uint64 Size = 0;`

#### struct `UE::IoStore::Tool::Upload::FContainerData`  
`struct FContainerData`  
_L73-85_
- L75 _public member_ `FIoHash UTocHash = FIoHash::Zero;`
- L76 _public member_ `FString FilePath;`
- L77 _public member_ `FString Name;`
- L78 _public member_ `TUniquePtr<FIoStoreReader> Reader;`
- L79 _public member_ `FIoBuffer Header;`
- L80 _public member_ `FIoBuffer UToc;`
- L81 _public member_ `TArray<FIoStoreTocChunkInfo> ChunkInfos;`
- L82 _public member_ `TMap<FString, TArray<uint32>> TagSets;`
- L83 _public member_ `TArray<FPartitionInfo> UploadedPartitions;`
- L84 _public member_ `FContainerStats Stats;`

#### struct `UE::IoStore::Tool::Upload::FChunkValidationSettings`  
`struct FChunkValidationSettings`  
_L91-95_
- L93 _public member_ `bool bValidate = false;`
- L94 _public member_ `uint64 MaxRawChunkSize = 32 << 20;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace IoStore` (scope `UE`)
- L19 _namespace_ `namespace Serialization` (scope `UE::IoStore`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace IoStore` (scope `UE`)
- L20 _namespace_ `namespace Serialization` (scope `UE::IoStore`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace IoStore` (scope `UE`)
- L22 _namespace_ `namespace Tool` (scope `UE::IoStore`)
- L22 _namespace_ `namespace Upload` (scope `UE::IoStore::Tool`)
- L26 _typedef_ `using FTagSets = TMap<FString, TArray<FString>>;` (scope `UE::IoStore::Tool::Upload`)
- L27 _typedef_ `using FEncryptionKeys = TMap<FGuid, FAES::FAESKey>;` (scope `UE::IoStore::Tool::Upload`)
- L48 _function_ `inline FCountSize operator+(const FCountSize& Lhs, const FCountSize& Rhs)` (scope `UE::IoStore::Tool::Upload`)
- L88 _typedef_ `using FUploadChunkCallback = TFunction<FIoStatus(FIoBuffer, const FIoHash&)>;` (scope `UE::IoStore::Tool::Upload`)
- L98 _prototype_ `FIoStatus LoadContainers( TConstArrayView<FString> FilePaths, const FEncryptionKeys& EncryptionKeys, TPagedArray<FContainerData>& OutContainers, bool bIgnoreContainerFlags = false);` (scope `UE::IoStore::Tool::Upload`)
- L105 _prototype_ `FIoStatus LoadTagSets( const FString& FilePath, FTagSets& Out);` (scope `UE::IoStore::Tool::Upload`)
- L110 _prototype_ `FIoStatus CreateTagSets( const FTagSets& TagSets, FContainerData& Container);` (scope `UE::IoStore::Tool::Upload`)
- L115 _prototype_ `void GenerateTestChunks( FS3Client& Client, const FString& Bucket, const FString& BucketRelativePath, uint8 MaxExp = 16);` (scope `UE::IoStore::Tool::Upload`)
- L122 _prototype_ `FIoStatus DownloadPartitionChunkHashes( FS3Client& Client, const FString& Bucket, const FString& BucketRelativePath, int32 MaxTocListCount, int32 MaxTocDownloadCount, TSet<FIoHash>& Out);` (scope `UE::IoStore::Tool::Upload`)
- L131 _prototype_ `FIoStatus UploadPartitionChunkHashes( FS3Client& Client, const FString& Bucket, const FString& BucketRelativePath, const FString& TargetPlatform, const FString& BuildVersion, TConstArrayView<FPartitionInfo> Partitions);` (scope `UE::IoStore::Tool::Upload`)
- L140 _prototype_ `FIoStatus UploadContainer( FContainerData& Container, const FEncryptionKeys& EncryptionKeys, int32 MaxPartitionSize, UE::IoStore::Serialization::EOnDemandContainerEntryFlags ContainerFlags, const TSet<FIoHash>& ExistingChunks, FUploadChunkCallback&& Upload, UE::IoStore::Serialization::FOnDemandTocWriter& OutWriter, const FChunkValidationSettings& ValidationSettings = FChunkValidationSettings());` (scope `UE::IoStore::Tool::Upload`)

### `Source/Developer/IoStore/OnDemandUtilities/Private/UploadQueue.h` (Private)


#### class `UE::IoStore::Tool::FUploadQueue`  
`class FUploadQueue`  
_L24-51_
- desc: s3 upload helper....
- L27 _public prototype_ `FUploadQueue(UE::FS3Client& Client, const FString& Bucket, int32 ThreadCount);`
- L28 _public prototype_ `bool Enqueue(FStringView Key, FIoBuffer Payload);`
- L29 _public prototype_ `bool Flush();`
- L32 _private prototype_ `void ThreadEntry();`
- L40 _private member_ `UE::FS3Client& Client;`
- L41 _private member_ `TArray<TFuture<void>> Threads;`
- L42 _private member_ `FString Bucket;`
- L43 _private member_ `FCriticalSection CriticalSection;`
- L44 _private member_ `TQueue<FQueueEntry> Queue;`
- L45 _private member_ `FEventRef WakeUpEvent;`
- L46 _private member_ `FEventRef UploadCompleteEvent;`
- L47 _private member_ `std::atomic_int32_t ConcurrentUploads{ 0 };`
- L48 _private member_ `std::atomic_int32_t ActiveThreadCount{ 0 };`
- L49 _private member_ `std::atomic_int32_t ErrorCount{ 0 };`
- L50 _private member_ `std::atomic_bool bCompleteAdding{ false };`

#### struct `UE::IoStore::Tool::FUploadQueue::FQueueEntry`  
`struct FQueueEntry`  
_L34-38_
- L36 _public member_ `FString Key;`
- L37 _public member_ `FIoBuffer Payload;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace IoStore` (scope `UE`)
- L19 _namespace_ `namespace Tool` (scope `UE::IoStore`)
