# Plugins / ChunkDownloader

- module root: `Plugins/Runtime/ChunkDownloader/Source`
- headers: 4; symbols: 134
- symbol kinds: class=2, delegate=2, enum=1, enumerator=6, function=7, macro=1, member=53, prototype=53, struct=4, typedef=5
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, HTTP
- PrivateIncludePathModuleNames: 

### `Plugins/Runtime/ChunkDownloader/Source/Private/ChunkDownloaderLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChunkDownloader, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChunkDownloader, Log, All);`

### `Plugins/Runtime/ChunkDownloader/Source/Private/Download.h` (Private)


#### class `FDownload`  
`class FDownload : public TSharedFromThis<FDownload>`  
_L8-40_
- inherits: `TSharedFromThis<FDownload>`
- L11 _public prototype_ `FDownload(const TSharedRef<FChunkDownloader>& DownloaderIn, const TSharedRef<FChunkDownloader::FPakFile>& PakFileIn);`
- L12 _public prototype_ `virtual ~FDownload();`
- L14 _public function_ `inline bool HasCompleted() const`
- L15 _public function_ `inline int32 GetProgress() const`
- L17 _public prototype_ `void Start();`
- L18 _public prototype_ `void Cancel(bool bResult);`
- L21 _public member_ `const TSharedRef<FChunkDownloader> Downloader;`
- L22 _public member_ `const TSharedRef<FChunkDownloader::FPakFile> PakFile;`
- L23 _public member_ `const FString TargetFile;`
- L26 _protected prototype_ `void UpdateFileSize();`
- L27 _protected prototype_ `bool ValidateFile() const;`
- L28 _protected prototype_ `bool HasDeviceSpaceRequired() const;`
- L29 _protected prototype_ `void StartDownload(int TryNumber);`
- L30 _protected prototype_ `void OnDownloadProgress(int32 BytesReceived);`
- L31 _protected prototype_ `void OnDownloadComplete(const FString& Url, int TryNumber, int32 HttpStatus);`
- L32 _protected prototype_ `void OnCompleted(bool bSuccess, const FText& ErrorText);`
- L35 _private member_ `bool bIsCancelled = false;`
- L36 _private member_ `FDownloadCancel CancelCallback;`
- L37 _private member_ `bool bHasCompleted = false;`
- L38 _private member_ `FDateTime BeginTime;`
- L39 _private member_ `int32 LastBytesReceived = 0;`

### `Plugins/Runtime/ChunkDownloader/Source/Private/PlatformStreamDownload.h` (Private)


#### Free symbols / members of external scopes

- L10 _typedef_ `typedef TFunction<void(int32 HttpStatus)> FDownloadComplete;`
- L11 _typedef_ `typedef TFunction<void(uint64 BytesReceived)> FDownloadProgress;`
- L12 _typedef_ `typedef TFunction<void(void)> FDownloadCancel;`
- L14 _prototype_ `extern FDownloadCancel PlatformStreamDownload(const FString& Url, const FString& TargetFile, const FDownloadProgress& Progress, const FDownloadComplete& Callback);`

### `Plugins/Runtime/ChunkDownloader/Source/Public/ChunkDownloader.h` (Public)


#### struct `FPakFileEntry`  
`struct FPakFileEntry`  
_L15-33_
- L18 _public member_ `FString FileName;` — unique name of the pak file (not path, i.e. no folder)
- L21 _public member_ `uint64 FileSize = 0;` — final size of the file in bytes
- L26 _public member_ `FString FileVersion;` — unique ID representing a particular version of this pak file when it is used for validation (not done on golden path, but can be requested) this is assumed to be a SHA1 hash if it begins with "SHA1:" otherwise it's considered just a unique ID.
- L29 _public member_ `int32 ChunkId = -1;` — chunk ID this pak file is assigned to
- L32 _public member_ `FString RelativeUrl;` — URL for this pak file (relative to CDN root, includes build-specific folder)

