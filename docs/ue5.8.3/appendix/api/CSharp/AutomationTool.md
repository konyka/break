# CSharp / AutomationTool

- project root: `Source/Programs/AutomationTool`
- files: 2; symbols: 10
- symbol kinds: class=1, field=1, method=8
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Program.cs` (AutomationTool)


#### class `AutomationToolDriver.Program`  
`public partial class Program`  
_public; L24-547_
- desc: Main entry point
- L33-154 _private method_ `private static void ParseParam(string CurrentParam, CommandInfo CurrentCommand, ILogger Logger)` — Parses command line parameter.
- L156-182 _private method_ `private static string ParseString(string Key, string Value)`
- L184-198 _private method_ `private static string ParseList(string Key, List<object> Value)`
- L200-238 _private method_ `private static void ParseDictionary(Dictionary<string, object> Value, List<string> Arguments)`
- L240-279 _private method_ `private static void ParseProfile(ref string[] CommandLine)`
- L286-367 _public method_ `public static void ParseCommandLine(string[] Arguments, ILogger Logger)` — Parse the command line and create a list of commands to execute.
- L369 _private* field_ `static ParsedCommandLine AutomationToolCommandLine`
- L375-492 _public method_ `public static async Task<int> Main(string[] Arguments)` — Main entry point
- L494-546 _private* method_ `static async Task<ExitCode> MainProc()`

### `Source/Programs/AutomationTool/Properties/AssemblyInfo.cs` (AutomationTool)
_(no declarations)_

