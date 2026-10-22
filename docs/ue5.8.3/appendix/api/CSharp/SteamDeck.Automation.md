# CSharp / SteamDeck.Automation

- project root: `Source/Programs/AutomationTool/SteamDeck`
- files: 1; symbols: 17
- symbol kinds: class=1, field=6, method=10
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/SteamDeck/SteamDeckSupport.cs` (SteamDeck.Automation)


#### class `SteamDeckSupport`  
`public static class SteamDeckSupport`  
_public; L15-377_
- L17 _private* field_ `static string RSyncPath = Path.Combine(Unreal.RootDirectory.FullName, "Engine\\Extras\\ThirdPartyNotUE\\cwrsync\\bin\\rsync.exe")`
- L18 _private* field_ `static string SSHPath = Path.Combine(Unreal.RootDirectory.FullName, "Engine\\Extras\\ThirdPartyNotUE\\cwrsync\\bin\\ssh.exe")`
- L19 _private* field_ `static string DevKitRSAPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), @"steamos-devkit\steamos-devkit\devkit_rsa")`
- L20 _private* field_ `static string KnownHostsPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), @".ssh\known_hosts")`
- L21 _private* field_ `static string SteamDeckScripts = Path.Combine(Unreal.RootDirectory.FullName, "Engine\\Build\\SteamDeck")`
- L22 _private* field_ `static string DefaultUserName = "deck"`
- L26-80 _public method_ `public static List<DeviceInfo> GetDevices(UnrealTargetPlatform RuntimePlatform)`
- L85-128 _public method_ `public static bool GetDeviceInfo(UnrealTargetPlatform RuntimePlatform, ProjectParams Params, out string IpAddr, out string UserName)`
- L134-166 _private method_ `private static string GetRegisterGameScript(ProjectParams Params, UnrealTargetPlatform RuntimePlatform, string GameFolderPath, string GameRunArgs, string MsvsmonVersion)`
- L168-174 _private method_ `private static string GetRunGameScript(ProjectParams Params, UnrealTargetPlatform RuntimePlatform)`
- L178-198 _public method_ `public static string FixupHostPath(string HostPath)`
- L200-244 _private method_ `private static IProcessResult Rsync(string SourceFolder, string DestFolder, string UserName, string IpAddr, string[] ExcludeList)`
- L246-250 _private method_ `private static IProcessResult SSHCommand(string Command, string UserName, string IpAddr)`
- L257-321 _public method_ `public static void Deploy(UnrealTargetPlatform RuntimePlatform, ProjectParams Params, DeploymentContext SC)`
- L323-343 _private method_ `private static bool DeployMsvsmon(string IpAddr, string UserName, out string MsvsmonVersion)`
- L349-374 _public method_ `public static IProcessResult RunClient(UnrealTargetPlatform RuntimePlatform, CommandUtils.ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
