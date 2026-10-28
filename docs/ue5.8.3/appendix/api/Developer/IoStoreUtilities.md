# Developer / IoStoreUtilities

- module root: `Source/Developer/IoStoreUtilities`
- headers: 17; symbols: 879
- symbol kinds: class=18, delegate=6, enum=7, enumerator=35, function=46, macro=4, member=438, namespace=24, prototype=245, struct=52, typedef=4
- PrivateDependencyModuleNames: AssetRegistry, CookMetadata, Core, CoreUObject, DerivedDataCache, DevHttp, DeveloperToolSettings, Json, PakFile, Projects, RSA, RenderCore, SandboxFile, Sockets, StudioTelemetry, Zen
- PrivateIncludePathModuleNames: StorageServerClient, TargetPlatform
- PublicIncludePathModuleNames: CoreUObject, Zen

### `Source/Developer/IoStoreUtilities/Internal/CookedPackageStore.h` (Internal)


#### class `FCookedPackageStore`  
`class FCookedPackageStore`  
_L20-61_
- L33 _public prototype_ `FCookedPackageStore(FStringView InCookedDir);`
- L35 _public prototype_ `FIoStatus LoadManifest(const TCHAR* ManifestFilename);`
- L36 _public prototype_ `FIoStatus LoadProjectStore(const TCHAR* ProjectStoreFilename);`
- L38 _public prototype_ `FIoChunkId GetChunkIdFromFileName(const FString& Filename) const;`
- L39 _public prototype_ `const FChunkInfo* GetChunkInfoFromChunkId(const FIoChunkId& ChunkId) const;`
- L40 _public prototype_ `const FChunkInfo* GetChunkInfoFromFileName(const FString& Filename) const;`
- L41 _public prototype_ `FString GetRelativeFilenameFromChunkId(const FIoChunkId& ChunkId) const;`
- L42 _public prototype_ `FName GetPackageNameFromChunkId(const FIoChunkId& ChunkId) const;`
- L43 _public prototype_ `FName GetPackageNameFromFileName(const FString& Filename) const;`
- L44 _public prototype_ `const FPackageStoreEntryResource* GetPackageStoreEntry(FPackageId PackageId) const;`
- L46 _public prototype_ `bool HasZenStoreClient() const;`
- L47 _public prototype_ `UE::FZenStoreHttpClient* GetZenStoreClient();`
- L49 _public prototype_ `TIoStatusOr<FIoBuffer> ReadChunk(const FIoChunkId& ChunkId);`
- L50 _public prototype_ `UE::Tasks::FTask ReadChunkAsync(const FIoChunkId& ChunkId, TFunction<void(TIoStatusOr<FIoBuffer>)>&& Callback);`
- L53 _private prototype_ `void ParseOplog(FCbObject& OplogObject);`
- L54 _private prototype_ `FIoStatus LoadChunkHashes();`
- L56 _private member_ `TUniquePtr<UE::FZenStoreHttpClient> ZenStoreClient;`
- L57 _private member_ `FString CookedDir;`
- L58 _private member_ `TMap<FPackageId, FPackageStoreEntryResource> PackageIdToEntry;`
- L59 _private member_ `TMap<FString, FIoChunkId> FilenameToChunkIdMap;`
- L60 _private member_ `TMap<FIoChunkId, FChunkInfo> ChunkInfoMap;`

#### struct `FCookedPackageStore::FChunkInfo`  
`struct FChunkInfo`  
_L23-31_
- L25 _public member_ `FIoChunkId ChunkId;`
- L26 _public member_ `FIoHash ChunkHash;`
- L27 _public member_ `uint64 ChunkSize = 0;`
- L28 _public member_ `FName PackageName;`
- L29 _public member_ `FString RelativeFileName;`
- L30 _public member_ `TArray<FFileRegion> FileRegions;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`

### `Source/Developer/IoStoreUtilities/Internal/PackageStoreOptimizer.h` (Internal)


#### class `FPackageStoreNameMapBuilder`  
`class FPackageStoreNameMapBuilder`  
_L16-84_
- L19 _public function_ `void SetNameMapType(FMappedName::EType InNameMapType)`
- L24 _public function_ `void AddName(FName Name)`
- L29 _public function_ `void AddName(FDisplayNameEntryId DisplayId)`
- L36 _public function_ `void MarkNamesAsReferenced(const TArray<FName>& Names, TArray<int32>& OutNameIndices)`
- L52 _public function_ `void MarkNameAsReferenced(FName Name)`
- L63 _public function_ `FMappedName MapName(FName Name) const`
- L69 _public function_ `TConstArrayView<FDisplayNameEntryId> GetNameMap() const`
- L74 _public function_ `void Empty()`
- L81 _private member_ `TMap<FDisplayNameEntryId, int32> NameIndices;`
- L82 _private member_ `TArray<FDisplayNameEntryId> NameMap;`
- L83 _private member_ `FMappedName::EType NameMapType = FMappedName::EType::Package;`

#### class `FPackageStorePackage`  
`class FPackageStorePackage`  
_L86-222_
- L89 _public function_ `FPackageId GetId() const`
- L94 _public function_ `uint64 GetHeaderSize() const`
- L99 _public function_ `uint64 GetNameCount() const`
- L104 _public function_ `const bool HasEditorData() const`
- L109 _public function_ `const TArray<FBulkDataMapEntry>& GetBulkDataEntries() const`
- L198 _private member_ `FPackageId Id;`
- L199 _private member_ `FName Name;`
- L201 _private member_ `TOptional<FZenPackageVersioningInfo> VersioningInfo;`
- L203 _private member_ `FPackageStoreNameMapBuilder NameMapBuilder;`
- L204 _private member_ `TArray<FPackageObjectIndex> Imports;`
- L205 _private member_ `TArray<FExport> Exports;`
- L206 _private member_ `TArray<FPackageObjectIndex> CellImports;`
- L207 _private member_ `TArray<FCellExport> CellExports;`
- L208 _private member_ `TArray<FExportGraphNode> ExportGraphNodes;`
- L209 _private member_ `FGraphData GraphData;`
- L211 _private member_ `TArray<FImportedPackageRef> ImportedPackages;`
- L212 _private member_ `TArray<uint64> ImportedPublicExportHashes;`
- L213 _private member_ `TArray<FBulkDataMapEntry> BulkDataEntries;`
- L214 _private member_ `TArray<FName> SoftPackageReferences;`
- L216 _private member_ `FIoBuffer HeaderBuffer;`
- L218 _private member_ `uint32 PackageFlags = 0;`
- L219 _private member_ `uint32 CookedHeaderSize = 0;`

#### struct `FPackageStorePackage::FExportGraphNode`  
`struct FExportGraphNode`  
_L115-121_
- L117 _public member_ `FExportBundleEntry BundleEntry;`
- L118 _public member_ `TArray<FExportGraphNode*> InternalDependencies;`
- L119 _public member_ `int32 IncomingEdgeCount = 0;`
- L120 _public member_ `bool bIsPublic = false;`

#### struct `FPackageStorePackage::FExport`  
`struct FExport`  
_L123-138_
- L125 _public member_ `FName ObjectName;`
- L126 _public member_ `uint64 PublicExportHash = 0;`
- L127 _public member_ `FPackageObjectIndex OuterIndex;`
- L128 _public member_ `FPackageObjectIndex ClassIndex;`
- L129 _public member_ `FPackageObjectIndex SuperIndex;`
- L130 _public member_ `FPackageObjectIndex TemplateIndex;`
- L131 _public member_ `EObjectFlags ObjectFlags = RF_NoFlags;`
- L132 _public member_ `uint64 SerialOffset = uint64(-1);`
- L133 _public member_ `uint64 SerialSize = uint64(-1);`
- L134 _public member_ `bool bNotForClient = false;`
- L135 _public member_ `bool bNotForServer = false;`
- L136 _public member_ `bool bIsPublic = false;`
- L137 _public member_ `FExportGraphNode* Nodes[FExportBundleEntry::ExportCommandType_Count] = { nullptr };`

#### struct `FPackageStorePackage::FCellExport`  
`struct FCellExport`  
_L139-147_
- L141 _public member_ `uint64 PublicExportHash = 0;`
- L142 _public member_ `FName CppClassInfo;`
- L143 _public member_ `uint64 SerialOffset = uint64(-1);`
- L144 _public member_ `uint64 SerialLayoutSize = uint64(-1);`
- L145 _public member_ `uint64 SerialSize = uint64(-1);`
- L146 _public member_ `FExportGraphNode* Nodes[FExportBundleEntry::ExportCommandType_Count] = { nullptr };`

#### struct `FPackageStorePackage::FUnresolvedExport`  
`struct FUnresolvedExport`  
_L149-153_
- L151 _public member_ `FString FullName;`
- L152 _public member_ `FString FullPath;`

#### struct `FPackageStorePackage::FUnresolvedImport`  
`struct FUnresolvedImport`  
_L155-164_
- L157 _public member_ `FString FullName;`
- L158 _public member_ `FString FullPath;`
- L159 _public member_ `FName FromPackageName;`
- L160 _public member_ `int32 FromPackageNameLen = 0;`
- L161 _public member_ `bool bIsScriptImport = false;`
- L162 _public member_ `bool bIsVerseVNIImport = false;`
- L163 _public member_ `bool bIsImportOfPackage = false;`

#### struct `FPackageStorePackage::FGraphData`  
`struct FGraphData`  
_L166-171_
- L168 _public member_ `TArray<FExportBundleEntry> ExportBundleEntries;`
- L169 _public member_ `TArray<FDependencyBundleHeader> DependencyBundleHeaders;`
- L170 _public member_ `TArray<FDependencyBundleEntry> DependencyBundleEntries;`

#### struct `FPackageStorePackage::FExportBundleGraphNode`  
`struct FExportBundleGraphNode`  
_L173-179_
- L175 _public member_ `FPackageStorePackage* Package = nullptr;`
- L176 _public member_ `TArray<FExportGraphNode*> ExportGraphNodes;`
- L177 _public member_ `int32 Index = -1;`
- L178 _public member_ `int32 IncomingEdgeCount = 0;`

#### struct `FPackageStorePackage::FImportedPackageRef`  
`struct FImportedPackageRef`  
_L181-196_
- L183 _public function_ `FImportedPackageRef(FName InName) : Id(FPackageId::FromName(InName)) , Name(InName)`
- L189 _public function_ `bool operator<(const FImportedPackageRef& Other) const`
- L194 _public member_ `const FPackageId Id;`
- L195 _public member_ `const FName Name;`

