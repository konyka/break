# Programs / IoStoreDependencyViewer

- module root: `Source/Programs/IoStoreDependencyViewer`
- headers: 8; symbols: 500
- symbol kinds: class=9, delegate=2, enum=2, enumerator=5, function=49, member=209, namespace=1, prototype=214, struct=9
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DesktopPlatform, HTTP, InputCore, IoStoreOnDemand, IoStoreOnDemandUtilities, Json, JsonUtilities, PakFile, Projects, RSA, Slate, SlateCore, StandaloneRenderer

### `Source/Programs/IoStoreDependencyViewer/Private/IoStoreConfigHelpers.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace IoStoreConfig`
- L22 _prototype_ `bool FindZenExePath(FString& OutPath);` (scope `IoStoreConfig`) — Find zen.exe path with fallback search: 1. Config setting (Engine.ini [IoStoreDependencyViewer] ZenExePath) 2. Application directory 3. Project directory (if -projectdir= specified) @param OutPath - Resolved path (may not exist - use ValidateZenExe to check) @return true if a path was resolved (not validated for existence)
- L34 _prototype_ `bool FindOidcTokenExePath(FString& OutPath, const FString& ZenExePath = FString());` (scope `IoStoreConfig`) — Find OidcToken.exe path with fallback search: 1. Config setting (Engine.ini [IoStoreDependencyViewer] OidcTokenExePath) 2. ../DotNET/OidcToken/win-x64/OidcToken.exe (relative to app directory) 3. Project directory (if -projectdir= specified) 4. Same directory as zen.exe (if provided) @param OutPath - Resolved path (may not exist) @param ZenExePath - Optional zen.exe path to check alongside (for fallback #4) @return true if a path was resolved
- L42 _prototype_ `bool ValidateZenExe(const FString& ZenExePath, bool bShowDialog = true);` (scope `IoStoreConfig`) — Validate that zen.exe exists and optionally show error dialog if missing @param ZenExePath - Path to validate @param bShowDialog - Show error dialog to user (default true) @return true if zen.exe exists
- L50 _prototype_ `bool ValidateOidcTokenExe(const FString& OidcExePath, bool bShowWarning = true);` (scope `IoStoreConfig`) — Validate that OidcToken.exe exists (warning only - not fatal) @param OidcExePath - Path to validate @param bShowWarning - Show warning if missing (default true) @return true if OidcToken.exe exists
- L62 _prototype_ `FString EscapeCommandLineArgument(const FString& Argument);` (scope `IoStoreConfig`) — Escapes a string for safe use as a command-line argument value on Windows. Implements proper Windows/CRT CommandLineToArgvW escaping rules: - Sequences of backslashes before quotes must be doubled, then the quote escaped - Trailing backslashes (before closing quote) must be doubled - Other backslashes are literal This prevents argument injection via embedded quotes. @param Argument - The string to escape @return Escaped string safe for use in command-line arguments
- L74 _prototype_ `bool TryLoadCryptoJsonFromSearchPaths(const TMap<FString, FString>& TemplateVars, const FString& DownloadDirectory);` (scope `IoStoreConfig`) — Try to load crypto.json from configured search paths. Reads path templates from Engine.ini [IoStoreDependencyViewer] +CryptoJsonSearchPath entries. Templates are expanded using provided variables (e.g., <buildname>, <branchname>, <cl>, <platform>). Example template: "\\epicgames.net\Root\Builds\Fortnite\++Fortnite+<branchname>-CL-<cl>\<platform>\Metadata\crypto.json" @param TemplateVars - Map of variable names to values for template substitution (e.g., "buildname" -> "Fortnite-Main-CL-123") @param DownloadDirectory - Local directory to copy crypto.json into (under <Platform>/Metadata/) @return true if crypto.json was found and copied successfully
- L82 _prototype_ `FString ParseBranchFromBuildName(const FString& BuildName);` (scope `IoStoreConfig`) — Parse branch name from a cloud build name. Examples: "Fortnite-Main-CL-123" → "Main", "Fortnite-Release-40.20-CL-456" → "Release-40.20" @param BuildName - Cloud build name @return Branch name, or full BuildName if parsing fails
- L90 _prototype_ `FString ParseChangelistFromBuildName(const FString& BuildName);` (scope `IoStoreConfig`) — Parse changelist number from a cloud build name. Examples: "Fortnite-Main-CL-12345" → "12345", "Fortnite-Release-40.20-CL-456789" → "456789" @param BuildName - Cloud build name @return Changelist number string, or empty string if not found
- L99 _prototype_ `bool LoadEncryptionKeysFromDirectory(const FString& DirectoryPath, TMap<FGuid, FAES::FAESKey>& OutKeys);` (scope `IoStoreConfig`) — Load encryption keys from crypto.json files in a directory. Searches all platform subdirectories (e.g., Windows/Metadata/crypto.json) and merges keys. @param DirectoryPath - Root directory containing platform subdirectories @param OutKeys - Map of encryption keys (Guid -> AES key) @return true if any crypto.json files were found and loaded

### `Source/Programs/IoStoreDependencyViewer/Private/IoStoreDependencyViewer.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIoStoreDependencyViewer, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIoStoreDependencyViewer, Log, All);`
- L11 _prototype_ `void TestOnDemandTocLoading(const FString& DirectoryPath);` — Test function for verifying .uondemandtoc loading
- L14 _prototype_ `void TestCloudDownload(const FString& DownloadPath);` — Test function for verifying cloud download
- L17 _prototype_ `void TestCloudDownloadSpecific(const FString& Namespace, const FString& Bucket, const FString& BuildId, const FString& DownloadPath);` — Test function for downloading specific build from cloud
- L20 _prototype_ `void TestTocToCSVFromCommandLine();` — Test function for exporting TOC assets to CSV
- L23 _prototype_ `bool RunTestBaselineUcas();` — Baseline test: Downloads full .utoc + .ucas files and exports asset data to CSV
- L26 _prototype_ `bool RunTestCloudPartialDownloadUCas();` — Cloud partial download test: Downloads only metadata, uses on-demand fetching, exports to CSV
- L29 _prototype_ `bool RunTestZenReaderIntegration();` — Zen Reader Integration test: Downloads metadata, uses FIoStoreReaderZenBuild, exports to CSV
- L32 _prototype_ `void TestPartialDownload();` — Test function for partial download functionality

### `Source/Programs/IoStoreDependencyViewer/Private/IoStoreReaderAdapter.h` (Private)


#### class `FIoStoreReaderAdapter`  
`class FIoStoreReaderAdapter`  
_L13-121_
- desc: Adapter that wraps either a standard FIoStoreReader or a FIoStoreReaderZenBuild Provides a unified interface for both types
- L23 _public function_ `explicit FIoStoreReaderAdapter(TUniquePtr<FIoStoreReader> InStandardReader) : StandardReader(MoveTemp(InStandardReader)) , ReaderType(EReaderType::Standard)` — Construct with standard reader
- L30 _public function_ `explicit FIoStoreReaderAdapter(TUniquePtr<FIoStoreReaderZenBuild> InZenReader) : ZenReader(MoveTemp(InZenReader)) , ReaderType(EReaderType::ZenBuild)` — Construct with zen build reader
- L37 _public function_ `FIoContainerId GetContainerId() const` — IoStore interface - delegates to the appropriate reader
- L44 _public function_ `uint32 GetVersion() const`
- L51 _public function_ `EIoContainerFlags GetContainerFlags() const`
- L58 _public function_ `FGuid GetEncryptionKeyGuid() const`
- L65 _public function_ `FString GetContainerName() const`
- L72 _public function_ `int32 GetChunkCount() const`
- L79 _public function_ `void EnumerateChunks(TFunction<bool(FIoStoreTocChunkInfo&&)>&& Callback) const`
- L91 _public function_ `TIoStatusOr<FIoStoreTocChunkInfo> GetChunkInfo(const FIoChunkId& ChunkId) const`
- L98 _public function_ `TIoStatusOr<FIoStoreTocChunkInfo> GetChunkInfo(const uint32 TocEntryIndex) const`
- L106 _public function_ `TIoStatusOr<FIoBuffer> Read(const FIoChunkId& Chunk, const FIoReadOptions& Options) const` — Read method - delegates to the appropriate reader
- L113 _public function_ `EReaderType GetReaderType() const`
- L114 _public function_ `FIoStoreReader* GetStandardReader() const`
- L115 _public function_ `FIoStoreReaderZenBuild* GetZenReader() const`
- L118 _private member_ `TUniquePtr<FIoStoreReader> StandardReader;`
- L119 _private member_ `TUniquePtr<FIoStoreReaderZenBuild> ZenReader;`
- L120 _private member_ `EReaderType ReaderType;`

#### enum `FIoStoreReaderAdapter::EReaderType`  
`enum class EReaderType`  
_L16-20_
- L18 _public enumerator_ `Standard` — File-based FIoStoreReader
- L19 _public enumerator_ `ZenBuild` — Cloud-based FIoStoreReaderZenBuild

### `Source/Programs/IoStoreDependencyViewer/Private/IoStoreReaderZenBuild.h` (Private)


#### class `FIoStoreReaderZenBuild`  
`class FIoStoreReaderZenBuild`  
_L25-164_
- desc: IoStore reader that fetches UCAS data on-demand from zen cloud builds instead of reading from local disk files.
- L30 _public prototype_ `FIoStoreReaderZenBuild();`
- L31 _public prototype_ `~FIoStoreReaderZenBuild();`
- L46 _public prototype_ `FIoStatus Initialize( FStringView InContainerPath, const TMap<FGuid, FAES::FAESKey>& InDecryptionKeys, const FString& InZenExePath, const FString& InOidcExePath, const FString& InNamespace, const FString& InBucketId, const FString& InBuildId, const FString& InProxyUrl, const FString& InBaseDownloadDirectory, const FString& InPartCacheDirectory);` — Initialize the reader with zen connection parameters @param InContainerPath Container path WITHOUT the .utoc extension (e.g., "D:/Builds/pakchunk0-WindowsClient") @param InDecryptionKeys Decryption keys for encrypted containers @param InZenExePath Path to zen.exe @param InOidcExePath Path to OidcToken.exe @param InNamespace Cloud namespace @param InBucketId Cloud bucket @param InBuildId Cloud build ID @param InProxyUrl Optional proxy URL @param InBaseDownloadDirectory Base directory where the build was downloaded @param InPartCacheDirectory Directory for caching .part files (unique per container)
- L59 _public prototype_ `FIoContainerId GetContainerId() const;` — IoStore interface methods
- L60 _public prototype_ `uint32 GetVersion() const;`
- L61 _public prototype_ `EIoContainerFlags GetContainerFlags() const;`
- L62 _public prototype_ `FGuid GetEncryptionKeyGuid() const;`
- L63 _public prototype_ `FString GetContainerName() const;`
- L64 _public prototype_ `int32 GetChunkCount() const;`
- L65 _public prototype_ `void EnumerateChunks(TFunction<bool(FIoStoreTocChunkInfo&&)>&& Callback) const;`
- L66 _public prototype_ `TIoStatusOr<FIoStoreTocChunkInfo> GetChunkInfo(const FIoChunkId& ChunkId) const;`
- L67 _public prototype_ `TIoStatusOr<FIoStoreTocChunkInfo> GetChunkInfo(const uint32 TocEntryIndex) const;`
- L73 _public prototype_ `TIoStatusOr<FIoBuffer> Read(const FIoChunkId& Chunk, const FIoReadOptions& Options) const;` — Read a chunk from the container (synchronous). This will download the required ranges from zen and decompress/decrypt as needed.
- L80 _public prototype_ `UE::Tasks::FTask StartAsyncRead( int32 InPartitionIndex, int64 InPartitionOffset, int64 InReadAmount, uint8* OutBuffer, std::atomic_bool* OutSuccess) const;` — Start an async read from the container. This will download the requested range from zen if not already cached, then copy the data into the output buffer.
- L91 _public prototype_ `void ClearCache();` — Clear the downloaded chunks cache to free memory. Should be called after loading completes to release memory used during downloads.
- L108 _private prototype_ `void FetchThread();` — Background thread methods
- L109 _private prototype_ `void WaitForConcurrencySlot() const;`
- L110 _private prototype_ `void PollInFlightProcesses() const;`
- L111 _private prototype_ `void WaitForAllInFlightDownloads() const;`
- L114 _private prototype_ `bool FetchRangeAsync(int32 PartitionIndex, uint64 Offset, uint64 Length, TArray64<uint8>& OutData) const;` — Async fetch methods
- L117 _private prototype_ `void ExecuteFetchBatchAsync(TArray<TSharedPtr<FZenChunkFetchRequest>>& Batch) const;` — Batch execution methods
- L118 _private prototype_ `void LaunchZenCommandAsync(int32 PartitionIndex, const TArray<TSharedPtr<FZenChunkFetchRequest>>& Requests) const;`
- L119 _private prototype_ `void PollZenCompletion(FProcHandle ProcHandle, TArray<TSharedPtr<FZenChunkFetchRequest>> Requests, FString BatchDirectory, FString ManifestPath, void* ReadPipe, int32 BatchId, int32 PartitionIndex) const;`
- L120 _private prototype_ `void ProcessBatchSuccess(const TArray<TSharedPtr<FZenChunkFetchRequest>>& Requests, const FString& BatchDirectory) const;`
- L121 _private prototype_ `void SignalBatchFailure(const TArray<TSharedPtr<FZenChunkFetchRequest>>& Requests) const;`
- L122 _private prototype_ `FString GenerateBatchManifest(int32 PartitionIndex, const TArray<TSharedPtr<FZenChunkFetchRequest>>& Requests) const;`
- L126 _private member_ `TUniquePtr<IIoStoreTocReader> TocReader;` — TOC reader for chunk metadata
- L129 _private member_ `FString ContainerPath;` — Container base path (without .utoc extension)
- L132 _private member_ `FString ZenExePath;` — Zen connection parameters
- L133 _private member_ `FString OidcExePath;`
- L134 _private member_ `FString Namespace;`
- L135 _private member_ `FString BucketId;`
- L136 _private member_ `FString BuildId;`
- L137 _private member_ `FString ProxyUrl;`
- L140 _private member_ `FString BaseDownloadDirectory;` — Base directory where the build was downloaded (for calculating relative paths)
- L143 _private member_ `FString PartCacheDirectory;` — Directory for caching .part files (unique per container)
- L146 _private member_ `FAES::FAESKey DecryptionKey;` — Decryption key for encrypted containers
- L149 _private member_ `mutable FCriticalSection AvailabilityCacheMutex;` — Async batching infrastructure - three separate mutexes for fine-grained concurrency
- L150 _private member_ `mutable FCriticalSection RequestQueueMutex;` — Protects PendingRequests queue
- L151 _private member_ `mutable FCriticalSection InFlightMutex;` — Protects InFlightProcesses
- L154 _private member_ `FEvent* WakeEvent = nullptr;` — Thread coordination
- L155 _private member_ `std::atomic<bool> bShuttingDown{false};` — Shutdown coordination flag
- L156 _private member_ `FRunnableThread* FetchThreadHandle = nullptr;` — Background fetch thread
- L157 _private member_ `FRunnable* FetchRunnable = nullptr;` — Runnable object (must be deleted manually)
- L160 _private member_ `mutable TMap<FString, TArray64<uint8>> DownloadedChunks;` — Data structures for async operation
- L161 _private member_ `mutable TArray<TSharedPtr<FZenChunkFetchRequest>> PendingRequests;` — Request queue
- L162 _private member_ `mutable TArray<FProcHandle> InFlightProcesses;` — Track concurrent zen.exe processes
- L163 _private member_ `int32 MaxConcurrentDownloads = 6;` — Tunable parallelism limit (4-8 recommended)

#### struct `FIoStoreReaderZenBuild::FZenChunkFetchRequest`  
`struct FZenChunkFetchRequest`  
_L95-105_
- desc: Request structure for async batching
- L97 _public member_ `int32 PartitionIndex = 0;` — Which .ucas partition
- L98 _public member_ `uint64 Offset = 0;` — Offset within partition
- L99 _public member_ `uint64 Length = 0;` — Bytes to fetch
- L100 _public member_ `FEvent* CompletionEvent = nullptr;` — Signal when complete (from pool)
- L101 _public member_ `TArray64<uint8>* OutDataPtr = nullptr;` — Where to write fetched data (MAY BE INVALID if bTimedOut=true)
- L102 _public member_ `std::atomic<bool> bCompleted{false};`
- L103 _public member_ `std::atomic<bool> bFailed{false};`
- L104 _public member_ `std::atomic<bool> bTimedOut{false};` — Set when caller gives up waiting - OutDataPtr becomes invalid

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogZenBuildReader, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogZenBuildReader, Log, All);`

### `Source/Programs/IoStoreDependencyViewer/Private/PartialDownloadPlatformFile.h` (Private)


#### struct `FBlockInfo`  
`struct FBlockInfo`  
_L23-30_
- desc: Information about a single compression block from a .utoc file
- L25 _public member_ `uint64 Offset;` — Absolute offset in .ucas partition(s)
- L26 _public member_ `uint32 CompressedSize;` — Size to read from disk
- L27 _public member_ `uint32 UncompressedSize;` — Size after decompression
- L28 _public member_ `uint32 PartitionIndex;` — Which .ucas partition file (0 for _s1, 1 for _s2, etc.)
- L29 _public member_ `uint8 CompressionMethodIndex;`

#### class `FIoStoreTocBlockMap`  
`class FIoStoreTocBlockMap`  
_L35-77_
- desc: Parses .utoc files and provides efficient byte-range to compression-block mapping
- L43 _public prototype_ `bool Initialize(const FString& TocFilePath);` — Load and parse a .utoc file @param TocFilePath Path to the .utoc file @return true if successfully parsed
- L51 _public prototype_ `void GetBlocksForRange(uint64 FileOffset, uint64 Length, TArray<int32>& OutBlockIndices) const;` — Given a byte range in the logical .ucas file, return which compression blocks are needed @param FileOffset Starting byte offset @param Length Number of bytes to read @param OutBlockIndices Indices of blocks that cover this range
- L56 _public prototype_ `const FBlockInfo* GetBlockInfo(int32 BlockIndex) const;` — Get information about a specific block
- L61 _public function_ `int32 GetBlockCount() const` — Get the total number of compression blocks
- L66 _public function_ `uint64 GetPartitionSize() const` — Get the partition size for this container (determines which .ucas file a block belongs to)
- L71 _public function_ `const FString& GetBaseName() const` — Get the base filename (without extension or partition suffix)
- L74 _private member_ `TArray<FBlockInfo> Blocks;`
- L75 _private member_ `uint64 PartitionSize = 0;`
- L76 _private member_ `FString BaseName;`

#### struct `FBlockFetchRequest`  
`struct FBlockFetchRequest`  
_L82-89_
- desc: Request for fetching compression blocks
- L84 _public member_ `FString UcasFilePath;` — Full path to the .ucas file
- L85 _public member_ `TArray<int32> BlockIndices;` — Which blocks to fetch
- L86 _public member_ `FEvent* CompletionEvent = nullptr;` — Event to signal when fetch completes
- L87 _public member_ `bool bCompleted = false;`
- L88 _public member_ `bool bFailed = false;`

#### class `FPartialDownloadCoordinator`  
`class FPartialDownloadCoordinator`  
_L94-229_
- desc: Coordinates on-demand downloading of compression blocks via zen.exe
- L99 _public prototype_ `FPartialDownloadCoordinator();`
- L100 _public prototype_ `~FPartialDownloadCoordinator();`
- L113 _public prototype_ `bool Initialize( const FString& InDownloadDirectory, const FString& InZenExePath, const FString& InOidcExePath, const FString& InNamespace, const FString& InBucketId, const FString& InBuildId, const FString& InProxyUrl);` — Initialize the coordinator @param InDownloadDirectory Where downloaded files are stored @param InZenExePath Path to zen.exe @param InOidcExePath Path to OidcToken.exe @param InNamespace Cloud namespace @param InBucketId Cloud bucket @param InBuildId Cloud build ID @param InProxyUrl Optional proxy URL @return true if initialization succeeded (including thread creation), false otherwise
- L127 _public prototype_ `void RegisterBlockMap(const FString& UcasBasePath, TSharedPtr<FIoStoreTocBlockMap> BlockMap);` — Register a TOC block map for a container @param UcasBasePath Base path to .ucas files (without _s1 suffix) @param BlockMap The parsed TOC block map
- L135 _public prototype_ `bool IsBlockAvailable(const FString& UcasFilePath, int32 BlockIndex) const;` — Check if a specific block is available locally @param UcasFilePath Path to the .ucas file @param BlockIndex Which block to check @return true if the block has been downloaded
- L143 _public prototype_ `bool FetchBlocks(const FString& UcasFilePath, const TArray<int32>& BlockIndices);` — Request blocks to be fetched. Blocks until the blocks are available or fetch fails. @param UcasFilePath Path to the .ucas file @param BlockIndices Which blocks to fetch @return true if blocks were successfully fetched
- L152 _public prototype_ `bool EnsureRangeAvailable(const FString& UcasFilePath, uint64 Offset, uint64 Length);` — Calculate which blocks are needed for a byte range and fetch any that are missing @param UcasFilePath Path to the .ucas file @param Offset Starting byte offset in the file @param Length Number of bytes to read @return true if all needed blocks are available
- L157 _public prototype_ `void Shutdown();` — Shutdown the coordinator and stop background tasks
- L162 _public function_ `bool IsShuttingDown() const` — Check if the coordinator is shutting down
- L179 _public prototype_ `void GetAvailablePartFiles(const FString& OriginalPath, TArray<FPartFileInfo>& OutPartFiles) const;` — Scan for available .part files for a given base path @param OriginalPath The original .ucas file path being requested @param OutPartFiles Array of available .part files with their ranges
- L185 _private prototype_ `void FetchThread();` — Background thread that batches and processes fetch requests
- L190 _private prototype_ `bool ExecuteFetchBatch(const TArray<TSharedPtr<FBlockFetchRequest>>& Requests);` — Execute a batch of fetch requests via zen.exe
- L195 _private prototype_ `FString GenerateManifest(const TArray<TSharedPtr<FBlockFetchRequest>>& Requests);` — Generate JSON manifest for zen.exe partial download
- L200 _private prototype_ `int32 RunZenCommand(const FString& Command, FString& OutResult);` — Run zen.exe with the given command
- L204 _private member_ `FString DownloadDirectory;` — Configuration
- L205 _private member_ `FString ZenExePath;`
- L206 _private member_ `FString OidcExePath;`
- L207 _private member_ `FString Namespace;`
- L208 _private member_ `FString BucketId;`
- L209 _private member_ `FString BuildId;`
- L210 _private member_ `FString ProxyUrl;`
- L213 _private member_ `mutable FCriticalSection BlockMapsMutex;` — Block maps for each container (keyed by base .ucas path)
- L214 _private member_ `TMap<FString, TSharedPtr<FIoStoreTocBlockMap>> BlockMaps;`
- L217 _private member_ `mutable FCriticalSection AvailabilityMutex;` — Availability tracking (keyed by "ucasfilepath:blockindex")
- L218 _private member_ `TSet<FString> AvailableBlocks;`
- L221 _private member_ `mutable FCriticalSection RequestQueueMutex;` — Fetch request queue
- L222 _private member_ `TArray<TSharedPtr<FBlockFetchRequest>> PendingRequests;`
- L225 _private member_ `FRunnableThread* FetchThreadHandle = nullptr;` — Background fetch thread
- L226 _private member_ `FRunnable* FetchRunnable = nullptr;` — Runnable object (must be deleted manually)
- L227 _private member_ `std::atomic<bool> bShuttingDown{false};`
- L228 _private member_ `FEvent* WakeEvent = nullptr;`

#### struct `FPartialDownloadCoordinator::FPartFileInfo`  
`struct FPartFileInfo`  
_L167-172_
- desc: Information about a downloaded .part file
- L169 _public member_ `FString FilePath;` — Full path to the .part file
- L170 _public member_ `uint64 StartOffset;` — Starting offset in the original file
- L171 _public member_ `uint64 Length;` — Length of data in this .part file

#### class `FPartialDownloadFileHandle`  
`class FPartialDownloadFileHandle : public IFileHandle`  
_L234-273_
- inherits: `IFileHandle`
- desc: Custom file handle that fetches compression blocks on-demand
- L237 _public prototype_ `FPartialDownloadFileHandle( IFileHandle* InRealHandle, const FString& InFilePath, TSharedPtr<FPartialDownloadCoordinator> InCoordinator, IPlatformFile* InPlatformFile);`
- L243 _public prototype_ `virtual ~FPartialDownloadFileHandle();`
- L246 _public prototype_ `virtual int64 Tell() override;` — IFileHandle interface
- L247 _public prototype_ `virtual bool Seek(int64 NewPosition) override;`
- L248 _public prototype_ `virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd) override;`
- L249 _public prototype_ `virtual bool Read(uint8* Destination, int64 BytesToRead) override;`
- L250 _public prototype_ `virtual bool ReadAt(uint8* Destination, int64 BytesToRead, int64 Offset) override;`
- L251 _public prototype_ `virtual bool Write(const uint8* Source, int64 BytesToWrite) override;`
- L252 _public prototype_ `virtual bool Flush(const bool bFullFlush) override;`
- L253 _public prototype_ `virtual bool Truncate(int64 NewSize) override;`
- L259 _private prototype_ `bool EnsureBlocksAvailable(int64 Offset, int64 Length);` — Ensure the blocks covering the given range are available
- L264 _private prototype_ `bool ReopenFile();` — Reopen the file handle to see newly written data
- L267 _private member_ `TUniquePtr<IFileHandle> RealHandle;`
- L268 _private member_ `FString FilePath;`
- L269 _private member_ `TSharedPtr<FPartialDownloadCoordinator> Coordinator;`
- L270 _private member_ `int64 CurrentPosition = 0;`
- L271 _private member_ `IPlatformFile* PlatformFile = nullptr;`
- L272 _private member_ `FCriticalSection HandleMutex;` — Protects all operations on RealHandle

#### class `FPartialDownloadPlatformFile`  
`class FPartialDownloadPlatformFile : public IPlatformFile`  
_L278-360_
- inherits: `IPlatformFile`
- desc: Custom IPlatformFile wrapper that intercepts .ucas file opens and provides on-demand fetching
- L281 _public function_ `static constexpr const TCHAR* GetTypeName()`
- L286 _public prototype_ `FPartialDownloadPlatformFile();`
- L287 _public prototype_ `virtual ~FPartialDownloadPlatformFile();`
- L300 _public prototype_ `bool InitializePartialDownload( const FString& InDownloadDirectory, const FString& InZenExePath, const FString& InOidcExePath, const FString& InNamespace, const FString& InBucketId, const FString& InBuildId, const FString& InProxyUrl);` — Initialize the platform file wrapper @param InDownloadDirectory Where .utoc and partial .ucas files are stored @param InZenExePath Path to zen.exe @param InOidcExePath Path to OidcToken.exe @param InNamespace Cloud namespace @param InBucketId Cloud bucket @param InBuildId Cloud build ID @param InProxyUrl Optional proxy URL @return true if initialization succeeded
- L312 _public prototype_ `void ParseTocFiles();` — Parse all .utoc files in the download directory and build block maps
- L317 _public function_ `TSharedPtr<FPartialDownloadCoordinator> GetCoordinator() const` — Get the coordinator (for testing/debugging)
- L320 _public function_ `virtual bool ShouldBeUsed(IPlatformFile* Inner, const TCHAR* CmdLine) const override` — IPlatformFile interface
- L321 _public prototype_ `virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CmdLine) override;`
- L322 _public function_ `virtual void InitializeAfterSetActive() override`
- L323 _public function_ `virtual IPlatformFile* GetLowerLevel() override`
- L324 _public function_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override`
- L325 _public function_ `virtual const TCHAR* GetName() const override`
- L327 _public prototype_ `virtual bool FileExists(const TCHAR* Filename) override;`
- L328 _public prototype_ `virtual int64 FileSize(const TCHAR* Filename) override;`
- L329 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) override;`
- L330 _public prototype_ `virtual bool IsReadOnly(const TCHAR* Filename) override;`
- L331 _public prototype_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override;`
- L332 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;`
- L333 _public prototype_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override;`
- L334 _public prototype_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;`
- L335 _public prototype_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override;`
- L336 _public prototype_ `virtual FString GetFilenameOnDisk(const TCHAR* Filename) override;`
- L338 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L339 _public prototype_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override;`
- L340 _public prototype_ `virtual bool DirectoryExists(const TCHAR* Directory) override;`
- L341 _public prototype_ `virtual bool CreateDirectory(const TCHAR* Directory) override;`
- L342 _public prototype_ `virtual bool DeleteDirectory(const TCHAR* Directory) override;`
- L343 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;`
- L345 _public prototype_ `virtual bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L346 _public prototype_ `virtual bool IterateDirectoryRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L347 _public prototype_ `virtual bool IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L348 _public prototype_ `virtual bool IterateDirectoryStatRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L354 _private prototype_ `bool ShouldInterceptFile(const TCHAR* Filename) const;` — Check if this is a .ucas file that should be intercepted
- L357 _private member_ `IPlatformFile* LowerLevel = nullptr;`
- L358 _private member_ `TSharedPtr<FPartialDownloadCoordinator> Coordinator;`
- L359 _private member_ `FString DownloadDirectory;`

