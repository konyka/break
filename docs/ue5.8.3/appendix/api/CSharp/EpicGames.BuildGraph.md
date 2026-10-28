# CSharp / EpicGames.BuildGraph

- project root: `Source/Programs/Shared/EpicGames.BuildGraph`
- files: 35; symbols: 1039
- symbol kinds: class=144, ctor=132, enum=9, enumerator=83, field=35, indexer=1, interface=1, method=319, operator=38, property=276, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.BuildGraph/BgAgentDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgAgentDef`  
`public class BgAgentDef`  
_public; L13-44_
- attrs: `[DebuggerDisplay("{Name}")] [BgObject(typeof(BgAgentDefSerializer))]`
- desc: Stores a list of nodes which can be executed on a single agent
- L18 _public property_ `public string Name { get; }` — Name of this agent. Used for display purposes in a build system.
- L24 _public property_ `public List<string> PossibleTypes { get; }` — Array of valid agent types that these nodes may run on. When running in the build system, this determines the class of machine that should be selected to run these nodes. The first defined agent type for this branch will be used.
- L29 _public property_ `public List<BgNodeDef> Nodes { get; set; }` — List of nodes in this agent group.
- L34 _public property_ `public List<BgDiagnosticDef> Diagnostics { get; }` — Diagnostics to output if executing this agent
- L40-43 _public ctor_ `public BgAgentDef(string name)` — Constructor

#### class `EpicGames.BuildGraph.BgAgentDefSerializer`  
`class BgAgentDefSerializer : BgObjectSerializer<BgAgentDef>`  
_internal*; L46-55_
- inherits: `BgObjectSerializer<BgAgentDef>`
- L49-54 _public method_ `public override BgAgentDef Deserialize(BgObjectDef<BgAgentDef> obj)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/BgAggregateDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgAggregateDef`  
`public class BgAggregateDef`  
_public; L10-39_
- desc: Defines a agggregate within a graph, which give the combined status of one or more job steps, and allow building several steps at once.
- L15 _public property_ `public string Name { get; }` — Name of this badge
- L20 _public property_ `public HashSet<BgNodeDef> RequiredNodes { get; }` — Set of nodes that must be run for this label to be shown.
- L26-29 _public ctor_ `public BgAggregateDef(string name)` — Constructor
- L35-38 _public method_ `public override string ToString()` — Get the name of this label

#### class `EpicGames.BuildGraph.BgAggregateExpressionDef`  
`public class BgAggregateExpressionDef`  
_public; L45-76_
- attrs: `[BgObject(typeof(BgAggregateExpressionDefSerializer))]`
- desc: Aggregate that was created from bytecode
- L48 _public property_ `public string Name { get; set; }` — (inheritdoc)
- L51 _public property_ `public List<BgNodeExpressionDef> RequiredNodes { get; }` — (inheritdoc)
- L56 _public property_ `public BgLabelDef? Label { get; set; }` — Labels to add this aggregate to
- L61-64 _public ctor_ `public BgAggregateExpressionDef(string name)` — Constructor
- L70-75 _public method_ `public BgAggregateDef ToAggregateDef()` — Construct a BgAggregateDef

#### class `EpicGames.BuildGraph.BgAggregateExpressionDefSerializer`  
`class BgAggregateExpressionDefSerializer : BgObjectSerializer<BgAggregateExpressionDef>`  
_internal*; L78-87_
- inherits: `BgObjectSerializer<BgAggregateExpressionDef>`
- L81-86 _public method_ `public override BgAggregateExpressionDef Deserialize(BgObjectDef<BgAggregateExpressionDef> obj)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/BgAnnotationDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgAnnotationDef`  
`public class BgAnnotationDef`  
_public; L8-36_
- desc: Defines an annotation key/value pair for BuildGraph nodes
- L13 _public property_ `public string Name { get; set; }` — Name, or key, of the annotation
- L18 _public property_ `public string Value { get; set; }` — Value to be paired with the annotation name
- L23-27 _public ctor_ `public BgAnnotationDef(string name, string value)` — Constructor
- L32-35 _public method_ `public override string ToString()` — Simply the annotation name.

### `Source/Programs/Shared/EpicGames.BuildGraph/BgArtifactDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgArtifactDef`  
`public class BgArtifactDef`  
_public; L10-83_
- desc: Defines an artifact produced by the build
- L15 _public property_ `public string Name { get; }` — Name of this artifact
- L20 _public property_ `public string? Type { get; }` — Type of this artifact
- L25 _public property_ `public string? Description { get; }` — Description for the artifact
- L30 _public property_ `public string? BasePath { get; }` — Base path for files included in the artifact. Will be detected from the files specified if not set.
- L35 _public property_ `public string? NodeName { get; }` — Node that produces the artifact. Either this or TagName should be set.
- L40 _public property_ `public string? TagName { get; }` — Tag to use for the artifact. Uses the artifact name by default.
- L45 _public property_ `public IReadOnlyList<string> Keys { get; }` — Keys that can be used to find the artifact
- L50 _public property_ `public IReadOnlyList<string> Metadata { get; }` — Metadata for the artifact
- L63-73 _public ctor_ `public BgArtifactDef(string name, string? type, string? description, string? basePath, string? nodeName, string? tagName, IReadOnlyList<string> keys, IReadOnlyList<string> metadata)` — Constructor
- L79-82 _public method_ `public override string ToString()` — Get the name of this badge

### `Source/Programs/Shared/EpicGames.BuildGraph/BgBadgeDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgBadgeDef`  
`public class BgBadgeDef`  
_public; L10-53_
- desc: Defines a badge which gives an at-a-glance summary of part of the build, and can be displayed in UGS
- L15 _public property_ `public string Name { get; }` — Name of this badge
- L20 _public property_ `public string Project { get; }` — Depot path to the project that this badge applies to. Used for filtering in UGS.
- L25 _public property_ `public int Change { get; }` — The changelist to post the badge for
- L30 _public property_ `public HashSet<BgNodeDef> Nodes { get; }` — Set of nodes that this badge reports the status of
- L38-43 _public ctor_ `public BgBadgeDef(string inName, string inProject, int inChange)` — Constructor
- L49-52 _public method_ `public override string ToString()` — Get the name of this badge

### `Source/Programs/Shared/EpicGames.BuildGraph/BgBytecodeWriter.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgBytecodeWriter`  
`public abstract class BgBytecodeWriter`  
_public; L8-63_
- desc: Helper class for writing BuildGraph bytecode to a buffer.
- L14 _public method_ `public abstract void WriteOpcode(BgOpcode opcode)` — Writes an opcode to the output
- L20 _public method_ `public abstract void WriteString(string str)` — Writes a string to the output
- L26 _public method_ `public abstract void WriteName(string name)` — Writes a reference to an interned string to the output
- L32 _public method_ `public abstract void WriteSignedInteger(long value)` — Writes a signed integer value to the output
- L38 _public method_ `public void WriteUnsignedInteger(int value)` — Writes an unsigned integer to the output
- L44 _public method_ `public abstract void WriteUnsignedInteger(ulong value)` — Writes an unsigned integer to the output
- L50 _public method_ `public abstract void WriteExpr(BgExpr expr)` — Writes an expression to the output buffer
- L56 _public method_ `public abstract void WriteExprAsFragment(BgExpr expr)` — Writes an expression as a standalone fragment, encoding just the fragment index into the output stream
- L62 _public method_ `public abstract void WriteThunk(BgThunkDef thunk)` — Writes a thunk to native code.

### `Source/Programs/Shared/EpicGames.BuildGraph/BgCompiler.cs` (EpicGames.BuildGraph)


#### enum `EpicGames.BuildGraph.BgBytecodeVersion`  
`enum BgBytecodeVersion`  
_internal*; L16-19_
- desc: Version numbers for bytecode streams
- L18 _public* enumerator_ `Current = 0`

#### class `EpicGames.BuildGraph.BgCompiler`  
`public static class BgCompiler`  
_public; L24-237_
- desc: Helper class for writing BuildGraph bytecode to a buffer.
- L200-236 _public method_ `public static (byte[], BgThunkDef[]) Compile(BgExpr expr)` — Compiles the given expression into bytecode

#### class `EpicGames.BuildGraph.BgCompiler.ReferenceEqualityComparer`  
`class ReferenceEqualityComparer : IEqualityComparer<object>`  
_private*; L26-34_
- inherits: `IEqualityComparer<object>`
- L28 _public field_ `public static readonly ReferenceEqualityComparer Instance = new()`
- L30 _public method_ `public new bool Equals([AllowNull] object x, [AllowNull] object y)`
- L33 _public method_ `public int GetHashCode([DisallowNull] object obj)` — attrs: `[SuppressMessage("MicrosoftCodeAnalysisCorrectness", "RS1024:Compare symbols correctly", Justification = "<Pending>")]`

#### class `EpicGames.BuildGraph.BgCompiler.FragmentCollector`  
`class FragmentCollector : BgBytecodeWriter`  
_private*; L36-107_
- inherits: `BgBytecodeWriter`
- L38 _private* field_ `readonly HashSet<BgExpr> _uniqueExprs = new(ReferenceEqualityComparer.Instance)`
- L39 _private* field_ `readonly List<BgExpr> _fragments`
- L40 _private* field_ `readonly Dictionary<BgExpr, int> _exprToFragmentIndex`
- L40 _private* field_ `readonly Dictionary< _exprToFragmentIndex`
- L42-46 _public ctor_ `public FragmentCollector(List<BgExpr> fragments, Dictionary<BgExpr, int> exprToFragmentIdx)`
- L49-63 _public method_ `public override void WriteExpr(BgExpr expr)` — (inheritdoc)
- L66-74 _public method_ `public override void WriteExprAsFragment(BgExpr expr)` — (inheritdoc)
- L80-88 _private* method_ `void RegisterFragment(BgExpr expr)` — Registers an expression for compilation into a new fragment
- L91 _public method_ `public override void WriteOpcode(BgOpcode opcode)` — (inheritdoc)
- L94 _public method_ `public override void WriteName(string str)` — (inheritdoc)
- L97 _public method_ `public override void WriteString(string str)` — (inheritdoc)
- L100 _public method_ `public override void WriteSignedInteger(long value)` — (inheritdoc)
- L103 _public method_ `public override void WriteUnsignedInteger(ulong value)` — (inheritdoc)
- L106 _public method_ `public override void WriteThunk(BgThunkDef handler)` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgCompiler.ForwardWriter`  
`class ForwardWriter : BgBytecodeWriter`  
_private*; L109-193_
- inherits: `BgBytecodeWriter`
- L111 _private* field_ `readonly ByteArrayBuilder _builder`
- L112 _private* field_ `readonly Dictionary<BgExpr, int> _exprToFragmentIdx`
- L112 _private* field_ `readonly Dictionary< _exprToFragmentIdx`
- L113 _private* field_ `readonly List<string> _names`
- L114 _private* field_ `readonly List<BgThunkDef> _thunks`
- L115 _private* field_ `readonly Dictionary<string, int> _nameToIndex = ...`
- L115 _private* field_ `readonly Dictionary< _nameToIndex = []`
- L117-128 _public ctor_ `public ForwardWriter(ByteArrayBuilder builder, Dictionary<BgExpr, int> exprToFragmentIdx, List<string> names, List<BgThunkDef> thunks)`
- L131-143 _public method_ `public override void WriteExpr(BgExpr expr)` — (inheritdoc)
- L146-149 _public method_ `public override void WriteExprAsFragment(BgExpr expr)` — (inheritdoc)
- L152-155 _public method_ `public override void WriteOpcode(BgOpcode opcode)` — (inheritdoc)
- L158-168 _public method_ `public override void WriteName(string name)` — (inheritdoc)
- L171-179 _public method_ `public override void WriteString(string str)` — (inheritdoc)
- L182 _public method_ `public override void WriteSignedInteger(long value)` — (inheritdoc)
- L185 _public method_ `public override void WriteUnsignedInteger(ulong value)` — (inheritdoc)
- L188-192 _public method_ `public override void WriteThunk(BgThunkDef thunk)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/BgContext.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgContext`  
`public abstract class BgContext`  
_public; L13-132_
- desc: Context for executing a node method
- L18 _public property_ `public abstract string Stream { get; }` — The stream executing the current build
- L23 _public property_ `public abstract int Change { get; }` — Changelist being built
- L28 _public property_ `public abstract int CodeChange { get; }` — The code changelist currently being built
- L33 _public property_ `public abstract (int Major, int Minor, int Patch) EngineVersion { get; }` — Version number for the engine
- L38 _public property_ `public abstract bool IsBuildMachine { get; }` — Whether this machine is a builder
- L43 _public property_ `public HashSet<FileReference> BuildProducts { get; }` — All outputs for the node
- L45 _private* field_ `readonly Dictionary<string, FileSet> _tagNameToFileSet`
- L45 _private* field_ `readonly Dictionary< _tagNameToFileSet`
- L50-53 _protected ctor_ `protected BgContext(Dictionary<string, FileSet> tagNameToFileSet)` — Constructor
- L60 _public method_ `public bool Get(BgBool expr)` — Resolve a boolean expression to a value
- L67 _public method_ `public int Get(BgInt expr)` — Resolve an integer expression to a value
- L74 _public method_ `public string Get(BgString expr)` — Resolve a string expression to a value
- L82 _public method_ `public TEnum Get<TEnum>(BgEnum<TEnum> expr) where TEnum : struct` — Resolves an enum expression to a value
- L90 _public method_ `public List<TEnum> Get<TEnum>(BgList<BgEnum<TEnum>> expr) where TEnum : struct` — Resolve a list of enums to a value
- L97 _public method_ `public List<string> Get(BgList<BgString> expr)` — Resolve a list of strings
- L104-116 _public method_ `public FileSet Get(BgFileSet fileSet)` — Resolve a file set
- L123-131 _public method_ `public FileSet Get(BgList<BgFileSet> fileSets)` — Resolve a file set

### `Source/Programs/Shared/EpicGames.BuildGraph/BgDiagnosticDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgDiagnosticDef`  
`public class BgDiagnosticDef`  
_public; L11-56_
- desc: Diagnostic message from the graph script. These messages are parsed at startup, then culled along with the rest of the graph nodes before output. Doing so allows errors and warnings which are only output if a node is part of the graph being executed.
- L16 _public property_ `public string File { get; }` — File containing the diagnostic
- L21 _public property_ `public int Line { get; }` — Line number containing the diagnostic
- L26 _public property_ `public LogLevel Level { get; }` — The diagnostic event type
- L31 _public property_ `public string Message { get; }` — The message to display
- L36 _public property_ `public bool ReportOnExecution { get; }` — Report the diagnostic during execution
- L42 _public property_ `public string[] ReportOnNodes { get; }` — An optional set of node names that when ReportOnExecution is true limits the reporting of the diagnostic to only this set of nodes
- L47-55 _public ctor_ `public BgDiagnosticDef(string file, int line, LogLevel level, string message, bool reportOnExecution, string[] reportOnNodes)` — Constructor

