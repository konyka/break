# CSharp / EpicGames.LogMatchers

- project root: `Source/Programs/Shared/EpicGames.LogMatchers`
- files: 23; symbols: 180
- symbol kinds: class=23, const=17, field=99, method=39, property=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.LogMatchers/CompileEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.CompileEventMatcher`  
`class CompileEventMatcher : ILogEventMatcher`  
_internal*; L15-415_
- inherits: `ILogEventMatcher`
- desc: Matches compile errors and annotates with the source file path and revision
- L17 _private* const_ `const string FilePattern = @"(?:(?<file>" + @"(?:[a-zA-Z]:)?" + @"[^:(\s]+" + @"[^:<>*?""]+" + @"(?:\.(?i)(?:h|hpp|hxx|c|cc|cpp|cxx|inc|inl|cs|targets|verse)|[/\\][a-zA-Z0-9_]+)" + @")|<scratch space>)"`
- L30 _private* const_ `const string VisualCppLocationPattern = @"\(" + @"(?:" + @"(?<line>\d+)" + @"|" + @"(?:(?<line>\d+)-(?<maxline>\d+))" + @"|" + @"(?:(?<line>\d+),(?<column>\d+))" + @"|" + @"(?:(?<line>\d+),(?<column>\d+)-(?<maxcolumn>\d+))" + @"|" + @"(?:(? ...`
- L45 _private* const_ `const string VisualCppSeverity = @"(?:Verse compiler |Script )?(?<severity>fatal error|[Ee]rror|[Ww]arning)(?: (?<code>[A-Z]*[0-9]+))?"`
- L48 _private* const_ `const string ClangLocationPattern = @":" + @"(?<line>\d+)" + @"(?::(?<column>\d+))?" + @""`
- L54 _private* const_ `const string ClangSeverity = @"(?<severity>error|warning|fatal error)"`
- L57 _private* field_ `static readonly Regex s_baseFilePattern = new(@"^\s*(?:\[[\d/]+\] Compile |[^/\ :]+\\.cpp\s*(?:\([^\)]*\))?$)")`
- L58 _private* field_ `static readonly Regex s_preludePattern = new(@"^\s*(?:In (member )?function|In file included from)")`
- L59 _private* field_ `static readonly Regex s_preludeFilePattern = new($"^\\s*In file included from {FilePattern}:")`
- L60 _private* field_ `static readonly Regex s_blankLinePattern = new(@"^\s*$")`
- L61 _private* field_ `static readonly Regex s_errorWarningPattern = new("[Ee]rror|[Ww]arning")`
- L62 _private* field_ `static readonly Regex s_clangDiagnosticPattern = new($"^\\s*{FilePattern}\\s*{ClangLocationPattern}:\\s*{ClangSeverity}\\s*:")`
- L63 _private* field_ `static readonly Regex s_clangNotePattern = new($"^\\s*{FilePattern}\\s*{ClangLocationPattern}:\\s*note:")`
- L64 _private* field_ `static readonly Regex s_clangMarkerPattern = new(@"^(\s*)[\^~][\s\^~]*$")`
- L65 _private* field_ `static readonly Regex s_llvmDiagnosticPattern = new($"^\\s*{ClangSeverity}:\\s*{FilePattern}\\s*{ClangLocationPattern}:\\s*")`
- L66 _private* field_ `static readonly Regex s_llvmNotePattern = new($"^\\s*note:\\s*(?:{FilePattern}\\s*{ClangLocationPattern}:)?")`
- L67 _private* field_ `static readonly Regex s_xcodeIDEWatchExtensionPattern = new(@"xcodebuild.*Requested but did not find extension point with identifier.*for extension.*\.watchOS of plug-in com\.apple\.dt\.IDEWatchSupportCore")`
- L68 _private* field_ `static readonly Regex s_scriptCompilePattern = new(@"^\s*[A-Za-z0-9_\.]+ ERROR:.* [A-Za-z_]+ failed to compile\.")`
- L69 _private* field_ `static readonly Regex s_cscSummaryPattern = new(@"^\s+\d+ (?:Warning|Error)\(s\)")`
- L70 _private* field_ `static readonly Regex s_cscOutputPattern = new(@"^ [^ ]+ -> ")`
- L71 _private* field_ `static readonly Regex s_tempLibpvxMacLoadCmdPattern = new(@"no platform load command found in")`
- L72 _private* field_ `static readonly Regex s_tempXCodeDupLibrariesPattern = new(@"ignoring duplicate libraries")`
- L74 _private* field_ `static readonly string[] s_invalidExtensions = [ ".obj", ".dll", ".exe" ]`
- L81 _private* const_ `const string DefaultSourceFileBaseDir = "Engine/Source"`
- L84-197 _public method_ `public LogEventMatch? Match(ILogCursor input)` — (inheritdoc)
- L199 _private* field_ `static readonly Regex s_xcodeProjectErrorPattern = new(@"^\s*(?<file>.+?\.xcodeproj):\s*(?<severity>[Ee]rror|[Ww]arning):\s*(?<message>.+)$")`
- L201 _private* field_ `static readonly Regex s_xcodeRebuildPCHPattern = new(@"(?<severity>(?:[Ff]atal )?[Ee]rror): file '(?<file>.*)' has been modified since the precompiled header '(?<pch>.*)' was built")`
- L203-244 _private* method_ `static bool TryMatchXcodeCppEvent(LogEventBuilder builder, [NotNullWhen(true)] out LogEventMatch? outEvent)`
- L246 _private* field_ `static readonly Regex s_msvcPattern = new($"^\\s*(?:ERROR: |WARNING: |Log[A-Za-z_]+: [A-Z][a-z]+: )?{FilePattern}(?:{VisualCppLocationPattern})? ?:\\s+{VisualCppSeverity}:")`
- L247 _private* field_ `static readonly Regex s_msvcNotePattern = new($"^\\s*{FilePattern}(?:{VisualCppLocationPattern})?\\s*: note:")`
- L248 _private* field_ `static readonly Regex s_projectPattern = new(@"\[(?<project>[^[\]]+)]\s*$")`
- L250-345 _private* method_ `static bool TryMatchVisualCppEvent(LogEventBuilder builder, [NotNullWhen(true)] out LogEventMatch? outEvent)`
- L347-361 _private* method_ `static void SkipClangMarker(LogEventBuilder builder)`
- L363-374 _private* method_ `static string? GetPlatformAgnosticDirectoryName(string fileName)`
- L376-391 _private* method_ `static bool IsSourceFile(Match match)`
- L393-404 _private* method_ `static LogLevel GetLogLevelFromSeverity(Match match)`
- L406-414 _private* method_ `static string ExtractIndent(string line)`

