# CSharp / CsvInfo

- project root: `Source/Programs/CSVTools/CsvInfo`
- files: 2; symbols: 10
- symbol kinds: class=2, field=1, method=7
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/CsvInfo/CSVInfo.cs` (CsvInfo)


#### class `CSVInfo.Version`  
`class Version`  
_internal*; L13-18_
- L15 _private field_ `private static string VersionString = "1.07"`
- L17 _public method_ `public static string Get()`

#### class `CSVInfo.Program`  
`class Program : CommandLineTool`  
_internal*; L20-272_
- inherits: `CommandLineTool`
- L22-43 _private* method_ `static int Main(string[] args)`
- L45-48 _private* method_ `string Quotify(string s)`
- L50-53 _private* method_ `string Sanitize(string s)`
- L55-58 _private* method_ `string ToJsonString(string s)`
- L60-68 _private* method_ `string ToJsonStringList(List<string> list)`
- L70-271 _private* method_ `void Run(string[] args)`

### `Source/Programs/CSVTools/CsvInfo/Properties/AssemblyInfo.cs` (CsvInfo)
_(no declarations)_