#### class `FPackageStoreOptimizer`  
`class FPackageStoreOptimizer`  
_L224-299_
- L241 _public function_ `uint64 GetTotalScriptObjectCount() const`
- L246 _public prototype_ `void Initialize();`
- L247 _public prototype_ `void Initialize(const FIoBuffer& ScriptObjectsBuffer);`
- L249 _public prototype_ `FPackageStorePackage* CreateMissingPackage(const FName& Name) const;`
- L250 _public prototype_ `FPackageStorePackage* CreatePackageFromCookedHeader(const FName& Name, const FIoBuffer& CookedHeaderBuffer) const;`
- L251 _public prototype_ `FIoBuffer CreatePackageBuffer(const FPackageStorePackage* Package, const FIoBuffer& CookedExportsBuffer) const;`
- L252 _public prototype_ `FPackageStoreEntryResource CreatePackageStoreEntry(const FPackageStorePackage* Package, const FPackageStorePackage* OptionalSegmentPackage) const;`
- L253 _public prototype_ `FIoBuffer CreateScriptObjectsBuffer() const;`
- L254 _public prototype_ `void LoadScriptObjectsBuffer(const FIoBuffer& ScriptObjectsBuffer);`
- L256 _public prototype_ `static void FindScriptObjects(TMap<FPackageObjectIndex, FScriptObjectData>& OutScriptObjectsMap);`
- L257 _public prototype_ `static void AppendPathForPublicExportHash(UObject* Object, FStringBuilderBase& OutPath);`
- L258 _public prototype_ `static bool TryGetPublicExportHash(FStringView PackageRelativeExportPath, uint64& OutPublicExportHash);`
- L275 _private typedef_ `using FExportGraphEdges = TMultiMap<FPackageStorePackage::FExportGraphNode*, FPackageStorePackage::FExportGraphNode*>;`
- L277 _private prototype_ `static uint64 GetPublicExportHash(FStringView PackageRelativeExportPath);`
- L279 _private prototype_ `static uint64 GetCellExportHash(Verse::VUniqueString* VersePath);`
- L281 _private prototype_ `static uint64 GetCellExportHash(FUtf8StringView VersePath);`
- L282 _private prototype_ `FCookedHeaderData LoadCookedHeader(const FIoBuffer& CookedHeaderBuffer) const;`
- L283 _private prototype_ `void ResolveImport(FPackageStorePackage::FUnresolvedImport* Imports, FPackageStorePackage::FUnresolvedExport* Exports, const FObjectImport* ObjectImports, const FObjectExport* ObjectExports, const FName& PackageName, int32 LocalImportIndex) const;`
- L284 _private prototype_ `void ProcessImports(const FCookedHeaderData& CookedHeaderData, FPackageStorePackage* Package, TArray<FPackageStorePackage::FUnresolvedImport>& UnresolvedImports, TArray<FPackageStorePackage::FUnresolvedExport>& UnresolvedExports) const;`
- L285 _private prototype_ `void ResolveExport(FPackageStorePackage::FUnresolvedImport* Imports, FPackageStorePackage::FUnresolvedExport* Exports, const FObjectImport* ObjectImports, const FObjectExport* ObjectExports, const FName& PackageName, int32 LocalExportIndex) const;`
- L286 _private prototype_ `void ProcessExports(const FCookedHeaderData& CookedHeaderData, FPackageStorePackage* Package, TArray<FPackageStorePackage::FUnresolvedImport>& UnresolvedImports, TArray<FPackageStorePackage::FUnresolvedExport>& UnresolvedExports) const;`
- L287 _private prototype_ `void ProcessPreloadDependencies(const FCookedHeaderData& CookedHeaderData, FPackageStorePackage* Package) const;`
- L288 _private prototype_ `void ProcessDataResources(const FCookedHeaderData& CookedHeaderData, FPackageStorePackage* Package) const;`
- L289 _private prototype_ `TArray<FPackageStorePackage::FExportGraphNode*> SortExportGraphNodesInLoadOrder(FPackageStorePackage* Package, FExportGraphEdges& Edges) const;`
- L290 _private prototype_ `void CreateExportBundle(FPackageStorePackage* Package) const;`
- L291 _private prototype_ `void FinalizePackageHeader(FPackageStorePackage* Package) const;`
- L292 _private prototype_ `static void FindScriptObjectsRecursive(TMap<FPackageObjectIndex, FScriptObjectData>& OutScriptObjectsMap, FPackageObjectIndex OuterIndex, bool bOuterIsVerseVNI, UObject* Object);`
- L294 _private prototype_ `void FindScriptObjects();`
- L296 _private member_ `TMap<FPackageObjectIndex, FScriptObjectData> ScriptObjectsMap;`
- L297 _private member_ `TMap<FPackageObjectIndex, FScriptCellData> ScriptCellsMap;`
- L298 _private member_ `uint64 TotalScriptObjectCount = 0;`

#### struct `FPackageStoreOptimizer::FScriptObjectData`  
`struct FScriptObjectData`  
_L227-234_
- L229 _public member_ `FName ObjectName;`
- L230 _public member_ `FString FullName;`
- L231 _public member_ `FPackageObjectIndex GlobalIndex;`
- L232 _public member_ `FPackageObjectIndex OuterIndex;`
- L233 _public member_ `FPackageObjectIndex CDOClassIndex;`

#### struct `FPackageStoreOptimizer::FScriptCellData`  
`struct FScriptCellData`  
_L235-239_
- L237 _public member_ `FUtf8String VersePath;`
- L238 _public member_ `FPackageObjectIndex GlobalIndex;`

#### struct `FPackageStoreOptimizer::FCookedHeaderData`  
`struct FCookedHeaderData`  
_L262-273_
- L264 _public member_ `FPackageFileSummary Summary;`
- L265 _public member_ `TArray<FName> SummaryNames;`
- L266 _public member_ `TArray<FObjectImport> ObjectImports;`
- L267 _public member_ `TArray<FObjectExport> ObjectExports;`
- L268 _public member_ `TArray<FCellImport> CellImports;`
- L269 _public member_ `TArray<FCellExport> CellExports;`
- L270 _public member_ `TArray<FPackageIndex> PreloadDependencies;`
- L271 _public member_ `TArray<FObjectDataResource> DataResources;`
- L272 _public member_ `TArray<FName> SoftPackageReferences;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`

### `Source/Developer/IoStoreUtilities/Internal/ZenStoreHttpClient.h` (Internal)


#### class `UE::FZenStoreHttpClient`  
`class FZenStoreHttpClient`  
_L39-136_
- desc: HTTP protocol implementation of Zen Store client interface
- L42 _public prototype_ `FZenStoreHttpClient();`
- L43 _public prototype_ `FZenStoreHttpClient(FStringView HostName, uint16 Port);`
- L44 _public prototype_ `FZenStoreHttpClient(UE::Zen::FServiceSettings&& InSettings);`
- L45 _public prototype_ `~FZenStoreHttpClient();`
- L47 _public prototype_ `bool TryCreateProject(FStringView InProjectId, FStringView InParentProjectId, FStringView InOplogId, FStringView ServerRoot, FStringView EngineRoot, FStringView ProjectRoot, FStringView ProjectFilePath);`
- L50 _public prototype_ `bool TryCreateOplog(FStringView InProjectId, FStringView InOplogId, FStringView InOplogLifetimeMarkerPath);`
- L51 _public prototype_ `bool TryDeleteOplog(FStringView InProjectId, FStringView InOplogId);`
- L53 _public prototype_ `void InitializeReadOnly(FStringView InProjectId, FStringView InOplogId);`
- L55 _public prototype_ `bool IsConnected() const;`
- L57 _public prototype_ `void StartBuildPass();`
- L58 _public prototype_ `TIoStatusOr<uint64> EndBuildPass(FCbPackage OpEntry);`
- L60 _public prototype_ `TIoStatusOr<uint64> AppendOp(FCbPackage OpEntry);`
- L62 _public prototype_ `TIoStatusOr<uint64> GetChunkSize(const FIoChunkId& Id);`
- L63 _public prototype_ `TIoStatusOr<FIoBuffer> ReadChunk(const FIoChunkId& Id, uint64 Offset = 0, uint64 Size = ~0ull);`
- L64 _public prototype_ `TIoStatusOr<FIoBuffer> ReadChunk(const FIoHash& RawHash, uint64 Offset = 0, uint64 Size = ~0ull);`
- L66 _public prototype_ `UE_INTERNAL void ReadChunks(TConstArrayView<FIoChunkId> Ids, TUniqueFunction<void(const FIoChunkId& Id, TIoStatusOr<FIoBuffer> Result)>&& ChunkCallback);` — TODO: Expand API to add partial chunk requests and ModTag field
- L67 _public prototype_ `UE_INTERNAL void ReadChunks(TConstArrayView<FIoHash> RawHashes, TUniqueFunction<void(const FIoHash& RawHash, TIoStatusOr<FIoBuffer> Result)>&& ChunkCallback);`
- L68 _public prototype_ `UE_INTERNAL void ReadChunksAsync(TConstArrayView<FIoChunkId> Ids, TUniqueFunction<void(const FIoChunkId& Id, TIoStatusOr<FIoBuffer> Result)>&& ChunkCallback);`
- L69 _public prototype_ `UE_INTERNAL void ReadChunksAsync(TConstArrayView<FIoHash> RawHashes, TUniqueFunction<void(const FIoHash& RawHash, TIoStatusOr<FIoBuffer> Result)>&& ChunkCallback);`
- L72 _public prototype_ `TIoStatusOr<FIoBuffer> ReadOpLogAttachment(FStringView Id);` — `UE_DEPRECATED(5.6, "Use ReadChunk(FIoHash) instead")`
- L74 _public function_ `const UE::Zen::FZenServiceInstance& GetZenServiceInstance() const`
- L75 _public function_ `UE::Zen::FZenServiceInstance& GetZenServiceInstance()`
- L77 _public prototype_ `TFuture<TIoStatusOr<FCbObject>> GetProjectInfo();`
- L78 _public prototype_ `TFuture<TIoStatusOr<FCbObject>> GetOplog(bool bTrimByReferencedset = true);`
- L79 _public prototype_ `TFuture<TArray<TIoStatusOr<FCbObject>>> GetOplogEntries(FStringView TargetProject, FStringView TargetOplog, TArray<FString> EntryKeys);`
- L80 _public prototype_ `TFuture<TIoStatusOr<FCbObject>> GetFiles();`
- L81 _public prototype_ `TFuture<TIoStatusOr<FCbObject>> GetChunkInfos();`
- L83 _public prototype_ `static const UTF8CHAR* FindOrAddAttachmentId(FUtf8StringView AttachmentText);`
- L84 _public prototype_ `static const UTF8CHAR* FindAttachmentId(FUtf8StringView AttachmentText);`
- L87 _private prototype_ `TIoStatusOr<FIoBuffer> ReadOpLogUri(FStringBuilderBase& ChunkUri, uint64 Offset = 0, uint64 Size = ~0ull);`
- L88 _private prototype_ `bool Download(Zen::FZenHttpRequest& Request, FStringView Uri, TArray64<uint8>* Buffer, Zen::EContentType AcceptType);`
- L89 _private prototype_ `bool Post(Zen::FZenHttpRequest& Request, FStringView Uri, FCbObjectView Obj);`
- L90 _private prototype_ `bool Post(Zen::FZenHttpRequest& Request, FStringView Uri, FMemoryView Payload);`
- L91 _private prototype_ `void Rpc(FAnsiStringView Uri, FCbObject RpcRequestObject, FCbPackage& OutResponse);`
- L92 _private prototype_ `void RpcAsync(FAnsiStringView Uri, FCbObject RpcRequestObject, TUniqueFunction<void(const FCbPackage& Response)>&& ResponseCallback);`
- L93 _private prototype_ `bool Delete(Zen::FZenHttpRequest& Request, FStringView Uri);`
- L94 _private prototype_ `bool ShouldRetry(Zen::FZenHttpRequest& Request);`
- L95 _private prototype_ `bool TryRecover();`
- L96 _private prototype_ `void SetRequestUri(class IHttpRequest& Request, FAnsiStringView Path);`
- L99 _private prototype_ `template<bool bAsync, typename T> void ReadChunks_Internal(TConstArrayView<T> Requests, TUniqueFunction<void(const T& Id, TIoStatusOr<FIoBuffer> Result)>&& ChunkCallback);`
- L101 _private prototype_ `void InitCommon();`
- L103 _private member_ `static const uint32 PoolEntryCount;`
- L117 _private member_ `UE::Zen::FScopeZenService ZenService;`
- L120 _private member_ `TUniquePtr<Zen::FZenHttpRequestPool> RequestPool;` — Legacy request pool
- L123 _private member_ `TUniquePtr<Zen::Internal::FZenHttpClientState> ClientState;` — Newer connection pool and request queue
- L125 _private member_ `FSaltGenerator SaltGen;`
- L126 _private member_ `FString ProjectPath;`
- L127 _private member_ `FString OplogPath;`
- L128 _private member_ `FAnsiString OplogRpcPath;`
- L129 _private member_ `FString OplogNewEntryPath;`
- L130 _private member_ `FString OplogPrepNewEntryPath;`
- L131 _private member_ `FString TempDirPath;`
- L132 _private member_ `const uint64 StandaloneThresholdBytes = 1 * 1024 * 1024;`
- L133 _private member_ `bool bAllowRead = false;`
- L134 _private member_ `bool bAllowEdit = false;`
- L135 _private member_ `bool bConnectionSucceeded = false;`

