# CSharp / MetadataServer

- project root: `Source/Programs/UnrealGameSync/MetadataServer`
- files: 22; symbols: 208
- symbol kinds: class=32, const=1, ctor=1, enum=4, enumerator=20, field=75, method=64, property=11
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealGameSync/MetadataServer/App_Start/WebApiConfig.cs` (MetadataServer)


#### class `MetadataServer.WebApiConfig`  
`public static class WebApiConfig`  
_public; L7-44_
- L9-43 _public method_ `public static void Register(HttpConfiguration config)`

### `Source/Programs/UnrealGameSync/MetadataServer/Connectors/SqlConnector.cs` (MetadataServer)


#### class `MetadataServer.Connectors.SqlConnector`  
`public static class SqlConnector`  
_public; L17-860_
- L19 _private field_ `private static string ConnectionString = System.Configuration.ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString`
- L20 _private field_ `private static bool StoreBuildMetadata = Convert.ToBoolean(System.Configuration.ConfigurationManager.AppSettings["StoreBuildMetadata"])`
- L22-82 _public method_ `public static LatestData GetLastIds(string Project = null)`
- L83-116 _public method_ `public static List<EventData> GetUserVotes(string Project, long LastEventId)`
- L117-148 _public method_ `public static List<CommentData> GetComments(string Project, long LastCommentId)`
- L150-196 _public method_ `public static List<BuildData> GetBuilds(string Project, long LastBuildId)`
- L198-226 _public method_ `public static List<TelemetryErrorData> GetErrorData(int Records)`
- L228-236 _private method_ `private static long TryInsertAndGetProject(MySqlConnection Connection, string Project)`
- L237-263 _public method_ `public static void PostBuild(BuildData Build)`
- L265-281 _public method_ `public static void PostEvent(EventData Event)`
- L283-299 _public method_ `public static void PostComment(CommentData Comment)`
- L301-321 _public method_ `public static void PostTelemetryData(TelemetryTimingData Data, string Version, string IpAddress)`
- L323-354 _public method_ `public static void PostErrorData(TelemetryErrorData Data, string Version, string IpAddress)`
- L355-365 _private method_ `private static string GetProjectStream(string Project)`
- L366-369 _private method_ `private static bool MatchesWildcard(string Wildcard, string Project)`
- L371-374 _private method_ `private static string NormalizeUserName(string UserName)`
- L376-383 _public method_ `public static long FindOrAddUserId(string Name)`
- L385-410 _private method_ `private static long FindOrAddUserId(string Name, MySqlConnection Connection)`
- L412 _private* const_ `const int IssueSummaryMaxLength = 200`
- L414-439 _public method_ `public static long AddIssue(IssueData Issue)`
- L441-452 _public method_ `public static IssueData GetIssue(long IssueId)`
- L454-457 _public method_ `public static List<IssueData> GetIssues(bool IncludeResolved, int NumResults)`
- L459-462 _public method_ `public static List<IssueData> GetIssues(string UserName)`
- L464-540 _private method_ `private static List<IssueData> GetIssuesInternal(long IssueId, string UserName, bool IncludeResolved, int NumResults)`
- L542-602 _public method_ `public static void UpdateIssue(long IssueId, IssueUpdateData Issue)`
- L604-619 _public method_ `public static string SanitizeText(string Text, int Length)`
- L621-649 _public method_ `public static void DeleteIssue(long IssueId)`
- L651-666 _public method_ `public static void AddDiagnostic(long IssueId, IssueDiagnosticData Diagnostic)`
- L668-696 _public method_ `public static List<IssueDiagnosticData> GetDiagnostics(long IssueId)`
- L698-713 _public method_ `public static void AddWatcher(long IssueId, string UserName)`
- L715-740 _public method_ `public static List<string> GetWatchers(long IssueId)`
- L742-757 _public method_ `public static void RemoveWatcher(long IssueId, string UserName)`
- L759-781 _public method_ `public static long AddBuild(long IssueId, IssueBuildData Build)`
- L783-812 _public method_ `public static List<IssueBuildData> GetBuilds(long IssueId)`
- L814-844 _public method_ `public static IssueBuildData GetBuild(long BuildId)`
- L846-859 _public method_ `public static void UpdateBuild(long BuildId, int Outcome)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/BuildController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.BuildController`  
`public class BuildController : ApiController`  
_public; L10-20_
- inherits: `ApiController`
- L12-15 _public method_ `public List<BuildData> Get(string Project, long LastBuildId)`
- L16-19 _public method_ `public void Post([FromBody]BuildData Build)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/CISController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.CISController`  
`public class CISController : ApiController`  
_public; L12-27_
- inherits: `ApiController`
- L14-18 _public method_ `public long[] Get(string Project = null)`
- L19-22 _public method_ `public List<BuildData> Get(string Project, long LastBuildId)`
- L23-26 _public method_ `public void Post([FromBody]BuildData Build)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/CommentController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.CommentController`  
`public class CommentController : ApiController`  
_public; L10-20_
- inherits: `ApiController`
- L12-15 _public method_ `public List<CommentData> Get(string Project, long LastCommentId)`
- L16-19 _public method_ `public void Post([FromBody] CommentData Comment)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/ErrorController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.ErrorController`  
`public class ErrorController : ApiController`  
_public; L10-20_
- inherits: `ApiController`
- L12-15 _public method_ `public List<TelemetryErrorData> Get(int Records = 10)`
- L16-19 _public method_ `public void Post([FromBody] TelemetryErrorData Data, string Version, string IpAddress)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/EventController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.EventController`  
`public class EventController : ApiController`  
_public; L10-21_
- inherits: `ApiController`
- L12-15 _public method_ `public List<EventData> Get(string Project, long LastEventId)`
- L17-20 _public method_ `public void Post([FromBody] EventData Event)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/IssuesController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.IssuesController`  
`public class IssuesController : ApiController`  
_public; L16-54_
- inherits: `ApiController`
- L19-22 _public method_ `public List<IssueData> Get(bool IncludeResolved = false, int MaxResults = -1)` — attrs: `[HttpGet]`
- L25-28 _public method_ `public List<IssueData> Get(string User)` — attrs: `[HttpGet]`
- L31-34 _public method_ `public IssueData Get(long id)` — attrs: `[HttpGet]`
- L37-40 _public method_ `public void Put(long id, IssueUpdateData Issue)` — attrs: `[HttpPut]`
- L43-47 _public method_ `public object Post(IssueData Issue)` — attrs: `[HttpPost]`
- L50-53 _public method_ `public void Delete(long id)` — attrs: `[HttpDelete]`

#### class `MetadataServer.Controllers.IssueBuildsSubController`  
`public class IssueBuildsSubController : ApiController`  
_public; L56-70_
- inherits: `ApiController`
- L59-62 _public method_ `public List<IssueBuildData> Get(long IssueId)` — attrs: `[HttpGet]`
- L65-69 _public method_ `public object Post(long IssueId, [FromBody] IssueBuildData Data)` — attrs: `[HttpPost]`

#### class `MetadataServer.Controllers.IssueDiagnosticsSubController`  
`public class IssueDiagnosticsSubController : ApiController`  
_public; L72-85_
- inherits: `ApiController`
- L75-78 _public method_ `public List<IssueDiagnosticData> Get(long IssueId)` — attrs: `[HttpGet]`
- L81-84 _public method_ `public void Post(long IssueId, [FromBody] IssueDiagnosticData Data)` — attrs: `[HttpPost]`

#### class `MetadataServer.Controllers.IssueBuildsController`  
`public class IssueBuildsController : ApiController`  
_public; L87-100_
- inherits: `ApiController`
- L90-93 _public method_ `public IssueBuildData Get(long BuildId)` — attrs: `[HttpGet]`
- L96-99 _public method_ `public void Put(long BuildId, [FromBody] IssueBuildUpdateData Data)` — attrs: `[HttpPut]`

#### class `MetadataServer.Controllers.IssueWatchersController`  
`public class IssueWatchersController : ApiController`  
_public; L102-121_
- inherits: `ApiController`
- L105-108 _public method_ `public List<string> Get(long IssueId)` — attrs: `[HttpGet]`
- L111-114 _public method_ `public void Post(long IssueId, [FromBody] IssueWatcherData Data)` — attrs: `[HttpPost]`
- L117-120 _public method_ `public void Delete(long IssueId, [FromBody] IssueWatcherData Data)` — attrs: `[HttpDelete]`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/LatestController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.LatestController`  
`public class LatestController : ApiController`  
_public; L14-20_
- inherits: `ApiController`
- L16-19 _public method_ `public LatestData Get(string Project = null)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/TelemetryController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.TelemetryController`  
`public class TelemetryController : ApiController`  
_public; L9-15_
- inherits: `ApiController`
- L11-14 _public method_ `public void Post([FromBody] TelemetryTimingData Data, string Version, string IpAddress)`

