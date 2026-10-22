# CSharp / PerfreportTool

- project root: `Source/Programs/CSVTools/PerfReportTool`
- files: 28; symbols: 1029
- symbol kinds: class=78, const=8, ctor=98, enum=17, enumerator=55, field=452, interface=1, method=308, operator=1, property=9, struct=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/PerfReportTool/ColumnFilters/ISummaryTableColumnFilter.cs` (PerfreportTool)


#### interface `PerfReportTool.ISummaryTableColumnFilter`  
`internal interface ISummaryTableColumnFilter`  
_internal; L5-8_
- L7 _public* method_ `bool ShouldFilter(SummaryTableColumn column, SummaryTable table)`

### `Source/Programs/CSVTools/PerfReportTool/ColumnFilters/MetadataColumnFilter.cs` (PerfreportTool)


#### class `PerfReportTool.MetadataColumnFilter`  
`internal class MetadataColumnFilter : ISummaryTableColumnFilter`  
_internal; L8-29_
- inherits: `ISummaryTableColumnFilter`
- L11 _private field_ `private HashSet<string> ColumnsToIgnore`
- L13-16 _public ctor_ `public MetadataColumnFilter(List<string> columnsToNotFilter)`
- L18-28 _public method_ `public bool ShouldFilter(SummaryTableColumn column, SummaryTable table)`

### `Source/Programs/CSVTools/PerfReportTool/ColumnFilters/RegressionColumnFilter.cs` (PerfreportTool)


#### class `PerfReportTool.RegressionColumnFilter`  
`internal class RegressionColumnFilter : ISummaryTableColumnFilter`  
_internal; L9-187_
- inherits: `ISummaryTableColumnFilter`
- L12 _private field_ `private string JoinRowsByStatName = null`
- L14 _private field_ `private double StdDevTreshold = 2.0`
- L16 _private field_ `private double OutlierStdDevThreshold = 4.0`
- L18 _private const_ `private const double MissingRowThresholdPercent = 0.6`
- L20-25 _public ctor_ `public RegressionColumnFilter(string joinRowsByName, float stdDevThreshold, float outlierStdDevThreshold)`
- L34-120 _public method_ `public bool ShouldFilter(SummaryTableColumn column, SummaryTable table)`
- L122-128 _private method_ `private bool IsValueOutsideThreshold(double value, double mean, double stdDev, double numStdDevations, bool highIsBad)`
- L130-134 _private method_ `private void CalculateStdDevAndMeanForRange(List<Tuple<int, double>> rows, out double mean, out double stdDev)`
- L136-146 _private method_ `private void CalculateStdDevAndMeanForRange(List<double> values, out double mean, out double stdDev)`
- L148-160 _private method_ `private List<Tuple<int, double>> GetNonEmptyRows(SummaryTableColumn column, int start, int end)`
- L162-186 _private method_ `private int GetNumRowsInFirstRowGroup(SummaryTable table)`

### `Source/Programs/CSVTools/PerfReportTool/ColumnFilters/StatThresholdColumnFilter.cs` (PerfreportTool)


#### class `PerfReportTool.StatThresholdColumnFilter`  
`internal class StatThresholdColumnFilter : ISummaryTableColumnFilter`  
_internal; L8-41_
- inherits: `ISummaryTableColumnFilter`
- L10 _private field_ `private float StatThreshold`
- L11-14 _public ctor_ `public StatThresholdColumnFilter(float statThreshold)`
- L16-40 _public method_ `public bool ShouldFilter(SummaryTableColumn column, SummaryTable table)`

### `Source/Programs/CSVTools/PerfReportTool/CsvFileCache..cs` (PerfreportTool)


#### class `PerfReportTool.CachedCsvFile`  
`class CachedCsvFile`  
_internal*; L22-235_
- L30-120 _public ctor_ `public CachedCsvFile(string inFilename, bool useCacheFiles, DerivedMetadataMappings inDerivedMetadataMappings, DerivedCsvStatDefinition[] inDerivedCsvStatDefinitions)`
- L122-129 _private method_ `private void AddDerivedMetadataToCsv(CsvStats csvStats)`
- L131-150 _public method_ `public void PrepareCsvData()`
- L152-173 _public method_ `public CsvStats GetFinalCsv()`
- L175-187 _public method_ `public bool DoesMetadataMatchQuery(QueryExpression metadataQuery)`
- L189-220 _public method_ `public void ComputeSummaryTableCacheId(string reportTypeId)`
- L223 _public field_ `public string filename`
- L224 _public field_ `public string summaryTableCacheId`
- L225 _public field_ `public string[] textCsvLines`
- L226 _public field_ `public CsvStats dummyCsvStats`
- L227 _public field_ `public CsvStats finalCsv`
- L228 _public field_ `public CsvMetadata metadata`
- L229 _public field_ `public SummaryTableRowData cachedSummaryTableRowData`
- L230 _public field_ `public ReportTypeInfo reportTypeInfo`
- L231 _public field_ `public XmlVariableMappings xmlVariableMappings`
- L232 _public field_ `public DerivedCsvStatDefinition[] derivedCsvStatDefinitions`
- L234 _private* field_ `FileType fileType`

#### enum `PerfReportTool.CachedCsvFile.FileType`  
`enum FileType`  
_private*; L24-29_
- L26 _public* enumerator_ `TextCsv`
- L27 _public* enumerator_ `BinaryCsv`
- L28 _public* enumerator_ `SummaryTableCachePrc`

#### class `PerfReportTool.ExternalMetadata`  
`class ExternalMetadata : Dictionary<string, string>`  
_internal*; L237-240_
- inherits: `Dictionary<string, string>`

#### class `PerfReportTool.ExternalMetadataCache`  
`class ExternalMetadataCache`  
_internal*; L242-342_
- L244-247 _public ctor_ `public ExternalMetadataCache(List<string> inExternalMetadataSourceStrings)`
- L248-267 _public method_ `public void InjectExternalMetadata(SummaryTableRowData summaryTableRowData)`
- L269-303 _private* method_ `ExternalMetadata LoadExternalMetadataFile(string filename)`
- L308-337 _private* method_ `static string ResolveExternalMetadataFilename(string sourceFilename, SummaryTableRowData summaryTableRowData)`
- L340 _private* field_ `Dictionary<string, ExternalMetadata> cachedExternalMetadataFiles = ...`
- L340 _private* field_ `Dictionary< cachedExternalMetadataFiles = new Dictionary<string, ExternalMetadata>()`
- L341 _private* field_ `List<string> externalMetadataSourceStrings`

#### class `PerfReportTool.CsvFileCache`  
`class CsvFileCache`  
_internal*; L344-612_
- L346-405 _public ctor_ `public CsvFileCache( string[] inCsvFilenames, int inLookaheadCount, int inThreadCount, bool inUseCacheFiles, QueryExpression inMetadataQuery, ReportXML inReportXml, ReportTypeParams inReportTypeParams, bool inBulkMode, bool inSummaryTableCacheOnlyMode, bool inSummaryTableCacheUseOnlyCsvID, bool inRemoveDuplicates, bool inRequireMetadata, string inSummaryTableCacheDir, bool inListFilesMode, ExternalMetadataCache inExternalMetadataCache)`
- L407-446 _public method_ `public CachedCsvFile GetNextCachedCsvFile()`
- L448-451 _private* method_ `static void PrecacheThreadRun()`
- L453-547 _private* method_ `void ThreadRun()`
- L549-568 _private* method_ `ReportTypeInfo GetCsvReportTypeInfo(CachedCsvFile csvFile, bool bBulkMode)`
- L571 _private* field_ `ThreadStart[] precacheJobs`
- L572 _private* field_ `Thread[] precacheThreads`
- L573 _private* field_ `int writeIndex`
- L574 _private* field_ `int readIndex`
- L575 _private* field_ `int lookaheadCount`
- L576 _private* field_ `int countFreedSinceLastGC`
- L577 _private* field_ `bool useCacheFiles`
- L578 _private* field_ `bool bulkMode`
- L579 _private* field_ `bool bRequireMetadata`
- L580 _private* field_ `bool summaryTableCacheOnlyMode`
- L581 _private* field_ `bool summaryTableCacheUseOnlyCsvID`
- L582 _private* field_ `QueryExpression metadataQuery`
- L583 _private* field_ `string summaryTableCacheDir`
- L584 _private* field_ `ReportXML reportXml`
- L585 _private* field_ `ReportTypeParams reportTypeParams`
- L586 _private* field_ `DerivedMetadataMappings derivedMetadataMappings`
- L587 _private* field_ `DerivedCsvStatDefinition[] derivedCsvStatDefinitions`
- L589 _private* field_ `Dictionary<string, string> csvIdToFilename`
- L589 _private* field_ `Dictionary< csvIdToFilename`
- L590 _public field_ `public int duplicateCount = 0`
- L591 _private* field_ `bool bRemoveDuplicates`
- L592 _private* field_ `bool bListFilesMode`
- L594 _private* field_ `static CsvFileCache fileCache`
- L595 _private* field_ `BlockingCollection<CsvFileInfo> outCsvQueue`
- L609 _private* field_ `CsvFileInfo[] csvFileInfos`
- L611 _private* field_ `ExternalMetadataCache externalMetadataCache`

#### class `PerfReportTool.CsvFileCache.CsvFileInfo`  
`class CsvFileInfo`  
_private*; L597-608_
- L599-604 _public ctor_ `public CsvFileInfo(string inFilename)`
- L605 _public field_ `public CachedCsvFile cachedFile`
- L606 _public field_ `public string filename`
- L607 _public field_ `public bool isValid`

### `Source/Programs/CSVTools/PerfReportTool/PerfReportTool.cs` (PerfreportTool)


#### class `PerfReportTool.Version`  
`class Version`  
_internal*; L24-30_
- L27 _private field_ `private static string VersionString = "4.274.1"`
- L29 _public method_ `public static string Get()`

#### enum `PerfReportTool.SummaryTableOutputFormat`  
`enum SummaryTableOutputFormat`  
_internal*; L33-38_
- attrs: `[Flags]`
- L35 _public* enumerator_ `Html = 1 << 0`
- L36 _public* enumerator_ `Csv = 1 << 1`
- L37 _public* enumerator_ `Json = 1 << 2`

#### class `PerfReportTool.HashHelper`  
`class HashHelper`  
_internal*; L40-60_
- L42-59 _public method_ `public static string StringToHashStr(string strIn, int maxCharsOut = -1)`

#### class `PerfReportTool.SummaryTableCacheStats`  
`class SummaryTableCacheStats`  
_internal*; L62-84_
- L64 _public field_ `public int WriteCount = 0`
- L65 _public field_ `public int HitCount = 0`
- L66 _public field_ `public int MissCount = 0`
- L67 _public field_ `public int PurgeCount = 0`
- L69-83 _public method_ `public void LogStats()`

#### class `PerfReportTool.Program`  
`class Program : CommandLineTool`  
_internal*; L86-2547_
- inherits: `CommandLineTool`
- L88 _private* field_ `static string formatString = "PerfReportTool v" + Version.Get() + "\n" + "\n" + "Format: \n" + " -csv <filename> or -csvdir <directory path> or -summaryTableCacheIn <directory path> or\n" + " -csvList <comma separated> or -prcLis ...`
- L266 _private* field_ `Dictionary<string, StatDisplayInfo> statDisplayNameMapping`
- L266 _private* field_ `Dictionary< statDisplayNameMapping`
- L267 _private* field_ `ReportXML reportXML`
- L269-273 _private* method_ `string GetBaseDirectory()`
- L275-903 _private* method_ `void Run(string[] args)`
- L905-938 _private* method_ `SummaryTableInfo GetTableInfo(string summaryTableName, string customSummaryTableFilterString = null, string customSummaryTableRowSortString = null)`
- L940-946 _private* method_ `void WriteSummaryTableReport(string outputDir, string filenameWithoutExtension, SummaryTable table, List<string> columnFilterList, List<string> rowSortList, bool bCollated, SummaryTableOutputFormat outputFormats, bool bSpreadsheetFriendlyStrings, List<SummarySectionBoundaryInfo> sectionBoundaries, string weightByColumnName)`
- L948-1072 _private* method_ `void WriteSummaryTableReport(string outputDir, string filenameWithoutExtension, SummaryTable table, SummaryTableInfo tableInfo, bool bCollated, SummaryTableOutputFormat outputFormats, bool bSpreadsheetFriendlyStrings, string weightByColumnNameOverride, string telemetrySessionLabel = null, string telemetryTestIdentity = null, IReadOnlyDictionary<string, string> telemetryPayloadMetadata = null)`
- L1074-1093 _private* method_ `IEnumerable<ISummaryTableColumnFilter> MakeAdditionalColumnFilters(SummaryTableInfo tableInfo)`
- L1095-1118 _private* method_ `string ReplaceFileExtension(string path, string newExtension)`
- L1120 _private* field_ `static Dictionary<string, bool> UniqueHTMLFilemameLookup = ...`
- L1120 _private* field_ `static Dictionary< UniqueHTMLFilemameLookup = new Dictionary<string, bool>()`
- L1122-1143 _private* method_ `void WriteCleanCsv(CachedCsvFile csvFile, string outCsvFilename, ReportTypeInfo reportTypeInfo)`
- L1145-1164 _private* method_ `CsvStats ProcessCsv(CachedCsvFile csvFile, out int numFramesStripped, out CsvStats csvStatsUnstripped, int minX = 0, int maxX = Int32.MaxValue, PerfLog perfLog = null, bool bStripStatsByEvents = true)`
- L1202-1225 _private* method_ `string ExpandGraphStatListDerivedStats(string originalGraphStatNamesStr, CsvStats csvStats)`
- L1227-1519 _private* method_ `void GenerateReport(CachedCsvFile csvFile, string outputDir, bool bBulkMode, SummaryTableRowData rowData, bool bBatchedGraphs, bool writeDetailedReport, bool bReadStatMinValues, bool bReadStatMaxValues, ReportTypeInfo reportTypeInfo, string csvDir)`
- L1520-1574 _private* method_ `CsvStats ReadCsvStats(CachedCsvFile csvFile, int minX, int maxX)`
- L1576-1603 _private* method_ `CsvStats StripCsvStatsByEvents(CsvStats csvStats, out int numFramesStripped)`
- L1608-1925 _private* method_ `void WriteReport(string htmlFilename, string title, List<CsvSvgInfo> csvSvgInfoList, ReportTypeInfo reportTypeInfo, CsvStats csvStats, CsvStats csvStatsUnstripped, int numFramesStripped, int minX, int maxX, bool bBulkMode, SummaryTableRowData summaryRowData)`
- L1928-1990 _private* method_ `void WriteEmail(string htmlFilename, string title, List<CsvSvgInfo> csvSvgInfoList, ReportTypeInfo reportTypeInfo, CsvStats csvStats, CsvStats csvStatsUnstripped, int minX, int maxX, bool bBulkMode)`
- L1991-1994 _private* method_ `string StripSpaces(string str)`
- L1996-2000 _private* method_ `string GetTempFilename(string csvFilename)`
- L2008-2186 _private* method_ `string GetCsvToSvgArgs(string csvFilename, string svgFilename, ReportGraph graph, double thicknessMultiplier, int minx, int maxx, bool multipleCSVs, int graphIndex, CsvToSvgArgFormat argFormat, float scaleby = 1.0f)`
- L2189-2354 _private* method_ `GraphParams GetCsvToSvgGraphParams(ReportGraph graph, double thicknessMultiplier, int minx, int maxx, bool multipleCSVs, int graphIndex, float scaleby = 1.0f)`
- L2357-2381 _private* method_ `Process LaunchCsvToSvgAsync(string args)`
- L2383-2404 _private* method_ `int CountCSVs(CsvStats csvStats)`
- L2406-2427 _private* method_ `static int Main(string[] args)`
- L2429-2444 _private* method_ `bool matchesPattern(string str, string pattern)`
- L2446-2474 _private* method_ `System.IO.FileInfo[] GetFilesWithSearchPattern(string directory, string searchPatternStr, bool recurse, int maxFileAgeDays = -1)`
- L2476-2496 _private* method_ `void ConvertJsonToPrcs(string jsonFilename, string prcOutputDir)`
- L2498-2503 _private* method_ `Dictionary<string, dynamic> JsonToDynamicDict(string jsonStr)`
- L2506-2546 _private* method_ `dynamic GetJsonValue(JsonElement jsonElement)`

