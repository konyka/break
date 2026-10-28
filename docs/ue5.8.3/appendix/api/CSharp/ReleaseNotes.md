# CSharp / ReleaseNotes

- project root: `Source/Programs/Horde/Tools/ReleaseNotes`
- files: 1; symbols: 16
- symbol kinds: class=2, field=6, method=2, property=5, record=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Tools/ReleaseNotes/Program.cs` (ReleaseNotes)


#### class `CreateReleaseNotes.Program`  
`internal class Program`  
_internal; L13-310_
- L15 _private* field_ `static readonly string[] s_paths = [ "Engine/Source/Programs/Horde/...", "Engine/Source/Programs/Shared/...", "Engine/Restricted/NotForLicensees/Source/Programs/Horde/...", ]`
- L22 _private field_ `private static readonly string[] s_ignoreFilter = [ "Engine/Source/Programs/Shared/EpicGames.UBA/...", "Engine/Source/Programs/Shared/EpicGames.Build/...", "Engine/Source/Programs/Shared/EpicGames.UHT/...", "Engine/Source/Programs/Shared/UnrealBuildT ...`
- L37 _private* field_ `static readonly string[] s_serverFilter = [ "...", "-/Engine/Source/Programs/Horde/HordeDashboard/...", "-/Engine/Source/Programs/Horde/HordeAgent/..." ]`
- L44 _private* field_ `static readonly string[] s_agentFilter = [ "...", "-/Engine/Source/Programs/Horde/HordeDashboard/...", "-/Engine/Source/Programs/Horde/HordeServer*/...", "-/Engine/Source/Programs/Horde/Plugins/*/HordeServer*/..." ]`
- L52 _private* field_ `static readonly string[] s_dashboardFilter = [ "-/...", "/Engine/Source/Programs/Horde/HordeDashboard/..." ]`
- L58 _private* field_ `static readonly string[] s_restrictedFilter = [ "-/...", "/Engine/Restricted/..." ]`
- L84-288 _private* method_ `static async Task<int> Main(string[] args)`
- L290-309 _private* method_ `static bool TryParseChange(string? name, out int version)`

#### record `CreateReleaseNotes.Program.ChangeInfo`  
`record ChangeInfo(int Number, string Description, string? JiraTicket)`  
_private*; L64-64_

#### class `CreateReleaseNotes.Program.Options`  
`class Options`  
_private*; L66-82_
- L69 _public property_ `public Uri Server { get; set; }` — attrs: `[CommandLine("-Server=", Required = true)]`
- L72 _public property_ `public int? Change { get; set; }` — attrs: `[CommandLine("-Change=")]`
- L75 _public property_ `public int? ServerChange { get; set; }` — attrs: `[CommandLine("-ServerChange=")]`
- L78 _public property_ `public int? AgentChange { get; set; }` — attrs: `[CommandLine("-ClientChange=")]`
- L81 _public property_ `public int? DashboardChange { get; set; }` — attrs: `[CommandLine("-DashboardChange=")]`