### `Source/Programs/IoStoreDependencyViewer/Private/SCloudDownloadDialog.h` (Private)


#### struct `FCloudBuild`  
`struct FCloudBuild`  
_L14-27_
- desc: Represents a cloud build
- L16 _public member_ `FString BuildName;`
- L17 _public member_ `FString BuildId;`
- L18 _public member_ `FString Changelist;`
- L19 _public member_ `FString BucketId;`
- L20 _public member_ `FString Namespace;`
- L21 _public member_ `FDateTime CreatedAt;`
- L22 _public member_ `TArray<FString> Platforms;`
- L24 _public prototype_ `FCloudBuild() = default;`
- L25 _public function_ `FCloudBuild(const FString& InName, const FString& InBuildId, const FString& InCL, const FString& InBucket, const FString& InNamespace, const FDateTime& InDate) : BuildName(InName), BuildId(InBuildId), Changelist(InCL), BucketId(InBucket), Namespace(InNamespace), CreatedAt(InDate)`

#### struct `FCloudNamespace`  
`struct FCloudNamespace`  
_L30-37_
- desc: Represents a namespace
- L32 _public member_ `FString Name;`
- L33 _public member_ `TArray<FString> Buckets;`
- L35 _public prototype_ `FCloudNamespace() = default;`
- L36 _public function_ `FCloudNamespace(const FString& InName) : Name(InName)`