#### class `PerfReportTool.Program.CsvSvgInfo`  
`private class CsvSvgInfo`  
_private; L1167-1200_
- L1177 _public property_ `public ReportGraph Graph { get; set; }`
- L1178 _public property_ `public GraphFormat Format { get; set; }`
- L1179 _public property_ `public string SvgFilename { get; set; }`
- L1181-1189 _public method_ `public static CsvSvgInfo CreateInlineGraphInfo(ReportGraph graph, string svgFilename)`
- L1191-1199 _public method_ `public static CsvSvgInfo CreateEmbeddedUrlGraphInfo(ReportGraph graph)`

#### enum `PerfReportTool.Program.CsvSvgInfo.GraphFormat`  
`public enum GraphFormat`  
_public; L1169-1175_
- L1172 _public* enumerator_ `Inline`
- L1174 _public* enumerator_ `Url`

#### enum `PerfReportTool.Program.CsvToSvgArgFormat`  
`enum CsvToSvgArgFormat`  
_private*; L2002-2006_
- L2004 _public* enumerator_ `CommandLine`
- L2005 _public* enumerator_ `Url`

### `Source/Programs/CSVTools/PerfReportTool/Properties/AssemblyInfo.cs` (PerfreportTool)
_(no declarations)_


### `Source/Programs/CSVTools/PerfReportTool/ReportGraph.cs` (PerfreportTool)


#### class `PerfReportTool.OptionalString`  
`class OptionalString`  
_internal*; L11-48_
- L13-17 _public ctor_ `public OptionalString(string valueIn)`
- L18-21 _public ctor_ `public OptionalString()`
- L22-43 _public ctor_ `public OptionalString(XElement element, string Name, bool IsElement = false, XmlVariableMappings vars = null )`
- L45 _public method_ `public void InheritFrom(OptionalString baseVersion)`
- L46 _public field_ `public bool isSet`
- L47 _public field_ `public string value`

#### class `PerfReportTool.Optional`  
`class Optional<T>`  
_internal*; L50-78_
- L52-56 _public ctor_ `public Optional(T valueIn)`
- L57-60 _public ctor_ `public Optional()`
- L61-73 _public ctor_ `public Optional(XElement element, string AttributeName, XmlVariableMappings vars = null)`
- L74 _public method_ `public void InheritFrom(Optional<T> baseVersion)`
- L76 _public field_ `public T value`
- L77 _public field_ `public bool isSet`

#### class `PerfReportTool.OptionalHelper`  
`static class OptionalHelper`  
_internal*; L81-92_
- L83-86 _public method_ `public static string GetDoubleSetting(Optional<double> setting, string cmdline)`
- L88-91 _public method_ `public static string GetStringSetting(OptionalString setting, string cmdline)`

#### class `PerfReportTool.ReportGraph`  
`class ReportGraph`  
_internal*; L94-164_
- L96-115 _public ctor_ `public ReportGraph(XElement element, XmlVariableMappings vars)`
- L117-155 _public method_ `public bool ShouldShow(CsvStats stats)`
- L156 _public field_ `public string title`
- L157 _public field_ `public Optional<double> budget`
- L158 _public field_ `public bool inSummary`
- L159 _public field_ `public Optional<double> minFilterStatValue`
- L160 _public field_ `public GraphSettings settings`
- L162 _public field_ `public bool isInline`
- L163 _public field_ `public string parent`

#### class `PerfReportTool.GraphSettings`  
`class GraphSettings`  
_internal*; L166-297_
- L168-219 _public ctor_ `public GraphSettings(XElement element, XmlVariableMappings vars = null)`
- L220-257 _public method_ `public void InheritFrom(GraphSettings baseSettings)`
- L258 _public field_ `public Optional<bool> smooth`
- L259 _public field_ `public OptionalString statString`
- L260 _public field_ `public Optional<double> thickness`
- L261 _public field_ `public Optional<double> minY`
- L262 _public field_ `public Optional<double> maxY`
- L263 _public field_ `public Optional<double> maxAutoMaxY`
- L264 _public field_ `public Optional<double> threshold`
- L265 _public field_ `public Optional<double> averageThreshold`
- L266 _public field_ `public Optional<double> minFilterStatValue`
- L267 _public field_ `public OptionalString minFilterStatName`
- L268 _public field_ `public Optional<double> smoothKernelSize`
- L269 _public field_ `public Optional<double> smoothKernelPercent`
- L270 _public field_ `public Optional<double> compression`
- L271 _public field_ `public Optional<int> width`
- L272 _public field_ `public Optional<int> height`
- L274 _public field_ `public Optional<bool> stacked`
- L275 _public field_ `public Optional<bool> showAverages`
- L276 _public field_ `public Optional<bool> showTotals`
- L277 _public field_ `public Optional<bool> filterOutZeros`
- L278 _public field_ `public Optional<int> maxHierarchyDepth`
- L279 _public field_ `public OptionalString hideStatPrefix`
- L280 _public field_ `public OptionalString mainStat`
- L281 _public field_ `public OptionalString showEvents`
- L282 _public field_ `public OptionalString ignoreStats`
- L283 _public field_ `public Optional<double> statMultiplier`
- L284 _public field_ `public Optional<double> legendAverageThreshold`
- L286 _public field_ `public Optional<bool> requiresDetailedStats`
- L287 _public field_ `public Optional<bool> snapToPeaks`
- L288 _public field_ `public Optional<int> lineDecimalPlaces`
- L290 _public field_ `public OptionalString startEvent`
- L291 _public field_ `public Optional<int> startEventOffset`
- L292 _public field_ `public OptionalString endEvent`
- L293 _public field_ `public Optional<int> endEventOffset`
- L295 _public field_ `public OptionalString requiredEvents`

### `Source/Programs/CSVTools/PerfReportTool/ReportType.cs` (PerfreportTool)


#### class `PerfReportTool.ReportTypeParams`  
`class ReportTypeParams`  
_internal*; L13-17_
- L15 _public field_ `public string reportTypeOverride`
- L16 _public field_ `public bool forceReportType`

#### class `PerfReportTool.ReportTypeInfo`  
`class ReportTypeInfo`  
_internal*; L19-98_
- L21-66 _public ctor_ `public ReportTypeInfo(XElement element, Dictionary<string, XElement> sharedSummaries, string baseXmlDirectory, XmlVariableMappings inVariableMappings, CsvMetadata csvMetadata )`
- L68-71 _public method_ `public string GetSummaryTableCacheID()`
- L73-87 _private method_ `private void ComputeSummaryTableCacheID()`
- L89 _public field_ `public List<ReportGraph> graphs`
- L90 _public field_ `public List<Summary> summaries`
- L91 _public field_ `public string name`
- L92 _public field_ `public string title`
- L93 _public field_ `public string[] metadataToShowList`
- L94 _public field_ `public string summaryTableCacheID`
- L95 _public field_ `public bool bStripEvents`
- L97 _public field_ `public XmlVariableMappings vars`

