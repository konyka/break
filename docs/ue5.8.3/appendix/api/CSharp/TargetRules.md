# CSharp / TargetRules

- project root: `-`
- files: 93; symbols: 218
- symbol kinds: class=95, const=1, ctor=96, delegate=2, field=13, method=11
- access marked `*` is implicit (not written in source)

### `Source/Developer/ChaosTestHarness/ChaosTestHarness.Target.cs` (TargetRules)


#### class `ChaosTestHarnessTarget` : `TestTargetRules`  
`public class ChaosTestHarnessTarget : TestTargetRules`  
_L6-22_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L8 _ctor_ `public ChaosTestHarnessTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: CATCH_CONFIG_ENABLE_BENCHMARKING=1
  - L10 `bCompileAgainstEngine = true`
  - L11 `bCompileAgainstCoreUObject = true`
  - L12 `bCompileAgainstApplicationCore = true`
  - L13 `bMockEngineDefaults = true`
  - L14 `bUsePlatformFileStub = true`
  - L16 `bWithLowLevelTestsOverride = true`
  - L20 `bWarningsAsErrors = true`

### `Source/Programs/BaseTextureBuildWorker/BaseTextureBuildWorker.Target.cs` (TargetRules)


#### class `BaseTextureBuildWorkerTarget` : `TextureBuildWorkerTarget`  
`public class BaseTextureBuildWorkerTarget : TextureBuildWorkerTarget`  
_L7-13_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public BaseTextureBuildWorkerTarget(TargetInfo Target) : base(Target)`
  - L11 `LaunchModuleName = "BaseTextureBuildWorker"`

### `Source/Programs/BenchmarkTool/BenchmarkTool.Target.cs` (TargetRules)


#### class `BenchmarkToolTarget` : `TargetRules`  
`public class BenchmarkToolTarget : TargetRules`  
_L7-23_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public BenchmarkToolTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LaunchModuleName = "BenchmarkTool"`
  - L16 `bBuildDeveloperTools = false`
  - L17 `bBuildWithEditorOnlyData = false`
  - L18 `bCompileAgainstEngine = false`
  - L19 `bCompileAgainstCoreUObject = false`
  - L20 `bCompileAgainstApplicationCore = false`
  - L21 `bIsBuildingConsoleApplication = true`

### `Source/Programs/BlankProgram/BlankProgram.Target.cs` (TargetRules)


#### class `BlankProgramTarget` : `TargetRules`  
`public class BlankProgramTarget : TargetRules`  
_L7-40_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L9 _ctor_ `public BlankProgramTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L14 `LinkType = TargetLinkType.Monolithic`
  - L15 `LaunchModuleName = "BlankProgram"`
  - L18 `bBuildDeveloperTools = false`
  - L23 `bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && bDebugOrDevelopment`
  - L26 `bCompileAgainstEngine = false`
  - L27 `bCompileAgainstCoreUObject = false`
  - L28 `bCompileAgainstApplicationCore = false`
  - L29 `bCompileICU = false`
  - L38 `bIsBuildingConsoleApplication = true`

### `Source/Programs/BreakpadSymbolEncoder/BreakpadSymbolEncoder.Target.cs` (TargetRules)


#### class `BreakpadSymbolEncoderTarget` : `TargetRules`  
`public class BreakpadSymbolEncoderTarget : TargetRules`  
_L7-33_
- attrs: `[SupportedPlatforms("Linux", "Win64")]`
- L9 _ctor_ `public BreakpadSymbolEncoderTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "BreakpadSymbolEncoder"`
  - L16 `UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L19 `bBuildDeveloperTools = false`
  - L22 `bCompileAgainstEngine = false`
  - L23 `bCompileAgainstCoreUObject = false`
  - L26 `bUseLoggingInShipping = true`
  - L29 `bIsBuildingConsoleApplication = true`
  - L31 `bUseUnityBuild = false`

### `Source/Programs/BuildPatchTool/BuildPatchTool.Target.cs` (TargetRules)


#### class `BuildPatchToolTarget` : `TargetRules`  
`public class BuildPatchToolTarget : TargetRules`  
_L8-45_
- attrs: `[SupportedPlatforms("Win64", "Mac", "Linux")] [SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)]`
- L10 _ctor_ `public BuildPatchToolTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: DISABLE_CWD_CHANGES=1, UE_DONT_USE_DEFAULT_OUTPUT_DEVICES=1, NOINITCRASHREPORTER=1, DISABLE_AUDIO_MCP_MODULES=1, PORTAL_CHANGELIST={0}, PORTAL_BRANCH_NAME=\"{0}\"
  - L12 `Type = TargetType.Program`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L15 `LinkType = TargetLinkType.Monolithic`
  - L17 `LaunchModuleName = "BuildPatchTool"`
  - L18 `bLegalToDistributeBinary = true`
  - L19 `UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L21 `bCompileAgainstEngine = false`
  - L22 `bCompileAgainstCoreUObject = false`
  - L23 `bCompileAgainstApplicationCore = false`
  - L24 `bBuildDeveloperTools = false`
  - L25 `bUseLoggingInShipping = true`
  - L26 `bUseChecksInShipping = true`
  - L27 `bIsBuildingConsoleApplication = true`
  - L28 `bHasExports = false`
  - L29 `bWithServerCode = false`
  - L30 `bForceDisableAutomationTests = true`

### `Source/Programs/BuildStorageTool/BuildStorageTool.Target.cs` (TargetRules)


#### class `BuildStorageToolTarget` : `TargetRules`  
`public class BuildStorageToolTarget : TargetRules`  
_L7-44_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public BuildStorageToolTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: WITH_AUTOMATION_TESTS=0, WITH_AUTOMATION_WORKER=0
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LaunchModuleName = "BuildStorageTool"`
  - L16 `bUseXGEController = false`
  - L17 `bLoggingToMemoryEnabled = true`
  - L18 `bUseLoggingInShipping = true`
  - L19 `bCompileWithAccessibilitySupport = false`
  - L20 `bWithServerCode = false`
  - L21 `bCompileNavmeshClusterLinks = false`
  - L22 `bCompileNavmeshSegmentLinks = false`
  - L23 `bCompileRecast = false`
  - L24 `bCompileICU = true`
  - L25 `bWithLiveCoding = false`
  - L26 `bBuildDeveloperTools = false`
  - L27 `bBuildWithEditorOnlyData = false`
  - L28 `bCompileAgainstEngine = false`
  - L29 `bCompileAgainstCoreUObject = true`
  - L30 `bCompileAgainstApplicationCore = true`
  - L31 `bUsesSlate = true`
  - L32 `bForceDisableAutomationTests = true`
  - L34 `bIsBuildingConsoleApplication = false`
  - L36 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L37 `WindowsPlatform.bPixProfilingEnabled = false`
  - L38 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L39 `WindowsPlatform.bStripUnreferencedSymbols = true`

### `Source/Programs/CSVTools/CSVToTelemetry/CSVToTelemetry.Target.cs` (TargetRules)


#### class `CSVToTelemetryTarget` : `TargetRules`  
`public class CSVToTelemetryTarget : TargetRules`  
_L6-47_
- L8 _ctor_ `public CSVToTelemetryTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_EXTERNAL_PROFILING_ENABLED=0
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Modular`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "CSVToTelemetry"`
  - L15 `bUseXGEController = false`
  - L16 `bCompileFreeType = false`
  - L17 `bLoggingToMemoryEnabled = false`
  - L18 `bUseLoggingInShipping = true`
  - L19 `bCompileWithAccessibilitySupport = false`
  - L20 `bCompileWithPluginSupport = true`
  - L21 `bIncludePluginsForTargetPlatforms = true`
  - L22 `bWithServerCode = false`
  - L23 `bCompileNavmeshClusterLinks = false`
  - L24 `bCompileNavmeshSegmentLinks = false`
  - L25 `bCompileRecast = false`
  - L26 `bCompileICU = false`
  - L27 `bWithLiveCoding = false`
  - L28 `bBuildDeveloperTools = false`
  - L29 `bBuildWithEditorOnlyData = true`
  - L30 `bCompileAgainstEngine = false`
  - L31 `bCompileAgainstCoreUObject = true`
  - L32 `bCompileAgainstApplicationCore = true`
  - L33 `bUsesSlate = false`
  - L34 `bIsBuildingConsoleApplication = true`
  - L35 `bForceBuildTargetPlatforms = true`
  - L36 `bNeedsExtraShaderFormats = true`
  - L37 `bAreTargetSDKVersionsRelevantOverride = false`
  - L39 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L40 `WindowsPlatform.bPixProfilingEnabled = false`
  - L41 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L42 `WindowsPlatform.bStripUnreferencedSymbols = true`
  - L44 `bEnableTrace = true`

### `Source/Programs/ChaosVisualDebugger/ChaosVisualDebugger.Target.cs` (TargetRules)


#### class `ChaosVisualDebuggerTarget` : `TargetRules`  
`public class ChaosVisualDebuggerTarget : TargetRules`  
_L7-70_
- attrs: `[SupportedPlatforms("Win64")]`
- L9 _ctor_ `public ChaosVisualDebuggerTarget(TargetInfo Target) : base(Target)`
  - **AdditionalPlugins**: ChaosVD, GeometryProcessing, PropertyAccessEditor
  - **EnablePlugins**: GeometryProcessing, ChaosVD, PropertyAccessEditor
  - **GlobalDefinitions**: AUTOSDKS_ENABLED=0, ASSETREGISTRY_FORCE_PREMADE_REGISTRY_IN_EDITOR=1, UE_IS_COOKED_EDITOR=1, UE_FORCE_USE_PAKS=1, UE_FORCE_USE_IOSTORE=0, UE_ALLOW_SHADER_COMPILING_BASED_ON_SHADER_DIRECTORY_EXISTENCE=1, UE_TRACE_SERVER_LAUNCH_ENABLED=1, UE_TRACE_SERVER_CONTROLS_ENABLED=1
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "ChaosVisualDebugger"`
  - L14 `BuildEnvironment = TargetBuildEnvironment.Unique`
  - L16 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L17 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L19 `bIsBuildingConsoleApplication = false`
  - L21 `bCompileAgainstCoreUObject = true`
  - L22 `bCompileAgainstEngine = true`
  - L23 `bCompileAgainstEditor = true`
  - L24 `bBuildWithEditorOnlyData = true`
  - L25 `bUsesSlate = true`
  - L26 `bEnableTrace = true`
  - L27 `bUseLoggingInShipping = true`
  - L29 `bCompileWithPluginSupport = true`
  - L30 `bBuildDeveloperTools = true`
  - L33 `bCompilePython = false`
  - L34 `bCompileICU = true`
  - L35 `bCompileRecast = false`
  - L36 `bUseGameplayDebugger = false`
  - L37 `bCompileNavmeshClusterLinks = false`
  - L38 `bCompileNavmeshSegmentLinks = false`
  - L39 `bWithLiveCoding = false`
  - L40 `bIncludePluginsForTargetPlatforms = false`
  - L42 `bCompileChaosVisualDebuggerSupport = true`
  - L44 `OptedInModulePlatforms = new UnrealTargetPlatform[] { UnrealTargetPlatform.Win64 }`

### `Source/Programs/CmdLink/CmdLink.Target.cs` (TargetRules)


#### class `CmdLinkTarget` : `TargetRules`  
`public class CmdLinkTarget : TargetRules`  
_L8-35_
- attrs: `[SupportedPlatforms("Win64")]`
- L10 _ctor_ `public CmdLinkTarget(TargetInfo Target) : base(Target)`
  - L12 `Type = TargetType.Program`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `LaunchModuleName = "CmdLink"`
  - L15 `bLegalToDistributeBinary = true`
  - L20 `bBuildDeveloperTools = false`
  - L23 `bCompileICU = false`
  - L26 `bCompileAgainstEngine = false`
  - L27 `bCompileAgainstCoreUObject = false`
  - L28 `bCompileAgainstApplicationCore = false`
  - L29 `bBuildWithEditorOnlyData = false`
  - L30 `bCompileCEF3 = false`
  - L33 `bIsBuildingConsoleApplication = true`

### `Source/Programs/CrashReportClient/CrashReportClient.Target.cs` (TargetRules)


