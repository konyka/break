# CSharp / CSVFilter

- project root: `Source/Programs/CSVTools/CSVFilter`
- files: 2; symbols: 8
- symbol kinds: class=2, field=2, method=4
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/CSVFilter/CSVFilter.cs` (CSVFilter)


#### class `CSVTools.Version`  
`class Version`  
_internal*; L15-20_
- L17 _private field_ `private static string VersionString = "1.02"`
- L19 _public method_ `public static string Get()`

#### class `CSVTools.Program`  
`class Program : CommandLineTool`  
_internal*; L22-217_
- inherits: `CommandLineTool`
- L24 _private* field_ `static string formatString = "Format: \n" + " -csv <filename> \n"+ " -stats <stat names> AND/OR -defaults (specifies a default stat list)\n" + " -o <csvFilename> \n"`
- L31-52 _private method_ `private bool IsStatIncluded(string statName, string[] statList)`
- L74-194 _private* method_ `void Run(string[] args)`
- L197-215 _private* method_ `static void Main(string[] args)`

### `Source/Programs/CSVTools/CSVFilter/Properties/AssemblyInfo.cs` (CSVFilter)
_(no declarations)_

