# CSharp / RegressionsReport

- project root: `Source/Programs/CSVTools/RegressionsReport`
- files: 2; symbols: 14
- symbol kinds: class=2, field=3, method=9
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/RegressionsReport/Properties/AssemblyInfo.cs` (RegressionsReport)
_(no declarations)_


### `Source/Programs/CSVTools/RegressionsReport/RegressionsReport.cs` (RegressionsReport)


#### class `RegressionsReport.Version`  
`class Version`  
_internal*; L19-25_
- L22 _private field_ `private static string VersionString = "1.1.0"`
- L24 _public method_ `public static string Get()`

#### class `RegressionsReport.Program`  
`class Program : CommandLineTool`  
_internal*; L27-360_
- inherits: `CommandLineTool`
- L29 _private* field_ `static string defaultBaseHTML = @" <!DOCTYPE html> <html> <head> <title>Regressions Report</title> <style> body { font-family: Arial, sans-serif; line-height: 1.6; margin: 0; padding: 0; background-color: #f4f4f4; } .container { wid ...`
- L67 _private* field_ `static string toolInformation = "RegressionsReport v" + Version.Get() + "\n" + "Required Arguments:\n" + " -csvFile <filename> - Path to input CSV file\n" + " -o <directory> - Path to output directory\n" + " -thresholds <filename> - ...`
- L82-176 _private* method_ `void Run(string[] args)`
- L179-209 _private* method_ `static DataTable ReadCsv(string filePath)`
- L212-240 _private* method_ `static Dictionary<string, double> ComputePercentageChanges(DataRow newRow, DataRow oldRow, DataColumnCollection columns, Dictionary<string, Dictionary<string, double>> thresholds)`
- L243-248 _private* method_ `static List<string> GenerateRegressionLines(Dictionary<string, double> regressions, Dictionary<string, double> changes, DataRow oldRow, DataRow newRow, string category)`
- L251-279 _private* method_ `static string GenerateReportContent(DataRow newRow, string message, List<string> significantLines, List<string> minorLines, Dictionary<string, double> percentageChanges)`
- L282-303 _private* method_ `static void WriteHtmlReport(string outputPath, string outputName, string baseHtml, string insertAfterTag, string reportContent)`
- L306-335 _private* method_ `static void DumpContentsToJson(string filePath, DataRow oldRow, DataRow newRow, Dictionary<string, double> significantRegressions, Dictionary<string, double> percentageChanges, string testName)`
- L337-359 _private* method_ `static int Main(string[] args)`
