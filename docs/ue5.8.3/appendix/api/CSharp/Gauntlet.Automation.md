# CSharp / Gauntlet.Automation

- project root: `Source/Programs/AutomationTool/Gauntlet`
- files: 139; symbols: 4828
- symbol kinds: class=366, const=39, ctor=255, delegate=10, dtor=20, enum=39, enumerator=207, field=1149, interface=55, method=1667, operator=4, property=1009, struct=8
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Gauntlet/Framework/Account/Gauntlet.Account.cs` (Gauntlet.Automation)


#### class `Gauntlet.Account`  
`public abstract class Account : IConfigOption<UnrealAppConfig>`  
_public; L12-24_
- inherits: `IConfigOption<UnrealAppConfig>`
- desc: Defines an account that can be used in tests by appending credential information to the command line
- L18 _public method_ `public abstract void ApplyToConfig(UnrealAppConfig AppConfig)` — Called to apply our data to the provided config
- L23 _public property_ `public abstract string Username { get; set; }` — Username for this account.

#### class `Gauntlet.EpicAccount`  
`public class EpicAccount : Account`  
_public; L30-54_
- inherits: `Account`
- desc: Epic account implementation, all of our accounts can be used on a client by providing the type, username, and password/token on the command line
- L32 _public property_ `public override string Username { get; set; }`
- L34 _public property_ `public string Password { get; set; }`
- L36 _public property_ `public string EpicAccountId { get; set; }`
- L38-42 _public ctor_ `public EpicAccount(string InUsername, string InPassword)`
- L44-47 _public ctor_ `public EpicAccount(string InUserName, string InPassword, string InAccountId) : this(InUserName, InPassword)`
- L49-53 _public method_ `public override void ApplyToConfig(UnrealAppConfig AppConfig)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Account/Gauntlet.AccountPool.cs` (Gauntlet.Automation)


#### class `Gauntlet.AccountPool`  
`public class AccountPool`  
_public; L11-66_
- L17 _private field_ `private static IManagedAccountPool _Instance` — Singleton
- L19-22 _public method_ `public static void Initialize()`
- L24-30 _private* dtor_ `~AccountPool()`
- L32-43 _public method_ `public static void Initialize<T>()`
- L45-55 _public property_ `public static IManagedAccountPool Instance { get; }`
- L57-64 _public method_ `public static void Shutdown()`

#### interface `Gauntlet.IManagedAccountPool`  
`public interface IManagedAccountPool: IDisposable`  
_public; L68-75_
- inherits: `IDisposable`
- L70 _public* method_ `void RegisterAccount(Account InAccount)`
- L72 _public* method_ `void ReleaseAccount(Account InAccount)`
- L74 _public* method_ `Account ReserveAccount()`

#### class `Gauntlet.ManagedAccountPool`  
`public class ManagedAccountPool : IManagedAccountPool`  
_public; L81-197_
- inherits: `IManagedAccountPool`
- desc: A pool of accounts for tests to use. The pool should be filled by the project-specific script that derives from RunUnrealTests
- L87 _protected field_ `protected Object LockObject = new Object()` — Object used for locking access to internal data
- L92 _protected field_ `protected List<Account> AllAccounts = new List<Account>()` — List of all registered accounts
- L97 _protected field_ `protected Dictionary<Account, bool> ReservedAccounts = ...` — Accounts that have been reserved
- L97 _protected field_ `protected Dictionary< ReservedAccounts = new Dictionary<Account, bool>()` — Accounts that have been reserved
- L102 _protected field_ `protected List<Account> RandomlyOrderedList = new List<Account>()` — A random ordering of AllAccounts
- L105-108 _private* dtor_ `~ManagedAccountPool()`
- L112-116 _public method_ `public void Dispose()`
- L123-138 _protected method_ `protected void Dispose(bool disposing)` — Perform actual dispose behavior
- L140-143 _public method_ `public void RegisterAccount(Account InAccount)`
- L145-152 _public method_ `public void ClearReservatios()`
- L154-160 _public method_ `public void ReleaseAccount(Account InAccount)`
- L162-196 _public method_ `virtual public Account ReserveAccount()`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.AppConfig.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IAppConfig`  
`public interface IAppConfig`  
_public; L13-34_
- desc: IAppConfig defines an interface that can express the configuration required to install and run an instance of a given app
- L18 _public* property_ `string Name { get; }` — Name of the app
- L23 _public* property_ `string CommandLine { get; }` — Arguments to execute the app with
- L28 _public* property_ `string Sandbox { get; }` — Sandbox that we'd like to install this instance in
- L33 _public* property_ `IBuild Build { get; }` — Build that the application uses

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.AppInstall.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IAppInstall`  
`public interface IAppInstall`  
_public; L12-44_
- desc: IAppInstall represents an instance of an application that has been installed on a device and may now be run
- L17 _public* property_ `string Name { get; }` — Description of this app
- L23 _public* method_ `IAppInstance Run()` — Create a running instance of the app
- L28 _public* property_ `ITargetDevice Device { get; }` — The device that we'll be run on

#### interface `Gauntlet.IAppInstall.IDynamicCommandLine`  
`public interface IDynamicCommandLine`  
_public; L36-43_
- desc: IAppInstallDynamicCommandLine can be implemented by IAppInstall classes where the platform allows the command line to be updated after installation
- L42 _public* method_ `void AppendCommandline(string AdditionalCommandLine)` — Appends the given string to the installed application's command line

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.AppInstance.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IAppInstance`  
`public interface IAppInstance`  
_public; L13-80_
- desc: Interface that represents an instance of an app running on a device
- L18 _public* property_ `bool HasExited { get; }` — Returns true/false if the process has exited for any reason
- L23 _public* property_ `string StdOut { get; }` — Current StdOut of the process. Not efficient when the process is running. Use GetLogBufferReader() instead.
- L28 _public* method_ `ILogStreamReader GetLogReader()` — Return a new log reader with an internal cursor
- L35 _public* method_ `ILogStreamReader GetLogBufferReader()` — Return a new log buffer reader with an internal cursor. Might not give access to the full log content (usually the last 1024 lines). Use GetLogReader() if you need the log from the beginning.
- L42 _public* method_ `bool WriteOutputToFile(string FilePath)` — Write output to file. Return true if there was output data to write.
- L47 _public* property_ `int ExitCode { get; }` — Exit code of the process.
- L52 _public* property_ `bool WasKilled { get; }` — Returns true if the process exited due to Kill() being called
- L57 _public* property_ `string CommandLine { get; }` — Path to commandline used to start the process
- L62 _public* property_ `string ArtifactPath { get; }` — Path to artifacts from the process
- L67 _public* property_ `ITargetDevice Device { get; }` — Device that the app was run on
- L72 _public* method_ `void Kill(bool GenerateDumpOnKill = false)` — Kills the process if its running (no need to call WaitForExit)
- L78 _public* method_ `int WaitForExit()` — Waits for the process to exit normally

#### interface `Gauntlet.IWithPLMSuspend`  
`public interface IWithPLMSuspend`  
_public; L85-96_
- desc: Interface used by IAppInstance if they support Suspend/Resume
- L90 _public* method_ `bool Suspend()` — Attempt to suspend the running application. Correlates to FCoreDelegates::ApplicationWillEnterBackgroundDelegate
- L95 _public* method_ `bool Resume()` — Attempts to resume a suspended application. Correlates to FCoreDelegates::ApplicationHasEnteredForegroundDelegate

#### interface `Gauntlet.IWithPLMConstrain`  
`public interface IWithPLMConstrain`  
_public; L101-112_
- desc: Interface used by IAppInstance if they support Constrain/Unconstrain
- L106 _public* method_ `bool Constrain()` — Attempts to contrain the running application. Correlates to FCoreDelegates::ApplicationWillDeactivateDelegate
- L111 _public* method_ `bool Unconstrain()` — Attempts to unconstained a constrained application. Correlates to FCoreDelegates::ApplicationHasReactivatedDelegate

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.BaseTestNode.cs` (Gauntlet.Automation)


#### class `Gauntlet.BaseTest`  
`public abstract class BaseTest : ITestNode`  
_public; L11-228_
- inherits: `ITestNode`
- desc: Simple node that implements the ITestNode interface and provides some convenience functions for inherited tests to use
- L16 _public property_ `public abstract float MaxDuration { get; set; }` — Override this to set the max running time for this test
- L21 _public property_ `public virtual EMaxDurationReachedResult MaxDurationReachedResult { get; set; }` — What the test result should be treated as if we reach max duration.
- L26 _public property_ `public virtual TestPriority Priority { get; }` — Override this to set the priority of this test
- L31 _public property_ `public abstract string Name { get; }` — Return the name of this test
- L36 _public property_ `public virtual bool HasWarnings { get; set; }` — Returns true if the test has encountered warnings. Test is expected to list any warnings it considers appropriate in the summary
- L41 _public property_ `public virtual string CancellationReason { get; set; }` — Returns reason for the test cancellation
- L46 _public property_ `public virtual bool WasCancelled { get; set; }` — Returns true if the test was cancelled
- L51 _private field_ `private TestStatus InnerStatus` — Internal status state
- L56 _public property_ `public virtual bool LogWarningsAndErrorsAfterSummary { get; set; }` — Return true if the warnings and errors needs to log after summary
- L61-64 _public ctor_ `public BaseTest()` — Default BaseTest Constructor
- L70 _public method_ `public abstract TestResult GetTestResult()` — OVerride this to return the result of the test
- L76 _public method_ `public abstract void SetTestResult(TestResult InTestResult)` — Set the test result value of the test.
- L81-83 _public method_ `public virtual void AddTestEvent(UnrealTestEvent InEvent)` — Add a new test event to be rolled up into the summary at the end of this test.
- L89-92 _public method_ `public virtual string GetTestSummary()` — Summarize the result of the test
- L98-101 _public method_ `public virtual IEnumerable<string> GetWarnings()` — Return list of warnings. Empty by default
- L107-110 _public method_ `public virtual IEnumerable<string> GetErrors()` — Return list of errors. Empty by default
- L112-117 _public method_ `public virtual string GetRunLocalCommand(string LaunchingBuildCommand)`
- L123-126 _protected method_ `protected void SetTestStatus(TestStatus InStatus)` — Updates the test status to the passed in value
- L132-136 _protected method_ `protected void MarkTestStarted()` — Mark the test as started
- L142-145 _protected method_ `protected void MarkTestComplete()` — Mark the test as complete
- L151-154 _public method_ `public TestStatus GetTestStatus()` — Return our internal status
- L156-159 _public method_ `public virtual bool IsReadyToStart()`
- L165 _public method_ `public abstract bool StartTest(int Pass, int NumPasses)` — Called to request the test launch. Should call MarkTestComplete
- L171 _public method_ `public abstract void CleanupTest()` — Called to request the test is shutdown
- L178-182 _public method_ `public virtual bool RestartTest()` — Called if TestResult returns WantRetry. Can be overridden for something more elegant than a hard shutdown/launch
- L189-191 _public method_ `public virtual void TickTest()` — Gives the test a chance to perform logic. Should call MarkComplete() when it detects a success or error state
- L198-201 _public method_ `public virtual void SetCancellationReason(string InReason)` — Sets Cancellation Reason.
- L208-211 _public method_ `public virtual void StopTest(StopReason InReason)` — Called after the test is completed and shutdown
- L218-220 _public method_ `public virtual void SetContext(ITestContext InContext)` — Helper to set context
- L225-227 _public method_ `public virtual void DisplayCommandlineHelp()` — Output all defined commandline information for this test to the gauntlet window and exit test early.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.BuildSource.cs` (Gauntlet.Automation)


#### enum `Gauntlet.BuildFlags`  
`public enum BuildFlags`  
_public; L14-24_
- attrs: `[Flags]`
- desc: Flags that are used to describe the characteristics or abilitites of a build
- L16 _public* enumerator_ `None = 0`
- L17 _public* enumerator_ `Packaged = (1 << 0)`
- L18 _public* enumerator_ `Loose = (1 << 1)`
- L19 _public* enumerator_ `CanReplaceCommandLine = (1 << 2)`
- L20 _public* enumerator_ `CanReplaceExecutable = (1 << 3)`
- L21 _public* enumerator_ `Bulk = (1 << 4)`
- L22 _public* enumerator_ `NotBulk = (1 << 5)`
- L23 _public* enumerator_ `ContentOnlyProject = (1 << 6)`

#### interface `Gauntlet.IBuild`  
`public interface IBuild`  
_public; L30-68_
- desc: An interface that represents a build. A build is defined as something that a device is able to install, hence most if not all implementations will have a strong association with the TargetDevice for that platform
- L35 _public* property_ `int PreferenceOrder { get; }` — Preference order for this build type vs. other build types. Lower is more prefered.
- L40 _public* property_ `BuildFlags Flags { get; }` — Flags that describe the properties of this build
- L45 _public* property_ `UnrealTargetPlatform Platform { get; }` — Platform that this build is for
- L50 _public* property_ `string Flavor { get; }` — Special property of the build (vanilla, asan, uban, etc)
- L55 _public* property_ `UnrealTargetConfiguration Configuration { get; }` — Configuration of this build
- L60 _public* property_ `bool SupportsAdditionalFileCopy { get; }` — Does this build support additional loose files be copied to the device
- L67 _public* method_ `bool CanSupportRole(UnrealTargetRole Role)` — Check if this buld is able to support the provided role

#### interface `Gauntlet.IBuildSource`  
`public interface IBuildSource`  
_public; L74-79_
- desc: Represents a class that can discover builds
- L76 _public* property_ `string BuildName { get; }`
- L78 _public* method_ `bool CanSupportPlatform(UnrealTargetPlatform Platform)`

#### interface `Gauntlet.IFolderBuildSource`  
`public interface IFolderBuildSource : IBuildSource`  
_public; L84-87_
- inherits: `IBuildSource`
- desc: Represents a class that can discover builds from a folder path
- L86 _public* method_ `List<IBuild> GetBuildsAtPath(string InProjectName, string InPath, int MaxRecursion = 3)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.BuildValidator.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IBuildValidator`  
`public interface IBuildValidator`  
_public; L13-18_
- desc: Utility for returning the path to a "Latest Good" build This is used to determine build paths when -build=LKG or -build=LatestGood
- L15 _public* property_ `string Name { get; }`
- L16 _public* method_ `bool CanSupportProject(string InProjectName)`
- L17 _public* method_ `string GetLatestGoodBuild()`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.ConfigOption.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IConfigOption`  
`public interface IConfigOption<ConfigType> where ConfigType : IAppConfig`  
_public; L13-17_
- constraints: `where ConfigType : IAppConfig`
- desc: An interface to a set of options that implement the IAppConfig interface
- L16 _public* method_ `void ApplyToConfig(ConfigType AppConfig)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.Container.cs` (Gauntlet.Automation)


#### class `Gauntlet.ContainerInfo`  
`public class ContainerInfo`  
_public; L12-18_
- desc: POCO class for apps that can run through containers.
- L14 _public property_ `public string ImageName { get; set; }`
- L15 _public property_ `public string ContainerName { get; set; }`
- L16 _public property_ `public string RunCommandPrepend { get; set; }`
- L17 _public property_ `public string WorkingDir { get; set; }`

#### interface `Gauntlet.IContainerized`  
`public interface IContainerized`  
_public; L20-26_
- L25 _public* property_ `ContainerInfo ContainerInfo { get; set; }` — For apps running through Docker containers.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.Database.cs` (Gauntlet.Automation)


#### interface `Gauntlet.ITelemetryContext`  
`public interface ITelemetryContext`  
_public; L19-22_
- desc: Hold information about the telemetry context
- L21 _public* method_ `object GetProperty(string Name)`

#### interface `Gauntlet.IDatabaseDriver`  
`public interface IDatabaseDriver<Data> where Data : class`  
_public; L27-48_
- constraints: `where Data : class`
- desc: Interface to drive Database submission
- L35 _public* method_ `bool SubmitDataItems(IEnumerable<Data> DataItems, ITelemetryContext Context)` — Submit collection of object to target Database, use TestContext to complete data modeling.
- L41 _public* method_ `DataSet ExecuteQuery(string Query)` — Execute a Query through the database driver
- L47 _public* method_ `DataSet FetchData(ITelemetryContext Conditions)` — Fetch collection of object from target Database, uses Conditions to narrow down pool of data.

#### interface `Gauntlet.IDatabaseConfig`  
`public interface IDatabaseConfig<Data> where Data : class`  
_public; L53-57_
- constraints: `where Data : class`
- desc: Interface for Database Configuration
- L55 _public* method_ `void LoadConfig(string ConfigFilePath)`
- L56 _public* method_ `IDatabaseDriver<Data> GetDriver()`

#### interface `Gauntlet.IMySQLConfig`  
`public interface IMySQLConfig<Data> where Data : class`  
_public; L62-81_
- constraints: `where Data : class`
- desc: Interface for data type MySQL Configuration
- L67 _public* method_ `string GetTableName()` — Get Target Table name based on data type
- L72 _public* method_ `IEnumerable<string> GetTableColumns()` — Get Target Table columns based on data type
- L80 _public* method_ `IEnumerable<string> FormatDataForTable(Data InData, ITelemetryContext InContext)` — Format the data for target table based on data type

#### class `Gauntlet.MySQLDriver`  
`public class MySQLDriver<Data> : IDatabaseDriver<Data> where Data : class`  
_public; L83-178_
- inherits: `IDatabaseDriver<Data>`
- constraints: `where Data : class`
- L85 _protected field_ `protected MySQLConfig<Data> Config`
- L87-98 _public ctor_ `public MySQLDriver(MySQLConfig<Data> InConfig)`
- L100-103 _public method_ `public override string ToString()`
- L105-108 _public method_ `public DataSet ExecuteQuery(string SqlQuery)`
- L110-125 _public method_ `public bool Insert(string Table, IEnumerable<string> Columns, IEnumerable<IEnumerable<string>> Rows)`
- L127-130 _private method_ `private IEnumerable<IEnumerable<T>> ChunkIt<T>(IEnumerable<T> ToChunk, int ChunkSize = 1000)`
- L132-162 _public method_ `public bool SubmitDataItems(IEnumerable<Data> DataRows, ITelemetryContext Context)`
- L164-167 _public method_ `public virtual bool PreSubmitQuery(IEnumerable<Data> DataRows, ITelemetryContext Context)`
- L168-171 _public method_ `public virtual bool PostSubmitQuery(IEnumerable<Data> DataRows, ITelemetryContext Context)`
- L173-176 _public method_ `public DataSet FetchData(ITelemetryContext Context)`

#### class `Gauntlet.MySQLConfig`  
`public abstract class MySQLConfig<Data> : IDatabaseConfig<Data>, IMySQLConfig<Data> where Data : class`  
_public; L180-296_
- inherits: `IDatabaseConfig<Data>, IMySQLConfig<Data>`
- constraints: `where Data : class`
- L182 _public property_ `public string ConfigString { get; set; }`
- L183 _public property_ `public string DatabaseName { get; set; }`
- L184 _protected field_ `protected Dictionary<string, string> KeyValuePairs = ...`
- L184 _protected field_ `protected Dictionary< KeyValuePairs = null`
- L186-221 _public method_ `public virtual void LoadConfig(string ConfigFilePath)`
- L223-245 _public method_ `public string GetConfigValue(string Key)`
- L247-250 _public method_ `public IDatabaseDriver<Data> GetDriver()`
- L259-262 _public method_ `public virtual bool PreSubmitQuery(IDatabaseDriver<Data> Driver, IEnumerable<Data> DataRows, ITelemetryContext Context)` — Override to add pre-submit query.
- L270-273 _public method_ `public virtual bool PostSubmitQuery(IDatabaseDriver<Data> Driver, IEnumerable<Data> DataRows, ITelemetryContext Context)` — Override to add post-submit query.
- L277 _public method_ `public abstract string GetTableName()` — Get Target Table name based on data type
- L281 _public method_ `public abstract IEnumerable<string> GetTableColumns()` — Get Target Table columns based on data type
- L286 _public method_ `public abstract IEnumerable<string> FormatDataForTable(Data InData, ITelemetryContext InContext)` — Format the data for target table based on data type
- L292-295 _public method_ `public virtual string GetFetchDataQuery(ITelemetryContext InContext)` — Return the query to fetch data

#### class `Gauntlet.JsonHttpRequestDriver`  
`public class JsonHttpRequestDriver<Data> : IDatabaseDriver<Data> where Data : class`  
_public; L298-361_
- inherits: `IDatabaseDriver<Data>`
- constraints: `where Data : class`
- L300 _protected field_ `protected JsonHttpRequestConfig<Data> Config`
- L301-312 _public ctor_ `public JsonHttpRequestDriver(JsonHttpRequestConfig<Data> InConfig)`
- L313-327 _public method_ `public virtual bool SubmitDataItems(IEnumerable<Data> DataItems, ITelemetryContext Context)`
- L328-331 _private method_ `private IEnumerable<IEnumerable<T>> ChunkIt<T>(IEnumerable<T> ToChunk, int ChunkSize = 1000)`
- L332-352 _public method_ `public virtual DataSet ExecuteQuery(string Query)`
- L353-356 _public method_ `public DataSet FetchData(ITelemetryContext Conditions)`
- L357-360 _public method_ `public override string ToString()`

#### class `Gauntlet.JsonHttpRequestConfig`  
`public abstract class JsonHttpRequestConfig<Data> : IDatabaseConfig<Data>where Data : class`  
_public; L363-419_
- inherits: `IDatabaseConfig<Data>where Data : class`
- L365 _public field_ `public string Host`
- L366 _public field_ `public string Path`
- L367 _public field_ `public JsonHttpRequestConfig.Auth Auth`
- L368-406 _public method_ `public virtual void LoadConfig(string ConfigFilePath)`
- L412 _public method_ `public abstract IEnumerable<object> FormatData(IEnumerable<Data> DataItems, ITelemetryContext Context)` — Format the data for target data type
- L414-418 _public method_ `public virtual IDatabaseDriver<Data> GetDriver()`

#### class `Gauntlet.JsonHttpRequestConfig`  
`public class JsonHttpRequestConfig`  
_public; L421-441_
- L429 _public property_ `public string endpoint { get; set; }`
- L430 _public property_ `public Auth authorization { get; set; }`
- L432-440 _public method_ `public static JsonHttpRequestConfig LoadFromFile(string FilePath)`

#### class `Gauntlet.JsonHttpRequestConfig.Auth`  
`public class Auth`  
_public; L423-427_
- L425 _public property_ `public string target { get; set; }`
- L426 _public property_ `public string token { get; set; }`

#### class `Gauntlet.DatabaseConfigManager`  
`public class DatabaseConfigManager<Data> where Data : class`  
_public; L443-454_
- constraints: `where Data : class`
- L445 _protected field_ `protected static IEnumerable<IDatabaseConfig<Data>> Configs`
- L446-449 _private* ctor_ `static DatabaseConfigManager()`
- L450-453 _public method_ `public static IDatabaseConfig<Data> GetConfigByName(string Name)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.Denylist.cs` (Gauntlet.Automation)


#### class `Gauntlet.DenylistEntry`  
`public class DenylistEntry`  
_public; L16-34_
- desc: Information that defines a device
- L18 _public field_ `public string TestName`
- L20 _public field_ `public string[] Platforms`
- L22 _public field_ `public string BranchName`
- L23-28 _public ctor_ `public DenylistEntry()`
- L30-33 _public method_ `public override string ToString()`

#### class `Gauntlet.Denylist`  
`public class Denylist`  
_public; L37-120_
- L42 _private field_ `private static Denylist _Instance` — Static instance
- L44 _private* field_ `IEnumerable<DenylistEntry> DenylistEntries`
- L49-60 _protected ctor_ `protected Denylist()` — Protected constructor - code should use DevicePool.Instance
- L65-75 _public property_ `public static Denylist Instance { get; }` — Access to our singleton
- L77-104 _protected method_ `protected void LoadDenylist(string InFilePath)`
- L105-119 _public method_ `public bool IsTestDenylisted(string InNodeName, UnrealTargetPlatform InPlatform, string InBranchName)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.OnlineServiceLogin.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IOnlineServiceLogin`  
`public interface IOnlineServiceLogin`  
_public; L9-16_
- desc: TargetDevice extension for platforms that contain an online service. Enables more robust user sign in verification.
- L15 _public* method_ `bool VerifyLogin()` — Verifies the device has connected to its relevant platform network.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.OverlayExecutable.cs` (Gauntlet.Automation)


#### class `Gauntlet.OverlayExecutable`  
`public class OverlayExecutable`  
_public; L19-120_
- desc: Manages the overlaying of a development executable over an existing build. These are useful for testing code changes without needing to re-cook or re-package builds. To use overlay executables, simply specify -dev on the UAT commandline. The overlay executable will automatically be applied as long as the following conditions are met - The build being used supports Overlay executables. See BuildFlags.CanReplaceExecutable - The development executable's write time is newer than that of the supplied builds write time
- L21 _private field_ `private string ProjectName`
- L22 _private field_ `private string Flavor`
- L23 _private field_ `private FileReference ProjectFile`
- L24 _private field_ `private UnrealTargetPlatform Platform`
- L25 _private field_ `private UnrealTargetConfiguration Configuration`
- L26 _private field_ `private UnrealTargetRole Role`
- L28-30 _public ctor_ `public OverlayExecutable(UnrealSessionRole SessionRole, string ProjectName, FileReference ProjectFile) : this(SessionRole.Platform.Value, SessionRole.Configuration, SessionRole.RoleType, ProjectName, ProjectFile, SessionRole.RequiredFlavor)`
- L32-41 _public ctor_ `public OverlayExecutable(UnrealTargetPlatform Platform, UnrealTargetConfiguration Configuration, UnrealTargetRole RoleType, string ProjectName, FileReference ProjectFile, string Flavor = "")`
- L51-119 _public method_ `public bool GetOverlay(string BaseExecutable, out string OverlayExecutable, string ExtensionOverride = null)` — Attempts to get the path to a local executable if it is newer than the base executable

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.TargetDevice.cs` (Gauntlet.Automation)


#### interface `Gauntlet.ITargetDevice`  
`public interface ITargetDevice : IDisposable`  
_public; L18-142_
- inherits: `IDisposable`
- desc: Base class for a device that is able to run applications
- L23 _public* property_ `string Name { get; }` — Name of this device
- L28 _public* property_ `UnrealTargetPlatform? Platform { get; }` — Platform of this device
- L33 _public* property_ `CommandUtils.ERunOptions RunOptions { get; set; }` — Options used when running processes
- L39 _public* property_ `bool IsAvailable { get; }` — Is the device available for use? Note: If we are the process holding a connection then this should still return true
- L44 _public* property_ `bool IsConnected { get; }` — Are we connected to this device?
- L50 _public* method_ `bool Connect()` — Connect and reserve the device
- L57 _public* method_ `bool Disconnect(bool bForce=false)` — Disconnect the device.
- L63 _public* property_ `bool IsOn { get; }` — Is the device powered on? TODO - Do we need to have a way of expressing whether power changes are supported
- L69 _public* method_ `bool PowerOn()` — Request the device power on. Should block until the change succeeds (or fails)
- L75 _public* method_ `bool PowerOff()` — Request the device power on. Should block until the change succeeds (or fails)
- L81 _public* method_ `bool Reboot()` — Request the device power on. Should block until the change succeeds (or fails)
- L88 _public* method_ `Dictionary<EIntendedBaseCopyDirectory, string> GetPlatformDirectoryMappings()` — Returns a Dictionary of EIntendedBaseCopyDirectory keys and their corresponding file path string values. If a platform has not set up these mappings, returns an empty Dictionary and warns.
- L90 _public* method_ `IAppInstall InstallApplication(UnrealAppConfig AppConfiguration)`
- L92 _public* method_ `IAppInstance Run(IAppInstall App)`
- L101 _public* method_ `void FullClean()` — Fully cleans the device by deleting - Artifacts and other loose files associated with UE processes - Staged/Packaged builds
- L106 _public* method_ `void CleanArtifacts(UnrealAppConfig AppConfiguration = null)` — Deletes artifacts and other loose files associated with UE processes
- L111 _public* property_ `string LocalCachePath { get; }` — Local cache path
- L117 _public* method_ `void InstallBuild(UnrealAppConfig AppConfiguration)` — Installs a build to the device
- L124 _public* method_ `IAppInstall CreateAppInstall(UnrealAppConfig AppConfiguration)` — Create an IAppInstall that is configured by the provided AppConfiguration
- L130 _public* method_ `void CopyAdditionalFiles(IEnumerable<UnrealFileToCopy> FilesToCopy)` — Copies any additional files to the device
- L136-139 _public method_ `public void TakeScreenshot(string ScreenshotName)` — Take a screenshot using device soft Filename is saved in the format of: yy-MM-dd-HH-mm-ss-ff

#### interface `Gauntlet.IRunningStateOptions`  
`public interface IRunningStateOptions`  
_public; L147-163_
- desc: Interface used by TargetDevice* classes to track spawned application running state.
- L152 _public* property_ `bool WaitForRunningState { get; set; }` — Whether or not to sleep after launching an app before querying for its running state.
- L157 _public* property_ `int SecondsToRunningState { get; set; }` — The number of seconds to sleep after launching an app before querying for its running state.
- L162 _public* property_ `int CachedStateRefresh { get; set; }` — Interval of time between app running state queries, in seconds.

#### interface `Gauntlet.IDeviceSource`  
`public interface IDeviceSource`  
_public; L168-171_
- desc: Represents a class able to provide devices
- L170 _public* method_ `bool CanSupportPlatform(UnrealTargetPlatform? Platform)`

#### interface `Gauntlet.IDefaultDeviceSource`  
`public interface IDefaultDeviceSource : IDeviceSource`  
_public; L176-179_
- inherits: `IDeviceSource`
- desc: Represents a class that provides locally available devices
- L178 _public* method_ `ITargetDevice[] GetDefaultDevices()`

#### interface `Gauntlet.IDeviceFactory`  
`public interface IDeviceFactory : IDeviceSource`  
_public; L184-187_
- inherits: `IDeviceSource`
- desc: Represents a class capable of creating devices of a specific type
- L186 _public* method_ `ITargetDevice CreateDevice(string InRef, string InLocalCache, string InParam=null)`

#### interface `Gauntlet.IDeviceService`  
`public interface IDeviceService : IDeviceSource`  
_public; L192-195_
- inherits: `IDeviceSource`
- desc: Represents a class that provides services for available devices
- L194 _public* method_ `void CleanupDevices()`

#### interface `Gauntlet.IVirtualLocalDevice`  
`public interface IVirtualLocalDevice : IDeviceSource`  
_public; L200-204_
- inherits: `IDeviceSource`
- desc: Represents a class that can provides virtual local devices
- L202 _public* method_ `bool CanRunVirtualFromPlatform(UnrealTargetPlatform? Platfrom)`
- L203 _public* method_ `UnrealTargetPlatform? GetPlatform()`

#### interface `Gauntlet.IDeviceBuildSupport`  
`public interface IDeviceBuildSupport : IDeviceSource`  
_public; L209-214_
- inherits: `IDeviceSource`
- desc: Represents a class that tell what build the device support
- L211 _public* method_ `bool CanSupportBuildType(BuildFlags Flag)`
- L212 _public* method_ `UnrealTargetPlatform? GetPlatform()`
- L213 _public* method_ `bool NeedBuildDeployed()`

#### class `Gauntlet.BaseBuildSupport`  
`public abstract class BaseBuildSupport : IDeviceBuildSupport`  
_public; L215-236_
- inherits: `IDeviceBuildSupport`
- L217 _protected property_ `protected virtual BuildFlags SupportedBuildTypes => ...`
- L218 _protected property_ `protected virtual UnrealTargetPlatform? Platform => ...`
- L220-223 _public method_ `public bool CanSupportBuildType(BuildFlags Flag)`
- L225-228 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? InPlatform)`
- L230-233 _public method_ `public UnrealTargetPlatform? GetPlatform()`
- L235 _public method_ `public virtual bool NeedBuildDeployed()`

#### interface `Gauntlet.IPlatformTargetSupport`  
`public interface IPlatformTargetSupport`  
_public; L243-264_
- desc: If platform supports host mounting of files or other platform specific functionality, this interface provides a way to provide that information without needing an instance of the device.
- L251 _public* method_ `string GetHostMountedPath(string Path)` — If host mounting is supported, return the equivalent host mounted path for given platform.
- L258 _public* method_ `bool IsHostMountingSupported()` — Returns true if host mounting is supported on given platform.
- L263 _public* property_ `UnrealTargetPlatform? Platform { get; }` — The target platform

#### class `Gauntlet.PlatformTargetSupport`  
`public static class PlatformTargetSupport`  
_public; L269-287_
- desc: Static helper class for querying platform specific target support
- L271-281 _public method_ `public static IPlatformTargetSupport Get(UnrealTargetPlatform Platform)`
- L283 _public method_ `public static string GetHostMountedPath(UnrealTargetPlatform Platform, string Path)`
- L284 _public method_ `public static bool IsHostMountingSupported(UnrealTargetPlatform Platform)`
- L286 _private field_ `private static List<IPlatformTargetSupport> PlatformSupportInstances`

#### class `Gauntlet.TargetPlatformSupportBase`  
`public abstract class TargetPlatformSupportBase : IPlatformTargetSupport`  
_public; L293-298_
- inherits: `IPlatformTargetSupport`
- desc: Default abstract implementation of IPlatformTargetSupport so that target platforms can override only parts they need
- L295 _public method_ `public virtual string GetHostMountedPath(string Path)`
- L296 _public method_ `public virtual bool IsHostMountingSupported()`
- L297 _public property_ `public virtual UnrealTargetPlatform? Platform => ...`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.TargetDeviceDesktopCommon.cs` (Gauntlet.Automation)


#### class `Gauntlet.TargetDeviceDesktopCommon`  
`public abstract class TargetDeviceDesktopCommon : ITargetDevice`  
_public; L18-308_
- inherits: `ITargetDevice`
- L21 _public property_ `public string Name { get; set; }`
- L22 _public property_ `public UnrealTargetPlatform? Platform { get; set; }`
- L23 _public property_ `public CommandUtils.ERunOptions RunOptions { get; set; }`
- L24 _public property_ `public bool IsAvailable => ...`
- L25 _public property_ `public bool IsConnected => ...`
- L26 _public property_ `public bool IsOn => ...`
- L27 _public method_ `public bool Connect()`
- L28 _public method_ `public bool Disconnect(bool bForce = false)`
- L29 _public method_ `public bool PowerOn()`
- L30 _public method_ `public bool PowerOff()`
- L31 _public method_ `public bool Reboot()`
- L32 _public method_ `public Dictionary<EIntendedBaseCopyDirectory, string> GetPlatformDirectoryMappings()`
- L33 _public method_ `public override string ToString()`
- L37 _private field_ `private bool DisposedValue = false`
- L39-53 _protected method_ `protected virtual void Dispose(bool Disposing)`
- L56-62 _public method_ `public void Dispose()`
- L65 _public property_ `public string LocalCachePath { get; set; }`
- L67 _public property_ `public string UserDir { get; set; }`
- L73 _public property_ `public string InstallRoot { get; set; }` — attrs: `[AutoParam]` — Optional directory staged builds are installed to if the requested build is not already on the same volume
- L78 _protected field_ `protected IAppInstall InstallCache` — Cached reference to the install on this device. Used to maintain a soft handle to desktop artifact directories for cleanup
- L80 _protected property_ `protected Dictionary<EIntendedBaseCopyDirectory, string> LocalDirectoryMappings { get; set; }`
- L82-96 _public ctor_ `public TargetDeviceDesktopCommon(string InName, string InCacheDir)`
- L98-101 _public method_ `public void FullClean()`
- L103-137 _public method_ `public void CleanArtifacts(UnrealAppConfig AppConfig = null)`
- L139-173 _public method_ `public virtual void InstallBuild(UnrealAppConfig AppConfig)`
- L175-196 _public method_ `public virtual IAppInstall CreateAppInstall(UnrealAppConfig AppConfig)`
- L198-237 _public method_ `public void CopyAdditionalFiles(IEnumerable<UnrealFileToCopy> FilesToCopy)`
- L239-252 _public method_ `public virtual void PopulateDirectoryMappings(string BaseDirectory)`
- L254 _public method_ `public abstract IAppInstance Run(IAppInstall Install)`
- L256 _protected method_ `protected abstract IAppInstall CreateNativeStagedInstall(UnrealAppConfig AppConfig, NativeStagedBuild Build)`
- L258 _protected method_ `protected abstract IAppInstall CreateStagedInstall(UnrealAppConfig AppConfig, StagedBuild Build)`
- L260 _protected method_ `protected abstract IAppInstall CreateEditorInstall(UnrealAppConfig AppConfig, EditorBuild Build)`
- L262-273 _protected method_ `protected string GetStagedBuildDirectory(UnrealAppConfig AppConfig, StagedBuild Build)`
- L275-283 _private method_ `private void CleanArtifactDirectory(string ArtifactDirectory)`
- L286-302 _public method_ `public virtual IAppInstall InstallApplication(UnrealAppConfig AppConfig)`
- L304 _protected method_ `protected abstract IAppInstall InstallNativeStagedBuild(UnrealAppConfig AppConfig, NativeStagedBuild Build)`
- L305 _protected method_ `protected abstract IAppInstall InstallStagedBuild(UnrealAppConfig AppConfig, StagedBuild Build)`
- L306 _protected method_ `protected abstract IAppInstall InstallEditorBuild(UnrealAppConfig AppConfig, EditorBuild Build)`

#### class `Gauntlet.DesktopCommonAppInstall`  
`public abstract class DesktopCommonAppInstall<DesktopTargetDevice> : IAppInstall where DesktopTargetDevice : TargetDeviceDesktopCommon`  
_public; L310-467_
- inherits: `IAppInstall`
- constraints: `where DesktopTargetDevice : TargetDeviceDesktopCommon`
- L312 _public property_ `public string Name { get; }`
- L314 _public property_ `public ITargetDevice Device => ...`
- L316 _public property_ `public DesktopTargetDevice DesktopDevice { get; set; }`
- L318 _public field_ `public string ArtifactPath`
- L320 _public field_ `public string ExecutablePath`
- L322 _public field_ `public string ProjectName`
- L324 _public field_ `public string WorkingDirectory`
- L326 _public field_ `public string LogFile`
- L328 _public field_ `public bool CanAlterCommandArgs`
- L330-344 _public property_ `public string CommandArguments { get; set; }`
- L346 _private field_ `private string CommandArgumentsPrivate`
- L348-351 _public method_ `public void AppendCommandline(string AdditionalCommandline)`
- L353 _public property_ `public LongProcessResult.OutputFilterCallbackType FilterLoggingDelegate { get; set; }`
- L355 _public property_ `public CommandUtils.ERunOptions RunOptions { get; set; }`
- L357-365 _public ctor_ `public DesktopCommonAppInstall(string InName, string InProjectName, DesktopTargetDevice InDevice)`
- L367-370 _public method_ `public virtual IAppInstance Run()`
- L376-379 _public method_ `public virtual void CleanDeviceArtifacts()` — Obsolete! Will be removed in a future release. Use ITargetDevice.CleanArtifacts instead
- L385-396 _public method_ `public virtual bool ForceCleanDeviceArtifacts()` — Obsolete! Will be removed in a future release. Use ITargetDevice.CleanArtifacts instead
- L398-466 _public method_ `public virtual void SetDefaultCommandLineArguments(UnrealAppConfig AppConfig, CommandUtils.ERunOptions InRunOptions, string BuildDir)`

#### class `Gauntlet.DesktopCommonAppInstance`  
`public abstract class DesktopCommonAppInstance<DesktopAppInstall, DesktopTargetDevice> : LocalAppProcess where DesktopAppInstall : DesktopCommonAppInstall<DesktopTargetDevice> where DesktopTargetDevice : TargetDeviceDesktopCommon`  
_public; L469-484_
- inherits: `LocalAppProcess`
- constraints: `where DesktopAppInstall : DesktopCommonAppInstall<DesktopTargetDevice> where DesktopTargetDevice : TargetDeviceDesktopCommon`
- L473 _public property_ `public override string ArtifactPath => ...`
- L475 _public property_ `public override ITargetDevice Device => ...`
- L477 _protected field_ `protected DesktopAppInstall Install`
- L479-483 _public ctor_ `public DesktopCommonAppInstance(DesktopAppInstall InInstall, ILongProcessResult InProcess, string InProcessLogFile = null) : base(InProcess, InInstall.CommandArguments, InProcessLogFile)`

#### class `Gauntlet.LocalAppProcess`  
`public abstract class LocalAppProcess : IAppInstance`  
_public; L486-673_
- inherits: `IAppInstance`
- L488 _public property_ `public ILongProcessResult ProcessResult { get; set; }`
- L490 _public property_ `public bool HasExited { get; }`
- L492 _public property_ `public bool WasKilled { get; set; }`
- L494-513 _public property_ `public string StdOut { get; }`
- L515-530 _public method_ `public ILogStreamReader GetLogReader()`
- L532-540 _public method_ `public ILogStreamReader GetLogBufferReader()`
- L542-572 _public method_ `public bool WriteOutputToFile(string FilePath)`
- L574 _public property_ `public int ExitCode { get; }`
- L576 _public property_ `public string CommandLine { get; set; }`
- L578-590 _public ctor_ `public LocalAppProcess(ILongProcessResult InProcess, string InCommandLine, string InProcessLogFile = null)`
- L592-600 _public method_ `public int WaitForExit()`
- L602-613 _public method_ `virtual public void Kill(bool bGenerateDump)`
- L615 _protected method_ `virtual protected void GenerateDump()`
- L620-664 _private* method_ `void LogFileReaderThread()` — Reader thread when logging to file
- L667 _public property_ `public abstract string ArtifactPath { get; }`
- L669 _public property_ `public abstract ITargetDevice Device { get; }`
- L671 _private* field_ `string ProcessLogFile`
- L672 _private* field_ `CircularLogBuffer ProcessLogOutput = null`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.TestContext.cs` (Gauntlet.Automation)


#### interface `Gauntlet.ITestContext`  
`public interface ITestContext`  
_public; L18-21_
- desc: A context that defines that environment that tests will be executed under. The base class has few properties but it is expected that concrete implementations use their context to store additional global and test-agnostic settings.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.TestNode.cs` (Gauntlet.Automation)


#### enum `Gauntlet.TestResult`  
`public enum TestResult`  
_public; L19-29_
- desc: Describe the end result of a test. Until a test is complete TestResult.Invalid should be returned
- L21 _public* enumerator_ `Invalid`
- L22 _public* enumerator_ `Passed`
- L23 _public* enumerator_ `Failed`
- L24 _public* enumerator_ `WantRetry`
- L25 _public* enumerator_ `Cancelled`
- L26 _public* enumerator_ `TimedOut`
- L27 _public* enumerator_ `InsufficientDevices`
- L28 _public* enumerator_ `OperationalException`

#### enum `Gauntlet.TestStatus`  
`public enum TestStatus`  
_public; L34-40_
- desc: Describes the current state of a test.
- L36 _public* enumerator_ `NotStarted`
- L37 _public* enumerator_ `Pending`
- L38 _public* enumerator_ `InProgress`
- L39 _public* enumerator_ `Complete`

#### enum `Gauntlet.StopReason`  
`public enum StopReason`  
_public; L45-49_
- desc: Describes why a test is stopping
- L47 _public* enumerator_ `Completed`
- L48 _public* enumerator_ `MaxDuration`

#### enum `Gauntlet.TestPriority`  
`public enum TestPriority`  
_public; L54-61_
- desc: Describes the priority of test.
- L56 _public* enumerator_ `Critical`
- L57 _public* enumerator_ `High`
- L58 _public* enumerator_ `Normal`
- L59 _public* enumerator_ `Low`
- L60 _public* enumerator_ `Idle`

#### enum `Gauntlet.EventSeverity`  
`public enum EventSeverity`  
_public; L66-72_
- desc: Describes the severity level of an event
- L68 _public* enumerator_ `Info`
- L69 _public* enumerator_ `Warning`
- L70 _public* enumerator_ `Error`
- L71 _public* enumerator_ `Fatal`

#### interface `Gauntlet.ITestEvent`  
`public interface ITestEvent`  
_public; L77-104_
- desc: Interface for test event that provides must-have information
- L82 _public* property_ `EventSeverity Severity { get; }` — Level of severity that describes this event
- L87 _public* property_ `DateTime Time { get; }` — Time at which the event was fired
- L92 _public* property_ `string Summary { get; }` — High level single-line summary of what occurred. Should never be null
- L98 _public* property_ `IEnumerable<string> Details { get; }` — Details for this event. E.g this could be a list of error messages or warnings for a failed test. May be empty, should never be null
- L103 _public* property_ `IEnumerable<string> Callstack { get; }` — Callstack for this event if that information is available. May be empty, should never be null

#### interface `Gauntlet.ITestNode`  
`public interface ITestNode`  
_public; L112-241_
- desc: The interface that all Gauntlet rests are required to implement. How these are implemented and whether responsibilities are handed off to other systems (e.g. Launch) is left to the implementor. It's expected that tests for major systems (e.g. Unreal) will likely implement their own base node.
- L117 _public* property_ `string Name { get; }` — Name of the test - used for logging / reporting
- L122 _public* property_ `float MaxDuration { get; }` — Maximum duration that the test is expected to run for. Tests longer than this will be halted.
- L127 _public* property_ `bool LogWarningsAndErrorsAfterSummary { get; }` — Return true if the warnings and errors needs to log after summary
- L132 _public* property_ `EMaxDurationReachedResult MaxDurationReachedResult { get; }` — What the test result should be treated as if we reach max duration.
- L137 _public* property_ `TestPriority Priority { get; }` — Priority of this test in relation to any others that are running
- L144 _public* method_ `void SetContext(ITestContext InContext)` — Sets the context that this test will run under. TODO - make this more of a contract that happens before CheckRequirements / LaunchTest
- L151 _public* method_ `bool IsReadyToStart()` — Checks if the test is ready to be started. If the test is not ready to run (e.g. resources not available) then it should return false. If it determines that it will never be ready it should throw an exception.
- L160 _public* method_ `bool StartTest(int Pass, int NumPasses)` — Begin executing the provided test. At this point .Status should return InProgress and the test will eventually receive OnComplete and ShutdownTest calls
- L165 _public* method_ `void TickTest()` — Called regularly to allow the test to check and report status
- L172 _public* method_ `void SetCancellationReason(string Reason)` — Sets Cancellation Reason.
- L179 _public* method_ `void StopTest(StopReason InReason)` — Called to request that the test stop, either because it's reported that its complete or due to external factors. Tests should consider whether they passed or succeeded (even a terminated test may have gotten all the data it needs) and set their result appropriately.
- L186 _public* method_ `bool RestartTest()` — Allows the node to restart with the same assigned devices. Only called if the expresses a .Result of TestResult.WantRetry while running.
- L191 _public* method_ `TestStatus GetTestStatus()` — Return an enum, that describes the state of the test
- L197 _public* method_ `TestResult GetTestResult()` — The result of the test. Only called once GetTestStatus() returns complete, but may be called multiple times.
- L202 _public* method_ `void SetTestResult(TestResult testResult)` — Set the Test Result value
- L207 _public* method_ `void AddTestEvent(UnrealTestEvent InEvent)` — Add a new Test Event to be rolled up and summarized at the end of this test.
- L213 _public* method_ `string GetTestSummary()` — Summary of the test. Only called once GetTestStatus() returns complete, but may be called multiple times.
- L218 _public* method_ `IEnumerable<string> GetWarnings()` — Return a list of all warnings that should be reported. May be different than Summary contents
- L223 _public* method_ `IEnumerable<string> GetErrors()` — Return a list of all errors that should be reported. May be different than Summary contents
- L228 _public* method_ `string GetRunLocalCommand(string LaunchingBuildCommand)` — returns a string that will be how to run this test locally with RunUAT.bat
- L235 _public* method_ `void CleanupTest()` — Called to request any that any necessary cleanup be performed. After CleanupTest is called no further calls will be made to this test and thus all resources should be released.
- L240 _public* method_ `void DisplayCommandlineHelp()` — Output all defined commandline information for this test to the gauntlet window and exit test early.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.TestReport.cs` (Gauntlet.Automation)


#### enum `Gauntlet.EventType`  
`public enum EventType`  
_public; L16-22_
- attrs: `[JsonConverter(typeof(JsonTryParseEnumConverter))]`
- desc: Event Type
- L18 _public* enumerator_ `Unknown`
- L19 _public* enumerator_ `Info`
- L20 _public* enumerator_ `Warning`
- L21 _public* enumerator_ `Error`

#### enum `Gauntlet.TestStateType`  
`public enum TestStateType`  
_public; L29-62_
- attrs: `[JsonConverter(typeof(JsonTryParseEnumConverter))]`
- desc: Test State type
- L31 _public* enumerator_ `Unknown`
- L36 _public* enumerator_ `NotRun` — The test case has not (yet) been executed
- L41 _public* enumerator_ `InProcess` — The test case is currently in progress
- L46 _public* enumerator_ `Fail` — The behavior that this test case was trying to exercise did not work as expected
- L51 _public* enumerator_ `Success` — The behavior that this test case was trying to exercise worked as expected
- L56 _public* enumerator_ `Skipped` — The test case was not executed, and will not be executed in this test run
- L61 _public* enumerator_ `Interrupted` — The test case was stopped for some reason other than failure of the behavior being tested

#### interface `Gauntlet.ITestReport`  
`public interface ITestReport`  
_public; L67-117_
- desc: Interface for test report
- L72 _public* property_ `string Type { get; }` — Return report type
- L80 _public* method_ `void SetProperty(string Property, object Value)` — Set a property of the test report
- L88 _public* method_ `void SetMetadata(string Key, string Value)` — Set a metadata key/value to the test report
- L97 _public* method_ `void AddEvent(EventType Type, string Message, params object[] Args)` — Add event to the test report
- L105 _public* method_ `bool AttachArtifact(string ArtifactPath, string Name = null)` — Attach an Artifact to the ITestReport
- L111 _public* method_ `Dictionary<string, object> GetReportDependencies()` — Return a dictionary of key/object intended to be a data collection of dependencies that comes with the report but not part of the report. ie: an artifact manifest
- L116 _public* method_ `void FinalizeReport()` — Call to finalize report

#### class `Gauntlet.TelemetryData`  
`public class TelemetryData`  
_public; L122-139_
- desc: Hold telemetry data
- L124 _public property_ `public string TestName { get; set; }`
- L125 _public property_ `public string DataPoint { get; set; }`
- L126 _public property_ `public double Measurement { get; set; }`
- L127 _public property_ `public string Context { get; set; }`
- L128 _public property_ `public string Unit { get; set; }`
- L129 _public property_ `public double Baseline { get; set; }`
- L130-138 _public ctor_ `public TelemetryData(string InTestName, string InDataPoint, double InMeasurement, string InContext = "", string InUnit = "", double InBaseline = 0)`

#### interface `Gauntlet.ITelemetryReport`  
`public interface ITelemetryReport`  
_public; L144-163_
- desc: Interface for telemetry report
- L156 _public* method_ `void AddTelemetry(string TestName, string DataPoint, double Measurement, string Context = "", string Unit = "", double Baseline = 0)` — Attach Telemetry data to the ITestReport
- L162 _public* method_ `IEnumerable<TelemetryData> GetAllTelemetryData()` — Return the telemetry data accumulated

#### class `Gauntlet.BaseTestReport`  
`public abstract class BaseTestReport : ITestReport, ITelemetryReport`  
_public; L168-306_
- inherits: `ITestReport, ITelemetryReport`
- desc: Test Report Base class
- L170-173 _public ctor_ `public BaseTestReport()`
- L178 _public property_ `public abstract int Version { get; }` — Horde report version
- L183 _public property_ `public Dictionary<string, string> Metadata { get; set; }` — Metadata blackboard
- L188 _public property_ `public virtual string Type { get; }` — Return report type
- L193 _protected field_ `protected List<TelemetryData> TelemetryDataList` — Hold the list of telemetry data accumulated
- L201-205 _public method_ `public virtual void SetProperty(string Property, object Value)` — Set a property of the test report
- L213-216 _public method_ `public virtual void SetMetadata(string Key, string Value)` — Set a metadata key/value to the test report
- L225 _public method_ `public abstract void AddEvent(EventType Type, string Message, params object[] Args)` — Add event to the test report
- L232-235 _public method_ `public void AddError(string Message, params object[] Args)` — Add Error event with optional formatting inputs to report
- L242-245 _public method_ `public void AddWarning(string Message, params object[] Args)` — Add Warning event with optional formatting inputs to report
- L252-255 _public method_ `public void AddInfo(string Message, params object[] Args)` — Add Info event with optional formatting inputs to report
- L263 _public method_ `public abstract bool AttachArtifact(string ArtifactPath, string Name = null)` — Attach an Artifact to the ITestReport
- L275-283 _public method_ `public virtual void AddTelemetry(string TestName, string DataPoint, double Measurement, string Context = "", string Unit = "", double Baseline = 0)` — Attach Telemetry data to the ITestReport
- L289-292 _public method_ `public virtual IEnumerable<TelemetryData> GetAllTelemetryData()` — Return all the telemetry data stored
- L298-301 _public method_ `public virtual Dictionary<string, object> GetReportDependencies()` — Return a dictionary of key/object intended to be a data collection of dependencies that comes with the report but not part of the report. ie: an artifact manifest
- L304-305 _public method_ `public virtual void FinalizeReport()` — (inheritdoc)

#### class `Gauntlet.JsonTryParseEnumConverter`  
`class JsonTryParseEnumConverter : JsonConverterFactory`  
_internal*; L308-361_
- inherits: `JsonConverterFactory`
- L310-313 _public method_ `public override bool CanConvert(Type TypeToConvert)`
- L315-320 _public method_ `public override JsonConverter CreateConverter(Type EnumType, JsonSerializerOptions Options)`

#### class `Gauntlet.JsonTryParseEnumConverter.DefaultToFirstEnumConverterInner`  
`private class DefaultToFirstEnumConverterInner<TEnum> : JsonConverter<TEnum> where TEnum : struct, Enum`  
_private; L322-360_
- inherits: `JsonConverter<TEnum>`
- constraints: `where TEnum : struct, Enum`
- L325-353 _public method_ `public override TEnum Read(ref Utf8JsonReader Reader, Type TypeToConvert, JsonSerializerOptions Options)`
- L355-359 _public method_ `public override void Write(Utf8JsonWriter Writer, TEnum EnumValue, JsonSerializerOptions Options)`

#### interface `Gauntlet.Report.ITestAuditMetadata`  
`public interface ITestAuditMetadata`  
_public; L369-406_
- desc: Interface to retrieve test audit metadata
- L372 _public property_ `public string TestKey { get; }`
- L375 _public property_ `public string TestName { get; }`
- L378 _public property_ `public string TestNodeClass { get; }`
- L381 _public property_ `public Version TestVersion { get; }`
- L384 _public property_ `public float TestTimeoutMinutes { get; }`
- L387 _public property_ `public string? TestCommandLine { get; }`
- L390 _public property_ `public TestHarness? TestHarness { get; }`
- L393 _public property_ `public TestProfile? TestProfile { get; }`
- L396 _public property_ `public TestTeam? TestTeam { get; }`
- L399 _public property_ `public string? TestIntent { get; }`
- L402 _public property_ `public TestTag[]? TestTags { get; }`
- L405 _public property_ `public Dictionary<string, object>? TestParams { get; }`

#### class `Gauntlet.Report.ReportProperty`  
`public partial class ReportProperty`  
_public; L411-423_
- desc: Extend able Property value for report
- L413 _private field_ `private string Key`
- L414-417 _public ctor_ `public ReportProperty(string InKey)`
- L419-422 _public method_ `public override string ToString()`

#### class `Gauntlet.Report.TestProfile`  
`public partial class TestProfile : ReportProperty`  
_public; L428-431_
- inherits: `ReportProperty`
- desc: Test profile (unit, functional, performance, etc)
- L430 _public ctor_ `public TestProfile(string Key) : base(Key)`

#### class `Gauntlet.Report.TestHarness`  
`public partial class TestHarness : ReportProperty`  
_public; L436-439_
- inherits: `ReportProperty`
- desc: Test harness
- L438 _public ctor_ `public TestHarness(string Key) : base(Key)`

#### class `Gauntlet.Report.TestTeam`  
`public partial class TestTeam : ReportProperty`  
_public; L444-447_
- inherits: `ReportProperty`
- desc: Test team
- L446 _public ctor_ `public TestTeam(string Key) : base(Key)`

#### class `Gauntlet.Report.TestTag`  
`public partial class TestTag : ReportProperty`  
_public; L452-455_
- inherits: `ReportProperty`
- desc: Test tag
- L454 _public ctor_ `public TestTag(string Key) : base(Key)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Base/Gauntlet.TestTracking.cs` (Gauntlet.Automation)


#### interface `Gauntlet.TestTracking.IPhaseDataHandler`  
`public interface IPhaseDataHandler`  
_public; L26-33_
- desc: Handler for associated phase data
- L32 _public method_ `public void OnAddToReport(TestPhase ReportedPhase)` — Called when test phase is added to report

#### class `Gauntlet.TestTracking.Phase`  
`public class Phase`  
_public; L38-176_
- desc: Object that represent a test phase
- L40 _public field_ `public string Name`
- L41 _public field_ `public double ElapseTimeInSeconds`
- L42 _public field_ `public DateTime? StartedAt`
- L43 _public field_ `public TestPhaseOutcome Outcome`
- L44 _private field_ `private ConcurrentQueue<LogEvent> Events`
- L52 _public field_ `public object? Data` — Opaque object that can be associated with the phase. The object class can implement its own handler by implementing IPhaseDataHandler interface. OnAddToReport method will be called when the phase is attached to the report allowing the opaque data to make modifications to the reported data.
- L54-62 _public ctor_ `public Phase(string InName, DateTime? InDateTime = null, object? InData = null)`
- L69-77 _public method_ `public void Start(object? InData = null)` — Mark the phase as started
- L84-98 _public method_ `public double End(TestPhaseOutcome? InOutcome = null)` — Mark the phase as finished
- L106-121 _public method_ `public void AddEvent(Logging.LogLevel Level, string Message, params object[] Args)` — Add an event to the phase tracker
- L128-136 _public method_ `public T? GetData<T>()` — Get the associated data
- L143-175 _public method_ `public TestPhase AddToReport(AutomatedTestSessionData Report)` — Add the information tracked by the phase to the test report

#### class `Gauntlet.TestTracking.PhaseQueue`  
`public class PhaseQueue : IEnumerable<Phase>`  
_public; L181-321_
- inherits: `IEnumerable<Phase>`
- desc: Object to track queued phases and enumerate through
- L183-189 _public ctor_ `public PhaseQueue()`
- L191 _private field_ `private ConcurrentDictionary<string, Phase> _manifest`
- L191 _private field_ `private ConcurrentDictionary< _manifest`
- L192 _private field_ `private ConcurrentQueue<Phase> _queuedPhases`
- L193 _private field_ `private Phase? _last`
- L194 _private field_ `private Phase? _current`
- L195 _private field_ `private bool _orderByCompletion = false`
- L200 _public property_ `public Phase? Last => ...` — The last added phase to the queue
- L206 _public property_ `public Phase? Current => ...` — The current running phase. Use Start to identify the running phase
- L215-237 _public method_ `public Phase Start(string Name, object? Data = null)` — Start a phase, if not queued it will be added to the queue
- L246-258 _public method_ `public Phase Add(string Name, object? Data = null)` — Add a new phase. Raise an exception if it already exists.
- L265-271 _public method_ `public Phase? Get(string Name)` — Get the corresponding phase
- L278-285 _public method_ `public bool SetCurrent(string Name)` — Set current phase
- L287-290 _private* method_ `IEnumerator IEnumerable.GetEnumerator()`
- L293-301 _public method_ `public IEnumerator<Phase> GetEnumerator()` — (inheritdoc)
- L306-309 _public method_ `public void SetOrderByCompletion(bool Value)` — Whether or not to order the phases by completion date when iterating the object
- L314-320 _public method_ `public void Clear()` — Clear the queue

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.ConfigurableDevice.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IConfigurableDevice`  
`public interface IConfigurableDevice`  
_public; L15-29_
- desc: ITargetDevice extension for platforms that support configurable settings
- L21 _public* method_ `PlatformConfigurationBase GetCurrentConfigurationSnapshot()` — Returns a configuration profile with the current device settings
- L28 _public* method_ `bool ApplyConfiguration(PlatformConfigurationBase Configuration)` — Applies a configuration profile to the device. If required it will reboot the device

#### interface `Gauntlet.IPlatformConfigurationReader`  
`public interface IPlatformConfigurationReader`  
_public; L34-50_
- desc: Base interface for a platform specific configuration reader
- L36 _public* method_ `bool SupportsPlatform(UnrealTargetPlatform? Platform)`
- L42 _public* method_ `string ConfigFileExtension()` — Returns the supported platform config file extension
- L49 _public* method_ `PlatformConfigurationBase ReadConfiguration(FileReference Location)` — Reads the configuration from the passed in file location

#### class `Gauntlet.PlatformConfigurationBase`  
`public abstract class PlatformConfigurationBase`  
_public; L56-73_
- desc: Base class for a platform configuration profile. This class needs to be implemented for each configurable platform
- L62 _public property_ `public string ProfileName { get; set; }` — Name of the config profile. This name doesn't need to be unique across namespaces.
- L67 _public property_ `public string Namespace { get; set; }` — Namespace of the profile. Profiles have to have a unique name inside a namespace.
- L72 _public property_ `public UnrealTargetPlatform Platform { get; set; }` — Platform this configuration profile is for

#### class `Gauntlet.DeviceConfigurationCache`  
`public class DeviceConfigurationCache`  
_public; L78-261_
- desc: A singleton class that encapsulates a cache of device config profiles
- L80 _public property_ `public static DeviceConfigurationCache Instance { get; set; }`
- L82 _private field_ `private Object LockObject = new Object()`
- L83 _private field_ `private Dictionary<ConfigurationCacheKey, PlatformConfigurationBase> ConfigurationCache = ...`
- L83 _private field_ `private Dictionary< ConfigurationCache = new()`
- L85-88 _protected ctor_ `protected DeviceConfigurationCache()`
- L136-178 _public method_ `public bool DiscoverConfigurationProfiles(UnrealTargetPlatform? Platform, string Namespace, string SettingDir)` — Scans the SettingDir for configuration profiles
- L180-197 _public method_ `public void CacheConfigurationSnapshot(PlatformConfigurationBase Configuration, bool Overwrite = false)`
- L199-202 _public method_ `public PlatformConfigurationBase GetConfigurationSnapshot(UnrealTargetPlatform? Platform, string DeviceName)`
- L204-211 _public method_ `public void ClearSnapshot(PlatformConfigurationBase Snapshot)`
- L213-242 _public method_ `public void RevertDeviceConfiguration(ITargetDevice Device)`
- L244-260 _public method_ `public PlatformConfigurationBase GetConfiguration(UnrealTargetPlatform? Platform, string Namespace, string ProfileName)`

#### class `Gauntlet.DeviceConfigurationCache.ConfigurationCacheKey`  
`class ConfigurationCacheKey`  
_private*; L93-127_
- desc: Key by which a configuration profile is identified in the cache.
- L95 _public field_ `public UnrealTargetPlatform Platform`
- L96 _public field_ `public string Namespace`
- L97 _public field_ `public string ProfileName`
- L99-104 _public ctor_ `public ConfigurationCacheKey(UnrealTargetPlatform Platform, string ProjectName, string ProfileName)`
- L106-111 _public ctor_ `public ConfigurationCacheKey(PlatformConfigurationBase Configuration)`
- L113-121 _public method_ `public override bool Equals(object Other)`
- L123-126 _public method_ `public override int GetHashCode()`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.DeviceFirmwareValidator.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IPlatformFirmwareHandler`  
`public interface IPlatformFirmwareHandler`  
_public; L10-21_
- L12 _public* method_ `bool CanSupportPlatform(UnrealTargetPlatform Platform)`
- L14 _public* method_ `bool CanSupportProject(string ProjectName)`
- L16 _public* method_ `bool GetDesiredVersion(UnrealTargetPlatform Platform, string ProjectName, out string Version)`
- L18 _public* method_ `bool GetCurrentVersion(ITargetDevice Device, out string Version)`
- L20 _public* method_ `bool UpdateDeviceFirmware(ITargetDevice Device, string Version)`

#### class `Gauntlet.FirmwareValidator`  
`public class FirmwareValidator : IDeviceValidator`  
_public; L23-218_
- inherits: `IDeviceValidator`
- L26 _public property_ `public string FirmwareVersion { get; set; }` — attrs: `[AutoParam("")]`
- L29 _public property_ `public string ProjectName { get; set; }` — attrs: `[AutoParamWithNames(Default: "", "Project", "ProjectName")]`
- L32 _public property_ `public bool bEnabled { get; set; }` — attrs: `[AutoParamWithNames(false, "UpdateFirmware", "TryUpdateFirmware")]`
- L34-40 _public ctor_ `public FirmwareValidator()`
- L42-56 _public method_ `public bool TryValidateDevice(ITargetDevice Device, ref string Message)`
- L65-137 _public method_ `public bool TryUpdateFirmware(ITargetDevice Device, string DesiredVersion, ref string Message)` — Attempts to update the provided Device's firmware to the requested version
- L146-201 _public method_ `public bool TryUpdateFirmwareForProject(ITargetDevice Device, string ProjectName, ref string Message)` — Attempts to update the provided Device's firmware version to the version requested by the specified project
- L204-209 _private method_ `private IPlatformFirmwareHandler GetRequiredPlatformFirmwareHandler(UnrealTargetPlatform Platform)`
- L212-217 _private method_ `private IPlatformFirmwareHandler GetRequiredPlatformFirmwareHandler(UnrealTargetPlatform Platform, string ProjectName)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.DeviceLoginValidator.cs` (Gauntlet.Automation)


#### class `Gauntlet.DeviceLoginValidator`  
`public class DeviceLoginValidator : IDeviceValidator`  
_public; L11-49_
- inherits: `IDeviceValidator`
- desc: DeviceLoginValidator works for any ITargetDevice that implements IOnlineServiceLogin (typically consoles) This validator ensures the device have an account logged into that platforms online service.
- L14 _public property_ `public bool bEnabled { get; set; }` — attrs: `[AutoParamWithNames(false, "VerifyLogin")]`
- L16-19 _public ctor_ `public DeviceLoginValidator()`
- L21-48 _public method_ `public bool TryValidateDevice(ITargetDevice Device, ref string Message)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.DevicePool.cs` (Gauntlet.Automation)


#### enum `Gauntlet.EPerfSpec`  
`public enum EPerfSpec`  
_public; L24-30_
- desc: Device performance specification
- L26 _public* enumerator_ `Unspecified`
- L27 _public* enumerator_ `Minimum`
- L28 _public* enumerator_ `Recommended`
- L29 _public* enumerator_ `High`

#### class `Gauntlet.DeviceDefinition`  
`public class DeviceDefinition`  
_public; L35-64_
- desc: Information that defines a device
- L37 _public property_ `public string Name { get; set; }`
- L39 _public property_ `public string Address { get; set; }`
- L41 _public property_ `public string DeviceData { get; set; }`
- L45 _public property_ `public UnrealTargetPlatform Type { get; set; }` — attrs: `[JsonConverter(typeof(UnrealTargetPlatformConvertor))]`
- L48 _public property_ `public UnrealTargetPlatform? Platform { get; set; }` — attrs: `[JsonConverter(typeof(UnrealTargetPlatformConvertor))]`
- L50 _public property_ `public EPerfSpec PerfSpec { get; set; }`
- L52 _public property_ `public string Model { get; set; }`
- L54 _public property_ `public string Available { get; set; }`
- L56 _public property_ `public bool RemoveOnShutdown { get; set; }`
- L58 _public property_ `public List<string> Tags { get; set; }`
- L60-63 _public method_ `public override string ToString()`

#### class `Gauntlet.UnrealDeviceTargetConstraint`  
`public class UnrealDeviceTargetConstraint : IEquatable<UnrealDeviceTargetConstraint>`  
_public; L69-231_
- inherits: `IEquatable<UnrealDeviceTargetConstraint>`
- desc: Device target constraint, can be expanded for specifying installed RAM, OS version, etc
- L71 _public field_ `public readonly UnrealTargetPlatform? Platform`
- L72 _public field_ `public readonly EPerfSpec PerfSpec`
- L73 _public field_ `public readonly string Model`
- L74 _public field_ `public readonly string DeviceName`
- L75 _public field_ `public readonly Tags Tags`
- L77-84 _public ctor_ `public UnrealDeviceTargetConstraint(UnrealTargetPlatform? Platform, EPerfSpec PerfSpec = EPerfSpec.Unspecified, string Model = null, string DeviceName = null, Tags Tags = null)`
- L89-95 _public method_ `public bool IsIdentity()` — Tests whether the constraint is identity, ie. unconstrained
- L101-104 _public method_ `public bool Check(ITargetDevice Device)` — Check whether device satisfies the constraint
- L106-136 _public method_ `public bool Check(DeviceDefinition DeviceDef)`
- L138-159 _public method_ `public bool Equals(UnrealDeviceTargetConstraint Other)`
- L161-179 _public method_ `public override bool Equals(object Obj)`
- L181-189 _public operator_ `public static bool operator ==(UnrealDeviceTargetConstraint C1, UnrealDeviceTargetConstraint C2)`
- L191-194 _public operator_ `public static bool operator !=(UnrealDeviceTargetConstraint C1, UnrealDeviceTargetConstraint C2)`
- L196-216 _public method_ `public override string ToString()`
- L222-225 _public method_ `public string FormatWithIdentifier()` — Format to string the device constraint including its identify
- L227-230 _public method_ `public override int GetHashCode()`

#### struct `Gauntlet.ProblemDevice`  
`public struct ProblemDevice`  
_public; L236-246_
- desc: Device marked as having a problem
- L238-242 _public ctor_ `public ProblemDevice(string Name, UnrealTargetPlatform Platform)`
- L244 _public field_ `public string Name`
- L245 _public field_ `public UnrealTargetPlatform Platform`

#### class `Gauntlet.DevicePool`  
`public class DevicePool : IDisposable`  
_public; L257-1404_
- inherits: `IDisposable`
- desc: Singleton class that's responsible for providing a list of devices and reserving them. Code should call EnumerateDevices to build a list of desired devices, which must then be reserved by calling ReserveDevices. Once done ReleaseDevices should be called. These reservations exist at the process level and we rely on the device implementation to provide arbitrage between difference processes and machines
- L262-282 _public property_ `public static DevicePool Instance { get; set; }` — Access to our singleton
- L288 _public field_ `public static bool SkipInstall` — Whether or not installations should be skipped This is primarily used within the context of UnrealSession
- L294 _public field_ `public static bool FullClean` — Whether or not devices should be fully cleaned This is primarily used within the context of UnrealSession
- L302 _public field_ `public static bool DeviceReservationBlock` — Whether or a device reservation block is active This is primarily used within the context of UnrealSession when a step is executed by Horde that contains a DeviceReserve=Begin annotation or is a step that proceeds one
- L308 _public field_ `public static bool DeviceReservationBlockFinalStep` — Whether or not a device reservation block is in it's final active step This is used to prevent cleaning of the tempdir where builds may be stored
- L314 _public field_ `public static bool? IsInstallStep` — Whether or not this particular step is an installations tep in a device reservation block This is primarily used within the context of UnrealSession when a job is executed by Horde that contains a DeviceReserve=Begin/Install annotation
- L321 _public property_ `public int LocalDeviceIndex { get; set; }` — attrs: `[AutoParam(0)]` — Optional index to name local devices Occasionally useful for retaining device caches from previous tests
- L326 _private field_ `private static DevicePool _Instance` — Active pool instance
- L331 _private field_ `private object LockObject = new object()` — Object used for locking access to internal data
- L336 _private field_ `private List<ITargetDevice> AvailableDevices = new List<ITargetDevice>()` — List of all provisioned devices that are can be claimed
- L341 _private field_ `private List<ITargetDevice> ClaimedDevices = new List<ITargetDevice>()` — List of all provisioned devices that have been claimed
- L346 _private property_ `private List<ITargetDevice> LocalDevices => ...` — List of all provisioned devices that were not provided by a reservation service
- L354 _private field_ `private List<IDeviceReservationService> ReservationServices = new List<IDeviceReservationService>()` — List of all enabled reservation services
- L359 _private field_ `private HashSet<UnrealTargetPlatform?> UsedPlatforms = new HashSet<UnrealTargetPlatform?>()` — List of platforms we've had devices for
- L364 _private field_ `private List<DeviceDefinition> UnprovisionedDevices = new List<DeviceDefinition>()` — List of device definitions that can be provisioned on demand
- L369 _private field_ `private List<DeviceDefinition> FailedProvisions = new List<DeviceDefinition>()` — List of definitions that failed to provision
- L374 _private field_ `private Dictionary<ITargetDevice, UnrealDeviceTargetConstraint> Constraints = ...` — Device constraints for performance profiles, etc
- L374 _private field_ `private Dictionary< Constraints = new Dictionary<ITargetDevice, UnrealDeviceTargetConstraint>()` — Device constraints for performance profiles, etc
- L379 _private field_ `private string LocalTempDir` — Directory automation artifacts are saved to
- L384 _private field_ `private string UniformCache` — Uniform cache, useful for some instances of multi-role editor tests. Only used if -UniformCache is enabled
- L389-402 _protected ctor_ `protected DevicePool()` — Protected constructor - code should use DevicePool.Instance
- L405 _private* field_ `bool bDisposed = false`
- L406-409 _private* dtor_ `~DevicePool()`
- L414-418 _public method_ `public static void Shutdown()` — Shutdown the pool and release all devices.
- L420-424 _public method_ `public void Dispose()`
- L430-465 _protected method_ `protected virtual void Dispose(bool disposing)` — Perform actual dispose behavior
- L472-479 _public method_ `public int GetAvailableDeviceCount(UnrealDeviceTargetConstraint Constraint, Func<ITargetDevice, bool> Validate = null)` — Returns the number of available devices of the provided type. This includes unprovisioned devices but not reserved ones. Note: unprovisioned devices are currently only returned when device is not constrained
- L485-492 _public method_ `public int GetTotalDeviceCount(UnrealDeviceTargetConstraint Constraint, Func<ITargetDevice, bool> Validate = null)` — Returns the number of available devices of the provided type. This includes unprovisioned devices but not reserved ones Note: unprovisioned devices are currently only returned when device is not constrained
- L494-502 _public method_ `public UnrealDeviceTargetConstraint GetConstraint(ITargetDevice Device)`
- L504-508 _public method_ `public void SetLocalOptions(string InLocalTemp, bool InUniqueTemps = false, string InDeviceURL = "")`
- L510-513 _public method_ `public void AddLocalDevices(int MaxCount)`
- L515-526 _public method_ `public void AddLocalDevices(int MaxCount, UnrealTargetPlatform LocalPlatform)`
- L528-550 _public method_ `public void AddVirtualDevices(int MaxCount)`
- L558-714 _public method_ `public void AddDevices(UnrealTargetPlatform DefaultPlatform, string InputReference, bool ObeyConstraints = true)` — Created a list of device definitions from the passed in reference. Needs work....
- L720-726 _public method_ `public void RegisterDevices(IEnumerable<ITargetDevice> InDevices)` — Adds the list of devices to our internal availability list
- L733-751 _public method_ `public void RegisterDevice(ITargetDevice Device, UnrealDeviceTargetConstraint Constraint = null)` — Registers the provided device for availability
- L756-759 _public method_ `public void EnumerateDevices(UnrealTargetPlatform Platform, Func<ITargetDevice, bool> Predicate)` — Run the provided function across all our devices until it returns false. Devices are provisioned on demand (e.g turned from info into an ITargetDevice)
- L761-839 _public method_ `public void EnumerateDevices(UnrealDeviceTargetConstraint Constraint, Func<ITargetDevice, bool> Predicate)`
- L847-864 _public method_ `public bool ClaimDevices(IEnumerable<ITargetDevice> DeviceList)` — Claim all devices in the provided list. Once reserved a device will not be seen by any code that calls EnumerateDevices
- L866-917 _public method_ `public bool ReserveDevicesFromService(Dictionary<UnrealDeviceTargetConstraint, int> DeviceTypes, IDeviceReservationService.Options Options = null)`
- L922-932 _public method_ `public void ReportDeviceError(ITargetDevice Device, string ErrorMessage)` — Report target device issue to service with given error message
- L939-973 _public method_ `public void ReleaseDevices(IEnumerable<ITargetDevice> DeviceList, IDeviceReservationService.Options ServiceOptions = null)` — Release all devices in the provided list from our reserved list
- L978-1061 _public method_ `public bool CheckAvailableDevices(Dictionary<UnrealDeviceTargetConstraint, int> RequiredDevices, IReadOnlyCollection<ProblemDevice> ProblemDevices = null, bool UseServiceDevices = true)` — Checks whether device pool can accommodate requirements, optionally add service devices to meet demand
- L1068-1158 _public method_ `public ITargetDevice CreateAndRegisterDeviceFromDefinition(DeviceDefinition Def, UnrealDeviceTargetConstraint Constraint, IDeviceReservationService Service = null, IDeviceFactory Factory = null)` — Created and registered a device from the provided definition
- L1160-1174 _private method_ `private void InitializeReservationServices()`
- L1176-1179 _private method_ `private bool IsServiceEnabled<T>() where T : IDeviceReservationService`
- L1187-1239 _protected method_ `protected bool TryValidateDeviceRequirements(ITargetDevice Device, ref string Message)` — Verifies if the provided TargetDevice meets requirements such as firmware, login status, settings, etc.
- L1244-1256 _private method_ `private void ReleaseReservations()` — Explicitly release all device reservations
- L1258-1272 _private method_ `private void CleanupDevices(IEnumerable<UnrealTargetPlatform?> Platforms)`
- L1274-1288 _public method_ `public bool TryGetDevicesReservationService(ITargetDevice Device, out IDeviceReservationService OutService)`
- L1293-1375 _private method_ `private string GetCleanCachePath(DeviceDefinition InDeviceDefiniton)` — Construct a path to hold cache files and make sure it's properly cleaned
- L1380-1384 _public property_ `public string DeviceURL { get; set; }` — attrs: `[Obsolete("Will be removed in a future release")]`
- L1389 _private field_ `private string Legacy_DeviceURL` — Device reservation service URL
- L1392-1395 _public method_ `public void ReserveDevices(IEnumerable<ITargetDevice> Devices)` — attrs: `[Obsolete("Misnomer, use ClaimDevices instead. Will be removed in a future release")]`
- L1398-1401 _public method_ `public bool ReserveDevicesFromService(string DeviceURL, Dictionary<UnrealDeviceTargetConstraint, int> DeviceTypes)` — attrs: `[Obsolete("Will be removed in a future release. Use the single parameter overload instead.")]`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.DeviceProfileValidator.cs` (Gauntlet.Automation)


#### class `Gauntlet.DeviceProfileValidator`  
`public class DeviceProfileValidator : IDeviceValidator`  
_public; L8-94_
- inherits: `IDeviceValidator`
- L10 _public property_ `public bool bEnabled { get; }`
- L13 _public property_ `public string DeviceProfile { get; set; }` — attrs: `[AutoParam("")]`
- L15 _private const_ `private const string DefaultNamespace = "Engine"`
- L17-21 _public ctor_ `public DeviceProfileValidator()`
- L23-93 _public method_ `public bool TryValidateDevice(ITargetDevice Device, ref string Message)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.DeviceReservationService.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IDeviceReservationService`  
`public interface IDeviceReservationService : IDisposable`  
_public; L22-35_
- inherits: `IDisposable`
- desc: An IDeviceReservationService provides a mechanism to obtain devices from an external service
- L27 _public* property_ `static virtual bool Enabled { get; }`
- L28 _public* property_ `List<ITargetDevice> ReservedDevices { get; }`
- L29 _public* method_ `bool CanSupportDeviceConstraint(UnrealDeviceTargetConstraint Constraint)`
- L30 _public* method_ `bool ReserveDevicesFromService(IEnumerable<UnrealDeviceTargetConstraint> RequestedDevices)`
- L31 _public* method_ `bool ReserveDevicesFromService(IEnumerable<UnrealDeviceTargetConstraint> RequestedDevices, Options? Options)`
- L32 _public* method_ `void ReleaseDevices(IEnumerable<ITargetDevice> Devices)`
- L33 _public* method_ `void ReleaseDevices(IEnumerable<ITargetDevice> Devices, Options? Options)`
- L34 _public* method_ `void ReportDeviceError(string DeviceName, string ErrorMessage)`

#### class `Gauntlet.IDeviceReservationService.Options`  
`public class Options`  
_public; L24-25_

#### class `Gauntlet.HordeDeviceReservationService`  
`public class HordeDeviceReservationService : IDeviceReservationService`  
_public; L40-551_
- inherits: `IDeviceReservationService`
- desc: Horde Service. Enabled by providing the base url via -DeviceURL= and pool via -DevicePool=
- L54 _public property_ `public static bool Enabled => ...` — Whether or not this reservation service is enabled
- L62 _public property_ `public List<ITargetDevice> ReservedDevices { get; set; }` — List of devices reserved from this service
- L68 _public property_ `public string DeviceURL { get; set; }` — attrs: `[AutoParam("")]` — The base URL of the horde service to request devices from
- L74 _public property_ `public string DevicePoolID { get; set; }` — attrs: `[AutoParamWithNames(Default: "", "DevicePool")]` — Name of the horde device pool to request devices from
- L81 _public field_ `public bool UseAgentTag` — attrs: `[AutoParam(false)]` — If true, the horde agent will have it's name appended as a required tag This is useful in instances where you want an agent to use a limited number of devices in a larger pool
- L86 _private field_ `private static HordeHttpClient? HordeClient = null` — HTTP client used to collect horde information
- L91 _private field_ `private static JobId HordeJobId = default` — ID of the actively running horde job
- L96 _private field_ `private static JobStepId HordeStepId = default` — ID of the actively running horde step
- L101 _private field_ `private Uri ReservationServerUri` — Endpoint for reservations
- L106 _private field_ `private Dictionary<ITargetDevice, DeviceReservationAutoRenew> ServiceReservations = ...` — Device to reservation lookup
- L106 _private field_ `private Dictionary< ServiceReservations = new Dictionary<ITargetDevice, DeviceReservationAutoRenew>()` — Device to reservation lookup
- L111 _private field_ `private Dictionary<ITargetDevice, DeviceDefinition> ServiceDeviceInfo = ...` — Target device info, private for reservation use
- L111 _private field_ `private Dictionary< ServiceDeviceInfo = new Dictionary<ITargetDevice, DeviceDefinition>()` — Target device info, private for reservation use
- L113 _private field_ `private Dictionary<ITargetDevice, bool> InitialConnectionState = ...`
- L113 _private field_ `private Dictionary< InitialConnectionState = new Dictionary<ITargetDevice, bool>()`
- L115-125 _private property_ `private bool? IsInstallStep { get; set; }`
- L127-212 _private* ctor_ `static HordeDeviceReservationService()`
- L214-222 _public ctor_ `public HordeDeviceReservationService()`
- L225 _private field_ `private bool bDisposed`
- L226-229 _private* dtor_ `~HordeDeviceReservationService()`
- L231-234 _public method_ `public void Dispose()`
- L236-250 _public method_ `public void Dispose(bool bDisposing)`
- L253-278 _public method_ `public virtual bool CanSupportDeviceConstraint(UnrealDeviceTargetConstraint Constraint)`
- L280 _private* method_ `bool IDeviceReservationService.ReserveDevicesFromService(IEnumerable<UnrealDeviceTargetConstraint> RequestedConstraints, IDeviceReservationService.Options? Options)`
- L283-387 _public method_ `public virtual bool ReserveDevicesFromService(IEnumerable<UnrealDeviceTargetConstraint> RequestedConstraints, Options? Options = null)`
- L389 _private* method_ `void IDeviceReservationService.ReleaseDevices(IEnumerable<ITargetDevice> Devices, IDeviceReservationService.Options? Options)`
- L396-450 _public method_ `public void ReleaseDevices(IEnumerable<ITargetDevice> DeviceList, Options? Options = null)` — Release all devices in the provided list from our reserved list
- L455-477 _public method_ `public virtual void ReportDeviceError(string DeviceName, string ErrorMessage)` — Report target device issue to service with given error message
- L484-492 _public method_ `public List<string> GetDeviceTags(ITargetDevice Device)` — Returns a list of the tags on the device, if any
- L500-503 _public method_ `public bool DeviceHasTag(ITargetDevice Device, string Tag)` — Checks if a device has a tag
- L510-519 _private method_ `private static GetJobResponse GetJobInfo()` — Fetches information about the actively running job
- L527-540 _private method_ `private static GetJobBatchResponse GetBatchInfo(GetJobResponse Job)` — Fetches information about the actively running job batch
- L547-550 _private method_ `private static GetJobStepResponse GetStepInfo(GetJobBatchResponse Batch)` — Fetches information about the actively running job step

#### class `Gauntlet.HordeDeviceReservationService.Options`  
`public class Options : IDeviceReservationService.Options`  
_public; L42-49_
- inherits: `IDeviceReservationService.Options`
- L48 _public property_ `public bool bForceDelete { get; set; }` — If true, reservations will be force deleted. Force deleted reservations will also clean any associated reservation blocks regardless of future steps

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.DeviceValidator.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IDeviceValidator`  
`public interface IDeviceValidator`  
_public; L18-85_
- desc: IDeviceValidator provides the ability to verify a TargetDevice matches a set of requirements. They are particularly useful for ensuring development kits are in a desired state prior to a test. This can include, but is not limited to: - Proper firmware versions - Having an account signed in - Pushing a list of settings onto the device To add new DeviceValidators, simply create a concrete type that inherits from IDeviceValidator. Implement ValidateDevice() and determine whether this validator should be enabled within the constructor It can be especially helpful to toggle whether a validator is enabled via commandline arguments, for ease of opt-in
- L23 _public* property_ `bool bEnabled { get; }` — If false, this validator will not be used when reserving devices for automated tests
- L31 _public* method_ `bool TryValidateDevice(ITargetDevice Device, ref string Message)` — Verifies if the device is valid in the context of the running program
- L40-84 _protected method_ `protected static bool EnsureConnection(ITargetDevice Device, ref string Message)` — Helper function that can be used to ensure a device is powered on/connected before attempting to run any validation checks

### `Source/Programs/AutomationTool/Gauntlet/Framework/Devices/Gauntlet.UnrealDeviceReservation.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealDeviceReservation`  
`public class UnrealDeviceReservation`  
_public; L12-297_
- desc: Device reservation utility class.
- L14 _public property_ `public List<ITargetDevice> ReservedDevices { get; set; }`
- L15 _protected property_ `protected List<ProblemDevice> ProblemDevices { get; set; }`
- L16 _private field_ `private static object LockObject = new object()`
- L18 _private field_ `private static readonly HordeDeviceReservationService.Options ForceReleaseOption = new HordeDeviceReservationService.Options() { bForceDelete = true }`
- L23-148 _public method_ `public bool TryReserveDevices(Dictionary<UnrealDeviceTargetConstraint, int> RequiredDeviceTypes, int ExpectedNumberOfDevices, bool bAllowPartialReservations = false)`
- L150-166 _public method_ `public void ReleaseDevices(bool bForceClearServiceReservations = false)`
- L168-197 _public method_ `public IEnumerable<ITargetDevice> ReleaseProblemDevices()`
- L199-213 _public method_ `public void MarkProblemDevice(ITargetDevice Device, string ErrorMessage)`
- L220-256 _private method_ `private Dictionary<UnrealDeviceTargetConstraint, int> GetPartialReservationTypes(Dictionary<UnrealDeviceTargetConstraint, int> DeviceTypes)` — Converts a set of required devices into only what is necessary by analyzing the list of already reserved devices
- L258-285 _private method_ `private void EstablishDeviceConnections(IEnumerable<ITargetDevice> Devices)`
- L287-296 _private method_ `private bool ClaimDevices(IEnumerable<ITargetDevice> Devices)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/FileLockInfo.cs` (Gauntlet.Automation)


#### class `FileLockInfo.Win32Processes`  
`public static class Win32Processes`  
_public; L12-160_
- L14-32 _public method_ `public static string GetCommandLine(Process process)`
- L43-47 _public method_ `public static List<Process> GetProcessesLockingFile(string path)` — Find out what process(es) have a lock on the specified file.
- L49-83 _public method_ `public static List<Process> GetProcessesLockingFiles(string[] FilePaths)`
- L93 _private* const_ `const int RmRebootReasonNone = 0`
- L94 _private* const_ `const int CCH_RM_MAX_APP_NAME = 255`
- L95 _private* const_ `const int CCH_RM_MAX_SVC_NAME = 63`
- L124 _private* method_ `static extern int RmRegisterResources(uint pSessionHandle, uint nFiles, string[] rgsFilenames, uint nApplications, [In] RM_UNIQUE_PROCESS[] rgApplications, uint nServices, string[] rgsServiceNames)` — attrs: `[DllImport("rstrtmgr.dll", CharSet = CharSet.Unicode)]`
- L129 _private* method_ `static extern int RmStartSession(out uint pSessionHandle, int dwSessionFlags, string strSessionKey)` — attrs: `[DllImport("rstrtmgr.dll", CharSet = CharSet.Auto)]`
- L132 _private* method_ `static extern int RmEndSession(uint pSessionHandle)` — attrs: `[DllImport("rstrtmgr.dll")]`
- L135 _private* method_ `static extern int RmGetList(uint dwSessionHandle, out uint pnProcInfoNeeded, ref uint pnProcInfo, [In, Out] RM_PROCESS_INFO[] rgAffectedApps, ref uint lpdwRebootReasons)` — attrs: `[DllImport("rstrtmgr.dll")]`
- L139-159 _private method_ `private static List<Process> EnumerateProcesses(uint pnProcInfoNeeded, uint handle, uint lpdwRebootReasons)`

#### struct `FileLockInfo.Win32Processes.RM_UNIQUE_PROCESS`  
`public struct RM_UNIQUE_PROCESS`  
_public; L87-91_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L89 _public field_ `public int dwProcessId`
- L90 _public field_ `public System.Runtime.InteropServices.ComTypes.FILETIME ProcessStartTime`

#### enum `FileLockInfo.Win32Processes.RM_APP_TYPE`  
`public enum RM_APP_TYPE`  
_public; L97-106_
- L99 _public* enumerator_ `RmUnknownApp = 0`
- L100 _public* enumerator_ `RmMainWindow = 1`
- L101 _public* enumerator_ `RmOtherWindow = 2`
- L102 _public* enumerator_ `RmService = 3`
- L103 _public* enumerator_ `RmExplorer = 4`
- L104 _public* enumerator_ `RmConsole = 5`
- L105 _public* enumerator_ `RmCritical = 1000`

#### struct `FileLockInfo.Win32Processes.RM_PROCESS_INFO`  
`public struct RM_PROCESS_INFO`  
_public; L109-121_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L111 _public field_ `public RM_UNIQUE_PROCESS Process`
- L113 _public field_ `public string strAppName` — attrs: `[MarshalAs(UnmanagedType.ByValTStr, SizeConst = CCH_RM_MAX_APP_NAME + 1)]`
- L115 _public field_ `public string strServiceShortName` — attrs: `[MarshalAs(UnmanagedType.ByValTStr, SizeConst = CCH_RM_MAX_SVC_NAME + 1)]`
- L117 _public field_ `public RM_APP_TYPE ApplicationType`
- L118 _public field_ `public uint AppStatus`
- L119 _public field_ `public uint TSSessionId`
- L120 _public field_ `public bool bRestartable` — attrs: `[MarshalAs(UnmanagedType.Bool)]`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Gauntlet.AutoParam.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IAutoParamNotifiable`  
`public interface IAutoParamNotifiable`  
_public; L12-15_
- L14 _public* method_ `void ParametersWereApplied(string[] Params)`

#### class `Gauntlet.AutoParam`  
`public class AutoParam : System.Attribute`  
_public; L28-515_
- attrs: `[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]`
- inherits: `System.Attribute`
- desc: An attribute that can be used to apply commandline options to fields or properties. Simply tag properties or fields with the CommandLineOption, a name, and a default value, then call CommandLineOption.Apply(obj, args) where args is a list of -switches or -key=value pairs The main constraint is that your object type must be convertable from a string
- L33 _protected field_ `protected object Default` — Default value
- L38 _public property_ `public string[] OptionNames { get; set; }` — Names that can refer to this param
- L44-48 _public ctor_ `public AutoParam()` — Constructor that takes nothing. Param option should be -MemberName or -MemberName=value. Members with no matching param will be left as-is.
- L55-59 _protected ctor_ `protected AutoParam(params string[] OptionNames)` — Constructor that takes an array of of potential argument names, e.g. {"build","builds"} Members with no matching param will be left as-is.
- L68-72 _public ctor_ `public AutoParam(object Default)` — Constructor that takes a default argument to use if no param is specified. Param option should be -MemberName or -MemberName=value. Members with no matching param will be set to 'Default'
- L80-84 _protected ctor_ `protected AutoParam(object Default, params string[] OptionNames)` — Constructor that takes an array of of potential argument names, e.g. {"build","builds"} Members with no matching param will be set to 'Default'
- L95-118 _protected method_ `static protected object CoerceToBool(string Param, string[] Args)` — Checks whether Args contains a -Param statement, if so returns true else checks if the passed argument is different from true or 1
- L128-167 _protected method_ `static protected object ParseAndCoerceParam(string Param, Type ParamType, string[] Args)` — Checks Args for a -param=value statement and either returns value or the provided default
- L174-180 _private* method_ `static bool IsSimple(Type type)` — Returns true if this type is considered a simple primitive (there is IsClass in c# but no IsStruct :()
- L188-212 _private method_ `private static bool IsEnumerableType(Type Type, out Type ElementType)` — Returns true if this type inherits from IEnumerable<>
- L221-315 _protected method_ `protected static void ApplyParamsAndDefaultsInternal(object Obj, string[] Args, bool ApplyDefaults, char EnumerableSeparator = ',')` — Call to process all CommandLineOption attributes on an objects members and set them based on the provided argument list
- L317-320 _public method_ `public static void ApplyDefaults(object Obj, char EnumerableSeparator = ',')`
- L322-325 _public method_ `public static void ApplyParams(object Obj, string[] Args, char EnumerableSeparator = ',')`
- L327-330 _public method_ `public static void ApplyParamsAndDefaults(object Obj, string[] Args, char EnumerableSeparator = ',')`
- L332-342 _private method_ `private static void SetMemberValue(MemberInfo Member, object Obj, object Value)`
- L344-362 _private method_ `private static void ApplyDefaultValue(AutoParam Param, MemberInfo Member, Type MemberType, object Obj, char EnumerableSeparator = ',')`
- L364-395 _private method_ `private static object ConstructComplexObject(string[] Args, MemberInfo Member, Type MemberType, object Obj, bool bApplyDefaults, char EnumerableSeparator = ',')`
- L397-465 _private method_ `private static object ConstructEnumerableFromString(MemberInfo Member, Type MemberType, Type ElementType, string Value, char EnumerableSeparator = ',')`

#### class `Gauntlet.AutoParamWithNames`  
`public class AutoParamWithNames : AutoParam`  
_public; L518-529_
- attrs: `[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]`
- inherits: `AutoParam`
- L520-523 _public ctor_ `public AutoParamWithNames(object Default, params string[] OptionNames) : base(Default, OptionNames)`
- L525-528 _public ctor_ `public AutoParamWithNames(params string[] OptionNames) : base(OptionNames)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Gauntlet.Exception.cs` (Gauntlet.Automation)


#### class `Gauntlet.TestException`  
`public class TestException : System.Exception`  
_public; L5-21_
- inherits: `System.Exception`
- L7-10 _public ctor_ `public TestException(string Msg) : base(Msg)`
- L12-15 _public ctor_ `public TestException(string Message, System.Exception InnerException) : base(Message, InnerException)`
- L17-20 _public ctor_ `public TestException(string Format, params object[] Args) : base(string.Format(Format, Args))`

#### class `Gauntlet.NonCriticalTestException`  
`public class NonCriticalTestException : TestException`  
_public; L23-38_
- inherits: `TestException`
- L25-27 _public ctor_ `public NonCriticalTestException(string Msg) : base(Msg)`
- L29-32 _public ctor_ `public NonCriticalTestException(string Message, System.Exception InnerException) : base(Message, InnerException)`
- L34-37 _public ctor_ `public NonCriticalTestException(string Format, params object[] Args) : base(string.Format(Format, Args))`

#### class `Gauntlet.DeviceException`  
`public class DeviceException : TestException`  
_public; L40-56_
- inherits: `TestException`
- L42-45 _public ctor_ `public DeviceException(string Msg) : base(Msg)`
- L47-50 _public ctor_ `public DeviceException(string Message, System.Exception InnerException) : base(Message, InnerException)`
- L52-55 _public ctor_ `public DeviceException(string Format, params object[] Args) : base(Format, Args)`

#### class `Gauntlet.InterruptTestException`  
`public class InterruptTestException : TestException`  
_public; L62-72_
- inherits: `TestException`
- desc: Exception class to be used for errors that stop the test case, but are not specifically a failure of the behavior being tested. For instance, setup issues or system/environment problems.
- L64-66 _public ctor_ `public InterruptTestException(string Msg) : base(Msg)`
- L68-71 _public ctor_ `public InterruptTestException(string Message, System.Exception InnerException) : base(Message, InnerException)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Gauntlet.Params.cs` (Gauntlet.Automation)


#### class `Gauntlet.Params`  
`public class Params`  
_public; L14-189_
- L16 _public property_ `public string[] AllArguments { get; set; }`
- L18-22 _public ctor_ `public Params(IEnumerable<string>InArgs)`
- L29-41 _public method_ `public bool ParseParam(string Param)` — Parses the argument list for a parameter and returns whether it is defined or not.
- L49-60 _public method_ `public bool ParseParams(params string[] Params)` — Parses the argument list for a set of parameters and returns whether any are defined or not. Useful for cases where you want one setting to have multiple possible command line triggers
- L71-136 _public method_ `public List<string> ParseValues(string Param, bool CommaSeparated=false, List<string> Default = default)` — Parses multiple values from a param. The multiple values can either be specified as repeated arguments, e.g. -foo=one -foo=two, or when 'CommaSeparated' is true as a comma-separated list, e.g. -foo=one,two, -foo="one, two".
- L145-150 _public method_ `public string ParseValue(string Param, string Default = null)` — Parses the argument list for a string parameter and reads its value. Ex. ParseParamValue(Args, "map=")
- L159-169 _public method_ `public int ParseValue(string Param, int Default = 0)` — Parses the argument list for an int parameter and reads its value. Ex. ParseParamValue(Args, "timeout=")
- L178-188 _public method_ `public float ParseValue(string Param, float Default = 0)` — Parses the argument list for a float parameter and reads its value. Ex. ParseParamValue(Args, "timeout=")

#### class `Gauntlet.ArgumentWithParams`  
`public class ArgumentWithParams : Params`  
_public; L191-263_
- inherits: `Params`
- L193 _public property_ `public string Argument { get; set; }`
- L195-199 _public ctor_ `public ArgumentWithParams(string InArgument, IEnumerable<string> InArgs) : base(InArgs)`
- L203-262 _public method_ `public static List<ArgumentWithParams> CreateFromString(string Input)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Gauntlet.TestExecutor.cs` (Gauntlet.Automation)


#### class `Gauntlet.TestExecutorOptions`  
`public class TestExecutorOptions`  
_public; L16-54_
- L19 _public field_ `public int TestIterations` — attrs: `[AutoParamWithNames(1, "iterations", "repeat")]`
- L22 _public field_ `public bool StopOnError` — attrs: `[AutoParam(false)]`
- L25 _public field_ `public bool NoTimeout` — attrs: `[AutoParam(false)]`
- L28 _public field_ `public int Wait` — attrs: `[AutoParam(300)]`
- L31 _public field_ `public int Parallel` — attrs: `[AutoParam(1)]`
- L34 _public field_ `public bool DeferReports` — attrs: `[AutoParam(true)]`
- L42 _public field_ `public int TestIterationCooldownSeconds` — attrs: `[AutoParam(0)]` — Optional delay in seconds to wait between test iterations. Primarily used to allow devices to cool down when benchmarking to mitigate thermal throttling. Default is 0 (no additional delay beyond standard crash processing time). Users can tune this value based on their specific device thermal characteristics and observed behavior.
- L53 _public field_ `public int StartingThreadShutdownLimitSeconds` — attrs: `[AutoParam(3 * 60)]` — Maximum number of seconds to wait for test start threads to join when a cancel is signalled If this time elapses, the thread is abandoned and expected to close on it's own. The most common case of this happening is during an installation to a devkit in UnrealSession ------- TODO: InstallBuild should be given a cancellation token so we're not forced to wait or rely on platform dependent implementations to handle cancellations in the middle of a synchronous sdk command call

#### class `Gauntlet.TestExecutor`  
`public class TestExecutor`  
_public; L59-1015_
- desc: Class that is manages the creation and execution of one or more tests
- L115 _private field_ `private List<TestExecutionInfo> RunningTests`
- L117 _private field_ `private DateTime CurrentTestStartTime`
- L119 _private field_ `private int CurrentTestPass`
- L121 _private* field_ `TestExecutorOptions Options`
- L123 _protected field_ `protected string BuildCommandThatLaunchedExecutor`
- L125 _public property_ `public bool IsRunning { get; set; }`
- L126 _public property_ `public bool IsCancelled { get; set; }`
- L127 _protected property_ `protected bool HaveReceivedPostAbort { get; set; }`
- L134-138 _public ctor_ `public TestExecutor(string InBuildCommand)` — Constructor that fills in some member variables @Param the BuildCommand that was used to start this Test Executor. Useful to log out or know where this test executor came from.
- L140-142 _public method_ `public void Dispose()`
- L149-639 _public method_ `public bool ExecuteTests(TestExecutorOptions InOptions, IEnumerable<ITestNode> RequiredTests)` — Executes the provided tests. Currently tests are executed synchronously
- L648-670 _private method_ `private bool StartTest(TestExecutionInfo TestInfo, int Pass, int NumPasses)` — Executes a single test
- L677-737 _private* method_ `void ReportTestSummary(TestExecutionInfo TestInfo)` — Report the summary for a single test
- L747-813 _private* method_ `void ReportMainSummary(int CurrentPass, int NumPasses, TimeSpan Duration, IEnumerable<TestExecutionInfo> AllInfo)` — Reports the summary of this pass, including a sumamry for each test
- L815-958 _private* method_ `TestResult TickTest(TestExecutionInfo TestInfo)`
- L964-1014 _private* method_ `bool WaitForTests()` — Waits for all pending tests to complete. Returns true/false based on whether all tests completed successfully.

#### class `Gauntlet.TestExecutor.TestExecutionInfo`  
`class TestExecutionInfo`  
_private*; L61-113_
- L73 _public field_ `public ITestNode TestNode`
- L74 _public field_ `public DateTime FirstReadyCheckTime`
- L75 _public field_ `public DateTime TimeSetupBegan`
- L76 _public field_ `public DateTime TimeSetupEnded`
- L77 _public field_ `public DateTime TimeTestEnded`
- L78 _public field_ `public ExecutionResult Result`
- L79 _public field_ `public TestResult FinalResult`
- L80 _public field_ `public string CancellationReason`
- L85 _public property_ `public TimeSpan WaitDuration { get; }` — Time the test had to wait before running
- L90 _public property_ `public TimeSpan SetupDuration { get; }` — Time the test had to wait before running
- L95 _public property_ `public TimeSpan TestDuration { get; }` — Time the test took to run
- L102-107 _public ctor_ `public TestExecutionInfo(ITestNode InNode)` — Creates TestExecutionInfo instance from an ITestNode. Sets FirstReadyCheckTime, copies the node and sets CancellationReason to empty string.
- L109-112 _public method_ `public override string ToString()`

#### enum `Gauntlet.TestExecutor.TestExecutionInfo.ExecutionResult`  
`public enum ExecutionResult`  
_public; L63-71_
- L65 _public* enumerator_ `NotStarted`
- L66 _public* enumerator_ `TimedOut`
- L67 _public* enumerator_ `Passed`
- L68 _public* enumerator_ `Failed`
- L69 _public* enumerator_ `Skipped`
- L70 _public* enumerator_ `Interrupted`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Gauntlet.TestGroup.cs` (Gauntlet.Automation)


#### class `Gauntlet.TestGroup`  
`public class TestGroup : System.Attribute`  
_public; L14-28_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `System.Attribute`
- L19 _public field_ `public string GroupName` — Names that can refer to this param
- L21 _public field_ `public int Priority`
- L23-27 _public ctor_ `public TestGroup(string InGroupName, int InPriority=5)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Gauntlet.Utils.cs` (Gauntlet.Automation)


#### class `Gauntlet.Globals`  
`public static class Globals`  
_public; L26-181_
- L28 _private* field_ `static Params InnerParams = new Params(Environment.GetCommandLineArgs())`
- L30-34 _public property_ `public static Params Params { get; set; }`
- L36 _public field_ `public static string BuildCommand = String.Empty`
- L38 _public field_ `public static readonly DateTime ProgramStartTime = DateTime.UtcNow`
- L40 _private* field_ `static string InnerTempDir`
- L41 _private* field_ `static string InnerLogDir`
- L42 _private* field_ `static string InnerUnrealRootDir`
- L43 _private* field_ `static object InnerLockObject = new object()`
- L44 _private* field_ `static List<Action> InnerAbortHandlers`
- L45 _private* field_ `static List<Action> InnerPostAbortHandlers = new List<Action>()`
- L46 _public property_ `public static bool CancelSignalled { get; set; }`
- L48 _public property_ `public static bool IsRunningDev => ...`
- L53-59 _public property_ `public static string DevicePoolId { get; }` — Returns the device pool id
- L68 _public property_ `public static bool UseExperimentalFeatures => ...` — This acts as a broad feature flag to allow for a smoother integration of large flow changes without impacting licensees. When true, Gauntlet will execute alternative "experimental" code paths in several areas of project, primarily effecting executions of RunUnreal Most notable areas this is used: - UnrealSession | Modifies the code path of LaunchSession to better reserve, setup, and handle errors for devices. - DevicePool | Removes the strict expectation that Horde is used as a device service. Allows users to specify new services, such as a cloud provider.
- L70-85 _public property_ `public static string TempDir { get; set; }`
- L87-102 _public property_ `public static string LogDir { get; set; }`
- L104-116 _public property_ `public static string UnrealRootDir { get; }`
- L122-125 _public property_ `public static string LongPathPrefix { get; }` — Return @"\\?\"; adding the prefix to a path string tells the Windows APIs to disable all string parsing and to send the string that follows it straight to the file system. Allowing for longer than 260 characters path.
- L132-135 _public property_ `public static object MainLock { get; }` — Acquired and released during the main Tick of the Gauntlet systems. Use this before touchung anything global scope from a test thread.
- L141-169 _public property_ `public static List<Action> AbortHandlers { get; }` — Allows classes to register for notification of system-wide abort request. On an abort (e.g. ctrl+c) all handlers will be called and then shutdown will continue
- L175 _public property_ `public static List<Action> PostAbortHandlers { get; }` — Allows classes to register for post-abort handlers. These are called after all abort handlers have returned so is the place to perform final cleanup.
- L180 _public property_ `public static string PreferredNetworkDomain { get; }` — Used by network functions that need to deal with multiple adapters

#### enum `Gauntlet.LogLevel`  
`public enum LogLevel`  
_public; L186-191_
- desc: Enable/disable verbose logging
- L188 _public* enumerator_ `Normal`
- L189 _public* enumerator_ `Verbose`
- L190 _public* enumerator_ `VeryVerbose`

#### class `Gauntlet.Log`  
`public class Log`  
_public; L196-479_
- desc: Gauntlet Logging helper
- L198 _public field_ `public static LogLevel Level = LogLevel.Normal`
- L200-206 _public property_ `public static bool IsVerbose { get; }`
- L208-214 _public property_ `public static bool IsVeryVerbose { get; }`
- L216 _private* field_ `static TextWriter LogFile = null`
- L218 _private* field_ `static List<Action<string>> Callbacks`
- L220 _private* field_ `static int ECSuspendCount = 0`
- L222 _private* field_ `static int SanitizationSuspendCount = 0`
- L224 _private* field_ `static ILogger Logger = EpicGames.Core.Log.Logger`
- L226-234 _public method_ `public static void AddCallback(Action<string> CB)`
- L236-269 _public method_ `public static void SaveToFile(string InPath)`
- L271-277 _private* method_ `static void Flush()`
- L279-288 _public method_ `public static void SuspendECErrorParsing()`
- L290-299 _public method_ `public static void ResumeECErrorParsing()`
- L301-304 _public method_ `public static void SuspendSanitization()`
- L306-309 _public method_ `public static void ResumeSanitization()`
- L319-332 _private method_ `static private string SanitizeInput(string Input, string[] Sanitize)` — Santi
- L344-408 _private method_ `static private void OutputMessage(string Message, Logging.EventId EventId, Logging.LogLevel Level = Logging.LogLevel.Information, bool Sanitize=true, params object[] Args)` — Outputs the message to the console with an optional log level and sanitization. Sanitizing allows errors and exceptions to be passed through to logs without triggering CIS warnings about out log
- L410-416 _public method_ `static public void Verbose(string Format, params object[] Args)`
- L418-424 _public method_ `static public void Verbose(Logging.EventId EventId, string Format, params object[] Args)`
- L426-432 _public method_ `static public void VeryVerbose(string Format, params object[] Args)`
- L434-440 _public method_ `static public void VeryVerbose(Logging.EventId EventId, string Format, params object[] Args)`
- L442-445 _public method_ `static public void Info(string Format, params object[] Args)`
- L447-450 _public method_ `static public void Info(Logging.EventId EventId, string Format, params object[] Args)`
- L452-455 _public method_ `static public void Warning(string Format, params object[] Args)`
- L457-460 _public method_ `static public void Warning(Logging.EventId EventId, string Format, params object[] Args)`
- L462-465 _public method_ `static public void Error(string Format, params object[] Args)`
- L466-469 _public method_ `static public void Error(Logging.EventId EventId, string Format, params object[] Args)`
- L471-474 _public method_ `static public void Critical(string Format, params object[] Args)`
- L475-478 _public method_ `static public void Critical(Logging.EventId EventId, string Format, params object[] Args)`

#### class `Gauntlet.Reporter`  
`public class Reporter`  
_public; L486-612_
- desc: Helper class providing logging methods for test events of various levels. Used to clearly display test events on the Horde dashboard, eliminates inconsistent reporting.
- L488 _private field_ `private static volatile Reporter? _Instance`
- L489 _private field_ `private static readonly object _Lock = new object()`
- L491-494 _private ctor_ `private Reporter()`
- L496-512 _public property_ `public static Reporter Instance { get; }`
- L514 _private field_ `private PhaseQueue? _Phases`
- L515 _private field_ `private Action<TestResult>? _SetUnrealTestResult`
- L516 _private field_ `private BaseTest? _TestNode`
- L525-530 _public method_ `public void UpdateReferences(PhaseQueue Phases, Action<TestResult> SetUnrealTestResult, BaseTest TestNode)` — This method is used to switch context when running tests in parallel. The method should be called each time TestExecutor switches between test nodes, such as in node loops, etc.
- L537-551 _public method_ `public void Interrupt(string Message, params object[] Args)` — Report a test-halting error that is NOT directly related to the behavior that is being tested.
- L558-572 _public method_ `public void Failure(string Message, params object[] Args)` — Report a test failure. Specifically, the behavior that is targeted by the test case did not function as expected.
- L579-582 _public method_ `public void Warning(string Message, params object[] Args)` — Report a warning with Gauntlet_TestEvent
- L590-599 _public method_ `public void Warning(EventId EventId, string Message, params object[] Args)` — Report a warning with required Log Event type
- L606-611 _public method_ `public void Info(string Message, params object[] Args)` — Report information

#### class `Gauntlet.Hasher`  
`public class Hasher`  
_public; L615-662_
- L617-636 _public method_ `public static string ComputeHash(string Input)`
- L638-659 _public method_ `public static string ComputeHash(string Input, HashAlgorithm Algo, int MaxLength = 0)`
- L661 _public field_ `static public HashAlgorithm DefaultAlgo = SHA1.Create()`

#### class `Gauntlet.ScopedSuspendECErrorParsing`  
`public class ScopedSuspendECErrorParsing : IDisposable`  
_public; L667-698_
- inherits: `IDisposable`
- L669-672 _public ctor_ `public ScopedSuspendECErrorParsing()`
- L674-677 _private* dtor_ `~ScopedSuspendECErrorParsing()`
- L680 _private field_ `private bool disposedValue = false`
- L682-690 _protected method_ `protected virtual void Dispose(bool disposing)`
- L693-696 _public method_ `public void Dispose()`

#### class `Gauntlet.Utils.TestConstructor`  
`public class TestConstructor`  
_public; L702-972_
- L710-812 _private method_ `private static Type GetTypeForTest(string TestName, IEnumerable<string> Namespaces)` — Helper function that returns the type of an object based on namespaces and name
- L821-832 _public method_ `public static IEnumerable<Type> GetTypesInNamespaces<BaseType>(IEnumerable<string> Namespaces) where BaseType : class` — Helper function that returns all types within the specified namespace that are or derive from the specified type
- L843-881 _public method_ `public static TestType ConstructTest<TestType, ParamType>(string TestName, ParamType Arg, IEnumerable<string> Namespaces) where TestType : class` — Constructs by name a new test of type "TestType" that takes no construction parameters
- L893-904 _public method_ `public static IEnumerable<TestType> ConstructTests<TestType, ParamType>(IEnumerable<string> TestNames, ParamType Arg, IEnumerable<string> Namespaces) where TestType : class` — Constructs by name a list of tests of type "TestType" that take no construction params
- L913-924 _public method_ `public static IEnumerable<TestType> ConstructTests<TestType>(IEnumerable<string> TestNames, IEnumerable<string> Namespaces) where TestType : class` — Constructs by name a list of tests of type "TestType" that take no construction params
- L933-970 _public method_ `public static IEnumerable<string> GetTestNamesByGroup<TestType>(string Group, IEnumerable<string> Namespaces) where TestType : class` — Constructs by name a list of tests of type "TestType" that take no construction params

#### class `Gauntlet.Utils.InterfaceHelpers`  
`public static class InterfaceHelpers`  
_public; L974-1040_
- L976-1000 _public method_ `public static IEnumerable<Type> FindTypes<InterfaceType>(bool bIncludeCompiledScripts = false, bool bConcreteTypesOnly = false) where InterfaceType : class`
- L1002-1021 _public method_ `public static IEnumerable<InterfaceType> FindImplementations<InterfaceType>(bool bIncludeCompiledScripts = false) where InterfaceType : class`
- L1029-1038 _public method_ `public static bool HasOverriddenMethod(Type ClassType, string MethodName, Type[] Signature)` — Check if the method signature is overridden.

#### class `Gauntlet.Utils.SystemHelpers`  
`public static class SystemHelpers`  
_public; L1043-1850_
- L1114-1117 _public method_ `public static void CopyDirectory(string SourceDirPath, string DestDirPath, CopyOptions Mode = CopyOptions.Default, int RetryCount = 5)` — Convenience function that removes some of the more esoteric options
- L1127-1135 _public method_ `public static void CopyDirectory(string SourceDirPath, string DestDirPath, CopyOptions Mode, Func<string, string> Transform, int RetryCount = 5)` — Legacy convenience function that exposes transform & Retry count
- L1144-1453 _public method_ `public static void CopyDirectory(string SourceDirPath, string DestDirPath, CopyDirectoryOptions Options)` — Copies src to dest by comparing files sizes and time stamps and only copying files that are different in src. Basically a more flexible robocopy
- L1455-1467 _public method_ `public static string MakePathRelative(string FullPath, string BasePath)`
- L1469-1479 _public method_ `public static string CorrectDirectorySeparators(string InPath)`
- L1481-1497 _public method_ `public static bool ApplicationExists(string InPath)`
- L1499-1515 _public method_ `public static bool IsNetworkPath(string InPath)`
- L1521-1531 _public method_ `public static void MarkDirectoryForCleanup(string InPath)` — Marks a directory for future cleanup
- L1540-1582 _public method_ `public static void CleanupMarkedDirectories(string InPath, int Days)` — Removes any directory at the specified path which has a file matching the provided name older than the specified number of days. Used by code that writes a .token file to temp folders
- L1587-1607 _public method_ `public static FileInfo[] GetFiles(DirectoryInfo Directory)` — Wrap DirectoryInfo.GetFiles() and retry once if exception is "A retry should be performed."
- L1612-1632 _public method_ `public static FileInfo[] GetFiles(DirectoryInfo Directory, string Pattern, SearchOption SearchOption)` — Wrap DirectoryInfo.GetFiles(Pattern, SearchOption) and retry once if exception is "A retry should be performed."
- L1637-1657 _public method_ `public static DirectoryInfo[] GetDirectories(DirectoryInfo Directory)` — Wrap DirectoryInfo.GetDirectories() and retry once if exception is "A retry should be performed."
- L1662-1682 _public method_ `public static DirectoryInfo[] GetDirectories(DirectoryInfo Directory, string Pattern, SearchOption SearchOption)` — Wrap DirectoryInfo.GetDirectories(Pattern, SearchOption) and retry once if exception is "A retry should be performed."
- L1692-1712 _public method_ `public static FileSystemInfo[] GetFileSystemInfos(DirectoryInfo Directory, string Pattern, SearchOption SearchOption)` — Wrap DirectoryInfo.GetFileSystemInfos(Pattern, SearchOption) and retry once if exception is "A retry should be performed."
- L1720-1803 _public method_ `public static void Delete(DirectoryInfo Directory, bool bRecursive, bool bForce = false)` — Deletes the specified directory
- L1810-1834 _public method_ `public static void Delete(FileInfo File, bool bForce = false)` — Deletes the specified file
- L1841-1849 _public method_ `public static string GetFullyQualifiedPath(string FilePath)` — Return the fully qualified location of file path, including the Long path prefix if necessary

#### enum `Gauntlet.Utils.SystemHelpers.CopyOptions`  
`public enum CopyOptions`  
_public; L1048-1053_
- desc: Options for copying directories
- L1050 _public* enumerator_ `Copy = (1 << 0)`
- L1051 _public* enumerator_ `Mirror = (1 << 1)`
- L1052 _public* enumerator_ `Default = Copy`

#### class `Gauntlet.Utils.SystemHelpers.CopyDirectoryOptions`  
`public class CopyDirectoryOptions`  
_public; L1058-1105_
- desc: Options that can be specified to the CopyDirectory function.
- L1060 _public property_ `public CopyOptions Mode { get; set; }`
- L1062 _public property_ `public int Retries { get; set; }`
- L1064 _public property_ `public Func<string, string> Transform { get; set; }`
- L1066 _public property_ `public string Pattern { get; set; }`
- L1068 _public property_ `public Regex Regex { get; set; }`
- L1070 _public property_ `public bool Recursive { get; set; }`
- L1072 _public property_ `public bool Verbose { get; set; }`
- L1074-1086 _public ctor_ `public CopyDirectoryOptions()`
- L1091-1104 _public property_ `public bool IsDirectoryPattern { get; }` — Returns true if the pattern indicates entire directory should be copied

#### class `Gauntlet.Utils.Image`  
`public class Image`  
_public; L1852-2021_
- L1854-1863 _protected method_ `protected static IEnumerable<FileInfo> GetSupportedFilesAtPath(string InPath)`
- L1866-1906 _public method_ `public static bool SaveImagesAsGif(IEnumerable<string> FilePaths, string OutPath, uint Delay=100)`
- L1908-1926 _public method_ `public static bool SaveImagesAsGif(string InDirectory, string OutPath)`
- L1928-1961 _public method_ `public static bool ResizeImages(string InDirectory, uint MaxWidth)`
- L1964-2020 _public method_ `public static bool ConvertImages(string InDirectory, string OutDirectory, string OutExtension, bool DeleteOriginals)`

#### class `Gauntlet.RegexUtil`  
`public static class RegexUtil`  
_public; L2024-2045_
- L2026-2029 _public method_ `public static bool MatchAndApplyGroups(string InContent, string RegEx, Action<string[]> InFunc)`
- L2031-2044 _public method_ `public static bool MatchAndApplyGroups(string InContent, string RegEx, RegexOptions Options, Action<string[]> InFunc)`

#### class `Gauntlet.DirectoryUtils`  
`public static class DirectoryUtils`  
_public; L2047-2168_
- L2055-2062 _public method_ `public static IEnumerable<string> FindFiles(string BaseDir, Regex Pattern)` — Enumerate files from a given directory that pass the specified regex
- L2071-2079 _public method_ `public static bool PathContainsComponent(string InPath, string InComponent, bool InPartialMatch=false)` — Returns true if any part of the specified path contains 'Component'. E.g. c:\Temp\Foo\Bar would return true for 'Foo'
- L2088-2110 _public method_ `public static IEnumerable<DirectoryInfo> FindMatchingDirectories(string BaseDir, string RegexPattern, int RecursionDepth=0)` — Returns subdirectories that match the specified regular expression, searching up to the specified maximum depth
- L2120-2125 _public method_ `public static IEnumerable<FileInfo> FindMatchingFiles(string BaseDir, string RegexPattern, int RecursionDepth = 0)` — Returns files, that match the specified regular expression, ignoring case, in the provided folder, searching up to a maximum depth
- L2134-2137 _public method_ `public static IEnumerable<FileInfo> FindMatchingFiles(string BaseDir, Regex RegExObj, int RecursionDepth = 0)` — Returns files that match a specified regular expression in the provided folder, searching up to a maximum depth
- L2146-2167 _private method_ `private static IEnumerable<FileInfo> MatchFiles(string BaseDir, Regex RegExObj, int RecursionDepth)` — Returns files that match the given RegEx from the provided folder, searching up to a maximum depth

#### class `Gauntlet.FileUtils`  
`public static class FileUtils`  
_public; L2170-2191_
- L2177-2180 _public method_ `static public string SanitizeFilename(string Name)` — Sanitize filename
- L2187-2190 _public method_ `static public string ConvertPathToUnix(string Path)` — Convert file path to Unix-style path

#### class `Gauntlet.ProcessUtils`  
`public static class ProcessUtils`  
_public; L2193-2324_
- L2203-2211 _public method_ `static public StreamWriter CreateWriterForProcessLog(string FilePath, string Commandline)` — Create a text file with a header listing Gauntlet Test and command line used. Return the StreamWriter instance used to create the file. Intended to be used for log file.
- L2220-2227 _public method_ `static public bool WriteOutputLog(IAppInstance AppInstance, string FilePath, string Commandline)` — Write output log from IAppInstance if related instance log size is under size limit.
- L2233-2236 _public method_ `static public long GetProcessLogSizeLimit()` — Get log size limit for log file in bytes. Return 0 if -NoMaxLogSize is used.
- L2238-2249 _public method_ `static public void CheckProcessLogReachedSizeLimit(IAppInstance AppInstance)`
- L2256-2267 _public method_ `static public void CheckProcessLogReachedSizeLimit(FileReference LogFile)` — Check if LogFile size reached limit. Throw AutomationException if reached.
- L2273-2276 _public method_ `static public int GetCircularLogBufferCapacityLimit()` — Get CircularLogBuffer line capacity limit.
- L2282-2285 _public method_ `static public CircularLogBuffer CreateLogBuffer()` — Create CircularLogBuffer using Gauntlet default buffer line limit
- L2293-2318 _public method_ `static public string GetLogFilePath(string AppName, string LocalCache)` — Try to get a log file. Return the available file path.
- L2323 _public property_ `static public string LocalLogsPath => ...` — Local logs cache

#### interface `Gauntlet.ILogStreamReader`  
`public interface ILogStreamReader`  
_public; L2329-2374_
- desc: Interface for stream reader used in context of log
- L2335 _public* method_ `void SetLineIndex(int LineIndex)` — Set desired line index to start reading line
- L2341 _public* method_ `int GetLineIndex()` — Get line index used to read next line
- L2348 _public* method_ `string GetNextLine()` — Get next line at line index and increment line index by one. Return null if no line is available.
- L2355 _public* method_ `string GetContent()` — Return full content of available underlying stream. This is for backward compatibility. It is not efficient and defy the purpose of using a stream reader.
- L2361 _public* method_ `IEnumerable<string> EnumerateNextLines()` — Generate an enumerator that iterates all available lines from last line index (and update it).
- L2367 _public* method_ `int GetAvailableLineCount()` — Get available line count from the underlying stream
- L2373 _public* method_ `ILogStreamReader Clone()` — Clone the stream reader including current line index

#### class `Gauntlet.DynamicStringReader`  
`public class DynamicStringReader : ILogStreamReader`  
_public; L2380-2473_
- inherits: `ILogStreamReader`
- desc: Provide a ILogStreamReader from a string using a callback to pull that string dynamically. Used in conjunction with IProcessResult to read process output.
- L2382 _private field_ `private Func<string> _getLog`
- L2383 _private field_ `private int _lineIndex = 0`
- L2384 _private field_ `private int _targetLineIndex = 0`
- L2385 _private field_ `private int _contentCharIndex = 0`
- L2387-2393 _public ctor_ `public DynamicStringReader(Func<string> Callback)`
- L2395-2403 _public method_ `public void SetLineIndex(int LineIndex)`
- L2405 _public method_ `public int GetLineIndex()`
- L2407-2429 _public method_ `public string GetNextLine()`
- L2431-2451 _private method_ `private void SkipToTargetIndex(string StdOut)`
- L2453-2461 _public method_ `public IEnumerable<string> EnumerateNextLines()`
- L2463 _public method_ `public string GetContent()`
- L2465 _public method_ `public int GetAvailableLineCount()`
- L2467-2472 _public method_ `public ILogStreamReader Clone()`

#### class `Gauntlet.LogFileReader`  
`public class LogFileReader : ILogStreamReader, IDisposable`  
_public; L2478-2590_
- inherits: `ILogStreamReader, IDisposable`
- desc: Provide a ILogStreamReader instance from a text file
- L2480 _private field_ `private string _filePath`
- L2481 _private field_ `private StreamReader _stream`
- L2482 _private field_ `private FileStream _file`
- L2483 _private field_ `private int _lineIndex`
- L2484 _private field_ `private int _targetLineIndex`
- L2486-2493 _public ctor_ `public LogFileReader(string FilePath)`
- L2495-2498 _private* dtor_ `~LogFileReader()`
- L2500-2504 _public method_ `public void Dispose()`
- L2506-2509 _public method_ `public void SetLineIndex(int Index)`
- L2511 _public method_ `public int GetLineIndex()`
- L2513-2538 _public method_ `public string GetNextLine()`
- L2540-2552 _public method_ `public string GetContent()`
- L2554-2562 _public method_ `public IEnumerable<string> EnumerateNextLines()`
- L2564-2582 _public method_ `public int GetAvailableLineCount()`
- L2584-2589 _public method_ `public ILogStreamReader Clone()`

#### class `Gauntlet.LogBufferReader`  
`public class LogBufferReader : ILogStreamReader`  
_public; L2595-2651_
- inherits: `ILogStreamReader`
- desc: Provide a ILogStreamReader instance from a CircularLogBuffer
- L2597 _private field_ `private int _lineIndex = 0`
- L2598 _private field_ `private CircularLogBuffer _buffer`
- L2600-2604 _public ctor_ `public LogBufferReader(CircularLogBuffer Buffer)`
- L2606-2616 _public method_ `public void SetLineIndex(int LineIndex)`
- L2618 _public method_ `public int GetLineIndex()`
- L2620-2629 _public method_ `public string GetNextLine()`
- L2631-2639 _public method_ `public IEnumerable<string> EnumerateNextLines()`
- L2641 _public method_ `public string GetContent()`
- L2643 _public method_ `public int GetAvailableLineCount()`
- L2645-2650 _public method_ `public ILogStreamReader Clone()`

#### class `Gauntlet.CircularLogBuffer`  
`public class CircularLogBuffer : IEnumerable<string>`  
_public; L2656-2830_
- inherits: `IEnumerable<string>`
- desc: Circular log buffer separating input as line. Capacity being based on lines.
- L2658 _private field_ `private string[] _list`
- L2659 _private field_ `private int _capacity = 0`
- L2660 _private field_ `private int _lineIndex = -1`
- L2661 _private field_ `private ReaderWriterLockSlim _lock = new ReaderWriterLockSlim()`
- L2663-2673 _public ctor_ `public CircularLogBuffer(int Capacity)`
- L2680-2694 _public method_ `public CircularLogBuffer Feed(string Content)` — Allow to feed the log buffer with text content. The input is parsed and separated into lines.
- L2701-2715 _public method_ `public CircularLogBuffer AppendLine(string Item)` — Append input line to the log buffer
- L2721-2724 _public method_ `public int GetLastLineIndex()` — Get last line index input
- L2732-2735 _public method_ `public int GetFirstAvailableLineIndex()` — Get the first/oldest available line index. If the capacity was reached, the first lines are lost, the returned line index will be that first available line
- L2742-2745 _public method_ `public int GetAvailableLineCount()` — Available line count. If the capacity was reached, the capacity will be returned.
- L2752-2773 _public method_ `public string GetLine(int LineIndex)` — Get line at index
- L2779-2782 _public method_ `public LogBufferReader GetReader()` — Return an instance of LogBufferReader
- L2788-2811 _public method_ `public IEnumerator<string> GetEnumerator()` — Return an enumerator that iterate all available lines
- L2817-2820 _private* method_ `System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()` — Return an enumerator that iterate all available lines
- L2826-2829 _public method_ `public string GetContent()` — Return the full available content as a string

#### class `Gauntlet.FileLogger`  
`public class FileLogger`  
_public; L2835-2954_
- desc: Logger to file with interface to get a log reader
- L2837 _private field_ `private CircularLogBuffer _buffer`
- L2838 _private field_ `private string _filepath`
- L2839 _private field_ `private string _commandline`
- L2840 _private field_ `private StreamWriter _writer`
- L2848-2868 _public ctor_ `public FileLogger(string FilePath, string CommandLine, bool bKeepStreamOpen = true)` — Instantiate Logger to file with interface to get a log reader
- L2870-2873 _private* dtor_ `~FileLogger()`
- L2875-2882 _public method_ `public void CloseStream()`
- L2884-2911 _public method_ `public void AppendLine(string Data)`
- L2913-2921 _public method_ `public ILogStreamReader GetReader()`
- L2923-2926 _public method_ `public ILogStreamReader GetBufferReader()`
- L2928-2953 _public method_ `public void CopyFile(string FilePath)`

#### interface `Gauntlet.ILongProcessResult`  
`public interface ILongProcessResult : IProcessResult`  
_public; L2959-2979_
- inherits: `IProcessResult`
- desc: Extend IProcessResult to add log and buffer readers
- L2965 _public* method_ `ILogStreamReader GetLogReader()` — Return an ILogStreamReader using the log file as a source
- L2971 _public* method_ `ILogStreamReader GetLogBufferReader()` — Return an ILogStreamReader using the log buffer as a source
- L2978 _public* method_ `void AppendToOutput(string InData, bool IsStdErr)` — Append string to the log output

#### class `Gauntlet.LongProcessResult`  
`public class LongProcessResult : ILongProcessResult`  
_public; L2986-3296_
- inherits: `ILongProcessResult`
- desc: Represent a process running for a long time. Output is redirected to a circular log buffer unless ERunOptions.NoStdOutRedirect is set in the options. An output filter callback can be set to modify process output.
- L2995 _public delegate_ `public delegate string OutputFilterCallbackType(string Message, bool bIsStdErr)` — Delegate to filter output. If the output is coming from StdErr, bIsStdErr is true. If the return value is null, the line is skipped in the final output.
- L2997 _public property_ `public int ExitCode { get; set; }`
- L2999 _public property_ `public bool bExitCodeSuccess => ...`
- L3001 _private property_ `private Process LocalProcess { get; set; }`
- L3003 _private property_ `private string AppName { get; set; }`
- L3005 _private property_ `private string CommandLine { get; set; }`
- L3007 _private property_ `private FileLogger Logger { get; set; }`
- L3009 _private property_ `private string LocalCachePath { get; set; }`
- L3011 _private property_ `private bool bOutputToConsole { get; set; }`
- L3013 _private field_ `private object ProcSyncObject`
- L3014 _private field_ `private object OutputSyncObject`
- L3016 _private field_ `private AutoResetEvent StdOutCloseHandle = new AutoResetEvent(false)`
- L3017 _private field_ `private AutoResetEvent StdErrCloseHandle = new AutoResetEvent(false)`
- L3019 _private field_ `private OutputFilterCallbackType OutputFilterCallback`
- L3021-3078 _public ctor_ `public LongProcessResult(string Command, string Args, ERunOptions Options, OutputFilterCallbackType OutputCallback = null, string WorkingDir = null, string LocalCache = null)`
- L3080-3087 _private method_ `private void TryCreateLogFile()`
- L3089-3099 _public method_ `public void StdOut(object sender, DataReceivedEventArgs Args)`
- L3101-3111 _public method_ `public void StdErr(object sender, DataReceivedEventArgs Args)`
- L3113-3127 _public method_ `public void AppendToOutput(string InData, bool IsStdErr)`
- L3129 _public property_ `public string Output => ...`
- L3131 _public method_ `public ILogStreamReader GetLogReader()`
- L3133 _public method_ `public ILogStreamReader GetLogBufferReader()`
- L3135-3145 _public method_ `public FileReference WriteOutputToFile(string FilePath)`
- L3147-3169 _public property_ `public bool HasExited { get; }`
- L3171-3174 _public property_ `public Process ProcessObject { get; }`
- L3176-3183 _public method_ `public void DisposeProcess()`
- L3185-3189 _private* dtor_ `~LongProcessResult()`
- L3191-3199 _public method_ `public string GetProcessName()`
- L3201-3233 _public method_ `public void StopProcess(bool KillDescendants = true)`
- L3235-3247 _private method_ `private void Kill(bool KillDescendants = true)`
- L3249-3252 _private method_ `private void ProcessExit(object sender, EventArgs e)`
- L3254-3259 _public method_ `public void OnProcessExited()`
- L3261-3266 _private method_ `private void RegisterProcessExit()`
- L3268-3295 _public method_ `public void WaitForExit()`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Horde/Gauntlet.Horde.cs` (Gauntlet.Automation)


#### class `Gauntlet.Horde`  
`public static class Horde`  
_public; L17-377_
- L20-26 _public property_ `static public bool IsHordeJob { get; }`
- L28-34 _public property_ `static public string? JobId { get; }`
- L36-42 _public property_ `static public string? StepId { get; }`
- L44-50 _public property_ `static public string? StepName { get; }`
- L135 _private property_ `private static string? curStepMessage { get; set; }`
- L136 _private property_ `private static string? curStepSeverity { get; set; }`
- L137 _private property_ `private static string? curStepColor { get; set; }`
- L146-150 _public method_ `public static void UpdateStepMessage(HordeStepMessage InStepMessage)` — Update the step message (short message written in-line in step view) These messages should be generic so we can aggregate multiple instances of it. Good message example "TestTimedOut", or "IslandNotFound", or "LoginFailed" Bad message example "This test timed out after 3 hours", "7 of 8 islands found"
- L161-177 _public method_ `public static void ReportInvalidatingIssue(HordeStepMessage InMessage, string IssueDescription, bool bGenerateSummary = true)` — Labels a test as being invalid, and provides reason why to the summary report, with a concise message to also be shown in step view. This should ONLY be used right before an exception is thrown. If it is being used outside of a currently running test (as in, the test is actively ticking), you want to set bGenerateSummary to true
- L182-188 _public property_ `static public bool UseTestDataV1 { get; }` — Whether to generate test data v1 model when writing test results for Horde
- L209 _private* field_ `static bool bHasGeneratedStepReport = false`
- L210 _private* field_ `static bool bHasGeneratedJobReport = false`
- L212 _public delegate_ `public delegate string SummaryLineDelegate()`
- L218 _public field_ `public static SummaryLineDelegate? OnStepSummary` — Delegate called when the Horde step summary is generated. Returned string is appended as a line to the summary report.
- L225 _public field_ `public static SummaryLineDelegate? OnStepSummaryFinalization` — Delegate called when the Horde step summary is finalized. Returned string is appended as a line to the summary report.
- L231 _public field_ `public static SummaryLineDelegate? OnJobSummary` — Delegate called when the Horde job summary is generated. Return stringis append as a line to the job summary report.
- L233-252 _public method_ `public static void AddJobBuildMetaData(IBuildSource buildSource)`
- L254-259 _public method_ `public static string GenerateArtifactLink(string ArtifactPath)`
- L261-326 _public method_ `public static void GenerateStepSummary()`
- L328-375 _public method_ `public static void GenerateJobSummary()`

#### enum `Gauntlet.Horde.JobStepMessageLevels`  
`public enum JobStepMessageLevels`  
_public; L52-58_
- L54 _public* enumerator_ `None`
- L55 _public* enumerator_ `Info`
- L56 _public* enumerator_ `Warning`
- L57 _public* enumerator_ `Error`

#### class `Gauntlet.Horde.HordeStepMessage`  
`public class HordeStepMessage`  
_public; L60-69_
- L62 _public property_ `public JobStepMessageLevels Severity { get; set; }`
- L63 _public property_ `public string Message { get; set; }`
- L64-68 _public ctor_ `public HordeStepMessage(string InMessage, JobStepMessageLevels InSeverity)`

#### class `Gauntlet.Horde.GauntletHordeStepMessage`  
`public partial class GauntletHordeStepMessage`  
_public; L72-133_
- L74 _public field_ `public static HordeStepMessage TestStepMessage = new HordeStepMessage("TestCategory", JobStepMessageLevels.Error)`
- L77 _public field_ `public static HordeStepMessage CannotAccessBuild = new HordeStepMessage("CannotAccessBuild", JobStepMessageLevels.Error)`
- L78 _public field_ `public static HordeStepMessage NotEnoughDriveSpace = new HordeStepMessage("NotEnoughDriveSpace", JobStepMessageLevels.Error)`
- L79 _public field_ `public static HordeStepMessage InvalidBuildSource = new HordeStepMessage("InvalidBuildSource", JobStepMessageLevels.Error)`
- L80 _public field_ `public static HordeStepMessage InvalidPerfSpec = new HordeStepMessage("InvalidPerfSpec", JobStepMessageLevels.Error)`
- L81 _public field_ `public static HordeStepMessage InstallationFailed = new HordeStepMessage("InstallationFailed", JobStepMessageLevels.Error)`
- L82 _public field_ `public static HordeStepMessage InvalidConfig = new HordeStepMessage("InvalidConfig", JobStepMessageLevels.Error)`
- L83 _public field_ `public static HordeStepMessage NotEnoughDevices = new HordeStepMessage("NotEnoughDevices", JobStepMessageLevels.Error)`
- L84 _public field_ `public static HordeStepMessage BuildNotFound = new HordeStepMessage("BuildNotFound", JobStepMessageLevels.Error)`
- L85 _public field_ `public static HordeStepMessage BuildNotSpecified = new HordeStepMessage("BuildNotSpecified", JobStepMessageLevels.Error)`
- L86 _public field_ `public static HordeStepMessage FailedToStart = new HordeStepMessage("FailedToStart", JobStepMessageLevels.Error)`
- L87 _public field_ `public static HordeStepMessage InvalidBackend = new HordeStepMessage("InvalidBackend", JobStepMessageLevels.Error)`
- L88 _public field_ `public static HordeStepMessage WrongAccountUsed = new HordeStepMessage("WrongAccountUsed", JobStepMessageLevels.Error)`
- L89 _public field_ `public static HordeStepMessage TestCancelled = new HordeStepMessage("TestCancelled", JobStepMessageLevels.Error)`
- L90 _public field_ `public static HordeStepMessage InvalidProject = new HordeStepMessage("InvalidProject", JobStepMessageLevels.Error)`
- L91 _public field_ `public static HordeStepMessage NoVerseFiles = new HordeStepMessage("NoVerseFiles", JobStepMessageLevels.Error)`
- L92 _public field_ `public static HordeStepMessage InvalidValues = new HordeStepMessage("InvalidValues", JobStepMessageLevels.Error)`
- L93 _public field_ `public static HordeStepMessage PermissionsFailure = new HordeStepMessage("PermissionsFailure", JobStepMessageLevels.Error)`
- L94 _public field_ `public static HordeStepMessage InvalidTestData = new HordeStepMessage("InvalidTestData", JobStepMessageLevels.Error)`
- L95 _public field_ `public static HordeStepMessage PushChangesFailure = new HordeStepMessage("PushChangesFailure", JobStepMessageLevels.Error)`
- L96 _public field_ `public static HordeStepMessage CompileError = new HordeStepMessage("CompileError", JobStepMessageLevels.Error)`
- L99 _public field_ `public static HordeStepMessage LoginFailed = new HordeStepMessage("LoginFailed", JobStepMessageLevels.Error)`
- L100 _public field_ `public static HordeStepMessage MatchmakingFailed = new HordeStepMessage("MatchmakingFailed", JobStepMessageLevels.Error)`
- L101 _public field_ `public static HordeStepMessage TestTimeoutExceeded = new HordeStepMessage("TestTimeoutExceeded", JobStepMessageLevels.Error)`
- L102 _public field_ `public static HordeStepMessage HeartbeatTimeout = new HordeStepMessage("HeartbeatTimeout", JobStepMessageLevels.Error)`
- L103 _public field_ `public static HordeStepMessage OverlayException = new HordeStepMessage("OverlayException", JobStepMessageLevels.Error)`
- L104 _public field_ `public static HordeStepMessage TestCasesFailed = new HordeStepMessage("TestCasesFailed", JobStepMessageLevels.Error)`
- L105 _public field_ `public static HordeStepMessage MissingArtifacts = new HordeStepMessage("MissingArtifacts", JobStepMessageLevels.Error)`
- L106 _public field_ `public static HordeStepMessage UnacceptablePerf = new HordeStepMessage("UnacceptablePerf", JobStepMessageLevels.Error)`
- L107 _public field_ `public static HordeStepMessage UnacceptableMem = new HordeStepMessage("UnacceptableMem", JobStepMessageLevels.Error)`
- L108 _public field_ `public static HordeStepMessage HardwareFailure = new HordeStepMessage("HardwareFailure", JobStepMessageLevels.Error)`
- L109 _public field_ `public static HordeStepMessage ServerCrashDetected = new HordeStepMessage("ServerCrashDetected", JobStepMessageLevels.Error)`
- L110 _public field_ `public static HordeStepMessage ClientCrashDetected = new HordeStepMessage("ClientCrashDetected", JobStepMessageLevels.Error)`
- L111 _public field_ `public static HordeStepMessage EditorCrashDetected = new HordeStepMessage("EditorCrashDetected", JobStepMessageLevels.Error)`
- L112 _public field_ `public static HordeStepMessage ServerError = new HordeStepMessage("ServerError", JobStepMessageLevels.Error)`
- L113 _public field_ `public static HordeStepMessage SyncError = new HordeStepMessage("SyncError", JobStepMessageLevels.Error)`
- L114 _public field_ `public static HordeStepMessage ContentError = new HordeStepMessage("ContentError", JobStepMessageLevels.Error)`
- L115 _public field_ `public static HordeStepMessage UploadError = new HordeStepMessage("UploadError", JobStepMessageLevels.Error)`
- L116 _public field_ `public static HordeStepMessage LobbyFailure = new HordeStepMessage("LobbyFailure", JobStepMessageLevels.Error)`
- L119 _public field_ `public static HordeStepMessage TestWarningsDetected = new HordeStepMessage("TestWarningsDetected", JobStepMessageLevels.Warning)`
- L120 _public field_ `public static HordeStepMessage PerfWarningsDetected = new HordeStepMessage("PerfWarningsDetected", JobStepMessageLevels.Warning)`
- L121 _public field_ `public static HordeStepMessage MemWarningsDetected = new HordeStepMessage("MemWarningsDetected", JobStepMessageLevels.Warning)`
- L122 _public field_ `public static HordeStepMessage ReplayGettingStale = new HordeStepMessage("ReplayGettingStale", JobStepMessageLevels.Warning)`
- L123 _public field_ `public static HordeStepMessage ImproperRpcCallDetected = new HordeStepMessage("ImproperRpcCallDetected", JobStepMessageLevels.Warning)`
- L126 _public field_ `public static HordeStepMessage TestSucceeded = new HordeStepMessage("TestSucceeded", JobStepMessageLevels.Info)`
- L127 _public field_ `public static HordeStepMessage TestDataGenerated = new HordeStepMessage("TestDataGenerated", JobStepMessageLevels.Info)`
- L130 _public field_ `public static HordeStepMessage ZeroTestsRun = new HordeStepMessage("ZeroTestsRun", JobStepMessageLevels.Error)`
- L131 _public field_ `public static HordeStepMessage CleanupFailure = new HordeStepMessage("CleanupFailure", JobStepMessageLevels.Error)`

#### class `Gauntlet.Horde.JobStepReport`  
`public class JobStepReport`  
_public; L190-199_
- L192 _public property_ `public string scope { get; }`
- L193 _public property_ `public string? name { get; set; }`
- L194 _public property_ `public string placement { get; }`
- L195 _public property_ `public string? fileName { get; set; }`
- L196 _public property_ `public string? message { get; set; }`
- L197 _public property_ `public string? severity { get; set; }`
- L198 _public property_ `public string? color { get; set; }`

#### class `Gauntlet.Horde.JobSummaryReport`  
`public class JobSummaryReport`  
_public; L201-207_
- L203 _public property_ `public string scope { get; }`
- L204 _public property_ `public string? name { get; set; }`
- L205 _public property_ `public string placement { get; }`
- L206 _public property_ `public string? fileName { get; set; }`

### `Source/Programs/AutomationTool/Gauntlet/Framework/RpcFramework/Gauntlet.AsyncTestNode.cs` (Gauntlet.Automation)


#### class `Gauntlet.AsyncEpicGameTestNode`  
`public abstract class AsyncEpicGameTestNode<TConfigClass>(UnrealTestContext InContext) : EpicGameTestNode<TConfigClass>(InContext) where TConfigClass : EpicGameTestConfig, new()`  
_public; L14-133_
- desc: A Test Node which simplifies writing asynchronous tests
- L17 _public property_ `public RpcTargetRegistry TargetRegistry { get; set; }`
- L18 _public property_ `public CancellationTokenSource SessionCancelTokenSource { get; set; }`
- L20 _private field_ `private Task<TestResult>? TestTask`
- L21 _private field_ `private AsyncSessionState CurrentState = AsyncSessionState.Init`
- L34-69 _public method_ `public override void TickTest()` — Subclasses should define their logic by overriding ExecuteTestAsync
- L72-76 _public method_ `public override void StopTest(StopReason InReason)` — (inheritdoc)
- L78-84 _private method_ `private void InitializeSession()`
- L89-97 _protected method_ `protected void ConfigureCancellation()` — Sets conditions for canceling the test session
- L100-108 _public method_ `public override void CleanupTest()` — (inheritdoc)
- L115 _protected method_ `protected abstract Task<TestResult> ExecuteTestAsync(CancellationToken CancelToken)` — Async logic for this test session. Tasks will be run on the default thread pool.
- L120-123 _public method_ `public virtual void BeforeTest()` — Additional setup steps run immediately before ExecuteTestAsync
- L129-132 _public method_ `public virtual void AfterTest(ref readonly TestResult FinishedTestResult)` — Additional teardown steps to run immediately after ExecuteTestAsync

#### enum `Gauntlet.AsyncEpicGameTestNode.AsyncSessionState`  
`private enum AsyncSessionState`  
_private; L22-29_
- L24 _public* enumerator_ `Init`
- L25 _public* enumerator_ `BeforeSession`
- L26 _public* enumerator_ `SessionStart`
- L27 _public* enumerator_ `SessionExecuting`
- L28 _public* enumerator_ `AfterSession`

### `Source/Programs/AutomationTool/Gauntlet/Framework/RpcFramework/Gauntlet.GauntletHttpClient.cs` (Gauntlet.Automation)


#### class `Gauntlet.GauntletHttpClient`  
`public class GauntletHttpClient : HttpClient`  
_public; L8-47_
- inherits: `HttpClient`
- L10-12 _public ctor_ `public GauntletHttpClient() : this(new HttpClientHandler())`
- L14-16 _public ctor_ `public GauntletHttpClient(HttpMessageHandler Handler) : base(Handler, true)`
- L18-22 _public method_ `public async Task<HttpResponseMessage> GetRequestAsync(string Route)`
- L24-29 _public method_ `public async Task<HttpResponseMessage> SendRequestAsync(HttpRequestMessage Msg)`
- L31-41 _private method_ `private async Task LogOutgoingRequestPayload(HttpRequestMessage Msg)`
- L43-46 _public method_ `public void LogOutgoingRequestURI(string Route)`

#### class `Gauntlet.GauntletHttpResponse`  
`public class GauntletHttpResponse`  
_public; L52-56_
- desc: Generic HTTP response class that
- L54 _public property_ `public bool Success { get; set; }`
- L55 _public property_ `public string Reason { get; set; }`

### `Source/Programs/AutomationTool/Gauntlet/Framework/RpcFramework/Gauntlet.RpcExecutor.cs` (Gauntlet.Automation)


#### class `Gauntlet.RpcDefinition`  
`public class RpcDefinition`  
_public; L28-35_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Contains all relevant information for a registered RPC route on a target
- L30 _public field_ `public string Name`
- L31 _public field_ `public string Route`
- L32 _public field_ `public string Verb`
- L33 _public field_ `public string InputContentType`
- L34 _public field_ `public List<RpcArgumentDesc> Args`

#### class `Gauntlet.RpcLedgerEntry`  
`public class RpcLedgerEntry`  
_public; L39-44_
- desc: Definition of a ledger entry when looking at our request history
- L41 _public field_ `public string RpcName`
- L42 _public field_ `public string RequestTimestamp`
- L43 _public field_ `public string RequestBody`

#### class `Gauntlet.RpcArgumentDesc`  
`public class RpcArgumentDesc`  
_public; L50-56_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Definition of an individual argument expected by an RPC.
- L52 _public field_ `public string Name`
- L53 _public field_ `public string Type`
- L54 _public field_ `public string Desc`
- L55 _public field_ `public bool Optional`

#### class `Gauntlet.ResponseData`  
`public class ResponseData`  
_public; L60-69_
- desc: Full response body and code.
- L62 _public field_ `public string ResponseBody`
- L63 _public field_ `public int ResponseCode`
- L64-68 _public ctor_ `public ResponseData()`

#### class `Gauntlet.RouteMapping`  
`public class RouteMapping`  
_public; L74-104_
- desc: Description for a route mapping that we are listening on from Gauntlet.
- L76 _public field_ `public string Path`
- L77 _public field_ `public string Verb`
- L78-82 _public ctor_ `public RouteMapping(string InPath, string InVerb = "post")`
- L84-87 _public method_ `public override bool Equals(object TargetObject)`
- L89-92 _public method_ `public bool Equals(RouteMapping InMap)`
- L94-98 _public method_ `public override int GetHashCode()`
- L99-102 _public method_ `public override string ToString()`

#### class `Gauntlet.RpcExecutor`  
`public partial class RpcExecutor`  
_public; L109-1096_
- desc: Singleton responsible for all of the communication from Gauntlet to the targets.
- L111 _private field_ `private static RpcExecutor ExecutorInstance = null`
- L112 _private field_ `private static readonly object ThreadLock = new object()`
- L113 _public field_ `public static GauntletHttpClient ExecutorClient = new GauntletHttpClient()`
- L115 _protected field_ `protected HttpListener RequestListener`
- L116 _protected field_ `protected Thread HttpListenThread`
- L117 _protected field_ `protected static int GauntletRPCListenPort = 23232`
- L118 _protected field_ `protected RpcTargetRegistry ActiveTargetRegistry = null`
- L120-135 _public property_ `public static RpcExecutor Instance { get; }`
- L137-139 _private ctor_ `private RpcExecutor()`
- L140-148 _private* dtor_ `~RpcExecutor()`
- L154-161 _public method_ `public void SetRpcTargetRegistry(RpcTargetRegistry CurrentRegistry, [CallerFilePath] string Caller = "", [CallerLineNumber] int Line = 0)` — Enables a message queue for each target application in the current test, reducing async lock contention
- L163-190 _public method_ `public static string GetListenAddressAndPort()`
- L192 _public field_ `public ConcurrentQueue<GauntletIncomingRpcMessage> IncomingMessageQueue = []`
- L193 _protected field_ `protected ConcurrentDictionary<GauntletRpcDelegateRegistryFilter, GauntletIncomingRpcMessageDelegate> MessageDelegates = ...`
- L193 _protected field_ `protected ConcurrentDictionary< MessageDelegates = []`
- L194 _protected field_ `protected ConcurrentDictionary<RouteMapping, GauntletHttpRouteDelegate> HttpRoutes = ...`
- L194 _protected field_ `protected ConcurrentDictionary< HttpRoutes = []`
- L196 _protected field_ `protected object ReceivedTerminationCallLock = new ()`
- L197 _private field_ `private bool _bHasReceivedTerminationCall = false`
- L198-214 _public property_ `public bool bHasReceivedTerminationCall { get; set; }`
- L215-241 _public method_ `public void ListenLoopThread()`
- L244-277 _public method_ `public virtual void HandleIncomingMessage(string MessageBody, ResponseData CallResponse)`
- L279-378 _public method_ `public void ReceiveListenRequest(IAsyncResult ListenResult)`
- L379-398 _public method_ `public List<GauntletIncomingRpcMessage> GetNewMessages(bool bClearMessageQueue = true)`
- L404-409 _public method_ `public List<string> GetAllMessageStrings()` — Returns the string representations of all messages across all queues, without modifying the queues.
- L411-438 _private method_ `private void PopulateNewMessagesFromQueue(ConcurrentQueue<GauntletIncomingRpcMessage> Queue, List<GauntletIncomingRpcMessage> Messages, bool bClearMessageQueue)`
- L440-443 _private method_ `private void PopulateNewMessagesFromCentralQueue(List<GauntletIncomingRpcMessage> Messages, bool bClearMessageQueue = true)`
- L445-454 _private method_ `private void PopulateNewMessagesFromActiveTargetQueues(List<GauntletIncomingRpcMessage> Messages, bool bClearMessageQueue = true)`
- L459-465 _private method_ `private void SafeClearMessages(ConcurrentQueue<GauntletIncomingRpcMessage> Queue, int MessagesToClear)` — Dequeues a number messages, allowing new messages to be concurrently enqueued
- L467-477 _public method_ `public void ClearIncomingMessageQueue()`
- L479-482 _public method_ `public void ClearMessageDelegates()`
- L491-519 _public method_ `public int GetMessageFilterMatches(GauntletIncomingRpcMessage NewMessage, List<GauntletRpcDelegateRegistryFilter> MessageFilters)` — Checks a single message for matches against a list of message filters to see if it matches any of them.
- L529-561 _private method_ `private int ConsumeIncomingMessagesFromQueue(ConcurrentQueue<GauntletIncomingRpcMessage> MessageQueue, List<GauntletRpcDelegateRegistryFilter> MessageFilters, bool bSaveUnmatchedMessages)` — Process a message queue and return how many messages match a filter, optionally retaining any unmatched messages. GauntletRpcDelegateRegistryFilter
- L570-573 _public method_ `public int ConsumeIncomingMessagesFromTarget(RpcTarget Target, List<GauntletRpcDelegateRegistryFilter> MessageFilters, bool bSaveUnmatchedMessages)` — Process an RpcTarget's queue and return how many messages match a filter, optionally retaining any unmatched messages. GauntletRpcDelegateRegistryFilter
- L581-593 _public method_ `public int ConsumeIncomingMessagesFromAllQueues(List<GauntletRpcDelegateRegistryFilter> MessageFilters, bool bSaveUnmatchedMessages)` — Process all active queues and return how many messages match a filter, optionally retaining any unmatched messages. GauntletRpcDelegateRegistryFilter
- L606-612 _public method_ `public int CheckIncomingMessages(List<GauntletRpcDelegateRegistryFilter> MessageFilters, bool bSaveUnmatchedMessages)` — Checks the IncomingMessages queue for messages matching a list of GauntletRpcDelegateRegistryFilters, which represent all of the messages that we are looking for.
- L626-629 _public method_ `public int CheckIncomingMessages(GauntletRpcDelegateRegistryFilter MessageFilter, bool bSaveUnmatchedMessages)` — attrs: `[Obsolete($"Instead use {nameof(ConsumeIncomingMessagesFromTarget)} on the target message queue(s)", false)]` — Checks the IncomingMessages queue for messages matching a GauntletRpcDelegateRegistryFilter, which represents the message(s) that we are looking for.
- L643-647 _public method_ `public int CheckIncomingMessages(string TargetSenderId, string TargetMessageCategory, string TargetMessagePayload, bool bSaveUnmatchedMessages)` — attrs: `[Obsolete($"Instead use {nameof(ConsumeIncomingMessagesFromTarget)} on the target message queue(s)", false)]` — Checks the IncomingMessages queue messages matching the sender ID, category and payload contents.
- L659-670 _public method_ `public int CheckIncomingMessages(List<RpcTarget> InTargets, string TargetMessageCategory, string TargetMessagePayload, bool bSaveUnmatchedMessages)` — Checks the IncomingMessages queue for a message matching a category and payload contents for a list of RPC Targets
- L683-687 _public method_ `public int CheckIncomingMessages(RpcTarget InTarget, string TargetMessageCategory, string TargetMessagePayload, bool bSaveUnmatchedMessages)` — attrs: `[Obsolete($"Instead use {nameof(ConsumeIncomingMessagesFromTarget)} on the target message queue(s)", false)]` — Checks the IncomingMessages queue for a message matching a category and payload contents for a single RPC Target
- L761 _public delegate_ `public delegate void GauntletIncomingRpcMessageDelegate(GauntletIncomingRpcMessage Message)` — Delegate type for incoming messages from Unreal processes.
- L771-787 _public method_ `public virtual void RegisterMessageDelegate(GauntletIncomingRpcMessageDelegate FunctionToRun, string SenderFilter = "", string CategoryFilter = "", string PayloadFilter = "", bool bDeregisterAfterTrigger = false)` — Delegate registry function. Set any fields that don't matter to the filter to "" or String.Empty, and your delegate will fire off any time a message comes in that matches all criteria of your filter. It does not fuzzy match.
- L797-820 _public method_ `public virtual bool DeregisterMessageDelegate(GauntletIncomingRpcMessageDelegate FunctionToRun, string SenderFilter = "", string CategoryFilter = "", string PayloadFilter = "")` — Delegate deregistry function. We will remove the delegate only if it matches everything passed in exactly.
- L823-837 _protected method_ `protected virtual void FireRelevantMessageDelegates(GauntletIncomingRpcMessage NewMessage)`
- L839-857 _public method_ `public void StartListenThread()`
- L859-867 _public method_ `public void ShutdownListenThread()`
- L872 _public delegate_ `public delegate void GauntletHttpRouteDelegate(string MessageBody, ResponseData CallResponse)` — Delegate type for handling messages on a http route.
- L874-896 _public method_ `public void RegisterHttpRoute(RouteMapping Path, GauntletHttpRouteDelegate RouteDelegate, bool bOverrideIfExists = false)`
- L898-908 _public method_ `public void DeregisterHttpRoute(RouteMapping Path)`
- L910-1029 _public method_ `public static HttpResponseMessage CallRpc(RpcTarget InTarget, string RpcName, int Timeout = 5000, Dictionary<string, object> InArgs = null, string InContentType = "application/json")`
- L1031-1095 _public method_ `public static HttpResponseMessage CallRPCWithUrlParams(RpcTarget InTarget, string RpcName, Dictionary<string, object> InArgs, int Timeout = 5000, string InContentType = "application/json")`

#### class `Gauntlet.RpcExecutor.GauntletRpcDelegateRegistryFilter`  
`public class GauntletRpcDelegateRegistryFilter`  
_public; L693-707_
- desc: Basic filter class that allows users to filter what incoming messages they would like to fire their delegate functions on. Null values act as wild cards.
- L695 _public field_ `public string DesiredSenderId`
- L696 _public field_ `public string DesiredCategory`
- L697 _public field_ `public string DesiredPayload`
- L698 _public field_ `public bool bDeregisterAfterFirstTrigger`
- L699-705 _public ctor_ `public GauntletRpcDelegateRegistryFilter(string InSender, string InCategory, string InPayload, bool bInDeregisterAfterFirstTrigger)`

#### class `Gauntlet.RpcExecutor.GauntletIncomingRpcMessage`  
`public class GauntletIncomingRpcMessage`  
_public; L712-756_
- desc: Basic class for handling and deserializing incoming messages from Unreal processes
- L714 _public field_ `public string SenderId`
- L715 _public field_ `public string Category`
- L716 _public field_ `public string Payload`
- L718-724 _public ctor_ `public GauntletIncomingRpcMessage()`
- L726-731 _public ctor_ `public GauntletIncomingRpcMessage(GauntletIncomingRpcMessage CopyTarget)`
- L733-738 _public ctor_ `public GauntletIncomingRpcMessage(string InSender, string InCategory, string InPayload)`
- L740-755 _public method_ `public bool MatchesMessageFilter(GauntletRpcDelegateRegistryFilter MessageFilter)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/RpcFramework/Gauntlet.RpcExecutorAsync.cs` (Gauntlet.Automation)


#### class `Gauntlet.RpcExecutor`  
`public partial class RpcExecutor`  
_public; L15-145_
- L38-78 _public method_ `public static Task<HttpResponseMessage> CallRpcAsync( RpcTarget InTarget, string InRpcName, IReadOnlyDictionary<string, object> InArgs, CancellationToken InCancellationToken = default)` — Asynchronously send an RPC to the target.
- L80-122 _private method_ `private static void ValidateRpcArguments(RpcDefinition InRpcDefinition, IReadOnlyDictionary<string, object> InArgs)`
- L124 _private field_ `private static readonly IReadOnlyDictionary<string, Type> RpcArgumentTypes = ...`
- L124 _private field_ `private static readonly IReadOnlyDictionary< RpcArgumentTypes = new Dictionary<string, Type> { { "bool", typeof(bool) }, { "int", typeof(int) }, { "float", typeof(float) }, { "double", typeof(double) }, }`
- L132-137 _private method_ `private static bool TryGetRpcDefinition(RpcTarget InTarget, string InName, [NotNullWhen(true)] out RpcDefinition? OutDefinition)`
- L139-144 _private method_ `private static bool TryGetRpcUrl(RpcTarget InTarget, string InName, [NotNullWhen(true)] out string? OutUrl)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/RpcFramework/Gauntlet.RpcLibrary.cs` (Gauntlet.Automation)


#### class `Gauntlet.RpcLibrary`  
`public class RpcLibrary`  
_public; L24-712_
- desc: Helper library for all RPCs not specific to Fortnite. This will eventually be moved to the engine side of gauntlet once we feel the RPC system is ready for prime time.
- L33-48 _public method_ `public static bool ValidateTarget(RpcTarget InTarget)`
- L55-70 _public method_ `public static bool ValidateResponse(RpcTarget InTarget, HttpResponseMessage InResponse)` — Method to check the returned HttpResponseMessage to ensure it is valid.
- L80-102 _public method_ `public static T ValidateResponse<T>(RpcTarget InTarget, HttpResponseMessage InResponse, bool bExceptionOnFailure = false) where T : FortBaseRpcHttpResponse` — Generic way to validate and deserialize an HttpResponseMessage into any type that extends FortBaseRpcHttpResponse.
- L104-127 _public method_ `public static string GetResponseAsString(HttpResponseMessage InResponse, bool bExceptionIfEmpty = false)`
- L136-161 _public method_ `public static T GetResponseAsObject<T>(HttpResponseMessage InResponse)` — Generic way to deserialize a HttpResponseMessage to your desired type. Handles null exceptions.
- L163-205 _public method_ `public static SimpleResponse GetSimpleResponse(HttpResponseMessage InResponse, bool bExceptionIfEmpty = false)`
- L207 _public delegate_ `public delegate void OnBeforeTimeoutDelegate()`
- L209-254 _public method_ `public static bool DoWhile(string FuncName, Func<bool> RpcCall, int DelayInMilliseconds = 5 * 1000, int TimeoutInMilliseconds = 60 * 1000, bool bSuppressExceptions = false, bool bSuppressTimeoutException = false, OnBeforeTimeoutDelegate OnBeforeTimeout = null)`
- L256-260 _public method_ `public static bool DoUntil(string FuncName, Func<bool> RpcCall, int DelayInMilliseconds = 5 * 1000, int TimeoutInMilliseconds = 60 * 1000, bool bSuppressExceptions = false)`
- L262-283 _public method_ `public static bool ExecuteRpcCheckSuccess(RpcTarget InTarget, string RpcName, Dictionary<string, object> Args = null)`
- L285-295 _public method_ `public static bool RunCheatCommand(RpcTarget InTarget, string CheatString)`
- L298-316 _public method_ `public static List<RpcLedgerEntry> GetRequestHistory(RpcTarget InTarget)`
- L318-330 _public method_ `public static bool LogMessageInTarget(RpcTarget InTarget, string Message)`
- L332-352 _public method_ `public static bool RunAndWaitForCheatCommand(RpcTarget InTarget, string CheatString)`
- L354-362 _public method_ `public static bool ExitClient(RpcTarget InTarget)`
- L368-416 _public method_ `public static bool QuitEditor(RpcTarget InTarget)` — Works with core editor and UEFN
- L418-451 _public method_ `public static bool CheckFEngineLoopInitComplete(RpcTarget InTarget)`
- L459 _private field_ `private static JsonSerializerOptions DefaultSerializationOptions = new() { PropertyNameCaseInsensitive = true }`
- L466-487 _public method_ `public static ScriptedBehaviorStatusResponse GetScriptedBehaviorStatus(RpcTarget InTarget)` — Gets the status of scripted behavior currently running on the pawn
- L494-506 _public method_ `public static bool IsPlayerCosmeticSet(RpcTarget InTarget)` — Checks if the player cosmetic loadout has been set (cosmetic loadout change is done)
- L517-522 _public method_ `public static void WaitForIncomingTargetMessage(RpcTarget InTarget, string MessageCategory, string MessageContents, int TimeoutInSeconds = 300, int TimeBetweenRetriesInSeconds = 60)` — Waits for a message to be received from a RPC Target (Unreal process). This is a blocking method.
- L533-578 _public method_ `public static void WaitForIncomingTargetMessage(List<RpcTarget> InTargets, string MessageCategory, string MessageContents, int TimeoutInSeconds = 300, int TimeBetweenRetriesInSeconds = 60)` — Waits for the same message to be received from multiple RPC Targets (Unreal processes). Will wait until all messages for all processes have been received. This is a blocking method.
- L588-637 _public method_ `public static void PollAllTargetsForReady(List<RpcTarget> InTargets, int TimeoutInSeconds = 300, int TimeBetweenRetriesInSeconds = 60)` — Polls all RPC Targets to see if they are ready. Specifically for platforms that cannot send messages to Gauntlet.
- L639-646 _public method_ `public static void WaitForAllTargetsToReportReady(List<RpcTarget> InTargets, int TimeoutInSeconds = 1200, int TimeBetweenRetriesInSeconds = 60)`
- L655-710 _public method_ `public static void WaitForAllTargetsToGetEndpoints(List<RpcTarget> InTargets, int TimeoutInSeconds = 300, int TimeBetweenRetriesInSeconds = 60)` — Blocking method that polls all targets for endpoints with configurable retry intervals and timeout.

#### class `Gauntlet.RpcLibrary.SimpleResponse`  
`public class SimpleResponse`  
_public; L26-31_
- L28 _public field_ `public bool Succeeded`
- L29 _public field_ `public string Value`
- L30 _public field_ `public bool Fatal`

#### struct `Gauntlet.RpcLibrary.ScriptedBehaviorStatusResponse`  
`public struct ScriptedBehaviorStatusResponse`  
_public; L453-457_
- L455 _public property_ `public bool IsRunning { get; set; }`
- L456 _public property_ `public string BehaviorName { get; set; }`

#### class `Gauntlet.RpcLibraryExtensions`  
`public static class RpcLibraryExtensions`  
_public; L714-812_
- L718-728 _public method_ `public static bool AddOptional<T>(this Dictionary<string, object> InArgs, string InKey, [NotNullWhen(true)] T? InValue)`
- L733-736 _public method_ `public static bool IsRpcAvailable(this RpcTarget RpcTarget, string RPCName)`
- L738-756 _public method_ `public static bool ChangeCVarValue(this RpcTarget RpcTarget, string CVar, string NewCVarValue)`
- L758-771 _public method_ `public static bool EnableExposureCapture(this RpcTarget RpcTarget)`
- L773-786 _public method_ `public static bool AutomationControllerClearReports(this RpcTarget InTarget)`
- L788-811 _public method_ `public static bool AutomationControllerSummarizeReports(this RpcTarget InTarget, out Dictionary<string, string> OutResponse)`

#### class `Gauntlet.FortBaseRpcHttpResponse`  
`public class FortBaseRpcHttpResponse`  
_public; L819-823_
- desc: Common base RPC HTTP response class with minimal information that can be inherited from for more complex responses. Helper macros in UE are in FortBaseExternalRpcHttpResponse.h
- L821 _public field_ `public bool WasSuccessful = false`
- L822 _public field_ `public string Message = string.Empty`

#### class `Gauntlet.BaseRpcResponse`  
`public class BaseRpcResponse : SimpleResponse`  
_public; L825-829_
- inherits: `SimpleResponse`
- L827 _public property_ `public HttpResponseMessage HttpResponse { get; set; }`
- L828 _public property_ `public string RawContent { get; set; }`

#### class `Gauntlet.BaseRpcLibrary`  
`public class BaseRpcLibrary`  
_public; L835-931_
- desc: Simple base class for building RPC libraries.
- L837 _private* const_ `const string REGISTRATION_FINISHED = "RegistrationFinished"`
- L842-871 _public method_ `public BaseRpcResponse RunRpc(RpcTarget InTarget, string InRpcName, Dictionary<string, object> InRequestArgs, int InTimeout = 5000, bool InSilenceErrors = false)` — Runs a RPC for a given target.
- L873-888 _private method_ `private void ValidateRpcTarget(RpcTarget Target)`
- L893-896 _public method_ `public BaseRpcResponse RegistrationFinished(RpcTarget InTarget)` — Run the default "RegistrationFinished" RPC that checks if registration has finished.
- L898-919 _public method_ `public JsonObject GetResponseValueAsJson(SimpleResponse InResponse)`
- L921-930 _public method_ `public bool GetResponseBoolFieldValue(SimpleResponse InResponse, string InBoolFieldName)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/RpcFramework/Gauntlet.RpcTargetRegistry.cs` (Gauntlet.Automation)


#### class `Gauntlet.RpcTarget`  
`public class RpcTarget`  
_public; L21-176_
- desc: Contains all information relevant to RPC Targets (Unreal Processes)
- L23 _public field_ `public string IpAddress`
- L24 _public field_ `public int Port`
- L25 _public field_ `public UnrealTargetRole TargetType`
- L26 _public field_ `public string TargetName`
- L27 _public field_ `public List<RpcDefinition> AvailableRPCs`
- L31 _public field_ `public bool HasSentMessage = false` — If this is true, we know the target is capable of sending messages to us and has available RPCs and we no longer need to manually poll those processes for messages.
- L38 _public property_ `public bool HasValidIpAddress => ...` — Returns true if a valid numeric IP address has been set, a valid IP has been received from the game via /updateip, or the address is localhost (which is a valid local target on Win64 even without a /updateip update). Returns false if the address is still an unresolved hostname or placeholder.
- L40 _public field_ `public bool IsDeferStart = false`
- L41 _protected field_ `protected bool bIsInvalidated = false`
- L42 _public field_ `public ConcurrentQueue<GauntletIncomingRpcMessage> IncomingMessageQueue = new ()`
- L44-51 _public ctor_ `public RpcTarget(string InIpAddress, int InPort, string InName, UnrealTargetRole InType = UnrealTargetRole.Client)`
- L53-63 _public method_ `public RpcDefinition GetRpc(string RpcName)`
- L65-73 _public method_ `public string CreateRpcUrl(string RpcName)`
- L75-117 _public method_ `public bool UpdateAvailableRpcs()`
- L121-124 _public method_ `public string LogInfo(string Format, params object[] Args)`
- L126-129 _public method_ `public string LogWarning(string Format, params object[] Args)`
- L131-134 _public method_ `public string LogError(string Format, params object[] Args)`
- L135-138 _public method_ `public string LogVerbose(string Format, params object[] Args)`
- L140-165 _private method_ `private string LogMessage(Microsoft.Extensions.Logging.LogLevel LogLevel, string Format, params object[] Args)`
- L167-170 _public method_ `public void SetIsInvalidated(bool InIsInvalidated = true)`
- L172-175 _public method_ `public bool IsInvalidated()`

#### class `Gauntlet.RpcTargetRegistry`  
`public class RpcTargetRegistry : IDisposable`  
_public; L178-682_
- inherits: `IDisposable`
- L184 _public property_ `public RpcTarget EditorTarget { get; set; }` — Quick accessor for the Editor Process RPC Target(if it is used)
- L188 _public property_ `public RpcTarget ServerTarget { get; set; }` — Quick accessor for the Server Process RPC Target(if it is used)
- L192 _public property_ `public RpcTarget ClientTarget { get; set; }` — Quick accessor for the Client Process RPC Target(if it is used). *Note* If multiple clients are in use, this will point to the first one registered.
- L201 _private field_ `private int CurrentClientRpcTargetIndex = 0` — When creating multiple RPC targets for each process role, these indexes are used to keep track of how many have been configured. This value is appended to the SenderId and increments the port so each process has a unique name and port.
- L202 _private field_ `private int CurrentServerRpcTargetIndex = 0`
- L203 _private field_ `private int CurrentEditorRpcTargetIndex = 0`
- L210 _private field_ `private string BaseEditorRpcTargetName = "EditorRpcTarget_"` — Base value used to build the SenderId of a RPC Target.
- L214 _private field_ `private string BaseServerRpcTargetName = "ServerRpcTarget_"` — Unique ID used by the Server to send or identify receipt of RPC's
- L218 _private field_ `private string BaseClientRpcTargetName = "ClientRpcTarget_"` — Unique ID used by the Client to send or identify receipt of RPC's
- L223 _private field_ `private string BaseRpcTargetUri = "localhost"` — Desired default URI. For tests running on the same machine, can be set to the same value.
- L228 _private field_ `private string RpcUpdateMessage = "RpcListUpdated"` — Message sent by an RPC enabled process
- L234 _private field_ `private int BaseClientRpcTargetListeningPort = 12321` — Base listening port for RPC calls to clients. Recommend to use ports be in the 12000 range.
- L239 _private field_ `private int BaseEditorRpcTargetListeningPort = 11321` — Base listening port for RPC calls to the editor. Recommend to use ports be in the 11000 range.
- L244 _private field_ `private int BaseServerRpcTargetListeningPort = 13321` — Base listening port for RPC calls to servers. Recommend to use ports be in the 13000 range.
- L251 _private field_ `private readonly ConcurrentDictionary<UnrealTestRole, RpcTarget> RoleTargets = ...` — Roles which have a RpcTarget registered, only one target should register for a single role
- L251 _private field_ `private readonly ConcurrentDictionary< RoleTargets = new()` — Roles which have a RpcTarget registered, only one target should register for a single role
- L256 _public field_ `public readonly ConcurrentDictionary<string, RpcTarget> RpcTargets = ...` — All registered RPC Targets stored here, in a thread-safe container.
- L256 _public field_ `public readonly ConcurrentDictionary< RpcTargets = new()` — All registered RPC Targets stored here, in a thread-safe container.
- L259-263 _public ctor_ `public RpcTargetRegistry()`
- L265-268 _private* dtor_ `~RpcTargetRegistry()`
- L270-273 _public method_ `public void AddNewTarget(string InName, string IpAddress = "localhost", int Port = 12321, UnrealTargetRole InType = UnrealTargetRole.Client)`
- L275-282 _public method_ `public void AddNewTarget(RpcTarget InTarget)`
- L284-294 _public method_ `public RpcTarget GetTarget(string InIpAddress, int InPort)`
- L296-304 _public method_ `public RpcTarget GetTarget(string InTargetName)`
- L306-313 _public method_ `public void ReceivedRpcListUpdateMessage(RpcExecutor.GauntletIncomingRpcMessage InMessage)`
- L315-324 _public method_ `public void UpdateAvailableRpcForAllTargets()`
- L326-329 _public method_ `public List<RpcTarget> GetAllTargetsOfType(UnrealTargetRole InTargetType)`
- L331-334 _public method_ `public List<RpcTarget> GetAllClients()`
- L336-339 _public method_ `public List<RpcTarget> GetAllServers()`
- L341-377 _public method_ `public virtual void UpdateTargetIp(string MessageBody, ResponseData CallResponse)`
- L384-429 _private method_ `private RpcTarget GetNextAvailableRpcTarget(UnrealTargetRole Role)` — Creates a Client RpcTarget with a guaranteed unique port and name. Post-Increments the target index.
- L434 _private method_ `private bool InitialTargetRoleIsSet(UnrealTargetRole TargetRoleType)`
- L450-476 _private method_ `private void CacheFirstRpcTargetByType(string RpcTargetName, UnrealTargetRole TargetType)` — Caches the first retrieved Client, Editor or Server to a class variables for simplified access.
- L486-550 _public method_ `public void EnableRpcForRole(UnrealTestRole TestRole, int PortOverride = 0, string UriOverride = "")` — This is a command config helper to quickly add the correct command line parameters to Enable RPC's for the desired role and register the RpcTarget with the RpcTargetRegistry, if not already registered.
- L559-584 _public method_ `public void UpdateIPsForRemoteAndNonDesktopTargets(UnrealSession UnrealApp, Action<string, object[]> ActionReportInterrupt)` — Replace the current IP address values with the values obtained during devices reservation. IP addresses are replaced for all remote devices, as well as for local non-desktop devices.
- L593-656 _private method_ `private string ResolveProcessUri(UnrealTestRole TestRole)` — This logic is similar to determining if -multihome should be used so being on VPN doesn't cause IP's to conflict.
- L659-676 _private method_ `private void ReleaseUnmanagedResources()`
- L678-681 _public method_ `public void Dispose()`

### `Source/Programs/AutomationTool/Gauntlet/Framework/RpcFramework/Gauntlet.RpcTimedSections.cs` (Gauntlet.Automation)


#### class `Gauntlet.RpcTimedSections`  
`public class RpcTimedSections`  
_public; L23-303_
- desc: This component collects information about the execution of a given code block between calls to the StartSection and FinishSection methods. It collects information about the code block's run duration, depth, and start and finish times relative to the test case's stopwatch.
- L25 _public property_ `public ConcurrentStack<TimedSection> ActiveSections { get; }`
- L26 _private property_ `private ConcurrentDictionary<int, ExecutedSectionData> FinishedSections { get; }`
- L34 _public property_ `public Stopwatch? ExecutionStopwatch { get; set; }` — Timer that is running during the whole test. May be started explicitly at the required place by call Stopwatch.StartNew(). Automatically starts when the StartSection method is first called if it has not been started explicitly before. Based on this timer Start and End Offsets are calculated.
- L36 _private field_ `private PhaseQueue? Phases`
- L37 _private field_ `private RpcTargetRegistry TargetRegistry`
- L45-49 _public ctor_ `public RpcTimedSections(RpcTargetRegistry TargetRegistry, PhaseQueue? Phases = null)` — The component can operate in two modes: with automatic Phase creation for each Section and without Phase creation.By default, Phases are not created.
- L109-146 _public method_ `public void StartSection(string Name)` — The beginning of the code block for which information needs to be collected. Blocks can be nested
- L152-162 _public method_ `public TimedSection GetCurrentActiveSection()` — Returns the currently active section, or an empty section if none are active
- L167-209 _public method_ `public void FinishSection()` — The finish of the code block for which information needs to be collected
- L215-223 _public method_ `public void LogAllInfo(string Message)` — Log the required message to the logs of all targets and the console
- L231-269 _public method_ `public string GetFormattedSummary()` — Returns information about Finished Sections with their Depth and Duration, or about Active Sections if any section was not completed in formatted and readable view. Can be used as part of test run report
- L276-302 _public method_ `public IList<object> GetSectionsData()` — Returns all gathered information about finished sections. The code between the stopwatch start point and the first section start is considered a "Boot" section.

#### class `Gauntlet.RpcTimedSections.TimedSection`  
`public class TimedSection`  
_public; L55-64_
- desc: Represents a Section that is currently running. When the Section completes its work, the data is transferred to the ExecutedSectionData object in accordance with the SectionIndex.
- L57 _public property_ `public Stopwatch? Watch { get; set; }`
- L58 _public property_ `public string? SectionName { get; set; }`
- L63 _public property_ `public int SectionIndex { get; set; }` — Section ordinal number

#### class `Gauntlet.RpcTimedSections.ExecutedSectionData`  
`public class ExecutedSectionData : IPhaseDataHandler`  
_public; L70-103_
- inherits: `IPhaseDataHandler`
- desc: Data container that contain a full set of data about Section. It is mainly filled in at the end of the Section's work. Also used to automatically add test date to the report.
- L72 _public property_ `public string? SectionName { get; set; }`
- L73 _public property_ `public double DurationInSeconds { get; set; }`
- L78 _public property_ `public double StartOffsetSec { get; set; }` — Section start time relative to test stopwatch
- L83 _public property_ `public double EndOffsetSec { get; set; }` — Section end time relative to test stopwatch
- L88 _public property_ `public int Depth { get; set; }` — Section Nesting. Root level is 0.
- L94-102 _public method_ `public void OnAddToReport(TestPhase ReportedPhase)` — Called when test phase is added to report

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.CSVParser.cs` (Gauntlet.Automation)


#### class `Gauntlet.CSVParser`  
`public static class CSVParser`  
_public; L11-57_
- L13-56 _public method_ `public static List<Dictionary<string, string>> Load(string File, string DefaultForMissingColumns = null)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.CsvImporter.cs` (Gauntlet.Automation)


#### enum `Gauntlet.CsvImportType`  
`public enum CsvImportType`  
_public; L11-22_
- L16 _public* enumerator_ `CsvFile` — Standard import pointing to a csv file.
- L21 _public* enumerator_ `Inline` — An import that has no csv and any metadata is provided via the manifest.

#### interface `Gauntlet.ICsvMetadata`  
`public interface ICsvMetadata`  
_public; L24-30_
- L29 _public method_ `public Dictionary<string, dynamic> ToDict()` — Get as a completed dict;

#### interface `Gauntlet.ICsvImport`  
`public interface ICsvImport`  
_public; L36-93_
- desc: Interface for a generic Csv Import. CsvImportEntry should suit most needs, but if you need something custom you can implement this interface.
- L41 _public property_ `public CsvImportType ImportType { get; }` — The type of import.
- L46 _public property_ `public string ImportName { get; }` — Friendly name of the import for logging purposes.
- L52 _public property_ `public string CsvFilename { get; }` — attrs: `[AllowNull]` — The path to the csv file.
- L58 _public property_ `public string LogFilename { get; set; }` — attrs: `[AllowNull]` — The path to the log file (Optional).
- L64 _public property_ `public Dictionary<string, dynamic> CustomFields { get; }` — Any additional metadata associated with this csv. Corresponds to 'CustomFields' in the datasource config.
- L72 _public property_ `public ICsvMetadata Metadata { get; set; }` — attrs: `[AllowNull]` — Metadata for this import which varies on the import type. For CsvFile imports, this is additional metadata that's included with the csv's metadata (not currently implemented). For inline imports, this is the only source of metadata as there's no csv file.
- L79 _public property_ `public Dictionary<string, double> AdditionalStatAverages { get; }` — attrs: `[AllowNull]` — Additional csv stat averages to include. Currently only implemented for inline imports.
- L85 _public property_ `public IReadOnlyDictionary<string, string> AdditionalFiles { get; }` — Any additional files that should be bundled with this csv. Key is the file type, value is the path to the file.
- L92 _public method_ `public void AddAdditionalFile(string FileType, string Filename)` — Adds an additional file to this import.

#### class `Gauntlet.CsvImportEntry`  
`public class CsvImportEntry : ICsvImport`  
_public; L98-195_
- inherits: `ICsvImport`
- desc: Generic Csv import entry.
- L100 _public property_ `public CsvImportType ImportType { get; set; }`
- L101 _public property_ `public string ImportName { get; set; }`
- L103 _public property_ `public string CsvFilename { get; set; }`
- L104 _public property_ `public string LogFilename { get; set; }`
- L105 _public property_ `public Dictionary<string, dynamic> CustomFields { get; set; }`
- L106 _public property_ `public ICsvMetadata Metadata { get; set; }`
- L107 _public property_ `public IReadOnlyDictionary<string, string> AdditionalFiles { get; set; }`
- L108 _public property_ `public Dictionary<string, double> AdditionalStatAverages { get; set; }`
- L117-124 _public ctor_ `public CsvImportEntry(string CsvFilename, string LogFilename = null, Dictionary<string, dynamic> CustomFields = null)` — CsvFile import constructor. Deprecated: Please use CreateCsvFileImportEntry.
- L132-135 _public method_ `public static CsvImportEntry CreateCsvFileImportEntry(string CsvFilename, string LogFilename = null, Dictionary<string, dynamic> CustomFields = null)` — Creates an import entry for a csv file.
- L148-175 _public method_ `public static CsvImportEntry CreateInlineImportEntry(string ImportName, ICsvMetadata CsvMetadata, Dictionary<string, double> AdditionalStatAverages = null, Dictionary<string, dynamic> CustomFields = null)` — Creates an inline Import entry.
- L177-190 _public method_ `public void AddAdditionalFile(string FileType, string Filename)`
- L192-194 _private ctor_ `private CsvImportEntry()`

#### interface `Gauntlet.ICsvImporter`  
`public interface ICsvImporter`  
_public; L200-204_
- desc: Csv Importer interface.
- L202 _public method_ `public void Import(IEnumerable<ICsvImport> Imports)`
- L203 _public method_ `public void Import(IEnumerable<ICsvImport> Imports, out string URLLink)`

#### class `Gauntlet.CsvStatSanitizer`  
`public class CsvStatSanitizer`  
_public; L209-254_
- desc: Helper class to sanitize stat names.
- L212 _private field_ `private static string ValidCharacters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ /_-[]()#.:"`
- L217-220 _public method_ `public static bool IsValidStatName(string StatName)` — Returns true if the stat name only contains valid characters.
- L225-228 _public method_ `public static string GetSanitizedStatName(string StatName)` — Returns a new stat string with all invalid characters removed.
- L234-253 _public method_ `public static string SanitizeNameWithReplacement(string StatName, Func<char, char?> ReplacementFunc)` — Returns a new stat string with all invalid character replaced with the result of ReplacementFunc(char). If ReplacementFunc(c) returns null that character is skipped.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.HordeReport.cs` (Gauntlet.Automation)


#### class `Gauntlet.HordeReport`  
`public static class HordeReport`  
_public; L21-2641_
- L26-32 _public property_ `public static string DefaultTestDataDir { get; }` — Default location to store Test Data
- L36-42 _public property_ `public static string DefaultArtifactsDir { get; }` — Default location to store test Artifacts
- L2604-2613 _private method_ `private static JsonSerializerOptions GetDefaultJsonOptions()`
- L2621-2640 _private method_ `private static string ValidateKey(string InKey)` — Validate Key name, intended to validate a key that is going to be used as property name (ie: Phase key).

#### class `Gauntlet.HordeReport.BaseHordeReport`  
`public abstract class BaseHordeReport : BaseTestReport`  
_public; L44-189_
- inherits: `BaseTestReport`
- L49 _public property_ `public override int Version => ...` — Horde report version
- L51 _protected field_ `protected string OutputArtifactPath`
- L52 _protected field_ `protected HashSet<string> ArtifactProcessedHashes`
- L53 _protected field_ `protected Dictionary<string, object> ExtraReports`
- L53 _protected field_ `protected Dictionary< ExtraReports`
- L61-64 _public method_ `public override bool AttachArtifact(string ArtifactPath, string Name = null)` — Attach Artifact to the Test Report
- L72-117 _public method_ `public bool AttachArtifact(string ArtifactPath, string Name = null, bool Overwrite = false)` — Attach Artifact to the Test Report
- L124-133 _public method_ `public void SetOutputArtifactPath(string InPath)` — Set Output Artifact Path and create the directory if missing
- L142 _public method_ `public abstract bool AttachDeviceLog(string InstanceName, string LogPath, string LogName)` — Attach a log path to a device instance name
- L144-155 _public method_ `public void AttachDependencyReport(object InReport, string Key = null)`
- L157-165 _public method_ `public override Dictionary<string, object> GetReportDependencies()`
- L172-179 _public method_ `public virtual string GetTestDataKey(string BaseKey = null)` — Return the Key to be used for the TestData
- L185-188 _public method_ `public virtual object GetTestData()` — Return the data to be stored in the TestData

#### class `Gauntlet.HordeReport.Device`  
`public class Device`  
_public; L195-208_
- desc: Contains detailed information about device that run tests
- L197 _public property_ `public string DeviceName { get; set; }`
- L198 _public property_ `public string Instance { get; set; }`
- L199 _public property_ `public string Platform { get; set; }`
- L200 _public property_ `public string OSVersion { get; set; }`
- L201 _public property_ `public string Model { get; set; }`
- L202 _public property_ `public string GPU { get; set; }`
- L203 _public property_ `public string CPUModel { get; set; }`
- L204 _public property_ `public int RAMInGB { get; set; }`
- L205 _public property_ `public string RenderMode { get; set; }`
- L206 _public property_ `public string RHI { get; set; }`
- L207 _public property_ `public string AppInstanceLog { get; set; }`

#### class `Gauntlet.HordeReport.ComparisonFiles`  
`public class ComparisonFiles`  
_public; L213-218_
- desc: Contains reference to files used or generated for file comparison
- L215 _public property_ `public string Difference { get; set; }`
- L216 _public property_ `public string Approved { get; set; }`
- L217 _public property_ `public string Unapproved { get; set; }`

#### class `Gauntlet.HordeReport.Artifact`  
`public class Artifact`  
_public; L222-233_
- desc: Contains information about test artifact
- L224-227 _public ctor_ `public Artifact()`
- L229 _public property_ `public string Id { get; set; }`
- L230 _public property_ `public string Name { get; set; }`
- L231 _public property_ `public string Type { get; set; }`
- L232 _public property_ `public ComparisonFiles Files { get; set; }`

#### class `Gauntlet.HordeReport.Event`  
`public class Event`  
_public; L237-243_
- desc: Contains information about test entry event
- L239 _public property_ `public EventType Type { get; set; }`
- L240 _public property_ `public string Message { get; set; }`
- L241 _public property_ `public string Context { get; set; }`
- L242 _public property_ `public string Artifact { get; set; }`

#### class `Gauntlet.HordeReport.Entry`  
`public class Entry`  
_public; L247-258_
- desc: Contains information about test entry
- L249-252 _public ctor_ `public Entry()`
- L254 _public property_ `public Event Event { get; set; }`
- L255 _public property_ `public string Filename { get; set; }`
- L256 _public property_ `public int LineNumber { get; set; }`
- L257 _public property_ `public string Timestamp { get; set; }`

#### class `Gauntlet.HordeReport.TestResultDetailed`  
`public class TestResultDetailed`  
_public; L262-300_
- desc: Contains detailed information about test result. This is to what TestPassResult refere to for each test result.
- L264-268 _public ctor_ `public TestResultDetailed()`
- L270 _public property_ `public string TestDisplayName { get; set; }`
- L271 _public property_ `public string FullTestPath { get; set; }`
- L272 _public property_ `public TestStateType State { get; set; }`
- L273 _public property_ `public string DeviceInstance { get; set; }`
- L274 _public property_ `public int Warnings { get; set; }`
- L275 _public property_ `public int Errors { get; set; }`
- L276 _public property_ `public List<Artifact> Artifacts { get; set; }`
- L277 _public property_ `public List<Entry> Entries { get; set; }`
- L282-288 _public method_ `public Artifact AddNewArtifact()` — Add a new Artifact to the test result and return it
- L293-299 _public method_ `public Entry AddNewEntry()` — Add a new Entry to the test result and return it

#### class `Gauntlet.HordeReport.TestResult`  
`public class TestResult`  
_public; L304-361_
- desc: Contains a brief information about test result.
- L306-309 _public ctor_ `public TestResult()`
- L311-315 _public property_ `public string TestDisplayName { get; set; }`
- L316-320 _public property_ `public string FullTestPath { get; set; }`
- L321-325 _public property_ `public TestStateType State { get; set; }`
- L326-330 _public property_ `public string DeviceInstance { get; set; }`
- L331-335 _public property_ `public int Errors { get; set; }`
- L336-340 _public property_ `public int Warnings { get; set; }`
- L342 _public property_ `public string ArtifactName { get; set; }`
- L345 _private property_ `private TestResultDetailed TestDetailed { get; set; }`
- L350-353 _public method_ `public TestResultDetailed GetTestResultDetailed()` — Return the underlying TestResultDetailed
- L357-360 _public method_ `public void SetTestResultDetailed(TestResultDetailed InTestResultDetailed)` — Set the underlying TestResultDetailed

#### class `Gauntlet.HordeReport.UnrealEngineTestPassResults`  
`public class UnrealEngineTestPassResults : BaseHordeReport`  
_public; L366-544_
- inherits: `BaseHordeReport`
- desc: Contains information about an entire test pass
- L368-371 _public property_ `public override string Type { get; }`
- L373-377 _public ctor_ `public UnrealEngineTestPassResults() : base()`
- L379 _public property_ `public List<Device> Devices { get; set; }`
- L380 _public property_ `public string ReportCreatedOn { get; set; }`
- L381 _public property_ `public string ReportURL { get; set; }`
- L382 _public property_ `public int SucceededCount { get; set; }`
- L383 _public property_ `public int SucceededWithWarningsCount { get; set; }`
- L384 _public property_ `public int FailedCount { get; set; }`
- L385 _public property_ `public int NotRunCount { get; set; }`
- L386 _public property_ `public int InProcessCount { get; set; }`
- L387 _public property_ `public float TotalDurationSeconds { get; set; }`
- L388 _public property_ `public List<TestResult> Tests { get; set; }`
- L393-399 _private method_ `private Device AddNewDevice()` — Add a new Device to the pass results and return it
- L401-413 _public method_ `public override bool AttachDeviceLog(string InstanceName, string LogPath, string LogName)`
- L418-424 _private method_ `private TestResult AddNewTestResult()` — Add a new TestResult to the pass results and return it
- L426-429 _public method_ `public override void AddEvent(EventType Type, string Message, params object[] Args)`
- L436-506 _public method_ `public static UnrealEngineTestPassResults FromUnrealAutomatedTests(UnrealAutomatedTestPassResults InTestPassResults, string ReportURL)` — Convert UnrealAutomatedTestPassResults to Horde data model
- L513-543 _public method_ `public void CopyTestResultsArtifacts(string ReportPath, string InOutputArtifactPath)` — Copy Test Results Artifacts

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy`  
`public class AutomatedTestSessionData_legacy : BaseHordeReport`  
_public; L549-1077_
- inherits: `BaseHordeReport`
- desc: Contains information about a test session
- L551-554 _public property_ `public override string Type { get; }`
- L754-762 _public ctor_ `public AutomatedTestSessionData_legacy(string InName) : base()`
- L764 _public property_ `public string Name { get; set; }`
- L765 _public property_ `public string PreFlightChange { get; set; }`
- L766 _public property_ `public TestSession TestSessionInfo { get; set; }`
- L767 _public property_ `public List<Device> Devices { get; set; }`
- L772 _public property_ `public Dictionary<string, IndexedError> IndexedErrors { get; set; }` — Database side optimization: Index the TestUID by TestError hash. Key is meant to be the TestError hash and Value the list of related TestUID.
- L777 _private property_ `private Dictionary<string, TestResultData> TestResults { get; set; }` — Allow the Database to pull only one test result from the TestData. Key is meant to be the TestUID and Value the test result detailed events.
- L779 _private field_ `private string CurrentTestUID`
- L781-786 _private method_ `private Device NewDevice(string InName, string InInstance, string InInstanceLog = null)`
- L788-800 _private method_ `private void IndexTestError(string ErrorHash, string TestUID, string Message, string Tag)`
- L802-809 _private method_ `private TestResult GetCurrentTest()`
- L818-824 _public method_ `public void SetTest(string InName, List<string> InTags, string InSuite, List<string> InDevices, string InDateTime = null)` — Add a Test entry and set it as current test
- L829-833 _public method_ `public void SetTestState(TestStateType InState)` — Set current test state
- L838-842 _public method_ `public void SetTestTimeElapseSec(float InTimeElapseSec)` — Set current test time elapse in second
- L849-855 _public method_ `public override void AddEvent(EventType Type, string Message, params object[] Args)` — Add event to current test
- L864-872 _public method_ `public void AddEvent(string InDateTime, EventType InType, string InMessage, string InTag, string InContext)` — Overload of AddEvent, add even to current test with date time
- L880-895 _public method_ `public bool AddArtifactToLastEvent(string InTag, string InFilePath, string InReferencePath = null)` — Add artifact to last test event
- L897-909 _public method_ `public override bool AttachDeviceLog(string InstanceName, string LogPath, string LogName)`
- L911-914 _public method_ `public override string GetTestDataKey(string BaseKey = null)`
- L915-924 _public method_ `public override Dictionary<string, object> GetReportDependencies()`
- L935-1076 _public method_ `public static AutomatedTestSessionData_legacy FromUnrealAutomatedTests(UnrealAutomatedTestPassResults InTestPassResults, string InName, string InSuite, string InReportPath, string InHordeArtifactPath)` — Convert UnrealAutomatedTestPassResults to Horde data model

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy.TestResult`  
`public class TestResult`  
_public; L557-627_
- L559 _public property_ `public string Name { get; set; }`
- L560 _public property_ `public List<string> Tags { get; set; }`
- L561 _public property_ `public string TestUID { get; set; }`
- L562 _public property_ `public string Suite { get; set; }`
- L563 _public property_ `public TestStateType State { get; set; }`
- L564 _public property_ `public List<string> DeviceAppInstanceName { get; set; }`
- L565 _public property_ `public uint ErrorCount { get; set; }`
- L566 _public property_ `public uint WarningCount { get; set; }`
- L567 _public property_ `public string ErrorHashAggregate { get; set; }`
- L568 _public property_ `public string DateTime { get; set; }`
- L569 _public property_ `public float TimeElapseSec { get; set; }`
- L571 _public field_ `public List<TestEvent> Events`
- L572 _public field_ `public SortedSet<string> ErrorHashes`
- L573-585 _public ctor_ `public TestResult(string InName, List<string> InTags, string InSuite, TestStateType InState, List<string> InDevices, string InDateTime)`
- L586-589 _private method_ `private string GenerateHash(string InName)`
- L590-618 _public method_ `public TestEvent NewEvent(string InDateTime, EventType InType, string InMessage, string InTag, string InContext = null)`
- L619-626 _public method_ `public TestEvent GetLastEvent()`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy.TestSession`  
`public class TestSession`  
_public; L628-645_
- L630 _public property_ `public string DateTime { get; set; }`
- L631 _public property_ `public float TimeElapseSec { get; set; }`
- L632 _public property_ `public Dictionary<string, TestResult> Tests { get; set; }`
- L633 _public property_ `public string TestResultsTestDataUID { get; set; }`
- L634-638 _public ctor_ `public TestSession()`
- L639-644 _public method_ `public TestResult NewTestResult(string InName, List<string> InTags, string InSuite, TestStateType InState, List<string> InDevices, string InDateTime)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy.Device`  
`public class Device`  
_public; L646-663_
- L648 _public property_ `public string Name { get; set; }`
- L649 _public property_ `public string AppInstanceName { get; set; }`
- L650 _public property_ `public string AppInstanceLog { get; set; }`
- L651 _public property_ `public Dictionary<string, string> Metadata { get; set; }`
- L652-658 _public ctor_ `public Device(string InName, string InInstance, string InInstanceLog)`
- L659-662 _public method_ `public void SetMetaData(string Key, string Value)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy.TestArtifact`  
`public class TestArtifact`  
_public; L664-668_
- L666 _public property_ `public string Tag { get; set; }`
- L667 _public property_ `public string ReferencePath { get; set; }`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy.TestEvent`  
`public class TestEvent`  
_public; L669-727_
- L671 _public property_ `public string Message { get; set; }`
- L672 _public property_ `public string Context { get; set; }`
- L673 _public property_ `public EventType Type { get; set; }`
- L674 _public property_ `public string Tag { get; set; }`
- L675 _public property_ `public string Hash { get; set; }`
- L676 _public property_ `public string DateTime { get; set; }`
- L677 _public property_ `public List<TestArtifact> Artifacts { get; set; }`
- L678-687 _public ctor_ `public TestEvent(EventType InType, string InMessage, string InTag, string InContext, string InDateTime)`
- L688-695 _public method_ `public TestArtifact NewArtifacts(string InTag, string InReferencePath)`
- L696-721 _private method_ `private string FilterEvent(string Text)`
- L722-726 _private method_ `private string GenerateEventHash()`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy.TestResultData`  
`public class TestResultData`  
_public; L728-740_
- L730-734 _public property_ `public List<TestEvent> Events { get; set; }`
- L735 _private field_ `private TestResult Result`
- L736-739 _public ctor_ `public TestResultData(TestResult InTestResult)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData_legacy.IndexedError`  
`public class IndexedError`  
_public; L741-752_
- L743 _public property_ `public string Message { get; set; }`
- L744 _public property_ `public string Tag { get; set; }`
- L745 _public property_ `public List<string> TestUIDs { get; set; }`
- L746-751 _public ctor_ `public IndexedError(string InMessage, string InTag)`

#### class `Gauntlet.HordeReport.SimpleTestReport`  
`public class SimpleTestReport : BaseHordeReport`  
_public; L1082-1176_
- inherits: `BaseHordeReport`
- desc: Contains Test success/failed status and a list of errors and warnings
- L1098-1101 _public property_ `public override string Type { get; }`
- L1103-1106 _public ctor_ `public SimpleTestReport() : base()`
- L1108-1123 _public ctor_ `public SimpleTestReport(Gauntlet.TestResult TestResult, UnrealTestContext Context, UnrealTestConfiguration Configuration) : base()`
- L1125 _public property_ `public string TestName { get; set; }`
- L1126 _public property_ `public string Description { get; set; }`
- L1127 _public property_ `public string ReportCreatedOn { get; set; }`
- L1128 _public property_ `public float TotalDurationSeconds { get; set; }`
- L1129 _public property_ `public bool HasSucceeded { get; set; }`
- L1130 _public property_ `public string Status { get; set; }`
- L1131 _public property_ `public string URLLink { get; set; }`
- L1132 _public property_ `public int BuildChangeList { get; set; }`
- L1133 _public property_ `public TestRole MainRole { get; set; }`
- L1134 _public property_ `public List<TestRole> Roles { get; set; }`
- L1135 _public property_ `public string TestResult { get; set; }`
- L1136 _public property_ `public List<String> Logs { get; set; }`
- L1137 _public property_ `public List<String> Errors { get; set; }`
- L1138 _public property_ `public List<String> Warnings { get; set; }`
- L1140-1156 _public method_ `public override void AddEvent(EventType Type, string Message, params object[] Args)`
- L1158-1166 _public method_ `public override bool AttachArtifact(string ArtifactPath, string Name = null)`
- L1168-1175 _public method_ `public override bool AttachDeviceLog(string InstanceName, string LogPath, string LogName)`

#### class `Gauntlet.HordeReport.SimpleTestReport.TestRole`  
`public class TestRole`  
_public; L1084-1096_
- L1086 _public property_ `public string Type { get; set; }`
- L1087 _public property_ `public string Platform { get; set; }`
- L1088 _public property_ `public string Configuration { get; set; }`
- L1090-1095 _public ctor_ `public TestRole(UnrealTestRole Role, UnrealTestRoleContext Context)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData`  
`public class AutomatedTestSessionData : BaseHordeReport`  
_public; L1184-2502_
- inherits: `BaseHordeReport`
- desc: Contains information about a test session (v2)
- L1186 _public property_ `public override string Type => ...`
- L1188 _public const_ `public const int DEFAULT_VERSION = 2`
- L1189 _public property_ `public override int Version => ...`
- L1194 _public property_ `public string Key { get; set; }` — Unique key that identify the test and group the different sessions
- L1196-1199 _public method_ `public override string GetTestDataKey(string? BaseKey = null)`
- L1204 _protected property_ `protected TestSession Data { get; set; }` — Stored data of the session
- L1206-1209 _public method_ `public override IDataBlob GetTestData()`
- L1216-1219 _private method_ `private static string GenerateKey(string InName)` — Utility function to generate a valid key from any name
- L1224 _private property_ `private TestPhase? CurrentPhase { get; set; }` — Cursor to the current phase
- L1229-1233 _private* ctor_ `static AutomatedTestSessionData()` — Static constructor
- L1235-1239 _public ctor_ `public AutomatedTestSessionData(string InKey, string? InName = null) : base()`
- L1241-1260 _public ctor_ `public AutomatedTestSessionData(ITestAuditMetadata InAudit) : this(InAudit.TestKey, InAudit.TestName)`
- L1576-1580 _public method_ `public virtual void SetSessionTiming(DateTime StartTime, float TimeElapse)` — Set the session timing information
- L1588-1600 _public method_ `public virtual TestDevice AddDevice(string InName, string? InKey = null)` — Add a Device to the session (or replace it) and return the new instance.
- L1607-1610 _public method_ `public virtual TestDevice? GetDevice(string Key)` — Return the device associated with the Key
- L1616-1619 _public method_ `public virtual List<TestDevice> GetDevices()` — Return all the devices associated with the report
- L1621-1635 _public method_ `public override bool AttachDeviceLog(string InstanceName, string LogPath, string LogName)`
- L1643-1648 _public method_ `public virtual TestPhase AddPhase(string InName, string? InKey = null)` — Add a phase to the test session
- L1655-1658 _public method_ `public virtual TestPhase? GetPhase(string Key)` — Get the phase associated with Key
- L1665-1673 _public method_ `public virtual void SetCurrentPhase(string Key)` — Set the current session phase with the phase associated with Key
- L1679-1683 _public method_ `public virtual void SetCurrentPhase(TestPhase InPhase)` — Set the current session phase with the input phase (and attach that phase the session with not already)
- L1689-1692 _public method_ `public virtual void AttachPhase(TestPhase InPhase)` — Attach the input phase to the test session
- L1698-1701 _public method_ `public virtual TestPhase? GetCurrentPhase()` — Get the current session phase
- L1707-1714 _public method_ `public virtual void AddTestTags(IEnumerable<string> NewTags)` — Add tags to the test
- L1723-1726 _public method_ `public virtual void AddTestDescription(string? Team, string? Intent, string? Harness, string? Profile)` — Add test description
- L1735-1739 _public method_ `public virtual void AddTestRecipe(string NodeClass, string Version, float TimeoutMinutes = 0, Dictionary<string, object>? Params = null)` — Add recipe to run the same test
- L1983-1986 _public method_ `public virtual void AddEvent(LogEvent Event)` — Attached the input LogEvent to the stream to current event stream
- L1995-1998 _public method_ `public virtual void AddEvent(DateTime Time, Logging.LogLevel Level, string Message, params object[] Args)` — Add event with optional formatting inputs to current event stream
- L2006-2009 _public method_ `public override void AddEvent(EventType Type, string Message, params object[] Args)` — Add event with optional formatting inputs to current event stream
- L2017-2026 _protected method_ `protected virtual bool AttachArtifact(ref string FilePath, string? Name = null)` — Attach Artifact to the report
- L2034-2043 _protected method_ `protected virtual bool AttachArtifactOrWarn(ref string? FilePath, string? Name = null)` — Attach artifact to the report, warn if it fails to do it
- L2236-2255 _private method_ `private static Logging.LogLevel EventTypeToLogLevel(EventType Type)`
- L2257-2280 _private method_ `private static Logging.LogLevel EventSeverityToLogLevel(EventSeverity Type)`
- L2282-2310 _private method_ `private static TestPhaseOutcome TestStateToPhaseOutcome(TestStateType State)`
- L2312-2341 _private method_ `private static TestPhaseOutcome TestResultToPhaseOutcome(Gauntlet.TestResult State)`
- L2349-2362 _public method_ `public virtual TestEventStream GetEventStream(string? InPhaseKey = null)` — Return the event stream of the target phase or current phase if not specified
- L2365-2411 _public method_ `public override void FinalizeReport()` — (inheritdoc)
- L2413-2416 _private method_ `private static DateTime ConvertUETimeStringToDateTime(string StringTime)`
- L2424-2501 _public method_ `public void PopulateFromUnrealAutomatedTests(UnrealAutomatedTestPassResults InTestPassResults, string InReportPath)` — Convert UnrealAutomatedTestPassResults to Horde data model

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestDevice`  
`public class TestDevice`  
_public; L1265-1279_
- desc: Represent a Device used during a test
- L1267 _public property_ `public string name { get; set; }`
- L1269 _public property_ `public string key { get; set; }` — attrs: `[JsonIgnore]`
- L1270 _public property_ `public string? appInstanceLogPath { get; set; }`
- L1271 _public property_ `public Dictionary<string, string> metadata { get; set; }`
- L1273-1278 _public ctor_ `public TestDevice(string InName, string InKey)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestSessionSummary`  
`public class TestSessionSummary`  
_public; L1284-1299_
- desc: Summary for the test session
- L1286 _public property_ `public string testName { get; set; }`
- L1287 _public property_ `public string? dateTime { get; set; }`
- L1288 _public property_ `public float timeElapseSec { get; set; }`
- L1289 _public property_ `public string? commandline { get; set; }`
- L1290 _public property_ `public int phasesTotalCount { get; set; }`
- L1291 _public property_ `public int phasesSucceededCount { get; set; }`
- L1292 _public property_ `public int phasesUndefinedCount { get; set; }`
- L1293 _public property_ `public int phasesFailedCount { get; set; }`
- L1295-1298 _public ctor_ `public TestSessionSummary(string InName)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestDescription`  
`public class TestDescription`  
_public; L1304-1318_
- desc: Description of the test
- L1306 _public property_ `public string? team { get; set; }`
- L1307 _public property_ `public string? profile { get; set; }`
- L1308 _public property_ `public string? harness { get; set; }`
- L1309 _public property_ `public string? intent { get; set; }`
- L1311-1317 _public ctor_ `public TestDescription(string? InTeam = null, string? InProfile = null, string? InHarness = null, string? InIntent = null)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestRecipe`  
`public class TestRecipe`  
_public; L1323-1336_
- desc: Recipe to run the test
- L1325 _public property_ `public string nodeClass { get; set; }`
- L1326 _public property_ `public string version { get; set; }`
- L1327 _public property_ `public float timeoutMinutes { get; set; }`
- L1329 _public property_ `public Dictionary<string, object>? @params { get; set; }` — attrs: `[JsonPropertyName("params")]`
- L1330-1335 _public ctor_ `public TestRecipe(string InNodeClass, string InVersion, float InTimeoutMinutes = 0)`

#### enum `Gauntlet.HordeReport.AutomatedTestSessionData.TestPhaseOutcome`  
`public enum TestPhaseOutcome`  
_public; L1339-1347_
- attrs: `[JsonConverter(typeof(JsonTryParseEnumConverter))]`
- L1341 _public* enumerator_ `Unknown`
- L1342 _public* enumerator_ `NotRun`
- L1343 _public* enumerator_ `Interrupted`
- L1344 _public* enumerator_ `Failed`
- L1345 _public* enumerator_ `Success`
- L1346 _public* enumerator_ `Skipped`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestPhase`  
`public class TestPhase`  
_public; L1352-1521_
- desc: Represent a phase of a test
- L1354 _public property_ `public string key { get; set; }`
- L1355 _public property_ `public string name { get; set; }`
- L1356 _public property_ `public string? dateTime { get; set; }`
- L1357 _public property_ `public float timeElapseSec { get; set; }`
- L1358 _public property_ `public TestPhaseOutcome outcome { get; set; }`
- L1359 _public property_ `public string? errorFingerprint { get; set; }`
- L1360 _public property_ `public bool? hasWarning { get; set; }`
- L1361 _public property_ `public HashSet<string>? tags { get; set; }`
- L1362 _public property_ `public HashSet<string> deviceKeys { get; set; }`
- L1363 _public property_ `public string? eventStreamPath { get; set; }`
- L1365 _private property_ `private TestSession? session { get; set; }`
- L1367 _private property_ `private TestEventStream eventStream { get; set; }`
- L1369-1380 _public ctor_ `public TestPhase(string InName, string? InKey = null, TestSession? InSession = null)`
- L1387-1391 _public method_ `public void SetTiming(DateTime StartTime, float TimeElapse)` — Set timing information about the phase
- L1397-1402 _public method_ `public void SetOutcome(TestPhaseOutcome OutCome)` — Set the outcome of the phase, it will update the test session phase counts
- L1408-1413 _public method_ `public void SetOutcome(TestStateType State)` — Set the outcome of the phase, it will update the test session phase counts
- L1419-1424 _public method_ `public void SetOutcome(Gauntlet.TestResult State)` — Set the outcome of the phase using Gauntlet TestResult type, it will update the test session phase counts
- L1430-1440 _public method_ `public void AttachToSession(TestSession InSession)` — Attach the phase to a session, making changes to the phase outcome tracked in that session
- L1451-1477 _private method_ `private void UpdatePhasesCount(PhaseCount Direction = PhaseCount.In)` — Update the phases count in the session based on the phase outcome
- L1482-1488 _public method_ `public void CompileErrorFingerprint()` — Compile the aggregate errors
- L1494-1501 _public method_ `public void AddTags(IEnumerable<string> NewTags)` — Add tags to the phase
- L1507-1510 _public method_ `public void AddTags(IEnumerable<TestTag> NewTags)` — Add tags to the phase
- L1517-1520 _public method_ `public TestEventStream GetStream()` — Get the event stream associated with this phase

#### enum `Gauntlet.HordeReport.AutomatedTestSessionData.TestPhase.PhaseCount`  
`private enum PhaseCount`  
_private; L1442-1446_
- L1444 _public* enumerator_ `In`
- L1445 _public* enumerator_ `Out`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TagComparer`  
`internal class TagComparer : IEqualityComparer<string>`  
_internal; L1523-1542_
- inherits: `IEqualityComparer<string>`
- L1525-1536 _public method_ `public bool Equals(string? TagA, string? TagB)`
- L1538-1541 _public method_ `public int GetHashCode([DisallowNull] string Tag)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestSession`  
`public class TestSession : IDataBlob`  
_public; L1547-1569_
- inherits: `IDataBlob`
- desc: fork of the test session data (summary, phases, devices, eventStreams)
- L1549 _public property_ `public TestSessionSummary summary { get; set; }`
- L1550 _public property_ `public List<TestPhase> phases { get; set; }`
- L1551 _public property_ `public Dictionary<string, TestDevice> devices { get; set; }`
- L1552 _public property_ `public int version { get; }`
- L1553 _public property_ `public Dictionary<string, string> metadata { get; }`
- L1554 _public property_ `public HashSet<string>? tags { get; set; }`
- L1555 _public property_ `public TestDescription? description { get; set; }`
- L1556 _public property_ `public TestRecipe? recipe { get; set; }`
- L1560 _public property_ `public AutomatedTestSessionData? report { get; set; }` — attrs: `[JsonIgnore]`
- L1562-1568 _public ctor_ `public TestSession(string InName, AutomatedTestSessionData? InReport = null)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestEventStream`  
`public class TestEventStream`  
_public; L1744-1977_
- desc: Represent the event stream of a phase
- L1747 _private* field_ `static Regex Regex_numbertimestampstring = new Regex(@"\d[\d.,:]*", RegexOptions.Compiled)`
- L1749 _private* field_ `static Regex Regex_pathstring = new Regex(@"(?:(?<![A-Z])|HTTPS*:)(?:[A-Z]:|[/\\])[\w/\\.:+?=%-]+", RegexOptions.Compiled)`
- L1751 _private* field_ `static Regex Regex_hexstring = new Regex(@"(?:0X|#)[0-9A-F]+", RegexOptions.Compiled)`
- L1753 _private property_ `private AutomatedTestSessionData? report { get; set; }`
- L1754 _private property_ `private TestPhase phase { get; set; }`
- L1755 _private property_ `private List<LogEvent> stream { get; set; }`
- L1757-1762 _public ctor_ `public TestEventStream(AutomatedTestSessionData? InReport, TestPhase InPhase)`
- L1768-1771 _public method_ `public bool HasAnyEvent()` — Return true if there is any LogEvent in this stream
- L1777-1780 _public method_ `public IEnumerable<LogEvent> GetEvents()` — Get the list of LogEvents
- L1786-1789 _public method_ `public virtual void AttachToReport(AutomatedTestSessionData InReport)` — Attach the event stream to a report
- L1795-1809 _public method_ `public virtual void AddEvent(LogEvent Event)` — Attached the input LogEvent to the stream
- L1811-1819 _private method_ `private string FilterEvent(string Text)`
- L1820-1823 _private method_ `private string GenerateHash(string InText)`
- L1832-1846 _public method_ `public virtual void AddEvent(DateTime Time, Logging.LogLevel Level, string Message, params object[] Args)` — Add event with optional formatting inputs
- L1854-1857 _public method_ `public virtual void AddEvent(Logging.LogLevel Level, string Message, params object[] Args)` — Add event with optional formatting inputs
- L1864-1867 _public method_ `public virtual void AddInfo(string Format, params object[] Args)` — Add Info event with optional formatting inputs
- L1874-1877 _public method_ `public virtual void AddWarning(string Format, params object[] Args)` — Add Warning event with optional formatting inputs
- L1884-1887 _public method_ `public virtual void AddError(string Format, params object[] Args)` — Add Error event with optional formatting inputs
- L1893-1909 _public method_ `public virtual void AddEvent(ITestEvent Event)` — Add event using ITestEvent as input
- L1918-1927 _public method_ `public virtual void AddURLLink(DateTime Time, Logging.LogLevel Level, string Name, string URL)` — Add URL link
- L1936-1952 _public method_ `public virtual void AddArtifact(DateTime Time, Logging.LogLevel Level, string Format, ILogArtifact Artifact)` — Add Artifact event
- L1961-1976 _public method_ `public virtual void AddImageComparison(DateTime Time, Logging.LogLevel Level, string Format, ImageComparisonFiles Artifact)` — Add Image Comparison event

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestLogValueTypes`  
`private static class TestLogValueTypes`  
_private; L2045-2065_
- L2048 _public field_ `public static readonly Utf8String Type = new Utf8String("$type")`
- L2049 _public field_ `public static readonly Utf8String Text = new Utf8String("$text")`
- L2051 _public field_ `public static readonly string artifacts = "Artifacts"`
- L2053 _public field_ `public static readonly string embeddedHtml = "Embedded HTML"`
- L2055 _public field_ `public static readonly string imageCompare = "Image Compare"`
- L2056 _public field_ `public static readonly string unapproved = "unapproved"`
- L2057 _public field_ `public static readonly string unapprovedMetadata = "unapproved_metadata"`
- L2058 _public field_ `public static readonly string approved = "approved"`
- L2059 _public field_ `public static readonly string approvedMetadata = "approved_metadata"`
- L2060 _public field_ `public static readonly string difference = "difference"`
- L2061 _public field_ `public static readonly string differenceReport = "difference_report"`
- L2063 _public field_ `public static readonly string url = "URL"`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestLogValue`  
`public class TestLogValue`  
_public; L2070-2095_
- desc: Represent a Log value. Necessary to support LogValue annotation in TestData.
- L2072 _public property_ `public Utf8String Type { get; set; }`
- L2073 _public property_ `public string Text { get; set; }`
- L2074 _public property_ `public Dictionary<Utf8String, object?> Properties { get; set; }`
- L2076-2081 _public ctor_ `public TestLogValue(string InType, string InText, Dictionary<Utf8String, object?> InProperties)`
- L2083-2086 _public method_ `public override string ToString()`
- L2091-2094 _public method_ `public static TestLogValue CreateURLLink(string Text, string URL)` — Utility function to create log value for URL link

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.TestLogValueFormatter`  
`public class TestLogValueFormatter : ILogValueFormatter`  
_public; L2100-2118_
- inherits: `ILogValueFormatter`
- desc: TestLogValue Formatter
- L2102-2117 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### interface `Gauntlet.HordeReport.AutomatedTestSessionData.ILogArtifact`  
`public interface ILogArtifact`  
_public; L2123-2127_
- desc: Interface for artifact in Log event
- L2125 _public method_ `public bool AttachTo(AutomatedTestSessionData Report)`
- L2126 _public* method_ `Dictionary<string, object?> ToProperties()`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.ArtifactFiles`  
`public class ArtifactFiles : ILogArtifact`  
_public; L2132-2200_
- inherits: `ILogArtifact`
- desc: Generic Artifact Files utility objects to attached files to report and generate event properties
- L2134 _public property_ `public string Type { get; set; }`
- L2135 _public property_ `public string Token { get; set; }`
- L2136 _public property_ `public string Name { get; set; }`
- L2137 _public property_ `public Dictionary<string, string?> Files { get; set; }`
- L2138 _public property_ `public string RootPath { get; set; }`
- L2140-2147 _public ctor_ `public ArtifactFiles(string InType, string InName, Dictionary<string, string?> InFiles, string InRootPath)`
- L2149-2150 _public ctor_ `public ArtifactFiles(string InName, Dictionary<string, string?> InFiles, string InRootPath) : this(TestLogValueTypes.artifacts, InName, InFiles, InRootPath)`
- L2152-2167 _private method_ `private bool AttachFileTo(ref string? FilePath, AutomatedTestSessionData Report)`
- L2169-2183 _public method_ `public bool AttachTo(AutomatedTestSessionData Report)`
- L2185-2199 _public method_ `public Dictionary<string, object?> ToProperties()`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.ImageComparisonFiles`  
`public class ImageComparisonFiles : ArtifactFiles, ILogArtifact`  
_public; L2205-2225_
- inherits: `ArtifactFiles, ILogArtifact`
- desc: Utility object to attached ImageComparison artifacts and generate related event properties
- L2207-2224 _public ctor_ `public ImageComparisonFiles(string InName, Dictionary<string, string?> InFiles, string InRootPath, bool AddMetadataFiles = false) : base(TestLogValueTypes.imageCompare, InName, InFiles, InRootPath)`

#### class `Gauntlet.HordeReport.AutomatedTestSessionData.EmbeddedHTMLFile`  
`public class EmbeddedHTMLFile : ArtifactFiles, ILogArtifact`  
_public; L2230-2234_
- inherits: `ArtifactFiles, ILogArtifact`
- desc: Utility object to attached Embedded HTML file and generate related event properties
- L2232-2233 _public ctor_ `public EmbeddedHTMLFile(string InName, string InFile, string InRootPath) : base(TestLogValueTypes.embeddedHtml, InName, new Dictionary<string, string?>() { { "path", InFile } }, InRootPath)`

#### class `Gauntlet.HordeReport.TestDataCollection`  
`public class TestDataCollection`  
_public; L2507-2603_
- desc: Container for Test Data items
- L2519-2522 _public ctor_ `public TestDataCollection()`
- L2524-2564 _public method_ `public DataItem AddNewTestReport(object InData, string? InKey = null)`
- L2566 _public property_ `public List<DataItem> items { get; set; }`
- L2573-2602 _public method_ `public void WriteToJson(string OutputTestDataFilePath, bool bIncrementNameIfFileExists = false)` — Write Test Data Collection to json

#### interface `Gauntlet.HordeReport.TestDataCollection.IDataBlob`  
`public interface IDataBlob`  
_public; L2509-2513_
- L2511 _public* property_ `int version { get; }`
- L2512 _public* property_ `Dictionary<string, string> metadata { get; }`

#### class `Gauntlet.HordeReport.TestDataCollection.DataItem`  
`public class DataItem`  
_public; L2514-2518_
- L2516 _public property_ `public string? key { get; set; }`
- L2517 _public property_ `public object? data { get; set; }`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.HtmlBuilder.cs` (Gauntlet.Automation)


#### class `Gauntlet.HtmlBuilder`  
`public class HtmlBuilder`  
_public; L11-362_
- L14 _protected field_ `protected StringBuilder SB`
- L15 _protected field_ `protected bool CurrentlyBuildingTable = false`
- L73-76 _public ctor_ `public HtmlBuilder()`
- L83-86 _public method_ `public override string ToString()` — Returns our formatted text
- L91-94 _public property_ `public bool EndsWithNewLine { get; }` — Returns true if the correct body ends with a new line
- L100-107 _public method_ `public HtmlBuilder EnsureEndsWithNewLine()` — Ensures any text after this starts on a new line
- L112-115 _public property_ `public bool EndsWithRowClose { get; }` — Returns true if the correct body ends with a new line
- L121-128 _public method_ `public HtmlBuilder EnsureEndsWithRowClose()` — Ensures any text after this starts on a new line
- L134-143 _public method_ `public HtmlBuilder StartBuildingTable()` — Open up a new table, if one doesn't already exist, to start adding cells to.
- L149-154 _public method_ `public HtmlBuilder StartRow()` — Open a new row. Close any existing open rows if they already exist.
- L159-163 _public method_ `public HtmlBuilder EndRow()` — Finalize a row with the proper tags.
- L165-174 _protected method_ `protected string CreateCell(string TableContents, TableCellInfo CellInfo)`
- L181-185 _public method_ `public HtmlBuilder AddNewCell(string TableContents, TableCellInfo CellInfo = null)` — Add a new cell with any formatting applied.
- L191-200 _public method_ `public HtmlBuilder FinalizeTable()` — Finish up an existing table. Close off any existing rows before closing the table and newlining.
- L202-206 _public method_ `public HtmlBuilder NewLine()`
- L214-218 _public method_ `public HtmlBuilder Hyperlink(string URL, string Text)` — Insert a hyperlink
- L225-230 _public method_ `public HtmlBuilder H1(string Text)` — Insert an H1 Header
- L237-242 _public method_ `public HtmlBuilder H2(string Text)` — Insert an H2 header
- L249-254 _public method_ `public HtmlBuilder H3(string Text)` — Insert an H3 header
- L261-266 _public method_ `public HtmlBuilder H4(string Text)` — Insert an H4 Header
- L272-277 _public method_ `public HtmlBuilder H5(string Text)` — Insert an H5 header
- L284-297 _public method_ `public HtmlBuilder OrderedList(IEnumerable<string> Items)` — Insert an ordered (numbered) list
- L304-317 _public method_ `public HtmlBuilder UnorderedList(IEnumerable<string> Items)` — Insert an unordered (bulleted) list
- L324-328 _public method_ `public HtmlBuilder Append(HtmlBuilder RHS)` — Append the provided Markdown to our body
- L335-339 _public method_ `public HtmlBuilder Append(string RHS)` — Append the provided text to our body. No formatting will be applied
- L349-360 _public method_ `public HtmlBuilder AppendFormatted(string RHS, TextOptions InOptions)` — Append the provided text to our body. No formatting will be applied

#### class `Gauntlet.HtmlBuilder.TableCellInfo`  
`public class TableCellInfo`  
_public; L19-38_
- desc: All of the possible ways to modify a stock table cell.
- L21 _public field_ `public bool WithBorder = true`
- L22 _public field_ `public bool CenterAlign = true`
- L26 _public field_ `public int CellColumnWidth = 1` — Number of columns the cell spans.
- L27 _public field_ `public string BackgroundColor = "#ffffff"`
- L28 _public field_ `public string BorderType = "border:1px solid black;"`
- L29 _public field_ `public string TableContents`
- L30-37 _public method_ `public void ResetToDefaults()`

#### class `Gauntlet.HtmlBuilder.TextOptions`  
`public class TextOptions`  
_public; L43-71_
- desc: All of the possible ways to modify a basic string via formatting.
- L45 _public field_ `public bool Italics = false`
- L46 _public field_ `public bool Bold = false`
- L47 _public field_ `public string TextColorOverride = string.Empty`
- L48 _public field_ `public string Hyperlink = string.Empty`
- L49-69 _public method_ `public string ApplyToString(string TextToAlter)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.HttpRequest.cs` (Gauntlet.Automation)


#### class `Gauntlet.HttpRequest`  
`public static class HttpRequest`  
_public; L13-54_
- L15-18 _public method_ `public static AuthenticationHeaderValue Authentication(string Target, string Token)`

#### class `Gauntlet.HttpRequest.Connection`  
`public class Connection`  
_public; L19-42_
- L21 _private field_ `private HttpClient Client`
- L22-31 _public ctor_ `public Connection(string Server, AuthenticationHeaderValue Auth)`
- L32-41 _public method_ `public HttpResponse PostJson(string Path, string JsonString)`

#### class `Gauntlet.HttpRequest.HttpResponse`  
`public class HttpResponse`  
_public; L43-53_
- L45 _public field_ `public string Content`
- L46 _public field_ `public HttpStatusCode StatusCode`
- L47-51 _public ctor_ `public HttpResponse(HttpStatusCode InCode, string InContent)`
- L52 _public property_ `public bool IsSuccessStatusCode { get; }`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.IMegazordService.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IMegazordService`  
`public partial interface IMegazordService`  
_public; L20-28_
- desc: Cross-boundary contract for the device farm Megazord API. Public engine code (e.g. TargetDeviceIOS) calls into the Megazord service via this interface so that restricted implementation details remain inside Engine/Restricted/NotForLicensees . This is a partial interface: platform-specific methods are declared in sibling files under the public platform paths (e.g. iOS contributes GetDeviceLockdownKeyAsync from Engine/Source/Programs/AutomationTool/Gauntlet/Platform/IOS/Gauntlet.IMegazordService.cs ).
- L27 _public* method_ `Task<string?> GetDeviceIPAddressAsync(string DeviceUUID)` — Query the IP address of a device from the Megazord API using its UUID or serial number.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.IgnoredIssueConfig.cs` (Gauntlet.Automation)


#### class `Gauntlet.IgnoredTestIssues`  
`public class IgnoredTestIssues`  
_public; L16-25_
- desc: Information that defines a device
- L18 _public field_ `public string TestName = ""`
- L20 _public field_ `public string[] IgnoredEnsures = new string[0]`
- L22 _public field_ `public string[] IgnoredWarnings = new string[0]`
- L24 _public field_ `public string[] IgnoredErrors = new string[0]`

#### class `Gauntlet.IgnoredIssueConfig`  
`public class IgnoredIssueConfig`  
_public; L33-129_
- desc: A class that can be serialized in from JSON file and used in a TestNode to ignore specific warnings/errors if so desired. Note - this is not used in the base Gauntlet classes but rather is intended for games where accepting *some* amount of issues may be necessary for a time. E.g. Issues that have been logged and are awaiting a fix, or a development branch that inherited some known issues from the mainline
- L35-38 _public ctor_ `public IgnoredIssueConfig()`
- L40 _private property_ `private IEnumerable<IgnoredTestIssues> IgnoredIssues { get; set; }`
- L58-71 _public method_ `public bool LoadFromFile(string InPath)` — Load from the provided JOSN file. [ { "TestName" : "Game.AbilityTests", "IgnoredWarnings" : [ "PNG Error: Duplicate ICCP" ], "IgnoredEnsures" : [ "Ensure condition failed: GlobalAbilityTaskCount < 1000", ] } ]
- L79-84 _public method_ `public bool IsEnsureIgnored(string InTestName, string InEnsureMsg)` — Returns true if the provided ensure should be ignored
- L92-97 _public method_ `public bool IsWarningIgnored(string InTestName, string InWarning)` — Returns true if the provided warning should be ignored for the specified test name
- L105-109 _public method_ `public bool IsErrorIgnored(string InTestName, string InError)` — Returns true if the provided error should be ignored for the specified test name
- L117-128 _public method_ `public bool IsLogEntryIgnored(string InTestName, UnrealLog.LogEntry InEntry)` — Returns true if the provided error should be ignored for the specified test name

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.IniConfigUtil.cs` (Gauntlet.Automation)


#### class `Gauntlet.IniConfigUtil`  
`public static class IniConfigUtil`  
_public; L14-139_
- L21-31 _public method_ `public static ConfigHierarchy GetConfigHierarchy(UnrealTestContext TestContext, ConfigHierarchyType ConfigType = ConfigHierarchyType.Game, UnrealTargetRole TargetRole = UnrealTargetRole.Client)` — Get a ConfigHierarchy of the type you want with platform-specific config for the given Role. This object can be used to read .ini config values. Default params return the client platform's game config. This looks for the workspace files for the project that you are trying to run your test on. The config directory for that project must exist to find valid results.
- L51-98 _public method_ `public static List<string> ParseListFromConfigString(string ConfigString, char ElementSeparator = ',')` — Helper function to return a list of separated values from a found config value string.
- L119-138 _public method_ `public static Dictionary<string, string> ParseDictionaryFromConfigString(string ConfigString, char KeyValueSeparator = '=')` — Helper function to return a Dictionary from a found config value string.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.InputActions.cs` (Gauntlet.Automation)


#### class `Gauntlet.Utils.FKey`  
`public class FKey`  
_public; L11-24_
- L13 _public property_ `public string KeyName { get; set; }`
- L15-18 _public ctor_ `public FKey(string InName)`

#### struct `Gauntlet.Utils.FKeyDetails`  
`public struct FKeyDetails`  
_public; L28-171_
- L57 _private field_ `private FKey Key`
- L58 _public field_ `public int PairedAxis = 0`
- L59 _public field_ `public FKey PairedAxisKey`
- L60 _public field_ `public string MenuCategory`
- L62 _public field_ `public int bIsModifierKey`
- L63 _public field_ `public int bIsGamepadKey`
- L64 _public field_ `public int bIsTouch`
- L65 _public field_ `public int bIsMouseButton`
- L66 _public field_ `public int bIsBindableInBlueprints`
- L67 _public field_ `public int bShouldUpdateAxisWithoutSamples`
- L68 _public field_ `public int bIsbindableToActions`
- L69 _public field_ `public int bIsDeprecated`
- L70 _public field_ `public int bIsGesture`
- L71 _public field_ `public EInputAxisType AxisType`
- L73 _public field_ `public string LongDisplayName`
- L74 _public field_ `public string ShortDisplayName`
- L76-109 _public ctor_ `public FKeyDetails(FKey InKey, string InLongDisplayName, string InShortDisplayName = "", int InKeyFlags = 0)`
- L111-114 _public method_ `public FKey GetKey()`
- L116-119 _public method_ `public string GetLongDisplayName()`
- L121-124 _public method_ `public string GetShortDisplayName()`
- L126-129 _public method_ `public bool IsGamepadKey()`
- L131-134 _public method_ `public bool IsModifierKey()`
- L136-139 _public method_ `public bool IsTouch()`
- L141-144 _public method_ `public bool IsMouseButton()`
- L146-149 _public method_ `public bool IsGesture()`
- L151-154 _public method_ `public string GetMenuCategory()`
- L156-159 _public method_ `public int GetPairedAxis()`
- L161-164 _public method_ `public FKey GetPairedAxisKey()`
- L166-169 _public method_ `public EInputAxisType GetAxisType()`

#### enum `Gauntlet.Utils.FKeyDetails.EKeyFlags`  
`public enum EKeyFlags`  
_public; L30-46_
- L32 _public* enumerator_ `GamepadKey = 1 << 0`
- L33 _public* enumerator_ `Touch = 1 << 1`
- L34 _public* enumerator_ `MouseButton = 1 << 2`
- L35 _public* enumerator_ `ModifierKey = 1 << 3`
- L36 _public* enumerator_ `NotBlueprintBindableKey = 1 << 4`
- L37 _public* enumerator_ `Axis1D = 1 << 5`
- L38 _public* enumerator_ `Axis3D = 1 << 6`
- L39 _public* enumerator_ `UpdateAxisWithoutSamples = 1 << 7`
- L40 _public* enumerator_ `NotActionBindableKey = 1 << 8`
- L41 _public* enumerator_ `Deprecated = 1 << 9`
- L42 _public* enumerator_ `ButtonAxis = 1 << 10`
- L43 _public* enumerator_ `Axis2D = 1 << 11`
- L44 _public* enumerator_ `Gesture = 1 << 12`
- L45 _public* enumerator_ `NoFlags = 0`

#### enum `Gauntlet.Utils.FKeyDetails.EInputAxisType`  
`public enum EInputAxisType`  
_public; L48-55_
- L50 _public* enumerator_ `None`
- L51 _public* enumerator_ `Button`
- L52 _public* enumerator_ `Axis1D`
- L53 _public* enumerator_ `Axis2D`
- L54 _public* enumerator_ `Axis3D`

#### struct `Gauntlet.Utils.EKeys`  
`public struct EKeys`  
_public; L173-550_
- L175 _public field_ `public static FKey A = new FKey("A")`
- L176 _public field_ `public static FKey B = new FKey("B")`
- L177 _public field_ `public static FKey C = new FKey("C")`
- L178 _public field_ `public static FKey D = new FKey("D")`
- L179 _public field_ `public static FKey E = new FKey("E")`
- L180 _public field_ `public static FKey F = new FKey("F")`
- L181 _public field_ `public static FKey G = new FKey("G")`
- L182 _public field_ `public static FKey H = new FKey("H")`
- L183 _public field_ `public static FKey I = new FKey("I")`
- L184 _public field_ `public static FKey J = new FKey("J")`
- L185 _public field_ `public static FKey K = new FKey("K")`
- L186 _public field_ `public static FKey L = new FKey("L")`
- L187 _public field_ `public static FKey M = new FKey("M")`
- L188 _public field_ `public static FKey N = new FKey("N")`
- L189 _public field_ `public static FKey O = new FKey("O")`
- L190 _public field_ `public static FKey P = new FKey("P")`
- L191 _public field_ `public static FKey Q = new FKey("Q")`
- L192 _public field_ `public static FKey R = new FKey("R")`
- L193 _public field_ `public static FKey S = new FKey("S")`
- L194 _public field_ `public static FKey T = new FKey("T")`
- L195 _public field_ `public static FKey U = new FKey("U")`
- L196 _public field_ `public static FKey V = new FKey("V")`
- L197 _public field_ `public static FKey W = new FKey("W")`
- L198 _public field_ `public static FKey X = new FKey("X")`
- L199 _public field_ `public static FKey Y = new FKey("Y")`
- L200 _public field_ `public static FKey Z = new FKey("Z")`
- L201 _public field_ `public static FKey MouseX = new FKey("MouseX")`
- L202 _public field_ `public static FKey MouseY = new FKey("MouseY")`
- L203 _public field_ `public static FKey Mouse2D = new FKey("Mouse2D")`
- L204 _public field_ `public static FKey MouseScrollUp = new FKey("MouseScrollUp")`
- L205 _public field_ `public static FKey MouseScrollDown = new FKey("MouseScrollDown")`
- L206 _public field_ `public static FKey MouseWheelAxis = new FKey("MouseWheelAxis")`
- L207 _public field_ `public static FKey LeftMouseButton = new FKey("LeftMouseButton")`
- L208 _public field_ `public static FKey RightMouseButton = new FKey("RightMouseButton")`
- L209 _public field_ `public static FKey MiddleMouseButton = new FKey("MiddleMouseButton")`
- L210 _public field_ `public static FKey ThumbMouseButton = new FKey("ThumbMouseButton")`
- L211 _public field_ `public static FKey ThumbMouseButton2 = new FKey("ThumbMouseButton2")`
- L214 _public field_ `public static FKey BackSpace = new FKey("Backspace")`
- L215 _public field_ `public static FKey Delete = new FKey("Delete")`
- L216 _public field_ `public static FKey Tab = new FKey("Tab")`
- L217 _public field_ `public static FKey Enter = new FKey("Enter")`
- L218 _public field_ `public static FKey Pause = new FKey("Pause")`
- L219 _public field_ `public static FKey CapsLock = new FKey("CapsLock")`
- L220 _public field_ `public static FKey Escape = new FKey("Escape")`
- L221 _public field_ `public static FKey SpaceBar = new FKey("SpaceBar")`
- L222 _public field_ `public static FKey PageUp = new FKey("PageUp")`
- L223 _public field_ `public static FKey PageDown = new FKey("PageDown")`
- L224 _public field_ `public static FKey End = new FKey("End")`
- L225 _public field_ `public static FKey Home = new FKey("Home")`
- L226 _public field_ `public static FKey Left = new FKey("Left")`
- L227 _public field_ `public static FKey Up = new FKey("Up")`
- L228 _public field_ `public static FKey Right = new FKey("Right")`
- L229 _public field_ `public static FKey Down = new FKey("Down")`
- L230 _public field_ `public static FKey Insert = new FKey("Insert")`
- L231 _public field_ `public static FKey Zero = new FKey("0")`
- L232 _public field_ `public static FKey One = new FKey("1")`
- L233 _public field_ `public static FKey Two = new FKey("2")`
- L234 _public field_ `public static FKey Three = new FKey("3")`
- L235 _public field_ `public static FKey Four = new FKey("4")`
- L236 _public field_ `public static FKey Five = new FKey("5")`
- L237 _public field_ `public static FKey Six = new FKey("6")`
- L238 _public field_ `public static FKey Seven = new FKey("7")`
- L239 _public field_ `public static FKey Eight = new FKey("8")`
- L240 _public field_ `public static FKey Nine = new FKey("9")`
- L241 _public field_ `public static FKey NumPadZero = new FKey("NumPadZero")`
- L242 _public field_ `public static FKey NumPadOne = new FKey("NumPadOne")`
- L243 _public field_ `public static FKey NumPadTwo = new FKey("NumPadTwo")`
- L244 _public field_ `public static FKey NumPadThree = new FKey("NumPadThree")`
- L245 _public field_ `public static FKey NumPadFour = new FKey("NumPadFour")`
- L246 _public field_ `public static FKey NumPadFive = new FKey("NumPadFive")`
- L247 _public field_ `public static FKey NumPadSix = new FKey("NumPadSix")`
- L248 _public field_ `public static FKey NumPadSeven = new FKey("NumPadSeven")`
- L249 _public field_ `public static FKey NumPadEight = new FKey("NumPadEight")`
- L250 _public field_ `public static FKey NumPadNine = new FKey("NumPadNine")`
- L251 _public field_ `public static FKey F1 = new FKey("F1")`
- L252 _public field_ `public static FKey F2 = new FKey("F2")`
- L253 _public field_ `public static FKey F3 = new FKey("F3")`
- L254 _public field_ `public static FKey F4 = new FKey("F4")`
- L255 _public field_ `public static FKey F5 = new FKey("F5")`
- L256 _public field_ `public static FKey F6 = new FKey("F6")`
- L257 _public field_ `public static FKey F7 = new FKey("F7")`
- L258 _public field_ `public static FKey F8 = new FKey("F8")`
- L259 _public field_ `public static FKey F9 = new FKey("F9")`
- L260 _public field_ `public static FKey F10 = new FKey("F10")`
- L261 _public field_ `public static FKey F11 = new FKey("F11")`
- L262 _public field_ `public static FKey F12 = new FKey("F12")`
- L263 _public field_ `public static FKey NumLock = new FKey("NumLock")`
- L264 _public field_ `public static FKey LeftShift = new FKey("LeftShift")`
- L265 _public field_ `public static FKey RightShift = new FKey("RightShift")`
- L266 _public field_ `public static FKey LeftControl = new FKey("LeftControl")`
- L267 _public field_ `public static FKey RightControl = new FKey("RightControl")`
- L268 _public field_ `public static FKey LeftAlt = new FKey("LeftAlt")`
- L269 _public field_ `public static FKey RightAlt = new FKey("RightAlt")`
- L270 _public field_ `public static FKey LeftCommand = new FKey("LeftCommand")`
- L271 _public field_ `public static FKey RightCommand = new FKey("RightCommand")`
- L272 _public field_ `public static FKey Semicolon = new FKey("Semicolon")`
- L273 _public field_ `public static FKey EqualsKey = new FKey("Equals")`
- L274 _public field_ `public static FKey Comma = new FKey("Comma")`
- L275 _public field_ `public static FKey Underscore = new FKey("Underscore")`
- L276 _public field_ `public static FKey Hyphen = new FKey("Hyphen")`
- L277 _public field_ `public static FKey Period = new FKey("Period")`
- L278 _public field_ `public static FKey Slash = new FKey("Slash")`
- L279 _public field_ `public static FKey Tilde = new FKey("'")`
- L280 _public field_ `public static FKey LeftBracket = new FKey("LeftBracket")`
- L281 _public field_ `public static FKey Backslash = new FKey("Backslash")`
- L282 _public field_ `public static FKey RightBracket = new FKey("RightBracket")`
- L283 _public field_ `public static FKey Apostrophe = new FKey("Apostrophe")`
- L284 _public field_ `public static FKey Ampersand = new FKey("Ampersand")`
- L285 _public field_ `public static FKey Asterix = new FKey("Asterix")`
- L286 _public field_ `public static FKey Caret = new FKey("Caret")`
- L287 _public field_ `public static FKey Colon = new FKey("Colon")`
- L288 _public field_ `public static FKey Dollar = new FKey("Dollar")`
- L289 _public field_ `public static FKey Exclamation = new FKey("Exclamation")`
- L290 _public field_ `public static FKey LeftParantheses = new FKey("LeftParantheses")`
- L291 _public field_ `public static FKey RightParantheses = new FKey("RightParantheses")`
- L292 _public field_ `public static FKey Quote = new FKey("Quote")`
- L295 _public field_ `public static FKey A_AccentGrave = new FKey($"{(char)224}")`
- L296 _public field_ `public static FKey E_AccentGrave = new FKey($"{(char)232}")`
- L297 _public field_ `public static FKey E_AccentAigu = new FKey($"{(char)233}")`
- L298 _public field_ `public static FKey C_Cedille = new FKey($"{(char)231}")`
- L299 _public field_ `public static FKey Section = new FKey($"{(char)167}")`
- L303 _public field_ `public static FKey Gamepad_Left2D = new FKey("Gamepad_Left2D")`
- L304 _public field_ `public static FKey Gamepad_LeftX = new FKey("Gamepad_LeftX")`
- L305 _public field_ `public static FKey Gamepad_LeftY = new FKey("Gamepad_LeftY")`
- L306 _public field_ `public static FKey Gamepad_Right2D = new FKey("Gamepad_Right2D")`
- L307 _public field_ `public static FKey Gamepad_RightX = new FKey("Gamepad_RightX")`
- L308 _public field_ `public static FKey Gamepad_RightY = new FKey("Gamepad_RightY")`
- L309 _public field_ `public static FKey Gamepad_Special_Left_X = new FKey("Gamepad_Special_Left_X")`
- L310 _public field_ `public static FKey Gamepad_Special_Left_Y = new FKey("Gamepad_Special_Left_Y")`
- L311 _public field_ `public static FKey Gamepad_LeftTrigger = new FKey("Gamepad_LeftTrigger")`
- L312 _public field_ `public static FKey Gamepad_RightTrigger = new FKey("Gamepad_RightTrigger")`
- L313 _public field_ `public static FKey Gamepad_LeftThumbstick = new FKey("Gamepad_LeftThumbstick")`
- L314 _public field_ `public static FKey Gamepad_RightThumbstick = new FKey("Gamepad_RightThumbstick")`
- L315 _public field_ `public static FKey Gamepad_LeftTriggerAxis = new FKey("Gamepad_LeftTriggerAxis")`
- L316 _public field_ `public static FKey Gamepad_RightTriggerAxis = new FKey("Gamepad_RightTriggerAxis")`
- L319 _public field_ `public static FKey Gamepad_DPad_Up = new FKey("Gamepad_DPad_Up")`
- L320 _public field_ `public static FKey Gamepad_DPad_Down = new FKey("Gamepad_DPad_Down")`
- L321 _public field_ `public static FKey Gamepad_DPad_Right = new FKey("Gamepad_DPad_Right")`
- L322 _public field_ `public static FKey Gamepad_DPad_Left = new FKey("Gamepad_DPad_Left")`
- L323 _public field_ `public static FKey Gamepad_LeftStick_Up = new FKey("Gamepad_LeftStick_Up")`
- L324 _public field_ `public static FKey Gamepad_LeftStick_Down = new FKey("Gamepad_LeftStick_Down")`
- L325 _public field_ `public static FKey Gamepad_LeftStick_Right = new FKey("Gamepad_LeftStick_Right")`
- L326 _public field_ `public static FKey Gamepad_LeftStick_Left = new FKey("Gamepad_LeftStick_Left")`
- L327 _public field_ `public static FKey Gamepad_RightStick_Up = new FKey("Gamepad_RightStick_Up")`
- L328 _public field_ `public static FKey Gamepad_RightStick_Down = new FKey("Gamepad_RightStick_Down")`
- L329 _public field_ `public static FKey Gamepad_RightStick_Right = new FKey("Gamepad_RightStick_Right")`
- L330 _public field_ `public static FKey Gamepad_RightStick_Left = new FKey("Gamepad_RightStick_Left")`
- L331 _public field_ `public static FKey Gamepad_Special_Left = new FKey("Gamepad_Special_Left")`
- L332 _public field_ `public static FKey Gamepad_Special_Right = new FKey("Gamepad_Special_Right")`
- L333 _public field_ `public static FKey Gamepad_FaceButton_Bottom = new FKey("Gamepad_FaceButton_Bottom")`
- L334 _public field_ `public static FKey Gamepad_FaceButton_Right = new FKey("Gamepad_FaceButton_Right")`
- L335 _public field_ `public static FKey Gamepad_FaceButton_Left = new FKey("Gamepad_FaceButton_Left")`
- L336 _public field_ `public static FKey Gamepad_FaceButton_Top = new FKey("Gamepad_FaceButton_Top")`
- L337 _public field_ `public static FKey Gamepad_LeftShoulder = new FKey("Gamepad_LeftShoulder")`
- L338 _public field_ `public static FKey Gamepad_RightShoulder = new FKey("Gamepad_RightShoulder")`
- L341 _public field_ `public static FKey Tilt = new FKey("Tilt")`
- L342 _public field_ `public static FKey RotationRate = new FKey("RotationRate")`
- L343 _public field_ `public static FKey Gravity = new FKey("Gravity")`
- L344 _public field_ `public static FKey Acceleration = new FKey("Acceleration")`
- L347 _public field_ `public static FKey Gesture_Pinch = new FKey("Gesture_Pinch")`
- L348 _public field_ `public static FKey Gesture_Flick = new FKey("Gesture_Flick")`
- L349 _public field_ `public static FKey Gesture_Rotate = new FKey("Gesture_Rotate")`
- L352 _public field_ `public static FKey Steam_Touch_0 = new FKey("Steam_Touch_0")`
- L353 _public field_ `public static FKey Steam_Touch_1 = new FKey("Steam_Touch_1")`
- L354 _public field_ `public static FKey Steam_Touch_2 = new FKey("Steam_Touch_2")`
- L355 _public field_ `public static FKey Steam_Touch_3 = new FKey("Steam_Touch_3")`
- L356 _public field_ `public static FKey Steam_Back_Left = new FKey("Steam_Back_Left")`
- L357 _public field_ `public static FKey Steam_Back_Right = new FKey("Steam_Back_Right")`
- L360 _public field_ `public static FKey Global_Menu = new FKey("Global_Menu")`
- L361 _public field_ `public static FKey Global_View = new FKey("Global_View")`
- L362 _public field_ `public static FKey Global_Pause = new FKey("Global_Pause")`
- L363 _public field_ `public static FKey Global_Play = new FKey("Global_Play")`
- L364 _public field_ `public static FKey Global_Back = new FKey("Global_Back")`
- L367 _public field_ `public static FKey Android_Back = new FKey("Android_Back")`
- L368 _public field_ `public static FKey Android_Volume_Up = new FKey("Android_Volume_Up")`
- L369 _public field_ `public static FKey Android_Volume_Down = new FKey("Android_Volume_Down")`
- L370 _public field_ `public static FKey Android_Menu = new FKey("Android_Menu")`
- L373 _public field_ `public static FKey Vive_Left_Grip_Click = new FKey("Vive_Left_Grip_Click")`
- L374 _public field_ `public static FKey Vive_Left_Menu_Click = new FKey("Vive_Left_Menu_Click")`
- L375 _public field_ `public static FKey Vive_Left_Trigger_Click = new FKey("Vive_Left_Trigger_Click")`
- L376 _public field_ `public static FKey Vive_Left_Trigger_Axis = new FKey("Vive_Left_Trigger_Axis")`
- L377 _public field_ `public static FKey Vive_Left_Trackpad_2D = new FKey("Vive_Left_Trackpad_2D")`
- L378 _public field_ `public static FKey Vive_Left_Trackpad_X = new FKey("Vive_Left_Trackpad_X")`
- L379 _public field_ `public static FKey Vive_Left_Trackpad_Y = new FKey("Vive_Left_Trackpad_Y")`
- L380 _public field_ `public static FKey Vive_Left_Trackpad_Click = new FKey("Vive_Left_Trackpad_Click")`
- L381 _public field_ `public static FKey Vive_Left_Trackpad_Touch = new FKey("Vive_Left_Trackpad_Touch")`
- L382 _public field_ `public static FKey Vive_Left_Trackpad_Up = new FKey("Vive_Left_Trackpad_Up")`
- L383 _public field_ `public static FKey Vive_Left_Trackpad_Down = new FKey("Vive_Left_Trackpad_Down")`
- L384 _public field_ `public static FKey Vive_Left_Trackpad_Left = new FKey("Vive_Left_Trackpad_Left")`
- L385 _public field_ `public static FKey Vive_Left_Trackpad_Right = new FKey("Vive_Left_Trackpad_Right")`
- L386 _public field_ `public static FKey Vive_Right_Grip_Click = new FKey("Vive_Right_Grip_Click")`
- L387 _public field_ `public static FKey Vive_Right_Menu_Click = new FKey("Vive_Right_Menu_Click")`
- L388 _public field_ `public static FKey Vive_Right_Trigger_Click = new FKey("Vive_Right_Trigger_Click")`
- L389 _public field_ `public static FKey Vive_Right_Trigger_Axis = new FKey("Vive_Right_Trigger_Axis")`
- L390 _public field_ `public static FKey Vive_Right_Trackpad_2D = new FKey("Vive_Right_Trackpad_2D")`
- L391 _public field_ `public static FKey Vive_Right_Trackpad_X = new FKey("Vive_Right_Trackpad_X")`
- L392 _public field_ `public static FKey Vive_Right_Trackpad_Y = new FKey("Vive_Right_Trackpad_Y")`
- L393 _public field_ `public static FKey Vive_Right_Trackpad_Click = new FKey("Vive_Right_Trackpad_Click")`
- L394 _public field_ `public static FKey Vive_Right_Trackpad_Touch = new FKey("Vive_Right_Trackpad_Touch")`
- L395 _public field_ `public static FKey Vive_Right_Trackpad_Up = new FKey("Vive_Right_Trackpad_Up")`
- L396 _public field_ `public static FKey Vive_Right_Trackpad_Down = new FKey("Vive_Right_Trackpad_Down")`
- L397 _public field_ `public static FKey Vive_Right_Trackpad_Left = new FKey("Vive_Right_Trackpad_Left")`
- L398 _public field_ `public static FKey Vive_Right_Trackpad_Right = new FKey("Vive_Right_Trackpad_Right")`
- L401 _public field_ `public static FKey MixedReality_Left_Menu_Click = new FKey("MixedReality_Left_Menu_Click")`
- L402 _public field_ `public static FKey MixedReality_Left_Grip_Click = new FKey("MixedReality_Left_Grip_Click")`
- L403 _public field_ `public static FKey MixedReality_Left_Trigger_Click = new FKey("MixedReality_Left_Trigger_Click")`
- L404 _public field_ `public static FKey MixedReality_Left_Trigger_Axis = new FKey("MixedReality_Left_Trigger_Axis")`
- L405 _public field_ `public static FKey MixedReality_Left_Thumbstick_2D = new FKey("MixedReality_Left_Thumbstick_2D")`
- L406 _public field_ `public static FKey MixedReality_Left_Thumbstick_X = new FKey("MixedReality_Left_Thumbstick_X")`
- L407 _public field_ `public static FKey MixedReality_Left_Thumbstick_Y = new FKey("MixedReality_Left_Thumbstick_Y")`
- L408 _public field_ `public static FKey MixedReality_Left_Thumbstick_Click = new FKey("MixedReality_Left_Thumbstick_Click")`
- L409 _public field_ `public static FKey MixedReality_Left_Thumbstick_Up = new FKey("MixedReality_Left_Thumbstick_Up")`
- L410 _public field_ `public static FKey MixedReality_Left_Thumbstick_Down = new FKey("MixedReality_Left_Thumbstick_Down")`
- L411 _public field_ `public static FKey MixedReality_Left_Thumbstick_Left = new FKey("MixedReality_Left_Thumbstick_Left")`
- L412 _public field_ `public static FKey MixedReality_Left_Thumbstick_Right = new FKey("MixedReality_Left_Thumbstick_Right")`
- L413 _public field_ `public static FKey MixedReality_Left_Trackpad_2D = new FKey("MixedReality_Left_Trackpad_2D")`
- L414 _public field_ `public static FKey MixedReality_Left_Trackpad_X = new FKey("MixedReality_Left_Trackpad_X")`
- L415 _public field_ `public static FKey MixedReality_Left_Trackpad_Y = new FKey("MixedReality_Left_Trackpad_Y")`
- L416 _public field_ `public static FKey MixedReality_Left_Trackpad_Click = new FKey("MixedReality_Left_Trackpad_Click")`
- L417 _public field_ `public static FKey MixedReality_Left_Trackpad_Touch = new FKey("MixedReality_Left_Trackpad_Touch")`
- L418 _public field_ `public static FKey MixedReality_Left_Trackpad_Up = new FKey("MixedReality_Left_Trackpad_Up")`
- L419 _public field_ `public static FKey MixedReality_Left_Trackpad_Down = new FKey("MixedReality_Left_Trackpad_Down")`
- L420 _public field_ `public static FKey MixedReality_Left_Trackpad_Left = new FKey("MixedReality_Left_Trackpad_Left")`
- L421 _public field_ `public static FKey MixedReality_Left_Trackpad_Right = new FKey("MixedReality_Left_Trackpad_Right")`
- L422 _public field_ `public static FKey MixedReality_Right_Menu_Click = new FKey("MixedReality_Right_Menu_Click")`
- L423 _public field_ `public static FKey MixedReality_Right_Grip_Click = new FKey("MixedReality_Right_Grip_Click")`
- L424 _public field_ `public static FKey MixedReality_Right_Trigger_Click = new FKey("MixedReality_Right_Trigger_Click")`
- L425 _public field_ `public static FKey MixedReality_Right_Trigger_Axis = new FKey("MixedReality_Right_Trigger_Axis")`
- L426 _public field_ `public static FKey MixedReality_Right_Thumbstick_2D = new FKey("MixedReality_Right_Thumbstick_2D")`
- L427 _public field_ `public static FKey MixedReality_Right_Thumbstick_X = new FKey("MixedReality_Right_Thumbstick_X")`
- L428 _public field_ `public static FKey MixedReality_Right_Thumbstick_Y = new FKey("MixedReality_Right_Thumbstick_Y")`
- L429 _public field_ `public static FKey MixedReality_Right_Thumbstick_Click = new FKey("MixedReality_Right_Thumbstick_Click")`
- L430 _public field_ `public static FKey MixedReality_Right_Thumbstick_Up = new FKey("MixedReality_Right_Thumbstick_Up")`
- L431 _public field_ `public static FKey MixedReality_Right_Thumbstick_Down = new FKey("MixedReality_Right_Thumbstick_Down")`
- L432 _public field_ `public static FKey MixedReality_Right_Thumbstick_Left = new FKey("MixedReality_Right_Thumbstick_Left")`
- L433 _public field_ `public static FKey MixedReality_Right_Thumbstick_Right = new FKey("MixedReality_Right_Thumbstick_Right")`
- L434 _public field_ `public static FKey MixedReality_Right_Trackpad_2D = new FKey("MixedReality_Right_Trackpad_2D")`
- L435 _public field_ `public static FKey MixedReality_Right_Trackpad_X = new FKey("MixedReality_Right_Trackpad_X")`
- L436 _public field_ `public static FKey MixedReality_Right_Trackpad_Y = new FKey("MixedReality_Right_Trackpad_Y")`
- L437 _public field_ `public static FKey MixedReality_Right_Trackpad_Click = new FKey("MixedReality_Right_Trackpad_Click")`
- L438 _public field_ `public static FKey MixedReality_Right_Trackpad_Touch = new FKey("MixedReality_Right_Trackpad_Touch")`
- L439 _public field_ `public static FKey MixedReality_Right_Trackpad_Up = new FKey("MixedReality_Right_Trackpad_Up")`
- L440 _public field_ `public static FKey MixedReality_Right_Trackpad_Down = new FKey("MixedReality_Right_Trackpad_Down")`
- L441 _public field_ `public static FKey MixedReality_Right_Trackpad_Left = new FKey("MixedReality_Right_Trackpad_Left")`
- L442 _public field_ `public static FKey MixedReality_Right_Trackpad_Right = new FKey("MixedReality_Right_Trackpad_Right")`
- L445 _public field_ `public static FKey OculusTouch_Left_X_Click = new FKey("OculusTouch_Left_X_Click")`
- L446 _public field_ `public static FKey OculusTouch_Left_Y_Click = new FKey("OculusTouch_Left_Y_Click")`
- L447 _public field_ `public static FKey OculusTouch_Left_X_Touch = new FKey("OculusTouch_Left_X_Touch")`
- L448 _public field_ `public static FKey OculusTouch_Left_Y_Touch = new FKey("OculusTouch_Left_Y_Touch")`
- L449 _public field_ `public static FKey OculusTouch_Left_Menu_Click = new FKey("OculusTouch_Left_Menu_Click")`
- L450 _public field_ `public static FKey OculusTouch_Left_Grip_Click = new FKey("OculusTouch_Left_Grip_Click")`
- L451 _public field_ `public static FKey OculusTouch_Left_Grip_Axis = new FKey("OculusTouch_Left_Grip_Axis")`
- L452 _public field_ `public static FKey OculusTouch_Left_Trigger_Click = new FKey("OculusTouch_Left_Trigger_Click")`
- L453 _public field_ `public static FKey OculusTouch_Left_Trigger_Axis = new FKey("OculusTouch_Left_Trigger_Axis")`
- L454 _public field_ `public static FKey OculusTouch_Left_Trigger_Touch = new FKey("OculusTouch_Left_Trigger_Touch")`
- L455 _public field_ `public static FKey OculusTouch_Left_Thumbstick_2D = new FKey("OculusTouch_Left_Thumbstick_2D")`
- L456 _public field_ `public static FKey OculusTouch_Left_Thumbstick_X = new FKey("OculusTouch_Left_Thumbstick_X")`
- L457 _public field_ `public static FKey OculusTouch_Left_Thumbstick_Y = new FKey("OculusTouch_Left_Thumbstick_Y")`
- L458 _public field_ `public static FKey OculusTouch_Left_Thumbstick_Click = new FKey("OculusTouch_Left_Thumbstick_Click")`
- L459 _public field_ `public static FKey OculusTouch_Left_Thumbstick_Touch = new FKey("OculusTouch_Left_Thumbstick_Touch")`
- L460 _public field_ `public static FKey OculusTouch_Left_Thumbstick_Up = new FKey("OculusTouch_Left_Thumbstick_Up")`
- L461 _public field_ `public static FKey OculusTouch_Left_Thumbstick_Down = new FKey("OculusTouch_Left_Thumbstick_Down")`
- L462 _public field_ `public static FKey OculusTouch_Left_Thumbstick_Left = new FKey("OculusTouch_Left_Thumbstick_Left")`
- L463 _public field_ `public static FKey OculusTouch_Left_Thumbstick_Right = new FKey("OculusTouch_Left_Thumbstick_Right")`
- L464 _public field_ `public static FKey OculusTouch_Right_A_Click = new FKey("OculusTouch_Right_A_Click")`
- L465 _public field_ `public static FKey OculusTouch_Right_B_Click = new FKey("OculusTouch_Right_B_Click")`
- L466 _public field_ `public static FKey OculusTouch_Right_A_Touch = new FKey("OculusTouch_Right_A_Touch")`
- L467 _public field_ `public static FKey OculusTouch_Right_B_Touch = new FKey("OculusTouch_Right_B_Touch")`
- L468 _public field_ `public static FKey OculusTouch_Right_Grip_Click = new FKey("OculusTouch_Right_Grip_Click")`
- L469 _public field_ `public static FKey OculusTouch_Right_Grip_Axis = new FKey("OculusTouch_Right_Grip_Axis")`
- L470 _public field_ `public static FKey OculusTouch_Right_Trigger_Click = new FKey("OculusTouch_Right_Trigger_Click")`
- L471 _public field_ `public static FKey OculusTouch_Right_Trigger_Axis = new FKey("OculusTouch_Right_Trigger_Axis")`
- L472 _public field_ `public static FKey OculusTouch_Right_Trigger_Touch = new FKey("OculusTouch_Right_Trigger_Touch")`
- L473 _public field_ `public static FKey OculusTouch_Right_Thumbstick_2D = new FKey("OculusTouch_Right_Thumbstick_2D")`
- L474 _public field_ `public static FKey OculusTouch_Right_Thumbstick_X = new FKey("OculusTouch_Right_Thumbstick_X")`
- L475 _public field_ `public static FKey OculusTouch_Right_Thumbstick_Y = new FKey("OculusTouch_Right_Thumbstick_Y")`
- L476 _public field_ `public static FKey OculusTouch_Right_Thumbstick_Click = new FKey("OculusTouch_Right_Thumbstick_Click")`
- L477 _public field_ `public static FKey OculusTouch_Right_Thumbstick_Touch = new FKey("OculusTouch_Right_Thumbstick_Touch")`
- L478 _public field_ `public static FKey OculusTouch_Right_Thumbstick_Up = new FKey("OculusTouch_Right_Thumbstick_Up")`
- L479 _public field_ `public static FKey OculusTouch_Right_Thumbstick_Down = new FKey("OculusTouch_Right_Thumbstick_Down")`
- L480 _public field_ `public static FKey OculusTouch_Right_Thumbstick_Left = new FKey("OculusTouch_Right_Thumbstick_Left")`
- L481 _public field_ `public static FKey OculusTouch_Right_Thumbstick_Right = new FKey("OculusTouch_Right_Thumbstick_Right")`
- L484 _public field_ `public static FKey ValveIndex_Left_A_Click = new FKey("ValveIndex_Left_A_Click")`
- L485 _public field_ `public static FKey ValveIndex_Left_B_Click = new FKey("ValveIndex_Left_B_Click")`
- L486 _public field_ `public static FKey ValveIndex_Left_A_Touch = new FKey("ValveIndex_Left_A_Touch")`
- L487 _public field_ `public static FKey ValveIndex_Left_B_Touch = new FKey("ValveIndex_Left_B_Touch")`
- L488 _public field_ `public static FKey ValveIndex_Left_Grip_Axis = new FKey("ValveIndex_Left_Grip_Axis")`
- L489 _public field_ `public static FKey ValveIndex_Left_Grip_Force = new FKey("ValveIndex_Left_Grip_Force")`
- L490 _public field_ `public static FKey ValveIndex_Left_Trigger_Click = new FKey("ValveIndex_Left_Trigger_Click")`
- L491 _public field_ `public static FKey ValveIndex_Left_Trigger_Axis = new FKey("ValveIndex_Left_Trigger_Axis")`
- L492 _public field_ `public static FKey ValveIndex_Left_Trigger_Touch = new FKey("ValveIndex_Left_Trigger_Touch")`
- L493 _public field_ `public static FKey ValveIndex_Left_Thumbstick_2D = new FKey("ValveIndex_Left_Thumbstick_2D")`
- L494 _public field_ `public static FKey ValveIndex_Left_Thumbstick_X = new FKey("ValveIndex_Left_Thumbstick_X")`
- L495 _public field_ `public static FKey ValveIndex_Left_Thumbstick_Y = new FKey("ValveIndex_Left_Thumbstick_Y")`
- L496 _public field_ `public static FKey ValveIndex_Left_Thumbstick_Click = new FKey("ValveIndex_Left_Thumbstick_Click")`
- L497 _public field_ `public static FKey ValveIndex_Left_Thumbstick_Touch = new FKey("ValveIndex_Left_Thumbstick_Touch")`
- L498 _public field_ `public static FKey ValveIndex_Left_Thumbstick_Up = new FKey("ValveIndex_Left_Thumbstick_Up")`
- L499 _public field_ `public static FKey ValveIndex_Left_Thumbstick_Down = new FKey("ValveIndex_Left_Thumbstick_Down")`
- L500 _public field_ `public static FKey ValveIndex_Left_Thumbstick_Left = new FKey("ValveIndex_Left_Thumbstick_Left")`
- L501 _public field_ `public static FKey ValveIndex_Left_Thumbstick_Right = new FKey("ValveIndex_Left_Thumbstick_Right")`
- L502 _public field_ `public static FKey ValveIndex_Left_Trackpad_2D = new FKey("ValveIndex_Left_Trackpad_2D")`
- L503 _public field_ `public static FKey ValveIndex_Left_Trackpad_X = new FKey("ValveIndex_Left_Trackpad_X")`
- L504 _public field_ `public static FKey ValveIndex_Left_Trackpad_Y = new FKey("ValveIndex_Left_Trackpad_Y")`
- L505 _public field_ `public static FKey ValveIndex_Left_Trackpad_Force = new FKey("ValveIndex_Left_Trackpad_Force")`
- L506 _public field_ `public static FKey ValveIndex_Left_Trackpad_Touch = new FKey("ValveIndex_Left_Trackpad_Touch")`
- L507 _public field_ `public static FKey ValveIndex_Left_Trackpad_Up = new FKey("ValveIndex_Left_Trackpad_Up")`
- L508 _public field_ `public static FKey ValveIndex_Left_Trackpad_Down = new FKey("ValveIndex_Left_Trackpad_Down")`
- L509 _public field_ `public static FKey ValveIndex_Left_Trackpad_Left = new FKey("ValveIndex_Left_Trackpad_Left")`
- L510 _public field_ `public static FKey ValveIndex_Left_Trackpad_Right = new FKey("ValveIndex_Left_Trackpad_Right")`
- L511 _public field_ `public static FKey ValveIndex_Right_A_Click = new FKey("ValveIndex_Right_A_Click")`
- L512 _public field_ `public static FKey ValveIndex_Right_B_Click = new FKey("ValveIndex_Right_B_Click")`
- L513 _public field_ `public static FKey ValveIndex_Right_A_Touch = new FKey("ValveIndex_Right_A_Touch")`
- L514 _public field_ `public static FKey ValveIndex_Right_B_Touch = new FKey("ValveIndex_Right_B_Touch")`
- L515 _public field_ `public static FKey ValveIndex_Right_Grip_Axis = new FKey("ValveIndex_Right_Grip_Axis")`
- L516 _public field_ `public static FKey ValveIndex_Right_Grip_Force = new FKey("ValveIndex_Right_Grip_Force")`
- L517 _public field_ `public static FKey ValveIndex_Right_Trigger_Click = new FKey("ValveIndex_Right_Trigger_Click")`
- L518 _public field_ `public static FKey ValveIndex_Right_Trigger_Axis = new FKey("ValveIndex_Right_Trigger_Axis")`
- L519 _public field_ `public static FKey ValveIndex_Right_Trigger_Touch = new FKey("ValveIndex_Right_Trigger_Touch")`
- L520 _public field_ `public static FKey ValveIndex_Right_Thumbstick_2D = new FKey("ValveIndex_Right_Thumbstick_2D")`
- L521 _public field_ `public static FKey ValveIndex_Right_Thumbstick_X = new FKey("ValveIndex_Right_Thumbstick_X")`
- L522 _public field_ `public static FKey ValveIndex_Right_Thumbstick_Y = new FKey("ValveIndex_Right_Thumbstick_Y")`
- L523 _public field_ `public static FKey ValveIndex_Right_Thumbstick_Click = new FKey("ValveIndex_Right_Thumbstick_Click")`
- L524 _public field_ `public static FKey ValveIndex_Right_Thumbstick_Touch = new FKey("ValveIndex_Right_Thumbstick_Touch")`
- L525 _public field_ `public static FKey ValveIndex_Right_Thumbstick_Up = new FKey("ValveIndex_Right_Thumbstick_Up")`
- L526 _public field_ `public static FKey ValveIndex_Right_Thumbstick_Down = new FKey("ValveIndex_Right_Thumbstick_Down")`
- L527 _public field_ `public static FKey ValveIndex_Right_Thumbstick_Left = new FKey("ValveIndex_Right_Thumbstick_Left")`
- L528 _public field_ `public static FKey ValveIndex_Right_Thumbstick_Right = new FKey("ValveIndex_Right_Thumbstick_Right")`
- L529 _public field_ `public static FKey ValveIndex_Right_Trackpad_2D = new FKey("ValveIndex_Right_Trackpad_2D")`
- L530 _public field_ `public static FKey ValveIndex_Right_Trackpad_X = new FKey("ValveIndex_Right_Trackpad_X")`
- L531 _public field_ `public static FKey ValveIndex_Right_Trackpad_Y = new FKey("ValveIndex_Right_Trackpad_Y")`
- L532 _public field_ `public static FKey ValveIndex_Right_Trackpad_Force = new FKey("ValveIndex_Right_Trackpad_Force")`
- L533 _public field_ `public static FKey ValveIndex_Right_Trackpad_Touch = new FKey("ValveIndex_Right_Trackpad_Touch")`
- L534 _public field_ `public static FKey ValveIndex_Right_Trackpad_Up = new FKey("ValveIndex_Right_Trackpad_Up")`
- L535 _public field_ `public static FKey ValveIndex_Right_Trackpad_Down = new FKey("ValveIndex_Right_Trackpad_Down")`
- L536 _public field_ `public static FKey ValveIndex_Right_Trackpad_Left = new FKey("ValveIndex_Right_Trackpad_Left")`
- L537 _public field_ `public static FKey ValveIndex_Right_Trackpad_Right = new FKey("ValveIndex_Right_Trackpad_Right")`
- L539-548 _public ctor_ `public EKeys()`

#### enum `Gauntlet.Utils.EInputEvent`  
`public enum EInputEvent`  
_public; L553-562_
- L555 _public* enumerator_ `IE_Pressed`
- L556 _public* enumerator_ `IE_Released`
- L557 _public* enumerator_ `IE_Repeat`
- L558 _public* enumerator_ `IE_DoubleClick`
- L559 _public* enumerator_ `IE_Axis`
- L560 _public* enumerator_ `IE_Max`

#### class `Gauntlet.Utils.InputAction`  
`public class InputAction(FKey InKey, EInputEvent InInputEvent, double InXDelta = 0, double InYDelta = 0, bool InTapped = false)`  
_public; L564-607_
- L567 _public property_ `public FKey Key { get; }` — attrs: `[JsonPropertyName("inputkey")]`
- L570 _public property_ `public EInputEvent KeyAction { get; }` — attrs: `[JsonPropertyName("inputevent")]`
- L573 _public property_ `public double XDelta { get; }` — attrs: `[JsonPropertyName("xdelta")]`
- L576 _public property_ `public double YDelta { get; }` — attrs: `[JsonPropertyName("ydelta")]`
- L579 _public property_ `public bool Tapped { get; }` — attrs: `[JsonPropertyName("tapped")]`
- L590-606 _public method_ `public Dictionary<string, object> AsRpcArgs()` — Converts the instance's properties into a dictionary suitable for RPC method arguments. Properties decorated with JsonPropertyNameAttribute are serialized and added to the dictionary.

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.MarkdownBuilder.cs` (Gauntlet.Automation)


#### class `Gauntlet.MarkdownBuilder`  
`public class MarkdownBuilder`  
_public; L14-224_
- desc: Helper class to generate text formatted as markdown
- L16 _protected field_ `protected StringBuilder SB`
- L18-21 _public ctor_ `public MarkdownBuilder()`
- L23-26 _public ctor_ `public MarkdownBuilder(string Contents)`
- L32-35 _public method_ `public override string ToString()` — Returns our formatted text
- L40-43 _public property_ `public bool EndsWithNewLine { get; }` — Returns true if the correct body ends with a new line
- L49-57 _public method_ `public MarkdownBuilder EnsureEndsWithNewLine()` — Ensures any text after this starts on a new line
- L65-70 _public method_ `public MarkdownBuilder H1(string Text)` — Insert an H1 Header
- L77-82 _public method_ `public MarkdownBuilder H2(string Text)` — Insert an H2 header
- L89-94 _public method_ `public MarkdownBuilder H3(string Text)` — Insert an H3 header
- L101-106 _public method_ `public MarkdownBuilder H4(string Text)` — Insert an H4 Header
- L113-118 _public method_ `public MarkdownBuilder H5(string Text)` — Insert an H5 header
- L124-128 _public method_ `public MarkdownBuilder NewLine()` — Insert a newline
- L135-144 _public method_ `public MarkdownBuilder HorizontalLine(int Count=80)` — Insert an H5 header
- L151-158 _public method_ `public MarkdownBuilder Paragraph(string Text)` — Insert a paragraph block
- L165-178 _public method_ `public MarkdownBuilder OrderedList(IEnumerable<string> Items)` — Insert an ordered (numbered) list
- L185-199 _public method_ `public MarkdownBuilder UnorderedList(IEnumerable<string> Items)` — Insert an unordered (bulleted) list
- L206-211 _public method_ `public MarkdownBuilder Append(MarkdownBuilder RHS)` — Append the provided Markdown to our body
- L218-223 _public method_ `public MarkdownBuilder Append(string RHS)` — Append the provided text to our body. No formatting will be applied

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.Megazord.cs` (Gauntlet.Automation)


#### class `Gauntlet.MegazordService`  
`public sealed partial class MegazordService`  
_public; L14-27_
- desc: Helper function library for the device farm Megazord API. This is a partial class with platform-specific and restricted implementations in: - Engine/Platforms/ /Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.Megazord.cs

#### class `Gauntlet.MegazordService.MegazordUserResponse`  
`public class MegazordUserResponse`  
_public; L19-26_
- desc: Wrapper for the response from the Megazord users requests
- L25 _public property_ `public string? UserID { get; set; }` — attrs: `[JsonPropertyName("user_id")]` — Identifier of the local user account

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.MinimalReportGenerator.cs` (Gauntlet.Automation)


#### class `Gauntlet.RoleReportData`  
`public class RoleReportData`  
_public; L16-27_
- L18 _public property_ `public DateTime SessionStartTime { get; set; }`
- L19 _public property_ `public ITargetDevice TargetDevice { get; set; }`
- L20 _public property_ `public string RoleType { get; set; }`
- L21 _public property_ `public UnrealTargetPlatform Platform { get; set; }`
- L22 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }`
- L23 _public property_ `public string ProjectName { get; set; }`
- L24 _public property_ `public string HordeArtifactsDir { get; set; }`
- L25 _public property_ `public List<UnrealTestEvent> InitializationEvents { get; set; }`
- L26 _public property_ `public List<UnrealTestEvent> ClosureEvents { get; set; }`

#### class `Gauntlet.MinimalHordeReportGenerator`  
`public class MinimalHordeReportGenerator`  
_public; L28-200_
- L30 _private field_ `private RoleReportData RoleReportData`
- L32-40 _public ctor_ `public MinimalHordeReportGenerator(RoleReportData InRoleReportData)`
- L42-67 _private method_ `private void SetReportMetadata(ITestReport Report)`
- L69-105 _private method_ `private void PopulateClosurePhase(AutomatedTestSessionData TestReport, ITestNode TestNode, string PhaseName = "Closure", DateTime? SessionTime = null, float TimeElapseSeconds = 0)`
- L106-115 _private method_ `private TestDevice AddDeviceToSessionReport(AutomatedTestSessionData TestReport)`
- L120-123 _public method_ `public ITestReport GenerateReport(string TestKey, ITestNode TestNode, PopulateTestPhasesReport OnPopulateTestPhases)` — Generates a Horde report for a test node that has completed.
- L128-186 _public method_ `public ITestReport GenerateReport(string TestKey, ITestNode TestNode, string JsonReportPath, PopulateTestPhasesReport OnPopulateTestPhases)` — Generates a Horde report for a test node that has completed, based on existing Json test data report.
- L188-199 _public method_ `public void SubmitToHorde(ITestReport Report, string ArtifactName, string HordeTestDataPath, string HordeTestDataKey)`

#### Namespace-level symbols

- L14 _public delegate_ `public delegate void PopulateTestPhasesReport(AutomatedTestSessionData TestReport)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.PathUtils.cs` (Gauntlet.Automation)


#### class `Gauntlet.PathUtils`  
`public class PathUtils`  
_public; L9-196_
- L16-24 _public method_ `public static string MakeLongPath(string InPath)` — Converts a path to the long path format if it's not already.
- L31-34 _public method_ `public static string CombineLongPath(params string[] Paths)` — Similar to Path.Combine but creates a long path instead.
- L42-51 _public method_ `public static string FindRelevantPath(string BasePath, params string[] PathNodes)` — Find a path that includes specific directories in the given order, but could also include unknown intermediate directories.
- L58-100 _public method_ `public static string FindRelevantPath(params string[] PathNodes)` — Find a path that includes specific directories in the given order, but could also include unknown intermediate directories.
- L102-160 _private method_ `private static string FindRelevantSubdirectory(string ParentDirectoryPath, string SubdirectoryName, bool bSearchWideFirst = true)`
- L162-195 _private method_ `private static string MatchChildDirectory(string ParentDirectoryPath, string ChildDirectoryName)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.ReportGenUtils.cs` (Gauntlet.Automation)


#### class `Gauntlet.SummaryTableData`  
`public class SummaryTableData`  
_public; L16-26_
- L19 _public property_ `public string CsvId { get; set; }` — attrs: `[JsonIgnore]`
- L21 _public property_ `public string DeviceProfile { get; set; }` — attrs: `[JsonIgnore]`
- L22 _public property_ `public Dictionary<string, double> CsvStatAverage { get; set; }`
- L23 _public property_ `public Dictionary<string, string> CsvMetadata { get; set; }`
- L24 _public property_ `public Dictionary<string, double> SummaryTableMetric { get; set; }`
- L25 _public property_ `public Dictionary<string, string> ToolMetadata { get; set; }`

#### class `Gauntlet.ReportGenUtils`  
`public static class ReportGenUtils`  
_public; L28-527_
- L30 _private field_ `private static string PythonExecutable = null`
- L31 _private field_ `private static string BasePythonLocation`
- L32 _private field_ `private static string DotnetPathLocation`
- L33 _public const_ `public const string CsvBinExt = ".csv.bin"`
- L35-62 _private* ctor_ `static ReportGenUtils()`
- L64-69 _public method_ `public static int RunPerfReportTool(string Args, string ReportXmlBaseDir)`
- L71-92 _public method_ `public static void DirCopy(string SourceDir, string TargetDir, bool bSkipExisting = false, string SearchPattern = "*.*")`
- L94-98 _public method_ `public static string GetCsvToolPath(string ToolName)`
- L100-109 _public method_ `public static int RunPythonScript(string ScriptPath, string Args)`
- L111-128 _public method_ `public static Process RunPythonScriptAsync(string ScriptPath, string Args, bool bRedirectStdOut = false)`
- L130-139 _public method_ `public static int RunCommandlineTool(string ToolPath, string Args)`
- L141-165 _public method_ `public static Process RunCommandlineToolAsync(string ToolPath, string Args, bool bRedirectStdOut = false)`
- L172-175 _public method_ `public static List<FileInfo> ConvertCsvsToBinary(string CsvDirectory)` — Converts the csv files in the given directory into binary.
- L182-221 _public method_ `public static List<FileInfo> ConvertCsvsToBinary(IEnumerable<string> CsvFilePaths)` — Converts the given csv files into binary format.
- L228-231 _public method_ `public static List<FileInfo> ConvertCsvsToBinary(IEnumerable<FileInfo> CsvFiles)` — Converts a list of csv files into binary (.csv.bin).
- L240-243 _public method_ `public static List<FileInfo> CollectAndConvertCsvFilesToBinary(string DirectoryPath, SearchOption Search = SearchOption.AllDirectories)` — Collects all valid csvs (with metadata) within a directory and converts them to binary (.csv.bin). Note: this will not return existing .csv.bin files, only newly converted ones.
- L251-257 _public method_ `public static List<FileInfo> CollectValidCsvFiles(string DirectoryPath, SearchOption Search = SearchOption.AllDirectories)` — Collects all csv files that have valid metadata.
- L268-287 _public method_ `public static ICsvImporter CreatePerfReportServerImporter(string DataSourceName, string BuildName, bool bIsBuildMachine, string ImportDirOverride = null, Dictionary<string, dynamic> CommonDataSourceFields = null)` — Attempts to create the PerfReportServerImporter. This importer is currently internal to Epic and such this function will return null when not used internally.
- L294-297 _public method_ `public static bool IsTestingPreflightBuild(string BuildName)` — Tests if a build is a preflight.
- L299-310 _public method_ `public static void OrderFilenamesByDate(string FilePrefix, string SearchPattern, string Dir)`
- L313-337 _public method_ `public static Dictionary<string, string> ReadCsvMetadataFromDirectory(string CsvDirectoryPath, bool bRecurse = false, string SearchPattern = null)`
- L340-368 _public method_ `public static Dictionary<string, string> ReadCsvMetadata(string CsvFilename, bool bDoLogging = true)`
- L370-381 _public method_ `public static string ReadCsvMetadataValue(string CsvFilename, string Key)`
- L383-386 _public method_ `public static string Quotify(string inStr)`
- L388-392 _public method_ `public static bool BuildVersionValidationCheck(string InBuildVersion, string CsvDirectory, string SearchPattern = null)`
- L394-398 _public method_ `public static bool BuildVersionValidationCheckForCsv(string InBuildVersion, string CsvFilename)`
- L400-405 _public method_ `public static string GetMetadataQueryForLastNDays(int DurationInDays)`
- L407-423 _public method_ `public static bool BuildVersionValidationCheck(string InBuildVersion, Dictionary<string, string> CsvMetadata)`
- L426-444 _public method_ `public static void OverwriteBuildVersionForCsvs(string CsvDirectory, string BuildVersion)`
- L447-526 _public method_ `public static bool GetSummaryTableData(List<FileReference> CsvFiles, out List<SummaryTableData> SummaryTables, out string Error)`

### `Source/Programs/AutomationTool/Gauntlet/Framework/Utils/Gauntlet.ScreenshotCompare.cs` (Gauntlet.Automation)


#### class `Gauntlet.ScreenshotComparisonOptions`  
`public sealed class ScreenshotComparisonOptions`  
_public; L9-18_
- L12 _public property_ `public double Threshold { get; set; }` — Minimum similarity percentage to consider a match (0-100).
- L15 _public property_ `public int ColorTolerance { get; set; }` — Per-channel color difference tolerance (0-255).
- L17 _public property_ `public static ScreenshotComparisonOptions Default => ...`

#### enum `Gauntlet.ScreenshotComparisonStatus`  
`public enum ScreenshotComparisonStatus`  
_public; L20-26_
- L22 _public* enumerator_ `Match`
- L23 _public* enumerator_ `NoMatch`
- L24 _public* enumerator_ `GroundTruthMissing`
- L25 _public* enumerator_ `Error`

#### class `Gauntlet.ScreenshotComparisonResult`  
`public sealed class ScreenshotComparisonResult`  
_public; L28-115_
- L30 _public property_ `public ScreenshotComparisonStatus Status { get; }`
- L31 _public property_ `public bool IsMatch => ...`
- L32 _public property_ `public bool IsGroundTruthMissing => ...`
- L33 _public property_ `public double SimilarityPercent { get; }`
- L34 _public property_ `public int DifferentPixels { get; }`
- L35 _public property_ `public int TotalPixels { get; }`
- L36 _public property_ `public string ActualPath { get; }`
- L37 _public property_ `public string ExpectedPath { get; }`
- L38 _public property_ `public string ErrorMessage { get; }`
- L40-56 _private ctor_ `private ScreenshotComparisonResult( ScreenshotComparisonStatus InStatus, double InSimilarityPercent = 0, int InDifferentPixels = 0, int InTotalPixels = 0, string InActualPath = null, string InExpectedPath = null, string InErrorMessage = null)`
- L58-73 _public method_ `public override string ToString()`
- L75-85 _public method_ `public static ScreenshotComparisonResult Match( double InSimilarity, int InTotal, string InActualPath, string InExpectedPath)`
- L87-98 _public method_ `public static ScreenshotComparisonResult NoMatch( double InSimilarity, int InDifferent, int InTotal, string InActualPath, string InExpectedPath)`
- L100-107 _public method_ `public static ScreenshotComparisonResult GroundTruthMissing( string InCandidatePath, string InExpectedGroundTruthPath)`
- L109-114 _public method_ `public static ScreenshotComparisonResult Error(string InMessage)`

#### class `Gauntlet.ScreenshotCompare`  
`public class ScreenshotCompare`  
_public; L120-197_
- desc: Pixel-level PNG screenshot comparison with no external dependencies.
- L122-143 _public method_ `public static ScreenshotComparisonResult Compare( string InActualPath, string InExpectedPath, ScreenshotComparisonOptions InOptions = null)`
- L145-188 _private method_ `private static ScreenshotComparisonResult ComparePixels( RawImage InActual, RawImage InExpected, string InActualPath, string InExpectedPath, ScreenshotComparisonOptions InOptions)`
- L190-196 _private method_ `private static bool AreColorsWithinTolerance(Pixel InA, Pixel InB, int InTolerance)`

#### class `Gauntlet.PngReader`  
`internal static class PngReader`  
_internal; L202-268_
- desc: Minimal PNG reader. Supports grayscale, RGB, indexed, grayscale+alpha, and RGBA.
- L204 _private field_ `private static readonly byte[] PngSignature = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A }`
- L206-210 _public method_ `public static RawImage Read(string InPath)`
- L212-261 _private method_ `private static RawImage Parse(byte[] InData)`
- L263-267 _private method_ `private static int ReadInt32BigEndian(byte[] InData, int InOffset)`

#### class `Gauntlet.RawImage`  
`internal class RawImage`  
_internal; L270-380_
- L272 _public property_ `public int Width { get; }`
- L273 _public property_ `public int Height { get; }`
- L274 _private field_ `private readonly byte[] Pixels`
- L275 _private field_ `private readonly int BytesPerPixel`
- L276 _private field_ `private readonly int Stride`
- L278-295 _public ctor_ `public RawImage(int InWidth, int InHeight, byte[] InPixels, int InColorType)`
- L297-317 _public method_ `public Pixel GetPixel(int InX, int InY)`
- L319-324 _private method_ `private Pixel GetPixelClamped(int InX, int InY)`
- L326-372 _public method_ `public RawImage Resize(int InTargetWidth, int InTargetHeight)`
- L374-379 _private method_ `private static double Bilerp(double V00, double V10, double V01, double V11, double Fx, double Fy)`

#### struct `Gauntlet.Pixel`  
`internal readonly struct Pixel`  
_internal; L382-393_
- L384 _public property_ `public byte R { get; }`
- L385 _public property_ `public byte G { get; }`
- L386 _public property_ `public byte B { get; }`
- L387 _public property_ `public byte A { get; }`
- L389-392 _public ctor_ `public Pixel(byte InR, byte InG, byte InB, byte InA)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Android/Gauntlet.AndroidBuildSource.cs` (Gauntlet.Automation)


#### class `Gauntlet.AndroidBuild`  
`public class AndroidBuild : IBuild`  
_public; L15-202_
- inherits: `IBuild`
- L17 _public property_ `public int PreferenceOrder { get; }`
- L19 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }`
- L21 _public field_ `public string SourceApkPath`
- L23 _public field_ `public Dictionary<string, string> FilesToInstall`
- L23 _public field_ `public Dictionary< FilesToInstall`
- L25 _public field_ `public string AndroidPackageName`
- L27 _public property_ `public BuildFlags Flags { get; set; }`
- L29 _public property_ `public string Flavor { get; }`
- L31 _public property_ `public UnrealTargetPlatform Platform { get; }`
- L33 _public property_ `public bool SupportsAdditionalFileCopy => ...`
- L35 _public property_ `public bool Is32Bit { get; set; }`
- L37 _public property_ `public bool UsesExternalFilesDir { get; set; }`
- L39 _public property_ `public bool UseAFSWithoutToken { get; set; }`
- L41 _public property_ `public string ParsedAFSToken { get; set; }`
- L43 _public property_ `public bool UsesPublicLogs { get; set; }`
- L45-57 _public ctor_ `public AndroidBuild(UnrealTargetConfiguration InConfig, string InAndroidPackageName, string InApkPath, Dictionary<string, string> InFilesToInstall, BuildFlags InFlags, bool InIs32Bit, bool bInUsesExternalFilesDir, bool bInUsesPublicLogs, bool bInUseAFSWithoutToken = false, string InParsedAFSToken = null)`
- L59-67 _public method_ `public bool CanSupportRole(UnrealTargetRole RoleType)`
- L69-201 _public method_ `public static IEnumerable<AndroidBuild> CreateFromPath(string InProjectName, string InPath)`

#### class `Gauntlet.AndroidBuildSource`  
`public class AndroidBuildSource : IFolderBuildSource`  
_public; L204-284_
- inherits: `IFolderBuildSource`
- L206 _public property_ `public string BuildName { get; }`
- L208-211 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform InPlatform)`
- L213 _public property_ `public string ProjectName { get; set; }`
- L215-217 _public ctor_ `public AndroidBuildSource()`
- L219-276 _public method_ `public List<IBuild> GetBuildsAtPath(string InProjectName, string InPath, int MaxRecursion = 3)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Android/Gauntlet.AndroidPGO.cs` (Gauntlet.Automation)


#### class `Gauntlet.AndroidPGOPlatform`  
`internal class AndroidPGOPlatform : IPGOPlatform`  
_internal; L17-101_
- inherits: `IPGOPlatform`
- desc: Skeleton Android PGO platform implementation (primarily used to test PGO locally with editor builds)
- L19 _private field_ `private readonly string AndroidLlvmProfdataPath`
- L20 _private* field_ `string LocalOutputDirectory`
- L21 _private* field_ `string LocalProfDataFile`
- L23-33 _public ctor_ `public AndroidPGOPlatform()`
- L35-38 _public method_ `public UnrealTargetPlatform GetPlatform()`
- L40-71 _public method_ `public void GatherResults(string ArtifactPath)`
- L73-87 _public method_ `public void ApplyConfiguration(PGOConfig Config)`
- L89-100 _public method_ `public bool TakeScreenshot(ITargetDevice Device, string ScreenshotDirectory, out string ImageFilename)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Android/Gauntlet.TargetDeviceAndroid.cs` (Gauntlet.Automation)


#### class `Gauntlet.TargetDeviceAndroid`  
`public class TargetDeviceAndroid : ITargetDevice`  
_public; L25-1686_
- inherits: `ITargetDevice`
- desc: Android implementation of a device that can run applications
- L28 _public property_ `public string Name { get; set; }`
- L30 _public property_ `public UnrealTargetPlatform? Platform => ...`
- L32 _public property_ `public CommandUtils.ERunOptions RunOptions { get; set; }`
- L34 _public property_ `public bool IsConnected => ...`
- L36-45 _public property_ `public bool IsOn { get; }`
- L47-68 _public property_ `public bool IsAvailable { get; }`
- L74 _public property_ `public string DeviceName { get; set; }` — Low-level device name
- L79 _public property_ `public string LocalCachePath { get; set; }` — Temp path we use to push/pull things from the device
- L84 _public property_ `public string StoragePath { get; set; }` — Root storage path of the device, e.g. /sdcard/
- L89 _public property_ `public string DeviceExternalStorageSavedPath { get; set; }` — External storage path on the device, e.g. /sdcard/UEGame/ etc..
- L94 _public property_ `public string DeviceExternalFilesSavedPath { get; set; }` — External files path on the device, this is the app's own publically accessible data directory e.g. /sdcard/Android/data/[com.package.name]/files/UnrealGame etc..
- L99 _public property_ `public string DeviceArtifactPath { get; set; }` — Saved storage path, e.g. /sdcard/UEGame/Saved (bulk) or /sdcard/Android/data/[com.package.name]/files/UEGame/Saved (notbulk)
- L104 _public property_ `public string DeviceLogPath { get; set; }` — Path to the log file. (This takes public logs setting of the package in to account.)
- L107 _public property_ `public int MaxInstallTime { get; set; }` — attrs: `[AutoParam((int)(60 * 15))]`
- L112 _protected property_ `protected string CommandLineFilePath { get; set; }` — Path to a command line if installed
- L114 _protected field_ `protected bool IsExistingDevice = false`
- L116 _protected field_ `protected Dictionary<EIntendedBaseCopyDirectory, string> LocalDirectoryMappings`
- L116 _protected field_ `protected Dictionary< LocalDirectoryMappings`
- L118 _private field_ `private string NoPlayProtectSetting = null`
- L120 _private field_ `private AndroidAppInstall InstallCache = null`
- L122 _private field_ `private bool bUseAFSWithoutToken`
- L124 _private field_ `private string ParsedAFSToken`
- L126 _private field_ `private Thread ScreenshotThread = null`
- L128 _private field_ `private AutoResetEvent ScreenshotTrigger = null`
- L130-229 _public ctor_ `public TargetDeviceAndroid(string InDeviceName = "", AndroidDeviceData DeviceData = null, string InCachePath = null)`
- L231-234 _private* dtor_ `~TargetDeviceAndroid()`
- L237 _private field_ `private bool DisposedValue = false`
- L239-278 _protected method_ `protected virtual void Dispose(bool disposing)`
- L281-287 _public method_ `public void Dispose()`
- L289-296 _public property_ `public bool Disposed { get; }`
- L301-305 _public method_ `public bool Connect()`
- L307-311 _public method_ `public bool Disconnect(bool bForce = false)`
- L313-319 _public method_ `public bool PowerOn()`
- L320-326 _public method_ `public bool PowerOff()`
- L328-331 _public method_ `public bool Reboot()`
- L333-336 _public method_ `public Dictionary<EIntendedBaseCopyDirectory, string> GetPlatformDirectoryMappings()`
- L338-346 _public method_ `public override string ToString()`
- L348-372 _public method_ `public void FullClean()`
- L374-411 _public method_ `public void CleanArtifacts(UnrealAppConfig AppConfig = null)`
- L413-441 _public method_ `public void InstallBuild(UnrealAppConfig AppConfig)`
- L443-466 _public method_ `public IAppInstall CreateAppInstall(UnrealAppConfig AppConfig)`
- L468-493 _public method_ `public void CopyAdditionalFiles(IEnumerable<UnrealFileToCopy> FilesToCopy)`
- L495-606 _public method_ `public IAppInstance Run(IAppInstall App)`
- L609-642 _public method_ `public void PopulateDirectoryMappings(UnrealAppConfig AppConfig)`
- L644-700 _public method_ `public static bool UsingAndroidFileServer(FileReference RawProjectPath, UnrealTargetConfiguration TargetConfiguration, out bool bEnablePlugin, out string AFSToken, out bool bIsShipping, out bool bIncludeInShipping, out bool bAllowExternalStartInShipping, bool bUseAFSWithoutToken = false, string ParsedAFSToken = null)`
- L702-714 _public method_ `public bool UseAFS(UnrealAppConfig AppConfig)`
- L725-733 _public method_ `public IProcessResult RunAdbDeviceCommand(string Args, bool Wait = true, bool bShouldLogCommand = false, bool bPauseErrorParsing = false, int TimeoutSec = 60 * 15)` — Runs an ADB command, automatically adding the name of the current device to the arguments sent to adb
- L735-743 _public method_ `public IProcessResult RunAFSDeviceCommand(string Args, bool Wait = true, bool bShouldLogCommand = false, bool bPauseErrorParsing = false, int TimeoutSec = 60 * 15)`
- L751-766 _public method_ `public string RunAdbDeviceCommandAndGetOutput(string Args)` — Runs an ADB command, automatically adding the name of the current device to the arguments sent to adb
- L776-807 _public method_ `public static IProcessResult RunAdbGlobalCommand(string Args, bool Wait = true, bool bShouldLogCommand = false, bool bPauseErrorParsing = false, int TimeoutSec = 60 * 15)` — Runs an ADB command at the global scope
- L814-825 _public method_ `public ILongProcessResult RunAdbCommandNoWait(string Args, string LocalCache)` — Run Adb command without waiting for exit
- L827-866 _public method_ `public static IProcessResult RunAFSGlobalCommand(string Args, bool Wait = true, bool bShouldLogCommand = false, bool bPauseErrorParsing = false, int TimeoutSec = 60 * 15)`
- L869-872 _public method_ `public static ITargetDevice[] GetDefaultDevices()`
- L874-890 _public method_ `public void PostRunCleanup(UnrealAppConfig AppConfig, string Package)`
- L892-951 _public method_ `public string AFSGetFileInfo(string PackageName, string AFSToken, string FileName)`
- L953-1152 _public method_ `public bool CopyFileToDevice(string PackageName, string SourcePath, string DestPath, FileReference ProjectFile = null, UnrealTargetConfiguration Configuration = UnrealTargetConfiguration.Unknown, bool IgnoreDependencies = false)`
- L1154-1158 _public method_ `public void AllowDeviceSleepState(bool bAllowSleep)`
- L1162-1173 _public method_ `public void EnablePermissions(string AndroidPackageName)` — Enable Android permissions which would otherwise block automation with permission requests
- L1175-1180 _public method_ `public void KillRunningProcess(string AndroidPackageName)`
- L1182-1271 _protected method_ `protected void CopyOBBFiles(UnrealAppConfig AppConfig, Dictionary<string, string> OBBFiles, string Package)`
- L1273-1298 _protected method_ `protected void CopyCommandlineFile(UnrealAppConfig AppConfig, string Commandline, string Package, string Project, bool bUseExternalFileDirectory)`
- L1300-1316 _protected method_ `protected bool DeleteFileFromDevice(string Package, string DestPath, FileReference ProjectFile = null, UnrealTargetConfiguration Configuration = UnrealTargetConfiguration.Unknown)`
- L1322-1334 _private method_ `private static Dictionary<string, string> GetAllConnectedDevices()` — Returns a list of locally connected devices (e.g. 'adb devices').
- L1336-1340 _private method_ `private static IEnumerable<string> GetAllAvailableDevices()`
- L1342-1351 _private method_ `private void StartScreenshotLoop()`
- L1356-1394 _public method_ `public void StopScreenshotLoop(string OutputDirectory = "")` — Stops Screenshot thread, pulls screenshots from sdcard, and cleans up temp dir on the phone.
- L1398-1415 _public method_ `public void TakeScreenshot(string ScreenshotName)` — Takes a screenshot using adb and saves to the phone's sdcard in a temp directory.
- L1418-1684 _public method_ `public IAppInstall InstallApplication(UnrealAppConfig AppConfig)`

#### class `Gauntlet.AndroidAppInstall`  
`class AndroidAppInstall : IAppInstall`  
_internal*; L1688-1739_
- inherits: `IAppInstall`
- L1690 _public property_ `public string Name { get; set; }`
- L1692 _public property_ `public TargetDeviceAndroid AndroidDevice { get; set; }`
- L1694 _public property_ `public ITargetDevice Device => ...`
- L1696 _public property_ `public string AndroidPackageName { get; set; }`
- L1698 _public property_ `public string CommandLine { get; set; }`
- L1700 _public property_ `public string AppTag { get; set; }`
- L1702 _public property_ `public string ApkPath { get; set; }`
- L1704 _public property_ `public FileReference ProjectFile { get; set; }`
- L1706 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }`
- L1708 _public property_ `public UnrealAppConfig AppConfig { get; set; }`
- L1710-1720 _public ctor_ `public AndroidAppInstall(UnrealAppConfig InAppConfig, TargetDeviceAndroid InDevice, string InName, string InAndroidPackageName, string InCommandLine, FileReference InProjectFile, UnrealTargetConfiguration InConfiguration, string InAppTag = "UE")`
- L1722-1733 _public ctor_ `public AndroidAppInstall(UnrealAppConfig InAppConfig, TargetDeviceAndroid InDevice, string InApkPath, string InName, string InAndroidPackageName, string InCommandLine, FileReference InProjectFile, UnrealTargetConfiguration InConfiguration, string InAppTag = "UE")`
- L1735-1738 _public method_ `public IAppInstance Run()`

#### class `Gauntlet.DefaultAndroidDevices`  
`public class DefaultAndroidDevices : IDefaultDeviceSource`  
_public; L1741-1752_
- inherits: `IDefaultDeviceSource`
- L1743-1746 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L1748-1751 _public method_ `public ITargetDevice[] GetDefaultDevices()`

#### class `Gauntlet.AndroidAppInstance`  
`class AndroidAppInstance : IAppInstance`  
_internal*; L1755-2021_
- inherits: `IAppInstance`
- L1757-1769 _public property_ `public string ArtifactPath { get; }`
- L1771-1789 _public property_ `public bool HasExited { get; }`
- L1791-1798 _public property_ `public string StdOut { get; }`
- L1800-1804 _public method_ `public ILogStreamReader GetLogReader()`
- L1806 _public method_ `public ILogStreamReader GetLogBufferReader()`
- L1808 _public method_ `public bool WriteOutputToFile(string FilePath)`
- L1810 _public property_ `public string CommandLine => ...`
- L1812 _public property_ `public ITargetDevice Device => ...`
- L1814 _public property_ `public int ExitCode => ...`
- L1816 _public property_ `public bool WasKilled { get; set; }`
- L1818 _public field_ `public IProcessResult LaunchProcess`
- L1820 _protected field_ `protected ILongProcessResult LogProcess`
- L1822 _protected field_ `protected TargetDeviceAndroid AndroidDevice`
- L1824 _protected field_ `protected AndroidAppInstall Install`
- L1826 _protected field_ `protected bool bHaveSavedArtifacts`
- L1827 _protected field_ `protected bool bWasCheckedForCrash = false`
- L1829 _private field_ `private bool ActivityExited = false`
- L1831 _public field_ `public AdbScreenRecorder Recorder`
- L1833 _private field_ `private System.Threading.Timer DiagnosticPingTimer`
- L1836-1853 _public ctor_ `public AndroidAppInstance(TargetDeviceAndroid InDevice, AndroidAppInstall InInstall, IProcessResult InProcess)`
- L1855-1864 _public method_ `public int WaitForExit()`
- L1866-1881 _public method_ `public void Kill(bool GenerateDump)`
- L1882-1897 _public method_ `public void StartRecording()`
- L1899-1907 _public method_ `public void StopRecording()`
- L1909-1944 _protected method_ `protected void SaveArtifacts()`
- L1946-1958 _private method_ `private void CheckGeneratedCrashLog()`
- L1963-1990 _private method_ `private bool IsActivityRunning()` — Checks on device whether the activity is running
- L1991-2020 _private method_ `private void PingGoogle(object State)`

#### class `Gauntlet.AndroidCrashParser`  
`static class AndroidCrashParser`  
_internal*; L2026-2136_
- desc: Helper class to parse Android native crash tombstones and generate Unreal compatible log callstack
- L2031-2055 _public method_ `public static string GenerateCrashLog(ILogStreamReader LogReader)` — Parse Android native crash tombstone format to Unreal log format
- L2057-2135 _private method_ `private static List<string> ParseTombstone(ILogStreamReader LogReader, out string SignalInfo)`

#### class `Gauntlet.AdbScreenRecorder`  
`public class AdbScreenRecorder : IDisposable`  
_public; L2138-2233_
- inherits: `IDisposable`
- L2140 _private field_ `private Process ADBProcess`
- L2141 _private field_ `private bool Disposed`
- L2143-2166 _public method_ `public void StartRecording(string Device, string OutputFilePath)`
- L2167-2186 _public method_ `public void StopRecording(int timeout = 500)`
- L2187-2200 _private method_ `private void KillAdbProcess()`
- L2202-2206 _public method_ `public void Dispose()`
- L2208-2227 _protected method_ `protected virtual void Dispose(bool disposing)`
- L2229-2232 _private* dtor_ `~AdbScreenRecorder()`

#### class `Gauntlet.AndroidDeviceData`  
`public sealed class AndroidDeviceData`  
_public; L2236-2246_
- L2239 _public property_ `public string HostIP { get; set; }`
- L2242 _public property_ `public string PublicKey { get; set; }`
- L2245 _public property_ `public string PrivateKey { get; set; }`

#### class `Gauntlet.AndroidBuildSupport`  
`public class AndroidBuildSupport : BaseBuildSupport`  
_public; L2248-2252_
- inherits: `BaseBuildSupport`
- L2250 _protected property_ `protected override BuildFlags SupportedBuildTypes => ...`
- L2251 _protected property_ `protected override UnrealTargetPlatform? Platform => ...`

#### class `Gauntlet.AndroidDeviceFactory`  
`public class AndroidDeviceFactory : IDeviceFactory`  
_public; L2254-2272_
- inherits: `IDeviceFactory`
- L2256-2259 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L2261-2271 _public method_ `public ITargetDevice CreateDevice(string InRef, string InCachePath, string InParam = null)`

#### class `Gauntlet.AdbCredentialCache`  
`internal static class AdbCredentialCache`  
_internal; L2277-2485_
- desc: ADB key credentials, running adb-server commands (must) use same pub/private key store
- L2279 _private field_ `private static int InstanceCount = 0`
- L2280 _private field_ `private static bool bUsingCustomKeys = false`
- L2282 _private field_ `private static string PrivateKey`
- L2283 _private field_ `private static string PublicKey`
- L2285 _private const_ `private const string KeyBackupExt = ".gauntlet.bak"`
- L2287-2290 _private* ctor_ `static AdbCredentialCache()`
- L2292-2316 _public method_ `public static void RemoveInstance()`
- L2318-2352 _public method_ `public static void RestoreBackupKeys()`
- L2354-2458 _public method_ `public static void AddInstance(AndroidDeviceData DeviceData = null)`
- L2460-2471 _private method_ `private static void Reset()`
- L2473-2484 _private method_ `private static void KillAdbServer()`

#### class `Gauntlet.AndroidPlatformSupport`  
`class AndroidPlatformSupport : TargetPlatformSupportBase`  
_internal*; L2487-2491_
- inherits: `TargetPlatformSupportBase`
- L2489 _public property_ `public override UnrealTargetPlatform? Platform => ...`
- L2490 _public method_ `public override bool IsHostMountingSupported()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/IOS/Gauntlet.IMegazordService.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IMegazordService`  
`public partial interface IMegazordService`  
_public; L12-28_
- desc: iOS-specific portion of the IMegazordService contract.
- L19 _public* method_ `Task<string?> GetDeviceLockdownKeyAsync(string Serial)` — Get the base64-encoded lockdown pair record plist for an iOS device by its UUID/serial. Returns null if the device is not found or has no lockdown key.
- L27 _public* method_ `Task<string?> GetDeviceSystemConfigAsync(string Serial)` — Get the base64-encoded SystemConfiguration plist for the host that paired the iOS device. Decoded contents are written to /var/db/lockdown/SystemConfiguration.plist . Returns null if the device is not found or has no system_config recorded.

### `Source/Programs/AutomationTool/Gauntlet/Platform/IOS/Gauntlet.IOSAppium.cs` (Gauntlet.Automation)


#### class `Gauntlet.AppiumContainer`  
`public class AppiumContainer : IDisposable`  
_public; L44-865_
- inherits: `IDisposable`
- desc: AppiumContainer is a wrapper for both an Appium server instance and an AppiumDriver. It's primary use in Gauntlet is for automating dismissal of blocking system notifications that cannot be managed by an MDM profile. Provided you configure your environment correctly, the container will automatically initialize as part of an IOS app instance execution. Steps for configuring your environment: 1. Download appium on your host. It's recommended you use the global npm installation 'npm install -g appium'. 2. For real device testing, you will need a WebDriverAgentRunner.app which is signed with a mobile provision that includes your device. For this you have two options: - Build the app from source. This lets you configure bundle.id's if your signing cert only allows for certain identifiers. - Download the precompiled app and re-sign after replacing the embedded mobileprovision. In either case, you can find both the source and precompiled app on this page https://github.com/appium/WebDriverAge
- L118 _private const_ `private const string AppiumConfigEnvVar = "UE-AppiumConfigPath"`
- L120 _private const_ `private const string AppiumConfigArg = "AppiumConfigPath"`
- L129 _public field_ `public static string AppiumConfigPath = "Engine/Restricted/NotForLicensees/Extras/ThirdPartyNotUE/WebDriverAgent/AppiumConfig.json"` — **REQUIRED** Path to a json file that can be deserialized into the AppiumContainer.Config type This allows users to specify things such as the org id, signing identity, etc. Can be overriden by setting the UE-AppiumConfigPath envvar, or by running with -AppiumConfigPath=/path Path can be relative or absolute
- L135 _public property_ `public static bool Enabled => ...` — Whether or not the appium container is configured properly for use. This requires the appium config path and the appium server path to point to existing files
- L140 _private field_ `private static object Mutex = new()` — Lock object
- L145 _public property_ `public static Config AppiumConfig { get; set; }` — Config file used for the Driver
- L150 _private field_ `private IOSDriver Driver = null` — Driver handle
- L155 _private field_ `private AppiumLocalService Server = null` — Server handle
- L157 _private field_ `private Thread MonitorThread = null`
- L159 _private field_ `private AutoResetEvent MonitorTrigger = null`
- L164 _private field_ `private string UUID = null` — UUID of the device being tests
- L169 _private field_ `private string PackageName = null` — Package name of the app being tested
- L170-195 _private* ctor_ `static AppiumContainer()`
- L197-201 _public ctor_ `public AppiumContainer(string UUID)`
- L204 _private field_ `private bool Disposed = false`
- L205-208 _private* dtor_ `~AppiumContainer()`
- L209-213 _public method_ `public void Dispose()`
- L215-234 _private method_ `private void Dispose(bool bDisposing)`
- L237-369 _public method_ `public void Start(string PackageName)`
- L375-382 _public method_ `public void StartMonitorThread()` — Starts the monitor thread which checks for alerts and takes screenshots Should be called after the app has launched on the device
- L384-402 _public method_ `public void Stop()`
- L410-445 _private method_ `private bool CheckIfWdaInstalled(string deviceUUID, string bundleId)` — Checks if WebDriverAgent is already installed on the device
- L447-485 _private method_ `private void ConfigureDrivers()`
- L487-506 _public method_ `public void VerifyAppInForeground(string packageName, int retries = 5)`
- L508-531 _public method_ `public bool CheckAppInForeground(string appID, int retries = 5)`
- L533-536 _public method_ `public void ForegroundApp(string appID)`
- L543-639 _private method_ `private void CheckAndDismissAlert(string ScreenshotDirectory)` — Checks for and dismisses Apple Sign-On alerts. Used by the monitor loop. Takes a screenshot if an alert is found before dismissing it. Only performs 1 retry attempt.
- L645-711 _private method_ `private bool CheckAndDismissViewPopup(string ScreenshotDirectory)` — Checks for view-based popups that aren't detected as system alerts. Looks for common dismiss buttons like Cancel, Try Again, etc.
- L718-761 _public method_ `public void TakeScreenshot(string OutputDirectory, string ScreenshotName)` — Uses appium WebDriver to take a screenshot. Filename is saved as png in the format of: yy-MM-dd-HH-mm-ss-ff
- L763-815 _private method_ `private void StartMonitorLoop()`
- L821-854 _public method_ `public void StopMonitorLoop(string OutputDirectory = "")` — Stops the monitoring loop (screenshots and alerts), optionally moving all captured images to an output directory
- L856-864 _public method_ `public string GetScreenshotDirectory()`

#### class `Gauntlet.AppiumContainer.Config`  
`public class Config`  
_public; L46-116_
- L51 _public property_ `public string AutomationName { get; set; }` — Name of the automation driver to use. Defaults to XCUITest if not specified
- L56 _public property_ `public string OrgId { get; set; }` — Your company's apple developer team ID
- L61 _public property_ `public string SigningId { get; set; }` — Identity of your signing cert. Usually just 'Apple Development'
- L66 _public property_ `public string WdaAppPath { get; set; }` — Path to a precompiled WebDriverAgentRunner app
- L71 _public property_ `public string WdaBundleId { get; set; }` — Bundle ID of the WebDriverAgent app. Ex: 'com.epicgames.WebDriverAgent'
- L76 _public property_ `public int WdaLaunchTimeoutMs { get; set; }` — Launch Timeout for WebDriverAgent app in ms. Default: 120000ms (increased for VM environments)
- L81 _public property_ `public float ScreenshotPeriod { get; set; }` — How often to take screenshots in seconds. Disabled if <= 0
- L86 _public property_ `public string ScreenshotDirectory { get; set; }` — Path screenshots are output to
- L92 _public property_ `public string AppiumLocation { get; set; }` — Optional - Allow you to override the location of the appium executable. Useful if you opt not to install appium to the global npm root
- L94-115 _public method_ `public AppiumOptions GetCapabilities(string UUID, string PackageName)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/IOS/Gauntlet.IOSBuildSource.cs` (Gauntlet.Automation)


#### class `Gauntlet.AppleBuild`  
`public class AppleBuild : IBuild`  
_public; L15-442_
- inherits: `IBuild`
- L17 _public property_ `public int PreferenceOrder => ...`
- L19 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }`
- L21 _public field_ `public string SourcePath`
- L23 _public field_ `public bool IsIPAFile`
- L25 _public field_ `public string PackageName`
- L27 _public property_ `public BuildFlags Flags { get; set; }`
- L29 _public property_ `public string Flavor => ...`
- L31 _public property_ `public virtual UnrealTargetPlatform Platform { get; }`
- L33 _public property_ `public bool SupportsAdditionalFileCopy { get; }`
- L35 _public property_ `public Dictionary<string, string> BulkContents { get; set; }`
- L37 _private const_ `private const int BulkContentSearchDepth = 3`
- L39-48 _public ctor_ `public AppleBuild(UnrealTargetConfiguration InConfig, string InPackageName, string InSourcePath, BuildFlags InFlags, Dictionary<string, string> InBulkContents = null)`
- L50-58 _public method_ `public bool CanSupportRole(UnrealTargetRole RoleType)`
- L60-78 _internal method_ `internal static IProcessResult ExecuteCommand(String Command, String Arguments)`
- L80-103 _internal method_ `internal static bool ExecuteIPAZipCommand(String Arguments, out String Output, String ShouldExist = "")`
- L106-131 _internal method_ `internal static bool ExecuteIPADittoCommand(String Arguments, out String Output, String ShouldExist = "")`
- L133-173 _private method_ `private static PlistInfo GetPlistInfo(string Source)`
- L252-441 _public method_ `public static T CreateFromPath<T>(string InProjectName, string InRootPath, string InBuildPath, AppleBuildSource<T> BuildSource) where T : AppleBuild`

#### class `Gauntlet.AppleBuild.PlistInfo`  
`private class PlistInfo`  
_private; L175-250_
- L177 _private field_ `private XDocument Document`
- L179-191 _public ctor_ `public PlistInfo(string InContent)`
- L198-220 _public method_ `public string GetFirstValue(string Key)` — Get first value from corresponding key
- L227-249 _public method_ `public IEnumerable<string> GetAllValues(string Key)` — Get all values from corresponding key

#### class `Gauntlet.AppleBuildSource`  
`public abstract class AppleBuildSource<T> : IFolderBuildSource where T : AppleBuild`  
_public; L444-521_
- inherits: `IFolderBuildSource`
- constraints: `where T : AppleBuild`
- L447 _public property_ `public string ProjectName { get; set; }`
- L449 _public property_ `public abstract string CFBundlePlatformName { get; }`
- L451 _public property_ `public string BuildName => ...`
- L453 _protected property_ `protected abstract UnrealTargetPlatform Platform { get; }`
- L455 _protected field_ `protected string BuildFilter`
- L457-460 _public ctor_ `public AppleBuildSource()`
- L462-465 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform InPlatform)`
- L467-520 _public method_ `public virtual List<IBuild> GetBuildsAtPath(string InProjectName, string InPath, int MaxRecursion = 3)`

#### class `Gauntlet.IOSBuild`  
`public class IOSBuild : AppleBuild`  
_public; L523-530_
- inherits: `AppleBuild`
- L525-527 _public ctor_ `public IOSBuild(UnrealTargetConfiguration InConfig, string InPackageName, string InSourcePath, BuildFlags InFlags, Dictionary<string, string> InBulkContents = null) : base(InConfig, InPackageName, InSourcePath, InFlags, InBulkContents)`
- L529 _public property_ `public override UnrealTargetPlatform Platform => ...`

#### class `Gauntlet.IOSBuildSource`  
`public class IOSBuildSource : AppleBuildSource<IOSBuild>`  
_public; L532-536_
- inherits: `AppleBuildSource<IOSBuild>`
- L534 _protected property_ `protected override UnrealTargetPlatform Platform => ...`
- L535 _public property_ `public override string CFBundlePlatformName => ...`

#### class `Gauntlet.TVOSBuild`  
`public class TVOSBuild : AppleBuild`  
_public; L538-545_
- inherits: `AppleBuild`
- L540-542 _public ctor_ `public TVOSBuild(UnrealTargetConfiguration InConfig, string InPackageName, string InSourcePath, BuildFlags InFlags, Dictionary<string, string> InBulkContents = null) : base(InConfig, InPackageName, InSourcePath, InFlags, InBulkContents)`
- L544 _public property_ `public override UnrealTargetPlatform Platform => ...`

#### class `Gauntlet.TVOSBuildSource`  
`public class TVOSBuildSource : AppleBuildSource<TVOSBuild>`  
_public; L547-551_
- inherits: `AppleBuildSource<TVOSBuild>`
- L549 _protected property_ `protected override UnrealTargetPlatform Platform => ...`
- L550 _public property_ `public override string CFBundlePlatformName => ...`

### `Source/Programs/AutomationTool/Gauntlet/Platform/IOS/Gauntlet.IOSPGO.cs` (Gauntlet.Automation)


#### class `Gauntlet.IOSPGOPlatform`  
`internal sealed class IOSPGOPlatform : IPGOPlatform`  
_internal; L14-66_
- inherits: `IPGOPlatform`
- desc: IOS PGO platform implementation (primarily used to test PGO locally with editor builds)
- L16 _private* field_ `string LocalOutputDirectory`
- L17 _private* field_ `string LocalProfDataFile`
- L19 _public method_ `public UnrealTargetPlatform GetPlatform()`
- L21-51 _public method_ `public void GatherResults(string ArtifactPath)`
- L53-59 _public method_ `public void ApplyConfiguration(PGOConfig Config)`
- L61-65 _public method_ `public bool TakeScreenshot(ITargetDevice Device, string ScreenshotDirectory, out string ImageFilename)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/IOS/Gauntlet.TargetDeviceIOS.cs` (Gauntlet.Automation)


#### class `Gauntlet.TargetDeviceIOS`  
`public class TargetDeviceIOS : ITargetDevice`  
_public; L54-1678_
- inherits: `ITargetDevice`
- desc: iOS implementation of a device to run applications
- L78 _public property_ `public static bool UseDeviceCtl { get; set; }` — Whether or not devicectl is used to run most device operations ios-deploy will be used when this is false. This property is set based on the installed version of xcode and the ios version of the device
- L83 _private field_ `private static Dictionary<string, ConnectedDevice> ConnectedDevices` — Collection of devices visible to the UAT host
- L83 _private field_ `private static Dictionary< ConnectedDevices` — Collection of devices visible to the UAT host
- L88 _private field_ `private static int XCodeMajorVersion` — Currently active version of XCode. This can be changed between installed versions using 'xcodes select'
- L94 _private field_ `private static bool bStaticInitialized` — Creating an iOS device requires several queries to be performed first. These results are cached and gated from being refreshed behind this bool
- L99 _private field_ `private static object Mutex = new object()` — Lock object
- L104 _private field_ `private static bool HasCopiedNetworkBuild = false` — Used to prevent re-copies of an entire network share build in the event of a device failure (bulk only)
- L107 _public property_ `public string Name { get; set; }`
- L109 _public property_ `public string IPAddress { get; set; }`
- L111 _public property_ `public UnrealTargetPlatform? Platform => ...`
- L113 _public property_ `public ERunOptions RunOptions { get; set; }`
- L115 _public property_ `public bool IsConnected => ...`
- L117 _public property_ `public bool IsOn => ...`
- L119 _public property_ `public bool IsAvailable => ...`
- L123 _public property_ `public int MaxInstallTime { get; set; }` — attrs: `[AutoParam((int)(60 * 60 * 2.5))]`
- L126 _public property_ `public int MaxPerFileInstallTime { get; set; }` — attrs: `[AutoParam(60 * 15)]`
- L131 _public property_ `public string LocalCachePath { get; set; }` — Temp path we use to push/pull things from the device
- L136 _public property_ `public string UUID { get; set; }` — Low-level device name (uuid)
- L142 _public property_ `public bool UseIOSDeployForCopy { get; set; }` — attrs: `[AutoParam]` — Temporary opt-in flag while we triage devicectl copy hangs
- L144 _protected property_ `protected Dictionary<EIntendedBaseCopyDirectory, string> LocalDirectoryMappings { get; set; }`
- L146 _private field_ `private bool IsDefaultDevice = false`
- L151 _private field_ `private IOSAppInstall InstallCache = null` — Handle to the device's Install
- L153 _public property_ `public AppiumContainer AppiumContainer { get; set; }`
- L155 _private field_ `private List<string> LockdownPlistPaths = new()`
- L157 _private field_ `private readonly IMegazordService MegazordService = InterfaceHelpers.FindImplementations<IMegazordService>(true).FirstOrDefault()`
- L160-270 _public ctor_ `public TargetDeviceIOS(string InName, string InCachePath = null)`
- L273 _private field_ `private bool DisposedValue = false`
- L274-277 _private* dtor_ `~TargetDeviceIOS()`
- L279-292 _protected method_ `protected virtual void Dispose(bool disposing)`
- L294-298 _public method_ `public void Dispose()`
- L302-441 _public method_ `public bool Connect()`
- L443-448 _public method_ `public bool Disconnect(bool bForce = false)`
- L450-453 _public method_ `public bool PowerOn()`
- L455-458 _public method_ `public bool PowerOff()`
- L460-464 _public method_ `public bool Reboot()`
- L466-469 _public method_ `public Dictionary<EIntendedBaseCopyDirectory, string> GetPlatformDirectoryMappings()`
- L470-473 _public method_ `public override string ToString()`
- L475-484 _public method_ `public void TakeScreenshot(string ScreenshotName)`
- L487-557 _public method_ `public void FullClean()`
- L559-573 _public method_ `public void CleanArtifacts(UnrealAppConfig AppConfig = null)`
- L575-763 _public method_ `public void CleanArtifacts(string BundleID, string ProjectName)`
- L765-924 _public method_ `public void InstallBuild(UnrealAppConfig AppConfig)`
- L926-951 _public method_ `public IAppInstall CreateAppInstall(UnrealAppConfig AppConfig)`
- L953-962 _public method_ `public void CopyAdditionalFiles(IEnumerable<UnrealFileToCopy> FilesToCopy)`
- L964-997 _public method_ `public void CopyAdditionalFiles(IEnumerable<UnrealFileToCopy> FilesToCopy, string BundleID)`
- L999-1029 _public method_ `public IProcessResult CopyFileToDevice(string Source, string Destination, string PackageName, int WaitTime = 60, bool bQuiet = false)`
- L1031-1043 _public method_ `public void PopulateDirectoryMappings(string ProjectDirectory)`
- L1045-1121 _public method_ `public IAppInstance Run(IAppInstall Install)`
- L1123-1132 _public method_ `public static IProcessResult ExecuteIOSDeployCommand(string CommandLine, string Device, int WaitTime = 60, bool WarnOnTimeout = true, ERunOptions AdditionalOptions = ERunOptions.None, bool bQuiet = false)`
- L1134-1138 _public method_ `public static ILongProcessResult ExecuteIOSDeployCommandNoWait(string CommandLine, ERunOptions AdditionalOptions = ERunOptions.None, string LocalCache = null, bool bQuiet = false)`
- L1140-1150 _public method_ `public IProcessResult ExecuteIOSDeployCommand(string CommandLine, int WaitTime = 60, bool WarnOnTimeout = true, bool UseDeviceID = true, ERunOptions AdditionalOptions = ERunOptions.None, bool bQuiet = false)`
- L1152-1163 _public method_ `public static IProcessResult ExecuteDevicectlCommand(string CommandLine, string Device, int WaitTime = 60, bool WarnOnTimeout = true, ERunOptions AdditionalOptions = ERunOptions.None, bool bQuiet = false)`
- L1165-1170 _public method_ `public static ILongProcessResult ExecuteDevicectlCommandNoWait(string CommandLine, ERunOptions AdditionalOptions = ERunOptions.None, string LocalCache = null, bool bQuiet = false)`
- L1172-1182 _public method_ `public IProcessResult ExecuteDevicectlCommand(string CommandLine, int WaitTime = 60, bool WarnOnTimeout = true, bool UseDeviceID = true, ERunOptions AdditionalOptions = ERunOptions.None, bool bQuiet = false)`
- L1184-1191 _private method_ `private static string FormatDeviceCopyCommand(string UUID, string Source, string Destination, string PackageName)`
- L1193-1249 _private method_ `private static IProcessResult ExecuteDeploymentCommand(string Executable, string CommandLine, int WaitTime = 60, bool WarnOnTimeout = true, string WorkingDir = null, ERunOptions AdditionalOptions = ERunOptions.None, bool bQuiet = false)`
- L1251-1279 _public method_ `public static ILongProcessResult ExecuteDeploymentCommandNoWait(string Executable, string CommandLine, string WorkingDir = null, ERunOptions AdditionalOptions = ERunOptions.None, string LocalCache = null, bool bQuiet = false)`
- L1281-1331 _private method_ `private static void InitializeDevices()`
- L1333-1352 _private method_ `private static Dictionary<string, ConnectedDevice> GetConnectedDevices()`
- L1354-1475 _private method_ `private static Dictionary<string, ConnectedDevice> GetConnectedDevicesInternal()`
- L1477-1487 _private method_ `private static string GetVolumeName(string InPath)`
- L1489-1510 _private method_ `private static bool ValidateDeviceConnection(JsonObject JsonDevice, bool LogFailure = false)`
- L1512-1614 _private method_ `private void WriteLockdownPairRecord()`
- L1616-1639 _private method_ `private void CleanupLockdownPairRecord()`
- L1646-1670 _private method_ `private string QueryDeviceIPAddress(string DeviceUUID)` — Query the IP address of an iOS device from Megazord API using its UUID
- L1673-1677 _public method_ `public IAppInstall InstallApplication(UnrealAppConfig AppConfig)`

#### class `Gauntlet.TargetDeviceIOS.ConnectedDevice`  
`public class ConnectedDevice`  
_public; L56-71_
- L58 _public field_ `public string UUID`
- L59 _public field_ `public int IOSMajorVersion`
- L60 _public field_ `public bool bConnected`
- L61 _public field_ `public string IPAddress`
- L62 _public field_ `public ITargetDevice AssignedDevice`
- L63 _public property_ `public bool IsAssigned => ...`
- L64-70 _public ctor_ `public ConnectedDevice(string UUID, int IOSMajorVersion, bool bConnected, string IPAddress = null)`

#### class `Gauntlet.IOSAppInstall`  
`class IOSAppInstall : IAppInstall`  
_internal*; L1680-1711_
- inherits: `IAppInstall`
- L1682 _public property_ `public string Name { get; set; }`
- L1684 _public property_ `public string AppPath { get; set; }`
- L1686 _public property_ `public string CommandLine { get; set; }`
- L1688 _public property_ `public string PackageName { get; set; }`
- L1690 _public property_ `public string ProjectName { get; set; }`
- L1692 _public property_ `public ITargetDevice Device => ...`
- L1694 _public field_ `public TargetDeviceIOS IOSDevice`
- L1696-1705 _public ctor_ `public IOSAppInstall(string InName, TargetDeviceIOS InDevice, string InPackageName, string InCommandLine, string InProjectName, string InAppPath = null)`
- L1707-1710 _public method_ `public IAppInstance Run()`

#### class `Gauntlet.IOSAppInstance`  
`class IOSAppInstance : IAppInstance`  
_internal*; L1713-1923_
- inherits: `IAppInstance`
- L1715 _public property_ `public ITargetDevice Device => ...`
- L1716 _public property_ `public TargetDeviceIOS IOSDevice => ...`
- L1717 _public property_ `public ILongProcessResult LaunchProcess { get; set; }`
- L1718 _public property_ `public string CommandLine { get; set; }`
- L1719 _public property_ `public bool WasKilled { get; set; }`
- L1720 _public property_ `public int ExitCode => ...`
- L1721 _public property_ `public bool HasExited => ...`
- L1723-1738 _public property_ `public string ArtifactPath { get; }`
- L1740-1747 _public property_ `public string StdOut { get; }`
- L1748-1762 _private method_ `private void CheckGeneratedCrashLog()`
- L1764-1768 _public method_ `public ILogStreamReader GetLogReader()`
- L1770 _public method_ `public ILogStreamReader GetLogBufferReader()`
- L1772 _public method_ `public bool WriteOutputToFile(string FilePath)`
- L1774 _protected field_ `protected IOSAppInstall Install`
- L1776 _protected field_ `protected bool bHaveSavedArtifacts = false`
- L1777 _protected field_ `protected bool bWasCheckedForCrash = false`
- L1779-1784 _public ctor_ `public IOSAppInstance(IOSAppInstall InInstall, ILongProcessResult InProcess, string InCommandLine)`
- L1786-1794 _public method_ `public int WaitForExit()`
- L1796-1803 _public method_ `public void Kill(bool bGenerateDump = false)`
- L1805-1922 _protected method_ `protected void SaveArtifacts()`

#### class `Gauntlet.LLDBCrashParser`  
`static class LLDBCrashParser`  
_internal*; L1928-2141_
- desc: Helper class to parses LLDB crash threads and generate Unreal compatible log callstack
- L1971-1997 _public method_ `public static string GenerateCrashLog(ILogStreamReader LogReader)` — Parse lldb thread crash dump to Unreal log format
- L1999-2140 _private method_ `private static ThreadInfo ParseCallstack(ILogStreamReader LogReader, out DateTime Timestamp, out int FrameNum)`

#### class `Gauntlet.LLDBCrashParser.FrameInfo`  
`class FrameInfo`  
_private*; L1931-1952_
- L1933 _public field_ `public string Module`
- L1934 _public field_ `public string Symbol = String.Empty`
- L1935 _public field_ `public string Address`
- L1936 _public field_ `public string Offset`
- L1937 _public field_ `public string Source`
- L1938 _public field_ `public string Line`
- L1940-1950 _public method_ `public override string ToString()`

#### class `Gauntlet.LLDBCrashParser.ThreadInfo`  
`class ThreadInfo`  
_private*; L1955-1966_
- L1957 _public field_ `public int Num`
- L1958 _public field_ `public string Status`
- L1959 _public field_ `public bool Current`
- L1960 _public field_ `public List<FrameInfo> Frames = new List<FrameInfo>()`
- L1962-1965 _public method_ `public override string ToString()`

#### class `Gauntlet.IOSDeviceFactory`  
`public class IOSDeviceFactory : IDeviceFactory`  
_public; L2143-2154_
- inherits: `IDeviceFactory`
- L2145-2148 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L2150-2153 _public method_ `public ITargetDevice CreateDevice(string InRef, string InCachePath, string InParam)`

#### class `Gauntlet.IOSBuildSupport`  
`public class IOSBuildSupport : BaseBuildSupport`  
_public; L2156-2160_
- inherits: `BaseBuildSupport`
- L2158 _protected property_ `protected override BuildFlags SupportedBuildTypes => ...`
- L2159 _protected property_ `protected override UnrealTargetPlatform? Platform => ...`

#### class `Gauntlet.IOSPlatformSupport`  
`class IOSPlatformSupport : TargetPlatformSupportBase`  
_internal*; L2162-2166_
- inherits: `TargetPlatformSupportBase`
- L2164 _public property_ `public override UnrealTargetPlatform? Platform => ...`
- L2165 _public method_ `public override bool IsHostMountingSupported()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Linux/Gauntlet.LinuxBuildSources.cs` (Gauntlet.Automation)


#### class `Gauntlet.LinuxBuildSource`  
`public class LinuxBuildSource : StagedBuildSource<StagedBuild>`  
_public; L8-15_
- inherits: `StagedBuildSource<StagedBuild>`
- L10 _public property_ `public override string BuildName { get; }`
- L12 _public property_ `public override UnrealTargetPlatform Platform { get; }`
- L14 _public property_ `public override string PlatformFolderPrefix { get; }`

#### class `Gauntlet.LinuxArmBuildSource`  
`public class LinuxArmBuildSource : StagedBuildSource<StagedBuild>`  
_public; L17-24_
- inherits: `StagedBuildSource<StagedBuild>`
- L19 _public property_ `public override string BuildName { get; }`
- L21 _public property_ `public override UnrealTargetPlatform Platform { get; }`
- L23 _public property_ `public override string PlatformFolderPrefix { get; }`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Linux/Gauntlet.LinuxPGO.cs` (Gauntlet.Automation)


#### class `Gauntlet.LinuxPGOPlatform`  
`internal class LinuxPGOPlatform : IPGOPlatform`  
_internal; L10-33_
- inherits: `IPGOPlatform`
- desc: Skeleton Linux PGO platform implementation (primarily used to test PGO locally with editor builds)
- L13-16 _public method_ `public UnrealTargetPlatform GetPlatform()`
- L18-21 _public method_ `public void GatherResults(string ArtifactPath)`
- L23-26 _public method_ `public void ApplyConfiguration(PGOConfig Config)`
- L28-32 _public method_ `public bool TakeScreenshot(ITargetDevice Device, string ScreenshotDirectory, out string ImageFilename)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Linux/Gauntlet.SelfTest.TestTargetDeviceLinux.cs` (Gauntlet.Automation)


#### class `Gauntlet.SelfTest.TestTargetDeviceLinux`  
`class TestTargetDeviceLinux : TestTargetDevice`  
_internal*; L16-28_
- attrs: `[TestGroup("Devices")]`
- inherits: `TestTargetDevice`
- L18-27 _public method_ `public override void TickTest()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Linux/Gauntlet.SelfTest.TestUnrealInstallAndRunLinux.cs` (Gauntlet.Automation)


#### class `Gauntlet.SelfTest.TestUnrealInstallAndRunLinux`  
`class TestUnrealInstallAndRunLinux : TestUnrealInstallAndRunDesktop`  
_internal*; L7-13_
- inherits: `TestUnrealInstallAndRunDesktop`
- L9-12 _public ctor_ `public TestUnrealInstallAndRunLinux()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Linux/Gauntlet.TargetDeviceLinux.cs` (Gauntlet.Automation)


#### class `Gauntlet.LinuxPlatformSupport`  
`public class LinuxPlatformSupport : TargetPlatformSupportBase`  
_public; L15-20_
- inherits: `TargetPlatformSupportBase`
- desc: Linux Implementation of the Linux Platform Support
- L17 _public property_ `public override UnrealTargetPlatform? Platform => ...`
- L18 _public method_ `public override bool IsHostMountingSupported()`
- L19 _public method_ `public override string GetHostMountedPath(string Path)`

#### class `Gauntlet.TargetDeviceLinux`  
`public class TargetDeviceLinux : TargetDeviceDesktopCommon`  
_public; L25-253_
- inherits: `TargetDeviceDesktopCommon`
- desc: Linux implementation of a device to run applications
- L27 _public property_ `public bool IsArm64 { get; set; }`
- L29-34 _public ctor_ `public TargetDeviceLinux(string InName, string InCacheDir) : base(InName, InCacheDir)`
- L36-42 _public ctor_ `public TargetDeviceLinux(string InName, string InCacheDir, bool InIsArm64) : base(InName, InCacheDir)`
- L44-88 _public method_ `public override IAppInstance Run(IAppInstall App)`
- L90-107 _protected method_ `protected override IAppInstall CreateNativeStagedInstall(UnrealAppConfig AppConfig, NativeStagedBuild Build)`
- L109-127 _protected method_ `protected override IAppInstall CreateStagedInstall(UnrealAppConfig AppConfig, StagedBuild Build)`
- L129-141 _protected method_ `protected override IAppInstall CreateEditorInstall(UnrealAppConfig AppConfig, EditorBuild Build)`
- L145-164 _protected method_ `protected override IAppInstall InstallNativeStagedBuild(UnrealAppConfig AppConfig, NativeStagedBuild InBuild)`
- L166-233 _protected method_ `protected override IAppInstall InstallStagedBuild(UnrealAppConfig AppConfig, StagedBuild InBuild)`
- L235-251 _protected method_ `protected override IAppInstall InstallEditorBuild(UnrealAppConfig AppConfig, EditorBuild Build)`

#### class `Gauntlet.LinuxAppInstall`  
`public class LinuxAppInstall : DesktopCommonAppInstall<TargetDeviceLinux>`  
_public; L255-263_
- inherits: `DesktopCommonAppInstall<TargetDeviceLinux>`
- L258 _public property_ `public TargetDeviceLinux LinuxDevice { get; set; }` — attrs: `[Obsolete("Will be removed in a future release. Use 'DesktopDevice' instead.")]`
- L260-262 _public ctor_ `public LinuxAppInstall(string InName, string InProjectName, TargetDeviceLinux InDevice) : base(InName, InProjectName, InDevice)`

#### class `Gauntlet.LinuxAppContainerInstall`  
`public class LinuxAppContainerInstall : LinuxAppInstall, IContainerized`  
_public; L265-274_
- inherits: `LinuxAppInstall, IContainerized`
- L267 _public property_ `public ContainerInfo ContainerInfo { get; set; }`
- L269-273 _public ctor_ `public LinuxAppContainerInstall(string InName, string InProjectName, ContainerInfo InContainerInfo, TargetDeviceLinux InDevice) : base(InName, InProjectName, InDevice)`

#### class `Gauntlet.LinuxAppInstance`  
`public class LinuxAppInstance : DesktopCommonAppInstance<LinuxAppInstall, TargetDeviceLinux>`  
_public; L276-281_
- inherits: `DesktopCommonAppInstance<LinuxAppInstall, TargetDeviceLinux>`
- L278-280 _public ctor_ `public LinuxAppInstance(LinuxAppInstall InInstall, ILongProcessResult InProcess, string InProcessLogFile = null) : base(InInstall, InProcess, InProcessLogFile)`

#### class `Gauntlet.LinuxDeviceFactory`  
`public class LinuxDeviceFactory : IDeviceFactory`  
_public; L283-294_
- inherits: `IDeviceFactory`
- L285-288 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L290-293 _public method_ `public ITargetDevice CreateDevice(string InRef, string InCachePath, string InParam = null)`

#### class `Gauntlet.LinuxArm64DeviceFactory`  
`public class LinuxArm64DeviceFactory : IDeviceFactory`  
_public; L296-307_
- inherits: `IDeviceFactory`
- L298-301 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L303-306 _public method_ `public ITargetDevice CreateDevice(string InRef, string InCachePath, string InParam = null)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Mac/Gauntlet.MacBuildSource.cs` (Gauntlet.Automation)


#### class `Gauntlet.MacAppChecker`  
`internal static class MacAppChecker`  
_internal; L16-46_
- L18-45 _public method_ `public static bool IsAppBundleUsable(string AppPath, string ProjectName)`

#### class `Gauntlet.MacStagedBuild`  
`public class MacStagedBuild : StagedBuild`  
_public; L48-56_
- inherits: `StagedBuild`
- L50-53 _public ctor_ `public MacStagedBuild(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfig, UnrealTargetRole InRole, string InBuildPath, string InExecutablePath, string InFlavor = "") : base(InPlatform, InConfig, InRole, InBuildPath, InExecutablePath, InFlavor)`
- L55 _public property_ `public override int PreferenceOrder { get; }`

#### class `Gauntlet.MacStagedBuildSource`  
`public class MacStagedBuildSource : StagedBuildSource<MacStagedBuild>`  
_public; L62-75_
- inherits: `StagedBuildSource<MacStagedBuild>`
- desc: Represents a loose collection of files. For Mac the executable will point to the binary.app bundle and not the inner executable file
- L64 _public property_ `public override string BuildName { get; }`
- L66 _public property_ `public override UnrealTargetPlatform Platform { get; }`
- L68 _public property_ `public override string PlatformFolderPrefix { get; }`
- L70-73 _public method_ `public override bool ShouldMakeBuildAvailable(string AppPath)`

#### class `Gauntlet.MacPackagedBuild`  
`public class MacPackagedBuild : PackagedBuild`  
_public; L80-88_
- inherits: `PackagedBuild`
- desc: Represents a packaged mac build. E.g. a Game.app that contains the executable and content
- L82-85 _public ctor_ `public MacPackagedBuild(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfig, UnrealTargetRole InRole, string InBuildPath, BuildFlags InFlags) : base(InPlatform, InConfig, InRole, InBuildPath, InFlags)`
- L87 _public property_ `public override int PreferenceOrder { get; }`

#### class `Gauntlet.MacPackagedBuildSource`  
`public class MacPackagedBuildSource : IFolderBuildSource`  
_public; L93-177_
- inherits: `IFolderBuildSource`
- desc: Build source that discovers packaged builds for Mac. A packaged build is a bundle.app that contains both an executable and UE content
- L95 _public property_ `public string BuildName { get; }`
- L97 _public property_ `public string PlatformFolderPrefix { get; }`
- L99-102 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform InPlatform)`
- L104-176 _public method_ `public List<IBuild> GetBuildsAtPath(string InProjectName, string InPath, int MaxRecursion = 3)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Mac/Gauntlet.SelfTest.TestTargetDeviceMac.cs` (Gauntlet.Automation)


#### class `Gauntlet.SelfTest.TestTargetDeviceMac`  
`class TestTargetDeviceMac : TestTargetDevice`  
_internal*; L16-28_
- attrs: `[TestGroup("Devices")]`
- inherits: `TestTargetDevice`
- L18-27 _public method_ `public override void TickTest()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Mac/Gauntlet.SelfTest.TestUnrealInstallAndRunMac.cs` (Gauntlet.Automation)


#### class `Gauntlet.SelfTest.TestUnrealInstallAndRunMac`  
`class TestUnrealInstallAndRunMac : TestUnrealInstallAndRunDesktop`  
_internal*; L7-13_
- inherits: `TestUnrealInstallAndRunDesktop`
- L9-12 _public ctor_ `public TestUnrealInstallAndRunMac()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Mac/Gauntlet.TargetDeviceMac.cs` (Gauntlet.Automation)


#### class `Gauntlet.TargetDeviceMac`  
`public class TargetDeviceMac : TargetDeviceDesktopCommon`  
_public; L16-382_
- inherits: `TargetDeviceDesktopCommon`
- L18-23 _public ctor_ `public TargetDeviceMac(string InName, string InCachePath) : base(InName, InCachePath)`
- L25-70 _public method_ `public override void InstallBuild(UnrealAppConfig AppConfig)`
- L72-96 _public method_ `public override IAppInstall CreateAppInstall(UnrealAppConfig AppConfig)`
- L98-125 _public method_ `public override IAppInstance Run(IAppInstall App)`
- L127-139 _protected method_ `protected override IAppInstall CreateNativeStagedInstall(UnrealAppConfig AppConfig, NativeStagedBuild Build)`
- L141-148 _protected method_ `protected override IAppInstall CreateStagedInstall(UnrealAppConfig AppConfig, StagedBuild Build)`
- L150-162 _protected method_ `protected override IAppInstall CreateEditorInstall(UnrealAppConfig AppConfig, EditorBuild Build)`
- L164-171 _protected method_ `protected IAppInstall CreatePackagedInstall(UnrealAppConfig AppConfig, MacPackagedBuild Build)`
- L174-187 _protected method_ `protected IAppInstall CreateMacInstall(UnrealAppConfig AppConfig, string BuildPath, string BundlePath)`
- L189-199 _protected method_ `protected string GetVolumeName(string InPath)`
- L206-216 _protected method_ `protected string GetExecutableIfBundle(string InBundlePath)` — If the path is to Foo.app this returns the actual executable to use (e.g. Foo.app/Contents/MacOS/Foo).
- L225-252 _protected method_ `protected string CopyBuildIfNecessary(UnrealAppConfig AppConfig, string InBuildPath)` — Copies a build folder (either a package.app or a folder with a staged built) to a local path if necessary. Necessary is defined as not being on locally attached storage
- L254-268 _private method_ `private string GetTargetBuildDirectory(string BasePath, string Sandbox, string Project, string ProcessType)`
- L272-291 _public method_ `public override IAppInstall InstallApplication(UnrealAppConfig AppConfig)`
- L293-303 _protected method_ `protected override IAppInstall InstallNativeStagedBuild(UnrealAppConfig AppConfig, NativeStagedBuild InBuild)`
- L305-320 _protected method_ `protected override IAppInstall InstallEditorBuild(UnrealAppConfig AppConfig, EditorBuild Build)`
- L322-327 _protected method_ `protected override IAppInstall InstallStagedBuild(UnrealAppConfig AppConfig, StagedBuild Build)`
- L329-333 _protected method_ `protected IAppInstall InstallPackagedBuild(UnrealAppConfig AppConfig, MacPackagedBuild Build)`
- L335-380 _protected method_ `protected IAppInstall InstallBuild(UnrealAppConfig AppConfig, string BuildPath, string BundlePath)`

#### class `Gauntlet.MacAppInstall`  
`public class MacAppInstall : DesktopCommonAppInstall<TargetDeviceMac>`  
_public; L384-396_
- inherits: `DesktopCommonAppInstall<TargetDeviceMac>`
- L387-391 _public property_ `public string LocalPath { get; set; }` — attrs: `[Obsolete("Will be removed in a future release. Use WorkingDirectory instead.")]`
- L393-395 _public ctor_ `public MacAppInstall(string InName, string InProjectName, TargetDeviceMac InDevice) : base(InName, InProjectName, InDevice)`

#### class `Gauntlet.MacAppInstance`  
`public class MacAppInstance : DesktopCommonAppInstance<MacAppInstall, TargetDeviceMac>`  
_public; L398-403_
- inherits: `DesktopCommonAppInstance<MacAppInstall, TargetDeviceMac>`
- L400-402 _public ctor_ `public MacAppInstance(MacAppInstall InInstall, ILongProcessResult InProcess, string ProcessLogFile = null) : base(InInstall, InProcess, ProcessLogFile)`

#### class `Gauntlet.MacDeviceFactory`  
`public class MacDeviceFactory : IDeviceFactory`  
_public; L405-416_
- inherits: `IDeviceFactory`
- L407-410 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L412-415 _public method_ `public ITargetDevice CreateDevice(string InRef, string InCachePath, string InParam = null)`

#### class `Gauntlet.MacPlatformSupport`  
`public class MacPlatformSupport : TargetPlatformSupportBase`  
_public; L418-423_
- inherits: `TargetPlatformSupportBase`
- L420 _public property_ `public override UnrealTargetPlatform? Platform => ...`
- L421 _public method_ `public override bool IsHostMountingSupported()`
- L422 _public method_ `public override string GetHostMountedPath(string Path)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Microsoft/Gauntlet.GDKBuildSource.cs` (Gauntlet.Automation)


#### class `Gauntlet.GDKPackagedBuild`  
`public class GDKPackagedBuild : IBuild`  
_public; L21-164_
- inherits: `IBuild`
- desc: Represents a packaged GDK build that can be installed
- L26 _public property_ `public int PreferenceOrder { get; }` — Preference Order for this build over other types (loose file)
- L31 _public property_ `public UnrealBuildTool.GDK.GDKGameConfigInfo MetaData { get; set; }` — Metadata for this package
- L36 _public property_ `public BuildFlags Flags { get; set; }` — Flags that represent the properties of this build
- L41 _public property_ `public string Flavor => ...` — Flavor of this build.
- L43 _public property_ `public bool SupportsAdditionalFileCopy => ...`
- L48 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }` — Configuration of the executable in this package
- L53 _public property_ `public UnrealTargetPlatform Platform { get; set; }` — Platform that this build runs on
- L58 _public field_ `public string PackageFilename` — Path of this package
- L68-75 _public ctor_ `public GDKPackagedBuild(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfig, BuildFlags InFlags, string InPackageFilename, GDKGameConfigInfo InInfo)` — /Constructor that takes all relevant info
- L82-85 _public method_ `public bool CanSupportRole(UnrealTargetRole Role)` — Packaged builds can only support Clients
- L95-98 _public method_ `public static IEnumerable<GDKPackagedBuild> CreateFromPath(UnrealTargetPlatform InPlatform, string InProjectName, string InPath, string InPackageFileRexEx)` — Attempts to find any packaged builds at the provided path.
- L100-163 _internal method_ `internal static IEnumerable<T> CreateFromPath<T>(UnrealTargetPlatform InPlatform, string InProjectName, string InPath, string InPackageFileRexEx) where T : GDKPackagedBuild`

#### class `Gauntlet.GDKPackagedBuildSource`  
`public abstract class GDKPackagedBuildSource : IFolderBuildSource`  
_public; L169-249_
- inherits: `IFolderBuildSource`
- desc: A build source for GDK that finds and returns packaged builds
- L171 _protected property_ `protected UnrealTargetPlatform Platform { get; set; }`
- L173 _protected property_ `protected string DirectorySearchPattern { get; set; }`
- L175 _public property_ `public string BuildName { get; set; }`
- L177 _public property_ `public string PackageFileExtension { get; set; }`
- L179 _public property_ `public string PackageSuffix { get; set; }`
- L184 _public property_ `public string PackageFileRexEx { get; }` — Regular expression for standard GDK package file name - [PackageName][Suffix].[Extension]
- L191-194 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform InPlatform)` — Platforms we can support
- L196-203 _protected ctor_ `protected GDKPackagedBuildSource( UnrealTargetPlatform InPlatform, string InPackageFileExtension, string InDirectorySearchPattern, string InBuildName, string InPackageSuffix = "")`
- L212-216 _public method_ `public virtual List<IBuild> GetBuildsAtPath(string InProjectName, string InPath, int MaxRecursion = 3)` — Find all builds at the specified path, recursing as specified
- L218-248 _internal method_ `internal List<IBuild> GetBuildsAtPath<T>(string InProjectName, string InPath, int MaxRecursion = 3) where T : GDKPackagedBuild`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Null/Gauntlet.TargetDeviceNull.cs` (Gauntlet.Automation)


#### class `Gauntlet.NullAppInstance`  
`class NullAppInstance : IAppInstance`  
_internal*; L13-62_
- inherits: `IAppInstance`
- L16-20 _public ctor_ `public NullAppInstance(ITargetDevice InDevice)`
- L22-28 _public property_ `public string ArtifactPath { get; }`
- L30 _public property_ `public string CommandLine { get; }`
- L32 _public property_ `public ITargetDevice Device { get; set; }`
- L34 _public property_ `public bool HasExited { get; set; }`
- L36 _public property_ `public bool WasKilled { get; set; }`
- L38 _public property_ `public string StdOut { get; }`
- L40 _public method_ `public ILogStreamReader GetLogReader()`
- L42 _public method_ `public ILogStreamReader GetLogBufferReader()`
- L44 _public method_ `public bool WriteOutputToFile(string FilePath)`
- L46 _public property_ `public int ExitCode { get; }`
- L48-55 _public method_ `public void Kill(bool GenerateDump)`
- L57-61 _public method_ `public int WaitForExit()`

#### class `Gauntlet.NullAppInstall`  
`class NullAppInstall : IAppInstall`  
_internal*; L65-84_
- inherits: `IAppInstall`
- L67 _public property_ `public ITargetDevice Device { get; set; }`
- L69 _public property_ `public string Name { get; set; }`
- L71 _public property_ `public string CommandLine { get; set; }`
- L73-78 _public ctor_ `public NullAppInstall(string InName, TargetDeviceNull InDevice, string InCommandLine)`
- L80-83 _public method_ `public IAppInstance Run()`

#### class `Gauntlet.NullDeviceFactory`  
`public class NullDeviceFactory : IDeviceFactory`  
_public; L86-97_
- inherits: `IDeviceFactory`
- L88-91 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L93-96 _public method_ `public ITargetDevice CreateDevice(string InRef, string InCachePath, string InParam = null)`

#### class `Gauntlet.TargetDeviceNull`  
`public class TargetDeviceNull : ITargetDevice`  
_public; L102-216_
- inherits: `ITargetDevice`
- desc: Win32/64 implementation of a device to run applications
- L104 _public property_ `public string Name { get; set; }`
- L106 _protected property_ `protected Dictionary<EIntendedBaseCopyDirectory, string> LocalDirectoryMappings { get; set; }`
- L108-112 _public ctor_ `public TargetDeviceNull(string InName)`
- L115 _private field_ `private bool disposedValue = false`
- L117-131 _protected method_ `protected virtual void Dispose(bool disposing)`
- L134-140 _public method_ `public void Dispose()`
- L143 _public property_ `public CommandUtils.ERunOptions RunOptions { get; set; }`
- L145-158 _public method_ `public IAppInstance Run(IAppInstall App)`
- L160-163 _public method_ `public IAppInstall InstallApplication(UnrealAppConfig AppConfig)`
- L165-168 _public method_ `public void FullClean()`
- L170-173 _public method_ `public void CleanArtifacts(UnrealAppConfig AppConfig = null)`
- L175 _public property_ `public string LocalCachePath => ...`
- L177-180 _public method_ `public void InstallBuild(UnrealAppConfig AppConfiguration)`
- L182-185 _public method_ `public IAppInstall CreateAppInstall(UnrealAppConfig AppConfig)`
- L187-190 _public method_ `public void CopyAdditionalFiles(IEnumerable<UnrealFileToCopy> FilesToCopy)`
- L192 _public property_ `public UnrealTargetPlatform? Platform { get; }`
- L194 _public property_ `public bool IsAvailable { get; }`
- L195 _public property_ `public bool IsConnected { get; }`
- L196 _public property_ `public bool IsOn { get; }`
- L197 _public method_ `public bool PowerOn()`
- L198 _public method_ `public bool PowerOff()`
- L199 _public method_ `public bool Reboot()`
- L200 _public method_ `public bool Connect()`
- L201 _public method_ `public bool Disconnect(bool bForce = false)`
- L203-206 _public method_ `public override string ToString()`
- L208-215 _public method_ `public Dictionary<EIntendedBaseCopyDirectory, string> GetPlatformDirectoryMappings()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/Gauntlet.SelfTest.TestTargetDeviceWindows.cs` (Gauntlet.Automation)


#### class `Gauntlet.SelfTest.TestTargetDeviceWindows`  
`class TestTargetDeviceWindows : TestTargetDevice`  
_internal*; L16-28_
- attrs: `[TestGroup("Devices")]`
- inherits: `TestTargetDevice`
- L18-27 _public method_ `public override void TickTest()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/Gauntlet.SelfTest.TestUnrealInstallAndRunWindows.cs` (Gauntlet.Automation)


#### class `Gauntlet.SelfTest.TestUnrealInstallAndRunWindows`  
`class TestUnrealInstallAndRunWindows : TestUnrealInstallAndRunDesktop`  
_internal*; L7-13_
- inherits: `TestUnrealInstallAndRunDesktop`
- L9-12 _public ctor_ `public TestUnrealInstallAndRunWindows()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/Gauntlet.TargetDeviceRemoteWin.cs` (Gauntlet.Automation)


#### class `Gauntlet.TargetDeviceRemoteWin`  
`public class TargetDeviceRemoteWin : ITargetDevice`  
_public; L15-177_
- inherits: `ITargetDevice`
- L17-23 _public ctor_ `public TargetDeviceRemoteWin(string InName, string InCacheDir, UnrealTargetPlatform InPlatform)`
- L26 _private field_ `private bool disposedValue = false`
- L28-31 _private* dtor_ `~TargetDeviceRemoteWin()`
- L34-38 _public method_ `public void Dispose()`
- L40-56 _protected method_ `protected virtual void Dispose(bool disposing)`
- L61 _public property_ `public string Name { get; set; }`
- L62 _public property_ `public UnrealTargetPlatform? Platform { get; set; }`
- L63 _public property_ `public CommandUtils.ERunOptions RunOptions { get; set; }`
- L64 _public property_ `public bool IsAvailable => ...`
- L65 _public property_ `public bool IsConnected => ...`
- L66 _public property_ `public bool IsOn => ...`
- L67 _public property_ `public string LocalCachePath { get; set; }`
- L68 _public method_ `public void CleanArtifacts(UnrealAppConfig AppConfig)`
- L69 _public method_ `public bool Connect()`
- L70 _public method_ `public void CopyAdditionalFiles(IEnumerable<UnrealFileToCopy> FilesToCopy)`
- L71 _public method_ `public bool Disconnect(bool bForce = false)`
- L72 _public method_ `public void FullClean()`
- L73 _public method_ `public bool PowerOff()`
- L74 _public method_ `public bool PowerOn()`
- L75 _public method_ `public bool Reboot()`
- L78 _public method_ `public Dictionary<EIntendedBaseCopyDirectory, string> GetPlatformDirectoryMappings()`
- L80-90 _public method_ `public IAppInstall CreateAppInstall(UnrealAppConfig AppConfig)`
- L92-96 _public method_ `public IAppInstall InstallApplication(UnrealAppConfig AppConfig)`
- L98-109 _public method_ `public void InstallBuild(UnrealAppConfig AppConfig)`
- L111-134 _public method_ `public IAppInstance Run(IAppInstall App)`
- L138 _protected property_ `protected Dictionary<EIntendedBaseCopyDirectory, string> LocalDirectoryMappings { get; set; }`
- L140 _public method_ `public override string ToString()`
- L142-160 _protected method_ `protected IAppInstall CreateStagedInstall(UnrealAppConfig AppConfig, StagedBuild Build)`
- L162-171 _protected method_ `protected IAppInstall InstallStagedBuild(UnrealAppConfig AppConfig, StagedBuild Build)`
- L173-176 _protected method_ `protected string GetRemoteRoot(UnrealAppConfig AppConfig)`

#### class `Gauntlet.RemoteWinAppInstance`  
`public class RemoteWinAppInstance : IAppInstance`  
_public; L184-298_
- inherits: `IAppInstance`
- L186 _private property_ `private TargetDeviceRemoteWin TargetDevice { get; set; }`
- L188 _private field_ `private readonly RemoteWinSupport.Placeholder_RemoteWinProcessMonitor ProcessMonitor`
- L190 _private field_ `private readonly object LoggerSyncObject = null`
- L191 _private field_ `private readonly FileLogger Logger = null`
- L194-212 _public ctor_ `public RemoteWinAppInstance(TargetDeviceRemoteWin InTargetDevice, RemoteWinAppInstall WinApp, RemoteWinSupport.Placeholder_RemoteWinProcessMonitor InProcessMonitor)`
- L214-217 _private method_ `private void OnOutputReceived(string Line)`
- L219-227 _public method_ `public void Kill(bool GenerateDumpOnKill = false)`
- L229 _public property_ `public ITargetDevice Device => ...`
- L230-246 _public property_ `public bool HasExited { get; }`
- L247 _public property_ `public bool WasKilled { get; set; }`
- L248 _public property_ `public string CommandLine { get; set; }`
- L251-260 _public property_ `public string StdOut { get; }`
- L262-279 _public property_ `public int ExitCode { get; }`
- L280 _public property_ `public string ArtifactPath => ...`
- L281 _public method_ `public ILogStreamReader GetLogBufferReader()`
- L282 _public method_ `public ILogStreamReader GetLogReader()`
- L283-287 _public method_ `public bool WriteOutputToFile(string FilePath)`
- L288-297 _public method_ `public int WaitForExit()`

#### class `Gauntlet.RemoteWinAppInstall`  
`public class RemoteWinAppInstall : IAppInstall`  
_public; L305-324_
- inherits: `IAppInstall`
- L307-311 _public ctor_ `public RemoteWinAppInstall(string InName, TargetDeviceRemoteWin InTargetDevice)`
- L313 _public property_ `public string Name { get; set; }`
- L314 _public property_ `public ITargetDevice Device => ...`
- L315 _public property_ `public string ExecutablePath { get; set; }`
- L316 _public property_ `public string CommandLine { get; set; }`
- L318 _public property_ `public TargetDeviceRemoteWin TargetDevice { get; set; }`
- L320-323 _public method_ `public IAppInstance Run()`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/Gauntlet.TargetDeviceWindows.cs` (Gauntlet.Automation)


#### class `Gauntlet.TargetDeviceWindows`  
`public class TargetDeviceWindows : TargetDeviceDesktopCommon`  
_public; L22-328_
- inherits: `TargetDeviceDesktopCommon`
- desc: Win32/64 implementation of a device to run applications
- L28 _public property_ `public string Bootstrap { get; set; }` — attrs: `[AutoParam]` — Optional executable that bootstraps the build
- L30-35 _public ctor_ `public TargetDeviceWindows(string InName, string InCacheDir) : base(InName, InCacheDir)`
- L37-46 _public method_ `public override void InstallBuild(UnrealAppConfig AppConfig)`
- L48-72 _public method_ `public override IAppInstall CreateAppInstall(UnrealAppConfig AppConfig)`
- L74-107 _public method_ `public override IAppInstance Run(IAppInstall App)`
- L109-121 _protected method_ `protected override IAppInstall CreateNativeStagedInstall(UnrealAppConfig AppConfig, NativeStagedBuild Build)`
- L123-141 _protected method_ `protected override IAppInstall CreateStagedInstall(UnrealAppConfig AppConfig, StagedBuild Build)`
- L143-155 _protected method_ `protected override IAppInstall CreateEditorInstall(UnrealAppConfig AppConfig, EditorBuild Build)`
- L157-162 _protected method_ `protected IAppInstall CreateSelfInstall(UnrealAppConfig AppConfig, IWindowsSelfInstallingBuild Build)`
- L165-184 _public method_ `public override IAppInstall InstallApplication(UnrealAppConfig AppConfig)`
- L186-207 _protected method_ `protected void BootstrapInstall(WindowsAppInstall Install)`
- L209-221 _protected method_ `protected override IAppInstall InstallNativeStagedBuild(UnrealAppConfig AppConfig, NativeStagedBuild InBuild)`
- L223-292 _protected method_ `protected override IAppInstall InstallStagedBuild(UnrealAppConfig AppConfig, StagedBuild InBuild)`
- L294-312 _protected method_ `protected override IAppInstall InstallEditorBuild(UnrealAppConfig AppConfig, EditorBuild Build)`
- L314-326 _protected method_ `protected IAppInstall InstallSelfInstallingBuild(UnrealAppConfig AppConfig, IWindowsSelfInstallingBuild Build)`

#### class `Gauntlet.WindowsAppInstall`  
`public class WindowsAppInstall : DesktopCommonAppInstall<TargetDeviceWindows>, IAppInstall.IDynamicCommandLine`  
_public; L330-339_
- inherits: `DesktopCommonAppInstall<TargetDeviceWindows>, IAppInstall.IDynamicCommandLine`
- L334 _public property_ `public TargetDeviceWindows WinDevice => ...` — Obsolete! Will be removed in a future release. Use 'DesktopDevice' instead
- L336-338 _public ctor_ `public WindowsAppInstall(string InName, string InProjectName, TargetDeviceWindows InDevice) : base(InName, InProjectName, InDevice)`

#### class `Gauntlet.WindowsAppInstance`  
`public class WindowsAppInstance : DesktopCommonAppInstance<WindowsAppInstall, TargetDeviceWindows>`  
_public; L341-464_
- inherits: `DesktopCommonAppInstance<WindowsAppInstall, TargetDeviceWindows>`
- L344 _private method_ `private static extern bool MiniDumpWriteDump(SafeHandle hProcess, uint ProcessId, SafeHandle hFile, MINIDUMP_TYPE DumpType, IntPtr ExceptionParam, IntPtr UserStreamParam, IntPtr CallbackParam)` — attrs: `[DllImport("dbghelp", SetLastError = true)]`
- L377-379 _public ctor_ `public WindowsAppInstance(WindowsAppInstall InInstall, ILongProcessResult InProcess, string InProcessLogFile = null) : base(InInstall, InProcess, InProcessLogFile)`
- L381-443 _protected method_ `protected override void GenerateDump()`
- L445-463 _private method_ `private static FileReference GetCDBExe()`

#### enum `Gauntlet.WindowsAppInstance.MINIDUMP_TYPE`  
`private enum MINIDUMP_TYPE`  
_private; L346-375_
- L348 _public* enumerator_ `MiniDumpNormal = 0x00000000`
- L349 _public* enumerator_ `MiniDumpWithDataSegs = 0x00000001`
- L350 _public* enumerator_ `MiniDumpWithFullMemory = 0x00000002`
- L351 _public* enumerator_ `MiniDumpWithHandleData = 0x00000004`
- L352 _public* enumerator_ `MiniDumpFilterMemory = 0x00000008`
- L353 _public* enumerator_ `MiniDumpScanMemory = 0x00000010`
- L354 _public* enumerator_ `MiniDumpWithUnloadedModules = 0x00000020`
- L355 _public* enumerator_ `MiniDumpWithIndirectlyReferencedMemory = 0x00000040`
- L356 _public* enumerator_ `MiniDumpFilterModulePaths = 0x00000080`
- L357 _public* enumerator_ `MiniDumpWithProcessThreadData = 0x00000100`
- L358 _public* enumerator_ `MiniDumpWithPrivateReadWriteMemory = 0x00000200`
- L359 _public* enumerator_ `MiniDumpWithoutOptionalData = 0x00000400`
- L360 _public* enumerator_ `MiniDumpWithFullMemoryInfo = 0x00000800`
- L361 _public* enumerator_ `MiniDumpWithThreadInfo = 0x00001000`
- L362 _public* enumerator_ `MiniDumpWithCodeSegs = 0x00002000`
- L363 _public* enumerator_ `MiniDumpWithoutAuxiliaryState = 0x00004000`
- L364 _public* enumerator_ `MiniDumpWithFullAuxiliaryState = 0x00008000`
- L365 _public* enumerator_ `MiniDumpWithPrivateWriteCopyMemory = 0x00010000`
- L366 _public* enumerator_ `MiniDumpIgnoreInaccessibleMemory = 0x00020000`
- L367 _public* enumerator_ `MiniDumpWithTokenInformation = 0x00040000`
- L368 _public* enumerator_ `MiniDumpWithModuleHeaders = 0x00080000`
- L369 _public* enumerator_ `MiniDumpFilterTriage = 0x00100000`
- L370 _public* enumerator_ `MiniDumpWithAvxXStateContext = 0x00200000`
- L371 _public* enumerator_ `MiniDumpWithIptTrace = 0x00400000`
- L372 _public* enumerator_ `MiniDumpScanInaccessiblePartialPages = 0x00800000`
- L373 _public* enumerator_ `MiniDumpFilterWriteCombinedMemory`
- L374 _public* enumerator_ `MiniDumpValidTypeFlags = 0x01ffffff`

#### class `Gauntlet.Win64DeviceFactory`  
`public class Win64DeviceFactory : IDeviceFactory`  
_public; L466-482_
- inherits: `IDeviceFactory`
- L468-471 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform? Platform)`
- L473-481 _public method_ `public ITargetDevice CreateDevice(string InRef, string InCachePath, string InParam = null)`

#### class `Gauntlet.WindowsPlatformSupport`  
`public class WindowsPlatformSupport : TargetPlatformSupportBase`  
_public; L484-489_
- inherits: `TargetPlatformSupportBase`
- L486 _public property_ `public override UnrealTargetPlatform? Platform => ...`
- L487 _public method_ `public override bool IsHostMountingSupported()`
- L488 _public method_ `public override string GetHostMountedPath(string Path)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/Gauntlet.WindowsBuildSources.cs` (Gauntlet.Automation)


#### class `Gauntlet.Win64BuildSource`  
`public class Win64BuildSource : StagedBuildSource<StagedBuild>`  
_public; L11-18_
- inherits: `StagedBuildSource<StagedBuild>`
- L13 _public property_ `public override string BuildName { get; }`
- L15 _public property_ `public override UnrealTargetPlatform Platform { get; }`
- L17 _public property_ `public override string PlatformFolderPrefix { get; }`

#### interface `Gauntlet.IWindowsSelfInstallingBuild`  
`public interface IWindowsSelfInstallingBuild`  
_public; L20-24_
- L22 _public* method_ `void Install(UnrealAppConfig AppConfiguration)`
- L23 _public* method_ `WindowsAppInstall CreateAppInstall(TargetDeviceWindows TargetDevice, UnrealAppConfig AppConfig, out string BasePath)`

#### class `Gauntlet.WindowsStagedBuildFilter`  
`public class WindowsStagedBuildFilter : IStagedBuildFilter`  
_public; L26-73_
- inherits: `IStagedBuildFilter`
- L28 _public property_ `public UnrealTargetPlatform Platform => ...`
- L30-66 _public method_ `public List<FileInfo> GetFilteredFiles(UnrealAppConfig AppConfig, StagedBuild Build)`
- L68-72 _protected method_ `protected virtual bool ShouldFilterFile(UnrealHelpers.ConfigInfo FileConfig, UnrealAppConfig AppConfig, StagedBuild Build)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/Gauntlet.WindowsPGO.cs` (Gauntlet.Automation)


#### class `Gauntlet.WinBasePGOPlatform`  
`internal abstract class WinBasePGOPlatform : IPGOPlatform`  
_internal; L16-138_
- inherits: `IPGOPlatform`
- desc: Skeleton Windows PGO platform implementation (primarily used to test PGO locally with editor builds)
- L18 _private* field_ `string LocalOutputDirectory`
- L19 _private* field_ `string PgcFilenamePrefix`
- L20 _private* field_ `string ExpectedProfrawFileName`
- L22 _private* field_ `UnrealTargetPlatform Platform`
- L24-27 _protected ctor_ `protected WinBasePGOPlatform(UnrealTargetPlatform InPlatform)`
- L29-32 _public method_ `public UnrealTargetPlatform GetPlatform()`
- L34-74 _private method_ `private void GatherResultsMSVC(string PathToPGOArtifacts)`
- L76-80 _private method_ `private void GatherResultsClang()`
- L82-102 _public method_ `public void GatherResults(string ArtifactPath)`
- L104-118 _public method_ `public void ApplyConfiguration(PGOConfig Config)`
- L120 _protected method_ `protected abstract string GetLocalCachePath(ITargetDevice Device)`
- L122-131 _protected method_ `protected void ConfigureDevice(ITargetDevice Device)`
- L133-137 _public method_ `public bool TakeScreenshot(ITargetDevice Device, string ScreenshotDirectory, out string ImageFilename)`

#### class `Gauntlet.WindowsPGOPlatform`  
`internal class WindowsPGOPlatform : WinBasePGOPlatform`  
_internal; L140-155_
- inherits: `WinBasePGOPlatform`
- L142-144 _public ctor_ `public WindowsPGOPlatform() : base(UnrealTargetPlatform.Win64)`
- L146-154 _protected method_ `protected override string GetLocalCachePath(ITargetDevice Device)`

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/MSGaming/Gauntlet.MSGameStoreBuildSource.cs` (Gauntlet.Automation)


#### class `Gauntlet.MSGameStorePackagedBuild`  
`public class MSGameStorePackagedBuild : GDKPackagedBuild, IWindowsSelfInstallingBuild`  
_public; L15-109_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `GDKPackagedBuild, IWindowsSelfInstallingBuild`
- L17-20 _public ctor_ `public MSGameStorePackagedBuild(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfig, BuildFlags InFlags, string InPackageFilename, GDKGameConfigInfo InInfo) : base(InPlatform, InConfig, InFlags, InPackageFilename, InInfo)`
- L22-68 _public method_ `public WindowsAppInstall CreateAppInstall(TargetDeviceWindows TargetDevice, UnrealAppConfig AppConfig, out string BasePath)`
- L70-85 _public method_ `public void Install(UnrealAppConfig AppConfig)`
- L87-108 _private method_ `private void CheckValid(IBuild Build)`

#### class `Gauntlet.MSGameStorePackagedBuildSource`  
`public class MSGameStorePackagedBuildSource : GDKPackagedBuildSource`  
_public; L116-135_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `GDKPackagedBuildSource`
- desc: A build source for MSGameStore that finds and returns packaged builds
- L118-121 _public ctor_ `public MSGameStorePackagedBuildSource() : base( UnrealTargetPlatform.Win64, "msixvc", "Windows*", "Win64PackagedBuildGDK")`
- L131-134 _public method_ `public override List<IBuild> GetBuildsAtPath(string InProjectName, string InPath, int MaxRecursion = 3)` — Find all builds at the specified path, recursing as specified

### `Source/Programs/AutomationTool/Gauntlet/Platform/Windows/MSGaming/Gauntlet.MSGameStoreUtils.cs` (Gauntlet.Automation)


#### class `Gauntlet.MSGameStoreUtils`  
`public class MSGameStoreUtils`  
_public; L19-228_
- desc: Helper functions for using Gauntlet with MSGameStore
- L26-31 _public method_ `public static bool InstallPackage(string PackagePath)` — Installs the provided package
- L38-43 _public method_ `public static bool UninstallPackage(string PackageName)` — Uninstall the provided package
- L50-62 _public method_ `public static IEnumerable<string> GetAUMIDsForInstalledPackage(string PackageFamilyName)` — Given a package family name (ElementalDemo_z844xmwvfmpty) returns all AUMIDs
- L67-76 _public method_ `public static IEnumerable<GDKInstalledApp> GetInstalledApplicationsDetail()` — Returns a collection of installed applications
- L81-96 _public method_ `public static GDKInstalledApp GetInstallApplicationDetail(string PackageFullName)` — Returns the properties for the given package
- L107-149 _public method_ `public static void UninstallPreviousPackageIfNewer(string InPackageFamilyName, string InPackageVersion, bool bRemoveAllPackages = false, bool bRemoveAllStaged = false)` — Uninstalls all previous builds from the given package family if it is newer than the given version, or optionally all matching builds
- L158-169 _public method_ `public static string GetAUMIDForInstalledPackage( string PackageFamilyName, UnrealTargetConfiguration Configuration )` — Given an IdentityName (ElementalDemo_z844xmwvfmpty) and target configuration, returns the best matched AUMID (ElementalDemo_z844xmwvfmpty!AppElementalDemoTest)
- L174-219 _public method_ `public static IProcessResult RunGDKCommand( string Command, string Args = "", bool bWait = true)` — Run the given GDK command
- L224-227 _public method_ `public static string RunGDKCommandAndGetOutput( string Command, string Args = "")` — Run the given GDK command and capture the output

### `Source/Programs/AutomationTool/Gauntlet/Properties/AssemblyInfo.cs` (Gauntlet.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/Gauntlet/Properties/Resources.Designer.cs` (Gauntlet.Automation)


#### class `Gauntlet.Automation.Properties.Resources`  
`internal class Resources`  
_internal; L25-62_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/CookUtils/Checker.cs` (Gauntlet.Automation)


#### class `Gauntlet.Checker`  
`public class Checker`  
_public; L12-61_
- desc: Object that allow to execute several callbacks until they return true.
- L14 _public property_ `public Dictionary<string, Validation> Validations { get; }`
- L16-19 _public ctor_ `public Checker()`
- L26-29 _public method_ `public void AddValidation(string ActionKey, Func<bool> Action)` — Register a callback to validate
- L35-51 _public method_ `public bool PerformValidations()` — Check all callbacks, return true if all passed.
- L57-60 _public method_ `public bool HasValidated(string ActionKey)` — Check the specific callback, return true if it passed and false otherwise.

#### class `Gauntlet.Validation`  
`public class Validation`  
_public; L66-77_
- desc: The class combining a key, a validation callback and its result
- L68 _public property_ `public string ActionKey { get; }`
- L69 _public property_ `public Func<bool> Validate { get; }`
- L70 _public property_ `public bool IsValidated { get; set; }`
- L72-76 _public ctor_ `public Validation(string InActionKey, Func<bool> InValidate)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/CookUtils/ContentFolder.cs` (Gauntlet.Automation)


#### class `Gauntlet.ContentFolder`  
`public class ContentFolder`  
_public; L12-50_
- desc: Keeps a folder and file structure of generated content starting from the given path and is used for comparison using ContentFolderEqualityComparer
- L14 _public property_ `public string Name { get; }`
- L15 _public property_ `public IList<ContentFolder> SubFolders { get; set; }`
- L16 _public property_ `public IList<string> Files { get; set; }`
- L18-23 _public ctor_ `public ContentFolder(string InName)`
- L29-34 _public method_ `public override string ToString()` — The recursive method visualizes a folder/file tree as a string using indentation
- L36-49 _private method_ `private void BuildFolderString(StringBuilder Sb, int IndentLevel)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/CookUtils/ContentFolderEqualityComparer.cs` (Gauntlet.Automation)


#### class `Gauntlet.ContentFolderEqualityComparer`  
`public sealed class ContentFolderEqualityComparer : IEqualityComparer<ContentFolder>`  
_public; L13-41_
- inherits: `IEqualityComparer<ContentFolder>`
- desc: The class defines custom equality comparison logic for ContentFolder objects. Equality refers to the occurrence of a set of expected files/folders in a set of actual files/folders.
- L15-35 _public method_ `public bool Equals(ContentFolder x, ContentFolder y)`
- L37-40 _public method_ `public int GetHashCode(ContentFolder obj)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/CookUtils/ContentFolderReader.cs` (Gauntlet.Automation)


#### class `Gauntlet.ContentFolderReader`  
`public static class ContentFolderReader`  
_public; L12-56_
- desc: The class for reading folder and file structure
- L22-32 _public method_ `public static ContentFolder ReadFolderStructure(string Dir, int Depth)` — Reads folder and file structure from a specific directory and represents it using ContentFolder class. Reading is recursive with read depth limit.
- L34-55 _private method_ `private static void PopulateFolderDetails(ContentFolder Folder, string Dir, int Depth)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/CookUtils/ContentProviders.cs` (Gauntlet.Automation)


#### interface `Gauntlet.ICookedContentProvider`  
`internal interface ICookedContentProvider`  
_internal; L9-12_
- L11 _public* method_ `ContentFolder GetCookedContent()`

#### class `Gauntlet.ContentProviderConfig`  
`internal class ContentProviderConfig`  
_internal; L14-20_
- L16 _public property_ `public UnrealTargetPlatform TargetPlatform { get; set; }`
- L17 _public property_ `public string TargetPlatformName { get; set; }`
- L18 _public property_ `public string ProjectName { get; set; }`
- L19 _public property_ `public bool IsZenStoreUsed { get; set; }`

#### class `Gauntlet.BaseCookedContentProvider`  
`internal class BaseCookedContentProvider(ContentProviderConfig Config) : ICookedContentProvider`  
_internal; L22-65_
- L24 _protected field_ `protected ContentProviderConfig Config = Config`
- L26-64 _public method_ `public virtual ContentFolder GetCookedContent()`

#### class `Gauntlet.WindowsCookedContentProvider`  
`internal class WindowsCookedContentProvider(ContentProviderConfig Config) : BaseCookedContentProvider(Config)`  
_internal; L67-76_
- L69-75 _public method_ `public override ContentFolder GetCookedContent()`

#### class `Gauntlet.LinuxCookedContentProvider`  
`internal class LinuxCookedContentProvider(ContentProviderConfig Config) : BaseCookedContentProvider(Config)`  
_internal; L78-87_
- L80-86 _public method_ `public override ContentFolder GetCookedContent()`

#### class `Gauntlet.MacCookedContentProvider`  
`internal class MacCookedContentProvider(ContentProviderConfig Config) : BaseCookedContentProvider(Config)`  
_internal; L89-98_
- L91-97 _public method_ `public override ContentFolder GetCookedContent()`

#### class `Gauntlet.CookedContentProviderFactory`  
`internal class CookedContentProviderFactory(ContentProviderConfig Config)`  
_internal; L100-119_
- L102 _private field_ `private readonly UnrealTargetPlatform TargetPlatform = Config.TargetPlatform`
- L103 _private field_ `private readonly Dictionary<UnrealTargetPlatform, ICookedContentProvider> ProvidersByPlatform = ...`
- L103 _private field_ `private readonly Dictionary< ProvidersByPlatform = new() { { UnrealTargetPlatform.Win64, new WindowsCookedContentProvider(Config) }, { UnrealTargetPlatform.Linux, new LinuxCookedContentProvider(Config) }, { UnrealTargetPlatform.Mac, new MacCookedConte ...`
- L110-118 _public method_ `public ICookedContentProvider GetProvider()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/CookUtils/CookHelpers.cs` (Gauntlet.Automation)


#### class `Gauntlet.CookHelpers`  
`internal static class CookHelpers`  
_internal; L9-64_
- L11-23 _internal method_ `internal static bool TryLaunchDeferredRole(UnrealSessionInstance TestInstance, UnrealTargetRole RoleType)`
- L25-28 _internal method_ `internal static IAppInstance[] GetRunningInstances(UnrealSession UnrealApp)`
- L30-33 _internal method_ `internal static IAppInstance GetRunningInstance(UnrealSession UnrealApp, UnrealTargetRole RoleType)`
- L35-38 _internal method_ `internal static bool HaveAllInstancesExited(UnrealSession UnrealApp)`
- L42-53 _internal method_ `internal static UnrealTestRole AddRequiredRole(UnrealTestConfiguration Config, UnrealTargetRole InRole)`
- L55-58 _private method_ `private static IEnumerable<RoleInstance> GetRunningRoles(UnrealSession UnrealApp)`
- L60-63 _private method_ `private static IEnumerable<RoleInstance> GetAllRoles(UnrealSession UnrealApp)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.Automation.cs` (Gauntlet.Automation)


#### class `UE.AutomationTestConfig`  
`public class AutomationTestConfig : UnrealTestConfiguration`  
_public; L20-384_
- inherits: `UnrealTestConfiguration`
- desc: Define a Config class for UE.EditorAutomation and UE.TargetAutomation with the options that can be used
- L26 _public field_ `public string RHI = ""` — attrs: `[AutoParam]` — Run with specific RHI
- L57 _public property_ `public virtual bool RHIValidation { get; set; }` — attrs: `[AutoParam]` — Enable the RHI validation layer.
- L63 _public field_ `public bool PreferNvidia = false` — attrs: `[AutoParam]` — Run with Nvidia cards for raytracing support
- L69 _public field_ `public bool RayTracing = false` — attrs: `[AutoParam]` — Run forcing raytracing
- L75 _public field_ `public bool StompMalloc = false` — attrs: `[AutoParam]` — Run forcing raytracing
- L81 _public field_ `public bool D3DDebug = false` — attrs: `[AutoParam]` — Run with d3ddebug
- L87 _public field_ `public bool AttachRenderDoc = false` — attrs: `[AutoParam]` — Attach to RenderDoc to capture frame traces for image based tests
- L93 _public field_ `public string RunTest = ""` — attrs: `[AutoParam]` — Filter or groups of tests to apply
- L99 _public field_ `public string ReportExportPath = ""` — attrs: `[AutoParam]` — Absolute or project relative path to write an automation report to.
- L105 _public field_ `public string ReportURL = ""` — attrs: `[AutoParam]` — Path the report can be found at
- L111 _public field_ `public string TelemetryDirectory = ""` — attrs: `[AutoParam]` — Absolute or project relative directory path to write automation telemetry outputs.
- L117 _public property_ `public virtual bool SimpleHordeReport { get; set; }` — attrs: `[AutoParam]` — Use Simple Horde Report instead of Unreal Automated Tests
- L123 _public field_ `public bool ResumeOnCriticalFailure = false` — attrs: `[AutoParam]` — Resume test run on critical failure through pass retry
- L129 _public field_ `public bool VerifyDDC = false` — attrs: `[AutoParam]` — Validate DDC during tests
- L135 _public field_ `public string DDC = ""` — attrs: `[AutoParam]` — Validate DDC during tests
- L141 _public property_ `public virtual int LogIdleTimeout { get; set; }` — attrs: `[AutoParam]` — Log Idle timeout in second
- L147 _public field_ `public bool EnableStereoTestVariants = false` — attrs: `[AutoParam]` — Enable stereo variants for image based tests
- L152 _public field_ `public string SessionID = Guid.NewGuid().ToString()` — Used for having the editor and any client communicate
- L153 _public method_ `public void GenerateSessionID()`
- L163-383 _public method_ `public override void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)` — Implement how the settings above are applied to different roles in the session. This is the main avenue for converting options into command line parameters for the different roles

#### class `UE.AutomationTestConfig.ValidRHI`  
`private static class ValidRHI`  
_private; L30-51_
- desc: Valid RHI names based on Platform

#### enum `UE.AutomationTestConfig.ValidRHI.Win64`  
`public enum Win64`  
_public; L32-37_
- L34 _public* enumerator_ `d3d11`
- L35 _public* enumerator_ `d3d12`
- L36 _public* enumerator_ `vulkan`

#### enum `UE.AutomationTestConfig.ValidRHI.Linux`  
`public enum Linux`  
_public; L38-41_
- L40 _public* enumerator_ `vulkan`

#### enum `UE.AutomationTestConfig.ValidRHI.Mac`  
`public enum Mac`  
_public; L42-45_
- L44 _public* enumerator_ `metal`

#### enum `UE.AutomationTestConfig.ValidRHI.ShaderModel`  
`public enum ShaderModel`  
_public; L46-50_
- L48 _public* enumerator_ `sm5`
- L49 _public* enumerator_ `sm6`

#### class `UE.EditorAutomation`  
`public class EditorAutomation : AutomationNodeBase<AutomationTestConfig>`  
_public; L390-417_
- inherits: `AutomationNodeBase<AutomationTestConfig>`
- desc: Implements a node that runs Unreal automation tests using the editor. The primary argument is "RunTest". E.g RunUnreal -test=UE.EditorAutomation -RunTest="Group:Animation"
- L392-396 _public ctor_ `public EditorAutomation(Gauntlet.UnrealTestContext InContext) : base(InContext)`
- L402-416 _public method_ `public override AutomationTestConfig GetConfiguration()` — Define the configuration for this test. Most options are applied by the test config above

#### class `UE.TargetAutomation`  
`public class TargetAutomation : AutomationNodeBase<AutomationTestConfig>`  
_public; L423-457_
- inherits: `AutomationNodeBase<AutomationTestConfig>`
- desc: Implements a node that runs Unreal automation tests on a target, monitored by an editor. The primary argument is "RunTest". E.g RunUnreal -test=UE.EditorAutomation -RunTest="Group:Animation"
- L425-428 _public ctor_ `public TargetAutomation(Gauntlet.UnrealTestContext InContext) : base(InContext)`
- L434-456 _public method_ `public override AutomationTestConfig GetConfiguration()` — Define the configuration for this test. Most options are applied by the test config above

#### class `UE.AutomationNodeBase`  
`public abstract class AutomationNodeBase<TConfigClass> : UnrealTestNode<TConfigClass> where TConfigClass : UnrealTestConfiguration, new()`  
_public; L462-1442_
- inherits: `UnrealTestNode<TConfigClass>`
- constraints: `where TConfigClass : UnrealTestConfiguration, new()`
- desc: Base class for automation tests. Most of the magic is in here with the Editor/Target forms simply defining the roles
- L466 _private field_ `private UnrealLogStreamParser LogReader = null`
- L468 _private field_ `private UnrealAutomatedTestPassResults TestPassResults = null`
- L470 _private field_ `private DateTime LastAutomationEntryTime = DateTime.MinValue`
- L472 _protected field_ `protected float IdleTimeoutSec = 30 * 60`
- L475 _protected property_ `protected virtual int MaxEventsDisplayPerTest { get; set; }` — Maximum of events display per test
- L477-480 _public ctor_ `public AutomationNodeBase(Gauntlet.UnrealTestContext InContext) : base(InContext)`
- L486-504 _public property_ `public override string Name { get; }` — Override our name to include the filter we're testing
- L509-539 _public property_ `public override string Suite { get; }` — Override the Suite by GroupName if RunTest is a Group
- L544-560 _protected property_ `protected virtual string GroupName { get; }` — The test group name if any from the command line arguments
- L565-571 _protected property_ `protected override string HordeReportTestName { get; }` — Override the HordeReportTestName in case a simple report is used
- L576-593 _public property_ `public override string Type { get; }` — Override the Type
- L597 _protected property_ `protected override TestHarness TestHarness => ...` — (inheritdoc)
- L599 _protected property_ `protected override TestTeam TestTeam => ...` — (inheritdoc)
- L601 _protected property_ `protected override TestProfile TestProfile => ...` — (inheritdoc)
- L603 _protected property_ `protected override string TestIntent => ...` — (inheritdoc)
- L611-640 _public method_ `public override bool StartTest(int Pass, int InNumPasses)` — Called when a test is starting
- L642-654 _public method_ `public override bool RestartTest()`
- L659-708 _public method_ `public override void TickTest()` — Override TickTest to log interesting things and make sure nothing has stalled
- L710-767 _private method_ `private UnrealAutomatedTestPassResults GetTestPassResults(UnrealLog InLog)`
- L773-976 _private method_ `private void UpdateTestStateOnCriticalFailure(UnrealAutomatedTestPassResults JsonTestPassResults)` — Look for critical failure during the test session and update the test states
- L983-1002 _private method_ `private string GetLastStartedTestFullNameFromRoleResult(UnrealRoleResult RoleResult)` — Get last started test full name from Unreal Role result
- L1013-1055 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)` — Override GetExitCodeAndReason to provide additional checking of success / failure based on what occurred
- L1057-1080 _public method_ `public override IEnumerable<UnrealRoleArtifacts> SaveRoleArtifacts(string OutputPath)`
- L1086-1135 _public method_ `public override ITestReport CreateReport(TestResult Result)` — Optional function that is called on test completion and gives an opportunity to create a report
- L1142-1384 _protected method_ `protected override void LogTestSummaryHeader()` — Override the summary report so we can create a custom summary with info about our tests and a link to the reports
- L1390-1410 _public method_ `public override IEnumerable<string> GetErrors()` — Returns Errors found during tests. We call the base version to get standard errors then Add on any errors seen in tests
- L1416-1441 _public method_ `public override IEnumerable<string> GetWarnings()` — Returns warnings found during tests. We call the base version to get standard warnings then Add on any errors seen in tests

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.ColdCookByTheBook.cs` (Gauntlet.Automation)


#### class `UE.ColdCookByTheBook`  
`public class ColdCookByTheBook : CookByTheBook`  
_public; L8-53_
- inherits: `CookByTheBook`
- L10 _private field_ `private readonly string DataCacheFolderPath`
- L12-18 _public ctor_ `public ColdCookByTheBook(UnrealTestContext InContext) : base(InContext)`
- L20-26 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L28-32 _public method_ `public override void StopTest(StopReason InReason)`
- L34-42 _private method_ `private void RecreateDataCacheFolder()`
- L44-52 _private method_ `private void DeleteDataCacheFolder()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.CookByTheBook.cs` (Gauntlet.Automation)


#### class `UE.CookByTheBook`  
`public class CookByTheBook : CookByTheBookEditor`  
_public; L11-98_
- inherits: `CookByTheBookEditor`
- desc: Implements the functionality of testing the cooking process with the launch of a client
- L13 _private const_ `private const string ClientStartedPattern = "Starting Game"`
- L15 _private field_ `private UnrealLogStreamParser ClientLogParser`
- L17-20 _public ctor_ `public CookByTheBook(UnrealTestContext InContext) : base(InContext)`
- L22-29 _protected method_ `protected override void InitTest()`
- L31-38 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L40-45 _public method_ `public override void TickTest()`
- L47-56 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)`
- L58-64 _private method_ `private static void SetClientRole(UnrealTestConfiguration Config)`
- L66-76 _private method_ `private void ReadClientLogStream()`
- L78-92 _protected method_ `protected override bool IsCookingComplete()`
- L94-97 _private method_ `private bool IsClientStarted()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.CookByTheBookCacheSettings.cs` (Gauntlet.Automation)


#### class `UE.CookByTheBookCacheSettings`  
`public class CookByTheBookCacheSettings : CookByTheBook`  
_public; L9-71_
- inherits: `CookByTheBook`
- L11 _private const_ `private const string SettingsFileName = "DefaultEditorPerProjectUserSettings.ini"`
- L12 _private field_ `private string SettingsFileContent`
- L13 _private field_ `private string SettingsFilePath`
- L14 _private field_ `private string Setting`
- L16-19 _public ctor_ `public CookByTheBookCacheSettings(UnrealTestContext InContext) : base(InContext)`
- L21-25 _public method_ `public override void StopTest(StopReason InReason)`
- L27-42 _private method_ `private void SetupDataCacheSetting()`
- L44-53 _private method_ `private void ReverseDataCacheSetting()`
- L55-59 _private method_ `private void RemoveReadOnlyFileAttribute()`
- L61-65 _private method_ `private void SetReadOnlyFileAttribute()`
- L67-70 _private method_ `private bool DoesOriginalFileContainSetting()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.CookByTheBookEditor.cs` (Gauntlet.Automation)


#### class `UE.CookByTheBookEditor`  
`public class CookByTheBookEditor : UnrealTestNode<UnrealTestConfiguration>`  
_public; L15-302_
- inherits: `UnrealTestNode<UnrealTestConfiguration>`
- desc: Implements the functionality of testing the cooking process in the editor
- L17 _private const_ `private const string CookingIsStartedKey = "The cooking process is started"`
- L18 _private const_ `private const string CookingStartedPattern = "CookSettings for Memory"`
- L19 _private const_ `private const string CookingInProgressPattern = @"Cooked\s+packages\s+\d+\s+Packages\s+Remain\s+\d+\s+Total\s+\d+"`
- L20 _private const_ `private const string CookingCompletePattern = "Cook by the book total time in tick"`
- L21 _private field_ `private string[] CookErrors`
- L22 _private field_ `private ICookedContentProvider ContentProvider`
- L24 _protected const_ `protected const string CookingCompleteKey = "The cooking process is complete"`
- L25 _protected const_ `protected const string CookingInProgressKey = "The cooking process is in progress"`
- L26 _protected const_ `protected const string CookingContentIsPlacedCorrectlyKey = "The cooking content is placed correctly"`
- L27 _protected field_ `protected string BaseEditorCommandLine = " -run=cook -log"`
- L28 _protected field_ `protected UnrealLogStreamParser EditorLogParser`
- L29 _protected field_ `protected Checker Checker`
- L30 _protected field_ `protected bool IsZenStoreUsed`
- L32-35 _public ctor_ `public CookByTheBookEditor(UnrealTestContext InContext) : base(InContext)`
- L37-44 _public method_ `public override bool StartTest(int Pass, int InNumPasses)`
- L46-55 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L57-76 _public method_ `public override void TickTest()`
- L78-90 _protected method_ `protected virtual void InitTest()`
- L92-110 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)`
- L112-119 _protected method_ `protected void SetEditorRole(UnrealTestConfiguration Config, bool IsDeferred)`
- L121-133 _private method_ `private void SetupContentProvider()`
- L135-144 _private method_ `private void InitEditorLogStreamParser()`
- L146-149 _private method_ `private bool IsCookingStarted()`
- L151-154 _private method_ `private bool IsCookingInProgress()`
- L156-159 _protected method_ `protected virtual bool IsCookingComplete()`
- L161-182 _protected method_ `protected virtual bool IsCookedContentPlacedCorrectly()`
- L184-190 _protected method_ `protected ContentFolder GetActualCookedContent()`
- L192-197 _protected method_ `protected virtual ContentFolder GetExpectedCookedContent()`
- L199-208 _private method_ `private string[] FindCookErrors()`
- L210-220 _protected method_ `protected void CleanContentDir()`
- L222-239 _private method_ `private string GetExitReason()`
- L241-247 _private method_ `private string[] GetFailedValidations()`
- L249-255 _protected method_ `protected string GetSavedPath()`
- L257-263 _protected method_ `protected string GetProjectPath()`
- L265-272 _protected method_ `protected string GetSavedCookedPlatformPath()`
- L274-280 _private method_ `private string GetSavedCookedPath()`
- L282-287 _private method_ `private UnrealTargetPlatform GetTargetPlatform()`
- L289-295 _protected method_ `protected string GetTargetPlatformName()`
- L297-301 _protected method_ `protected void CompleteTest(TestResult TestResult)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.CookByTheBookEditors.cs` (Gauntlet.Automation)


#### class `UE.CookByTheBookEditors`  
`public class CookByTheBookEditors : CookByTheBookEditor`  
_public; L11-70_
- inherits: `CookByTheBookEditor`
- desc: Implements the functionality of testing the cooking process with the possibility of restarting the cooking in a new editor
- L13 _protected field_ `protected bool IsEditorRestarted`
- L15-18 _public ctor_ `public CookByTheBookEditors(UnrealTestContext InContext) : base(InContext)`
- L20-23 _public method_ `public override void CleanupTest()`
- L25-32 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L34-50 _protected method_ `protected void RestartEditorRole()`
- L52-69 _private method_ `private void StopRunningRoles()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.CookOnTheFly.cs` (Gauntlet.Automation)


#### class `UE.CookOnTheFly`  
`public class CookOnTheFly : UnrealTestNode<UnrealTestConfiguration>`  
_public; L16-297_
- inherits: `UnrealTestNode<UnrealTestConfiguration>`
- desc: Runs cook on the fly 2 test
- L18 _private* field_ `string CookedProjectDirectoryPath`
- L19 _private* field_ `string SavedCookedPath`
- L20 _private* field_ `string CookedSettingsFilePath`
- L21 _private* field_ `DateTime StartTime = DateTime.Now`
- L22 _private* field_ `bool DeferredClientStarted = false`
- L23 _private* field_ `bool ServerStarted = false`
- L24 _private* field_ `bool ClientConnected = false`
- L25 _private* field_ `bool CookingRequest = false`
- L26 _private* field_ `bool CookOnTheFlyModeChange = false`
- L27 _private* field_ `bool CookingProcessStarted = false`
- L28 _private* field_ `IEnumerable<string> LogCategories = new string[] { "CookOnTheFly", "Cook" }`
- L29 _public method_ `public override IEnumerable<string> GetHeartbeatLogCategories()`
- L30 _private* field_ `UnrealLogStreamParser EditorLogParser = null`
- L31 _private* field_ `UnrealLogStreamParser ClientLogParser = null`
- L32 _private* field_ `Checker ClientCookOnTheFlyCheckers = null`
- L34-37 _public ctor_ `public CookOnTheFly(Gauntlet.UnrealTestContext InContext) : base(InContext)`
- L39-42 _protected method_ `protected virtual string GetStartedCookServerString()`
- L44-47 _protected method_ `protected virtual string GetClientConnectedString()`
- L49-52 _protected method_ `protected virtual string GetCookingRequestString()`
- L54-57 _protected method_ `protected virtual string GetCookingProcessString()`
- L59-62 _protected method_ `protected virtual string GetGameStartString()`
- L64-67 _protected method_ `protected virtual string GetCookModeString()`
- L69-72 _protected method_ `protected virtual string GetEngineInitializedString()`
- L74-77 _protected method_ `protected virtual string GetReceivedPackagesCookedString()`
- L79-103 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L105-115 _public method_ `public override bool StartTest(int Pass, int InNumPasses)`
- L117-126 _private method_ `private bool AttachToEditorLog()`
- L128-149 _private method_ `private bool AttachToClientLog()`
- L151-286 _public method_ `public override void TickTest()`
- L288-296 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.CookSinglePackageByTheBook.cs` (Gauntlet.Automation)


#### class `UE.CookSinglePackageByTheBook`  
`public class CookSinglePackageByTheBook : CookByTheBookEditor`  
_public; L10-93_
- inherits: `CookByTheBookEditor`
- L12 _private const_ `private const string GeneratedFolder = "_Generated_"`
- L13 _private field_ `private readonly string Map`
- L14 _private field_ `private readonly bool IsWorldPartitionMap`
- L16-21 _public ctor_ `public CookSinglePackageByTheBook(UnrealTestContext InContext) : base(InContext)`
- L23-34 _public method_ `public override bool StartTest(int Pass, int InNumPasses)`
- L36-50 _protected method_ `protected override bool IsCookedContentPlacedCorrectly()`
- L52-69 _private method_ `private bool IsSinglePackageCorrect(string SavedCookedPlatformPath)`
- L71-87 _private method_ `private bool AreStreamingPartsCorrect(string SavedCookedPlatformPath)`
- L89-92 _private method_ `private static string GetFileNames(FileInfo[] Files)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.FastCookByTheBook.cs` (Gauntlet.Automation)


#### class `UE.FastCookByTheBook`  
`public class FastCookByTheBook : CookByTheBook`  
_public; L7-21_
- inherits: `CookByTheBook`
- L9-12 _public ctor_ `public FastCookByTheBook(UnrealTestContext InContext) : base(InContext)`
- L14-20 _protected method_ `protected override ContentFolder GetExpectedCookedContent()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.IncrementalCookByTheBook.cs` (Gauntlet.Automation)


#### class `UE.IncrementalCookByTheBook`  
`public class IncrementalCookByTheBook : CookByTheBookEditors`  
_public; L12-118_
- inherits: `CookByTheBookEditors`
- desc: Runs an incremental cook and a game twice
- L14 _private const_ `private const string ClientStartedKey = "The client is started"`
- L15 _private field_ `private UnrealLogStreamParser ClientLogParser`
- L17-21 _public ctor_ `public IncrementalCookByTheBook(UnrealTestContext InContext) : base(InContext)`
- L23-30 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L32-42 _public method_ `public override void TickTest()`
- L44-61 _protected method_ `protected override void InitTest()`
- L63-72 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)`
- L74-88 _protected method_ `protected override bool IsCookingComplete()`
- L90-99 _private method_ `private static void SetClientRoles(UnrealTestConfiguration Config)`
- L101-111 _private method_ `private void ReadClientLogStream()`
- L113 _private method_ `private bool IsClientStarted()`
- L114 _private method_ `private bool AreCookedPackages()`
- L115 _private method_ `private bool NoCookedPackages()`
- L116 _private method_ `private bool IsIncrementalCook()`
- L117 _private method_ `private bool IsFullCook()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.InstallOnly.cs` (Gauntlet.Automation)


#### class `UE.InstallOnlyConfiguration`  
`public class InstallOnlyConfiguration : UnrealTestConfiguration`  
_public; L7-14_
- inherits: `UnrealTestConfiguration`
- L10 _public field_ `public int ClientCount = 1` — attrs: `[AutoParam]`
- L13 _public field_ `public int ServerCount = 0` — attrs: `[AutoParam]`

#### class `UE.InstallOnly`  
`public class InstallOnly : UnrealTestNode<InstallOnlyConfiguration>`  
_public; L19-57_
- inherits: `UnrealTestNode<InstallOnlyConfiguration>`
- desc: No-op test that only installs a build
- L22-25 _public ctor_ `public InstallOnly(Gauntlet.UnrealTestContext InContext) : base(InContext)`
- L31-47 _public method_ `public override InstallOnlyConfiguration GetConfiguration()` — Returns the configuration description for this test
- L52-56 _public method_ `public override void TickTest()` — Completes the test as soon as it starts because this test is a no-op

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.InterruptedCookByTheBook.cs` (Gauntlet.Automation)


#### class `UE.InterruptedCookByTheBook`  
`public class InterruptedCookByTheBook : CookByTheBookEditors`  
_public; L7-23_
- inherits: `CookByTheBookEditors`
- L9-12 _public ctor_ `public InterruptedCookByTheBook(UnrealTestContext InContext) : base(InContext)`
- L14-22 _public method_ `public override void TickTest()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.IterativeCookByTheBook.cs` (Gauntlet.Automation)


#### class `UE.IterativeCookByTheBook`  
`public class IterativeCookByTheBook : CookByTheBookEditors`  
_public; L10-98_
- inherits: `CookByTheBookEditors`
- L12 _private const_ `private const string IterativeCookKey = "Iterative cook enabled"`
- L13 _private const_ `private const string StatisticsShownKey = "Statistics of cooked packets are shown"`
- L14 _private const_ `private const string PacketsSkippedKey = "The number of cooked packets at the first pass is equal to the number of iteratively skipped packets at the second pass"`
- L16 _private const_ `private const string DiffTotalKey = "The number of different packages is zero"`
- L17 _private const_ `private const string PacketsStatisticsPattern = "Total Packages"`
- L18 _private const_ `private const string DetailedPacketsStatisticsPattern = @"Packages Cooked: (\d+), Packages Incrementally Skipped: (\d+)"`
- L19 _private const_ `private const string IterativePattern = "IsIterativeCook=true"`
- L20 _private const_ `private const string DiffTotalPattern = "NumberOfDifferentPackages=0"`
- L22 _private field_ `private List<(string Cooked, string Skipped)> PacketsStatistics`
- L24-28 _public ctor_ `public IterativeCookByTheBook(UnrealTestContext InContext) : base(InContext)`
- L30-37 _protected method_ `protected override void InitTest()`
- L39-48 _public method_ `public override void TickTest()`
- L50-56 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L58-62 _public method_ `public override void CleanupTest()`
- L64-82 _private method_ `private bool ArePacketStatisticsShown()`
- L84-87 _private method_ `private bool AreCookedPacketsSkipped()`
- L89-92 _private method_ `private bool IsIterativeCook()`
- L94-97 _private method_ `private bool IsNumberOfDifferentPackagesZero()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.Networking.cs` (Gauntlet.Automation)


#### class `UE.NetworkAutomation.DedicatedServer`  
`public class DedicatedServer : NetworkingNodeBase<EpicGameTestConfig>`  
_public; L17-41_
- inherits: `NetworkingNodeBase<EpicGameTestConfig>`
- L19-21 _public ctor_ `public DedicatedServer(UnrealTestContext InContext) : base(InContext)`
- L23-40 _public method_ `public override EpicGameTestConfig GetConfiguration()`

#### class `UE.NetworkAutomation.ListenServerConfig`  
`public class ListenServerConfig : UnrealGame.UnrealTestConfig`  
_public; L43-82_
- inherits: `UnrealGame.UnrealTestConfig`
- L45 _private* field_ `string ListenServerIP = ""`
- L47-81 _public method_ `public override void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)`

#### class `UE.NetworkAutomation.ListenServer`  
`public class ListenServer : NetworkingNodeBase<ListenServerConfig>`  
_public; L84-103_
- inherits: `NetworkingNodeBase<ListenServerConfig>`
- L86-88 _public ctor_ `public ListenServer(UnrealTestContext InContext) : base(InContext)`
- L90-102 _public method_ `public override ListenServerConfig GetConfiguration()`

#### class `UE.NetworkingNodeBase`  
`public abstract class NetworkingNodeBase<TConfigClass> : UnrealTestNode<TConfigClass> where TConfigClass : UnrealGame.UnrealTestConfig, new()`  
_public; L109-170_
- inherits: `UnrealTestNode<TConfigClass>`
- constraints: `where TConfigClass : UnrealGame.UnrealTestConfig, new()`
- desc: Runs automated tests on a platform
- L112 _private field_ `private DateTime LastAutomationEntryTime = DateTime.MinValue`
- L114-118 _public ctor_ `public NetworkingNodeBase(Gauntlet.UnrealTestContext InContext) : base(InContext)`
- L124-147 _protected method_ `protected override void LogTestSummaryHeader()` — Override the summary report
- L149-169 _public method_ `public override ITestReport CreateReport(TestResult Result)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.UnversionedCookByTheBook.cs` (Gauntlet.Automation)


#### class `UE.UnversionedCookByTheBook`  
`public class UnversionedCookByTheBook : CookByTheBook`  
_public; L8-28_
- inherits: `CookByTheBook`
- L10 _private const_ `private const string UnversionedPattern = "IsUnversioned=true"`
- L12-15 _public ctor_ `public UnversionedCookByTheBook(UnrealTestContext InContext) : base(InContext)`
- L17-22 _protected method_ `protected override void InitTest()`
- L24-27 _private method_ `private bool IsUnversionedCook()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Automation/UE.ZenStreaming.cs` (Gauntlet.Automation)


#### class `UE.ZenStreaming`  
`public class ZenStreaming: UnrealTestNode<UnrealTestConfiguration>`  
_public; L12-71_
- inherits: `UnrealTestNode<UnrealTestConfiguration>`
- L14 _private const_ `private const string StreamingStatsFile = "ZenStreamingClient.log"`
- L15 _private field_ `private UnrealLogStreamParser ClientLogParser`
- L16 _private field_ `private readonly string ReplayFile`
- L17 _private field_ `private string ZenArgs`
- L19-26 _public ctor_ `public ZenStreaming(UnrealTestContext InContext) : base(InContext)`
- L28-37 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L39-45 _public method_ `public override void StopTest(StopReason InReason)`
- L47-57 _private method_ `private void ReadClientLogStream()`
- L59-70 _private method_ `private void ParseStreamingStats()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealAppConfig.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealAppConfig`  
`public class UnrealAppConfig : IAppConfig`  
_public; L14-144_
- inherits: `IAppConfig`
- desc: Represents the configuration needed to run an instance of an Unreal app
- L19 _public property_ `public string Name { get; set; }` — Reference name
- L24 _public property_ `public string ProjectName { get; set; }` — Name of this unreal project
- L29 _public property_ `public FileReference ProjectFile { get; set; }` — Path to the file. Can be null if the project isn't on disk
- L34 _public property_ `public UnrealTargetRole ProcessType { get; set; }` — Type of role this instance performs
- L39 _public property_ `public UnrealTargetPlatform? Platform { get; set; }` — Platform this role runs on
- L44 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }` — Configuration for this role
- L49 _public property_ `public List<UnrealFileToCopy> FilesToCopy { get; set; }` — Files to copy over to the device, plus what type of files they are.
- L55-58 _public property_ `public bool CanAlterCommandArgs { get; set; }` — Some IAppInstall instances can alter command line after it has been copied from AppConfig.CommandLine Use this to restrict this behavior if necessary.
- L59 _private field_ `private bool CanAlterCommandArgsPrivate = true`
- L64 _public property_ `public ContainerInfo ContainerInfo { get; set; }` — Set this property when the application is executed through a Docker container.
- L69 _public property_ `public LongProcessResult.OutputFilterCallbackType FilterLoggingDelegate { get; set; }` — Delegate to filter logging output
- L74-95 _public property_ `public string CommandLine { get; set; }` — Arguments for this instance
- L100 _public field_ `public GauntletCommandLine CommandLineParams` — Dictionary of commandline arguments that are turned into a commandline at the end. For flags, leave the value set to null.
- L105 _public property_ `public string Sandbox { get; set; }` — Sandbox that we'd like to install this instance in
- L107 _public property_ `public IBuild Build { get; set; }`
- L109 _public property_ `public OverlayExecutable OverlayExecutable { get; set; }`
- L112 _public property_ `public bool SkipInstall => ...`
- L115 _public property_ `public bool FullClean => ...`
- L120 _public property_ `public bool UsePlatformExtraDebugMemory { get; set; }` — Use additional debug memory on target device if available.
- L125 _public property_ `public int MaxDuration { get; set; }` — Defines the expected duration of the app process. May not be set depending on the context of this object's creation
- L130 _public property_ `public bool DisableStdoutProcessing { get; set; }` — Disable stdout redirection and write the output of the app process to a log file
- L135-143 _public ctor_ `public UnrealAppConfig()` — Constructor that sets some required values to defaults

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealConfigOptions.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealOptions`  
`public class UnrealOptions : IConfigOption<UnrealAppConfig>, ICloneable`  
_public; L16-108_
- inherits: `IConfigOption<UnrealAppConfig>, ICloneable`
- desc: Defines a basic set of options that can be applied to client & server instances of Unreal
- L19 _public field_ `public bool NullRHI` — attrs: `[AutoParam(false)]`
- L22 _public field_ `public bool Debug` — attrs: `[AutoParam(false)]`
- L25 _public field_ `public bool Windowed` — attrs: `[AutoParam(true)]`
- L28 _public field_ `public int ResX` — attrs: `[AutoParam(1920)]`
- L31 _public field_ `public int ResY` — attrs: `[AutoParam(1080)]`
- L34 _public field_ `public bool Unattended` — attrs: `[AutoParam(false)]`
- L37 _public field_ `public bool Log` — attrs: `[AutoParam(false)]`
- L40 _public field_ `public string Map` — attrs: `[AutoParam("")]`
- L43 _public field_ `public string CommonArgs` — attrs: `[AutoParam("")]`
- L46 _public field_ `public string ClientArgs` — attrs: `[AutoParam("")]`
- L49 _public field_ `public string ServerArgs` — attrs: `[AutoParam("")]`
- L51-55 _public ctor_ `public UnrealOptions()`
- L57-103 _public method_ `public virtual void ApplyToConfig(UnrealAppConfig AppConfig)`
- L104-107 _public method_ `public object Clone()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealPGONode.cs` (Gauntlet.Automation)


#### class `Gauntlet.PGOConfig`  
`public class PGOConfig : UnrealTestConfiguration, IAutoParamNotifiable`  
_public; L14-41_
- inherits: `UnrealTestConfiguration, IAutoParamNotifiable`
- L20 _public field_ `public string ProfileOutputDirectory` — attrs: `[AutoParam("")]` — Output directory to write the resulting profile data to.
- L26 _public field_ `public string ScreenshotDirectory` — attrs: `[AutoParam("")]` — Directory to save periodic screenshots to whilst the PGO run is in progress.
- L29 _public field_ `public string PGOAccountSandbox` — attrs: `[AutoParam("")]`
- L32 _public field_ `public string PgcFilenamePrefix` — attrs: `[AutoParam("")]`
- L34-40 _public method_ `public virtual void ParametersWereApplied(string[] Params)`

#### class `Gauntlet.PGONode`  
`public class PGONode<TConfigClass> : UnrealTestNode<TConfigClass> where TConfigClass : PGOConfig, new()`  
_public; L43-191_
- inherits: `UnrealTestNode<TConfigClass>`
- constraints: `where TConfigClass : PGOConfig, new()`
- L45 _protected field_ `protected string LocalOutputDirectory`
- L46 _internal field_ `internal IPGOPlatform PGOPlatform`
- L47 _private* field_ `bool ProcessPGODataFailed = false`
- L49-52 _public ctor_ `public PGONode(UnrealTestContext InContext) : base(InContext)`
- L54-92 _public method_ `public override TConfigClass GetConfiguration()`
- L94 _private field_ `private DateTime ScreenshotStartTime = DateTime.UtcNow`
- L95 _private field_ `private DateTime ScreenshotTime = DateTime.MinValue`
- L96 _private field_ `private TimeSpan ScreenshotInterval = TimeSpan.FromSeconds(30)`
- L97 _private const_ `private const float ScreenshotScale = 1.0f / 3.0f`
- L98 _private const_ `private const int ScreenshotQuality = 30`
- L99 _protected field_ `protected string ScreenshotDirectory`
- L100 _protected field_ `protected bool ResultsGathered = false`
- L102-110 _protected method_ `protected override TestResult GetUnrealTestResult()`
- L112-190 _public method_ `public override void TickTest()`

#### interface `Gauntlet.IPGOCustomReplayPlatform`  
`public interface IPGOCustomReplayPlatform`  
_public; L194-197_
- L196 _public* method_ `void ConfigureClientForReplay( PGOConfig Config, UnrealTestRole ClientRole, string LocalReplayFileName )`

#### class `Gauntlet.BasicReplayPGOConfig`  
`public class BasicReplayPGOConfig : PGOConfig`  
_public; L200-218_
- inherits: `PGOConfig`
- L203 _public field_ `public string LocalReplay` — attrs: `[AutoParam("")]`
- L206 _public field_ `public string AdditionalCommandLine` — attrs: `[AutoParam("")]`
- L208-217 _public method_ `public override void ParametersWereApplied(string[] Params)`

#### class `Gauntlet.BasicReplayPGONode`  
`public class BasicReplayPGONode : PGONode<BasicReplayPGOConfig>`  
_public; L224-258_
- inherits: `PGONode<BasicReplayPGOConfig>`
- desc: PGO Profiling Node that runs a replay & gathers the results. Requires an existing build compiled with -PGOProfile -Configuration=Shipping e.g. RunUnreal -Test=BasicReplayPGONode -project=MyProject -platform=Win64 -configuration=Shipping -build=MyProject\Saved\StagedBuilds\Windows -LocalReplay=MyProject\Replays\PGO.replay -ProfileOutputDirectory=MyProject\Platforms\Windows\Build\PGO -MaxDuration=7200
- L226-228 _public ctor_ `public BasicReplayPGONode(UnrealTestContext InContext) : base(InContext)`
- L230-257 _public method_ `public override BasicReplayPGOConfig GetConfiguration()`

#### interface `Gauntlet.IPGOPlatform`  
`internal interface IPGOPlatform`  
_internal; L262-271_
- L264 _public* method_ `void ApplyConfiguration(PGOConfig Config)`
- L266 _public* method_ `void GatherResults(string ArtifactPath)`
- L268 _public* method_ `bool TakeScreenshot(ITargetDevice Device, string ScreenshotDirectory, out string ImageFilename)`
- L270 _public* method_ `UnrealTargetPlatform GetPlatform()`

#### class `Gauntlet.PGOPlatformManager`  
`internal abstract class PGOPlatformManager`  
_internal; L276-307_
- desc: PGO platform manager
- L278-287 _public method_ `public static IPGOPlatform GetPGOPlatform(UnrealTargetPlatform Platform)`
- L289-292 _protected method_ `protected static void RegisterPGOPlatform(UnrealTargetPlatform Platform, Type PGOPlatformType)`
- L294 _private* field_ `static Dictionary<UnrealTargetPlatform, Type> PGOPlatforms = ...`
- L294 _private* field_ `static Dictionary< PGOPlatforms = new Dictionary<UnrealTargetPlatform, Type>()`
- L296-305 _private* ctor_ `static PGOPlatformManager()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealProcessResult.cs` (Gauntlet.Automation)


#### enum `Gauntlet.UnrealProcessResult`  
`public enum UnrealProcessResult`  
_public; L8-19_
- desc: Describes reasons an Unreal process may have exited
- L10 _public* enumerator_ `ExitOk`
- L11 _public* enumerator_ `InitializationFailure`
- L12 _public* enumerator_ `EncounteredFatalError`
- L13 _public* enumerator_ `EncounteredEnsure`
- L14 _public* enumerator_ `LoginFailed`
- L15 _public* enumerator_ `TimeOut`
- L16 _public* enumerator_ `TestFailure`
- L17 _public* enumerator_ `EngineTestError`
- L18 _public* enumerator_ `Unknown`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealRoleConfiguration.cs` (Gauntlet.Automation)


#### interface `Gauntlet.IUnrealRoleConfiguration`  
`public interface IUnrealRoleConfiguration`  
_public; L15-19_
- desc: UnrealRoleConfigurations can be added to an UnrealTestRole to modularize the creation of commandline arguments. A common use case is generating args for a the CSV Profiler. You would normally need to manually create the arguments for every role, but with an UnrealRoleConfiguration you can set a couple properties and the commandline will be generated and applied automatically. Experimental feature! Subject to rapid change.
- L17 _public* method_ `void ApplyConfigToRole(UnrealTestRole Role)`
- L18 _public* method_ `void VerifyRoleConfig(UnrealTestRole Role)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealSession.cs` (Gauntlet.Automation)


#### enum `Gauntlet.ERoleModifier`  
`public enum ERoleModifier`  
_public; L18-23_
- L20 _public* enumerator_ `None`
- L21 _public* enumerator_ `Dummy`
- L22 _public* enumerator_ `Null`

#### class `Gauntlet.UnrealSessionRole`  
`public class UnrealSessionRole`  
_public; L28-275_
- desc: Represents a role that will be performed in an Unreal Session
- L34 _public field_ `public UnrealTargetRole RoleType` — Type of role
- L39 _public field_ `public UnrealTargetPlatform? Platform` — Platform this role uses
- L44 _public field_ `public UnrealTargetConfiguration Configuration` — Configuration this role runs in
- L49 _public field_ `public UnrealDeviceTargetConstraint Constraint` — Constraints this role runs under
- L54 _public field_ `public IConfigOption<UnrealAppConfig> Options` — Options that this role needs
- L60 _public field_ `public string Tag` — Unique tag for logging purposes
- L65-86 _public property_ `public string CommandLine { get; set; }` — Command line that this role will use
- L92 _public property_ `public GauntletCommandLine CommandLineParams { get; set; }` — Dictionary of commandline arguments that are turned into a commandline at the end. For flags, leave the value set to null. Generated from the Test Role's commandline object and modified as needed. Then passed through to the AppConfig in UnrealBuildSource.cs
- L98 _public field_ `public string MapOverride` — Map override to use on a server in case we don't want them all running the same map.
- L103 _public field_ `public List<UnrealFileToCopy> FilesToCopy` — List of files to copy to the device.
- L108 _public field_ `public List<EIntendedBaseCopyDirectory> AdditionalArtifactDirectories` — Additional UE directories to copy from when saving artifacts
- L113 _public field_ `public PreConfigureDeviceHandler PreConfigureDevice` — Allows for individual roles to configure their associated Target device before build installation
- L118 _public field_ `public ConfigureDeviceHandler ConfigureDevice` — Allows for individual roles to configure their associated Target device after build installation and AppInstall creation
- L123 _public field_ `public BuildFlags RequiredBuildFlags` — Properties we require our build to have
- L128 _public field_ `public string RequiredFlavor` — Flavor of the build
- L133 _public field_ `public ERoleModifier RoleModifier` — Should be represented by a null device?
- L138 _public method_ `public bool IsDummy()` — Is this a dummy executable?
- L143 _public property_ `public bool InstallOnly { get; set; }` — Whether this role should be responsible only for installing the build and not monitoring a process.
- L148 _public property_ `public bool DeferredLaunch { get; set; }` — Whether this role will launched by the test node at a later time, typically during TickTest(). By default, all roles are launched immediately.
- L153 _public property_ `public bool CompressScreenshots { get; set; }` — Whether this role will compress screenshots produced as an artifact into a jpeg format
- L158 _public property_ `public bool CreateGifFromScreenshots { get; set; }` — Whether this role will create a gif from screenshots produced as artifacts
- L163 _public property_ `public bool SkipCleanDeviceArtifacts { get; set; }` — Whether or not this role should skip the cleaning of its device's artifact between each test run
- L169 _public property_ `public bool ArchiveDevArtifacts { get; set; }` — Whether or not this role will save artifacts when running with -dev. These can be huge, so be cautious with using this.
- L174 _public property_ `public bool RespawnProcessOnUnexpectedExit { get; set; }` — Whether to respawn this process automatically if it fails unexpectedly
- L179 _public field_ `public OnTryToRestoreProcessDelegate OnTryToRestoreProcess` — What to do if this role exits unexpectedly.
- L184 _public method_ `public bool IsNullRole()` — Is this role Null?
- L194-197 _public ctor_ `public UnrealSessionRole(UnrealTargetRole InType, UnrealTargetPlatform? InPlatform, UnrealTargetConfiguration InConfiguration, IConfigOption<UnrealAppConfig> InOptions) : this(InType, InPlatform, InConfiguration, null, InOptions)` — Constructor taking limited params
- L207-265 _public ctor_ `public UnrealSessionRole(UnrealTargetRole InType, UnrealTargetPlatform? InPlatform, UnrealTargetConfiguration InConfiguration, string InCommandLine = null, IConfigOption<UnrealAppConfig> InOptions = null, bool CompressScreenshots = true, bool CreateGifFromScreenshots = true)` — Constructor taking optional params
- L271-274 _public method_ `public override string ToString()` — Debugging aid

#### class `Gauntlet.UnrealSessionInstance`  
`public class UnrealSessionInstance : IDisposable`  
_public; L283-612_
- inherits: `IDisposable`
- desc: Represents an instance of a running an Unreal session. Basically an aggregate of all processes for all roles (clients, server, etc TODO - combine this into UnrealSession
- L319 _public property_ `public RoleInstance[] AllRoles { get; set; }` — All roles
- L324 _public property_ `public IEnumerable<RoleInstance> RunningRoles { get; }` — All running roles
- L329 _public property_ `public IEnumerable<RoleInstance> DeferredRoles { get; }` — All deferred roles
- L334 _public property_ `public Dictionary<RoleInstance, IAppInstall> DeferredRoleToAppInstall { get; set; }` — All deferred roles and their associated IAppInstall
- L339-345 _public property_ `public IAppInstance[] ClientApps { get; }` — Helper for accessing all client processes. May return an empty array if no clients are involved
- L350-356 _public property_ `public IAppInstance ServerApp { get; }` — Helper for accessing server process. May return null if no server is involved
- L361-367 _public property_ `public IAppInstance EditorApp { get; }` — Helper for accessing editor process. May return null if no editor is involved
- L372-378 _public property_ `public bool ClientsRunning { get; }` — Helper that returns true if clients are currently running
- L383-389 _public property_ `public bool ServerRunning { get; }` — Helper that returns true if there's a running server
- L394-400 _public property_ `public bool IsRunningRoles { get; }` — Returns true if any of our roles are still running
- L407-411 _public ctor_ `public UnrealSessionInstance(RoleInstance[] InAllRoles, Dictionary<RoleInstance, IAppInstall> InDeferredRoleToAppInstall = null)` — Constructor. Roles must be passed in
- L413-416 _private* dtor_ `~UnrealSessionInstance()`
- L419 _private field_ `private bool disposedValue = false`
- L421-433 _protected method_ `protected virtual void Dispose(bool disposing)`
- L436-440 _public method_ `public void Dispose()`
- L448-461 _public method_ `public IAppInstall FindInstallForDeferredRole( UnrealSessionRole Role )` — Returns the app install for a given role, where the role was marked as 'DeferredLaunch'
- L469-472 _public method_ `public bool LaunchDeferredRole( UnrealSessionRole Role )` — Launches a role that was previously flagged as 'DeferredLaunch'. Note that this does not handle device failure, marking problem devices etc.
- L480-523 _public method_ `public bool LaunchDeferredRole(UnrealSessionRole Role, out RoleInstance RoleInstance)` — Launches a role that was previously flagged as 'DeferredLaunch'. Note that this does not handle device failure, marking problem devices etc.
- L530-560 _public method_ `public bool RecoverProcessForRole(UnrealSessionRole Role, IAppInstall CurInstall)` — Tries to recover a process for a role that exited unexpectedly.
- L566-611 _public method_ `public void Shutdown(bool GenerateDumpOnKill = false)` — Shutdown the session by killing any remaining processes.

#### class `Gauntlet.UnrealSessionInstance.RoleInstance`  
`public class RoleInstance`  
_public; L288-314_
- desc: Represents an running role in our session
- L290-294 _public ctor_ `public RoleInstance(UnrealSessionRole InRole, IAppInstance InInstance)`
- L299 _public property_ `public UnrealSessionRole Role { get; set; }` — Role that is being performed in this session
- L304 _public property_ `public IAppInstance AppInstance { get; set; }` — Underlying AppInstance that is running the role
- L310-313 _public method_ `public override string ToString()` — Debugging aid

#### class `Gauntlet.UnrealRoleArtifacts`  
`public class UnrealRoleArtifacts`  
_public; L617-653_
- desc: Represents the set of available artifacts available after an UnrealSessionRole has completed
- L622 _public property_ `public UnrealSessionRole SessionRole { get; set; }` — Session role info that created these artifacts
- L627 _public property_ `public IAppInstance AppInstance { get; set; }` — AppInstance that was used to run this role
- L632 _public property_ `public string ArtifactPath { get; set; }` — Path to artifacts from this role (these are local and were retried from the device).
- L637 _public property_ `public string LogPath { get; set; }` — Path to Log from this role
- L646-652 _public ctor_ `public UnrealRoleArtifacts(UnrealSessionRole InSessionRole, IAppInstance InAppInstance, string InArtifactPath, string InLogPath)` — Constructor, all values must be provided

#### class `Gauntlet.UnrealSession`  
`public class UnrealSession : IDisposable`  
_public; L659-2209_
- inherits: `IDisposable`
- desc: Helper class that understands how to launch/monitor/stop an Unreal test (clients + server) based on params contained in the test context and config
- L664 _public property_ `public UnrealDeviceReservation UnrealDeviceReservation { get; set; }` — Device reservation instance of this session
- L669 _protected property_ `protected UnrealBuildSource BuildSource { get; set; }` — Source of the build that will be launched
- L674 _protected property_ `protected UnrealSessionRole[] SessionRoles { get; set; }` — Roles that will be performed by this session
- L679 _public property_ `public UnrealSessionInstance SessionInstance { get; set; }` — Running instance of this session
- L684 _public property_ `public string Sandbox { get; set; }` — Sandbox for installed apps
- L689 _public property_ `public bool ShouldRetainDevices { get; set; }` — Whether or not devices should be retained between each test iteration
- L692 _public property_ `public bool ReinstallPerPass { get; set; }` — attrs: `[AutoParam(false)]`
- L698 _public property_ `public int LaunchSessionAttempts { get; set; }` — Number of attempts when launching a session. Failed installs and runs will trigger a re-try
- L703 _public property_ `public int DeviceReservationAttempts { get; set; }` — Number of attempts when trying to reserve devices
- L708 _public property_ `public int DeviceReservationRetryTime { get; set; }` — Number of seconds to wait between failed device reservation attempts
- L713 _public property_ `public Dictionary<UnrealSessionRole, ITargetDevice> RolesToDevices { get; set; }` — Record of each ITargetDevice assigned to a given role
- L718 _public property_ `public Dictionary<UnrealSessionRole, UnrealAppConfig> RolesToConfigs { get; set; }` — Record of each UnrealAppConfig created for each role
- L723 _public property_ `public Dictionary<UnrealSessionRole, IAppInstall> RolesToInstalls { get; set; }` — Record of our installations in case we want to re-use them in a later pass
- L730-761 _public ctor_ `public UnrealSession(UnrealBuildSource InSource, IEnumerable<UnrealSessionRole> InSessionRoles)` — Constructor that takes a build source and a number of roles
- L766-769 _private* dtor_ `~UnrealSession()` — Destructor, terminates any running session
- L772 _private field_ `private bool disposedValue = false`
- L774-786 _protected method_ `protected virtual void Dispose(bool disposing)`
- L789-793 _public method_ `public void Dispose()`
- L800-845 _public method_ `public bool TryReserveDevices()` — Helper that reserves and returns a list of available devices based on the passed in roles
- L847-870 _public method_ `public bool TryReserveDevices(int Attempts)`
- L877-889 _private* method_ `bool CheckRolesArePossible(ref List<string> Issues)` — Check that all the current roles can be performed by our build source
- L897-993 _public method_ `public UnrealSessionInstance LaunchSession()` — Installs and launches all of our roles and returns an UnrealSessonInstance that represents the aggregate of all of these processes. Will perform retries if errors with devices are encountered so this is a "best attempt" at running with the devices provided
- L999-1006 _public method_ `public UnrealSessionInstance RestartSession()` — Restarts the current session (if any)
- L1011-1018 _public method_ `public void ShutdownInstance()` — Shuts down any running apps
- L1024-1032 _public method_ `public void ShutdownSession()` — Shuts down the current session (if any)
- L1034-1057 _public method_ `public void ReleaseSessionDevices(bool bForce = false)`
- L1059-1088 _public method_ `public void ReleaseProblemDevices()`
- L1097-1101 _public method_ `public UnrealRoleArtifacts SaveRoleArtifacts(UnrealTestContext InContext, UnrealSessionInstance.RoleInstance InRunningRole, string DestinationArtifactPath)` — Retrieves and saves all artifacts from the provided session role. Artifacts are saved to the destination path
- L1103-1292 _public method_ `public UnrealRoleArtifacts SaveRoleArtifacts(UnrealTestContext InContext, UnrealSessionInstance.RoleInstance InRunningRole, string DestinationArtifactPath, ref string DirectoryToCleanUp)`
- L1301-1430 _public method_ `public IEnumerable<UnrealRoleArtifacts> SaveRoleArtifacts(UnrealTestContext Context, UnrealSessionInstance TestInstance, string OutputPath)` — Saves all artifacts from the provided session to the specified output path.
- L1432-1678 _private method_ `private UnrealSessionInstance Legacy_LaunchSession()`
- L1683-1689 _private method_ `private bool HasAcquiredDevices()` — Returns true if the number of reserved devices matches the number on non-null session roles
- L1694-1697 _private method_ `private bool RoleNeedsDevice(UnrealSessionRole Role)` — Returns true if the provided session role has not yet been assigned a device
- L1702-1707 _private method_ `private bool RoleNeedsInstall(UnrealSessionRole Role)` — Returns true if the provided session role has not yet had an install performed on it's assigned device
- L1712-1719 _private method_ `private bool DeviceMatchesRoleConstraint(UnrealSessionRole Role, ITargetDevice Device)` — Returns true if the provided target device matches the constraint requested by the session role
- L1725-1762 _private method_ `private bool TryAssignDevicesToRoles()` — From the existing reserved device pool, assign each role a device that matches it's requested constraint This will cache a map of each role and the target device it's using in this UnrealSession
- L1772-1889 _private method_ `private void ReadyDevicesForSession()` — Prepares each device for launch by performing the following - Install builds - Clean up old artifacts - Copy additional files requested by a test - Specific role configurations This will create and cache both an UnrealAppConfig and an IAppInstall for future reference
- L1897-1962 _private method_ `private UnrealSessionInstance LaunchProcesses()` — Launches the Unreal Engine processes for each role requested by this session. Roles marked InstallOnly will not have a process launched. Roles marked DeferredLaunch will not have a process launched. Deferred roles can be launched at anytime (usually in TickTest()) by calling UnrealSessionInstance.LaunchDeferredRole
- L1964-2029 _private method_ `private void SaveScreenshots(string RoleName, string SourceDirectory, string DestinationDirectory, bool bCompressImages, bool bCreateGif)`
- L2031-2119 _private method_ `private void SavePSOs(UnrealTestContext InContext, UnrealSessionInstance.RoleInstance InRunningRole, string DestSavedDir)`
- L2121-2160 _private method_ `private string GenerateNotTakenFilePath(string DesiredPath)`
- L2169-2189 _private method_ `private string TruncateLongPathFilter(string LongFilePath)` — Filter that Truncate long file paths such as CrashReporter files. //UECC-Windows-F0DD9BB04C3C9250FAF39D8AB4A88556// These are particularly problematic with testflights which append a long random name to the destination folder, easily pushing past 260 chars.
- L2191-2198 _private method_ `private string GetInstallTime(TimeSpan Time)`
- L2200-2203 _private method_ `private bool IsOutOfSpaceException(Exception Ex)`
- L2205-2208 _private method_ `private bool IsOverlayException(Exception Ex)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealTestConfiguration.cs` (Gauntlet.Automation)


#### class `Gauntlet.GauntletCommandLine`  
`public class GauntletCommandLine`  
_public; L13-365_
- L15 _public field_ `public string Project`
- L16 _public field_ `public string GameMap`
- L17 _private field_ `private Dictionary<string, object> Params`
- L17 _private field_ `private Dictionary< Params`
- L18 _private field_ `private HashSet<string> NonOptionParams`
- L20 _public field_ `public static readonly Regex CommandLineRegex = new Regex("(?:\"[^\"]*\"|[^\\s\"])+", RegexOptions.Compiled)`
- L21 _public field_ `public static readonly Regex CommandlineOptionRegex = new Regex(@"-(?<option>-?[\w\d.:!\[\]\/\\?-]+)(=(?<value>(""(?:(?:\\""|[^""])+)"")|(?:\S+)))?", RegexOptions.Compiled)`
- L24 _public property_ `public IReadOnlyDictionary<string, object> Arguments { get; }`
- L30 _public field_ `public string AdditionalExplicitCommandLineArgs` — String containing extra commandline args that do not conform to UE commandline arg specs. Please do not use this for for standard flags.
- L32-39 _public ctor_ `public GauntletCommandLine()`
- L42-49 _public ctor_ `public GauntletCommandLine(GauntletCommandLine InCopy)`
- L57-77 _public method_ `public void AddRawCommandline(string InRawCommandline, bool bOverrideExistingValues = true)` — Breaks down a raw commandline and adds it to the commandline dictionary. Will override current set values in the dictionary when conflicts arise.
- L85-91 _public method_ `public void CombineCommandLines(GauntletCommandLine InCommandline, bool bOverrideExistingValues = true)` — Breaks down a raw commandline and adds it to the commandline dictionary. Will override current set values in the dictionary when conflicts arise.
- L99-121 _public method_ `public bool AddUnique(string ParamName, object ParamVal = null)` — Add a new value to the commandline, returning false if the value already exists on the commandline and would be set to something other than what is passed in. Execcmds passed in here will still append to an existing value.
- L131-168 _public method_ `public void Add(string ParamName, object ParamVal = null, bool IsNonOption = false)` — Add new param value (adding with a value of null makes it a flag instead of a param) Overrides current value of the param if one exists. Execcmds will be appended to instead of overridden.
- L176-194 _public method_ `public void AddOrAppendParamValue(string ParamName, string ParamVal, string DelimiterToUse = ",")` — Add a new param, or append passed in value to it if a value already exists, delimited with the Delimiter passed in.
- L199-205 _public method_ `public void RemoveParam(string ParamName)` — Remove the param or flag by the passed-in name if it exists.
- L213-220 _public method_ `public object GetParamValue(string ParamName)` — Returns the current value of the param if it has one. Flags and nonexistent entries will return null.
- L230-252 _public method_ `public Dictionary<string, string> GetGroupParamValues(string GroupName, string SubParamDelimeter = ",", string SubValueDelimeter = " ")` — Get a collection of all sub paremeters Useful for group arguments like ExecCmds
- L259-262 _public method_ `public bool HasParam(string ParamName)` — Checks if a parameter is present
- L272-275 _public method_ `public bool HasGroupParam(string GroupName, string SubParamName, string SubParamDelimeter = ",", string SubValueDelimeter = " ")` — Checks if a parameter group has a subparameter
- L280-284 _public method_ `public void ClearCommandLine()` — Wipe out the entire set of passed in params.
- L293-327 _public method_ `public string GenerateFullCommandLine(bool CanAlterCommandArgs = true)` — Cobbles together the finalized commandline from the passed-in values. Wraps param values w/ spaces in quotes etc. This is the function we use, as well, when accessing the Role's commandline itself.
- L329-364 _public method_ `public static List<string> GetArgumentList(string Args)`

#### enum `Gauntlet.EWindowMode`  
`public enum EWindowMode`  
_public; L367-385_
- L372 _public* enumerator_ `Fullscreen` — The window is in true fullscreen mode.
- L376 _public* enumerator_ `WindowedFullscreen` — CURRENTLY UNSUPPORTED. Using this value will enable -fullscreen for now. The window has no border and takes up the entire area of the screen.
- L380 _public* enumerator_ `Windowed` — The window has a border and may not take up the entire screen area.
- L384 _public* enumerator_ `NumWindowModes` — The total number of supported window modes.

#### enum `Gauntlet.EIntendedBaseCopyDirectory`  
`public enum EIntendedBaseCopyDirectory`  
_public; L391-402_
- desc: Generic intent enum for the base of where we would like to copy a file to. Interpreted properly in TargetDeviceX.cs.
- L393 _public* enumerator_ `Build`
- L394 _public* enumerator_ `Binaries`
- L395 _public* enumerator_ `Config`
- L396 _public* enumerator_ `Content`
- L397 _public* enumerator_ `Demos`
- L398 _public* enumerator_ `Profiling`
- L399 _public* enumerator_ `Saved`
- L400 _public* enumerator_ `Platform`
- L401 _public* enumerator_ `PersistentDownloadDir`

#### enum `Gauntlet.EMaxDurationReachedResult`  
`public enum EMaxDurationReachedResult`  
_public; L407-411_
- desc: What reaching the max duration of this test signifies.
- L409 _public* enumerator_ `Failure`
- L410 _public* enumerator_ `Success`

#### class `Gauntlet.UnrealTestRole`  
`public class UnrealTestRole`  
_public; L436-587_
- desc: This class represents a process-role in a test and defines the type, command line, and controllers that are needed. TODO - can this be removed and UnrealSessionRole used directly?
- L444-461 _public ctor_ `public UnrealTestRole(UnrealTargetRole InType, UnrealTargetPlatform? InPlatformOverride)` — Constructor. This intentionally takes only a type as it's expected that code creating roles should do so via the configuration class and take care to append properties.
- L463 _public property_ `public ERoleModifier RoleType { get; set; }`
- L468 _public property_ `public bool InstallOnly { get; set; }` — Whether this role should be responsible only for installing the build and not monitoring a process.
- L473 _public property_ `public bool DeferredLaunch { get; set; }` — Whether this role will launched by the test node at a later time, typically during TickTest(). By default, all roles are launched immediately.
- L478 _public property_ `public UnrealTargetRole Type { get; set; }` — Type of process this role represents
- L483 _public property_ `public UnrealTargetPlatform? PlatformOverride { get; set; }` — Override for what platform this role is on
- L488-509 _public property_ `public string CommandLine { get; set; }` — Command line or this role
- L516 _public property_ `public GauntletCommandLine CommandLineParams { get; set; }` — Dictionary of commandline arguments that are turned into a commandline at the end. For flags, leave the value set to null. Created and then passed through to the Session Role's Commandline Object in UnrealTestNode.cs
- L521 _public property_ `public List<string> Controllers { get; set; }` — Controllers for this role
- L526 _public property_ `public List<IUnrealRoleConfiguration> RoleConfigurations { get; set; }` — Collection of modular configurations applied to this role
- L532 _public property_ `public string ExplicitClientCommandLine { get; set; }` — Explicit command line for this role. If this is set no other options from above or configs will be applied!
- L534 _public property_ `public List<UnrealFileToCopy> FilesToCopy { get; set; }`
- L539 _public property_ `public List<EIntendedBaseCopyDirectory> AdditionalArtifactDirectories { get; set; }` — Additional directories to
- L544 _public property_ `public string MapOverride { get; set; }` — A map value passed in per server in case a test needs multiple servers on different maps.
- L549 _public field_ `public PreConfigureDeviceHandler PreConfigureDevice` — Allows for individual roles to configure their associated Target device before build installation
- L554 _public field_ `public ConfigureDeviceHandler ConfigureDevice` — Allows for individual roles to configure their associated Target device after build installation and AppInstall creation
- L559 _public field_ `public bool CompressScreenshots` — Whether this role will compress screenshots produced as an artifact into a jpeg format
- L564 _public field_ `public bool CreateGifFromScreenshots` — Whether this role will create a gif from screenshots produced as an artifact
- L569 _public property_ `public bool SkipCleanDeviceArtifacts { get; set; }` — Whether or not this role should skip the cleaning of its device's artifact between each test run
- L575 _public property_ `public bool ArchiveDevArtifacts { get; set; }` — Whether or not this role will save artifacts when running with -dev. These can be huge, so be cautious with using this.
- L580 _public property_ `public bool RespawnProcessOnUnexpectedExit { get; set; }` — Whether to respawn this process automatically if it fails unexpectedly
- L585 _public field_ `public OnTryToRestoreProcessDelegate OnTryToRestoreProcess` — What to do if this role exits unexpectedly and we try to restore it

#### class `Gauntlet.UnrealHeartbeatOptions`  
`public class UnrealHeartbeatOptions`  
_public; L594-636_
- desc: Collection of parameters that control how heartbeats coming from the native gauntlet controller for this role should be handled. To make best use of this, your GauntletTestController should regularly call MarkHeartbeatActive(). Set bExpectHeartbeats to true to enable killing the App Instance when expected heartbeats are not detected.
- L599 _public field_ `public float HeartbeatPeriod` — The amount of time between regular heartbeats. This value is passed along through the command line.
- L604 _public field_ `public bool bExpectHeartbeats` — Set to true to allow the App Instance to be killed when expected heartbeats are not detected. If left false, heartbeat timeouts will not result in any action or timeouts.
- L609 _public field_ `public float TimeoutBeforeFirstActiveHeartbeat` — The max amount of time allowed before the first "active" heartbeat is detected
- L614 _public field_ `public float TimeoutBetweenActiveHeartbeats` — The max amount of time allowed between "active" heartbeats
- L619 _public field_ `public float TimeoutBetweenAnyHeartbeats` — The max amount of time allowed between any heartbeats, active or not
- L624 _public field_ `public float LogHeartbeatInterval` — The minimum time interval between retrieval of heartbeat logs
- L626-634 _public ctor_ `public UnrealHeartbeatOptions(float InHeartbeatPeriod = 30f, bool bShouldExpectHeartbeats = false, float InTimeoutBeforeFirstActiveHeartbeat = 0f, float InTimeoutBetweenActiveHeartbeats = 0f, float InTimeoutBetweenAnyHeartbeats = 90f, float InLogHeartbeatInterval = 0f)`

#### class `Gauntlet.UnrealTestConfiguration`  
`public class UnrealTestConfiguration : IConfigOption<UnrealAppConfig>`  
_public; L653-1145_
- inherits: `IConfigOption<UnrealAppConfig>`
- desc: TestConfiguration describes the setup that is required for a specific test. Protected parameters are generally test-wide options that are read from the command line and which tests cannot control. Public parameters are options that individual tests can configure as appropriate. Each test can (and should) supply its own configuration by overriding TestNode.GetConfiguration. At a minimum a test must add one or more roles and the command line or controller necessary to execute the tests. Inherited classes should implement ApplyToConfig to apply the options they expose, and should ball the base class implementation.
- L663 _protected property_ `protected int ScreenshotPeriod { get; set; }` — attrs: `[AutoParam(0)]` — How often to grab a screenshot
- L670 _public property_ `public bool NullRHI { get; set; }` — attrs: `[AutoParam(false)]` — Use a nullrhi for tests
- L678 _public field_ `public string Map = ""` — attrs: `[AutoParam]` — Map to use
- L685 _public property_ `public bool IgnoreDefaultResolutionAndWindowMode { get; set; }` — attrs: `[AutoParam(false)]` — If true, explicitly do not set the default resolution of 1280x720 or the window mode. Most tests should not do this.
- L692 _public property_ `public int ResX { get; set; }` — attrs: `[AutoParam(0)]` — The width resolution.
- L699 _public property_ `public int ResY { get; set; }` — attrs: `[AutoParam(0)]` — The height resolution.
- L706 _protected property_ `protected bool Windowed { get; set; }` — attrs: `[AutoParam(false)]` — Set to Windowed mode (same as -WindowMode=Windowed);
- L713 _public property_ `public EWindowMode WindowMode { get; set; }` — attrs: `[AutoParam(EWindowMode.Windowed)]` — Which window mode to use for the PC or Mac or Linux client. Only Windowed and Fullscreen are fully supported.
- L720 _public property_ `public bool Attended { get; set; }` — attrs: `[AutoParam(false)]` — Do not specify the unattended flag
- L726 _public property_ `public float MaxDuration { get; set; }` — attrs: `[AutoParam(600.0f)]` — Maximum duration in seconds that this test is expected to run for. Defaults to 600.
- L732 _public property_ `public int MaxRetries { get; set; }` — attrs: `[AutoParam(3)]` — Max number of retries in case of critical failure
- L738 _public field_ `public bool WriteTestResultsForHorde = false` — attrs: `[AutoParam]` — Produce test artifacts for Horde build system
- L744 _public field_ `public string HordeTestDataPath = ""` — attrs: `[AutoParam]` — Path to store test data for Horde build system
- L750 _public field_ `public string HordeTestDataKey = ""` — attrs: `[AutoParam]` — Key to store Horde Test Data
- L756 _public field_ `public string HordeArtifactPath = ""` — attrs: `[AutoParam]` — Path to store test artifacts for Horde build system
- L762 _public field_ `public string PreFlightChange = ""` — attrs: `[AutoParam]` — PreFlight change id
- L768 _public field_ `public string PublishTelemetryTo = ""` — attrs: `[AutoParam]` — Telemetry Database config to use
- L774 _public field_ `public string DatabaseConfigPath = ""` — attrs: `[AutoParam]` — Path to Database config file
- L779 _public property_ `public EMaxDurationReachedResult MaxDurationReachedResult { get; set; }` — What the test result should be treated as if we reach max duration.
- L785 _public property_ `public bool FailOnEnsures { get; set; }` — attrs: `[AutoParam(false)]` — Whether ensures are considered a failure
- L791 _public property_ `public bool IgnoreEnsures { get; set; }` — attrs: `[AutoParam(false)]` — Whether ensures should be ignored from report
- L797 _public property_ `public bool ShowWarningsInSummary { get; set; }` — attrs: `[AutoParam(false)]` — Whether warnings are shown in the summary
- L803 _public property_ `public bool ShowErrorsInSummary { get; set; }` — attrs: `[AutoParam(false)]` — Whether warnings are shown in the summary
- L808 _public property_ `public bool AllRolesExit { get; set; }` — Whether the test expects all roles to exit
- L813 _public property_ `public UnrealHeartbeatOptions HeartbeatOptions { get; set; }` — The collection of options which define heartbeat behavior
- L819 _public property_ `public bool DisableHeartbeatTimeout { get; set; }` — attrs: `[AutoParam(false)]` — Prevents heartbeats timeouts from being checked so that tests will not fail from missed heartbeats
- L825 _public field_ `public int ForceVerticalRes = 0` — attrs: `[AutoParam]` — Enforce Vertical resolution
- L831 _public property_ `public bool CookedEditor { get; set; }` — attrs: `[AutoParam(false)]` — Consider the package as CookedEditor
- L837 _public property_ `public string VerboseLogCategories { get; set; }` — attrs: `[AutoParam]` — Enforce Verbose logging for a list of loggers
- L843 _public property_ `public string TagFilter { get; set; }` — attrs: `[AutoParam]` — Apply a tag filter, restricting tests to run
- L848 _public property_ `public bool IgnoreRoleFailures { get; set; }` — If true, an individual process role failing (i.e. crash) does not flag the test as a failure
- L855 _public property_ `public Dictionary<UnrealTargetRole, List<UnrealTestRole>> RequiredRoles { get; set; }` — A map of role types to test roles
- L861 _public property_ `public List<string> LogCategoriesForEvents { get; set; }` — Log channels that should be treated as events for this test. Warnings & Errors in these channels will be promoted to test warnings and errors. For LogFoo return "Foo".
- L866-876 _public ctor_ `public UnrealTestConfiguration()` — Base constructor
- L883-890 _public method_ `public void AddDummyClients(int Quantity, string AdditionalCommandLine = "")` — Set this test to use dummy, renderless clients.
- L898-905 _public method_ `public UnrealTestRole RequireRole(UnrealTargetRole InRole)` — Adds one role of the specified type to this test. With inherited tests this could return an existing role so care should be added to append commandlines, controllers etc
- L907-914 _public method_ `public UnrealTestRole RequireRole(UnrealTargetRole InRole, UnrealTargetPlatform PlatformOverride)`
- L916-920 _public method_ `public UnrealTestRole GetEditorRole()`
- L928-931 _public method_ `public List<UnrealTestRole> RequireRoles(UnrealTargetRole InRole, int Count)` — Adds 'Count' of the specified roles to this test
- L936-939 _public method_ `public void ClearRoles()` — Clears all roles from this config.
- L941-961 _public method_ `public List<UnrealTestRole> RequireRoles(UnrealTargetRole InRole, UnrealTargetPlatform? PlatformOverride, int Count, ERoleModifier roleType = ERoleModifier.None)`
- L968-978 _public method_ `public int RoleCount(UnrealTargetRole Role)` — Returns the number of roles of the specified type that exist for this test
- L985-992 _public method_ `public List<UnrealTestRole> GetRequiredRoles(UnrealTargetRole InRole)` — Return the list of required roles for the target role
- L998-1026 _public method_ `public UnrealTestRole GetMainRequiredRole()` — Return the main required role to execute the test.
- L1032-1035 _public method_ `public void ApplyToConfig(UnrealAppConfig AppConfig)`
- L1044-1144 _public method_ `public virtual void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)` — Apply our options to the provided app config

#### Namespace-level symbols

- L416 _public delegate_ `public delegate void PreConfigureDeviceHandler(ITargetDevice Device, UnrealSessionRole Role)` — Delegate for role device pre-configuration
- L421 _public delegate_ `public delegate void ConfigureDeviceHandler(ITargetDevice Device)` — Delegate for role device configuration
- L427 _public delegate_ `public delegate void OnTryToRestoreProcessDelegate(UnrealSessionInstance.RoleInstance InRole)` — Delegate to fire when a process exits unexpectedly. We pass in the Role Instance instead of the Role so we can get all of the instantiated data.

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealTestContext.cs` (Gauntlet.Automation)


#### class `Gauntlet.TestRequest`  
`public class TestRequest`  
_public; L14-29_
- L16 _public property_ `public string TestName { get; set; }`
- L18 _public field_ `public List<ArgumentWithParams> Platforms = new List<ArgumentWithParams>()`
- L20 _public property_ `public Params TestParams { get; set; }`
- L22-25 _public method_ `public override string ToString()`
- L28 _public method_ `static public TestRequest CreateRequest(string InName)`

#### class `Gauntlet.UnrealTestOptions`  
`public class UnrealTestOptions : TestExecutorOptions, IAutoParamNotifiable`  
_public; L37-398_
- inherits: `TestExecutorOptions, IAutoParamNotifiable`
- desc: Represents options that can be configured on the test context. These options are considered global, e.g they apply to all tests executed in a given session and are not exposed to invidiual tests to modify
- L42 _public property_ `public Params Params { get; set; }` — Params for this test run
- L49 _public field_ `public string Project = ""` — attrs: `[AutoParam]` — Name or path to this this project. This will be normalized to the project name and the path to the project file available via the ProjectPath argument,
- L54 _public property_ `public FileReference ProjectPath { get; set; }` — Returns the path to the project file. Created based on the Project argument
- L60 _public field_ `public string Build = ""` — attrs: `[AutoParamWithNames("Build", "Builds")]` — Reference to the build that is being tested
- L66 _public field_ `public string EditorDir = ""` — attrs: `[AutoParam]` — Location of the editor build
- L72 _public field_ `public bool UsesSharedBuildType = true` — attrs: `[AutoParam(true)]` — Does this project use 'Game' or Client/Server?
- L75 _public field_ `public Type BuildSourceType`
- L81 _public field_ `public UnrealTargetConfiguration Configuration` — attrs: `[AutoParam(UnrealTargetConfiguration.Development)]` — Configuration to perform tests on
- L86 _public field_ `public List<ArgumentWithParams> PlatformList = new List<ArgumentWithParams>()` — Platforms to perform tests on and their params
- L91 _public field_ `public Dictionary<UnrealTargetRole, UnrealTargetPlatform> RolePlatformOverrides = ...` — Optional set of platform overrides for a given role
- L91 _public field_ `public Dictionary< RolePlatformOverrides = new Dictionary<UnrealTargetRole, UnrealTargetPlatform>()` — Optional set of platform overrides for a given role
- L96 _public field_ `public List<TestRequest> TestList = new List<TestRequest>()` — Tests to run and their params.
- L101 _public field_ `public List<ArgumentWithParams> DeviceList = new List<ArgumentWithParams>()` — List of devices to use for tests
- L107 _public field_ `public string DeviceURL` — attrs: `[AutoParam("")]` — Service URL of devices to use for tests
- L113 _public field_ `public int MaxLocalDevices` — attrs: `[AutoParam(10)]` — Maximum number of available local(host platform) devices
- L119 _public field_ `public int MaxVirtualDevices` — attrs: `[AutoParam(2)]` — Maximum number of available virtual devices of each type (supported on the host platform)
- L125 _public field_ `public string JobDetails` — attrs: `[AutoParam("")]` — Details for current job (example: link to CIS, etc)
- L133 _public field_ `public string Namespaces` — attrs: `[AutoParam("")]` — Comma-separated list of namespaces to check for tests. E.g. with test 'Foo' and namespace 'Bar' then Bar.Foo and Foo will be checked for.
- L135 _public field_ `public IEnumerable<string> SearchPaths`
- L141 _public property_ `public string Sandbox { get; set; }` — attrs: `[AutoParam("")]` — Directory to store temp files (including builds that need to be run locally)
- L147 _public property_ `public bool Attended { get; set; }` — attrs: `[AutoParam(false)]` — Skip any check or copying of builds. Mostly useful when debugging
- L153 _public property_ `public bool SkipCopy { get; set; }` — attrs: `[AutoParam(false)]` — Skip any check or copying of builds. Mostly useful when debugging
- L159 _public property_ `public bool Dev { get; set; }` — attrs: `[AutoParam(false)]` — 'Dev' - turns on a few options, most useful of which is that local exes will be used if newer
- L165 _public property_ `public bool LogPSO { get; set; }` — attrs: `[AutoParam(false)]` — 'LogPSO' - turns on logpso on the client and uploads the files to P:
- L171 _public property_ `public bool NullRHI { get; set; }` — attrs: `[AutoParam(false)]` — Use a nullrhi
- L178 _public field_ `public string TempDir` — attrs: `[AutoParam("")]` — Location to store temporary files. Defaults to GauntletTemp in the root of the current drive
- L184 _public field_ `public string LogDir` — attrs: `[AutoParam("")]` — Location to store log files. Defaults to TEmpDir/Logs
- L190 _public field_ `public string ArtifactName` — attrs: `[AutoParam("")]` — Custom name for the directory under LogDir where artifacts are stored.
- L196 _public field_ `public string ArtifactPostfix` — attrs: `[AutoParam("")]` — Psotfix to apply to the artifact folder (e.g. don't replace the whole thing like ArtifactName, just append this string)
- L203 _public property_ `public string CustomModuleRoles { get; set; }` — attrs: `[AutoParam("")]` — Add custom module name/role pair to identify custom project target executable Format is : + :
- L209 _public property_ `public string Target { get; set; }` — attrs: `[AutoParam("")]` — Set the target name of the module name to identify a custom project target executable
- L215 _public field_ `public bool Verbose` — attrs: `[AutoParamWithNames(false, "Verbose", "Gauntlet.Verbose")]` — Less logging
- L222 _public field_ `public bool VeryVerbose` — attrs: `[AutoParam(false)] [AutoParamWithNames(false, "VeryVerbose", "Gauntlet.VeryVerbose")]` — Less logging
- L224-230 _public ctor_ `public UnrealTestOptions()`
- L236-397 _public method_ `public virtual void ParametersWereApplied(string[] InParams)` — Called after command line params are applied. Perform any checks / fixup

#### class `Gauntlet.UnrealTestRoleContext`  
`public class UnrealTestRoleContext : ICloneable`  
_public; L410-449_
- inherits: `ICloneable`
- desc: This class describes the "context" that is used for a given role. E.g. if the test specifies it needs a Client role then this class determines what that actually means, and even whether it's really a client or a client emulated by running the editor with -game This mappinf of role->context is performed by the TestContext so this structure holds the absolute truth of how a client is configured
- L415 _public field_ `public UnrealTargetRole Type` — Role of this role :)
- L420 _public field_ `public UnrealTargetPlatform Platform` — Platform that this role is run under
- L425 _public field_ `public UnrealTargetConfiguration Configuration` — Configuration that this role is run under
- L430 _public field_ `public string ExtraArgs` — Extra args to use for this role
- L436 _public field_ `public bool Skip` — Are these roles actually skipped during tests? Useful if you need to manually start a role when debugging etc
- L438-442 _public method_ `public object Clone()`
- L444-448 _public method_ `public override string ToString()`

#### class `Gauntlet.UnrealTestContext`  
`public class UnrealTestContext : ITestContext, ICloneable`  
_public; L455-524_
- inherits: `ITestContext, ICloneable`
- desc: This class contains the Context - build and global options - that one or more tests are going to be executed under.
- L458 _public property_ `public UnrealBuildSource BuildInfo { get; set; }`
- L461 _public field_ `public string WorkerJobID`
- L466 _public property_ `public UnrealTestOptions Options { get; set; }` — Global options for this test
- L468 _public property_ `public Params TestParams { get; set; }`
- L470-473 _public method_ `public UnrealTestRoleContext GetRoleContext(UnrealTargetRole Role)`
- L475 _public property_ `public Dictionary<UnrealTargetRole, UnrealTestRoleContext> RoleContext { get; set; }`
- L480 _public field_ `public UnrealDeviceTargetConstraint Constraint` — Target constraint that this test is run under
- L482-490 _public ctor_ `public UnrealTestContext(UnrealBuildSource InBuildInfo, Dictionary<UnrealTargetRole, UnrealTestRoleContext> InRoleContexts, UnrealTestOptions InOptions)`
- L492-501 _public method_ `public object Clone()`
- L503-506 _public method_ `public override string ToString()`
- L508-523 _public method_ `public string ToString(bool bWithServerType = false)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealTestEvent.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealTestEvent`  
`public class UnrealTestEvent : ITestEvent`  
_public; L13-78_
- inherits: `ITestEvent`
- desc: Unreal-specific implementation of a TestEvent
- L18 _public property_ `public EventSeverity Severity { get; set; }` — Level of severity that this event represents
- L21 _public property_ `public DateTime Time { get; }`
- L24 _public property_ `public string Summary { get; set; }`
- L27 _public property_ `public IEnumerable<string> Details { get; set; }`
- L30 _public property_ `public IEnumerable<string> Callstack { get; set; }`
- L33 _public property_ `public bool IsEnsure { get; set; }`
- L36 _public property_ `public bool IsSanReport { get; set; }`
- L39 _public property_ `public bool IsError => ...`
- L42 _public property_ `public bool IsWarning => ...`
- L45-64 _public ctor_ `public UnrealTestEvent(DateTime InTime, EventSeverity InSeverity, string InSummary, IEnumerable<string> InDetails, UnrealLog.CallstackMessage InCallstack = null)`
- L67-68 _public ctor_ `public UnrealTestEvent(EventSeverity InSeverity, string InSummary, IEnumerable<string> InDetails, UnrealLog.CallstackMessage InCallstack = null) : this(DateTime.UtcNow, InSeverity, InSummary, InDetails, InCallstack)`
- L71-77 _public ctor_ `public UnrealTestEvent(EventSeverity InSeverity, string InFormat, params object[] Args) : this(InSeverity, string.Empty, Enumerable.Empty<string>())`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Base/Gauntlet.UnrealTestNode.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealTestNode`  
`public abstract class UnrealTestNode<TConfigClass> : BaseTest, IDisposable where TConfigClass : UnrealTestConfiguration, new()`  
_public; L30-3069_
- inherits: `BaseTest, IDisposable`
- constraints: `where TConfigClass : UnrealTestConfiguration, new()`
- desc: Implementation of a Gauntlet TestNode that is capable of executing tests on an Unreal "session" where multiple Unreal instances may be involved. This class leans on UnrealSession to do the work of spinning up, monitoring, and shutting down instances. Those operations plus basic validation of Unreal's functionality are used to provide the required ITestNode interfaces
- L44 _public field_ `public ITestAuditMetadata TestMetadata` — Test Metadata for audit
- L50-56 _protected property_ `protected virtual string ReportTestKey { get; }` — Unique key to identify and cross reference test across test sessions
- L57 _protected property_ `protected virtual string HordeReportTestKey => ...`
- L62-74 _protected property_ `protected virtual string ReportTestName { get; }` — The test name used in report
- L75 _protected property_ `protected virtual string HordeReportTestName => ...`
- L80 _protected property_ `protected virtual TestHarness? TestHarness => ...` — The harness used to execute the test
- L85 _protected property_ `protected virtual TestProfile? TestProfile => ...` — The test profile (unit test, functional, performance)
- L90 _protected property_ `protected virtual TestTeam? TestTeam => ...` — The team for which the test is for
- L95 _protected property_ `protected virtual string? TestIntent => ...` — Short description of the test intent
- L100 _protected property_ `protected virtual TestTag[]? TestTags => ...` — The tags associated with this test
- L106 _public property_ `public override string Name { get; }` — Returns an identifier for this test
- L111 _public property_ `public virtual string Suite { get; }` — Returns the test suite. Default to the project name
- L116 _public property_ `public virtual string Type { get; }` — Returns an identifier for this type of test
- L121 _public property_ `public override bool LogWarningsAndErrorsAfterSummary { get; set; }` — This class will log its own warnings and errors as part of its summary
- L126 _public property_ `public override float MaxDuration { get; set; }` — How long this test should run for, set during LaunchTest based on results of GetConfiguration
- L130 _public property_ `public BehaviorFlags Flags { get; set; }` — Behavior flags for this test
- L134 _public property_ `public override TestPriority Priority { get; }` — Priority of this test
- L140 _protected delegate_ `protected delegate void PopulateTestPhasesReport(AutomatedTestSessionData TestReport)` — Delegate type to populate test phase in report
- L144 _protected field_ `protected PopulateTestPhasesReport OnPopulateTestPhases` — Call when populating Horde test report
- L149 _protected field_ `protected PhaseQueue Phases` — Phase tracker
- L154-157 _public method_ `public virtual IEnumerable<string> GetHeartbeatLogCategories()` — Returns a list of all log channels the heartbeat tick should look for.
- L162-172 _public method_ `public override IEnumerable<string> GetWarnings()` — Returns Warnings found during tests. By default only ensures and are considered
- L178-188 _public method_ `public override IEnumerable<string> GetErrors()` — Returns Errors found during tests. By default fatal and error severities are considered. returning lists of event summaries
- L193-204 _public method_ `public virtual IEnumerable<string> GetErrorsAndAbnornalExits()` — Returns Errors found during tests. Including Abnormal Exit reasons
- L211-214 _public method_ `public virtual void ReportError(string Message, params object[] Args)` — Report an error - Legacy. Instead, please consider using ReportInterrupt for functional test problems, or ReportFailure for actual test failures
- L222-225 _public method_ `public virtual void ReportInterrupt(string Message, params object[] Args)` — Report a test-halting error that is NOT directly related to the behavior that is being tested. This method is deprecated. Please use Gauntlet.Reporter.Instance.Interrupt instead of this method.
- L233-236 _public method_ `public virtual void ReportFailure(string Message, params object[] Args)` — Report a test failure. Specifically, the behavior that is targeted by the test case did not function as expected. This method is deprecated. Please use Gauntlet.Reporter.Instance.Failure instead of this method.
- L244-247 _public method_ `public virtual void ReportWarning(string Message, params object[] Args)` — Report a warning. This method is deprecated. Please use Gauntlet.Reporter.Instance.Warning instead of this method.
- L255-258 _public method_ `public virtual void ReportInfo(string Message, params object[] Args)` — Report information. This method is deprecated. Please use Gauntlet.Reporter.Instance.Info instead of this method.
- L265 _public property_ `public UnrealTestContext Context { get; set; }` — Our context that holds environment wide info about the required conditions for the test
- L270 _public property_ `public UnrealSessionInstance TestInstance { get; set; }` — When the test is running holds all running Unreal processes (clients, servers etc).
- L275 _public property_ `public string ArtifactPath { get; set; }` — Path to the directory that logs and other artifacts are copied to after the test run.
- L330 _public property_ `public IEnumerable<UnrealRoleResult> RoleResults { get; set; }` — After the test completes holds artifacts for each process (clients, servers etc).
- L335 _public property_ `public IEnumerable<UnrealRoleArtifacts> SessionArtifacts { get; set; }` — After the test completes holds artifacts for each process (clients, servers etc).
- L340 _protected property_ `protected IReadOnlyCollection<UnrealTestEvent> TestNodeEvents => ...` — Collection of events thrown by gauntlet itself during the test run.
- L341 _private property_ `private ConcurrentQueue<UnrealTestEvent> _TestNodeEvents { get; set; }`
- L343-346 _public method_ `public override void AddTestEvent(UnrealTestEvent InEvent)`
- L351 _protected property_ `protected UnrealSession UnrealApp { get; set; }` — UnrealSession for this instance
- L356 _private field_ `private Dictionary<RoleInstance, UnrealLogStreamParser> RoleParsers = ...` — Used to track each running app's new log output
- L356 _private field_ `private Dictionary< RoleParsers = new Dictionary<RoleInstance, UnrealLogStreamParser>()` — Used to track each running app's new log output
- L362-369 _private method_ `private UnrealLogStreamParser GetParserForRole(RoleInstance Role)` — Returns the Role Log Parser from a given RoleInstance key. If the key does not exist it will be created before returning it.
- L371 _private field_ `private int CurrentPass`
- L373 _private field_ `private int NumPasses`
- L375 _protected field_ `static protected DateTime SessionStartTime = DateTime.MinValue`
- L377 _public property_ `public int Retries { get; set; }`
- L378 _private field_ `private int MaxRetries = 3`
- L379 _public method_ `public virtual bool CanRetry()`
- L380-393 _public method_ `public virtual bool SetToRetryIfPossible()`
- L401-404 _protected method_ `protected virtual bool CheckShouldRetry()` — PLEASE READ BEFORE OVERRIDING: This checks a condition defined in a test node at the end of the test to determine whether or not the test should run again. This should only be used in very specific instances to retry for user defined dependency/service failure string. Example: Useful for unexpected unattended log outs during testing
- L406-409 _public method_ `public virtual bool IsSetToRetry()`
- L416 _protected field_ `protected Version TestVersion`
- L421 _private field_ `private TestResult UnrealTestResult` — Our test result. May be set directly, or by overriding GetUnrealTestResult()
- L423 _protected field_ `protected TConfigClass CachedConfig = null`
- L425 _protected field_ `protected DateTime TimeOfFirstMissingProcess`
- L427 _protected property_ `protected int TimeToWaitForProcesses { get; set; }`
- L429 _protected field_ `protected bool bDisableHeartbeatLogging = false`
- L431 _protected field_ `protected DateTime LastHeartbeatTime = DateTime.MinValue`
- L432 _protected field_ `protected DateTime LastActiveHeartbeatTime = DateTime.MinValue`
- L433 _private field_ `private DateTime LastHeartbeatLogTime = DateTime.MinValue`
- L438 _protected field_ `static protected HashSet<string> ReservedArtifcactPaths = new HashSet<string>()`
- L443 _public field_ `public List<GauntletParamDescription> SupportedParameters = new List<GauntletParamDescription>()` — Help doc-style list of parameters supported by this test. List can be divided into test-specific and general arguments.
- L449 _protected field_ `protected List<KeyValuePair<string, string>> SampleCommandlines = ...` — Optional list of provided commandlines to be displayed to users who want to look at test help docs. Key should be the commandline to use, value should be the description for that commandline.
- L449 _protected field_ `protected List<KeyValuePair< SampleCommandlines = new List<KeyValuePair<string, string>>()` — Optional list of provided commandlines to be displayed to users who want to look at test help docs. Key should be the commandline to use, value should be the description for that commandline.
- L451-454 _public method_ `public void AddSampleCommandline(string Commandline, string Description)`
- L459 _private field_ `private List<string> HeartbeatLogCategories = new List<string>()` — List of log event categories to track with the heartbeat system.
- L465-498 _public ctor_ `public UnrealTestNode(UnrealTestContext InContext)` — Constructor. A context of the correct type is required
- L500-503 _private* dtor_ `~UnrealTestNode()`
- L506 _private field_ `private bool disposedValue = false`
- L508-529 _protected method_ `protected virtual void Dispose(bool disposing)`
- L532-536 _public method_ `public void Dispose()`
- L539-547 _public method_ `public override String ToString()`
- L549-559 _public method_ `public string GetMainRoleContextString()`
- L566-569 _public method_ `public override void SetContext(ITestContext InContext)` — Sets the context that tests run under. Called once during creation
- L577-585 _public method_ `public virtual TConfigClass GetConfiguration()` — Returns information about how to configure our Unreal processes. For the most part the majority of Unreal tests should only need to override this function
- L591-599 _protected method_ `protected TConfigClass GetCachedConfiguration()` — Returns the cached version of our config. Avoids repeatedly calling GetConfiguration() on derived nodes
- L605-619 _protected method_ `protected TestPriority GetPriority()` — Returns a priority value for this test
- L621-624 _protected method_ `protected virtual IEnumerable<RoleInstance> FindAnyMissingRoles()`
- L626-651 _protected method_ `protected virtual bool TryRestoreAllMissingRoles(IEnumerable<UnrealSessionInstance.RoleInstance> MissingRoles)`
- L658-701 _public method_ `public virtual bool IsTestRunning()` — Checks whether the test is still running. The default implementation checks whether all of our processes are still alive.
- L703-842 _protected method_ `protected bool PrepareUnrealApp()`
- L844-854 _public method_ `public override bool IsReadyToStart()`
- L861-930 _protected method_ `protected string ReserveArtifactPath()` — Generates a unique path for the test artifacts and reserves it This will create the target directory, deleting it first if it exists already
- L937-1008 _public method_ `public override bool StartTest(int Pass, int InNumPasses)` — Called by the test executor to start our test running. After this Test.Status should return InProgress or greater
- L1017-1039 _public method_ `public void AddLinkToReport(ITestReport Report, string ReportName, string URLLink, string TextLink = null)` — Used to Add a URL to a Horde Report.
- L1041-1084 _public method_ `public virtual void PopulateCommandlineInfo()`
- L1086-1129 _protected method_ `protected virtual IEnumerable<KeyValuePair<string, object>> GetDistilledTestParams()`
- L1131-1153 _public method_ `public override string GetRunLocalCommand(string LaunchingBuildCommand)`
- L1159-1181 _public method_ `public override void CleanupTest()` — Cleanup all resources
- L1188-1215 _public method_ `public override bool RestartTest()` — Restarts the provided test. Only called if one of our derived classes requests it via the Status result
- L1223-1230 _public method_ `public virtual void TickTest(UnrealSessionInstance InInstance)` — Periodically called while the test is running. A chance for tests to examine their health, log updates etc. Base classes must call this or take all responsibility for setting Status as necessary
- L1238-1249 _public method_ `public override void TickTest()` — Periodically called while the test is running. A chance for tests to examine their health, log updates etc. Base classes must call this or take all responsibility for setting Status as necessary
- L1255-1258 _protected method_ `protected virtual void StopTest(bool WasCancelled)` — This class is here to provide compatibility
- L1265-1406 _public method_ `public override void StopTest(StopReason InReason)` — Called when a test has completed. By default saves artifacts and calls CreateReport
- L1411-1419 _protected method_ `protected virtual void HandleCreateReportFailure(UnrealTestContext Context, string Message = "")` — Called when report creation fails, by default logs warning with failure message
- L1424 _public property_ `public bool CreateReportFailed { get; set; }` — Whether creating the test report failed
- L1429-1465 _public method_ `public virtual void AddProcessResultEventsFromTestNode()` — Add all of our process results to the gauntlet event summary list.
- L1471-1515 _public method_ `public override void DisplayCommandlineHelp()` — Display all of the defined commandline information for this test. Will display generic gauntlet params as well if -help=full is passed in.
- L1527-1537 _public method_ `public virtual ITestReport CreateReport(TestResult Result, UnrealTestContext Context, UnrealBuildSource Build, IEnumerable<UnrealRoleResult> RoleResults, string ArtifactPath)` — Optional function that is called on test completion and gives an opportunity to create a report. The returned class will later be passed to SubmitToDashboard if submission of results is enabled
- L1544-1553 _public method_ `public virtual ITestReport CreateReport(TestResult Result)` — Optional function that is called on test completion and gives an opportunity to create a report
- L1555-1563 _private method_ `private string GetHordeTestDataKey_legacy()`
- L1569-1659 _protected method_ `protected virtual ITestReport CreateSimpleReportForHorde(TestResult Result)` — Generate a Simple Test Report from the results of this test
- L1665-1681 _protected method_ `protected virtual void PopulatePhaseReport(AutomatedTestSessionData SessionData)` — Populate report phases from test execution
- L1688-1725 _protected method_ `protected virtual void PopulateClosurePhase(AutomatedTestSessionData TestReport, string PhaseName = "Closure", DateTime? SessionTime = null, float TimeElapseSeconds = 0)` — Default populate closure phase
- L1727-1738 _private method_ `private AutomatedTestSessionData.TestDevice AddRoleDeviceToSessionReport(UnrealRoleResult RoleResult, AutomatedTestSessionData TestReport)`
- L1740-1765 _private method_ `private SimpleTestReport CreateSimpleReportForHorde_legacy(TestResult Result)`
- L1773-1943 _public method_ `public virtual ITestReport CreateUnrealEngineTestPassReport(string UnrealAutomatedTestReportPath, string ReportURL)` — Generate report from Unreal Automated Test Results
- L1950-1983 _protected method_ `protected virtual void SetReportMetadata(ITestReport Report, IEnumerable<UnrealTestRole> Roles)` — Set Metadata on ITestReport
- L1985-2001 _private* method_ `void SubmitToHorde(ITestReport Report)`
- L2007-2040 _public method_ `public virtual void SubmitToDashboard(ITestReport Report)` — Optional function that is called on test completion and gives an opportunity to submit a report to a Dashboard
- L2048-2051 _public method_ `public virtual void SaveArtifacts_DEPRECATED(string OutputPath)` — Called to request that the test save all artifacts from the completed test to the specified output path. By default the app will save all logs and crash dumps
- L2059-2067 _public method_ `public virtual IEnumerable<UnrealRoleArtifacts> SaveRoleArtifacts(string OutputPath)` — Called to request that the test save all artifacts from the completed test to the specified output path. By default the app will save all logs and crash dumps
- L2078-2169 _protected method_ `protected virtual UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)` — Parses the provided artifacts to determine the cause of an exit and whether it was abnormal
- L2181-2235 _protected method_ `protected virtual IEnumerable<UnrealTestEvent> CreateEventListFromArtifact(StopReason InReason, UnrealRoleArtifacts InRoleArtifacts, UnrealLog InLog, UnrealProcessResult ProcessResult)` — Creates an EventList from the artifacts for the specified role. By default this will be asserts (errors), ensures (warnings) from the log, plus any log entries from categories that are the list returned by GetMonitoredLogCategories(). Nodes can also set their behavior flags to elevate *all* warnings/errors
- L2244-2265 _protected method_ `protected virtual UnrealRoleResult CreateRoleResultFromArtifact(StopReason InReason, UnrealRoleArtifacts InRoleArtifacts)` — Returns a RoleResult, a representation of this roles result from the test, for the provided artifact
- L2272-2275 _protected method_ `protected virtual UnrealLog CreateLogSummaryFromArtifact(UnrealRoleArtifacts InArtifacts)` — Returns a log summary from the provided artifacts.
- L2284-2287 _protected method_ `protected virtual IEnumerable<UnrealRoleResult> CreateRoleResultsFromArtifacts(StopReason InReason, IEnumerable<UnrealRoleArtifacts> InAllArtifacts)` — Returns a list of all results for the roles involved in this test by calling CreateRoleResultFromArtifact for all artifacts in the list
- L2290-2368 _private method_ `private void LogHeartbeat(UnrealSessionInstance InInstance)`
- L2370-2421 _private method_ `private void CheckHeartbeat()`
- L2428-2453 _protected method_ `protected virtual string GetRoleResultHash(UnrealRoleResult InResult)` — Returns a hash that represents the results of a role. Should be 0 if no fatal errors or ensures
- L2459-2470 _protected method_ `protected virtual string GetTestResultHash()` — Returns a hash that represents the failure results of this test. If the test failed this should be an empty string
- L2477-2480 _protected method_ `protected virtual string GetFormattedRoleSummary(UnrealRoleResult InRoleResult)` — Deprecated
- L2495-2541 _protected method_ `protected static LogEvent DecomposeAssert(UnrealTestEvent Event, int MaxCallstackLines = 0)` — Decompose an assert event so that it can be easily logged.
- L2548-2714 _protected method_ `protected virtual void LogRoleSummary(UnrealRoleResult InRoleResult)` — Log a formatted summary of the role that's suitable for displaying
- L2720-2790 _protected method_ `protected virtual string CreateFormattedEventListFromTestNode()` — Returns a formatted summary of the events that were thrown by the test node itself during run.
- L2795-2798 _public method_ `public int GetCurrentPass()` — Returns the current 0-based Pass count for this node.
- L2804-2807 _public method_ `public int GetNumPasses()` — Returns the current total Pass count for this node
- L2813-2821 _public method_ `public sealed override TestResult GetTestResult()` — Result of the test once completed. Nodes inheriting from us should override this if custom results are necessary
- L2826-2829 _public method_ `public override void SetTestResult(TestResult testResult)` — Result of the test once completed. Nodes inheriting from us should override
- L2837-2845 _protected method_ `protected void SetUnrealTestResult(TestResult Result)` — Allows tests to set this at anytime. If not called then GetUnrealTestResult() will be called when the framework first calls GetTestResult()
- L2852-2861 _protected method_ `protected virtual IEnumerable<UnrealRoleResult> GetRolesThatExitedAbnormally()` — Return all artifacts that are exited abnormally. An abnormal exit is termed as a fatal error, crash, assert, or other exit that does not appear to have been caused by completion of a process
- L2867-2876 _protected method_ `protected virtual IEnumerable<UnrealRoleResult> GetRolesThatFailed()` — Return all artifacts that are considered to have caused the test to fail
- L2882-2891 _protected method_ `protected virtual IEnumerable<UnrealRoleResult> GetRolesThatInterrupted()` — Return all artifacts that are considered to have caused a test Interrupt
- L2898-2936 _protected method_ `protected virtual TestResult GetUnrealTestResult()` — THe base implementation considers considers Classes can override this to implement more custom detection of success/failure than our log parsing. Not guaranteed to be called if a test is marked complete
- L2943-2946 _protected method_ `protected virtual string GetTestSummaryHeader()` — Deprecated
- L2953-3000 _protected method_ `protected virtual void LogTestSummaryHeader()` — Log header for the test summary. The header is the first block of text and will be followed by the summary of each individual role in the test
- L3006-3068 _public method_ `public override string GetTestSummary()` — Returns a summary of this test

#### enum `Gauntlet.UnrealTestNode.BehaviorFlags`  
`public enum BehaviorFlags`  
_public; L34-39_
- attrs: `[Flags]`
- L36 _public* enumerator_ `None = 0`
- L37 _public* enumerator_ `PromoteErrors = 1`
- L38 _public* enumerator_ `PromoteWarnings = 2`

#### class `Gauntlet.UnrealTestNode.UnrealRoleResult`  
`public class UnrealRoleResult`  
_public; L280-325_
- desc: Describes the post-test results for a role.
- L285 _public field_ `public UnrealProcessResult ProcessResult` — High-level description of how the process ended
- L291 _public field_ `public int ExitCode` — Exit code for the process. Unreal makes limited use of exit codes so in most cases this will be 0 / -1
- L296 _public field_ `public string Summary` — Human-readable of the process result. (E.g 'process encountered a fatal error')
- L301 _public field_ `public UnrealLog LogSummary` — A summary of information such as entries, warnings, errors, ensures, etc etc extracted from the log
- L306 _public field_ `public UnrealRoleArtifacts Artifacts` — Artifacts for this role.
- L311 _public field_ `public IEnumerable<UnrealTestEvent> Events` — Events that occurred during the test pass. Asserts/Ensures/Errors/Warnings should all be in here
- L316-324 _public ctor_ `public UnrealRoleResult(UnrealProcessResult InResult, int InExitCode, string InSummary, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, IEnumerable<UnrealTestEvent> InEvents)` — Constructor. All members are required

#### struct `Gauntlet.UnrealTestNode.DecomposedAssert`  
`protected struct DecomposedAssert`  
_protected; L2482-2487_
- L2484 _public field_ `public EventId EventType`
- L2485 _public field_ `public string Message`
- L2486 _public field_ `public object[] FormatArguments`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/BuildSource/Gauntlet.StagedBuildSource.cs` (Gauntlet.Automation)


#### class `Gauntlet.EditorBuild`  
`public class EditorBuild : IBuild`  
_public; L16-39_
- inherits: `IBuild`
- L18 _public property_ `public int PreferenceOrder { get; }`
- L20 _public property_ `public UnrealTargetPlatform Platform { get; }`
- L22 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }`
- L24 _public property_ `public BuildFlags Flags { get; }`
- L26 _public property_ `public bool SupportsAdditionalFileCopy => ...`
- L28 _public property_ `public string Flavor { get; }`
- L30 _public method_ `public bool CanSupportRole(UnrealTargetRole InRoleType)`
- L32 _public property_ `public string ExecutablePath { get; set; }`
- L34-38 _public ctor_ `public EditorBuild(string InExecutablePath, UnrealTargetConfiguration InConfig)`

#### class `Gauntlet.PackagedBuild`  
`public class PackagedBuild : IBuild`  
_public; L41-77_
- inherits: `IBuild`
- L43 _public property_ `public virtual int PreferenceOrder { get; }`
- L45 _public property_ `public UnrealTargetPlatform Platform { get; set; }`
- L47 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }`
- L49 _public property_ `public UnrealTargetRole Role { get; set; }`
- L51 _public property_ `public BuildFlags Flags { get; set; }`
- L53 _public property_ `public string Flavor { get; set; }`
- L55 _public property_ `public bool SupportsAdditionalFileCopy => ...`
- L57 _public property_ `public string BuildPath { get; set; }`
- L59-66 _public method_ `public virtual bool CanSupportRole(UnrealTargetRole InRoleType)`
- L68-76 _public ctor_ `public PackagedBuild(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfig, UnrealTargetRole InRole, string InBuildPath, BuildFlags InFlags, string InFlavor="")`

#### class `Gauntlet.StagedBuild`  
`public class StagedBuild : IBuild`  
_public; L80-352_
- inherits: `IBuild`
- L82 _public property_ `public virtual int PreferenceOrder { get; }`
- L84 _public property_ `public UnrealTargetPlatform Platform { get; set; }`
- L86 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }`
- L88 _public property_ `public UnrealTargetRole Role { get; set; }`
- L90 _public property_ `public BuildFlags Flags { get; set; }`
- L92 _public property_ `public string Flavor { get; set; }`
- L94 _public property_ `public bool SupportsAdditionalFileCopy { get; }`
- L96 _public property_ `public string BuildPath { get; set; }`
- L98 _public property_ `public string ExecutablePath { get; set; }`
- L100-107 _public method_ `public virtual bool CanSupportRole(UnrealTargetRole InRoleType)`
- L109-112 _public method_ `public virtual IStagedBuildFilter GetInstallFilter(UnrealAppConfig AppConfig)`
- L114-124 _public ctor_ `public StagedBuild(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfig, UnrealTargetRole InRole, string InBuildPath, string InExecutablePath, string InFlavor="")`
- L147 _private* field_ `static Dictionary<StagedBuild, Install> LocalInstalls = ...`
- L147 _private* field_ `static Dictionary< LocalInstalls = new Dictionary<StagedBuild, Install>()`
- L153-252 _public method_ `public static string InstallBuildParallel(UnrealAppConfig AppConfig, StagedBuild InBuild, string BuildPath, string DestPath, string Desc)` — When running parallel tests using staged builds, local desktop devices only need one copy of client/server this method is used to coordinate the copy across multiple local devices
- L254-343 _public method_ `public static IEnumerable<T> CreateFromPath<T>(UnrealTargetPlatform InPlatform, string InProjectName, string InPath, string InExecutableExtension, StagedBuildSource<T> VerificationBuildSource = null) where T : StagedBuild`
- L345-351 _public method_ `public static void CleanupInstalls()`

#### enum `Gauntlet.StagedBuild.InstallStatus`  
`enum InstallStatus`  
_private*; L126-131_
- L128 _public* enumerator_ `Error`
- L129 _public* enumerator_ `Installing`
- L130 _public* enumerator_ `Installed`

#### class `Gauntlet.StagedBuild.Install`  
`class Install`  
_private*; L133-145_
- L135 _public field_ `public InstallStatus Status`
- L136 _public field_ `public string Path`
- L137 _public field_ `public UnrealTargetConfiguration Configuration`
- L139-144 _public ctor_ `public Install(InstallStatus InStatus, string InPath, UnrealTargetConfiguration InConfiguration = UnrealTargetConfiguration.Unknown)`

#### class `Gauntlet.NativeStagedBuild`  
`public class NativeStagedBuild : StagedBuild`  
_public; L354-361_
- inherits: `StagedBuild`
- L356-360 _public ctor_ `public NativeStagedBuild(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfig, UnrealTargetRole InRole, string InBuildPath, string InExecutablePath, string InFlavor = "") : base(InPlatform, InConfig, InRole, InBuildPath, InExecutablePath, InFlavor)`

#### class `Gauntlet.StagedBuildSource`  
`public abstract class StagedBuildSource<T> : IFolderBuildSource where T : StagedBuild`  
_public; L363-445_
- inherits: `IFolderBuildSource`
- constraints: `where T : StagedBuild`
- L366 _public property_ `public abstract string BuildName { get; }`
- L368 _public property_ `public abstract UnrealTargetPlatform Platform { get; }`
- L370 _public property_ `public abstract string PlatformFolderPrefix { get; }`
- L372-375 _public method_ `virtual public bool CanSupportPlatform(UnrealTargetPlatform InPlatform)`
- L377-380 _public method_ `virtual public bool ShouldMakeBuildAvailable(string AppPath)`
- L382-385 _public property_ `virtual public string ExecutableExtension { get; }`
- L387 _protected property_ `protected virtual string[] ValidPlatformFolders => ...`
- L390-444 _public method_ `public virtual List<IBuild> GetBuildsAtPath(string InProjectName, string InPath, int MaxRecursion = 3)`

#### interface `Gauntlet.IStagedBuildFilter`  
`public interface IStagedBuildFilter`  
_public; L447-457_
- L449 _public property_ `public UnrealTargetPlatform Platform { get; }`
- L451 _public method_ `public List<FileInfo> GetFilteredFiles(UnrealAppConfig AppConfig, StagedBuild Build)`
- L453-456 _public method_ `public static IStagedBuildFilter GetFilterForPlatform(UnrealTargetPlatform Platform)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/BuildSource/Gauntlet.UnrealBuildSource.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealBuildSource`  
`public class UnrealBuildSource : IBuildSource`  
_public; L16-1047_
- inherits: `IBuildSource`
- L18 _public property_ `public DirectoryReference UnrealPath { get; set; }`
- L20 _public property_ `public string ProjectName { get; set; }`
- L22 _public property_ `public FileReference ProjectPath { get; set; }`
- L24 _public property_ `public bool UsesSharedBuildType { get; set; }`
- L26 _public property_ `public string BuildName { get; set; }`
- L28 _public property_ `public IEnumerable<string> BuildPaths { get; set; }`
- L30 _public property_ `public string Branch { get; set; }`
- L32 _public property_ `public int Changelist { get; set; }`
- L34 _public property_ `public int Preflight { get; set; }`
- L36 _public property_ `public bool EditorValid { get; set; }`
- L38 _protected field_ `protected Dictionary<UnrealTargetPlatform, List<IBuild>> DiscoveredBuilds`
- L38 _protected field_ `protected Dictionary< DiscoveredBuilds`
- L69-72 _public ctor_ `public UnrealBuildSource(string InProjectName, FileReference InProjectPath, DirectoryReference InUnrealPath, bool InUsesSharedBuildType, string BuildReference)`
- L74-77 _public ctor_ `public UnrealBuildSource(string InProjectName, FileReference InProjectPath, DirectoryReference InUnrealPath, bool InUsesSharedBuildType, string BuildReference, Func<string, string> ResolutionDelegate)`
- L79-99 _public ctor_ `public UnrealBuildSource(string InProjectName, FileReference InProjectPath, DirectoryReference InUnrealPath, bool InUsesSharedBuildType, string BuildReference, IEnumerable<string> InSearchPaths)`
- L101-104 _public method_ `public bool CanSupportPlatform(UnrealTargetPlatform Platform)`
- L107-194 _protected method_ `protected void InitBuildSource(string InProjectName, FileReference InProjectPath, DirectoryReference InUnrealPath, bool InUsesSharedBuildType, string InBuildArgument, Func<string, string> ResolutionDelegate)`
- L196-354 _protected method_ `virtual protected bool ResolveBuildReference(string InBuildReference, Func<string, string> ResolutionDelegate, out IEnumerable<string> OutBuildPaths, out string OutBuildName)`
- L360-376 _protected method_ `virtual protected void AddBuild(IBuild NewBuild)` — Adds the provided build to our list (calls ShouldMakeBuildAvailable to verify).
- L383-386 _protected method_ `virtual protected IBuild ShouldMakeBuildAvailable(IBuild InBuild)` — Allows derived classes to nix or modify builds as they are discovered
- L393-421 _protected method_ `virtual protected IBuild CreateEditorBuild(DirectoryReference InUnrealPath, UnrealTargetConfiguration InConfiguration = UnrealTargetConfiguration.Development)` — Adds an Editor build to our list of available builds if one exists
- L429-432 _private* method_ `bool HaveDiscoveredBuilds(UnrealTargetPlatform InPlatform)` — True/false on whether we've tried to discover builds for the specified platform
- L440-486 _protected method_ `virtual protected void DiscoverBuilds(UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfiguration = UnrealTargetConfiguration.Development)` — Discover all builds for the specified platform. Nop if this has already been run for the provided platform
- L494-502 _public method_ `public int GetBuildCount(UnrealTargetPlatform InPlatform, BuildFlags InFlags = BuildFlags.None)` — Returns how many builds are available for the specified platform
- L513-564 _private* method_ `IEnumerable<IBuild> GetMatchingBuilds(UnrealTargetRole InRole, UnrealTargetPlatform? InPlatform, UnrealTargetConfiguration InConfiguration, BuildFlags InFlags, string InFlavor="")` — Returns all builds that match the specified parameters. If no builds have been discovered then that is performed first
- L573-601 _public method_ `public bool CanSupportRole(UnrealSessionRole Role, ref List<string> Reasons)` — Checks if we are able to support the specified role. This will trigger build discovery if it has not yet happened for the specified platform
- L603-606 _public method_ `virtual public UnrealAppConfig CreateConfiguration(UnrealSessionRole Role)`
- L608-710 _public method_ `virtual public UnrealAppConfig CreateConfiguration(UnrealSessionRole Role, IEnumerable<UnrealSessionRole> OtherRoles)`
- L712-716 _private method_ `private bool CanRunPlatformVirtualized(UnrealTargetPlatform? Platform)`
- L723-808 _private method_ `private string GenerateProcessedCommandLine(string InCommandLine)` — Remove all duplicate flags and combine any execcmd strings that might be floating around in the commandline.
- L814-820 _private method_ `private string GetModuleOverlayExecutablePath(UnrealTargetRole role, UnrealTargetPlatform platform)` — Get the module overlay binary path for a particular configuration
- L829-1015 _public method_ `virtual public string GetRelativeExecutablePath(UnrealTargetRole TargetRole, UnrealTargetPlatform TargetPlatform, UnrealTargetConfiguration TargetConfiguration)` — Given a role, platform, and config, returns the path to the binary for that config. E.g. Binaries\Win64\FooServer-Win64-Shipping.exe
- L1017-1046 _public method_ `public string GetPlatformPath(UnrealTargetRole Type, UnrealTargetPlatform Platform)`

#### class `Gauntlet.UnrealBuildSource.ArtifactMetadata`  
`protected class ArtifactMetadata`  
_protected; L40-67_
- L43 _public property_ `public string Change { get; set; }` — attrs: `[JsonPropertyName("change")]`
- L45 _public property_ `public string Preflight { get; set; }` — attrs: `[JsonPropertyName("preflight")]`
- L47 _public property_ `public string Branch { get; set; }` — attrs: `[JsonPropertyName("branch")]`
- L49 _public property_ `public string BuildName { get; set; }` — attrs: `[JsonPropertyName("buildName")]`
- L51 _public property_ `public string Configuration { get; set; }` — attrs: `[JsonPropertyName("configuration")]`
- L53 _public property_ `public string Platform { get; set; }` — attrs: `[JsonPropertyName("platform")]`
- L55 _public property_ `public string Type { get; set; }` — attrs: `[JsonPropertyName("type")]`
- L57-66 _public method_ `public static ArtifactMetadata LoadFromJson(string FilePath)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Config/Gauntlet.EpicConfig.cs` (Gauntlet.Automation)


#### class `EpicConfig.UETelemetry`  
`public class UETelemetry : MySQLConfig<Gauntlet.TelemetryData>`  
_public; L19-184_
- inherits: `MySQLConfig<Gauntlet.TelemetryData>`
- desc: Production UE Telemetry config
- L21 _protected property_ `protected virtual string TableName { get; }`
- L22 _protected property_ `protected virtual string BuildTableName { get; }`
- L23 _private field_ `private int BuildID = -1`
- L24-44 _public method_ `public override void LoadConfig(string ConfigFilePath)`
- L48-51 _public method_ `public override string GetTableName()` — Get Target Table name based on data type
- L55-71 _public method_ `public override IEnumerable<string> GetTableColumns()` — Get Target Table columns based on data type
- L76-92 _public method_ `public override IEnumerable<string> FormatDataForTable(Gauntlet.TelemetryData Data, ITelemetryContext Context)` — Format the data for target table based on data type
- L96-99 _public method_ `public virtual string GetBuildTableName()` — Get Build Table name
- L106-128 _public method_ `public override bool PreSubmitQuery(IDatabaseDriver<Gauntlet.TelemetryData> Driver, IEnumerable<Gauntlet.TelemetryData> DataRows, ITelemetryContext Context)` — Query DB to get build id or add it and store the build id.
- L135-183 _public method_ `public override string GetFetchDataQuery(ITelemetryContext InContext)` — Return the query to fetch data

#### class `EpicConfig.UETelemetryStaging`  
`public class UETelemetryStaging : UETelemetry`  
_public; L188-192_
- inherits: `UETelemetry`
- desc: Staging UE Telemetry Config
- L190 _protected property_ `protected override string TableName { get; }`
- L191 _protected property_ `protected override string BuildTableName { get; }`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Game/EpicGame.TestConfig.cs` (Gauntlet.Automation)


#### class `EpicGame.EpicGameTestConfig`  
`public class EpicGameTestConfig : UnrealGame.UnrealTestConfig, IAutoParamNotifiable`  
_public; L24-409_
- inherits: `UnrealGame.UnrealTestConfig, IAutoParamNotifiable`
- desc: An additional set of options that pertain to internal epic games.
- L30 _public field_ `public bool NoMCP = false` — attrs: `[AutoParam]` — Should this test skip mcp?
- L36 _public field_ `public bool DeviceAuthSkip = false` — attrs: `[AutoParam]` — Tell the server not to authenticate u
- L39 _public field_ `public bool FastCook = false` — attrs: `[AutoParam]`
- L45 _public field_ `public string EpicApp = "DevLatest"` — attrs: `[AutoParam]` — Which backend to use for matchmaking
- L51 _protected field_ `protected string BuildIDOverride = ""` — attrs: `[AutoParam]` — Unique buildid to avoid matchmaking collisions
- L57 _private* field_ `int ServerPortStart = 7777` — attrs: `[AutoParam]` — Initial value for a unique server port to avoid matchmaking collisions
- L62 _protected property_ `protected int ServerPort { get; set; }` — Unique server port for the current Config object
- L68 _private* field_ `int BeaconPortStart = 15000` — attrs: `[AutoParam]` — Initial value for a unique server beacon port to avoid matchmaking collisions
- L73 _protected property_ `protected int BeaconPort { get; set; }` — Unique beacon port for the current Config object
- L79 _public field_ `public bool LogPSO = false` — attrs: `[AutoParam]` — Make sure the client gets -logpso when we are collecting them
- L85 _public field_ `public string MemPro` — attrs: `[AutoParam]` — Which Mempro tags we want to track if we need them. Note, should only be used in short runs.
- L92 _public field_ `public bool PreAssignAccount = true` — attrs: `[AutoParam]` — Should this test assign a random test account?
- L98 _public field_ `public bool RequiresLogin = false` — attrs: `[AutoParam]` — Does the current test require a user to be logged in to function correctly?
- L104 _public field_ `public bool RemoteServer = false` — attrs: `[AutoParam]` — If true, do not apply args to client and server as if they were running on the same host
- L110 _public field_ `public string McpRegion = string.Empty` — attrs: `[AutoParam]` — Optional specifier for client mcp region
- L116 _public field_ `public string McpSubRegion = string.Empty` — attrs: `[AutoParam]` — Optional specifier for client mcp subregion
- L122 _public property_ `public string EditorTraces { get; set; }` — attrs: `[AutoParam]` — Comma-separated list of Unreal Insights trace channels to collect for Editor roles, saved to a file named EditorTrace{ID#}.utrace
- L128 _public property_ `public string ClientTraces { get; set; }` — attrs: `[AutoParam]` — Comma-separated list of Unreal Insights trace channels to collect for Client roles, saved to a file named ClientTrace{ID#}.utrace
- L134 _public property_ `public string ServerTraces { get; set; }` — attrs: `[AutoParam]` — Comma-separated list of Unreal Insights trace channels to collect for Server roles, saved to a file named ServerTrace{ID#}.utrace
- L142 _public field_ `public bool WprTraces = false` — attrs: `[AutoParam]` — Enables Windows Performance Recorder on the local machine, saved to a file named WinPerfReportTrace{ID#}.etl Can produce around 1 GB/minute, avoid for long-running tests. Requires running with Admin privileges.
- L147 _public field_ `public readonly List<string> TraceLogPaths = []` — Filepaths to trace logging artifacts, copied after test execution ends
- L150 _protected field_ `protected bool SkipMcpSetup = false`
- L153 _private field_ `private readonly int CurrentConfigIndex`
- L154 _private field_ `static private int NumberOfConfigsCreated = 0`
- L155 _private field_ `static private int NumberOfEditorsConfigured = 0`
- L156 _private field_ `static private int NumberOfClientsConfigured = 0`
- L157 _private field_ `static private int NumberOfServersConfigured = 0`
- L159 _public field_ `public static readonly string AutomationToolLogsDir = Path.Combine(Unreal.EngineDirectory.FullName, "Programs", "AutomationTool", "Saved", "Logs")`
- L161-165 _public ctor_ `public EpicGameTestConfig()`
- L167-189 _public method_ `public void ParametersWereApplied(string[] Params)`
- L191-383 _public method_ `public override void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)`
- L385-403 _private method_ `private string SetupInsightsTraceFile(UnrealTargetRole RoleType, int RoleCount)`
- L408 _public method_ `public string CurrentConfigWprPath()` — Path to generate Windows Performance Recorder artifacts

#### class `EpicGame.EpicGameTestNode`  
`public abstract class EpicGameTestNode<TConfigClass> : UnrealTestNode<TConfigClass> where TConfigClass : EpicGameTestConfig, new()`  
_public; L414-560_
- inherits: `UnrealTestNode<TConfigClass>`
- constraints: `where TConfigClass : EpicGameTestConfig, new()`
- desc: Generic TestNode class for Epic Games internal projects.
- L417-420 _public ctor_ `public EpicGameTestNode(UnrealTestContext InContext) : base(InContext)`
- L422-430 _private method_ `private static bool IsWindowsAdmin()`
- L432-439 _public method_ `public override bool StartTest(int Pass, int InNumPasses)`
- L441-481 _private method_ `private void StartWprCapture()`
- L483-503 _private method_ `private void SafeCancelWprCapture()`
- L505-527 _private method_ `private void EndWprCapture(string EtlOutputPath)`
- L529-559 _public method_ `public override IEnumerable<UnrealRoleArtifacts> SaveRoleArtifacts(string OutputPath)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Game/UnrealGame.DefaultNode.cs` (Gauntlet.Automation)


#### class `UnrealGame.DefaultTest`  
`public class DefaultTest : UnrealTestNode<UnrealTestConfig>`  
_public; L16-42_
- inherits: `UnrealTestNode<UnrealTestConfig>`
- desc: Implements a default node that should boot most projects and supports n number of clients via -numclients= and a server via -server
- L18-20 _public ctor_ `public DefaultTest(UnrealTestContext InContext) : base(InContext)`
- L22-41 _public method_ `public override UnrealTestConfig GetConfiguration()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Game/UnrealGame.TestConfig.cs` (Gauntlet.Automation)


#### class `UnrealGame.UnrealTestConfig`  
`public class UnrealTestConfig : UnrealTestConfiguration`  
_public; L16-29_
- inherits: `UnrealTestConfiguration`
- desc: Default set of options for testing "DefaultGame". Options that tests can configure should be public, external command-line driven options should be protected/private
- L24-28 _public method_ `public override void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)` — Applies these options to the provided app config

### `Source/Programs/AutomationTool/Gauntlet/Unreal/InstallUnrealBuild.cs` (Gauntlet.Automation)


#### class `Gauntlet.InstallUnrealBuild`  
`public class InstallUnrealBuild : BuildCommand`  
_public; L24-59_
- attrs: `[Help("Install Unreal Build onto one or more connected devices using Gauntlet")] [ParamHelp("platform=<platform>", "Platform to use")] [ParamHelp("path=<path>", "Path to a build to install")] [ParamHelp("device=<device>", "Device to install a build on")] [ParamHelp("devices=<devices>", "List of devices, separated with commas, to install a build on")] [ParamHelp("commandline=\"-arg1 -arg2 -etc\"", `
- inherits: `BuildCommand`
- desc: Main class for Unreal Installer script
- L31-58 _public method_ `public override ExitCode Execute()` — Entrance point for Unreal Installer script

### `Source/Programs/AutomationTool/Gauntlet/Unreal/RunUnreal.cs` (Gauntlet.Automation)


#### class `Gauntlet.RunUnreal`  
`public class RunUnreal : BuildCommand`  
_public; L70-554_
- attrs: `[Help("Run Unreal tests using Gauntlet")] [ParamHelp("Tests", "List of gauntlet tests to run", Required = true, MultiSelectSeparator = ",")] [ParamHelp("ExecCmds", "List commands to execute. NOTE: To provide ExecCmds to specific roles, use -EditorExecCmds, -ClientExecCmds, etc.", MultiSelectSeparator = "+")] [ParamHelp("Build", "Reference to the build that is being tested")] [ParamHelp("Configurat`
- inherits: `BuildCommand`
- desc: Base class for executing Unreal tests. For a full list of options see UnrealTestContextOption
- L75 _public property_ `public virtual string DefaultTestName { get; }` — Test node to create if none were specified
- L80 _private const_ `private const string CleanEnvironmentVariable = "UE_GauntletCleanTempDir"` — Constant for environment variable that can be set to trigger the cleanup of Options.TempDir upon completion
- L88-106 _public method_ `public override ExitCode Execute()` — Main UAT entrance point. Custom games can derive from RunUnrealTests to run custom setup steps or directly set params on ContextOptions to remove the need for certain command line params (e.g. -project=FooGame
- L113-353 _public method_ `public virtual ExitCode RunTests(UnrealTestOptions ContextOptions)` — Execute all tests according to the provided context
- L355-402 _private* method_ `bool ExecuteTests(UnrealTestOptions Options, IEnumerable<ITestNode> TestList)`
- L411-490 _private* method_ `IEnumerable<ITestNode> CreateTestList(UnrealTestContext Context, Params DefaultParams, ArgumentWithParams PlatformParams = null)` — Create the list of tests specified by the context.
- L498-510 _protected method_ `protected virtual void SetupAccounts()` — Setup the account pool for tests that use it. Internally our derived classes (e.g. RunOrionTests) fill these with the usernames and passwords for all of our various test accounts. This is left here as an example.
- L516-519 _protected method_ `protected virtual void TeardownAccounts()` — TearDown the account pool that was SetUp for tests.
- L521-544 _protected method_ `protected void SetupDevices(UnrealTargetPlatform DefaultPlatform, UnrealTestOptions Options)`
- L546-553 _protected method_ `protected void SetupPlatformConfigurationProfiles(UnrealTargetPlatform PlatformType, UnrealTestOptions Options)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Tasks/Gauntlet.Task.CheckBuildSize.cs` (Gauntlet.Automation)


#### class `Gauntlet.CheckBuildSize`  
`public class CheckBuildSize : BuildCommand`  
_public; L18-60_
- inherits: `BuildCommand`
- L20-59 _public method_ `public override ExitCode Execute()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Tasks/Gauntlet.Task.CleanDevices.cs` (Gauntlet.Automation)


#### class `Gauntlet.CleanDevices`  
`public class CleanDevices : AutomationTool.BuildCommand`  
_public; L18-103_
- inherits: `AutomationTool.BuildCommand`
- desc: Runs through every device provided (either singularly, a comma-separated list, or a device file) and removes any Gauntlet-installed builds older than MaxDays, and ay local crashdump info (if applicable) older than MaxDays
- L22 _public field_ `public string Devices = ""` — attrs: `[AutoParamWithNames("", "device", "devices")]`
- L25 _public field_ `public string DeviceURL` — attrs: `[AutoParam("")]`
- L28 _public field_ `public string TempDir` — attrs: `[AutoParam("")]`
- L31 _public field_ `public int MaxDays` — attrs: `[AutoParam(7)]`
- L34-72 _public method_ `public override ExitCode Execute()`
- L74-102 _protected method_ `protected void CleanDevice(ITargetDevice Device)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.AutomationLogParser.cs` (Gauntlet.Automation)


#### class `Gauntlet.AutomationLogParser`  
`public class AutomationLogParser`  
_public; L16-172_
- desc: Helper class for parsing AutomationTest results from either an UnrealLogParser or log contents
- L18 _protected field_ `protected UnrealLogParser Parser`
- L20 _public property_ `public string AutomationReportPath { get; set; }`
- L22 _public property_ `public string AutomationReportURL { get; set; }`
- L27 _public property_ `public IEnumerable<UnrealLog.LogEntry> AutomationLogEntries { get; set; }` — Returns entries in the log file related to automation
- L32-38 _public property_ `public IEnumerable<UnrealLog.LogEntry> AutomationWarningsAndErrors { get; }` — Returns warning/errors in the logfile related to automation
- L44-66 _public ctor_ `public AutomationLogParser(UnrealLogParser InParser)` — Constructor that uses an existing log parser
- L72-75 _public ctor_ `public AutomationLogParser(string InContents) : this(new UnrealLogParser(InContents))` — Constructor that takes raw log contents
- L81-84 _public ctor_ `public AutomationLogParser(UnrealLog InLog) : this(InLog.GetParser())` — Constructor that takes UnrealLog instance
- L90-171 _public method_ `public IEnumerable<UnrealAutomatedTestResult> GetResults()` — Returns all results found in our construction content.

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.DeviceUsageReporter.cs` (Gauntlet.Automation)


#### class `Gauntlet.IDeviceUsageReporter`  
`public abstract class IDeviceUsageReporter`  
_public; L10-125_
- L26-32 _public method_ `public static void RecordStart(string deviceName, UnrealTargetPlatform? platform, EventType et, EventState state = EventState.Success, string comment = "")`
- L34-40 _public method_ `public static void RecordEnd(string deviceName, UnrealTargetPlatform? platform, EventType et, EventState state = EventState.Success, string comment = "")`
- L42-48 _public method_ `public static void RecordComment(string deviceName, UnrealTargetPlatform? platform, EventType et, string comment)`
- L50-85 _private method_ `private static List<IDeviceUsageReporter> GetEnabledReporters()`
- L87-102 _private method_ `private static void RecordToAll(string deviceName, UnrealTargetPlatform platform, EventType ev, bool bStarting, EventState state, string comment = "")`
- L104-119 _private method_ `private static void CommentToAll(string DeviceName, UnrealTargetPlatform platform, EventType ev, string comment)`
- L121 _public method_ `public abstract void RecordEvent(string deviceName, UnrealTargetPlatform platform, EventType ev, bool bStarting, EventState state = EventState.Success, string comment = "")`
- L122 _public method_ `public abstract void AddCommentToEvent(string deviceName, UnrealTargetPlatform platform, EventType ev, string comment)`
- L124 _public method_ `public abstract bool IsEnabled()`

#### enum `Gauntlet.IDeviceUsageReporter.EventType`  
`public enum EventType`  
_public; L12-18_
- L14 _public* enumerator_ `Device`
- L15 _public* enumerator_ `Install`
- L16 _public* enumerator_ `Test`
- L17 _public* enumerator_ `SavingArtifacts`

#### enum `Gauntlet.IDeviceUsageReporter.EventState`  
`public enum EventState : int`  
_public; L20-24_
- inherits: `int`
- L22 _public* enumerator_ `Failure = 0`
- L23 _public* enumerator_ `Success = 1`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.InstallUnreal.cs` (Gauntlet.Automation)


#### class `Gauntlet.InstallUnreal`  
`public class InstallUnreal`  
_public; L18-196_
- desc: Base class implementing Installer functionality
- L25-195 _public method_ `public static bool RunInstall( string PlatformParam, string BuildPath, string ProjectName, string CommandLine, string DevicesArg, int ParallelTasks )` — A method which is responsible for the core Installer functionality. Iterates through devices and installs the project to each device.

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.ParamDescription.cs` (Gauntlet.Automation)


#### class `Gauntlet.GauntletParamDescription`  
`public class GauntletParamDescription`  
_public; L11-77_
- L17 _public field_ `public string ParamName` — The param name that is passed in on the commandline In -PARAMNAME or -PARAMNAME=val format
- L22 _public field_ `public bool Required` — Is this required for the test to run?
- L30 _public field_ `public string InputFormat` — Very brief desc of what to pass in - Will show up in -param= format. Ex - a value of "Map To Use" would show up as -param= Leave blank for a param that is just a flag.
- L35 _public field_ `public string ParamDesc` — Helpful description for what this Parameter or flag represents and what can be passed in.
- L40 _public field_ `public string SampleInput` — If you would like to provide a sample input for this field, do so here. Will show up as (ex: SampleInput) at the end of the param description
- L45 _public field_ `public string DefaultValue` — If this param has a default value, put it here. Will show ups as (default: DefaultValue)
- L50 _public field_ `public bool TestSpecificParam` — Whether this is a Test-specific param or a generic gauntlet param.
- L52-55 _public ctor_ `public GauntletParamDescription()`
- L57-76 _public method_ `public override string ToString()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.UnrealHelpers.cs` (Gauntlet.Automation)


#### enum `Gauntlet.UnrealTargetRole`  
`public enum UnrealTargetRole`  
_public; L22-32_
- desc: Defines roles that can be performed for Unreal TODO - Editor variants should be a tag, not an enum?
- L24 _public* enumerator_ `Unknown`
- L25 _public* enumerator_ `Editor`
- L26 _public* enumerator_ `EditorGame`
- L27 _public* enumerator_ `EditorServer`
- L28 _public* enumerator_ `Client`
- L29 _public* enumerator_ `Server`
- L30 _public* enumerator_ `Host`
- L31 _public* enumerator_ `CookedEditor`

#### class `Gauntlet.UnrealFileToCopy`  
`public class UnrealFileToCopy`  
_public; L37-58_
- desc: Base class of a file to copy as part of a test.
- L42 _public field_ `public string SourceFileLocation` — Base file to copy, including filename and extension.
- L46 _public field_ `public EIntendedBaseCopyDirectory TargetBaseDirectory` — The high-level base directory we want to copy to.
- L51 _public field_ `public string TargetRelativeLocation` — Where to copy the file to, including filename and extension, relative to the intended base directory. Should be any additional subdirectories, plus file name.
- L52-57 _public ctor_ `public UnrealFileToCopy(string SourceLoc, EIntendedBaseCopyDirectory TargetDirType, string TargetLoc)`

#### class `Gauntlet.UnrealRoleTypeExtensions`  
`public static class UnrealRoleTypeExtensions`  
_public; L63-102_
- desc: Helper extensions for our enums
- L65-72 _public method_ `public static bool UsesEditor(this UnrealTargetRole Type)`
- L74-77 _public method_ `public static bool IsServer(this UnrealTargetRole Type)`
- L79-82 _public method_ `public static bool IsClient(this UnrealTargetRole Type)`
- L84-87 _public method_ `public static bool IsHost(this UnrealTargetRole Type)`
- L89-92 _public method_ `public static bool IsEditor(this UnrealTargetRole Type)`
- L93-96 _public method_ `public static bool IsCookedEditor(this UnrealTargetRole Type)`
- L98-101 _public method_ `public static bool RunsLocally(this UnrealTargetRole Type)`

#### class `Gauntlet.UnrealHelpers`  
`public static class UnrealHelpers`  
_public; L107-452_
- desc: Utility functions for Unreal tests
- L109-118 _public method_ `public static UnrealTargetPlatform GetPlatformFromString(string PlatformName)`
- L127-172 _public method_ `public static string GetPlatformName(UnrealTargetPlatform TargetPlatform, UnrealTargetRole ProcessType, bool UsesSharedBuildType)` — Given a platform and a client/server flag, returns the name Unreal refers to it as. E.g. "WindowsClient", "LinuxServer".
- L180-199 _public method_ `public static System.Net.IPAddress[] GetAllLocalIPv4(NetworkInterfaceType Type)` — Fallback to use when GetHostEntry throws an exception.
- L206-255 _public method_ `public static string GetHostIpAddress(string PreferredDomain="epicgames.net")` — Gets the filehost IP to provide to devkits by examining our local adapters and returning the one that's active and on the local LAN (based on DNS assignment)
- L257-298 _public method_ `static public string GetExecutableName(string ProjectName, UnrealTargetPlatform Platform, UnrealTargetConfiguration Config, UnrealTargetRole Role, string Flavor, string Extension)`
- L300-303 _public method_ `static public string GetExecutableName(string ProjectName, UnrealTargetPlatform Platform, UnrealTargetConfiguration Config, UnrealTargetRole Role, string Extension)`
- L334 _public field_ `public static Dictionary<string, ModuleConfig> CustomModules = ...`
- L334 _public field_ `public static Dictionary< CustomModules = new()`
- L345-348 _public method_ `public static void AddCustomModuleName(string InModuleName, UnrealTargetRole InRole, string InFlavor = "")` — Adds an additional module name to search for when determining if an application path has a guantlet usable role. Traditionally all application paths must be in the form ProjectName(Game|Server).exe This method allows for applications with nontraditional names to have the role of Game, Server, Editor etc.
- L350-353 _public method_ `public static void AddCustomModuleName(ModuleConfig Config)`
- L355-437 _public method_ `static public ConfigInfo GetUnrealConfigFromFileName(string InProjectName, string InName)`
- L439-442 _public method_ `static public UnrealTargetConfiguration GetConfigurationFromExecutableName(string InProjectName, string InName)`
- L444-447 _public method_ `static public UnrealTargetRole GetRoleFromExecutableName(string InProjectName, string InName)`
- L448-451 _public method_ `static public string GetBuildFlavorFromExecutableName(string InProjectName, string InName)`

#### class `Gauntlet.UnrealHelpers.ConfigInfo`  
`public class ConfigInfo`  
_public; L305-318_
- L307 _public field_ `public UnrealTargetRole RoleType`
- L308 _public field_ `public UnrealTargetPlatform? Platform`
- L309 _public field_ `public UnrealTargetConfiguration Configuration`
- L310 _public field_ `public bool SharedBuild`
- L311 _public field_ `public string Flavor`
- L313-317 _public ctor_ `public ConfigInfo()`

#### class `Gauntlet.UnrealHelpers.ModuleConfig`  
`public class ModuleConfig`  
_public; L320-332_
- L322 _public field_ `public string ModuleName`
- L323 _public field_ `public UnrealTargetRole Role`
- L324 _public field_ `public string Flavor`
- L326-331 _public ctor_ `public ModuleConfig(string InModuleName, UnrealTargetRole InRole, string InFlavor = "")`

#### class `Gauntlet.EpicRoot`  
`public class EpicRoot`  
_public; L457-508_
- desc: Automatically maps root drive to proper platform specific path
- L459 _private* field_ `string PlatformPath`
- L461-497 _public ctor_ `public EpicRoot(string InPath)`
- L499-502 _public operator_ `public static implicit operator string(EpicRoot Path)`
- L503-506 _public operator_ `public static implicit operator EpicRoot(string Path)`

#### class `Gauntlet.UnrealTargetPlatformConvertor`  
`public class UnrealTargetPlatformConvertor : JsonConverter<UnrealTargetPlatform>`  
_public; L513-540_
- inherits: `JsonConverter<UnrealTargetPlatform>`
- desc: Converts between json and UnrealTargetPlatform
- L515-518 _public method_ `public override bool CanConvert(Type ObjectType)`
- L520-533 _public method_ `public override UnrealTargetPlatform Read(ref Utf8JsonReader Reader, Type TypeToConvert, JsonSerializerOptions Options)`
- L535-539 _public method_ `public override void Write(Utf8JsonWriter Writer, UnrealTargetPlatform StructValue, JsonSerializerOptions Options)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.UnrealLogParser.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealLog`  
`public class UnrealLog : IDisposable`  
_public; L21-356_
- inherits: `IDisposable`
- desc: Represents a prepared summary of the most relevant info in a log. Generated once by a LogParser and cached.
- L40 _public field_ `public static string[] EditorBusyChannels = new string[] { "Automation", "FunctionalTest", "Material", "DerivedDataCache", "ShaderCompilers", "Texture", "SkeletalMesh", "StaticMesh", "Python", "AssetRegistry" }` — Set of log channels that are used to monitor Editor processing
- L194 _private field_ `private UnrealLogParser _parser`
- L196-208 _public ctor_ `public UnrealLog(UnrealLogParser InParser)`
- L211 _private field_ `private bool _disposed = false`
- L212-215 _private* dtor_ `~UnrealLog()`
- L217-220 _public method_ `public void Dispose()`
- L222-232 _private method_ `private void Dispose(bool bDisposing = true)`
- L235-257 _private method_ `private bool GetRequestedExitReason()`
- L259-263 _private method_ `private bool HasEngineInitialized()`
- L269 _public method_ `public UnrealLogParser GetParser()` — Return the log parser attached to it
- L274 _public property_ `public BuildInfo LoggedBuildInfo => ...` — Build info from the log
- L275 _private field_ `private Lazy<BuildInfo> _loggedBuildInfo`
- L280 _public property_ `public PlatformInfo LoggedPlatformInfo => ...` — Platform info from the log
- L281 _private field_ `private Lazy<PlatformInfo> _loggedPlatformInfo`
- L286 _public property_ `public IEnumerable<LogEntry> LogEntries { get; set; }` — Entries in the log
- L287 _private field_ `private Lazy<IEnumerable<LogEntry>> _logEntries`
- L292 _public property_ `public IEnumerable<LogEntry> Warnings { get; }` — Warnings for this role
- L297 _public property_ `public IEnumerable<LogEntry> Errors { get; }` — Errors for this role
- L302 _public property_ `public CallstackMessage FatalError { get; set; }` — Fatal error instance if one occurred
- L303 _private field_ `private Lazy<CallstackMessage> _fatalError`
- L308 _public property_ `public IEnumerable<CallstackMessage> Ensures { get; set; }` — A list of ensures if any occurred
- L309 _private field_ `private Lazy<IEnumerable<CallstackMessage>> _ensures`
- L314 _public property_ `public int LineCount => ...` — Number of lines in the log
- L315 _private field_ `private Lazy<int> _lineCount`
- L320 _public property_ `public bool EngineInitialized { get; set; }` — True if the engine reached initialization
- L321 _private field_ `private Lazy<bool> _engineInitialized`
- L326 _public field_ `public string EngineInitializedPattern = @"LogInit.+Engine is initialized\."` — Regex pattern used to detect if the engine was initialized
- L331 _public property_ `public bool RequestedExit { get; set; }` — True if the instance requested exit
- L332 _private field_ `private bool _requestedExit`
- L333 _public property_ `public string RequestedExitReason { get; set; }`
- L334 _private field_ `private string _requestedExitReason`
- L335 _private field_ `private Lazy<bool> _hasParseRequestedExitReason`
- L336 _public property_ `public bool HasTestExitCode { get; set; }`
- L337 _private field_ `private Lazy<bool> _hasTestExitCode`
- L338 _public property_ `public int TestExitCode { get; set; }`
- L339 _protected field_ `protected int _testExitCode`
- L342 _public property_ `public string FullLogContent => ...`
- L347-355 _public property_ `public bool HasAbnormalExit { get; }` — Returns true if this log indicates the Unreal instance exited abnormally

#### enum `Gauntlet.UnrealLog.LogLevel`  
`public enum LogLevel`  
_public; L26-35_
- desc: Represents the level
- L28 _public* enumerator_ `Log`
- L29 _public* enumerator_ `Display`
- L30 _public* enumerator_ `Verbose`
- L31 _public* enumerator_ `VeryVerbose`
- L32 _public* enumerator_ `Warning`
- L33 _public* enumerator_ `Error`
- L34 _public* enumerator_ `Fatal`

#### class `Gauntlet.UnrealLog.LogEntry`  
`public class LogEntry`  
_public; L45-145_
- desc: Represents an entry in an Unreal logfile with and contails the associated category, level, and message
- L47 _public property_ `public string Prefix { get; set; }`
- L52 _public property_ `public string Category { get; set; }` — Category of the entry. E.g for "LogNet" this will be "Net"
- L57 _public property_ `public string LongChannelName => ...` — Full channel name
- L62 _public property_ `public LogLevel Level { get; set; }` — Represents the level of the entry
- L67 _public property_ `public string Message { get; set; }` — The message string from the entry
- L72 _public property_ `public DateTime? Timestamp { get; set; }` — Optional datetime of the entry
- L78-90 _public method_ `public override string ToString()` — Format the entry as it would have appeared in the log (without the timestamp).
- L96-106 _public method_ `public string ToStringWithUtcTimestamp()` — Format the entry as it would have appeared in the log (with the UTC timestamp).
- L116-127 _public ctor_ `public LogEntry(string InPrefix, string InCategory, LogLevel InLevel, string InMessage, string InTimestamp)` — Constructor that requires all info
- L137-144 _public ctor_ `public LogEntry(string InPrefix, string InCategory, LogLevel InLevel, string InMessage, DateTime? InTimestamp)` — Constructor that requires all info

#### class `Gauntlet.UnrealLog.CallstackMessage`  
`public class CallstackMessage`  
_public; L150-171_
- desc: Compound object that represents a fatal entry
- L152 _public field_ `public int Position`
- L153 _public field_ `public string Message`
- L154 _public field_ `public string[] Callstack`
- L155 _public field_ `public bool IsEnsure`
- L156 _public field_ `public bool IsSanReport`
- L162-170 _public method_ `public string FormatForLog()` — Generate a string that represents a CallstackMessage formatted to be inserted into a log file.

#### class `Gauntlet.UnrealLog.PlatformInfo`  
`public class PlatformInfo`  
_public; L176-182_
- desc: Information about the current platform that will exist and be extracted from the log
- L178 _public field_ `public string OSName`
- L179 _public field_ `public string OSVersion`
- L180 _public field_ `public string CPUName`
- L181 _public field_ `public string GPUName`

#### class `Gauntlet.UnrealLog.BuildInfo`  
`public class BuildInfo`  
_public; L187-192_
- desc: Information about the current build info
- L189 _public field_ `public string BuildVersion`
- L190 _public field_ `public string BranchName`
- L191 _public field_ `public int Changelist`

#### class `Gauntlet.UnrealLogStreamParser`  
`public class UnrealLogStreamParser`  
_public; L362-632_
- desc: Parse Unreal log from string chunk and aggregate lines as LogEvents Support structure logging output and legacy logging style
- L364 _protected property_ `protected List<UnrealLog.LogEntry> LogEvents { get; set; }`
- L366 _private property_ `private HashSet<string> UnidentifiedLogLevels { get; set; }`
- L368 _private property_ `private ILogStreamReader LogReader { get; set; }`
- L370-375 _public ctor_ `public UnrealLogStreamParser()`
- L377-381 _public ctor_ `public UnrealLogStreamParser(ILogStreamReader InLogReader) : this()`
- L387-390 _public method_ `public void SetLogReader(ILogStreamReader InLogReader)` — Set the internal log stream reader
- L396-399 _public method_ `public bool IsAttachedToLogReader()` — Return true if the internal log reader was set.
- L404-407 _public method_ `public void Clear()` — Clear aggregated log events
- L415-422 _public method_ `public int ReadStream(int LineOffset = -1, bool bClearAggregatedLines = true)` — Parse a string as log and aggregate identified unreal log lines using internal Log reader
- L431-434 _public method_ `public int ReadStream(string InContent, int LineOffset = 0, bool bClearAggregatedLines = true)` — Parse a string as log and aggregate identified unreal log lines
- L443-502 _public method_ `public int ReadStream(ILogStreamReader LogReader, int LineOffset = 0, bool bClearAggregatedLines = true)` — Parse a string as log and aggregate identified unreal log lines
- L508-511 _public method_ `public IEnumerable<UnrealLog.LogEntry> GetEvents()` — Return All the LogEvent instances
- L520-540 _private method_ `private IEnumerable<UnrealLog.LogEntry> InternalGetEventsFromChannels(IEnumerable<string> InValues, bool ExactMatch = false, bool UseLongName = true)` — Return the LogEvent instances which channel name match
- L548-551 _public method_ `public IEnumerable<UnrealLog.LogEntry> GetEventsFromChannels(IEnumerable<string> Channels, bool ExactMatch = true)` — Return the LogEvent instances that match the channel names
- L557-560 _public method_ `public IEnumerable<UnrealLog.LogEntry> GetEventsFromEditorBusyChannels()` — Return the LogEvent instances that match the Editor busy channels
- L568-571 _public method_ `public IEnumerable<string> GetLogFromChannels(IEnumerable<string> Channels, bool ExactMatch = true)` — Return the log lines that match the channel names
- L578-581 _public method_ `public IEnumerable<string> GetLogFromShortNameChannels(IEnumerable<string> Channels)` — Return the log lines that match the channel names ignoring the "log" prefix
- L587-590 _public method_ `public IEnumerable<string> GetLogFromEditorBusyChannels()` — Return the log lines that match the Editor busy channels
- L598-601 _public method_ `public IEnumerable<string> GetLogFromChannel(string Channel, bool ExactMatch = true)` — Return the log lines that match the channel name
- L607-610 _public method_ `public IEnumerable<string> GetLogLines()` — Return all the aggregated log lines
- L617-620 _public method_ `public IEnumerable<string> GetLogLinesContaining(string Text)` — Return the log lines that contain a string
- L627-631 _public method_ `public IEnumerable<string> GetLogLinesMatchingPattern(string Pattern)` — Return the log lines that match the regex pattern

#### class `Gauntlet.UnrealLogParser`  
`public class UnrealLogParser : IDisposable`  
_public; L637-1507_
- inherits: `IDisposable`
- desc: Helper class for parsing logs
- L642 _public property_ `public string Content => ...` — DEPRECATED - Use GetLogReader() to read through the log stream efficiently.
- L647 _public method_ `public ILogStreamReader GetLogReader()` — Allow reading log line by line with an internal cursor
- L648 _private property_ `private ILogStreamReader _logReader { get; set; }`
- L653 _public property_ `public IEnumerable<UnrealLog.LogEntry> LogEntries => ...` — All entries in the log
- L654 _private field_ `private Lazy<IEnumerable<UnrealLog.LogEntry>> _logEntries`
- L659 _private field_ `private Lazy<UnrealLog> _summary` — Summary of the log
- L662 _protected field_ `protected static HashSet<string> UnidentifiedLogLevels = new HashSet<string>()`
- L668-673 _public ctor_ `public UnrealLogParser(ILogStreamReader InLogReader)` — Constructor that takes a ILogStreamReader instance
- L680-681 _public ctor_ `public UnrealLogParser(string InContent) : this(new DynamicStringReader(() => InContent))` — Constructor that takes the content to parse
- L684 _private field_ `private bool _disposed = false`
- L685-688 _private* dtor_ `~UnrealLogParser()`
- L690-693 _public method_ `public void Dispose()`
- L695-709 _public method_ `public void Dispose(bool bDisposing = true)`
- L712-753 _protected method_ `protected List<UnrealLog.LogEntry> ParseEntries()`
- L755-801 _public method_ `public static string SanitizeLogText(string InContent)`
- L803-824 _public method_ `public static string SanitizeJsonOutputLine(string Line, bool ThrowOnFailure = false)`
- L826 _public method_ `public UnrealLog GetSummary()`
- L827 _protected method_ `protected UnrealLog CreateSummary()`
- L837-848 _protected method_ `protected IEnumerable<Match> GetAllMatches(ILogStreamReader InLogReader, string InPattern, RegexOptions InOptions = RegexOptions.None)` — Returns all lines from the specified content match the specified regex
- L857-860 _protected method_ `protected IEnumerable<string> GetAllMatchingLines(ILogStreamReader InLogReader, string InPattern, RegexOptions InOptions = RegexOptions.None)` — Returns all lines from the specified content match the specified regex
- L869-872 _protected method_ `protected string[] GetAllMatchingLines(string InContent, string InPattern, RegexOptions InOptions = RegexOptions.None)` — Returns all lines from the specified content match the specified regex
- L880-883 _public method_ `public string[] GetAllMatchingLines(string InPattern, RegexOptions InOptions = RegexOptions.None)` — Returns all lines that match the specified regex
- L891-894 _public method_ `public IEnumerable<Match> GetAllMatches(string InPattern, RegexOptions InOptions = RegexOptions.None)` — Returns all Matches that match the specified regex
- L902-910 _public method_ `public IEnumerable<string> GetAllContainingLines(string Substring, StringComparison Options = StringComparison.Ordinal)` — Returns all lines containing the specified substring
- L918-925 _public method_ `public void MatchAndApplyGroups(string InPattern, Action<string[]> InFunc, RegexOptions InOptions = RegexOptions.None)` — Match regex pattern and execute callback with group values passed as argument
- L931-945 _public method_ `public UnrealLog.PlatformInfo GetPlatformInfo()` — Returns a structure containing platform information extracted from the log
- L951-976 _public method_ `public UnrealLog.BuildInfo GetBuildInfo()` — Returns a structure containing build information extracted from the log
- L983-987 _public method_ `public IEnumerable<UnrealLog.LogEntry> GetEntriesOfLevel(UnrealLog.LogLevel InLevel)` — Returns all entries from the log that have the specified level
- L995-1022 _public method_ `public IEnumerable<UnrealLog.LogEntry> GetEntriesOfCategories(IEnumerable<string> InCategories, bool ExactMatch = false)` — Returns all warnings from the log
- L1031-1034 _public method_ `public IEnumerable<string> GetLogChannels(IEnumerable<string> Channels, bool ExactMatch = true)` — Return all entries for the specified channel. E.g. "OrionGame" will return all entries starting with LogOrionGame
- L1040-1043 _public method_ `public IEnumerable<string> GetEditorBusyChannels()` — Returns channels that signify the editor doing stuff
- L1052-1055 _public method_ `public IEnumerable<string> GetLogChannel(string Channel, bool ExactMatch = true)` — Return all entries for the specified channel. E.g. "OrionGame" will return all entries starting with LogOrionGame
- L1063-1073 _public method_ `public IEnumerable<string> GetWarnings(string InChannel = null)` — Returns all warnings from the log
- L1080-1090 _public method_ `public IEnumerable<string> GetErrors(string InChannel = null)` — Returns all errors from the log
- L1096-1106 _public method_ `public IEnumerable<UnrealLog.CallstackMessage> GetEnsures()` — Returns all ensures from the log
- L1112-1126 _public method_ `public UnrealLog.CallstackMessage GetFatalError()` — If the log contains a fatal error return that information
- L1132-1199 _public method_ `public IEnumerable<UnrealLog.CallstackMessage> GetASanErrors()` — Parse the log for Address Sanitizer error.
- L1205 _public method_ `public bool HasTestCompleteMarker()` — Returns true if the log contains a test complete marker
- L1211-1214 _public method_ `public bool HasRequestExit()` — Returns true if the log contains a request to exit that was not due to an error
- L1223-1250 _public method_ `public string[] GetGroupsOfLinesBetween(string StartPattern, string EndPattern, RegexOptions PatternOptions = RegexOptions.IgnoreCase)` — Returns a block of lines that start and end with the specified regex patterns
- L1259-1286 _public method_ `public string[] GetGroupsOfLinesStartingWith(string Pattern, int LineCount, RegexOptions PatternOptions = RegexOptions.IgnoreCase)` — Returns a block of lines that start with the specified regex
- L1294-1474 _protected method_ `protected IEnumerable<UnrealLog.CallstackMessage> ParseTracedErrors(string[] Patterns, int Limit = 0)` — Finds all callstack-based errors with the specified pattern
- L1481-1506 _public method_ `public bool GetTestExitCode(out int ExitCode)` — Attempts to find an exit code for a test

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.UnrealSnapshotParser.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealHealthSnapshot`  
`public class UnrealHealthSnapshot`  
_public; L12-230_
- L14 _public field_ `public string Name`
- L15 _public field_ `public float ProfileLength`
- L17 _public field_ `public float? CpuUsedMemory`
- L18 _public field_ `public float? CpuPeakMemory`
- L19 _public field_ `public float? PhysicalUsedMemory`
- L20 _public field_ `public float? PhysicalPeakMemory`
- L21 _public field_ `public float? StreamingUsedMemory`
- L22 _public field_ `public float? StreamingPeakMemory`
- L23 _public field_ `public float? MVP`
- L24 _public field_ `public float? AvgFps`
- L25 _public field_ `public float? Hitches`
- L26 _public field_ `public float? AvgHitches`
- L27 _public field_ `public float? DynamicRes`
- L28 _public field_ `public float? GTTime`
- L29 _public field_ `public float? RTTime`
- L30 _public field_ `public float? GPUTime`
- L31 _public field_ `public float? FTTime`
- L32 _public field_ `public float? RHIT`
- L33 _public field_ `public int? DrawCalls`
- L34 _public field_ `public int? DrawnPrims`
- L35 _public field_ `public int? UnbuiltHLODs`
- L37-41 _public ctor_ `public UnrealHealthSnapshot()`
- L43-135 _public method_ `public override string ToString()`
- L137-219 _public method_ `public virtual void CreateFromString(string InContent)`
- L221-224 _private method_ `private static float ParseSingleInvariant(string Text)`
- L226-229 _private method_ `private static int ParseIntInvariant(string Text)`

#### class `Gauntlet.UnrealSnapshotSummary`  
`public class UnrealSnapshotSummary<TSnapshotClass> where TSnapshotClass : UnrealHealthSnapshot, new()`  
_public; L232-477_
- constraints: `where TSnapshotClass : UnrealHealthSnapshot, new()`
- L235 _public field_ `public int SampleCount`
- L236 _public field_ `public float SessionTime`
- L237 _public field_ `public float PeakMemory`
- L239 _public field_ `public List<float> MVP`
- L240 _public field_ `public List<float> AvgFps`
- L241 _public field_ `public List<float> Hitches`
- L242 _public field_ `public List<float> AvgHitches`
- L243 _public field_ `public List<float> DynamicRes`
- L244 _public field_ `public List<float> GTTime`
- L245 _public field_ `public List<float> RTTime`
- L246 _public field_ `public List<float> GPUTime`
- L247 _public field_ `public List<float> FTTime`
- L248 _public field_ `public List<float> RHIT`
- L249 _public field_ `public List<int> DrawCalls`
- L250 _public field_ `public List<int> DrawnPrims`
- L251 _public field_ `public List<int> UnbuiltHLODs`
- L253 _public field_ `public IEnumerable<TSnapshotClass> Snapshots`
- L255-275 _public ctor_ `public UnrealSnapshotSummary(ILogStreamReader LogReader, string SnapshotTitles="")`
- L277-279 _public ctor_ `public UnrealSnapshotSummary(string InContent, string SnapshotTitles = "") : this(new DynamicStringReader(() => InContent), SnapshotTitles)`
- L281-400 _protected method_ `protected virtual void CreateFromLog(ILogStreamReader LogReader, string InTitle)`
- L402-476 _public method_ `public override string ToString()`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.UnrealTelemetry.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealAutomationTelemetry`  
`static class UnrealAutomationTelemetry`  
_internal*; L19-148_
- desc: Utility functions for Unreal Automation Telemetry
- L27-39 _public method_ `static public void LoadOutputsIntoReport(string TelemetryDirectory, ITelemetryReport TelemetryReport, Dictionary<string, string> Mapping = null)` — Gather csv telemetry outputs generated by UE automated tests and add them to a test report
- L47-115 _public method_ `static public void LoadCSVOutputIntoReport(string File, ITelemetryReport TelemetryReport, Dictionary<string, string> Mapping = null)` — Gather telemetry data from csv file generated by UE automated tests and add them to a test report
- L127-146 _public method_ `static public void WriteDataTableToCSV(DataTable Data, string OutputFile)`

#### enum `Gauntlet.UnrealAutomationTelemetry.CSVColumns`  
`public enum CSVColumns`  
_public; L117-125_
- L119 _public* enumerator_ `TestName`
- L120 _public* enumerator_ `DataPoint`
- L121 _public* enumerator_ `Measurement`
- L122 _public* enumerator_ `Context`
- L123 _public* enumerator_ `Unit`
- L124 _public* enumerator_ `Baseline`

#### class `Gauntlet.UnrealTelemetryContext`  
`public class UnrealTelemetryContext : ITelemetryContext`  
_public; L150-168_
- inherits: `ITelemetryContext`
- L152-157 _public method_ `public object GetProperty(string Name)`
- L158 _private* field_ `Dictionary<string, object> Properties`
- L158 _private* field_ `Dictionary< Properties`
- L160-163 _public ctor_ `public UnrealTelemetryContext()`
- L164-167 _public method_ `public void SetProperty(string Name, object Value)`

#### class `Gauntlet.PublishUnrealAutomationTelemetry`  
`class PublishUnrealAutomationTelemetry : BuildCommand`  
_internal*; L173-342_
- inherits: `BuildCommand`
- desc: Build command to read Unreal Automation telemetry data saved in csv format and then publish it to a database.
- L188-318 _public method_ `public override ExitCode Execute()` — attrs: `[Help("CSVFile", "Path to the csv file to parse.")] [Help("CSVDirectory", "Path to a folder containing csv files to parse.")] [Help("CSVMapping", "Optional CSV column mapping. Format is: <target key>:<source key>,...")] [Help("TelemetryConf`
- L325-340 _private method_ `private DateTime GetChangelistDateTime(int Changelist)` — Get the DateTime of the given changelist

#### class `Gauntlet.FetchUnrealAutomationTelemetry`  
`class FetchUnrealAutomationTelemetry : BuildCommand`  
_internal*; L347-481_
- inherits: `BuildCommand`
- desc: Build command to fetch Unreal Automation telemetry data from a database and save it to csv.
- L362-446 _public method_ `public override ExitCode Execute()` — attrs: `[Help("CSVFile", "Path of the csv file to save.")] [Help("TelemetryConfig", "Telemetry configuration to use to publish to Database. Default: UETelemetryStaging.")] [Help("DatabaseConfigPath", "Path to alternate Database config. Default is T`
- L448-479 _private method_ `private DateTime SinceStringToDate(string SinceString)`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.UnrealTestAudit.cs` (Gauntlet.Automation)


#### class `Gauntlet.Report.TestProfile`  
`public partial class TestProfile`  
_public; L18-24_
- desc: Test profile (unit, functional, performance, etc)
- L20 _public field_ `public static readonly TestProfile Unit = new TestProfile("Unit")`
- L21 _public field_ `public static readonly TestProfile Functional = new TestProfile("Functional")`
- L22 _public field_ `public static readonly TestProfile Performance = new TestProfile("Performance")`
- L23 _public field_ `public static readonly TestProfile Smoke = new TestProfile("Smoke")`

#### class `Gauntlet.Report.TestHarness`  
`public partial class TestHarness`  
_public; L29-35_
- desc: Test harness
- L31 _public field_ `public static readonly TestHarness UEFunctionalTest = new TestHarness("UE Functional Test")`
- L32 _public field_ `public static readonly TestHarness Gauntlet = new TestHarness("Gauntlet")`
- L33 _public field_ `public static readonly TestHarness GauntletRPC = new TestHarness("Gauntlet RPC")`
- L34 _public field_ `public static readonly TestHarness LLT = new TestHarness("Low Level Test")`

#### class `Gauntlet.Report.TestTeam`  
`public partial class TestTeam`  
_public; L40-43_
- desc: Test team
- L42 _public field_ `public static readonly TestTeam UE = new TestTeam("UE")`

#### class `Gauntlet.Report.TestTag`  
`public partial class TestTag`  
_public; L48-50_
- desc: Test tag

#### class `Gauntlet.UnrealTestMetadata`  
`public class UnrealTestMetadata : ITestAuditMetadata`  
_public; L57-140_
- inherits: `ITestAuditMetadata`
- desc: Unreal Test metadata component for Audit
- L59-73 _public ctor_ `public UnrealTestMetadata(string Key, string Name, string NodeClass, Version Version, float Timeout, string? CommandLine = null, TestHarness? Harness = null, TestProfile? Profile = null, TestTeam? Team = null, string? Intent = null, TestTag[]? Tags = null, Dictionary<string, object>? Params = null)`
- L74-88 _public ctor_ `public UnrealTestMetadata(Func<string> Key, Func<string> Name, Func<string> NodeClass, Func<Version> Version, Func<float> Timeout, Func<string?>? CommandLine = null, Func<TestHarness?>? Harness = null, Func<TestProfile?>? Profile = null, Func<TestTeam?>? Team = null, Func<string?>? Intent = null, Func<TestTag[]?>? Tags = null, Func<Dictionary<string, object>>? Params = null)`
- L90 _private* field_ `Func<string> _key`
- L91 _private* field_ `Func<string> _name`
- L92 _private* field_ `Func<string> _class`
- L93 _private* field_ `Func<Version> _version`
- L94 _private* field_ `Func<float> _timeout`
- L95 _private* field_ `Func<string?>? _commandline`
- L96 _private* field_ `Func<TestHarness?>? _harness`
- L97 _private* field_ `Func<TestProfile?>? _profile`
- L98 _private* field_ `Func<TestTeam?>? _team`
- L99 _private* field_ `Func<string?>? _intent`
- L100 _private* field_ `Func<TestTag[]?>? _tags`
- L101 _private* field_ `Func<Dictionary<string, object>?>? _params`
- L101 _private* field_ `Func<Dictionary< _params`
- L103 _private* field_ `static Regex AbsoluteFilePathPattern = new Regex(@"^(?:[/\\]+|[a-z]:[/\\]|https?://)", RegexOptions.Compiled | RegexOptions.IgnoreCase)`
- L106 _public property_ `public string TestKey => ...`
- L109 _public property_ `public string TestName => ...`
- L112 _public property_ `public string TestNodeClass => ...`
- L115 _public property_ `public Version TestVersion => ...`
- L118 _public property_ `public float TestTimeoutMinutes => ...`
- L121 _public property_ `public string? TestCommandLine => ...`
- L124 _public property_ `public TestHarness? TestHarness => ...`
- L127 _public property_ `public TestProfile? TestProfile => ...`
- L130 _public property_ `public TestTeam? TestTeam => ...`
- L133 _public property_ `public string? TestIntent => ...`
- L136 _public property_ `public TestTag[]? TestTags => ...`
- L139 _public property_ `public Dictionary<string, object>? TestParams => ...`

### `Source/Programs/AutomationTool/Gauntlet/Unreal/Utils/Gauntlet.UnrealTestResults.cs` (Gauntlet.Automation)


#### class `Gauntlet.UnrealAutomationDevice`  
`public class UnrealAutomationDevice`  
_public; L19-45_
- L22 _public property_ `public string DeviceName { get; set; }` — attrs: `[JsonPropertyName("deviceName")]`
- L24 _public property_ `public string Instance { get; set; }` — attrs: `[JsonPropertyName("instance")]`
- L26 _public property_ `public string InstanceName { get; set; }` — attrs: `[JsonPropertyName("instanceName")]`
- L28 _public property_ `public string Platform { get; set; }` — attrs: `[JsonPropertyName("platform")]`
- L30 _public property_ `public string OSVersion { get; set; }` — attrs: `[JsonPropertyName("oSversion")]`
- L32 _public property_ `public string Model { get; set; }` — attrs: `[JsonPropertyName("model")]`
- L34 _public property_ `public string GPU { get; set; }` — attrs: `[JsonPropertyName("gPU")]`
- L36 _public property_ `public string CPUModel { get; set; }` — attrs: `[JsonPropertyName("cPUModel")]`
- L38 _public property_ `public int RAMInGB { get; set; }` — attrs: `[JsonPropertyName("rAMInGB")]`
- L40 _public property_ `public string RenderMode { get; set; }` — attrs: `[JsonPropertyName("renderMode")]`
- L42 _public property_ `public string RHI { get; set; }` — attrs: `[JsonPropertyName("rHI")]`
- L44 _public property_ `public string AppInstanceLog { get; set; }` — attrs: `[JsonPropertyName("appInstanceLog")]`

#### class `Gauntlet.UnrealAutomationArtifact`  
`public class UnrealAutomationArtifact`  
_public; L46-56_
- L49 _public property_ `public string Id { get; set; }` — attrs: `[JsonPropertyName("id")]`
- L51 _public property_ `public string Name { get; set; }` — attrs: `[JsonPropertyName("name")]`
- L53 _public property_ `public string Type { get; set; }` — attrs: `[JsonPropertyName("type")]`
- L55 _public property_ `public Dictionary<string, string> Files { get; set; }` — attrs: `[JsonPropertyName("files")]`

#### class `Gauntlet.UnrealAutomationEvent`  
`public class UnrealAutomationEvent`  
_public; L57-155_
- L60 _public property_ `public EventType Type { get; set; }` — attrs: `[JsonPropertyName("type")]`
- L62 _public property_ `public string Message { get; set; }` — attrs: `[JsonPropertyName("message")]`
- L64 _public property_ `public string Context { get; set; }` — attrs: `[JsonPropertyName("context")]`
- L66 _public property_ `public string Artifact { get; set; }` — attrs: `[JsonPropertyName("artifact")]`
- L68 _private* const_ `const string CriticalFailureString = "critical failure"`
- L69 _private* const_ `const string SanitizerReportString = "Sanitizer: "`
- L71-72 _public ctor_ `public UnrealAutomationEvent()`
- L73-81 _public ctor_ `public UnrealAutomationEvent(EventType InType, string InMessage, bool bIsCriticalFailure = false)`
- L84-91 _public property_ `public bool IsError { get; }` — attrs: `[JsonIgnore]`
- L94-101 _public property_ `public bool IsWarning { get; }` — attrs: `[JsonIgnore]`
- L104-110 _public property_ `public bool IsCriticalFailure { get; }` — attrs: `[JsonIgnore]`
- L111-118 _public method_ `public void SetAsCriticalFailure()`
- L124-130 _public property_ `public bool IsSanReport { get; }` — attrs: `[JsonIgnore]` — True if the event contains a Sanitizer report
- L132-135 _public method_ `public string FormatToString()`
- L137-140 _protected method_ `protected bool Equals(UnrealAutomationEvent other)`
- L142-148 _public method_ `public override bool Equals(object obj)`
- L150-153 _public method_ `public override int GetHashCode()`

#### class `Gauntlet.UnrealAutomationEntry`  
`public class UnrealAutomationEntry`  
_public; L156-276_
- L159 _public property_ `public UnrealAutomationEvent Event { get; set; }` — attrs: `[JsonPropertyName("event")]`
- L161 _public property_ `public string Filename { get; set; }` — attrs: `[JsonPropertyName("filename")]`
- L163 _public property_ `public int LineNumber { get; set; }` — attrs: `[JsonPropertyName("lineNumber")]`
- L165 _public property_ `public string Timestamp { get; set; }` — attrs: `[JsonPropertyName("timestamp")]`
- L167 _public const_ `public const string InvalidDateTime = "0001.01.01-00.00.00"`
- L168 _public const_ `public const string DateTimeFormat = "yyyy.MM.dd-HH.mm.ss"`
- L174 _private field_ `private static Regex SummaryPattern = new Regex(@"\w[\w ]+:(?:\s+.+)?\s+\[[^]]+\.[^]]+\](?:\s*\[[^]]+\])?(?:\s*\n\w+.+)? *", RegexOptions.Multiline | RegexOptions.ExplicitCapture)` — Regex pattern to match assertion, ensure and other crash report summary from UE ie: Assertion failed: !This->CurrentlySerializingObject [File:.\\Runtime/CoreUObject/Private/Misc/GCObjectReferencer.cpp] [Line: 54]
- L176-184 _public method_ `public static DateTime GetTimestampAsDateTime(string StringTime)`
- L190-257 _public method_ `public LogEvent AsLogEvent()` — Produce a LogEvent instance from this UnrealAutomationEntry
- L259-262 _protected method_ `protected bool Equals(UnrealAutomationEntry other)`
- L264-270 _public method_ `public override bool Equals(object obj)`
- L272-275 _public method_ `public override int GetHashCode()`

#### class `Gauntlet.UnrealAutomatedTestResult`  
`public class UnrealAutomatedTestResult`  
_public; L277-420_
- L280 _public property_ `public string TestDisplayName { get; set; }` — attrs: `[JsonPropertyName("testDisplayName")]`
- L282 _public property_ `public string FullTestPath { get; set; }` — attrs: `[JsonPropertyName("fullTestPath")]`
- L284 _public property_ `public List<string> Tags { get; set; }` — attrs: `[JsonPropertyName("tags")]`
- L286 _public property_ `public string ArtifactName { get; set; }` — attrs: `[JsonPropertyName("artifactName")]`
- L288 _public property_ `public TestStateType State { get; set; }` — attrs: `[JsonPropertyName("state")]`
- L290 _public property_ `public List<string> DeviceInstance { get; set; }` — attrs: `[JsonPropertyName("deviceInstance")]`
- L292 _public property_ `public float Duration { get; set; }` — attrs: `[JsonPropertyName("duration")]`
- L294 _public property_ `public string DateTime { get; set; }` — attrs: `[JsonPropertyName("dateTime")]`
- L296 _public property_ `public int Warnings { get; set; }` — attrs: `[JsonPropertyName("warnings")]`
- L298 _public property_ `public int Errors { get; set; }` — attrs: `[JsonPropertyName("errors")]`
- L300 _public property_ `public List<UnrealAutomationArtifact> Artifacts { get; set; }` — attrs: `[JsonPropertyName("artifacts")]`
- L302 _public property_ `public List<UnrealAutomationEntry> Entries { get; set; }` — attrs: `[JsonPropertyName("entries")]`
- L304-308 _public ctor_ `public UnrealAutomatedTestResult()`
- L310-327 _public method_ `public void AddEvent(EventType EventType, string Message, bool bIsCriticalFailure = false)`
- L328-331 _public method_ `public void AddError(string Message, bool bIsCriticalFailure = false)`
- L332-335 _public method_ `public void AddWarning(string Message)`
- L336-339 _public method_ `public void AddInfo(string Message)`
- L342-348 _public property_ `public bool IsComplete { get; }` — attrs: `[JsonIgnore]`
- L350-356 _public property_ `public bool HasSucceeded { get; }` — attrs: `[JsonIgnore]`
- L358-364 _public property_ `public bool HasFailed { get; }` — attrs: `[JsonIgnore]`
- L366-372 _public property_ `public bool WasSkipped { get; }` — attrs: `[JsonIgnore]`
- L374-380 _public property_ `public bool HasWarnings { get; }` — attrs: `[JsonIgnore]`
- L382-388 _public property_ `public IEnumerable<UnrealAutomationEvent> ErrorEvents { get; }` — attrs: `[JsonIgnore]`
- L390-396 _public property_ `public IEnumerable<UnrealAutomationEvent> WarningEvents { get; }` — attrs: `[JsonIgnore]`
- L398-404 _public property_ `public IEnumerable<UnrealAutomationEvent> WarningAndErrorEvents { get; }` — attrs: `[JsonIgnore]`
- L406-409 _public method_ `public IEnumerable<UnrealAutomationEntry> GetErrorEntries()`
- L411-414 _public method_ `public IEnumerable<UnrealAutomationEntry> GetWarningEntries()`
- L416-419 _public method_ `public IEnumerable<UnrealAutomationEntry> GetWarningAndErrorEntries()`

#### class `Gauntlet.UnrealAutomatedTestPassResults`  
`public class UnrealAutomatedTestPassResults`  
_public; L421-550_
- L424 _public property_ `public List<UnrealAutomationDevice> Devices { get; set; }` — attrs: `[JsonPropertyName("devices")]`
- L426 _public property_ `public string ReportCreatedOn { get; set; }` — attrs: `[JsonPropertyName("reportCreatedOn")]`
- L428 _public property_ `public int Succeeded { get; set; }` — attrs: `[JsonPropertyName("succeeded")]`
- L430 _public property_ `public int SucceededWithWarnings { get; set; }` — attrs: `[JsonPropertyName("succeededWithWarnings")]`
- L432 _public property_ `public int Failed { get; set; }` — attrs: `[JsonPropertyName("failed")]`
- L434 _public property_ `public int NotRun { get; set; }` — attrs: `[JsonPropertyName("notRun")]`
- L436 _public property_ `public int InProcess { get; set; }` — attrs: `[JsonPropertyName("inProcess")]`
- L438 _public property_ `public float TotalDuration { get; set; }` — attrs: `[JsonPropertyName("totalDuration")]`
- L440 _public property_ `public bool ComparisonExported { get; set; }` — attrs: `[JsonPropertyName("comparisonExported")]`
- L442 _public property_ `public string ComparisonExportDirectory { get; set; }` — attrs: `[JsonPropertyName("comparisonExportDirectory")]`
- L444 _public property_ `public List<UnrealAutomatedTestResult> Tests { get; set; }` — attrs: `[JsonPropertyName("tests")]`
- L446 _private field_ `private string FilePath`
- L448-451 _public method_ `public void SetFilePath(string InFilePath)`
- L453-457 _public ctor_ `public UnrealAutomatedTestPassResults()`
- L459-467 _public method_ `public UnrealAutomatedTestResult AddTest(string DisplayName, string FullName, TestStateType State)`
- L469-497 _public method_ `public UnrealAutomatedTestResult AddTest(UnrealAutomatedTestResult Test)`
- L503-513 _public method_ `public static UnrealAutomatedTestPassResults LoadFromJson(string FilePath)` — Load Unreal Automated Test Results from json report
- L519-549 _public method_ `public void WriteToJson(string InFilePath = null)` — Write json data into a file