### `Source/Programs/CSVTools/PerfReportTool/ReportXml.cs` (PerfreportTool)


#### class `PerfReportTool.CsvEventStripInfo`  
`class CsvEventStripInfo`  
_internal*; L15-19_
- L17 _public field_ `public string beginName`
- L18 _public field_ `public string endName`

#### class `PerfReportTool.DerivedMetadataEntry`  
`class DerivedMetadataEntry`  
_internal*; L21-62_
- L23-42 _public ctor_ `public DerivedMetadataEntry(XElement derivedMetadataEntry)`
- L43-45 _private ctor_ `private DerivedMetadataEntry()`
- L46-57 _public method_ `public DerivedMetadataEntry ApplyVariableMappings(XmlVariableMappings vars)`
- L58 _public field_ `public string metadataQuery`
- L59 _public field_ `public string destName`
- L60 _public field_ `public string destValue`
- L61 _public field_ `public bool bHasVariables`

#### class `PerfReportTool.DerivedCsvStatDefinition`  
`class DerivedCsvStatDefinition`  
_internal*; L64-77_
- L66-70 _public ctor_ `public DerivedCsvStatDefinition(XElement element, XmlVariableMappings vars)`
- L71-74 _public method_ `public string getExpressionStr()`
- L75 _public field_ `public string name`
- L76 _private* field_ `string expression`

#### class `PerfReportTool.DerivedMetadataMappings`  
`class DerivedMetadataMappings`  
_internal*; L79-114_
- L81-84 _public ctor_ `public DerivedMetadataMappings()`
- L85-112 _public method_ `public void ApplyMapping(CsvMetadata csvMetadata, XmlVariableMappings vars)`
- L113 _public field_ `public List<DerivedMetadataEntry> entries`

#### class `PerfReportTool.ReportXML`  
`class ReportXML`  
_internal*; L116-695_
- L118-125 _private* method_ `bool IsAbsolutePath(string path)`
- L127-133 _private* method_ `static XDocument LoadXmlDocument(string filename)`
- L135-147 _private* method_ `static void StripNamespaceRecursive(XElement element, XNamespace namespaceToStrip)`
- L150-419 _public ctor_ `public ReportXML( string graphXMLFilenameIn, string reportXMLFilenameIn, string baseXMLDirectoryOverride, string additionalSummaryTableXmlFilename, string summaryTableXmlSubstStr, string summaryTableXmlAppendStr, string summaryTableXmlRowSortAppendStr )`
- L421-549 _public method_ `public ReportTypeInfo GetReportTypeInfo(string reportType, CachedCsvFile csvFile, bool bBulkMode, bool forceReportType)`
- L551-629 _private* method_ `bool IsReportTypeXMLCompatibleWithStats(XElement reportTypeElement, CsvStats csvStats, XmlVariableMappings vars, bool bIsDefaultFallback=false)`
- L632 _public method_ `public Dictionary<string, StatDisplayInfo> GetDisplayNameMapping()`
- L634-644 _public method_ `public SummaryTableInfo GetSummaryTable(string name)`
- L646-649 _public method_ `public List<CsvEventStripInfo> GetCsvEventsToStrip()`
- L651-654 _public method_ `public List<string> GetSummaryTableNames()`
- L656-664 _public method_ `public string GetMetadataProxyInfo(string key)`
- L666-673 _public method_ `public DerivedCsvStatDefinition GetDerivedCsvStatDefinition(string name)`
- L675 _private* field_ `Dictionary<string, SummaryTableInfo> summaryTables`
- L675 _private* field_ `Dictionary< summaryTables`
- L677 _private* field_ `XElement reportTypesElement`
- L678 _private* field_ `XElement rootElement`
- L679 _private* field_ `XElement graphGroupsElement`
- L680 _private* field_ `XElement summaryTablesElement`
- L681 _private* field_ `XElement globalVariableSetElement`
- L682 _private* field_ `XmlVariableMappings staticVariableMappings`
- L683 _private* field_ `string defaultReportTypeName`
- L684 _private* field_ `Dictionary<string, XElement> sharedSummaries`
- L684 _private* field_ `Dictionary< sharedSummaries`
- L685 _private* field_ `Dictionary<string, GraphSettings> graphs`
- L685 _private* field_ `Dictionary< graphs`
- L686 _private* field_ `Dictionary<string, StatDisplayInfo> statDisplayNameMapping`
- L686 _private* field_ `Dictionary< statDisplayNameMapping`
- L687 _private* field_ `Dictionary<string, string> metadataProxyInfo`
- L687 _private* field_ `Dictionary< metadataProxyInfo`
- L688 _public field_ `public SummaryTableColumnFormatInfoCollection columnFormatInfoList`
- L689 _private* field_ `string baseXmlDirectory`
- L691 _private* field_ `List<CsvEventStripInfo> csvEventsToStrip`
- L692 _private* field_ `string reportTypeXmlFilename`
- L693 _public field_ `public DerivedMetadataMappings derivedMetadataMappings`
- L694 _public field_ `public Dictionary<string, DerivedCsvStatDefinition> derivedCsvStatDefinitions`
- L694 _public field_ `public Dictionary< derivedCsvStatDefinitions`

#### class `PerfReportTool.XmlVariableMappings`  
`class XmlVariableMappings`  
_internal*; L697-910_
- L699-711 _public method_ `public void SetVariable(string Name, string Value, bool bValidate = true)`
- L713-720 _public method_ `public void SetMetadataVariables(CsvMetadata csvMetadata)`
- L722-734 _public method_ `public void DumpToLog(bool bIncludeMetadata = false)`
- L735-765 _public method_ `public void SerializeToJson(string Filename, string toMatch, string toIgnore)`
- L767-851 _public method_ `public string ResolveVariables(string attributeValue)`
- L853-907 _public method_ `public void ApplyVariableSet(XElement variableSetElement, CsvMetadata csvMetadata, double parentMultiplier=1.0)`
- L909 _private* field_ `Dictionary<string, string> vars = ...`
- L909 _private* field_ `Dictionary< vars = new Dictionary<string, string>()`

#### class `PerfReportTool.Extensions`  
`static class Extensions`  
_internal*; L913-1003_
- L915-923 _public method_ `public static string GetValue(this XElement element, XmlVariableMappings xmlVariableMappings = null)`
- L924-927 _public method_ `public static T GetRequiredAttribute<T>(this XElement element, string attributeName)`
- L929-932 _public method_ `public static T GetRequiredAttribute<T>(this XElement element, XmlVariableMappings xmlVariableMappings, string attributeName)`
- L934-937 _public method_ `public static T GetSafeAttribute<T>(this XElement element, string attributeName, T defaultValue = default)`
- L939-942 _public method_ `public static T GetSafeAttribute<T>(this XElement element, XmlVariableMappings xmlVariableMappings, string attributeName, T defaultValue = default)`
- L944-1002 _private method_ `private static T GetAttributeInternal<T>(this XElement element, XmlVariableMappings xmlVariableMappings, string attributeName, T defaultValue, bool throwIfNotFound)`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/BoundedStatValuesSummary.cs` (PerfreportTool)


#### class `PerfSummaries.BoundedStatValuesSummary`  
`class BoundedStatValuesSummary : Summary`  
_internal*; L13-512_
- inherits: `Summary`
- L52-100 _public ctor_ `public BoundedStatValuesSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L102 _public ctor_ `public BoundedStatValuesSummary()`
- L104 _public method_ `public override string GetName()`
- L106-503 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L504-506 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L507 _private* field_ `string title`
- L508 _private* field_ `string beginEvent`
- L509 _private* field_ `string endEvent`
- L510 _private* field_ `double endOffsetPercentage`
- L511 _private* field_ `List<Column> columns`

#### class `PerfSummaries.BoundedStatValuesSummary.Column`  
`class Column`  
_private*; L15-51_
- L17 _public field_ `public string name`
- L18 _public field_ `public string formula`
- L19 _public field_ `public double value`
- L20 _public field_ `public string summaryStatName`
- L21 _public field_ `public string statName`
- L22 _public field_ `public string otherStatName`
- L23 _public field_ `public bool perSecond`
- L24 _public field_ `public bool filterOutZeros`
- L25 _public field_ `public bool applyEndOffset`
- L26 _public field_ `public double multiplier`
- L27 _public field_ `public double threshold`
- L28 _public field_ `public double frameExponent`
- L29 _public field_ `public double statExponent`
- L30 _public field_ `public ColourThresholdList colourThresholdList`
- L32 _public ctor_ `public Column()`
- L34-50 _public ctor_ `public Column(Column inCol)`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/BucketSummary.cs` (PerfreportTool)


#### class `PerfSummaries.BucketSummary`  
`class BucketSummary : Summary`  
_internal*; L14-219_
- inherits: `Summary`
- L29-76 _public ctor_ `public BucketSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L77 _public ctor_ `public BucketSummary()`
- L79 _public method_ `public override string GetName()`
- L81-206 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L208 _public field_ `public double[] Buckets`
- L209 _public field_ `public string Title`
- L210 _public field_ `public bool ReportBelowRange`
- L211 _public field_ `public bool ReportAboveRange`
- L212 _public field_ `public Colour LowEndColor`
- L213 _public field_ `public Colour HighEndColor`
- L214 _private field_ `private string ColumnHeaderPrecision = "0"`
- L216 _private* field_ `ESortMode SortMode = ESortMode.None`
- L217 _private* field_ `ESortDirection SortDirection`
- L218 _private field_ `private int SortByBucketIndex = -1`

#### enum `PerfSummaries.BucketSummary.ESortMode`  
`private enum ESortMode`  
_private; L16-21_
- L18 _public* enumerator_ `None`
- L19 _public* enumerator_ `Alpha`
- L20 _public* enumerator_ `BucketIndex`

#### enum `PerfSummaries.BucketSummary.ESortDirection`  
`private enum ESortDirection`  
_private; L23-27_
- L25 _public* enumerator_ `Ascending`
- L26 _public* enumerator_ `Descending`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/CheckpointSummary.cs` (PerfreportTool)


#### class `PerfSummaries.CheckpointSummary`  
`class CheckpointSummary : Summary`  
_internal*; L16-198_
- inherits: `Summary`
- L34-59 _public ctor_ `public CheckpointSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L61-63 _public ctor_ `public CheckpointSummary()`
- L65 _public method_ `public override string GetName()`
- L67-80 _public method_ `public List<int> GetFramesMatchingEventString(string inEventString, CsvStats csvStats)`
- L82-190 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L191-193 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L195 _private* field_ `List<CaptureEventPoint> captureEventPoints`
- L196 _private* field_ `string metricPrefix`
- L197 _private* field_ `string summaryTitle`

