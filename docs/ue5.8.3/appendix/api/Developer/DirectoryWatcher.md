# Developer / DirectoryWatcher

- module root: `Source/Developer/DirectoryWatcher`
- headers: 13; symbols: 359
- symbol kinds: class=11, delegate=2, enum=8, enumerator=21, function=53, macro=1, member=105, namespace=2, prototype=131, struct=18, typedef=7
- PrivateDependencyModuleNames: Core

### `Source/Developer/DirectoryWatcher/Private/DirectoryWatcherPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDirectoryWatcher, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDirectoryWatcher, Log, All);`

### `Source/Developer/DirectoryWatcher/Private/DirectoryWatcherProxy.h` (Private)


#### class `FDirectoryWatcherProxy`  
`class FDirectoryWatcherProxy : public IDirectoryWatcher`  
_L16-61_
- inherits: `IDirectoryWatcher`
- desc: Proxy around the real directory watcher. Allows this proxy to process external file-system changes that aren't OS specific.
- L19 _public prototype_ `FDirectoryWatcherProxy();`
- L20 _public prototype_ `virtual ~FDirectoryWatcherProxy();`
- L22 _public prototype_ `virtual bool RegisterDirectoryChangedCallback_Handle(const FString& Directory, const FDirectoryChanged& InDelegate, FDelegateHandle& OutHandle, uint32 Flags) override;`
- L23 _public prototype_ `virtual bool UnregisterDirectoryChangedCallback_Handle(const FString& Directory, FDelegateHandle InHandle) override;`
- L24 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L25 _public prototype_ `virtual bool DumpStats() override;`
- L28 _public prototype_ `void RegisterExternalChanges(TArrayView<const FFileChangeData> FileChanges);` — Register external changes that the OS file watcher couldn't detect (eg, a file changing in a UE sandbox)
- L32 _private prototype_ `void RegisterExternalChanges_GameThread(TArrayView<const FFileChangeData> FileChanges);` — Register external changes that the OS file watcher couldn't detect (eg, a file changing in a UE sandbox)
- L35 _private prototype_ `void ProcessPendingChanges();` — Process pending external changes that the OS file watcher couldn't detect (eg, a file changing in a UE sandbox)
- L51 _private member_ `IDirectoryWatcher* Inner;` — Internal directory watcher we act as a proxy for
- L54 _private member_ `TArray<FFileChangeData> PendingFileChanges;` — Array of pending file changes to notify on Tick
- L57 _private member_ `TMap<FString, TArray<FWatchCallback>> WatchMap;` — Map from absolute directories to watch requests for those directories
- L60 _private member_ `bool bWatchMapPendingSort;` — True if the WatchMap is pending a sort

#### struct `FDirectoryWatcherProxy::FWatchCallback`  
`struct FWatchCallback`  
_L38-48_
- desc: Individual watch callback
- L41 _public member_ `FDirectoryChanged Delegate;` — Delegate to call when directory changes happen
- L44 _public member_ `FDelegateHandle InnerHandle;` — Delegate handle after registering the internal directory watcher request
- L47 _public member_ `uint32 WatchFlags;` — Flags specified for this watch (see WatchOptions)

### `Source/Developer/DirectoryWatcher/Private/DirectoryWatcherStub.h` (Private)


#### class `FDirectoryWatcherStub`  
`class FDirectoryWatcherStub : public IDirectoryWatcher`  
_L9-19_
- inherits: `IDirectoryWatcher`
- L12 _public prototype_ `FDirectoryWatcherStub() = default;`
- L13 _public prototype_ `virtual ~FDirectoryWatcherStub() = default;`
- L15 _public function_ `virtual bool RegisterDirectoryChangedCallback_Handle (const FString& Directory, const FDirectoryChanged& InDelegate, FDelegateHandle& OutHandle, uint32 Flags) override`
- L16 _public function_ `virtual bool UnregisterDirectoryChangedCallback_Handle(const FString& Directory, FDelegateHandle InHandle) override`
- L17 _public function_ `virtual void Tick (float DeltaSeconds) override`
- L18 _public function_ `virtual bool DumpStats() override`

#### Free symbols / members of external scopes

- L21 _typedef_ `typedef FDirectoryWatcherStub FDirectoryWatcher;`

### `Source/Developer/DirectoryWatcher/Private/Linux/DirectoryWatchRequestLinux.h` (Private)


#### class `FDirectoryWatchRequestLinux`  
`class FDirectoryWatchRequestLinux`  
_L9-86_
- L13 _public prototype_ `FDirectoryWatchRequestLinux();`
- L14 _public prototype_ `virtual ~FDirectoryWatchRequestLinux();`
- L17 _public prototype_ `bool Init(const FString& InDirectory, uint32 Flags);` — Sets up the directory handle and request information
- L20 _public prototype_ `FDelegateHandle AddDelegate( const IDirectoryWatcher::FDirectoryChanged& InDelegate, uint32 Flags );` — Adds a delegate to get fired when the directory changes
- L22 _public prototype_ `bool RemoveDelegate( FDelegateHandle InHandle );` — Removes a delegate to get fired when the directory changes
- L24 _public prototype_ `bool HasDelegates() const;` — Returns true if this request has any delegates listening to directory changes
- L26 _public prototype_ `void EndWatchRequest();` — Prepares the request for deletion
- L29 _public prototype_ `static void ProcessNotifications(TMap<FString, FDirectoryWatchRequestLinux*>& RequestMap);` — Call ProcessPendingNotifications on each delegate
- L32 _public prototype_ `static void DumpStats(TMap<FString, FDirectoryWatchRequestLinux*>& RequestMap);` — Dump inotify stats
- L37 _private prototype_ `void ProcessPendingNotifications();` — Triggers all pending file change notifications
- L40 _private prototype_ `void WatchDirectoryTree(const FString& RootAbsolutePath, TArray<TPair<FFileChangeData, bool>>* FileChanges);` — Adds watches for all files (and subdirectories) in a directory.
- L43 _private prototype_ `void UnwatchDirectoryTree(const FString& RootAbsolutePath);` — Removes all watches for path
- L45 _private prototype_ `void Shutdown();`
- L47 _private prototype_ `void ProcessNotifyChanges(const FString& FolderName, const struct inotify_event* Event);`
- L49 _private prototype_ `static void ProcessAllINotifyChanges();`
- L51 _private prototype_ `static void SetINotifyErrorMsg(const FString &ErrorMsg);`
- L52 _private prototype_ `static void DumpINotifyErrorDetails(TMap<FString, FDirectoryWatchRequestLinux*>& RequestMap);`
- L57 _private member_ `bool bWatchSubtree;` — Whether or not watch subtree.
- L60 _private member_ `bool bEndWatchRequestInvoked;` — EndWatchRequest called?
- L63 _private member_ `FString WatchDirectory;` — Absolute path to our root watch directory
- L66 _private member_ `TSet<uint32> PathNameHashSet;` — Set of hashed directory names we're watching
- L69 _private typedef_ `typedef TPair<IDirectoryWatcher::FDirectoryChanged, uint32> FWatchDelegate;` — A delegate with its corresponding IDirectoryWatcher::WatchOptions flags
- L70 _private member_ `TArray<FWatchDelegate> Delegates;`
- L72 _private member_ `TArray<TPair<FFileChangeData, bool>> FileChanges;`
- L77 _private member_ `static int GFileDescriptor;` — INotify file descriptor
- L85 _private member_ `static TMultiMap<int32, FWatchInfo> GWatchDescriptorsToWatchInfo;`

