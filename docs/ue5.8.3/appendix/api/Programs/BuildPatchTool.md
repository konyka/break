# Programs / BuildPatchTool

- module root: `Source/Programs/BuildPatchTool`
- headers: 19; symbols: 183
- symbol kinds: class=5, delegate=1, enum=2, enumerator=18, function=27, macro=39, member=36, namespace=6, prototype=21, struct=17, typedef=2, variable=9
- PrivateDependencyModuleNames: BuildPatchServices, Core, CoreUObject, HTTP, Networking, Projects

### `Source/Programs/BuildPatchTool/Private/Common/VerboseLogging.h` (Private)


#### Free symbols / members of external scopes

- L4 _prototype_ `void SetupVerboseLogging(bool bVerboseLogsSpecified);`

### `Source/Programs/BuildPatchTool/Private/ToolModes/ToolModesHelp.h` (Private)


#### struct `BuildPatchTool::FBptBaseToolModeHelp`  
`struct FBptBaseToolModeHelp`  
_L9-13_
- L11 _public member_ `static const TCHAR* Text[];`
- L12 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FDiffManifestToolModeHelp`  
`struct FDiffManifestToolModeHelp`  
_L15-19_
- L17 _public member_ `static const TCHAR* Text[];`
- L18 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FChunkDirectoryToolModeHelp`  
`struct FChunkDirectoryToolModeHelp`  
_L21-25_
- L23 _public member_ `static const TCHAR* Text[];`
- L24 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FAutomationToolModeHelp`  
`struct FAutomationToolModeHelp`  
_L27-31_
- L29 _public member_ `static const TCHAR* Text[];`
- L30 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FChunkDeltaOptimiseModeHelp`  
`struct FChunkDeltaOptimiseModeHelp`  
_L33-37_
- L35 _public member_ `static const TCHAR* Text[];`
- L36 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FCompactifyToolModeHelp`  
`struct FCompactifyToolModeHelp`  
_L39-43_
- L41 _public member_ `static const TCHAR* Text[];`
- L42 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FEnumerationToolModeHelp`  
`struct FEnumerationToolModeHelp`  
_L45-49_
- L47 _public member_ `static const TCHAR* Text[];`
- L48 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FExtractMetadataToolModeHelp`  
`struct FExtractMetadataToolModeHelp`  
_L51-55_
- L53 _public member_ `static const TCHAR* Text[];`
- L54 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FInstallManifestToolModeHelp`  
`struct FInstallManifestToolModeHelp`  
_L57-61_
- L59 _public member_ `static const TCHAR* Text[];`
- L60 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FMergeManifestToolModeHelp`  
`struct FMergeManifestToolModeHelp`  
_L63-67_
- L65 _public member_ `static const TCHAR* Text[];`
- L66 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FPackageChunksToolModeHelp`  
`struct FPackageChunksToolModeHelp`  
_L69-73_
- L71 _public member_ `static const TCHAR* Text[];`
- L72 _public member_ `static const int32 NumLines;`

#### struct `BuildPatchTool::FVerifyChunksToolModeHelp`  
`struct FVerifyChunksToolModeHelp`  
_L75-79_
- L77 _public member_ `static const TCHAR* Text[];`
- L78 _public member_ `static const int32 NumLines;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchTool`

### `Source/Programs/BuildPatchTool/Public/BuildPatchTool.h` (Public)


#### enum `BuildPatchTool::EReturnCode`  
`enum class EReturnCode : int32`  
_L10-31_
- L12 _public enumerator_ `OK = 0`
- L13 _public enumerator_ `UnknownError`
- L14 _public enumerator_ `ArgumentProcessingError`
- L15 _public enumerator_ `UnknownToolMode`
- L16 _public enumerator_ `FileNotFound`
- L17 _public enumerator_ `ToolFailure`
- L18 _public enumerator_ `OnlineMcpError`
- L19 _public enumerator_ `DeprecatedVersion`
- L20 _public enumerator_ `DirectoryNotFound`
- L21 _public enumerator_ `MissingCredentials`
- L22 _public enumerator_ `InvalidCredentials`
- L23 _public enumerator_ `InvalidData`
- L26 _public enumerator_ `LastPlusOne` — !! Always after the last code, signifies the last return code plus 1 to allow the following Last alias.
- L28 _public enumerator_ `Last = (LastPlusOne - 1)` — An alias for the actual last return code.
- L30 _public enumerator_ `Crash = 255`

