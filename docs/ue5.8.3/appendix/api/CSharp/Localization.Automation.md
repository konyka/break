# CSharp / Localization.Automation

- project root: `Source/Programs/AutomationTool/Localization`
- files: 12; symbols: 237
- symbol kinds: class=27, const=1, ctor=11, enum=1, enumerator=3, field=26, method=72, property=95, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Localization/LocalizationConfigFile.cs` (Localization.Automation)


#### enum `EpicGames.Localization.LocalizationConfigFileFormat`  
`public enum LocalizationConfigFileFormat`  
_public; L13-20_
- L15 _public* enumerator_ `LegacyMonolithic`
- L16 _public* enumerator_ `Modular`
- L19 _public* enumerator_ `Latest = Modular`

#### class `EpicGames.Localization.LocalizationConfigFile`  
`public class LocalizationConfigFile`  
_public; L22-145_
- L24 _private field_ `private readonly ConfigFile _configFile`
- L25 _public property_ `public string Name { get; set; }`
- L26-29 _public ctor_ `public LocalizationConfigFile()`
- L31-35 _public ctor_ `public LocalizationConfigFile(string fileName)`
- L37-41 _private ctor_ `private LocalizationConfigFile(ConfigFile configFile, string fileName)`
- L43-47 _public method_ `public LocalizationConfigFileSection FindOrAddSection(string sectionName)`
- L49-66 _public method_ `public static LocalizationConfigFile Load(string filePath)`
- L68-90 _private method_ `private LocalizationConfigFile DeepCopy()`
- L92-120 _public method_ `public LocalizationConfigFile ReplacePlaceHolders(Dictionary<string, string> replacements)`
- L122-125 _public method_ `public bool IsEmpty()`
- L129-144 _public method_ `public void Write(FileReference destinationFilePath)`

#### class `EpicGames.Localization.LocalizationConfigFileSection`  
`public class LocalizationConfigFileSection`  
_public; L147-186_
- L149 _private field_ `private readonly ConfigFileSection _configFileSection`
- L151-154 _public ctor_ `public LocalizationConfigFileSection(ConfigFileSection configFileSection)`
- L156-162 _public method_ `public void AddValue(string key, bool value)`
- L164-170 _public method_ `public void AddValue(string key, string value)`
- L172-185 _public method_ `public void AddValues(string key, string[] values)`

### `Source/Programs/AutomationTool/Localization/LocalizationConfigFileBuilder.cs` (Localization.Automation)


#### class `EpicGames.Localization.LocalizationConfigFileBuilder`  
`public class LocalizationConfigFileBuilder`  
_public; L5-153_
- L7 _private field_ `private LocalizationConfigFile _configFile`
- L8 _private field_ `private int _gatherTextStepCount`
- L10-14 _public ctor_ `public LocalizationConfigFileBuilder(string localizationConfigFileName)`
- L16-32 _public method_ `public void AddCommonSettingsSection(CommonSettingsParams commonSettings)`
- L34-44 _public method_ `public void AddGatherTextFromSourceSection(GatherTextFromSourceParams gatherTextParams)`
- L46-61 _public method_ `public void AddGatherTextFromAssetsSection(GatherTextFromAssetsParams gatherTextParams)`
- L63-84 _public method_ `public void AddGatherTextFromMetadataSection(GatherTextFromMetaDataParams gatherTextParams)`
- L86-92 _public method_ `public void AddGenerateGatherManifestSection(GenerateGatherManifestParams generateGatherManifestParams)`
- L94-100 _public method_ `public void AddGenerateGatherArchiveSection(GenerateGatherArchiveParams generateGatherArchiveParams)`
- L102-113 _public method_ `public void AddExportPortableObjectFilesSection(ExportPortableObjectFilesParams exportParams)`
- L115-124 _public method_ `public void AddImportPortableObjectFilesSection(ImportPortableObjectFilesParams importParams)`
- L126-132 _public method_ `public void AddGenerateTextLocalizationResourceSection(GenerateTextLocalizationResourceParams localizationResourceParams)`
- L134-147 _public method_ `public void AddGenerateTextLocalizationReportSection(GenerateTextLocalizationReportParams textReportParams)`
- L149-152 _public method_ `public LocalizationConfigFile Get()`

### `Source/Programs/AutomationTool/Localization/LocalizationConfigFileGenerator.cs` (Localization.Automation)


#### class `EpicGames.Localization.LocalizationConfigFileGeneratorParams`  
`public class LocalizationConfigFileGeneratorParams`  
_public; L12-17_
- L14 _public property_ `public LocalizationTargetDescriptorLoadingPolicy LoadingPolicy { get; set; }`
- L15 _public property_ `public string LocalizationTargetName { get; set; }`
- L16 _public property_ `public string LocalizationTargetRootDirectory { get; set; }`

#### class `EpicGames.Localization.LocalizationConfigFileGenerator`  
`public abstract class LocalizationConfigFileGenerator`  
_public; L19-34_
- L21-30 _public method_ `public static LocalizationConfigFileGenerator GetGeneratorForFileFormat(LocalizationConfigFileFormat fileFormat)`
- L32 _public method_ `public abstract List<LocalizationConfigFile> GenerateDefaultSettingsConfigFiles(LocalizationConfigFileGeneratorParams generatorParams)`
- L33 _public method_ `public abstract List<LocalizationConfigFile> GenerateConfigFilesFromTemplate(LocalizationConfigFileGeneratorParams generatorParams, List<LocalizationConfigFile> templateFiles)`

#### class `EpicGames.Localization.ModularLocalizationConfigFileGenerator`  
`public class ModularLocalizationConfigFileGenerator : LocalizationConfigFileGenerator`  
_public; L36-160_
- inherits: `LocalizationConfigFileGenerator`
- L38-47 _public method_ `public override List<LocalizationConfigFile> GenerateDefaultSettingsConfigFiles(LocalizationConfigFileGeneratorParams generatorParams)`
- L49-79 _public method_ `public override List<LocalizationConfigFile> GenerateConfigFilesFromTemplate(LocalizationConfigFileGeneratorParams generatorParams, List<LocalizationConfigFile> templateFiles)`
- L81-112 _private method_ `private LocalizationConfigFile GenerateLocalizationGatherConfigFile(LocalizationConfigFileGeneratorParams generatorParam)`
- L114-123 _private method_ `private LocalizationConfigFile GenerateLocalizationExportConfigFile(LocalizationConfigFileGeneratorParams generatorParams)`
- L125-134 _private method_ `private LocalizationConfigFile GenerateLocalizationImportConfigFile(LocalizationConfigFileGeneratorParams generatorParams)`
- L136-145 _private method_ `private LocalizationConfigFile GenerateLocalizationCompileConfigFile(LocalizationConfigFileGeneratorParams generatorParams)`
- L147-159 _private method_ `private LocalizationConfigFile GenerateLocalizationGenerateReportsConfigFile(LocalizationConfigFileGeneratorParams generatorParams)`

### `Source/Programs/AutomationTool/Localization/LocalizationConfigFileParams.cs` (Localization.Automation)


#### class `EpicGames.Localization.CommonSettingsParams`  
`public class CommonSettingsParams`  
_public; L9-47_
- L11 _public property_ `public List<string> manifestDependencies { get; set; }`
- L12 _public property_ `public string SourcePath { get; set; }`
- L13 _public property_ `public string DestinationPath { get; set; }`
- L14 _public property_ `public string ManifestName { get; set; }`
- L15 _public property_ `public string ArchiveName { get; set; }`
- L16 _public property_ `public string ResourceName { get; set; }`
- L17 _public property_ `public string PortableObjectName { get; set; }`
- L18 _public property_ `public bool bSkipSourceCheck { get; set; }`
- L19 _public property_ `public bool bValidateFormatPatterns { get; set; }`
- L20 _public property_ `public bool bValidateSafeWhitespace { get; set; }`
- L21 _public property_ `public bool bValidateRichTextTags { get; set; }`
- L22 _public property_ `public string NativeCulture { get; set; }`
- L23 _public property_ `public List<string> CulturesToGenerate { get; set; }`
- L25-46 _public method_ `public static CommonSettingsParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.GatherTextFromSourceParams`  
`public class GatherTextFromSourceParams`  
_public; L49-68_
- L51 _public property_ `public string CommandletClass { get; }`
- L52 _public property_ `public List<string> SearchDirectoryPaths { get; set; }`
- L53 _public property_ `public List<string> ExcludePathFilters { get; set; }`
- L54 _public property_ `public List<string> FileNameFilters { get; set; }`
- L55 _public property_ `public bool bShouldGatherFromEditorOnlyData { get; set; }`
- L57-67 _public method_ `public static GatherTextFromSourceParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.GatherTextFromAssetsParams`  
`public class GatherTextFromAssetsParams`  
_public; L70-102_
- L72 _public property_ `public string CommandletClass { get; }`
- L73 _public property_ `public List<string> IncludePathFilters { get; set; }`
- L74 _public property_ `public List<string> ExcludePathFilters { get; set; }`
- L75 _public property_ `public List<string> PackageFileNameFilters { get; set; }`
- L76 _public property_ `public List<string> CollectionFilters { get; set; }`
- L77 _public property_ `public List<string> WorldCollectionFilters { get; set; }`
- L78 _public property_ `public bool bShouldExcludeDerivedClasses { get; set; }`
- L79 _public property_ `public bool bShouldGatherFromEditorOnlyData { get; set; }`
- L80 _public property_ `public bool bSkipGatherCache { get; set; }`
- L82-101 _public method_ `public static GatherTextFromAssetsParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.GatherTextFromMetaDataParams`  
`public class GatherTextFromMetaDataParams`  
_public; L104-144_
- L106 _public property_ `public string CommandletClass { get; }`
- L107 _public property_ `public List<string> ModulesToPreload { get; set; }`
- L108 _public property_ `public List<string> IncludePathFilters { get; set; }`
- L109 _public property_ `public List<string> ExcludePathFilters { get; set; }`
- L110 _public property_ `public List<string> FieldTypesToInclude { get; set; }`
- L111 _public property_ `public List<string> FieldOwnerTypesToInclude { get; set; }`
- L112 _public property_ `public List<string> InputKeys { get; set; }`
- L113 _public property_ `public List<string> OutputKeys { get; set; }`
- L114 _public property_ `public List<string> InputNamespaceses { get; set; }`
- L115 _public property_ `public List<string> OutputNamespaces { get; set; }`
- L116 _public property_ `public bool bShouldGatherFromEditorOnlyData { get; set; }`
- L118-143 _public method_ `public static GatherTextFromMetaDataParams CreateDefault(string localizationTargetRootDirectory, LocalizationTargetDescriptorLoadingPolicy localizationPolicy)`

#### class `EpicGames.Localization.GenerateGatherManifestParams`  
`public class GenerateGatherManifestParams`  
_public; L146-155_
- L148 _public property_ `public string CommandletClass { get; }`
- L149-154 _public method_ `public static GenerateGatherManifestParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.GenerateGatherArchiveParams`  
`public class GenerateGatherArchiveParams`  
_public; L157-169_
- L159 _public property_ `public string CommandletClass { get; }`
- L160 _public property_ `public bool bPurgeOldEmptyEntries { get; set; }`
- L162-168 _public method_ `public static GenerateGatherArchiveParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.ImportPortableObjectFilesParams`  
`public class ImportPortableObjectFilesParams`  
_public; L171-186_
- L173 _public property_ `public string CommandletClass { get; }`
- L174 _public property_ `public bool bImportLoc { get; }`
- L175 _public property_ `public string LocalizedTextCollapseMode { get; set; }`
- L176 _public property_ `public string POFormat { get; set; }`
- L178-185 _public method_ `public static ImportPortableObjectFilesParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.GenerateTextLocalizationResourceParams`  
`public class GenerateTextLocalizationResourceParams`  
_public; L188-195_
- L190 _public property_ `public string CommandletClass { get; }`
- L191-194 _public method_ `public static GenerateTextLocalizationResourceParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.ExportPortableObjectFilesParams`  
`public class ExportPortableObjectFilesParams`  
_public; L197-215_
- L199 _public property_ `public string CommandletClass { get; }`
- L200 _public property_ `public bool bExportLoc { get; }`
- L201 _public property_ `public string LocalizedTextCollapseMode { get; set; }`
- L202 _public property_ `public string POFormat { get; set; }`
- L203 _public property_ `public bool bShouldPersistCommentsOnExport { get; set; }`
- L204 _public property_ `public bool bShouldAddSourceLocationsAsComments { get; set; }`
- L206-214 _public method_ `public static ExportPortableObjectFilesParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

