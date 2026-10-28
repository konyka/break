# CSharp / EpicGames.Benchmarks

- project root: `Source/Programs/Shared/EpicGames.Benchmarks`
- files: 2; symbols: 10
- symbol kinds: class=2, field=1, method=6, property=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Benchmarks/HashBenchmarks.cs` (EpicGames.Benchmarks)


#### class `EpicGames.Benchmarks.HashBenchmarks`  
`public class HashBenchmarks`  
_public; L14-52_
- attrs: `[CPUUsageDiagnoser] [MemoryDiagnoser]`
- L17 _public property_ `public int DataLength { get; set; }` — attrs: `[Params(1000, 10_000, 1_000_000)]`
- L19 _private field_ `private byte[]? _data`
- L23-27 _public method_ `public void Setup()` — attrs: `[GlobalSetup] [SuppressMessage("Security", "CA5394:Do not use insecure randomness", Justification = "Using Random for deterministic test data generation")]`
- L30-33 _public method_ `public IoHash IOHash()` — attrs: `[Benchmark]`
- L36-39 _public method_ `public ContentHash ContentHashSHA1()` — attrs: `[Benchmark]`
- L42-45 _public method_ `public ContentHash ContentHashMD5()` — attrs: `[Benchmark]`
- L48-51 _public method_ `public Md5Hash MD5Hash()` — attrs: `[Benchmark]`

### `Source/Programs/Shared/EpicGames.Benchmarks/Program.cs` (EpicGames.Benchmarks)


#### class `EpicGames.Benchmarks.Program`  
`internal class Program`  
_internal; L7-13_
- L9-12 _private* method_ `static void Main(string[] args)`
