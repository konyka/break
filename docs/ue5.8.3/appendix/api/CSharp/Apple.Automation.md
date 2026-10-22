# CSharp / Apple.Automation

- project root: `Source/Programs/AutomationTool/Apple`
- files: 3; symbols: 58
- symbol kinds: class=3, ctor=2, field=6, method=21, property=1, record=25
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Apple/ApplePlatform.Automation.cs` (Apple.Automation)


#### class `ApplePlatform`  
`public abstract class ApplePlatform : Platform`  
_public; L15-380_
- inherits: `Platform`
- L17-20 _public ctor_ `public ApplePlatform(UnrealTargetPlatform TargetPlatform) : base(TargetPlatform)`
- L24-53 _public method_ `public override bool GetSDKInstallCommand(out string Command, out string Params, ref bool bRequiresPrivilegeElevation, ref bool bCreateWindow, ITurnkeyContext TurnkeyContext)`
- L55-69 _public method_ `public override bool OnSDKInstallComplete(int ExitCode, ITurnkeyContext TurnkeyContext, DeviceInfo Device)`
- L73-82 _public method_ `public override void PreBuildAgenda(UnrealBuild Build, UnrealBuild.BuildAgenda Agenda, ProjectParams Params)`
- L84-92 _private method_ `private string MakeContentOnlyTargetName(TargetReceipt Target, string GameName)`
- L94-160 _public method_ `public override void PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)`
- L162-185 _private method_ `private DirectoryReference GetArchivePath(StageTarget Target, DeploymentContext SC)`
- L187-219 _private method_ `private DirectoryReference GetFinalAppPath(StageTarget Target, DeploymentContext SC)`
- L221-317 _public method_ `public override void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L319-379 _public method_ `public override void GetFilesToArchive(ProjectParams Params, DeploymentContext SC)`

### `Source/Programs/AutomationTool/Apple/ExportAppleBuild.Automation.cs` (Apple.Automation)


#### class `ExportAppleBuild`  
`class ExportAppleBuild : BuildCommand`  
_internal*; L29-655_
- inherits: `BuildCommand`
- L31-181 _public method_ `public override ExitCode Execute()`
- L219 _private* field_ `static CancellationToken CancellationToken = new()`
- L222 _private* field_ `JwtTokenClient TokenClient = null`
- L224-228 _private method_ `private async Task<TResponse> GetAsync<TResponse>(string RelativePath, CancellationToken CancellationToken = default)`
- L230-234 _private* method_ `string GetAppId(string BundleId)`
- L236-271 _private* method_ `string GetBuildId(string AppId, string PreReleaseVersion, string BuildVersion)`
- L274-287 _private* method_ `string GetLocalizationId(string BuildId)`
- L290-443 _private* method_ `bool CheckVersion(JwtTokenClient TokenClient, ref DirectoryReference XcArchive, string SigningIdentity, string Increment)`
- L446-467 _private* method_ `bool CreateWhatsNew(string BuildId, string Text)`
- L469-487 _private* method_ `bool SetWhatsNew(string LocId, string Text)`
- L489-585 _private* method_ `bool UpdateWhatsNew(JwtTokenClient TokenClient, string BundleId, string PreReleaseVersion, string BundleVersion, string Text, int Delay = 30, int Tries = 30)`
- L587-654 _private* method_ `static void GetInfoFromXcArchive(DirectoryReference XcArchive, out string BundleId, out string AppVersion, out string BundleVersion, out string CommandLine)`

#### record `ExportAppleBuild.Links`  
`record Links(string self, string related)`  
_private*; L184-184_

#### record `ExportAppleBuild.Relationship`  
`record Relationship(Links links)`  
_private*; L185-185_

#### record `ExportAppleBuild.AppInfo`  
`record AppInfo(string type, string id)`  
_private*; L187-187_

#### record `ExportAppleBuild.AppResponse`  
`record AppResponse(List<AppInfo> data)`  
_private*; L188-188_

#### record `ExportAppleBuild.BuildRelationships`  
`record BuildRelationships(Relationship preReleaseVersion)`  
_private*; L191-191_