#### class `EpicGames.Localization.GenerateTextLocalizationReportParams`  
`public class GenerateTextLocalizationReportParams`  
_public; L217-235_
- L219 _public property_ `public string CommandletClass { get; }`
- L220 _public property_ `public string DestinationPath { get; set; }`
- L221 _public property_ `public bool bWordCountReport { get; set; }`
- L222 _public property_ `public string WordCountReportName { get; set; }`
- L223 _public property_ `public bool bConflictReport { get; set; }`
- L224 _public property_ `public string ConflictReportName { get; set; }`
- L226-234 _public method_ `public static GenerateTextLocalizationReportParams CreateDefault(string localizationTargetName, string localizationTargetRootDirectory)`

### `Source/Programs/AutomationTool/Localization/LocalizationConstants.cs` (Localization.Automation)


#### class `EpicGames.Localization.LocalizationFileExtensions`  
`public static class LocalizationFileExtensions`  
_public; L5-13_
- L7 _public property_ `public static string LegacyMonolithicLocalizationConfigFileExtension { get; }`
- L8 _public property_ `public static string ModularLocalizationConfigFileExtension { get; }`
- L9 _public property_ `public static string ArchiveFileExtension { get; }`
- L10 _public property_ `public static string ManifestFileExtension { get; }`
- L11 _public property_ `public static string PortableObjectFileExtension { get; }`
- L12 _public property_ `public static string LocalizationResourceFileExtension { get; }`