#### class `PerfSummaries.CheckpointSummary.CaptureEventPoint`  
`class CaptureEventPoint`  
_private*; L18-32_
- L20 _public field_ `public string friendlyName`
- L21 _public field_ `public string eventString`
- L22 _public field_ `public string metricSuffix`
- L24 _public ctor_ `public CaptureEventPoint()`
- L26-31 _public ctor_ `public CaptureEventPoint(string inFriendlyName, string inEventString, string inMetricSuffix)`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/EventSummary.cs` (PerfreportTool)


#### class `PerfSummaries.EventSummary`  
`class EventSummary : Summary`  
_internal*; L12-110_
- inherits: `Summary`
- L14-22 _public ctor_ `public EventSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L24 _public ctor_ `public EventSummary()`
- L26 _public method_ `public override string GetName()`
- L28-101 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L102-104 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L105 _private* field_ `string[] events`
- L106 _private* field_ `double[] colourThresholds`
- L107 _private* field_ `string title`
- L108 _private* field_ `string summaryStatName`
- L109 _private* field_ `bool bSortByName`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/ExtraLinksSummary.cs` (PerfreportTool)


#### class `PerfSummaries.ExtraLinksSummary`  
`class ExtraLinksSummary : Summary`  
_internal*; L13-145_
- inherits: `Summary`
- L67-76 _public ctor_ `public ExtraLinksSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory, bool bInLinkTemplates=false)`
- L78 _public ctor_ `public ExtraLinksSummary()`
- L80 _public method_ `public override string GetName()`
- L82-139 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L140-142 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L143 _private* field_ `string title`
- L144 _private* field_ `bool bLinkTemplates`

#### class `PerfSummaries.ExtraLinksSummary.ExtraLink`  
`class ExtraLink`  
_private*; L15-66_
- L17-51 _public ctor_ `public ExtraLink(string fileLine, string inLinkTemplateCsvId)`
- L52-61 _public method_ `public string GetLinkString(bool bIsSummaryTable)`
- L62 _public field_ `public string ReportText`
- L63 _public field_ `public string SummaryTableText`
- L64 _public field_ `public string LinkURL`
- L65 _public field_ `public string LinkTemplateCsvId`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/FPSChartSummary.cs` (PerfreportTool)


#### class `PerfSummaries.FPSChartSummary`  
`class FPSChartSummary : Summary`  
_internal*; L13-553_
- inherits: `Summary`
- L15-32 _public ctor_ `public FPSChartSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L34 _public ctor_ `public FPSChartSummary()`
- L36 _public method_ `public override string GetName()`
- L38-45 _private* method_ `float GetEngineHitchToNonHitchRatio()`
- L57-165 _private* method_ `FpsChartData ComputeFPSChartDataForFrames(List<float> frameTimes, bool skiplastFrame)`
- L193-211 _private method_ `private ColourThresholdList ComputeFrameTimeColorThresholdsFromMVP( int fps )`
- L213-538 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L539-541 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L543 _private* field_ `int fps`
- L544 _private* field_ `int recommendedFps`
- L545 _private* field_ `float slowFrameTimeBuffer`
- L546 _private* field_ `float hitchThreshold`
- L547 _private* field_ `bool bUseEngineHitchMetric`
- L548 _private* field_ `bool bIgnoreHitchTimePercent`
- L549 _private* field_ `bool bIgnoreSlowFrameTimePercent`
- L550 _private* field_ `bool bIgnoreMVP`
- L551 _private* field_ `float engineHitchToNonHitchRatio`
- L552 _private* field_ `float engineMinTimeBetweenHitchesMs`

#### struct `PerfSummaries.FPSChartSummary.FpsChartData`  
`struct FpsChartData`  
_private*; L47-55_
- L49 _public field_ `public float MVP`
- L50 _public field_ `public float HitchesPerMinute`
- L51 _public field_ `public float HitchTimePercent`
- L52 _public field_ `public int HitchCount`
- L53 _public field_ `public float TotalTimeSeconds`
- L54 _public field_ `public float? SlowFrameTimePerecent`

#### class `PerfSummaries.FPSChartSummary.ColumnInfo`  
`class ColumnInfo`  
_private*; L167-191_
- L169-178 _public ctor_ `public ColumnInfo(string inName, double inValue, ColourThresholdList inColorThresholds, string inDetails=null, bool inIsAvgValue=false)`
- L180-183 _public method_ `public void UpdateColor()`
- L185 _public field_ `public string Name`
- L186 _public field_ `public double Value`
- L187 _public field_ `public string Color`
- L188 _public field_ `public ColourThresholdList ColorThresholds`
- L189 _public field_ `public string Details`
- L190 _public field_ `public bool isAverageValue`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/HistogramSummary.cs` (PerfreportTool)


#### class `PerfSummaries.HistogramSummary`  
`class HistogramSummary : Summary`  
_internal*; L12-144_
- inherits: `Summary`
- L14-40 _public ctor_ `public HistogramSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L42 _public ctor_ `public HistogramSummary()`
- L44 _public method_ `public override string GetName()`
- L46-137 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L139 _public field_ `public double[] ColourThresholds`
- L140 _public field_ `public double[] HistogramThresholds`
- L141 _public field_ `public string BudgetOverrideStatName`
- L142 _public field_ `public double BudgetOverrideStatBudget`
- L143 _private* field_ `bool bSuppressAveragesTable`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/HitchSummary.cs` (PerfreportTool)


#### class `PerfSummaries.HitchSummary`  
`class HitchSummary : Summary`  
_internal*; L13-126_
- inherits: `Summary`
- L15-28 _public ctor_ `public HitchSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L29 _public ctor_ `public HitchSummary()`
- L31 _public method_ `public override string GetName()`
- L33-124 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L125 _public field_ `public double[] HitchThresholds`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/MapOverlaySummary.cs` (PerfreportTool)


#### class `PerfSummaries.MapOverlaySummary`  
`class MapOverlaySummary : Summary`  
_internal*; L17-527_
- inherits: `Summary`
- L69-138 _public ctor_ `public MapOverlaySummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L139 _public ctor_ `public MapOverlaySummary()`
- L141 _public method_ `public override string GetName()`
- L143-148 _private* method_ `int toSvgX(float worldX, float worldY)`
- L150-155 _private* method_ `int toSvgY(float worldX, float worldY)`
- L157-197 _private* method_ `SVGPosition toSVGLocation(float worldX, float worldY, Rectangle imageRegion)`
- L199-207 _private* method_ `SVGPosition toSVGLocationClamped(float worldX, float worldY, Rectangle imageRegion, int imagePadding)`
- L209-231 _private method_ `private void CopyAndResizeImage(string sourceImagePath, string destImagePath, int destWidth, int destHeight)`
- L233-284 _private method_ `private void CopyAndTrimImage(string sourceImagePath, string destImagePath, int destWidth, int destHeight, Rectangle subRegion)`
- L286-362 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L364-499 _private method_ `private void GenerateImageSection(CsvStats csvStats, HtmlSection htmlSection, Rectangle imageRegion, string imageName)`
- L501-503 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L513 _private* field_ `string title`
- L514 _private* field_ `string sourceImagePath`
- L515 _private* field_ `float[] transform = new float[6]`
- L516 _private* field_ `float[] fullTransform = null`
- L517 _private* field_ `Matrix4x4 transformMatrix = Matrix4x4.Identity`
- L518 _private* field_ `string destImageFilename`
- L519 _private* field_ `float imageWidth`
- L520 _private* field_ `float imageHeight`
- L521 _private* field_ `float lineSplitDistanceThreshold`
- L522 _private* field_ `int framesPerLineSegment`
- L523 _private* field_ `bool createCroppedImage = false`
- L525 _private* field_ `List<MapOverlay> overlays = new List<MapOverlay>()`
- L526 _private* field_ `MapEventDimensions eventDimensions = new MapEventDimensions()`

#### class `PerfSummaries.MapOverlaySummary.MapOverlayEvent`  
`class MapOverlayEvent`  
_private*; L19-32_
- L21-24 _public ctor_ `public MapOverlayEvent(string inName)`
- L25-27 _public ctor_ `public MapOverlayEvent(XElement element)`
- L28 _public field_ `public string name`
- L29 _public field_ `public string summaryStatName`
- L30 _public field_ `public string shortName`
- L31 _public field_ `public string lineColor`

#### struct `PerfSummaries.MapOverlaySummary.SVGPosition`  
`struct SVGPosition`  
_private*; L34-38_
- L36 _public field_ `public int X`
- L37 _public field_ `public int Y`

#### class `PerfSummaries.MapOverlaySummary.MapOverlay`  
`class MapOverlay`  
_private*; L40-67_
- L42-61 _public ctor_ `public MapOverlay(XElement element, XmlVariableMappings vars)`
- L62 _public field_ `public string[] positionStatNames = new string[3]`
- L63 _public field_ `public string summaryStatNamePrefix`
- L64 _public field_ `public List<MapOverlayEvent> startEvents = new List<MapOverlayEvent>()`
- L65 _public field_ `public string lineColor`
- L66 _public field_ `public List<MapOverlayEvent> events = new List<MapOverlayEvent>()`

#### class `PerfSummaries.MapOverlaySummary.MapEventDimensions`  
`class MapEventDimensions`  
_private*; L505-511_
- L507 _public field_ `public float minX = float.MaxValue`
- L508 _public field_ `public float maxX = float.MinValue`
- L509 _public field_ `public float minY = float.MaxValue`
- L510 _public field_ `public float maxY = float.MinValue`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/PeakSummary.cs` (PerfreportTool)


#### class `PerfSummaries.PeakSummary`  
`class PeakSummary : Summary`  
_internal*; L13-293_
- inherits: `Summary`
- L61-81 _public ctor_ `public PeakSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L83 _public ctor_ `public PeakSummary()`
- L85 _public method_ `public override string GetName()`
- L87-162 _private* method_ `void WriteStatSection(HtmlSection htmlSection, CsvStats csvStats, PeakSummarySection section, StreamWriter LLMCsvData, SummaryTableRowData summaryTableRowData)`
- L164-174 _private* method_ `PeakSummarySection FindStatSection(CsvStats csvStats, string statName)`
- L176-216 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L220-229 _private* method_ `void AddStat(string statName, Optional<double> budget)`
- L231-256 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L258 _private* field_ `List<PeakSummarySection> peakSummarySections = new List<PeakSummarySection>()`
- L260 _private* field_ `Dictionary<string, PeakStatInfo> statInfoLookup = ...`
- L260 _private* field_ `Dictionary< statInfoLookup = new Dictionary<string, PeakStatInfo>()`
- L274-290 _private* method_ `PeakStatInfo getOrAddStatInfo(string statName)`
- L292 _private* field_ `string hideStatPrefix`

#### class `PerfSummaries.PeakSummary.PeakSummarySection`  
`class PeakSummarySection`  
_private*; L28-59_
- L30-34 _public ctor_ `public PeakSummarySection(string inTitle, string inStatFilterStr)`
- L35-41 _public ctor_ `public PeakSummarySection(XElement element, XmlVariableMappings vars)`
- L42-49 _public method_ `public bool StatMatchesSection(CsvStats csvStats, string statName)`
- L50-53 _public method_ `public void AddStat(PeakStatInfo statInfo)`
- L54 _private* field_ `string[] statNamesFilter`
- L55 _private* field_ `HashSet<string> statNameFilterSet`
- L57 _public field_ `public List<PeakStatInfo> stats = new List<PeakStatInfo>()`
- L58 _public field_ `public string title`

#### class `PerfSummaries.PeakSummary.PeakStatInfo`  
`class PeakStatInfo`  
_private*; L261-272_
- L263-268 _public ctor_ `public PeakStatInfo(string inName, string inShortName)`
- L269 _public field_ `public string name`
- L270 _public field_ `public string shortName`
- L271 _public field_ `public Optional<double> budget`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/StandardSummary.cs` (PerfreportTool)