### `Source/Programs/Shared/EpicGames.BuildGraph/BgGraphDef.cs` (EpicGames.BuildGraph)


#### enum `EpicGames.BuildGraph.GraphPrintOptions`  
`public enum GraphPrintOptions`  
_public; L20-41_
- attrs: `[Flags]`
- desc: Options for how the graph should be printed
- L25 _public* enumerator_ `None = 0` — No options specified
- L30 _public* enumerator_ `ShowCommandLineOptions = 0x1` — Includes a list of the graph options
- L35 _public* enumerator_ `ShowDependencies = 0x2` — Includes the list of dependencies for each node
- L40 _public* enumerator_ `ShowNotifications = 0x4` — Includes the list of notifiers for each node

#### class `EpicGames.BuildGraph.BgGraphDef`  
`public class BgGraphDef`  
_public; L46-789_
- desc: Definition of a graph.
- L51 _public property_ `public List<BgOptionDef> Options { get; }` — List of options, in the order they were specified
- L56 _public property_ `public List<BgAgentDef> Agents { get; }` — List of agents containing nodes to execute
- L61 _public property_ `public Dictionary<string, BgAgentDef> NameToAgent { get; set; }` — Mapping from name to agent
- L66 _public property_ `public Dictionary<string, BgNodeDef> NameToNode { get; set; }` — Mapping of names to the corresponding node.
- L71 _public property_ `public Dictionary<string, BgReport> NameToReport { get; set; }` — Mapping of names to the corresponding report.
- L76 _public property_ `public Dictionary<string, BgNodeOutput> TagNameToNodeOutput { get; set; }` — Mapping of names to their corresponding node output.
- L81 _public property_ `public Dictionary<string, BgAggregateDef> NameToAggregate { get; set; }` — Mapping of aggregate names to their respective nodes
- L86 _public property_ `public List<BgArtifactDef> Artifacts { get; }` — Mapping of artifact names to their definitions. Artifacts will be produced from matching tag names.
- L91 _public property_ `public List<BgBadgeDef> Badges { get; }` — List of badges that can be displayed for this build
- L96 _public property_ `public List<BgLabelDef> Labels { get; }` — List of labels that can be displayed for this build
- L101 _public property_ `public List<BgDiagnosticDef> Diagnostics { get; }` — Diagnostics at graph scope
- L106-108 _public ctor_ `public BgGraphDef()` — Default constructor
- L115-118 _public method_ `public bool ContainsName(string name)` — Checks whether a given name already exists
- L124-136 _public method_ `public List<BgDiagnosticDef> GetAllDiagnostics()` — Gets diagnostics from all graph structures
- L144-187 _public method_ `public bool TryResolveReference(string name, [NotNullWhen(true)] out BgNodeDef[]? outNodes)` — Tries to resolve the given name to one or more nodes. Checks for aggregates, and actual nodes.
- L195-227 _public method_ `public bool TryResolveInputReference(string name, [NotNullWhen(true)] out BgNodeOutput[]? outOutputs)` — Tries to resolve the given name to one or more node outputs. Checks for aggregates, and actual nodes.
- L229-243 _private* method_ `static void AddDependencies(BgNodeDef node, HashSet<BgNodeDef> retainNodes)`
- L249-318 _public method_ `public void Select(IEnumerable<BgNodeDef> targetNodes)` — Cull the graph to only include the given nodes and their dependencies
- L325-436 _public method_ `public void Export(FileReference file, HashSet<BgNodeDef> completedNodes)` — Export the build graph to a Json file, for parallel execution by the build system
- L442-662 _public method_ `public void ExportForHorde(FileReference file)` — Export the build graph to a Json file for parsing by Horde
- L670-788 _public method_ `public void Print(HashSet<BgNodeDef> completedNodes, GraphPrintOptions printOptions, ILogger logger)` — Print the contents of the graph

#### class `EpicGames.BuildGraph.BgGraphExpressionDef`  
`public class BgGraphExpressionDef`  
_public; L794-875_
- desc: Definition of a graph from bytecode. Can be converted to regular graph definition.
- L799 _public property_ `public List<BgNodeExpressionDef> Nodes { get; }` — Nodes for the graph
- L804 _public property_ `public List<BgAggregateExpressionDef> Aggregates { get; }` — Aggregates for the graph
- L810-849 _public method_ `public BgGraphDef ToGraphDef()` — Creates a graph definition from this template
- L851-874 _private* method_ `static void RegisterNode(BgGraphDef graph, BgNodeExpressionDef node, HashSet<BgNodeDef> uniqueNodes, HashSet<BgAgentDef> uniqueAgents)`

### `Source/Programs/Shared/EpicGames.BuildGraph/BgInterpreter.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgBytecodeException`  
`public sealed class BgBytecodeException : Exception`  
_public; L20-52_
- inherits: `Exception`
- desc: Exception thrown by the runtime
- L25 _public property_ `public string SourceFile { get; }` — Source file that the error was thrown from
- L30 _public property_ `public int SourceLine { get; }` — Line number that threw the exception
- L35 _public property_ `public string Diagnostic { get; }` — Message to display
- L43-48 _public ctor_ `public BgBytecodeException(string sourceFile, int sourceLine, string diagnostic)` — Constructor
- L51 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgInterpreter`  
`public class BgInterpreter`  
_public; L57-917_
- desc: Interprets compiled buildgraph bytecode
- L115 _private* field_ `readonly byte[] _data`
- L116 _private* field_ `readonly BgThunkDef[] _thunks`
- L117 _private* field_ `readonly string[] _names`
- L118 _private* field_ `readonly IReadOnlyDictionary<string, string> _options`
- L118 _private* field_ `readonly IReadOnlyDictionary< _options`
- L119 _private* field_ `readonly BgBytecodeVersion _version`
- L120 _private* field_ `readonly int[] _fragments`
- L121 _private* field_ `readonly List<BgOptionDef> _optionDefs = []`
- L126 _public property_ `public IReadOnlyList<BgOptionDef> OptionDefs => ...` — The option definitions that were parsed during execution
- L128 _private* field_ `static readonly BgOpcodeInfo[] s_opcodeTable = CreateOpcodeLookup()`
- L130-198 _private* method_ `static BgOpcodeInfo[] CreateOpcodeLookup()`
- L206-226 _public ctor_ `public BgInterpreter(byte[] data, BgThunkDef[] thunks, IReadOnlyDictionary<string, string> options)` — Constructor
- L231-237 _public method_ `public object Evaluate()` — Evaluates the graph
- L239-249 _private* method_ `object Evaluate(Frame frame)`
- L251-286 _private* method_ `object ReadArgument(Frame frame, BgArg type)`
- L288-703 _private* method_ `object Evaluate(Frame frame, BgOpcode opcode, object arg0, object arg1, object arg2)`
- L705-708 _private* method_ `static List<T> GetListArg<T>(object value)`
- L710-713 _private* method_ `IEnumerable<object> LazyEvaluateItem(Frame frame, int fragment)`
- L715-722 _private* method_ `IEnumerable<object> LazyEvaluateList(Frame frame, int fragment)`
- L724-739 _private* method_ `object Jump(Frame frame, int fragment)`
- L741-745 _private* method_ `object Call(int fragment, object[] arguments)`
- L747-750 _private* method_ `int ReadFragment(Frame frame)`
- L756-760 _private* method_ `BgOpcode ReadOpcode(Frame frame)` — Reads an opcode from the input stream
- L765-769 _private* method_ `string ReadName(Frame frame)` — Reads a name from the input stream
- L774-785 _private* method_ `string ReadString(Frame frame)` — Reads a string from the input stream
- L791-795 _private* method_ `int ReadSignedInteger(Frame frame)` — Writes a signed integer value to the output
- L801-806 _private* method_ `ulong ReadUnsignedInteger(Frame frame)` — Read an unsigned integer value from the input
- L813-823 _private* method_ `static int DecodeSignedInteger(ulong value)` — Decode a signed integer using the lower bit for the sign flag, allowing us to encode it more efficiently as a VarInt
- L829-838 _public method_ `public void Disassemble(ILogger logger)` — Disassemble the current script to a logger
- L840-884 _private* method_ `void Disassemble(Frame frame, ILogger logger)`
- L886-889 _private* method_ `int TraceFragment(Frame frame, ILogger logger)`
- L891-900 _private* method_ `T Trace<T>(Frame frame, string? type, Func<Frame, T> readValue, ILogger logger)`
- L902-910 _private* method_ `T Trace<T>(Frame frame, Func<Frame, T> readValue, Func<T, object> formatValue, ILogger logger)`
- L912-916 _private* method_ `void Trace<T>(int offset, int length, object value, ILogger logger)`

#### enum `EpicGames.BuildGraph.BgInterpreter.BgArg`  
`enum BgArg`  
_private*; L59-70_
- L61 _public* enumerator_ `None`
- L62 _public* enumerator_ `Value`
- L63 _public* enumerator_ `ArgList`
- L64 _public* enumerator_ `Fragment`
- L65 _public* enumerator_ `Name`
- L66 _public* enumerator_ `Thunk`
- L67 _public* enumerator_ `StringLiteral`
- L68 _public* enumerator_ `VarIntSigned`
- L69 _public* enumerator_ `VarIntUnsigned`

#### struct `EpicGames.BuildGraph.BgInterpreter.BgOpcodeInfo`  
`readonly struct BgOpcodeInfo`  
_private*; L72-92_
- L74 _private* field_ `readonly uint _data`
- L76 _public ctor_ `public BgOpcodeInfo(BgArg arg1) : this(1, arg1, BgArg.None, BgArg.None)`
- L77 _public ctor_ `public BgOpcodeInfo(BgArg arg1, BgArg arg2) : this(2, arg1, arg2, BgArg.None)`
- L78 _public ctor_ `public BgOpcodeInfo(BgArg arg1, BgArg arg2, BgArg arg3) : this(3, arg1, arg2, arg3)`
- L80-83 _private ctor_ `private BgOpcodeInfo(int count, BgArg arg1, BgArg arg2, BgArg arg3)`
- L85 _public property_ `public int ArgCount => ...`
- L87 _public property_ `public BgArg Arg0 => ...`
- L88 _public property_ `public BgArg Arg1 => ...`
- L89 _public property_ `public BgArg Arg2 => ...`
- L91 _public method_ `public BgArg GetArg(int idx)`

#### class `EpicGames.BuildGraph.BgInterpreter.Frame`  
`class Frame`  
_private*; L94-113_
- L96 _public property_ `public int Offset { get; set; }`
- L97 _public property_ `public IReadOnlyList<object> Arguments { get; }`
- L98 _public property_ `public Dictionary<int, object> Objects { get; set; }`
- L100-105 _public ctor_ `public Frame(Frame other)`
- L107-112 _public ctor_ `public Frame(int offset, IReadOnlyList<object> arguments)`

### `Source/Programs/Shared/EpicGames.BuildGraph/BgLabelDef.cs` (EpicGames.BuildGraph)


#### enum `EpicGames.BuildGraph.BgLabelChange`  
`public enum BgLabelChange`  
_public; L11-22_
- desc: Which changelist to show a UGS badge for
- L16 _public* enumerator_ `Current` — The current changelist being built
- L21 _public* enumerator_ `Code` — The last code changelist

#### class `EpicGames.BuildGraph.BgLabelDef`  
`public class BgLabelDef`  
_public; L28-104_
- desc: Defines a label within a graph. Labels are similar to badges, and give the combined status of one or more job steps. Unlike badges, they separate the requirements for its status and optional nodes to be included in its status, allowing this to be handled externally.
- L33 _public property_ `public string? DashboardName { get; set; }` — Name of this badge
- L38 _public property_ `public string? DashboardCategory { get; set; }` — Category for this label
- L43 _public property_ `public string? UgsBadge { get; set; }` — Name of the badge in UGS
- L48 _public property_ `public string? UgsProject { get; set; }` — Path to the project folder in UGS
- L53 _public property_ `public BgLabelChange Change { get; set; }` — Which change to show the badge for
- L58 _public property_ `public HashSet<BgNodeDef> RequiredNodes { get; }` — Set of nodes that must be run for this label to be shown.
- L63 _public property_ `public HashSet<BgNodeDef> IncludedNodes { get; }` — Set of nodes that will be included in this label if present.
- L68-70 _public ctor_ `public BgLabelDef()` — Constructor
- L80-87 _public ctor_ `public BgLabelDef(string? inDashboardName = null, string? inDashboardCategory = null, string? inUgsBadge = null, string? inUgsProject = null, BgLabelChange inChange = BgLabelChange.Current)` — Constructor
- L93-103 _public method_ `public override string ToString()` — Get the name of this label

### `Source/Programs/Shared/EpicGames.BuildGraph/BgNodeDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgNodeOutput`  
`public class BgNodeOutput`  
_public; L14-45_
- desc: Reference to an output tag from a particular node
- L19 _public property_ `public BgNodeDef ProducingNode { get; }` — The node which produces the given output
- L24 _public property_ `public string TagName { get; }` — Name of the tag
- L31-35 _public ctor_ `public BgNodeOutput(BgNodeDef producingNode, string tagName)` — Constructor
- L41-44 _public method_ `public override string ToString()` — Returns a string representation of this output for debugging purposes

#### class `EpicGames.BuildGraph.BgNodeOutputExprDef`  
`public class BgNodeOutputExprDef`  
_public; L51-89_
- attrs: `[BgObject(typeof(BgNodeOutputExprDefSerializer))]`
- desc: Describes a dependency on a node output
- L56 _public property_ `public BgNodeExpressionDef ProducingNode { get; }` — The producing node
- L61 _public property_ `public int OutputIndex { get; }` — The output index. -1 means all inputs and outputs for the node.
- L68-72 _public ctor_ `public BgNodeOutputExprDef(BgNodeExpressionDef producingNode, int outputIndex)` — Constructor
- L78-88 _public method_ `public IEnumerable<BgNodeOutput> Flatten()` — Flattens this expression to a list of outputs

#### class `EpicGames.BuildGraph.BgNodeOutputExprDefSerializer`  
`class BgNodeOutputExprDefSerializer : BgObjectSerializer<BgNodeOutputExprDef>`  
_internal*; L91-98_
- inherits: `BgObjectSerializer<BgNodeOutputExprDef>`
- L94-97 _public method_ `public override BgNodeOutputExprDef Deserialize(BgObjectDef<BgNodeOutputExprDef> obj)` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgNodeDef`  
`public class BgNodeDef`  
_public; L103-288_
- desc: Defines a node, a container for tasks and the smallest unit of execution that can be run as part of a build graph.
- L108 _public property_ `public string Name { get; }` — The node's name
- L113 _public property_ `public BgThunkDef? Thunk { get; }` — Thunk to execute this node.
- L118 _public property_ `public List<BgNodeOutput> Inputs { get; }` — Array of inputs which this node requires to run
- L123 _public property_ `public List<BgNodeOutput> OptionalInputs { get; }` — Array of inputs which this node is not dependent on to run
- L128 _public property_ `public IReadOnlyList<BgNodeOutput> Outputs { get; }` — Array of outputs produced by this node
- L133 _public property_ `public List<BgNodeDef> InputDependencies { get; }` — Nodes which this node has input dependencies on
- L138 _public property_ `public List<BgNodeDef> OptionalInputDependencies { get; }` — Nodes which this has optional input dependencies on
- L143 _public property_ `public List<BgNodeDef> OrderDependencies { get; }` — Nodes which this node needs to run after
- L148 _public property_ `public List<FileReference> RequiredTokens { get; }` — Tokens which must be acquired for this node to run
- L153 _public property_ `public HashSet<string> NotifyUsers { get; set; }` — List of email addresses to notify if this node fails.
- L158 _public property_ `public HashSet<string> NotifySubmitters { get; set; }` — If set, anyone that has submitted to one of the given paths will be notified on failure of this node
- L163 _public property_ `public bool RunEarly { get; set; }` — Whether to start this node as soon as its dependencies are satisfied, rather than waiting for all of its agent's dependencies to be met.
- L168 _public property_ `public bool AllowRetry { get; set; }` — Whether this node can be retried.
- L173 _public property_ `public bool NotifyOnWarnings { get; set; }` — Whether to ignore warnings produced by this node
- L178 _public property_ `public List<BgAnnotationDef> Annotations { get; }` — Annotations for this node
- L183 _public property_ `public List<string> IgnoreModified { get; set; }` — Ignore modified files matching the patterns provided
- L188 _public property_ `public List<BgDiagnosticDef> Diagnostics { get; }` — Diagnostics to output if executing this node
- L193-204 _public ctor_ `public BgNodeDef(string name, BgThunkDef? thunk, IReadOnlyList<string> outputNames)` — Constructor
- L218-229 _public ctor_ `public BgNodeDef(string name, IReadOnlyList<BgNodeOutput> inputs, IReadOnlyList<BgNodeOutput> optionalInputs, IReadOnlyList<string> outputNames, IReadOnlyList<BgNodeDef> inputDependencies, IReadOnlyList<BgNodeDef> optionalInputDependencies, IReadOnlyList<BgNodeDef> orderDependencies, IReadOnlyList<FileReference> requiredTokens, IReadOnlyList<string> ignoreModified) : this(name, null, outputNames)` — Constructor
- L234 _public property_ `public BgNodeOutput DefaultOutput => ...` — Returns the default output for this node, which includes all build products
- L240-249 _public method_ `public IEnumerable<BgNodeDef> GetDirectInputDependencies()` — Determines the minimal set of direct input dependencies for this node to run
- L255-264 _public method_ `public IEnumerable<BgNodeDef> GetDirectOptionalInputDependencies()` — Determines the minimal set of direct optional input dependencies for this node to run
- L270-278 _public method_ `public IEnumerable<BgNodeDef> GetDirectOrderDependencies()` — Determines the minimal set of direct order dependencies for this node to run
- L284-287 _public method_ `public override string ToString()` — Returns the name of this node