#### struct `FDirectoryWatchRequestLinux::FWatchInfo`  
`struct FWatchInfo`  
_L80-84_
- desc: Mapping from inotify watch descriptors to watched directory names + watch request
- L82 _public member_ `FString FolderName;`
- L83 _public member_ `FDirectoryWatchRequestLinux &WatchRequest;`

### `Source/Developer/DirectoryWatcher/Private/Linux/DirectoryWatcherLinux.h` (Private)


#### class `FDirectoryWatcherLinux`  
`class FDirectoryWatcherLinux : public IDirectoryWatcher`  
_L10-27_
- inherits: `IDirectoryWatcher`
- L13 _public prototype_ `FDirectoryWatcherLinux();`
- L14 _public prototype_ `virtual ~FDirectoryWatcherLinux();`
- L16 _public prototype_ `virtual bool RegisterDirectoryChangedCallback_Handle (const FString& Directory, const FDirectoryChanged& InDelegate, FDelegateHandle& OutHandle, uint32 Flags) override;`
- L17 _public prototype_ `virtual bool UnregisterDirectoryChangedCallback_Handle(const FString& Directory, FDelegateHandle InHandle) override;`
- L18 _public prototype_ `virtual void Tick (float DeltaSeconds) override;`
- L19 _public prototype_ `virtual bool DumpStats() override;`
- L22 _public member_ `TMap<FString, FDirectoryWatchRequestLinux*> RequestMap;` — Map of directory paths to requests
- L23 _public member_ `TArray<FDirectoryWatchRequestLinux*> RequestsPendingDelete;`
- L26 _public member_ `int32 NumRequests;` — A count of FDirectoryWatchRequestLinux created to ensure they are cleaned up on shutdown

#### Free symbols / members of external scopes

- L29 _typedef_ `typedef FDirectoryWatcherLinux FDirectoryWatcher;`

### `Source/Developer/DirectoryWatcher/Private/Mac/DirectoryWatchRequestMac.h` (Private)


#### class `FDirectoryWatchRequestMac`  
`class FDirectoryWatchRequestMac`  
_L14-51_
- L17 _public prototype_ `FDirectoryWatchRequestMac();`
- L18 _public prototype_ `virtual ~FDirectoryWatchRequestMac();`
- L21 _public prototype_ `bool Init(const FString& InDirectory);` — Sets up the directory handle and request information
- L24 _public prototype_ `FDelegateHandle AddDelegate( const IDirectoryWatcher::FDirectoryChanged& InDelegate, uint32 Flags );` — Adds a delegate to get fired when the directory changes
- L26 _public prototype_ `bool RemoveDelegate( FDelegateHandle InHandle );` — Removes a delegate to get fired when the directory changes
- L28 _public prototype_ `bool HasDelegates() const;` — Returns true if this request has any delegates listening to directory changes
- L30 _public prototype_ `void EndWatchRequest();` — Prepares the request for deletion
- L32 _public prototype_ `void ProcessPendingNotifications();` — Triggers all pending file change notifications
- L36 _private member_ `FSEventStreamRef EventStream;`
- L37 _private member_ `bool bRunning;`
- L38 _private member_ `bool bEndWatchRequestInvoked;`
- L41 _private typedef_ `typedef TPair<IDirectoryWatcher::FDirectoryChanged, uint32> FWatchDelegate;` — A delegate with its corresponding IDirectoryWatcher::WatchOptions flags
- L42 _private member_ `TArray<FWatchDelegate> Delegates;`
- L44 _private member_ `TArray<TPair<FFileChangeData, bool>> FileChanges;` — Each FFileChangeData tracks whether it is a directory or not
- L45 _private member_ `FRWLock FileChangesLock;`
- L49 _private prototype_ `void ProcessChanges( size_t EventCount, void* EventPaths, const FSEventStreamEventFlags EventFlags[] );`
- L50 _private prototype_ `void Shutdown( void );`

### `Source/Developer/DirectoryWatcher/Private/Mac/DirectoryWatcherMac.h` (Private)


#### class `FDirectoryWatcherMac`  
`class FDirectoryWatcherMac : public IDirectoryWatcher`  
_L13-29_
- inherits: `IDirectoryWatcher`
- L16 _public prototype_ `FDirectoryWatcherMac();`
- L17 _public prototype_ `virtual ~FDirectoryWatcherMac();`
- L19 _public prototype_ `virtual bool RegisterDirectoryChangedCallback_Handle (const FString& Directory, const FDirectoryChanged& InDelegate, FDelegateHandle& OutHandle, uint32 Flags) override;`
- L20 _public prototype_ `virtual bool UnregisterDirectoryChangedCallback_Handle (const FString& Directory, FDelegateHandle InHandle) override;`
- L21 _public prototype_ `virtual void Tick (float DeltaSeconds) override;`
- L24 _public member_ `TMap<FString, FDirectoryWatchRequestMac*> RequestMap;` — Map of directory paths to requests
- L25 _public member_ `TArray<FDirectoryWatchRequestMac*> RequestsPendingDelete;`
- L28 _public member_ `int32 NumRequests;` — A count of FDirectoryWatchRequestMac created to ensure they are cleaned up on shutdown