#### class `EpicGames.Localization.ModularLocalizationConfigFileSuffixes`  
`public static class ModularLocalizationConfigFileSuffixes`  
_public; L15-22_
- L17 _public property_ `public static string GatherSuffix { get; }`
- L18 _public property_ `public static string ExportSuffix { get; }`
- L19 _public property_ `public static string ImportSuffix { get; }`
- L20 _public property_ `public static string CompileSuffix { get; }`
- L21 _public property_ `public static string GenerateReportsSuffix { get; }`

### `Source/Programs/AutomationTool/Localization/LocalizationProvider.cs` (Localization.Automation)


#### class `EpicGames.Localization.ProjectImportExportInfo`  
`public class ProjectImportExportInfo`  
_public; L16-74_
- L18-27 _public ctor_ `public ProjectImportExportInfo(string InDestinationPath, string InManifestName, string InArchiveName, string InPortableObjectName, string InNativeCulture, IReadOnlyList<string> InCulturesToGenerate, bool InUseCultureDirectory)`
- L30 _public property_ `public string DestinationPath { get; set; }`
- L33 _public property_ `public string ManifestName { get; set; }`
- L36 _public property_ `public string ArchiveName { get; set; }`
- L39 _public property_ `public string PortableObjectName { get; set; }`
- L42 _public property_ `public string NativeCulture { get; set; }`
- L45 _public property_ `public IReadOnlyList<string> CulturesToGenerate { get; set; }`
- L48 _public property_ `public bool bUseCultureDirectory { get; set; }`
- L51 _public property_ `public IReadOnlyList<string> SplitPlatformNames { get; set; }`
- L54 _public const_ `public const string PlatformLocalizationFolderName = "Platforms"`
- L56-73 _public method_ `public void CalculateSplitPlatformNames(string RootWorkingDirectory)`