#### struct `UE::FZenStoreHttpClient::FSaltGenerator`  
`struct FSaltGenerator`  
_L104-115_
- L106 _public prototype_ `FSaltGenerator();`
- L107 _public function_ `inline int32_t Next()`
- L113 _private member_ `static std::atomic<uint32> GOpCounter;`
- L114 _private member_ `const uint32_t SaltBase;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API IOSTOREUTILITIES_API`
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Zen` (scope `UE`)
- L31 _namespace_ `namespace Internal` (scope `UE::Zen`)

### `Source/Developer/IoStoreUtilities/Private/CookMetadataFiles.h` (Private)


#### enum `ECookMetadataFiles`  
`enum class ECookMetadataFiles`  
_L12-18_
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `AssetRegistry = 1`
- L16 _public enumerator_ `CookMetadata = 2`
- L17 _public enumerator_ `All = 4`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cook` (scope `UE`)
- L19 _prototype_ `ENUM_CLASS_FLAGS(ECookMetadataFiles);`
- L21 _prototype_ `ECookMetadataFiles FindAndLoadMetadataFiles( FCookedPackageStore* InPackageStore, const FString& InCookedDir, ECookMetadataFiles InRequiredFiles, FAssetRegistryState& OutAssetRegistry, FString* OutAssetRegistryFileName , UE::Cook::FCookMetadataState* OutCookMetadata, FString* OutCookMetadataFileName );`

### `Source/Developer/IoStoreUtilities/Private/IoStoreLooseFiles.h` (Private)


#### struct `FLooseFilesWriterSettings`  
`struct FLooseFilesWriterSettings`  
_L11-16_
- L13 _public member_ `FString TocFilePath;`
- L14 _public member_ `FString TargetRootPath;`
- L15 _public member_ `FName ContainerName;`

#### Free symbols / members of external scopes

- L18 _prototype_ `TSharedPtr<IIoStoreWriter> MakeLooseFilesIoStoreWriter(const FLooseFilesWriterSettings& WriterSettings, uint32 MaxConcurrentWrites = 64);`

### `Source/Developer/IoStoreUtilities/Private/IoStoreShaderLibraryProcessor.h` (Private)


#### struct `UE::IoStore::Private::FShaderAssociationInfo`  
`struct FShaderAssociationInfo`  
_L31-83_
- desc: Carries association between shaders and packages from shader processing to size assignment.
- L62 _public function_ `friend uint32 GetTypeHash(const FShaderChunkInfoKey& Key)`
- L66 _public function_ `friend bool operator == (const FShaderChunkInfoKey& LHS, const FShaderChunkInfoKey& RHS)`
- L72 _public member_ `TMap<FShaderChunkInfoKey, FShaderChunkInfo> ShaderChunkInfos;`
- L75 _public member_ `TMap<FName , TArray<FShaderChunkInfoKey>> PackageShaderMap;` — The list of shaders referenced by each package. This can be used to look up in to ContainerShaderInfos.
- L78 _public function_ `FORCEINLINE void AddPackageShaderInfoKey(const FName& PackageName, const FShaderChunkInfoKey& InfoKey)` — Adds a shader chunk info key to the PackageShaderMap for the specified package name.

#### struct `UE::IoStore::Private::FShaderAssociationInfo::FShaderChunkInfo`  
`struct FShaderChunkInfo`  
_L33-55_
- L48 _public member_ `EType Type;`
- L49 _public member_ `TArray<FName> ReferencedByPackages;`
- L50 _public member_ `uint32 CompressedSize = 0;`
- L51 _public member_ `UE::Cook::EPluginSizeTypes SizeType;`
- L54 _public member_ `FString SharedPluginName;` — If we are shared across plugins, this is our pseudo plugin name. This is generated during size assignment.

#### enum `UE::IoStore::Private::FShaderAssociationInfo::FShaderChunkInfo::EType`  
`enum EType`  
_L35-46_
- L39 _public enumerator_ `Package` — This shader is referenced by one or more packages and can assign its size to those packages
- L42 _public enumerator_ `Global` — This shader is needed by the baseline engine in some manner and is a flat size cost.
- L45 _public enumerator_ `Orphan` — This shader isn't global or referenced by packages - theoretically shouldn't exist.

#### struct `UE::IoStore::Private::FShaderAssociationInfo::FShaderChunkInfoKey`  
`struct FShaderChunkInfoKey`  
_L57-70_
- L59 _public member_ `FName PakChunkName;`
- L60 _public member_ `FIoChunkId IoChunkId;`

#### struct `UE::IoStore::Private::FContainerChunkDependency`  
`struct FContainerChunkDependency`  
_L92-97_
- desc: @lh-todo Move this information into FContainerSourceSpec and FContainerTargetSpec. This information should be determined in `ParseContainerGenerationArguments()` when the source containers are built, and then transferred to the target containers in `InitializeContainerTargetsAndPackages()`. More testing beyond shaders for this is required, so keep this information private to the shader library processor for now. Same goes for `IsTargetFileGlobalShaderLibrary()`, which should be determined as soon as the source container is generated instead of parsing the filename later on to extract those flags.
- L94 _public member_ `int32 ChunkId = INDEX_NONE;`
- L95 _public member_ `bool bIsExternalContainer = false;` — Is the container loaded externally? E.g. pakchunk100iad, pakchunk100ondemand, etc.
- L96 _public member_ `TSet<int32> ChunkDependencies;`

#### struct `UE::IoStore::Private::FIoStoreShaderLibraryOutput`  
`struct FIoStoreShaderLibraryOutput`  
_L99-103_
- L101 _public member_ `TArray<FShaderInfo*> ShaderInfos;`
- L102 _public member_ `FShaderAssociationInfo AssocInfo;`

#### class `UE::IoStore::Private::FIoStoreShaderLibraryProcessor`  
`class FIoStoreShaderLibraryProcessor`  
_L108-219_
- desc: Processor to load cooked shader libraries and package them into IoStore entries
- L123 _private member_ `FCookedPackageStore* PackageStore = nullptr;` — Input arguments
- L124 _private member_ `FOodleDataCompression::ECompressor ShaderOodleCompressor = FOodleDataCompression::ECompressor::NotSet;`
- L125 _private member_ `FOodleDataCompression::ECompressionLevel ShaderOodleLevel = FOodleDataCompression::ECompressionLevel::None;`
- L128 _private member_ `TMap<FIoChunkId, FShaderInfo*> ChunkIdToShaderInfoMap;` — Persitent data for entire shader library processing
- L129 _private member_ `TMap<FShaderHash, TArray<FIoChunkId>> ShaderMapToGroupChunkIds;` — Maps from shader map hash to its set of shader group IoChunk Ids
- L130 _private member_ `TMap<FContainerTargetSpec*, TSet<FShaderInfo*>> ContainerTargetToShaderLibrary;`
- L131 _private member_ `FShaderMapAssetAssociations ShaderMapAssetAssociations;`
- L132 _private member_ `TMap<const FContainerTargetSpec*, FContainerChunkDependency> ContainerTargetToChunkDependencies;`
- L135 _private member_ `TArray<FShaderGroupIoChunk> CodeIoChunks;` — Intermediate data while processing a subset of target files
- L136 _private member_ `TArray<FShaderGroupIoChunkMap> CodeIoChunkMaps;` — Maps from shadermap index to shader group IoChunks
- L140 _private member_ `TMap<FString, TUniquePtr<FEditorShaderCodeArchive>> AllMonolithicShaderArchives;` — Intermediate data for chunk re-assignment
- L141 _private member_ `TMap<const FContainerTargetFile*, TUniquePtr<FSerializedShaderArchiveBuffer>> AllAssignedSerializedShaders;`
- L142 _private member_ `TMap<int32, FContainerShaderArchives> ChunkIdToContainerInfo;` — Maps ChunkId to the container information with all their assigned shader archives
- L147 _private member_ `TMap<FString, FContainerTargetSpec*> FormatToOverrideContainer;` — Resolved [ShaderCodeLibrary.PakChunkOverride] +FormatTargetContainer entries. Maps a shader Format-Platform string (e.g. "PCD3D_SM5-PCD3D_SM5") to the container its shaders should be redirected into. Populated by ResolveFormatTargetContainerOverrides at the start of ProcessShaderLibraries when the chunk override is enabled.
- L151 _private member_ `TSet<FName> AllPackagesAcrossContainers;` — Union of every package across every container, used as the "include all" asset filter when assigning shaders into a FormatTargetContainer override target. Populated alongside FormatToOverrideContainer; empty when no overrides exist.
- L168 _private member_ `TMap<FName, FMonolithicArchiveDebugInfo> ChunkAssignmentDebugInfo;`
- L172 _public prototype_ `FIoStoreShaderLibraryProcessor();`
- L173 _public prototype_ `~FIoStoreShaderLibraryProcessor();`
- L175 _public prototype_ `void ProcessShaderLibraries(const FIoStoreArguments& Arguments, TArrayView<FContainerTargetSpec*> ContainerTargets, FIoStoreShaderLibraryOutput& Output);`
- L178 _private prototype_ `bool ProcessShaderLibraryFromTargetFile(const FIoStoreArguments& Arguments, FContainerTargetFile& TargetFile, FIoStoreShaderLibraryOutput& Output, const FString& ProjectDir);`
- L185 _private prototype_ `void ResolveFormatTargetContainerOverrides(TArrayView<FContainerTargetSpec*> ContainerTargets, TArrayView<const FString> InFormatAndPlatformNames);` — Reads [ShaderCodeLibrary.PakChunkOverride] +FormatTargetContainer entries from GEngineIni, resolves each referenced container against ContainerTarget->Name, validates that the configured format is one this cook actually produces, and populates FormatToOverrideContainer. Rules whose format isn't present in InFormatAndPlatformNames are dropped with a Warning -- catches typos and stray cross-platform config.
- L188 _private prototype_ `void BuildContainerTargetChunkDependencies(const FContainerTargetSpec* ContainerTarget);` — Builds the chunk dependency information for the specified container target. See ContainerTargetToChunkDependencies.
- L191 _private prototype_ `bool PreloadShaderArchive(const FContainerTargetFile& TargetFile);` — Preloads the *.ushaderbytecode for the specified target file for later chunk assignment.
- L194 _private prototype_ `bool AssignShaderArchives(const FContainerTargetFile& TargetFile);` — Assigns preloaded shader archives to their respective target file (i.e. to their respective pakchunks).
- L196 _private prototype_ `void AddShaderMapsToPakChunkDebugInfo(const FContainerTargetFile& TargetFile, const FSerializedShaderArchiveBuffer& SerializedShaders, FName FormatAndPlatformName, int32 ChunkAssignmentType);`
- L200 _private prototype_ `void LogChunkOverrideStats(FName FormatAndPlatformName);` — Logs statistics about how many shadermaps have been duplicated and deduplicated.
- L204 _private prototype_ `bool DumpChunkOverrideDebugInfo(FName FormatAndPlatformName, FArchive& Ar);` — Writes out a debug file with information about all the shaders that have been re-assigned to a difference chunk (if r.ShaderCodeLibrary.PakChunkOverride is enabled).
- L208 _private prototype_ `bool LoadSerializedShaders(const FContainerTargetFile& TargetFile, FSerializedShaderArchiveBuffer& OutSerializedShaders, bool bIncludeTypeInfo = false, FShaderLibraryNameInfo* OutNameInfo = nullptr);` — Loads the serialized shaders of the *.ushaderbytecode file of the specified target.
- L211 _private prototype_ `bool ConvertToIoStoreShaderLibrary(FContainerTargetFile& TargetFile, const FSerializedShaderArchiveBuffer& SerializedShaders, const FString& ProjectDir);` — Converts the *.ushaderbytecode file of the specified target to an IoStore shader code library.
- L214 _private prototype_ `void FlushCodeIoChunks(FContainerTargetSpec* ContainerTarget, FIoStoreShaderLibraryOutput& Output, FShaderInfo::EShaderType ShaderType);` — Flushes all generated shader code IoChunks to the output.
- L216 _private prototype_ `void UpdatePackageStoreShaders(FCookedPackage* Package, const FName& ContainerTargetName);`
- L217 _private prototype_ `void AddAllReferencedShadersToContainerTarget(FContainerTargetSpec* ContainerTarget, FIoStoreShaderLibraryOutput& Output);`