### `Source/Programs/UnrealGameSync/MetadataServer/Controllers/UserController.cs` (MetadataServer)


#### class `MetadataServer.Controllers.UserController`  
`public class UserController : ApiController`  
_public; L11-18_
- inherits: `ApiController`
- L13-17 _public method_ `public object Get(string Name)`

### `Source/Programs/UnrealGameSync/MetadataServer/Global.asax.cs` (MetadataServer)


#### class `MetadataServer.WebApiApplication`  
`public class WebApiApplication : System.Web.HttpApplication`  
_public; L13-36_
- inherits: `System.Web.HttpApplication`
- L15-35 _protected method_ `protected void Application_Start()`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/BuildData.cs` (MetadataServer)


#### class `MetadataServer.Models.Link`  
`public class Link`  
_public; L10-14_
- L12 _public property_ `public string Text { get; set; }`
- L13 _public property_ `public string Url { get; set; }`

#### class `MetadataServer.Models.BuildMetadata`  
`public class BuildMetadata`  
_public; L16-19_
- L18 _public property_ `public List<Link> Links { get; set; }`

#### class `MetadataServer.Models.BuildData`  
`public class BuildData`  
_public; L21-50_
- L32 _public field_ `public long Id`
- L33 _public field_ `public int ChangeNumber`
- L34 _public field_ `public string BuildType`
- L35 _public field_ `public BuildDataResult Result`
- L36 _public field_ `public string Url`
- L37 _public field_ `public string Project`
- L38 _public field_ `public string ArchivePath`
- L39 _public field_ `public BuildMetadata Metadata`
- L41-44 _public property_ `public bool IsSuccess { get; }`
- L46-49 _public property_ `public bool IsFailure { get; }`

#### enum `MetadataServer.Models.BuildData.BuildDataResult`  
`public enum BuildDataResult`  
_public; L23-30_
- L25 _public* enumerator_ `Starting`
- L26 _public* enumerator_ `Failure`
- L27 _public* enumerator_ `Warning`
- L28 _public* enumerator_ `Success`
- L29 _public* enumerator_ `Skipped`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/CommentData.cs` (MetadataServer)