#### class `SCloudDownloadDialog`  
`class SCloudDownloadDialog : public SCompoundWidget`  
_L42-166_
- inherits: `SCompoundWidget`
- desc: Dialog for downloading builds from cloud storage
- L45 _public function_ `SLATE_BEGIN_ARGS(SCloudDownloadDialog)`
- L46 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SWindow> InParentWindow);`
- L51 _public function_ `FString GetDownloadDirectory() const` — Returns the selected download directory
- L54 _public function_ `bool WasDownloadInitiated() const` — Returns true if download was initiated
- L57 _public function_ `bool WasPartialDownloadUsed() const` — Returns true if partial downloads were used
- L60 _public function_ `FString GetZenExePath() const` — Returns zen.exe path
- L63 _public function_ `FString GetOidcExePath() const` — Returns OidcToken.exe path
- L66 _public function_ `FString GetCloudNamespace() const` — Returns cloud namespace
- L69 _public function_ `FString GetCloudBucket() const` — Returns cloud bucket
- L72 _public function_ `FString GetCloudBuildId() const` — Returns cloud build ID
- L75 _public function_ `FString GetProxyUrl() const` — Returns proxy URL
- L79 _private prototype_ `bool LoadCloudSettings();` — Configuration reading
- L82 _private prototype_ `bool QueryNamespaces();` — Zen.exe interaction
- L83 _private prototype_ `bool QueryBuilds(const FString& Namespace, const FString& BuildType);`
- L84 _private prototype_ `bool DownloadBuild(const FCloudBuild& Build);`
- L85 _private prototype_ `int32 RunZenCommand(const FString& Command, FString& OutResult);`
- L88 _private prototype_ `FReply OnRefreshNamespacesClicked();` — UI callbacks
- L89 _private prototype_ `FReply OnQueryBuildsClicked();`
- L90 _private prototype_ `FReply OnDownloadClicked();`
- L91 _private prototype_ `FReply OnCancelClicked();`
- L92 _private prototype_ `FReply OnBrowseDirectoryClicked();`
- L95 _private prototype_ `TSharedRef<SWidget> OnGenerateNamespaceWidget(TSharedPtr<FString> InItem);` — Dropdown callbacks
- L96 _private prototype_ `void OnNamespaceSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L97 _private prototype_ `FText GetCurrentNamespaceText() const;`
- L99 _private prototype_ `TSharedRef<SWidget> OnGenerateBuildTypeWidget(TSharedPtr<FString> InItem);`
- L100 _private prototype_ `void OnBuildTypeSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L101 _private prototype_ `FText GetCurrentBuildTypeText() const;`
- L103 _private prototype_ `TSharedRef<SWidget> OnGenerateStreamWidget(TSharedPtr<FString> InItem);`
- L104 _private prototype_ `void OnStreamSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L105 _private prototype_ `FText GetCurrentStreamText() const;`
- L107 _private prototype_ `TSharedRef<SWidget> OnGeneratePlatformWidget(TSharedPtr<FString> InItem);`
- L108 _private prototype_ `void OnPlatformSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L109 _private prototype_ `FText GetCurrentPlatformText() const;`
- L111 _private prototype_ `TSharedRef<SWidget> OnGenerateBuildWidget(TSharedPtr<FCloudBuild> InItem);`
- L112 _private prototype_ `void OnBuildSelectionChanged(TSharedPtr<FCloudBuild> NewSelection, ESelectInfo::Type SelectInfo);`
- L113 _private prototype_ `FText GetCurrentBuildText() const;`
- L115 _private prototype_ `void OnDownloadDirectoryChanged(const FText& NewText);`
- L116 _private prototype_ `void OnBuildFilterTextChanged(const FText& NewText);`
- L119 _private prototype_ `void UpdateAvailableStreams();` — Helper functions for cascading dropdowns
- L120 _private prototype_ `void UpdateAvailablePlatforms(const FString& PreviousPlatform = FString());`
- L121 _private prototype_ `TArray<FString> GetMatchingBuckets() const;`
- L122 _private prototype_ `void ApplyBuildFilter();`
- L125 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Parent window
- L128 _private member_ `FString ZenExePath;` — Cloud settings
- L129 _private member_ `FString OidcExePath;`
- L130 _private member_ `FString ProxyUrl;`
- L133 _private member_ `TArray<TSharedPtr<FString>> NamespaceList;` — UI state
- L134 _private member_ `TSharedPtr<FString> SelectedNamespace;`
- L135 _private member_ `TMap<FString, TArray<FString>> NamespaceBuckets;` — Map of namespace -> buckets
- L137 _private member_ `TArray<TSharedPtr<FString>> BuildTypeList;`
- L138 _private member_ `TSharedPtr<FString> SelectedBuildType;`
- L140 _private member_ `TArray<TSharedPtr<FString>> StreamList;`
- L141 _private member_ `TSharedPtr<FString> SelectedStream;`
- L143 _private member_ `TArray<TSharedPtr<FString>> PlatformList;`
- L144 _private member_ `TSharedPtr<FString> SelectedPlatform;`
- L146 _private member_ `TArray<TSharedPtr<FCloudBuild>> BuildList;`
- L147 _private member_ `TArray<TSharedPtr<FCloudBuild>> FilteredBuildList;` — Filtered list based on BuildFilterText
- L148 _private member_ `TSharedPtr<FCloudBuild> SelectedBuild;`
- L149 _private member_ `FString BuildFilterText;` — Regex filter for build names
- L151 _private member_ `FString DownloadDirectory;`
- L152 _private member_ `bool bDownloadInitiated = false;`
- L153 _private member_ `bool bPartialDownloadUsed = false;`
- L154 _private member_ `std::atomic<bool> bCancelRequested{false};` — Set when user clicks Cancel during download
- L157 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> NamespaceComboBox;` — UI widgets
- L158 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> BuildTypeComboBox;`
- L159 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> StreamComboBox;`
- L160 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> PlatformComboBox;`
- L161 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FCloudBuild>>> BuildComboBox;`
- L162 _private member_ `TSharedPtr<SEditableTextBox> BuildFilterTextBox;`
- L163 _private member_ `TSharedPtr<SEditableTextBox> DownloadDirectoryTextBox;`
- L164 _private member_ `TSharedPtr<SCheckBox> UsePartialDownloadsCheckBox;`
- L165 _private member_ `TSharedPtr<STextBlock> StatusTextBlock;`

