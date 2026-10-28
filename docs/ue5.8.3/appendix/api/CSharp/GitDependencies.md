# CSharp / GitDependencies

- project root: `Source/Programs/GitDependencies`
- files: 8; symbols: 199
- symbol kinds: class=17, const=4, ctor=6, delegate=1, enum=1, enumerator=3, field=87, method=68, property=10, struct=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/GitDependencies/DependencyManifest.cs` (GitDependencies)


#### class `GitDependencies.DependencyFile`  
`public class DependencyFile`  
_public; L19-39_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Contains information about a binary dependency in the workspace
- L25 _public field_ `public string Name = null!` — attrs: `[XmlAttribute]` — Name of the file, relative to the root. Directories are separated with forward slashes, without a leading slash.
- L31 _public field_ `public string Hash = null!` — attrs: `[XmlAttribute]` — Hash of this file. Used to determine which blob represents its contents.
- L38 _public field_ `public bool IsExecutable` — attrs: `[XmlAttribute] [DefaultValue(false)]` — Whether this file should have the exectuable bit set, on platforms that support it.

#### class `GitDependencies.DependencyBlob`  
`public class DependencyBlob`  
_public; L45-70_
- attrs: `[DebuggerDisplay("{Hash}")]`
- desc: Represents a hashed binary blob of data.
- L51 _public field_ `public string Hash = null!` — attrs: `[XmlAttribute]` — Hash of the blob.
- L57 _public field_ `public long Size` — attrs: `[XmlAttribute]` — Size of the blob.
- L63 _public field_ `public string PackHash = null!` — attrs: `[XmlAttribute]` — Hash of the pack file containing this blob.
- L69 _public field_ `public long PackOffset` — attrs: `[XmlAttribute]` — Offset of this blob's data within the pack file.

#### class `GitDependencies.DependencyPack`  
`public class DependencyPack`  
_public; L76-101_
- attrs: `[DebuggerDisplay("{Hash}")]`
- desc: A downloadable data file which can contain several blobs.
- L82 _public field_ `public string Hash = null!` — attrs: `[XmlAttribute]` — Hash of this pack file.
- L88 _public field_ `public long Size` — attrs: `[XmlAttribute]` — Size of this pack file, when uncompressed.
- L94 _public field_ `public long CompressedSize` — attrs: `[XmlAttribute]` — Compressed size of this pack file.
- L100 _public field_ `public string RemotePath = null!` — attrs: `[XmlAttribute]` — Subdirectory for this pack file on the remote server.

#### class `GitDependencies.DependencyManifest`  
`public class DependencyManifest`  
_public; L106-138_
- desc: A manifest for dependencies that should be unpacked into the workspace at a given revision.
- L112 _public field_ `public string BaseUrl = "http://cdn.unrealengine.com/dependencies"` — attrs: `[XmlAttribute]` — Base URL for downloading pack files from.
- L119 _public field_ `public bool IgnoreProxy` — attrs: `[XmlAttribute] [DefaultValue(false)]` — Whether to ignore proxy servers when downloading files from this remote.
- L125 _public field_ `public DependencyFile[] Files = new DependencyFile[0]` — attrs: `[XmlArrayItem("File")]` — Files which should be extracted into the workspace.
- L131 _public field_ `public DependencyBlob[] Blobs = new DependencyBlob[0]` — attrs: `[XmlArrayItem("Blob")]` — All the blobs required for entries in the Files array.
- L137 _public field_ `public DependencyPack[] Packs = new DependencyPack[0]` — attrs: `[XmlArrayItem("Pack")]` — All the packs required for entries in the Blobs array

### `Source/Programs/GitDependencies/ForkReadStream.cs` (GitDependencies)


#### class `GitDependencies.ForkReadStream`  
`class ForkReadStream : Stream`  
_internal*; L11-97_
- inherits: `Stream`
- L13 _private* field_ `Stream? Inner`
- L14 _private* field_ `Stream? ForkWrite`
- L16-20 _public ctor_ `public ForkReadStream(Stream? InInner, Stream? InForkWrite)`
- L22-34 _protected method_ `protected override void Dispose(bool Disposing)`
- L36-39 _public property_ `public override bool CanRead { get; }`
- L41-44 _public property_ `public override bool CanWrite { get; }`
- L46-49 _public property_ `public override bool CanSeek { get; }`
- L51-61 _public property_ `public override long Position { get; set; }`
- L63-66 _public property_ `public override long Length { get; }`
- L68-71 _public method_ `public override void SetLength(long Value)`
- L73-81 _public method_ `public override int Read(byte[] Buffer, int Offset, int Count)`
- L83-86 _public method_ `public override void Write(byte[] Buffer, int Offset, int Count)`
- L88-91 _public method_ `public override long Seek(long Offset, SeekOrigin Origin)`
- L93-96 _public method_ `public override void Flush()`

### `Source/Programs/GitDependencies/IgnoreFile.cs` (GitDependencies)


#### class `GitDependencies.IgnoreFile`  
`class IgnoreFile`  
_internal*; L10-73_
- L12 _private* field_ `List<Tuple<Regex, bool>> Patterns = ...`
- L12 _private* field_ `List<Tuple< Patterns = new List<Tuple<Regex, bool>>()`
- L14-16 _public ctor_ `public IgnoreFile(string FileName) : this(File.ReadAllLines(FileName))`
- L18-53 _public ctor_ `public IgnoreFile(string[] Lines)`
- L55-72 _public method_ `public bool IsExcludedFile(string FilePath)`

### `Source/Programs/GitDependencies/Log.cs` (GitDependencies)


#### class `GitDependencies.Log`  
`static class Log`  
_internal*; L11-79_
- L13 _private* field_ `static string CurrentStatus = ""`
- L15-19 _public method_ `public static void WriteLine()`
- L21-25 _public method_ `public static void WriteLine(string Line)`
- L27-31 _public method_ `public static void WriteLine(string Format, params object[] Args)`
- L33-39 _public method_ `public static void WriteError(string Format, params object[] Args)`
- L41-64 _public method_ `public static void WriteStatus(string Status)`
- L66-69 _public method_ `public static void WriteStatus(string Format, params object[] Args)`
- L71-78 _public method_ `public static void FlushStatus()`

### `Source/Programs/GitDependencies/NotifyReadStream.cs` (GitDependencies)


#### class `GitDependencies.NotifyReadStream`  
`class NotifyReadStream : Stream`  
_internal*; L13-94_
- inherits: `Stream`
- L15 _private* field_ `Stream? Inner`
- L16 _private* field_ `NotifyReadDelegate NotifyRead`
- L17 _private* field_ `long TotalRead`
- L19-24 _public ctor_ `public NotifyReadStream(Stream? InInner, NotifyReadDelegate InNotifyRead)`
- L26-33 _protected method_ `protected override void Dispose(bool Disposing)`
- L35-38 _public property_ `public override bool CanRead { get; }`
- L40-43 _public property_ `public override bool CanWrite { get; }`
- L45-48 _public property_ `public override bool CanSeek { get; }`
- L50-60 _public property_ `public override long Position { get; set; }`
- L62-65 _public property_ `public override long Length { get; }`
- L67-70 _public method_ `public override void SetLength(long Value)`
- L72-78 _public method_ `public override int Read(byte[] Buffer, int Offset, int Count)`
- L80-83 _public method_ `public override void Write(byte[] Buffer, int Offset, int Count)`
- L85-88 _public method_ `public override long Seek(long Offset, SeekOrigin Origin)`
- L90-93 _public method_ `public override void Flush()`

#### Namespace-level symbols

- L11 _private* delegate_ `delegate void NotifyReadDelegate(int SizeRead)`

### `Source/Programs/GitDependencies/Program.cs` (GitDependencies)


#### class `GitDependencies.Program`  
`class Program`  
_internal*; L22-1669_
- L84 _private* const_ `const string IncomingFileSuffix = ".incoming"`
- L85 _private* const_ `const string TempManifestExtension = ".tmp"`
- L87 _private* const_ `const string ManifestFilename = ".uedependencies"`
- L88 _private* const_ `const string LegacyManifestFilename = ".ue4dependencies"`
- L90 _private* field_ `static readonly string InstanceSuffix = Guid.NewGuid().ToString().Replace("-", "")`
- L91 _private* field_ `static HttpClient? HttpClientInstance = null`
- L93-243 _private* method_ `static int Main(string[] Args)`
- L245-254 _private* method_ `static void NormalizeArguments(List<string> ArgsList)`
- L256-286 _private* method_ `static List<string> SplitArguments(string? Text)`
- L288-299 _private* method_ `static bool ParseSwitch(List<string> ArgsList, string Name)`
- L301-314 _private* method_ `static string? ParseParameter(List<string> ArgsList, string Prefix, string? Default)`
- L316-319 _private* method_ `static string? ParseParameter(List<string> ArgsList, List<string> DefaultArgsList, string Prefix, string? Default)`
- L321-333 _private* method_ `static int ParseIntParameter(List<string> ArgsList, string Prefix, int Default)`
- L335-338 _private* method_ `static int ParseIntParameter(List<string> ArgsList, List<string> DefaultArgsList, string Prefix, int Default)`
- L340-352 _private* method_ `static float ParseFloatParameter(List<string> ArgsList, string Prefix, float Default)`
- L354-357 _private* method_ `static float ParseFloatParameter(List<string> ArgsList, List<string> DefaultArgsList, string Prefix, float Default)`
- L359-370 _private* method_ `static IEnumerable<string> ParseParameters(List<string> ArgsList, string Prefix)`
- L372-696 _private* method_ `static bool UpdateWorkingTree(bool bDryRun, string RootPath, HashSet<string> ExcludeFolders, int NumThreads, double HttpTimeoutMultiplier, int MaxRetries, Uri? Proxy, OverwriteMode Overwrite, string CachePath, float CacheSizeMultiplier, int CacheDays)`
- L698-719 _private* method_ `static bool AddPluginManifests(Dictionary<string, DependencyFile> TargetFiles, Dictionary<string, DependencyBlob> TargetBlobs, Dictionary<string, DependencyPackInfo> TargetPacks, string PluginsFolder, string ExtractPrefix)`
- L721-755 _private* method_ `static bool AddManifests(Dictionary<string, DependencyFile> TargetFiles, Dictionary<string, DependencyBlob> TargetBlobs, Dictionary<string, DependencyPackInfo> TargetPacks, string BuildFolder, string ExtractPrefix)`
- L757-791 _private* method_ `static void PurgeCacheFiles(string CachePath, Dictionary<string, DependencyPackInfo> Packs, float CacheSizeMultiplier, int CacheDays)`
- L798-803 _public method_ `public static int GetFileMode_Mac(string FileName)` — Gets the file mode on Mac
- L810-813 _public method_ `public static int SetFileMode_Mac(string FileName, ushort Mode)` — Sets the file mode on Mac
- L820-825 _public method_ `public static int GetFileMode_Linux(string FileName)` — Gets the file mode on Linux
- L832-835 _public method_ `public static int SetFileMode_Linux(string FileName, ushort Mode)` — Sets the file mode on Linux
- L870 _private* method_ `static extern int stat64(string pathname, stat64_t stat)` — attrs: `[DllImport("libSystem.dylib")]`
- L873 _private* method_ `static extern int chmod(string path, ushort mode)` — attrs: `[DllImport("libSystem.dylib")]`
- L905 _private* method_ `static extern int stat64_linux(int ver, string pathname, stat64_linux_t stat)` — attrs: `[DllImport("libc", EntryPoint = "__xstat64")]`
- L908 _private* method_ `static extern int chmod_linux(string path, ushort mode)` — attrs: `[DllImport("libc", EntryPoint = "chmod")]`
- L913-974 _private* method_ `static bool SetExecutablePermissions(string RootDir, IEnumerable<DependencyFile> Files)`
- L976-999 _private* method_ `static bool IsExcludedFolder(string Name, IEnumerable<string> ExcludeFolders)`
- L1001-1121 _private* method_ `static bool DownloadDependencies(string RootPath, IEnumerable<DependencyFile> RequiredFiles, IEnumerable<DependencyBlob> Blobs, IEnumerable<DependencyPackInfo> Packs, int NumThreads, double HttpTimeoutMultiplier, int MaxRetries, Uri? Proxy, string? CachePath)`
- L1123-1129 _private* method_ `static string FormatMegabytes(long Value, int NumDecimalPlaces)`
- L1131-1146 _private* method_ `static IncomingFile[] GetIncomingFilesForPack(string RootPath, DependencyPack RequiredPack, Dictionary<string, List<DependencyBlob>> PackToBlobs, Dictionary<string, List<DependencyFile>> BlobToFiles)`
- L1148-1219 _private* method_ `static void DownloadWorker(ConcurrentQueue<IncomingPack> DownloadQueue, AsyncDownloadState State, int MaxRetries, CancellationToken CancellationToken)`
- L1221-1252 _private* method_ `static bool TryUnpackFromCache(string? CacheFileName, IncomingFile[] Files)`
- L1254-1271 _private* method_ `static async Task DownloadAndExtractFiles(string Url, string? CacheFileName, long CompressedSize, string ExpectedHash, IncomingFile[] Files, NotifyReadDelegate NotifyRead)`
- L1273-1292 _private* method_ `static void CreateHttpClient(Uri? Proxy, long LargestPackSize, double HttpTimeoutMultiplier, int NumThreads)`
- L1294-1306 _private* method_ `static NetworkCredential? MakeCredentialsFromUri(Uri Address)`
- L1308-1313 _private* method_ `static void ExtractFiles(Stream InputStream, IncomingFile[] Files)`
- L1315-1351 _private* method_ `static void ExtractFilesThroughCache(Stream InputStream, string FileName, long CompressedSize, string ExpectedHash, IncomingFile[] Files)`
- L1353-1461 _private* method_ `static void ExtractFilesFromRawStream(Stream RawStream, IncomingFile[] Files, SHA1? RawStreamHasher)`
- L1463-1480 _private* method_ `static bool ReadXmlObject<T>(string FileName, out T NewObject)`
- L1482-1502 _private* method_ `static bool WriteXmlObject<T>(string FileName, T XmlObject)`
- L1504-1523 _private* method_ `static bool WriteWorkingManifest(string FileName, string TemporaryFileName, WorkingManifest Manifest)`
- L1525-1537 _private* method_ `static bool SafeModifyFileAttributes(string FileName, FileAttributes AddAttributes, FileAttributes RemoveAttributes)`
- L1539-1551 _private* method_ `static bool SafeDeleteFile(string FileName)`
- L1553-1564 _private* method_ `static bool SafeDeleteFileQuiet(string FileName)`
- L1566-1578 _private* method_ `static bool SafeMoveFile(string SourceFileName, string TargetFileName)`
- L1580-1591 _private* method_ `static bool SafeMoveFileQuiet(string SourceFileName, string TargetFileName)`
- L1593-1601 _private* method_ `static string ComputeHashForFile(string FileName)`
- L1603-1625 _private* method_ `static void BuildExceptionStack(Exception? exception, List<Exception> exceptionStack)`
- L1627-1668 _private* method_ `static string FormatExceptionDetails(Exception ex)`

#### class `GitDependencies.Program.AsyncDownloadState`  
`class AsyncDownloadState`  
_private*; L24-33_
- L26 _public field_ `public int NumFiles`
- L27 _public field_ `public int NumFilesRead`
- L28 _public field_ `public long NumBytesRead`
- L29 _public field_ `public long NumBytesTotal`
- L30 _public field_ `public long NumBytesCached`
- L31 _public field_ `public int NumFailingOrIdleDownloads`
- L32 _public field_ `public string LastDownloadError = null!`

#### enum `GitDependencies.Program.OverwriteMode`  
`enum OverwriteMode`  
_private*; L35-40_
- L37 _public* enumerator_ `Unchanged`
- L38 _public* enumerator_ `Prompt`
- L39 _public* enumerator_ `Force`

#### class `GitDependencies.Program.IncomingPack`  
`class IncomingPack`  
_private*; L42-49_
- L44 _public field_ `public string Url = null!`
- L45 _public field_ `public string Hash = null!`
- L46 _public field_ `public string? CacheFileName = null!`
- L47 _public field_ `public IncomingFile[] Files = new IncomingFile[0]`
- L48 _public field_ `public long CompressedSize`

#### class `GitDependencies.Program.IncomingFile`  
`class IncomingFile`  
_private*; L51-57_
- L53 _public field_ `public string[] Names = new string[0]`
- L54 _public field_ `public string Hash = null!`
- L55 _public field_ `public long MinPackOffset`
- L56 _public field_ `public long MaxPackOffset`

#### struct `GitDependencies.Program.DependencyPackInfo`  
`struct DependencyPackInfo`  
_private*; L59-74_
- L61 _public field_ `public DependencyManifest Manifest`
- L62 _public field_ `public DependencyPack Pack`
- L64-68 _public ctor_ `public DependencyPackInfo(DependencyManifest Manifest, DependencyPack Pack)`
- L70-73 _public method_ `public string GetCacheFileName()`

#### class `GitDependencies.Program.CorruptPackFileException`  
`class CorruptPackFileException : Exception`  
_private*; L76-82_
- inherits: `Exception`
- L78-81 _public ctor_ `public CorruptPackFileException(string Message, Exception? InnerException) : base(Message, InnerException)`

#### struct `GitDependencies.Program.timespec_t`  
`struct timespec_t`  
_private*; L839-843_
- L841 _public field_ `public ulong tv_sec`
- L842 _public field_ `public ulong tv_nsec`

#### class `GitDependencies.Program.stat64_t`  
`class stat64_t`  
_private*; L846-867_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L848 _public field_ `public uint st_dev`
- L849 _public field_ `public ushort st_mode`
- L850 _public field_ `public ushort st_nlink`
- L851 _public field_ `public ulong st_ino`
- L852 _public field_ `public uint st_uid`
- L853 _public field_ `public uint st_gid`
- L854 _public field_ `public uint st_rdev`
- L855 _public field_ `public timespec_t st_atimespec`
- L856 _public field_ `public timespec_t st_mtimespec`
- L857 _public field_ `public timespec_t st_ctimespec`
- L858 _public field_ `public timespec_t st_birthtimespec`
- L859 _public field_ `public ulong st_size`
- L860 _public field_ `public ulong st_blocks`
- L861 _public field_ `public uint st_blksize`
- L862 _public field_ `public uint st_flags`
- L863 _public field_ `public uint st_gen`
- L864 _public field_ `public uint st_lspare`
- L865 _public field_ `public ulong st_qspare1`
- L866 _public field_ `public ulong st_qspare2`

#### class `GitDependencies.Program.stat64_linux_t`  
`class stat64_linux_t`  
_private*; L882-901_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L884 _public field_ `public ulong st_dev`
- L885 _public field_ `public ulong st_ino`
- L886 _public field_ `public ulong st_nlink`
- L887 _public field_ `public uint st_mode`
- L888 _public field_ `public uint st_uid`
- L889 _public field_ `public uint st_gid`
- L890 _public field_ `public int pad0`
- L891 _public field_ `public ulong st_rdev`
- L892 _public field_ `public long st_size`
- L893 _public field_ `public long st_blksize`
- L894 _public field_ `public long st_blocks`
- L895 _public field_ `public timespec_t st_atime`
- L896 _public field_ `public timespec_t st_mtime`
- L897 _public field_ `public timespec_t st_ctime`
- L898 _public field_ `public long glibc_reserved0`
- L899 _public field_ `public long glibc_reserved1`
- L900 _public field_ `public long glibc_reserved2`

### `Source/Programs/GitDependencies/Properties/AssemblyInfo.cs` (GitDependencies)
_(no declarations)_


### `Source/Programs/GitDependencies/WorkingManifest.cs` (GitDependencies)


#### class `GitDependencies.WorkingFile`  
`public class WorkingFile`  
_public; L12-25_
- L15 _public field_ `public string Name = null!` — attrs: `[XmlAttribute]`
- L18 _public field_ `public string Hash = null!` — attrs: `[XmlAttribute]`
- L21 _public field_ `public string ExpectedHash = null!` — attrs: `[XmlAttribute]`
- L24 _public field_ `public long Timestamp` — attrs: `[XmlAttribute]`

#### class `GitDependencies.WorkingManifest`  
`public class WorkingManifest`  
_public; L27-31_
- L30 _public field_ `public List<WorkingFile> Files = new List<WorkingFile>()` — attrs: `[XmlArrayItem("File")]`
