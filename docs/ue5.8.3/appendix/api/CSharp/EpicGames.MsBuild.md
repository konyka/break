# CSharp / EpicGames.MsBuild

- project root: `Source/Programs/Shared/EpicGames.MsBuild`
- files: 2; symbols: 12
- symbol kinds: class=2, field=2, method=8
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.MsBuild/CsProjBuilder.cs` (EpicGames.MsBuild)


#### class `EpicGames.MsBuild.CsProjBuilder`  
`public static class CsProjBuilder`  
_public; L24-606_
- desc: Builds .csproj files
- L26-48 _private* method_ `static FileReference ConstructBuildRecordPath(CsProjBuildHook hook, FileReference projectPath, IEnumerable<DirectoryReference> baseDirectories)`
- L60-69 _public method_ `public static Dictionary<FileReference, CsProjBuildRecordEntry> Build(HashSet<FileReference> foundProjects, bool bForceCompile, out bool bBuildSuccess, CsProjBuildHook hook, IEnumerable<DirectoryReference> baseDirectories, IReadOnlyDictionary<string, IEnumerable<string>> customGlobalProperties, ILogger logger)` — Builds multiple projects
- L81-407 _private method_ `private static Dictionary<FileReference, CsProjBuildRecordEntry> BuildInternal(HashSet<FileReference> foundProjects, bool bForceCompile, out bool bBuildSuccess, CsProjBuildHook hook, IEnumerable<DirectoryReference> baseDirectories, IReadOnlyDictionary<string, IEnumerable<string>> customGlobalProperties, ILogger logger)` — Builds multiple projects. This is the internal implementation invoked after the MS build path is set
- L411-438 _private method_ `private static string CleanGlobString(string globString)`
- L440-476 _private method_ `private static async Task<FileReference> WriteCsPropertiesAsync(IEnumerable<FileReference> projects, CsProjBuildHook hook, CancellationToken cancellationToken)`
- L478-519 _private method_ `private static async Task<bool> RunDotnetAsync(IEnumerable<string> arguments, CsProjBuildHook hook, ILogger logger, CancellationToken cancellationToken)`
- L521-605 _private method_ `private static async Task<bool> RunDotnetBuildAsync(IEnumerable<FileReference> projects, Dictionary<string, string> globalProperties, CsProjBuildHook hook, ILogger logger, CancellationToken cancellationToken)`

### `Source/Programs/Shared/EpicGames.MsBuild/MsBuildSupport.cs` (EpicGames.MsBuild)


#### class `EpicGames.MsBuild.MsBuildSupport`  
`public static class MsBuildSupport`  
_public; L15-79_
- desc: Support for loading MSBuild assemblies from a dotnet install.
- L17 _private field_ `private static bool s_hasRegisteredMsBuildPath = false`
- L18 _private field_ `private static readonly Lock s_lock = new()`
- L24-78 _public method_ `public static void RegisterMsBuildPath(IMsBuildRegistration hook)` — Register our bundled dotnet installation to be used by Microsoft.Build This needs to happen in a function called before the first use of any Microsoft.Build types
