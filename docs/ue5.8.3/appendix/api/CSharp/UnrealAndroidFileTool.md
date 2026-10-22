# CSharp / UnrealAndroidFileTool

- project root: `Source/Programs/UnrealAndroidFileTool`
- files: 2; symbols: 8
- symbol kinds: class=1, field=2, method=5
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealAndroidFileTool/Program.cs` (UnrealAndroidFileTool)


#### class `UnrealAndroidFileTool.Program`  
`class Program`  
_internal*; L12-1393_
- L14 _private field_ `private static string AppVersion = "1.0.9"`
- L15 _private field_ `private static ILogger Logger = Log.Logger`
- L17-99 _private* method_ `static void ShowHelp(string command)`
- L101-131 _private* method_ `static string FixPath(AndroidFileClient client, string path)`
- L133-1133 _private* method_ `static int ProcessCommand(AndroidFileClient client, bool bInShell, string[] args, int ArgIndex)`
- L1135-1192 _private* method_ `static AndroidFileClient? CreateAndConnectClient(string Device, string PackageName, string Token, string IPAddress, int Port)`
- L1194-1392 _private* method_ `static void Main(string[] args)`

### `Source/Programs/UnrealAndroidFileTool/Properties/AssemblyInfo.cs` (UnrealAndroidFileTool)
_(no declarations)_

