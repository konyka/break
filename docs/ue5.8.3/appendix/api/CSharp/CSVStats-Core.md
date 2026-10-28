# CSharp / CSVStats-Core

- project root: `Source/Programs/CSVTools/CsvStats`
- files: 4; symbols: 245
- symbol kinds: class=16, ctor=23, enum=9, enumerator=35, field=47, method=112, property=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/CsvStats/CommandLineTool.cs` (CSVStats-Core)


#### class `CSVStats.CommandLine`  
`public class CommandLine`  
_public; L13-223_
- L15 _protected field_ `protected string commandLine = ""`
- L17 _protected field_ `protected Dictionary<string, string> CommandLineArgs`
- L17 _protected field_ `protected Dictionary< CommandLineArgs`
- L19-22 _public method_ `public string GetCommandLine()`
- L24-39 _public method_ `public static bool IsParamName(string str)`
- L41-82 _private method_ `private List<string> GetArgList(string inCommandLine)`
- L84-155 _public ctor_ `public CommandLine(string[] args)`
- L157-162 _public method_ `public int GetIntArg(string key, int defaultValue)`
- L164-169 _public method_ `public float GetFloatArg(string key, float defaultValue)`
- L171-186 _public method_ `public bool GetBoolArg(string key, bool defaultValue)`
- L188-195 _public method_ `public bool? GetOptionalBoolArg(string key)`
- L197-206 _public method_ `public string GetArg(string key, string defaultValue)`
- L208-221 _public method_ `public string GetArg(string key, bool mandatory = false)`

#### class `CSVStats.CommandLineTool`  
`public class CommandLineTool`  
_public; L225-400_
- L234 _private* field_ `static int initCounter = 0`
- L236-240 _public ctor_ `public CommandLineTool()`
- L243-246 _public method_ `public static CommandLine GetGlobalCommandLine()`
- L247-250 _public method_ `public CommandLine GetCommandLine()`
- L254 _protected field_ `protected CommandLine commandLine`
- L255 _private field_ `private static CommandLine globalCommandLine`
- L256 _private field_ `private bool bMainInstance = true`
- L258 _private field_ `private readonly static bool bIsMac = File.Exists("/System/Library/CoreServices/SystemVersion.plist")`
- L260-277 _protected property_ `protected static HostPlatform Host { get; }`
- L279-290 _protected method_ `protected static string MakeShortFilename(string filename)`
- L291-294 _protected method_ `protected int GetIntArg(string key, int defaultValue)`
- L296-299 _protected method_ `protected float GetFloatArg(string key, float defaultValue)`
- L301-304 _protected method_ `protected bool GetBoolArg(string key, bool defaultValue=false)`
- L306-316 _protected method_ `protected T GetEnumArg<T>(string key, T defaultValue) where T : System.Enum`
- L318-321 _protected method_ `protected bool? GetOptionalBoolArg(string key)`
- L324-327 _protected method_ `protected string GetArg(string key, string defaultValue)`
- L329-332 _protected method_ `protected string GetArg(string key, bool mandatory = false)`
- L334-346 _protected method_ `protected List<string> GetListArg(string key, char separator=';', bool convertToLowercase=false, bool mandatory=false)`
- L348-352 _protected method_ `protected void WriteLine(String message, params object[] args)`
- L355-390 _protected method_ `protected string[] ReadLinesFromFile(string filename)`
- L392-399 _protected method_ `protected void ReadCommandLine(string[] args)`

#### enum `CSVStats.CommandLineTool.HostPlatform`  
`protected enum HostPlatform`  
_protected; L227-232_
- L229 _public* enumerator_ `Windows`
- L230 _public* enumerator_ `Mac`
- L231 _public* enumerator_ `Linux`

#### class `CSVStats.PerfLog`  
`public class PerfLog`  
_public; L403-454_
- L405-414 _public ctor_ `public PerfLog(bool inLoggingEnabled, string inLogPrefix=null)`
- L416-432 _public method_ `public double LogTiming(string description, bool newLine = false)`
- L434-449 _public method_ `public double LogTotalTiming(bool seconds=true)`
- L450 _private* field_ `Stopwatch stopWatch`
- L451 _private* field_ `double previousTime`
- L452 _private* field_ `bool loggingEnabled`
- L453 _private* field_ `string logPrefix = ""`

### `Source/Programs/CSVTools/CsvStats/CsvStats.cs` (CSVStats-Core)


#### enum `CSVStats.CsvBinVersion`  
`public enum CsvBinVersion`  
_public; L18-27_
- L20 _public* enumerator_ `PreRelease = 1`
- L21 _public* enumerator_ `InitialRelease`
- L22 _public* enumerator_ `CompressionSupportAndFlags`
- L23 _public* enumerator_ `EventTimestamps`
- L25 _public* enumerator_ `COUNT`
- L26 _public* enumerator_ `CURRENT = COUNT - 1`

#### enum `CSVStats.CsvBinFlags`  
`enum CsvBinFlags`  
_internal*; L29-32_
- L31 _public* enumerator_ `HasMetadata = 0x00000001`

#### enum `CSVStats.CsvBinCompressionType`  
`public enum CsvBinCompressionType`  
_public; L33-36_
- L35 _public* enumerator_ `MsDeflate`

#### enum `CSVStats.CsvBinCompressionLevel`  
`public enum CsvBinCompressionLevel`  
_public; L38-43_
- L40 _public* enumerator_ `None`
- L41 _public* enumerator_ `Min`
- L42 _public* enumerator_ `Max`

#### class `CSVStats.CsvFileInfo`  
`public class CsvFileInfo`  
_public; L46-52_
- L48 _public field_ `public bool bIsCsvBin`
- L49 _public field_ `public CsvBinVersion BinVersion = CsvBinVersion.COUNT`
- L50 _public field_ `public CsvBinCompressionLevel BinCompressionLevel = CsvBinCompressionLevel.None`
- L51 _public field_ `public int SampleCount = 0`

#### class `CSVStats.CsvEvent`  
`public class CsvEvent`  
_public; L55-79_
- L57-62 _public ctor_ `public CsvEvent(CsvEvent source)`
- L63-68 _public ctor_ `public CsvEvent(string NameIn, int FrameIn, double TimestampIn)`
- L69-72 _public ctor_ `public CsvEvent()`
- L74 _public method_ `public bool HasTimestamp()`
- L76 _public field_ `public string Name`
- L77 _public field_ `public int Frame`
- L78 _public field_ `public double Timestamp = double.MaxValue`

#### class `CSVStats.DerivedStatException`  
`public class DerivedStatException : Exception`  
_public; L81-84_
- inherits: `Exception`
- L83 _public ctor_ `public DerivedStatException(string message) : base(message)`

#### class `CSVStats.DerivedStatMissingSourceException`  
`public class DerivedStatMissingSourceException : DerivedStatException`  
_public; L86-89_
- inherits: `DerivedStatException`
- L88 _public ctor_ `public DerivedStatMissingSourceException(string message) : base(message)`

#### class `CSVStats.CsvMetadata`  
`public class CsvMetadata`  
_public; L92-286_
- L94 _public field_ `public Dictionary<string, string> Values`
- L94 _public field_ `public Dictionary< Values`
- L96-101 _public method_ `public CsvMetadata Clone()`
- L103-111 _public ctor_ `public CsvMetadata(CsvMetadata source)`
- L113-116 _public ctor_ `public CsvMetadata()`
- L118-184 _public ctor_ `public CsvMetadata(string[] csvLine)`
- L186-195 _public method_ `public void WriteToBinaryFile(BinaryWriter fileWriter)`
- L196-206 _public method_ `public void ReadFromBinaryFile(BinaryReader fileReader)`
- L208-235 _public method_ `public void CombineAndValidate(CsvMetadata comparisonMetadata)`
- L237-275 _public method_ `public static bool Matches(CsvMetadata a, CsvMetadata b)`
- L278-285 _public method_ `public string GetValue(string key, string defaultValue)`

#### class `CSVStats.StatSamples`  
`public class StatSamples : IComparable`  
_public; L290-468_
- inherits: `IComparable`
- L292-304 _public ctor_ `public StatSamples(StatSamples source, bool copySamples=true)`
- L305-321 _public ctor_ `public StatSamples(string name, int sampleListLength=0, bool bInIsDerived = false)`
- L323-334 _public method_ `public float GetRatioOfFramesInBudget(float budget)`
- L336-339 _public method_ `public float GetRatioOfFramesOverBudget(float budget)`
- L341-352 _public method_ `public int GetCountOfFramesOverBudget(float budget, bool IgnoreFirstFrame = true, bool IgnoreLastFrame = true)`
- L354-365 _public method_ `public int GetCountOfFramesAtOrOverBudget(float budget, bool IgnoreFirstFrame = true, bool IgnoreLastFrame = true)`
- L368-383 _public method_ `public int GetCountOfFramesInRangeOverBudget(float budget, int startindex, int endindex)`
- L387-398 _public method_ `public int CompareTo(object obj)`
- L401-413 _public method_ `public float ComputeAverage(int minSample=0, int maxSample=-1)`
- L415-427 _public method_ `public void ComputeAverageAndTotal(int minSample = 0, int maxSample = -1)`
- L429-445 _public method_ `public float ComputeMaxValue(int minSample = 0, int maxSample = -1)`
- L446-458 _public method_ `public float ComputeMinValue(int minSample = 0, int maxSample = -1)`
- L460 _public method_ `public int GetNumSamples()`
- L461 _public field_ `public string Name`
- L462 _public field_ `public string LegendName`
- L463 _public field_ `public List<float> samples`
- L464 _public field_ `public float average`
- L465 _public field_ `public double total`
- L466 _public field_ `public Colour colour`
- L467 _public field_ `public bool bIsDerived`

#### class `CSVStats.CsvStats`  
`public class CsvStats`  
_public; L471-2634_
- L473-477 _public ctor_ `public CsvStats()`
- L478-512 _public ctor_ `public CsvStats(CsvStats sourceCsvStats, string[] statNamesToFilter = null)`
- L513-521 _public method_ `public StatSamples GetStat(string name)`
- L523-530 _public method_ `public string GetMetadataValue(string key)`
- L532-540 _public method_ `public Tuple<CsvEvent, CsvEvent> FindEventPair(string patternBegin, string patternEnd, bool bFindLast = false)`
- L542-545 _public method_ `public CsvEvent FindEvent(string pattern, double startTime = 0.0, double endTime = double.MaxValue)`
- L547-557 _private method_ `private CsvEvent FindEventInternal(IEnumerable<CsvEvent> InEvents, string pattern, double startTime = 0.0, double endTime = double.MaxValue)`
- L559-562 _public method_ `public List<CsvEvent> FindEvents(string pattern, double startTime = 0.0, double endTime = double.MaxValue)`
- L564-575 _private method_ `private List<CsvEvent> FindEventsInternal(IEnumerable<CsvEvent> InEvents, string pattern, double startTime = 0.0, double endTime = double.MaxValue)`
- L578-590 _private* method_ `string ReadQuotedString(string str)`
- L591-625 _private* method_ `string ReadBracketString(string str)`
- L628-809 _private* method_ `string ReadNextToken(string expression, ref int index, Dictionary<string, StatSamples> statsOut, int tokenIndex)`
- L811-831 _private* method_ `string PreProcessExpression(string expression, Dictionary<string,StatSamples> statsOut)`
- L833-926 _public method_ `public StatSamples MakeDerivedStatFromExpression(string expression, bool bVerboseErrors = false)`
- L928-936 _public method_ `public StatSamples AddDerivedStatFromExpression(string expression, bool bVerboseErrors = false)`
- L939-988 _public method_ `public static List<string> SplitStringListWithBracketGroups(string listStr, char separator)`
- L990-1003 _public method_ `public StatSamples MakeEventCountStat(string statName, string eventStr)`
- L1005-1016 _public method_ `public List<CsvEvent> GetEventsMatchingString(string eventStr)`
- L1019-1022 _public method_ `public void AddStat(StatSamples stat)`
- L1024-1067 _public method_ `public void CropStats(int minFrame, int maxFrame = Int32.MaxValue)`
- L1069-1111 _private* method_ `static string[] ReadLinesFromFile(string filename)`
- L1113-1141 _private method_ `private static bool WildcardSubstringMatch(string strLower, string[] subSearchStrings)`
- L1143-1156 _public method_ `public static bool DoesSearchStringMatch(string str, string searchString)`
- L1158-1168 _public method_ `public static string GetColorFromString(string input, int minBrightness = 64, int maxBrightness = 200)`
- L1170-1271 _public method_ `public static List<string> WildcardMatchStringList(List<string> stringList, string searchString, bool bCaseSensitive = false, bool bListIsSorted = false)`
- L1273-1288 _public method_ `public HashSet<StatSamples> GetStatsMatchingStringList_Set(string[] statNames)`
- L1289-1292 _public method_ `public List<StatSamples> GetStatsMatchingStringList(string[] statNames)`
- L1294-1303 _public method_ `public HashSet<string> GetStatNamesMatchingStringList_Set(string[] statNames)`
- L1305-1308 _public method_ `public List<string> GetStatNamesMatchingStringList(string[] statNames)`
- L1310-1341 _public method_ `public List<StatSamples> GetStatsMatchingString(string statString)`
- L1343-1346 _private method_ `private static bool GetFlag(uint flags, CsvBinFlags flag)`
- L1348-1358 _private method_ `private static void SetFlag(ref uint flags, CsvBinFlags flag, bool value)`
- L1360-1372 _private method_ `private System.IO.Compression.CompressionLevel GetIOCompressionLevel(CsvBinCompressionLevel compressionLevel)`
- L1376-1481 _public method_ `public void WriteBinFile(string filename, CsvBinCompressionLevel compressionLevel = CsvBinCompressionLevel.None)`
- L1484-1678 _public method_ `public static CsvStats ReadBinFile(string filename, string[] statNamesToRead=null, int numRowsToSkip=0, bool justHeader=false, CsvFileInfo FileInfoOut=null)`
- L1680-1825 _public method_ `public void WriteToCSV(string filename, bool bWriteMetadataRow = true)`
- L1828-1834 _public method_ `public void ComputeAveragesAndTotal()`
- L1836-1902 _public method_ `public void Combine(CsvStats srcStats, bool sumRows = false, bool computeAverage = true)`
- L1908-1992 _public method_ `public static CsvStats AverageByFrame(CsvStats[] statsToAvg, bool bStatsAvarage = false)`
- L1995-2005 _public method_ `public static CsvMetadata ReadCSVMetadata(string csvFilename)`
- L2006-2015 _public method_ `public static CsvMetadata ReadCSVMetadataFromLines(string [] csvFileLines)`
- L2017-2112 _public method_ `public void GetEventFrameIndexDelimiters(string startString, string endString, out List<int> startIndices, out List<int> endIndices)`
- L2114-2138 _public method_ `public void ComputeEventStripSampleMask(string startString, string endString, ref BitArray sampleMask)`
- L2140-2153 _private* method_ `StatSamples ApplySampleMaskToSamples(StatSamples sourceStat, BitArray sampleMask)`
- L2155-2210 _public method_ `public CsvStats ApplySampleMask(BitArray sampleMask, bool parallel=false)`
- L2212-2225 _public property_ `public int SampleCount { get; }`
- L2227-2231 _public method_ `public static bool DoesMetadataMatchFilter(CsvMetadata metadata, string metadataFilterString)`
- L2233-2236 _public method_ `public static bool IsDerivedStatExpression(string stat)`
- L2239-2263 _public method_ `public static CsvStats ReadCSVFile(string csvFilename, string[] statNames=null, int numRowsToSkip = 0, bool bGenerateCsvIdIfMissing=false, CsvFileInfo FileInfoOut=null, bool bJustHeader=false)`
- L2265-2279 _public method_ `public bool GenerateCsvIDIfMissing()`
- L2281-2321 _public method_ `public string MakeCsvIdHash()`
- L2324-2331 _private* method_ `static bool LineIsMetadata(string line)`
- L2333-2628 _public method_ `public static CsvStats ReadCSVFromLines(string[] linesArray, string[] statNames=null, int numRowsToSkip = 0, bool skipReadingData=false, CsvFileInfo fileInfo=null)`
- L2631 _public field_ `public Dictionary<string, StatSamples> Stats`
- L2631 _public field_ `public Dictionary< Stats`
- L2632 _public field_ `public List<CsvEvent> Events`
- L2633 _public field_ `public CsvMetadata metaData`

#### enum `CSVStats.CsvStats.BuiltinFunctionType`  
`enum BuiltinFunctionType`  
_private*; L627-627_
- L627 _public* enumerator_ `addstats`
- L627 _public* enumerator_ `meta`
- L627 _public* enumerator_ `eventcount`
- L627 _public* enumerator_ `framedelta`
- L627 _public* enumerator_ `cumulative`
- L627 _public* enumerator_ `COUNT`

#### class `CSVStats.Colour`  
`public class Colour`  
_public; L2637-2680_
- L2639 _public ctor_ `public Colour(byte rIn, byte gIn, byte bIn, float alphaIn = 1.0f)`
- L2640-2646 _public ctor_ `public Colour(uint hex, float alphaIn = 1.0f)`
- L2647 _public ctor_ `public Colour(Colour colourIn)`
- L2649-2657 _public ctor_ `public Colour(string str)`
- L2659-2662 _public method_ `public string SVGString()`
- L2663-2673 _public method_ `public string SVGStringNoQuotes()`
- L2675 _public field_ `public static Colour White = new Colour(255, 255, 255)`
- L2676 _public field_ `public static Colour Black = new Colour(0, 0, 0)`
- L2678 _public field_ `public byte r, g, b`
- L2678 _public field_ `public byte g`
- L2678 _public field_ `public byte b`
- L2679 _public field_ `public float alpha`

#### class `CSVStats.FileEfficientBitArray`  
`class FileEfficientBitArray`  
_internal*; L2683-2743_
- L2685-2688 _public ctor_ `public FileEfficientBitArray()`
- L2689-2694 _public ctor_ `public FileEfficientBitArray(int inBitCount)`
- L2696-2701 _public method_ `public bool Get(int bitIndex)`
- L2702-2707 _public method_ `public void Set(int bitIndex)`
- L2709-2716 _public method_ `public void WriteToFile(BinaryWriter fileWriter)`
- L2718-2731 _public method_ `public void ReadFromFile(BinaryReader fileReader)`
- L2732-2735 _public method_ `public int GetSizeBytes()`
- L2737-2740 _public property_ `public int Count { get; }`
- L2741 _private* field_ `uint[] words`
- L2742 _private* field_ `int bitCount`

### `Source/Programs/CSVTools/CsvStats/MetadataQueryBuilder.cs` (CSVStats-Core)


#### enum `CSVStats.EvalOp`  
`public enum EvalOp`  
_public; L8-15_
- L10 _public* enumerator_ `And`
- L11 _public* enumerator_ `Or`
- L12 _public* enumerator_ `None`
- L14 _public* enumerator_ `COUNT=None`

#### enum `CSVStats.ComparisonOp`  
`public enum ComparisonOp`  
_public; L17-28_
- L19 _public* enumerator_ `Equal`
- L20 _public* enumerator_ `NotEqual`
- L21 _public* enumerator_ `GreaterThan`
- L22 _public* enumerator_ `LessThan`
- L23 _public* enumerator_ `GreaterThanOrEqual`
- L24 _public* enumerator_ `LessThanOrEqual`
- L25 _public* enumerator_ `Contains`
- L27 _public* enumerator_ `COUNT`

#### class `CSVStats.QueryExpression`  
`public abstract class QueryExpression`  
_public; L30-35_
- L32 _public method_ `public abstract bool Evaluate(CsvMetadata metadata)`
- L34 _public field_ `public bool bNegate`

#### class `CSVStats.QueryComparisonExpression`  
`public class QueryComparisonExpression : QueryExpression`  
_public; L37-127_
- inherits: `QueryExpression`
- L39-123 _public method_ `public override bool Evaluate(CsvMetadata metadata)`
- L124 _public field_ `public string Key`
- L125 _public field_ `public string Value`
- L126 _public field_ `public ComparisonOp Op`

#### class `CSVStats.QueryLogicOpExpression`  
`public class QueryLogicOpExpression : QueryExpression`  
_public; L129-164_
- inherits: `QueryExpression`
- L131-136 _public ctor_ `public QueryLogicOpExpression()`
- L137-142 _public ctor_ `public QueryLogicOpExpression(QueryExpression first, QueryExpression second, EvalOp op)`
- L143 _public field_ `public QueryExpression First`
- L144 _public field_ `public QueryExpression Second`
- L145 _public field_ `public EvalOp Op`
- L147-163 _public method_ `public override bool Evaluate(CsvMetadata metadata)`

#### class `CSVStats.MetadataQueryBuilder`  
`public class MetadataQueryBuilder`  
_public; L166-402_
- L168-211 _private method_ `private static QueryComparisonExpression ConsumeTerm(ref List<string> tokenList)`
- L214-240 _private method_ `private static QueryExpression ConsumeBracketExpression(ref List<string> tokenList)`
- L242-260 _private method_ `private static EvalOp ConsumeOp(ref List<string> tokenList)`
- L262-270 _private method_ `private static bool ConsumeNot(ref List<string> tokenList)`
- L272-279 _private* method_ `static string FirstToken(List<string> tokenList)`
- L281-331 _private method_ `private static QueryExpression ConsumeExpression(ref List<string> tokenList)`
- L340-374 _private method_ `private static string ConsumeNextToken(ref string remainingString)`
- L376-390 _private method_ `private static List<string> Tokenize(string str)`
- L392-400 _public method_ `public static QueryExpression BuildQueryExpressionTree(string metadataFilterString)`

#### enum `CSVStats.MetadataQueryBuilder.CharType`  
`enum CharType`  
_private*; L333-338_
- L335 _public* enumerator_ `Standard`
- L336 _public* enumerator_ `Operator`
- L337 _public* enumerator_ `Whitespace`

### `Source/Programs/CSVTools/CsvStats/Properties/AssemblyInfo.cs` (CSVStats-Core)
_(no declarations)_

