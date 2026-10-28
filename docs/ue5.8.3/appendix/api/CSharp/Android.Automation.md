# CSharp / Android.Automation

- project root: `Source/Programs/AutomationTool/Android`
- files: 4; symbols: 355
- symbol kinds: class=14, const=27, ctor=7, delegate=1, dtor=3, enum=2, enumerator=6, field=82, method=199, property=14
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Android/AndroidFileClient.cs` (Android.Automation)


#### class `AutomationTool.AndroidFileClient`  
`public class AndroidFileClient`  
_public; L18-3104_
- L20 _public delegate_ `public delegate bool ShellOutputCallbackType(object Data, string Message)`
- L22 _protected property_ `protected static ILogger Logger => ...`
- L24 _private const_ `private const bool TimeBatching = false`
- L26 _private const_ `private const int DefaultPort = 57099`
- L27 _private const_ `private const int ServerVersion_Min = 100`
- L28 _private const_ `private const int ServerVersion_Max = 101`
- L29 _private const_ `private const int ServerVersion_Handshake = 101`
- L30 _private const_ `private const int FILE_BUFFERSIZE = 65536 * 16`
- L31 _private const_ `private const int SOCKET_READBUFFER = 625 * 1024`
- L32 _private const_ `private const int SOCKET_SENDBUFFER = 625 * 1024`
- L33 _private const_ `private const int BATCH_BUFFERSIZE = !TimeBatching ? 65536 * 16 : 200000000`
- L34 _private const_ `private const int BATCH_SENDSIZE = 65536 * 16`
- L36 _private field_ `private string Device`
- L37 _private field_ `private int ServerPort`
- L38 _private field_ `private int HostPort`
- L40 _private field_ `private string ActivePackageName = ""`
- L41 _private field_ `private string ActiveToken = ""`
- L42 _private field_ `private string ActiveIPAddress = "127.0.0.1"`
- L43 _private field_ `private int ActiveVersion = 0`
- L45 _private field_ `private static OptimalADB adb = new OptimalADB()`
- L46 _private* field_ `static string LastListenDevice = ""`
- L47 _private* field_ `static bool bHave_ss = true`
- L48 _private* field_ `static bool bHave_netstat = true`
- L50 _private field_ `private Socket ClientSocket = null`
- L52 _private field_ `private FileStream RecordFile = null`
- L53 _private field_ `private BufferedStream RecordStream = null`
- L54 _private field_ `private bool bBlockSend = false`
- L56 _private field_ `private byte[] BatchBuffer = null`
- L57 _private field_ `private int BatchBufferIndex = 0`
- L59 _private field_ `private string LastBaseDir = ""`
- L61 _private field_ `private static int Command_Terminate = 0`
- L62 _private field_ `private static int Command_Close = 1`
- L63 _private field_ `private static int Command_Info = 2`
- L64 _private field_ `private static int Command_Query = 3`
- L65 _private field_ `private static int Command_GetProp = 4`
- L66 _private field_ `private static int Command_SetBaseDir = 5`
- L68 _private field_ `private static int Command_DirExists = 10`
- L69 _private field_ `private static int Command_DirList = 11`
- L70 _private field_ `private static int Command_DirListFlat = 12`
- L71 _private field_ `private static int Command_DirCreate = 13`
- L72 _private field_ `private static int Command_DirDelete = 14`
- L73 _private field_ `private static int Command_DirDeleteRecurse = 15`
- L75 _private field_ `private static int Command_FileExists = 20`
- L76 _private field_ `private static int Command_FileDelete = 21`
- L77 _private field_ `private static int Command_FileCopy = 22`
- L78 _private field_ `private static int Command_FileMove = 23`
- L79 _private field_ `private static int Command_FileRead = 24`
- L80 _private field_ `private static int Command_FileWrite = 25`
- L81 _private field_ `private static int Command_FileWriteCompressed = 26`
- L82 _private field_ `private static int Command_FileWriteHandshake = 27`
- L526-534 _private method_ `private static string GetAdbCommandLine(string SerialNumber, string Args)`
- L536 _private* field_ `static string LastSpewFilename = ""`
- L538-557 _public method_ `public static string ADBSpewFilter(string Message)`
- L559-568 _public method_ `public static IProcessResult RunAdbCommand(string SerialNumber, string Args, string Input = null, CommandUtils.ERunOptions Options = CommandUtils.ERunOptions.NoLoggingOfRunCommand, bool bShouldLogCommand = false)`
- L570-599 _public method_ `public static void GetConnectedDevices(out List<string> Devices)`
- L602-650 _public method_ `public static int ForwardPort_FindOrAdd(string Device, int DevicePort)`
- L654-699 _public method_ `public static int ForwardPort_Add(string Device, int DevicePort)`
- L701-705 _public method_ `public static void ForwardPort_Remove(string Device, int HostPort)`
- L707-712 _public method_ `public static void ReversePort_Add(string Device, int DevicePort, int HostPort)`
- L714-719 _public method_ `public static void ReversePort_Remove(string Device, int DevicePort)`
- L723 _private field_ `private long Stats_FilesRead = 0`
- L724 _private field_ `private long Stats_FilesWrite = 0`
- L726 _private field_ `private long Stats_TotalBytesReceived = 0`
- L727 _private field_ `private long Stats_TotalBytesSent = 0`
- L729 _private field_ `private long Stats_PayloadBytesReceived = 0`
- L730 _private field_ `private long Stats_PayloadBytesSent = 0`
- L732 _private field_ `private long Stats_CompressedBytesReceived = 0`
- L733 _private field_ `private long Stats_CompressedBytesSent = 0`
- L735 _private field_ `private Stopwatch Stats_Stopwatch = null`
- L737-755 _public method_ `public void Stats_Clear(bool bStartTimer = true)`
- L757-760 _public method_ `public void Stats_StartStopwatch()`
- L762-777 _public method_ `public void Stats_Combine(AndroidFileClient client)`
- L779-803 _public method_ `public void Stats_Report()`
- L805-820 _public method_ `public void Record_Stop()`
- L822-848 _public method_ `public bool Record_Begin(string Filename, bool BlockSend = false)`
- L850-884 _public method_ `public bool Record_Play(string Filepath)`
- L886-905 _private method_ `private int SocketReceive(bool bPayload, byte[] packet)`
- L907-918 _private method_ `private int SocketReceive(bool bPayload, byte[] packet, int readSize)`
- L920-931 _public method_ `public bool Batch_Start()`
- L933-955 _public method_ `public bool Batch_Flush()`
- L957-963 _public method_ `public void Batch_Stop()`
- L965-982 _private method_ `private void Batch_Append(byte[] packet, int writeSize)`
- L984-1015 _private method_ `private int SocketSend(bool bPayload, byte[] packet)`
- L1017-1047 _private method_ `private int SocketSend(bool bPayload, byte[] packet, int writeSize)`
- L1049-1060 _private method_ `private byte[] CommandPacket(int Command, long Size)`
- L1062-1081 _private method_ `private long ResultSize()`
- L1083-1110 _private method_ `private string GetStringResult()`
- L1112-1137 _private method_ `private string GetStringResult(int Command, string Params)`
- L1139-1148 _private method_ `private bool GetBoolResult(int Command, string Params)`
- L1152-1228 _private method_ `private string OptimizePath(string inPath)`
- L1232-1237 _public ctor_ `public AndroidFileClient(string inDevice, int inPort = DefaultPort)`
- L1239-1242 _private* dtor_ `~AndroidFileClient()`
- L1244-1247 _public method_ `public static int GetDefaultPort()`
- L1249-1252 _public method_ `public string GetDevice()`
- L1254-1257 _public method_ `public int GetServerPort()`
- L1259-1264 _public method_ `public void SetActive(String PackageName, String Token, String Address)`
- L1266-1366 _public method_ `public bool OpenConnection(String Address = "127.0.0.1")`
- L1368-1371 _public method_ `public static string Logcat(string Device, string Options, int Timeout = 0, ShellOutputCallbackType InCallback = null, object InCallbackData = null)`
- L1373-1400 _public method_ `public static string GetLastLogcatTime(string Device)`
- L1499-1503 _private method_ `private static bool LogcatWaitCallback(object InData, string Message)`
- L1505-1511 _public method_ `public static bool WaitForLogcat(string Device, string Options, string Line, int Timeout, double AfterTime = -1.0)`
- L1513-1559 _public method_ `public static List<string> GetInstalledReceivers(string Device)`
- L1561-1607 _public method_ `public static List<string> GetInstalledActivities(string Device)`
- L1609-1645 _public method_ `public static bool GetListenStatus_netstat(string Device, int Port, out bool bHaveApp, out bool bUSB, out bool bWifi, out string WifiAddress)`
- L1647-1710 _public method_ `public static bool GetListenStatus_ss(string Device, int Port, out bool bHaveApp, out bool bUSB, out bool bWifi, out string WifiAddress)`
- L1712-1746 _public method_ `public static bool GetListenStatus(string Device, int Port, out bool bUSB, out bool bWifi, out string WifiAddress)`
- L1748 _private field_ `private static string CurrentAndroidSDKLevelDevice = ""`
- L1749 _private field_ `private static int CurrentAndroidSDKLevel = -1`
- L1751-1762 _private method_ `private static int GetDeviceAndroidSDKLevel(string Device)`
- L1764-1786 _private method_ `private static bool ActivityManagerSendAndWait(string Device, string PackageName, string Arguments)`
- L1788-1840 _public method_ `public static bool StopAnyServers(string Device, int Port, bool bWaitForStop = true)`
- L1842-2002 _public method_ `public bool StartServer(string PackageName, string Token = "", string IPAddress = "127.0.0.1", bool bStopAnyServers = true)`
- L2004-2040 _public method_ `public void TerminateServer()`
- L2042-2081 _public method_ `public void CloseConnection()`
- L2083-2091 _public method_ `public string Query(string Filepath, bool bStripEndingSlash = false)`
- L2093-2096 _public method_ `public string GetProp(string Filepath)`
- L2098-2106 _public method_ `public bool SetBaseDir(string Filepath)`
- L2108-2111 _public method_ `public bool DirExists(string Filepath)`
- L2113-2116 _public method_ `public string DirList(string Filepath)`
- L2118-2121 _public method_ `public string DirListFlat(string Filepath)`
- L2123-2126 _public method_ `public bool DirCreate(string Filepath)`
- L2128-2131 _public method_ `public bool DirDelete(string Filepath)`
- L2133-2136 _public method_ `public bool DirDeleteRecurse(string Filepath)`
- L2138-2141 _public method_ `public bool FileExists(string Filepath)`
- L2143-2146 _public method_ `public bool FileDelete(string Filepath)`
- L2148-2151 _public method_ `public bool FileCopy(string SourcePath, string DestPath)`
- L2153-2156 _public method_ `public bool FileMove(string SourcePath, string DestPath)`
- L2158-2236 _public method_ `public bool FileRead(string SourcePath, string DestPath)`
- L2238-2304 _public method_ `public string FileReadString(string SourcePath)`
- L2306 _private const_ `private const int RetriesMax = 5`
- L2307 _private const_ `private const int RetryMillisecondsDelay = 5000`
- L2309-2372 _public method_ `public bool FileWrite(string SourcePath, string DestPath, int bLog = 0)`
- L2374-2476 _private method_ `private (bool Result, bool HasNetworkError) FileWriteInternal_Normal(string SourcePath, string DestPath, int bLog = 0)`
- L2478-2594 _private method_ `private (bool Result, bool HasNetworkError) FileWriteInternal(string SourcePath, string DestPath, int bLog = 0)`
- L2596-2728 _public method_ `public bool FileWriteCompressed(string SourcePath, string DestPath, int bLog = 0)`
- L2730-2775 _public method_ `public bool FileWriteString(string Contents, string DestPath)`
- L2777-2804 _public method_ `public bool PushFile(string InSource, string InDest, bool bCompress = false, int bLog = 0)`
- L2806-2819 _public method_ `public bool PushDirectory(string InSource, string InDest, bool bCompress = false, int bLog = 0)`
- L2821-2842 _public method_ `public bool PushDirectories(string InSource, string InDest, bool bCompress = false, int bLog = 0)`
- L2844-2867 _private method_ `private void AddDeployDirectories(ref List<KeyValuePair<string, string>> USBClientFiles, ref List<KeyValuePair<string, string>> WiFiClientFiles, ref bool bAlternate, string InSource, string InDest)`
- L2869 _private field_ `private bool bDeployThreadInterruptRequested = false`
- L2870 _private field_ `private bool bDeployThreadError = false`
- L2872-2887 _private method_ `private void DeployThread(AndroidFileClient Client, ref List<KeyValuePair<string, string>> Files, bool bCompress, int bLog)`
- L2889-2904 _private method_ `private void AddSourceDirectories(ref List<string> Directories, string InSource, string InDest)`
- L2906-3074 _public method_ `public bool Deploy(HashSet<string> EntriesToDeploy, string SourceDir, string DestDir, bool bCompress = false, bool bLog = false, bool bReportStats = true, AndroidFileClient WiFiClient = null)`

#### class `AutomationTool.AndroidFileClient.OptimalADB`  
`public class OptimalADB`  
_public; L87-524_
- L89 _private const_ `private const int DefaultPort = 5037`
- L91 _private field_ `private string Executable`
- L92 _private field_ `private int Port = 6037`
- L93 _private field_ `private Socket ClientSocket = null`
- L95 _private field_ `private string LastShellDevice = ""`
- L96 _private field_ `private string LastShellFeatures = ""`
- L99 _private field_ `private static int kHeaderSize = 1 + 4`
- L101 _private const_ `private const int kIdStdin = 0`
- L102 _private const_ `private const int kIdStdOut = 1`
- L103 _private const_ `private const int kIdStdErr = 2`
- L104 _private const_ `private const int kIdExit = 3`
- L105 _private const_ `private const int kIdCloseStdin = 4`
- L106 _private const_ `private const int kIdWindowSizeChange = 5`
- L107 _private const_ `private const int kIdInvalid = 255`
- L109-113 _public ctor_ `public OptimalADB(string ADBExecutable = "", int inPort = DefaultPort)`
- L115-118 _private* dtor_ `~OptimalADB()`
- L120-152 _private method_ `private bool OpenConnection()`
- L154-177 _private method_ `private void CloseConnection()`
- L179-190 _private method_ `private bool sendData(string Data)`
- L192-310 _private method_ `private bool receiveData(out string Output, bool bOnce = false)`
- L312-322 _private method_ `private bool execute(string Command, out string Output, bool bOnce = false)`
- L324-331 _private method_ `private bool executeDevice(string Device, string Command, out string Output, bool bOnce = false)`
- L333-339 _public method_ `public string GetVersion()`
- L341-347 _public method_ `public string GetDevices()`
- L349-356 _public method_ `public string GetFeatures(string Device)`
- L358-362 _private method_ `private string shellEscape(string source)`
- L364-496 _public method_ `public string Shell(string Device, string Command, int Timeout = 0, ShellOutputCallbackType OutputCallback = null, object OutputCallbackData = null)`
- L498-505 _public method_ `public string ListForward(string Device)`
- L507-514 _public method_ `public string AddForward(string Device, string Local, string Remote)`
- L516-523 _public method_ `public string RemoveForward(string Device, string Local)`

#### class `AutomationTool.AndroidFileClient.WaitCallbackData`  
`private class WaitCallbackData`  
_private; L1402-1497_
- L1404 _public field_ `public double AfterTime`
- L1405 _public field_ `public string WaitForLine`
- L1406 _public field_ `public string MessageBuffer`
- L1408-1413 _public ctor_ `public WaitCallbackData(double InAfterTime, string InWaitForLine)`
- L1415-1496 _public method_ `public bool CheckForLine(string InNewData)`

### `Source/Programs/AutomationTool/Android/AndroidPlatform.Automation.cs` (Android.Automation)


#### class `AndroidPlatform`  
`public class AndroidPlatform : Platform`  
_public; L18-4602_
- inherits: `Platform`
- L21 _private const_ `private const Int64 SmallOBBSizeAllowed = 1073741824`
- L22 _private const_ `private const Int64 NormalOBBSizeAllowed = 2147483648`
- L23 _private const_ `private const Int64 MaxOBBSizeAllowed = 4294967296`
- L25 _private const_ `private const int DeployMaxParallelCommands = 6`
- L27 _private const_ `private const string TargetAndroidLocation = "obb/"`
- L28 _private const_ `private const string TargetAndroidTemp = "/data/local/tmp/"`
- L30 _private const_ `private const string DefaultLaunchActivity = "com.epicgames.unreal.SplashActivity"`
- L167-171 _public ctor_ `public AndroidPlatform() : base(UnrealTargetPlatform.Android)`
- L174-179 _public method_ `public override string[] GetCodeSpecifiedSdkVersions()`
- L182-357 _public method_ `public override bool InstallSDK(BuildCommand BuildCommand, ITurnkeyContext TurnkeyContext, DeviceInfo Device, bool bUnattended, bool bSdkAlreadyInstalled)`
- L359-389 _public method_ `public override bool PostSDKSetup(ITurnkeyContext TurnkeyContext, bool bUnattended)`
- L391-423 _private method_ `private static string GetAndroidStudioExe()`
- L425-486 _private method_ `private static string GetSdkDir()`
- L488-636 _public method_ `public override bool UpdateHostPrerequisites(BuildCommand Command, ITurnkeyContext TurnkeyContext, bool bVerifyOnly)`
- L638-641 _private* method_ `static string GetAvdHomePath()`
- L643-671 _public method_ `public override DeviceInfo[] GetDevices()`
- L673-697 _public method_ `public override DeviceInfo GetDeviceByName(string DeviceName)`
- L699-702 _private method_ `private static string GetSONameWithoutArchitecture(ProjectParams Params, string DecoratedExeName)`
- L704-708 _private method_ `private static string GetSOName(ProjectParams Params, string DecoratedExeName, UnrealArch? Architecture)`
- L710-739 _private method_ `private static string GetFinalApkName(ProjectParams Params, string DecoratedExeName, bool bRenameUnrealGame, UnrealArch? Architecture)`
- L741 _private field_ `private static bool bHaveReadEngineVersion = false`
- L742 _private field_ `private static string EngineMajorVersion = "4"`
- L743 _private field_ `private static string EngineMinorVersion = "0"`
- L744 _private field_ `private static string EnginePatchVersion = "0"`
- L747 _private field_ `private static string EngineChangelist = "0"`
- L749-779 _private method_ `private static string ReadEngineVersion(string EngineDirectory)`
- L784-793 _private method_ `private static string GetFinalSymbolizedSODirectory(string ApkName, DeploymentContext SC, UnrealArch Architecture)`
- L795-828 _private method_ `private static string GetFinalObbName(string ApkName, DeploymentContext SC, bool bUseAppType = true)`
- L830-863 _private method_ `private static string GetFinalPatchName(string ApkName, DeploymentContext SC, bool bUseAppType = true)`
- L865-898 _private method_ `private static string GetFinalOverflowName(string ApkName, DeploymentContext SC, int Index, bool bUseAppType = true)`
- L901-912 _public method_ `public override string GetPlatformPakCommandLine(ProjectParams Params, DeploymentContext SC)`
- L914-919 _private method_ `private static string GetDeviceObbName(string ApkName, DeploymentContext SC)`
- L921-926 _private method_ `private static string GetDevicePatchName(string ApkName, DeploymentContext SC)`
- L928-933 _private method_ `private static string GetDeviceOverflowName(string ApkName, DeploymentContext SC, int Index)`
- L935-945 _public method_ `public static string GetStorageQueryCommand(bool bForcePC = false)`
- L953-977 _private method_ `private static string GetFinalBatchName(string ApkName, DeploymentContext SC, bool bNoOBBInstall, EBatchType BatchType, UnrealTargetPlatform Target)`
- L979-995 _private method_ `private UnrealArchitectures GetDeploymentArchitectures(ProjectParams Params, DeploymentContext SC)`
- L997-1017 _private method_ `private List<string> CollectPluginDataPaths(DeploymentContext SC)`
- L1019-1059 _private method_ `private bool UsingAndroidFileServer(ProjectParams Params, DeploymentContext SC, out bool bEnablePlugin, out string AFSToken, out bool bIsShipping, out bool bIncludeInShipping, out bool bAllowExternalStartInShipping)`
- L1068-1126 _private method_ `private EConnectionType GetAndroidFileServerNetworkConfig(DeploymentContext SC, out bool bUseCompression, out bool bLogFiles, out bool bReportStats, out bool bUseManualIPAddress, out string ManualIPAddress)`
- L1128-1132 _private method_ `private bool BuildWithHiddenSymbolVisibility(DeploymentContext SC)`
- L1134-1139 _private method_ `private bool GetSaveSymbols(DeploymentContext SC)`
- L1141-1146 _private method_ `private bool GetEnableBundle(DeploymentContext SC)`
- L1148-1153 _private method_ `private bool GetEnableUniversalAPK(DeploymentContext SC)`
- L1155-1163 _private method_ `private Int64 GetMaxOBBSizeAllowed(DeploymentContext SC)`
- L1165-1171 _private method_ `private bool AllowPatchOBBFile(DeploymentContext SC)`
- L1173-1185 _private method_ `private int AllowOverflowOBBFiles(DeploymentContext SC)`
- L1187-1209 _private method_ `private bool CreateOBBFile(DeploymentContext SC, string OutputFilename, List<FileReference> FilesForObb)`
- L1211-1226 _private method_ `private bool UpdateObbStoreVersion(string Filename)`
- L1239-1712 _public method_ `public override void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L1714-1717 _private* method_ `string GetAFSExecutable(UnrealTargetPlatform Target)`
- L1735-2011 _private method_ `private List<string> GenerateInstallBatchFile(bool bPackageDataInsideApk, string PackageName, string ApkName, ProjectParams Params, string ObbName, string DeviceObbName, bool bNoObbInstall, string PatchName, string DevicePatchName, bool bNoPatchInstall, List<OverflowBatchInstallInfo> OverflowInfo, bool bIsPC, bool bIsDistribution, bool bRequireRuntimeStoragePermission, bool bDisablePerfHarden, bool bUseAFS, bool bUseAFSProject, string AFSToken, UnrealTargetPlatform Target)`
- L2014-2093 _private method_ `private string[] GenerateUninstallBatchFile(bool bPackageDataInsideApk, string PackageName, string ApkName, ProjectParams Params, bool bIsPC, UnrealTargetPlatform Target)`
- L2095-2145 _private method_ `private string[] GenerateSymbolizeBatchFile(ProjectParams Params, string PackageName, string ApkName, DeploymentContext SC, UnrealArch Architecture, bool bIsPC)`
- L2147-2391 _public method_ `public override void GetFilesToArchive(ProjectParams Params, DeploymentContext SC)`
- L2393-2420 _private method_ `private void GetPlatformInstallOptions(DeploymentContext SC, out bool bNeedsPCInstall, out bool bNeedsMacInstall, out bool bNeedsLinuxInstall)`
- L2422-2430 _private method_ `private static string GetAdbCommandLine(string SerialNumber, string Args)`
- L2431-2439 _private method_ `private static string GetAFSCommandLine(string SerialNumber, string Args)`
- L2441 _private* field_ `static string LastSpewFilename = ""`
- L2443-2462 _public method_ `public static string ADBSpewFilter(string Message)`
- L2464-2467 _public method_ `public static IProcessResult RunAdbCommand(ProjectParams Params, string SerialNumber, string Args, string Input = null, ERunOptions Options = ERunOptions.Default, bool bShouldLogCommand = false)`
- L2469-2478 _private method_ `private static IProcessResult RunAdbCommand(string SerialNumber, string Args, string Input = null, ERunOptions Options = ERunOptions.Default, bool bShouldLogCommand = false)`
- L2480-2485 _private method_ `private string RunAndLogAdbCommand(ProjectParams Params, string SerialNumber, string Args, out int SuccessCode)`
- L2487-2490 _public method_ `public static IProcessResult RunAFSCommand(ProjectParams Params, string SerialNumber, string Args, string Input = null, ERunOptions Options = ERunOptions.Default, bool bShouldLogCommand = false)`
- L2492-2503 _private method_ `private static IProcessResult RunAFSCommand(string SerialNumber, string Args, string Input = null, ERunOptions Options = ERunOptions.Default, bool bShouldLogCommand = false)`
- L2505-2511 _private method_ `private string RunAndLogAFSCommand(ProjectParams Params, string SerialNumber, string Args, out int SuccessCode)`
- L2513-2551 _public method_ `public override void GetConnectedDevices(ProjectParams Params, out List<string> Devices)`
- L2578-2650 _private method_ `private bool RetrieveDeployedManifestsAFS(ProjectParams Params, DeploymentContext SC, string DeviceName, out List<string> UFSManifests, out List<string> NonUFSManifests, string AFSToken)`
- L2652-2702 _public method_ `public override bool RetrieveDeployedManifests(ProjectParams Params, DeploymentContext SC, string DeviceName, out List<string> UFSManifests, out List<string> NonUFSManifests)`
- L2715-2727 _private method_ `private string GetFileNameFromListing(string SingleLine)`
- L2729-2733 _private method_ `private bool WasBuiltWithDontBundleLibrariesInAPK(string FinalSOName)`
- L2735-3389 _private method_ `private void DeployAndroidFileServer(ProjectParams Params, DeploymentContext SC, string AFSToken)`
- L3391-3940 _private method_ `private void DeployADB(ProjectParams Params, DeploymentContext SC)`
- L3942-3959 _public method_ `public override void Deploy(ProjectParams Params, DeploymentContext SC)`
- L3962 _private field_ `private static string PackageLine = null`
- L3963 _private field_ `private static Mutex PackageInfoMutex = new Mutex()`
- L3964 _private field_ `private static string LaunchableActivityLine = null`
- L3965 _private field_ `private static string MetaAppTypeLine = null`
- L3966 _private field_ `private static Dictionary<string,string> MetaDataMap = ...`
- L3966 _private field_ `private static Dictionary< MetaDataMap = null`
- L3969-4010 _public method_ `public static string GetPackageInfo(string ApkName, bool bRetrieveVersionCode)`
- L4012-4023 _public method_ `public static string GetPackageInfo(string ApkName, DeploymentContext SC, bool bRetrieveVersionCode)`
- L4026-4068 _private method_ `private static string GetPackageInfoFromInfoFile(string ApkName, DeploymentContext SC, bool bRetrieveVersionCode)`
- L4071-4084 _public method_ `public static string GetLaunchableActivityName()`
- L4086-4093 _public method_ `public static string GetLaunchableActivityName(string ApkName)`
- L4096-4109 _public method_ `public static string GetMetaAppType()`
- L4111-4122 _public method_ `public static string GetMetadataValue(string MetadataKey)`
- L4125-4178 _private method_ `private static void ParsePackageName(object Sender, DataReceivedEventArgs Event)`
- L4180 _private field_ `static private string CachedAaptPath = null`
- L4181 _private field_ `static private string LastAndroidHomePath = null`
- L4183-4201 _private method_ `private static uint GetRevisionValue(string VersionString)`
- L4203-4263 _private method_ `private static string GetAaptPath()`
- L4265-4293 _private* method_ `static string GetIniValue(string Path, string Key)`
- L4295-4354 _private* method_ `static string GetSerialNumber(string DeviceName)`
- L4356-4391 _private method_ `private UnrealArch? GetBestDeviceArchitecture(ProjectParams Params, string DeviceName)`
- L4393-4426 _private method_ `private bool DeployClientCmdLineAFS(ProjectParams Params, string DeviceName, string PackageName, string AFSToken, string ClientCmdLine)`
- L4428-4441 _private method_ `private bool DeployClientCmdLineADB(ProjectParams Params, string DeviceName, string PackageName, string ClientCmdLine)`
- L4443-4446 _public method_ `public override void ModifyFileHostAddresses(List<string> HostAddresses)`
- L4448-4535 _public method_ `public override IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
- L4537-4545 _public method_ `public override void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L4551-4554 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)` — Gets cook platform name for this platform.
- L4556-4559 _public method_ `public override bool DeployLowerCaseFilenames(StagedFileType FileType)`
- L4561-4564 _public method_ `public override string LocalPathToTargetPath(string LocalPath, string LocalRoot)`
- L4566 _public property_ `public override bool IsSupported { get; }`
- L4568-4572 _public method_ `public override PakType RequiresPak(ProjectParams Params)`
- L4573-4579 _public property_ `public override bool SupportsMultiDeviceDeploy { get; }`
- L4588-4591 _public method_ `public override List<string> GetDebugFileExtensions()`
- L4593-4596 _public method_ `public override void StripSymbols(FileReference SourceFile, FileReference TargetFile)`
- L4598-4601 _public method_ `public override void StripAllSymbols(FileReference SourceFile, FileReference TargetFile)`

#### class `AndroidPlatform.AdbCreatedProcess`  
`public class AdbCreatedProcess : AutomationTool.IProcessResult`  
_public; L32-165_
- inherits: `AutomationTool.IProcessResult`
- L34 _private field_ `private readonly object StopSyncObject = new object()`
- L35 _private* field_ `IProcessResult AdbLogProcess`
- L36 _private* field_ `string LogPath`
- L37 _private* field_ `string PackageName`
- L38 _private* field_ `string DeviceName`
- L39 _private* field_ `int LogFileProcessExitCode = 0`
- L40 _private* field_ `bool bStopped = false`
- L42-53 _public ctor_ `public AdbCreatedProcess( IProcessResult InAdbLogProcess, string InLogPath, string InPackageName, string InDeviceName)`
- L55-58 _private* dtor_ `~AdbCreatedProcess()`
- L60-75 _public method_ `public void StopProcess(bool KillDescendants = true)`
- L77-87 _public property_ `public bool HasExited { get; }`
- L89-92 _public method_ `public string GetProcessName()`
- L94-96 _public method_ `public void OnProcessExited()`
- L98-101 _public method_ `public void DisposeProcess()`
- L103-105 _public method_ `public void StdOut(object sender, DataReceivedEventArgs e)`
- L107-109 _public method_ `public void StdErr(object sender, DataReceivedEventArgs e)`
- L111-115 _public property_ `public int ExitCode { get; set; }`
- L117 _public property_ `public bool bExitCodeSuccess => ...`
- L119-122 _public property_ `public string Output { get; }`
- L124-127 _public property_ `public Process ProcessObject { get; }`
- L129-136 _public method_ `public void WaitForExit()`
- L138-141 _public method_ `public FileReference WriteOutputToFile(string FileName)`
- L143-150 _private method_ `private bool IsPackageRunningOnDevice()`
- L152-164 _private method_ `private void DumpDeviceOutputToLogFiles()`

#### enum `AndroidPlatform.EBatchType`  
`enum EBatchType`  
_private*; L947-952_
- L949 _public* enumerator_ `Install`
- L950 _public* enumerator_ `Uninstall`
- L951 _public* enumerator_ `Symbolize`

#### enum `AndroidPlatform.EConnectionType`  
`enum EConnectionType`  
_private*; L1061-1066_
- L1063 _public* enumerator_ `USBOnly`
- L1064 _public* enumerator_ `NetworkOnly`
- L1065 _public* enumerator_ `Combined`

#### class `AndroidPlatform.OverflowFileInfo`  
`private class OverflowFileInfo`  
_private; L1227-1237_
- L1229-1233 _public ctor_ `public OverflowFileInfo(List<FileReference> InFilesForOverflow, Int64 InOverflowObbSize)`
- L1235 _public property_ `public List<FileReference> FilesForOverflow { get; set; }`
- L1236 _public property_ `public Int64 OverflowObbSize { get; set; }`

#### class `AndroidPlatform.OverflowBatchInstallInfo`  
`private class OverflowBatchInstallInfo`  
_private; L1719-1733_
- L1721-1727 _public ctor_ `public OverflowBatchInstallInfo(int InOverflowIndex, string InDeviceOverflowName, string InOverflowName, bool InNoOverflowInstall)`
- L1729 _public property_ `public int OverflowIndex { get; }`
- L1730 _public property_ `public string DeviceOverflowName { get; }`
- L1731 _public property_ `public string OverflowName { get; }`
- L1732 _public property_ `public bool bNoOverflowInstall { get; }`

#### class `AndroidPlatform.LongestFirst`  
`internal class LongestFirst : IComparer<string>`  
_internal; L2704-2711_
- inherits: `IComparer<string>`
- L2706-2710 _public method_ `public int Compare(string a, string b)`

#### class `AndroidPlatformMulti`  
`public class AndroidPlatformMulti : AndroidPlatform`  
_public; L4604-4614_
- inherits: `AndroidPlatform`
- L4606-4609 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L4610-4613 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `AndroidPlatformDXT`  
`public class AndroidPlatformDXT : AndroidPlatform`  
_public; L4616-4627_
- inherits: `AndroidPlatform`
- L4618-4621 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L4623-4626 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `AndroidPlatformETC2`  
`public class AndroidPlatformETC2 : AndroidPlatform`  
_public; L4628-4638_
- inherits: `AndroidPlatform`
- L4630-4633 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L4634-4637 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `AndroidPlatformASTC`  
`public class AndroidPlatformASTC : AndroidPlatform`  
_public; L4640-4650_
- inherits: `AndroidPlatform`
- L4642-4645 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L4646-4649 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `AndroidPlatformOpenXR`  
`public class AndroidPlatformOpenXR : AndroidPlatform`  
_public; L4652-4662_
- inherits: `AndroidPlatform`
- L4654-4657 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L4658-4661 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

### `Source/Programs/AutomationTool/Android/Properties/AssemblyInfo.cs` (Android.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/Android/Scripts/AndroidAutomationUtils.cs` (Android.Automation)


#### class `ReplaceAndroidExecutable`  
`public class ReplaceAndroidExecutable : BuildCommand`  
_public; L12-49_
- inherits: `BuildCommand`
- L14-48 _public method_ `public override ExitCode Execute()`