### `Source/Programs/Shared/EpicGames.LogMatchers/ContentEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.ContentEventMatcher`  
`class ContentEventMatcher : ILogEventMatcher`  
_internal*; L13-60_
- inherits: `ILogEventMatcher`
- desc: Matches compile errors and annotates with the source file path and revision
- L15 _private* field_ `static readonly Regex s_errorWarningPattern = new("Error:|Warning:")`
- L17 _private* field_ `static readonly Regex s_pattern = new( @"^\s*" + @"(?:\[[\d\.\-: ]+\])*" + @"(?<channel>[a-zA-Z0-9]+):\s+" + @"(?<severity>Error:|Warning:)\s+" + @"(?:\[AssetLog\] )?" + @"(?<asset>(?:[a-zA-Z]:)?[^:]+(?:.uasset|.umap)):\s*" + @"(?<mes ...`
- L27-46 _public method_ `public LogEventMatch? Match(ILogCursor input)` — (inheritdoc)
- L48-59 _private* method_ `static LogLevel GetLogLevelFromSeverity(Match match)`

### `Source/Programs/Shared/EpicGames.LogMatchers/CrashEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.CrashEventMatcher`  
`class CrashEventMatcher : ILogEventMatcher`  
_internal*; L12-89_
- inherits: `ILogEventMatcher`
- desc: Matcher for engine crashes
- L14 _private* field_ `static readonly Regex s_exitCodePattern = new(@"ExitCode=(3|139|255)(?!\d)")`
- L16 _private* field_ `static readonly Regex s_appErrorPattern = new(@"^\s*[A-Za-z]+: Error: appError called: ")`
- L18 _private* field_ `static readonly Regex s_assertionFailedPattern = new(@"^Assertion failed: ")`
- L20-69 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`
- L71 _private* field_ `static readonly Regex s_errorPattern = new("[Ee]rror:")`
- L72 _private* field_ `static readonly Regex s_warningPattern = new("[Ww]arning:")`
- L74-88 _private* method_ `static LogLevel GetLogLevel(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/DockerEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.DockerEventMatcher`  
`class DockerEventMatcher : ILogEventMatcher`  
_internal*; L12-32_
- inherits: `ILogEventMatcher`
- desc: Matcher for docker errors
- L14 _private* field_ `static readonly Regex s_noSpacePattern = new(": no space left on device$")`
- L15 _private* field_ `static readonly Regex s_updateAlternativesPattern = new(@"^update-alternatives: warning:")`
- L18-31 _public method_ `public LogEventMatch? Match(ILogCursor cursor)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.LogMatchers/ExceptionEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.ExceptionEventMatcher`  
`class ExceptionEventMatcher : ILogEventMatcher`  
_internal*; L12-31_
- inherits: `ILogEventMatcher`
- desc: Matches a generic C# exception
- L14 _private* field_ `static readonly Regex s_pattern = new(@"^\s*Unhandled Exception: ")`
- L15 _private* field_ `static readonly Regex s_atPattern = new(@"^\s*at ")`
- L18-30 _public method_ `public LogEventMatch? Match(ILogCursor cursor)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.LogMatchers/ExitCodeEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.ExitCodeEventMatcher`  
`class ExitCodeEventMatcher : ILogEventMatcher`  
_internal*; L12-43_
- inherits: `ILogEventMatcher`
- desc: Matcher for editor/UAT instances exiting with an error
- L14 _private* field_ `static readonly Regex s_pattern = new( @"Editor terminated with exit code -?[1-9]" + @"|(?:Error executing.+)(?:tool returned code)(.+)" + @"|\s*RunU[AB]T ERROR:" + @"|\s*ERROR:.*did not complete successfully: exit code: [0-9]+")`
- L20-42 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/GenericEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.GenericEventMatcher`  
`class GenericEventMatcher : ILogEventMatcher`  
_internal*; L13-49_
- inherits: `ILogEventMatcher`
- desc: Low-priority matcher for generic error strings like "warning:" and "error:"
- L15 _private* field_ `static readonly Regex s_fatalPattern = new( @"^\s*(FATAL|fatal error):")`
- L18 _private* field_ `static readonly Regex s_warningErrorPattern = new( @"(?<!\w)(?i)(WARNING|ERROR) ?(\([^)]+\)|\[[^\]]+\])?:(?: |$)")`
- L21 _private* field_ `static readonly Regex s_errorPattern = new( @"[Ee]rror [A-Z]\d+\s:")`
- L25-48 _public method_ `public LogEventMatch? Match(ILogCursor cursor)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.LogMatchers/GradleEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.GradleEventMatcher`  
`class GradleEventMatcher : ILogEventMatcher`  
_internal*; L12-50_
- inherits: `ILogEventMatcher`
- desc: Matcher for Gradle errors
- L14 _private* field_ `static readonly Regex s_failurePattern = new(@"^\s*FAILURE:")`
- L15 _private* field_ `static readonly Regex s_blankPattern = new(@"^\s*$")`
- L16 _private* field_ `static readonly Regex s_indentPattern = new(@"^(\s*)\*")`
- L18-49 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/LinkEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.LinkEventMatcher`  
`class LinkEventMatcher : ILogEventMatcher`  
_internal*; L13-232_
- inherits: `ILogEventMatcher`
- desc: Matcher for linker errors
- L15 _private* field_ `static readonly Regex s_undefinedReferencePattern = new( @": undefined reference to |undefined symbol|^\s*(ld|ld.lld|lld-link|(.*clang)):|^[^:]*[^a-zA-Z][a-z]?ld: |^\s*>>>")`
- L18 _private* field_ `static readonly Regex s_undefinedSymbolsForArchPattern = new( @"^(\s*)Undefined symbols for architecture")`
- L21 _private* field_ `static readonly Regex s_ldClangPattern = new( @"^\s*(ld|ld.lld|lld-link|clang|clang\+\+):")`
- L24 _private* field_ `static readonly Regex s_ldClangErrorPattern = new( @"^\s*(ld|ld.lld|lld-link|clang|clang\+\+):\s+error:\s+(?<error>.+)$")`
- L27 _private* field_ `static readonly Regex s_ldMultiplyDefinedPattern = new( @"(?<severity>error): L\d+: symbol '(?<symbol>[^']+)' multiply defined$")`
- L30 _private* field_ `static readonly Regex s_ldMultiplyDefinedInfoPattern = new( @"error: \.\.\.")`
- L33 _private* field_ `static readonly Regex s_microsoftErrorPattern = new( @"error (?<code>LNK\d+):")`
- L36 _private* field_ `static readonly Regex s_ignoredLinkWarningPattern = new( @"^\s*ld: warning: Linker asked to preserve internal global:")`
- L40-166 _public method_ `public LogEventMatch? Match(ILogCursor cursor)` — (inheritdoc)
- L168-231 _private* method_ `static bool AddSymbolMarkupForLine(LogEventBuilder builder)`

### `Source/Programs/Shared/EpicGames.LogMatchers/LocalizationEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.LocalizationEventMatcher`  
`class LocalizationEventMatcher : ILogEventMatcher`  
_internal*; L12-59_
- inherits: `ILogEventMatcher`
- desc: Matches events formatted as UE log channel output by the localization commandlet
- L14 _private* field_ `static readonly Regex s_pattern = new( @"^(\s*)" + @"(?:\[[\d\.\-: ]+\])*" + @"(?<channel>LogLocTextHelper|LogGatherTextFromSourceCommandlet):\s*" + @"(?<severity>Error|Warning|Display):\s+" + @"(?<file>([a-zA-Z]:)?[^:/\\]*[/\\][^:]+[ ...`
- L23 _private* field_ `static readonly Regex s_trailingPattern = new(@": See conflicting location\.\s*$")`
- L26-50 _public method_ `public LogEventMatch? Match(ILogCursor input)` — (inheritdoc)
- L52-58 _private* method_ `static void Annotate(LogEventBuilder builder, Match match)`

### `Source/Programs/Shared/EpicGames.LogMatchers/LogChannelEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.LogChannelEventMatcher`  
`class LogChannelEventMatcher : ILogEventMatcher`  
_internal*; L12-128_
- inherits: `ILogEventMatcher`
- desc: Matches events formatted as UE log channel output
- L14 _private* field_ `static readonly Regex s_pattern = new( @"^(\s*)" + @"(?:\[[\d\.\-: ]+\])*" + @"(?<channel>[a-zA-Z_][a-zA-Z0-9_]*):\s*" + @"(?<severity>Error|Warning|Display): " )`
- L21 _private* field_ `static readonly Regex s_callstackLine = new(@"\[Callstack\]")`
- L22 _private* field_ `static readonly Regex s_crashHeader = new(@"=== Critical error: ===|=== Handled ensure: ===")`
- L25 _private* field_ `static readonly Regex s_assertPattern = new( @"(?<type>Assertion failed|Ensure condition failed): (?<condition>.+?)\s+\[File:(?:.*[/\\])?(?<file>[^\]]+)\]")`
- L29 _private* field_ `static readonly Regex s_blankChannelLine = new( @"^(\s*)" + @"(?:\[[\d\.\-: ]+\])*" + @"[a-zA-Z_][a-zA-Z0-9_]*:\s*" + @"(?:Error|Warning|Display):\s*$" )`
- L37-127 _public method_ `public LogEventMatch? Match(ILogCursor input)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.LogMatchers/LogMatcherCollections.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.LogMatcherCollections`  
`public static class LogMatcherCollections`  
_public; L11-48_
- desc: Helper class that specifies collections of matchers to use for log parsing.
- L17 _public property_ `public static IEnumerable<ILogEventMatcher> AutomationUtilsMatchers => ...` — All matchers originally from the AutomationUtils project, for legacy compatibility. Not recommended for new usage - choose what matchers you need instead.
- L42 _public property_ `public static IEnumerable<ILogEventMatcher> UBTMatchers => ...` — All matchers originally from the UBT project, for legacy compatibility. Not recommended for new usage - choose what matchers you need instead.

### `Source/Programs/Shared/EpicGames.LogMatchers/MicrosoftEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.MicrosoftEventMatcher`  
`class MicrosoftEventMatcher : ILogEventMatcher`  
_internal*; L13-57_
- inherits: `ILogEventMatcher`
- desc: Matcher for generic Microsoft errors (see https://docs.microsoft.com/en-us/cpp/build/formatting-the-output-of-a-custom-build-step-or-build-event?view=msvc-160)
- L15 _private* field_ `static readonly Regex s_warningCodePattern = new( @"(?<severity>(?:error|warning)) " + @"(?<code>[a-zA-Z]+[0-9]+)\s*:")`
- L19 _private* field_ `static readonly Regex s_fileOrToolPattern = new(@"^\s*(.*[^\s])\s*:")`
- L21 _private* field_ `static readonly Regex s_fileLinePattern = new(@"^\s*(?<file>.*)\((?<line>\d+)(?:, (?<column>\d+))?\)\s*:$")`
- L23-56 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/MsTestEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.MsTestEventMatcher`  
`class MsTestEventMatcher : ILogEventMatcher`  
_internal*; L9-36_
- inherits: `ILogEventMatcher`
- L11 _private* field_ `static readonly Regex s_failedPattern = new(@"^ \s*Failed [A-Za-z0-9_]+ (?:\(.*\) )?\[\d+ (?:s|ms)\]$")`
- L12 _private* field_ `static readonly Regex s_detailPattern = new(@"^ \s*(?:Error Message|Stack Trace):$")`
- L14-35 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/SanitizerEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.SanitizerEventMatcher`  
`public class SanitizerEventMatcher : ILogEventMatcher`  
_public; L17-261_
- inherits: `ILogEventMatcher`
- desc: Matcher for LLVM Sanitizer reports
- L26 _public field_ `public static readonly Regex ReportStartPattern = new(@"(^=+$)", RegexOptions.Multiline | RegexOptions.ExplicitCapture)`
- L35 _public field_ `public static readonly Regex ReportEndPattern = new(@"(End of Address Sanitizer report)|(^==\d+==(\s*\w+)?$)|(^=+$)", RegexOptions.Multiline | RegexOptions.ExplicitCapture)`
- L45 _public field_ `public static readonly Regex ReportLevelPattern = new( @"^[\s\t]*(==\d+(?:\[0x\w+\])?==\s*)?" + @"(?<ReportLevel>WARNING|ERROR):\s+" + @"(" + @"((?<SanitizerName>\w+)Sanitizer:\s*(?<Summary>.+))" + @"|" + @"((?<SanitizerName>\w+):\s*(?<SummaryReason> ...`
- L60 _public field_ `public static readonly Regex StackTracePattern = new( @"^[\s\t]+\#[\d]+\s+(0x[0-9a-fA-F]+\s+in\s+)?" + @"(?<Symbol>.+?)\s" + @"(?<SourceFile>(\/|\w:).+?)" + @"(:(?<Line>\d+?))?" + @"(:(?<Column>\d+?))?" + @"(\s+\(.+?\+(?<Address>0x[0-9a-fA-F]+?)\))? ...`
- L74 _public field_ `public static readonly Regex RaceDetectorStackTracePattern = new( @"^(?<SourceFile>(\/|\w:)[^\(]+)" + @"(\s\((?<Line>\d+)\))?:\s+" + @"(?<Symbol>.+)\s" + @"(?<Address>0x[\w]+)$", RegexOptions.Multiline | RegexOptions.ExplicitCapture)`
- L87 _public field_ `public static readonly Regex SummaryPattern = new( @"^[\s]*SUMMARY:\s+(?<SanitizerName>\w+)Sanitizer:\s*" + @"(?<SummaryReason>[\w\s\-\(\)]+)\s" + @"\(?(?<SourceFile>.+?)" + @"(\+(?<Address>0[xX][0-9a-fA-F]+?)\))?" + @"(:(?<Line>\d+?))?" + @"(:(? ...`
- L102-112 _public method_ `public static EventId ConvertSanitizerNameToEventId(string sanitizerName)` — Convert SanitizerName to EventId
- L119-127 _public method_ `public static LogLevel ConvertReportLevel(string reportLevel)` — Convert ReportLevel string to LogLevel enum
- L137-144 _private method_ `private static void AddPropertyAndReplace(LogValue value, Group group, Dictionary<string, object> properties, ref string message, int offset = 0)` — Add Value to Properties using (Regex) Group match and update Message with the corresponding key instead of value from Group.
- L153-167 _public method_ `public static bool AddSanitizerSummaryProperties(ref string message, Dictionary<string, object> properties)` — Add Sanitizer Summary information to input Key/Value Pair Properties and update Message with Key markers
- L171-260 _public method_ `public LogEventMatch? Match(ILogCursor cursor)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.LogMatchers/ShaderEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.ShaderEventMatcher`  
`class ShaderEventMatcher : ILogEventMatcher`  
_internal*; L15-104_
- inherits: `ILogEventMatcher`
- desc: Matches shader compile errors and annotates with the source file path and revision. Also detects "Failed to compile Material" warnings and extracts the material path to enable grouping by material in the issue handler.
- L17 _private* const_ `const string Prefix = @"^\s*LogShaderCompilers: (?<severity>Error|Warning): "`
- L19 _private* const_ `const string FilePattern = @"(?<file>" + @"(?:[a-zA-Z]:)?" + @"[^:(\s]+" + @"[^:(\s\\/]" + @")"`
- L29 _private* const_ `const string LinePattern = @"(?<line>\d+)(?::(?<column>\d+))?"`
- L38 _private* const_ `const string MaterialPattern = @"Failed to compile Material (?<material>/[^\s]+)"` — Pattern to extract material path from "Failed to compile Material {path}" messages. The material path is a forward-slash separated path like "/Game/Materials/MyMaterial.MyMaterial". This property enables ShaderIssueHandler to group all compilation failures for the same material together, rather than creating separate issues for each shader/platform combination.
- L40 _private* field_ `static readonly Regex s_pattern = new(Prefix)`
- L41 _private* field_ `static readonly Regex s_patternWithFile = new($"{Prefix}{FilePattern}(?:\\({LinePattern}\\))?:")`
- L42 _private* field_ `static readonly Regex s_materialPattern = new(MaterialPattern)`
- L49 _private* field_ `static readonly Regex s_content = new(@"^(?:\s+|Validation failed|[A-Za-z]:[/\\]|Internal Error!)")`
- L52-90 _public method_ `public LogEventMatch? Match(ILogCursor input)` — (inheritdoc)
- L92-103 _private* method_ `static LogLevel GetLogLevelFromSeverity(Match match)`

### `Source/Programs/Shared/EpicGames.LogMatchers/SourceFileLineEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.SourceFileLineEventMatcher`  
`class SourceFileLineEventMatcher : ILogEventMatcher`  
_internal*; L13-75_
- inherits: `ILogEventMatcher`
- desc: Matches compile errors and annotates with the source file path and revision
- L15 _private* const_ `const string SeverityPattern = "(?<severity>ERROR|WARNING)"`
- L18 _private* const_ `const string FilePattern = @"(?<file>" + @"(?:[a-zA-Z]:)?" + @"[^:(\s]+" + @"[^:(\s\\/]" + @")"`
- L28 _private* const_ `const string LinePattern = @"(?<line>\d+)"`
- L31 _private* field_ `static readonly Regex s_pattern = new($"^\\s*{SeverityPattern}: {FilePattern}(?:\\({LinePattern}\\))?: ")`
- L32 _private* field_ `static readonly Regex s_copyright = new("copyright")`
- L35-61 _public method_ `public LogEventMatch? Match(ILogCursor input)` — (inheritdoc)
- L63-74 _private* method_ `static LogLevel GetLogLevelFromSeverity(Match match)`

### `Source/Programs/Shared/EpicGames.LogMatchers/SystemicEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.SystemicEventMatcher`  
`class SystemicEventMatcher : ILogEventMatcher`  
_internal*; L9-118_
- inherits: `ILogEventMatcher`
- L11 _private* field_ `static readonly Regex s_ddc = new(@"^\s*LogDerivedDataCache: Warning:")`
- L13 _private* field_ `static readonly Regex s_pdbUtil = new(@"^\s*ERROR: Error: EC_OK")`
- L14 _private* field_ `static readonly Regex s_pdbUtilSuffix = new(@"^\s*ERROR:\s*$")`
- L16 _private* field_ `static readonly Regex s_roboMerge = new(@"RoboMerge\/gates.*already locked on Commit Server by buildmachine")`
- L18 _private* field_ `static readonly Regex s_hostDown = new(@"ERROR: System\.IO\.IOException: Host is down")`
- L20 _private* field_ `static readonly Regex s_missingFileList = new(@"^\s*ERROR: Missing local or shared file list.*\.xml")`
- L22 _private* field_ `static readonly Regex s_ubaCacheResponseTimeout = new(@"UbaCache (.*) - Timed out after .* waiting for message response from server")`
- L24-117 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/UnsecureHttpMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.UnsecureHttpMatcher`  
`class UnsecureHttpMatcher : ILogEventMatcher`  
_internal*; L8-19_
- inherits: `ILogEventMatcher`
- L10-18 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/WorldLeakEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.WorldLeakEventMatcher`  
`public class WorldLeakEventMatcher : ILogEventMatcher`  
_public; L17-125_
- inherits: `ILogEventMatcher`
- desc: Matcher for World Leak Errors
- L22 _public field_ `public static readonly Regex ReportStartPattern = new(@"^====Fatal World Leaks====$", RegexOptions.Multiline | RegexOptions.ExplicitCapture)` — Regex pattern that matches Report Start
- L27 _public field_ `public static readonly Regex ReportEndPattern = new(@"^====End Fatal World Leaks====$", RegexOptions.Multiline | RegexOptions.ExplicitCapture)` — Regex pattern that matches Report End
- L32 _public field_ `public static readonly Regex ReportCallstackPattern = new( @"^[\s]*\^\s" + @"(?<Symbol>.+?)\s" + @"\[(?<SourceFile>(\/|\w:).+?)" + @"(:(?<Line>\d+?))?\]", RegexOptions.Multiline | RegexOptions.ExplicitCapture)` — Regex pattern that matches callstacks reported during leak reports
- L41 _public field_ `public static readonly Regex ReportLingeringReferenceUnderlinePattern = new(@"^\s*\^+\s*$", RegexOptions.Multiline | RegexOptions.ExplicitCapture)` — Regex pattern that matches the underlining of the reference preventing the object from being GC'd
- L46 _public field_ `public static readonly Regex ReportLingeringReference = new(@"^\s*\->\s*(?<ObjectText>.+)$", RegexOptions.Multiline | RegexOptions.ExplicitCapture)` — Regex pattern that matches leaking reference chain text
- L51 _public field_ `public static readonly Regex ReportBodyPattern = new(@"^\s*(?<ObjectFlags>((\([\w\s]+\)\s))+)?\s*(?<ObjectText>(.+)\s/(.)+/(.)+)$", RegexOptions.Multiline | RegexOptions.ExplicitCapture)` — Regex pattern that matches reference chain text
- L54-124 _public method_ `public LogEventMatch? Match(ILogCursor cursor)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.LogMatchers/WriteDummyPipeMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.WriteDummyPipeMatcher`  
`class WriteDummyPipeMatcher : ILogEventMatcher`  
_internal*; L8-21_
- inherits: `ILogEventMatcher`
- L10-20 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/XoreaxEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.XoreaxEventMatcher`  
`class XoreaxEventMatcher : ILogEventMatcher`  
_internal*; L9-122_
- inherits: `ILogEventMatcher`
- L11 _public const_ `public const string PropertyName = "name"`
- L12 _public const_ `public const string PropertyAgent = "agent"`
- L13 _public const_ `public const string PropertyDuration = "duration"`
- L14 _public const_ `public const string PropertyStartTime = "startTime"`
- L16 _private* field_ `static readonly Regex s_buildService = new(@"\(BuildService.exe\) is not running")`
- L18 _private* field_ `static readonly Regex s_xgConsole = new(@"BUILD FAILED: (.*)xgConsole\.exe(.*)")`
- L20 _private* field_ `static readonly Regex s_buildSystemError = new(@"^\s*--------------------Build System Error")`
- L21 _private* field_ `static readonly Regex s_buildSystemErrorEnd = new(@"^(\s*)--------------------")`
- L23 _private* field_ `static readonly Regex s_buildSystemWarning = new(@"^\s*--------------------Build System Warning[- ]")`
- L24 _private* field_ `static readonly Regex s_buildSystemWarningNext = new(@"^(\s*)([^ ].*):")`
- L26 _private* field_ `static readonly Regex s_buildSystemWarningSummary = new(@"^\d+ build system warning\(s\):")`
- L27 _private* field_ `static readonly Regex s_buildSystemWarningSummaryNext = new(@"^(\s*-\s*)([^ ].*)")`
- L29 _private* field_ `static readonly Regex s_cacheWarning = new(@"^\s*WARNING: \d+ items \([^\)]*\) removed from the cache due to reaching the cache size limit")`
- L30 _private* field_ `static readonly Regex s_cacheWarning2 = new(@"^\s*WARNING: Several items removed from the cache due to reaching the cache size limit")`
- L31 _private* field_ `static readonly Regex s_cacheWarning3 = new(@"^\s*WARNING: The Build Cache is close to full")`
- L33-121 _public method_ `public LogEventMatch? Match(ILogCursor cursor)`

### `Source/Programs/Shared/EpicGames.LogMatchers/ZenCliEventMatcher.cs` (EpicGames.LogMatchers)


#### class `EpicGames.LogMatchers.ZenCliEventMatcher`  
`class ZenCliEventMatcher : ILogEventMatcher`  
_internal*; L12-42_
- inherits: `ILogEventMatcher`
- desc: Matcher log output from zen cli in plain progress
- L14 _private* field_ `static readonly Regex s_httpOperationErrorPattern = new( @"Error: Operation failed due to a http error: (?<message>.*)\((?<http_error>\d+)\)")`
- L17 _private* field_ `static readonly Regex s_httpRequestErrorPattern = new( @"HttpClient request failed.*?""error_code"": (?<http_error>\d+)")`
- L20 _private* field_ `static readonly Regex s_httpRequestJsonErrorPattern = new( @"HttpClient request failed.*? Status: (?<http_error>\d+), Error: \'")`
- L23-41 _public method_ `public LogEventMatch? Match(ILogCursor input)`