#### class `CrashReportClientTarget` : `TargetRules`  
`public class CrashReportClientTarget : TargetRules`  
_L8-107_
- attrs: `[SupportedPlatforms("Win64", "Mac", "Linux", "LinuxArm64")] [SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)]`
- L26 _ctor_ `public CrashReportClientTarget(TargetInfo Target) : this(Target, true)`
- L29 _ctor_ `protected CrashReportClientTarget(TargetInfo Target, bool bSetConfiguredDefinitions) : base(Target)`
  - **ExtraModuleNames** [`if (bBuildEditor == true && Target.Platform != UnrealTargetPlatform.Linux)`]: EditorStyle
  - **GlobalDefinitions**: UE_TASKGRAPH_THREAD_LIMIT=5, NOINITCRASHREPORTER=1
  - **GlobalDefinitions** [`if (bSetConfiguredDefinitions)`]: SetupConfiguredDefines( DefaultUrl, DefaultCompanyName, TelemetryUrl, TelemetryK
  - L31 `Type = TargetType.Program`
  - L32 `LinkType = TargetLinkType.Monolithic`
  - L33 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L34 `UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L36 `LaunchModuleName = "CrashReportClient"`
  - L43 `bLegalToDistributeBinary = true`
  - L45 `bBuildDeveloperTools = false`
  - L48 `bCompileAgainstEngine = false`
  - L49 `bCompileAgainstCoreUObject = true`
  - L50 `bUseLoggingInShipping = true`
  - L54 `bHasExports = false`
  - L56 `bUseChecksInShipping = true`
  - L59 `bEnableOSX109Support = true`
  - L62 `WindowsPlatform.bUseBundledDbgHelp = false`
- L78 _method_ `protected static List<string> SetupConfiguredDefines( string DefaultUrl, string DefaultCompanyName, string TelemetryUrl, string TelemetryKey)`
  - **Definitions** [`if (!string.IsNullOrEmpty(DefaultUrl))`]: CRC_DEFAULT_URL=\"{DefaultUrl}\"
  - **Definitions** [`if (!string.IsNullOrEmpty(DefaultCompanyName))`]: CRC_DEFAULT_COMPANY_NAME=\"{DefaultCompanyName}\"
  - **Definitions** [`if(!string.IsNullOrWhiteSpace(TelemetryUrl))`]: CRC_TELEMETRY_URL=\"{TelemetryUrl}\"
  - **Definitions** [`if (!string.IsNullOrWhiteSpace(TelemetryKey))`]: CRC_TELEMETRY_KEY=\"{TelemetryKey}\"

### `Source/Programs/CrashReportClient/CrashReportClientEditor.Target.cs` (TargetRules)


#### class `CrashReportClientEditorTarget` : `CrashReportClientTarget`  
`public sealed class CrashReportClientEditorTarget : CrashReportClientTarget`  
_L7-54_
- attrs: `[SupportedPlatforms("Win64", "Mac", "Linux")] [SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)]`
- L25 _ctor_ `public CrashReportClientEditorTarget(TargetInfo Target) : base(Target, false )`
  - **AdditionalPlugins** [`if (bHostRecoverySvc)`]: UdpMessaging
  - **AdditionalPlugins** [`if (bHostRecoverySvc)`]: ConcertSyncServer
  - **GlobalDefinitions**: SetupConfiguredDefines( DefaultUrl, DefaultCompanyName, TelemetryUrl, TelemetryK
  - **GlobalDefinitions** [`if (bHostRecoverySvc) && if (Target.Configuration == UnrealTargetConfiguration.Shipping && LinkType == TargetLinkType.Monolithic)`]: PLATFORM_SUPPORTS_MESSAGEBUS=1
  - L27 `LaunchModuleName = "CrashReportClientEditor"`
  - L32 `bBuildWithEditorOnlyData = false`
  - L33 `bBuildDeveloperTools = true`
  - L39 [`if (bHostRecoverySvc)`] `bCompileWithPluginSupport = true`

### `Source/Programs/DerivedDataTool/DerivedDataTool.Target.cs` (TargetRules)


#### class `DerivedDataToolTarget` : `TargetRules`  
`public class DerivedDataToolTarget : TargetRules`  
_L6-32_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public DerivedDataToolTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions** [`if (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development)`]: LLM_ENABLED_IN_CONFIG=1
  - **GlobalDefinitions** [`if (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development)`]: UE_MEMORY_TAGS_TRACE_ENABLED=1
  - L10 `Type = TargetType.Program`
  - L11 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "DerivedDataTool"`
  - L15 `bBuildDeveloperTools = false`
  - L16 `bCompileAgainstApplicationCore = true`
  - L17 `bCompileAgainstCoreUObject = false`
  - L18 `bCompileAgainstEngine = false`
  - L19 `bCompileICU = false`
  - L20 `bForceDisableAutomationTests = true`
  - L21 `bIsBuildingConsoleApplication = true`
  - L22 `bUseLoggingInShipping = true`
  - L29 [`if (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development)`] `bEnableTrace = true`

### `Source/Programs/DiffAssetBulkData/DiffAssetBulkData.Target.cs` (TargetRules)


#### class `DiffAssetBulkDataTarget` : `TargetRules`  
`public class DiffAssetBulkDataTarget : TargetRules`  
_L6-47_
- L8 _ctor_ `public DiffAssetBulkDataTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_EXTERNAL_PROFILING_ENABLED=0
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Modular`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "DiffAssetBulkData"`
  - L15 `bUseXGEController = false`
  - L16 `bCompileFreeType = false`
  - L17 `bLoggingToMemoryEnabled = false`
  - L18 `bUseLoggingInShipping = true`
  - L19 `bCompileWithAccessibilitySupport = false`
  - L20 `bCompileWithPluginSupport = false`
  - L21 `bIncludePluginsForTargetPlatforms = false`
  - L22 `bWithServerCode = false`
  - L23 `bCompileNavmeshClusterLinks = false`
  - L24 `bCompileNavmeshSegmentLinks = false`
  - L25 `bCompileRecast = false`
  - L26 `bCompileICU = false`
  - L27 `bWithLiveCoding = false`
  - L28 `bBuildDeveloperTools = false`
  - L29 `bBuildWithEditorOnlyData = true`
  - L30 `bCompileAgainstEngine = false`
  - L31 `bCompileAgainstCoreUObject = true`
  - L32 `bCompileAgainstApplicationCore = true`
  - L33 `bUsesSlate = false`
  - L34 `bIsBuildingConsoleApplication = true`
  - L35 `bForceBuildTargetPlatforms = true`
  - L36 `bNeedsExtraShaderFormats = false`
  - L37 `bAreTargetSDKVersionsRelevantOverride = false`
  - L39 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L40 `WindowsPlatform.bPixProfilingEnabled = false`
  - L41 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L42 `WindowsPlatform.bStripUnreferencedSymbols = true`
  - L44 `bEnableTrace = true`

### `Source/Programs/DumpSyms/DumpSyms.Target.cs` (TargetRules)


#### class `DumpSymsTarget` : `TargetRules`  
`public class DumpSymsTarget : TargetRules`  
_L9-39_
- attrs: `[SupportedPlatforms("Win64", "Linux")]`
- L11 _ctor_ `public DumpSymsTarget(TargetInfo Target) : base(Target)`
  - L13 `Type = TargetType.Program`
  - L14 `LinkType = TargetLinkType.Monolithic`
  - L15 `LaunchModuleName = "DumpSyms"`
  - L18 `UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L21 `bBuildDeveloperTools = false`
  - L24 `bCompileAgainstEngine = false`
  - L25 `bCompileAgainstCoreUObject = false`
  - L28 `bUseLoggingInShipping = true`
  - L31 `bIsBuildingConsoleApplication = true`
  - L33 `bUseUnityBuild = false`
  - L37 `OutputFile = Path.Combine("Binaries", "Linux", $"dump_syms{BinaryExt}")`

### `Source/Programs/Enterprise/Datasmith/DatasmithCADWorker/DatasmithCADWorker.Target.cs` (TargetRules)


#### class `DatasmithCADWorkerTarget` : `TargetRules`  
`public class DatasmithCADWorkerTarget : TargetRules`  
_L7-39_
- attrs: `[SupportedPlatforms("Win64")]`
- L9 _ctor_ `public DatasmithCADWorkerTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LaunchModuleName = "DatasmithCADWorker"`
  - L15 `SolutionDirectory = "Programs/Datasmith"`
  - L18 `bBuildDeveloperTools = false`
  - L21 `bBuildWithEditorOnlyData = false`
  - L24 `bCompileAgainstEngine = false`
  - L25 `bCompileAgainstCoreUObject = false`
  - L26 `bCompileAgainstApplicationCore = true`
  - L29 `bIsBuildingConsoleApplication = true`
  - L31 `bLegalToDistributeBinary = true`
  - L33 `bCompileICU = false`
  - L34 `bCompileCEF3 = false`
  - L37 `ExeBinariesSubFolder = EngineDir + @"\Plugins\Enterprise\DatasmithCADImporter\Binaries\Win64\"`

### `Source/Programs/Enterprise/Datasmith/DatasmithFacadeCSharp/DatasmithFacadeCSharp.Target.cs` (TargetRules)


#### class `DatasmithFacadeCSharpTarget` : `TargetRules`  
`public class DatasmithFacadeCSharpTarget : TargetRules`  
_L8-117_
- attrs: `[SupportedPlatforms("Win64", "Mac")]`
- L10 _ctor_ `public DatasmithFacadeCSharpTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_EXTERNAL_PROFILING_ENABLED=0, NOINITCRASHREPORTER=1
  - L13 `Type = TargetType.Program`
  - L14 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L15 `SolutionDirectory = Path.Combine("Programs","Datasmith")`
  - L16 `bBuildInSolutionByDefault = false`
  - L18 `LaunchModuleName = "DatasmithFacadeCSharp"`
  - L19 `ExeBinariesSubFolder = "DatasmithFacadeCSharp"`
  - L21 `bShouldCompileAsDLL = true`
  - L22 `LinkType = TargetLinkType.Monolithic`
  - L24 `bBuildDeveloperTools = false`
  - L25 `bBuildWithEditorOnlyData = true`
  - L26 `bCompileAgainstEngine = false`
  - L27 `bCompileAgainstCoreUObject = true`
  - L28 `bCompileICU = false`
  - L30 `bUsesSlate = true`
  - L31 `bHasExports = true`
  - L32 `bForceEnableExceptions = true`
  - L43 call `AddPreBuildSteps(Target.Platform)`
  - L44 call `AddPostBuildSteps(Target.Platform)`
- L47 _method_ `public void AddPreBuildSteps(UnrealTargetPlatform TargetPlatform)`
  - **PreBuildSteps**: echo Using SWIG_DIR env. variable: %SWIG_DIR%, CleanCommand, SwigCommand
  - **PreBuildSteps** [`if (string.IsNullOrEmpty(System.Environment.GetEnvironmentVariable("SWIG_DIR")))`]: echo Environment variable SWIG_DIR is not defined.
  - **PreBuildSteps** [`if (TargetPlatform == UnrealTargetPlatform.Mac)`]: \"{0}\" \"{1}\", Mac, bin, python, FacadeHeaderHelper.py
  - **PreBuildSteps** [`else`]: \"{0}\" \"{1}\", Win64, python.exe, FacadeHeaderHelper.py
  - L76 [`if (TargetPlatform == UnrealTargetPlatform.Mac)`] `CleanCommand = string.Format("rm -f \"{0}\"", CleanupPath)`
- L97 _method_ `protected void AddPostBuildSteps(UnrealTargetPlatform TargetPlatform)`
  - **PostBuildSteps**: echo \"Replace {1} with {0}\"
  - **PostBuildSteps** [`if (TargetPlatform == UnrealTargetPlatform.Win64)`]: del /S /Q \"{0}\", *.cs
  - **PostBuildSteps** [`if (TargetPlatform == UnrealTargetPlatform.Win64)`]: xcopy \"{0}\" \"{1}\" /R /S /Y
  - **PostBuildSteps** [`else if (TargetPlatform == UnrealTargetPlatform.Mac)`]: mkdir -p \"{0}\"
  - **PostBuildSteps** [`else if (TargetPlatform == UnrealTargetPlatform.Mac)`]: rm -f \"{0}\"*.cs
  - **PostBuildSteps** [`else if (TargetPlatform == UnrealTargetPlatform.Mac)`]: cp -R \"{0}\"*.cs \"{1}\"

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2022.Target.cs` (TargetRules)


#### class `DatasmithMaxBaseTarget` : `TargetRules`  
`public abstract class DatasmithMaxBaseTarget : TargetRules`  
_L9-86_
- attrs: `[SupportedPlatforms("Win64")]`
- L11 _ctor_ `public DatasmithMaxBaseTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_EXTERNAL_PROFILING_ENABLED=0, NO_INIUTIL_USING, NOINITCRASHREPORTER=1
  - L14 `Type = TargetType.Program`
  - L15 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L16 `SolutionDirectory = "Programs/Datasmith"`
  - L17 `bBuildInSolutionByDefault = false`
  - L18 `bLegalToDistributeBinary = true`
  - L20 `bShouldCompileAsDLL = true`
  - L21 `LinkType = TargetLinkType.Monolithic`
  - L23 `WindowsPlatform.ModuleDefinitionFile = "Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMaxExporterWithDirectLink.def"`
  - L31 [`if(StaticAnalyzer != StaticAnalyzer.None) && if (SDKRootEnvVar != null && SDKRootEnvVar != "")`] `MaxSDKLocation = Path.Combine(SDKRootEnvVar, "HostWin64", "Win64", "3dsMax")`
  - L38 [`if(StaticAnalyzer != StaticAnalyzer.None)`] `WindowsPlatform.Compiler = WindowsCompiler.Clang`
  - L39 [`if(StaticAnalyzer != StaticAnalyzer.None)`] call `Console.WriteLine("Skipping " + MaxSDKLocation)`
  - L40 [`if(StaticAnalyzer != StaticAnalyzer.None)`] `AdditionalCompilerArguments = "-Xanalyzer,-isystem-after" + MaxSDKLocation`
  - L44 [`else`] `WindowsPlatform.Compiler = WindowsCompiler.VisualStudio`
  - L47 `bBuildDeveloperTools = false`
  - L48 `bBuildWithEditorOnlyData = true`
  - L49 `bCompileAgainstEngine = false`
  - L50 `bCompileAgainstCoreUObject = true`
  - L51 `bCompileICU = false`
  - L52 `bUsesSlate = false`
  - L54 `bHasExports = true`
  - L55 `bForceEnableExceptions = true`
- L68 _method_ `protected void AddCopyPostBuildStep(TargetInfo Target)`
  - **PostBuildSteps**: echo Copying {0} to {1}..., copy /Y \"{0}\" \"{1}\" 1>nul, echo Copying {0} to {1}..., copy /Y \"{0}\" \"{1}\" 1>nul
  - L74 [`if (Target.Configuration != UnrealTargetConfiguration.Development)`] `OutputName = string.Format("{0}-{1}-{2}", OutputName, Target.Platform, Target.Configuration)`

#### class `DatasmithMax2022Target` : `DatasmithMaxBaseTarget`  
`public class DatasmithMax2022Target : DatasmithMaxBaseTarget`  
_L88-99_
- L90 _ctor_ `public DatasmithMax2022Target(TargetInfo Target) : base(Target)`
  - L92 `LaunchModuleName = "DatasmithMax2022"`
  - L93 `ExeBinariesSubFolder = @"3DSMax\2022"`
  - L97 call `AddCopyPostBuildStep(Target)`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2023.Target.cs` (TargetRules)