#### class `PerfSummaries.StandardSummary`  
`class StandardSummary : Summary`  
_internal*; L14-51_
- inherits: `Summary`
- L20-22 _public ctor_ `public StandardSummary()`
- L24 _public method_ `public override string GetName()`
- L27-49 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/StatBudgetsSummary.cs` (PerfreportTool)


#### class `PerfSummaries.StatInfo`  
`class StatInfo`  
_internal*; L27-45_
- L29-34 _public ctor_ `public StatInfo( StatSamples inCsvStat )`
- L35-39 _public ctor_ `public StatInfo(string inName, double inAverageValue )`
- L41 _public field_ `public string name`
- L42 _public field_ `public double averageValue`
- L43 _public field_ `public StatSamples csvStat = null`
- L44 _public field_ `public ColourThresholdList colorThresholds = null`

#### class `PerfSummaries.StatBudgetsSummary`  
`class StatBudgetsSummary : Summary`  
_internal*; L47-224_
- inherits: `Summary`
- L49-72 _public ctor_ `public StatBudgetsSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L74 _public ctor_ `public StatBudgetsSummary()`
- L76 _public method_ `public override string GetName()`
- L78-88 _private* method_ `string StripStatPrefix(string statName)`
- L90-213 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L215 _private* field_ `ColourThresholdList colorThresholdsTotal = null`
- L216 _private* field_ `Dictionary<string, ColourThresholdList> statColorThresholds = ...`
- L216 _private* field_ `Dictionary< statColorThresholds = new Dictionary<string, ColourThresholdList>()`
- L218 _private* field_ `string title = ""`
- L219 _private* field_ `string metricName = null`
- L220 _private* field_ `string stripStatPrefix = null`
- L221 _private* field_ `string totalStatName = null`
- L222 _private* field_ `bool emitStatMetrics = false`
- L223 _private* field_ `bool showTotal = true`

### `Source/Programs/CSVTools/PerfReportTool/Summaries/TimingRegionSummary.cs` (PerfreportTool)


#### class `PerfSummaries.TimingRegionSummary`  
`class TimingRegionSummary : Summary`  
_internal*; L12-594_
- inherits: `Summary`
- L31-70 _public ctor_ `public TimingRegionSummary(XElement element, XmlVariableMappings vars, string baseXmlDirectory)`
- L71 _public ctor_ `public TimingRegionSummary()`
- L73 _public method_ `public override string GetName()`
- L172-184 _private* method_ `bool TryGetRegionFilterInfo(RegionEvent regionEvent, out RegionFilterInfo outRegionFilterInfo)`
- L188-304 _private* method_ `List<RegionEvent> GetRegionEvents(CsvStats csvStats, double startTime, double endTime)`
- L435-582 _public method_ `public override HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L583-585 _public method_ `public override void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L587 _private* field_ `string title`
- L588 _private* field_ `string beginEventName`
- L589 _private* field_ `string endEventName`
- L590 _private* field_ `string metricPrefix`
- L591 _private* field_ `bool bShowTimingTable`
- L592 _private* field_ `bool bFindLast`
- L593 _private* field_ `List<RegionFilterInfo> regionFilters = new List<RegionFilterInfo>()`

#### class `PerfSummaries.TimingRegionSummary.RegionFilterInfo`  
`class RegionFilterInfo`  
_private*; L15-30_
- L17-24 _public ctor_ `public RegionFilterInfo(XElement element, XmlVariableMappings vars, int indexIn)`
- L25 _public field_ `public string pattern`
- L26 _public field_ `public string busyTimeMetric = null`
- L27 _public field_ `public string hidePrefix = null`
- L28 _public field_ `public int index = 0`
- L29 _public field_ `public int trackDisplayThreshold = 0`

#### enum `PerfSummaries.TimingRegionSummary.ERangeType`  
`enum ERangeType`  
_private*; L75-80_
- L77 _public* enumerator_ `Before`
- L78 _public* enumerator_ `Inside`
- L79 _public* enumerator_ `After`

#### class `PerfSummaries.TimingRegionSummary.RegionEvent`  
`class RegionEvent`  
_private*; L82-170_
- L84-126 _public method_ `public static RegionEvent TryCreateFromCsvEvent(CsvEvent csvEvent)`
- L128-135 _public method_ `public double GetPairDuration()`
- L137-144 _public method_ `public string GetFullName()`
- L146-160 _public method_ `public RegionEvent CreateTruncatedPairEvent(double startTime, double endTime)`
- L162 _public field_ `public string category`
- L163 _public field_ `public string name`
- L164 _public field_ `public int frameNumber = -1`
- L165 _public field_ `public bool bBegin`
- L166 _public field_ `public double timestamp`
- L167 _public field_ `public RegionEvent otherEvent`
- L168 _public field_ `public RegionFilterInfo filterInfo`
- L169 _public field_ `public ERangeType rangeType = ERangeType.Inside`

#### class `PerfSummaries.TimingRegionSummary.RegionEventTrack`  
`class RegionEventTrack : IComparable<RegionEventTrack>`  
_private*; L306-433_
- inherits: `IComparable<RegionEventTrack>`
- L308-320 _public ctor_ `public RegionEventTrack(string inCategory, double inStartTime, double inEndTime, RegionFilterInfo inFilterInfo, double inTrackWidth, double inTrackHeight)`
- L321-338 _public method_ `public bool TryAddEvent(RegionEvent beginEvent)`
- L340-409 _public method_ `public void WriteToHtml(HtmlSection htmlSection, double xOffset, double yOffset, string backgroundColor="#ffffff")`
- L411-419 _public method_ `public int CompareTo(RegionEventTrack other)`
- L421 _public field_ `public string category`
- L422 _public field_ `public int filterIndex`
- L423 _public field_ `public double lastEventTime`
- L424 _public field_ `public double firstEventTime = double.MaxValue`
- L425 _public field_ `public List<RegionEvent> events = new List<RegionEvent>()`
- L426 _public field_ `public double startTime`
- L427 _public field_ `public double endTime`
- L428 _public field_ `public double trackWidth`
- L429 _public field_ `public double innerTrackWidth`
- L430 _public field_ `public double trackHeight`
- L431 _public field_ `public double regionDurationThreshold`
- L432 _public field_ `public RegionFilterInfo filterInfo`

### `Source/Programs/CSVTools/PerfReportTool/Summary.cs` (PerfreportTool)


#### class `PerfSummaries.SummaryFactory`  
`class SummaryFactory`  
_internal*; L16-43_
- L18-30 _public method_ `public static void Init()`
- L32-40 _public method_ `public static Summary Create(string summaryTypeName, XElement summaryXmlElement, XmlVariableMappings vars, string baseXmlDirectory)`
- L42 _private* field_ `static Dictionary<string, System.Type> summaryNameLookup = ...`
- L42 _private* field_ `static Dictionary< summaryNameLookup = null`

#### class `PerfSummaries.Summary`  
`abstract class Summary`  
_internal*; L45-259_
- L77-82 _public ctor_ `public Summary()`
- L83-86 _public method_ `public virtual HtmlSection WriteSummaryData(bool bWriteHtml, CsvStats csvStats, CsvStats csvStatsUnstripped, bool bWriteSummaryCsv, SummaryTableRowData rowData, string htmlFileName)`
- L88-92 _public method_ `public virtual void PostInit(ReportTypeInfo reportTypeInfo, CsvStats csvStats)`
- L94 _public method_ `public abstract string GetName()`
- L96-165 _public method_ `public void ReadStatsFromXML(XElement element, XmlVariableMappings vars)`
- L166-197 _public method_ `public CaptureData GetFramesForCapture(CaptureRange inCapture, List<float> FrameTimes, List<CsvEvent> EventsCaptured)`
- L199-210 _public method_ `public string[] GetUniqueStatNames()`
- L212-215 _protected method_ `protected ColourThresholdList ReadColourThresholdListXML(XElement colourThresholdEl, XmlVariableMappings vars)`
- L217-220 _protected method_ `protected double [] ReadColourThresholdsXML(XElement colourThresholdEl, XmlVariableMappings vars)`
- L222-230 _public method_ `public string GetStatThresholdColour(string StatToUse, double value)`
- L232-239 _public method_ `public ColourThresholdList GetStatColourThresholdList(string StatToUse)`
- L241-244 _public method_ `public void SetReportSummaryIndex(int index)`
- L246-249 _protected method_ `protected string MakeSectionId(string title)`
- L252 _public field_ `public List<CaptureRange> captures`
- L253 _public field_ `public List<string> stats`
- L254 _public field_ `public Dictionary<string, ColourThresholdList> StatThresholds`
- L254 _public field_ `public Dictionary< StatThresholds`
- L255 _public field_ `public bool useUnstrippedCsvStats`
- L256 _public field_ `public bool bStartCollapsed`
- L257 _public field_ `public bool bHideInDetailedReport = false`
- L258 _public field_ `public int reportSummaryIndex = -1`

#### class `PerfSummaries.Summary.CaptureRange`  
`public class CaptureRange`  
_public; L48-63_
- L50 _public field_ `public string name`
- L51 _public field_ `public string startEvent`
- L52 _public field_ `public string endEvent`
- L53 _public field_ `public bool includeFirstFrame`
- L54 _public field_ `public bool includeLastFrame`
- L55-62 _public ctor_ `public CaptureRange(string inName, string start, string end)`

#### class `PerfSummaries.Summary.CaptureData`  
`public class CaptureData`  
_public; L64-75_
- L66 _public field_ `public int startIndex`
- L67 _public field_ `public int endIndex`
- L68 _public field_ `public List<float> Frames`
- L69-74 _public ctor_ `public CaptureData(int start, int end, List<float> inFrames)`

#### class `PerfSummaries.HtmlSection`  
`class HtmlSection`  
_internal*; L263-360_
- L265-272 _public ctor_ `public HtmlSection(string titleIn, bool bStartCollapsedIn, string elementIdIn = null, int headingLevelIn=2)`
- L274-278 _public method_ `public void WriteLine(string text)`
- L279-282 _public method_ `public void Write(string text)`
- L284-293 _public method_ `public void WriteToFile( System.IO.StreamWriter htmlFile )`
- L295-302 _private method_ `private void FlushPendingLine()`
- L304-341 _protected method_ `protected void BeginHtmlSection(System.IO.StreamWriter htmlFile)`
- L343-351 _protected method_ `protected void EndHtmlSection(System.IO.StreamWriter htmlFile)`
- L353 _private* field_ `string title`
- L354 _private* field_ `StringBuilder pendingLine = new StringBuilder()`
- L355 _private* field_ `List<string> lines = new List<string>()`
- L356 _private* field_ `bool bStartCollapsed`
- L357 _private* field_ `int headingLevel`
- L358 _private* field_ `string elementId`
- L359 _private* field_ `string headingType`

### `Source/Programs/CSVTools/PerfReportTool/SummaryTable.cs` (PerfreportTool)


#### class `PerfSummaries.StatDisplayInfo`  
`class StatDisplayInfo`  
_internal*; L15-24_
- L17-21 _public ctor_ `public StatDisplayInfo(string inDisplayName, string inToolTip = null)`
- L22 _public field_ `public string displayName = null`
- L23 _public field_ `public string toolTip = null`

#### class `PerfSummaries.TableUtil`  
`class TableUtil`  
_internal*; L26-64_
- L28-32 _public method_ `public static string FormatStatName(string inStatName)`
- L34-37 _public method_ `public static string SanitizeHtmlString(string str)`
- L39-63 _public method_ `public static string SafeTruncateHtmlTableValue(string inValue, int maxLength)`

#### class `PerfSummaries.SummaryTableStyle`  
`class SummaryTableStyle`  
_internal*; L68-74_
- L72 _public field_ `public int maxColumnHeaderWidth = 220`
- L73 _public field_ `public int minColumnHeaderWidth = 75`

#### class `PerfSummaries.SummarySectionBoundaryInfo`  
`class SummarySectionBoundaryInfo`  
_internal*; L76-93_
- L78-86 _public ctor_ `public SummarySectionBoundaryInfo(string inStatName, string inStartToken, string inEndToken, int inLevel, bool inInCollatedTable, bool inInFullTable)`
- L87 _public field_ `public string statName`
- L88 _public field_ `public string startToken`
- L89 _public field_ `public string endToken`
- L90 _public field_ `public int level`
- L91 _public field_ `public bool inCollatedTable`
- L92 _public field_ `public bool inFullTable`