### `Source/Programs/IoStoreDependencyViewer/Private/SDependencyGraphPanel.h` (Private)


#### struct `FGraphNode`  
`struct FGraphNode`  
_L11-34_
- desc: Represents a node in the visual graph
- L13 _public member_ `TSharedPtr<FIoStoreAssetInfo> AssetInfo;`
- L14 _public member_ `FVector2D Position;`
- L15 _public member_ `FVector2D Size;`
- L16 _public member_ `TArray<TWeakPtr<FGraphNode>> HardDependencies;`
- L17 _public member_ `TArray<TWeakPtr<FGraphNode>> SoftDependencies;`
- L18 _public member_ `bool bIsRoot = false;`
- L21 _public member_ `FString ContainerName;` — For container view
- L22 _public member_ `bool bIsContainer = false;`
- L23 _public member_ `int32 HardDependencyCount = 0;` — Deprecated: Use HardDependencyCounts array for accurate per-edge counts
- L24 _public member_ `int32 SoftDependencyCount = 0;` — Deprecated: Use SoftDependencyCounts array for accurate per-edge counts
- L30 _public member_ `TArray<int32> HardDependencyCounts;` — Edge-specific dependency counts (for container view) Parallel arrays to HardDependencies/SoftDependencies: count at index i corresponds to dependency at index i Prevents overwriting when multiple sources point to same target Using parallel arrays instead of TMap to avoid TSharedPtr reference cycles
- L31 _public member_ `TArray<int32> SoftDependencyCounts;`
- L33 _public function_ `FGraphNode() : Position(0, 0), Size(200, 80)`