#### class `DatasmithMax2023Target` : `DatasmithMaxBaseTarget`  
`public class DatasmithMax2023Target : DatasmithMaxBaseTarget`  
_L6-15_
- L8 _ctor_ `public DatasmithMax2023Target(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "DatasmithMax2023"`
  - L11 `ExeBinariesSubFolder = @"3DSMax\2023"`
  - L13 call `AddCopyPostBuildStep(Target)`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2024.Target.cs` (TargetRules)


#### class `DatasmithMax2024Target` : `DatasmithMaxBaseTarget`  
`public class DatasmithMax2024Target : DatasmithMaxBaseTarget`  
_L6-15_
- L8 _ctor_ `public DatasmithMax2024Target(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "DatasmithMax2024"`
  - L11 `ExeBinariesSubFolder = @"3DSMax\2024"`
  - L13 call `AddCopyPostBuildStep(Target)`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2025.Target.cs` (TargetRules)


#### class `DatasmithMax2025Target` : `DatasmithMaxBaseTarget`  
`public class DatasmithMax2025Target : DatasmithMaxBaseTarget`  
_L6-15_
- L8 _ctor_ `public DatasmithMax2025Target(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "DatasmithMax2025"`
  - L11 `ExeBinariesSubFolder = @"3DSMax\2025"`
  - L13 call `AddCopyPostBuildStep(Target)`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2026.Target.cs` (TargetRules)


#### class `DatasmithMax2026Target` : `DatasmithMaxBaseTarget`  
`public class DatasmithMax2026Target : DatasmithMaxBaseTarget`  
_L6-15_
- L8 _ctor_ `public DatasmithMax2026Target(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "DatasmithMax2026"`
  - L11 `ExeBinariesSubFolder = @"3DSMax\2026"`
  - L13 call `AddCopyPostBuildStep(Target)`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2027.Target.cs` (TargetRules)


#### class `DatasmithMax2027Target` : `DatasmithMaxBaseTarget`  
`public class DatasmithMax2027Target : DatasmithMaxBaseTarget`  
_L6-15_
- L8 _ctor_ `public DatasmithMax2027Target(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "DatasmithMax2027"`
  - L11 `ExeBinariesSubFolder = @"3DSMax\2027"`
  - L13 call `AddCopyPostBuildStep(Target)`

### `Source/Programs/Enterprise/Datasmith/DatasmithSDK/DatasmithSDK.Target.cs` (TargetRules)


#### class `DatasmithSDKTarget` : `TargetRules`  
`public class DatasmithSDKTarget : TargetRules`  
_L13-170_
- attrs: `[SupportedPlatforms("Win64", "Mac", "Linux")]`
- L15 _ctor_ `public DatasmithSDKTarget(TargetInfo Target) : base(Target)`
  - **ExtraModuleNames**: DatasmithCore, DatasmithExporter
  - **GlobalDefinitions** [`if (BuildEnvironment == TargetBuildEnvironment.Unique)`]: ALLOW_UDP_MESSAGING_SHIPPING=1
  - **GlobalDefinitions** [`if (BuildEnvironment == TargetBuildEnvironment.Unique)`]: PLATFORM_SUPPORTS_MESSAGEBUS=1
  - **PostBuildSteps** [`if (Platform != UnrealTargetPlatform.Win64)`]: echo Creating directories to export to\n
  - **PostBuildSteps** [`if (Platform != UnrealTargetPlatform.Win64) && foreach (string Directory in Directories)`]: mkdir -p {0}\n
  - L18 `Type = TargetType.Program`
  - L19 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L20 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L21 `SolutionDirectory = "Programs/Datasmith"`
  - L22 `bBuildInSolutionByDefault = false`
  - L24 `LaunchModuleName = "DatasmithSDK"`
  - L25 `ExeBinariesSubFolder = "DatasmithSDK"`
  - L29 `LinkType = TargetLinkType.Monolithic`
  - L30 `bShouldCompileAsDLL = true`
  - L32 `bBuildDeveloperTools = false`
  - L33 `bBuildWithEditorOnlyData = true`
  - L34 `bCompileAgainstEngine = false`
  - L35 `bCompileAgainstCoreUObject = true`
  - L36 `bCompileICU = false`
  - L37 `bUsesSlate = false`
  - L38 `DebugInfo = DebugInfoMode.Full`
  - L39 `bUsePDBFiles = true`
  - L40 `bHasExports = true`
  - L41 `bIsBuildingConsoleApplication = true`
  - L69 [`if (Platform != UnrealTargetPlatform.Win64)`] `PostBuildCopy = PostBuildCopyUnix`
  - L72 call `AddPostBuildSteps()`
- L81 _method_ `public void PostBuildCopyWin64(string SrcPath, string DestPath, string Files)`
  - **PostBuildSteps**: echo Copying {0}{2} to {1}, call $(EngineDir)\Source\Programs\Enterprise\Datasmith\DatasmithSDK\CopyCmd.bat {0} {1} {2}
- L87 _method_ `public void PostBuildCopyUnix(string SrcPath, string DestPath, string Files)`
  - **PostBuildSteps**: echo Copying \"{0}\" to {1}\n, cp -R -f {0}/{2} {1} || true\n
  - L89 `SrcPath = SrcPath.Replace("\\", "/")`
  - L90 `DestPath = DestPath.Replace("\\", "/")`
- L96 _method_ `public void PostBuildCopyUnix(string SrcPath, string DestPath)`
  - **PostBuildSteps**: echo Copying \"{0}\" to {1}\n, cp -R -f {0} {1} || true\n
  - L98 `SrcPath = SrcPath.Replace("\\", "/")`
  - L99 `DestPath = DestPath.Replace("\\", "/")`
- L105 _method_ `public void AddPostBuildSteps()`
  - **PostBuildSteps** [`if (Platform != UnrealTargetPlatform.Win64)`]: echo Creating directories to export to\n
  - **PostBuildSteps** [`if (Platform != UnrealTargetPlatform.Win64) && foreach (string Directory in Directories)`]: mkdir -p {0}\n
  - **PostBuildSteps** [`else`]: mkdir {0}\n, Engine\\Content\\Binary
  - L132 [`if (Platform != UnrealTargetPlatform.Win64)`] `PostBuildCopy = PostBuildCopyUnix`
  - L134 [`if (Platform != UnrealTargetPlatform.Win64)`] call `PostBuildCopyUnix(@"$(EngineDir)/Content/Slate", Path.Combine(DstDatasmithSDK, "Engine/Content/"))`
  - L135 [`if (Platform != UnrealTargetPlatform.Win64)`] call `PostBuildCopyUnix(@"$(EngineDir)/Shaders/StandaloneRenderer/OpenGL", Path.Combine(DstDatasmithSDK, "Engine/Shaders/StandaloneRenderer"))`
  - L140 [`else`] call `PostBuildCopyWin64(@"$(EngineDir)\Content\Slate\", Path.Combine(DstDatasmithSDK, "Engine\\Content\\"), "")`
  - L141 [`else`] call `PostBuildCopyWin64(@"$(EngineDir)\Shaders\StandaloneRenderer\D3D\", Path.Combine(DstDatasmithSDK, "Engine\\Shaders\\StandaloneRenderer\\D3D\\"), "")`
  - L167 [`foreach ((string, string, string) ToCopy in FilesToCopy)`] call `PostBuildCopy(ToCopy.Item1, ToCopy.Item2, ToCopy.Item3)`

### `Source/Programs/EpicWebHelper/EpicWebHelper.Target.cs` (TargetRules)


#### class `EpicWebHelperTarget` : `TargetRules`  
`public class EpicWebHelperTarget : TargetRules`  
_L9-66_
- attrs: `[SupportedPlatforms("Win64", "Mac", "Linux")] [SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)]`
- L11 _ctor_ `public EpicWebHelperTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: ALLOW_LOG_FILE=0
  - **PostBuildSteps** [`if (Target.Platform == UnrealTargetPlatform.Mac)`]: echo Creating helper syminks
  - **PostBuildSteps** [`if (Target.Platform == UnrealTargetPlatform.Mac) && foreach( string HelperType in HelperTypes)`]: cd $(EngineDir)/Binaries/$(TargetPlatform); if [ ! -h \"EpicWebHelper ({0})\" ]; then ln -s \"EpicWebHelper\" \"EpicWebHelper ({1})\"; fi
  - L13 `Type = TargetType.Program`
  - L14 `LinkType = TargetLinkType.Monolithic`
  - L15 `LaunchModuleName = "EpicWebHelper"`
  - L17 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L18 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L21 `UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L38 `bBuildDeveloperTools = false`
  - L41 `bCompileAgainstEngine = false`
  - L42 `bCompileAgainstCoreUObject = false`
  - L43 `bBuildWithEditorOnlyData = true`
  - L51 [`if (Target.Platform == UnrealTargetPlatform.Mac)`] `bIsBuildingConsoleApplication = true`
  - L56 [`else`] `bIsBuildingConsoleApplication = false`
  - L63 `bEnableOSX109Support = true`

### `Source/Programs/GPUReshape/Source/GPUReshapeBootstrapper.Target.cs` (TargetRules)


#### class `GPUReshapeBootstrapperTarget` : `TargetRules`  
`public class GPUReshapeBootstrapperTarget : TargetRules`  
_L6-25_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public GPUReshapeBootstrapperTarget(TargetInfo Target) : base(Target)`
  - L10 `Type = TargetType.Program`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L15 `bCompileICU = false`
  - L16 `bBuildDeveloperTools = false`
  - L17 `bCompileAgainstEngine = false`
  - L18 `bCompileAgainstCoreUObject = false`
  - L19 `bCompileAgainstApplicationCore = false`
  - L20 `bIsBuildingConsoleApplication = true`
  - L22 `SolutionDirectory = "Programs/GPUReshape"`
  - L23 `LaunchModuleName = "GPUReshapeBootstrapper"`

### `Source/Programs/GeometryProcessing/GeometryProcessing.Target.cs` (TargetRules)


#### class `GeometryProcessingTarget` : `TargetRules`  
`public class GeometryProcessingTarget : TargetRules`  
_L7-33_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L9 _ctor_ `public GeometryProcessingTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `LaunchModuleName = "GeometryProcessing"`
  - L17 `bBuildDeveloperTools = false`
  - L19 `bBuildWithEditorOnlyData = true`
  - L22 `bCompileAgainstEngine = false`
  - L23 `bCompileAgainstCoreUObject = false`
  - L24 `bCompileAgainstApplicationCore = false`
  - L25 `bCompileICU = false`
  - L31 `bIsBuildingConsoleApplication = true`

### `Source/Programs/HeadlessChaos/HeadlessChaos.Target.cs` (TargetRules)


#### class `HeadlessChaosTarget` : `TestTargetRules`  
`public class HeadlessChaosTarget : TestTargetRules`  
_L6-22_
- attrs: `[SupportedPlatforms("Win64")]`
- L8 _ctor_ `public HeadlessChaosTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: CHAOS_SERIALIZE_OUT=1, CHAOS_CONSTRAINTHANDLE_DEBUG_ENABLED=1
  - L10 `bHasExports = false`
  - L15 `bDebugBuildsActuallyUseDebugCRT = false`
  - L19 `BuildEnvironment = TargetBuildEnvironment.Unique`
  - L20 `bWarningsAsErrors = true`

### `Source/Programs/HeadlessChaosPerf/HeadlessChaosPerf.Target.cs` (TargetRules)


#### class `HeadlessChaosPerfTarget` : `TargetRules`  
`public class HeadlessChaosPerfTarget : TargetRules`  
_L7-33_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L9 _ctor_ `public HeadlessChaosPerfTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: CHAOS_SERIALIZE_OUT=1, CSV_PROFILER=1
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L14 `ExeBinariesSubFolder = "NotForLicensees"`
  - L15 `LaunchModuleName = "HeadlessChaosPerf"`
  - L17 `bBuildDeveloperTools = false`
  - L20 `bCompileAgainstEngine = false`
  - L21 `bCompileAgainstCoreUObject = true`
  - L23 `bHasExports = false`
  - L25 `bUseLoggingInShipping = true`
  - L28 `bIsBuildingConsoleApplication = true`

### `Source/Programs/IOS/UnrealLaunchDaemon/UnrealLaunchDaemon.Target.cs` (TargetRules)


#### class `UnrealLaunchDaemonTarget` : `TargetRules`  
`public class UnrealLaunchDaemonTarget : TargetRules`  
_L7-25_
- attrs: `[SupportedPlatforms("IOS")]`
- L9 _ctor_ `public UnrealLaunchDaemonTarget(TargetInfo Target) : base(Target)`
  - **AdditionalPlugins**: UdpMessaging
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `bUsesSlate = false`
  - L18 `LaunchModuleName = "UnrealLaunchDaemon"`
  - L20 `bBuildDeveloperTools = false`
  - L21 `bCompileAgainstEngine = false`
  - L23 `bHasExports = false`

### `Source/Programs/InterchangeWorker/InterchangeWorker.Target.cs` (TargetRules)


#### class `InterchangeWorkerTarget` : `TargetRules`  
`public class InterchangeWorkerTarget : TargetRules`  
_L8-40_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)] [SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)]`
- L10 _ctor_ `public InterchangeWorkerTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: USE_LOCALIZED_PACKAGE_CACHE=0
  - L12 `Type = TargetType.Program`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L15 `LaunchModuleName = "InterchangeWorker"`
  - L16 `SolutionDirectory = "Programs/InterchangeWorker"`
  - L19 `bBuildDeveloperTools = false`
  - L22 `bBuildWithEditorOnlyData = false`
  - L25 `bCompileAgainstEngine = false`
  - L26 `bCompileAgainstCoreUObject = true`
  - L27 `bCompileAgainstApplicationCore = true`
  - L30 `bIsBuildingConsoleApplication = true`
  - L32 `bLegalToDistributeBinary = true`
  - L34 `bCompileICU = false`
  - L35 `bCompileCEF3 = false`

### `Source/Programs/IoStoreDependencyViewer/IoStoreDependencyViewer.Target.cs` (TargetRules)


#### class `IoStoreDependencyViewerTarget` : `TargetRules`  
`public class IoStoreDependencyViewerTarget : TargetRules`  
_L7-34_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public IoStoreDependencyViewerTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `LaunchModuleName = "IoStoreDependencyViewer"`
  - L17 `bCompileAgainstEngine = false`
  - L18 `bCompileAgainstCoreUObject = true`
  - L19 `bCompileAgainstApplicationCore = true`
  - L22 `bIsBuildingConsoleApplication = true`
  - L25 `bUseLoggingInShipping = true`
  - L28 `bCompileWithPluginSupport = false`
  - L29 `bIncludePluginsForTargetPlatforms = false`
  - L32 `bForceEnableExceptions = true`