#### record `ExportAppleBuild.BuildAttributes`  
`record BuildAttributes(string version, string processingState, string uploadedDate)`  
_private*; L192-192_

#### record `ExportAppleBuild.BuildInfo`  
`record BuildInfo(string type, string id, BuildAttributes attributes, BuildRelationships relationships)`  
_private*; L193-193_

#### record `ExportAppleBuild.BuildsResponse`  
`record BuildsResponse(List<BuildInfo> data)`  
_private*; L194-194_

#### record `ExportAppleBuild.VersionAttributes`  
`record VersionAttributes(string version, string platform)`  
_private*; L196-196_

#### record `ExportAppleBuild.VersionInfo`  
`record VersionInfo(string id, VersionAttributes attributes)`  
_private*; L197-197_

#### record `ExportAppleBuild.VersionResponse`  
`record VersionResponse(VersionInfo data)`  
_private*; L198-198_

#### record `ExportAppleBuild.VersionsResponse`  
`record VersionsResponse(List<VersionInfo> data)`  
_private*; L199-199_

#### record `ExportAppleBuild.BuildsWithVersionsResponse`  
`record BuildsWithVersionsResponse(List<BuildInfo> data, List<VersionInfo> included)`  
_private*; L201-201_

#### record `ExportAppleBuild.PagedLinks`  
`record PagedLinks(string next)`  
_private*; L203-203_

#### record `ExportAppleBuild.PagedBuildsResponse`  
`record PagedBuildsResponse(List<BuildInfo> data, PagedLinks links)`  
_private*; L204-204_

#### record `ExportAppleBuild.LocalizationAttributes`  
`record LocalizationAttributes(string whatsNew)`  
_private*; L206-206_

#### record `ExportAppleBuild.LocalizationInfo`  
`record LocalizationInfo(string type, string id, LocalizationAttributes attributes)`  
_private*; L207-207_

#### record `ExportAppleBuild.LocalizationResponse`  
`record LocalizationResponse(List<LocalizationInfo> data)`  
_private*; L208-208_

#### record `ExportAppleBuild.LocalizationUpdate`  
`record LocalizationUpdate(LocalizationInfo data)`  
_private*; L209-209_

#### record `ExportAppleBuild.LocalizationRelationship`  
`record LocalizationRelationship(string id, string type)`  
_private*; L211-211_

#### record `ExportAppleBuild.LocalizationRelationshipsData`  
`record LocalizationRelationshipsData(LocalizationRelationship data)`  
_private*; L212-212_

#### record `ExportAppleBuild.LocalizationRelationships`  
`record LocalizationRelationships(LocalizationRelationshipsData build)`  
_private*; L213-213_

#### record `ExportAppleBuild.LocalizationCreateAttributes`  
`record LocalizationCreateAttributes(string locale, string whatsNew)`  
_private*; L214-214_

#### record `ExportAppleBuild.LocalizationCreateInfo`  
`record LocalizationCreateInfo(LocalizationCreateAttributes attributes, LocalizationRelationships relationships, string type)`  
_private*; L215-215_

#### record `ExportAppleBuild.LocalizationCreateRequest`  
`record LocalizationCreateRequest(LocalizationCreateInfo data)`  
_private*; L216-216_

#### class `JwtTokenClient`  
`class JwtTokenClient`  
_internal*; L657-759_
- L659-665 _public ctor_ `public JwtTokenClient(FileReference ProjectFile)`
- L667-674 _public property_ `public HttpClient Client { get; }`
- L676 _private field_ `private DateTime expirationDate = DateTime.MinValue`
- L677 _private field_ `private string token = ""`
- L678 _private field_ `private FileReference projectFile`
- L679 _private field_ `private HttpClient client`
- L681-690 _private* method_ `void CheckExpiration()`
- L692-758 _private* method_ `void CreateJWTToken()`

### `Source/Programs/AutomationTool/Apple/Properties/AssemblyInfo.cs` (Apple.Automation)
_(no declarations)_