#### Free symbols / members of external scopes

- L31 _typedef_ `typedef FDirectoryWatcherMac FDirectoryWatcher;`

### `Source/Developer/DirectoryWatcher/Private/Windows/DirectoryWatchRequestWindows.h` (Private)


#### class `FDirectoryWatchRequestWindows`  
`class FDirectoryWatchRequestWindows`  
_L11-67_
- L14 _public prototype_ `FDirectoryWatchRequestWindows(uint32 Flags);`
- L15 _public prototype_ `virtual ~FDirectoryWatchRequestWindows();`
- L18 _public prototype_ `bool Init(const FString& InDirectory);` — Sets up the directory handle and request information
- L21 _public prototype_ `FDelegateHandle AddDelegate( const IDirectoryWatcher::FDirectoryChanged& InDelegate );` — Adds a delegate to get fired when the directory changes
- L23 _public prototype_ `bool RemoveDelegate( FDelegateHandle InHandle );` — Removes a delegate to get fired when the directory changes
- L25 _public prototype_ `bool HasDelegates() const;` — Returns true if this request has any delegates listening to directory changes
- L27 _public prototype_ `HANDLE GetDirectoryHandle() const;` — Returns the file handle for the directory that is being watched
- L29 _public prototype_ `void EndWatchRequest();` — Closes the system resources and prepares the request for deletion
- L31 _public function_ `bool IsPendingDelete() const` — True if system resources have been closed and the request is ready for deletion
- L33 _public prototype_ `void ProcessPendingNotifications();` — Triggers all pending file change notifications
- L37 _private prototype_ `void ProcessChange(uint32 Error, uint32 NumBytes);` — Non-static handler for an OS notification of a directory change
- L38 _private prototype_ `void SetBufferByChangeCount(int32 MaxChanges);`
- L39 _private prototype_ `void SetBufferBySize(int32 BufferSize);`
- L42 _private prototype_ `static void CALLBACK ChangeNotification(::DWORD Error, ::DWORD NumBytes, LPOVERLAPPED InOverlapped);` — Static Handler for an OS notification of a directory change
- L44 _private member_ `FString Directory;`
- L45 _private member_ `HANDLE DirectoryHandle;`
- L46 _private member_ `int64 WatchStartedTimeStampHistory[2];`
- L47 _private member_ `uint32 NotifyFilter;`
- L48 _private member_ `uint32 BufferLength = 0;`
- L56 _private member_ `TUniquePtr<uint8, FDeleterFree> Buffer;`
- L57 _private member_ `TUniquePtr<uint8, FDeleterFree> BackBuffer;`
- L58 _private member_ `OVERLAPPED Overlapped;`
- L60 _private member_ `bool bPendingDelete;`
- L61 _private member_ `bool bEndWatchRequestInvoked;`
- L62 _private member_ `bool bBufferInUse = false;`
- L63 _private member_ `bool bWatchSubtree;`
- L65 _private member_ `TArray<IDirectoryWatcher::FDirectoryChanged> Delegates;`
- L66 _private member_ `TArray<FFileChangeData> FileChanges;`

#### struct `FDirectoryWatchRequestWindows::FDeleterFree`  
`struct FDeleterFree`  
_L49-55_
- L51 _public function_ `void operator()(uint8* Ptr) const`

### `Source/Developer/DirectoryWatcher/Private/Windows/DirectoryWatcherWindows.h` (Private)


#### class `FDirectoryWatcherWindows`  
`class FDirectoryWatcherWindows : public IDirectoryWatcher`  
_L13-32_
- inherits: `IDirectoryWatcher`
- L17 _private typedef_ `typedef TPair<FString, uint32> FDirectoryWithFlags;` — A directory and its associated IDirectoryWatcher::WatchOptions, which represents a unique ID for a watch request
- L19 _public prototype_ `FDirectoryWatcherWindows();`
- L20 _public prototype_ `virtual ~FDirectoryWatcherWindows();`
- L22 _public prototype_ `virtual bool RegisterDirectoryChangedCallback_Handle (const FString& Directory, const FDirectoryChanged& InDelegate, FDelegateHandle& OutHandle, uint32 Flags) override;`
- L23 _public prototype_ `virtual bool UnregisterDirectoryChangedCallback_Handle (const FString& Directory, FDelegateHandle InHandle) override;`
- L24 _public prototype_ `virtual void Tick (float DeltaSeconds) override;`
- L27 _public member_ `TMap<FDirectoryWithFlags, FDirectoryWatchRequestWindows*> RequestMap;` — Map of directory paths to requests
- L28 _public member_ `TArray<FDirectoryWatchRequestWindows*> RequestsPendingDelete;`
- L31 _public member_ `int32 NumRequests;` — A count of FDirectoryWatchRequestWindows created to ensure they are cleaned up on shutdown

#### Free symbols / members of external scopes

- L34 _typedef_ `typedef FDirectoryWatcherWindows FDirectoryWatcher;`

### `Source/Developer/DirectoryWatcher/Public/DirectoryWatcherModule.h` (Public)