### `Source/Programs/IoStoreOnDemand/IasTool.Target.cs` (TargetRules)


#### class `IasToolTarget` : `TargetRules`  
`public class IasToolTarget : TargetRules`  
_L6-33_
- attrs: `[SupportedPlatforms("Win64", "Linux", "Mac")]`
- L8 _ctor_ `public IasToolTarget(TargetInfo Target) : base(Target)`
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `LaunchModuleName = "IasTool"`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L15 `bBuildDeveloperTools = false`
  - L16 `bBuildWithEditorOnlyData = false`
  - L17 `bCompileAgainstApplicationCore = false`
  - L18 `bCompileAgainstCoreUObject = false`
  - L19 `bCompileAgainstEngine = false`
  - L20 `bCompileICU = false`
  - L21 `bCompileNavmeshClusterLinks = false`
  - L22 `bCompileNavmeshSegmentLinks = false`
  - L23 `bCompileRecast = false`
  - L24 `bCompileWithPluginSupport = true`
  - L25 `bForceEnableExceptions = true`
  - L26 `bIsBuildingConsoleApplication = true`
  - L27 `bUsesSlate = false`
  - L28 `bWithLiveCoding = false`
  - L29 `bWithServerCode = false`
  - L31 `bEnableTrace = true`

### `Source/Programs/LiveCodingConsole/LiveCodingConsole.Target.cs` (TargetRules)


#### class `LiveCodingConsoleTarget` : `TargetRules`  
`public class LiveCodingConsoleTarget : TargetRules`  
_L7-38_
- attrs: `[SupportedPlatforms("Win64")]`
- L9 _ctor_ `public LiveCodingConsoleTarget(TargetInfo Target) : base(Target)`
  - L17 `Type = TargetType.Program`
  - L18 `LinkType = TargetLinkType.Monolithic`
  - L19 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L20 `LaunchModuleName = "LiveCodingConsole"`
  - L22 `bBuildDeveloperTools = false`
  - L23 `bCompileWithPluginSupport = true`
  - L24 `bIncludePluginsForTargetPlatforms = true`
  - L25 `bWithLiveCoding = true`
  - L28 `bBuildWithEditorOnlyData = true`
  - L31 `bCompileAgainstApplicationCore = true`
  - L32 `bCompileAgainstCoreUObject = true`
  - L33 `bCompileAgainstEngine = false`
  - L36 `bCompileICU = true`

### `Source/Programs/LiveLinkFbxProvider/Source/LiveLinkFbxProvider.Target.cs` (TargetRules)


#### class `LiveLinkFbxProviderTarget` : `TargetRules`  
`public class LiveLinkFbxProviderTarget : TargetRules`  
_L7-34_
- L9 _ctor_ `public LiveLinkFbxProviderTarget(TargetInfo Target) : base(Target)`
  - **AdditionalPlugins**: UdpMessaging
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L14 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L15 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L17 `SolutionDirectory = "Programs/LiveLink"`
  - L20 `LaunchModuleName = "LiveLinkFbxProvider"`
  - L23 `bCompileAgainstCoreUObject = true`
  - L24 `bCompileAgainstEngine = false`
  - L25 `bBuildDeveloperTools = false`
  - L26 `bCompileWithPluginSupport = false`
  - L29 `bBuildWithEditorOnlyData = true`
  - L32 `bIsBuildingConsoleApplication = true`

### `Source/Programs/LiveLinkHub/Source/LiveLinkHub.Target.cs` (TargetRules)


#### class `LiveLinkHubTarget` : `TargetRules`  
`public class LiveLinkHubTarget : TargetRules`  
_L9-137_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L21 _ctor_ `public LiveLinkHubTarget(TargetInfo Target) : base(Target)`
  - **EnablePlugins**: ACLPlugin, AudioCaptureTimecodeProvider, LiveLink, LiveLinkHub, PluginBrowser, LiveLinkCamera, LiveLinkLens, LensComponent, LiveLinkInputDevice, ContentBrowserAssetDataSource, ProceduralMeshComponent, PropertyAccessEditor, PythonScriptPlugin, UdpMessaging, MessageBusTester, CameraCalibrationCore, AppleARKitFaceSupport, XInputDevice, LiveLinkDevice, LiveLinkUnrealDevice, LiveLinkKiProDevice, LiveLinkSoundDevice, LiveLinkOBSDevice, LiveLinkOpenVR, LiveLinkOpenTrackIO, CaptureManagerApp, CaptureManagerDevices, MediaIOFramework, MediaFrameworkUtilities, AjaMedia, BlackmagicMedia, NDIMedia
  - **EnablePlugins** [`if (bEnableMetaHumanLiveLinkPlugin)`]: MetaHumanLiveLink, WmfMedia, AvfMedia, StreamingADA
  - **OutputFile** [`if (Configuration != UndecoratedConfiguration)`]: -, -
  - **OutputFile** [`if (Platform == UnrealTargetPlatform.Win64)`]: .exe
  - **PostBuildSteps**: echo Copying \"{ReceiptSrcPath}\" to \"{ReceiptDestPath}\"
  - **PostBuildSteps** [`if (Platform == UnrealTargetPlatform.Win64)`]: copy /Y \"{ReceiptSrcPath}\" \"{ReceiptDestPath}\"
  - **PostBuildSteps** [`else`]: cp -a \"{ReceiptSrcPath}\" \"{ReceiptDestPath}\"
  - L23 `Type = TargetType.Editor`
  - L24 `bExplicitTargetForType = true`
  - L25 `bGenerateProgramProject = true`
  - L27 `SolutionDirectory = "Programs/LiveLink"`
  - L28 `LaunchModuleName = "LiveLinkHubLauncher"`
  - L30 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L31 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L33 `MacPlatform.bForceTargetNameAsExeName = true`
  - L93 [`if (bSingleModulePlatform)`] `OptedInModulePlatforms = new UnrealTargetPlatform[] { Target.Platform }`
  - L96 `bAllowEnginePluginsEnabledByDefault = false`
  - L97 `bBuildAdditionalConsoleApp = false`
  - L101 `OutputFile = "Binaries/" + Platform.ToString() + "/" + BaseExeName`
  - L124 call `DirectoryReference.CreateDirectory(ReceiptDestPath.Directory)`

### `Source/Programs/Mac/DsymExporter/DsymExporter.Target.cs` (TargetRules)


#### class `DsymExporterTarget` : `TargetRules`  
`public class DsymExporterTarget : TargetRules`  
_L7-28_
- attrs: `[SupportedPlatforms("Mac")]`
- L9 _ctor_ `public DsymExporterTarget( TargetInfo Target ) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "DsymExporter"`
  - L15 `bBuildDeveloperTools = false`
  - L18 `bCompileAgainstEngine = false`
  - L21 `bHasExports = false`
  - L23 `bCompileAgainstCoreUObject = false`
  - L26 `bIsBuildingConsoleApplication = true`

### `Source/Programs/Mac/UnrealAtoS/UnrealAtoS.Target.cs` (TargetRules)


#### class `UnrealAtoSTarget` : `TargetRules`  
`public class UnrealAtoSTarget : TargetRules`  
_L7-28_
- attrs: `[SupportedPlatforms("Mac")]`
- L9 _ctor_ `public UnrealAtoSTarget( TargetInfo Target ) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "UnrealAtoS"`
  - L15 `bBuildDeveloperTools = false`
  - L18 `bCompileAgainstEngine = false`
  - L21 `bHasExports = false`
  - L23 `bCompileAgainstCoreUObject = false`
  - L26 `bIsBuildingConsoleApplication = true`

### `Source/Programs/Mac/UnrealEditorServices/UnrealEditorServices.Target.cs` (TargetRules)


#### class `UnrealEditorServicesTarget` : `TargetRules`  
`public class UnrealEditorServicesTarget : TargetRules`  
_L7-28_
- attrs: `[SupportedPlatforms("Mac")]`
- L9 _ctor_ `public UnrealEditorServicesTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "UnrealEditorServices"`
  - L15 `bBuildDeveloperTools = false`
  - L17 `bCompileICU = false`
  - L19 `bBuildWithEditorOnlyData = false`
  - L22 `bCompileAgainstEngine = false`
  - L23 `bCompileAgainstCoreUObject = false`
  - L26 `bEnableOSX109Support = true`

### `Source/Programs/ShaderAuditViewer/ShaderAuditViewer.Target.cs` (TargetRules)


#### class `ShaderAuditViewerTarget` : `TargetRules`  
`public class ShaderAuditViewerTarget : TargetRules`  
_L6-25_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public ShaderAuditViewerTarget(TargetInfo Target) : base(Target)`
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `LaunchModuleName = "ShaderAuditViewer"`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L17 `bCompileAgainstEngine = false`
  - L18 `bCompileAgainstCoreUObject = true`
  - L19 `bBuildDeveloperTools = true`
  - L20 `bBuildWithEditorOnlyData = true`
  - L21 `bCompileICU = false`
  - L22 `bIsBuildingConsoleApplication = true`
  - L23 `bHasExports = false`

### `Source/Programs/ShaderBuildWorker/ShaderBuildWorker.Target.cs` (TargetRules)


#### class `ShaderBuildWorkerTarget` : `DerivedDataBuildWorkerTarget`  
`public class ShaderBuildWorkerTarget : DerivedDataBuildWorkerTarget`  
_L8-29_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Editor)]`
- L10 _ctor_ `public ShaderBuildWorkerTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions** [`if (bShaderCompilerWorkerTrace)`]: LLM_ENABLED_IN_CONFIG=1
  - **GlobalDefinitions** [`if (bShaderCompilerWorkerTrace)`]: UE_MEMORY_TAGS_TRACE_ENABLED=1
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `BuildEnvironment = TargetBuildEnvironment.UniqueIfNeeded`
  - L14 `LinkType = TargetLinkType.Modular`
  - L15 `LaunchModuleName = "ShaderBuildWorker"`
  - L17 `bCompileAgainstApplicationCore = true`
  - L20 `bForceBuildShaderFormats = true`
  - L26 [`if (bShaderCompilerWorkerTrace)`] `bEnableTrace = true`

### `Source/Programs/ShaderCompileWorker/ShaderCompileWorker.Target.cs` (TargetRules)


#### class `ShaderCompileWorkerTarget` : `TargetRules`  
`public class ShaderCompileWorkerTarget : TargetRules`  
_L8-81_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Editor)]`
- L10 _ctor_ `public ShaderCompileWorkerTarget(TargetInfo Target) : base(Target)`
  - **AdditionalBuildProducts** [`if (bUseXGEController && (Target.Platform == UnrealTargetPlatform.Win64) && Configuration == UnrealTargetConfiguration.Development) && foreach (UnrealArch Arch in Target.Architectures.Architectures)`]: DestPath
  - **GlobalDefinitions**: ALLOW_LOG_FILE=0, ALLOW_WINDOWS_ERROR_REPORT_LIB=0, UE_EXTERNAL_PROFILING_ENABLED=0, NOINITCRASHREPORTER=1
  - **GlobalDefinitions** [`if (bShaderCompilerWorkerTrace)`]: LLM_ENABLED_IN_CONFIG=1
  - **GlobalDefinitions** [`if (bShaderCompilerWorkerTrace)`]: UE_MEMORY_TAGS_TRACE_ENABLED=1
  - **PostBuildSteps** [`if (bUseXGEController && (Target.Platform == UnrealTargetPlatform.Win64) && Configuration == UnrealTargetConfiguration.Development) && foreach (UnrealArch Arch in Target.Architectures.Architectures)`]: echo Copying {0} to {1}
  - **PostBuildSteps** [`if (bUseXGEController && (Target.Platform == UnrealTargetPlatform.Win64) && Configuration == UnrealTargetConfiguration.Development) && foreach (UnrealArch Arch in Target.Architectures.Architectures)`]: copy /Y /B \"{0}\" /B \"{1}\" >nul:
  - L12 `Type = TargetType.Program`
  - L13 `LinkType = TargetLinkType.Modular`
  - L14 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L15 `BuildEnvironment = TargetBuildEnvironment.UniqueIfNeeded`
  - L17 `LaunchModuleName = "ShaderCompileWorker"`
  - L40 `bBuildDeveloperTools = false`
  - L43 `bCompileICU = false`
  - L46 `bCompileAgainstEngine = false`
  - L47 `bCompileAgainstCoreUObject = false`
  - L48 `bBuildWithEditorOnlyData = true`
  - L49 `bCompileCEF3 = false`
  - L52 `bForceBuildShaderFormats = true`
  - L55 `bIsBuildingConsoleApplication = true`
  - L62 `bLoggingToMemoryEnabled = true`
  - L63 `bUseLoggingInShipping = true`
  - L78 [`if (bShaderCompilerWorkerTrace)`] `bEnableTrace = true`

### `Source/Programs/Shared/EpicGames.Perforce.Native/DotNetPerforceLib.Target.cs` (TargetRules)