#### struct `UE::IoStore::Private::FIoStoreShaderLibraryProcessor::FShaderGroupIoChunkMap`  
`struct FShaderGroupIoChunkMap`  
_L111-115_
- desc: Shader map hash with its IoChunk Ids of all its shader groups
- L113 _public member_ `FShaderHash ShaderMapHash;`
- L114 _public member_ `TArray<FIoChunkId> ShaderGroupChunkIds;`

#### struct `UE::IoStore::Private::FIoStoreShaderLibraryProcessor::FContainerShaderArchives`  
`struct FContainerShaderArchives`  
_L117-120_
- L119 _public member_ `TArray<FSerializedShaderArchiveBuffer*> AssignedSerializedShaders;`

#### enum `UE::IoStore::Private::FIoStoreShaderLibraryProcessor::EChunkAssignmentType`  
`enum EChunkAssignmentType`  
_L154-158_
- desc: Debug information (used with CVar `r.ShaderCodeLibrary.PakChunkOverride.DumpDebugInfo`)
- L156 _public enumerator_ `ChunkAssignment_Old = (1 << 0)`
- L157 _public enumerator_ `ChunkAssignment_New = (1 << 1)`

#### struct `UE::IoStore::Private::FIoStoreShaderLibraryProcessor::FChunkAssignmentInfo`  
`struct FChunkAssignmentInfo`  
_L159-163_
- L161 _public member_ `TArray<FName> OldPakChunks;`
- L162 _public member_ `TArray<FName> NewPakChunks;`