#### class `SDependencyGraphPanel`  
`class SDependencyGraphPanel : public SCompoundWidget`  
_L37-195_
- inherits: `SCompoundWidget`
- desc: Custom widget for displaying dependency graph
- L40 _public function_ `SLATE_BEGIN_ARGS(SDependencyGraphPanel)`
- L41 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L44 _public prototype_ `virtual ~SDependencyGraphPanel();`
- L47 _public prototype_ `void RebuildGraph(TSharedPtr<FIoStoreAssetInfo> RootAsset, const TMap<FPackageId, TSharedPtr<FIoStoreAssetInfo>>& InPackageIdToAsset, int32 DepthLimit, int32 ReferencerDepthLimit = 0);` — Rebuild the graph from a root asset
- L53 _public prototype_ `void RebuildGraphAllAssets(const TArray<TSharedPtr<FIoStoreAssetInfo>>& Assets, TSharedPtr<FIoStoreAssetInfo> SelectedAsset);` — Rebuild graph showing all assets
- L57 _public prototype_ `void RebuildGraphContainers(const TArray<TSharedPtr<FIoStoreAssetInfo>>& AllAssets);` — Rebuild graph showing container dependencies
- L60 _public prototype_ `void ZoomToFit();` — Zoom to fit all nodes
- L63 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — Paint the graph
- L66 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L67 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L68 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L69 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L72 _public prototype_ `TSharedPtr<SWidget> OnGraphContextMenuOpening();` — Context menu for graph panel
- L73 _public prototype_ `void CopyEntireGraphToClipboard();`
- L74 _public prototype_ `void CopyHighlightedPathToClipboard();`
- L75 _public prototype_ `void CopyNodeAssetToClipboard();`
- L78 _public member_ `TSharedPtr<FGraphNode> RightClickedNode;` — Track right-clicked node for context menu
- L81 _public function_ `void SetSelectedNode(TSharedPtr<FGraphNode> Node)` — Set the selected node
- L84 _public function_ `TSharedPtr<FGraphNode> GetSelectedNode() const` — Get the currently selected node
- L87 _public prototype_ `void OnGraphSearchTextChanged(const FText& InText);` — Search functionality
- L88 _public function_ `FText GetGraphSearchText() const`
- L91 _public prototype_ `FText GetTooltipText() const;` — Get tooltip text for hovered node
- L94 _public function_ `void SetReferencerMap(const TMap<FPackageId, TArray<FAssetDependency>>& InReferencerMap)` — Set the referencer map for building referencer nodes
- L98 _private prototype_ `void CreateDependencyNodes(TSharedPtr<FGraphNode> ParentNode, TSharedPtr<FIoStoreAssetInfo> ParentAsset, int32 CurrentDepth, int32 MaxDepth, TMap<FPackageId, TSharedPtr<FGraphNode>>& CreatedNodes, float& CurrentX, float& CurrentY, bool bIsRootCall = false);` — Recursively create nodes for dependencies
- L103 _private prototype_ `void CreateReferencerNodes(TSharedPtr<FGraphNode> ChildNode, TSharedPtr<FIoStoreAssetInfo> ChildAsset, int32 CurrentDepth, int32 MaxDepth, TMap<FPackageId, TSharedPtr<FGraphNode>>& CreatedNodes, const TMap<FPackageId, TArray<FAssetDependency>>& ReferencerMap, float& CurrentX, float& CurrentY, bool bIsRootCall = false);` — Recursively create nodes for referencers
- L109 _private prototype_ `void DrawNode(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId, TSharedPtr<FGraphNode> Node) const;` — Draw a node
- L113 _private prototype_ `void DrawConnection(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId, const FVector2D& Start, const FVector2D& End, const FLinearColor& Color, float Thickness) const;` — Draw a connection between nodes
- L117 _private prototype_ `FVector2D GetNodeScreenPosition(TSharedPtr<FGraphNode> Node) const;` — Get screen space position for a node
- L120 _private member_ `TArray<TSharedPtr<FGraphNode>> AllNodes;` — All nodes in the graph
- L123 _private member_ `TSharedPtr<FGraphNode> RootNode;` — Root node
- L126 _private member_ `TMap<FPackageId, TSharedPtr<FIoStoreAssetInfo>> PackageIdToAsset;` — Package ID to asset lookup
- L129 _private member_ `TMap<FPackageId, TArray<FAssetDependency>> PackageIdToReferencers;` — Package ID to referencers lookup
- L132 _private member_ `FVector2D ViewOffset;` — View transform
- L133 _private member_ `float ZoomLevel;`
- L136 _private member_ `bool bIsPanning;` — Interaction state
- L137 _private member_ `FVector2D LastMousePosition;`
- L138 _private member_ `FVector2D LastClickPosition;`
- L139 _private member_ `double LastClickTime;`
- L142 _private member_ `TSharedPtr<FGraphNode> SelectedNode;` — Selected and hovered nodes
- L143 _private member_ `TSharedPtr<FGraphNode> HoveredNode;`
- L146 _private prototype_ `TSharedPtr<FGraphNode> FindNodeAtPosition(const FVector2D& ScreenPosition, const FGeometry& MyGeometry) const;` — Find node at screen position
- L149 _private prototype_ `void PerformSearch();` — Perform search (private helper)
- L152 _private prototype_ `void CopyTreeToClipboardHelper(TSharedPtr<FGraphNode> Node, bool bOnlyHighlighted, bool bShowSelectedMarker);` — Helper to copy tree to clipboard with specified options
- L155 _private prototype_ `void BuildTreeTextRecursive(TSharedPtr<FGraphNode> Node, int32 Indent, TSet<TSharedPtr<FGraphNode>>& Visited, FString& OutText, bool bOnlyHighlighted, int32 CurrentDepth = 0, int32 MaxDepth = 999) const;` — Build tree text representation
- L156 _private prototype_ `void BuildReferencerTreeTextRecursive(TSharedPtr<FGraphNode> Node, int32 Indent, TSet<TSharedPtr<FGraphNode>>& Visited, FString& OutText, bool bOnlyHighlighted, int32 CurrentDepth = 0, int32 MaxDepth = 999) const;`
- L159 _private prototype_ `void CollectReferencePaths(TSharedPtr<FGraphNode> Node, TArray<TSharedPtr<FGraphNode>>& CurrentPath, TSet<TSharedPtr<FGraphNode>>& PathVisited, TArray<TArray<TSharedPtr<FGraphNode>>>& OutPaths, bool bOnlyHighlighted, int32 CurrentDepth, int32 MaxDepth) const;` — Helper to collect all unique reference paths from leaf nodes to target node
- L162 _private prototype_ `void BuildReverseEdges() const;` — Build reverse edge map for efficient incoming-edge queries (const to support mutable cache pattern)
- L165 _private prototype_ `void ComputePathsToMatchedNodes();` — Compute paths from selected to matched nodes
- L166 _private prototype_ `bool IsReachableFromSelected(TSharedPtr<FGraphNode> Node, TSet<TSharedPtr<FGraphNode>>& Visited) const;`
- L167 _private prototype_ `bool CanReachMatchedNode(TSharedPtr<FGraphNode> Node, TSet<TSharedPtr<FGraphNode>>& Visited) const;`
- L168 _private prototype_ `bool CanReachNode(TSharedPtr<FGraphNode> FromNode, TSharedPtr<FGraphNode> ToNode, TSet<TSharedPtr<FGraphNode>>& Visited) const;`
- L169 _private prototype_ `bool IsReachableFromMatched(TSharedPtr<FGraphNode> Node, TSet<TSharedPtr<FGraphNode>>& Visited) const;`
- L170 _private prototype_ `bool CanReachSelected(TSharedPtr<FGraphNode> Node, TSet<TSharedPtr<FGraphNode>>& Visited) const;`
- L173 _private member_ `FText GraphSearchText;` — Search state
- L174 _private member_ `TSet<TSharedPtr<FGraphNode>> MatchedNodes;`
- L177 _private member_ `mutable TMap<TSharedPtr<FGraphNode>, bool> NodeCanReachMatched;` — Path highlighting state - nodes that can reach matched nodes
- L178 _private member_ `mutable TMap<TSharedPtr<FGraphNode>, bool> NodeReachableFromSelected;`
- L179 _private member_ `mutable TMap<TSharedPtr<FGraphNode>, bool> NodeReachableFromMatched;`
- L180 _private member_ `mutable TMap<TSharedPtr<FGraphNode>, bool> NodeCanReachSelected;`
- L183 _private member_ `mutable TMap<TSharedPtr<FGraphNode>, TArray<TSharedPtr<FGraphNode>>> ReverseEdges;` — Reverse edge map: node -> set of nodes that depend on it (for efficient incoming edge queries)
- L186 _private member_ `static constexpr float NodeWidth = 200.0f;` — Layout constants
- L187 _private member_ `static constexpr float NodeHeight = 80.0f;`
- L188 _private member_ `static constexpr float HorizontalSpacing = 250.0f;`
- L189 _private member_ `static constexpr float VerticalSpacing = 120.0f;`
- L190 _private member_ `static constexpr int32 MaxClipboardDepth = 50;` — Maximum depth for clipboard copy operations
- L193 _private member_ `int32 CurrentDependencyDepth = 1;` — Current depth limits for copy functions
- L194 _private member_ `int32 CurrentReferencerDepth = 0;`

