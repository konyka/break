# CSharp / CSVToSVG

- project root: `Source/Programs/CSVTools/CSVToSVG`
- files: 2; symbols: 17
- symbol kinds: class=2, field=6, method=9
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/CSVToSVG/CsvToSvgProgram.cs` (CSVToSVG)


#### class `CSVTools.CsvCache`  
`class CsvCache`  
_internal*; L16-37_
- L18-32 _public method_ `public CsvStats ReadCSVFile(string csvFilename, string[] statNames, int numRowsToSkip)`
- L33 _public field_ `public CsvStats csvStats`
- L34 _public field_ `public string filename`
- L35 _public field_ `public int skipRows`
- L36 _private field_ `private readonly object readLock = new object()`

#### class `CSVTools.Program`  
`class Program : CSVStats.CommandLineTool`  
_internal*; L40-558_
- inherits: `CSVStats.CommandLineTool`
- L42 _private* field_ `static CsvCache csvCache = null`
- L44 _private* field_ `static string formatString = "Format: \n" + " -csvs <list> OR -csv <list> OR -csvDir <path>\n" + " [ -o <svgFilename> ]\n" + " -stats <stat names> (can include wildcards)\n" + " OR \n" + " -batchCommands <response file with comma ...`
- L115-152 _private* method_ `void Run(string[] args)`
- L154-164 _private* method_ `string GenerateIDFromString(string str)`
- L167-288 _private* method_ `void MakeGraph()`
- L290-334 _private* method_ `static string[] MakeArgsArray(string argsStr)`
- L336-350 _private* method_ `void ViewGraph(string svgPath)`
- L352-479 _private* method_ `GraphParams getGraphParamsFromArgs()`
- L481-507 _private* method_ `CsvStats LoadCsv(string csvFilename, string[] statNames)`
- L509-557 _private* method_ `static void Main(string[] args)`

### `Source/Programs/CSVTools/CSVToSVG/Properties/AssemblyInfo.cs` (CSVToSVG)
_(no declarations)_