#### class `DotNetPerforceLibTarget` : `TargetRules`  
`public class DotNetPerforceLibTarget : TargetRules`  
_L7-38_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)] [System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1050:Declare types in namespaces", Justification = "<Pending>")]`
- L9 _ctor_ `public DotNetPerforceLibTarget(TargetInfo target) : base(target)`
  - L11 `Type = TargetType.Program`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `LaunchModuleName = "DotNetPerforceLib"`
  - L16 `bShouldCompileAsDLL = true`
  - L18 `bBuildDeveloperTools = false`
  - L19 `bCompileICU = false`
  - L20 `bBuildWithEditorOnlyData = false`
  - L21 `bCompileAgainstEngine = false`
  - L22 `bCompileAgainstCoreUObject = false`
  - L27 [`if (target.Platform == UnrealTargetPlatform.Win64)`] `OutputFile = $"Binaries/DotNET/EpicGames.Perforce.Native/win-x64/{configFolder}/EpicGames.Perforce.Native.dll"`
  - L31 [`else if (target.Platform == UnrealTargetPlatform.Mac)`] `OutputFile = $"Binaries/DotNET/EpicGames.Perforce.Native/mac-x64/{configFolder}/EpicGames.Perforce.Native.dylib"`
  - L35 [`else if (target.Platform == UnrealTargetPlatform.Linux)`] `OutputFile = $"Binaries/DotNET/EpicGames.Perforce.Native/linux-x64/{configFolder}/EpicGames.Perforce.Native.so"`

### `Source/Programs/SlateUGS/SlateUGS.Target.cs` (TargetRules)


#### class `SlateUGSTarget` : `TargetRules`  
`public class SlateUGSTarget : TargetRules`  
_L7-32_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public SlateUGSTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L15 `LaunchModuleName = "SlateUGS"`
  - L17 `bBuildDeveloperTools = false`
  - L20 `bCompileAgainstEngine = false`
  - L23 `bCompileAgainstCoreUObject = true`
  - L27 `bHasExports = false`
  - L30 `bBuildDeveloperTools = true`

### `Source/Programs/SlateViewer/SlateViewer.Target.cs` (TargetRules)


#### class `SlateViewerTarget` : `TargetRules`  
`public class SlateViewerTarget : TargetRules`  
_L9-37_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)] [SupportedPlatforms("IOS")] [SupportedPlatforms("Android")]`
- L11 _ctor_ `public SlateViewerTarget(TargetInfo Target) : base(Target)`
  - **ExtraModuleNames** [`if (bBuildEditor)`]: EditorStyle
  - L13 `Type = TargetType.Program`
  - L14 `LinkType = TargetLinkType.Monolithic`
  - L16 `LaunchModuleName = "SlateViewer"`
  - L22 `bBuildDeveloperTools = false`
  - L25 `bCompileAgainstEngine = false`
  - L28 `bCompileAgainstCoreUObject = true`
  - L32 `bHasExports = false`
  - L35 `bBuildDeveloperTools = true`

### `Source/Programs/SubmitTool/SubmitTool.Target.cs` (TargetRules)


#### class `SubmitToolTarget` : `TargetRules`  
`public class SubmitToolTarget : TargetRules`  
_L6-57_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public SubmitToolTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_TASK_TRACE_ENABLED=1, AUTOSDKS_ENABLED=0, EXCLUDE_NONPAK_UE_EXTENSIONS=0, WITH_AUTOMATION_WORKER=0, UE_EXTERNAL_PROFILING_ENABLED=0, STATS=0, ENABLE_STATNAMEDEVENTS=0, ALLOW_HITCH_DETECTION=0, UE_USE_MALLOC_FILL_BYTES=0
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "SubmitTool"`
  - L16 `bUseXGEController = false`
  - L17 `bLoggingToMemoryEnabled = true`
  - L18 `bUseLoggingInShipping = true`
  - L19 `bCompileWithAccessibilitySupport = false`
  - L20 `bWithServerCode = false`
  - L21 `bCompileNavmeshClusterLinks = false`
  - L22 `bCompileNavmeshSegmentLinks = false`
  - L23 `bCompileRecast = false`
  - L24 `bCompileICU = true`
  - L25 `bWithLiveCoding = false`
  - L26 `bBuildDeveloperTools = false`
  - L27 `bBuildWithEditorOnlyData = false`
  - L28 `bCompileAgainstEngine = false`
  - L29 `bCompileAgainstCoreUObject = true`
  - L30 `bUsesSlate = true`
  - L31 `bIsBuildingConsoleApplication = false`
  - L32 `bCompileWithPluginSupport = true`
  - L33 `bBuildRequiresCookedData = false`
  - L34 `bEnableTrace = true`
  - L35 `bForceDisableAutomationTests = true`
  - L37 `bHasExports = false`
  - L39 `WindowsPlatform.bStripUnreferencedSymbols = true`
  - L40 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L41 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L42 `WindowsPlatform.bPixProfilingEnabled = false`
  - L54 `OptedInModulePlatforms = new UnrealTargetPlatform[] { UnrealTargetPlatform.Win64, UnrealTargetPlatform.Mac, UnrealTargetPlatform.Linux, UnrealTargetPlatform.LinuxArm64 }`

### `Source/Programs/SwitchboardListener/SwitchboardListener.Target.cs` (TargetRules)


#### class `SwitchboardListenerTargetBase` : `TargetRules`  
`public class SwitchboardListenerTargetBase : TargetRules`  
_L6-27_
- L8 _ctor_ `public SwitchboardListenerTargetBase(TargetInfo Target) : base(Target)`
  - L10 `SolutionDirectory = "Programs/Switchboard"`
  - L12 `Type = TargetType.Program`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L15 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L18 `bCompileAgainstCoreUObject = true`
  - L19 `bCompileAgainstEngine = false`
  - L20 `bBuildWithEditorOnlyData = false`
  - L23 `bCompileICU = false`
  - L25 `bEnableTrace = true`

#### class `SwitchboardListenerTarget` : `SwitchboardListenerTargetBase`  
`public class SwitchboardListenerTarget : SwitchboardListenerTargetBase`  
_L30-36_
- L32 _ctor_ `public SwitchboardListenerTarget(TargetInfo Target) : base(Target)`
  - L34 `LaunchModuleName = "SwitchboardListener"`

### `Source/Programs/SwitchboardListener/SwitchboardListenerCmd.Target.cs` (TargetRules)


#### class `SwitchboardListenerCmdTarget` : `SwitchboardListenerTargetBase`  
`public class SwitchboardListenerCmdTarget : SwitchboardListenerTargetBase`  
_L6-16_
- L8 _ctor_ `public SwitchboardListenerCmdTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "SwitchboardListenerCmd"`
  - L14 `bIsBuildingConsoleApplication = Target.Platform != UnrealTargetPlatform.Mac`

### `Source/Programs/SwitchboardListener/SwitchboardListenerTests.Target.cs` (TargetRules)


#### class `SwitchboardListenerTestsTarget` : `TestTargetRules`  
`public class SwitchboardListenerTestsTarget : TestTargetRules`  
_L7-19_
- attrs: `[SupportedPlatforms("Win64", "Linux")]`
- L9 _ctor_ `public SwitchboardListenerTestsTarget(TargetInfo Target) : base(Target)`
  - **ExtraModuleNames**: LaunchModuleName
  - **GlobalDefinitions**: SWITCHBOARD_LISTENER_EXCLUDE_MAIN=1
  - L11 `SolutionDirectory = "Programs/Switchboard"`
  - L12 `LaunchModuleName = "SwitchboardListenerTests"`

### `Source/Programs/SwitchboardListenerHelper/SwitchboardListenerHelper.Target.cs` (TargetRules)


#### class `SwitchboardListenerHelperTarget` : `TargetRules`  
`public class SwitchboardListenerHelperTarget : TargetRules`  
_L8-42_
- L10 _ctor_ `public SwitchboardListenerHelperTarget(TargetInfo Target) : base(Target)`
  - L12 `Type = TargetType.Program`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `LaunchModuleName = "SwitchboardListenerHelper"`
  - L15 `SolutionDirectory = "Programs/Switchboard"`
  - L17 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L20 `bCompileAgainstCoreUObject = true`
  - L21 `bCompileAgainstEngine = false`
  - L22 `bBuildWithEditorOnlyData = false`
  - L25 `bCompileICU = false`
  - L28 `bIsBuildingConsoleApplication = Target.Platform != UnrealTargetPlatform.Mac`
  - L30 `bEnableTrace = true`
  - L36 [`if (Target.Platform == UnrealTargetPlatform.Win64)`] `AdditionalLinkerArguments = "/MANIFESTUAC:NO"`
  - L37 [`if (Target.Platform == UnrealTargetPlatform.Win64)`] `WindowsPlatform.ManifestFile = FileReference.Combine(Unreal.EngineDirectory, "Source", "Programs", "SwitchboardListenerHelper", "Resources", "Windows", "SBLHelper.manifest.xml").ToString()`

### `Source/Programs/SymsLibDump/SymsLibDump.Target.cs` (TargetRules)


#### class `SymsLibDumpTarget` : `TargetRules`  
`public class SymsLibDumpTarget : TargetRules`  
_L7-37_
- attrs: `[SupportedPlatforms("Win64", "Linux")]`
- L9 _ctor_ `public SymsLibDumpTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions** [`if (Target.Configuration == UnrealTargetConfiguration.Shipping)`]: COMPILED_IN_MINIMUM_VERBOSITY=Error
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "SymsLibDump"`
  - L16 `UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L19 `bBuildDeveloperTools = false`
  - L22 `bCompileAgainstEngine = false`
  - L23 `bCompileAgainstCoreUObject = false`
  - L26 `bUseLoggingInShipping = true`
  - L29 `bIsBuildingConsoleApplication = true`

### `Source/Programs/TestPAL/TestPAL.Target.cs` (TargetRules)


#### class `TestPALTarget` : `TargetRules`  
`public class TestPALTarget : TargetRules`  
_L7-34_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public TestPALTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions** [`if (Target.Platform == UnrealTargetPlatform.Linux && Target.Configuration != UnrealTargetConfiguration.Shipping)`]: COMPILE_FORK_PAGE_PROTECTOR=1
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LaunchModuleName = "TestPAL"`
  - L17 `bBuildDeveloperTools = false`
  - L20 `bCompileAgainstEngine = false`
  - L21 `bCompileAgainstCoreUObject = false`
  - L24 `bUseLoggingInShipping = true`
  - L27 `bIsBuildingConsoleApplication = true`

### `Source/Programs/TraceAnalyzer/TraceAnalyzer.Target.cs` (TargetRules)


#### class `TraceAnalyzerTarget` : `TargetRules`  
`public class TraceAnalyzerTarget : TargetRules`  
_L7-56_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L9 _ctor_ `public TraceAnalyzerTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: CPUPROFILERTRACE_ENABLED=0, LOADTIMEPROFILERTRACE_ENABLED=0, STATSTRACE_ENABLED=0, COUNTERSTRACE_ENABLED=0, LOGTRACE_ENABLED=0, MISCTRACE_ENABLED=0, UE_TASK_TRACE_ENABLED=0, UE_NET_TRACE_ENABLED=0, UE_MEMORY_TAGS_TRACE_ENABLED=0, UE_MEMORY_TRACE_ENABLED=0, UE_CALLSTACK_TRACE_ENABLED=0, UE_TRACE_ANALYSIS_DEBUG_API=1, UE_TRACE_ANALYSIS_DEBUG=1, UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=1
  - L11 `Type = TargetType.Program`
  - L12 `LaunchModuleName = "TraceAnalyzer"`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L15 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L18 `bIsBuildingConsoleApplication = true`
  - L21 `bBuildDeveloperTools = false`
  - L23 `bBuildWithEditorOnlyData = false`
  - L28 `bCompileAgainstEngine = false`
  - L29 `bCompileAgainstCoreUObject = false`
  - L30 `bCompileAgainstApplicationCore = false`
  - L31 `bCompileICU = false`
  - L34 `bEnableTrace = false`

### `Source/Programs/TraceQuery/TraceQuery.Target.cs` (TargetRules)


#### class `TraceQueryTarget` : `TargetRules`  
`public class TraceQueryTarget : TargetRules`  
_L7-51_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L9 _ctor_ `public TraceQueryTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: CPUPROFILERTRACE_ENABLED=0, GPUPROFILERTRACE_ENABLED=0, LOADTIMEPROFILERTRACE_ENABLED=0, STATSTRACE_ENABLED=0, COUNTERSTRACE_ENABLED=0, LOGTRACE_ENABLED=0, MISCTRACE_ENABLED=0, UE_TASK_TRACE_ENABLED=0, UE_NET_TRACE_ENABLED=0, UE_MEMORY_TAGS_TRACE_ENABLED=0, UE_MEMORY_TRACE_ENABLED=0, UE_CALLSTACK_TRACE_ENABLED=0, UE_TRACE_ANALYSIS_DEBUG_API=0, UE_TRACE_ANALYSIS_DEBUG=0, UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=1, UE_TRACE_ANALYSIS_DEBUG_LEVEL=2
  - L11 `Type = TargetType.Program`
  - L12 `LaunchModuleName = "TraceQuery"`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L15 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L18 `bIsBuildingConsoleApplication = true`
  - L21 `bBuildDeveloperTools = false`
  - L23 `bBuildWithEditorOnlyData = false`
  - L26 `bCompileAgainstEngine = false`
  - L27 `bCompileAgainstCoreUObject = false`
  - L28 `bCompileAgainstApplicationCore = false`
  - L29 `bCompileICU = false`
  - L31 `bEnableTrace = false`

### `Source/Programs/TraceTrimmer/TraceTrimmer.Target.cs` (TargetRules)