### `Source/Programs/IoStoreDependencyViewer/Private/SIoStoreDependencyViewer.h` (Private)


#### struct `FAssetDependency`  
`struct FAssetDependency`  
_L25-33_
- desc: Represents a dependency relationship
- L27 _public member_ `FPackageId PackageId;`
- L28 _public member_ `FString PackageName;`
- L29 _public member_ `bool bIsSoftReference = false;` — false = hard, true = soft
- L31 _public prototype_ `FAssetDependency() = default;`
- L32 _public function_ `FAssetDependency(FPackageId InId, bool bSoft) : PackageId(InId), bIsSoftReference(bSoft)`

#### struct `FIoStoreAssetInfo`  
`struct FIoStoreAssetInfo`  
_L36-52_
- desc: Represents a chunk/asset in the container
- L38 _public member_ `FIoChunkId ChunkId;`
- L39 _public member_ `FPackageId PackageId;`
- L40 _public member_ `FString FileName;`
- L41 _public member_ `FString PackageName;`
- L42 _public member_ `FString ContainerName;`
- L43 _public member_ `uint64 Size = 0;`
- L44 _public member_ `uint64 CompressedSize = 0;`
- L45 _public member_ `bool bIsCompressed = false;`
- L46 _public member_ `TArray<FAssetDependency> HardDependencies;`
- L47 _public member_ `TArray<FAssetDependency> SoftDependencies;`
- L48 _public member_ `TArray<FString> Tags;`
- L49 _public member_ `int32 PartitionIndex = 0;`
- L51 _public prototype_ `FIoStoreAssetInfo() = default;`

