# CSharp / EpicGames.Perforce.Managed

- project root: `Source/Programs/Shared/EpicGames.Perforce.Managed`
- files: 12; symbols: 325
- symbol kinds: class=29, const=6, ctor=30, delegate=1, enum=4, enumerator=18, event=1, field=70, method=124, property=41, record=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Perforce.Managed/CachedFileInfo.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.CachedFileInfo`  
`class CachedFileInfo`  
_internal*; L16-79_
- attrs: `[DebuggerDisplay("{ContentId}")]`
- desc: Stores information about where a particular FileContentId has been staged, or its location in the cache
- L18 _public field_ `public readonly DirectoryReference CacheDir`
- L19 _public field_ `public readonly FileContentId ContentId`
- L20 _public field_ `public readonly ulong CacheId`
- L21 _public field_ `public readonly long Length`
- L22 _public field_ `public readonly long LastModifiedTicks`
- L23 _public field_ `public readonly bool ReadOnly`
- L24 _public field_ `public readonly uint SequenceNumber`
- L26-35 _public ctor_ `public CachedFileInfo(DirectoryReference cacheDir, FileContentId contentId, ulong cacheId, long length, long lastModifiedTicks, bool readOnly, uint sequenceNumber)`
- L37-64 _public method_ `public bool CheckIntegrity(ILogger logger)`
- L66-78 _public method_ `public FileReference GetLocation()`

#### class `EpicGames.Perforce.Managed.CachedFileInfoExtensions`  
`static class CachedFileInfoExtensions`  
_internal*; L81-108_
- L83-92 _public method_ `public static CachedFileInfo ReadCachedFileInfo(this MemoryReader reader, DirectoryReference cacheDir)`
- L94-102 _public method_ `public static void WriteCachedFileInfo(this MemoryWriter writer, CachedFileInfo fileInfo)`
- L104-107 _public method_ `public static int GetSerializedSize(this CachedFileInfo fileInfo)`

### `Source/Programs/Shared/EpicGames.Perforce.Managed/FileContentId.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.FileContentId`  
`public class FileContentId`  
_public; L13-51_
- attrs: `[DebuggerDisplay("{Digest} ({Type})")]`
- desc: Unique identifier for the content of a file
- L18-21 _public property_ `public Md5Hash Digest { get; }` — MD5 digest of the file
- L26-29 _public property_ `public Utf8String Type { get; }` — Type of the file
- L34-38 _public ctor_ `public FileContentId(Md5Hash digest, Utf8String type)` — Constructor
- L41-44 _public method_ `public override bool Equals(object? other)` — (inheritdoc)
- L47-50 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### class `EpicGames.Perforce.Managed.FileContentIdExtensions`  
`static class FileContentIdExtensions`  
_internal*; L53-72_
- L55-60 _public method_ `public static FileContentId ReadFileContentId(this MemoryReader reader)`
- L62-66 _public method_ `public static void WriteFileContentId(this MemoryWriter writer, FileContentId fileContentId)`
- L68-71 _public method_ `public static int GetSerializedSize(this FileContentId fileContentId)`

### `Source/Programs/Shared/EpicGames.Perforce.Managed/ManagedWorkspace.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.ManagedWorkspaceException`  
`public class ManagedWorkspaceException : Exception`  
_public; L24-32_
- inherits: `Exception`
- desc: Exception relating to managed workspace
- L29-31 _public ctor_ `public ManagedWorkspaceException(string message) : base(message)` — Constructor

#### class `EpicGames.Perforce.Managed.InsufficientSpaceException`  
`public class InsufficientSpaceException : ManagedWorkspaceException`  
_public; L37-47_
- inherits: `ManagedWorkspaceException`
- desc: Exception thrown when there is not enough free space on the drive
- L43-46 _public ctor_ `public InsufficientSpaceException(string message) : base(message)` — Constructor

#### class `EpicGames.Perforce.Managed.PopulateRequest`  
`public class PopulateRequest`  
_public; L52-81_
- desc: Information about a populate request
- L57 _public property_ `public IPerforceConnection PerforceClient { get; }` — The Perforce connection
- L62 _public property_ `public string StreamName { get; }` — Stream to sync it to
- L67 _public property_ `public IReadOnlyList<string> View { get; }` — View for this client
- L75-80 _public ctor_ `public PopulateRequest(IPerforceConnection perforceClient, string streamName, IReadOnlyList<string> view)` — Constructor

#### record `EpicGames.Perforce.Managed.ManagedWorkspaceOptions`  
`public record ManagedWorkspaceOptions ( int NumParallelSyncThreads, int MaxFileConcurrency, int MaxFileScanConcurrency, long MinScratchSpace, bool UseHaveTable, bool Partitioned, bool PreferNativeClient, bool UseModTime )`  
_public; L99-126_
- desc: Extra options for configuring ManagedWorkspace
- L112-122 _public ctor_ `public ManagedWorkspaceOptions(int? numParallelSyncThreads = null, int? maxFileConcurrency = null, int? maxFileScanConcurrency = null, long minScratchSpace = 50L * 1024, bool useHaveTable = true, bool partitioned = false, bool preferNativeClient = false, bool useModTime = false) : this( numParallelSyncThreads ?? GetDefaultThreadCount(4), maxFileConcurrency ?? GetDefaultThreadCount(4), maxFileScanConcurrency ?? GetDefaultThreadCount(4), minScratchSpace, useHaveTable, partitioned, preferNativeClient, useModTime)` — (inheritdoc)
- L124 _private* method_ `static int GetDefaultThreadCount(int defaultValue)`

#### enum `EpicGames.Perforce.Managed.ManagedWorkspaceVersion`  
`enum ManagedWorkspaceVersion`  
_internal*; L131-147_
- desc: Version number for managed workspace cache files
- L136 _public* enumerator_ `Initial = 2` — Initial version number
- L141 _public* enumerator_ `AddDigest = 3` — Including stream directory digests in workspace directories
- L146 _public* enumerator_ `AddDigestIoHash = 4` — Changing hash algorithm from SHA1 to IoHash

#### class `EpicGames.Perforce.Managed.ManagedWorkspace`  
`public class ManagedWorkspace`  
_public; L152-2558_
- desc: Represents a repository of streams and cached data
- L166 _private* const_ `const int CurrentSignature = ('W' << 24) | ('T' << 16) | 2` — The file signature and version. Update this to introduce breaking changes and ignore old repositories.
- L171 _private* property_ `static int CurrentVersion { get; }` — The current revision number for cache archives.
- L176 _private const_ `private const int UntrackedFileVersion = 1` — File format version for untracked state file
- L181 _private field_ `private readonly ManagedWorkspaceOptions _options` — Externally configurable options
- L186 _public const_ `public const int LatestChangeNumber = -1` — Constant for syncing the latest change number
- L191 _private* const_ `const string SignatureFileName = "Repository.sig"` — Name of the signature file for a repository. This
- L196 _private* const_ `const string DataFileName = "Repository.dat"` — Name of the main data file for a repository
- L201 _private* const_ `const string UntrackedStateFileName = "Untracked.dat"` — Name of the untracked state file for a repository
- L206 _private* field_ `readonly string _hostName` — Name of the host
- L211 _private* field_ `uint _nextSequenceNumber` — Incrementing number assigned to sequential operations that modify files. Used to age out files in the cache.
- L216 _private* field_ `bool _requiresRepair` — Whether a repair operation should be run on this workspace. Set whenever the state may be inconsistent.
- L221 _private* field_ `readonly Tracer _tracer` — Tracer
- L226 _private* field_ `readonly ILogger _logger` — The log output device
- L231 _private* field_ `readonly DirectoryReference _baseDir` — The root directory for the stash
- L236 _private* field_ `readonly DirectoryReference _cacheDir` — Root directory for storing cache files
- L241 _private* field_ `readonly DirectoryReference _workspaceDir` — Root directory for storing workspace files
- L246 _private* field_ `readonly Dictionary<string, ClientRecord> _createdClients = ...` — Set of clients that we're created. Used to avoid updating multiple times during one run.
- L246 _private* field_ `readonly Dictionary< _createdClients = []` — Set of clients that we're created. Used to avoid updating multiple times during one run.
- L251 _private* field_ `readonly HashSet<ulong> _cacheEntries = []` — Set of unique cache entries. We use this to ensure new names in the cache are unique.
- L256 _private* field_ `WorkspaceDirectoryInfo _workspace` — List of all the staged files
- L261 _private* field_ `Dictionary<FileContentId, CachedFileInfo> _contentIdToTrackedFile = ...` — All the files which are currently being tracked
- L261 _private* field_ `Dictionary< _contentIdToTrackedFile = []` — All the files which are currently being tracked
- L266 _public delegate_ `public delegate void OnCleanDelegate(int numFilesDeleted, int numDirsDeleted)` — Notification that a clean has been performed
- L271 _public event_ `public event OnCleanDelegate? OnClean` — Occurs when a clean operation has been performed.
- L282-303 _private ctor_ `private ManagedWorkspace(string hostName, uint nextSequenceNumber, DirectoryReference baseDir, ManagedWorkspaceOptions options, Tracer tracer, ILogger logger)` — Constructor
- L316-338 _public method_ `public static async Task<ManagedWorkspace> LoadOrCreateAsync(string hostName, DirectoryReference baseDir, bool overwrite, ManagedWorkspaceOptions options, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — Loads a repository from the given directory, or create it if it doesn't exist
- L375-395 _public method_ `public static async Task<ManagedWorkspace> CreateAsync(string hostName, DirectoryReference baseDir, ManagedWorkspaceOptions options, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — Creates a repository at the given location
- L402-417 _public method_ `public static bool Exists(DirectoryReference baseDir)` — Tests whether a repository exists in the given directory
- L428-467 _public method_ `public static async Task<ManagedWorkspace> LoadAsync(string hostName, DirectoryReference baseDir, ManagedWorkspaceOptions options, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — Loads a repository from disk
- L472-498 _private method_ `private async Task SaveAsync(TransactionState state, CancellationToken cancellationToken)` — Save the state of the repository
- L504-522 _private method_ `private async Task SaveUntrackedStateAsync(IPerforceConnection connection, bool containsUntrackedFiles, CancellationToken cancellationToken)` — Mark whether current repository in combination with P4 client contains untracked files Stores data in a file separate to the repository metadata as that can grow large (hundreds of megabytes)
- L529-557 _private method_ `private async Task<bool> LoadUntrackedStateAsync(IPerforceConnection connection, CancellationToken cancellationToken)` — Check if current repository in combination with P4 client contains untracked files If deserialization is not possible, assume the repo contains untracked files
- L567-583 _public method_ `public async Task CleanAsync(IPerforceConnection? perforce, bool removeUntracked, CancellationToken cancellationToken)` — Cleans the current workspace
- L590-661 _private method_ `private async Task CleanInternalAsync(bool removeUntracked, CancellationToken cancellationToken)` — Cleans the current workspace
- L666-680 _public method_ `public async Task ClearAsync(CancellationToken cancellationToken)` — Empties the staging directory of any staged files
- L685-711 _public method_ `public void Dump()` — Dumps the contents of the repository to the log for analysis
- L716-751 _public method_ `public async Task RepairCacheAsync(CancellationToken cancellationToken)` — Checks the integrity of the cache
- L756-763 _public method_ `public async Task RevertAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Cleans the current workspace
- L768-774 _private method_ `private async Task RunOptionalCacheRepairAsync(CancellationToken cancellationToken)` — Checks the _requiresRepair flag, and repairs/resets it if set.
- L781-807 _public method_ `public async Task PurgeAsync(long maxSize, CancellationToken cancellationToken)` — Shrink the size of the cache to the given size
- L815-818 _public method_ `public async Task SetupAsync(IPerforceConnection perforceClient, string streamName, CancellationToken cancellationToken)` — Configures the client for the given stream
- L823-926 _public method_ `public async Task StatsAsync(IPerforceConnection perforceClient, List<string> streamNames, List<string> view, CancellationToken cancellationToken)` — Prints stats showing coherence between different streams
- L931-966 _public method_ `public async Task StatusAsync()` — Prints information about the repository state
- L979-1054 _public method_ `public async Task SyncAsync(IPerforceConnection perforce, string streamName, int changeNumber, IReadOnlyList<string> view, bool removeUntracked, bool fakeSync, FileReference? cacheFile, CancellationToken cancellationToken)` — Switches to the given stream
- L1060-1154 _public method_ `public async Task UnshelveAsync(IPerforceConnection perforce, int unshelveChangelist, CancellationToken cancellationToken)` — Replays the effects of unshelving a changelist, but clobbering files in the workspace rather than actually unshelving them (to prevent problems with multiple machines locking them)
- L1159-1167 _public method_ `public async Task PopulateAsync(List<PopulateRequest> requests, bool fakeSync, CancellationToken cancellationToken)` — Populates the cache with the head revision of the given streams.
- L1172-1272 _public method_ `public async Task<Tuple<int, StreamSnapshot>[]> PopulateCleanAsync(List<PopulateRequest> requests, CancellationToken cancellationToken)` — Perform the clean part of a populate command
- L1277-1307 _public method_ `public async Task PopulateSyncAsync(List<PopulateRequest> requests, Tuple<int, StreamSnapshot>[] streamState, bool fakeSync, CancellationToken cancellationToken)` — Perform the sync part of a populate command
- L1319-1338 _public method_ `public async Task DeleteClientAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Deletes a client
- L1340-1392 _private method_ `private async Task<ClientRecord> GetOrCreateClientAsync(IPerforceConnection perforceClient, string streamName, CancellationToken cancellationToken)`
- L1400-1411 _private method_ `private async Task UpdateClientAsync(IPerforceConnection perforceClient, string streamName, CancellationToken cancellationToken)` — Sets the stream for the current client
- L1420-1427 _public method_ `public async Task<int> GetLatestChangeAsync(IPerforceConnection perforceClient, string streamName, CancellationToken cancellationToken)` — Gets the latest change submitted for the given stream
- L1435-1454 _private method_ `private async Task<int> GetLatestClientChangeAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Get the latest change number in the current client
- L1461-1500 _private method_ `private async Task RevertInternalAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Revert all files that are open in the current workspace. Does not replace them with valid revisions.
- L1507-1517 _private method_ `private async Task ClearClientHaveTableAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Clears the have table. This ensures that we'll always fetch the names of files at head revision, which aren't updated otherwise.
- L1526-1561 _private method_ `private async Task UpdateClientHaveTableAsync(IPerforceConnection perforceClient, int changeNumber, IReadOnlyList<string> view, CancellationToken cancellationToken)` — Updates the have table to reflect the given stream
- L1571-1585 _private method_ `private static async Task UpdateHaveTablePathAsync(IPerforceConnection perforceClient, string syncPath, Tracer tracer, CancellationToken cancellationToken)` — Update a path in the have table
- L1630-1760 _private method_ `private async Task<StreamSnapshotFromMemory> FindClientContentsAsync(IPerforceConnection perforceClient, int changeNumber, CancellationToken cancellationToken)` — Get the contents of the client, as synced.
- L1799-1865 _public method_ `public async Task<StreamSnapshotFromMemory> FindClientContentsWithoutHaveTableAsync(IPerforceConnection perforceClient, string streamName, IReadOnlyList<string> view, int changeNumber, CancellationToken cancellationToken)` — Get the contents of the client without using the have table
- L1874-1889 _private* method_ `async Task<StreamSnapshot?> TryLoadClientContentsAsync(FileReference cacheFile, Utf8String basePath, CancellationToken cancellationToken)` — Loads the contents of a client from disk
- L1901-1934 _private method_ `private async Task<StreamSnapshotFromMemory> FindAndSaveClientContentsAsync(IPerforceConnection perforceClient, Utf8String basePath, IReadOnlyList<string> view, int changeNumber, FileReference cacheFile, CancellationToken cancellationToken)` — Finds the contents of a workspace, and saves it to disk
- L1941-2031 _private method_ `private async Task RemoveFilesFromWorkspaceAsync(StreamSnapshot contents, CancellationToken cancellationToken)` — Remove files from the workspace
- L2033-2051 _private* method_ `ValueTask MoveFileToCache(FileContentId contentId, FileReference sourceFile, FileReference targetFile, Dictionary<FileContentId, CachedFileInfo> contentIdToTrackedFile, CancellationToken cancellationToken)`
- L2057-2068 _private* method_ `void RemoveFile(WorkspaceFileInfo fileToDelete)` — Helper function to delete a file from the workspace, and output any failure as a warning.
- L2074-2085 _private* method_ `void RemoveDirectory(string directoryToDelete)` — Helper function to delete a directory from the workspace, and output any failure as a warning.
- L2089 _private* method_ `static extern bool GetDiskFreeSpaceEx( string lpDirectoryName, out ulong lpFreeBytesAvailable, out ulong lpTotalNumberOfBytes, out ulong lpTotalNumberOfFreeBytes )` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)] [return: MarshalAs(UnmanagedType.Bool)]`
- L2103-2284 _private method_ `private async Task AddFilesToWorkspaceAsync(IPerforceConnection client, StreamSnapshot stream, bool fakeSync, CancellationToken cancellationToken)` — Update the workspace to match the given stream, syncing files and moving to/from the cache as necessary.
- L2297-2379 _private* method_ `async Task SyncBatchAsync(IPerforceConnection client, WorkspaceFileToSync[] filesToSync, int beginIdx, int endIdx, bool fakeSync, Stack<IPerforceConnection> connectionPool, CancellationToken cancellationToken)` — Syncs a batch of files
- L2386-2412 _private* method_ `void MoveFileFromCache(WorkspaceFileToMove fileToMove, ConcurrentQueue<WorkspaceFileToSync> filesToSync)` — Helper function to move a file from the cache into the workspace. If it fails, adds the file to a list to be synced.
- L2419-2432 _private* method_ `void CopyFileWithinWorkspace(WorkspaceFileToCopy fileToCopy, ConcurrentQueue<WorkspaceFileToSync> filesToSync)` — Helper function to copy a file within the workspace. If it fails, adds the file to a list to be synced.
- L2434-2439 _private* method_ `void RemoveTrackedFile(CachedFileInfo trackedFile)`
- L2441-2458 _private* method_ `void CreateCacheHierarchy()`
- L2465-2478 _private* method_ `ulong GetUniqueCacheId(FileContentId contentId)` — Determines a unique cache id for a file content id
- L2485-2495 _private* method_ `static string RemoveLeadingSlash(string path)` — Removes the leading slash from a path
- L2502-2505 _private method_ `private static FileReference GetBackupFile(FileReference targetFile)` — Gets the path to a backup file used while a new file is being written out
- L2511-2522 _public method_ `public static void BeginTransaction(FileReference targetFile)` — Begins a write transaction on the given file. Assumes only one process will be reading/writing at a time, but the operation can be interrupted.
- L2528-2532 _public method_ `public static void CompleteTransaction(FileReference targetFile)` — Mark a transaction on the given file as complete, and removes the backup file.
- L2538-2545 _public method_ `public static void RestoreBackup(FileReference targetFile)` — Restores the backup for a target file, if it exists. This allows recovery from an incomplete transaction.
- L2552-2555 _private method_ `private static IDisposable Trace(string operation)` — Creates a scoped trace object

#### enum `EpicGames.Perforce.Managed.ManagedWorkspace.TransactionState`  
`enum TransactionState`  
_private*; L157-161_
- desc: The current transaction state. Used to determine whether a repository needs to be cleaned on startup.
- L159 _public* enumerator_ `Dirty`
- L160 _public* enumerator_ `Clean`

#### class `EpicGames.Perforce.Managed.ManagedWorkspace.FStatIndexedRecord`  
`class FStatIndexedRecord`  
_private*; L1592-1622_
- desc: Optimized record definition for fstat calls when populating a workspace. Since there are so many files in a typical branch, the speed of serializing these records is crucial for performance. Rather than deseralizing everything, we filter to just the fields we need, and avoid any unnecessary conversions from their primitive data types.
- L1606 _public field_ `public static readonly string[] FieldNames = Enum.GetNames(typeof(Field))`
- L1607 _public field_ `public static readonly Utf8String[] Utf8FieldNames = Array.ConvertAll(FieldNames, x => new Utf8String(x))`
- L1609 _public property_ `public PerforceValue[] Values { get; }`
- L1611 _public property_ `public Utf8String DepotFile => ...`
- L1613 _public property_ `public Utf8String ClientFile => ...`
- L1615 _public property_ `public Utf8String HeadType => ...`
- L1617 _public property_ `public Utf8String HaveRev => ...`
- L1619 _public property_ `public long FileSize => ...`
- L1621 _public property_ `public Utf8String Digest => ...`

#### enum `EpicGames.Perforce.Managed.ManagedWorkspace.FStatIndexedRecord.Field`  
`enum Field`  
_private*; L1595-1604_
- L1597 _public* enumerator_ `code`
- L1598 _public* enumerator_ `depotFile`
- L1599 _public* enumerator_ `clientFile`
- L1600 _public* enumerator_ `headType`
- L1601 _public* enumerator_ `haveRev`
- L1602 _public* enumerator_ `fileSize`
- L1603 _public* enumerator_ `digest`

#### class `EpicGames.Perforce.Managed.ManagedWorkspace.FStatRecordWithoutHaveTable`  
`class FStatRecordWithoutHaveTable`  
_private*; L1762-1789_
- L1775 _public field_ `public static readonly string[] FieldNames = Enum.GetNames(typeof(Field))`
- L1776 _public field_ `public static readonly Utf8String[] Utf8FieldNames = Array.ConvertAll(FieldNames, x => new Utf8String(x))`
- L1778 _public property_ `public PerforceValue[] Values { get; }`
- L1780 _public property_ `public Utf8String DepotFile => ...`
- L1782 _public property_ `public Utf8String HeadType => ...`
- L1784 _public property_ `public int HeadRev => ...`
- L1786 _public property_ `public long FileSize => ...`
- L1788 _public property_ `public Utf8String Digest => ...`

#### enum `EpicGames.Perforce.Managed.ManagedWorkspace.FStatRecordWithoutHaveTable.Field`  
`enum Field`  
_private*; L1765-1773_
- L1767 _public* enumerator_ `code`
- L1768 _public* enumerator_ `depotFile`
- L1769 _public* enumerator_ `headType`
- L1770 _public* enumerator_ `headRev`
- L1771 _public* enumerator_ `fileSize`
- L1772 _public* enumerator_ `digest`

### `Source/Programs/Shared/EpicGames.Perforce.Managed/StreamSnapshot.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.StreamSnapshot`  
`public abstract class StreamSnapshot`  
_public; L10-28_
- desc: Interface for a stream snapshot
- L15 _public property_ `public static StreamSnapshot Empty => ...` — Empty snapshot instance
- L20 _public property_ `public abstract StreamTreeRef Root { get; }` — The root digest
- L27 _public method_ `public abstract StreamTree Lookup(StreamTreeRef treeRef)` — Lookup a directory by reference

#### class `EpicGames.Perforce.Managed.StreamSnapshotExtensions`  
`static class StreamSnapshotExtensions`  
_internal*; L33-61_
- desc: Extension methods for IStreamSnapshot
- L39-44 _public method_ `public static List<StreamFile> GetFiles(this StreamSnapshot snapshot)` — Get all the files in this directory
- L52-60 _private* method_ `static void AppendFiles(StreamSnapshot snapshot, StreamTreeRef treeRef, List<StreamFile> files)` — Append the contents of this directory and subdirectories to a list

### `Source/Programs/Shared/EpicGames.Perforce.Managed/StreamSnapshotFromMemory.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.StreamSnapshotFromMemory`  
`public class StreamSnapshotFromMemory : StreamSnapshot`  
_public; L16-149_
- inherits: `StreamSnapshot`
- desc: Stores the contents of a stream in memory
- L21 _private* field_ `static readonly byte[] s_currentSignature = [(byte)'W', (byte)'S', (byte)'D', 5]` — The current signature for saved directory objects
- L26 _public property_ `public override StreamTreeRef Root { get; }` — The root digest
- L31 _public property_ `public IReadOnlyDictionary<IoHash, CbObject> HashToTree { get; }` — Map of digest to directory
- L38-42 _public ctor_ `public StreamSnapshotFromMemory(StreamTreeRef root, Dictionary<IoHash, CbObject> hashToTree)` — Constructor
- L48-53 _public ctor_ `public StreamSnapshotFromMemory(StreamTreeBuilder builder)` — Constructor
- L61-69 _private* method_ `static IoHash EncodeObject(StreamTree tree, Dictionary<IoHash, CbObject> hashToTree)` — Serialize to a compact binary object
- L72-75 _public method_ `public override StreamTree Lookup(StreamTreeRef treeRef)` — (inheritdoc)
- L84-110 _public method_ `public static async Task<StreamSnapshotFromMemory?> TryLoadAsync(FileReference inputFile, Utf8String defaultBasePath, CancellationToken cancellationToken)` — Load a stream directory from a file on disk
- L117-148 _public method_ `public async Task SaveAsync(FileReference outputFile, Utf8String basePath)` — Saves the contents of this object to disk

### `Source/Programs/Shared/EpicGames.Perforce.Managed/StreamTree.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.StreamFile`  
`public class StreamFile`  
_public; L16-99_
- attrs: `[DebuggerDisplay("{Path}")]`
- desc: Metadata for a Perforce file
- L21 _public property_ `public Utf8String Path { get; }` — Depot path for this file
- L26 _public property_ `public long Length { get; }` — Length of the file, as reported by the server (actual size on disk may be different due to workspace options).
- L31 _public property_ `public FileContentId ContentId { get; }` — Unique identifier for the file content
- L36 _public property_ `public int Revision { get; }` — Revision number of the file
- L39 _private* field_ `static readonly Utf8String s_lengthField = new("len")`
- L40 _private* field_ `static readonly Utf8String s_digestField = new("dig")`
- L41 _private* field_ `static readonly Utf8String s_typeField = new("type")`
- L42 _private* field_ `static readonly Utf8String s_revisionField = new("rev")`
- L48-51 _public ctor_ `public StreamFile(string path, long length, FileContentId contentId, int revision) : this(new Utf8String(path), length, contentId, revision)` — Constructor
- L56-62 _public ctor_ `public StreamFile(Utf8String path, long length, FileContentId contentId, int revision)` — Constructor
- L70-80 _public ctor_ `public StreamFile(Utf8String path, CbObject field)` — Parse from a compact binary object
- L86-92 _public method_ `public void Write(CbWriter writer)` — Write this object to compact binary
- L95-98 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Perforce.Managed.StreamTreeRef`  
`public class StreamTreeRef`  
_public; L104-163_
- desc: Stores a reference to another tree
- L109 _public property_ `public Utf8String Path { get; set; }` — Base depot path for the directory
- L114 _public property_ `public IoHash Hash { get; set; }` — Hash of the tree
- L117 _private* field_ `static readonly Utf8String s_hashField = new("hash")`
- L125-129 _public ctor_ `public StreamTreeRef(Utf8String path, IoHash hash)` — Constructor
- L136-140 _public ctor_ `public StreamTreeRef(Utf8String path, CbObject field)` — Constructor
- L146-153 _public method_ `public IoHash ComputeHash()` — Gets the hash of this reference
- L159-162 _public method_ `public void Write(CbWriter writer)` — Serialize to a compact binary object

#### class `EpicGames.Perforce.Managed.StreamTree`  
`public class StreamTree`  
_public; L168-340_
- desc: Information about a directory within a stream
- L173 _public property_ `public Utf8String Path { get; }` — The path to this tree
- L178 _public property_ `public Dictionary<Utf8String, StreamFile> NameToFile { get; }` — Map of name to file within the directory
- L183 _public property_ `public Dictionary<Utf8String, StreamTreeRef> NameToTree { get; }` — Map of name to subdirectory
- L186 _private* field_ `static readonly Utf8String s_nameField = new("name")`
- L187 _private* field_ `static readonly Utf8String s_pathField = new("path")`
- L188 _private* field_ `static readonly Utf8String s_filesField = new("files")`
- L189 _private* field_ `static readonly Utf8String s_treesField = new("trees")`
- L195-197 _public ctor_ `public StreamTree()` — Default constructor
- L202-209 _public ctor_ `public StreamTree(Utf8String path, Dictionary<Utf8String, StreamFile> nameToFile, Dictionary<Utf8String, StreamTreeRef> nameToTree)` — Default constructor
- L214-242 _public ctor_ `public StreamTree(Utf8String path, CbObject @object)` — Deserialize a tree from a compact binary object
- L248-277 _public method_ `public void Write(CbWriter writer)` — Serialize to a compact binary object
- L286-298 _private* method_ `static Utf8String ReadPath(CbObject @object, Utf8String basePath, Utf8String name)` — Reads a path from an object, defaulting it to the parent path plus the child name
- L307-313 _private* method_ `static void WritePath(CbWriter writer, Utf8String path, Utf8String parentPath, Utf8String name)` — Writes a path if it's not the default (the parent path, a slash, followed by the child name)
- L320-326 _private* method_ `static void CheckPath(Utf8String path)` — Checks that a base path does not have a trailing slash
- L332-339 _public method_ `public CbObject ToCbObject()` — Convert to a compact binary object

### `Source/Programs/Shared/EpicGames.Perforce.Managed/StreamTreeBuilder.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.StreamTreeBuilder`  
`public class StreamTreeBuilder`  
_public; L12-123_
- desc: Utility class to efficiently track changes to a StreamTree object in memory
- L17 _public property_ `public Dictionary<Utf8String, StreamFile> NameToFile { get; }` — Map from name to mutable tree
- L22 _public property_ `public Dictionary<Utf8String, StreamTreeRef> NameToTree { get; }` — Map from name to mutable tree
- L27 _public property_ `public Dictionary<Utf8String, StreamTreeBuilder> NameToTreeBuilder { get; }` — Map from name to mutable tree
- L32 _public property_ `public bool IsEmpty => ...` — Tests whether the tree is empty
- L37-41 _public ctor_ `public StreamTreeBuilder()` — Constructor
- L47-51 _public ctor_ `public StreamTreeBuilder(StreamTree tree)` — Copy constructor
- L58-77 _public method_ `public StreamTree Encode(Func<StreamTree, IoHash> writeTree)` — Encodes the current tree state and returns a reference to it
- L84-88 _public method_ `public StreamTreeRef EncodeRef(Func<StreamTree, IoHash> writeTree)` — Encodes a StreamTreeRef from this tree
- L94-106 _public method_ `public void EncodeChildren(Func<StreamTree, IoHash> writeTree)` — Collapses all of the builders underneath this node
- L114-122 _private* method_ `static void AddBasePath(Dictionary<Utf8String, int> basePathToCount, Utf8String path, Utf8String name)` — Adds the base path of the given item to the count of similar items

#### class `EpicGames.Perforce.Managed.DepotStreamTreeBuilder`  
`public class DepotStreamTreeBuilder : StreamTreeBuilder`  
_public; L128-162_
- inherits: `StreamTreeBuilder`
- desc: Helper variant of StreamTreeBuilder capable of adding files to tree using both client and depot file paths
- L133-161 _public method_ `public void AddFile(string clientFile, StreamFile depotFile)` — Adds a file to the tree

### `Source/Programs/Shared/EpicGames.Perforce.Managed/StreamTreeReader.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.StreamTreeReader`  
`public abstract class StreamTreeReader`  
_public; L13-21_
- desc: Interface for
- L20 _public method_ `public abstract Task<StreamTree> ReadAsync(StreamTreeRef treeRef)` — Reads a node of the tree

#### class `EpicGames.Perforce.Managed.StreamTreeMemoryReader`  
`public class StreamTreeMemoryReader : StreamTreeReader`  
_public; L26-47_
- inherits: `StreamTreeReader`
- desc: Implements a StreamTreeReader using a contiguous block of memory
- L31 _private* field_ `readonly Dictionary<IoHash, CbObject> _hashToTree` — Map from hash to encoded CB tree object
- L31 _private* field_ `readonly Dictionary< _hashToTree` — Map from hash to encoded CB tree object
- L37-40 _public ctor_ `public StreamTreeMemoryReader(Dictionary<IoHash, CbObject> hashToTree)` — Constructor
- L43-46 _public method_ `public override Task<StreamTree> ReadAsync(StreamTreeRef treeRef)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Perforce.Managed/Transactions/AddTransaction.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.WorkspaceFileToMove`  
`class WorkspaceFileToMove`  
_internal*; L11-23_
- L13 _public field_ `public StreamFile _streamFile`
- L14 _public field_ `public CachedFileInfo _trackedFile`
- L15 _public field_ `public WorkspaceFileInfo _workspaceFile`
- L17-22 _public ctor_ `public WorkspaceFileToMove(StreamFile streamFile, CachedFileInfo trackedFile, WorkspaceFileInfo workspaceFile)`

#### class `EpicGames.Perforce.Managed.WorkspaceFileToCopy`  
`class WorkspaceFileToCopy`  
_internal*; L25-37_
- L27 _public field_ `public StreamFile _streamFile`
- L28 _public field_ `public WorkspaceFileInfo _sourceWorkspaceFile`
- L29 _public field_ `public WorkspaceFileInfo _targetWorkspaceFile`
- L31-36 _public ctor_ `public WorkspaceFileToCopy(StreamFile streamFile, WorkspaceFileInfo sourceWorkspaceFile, WorkspaceFileInfo targetWorkspaceFile)`

#### class `EpicGames.Perforce.Managed.WorkspaceFileToSync`  
`class WorkspaceFileToSync`  
_internal*; L39-49_
- L41 _public field_ `public StreamFile _streamFile`
- L42 _public field_ `public WorkspaceFileInfo _workspaceFile`
- L44-48 _public ctor_ `public WorkspaceFileToSync(StreamFile streamFile, WorkspaceFileInfo workspaceFile)`

#### class `EpicGames.Perforce.Managed.AddTransaction`  
`class AddTransaction`  
_internal*; L51-183_
- L53 _public field_ `public WorkspaceDirectoryInfo _newWorkspaceRootDir`
- L54 _public field_ `public StreamSnapshot _streamSnapshot`
- L55 _public field_ `public ConcurrentDictionary<CachedFileInfo, WorkspaceFileToMove> _filesToMove = ...`
- L55 _public field_ `public ConcurrentDictionary< _filesToMove = new()`
- L56 _public field_ `public ConcurrentQueue<WorkspaceFileToCopy> _filesToCopy = new()`
- L57 _public field_ `public ConcurrentQueue<WorkspaceFileToSync> _filesToSync = new()`
- L58 _private* field_ `readonly Dictionary<FileContentId, CachedFileInfo> _contentIdToTrackedFile`
- L58 _private* field_ `readonly Dictionary< _contentIdToTrackedFile`
- L59 _private* field_ `readonly Dictionary<FileContentId, WorkspaceFileInfo> _contentIdToWorkspaceFile = ...`
- L59 _private* field_ `readonly Dictionary< _contentIdToWorkspaceFile = []`
- L61-73 _private ctor_ `private AddTransaction(WorkspaceDirectoryInfo workspaceRootDir, StreamSnapshot streamSnapshot, Dictionary<FileContentId, CachedFileInfo> contentIdToTrackedFile)`
- L75-82 _public method_ `public static async Task<AddTransaction> CreateAsync(WorkspaceDirectoryInfo workspaceRootDir, StreamSnapshot streamSnapshot, Dictionary<FileContentId, CachedFileInfo> contentIdToTrackedFile, int numWorkers)`
- L84-117 _private* method_ `async Task MergeDirectoryAsync(WorkspaceDirectoryInfo workspaceDir, WorkspaceDirectoryInfo newWorkspaceDir, StreamTreeRef streamTreeRef, AsyncThreadPoolWorkQueue queue)`
- L119-135 _private* method_ `async Task AddDirectoryAsync(WorkspaceDirectoryInfo newWorkspaceDir, StreamTreeRef streamTreeRef, AsyncThreadPoolWorkQueue queue)`
- L137-142 _private* method_ `async Task MergeSubDirectoryAsync(Utf8String name, WorkspaceDirectoryInfo workspaceSubDir, StreamTreeRef streamSubTreeRef, WorkspaceDirectoryInfo newWorkspaceDir, AsyncThreadPoolWorkQueue queue)`
- L144-149 _private* method_ `async Task AddSubDirectoryAsync(Utf8String name, WorkspaceDirectoryInfo newWorkspaceDir, StreamTreeRef streamSubTreeRef, AsyncThreadPoolWorkQueue queue)`
- L151-182 _private* method_ `void AddFile(WorkspaceDirectoryInfo newWorkspaceDir, Utf8String name, StreamFile streamFile)`

### `Source/Programs/Shared/EpicGames.Perforce.Managed/Transactions/RemoveTransaction.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.RemoveTransaction`  
`class RemoveTransaction`  
_internal*; L10-98_
- L12 _private* field_ `readonly Dictionary<FileContentId, CachedFileInfo> _contentIdToTrackedFile`
- L12 _private* field_ `readonly Dictionary< _contentIdToTrackedFile`
- L14 _public field_ `public WorkspaceDirectoryInfo _newWorkspaceRootDir`
- L15 _public field_ `public StreamSnapshot _streamSnapshot`
- L16 _public field_ `public ConcurrentDictionary<FileContentId, WorkspaceFileInfo> _filesToMove = ...`
- L16 _public field_ `public ConcurrentDictionary< _filesToMove = new()`
- L17 _public field_ `public ConcurrentQueue<WorkspaceFileInfo> _filesToDelete = new()`
- L18 _public field_ `public ConcurrentQueue<WorkspaceDirectoryInfo> _directoriesToDelete = new()`
- L20-25 _public ctor_ `public RemoveTransaction(WorkspaceDirectoryInfo workspaceRootDir, StreamSnapshot streamSnapshot, Dictionary<FileContentId, CachedFileInfo> contentIdToTrackedFile)`
- L27-35 _public method_ `public static async Task<RemoveTransaction> CreateAsync(WorkspaceDirectoryInfo workspaceRootDir, StreamSnapshot streamSnapshot, Dictionary<FileContentId, CachedFileInfo> contentIdToTrackedFile, int numWorkers)`
- L37-68 _private* method_ `async Task MergeAsync(WorkspaceDirectoryInfo workspaceDir, WorkspaceDirectoryInfo newWorkspaceDir, StreamTreeRef streamTreeRef, AsyncThreadPoolWorkQueue queue)`
- L70-75 _private* method_ `async Task MergeSubDirectoryAsync(Utf8String name, WorkspaceDirectoryInfo newWorkspaceDir, WorkspaceDirectoryInfo workspaceSubDir, StreamTreeRef streamSubTreeRef, AsyncThreadPoolWorkQueue queue)`
- L77-89 _private* method_ `async Task RemoveDirectoryAsync(WorkspaceDirectoryInfo workspaceDir, AsyncThreadPoolWorkQueue queue)`
- L91-97 _private* method_ `void RemoveFile(WorkspaceFileInfo workspaceFile)`

### `Source/Programs/Shared/EpicGames.Perforce.Managed/WorkspaceDirectoryInfo.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.WorkspaceDirectoryInfo`  
`class WorkspaceDirectoryInfo`  
_internal*; L17-328_
- desc: Stores the state of a directory in the workspace
- L22 _public property_ `public WorkspaceDirectoryInfo? ParentDirectory { get; }` — The parent directory
- L27 _public property_ `public Utf8String Name { get; }` — Name of this directory
- L32 _public property_ `public IoHash StreamDirectoryDigest { get; set; }` — Digest of the matching stream directory info with the base path. This should be set to zero if the workspace is modified.
- L37 _public property_ `public Dictionary<Utf8String, WorkspaceFileInfo> NameToFile { get; set; }` — Map of name to file
- L42 _public property_ `public Dictionary<Utf8String, WorkspaceDirectoryInfo> NameToSubDirectory { get; set; }` — Map of name to subdirectory
- L48-51 _public ctor_ `public WorkspaceDirectoryInfo(DirectoryReference rootDir) : this(null, new Utf8String(rootDir.FullName), null)` — Constructor
- L59-66 _public ctor_ `public WorkspaceDirectoryInfo(WorkspaceDirectoryInfo? parentDirectory, Utf8String name, StreamTreeRef? treeRef)` — Constructor
- L76-98 _public method_ `public void AddFile(Utf8String path, long length, long lastModifiedTicks, bool readOnly, FileContentId contentId)` — Adds a file to the workspace
- L104-109 _public method_ `public List<WorkspaceFileInfo> GetFiles()` — Create a flat list of files in this workspace
- L115-123 _private method_ `private void GetFilesInternal(List<WorkspaceFileInfo> files)` — Internal helper method for recursing through the tree to build a file list
- L130-138 _public method_ `public async Task<(FileInfo[] filesToDelete, DirectoryInfo[] directoriesToDelete)> RefreshAsync(bool removeUntracked, int numWorkers)` — Refresh the state of the workspace on disk
- L148-208 _private* method_ `async Task RefreshAsync(DirectoryInfo info, bool removeUntracked, ConcurrentQueue<FileInfo> filesToDelete, ConcurrentQueue<DirectoryInfo> directoriesToDelete, AsyncThreadPoolWorkQueue queue)` — Recursive method for querying the workspace state
- L214-221 _public method_ `public async Task<string[]> FindDifferencesAsync(int numWorkers)` — Builds a list of differences from the working directory
- L230-273 _private* method_ `async Task FindDifferencesAsync(DirectoryInfo directory, string path, ConcurrentQueue<string> paths, AsyncThreadPoolWorkQueue queue)` — Helper method for finding differences from the working directory
- L279-284 _public method_ `public string GetFullName()` — Get the full path to this directory
- L290-293 _public method_ `public DirectoryReference GetLocation()` — Get the path to this directory
- L299-307 _public method_ `public void AppendClientPath(StringBuilder builder)` — Append the client path, using native directory separators, to the given string builder
- L313-321 _public method_ `public void AppendFullPath(StringBuilder builder)` — Append the path for this directory to the given string builder
- L324-327 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Perforce.Managed.WorkspaceDirectoryInfoExtensions`  
`static class WorkspaceDirectoryInfoExtensions`  
_internal*; L333-391_
- desc: Extension methods for WorkspaceDirectoryInfo
- L335-367 _public method_ `public static void ReadWorkspaceDirectoryInfo(this MemoryReader reader, WorkspaceDirectoryInfo directoryInfo, ManagedWorkspaceVersion version)`
- L369-385 _public method_ `public static void WriteWorkspaceDirectoryInfo(this MemoryWriter writer, WorkspaceDirectoryInfo directoryInfo)`
- L387-390 _public method_ `public static int GetSerializedSize(this WorkspaceDirectoryInfo directoryInfo)`

### `Source/Programs/Shared/EpicGames.Perforce.Managed/WorkspaceFileInfo.cs` (EpicGames.Perforce.Managed)


#### class `EpicGames.Perforce.Managed.WorkspaceFileInfo`  
`class WorkspaceFileInfo`  
_internal*; L12-92_
- desc: Stores information about a file that has been staged into a workspace
- L14 _public field_ `public readonly WorkspaceDirectoryInfo Directory`
- L15 _public field_ `public readonly Utf8String Name`
- L16 _public field_ `public long _length`
- L17 _public field_ `public long _lastModifiedTicks`
- L18 _public field_ `public bool _readOnly`
- L19 _public field_ `public readonly FileContentId ContentId`
- L21-26 _public ctor_ `public WorkspaceFileInfo(WorkspaceDirectoryInfo directory, Utf8String name, FileContentId contentId)`
- L28-31 _public ctor_ `public WorkspaceFileInfo(WorkspaceDirectoryInfo directory, Utf8String name, FileInfo info, FileContentId contentId) : this(directory, name, info.Length, info.LastWriteTimeUtc.Ticks, info.Attributes.HasFlag(FileAttributes.ReadOnly), contentId)`
- L33-41 _public ctor_ `public WorkspaceFileInfo(WorkspaceDirectoryInfo directory, Utf8String name, long length, long lastModifiedTicks, bool readOnly, FileContentId contentId)`
- L43-48 _public method_ `public void SetMetadata(long length, long lastModifiedTicks, bool readOnly)`
- L50-59 _public method_ `public void UpdateMetadata()`
- L61-64 _public method_ `public bool MatchesAttributes(FileInfo info)`
- L66-72 _public method_ `public string GetClientPath()`
- L74-81 _public method_ `public string GetFullName()`
- L83-86 _public method_ `public FileReference GetLocation()`
- L88-91 _public method_ `public override string ToString()`

#### class `EpicGames.Perforce.Managed.WorkspaceFileInfoExtensions`  
`static class WorkspaceFileInfoExtensions`  
_internal*; L94-119_
- L96-104 _public method_ `public static WorkspaceFileInfo ReadWorkspaceFileInfo(this MemoryReader reader, WorkspaceDirectoryInfo directory)`
- L106-113 _public method_ `public static void WriteWorkspaceFileInfo(this MemoryWriter writer, WorkspaceFileInfo fileInfo)`
- L115-118 _public method_ `public static int GetSerializedSize(this WorkspaceFileInfo fileInfo)`