#### class `TraceTrimmerTarget` : `TargetRules`  
`public class TraceTrimmerTarget : TargetRules`  
_L7-57_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L9 _ctor_ `public TraceTrimmerTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: CPUPROFILERTRACE_ENABLED=0, GPUPROFILERTRACE_ENABLED=0, LOADTIMEPROFILERTRACE_ENABLED=0, STATSTRACE_ENABLED=0, COUNTERSTRACE_ENABLED=0, LOGTRACE_ENABLED=0, MISCTRACE_ENABLED=0, UE_TASK_TRACE_ENABLED=0, UE_NET_TRACE_ENABLED=0, UE_MEMORY_TAGS_TRACE_ENABLED=0, UE_MEMORY_TRACE_ENABLED=0, UE_CALLSTACK_TRACE_ENABLED=0, UE_TRACE_ANALYSIS_DEBUG_API=0, UE_TRACE_ANALYSIS_DEBUG=0, UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=1
  - L11 `Type = TargetType.Program`
  - L12 `LaunchModuleName = "TraceTrimmer"`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L15 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L18 `bIsBuildingConsoleApplication = true`
  - L21 `bBuildDeveloperTools = false`
  - L23 `bBuildWithEditorOnlyData = false`
  - L28 `bCompileAgainstEngine = false`
  - L29 `bCompileAgainstCoreUObject = false`
  - L30 `bCompileAgainstApplicationCore = false`
  - L31 `bCompileICU = false`
  - L34 `bEnableTrace = false`

### `Source/Programs/UninstallHelper/UninstallHelper.Target.cs` (TargetRules)


#### class `UninstallHelperTarget` : `TargetRules`  
`public class UninstallHelperTarget : TargetRules`  
_L8-30_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)] [SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)]`
- L10 _ctor_ `public UninstallHelperTarget(TargetInfo Target) : base(Target)`
  - L12 `Type = TargetType.Program`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LinkType = TargetLinkType.Monolithic`
  - L15 `LaunchModuleName = "UninstallHelper"`
  - L18 `bBuildDeveloperTools = false`
  - L21 `bCompileAgainstEngine = false`
  - L22 `bCompileAgainstCoreUObject = false`
  - L23 `bCompileAgainstApplicationCore = false`
  - L24 `bBuildWithEditorOnlyData = false`
  - L25 `bCompileICU = false`
  - L28 `bIsBuildingConsoleApplication = true`

### `Source/Programs/UnrealAssetStringify/UnrealAssetStringify.Target.cs` (TargetRules)


#### class `UnrealAssetStringifyTarget` : `TargetRules`  
`public class UnrealAssetStringifyTarget : TargetRules`  
_L6-41_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UnrealAssetStringifyTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_SUPPORT_FULL_PACKAGEPATH=1, ALLOW_OTHER_PLATFORM_CONFIG=1, UE_INTERNAL_UNIVERSAL_PLACEHOLDERS=1, NOINITCRASHREPORTER=1, UE_TASKGRAPH_THREAD_LIMIT=5, UE_WITH_OBJECT_HANDLE_LATE_RESOLVE=0
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "UnrealAssetStringify"`
  - L14 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L18 `bCompileAgainstEngine = false`
  - L19 `bBuildDeveloperTools = false`
  - L20 `bCompileAgainstApplicationCore = false`
  - L21 `bBuildWithEditorOnlyData = true`
  - L22 `bCompileAgainstEditor = true`
  - L23 `bCompileAgainstCoreUObject = true`
  - L25 `bIsBuildingConsoleApplication = true`
  - L26 `bEnableTrace = true`

### `Source/Programs/UnrealBuildAccelerator/UbaAgent.Target.cs` (TargetRules)


#### class `UbaAgentTarget` : `TargetRules`  
`public class UbaAgentTarget : TargetRules`  
_L7-199_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L194 _ctor_ `public UbaAgentTarget(TargetInfo Target) : base(Target)`
  - L196 `LaunchModuleName = "UbaAgent"`
  - L197 call `CommonUbaSettings(this, Target)`
- L11 _method_ `public static void CommonUbaSettings(TargetRules Rules, TargetInfo Target, bool ShouldExport = false)`
  - **AdditionalLinkerArguments** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))`]:  /NODEFAULTLIB:kernel32.lib
  - **AdditionalLinkerArguments** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))`]:  mincore.lib
  - **AdditionalLinkerArguments** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux)) && if (!Rules.bShouldCompileAsDLL)`]:  -Wl,--no-export-dynamic
  - **Architectures** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (!Rules.Architectures.Contains(UnrealArch.X64))`]: UnrealArch.X64
  - **Architectures** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (!Rules.Architectures.Contains(UnrealArch.Arm64))`]: UnrealArch.Arm64
  - **GlobalDefinitions**: UBA_BUILD=1, UBA_BINARY=\"{BinaryName}\", UBA_USE_MIMALLOC={useMiMalloc}
  - **GlobalDefinitions** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))`]: UBA_DETOURS_LIBRARY=L\"UbaDetours.dll\", UBA_AGENT_EXECUTABLE=L\"UbaAgent.exe\", UBA_DETOURS_LIBRARY_ANSI=\"UbaDetours.dll\", UBA_DETOURS_LIBRARY_LINUX=\"libUbaDetours.so\"
  - **GlobalDefinitions** [`else`]: PLATFORM_WINDOWS=0
  - **GlobalDefinitions** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))`]: UBA_DETOURS_LIBRARY=\"libUbaDetours.so\", UBA_AGENT_EXECUTABLE=\"UbaAgent\", __NO_INLINE__
  - **GlobalDefinitions** [`else`]: PLATFORM_LINUX=0
  - **GlobalDefinitions** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple))`]: UBA_DETOURS_LIBRARY=\"libUbaDetours.dylib\", UBA_AGENT_EXECUTABLE=\"UbaAgent\", UBA_DETOURS_LIBRARY_LINUX=\"libUbaDetours.so\"
  - **GlobalDefinitions** [`else`]: PLATFORM_MAC=0
  - **GlobalDefinitions** [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows)) && if (ShouldExport)`]: UBA_API=__declspec(dllexport)
  - **GlobalDefinitions** [`else && if (ShouldExport)`]: UBA_API=__attribute__ ((visibility(\"default\")))
  - **GlobalDefinitions** [`if (!ShouldExport)`]: UBA_API=
  - **GlobalDefinitions** [`if (Target.Configuration == UnrealTargetConfiguration.Debug)`]: UBA_DEBUG=1
  - **GlobalDefinitions** [`else`]: UBA_DEBUG=0
  - L13 `Rules.Type = TargetType.Program`
  - L14 `Rules.IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L15 `Rules.LinkType = TargetLinkType.Monolithic`
  - L16 `Rules.bDeterministic = true`
  - L17 `Rules.bWarningsAsErrors = true`
  - L19 `Rules.UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L20 `Rules.bHasExports = false`
  - L22 `Rules.bRetainFramePointers = true`
  - L25 `Rules.bBuildDeveloperTools = false`
  - L29 `Rules.bBuildWithEditorOnlyData = false`
  - L32 `Rules.bCompileAgainstEngine = false`
  - L33 `Rules.bCompileAgainstCoreUObject = false`
  - L34 `Rules.bCompileAgainstApplicationCore = false`
  - L35 `Rules.bCompileICU = false`
  - L46 `Rules.bIsBuildingConsoleApplication = true`
  - L48 `Rules.WindowsPlatform.TargetWindowsVersion = 0x0A00`
  - L49 `Rules.WindowsPlatform.TargetWindowsMinorVersion = 0x0A000005`
  - L50 `Rules.bUseStaticCRT = true`
  - L52 `Rules.SolutionDirectory = "Programs/UnrealBuildAccelerator"`
  - L65 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))`] `BinaryName = $"{Rules.LaunchModuleName}{BinaryExt}"`
  - L66 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))`] `Rules.OutputFile = Path.Combine(BinariesFolder, Target.Architectures.SingleArchitecture.bIsX64 ? "x64" : "arm64", BinaryName)`
  - L74 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))`] `usingSanitizer = Rules.WindowsPlatform.bEnableAddressSanitizer`
  - L85 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))`] `BinaryName = $"{BinaryPrefix}{Rules.LaunchModuleName}{BinaryExt}"`
  - L86 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))`] `Rules.OutputFile = Path.Combine(BinariesFolder, BinaryName)`
  - L100 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))`] `usingSanitizer = Rules.LinuxPlatform.bEnableAddressSanitizer || Rules.LinuxPlatform.bEnableThreadSanitizer`
  - L121 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (Rules.LaunchModuleName != "UbaVisualizer")`] `BinaryName = $"{BinaryPrefix}{Rules.LaunchModuleName}{BinaryExt}"`
  - L122 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (Rules.LaunchModuleName != "UbaVisualizer")`] `Rules.OutputFile = Path.Combine(BinariesFolder, BinaryName)`
  - L126 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && else`] `Rules.ExeBinariesSubFolder = "UnrealBuildAccelerator"`
  - L147 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows) || (!Rules.bShouldCompileAsDLL && Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))) && if (Rules.bUsePCHFiles && !usingSanitizer)`] `useMiMalloc = 1`
  - L185 [`if (Target.Configuration == UnrealTargetConfiguration.Shipping)`] `Rules.bAllowLTCG = true`
  - L188 `Rules.WindowsPlatform.bSetResourceVersions = true`
  - L189 `Rules.BuildVersion = $"{UbaVersion}-{Rules.Version.Changelist}"`
  - L191 `Rules.CppCompileWarningSettings.CastFunctionTypeMismatchWarningLevel = WarningLevel.Off`

### `Source/Programs/UnrealBuildAccelerator/UbaCacheService.Target.cs` (TargetRules)


#### class `UbaCacheServiceTarget` : `TargetRules`  
`public class UbaCacheServiceTarget : TargetRules`  
_L6-13_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaCacheServiceTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaCacheService"`
  - L11 call `UbaAgentTarget.CommonUbaSettings(this, Target)`

### `Source/Programs/UnrealBuildAccelerator/UbaCli.Target.cs` (TargetRules)


#### class `UbaCliTarget` : `TargetRules`  
`public class UbaCliTarget : TargetRules`  
_L6-13_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaCliTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaCli"`
  - L11 call `UbaAgentTarget.CommonUbaSettings(this, Target)`

### `Source/Programs/UnrealBuildAccelerator/UbaCommon.Target.cs` (TargetRules)


#### class `UbaCommonTarget` : `TargetRules`  
`public class UbaCommonTarget : TargetRules`  
_L6-14_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaCommonTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaCommon"`
  - L11 `bShouldCompileAsDLL = true`
  - L12 call `UbaAgentTarget.CommonUbaSettings(this, Target)`

### `Source/Programs/UnrealBuildAccelerator/UbaCoordinatorHorde.Target.cs` (TargetRules)


#### class `UbaCoordinatorHordeTarget` : `TargetRules`  
`public class UbaCoordinatorHordeTarget : TargetRules`  
_L7-82_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public UbaCoordinatorHordeTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_EXTERNAL_PROFILING_ENABLED=0, STATS=0, ENABLE_STATNAMEDEVENTS=0, ALLOW_HITCH_DETECTION=0, UE_USE_MALLOC_FILL_BYTES=0, DISABLE_CWD_CHANGES=1, UE_NO_ENGINE_OIDC=0, UBA_COORDINATOR_HORDE_DLL
  - **GlobalDefinitions** [`else`]: PLATFORM_WINDOWS=0
  - **GlobalDefinitions** [`else`]: PLATFORM_MAC=0
  - **GlobalDefinitions** [`else`]: PLATFORM_LINUX=0
  - L11 `LaunchModuleName = "UbaCoordinatorHorde"`
  - L12 `bShouldCompileAsDLL = true`
  - L14 `Type = TargetType.Program`
  - L15 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L16 `LinkType = TargetLinkType.Monolithic`
  - L17 `bDeterministic = true`
  - L18 `bWarningsAsErrors = true`
  - L20 `UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
  - L21 `bHasExports = false`
  - L24 `bBuildDeveloperTools = false`
  - L28 `bBuildWithEditorOnlyData = false`
  - L31 `bCompileAgainstEngine = false`
  - L32 `bCompileAgainstCoreUObject = false`
  - L34 `bCompileICU = false`
  - L36 `bIsBuildingConsoleApplication = true`
  - L38 `WindowsPlatform.TargetWindowsVersion = 0x0A00`
  - L41 `SolutionDirectory = "Programs/UnrealBuildAccelerator"`
  - L47 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))`] `OutputFile = Path.Combine(BinariesFolder, Target.Architectures.SingleArchitecture.bIsX64 ? "x64" : "arm64", $"{LaunchModuleName}{".dll"}")`
  - L56 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple))`] `OutputFile = Path.Combine(BinariesFolder, $"lib{LaunchModuleName}.dylib")`
  - L65 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))`] `OutputFile = Path.Combine(BinariesFolder, $"lib{LaunchModuleName}.so")`

### `Source/Programs/UnrealBuildAccelerator/UbaCore.Target.cs` (TargetRules)


#### class `UbaCoreTarget` : `TargetRules`  
`public class UbaCoreTarget : TargetRules`  
_L6-15_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaCoreTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaCore"`
  - L11 `bShouldCompileAsDLL = true`
  - L12 call `UbaAgentTarget.CommonUbaSettings(this, Target)`
  - L13 `bDisableLinking = true`

### `Source/Programs/UnrealBuildAccelerator/UbaDetours.Target.cs` (TargetRules)


#### class `UbaDetoursTarget` : `TargetRules`  
`public class UbaDetoursTarget : TargetRules`  
_L6-39_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaDetoursTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES=0
  - L10 `LaunchModuleName = "UbaDetours"`
  - L11 `bShouldCompileAsDLL = true`
  - L12 call `UbaAgentTarget.CommonUbaSettings(this, Target)`
  - L18 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple))`] `bAllowLTCG = false`
  - L36 [`if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))`] `AdditionalLinkerArguments = "-Wl,-z,now"`

### `Source/Programs/UnrealBuildAccelerator/UbaHost.Target.cs` (TargetRules)


#### class `UbaHostTarget` : `TargetRules`  
`public class UbaHostTarget : TargetRules`  
_L6-14_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaHostTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaHost"`
  - L11 `bShouldCompileAsDLL = true`
  - L12 call `UbaAgentTarget.CommonUbaSettings(this, Target, true)`

### `Source/Programs/UnrealBuildAccelerator/UbaNinja.Target.cs` (TargetRules)


#### class `UbaNinjaTarget` : `TargetRules`  
`public class UbaNinjaTarget : TargetRules`  
_L6-13_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaNinjaTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaNinja"`
  - L11 call `UbaAgentTarget.CommonUbaSettings(this, Target)`

### `Source/Programs/UnrealBuildAccelerator/UbaObjTool.Target.cs` (TargetRules)


#### class `UbaObjToolTarget` : `TargetRules`  
`public class UbaObjToolTarget : TargetRules`  
_L6-13_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaObjToolTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaObjTool"`
  - L11 call `UbaAgentTarget.CommonUbaSettings(this, Target)`

### `Source/Programs/UnrealBuildAccelerator/UbaTest.Target.cs` (TargetRules)


#### class `UbaTestTarget` : `TargetRules`  
`public class UbaTestTarget : TargetRules`  
_L6-17_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaTestTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UBA_TEST_TARGET=1, UBA_BUILD_MACHINE={(AdditionalProperties.GetProperty(, ) == ,  ? ,  : , )}
  - L10 `LaunchModuleName = "UbaTest"`
  - L11 call `UbaAgentTarget.CommonUbaSettings(this, Target)`