#### class `FDirectoryWatcherModule`  
`class FDirectoryWatcherModule : public IModuleInterface`  
_L13-27_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule();`
- L17 _public prototype_ `virtual void ShutdownModule();`
- L20 _public prototype_ `virtual IDirectoryWatcher* Get();` — Gets the directory watcher singleton or returns NULL if the platform does not support directory watching
- L23 _public prototype_ `virtual void RegisterExternalChanges(TArrayView<const FFileChangeData> FileChanges) const;` — Register external changes that the OS file watcher couldn't detect (eg, a file changing in a UE sandbox)
- L26 _private member_ `FDirectoryWatcherProxy* DirectoryWatcher;`

### `Source/Developer/DirectoryWatcher/Public/FileCache.h` (Public)


#### struct `DirectoryWatcher::FFileCacheCustomVersion`  
`struct FFileCacheCustomVersion`  
_L37-41_
- desc: Custom serialization version for FFileCache
- L39 _public member_ `static const FGuid Key;`

#### enum `DirectoryWatcher::FFileCacheCustomVersion::Type`  
`enum Type`  
_L40-40_
- L40 _public enumerator_ `enum Type { Initial, IncludeFileHash, Latest = IncludeFileHash };`
- L40 _public enumerator_ `enum Type { Initial, IncludeFileHash, Latest = IncludeFileHash };`
- L40 _public enumerator_ `enum Type { Initial, IncludeFileHash, Latest = IncludeFileHash };`

#### struct `DirectoryWatcher::FFileData`  
`struct FFileData`  
_L44-81_
- desc: Structure representing specific information about a particular file
- L47 _public function_ `FFileData() : Timestamp(0)` — Constructiors
- L48 _public function_ `FFileData(const FDateTime& InTimestamp, const FMD5Hash& InFileHash) : Timestamp(InTimestamp), FileHash(InFileHash)`
- L77 _public member_ `FDateTime Timestamp;` — The cached timestamp of the file on disk
- L80 _public member_ `FMD5Hash FileHash;` — The cached MD5 hash of the file on disk

#### struct `DirectoryWatcher::FDirectoryState`  
`struct FDirectoryState`  
_L84-122_
- desc: Structure representing the file data for a number of files in a directory
- L87 _public function_ `FDirectoryState()` — Default construction
- L90 _public function_ `FDirectoryState(FDirectoryState&& In) : Rules(MoveTemp(In.Rules)), Files(MoveTemp(In.Files))` — Move construction
- L91 _public function_ `FDirectoryState& operator=(FDirectoryState&& In)`
- L94 _public member_ `FMatchRules Rules;` — The rules that define what this state applies to
- L97 _public member_ `TMap<FImmutableString, FFileData> Files;` — Filename -> data map

#### enum `DirectoryWatcher::EFileAction`  
`enum class EFileAction : uint8`  
_L124-127_
- L126 _public enumerator_ `Added`
- L126 _public enumerator_ `Added`
- L126 _public enumerator_ `Added`
- L126 _public enumerator_ `Added`

#### struct `DirectoryWatcher::FUpdateCacheTransaction`  
`struct FUpdateCacheTransaction`  
_L130-164_
- desc: A transaction issued by FFileCache to describe a change to the cache. The change is only committed once the transaction is returned to the cache (see FFileCache::CompleteTransaction).
- L133 _public member_ `FImmutableString Filename;` — The path of the file to which this transaction relates
- L136 _public member_ `FImmutableString MovedFromFilename;` — In the case of a moved file, this represents the path the file was moved from
- L139 _public member_ `FFileData FileData;` — File data pertaining to this change at the time of dispatch
- L142 _public member_ `EFileAction Action;` — The type of action that prompted this transaction
- L145 _public function_ `FUpdateCacheTransaction(FUpdateCacheTransaction&& In) : Filename(MoveTemp(In.Filename)), MovedFromFilename(MoveTemp(In.MovedFromFilename)), FileData(MoveTemp(In.FileData)), Action(MoveTemp(In.Action))` — Publically moveable
- L146 _public function_ `FUpdateCacheTransaction& operator=(FUpdateCacheTransaction&& In)`
- L152 _private function_ `FUpdateCacheTransaction(FImmutableString InFilename, EFileAction InAction, const FFileData& InFileData = FFileData()) : Filename(MoveTemp(InFilename)), FileData(InFileData), Action(InAction)` — Construction responsibility is held by FFileCache
- L157 _private function_ `FUpdateCacheTransaction(FImmutableString InMovedFromFilename, FImmutableString InMovedToFilename, const FFileData& InFileData) : Filename(MoveTemp(InMovedToFilename)), MovedFromFilename(MoveTemp(InMovedFromFilename)), FileData(InFileData), Action(EFileAction::Moved)` — Construction responsibility is held by FFileCache
- L162 _private prototype_ `FUpdateCacheTransaction(const FUpdateCacheTransaction&) = delete;` — Not Copyable
- L163 _private prototype_ `FUpdateCacheTransaction& operator=(const FUpdateCacheTransaction&) = delete;`

#### enum `DirectoryWatcher::EPathType`  
`enum EPathType`  
_L167-174_
- desc: Enum specifying whether a path should be relative or absolute
- L170 _public enumerator_ `Relative` — Paths should be cached relative to the root cache directory
- L173 _public enumerator_ `Absolute` — Paths should be cached as absolute file system paths

#### struct `DirectoryWatcher::IAsyncFileCacheTask`  
`struct IAsyncFileCacheTask : public TSharedFromThis<IAsyncFileCacheTask, ESPMode::ThreadSafe>`  
_L176-199_
- inherits: `TSharedFromThis<IAsyncFileCacheTask,ESPMode::ThreadSafe>`
- L183 _public function_ `IAsyncFileCacheTask() : StartTime(FPlatformTime::Seconds())`
- L184 _public prototype_ `virtual ~IAsyncFileCacheTask() = default;`
- L187 _public prototype_ `virtual EProgressResult Tick(const FTimeLimit& TimeLimit) = 0;` — Tick this task. Only to be called on the task thread.
- L190 _public prototype_ `virtual bool IsComplete() const = 0;` — Check whether this task is complete. Must be implemented in a thread-safe manner.
- L193 _public function_ `double GetAge() const` — Get the age of this task in seconds
- L198 _protected member_ `double StartTime;` — The time this task started

#### enum `DirectoryWatcher::IAsyncFileCacheTask::EProgressResult`  
`enum class EProgressResult`  
_L178-181_
- L180 _public enumerator_ `Finished`
- L180 _public enumerator_ `Finished`

#### struct `DirectoryWatcher::FFilenameAndHash`  
`struct FFilenameAndHash`  
_L202-209_
- desc: Simple struct that encapsulates a filename and its associated MD5 hash
- L204 _public member_ `FString AbsoluteFilename;`
- L205 _public member_ `FMD5Hash FileHash;`
- L207 _public function_ `FFilenameAndHash()`
- L208 _public function_ `FFilenameAndHash(const FString& File) : AbsoluteFilename(File)`

#### struct `DirectoryWatcher::FAsyncFileHasher`  
`struct FAsyncFileHasher : public IAsyncFileCacheTask`  
_L212-239_
- inherits: `IAsyncFileCacheTask`
- desc: Async task responsible for MD5 hashing a number of files, reporting completed hashes to the client when done
- L215 _public prototype_ `FAsyncFileHasher(TArray<FFilenameAndHash> InFilesThatNeedHashing);` — Constructor
- L218 _public prototype_ `TArray<FFilenameAndHash> GetCompletedData();` — Return any completed filenames and their corresponding hashes
- L221 _public prototype_ `virtual bool IsComplete() const override;` — Returns true when this task has finished hashing all its files
- L226 _protected prototype_ `virtual EProgressResult Tick(const FTimeLimit& Limit) override;` — Tick this reader (hashes as many files as possible in the time allowed). Returns progress state.
- L229 _protected member_ `TArray<FFilenameAndHash> Data;` — The array of data that we will process
- L232 _protected member_ `int32 NumReturned;` — The number of items we have returned to the client. Only accessed from the main thread.
- L235 _protected member_ `FThreadSafeCounter CurrentIndex;` — The number of files that we have hashed on the task thread. Atomic - safe to access from any thread.
- L238 _protected member_ `TArray<uint8> ScratchBuffer;` — Scratch buffer used for reading in files

#### struct `DirectoryWatcher::FAsyncDirectoryReader`  
`struct FAsyncDirectoryReader : public IAsyncFileCacheTask`  
_L253-329_
- inherits: `IAsyncFileCacheTask`
- desc: Class responsible for 'asynchronously' scanning a folder for files and timestamps. Example usage: FAsyncDirectoryReader Reader(TEXT("C:\\Path"), EPathType::Relative); while(!Reader.IsComplete()) { FPlatformProcess::Sleep(1); Reader.Tick(FTimedSignal(1));	// Do 1 second of work } TOptional<FDirectoryState> State = Reader.GetFinalState();
- L256 _public prototype_ `FAsyncDirectoryReader(const FString& InDirectory, EPathType InPathType);` — Constructor that sets up the directory reader to the specified directory
- L259 _public function_ `void SetMatchRules(const FMatchRules& InRules)` — Set what files are relevant to this reader. Calling this once the reader starts results in undefined behaviour.
- L271 _public prototype_ `TOptional<FDirectoryState> GetLiveState();` — Get the state of the directory once finished. Relinquishes the currently stored directory state to the client. Returns nothing if incomplete, or if GetLiveState() has already been called.
- L274 _public prototype_ `TOptional<FDirectoryState> GetCachedState();` — Retrieve the cached state supplied to this class through UseCachedState().
- L277 _public function_ `TArray<FFilenameAndHash> GetFilesThatNeedHashing()` — Retrieve the cached state supplied to this class through UseCachedState().
- L285 _public function_ `void UseCachedState(FDirectoryState InCachedState)` — Instruct the directory reader to use the specified cached state to lookup file hashes, where timestamps haven't changed
- L291 _public prototype_ `virtual bool IsComplete() const override;` — Returns true when this directory reader has finished scanning the directory
- L294 _public prototype_ `virtual EProgressResult Tick(const FTimeLimit& Limit) override;` — Tick this reader (discover new directories / files). Returns progress state.
- L298 _private prototype_ `void ScanDirectory(const FString& InDirectory);` — Non-recursively scan a single directory for its contents. Adds results to Pending arrays.
- L301 _private prototype_ `FString GetPathToStore(const FString& InPath) const;` — Returns version of path to store
- L304 _private member_ `FString RootPath;` — Path to the root directory we want to scan
- L307 _private member_ `FString StandardRootPath;` — Standardized path to the root directory we want to scan
- L310 _private member_ `EPathType PathType;` — Whether we should return relative or absolute paths
- L313 _private member_ `TOptional<FDirectoryState> LiveState;` — The currently discovered state of the directory - reset once relinquished to the client through GetLiveState
- L316 _private member_ `TOptional<FDirectoryState> CachedState;` — The previously cached  state of the directory, optional
- L319 _private member_ `TArray<FFilenameAndHash> FilesThatNeedHashing;` — An array of files that need hashing
- L322 _private member_ `TArray<FString> PendingDirectories;` — A list of directories we have recursively found on our travels
- L325 _private member_ `TArray<FString> PendingFiles;` — A list of files we have recursively found on our travels
- L328 _private member_ `FThreadSafeBool bIsComplete;` — Thread safe flag to signify when this class has finished reading

#### struct `DirectoryWatcher::FFileCacheConfig`  
`struct FFileCacheConfig`  
_L332-409_
- desc: Configuration structure required to construct a FFileCache
- L343 _public function_ `FFileCacheConfig(FString InDirectory, FString InCacheFile) : Directory(InDirectory), CacheFile(InCacheFile), PathType(EPathType::Relative), bDetectChangesSinceLastRun(false) , ChangeDetectionBits(false, 2)`
- L352 _public member_ `FString Directory;` — String specifying the directory on disk that the cache should reflect
- L355 _public member_ `FString CacheFile;` — String specifying the file that the cache should be saved to. When empty, no cache file will be maintained (thus only an in-memory cache is used)
- L358 _public member_ `FMatchRules Rules;` — List of rules which define what we will be watching
- L361 _public member_ `EPathType PathType;` — Path type to return, relative to the directory or absolute.
- L364 _public member_ `bool bDetectChangesSinceLastRun;` — When true, changes to the directory since the cache shutdown will be detected and reported. When false, said changes will silently be applied to the serialized cache.
- L367 _public member_ `TFunction<TOptional<bool>(const FImmutableString&, const FFileData&)> CustomChangeLogic;` — User-specified custom change detection logic. Called when a file's timestamp has been modified, to see if we should report this change to the client
- L370 _public function_ `FFileCacheConfig& DetectMoves(bool bInDetectMoves)` — Set up this cache to detect moves
- L381 _public function_ `FFileCacheConfig& RequireFileHashes(bool bInRequireFileHashes)` — Set up this cache to generate MD5 hashes for its constituent files
- L391 _public function_ `FFileCacheConfig& DetectChangesFor(EChangeDetection ChangeType, bool Value)` — Instruct the cache to report the specified changes to files
- L400 _private member_ `bool bDetectMoves;` — True to detect moves and renames (based on file hash), false otherwise. Implies bRequireFileHashes.
- L403 _private member_ `bool bRequireFileHashes;` — When true, the cache will also calculate MD5 hashes for files. When true, an additional thread will be launched on startup to harvest unknown MD5 hashes for the directory.
- L406 _private member_ `TBitArray<> ChangeDetectionBits;` — Bitfied specifying how we will be detecting changes. See EChangeDetection.

#### enum `DirectoryWatcher::FFileCacheConfig::EChangeDetection`  
`enum EChangeDetection`  
_L335-341_
- desc: Enum that specifies what changes are required for a change to be reported. When combined, any valid change is reported.
- L338 _public enumerator_ `Timestamp` — Report modifications when the timestamp of a file changes
- L340 _public enumerator_ `FileHash` — Report modifications when the contents of a file changes

#### class `DirectoryWatcher::FFileCache`  
`class FFileCache`  
_L416-552_
- desc: A class responsible for scanning a directory, and maintaining a cache of its state (files and timestamps). Changes in the cache can be retrieved through GetOutstandingChanges(). Changes will be reported for any change in the cached state even between runs of the process.
- L421 _public prototype_ `FFileCache(const FFileCacheConfig& InConfig);` — Construction from a config
- L423 _public prototype_ `FFileCache(const FFileCache&) = delete;`
- L424 _public prototype_ `FFileCache& operator=(const FFileCache&) = delete;`
- L427 _public prototype_ `~FFileCache();` — Destructor
- L430 _public prototype_ `void Destroy();` — Destroy this cache. Cleans out the in-memory state and deletes the cache file, if present.
- L433 _public function_ `const FString& GetDirectory() const` — Get the absolute path of the directory this cache reflects
- L436 _public prototype_ `bool HasStartedUp() const;` — Check whether this file cache has finished starting up yet. Does not imply rename/move detection is fully initialized. (see MoveDetectionInitialized())
- L439 _public prototype_ `bool MoveDetectionInitialized() const;` — Check whether this move/rename detection has been initiated or not. This can take much longer than startup, so can be checked separately
- L445 _public prototype_ `const FFileData* FindFileData(FImmutableString InFilename) const;` — Attempt to locate file data pertaining to the specified filename. @param		InFilename		The filename to find data for - either relative to the directory, or absolute, depending on Config.PathType. @return		The current cached file data pertaining to the specified filename, or nullptr. May not be completely up to date if there are outstanding transactions.
- L448 _public prototype_ `void Tick();` — Tick this FileCache
- L451 _public prototype_ `void WriteCache();` — Write out the cached file, if we have any changes to write
- L457 _public prototype_ `void CompleteTransaction(FUpdateCacheTransaction&& Transaction);` — Return a transaction to the cache for completion. Will update the cached state with the change described in the transaction, and mark the cache as needing to be saved.
- L460 _public prototype_ `void IgnoreNewFile(const FString& Filename);` — Report an external change to the manager, such that a subsequent equal change reported by the os be ignored
- L461 _public prototype_ `void IgnoreFileModification(const FString& Filename);`
- L462 _public prototype_ `void IgnoreMovedFile(const FString& SrcFilename, const FString& DstFilename);`
- L463 _public prototype_ `void IgnoreDeletedFile(const FString& Filename);`
- L466 _public function_ `int32 GetNumDirtyFiles() const` — Get the number of pending changes to the cache.
- L474 _public prototype_ `void IterateOutstandingChanges(TFunctionRef<bool(const FUpdateCacheTransaction&, const FDateTime&)> InPredicate) const;` — Iterate the number of pending changes to the cache with the specified predicate. Assumes Tick has been called (and thus, PendingTransactions is up-to-date) @param InIter		A predicate to match files against (returning true to continue iteration, false to break), based on: 1) the pending transaction 2) the time the change was detected
- L478 _public prototype_ `TArray<FUpdateCacheTransaction> FilterOutstandingChanges(TFunctionRef<bool(const FUpdateCacheTransaction&, const FDateTime&)> InPredicate);` — Get pending changes to the cache. Transactions must be returned to CompleteTransaction to update the cache. Filter predicate receives a transaction and the time the change was reported.
- L479 _public prototype_ `TArray<FUpdateCacheTransaction> GetOutstandingChanges();`
- L484 _private prototype_ `void OnDirectoryChanged(const TArray<FFileChangeData>& FileChanges);` — Called when the directory we are monitoring has been changed in some way
- L490 _private prototype_ `void DiffDirtyFiles(TMap<FImmutableString, FFileData>& InDirtyFiles, TArray<FUpdateCacheTransaction>& OutTransactions, const FDirectoryState* InFileSystemState = nullptr) const;` — Diff the specified set of dirty files (absolute paths, or relative to the monitor directory), adding transactions to the specified array if necessary. Optionally takes a directory state from which we can retrieve current file system state, without having to ask the FS directly. Optionally exclude files that have changed since the specified threshold, to ensure that related events get grouped together correctly.
- L493 _private prototype_ `void DetectRename();` — Detect a rename for the specified file
- L496 _private prototype_ `FString GetAbsolutePath(const FString& InTransactionPath) const;` — Get the absolute path from a transaction filename
- L499 _private prototype_ `TOptional<FString> GetTransactionPath(const FString& InAbsolutePath) const;` — Get the transaction path from an absolute filename. Returns nothing if the absolute path is invalid (not under the correct folder, or not applicable)
- L502 _private prototype_ `void UnbindWatcher();` — Unbind the watcher from the directory. Called on destruction.
- L505 _private prototype_ `TOptional<FDirectoryState> ReadCache() const;` — Read the cache file data and return the contents
- L508 _private prototype_ `void ReadStateFromAsyncReader();` — Called when the initial async reader has finished harvesting file system timestamps
- L511 _private prototype_ `void HarvestDirtyFileHashes();` — Called to harvest any file hashes that have been generated by the DirtyFileHasher thread task
- L512 _private prototype_ `void RescanForDirtyFileHashes();`
- L515 _private prototype_ `void UpdatePendingTransactions();` — Update our cache of pending transactions (to prevent diffing against the directory unnecessarily)
- L518 _private prototype_ `FString GetPathToStore(const FFilenameAndHash& InData) const;` — Returns version of path to store
- L523 _private member_ `FFileCacheConfig Config;` — Configuration settings applied on construction
- L526 _private member_ `TSharedPtr<FAsyncDirectoryReader, ESPMode::ThreadSafe> DirectoryReader;` — Asynchronous directory reader responsible for gathering all file/timestamp information recursively from our cache directory
- L528 _private member_ `TSharedPtr<FAsyncFileHasher, ESPMode::ThreadSafe> AsyncFileHasher;` — Asynchronous task used to harvest the MD5 hashes of a set of filenames
- L530 _private member_ `TSharedPtr<FAsyncFileHasher, ESPMode::ThreadSafe> DirtyFileHasher;` — Asynchronous task used to harvest the MD5 hashes of a set of recently changed filenames
- L533 _private member_ `TMap<FImmutableString, FFileData> DirtyFiles;` — A map of dirty files that we will use to report changes to the user. Timestamp value of FFileData here pertains to the *time of the change* not the timestamp of the file.
- L536 _private member_ `FDirectoryState CachedDirectoryState;` — Our in-memory view of the cached directory state.
- L539 _private member_ `FDelegateHandle WatcherDelegate;` — Handle to the directory watcher delegate so we can delete it properly
- L542 _private member_ `bool bSavedCacheDirty;` — True when the cached state we have in memory is more up to date than the serialized file. Enables WriteCache() when true.
- L545 _private member_ `double LastFileHashGetTime;` — The time we last retrieved file hashes from the thread
- L548 _private member_ `bool bPendingTransactionsDirty;` — List of cached pending transactions
- L549 _private member_ `TArray<FUpdateCacheTransaction> PendingTransactions;`
- L551 _private member_ `FString ConfigDirectoryStandardized;`

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API DIRECTORYWATCHER_API`
- L33 _namespace_ `namespace DirectoryWatcher`
- L50 _function_ `friend bool operator==(const FFileData& LHS, const FFileData& RHS)` (scope `DirectoryWatcher`)
- L55 _function_ `friend bool operator!=(const FFileData& LHS, const FFileData& RHS)` (scope `DirectoryWatcher`)
- L61 _function_ `friend FArchive& operator<<(FArchive& Ar, FFileData& Data)` (scope `DirectoryWatcher`) — Serializer for this type
- L100 _function_ `friend FArchive& operator<<(FArchive& Ar, FDirectoryState& State)` (scope `DirectoryWatcher`) — Serializer for this type