#### class `MetadataServer.Models.CommentData`  
`public class CommentData`  
_public; L10-17_
- L12 _public field_ `public long Id`
- L13 _public field_ `public int ChangeNumber`
- L14 _public field_ `public string UserName`
- L15 _public field_ `public string Text`
- L16 _public field_ `public string Project`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/EventData.cs` (MetadataServer)


#### class `MetadataServer.Models.EventData`  
`public class EventData`  
_public; L10-37_
- L32 _public field_ `public long Id`
- L33 _public field_ `public int Change`
- L34 _public field_ `public string UserName`
- L35 _public field_ `public EventType Type`
- L36 _public field_ `public string Project`

#### enum `MetadataServer.Models.EventData.EventType`  
`public enum EventType`  
_public; L12-30_
- L14 _public* enumerator_ `Syncing`
- L17 _public* enumerator_ `Compiles`
- L18 _public* enumerator_ `DoesNotCompile`
- L19 _public* enumerator_ `Good`
- L20 _public* enumerator_ `Bad`
- L21 _public* enumerator_ `Unknown`
- L24 _public* enumerator_ `Starred`
- L25 _public* enumerator_ `Unstarred`
- L28 _public* enumerator_ `Investigating`
- L29 _public* enumerator_ `Resolved`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/EventSummary.cs` (MetadataServer)


#### class `MetadataServer.Models.EventSummary`  
`public class EventSummary`  
_public; L10-28_
- L20 _public field_ `public int ChangeNumber`
- L21 _public field_ `public ReviewVerdict Verdict`
- L22 _public field_ `public List<EventData> SyncEvents = new List<EventData>()`
- L23 _public field_ `public List<EventData> Reviews = new List<EventData>()`
- L24 _public field_ `public List<string> CurrentUsers = new List<string>()`
- L25 _public field_ `public EventData LastStarReview`
- L26 _public field_ `public List<BuildData> Builds = new List<BuildData>()`
- L27 _public field_ `public List<CommentData> Comments = new List<CommentData>()`