#### class `PerfSummaries.SummaryTableInfo`  
`class SummaryTableInfo`  
_internal*; L95-225_
- L97-162 _public ctor_ `public SummaryTableInfo(XElement tableElement, Dictionary<string,List<string>> substitutionsDict, string[] appendList, string[] rowSortAppendList, XmlVariableMappings variableMappings )`
- L164-179 _private method_ `private void ApplySubstitutionsToList(List<string> list, Dictionary<string, List<string>> substitutionsDict)`
- L181-197 _private method_ `private string ApplySubstitution(string str, Dictionary<string, List<string>> substitutionsDict)`
- L200-204 _public ctor_ `public SummaryTableInfo(string filterListStr, string rowSortStr)`
- L206-208 _public ctor_ `public SummaryTableInfo()`
- L210 _public field_ `public List<string> rowSortList = new List<string>()`
- L211 _public field_ `public List<string> columnFilterList = new List<string>()`
- L212 _public field_ `public List<SummarySectionBoundaryInfo> sectionBoundaries = new List<SummarySectionBoundaryInfo>()`
- L213 _public field_ `public bool bReverseSortRows`
- L214 _public field_ `public bool bScrollableFormatting`
- L215 _public field_ `public TableColorizeMode tableColorizeMode = TableColorizeMode.Budget`
- L216 _public field_ `public DateCollationVisibility dateCollationVisibility = DateCollationVisibility.Newest`
- L217 _public field_ `public StringCollationVisibility stringCollationVisibility = StringCollationVisibility.Auto`
- L218 _public field_ `public CollateAverageMethod collateAverageMethod = CollateAverageMethod.Mean`
- L219 _public field_ `public TableColumnSortMode columnSortMode = TableColumnSortMode.Default`
- L220 _public field_ `public SummaryTableStyle summaryTableStyle = new SummaryTableStyle()`
- L222 _public field_ `public float statThreshold`
- L223 _public field_ `public string hideStatPrefix = null`
- L224 _public field_ `public string weightByColumn = null`

#### class `PerfSummaries.SummaryTableColumnFormatInfoCollection`  
`class SummaryTableColumnFormatInfoCollection`  
_internal*; L228-274_
- L230-236 _public ctor_ `public SummaryTableColumnFormatInfoCollection(XElement element)`
- L238-265 _public method_ `public SummaryTableColumnFormatInfo GetFormatInfo(string columnName)`
- L267-270 _public property_ `public static SummaryTableColumnFormatInfo DefaultColumnInfo { get; }`
- L272 _private* field_ `List<SummaryTableColumnFormatInfo> columnFormatInfoList = new List<SummaryTableColumnFormatInfo>()`
- L273 _private* field_ `static SummaryTableColumnFormatInfo defaultColumnInfo = new SummaryTableColumnFormatInfo()`

#### enum `PerfSummaries.TableColorizeMode`  
`enum TableColorizeMode`  
_internal*; L276-281_
- L278 _public* enumerator_ `Off`
- L279 _public* enumerator_ `Budget`
- L280 _public* enumerator_ `Auto`

#### enum `PerfSummaries.TableColumnSortMode`  
`enum TableColumnSortMode`  
_internal*; L283-290_
- L285 _public* enumerator_ `Default`
- L286 _public* enumerator_ `WildcardSortByAvg`
- L287 _public* enumerator_ `WildcardSortByMax`
- L288 _public* enumerator_ `SortByAvg`
- L289 _public* enumerator_ `SortByMax`

#### enum `PerfSummaries.AutoColorizeMode`  
`enum AutoColorizeMode`  
_internal*; L292-297_
- L294 _public* enumerator_ `Off`
- L295 _public* enumerator_ `HighIsBad`
- L296 _public* enumerator_ `LowIsBad`

#### enum `PerfSummaries.ColumnAggregateType`  
`enum ColumnAggregateType`  
_internal*; L299-305_
- L301 _public* enumerator_ `None`
- L302 _public* enumerator_ `Avg`
- L303 _public* enumerator_ `Min`
- L304 _public* enumerator_ `Max`

#### enum `PerfSummaries.DiffRowFrequency`  
`enum DiffRowFrequency`  
_internal*; L307-313_
- L309 _public* enumerator_ `None`
- L310 _public* enumerator_ `Alternating`
- L311 _public* enumerator_ `AfterEachPair`
- L312 _public* enumerator_ `All`

#### enum `PerfSummaries.DateCollationVisibility`  
`enum DateCollationVisibility`  
_internal*; L315-320_
- L317 _public* enumerator_ `Hide`
- L318 _public* enumerator_ `Newest`
- L319 _public* enumerator_ `Oldest`

#### enum `PerfSummaries.StringCollationVisibility`  
`enum StringCollationVisibility`  
_internal*; L322-327_
- L324 _public* enumerator_ `Show`
- L325 _public* enumerator_ `Hide`
- L326 _public* enumerator_ `Auto`

#### enum `PerfSummaries.CollateAverageMethod`  
`enum CollateAverageMethod`  
_internal*; L329-333_
- L331 _public* enumerator_ `Mean`
- L332 _public* enumerator_ `Median`

#### class `PerfSummaries.SummaryTableColumnFormatInfo`  
`class SummaryTableColumnFormatInfo`  
_internal*; L335-421_
- L337-342 _public ctor_ `public SummaryTableColumnFormatInfo()`
- L343-400 _public ctor_ `public SummaryTableColumnFormatInfo(XElement element)`
- L402 _public method_ `public bool IsDate()`
- L404 _public field_ `public AutoColorizeMode autoColorizeMode = AutoColorizeMode.HighIsBad`
- L405 _public field_ `public string name`
- L406 _public field_ `public bool noWrap = false`
- L407 _public field_ `public string numericFormat`
- L408 _public field_ `public int maxStringLength`
- L409 _public field_ `public int maxStringLengthCollated`
- L411 _public field_ `public bool includeValueWithBucketName = true`
- L413 _public field_ `public List<string> bucketNames = new List<string>()`
- L415 _public field_ `public List<float> bucketThresholds = new List<float>()`
- L417 _public field_ `public ColourThresholdList colourThresholdList = null`
- L419 _public field_ `public string dateFormat = null`
- L420 _public field_ `public TimeZoneInfo dateTimeZone = null`

#### class `PerfSummaries.SummaryTableColumn`  
`class SummaryTableColumn`  
_internal*; L423-1247_
- L425 _public field_ `public string name`
- L426 _public field_ `public bool isNumeric = false`
- L427 _public field_ `public string displayName`
- L428 _public field_ `public bool isRowWeightColumn = false`
- L429 _public field_ `public DiffRowFrequency diffRowFrequency = DiffRowFrequency.None`
- L430 _public field_ `public bool bShowOnlyDiffRows = false`
- L431 _public field_ `public bool isCountColumn = false`
- L432 _public field_ `public bool isSortByColumn = false`
- L434 _public field_ `public string tooltip = null`
- L436 _public field_ `public Colour columnColourModifier = null`
- L437 _public field_ `public ColumnAggregateType aggregateType = ColumnAggregateType.None`
- L438 _public field_ `public SummaryTableColumn aggregateBaseColumn = null`
- L440 _private* field_ `List<double> doubleValues = new List<double>()`
- L441 _private* field_ `List<string> stringValues = new List<string>()`
- L442 _private* field_ `List<string> toolTips = new List<string>()`
- L444 _private* field_ `Dictionary<int, Colour> colourModifiers = ...`
- L444 _private* field_ `Dictionary< colourModifiers = new Dictionary<int, Colour>()`
- L445 _public field_ `public SummaryTableElement.Type elementType`
- L446 _public field_ `public SummaryTableColumnFormatInfo formatInfo = null`
- L448 _private* field_ `List<ColourThresholdList> colourThresholds = new List<ColourThresholdList>()`
- L449 _private* field_ `ColourThresholdList colourThresholdOverride = null`
- L450 _public field_ `public bool isVisible = true`
- L452-484 _public ctor_ `public SummaryTableColumn( string inName, bool inIsNumeric, string inDisplayName, bool inIsRowWeightColumn, SummaryTableElement.Type inElementType, SummaryTableColumnFormatInfo inFormatInfo = null, string inTooltip = null, Colour inColumnColourModifier = null, ColumnAggregateType inAggregateType = ColumnAggregateType.None, SummaryTableColumn inAggregateBaseColumn = null, bool bInIsCountColumn = false, bool bInIsSortByColumn = false, bool bInIsVisible = true )`
- L486-499 _public method_ `public static string getAggregateTypePrefix(ColumnAggregateType aggregateType)`
- L501-504 _public method_ `public string getKey(bool bIncludeTypeQualifier = true)`
- L507-520 _public method_ `public string GetJsData()`
- L522-532 _public method_ `public SummaryTableColumn Clone()`
- L535-546 _public method_ `public string GetStatCategory()`
- L548-551 _public method_ `public bool IsDateFormat()`
- L553-556 _private method_ `private double FilterInvalidValue(double value)`
- L558-579 _public method_ `public double GetMaxValue()`
- L581-602 _public method_ `public double GetMinValue()`
- L604-625 _public method_ `public double GetAvgValue()`
- L628-729 _public method_ `public void AddDiffRows(bool bIsFirstColumn, DiffRowFrequency inDiffRowFrequency, bool bShowOnlyDiffRows)`
- L731-734 _private* method_ `bool IsDiffRow(int rowIndex)`
- L737-757 _public method_ `public double GetDiffScore()`
- L760-775 _public method_ `public double GetMaxAbsDiff()`
- L777-809 _public method_ `public string GetDisplayName(string hideStatPrefix=null, bool bAddStatCategorySeparatorSpaces = true, bool bGreyOutStatCategories = false)`
- L811-822 _public method_ `public void ReserveRows(int count)`
- L824-841 _public method_ `public void SetValue(int index, double value)`
- L843-855 _private* method_ `void convertToStrings()`
- L857-868 _public method_ `public void SetColourThresholds(int index, ColourThresholdList value)`
- L870-877 _public method_ `public ColourThresholdList GetColourThresholds(int index)`
- L879-926 _public method_ `public string GetBackgroundColor(int index)`
- L928-977 _public method_ `public string GetTextColor(int index)`
- L980-1050 _public method_ `public void ComputeColorThresholds(TableColorizeMode tableColorizeMode)`
- L1052-1069 _public method_ `public List<string> GetHeaderAttributes()`
- L1071-1074 _public method_ `public int GetCount()`
- L1075-1082 _public method_ `public double GetValue(int index)`
- L1084-1103 _public method_ `public bool AreAllValuesOverThreshold(double threshold)`
- L1105-1122 _public method_ `public void SetStringValue(int index, string value)`
- L1123-1214 _public method_ `public string GetStringValue(int index, bool roundNumericValues = false, string forceNumericFormat = null)`
- L1215-1226 _public method_ `public void SetToolTipValue(int index, string value)`
- L1227-1234 _public method_ `public string GetToolTipValue(int index)`
- L1236-1240 _public method_ `public void DebugMarkRowInvalid(int index, string reason)`
- L1242-1246 _public method_ `public void DebugMarkAsFiltered(string filterName, string reason)`

