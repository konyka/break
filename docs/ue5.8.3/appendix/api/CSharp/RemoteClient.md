# CSharp / RemoteClient

- project root: `Source/Programs/Horde/Samples/RemoteClient`
- files: 1; symbols: 16
- symbol kinds: class=2, const=3, method=4, property=7
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Samples/RemoteClient/RemoteClientApp.cs` (RemoteClient)


#### class `RemoteClient.ClientAppOptions`  
`class ClientAppOptions`  
_internal*; L18-34_
- L21 _public property_ `public string? Server { get; set; }` — attrs: `[CommandLine("-Server=")]`
- L24 _public property_ `public string? OidcProvider { get; set; }` — attrs: `[CommandLine("-Oidc=")]`
- L27 _public property_ `public string? Condition { get; set; }` — attrs: `[CommandLine("-Condition=")]`
- L30 _public property_ `public bool InProc { get; set; }` — attrs: `[CommandLine]`
- L33 _public property_ `public bool UseCppWorker { get; set; }` — attrs: `[CommandLine("-Cpp")]`

#### class `RemoteClient.ClientApp`  
`class ClientApp`  
_internal*; L36-177_
- L38 _private* property_ `static FileReference CurrentAssemblyFile { get; }`
- L39 _private* property_ `static DirectoryReference ClientSourceDir { get; }`
- L41-93 _private* method_ `static async Task Main(string[] args)`
- L95 _private* const_ `const int PrimaryChannelId = 0`
- L96 _private* const_ `const int BackgroundChannelId = 1`
- L97 _private* const_ `const int ChildProcessChannelId = 100`
- L99-135 _private* method_ `static async Task RunRemoteAsync(IComputeLease lease, DirectoryReference uploadDir, string executable, List<string> arguments, ILogger logger)`
- L137-157 _private* method_ `static async Task WriteNumbersAsync(ComputeChannel channel, ILogger logger, CancellationToken cancellationToken)`
- L159-176 _private* method_ `static async Task RunBackgroundXorAsync(AgentMessageChannel channel)`
