# CSharp / EpicGames.Perforce.Fixture

- project root: `Source/Programs/Shared/EpicGames.Perforce.Fixture`
- files: 3; symbols: 72
- symbol kinds: class=6, const=6, ctor=3, field=6, method=28, property=17, record=6
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Perforce.Fixture/PerforceFixture.cs` (EpicGames.Perforce.Fixture)


#### class `EpicGames.Perforce.Fixture.DepotFileFixture`  
`public class DepotFileFixture`  
_public; L17-40_
- L19 _public property_ `public string DepotFile { get; }`
- L20 _public property_ `public string ClientFile { get; }`
- L21 _public property_ `public long Size { get; }`
- L22 _public property_ `public int Revision { get; }`
- L23 _public property_ `public string Digest { get; }`
- L24 _public property_ `public string Content { get; }`
- L26-34 _public ctor_ `public DepotFileFixture(string depotFile, string clientFile, string content, int revision)`
- L36-39 _public method_ `public override string ToString()`

#### class `EpicGames.Perforce.Fixture.ChangelistFixture`  
`public class ChangelistFixture`  
_public; L42-194_
- L44 _public const_ `public const string Placeholder = "<placeholder>"`
- L46 _public property_ `public int Number { get; }`
- L47 _public property_ `public string Description { get; }`
- L48 _public property_ `public bool IsShelved { get; }`
- L54 _public property_ `public IReadOnlyList<DepotFileFixture> StreamFiles { get; }` — List of files in stream as how they would appear locally on disk, when synced to this changelist (after any view maps have been applied)
- L56-62 _public ctor_ `public ChangelistFixture(int number, string description, List<DepotFileFixture> streamFiles, bool isShelved = false)`
- L68-72 _public method_ `public void AssertDepotFiles(string clientRoot)` — Assert directory contains exactly the files described by stream
- L79-104 _public method_ `public static void AssertFileSets(FileSet actual, FileSet expected)` — Assert directory contains exactly the specified file set
- L111-145 _public method_ `public async Task AssertHaveTableAsync(IPerforceConnection perforce, bool useHaveTable = true)` — Assert files in stream for this changelist matches the client's have table
- L147-152 _public method_ `public (FileSet localFiles, FileSet streamFiles) GetFileSets(string clientRoot)`
- L154-174 _public method_ `public static FileSet GetLocalFileSet(string clientRoot)`
- L176-188 _public method_ `public (List<string> localFiles, List<string> streamFiles) GetFiles(string clientRoot)`
- L190-193 _public method_ `public DepotFileFixture? GetFile(string depotPath)`

#### class `EpicGames.Perforce.Fixture.StreamFixture`  
`public class StreamFixture`  
_public; L196-224_
- L198 _public property_ `public string Root { get; }`
- L199 _public property_ `public IEnumerable<ChangelistFixture> Changelists => ...`
- L200 _public property_ `public ChangelistFixture Head { get; }`
- L201 _private field_ `private readonly IReadOnlyList<ChangelistFixture> _changelists`
- L203-208 _public ctor_ `public StreamFixture(string root, int headCl, IReadOnlyList<ChangelistFixture> changelists)`
- L210 _public property_ `public ChangelistFixture LatestChangelist => ...`
- L212-223 _public method_ `public ChangelistFixture GetChangelist(int changeNum)`

#### class `EpicGames.Perforce.Fixture.PerforceFixture`  
`public class PerforceFixture`  
_public; L226-394_
- L228 _public property_ `public StreamFixture StreamFooMain { get; }`
- L296 _public property_ `public StreamFixture StreamFooRelease { get; }`
- L315 _public property_ `public StreamFixture StreamFooSparseDev { get; }`
- L327-331 _public method_ `public static string CalcMd5(string content)`
- L338-368 _public method_ `public static void AssertCacheEquals(string cacheDir, params string[] digests)` — Assert cache contains exactly the provided digests
- L370-393 _private method_ `private static HashSet<(string cacheId, string digest, long fileSize)> GetCachedFiles(string cacheDir)`

### `Source/Programs/Shared/EpicGames.Perforce.Fixture/PerforceSnapshot.cs` (EpicGames.Perforce.Fixture)


#### record `EpicGames.Perforce.Fixture.ServerSnapshot`  
`public record ServerSnapshot(Dictionary<string, StreamSnapshot> StreamSnapshots)`  
_public; L19-25_
- L21-24 _public method_ `public StreamSnapshot GetStream(string stream)`

#### record `EpicGames.Perforce.Fixture.StreamSnapshot`  
`public record StreamSnapshot(string Name, List<Changelist> Changelists, List<WorkspaceSnapshot> WorkspaceSnapshots)`  
_public; L27-34_
- L29-33 _public method_ `public WorkspaceSnapshot GetWorkspace(int cl, int shelvedCl = -1)`

#### record `EpicGames.Perforce.Fixture.Changelist`  
`public record Changelist(int Change, string Description)`  
_public; L36-36_

#### record `EpicGames.Perforce.Fixture.WorkspaceFile`  
`public record WorkspaceFile( string Path, long Size, string Content, string Digest, int Revision )`  
_public; L38-55_
- L46-54 _public method_ `public static WorkspaceFile Create(string path, string content)`

#### record `EpicGames.Perforce.Fixture.WorkspaceSnapshot`  
`public record WorkspaceSnapshot(int Change, int ShelvedChange, HashSet<WorkspaceFile> Files)`  
_public; L57-103_
- L63-68 _public method_ `public void AssertDepotFiles(string clientRoot)` — Assert local directory contains exactly the files described by stream
- L75-102 _public method_ `public static void AssertFileSets(HashSet<WorkspaceFile> actual, HashSet<WorkspaceFile> expected)` — Assert directory contains exactly the specified file set

#### record `EpicGames.Perforce.Fixture.WorkspaceState`  
`public record WorkspaceState(string Stream, int Cl, int ShelvedCl = 0, bool RemoveUntracked = true, Action? OnPreSync = null, Action? OnPostSync = null)`  
_public; L105-105_

#### class `EpicGames.Perforce.Fixture.PerforceSnapshot`  
`public class PerforceSnapshot(PerforceConnection perforce)`  
_public; L107-249_
- L109 _public const_ `public const string SnapshotJsonFile = "snapshot.json"`
- L111 _public const_ `public const string FooMain = "//Foo/Main"`
- L112 _public const_ `public const string FooRelease = "//Foo/Release"`
- L113 _public const_ `public const string FooMainSparseDev = "//Foo/Main-SparseDev"`
- L114 _public const_ `public const string FooMainSparseRel = "//Foo/Main-SparseRel"`
- L116 _public field_ `public static readonly IReadOnlyList<WorkspaceState> FooMainStates = [ Main(2), Main(3), Main(4), Main(5), Main(6), Main(7), Main(9), Main(2, 8), Main(3, 8), Main(7, 8), Main(9, 8) ]`
- L124 _public field_ `public static readonly IReadOnlyList<WorkspaceState> FooReleaseStates = [Release(11), Release(12)]`
- L125 _public field_ `public static readonly IReadOnlyList<WorkspaceState> FooMainSparseDevStates = [SparseDev(9), SparseDev(13)]`
- L127 _private field_ `private static readonly JsonSerializerOptions s_jsonSerializerOptions = new() { WriteIndented = true }`
- L128 _private field_ `private static readonly Lazy<ServerSnapshot> s_serverSnapshot = new(LoadSnapshot)`
- L130 _public method_ `public static ServerSnapshot GetSnapshot()`
- L131 _public method_ `public static WorkspaceState Main(int cl, int shelvedCl = -1)`
- L132 _public method_ `public static WorkspaceState Release(int cl, int shelvedCl = -1)`
- L133 _public method_ `public static WorkspaceState SparseDev(int cl, int shelvedCl = -1)`
- L135-147 _private method_ `private static ServerSnapshot LoadSnapshot()`
- L149-163 _public method_ `public async Task TakeSnapshotsAsync(string snapshotJsonFile)`
- L165-173 _private method_ `private async Task<StreamSnapshot> TakeStreamSnapshotAsync(string stream, IReadOnlyList<WorkspaceState> streamStates)`
- L175-203 _private method_ `private async Task<WorkspaceSnapshot> TakeWorkspaceSnapshotAsync(WorkspaceState ss)`
- L205-226 _public method_ `public static HashSet<WorkspaceFile> GetLocalFileSet(string clientRoot)`
- L228-248 _private method_ `private async Task<(IPerforceConnection perforce, string clientRoot)> CreateClientAsync(string stream, CancellationToken ct)`

### `Source/Programs/Shared/EpicGames.Perforce.Fixture/Program.cs` (EpicGames.Perforce.Fixture)


#### class `EpicGames.Perforce.Fixture.Program`  
`public static class Program`  
_public; L9-29_
- L11-28 _public method_ `public static async Task<int> Main()`