#### class `SIoStoreDependencyViewer`  
`class SIoStoreDependencyViewer : public SCompoundWidget`  
_L59-226_
- inherits: `SCompoundWidget`
- desc: IoStore Dependency Viewer Widget Loads and displays IoStore container files (.utoc, .uondemandtoc)
- L62 _public function_ `SLATE_BEGIN_ARGS(SIoStoreDependencyViewer)`
- L63 _public prototype_ `SLATE_ARGUMENT(FString, InitialPath) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L67 _public prototype_ `virtual ~SIoStoreDependencyViewer();`
- L71 _private prototype_ `FReply OnLoadDirectoryClicked();` — Menu actions
- L72 _private prototype_ `FReply OnRefreshClicked();`
- L73 _private prototype_ `FReply OnClearClicked();`
- L74 _private prototype_ `FReply OnCloudDownloadClicked();`
- L75 _private prototype_ `FReply OnLoadCloudBuildClicked();`
- L78 _private prototype_ `void ClearAllData();` — Loading functions
- L79 _private prototype_ `bool LoadFromDirectory(const FString& DirectoryPath);`
- L80 _private prototype_ `bool LoadAllContainersWithProgress(const FString& DirectoryPath);`
- L81 _private prototype_ `bool LoadOnDemandContainers(const FString& DirectoryPath, const TMap<FGuid, FAES::FAESKey>& EncryptionKeys);`
- L82 _private prototype_ `bool LoadMetaData(const FString& DirectoryPath);`
- L83 _private prototype_ `void ProcessContainerHeader(const FIoContainerHeader& Header, const FString& ContainerName);`
- L84 _private prototype_ `void ResolveDependencyNames();`
- L87 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForAssetList(TSharedPtr<FIoStoreAssetInfo> AssetInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Asset list callbacks
- L88 _private prototype_ `void OnAssetListSelectionChanged(TSharedPtr<FIoStoreAssetInfo> AssetInfo, ESelectInfo::Type SelectInfo);`
- L91 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForDependencyList(TSharedPtr<FAssetDependency> Dependency, const TSharedRef<STableViewBase>& OwnerTable);` — Dependency list callbacks
- L92 _private prototype_ `void OnDependencyListSelectionChanged(TSharedPtr<FAssetDependency> Dependency, ESelectInfo::Type SelectInfo);`
- L95 _private prototype_ `void OnSearchTextChanged(const FText& InText);` — Search
- L96 _private prototype_ `void OnSearchModeChanged(int32 NewMode);`
- L99 _private prototype_ `void OnDepthChanged(int32 NewDepth);` — Graph controls
- L100 _private function_ `int32 GetCurrentDepth() const`
- L101 _private prototype_ `void OnReferencerDepthChanged(int32 NewDepth);`
- L102 _private function_ `int32 GetCurrentReferencerDepth() const`
- L103 _private prototype_ `FReply OnZoomToFitClicked();`
- L104 _private prototype_ `void OnGraphViewModeChanged(TSharedPtr<FString> NewMode, ESelectInfo::Type SelectInfo);`
- L105 _private prototype_ `TSharedRef<SWidget> OnGenerateGraphViewModeWidget(TSharedPtr<FString> InItem);`
- L106 _private prototype_ `FText GetCurrentGraphViewModeText() const;`
- L107 _private prototype_ `void OnGraphSearchTextChanged(const FText& InText);`
- L110 _private prototype_ `void UpdateAssetList();` — UI update functions
- L111 _private prototype_ `void UpdateAssetInfoPanel(TSharedPtr<FIoStoreAssetInfo> AssetInfo);`
- L112 _private prototype_ `void BuildDependencyGraph(TSharedPtr<FIoStoreAssetInfo> RootAsset);`
- L115 _private prototype_ `FReply OnNavigateBackClicked();` — Navigation
- L116 _private prototype_ `FReply OnNavigateForwardClicked();`
- L117 _private prototype_ `bool CanNavigateBack() const;`
- L118 _private prototype_ `bool CanNavigateForward() const;`
- L119 _private prototype_ `void NavigateToAsset(TSharedPtr<FIoStoreAssetInfo> Asset, bool bAddToHistory);`
- L122 _private prototype_ `TSharedPtr<SWidget> OnReferencersContextMenuOpening();` — Context menu handlers
- L123 _private prototype_ `TSharedPtr<SWidget> OnHardDepsContextMenuOpening();`
- L124 _private prototype_ `TSharedPtr<SWidget> OnSoftDepsContextMenuOpening();`
- L125 _private prototype_ `void CopyReferencersToClipboard();`
- L126 _private prototype_ `void CopyHardDepsToClipboard();`
- L127 _private prototype_ `void CopySoftDepsToClipboard();`
- L130 _private prototype_ `TSharedPtr<FIoStoreAssetInfo> FindAssetByPackageId(const FPackageId& PackageId);` — Helper functions
- L131 _private prototype_ `TSharedPtr<FIoStoreAssetInfo> FindAssetByChunkId(const FIoChunkId& ChunkId);`
- L132 _private prototype_ `FString FindDirectoryWithTocFiles(const FString& RootDirectory);`
- L135 _private member_ `TSharedPtr<SListView<TSharedPtr<FIoStoreAssetInfo>>> AssetListView;` — UI state
- L136 _private member_ `TSharedPtr<SListView<TSharedPtr<FAssetDependency>>> HardDependenciesListView;`
- L137 _private member_ `TSharedPtr<SListView<TSharedPtr<FAssetDependency>>> SoftDependenciesListView;`
- L138 _private member_ `TSharedPtr<SListView<TSharedPtr<FAssetDependency>>> ReferencersListView;`
- L139 _private member_ `TSharedPtr<STextBlock> StatusText;`
- L140 _private member_ `TSharedPtr<STextBlock> AssetInfoText;`
- L141 _private member_ `TSharedPtr<SDependencyGraphPanel> GraphPanel;`
- L142 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L143 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> GraphViewModeComboBox;`
- L144 _private member_ `TArray<TSharedPtr<FString>> GraphViewModeOptions;`
- L147 _private member_ `TArray<TSharedPtr<FIoStoreAssetInfo>> AllAssets;` — Data
- L148 _private member_ `TArray<TSharedPtr<FIoStoreAssetInfo>> FilteredAssets;`
- L149 _private member_ `TArray<TSharedPtr<FAssetDependency>> CurrentHardDependencies;`
- L150 _private member_ `TArray<TSharedPtr<FAssetDependency>> CurrentSoftDependencies;`
- L151 _private member_ `TArray<TSharedPtr<FAssetDependency>> CurrentReferencers;`
- L152 _private member_ `TMap<FIoChunkId, TSharedPtr<FIoStoreAssetInfo>> ChunkIdToAsset;`
- L153 _private member_ `TMap<FPackageId, TSharedPtr<FIoStoreAssetInfo>> PackageIdToAsset;`
- L154 _private member_ `TMap<FPackageId, TArray<FAssetDependency>> PackageIdToReferencers;` — Reverse dependency map
- L155 _private member_ `TSharedPtr<FIoStoreAssetInfo> CurrentSelectedAsset;`
- L158 _private member_ `TArray<TSharedPtr<FIoStoreAssetInfo>> NavigationHistory;` — Navigation history for back/forward
- L159 _private member_ `int32 NavigationHistoryIndex = -1;`
- L160 _private member_ `bool bIsNavigating = false;` — Prevent adding to history during navigation
- L163 _private member_ `FCriticalSection SharedDataLock;` — Shared data lock for parallel container loading
- L166 _private member_ `FString CurrentSearchText;` — Search state
- L167 _private member_ `int32 SearchMode = 0;` — 0=Name, 1=ChunkId, 2=Tags
- L176 _private member_ `EGraphViewMode CurrentGraphViewMode = EGraphViewMode::SelectedAssetDependencies;`
- L179 _private member_ `int32 CurrentTreeDepth = 1;` — Tree depth
- L180 _private member_ `int32 CurrentReferencerDepth = 0;`
- L183 _private member_ `TArray<TUniquePtr<FIoStoreReader>> IoStoreReaders;` — IoStore data
- L184 _private member_ `TArray<TSharedPtr<class FIoStoreReaderAdapter>> IoStoreAdapters;` — New adapter-based readers
- L185 _private member_ `TSharedPtr<FIoContainerMetaReader> MetaReader;`
- L188 _private member_ `bool bUsePartialDownloads = false;` — Cloud build parameters (for partial downloads)
- L189 _private member_ `FString ZenExePath;`
- L190 _private member_ `FString OidcExePath;`
- L191 _private member_ `FString CloudNamespace;`
- L192 _private member_ `FString CloudBucket;`
- L193 _private member_ `FString CloudBuildId;`
- L194 _private member_ `FString CloudProxyUrl;`
- L195 _private member_ `FString BaseDownloadDirectory;` — Where UTOCs are stored
- L198 _private member_ `FString LoadedBuildSource;` — Current loaded build info (for status display)
- L200 _private member_ `static constexpr int32 MaxTreeDepth = 10;`
- L207 _public function_ `void SetCloudBuildParameters( const FString& InZenExePath, const FString& InOidcExePath, const FString& InNamespace, const FString& InBucket, const FString& InBuildId, const FString& InProxyUrl, const FString& InBaseDownloadDirectory, bool bInUsePartialDownloads)` — Configure cloud build parameters for partial downloads Call this before LoadFromDirectory if using partial downloads

#### enum `SIoStoreDependencyViewer::EGraphViewMode`  
`enum class EGraphViewMode`  
_L170-175_
- desc: Graph view mode
- L172 _public enumerator_ `SelectedAssetDependencies`
- L173 _public enumerator_ `AllAssets`
- L174 _public enumerator_ `ContainerDependencies`
