# CSharp / BuildGraph.Automation

- project root: `Source/Programs/AutomationTool/BuildGraph`
- files: 84; symbols: 1746
- symbol kinds: class=221, const=21, ctor=113, enum=5, enumerator=54, field=133, interface=1, method=609, operator=1, property=583, record=2, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/BuildGraph/BgCondition.cs` (BuildGraph.Automation)


#### class `AutomationTool.BgConditionException`  
`public class BgConditionException : Exception`  
_public; L17-27_
- inherits: `Exception`
- desc: Exception class thrown due to type and syntax errors in condition expressions
- L24-26 _public ctor_ `public BgConditionException(string format, params object[] args) : base(String.Format(format, args))` — Constructor; formats the exception message with the given String.Format() style parameters.

#### record `AutomationTool.BgConditionContext`  
`public record class BgConditionContext(DirectoryReference RootDir)`  
_public; L33-33_
- desc: Context for evaluating BuildGraph conditions

#### class `AutomationTool.BgCondition`  
`public class BgCondition`  
_public; L65-556_
- desc: Class to evaluate condition expressions in build scripts, following this grammar: or-expression ::= and-expression | or-expression "Or" and-expression; and-expression ::= comparison | and-expression "And" comparison; comparison ::= scalar | scalar "==" scalar | scalar "!=" scalar | scalar "<" scalar | scalar "<=" scalar; | scalar ">" scalar | scalar ">=" scalar; scalar ::= "(" or-expression ")" | "!" scalar | "Exists" "(" scalar ")" | "HasTrailingSlash" "(" scalar ")" | string | identifier; string ::= any sequence of characters terminated by single quotes (') or double quotes ("). Not escaped. identifier ::= any sequence of letters, digits, or underscore characters. The type of each subexpression is always a scalar, which are converted to expression-specific types (eg. booleans, integers) as required. Scalar values are case-insensitive strings. The identifier 'true' and the strings "true" and "True" are all identical scalars.
- L70 _private* const_ `const string EndToken = "<EOF>"` — Sentinel added to the end of a sequence of tokens.
- L75 _private* field_ `readonly List<string> _tokens = new List<string>()` — Tokens for the condition
- L80 _private* field_ `int _idx` — The current token index
- L86-89 _private ctor_ `private BgCondition(string text)` — Constructor
- L97-100 _public method_ `public static ValueTask<bool> EvaluateAsync(string text, BgConditionContext context)` — Evaluates the given string as a condition. Throws a ConditionException on a type or syntax error.
- L107-123 _private* method_ `async ValueTask<bool> EvaluateAsync(BgConditionContext context)` — Evaluates the given string as a condition. Throws a ConditionException on a type or syntax error.
- L130-143 _private* method_ `async ValueTask<string> EvaluateOrAsync(BgConditionContext context)` — Evaluates an "or-expression" production.
- L150-163 _private* method_ `async ValueTask<string> EvaluateAndAsync(BgConditionContext context)` — Evaluates an "and-expression" production.
- L170-230 _private* method_ `async ValueTask<string> EvaluateComparisonAsync(BgConditionContext context)` — Evaluates a "comparison" production.
- L236-278 _private* method_ `IEnumerable<string> EvaluateArguments()` — Evaluates arguments from a token string. Arguments are all comma-separated tokens until a closing ) is encountered
- L285-373 _private* method_ `async ValueTask<string> EvaluateScalarAsync(BgConditionContext context)` — Evaluates a "scalar" production.
- L378-388 _private* method_ `static bool Exists(string path, BgConditionContext context)` — Determine if a path exists
- L396-406 _private* method_ `static bool Contains(string haystack, string needle)` — Checks whether Haystack contains "Needle".
- L415-426 _private* method_ `static bool ContainsItem(string haystack, string needle, string haystackSeparator)` — Checks whether HaystackItems contains "Needle".
- L433-449 _private* method_ `static bool CoerceToBool(string scalar)` — Converts a scalar to a boolean value.
- L456-464 _private* method_ `static int CoerceToInteger(string scalar)` — Converts a scalar to a boolean value.
- L471-521 _private* method_ `static void Tokenize(string text, List<string> tokens)` — Splits an input string up into expression tokens.
- L526-544 _public method_ `public static async Task TestConditionsAsync()` — Test cases for conditions.
- L551-555 _private* method_ `static async Task TestConditionAsync(string condition, bool expectedResult)` — Helper method to evaluate a condition and check it's the expected result

### `Source/Programs/AutomationTool/BuildGraph/BgGraphBuilder.cs` (BuildGraph.Automation)


#### class `AutomationTool.BgGraphBuilder`  
`public abstract class BgGraphBuilder`  
_public; L14-25_
- desc: Base class for any user defined graphs
- L19 _protected property_ `protected static ILogger Logger => ...` — Accessor for default logger instance
- L24 _public method_ `public abstract BgGraph CreateGraph()` — Callback used to instantiate the graph

### `Source/Programs/AutomationTool/BuildGraph/BgNodeExecutor.cs` (BuildGraph.Automation)


#### class `AutomationTool.BgNodeExecutor`  
`abstract class BgNodeExecutor`  
_internal*; L26-29_
- desc: Base class for binding and executing nodes
- L28 _public method_ `public abstract Task<bool> Execute(JobContext job, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)`

#### class `AutomationTool.BgBytecodeNodeExecutor`  
`class BgBytecodeNodeExecutor : BgNodeExecutor`  
_internal*; L31-141_
- inherits: `BgNodeExecutor`
- L59 _private* field_ `readonly BgNodeDef _node`
- L61-64 _public ctor_ `public BgBytecodeNodeExecutor(BgNodeDef node)`
- L66-70 _public method_ `public static bool Bind(ILogger logger)`
- L78-140 _public method_ `public override async Task<bool> Execute(JobContext job, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the method given in the

#### class `AutomationTool.BgBytecodeNodeExecutor.BgContextImpl`  
`class BgContextImpl : BgContext`  
_private*; L33-57_
- inherits: `BgContext`
- L35-39 _public ctor_ `public BgContextImpl(JobContext jobContext, Dictionary<string, HashSet<FileReference>> tagNameToFileSet) : base(tagNameToFileSet.ToDictionary(x => x.Key, x => FileSet.FromFiles(Unreal.RootDirectory, x.Value)))`
- L41 _public property_ `public override string Stream => ...`
- L43 _public property_ `public override int Change => ...`
- L45 _public property_ `public override int CodeChange => ...`
- L47-54 _public property_ `public override (int Major, int Minor, int Patch) EngineVersion { get; }`
- L56 _public property_ `public override bool IsBuildMachine => ...`

#### class `AutomationTool.BgScriptNodeExecutor`  
`class BgScriptNodeExecutor : BgNodeExecutor`  
_internal*; L146-431_
- inherits: `BgNodeExecutor`
- desc: Implementation of BgNodeDef for graphs defined through XML syntax
- L151 _public property_ `public BgScriptNode Node { get; }` — The script node
- L156 _private* field_ `readonly List<BgTaskImpl> _boundTasks = new List<BgTaskImpl>()` — List of bound task implementations
- L161-164 _public ctor_ `public BgScriptNodeExecutor(BgScriptNode node)` — Constructor
- L166-182 _public method_ `public async ValueTask<bool> BindAsync(Dictionary<string, ScriptTaskBinding> nameToTask, Dictionary<string, BgNodeOutput> tagNameToNodeOutput, ILogger logger)`
- L184-303 _private* method_ `async ValueTask<BgTaskImpl?> BindTaskAsync(BgTask taskInfo, Dictionary<string, ScriptTaskBinding> nameToTask, IReadOnlyDictionary<string, BgNodeOutput> tagNameToNodeOutput, ILogger logger)`
- L312-355 _private* method_ `static async ValueTask<object?> ParseValueAsync(string valueText, Type valueType, BgConditionContext context)` — Parse a value of the given type
- L363-430 _public method_ `public override async Task<bool> Execute(JobContext job, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Build all the tasks for this node

### `Source/Programs/AutomationTool/BuildGraph/BgSchema.cs` (BuildGraph.Automation)


#### enum `AutomationTool.TaskParameterValidationType`  
`public enum TaskParameterValidationType`  
_public; L19-35_
- desc: Specifies validation that should be performed on a task parameter.
- L24 _public* enumerator_ `Default` — Allow any valid values for the field type.
- L29 _public* enumerator_ `TagList` — A list of tag names separated by semicolons
- L34 _public* enumerator_ `FileSpec` — A file specification, which may contain tags and wildcards.

#### class `AutomationTool.BgScriptTaskParameter`  
`public class BgScriptTaskParameter`  
_public; L41-100_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Information about a parameter to a task
- L46 _public property_ `public string Name { get; }` — Name of this parameter
- L51 _public property_ `public Type ValueType { get; }` — The type for values assigned to this field
- L56 _public property_ `public Type? CollectionType { get; }` — The ICollection interface for this type
- L61 _public property_ `public TaskParameterValidationType ValidationType { get; }` — Validation type for this field
- L66 _public property_ `public bool Optional { get; }` — Whether this parameter is optional
- L71-99 _public ctor_ `public BgScriptTaskParameter(string name, Type valueType, TaskParameterValidationType validationType, bool optional)` — Constructor

#### class `AutomationTool.BgScriptTask`  
`public class BgScriptTask`  
_public; L106-128_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Helper class to serialize a task from an xml element
- L111 _public property_ `public string Name { get; }` — Name of this task
- L116 _public property_ `public List<BgScriptTaskParameter> Parameters { get; }` — Parameters for this task
- L123-127 _public ctor_ `public BgScriptTask(string name, List<BgScriptTaskParameter> parameters)` — Constructor

#### enum `AutomationTool.ScriptSchemaStandardType`  
`public enum ScriptSchemaStandardType`  
_public; L134-172_
- desc: Enumeration of standard types used in the schema. Avoids hard-coding names.
- L136 _public* enumerator_ `Graph`
- L137 _public* enumerator_ `Agent`
- L138 _public* enumerator_ `AgentBody`
- L139 _public* enumerator_ `Node`
- L140 _public* enumerator_ `NodeBody`
- L141 _public* enumerator_ `Aggregate`
- L142 _public* enumerator_ `Artifact`
- L143 _public* enumerator_ `Report`
- L144 _public* enumerator_ `Badge`
- L145 _public* enumerator_ `Label`
- L146 _public* enumerator_ `Notify`
- L147 _public* enumerator_ `Include`
- L148 _public* enumerator_ `Option`
- L149 _public* enumerator_ `EnvVar`
- L150 _public* enumerator_ `Property`
- L151 _public* enumerator_ `Regex`
- L152 _public* enumerator_ `StringOp`
- L153 _public* enumerator_ `Macro`
- L154 _public* enumerator_ `MacroBody`
- L155 _public* enumerator_ `Extend`
- L156 _public* enumerator_ `Expand`
- L157 _public* enumerator_ `Annotate`
- L158 _public* enumerator_ `Trace`
- L159 _public* enumerator_ `Warning`
- L160 _public* enumerator_ `Error`
- L161 _public* enumerator_ `Name`
- L162 _public* enumerator_ `NameList`
- L163 _public* enumerator_ `Tag`
- L164 _public* enumerator_ `TagList`
- L165 _public* enumerator_ `NameOrTag`
- L166 _public* enumerator_ `NameOrTagList`
- L167 _public* enumerator_ `QualifiedName`
- L168 _public* enumerator_ `BalancedString`
- L169 _public* enumerator_ `Boolean`
- L170 _public* enumerator_ `Integer`
- L171 _public* enumerator_ `LabelChange`

#### class `AutomationTool.BgScriptSchema`  
`public class BgScriptSchema`  
_public; L178-1210_
- desc: Schema for build graph definitions. Stores information about the supported tasks, and allows validating an XML document.
- L183 _public const_ `public const string RootElementName = "BuildGraph"` — Name of the root element
- L188 _public const_ `public const string NamespaceUri = "http://www.epicgames.com/BuildGraph"` — Namespace for the schema
- L193 _private* field_ `static readonly XmlQualifiedName s_stringTypeName = new XmlQualifiedName("string", "http://www.w3.org/2001/XMLSchema")` — Qualified name for the string type
- L198 _public property_ `public XmlSchema CompiledSchema { get; }` — The inner xml schema
- L203 _public const_ `public const string IllegalNameCharacters = "^<>:\"/\\|?*"` — Characters which are not permitted in names.
- L208 _private* const_ `const string NamePattern = "[^ " + IllegalNameCharacters + "]+( [^ " + IllegalNameCharacters + "]+)*"` — Pattern which matches any name; alphanumeric characters, with single embedded spaces.
- L213 _private* const_ `const string NameListPattern = NamePattern + "(;" + NamePattern + ")*"` — Pattern which matches a list of names, separated by semicolons.
- L218 _private* const_ `const string TagPattern = "#" + NamePattern` — Pattern which matches any tag name; a name with a leading '#' character
- L223 _private* const_ `const string TagListPattern = TagPattern + "(;" + TagPattern + ")*"` — Pattern which matches a list of tag names, separated by semicolons;
- L228 _private* const_ `const string NameOrTagPattern = "#?" + NamePattern` — Pattern which matches any name or tag name; a name with a leading '#' character
- L233 _private* const_ `const string NameOrTagListPattern = NameOrTagPattern + "(;" + NameOrTagPattern + ")*"` — Pattern which matches a list of names or tag names, separated by semicolons;
- L238 _private* const_ `const string QualifiedNamePattern = NamePattern + "(\\." + NamePattern + ")*"` — Pattern which matches a qualified name.
- L243 _private* const_ `const string PropertyPattern = "\\$\\(" + NamePattern + "\\)"` — Pattern which matches a property name
- L248 _private* const_ `const string StringWithPropertiesPattern = "[^\\$]*" + "(" + "(" + PropertyPattern + "|" + "\\$[^\\(]" + ")" + "[^\\$]*" + ")+" + "\\$?"` — Pattern which matches balanced parentheses in a string
- L253 _private* const_ `const string BalancedStringPattern = "[^\\$]*" + "(" + "(" + PropertyPattern + "|" + "\\$[^\\(]" + ")" + "[^\\$]*" + ")*" + "\\$?"` — Pattern which matches balanced parentheses in a string
- L255-258 _private ctor_ `private BgScriptSchema(XmlSchema schema)`
- L265-378 _public ctor_ `public BgScriptSchema(IEnumerable<BgScriptTask> tasks, List<(Type, ScriptSchemaStandardType)> primitiveTypes)` — Constructor
- L384-398 _public method_ `public void Export(FileReference file)` — Export the schema to a file
- L405-417 _public method_ `public static BgScriptSchema? Import(FileReference file)` — Imports a schema from a file
- L419-429 _private* method_ `static void ValidationCallback(object? sender, ValidationEventArgs eventArgs)`
- L436-439 _private* method_ `static string GetTypeName(ScriptSchemaStandardType type)` — Gets the bare name for the given script type
- L446-449 _private* method_ `static XmlQualifiedName GetQualifiedTypeName(ScriptSchemaStandardType type)` — Gets the qualified name for the given script type
- L455-463 _private* method_ `static XmlQualifiedName? GetQualifiedTypeName(TaskParameterValidationType type)` — Gets the qualified name of the schema type for the given type of validation
- L469-502 _private* method_ `static XmlSchemaType CreateGraphType()` — Creates the schema type representing the graph type
- L508-523 _private* method_ `static XmlSchemaType CreateAgentType()` — Creates the schema type representing the agent type
- L529-554 _private* method_ `static XmlSchemaType CreateAgentBodyType()` — Creates the schema type representing the contents of agent type
- L560-584 _private* method_ `static XmlSchemaType CreateNodeType()` — Creates the schema type representing the node type
- L590-623 _private* method_ `static XmlSchemaType CreateNodeBodyType(Dictionary<string, XmlSchemaComplexType> taskNameToType)` — Creates the schema type representing the body of the node type
- L629-640 _private* method_ `static XmlSchemaType CreateAggregateType()` — Creates the schema type representing the aggregate type
- L646-659 _private* method_ `static XmlSchemaType CreateArtifactType()` — Creates the schema type representing the artifact type
- L665-673 _private* method_ `static XmlSchemaType CreateReportType()` — Creates the schema type representing the report type
- L679-690 _private* method_ `static XmlSchemaType CreateBadgeType()` — Creates the schema type representing the badge type
- L696-710 _private* method_ `static XmlSchemaType CreateLabelType()` — Creates the schema type representing the label type
- L716-730 _private* method_ `static XmlSchemaType CreateNotifyType()` — Creates the schema type representing a notifier
- L736-746 _private* method_ `static XmlSchemaType CreateAnnotateType()` — Creates the schema type representing an annotation
- L752-760 _private* method_ `static XmlSchemaType CreateIncludeType()` — Creates the schema type representing an include type
- L766-776 _private* method_ `static XmlSchemaType CreateOptionType()` — Creates the schema type representing a parameter type
- L782-789 _private* method_ `static XmlSchemaType CreateEnvVarType()` — Creates the schema type representing a environment variable type
- L795-813 _private* method_ `static XmlSchemaType CreatePropertyType()` — Creates the schema type representing a property type
- L819-837 _private* method_ `static XmlSchemaType CreateRegexType()` — Creates the schema type representing a regex type
- L843-861 _private* method_ `static XmlSchemaType CreateStringOpType()` — Creates the schema type representing a stringop type
- L867-882 _private* method_ `static XmlSchemaType CreateMacroType()` — Creates the schema type representing the macro type
- L888-930 _private* method_ `static XmlSchemaType CreateMacroBodyType(Dictionary<string, XmlSchemaComplexType> taskNameToType)` — Creates the schema type representing the macro type
- L936-949 _private* method_ `static XmlSchemaType CreateExtendType()` — Creates the schema type representing the macro type
- L955-966 _private* method_ `static XmlSchemaType CreateExpandType()` — Creates the schema type representing a macro expansion
- L972-981 _private* method_ `static XmlSchemaType CreateDiagnosticType(ScriptSchemaStandardType standardType)` — Creates the schema type representing a warning or error type
- L988-1004 _private* method_ `static XmlSchemaElement CreateDoElement(ScriptSchemaStandardType innerType)` — Creates an element representing a conditional "Do" block, which recursively contains another type
- L1011-1049 _private* method_ `static XmlSchemaElement CreateSwitchElement(ScriptSchemaStandardType innerType)` — Creates an element representing a conditional "Switch" block, which recursively contains another type
- L1056-1075 _private* method_ `static XmlSchemaElement CreateForEachElement(ScriptSchemaStandardType innerType)` — Creates an element representing a conditional "ForEach" block, which recursively contains another type
- L1083-1086 _private* method_ `static XmlSchemaElement CreateSchemaElement(string name, ScriptSchemaStandardType schemaType)` — Constructs an XmlSchemaElement and initializes it with the given parameters
- L1094-1100 _private* method_ `static XmlSchemaElement CreateSchemaElement(string name, XmlQualifiedName schemaTypeName)` — Constructs an XmlSchemaElement and initializes it with the given parameters
- L1109-1112 _private* method_ `static XmlSchemaAttribute CreateSchemaAttribute(string name, ScriptSchemaStandardType schemaType, XmlSchemaUse use)` — Constructs an XmlSchemaAttribute and initialize it with the given parameters
- L1121-1128 _private* method_ `static XmlSchemaAttribute CreateSchemaAttribute(string name, XmlQualifiedName schemaTypeName, XmlSchemaUse use)` — Constructs an XmlSchemaAttribute and initialize it with the given parameters
- L1136-1148 _private* method_ `static XmlSchemaSimpleType CreateSimpleTypeFromUnion(string name, params XmlSchemaType[] validTypes)` — Creates a simple type that is the union of two other types
- L1156-1169 _private* method_ `static XmlSchemaSimpleType CreateSimpleTypeFromRegex(string? name, string pattern)` — Creates a simple type that matches a regex
- L1176-1186 _private* method_ `static XmlSchemaType CreateUserType(string name, Type type)` — Create a schema type for the given user type. Currently only handles enumerations.
- L1193-1209 _private* method_ `static XmlSchemaType CreateEnumType(string? name, Type type)` — Create a schema type for the given enum.

### `Source/Programs/AutomationTool/BuildGraph/BgScriptNode.cs` (BuildGraph.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/BuildGraph/BgScriptReader.cs` (BuildGraph.Automation)


#### class `AutomationTool.BgScriptLocation`  
`public class BgScriptLocation`  
_public; L25-47_
- desc: Location of an element within a file
- L30 _public property_ `public FileReference File { get; }` — The file containing this element
- L35 _public property_ `public int LineNumber { get; }` — The line number containing this element
- L42-46 _public ctor_ `public BgScriptLocation(FileReference file, int lineNumber)` — Constructor

#### class `AutomationTool.BgScriptDocument`  
`public class BgScriptDocument : XmlDocument`  
_public; L52-178_
- inherits: `XmlDocument`
- desc: Implementation of XmlDocument which preserves line numbers for its elements
- L57 _private* property_ `FileReference File { get; }` — The file being read
- L62 _private* field_ `IXmlLineInfo? _lineInfo` — Interface to the LineInfo on the active XmlReader
- L67 _private* field_ `bool _hasErrors` — Set to true if the reader encounters an error
- L72 _private* property_ `ILogger Logger { get; }` — Logger for validation errors
- L77-81 _private* ctor_ `BgScriptDocument(FileReference file, ILogger logger)` — Private constructor. Use ScriptDocument.Load to read an XML document.
- L86-90 _public method_ `public override XmlElement CreateElement(string? prefix, string? localName, string? namespaceUri)` — Overrides XmlDocument.CreateElement() to construct ScriptElements rather than XmlElements
- L101-158 _public method_ `public static bool TryRead(FileReference file, byte[] data, BgScriptSchema? schema, ILogger logger, [NotNullWhen(true)] out BgScriptDocument? outDocument)` — Loads a script document from the given file
- L165-177 _private* method_ `void ValidationEvent(object? sender, ValidationEventArgs args)` — Callback for validation errors in the document

#### class `AutomationTool.BgScriptElement`  
`public class BgScriptElement : XmlElement`  
_public; L183-198_
- inherits: `XmlElement`
- desc: Implementation of XmlElement which preserves line numbers
- L188 _public property_ `public BgScriptLocation Location { get; }` — Location of the element within the file
- L193-197 _public ctor_ `public BgScriptElement(BgScriptLocation location, string prefix, string localName, string namespaceUri, BgScriptDocument document) : base(prefix, localName, namespaceUri, document)` — Constructor

#### class `AutomationTool.BgScriptMacro`  
`class BgScriptMacro`  
_internal*; L203-245_
- desc: Stores information about a script function that has been declared
- L208 _public property_ `public string Name { get; }` — Name of the function
- L213 _public property_ `public List<BgScriptElement> Elements { get; }` — Element where the function was declared
- L218 _public property_ `public int NumArguments { get; }` — The total number of arguments
- L223 _public property_ `public int NumRequiredArguments { get; }` — Number of arguments that are required
- L228 _public property_ `public IReadOnlyDictionary<string, int> ArgumentNameToIndex { get; }` — Maps an argument name to its type
- L237-244 _public ctor_ `public BgScriptMacro(string name, BgScriptElement element, Dictionary<string, int> argumentNameToIndex, int numRequiredArguments)` — Constructor

#### class `AutomationTool.BgScriptExtensions`  
`public static class BgScriptExtensions`  
_public; L250-281_
- desc: Extension methods for writing script error messages
- L255-265 _public method_ `public static void LogScriptError(this ILogger logger, BgScriptLocation location, string format, params object[] args)` — Utility method to log a script error at a particular location
- L270-280 _public method_ `public static void LogScriptWarning(this ILogger logger, BgScriptLocation location, string format, params object[] args)` — Utility method to log a script warning at a particular location

#### class `AutomationTool.BgScriptNode`  
`class BgScriptNode : BgNodeDef`  
_internal*; L286-300_
- inherits: `BgNodeDef`
- desc: Overridden version of BgNodeDef which contains a list of tasks
- L291 _public property_ `public List<BgTask> Tasks { get; }` — List of tasks to execute
- L296-299 _public ctor_ `public BgScriptNode(string name, IReadOnlyList<BgNodeOutput> inputs, IReadOnlyList<BgNodeOutput> optionalInputs, IReadOnlyList<string> outputNames, IReadOnlyList<BgNodeDef> inputDependencies, IReadOnlyList<BgNodeDef> optionalInputDependencies, IReadOnlyList<BgNodeDef> orderDependencies, IReadOnlyList<FileReference> requiredTokens, IReadOnlyList<string> ignoreModified) : base(name, inputs, optionalInputs, outputNames, inputDependencies, optionalInputDependencies, orderDependencies, requiredTokens, ignoreModified)` — Constructor

#### class `AutomationTool.BgScriptReader`  
`public class BgScriptReader`  
_public; L305-2540_
- desc: Reader for build graph definitions. Instanced to contain temporary state; public interface is through ScriptReader.TryRead().
- L310 _private* field_ `readonly DirectoryReference _rootDir` — Root directory to resolve relative paths against
- L316 _protected property_ `protected List<Dictionary<string, string?>> ScopedProperties { get; }` — List of property name to value lookups. Modifications to properties are scoped to nodes and agents. EnterScope() pushes an empty dictionary onto the end of this list, and LeaveScope() removes one. ExpandProperties() searches from last to first lookup when trying to resolve a property name, and takes the first it finds.
- L322 _private* field_ `readonly List<HashSet<string>> _shadowProperties = new List<HashSet<string>>()` — When declaring a property in a nested scope, we enter its name into a set for each parent scope which prevents redeclaration in an OUTER scope later. Subsequent NESTED scopes can redeclare it. The former is likely a coding error, since it implies that the scope of the variable was meant to be further out, whereas the latter is common for temporary and loop variables.
- L327 _private* field_ `readonly Dictionary<string, BgScriptMacro> _macroNameToDefinition = ...` — Maps from a function name to its definition
- L327 _private* field_ `readonly Dictionary< _macroNameToDefinition = new Dictionary<string, BgScriptMacro>()` — Maps from a function name to its definition
- L333 _private* field_ `readonly HashSet<FileReference> _includedScripts = new HashSet<FileReference>()` — Set of scripts that have been previously read via an include element This is used to prevent duplicate reads of a script if it has been guarded against
- L338 _private* field_ `readonly BgGraphDef _graph = new BgGraphDef()` — The current graph
- L343 _private* field_ `readonly Dictionary<string, string> _arguments` — Arguments for evaluating the graph
- L343 _private* field_ `readonly Dictionary< _arguments` — Arguments for evaluating the graph
- L348 _private* field_ `readonly string? _singleNodeName` — The name of the node if only a single node is going to be built, otherwise null.
- L353 _private* property_ `BgScriptSchema? Schema { get; }` — Schema for the script
- L358 _protected property_ `protected ILogger Logger { get; }` — Logger for diagnostic messages
- L363 _public property_ `public int NumErrors { get; set; }` — The number of errors encountered during processing so far
- L365 _private* field_ `BgAgentDef? _enclosingAgent`
- L366 _private* field_ `BgScriptNode? _enclosingNode`
- L377-393 _protected ctor_ `protected BgScriptReader(DirectoryReference rootDir, IDictionary<string, string?> defaultProperties, IReadOnlyDictionary<string, string> arguments, string? singleNodeName, BgScriptSchema? schema, ILogger logger)` — Private constructor. Use ScriptReader.TryRead() to read a script file.
- L406-442 _public method_ `public static async Task<BgGraphDef?> ReadAsync(FileReference file, DirectoryReference rootDir, Dictionary<string, string> arguments, Dictionary<string, string?> defaultProperties, BgScriptSchema? schema, ILogger logger, string? singleNodeName = null)` — Try to read a script file from the given file.
- L448-472 _protected method_ `protected async Task<bool> TryReadAsync(FileReference file)` — Read the script from the given file
- L478-558 _private* method_ `async Task ReadGraphBodyAsync(XmlElement element)` — Reads the contents of a graph
- L563-567 _protected method_ `protected void EnterScope()` — Push a new property scope onto the stack
- L572-576 _protected method_ `protected void LeaveScope()` — Pop a property scope from the stack
- L585-626 _protected method_ `protected void SetPropertyValue(BgScriptElement element, string name, string? value, bool createInParentScope = false)` — Sets a property value in the current scope
- L634-672 _protected method_ `protected bool TryGetPropertyValue(string name, out string? value)` — Tries to get the value of a property
- L678-731 _private* method_ `async Task ReadIncludeAsync(BgScriptElement element)` — Read an include directive, and the contents of the target file
- L736-769 _private* method_ `static string? CombinePaths(string basePath, string nextPath)` — Combine two paths without validating the result
- L774-780 _private* method_ `static IEnumerable<FileReference> FindMatchingFiles(DirectoryReference rootDir, string pattern)` — Find files matching a pattern
- L786-844 _private* method_ `async Task ReadOptionAsync(BgScriptElement element)` — Reads the definition of a graph option; a parameter which can be set by the user on the command-line or via an environment variable.
- L850-921 _private* method_ `async Task ReadPropertyAsync(BgScriptElement element)` — Reads a property assignment.
- L927-975 _private* method_ `async Task ReadRegexAsync(BgScriptElement element)` — Reads a Regex assignment.
- L981-1041 _private* method_ `async Task ReadStringOpAsync(BgScriptElement element)` — Reads a StringOp element and applies string method.
- L1047-1065 _private* method_ `async Task ReadEnvVarAsync(BgScriptElement element)` — Reads a property assignment from an environment variable.
- L1071-1093 _private* method_ `void ReadMacro(BgScriptElement element)` — Reads a macro definition
- L1101-1118 _private* method_ `void ReadMacroArguments(BgScriptElement element, string attributeName, Dictionary<string, int> argumentNameToIndex)` — Reads a list of macro arguments from an attribute
- L1124-1140 _private* method_ `async Task ReadExtendAsync(BgScriptElement element)` — Reads a macro definition
- L1146-1183 _private* method_ `async Task ReadAgentAsync(BgScriptElement element)` — Reads the definition for an agent.
- L1189-1247 _protected method_ `protected async Task ReadAgentBodyAsync(BgScriptElement element)` — Read the contents of an agent definition
- L1253-1308 _private* method_ `async Task ReadAggregateAsync(BgScriptElement element)` — Reads the definition for an aggregate
- L1314-1353 _private* method_ `async Task ReadArtifactAsync(BgScriptElement element)` — Reads the definition for an artifact
- L1359-1374 _private* method_ `async Task ReadReportAsync(BgScriptElement element)` — Reads the definition for a report
- L1380-1402 _private* method_ `async Task ReadBadgeAsync(BgScriptElement element)` — Reads the definition for a badge
- L1408-1448 _private* method_ `async Task ReadLabelAsync(BgScriptElement element)` — Reads the definition for a label
- L1454-1610 _private* method_ `async Task ReadNodeAsync(BgScriptElement element)` — Reads the definition for a node, and adds it to the given agent
- L1616-1659 _protected method_ `protected async Task ReadNodeBodyAsync(XmlElement element)` — Reads the contents of a node element
- L1666-1672 _private* method_ `async Task ReadBlockAsync(BgScriptElement element, Func<BgScriptElement, Task> readContentsAsync)` — Reads a block element
- L1679-1689 _private* method_ `async Task ReadSwitchAsync(BgScriptElement element, Func<BgScriptElement, Task> readContentsAsync)` — Reads a "Switch" element
- L1696-1731 _private* method_ `async Task ReadForEachAsync(BgScriptElement element, Func<BgScriptElement, Task> readContentsAsync)` — Reads a "ForEach" element
- L1738-1798 _private* method_ `async Task ReadExpandAsync(BgScriptElement element, Func<BgScriptElement, Task> readContentsAsync)` — Reads an "Expand" element
- L1804-1834 _private* method_ `async Task ReadTaskAsync(BgScriptElement element)` — Reads a task definition from the given element, and add it to the given list
- L1836-1860 _private* method_ `void AddArtifactFromTask(BgScriptElement element, Dictionary<string, string> arguments)`
- L1862-1891 _private* method_ `void AddCloudArtifactFromTask(BgScriptElement element, Dictionary<string, string> arguments)`
- L1897-1984 _private* method_ `async Task ReadNotifierAsync(BgScriptElement element)` — Reads the definition for an email notifier
- L1990-2043 _private* method_ `async Task ReadAnnotationAsync(BgScriptElement element)` — Reads a graph annotation
- L2050-2072 _private* method_ `async Task ReadDiagnosticAsync(BgScriptElement element, LogLevel level)` — Reads a warning from the given element, evaluates the condition on it, and writes it to the log if the condition passes.
- L2080-2101 _protected method_ `protected bool TryReadObjectName(BgScriptElement element, [NotNullWhen(true)] out string? name)` — Reads an object name from its defining element. Outputs an error if the name is missing.
- L2109-2118 _private* method_ `bool CheckNameIsUnique(BgScriptElement element, string name)` — Checks that the given name does not already used to refer to a node, and print an error if it is.
- L2126-2146 _private* method_ `HashSet<BgNodeDef> ResolveReferences(BgScriptElement element, IEnumerable<string> referenceNames)` — Resolve a list of references to a set of nodes
- L2154-2174 _private* method_ `HashSet<BgNodeOutput> ResolveInputReferences(BgScriptElement element, IEnumerable<string> referenceNames)` — Resolve a list of references to a set of nodes
- L2182-2206 _protected method_ `protected bool ValidateName(BgScriptElement element, string name)` — Checks that the given name is valid syntax
- L2214-2230 _protected method_ `protected Regex? ParseRegex(BgScriptElement element, string regex)` — Constructs a regex from a regex string and returns it
- L2238-2241 _protected method_ `protected string ReadAttribute(BgScriptElement element, string name)` — Expands any properties and reads an attribute.
- L2250-2258 _protected method_ `protected string[] ReadListAttribute(BgScriptElement element, string name, char separator = ';')` — Expands any properties and reads a list of strings from an attribute, separated by semi-colon characters
- L2266-2270 _protected method_ `protected Dictionary<string, string> ReadAnnotationsAttribute(BgScriptElement element, string name)` — Parse a map of annotations
- L2293-2320 _private method_ `private static string[] SplitIgnoreSeparatorInQuotes(string value, char separator = ';')` — Split string with given separator into a list of strings while ignoring any separators within quotes
- L2328-2359 _private method_ `private Dictionary<string, string> ParseAnnotations(BgScriptElement element, string[] pairs)` — Parse a map of annotations
- L2368-2388 _protected method_ `protected bool ReadBooleanAttribute(BgScriptElement element, string name, bool defaultValue)` — Reads an attribute from the given XML element, expands any properties in it, and parses it as a boolean.
- L2397-2415 _protected method_ `protected int ReadIntegerAttribute(BgScriptElement element, string name, int defaultValue)` — Reads an attribute from the given XML element, expands any properties in it, and parses it as an integer.
- L2425-2443 _protected method_ `protected T ReadEnumAttribute<T>(BgScriptElement element, string name, T defaultValue) where T : struct` — Reads an attribute from the given XML element, expands any properties in it, and parses it as an enum of the given type.
- L2451-2455 _protected method_ `protected void LogError(BgScriptElement element, string format, params object[] args)` — Outputs an error message to the log and increments the number of errors, referencing the file and line number of the element that caused it.
- L2463-2466 _protected method_ `protected void LogWarning(BgScriptElement element, string format, params object[] args)` — Outputs a warning message to the log, referencing the file and line number of the element that caused it.
- L2473-2493 _protected method_ `protected async Task<bool> EvaluateConditionAsync(BgScriptElement element)` — Evaluates the (optional) conditional expression on a given XML element via the If="..." attribute, and returns true if the element is enabled.
- L2501-2533 _protected method_ `protected string ExpandProperties(BgScriptElement element, string text)` — Expand all the property references (of the form $(PropertyName)) in a string.
- L2536-2539 _public method_ `public static object GetNativePath(DirectoryReference rootDir, string path)` — (inheritdoc)

### `Source/Programs/AutomationTool/BuildGraph/BgScriptWriter.cs` (BuildGraph.Automation)


#### class `AutomationTool.BgScriptWriter`  
`public static class BgScriptWriter`  
_public; L17-198_
- desc: Implementation of XmlDocument which preserves line numbers for its elements
- L25-117 _public method_ `public static void Write(this BgGraphDef graph, FileReference file, FileReference? schemaFile)` — Writes a preprocessed build graph to a script file
- L124-134 _public method_ `public static void Write(this BgAgentDef agent, XmlWriter writer)` — Writes this agent group out to a file, filtering nodes by a controlling trigger
- L141-197 _public method_ `public static void Write(this BgNodeDef node, XmlWriter writer)` — Write this node to an XML writer

### `Source/Programs/AutomationTool/BuildGraph/BgTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.BgTask`  
`public class BgTask`  
_public; L13-52_
- desc: A task invocation
- L18 _public property_ `public BgScriptLocation Location { get; }` — Line number in a source file that this task was declared. Optional; used for log messages.
- L23 _public property_ `public string Name { get; set; }` — Name of the task
- L28 _public property_ `public Dictionary<string, string> Arguments { get; }` — Arguments for the task
- L33-37 _public ctor_ `public BgTask(BgScriptLocation location, string name)` — Constructor
- L43-51 _public method_ `public void Write(XmlWriter writer)` — Write to an xml file

### `Source/Programs/AutomationTool/BuildGraph/BuildGraph.cs` (BuildGraph.Automation)


#### class `AutomationTool.ScriptTaskParameterBinding`  
`abstract class ScriptTaskParameterBinding : BgScriptTaskParameter`  
_internal*; L30-42_
- inherits: `BgScriptTaskParameter`
- desc: Implementation of ScriptTaskParameter corresponding to a field in a parameter class
- L32 _public property_ `public abstract Type ParameterType { get; }`
- L34-37 _public ctor_ `public ScriptTaskParameterBinding(string name, Type valueType, TaskParameterValidationType validationType, bool optional) : base(name, valueType, validationType, optional)`
- L39 _public method_ `public abstract string GetXmlDocName()`
- L40 _public method_ `public abstract object? GetValue(object sourceObject)`
- L41 _public method_ `public abstract void SetValue(object targetObject, object? value)`

#### class `AutomationTool.ScriptTaskParameterPropertyBinding`  
`class ScriptTaskParameterPropertyBinding : ScriptTaskParameterBinding`  
_internal*; L44-65_
- inherits: `ScriptTaskParameterBinding`
- L46 _private* field_ `readonly PropertyInfo _propertyInfo`
- L48-52 _public ctor_ `public ScriptTaskParameterPropertyBinding(string name, PropertyInfo propertyInfo, TaskParameterValidationType validationType, bool optional) : base(name, propertyInfo.PropertyType, validationType, optional)`
- L54 _public property_ `public override Type ParameterType => ...`
- L57 _public method_ `public override string GetXmlDocName()`
- L60 _public method_ `public override object? GetValue(object sourceObject)`
- L63 _public method_ `public override void SetValue(object targetObject, object? value)`

#### class `AutomationTool.ScriptTaskParameterFieldBinding`  
`class ScriptTaskParameterFieldBinding : ScriptTaskParameterBinding`  
_internal*; L67-88_
- inherits: `ScriptTaskParameterBinding`
- L69 _private* field_ `readonly FieldInfo _fieldInfo`
- L71-75 _public ctor_ `public ScriptTaskParameterFieldBinding(string name, FieldInfo fieldInfo, TaskParameterValidationType validationType, bool optional) : base(name, fieldInfo.FieldType, validationType, optional)`
- L77 _public property_ `public override Type ParameterType => ...`
- L80 _public method_ `public override string GetXmlDocName()`
- L83 _public method_ `public override object? GetValue(object sourceObject)`
- L86 _public method_ `public override void SetValue(object targetObject, object? value)`

#### class `AutomationTool.ScriptTaskBinding`  
`class ScriptTaskBinding : BgScriptTask`  
_internal*; L93-156_
- inherits: `BgScriptTask`
- desc: Binding of a ScriptTask to a Script
- L98 _public property_ `public Type TaskClass { get; }` — Type of the task to construct with this info
- L103 _public property_ `public Type ParametersClass { get; }` — Type to construct with the parsed parameters
- L108 _public property_ `public IReadOnlyDictionary<string, ScriptTaskParameterBinding> NameToParameter { get; }` — Map from name to parameter
- L116-119 _public ctor_ `public ScriptTaskBinding(string name, Type taskClass, Type parametersClass) : this(name, taskClass, parametersClass, CreateParameters(parametersClass))` — Constructor
- L124-130 _private ctor_ `private ScriptTaskBinding(string name, Type taskClass, Type parametersClass, List<ScriptTaskParameterBinding> parameters) : base(name, parameters.ConvertAll<BgScriptTaskParameter>(x => x))` — Private constructor
- L132-155 _private* method_ `static List<ScriptTaskParameterBinding> CreateParameters(Type parametersClass)`

#### class `AutomationTool.BuildGraph`  
`public class BuildGraph : BuildCommand`  
_public; L216-1662_
- attrs: `[Help("Tool for creating extensible build processes in UE which can be run locally or in parallel across a build farm.")] [ParamHelp("Script=<FileName>", "Path to the script describing the graph", ParamType = typeof(File), Required = true)] [ParamHelp("Target=<Name>", "Name of the node or output tag to be built")] [ParamHelp("Schema", "Generates a schema to the default location", ParamType = typeo`
- inherits: `BuildCommand`
- desc: Tool to execute build automation scripts for UE projects, which can be run locally or in parallel across a build farm (assuming synchronization and resource allocation implemented by a separate system). Build graphs are declared using an XML script using syntax similar to MSBuild, ANT or NAnt, and consist of the following components: - Tasks: Building blocks which can be executed as part of the build process. Many predefined tasks are provided ('Cook', 'Compile', 'Copy', 'Stage', 'Log', 'PakFile', etc...), and additional tasks may be added be declaring classes derived from AutomationTool.BuildTask in other UAT modules. - Nodes: A named sequence of tasks which are executed in order to produce outputs. Nodes may have dependencies on other nodes for their outputs before they can be executed. Declared with the 'Node' element. - Agents: A machine which can execute a sequence of nodes, if running as part of a build system. Has no effect when building locally. Declared with the 'Agent' elemen
- L221-763 _public method_ `public override async Task<ExitCode> ExecuteAsync()` — Main entry point for the BuildGraph command
- L765-776 _private* method_ `static async ValueTask<bool> BindNodesAsync(BgGraphDef graph, Dictionary<string, ScriptTaskBinding> nameToTask, Dictionary<BgNodeDef, BgNodeExecutor> nodeToExecutor)`
- L778-796 _private* method_ `static async ValueTask<bool> BindNodesAsync(BgNodeDef node, Dictionary<string, ScriptTaskBinding> nameToTask, Dictionary<string, BgNodeOutput> tagNameToNodeOutput, Dictionary<BgNodeDef, BgNodeExecutor> nodeToExecutor)`
- L798-821 _private* method_ `static void FindAvailableGraphs(Dictionary<string, Type> nameToType)`
- L828-868 _private* method_ `static bool FindAvailableTasks(Dictionary<string, ScriptTaskBinding> nameToTask, bool publicTasksOnly)` — Find all the tasks which are available from the loaded assemblies
- L874-877 _public method_ `public static string? ReadTokenFile(FileReference location)` — Reads the contents of the given token
- L883-938 _public method_ `public static bool WriteTokenFile(FileReference location, string signature)` — Attempts to write an owner to a token file transactionally
- L945-957 _private* method_ `static bool IsPublicAssembly(FileReference file)` — Checks whether the given assembly is a publically distributed engine assembly.
- L964-975 _private* method_ `static HashSet<BgNodeDef> FindCompletedNodes(BgGraphDef graph, TempStorage storage)` — Find all the nodes in the graph which are already completed
- L985-1052 _private* method_ `async Task<bool> BuildAllNodesAsync(BgGraphDef graph, Dictionary<BgNodeDef, BgNodeExecutor> nodeToExecutor, TempStorage storage, bool ignoreOptionalNodeFailures)` — Builds all the nodes in the graph
- L1106-1357 _private* method_ `async Task<bool> BuildNodeAsync(BgGraphDef graph, BgNodeDef node, Dictionary<BgNodeDef, BgNodeExecutor> nodeToExecutor, TempStorage storage, bool withBanner)` — Build a node
- L1362-1366 _private* method_ `static string? GetEnvVarOrNull(string name)` — Gets an environment variable, returning null if it's not set or empty.
- L1371-1379 _private* method_ `static int? GetEnvVarIntOrNull(string name)` — Gets an environment variable as an integer, returning null if it's not set or empty.
- L1386-1434 _private* method_ `static void WriteDocumentation(Dictionary<string, ScriptTaskBinding> nameToTask, FileReference outputFile)` — Generate HTML documentation for all the tasks
- L1442-1541 _private* method_ `static void WriteDocumentationUdn(Dictionary<string, ScriptTaskBinding> nameToTask, Dictionary<string, XmlElement> memberNameToElement, FileReference outputFile)` — Writes documentation to a UDN file
- L1549-1633 _private* method_ `static void WriteDocumentationHtml(Dictionary<string, ScriptTaskBinding> nameToTask, Dictionary<string, XmlElement> memberNameToElement, FileReference outputFile)` — Writes documentation to an HTML file
- L1640-1661 _private* method_ `static string ConvertToMarkdown(XmlNode node)` — Converts an XML documentation node to markdown

#### class `AutomationTool.BuildGraph.CleanupScriptRunner`  
`class CleanupScriptRunner : IDisposable`  
_private*; L1057-1095_
- inherits: `IDisposable`
- desc: Helper class to execute a cleanup script on termination
- L1059 _private* field_ `readonly ILogger _logger`
- L1060 _private* field_ `readonly FileReference? _scriptFile`
- L1062-1074 _public ctor_ `public CleanupScriptRunner(ILogger logger)`
- L1076-1094 _public method_ `public void Dispose()`

#### class `AutomationTool.Build`  
`public class Build : BuildGraph`  
_public; L1667-1669_
- inherits: `BuildGraph`
- desc: Legacy command name for compatibility.

### `Source/Programs/AutomationTool/BuildGraph/JobContext.cs` (BuildGraph.Automation)


#### class `AutomationTool.JobContext`  
`public class JobContext`  
_public; L10-40_
- desc: Used to pass information to tasks about the currently running job.
- L15 _public property_ `public string CurrentNode { get; }` — The current node name
- L20 _public property_ `public BuildCommand OwnerCommand { get; }` — The command that is running the current job.
- L26-28 _public ctor_ `public JobContext(BuildCommand inOwnerCommand) : this("Unknown", inOwnerCommand)` — Constructor
- L35-39 _public ctor_ `public JobContext(string inCurrentNode, BuildCommand inOwnerCommand)` — Constructor

### `Source/Programs/AutomationTool/BuildGraph/Properties/AssemblyInfo.cs` (BuildGraph.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/BuildGraph/Scripts/InstalledBuild.cs` (BuildGraph.Automation)


#### class `AutomationTool.InstalledBuild`  
`class InstalledBuild : BgGraphBuilder`  
_internal*; L19-484_
- inherits: `BgGraphBuilder`
- L21 _private* property_ `static FileSet Workspace { get; }`
- L22 _private* property_ `static DirectoryReference RootDir { get; }`
- L23 _private* property_ `static DirectoryReference IntermediateDir => ...`
- L24 _private* property_ `static DirectoryReference TempMiscDir => ...`
- L25 _private* property_ `static DirectoryReference TempCsToolsDir => ...`
- L26 _private* property_ `static DirectoryReference TempDdcDir => ...`
- L42 _private* field_ `static readonly string[] s_winStripFilter = { "*.pdb", "-/Engine/Binaries/Win64/UnrealEditor*.pdb", "-/Engine/Plugins/.../Binaries/Win64/UnrealEditor*.pdb", }`
- L49-76 _private* method_ `static List<string> GetDdcProjects(UnrealTargetPlatform platform)`
- L78-214 _public method_ `public override BgGraph CreateGraph()`
- L219-225 _private* method_ `static async Task UpdateVersionFilesAsync(BgContext state)` — Update the build version
- L231-266 _private* method_ `static async Task<BgFileSet> CompileUnrealEditorWin64Async(BgContext state, BgString crashReporterCompileArgs, BgBool embedSrcSrvInfo, BgBool compileDatasmithPlugins, BgBool withFullDebugInfo, BgBool signExecutables)` — attrs: `[BgNodeName("Compile UnrealEditor Win64")]` — Builds the Windows editor
- L272-288 _private* method_ `static async Task<BgFileSet> CompileUnrealGameWin64Async(BgContext state, BgList<BgEnum<UnrealTargetConfiguration>> configurations, BgBool embedSrcSrvInfo, BgBool withFullDebugInfo, BgBool signExecutables)` — attrs: `[BgNodeName("Compile UnrealGame Win64")]` — Builds the game target
- L290-299 _private* method_ `static async Task<BgFileSet> CompileRulesAssembliesAsync(BgContext state)`
- L301-327 _private* method_ `static async Task<BgFileSet> BuildToolsWin64Async(BgContext state, BgString crashReporterCompileArgs)`
- L330-368 _private* method_ `static async Task<BgFileSet> BuildToolsCsAsync(BgContext state, BgBool signExecutables)` — attrs: `[BgNodeName("Build Tools CS")]`
- L374-413 _private* method_ `static async Task<BgFileSet> BuildDdcWin64Async(BgContext state, BgList<BgString> platforms, BgList<BgFileSet> dependencies)` — attrs: `[BgNodeName("Build DDC Win64")]` — Creates a DDC pack file for the supported platforms
- L419-456 _private* method_ `static async Task<BgFileSet> MakeInstalledBuildWin64Async(BgContext state, BgList<BgFileSet> inputFiles, BgString finalizeArgs, BgString outputDir)` — attrs: `[BgNodeName("Make Installed Build Win64")]` — Copy all the build artifacts to the output folder
- L458-483 _private* method_ `static void MapFilesToOutputDir(IEnumerable<FileReference> sourceFiles, DirectoryReference targetDir, Dictionary<FileReference, FileReference> targetFileToSourceFile)`

### `Source/Programs/AutomationTool/BuildGraph/Task.cs` (BuildGraph.Automation)


#### class `AutomationTool.TaskParameterAttribute`  
`public sealed class TaskParameterAttribute : Attribute`  
_public; L24-43_
- attrs: `[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attribute to mark parameters to a task, which should be read as XML attributes from the script file.
- L29-33 _public property_ `public bool Optional { get; set; }` — Whether the parameter can be omitted
- L38-42 _public property_ `public TaskParameterValidationType ValidationType { get; set; }` — Sets additional restrictions on how this field is validated in the schema. Default is to allow any valid field type.

#### class `AutomationTool.TaskElementAttribute`  
`public sealed class TaskElementAttribute : Attribute`  
_public; L49-71_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute used to associate an XML element name with a parameter block that can be used to construct tasks
- L54 _public property_ `public string Name { get; }` — Name of the XML element that can be used to denote this class
- L59 _public property_ `public Type ParametersType { get; }` — Type to be constructed from the deserialized element
- L66-70 _public ctor_ `public TaskElementAttribute(string name, Type parametersType)` — Constructor

#### interface `AutomationTool.ITaskExecutor`  
`public interface ITaskExecutor`  
_public; L77-94_
- desc: Proxy to handle executing multiple tasks simultaneously (such as compile tasks). If a task supports simultaneous execution, it can return a separate executor an executor instance from GetExecutor() callback. If not, it must implement ExecuteAsync().
- L84 _public* method_ `bool Add(BgTaskImpl task)` — Adds another task to this executor
- L93 _public* method_ `Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync all the tasks added to this executor.

#### class `AutomationTool.BgTaskImpl`  
`public abstract class BgTaskImpl`  
_public; L99-504_
- desc: Base class for all custom build tasks
- L104 _protected property_ `protected static ILogger Logger => ...` — Accessor for the default log interface
- L109 _public property_ `public BgScriptLocation? SourceLocation { get; set; }` — Line number in a source file that this task was declared. Optional; used for log messages.
- L118 _public method_ `public abstract Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync this node.
- L124-127 _public method_ `public virtual ITaskExecutor? GetExecutor()` — Creates a proxy to execute this node.
- L132 _public method_ `public abstract void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L139-173 _protected method_ `protected void Write(XmlWriter writer, object parameters)` — Writes this task to an XML writer, using the given parameters object.
- L178-186 _public method_ `public string GetTraceString()` — Returns a string used for trace messages
- L192-196 _public method_ `public virtual string GetTraceName()` — Gets the name of this task for tracing
- L203-210 _public method_ `public virtual void GetTraceMetadata(ITraceSpan span, string prefix)` — Get properties to include in tracing info
- L217-224 _public method_ `public virtual void GetTraceMetadata(ISpan span, string prefix)` — Get properties to include in tracing info
- L230 _public method_ `public abstract IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L236 _public method_ `public abstract IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task
- L243-255 _protected method_ `protected static IEnumerable<string> FindTagNamesFromFilespec(string filespec)` — Adds tag names from a filespec
- L262-271 _protected method_ `protected static IEnumerable<string> FindTagNamesFromList(string? tagList)` — Enumerates tag names from a list
- L278-288 _public method_ `public static FileReference ResolveFile(string name)` — Resolves a single name to a file reference, resolving relative paths to the root of the current path.
- L295-309 _public method_ `public static DirectoryReference ResolveDirectory(string? name)` — Resolves a directory reference from the given string. Assumes the root directory is the root of the current branch.
- L317-347 _public method_ `public static HashSet<FileReference> FindOrAddTagSet(Dictionary<string, HashSet<FileReference>> tagNameToFileSet, string tagName)` — Finds or adds a set containing files with the given tag
- L361-365 _public method_ `public static HashSet<FileReference> ResolveFilespec(DirectoryReference defaultDirectory, string delimitedPatterns, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Resolve a list of files, tag names or file specifications separated by semicolons. Supported entries may be: a) The name of a tag set (eg. #CompiledBinaries) b) Relative or absolute filenames c) A simple file pattern (eg. Foo/*.cpp) d) A full directory wildcard (eg. Engine/...) Note that wildcards may only match the last fragment in a pattern, so matches like "/*/Foo.txt" and "/.../Bar.txt" are illegal.
- L375-380 _public method_ `public static HashSet<FileReference> ResolveFilespecWithExcludePatterns(DirectoryReference defaultDirectory, string delimitedPatterns, List<string> excludePatterns, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Resolve a list of files, tag names or file specifications separated by semicolons as above, but preserves any directory references for further processing.
- L390-440 _public method_ `public static HashSet<FileReference> ResolveFilespecWithExcludePatterns(DirectoryReference defaultDirectory, List<string> filePatterns, List<string> excludePatterns, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Resolve a list of files, tag names or file specifications as above, but preserves any directory references for further processing.
- L447-450 _public method_ `public static List<string> SplitDelimitedList(string text)` — Splits a string separated by semicolons into a list, removing empty entries
- L455 _public const_ `public const string CleanupScriptEnvVarName = "UE_HORDE_CLEANUP"` — Name of the environment variable containing cleanup commands
- L460 _public const_ `public const string LeaseCleanupScriptEnvVarName = "UE_HORDE_LEASE_CLEANUP"` — Name of the environment variable containing lease cleanup commands
- L467-475 _public method_ `public static async Task AddCleanupCommandsAsync(IEnumerable<string> newLines, bool lease = false)` — Add cleanup commands to run after the step completes
- L480 _public const_ `public const string GraphUpdateEnvVarName = "UE_HORDE_GRAPH_UPDATE"` — Name of the environment variable containing a file to write Horde graph updates to
- L486-503 _public method_ `public static void UpdateGraphForHorde(JobContext job)` — Updates the graph currently used by Horde

#### class `AutomationTool.CustomTask`  
`public abstract class CustomTask : BgTaskImpl`  
_public; L509-526_
- inherits: `BgTaskImpl`
- desc: Legacy implementation of BgTaskImpl which operates synchronously
- L512-516 _public method_ `public sealed override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — (inheritdoc)
- L525 _public method_ `public abstract void Execute(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync this node.

### `Source/Programs/AutomationTool/BuildGraph/Tasks/AgeStoreTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.AgeStoreTaskParameters`  
`public class AgeStoreTaskParameters`  
_public; L18-51_
- desc: Parameters for a task that purges data from a symbol store after a given age
- L24 _public property_ `public UnrealTargetPlatform Platform { get; set; }` — attrs: `[TaskParameter]` — The target platform to age symbols for.
- L30 _public property_ `public string StoreDir { get; set; }` — attrs: `[TaskParameter]` — The symbol server directory.
- L36 _public property_ `public int Days { get; set; }` — attrs: `[TaskParameter]` — Number of days worth of symbols to keep.
- L42 _public property_ `public string BuildDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The root of the build directory to check for existing buildversion named directories.
- L50 _public property_ `public string Filter { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — A substring to match in directory file names before deleting symbols. This allows the "age store" task to avoid deleting symbols from other builds in the case where multiple builds share the same symbol server. Specific use of the filter value is determined by the symbol server structure defined by the platform toolchain.

#### class `AutomationTool.Tasks.AgeStoreTask`  
`public class AgeStoreTask : BgTaskImpl`  
_public; L58-254_
- attrs: `[TaskElement("AgeStore", typeof(AgeStoreTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Task that strips symbols from a set of files. This task is named after the AGESTORE utility that comes with the Microsoft debugger tools SDK, but is actually a separate implementation. The main difference is that it uses the last modified time rather than last access time to determine which files to delete.
- L63 _private* field_ `readonly AgeStoreTaskParameters _parameters` — Parameters for this task
- L69-72 _public ctor_ `public AgeStoreTask(AgeStoreTaskParameters parameters)` — Construct a spawn task
- L74-85 _private method_ `private static void TryDelete(DirectoryInfo directory)`
- L87-98 _private method_ `private static void TryDelete(FileInfo file)`
- L101-131 _private method_ `private static bool CheckCanDeleteFromVersionFile(HashSet<string> existingBuilds, DirectoryInfo directory, FileInfo individualFile = null)`
- L133-175 _private method_ `private static void RecurseDirectory(DateTime expireTimeUtc, DirectoryInfo currentDirectory, string[] directoryStructure, int level, string filter, HashSet<string> existingBuilds, bool deleteIndividualFiles)`
- L183-227 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L232-235 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L241-244 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L250-253 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L256-280_
- L267-279 _public method_ `public static async Task<FileSet> AgeStoreAsync(UnrealTargetPlatform platform, string storeDir, int days, string buildDir, string filter = null)` — Task that strips symbols from a set of files

### `Source/Programs/AutomationTool/BuildGraph/Tasks/AwsAssumeRoleTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.AwsAssumeRoleTaskParameters`  
`public class AwsAssumeRoleTaskParameters`  
_public; L16-53_
- desc: Parameters for an AWS CLI task
- L22 _public property_ `public string Arn { get; set; }` — attrs: `[TaskParameter]` — Role to assume
- L28 _public property_ `public string Session { get; set; }` — attrs: `[TaskParameter]` — Name of this session
- L34 _public property_ `public int Duration { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Duration of the token in seconds
- L40 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables
- L46 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment variables from
- L52 _public property_ `public string OutputFile { get; set; }` — attrs: `[TaskParameter]` — Output file for the new environment

#### class `AutomationTool.Tasks.AwsAssumeRoleTask`  
`public class AwsAssumeRoleTask : SpawnTaskBase`  
_public; L59-156_
- attrs: `[TaskElement("Aws-AssumeRole", typeof(AwsAssumeRoleTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Assumes an AWS role.
- L73 _private* field_ `readonly AwsAssumeRoleTaskParameters _parameters`
- L79-82 _public ctor_ `public AwsAssumeRoleTask(AwsAssumeRoleTaskParameters parameters)` — Construct an AWS CLI task
- L90-129 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L134-137 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L143-146 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L152-155 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.AwsAssumeRoleTask.AwsSettings`  
`class AwsSettings`  
_private*; L61-64_
- L63 _public property_ `public AwsCredentials Credentials { get; set; }`

#### class `AutomationTool.Tasks.AwsAssumeRoleTask.AwsCredentials`  
`class AwsCredentials`  
_private*; L66-71_
- L68 _public property_ `public string AccessKeyId { get; set; }`
- L69 _public property_ `public string SecretAccessKey { get; set; }`
- L70 _public property_ `public string SessionToken { get; set; }`

### `Source/Programs/AutomationTool/BuildGraph/Tasks/AwsEcsDeployTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.AwsEcsDeployTaskParameters`  
`public class AwsEcsDeployTaskParameters`  
_public; L19-68_
- desc: Parameters for a AWS ECS deploy task
- L25 _public property_ `public string TaskDefinitionFile { get; set; }` — attrs: `[TaskParameter(Optional = false)]` — Task definition file to use
- L31 _public property_ `public string DockerImage { get; set; }` — attrs: `[TaskParameter(Optional = false)]` — Docker image to set in new task definition (will replace %%DOCKER_PATTERN%% with this value)
- L37 _public property_ `public string Version { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — App version to set in new task definition (will replace %%VERSION%% with this value)
- L43 _public property_ `public string Cluster { get; set; }` — attrs: `[TaskParameter(Optional = false)]` — Cluster ARN representing AWS ECS cluster to operate on
- L49 _public property_ `public string Service { get; set; }` — attrs: `[TaskParameter(Optional = false)]` — Service name to update and deploy to
- L55 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables
- L61 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment from
- L67 _public property_ `public bool LogOutput { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Write output to the log

#### class `AutomationTool.Tasks.AwsEcsDeployTask`  
`public class AwsEcsDeployTask : SpawnTaskBase`  
_public; L74-146_
- attrs: `[TaskElement("Aws-EcsDeploy", typeof(AwsEcsDeployTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Creates a new AWS ECS task definition and updates the ECS service to use this new revision of the task def
- L79 _private* field_ `readonly AwsEcsDeployTaskParameters _parameters` — Parameters for this task
- L85-88 _public ctor_ `public AwsEcsDeployTask(AwsEcsDeployTaskParameters parameters)` — Construct an AWS ECS deploy task
- L96-119 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L124-127 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L133-136 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L142-145 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/AwsTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.AwsTaskParameters`  
`public class AwsTaskParameters`  
_public; L13-38_
- desc: Parameters for a spawn task
- L19 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments for the newly created process.
- L25 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables
- L31 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment from
- L37 _public property_ `public bool LogOutput { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Write output to the log

#### class `AutomationTool.Tasks.AwsTask`  
`public class AwsTask : SpawnTaskBase`  
_public; L44-93_
- attrs: `[TaskElement("Aws", typeof(AwsTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns AWS CLI and waits for it to complete.
- L46 _private* field_ `readonly AwsTaskParameters _parameters`
- L52-55 _public ctor_ `public AwsTask(AwsTaskParameters parameters)` — Construct an AWS CLI task
- L63-66 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L71-74 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L80-83 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L89-92 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CheckMarkdownTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CheckMarkdownTaskParameters`  
`public class CheckMarkdownTaskParameters`  
_public; L18-25_
- desc: Parameters for a CheckMarkdown task
- L24 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Optional filter to be applied to the list of input files.

#### class `AutomationTool.Tasks.CheckMarkdownTask`  
`public class CheckMarkdownTask : BgTaskImpl`  
_public; L31-146_
- attrs: `[TaskElement("CheckMarkdown", typeof(CheckMarkdownTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Checks that all markdown links between the given files are valid.
- L33 _private* field_ `readonly CheckMarkdownTaskParameters _parameters`
- L39-42 _public ctor_ `public CheckMarkdownTask(CheckMarkdownTaskParameters parameters)` — Constructor
- L45-133 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — (inheritdoc)
- L136 _public method_ `public override void Write(XmlWriter writer)` — (inheritdoc)
- L140 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — (inheritdoc)
- L144 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — (inheritdoc)

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CommandTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.StringExtensions`  
`static class StringExtensions`  
_internal*; L15-21_
- L17-20 _public method_ `public static bool CaseInsensitiveContains(this string text, string value)`

#### class `AutomationTool.Tasks.CommandTaskParameters`  
`public class CommandTaskParameters`  
_public; L26-45_
- desc: Parameters for a task that calls another UAT command
- L32 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter]` — The command name to execute.
- L38 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments to be passed to the command.
- L44 _public property_ `public string MergeTelemetryWithPrefix { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — If non-null, instructs telemetry from the command to be merged into the telemetry for this UAT instance with the given prefix. May be an empty (non-null) string.

#### class `AutomationTool.Tasks.CommandTask`  
`public class CommandTask : BgTaskImpl`  
_public; L51-172_
- attrs: `[TaskElement("Command", typeof(CommandTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Invokes an AutomationTool child process to run the given command.
- L56 _private* field_ `readonly CommandTaskParameters _parameters` — Parameters for this task
- L62-65 _public ctor_ `public CommandTask(CommandTaskParameters parameters)` — Construct a new CommandTask.
- L73-136 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L142-145 _public method_ `public override string GetTraceName()` — Gets the name of this trace
- L150-153 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L159-162 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L168-171 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L174-210_
- L183-193 _public method_ `public static async Task CommandAsync(this BgContext state, string name, string arguments = null, string mergeTelemetryWithPrefix = null)` — Runs another UAT command
- L201-209 _public method_ `public static async Task CommandAsync(string name, string arguments = null, string mergeTelemetryWithPrefix = null)` — Runs another UAT command

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CommandletTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CommandletTaskParameters`  
`public class CommandletTaskParameters`  
_public; L17-48_
- desc: Parameters for a task which runs a UE commandlet
- L23 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter]` — The commandlet name to execute.
- L29 _public property_ `public string Project { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — The project to run the editor with.
- L35 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments to be passed to the commandlet.
- L41 _public property_ `public FileReference EditorExe { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The editor executable to use. Defaults to the development UnrealEditor executable for the current platform.
- L47 _public property_ `public int ErrorLevel { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The minimum exit code, which is treated as an error.

#### class `AutomationTool.Tasks.CommandletTask`  
`public class CommandletTask : BgTaskImpl`  
_public; L54-131_
- attrs: `[TaskElement("Commandlet", typeof(CommandletTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Spawns the editor to run a commandlet.
- L56 _private* field_ `readonly CommandletTaskParameters _parameters`
- L62-65 _public ctor_ `public CommandletTask(CommandletTaskParameters parameters)` — Construct a new CommandletTask.
- L73-104 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L109-112 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L118-121 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L127-130 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L136-159_
- desc: Task wrapper methods
- L147-158 _public method_ `public static async Task CommandletAsync(this BgContext state, string name, FileReference project = null, string arguments = null, FileReference editorExe = null, int errorLevel = 1)` — Task which runs a UE commandlet

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CompileTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CompileTaskParameters`  
`public class CompileTaskParameters`  
_public; L17-85_
- desc: Parameters for a compile task
- L23 _public property_ `public string Target { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The target to compile.
- L29 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }` — attrs: `[TaskParameter]` — The configuration to compile.
- L35 _public property_ `public UnrealTargetPlatform Platform { get; set; }` — attrs: `[TaskParameter]` — The platform to compile for.
- L41 _public property_ `public string Project { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — The project to compile with.
- L47 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional arguments for UnrealBuildTool.
- L53 _public property_ `public bool AllowXGE { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to allow using XGE for compilation.
- L60 _public property_ `public bool AllowParallelExecutor { get; set; }` — attrs: `[TaskParameter(Optional = true)] [Obsolete("This setting is no longer used")]` — No longer necessary as UnrealBuildTool is run to compile targets.
- L66 _public property_ `public bool AllowAllCores { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to allow UBT to use all available cores, when AllowXGE is disabled.
- L72 _public property_ `public bool? Clean { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to allow cleaning this target. If unspecified, targets are cleaned if the -Clean argument is passed on the command line.
- L78 _public property_ `public bool SkipBuild { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Global flag passed to UBT that can be used to generate target files without fully compiling.
- L84 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.

#### class `AutomationTool.Tasks.CompileTaskExecutor`  
`public class CompileTaskExecutor : ITaskExecutor`  
_public; L90-234_
- inherits: `ITaskExecutor`
- desc: Executor for compile tasks, which can compile multiple tasks simultaneously
- L95 _private* field_ `readonly List<UnrealBuild.BuildTarget> _targets = new List<UnrealBuild.BuildTarget>()` — List of targets to compile. As well as the target specifically added for this task, additional compile tasks may be merged with it.
- L100 _private* field_ `readonly Dictionary<UnrealBuild.BuildTarget, string> _targetToTagName = ...` — Mapping of receipt filename to its corresponding tag name
- L100 _private* field_ `readonly Dictionary<UnrealBuild. _targetToTagName = new Dictionary<UnrealBuild.BuildTarget, string>()` — Mapping of receipt filename to its corresponding tag name
- L105 _private* field_ `bool _allowXge = true` — Whether to allow using XGE for this job
- L110 _private* field_ `bool _allowAllCores = false` — Whether to allow using all available cores for this job, when bAllowXGE is false
- L115 _private* field_ `bool _skipBuild = false` — Should SkipBuild be passed to UBT so that only .target files are generated.
- L121-124 _public ctor_ `public CompileTaskExecutor(CompileTask task)` — Constructor
- L131-166 _public method_ `public bool Add(BgTaskImpl task)` — Adds another task to this executor
- L175-233 _public method_ `public Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync all the tasks added to this executor.

#### class `AutomationTool.Tasks.CompileTask`  
`public class CompileTask : BgTaskImpl`  
_public; L240-376_
- attrs: `[TaskElement("Compile", typeof(CompileTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Compiles a target with UnrealBuildTool.
- L245 _public property_ `public CompileTaskParameters Parameters { get; set; }` — Parameters for this task
- L250 _public property_ `public FileReference ProjectFile { get; set; }` — Resolved path to Project file
- L256-259 _public ctor_ `public CompileTask(CompileTaskParameters parameters)` — Construct a compile task
- L264-287 _public method_ `public FileReference FindProjectFile()` — Resolve the path to the project file
- L295-302 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L308-311 _public method_ `public override ITaskExecutor GetExecutor()`
- L318-330 _public method_ `public override void GetTraceMetadata(ITraceSpan span, string prefix)` — Get properties to include in tracing info
- L337-349 _public method_ `public override void GetTraceMetadata(ISpan span, string prefix)` — Get properties to include in tracing info
- L354-357 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L363-366 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L372-375 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L378-403_
- L391-402 _public method_ `public static async Task<FileSet> CompileAsync(string target, UnrealTargetPlatform platform, UnrealTargetConfiguration configuration, FileReference project = null, string arguments = null, bool allowXge = true, bool? clean = null)` — Compiles a target

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CookTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CookTaskParameters`  
`public class CookTaskParameters`  
_public; L16-65_
- desc: Parameters for a task that runs the cooker
- L22 _public property_ `public string Project { get; set; }` — attrs: `[TaskParameter]` — Project file to be cooked.
- L28 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter]` — The cook platform to target (for example, Windows).
- L34 _public property_ `public string Maps { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — List of maps to be cooked, separated by '+' characters.
- L40 _public property_ `public bool Versioned { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional arguments to be passed to the cooker.
- L46 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional arguments to be passed to the cooker.
- L52 _public property_ `public string EditorExe { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional path to what editor executable to run for cooking.
- L58 _public property_ `public bool TagOutput { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to tag the output from the cook. Since cooks produce a lot of files, it can be detrimental to spend time tagging them if we don't need them in a dependent node.
- L64 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.

#### class `AutomationTool.Tasks.CookTask`  
`public class CookTask : BgTaskImpl`  
_public; L71-173_
- attrs: `[TaskElement("Cook", typeof(CookTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Cook a selection of maps for a certain platform
- L76 _private* field_ `readonly CookTaskParameters _parameters` — Parameters for the task
- L82-85 _public ctor_ `public CookTask(CookTaskParameters parameters)` — Constructor.
- L93-146 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L151-154 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L160-163 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L169-172 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CopyDDCTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CopyDDCTaskParameters`  
`public class CopyDDCTaskParameters`  
_public; L19-98_
- desc: Copy derived data from one source to one or more targets using a replay file as reference for what gets copied
- L25 _public property_ `public string Project { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — The project to run the tool with.
- L31 _public property_ `public string Replay { get; set; }` — attrs: `[TaskParameter]` — The DDC replay file or tag set to use as a reference for what is to be copied.
- L37 _public property_ `public string Source { get; set; }` — attrs: `[TaskParameter]` — The DDC graph name or config to use as the source for the data to copy
- L43 _public property_ `public string Targets { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — An array of the the DDC graph names or configs to use as the target for the data to copy, separated with plus (+) symbol
- L49 _public property_ `public bool Preview { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Whether to preview the operation without doing any writing of data
- L55 _public property_ `public bool Overwrite { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Whether to allow overwriting of data in the target(s)
- L61 _public property_ `public bool ForceOverwrite { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Whether to force overwriting of data in the target(s) even when it is there and seems identical
- L67 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments for the newly created process.
- L73 _public property_ `public string WorkingDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Working directory for spawning the copy task
- L79 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables to set
- L85 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment from
- L91 _public property_ `public bool LogOutput { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Write output to the log
- L97 _public property_ `public int ErrorLevel { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The minimum exit code, which is treated as an error.

#### class `AutomationTool.Tasks.CopyDDCTask`  
`public class CopyDDCTask : SpawnTaskBase`  
_public; L104-237_
- attrs: `[TaskElement("CopyDDC", typeof(CopyDDCTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns an external executable to copy derived data listed in a replay file and waits for it to complete.
- L109 _private* field_ `readonly CopyDDCTaskParameters _parameters` — Parameters for this task
- L115-118 _public ctor_ `public CopyDDCTask(CopyDDCTaskParameters parameters)` — Construct a spawn task
- L126-210 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L215-218 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L224-227 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L233-236 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CopyTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CopyTaskParameters`  
`public class CopyTaskParameters`  
_public; L17-66_
- desc: Parameters for a copy task
- L23 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Optional filter to be applied to the list of input files.
- L29 _public property_ `public string From { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — The pattern(s) to copy from (for example, Engine/*.txt).
- L35 _public property_ `public string To { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — The directory to copy to.
- L41 _public property_ `public string Exclude { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Optional pattern(s) to exclude from the copy for example, Engine/NoCopy*.txt)
- L47 _public property_ `public bool Overwrite { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether or not to overwrite existing files.
- L53 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.
- L59 _public property_ `public bool ErrorIfNotFound { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether or not to throw an error if no files were found to copy
- L65 _public property_ `public bool TagInDefaultSet { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether copied files should be tagged in the default set.

#### class `AutomationTool.Tasks.CopyTask`  
`public class CopyTask : BgTaskImpl`  
_public; L72-286_
- attrs: `[TaskElement("Copy", typeof(CopyTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Copies files from one directory to another.
- L74 _private* field_ `readonly CopyTaskParameters _parameters`
- L80-83 _public ctor_ `public CopyTask(CopyTaskParameters parameters)` — Constructor
- L91-177 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L185-256 _public method_ `public static async Task ExecuteAsync(Dictionary<FileReference, FileReference> targetFileToSourceFile, bool overwrite)`
- L261-264 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L270-276 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L282-285 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.BgStateExtensions`  
`public static partial class BgStateExtensions`  
_public; L291-312_
- desc: Extension methods
- L299-311 _public method_ `public static async Task<FileSet> CopyToAsync(this FileSet files, DirectoryReference targetDir, bool? overwrite = null)` — Copy files from one location to another

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CreateArtifactTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CreateArtifactTaskParameters`  
`public class CreateArtifactTaskParameters`  
_public; L29-96_
- desc: Parameters for a CreateArtifactTask.
- L35 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter]` — Name of the artifact
- L41 _public property_ `public string Type { get; set; }` — attrs: `[TaskParameter]` — The artifact type. Determines the permissions and expiration policy for the artifact.
- L47 _public property_ `public string? Description { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Description for the artifact. Will be shown through the Horde dashboard.
- L53 _public property_ `public string? BaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Base path for the uploaded files. All the tagged files must be under this directory. Defaults to the workspace root directory.
- L59 _public property_ `public string? StreamId { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Stream containing the artifact.
- L65 _public property_ `public string? Commit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Commit for the uploaded artifact.
- L71 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — Files to include in the artifact.
- L77 _public property_ `public string? Keys { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Queryable keys for this artifact, separated by semicolons.
- L83 _public property_ `public string? Metadata { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Other metadata for the artifact, separated by semicolons.
- L89 _public property_ `public bool Symbols { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to add aliases for symbol files
- L95 _public property_ `public bool Dedupe { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to reuse blobs from the previous artifact

#### class `AutomationTool.Tasks.CreateArtifactTask`  
`public class CreateArtifactTask : BgTaskImpl`  
_public; L102-353_
- attrs: `[TaskElement("CreateArtifact", typeof(CreateArtifactTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Uploads an artifact to Horde
- L104 _private* field_ `readonly CreateArtifactTaskParameters _parameters`
- L107 _protected property_ `protected ArtifactName Name { get; set; }` — The name of the artifact we are uploading.
- L110 _protected property_ `protected ArtifactType Type { get; set; }` — The type of the artifact being uploaded
- L113 _protected property_ `protected StreamId? StreamId { get; set; }` — Stream Id resolved from parameters or environment variable
- L116 _protected property_ `protected CommitId? CommitId { get; set; }` — Commit Id resolved from parameters or environment variable
- L122-127 _public ctor_ `public CreateArtifactTask(CreateArtifactTaskParameters parameters)` — Constructor.
- L135-281 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L283-303 _private* method_ `static async ValueTask ComputeHashAsync(DirectoryReference baseDir, FileReference file, IBlobRef<DirectoryNode> rootRef, ConcurrentBag<(IBlobRef, string)> aliases, CancellationToken cancellationToken)`
- L305-340 _private* method_ `static async Task<FileEntry?> FindFileAsync(IBlobRef<DirectoryNode> rootDir, string path, CancellationToken cancellationToken = default)`
- L343 _public method_ `public override void Write(XmlWriter writer)` — (inheritdoc)
- L347 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — (inheritdoc)
- L351 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — (inheritdoc)

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CreateCloudArtifactTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CreateCloudArtifactTaskParameters`  
`public class CreateCloudArtifactTaskParameters`  
_public; L31-180_
- desc: Parameters for a CreateCloudArtifactTask.
- L37 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter]` — Name of the artifact
- L43 _public property_ `public string HordeArtifactID { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — An optional override of the id of the artifact as presented in Horde, defaults to name if not set
- L49 _public property_ `public string BuildGroup { get; set; }` — attrs: `[TaskParameter]` — An identifier to set for a group of builds that are compatible
- L55 _public property_ `public string Type { get; set; }` — attrs: `[TaskParameter]` — The artifact type. Determines the permissions and expiration policy for the artifact.
- L61 _public property_ `public string? Description { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Description for the artifact. Will be shown through the Horde dashboard.
- L67 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter]` — The platform the artifact is created for
- L73 _public property_ `public FileReference? Project { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The uproject this artifact is created for
- L79 _public property_ `public string ProjectNameOverride { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Override the project name, defaults to the filename of the uproject
- L85 _public property_ `public string? Host { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The platform the artifact is created for
- L91 _public property_ `public string? Namespace { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The platform the artifact is created for
- L97 _public property_ `public string? AccessToken { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The access token to use
- L103 _public property_ `public string? BaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Base path for the uploaded files. All the tagged files must be under this directory. Defaults to the workspace root directory.
- L109 _public property_ `public string? StreamId { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Stream containing the artifact.
- L115 _public property_ `public string? Commit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Commit for the uploaded artifact.
- L120 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — Files to include in the artifact.
- L126 _public property_ `public string? SymbolFiles { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec, Optional = true)]` — Files to include in the symbols artifact.
- L132 _public property_ `public string? Metadata { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Other metadata for the artifact, separated by semicolons. Use key=value for each field.
- L138 _public property_ `public bool Force { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Force the blobs to be uploaded no matter if they exist or not
- L144 _public property_ `public string BaselineBranch { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The streamid used for your mainline, used to build content as patches on top of this branch if no other baselines exist.
- L150 _public property_ `public bool AllowMultipart { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Enable to use multipart endpoints if valuable
- L156 _public property_ `public string HttpVersion { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Set the explicit http version to use. None to use http handshaking.
- L162 _public property_ `public bool Verify { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Verify the contents after upload, essentially downloads the entire build to make sure all data was uploaded correctly. Takes a bit of time and is generally not needed but can be useful to detect issues in the upload.
- L168 _public property_ `public bool Verbose { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Verbose logging output, can be useful to find out more information when an issue has occured.
- L174 _public property_ `public bool BoostWorkers { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Increase the number of worker threads used by zen, may cause machine to be less responsive but will generally improve upload times
- L179 _public property_ `public bool EnableTracing { get; set; }` — Enable to create an Unreal Insights trace of the upload process

#### class `AutomationTool.Tasks.CreateCloudArtifactTask`  
`public class CreateCloudArtifactTask : BgTaskImpl`  
_public; L186-719_
- attrs: `[TaskElement("CreateCloudArtifact", typeof(CreateCloudArtifactTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Uploads an artifact to Cloud DDC
- L188 _private* field_ `readonly CreateCloudArtifactTaskParameters _parameters`
- L190 _private field_ `private readonly HashSet<string> _supportedSymbolsExtensions = [ ".exp", ".map", ".pdb" ]`
- L200 _public ctor_ `public CreateCloudArtifactTask(CreateCloudArtifactTaskParameters parameters)` — Constructor.
- L209-642 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L644-660 _internal method_ `internal static (Dictionary<UnrealTargetPlatform, ConfigHierarchy>, Dictionary<UnrealTargetPlatform, ConfigHierarchy>) GetIniConfigs(FileReference projectPath)`
- L662-706 _private* method_ `async Task RegisterHordeArtifactAsync(Uri buildUri, ArtifactName name, ArtifactType type, StreamId streamId, CommitId commitId, Dictionary<string, object> metadata)`
- L709 _public method_ `public override void Write(XmlWriter writer)` — (inheritdoc)
- L713 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — (inheritdoc)
- L717 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — (inheritdoc)

#### class `AutomationTool.Tasks.BuildUploader`  
`static class BuildUploader`  
_internal*; L721-806_
- L731-805 _public method_ `public static void UploadBuild(string host, DirectoryReference baseDir, string namespaceId, string bucketId, CbObjectId buildId, FileReference manifestFile, Dictionary<string, object> metadata, string accessToken, BuildInfo info, bool allowMultipart = false, bool assumeHttp2 = false, bool forceClean = false, bool verify = false, bool verbose = false, bool boostWorkers = false, FileReference? traceFile = null)`

#### struct `AutomationTool.Tasks.BuildUploader.BuildInfo`  
`internal struct BuildInfo`  
_internal; L723-730_
- L725 _public property_ `public string ProjectName { get; set; }`
- L726 _public property_ `public string Name { get; set; }`
- L727 _public property_ `public string Platform { get; set; }`
- L728 _public property_ `public string Branch { get; set; }`
- L729 _public property_ `public string BaselineBranch { get; set; }`

#### class `AutomationTool.Tasks.CloudDDC.StartMultipartUploadRequest`  
`class StartMultipartUploadRequest`  
_internal*; L809-813_
- L812 _public property_ `public ulong BlobLength { get; set; }` — attrs: `[CbField("blobLength")]`

#### class `AutomationTool.Tasks.CloudDDC.MultipartUploadIdResponse`  
`class MultipartUploadIdResponse`  
_internal*; L815-827_
- L818 _public property_ `public string UploadId { get; set; }` — attrs: `[CbField("uploadId")]`
- L821 _public property_ `public string BlobName { get; set; }` — attrs: `[CbField("blobName")]`
- L825 _public property_ `public List<string> PartQueryStrings { get; set; }` — attrs: `[CbField("blobQueryStrings")]`

#### class `AutomationTool.Tasks.CloudDDC.PutBuildResponse`  
`class PutBuildResponse`  
_internal*; L829-833_
- L832 _public property_ `public uint ChunkSize { get; set; }` — attrs: `[CbField("chunkSize")]`

#### class `AutomationTool.Tasks.CloudDDC.NeedsResponse`  
`class NeedsResponse`  
_internal*; L835-849_
- L837-840 _public ctor_ `public NeedsResponse()`
- L842-845 _public ctor_ `public NeedsResponse(List<IoHash> needs)`
- L848 _public property_ `public List<IoHash> Needs { get; set; }` — attrs: `[CbField("needs")]`

#### class `AutomationTool.Tasks.CloudDDC.CompleteMultipartUploadRequest`  
`class CompleteMultipartUploadRequest`  
_internal*; L851-861_
- L854 _public property_ `public string BlobName { get; set; }` — attrs: `[CbField("blobName")]`
- L857 _public property_ `public string UploadId { get; set; }` — attrs: `[CbField("uploadId")]`
- L860 _public property_ `public bool IsCompressed { get; set; }` — attrs: `[CbField("isCompressed")]`

#### class `AutomationTool.Tasks.CloudDDC.CustomMediaTypeNames`  
`static class CustomMediaTypeNames`  
_internal*; L863-874_
- L868 _public const_ `public const string UnrealCompactBinary = "application/x-ue-cb"` — Media type for compact binary
- L873 _public const_ `public const string UnrealCompressedBuffer = "application/x-ue-comp"` — Media type for compressed buffers

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CreateSummaryArtifactTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CreateSummaryArtifactTaskParameters`  
`public class CreateSummaryArtifactTaskParameters : CreateArtifactTaskParameters`  
_public; L26-55_
- inherits: `CreateArtifactTaskParameters`
- desc: Parameters for a CreateSummaryArtifactTask. Inherits all parameters from CreateArtifactTaskParameters and adds report fields.
- L32 _public property_ `public string Scope { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Where to display the report
- L39 _public property_ `public string ReportName { get; set; }` — attrs: `[TaskParameter]` — Name for the Horde report, shown on the job dashboard. Also used as the base filename for the .md and .report.json files written to the log folder.
- L45 _public property_ `public string ReportPlacement { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Dashboard placement for the report. Defaults to "Summary".
- L54 _public property_ `public string ReportText { get; set; }` — attrs: `[TaskParameter]` — Markdown text body for the report. Supports two substitution tokens: {ArtifactId} — replaced with the uploaded artifact's id. {HordeUrl} — replaced with the Horde server base URL (from UE_HORDE_URL env var). Example: "[View Report]({HordeUrl}/api/v2/artifacts/{ArtifactId}/browse/report.html)"

#### class `AutomationTool.Tasks.CreateSummaryArtifactTask`  
`public class CreateSummaryArtifactTask : CreateArtifactTask`  
_public; L63-145_
- attrs: `[TaskElement("Horde-CreateSummaryArtifact", typeof(CreateSummaryArtifactTaskParameters))]`
- inherits: `CreateArtifactTask`
- desc: Uploads an artifact to Horde and writes a job-summary report containing a direct link to the artifact. Extends CreateArtifactTask so all artifact upload behaviour is inherited unchanged; the only addition is writing the .md / .report.json pair to the step log folder after upload completes.
- L65 _private* field_ `readonly CreateSummaryArtifactTaskParameters _summaryParameters`
- L71 _public ctor_ `public CreateSummaryArtifactTask(CreateSummaryArtifactTaskParameters parameters) : base(parameters)` — Constructor.
- L75-135 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — (inheritdoc)
- L138 _public method_ `public override void Write(XmlWriter writer)` — (inheritdoc)
- L141 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — (inheritdoc)
- L144 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — (inheritdoc)

### `Source/Programs/AutomationTool/BuildGraph/Tasks/CsCompileTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.CsCompileTaskParameters`  
`public class CsCompileTaskParameters`  
_public; L16-78_
- desc: Parameters for a task that compiles a C# project
- L22 _public property_ `public string Project { get; set; }` — attrs: `[TaskParameter]` — The C# project file to compile. Using semicolons, more than one project file can be specified.
- L28 _public property_ `public string Configuration { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The configuration to compile.
- L34 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The platform to compile.
- L40 _public property_ `public string Target { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The target to build.
- L46 _public property_ `public string Properties { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Properties for the command
- L52 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional options to pass to the compiler.
- L58 _public property_ `public bool EnumerateOnly { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Only enumerate build products -- do not actually compile the projects.
- L64 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.
- L71 _public property_ `public string TagReferences { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to any non-private references the projects have. (for example, those that are external and not copied into the output directory).
- L77 _public property_ `public bool UseSystemCompiler { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to use the system toolchain rather than the bundled UE SDK

#### class `AutomationTool.Tasks.CsCompileTask`  
`public class CsCompileTask : BgTaskImpl`  
_public; L84-322_
- attrs: `[TaskElement("CsCompile", typeof(CsCompileTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Compiles C# project files, and their dependencies.
- L86 _private* field_ `readonly CsCompileTaskParameters _parameters`
- L92-95 _public ctor_ `public CsCompileTask(CsCompileTaskParameters parameters)` — Constructor.
- L103-214 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L219-222 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L228-231 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L237-248 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task
- L257-289 _private* method_ `static void FindBuildProductsAndReferences(HashSet<FileReference> projectFiles, Dictionary<string, string> initialProperties, out HashSet<FileReference> outBuildProducts, out HashSet<FileReference> outReferences)` — Find all the build products created by compiling the given project file
- L298-321 _private* method_ `static void ReadProjectsRecursively(FileReference file, Dictionary<string, string> initialProperties, Dictionary<FileReference, IDotnetProjectInfo> fileToProjectInfo)` — Read a project file, plus all the project files it references.

#### class `AutomationTool.Tasks.CsCompileOutput`  
`public class CsCompileOutput`  
_public; L327-369_
- desc: Output from compiling a csproj file
- L332 _public property_ `public static CsCompileOutput Empty { get; }` — Empty instance of CsCompileOutput
- L337 _public property_ `public FileSet Binaries { get; }` — Output binaries
- L342 _public property_ `public FileSet References { get; }` — Referenced output
- L347-351 _public ctor_ `public CsCompileOutput(FileSet binaries, FileSet references)` — Constructor
- L357-360 _public method_ `public FileSet Merge()` — Merge all outputs from this project
- L365-368 _public operator_ `public static CsCompileOutput operator +(CsCompileOutput lhs, CsCompileOutput rhs)` — Merges two outputs together

#### class `AutomationTool.Tasks.CsCompileOutputExtensions`  
`public static class CsCompileOutputExtensions`  
_public; L374-385_
- desc: Extension methods for csproj compilation
- L381-384 _public method_ `public static async Task<FileSet> MergeAsync(this Task<CsCompileOutput> task)`

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L387-429_
- L399-428 _public method_ `public static async Task<CsCompileOutput> CsCompileAsync(FileReference project, string platform = null, string configuration = null, string target = null, string properties = null, string arguments = null, bool? enumerateOnly = null)` — Compile a C# project

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DDCReplayLoadTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DDCReplayLoadTaskParameters`  
`public class DDCReplayLoadTaskParameters`  
_public; L17-72_
- desc: Parameters for updating the derived data via a replay load
- L23 _public property_ `public string Exe { get; set; }` — attrs: `[TaskParameter]` — Executable to spawn.
- L29 _public property_ `public string Project { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — The project to run the tool with.
- L35 _public property_ `public string DDCReplayFile { get; set; }` — attrs: `[TaskParameter]` — The DDC replay load file or tag set to use.
- L41 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments for the newly created process.
- L47 _public property_ `public string WorkingDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Working directory for spawning the new task
- L53 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables to set
- L59 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment from
- L65 _public property_ `public bool LogOutput { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Write output to the log
- L71 _public property_ `public int ErrorLevel { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The minimum exit code, which is treated as an error.

#### class `AutomationTool.Tasks.DDCReplayLoadTask`  
`public class DDCReplayLoadTask : SpawnTaskBase`  
_public; L78-163_
- attrs: `[TaskElement("DDCReplayLoad", typeof(DDCReplayLoadTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns an external executable to UpdateDerivedData and waits for it to complete.
- L83 _private* field_ `readonly DDCReplayLoadTaskParameters _parameters` — Parameters for this task
- L89-92 _public ctor_ `public DDCReplayLoadTask(DDCReplayLoadTaskParameters parameters)` — Construct a spawn task
- L100-136 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L141-144 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L150-153 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L159-162 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DeleteTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DeleteTaskParameters`  
`public class DeleteTaskParameters`  
_public; L18-43_
- desc: Parameters for a copy task
- L24 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — List of file specifications separated by semicolons (for example, *.cpp;Engine/.../*.bat), or the name of a tag set
- L30 _public property_ `public string Directories { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — List of directory names
- L36 _public property_ `public bool DeleteEmptyDirectories { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to delete empty directories after deleting the files. Defaults to true.
- L42 _public property_ `public bool Verbose { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether or not to use verbose logging.

#### class `AutomationTool.Tasks.DeleteTask`  
`public class DeleteTask : BgTaskImpl`  
_public; L49-187_
- attrs: `[TaskElement("Delete", typeof(DeleteTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Delete a set of files.
- L51 _private* field_ `readonly DeleteTaskParameters _parameters`
- L57-60 _public ctor_ `public DeleteTask(DeleteTaskParameters parameters)` — Constructor
- L68-128 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L135-160 _private* method_ `static bool TryDeleteEmptyDirectory(DirectoryReference candidateDirectory)` — Deletes a directory, if it's empty
- L165-168 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L174-177 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L183-186 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DeployToolTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DeployToolTaskParameters`  
`public class DeployToolTaskParameters`  
_public; L25-68_
- desc: Parameters for a DeployTool task
- L31 _public property_ `public string Id { get; set; }` — attrs: `[TaskParameter]` — Identifier for the tool
- L37 _public property_ `public string Settings { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Settings file to use for the deployment. Should be a JSON file containing server name and access token.
- L43 _public property_ `public string Version { get; set; }` — attrs: `[TaskParameter]` — Version number for the new tool
- L49 _public property_ `public int Duration { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Duration over which to roll out the tool, in minutes.
- L55 _public property_ `public bool Paused { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to create the deployment as paused
- L61 _public property_ `public string? File { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Zip file containing files to upload
- L67 _public property_ `public string? Directory { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Directory to upload for the tool

#### class `AutomationTool.Tasks.DeployToolTask`  
`public class DeployToolTask : SpawnTaskBase`  
_public; L74-231_
- attrs: `[TaskElement("DeployTool", typeof(DeployToolTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Deploys a tool update through Horde
- L93 _private* field_ `readonly DeployToolTaskParameters _parameters`
- L99-102 _public ctor_ `public DeployToolTask(DeployToolTaskParameters parameters)` — Construct a Helm task
- L110-204 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L209-212 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L218-221 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L227-230 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.DeployToolTask.DeploySettings`  
`class DeploySettings`  
_private*; L76-80_
- L78 _public property_ `public string Server { get; set; }`
- L79 _public property_ `public string? Token { get; set; }`

#### class `AutomationTool.Tasks.DeployToolTask.CreateDeploymentRequest`  
`class CreateDeploymentRequest`  
_private*; L85-91_
- desc: Options for a new deployment
- L87 _public property_ `public string Version { get; set; }`
- L88 _public property_ `public double? Duration { get; set; }`
- L89 _public property_ `public bool? CreatePaused { get; set; }`
- L90 _public property_ `public string? Node { get; set; }`

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DockerBuildTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DockerBuildTaskParameters`  
`public class DockerBuildTaskParameters`  
_public; L19-104_
- desc: Parameters for a Docker-Build task
- L25 _public property_ `public string BaseDir { get; set; }` — attrs: `[TaskParameter]` — Base directory for the build
- L31 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter]` — Files to be staged before building the image
- L37 _public property_ `public string DockerFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to the Dockerfile. Uses the root of basedir if not specified.
- L43 _public property_ `public string DockerIgnoreFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to a .dockerignore. Will be copied to basedir if specified.
- L49 _public property_ `public bool UseBuildKit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Use BuildKit in Docker
- L55 _public property_ `public string Ulimit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Set ulimit in build
- L61 _public property_ `public string ProgressOutput { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Type of progress output (--progress)
- L67 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Tag for the image
- L73 _public property_ `public string Target { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Set the target build stage to build (--target)
- L79 _public property_ `public string Output { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Custom output exporter. Requires BuildKit (--output)
- L85 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional arguments
- L91 _public property_ `public string OverlayDirs { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — List of additional directories to overlay into the staged input files. Allows credentials to be staged, etc...
- L97 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables to set
- L103 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment variables from

#### class `AutomationTool.Tasks.DockerBuildTask`  
`public class DockerBuildTask : SpawnTaskBase`  
_public; L110-243_
- attrs: `[TaskElement("Docker-Build", typeof(DockerBuildTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns Docker and waits for it to complete.
- L112 _private* field_ `readonly DockerBuildTaskParameters _parameters`
- L118-121 _public ctor_ `public DockerBuildTask(DockerBuildTaskParameters parameters)` — Construct a Docker task
- L129-209 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L211 _private* field_ `static readonly Regex s_filterOutputPattern = new Regex(@"^#\d+ (?:\d+\.\d+ )?")`
- L213 _private* method_ `static string FilterOutput(string line)`
- L218-221 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L227-233 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L239-242 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DockerComposeDownTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DockerComposeDownTaskParameters`  
`public class DockerComposeDownTaskParameters`  
_public; L17-30_
- desc: Parameters for a Docker-Compose task
- L23 _public property_ `public string File { get; set; }` — attrs: `[TaskParameter]` — Path to the docker-compose file
- L29 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments for the command

#### class `AutomationTool.Tasks.DockerComposeDownTask`  
`public class DockerComposeDownTask : SpawnTaskBase`  
_public; L36-103_
- attrs: `[TaskElement("Docker-Compose-Down", typeof(DockerComposeDownTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns Docker and waits for it to complete.
- L41 _private* field_ `readonly DockerComposeDownTaskParameters _parameters` — Parameters for this task
- L47-50 _public ctor_ `public DockerComposeDownTask(DockerComposeDownTaskParameters parameters)` — Construct a Docker-Compose task
- L58-76 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L81-84 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L90-93 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L99-102 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DockerComposeUpTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DockerComposeUpTaskParameters`  
`public class DockerComposeUpTaskParameters`  
_public; L18-31_
- desc: Parameters for a Docker-Compose task
- L24 _public property_ `public string File { get; set; }` — attrs: `[TaskParameter]` — Path to the docker-compose file
- L30 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments for the command

#### class `AutomationTool.Tasks.DockerComposeUpTask`  
`public class DockerComposeUpTask : SpawnTaskBase`  
_public; L37-109_
- attrs: `[TaskElement("Docker-Compose-Up", typeof(DockerComposeUpTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns Docker and waits for it to complete.
- L39 _private* field_ `readonly DockerComposeUpTaskParameters _parameters`
- L45-48 _public ctor_ `public DockerComposeUpTask(DockerComposeUpTaskParameters parameters)` — Construct a Docker-Compose task
- L56-82 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L87-90 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L96-99 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L105-108 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DockerPushTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DockerPushTaskParameters`  
`public class DockerPushTaskParameters`  
_public; L16-59_
- desc: Parameters for a Docker-Build task
- L22 _public property_ `public string Repository { get; set; }` — attrs: `[TaskParameter]` — Repository
- L28 _public property_ `public string Image { get; set; }` — attrs: `[TaskParameter]` — Source image to push
- L34 _public property_ `public string TargetImage { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Name of the target image
- L40 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional environment variables
- L46 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment from
- L52 _public property_ `public bool AwsEcr { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to login to AWS ECR
- L58 _public property_ `public string RepositoryAuthFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to a json file for authentication to the repository for pushing.

#### class `AutomationTool.Tasks.DockerPushTask`  
`public class DockerPushTask : SpawnTaskBase`  
_public; L65-135_
- attrs: `[TaskElement("Docker-Push", typeof(DockerPushTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns Docker and waits for it to complete.
- L67 _private* field_ `readonly DockerPushTaskParameters _parameters`
- L73-76 _public ctor_ `public DockerPushTask(DockerPushTaskParameters parameters)` — Construct a Docker task
- L84-108 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L113-116 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L122-125 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L131-134 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DockerTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DockerTaskParameters`  
`public class DockerTaskParameters`  
_public; L14-39_
- desc: Parameters for a Docker task
- L20 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter]` — Docker command line arguments
- L26 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables to set
- L32 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment variables from
- L38 _public property_ `public string WorkingDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Base directory for running the command

#### class `AutomationTool.Tasks.DockerTask`  
`public class DockerTask : SpawnTaskBase`  
_public; L45-107_
- attrs: `[TaskElement("Docker", typeof(DockerTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns Docker and waits for it to complete.
- L50 _private* field_ `readonly DockerTaskParameters _parameters` — Parameters for this task
- L56-59 _public ctor_ `public DockerTask(DockerTaskParameters parameters)` — Construct a Docker task
- L67-70 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L75-78 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L84-87 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L93-96 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task
- L103-106 _public method_ `public static string GetDockerExecutablePath()` — Resolve path to Docker executable by using the optional env var "UE_DOCKER_EXEC_PATH" Will default to "docker" if not set. Allows supporting alternative Docker implementations such as Podman.

### `Source/Programs/AutomationTool/BuildGraph/Tasks/DotNetTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.DotNetTaskParameters`  
`public class DotNetTaskParameters`  
_public; L18-55_
- desc: Parameters for a DotNet task
- L24 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Docker command line arguments
- L30 _public property_ `public string BaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Base directory for running the command
- L36 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables to set
- L42 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment variables from
- L48 _public property_ `public int ErrorLevel { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The minimum exit code, which is treated as an error.
- L54 _public property_ `public FileReference DotNetPath { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Override path to dotnet executable

#### class `AutomationTool.Tasks.DotNetTask`  
`public class DotNetTask : SpawnTaskBase`  
_public; L61-177_
- attrs: `[TaskElement("DotNet", typeof(DotNetTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns Docker and waits for it to complete.
- L63 _private* field_ `readonly DotNetTaskParameters _parameters`
- L69-72 _public ctor_ `public DotNetTask(DotNetTaskParameters parameters)` — Construct a Docker task
- L80-150 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L155-158 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L164-167 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L173-176 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L179-202_
- L190-201 _public method_ `public static async Task DotNetAsync(string arguments = null, DirectoryReference baseDir = null, string environment = null, FileReference environmentFile = null, int errorLevel = 1, FileReference dotNetPath = null)` — Runs a command using dotnet.

### `Source/Programs/AutomationTool/BuildGraph/Tasks/FindModifiedFiles.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.FindModifiedFilesTaskParameters`  
`public class FindModifiedFilesTaskParameters`  
_public; L18-49_
- desc: Parameters for a task that compiles a C# project
- L24 _public property_ `public string Path { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — List of file specifications separated by semicolon (default is ...)
- L30 _public property_ `public int Change { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The configuration to compile.
- L36 _public property_ `public int MinChange { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The configuration to compile.
- L42 _public property_ `public int MaxChange { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The configuration to compile.
- L48 _public property_ `public FileReference Output { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The file to write to

#### class `AutomationTool.Tasks.FindModifiedFilesTask`  
`public class FindModifiedFilesTask : BgTaskImpl`  
_public; L55-175_
- attrs: `[TaskElement("FindModifiedFiles", typeof(FindModifiedFilesTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Compiles C# project files, and their dependencies.
- L60 _private* field_ `readonly FindModifiedFilesTaskParameters _parameters` — Parameters for the task
- L66-69 _public ctor_ `public FindModifiedFilesTask(FindModifiedFilesTaskParameters parameters)` — Constructor.
- L77-138 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L143-146 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L152-156 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L162-174 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/GatherBuildProductsFromFileTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.GatherBuildProductsFromFileTaskParameters`  
`public class GatherBuildProductsFromFileTaskParameters`  
_public; L16-29_
- desc: Parameters for GatherBuildProductsFromFileTask
- L22 _public property_ `public string BuildProductsFile { get; set; }` — attrs: `[TaskParameter]` — Path to the file containing the list of build products
- L28 _public property_ `public string BaseDirectory { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional base directory to apply to entries in the BuildProducts file

#### class `AutomationTool.Tasks.GatherBuildProductsFromFileTask`  
`class GatherBuildProductsFromFileTask : BgTaskImpl`  
_internal*; L32-79_
- attrs: `[TaskElement("GatherBuildProductsFromFile", typeof(GatherBuildProductsFromFileTaskParameters))]`
- inherits: `BgTaskImpl`
- L34-37 _public ctor_ `public GatherBuildProductsFromFileTask(GatherBuildProductsFromFileTaskParameters parameters)`
- L39-61 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)`
- L63-66 _public method_ `public override void Write(XmlWriter writer)`
- L68-71 _public method_ `public override IEnumerable<string> FindConsumedTagNames()`
- L73-76 _public method_ `public override IEnumerable<string> FindProducedTagNames()`
- L78 _public field_ `public GatherBuildProductsFromFileTaskParameters _parameters`

### `Source/Programs/AutomationTool/BuildGraph/Tasks/GitCloneTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.GitCloneTaskParameters`  
`public class GitCloneTaskParameters`  
_public; L15-40_
- desc: Parameters for a Git-Checkout task
- L21 _public property_ `public string Dir { get; set; }` — attrs: `[TaskParameter]` — Directory for the repository
- L27 _public property_ `public string Remote { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The remote to add
- L33 _public property_ `public string Branch { get; set; }` — attrs: `[TaskParameter]` — The branch to check out on the remote
- L39 _public property_ `public string ConfigFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Configuration file for the repo. This can be used to set up a remote to be fetched and/or provide credentials.

#### class `AutomationTool.Tasks.GitCloneTask`  
`public class GitCloneTask : BgTaskImpl`  
_public; L46-143_
- attrs: `[TaskElement("Git-Clone", typeof(GitCloneTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Clones a Git repository into a local path.
- L51 _private* field_ `readonly GitCloneTaskParameters _parameters` — Parameters for this task
- L57-60 _public ctor_ `public GitCloneTask(GitCloneTaskParameters parameters)` — Construct a Git task
- L68-100 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L108-116 _private* method_ `static Task RunGit(FileReference toolFile, string arguments, DirectoryReference workingDir)` — Runs a git command
- L121-124 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L130-133 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L139-142 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/GitTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.GitTaskParameters`  
`public class GitTaskParameters`  
_public; L13-32_
- desc: Parameters for a Git task
- L19 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Git command line arguments
- L25 _public property_ `public string BaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Base directory for running the command
- L31 _public property_ `public int ErrorLevel { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The minimum exit code, which is treated as an error.

#### class `AutomationTool.Tasks.GitTask`  
`public class GitTask : BgTaskImpl`  
_public; L38-99_
- attrs: `[TaskElement("Git", typeof(GitTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Spawns Git and waits for it to complete.
- L40 _private* field_ `readonly GitTaskParameters _parameters`
- L46-49 _public ctor_ `public GitTask(GitTaskParameters parameters)` — Construct a Git task
- L57-72 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L77-80 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L86-89 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L95-98 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/HelmTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.HelmTaskParameters`  
`public class HelmTaskParameters`  
_public; L15-82_
- desc: Parameters for a Helm task
- L21 _public property_ `public string Chart { get; set; }` — attrs: `[TaskParameter]` — Helm command line arguments
- L27 _public property_ `public string Deployment { get; set; }` — attrs: `[TaskParameter]` — Name of the release
- L33 _public property_ `public string Namespace { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The Kubernetes namespace
- L39 _public property_ `public string KubeContext { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The kubectl context
- L45 _public property_ `public string KubeConfig { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The kubectl config file to use
- L51 _public property_ `public string Values { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Values to set for running the chart
- L57 _public property_ `public string ValuesFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Values to set for running the chart
- L63 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables to set
- L69 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to parse environment variables from
- L75 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional arguments
- L81 _public property_ `public string WorkingDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Base directory for running the command

#### class `AutomationTool.Tasks.HelmTask`  
`public class HelmTask : SpawnTaskBase`  
_public; L88-178_
- attrs: `[TaskElement("Helm", typeof(HelmTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns Helm and waits for it to complete.
- L90 _private* field_ `readonly HelmTaskParameters _parameters`
- L96-99 _public ctor_ `public HelmTask(HelmTaskParameters parameters)` — Construct a Helm task
- L107-151 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L156-159 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L165-168 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L174-177 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/HordeCreateReportTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.HordeCreateReportTaskParameters`  
`public class HordeCreateReportTaskParameters`  
_public; L17-42_
- desc: Parameters for a HordeCreateReportTask.
- L23 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter]` — Name for the report
- L29 _public property_ `public string Scope { get; set; }` — attrs: `[TaskParameter]` — Where to display the report
- L35 _public property_ `public string Placement { get; set; }` — attrs: `[TaskParameter]` — Where to show the report
- L41 _public property_ `public string Text { get; set; }` — attrs: `[TaskParameter]` — Text to be displayed

#### class `AutomationTool.Tasks.HordeCreateReportTask`  
`public class HordeCreateReportTask : BgTaskImpl`  
_public; L48-111_
- attrs: `[TaskElement("Horde-CreateReport", typeof(HordeCreateReportTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Creates a Horde report file, which will be displayed on the dashboard with any job running this task.
- L53 _private* field_ `readonly HordeCreateReportTaskParameters _parameters` — Parameters for this task.
- L59-62 _public ctor_ `public HordeCreateReportTask(HordeCreateReportTaskParameters parameters)` — Constructor.
- L70-90 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L95-98 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L104 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L110 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L113-134_
- L123-133 _public method_ `public static async Task<FileSet> HordeCreateReportAsync(string name, string scope, string placement, string text)` — Compiles a target

### `Source/Programs/AutomationTool/BuildGraph/Tasks/HordeGetSecretsTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.HordeGetSecretsTaskParameters`  
`public class HordeGetSecretsTaskParameters`  
_public; L22-42_
- desc: Parameters for a HordeGetSecretsTask.
- L28 _public property_ `public string File { get; set; }` — attrs: `[TaskParameter]` — File to update with secrets
- L34 _public property_ `public string? Text { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Text to update with secrets
- L41 _public property_ `public string? Replace { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Pairs of strings and secret names to expand in the text file, in the form SOURCE_TEXT=secret-name;SOURCE_TEXT_2=secret-name-2. If not specified, secrets embedded inline in the text will be expanded from {{secret-name.value}} strings.

#### class `AutomationTool.Tasks.HordeGetSecretsTask`  
`public class HordeGetSecretsTask : BgTaskImpl`  
_public; L48-227_
- attrs: `[TaskElement("Horde-GetSecrets", typeof(HordeGetSecretsTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Replaces strings in a text file with secrets obtained from Horde
- L52 _private* field_ `readonly HordeGetSecretsTaskParameters _parameters`
- L58-61 _public ctor_ `public HordeGetSecretsTask(HordeGetSecretsTaskParameters parameters)` — Constructor.
- L69-184 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L186-206 _private* method_ `static bool ParseReplacementInfo(string variable, string replacement, Dictionary<SecretId, List<ReplacementInfo>> secretToReplacementInfo)`
- L211-214 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L220 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L226 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### record `AutomationTool.Tasks.HordeGetSecretsTask.ReplacementInfo`  
`record class ReplacementInfo(string Property, string Variable)`  
_private*; L50-50_

### `Source/Programs/AutomationTool/BuildGraph/Tasks/HordeSetSecretEnvVarTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.HordeSetSecretEnvVarTaskParameters`  
`public class HordeSetSecretEnvVarTaskParameters`  
_public; L23-36_
- desc: Parameters for a HordeGetSecretsTask.
- L29 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter]` — Name of the environment variable to set
- L35 _public property_ `public string Secret { get; set; }` — attrs: `[TaskParameter]` — Name of the secret to fetch

#### class `AutomationTool.Tasks.HordeSetSecretEnvVarTask`  
`public class HordeSetSecretEnvVarTask : BgTaskImpl`  
_public; L42-126_
- attrs: `[TaskElement("Horde-SetSecretEnvVar", typeof(HordeSetSecretEnvVarTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Replaces strings in a text file with secrets obtained from Horde
- L44 _private* field_ `readonly HordeSetSecretEnvVarTaskParameters _parameters`
- L50-53 _public ctor_ `public HordeSetSecretEnvVarTask(HordeSetSecretEnvVarTaskParameters parameters)` — Constructor.
- L61-105 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L110-113 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L119 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L125 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/KubectlTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.KubectlTaskParameters`  
`public class KubectlTaskParameters`  
_public; L13-26_
- desc: Parameters for a Kubectl task
- L19 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter]` — Command line arguments
- L25 _public property_ `public string BaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Base directory for running the command

#### class `AutomationTool.Tasks.KubectlTask`  
`public class KubectlTask : BgTaskImpl`  
_public; L32-93_
- attrs: `[TaskElement("Kubectl", typeof(KubectlTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Spawns Kubectl and waits for it to complete.
- L34 _private* field_ `readonly KubectlTaskParameters _parameters`
- L40-43 _public ctor_ `public KubectlTask(KubectlTaskParameters parameters)` — Construct a Kubectl task
- L51-66 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L71-74 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L80-83 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L89-92 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/LogTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.LogTaskParameters`  
`public class LogTaskParameters`  
_public; L17-36_
- desc: Parameters for the log task
- L23 _public property_ `public string Message { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Message to print out.
- L29 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — If specified, causes the given list of files to be printed after the given message.
- L35 _public property_ `public bool IncludeContents { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — If specified, causes the contents of the given files to be printed out.

#### class `AutomationTool.Tasks.LogTask`  
`public class LogTask : BgTaskImpl`  
_public; L42-116_
- attrs: `[TaskElement("Log", typeof(LogTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Print a message (and other optional diagnostic information) to the output log.
- L47 _private* field_ `readonly LogTaskParameters _parameters` — Parameters for the task
- L53-56 _public ctor_ `public LogTask(LogTaskParameters parameters)` — Constructor.
- L64-89 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L94-97 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L103-106 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L112-115 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ModifyConfigTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ModifyConfigTaskParameters`  
`public class ModifyConfigTaskParameters`  
_public; L15-46_
- desc: Parameters for a ModifyConfig task
- L21 _public property_ `public string File { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — Path to the config file
- L27 _public property_ `public string Section { get; set; }` — attrs: `[TaskParameter]` — The section name to modify
- L33 _public property_ `public string Key { get; set; }` — attrs: `[TaskParameter]` — The property name to set
- L39 _public property_ `public string Value { get; set; }` — attrs: `[TaskParameter]` — The property value to set
- L45 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to the extracted files

#### class `AutomationTool.Tasks.ModifyConfigTask`  
`public class ModifyConfigTask : BgTaskImpl`  
_public; L52-128_
- attrs: `[TaskElement("ModifyConfig", typeof(ModifyConfigTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Modifies a config file
- L54 _private* field_ `readonly ModifyConfigTaskParameters _parameters`
- L60-63 _public ctor_ `public ModifyConfigTask(ModifyConfigTaskParameters parameters)` — Constructor
- L71-101 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L106-109 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L115-118 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L124-127 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ModifyJsonValue.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ModifyJsonValueParameters`  
`public class ModifyJsonValueParameters`  
_public; L18-37_
- desc: Parameters for a ModifyJsonValue task
- L24 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — json file paths which will be modified
- L30 _public property_ `public string KeyPath { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.Default)]` — json key path to find in each file
- L36 _public property_ `public int NewValue { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.Default)]` — new value to apply

#### class `AutomationTool.Tasks.ModifyJsonValue`  
`public class ModifyJsonValue : BgTaskImpl`  
_public; L43-114_
- attrs: `[TaskElement("ModifyJsonValue", typeof(ModifyJsonValueParameters))]`
- inherits: `BgTaskImpl`
- desc: Modifies json files by setting a value specified in the key path
- L45 _private* field_ `readonly ModifyJsonValueParameters _parameters`
- L51-54 _public ctor_ `public ModifyJsonValue(ModifyJsonValueParameters parameters)` — Create a new ModifyJsonValue.
- L59-86 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Placeholder comment
- L91-94 _public method_ `public override void Write(XmlWriter writer)` — Placeholder comment
- L99-105 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Placeholder comment
- L110-113 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Placeholder comment

### `Source/Programs/AutomationTool/BuildGraph/Tasks/MoveTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.MoveTaskParameters`  
`public class MoveTaskParameters`  
_public; L17-54_
- desc: Parameters for a move task
- L23 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Optional filter to be applied to the list of input files.
- L29 _public property_ `public string From { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — The pattern(s) to copy from (for example, Engine/*.txt).
- L35 _public property_ `public string To { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — The directory to copy to.
- L41 _public property_ `public bool Overwrite { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optionally if files should be overwritten, defaults to false.
- L47 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.
- L53 _public property_ `public bool ErrorIfNotFound { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether or not to throw an error if no files were found to copy

#### class `AutomationTool.Tasks.MoveTask`  
`public class MoveTask : BgTaskImpl`  
_public; L60-171_
- attrs: `[TaskElement("Move", typeof(MoveTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Moves files from one directory to another.
- L62 _private* field_ `readonly MoveTaskParameters _parameters`
- L68-71 _public ctor_ `public MoveTask(MoveTaskParameters parameters)` — Constructor
- L79-141 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L146-149 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L155-161 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L167-170 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/MsBuildTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.MsBuildTaskParameters`  
`public class MsBuildTaskParameters`  
_public; L16-47_
- desc: Parameters for a task that executes MSBuild
- L22 _public property_ `public string Project { get; set; }` — attrs: `[TaskParameter]` — The C# project file to compile. Using semicolons, more than one project file can be specified.
- L28 _public property_ `public string Configuration { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The configuration to compile.
- L34 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The platform to compile.
- L40 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional options to pass to the compiler.
- L46 _public property_ `public string Verbosity { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The MSBuild output verbosity.

#### class `AutomationTool.Tasks.MsBuildTask`  
`public class MsBuildTask : BgTaskImpl`  
_public; L53-141_
- attrs: `[TaskElement("MsBuild", typeof(MsBuildTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Executes MsBuild
- L58 _private* field_ `readonly MsBuildTaskParameters _parameters` — Parameters for the task
- L64-67 _public ctor_ `public MsBuildTask(MsBuildTaskParameters parameters)` — Constructor.
- L75-114 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L119-122 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L128-131 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L137-140 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/NotarizeTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.NotarizeTaskParameters`  
`public class NotarizeTaskParameters`  
_public; L19-50_
- desc: Parameters for a task that notarizes a dmg via the apple notarization process
- L25 _public property_ `public string DmgPath { get; set; }` — attrs: `[TaskParameter]` — Path to the dmg to notarize
- L31 _public property_ `public string BundleID { get; set; }` — attrs: `[TaskParameter]` — primary bundle ID
- L37 _public property_ `public string UserName { get; set; }` — attrs: `[TaskParameter]` — Apple ID Username
- L43 _public property_ `public string KeyChainID { get; set; }` — attrs: `[TaskParameter]` — The keychain ID
- L49 _public property_ `public bool RequireStapling { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — When true the notarization ticket will be stapled

#### class `AutomationTool.Tasks.NotarizeTask`  
`class NotarizeTask : BgTaskImpl`  
_internal*; L53-224_
- attrs: `[TaskElement("Notarize", typeof(NotarizeTaskParameters))]`
- inherits: `BgTaskImpl`
- L58 _private* field_ `readonly NotarizeTaskParameters _parameters` — Parameters for the task
- L64-67 _public ctor_ `public NotarizeTask(NotarizeTaskParameters parameters)` — Constructor.
- L75-176 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L178-197 _private method_ `private string GetRequestLogs(string requestUuid)`
- L202-205 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L211-214 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L220-223 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/NuGetLicenseCheckTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.NuGetLicenseCheckTaskParameters`  
`public class NuGetLicenseCheckTaskParameters`  
_public; L23-54_
- desc: Parameters for a NuGetLicenseCheck task
- L29 _public property_ `public string BaseDir { get; set; }` — attrs: `[TaskParameter]` — Base directory for running the command
- L35 _public property_ `public string IgnorePackages { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Specifies a list of packages to ignore for version checks, separated by semicolons. Optional version number may be specified with 'name@version' syntax.
- L41 _public property_ `public DirectoryReference LicenseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Directory containing allowed licenses
- L47 _public property_ `public FileReference CsvFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to a csv file to write with list of packages and their licenses
- L53 _public property_ `public FileReference DotNetPath { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Override path to dotnet executable

#### class `AutomationTool.Tasks.NuGetLicenseCheckTask`  
`public class NuGetLicenseCheckTask : SpawnTaskBase`  
_public; L60-440_
- attrs: `[TaskElement("NuGet-LicenseCheck", typeof(NuGetLicenseCheckTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Verifies which licenses are in use by nuget dependencies
- L67 _private* field_ `readonly NuGetLicenseCheckTaskParameters _parameters`
- L73-76 _public ctor_ `public NuGetLicenseCheckTask(NuGetLicenseCheckTaskParameters parameters)` — Construct a NuGetLicenseCheckTask task
- L108-132 _private* method_ `static LicenseInfo FindOrAddLicense(Dictionary<IoHash, LicenseInfo> licenses, string text, string extension)`
- L140-413 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L418-421 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L427-430 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L436-439 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.NuGetLicenseCheckTask.LicenseConfig`  
`class LicenseConfig`  
_private*; L62-65_
- L64 _public property_ `public List<string> Urls { get; set; }`

#### enum `AutomationTool.Tasks.NuGetLicenseCheckTask.PackageState`  
`enum PackageState`  
_private*; L78-85_
- L80 _public* enumerator_ `None`
- L81 _public* enumerator_ `IgnoredViaArgs`
- L82 _public* enumerator_ `MissingPackageFolder`
- L83 _public* enumerator_ `MissingPackageDescriptor`
- L84 _public* enumerator_ `Valid`

#### class `AutomationTool.Tasks.NuGetLicenseCheckTask.PackageInfo`  
`class PackageInfo`  
_private*; L87-96_
- L89 _public field_ `public string _name`
- L90 _public field_ `public string _version`
- L91 _public field_ `public string _projectUrl`
- L92 _public field_ `public LicenseInfo _license`
- L93 _public field_ `public string _licenseSource`
- L94 _public field_ `public PackageState _state`
- L95 _public field_ `public FileReference _descriptor`

#### class `AutomationTool.Tasks.NuGetLicenseCheckTask.LicenseInfo`  
`class LicenseInfo`  
_private*; L98-106_
- L100 _public field_ `public IoHash _hash`
- L101 _public field_ `public string _text`
- L102 _public field_ `public string _normalizedText`
- L103 _public field_ `public string _extension`
- L104 _public field_ `public bool _approved`
- L105 _public field_ `public FileReference _file`

### `Source/Programs/AutomationTool/BuildGraph/Tasks/OnExitTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.OnExitTaskParameters`  
`public class OnExitTaskParameters`  
_public; L15-28_
- desc: Parameters for a spawn task
- L21 _public property_ `public string Command { get; set; }` — attrs: `[TaskParameter]` — Executable to spawn.
- L27 _public property_ `public bool Lease { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to execute on lease termination

#### class `AutomationTool.Tasks.OnExitTask`  
`public class OnExitTask : BgTaskImpl`  
_public; L34-71_
- attrs: `[TaskElement("OnExit", typeof(OnExitTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Spawns an external executable and waits for it to complete.
- L36 _private* field_ `readonly OnExitTaskParameters _parameters`
- L42-45 _public ctor_ `public OnExitTask(OnExitTaskParameters parameters)` — Construct a spawn task
- L48-52 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — (inheritdoc)
- L55-58 _public method_ `public override void Write(XmlWriter writer)` — (inheritdoc)
- L61-64 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — (inheritdoc)
- L67-70 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — (inheritdoc)

### `Source/Programs/AutomationTool/BuildGraph/Tasks/PakFileTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.PakFileTaskParameters`  
`public class PakFileTaskParameters`  
_public; L19-74_
- desc: Parameters for a task that runs the cooker
- L25 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — List of files, wildcards, and tag sets to add to the pak file, separated by ';' characters.
- L31 _public property_ `public FileReference Output { get; set; }` — attrs: `[TaskParameter]` — PAK file to output.
- L37 _public property_ `public FileReference ResponseFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to a Response File that contains a list of files to add to the pak file -- instead of specifying them individually.
- L43 _public property_ `public HashSet<DirectoryReference> RebaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Directories to rebase the files relative to. If specified, the shortest path under a listed directory will be used for each file.
- L49 _public property_ `public FileReference Order { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Script that gives the order of files.
- L55 _public property_ `public FileReference Sign { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Encryption keys for this pak file.
- L61 _public property_ `public bool Compress { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to compress files.
- L67 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Additional arguments to pass to UnrealPak.
- L73 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.

#### class `AutomationTool.Tasks.PakFileTask`  
`public class PakFileTask : BgTaskImpl`  
_public; L80-227_
- attrs: `[TaskElement("PakFile", typeof(PakFileTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Creates a PAK file from a given set of files.
- L82 _private* field_ `readonly PakFileTaskParameters _parameters`
- L88-91 _public ctor_ `public PakFileTask(PakFileTaskParameters parameters)` — Constructor.
- L99-177 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L185-200 _public method_ `public static string FindShortestRelativePath(FileReference file, IEnumerable<DirectoryReference> rebaseDirs)` — Find the shortest relative path of the given file from a set of base directories.
- L205-208 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L214-217 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L223-226 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/QueryTargetsTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.QueryTargetsTaskParameters`  
`public class QueryTargetsTaskParameters`  
_public; L18-43_
- desc: Parameters to query for all the targets in a project
- L24 _public property_ `public FileReference? ProjectFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to the project file to query
- L30 _public property_ `public FileReference? OutputFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to the output file to receive information about the targets
- L36 _public property_ `public bool IncludeAllTargets { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Write out all targets, even if a default is specified in the BuildSettings section of the Default*.ini files.
- L42 _public property_ `public string? Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.

#### class `AutomationTool.Tasks.QueryTargetsTask`  
`public class QueryTargetsTask : BgTaskImpl`  
_public; L49-142_
- attrs: `[TaskElement("QueryTargets", typeof(QueryTargetsTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Runs UBT to query all the targets for a particular project
- L54 _private* field_ `readonly QueryTargetsTaskParameters _parameters` — Parameters for this task
- L60-63 _public ctor_ `public QueryTargetsTask(QueryTargetsTaskParameters parameters)` — Construct a spawn task
- L71-115 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L120-123 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L129-132 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L138-141 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/RandomDataTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.RandomDataTaskParameters`  
`public class RandomDataTaskParameters`  
_public; L15-52_
- desc: Parameters for RandomDataTask.
- L21 _public property_ `public int Seed { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Seed for the data generation
- L27 _public property_ `public int Size { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The size of each file.
- L33 _public property_ `public int Count { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Number of files to write.
- L39 _public property_ `public bool Different { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to generate different data for each output file.
- L45 _public property_ `public string OutputDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Output directory
- L51 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional filter to be applied to the list of input files.

#### class `AutomationTool.Tasks.RandomDataTask`  
`public class RandomDataTask : BgTaskImpl`  
_public; L58-140_
- attrs: `[TaskElement("RandomData", typeof(RandomDataTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Creates files containing random data in the specified output directory. Used for generating test data for the temp storage system.
- L60 _private* field_ `readonly RandomDataTaskParameters _parameters`
- L66-69 _public ctor_ `public RandomDataTask(RandomDataTaskParameters parameters)` — Constructor
- L77-113 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L118-121 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L127-130 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L136-139 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ReconcileTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ReconcileTaskParameters`  
`public class ReconcileTaskParameters`  
_public; L18-79_
- desc: Parameters for the submit task
- L24 _public property_ `public string Description { get; set; }` — attrs: `[TaskParameter]` — The description for the submitted changelist.
- L30 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — The files to reconcile
- L36 _public property_ `public string Directories { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The directories to reconcile, semi colon delimited, relative p4 syntax
- L42 _public property_ `public string Workspace { get; set; }` — attrs: `[TaskParameter(Optional=true)]` — The workspace name. If specified, a new workspace will be created using the given stream and root directory to submit the files. If not, the current workspace will be used.
- L48 _public property_ `public string Stream { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The stream for the workspace -- defaults to the current stream. Ignored unless the Workspace attribute is also specified.
- L54 _public property_ `public string Branch { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Branch for the workspace (legacy P4 depot path). May not be used in conjunction with Stream.
- L60 _public property_ `public DirectoryReference RootDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Root directory for the stream. If not specified, defaults to the current root directory.
- L66 _public property_ `public bool Force { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Force the submit to happen -- even if a resolve is needed (always accept current version).
- L72 _public property_ `public bool P4Verbose { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Allow verbose P4 output (spew).
- L78 _public property_ `public bool Preview { get; set; }` — attrs: `[TaskParameter(Optional = false)]` — Runs a reconcile preview, does not submit.

#### class `AutomationTool.Tasks.ReconcileTask`  
`public class ReconcileTask : BgTaskImpl`  
_public; L85-215_
- attrs: `[TaskElement("Reconcile", typeof(ReconcileTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Creates a new changelist and reconciles a set of files to submit to a Perforce stream.
- L90 _private* field_ `readonly ReconcileTaskParameters _parameters` — Parameters for the task
- L96-99 _public ctor_ `public ReconcileTask(ReconcileTaskParameters parameters)` — Construct a version task
- L107-188 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Execute the task.
- L193-196 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L202-205 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L211-214 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/RenameTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.RenameTaskParameters`  
`public class RenameTaskParameters`  
_public; L18-43_
- desc: Parameters for a copy task
- L24 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — The file or files to rename.
- L30 _public property_ `public string From { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The current file name, or pattern to match (for example, *.txt). Should not include any path separators.
- L36 _public property_ `public string To { get; set; }` — attrs: `[TaskParameter]` — The new name for the file(s). Should not include any path separators.
- L42 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to the renamed files.

#### class `AutomationTool.Tasks.RenameTask`  
`public class RenameTask : BgTaskImpl`  
_public; L49-170_
- attrs: `[TaskElement("Rename", typeof(RenameTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Renames a file, or group of files.
- L51 _private* field_ `readonly RenameTaskParameters _parameters`
- L57-60 _public ctor_ `public RenameTask(RenameTaskParameters parameters)` — Constructor
- L68-143 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L148-151 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L157-160 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L166-169 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/RetrieveArtifactTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.RetrieveArtifactTaskParameters`  
`public class RetrieveArtifactTaskParameters`  
_public; L26-82_
- desc: Parameters for a CreateArtifactTask.
- L32 _public property_ `public string? Stream { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Stream containing the artifact
- L38 _public property_ `public string? Commit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Change number for the artifact
- L44 _public property_ `public string? MaxCommit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Maximum commit for the artifact
- L50 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Name of the artifact
- L56 _public property_ `public string Type { get; set; }` — attrs: `[TaskParameter]` — The artifact type. Determines the permissions and expiration policy for the artifact.
- L62 _public property_ `public string Keys { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Keys for the artifact
- L68 _public property_ `public string? OutputDir { get; set; }` — attrs: `[TaskParameter]` — Output directory for
- L75 _public property_ `public bool ErrorIfNotFound { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether or not to throw an error if the artifact was not found
- L81 _public property_ `public bool ScopeToJobId { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Append the environment variable UE_HORDE_JOBID to the artifact query

#### class `AutomationTool.Tasks.RetrieveArtifactTask`  
`public class RetrieveArtifactTask : BgTaskImpl`  
_public; L88-235_
- attrs: `[TaskElement("RetrieveArtifact", typeof(RetrieveArtifactTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Retrieves an artifact from Horde
- L90 _private* field_ `readonly RetrieveArtifactTaskParameters _parameters`
- L96 _public ctor_ `public RetrieveArtifactTask(RetrieveArtifactTaskParameters parameters)` — Constructor.
- L100-222 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — (inheritdoc)
- L225 _public method_ `public override void Write(XmlWriter writer)` — (inheritdoc)
- L229 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — (inheritdoc)
- L233 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — (inheritdoc)

### `Source/Programs/AutomationTool/BuildGraph/Tasks/RetrieveCloudArtifactTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.RetrieveCloudArtifactTaskParameters`  
`public class RetrieveCloudArtifactTaskParameters`  
_public; L29-162_
- desc: Parameters for a RetrieveCloudArtifactTask.
- L35 _public property_ `public string? StreamId { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Stream containing the artifact
- L41 _public property_ `public string? Commit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Change number for the artifact
- L47 _public property_ `public bool? RequireMatchingCommit { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Requires that the current synced commit is the same as the artifacts commit
- L53 _public property_ `public string Name { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Name of the artifact
- L59 _public property_ `public string? BuildGroup { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional filter to require the artifact to be in build group
- L65 _public property_ `public string Type { get; set; }` — attrs: `[TaskParameter]` — The artifact type. Determines the permissions and expiration policy for the artifact.
- L71 _public property_ `public string Keys { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Keys for the artifact
- L77 _public property_ `public string? OutputDir { get; set; }` — attrs: `[TaskParameter]` — Output directory for
- L83 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter]` — The platform the artifact is created for
- L89 _public property_ `public FileReference? Project { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The path to the uproject this artifact is created for, this is optional if UAT is run with the -project option
- L95 _public property_ `public string? Host { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The platform the artifact is created for
- L101 _public property_ `public string? Namespace { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The platform the artifact is created for
- L107 _public property_ `public string? AccessToken { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The access token to use
- L113 _public property_ `public bool AllowMultipleMatches { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Set this to use the latest match if multiple artifacts are possible matches
- L119 _public property_ `public bool AllowMultipart { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Enable to use multipart endpoints if valuable
- L125 _public property_ `public string HttpVersion { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Set the explicit http version to use. None to use http handshaking.
- L131 _public property_ `public bool BoostWorkers { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Increase the number of worker threads used by zen, may cause machine to be less responsive but will generally improve download times
- L136 _public property_ `public bool EnableTracing { get; set; }` — Enable to create an Unreal Insights trace of the download process
- L142 _public property_ `public string? Include { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Optional pattern(s) to download from the artifact, if omitted the entire artifact is downloaded
- L148 _public property_ `public string? Exclude { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Optional pattern(s) to exclude from the copy for example, Engine/NoCopy*.txt)
- L155 _public property_ `public bool Append { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to append downloads to an existing directory (true) or to clear the directory before download (false) Set this to true if you want to download an artifact to a directory, then download an additional artifact from another without wiping state between
- L161 _public property_ `public bool Clean { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Delete all data in target folder that is not part of the downloaded content

#### class `AutomationTool.Tasks.RetrieveCloudArtifactTask`  
`public class RetrieveCloudArtifactTask : BgTaskImpl`  
_public; L168-437_
- attrs: `[TaskElement("RetrieveCloudArtifact", typeof(RetrieveCloudArtifactTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Retrieves an artifact from Cloud DDC
- L170 _private* field_ `readonly RetrieveCloudArtifactTaskParameters _parameters`
- L175 _protected property_ `protected RetrieveCloudArtifactTaskParameters Parameters => ...` — Parameters for the task.
- L181 _public ctor_ `public RetrieveCloudArtifactTask(RetrieveCloudArtifactTaskParameters parameters)` — Constructor.
- L190-424 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L427 _public method_ `public override void Write(XmlWriter writer)` — (inheritdoc)
- L431 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — (inheritdoc)
- L435 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — (inheritdoc)

### `Source/Programs/AutomationTool/BuildGraph/Tasks/SanitizeReceiptTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.SanitizeReceiptTaskParameters`  
`public class SanitizeReceiptTaskParameters`  
_public; L17-30_
- desc: Parameters for the Tag Receipt task.
- L23 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — Set of receipt files (*.target) to read, including wildcards and tag names, separated by semicolons.
- L29 _public property_ `public DirectoryReference EngineDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to the Engine folder, used to expand $(EngineDir) properties in receipt files. Defaults to the Engine directory for the current workspace.

#### class `AutomationTool.Tasks.SanitizeReceiptTask`  
`class SanitizeReceiptTask : BgTaskImpl`  
_internal*; L36-151_
- attrs: `[TaskElement("SanitizeReceipt", typeof(SanitizeReceiptTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Task that tags build products and/or runtime dependencies by reading from *.target files.
- L38 _private* field_ `readonly SanitizeReceiptTaskParameters _parameters`
- L44-47 _public ctor_ `public SanitizeReceiptTask(SanitizeReceiptTaskParameters parameters)` — Constructor
- L55-63 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L65-124 _public method_ `public static Task Execute(IEnumerable<FileReference> targetFiles, DirectoryReference engineDir)`
- L129-132 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L138-141 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are required by this task
- L147-150 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the referenced tags from tasks in this task

#### class `AutomationTool.Tasks.SanitizeReceiptExtensions`  
`public static class SanitizeReceiptExtensions`  
_public; L156-165_
- desc: Extension methods
- L161-164 _public method_ `public static async Task SanitizeReceiptsAsync(this FileSet targetFiles, DirectoryReference engineDir = null)` — Sanitize the given receipt files, removing any files that don't exist in the current workspace

### `Source/Programs/AutomationTool/BuildGraph/Tasks/SetVersionTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.SetVersionTaskParameters`  
`public class SetVersionTaskParameters`  
_public; L14-69_
- desc: Parameters for the version task
- L20 _public property_ `public int Change { get; set; }` — attrs: `[TaskParameter]` — The changelist to set in the version files.
- L26 _public property_ `public int CompatibleChange { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The engine compatible changelist to set in the version files.
- L32 _public property_ `public string Branch { get; set; }` — attrs: `[TaskParameter]` — The branch string.
- L38 _public property_ `public string Build { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The build version string.
- L44 _public property_ `public string BuildURL { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The URL for a running continuous integration job.
- L50 _public property_ `public bool Licensee { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to set the IS_LICENSEE_VERSION flag to true.
- L56 _public property_ `public bool Promoted { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to set the ENGINE_IS_PROMOTED_BUILD flag to true.
- L62 _public property_ `public bool SkipWrite { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — If set, do not write to the files -- just return the version files that would be updated. Useful for local builds.
- L68 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.

#### class `AutomationTool.Tasks.SetVersionTask`  
`public class SetVersionTask : BgTaskImpl`  
_public; L75-135_
- attrs: `[TaskElement("SetVersion", typeof(SetVersionTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Updates the local version files (Engine/Source/Runtime/Launch/Resources/Version.h, Engine/Build/Build.version, and Engine/Source/Programs/Shared/Metadata.cs) with the given version information.
- L77 _private* field_ `readonly SetVersionTaskParameters _parameters`
- L83-86 _public ctor_ `public SetVersionTask(SetVersionTaskParameters parameters)` — Construct a version task
- L94-108 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L113-116 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L122-125 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L131-134 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L140-170_
- desc: Task wrapper methods
- L147-152 _public method_ `public static async Task<FileSet> ExecuteAsync(BgTaskImpl task)` — ExecuteAsync a task instance
- L157-169 _public method_ `public static async Task<FileSet> SetVersionAsync(int change, string branch, int? compatibleChange = null, string build = null, string buildUrl = null, bool? licensee = null, bool? promoted = null, bool? skipWrite = null)` — Updates the current engine version

### `Source/Programs/AutomationTool/BuildGraph/Tasks/SignTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.SignTaskParameters`  
`public class SignTaskParameters`  
_public; L15-40_
- desc: Parameters for a task that signs a set of files.
- L21 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — List of file specifications separated by semicolons (for example, *.cpp;Engine/.../*.bat), or the name of a tag set.
- L27 _public property_ `public string Description { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional description for the signed content
- L33 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.
- L39 _public property_ `public bool Parallel { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — If true, the calls to the signing tool will be performed in parallel.

#### class `AutomationTool.Tasks.SignTask`  
`public class SignTask : BgTaskImpl`  
_public; L46-112_
- attrs: `[TaskElement("Sign", typeof(SignTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Signs a set of executable files with an installed certificate.
- L51 _private* field_ `readonly SignTaskParameters _parameters` — Parameters for this task
- L57-60 _public ctor_ `public SignTask(SignTaskParameters parameters)` — Construct a spawn task
- L68-85 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L90-93 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L99-102 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L108-111 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/SpawnTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.SpawnTaskParameters`  
`public class SpawnTaskParameters`  
_public; L15-58_
- desc: Parameters for a spawn task
- L21 _public property_ `public string Exe { get; set; }` — attrs: `[TaskParameter]` — Executable to spawn.
- L27 _public property_ `public string Arguments { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Arguments for the newly created process.
- L33 _public property_ `public string WorkingDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Working directory for spawning the new task
- L39 _public property_ `public string Environment { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Environment variables to set
- L45 _public property_ `public string EnvironmentFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — File to read environment from
- L51 _public property_ `public bool LogOutput { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Write output to the log
- L57 _public property_ `public int ErrorLevel { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The minimum exit code, which is treated as an error.

#### class `AutomationTool.Tasks.SpawnTaskBase`  
`public abstract class SpawnTaskBase : BgTaskImpl`  
_public; L63-143_
- inherits: `BgTaskImpl`
- desc: Base class for tasks that run an external tool
- L68-88 _protected method_ `protected static Task<IProcessResult> ExecuteAsync(string exe, string arguments, string workingDir = null, Dictionary<string, string> envVars = null, bool logOutput = true, int errorLevel = 1, string input = null, ProcessResult.SpewFilterCallbackType spewFilterCallback = null)` — ExecuteAsync a command
- L96-108 _protected method_ `protected static Dictionary<string, string> ParseEnvVars(string environment, string environmentFile)` — Parses environment from a property and file
- L116-142 _private* method_ `static void ParseEnvironment(string environment, char separator, Dictionary<string, string> envVars)` — Parse environment from a string

#### class `AutomationTool.Tasks.SpawnTask`  
`public class SpawnTask : SpawnTaskBase`  
_public; L149-201_
- attrs: `[TaskElement("Spawn", typeof(SpawnTaskParameters))]`
- inherits: `SpawnTaskBase`
- desc: Spawns an external executable and waits for it to complete.
- L154 _private* field_ `readonly SpawnTaskParameters _parameters` — Parameters for this task
- L160-163 _public ctor_ `public SpawnTask(SpawnTaskParameters parameters)` — Construct a spawn task
- L171-174 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L179-182 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L188-191 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L197-200 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L203-228_
- L215-227 _public method_ `public static async Task SpawnAsync(string exe, string arguments = null, string workingDir = null, string environment = null, string environmentFile = null, bool? logOutput = null, int? errorLevel = null)` — ExecuteAsync an external program

### `Source/Programs/AutomationTool/BuildGraph/Tasks/StageTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.StageTaskParameters`  
`public class StageTaskParameters`  
_public; L16-65_
- desc: Parameters for the staging task
- L22 _public property_ `public FileReference Project { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The project that this target belongs to.
- L28 _public property_ `public string Target { get; set; }` — attrs: `[TaskParameter]` — Name of the target to stage.
- L34 _public property_ `public UnrealTargetPlatform Platform { get; set; }` — attrs: `[TaskParameter]` — Platform to stage.
- L40 _public property_ `public UnrealTargetConfiguration Configuration { get; set; }` — attrs: `[TaskParameter]` — Configuration to be staged.
- L46 _public property_ `public string Architecture { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Architecture to be staged.
- L52 _public property_ `public DirectoryReference ToDir { get; set; }` — attrs: `[TaskParameter]` — Directory that the receipt files should be staged to.
- L58 _public property_ `public bool Overwrite { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to overwrite existing files.
- L64 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.

#### class `AutomationTool.Tasks.StageTask`  
`public class StageTask : BgTaskImpl`  
_public; L71-193_
- attrs: `[TaskElement("Stage", typeof(StageTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Stages files listed in a build receipt to an output directory.
- L73 _private* field_ `readonly StageTaskParameters _parameters`
- L79-82 _public ctor_ `public StageTask(StageTaskParameters parameters)` — Constructor.
- L90-166 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L171-174 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L180-183 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L189-192 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/StripTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.StripTaskParameters`  
`public class StripTaskParameters`  
_public; L17-54_
- desc: Parameters for a task that strips symbols from a set of files
- L23 _public property_ `public UnrealTargetPlatform Platform { get; set; }` — attrs: `[TaskParameter]` — The platform toolchain to strip binaries.
- L29 _public property_ `public DirectoryReference BaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The directory to find files in.
- L35 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — List of file specifications separated by semicolons (for example, Engine/.../*.pdb), or the name of a tag set.
- L41 _public property_ `public DirectoryReference OutputDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Output directory for the stripped files. Defaults to the input path, overwriting the input files.
- L47 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.
- L53 _public property_ `public bool StripAll { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether all symbols should be stripped. Not relevant to all platforms.

#### class `AutomationTool.Tasks.StripTask`  
`public class StripTask : BgTaskImpl`  
_public; L60-153_
- attrs: `[TaskElement("Strip", typeof(StripTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Strips debugging information from a set of files.
- L62 _private* field_ `readonly StripTaskParameters _parameters`
- L68-71 _public ctor_ `public StripTask(StripTaskParameters parameters)` — Construct a spawn task
- L79-126 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L131-134 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L140-143 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L149-152 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.StandardTasks`  
`public static partial class StandardTasks`  
_public; L155-174_
- L165-173 _public method_ `public static async Task<FileSet> StripAsync(FileSet files, UnrealTargetPlatform platform, DirectoryReference baseDir = null, DirectoryReference outputDir = null)` — Strips symbols from a set of files.

### `Source/Programs/AutomationTool/BuildGraph/Tasks/SubmitTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.SubmitTaskParameters`  
`public class SubmitTaskParameters`  
_public; L17-78_
- desc: Parameters for the submit task
- L23 _public property_ `public string Description { get; set; }` — attrs: `[TaskParameter]` — The description for the submitted changelist.
- L29 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — The files to submit.
- L35 _public property_ `public string FileType { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The Perforce file type for the submitted files (for example, binary+FS32).
- L41 _public property_ `public string Workspace { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The workspace name. If specified, a new workspace will be created using the given stream and root directory to submit the files. If not, the current workspace will be used.
- L47 _public property_ `public string Stream { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The stream for the workspace -- defaults to the current stream. Ignored unless the Workspace attribute is also specified.
- L53 _public property_ `public string Branch { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Branch for the workspace (legacy P4 depot path). May not be used in conjunction with Stream.
- L59 _public property_ `public DirectoryReference RootDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Root directory for the stream. If not specified, defaults to the current root directory.
- L65 _public property_ `public bool RevertUnchanged { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to revert unchanged files before attempting to submit.
- L71 _public property_ `public bool Force { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Force the submit to happen -- even if a resolve is needed (always accept current version).
- L77 _public property_ `public bool P4Verbose { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Allow verbose P4 output (spew).

#### class `AutomationTool.Tasks.SubmitTask`  
`public class SubmitTask : BgTaskImpl`  
_public; L84-213_
- attrs: `[TaskElement("Submit", typeof(SubmitTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Creates a new changelist and submits a set of files to a Perforce stream.
- L86 _private* field_ `readonly SubmitTaskParameters _parameters`
- L92-95 _public ctor_ `public SubmitTask(SubmitTaskParameters parameters)` — Construct a version task
- L103-186 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L191-194 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L200-203 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L209-212 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/SymGenTask.cs` (BuildGraph.Automation)


#### class `BuildGraph.Tasks.SymGenTaskParameters`  
`public class SymGenTaskParameters`  
_public; L21-41_
- desc: Parameters for a task that generates debugging symbols from a set of files
- L27 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — List of file specifications separated by semicolons (eg. *.cpp;Engine/.../*.bat), or the name of a tag set
- L33 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task
- L39 _public property_ `public bool UseRadSym { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — If set, this will use the rad debugger pdb symbol dumper as well as the rad symbol_path_fixer.

#### class `BuildGraph.Tasks.SymGenTask`  
`public class SymGenTask : CustomTask`  
_public; L47-378_
- attrs: `[TaskElement("SymGen", typeof(SymGenTaskParameters))]`
- inherits: `CustomTask`
- desc: Generates a portable symbol dump file from the specified binaries
- L52 _private* field_ `readonly SymGenTaskParameters _parameters` — Parameters for this task
- L58-61 _public ctor_ `public SymGenTask(SymGenTaskParameters parameters)` — Construct a spawn task
- L63-81 _private* method_ `static UnrealArchitectures ArchitecturesInBinary(FileReference binary)`
- L89-267 _public method_ `public override void Execute(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Execute the task.
- L273-330 _private* method_ `static bool ProcessSymbols(StringBuilderReader reader, TextWriter writer)`
- L335-346 _private* method_ `string FilterSpew(string message)` — Filters the output from the dump_syms executable, which depending on the platform can be pretty spammy
- L351 _private* field_ `static readonly string[] s_outputFilterStrings = new string[] { "the DIE at offset", "warning: function", "warning: failed", ": in compilation unit" }` — Array of source strings to filter from output
- L356-359 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L365-368 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L374-377 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `BuildScripts.Automation.GeneratePsyms`  
`class GeneratePsyms : BuildCommand`  
_internal*; L383-395_
- inherits: `BuildCommand`
- L385-394 _public method_ `public override ExitCode Execute()`

### `Source/Programs/AutomationTool/BuildGraph/Tasks/SymStoreTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.SymStoreTaskParameters`  
`public class SymStoreTaskParameters`  
_public; L18-95_
- desc: Parameters for a task that uploads symbols to a symbol server
- L24 _public property_ `public UnrealTargetPlatform Platform { get; set; }` — attrs: `[TaskParameter]` — The platform toolchain required to handle symbol files.
- L30 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter]` — List of output files. PDBs will be extracted from this list.
- L36 _public property_ `public string StoreDir { get; set; }` — attrs: `[TaskParameter]` — Output directory for the compressed symbols.
- L42 _public property_ `public string Product { get; set; }` — attrs: `[TaskParameter]` — Name of the product for the symbol store records.
- L49 _public property_ `public string Branch { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Name of the Branch to base all the depot source files from. Used when IndexSources is true (may be used only on some platforms).
- L56 _public property_ `public int Change { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Changelist to which all the depot source files have been synced to. Used when IndexSources is true (may be used only on some platforms).
- L62 _public property_ `public string BuildVersion { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — BuildVersion associated with these symbols. Used for clean-up in AgeStore by matching this version against a directory name in a build share.
- L70 _public property_ `public bool IndexSources { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to include the source code index in the uploaded symbols. When enabled, the task will generate data required by a source server (only some platforms and source control servers are supported). The source server allows debuggers to automatically fetch the matching source code when debbugging builds or analyzing dumps.
- L79 _public property_ `public string SourceFiles { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Filter for the depot source files that are to be indexed. It's a semicolon-separated list of perforce filter e.g. Engine/....cpp;Engine/....h. It may also be a name of a previously defined tag e.g. "#SourceFiles Used when IndexSources is true (may be used only on some platforms).
- L94 _public property_ `public string VFSMapping { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — List of file path mappings to be applied during source indexing. It is needed only when using VFS (Virtual File System) feature when compiling the binary. VFS replaces the real local paths used with standardized paths like Z:\UEVFS\... Since these virtualized paths don't match paths used by the local workspace, we need to map them manually so that paths in object files/symbols matched the data we have in source indexing. It's a semicolon-separated list of path assignments e.g. "[Root]\Samples\Games\SampleGame=Z:\UEVFS\SampleGame;[Root]=Z:\UEVFS\Root" [Root] will be replaced with Unreal.RootDirectory. You need to ensure that the mapping used here matches the conventions used by Unreal Build Tool. We may improve it in the future but current the VFS mapping used during compilation is not available outside of UBT.

#### class `AutomationTool.Tasks.SymStoreTask`  
`public class SymStoreTask : BgTaskImpl`  
_public; L101-193_
- attrs: `[TaskElement("SymStore", typeof(SymStoreTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Task that strips symbols from a set of files.
- L106 _private* field_ `readonly SymStoreTaskParameters _parameters` — Parameters for this task
- L112-115 _public ctor_ `public SymStoreTask(SymStoreTaskParameters parameters)` — Construct a spawn task
- L123-166 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L171-174 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L180-183 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L189-192 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/TagReceiptTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.TagReceiptTaskParameters`  
`public class TagReceiptTaskParameters`  
_public; L17-66_
- desc: Parameters for the Tag Receipt task.
- L23 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — Set of receipt files (*.target) to read, including wildcards and tag names, separated by semicolons.
- L29 _public property_ `public DirectoryReference EngineDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to the Engine folder, used to expand $(EngineDir) properties in receipt files. Defaults to the Engine directory for the current workspace.
- L35 _public property_ `public DirectoryReference ProjectDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Path to the project folder, used to expand $(ProjectDir) properties in receipt files. Defaults to the Engine directory for the current workspace -- DEPRECATED.
- L41 _public property_ `public bool BuildProducts { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to tag the Build Products listed in receipts.
- L47 _public property_ `public string BuildProductType { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Which type of Build Products to tag (see TargetReceipt.cs - UnrealBuildTool.BuildProductType for valid values).
- L53 _public property_ `public bool RuntimeDependencies { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether to tag the Runtime Dependencies listed in receipts.
- L59 _public property_ `public string StagedFileType { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Which type of Runtime Dependencies to tag (see TargetReceipt.cs - UnrealBuildTool.StagedFileType for valid values).
- L65 _public property_ `public string With { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.TagList)]` — Name of the tag to apply.

#### class `AutomationTool.Tasks.TagReceiptTask`  
`class TagReceiptTask : BgTaskImpl`  
_internal*; L72-226_
- attrs: `[TaskElement("TagReceipt", typeof(TagReceiptTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Task that tags build products and/or runtime dependencies by reading from *.target files.
- L77 _private* field_ `readonly TagReceiptTaskParameters _parameters` — Parameters to this task
- L82 _private* field_ `readonly BuildProductType? _buildProductType` — The type of build products to enumerate. May be null.
- L87 _private* field_ `readonly StagedFileType? _stagedFileType` — The type of staged files to enumerate. May be null,
- L93-105 _public ctor_ `public TagReceiptTask(TagReceiptTaskParameters parameters)` — Constructor
- L113-132 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L134-199 _public method_ `public static Task<HashSet<FileReference>> Execute(DirectoryReference engineDir, IEnumerable<FileReference> targetFiles, bool buildProducts, BuildProductType? buildProductType, bool runtimeDependencies, StagedFileType? stagedFileType = null)`
- L204-207 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L213-216 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are required by this task
- L222-225 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the referenced tags from tasks in this task

#### class `AutomationTool.Tasks.TaskExtensions`  
`public static class TaskExtensions`  
_public; L231-241_
- desc: Extension methods
- L236-240 _public method_ `public static async Task<FileSet> TagReceiptsAsync(this FileSet files, DirectoryReference engineDir = null, bool buildProducts = false, BuildProductType? buildProductType = null, bool runtimeDependencies = false, StagedFileType? stagedFileType = null)` — Task that tags build products and/or runtime dependencies by reading from *.target files.

### `Source/Programs/AutomationTool/BuildGraph/Tasks/TagTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.TagTaskParameters`  
`public class TagTaskParameters`  
_public; L15-52_
- desc: Parameters for the Tag task.
- L21 _public property_ `public DirectoryReference BaseDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Set the base directory to resolve relative paths and patterns against. If set, any absolute patterns (for example, /Engine/Build/...) are taken to be relative to this path. If not, they are taken to be truly absolute.
- L27 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Set of files to work from, including wildcards and tag names, separated by semicolons. If set, resolved relative to BaseDir, otherwise resolved to the branch root directory.
- L33 _public property_ `public string FileLists { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Set of text files to add additional files from. Each file list should have one file per line.
- L39 _public property_ `public string Filter { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Patterns to filter the list of files by, including tag names or wildcards. If set, may include patterns that apply to the base directory. If not specified, defaults to all files.
- L45 _public property_ `public string Except { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — Set of patterns to exclude from the matched list. May include tag names of patterns that apply to the base directory.
- L51 _public property_ `public string With { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.TagList)]` — Name of the tag to apply.

#### class `AutomationTool.Tasks.TagTask`  
`class TagTask : BgTaskImpl`  
_internal*; L59-224_
- attrs: `[TaskElement("Tag", typeof(TagTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Applies a tag to a given set of files. The list of files is found by enumerating the tags and file specifications given by the 'Files' parameter. From this list, any files not matched by the 'Filter' parameter are removed, followed by any files matched by the 'Except' parameter.
- L61 _private* field_ `readonly TagTaskParameters _parameters`
- L67-70 _public ctor_ `public TagTask(TagTaskParameters parameters)` — Constructor
- L78-129 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L138-178 _private* method_ `static List<string> ParseRules(DirectoryReference baseDir, string delimitedPatterns, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Add rules matching a given set of patterns to a file filter. Patterns are added as absolute paths from the root.
- L183-186 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L192-214 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are modified by this task
- L220-223 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the referenced tags from tasks in this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/UnzipTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.UnzipTaskParameters`  
`public class UnzipTaskParameters`  
_public; L15-46_
- desc: Parameters for a zip task
- L21 _public property_ `public string ZipFile { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — Path to the zip file to extract.
- L27 _public property_ `public DirectoryReference ToDir { get; set; }` — attrs: `[TaskParameter]` — Output directory for the extracted files.
- L33 _public property_ `public bool UseLegacyUnzip { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether or not to use the legacy unzip code.
- L39 _public property_ `public bool OverwriteFiles { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Whether or not to overwrite files during unzip.
- L45 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to the extracted files.

#### class `AutomationTool.Tasks.UnzipTask`  
`public class UnzipTask : BgTaskImpl`  
_public; L52-128_
- attrs: `[TaskElement("Unzip", typeof(UnzipTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Extract files from a zip archive.
- L54 _private* field_ `readonly UnzipTaskParameters _parameters`
- L60-63 _public ctor_ `public UnzipTask(UnzipTaskParameters parameters)` — Constructor
- L71-101 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L106-109 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L115-118 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L124-127 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/UploadCloudSymbolsTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.UploadCloudSymbolsTaskParameters`  
`public class UploadCloudSymbolsTaskParameters`  
_public; L26-51_
- desc: Parameters for a task that uploads symbols to the cloud
- L32 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — List of output files. PDBs will be extracted from this list.
- L38 _public property_ `public string? Host { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The cloud host to which symbols should be uploaded
- L44 _public property_ `public string? AccessToken { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The access token to use
- L50 _public property_ `public string? Namespace { get; set; }` — attrs: `[TaskParameter]` — The destination namespace to which symbols should be uploaded

#### class `AutomationTool.Tasks.UploadCloudSymbolsTask`  
`public class UploadCloudSymbolsTask : BgTaskImpl`  
_public; L57-554_
- attrs: `[TaskElement("UploadCloudSymbols", typeof(UploadCloudSymbolsTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Task that strips symbols from a set of files.
- L62 _private* field_ `readonly UploadCloudSymbolsTaskParameters _parameters` — Parameters for this task
- L68-71 _public ctor_ `public UploadCloudSymbolsTask(UploadCloudSymbolsTaskParameters parameters)` — Construct a spawn task
- L79-129 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L131-156 _private method_ `private Uri GetCloudHost()`
- L158-183 _private method_ `private string GetAccessToken()`
- L192-222 _private method_ `private static async Task<List<ChunkMetadata>> ChunkAsync(Stream stream, int fixedChunkSize = 64 * 1024 * 1024)`
- L224-237 _private method_ `private async Task<NeedsResponse> PutModuleAsync(HttpClient httpClient, string moduleName, Stream stream, List<ChunkMetadata> chunks)`
- L239-251 _private method_ `private async Task PutBlobAsync(HttpClient httpClient, string moduleName, IoHash hash, byte[] chunk)`
- L253-300 _private method_ `private static async Task<HttpResponseMessage> CallWithRetriesAsync(Func<Task<HttpResponseMessage>> func, int maxAttempts = 10, double initialBackoffSeconds = 0.5, double maxBackoffSeconds = 60.0)`
- L302-325 _private method_ `private static byte[] CreatePutSymbolsPayload(List<ChunkMetadata> pdbChunks, string moduleName, string pdbIdentifier, int pdbAge, long pdbSize)`
- L327-337 _private method_ `private static (string pdbGuid, int pdbAge) ExtractModuleInformation(string moduleName, Stream stream)`
- L339-498 _private method_ `private static (string pdbGuid, int pdbAge) ExtractModuleInformationPdb(Stream stream)`
- L503-506 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L512-515 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L521-524 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### struct `AutomationTool.Tasks.UploadCloudSymbolsTask.ChunkMetadata`  
`private readonly struct ChunkMetadata(IoHash hash, long offset, long length)`  
_private; L185-190_
- L187 _public property_ `public IoHash Hash { get; }`
- L188 _public property_ `public long Offset { get; }`
- L189 _public property_ `public long Length { get; }`

#### class `AutomationTool.Tasks.UploadCloudSymbolsTask.NeedsResponse`  
`class NeedsResponse`  
_private*; L526-540_
- L528-531 _public ctor_ `public NeedsResponse()`
- L533-536 _public ctor_ `public NeedsResponse(List<IoHash> needs)`
- L539 _public property_ `public List<IoHash> Needs { get; set; }` — attrs: `[CbField("needs")]`

#### class `AutomationTool.Tasks.UploadCloudSymbolsTask.CustomMediaTypeNames`  
`static class CustomMediaTypeNames`  
_private*; L542-553_
- L547 _public const_ `public const string UnrealCompactBinary = "application/x-ue-cb"` — Media type for compact binary
- L552 _public const_ `public const string UnrealCompressedBuffer = "application/x-ue-comp"` — Media type for compressed buffers

### `Source/Programs/AutomationTool/BuildGraph/Tasks/WaitTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.WaitTaskParameters`  
`public class WaitTaskParameters`  
_public; L14-21_
- desc: Parameters for a wait task
- L20 _public property_ `public int Seconds { get; set; }` — attrs: `[TaskParameter]` — Number of seconds to wait.

#### class `AutomationTool.Tasks.WaitTask`  
`public class WaitTask : BgTaskImpl`  
_public; L27-76_
- attrs: `[TaskElement("Wait", typeof(WaitTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Waits a defined number of seconds.
- L29 _private* field_ `readonly WaitTaskParameters _parameters`
- L35-38 _public ctor_ `public WaitTask(WaitTaskParameters parameters)` — Construct a wait task
- L46-49 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L54-57 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L63-66 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L72-75 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/WriteJsonValueTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.WriteJsonValueTaskParameters`  
`public class WriteJsonValueTaskParameters`  
_public; L21-42_
- desc: Parameters for WriteJsonValueTask task
- L27 _public property_ `public string File { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.FileSpec)]` — Json file(s) which will be modified
- L35 _public property_ `public string Key { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.Default)]` — Json element to set in each file. Syntax for this string is a limited subset of JsonPath notation, and may support object properties and array indices. Any array indices which are omitted or out of range will add a new element to the array (eg. '$.foo.bar[]' will add an element to the 'bar' array in the 'foo' object).
- L41 _public property_ `public string Value { get; set; }` — attrs: `[TaskParameter(ValidationType = TaskParameterValidationType.Default)]` — New value to set. May be any value JSON value (string, array, object, number, boolean or null).

#### class `AutomationTool.Tasks.WriteJsonValueTask`  
`public class WriteJsonValueTask : BgTaskImpl`  
_public; L48-202_
- attrs: `[TaskElement("WriteJsonValue", typeof(WriteJsonValueTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Modifies json files by setting a value specified in the key path
- L50 _private* field_ `readonly WriteJsonValueTaskParameters _parameters`
- L56-59 _public ctor_ `public WriteJsonValueTask(WriteJsonValueTaskParameters parameters)` — Create a new ModifyJsonValue.
- L64-103 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — Placeholder comment
- L105-174 _private* method_ `static JsonNode? MergeValue(string key, int minIdx, JsonNode? prevValue, JsonNode? value)`
- L179-182 _public method_ `public override void Write(XmlWriter writer)` — Placeholder comment
- L187-193 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Placeholder comment
- L198-201 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Placeholder comment

### `Source/Programs/AutomationTool/BuildGraph/Tasks/WriteTextFileTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.WriteTextFileTaskParameters`  
`public class WriteTextFileTaskParameters`  
_public; L17-48_
- desc: Parameters for a WriteTextFileTask.
- L23 _public property_ `public FileReference File { get; set; }` — attrs: `[TaskParameter]` — Path to the file to write.
- L29 _public property_ `public bool Append { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional, whether or not to append to the file rather than overwrite.
- L35 _public property_ `public string Text { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The text to write to the file.
- L41 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — If specified, causes the given list of files to be printed after the given message.
- L47 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to build products of this task.

#### class `AutomationTool.Tasks.WriteTextFileTask`  
`public class WriteTextFileTask : BgTaskImpl`  
_public; L54-150_
- attrs: `[TaskElement("WriteTextFile", typeof(WriteTextFileTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Writes text to a file.
- L59 _private* field_ `readonly WriteTextFileTaskParameters _parameters` — Parameters for this task.
- L65-68 _public ctor_ `public WriteTextFileTask(WriteTextFileTaskParameters parameters)` — Constructor.
- L76-120 _public method_ `public override async Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L125-128 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L134-140 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L146-149 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ZenExportSnapshotTask.cs` (BuildGraph.Automation)


#### enum `AutomationTool.Tasks.SnapshotStorageType`  
`public enum SnapshotStorageType`  
_public; L26-48_
- desc: Enumeration of different storage options for snapshots.
- L31 _public* enumerator_ `Invalid` — A reserved non-valid storage type for snapshots.
- L35 _public* enumerator_ `Cloud` — Snapshot stored in cloud repository such as Unreal Cloud DDC.
- L39 _public* enumerator_ `Builds` — Snapshot stored in builds repository such as Unreal Cloud DDC.
- L43 _public* enumerator_ `Zen` — Snapshot stored in a zenserver.
- L47 _public* enumerator_ `File` — Snapshot stored as a file on disk.

#### class `AutomationTool.Tasks.ZenExportSnapshotTaskParameters`  
`public class ZenExportSnapshotTaskParameters`  
_public; L53-175_
- desc: Parameters for a task that exports an snapshot from ZenServer
- L59 _public property_ `public FileReference Project { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The project from which to export the snapshot
- L65 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The target platform(s) to export the snapshot for
- L71 _public property_ `public string Metadata { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The metadata to associate with the snapshot
- L77 _public property_ `public FileReference SnapshotBaseDescriptorFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — A file to read with information about the snapshot that should be used as a base when exporting this new snapshot
- L83 _public property_ `public FileReference SnapshotDescriptorFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — A file to create with information about the snapshot that was exported
- L89 _public property_ `public string DestinationStorageType { get; set; }` — attrs: `[TaskParameter]` — The type of destination to export the snapshot to (cloud, ...)
- L95 _public property_ `public string DestinationIdentifier { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The identifier to use when exporting to a destination
- L101 _public property_ `public string DestinationCloudHost { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The host name to use when exporting to a cloud destination
- L107 _public property_ `public string SnapshotDescriptorCloudHost { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The host name to use when writing a snapshot descriptor for a cloud destination
- L113 _public property_ `public string SnapshotDescriptorPlatform { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The target platform to use when writing a snapshot descriptor
- L119 _public property_ `public string DestinationCloudHttpVersion { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The http version to use when exporting to a cloud destination
- L125 _public property_ `public string SnapshotDescriptorCloudHttpVersion { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The http version to use when writing a snapshot descriptor for a cloud destination
- L131 _public property_ `public string DestinationCloudNamespace { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The namespace to use when exporting to a cloud destination
- L137 _public property_ `public string DestinationCloudBucket { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — A custom bucket name to use when exporting to a cloud destination
- L143 _public property_ `public string DestinationZenHost { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The host name to use when exporting to a zen destination
- L149 _public property_ `public DirectoryReference DestinationFileDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The directory to use when exporting to a file destination
- L155 _public property_ `public string DestinationFileName { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The filename to use when exporting to a file destination
- L162 _public property_ `public string OverridePlatformCookedDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Where to look for the ue.projectstore The pattern {Platform} can be used for exporting multiple platforms at once.
- L168 _public property_ `public bool ForceExport { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Whether to force export of data even if the destination claims to have them.
- L174 _public property_ `public bool SkipExport { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Whether to entirely bypass the exporting of data and write a snapshot descriptor as if the data had been exported.

#### class `AutomationTool.Tasks.ZenExportSnapshotTask`  
`public class ZenExportSnapshotTask : BgTaskImpl`  
_public; L181-917_
- attrs: `[TaskElement("ZenExportSnapshot", typeof(ZenExportSnapshotTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Exports an snapshot from Zen to a specified destination.
- L258 _private* field_ `readonly ZenExportSnapshotTaskParameters _parameters` — Parameters for the task
- L264-267 _public ctor_ `public ZenExportSnapshotTask(ZenExportSnapshotTaskParameters parameters)` — Constructor.
- L273-276 _public method_ `public static FileReference ZenExeFileReference()` — Gets the assumed path to where Zen should exist
- L284-293 _public method_ `public static void ZenLaunch(FileReference projectFile)` — Ensures that ZenServer is running on this current machine. This is needed before running any oplog commands This passes the sponsor'd process Id to launch zen. This ensures that zen does not live longer than the lifetime of a particular a process that needs Zen to be running
- L295-303 _private* method_ `static JsonSerializerOptions GetDefaultJsonSerializerOptions()`
- L306-324 _private* method_ `static bool TryLoadJson<T>(FileReference file, [NotNullWhen(true)] out T? obj) where T : class`
- L326-330 _private* method_ `static T LoadJson<T>(FileReference file)`
- L332-335 _private* method_ `static string SanitizeOplogName(string name)`
- L337-347 _private method_ `private string GetCloudBucketName()`
- L349-414 _private method_ `private void WriteExportSource(JsonWriter writer, SnapshotStorageType destinationStorageType, ExportSourceData exportSource, string name, string destinationId)`
- L416-439 _private method_ `private static bool TryRunAndLogWithoutSpew(string app, string commandLine, bool ignoreFailure, out int exitCode)`
- L441-467 _private method_ `private static bool TryExportOplogCommand(string app, string commandLine)`
- L469 _private method_ `private static bool IsValidCharacter(char character)`
- L471-486 _private method_ `private static bool IsValidCharacter(byte character)`
- L488-528 _private method_ `private static string SanitizeBucketName(string inString)`
- L536-890 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L895-898 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L904-907 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L913-916 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `AutomationTool.Tasks.ZenExportSnapshotTask.SnapshotDescriptor`  
`class SnapshotDescriptor`  
_private*; L186-232_
- desc: Metadata about a snapshot
- L191 _public property_ `public string Name { get; set; }` — Name of the snapshot
- L196 _public property_ `public SnapshotStorageType Type { get; set; }` — Storage type used for the snapshot
- L201 _public property_ `public string TargetPlatform { get; set; }` — Target platform for this snapshot
- L206 _public property_ `public string Host { get; set; }` — For cloud snapshots, the host they are stored on.
- L211 _public property_ `public string Namespace { get; set; }` — For cloud snapshots, the namespace they are stored in.
- L216 _public property_ `public string Bucket { get; set; }` — For cloud snapshots, the bucket they are stored in.
- L221 _public property_ `public string Key { get; set; }` — For cloud snapshots, the key they are stored in.
- L226 _public property_ `public string Directory { get; set; }` — For file snapshots, the directory it is stored in.
- L231 _public property_ `public string Filename { get; set; }` — For file snapshots, the filename (not including path) that they are stored in.

#### class `AutomationTool.Tasks.ZenExportSnapshotTask.SnapshotDescriptorCollection`  
`class SnapshotDescriptorCollection`  
_private*; L236-242_
- desc: A collection of one or more snapshot descriptors
- L241 _public property_ `public List<SnapshotDescriptor> Snapshots { get; set; }` — The list of snapshots contained within this collection.

#### class `AutomationTool.Tasks.ZenExportSnapshotTask.ExportSourceData`  
`private class ExportSourceData`  
_private; L244-253_
- L246 _public field_ `public bool _isLocalHost`
- L247 _public field_ `public string _hostName`
- L248 _public field_ `public int _hostPort`
- L249 _public field_ `public string _projectId`
- L250 _public field_ `public string _oplogId`
- L251 _public field_ `public string _targetPlatform`
- L252 _public field_ `public SnapshotDescriptor _snapshotBaseDescriptor`

#### struct `AutomationTool.Tasks.CloudConfiguration`  
`struct CloudConfiguration`  
_internal*; L919-928_
- L922 _public field_ `public string Host = ""`
- L923 _public field_ `public string BuildsNamespace = ""`
- L924 _public field_ `public string BuildsBaselineBranch = ""`
- L927 _public ctor_ `public CloudConfiguration()`

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ZenImportOplogTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ZenImportOplogTaskParameters`  
`public class ZenImportOplogTaskParameters`  
_public; L21-101_
- desc: Parameters for a task that exports an snapshot from ZenServer
- L27 _public property_ `public string ImportType { get; set; }` — attrs: `[TaskParameter]` — The type of destination to import from to (cloud, file...)
- L34 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — comma separated full path to the oplog dir to import into the local zen server Files="Path1,Path2"
- L40 _public property_ `public FileReference Project { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The project from which to import for
- L46 _public property_ `public string ProjectName { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The name of the newly created Zen Project we will be importing into
- L52 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The target platform to import the snapshot for
- L58 _public property_ `public string RootDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Root dir for the UE project. Used to derive the Enging folder and the Project folder
- L64 _public property_ `public string OplogName { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The name of the imported oplog
- L70 _public property_ `public string HostName { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The host URL for the zen server we are importing from
- L76 _public property_ `public string HostPort { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The host port for the zen server we are importing from
- L82 _public property_ `public string CloudURL { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The cloud URL to import from
- L88 _public property_ `public string Namespace { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — what namespace to use when importing from cloud
- L94 _public property_ `public string Bucket { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — what bucket to use when importing from cloud
- L100 _public property_ `public string Key { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — What key to use when importing from cloud

#### class `AutomationTool.Tasks.ZenImportOplogTask`  
`public class ZenImportOplogTask : BgTaskImpl`  
_public; L107-292_
- attrs: `[TaskElement("ZenImportOplog", typeof(ZenImportOplogTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Imports an oplog from Zen to a specified destination.
- L109 _private* field_ `readonly ZenImportOplogTaskParameters _parameters`
- L111 _private* field_ `FileReference _projectFile`
- L117-120 _public ctor_ `public ZenImportOplogTask(ZenImportOplogTaskParameters parameters)` — Constructor.
- L128-188 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L190-208 _private method_ `private void ImportFromFile(FileReference zenExe)`
- L210-234 _private method_ `private void WriteProjectStoreFile()`
- L236-265 _private method_ `private void ImportFromCloud(FileReference zenExe)`
- L270-273 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L279-282 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L288-291 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ZenImportSnapshotTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ZenImportSnapshotTaskParameters`  
`public class ZenImportSnapshotTaskParameters`  
_public; L25-81_
- desc: Parameters for a task that imports snapshots into ZenServer
- L31 _public property_ `public FileReference Project { get; set; }` — attrs: `[TaskParameter]` — The project into which snapshots should be imported
- L37 _public property_ `public FileReference SnapshotDescriptorFile { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — A file to read with information about the snapshots to be imported
- L43 _public property_ `public string SnapshotDescriptorJSON { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — A JSON blob with information about the snapshots to be imported
- L50 _public property_ `public string OverridePlatformCookedDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Where to look for the ue.projectstore file. The pattern {Platform} can be used for importing multiple platforms at once.
- L56 _public property_ `public bool ForceImport { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. If true, force import of the oplog (corresponds to --force on the Zen command line).
- L62 _public property_ `public bool AsyncImport { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. If true, import oplogs asynchronously (corresponds to --async on the Zen command line).
- L68 _public property_ `public string RemoteZenHost { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Remote zenserver host to import snapshots into.
- L74 _public property_ `public int RemoteZenPort { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Port on remote host which zenserver is listening on.
- L80 _public property_ `public string DestinationProjectId { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — Optional. Destination project ID to import snapshots into.

#### class `AutomationTool.Tasks.ZenImportSnapshotTask`  
`public class ZenImportSnapshotTask : BgTaskImpl`  
_public; L87-509_
- attrs: `[TaskElement("ZenImportSnapshot", typeof(ZenImportSnapshotTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Imports a snapshot from a specified destination to Zen.
- L197 _private* field_ `readonly ZenImportSnapshotTaskParameters _parameters` — Parameters for the task
- L203-206 _public ctor_ `public ZenImportSnapshotTask(ZenImportSnapshotTaskParameters parameters)` — Constructor.
- L211-214 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L220-223 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L229-232 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task
- L234-248 _private method_ `private static void RunAndLogWithoutSpew(string app, string commandLine)`
- L250-253 _private method_ `private static FileReference ZenExeFileReference()`
- L255-263 _private method_ `private static void ZenLaunch(FileReference projectFile)`
- L270-279 _private method_ `private static JsonSerializerOptions GetDefaultJsonSerializerOptions()`
- L281-324 _private method_ `private static SnapshotDescriptorCollection GetDescriptors(ZenImportSnapshotTaskParameters parameters)`
- L326-368 _private method_ `private FileReference WriteProjectStoreFile(string projectId, string platform, string host, int port)`
- L371-382 _private method_ `private string GetProjectID()` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA5351", Justification = "Not using MD5 for cryptographically secure use case")]`
- L384-405 _private method_ `private static string GetHostNameFQDN()`
- L407-413 _private method_ `private static string[] GetHostAddresses()`
- L421-508 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.

#### enum `AutomationTool.Tasks.ZenImportSnapshotTask.SnapshotStorageType`  
`public enum SnapshotStorageType`  
_public; L92-114_
- desc: Enumeration of different storage options for snapshots.
- L97 _public* enumerator_ `Invalid` — A reserved non-valid storage type for snapshots.
- L101 _public* enumerator_ `Cloud` — Snapshot stored in cloud repositories such as Unreal Cloud DDC.
- L105 _public* enumerator_ `Zen` — Snapshot stored in a zenserver.
- L109 _public* enumerator_ `File` — Snapshot stored as a file on disk.
- L113 _public* enumerator_ `Builds` — Snapshot stored in Unreal Cloud builds API.

#### class `AutomationTool.Tasks.ZenImportSnapshotTask.SnapshotDescriptor`  
`class SnapshotDescriptor`  
_private*; L119-181_
- desc: Metadata about a snapshot
- L124 _public property_ `public string Name { get; set; }` — Name of the snapshot
- L129 _public property_ `public SnapshotStorageType Type { get; set; }` — Storage type used for the snapshot
- L134 _public property_ `public string TargetPlatform { get; set; }` — Target platform for this snapshot
- L139 _public property_ `public string Host { get; set; }` — For cloud or Zen snapshots, the host they are stored on.
- L144 _public property_ `public string ProjectId { get; set; }` — For Zen snapshots, the project ID to import from.
- L149 _public property_ `public string OplogId { get; set; }` — For Zen snapshots, the oplog ID to import from.
- L154 _public property_ `public string Namespace { get; set; }` — For cloud snapshots, the namespace they are stored in.
- L159 _public property_ `public string Bucket { get; set; }` — For cloud snapshots, the bucket they are stored in.
- L164 _public property_ `public string Key { get; set; }` — For cloud snapshots, the key they are stored in.
- L170 _public property_ `public string BuildsId { get; set; }` — attrs: `[JsonPropertyName("builds-id")]` — For builds snapshots, the builds ID that identifies them.
- L175 _public property_ `public string Directory { get; set; }` — For file snapshots, the directory it is stored in.
- L180 _public property_ `public string Filename { get; set; }` — For file snapshots, the filename (not including path) that they are stored in.

#### class `AutomationTool.Tasks.ZenImportSnapshotTask.SnapshotDescriptorCollection`  
`class SnapshotDescriptorCollection`  
_private*; L186-192_
- desc: A collection of one or more snapshot descriptors
- L191 _public property_ `public List<SnapshotDescriptor> Snapshots { get; set; }` — The list of snapshots contained within this collection.

#### class `AutomationTool.Tasks.ZenImportSnapshotTask.LowerCaseNamingPolicy`  
`private class LowerCaseNamingPolicy : JsonNamingPolicy`  
_private; L265-268_
- inherits: `JsonNamingPolicy`
- L267 _public method_ `public override string ConvertName(string name)`

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ZenLaunchTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ZenLaunchTaskParameters`  
`public class ZenLaunchTaskParameters`  
_public; L16-23_
- desc: Parameters for a task that launches ZenServer
- L22 _public property_ `public FileReference Project { get; set; }` — attrs: `[TaskParameter]` — The project for which to launch ZenServer

#### class `AutomationTool.Tasks.ZenLaunchTask`  
`public class ZenLaunchTask : BgTaskImpl`  
_public; L29-101_
- attrs: `[TaskElement("ZenLaunch", typeof(ZenLaunchTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Launches ZenServer
- L38-47 _public method_ `public static void ZenLaunch(FileReference projectFile)` — Ensures that ZenServer is running on this current machine. This is needed before running any oplog commands This passes the sponsor'd process Id to launch zen. This ensures that zen does not live longer than the lifetime of a particular a process that needs Zen to be running
- L52 _private* field_ `readonly ZenLaunchTaskParameters _parameters` — Parameters for the task
- L58-61 _public ctor_ `public ZenLaunchTask(ZenLaunchTaskParameters parameters)` — Constructor.
- L69-74 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L79-82 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L88-91 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L97-100 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ZenMirrorTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ZenMirrorTaskParameters`  
`public class ZenMirrorTaskParameters`  
_public; L17-37_
- desc: Parameters for a task that calls zen mirror to write the Zen oplog onto disk
- L23 _public property_ `public FileReference Project { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The project from which to export the snapshot
- L29 _public property_ `public string Platform { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The target platform to mirror the snapshot for
- L36 _public property_ `public DirectoryReference DestinationFileDir { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — The path on the local disk to which the data will be mirrored If empty then the path will be set to the %Project%\Saved\Cooked\%Platform% directory.

#### class `AutomationTool.Tasks.ZenMirrorTask`  
`public class ZenMirrorTask : BgTaskImpl`  
_public; L43-204_
- attrs: `[TaskElement("ZenMirror", typeof(ZenMirrorTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Exports an snapshot from Zen to a specified destination.
- L48 _private* field_ `readonly ZenMirrorTaskParameters _parameters` — Parameters for the task
- L54-57 _public ctor_ `public ZenMirrorTask(ZenMirrorTaskParameters parameters)` — Constructor.
- L63-68 _public method_ `public static FileReference ZenExeFileReference()` — Gets the assumed path to where Zen should exist
- L76-89 _public method_ `public static void ZenLaunch(FileReference projectFile)` — Ensures that ZenServer is running on this current machine. This is needed before running any oplog commands This passes the sponsor'd process Id to launch zen. This ensures that zen does not live longer than the lifetime of the a process that needs Zen.
- L91-111 _private method_ `private static bool TryRunAndLogWithoutSpew(string app, string commandLine, bool ignoreFailure)`
- L113-128 _private method_ `private static bool TryRunMirrorCommand(string app, string commandLine)`
- L136-177 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L182-185 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L191-194 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L200-203 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/Tasks/ZipTask.cs` (BuildGraph.Automation)


#### class `AutomationTool.Tasks.ZipTaskParameters`  
`public class ZipTaskParameters`  
_public; L15-52_
- desc: Parameters for a zip task
- L21 _public property_ `public DirectoryReference FromDir { get; set; }` — attrs: `[TaskParameter]` — The directory to read compressed files from.
- L27 _public property_ `public string Files { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — List of file specifications separated by semicolons (for example, *.cpp;Engine/.../*.bat), or the name of a tag set. Relative paths are taken from FromDir.
- L33 _public property_ `public string ExecutableFiles { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.FileSpec)]` — List of files that should have an executable bit set.
- L39 _public property_ `public FileReference ZipFile { get; set; }` — attrs: `[TaskParameter]` — The zip file to create.
- L45 _public property_ `public bool SkipDefaultTag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.Default)]` — Skips adding the resulting zip to the default tagset.
- L51 _public property_ `public string Tag { get; set; }` — attrs: `[TaskParameter(Optional = true, ValidationType = TaskParameterValidationType.TagList)]` — Tag to be applied to the created zip file.

#### class `AutomationTool.Tasks.ZipTask`  
`public class ZipTask : BgTaskImpl`  
_public; L58-147_
- attrs: `[TaskElement("Zip", typeof(ZipTaskParameters))]`
- inherits: `BgTaskImpl`
- desc: Compresses files into a zip archive.
- L63 _private* field_ `readonly ZipTaskParameters _parameters` — Parameters for this task
- L69-72 _public ctor_ `public ZipTask(ZipTaskParameters parameters)` — Constructor
- L80-120 _public method_ `public override Task ExecuteAsync(JobContext job, HashSet<FileReference> buildProducts, Dictionary<string, HashSet<FileReference>> tagNameToFileSet)` — ExecuteAsync the task.
- L125-128 _public method_ `public override void Write(XmlWriter writer)` — Output this task out to an XML writer.
- L134-137 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L143-146 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

### `Source/Programs/AutomationTool/BuildGraph/TempStorage.cs` (BuildGraph.Automation)


#### class `AutomationTool.TempStorageBlockRef`  
`public class TempStorageBlockRef`  
_public; L30-92_
- desc: Stores the name of a temp storage block
- L36 _public property_ `public string NodeName { get; set; }` — attrs: `[XmlAttribute]` — Name of the node
- L42 _public property_ `public string OutputName { get; set; }` — attrs: `[XmlAttribute]` — Name of the output from this node
- L47-51 _private ctor_ `private TempStorageBlockRef()` — Default constructor, for XML serialization.
- L58-62 _public ctor_ `public TempStorageBlockRef(string nodeName, string outputName)` — Construct a temp storage block
- L69-73 _public method_ `public override bool Equals(object? other)` — Tests whether two temp storage blocks are equal
- L79-82 _public method_ `public override int GetHashCode()` — Returns a hash code for this block name
- L88-91 _public method_ `public override string ToString()` — Returns the name of this block for debugging purposes

#### class `AutomationTool.TempStorageFile`  
`public class TempStorageFile`  
_public; L98-294_
- attrs: `[DebuggerDisplay("{RelativePath}")]`
- desc: Information about a single file in temp storage
- L104 _public property_ `public string RelativePath { get; set; }` — attrs: `[XmlAttribute]` — The path of the file, relative to the engine root. Stored using forward slashes.
- L110 _public property_ `public long LastWriteTimeUtcTicks { get; set; }` — attrs: `[XmlAttribute]` — The last modified time of the file, in UTC ticks since the Epoch.
- L116 _public property_ `public long Length { get; set; }` — attrs: `[XmlAttribute]` — Length of the file
- L122 _public property_ `public string? Digest { get; set; }` — attrs: `[XmlAttribute]` — Digest for the file. Not all files are hashed.
- L127-130 _private ctor_ `private TempStorageFile()` — Default constructor, for XML serialization.
- L137-158 _public ctor_ `public TempStorageFile(FileInfo fileInfo, DirectoryReference rootDir)` — Constructor
- L165-184 _public method_ `public bool Compare(DirectoryReference rootDir)` — Compare stored for this file with the one on disk, and output an error if they differ.
- L192-256 _public method_ `public bool Compare(DirectoryReference rootDir, [NotNullWhen(false)] out string? message)` — Compare stored for this file with the one on disk, and output an error if they differ.
- L262-265 _private* method_ `bool RequireMatchingTimestamps()` — Whether we should compare timestamps for this file. Some build products are harmlessly overwritten as part of the build process, so we flag those here.
- L271-274 _private* method_ `bool GenerateDigest()` — Determines whether to generate a digest for the current file
- L280-283 _public method_ `public bool ShouldSerializeDigest()` — Determine whether to serialize the digest property
- L290-293 _public method_ `public FileReference ToFileReference(DirectoryReference rootDir)` — Gets a local file reference for this file, given a root directory to base it from.

#### class `AutomationTool.TempStorageZipFile`  
`public class TempStorageZipFile`  
_public; L300-331_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Information about a single file in temp storage
- L306 _public property_ `public string Name { get; set; }` — attrs: `[XmlAttribute]` — Name of this file, including extension
- L312 _public property_ `public long Length { get; set; }` — attrs: `[XmlAttribute]` — Length of the file in bytes
- L317-320 _private ctor_ `private TempStorageZipFile()` — Default constructor, for XML serialization
- L326-330 _public ctor_ `public TempStorageZipFile(FileInfo info)` — Constructor

#### class `AutomationTool.TempStorageBlockManifest`  
`public class TempStorageBlockManifest`  
_public; L337-419_
- attrs: `[XmlRoot(ElementName = "TempStorageManifest")]`
- desc: A manifest storing information about build products for a node's output
- L344 _public property_ `public TempStorageFile[] Files { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("File")]` — List of output files
- L351 _public property_ `public TempStorageZipFile[] ZipFiles { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("ZipFile")]` — List of compressed archives containing the given files
- L356 _private* field_ `static readonly XmlSerializer s_serializer = XmlSerializer.FromTypes(new Type[] { typeof(TempStorageBlockManifest) })[0]!` — Construct a static Xml serializer to avoid throwing an exception searching for the reflection info at runtime
- L361-365 _private ctor_ `private TempStorageBlockManifest()` — Construct an empty temp storage manifest
- L372-376 _public ctor_ `public TempStorageBlockManifest(FileInfo[] files, DirectoryReference rootDir)` — Creates a manifest from a flat list of files (in many folders) and a BaseFolder from which they are rooted.
- L382-390 _public method_ `public long GetTotalSize()` — Gets the total size of the files stored in this manifest
- L396-402 _public method_ `public static TempStorageBlockManifest Load(FileReference file)` — Load a manifest from disk
- L408-418 _public method_ `public void Save(FileReference file)` — Saves a manifest to disk

#### class `AutomationTool.TempStorageTagManifest`  
`public class TempStorageTagManifest`  
_public; L425-540_
- attrs: `[XmlRoot(ElementName = "TempStorageFileList")]`
- desc: Stores the contents of a tagged file set
- L432 _public property_ `public string[] LocalFiles { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("LocalFile")]` — List of files that are in this tag set, relative to the root directory
- L439 _public property_ `public string[] ExternalFiles { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("LocalFile")]` — List of files that are in this tag set, but not relative to the root directory
- L446 _public property_ `public TempStorageBlockRef[] Blocks { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("Block")]` — List of referenced storage blocks
- L453 _public property_ `public string[] ArtifactKeys { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("ArtifactKey")]` — List of keys for published artifacts
- L458 _private* field_ `static readonly XmlSerializer s_serializer = XmlSerializer.FromTypes(new Type[] { typeof(TempStorageTagManifest) })[0]!` — Construct a static Xml serializer to avoid throwing an exception searching for the reflection info at runtime
- L463-469 _private ctor_ `private TempStorageTagManifest()` — Construct an empty file list for deserialization
- L478-498 _public ctor_ `public TempStorageTagManifest(IEnumerable<FileReference> files, DirectoryReference rootDir, IEnumerable<TempStorageBlockRef> blocks, IEnumerable<string> artifactKeys)` — Creates a manifest from a flat list of files (in many folders) and a BaseFolder from which they are rooted.
- L504-510 _public method_ `public static TempStorageTagManifest Load(FileReference file)` — Load this list of files from disk
- L516-526 _public method_ `public void Save(FileReference file)` — Saves this list of files to disk
- L533-539 _public method_ `public HashSet<FileReference> ToFileSet(DirectoryReference rootDir)` — Converts this file list into a set of FileReference objects

#### class `AutomationTool.TempStorage`  
`class TempStorage`  
_internal*; L552-1458_
- desc: Tracks the state of the current build job using the filesystem, allowing jobs to be restarted after a failure or expanded to include larger targets, and providing a proxy for different machines executing parts of the build in parallel to transfer build products and share state as part of a build system. If a shared temp storage directory is provided - typically a mounted path on a network share - all build products potentially needed as inputs by another node are compressed and copied over, along with metadata for them (see TempStorageFile) and flags for build events that have occurred (see TempStorageEvent). The local temp storage directory contains the same information, with the exception of the archived build products. Metadata is still kept to detect modified build products between runs. If data is not present in local temp storage, it's retrieved from shared temp storage and cached in local storage.
- L557 _private* field_ `readonly DirectoryReference _rootDir` — Root directory for this branch.
- L562 _private* field_ `readonly DirectoryReference _localDir` — The local temp storage directory (typically somewhere under /Engine/Saved directory).
- L567 _private* field_ `readonly DirectoryReference? _sharedDir` — The shared temp storage directory; typically a network location. May be null.
- L572 _private* field_ `readonly bool _writeToSharedStorage` — Whether to allow writes to shared storage
- L581-587 _public ctor_ `public TempStorage(DirectoryReference rootDir, DirectoryReference localDir, DirectoryReference? sharedDir, bool writeToSharedStorage)` — Constructor
- L592-595 _public method_ `public void CleanLocal()` — Cleans all cached local state. We never remove shared storage.
- L601-609 _public method_ `public void CleanLocalNode(string nodeName)` — Cleans local build products for a given node. Does not modify shared storage.
- L616-637 _public method_ `public bool IsComplete(string nodeName)` — Check whether the given node is complete
- L643-657 _public method_ `public void MarkAsComplete(string nodeName)` — Mark the given node as complete
- L666-749 _public method_ `public bool CheckLocalIntegrity(string nodeName, IEnumerable<string> tagNames, FileFilter ignoreModified)` — Checks the integrity of the give node's local build products.
- L757-809 _public method_ `public TempStorageTagManifest? ReadTagFileList(string nodeName, string tagName)` — Reads a set of tagged files from disk
- L820-853 _public method_ `public void WriteFileList(string nodeName, string tagName, IEnumerable<FileReference> files, IEnumerable<TempStorageBlockRef> blocks, IEnumerable<string> artifactKeys)` — Writes a list of tagged files to disk
- L863-906 _public method_ `public TempStorageBlockManifest Archive(string nodeName, string? blockName, FileReference[] buildProducts, bool pushToRemote = true)` — Saves the given files (that should be rooted at the branch root) to a shared temp storage manifest with the given temp storage node and game.
- L915-1008 _public method_ `public TempStorageBlockManifest Retrieve(string nodeName, string? outputName, FileFilter ignoreModified)` — Retrieve an output of the given node. Fetches and decompresses the files from shared storage if necessary, or validates the local files.
- L1010-1029 _private* method_ `static void PerformActionWithRetries(Action retryAction, int retryCount, TimeSpan waitTime)`
- L1044-1131 _private* method_ `static FileInfo[] ParallelZipFiles(FileInfo[] inputFiles, DirectoryReference rootDir, DirectoryReference outputDir, DirectoryReference stagingDir, string zipBaseName)` — Zips a set of files (that must be rooted at the given RootDir) to a set of zip files in the given OutputDir. The files will be prefixed with the given basename.
- L1142-1244 _private method_ `private static string ParallelUnzipFiles(FileInfo[] zipFiles, DirectoryReference rootDir)` — Unzips a set of zip files with a given basename in a given folder to a given RootDir.
- L1252-1255 _private* method_ `static DirectoryReference GetDirectoryForNode(DirectoryReference baseDir, string nodeName)` — Gets the directory used to store data for the given node
- L1263-1266 _private* method_ `static FileReference GetManifestLocation(DirectoryReference baseDir, string nodeName, string? blockName)` — Gets the path to the manifest created for a node's output.
- L1274-1278 _private* method_ `static FileReference GetTaggedFileListLocation(DirectoryReference baseDir, string nodeName, string tagName)` — Gets the path to the file created to store a tag manifest for a node
- L1285-1288 _private* method_ `static FileReference GetCompleteMarkerFile(DirectoryReference baseDir, string nodeName)` — Gets the path to a file created to indicate that a node is complete, under the given base directory.
- L1296-1342 _public method_ `public static bool IsDuplicateBuildProduct(FileReference localFile)` — Checks whether the given path is allowed as a build product that can be produced by more than one node (timestamps may be modified, etc..). Used to suppress warnings about build products being overwritten.
- L1351-1368 _private* method_ `static string CopyFile(FileInfo zipFile, DirectoryReference rootDir)` — Copy a temp storage .zip file to directory. Uses Robocopy on Windows, rsync on Linux/macOS and native .NET API when under Wine.
- L1377-1387 _private* method_ `static string CopyDirectory(DirectoryReference sourceDir, DirectoryReference destinationDir)` — Copy a directory using the most suitable option
- L1397-1407 _private* method_ `static string CopyDirectoryExternalTool(DirectoryReference sourceDir, DirectoryReference destinationDir)` — Copy a directory using an external tool native to OS Robocopy Windows and rsync for Linux and macOS.
- L1416-1441 _private* method_ `static string CopyDirectoryDotNet(DirectoryReference sourceDir, DirectoryReference destinationDir)` — Copy a directory using .NET SDK directory and file copy API
- L1443-1457 _private* method_ `static string GetRoboCopyExe()`

#### class `AutomationTool.TempStorageTests`  
`class TempStorageTests : BuildCommand`  
_internal*; L1463-1590_
- inherits: `BuildCommand`
- desc: Automated tests for temp storage
- L1468-1534 _public method_ `public override void ExecuteBuild()` — Run the automated tests
- L1543-1555 _private* method_ `static Dictionary<FileReference, DateTime> SelectFiles(DirectoryReference sourceDir, char charRangeBegin, char charRangeEnd)` — Enumerate all the files beginning with a letter within a certain range
- L1563-1589 _private* method_ `static void CheckManifest(DirectoryReference rootDir, TempStorageBlockManifest manifest, Dictionary<FileReference, DateTime> files)` — Checks that a manifest matches the files on disk

#### class `AutomationTool.CleanTempStorage`  
`class CleanTempStorage : BuildCommand`  
_internal*; L1597-1721_
- attrs: `[Help("Removes folders in a given temp storage directory that are older than a certain time.")] [Help("TempStorageDir=<Directory>", "Path to the root temp storage directory")] [Help("Days=<N>", "Number of days to keep in temp storage")]`
- inherits: `BuildCommand`
- desc: Commandlet to clean up all folders under a temp storage root that are older than a given number of days
- L1602-1720 _public method_ `public override void ExecuteBuild()` — Entry point for the commandlet