### `Source/Programs/UnrealBuildAccelerator/UbaTestApp.Target.cs` (TargetRules)


#### class `UbaTestAppTarget` : `TargetRules`  
`public class UbaTestAppTarget : TargetRules`  
_L6-13_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UbaTestAppTarget(TargetInfo Target) : base(Target)`
  - L10 `LaunchModuleName = "UbaTestApp"`
  - L11 call `UbaAgentTarget.CommonUbaSettings(this, Target)`

### `Source/Programs/UnrealBuildAccelerator/UbaVisualizer.Target.cs` (TargetRules)


#### class `UbaVisualizerTarget` : `TargetRules`  
`public class UbaVisualizerTarget : TargetRules`  
_L5-14_
- L7 _ctor_ `public UbaVisualizerTarget(TargetInfo Target) : base(Target)`
  - L9 `LaunchModuleName = "UbaVisualizer"`
  - L10 call `UbaAgentTarget.CommonUbaSettings(this, Target)`
  - L11 `bIsBuildingConsoleApplication = false`
  - L12 `WindowsPlatform.ApplicationIcon = "Programs/UnrealBuildAccelerator/Visualizer/Resources/Windows/UbaVisualizer.ico"`

### `Source/Programs/UnrealFrontend/UnrealFrontend.Target.cs` (TargetRules)


#### class `UnrealFrontendTarget` : `TargetRules`  
`public class UnrealFrontendTarget : TargetRules`  
_L5-37_
- L7 _ctor_ `public UnrealFrontendTarget( TargetInfo Target ) : base(Target)`
  - **AdditionalPlugins**: UdpMessaging, ProjectLauncher
  - **GlobalDefinitions**: FORCE_USE_STATS=1
  - L9 `Type = TargetType.Program`
  - L10 `LinkType = TargetLinkType.Modular`
  - L11 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "UnrealFrontend"`
  - L18 `bCompileAgainstEngine = false`
  - L19 `bCompileAgainstCoreUObject = true`
  - L20 `bForceBuildTargetPlatforms = true`
  - L21 `bCompileWithStatsWithoutEngine = true`
  - L22 `bCompileWithPluginSupport = true`
  - L25 `bBuildDeveloperTools = true`
  - L27 `bHasExports = false`
  - L29 `bEnableTrace = true`

### `Source/Programs/UnrealInsights/UnrealInsights.Target.cs` (TargetRules)


#### class `UnrealInsightsTarget` : `TargetRules`  
`public class UnrealInsightsTarget : TargetRules`  
_L8-94_
- attrs: `[SupportedPlatforms("Win64", "Linux", "Mac")]`
- L19 _ctor_ `public UnrealInsightsTarget(TargetInfo Target) : base(Target)`
  - **ExtraModuleNames** [`if (bBuildEditor)`]: EditorStyle
  - **GlobalDefinitions**: UE_TRACE_SERVER_CONTROLS_ENABLED=1, UE_TRACE_SERVER_LAUNCH_ENABLED=1
  - **GlobalDefinitions** [`if (bEnableTrace)`]: UE_MEMORY_TRACE_AVAILABLE=1
  - **GlobalDefinitions** [`if (bEnableTrace)`]: UE_MEMORY_TAGS_TRACE_ENABLED=1
  - **GlobalDefinitions** [`if (bEnableTrace)`]: LLM_ENABLED_IN_CONFIG=1
  - **GlobalDefinitions** [`if (bTraceAnalysisDebug)`]: UE_TRACE_ANALYSIS_DEBUG_API=1
  - **GlobalDefinitions** [`if (bTraceAnalysisDebug)`]: UE_TRACE_ANALYSIS_DEBUG=1
  - **GlobalDefinitions** [`if (bTraceAnalysisDebug)`]: UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=4
  - **GlobalDefinitions** [`if (bTraceAnalysisDebug)`]: UE_TRACE_ANALYSIS_DEBUG_LEVEL=1
  - L21 `Type = TargetType.Program`
  - L22 `LinkType = bMonolithic ? TargetLinkType.Monolithic : TargetLinkType.Modular`
  - L23 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L25 `LaunchModuleName = "UnrealInsights"`
  - L30 `bCompileAgainstEngine = false`
  - L31 `bCompileAgainstCoreUObject = true`
  - L32 `bForceBuildTargetPlatforms = true`
  - L33 `bCompileWithStatsWithoutEngine = true`
  - L34 `bCompileWithPluginSupport = true`
  - L35 `bCompileAsioSSLSupport = true`
  - L38 `bIncludePluginsForTargetPlatforms = true`
  - L39 `bCompileICU = true`
  - L42 `bBuildDeveloperTools = true`
  - L51 `bHasExports = false`
  - L59 `bEnableTrace = bCmdLineTrace`

### `Source/Programs/UnrealLightmass/UnrealLightmass.Target.cs` (TargetRules)


#### class `UnrealLightmassTarget` : `TargetRules`  
`public class UnrealLightmassTarget : TargetRules`  
_L8-42_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)] [SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development)]`
- L10 _ctor_ `public UnrealLightmassTarget(TargetInfo Target) : base(Target)`
  - **AdditionalPlugins**: UdpMessaging
  - **GlobalDefinitions**: ALLOW_LOG_FILE=0
  - L12 `Type = TargetType.Program`
  - L13 `LinkType = TargetLinkType.Modular`
  - L14 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L16 `LaunchModuleName = "UnrealLightmass"`
  - L19 `bBuildDeveloperTools = false`
  - L22 `bBuildWithEditorOnlyData = true`
  - L25 `bCompileAgainstEngine = false`
  - L32 [`if (Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.Linux)`] `bCompileWithPluginSupport = true`
  - L33 [`if (Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.Linux)`] `bBuildDeveloperTools = true`
  - L37 `bIsBuildingConsoleApplication = true`

### `Source/Programs/UnrealMultiUserServer/UnrealMultiUserServer.Target.cs` (TargetRules)


#### class `UnrealMultiUserServerTarget` : `TargetRules`  
`public class UnrealMultiUserServerTarget : TargetRules`  
_L6-33_
- L8 _ctor_ `public UnrealMultiUserServerTarget(TargetInfo Target) : base(Target)`
  - **AdditionalPlugins**: UdpMessaging, QuicMessaging, ConcertSyncServer
  - **GlobalDefinitions**: UE_LOG_CONCERT_DEBUG_VERBOSITY_LEVEL=Log
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Modular`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "UnrealMultiUserServer"`
  - L19 `bCompileAgainstCoreUObject = true`
  - L20 `bCompileAgainstEngine = false`
  - L21 `bBuildWithEditorOnlyData = false`
  - L24 `bCompileWithPluginSupport = true`
  - L25 `bBuildDeveloperTools = true`
  - L28 `bIsBuildingConsoleApplication = Target.Platform != UnrealTargetPlatform.Mac`
  - L31 `bEnableTrace = true`

### `Source/Programs/UnrealMultiUserSlateServer/UnrealMultiUserSlateServer.Target.cs` (TargetRules)


#### class `UnrealMultiUserSlateServerTarget` : `TargetRules`  
`public class UnrealMultiUserSlateServerTarget : TargetRules`  
_L6-32_
- L8 _ctor_ `public UnrealMultiUserSlateServerTarget(TargetInfo Target) : base(Target)`
  - **AdditionalPlugins**: UdpMessaging, QuicMessaging, ConcertSyncServer, MultiUserServer
  - **GlobalDefinitions**: UE_LOG_CONCERT_DEBUG_VERBOSITY_LEVEL=Log
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Modular`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "UnrealMultiUserSlateServer"`
  - L20 `bCompileAgainstCoreUObject = true`
  - L21 `bCompileAgainstEngine = false`
  - L22 `bBuildWithEditorOnlyData = false`
  - L25 `bCompileWithPluginSupport = true`
  - L26 `bBuildDeveloperTools = true`
  - L27 `bIsBuildingConsoleApplication = false`
  - L30 `bEnableTrace = true`

### `Source/Programs/UnrealObjectPtrTool/UnrealObjectPtrTool.Target.cs` (TargetRules)


#### class `UnrealObjectPtrToolTarget` : `TargetRules`  
`public class UnrealObjectPtrToolTarget : TargetRules`  
_L7-24_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public UnrealObjectPtrToolTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Modular`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LaunchModuleName = "UnrealObjectPtrTool"`
  - L16 `bBuildDeveloperTools = false`
  - L17 `bBuildWithEditorOnlyData = false`
  - L18 `bCompileAgainstEngine = false`
  - L19 `bCompileAgainstCoreUObject = false`
  - L20 `bCompileAgainstApplicationCore = false`
  - L21 `bUsesSlate = false`
  - L22 `bIsBuildingConsoleApplication = true`

### `Source/Programs/UnrealPackageTool/UnrealPackageTool.Target.cs` (TargetRules)


#### class `UnrealPackageToolTarget` : `TargetRules`  
`public class UnrealPackageToolTarget : TargetRules`  
_L6-33_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public UnrealPackageToolTarget(TargetInfo Target) : base(Target)`
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "UnrealPackageTool"`
  - L14 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L17 `bForceEnableRTTI = true`
  - L18 `bForceEnableExceptions = true`
  - L20 `bBuildDeveloperTools = false`
  - L21 `bBuildWithEditorOnlyData = true`
  - L24 `bCompileAgainstApplicationCore = true`
  - L25 `bCompileAgainstCoreUObject = true`
  - L26 `bCompileAgainstEngine = false`
  - L27 `bCompileICU = false`
  - L29 `bIsBuildingConsoleApplication = true`
  - L31 `bEnableTrace = true`

### `Source/Programs/UnrealPak/UnrealPak.Target.cs` (TargetRules)


#### class `UnrealPakTarget` : `TargetRules`  
`public class UnrealPakTarget : TargetRules`  
_L6-48_
- L8 _ctor_ `public UnrealPakTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_EXTERNAL_PROFILING_ENABLED=0, ALLOW_OTHER_PLATFORM_CONFIG=1
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Modular`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "UnrealPak"`
  - L15 `bUseXGEController = false`
  - L16 `bCompileFreeType = false`
  - L17 `bLoggingToMemoryEnabled = false`
  - L18 `bUseLoggingInShipping = true`
  - L19 `bCompileWithAccessibilitySupport = false`
  - L20 `bCompileWithPluginSupport = true`
  - L21 `bIncludePluginsForTargetPlatforms = true`
  - L22 `bWithServerCode = false`
  - L23 `bCompileNavmeshClusterLinks = false`
  - L24 `bCompileNavmeshSegmentLinks = false`
  - L25 `bCompileRecast = false`
  - L26 `bCompileICU = false`
  - L27 `bWithLiveCoding = false`
  - L28 `bBuildDeveloperTools = false`
  - L29 `bBuildWithEditorOnlyData = true`
  - L30 `bCompileAgainstEngine = false`
  - L31 `bCompileAgainstCoreUObject = true`
  - L32 `bCompileAgainstApplicationCore = true`
  - L33 `bUsesSlate = false`
  - L34 `bIsBuildingConsoleApplication = true`
  - L35 `bForceBuildTargetPlatforms = true`
  - L36 `bNeedsExtraShaderFormats = true`
  - L37 `bAreTargetSDKVersionsRelevantOverride = false`
  - L39 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L40 `WindowsPlatform.bPixProfilingEnabled = false`
  - L41 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L42 `WindowsPlatform.bStripUnreferencedSymbols = true`
  - L44 `bEnableTrace = true`

### `Source/Programs/UnrealRecoverySvc/UnrealRecoverySvc.Target.cs` (TargetRules)


#### class `UnrealRecoverySvcTarget` : `TargetRules`  
`public class UnrealRecoverySvcTarget : TargetRules`  
_L6-26_
- L8 _ctor_ `public UnrealRecoverySvcTarget(TargetInfo Target) : base(Target)`
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `LaunchModuleName = "UnrealRecoverySvc"`
  - L15 `bCompileAgainstCoreUObject = true`
  - L16 `bCompileAgainstEngine = false`
  - L17 `bBuildWithEditorOnlyData = false`
  - L20 `bCompileWithPluginSupport = true`
  - L21 `bBuildDeveloperTools = true`
  - L24 `bIsBuildingConsoleApplication = true`

### `Source/Programs/UnrealVersionSelector/UnrealVersionSelector.Target.cs` (TargetRules)