#### class `EpicGames.Localization.ProjectStepInfo`  
`public class ProjectStepInfo`  
_public; L76-89_
- L78-82 _public ctor_ `public ProjectStepInfo(string InName, string InLocalizationConfigFile)`
- L85 _public property_ `public string Name { get; set; }`
- L88 _public property_ `public string LocalizationConfigFile { get; set; }`

#### class `EpicGames.Localization.ProjectInfo`  
`public class ProjectInfo`  
_public; L91-125_
- L93-99 _public ctor_ `public ProjectInfo(string InProjectName, IReadOnlyList<ProjectStepInfo> InLocalizationSteps, ProjectImportExportInfo InImportInfo, ProjectImportExportInfo InExportInfo)`
- L101-112 _public method_ `public List<string> GetConfigFilesToRun(List<string> RequestedLocalizationStepNames)`
- L115 _public property_ `public string ProjectName { get; set; }`
- L118 _public property_ `public IReadOnlyList<ProjectStepInfo> LocalizationSteps { get; set; }`
- L121 _public property_ `public ProjectImportExportInfo ImportInfo { get; set; }`
- L124 _public property_ `public ProjectImportExportInfo ExportInfo { get; set; }`

#### class `EpicGames.Localization.LocalizationProvider`  
`public abstract class LocalizationProvider`  
_public; L127-256_
- L138-147 _public ctor_ `public LocalizationProvider(LocalizationProviderArgs InArgs)`
- L149-152 _public method_ `public virtual string GetLocalizationProviderId()`
- L154-157 _public method_ `public async virtual Task InitializeProjectWithLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectImportInfo)`
- L159-162 _public method_ `public async virtual Task DownloadProjectFromLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectImportInfo)`
- L164-167 _public method_ `public async virtual Task UploadProjectToLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectExportInfo)`
- L169-246 _public method_ `public static LocalizationProvider GetLocalizationProvider(string InLocalizationProviderId, LocalizationProvider.LocalizationProviderArgs InLocalizationProviderArgs)`
- L248 _protected field_ `protected string RootWorkingDirectory`
- L249 _protected field_ `protected string LocalizationBranchName`
- L250 _protected field_ `protected string RemoteFilenamePrefix`
- L251 _protected field_ `protected bool bUploadAllCultures`
- L252 _protected field_ `protected BuildCommand Command`
- L253 _protected field_ `protected int PendingChangeList`
- L255 _private field_ `private static Dictionary<string, Type> CachedLocalizationProviderTypes`
- L255 _private field_ `private static Dictionary< CachedLocalizationProviderTypes`