### `Source/Developer/DirectoryWatcher/Public/FileCacheUtilities.h` (Public)


#### struct `DirectoryWatcher::FImmutableString`  
`struct FImmutableString`  
_L25-80_
- desc: An immutable string with a cached CRC for efficient comparison with other strings
- L28 _public function_ `FImmutableString(FString InString = FString()) : String(MoveTemp(InString)), CachedHash(0)` — Constructible from a raw string
- L29 _public function_ `FImmutableString& operator=(FString InString)`
- L31 _public function_ `FImmutableString(const TCHAR* InString) : String(InString), CachedHash(0)`
- L32 _public function_ `FImmutableString& operator=(const TCHAR* InString)`
- L34 _public prototype_ `FImmutableString(const FImmutableString&) = default;`
- L35 _public prototype_ `FImmutableString& operator=(const FImmutableString&) = default;`
- L38 _public function_ `FImmutableString(FImmutableString&& In) : String(MoveTemp(In.String)), CachedHash(MoveTemp(In.CachedHash))` — Move construction/assignment
- L39 _public function_ `FImmutableString& operator=(FImmutableString&& In)`
- L58 _public function_ `const FString& Get() const` — Get the underlying string
- L76 _private member_ `FString String;` — The string itself.
- L79 _private member_ `mutable uint32 CachedHash;` — The cached hash of our string. 0 until compared with another string.

