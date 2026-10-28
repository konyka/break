# CSharp / CsvToSvgLib

- project root: `Source/Programs/CSVTools/CsvToSvgLib`
- files: 2; symbols: 200
- symbol kinds: class=13, const=1, ctor=11, enum=1, enumerator=3, field=109, method=61, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/CSVTools/CsvToSvgLib/CsvToSvgLib.cs` (CsvToSvgLib)


#### class `CSVTools.CsvToSvgLibVersion`  
`public class CsvToSvgLibVersion`  
_public; L16-21_
- L18 _private field_ `private static string VersionString = "3.70"`
- L20 _public method_ `public static string Get()`

#### enum `CSVTools.ShowEventTextMode`  
`public enum ShowEventTextMode`  
_public; L23-28_
- L25 _public* enumerator_ `Hide = 0`
- L26 _public* enumerator_ `ShowAuto = 1`
- L27 _public* enumerator_ `ShowAll = 2`

#### class `CSVTools.GraphParams`  
`public class GraphParams`  
_public; L30-181_
- L32 _public field_ `public int width = 1800`
- L33 _public field_ `public int height = 550`
- L34 _public field_ `public string title = ""`
- L35 _public field_ `public List<string> statNames = new List<string>()`
- L36 _public field_ `public List<string> ignoreStats = new List<string>()`
- L37 _public field_ `public int colorOffset = 0`
- L40 _public field_ `public List<string> showEventNames = new List<string>()`
- L41 _public field_ `public ShowEventTextMode showEventNameTextMode = ShowEventTextMode.ShowAuto`
- L42 _public field_ `public List<string> highlightEventRegions = new List<string>()`
- L45 _public field_ `public bool smooth = false`
- L46 _public field_ `public float smoothKernelPercent = 2.0f`
- L47 _public field_ `public int smoothKernelSize = -1`
- L50 _public field_ `public bool showMetadata = true`
- L51 _public field_ `public bool graphOnly = false`
- L52 _public field_ `public bool interactive = false`
- L53 _public field_ `public bool snapToPeaks = true`
- L54 _public field_ `public int maxHierarchyDepth = -1`
- L55 _public field_ `public char hierarchySeparator = '/'`
- L56 _public field_ `public List<string> hideStatPrefixes = new List<string>()`
- L59 _public field_ `public float compression = 0.0f`
- L60 _public field_ `public bool bFixedPointGraphs = true`
- L61 _public field_ `public float fixedPointPrecisionScale = 2.0f`
- L62 _public field_ `public int lineDecimalPlaces = 3`
- L65 _public field_ `public bool stacked = false`
- L66 _public field_ `public string stackTotalStat = ""`
- L67 _public field_ `public bool stackedUnsorted = false`
- L70 _public field_ `public bool percentileTop90 = false`
- L71 _public field_ `public bool percentileTop99 = false`
- L72 _public field_ `public bool percentile = false`
- L75 _public field_ `public float minX = Range.Auto`
- L76 _public field_ `public float maxX = Range.Auto`
- L77 _public field_ `public float minY = Range.Auto`
- L78 _public field_ `public float maxY = Range.Auto`
- L81 _public field_ `public string startEvent`
- L82 _public field_ `public int startEventOffset = 0`
- L83 _public field_ `public string endEvent`
- L84 _public field_ `public int endEventOffset = 0`
- L87 _public field_ `public float maxAutoMaxY = 0.0f`
- L89 _public field_ `public float budget = float.MaxValue`
- L90 _public field_ `public float lineThickness = 1.0f`
- L93 _public field_ `public float threshold = -float.MaxValue`
- L94 _public field_ `public float averageThreshold = -float.MaxValue`
- L96 _public field_ `public string embedText = "Created with CSVtoSVG "+ CsvToSvgLibVersion.Get()`
- L97 _public field_ `public string uniqueId = "ID"`
- L100 _public field_ `public bool showAverages = false`
- L101 _public field_ `public bool showTotals = false`
- L102 _public field_ `public bool forceLegendSort = false`
- L103 _public field_ `public float legendAverageThreshold = -float.MaxValue`
- L104 _public field_ `public List<string> customLegendNames = new List<string>()`
- L105 _public field_ `public List<string> csvColors = new List<string>()`
- L108 _public field_ `public bool bSmoothMultithreaded = true`
- L109 _public field_ `public bool bPerfLog = false`
- L112 _public field_ `public string themeName = ""`
- L113 _public field_ `public int frameOffset = 0`
- L114 _public field_ `public float statMultiplier = 1.0f`
- L115 _public field_ `public string minFilterStatName = null`
- L116 _public field_ `public float minFilterStatValue = -float.MaxValue`
- L117 _public field_ `public bool filterOutZeros = false`
- L118 _public field_ `public bool discardLastFrame = true`
- L120 _private field_ `private bool bFinalized = false`
- L122-169 _public method_ `public void FinalizeSettings()`
- L172-180 _public method_ `public void DebugPrintProperties()`

#### class `CSVTools.CsvInfo`  
`public class CsvInfo`  
_public; L183-192_
- L185-189 _public ctor_ `public CsvInfo(CsvStats csvStatsIn, string csvFilenameIn)`
- L190 _public field_ `public CsvStats stats`
- L191 _public field_ `public string filename`

#### class `CSVTools.SvgFile`  
`class SvgFile`  
_internal*; L194-241_
- L196-201 _public ctor_ `public SvgFile(string filename, string inUniqueId=null)`
- L203-206 _public method_ `public void WriteFast(string str)`
- L208-211 _public method_ `public void Write(string str)`
- L213-216 _public method_ `public void WriteLineFast(string str)`
- L218-222 _public method_ `public void WriteLine(string str)`
- L224-228 _public method_ `public void Flush()`
- L230-235 _public method_ `public void Close()`
- L237 _private* field_ `readonly string idSuffix`
- L238 _private* field_ `System.IO.StreamWriter file = null`
- L239 _private* field_ `StringBuilder sb = null`

#### class `CSVTools.Rect`  
`class Rect`  
_internal*; L245-253_
- L247-250 _public ctor_ `public Rect(float xIn, float yIn, float widthIn, float heightIn)`
- L251 _public field_ `public float x, y`
- L251 _public field_ `public float y`
- L252 _public field_ `public float width, height`
- L252 _public field_ `public float height`

#### class `CSVTools.Range`  
`class Range`  
_internal*; L255-263_
- L257 _public const_ `public const float Auto = -100000.0f`
- L259 _public ctor_ `public Range()`
- L260 _public ctor_ `public Range(float minx, float maxx, float miny, float maxy)`
- L261 _public field_ `public float MinX, MaxX`
- L261 _public field_ `public float MaxX`
- L262 _public field_ `public float MinY, MaxY`
- L262 _public field_ `public float MaxY`

#### class `CSVTools.Theme`  
`class Theme`  
_internal*; L265-368_
- L268-354 _public ctor_ `public Theme(string Name)`
- L355 _public field_ `public Colour BackgroundColour`
- L356 _public field_ `public Colour BackgroundColourCentre`
- L357 _public field_ `public Colour LineColour`
- L358 _public field_ `public Colour TextColour`
- L359 _public field_ `public Colour MinorTextColour`
- L360 _public field_ `public Colour MediumTextColour`
- L361 _public field_ `public Colour AxisLineColour`
- L362 _public field_ `public Colour MinorGridlineColour`
- L363 _public field_ `public Colour MajorGridlineColour`
- L364 _public field_ `public Colour BudgetLineColour`
- L365 _public field_ `public Colour EventTextColour`
- L366 _public field_ `public float BudgetLineThickness`
- L367 _public field_ `public Colour[] GraphColours`

#### class `CSVTools.GraphGenerator`  
`public class GraphGenerator`  
_public; L371-2910_
- L373 _private* field_ `List<CsvInfo> csvList`
- L375-378 _public ctor_ `public GraphGenerator(List<CsvInfo> csvsIn)`
- L380-384 _public ctor_ `public GraphGenerator(CsvStats csv, string filename)`
- L386-393 _public method_ `public Task MakeGraphAsync(GraphParams graphParams, string svgFilename, bool bWriteErrorsToSvg, bool rethrowExceptions = true)`
- L395-427 _public method_ `public void MakeGraph(GraphParams graphParams, string svgFilename, bool bWriteErrorsToSvg, bool rethrowExceptions = true)`
- L429-803 _private* method_ `void MakeGraphInternal(GraphParams graphParams, SvgFile svg)`
- L805-837 _private* method_ `Range ComputeAdjustedYRange(Range range, Rect rect, List<CsvStats> csvStats, float maxAutoMaxY)`
- L839-868 _private* method_ `Range ComputeAdjustedXRange(Range range, Rect rect, List<CsvStats> csvStats)`
- L972-1020 _private* method_ `CsvStats SmoothStats(CsvStats stats, int KernelSize, GraphParams graphParams)`
- L1022-1047 _private* method_ `void SetLegend(CsvStats csvStats, string csvFilename, GraphParams graphParams, bool UseFilename, ref int currentCustomLabelIndex)`
- L1049-1080 _private* method_ `int AssignColours(CsvStats stats, Theme theme, bool reverseOrder, int inColorOffset, Colour csvColorOverride)`
- L1082-1182 _private* method_ `CsvStats StackStats(CsvStats stats, Range range, bool stackedUnsorted, string stackTotalStat, bool bStackTotalStatIsAutomatic)`
- L1184-1205 _private* method_ `float GetXAxisIncrement(Rect rect, Range range)`
- L1207-1226 _private* method_ `float GetYAxisIncrement(Rect rect, Range range)`
- L1228-1306 _private* method_ `void DrawGridLines(SvgFile svg, Theme theme, Rect rect, Range range, GraphParams graphParams, bool bDrawAxisText, float alpha = 1.0f, bool extendLines = false)`
- L1308-1314 _private* method_ `void DrawText(SvgFile svg, string text, float x, float y, float size, Rect rect, Colour colour, string anchor = "start", string font = "Helvetica", string id = "", bool dropShadow = false)`
- L1316-1319 _private* method_ `void DrawTitle(SvgFile svg, Theme theme, string title, Rect rect)`
- L1322-1337 _private* method_ `void DrawGraphArea(SvgFile svg, Theme theme, Colour colour, Rect rect, bool gradient, bool interactive = false)`
- L1339-1343 _private* method_ `float ToSvgX(float graphX, Rect rect, Range range)`
- L1345-1352 _private* method_ `float ToSvgY(float graphY, Rect rect, Range range)`
- L1354-1358 _private* method_ `float ToSvgXScale(float graphX, Rect rect, Range range)`
- L1360-1364 _private* method_ `float ToSvgYScale(float graphY, Rect rect, Range range)`
- L1366-1370 _private* method_ `float ToCsvXScale(float graphX, Rect rect, Range range)`
- L1372-1376 _private* method_ `float ToCsvYScale(float graphY, Rect rect, Range range)`
- L1378-1381 _private* method_ `float ToCsvX(float svgX, Rect rect, Range range)`
- L1383-1386 _private* method_ `float ToCsvY(float svgY, Rect rect, Range range)`
- L1422-1467 _private* method_ `Vec2[] RemoveRedundantPoints(Vec2[] RawPoints, float compressionThreshold, int passIndex)`
- L1469-1521 _private* method_ `List<Vec2> CompressPoints(List<Vec2> RawPoints, float pixelsPerPoint, Rect rect, Range range)`
- L1523-1631 _private* method_ `void DrawGraph(SvgFile svg, List<float> samples, Colour colour, Rect rect, Range range, float thickness, string id, GraphParams graphParams, int MaxSegments=1)`
- L1632-1668 _private* method_ `void DrawPercentileGraph(SvgFile svg, List<float> samples, Colour colour, Rect rect, Range range, string id)`
- L1685-1692 _private method_ `private string truncateTextIfNeeded(string text, int maxLength)`
- L1694-1791 _private* method_ `void DrawEventText(SvgFile svg, List<CsvEvent> events, Colour colour, Rect rect, Range range, GraphParams graphParams )`
- L1793-1815 _private* method_ `void DrawEventLines(SvgFile svg, Theme theme, List<CsvEvent> events, Rect rect, Range range)`
- L1818-1859 _private* method_ `void DrawEventHighlightRegions(SvgFile svg, CsvStats csvStats, Rect rect, Range range, List<string> highlightEventRegions )`
- L1860-1872 _private* method_ `void DrawVerticalAxisNotch(SvgFile svg, float sample, Colour colour, Rect rect, Range range, float thickness = 0.25f)`
- L1874-1898 _private* method_ `void DrawHorizLine(SvgFile svg, float sample, Colour colour, Rect rect, Range range, bool dashed = false, float thickness = 0.25f, bool dropShadow = false)`
- L1900-1905 _private* method_ `void DrawVerticalAxisText(SvgFile svg, string text, float textY, Colour colour, Rect rect, Range range, float size = 10.0f)`
- L1908-1920 _private* method_ `void DrawHorizontalAxisText(SvgFile svg, string text, float textX, Colour colour, Rect rect, Range range, float size = 10.0f, bool top = false)`
- L1922-1996 _private* method_ `void DrawLegend(SvgFile svg, Theme theme, List<CsvStats> csvStats, GraphParams graphParams, Rect rect)`
- L1999-2021 _private* method_ `void DrawVerticalLine(SvgFile svg, float sampleX, Colour colour, Rect rect, Range range, float thickness = 0.25f, bool dashed = false, bool dropShadow = false, string id = "", bool noTranslate = false)`
- L2022-2025 _private* method_ `float frac(float value)`
- L2027-2035 _private* method_ `string GetStringHash8Char(string name)`
- L2037-2053 _private* method_ `string GetJSStatName(string statName)`
- L2067-2587 _private* method_ `void AddInteractiveScripting(SvgFile svg, Theme theme, Rect rect, Range range, List<CsvStats> csvStats, GraphParams graphParams )`
- L2589-2606 _private* method_ `void DrawMetadata(SvgFile svg, CsvMetadata metadata, Rect rect, Colour colour)`
- L2608-2611 _private* method_ `bool IsEventShown(string eventString, GraphParams graphParams)`
- L2613-2649 _private* method_ `int GetEventPriority(string eventString, GraphParams graphParams)`
- L2651-2695 _private* method_ `bool IsStatIgnored(string statName, GraphParams graphParams)`
- L2709-2736 _private* method_ `FrameRange GetEventTruncationFrameRange(CsvStats csvStats, GraphParams graphParams)`
- L2738-2898 _private* method_ `CsvStats ProcessCsvStats(CsvStats csvStatsIn, GraphParams graphParams, out FrameRange frameRange)`
- L2900-2909 _private* method_ `void RecomputeStatAveragesForRange(CsvStats stats, Range range)`

#### class `CSVTools.GraphGenerator.SmoothKernel`  
`class SmoothKernel`  
_private*; L870-965_
- L872-894 _public ctor_ `public SmoothKernel(int inKernelSize, float maxDownsampleMultiplier = 4.0f)`
- L895-960 _public method_ `public StatSamples SmoothStatSamples(StatSamples sourceStatSamples)`
- L962 _private* field_ `int kernelSize`
- L963 _private* field_ `int downsampleLevel`
- L964 _private* field_ `float [] weights`

#### struct `CSVTools.GraphGenerator.Vec2`  
`struct Vec2`  
_private*; L1388-1393_
- L1390 _public ctor_ `public Vec2(float inX, float inY)`
- L1391 _public field_ `public float X`
- L1392 _public field_ `public float Y`

#### class `CSVTools.GraphGenerator.PointInfo`  
`class PointInfo`  
_private*; L1395-1418_
- L1397-1406 _public method_ `public void AddPoint(Vec2 pt)`
- L1407-1413 _public method_ `public Vec2 ComputeAvg()`
- L1414 _public field_ `public Vec2 Max = new Vec2(float.MinValue, float.MinValue)`
- L1415 _public field_ `public Vec2 Min = new Vec2(float.MaxValue, float.MaxValue)`
- L1416 _public field_ `public Vec2 Total = new Vec2(0, 0)`
- L1417 _public field_ `public int Count = 0`

#### class `CSVTools.GraphGenerator.CsvGraphEvent`  
`class CsvGraphEvent : CsvEvent`  
_private*; L1671-1683_
- inherits: `CsvEvent`
- L1673-1680 _public ctor_ `public CsvGraphEvent(CsvEvent ev, int inPriority)`
- L1681 _public field_ `public int count`
- L1682 _public field_ `public int priority`

#### class `CSVTools.GraphGenerator.InteractiveStatInfo`  
`class InteractiveStatInfo`  
_private*; L2055-2065_
- L2057 _public field_ `public string friendlyName`
- L2058 _public field_ `public string jsVarName`
- L2059 _public field_ `public string jsTextElementId`
- L2060 _public field_ `public string jsGroupElementId`
- L2061 _public field_ `public string graphID`
- L2062 _public field_ `public Colour colour`
- L2063 _public field_ `public StatSamples statSamples`
- L2064 _public field_ `public StatSamples originalStatSamples`

#### class `CSVTools.GraphGenerator.FrameRange`  
`class FrameRange`  
_private*; L2698-2707_
- L2700-2703 _public method_ `public bool isLimited()`
- L2705 _public field_ `public int start = 0`
- L2706 _public field_ `public int end = Int32.MaxValue`

### `Source/Programs/CSVTools/CsvToSvgLib/Properties/AssemblyInfo.cs` (CsvToSvgLib)
_(no declarations)_