#### struct `EpicGames.Localization.LocalizationProvider.LocalizationProviderArgs`  
`public struct LocalizationProviderArgs`  
_public; L129-136_
- L131 _public field_ `public string RootWorkingDirectory`
- L132 _public field_ `public string RootLocalizationTargetDirectory`
- L133 _public field_ `public string RemoteFilenamePrefix`
- L134 _public field_ `public BuildCommand Command`
- L135 _public field_ `public int PendingChangeList`

### `Source/Programs/AutomationTool/Localization/LocalizationTargetEditor/Commands/LocalizationTargetCommand.cs` (Localization.Automation)


#### class `EpicGames.Localization.LocalizationTargetCommand`  
`public abstract class LocalizationTargetCommand`  
_public; L14-109_
- L16 _protected field_ `protected static BuildCommand _commandLineHelper`
- L17 _private field_ `private static Dictionary<string, LocalizationTargetCommand> _nameToLocalizationTargetCommandMap = ...`
- L17 _private field_ `private static Dictionary< _nameToLocalizationTargetCommandMap = new Dictionary<string, LocalizationTargetCommand>()`
- L19 _public property_ `public string Name { get; set; }`
- L20 _public property_ `public string DisplayName { get; set; }`
- L21 _public property_ `public bool bIsExecutingInPreview { get; set; }`
- L23-39 _private* ctor_ `static LocalizationTargetCommand()`
- L41-44 _public method_ `public static void Initialize(BuildCommand commandLineHelper)`
- L46-51 _public method_ `public static LocalizationTargetCommand GetLocalizationTargetCommandFromName(string commandName)`
- L53-57 _protected method_ `protected virtual bool ParseCommandLine()`
- L59 _public method_ `public abstract bool Execute()`
- L61-65 _public method_ `public void PrintHelpText()`
- L67-74 _public method_ `public virtual string GetHelpText()`
- L80-83 _protected method_ `protected virtual void BuildHelpDescription(StringBuilder builder)` — Buils the description portion of the help text. Concrete child classes of LocalizationTargetCommand should override this function
- L89-93 _protected method_ `protected virtual void BuildHelpArguments(StringBuilder builder)` — Builds the arguments portion of the help text explaining what each parameter of the command does. Child classes should override this function
- L100-103 _protected method_ `protected virtual void BuildHelpUsage(StringBuilder builder)` — Builds the usage portion of the help text. Useres should override this function and call teh base implementation and provide usage scenarios and the associated usage syntax for each scenario.
- L105-108 _public method_ `public static List<LocalizationTargetCommand> GetAllCommands()`