#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuildPatchTool, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuildPatchTool, Log, All);`
- L8 _namespace_ `namespace BuildPatchTool`
- L34 _namespace_ `namespace CommandLineHelpers`
- L36 _prototype_ `bool ParseSwitch(const TCHAR* InSwitch, FString& Value, const TArray<FString>& Switches);` (scope `CommandLineHelpers`)
- L39 _function_ `inline const TCHAR* LexToString(BuildPatchTool::EReturnCode ReturnCode)`
- L42 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchTool::EReturnCode::Value: return TEXT(#Value)`

### `Source/Programs/BuildPatchTool/Public/BuildPatchToolVersion.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define BUILDPATCHTOOL_MAJOR_VERSION 1` — Change the following three defines to set the version of BuildPatchTool
- L6 _macro_ `#define BUILDPATCHTOOL_MINOR_VERSION 9`
- L7 _macro_ `#define BUILDPATCHTOOL_PATCH_VERSION 0`
- L14 _macro_ `#define VERSION_TEXT(x) TEXT(x)` — Macros for encoding strings
- L15 _macro_ `#define VERSION_STRINGIFY_2(x) VERSION_TEXT(#x)`
- L16 _macro_ `#define VERSION_STRINGIFY(x) VERSION_STRINGIFY_2(x)`
- L19 _macro_ `#define BUILDPATCHTOOL_VERSION_STRING \` — Macro to build up full major.minor.patch version string for BuildPatchTool

### `Source/Programs/BuildPatchTool/Public/Common/CmdLineProcessor.h` (Public)


#### class `FCmdLineProcessor`  
`class FCmdLineProcessor`  
_L299-342_
- L302 _public prototype_ `FCmdLineProcessor(int32 ArgC, TCHAR* ArgV[], const FString& WorkingDirectory, TFunction<void(const FString&)> ErrorLogger);`
- L304 _public prototype_ `bool ContainsFlag(const TCHAR* Flag) const;`
- L306 _public prototype_ `bool ContainsSwitch(const TCHAR* Switch) const;`
- L308 _public prototype_ `bool GetSwitchValue(const TCHAR* Switch, FString& OutValue) const;`
- L310 _public prototype_ `const FString& GetOriginalCommandLine();`
- L312 _public prototype_ `FString GetEngineString();`
- L314 _public prototype_ `void ProcessDragAndDrop();`
- L316 _public prototype_ `bool ProcessCommandlineFiles();`
- L318 _public prototype_ `bool HandleLegacyCommandline();`
- L320 _public prototype_ `bool ConvertCommandlinePaths();`
- L322 _public prototype_ `void AddDesiredEngineFlags();`
- L325 _public function_ `static inline bool IsEmpty(const FString& Val)` — Helpers for BPT_MODE_COMMANDLINE macros.
- L326 _public function_ `static inline bool ExceedsSize(const FString& Val, int32 Max)`
- L329 _private member_ `const FString WorkingDirectory;`
- L330 _private member_ `TFunction<void(const FString&)> ErrorLogger;`
- L331 _private member_ `FString OriginalCommandLine;`
- L332 _private member_ `TArray<FString> Tokens;`
- L334 _private member_ `const TArray<FString> PathParamsToMakeAbsolute = { TEXT("-CloudDir="), TEXT("-ManifestA="), TEXT("-ManifestB="), TEXT("-ManifestC="), TEXT("-DownloadCloudDirectory="), TEXT("-ResultDataFile="), TEXT("-BuildRoot="), TEXT("-CloudDirs="), TEXT("-OutputFile="), TEXT("-File="), TEXT("-MergeFileList="), TEXT("-PrevManifestFile="), TEXT("-ManifestFile="), TEXT("-SearchPath="), TEXT("-InputFile="), TEXT("-Manifest="), TEXT("-OutputDir="), TEXT("-DeletedChunkLo`
- L340 _private member_ `const TArray<FString> PathParamsToCollapseRelativeDirectories = { TEXT("-AppL`

#### Free symbols / members of external scopes

- L9 _macro_ `#define BPT_DECLARE_COMMANDLINE(TConfig) \`
- L14 _macro_ `#define BPT_COMMANDLINE_START(TClass) \`
- L27 _macro_ `#define BPT_ARG_REQUIRED_SWITCH(Switch) \`
- L35 _macro_ `#define BPT_ARG_REQUIRED_SWITCH_PAIRS(Key, Val, Map) \`
- L52 _macro_ `#define BPT_ARG_OPTIONAL_SWITCH_PAIRS(Key, Val, Map) \`
- L64 _macro_ `#define BPT_ARG_REQUIRED_SWITCH_NOEMPTY_ALIAS(Switch, VarName) \`
- L77 _macro_ `#define BPT_ARG_REQUIRED_SWITCH_NOEMPTY(Switch) BPT_ARG_REQUIRED_SWITCH_NOEMPTY_ALIAS(Switch, Switch)`
- L79 _macro_ `#define BPT_ARG_REQUIRED_FILENAME(Switch) \`
- L102 _macro_ `#define BPT_ARG_REQUIRED_FILENAME_EXISTS(Switch) \`
- L110 _macro_ `#define BPT_ARG_OPTIONAL_FILENAME(Switch) \`
- L125 _macro_ `#define BPT_ARG_OPTIONAL_FILENAME_EXISTS(Switch) \`
- L133 _macro_ `#define BPT_ARG_REQUIRED_PATH(Switch) \`
- L155 _macro_ `#define BPT_ARG_REQUIRED_PATH_NOEMPTY(Switch) \`
- L168 _macro_ `#define BPT_ARG_REQUIRED_SWITCH_MAXSIZE(Switch, MaxSize) \`
- L186 _macro_ `#define BPT_ARG_UNEXPECTED_SWITCH(Switch) \`
- L193 _macro_ `#define BPT_ARG_OPTIONAL_SWITCH(Switch) \`
- L196 _macro_ `#define BPT_ARG_OPTIONAL_SWITCH_INT32(Switch) \`
- L199 _macro_ `#define BPT_ARG_OPTIONAL_SWITCH_NOEMPTY(Switch) \`
- L207 _macro_ `#define BPT_ARG_OPTIONAL_SWITCH_CLAMPED(Switch, TInt, Min, Max) \`
- L221 _macro_ `#define BPT_ARG_OPTIONAL_SWITCH_MULTI(Switch) \`
- L224 _macro_ `#define BPT_ARG_OPTION(Option) \`
- L227 _macro_ `#define BPT_ARG_OPTION_MEMBER(Option) \`
- L230 _macro_ `#define BPT_ARG_FEATURELEVEL_OPTIONAL_ALIAS(Switch) \`
- L250 _macro_ `#define BPT_ARG_FEATURELEVEL_OPTIONAL BPT_ARG_FEATURELEVEL_OPTIONAL_ALIAS(FeatureLevel) \`
- L252 _macro_ `#define BPT_ARG_FEATURELEVEL_REQUIRED \`
- L283 _macro_ `#define BPT_ARG_DIFFABORTTHRESHOLD_OPTIONAL \`
- L286 _macro_ `#define BPT_COMMANDLINE_FAIL_IF_TCHAR(Condition, ErrorStr) \`
- L292 _macro_ `#define BPT_COMMANDLINE_FAIL_IF(Condition, ErrorStr) \`
- L295 _macro_ `#define BPT_COMMANDLINE_END \`

### `Source/Programs/BuildPatchTool/Public/Common/DiffAbortThresholdArgument.h` (Public)


#### class `BuildPatchTool::FDiffAbortThresholdArgument`  
`class FDiffAbortThresholdArgument`  
_L7-13_
- L10 _public prototype_ `static TOptional<BuildPatchServices::FDiffAbortThreshold> Parse(BuildPatchTool::IToolMode& ToolMode, const TArray<FString>& Switches);`
- L12 _private prototype_ `static BuildPatchServices::FDiffAbortThreshold ClampToSaneRange(const FString& DiffAbortThresholdRaw, const BuildPatchServices::FDiffAbortThreshold& DiffAbortThreshold);`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace BuildPatchTool`

### `Source/Programs/BuildPatchTool/Public/Common/MetadataSerialiser.h` (Public)


#### enum `EMetadataOutputFormat`  
`enum class EMetadataOutputFormat`  
_L6-11_
- L8 _public enumerator_ `Human = 0`
- L9 _public enumerator_ `Json`
- L10 _public enumerator_ `InvalidOrMax`

#### class `FMetadataSerialiser`  
`class FMetadataSerialiser`  
_L15-19_
- L18 _public prototype_ `static FString SerialiseMetadata(const IBuildManifest& Manifest, EMetadataOutputFormat OutputFormat);`

#### Free symbols / members of external scopes

- L13 _prototype_ `bool LexFromString(EMetadataOutputFormat& OutValue, const TCHAR* Buffer);`

### `Source/Programs/BuildPatchTool/Public/Interfaces/ToolMode.h` (Public)


#### struct `is_ue_set`  
`template<typename T> struct is_ue_set : std::false_type`  
_L54-54_
- inherits: `std::false_type`
- desc: Detect if a template parameter is a TSet

#### struct `is_ue_set`  
`template<typename... T> struct is_ue_set<TSet<T...>> : std::true_type`  
_L57-57_
- inherits: `std::true_type`

#### struct `is_ue_array`  
`template<typename T> struct is_ue_array : std::false_type`  
_L61-61_
- inherits: `std::false_type`
- desc: Detect if template parameter is a TArray

#### struct `is_ue_array`  
`template<typename... T> struct is_ue_array<TArray<T...>> : std::true_type`  
_L64-64_
- inherits: `std::true_type`

#### class `BuildPatchTool::IToolMode`  
`class IToolMode`  
_L70-486_
- L73 _public member_ `TCHAR const * const EqualsStr = TEXT("=")`
- L74 _public member_ `TCHAR const * const QuoteStr = TEXT("\""`
- L85 _public function_ `virtual ~IToolMode()`
- L87 _public prototype_ `virtual EReturnCode Execute() = 0;`
- L89 _public member_ `bool bHelp = false;`
- L91 _public function_ `template<typename T> void PrintHelp()`
- L105 _public function_ `void NormalizeUriFile(FString& UriFile)` — Helper for normalizing a URI referring to a file. We make sure not to cause issues with URIs that separate a protocol and authority with :// and windows UNC paths that begin with \\. Windows UNC paths still work in UE4 code with //. @param UriFile       The file URI to be Normalized.
- L111 _public function_ `void NormalizeUriFileInKeys(TArray<TPair<FString, FString>>& Pairs)`
- L125 _public function_ `void NormalizeUriPath(FString& UriPath)` — Helper for normalizing a URI referring to a path. We make sure not to cause issues with URIs that separate a protocol and authority with :// and windows UNC paths that begin with \\. Windows UNC paths still work in UE4 code with //. @param UriPath       The path URI to be Normalized.
- L139 _public function_ `bool IsEmptyDirectory(const FString& Directory)`
- L163 _public function_ `template <typename TValueType> bool ParseSwitch(const TCHAR* InSwitch, TValueType& Value, const TArray<FString>& Switches)` — Helper for parsing a switch from an array of switches, usually produced using FCommandLine::Parse(..) @param InSwitch      The switch name, ending with =. E.g. option=, foo=. It would usually be a compile time const. @param Value         Receives the value from the switch. @param Switches      The array of switches to search through. @return true if the switch was found.
- L187 _public function_ `template <typename TValueType> bool ParseSwitches(const TCHAR* InSwitch, TArray<TValueType>& Values, const TArray<FString>& Switches)` — Helper for parsing an array of multiple same name switches from the full array of switches, usually produced using FCommandLine::Parse(..) @param InSwitch      The switch name, ending with =. E.g. option=, foo=. It would usually be a compile time const. @param Values        Receives the values from the switches. @param Switches      The array of switches to search through. @return true if at least one match was found.
- L211 _public function_ `bool ParseOption(const TCHAR* InSwitch, const TArray<FString>& Switches)`
- L217 _public function_ `template<typename TFirst, typename TSecond, typename TContainer> bool ParsePairs(const TCHAR* InFirstSwitch, const TCHAR* InSecondSwitch, const TArray<FString>& Switches, TContainer& OutPairs, FString& ErrorMessage)`
- L277 _public function_ `bool ParsePairs(const TCHAR* InFirstSwitch, const TCHAR* InSecondSwitch, const TArray<FString>& Switches, TMap<FGuid, TArray<uint8>>& OutPairs, FString& ErrorMessage)`
- L282 _public function_ `bool ParsePairs(const TCHAR* InFirstSwitch, const TCHAR* InSecondSwitch, const TArray<FString>& Switches, TArray<TPair<FString, FString>>& OutPairs, FString& ErrorMessage)`
- L287 _public function_ `bool ParseInstallActions(const TCHAR* InPrevManifestSwitch, const TCHAR* InNewManifestSwitch, const TCHAR* InTagsSwitch, const TArray<FString>& Switches, TArray<FInstallActionArgs>& OutActions, FString& ErrorMessage)`
- L394 _public function_ `bool ParseInstallActions(const TArray<FString>& Switches, TArray<FInstallActionArgs>& OutActions, FString& ErrorMessage)` — Helper to run ParseInstallActions with default argument names.
- L399 _public function_ `bool ParseValue(const FString& ValueIn, FString& ValueOut)`
- L405 _public function_ `bool ParseValue(const FString& ValueIn, uint64& ValueOut)`
- L415 _public function_ `bool ParseValue(const FString& ValueIn, uint32& ValueOut)`
- L425 _public function_ `bool ParseValue(const FString& ValueIn, int32& ValueOut)`
- L435 _public function_ `bool ParseValue(const FString& ValueIn, FGuid& ValueOut)`
- L442 _public function_ `ParseValue(const FString& ValueIn, TCollection& ValueOut)`
- L464 _public function_ `bool ParseValue(const FString& ValueIn, TArray<uint8>& ValueOut)`
- L481 _public function_ `ParseValue(const FString& ValueIn, TEnum& ValueOut)`

#### struct `BuildPatchTool::IToolMode::FInstallActionArgs`  
`struct FInstallActionArgs`  
_L76-82_
- L79 _public member_ `TOptional<FString> PrevManifestUri;`
- L80 _public member_ `TOptional<FString> NewManifestUri;`
- L81 _public member_ `TOptional<TSet<FString>> InstallTags;`

#### class `BuildPatchTool::FToolModeFactory`  
`class FToolModeFactory`  
_L488-496_
- L491 _public typedef_ `typedef TFunction<IToolMode* (IBuildPatchServicesModule&, const TCHAR* )> FToolModeCreateFunc;`
- L492 _public typedef_ `typedef TMulticastDelegate<void(TMap<FString, FToolModeCreateFunc>&)> FModeRegistryDelegate;`
- L494 _public prototype_ `static IToolMode* Create(IBuildPatchServicesModule& BpsInterface, const TCHAR* CommandLine);`
- L495 _public prototype_ `static FModeRegistryDelegate& GetModeRegistryDelegate();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define IMPLEMENT_BPT_MODE(ModeName, ModeClass) \`
- L26 _macro_ `#define IMPLEMENT_BPT_MODE_ALIAS(ModeName, ModeClass) \`
- L39 _namespace_ `namespace Constants`
- L41 _variable_ `static const FString Comma(TEXT(","))` (scope `Constants`)
- L42 _variable_ `static const FString Equals(TEXT("="))` (scope `Constants`)
- L43 _variable_ `static const FString DoubleQuote(TEXT("\"")` (scope `Constants`)
- L44 _variable_ `static const FString SingleQuote(TEXT("'"))` (scope `Constants`)
- L45 _variable_ `static const FString Slash(TEXT("/"))` (scope `Constants`)
- L46 _variable_ `static const FString Backslash(TEXT("\\")` (scope `Constants`)
- L47 _variable_ `static const FString Custom(TEXT("cust` (scope `Constants`)
- L48 _variable_ `static const FString CustomInt(TEXT("cust` (scope `Constants`)
- L49 _variable_ `static const FString CustomFloat(TEXT("cust` (scope `Constants`)
- L66 _namespace_ `namespace BuildPatchTool`
- L169 _function_ `if (const FString* Switch = Switches.FindByPredicate([InSwitch](const FString& Switch) { return Switch.StartsWith(InSwitch); }))` (scope `BuildPatchTool::IToolMode::ParseSwitch`)
- L294 _function_ `` (scope `BuildPatchTool::IToolMode::ParseInstallActions`)

### `Source/Programs/BuildPatchTool/Public/ToolModes/AutomationMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/ChunkDeltaOptimiseMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/ChunkDirectoryMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/CompactifyMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/DiffManifestMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/EnumerationMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/ExtractMetadataMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/InstallManifestMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/MergeManifestMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/PackageChunksMode.h` (Public)
_(no declarations extracted)_

### `Source/Programs/BuildPatchTool/Public/ToolModes/VerifyChunksMode.h` (Public)
_(no declarations extracted)_