#### struct `UE::IoStore::Private::FIoStoreShaderLibraryProcessor::FMonolithicArchiveDebugInfo`  
`struct FMonolithicArchiveDebugInfo`  
_L164-167_
- L166 _public member_ `TMap<FShaderHash, FChunkAssignmentInfo> ShaderMaps;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace IoStore` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::IoStore`)

### `Source/Developer/IoStoreUtilities/Private/IoStoreUtilitiesCore.h` (Private)


#### struct `UE::IoStore::Private::FContainerSourceFile`  
`struct FContainerSourceFile`  
_L30-36_
- L32 _public member_ `FString NormalizedPath;`
- L33 _public member_ `FString DestinationPath;`
- L34 _public member_ `bool bNeedsCompression = false;`
- L35 _public member_ `bool bNeedsEncryption = false;`

#### struct `UE::IoStore::Private::FContainerSourceSpec`  
`struct FContainerSourceSpec`  
_L38-50_
- L40 _public member_ `FName Name;`
- L41 _public member_ `FString OutputPath;`
- L42 _public member_ `FString OptionalOutputPath;`
- L43 _public member_ `FString StageLooseFileRootPath;`
- L44 _public member_ `TArray<FContainerSourceFile> SourceFiles;`
- L45 _public member_ `FString PatchTargetFile;`
- L46 _public member_ `TArray<FString> PatchSourceContainerFiles;`
- L47 _public member_ `FString EncryptionKeyOverrideGuid;`
- L48 _public member_ `bool bGenerateDiffPatch = false;`
- L49 _public member_ `bool bOnDemand = false;`

#### struct `UE::IoStore::Private::FCookedFileStatData`  
`struct FCookedFileStatData`  
_L52-71_
- L69 _public member_ `int64 FileSize = 0;`
- L70 _public member_ `EFileType FileType = Invalid;`

#### enum `UE::IoStore::Private::FCookedFileStatData::EFileType`  
`enum EFileType`  
_L54-67_
- L56 _public enumerator_ `PackageHeader`
- L57 _public enumerator_ `PackageData`
- L58 _public enumerator_ `BulkData`
- L59 _public enumerator_ `OptionalBulkData`
- L60 _public enumerator_ `MemoryMappedBulkData`
- L61 _public enumerator_ `ShaderLibrary`
- L62 _public enumerator_ `Regions`
- L63 _public enumerator_ `OptionalSegmentPackageHeader`
- L64 _public enumerator_ `OptionalSegmentPackageData`
- L65 _public enumerator_ `OptionalSegmentBulkData`
- L66 _public enumerator_ `Invalid`

#### class `UE::IoStore::Private::FCookedFileStatMap`  
`class FCookedFileStatMap`  
_L73-92_
- L76 _public prototype_ `FCookedFileStatMap();`
- L78 _public function_ `FORCEINLINE int32 Num() const`
- L83 _public prototype_ `void Add(const TCHAR* Path, int64 FileSize);`
- L85 _public prototype_ `const FCookedFileStatData* Find(FStringView NormalizedPath) const;`
- L88 _private prototype_ `const FCookedFileStatData::EFileType* FindFileTypeFromExtension(const FStringView& Extension);`
- L90 _private member_ `TArray<TTuple<FString, FCookedFileStatData::EFileType>> Extensions;`
- L91 _private member_ `TMap<FString, FCookedFileStatData> Map;`

#### enum `UE::IoStore::Private::EFallbackOrderMode`  
`enum class EFallbackOrderMode`  
_L94-99_
- L96 _public enumerator_ `LoadOrder` — Default fallback ordering. Uses LoadOrder dependency ordering
- L97 _public enumerator_ `AlphabeticalClustered` — As above but clusters are sorted alphabetically at the end for improved patching stability
- L98 _public enumerator_ `Alphabetical` — Pure alphabetical fallback ordering. Best for patching stability but not optimized to reduce seeks

#### struct `UE::IoStore::Private::FIoStoreOrderingOptions`  
`struct FIoStoreOrderingOptions`  
_L101-116_
- L103 _public member_ `bool bClusterByOrderFilePriority = false;`
- L104 _public member_ `bool bAlphaSortClusterPackageLists = false;`
- L105 _public member_ `bool bPlaceShadersAtEnd = false;`
- L107 _public member_ `EFallbackOrderMode FallbackOrderMode = EFallbackOrderMode::LoadOrder;`
- L109 _public function_ `bool operator==(const FIoStoreOrderingOptions& Other) const`

#### struct `UE::IoStore::Private::FReleasedPackages`  
`struct FReleasedPackages`  
_L120-124_
- L122 _public member_ `TSet<FName> PackageNames;`
- L123 _public member_ `TMap<FPackageId, FName> PackageIdToName;`

#### struct `UE::IoStore::Private::FFileOrderMap`  
`struct FFileOrderMap`  
_L126-138_
- L128 _public member_ `TMap<FName, int64> PackageNameToOrder;`
- L129 _public member_ `FString Name;`
- L130 _public member_ `int32 Priority;`
- L131 _public member_ `int32 Index;`
- L133 _public function_ `FFileOrderMap(int32 InPriority, int32 InIndex) : Priority(InPriority) , Index(InIndex)`

#### struct `UE::IoStore::Private::FIoStoreArguments`  
`struct FIoStoreArguments`  
_L140-178_
- L142 _public member_ `FString GlobalContainerPath;`
- L143 _public member_ `FString CookedDir;`
- L144 _public member_ `TArray<FContainerSourceSpec> Containers;`
- L145 _public member_ `FCookedFileStatMap CookedFileStatMap;`
- L146 _public member_ `TArray<FFileOrderMap> OrderMaps;`
- L147 _public member_ `FKeyChain KeyChain;`
- L148 _public member_ `FKeyChain PatchKeyChain;`
- L149 _public member_ `FString DLCPluginPath;`
- L150 _public member_ `FString DLCName;`
- L151 _public member_ `FString ReferenceChunkGlobalContainerFileName;`
- L152 _public member_ `FString ReferenceChunkChangesCSVFileName;`
- L153 _public member_ `FString ReferenceChunkAdditionalContainersPath;`
- L154 _public member_ `FString PatchInPlaceReferenceContainerPathOverride;`
- L155 _public member_ `FString PatchInPlaceReferenceAdditionalContainersPath;`
- L156 _public member_ `FString CsvPath;`
- L157 _public member_ `FKeyChain ReferenceChunkKeys;`
- L158 _public member_ `FKeyChain PatchInPlaceReferenceChunkKeys;`
- L159 _public member_ `FReleasedPackages ReleasedPackages;`
- L160 _public member_ `TUniquePtr<FCookedPackageStore> PackageStore;`
- L161 _public member_ `TUniquePtr<FIoBuffer> ScriptObjects;`
- L162 _public member_ `FIoStoreOrderingOptions OrderingOptions;`
- L163 _public member_ `TMap<FString, FIoStoreOrderingOptions> OrderingOptionsOverrides;`
- L164 _public member_ `bool bSign = false;`
- L165 _public member_ `bool bRemapPluginContentToGame = false;`
- L166 _public member_ `bool bCreateDirectoryIndex = true;`
- L167 _public member_ `bool bFileRegions = false;`
- L168 _public member_ `EAssetRegistryWritebackMethod WriteBackMetadataToAssetRegistry = EAssetRegistryWritebackMethod::Disabled;`
- L169 _public member_ `bool bWritePluginSizeSummaryJsons = false;` — Only valid if WriteBackMetadataToAssetRegistry != Disabled.
- L171 _public member_ `FOodleDataCompression::ECompressor ShaderOodleCompressor = FOodleDataCompression::ECompressor::Mermaid;`
- L172 _public member_ `FOodleDataCompression::ECompressionLevel ShaderOodleLevel = FOodleDataCompression::ECompressionLevel::Normal;`
- L174 _public function_ `bool IsDLC() const`

#### struct `UE::IoStore::Private::FShaderGroupIoChunk`  
`struct FShaderGroupIoChunk`  
_L181-196_
- desc: IoChunk per shader group
- L183 _public member_ `FIoChunkId ChunkId;`
- L184 _public member_ `FIoBuffer CodeIoBuffer;`
- L185 _public member_ `uint32 LoadOrderFactor = MAX_uint32;` — the smaller the order, the more likely this will be loaded
- L187 _public function_ `static bool Sort(const FShaderGroupIoChunk& A, const FShaderGroupIoChunk& B)`

#### struct `UE::IoStore::Private::FShaderInfo`  
`struct FShaderInfo`  
_L198-211_
- L202 _public member_ `FShaderGroupIoChunk ShaderGroupChunk;`
- L203 _public member_ `TSet<struct FCookedPackage*> ReferencedByPackages;`
- L204 _public member_ `TMap<FContainerTargetSpec*, EShaderType> TypeInContainer;`
- L207 _public function_ `static bool Sort(const FShaderInfo* A, const FShaderInfo* B)` — This is used to ensure build determinism and such must be stable across builds.

#### enum `UE::IoStore::Private::FShaderInfo::EShaderType`  
`enum EShaderType`  
_L200-200_
- L200 _public enumerator_ `enum EShaderType { Normal, Global, Inline }; FShaderGroupIoChunk ShaderGroupChunk; TSet<struct FCookedPackage*> ReferencedByPackages; TMap<FContainerTargetSpec*`
- L200 _public enumerator_ `enum EShaderType { Normal, Global, Inline }; FShaderGroupIoChunk ShaderGroupChunk; TSet<struct FCookedPackage*> ReferencedByPackages; TMap<FContainerTargetSpec*`
- L200 _public enumerator_ `enum EShaderType { Normal, Global, Inline }; FShaderGroupIoChunk ShaderGroupChunk; TSet<struct FCookedPackage*> ReferencedByPackages; TMap<FContainerTargetSpec*`

#### struct `UE::IoStore::Private::FCookedPackage`  
`struct FCookedPackage`  
_L213-231_
- L215 _public member_ `FPackageId GlobalPackageId;`
- L216 _public member_ `FName PackageName;`
- L217 _public member_ `FName SourcePackageName;` — Source package name for redirected package
- L218 _public member_ `TArray<FShaderInfo*> Shaders;`
- L219 _public member_ `TArray<FShaderHash> ShaderMapHashes;`
- L220 _public member_ `uint64 UAssetSize = 0;`
- L221 _public member_ `uint64 OptionalSegmentUAssetSize = 0;`
- L222 _public member_ `uint64 UExpSize = 0;`
- L223 _public member_ `uint64 TotalBulkDataSize = 0;`
- L224 _public member_ `uint64 LoadOrder = MAX_uint64;` — Ordered by dependencies
- L225 _public member_ `uint64 DiskLayoutOrder = MAX_uint64;` — Final order after considering input order files
- L226 _public member_ `uint64 OverrideDiskLayoutOrder = MAX_uint64;` — Final order after applying custom per-container ordering
- L227 _public member_ `FPackageStoreEntryResource PackageStoreEntry;`
- L228 _public member_ `int32 PreOrderNumber = -1;` — Used for sorting in load order
- L229 _public member_ `bool bPermanentMark = false;` — Used for sorting in load order
- L230 _public member_ `bool bIsLocalized = false;`

#### struct `UE::IoStore::Private::FLegacyCookedPackage`  
`struct FLegacyCookedPackage : public FCookedPackage`  
_L233-240_
- inherits: `FCookedPackage`
- L236 _public member_ `FString FileName;`
- L237 _public member_ `FString OptionalSegmentFileName;`
- L238 _public member_ `FPackageStorePackage* OptimizedPackage = nullptr;`
- L239 _public member_ `FPackageStorePackage* OptimizedOptionalSegmentPackage = nullptr;`

#### enum `UE::IoStore::Private::EContainerChunkType`  
`enum class EContainerChunkType`  
_L242-253_
- L244 _public enumerator_ `ShaderCodeLibrary`
- L245 _public enumerator_ `ShaderCode`
- L246 _public enumerator_ `PackageData`
- L247 _public enumerator_ `BulkData`
- L248 _public enumerator_ `OptionalBulkData`
- L249 _public enumerator_ `MemoryMappedBulkData`
- L250 _public enumerator_ `OptionalSegmentPackageData`
- L251 _public enumerator_ `OptionalSegmentBulkData`
- L252 _public enumerator_ `Invalid`

#### struct `UE::IoStore::Private::FContainerTargetFile`  
`struct FContainerTargetFile`  
_L255-272_
- L257 _public member_ `FContainerTargetSpec* ContainerTarget = nullptr;`
- L258 _public member_ `FCookedPackage* Package = nullptr;`
- L259 _public member_ `FString NormalizedSourcePath;`
- L260 _public member_ `TOptional<FIoBuffer> SourceBuffer;`
- L261 _public member_ `FString DestinationPath;`
- L262 _public member_ `uint64 SourceSize = 0;`
- L263 _public member_ `uint64 IdealOrder = 0;`
- L264 _public member_ `FIoChunkId ChunkId;`
- L265 _public member_ `FIoHash ChunkHash;`
- L266 _public member_ `FBulkDataCookedIndex BulkDataCookedIndex;`
- L267 _public member_ `TArray<uint8> PackageHeaderData;`
- L268 _public member_ `EContainerChunkType ChunkType;`
- L269 _public member_ `bool bForceUncompressed = false;`
- L270 _public member_ `FIoChunkId DuplicateOfChunkId = {};` — when valid, is source byte identical to provided chunkid, including alignment requirements
- L271 _public member_ `TArray<FFileRegion> FileRegions;`

#### struct `UE::IoStore::Private::FPackageRedirectRequest`  
`struct FPackageRedirectRequest`  
_L274-279_
- L276 _public member_ `FPackageId SourcePackageId;`
- L277 _public member_ `FPackageId TargetPackageId;`
- L278 _public member_ `FName SourcePackageName;`

#### struct `UE::IoStore::Private::FContainerTargetSpec`  
`struct FContainerTargetSpec`  
_L281-305_
- L283 _public member_ `FIoContainerId ContainerId;`
- L284 _public member_ `FIoContainerId OptionalSegmentContainerId;`
- L285 _public member_ `FIoContainerHeader Header;`
- L286 _public member_ `FIoContainerHeader OptionalSegmentHeader;`
- L287 _public member_ `FName Name;`
- L288 _public member_ `FGuid EncryptionKeyGuid;`
- L289 _public member_ `FString OutputPath;`
- L290 _public member_ `FString OptionalSegmentOutputPath;`
- L291 _public member_ `FString StageLooseFileRootPath;`
- L292 _public member_ `TSharedPtr<IIoStoreWriter> IoStoreWriter;`
- L293 _public member_ `TSharedPtr<IIoStoreWriter> OptionalSegmentIoStoreWriter;`
- L294 _public member_ `TArray<FContainerTargetFile> TargetFiles;`
- L295 _public member_ `TArray<TUniquePtr<FIoStoreReader>> PatchSourceReaders;`
- L296 _public member_ `EIoContainerFlags ContainerFlags = EIoContainerFlags::None;`
- L297 _public member_ `TArray<FCookedPackage*> Packages;`
- L298 _public member_ `TSet<FShaderInfo*> GlobalShaders;`
- L299 _public member_ `TSet<FShaderInfo*> SharedShaders;`
- L300 _public member_ `TSet<FShaderInfo*> UniqueShaders;`
- L301 _public member_ `TSet<FShaderInfo*> InlineShaders;`
- L302 _public member_ `TArray<FPackageRedirectRequest> PackageRedirects;`
- L303 _public member_ `TArray<FPackageRedirectRequest> OptionalSegmentPackageRedirects;`
- L304 _public member_ `bool bGenerateDiffPatch = false;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define IOSTORE_CPU_SCOPE(NAME) TRACE_CPUPROFILER_EVENT_SCOPE(IoStore##NAME);`
- L23 _macro_ `#define IOSTORE_CPU_SCOPE_DATA(NAME, DATA) TRACE_CPUPROFILER_EVENT_SCOPE(IoStore##NAME);`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace IoStore` (scope `UE`)
- L25 _namespace_ `namespace Private` (scope `UE::IoStore`)
- L118 _prototype_ `uint32 GetTypeHash(const FIoStoreOrderingOptions& OrderingOptions);` (scope `UE::IoStore::Private`)
- L324 _prototype_ `int32 GetFullExtensionStartIndex(FStringView Path);` (scope `UE::IoStore::Private`) — Finds where the extension starts in a path. We can't just find the left most '.' in the file name because the path might contain a bulkdata cooked index (@see FBulkDataCookedIndex) and we don't want to include the index part. We are attempting to match up the extensions with those found in the constructor of FCookedFileStatMap. For example take the following filenames and the extensions we want to find: <packagename>.m.ubulk   -> .m.ubulk <packagename>.o.ubulk   -> .o.ubulk <packagename>.001.ubulk ->.ubulk So we want to find the left most '.' unless that is followed by only numeric values in which case we have found a cooked index and we want to find the '.' after those values.
- L326 _prototype_ `FStringView GetFullExtension(FStringView Path);` (scope `UE::IoStore::Private`)

### `Source/Developer/IoStoreUtilities/Private/IoStoreWriter.h` (Private)


#### struct `FIoStoreWriterSettings`  
`struct FIoStoreWriterSettings`  
_L12-41_
- L14 _public member_ `FName CompressionMethod = NAME_None;`
- L15 _public member_ `uint64 CompressionBlockSize = 64 << 10;`
- L19 _public member_ `uint64 CompressionBlockAlignment = 0;` — This does not align every entry - it tries to prevent excess crossings of this boundary by inserting padding. and happens whether or not the entry is compressed.
- L20 _public member_ `int32 CompressionMinBytesSaved = 0;`
- L21 _public member_ `int32 CompressionMinPercentSaved = 0;`
- L22 _public member_ `int32 CompressionMinSizeToConsiderDDC = 0;`
- L23 _public member_ `uint64 MemoryMappingAlignment = 0;`
- L24 _public member_ `uint64 MaxPartitionSize = 0;`
- L25 _public member_ `uint64 PatchInPlaceMaximumTotalGrowth = 0;` — fail build if total overhead goes over this value and bUsePatchInPlaceLayout is enabled, 0 to ignore
- L26 _public member_ `uint64 PatchInPlaceMaximumPerContainerGrowth = 0;` — defragment container if it's overhead goes above this value by moving some entries, 0 to ignore
- L27 _public member_ `uint64 PatchInPlaceParetoFrontCoarseSamples = 0;` — amount of coarse samples to use for pareto front probing during defrag
- L28 _public member_ `uint64 PatchInPlaceParetoFrontFineSamples = 0;` — amount of fine samples to fine tune pareto front during defrag
- L29 _public member_ `uint64 PatchInPlaceReadGranularity = 0;` — group inserted entries with-in read granularity bins based on offsets from file open order, 0 to ignore
- L30 _public member_ `uint64 PatchInPlaceMaxChainSize = 0;` — largest possible insertion chain size, 0 to ignore
- L31 _public member_ `int32 PatchInPlaceMaxChainLength = 0;` — largest possible insertion chain length, 0 to ignore
- L32 _public member_ `uint8 PatchInPlaceParetoFrontHeuristic = 0;` — heuristic to choose for pareto front, see FPatchInPlaceLayout::BuildUnpinCandidates
- L33 _public member_ `TMap<FString, uint64> MaxPartitionSizeOverride;`
- L34 _public member_ `bool bEnableFileRegions = false;`
- L35 _public member_ `bool bContainerMetaEnabled = false;`
- L36 _public member_ `bool bPerContainerMeta = false;`
- L37 _public member_ `bool bCompressionEnableDDC = false;`
- L38 _public member_ `bool bValidateChunkHashes = false;`
- L39 _public member_ `bool bUsePatchInPlaceLayout = false;`
- L40 _public member_ `bool bDeduplicateChunks = false;`

#### struct `FIoStoreWriterResult`  
`struct FIoStoreWriterResult`  
_L43-66_
- L45 _public member_ `FIoContainerId ContainerId;`
- L46 _public member_ `FString ContainerName;` — This is the base filename of the utoc used for output.
- L47 _public member_ `int64 TocSize = 0;`
- L48 _public member_ `int64 TocEntryCount = 0;`
- L49 _public member_ `int64 PaddingSize = 0;`
- L50 _public member_ `int64 UncompressedContainerSize = 0;` — this is the size the container would be if it were uncompressed.
- L51 _public member_ `int64 CompressedContainerSize = 0;` — this is the size of the container with the given compression (which may be none). Should be the sum of all partition file sizes.
- L52 _public member_ `int64 DirectoryIndexSize = 0;`
- L53 _public member_ `uint64 TotalEntryCompressedSize = 0;` — sum of the compressed size of entries excluding encryption alignment.
- L54 _public member_ `uint64 ReferenceCacheMissBytes = 0;` — number of compressed bytes excluding alignment that could have been from refcache but weren't.
- L55 _public member_ `uint64 PatchInPlaceSizeBeforeLayout = 0;`
- L56 _public member_ `uint64 PatchInPlacePinnedSizeBeforeDefrag = 0;`
- L57 _public member_ `uint64 PatchInPlacePinnedSizeAfterDefrag = 0;`
- L58 _public member_ `int64 PatchInPlaceLocalityChange = 0;`
- L59 _public member_ `uint64 AddedChunksCount = 0;`
- L60 _public member_ `uint64 AddedChunksSize = 0;`
- L61 _public member_ `uint64 ModifiedChunksCount = 0;`
- L62 _public member_ `uint64 ModifiedChunksSize = 0;`
- L63 _public member_ `uint64 DeduplicatedSavedBytes = 0;`
- L64 _public member_ `FName CompressionMethod = NAME_None;`
- L65 _public member_ `EIoContainerFlags ContainerFlags = EIoContainerFlags::None;`

#### struct `FIoWriteOptions`  
`struct FIoWriteOptions`  
_L68-76_
- L70 _public member_ `FString FileName;`
- L71 _public member_ `const TCHAR* DebugName = nullptr;`
- L73 _public member_ `FIoChunkId DuplicateOf = {};` — If valid, this chunk is byte-identical to specified chunk.
- L74 _public member_ `bool bForceUncompressed = false;`
- L75 _public member_ `bool bIsMemoryMapped = false;`

#### class `FIoStoreWriterContext`  
`class FIoStoreWriterContext`  
_L78-124_
- L111 _public prototype_ `FIoStoreWriterContext();`
- L112 _public prototype_ `~FIoStoreWriterContext();`
- L114 _public prototype_ `[[nodiscard]] FIoStatus Initialize(const FIoStoreWriterSettings& InWriterSettings);`
- L115 _public prototype_ `TSharedPtr<class IIoStoreWriter> CreateContainer(const TCHAR* InContainerPath, const FIoContainerSettings& InContainerSettings);`
- L116 _public prototype_ `void FinalizeLayout();`
- L117 _public prototype_ `void FinalizeWrites();`
- L118 _public prototype_ `FProgress GetProgress() const;`
- L119 _public prototype_ `uint32 GetErrors() const;`
- L120 _public prototype_ `void SaveContainerMeta(const FString& FilePath);`
- L123 _private member_ `FIoStoreWriterContextImpl* Impl;`

#### struct `FIoStoreWriterContext::FProgress`  
`struct FProgress`  
_L81-109_
- L83 _public member_ `uint64 TotalChunksCount = 0;`
- L84 _public member_ `uint64 HashedChunksCount = 0;`
- L86 _public member_ `uint64 HashDbChunksCount = 0;` — Number of chunks where we avoided reading and hashing, and instead used the result from the hashdb, and their types
- L87 _public member_ `uint64 HashDbChunksByType[(int8)EIoChunkType::MAX] = { 0 };`
- L89 _public member_ `uint64 CompressedChunksCount = 0;` — Number of chunks that were passed to the compressor (i.e. passed the various opt-outs), and their types
- L90 _public member_ `uint64 CompressedChunksByType[(int8)EIoChunkType::MAX] = { 0 };`
- L91 _public member_ `uint64 SerializedChunksCount = 0;`
- L92 _public member_ `uint64 ScheduledCompressionTasksCount = 0;`
- L93 _public member_ `uint64 ScheduledCompressionMemoryBytes = 0;`
- L94 _public member_ `uint64 CompressionDDCHitsByType[(int8)EIoChunkType::MAX] = { 0 };`
- L95 _public member_ `uint64 CompressionDDCPutsByType[(int8)EIoChunkType::MAX] = { 0 };`
- L96 _public member_ `uint64 CompressionDDCHitCount = 0;`
- L97 _public member_ `uint64 CompressionDDCMissCount = 0;`
- L98 _public member_ `uint64 CompressionDDCPutCount = 0;`
- L99 _public member_ `uint64 CompressionDDCPutErrorCount = 0;`
- L100 _public member_ `uint64 CompressionDDCGetBytes = 0;`
- L101 _public member_ `uint64 CompressionDDCPutBytes = 0;`
- L104 _public member_ `uint64 RefDbChunksCount{ 0 };` — The number of chunk retrieved from the reference cache database, and their types.
- L105 _public member_ `uint64 RefDbChunksByType[(int8)EIoChunkType::MAX] = { 0 };`
- L108 _public member_ `uint64 BeginCompressChunksByType[(int8)EIoChunkType::MAX] = { 0 };` — The type of chunk that landed in BeginCompress before any opt-outs.

#### class `IIoStoreWriteRequest`  
`class IIoStoreWriteRequest`  
_L126-148_
- L129 _public prototype_ `virtual ~IIoStoreWriteRequest() = default;`
- L131 _public prototype_ `virtual uint64 GetOrderHint() = 0;`
- L132 _public prototype_ `virtual TArrayView<const FFileRegion> GetRegions() = 0;`
- L133 _public prototype_ `virtual const FIoHash* GetChunkHash() = 0;`
- L136 _public prototype_ `virtual void PrepareSourceBufferAsync(UE::Tasks::FTaskEvent& CompletionEvent) = 0;` — Launches any async operations necessary in order to access the buffer. CompletionEvent is set once it's ready, which may be immediate.
- L139 _public prototype_ `virtual const FIoBuffer* GetSourceBuffer() = 0;` — Only valid after the completion event passed to PrepareSourceBufferAsync has fired.
- L142 _public prototype_ `virtual void FreeSourceBuffer() = 0;` — Can't be called between PrepareSourceBufferAsync and its completion!
- L144 _public prototype_ `virtual uint64 GetSourceBufferSizeEstimate() = 0;`
- L147 _public prototype_ `virtual const TCHAR* DebugNameOfRepository() const = 0;` — Return an identifier for the repository that is providing the source data, e.g. loosefile, zenserver.

#### class `IIoStoreWriterReferenceChunkDatabase`  
`class IIoStoreWriterReferenceChunkDatabase`  
_L150-197_
- L153 _public prototype_ `virtual ~IIoStoreWriterReferenceChunkDatabase() = default;`
- L173 _public prototype_ `virtual UE::Tasks::FTask RetrieveChunk(const FIoContainerId& InContainerId, const FIoHash& InChunkHash, const FIoChunkId& InChunkId, TUniqueFunction<void(TIoStatusOr<FIoStoreCompressedReadResult>)> InCompletionCallback) = 0;` — Used by IIoStoreWriter to check and see if there's a reference chunk that matches the data that IoStoreWriter wants to compress and write. Validity checks must be synchronous - if a chunk can't be used for some reason (no matching chunk exists or otherwise), this function must return false and not call InCompletionCallback. Once a matching chunk is found, it is read from the source iostore container asynchronously, and upon completion InCompletionCallback is called with the raw output from FIoStoreReader::ReadCompressed (i.e. FIoStoreCompressedReadResult). Failures once the async read process has started are currently fatal due to difficulties in rekicking a read. For the moment, changes in compression method are allowed. RetrieveChunk is not currently thread safe and must be called from a single thread. Chunks provided *MUST* decompress to bits that hash to the exact value provided in InChunkKey (i.e. be exactly the same bits), and also be the same number of blocks (i.e. same CompressionBlockSize)
- L180 _public prototype_ `virtual bool ChunkExists(const FIoContainerId& InContainerId, const FIoHash& InChunkHash, const FIoChunkId& InChunkId, int32& OutNumChunkBlocks) = 0;` — Quick synchronous existence check that returns the number of blocks for the chunk. This is used to set up the necessary structures without needing to read the source data for the chunk. This might be called from multiple threads as it has to happen after we have the source hash computed.
- L186 _public prototype_ `virtual uint32 GetCompressionBlockSize() const = 0;` — Returns the compression block size that was used to break up the IoChunks in the source containers. If this is different than what we want, then none of the chunks will ever match. Knowing this up front allows us to only match on hash
- L191 _public prototype_ `virtual void NotifyAddedToWriter(const FIoContainerId& InContainerId, const FString& InContainerName) = 0;` — Called by an iostore writer implementation to notify the ref cache it's been added
- L196 _public prototype_ `virtual bool GetContainerFilePath(const FIoContainerId& InContainerId, FString& OutContainerFilePath) = 0;` — Returns true if ContainerId was found and OutContainerFilePath is set.

#### class `IIoStoreWriter`  
`class IIoStoreWriter`  
_L199-214_
- L202 _public prototype_ `virtual ~IIoStoreWriter() = default;`
- L208 _public prototype_ `virtual void SetReferenceChunkDatabase(TSharedPtr<IIoStoreWriterReferenceChunkDatabase> ReferenceChunkDatabase, TSharedPtr<IIoStoreWriterReferenceChunkDatabase> PatchInPlaceReferenceChunkDatabase) = 0;` — If a reference database is provided, the IoStoreWriter implementation may elect to reuse compressed blocks from previous containers instead of recompressing input data. This must be set before any writes are appended.
- L209 _public prototype_ `virtual void EnableDiskLayoutOrdering(const TArray<TUniquePtr<FIoStoreReader>>& PatchSourceReaders = TArray<TUniquePtr<FIoStoreReader>>()) = 0;`
- L210 _public prototype_ `virtual void Append(const FIoChunkId& ChunkId, FIoBuffer Chunk, const FIoWriteOptions& WriteOptions, uint64 OrderHint = MAX_uint64) = 0;`
- L211 _public prototype_ `virtual void Append(const FIoChunkId& ChunkId, IIoStoreWriteRequest* Request, const FIoWriteOptions& WriteOptions) = 0;`
- L212 _public prototype_ `virtual TIoStatusOr<FIoStoreWriterResult> GetResult() = 0;`
- L213 _public prototype_ `virtual void EnumerateChunks(TFunction<bool(FIoStoreTocChunkInfo&&)>&& Callback) const = 0;`

### `Source/Developer/IoStoreUtilities/Private/ZenFileSystemManifest.h` (Private)


#### struct `FZenFileSystemManifestEntry`  
`struct FZenFileSystemManifestEntry`  
_L22-27_
- L24 _public member_ `FString ServerPath;`
- L25 _public member_ `FString ClientPath;`
- L26 _public member_ `FIoChunkId FileChunkId;`

#### class `FZenFileSystemManifest`  
`class FZenFileSystemManifest`  
_L29-96_
- L32 _public prototype_ `FZenFileSystemManifest(const ITargetPlatform& InTargetPlatform, FString InCookDirectory);`
- L35 _public prototype_ `void ConstructReferencedSetClientPath(const FString& MetadataDirectoryPath);`
- L36 _public prototype_ `void SetCookSandbox(UE::Cook::ICookSandbox* InCookSandbox);`
- L44 _public prototype_ `int32 Generate(const FString& MetadataDirectoryPath, const TOptional<ICookedPackageWriter::FReferencedPluginsInfo>& ReferencedPlugins = TOptional<ICookedPackageWriter::FReferencedPluginsInfo>());` — Scan the local Cooked folder for files on disk, create and append Entries for any files not already present in the manifest. Files in the manifest do not contain any payload data, so no update is necessary for Entries that already exist. Returns the number of new entries.
- L48 _public prototype_ `const FZenFileSystemManifestEntry& CreateManifestEntry(const FString& Filename);`
- L50 _public prototype_ `const FZenFileSystemManifestEntry& AddManifestEntry(const FIoChunkId& FileChunkId, FString ServerPath, FString ClientPath);`
- L52 _public function_ `TArrayView<const FZenFileSystemManifestEntry> ManifestEntries() const`
- L57 _public prototype_ `bool Save(const TCHAR* Filename);`
- L59 _public function_ `int32 NumEntries() const`
- L64 _public function_ `const FString& ServerRootPath() const`
- L75 _public function_ `TOptional<FZenFileSystemManifestEntry> GetReferencedSet() const` — Return the ManifestEntry that was found for the ReferencedSet.txt artifact left by the cooker in the Metadata directory. The ReferencedSet reports which packages in the oplog were cooked in the most recent incremental cook. ZenServer needs to read it, so we report it separately to ZenServer rather than reporting it with the rest of the cook artifacts reported in the EndCook op.
- L81 _private member_ `const ITargetPlatform& TargetPlatform;`
- L82 _private member_ `FString CookDirectory;`
- L83 _private member_ `FString ServerRoot;`
- L84 _private member_ `TMap<FString, int32> ServerPathToEntry;`
- L85 _private member_ `TArray<FZenFileSystemManifestEntry> Entries;`
- L86 _private member_ `TOptional<FZenFileSystemManifestEntry> ReferencedSet;`
- L88 _private member_ `FString ReferencedSetClientPath;`
- L89 _private member_ `UE::Cook::ICookSandbox* CookSandbox = nullptr;`
- L92 _private member_ `static const FZenFileSystemManifestEntry InvalidEntry;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ZenFileSystemManifest` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ZenFileSystemManifest` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Cook` (scope `UE`)

### `Source/Developer/IoStoreUtilities/Public/CookArtifactReader.h` (Public)


#### Free symbols / members of external scopes

- L10 _typedef_ `typedef UE::Cook::ICookArtifactReader ICookArtifactReader;` — `UE_DEPRECATED(5.8, "Use UE::Cook::ICookArtifactReader.")`

### `Source/Developer/IoStoreUtilities/Public/CookArtifactReaderCommon.h` (Public)


#### class `FCookArtifactReaderCommon`  
`class FCookArtifactReaderCommon : public UE::Cook::ICookArtifactReader`  
_L12-23_
- inherits: `UE::Cook::ICookArtifactReader`
- L16 _public prototype_ `virtual ~FCookArtifactReaderCommon() = default;`
- L19 _public prototype_ `FArchive* CreateFileReader(const TCHAR* Filename) override;` — Utilities
- L20 _public prototype_ `bool IterateDirectoryRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L21 _public prototype_ `void FindFiles(TArray<FString>& Result, const TCHAR* Filename, bool Files, bool Directories) override;`
- L22 _public prototype_ `void FindFiles(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension = nullptr) override;`

### `Source/Developer/IoStoreUtilities/Public/IoStoreUtilities.h` (Public)


#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API IOSTOREUTILITIES_API`
- L22 _prototype_ `int32 CreateIoStoreContainerFiles(const TCHAR* CmdLine);`
- L24 _prototype_ `bool DumpIoStoreContainerInfo(const TCHAR* InContainerFilename, const FKeyChain& InKeyChain);`
- L26 _prototype_ `bool LegacyListIoStoreContainer( const TCHAR* InContainerFilename, int64 InSizeFilter, const FString& InCSVFilename, const FKeyChain& InKeyChain);`
- L32 _prototype_ `bool ListIoStoreContainer(const TCHAR* CmdLine);`
- L33 _prototype_ `bool ListIoStoreContainerBulkData(const TCHAR* CmdLine);`
- L34 _prototype_ `bool ListIoStoreContainerMetadataFile(const TCHAR* CmdLine);`
- L36 _prototype_ `bool DiffIoStoreContainer(const TCHAR* CmdLine);`
- L37 _prototype_ `bool LegacyDiffIoStoreContainers( const TCHAR* InContainerFilename1, const TCHAR* InContainerFilename2, bool bInLogUniques1, bool bInLogUniques2, const FKeyChain& InKeyChain1, const FKeyChain* InKeyChain2 = nullptr);`
- L45 _prototype_ `bool ExtractFilesFromIoStoreContainer( const TCHAR* InContainerFilename, const TCHAR* InDestPath, const FKeyChain& InKeyChain, const FString* InFilter, TMap<FString, uint64>* OutOrderMap, TArray<FGuid>* OutUsedEncryptionKeys, bool* bOutIsSigned);`
- L54 _prototype_ `bool ProcessFilesFromIoStoreContainer( const TCHAR* InContainerFilename, const TCHAR* InDestPath, const FKeyChain& InKeyChain, const FString* InFilter, TFunction<bool (const FString&, const FString&, const FIoChunkId&, const uint8*, uint64)> FileProcessFunc, TMap<FString, uint64>* OutOrderMap, TArray<FGuid>* OutUsedEncryptionKeys, bool* bOutIsSigned, int32 MaxConcurrentReaders);`
- L65 _prototype_ `bool SignIoStoreContainer(const TCHAR* InContainerFilename, const FRSAKeyHandle InSigningKey);`

### `Source/Developer/IoStoreUtilities/Public/LayeredCookArtifactReader.h` (Public)


#### class `FLayeredCookArtifactReader`  
`class FLayeredCookArtifactReader : public FCookArtifactReaderCommon`  
_L9-34_
- inherits: `FCookArtifactReaderCommon`
- L13 _public prototype_ `FLayeredCookArtifactReader() = default;`
- L15 _public function_ `void Initialize(bool bCleanBuild) override`
- L23 _public prototype_ `void AddLayer(TSharedRef<UE::Cook::ICookArtifactReader> InLayer);`
- L24 _public prototype_ `bool RemoveLayer(TSharedRef<UE::Cook::ICookArtifactReader> InLayer);`
- L25 _public prototype_ `void EmptyLayers();`
- L27 _public prototype_ `bool FileExists(const TCHAR* Filename) override;`
- L28 _public prototype_ `int64 FileSize(const TCHAR* Filename) override;`
- L29 _public prototype_ `IFileHandle* OpenRead(const TCHAR* Filename) override;`
- L31 _public prototype_ `bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L33 _private member_ `TArray<TSharedRef<UE::Cook::ICookArtifactReader>> Layers;`

### `Source/Developer/IoStoreUtilities/Public/LooseFilesCookArtifactReader.h` (Public)


#### class `FLooseFilesCookArtifactReader`  
`class FLooseFilesCookArtifactReader : public FCookArtifactReaderCommon`  
_L7-18_
- inherits: `FCookArtifactReaderCommon`
- L11 _public prototype_ `FLooseFilesCookArtifactReader() = default;`
- L13 _public prototype_ `bool FileExists(const TCHAR* Filename) override;`
- L14 _public prototype_ `int64 FileSize(const TCHAR* Filename) override;`
- L15 _public prototype_ `IFileHandle* OpenRead(const TCHAR* Filename) override;`
- L17 _public prototype_ `bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`

### `Source/Developer/IoStoreUtilities/Public/PackageStoreWriter.h` (Public)


#### class `IPackageStoreWriter`  
`class IPackageStoreWriter : public FBaseCookedPackageWriter`  
_L10-84_
- inherits: `FBaseCookedPackageWriter`
- L14 _public function_ `virtual IPackageStoreWriter* AsPackageStoreWriter() override` — Identify as a member of this interface from the ICookedPackageWriter api.
- L20 _public function_ `virtual FZenStoreWriter* AsZenStoreWriter()` — Downcast function for IPackageStoreWriter that is of class FZenStoreWriter.
- L41 _public prototype_ `virtual void GetEntries(TFunction<void(TArrayView<const FPackageStoreEntryResource>, TArrayView<const FOplogCookInfo>)>&&) = 0;` — Returns all cooked package store entries.
- L49 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FEntryCreatedEvent, const FEntryCreatedEventArgs&);`
- L50 _public prototype_ `virtual FEntryCreatedEvent& OnEntryCreated() = 0;`
- L68 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FCommitEvent, const FCommitEventArgs&);` — Broadcasted after a package has been committed, i.e cooked.
- L69 _public prototype_ `virtual FCommitEvent& OnCommit() = 0;`
- L82 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FMarkUpToDateEvent, const FMarkUpToDateEventArgs&);` — Broadcasted after a set of packages have been found to be up to date.
- L83 _public prototype_ `virtual FMarkUpToDateEvent& OnMarkUpToDate() = 0;`

