# CSharp / CSVCollate

- project root: `Source/Programs/CSVTools/CSVCollate`
- files: 2; symbols: 7
- symbol kinds: class=2, field=2, method=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/CSVCollate/CSVCollate.cs` (CSVCollate)


#### class `CSVTools.Version`  
`class Version`  
_internal*; L15-20_
- L17 _private field_ `private static string VersionString = "1.35"`
- L19 _public method_ `public static string Get()`

#### class `CSVTools.Program`  
`class Program : CommandLineTool`  
_internal*; L22-293_
- inherits: `CommandLineTool`
- L24 _private* field_ `static string formatString = "Format: \n" + " -csvs <filename or ; separated list> -csvDir <path>\n" + " [-searchPattern <pattern, e.g *.csv>] - for use with -csvDir\n" + " [-avg] -stats will be per frame averaged\n" + " [-recurs ...`
- L36-270 _private* method_ `void Run(string[] args)`
- L273-291 _private* method_ `static void Main(string[] args)`

### `Source/Programs/CSVTools/CSVCollate/Properties/AssemblyInfo.cs` (CSVCollate)
_(no declarations)_