#### enum `MetadataServer.Models.EventSummary.ReviewVerdict`  
`public enum ReviewVerdict`  
_public; L12-18_
- L14 _public* enumerator_ `Unknown`
- L15 _public* enumerator_ `Good`
- L16 _public* enumerator_ `Bad`
- L17 _public* enumerator_ `Mixed`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/IssueData.cs` (MetadataServer)


#### class `MetadataServer.Models.IssueWatcherData`  
`public class IssueWatcherData`  
_public; L11-14_
- L13 _public field_ `public string UserName`

#### class `MetadataServer.Models.IssueBuildData`  
`public class IssueBuildData`  
_public; L16-27_
- L18 _public field_ `public long Id`
- L19 _public field_ `public string Stream`
- L20 _public field_ `public int Change`
- L21 _public field_ `public string JobName`
- L22 _public field_ `public string JobUrl`
- L23 _public field_ `public string JobStepName`
- L24 _public field_ `public string JobStepUrl`
- L25 _public field_ `public string ErrorUrl`
- L26 _public field_ `public int Outcome`

#### class `MetadataServer.Models.IssueBuildUpdateData`  
`public class IssueBuildUpdateData`  
_public; L29-32_
- L31 _public field_ `public int Outcome`

#### class `MetadataServer.Models.IssueDiagnosticData`  
`public class IssueDiagnosticData`  
_public; L34-39_
- L36 _public field_ `public long? BuildId`
- L37 _public field_ `public string Message`
- L38 _public field_ `public string Url`

#### class `MetadataServer.Models.IssueData`  
`public class IssueData`  
_public; L41-54_
- L43 _public field_ `public long Id`
- L44 _public field_ `public DateTime CreatedAt`
- L45 _public field_ `public DateTime RetrievedAt`
- L46 _public field_ `public string Project`
- L47 _public field_ `public string Summary`
- L48 _public field_ `public string Owner`
- L49 _public field_ `public string NominatedBy`
- L50 _public field_ `public DateTime? AcknowledgedAt`
- L51 _public field_ `public int FixChange`
- L52 _public field_ `public DateTime? ResolvedAt`
- L53 _public field_ `public bool bNotify`

#### class `MetadataServer.Models.IssueUpdateData`  
`public class IssueUpdateData`  
_public; L56-64_
- L58 _public field_ `public string Summary`
- L59 _public field_ `public string Owner`
- L60 _public field_ `public string NominatedBy`
- L61 _public field_ `public bool? Acknowledged`
- L62 _public field_ `public int? FixChange`
- L63 _public field_ `public bool? Resolved`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/LatestData.cs` (MetadataServer)


#### class `MetadataServer.Models.LatestData`  
`public class LatestData`  
_public; L10-15_
- L12 _public property_ `public long LastEventId { get; set; }`
- L13 _public property_ `public long LastCommentId { get; set; }`
- L14 _public property_ `public long LastBuildId { get; set; }`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/TelemetryErrorData.cs` (MetadataServer)


#### class `MetadataServer.Models.TelemetryErrorData`  
`public class TelemetryErrorData`  
_public; L10-24_
- L16 _public field_ `public int Id`
- L17 _public field_ `public TelemetryErrorType Type`
- L18 _public field_ `public string Text`
- L19 _public field_ `public string UserName`
- L20 _public field_ `public string Project`
- L21 _public field_ `public DateTime Timestamp`
- L22 _public field_ `public string Version`
- L23 _public field_ `public string IpAddress`

#### enum `MetadataServer.Models.TelemetryErrorData.TelemetryErrorType`  
`public enum TelemetryErrorType`  
_public; L12-15_
- L14 _public* enumerator_ `Crash`

### `Source/Programs/UnrealGameSync/MetadataServer/Models/TelemetryTimingData.cs` (MetadataServer)


#### class `MetadataServer.Models.TelemetryTimingData`  
`public class TelemetryTimingData`  
_public; L10-18_
- L12 _public field_ `public string Action`
- L13 _public field_ `public string Result`
- L14 _public field_ `public string UserName`
- L15 _public field_ `public string Project`
- L16 _public field_ `public DateTime Timestamp`
- L17 _public field_ `public float Duration`

### `Source/Programs/UnrealGameSync/MetadataServer/Properties/AssemblyInfo.cs` (MetadataServer)
_(no declarations)_


### `Source/Programs/UnrealGameSync/MetadataServer/Properties/Resources.Designer.cs` (MetadataServer)


#### class `MetadataServer.Properties.Resources`  
`internal class Resources`  
_internal; L25-89_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.
- L84-88 _internal property_ `internal static string Setup { get; }` — Looks up a localized string similar to CREATE DATABASE IF NOT EXISTS ugs_db; CREATE TABLE IF NOT EXISTS ugs_db.Projects ( Id INT NOT NULL AUTO_INCREMENT, `Name` NVARCHAR(128) NOT NULL UNIQUE, PRIMARY KEY ( Id ) ); CREATE TABLE IF NOT EXISTS ugs_db.CIS ( Id INT NOT NULL AUTO_INCREMENT, ChangeNumber INT NOT NULL, BuildType NCHAR(32) NOT NULL, Result NCHAR(10) NOT NULL, Url VARCHAR(512) NOT NULL, Project VARCHAR(512) NULL, ProjectId INTEGER NULL, ArchivePath VARCHAR(512) NULL, PRIMARY KEY ( Id ), FOREIGN [rest of string was truncated]&quot;;.