#### struct `IPackageStoreWriter::FOplogCookInfo`  
`struct FOplogCookInfo`  
_L25-36_
- L33 _public member_ `FName PackageName;`
- L34 _public member_ `TArray<FAttachment> Attachments;`
- L35 _public member_ `bool bUpToDate = false;`

#### struct `IPackageStoreWriter::FOplogCookInfo::FAttachment`  
`struct FAttachment`  
_L27-31_
- L29 _public member_ `const UTF8CHAR* Key;`
- L30 _public member_ `FIoHash Hash;`

#### struct `IPackageStoreWriter::FEntryCreatedEventArgs`  
`struct FEntryCreatedEventArgs`  
_L43-47_
- L45 _public member_ `FName PlatformName;`
- L46 _public member_ `const FPackageStoreEntryResource& Entry;`

#### struct `IPackageStoreWriter::FCommitEventArgs`  
`struct FCommitEventArgs`  
_L55-63_
- desc: Package commit event arguments
- L57 _public member_ `FName PlatformName;`
- L58 _public member_ `FName PackageName;`
- L59 _public member_ `int32 EntryIndex = INDEX_NONE;`
- L60 _public member_ `TArrayView<const FPackageStoreEntryResource> Entries;`
- L61 _public member_ `TArrayView<const FOplogCookInfo> CookInfos;`
- L62 _public member_ `TArray<FAdditionalFileInfo> AdditionalFiles;`