#### class `FChunkDownloader`  
`class FChunkDownloader : public TSharedFromThis<FChunkDownloader>`  
_L37-278_
- inherits: `TSharedFromThis<FChunkDownloader>`
- L40 _public prototype_ `~FChunkDownloader();`
- L41 _public typedef_ `typedef TFunction<void(bool bSuccess)> FCallback;`
- L44 _public prototype_ `static TSharedPtr<FChunkDownloader> Get();` — static getters
- L45 _public prototype_ `static TSharedRef<FChunkDownloader> GetChecked();`
- L46 _public prototype_ `static TSharedRef<FChunkDownloader> GetOrCreate();`
- L47 _public prototype_ `static void Shutdown();`
- L50 _public prototype_ `void Initialize(const FString& PlatformName, int32 TargetDownloadsInFlight);` — initialize the download manager (populates the list of cached pak files from disk). Call only once.
- L54 _public prototype_ `void Finalize();` — unmount all chunks and cancel any downloads in progress (preserving partial downloads). Call only once, don't reuse this object, make a new one.
- L57 _public prototype_ `bool LoadCachedBuild(const FString& DeploymentName);` — try to load a cached build ID from disk (good to do before updating build so it can possibly no-op)
- L64 _public prototype_ `void UpdateBuild(const FString& DeploymentName, const FString& ContentBuildId, const FCallback& Callback);` — set the the content build id if the content build id has changed, we pull the new BuildManifest from CDN and load it. the client should compare ContentBuildId with its current embedded build id to determine if this content is even compatible BEFORE calling this function. e.g. ContentBuildId="v1.4.22-r23928293" we might consider BUILD_VERSION="1.4.1" compatible but BUILD_VERSION="1.3.223" incompatible (needing an update)
- L67 _public function_ `inline const FString& GetContentBuildId() const` — get the current content build ID
- L69 _public function_ `inline const FString& GetDeploymentName() const` — get the most recent deployment name
- L81 _public prototype_ `static void DumpLoadedChunks();`
- L84 _public prototype_ `static const TCHAR* ChunkStatusToString(EChunkStatus Status);` — chunk status as logable string
- L87 _public prototype_ `EChunkStatus GetChunkStatus(int32 ChunkId) const;` — get the current status of the specified chunk
- L90 _public prototype_ `void GetAllChunkIds(TArray<int32>& OutChunkIds) const;` — return a list of all chunk IDs in the current manifest
- L93 _public prototype_ `void MountChunks(const TArray<int32>& ChunkIds, const FCallback& Callback);` — Download and mount all chunks then fire the callback (convenience wrapper managing multiple MountChunk calls)
- L96 _public prototype_ `void MountChunk(int32 ChunkId, const FCallback& Callback);` — download all pak files, then asynchronously mount them in order (in order among themselves, async with game thread).
- L99 _public prototype_ `void DownloadChunks(const TArray<int32>& ChunkIds, const FCallback& Callback, int32 Priority = 0);` — Download (Cache) all pak files in these chunks then fire the callback (convenience wrapper managing multiple DownloadChunk calls)
- L103 _public prototype_ `void DownloadChunk(int32 ChunkId, const FCallback& Callback, int32 Priority = 0);` — download all pak files in the chunk, but don't mount. Callback is fired when all paks have finished caching (whether success or failure). Downloads will retry forever, but might fail due to space issues.
- L107 _public prototype_ `int FlushCache();` — flush any cached files (on disk) that are not currently being downloaded to or mounting (does not unmount the corresponding pak files). this will include full and partial downloads, but not active downloads.
- L112 _public prototype_ `int ValidateCache();` — validate all fully cached files (blocking) by attempting to read them and check their Version hash. this automatically deletes any files that don't match. Returns the number of files deleted. in this case best to return to a simple update map and reinitialize ChunkDownloader (or restart).
- L116 _public prototype_ `void BeginLoadingMode(const FCallback& Callback);` — Snapshot stats and enter into loading screen mode (pauses all background downloads). Fires callback when all non-background downloads have completed. If no downloads/mounts are currently queued by the end of the frame, callback will fire next frame.
- L138 _public function_ `inline const FStats& GetLoadingStats() const` — get the current loading stats (generally only useful if you're in loading mode see BeginLoadingMode)
- L141 _public member_ `FPlatformChunkInstallMultiDelegate OnChunkMounted;` — Called whenever a chunk mounts (success or failure). ONLY USE THIS IF YOU WANT TO PASSIVELY LISTEN FOR MOUNTS (otherwise use the proper request callback on MountChunk)
- L144 _public member_ `TFunction<void(const FString& FileName, const FString& Url, uint64 SizeBytes, const FTimespan& DownloadTime, int32 HttpStatus)> OnDownloadAnalytics;` — called each time a download attempt finishes (success or failure). ONLY USE THIS IF YOU WANT TO PASSIVELY LISTEN. Downloads retry until successful.
- L147 _public function_ `inline int32 GetNumDownloadRequests() const` — get current number of download requests, so we know whether download is in progress. Downlading Requests will be removed from this array in it's FDownload::OnCompleted callback.
- L153 _protected prototype_ `FChunkDownloader();`
- L155 _protected prototype_ `static bool CheckFileSha1Hash(const FString& FullPathOnDisk, const FString& Sha1HashStr);`
- L161 _private prototype_ `void SetContentBuildId(const FString& DeploymentName, const FString& NewContentBuildId);`
- L163 _private prototype_ `void LoadManifest(const TArray<FPakFileEntry>& PakFiles);`
- L164 _private prototype_ `void TryLoadBuildManifest(int TryNumber);`
- L165 _private prototype_ `void TryDownloadBuildManifest(int TryNumber);`
- L167 _private prototype_ `void WaitForMounts();`
- L168 _private prototype_ `void SaveLocalManifest(bool bForce);`
- L170 _private prototype_ `bool UpdateLoadingMode();`
- L171 _private prototype_ `void ComputeLoadingStats();`
- L173 _private prototype_ `void UnmountPakFile(const TSharedRef<FPakFile>& PakFile);`
- L174 _private prototype_ `void CancelDownload(const TSharedRef<FPakFile>& PakFile, bool bResult);`
- L175 _private prototype_ `void DownloadPakFileInternal(const TSharedRef<FPakFile>& PakFile, const FCallback& Callback, int32 Priority);`
- L177 _private prototype_ `void MountChunkInternal(FChunk& Chunk, const FCallback& Callback);`
- L178 _private prototype_ `void DownloadChunkInternal(const FChunk& Chunk, const FCallback& Callback, int32 Priority);`
- L179 _private prototype_ `void CompleteMountTask(FChunk& Chunk);`
- L181 _private prototype_ `bool UpdateMountTasks(float dts);`
- L182 _private prototype_ `void ExecuteNextTick(const FCallback& Callback, bool bSuccess);`
- L184 _private prototype_ `void IssueDownloads();`
- L207 _private typedef_ `typedef FAsyncTask<FPakMountWork> FMountTask;`
- L235 _private member_ `FStats LoadingModeStats;` — cumulative stats for loading screen mode
- L236 _private member_ `TArray<FCallback> PostLoadCallbacks;`
- L237 _private member_ `int32 LoadingCompleteLatch = 0;`
- L239 _private member_ `FCallback UpdateBuildCallback;`
- L242 _private member_ `FString PlatformName;` — platform name (determines the manifest)
- L245 _private member_ `FString CacheFolder;` — folders to save pak files into on disk
- L248 _private member_ `FString EmbeddedFolder;` — content folder where we can find some chunks shipped with the build
- L251 _private member_ `FString LastDeploymentName;` — build specific ID and URL paths
- L252 _private member_ `FString ContentBuildId;`
- L253 _private member_ `TArray<FString> BuildBaseUrls;`
- L256 _private member_ `TMap<int32,TSharedRef<FChunk>> Chunks;` — chunk id to chunk record
- L259 _private member_ `TMap<FString,TSharedRef<FPakFile>> PakFiles;` — pak file name to pak file record
- L262 _private member_ `TMap<FString,FPakFileEntry> EmbeddedPaks;` — pak files embedded in the build (immutable, compressed)
- L265 _private member_ `bool bNeedsManifestSave = false;` — do we need to save the manifest (done whenever new downloads have started)
- L268 _private member_ `FTSTicker::FDelegateHandle MountTicker;` — handle for the per-frame mount ticker in the main thread
- L271 _private member_ `TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> ManifestRequest;` — manifest download request
- L274 _private member_ `int32 TargetDownloadsInFlight = 1;` — maximum number of downloads to allow concurrently
- L277 _private member_ `TArray<TSharedRef<FPakFile>> DownloadRequests;` — list of pak files that have been requested

#### enum `FChunkDownloader::EChunkStatus`  
`enum class EChunkStatus`  
_L71-79_
- L73 _public enumerator_ `Mounted` — chunk is cached locally and mounted in RAM
- L74 _public enumerator_ `Cached` — chunk is fully cached locally but not mounted
- L75 _public enumerator_ `Downloading` — chunk is partially cached locally, not mounted, download in progress
- L76 _public enumerator_ `Partial` — chunk is partially cached locally, not mounted, download NOT in progress
- L77 _public enumerator_ `Remote` — no local caching has started
- L78 _public enumerator_ `Unknown` — no paks are included in this chunk, can consider it either an error or fully mounted depending

#### struct `FChunkDownloader::FStats`  
`struct FStats`  
_L118-135_
- L121 _public member_ `int FilesDownloaded = 0;` — number of pak files downloaded
- L122 _public member_ `int TotalFilesToDownload = 0;`
- L125 _public member_ `uint64 BytesDownloaded = 0;` — number of bytes downloaded
- L126 _public member_ `uint64 TotalBytesToDownload = 0;`
- L129 _public member_ `int ChunksMounted = 0;` — number of chunks mounted (chunk is an ordered array of paks)
- L130 _public member_ `int TotalChunksToMount = 0;`
- L133 _public member_ `FDateTime LoadingStartTime = FDateTime::MinValue();` — UTC time that loading began (for rate estimates)
- L134 _public member_ `FText LastError;`

#### struct `FChunkDownloader::FPakFile`  
`struct FPakFile`  
_L190-203_
- desc: entry per pak file
- L192 _public member_ `FPakFileEntry Entry;`
- L193 _public member_ `bool bIsCached = false;`
- L194 _public member_ `bool bIsMounted = false;`
- L196 _public member_ `bool bIsEmbedded = false;`
- L197 _public member_ `uint64 SizeOnDisk = 0;` — grows as the file is downloaded. See Entry.FileSize for the target size
- L200 _public member_ `int32 Priority = 0;` — async download
- L201 _public member_ `TSharedPtr<FDownload> Download;`
- L202 _public member_ `TArray<FChunkDownloader::FCallback> PostDownloadCallbacks;`

#### struct `FChunkDownloader::FChunk`  
`struct FChunk`  
_L210-231_
- desc: entry per chunk
- L212 _public member_ `int32 ChunkId = -1;`
- L213 _public member_ `bool bIsMounted = false;`
- L215 _public member_ `TArray<TSharedRef<FPakFile>> PakFiles;`
- L217 _public function_ `inline bool IsCached() const`
- L230 _public member_ `FMountTask* MountTask = nullptr;` — async mount

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHUNKDOWNLOADER_API`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPlatformChunkInstallMultiDelegate, uint32, bool);`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPlatformChunkInstallMultiDelegate, uint32, bool);`