### `Source/Programs/AutomationTool/Localization/LocalizationTargetEditor/Commands/NewPluginLocalizationTargetCommand.cs` (Localization.Automation)


#### class `EpicGames.Localization.NewPluginLocalizationTargetCommand`  
`public class NewPluginLocalizationTargetCommand : PluginLocalizationTargetCommand`  
_public; L15-260_
- inherits: `PluginLocalizationTargetCommand`
- L17 _private field_ `private LocalizationTargetDescriptorLoadingPolicy _loadingPolicy`
- L18 _private field_ `private LocalizationConfigGenerationPolicy _configGenerationPolicy`
- L19 _private field_ `private string _localizationTargetNameSuffix = ""`
- L20 _private field_ `private LocalizationConfigFileFormat _fileFormat = LocalizationConfigFileFormat.Latest`
- L21 _private field_ `private List<string> _filesToAdd = new List<string>()`
- L22 _private field_ `private List<string> _filesToEdit = new List<string>()`
- L24-28 _public ctor_ `public NewPluginLocalizationTargetCommand()`
- L30-36 _protected method_ `protected override void BuildHelpDescription(StringBuilder builder)`
- L38-45 _protected method_ `protected override void BuildHelpArguments(StringBuilder builder)`
- L47-54 _protected method_ `protected override void BuildHelpUsage(StringBuilder builder)`
- L56-78 _protected method_ `protected override bool ParseCommandLine()`
- L80-136 _public method_ `public override bool Execute()`
- L138-171 _private method_ `private void GeneratePluginLocalizationConfigFiles(PluginInfo pluginInfo, string localizationTargetName, string localizationTargetRootDirectory)`
- L173-213 _private method_ `private void UpdatePluginLocalizationTargetDescriptor(PluginInfo pluginInfo, string localizationTargetName)`
- L215-259 _private method_ `private void CreatePerforceChangeList()`

### `Source/Programs/AutomationTool/Localization/LocalizationTargetEditor/Commands/PluginLocalizationTargetCommand.cs` (Localization.Automation)


#### class `EpicGames.Localization.PluginLocalizationTargetCommand`  
`public abstract class PluginLocalizationTargetCommand : LocalizationTargetCommand`  
_public; L15-93_
- inherits: `LocalizationTargetCommand`
- L17 _public property_ `public string UERootDirectory { get; set; }`
- L18 _public property_ `public string UEProjectDirectory { get; set; }`
- L19 _public property_ `public string UEProjectName { get; set; }`
- L21 _public property_ `public HashSet<string> IncludePlugins { get; set; }`
- L22 _public property_ `public HashSet<string> ExcludePlugins { get; set; }`
- L24-36 _protected method_ `protected override void BuildHelpArguments(StringBuilder builder)`
- L38-92 _protected method_ `protected override bool ParseCommandLine()`

### `Source/Programs/AutomationTool/Localization/LocalizationTargetEditor/LocalizationTargetEditor.Automation.cs` (Localization.Automation)


#### class `EpicGames.Localization.LocalizationTargetEditor`  
`class LocalizationTargetEditor : BuildCommand`  
_internal*; L12-53_
- attrs: `[Help("Allows users to create, update, delete or query localization targets for the Engine or projects. This command has sub-commands and more info for each command can be retrieved with the -Info flag.")] [Help("Command", "The sub-command you want to run. For a full list of valid command, use LocalizationTargetEditor -Info")] [Help("Info", "An optional flag that can be passed to any sub-command. `
- inherits: `BuildCommand`
- L14-52 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Localization/LocalizationUtilities.cs` (Localization.Automation)


#### class `EpicGames.Localization.LocalizationUtilities`  
`public static class LocalizationUtilities`  
_public; L10-90_
- L12-38 _public method_ `public static HashSet<string> GetPluginNamesUnderDirectory(string PluginDirectoryPath, string PluginRoot, PluginType Type)`
- L40-51 _public method_ `public static string[] GetModularConfigSuffixes()`
- L53-70 _public method_ `public static bool IsModularLocalizationConfigFile(String file)`
- L72-89 _public method_ `public static string GetModularLocalizationConfigSuffix(String file)`

### `Source/Programs/AutomationTool/Localization/Properties/AssemblyInfo.cs` (Localization.Automation)
_(no declarations)_

