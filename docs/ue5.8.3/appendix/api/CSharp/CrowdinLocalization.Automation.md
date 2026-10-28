# CSharp / CrowdinLocalization.Automation

- project root: `Source/Programs/AutomationTool/CrowdinLocalization`
- files: 2; symbols: 68
- symbol kinds: class=12, ctor=1, field=9, method=11, property=33, struct=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/CrowdinLocalization/CrowdinLocalizationProvider.cs` (CrowdinLocalization.Automation)


#### struct `EpicGames.CrowdinLocalization.CrowdInUrlData`  
`struct CrowdInUrlData`  
_internal*; L25-31_
- L27 _public property_ `public string Url { get; set; }`
- L28 _public property_ `public DateTime ExpireIn { get; set; }`
- L30 _public property_ `public string ETag { get; set; }`

#### class `EpicGames.CrowdinLocalization.DataEnvelope`  
`class DataEnvelope<T>`  
_internal*; L33-36_
- L35 _public property_ `public T Data { get; set; }`

#### struct `EpicGames.CrowdinLocalization.Pagination`  
`struct Pagination`  
_internal*; L38-42_
- L40 _public property_ `public int Offset { get; set; }`
- L41 _public property_ `public int Limit { get; set; }`

#### class `EpicGames.CrowdinLocalization.FileInfoData`  
`public class FileInfoData`  
_public; L44-55_
- L46 _public property_ `public int Id { get; set; }`
- L47 _public property_ `public int? projectId { get; set; }`
- L48 _public property_ `public int? branchId { get; set; }`
- L49 _public property_ `public int? directoryId { get; set; }`
- L50 _public property_ `public string name { get; set; }`
- L51 _public property_ `public string title { get; set; }`
- L52 _public property_ `public string type { get; set; }`
- L53 _public property_ `public string path { get; set; }`
- L54 _public property_ `public string status { get; set; }`

#### class `EpicGames.CrowdinLocalization.PagedData`  
`class PagedData<T>`  
_internal*; L57-61_
- L59 _public property_ `public DataEnvelope<T>[] Data { get; set; }`
- L60 _public property_ `public Pagination Pagination { get; set; }`

#### class `EpicGames.CrowdinLocalization.StorageResponse`  
`public class StorageResponse`  
_public; L63-67_
- L65 _public property_ `public int Id { get; set; }`
- L66 _public property_ `public string FileName { get; set; }`

#### class `EpicGames.CrowdinLocalization.TranslationUploadResponse`  
`public class TranslationUploadResponse`  
_public; L69-75_
- L71 _public property_ `public int projectId { get; set; }`
- L72 _public property_ `public int storageId { get; set; }`
- L73 _public property_ `public string languageId { get; set; }`
- L74 _public property_ `public int fileId { get; set; }`

#### class `EpicGames.CrowdinLocalization.RequestErrors`  
`public class RequestErrors`  
_public; L77-80_
- L79 _public property_ `public RequestErrorEnvelope[] Errors { get; set; }`

#### class `EpicGames.CrowdinLocalization.RequestErrorEnvelope`  
`public class RequestErrorEnvelope`  
_public; L82-85_
- L84 _public property_ `public RequestError Error { get; set; }`

#### class `EpicGames.CrowdinLocalization.RequestError`  
`public class RequestError`  
_public; L87-91_
- L89 _public property_ `public string key { get; set; }`
- L90 _public property_ `public RequestKeyError[] Errors { get; set; }`

#### class `EpicGames.CrowdinLocalization.RequestKeyError`  
`public class RequestKeyError`  
_public; L93-97_
- L95 _public property_ `public string code { get; set; }`
- L96 _public property_ `public string message { get; set; }`

#### class `EpicGames.CrowdinLocalization.BranchInfo`  
`public class BranchInfo`  
_public; L99-105_
- L101 _public property_ `public int id { get; set; }`
- L102 _public property_ `public int projectId { get; set; }`
- L103 _public property_ `public string name { get; set; }`
- L104 _public property_ `public string title { get; set; }`

#### class `EpicGames.CrowdinLocalization.CrowdinConfig`  
`public class CrowdinConfig`  
_public; L107-111_
- L109 _public field_ `public string ProjectId`
- L110 _public field_ `public string AccessToken`

#### class `EpicGames.CrowdinLocalization.CrowdinLocalizationProvider`  
`public abstract class CrowdinLocalizationProvider : LocalizationProvider`  
_public; L113-528_
- inherits: `LocalizationProvider`
- L115-127 _public ctor_ `public CrowdinLocalizationProvider(LocalizationProviderArgs InArgs) : base(InArgs)`
- L129-171 _public method_ `public async override Task InitializeProjectWithLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectImportInfo)`
- L173-190 _public method_ `public async override Task DownloadProjectFromLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectImportInfo)`
- L192-291 _private method_ `private async Task DownloadLatestPOFile(string Culture, string Platform, ProjectImportExportInfo ProjectImportInfo)`
- L293-306 _private* method_ `int? GetFileId(PagedData<FileInfoData> FileList, string File)`
- L308-333 _public method_ `public async override Task UploadProjectToLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectExportInfo)`
- L335-403 _private method_ `private async Task UploadLatestPOFile(string Culture, string Platform, ProjectImportExportInfo ProjectExportInfo)`
- L405-421 _private method_ `private string GetCrowdinFilename(string BaseFilename, string Platform)`
- L424-459 _private method_ `private async Task<T> CrowdInRequest<T>(HttpMethod Method, string Url, object Content) where T : class`
- L461-488 _private method_ `private async Task<StorageResponse> CrowdInStorage(string Url, string CrowdinFilename, string LocalFilePath)`
- L490-499 _protected method_ `virtual protected string ConvertEpicCultureToCowdinLanguageCode(string Culture)`
- L501-510 _private* method_ `string SlugBranchName(string BranchName)`
- L512 _protected field_ `protected CrowdinConfig Config`
- L513 _protected field_ `protected HttpClient Client`
- L514 _protected field_ `protected HashSet<string> MissingFiles`
- L516 _private field_ `private JsonSerializerOptions JsonOptions`
- L517 _private field_ `private int? BranchId`
- L521 _private field_ `private static Dictionary<string, string> CultureMappings = ...`
- L521 _private field_ `private static Dictionary< CultureMappings = new Dictionary<string, string> { { "es-419", "es-US" }, { "zh-Hans", "zh-CN" }, { "zh-Hant", "zh-TW" }, }`

### `Source/Programs/AutomationTool/CrowdinLocalization/Properties/AssemblyInfo.cs` (CrowdinLocalization.Automation)
_(no declarations)_