#### class `UnrealVersionSelectorTarget` : `TargetRules`  
`public class UnrealVersionSelectorTarget : TargetRules`  
_L6-32_
- L8 _ctor_ `public UnrealVersionSelectorTarget(TargetInfo Target) : base(Target)`
  - **ExtraModuleNames** [`if (bUsingSlate && bBuildEditor)`]: EditorStyle
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "UnrealVersionSelector"`
  - L15 `bBuildDeveloperTools = false`
  - L24 `bCompileICU = false`
  - L26 `bBuildWithEditorOnlyData = bUsingSlate`
  - L29 `bCompileAgainstEngine = false`
  - L30 `bCompileAgainstCoreUObject = bUsingSlate`

### `Source/Programs/UnrealVirtualizationTool/UnrealVirtualizationTool.Target.cs` (TargetRules)


#### class `UnrealVirtualizationToolTarget` : `TargetRules`  
`public class UnrealVirtualizationToolTarget : TargetRules`  
_L6-46_
- L8 _ctor_ `public UnrealVirtualizationToolTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: UE_SUPPORT_FULL_PACKAGEPATH=1
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LaunchModuleName = "UnrealVirtualizationTool"`
  - L16 `bBuildDeveloperTools = false`
  - L18 `bCompileAgainstEditor = false`
  - L19 `bBuildWithEditorOnlyData = true`
  - L22 `bCompileAgainstApplicationCore = true`
  - L23 `bCompileAgainstCoreUObject = true`
  - L24 `bCompileAgainstEngine = false`
  - L25 `bUsesSlate = false`
  - L28 `bCompileFreeType = false`
  - L29 `bCompileICU = false`
  - L32 `bIsBuildingConsoleApplication = true`
  - L35 `bCompileWithPluginSupport = true`
  - L38 `WindowsPlatform.bStripUnreferencedSymbols = true`
  - L39 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L40 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L41 `WindowsPlatform.bPixProfilingEnabled = false`
  - L43 `bEnableTrace = true`

### `Source/Programs/Unsync/Unsync.Target.cs` (TargetRules)


#### class `UnsyncTarget` : `TargetRules`  
`public class UnsyncTarget : TargetRules`  
_L6-25_
- L8 _ctor_ `public UnsyncTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: _CRT_SECURE_NO_WARNINGS
  - L10 `Name = "unsync"`
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "Unsync"`
  - L14 `bBuildDeveloperTools = false`
  - L15 `bCompileICU = false`
  - L16 `bBuildWithEditorOnlyData = false`
  - L17 `bCompileAgainstEngine = false`
  - L18 `bCompileAgainstCoreUObject = false`
  - L19 `bEnforceIWYU = false`
  - L21 `WindowsPlatform.TargetWindowsVersion = 0x0603`
  - L22 `bUseStaticCRT = true`
  - L23 `bIsBuildingConsoleApplication = true`

### `Source/Programs/VirtualProduction/TextureShare/TextureShareSDK.Target.cs` (TargetRules)


#### class `TextureShareSDKTarget` : `TargetRules`  
`public class TextureShareSDKTarget : TargetRules`  
_L9-93_
- attrs: `[SupportedPlatforms("Win64")]`
- L47 _ctor_ `public TextureShareSDKTarget(TargetInfo Target) : base(Target)`
  - L50 `DefaultBuildSettings = BuildSettingsVersion.Latest`
  - L51 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L53 `Type = TargetType.Program`
  - L54 `LinkType = TargetLinkType.Monolithic`
  - L57 `bShouldCompileAsDLL = true`
  - L59 `ExeBinariesSubFolder = @"TextureShareSDK"`
  - L61 `SolutionDirectory = "Programs/VirtualProduction/TextureShare"`
  - L62 `LaunchModuleName = "TextureShareSDK"`
  - L65 `bBuildDeveloperTools = false`
  - L67 `bBuildWithEditorOnlyData = false`
  - L70 `bCompileAgainstEngine = false`
  - L71 `bCompileAgainstCoreUObject = false`
  - L74 `bUseLoggingInShipping = true`
  - L75 `bUseChecksInShipping = true`
  - L78 `bCompileICU = false`
  - L80 `bUsesSlate = false`
  - L83 `bHasExports = true`
  - L86 `bBuildInSolutionByDefault = false`
  - L90 [`if (Platform == UnrealTargetPlatform.Win64)`] call `AddWindowsPostBuildSteps()`
- L11 _method_ `private void ImplPostBuildCopy(string SrcPath, string DestPath)`
  - **PostBuildSteps**: echo Copying {0} to {1}, xcopy /y /i /v \"{0}\" \"{1}\" 1>nul
- L17 _method_ `private void AddWindowsPostBuildSteps()`
  - L26 call `ImplPostBuildCopy(Path.Combine(SDKSrcPath, "Public", "*.h"), Path.Combine(SDKHeadersDestPath))`
  - L27 call `ImplPostBuildCopy(Path.Combine(SDKSrcPath, "Public", "Serialize", "*.h"), Path.Combine(SDKHeadersDestPath, "Serialize"))`
  - L28 call `ImplPostBuildCopy(Path.Combine(SDKSrcPath, "Public", "Containers", "*.h"), Path.Combine(SDKHeadersDestPath, "Containers"))`
  - L29 call `ImplPostBuildCopy(Path.Combine(SDKSrcPath, "Public", "Containers/UnrealEngine", "*.h"), Path.Combine(SDKHeadersDestPath, "Containers", "UnrealEngine"))`
  - L33 call `ImplPostBuildCopy(Path.Combine(MainPluginSrcPath, "Source/TextureShare/Private", "Misc", "*.h"), Path.Combine(SDKHeadersDestPath, "Misc"))`
  - L34 call `ImplPostBuildCopy(Path.Combine(MainPluginSrcPath, "Source/TextureShareCore/Private", "Misc", "*.h"), Path.Combine(SDKHeadersDestPath, "Misc"))`
  - L35 call `ImplPostBuildCopy(Path.Combine(MainPluginSrcPath, "Source/TextureShareCore/Private", "Containers", "*.h"), Path.Combine(SDKHeadersDestPath, "Containers"))`
  - L36 call `ImplPostBuildCopy(Path.Combine(MainPluginSrcPath, "Source/TextureShareCore/Private", "Serialize", "*.h"), Path.Combine(SDKHeadersDestPath, "Serialize"))`
  - L38 call `ImplPostBuildCopy(Path.Combine(MainPluginSrcPath, "Source/TextureShareDisplayCluster/Private", "Misc", "*.h"), Path.Combine(SDKHeadersDestPath, "Misc"))`
  - L44 call `ImplPostBuildCopy(Path.Combine(SDKBinariesSrcPath, "*.*"), SDKBinariesDestPath)`

### `Source/Programs/WebTestsServerCpp/WebTestsServerCpp.Target.cs` (TargetRules)


#### class `WebTestsServerCppTarget` : `TargetRules`  
`public class WebTestsServerCppTarget : TargetRules`  
_L6-22_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public WebTestsServerCppTarget(TargetInfo Target) : base(Target)`
  - L10 `Type = TargetType.Program`
  - L11 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `LaunchModuleName = "WebTestsServerCpp"`
  - L15 `bBuildDeveloperTools = false`
  - L16 `bCompileAgainstEngine = false`
  - L17 `bCompileAgainstCoreUObject = false`
  - L18 `bCompileAgainstApplicationCore = true`
  - L19 `bCompileICU = false`
  - L20 `bIsBuildingConsoleApplication = true`

### `Source/Programs/Windows/ASDTool/ASDTool.Target.cs` (TargetRules)


#### class `ASDToolTarget` : `TargetRules`  
`public class ASDToolTarget : TargetRules`  
_L6-45_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Editor)]`
- L8 _ctor_ `public ASDToolTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: SQLITE_OS_OTHER=0, SQLITE_OS_WIN=1, AUTOSDKS_ENABLED=0
  - L10 `Type = TargetType.Program`
  - L11 `LinkType = TargetLinkType.Monolithic`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LaunchModuleName = "ASDTool"`
  - L15 `bBuildDeveloperTools = false`
  - L18 `bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && bDebugOrDevelopment`
  - L20 `bCompileAgainstEngine = false`
  - L21 `bCompileAgainstCoreUObject = false`
  - L22 `bCompileAgainstApplicationCore = true`
  - L23 `bCompileICU = false`
  - L25 `bIsBuildingConsoleApplication = true`
  - L27 `bForceCompileDevelopmentAutomationTests = false`
  - L28 `bCompileWithStatsWithoutEngine = false`
  - L30 `bUseLoggingInShipping = true`
  - L31 `bLegalToDistributeBinary = true`
  - L33 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L34 `WindowsPlatform.bPixProfilingEnabled = false`
  - L35 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L36 `WindowsPlatform.bStripUnreferencedSymbols = true`
  - L39 `bCompileCustomSQLitePlatform = false`

### `Source/Programs/Windows/BootstrapPackagedGame/BootstrapPackagedGame.Target.cs` (TargetRules)


#### class `BootstrapPackagedGameTarget` : `TargetRules`  
`public class BootstrapPackagedGameTarget : TargetRules`  
_L8-34_
- attrs: `[SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)] [SupportedPlatforms("Win64")]`
- L10 _ctor_ `public BootstrapPackagedGameTarget(TargetInfo Target) : base(Target)`
  - L12 `Type = TargetType.Program`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L15 `LaunchModuleName = "BootstrapPackagedGame"`
  - L17 `bUseStaticCRT = true`
  - L19 `bUseSharedPCHs = false`
  - L22 `bBuildDeveloperTools = false`
  - L23 `bCompileICU = false`
  - L24 `bBuildWithEditorOnlyData = false`
  - L25 `bCompileAgainstEngine = false`
  - L26 `bCompileAgainstCoreUObject = false`

### `Source/Programs/ZenDashboard/ZenDashboard.Target.cs` (TargetRules)


#### class `ZenDashboardTarget` : `TargetRules`  
`public class ZenDashboardTarget : TargetRules`  
_L7-44_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public ZenDashboardTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions**: WITH_AUTOMATION_TESTS=0, WITH_AUTOMATION_WORKER=0
  - L11 `Type = TargetType.Program`
  - L12 `LinkType = TargetLinkType.Monolithic`
  - L13 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L14 `LaunchModuleName = "ZenDashboard"`
  - L16 `bUseXGEController = false`
  - L17 `bLoggingToMemoryEnabled = true`
  - L18 `bUseLoggingInShipping = true`
  - L19 `bCompileWithAccessibilitySupport = false`
  - L20 `bWithServerCode = false`
  - L21 `bCompileNavmeshClusterLinks = false`
  - L22 `bCompileNavmeshSegmentLinks = false`
  - L23 `bCompileRecast = false`
  - L24 `bCompileICU = false`
  - L25 `bWithLiveCoding = false`
  - L26 `bBuildDeveloperTools = false`
  - L27 `bBuildWithEditorOnlyData = false`
  - L28 `bCompileAgainstEngine = false`
  - L29 `bCompileAgainstCoreUObject = true`
  - L30 `bCompileAgainstApplicationCore = true`
  - L31 `bUsesSlate = true`
  - L32 `bForceDisableAutomationTests = true`
  - L34 `bIsBuildingConsoleApplication = false`
  - L36 `WindowsPlatform.bUseBundledDbgHelp = false`
  - L37 `WindowsPlatform.bPixProfilingEnabled = false`
  - L38 `WindowsPlatform.bMergeIdenticalCOMDATs = true`
  - L39 `WindowsPlatform.bStripUnreferencedSymbols = true`

### `Source/Programs/ZenLaunch/ZenLaunch.Target.cs` (TargetRules)


#### class `ZenLaunchTarget` : `TargetRules`  
`public class ZenLaunchTarget : TargetRules`  
_L7-37_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L9 _ctor_ `public ZenLaunchTarget(TargetInfo Target) : base(Target)`
  - L11 `Type = TargetType.Program`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `LinkType = TargetLinkType.Monolithic`
  - L14 `LaunchModuleName = "ZenLaunch"`
  - L17 `bBuildDeveloperTools = false`
  - L20 `bBuildWithEditorOnlyData = true`
  - L23 `bCompileAgainstEngine = false`
  - L24 `bCompileAgainstCoreUObject = false`
  - L25 `bCompileAgainstApplicationCore = false`
  - L26 `bCompileICU = false`
  - L35 `bIsBuildingConsoleApplication = true`

### `Source/Programs/ZenOplogDiffTool/ZenOplogDiffTool.Target.cs` (TargetRules)


#### class `ZenOplogDiffToolTarget` : `TargetRules`  
`public class ZenOplogDiffToolTarget : TargetRules`  
_L6-32_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Desktop)]`
- L8 _ctor_ `public ZenOplogDiffToolTarget(TargetInfo Target) : base(Target)`
  - **GlobalDefinitions** [`if (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development)`]: LLM_ENABLED_IN_CONFIG=1
  - **GlobalDefinitions** [`if (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development)`]: UE_MEMORY_TAGS_TRACE_ENABLED=1
  - L10 `Type = TargetType.Program`
  - L11 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L12 `LinkType = TargetLinkType.Modular`
  - L13 `LaunchModuleName = "ZenOplogDiffTool"`
  - L15 `bBuildDeveloperTools = false`
  - L16 `bCompileAgainstApplicationCore = true`
  - L17 `bCompileAgainstCoreUObject = false`
  - L18 `bCompileAgainstEngine = false`
  - L19 `bCompileICU = false`
  - L20 `bForceDisableAutomationTests = true`
  - L21 `bIsBuildingConsoleApplication = true`
  - L22 `bUseLoggingInShipping = true`
  - L29 [`if (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development)`] `bEnableTrace = true`

### `Source/UnrealClient.Target.cs` (TargetRules)


#### class `UnrealClientTarget` : `TargetRules`  
`public class UnrealClientTarget : TargetRules`  
_L6-15_
- L8 _ctor_ `public UnrealClientTarget(TargetInfo Target) : base(Target)`
  - **ExtraModuleNames**: UnrealGame
  - L10 `Type = TargetType.Client`
  - L11 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L12 `BuildEnvironment = TargetBuildEnvironment.Shared`

### `Source/UnrealEditor.Target.cs` (TargetRules)


#### class `UnrealEditorTarget` : `TargetRules`  
`public class UnrealEditorTarget : TargetRules`  
_L6-16_
- L8 _ctor_ `public UnrealEditorTarget( TargetInfo Target ) : base(Target)`
  - **ExtraModuleNames**: UnrealGame
  - L10 `Type = TargetType.Editor`
  - L11 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L12 `BuildEnvironment = TargetBuildEnvironment.Shared`
  - L13 `bBuildAllModules = true`

### `Source/UnrealGame.Target.cs` (TargetRules)


#### class `UnrealGameTarget` : `TargetRules`  
`public class UnrealGameTarget : TargetRules`  
_L7-17_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.All)]`
- L9 _ctor_ `public UnrealGameTarget( TargetInfo Target ) : base(Target)`
  - **ExtraModuleNames**: UnrealGame
  - L11 `Type = TargetType.Game`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `BuildEnvironment = TargetBuildEnvironment.Shared`

### `Source/UnrealServer.Target.cs` (TargetRules)


#### class `UnrealServerTarget` : `TargetRules`  
`public class UnrealServerTarget : TargetRules`  
_L7-16_
- attrs: `[SupportedPlatforms(UnrealPlatformClass.Server)]`
- L9 _ctor_ `public UnrealServerTarget(TargetInfo Target) : base(Target)`
  - **ExtraModuleNames**: UnrealGame
  - L11 `Type = TargetType.Server`
  - L12 `IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
  - L13 `BuildEnvironment = TargetBuildEnvironment.Shared`