#### struct `IPackageStoreWriter::FMarkUpToDateEventArgs`  
`struct FMarkUpToDateEventArgs`  
_L71-78_
- L73 _public member_ `FName PlatformName;`
- L74 _public member_ `TArray<int32> PackageIndexes;`
- L75 _public member_ `TArrayView<const FPackageStoreEntryResource> Entries;`
- L76 _public member_ `TArrayView<const FOplogCookInfo> CookInfos;`
- L77 _public member_ `TArray<FAdditionalFileInfo> AdditionalFiles;`

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FEntryCreatedEvent, const FEntryCreatedEventArgs&);`
- L68 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FCommitEvent, const FCommitEventArgs&);` — Broadcasted after a package has been committed, i.e cooked.
- L82 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FMarkUpToDateEvent, const FMarkUpToDateEventArgs&);` — Broadcasted after a set of packages have been found to be up to date.

### `Source/Developer/IoStoreUtilities/Public/ZenCookArtifactReader.h` (Public)


#### class `FZenCookArtifactReader`  
`class FZenCookArtifactReader : public FCookArtifactReaderCommon`  
_L13-37_
- inherits: `FCookArtifactReaderCommon`
- L17 _public prototype_ `FZenCookArtifactReader(const FString& InputPath, const FString& MetadataDirectoryPath, const ITargetPlatform* TargetPlatform);`
- L20 _public prototype_ `virtual ~FZenCookArtifactReader();`
- L21 _public prototype_ `void InitializeConnection();`
- L22 _public prototype_ `void Initialize(bool bCleanBuild) override;`
- L24 _public prototype_ `bool FileExists(const TCHAR* Filename) override;`
- L25 _public prototype_ `int64 FileSize(const TCHAR* Filename) override;`
- L26 _public prototype_ `IFileHandle* OpenRead(const TCHAR* Filename) override;`
- L28 _public prototype_ `bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L31 _private prototype_ `bool MakeStorageServerPath(const TCHAR* Filename, FString& OutFilename) const;`
- L33 _private member_ `TUniquePtr<UE::Zen::FScopeZenService> ScopeZenService;`
- L34 _private member_ `FString ZenRootPath;`
- L35 _private member_ `TUniquePtr<IStorageServerPlatformFile> StorageServerPlatformFile;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Developer/IoStoreUtilities/Public/ZenStoreWriter.h` (Public)