#### struct `DirectoryWatcher::FTimeLimit`  
`struct FTimeLimit`  
_L83-107_
- desc: A time limit that counts down from the time of construction, until it hits a given delay
- L86 _public function_ `FTimeLimit() : Delay(-1)` — Constructor specifying that we should never bail out early
- L89 _public function_ `FTimeLimit(float NumSeconds) : Delay(NumSeconds)` — Constructor specifying not to run over the specified number of seconds
- L92 _public function_ `bool IsValid() const` — Return true if this time limit has been set up, false otherwise
- L95 _public function_ `bool Exceeded() const` — Check whether we have exceeded the time limit
- L98 _public function_ `void Reset()` — Reset the time limit to start timing again from the current time
- L103 _private member_ `float Delay;` — The delay specified by the user
- L106 _private member_ `double StartTime;` — The time we started

#### struct `DirectoryWatcher::IMatchRule`  
`struct IMatchRule`  
_L110-117_
- desc: A rule that checks whether a file is applicable or not
- L113 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;` — Serialize this rule
- L116 _public prototype_ `virtual TOptional<bool> IsFileApplicable(const TCHAR* Filename) const = 0;` — Test to see if a file is applicable based on this rule. Returns true if so, false of not, or empty if the file doesn't match this rule.

#### struct `DirectoryWatcher::FMatchRules`  
`struct FMatchRules`  
_L120-167_
- desc: A set of rules that specifies what files we'll be watching
- L122 _public function_ `FMatchRules() : bDefaultIncludeState(true)`
- L125 _public prototype_ `void AddWildcardRule(const FWildcardString& WildcardString, bool bInclude);` — Specify a wildcard match to include or exclude
- L128 _public prototype_ `void SetApplicableExtensions(const FString& InExtensions);` — Specify a set of applicable extensions, ; separated. Provided as an optimization to early-out on files we're not interested in.
- L131 _public prototype_ `bool IsFileApplicable(const TCHAR* Filename) const;` — Check whether the specified file is applicable based on these rules or not
- L153 _private function_ `friend void operator<<(FArchive& Ar, FMatchRule& Rule)`
- L160 _private member_ `FString ApplicableExtensions;` — Optimization to ignore files that don't match the given set of extensions. Expected to be of the form ;ext1;ext2;ext3;
- L163 _private member_ `TArray<FMatchRule> Impls;` — Array of implementations
- L166 _private member_ `bool bDefaultIncludeState;` — Default inclusion state. True when only exclude rules exist, false if there are any Include rules

#### struct `DirectoryWatcher::FMatchRules::FMatchRule`  
`struct FMatchRule`  
_L143-157_
- desc: Implementation of a match rule, wrapping up its type, and implementation
- L147 _public member_ `TEnumAsByte<EType> Type;` — The type of this rule
- L149 _public member_ `TSharedPtr<IMatchRule> RuleImpl;` — The runtime implementation
- L152 _private prototype_ `void Serialize(FArchive& Ar);`

#### enum `DirectoryWatcher::FMatchRules::FMatchRule::EType`  
`enum EType`  
_L145-145_
- L145 _public enumerator_ `enum EType { Wildcard }; TEnumAsByte<EType> Type; TSharedPtr<IMatchRule> RuleImpl; private: void Serialize(FArchive& Ar);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace DirectoryWatcher`
- L22 _prototype_ `bool MatchExtensionString(const TCHAR* Filename, const TCHAR* Extensions);` (scope `DirectoryWatcher`) — Helper method to determine whether filename matches expected extensions
- L42 _function_ `friend bool operator==(const FImmutableString& A, const FImmutableString& B)` (scope `DirectoryWatcher`) — Check for equality with another immutable string (case-sensitive)
- L48 _function_ `friend uint32 GetTypeHash(const FImmutableString& In)` (scope `DirectoryWatcher`) — Calculate the type hash for this string
- L61 _function_ `friend FArchive& operator<<(FArchive& Ar, FImmutableString& InString)` (scope `DirectoryWatcher`) — Serialise this string
- L133 _function_ `friend void operator<<(FArchive& Ar, FMatchRules& Rules)` (scope `DirectoryWatcher`)

### `Source/Developer/DirectoryWatcher/Public/IDirectoryWatcher.h` (Public)


#### struct `FFileChangeData`  
`struct FFileChangeData`  
_L8-40_
- L19 _public function_ `FFileChangeData(const FString& InFilename, EFileChangeAction InAction) : Filename(InFilename) , Action(InAction)`
- L31 _public member_ `FString Filename;` — If the Action references a specific file, the name of the file. Applies To: FCA_Added, FCA_Modified, FCA_Removed, FCA_RescanRequired. For all other actions value will be emptystring.
- L37 _public member_ `int64 TimeStamp = 0;` — If the Action references a timestamp, the timezone UTC UnixTimeStamp (e.g. FDateTime::ToUnixTimeStamp) of the Action. Applies to: FCA_RescanRequired. For all other actions value will be 0.
- L39 _public member_ `EFileChangeAction Action = EFileChangeAction::FCA_Unknown;` — The reported Action.

#### enum `FFileChangeData::EFileChangeAction`  
`enum EFileChangeAction`  
_L10-17_
- L12 _public enumerator_ `FCA_Unknown`
- L13 _public enumerator_ `FCA_Added`
- L14 _public enumerator_ `FCA_Modified`
- L15 _public enumerator_ `FCA_Removed`
- L16 _public enumerator_ `FCA_RescanRequired`

#### class `IDirectoryWatcher`  
`class IDirectoryWatcher`  
_L44-96_
- desc: The public interface for the directory watcher singleton.
- L59 _public prototype_ `DECLARE_DELEGATE_OneParam(FDirectoryChanged, const TArray<struct FFileChangeData>& );` — A delegate to report directory changes
- L62 _public prototype_ `virtual ~IDirectoryWatcher() = default;` — Virtual destructor
- L72 _public prototype_ `virtual bool RegisterDirectoryChangedCallback_Handle (const FString& Directory, const FDirectoryChanged& InDelegate, FDelegateHandle& OutHandle, uint32 Flags = 0) = 0;` — Register a callback to fire when directories are changed @param	Directory to watch @param	Delegate to add to our callback list @param	The handle to the registered delegate, if the registration was successful. @param	Set of options to use when registering the delegates.
- L80 _public prototype_ `virtual bool UnregisterDirectoryChangedCallback_Handle (const FString& Directory, FDelegateHandle InHandle) = 0;` — Unregisters a callback to fire when directories are changed @param	Directory to stop watching @param	Handle to the delegate to remove from our callback list
- L85 _public function_ `virtual void Tick(float DeltaSeconds)` — Allows for subclasses to be ticked (by editor or other programs that need to tick the singleton)
- L92 _public function_ `virtual bool DumpStats()` — Allows for subclasses to dump notify statistics (returns true if implemented)

#### enum `IDirectoryWatcher::WatchOptions`  
`enum WatchOptions : uint32`  
_L49-56_
- desc: Options for a single watch (can be combined)
- L52 _public enumerator_ `IncludeDirectoryChanges = (1<<0)` — Whether to include notifications for changes to actual directories (such as directories being created or removed).
- L55 _public enumerator_ `IgnoreChangesInSubtree = (1<<1)` — Whether changes in subdirectories need to be reported.

#### Free symbols / members of external scopes

- L59 _delegate_ `DECLARE_DELEGATE_OneParam(FDirectoryChanged, const TArray<struct FFileChangeData>& );` — A delegate to report directory changes