#### class `EpicGames.BuildGraph.BgNodeExpressionDef`  
`public class BgNodeExpressionDef : BgNodeDef`  
_public; L294-340_
- attrs: `[BgObject(typeof(BgNodeExpressionDefSerializer))]`
- inherits: `BgNodeDef`
- desc: Node constructed from a bytecode expression
- L299 _public property_ `public BgAgentDef Agent { get; }` — Agent declaring this node
- L304 _public property_ `public List<BgLabelDef> Labels { get; }` — Labels to add this node to
- L309 _public property_ `public List<BgNodeOutputExprDef> InputExprs { get; }` — Input expressions
- L314 _public property_ `public List<BgNodeOutputExprDef> OptionalInputExprs { get; }` — Optional input expressions
- L319 _public property_ `public List<BgNodeExpressionDef> OrderExprs { get; }` — Order expressions
- L324 _public property_ `public int OutputCount { get; }` — Number of outputs from this node
- L329-334 _public ctor_ `public BgNodeExpressionDef(BgAgentDef agent, string name, BgThunkDef thunk, int outputCount) : base(name, thunk, GetOutputNames(name, outputCount))` — Constructor
- L336-339 _private* method_ `static string[] GetOutputNames(string name, int numOutputs)`

#### class `EpicGames.BuildGraph.BgNodeExpressionDefSerializer`  
`class BgNodeExpressionDefSerializer : BgObjectSerializer<BgNodeExpressionDef>`  
_internal*; L342-378_
- inherits: `BgObjectSerializer<BgNodeExpressionDef>`
- L345-377 _public method_ `public override BgNodeExpressionDef Deserialize(BgObjectDef<BgNodeExpressionDef> obj)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/BgObjectDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgObjectDef`  
`public class BgObjectDef`  
_public; L16-110_
- desc: Value of an object
- L21 _private field_ `private object? _value` — Deserialized object value
- L26 _public property_ `public ImmutableDictionary<string, object?> Properties { get; }` — Properties for the object
- L31-34 _public ctor_ `public BgObjectDef()` — Constructor
- L39-42 _public ctor_ `public BgObjectDef(ImmutableDictionary<string, object?> properties)` — Constructor
- L50-53 _public method_ `public BgObjectDef Set(string name, object? value)` — Sets a property value
- L61-69 _public method_ `public object? Get(string name, object? defaultValue)` — Gets a property value
- L76 _public method_ `public BgObjectDef<T> WithType<T>()` — Creates a strongly typed object instance
- L81 _private* field_ `static readonly ConcurrentDictionary<Type, BgObjectSerializer> s_typeToSerializer = ...` — Cache of serializer instances
- L81 _private* field_ `static readonly ConcurrentDictionary< s_typeToSerializer = new()` — Cache of serializer instances
- L88-102 _public method_ `public object Deserialize(Type type)` — Deserialize an object of the given type, using the default serializer
- L109 _public method_ `public T Deserialize<T>()` — Deserialize an object of the given type

#### class `EpicGames.BuildGraph.BgObjectDef`  
`public class BgObjectDef<T> : BgObjectDef`  
_public; L116-273_
- inherits: `BgObjectDef`
- desc: Strongly typed instance of BgObjectDef
- L161 _private* field_ `static readonly IReadOnlyDictionary<string, PropertySetter> s_nameToSetter = ...`
- L161 _private* field_ `static readonly IReadOnlyDictionary< s_nameToSetter = GetPropertyMap()`
- L166-168 _public ctor_ `public BgObjectDef()` — Constructor
- L173-176 _public ctor_ `public BgObjectDef(ImmutableDictionary<string, object?> properties) : base(properties)` — Constructor
- L185-191 _public method_ `public TValue Get<TValue>(Expression<Func<T, TValue>> property, TValue defaultValue)` — Gets a property value
- L197-206 _public method_ `public void CopyTo(object instance)` — Copies properties from the object value to an instance
- L214-232 _private* method_ `static object? ConvertValue(object? value, Type type)` — Convert a value to a particular type
- L238-255 _private* method_ `static IReadOnlyDictionary<string, PropertySetter> GetPropertyMap()` — Creates a map from name to property info
- L257-272 _private* method_ `static PropertySetter? CreateSetter(PropertyInfo property)`

#### class `EpicGames.BuildGraph.BgObjectDef.PropertySetter`  
`class PropertySetter`  
_private*; L118-125_
- L120 _protected property_ `protected PropertyInfo Property { get; }`
- L122 _public ctor_ `public PropertySetter(PropertyInfo property)`
- L124 _public method_ `public virtual void SetValue(object instance, object? value)`

#### class `EpicGames.BuildGraph.BgObjectDef.CollectionPropertySetter`  
`class CollectionPropertySetter<TElement> : PropertySetter`  
_private*; L127-159_
- inherits: `PropertySetter`
- L129-132 _public ctor_ `public CollectionPropertySetter(PropertyInfo property) : base(property)`
- L134-158 _public method_ `public override void SetValue(object instance, object? value)`

#### class `EpicGames.BuildGraph.BgPropertyAttribute`  
`public sealed class BgPropertyAttribute : Attribute`  
_public; L279-293_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attribute marking that a property should be serialized to BuildGraph
- L284 _public property_ `public string? Name { get; }` — Name of the property. If unspecified, the property name will be used.
- L289-292 _public ctor_ `public BgPropertyAttribute(string? name = null)` — Constructor

#### class `EpicGames.BuildGraph.BgObjectAttribute`  
`public sealed class BgObjectAttribute : Attribute`  
_public; L299-314_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute marking the type of serializer for an object
- L304 _public property_ `public Type SerializerType { get; }` — The serailizer to use for this object
- L310-313 _public ctor_ `public BgObjectAttribute(Type serializerType)` — Constructor

#### class `EpicGames.BuildGraph.BgObjectSerializer`  
`public abstract class BgObjectSerializer`  
_public; L319-327_
- desc: Base class for deserializing objects from untyped BgObjectDef instances
- L326 _public method_ `public abstract object Deserialize(BgObjectDef obj)` — Deserialize an object from the given property bag

#### class `EpicGames.BuildGraph.BgObjectSerializer`  
`public abstract class BgObjectSerializer<T> : BgObjectSerializer`  
_public; L333-344_
- inherits: `BgObjectSerializer`
- desc: Strongly typed base class for deserializing objects
- L336 _public method_ `public sealed override object Deserialize(BgObjectDef obj)` — (inheritdoc)
- L343 _public method_ `public abstract T Deserialize(BgObjectDef<T> obj)` — Typed deserialization method

#### class `EpicGames.BuildGraph.BgDefaultObjectSerializer`  
`public class BgDefaultObjectSerializer<T> : BgObjectSerializer<T> where T : new()`  
_public; L350-359_
- inherits: `BgObjectSerializer<T>`
- constraints: `where T : new()`
- desc: Default serializer for objects with a default constructor
- L353-358 _public method_ `public override T Deserialize(BgObjectDef<T> obj)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/BgOpcode.cs` (EpicGames.BuildGraph)


