# CSharp / SmartlingLocalization.Automation

- project root: `Source/Programs/AutomationTool/SmartlingLocalization`
- files: 2; symbols: 43
- symbol kinds: class=7, ctor=1, field=9, method=15, property=11
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/SmartlingLocalization/Properties/AssemblyInfo.cs` (SmartlingLocalization.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/SmartlingLocalization/SmartlingLocalizationProvider.cs` (SmartlingLocalization.Automation)


#### class `EpicGames.SmartlingLocalization.SmartlingConfig`  
`public class SmartlingConfig`  
_public; L26-31_
- L28 _public field_ `public string ProjectId`
- L29 _public field_ `public string UserId`
- L30 _public field_ `public string UserSecret`

#### class `EpicGames.SmartlingLocalization.SmartlingResponseEnvelope`  
`public class SmartlingResponseEnvelope<T>`  
_public; L34-37_
- L36 _public property_ `public T Response { get; set; }`

#### class `EpicGames.SmartlingLocalization.SmartlingDataEnvelope`  
`public class SmartlingDataEnvelope<T>`  
_public; L39-42_
- L41 _public property_ `public T Data { get; set; }`

#### class `EpicGames.SmartlingLocalization.SmartlingAuthenticationToken`  
`public class SmartlingAuthenticationToken`  
_public; L44-52_
- L46 _public property_ `public string AccessToken { get; set; }`
- L47 _public property_ `public int ExpiresIn { get; set; }`
- L48 _public property_ `public int RefreshExpiresIn { get; set; }`
- L49 _public property_ `public string RefreshToken { get; set; }`
- L50 _public property_ `public string TokenType { get; set; }`
- L51 _public property_ `public DateTime LastSuccessfulUpdateTime { get; set; }`

#### class `EpicGames.SmartlingLocalization.SmartlingRequestError`  
`public class SmartlingRequestError`  
_public; L54-63_
- L56 _public property_ `public string Key { get; set; }`
- L57 _public property_ `public string Message { get; set; }`
- L59-62 _public method_ `public override string ToString()`

#### class `EpicGames.SmartlingLocalization.SmartlingRequestErrorsEnvelope`  
`public class SmartlingRequestErrorsEnvelope`  
_public; L65-68_
- L67 _public property_ `public List<SmartlingRequestError> Errors { get; set; }`

#### class `EpicGames.SmartlingLocalization.SmartlingLocalizationProvider`  
`public abstract class SmartlingLocalizationProvider : LocalizationProvider`  
_public; L70-609_
- inherits: `LocalizationProvider`
- L72-85 _public ctor_ `public SmartlingLocalizationProvider(LocalizationProviderArgs InArgs) : base(InArgs)`
- L92-115 _public method_ `public async override Task DownloadProjectFromLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectImportInfo)`
- L117-134 _private method_ `private async Task DownloadLatestPOFileAndLog(string EpicLocale, string Platform, ProjectImportExportInfo ProjectImportInfo)`
- L136-283 _private method_ `private async Task<List<string>> DownloadLatestPOFile(string EpicLocale, string Platform, ProjectImportExportInfo ProjectImportInfo)`
- L285-295 _private method_ `private async Task AppendRequestErrorsToLog(HttpResponseMessage Response, List<string> Logs)`
- L297-314 _public method_ `public async override Task UploadProjectToLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectExportInfo)`
- L316-335 _private method_ `private async Task UploadLatestPOFileAndLog(string EpicLocale, string Platform, ProjectImportExportInfo ProjectExportInfo)`
- L337-423 _private method_ `private async Task<List<string>> UploadLatestPOFile(string EpicLocale, string Platform, ProjectImportExportInfo ProjectExportInfo)`
- L426-437 _protected method_ `virtual protected Dictionary<string,string> GetEpicLocaleToSmartlingLocaleDictionary()`
- L439-448 _private method_ `private string ConvertEpicLocaleToSmartlingLocale(string EpicLocale)`
- L450-466 _private method_ `private string GetSmartlingFilename(string BaseFilename, string Platform)`
- L468-480 _private method_ `private string GetSmartlingFileUri(string SmartlingFilename)`
- L482-522 _private method_ `private async Task GetAuthenticationToken(List<string> Logs)`
- L529-562 _private method_ `private async Task RequestAuthenticationToken(List<string> Logs)` — Requests a new authentication token from the Smartling endpoints. This call is not threadsafe and should ONLY be used from GetAuthenticationToken() where the AuthenticationToken instane is protected by syncrhonization primitives. Do not call this function directly.
- L569-601 _private method_ `private async Task RefreshAuthenticationToken(List<string> Logs)` — Refreshes the authentication token using the Smarglin endpoint. This function is not thread safe and should ONLY be called by GetAuthenticationToken() where synchronization is used to protect the AuthenticationToken instance. Do not call this function directly, use GetAuthenticationToken() isntead.
- L603 _protected field_ `protected SmartlingConfig Config`
- L604 _protected field_ `protected HttpClient Client`
- L605 _private field_ `private JsonSerializerOptions JsonOptions`
- L606 _private field_ `private SmartlingAuthenticationToken AuthenticationToken`
- L607 _private field_ `private readonly SemaphoreSlim AuthenticationTokenSemaphore = new SemaphoreSlim(1, 1)`
- L608 _private field_ `private readonly Object LoggerLock = new object()`