#### class `PerfSummaries.SummaryTable`  
`class SummaryTable`  
_internal*; L1251-3105_
- L1383-1385 _public ctor_ `public SummaryTable()`
- L1387-1393 _public method_ `public void SetColumnFormatInfo(SummaryTableColumnFormatInfoCollection collection)`
- L1395-1405 _private* method_ `string MakeRowSortKey(List<SummaryTableColumn> sortByColumnList, int rowIndex)`
- L1407-1415 _private method_ `private SummaryTableColumn CollateColumn(SummaryTableColumn srcColumn, ColumnAggregateType aggregateType, List<int> collatedRowSourceRowCounts, SummaryTableColumn aggregateBaseColumn = null, bool bShowMergedStringValues = false, CollateAverageMethod collateAverageMethod = CollateAverageMethod.Mean)`
- L1417-1567 _private method_ `private SummaryTableColumn CollateColumn(SummaryTableColumn srcColumn, ColumnAggregateType aggregateType, List<int> collatedRowSourceRowCounts, SummaryTableColumn aggregateBaseColumn, bool bShowMergedStringValues, out int validMultiRowCollationsCount, CollateAverageMethod collateAverageMethod = CollateAverageMethod.Mean)`
- L1569-1707 _public method_ `public SummaryTable CollateSortedTable(List<string> collateByList, bool addMinMaxColumns, StringCollationVisibility stringCollationVisibility, DateCollationVisibility dateCollationVisibility, CollateAverageMethod collateAverageMethod)`
- L1709-1767 _public method_ `public Dictionary<string, dynamic> ToFlatJsonDict()`
- L1770-1792 _private method_ `private SummaryTableColumn GetAggregateColumn(SummaryTableColumn inColumn, ColumnAggregateType aggregateType)`
- L1794-1797 _private* method_ `SummaryTableColumnLookup GetColumnLookup()`
- L1799-1821 _public method_ `public static string GetElementTypeStatPrefix(SummaryTableElement.Type type)`
- L1823-1857 _public method_ `public static SummaryTableElement.Type GetQualfiedStatType(string fullNameWithQualifier)`
- L1859-1902 _public method_ `public static SummaryTableElement.Type GetQualfiedStatType(string fullNameWithQualifier, out string statNameOut)`
- L1904-2029 _public method_ `public SummaryTable SortAndFilter(List<string> columnFilterList, List<string> rowSortList, bool bReverseSort, string weightByColumnName, IEnumerable<ISummaryTableColumnFilter> additionalFilters, bool bSortTrailingDigitsAsNumeric, TableColumnSortMode tableColumnSortMode)`
- L2031-2064 _public method_ `public void AddDiffRows(bool bSortColumnsByDiff, double columnDiffDisplayThreshold, bool bInShowOnlyDiffRows, bool bDiffRowsAlternating)`
- L2067-2088 _public method_ `public void ApplyDisplayNameMapping(Dictionary<string, StatDisplayInfo> statDisplayNameMapping)`
- L2090-2094 _public method_ `public static string GetBaseStatPrefix(string inName)`
- L2096-2099 _public method_ `public static string GetBaseStatName(string inName)`
- L2101-2117 _public method_ `public static string GetBaseStatNameWithPrefixAndSuffix(string inName, out string prefix, out string suffix)`
- L2119-2142 _public method_ `public void WriteToCSV(string csvFilename)`
- L2148-2165 _public method_ `public IEnumerable<IEnumerable<KeyValuePair<SummaryTableColumn, dynamic>>> EnumerateTableDataByRow()` — An enumerable representation of the SummaryTable, by rows.
- L2169-2226 _private method_ `private void SortColumnsByDiffRows()`
- L2230-2250 _private method_ `private void FilterColumnsByDiffThreshold(double threshold)`
- L2253-2864 _public method_ `public void WriteToHTML( string htmlFilename, string VersionString, bool bSpreadsheetFriendlyStrings, List<SummarySectionBoundaryInfo> sectionBoundaries, bool bScrollableTable, TableColorizeMode tableColorizeMode, bool bAddMinMaxColumns, string hideStatPrefix, int maxColumnStringLength, string weightByColumnName, CollateAverageMethod collateAverageMethod, string title, bool bTranspose, SummaryTableStyle summaryTableStyle, bool bEmitJsData, bool showFilteredColumnDebug = false )`
- L2866-2943 _public method_ `public SummaryTable SortRows(List<string> rowSortList, bool reverseSort, bool sortTrailingDigitsAsNumeric = false)`
- L2946-2991 _private* method_ `string GetRowColumnJsData()`
- L2993-3000 _private* method_ `void InitColumnLookup()`
- L3002-3048 _public method_ `public void AddRowData(SummaryTableRowData metadata, bool bIncludeCsvStatAverages, bool bIncludeCsvStatMin, bool bIncludeCsvStatMax, bool bIncludeHiddenStats)`
- L3050-3053 _public property_ `public int Count { get; }`
- L3055-3058 _public method_ `public SummaryTableColumn GetColumnByName(string name)`
- L3060-3063 _public method_ `public bool IsRowVisible(int rowIndex)`
- L3065-3075 _public method_ `public static bool IsRowVisible(DiffRowFrequency diffRowFrequency, bool bShowOnlyDiffRows, int rowIndex)`
- L3077-3093 _public method_ `public static bool IsDiffRow(DiffRowFrequency diffRowFrequency, int rowIndex)`
- L3096 _private* field_ `SummaryTableColumnLookup columnLookup = new SummaryTableColumnLookup()`
- L3097 _private* field_ `List<SummaryTableColumn> columns = new List<SummaryTableColumn>()`
- L3098 _private* field_ `List<double> rowWeightings = null`
- L3099 _private* field_ `int rowCount = 0`
- L3100 _private* field_ `int firstStatColumnIndex = 0`
- L3101 _private* field_ `bool isCollated = false`
- L3102 _private* field_ `bool hasMinMaxColumns = false`
- L3103 _private* field_ `DiffRowFrequency diffRowFrequency = DiffRowFrequency.None`
- L3104 _private* field_ `bool bShowOnlyDiffRows = false`

#### class `PerfSummaries.SummaryTable.SummaryTableColumnLookup`  
`class SummaryTableColumnLookup`  
_private*; L1253-1381_
- L1255-1258 _public ctor_ `public SummaryTableColumnLookup()`
- L1260-1266 _public method_ `public void Clear()`
- L1268-1273 _public method_ `public List<string> GetSortedKeyList(SummaryTableElement.Type type = SummaryTableElement.Type.ANY)`
- L1275-1301 _public method_ `public void Add(string key, SummaryTableColumn column)`
- L1303-1306 _public method_ `public bool ContainsKey(string key, SummaryTableElement.Type type = SummaryTableElement.Type.ANY)`
- L1308-1339 _public method_ `public void Remove(string key, SummaryTableElement.Type type = SummaryTableElement.Type.ANY)`
- L1341-1354 _public method_ `public SummaryTableColumn Get(string key, SummaryTableElement.Type type = SummaryTableElement.Type.ANY)`
- L1357-1378 _public method_ `public static int GetElementTypePriority(SummaryTableElement.Type type)`
- L1380 _private* field_ `Dictionary<string, SummaryTableColumn>[] columnLookupByType = ...`
- L1380 _private* field_ `Dictionary< columnLookupByType = new Dictionary<string, SummaryTableColumn>[(int)SummaryTableElement.Type.COUNT + 1]`

#### class `PerfSummaries.HtmlTable`  
`class HtmlTable`  
_internal*; L3107-3275_
- L3208-3214 _public ctor_ `public HtmlTable(string inAttributes="", int inNumHeaderRows=1, int reserveColumnCount=0)`
- L3216-3230 _public method_ `public HtmlTable Transpose()`
- L3232-3243 _public method_ `public void WriteToHtml(System.IO.StreamWriter htmlFile)`
- L3245-3258 _public method_ `public void Set(int RowIndex, int ColIndex, Cell cell)`
- L3260-3265 _public method_ `public Row CreateRow(string attributes="")`
- L3266-3269 _public method_ `public void AddRow(Row row)`
- L3271 _public field_ `public List<Row> rows`
- L3272 _public field_ `public string attributes`
- L3273 _public field_ `public int numHeaderRows = 0`
- L3274 _private* field_ `int reserveColumnCount = 0`

#### class `PerfSummaries.HtmlTable.Row`  
`public class Row`  
_public; L3109-3174_
- L3111-3123 _public ctor_ `public Row(string inAttributes="", int reserveColumnCount=0, string inId=null)`
- L3125-3128 _public method_ `public void AddCell(string contents="", string attributes="", string cellId = null)`
- L3130-3136 _public method_ `public void AddCell(string contents, List<string> attributes, Dictionary<string, string> styleAttributes, string cellId = null)`
- L3139-3156 _public method_ `public void WriteToHtml(System.IO.StreamWriter htmlFile, bool bIsHeaderRow )`
- L3158-3169 _public method_ `public void Set(int ColIndex, Cell cell)`
- L3171 _public field_ `public string attributes`
- L3172 _public field_ `public string id`
- L3173 _public field_ `public List<Cell> cells`

#### class `PerfSummaries.HtmlTable.Cell`  
`public class Cell`  
_public; L3176-3206_
- L3178-3180 _public ctor_ `public Cell()`
- L3181-3186 _public ctor_ `public Cell(Cell srcCell)`
- L3188-3193 _public ctor_ `public Cell(string inContents, string inAttributes, bool bInIsHeader=false, string inId = null)`
- L3195-3201 _public method_ `public void WriteToHtml(System.IO.StreamWriter htmlFile, bool bIsHeaderRow)`
- L3203 _public field_ `public string contents`
- L3204 _public field_ `public string attributes`
- L3205 _public field_ `public string id`

### `Source/Programs/CSVTools/PerfReportTool/SummaryTableData.cs` (PerfreportTool)


#### class `PerfSummaries.SummaryTableDataJsonWriteHelper`  
`class SummaryTableDataJsonWriteHelper`  
_internal*; L16-94_
- L18-31 _public ctor_ `public SummaryTableDataJsonWriteHelper(string InJsonFilenameOrDirectory, bool bInSeparateFiles, bool bInCsvMetadataOnly, bool bInWriteAllElementData, bool bInWriteIndented=false)`
- L32-42 _public method_ `public void AddRowData(SummaryTableRowData rowData)`
- L44-61 _public method_ `public void WriteToJson(bool bSerializeToStream)`
- L63-77 _public method_ `public static void WriteJsonFile(bool bSerializeToStream, string filename, Dictionary<string, dynamic> dictToSerialize, bool bWriteIndented)`
- L80-86 _private method_ `private static async Task WriteJsonFileAsyncPrivate(JsonSerializerOptions options, string Filename, Dictionary<string, dynamic> DictToSerialize)`
- L88 _private* field_ `Dictionary<string, dynamic> Dict = ...`
- L88 _private* field_ `Dictionary< Dict = new Dictionary<string, dynamic>()`
- L89 _private* field_ `string JsonFilename = null`
- L90 _private* field_ `string JsonDirectory = null`
- L91 _private* field_ `bool bCsvMetadataOnly`
- L92 _private* field_ `bool bWriteAllElementData`
- L93 _private* field_ `bool bWriteIndented`

#### class `PerfSummaries.SummaryTableElement`  
`class SummaryTableElement`  
_internal*; L98-349_
- L101 _public field_ `public static int CacheVersion = 1`
- L122-124 _private ctor_ `private SummaryTableElement()`
- L126-140 _public ctor_ `public SummaryTableElement(Type inType, string inName, double inValue, ColourThresholdList inColorThresholdList, string inToolTip, uint inFlags = 0)`
- L141-155 _public ctor_ `public SummaryTableElement(Type inType, string inName, string inValue, ColourThresholdList inColorThresholdList, string inToolTip, uint inFlags = 0)`
- L157-187 _public method_ `public static SummaryTableElement ReadFromCache(BinaryReader reader)`
- L191-215 _public method_ `public void WriteToCache(BinaryWriter writer)`
- L217-220 _public method_ `public SummaryTableElement Clone()`
- L222-232 _public method_ `public void SetFlag(Flags flag, bool value)`
- L233-236 _public method_ `public bool GetFlag(Flags flag)`
- L238-279 _public ctor_ `public SummaryTableElement(Type typeIn, string elementName, Dictionary<string, dynamic> jsonDict)`
- L281-328 _public method_ `public Dictionary<string, dynamic> ToJsonDict(bool bWriteType)`
- L329-339 _public property_ `public dynamic DynamicValue { get; }`
- L341 _public field_ `public Type type`
- L342 _public field_ `public string name`
- L343 _public field_ `public string value`
- L344 _public field_ `public string tooltip`
- L345 _public field_ `public ColourThresholdList colorThresholdList`
- L346 _public field_ `public double numericValue`
- L347 _public field_ `public bool isNumeric`
- L348 _public field_ `public uint flags`

