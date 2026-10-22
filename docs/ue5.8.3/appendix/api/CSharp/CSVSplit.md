# CSharp / CSVSplit

- project root: `Source/Programs/CSVTools/CSVSplit`
- files: 2; symbols: 7
- symbol kinds: class=2, field=2, method=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/CSVSplit/CSVSplit.cs` (CSVSplit)


#### class `CSVTools.Version`  
`class Version`  
_internal*; L15-20_
- L17 _private field_ `private static string VersionString = "1.33"`
- L19 _public method_ `public static string Get()`

#### class `CSVTools.Program`  
`class Program : CommandLineTool`  
_internal*; L22-193_
- inherits: `CommandLineTool`
- L24 _private* field_ `static string formatString = "Format: \n" + " -csv <filename>\n" + " -splitStat <statname>" + " [ -o <csvFilename> ] \n" + " [ -delay <frame count> ] \n" + " [ -virtualEvents ] \n"`
- L32-170 _private* method_ `void Run(string[] args)`
- L173-191 _private* method_ `static void Main(string[] args)`

### `Source/Programs/CSVTools/CSVSplit/Properties/AssemblyInfo.cs` (CSVSplit)
_(no declarations)_