#### enum `EpicGames.BuildGraph.BgOpcode`  
`public enum BgOpcode`  
_public; L8-326_
- desc: Opcodes for graph expressions. Each opcode is followed by 1-3 operands
- L15 _public* enumerator_ `BoolFalse = 0x00` — Pushes a boolean 'false' value onto the stack
- L20 _public* enumerator_ `BoolTrue = 0x01` — Pushes a boolean 'true' value onto the stack
- L25 _public* enumerator_ `BoolNot = 0x02` — Logical NOT
- L30 _public* enumerator_ `BoolAnd = 0x03` — Logical AND
- L35 _public* enumerator_ `BoolOr = 0x04` — Logical OR
- L40 _public* enumerator_ `BoolXor = 0x05` — Logical XOR
- L45 _public* enumerator_ `BoolEq = 0x06` — Tests whether two boolean values are equal
- L50 _public* enumerator_ `BoolOption = 0x07` — A boolean option
- L55 _public* enumerator_ `BoolToString = 0x08` — Converts a bool to a string
- L64 _public* enumerator_ `IntLiteral = 0x10` — An integer literal. Opcode is followed by a 32-bit little-endian integer.
- L69 _public* enumerator_ `IntEq = 0x11` — Tests whether two integers are equal
- L74 _public* enumerator_ `IntLt = 0x12` — Pops an integer from the stack, tests whether it is less than zero, and pushes a bool onto the stack with the result.
- L79 _public* enumerator_ `IntGt = 0x13` — Pops an integer from the stack, tests whether it is greater than zero, and pushes a bool onto the stack with the result.
- L84 _public* enumerator_ `IntAdd = 0x14` — Adds two integers together
- L89 _public* enumerator_ `IntMultiply = 0x15` — Multiplies two integers
- L94 _public* enumerator_ `IntDivide = 0x16` — Divides one integer by another
- L99 _public* enumerator_ `IntModulo = 0x17` — Computes the modulo of one integer with another
- L104 _public* enumerator_ `IntNegate = 0x18` — Negates an integer
- L109 _public* enumerator_ `IntOption = 0x19` — An integer option between two values (see Expressions.BgIntOption)
- L114 _public* enumerator_ `IntToString = 0x1a` — Converts a bool to a string
- L123 _public* enumerator_ `StrEmpty = 0x20` — An empty string literal
- L128 _public* enumerator_ `StrLiteral = 0x21` — A string literal. Opcode is followed by a UTF-8 encoded string with length.
- L133 _public* enumerator_ `StrCompare = 0x22` — Compares two strings for equality, using a System.StringComparison value encoded into the byte stream as an unsigned EpicGames.Core.VarInt.
- L138 _public* enumerator_ `StrConcat = 0x23` — Concatenates two strings and returns the result
- L143 _public* enumerator_ `StrFormat = 0x24` — Format a string, similar to System.String.Format(System.String, System.Object?[])
- L148 _public* enumerator_ `StrJoin = 0x25` — Joins a list of strings (first argument) with a separator (second argument)
- L153 _public* enumerator_ `StrSplit = 0x26` — Splits a string by a delimiter
- L158 _public* enumerator_ `StrMatch = 0x27` — Tests whether a string (first argument) matches a regular expression (second argument)
- L163 _public* enumerator_ `StrReplace = 0x28` — Returns a string with all ocurrences of the second argument in the first argument replaced with the third argument
- L168 _public* enumerator_ `StrOption = 0x29` — A string option (see Expressions.BgStringOption)
- L177 _public* enumerator_ `EnumConstant = 0x30` — Literal enum value, as an integer.
- L182 _public* enumerator_ `EnumParse = 0x31` — Parses a string as an enum
- L187 _public* enumerator_ `EnumToString = 0x32` — Converts an enum to a string
- L196 _public* enumerator_ `ListEmpty = 0x40` — Creates an empty list
- L201 _public* enumerator_ `ListPush = 0x41` — Adds an item to a list
- L206 _public* enumerator_ `ListPushLazy = 0x42` — Adds a lazily evaluated item to a list
- L211 _public* enumerator_ `ListCount = 0x43` — Gets the length of a list
- L216 _public* enumerator_ `ListElement = 0x44` — Gets the element of a list at an index. Second argument is an integer expression.
- L221 _public* enumerator_ `ListConcat = 0x45` — Concatenates two lists
- L226 _public* enumerator_ `ListUnion = 0x46` — Creates the union of two lists
- L231 _public* enumerator_ `ListExcept = 0x47` — Creates the set excluding another set of items
- L236 _public* enumerator_ `ListSelect = 0x48` — Call a function on each element of a list, returning the transformed list
- L241 _public* enumerator_ `ListWhere = 0x49` — Select elements from a list using a predicate
- L246 _public* enumerator_ `ListDistinct = 0x4a` — Selects all the unique entries in the list. The comparer for the list type is determined by the type of the first element.
- L251 _public* enumerator_ `ListContains = 0x4b` — Determines whether a list contains a particular item
- L256 _public* enumerator_ `ListLazy = 0x4c` — Indicates that the list should only be evaluated when the first item is enumerated from it.
- L261 _public* enumerator_ `ListOption = 0x4d` — An option providing a list of strings (see Expressions.BgListOption
- L270 _public* enumerator_ `ObjEmpty = 0x60` — An empty object
- L275 _public* enumerator_ `ObjGet = 0x61` — Gets the value of a property
- L280 _public* enumerator_ `ObjSet = 0x62` — Sets the value of a property
- L289 _public* enumerator_ `Call = 0xd0` — Takes an operand indicating the number of arguments, and offset of the function to call. Pops the arguments from the evaluation stack, pushes them onto the function stack, and jumps to the given offset.
- L294 _public* enumerator_ `Argument = 0xd1` — Fetches a numbered argument from the functions stack frame.
- L299 _public* enumerator_ `Jump = 0xd2` — Jumps to another fragment without creating a new stack frame
- L308 _public* enumerator_ `Choose = 0xe0` — Chooses between two operands based on a boolean parameter.
- L313 _public* enumerator_ `Throw = 0xe1` — Throws an exception
- L318 _public* enumerator_ `Null = 0xe2` — Null value for an optional expression
- L323 _public* enumerator_ `Thunk = 0xe3` — A native method invocation, represented as an index into the method table

### `Source/Programs/Shared/EpicGames.BuildGraph/BgOptionDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgOptionDef`  
`public abstract class BgOptionDef`  
_public; L11-51_
- desc: Represents a graph option. These are expanded during preprocessing, but are retained in order to display help messages.
- L16 _public property_ `public string Name { get; }` — Name of this option
- L21 _public property_ `public string? Label { get; set; }` — Label for the option in the dashboard
- L26 _public property_ `public string? Description { get; set; }` — Description for this option
- L32-35 _protected ctor_ `protected BgOptionDef(string name)` — Constructor
- L41 _public method_ `public abstract string? GetDefaultArgument()` — Returns the default argument value
- L47-50 _public method_ `public override string ToString()` — Returns a name of this option for debugging

#### class `EpicGames.BuildGraph.BgBoolOptionDef`  
`public class BgBoolOptionDef : BgOptionDef`  
_public; L57-75_
- attrs: `[BgObject(typeof(BgBoolOptionSerializer))]`
- inherits: `BgOptionDef`
- desc: Definition of a boolean option
- L62 _public property_ `public bool DefaultValue { get; set; }` — Default value for the option
- L68-71 _public ctor_ `public BgBoolOptionDef(string name) : base(name)` — Constructor
- L74 _public method_ `public override string? GetDefaultArgument()` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgBoolOptionSerializer`  
`class BgBoolOptionSerializer : BgObjectSerializer<BgBoolOptionDef>`  
_internal*; L80-89_
- inherits: `BgObjectSerializer<BgBoolOptionDef>`
- desc: Serializer for bool options
- L83-88 _public method_ `public override BgBoolOptionDef Deserialize(BgObjectDef<BgBoolOptionDef> obj)` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgIntOptionDef`  
`public class BgIntOptionDef : BgOptionDef`  
_public; L95-123_
- attrs: `[BgObject(typeof(BgIntOptionSerializer))]`
- inherits: `BgOptionDef`
- desc: Definition of an integer option
- L100 _public property_ `public int DefaultValue { get; set; }` — Default value for the option
- L105 _public property_ `public int? MinValue { get; set; }` — Minimum allowed value
- L110 _public property_ `public int? MaxValue { get; set; }` — Maximum allowed value
- L116-119 _public ctor_ `public BgIntOptionDef(string name) : base(name)` — Constructor
- L122 _public method_ `public override string? GetDefaultArgument()` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgIntOptionSerializer`  
`class BgIntOptionSerializer : BgObjectSerializer<BgIntOptionDef>`  
_internal*; L128-137_
- inherits: `BgObjectSerializer<BgIntOptionDef>`
- desc: Serializer for int options
- L131-136 _public method_ `public override BgIntOptionDef Deserialize(BgObjectDef<BgIntOptionDef> obj)` — (inheritdoc)

#### enum `EpicGames.BuildGraph.BgStringOptionStyle`  
`public enum BgStringOptionStyle`  
_public; L142-153_
- desc: Style for a string option
- L147 _public* enumerator_ `Text` — Free-form text entry
- L152 _public* enumerator_ `DropList` — List of options

#### class `EpicGames.BuildGraph.BgStringOptionDef`  
`public class BgStringOptionDef : BgOptionDef`  
_public; L159-202_
- attrs: `[BgObject(typeof(BgStringOptionSerializer))]`
- inherits: `BgOptionDef`
- desc: Definition of a string option
- L164 _public property_ `public string DefaultValue { get; set; }` — Default value for the option
- L169 _public property_ `public BgStringOptionStyle Style { get; }` — Style for this option
- L174 _public property_ `public string? Pattern { get; set; }` — Regex for validating values for the option
- L179 _public property_ `public string? PatternFailed { get; set; }` — Message to display if validation fails
- L184 _public property_ `public List<string>? Values { get; set; }` — List of values to choose from
- L189 _public property_ `public List<string>? ValueDescriptions { get; set; }` — Matching list of descriptions for each value
- L195-198 _public ctor_ `public BgStringOptionDef(string name) : base(name)` — Constructor
- L201 _public method_ `public override string? GetDefaultArgument()` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgStringOptionSerializer`  
`class BgStringOptionSerializer : BgObjectSerializer<BgStringOptionDef>`  
_internal*; L207-216_
- inherits: `BgObjectSerializer<BgStringOptionDef>`
- desc: Serializer for string options
- L210-215 _public method_ `public override BgStringOptionDef Deserialize(BgObjectDef<BgStringOptionDef> obj)` — (inheritdoc)

#### enum `EpicGames.BuildGraph.BgListOptionStyle`  
`public enum BgListOptionStyle`  
_public; L221-232_
- desc: Style for a list option
- L226 _public* enumerator_ `CheckList = 0` — List of checkboxes
- L231 _public* enumerator_ `TagPicker = 1` — Tag picker

#### class `EpicGames.BuildGraph.BgListOptionDef`  
`public class BgListOptionDef : BgOptionDef`  
_public; L238-271_
- attrs: `[BgObject(typeof(BgListOptionSerializer))]`
- inherits: `BgOptionDef`
- desc: A list option definition
- L243 _public property_ `public BgListOptionStyle Style { get; }` — Style for this list box
- L248 _public property_ `public string? DefaultValue { get; set; }` — Default value for the option
- L253 _public property_ `public List<string>? Values { get; set; }` — List of values to choose from
- L258 _public property_ `public List<string>? ValueDescriptions { get; set; }` — Matching list of descriptions for each value
- L264-267 _public ctor_ `public BgListOptionDef(string name) : base(name)` — Constructor
- L270 _public method_ `public override string? GetDefaultArgument()` — (inheritdoc)

#### class `EpicGames.BuildGraph.BgListOptionSerializer`  
`class BgListOptionSerializer : BgObjectSerializer<BgListOptionDef>`  
_internal*; L276-285_
- inherits: `BgObjectSerializer<BgListOptionDef>`
- desc: Serializer for string options
- L279-284 _public method_ `public override BgListOptionDef Deserialize(BgObjectDef<BgListOptionDef> obj)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/BgReport.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgReport`  
`public class BgReport`  
_public; L11-45_
- desc: Defines a report to be generated as part of the build.
- L16 _public property_ `public string Name { get; }` — Name of this trigger
- L21 _public property_ `public HashSet<BgNodeDef> Nodes { get; }` — Set of nodes to include in the report
- L26 _public property_ `public HashSet<string> NotifyUsers { get; }` — List of users to notify with this report
- L32-35 _public ctor_ `public BgReport(string inName)` — Constructor
- L41-44 _public method_ `public override string ToString()` — Get the name of this report

### `Source/Programs/Shared/EpicGames.BuildGraph/BgThunkDef.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.BgThunkDef`  
`public class BgThunkDef`  
_public; L11-31_
- desc: Information about the method bound to execute a node
- L16 _public property_ `public MethodInfo Method { get; }` — Method to call
- L21 _public property_ `public IReadOnlyList<object?> Arguments { get; }` — Arguments to the method
- L26-30 _public ctor_ `public BgThunkDef(MethodInfo method, IReadOnlyList<object?> arguments)` — Constructor

#### class `EpicGames.BuildGraph.BgThunkOutputDef`  
`public class BgThunkOutputDef`  
_public; L36-58_
- desc: Outputs from a thunk
- L41 _public property_ `public BgThunkDef Thunk { get; }` — The thunk definition
- L46 _public property_ `public int Index { get; }` — Output index from the thunk
- L53-57 _public ctor_ `public BgThunkOutputDef(BgThunkDef thunk, int index)` — Constructor

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgAgent.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgAgent`  
`public class BgAgent : BgExpr`  
_public; L8-49_
- inherits: `BgExpr`
- desc: Describes an agent that can execute execute build steps
- L13 _public property_ `public BgString Name { get; }` — Name of the agent
- L18 _public property_ `public BgList<BgString> Types { get; set; }` — List of agent types to select from, in order of preference. The first agent type supported by a stream will be used.
- L23-26 _public ctor_ `public BgAgent(BgString name, BgString type) : this(name, BgList.Create(type))` — Constructor
- L31-36 _public ctor_ `public BgAgent(BgString name, BgList<BgString> types) : base(BgExprFlags.ForceFragment)` — Constructor
- L39-45 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L48 _public method_ `public override BgString ToBgString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgAggregate.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgAggregate`  
`public class BgAggregate : BgExpr`  
_public; L8-75_
- inherits: `BgExpr`
- desc: Specification for an aggregate target in the graph
- L13 _public property_ `public BgString Name { get; }` — Name of the aggregate
- L18 _public property_ `public BgList<BgNode> Requires { get; }` — Outputs required for the aggregate
- L23 _public property_ `public BgLabel? Label { get; }` — Label to apply to this aggregate
- L28-31 _public ctor_ `public BgAggregate(BgString name, params BgNode[] requires) : this(name, BgList.Create(requires))` — Constructor.
- L36-39 _public ctor_ `public BgAggregate(BgString name, params BgList<BgNode>[] requires) : this(name, BgList.Concat(requires))` — Constructor.
- L44-47 _public ctor_ `public BgAggregate(BgString name, BgList<BgNode> requires, string label) : this(name, requires, new BgLabel(label))` — Constructor.
- L52-58 _public ctor_ `public BgAggregate(BgString name, BgList<BgNode> requires, BgLabel? label = null) : base(BgExprFlags.None)` — Constructor.
- L61-71 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L74 _public method_ `public override BgString ToBgString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgAnnotation.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgAnnotation`  
`public class BgAnnotation : BgExpr`  
_public; L8-39_
- inherits: `BgExpr`
- desc: Specification for a annotation
- L13 _public property_ `public BgString Name { get; }` — Name, or key, of the annotation
- L18 _public property_ `public BgString Value { get; }` — Value to be paired with the annotation name
- L21-26 _public ctor_ `public BgAnnotation(BgString name, BgString value) : base(BgExprFlags.ForceFragment)` — (inheritdoc)
- L29-35 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L38 _public method_ `public override BgString ToBgString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgBool.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgBool`  
`public abstract class BgBool : BgExpr`  
_public; L11-66_
- attrs: `[BgType(typeof(BgBoolType))]`
- inherits: `BgExpr`
- desc: Abstract base class for expressions returning a boolean value
- L16 _public property_ `public static BgBool False { get; }` — Constant value for false
- L21 _public property_ `public static BgBool True { get; }` — Constant value for true
- L27-30 _protected ctor_ `protected BgBool(BgExprFlags flags) : base(flags)` — Constructor
- L35-38 _public operator_ `public static implicit operator BgBool(bool value)` — Implict conversion operator from a boolean literal
- L41 _public operator_ `public static BgBool operator !(BgBool inner)` — (inheritdoc)
- L44 _public operator_ `public static BgBool operator &(BgBool lhs, BgBool rhs)` — (inheritdoc)
- L47 _public operator_ `public static BgBool operator |(BgBool lhs, BgBool rhs)` — (inheritdoc)
- L50 _public operator_ `public static BgBool operator ^(BgBool lhs, BgBool rhs)` — (inheritdoc)
- L53 _public operator_ `public static BgBool operator ==(BgBool lhs, BgBool rhs)` — (inheritdoc)
- L56 _public operator_ `public static BgBool operator !=(BgBool lhs, BgBool rhs)` — (inheritdoc)
- L59 _public method_ `public sealed override bool Equals(object? obj)` — (inheritdoc)
- L62 _public method_ `public sealed override int GetHashCode()` — (inheritdoc)
- L65 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgBoolType`  
`class BgBoolType : BgType<BgBool>`  
_internal*; L71-78_
- inherits: `BgType<BgBool>`
- desc: Type traits for a BgBool
- L74 _public method_ `public override BgBool Constant(object value)` — (inheritdoc)
- L77 _public method_ `public override BgBool Wrap(BgExpr expr)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgBoolNotExpr`  
`class BgBoolNotExpr : BgBool`  
_internal*; L82-97_
- inherits: `BgBool`
- L84 _public property_ `public BgBool Inner { get; }`
- L86-90 _public ctor_ `public BgBoolNotExpr(BgBool inner) : base(inner.Flags & BgExprFlags.Eager)`
- L92-96 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgBoolBinaryExpr`  
`class BgBoolBinaryExpr : BgBool`  
_internal*; L99-119_
- inherits: `BgBool`
- L101 _public property_ `public BgOpcode Opcode { get; }`
- L102 _public property_ `public BgBool Lhs { get; }`
- L103 _public property_ `public BgBool Rhs { get; }`
- L105-111 _public ctor_ `public BgBoolBinaryExpr(BgOpcode opcode, BgBool lhs, BgBool rhs) : base(lhs.Flags & rhs.Flags & BgExprFlags.Eager)`
- L113-118 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgBoolConstantExpr`  
`class BgBoolConstantExpr : BgBool`  
_internal*; L121-132_
- inherits: `BgBool`
- L123 _public property_ `public bool Value { get; }`
- L125-129 _public ctor_ `public BgBoolConstantExpr(bool value) : base(BgExprFlags.NotInterned | BgExprFlags.Eager)`
- L131 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgBoolWrappedExpr`  
`class BgBoolWrappedExpr : BgBool`  
_internal*; L134-145_
- inherits: `BgBool`
- L136 _public property_ `public BgExpr Expr { get; }`
- L138-142 _public ctor_ `public BgBoolWrappedExpr(BgExpr expr) : base(expr.Flags)`
- L144 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgBoolToBgStringExpr`  
`class BgBoolToBgStringExpr : BgString`  
_internal*; L147-162_
- inherits: `BgString`
- L149 _public property_ `public BgExpr Expr { get; }`
- L151-155 _public ctor_ `public BgBoolToBgStringExpr(BgExpr expr) : base(expr.Flags & BgExprFlags.Eager)`
- L157-161 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgBoolOption`  
`public class BgBoolOption : BgBool`  
_public; L169-236_
- inherits: `BgBool`
- desc: A boolean option expression
- L174 _public property_ `public BgString Name { get; }` — Name of the option
- L179 _public property_ `public BgString? Label { get; }` — Label to display next to the option
- L184 _public property_ `public BgString? Description { get; }` — Help text to display for the user
- L189 _public property_ `public BgBool? DefaultValue { get; }` — Default value for the option
- L194-197 _public ctor_ `public BgBoolOption(BgString name, BgString? description = null, BgBool? defaultValue = null) : this(name, null, description, defaultValue)` — Constructor
- L202-209 _public ctor_ `public BgBoolOption(BgString name, BgString? label, BgString? description, BgBool? defaultValue) : base(BgExprFlags.None)` — Constructor
- L212-216 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L218-235 _private* method_ `BgObject<BgBoolOptionDef> CreateOptionsObject()`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgEnum.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgEnum`  
`public abstract class BgEnum<TEnum> : BgExpr where TEnum : struct`  
_public; L12-53_
- attrs: `[BgType(typeof(BgEnumType<>))]`
- inherits: `BgExpr`
- constraints: `where TEnum : struct`
- desc: Abstract base class for expressions returning a string value
- L15 _public property_ `public Type EnumType => ...` — (inheritdoc)
- L20 _public property_ `public static BgList<BgString> Names { get; }` — Names of this enum
- L25 _public property_ `public static BgList<BgInt> Values { get; }` — Values of this enum
- L30-33 _protected ctor_ `protected BgEnum(BgExprFlags flags) : base(flags)` — Constructor
- L38-41 _public operator_ `public static implicit operator BgEnum<TEnum>(TEnum value)` — Implicit conversion from a regular enum type
- L46-49 _public method_ `public static BgEnum<TEnum> Parse(BgString value)` — Explicit conversion from a string value
- L52 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgEnumType`  
`class BgEnumType<TEnum> : BgType<BgEnum<TEnum>> where TEnum : struct`  
_internal*; L58-71_
- inherits: `BgType<BgEnum<TEnum>>`
- constraints: `where TEnum : struct`
- desc: Type traits for a BgEnum{TEnum}
- L61-64 _public method_ `public override BgEnum<TEnum> Constant(object value)` — (inheritdoc)
- L67-70 _public method_ `public override BgEnum<TEnum> Wrap(BgExpr expr)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgEnumConstantExpr`  
`class BgEnumConstantExpr<TEnum> : BgEnum<TEnum> where TEnum : struct`  
_internal*; L75-90_
- inherits: `BgEnum<TEnum>`
- constraints: `where TEnum : struct`
- L77 _public property_ `public TEnum Value { get; }`
- L79-83 _public ctor_ `public BgEnumConstantExpr(TEnum value) : base(BgExprFlags.NotInterned | BgExprFlags.Eager)`
- L85-89 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgEnumParseExpr`  
`class BgEnumParseExpr<TEnum> : BgEnum<TEnum> where TEnum : struct`  
_internal*; L92-109_
- inherits: `BgEnum<TEnum>`
- constraints: `where TEnum : struct`
- L94 _public property_ `public BgString Value { get; }`
- L96-100 _public ctor_ `public BgEnumParseExpr(BgString value) : base(value.Flags & BgExprFlags.Eager)`
- L102-108 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgEnumToStringExpr`  
`class BgEnumToStringExpr<TEnum> : BgString where TEnum : struct`  
_internal*; L111-128_
- inherits: `BgString`
- constraints: `where TEnum : struct`
- L113 _public property_ `public BgEnum<TEnum> Expr { get; }`
- L115-119 _public ctor_ `public BgEnumToStringExpr(BgEnum<TEnum> expr) : base(expr.Flags & BgExprFlags.Eager)`
- L121-127 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgEnumWrappedExpr`  
`class BgEnumWrappedExpr<TEnum> : BgEnum<TEnum> where TEnum : struct`  
_internal*; L130-144_
- inherits: `BgEnum<TEnum>`
- constraints: `where TEnum : struct`
- L132 _public property_ `public BgExpr Expr { get; }`
- L134-138 _public ctor_ `public BgEnumWrappedExpr(BgExpr expr) : base(expr.Flags)`
- L140-143 _public method_ `public override void Write(BgBytecodeWriter writer)`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgExpr.cs` (EpicGames.BuildGraph)


#### enum `EpicGames.BuildGraph.BgExprFlags`  
`public enum BgExprFlags`  
_public; L13-35_
- attrs: `[Flags]`
- desc: Flags for an expression
- L18 _public* enumerator_ `None = 0` — No flags set
- L24 _public* enumerator_ `NotInterned = 1` — Indicates that the expression should never be interned (ie. encoded to a separate fragment), and will always be duplicated in the bytecode. Trivial constants with short encodings typically have this flag set.
- L29 _public* enumerator_ `Eager = 2` — Always eagerly evaluate this expression
- L34 _public* enumerator_ `ForceFragment = 4` — Force this expression to be stored in a separate fragment. Can help improves readability of the disassembly output.

#### class `EpicGames.BuildGraph.BgExpr`  
`public abstract class BgExpr`  
_public; L40-96_
- desc: Base class for computable expressions
- L45 _public property_ `public static BgExpr Null { get; }` — Null value
- L50 _public property_ `public BgExprFlags Flags { get; }` — Flags for this expression
- L56-59 _protected ctor_ `protected BgExpr(BgExprFlags flags)` — Constructor
- L68-71 _public method_ `public static T Throw<T>(BgString message, [CallerFilePath] string sourcePath = "", [CallerLineNumber] int sourceLine = 0) where T : BgExpr` — Throws an exception
- L81-84 _public method_ `public static T Choose<T>(BgBool condition, T valueIfTrue, T valueIfFalse) where T : BgExpr` — Chooses between two values based on a condition
- L90 _public method_ `public abstract void Write(BgBytecodeWriter writer)` — Serialize the expression to an output stream
- L95 _public method_ `public abstract BgString ToBgString()` — Convert the value of the expression to a string

#### class `EpicGames.BuildGraph.BgChooseExpr`  
`class BgChooseExpr<T> : BgExpr where T : BgExpr`  
_internal*; L98-121_
- inherits: `BgExpr`
- constraints: `where T : BgExpr`
- L100 _public property_ `public BgBool Condition { get; }`
- L101 _public property_ `public T ValueIfTrue { get; }`
- L102 _public property_ `public T ValueIfFalse { get; }`
- L104-110 _public ctor_ `public BgChooseExpr(BgBool condition, T valueIfTrue, T valueIfFalse) : base(BgExprFlags.None)`
- L112-118 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L120 _public method_ `public override BgString ToBgString()`

#### class `EpicGames.BuildGraph.BgThrowExpr`  
`class BgThrowExpr : BgExpr`  
_internal*; L123-146_
- inherits: `BgExpr`
- L125 _public property_ `public string SourcePath { get; }`
- L126 _public property_ `public int SourceLine { get; }`
- L127 _public property_ `public BgString Message { get; }`
- L129-135 _public ctor_ `public BgThrowExpr(string sourcePath, int sourceLine, BgString message) : base(BgExprFlags.None)`
- L137-143 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L145 _public method_ `public override BgString ToBgString()`

#### class `EpicGames.BuildGraph.BgNullExpr`  
`class BgNullExpr : BgExpr`  
_internal*; L148-161_
- inherits: `BgExpr`
- L150-153 _public ctor_ `public BgNullExpr() : base(BgExprFlags.NotInterned)`
- L155-158 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L160 _public method_ `public override BgString ToBgString()`

#### class `EpicGames.BuildGraph.BgExprExtensions`  
`public static class BgExprExtensions`  
_public; L166-193_
- desc: Extension methods for expressions
- L176-179 _public method_ `public static T If<T>(this T expr, BgBool condition, T value) where T : BgExpr` — Chose an expression if a condition evaluates to true
- L189-192 _public method_ `public static T If<T>(this T expr, BgBool condition, Func<T, T> func) where T : BgExpr` — Chose an expression if a condition evaluates to true

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgFileSet.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgFileSet`  
`public abstract class BgFileSet : BgExpr`  
_public; L13-40_
- attrs: `[BgType(typeof(BgFileSetType))]`
- inherits: `BgExpr`
- desc: Represents a placeholder for the output from a node, which can be exchanged for the artifacts produced by a node at runtime
- L18 _public property_ `public static BgFileSet Empty { get; }` — Constant empty fileset
- L24-27 _protected ctor_ `protected BgFileSet(BgExprFlags flags) : base(flags)` — Constructor
- L33-36 _public operator_ `public static implicit operator BgFileSet(FileSet fileSet)` — Implicit conversion from a regular fileset
- L39 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgFileSetType`  
`class BgFileSetType : BgType<BgFileSet>`  
_internal*; L45-57_
- inherits: `BgType<BgFileSet>`
- desc: Traits for a BgFileSet
- L48-53 _public method_ `public override BgFileSet Constant(object value)` — (inheritdoc)
- L56 _public method_ `public override BgFileSet Wrap(BgExpr expr)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgFileSetInputExpr`  
`class BgFileSetInputExpr : BgFileSet`  
_internal*; L61-75_
- inherits: `BgFileSet`
- L63 _public property_ `public IReadOnlyList<BgNodeOutput> Outputs { get; }`
- L65-69 _public ctor_ `public BgFileSetInputExpr(BgNodeOutput[] outputs) : base(BgExprFlags.None)`
- L71-74 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgFileSetOutputExpr`  
`public class BgFileSetOutputExpr : BgFileSet`  
_public; L80-102_
- inherits: `BgFileSet`
- desc: /
- L85 _public property_ `public FileSet Value { get; }`
- L91-95 _public ctor_ `public BgFileSetOutputExpr(FileSet value) : base(BgExprFlags.NotInterned)`
- L98-101 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgFileSetFromNodeExpr`  
`class BgFileSetFromNodeExpr : BgFileSet`  
_internal*; L104-120_
- inherits: `BgFileSet`
- L106 _public property_ `public BgNode Node { get; }`
- L108-112 _public ctor_ `public BgFileSetFromNodeExpr(BgNode node) : base(BgExprFlags.NotInterned)`
- L114-119 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgFileSetFromNodeOutputExpr`  
`class BgFileSetFromNodeOutputExpr : BgFileSet`  
_internal*; L122-141_
- inherits: `BgFileSet`
- L124 _public property_ `public BgNode Node { get; }`
- L125 _public property_ `public int OutputIndex { get; }`
- L127-132 _public ctor_ `public BgFileSetFromNodeOutputExpr(BgNode node, int outputIndex) : base(BgExprFlags.NotInterned)`
- L134-140 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgFileSetWrappedExpr`  
`class BgFileSetWrappedExpr : BgFileSet`  
_internal*; L143-154_
- inherits: `BgFileSet`
- L145 _public property_ `public BgExpr Expr { get; }`
- L147-151 _public ctor_ `public BgFileSetWrappedExpr(BgExpr expr) : base(expr.Flags)`
- L153 _public method_ `public override void Write(BgBytecodeWriter writer)`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgFunc.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgFunc`  
`public abstract class BgFunc`  
_public; L10-27_
- desc: Abstract base class for function expressions
- L15 _public property_ `public BgExpr Body { get; }` — The function expression.
- L21-26 _protected ctor_ `protected BgFunc(BgExpr body)` — Constructor

#### class `EpicGames.BuildGraph.Expressions.BgFunc`  
`public class BgFunc<TResult> : BgFunc where TResult : BgExpr`  
_public; L33-55_
- inherits: `BgFunc`
- constraints: `where TResult : BgExpr`
- desc: A function taking no arguments
- L40-43 _public ctor_ `public BgFunc(Func<TResult> func) : base(func())` — Constructor
- L48 _public operator_ `public static implicit operator BgFunc<TResult>(Func<TResult> func)` — Implicit conversion from a regular C# function
- L54 _public method_ `public TResult Call()` — Call the function with the given arguments

#### class `EpicGames.BuildGraph.Expressions.BgFunc`  
`public class BgFunc<TArg, TResult> : BgFunc where TArg : BgExpr where TResult : BgExpr`  
_public; L62-86_
- inherits: `BgFunc`
- constraints: `where TArg : BgExpr where TResult : BgExpr`
- desc: A function taking a single argument
- L70-73 _public ctor_ `public BgFunc(Func<TArg, TResult> func) : base(func(BgType.Wrap<TArg>(new BgFuncArgumentExpr(0))))` — Constructor
- L78 _public operator_ `public static implicit operator BgFunc<TArg, TResult>(Func<TArg, TResult> func)` — Implicit conversion from a regular C# function
- L85 _public method_ `public TResult Call(TArg arg)` — Call the function with the given arguments

#### class `EpicGames.BuildGraph.Expressions.BgFunc`  
`public class BgFunc<TArg1, TArg2, TResult> : BgFunc where TArg1 : BgExpr where TArg2 : BgExpr where TResult : BgExpr`  
_public; L94-120_
- inherits: `BgFunc`
- constraints: `where TArg1 : BgExpr where TArg2 : BgExpr where TResult : BgExpr`
- desc: A function taking two arguments
- L103-106 _public ctor_ `public BgFunc(Func<TArg1, TArg2, TResult> func) : base(func(BgType.Wrap<TArg1>(new BgFuncArgumentExpr(0)), BgType.Wrap<TArg2>(new BgFuncArgumentExpr(1))))` — Constructor
- L111 _public operator_ `public static implicit operator BgFunc<TArg1, TArg2, TResult>(Func<TArg1, TArg2, TResult> func)` — Implicit conversion from a regular C# function
- L119 _public method_ `public TResult Call(TArg1 arg1, TArg2 arg2)` — Call the function with the given arguments

#### class `EpicGames.BuildGraph.Expressions.BgFuncArgumentExpr`  
`class BgFuncArgumentExpr : BgExpr`  
_internal*; L124-141_
- inherits: `BgExpr`
- L126 _private* property_ `uint Index { get; }`
- L128-132 _public ctor_ `public BgFuncArgumentExpr(uint index) : base(BgExprFlags.NotInterned)`
- L134-138 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L140 _public method_ `public override BgString ToBgString()`

#### class `EpicGames.BuildGraph.Expressions.BgFuncCallExpr`  
`class BgFuncCallExpr<T> : BgExpr where T : BgExpr`  
_internal*; L143-167_
- inherits: `BgExpr`
- constraints: `where T : BgExpr`
- L145 _private* field_ `readonly BgFunc _function`
- L146 _private* field_ `readonly BgExpr[] _arguments`
- L148-153 _public ctor_ `public BgFuncCallExpr(BgFunc function, params BgExpr[] arguments) : base(BgExprFlags.None)`
- L155-164 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L166 _public method_ `public override BgString ToBgString()`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgGraph.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgGraph`  
`public class BgGraph : BgExpr`  
_public; L8-73_
- inherits: `BgExpr`
- desc: Specification for a graph in fluent syntax
- L13 _public property_ `public BgList<BgNode> Nodes { get; }` — Nodes for the graph
- L18 _public property_ `public BgList<BgAggregate> Aggregates { get; }` — Aggregates for the graph
- L23-28 _public ctor_ `public BgGraph(BgList<BgNode> nodes, BgList<BgAggregate> aggregates) : base(BgExprFlags.ForceFragment)` — Constructor
- L33-36 _public operator_ `public static implicit operator BgGraph(BgNode node)` — Implicit conversion from a node spec
- L41-44 _public operator_ `public static implicit operator BgGraph(BgList<BgNode> nodes)` — Implicit conversion from a list of node specs
- L49-52 _public operator_ `public static implicit operator BgGraph(BgAggregate aggregate)` — Implicit conversion from an aggregate spec
- L57-60 _public operator_ `public static implicit operator BgGraph(BgList<BgAggregate> aggregates)` — Implicit conversion from a list of node specs
- L63-69 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L72 _public method_ `public override BgString ToBgString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgInt.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgInt`  
`public abstract class BgInt : BgExpr`  
_public; L11-77_
- attrs: `[BgType(typeof(BgIntType))]`
- inherits: `BgExpr`
- desc: Abstract base class for expressions returning a 32-bit integer value
- L16-19 _public operator_ `public static implicit operator BgInt(int value)` — Implicit conversion from an integer value
- L25-28 _protected ctor_ `protected BgInt(BgExprFlags flags) : base(flags)` — Constructor
- L31 _public operator_ `public static BgInt operator -(BgInt value)` — (inheritdoc)
- L34 _public operator_ `public static BgInt operator +(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L37 _public operator_ `public static BgInt operator -(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L40 _public operator_ `public static BgInt operator *(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L43 _public operator_ `public static BgInt operator /(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L46 _public operator_ `public static BgInt operator %(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L49 _public operator_ `public static BgBool operator <(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L52 _public operator_ `public static BgBool operator >(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L55 _public operator_ `public static BgBool operator ==(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L58 _public operator_ `public static BgBool operator !=(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L61 _public operator_ `public static BgBool operator <=(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L64 _public operator_ `public static BgBool operator >=(BgInt lhs, BgInt rhs)` — (inheritdoc)
- L67 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L70 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L73-76 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgIntType`  
`class BgIntType : BgType<BgInt>`  
_internal*; L82-89_
- inherits: `BgType<BgInt>`
- desc: Traits for a BgInt
- L85 _public method_ `public override BgInt Constant(object value)` — (inheritdoc)
- L88 _public method_ `public override BgInt Wrap(BgExpr expr)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgIntUnaryExpr`  
`class BgIntUnaryExpr : BgInt`  
_internal*; L93-110_
- inherits: `BgInt`
- L95 _public property_ `public BgOpcode Opcode { get; }`
- L96 _public property_ `public BgInt Value { get; }`
- L98-103 _public ctor_ `public BgIntUnaryExpr(BgOpcode opcode, BgInt value) : base(value.Flags & BgExprFlags.Eager)`
- L105-109 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgIntBinaryExpr`  
`class BgIntBinaryExpr : BgInt`  
_internal*; L112-132_
- inherits: `BgInt`
- L114 _public property_ `public BgOpcode Opcode { get; }`
- L115 _public property_ `public BgInt Lhs { get; }`
- L116 _public property_ `public BgInt Rhs { get; }`
- L118-124 _public ctor_ `public BgIntBinaryExpr(BgOpcode opcode, BgInt lhs, BgInt rhs) : base(lhs.Flags & rhs.Flags & BgExprFlags.Eager)`
- L126-131 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgIntTestExpr`  
`class BgIntTestExpr : BgBool`  
_internal*; L134-154_
- inherits: `BgBool`
- L136 _public property_ `public BgOpcode Opcode { get; }`
- L137 _public property_ `public BgInt Lhs { get; }`
- L138 _public property_ `public BgInt Rhs { get; }`
- L140-146 _public ctor_ `public BgIntTestExpr(BgOpcode opcode, BgInt lhs, BgInt rhs) : base(lhs.Flags & rhs.Flags & BgExprFlags.Eager)`
- L148-153 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgIntChooseExpr`  
`class BgIntChooseExpr : BgInt`  
_internal*; L156-177_
- inherits: `BgInt`
- L158 _public property_ `public BgBool Condition { get; }`
- L159 _public property_ `public BgInt ValueIfTrue { get; }`
- L160 _public property_ `public BgInt ValueIfFalse { get; }`
- L162-168 _public ctor_ `public BgIntChooseExpr(BgBool condition, BgInt valueIfTrue, BgInt valueIfFalse) : base(BgExprFlags.None)`
- L170-176 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgIntConstantExpr`  
`class BgIntConstantExpr : BgInt`  
_internal*; L179-194_
- inherits: `BgInt`
- L181 _public property_ `public int Value { get; }`
- L183-187 _public ctor_ `public BgIntConstantExpr(int value) : base(BgExprFlags.NotInterned | BgExprFlags.Eager)`
- L189-193 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgIntWrappedExpr`  
`class BgIntWrappedExpr : BgInt`  
_internal*; L196-207_
- inherits: `BgInt`
- L198 _private* property_ `BgExpr Expr { get; }`
- L200-204 _public ctor_ `public BgIntWrappedExpr(BgExpr expr) : base(expr.Flags)`
- L206 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgIntToBgStringExpr`  
`class BgIntToBgStringExpr : BgString`  
_internal*; L209-224_
- inherits: `BgString`
- L211 _private* property_ `BgInt Expr { get; }`
- L213-217 _public ctor_ `public BgIntToBgStringExpr(BgInt expr) : base(expr.Flags & BgExprFlags.Eager)`
- L219-223 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgIntOption`  
`public class BgIntOption : BgInt`  
_public; L231-310_
- inherits: `BgInt`
- desc: An integer option expression
- L236 _public property_ `public BgString Name { get; }` — Name of the option
- L241 _public property_ `public BgString? Label { get; }` — Label to display next to the option
- L246 _public property_ `public BgString? Description { get; }` — Help text to display for the user
- L251 _public property_ `public BgInt? DefaultValue { get; }` — Default value for the option
- L256 _public property_ `public BgInt? MinValue { get; }` — Minimum allowed value
- L261 _public property_ `public BgInt? MaxValue { get; }` — Maximum allowed value
- L266-275 _public ctor_ `public BgIntOption(string name, BgString? description = null, BgInt? defaultValue = null, BgInt? minValue = null, BgInt? maxValue = null, BgString? label = null) : base(BgExprFlags.None)` — Constructor
- L278-282 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L284-309 _private* method_ `BgObject<BgIntOptionDef> CreateOptionsObject()`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgLabel.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgLabel`  
`public class BgLabel : BgExpr`  
_public; L8-77_
- inherits: `BgExpr`
- desc: Specification for a label
- L13 _public property_ `public BgString? DashboardName { get; }` — Name of this badge
- L18 _public property_ `public BgString? DashboardCategory { get; }` — Category for this label
- L23 _public property_ `public BgString? UgsBadge { get; }` — Name of the badge in UGS
- L28 _public property_ `public BgString? UgsProject { get; }` — Path to the project folder in UGS
- L33 _public property_ `public BgEnum<BgLabelChange>? Change { get; }` — Which change to show the badge for
- L38-46 _public ctor_ `public BgLabel(BgString? name = null, BgString? category = null, BgString? ugsBadge = null, BgString? ugsProject = null, BgEnum<BgLabelChange>? change = null) : base(BgExprFlags.ForceFragment)` — Constructor
- L49-73 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L76 _public method_ `public override BgString ToBgString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgList.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgList`  
`public static class BgList`  
_public; L13-64_
- desc: Utility methods for lists
- L20 _public method_ `public static BgList<T> Empty<T>() where T : BgExpr` — Gets an empty list of the given type
- L27 _public method_ `public static BgList<BgString> Create(IEnumerable<string> items)` — Crates a list from an array of values
- L34 _public method_ `public static BgList<BgString> Create(params string[] items)` — Crates a list from an array of values
- L41 _public method_ `public static BgList<T> Create<T>(IEnumerable<T> items) where T : BgExpr` — Crates a list from an array of values
- L48 _public method_ `public static BgList<T> Create<T>(params T[] items) where T : BgExpr` — Crates a list from an array of values
- L56 _public method_ `public static BgList<T> Concat<T>(BgList<T> lhs, BgList<T> rhs) where T : BgExpr` — Concatenates two lists together
- L63 _public method_ `public static BgList<T> Concat<T>(params BgList<T>[] others) where T : BgExpr` — Concatenates two lists together

#### class `EpicGames.BuildGraph.Expressions.BgList`  
`public abstract class BgList<T> : BgExpr where T : BgExpr`  
_public; L70-226_
- attrs: `[BgType(typeof(BgListType<>))]`
- inherits: `BgExpr`
- constraints: `where T : BgExpr`
- desc: Abstract base class for expressions returning an immutable list of values
- L74 _public property_ `public Type ElementType => ...` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — (inheritdoc)
- L80 _public property_ `public static BgList<T> Empty { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — Constant representation of an empty list
- L86-89 _protected ctor_ `protected BgList(BgExprFlags flags) : base(flags)` — Constructor
- L92 _public indexer_ `public T this[BgInt index]` — (inheritdoc)
- L97 _public operator_ `public static implicit operator BgList<T>(T item)` — Implicit conversion operator from a single value
- L102 _public operator_ `public static implicit operator BgList<T>(T[] items)` — Implicit conversion operator from an array of values
- L107 _public operator_ `public static implicit operator BgList<T>(List<T> items)` — Implicit conversion operator from a list of values
- L114 _public method_ `public static BgList<T> Create(IEnumerable<T> items)` — Crates a list from an array of values
- L121 _public method_ `public static BgList<T> Create(params T[] items)` — Crates a list from an array of values
- L129 _public method_ `public static BgList<T> Concat(BgList<T> lhs, BgList<T> rhs)` — Concatenates two lists together
- L136-144 _public method_ `public static BgList<T> Concat(params BgList<T>[] others)` — Concatenates two lists together
- L150 _public property_ `public BgInt Count => ...` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — Gets the length of this list
- L157 _public method_ `public BgList<T> Add(T item)` — Adds an item to the end of the list, returning the new list
- L164 _public method_ `public BgList<T> Add(params T[] items)` — Adds items to the end of the list, returning the new list
- L167 _public method_ `public BgList<T> Add(BgList<T> list)` — (inheritdoc)
- L170-178 _public method_ `public BgList<T> Add(IEnumerable<T> items)` — (inheritdoc)
- L181 _public method_ `public BgList<T> Union(params T[] items)` — (inheritdoc)
- L184 _public method_ `public BgList<T> Union(IEnumerable<T> items)` — (inheritdoc)
- L191 _public method_ `public BgList<T> Union(BgList<T> items)` — Creates the union of this list with another
- L198 _public method_ `public BgList<T> Except(BgList<T> items)` — Removes the given items from this list
- L204 _public method_ `public BgList<T> Distinct()` — Removes any duplicate items from the list. The first item in the list is retained in its original order.
- L207 _public method_ `public BgList<TResult> Select<TResult>(Func<T, TResult> function) where TResult : BgExpr` — (inheritdoc)
- L210 _public method_ `public BgList<TResult> Select<TResult>(BgFunc<T, TResult> function) where TResult : BgExpr` — (inheritdoc)
- L213 _public method_ `public BgList<T> Where(Func<T, BgBool> predicate)` — (inheritdoc)
- L216 _public method_ `public BgBool Contains(T item)` — (inheritdoc)
- L222 _public method_ `public BgList<T> Lazy()` — Creates a lazily evaluated copy of this list, if it's not constant
- L225 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgListType`  
`class BgListType<T> : BgType<BgList<T>> where T : BgExpr`  
_internal*; L231-250_
- inherits: `BgType<BgList<T>>`
- constraints: `where T : BgExpr`
- desc: Traits for a BgList{T}
- L234-245 _public method_ `public override BgList<T> Constant(object value)` — (inheritdoc)
- L249 _public method_ `public override BgList<T> Wrap(BgExpr expr)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgListEmptyExpr`  
`class BgListEmptyExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L254-265_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L256-259 _public ctor_ `public BgListEmptyExpr() : base(BgExprFlags.NotInterned)`
- L261-264 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListConstantExpr`  
`class BgListConstantExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L267-281_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L269 _public property_ `public IReadOnlyList<T> Value { get; }`
- L271-275 _public ctor_ `public BgListConstantExpr(IEnumerable<T> value) : base(BgExprFlags.NotInterned)`
- L277-280 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListPushExpr`  
`class BgListPushExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L283-310_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L285 _public property_ `public BgList<T> List { get; }`
- L286 _public property_ `public T Item { get; }`
- L288-293 _public ctor_ `public BgListPushExpr(BgList<T> list, T item) : base(BgExprFlags.None)`
- L295-309 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListCountExpr`  
`class BgListCountExpr<T> : BgInt where T : BgExpr`  
_internal*; L312-327_
- inherits: `BgInt`
- constraints: `where T : BgExpr`
- L314 _public property_ `public BgList<T> List { get; }`
- L316-320 _public ctor_ `public BgListCountExpr(BgList<T> list) : base(BgExprFlags.None)`
- L322-326 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListConcatExpr`  
`class BgListConcatExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L329-347_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L331 _public property_ `public BgList<T> Lhs { get; }`
- L332 _public property_ `public BgList<T> Rhs { get; }`
- L334-339 _public ctor_ `public BgListConcatExpr(BgList<T> lhs, BgList<T> rhs) : base(BgExprFlags.None)`
- L341-346 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListElementExpr`  
`class BgListElementExpr<T> : BgExpr where T : BgExpr`  
_internal*; L349-369_
- inherits: `BgExpr`
- constraints: `where T : BgExpr`
- L351 _public property_ `public BgList<T> List { get; }`
- L352 _public property_ `public BgInt Index { get; }`
- L354-359 _public ctor_ `public BgListElementExpr(BgList<T> list, BgInt index) : base(BgExprFlags.None)`
- L361-366 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L368 _public method_ `public override BgString ToBgString()`

#### class `EpicGames.BuildGraph.Expressions.BgListDistinctExpr`  
`class BgListDistinctExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L371-386_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L373 _public property_ `public BgList<T> Source { get; }`
- L375-379 _public ctor_ `public BgListDistinctExpr(BgList<T> source) : base(BgExprFlags.None)`
- L381-385 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListSelectExpr`  
`class BgListSelectExpr<TIn, TOut> : BgList<TOut> where TIn : BgExpr where TOut : BgExpr`  
_internal*; L388-406_
- inherits: `BgList<TOut>`
- constraints: `where TIn : BgExpr where TOut : BgExpr`
- L390 _public property_ `public BgList<TIn> Source { get; }`
- L391 _public property_ `public BgFunc<TIn, TOut> Function { get; }`
- L393-398 _public ctor_ `public BgListSelectExpr(BgList<TIn> source, BgFunc<TIn, TOut> function) : base(BgExprFlags.None)`
- L400-405 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListWhereExpr`  
`class BgListWhereExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L408-426_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L410 _public property_ `public BgList<T> Source { get; }`
- L411 _public property_ `public BgFunc<T, BgBool> Predicate { get; }`
- L413-418 _public ctor_ `public BgListWhereExpr(BgList<T> source, BgFunc<T, BgBool> predicate) : base(BgExprFlags.None)`
- L420-425 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListUnionExpr`  
`class BgListUnionExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L428-446_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L430 _public property_ `public BgList<T> Input { get; }`
- L431 _public property_ `public BgList<T> Other { get; }`
- L433-438 _public ctor_ `public BgListUnionExpr(BgList<T> input, BgList<T> other) : base(BgExprFlags.None)`
- L440-445 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListExceptExpr`  
`class BgListExceptExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L448-466_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L450 _public property_ `public BgList<T> Input { get; }`
- L451 _public property_ `public BgList<T> Other { get; }`
- L453-458 _public ctor_ `public BgListExceptExpr(BgList<T> input, BgList<T> other) : base(BgExprFlags.None)`
- L460-465 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListContainsExpr`  
`class BgListContainsExpr<T> : BgBool where T : BgExpr`  
_internal*; L468-486_
- inherits: `BgBool`
- constraints: `where T : BgExpr`
- L470 _public property_ `public BgList<T> List { get; }`
- L471 _public property_ `public T Item { get; }`
- L473-478 _public ctor_ `public BgListContainsExpr(BgList<T> list, T item) : base(BgExprFlags.None)`
- L480-485 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListLazyEval`  
`class BgListLazyEval<T> : BgList<T> where T : BgExpr`  
_internal*; L488-503_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L490 _private* property_ `BgList<T> List { get; }`
- L492-496 _public ctor_ `public BgListLazyEval(BgList<T> list) : base(BgExprFlags.None)`
- L498-502 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListWrappedExpr`  
`class BgListWrappedExpr<T> : BgList<T> where T : BgExpr`  
_internal*; L505-516_
- inherits: `BgList<T>`
- constraints: `where T : BgExpr`
- L507 _private* property_ `BgExpr Expr { get; }`
- L509-513 _public ctor_ `public BgListWrappedExpr(BgExpr expr) : base(expr.Flags)`
- L515 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgListOption`  
`public class BgListOption : BgList<BgString>`  
_public; L523-612_
- inherits: `BgList<BgString>`
- desc: A list option expression
- L528 _public property_ `public BgString Name { get; }` — Name of the option
- L533 _public property_ `public BgString? Label { get; }` — Label to display next to the option
- L538 _public property_ `public BgString? Description { get; }` — Help text to display for the user
- L543 _public property_ `public BgEnum<BgListOptionStyle> Style { get; }` — Style for this list box
- L548 _public property_ `public BgString? DefaultValue { get; set; }` — Default value for the option
- L553 _public property_ `public BgList<BgString>? Values { get; set; }` — List of values to choose from
- L558 _public property_ `public BgList<BgString>? ValueDescriptions { get; set; }` — Matching list of descriptions for each value
- L563-573 _public ctor_ `public BgListOption(string name, BgString? description = null, BgString? defaultValue = null, BgListOptionStyle style = BgListOptionStyle.CheckList, BgList<BgString>? values = null, BgList<BgString>? valueDescriptions = null, BgString? label = null) : base(BgExprFlags.None)` — Constructor
- L576-580 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L582-611 _private* method_ `BgObject<BgListOptionDef> CreateOptionsObject()`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgNode.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgNodeException`  
`public sealed class BgNodeException : Exception`  
_public; L17-26_
- inherits: `Exception`
- desc: Exception for constructing nodes
- L23-25 _public ctor_ `public BgNodeException(string message) : base(message)` — Constructor

#### class `EpicGames.BuildGraph.Expressions.BgNodeNameAttribute`  
`public sealed class BgNodeNameAttribute : Attribute`  
_public; L32-47_
- attrs: `[AttributeUsage(AttributeTargets.Method)]`
- inherits: `Attribute`
- desc: Speecifies the node name for a method. Parameters from the method may be embedded in the name using the {ParamName} syntax.
- L37 _public property_ `public string Template { get; }` — The format string
- L43-46 _public ctor_ `public BgNodeNameAttribute(string template)` — Constructor

#### class `EpicGames.BuildGraph.Expressions.BgNode`  
`public class BgNode : BgExpr`  
_public; L52-362_
- inherits: `BgExpr`
- desc: Specification for a node to execute
- L57 _public property_ `public BgString Name { get; }` — Name of the node
- L62 _public property_ `public BgThunk Thunk { get; }` — Thunk to native code to execute the node
- L67 _public property_ `public int OutputCount { get; set; }` — Number of outputs from this node
- L72 _public property_ `public BgFileSet DefaultOutput { get; }` — The default output of this node. Includes all other outputs.
- L77 _public property_ `public BgAgent Agent { get; }` — Agent for the node to be run on
- L82 _public property_ `public BgList<BgFileSet> Inputs { get; set; }` — Tokens for inputs of this node
- L87 _public property_ `public BgList<BgFileSet> OptionalInputs { get; set; }` — Tokens for optional inputs of this node
- L92 _public property_ `public BgList<BgNode> Fences { get; set; }` — Weak dependency on outputs that must be generated for the node to run, without making those dependencies inputs.
- L97 _public property_ `public BgBool RunEarly { get; set; }` — Whether this node should start running as soon as its dependencies are ready, even if other nodes in the same agent are not.
- L102 _public property_ `public BgList<BgLabel> Labels { get; set; }` — Labels that this node contributes to
- L107 _public property_ `public BgList<BgAnnotation> Annotations { get; set; }` — Custom annotations for this node
- L112-119 _public ctor_ `public BgNode(BgThunk thunk, BgAgent agent, BgString? name = null) : base(BgExprFlags.ForceFragment)` — Constructor
- L125-138 _public ctor_ `public BgNode(BgNode node) : base(BgExprFlags.ForceFragment)` — Copy constructor
- L141-156 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L168-203 _internal method_ `internal BgNode Modify( BgList<BgFileSet>? inputs = null, BgList<BgFileSet>? optionalInputs = null, BgList<BgNode>? fences = null, BgBool? runEarly = null, BgList<BgLabel>? labels = null, BgList<BgAnnotation>? annotations = null )` — Creates a copy of this node and updates the given parameters
- L209 _protected method_ `protected virtual BgNode Clone()` — Clone this node
- L217-220 _internal method_ `internal static string GetDefaultTagName(string name, int index)` — Gets the default tag name for the numbered output index
- L222-234 _private* method_ `static BgString GetDefaultNodeName(BgThunk thunk)`
- L236-302 _private* method_ `static BgString GetNodeNameFromTemplate(string template, ParameterInfo[] parameters, IReadOnlyList<object?> arguments)`
- L307-340 _public method_ `public static string GetNodeNameFromMethodName(string methodName)` — Inserts spaces into a PascalCase method name to create a node name
- L346-349 _public operator_ `public static implicit operator BgFileSet(BgNode node)` — Implicit conversion to a fileset
- L355-358 _public operator_ `public static implicit operator BgList<BgFileSet>(BgNode node)` — Implicit conversion to a fileset
- L361 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgNode`  
`public class BgNode<T> : BgNode`  
_public; L368-457_
- inherits: `BgNode`
- desc: Nodespec with a typed return value
- L373 _public property_ `public T Output { get; }` — Output from this node
- L378-382 _public ctor_ `public BgNode(BgThunk<T> thunk, BgAgent agent, BgString? name = null) : base(thunk, agent, name)` — Constructor
- L387-391 _public ctor_ `public BgNode(BgNode<T> other) : base(other)` — Copy constructor
- L397 _protected method_ `protected override BgNode Clone()` — Clone this node
- L399-414 _private* method_ `T CreateOutput()`
- L416-424 _private* method_ `BgExpr[] CreateOutputExprs(Type[] types)`
- L426-443 _private* method_ `BgExpr CreateOutputExpr(Type type, int index)`
- L445-456 _internal method_ `internal static bool IsValueTuple(Type returnType)`

#### class `EpicGames.BuildGraph.Expressions.BgNodeExtensions`  
`public static class BgNodeExtensions`  
_public; L462-622_
- desc: Extension methods for BgNode types
- L470-474 _public method_ `public static BgNode AddNode(this BgAgent agent, Expression<Func<BgContext, Task>> func)` — Creates a node builder for the given agent
- L484-488 _public method_ `public static BgNode AddNode(this BgAgent agent, BgString name, Expression<Func<BgContext, Task>> func)` — Creates a node builder for the given agent
- L496-500 _public method_ `public static BgNode<T> AddNode<T>(this BgAgent agent, Expression<Func<BgContext, Task<T>>> func)` — Creates a node builder for the given agent
- L509-513 _public method_ `public static BgNode<T> AddNode<T>(this BgAgent agent, BgString name, Expression<Func<BgContext, Task<T>>> func)` — Creates a node builder for the given agent
- L521-524 _public method_ `public static T Requires<T>(this T node, params BgNode[] inputs) where T : BgNode` — Add dependencies onto other nodes or outputs. Outputs from the given tokens will be copied to the current machine before execution of the node.
- L532-535 _public method_ `public static T OptionalRequires<T>(this T node, params BgNode[] inputs) where T : BgNode` — Add optional dependencies onto other nodes or outputs. Outputs from the given tokens will be copied to the current machine before execution of the node.
- L543-546 _public method_ `public static T Requires<T>(this T node, params BgFileSet[] inputs) where T : BgNode` — Add dependencies onto other nodes or outputs. Outputs from the given tokens will be copied to the current machine before execution of the node.
- L554-557 _public method_ `public static T OptionalRequires<T>(this T node, params BgFileSet[] inputs) where T : BgNode` — Add optional dependencies onto other nodes or outputs. Outputs from the given tokens will be copied to the current machine before execution of the node.
- L565-568 _public method_ `public static T Requires<T>(this T node, BgList<BgFileSet> inputs) where T : BgNode` — Add dependencies onto other nodes or outputs. Outputs from the given tokens will be copied to the current machine before execution of the node.
- L576-579 _public method_ `public static T OptionalRequires<T>(this T node, BgList<BgFileSet> inputs) where T : BgNode` — Add optional dependencies onto other nodes or outputs. Outputs from the given tokens will be copied to the current machine before execution of the node.
- L588-591 _public method_ `public static T After<T>(this T node, params BgNode[] inputs) where T : BgNode` — Add weak dependencies onto other nodes or outputs. The producing nodes must complete successfully if they are part of the graph, but outputs from them will not be transferred to the machine running this node.
- L599-602 _public method_ `public static T AddLabel<T>(this T node, BgLabel label) where T : BgNode` — Add a label to the node.
- L607-610 _public method_ `public static T RunEarly<T>(this T node) where T : BgNode` — Allows the node to run early.
- L618-621 _public method_ `public static T AddAnnotation<T>(this T node, BgAnnotation annotation) where T : BgNode` — Add an annotation to the node.

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgObject.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgObject`  
`public abstract class BgObject<T> : BgExpr`  
_public; L15-77_
- attrs: `[BgType(typeof(BgObjectType<>))]`
- inherits: `BgExpr`
- desc: Abstract base class for expressions returning an object
- L20 _public property_ `public static BgObject<T> Empty { get; }` — Constant representation of an empty object
- L26-29 _protected ctor_ `protected BgObject(BgExprFlags flags) : base(flags)` — Constructor
- L37 _public method_ `public BgObject<T> Set(string name, BgExpr value)` — Sets the value of a property in the object
- L45-51 _public method_ `public BgObject<T> Set<TExpr, TNative>(Expression<Func<T, TNative>> property, TExpr value) where TExpr : BgExpr` — Sets the value of a property in the object
- L59 _public method_ `public TExpr Get<TExpr>(string name, TExpr defaultValue) where TExpr : BgExpr` — Gets the value of a field in the object
- L67-73 _public method_ `public TExpr Get<TExpr, TNative>(Expression<Func<T, TNative>> property, TExpr defaultValue) where TExpr : BgExpr` — Gets the value of a field in the object
- L76 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgObjectType`  
`class BgObjectType<T> : BgType<BgObject<T>> where T : new()`  
_internal*; L82-89_
- inherits: `BgType<BgObject<T>>`
- constraints: `where T : new()`
- desc: Traits for a BgList{T}
- L85 _public method_ `public override BgObject<T> Constant(object value)` — (inheritdoc)
- L88 _public method_ `public override BgObject<T> Wrap(BgExpr expr)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgObjectEmptyExpr`  
`class BgObjectEmptyExpr<T> : BgObject<T>`  
_internal*; L93-104_
- inherits: `BgObject<T>`
- L95-98 _public ctor_ `public BgObjectEmptyExpr() : base(BgExprFlags.NotInterned)`
- L100-103 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgObjectConstantExpr`  
`class BgObjectConstantExpr<T> : BgObject<T>`  
_internal*; L106-120_
- inherits: `BgObject<T>`
- L108 _public property_ `public ImmutableDictionary<string, object> Fields { get; }`
- L110-114 _public ctor_ `public BgObjectConstantExpr(ImmutableDictionary<string, object> fields) : base(BgExprFlags.NotInterned)`
- L116-119 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgObjectSetExpr`  
`class BgObjectSetExpr<T> : BgObject<T>`  
_internal*; L122-143_
- inherits: `BgObject<T>`
- L124 _public property_ `public BgObject<T> Object { get; }`
- L125 _public property_ `public string Name { get; }`
- L126 _public property_ `public BgExpr Value { get; }`
- L128-134 _public ctor_ `public BgObjectSetExpr(BgObject<T> obj, string name, BgExpr value) : base(BgExprFlags.NotInterned)`
- L136-142 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgObjectGetExpr`  
`class BgObjectGetExpr<T> : BgObject<T>`  
_internal*; L145-166_
- inherits: `BgObject<T>`
- L147 _public property_ `public BgObject<T> Object { get; }`
- L148 _public property_ `public string Name { get; }`
- L149 _public property_ `public BgExpr DefaultValue { get; }`
- L151-157 _public ctor_ `public BgObjectGetExpr(BgObject<T> obj, string name, BgExpr defaultValue) : base(BgExprFlags.NotInterned)`
- L159-165 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgObjectWrappedExpr`  
`class BgObjectWrappedExpr<T> : BgObject<T>`  
_internal*; L168-179_
- inherits: `BgObject<T>`
- L170 _private* property_ `BgExpr Expr { get; }`
- L172-176 _public ctor_ `public BgObjectWrappedExpr(BgExpr expr) : base(expr.Flags)`
- L178 _public method_ `public override void Write(BgBytecodeWriter writer)`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgString.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgString`  
`public abstract class BgString : BgExpr`  
_public; L12-79_
- attrs: `[BgType(typeof(BgStringType))]`
- inherits: `BgExpr`
- desc: Abstract base class for expressions returning a string value
- L17 _public property_ `public static BgString Empty { get; }` — Constant value for an empty string
- L23-26 _protected ctor_ `protected BgString(BgExprFlags flags) : base(flags)` — Constructor
- L31-34 _public operator_ `public static implicit operator BgString(string value)` — Implicit conversion from a regular string type
- L37 _public method_ `public static BgBool Equals(BgString lhs, BgString rhs, StringComparison comparison = StringComparison.CurrentCulture)` — (inheritdoc)
- L40 _public method_ `public static BgInt Compare(BgString lhs, BgString rhs, StringComparison comparison = StringComparison.CurrentCulture)` — (inheritdoc)
- L43 _public method_ `public static BgString Join(BgString separator, BgList<BgString> values)` — (inheritdoc)
- L46 _public method_ `public BgList<BgString> Split(BgString separator)` — (inheritdoc)
- L49 _public method_ `public static BgString Format(string format, params BgExpr[] args)` — (inheritdoc)
- L52 _public operator_ `public static BgString operator +(BgString lhs, BgString rhs)` — (inheritdoc)
- L55 _public operator_ `public static BgBool operator ==(BgString lhs, BgString rhs)` — (inheritdoc)
- L58 _public operator_ `public static BgBool operator !=(BgString lhs, BgString rhs)` — (inheritdoc)
- L63 _public method_ `public BgString Append(BgString other)` — Appens another string to this one
- L66 _public method_ `public BgBool Match(BgString pattern)` — (inheritdoc)
- L69 _public method_ `public BgString Replace(BgString pattern, BgString replace)` — (inheritdoc)
- L72 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L75 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L78 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgStringType`  
`class BgStringType : BgType<BgString>`  
_internal*; L84-91_
- inherits: `BgType<BgString>`
- desc: Traits implementation for BgString
- L87 _public method_ `public override BgString Constant(object value)` — (inheritdoc)
- L90 _public method_ `public override BgString Wrap(BgExpr expr)` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgStringCompareExpr`  
`class BgStringCompareExpr : BgInt`  
_internal*; L95-118_
- inherits: `BgInt`
- L97 _public property_ `public BgString Lhs { get; }`
- L98 _public property_ `public BgString Rhs { get; }`
- L99 _public property_ `public StringComparison Comparison { get; }`
- L101-107 _public ctor_ `public BgStringCompareExpr(BgString lhs, BgString rhs, StringComparison comparison) : base(lhs.Flags & rhs.Flags & BgExprFlags.Eager)`
- L109-115 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L117 _public method_ `public override string ToString()`

#### class `EpicGames.BuildGraph.Expressions.BgStringConcatExpr`  
`class BgStringConcatExpr : BgString`  
_internal*; L120-140_
- inherits: `BgString`
- L122 _public property_ `public BgString Lhs { get; }`
- L123 _public property_ `public BgString Rhs { get; }`
- L125-130 _public ctor_ `public BgStringConcatExpr(BgString lhs, BgString rhs) : base(lhs.Flags & rhs.Flags & BgExprFlags.Eager)`
- L132-137 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L139 _public method_ `public override string ToString()`

#### class `EpicGames.BuildGraph.Expressions.BgStringJoinExpr`  
`class BgStringJoinExpr : BgString`  
_internal*; L142-162_
- inherits: `BgString`
- L144 _public property_ `public BgString Separator { get; }`
- L145 _public property_ `public BgList<BgString> Values { get; }`
- L147-152 _public ctor_ `public BgStringJoinExpr(BgString separator, BgList<BgString> values) : base(BgExprFlags.None)`
- L154-159 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L161 _public method_ `public override string ToString()`

#### class `EpicGames.BuildGraph.Expressions.BgStringSplitExpr`  
`class BgStringSplitExpr : BgList<BgString>`  
_internal*; L164-184_
- inherits: `BgList<BgString>`
- L166 _public property_ `public BgString Source { get; }`
- L167 _public property_ `public BgString Separator { get; }`
- L169-174 _public ctor_ `public BgStringSplitExpr(BgString source, BgString separator) : base(source.Flags & separator.Flags & BgExprFlags.Eager)`
- L176-181 _public method_ `public override void Write(BgBytecodeWriter writer)`
- L183 _public method_ `public override string ToString()`

#### class `EpicGames.BuildGraph.Expressions.BgStringMatchExpr`  
`class BgStringMatchExpr : BgBool`  
_internal*; L186-204_
- inherits: `BgBool`
- L188 _public property_ `public BgString Input { get; }`
- L189 _public property_ `public BgString Pattern { get; }`
- L191-196 _public ctor_ `public BgStringMatchExpr(BgString input, BgString pattern) : base(input.Flags & BgExprFlags.Eager)`
- L198-203 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgStringReplaceExpr`  
`class BgStringReplaceExpr : BgString`  
_internal*; L206-227_
- inherits: `BgString`
- L208 _public property_ `public BgString Input { get; }`
- L209 _public property_ `public BgString Pattern { get; }`
- L210 _public property_ `public BgString Replacement { get; }`
- L212-218 _public ctor_ `public BgStringReplaceExpr(BgString input, BgString pattern, BgString replacement) : base(input.Flags & replacement.Flags & BgExprFlags.Eager)`
- L220-226 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgStringFormatExpr`  
`class BgStringFormatExpr : BgString`  
_internal*; L229-251_
- inherits: `BgString`
- L231 _private* field_ `readonly BgString _format`
- L232 _private* field_ `readonly BgExpr[] _arguments`
- L234-239 _public ctor_ `public BgStringFormatExpr(BgString format, BgExpr[] arguments) : base(BgExprFlags.None)`
- L241-250 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgStringEmptyExpr`  
`class BgStringEmptyExpr : BgString`  
_internal*; L253-264_
- inherits: `BgString`
- L255-258 _public ctor_ `public BgStringEmptyExpr() : base(BgExprFlags.NotInterned | BgExprFlags.Eager)`
- L260-263 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgStringConstantExpr`  
`class BgStringConstantExpr : BgString`  
_internal*; L266-281_
- inherits: `BgString`
- L268 _public property_ `public string Value { get; }`
- L270-274 _public ctor_ `public BgStringConstantExpr(string value) : base(BgExprFlags.Eager)`
- L276-280 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### class `EpicGames.BuildGraph.Expressions.BgStringWrappedExpr`  
`class BgStringWrappedExpr : BgString`  
_internal*; L283-294_
- inherits: `BgString`
- L285 _private* property_ `BgExpr Expr { get; }`
- L287-291 _public ctor_ `public BgStringWrappedExpr(BgExpr expr) : base(expr.Flags)`
- L293 _public method_ `public override void Write(BgBytecodeWriter writer)`

#### enum `EpicGames.BuildGraph.Expressions.BgStringOptionStyle`  
`public enum BgStringOptionStyle`  
_public; L301-312_
- desc: Style for a string option
- L306 _public* enumerator_ `Text` — Free-form text entry
- L311 _public* enumerator_ `DropList` — List of options

#### class `EpicGames.BuildGraph.Expressions.BgStringOption`  
`public class BgStringOption : BgString`  
_public; L317-426_
- inherits: `BgString`
- desc: A string option expression
- L322 _public property_ `public BgString Name { get; }` — Name of the option
- L327 _public property_ `public BgString? Label { get; }` — Label to display next to the option
- L332 _public property_ `public BgString? Description { get; }` — Help text to display for the user
- L337 _public property_ `public BgString? DefaultValue { get; set; }` — Default value for the option
- L342 _public property_ `public BgEnum<BgStringOptionStyle>? Style { get; }` — Style for this option
- L347 _public property_ `public BgString? Pattern { get; set; }` — Regex for validating values for the option
- L352 _public property_ `public BgString? PatternFailed { get; set; }` — Message to display if validation fails
- L357 _public property_ `public BgList<BgString>? Values { get; set; }` — List of values to choose from
- L362 _public property_ `public BgList<BgString>? ValueDescriptions { get; set; }` — Matching list of descriptions for each value
- L367-379 _public ctor_ `public BgStringOption(string name, BgString? description = null, BgString? defaultValue = null, BgEnum<BgStringOptionStyle>? style = null, BgString? pattern = null, BgString? patternFailed = null, BgList<BgString>? values = null, BgList<BgString>? valueDescriptions = null, BgString? label = null) : base(BgExprFlags.None)` — Constructor
- L382-386 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L388-425 _private* method_ `BgObject<BgStringOptionDef> CreateOptionsObject()`

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgThunk.cs` (EpicGames.BuildGraph)


#### class `EpicGames.BuildGraph.Expressions.BgThunk`  
`public class BgThunk : BgExpr`  
_public; L14-131_
- inherits: `BgExpr`
- desc: Thunks to a native method from within an expression. These objects contain an index into a thunk table that is not persisted to the bytecode.
- L19 _public property_ `public MethodInfo Method { get; }` — Method to call
- L24 _public property_ `public IReadOnlyList<object?> Arguments { get; }` — Arguments for the method
- L31-35 _public method_ `public static BgThunk Create(Expression<Func<Task>> expr)` — Creates a method closure from the given expression
- L43-47 _public method_ `public static BgThunk<TRet> Create<TRet>(Expression<Func<Task<TRet>>> expr)` — Creates a method closure from the given expression
- L55-59 _public method_ `public static BgThunk Create<TArg>(Expression<Func<TArg, Task>> expr)` — Creates a method closure from the given expression
- L68-72 _public method_ `public static BgThunk<TRet> Create<TArg, TRet>(Expression<Func<TArg, Task<TRet>>> expr)` — Creates a method closure from the given expression
- L78-83 _public ctor_ `public BgThunk(MethodCallExpression call) : base(BgExprFlags.None)` — Constructor
- L85-105 _private* method_ `static object?[] GetArguments(MethodCallExpression call)`
- L108-127 _public method_ `public override void Write(BgBytecodeWriter writer)` — (inheritdoc)
- L130 _public method_ `public override BgString ToBgString()` — (inheritdoc)

#### class `EpicGames.BuildGraph.Expressions.BgThunk`  
`public class BgThunk<T> : BgThunk`  
_public; L137-147_
- inherits: `BgThunk`
- desc: Wraps a native method that returns a value
- L143-146 _public ctor_ `public BgThunk(MethodCallExpression expr) : base(expr)` — Constructor

### `Source/Programs/Shared/EpicGames.BuildGraph/Expressions/BgType.cs` (EpicGames.BuildGraph)


#### interface `EpicGames.BuildGraph.Expressions.IBgType`  
`public interface IBgType`  
_public; L12-20_
- desc: Interface for type traits
- L19 _public method_ `public abstract BgExpr Constant(object value)` — Creates a constant expression wrapping the given value

#### class `EpicGames.BuildGraph.Expressions.BgType`  
`public abstract class BgType<T> : IBgType where T : BgExpr`  
_public; L25-39_
- inherits: `IBgType`
- constraints: `where T : BgExpr`
- desc: Base class for type functions
- L28 _private* method_ `BgExpr IBgType.Constant(object value)` — (inheritdoc)
- L31 _public method_ `public abstract T Constant(object value)` — (inheritdoc)
- L38 _public method_ `public abstract T Wrap(BgExpr expr)` — Wraps an untyped expression as a strongly typed value

#### class `EpicGames.BuildGraph.Expressions.BgTypeAttribute`  
`sealed class BgTypeAttribute : Attribute`  
_internal*; L45-60_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute used to specify the converter class to use for a type
- L50 _public property_ `public Type Type { get; }` — The converter type
- L56-59 _public ctor_ `public BgTypeAttribute(Type type)` — Constructor

#### class `EpicGames.BuildGraph.Expressions.BgType`  
`public abstract class BgType`  
_public; L65-149_
- desc: Utility methods for type traits
- L72 _private* field_ `static readonly ConcurrentDictionary<Type, IBgType> s_typeCache = ...`
- L72 _private* field_ `static readonly ConcurrentDictionary< s_typeCache = new()`
- L79-90 _private* method_ `static object CreateInstance(Type type)` — Create a converter instance for the given type
- L97-100 _public method_ `public static IBgType Get(Type type)` — Gets the type interface for a type
- L102-106 _private* method_ `static IBgType CreateTypeInstance(Type type)`
- L112-115 _public method_ `public static BgType<T> Get<T>() where T : BgExpr` — Create a traits instance for the given type
- L123-126 _public method_ `public static T Wrap<T>(BgExpr expr) where T : BgExpr` — Wraps an expression as a different type
- L134-137 _public method_ `public static T Constant<T>(object value) where T : BgExpr` — Creates a constant of the given type
- L145-148 _public method_ `public static BgExpr Constant(Type type, object value)` — Creates a constant of the given type

#### class `EpicGames.BuildGraph.Expressions.BgType.BgTypeCache`  
`class BgTypeCache<T> where T : BgExpr`  
_private*; L67-70_
- constraints: `where T : BgExpr`
- L69 _public property_ `public static BgType<T> Instance { get; }`