#### enum `PerfSummaries.SummaryTableElement.Type`  
`public enum Type`  
_public; L104-115_
- L106 _public* enumerator_ `CsvStatAverage`
- L107 _public* enumerator_ `CsvMetadata`
- L108 _public* enumerator_ `SummaryTableMetric`
- L109 _public* enumerator_ `ToolMetadata`
- L110 _public* enumerator_ `ExternalMetadata`
- L111 _public* enumerator_ `CsvStatMin`
- L112 _public* enumerator_ `CsvStatMax`
- L113 _public* enumerator_ `COUNT`
- L114 _public* enumerator_ `ANY=COUNT`

#### enum `PerfSummaries.SummaryTableElement.Flags`  
`public enum Flags`  
_public; L117-120_
- L119 _public* enumerator_ `Hidden = 0x01`

#### class `PerfSummaries.SummaryTableRowData`  
`class SummaryTableRowData`  
_internal*; L351-647_
- L353-355 _public ctor_ `public SummaryTableRowData()`
- L358 _private* field_ `static int CacheVersion = 6`
- L360-364 _public method_ `public static SummaryTableRowData TryReadFromCache(string summaryTableCacheDir, string csvId)`
- L366-386 _public method_ `public CsvMetadata ReadCsvMetadata()`
- L388-439 _public method_ `public static SummaryTableRowData TryReadFromCacheFile(string filename, bool bReadJustInitialMetadata = false)`
- L443-454 _private* method_ `List<KeyValuePair<string, SummaryTableElement>> GetCacheableEntries()`
- L456-485 _public method_ `public bool WriteToCache(string summaryTableCacheDir, string csvId)`
- L487-494 _public method_ `public int GetFrameCount()`
- L496-499 _public method_ `public bool Contains(string key)`
- L500-507 _public method_ `public SummaryTableElement Get(string key)`
- L509-516 _public method_ `public void RemoveSafe(string name)`
- L518-531 _public method_ `public void Add(SummaryTableElement.Type type, string name, double value, ColourThresholdList colorThresholdList = null, string tooltip = "", uint flags = 0)`
- L533-569 _public method_ `public void Add(SummaryTableElement.Type type, string name, string value, ColourThresholdList colorThresholdList = null, string tooltip = "", uint flags = 0)`
- L570-573 _public method_ `public void Add(SummaryTableElement element)`
- L576-581 _public method_ `public void AddString(SummaryTableElement.Type type, string name, string value, ColourThresholdList colorThresholdList = null, string tooltip = "")`
- L583-597 _public ctor_ `public SummaryTableRowData(Dictionary<string, dynamic> jsonDict)`
- L599-644 _public method_ `public Dictionary<string, dynamic> ToJsonDict(bool bCsvMetadataOnly, bool bWriteAllElementData)`
- L646 _public field_ `public Dictionary<string, SummaryTableElement> dict = ...`
- L646 _public field_ `public Dictionary< dict = new Dictionary<string, SummaryTableElement>()`

### `Source/Programs/CSVTools/PerfReportTool/SummaryTypes.cs` (PerfreportTool)


#### class `PerfSummaries.Colour`  
`class Colour`  
_internal*; L11-173_
- L13-24 _public ctor_ `public Colour(string str)`
- L25-36 _public ctor_ `public Colour(uint hex, float alphaIn = 1.0f)`
- L37 _public ctor_ `public Colour(Colour colourIn)`
- L38 _public ctor_ `public Colour(float rIn, float gIn, float bIn, float aIn = 1.0f)`
- L40-43 _public method_ `public static float Lerp(float A, float B, float T)`
- L45-52 _public method_ `public static Colour Lerp(Colour Colour0, Colour Colour1, float t)`
- L54-71 _public method_ `public Colour LinearRGBToHSV()`
- L74-106 _public method_ `public Colour HSVToLinearRGB()`
- L108-144 _public method_ `public static Colour LerpUsingHSV(Colour From, Colour To, float T)`
- L146-149 _public operator_ `public static Colour operator *(Colour a, Colour b)`
- L151-154 _public method_ `public string ToHTMLString()`
- L156-162 _public method_ `public override string ToString()`
- L164 _public field_ `public static Colour White = new Colour(1.0f, 1.0f, 1.0f, 1.0f)`
- L165 _public field_ `public static Colour Black = new Colour(0, 0, 0, 1.0f)`
- L166 _public field_ `public static Colour Red = new Colour(1.0f, 0.4f, 0.4f)`
- L167 _public field_ `public static Colour Orange = new Colour(1.0f, 0.7f, 0.4f, 1.0f)`
- L168 _public field_ `public static Colour Yellow = new Colour(1.0f, 1.0f, 0.5f)`
- L169 _public field_ `public static Colour Green = new Colour(0.53f, 0.83f, 0.53f)`
- L171 _public field_ `public float r, g, b`
- L171 _public field_ `public float g`
- L171 _public field_ `public float b`
- L172 _public field_ `public float alpha`

#### class `PerfSummaries.ThresholdInfo`  
`class ThresholdInfo`  
_internal*; L176-185_
- L178-182 _public ctor_ `public ThresholdInfo(double inValue, Colour inColourOverride = null)`
- L183 _public field_ `public double value`
- L184 _public field_ `public Colour colour`

#### class `PerfSummaries.ColourThresholdList`  
`class ColourThresholdList`  
_internal*; L187-454_
- L189-190 _public ctor_ `public ColourThresholdList()`
- L192-199 _public ctor_ `public ColourThresholdList(double redValue, double orangeValue, double yellowValue, double greenValue, bool lerpColours = true)`
- L201-205 _public ctor_ `public ColourThresholdList(IEnumerable<ThresholdInfo> thresholds, bool lerpColours)`
- L207-231 _public ctor_ `public ColourThresholdList(Dictionary<string, dynamic> JsonDict)`
- L233-261 _public method_ `public Dictionary<string, dynamic> ToJsonDict()`
- L263-306 _public method_ `public static string GetThresholdColour(double value, List<ThresholdInfo> thresholds, bool lerpColours = true)`
- L308-333 _public method_ `public static string GetThresholdColour(double value, double redValue, double orangeValue, double yellowValue, double greenValue, Colour redOverride = null, Colour orangeOverride = null, Colour yellowOverride = null, Colour greenOverride = null, bool lerpColours = true)`
- L335-338 _public method_ `public void Add(ThresholdInfo info)`
- L339-342 _public property_ `public int Count { get; }`
- L344-354 _public method_ `public string GetColourForValue(string value)`
- L356-367 _public method_ `public string GetColourForValue(double value)`
- L369-376 _public method_ `public static string GetSafeColourForValue(ColourThresholdList list, string value)`
- L377-384 _public method_ `public static string GetSafeColourForValue(ColourThresholdList list, double value)`
- L386-428 _public method_ `public static ColourThresholdList ReadColourThresholdListXML(XElement colourThresholdEl, XmlVariableMappings vars)`
- L430-449 _public method_ `public static double[] ReadColourThresholdsXML(XElement colourThresholdEl, XmlVariableMappings vars )`
- L451 _public field_ `public List<ThresholdInfo> Thresholds = new List<ThresholdInfo>()`
- L453 _public field_ `public bool LerpColours = true`

### `Source/Programs/CSVTools/PerfReportTool/Telemetry.cs` (PerfreportTool)


#### class `PerfReportTool.Telemetry`  
`internal static class Telemetry`  
_internal; L22-458_
- desc: Telemetry class used to emit telemetry events for PerfReportTool.
- L24 _private field_ `private static object _lock = new object()`
- L25 _private const_ `private const string DefaultAppId = "Horde"`
- L26 _private const_ `private const int DefaultAppVersion = 1`
- L27 _private const_ `private const string DefaultAppEnvironment = "Dev"`
- L28 _private const_ `private const string EventName = "State.Performance"`
- L29 _private const_ `private const string DefaultSummaryTableName = "default"`
- L30 _private const_ `private const int CurrentSchemaVersion = 2`
- L31 _private const_ `private const int DefaultTimeoutSeconds = 15`
- L32 _private field_ `private static ServiceProvider _serviceProvider = null`
- L33 _private field_ `private static IHordeClient _hordeClient = null`
- L34 _private field_ `private static HordeHttpClient _hordeHttpClient = null`
- L35 _private field_ `private readonly static List<Task<bool>> _queuedRequests = new List<Task<bool>>(16)`
- L36 _private field_ `private readonly static string _sessionId = Guid.NewGuid().ToString("N")`
- L41-67 _internal property_ `internal static IHordeClient HordeClient { get; }` — Gets the HordeClient used to create Horde Http Clients.
- L72-87 _internal property_ `internal static HordeHttpClient HordeHttpClient { get; }` — Gets the Horde Http Client used to emit events.
- L92-141 _internal method_ `internal static void Flush()` — Flushes all telemetry events that have been queued.
- L146-162 _internal method_ `internal static void Dispose()` — Releases underlying singletons for the Telemetry helper.
- L174-195 _internal method_ `internal async static Task<bool> PostSummaryTableMetricEventAsync(SummaryTableRowData rowData, string sessionLabel = null, string testIdentity = null, IReadOnlyDictionary<string, string> payloadMetadata = null)` — Posts a rowData data's SummaryTableMetric to the Horde event stream, asynchronously.
- L205-219 _internal method_ `internal static IReadOnlyList<Task<bool>> EnqueuePostSummaryTableMetricEvent(SummaryTableRowData rowData, string sessionLabel = null, string testIdentity = null, IReadOnlyDictionary<string, string> payloadMetadata = null)` — Enqueues a task to posts a rowData data's SummaryTableMetric to the Horde event stream.
- L229-250 _internal method_ `internal static bool PostSummaryTableMetricEvent(SummaryTableRowData rowData, string sessionLabel = null, string testIdentity = null, IReadOnlyDictionary<string, string> payloadMetadata = null)` — Posts a rowData data's SummaryTableMetric to the Horde event stream.
- L252-307 _private method_ `private static Hashtable CreatePayload(SummaryTableRowData rowData, string sessionLabel = null, string testIdentity = null, IReadOnlyDictionary<string, string> payloadMetadata = null)`
- L309-330 _private method_ `private static void CoalesceDictionary(dynamic summaryTableEntry, Hashtable telemetryPayload)`
- L335-346 _private method_ `private static void ApplyPayloadMetadata(Hashtable telemetryPayload, IReadOnlyDictionary<string, string> payloadMetadata)` — Folds optional metadata into a telemetry payload, overriding existing keys.
- L362-410 _internal method_ `internal static IReadOnlyList<Task<bool>> EnqueuePostSummaryTableMetricEvent(string summaryTableName, SummaryTable tableData, bool isCollated, string sessionLabel = null, string testIdentity = null, IReadOnlyDictionary<string, string> payloadMetadata = null)` — Enqueues a task to posts an entire summary table to the Horde event stream.
- L416-455 _private method_ `private static async Task<bool> EmitPayloadsAsync(Hashtable[] telemetryPayloads)`