#### class `FZenStoreWriter`  
`class FZenStoreWriter : public IPackageStoreWriter`  
_L55-308_
- inherits: `IPackageStoreWriter`
- desc: A PackageStoreWriter that saves cooked packages for use by IoStore, and stores them in the Zen storage service.
- L59 _public prototype_ `FZenStoreWriter( const FString& OutputPath, const FString& MetadataDirectoryPath, const ITargetPlatform* TargetPlatform, TSharedRef<UE::Cook::ICookArtifactReader> CookArtifactReader);`
- L64 _public prototype_ `~FZenStoreWriter();`
- L66 _public prototype_ `static bool CanUse();`
- L69 _public function_ `virtual FZenStoreWriter* AsZenStoreWriter() override` — Identify as a implmenter of this class from the IPackageStoreWriter api.
- L74 _public prototype_ `virtual void SetCooker(UE::PackageWriter::Private::ICookerInterface* CookerInterface) override;`
- L77 _public typedef_ `FDeprecatedBeginCacheCallback;`
- L80 _public typedef_ `FDeprecatedRegisterDeterminismHelperCallback;`
- L82 _public function_ `void SetBeginCacheCallback(FDeprecatedBeginCacheCallback&&)` — `UE_DEPRECATED(5.7, "Use SetCooker instead")`
- L86 _public function_ `void SetRegisterDeterminismHelperCallback(FDeprecatedRegisterDeterminismHelperCallback&&)` — `UE_DEPRECATED(5.7, "Use SetCooker instead")`
- L98 _public function_ `virtual FCapabilities GetCapabilities() const override`
- L105 _public function_ `virtual FCookCapabilities GetCookCapabilities() const override`
- L115 _public prototype_ `ZenHostInfo GetHostInfo() const;`
- L117 _public prototype_ `virtual void BeginPackage(const FBeginPackageInfo& Info) override;`
- L118 _public prototype_ `virtual void CommitPackage(FCommitPackageInfo&& Info) override;`
- L120 _public prototype_ `virtual void WritePackageData(const FPackageInfo& Info, FLargeMemoryWriter& ExportsArchive, const TArray<FFileRegion>& FileRegions) override;`
- L121 _public prototype_ `virtual void WriteAdditionalFile(const FAdditionalFileInfo& Info, const FIoBuffer& FileData) override;`
- L122 _public prototype_ `virtual void WriteLinkerAdditionalData(const FLinkerAdditionalDataInfo& Info, const FIoBuffer& Data, const TArray<FFileRegion>& FileRegions) override;`
- L123 _public prototype_ `virtual void WritePackageTrailer(const FPackageTrailerInfo& Info, const FIoBuffer& Data) override;`
- L126 _public prototype_ `virtual void WriteBulkData(const FBulkDataInfo& Info, const FIoBuffer& BulkData, const TArray<FFileRegion>& FileRegions) override;`
- L127 _public prototype_ `virtual void RegisterDeterminismHelper(UObject* SourceObject, const TRefCountPtr<UE::Cook::IDeterminismHelper>& DeterminismHelper) override;`
- L130 _public prototype_ `void InitializeConnection();`
- L131 _public prototype_ `virtual void Initialize(const FCookInfo& Info) override;`
- L132 _public prototype_ `virtual void BeginCook(const FCookInfo& Info) override;`
- L133 _public prototype_ `virtual void EndCook(const FCookInfo& Info) override;`
- L135 _public prototype_ `virtual void GetEntries(TFunction<void(TArrayView<const FPackageStoreEntryResource>, TArrayView<const FOplogCookInfo>)>&& Callback) override;`
- L137 _public prototype_ `DECLARE_DERIVED_EVENT(FZenStoreWriter, IPackageStoreWriter::FEntryCreatedEvent, FEntryCreatedEvent);`
- L138 _public function_ `virtual FEntryCreatedEvent& OnEntryCreated() override`
- L142 _public prototype_ `DECLARE_DERIVED_EVENT(FZenStoreWriter, IPackageStoreWriter::FCommitEvent, FCommitEvent);`
- L143 _public function_ `virtual FCommitEvent& OnCommit() override`
- L147 _public prototype_ `DECLARE_DERIVED_EVENT(FZenStoreWriter, IPackageStoreWriter::FMarkUpToDateEvent, FMarkUpToDateEvent);`
- L148 _public function_ `virtual FMarkUpToDateEvent& OnMarkUpToDate() override`
- L153 _public prototype_ `void WriteIoStorePackageData(const FPackageInfo& Info, const FIoBuffer& PackageData, const FPackageStoreEntryResource& PackageStoreEntry, const TArray<FFileRegion>& FileRegions);`
- L155 _public prototype_ `virtual void PopulateOplog(const FAssetRegistryState& PreviousState, int32& OutNumPackagesInOplog) override;`
- L157 _public prototype_ `virtual void UpdateLastReferenceDateAndPruneStaleOps( UE::Cook::Artifact::FUpdateOplogPackagesContext& OplogContext) override;`
- L159 _public prototype_ `virtual TArray<FName> GetOplogPackageNames() override;`
- L160 _public prototype_ `virtual FCbObject GetOplogAttachment(FName PackageName, FUtf8StringView AttachmentKey) override;`
- L161 _public prototype_ `virtual void GetOplogAttachments(TArrayView<FName> PackageNames, TArrayView<FUtf8StringView> AttachmentKeys, TUniqueFunction<void(FName PackageName, FUtf8StringView AttachmentKey, FCbObject&& Attachment)>&& Callback) override;`
- L164 _public prototype_ `virtual void GetBaseGameOplogAttachments(TArrayView<FName> PackageNames, TArrayView<FUtf8StringView> AttachmentKeys, TUniqueFunction<void(FName PackageName, FUtf8StringView AttachmentKey, FCbObject&& Attachment)>&& Callback) override;`
- L167 _public prototype_ `virtual ECommitStatus GetCommitStatus(FName PackageName) override;`
- L169 _public prototype_ `virtual void RemoveCookedPackages(TArrayView<const FName> PackageNamesToRemove) override;`
- L170 _public prototype_ `virtual void RemoveCookedPackages() override;`
- L171 _public prototype_ `virtual void UpdatePackageModifiedStatus(FUpdatePackageModifiedStatusContext& Context) override;`
- L172 _public prototype_ `bool GetPreviousCookedBytes(const FPackageInfo& Info, FPreviousCookedBytesData& OutData) override;`
- L173 _public prototype_ `void CompleteExportsArchiveForDiff(FPackageInfo& Info, FLargeMemoryWriter& ExportsArchive) override;`
- L174 _public prototype_ `virtual EPackageWriterResult BeginCacheForCookedPlatformData(FBeginCacheForCookedPlatformDataInfo& Info) override;`
- L175 _public prototype_ `virtual TFuture<FCbObject> WriteMPCookMessageForPackage(FName PackageName) override;`
- L176 _public prototype_ `virtual bool TryReadMPCookMessageForPackage(FName PackageName, FCbObjectView Message) override;`
- L177 _public prototype_ `virtual void AppendOp(FName KeyName, FCbObject Payload) override;`
- L179 _public function_ `virtual TMap<FName, TRefCountPtr<FPackageHashes>>& GetPackageHashes() override`
- L230 _private function_ `FPendingPackageState& GetPendingPackage(const FName& PackageName)`
- L238 _private prototype_ `FPendingPackageState& AddPendingPackage(const FName& PackageName);`
- L240 _private function_ `TUniquePtr<FPendingPackageState> RemovePendingPackage(const FName& PackageName)`
- L246 _private prototype_ `FCbPackage CreateReferencedSetOpPackage();`
- L247 _private prototype_ `FCbPackage CreateProjectMetaDataOpPackage(const ANSICHAR* MetadataOplogKeyName);`
- L248 _private prototype_ `void CreateProjectMetaData(FCbPackage& Pkg, FCbWriter& PackageObj);`
- L249 _private prototype_ `void WriteManifestEntryToPackageWriter(FCbPackage& Pkg, FCbWriter& PackageObj, const FZenFileSystemManifestEntry& Entry) const;`
- L251 _private prototype_ `void BroadcastCommit(IPackageStoreWriter::FCommitEventArgs& EventArgs);`
- L252 _private prototype_ `void BroadcastMarkUpToDate(IPackageStoreWriter::FMarkUpToDateEventArgs& EventArgs);`
- L255 _private prototype_ `void CommitPackageInternal(FZenCommitInfo&& CommitInfo);`
- L256 _private prototype_ `FCbAttachment CreateAttachment(FSharedBuffer Buffer) const;`
- L257 _private prototype_ `FCbAttachment CreateAttachment(FIoBuffer Buffer) const;`
- L258 _private prototype_ `FString GetProjectStorePath() const;`
- L259 _private prototype_ `void WriteProjectStoreFile();`
- L261 _private member_ `FCriticalSection PackagesCriticalSection;`
- L262 _private member_ `TMap<FName, TUniquePtr<FPendingPackageState>> PendingPackages;`
- L263 _private member_ `TUniquePtr<UE::FZenStoreHttpClient> HttpClient;`
- L264 _private member_ `bool IsLocalConnection = true;`
- L266 _private member_ `TSharedRef<UE::Cook::ICookArtifactReader> CookArtifactReader;`
- L267 _private member_ `const ITargetPlatform& TargetPlatform;`
- L268 _private member_ `const FName TargetPlatformFName;`
- L269 _private member_ `FString ProjectId;`
- L270 _private member_ `FString ParentProjectId;`
- L271 _private member_ `FString OplogId;`
- L272 _private member_ `FString OutputPath;`
- L273 _private member_ `FString MetadataDirectoryPath;`
- L274 _private member_ `TMap<FName, TRefCountPtr<FPackageHashes>> AllPackageHashes;`
- L276 _private member_ `TUniquePtr<FPackageStoreOptimizer> PackageStoreOptimizer;`
- L278 _private member_ `FRWLock EntriesLock;`
- L279 _private member_ `TArray<FPackageStoreEntryResource> PackageStoreEntries;`
- L280 _private member_ `TArray<FOplogCookInfo> CookedPackagesInfo;`
- L281 _private member_ `TMap<FName, int32> PackageNameToIndex;`
- L283 _private member_ `UE::FMutex ZenFileSystemManifestMutex;`
- L284 _private member_ `TUniquePtr<FZenFileSystemManifest> ZenFileSystemManifest;`
- L285 _private member_ `TMap<FName, TArray<FString>> PackageAdditionalFiles;`
- L287 _private member_ `UE::PackageWriter::Private::ICookerInterface* Cooker = nullptr;`
- L289 _private member_ `std::atomic<int32> NumCommitPending;`
- L290 _private member_ `UE::FEventCount CommitPendingEvent;`
- L291 _private member_ `FEntryCreatedEvent EntryCreatedEvent;`
- L292 _private member_ `FCriticalSection CommitEventCriticalSection;`
- L293 _private member_ `FCommitEvent CommitEvent;`
- L294 _private member_ `FMarkUpToDateEvent MarkUpToDateEvent;`
- L296 _private member_ `ICookedPackageWriter::FCookInfo::ECookMode CookMode;`
- L298 _private member_ `FOodleDataCompression::ECompressor Compressor;`
- L299 _private member_ `FOodleDataCompression::ECompressionLevel CompressionLevel;`
- L301 _private member_ `bool bInitialized;`
- L302 _private member_ `bool bInitializedConnection;`
- L303 _private member_ `bool bProvidePerPackageResults;`
- L305 _private prototype_ `static void StaticInit();`
- L306 _private prototype_ `static bool IsReservedOplogKey(FUtf8StringView Key);`
- L307 _private member_ `static TArray<const UTF8CHAR*> ReservedOplogKeys;`

#### struct `FZenStoreWriter::ZenHostInfo`  
`struct ZenHostInfo`  
_L90-96_
- L92 _public member_ `FString ProjectId;`
- L93 _public member_ `FString OplogId;`
- L94 _public member_ `FString HostName;`
- L95 _public member_ `uint16 HostPort;`

#### struct `FZenStoreWriter::FBulkDataEntry`  
`struct FBulkDataEntry`  
_L185-192_
- L187 _public member_ `UE::Tasks::TTask<FCompressedBuffer> CompressedPayload;`
- L188 _public member_ `FBulkDataInfo Info;`
- L189 _public member_ `FCbObjectId ChunkId;`
- L190 _public member_ `TArray<FFileRegion> FileRegions;`
- L191 _public member_ `bool IsValid = false;`

#### struct `FZenStoreWriter::FPackageDataEntry`  
`struct FPackageDataEntry`  
_L194-204_
- L196 _public prototype_ `~FPackageDataEntry();`
- L198 _public member_ `UE::Tasks::TTask<FCompressedBuffer> CompressedPayload;`
- L199 _public member_ `FPackageInfo Info;`
- L200 _public member_ `FCbObjectId ChunkId;`
- L201 _public member_ `TUniquePtr<FPackageStorePackage> OptimizedPackage;`
- L202 _public member_ `TArray<FFileRegion> FileRegions;`
- L203 _public member_ `bool IsValid = false;`

#### struct `FZenStoreWriter::FFileDataEntry`  
`struct FFileDataEntry`  
_L206-212_
- L208 _public member_ `UE::Tasks::TTask<FCompressedBuffer> CompressedPayload;`
- L209 _public member_ `FAdditionalFileInfo Info;`
- L210 _public member_ `FString ZenManifestServerPath;`
- L211 _public member_ `FString ZenManifestClientPath;`

#### struct `FZenStoreWriter::FPendingPackageState`  
`struct FPendingPackageState`  
_L214-228_
- L216 _public prototype_ `~FPendingPackageState();`
- L218 _public member_ `FName PackageName;`
- L219 _public member_ `TArray<FPackageDataEntry> PackageData;`
- L220 _public member_ `TArray<FBulkDataEntry> BulkData;`
- L221 _public member_ `TArray<FFileDataEntry> FileData;`
- L222 _public member_ `TRefCountPtr<FPackageHashes> PackageHashes;`
- L223 _public member_ `TUniquePtr<TPromise<int>> PackageHashesCompletionPromise;`
- L226 _public member_ `uint64 OriginalHeaderSize = 0;` — Solely for use in DiffOnly mode
- L227 _public member_ `TUniquePtr<FPackageStorePackage> PreOptimizedPackage;`

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace UE`
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Cook` (scope `UE`)
- L137 _delegate_ `DECLARE_DERIVED_EVENT(FZenStoreWriter, IPackageStoreWriter::FEntryCreatedEvent, FEntryCreatedEvent);`
- L142 _delegate_ `DECLARE_DERIVED_EVENT(FZenStoreWriter, IPackageStoreWriter::FCommitEvent, FCommitEvent);`
- L147 _delegate_ `DECLARE_DERIVED_EVENT(FZenStoreWriter, IPackageStoreWriter::FMarkUpToDateEvent, FMarkUpToDateEvent);`
