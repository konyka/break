# CSharp / OneSkyLocalization.Automation

- project root: `Source/Programs/AutomationTool/OneSkyLocalization`
- files: 3; symbols: 26
- symbol kinds: class=3, ctor=2, field=7, method=14
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/OneSkyLocalization/OneSkyConfigHelper.cs` (OneSkyLocalization.Automation)


#### class `EpicGames.OneSkyLocalization.Config.OneSkyConfigHelper`  
`public class OneSkyConfigHelper`  
_public; L18-62_
- desc: Class for retrieving OneSky localization configuration data
- L21 _private field_ `private static Dictionary<string, OneSkyConfigData> Configs`
- L21 _private field_ `private static Dictionary< Configs`
- L23-61 _public method_ `public static OneSkyConfigData Find(string ConfigName)`

#### class `EpicGames.OneSkyLocalization.Config.OneSkyConfigData`  
`public class OneSkyConfigData`  
_public; L67-86_
- desc: Class for storing OneSky Localization configuration data
- L69-74 _public ctor_ `public OneSkyConfigData(string InName, string InApiKey, string InApiSecret)`
- L76 _public field_ `public string Name`
- L77 _public field_ `public string ApiKey`
- L78 _public field_ `public string ApiSecret`
- L80-85 _public method_ `public void SpewValues()`

### `Source/Programs/AutomationTool/OneSkyLocalization/OneSkyLocalizationProvider.cs` (OneSkyLocalization.Automation)


#### class `EpicGames.OneSkyLocalization.OneSkyLocalizationProvider`  
`public class OneSkyLocalizationProvider : LocalizationProvider`  
_public; L17-349_
- attrs: `[Help("OneSkyConfigName", "Name of the config data to use (see OneSkyConfigHelper).")] [Help("OneSkyProjectGroupName", "Name of the project group in OneSky.")]`
- inherits: `LocalizationProvider`
- L19-37 _public ctor_ `public OneSkyLocalizationProvider(LocalizationProviderArgs InArgs) : base(InArgs)`
- L39-42 _public method_ `public static string StaticGetLocalizationProviderId()`
- L44-47 _public method_ `public override string GetLocalizationProviderId()`
- L49-59 _public method_ `public async override Task DownloadProjectFromLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectImportInfo)`
- L61-90 _private method_ `private void DownloadLatestPOFiles(Project OneSkyProject, string Platform, ProjectImportExportInfo ProjectImportInfo)`
- L92-119 _private method_ `private UploadedFile.ExportTranslationState ExportOneSkyTranslationWithRetry(UploadedFile OneSkyFile, string Culture, MemoryStream MemoryStream)`
- L121-197 _private method_ `private void ExportOneSkyFileToDirectory(UploadedFile OneSkyFile, DirectoryInfo DestinationDirectory, string DestinationFilename, IEnumerable<string> Cultures, bool bUseCultureDirectory)`
- L199-228 _public method_ `public async override Task UploadProjectToLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectExportInfo)`
- L230-257 _private method_ `private UploadedFile UploadOneSkyTranslationWithRetry(OneSky.Project OneSkyProject, string OneSkyFileName, string Culture, FileStream FileStream)`
- L259-294 _private method_ `private void UploadFileToOneSky(OneSky.Project OneSkyProject, string Culture, string Platform, ProjectImportExportInfo ProjectExportInfo)`
- L296-307 _private method_ `private ProjectGroup GetOneSkyProjectGroup(string ProjectGroupName)`
- L309-322 _private method_ `private OneSky.Project GetOneSkyProject(string ProjectName, string ProjectDescription = "")`
- L324-345 _private method_ `private string GetOneSkyFilename(string BaseFilename, string Platform)`
- L347 _private field_ `private OneSkyService OneSkyService`
- L348 _private field_ `private ProjectGroup OneSkyProjectGroup`

### `Source/Programs/AutomationTool/OneSkyLocalization/Properties/AssemblyInfo.cs` (OneSkyLocalization.Automation)
_(no declarations)_

