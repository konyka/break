# CSharp / EpicGames.UHT

- project root: `Source/Programs/Shared/EpicGames.UHT`
- files: 140; symbols: 4423
- symbol kinds: class=241, const=122, ctor=243, delegate=25, enum=60, enumerator=377, field=320, interface=15, method=1968, operator=1, property=989, record=2, record struct=9, struct=51
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/EditorDataStorageUhtExtension.cs` (EpicGames.UHT)


#### class `EditorDataStorageUhtExtension.Extension`  
`sealed class Extension`  
_internal*; L11-25_
- attrs: `[UnrealHeaderTool]`
- L13 _private const_ `private const string DynamicTemplateMetadata = "EditorDataStorage_DynamicColumnTemplate"`
- L18-24 _public method_ `public static void InjectDynamicColumnTemplateStaticAttribute(StringBuilder builder, UhtType uhtType, int leadingTabs, string eolSequence)` — attrs: `[UhtCodeGeneratorInjector( UhtType = typeof(UhtScriptStruct), Location = UhtCodeGeneratorInjectionLocation.GeneratedMacro)]`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtCodeBlockComment.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Exporters.CodeGen.UhtCodeBlockComment`  
`internal readonly struct UhtCodeBlockComment : IDisposable`  
_internal; L9-79_
- inherits: `IDisposable`
- L11 _private const_ `private const string HighlightPrefix = "**********"`
- L12 _private const_ `private const char HighlightChar = '*'`
- L13 _private const_ `private const int HighlightLength = 100`
- L14 _private field_ `private readonly StringBuilder _builder`
- L15 _private field_ `private readonly UhtType? _primaryType = null`
- L16 _private field_ `private readonly UhtType? _secondaryType = null`
- L17 _private field_ `private readonly string? _text = null`
- L19-24 _public ctor_ `public UhtCodeBlockComment(StringBuilder builder, string text)`
- L26-32 _public ctor_ `public UhtCodeBlockComment(StringBuilder builder, UhtType primaryType, string? text = null)`
- L34-41 _public ctor_ `public UhtCodeBlockComment(StringBuilder builder, UhtType primaryType, UhtType secondaryType, string? text = null)`
- L43-46 _public method_ `public void Dispose()`
- L48-52 _private method_ `private void Begin()`
- L54-78 _private method_ `private void AppendText(string startOrEnd)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtCodeGenExpressions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtExpressionFactory`  
`internal static class UhtExpressionFactory`  
_internal; L14-32_
- desc: Utility functions to construct structs which can be used in interpolated strings. It is recommended to import this type into a namespace with 'using static' so its methods can be used without the type name prefix for brevity.
- L16 _private* field_ `static readonly ReadOnlyMemory<char> s_tabs = String.Empty.PadLeft(100, '\t').AsMemory()`
- L18 _internal method_ `internal static TabsExpression Tabs(int count)`
- L20 _internal method_ `internal static SingletonRefExpression SingletonRef(IUhtObjectLinker provider, UhtObject? obj, UhtSingletonType type)`
- L23 _internal method_ `internal static SingletonRefExpression ConstInitSingletonRef(IUhtObjectLinker provider, UhtObject? obj, bool explicitType = false)`
- L26 _internal method_ `internal static UhtCppIdentifier VniModuleStatics(UhtModule module)`
- L30 _internal method_ `internal static UhtCppIdentifier VniPackageDesc(UhtModule module)`

#### record struct `EpicGames.UHT.Exporters.CodeGen.TabsExpression`  
`internal readonly record struct TabsExpression(int Count, ReadOnlyMemory<char> Tabs) : ISpanFormattable`  
_internal; L35-58_
- inherits: `ISpanFormattable`
- L37 _public method_ `public string ToString(string? format, IFormatProvider? formatProvider)`
- L39-57 _public method_ `public bool TryFormat(Span<char> destination, out int charsWritten, ReadOnlySpan<char> format, IFormatProvider? provider)`

#### record struct `EpicGames.UHT.Exporters.CodeGen.SimpleExpression`  
`internal readonly record struct SimpleExpression(string? Prefix, string Unique, string? Suffix = null) : ISpanFormattable`  
_internal; L67-73_
- inherits: `ISpanFormattable`
- desc: Utility class for simple expressions such as variable names derived from a type name. Intended to be used as a return type from factory methods with a more explicit name, e.g. ModuleLinkableObjects
- L69 _public method_ `public string ToString(string? format, IFormatProvider? formatProvider)`
- L71 _public method_ `public bool TryFormat(Span<char> destination, out int charsWritten, ReadOnlySpan<char> format, IFormatProvider? provider)`

#### record struct `EpicGames.UHT.Exporters.CodeGen.SingletonRefExpression`  
`internal readonly record struct SingletonRefExpression(IUhtObjectLinker Provider, UhtObject? Obj, UhtSingletonType Type, bool Explicit) : ISpanFormattable`  
_internal; L75-87_
- inherits: `ISpanFormattable`
- L77 _public method_ `public string ToString(string? format, IFormatProvider? formatProvider)`
- L79 _public method_ `public bool TryFormat(Span<char> destination, out int charsWritten, ReadOnlySpan<char> format, IFormatProvider? provider)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtCodeGenerator.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Exporters.CodeGen.UhtSingletonType`  
`public enum UhtSingletonType`  
_public; L18-39_
- desc: Type of singleton to retrieve a name or declaration for
- L23 _public* enumerator_ `Registered = 0` — Function that returns a fully constructed object - the distinction between this and Unregistered is only important for classes.
- L28 _public* enumerator_ `Unregistered = 1` — Function that returns a partially constructed object
- L33 _public* enumerator_ `ConstInit = 2` — Constinit variable (C++20 feature)
- L38 _public* enumerator_ `Statics = 3` — Struct containing initialization data for the object

#### enum `EpicGames.UHT.Exporters.CodeGen.UhtSingletonTypeFlag`  
`public enum UhtSingletonTypeFlag`  
_public; L45-67_
- attrs: `[Flags]`
- desc: Mirror of UhtSingletonType as flags for storing sets of singleton types
- L50 _public* enumerator_ `None = 0` — Flag matching nothing
- L54 _public* enumerator_ `Registered = 1 << UhtSingletonType.Registered` — Flag for UhtSingletonType.Registered
- L58 _public* enumerator_ `Unregistered = 1 << UhtSingletonType.Unregistered` — Flag for UhtSingletonType.Unregistered
- L62 _public* enumerator_ `ConstInit = 1 << UhtSingletonType.ConstInit` — Flag for UhtSingletonType.ConstInit
- L66 _public* enumerator_ `Statics = 1 << UhtSingletonType.Statics` — Flag for UhtSingletonType.Statics

#### interface `EpicGames.UHT.Exporters.CodeGen.IUhtSingletonNameProvider`  
`public interface IUhtSingletonNameProvider`  
_public; L72-81_
- desc: Interface to provide singleton names during code generation.
- L80 _public method_ `public string GetSingletonName(UhtObject? obj, UhtSingletonType type)` — Return the singleton name for the given object

#### interface `EpicGames.UHT.Exporters.CodeGen.IUhtObjectLinker`  
`public interface IUhtObjectLinker : IUhtSingletonNameProvider`  
_public; L87-109_
- inherits: `IUhtSingletonNameProvider`
- desc: Interface to link objects together in generated code by initialization expressions such as address-of or initializing encoded pointers for runtime linking
- L94 _public method_ `public bool IsCrossModuleRef(UhtObject obj)` — Used by code generation to determine how a reference should be linked, i.e. by direct pointer or by encoded pointe requiring runtime fixup.
- L101 _public method_ `public int GetModuleIndex(UhtModule obj)`
- L108 _public method_ `public int GetObjectIndex(UhtObject obj)`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtCodeGenerator`  
`sealed class UhtCodeGenerator : IUhtSingletonNameProvider`  
_internal*; L112-578_
- attrs: `[UnrealHeaderTool]`
- inherits: `IUhtSingletonNameProvider`
- L117-121 _public method_ `public static void CodeGenerator(IUhtExportFactory factory)` — attrs: `[UhtExporter(Name = "CodeGen", Description = "Standard UnrealEngine code generation", Options = UhtExporterOptions.Default, CppFilters = new string[] { "*.generated.cpp", "*.generated.*.cpp", "*.gen.cpp", "*.gen.*.cpp" }, HeaderFilters = ne`
- L127 _public property_ `public PackageInfo[] PackageInfos { get; set; }`
- L145 _public property_ `public HeaderInfo[] HeaderInfos { get; set; }`
- L167 _public property_ `public ObjectInfo[] ObjectInfos { get; set; }`
- L169 _public field_ `public readonly IUhtExportFactory Factory`
- L170 _public property_ `public UhtSession Session => ...`
- L171 _public property_ `public UhtScriptStruct? FastArraySerializer { get; set; }`
- L173-179 _private ctor_ `private UhtCodeGenerator(IUhtExportFactory factory)`
- L181-266 _private method_ `private void Generate()`
- L275-292 _public method_ `public string GetSingletonName(UhtObject? obj, UhtSingletonType type)` — Return the singleton name for an object
- L300-303 _public method_ `public string GetExternalDecl(UhtObject obj, UhtSingletonType type)` — Return the external declaration for an object
- L311-324 _public method_ `public string GetExternalDecl(int objectIndex, UhtSingletonType type)` — Return the external declaration for an object
- L328-340 _private method_ `private void InitModuleInfo(UhtModule module)`
- L342-357 _private method_ `private void InitPackageInfo(StringBuilder builder, UhtPackage package)`
- L359-419 _private method_ `private void InitHeaderInfo(StringBuilder builder, UhtHeaderFile headerFile)`
- L421-512 _private method_ `private void InitObjectInfo(StringBuilder builder, UhtPackage package, ref HeaderInfo headerInfo, UhtObject obj)`
- L519-555 _private* method_ `static void InitVerseInfo(ref HeaderInfo headerInfo, UhtStruct structObj)` — Given a structure (class or script struct), initialize the header info based on the existence of verse elements
- L564-576 _private method_ `private static List<UhtHeaderFile> GetSortedHeaderFiles(UhtModule module)` — Return a module's sorted header file list of all header files that or referenced or have declarations.

#### struct `EpicGames.UHT.Exporters.CodeGen.UhtCodeGenerator.PackageInfo`  
`public struct PackageInfo`  
_public; L123-126_
- L125 _public property_ `public string StrippedName { get; set; }`

#### struct `EpicGames.UHT.Exporters.CodeGen.UhtCodeGenerator.HeaderInfo`  
`public struct HeaderInfo`  
_public; L129-144_
- L131 _public property_ `public Task? Task { get; set; }`
- L132 _public property_ `public string IncludePath { get; set; }`
- L133 _public property_ `public string FileId { get; set; }`
- L134 _public property_ `public IoHash BodyHash { get; set; }`
- L135 _public property_ `public bool NeedsPushModelHeaders { get; set; }`
- L136 _public property_ `public bool NeedsFastArrayHeaders { get; set; }`
- L137 _public property_ `public bool NeedsVerseValue { get; set; }`
- L138 _public property_ `public bool NeedsVerseString { get; set; }`
- L139 _public property_ `public bool NeedsVerseCodeGen { get; set; }`
- L140 _public property_ `public bool NeedsVerseField { get; set; }`
- L141 _public property_ `public bool NeedsVersePointer { get; set; }`
- L142 _public property_ `public bool NeedsVerseTask { get; set; }`
- L143 _public property_ `public bool NeedsVerseCoroutine { get; set; }`

#### struct `EpicGames.UHT.Exporters.CodeGen.UhtCodeGenerator.ObjectInfo`  
`public struct ObjectInfo`  
_public; L147-166_
- L150 _public property_ `public string RegisteredSingletonName { get; set; }`
- L152 _public property_ `public string RegisteredExternalDecl { get; set; }`
- L155 _public property_ `public string ConstInitSingletonName { get; set; }`
- L159 _public property_ `public string ConstInitExternalDecl { get; set; }`
- L162 _public property_ `public string StaticsName { get; set; }`
- L163 _public property_ `public UhtClass? NativeInterface { get; set; }`
- L164 _public property_ `public UhtProperty? FastArrayProperty { get; set; }`
- L165 _public property_ `public IoHash Hash { get; set; }`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtCodeGeneratorExtensions`  
`static class UhtCodeGeneratorExtensions`  
_internal*; L580-589_
- L588 _public method_ `public static bool IsCrossModuleRef(this UhtObject obj, IUhtObjectLinker linker)` — Convenience function so allow use of ?. operator on objects to determine if they are cross-module references according to the given linker.

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtHeaderCodeGenerator.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtHeaderCodeGenerator`  
`class UhtHeaderCodeGenerator : UhtPackageCodeGenerator`  
_internal*; L13-667_
- inherits: `UhtPackageCodeGenerator`
- L16 _public const_ `public const string CallbackWrappersMacroSuffix = "CALLBACK_WRAPPERS"`
- L17 _public const_ `public const string SparseDataMacroSuffix = "SPARSE_DATA"`
- L18 _public const_ `public const string SparseDataPropertyAccessorsMacroSuffix = "SPARSE_DATA_PROPERTY_ACCESSORS"`
- L19 _public const_ `public const string RpcWrappersMacroSuffix = "RPC_WRAPPERS"`
- L20 _public const_ `public const string RpcWrappersNoPureDeclsMacroSuffix = "RPC_WRAPPERS_NO_PURE_DECLS"`
- L21 _public const_ `public const string VerseNativeCallableWrappersMacroSuffix = "VERSE_NATIVE_CALLABLE_WRAPPERS"`
- L22 _public const_ `public const string AccessorsMacroSuffix = "ACCESSORS"`
- L23 _public const_ `public const string ArchiveSerializerMacroSuffix = "ARCHIVESERIALIZER"`
- L24 _public const_ `public const string StandardConstructorsMacroSuffix = "STANDARD_CONSTRUCTORS"`
- L25 _public const_ `public const string EnchancedConstructorsMacroSuffix = "ENHANCED_CONSTRUCTORS"`
- L26 _public const_ `public const string GeneratedBodyMacroSuffix = "GENERATED_BODY"`
- L27 _public const_ `public const string GeneratedBodyLegacyMacroSuffix = "GENERATED_BODY_LEGACY"`
- L28 _public const_ `public const string GeneratedUInterfaceBodyMacroSuffix = "GENERATED_UINTERFACE_BODY()"`
- L29 _public const_ `public const string FieldNotifyMacroSuffix = "FIELDNOTIFY"`
- L30 _public const_ `public const string InClassMacroSuffix = "INCLASS"`
- L31 _public const_ `public const string InClassNoPureDeclsMacroSuffix = "INCLASS_NO_PURE_DECLS"`
- L32 _public const_ `public const string InClassIInterfaceMacroSuffix = "INCLASS_IINTERFACE"`
- L33 _public const_ `public const string InClassIInterfaceNoPureDeclsMacroSuffix = "INCLASS_IINTERFACE_NO_PURE_DECLS"`
- L34 _public const_ `public const string PrologMacroSuffix = "PROLOG"`
- L35 _public const_ `public const string AutoGettersSettersMacroSuffix = "AUTOGETTERSETTER_DECLS"`
- L36 _public const_ `public const string VInterfacesMacroSuffix = "VINTERFACES"`
- L39 _public field_ `public readonly UhtHeaderFile HeaderFile`
- L40 _public property_ `public string FileId => ...`
- L42-46 _public ctor_ `public UhtHeaderCodeGenerator(UhtCodeGenerator codeGenerator, UhtHeaderFile headerFile) : base(codeGenerator, headerFile.Module)`
- L49-114 _protected method_ `protected static StringBuilder AppendEventParameter(StringBuilder builder, UhtFunction function, string strippedFunctionName, UhtPropertyTextType textType, bool outputConstructor, int tabs, string endl)`
- L116-119 _protected method_ `protected static bool WillExportEventParameters(UhtFunction function)`
- L121-149 _protected method_ `protected static string GetEventStructParametersName(UhtType? outer, string functionName)`
- L153-298 _protected method_ `protected StringBuilder AppendNativeFunctionHeader(StringBuilder builder, UhtFunction function, UhtPropertyTextType textType, bool isDeclaration, string? alternateFunctionName, string? extraParam, UhtFunctionExportFlags extraExportFlags, int tabs, string endl)`
- L302-315 _protected method_ `protected static StringBuilder AppendFindUFunction(StringBuilder builder, UhtClass classObj, UhtFunction function, int tabs, string endl = "\r\n")`
- L317-364 _protected method_ `protected static StringBuilder AppendEventFunctionPrologue(StringBuilder builder, UhtFunction function, string functionName, int tabs, string endl, bool addEventParameterStruct, bool bAddFunctionScopeBracket = true)`
- L366-433 _protected method_ `protected static StringBuilder AppendEventFunctionEpilogue(StringBuilder builder, UhtFunction function, int tabs, string endl, bool bAddFunctionScopeBracket = true)`
- L435-465 _protected method_ `protected static StringBuilder AppendParameters(StringBuilder builder, UhtFunction function, UhtPropertyTextType textType, string? extraParameter, bool skipParameterName)`
- L467-472 _protected method_ `protected static bool IsRpcFunction(UhtFunction function)`
- L474-477 _protected method_ `protected static bool IsCallbackFunction(UhtFunction function)`
- L484-524 _protected method_ `protected static bool ShouldExportFunction(UhtFunction function)` — Determines whether the glue version of the specified native function should be exported.
- L542-583 _protected method_ `protected static ConstructorType GetConstructorType(UhtClass classObj)` — Return the type of constructor the class will have regardless of if one has been explicitly declared or will be generated.
- L591-607 _protected method_ `protected static IEnumerable<UhtScriptStruct> GetSparseDataStructsToExport(UhtClass classObj)` — A list of sparse data structs that should export accessors for this class. This list excludes anything that has already been exported by the super class.
- L611-616 _protected method_ `protected static bool NeedFieldNotifyCodeGen(UhtClass classObj)`
- L618-632 _protected method_ `protected static string GetNotifyTypeName(UhtType notifyType)`
- L634-655 _protected method_ `protected static UhtUsedDefineScopes<UhtType> GetFieldNotifyTypes(UhtClass classObj)`
- L659-665 _protected method_ `protected static UhtUsedDefineScopes<UhtProperty> GetAutoGetterSetterProperties(UhtClass classObj)`

#### enum `EpicGames.UHT.Exporters.CodeGen.UhtHeaderCodeGenerator.ConstructorType`  
`protected enum ConstructorType`  
_protected; L529-534_
- desc: Type of constructor on the class regardless of explicit or generated.
- L531 _public* enumerator_ `ObjectInitializer`
- L532 _public* enumerator_ `Default`
- L533 _public* enumerator_ `ForbiddenDefault`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtHaederCodeGeneratorStringBuilderExtensions`  
`internal static class UhtHaederCodeGeneratorStringBuilderExtensions`  
_internal; L669-914_
- L671-681 _public method_ `public static int GetMacroLineNumber(this UhtType type)`
- L683-695 _public method_ `public static string GetScopeSuffix(this UhtDefineScope definedScope)`
- L697-701 _public method_ `public static StringBuilder AppendMacroName(this StringBuilder builder, string fileId, int lineNumber, string macroSuffix)`
- L703-706 _public method_ `public static StringBuilder AppendMacroName(this StringBuilder builder, UhtHeaderCodeGenerator generator, int lineNumber, string macroSuffix)`
- L708-711 _public method_ `public static StringBuilder AppendMacroName(this StringBuilder builder, UhtHeaderCodeGenerator generator, UhtType type, string macroSuffix)`
- L723-731 _public method_ `public static StringBuilder AppendMacroName(this StringBuilder builder, string fileId, int lineNumber, string macroSuffix, UhtDefineScope defineScope, bool includeSuffix)` — Append the macro name including an optional suffix to uniquely identify a define scope
- L739-778 _public method_ `public static StringBuilder AppendVerseNativeCallableReturnType(this StringBuilder builder, UhtFunction function)` — Append just the overall return type of the native callable verse function
- L788-806 _public method_ `public static StringBuilder AppendVerseNativeCallableSignature(this StringBuilder builder, UhtClass? classObj, UhtFunction function, string classNameSuffix)` — Append the complete signature of the native callable verse function
- L808-838 _public method_ `public static StringBuilder AppendVerseNativeCallableTypeDef(this StringBuilder builder, UhtFunction function)`
- L840-913 _public method_ `public static StringBuilder AppendVerseFunctionArgs(this StringBuilder builder, UhtFunction function, bool startWithSeparator, bool decidesBeforeReturn, Action<UhtProperty> propertyAction, Action decidesAction)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtHeaderCodeGeneratorCppFile.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtRegistrations`  
`internal sealed class UhtRegistrations`  
_internal; L18-25_
- desc: Collection of all registrations for a specific package
- L20 _public property_ `public UhtUsedDefineScopes<UhtEnum> Enumerations { get; }`
- L21 _public property_ `public UhtUsedDefineScopes<UhtScriptStruct> ScriptStructs { get; }`
- L22 _public property_ `public UhtUsedDefineScopes<UhtScriptStruct> RigVMStructs { get; }`
- L23 _public property_ `public UhtUsedDefineScopes<UhtClass> Classes { get; }`
- L24 _public property_ `public UhtUsedDefineScopes<UhtPartial> Partials { get; }`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtHeaderCodeGeneratorCppFile`  
`internal sealed class UhtHeaderCodeGeneratorCppFile : UhtHeaderCodeGenerator`  
_internal; L27-3664_
- inherits: `UhtHeaderCodeGenerator`
- L34-37 _public ctor_ `public UhtHeaderCodeGeneratorCppFile(UhtCodeGenerator codeGenerator, UhtHeaderFile headerFile) : base(codeGenerator, headerFile)` — Construct an instance of this generator object
- L45-557 _public method_ `public void Generate(IUhtExportFactory factory)` — For a given UE header file, generated the generated H file
- L560-578 _private method_ `private void AddIncludeForType(UhtProperty uhtProperty, bool requireIncludeForClasses, HashSet<UhtHeaderFile> addedIncludes, IList<string> includesToAdd)`
- L580-593 _private method_ `private void AddIncludeForProperty(UhtProperty property, bool requireIncludeForClasses, HashSet<UhtHeaderFile> addedIncludes, IList<string> includesToAdd)`
- L595-620 _private method_ `private static string GetUEnumEnumUnderlyingType(UhtEnumUnderlyingType underlyingType)`
- L622-883 _private method_ `private StringBuilder AppendEnum(StringBuilder builder, UhtEnum enumObj)`
- L885-1338 _private method_ `private StringBuilder AppendScriptStruct(StringBuilder builder, UhtScriptStruct scriptStruct)`
- L1340-1484 _private method_ `private StringBuilder AppendPartial(StringBuilder builder, UhtPartial partial)`
- L1486-1705 _private method_ `private StringBuilder AppendFunction(StringBuilder builder, UhtFunction function, bool isNoExport, bool isVerseNativeCallable)`
- L1707-1725 _private method_ `private string GetFunctionOuterFunc(UhtFunction function)`
- L1727-1743 _private method_ `private static StringBuilder AppendMirrorsForNoexportStruct(StringBuilder builder, UhtScriptStruct noExportStruct, int tabs)`
- L1745-1756 _private method_ `private static StringBuilder AppendExportProperties(StringBuilder builder, UhtScriptStruct scriptStruct, int tabs)`
- L1758-1827 _private method_ `private StringBuilder AppendPropertiesDecl(StringBuilder builder, UhtPropertyMemberContextImpl context, UhtUsedDefineScopes<UhtProperty> properties, int tabs)`
- L1829-1919 _private method_ `private StringBuilder AppendPropertiesDefs(StringBuilder builder, UhtPropertyMemberContextImpl context, UhtUsedDefineScopes<UhtProperty> properties, int tabs)`
- L1921-1979 _private method_ `private StringBuilder AppendClassFunction(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L1981-1991 _private method_ `private static StringBuilder AppendNativeInterfaceVerseProxyFunctions(StringBuilder builder, UhtClass classObj, UhtClass? funcClassObj)`
- L1993-2000 _private method_ `private static StringBuilder AppendVerseNativeCallableProxyFunctions(StringBuilder builder, UhtClass classObj, UhtUsedDefineScopes<UhtFunction> verseNativeCallableFunctions)`
- L2002-2065 _private method_ `private static StringBuilder AppendVerseNativeCallableFunctionStub(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L2067-2094 _private method_ `private static StringBuilder AppendVerseNativeCallableFunction(StringBuilder builder, UhtClass classObj, UhtFunction function, string classNameSuffix)`
- L2096-2142 _private method_ `private static StringBuilder AppendVerseNativeCallableFunctionBody(StringBuilder builder, UhtClass classObj, UhtFunction function, UhtProperty? returnProperty, bool isVerseVM)`
- L2144-2179 _private method_ `private static StringBuilder AppendVerseCallableFunction(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L2181-2378 _private method_ `private static StringBuilder AppendVerseCallableFunctionBody(StringBuilder builder, UhtClass classObj, UhtFunction function, UhtProperty? returnProperty, bool isVerseVM)`
- L2380-2538 _private method_ `private StringBuilder AppendClassFunctionCallback(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L2540-2621 _private method_ `private StringBuilder AppendInterfaceCallFunction(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L2623-2672 _private method_ `private StringBuilder AppendClass(StringBuilder builder, UhtClass classObj, UhtUsedDefineScopes<UhtFunction> functions)`
- L2674-2700 _private method_ `private static StringBuilder AppendFieldNotify(StringBuilder builder, UhtClass classObj)`
- L2702-2730 _private method_ `private static StringBuilder AppendAutoGettersSetters(StringBuilder builder, UhtClass classObj)`
- L2732-2849 _private method_ `private static StringBuilder AppendPropertyAccessors(StringBuilder builder, UhtClass classObj)`
- L2851-2878 _private method_ `private static StringBuilder AppendSparseAccessors(StringBuilder builder, UhtClass classObj)`
- L2880-2888 _private method_ `private static StringBuilder AppendSerializer(StringBuilder builder, UhtClass classObj, UhtSerializerArchiveType serializerType, string macroText)`
- L2892-3447 _private method_ `private StringBuilder AppendNativeGeneratedInitCode(StringBuilder builder, UhtClass classObj, UhtUsedDefineScopes<UhtFunction> functions)`
- L3450-3481 _private method_ `private static StringBuilder AppendImplementedInterfaceParam(StringBuilder builder, UhtPropertyMemberContextImpl context, UhtClass classObj, UhtClass interfaceObj, UhtSingletonType singletonType)`
- L3483-3546 _private method_ `private static StringBuilder AppendFunctionThunk(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L3548-3562 _private method_ `private void AppendVniTypeDesc(StringBuilder builder, UhtField fieldObj)`
- L3564-3598 _private method_ `private static void FindNoExportStructsRecursive(List<UhtScriptStruct> outScriptStructs, UhtStruct structObj)`
- L3600-3606 _private method_ `private static List<UhtScriptStruct> FindNoExportStructs(UhtStruct structObj)`
- L3608-3618 _private method_ `private static UhtRegistrations GetRegistrations(Dictionary<UhtPackage, UhtRegistrations> packageRegistrations, UhtField fieldObj)`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtHeaderCodeGeneratorCppFile.UhtPropertyMemberContextImpl`  
`private sealed class UhtPropertyMemberContextImpl : IUhtPropertyMemberContext`  
_private; L3620-3663_
- inherits: `IUhtPropertyMemberContext`
- L3622 _private field_ `private readonly UhtHeaderCodeGenerator _codeGenerator`
- L3623 _private field_ `private readonly UhtStruct _outerStruct`
- L3624 _private field_ `private readonly UhtCppIdentifier _outerIdentifier`
- L3626-3631 _public ctor_ `public UhtPropertyMemberContextImpl(UhtHeaderCodeGenerator codeGenerator, UhtStruct outerStruct, string outerStructNamespaceName, string outerStructSourceName)`
- L3633-3640 _public ctor_ `public UhtPropertyMemberContextImpl(UhtHeaderCodeGenerator codeGenerator, UhtStruct outerStruct)`
- L3642 _public property_ `public UhtStruct OuterStruct => ...`
- L3644 _public property_ `public UhtCppIdentifier OuterIdentifier => ...`
- L3646 _public property_ `public bool IsLegacy { get; set; }`
- L3648-3651 _public method_ `public string GetSingletonName(UhtObject? obj, UhtSingletonType type)`
- L3653 _public method_ `public bool IsCrossModuleRef(UhtObject obj)`
- L3655 _public method_ `public int GetModuleIndex(UhtModule obj)`
- L3657 _public method_ `public int GetObjectIndex(UhtObject obj)`
- L3659-3662 _public method_ `public IoHash GetTypeHash(UhtObject obj)`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtHeaderCodeGeneratorCppFileStringBuilderExtensions`  
`public static class UhtHeaderCodeGeneratorCppFileStringBuilderExtensions`  
_public; L3669-3828_
- desc: Collection of string builder extensions used to generate the cpp files for individual headers.
- L3681-3708 _public method_ `public static StringBuilder AppendConstInitObjectParams(this StringBuilder builder, UhtObject uhtObject, IUhtObjectLinker linker, int tabs, string? additionalObjectFlags = null)` — Appends a structure initialization expression for a constant-initialized UObject, followed by a comma and newline for use in a larger aggregate initialization expression
- L3716-3745 _public method_ `public static StringBuilder AppendFunctionThunkParameterNames(this StringBuilder builder, UhtFunction function)` — Append the parameter names for a function
- L3753-3768 _public method_ `public static StringBuilder AppendFunctionParamsType(this StringBuilder builder, UhtFunction function)` — Append the name of the function params type
- L3776-3791 _public method_ `public static StringBuilder AppendFunctionConstructorName(this StringBuilder builder, UhtFunction function)` — Append the name of the function constructor
- L3799-3803 _public method_ `public static StringBuilder AppendClassParamsType(this StringBuilder builder, UhtClass classObj)` — Append the name of the class params
- L3811-3815 _public method_ `public static StringBuilder AppendStructParamsType(this StringBuilder builder, UhtStruct structObj)` — Append the name of the struct params
- L3823-3827 _public method_ `public static StringBuilder AppendEnumParamsType(this StringBuilder builder, UhtEnum enumObj)` — Append the name of the enum params

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtHeaderCodeGeneratorHFile.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtHeaderCodeGeneratorHFile`  
`internal sealed class UhtHeaderCodeGeneratorHFile : UhtHeaderCodeGenerator`  
_internal; L15-2156_
- inherits: `UhtHeaderCodeGenerator`
- L18 _public field_ `public static string RigVMExecuteContextParamName = "ExecuteContext"`
- L19 _public field_ `public static string RigVMExecuteContextDeclaration = "FRigVMExtendedExecuteContext& RigVMExecuteContext"`
- L26-29 _public ctor_ `public UhtHeaderCodeGeneratorHFile(UhtCodeGenerator codeGenerator, UhtHeaderFile headerFile) : base(codeGenerator, headerFile)` — Construct an instance of this generator object
- L35-232 _public method_ `public void Generate(IUhtExportFactory factory)` — For a given UE header file, generated the generated H file
- L234-269 _private method_ `private static StringBuilder AppendRigVmStructInfoDefine(StringBuilder builder, UhtScriptStruct scriptStruct)`
- L271-497 _private method_ `private static StringBuilder AppendRigVmStructInfoMethods(StringBuilder builder, UhtScriptStruct scriptStruct)`
- L499-729 _private method_ `private StringBuilder AppendScriptStruct(StringBuilder builder, UhtScriptStruct scriptStruct)`
- L731-754 _private method_ `private StringBuilder Appendpartial(StringBuilder builder, UhtPartial partial)`
- L756-829 _private method_ `private StringBuilder AppendEnum(StringBuilder builder, UhtEnum enumObj)`
- L831-1012 _private method_ `private StringBuilder AppendClass(StringBuilder builder, UhtClass classObj)`
- L1014-1046 _private method_ `private static StringBuilder AppendNativeInterfaceVerseProxy(StringBuilder builder, UhtClass classObj)`
- L1048-1058 _private method_ `private static StringBuilder AppendNativeInterfaceVerseProxyFunctions(StringBuilder builder, UhtClass? classObj)`
- L1060-1070 _private method_ `private StringBuilder AppendProlog(StringBuilder builder, UhtClass classObj )`
- L1072-1108 _private method_ `private StringBuilder AppendFieldNotify(StringBuilder builder, UhtClass classObj)`
- L1110-1134 _private method_ `private StringBuilder AppendAutoGettersSetters(StringBuilder builder, UhtClass classObj, string api, UhtUsedDefineScopes<UhtProperty> autoGetterSetterProperties)`
- L1136-1148 _private method_ `private static IEnumerable<UhtProperty> EnumerateSparseDataStructProperties(IEnumerable<UhtScriptStruct> sparseScriptStructs)`
- L1150-1183 _private method_ `private StringBuilder AppendSparseDeclarations(StringBuilder builder, UhtClass classObj, IEnumerable<UhtScriptStruct> sparseScriptStructs, UhtUsedDefineScopes<UhtProperty> sparseProperties)`
- L1185-1205 _private method_ `private StringBuilder AppendSparseStructDeclarations(StringBuilder builder, UhtClass classObj, IEnumerable<UhtScriptStruct> sparseScriptStructs)`
- L1207-1227 _private method_ `private StringBuilder AppendRpcFunctions(StringBuilder builder, UhtClass classObj, bool usesLegacy, UhtUsedDefineScopes<UhtFunction> functions)`
- L1229-1240 _private method_ `private StringBuilder AppendVerseNativeCallableFunctions(StringBuilder builder, UhtClass classObj, UhtUsedDefineScopes<UhtFunction> functions)`
- L1242-1258 _private method_ `private static StringBuilder AppendVerseNativeCallableProxyFunctions(StringBuilder builder, UhtClass classObj, UhtUsedDefineScopes<UhtFunction> functions)`
- L1260-1279 _private method_ `private StringBuilder AppendPropertyAccessors(StringBuilder builder, UhtClass classObj, IEnumerable<UhtProperty> getterSetterProperties)`
- L1281-1299 _private method_ `private StringBuilder AppendAutogeneratedBlueprintFunctionDeclarations(StringBuilder builder, UhtClass classObj, IEnumerable<UhtFunction> functions)`
- L1301-1319 _private method_ `private StringBuilder AppendAutogeneratedBlueprintFunctionDeclarationsOnlyNotDeclared(StringBuilder builder, UhtClass classObj, IEnumerable<UhtFunction> functions)`
- L1321-1343 _private method_ `private StringBuilder AppendNetValidateDeclaration(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L1345-1371 _private method_ `private static StringBuilder AppendRpcWrappers(StringBuilder builder, IEnumerable<UhtFunction> functions)`
- L1373-1389 _private method_ `private StringBuilder AppendCallbackRpcWrapperDecls(StringBuilder builder, UhtClass classObj, List<UhtFunction> callbackFunctions)`
- L1391-1399 _private method_ `private StringBuilder AppendSerializer(StringBuilder builder, UhtClass classObj, string api, UhtSerializerArchiveType type, string declare)`
- L1408-1436 _private method_ `private StringBuilder AppendStandardConstructors(StringBuilder builder, UhtClass classObj, string api)` — Generates standard constructor declarations
- L1445-1455 _private method_ `private StringBuilder AppendEnhancedConstructors(StringBuilder builder, UhtClass classObj, string api)` — Generates enhanced constructor declaration.
- L1464-1472 _private method_ `private static StringBuilder AppendVTableHelperCtorAndCaller(StringBuilder builder, UhtClass classObj, string api)` — Generates vtable helper caller and eventual constructor body.
- L1480-1486 _private method_ `private static StringBuilder AppendCopyConstructorDefinition(StringBuilder builder, UhtClass classObj)` — Generates private copy-constructor declaration.
- L1495-1523 _private method_ `private static StringBuilder AppendDestructorDefinition(StringBuilder builder, UhtClass classObj, string api)` — Generates a destructor
- L1532-1550 _private method_ `private static StringBuilder AppendConstructorDefinition(StringBuilder builder, UhtClass classObj, string api)` — Generates private copy-constructor declaration.
- L1558-1592 _private method_ `private static StringBuilder AppendDefaultConstructorCallDefinition(StringBuilder builder, UhtClass classObj)` — Generates constructor call definition
- L1601-1631 _private method_ `private StringBuilder AppendClassGeneratedBody(StringBuilder builder, UhtClass classObj, string api)` — Generates generated body code for classes
- L1639-1720 _private method_ `private StringBuilder AppendCommonGeneratedBody(StringBuilder builder, UhtClass classObj)` — Generates standard generated body code for interfaces and non-interfaces
- L1729-1772 _private method_ `private static StringBuilder AppendClassFlags(StringBuilder builder, UhtClass classObj)` — Appends the class flags in the form of CLASS_Something|CLASS_Something which represents all class flags that are set for the specified class which need to be exported as part of the DECLARE_CLASS macro
- L1781-1786 _private method_ `private static StringBuilder AppendGeneratedMacroDeprecationWarning(StringBuilder builder, string macroName)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "Referencing code commented out")]` — Appends preprocessor string to emit GENERATED_U*_BODY() macro is deprecated.
- L1788-1806 _private method_ `private static StringBuilder AppendAccessSpecifier(StringBuilder builder, UhtClass classObj)`
- L1808-1835 _private method_ `private StringBuilder AppendInClassIInterface(StringBuilder builder, UhtClass classObj, List<UhtFunction> callbackFunctions, string api)`
- L1837-1871 _private method_ `private static StringBuilder AppendReplicatedMacroData(StringBuilder builder, UhtClass classObj, string api)`
- L1873-1952 _private method_ `private static StringBuilder AppendNetData(StringBuilder builder, UhtClass classObj, string api)`
- L1954-1966 _private method_ `private StringBuilder AppendInterfaceCallFunctions(StringBuilder builder, List<UhtFunction> callbackFunctions)`
- L1968-2048 _private method_ `private StringBuilder AppendGeneratedBodyMacroBlock(StringBuilder builder, UhtClass classObj, UhtClass bodyClassObj, bool isLegacy, UhtUsedDefineScopes<UhtFunction> rpcFunctions, UhtUsedDefineScopes<UhtFunction> verseNativeCallableFunctions, UhtUsedDefineScopes<UhtProperty> autoGetterSetterProperties, bool hasSparseStructs, UhtUsedDefineScopes<UhtProperty> sparseProperties, IEnumerable<UhtProperty> getterSetterProperties, bool hasCallbacks, string? deprecatedMacroName)`
- L2050-2053 _private method_ `private static StringBuilder AppendForwardDeclarationWithNamespace(StringBuilder builder, UhtField field)`
- L2056-2059 _private method_ `private static bool IsFullEnumName(string inEnumName)`
- L2061-2110 _private method_ `private static StringView GenerateEnumPrefix(UhtEnum enumObj)`
- L2112-2119 _private method_ `private static string GenerateFullEnumName(UhtEnum enumObj, string inEnumName)`
- L2121-2134 _private method_ `private static bool EnumHasExistingMax(UhtEnum enumObj)`
- L2136-2154 _private method_ `private static long GetMaxEnumValue(UhtEnum enumObj)`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtClassExtensions`  
`static class UhtClassExtensions`  
_internal*; L2158-2178_
- L2160-2177 _public method_ `public static IEnumerable<UhtProperty> EnumerateReplicatedProperties(this UhtClass classObj, bool includeSuper)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtMacroBlockEmitter.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Exporters.CodeGen.UhtMacroBlockEmitter`  
`internal struct UhtMacroBlockEmitter : IDisposable`  
_internal; L9-90_
- inherits: `IDisposable`
- L11 _private field_ `private readonly StringBuilder _builder`
- L12 _private field_ `private UhtDefineScope _current = UhtDefineScope.None`
- L13 _private field_ `private bool _open = false`
- L15-19 _public ctor_ `public UhtMacroBlockEmitter(StringBuilder builder, UhtDefineScope initialState)`
- L25-46 _public method_ `public void Set(UhtDefineScope defineScope)` — Change the define scope to the new provided one using #endif and #if
- L55-80 _public method_ `public void SetElse(UhtDefineScope defineScope)` — Change the define scope to the new provided. None -> Scope X uses #if Scope X -> None uses #else Scope X -> Scope Y uses #elif
- L82-89 _public method_ `public void Dispose()`

#### struct `EpicGames.UHT.Exporters.CodeGen.UhtConditionalMacroBlock`  
`internal struct UhtConditionalMacroBlock : IDisposable`  
_internal; L97-122_
- inherits: `IDisposable`
- desc: Utility class to wrap blocks of generated code in #if/#endif for a literal string conditionally. i.e. used to conditionally wrap code in #if UE_WITH_CONSTINIT_UOBJECT depending on the value of Session.IsUsingMultipleCompiledInObjectFormats
- L99 _private field_ `private readonly StringBuilder _builder`
- L100 _private field_ `private readonly string _macroName`
- L101 _private field_ `private bool _enabled`
- L103-112 _public ctor_ `public UhtConditionalMacroBlock(StringBuilder builder, string macroName, bool isEnabled)`
- L114-121 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtMacroCreator.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Exporters.CodeGen.UhtMacroCreator`  
`internal readonly struct UhtMacroCreator : IDisposable`  
_internal; L10-58_
- inherits: `IDisposable`
- L12 _private field_ `private readonly StringBuilder _builder`
- L13 _private field_ `private readonly int _startingLength`
- L15-20 _public ctor_ `public UhtMacroCreator(StringBuilder builder, UhtHeaderCodeGenerator generator, int lineNumber, string macroSuffix)`
- L22-27 _public ctor_ `public UhtMacroCreator(StringBuilder builder, UhtHeaderCodeGenerator generator, UhtType type, string macroSuffix)`
- L29-34 _public ctor_ `public UhtMacroCreator(StringBuilder builder, UhtHeaderCodeGenerator generator, UhtType type, string macroSuffix, UhtDefineScope defineScope = UhtDefineScope.None, bool includeSuffix = true)`
- L36-57 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtPackageCodeGenerator.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtPackageCodeGenerator`  
`class UhtPackageCodeGenerator : IUhtObjectLinker`  
_internal*; L12-128_
- inherits: `IUhtObjectLinker`
- L14 _public field_ `public static string HeaderCopyright = "// Copyright Epic Games, Inc. All Rights Reserved.\r\n" + "/*===========================================================================\r\n" + "\tGenerated code exported from UnrealHeaderTool.\r\n"  ...`
- L22 _public field_ `public static string RequiredCPPIncludes = "#include \"UObject/GeneratedCppIncludes.h\"\r\n"`
- L24 _public field_ `public static string EnableDeprecationWarnings = "PRAGMA_ENABLE_DEPRECATION_WARNINGS"`
- L25 _public field_ `public static string DisableDeprecationWarnings = "PRAGMA_DISABLE_DEPRECATION_WARNINGS"`
- L27 _public field_ `public readonly UhtCodeGenerator CodeGenerator`
- L28 _public field_ `public readonly UhtModule Module`
- L29 _public property_ `public bool SaveExportedHeaders => ...`
- L31 _public property_ `public Utils.UhtSession Session => ...`
- L32 _public property_ `public UhtCodeGenerator.PackageInfo[] PackageInfos => ...`
- L33 _public property_ `public UhtCodeGenerator.HeaderInfo[] HeaderInfos => ...`
- L34 _public property_ `public UhtCodeGenerator.ObjectInfo[] ObjectInfos => ...`
- L36-40 _public ctor_ `public UhtPackageCodeGenerator(UhtCodeGenerator codeGenerator, UhtModule module)`
- L50-53 _public method_ `public string GetSingletonName(UhtObject? obj, UhtSingletonType type)` — Return the singleton name for an object
- L56 _public method_ `public bool IsCrossModuleRef(UhtObject obj)` — (inheritdoc)
- L59-73 _public method_ `public int GetModuleIndex(UhtModule otherModule)` — (inheritdoc)
- L76-90 _public method_ `public int GetObjectIndex(UhtObject obj)` — (inheritdoc)
- L98-101 _public method_ `public string GetExternalDecl(UhtObject obj, UhtSingletonType type)` — Return the external declaration for an object
- L109-112 _public method_ `public string GetExternalDecl(int objectIndex, UhtSingletonType type)` — Return the external declaration for an object
- L119-126 _public method_ `public static bool IsDelegateFunction(UhtField field)` — Test to see if the given field is a delegate function

#### class `EpicGames.UHT.Exporters.CodeGen.UhtPackageCodeGeneratorExtensions`  
`public static class UhtPackageCodeGeneratorExtensions`  
_public; L133-203_
- desc: Helper formatting methods
- L143-151 _internal method_ `internal static StringBuilder AppendSingletonRef(this StringBuilder builder, IUhtSingletonNameProvider provider, UhtObject? obj, UhtSingletonType singletonType)` — Append an expression to reference a singleton. i.e. the name of a factory function, or an address-of expression for a constinit variable ref.
- L160-163 _internal method_ `internal static StringBuilder AppendConstInitSingletonRef(this StringBuilder builder, IUhtSingletonNameProvider provider, UhtObject? obj)` — Append nullptr or an address-of expression for the constinit singleton for the given object
- L165-188 _internal method_ `internal static StringBuilder AppendLinkingMacros(this StringBuilder builder, UhtSession session, IEnumerable<UhtModule> modules)`
- L190-202 _internal method_ `internal static StringBuilder AppendLinkingMacrosUndef(this StringBuilder builder, UhtSession session, IEnumerable<UhtModule> modules)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtPackageCodeGeneratorCppFile.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtPackageCodeGeneratorCppFile`  
`internal sealed class UhtPackageCodeGeneratorCppFile : UhtPackageCodeGenerator`  
_internal; L16-411_
- inherits: `UhtPackageCodeGenerator`
- L23-26 _public ctor_ `public UhtPackageCodeGeneratorCppFile(UhtCodeGenerator codeGenerator, UhtModule module) : base(codeGenerator, module)` — Construct an instance of this generator object
- L33-376 _public method_ `public void Generate(IUhtExportFactory factory, List<UhtHeaderFile> packageSortedHeaders)` — For a given UE header file, generated the generated cpp file
- L378-388 _private method_ `private static string GetVniPackageName(ReadOnlySpan<char> packageName)`
- L390-405 _private method_ `private static (int Start, int End) GetTypeRange<T>(ReadOnlyCollection<UhtObject> objects, int start) where T : UhtObject`
- L407 _private method_ `private static SimpleExpression ModuleLinkableObjects(UhtModule module)`
- L408 _private method_ `private static SimpleExpression ModuleLinkedModules(UhtModule module)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtPackageCodeGeneratorHFile.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtPackageCodeGeneratorHFile`  
`internal sealed class UhtPackageCodeGeneratorHFile : UhtPackageCodeGenerator`  
_internal; L12-71_
- inherits: `UhtPackageCodeGenerator`
- L19-22 _public ctor_ `public UhtPackageCodeGeneratorHFile(UhtCodeGenerator codeGenerator, UhtModule module) : base(codeGenerator, module)` — Construct an instance of this generator object
- L29-70 _public method_ `public void Generate(IUhtExportFactory factory, List<UhtHeaderFile> moduleSortedHeaders)` — For a given UE header file, generated the generated H file

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtRigVMStringBuilderExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtRigVMStringBuilderExtensions`  
`internal static class UhtRigVMStringBuilderExtensions`  
_internal; L10-121_
- L12-15 _public method_ `public static StringBuilder AppendArgumentsName(this StringBuilder builder, UhtStruct structObj, UhtRigVMMethodInfo methodInfo)`
- L17-35 _public method_ `public static StringBuilder AppendParameterNames(this StringBuilder builder, IEnumerable<UhtRigVMParameter> parameters, bool leadingSeparator = false, string separator = ", ", bool castName = false, bool includeEditorOnly = false)`
- L37-58 _public method_ `public static StringBuilder AppendTypeConstRef(this StringBuilder builder, UhtRigVMParameter parameter, bool castType = false)`
- L60-73 _public method_ `public static StringBuilder AppendTypeRef(this StringBuilder builder, UhtRigVMParameter parameter, bool castType = false)`
- L75-84 _public method_ `public static StringBuilder AppendTypeNoRef(this StringBuilder builder, UhtRigVMParameter parameter, bool castType = false)`
- L86-97 _public method_ `public static StringBuilder AppendTypeVariableRef(this StringBuilder builder, UhtRigVMParameter parameter, bool castType = false)`
- L99-120 _public method_ `public static StringBuilder AppendParameterDecls(this StringBuilder builder, IEnumerable<UhtRigVMParameter> parameters, bool leadingSeparator = false, string separator = ", ", bool castType = false, bool castName = false, bool includeEditorOnly = false)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtStaticsEmitter.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtStaticsEmitter`  
`class UhtStaticsEmitter : IDisposable`  
_internal*; L9-39_
- inherits: `IDisposable`
- L11 _private field_ `private readonly StringBuilder _builder`
- L13-17 _public ctor_ `public UhtStaticsEmitter(StringBuilder builder, IUhtSingletonNameProvider provider, UhtObject obj)`
- L19-23 _public ctor_ `public UhtStaticsEmitter(StringBuilder builder, string definition)`
- L25-28 _public method_ `public void Dispose()`
- L30-38 _private method_ `private void EmitMacro(string definition)`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/CodeGen/UhtUsedDefineScopes.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.CodeGen.UhtUsedDefineScopes`  
`public class UhtUsedDefineScopes<T> where T : UhtType`  
_public; L19-163_
- constraints: `where T : UhtType`
- desc: Helper class for collection where types exist in different define scope blocks
- L21 _private field_ `private bool _first = true`
- L22 _private field_ `private UhtDefineScope _soleScope = UhtDefineScope.Invalid`
- L23 _private field_ `private UhtDefineScope _allScopes = UhtDefineScope.None`
- L24 _private field_ `private uint _present = 0`
- L29 _public property_ `public List<T> Instances { get; }` — Collection of instances
- L34 _public property_ `public bool IsEmpty => ...` — If true, there are no instances
- L39 _public property_ `public bool HasNoneScope => ...` — If true, at least one instance had no scope
- L45 _public property_ `public UhtDefineScope SoleScope => ...` — If all types share the same scope, then the sole scope is that scope. The value will be Invalid if the instances have different scopes.
- L50 _public property_ `public UhtDefineScope AllScopes => ...` — Collection of all scopes found in the types. If
- L55 _public property_ `public UhtDefineScope NoneAwareScopes => ...` — If any instance has no scope, then None is returned. Otherwise AllScopes is returned.
- L60-62 _public ctor_ `public UhtUsedDefineScopes()` — Constructor with no initial instances
- L68-71 _public ctor_ `public UhtUsedDefineScopes(IEnumerable<T> instances)` — Constructor with initial range of types
- L77-92 _public method_ `public void Add(T instance)` — Add an instance to the collection
- L98-104 _public method_ `public void AddRange(IEnumerable<T> instances)` — Add a range of instances to the collection
- L111-114 _public method_ `public bool HasScope(UhtDefineScope defineScope)` — Check to see if the given scope has instances
- L119-122 _public method_ `public void OrderByDefineScope()` — Update the list to by ordered by the define scope
- L128-138 _public method_ `public IEnumerable<UhtDefineScope> EnumerateDefinedScopes()` — Enumerate all of the used defined scopes
- L144-157 _public method_ `public IEnumerable<UhtDefineScope> EnumerateDefinedScopesNoneAtEnd()` — Enumerate all of the used defined scopes
- L159-162 _private method_ `private static uint ScopeToMask(UhtDefineScope defineScope)`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtDefineScopeListBuilder`  
`public class UhtDefineScopeListBuilder<T> : IDisposable where T : UhtType`  
_public; L170-226_
- inherits: `IDisposable`
- constraints: `where T : UhtType`
- desc: Helper class to build linked lists of objects which are defined in different scopes. e.g. properties of a class, where some properties are only present when WITH_EDITORONLY_DATA is defined
- L176-180 _public ctor_ `public UhtDefineScopeListBuilder(UhtDefineScope scope)` — Initialize the builder with an empty 'head' link.
- L185 _public property_ `public UhtDefineScopeLink<T> Head { get; }` — Link pointing to the first object in the list for each relevant define scope.
- L192-202 _public method_ `public UhtDefineScopeLink<T> Add(T inNext)` — Add the given object as the next object after any preceding object which does not yet have a following object in the scope(s) the new object is defined in.
- L205-209 _public method_ `public void Dispose()` — (inheritdoc)
- L214-223 _protected method_ `protected virtual void Dispose(bool disposing)` — Explicitly terminate each pending link with null
- L225 _private field_ `private readonly List<UhtDefineScopeLink<T>> _pending = []`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtDefineScopeLink`  
`public class UhtDefineScopeLink<T> where T : UhtType`  
_public; L234-332_
- constraints: `where T : UhtType`
- desc: This class can be used as a field in UhtTypes to perform as an intrusive linked list 'next' pointer to another object of the same type, resolving to a different object depending on which preprocessor definitions are set.
- L240-246 _public ctor_ `public UhtDefineScopeLink(UhtDefineScope thisScope)` — Initialize this link with the declaration scope of the object holding the link.
- L256-270 _public method_ `public void Add(T inNext)` — Try to add a new element following this one in the linked list. If there is already a next element for every combination of scopes for which this and the candidate are defined, the new element will not be added. If, after adding the new element, there is a next element for every combination of scopes in which this is defined, this link will return true from IsComplete.
- L276-283 _public method_ `public void Terminate()` — Must be called on an incomplete link. Terminates the link explicitly with nullptr to handle the case where there is a next link for some scopes, but none for all scopes the link is defined in.
- L288 _public property_ `public bool IsComplete { get; set; }` — Returns true if there is a next element for every combination of scopes which this is defined.
- L293 _public property_ `public UhtDefineScope InitialScope => ...` — Returns the scope of the first object in the list, or UhtDefineScope.None.
- L299 _public property_ `public IReadOnlyList<T?> Next => ...` — Returns all objects which follow this object in some relevant scope. Only the last element may be null.
- L302 _private field_ `private readonly List<T?> _next = []`
- L305 _private field_ `private readonly UhtDefineScope _thisScope`
- L308 _private field_ `private readonly uint _completionMask`
- L311 _private field_ `private uint _addedScopes = 0`
- L315-319 _private method_ `private static uint ToCompletionMask(UhtDefineScope scope)`
- L323-331 _private method_ `private uint ToAddedMask(UhtDefineScope scope)`

#### class `EpicGames.UHT.Exporters.CodeGen.UhtUsedDefineScopesExtensions`  
`internal static class UhtUsedDefineScopesExtensions`  
_internal; L353-929_
- desc: Helper extensions when working with defined scope collections. This class helps with producing consistent and correct code that works with the DefineScope element in UhtType. In generated header files, it supports two flavors of macro definitions used to generate the body macro. The multi macro style will generate one macro for each unique combination of DefineScope found. Only the instances that match the DefineScope will be placed in that macro. The macros will be generated in such a way that they will always be present and each much be included in the generated body macro. This style is used to generate declarations as needed. The single macro style will generate a single macro, but that macro will appear multiple times depending on each combination of the DefineScope combinations required. Each macro will have a complete set of instances filtered by the DefineScope. This style is used to populate such things as enum definitions needed by the engine. In generated cpp files, there is
- L363-368 _public method_ `public static StringBuilder AppendScoped(this StringBuilder builder, UhtDefineScope defineScope, Action<StringBuilder> appendAction)` — Append a macro scoped macro
- L377-384 _public method_ `public static StringBuilder AppendMultiScoped<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, Action<StringBuilder, IEnumerable<T>> appendAction) where T : UhtType` — Append multiple for the given collection of scopes
- L397-430 _public method_ `public static StringBuilder AppendScopedMacro(this StringBuilder builder, UhtDefineScope defineScope, UhtHeaderCodeGenerator generator, UhtType outerType, string macroSuffix, bool includeSuffix, Action<StringBuilder> appendAction)` — Append a macro scoped macro
- L442-451 _public method_ `public static StringBuilder AppendMultiScopedMacros<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, UhtHeaderCodeGenerator generator, UhtType outerType, string macroSuffix, Action<StringBuilder, IEnumerable<T>> appendAction) where T : UhtType` — Append multi macros for the given collection of scopes
- L462-470 _public method_ `public static StringBuilder AppendMultiMacroRefs<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, UhtHeaderCodeGenerator generator, UhtType outerType, string macroSuffix) where T : UhtType` — Append the macro definitions requested
- L483-525 _public method_ `public static StringBuilder AppendSingleMacro<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, UhtHeaderCodeGenerator generator, UhtType outerType, string macroSuffix, Action<StringBuilder, IEnumerable<T>> appendAction) where T : UhtType` — Append a single macro, where the macro -same- definition can exist inside of define scopes where the instances contained are all instances that would be satisfied by a scope.
- L535-543 _public method_ `public static StringBuilder AppendIfInstances<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, Action<StringBuilder> appendAction) where T : UhtType` — Invoke the append action if any types are present. If all types are from the same define scope, then it will be wrapped with and #if block.
- L552-555 _public method_ `public static StringBuilder AppendInstances<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, Action<StringBuilder, T> appendAction) where T : UhtType` — Append each instance to the builder
- L566-584 _public method_ `public static StringBuilder AppendInstances<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, Action<StringBuilder>? preambleAction, Action<StringBuilder, T> appendAction, Action<StringBuilder>? postambleAction) where T : UhtType` — Append each instance to the builder
- L595-634 _public method_ `public static StringBuilder AppendArrayView<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, UhtCppIdentifier identifier, int tabs, string endl) where T : UhtType` — Append an array view construction expression for the given instances
- L645-683 _public method_ `public static StringBuilder AppendArrayPtrAndCountLine<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, UhtCppIdentifier identifier, int tabs, string endl) where T : UhtType` — Append the given array list and count as arguments to a structure constructor
- L694-732 _public method_ `public static StringBuilder AppendArrayPtrLine<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, UhtCppIdentifier identifier, int tabs, string endl) where T : UhtType` — Append the given array list as arguments to a structure constructor
- L743-781 _public method_ `public static StringBuilder AppendArrayCountLine<T>(this StringBuilder builder, UhtUsedDefineScopes<T> instances, UhtCppIdentifier identifier, int tabs, string endl) where T : UhtType` — Append the given array count as arguments to a structure constructor
- L792-810 _public method_ `public static StringBuilder AppendScopeLink(this StringBuilder builder, UhtDefineScopeLink<UhtProperty>? link, int tabs, string? prefix, string? endl)` — Append a link which resolves to a different object under different preprocessor definitions
- L822-840 _public method_ `public static StringBuilder AppendScopeLink(this StringBuilder builder, UhtDefineScopeLink<UhtFunction>? link, IUhtPropertyMemberContext context, int tabs, string? prefix, string? endl)` — Append a link which resolves to a different object under different preprocessor definitions
- L848-855 _public method_ `public static StringBuilder AppendIfPreprocessor(this StringBuilder builder, UhtDefineScope defineScope)` — Start an #if block with the given scope
- L863-870 _public method_ `public static StringBuilder AppendElsePreprocessor(this StringBuilder builder, UhtDefineScope defineScope)` — Start an #else block with the given scope
- L878-885 _public method_ `public static StringBuilder AppendElseIfPreprocessor(this StringBuilder builder, UhtDefineScope defineScope)` — Start an #elif block with the given scope
- L893-900 _public method_ `public static StringBuilder AppendEndIfPreprocessor(this StringBuilder builder, UhtDefineScope defineScope)` — Start an #endif block with the given scope
- L908-928 _public method_ `public static StringBuilder AppendScopeExpression(this StringBuilder builder, UhtDefineScope defineScope)` — Append scope expression (i.e. WITH_X && WITH_Y && ...)

### `Source/Programs/Shared/EpicGames.UHT/Exporters/Json/UhtJsonExporter.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.Json.UhtJsonExporter`  
`sealed class UhtJsonExporter`  
_internal*; L14-57_
- attrs: `[UnrealHeaderTool]`
- L18-21 _public method_ `public static void JsonExporter(IUhtExportFactory factory)` — attrs: `[UhtExporter(Name = "Json", Description = "Json description of packages", Options = UhtExporterOptions.None)]`
- L23 _public field_ `public readonly IUhtExportFactory Factory`
- L24 _public property_ `public UhtSession Session => ...`
- L26-29 _private ctor_ `private UhtJsonExporter(IUhtExportFactory factory)`
- L31-56 _private method_ `private void Export()`

### `Source/Programs/Shared/EpicGames.UHT/Exporters/Stats/UhtStatsExporter.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Exporters.Stats.UhtStatsExporter`  
`internal sealed class UhtStatsExporter`  
_internal; L13-54_
- attrs: `[UnrealHeaderTool]`
- L17-36 _private method_ `private static void StatsExporter(IUhtExportFactory factory)` — attrs: `[UhtExporter(Name = "Stats", Description = "Type Stats", Options = UhtExporterOptions.None)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- L38-53 _private method_ `private static void Collect(SortedDictionary<string, int> countByType, UhtType type)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtClassParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtClassParser`  
`public static class UhtClassParser`  
_public; L16-162_
- attrs: `[UnrealHeaderTool]`
- desc: UCLASS parser
- L23-26 _private method_ `private static UhtParseResult UCLASSKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`
- L31-34 _private method_ `private static UhtParseResult VMODULEKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`
- L40-62 _private method_ `private static UhtParseResult GENERATED_UCLASS_BODYKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Class)] [UhtKeyword(Extends = UhtTableNames.Class, Keyword = "GENERATED_BODY")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Supp`
- L65-161 _private method_ `private static UhtParseResult ParseUClass(UhtParsingScope parentScope, ref UhtToken token)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtEnumParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtEnumParser`  
`public static class UhtEnumParser`  
_public; L16-266_
- attrs: `[UnrealHeaderTool]`
- desc: UENUM parser
- L22-25 _private method_ `private static UhtParseResult UENUMKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`
- L28-247 _private method_ `private static UhtParseResult ParseUEnum(UhtParsingScope parentScope, UhtToken keywordToken)`
- L249-265 _private method_ `private static void ParseUnderlyingType(UhtParsingScope topScope, UhtEnum enumObject)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtFunctionParser.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Parsers.UhtAdvancedDisplayParameterHandler`  
`struct UhtAdvancedDisplayParameterHandler`  
_internal*; L20-90_
- L22 _private field_ `private readonly UhtMetaData _metaData`
- L23 _private field_ `private readonly string[]? _parameterNames`
- L24 _private field_ `private readonly int _numberLeaveUnmarked`
- L25 _private field_ `private readonly bool _bUseNumber`
- L26 _private field_ `private int _alreadyLeft`
- L28-48 _public ctor_ `public UhtAdvancedDisplayParameterHandler(UhtMetaData metaData)`
- L54-83 _public method_ `public bool ShouldMarkParameter(StringView parameterName)`
- L86-89 _public method_ `public readonly bool CanMarkMore()`

#### class `EpicGames.UHT.Parsers.UhtFunctionParser`  
`public static class UhtFunctionParser`  
_public; L96-763_
- attrs: `[UnrealHeaderTool]`
- desc: UFUNCTION parser
- L103-106 _private method_ `private static UhtParseResult UDELEGATEKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global)] [UhtKeyword(Extends = UhtTableNames.Class)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE00`
- L115-118 _private method_ `private static UhtParseResult UFUNCTIONKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Class)] [UhtKeyword(Extends = UhtTableNames.Interface)] [UhtKeyword(Extends = UhtTableNames.NativeInterface)] [UhtKeyword(Extends = UhtTableNames.VModule)] [UhtKeyword(Extends = UhtTableNames.Partial)] [S`
- L122-129 _private method_ `private static UhtParseResult ParseCatchAllKeyword(UhtParsingScope topScope, ref UhtToken token)` — attrs: `[UhtKeywordCatchAll(Extends = UhtTableNames.Global)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- L132-308 _private method_ `private static UhtParseResult ParseUDelegate(UhtParsingScope parentScope, UhtToken token, bool hasSpecifiers)`
- L310-608 _private method_ `private static UhtParseResult ParseUFunction(UhtParsingScope parentScope, UhtToken token)`
- L610-617 _private method_ `private static void FinalizeFunctionSpecifiers(UhtFunction function)`
- L619-622 _internal method_ `internal static bool IsValidateDelegateDeclaration(UhtToken token)`
- L624-692 _private method_ `private static void ParseParameterList(UhtParsingScope topScope, UhtPropertyParseOptions options)`
- L694-697 _private method_ `private static void AddFunction(UhtFunction function)`
- L699-762 _private method_ `private static void SetFunctionNames(UhtFunction function)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtHeaderFileParser.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Parsers.UhtParseResult`  
`public enum UhtParseResult`  
_public; L19-36_
- desc: Keyword parse results
- L25 _public* enumerator_ `Handled` — Keyword was handled
- L30 _public* enumerator_ `Unhandled` — Keyword wasn't handled (more attempts will be made to match)
- L35 _public* enumerator_ `Invalid` — Keyword is invalid

#### enum `EpicGames.UHT.Parsers.UhtCompilerDirective`  
`public enum UhtCompilerDirective`  
_public; L43-129_
- attrs: `[Flags] [SuppressMessage("Usage", "CA2217:Do not mark enums with FlagsAttribute")]`
- desc: Compiler directives
- L48 _public* enumerator_ `None = 0` — No compile directives
- L53 _public* enumerator_ `CPPBlock = 1 << 0` — This indicates we are in a "#if CPP" block
- L58 _public* enumerator_ `NotCPPBlock = 1 << 1` — This indicates we are in a "#if !CPP" block
- L63 _public* enumerator_ `ZeroBlock = 1 << 2` — This indicates we are in a "#if 0" block
- L68 _public* enumerator_ `OneBlock = 1 << 3` — This indicates we are in a "#if 1" block
- L73 _public* enumerator_ `WithEditor = 1 << 4` — This indicates we are in a "#if WITH_EDITOR" block
- L78 _public* enumerator_ `WithEditorOnlyData = 1 << 5` — This indicates we are in a "#if WITH_EDITORONLY_DATA" block
- L83 _public* enumerator_ `WithHotReload = 1 << 6` — This indicates we are in a "#if WITH_HOT_RELOAD" block
- L88 _public* enumerator_ `WithEngine = 1 << 7` — This indicates we are in a "#if WITH_ENGINE" block
- L93 _public* enumerator_ `WithCoreUObject = 1 << 8` — This indicates we are in a "#if WITH_COREUOBJECT" block
- L98 _public* enumerator_ `WithVerseVM = 1 << 9` — This indicates we are in a "#if WITH_VERSE_VM" block
- L103 _public* enumerator_ `Unrecognized = 1 << 10` — This directive is unrecognized and does not change the code generation at all
- L108 _public* enumerator_ `WithTests = 1 << 11` — This indicates we are in a "#if WITH_TESTS" block
- L113 _public* enumerator_ `WithVerseBPVM = 1 << 12` — This indicates we are in a "#if WITH_VERSE_BPVM" block
- L118 _public* enumerator_ `AllowedCheckIgnoredFlags = CPPBlock | NotCPPBlock | ZeroBlock | OneBlock | WithHotReload` — The following flags are always ignored when keywords test for allowed conditional blocks
- L123 _public* enumerator_ `DefaultAllowedCheck = WithEditor | WithEditorOnlyData | WithVerseVM | WithTests | WithVerseBPVM` — Default compiler directives to be allowed
- L128 _public* enumerator_ `SilenceAllowedCheck = ~None` — All flags are allowed

#### class `EpicGames.UHT.Parsers.UhtCompilerDirectiveExtensions`  
`public static class UhtCompilerDirectiveExtensions`  
_public; L135-280_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L137 _private field_ `private static readonly Lazy<List<string>> s_names = new(() => { List<string> outList = []; FieldInfo[] fields = typeof(UhtCompilerDirective).GetFields(); for (int bit = 0; bit < 32; ++bit) { bool found = false; uint mask = (uint)1 << bit; foreach (Fiel ...`
- L175-193 _public method_ `public static string GetCompilerDirectiveText(this UhtCompilerDirective compilerDirective)` — Return the text associated with the given compiler directive
- L200-220 _public method_ `public static UhtDefineScope GetDefaultDefineScopes(this UhtCompilerDirective compilerDirectives)` — Return a define scope based on the given compiler directives
- L227-245 _public method_ `public static List<string> ToStringList(this UhtCompilerDirective inFlags)` — Return a string list of the given compiler directives
- L253-256 _public method_ `public static bool HasAnyFlags(this UhtCompilerDirective inFlags, UhtCompilerDirective testFlags)` — Test to see if any of the specified flags are set
- L264-267 _public method_ `public static bool HasAllFlags(this UhtCompilerDirective inFlags, UhtCompilerDirective testFlags)` — Test to see if all of the specified flags are set
- L276-279 _public method_ `public static bool HasExactFlags(this UhtCompilerDirective inFlags, UhtCompilerDirective testFlags, UhtCompilerDirective matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Parsers.UhtAccessSpecifierKeywords`  
`public static class UhtAccessSpecifierKeywords`  
_public; L286-323_
- attrs: `[UnrealHeaderTool]`
- desc: Specifiers for public, private, and protected
- L293-296 _private method_ `private static UhtParseResult PublicKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.ClassBase, Keyword = "public", AllowedCompilerDirectives = UhtCompilerDirective.SilenceAllowedCheck)] [UhtKeyword(Extends = UhtTableNames.ScriptStruct, Keyword = "public", AllowedCompilerDirectives = UhtC`
- L302-305 _private method_ `private static UhtParseResult ProtectedKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.ClassBase, Keyword = "protected", AllowedCompilerDirectives = UhtCompilerDirective.SilenceAllowedCheck)] [UhtKeyword(Extends = UhtTableNames.ScriptStruct, Keyword = "protected", AllowedCompilerDirectives `
- L311-314 _private method_ `private static UhtParseResult PrivateKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.ClassBase, Keyword = "private", AllowedCompilerDirectives = UhtCompilerDirective.SilenceAllowedCheck)] [UhtKeyword(Extends = UhtTableNames.ScriptStruct, Keyword = "private", AllowedCompilerDirectives = Uh`
- L317-322 _private method_ `private static UhtParseResult SetAccessSpecifier(UhtParsingScope topScope, UhtAccessSpecifier accessSpecifier)`

#### class `EpicGames.UHT.Parsers.UhtHeaderFileParser`  
`public class UhtHeaderFileParser : IUhtTokenPreprocessor`  
_public; L328-1520_
- inherits: `IUhtTokenPreprocessor`
- desc: Header file parser
- L339 _public property_ `public UhtHeaderFile HeaderFile { get; }` — Header file being parsed
- L344 _public property_ `public UhtModule Module => ...` — Module containing the header file
- L349 _public property_ `public IUhtTokenReader TokenReader { get; }` — Token reader for the header
- L354 _public property_ `public bool SpottedAutogeneratedHeaderInclude { get; set; }` — If true, the inclusion of the generated header file was seen
- L360 _public property_ `public string? RestrictedPreprocessorContext { get; set; }` — If set, the preprocessor is run in a C++ UHT compatibility mode where only a subset of #if class of preprocessor statements are allowed.
- L365 _public property_ `public int NamespaceDepth => ...` — Depth of the namespaces
- L370 _private field_ `private readonly List<CompilerDirective> _compilerDirectives = []` — Stack of current #if states
- L375 _private field_ `private readonly List<CompilerDirective> _savedCompilerDirectives = []` — Stack of current #if states saved as part of the preprocessor state
- L380 _private field_ `private UhtParsingScope? _topScope = null` — Current top of the parsing scopes. Classes, structures and functions all allocate scopes.
- L385 _private field_ `private readonly List<UhtNamespaceElement> _namespaces = []` — Current namespaces being parsed
- L390 _private field_ `private readonly Dictionary<string, UhtNamespace> _namespaceLookupCache = ...` — Lookup cache for any namespaces defined in this header.
- L390 _private field_ `private readonly Dictionary< _namespaceLookupCache = []` — Lookup cache for any namespaces defined in this header.
- L397-447 _public method_ `public static UhtHeaderFileParser Parse(UhtHeaderFile headerFile)` — Parse the given header file
- L449-457 _private ctor_ `private UhtHeaderFileParser(UhtHeaderFile headerFile)`
- L464-471 _public method_ `public void PushScope(UhtParsingScope scope)` — Push a new scope
- L478-485 _public method_ `public void PopScope(UhtParsingScope scope)` — Pop the given scope
- L491-494 _public method_ `public void PushNamespace(UhtToken token)` — Add a namespace to the token list
- L500-507 _public method_ `public void PopNamespaces(int count)` — Remove the given number of namespaces
- L513-520 _public method_ `public UhtNamespace GetNamespace()` — Returns the currently active namespace
- L526-529 _public method_ `public UhtCompilerDirective GetCurrentCompositeCompilerDirective()` — Return the current compiler directive
- L535-538 _public method_ `public UhtCompilerDirective GetCurrentNonCompositeCompilerDirective()` — Get the current compiler directive without any parent scopes merged in
- L542-551 _public method_ `public bool ParsePreprocessorDirective(ref UhtToken token, bool isBeingIncluded, out bool clearComments, out bool illegalContentsCheck)` — (inheritdoc)
- L554-558 _public method_ `public void SaveState()` — (inheritdoc)
- L561-565 _public method_ `public void RestoreState()` — (inheritdoc)
- L573-576 _public method_ `public void ParseStatements()` — Parse all statements in the header file
- L584-617 _public method_ `public void ParseStatements(char initiator, char terminator, bool logUnhandledKeywords)` — Parse the statements between the given symbols
- L626-719 _public method_ `public static bool ParseStatement(UhtParsingScope topScope, ref UhtToken token, bool logUnhandledKeywords)` — Parse a statement
- L721-742 _private method_ `private static UhtParseResult DispatchKeyword(UhtParsingScope topScope, ref UhtToken token)`
- L744-758 _private method_ `private static UhtParseResult DispatchCatchAll(UhtParsingScope topScope, ref UhtToken token)`
- L766-818 _private method_ `private static UhtParseResult ProbablyAnUnknownObjectLikeMacro(IUhtTokenReader tokenReader, ref UhtToken token)` — Tests if an identifier looks like a macro which doesn't have a following open parenthesis.
- L820-826 _private method_ `private void CheckEof(ref UhtToken token)`
- L835-1018 _private method_ `private bool ParseDirectiveInternal(bool isBeingIncluded)` — Parse a preprocessor directive.
- L1020-1026 _private method_ `private void CheckRestrictedMode()`
- L1028-1114 _private method_ `private UhtCompilerDirective ParserConditional(UhtTokenBufferReader lineTokenReader)`
- L1116-1159 _private method_ `private UhtCompilerDirective ParserEngineVersionConditional(UhtToken define, bool notPresent, UhtTokenBufferReader lineTokenReader)`
- L1165-1171 _private method_ `private void PushCompilerDirective(UhtCompilerDirective compilerDirective)` — Add a new compiler directive to the stack
- L1176-1185 _private method_ `private UhtCompilerDirective PopCompilerDirective(UhtToken token)` — Remove the top level compiler directive from the stack
- L1187-1194 _private method_ `private bool IncludeCurrentCompilerDirective()`
- L1204-1233 _private method_ `private bool ClearCommentsCompilerDirective()` — The old UHT would preprocess the file and eliminate any #if blocks that were not required for any contextual information. This results in comments before the #if block being considered for the next definition. This routine classifies each #if block type into if comments should be purged after the directive.
- L1235-1259 _private method_ `private static bool IsRestrictedDirective(UhtCompilerDirective compilerDirective)`
- L1261-1272 _private method_ `private static bool SupportsElif(UhtCompilerDirective compilerDirective)`
- L1274-1285 _private method_ `private static void SkipVirtualAndAPI(IUhtTokenReader replayReader)`
- L1287-1399 _private method_ `private bool CheckForConstructor(UhtClass classObj, UhtDeclaration declaration)`
- L1401-1419 _private method_ `private bool CheckForDestructor(UhtClass classObj, UhtDeclaration declaration)`
- L1421-1500 _private* method_ `bool CheckForSerialize(UhtClass classObj, UhtDeclaration declaration)`
- L1502-1517 _private method_ `private bool CheckForBeginDestroy(UhtPartial partial, UhtDeclaration declaration)`

#### struct `EpicGames.UHT.Parsers.UhtHeaderFileParser.CompilerDirective`  
`private struct CompilerDirective`  
_private; L330-334_
- L332 _public field_ `public UhtCompilerDirective _element`
- L333 _public field_ `public UhtCompilerDirective _composite`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtInterfaceClassParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtInterfaceClassParser`  
`public static class UhtInterfaceClassParser`  
_public; L17-136_
- attrs: `[UnrealHeaderTool]`
- desc: Interface class parser
- L24-27 _private method_ `private static UhtParseResult UINTERFACEKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`
- L33-48 _private method_ `private static UhtParseResult GENERATED_UINTERFACE_BODYKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Interface)] [UhtKeyword(Extends = UhtTableNames.Interface, Keyword = "GENERATED_BODY")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method"`
- L51-135 _private method_ `private static UhtParseResult ParseUInterface(UhtParsingScope parentScope, ref UhtToken token)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtNamespaceParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtNamespaceParser`  
`sealed class UhtNamespaceParser`  
_internal*; L17-82_
- attrs: `[UnrealHeaderTool]`
- desc: namespace parser
- L22-25 _private method_ `private static UhtParseResult NamespaceKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global, Keyword = "namespace", DisableUsageError = true)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "`
- L27-43 _private method_ `private static int ParseNamespaceIdentifiers(UhtParsingScope topScope)`
- L45-81 _private method_ `private static UhtParseResult ParseNamespace(UhtParsingScope parentScope)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtNativeInterfaceClassParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtNativeInterfaceClassParser`  
`public static class UhtNativeInterfaceClassParser`  
_public; L17-147_
- attrs: `[UnrealHeaderTool]`
- desc: Parser object for native interfaces
- L24-38 _private method_ `private static UhtParseResult ClassKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global, Keyword = "class", DisableUsageError = true)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0`
- L44-60 _private method_ `private static UhtParseResult GENERATED_IINTERFACE_BODYKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.NativeInterface)] [UhtKeyword(Extends = UhtTableNames.NativeInterface, Keyword = "GENERATED_BODY")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute acce`
- L63-102 _private method_ `private static bool TryParseIInterface(UhtParsingScope parentScope, out UhtToken sourceName, out UhtToken[] superName)`
- L104-146 _private method_ `private static void ParseIInterface(UhtParsingScope parentScope, ref UhtToken token, UhtToken sourceName, UhtToken[] superName)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtParserHelpers.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Parsers.UhtInheritance`  
`public struct UhtInheritance`  
_public; L16-45_
- desc: Collection of parsed inheritance data
- L22 _public property_ `public UhtToken[] SuperIdentifier { get; set; }` — Super class identifier
- L27 _public property_ `public List<UhtToken[]> BaseIdentifiers { get; }` — Collection of other base identifiers
- L32 _public property_ `public List<UhtToken[]> VerseInterfaceIdentifiers { get; }` — Collection of verse interface identifiers
- L37 _public property_ `public int VerseInterfacesLine { get; set; }` — Line number that the VIDENTIFIER macro appeared
- L42-44 _public ctor_ `public UhtInheritance()` — Constructor

#### class `EpicGames.UHT.Parsers.UhtParserHelpers`  
`public static class UhtParserHelpers`  
_public; L50-139_
- desc: Collection of helper methods
- L59-106 _public method_ `public static void ParseInheritance(UhtHeaderFileParser headerFileParser, IUhtConfig config, out UhtInheritance inheritance)` — Parse the inheritance
- L114-138 _public method_ `public static void ParseCompileVersionDeclaration(IUhtTokenReader tokenReader, IUhtConfig config, UhtStruct structObj)` — Parse compiler version declaration

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtParsingScope.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtParsingScope`  
`public class UhtParsingScope : IDisposable`  
_public; L18-603_
- inherits: `IDisposable`
- desc: Nested structure of scopes being parsed
- L24 _public property_ `public UhtHeaderFileParser HeaderParser { get; }` — Header file parser
- L29 _public property_ `public UhtHeaderFile HeaderFile => ...` — Header file being parsed
- L34 _public property_ `public UhtModule Module => ...` — Module owning the header file
- L39 _public property_ `public IUhtTokenReader TokenReader { get; }` — Token reader
- L44 _public property_ `public UhtParsingScope? ParentScope { get; }` — Parent scope
- L49 _public property_ `public UhtType ScopeType { get; }` — Type being parsed.
- L54 _public property_ `public UhtKeywordTable ScopeKeywordTable { get; }` — Keyword table for the scope
- L59 _public property_ `public UhtAccessSpecifier AccessSpecifier { get; set; }` — Current access specifier
- L64 _public property_ `public UhtSession Session => ...` — Current session
- L69-84 _public property_ `public UhtParsingScope CurrentClassScope { get; }` — Return the current class scope being compiled
- L91-99 _public ctor_ `public UhtParsingScope(UhtHeaderFileParser headerParser, UhtKeywordTable keywordTable)` — Construct a root/global scope
- L108-117 _public ctor_ `public UhtParsingScope(UhtParsingScope parentScope, UhtType scopeType, UhtKeywordTable keywordTable, UhtAccessSpecifier accessSpecifier)` — Construct a scope for a type
- L122-126 _public method_ `public void Dispose()` — Dispose the scope
- L132-138 _protected method_ `protected virtual void Dispose(bool disposing)` — Virtual method for disposing the object
- L143-146 _public method_ `public void AddModuleRelativePathToMetaData()` — Add the module's relative path to the type's meta data
- L153-156 _public method_ `public static void AddModuleRelativePathToMetaData(UhtMetaData metaData, UhtHeaderFile headerFile)` — Add the module's relative path to the meta data
- L162-165 _public method_ `public void AddFormattedCommentsAsTooltipMetaData(int metaNameIndex = UhtMetaData.IndexNone)` — Format the current token reader comments and add it as meta data
- L172-222 _public method_ `public void AddFormattedCommentsAsTooltipMetaData(UhtType type, int metaNameIndex = UhtMetaData.IndexNone)` — Format the current token reader comments and add it as meta data
- L230-240 _private method_ `private static bool HasValidCommentChar(ReadOnlySpan<char> comments)` — Given a list of comments, check to see if any have alpha, numeric, or unicode code points with a value larger than 0xFF.
- L260-443 _private method_ `private static string FormatCommentForToolTip(string comments)` — Convert the given list of comments to a tooltip. Each string view is a comment where the // style comments also includes the trailing \r\n. The following style comments are supported: /* */ - C Style /** */ - C Style JavaDocs /*~ */ - C Style but ignore //\r\n - C++ Style ///\r\n - C++ Style JavaDocs //~\r\n - C++ Style bug ignore As per TokenReader, there will only be one C style comment ever present, and it will be the first one. When a C style comment is parsed, any prior comments are cleared. However, if a C++ style comment follows a C style comment (regardless of any intermediate blank lines), then both blocks of comments will be present. If any blank lines are encountered between blocks of C++ style comments, then any prior comments are cleared.
- L451-491 _private method_ `private static int RemoveIgnoreComments(char[] comments, int inLength)` — Remove any comments marked to be ignored
- L500-547 _private method_ `private static int RemoveBlockCommentMarkers(char[] comments, int inLength, bool javaDocStyle)` — Remove any block comment markers
- L555-602 _private method_ `private static int RemoveLineCommentMarkers(char[] comments, int inLength)` — Remove any line comment markers

#### struct `EpicGames.UHT.Parsers.UhtTokenRecorder`  
`public struct UhtTokenRecorder : IDisposable`  
_public; L608-682_
- inherits: `IDisposable`
- desc: Token recorder
- L610 _private field_ `private readonly UhtCompilerDirective _compilerDirective`
- L611 _private field_ `private readonly UhtParsingScope _scope`
- L612 _private field_ `private readonly UhtFunction? _function`
- L613 _private field_ `private bool _flushed`
- L620-631 _public ctor_ `public UhtTokenRecorder(UhtParsingScope scope, ref UhtToken initialToken)` — Construct a new recorder
- L638-648 _public ctor_ `public UhtTokenRecorder(UhtParsingScope scope, UhtFunction function)` — Create a new recorder
- L653-656 _public method_ `public void Dispose()` — Stop the recording
- L662-681 _public method_ `public bool Stop()` — Stop the recording

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtPartialParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtPartialParser`  
`public static class UhtPartialParser`  
_public; L15-134_
- attrs: `[UnrealHeaderTool]`
- desc: UPARTIAL parser object
- L21-24 _private method_ `private static UhtParseResult UPARTIALKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`
- L29-49 _private method_ `private static UhtParseResult GENERATED_BODYKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Partial)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification `
- L52-133 _private method_ `private static UhtParseResult ParseUPartial(UhtParsingScope parentScope, UhtToken keywordToken)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtPropertyParser.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Parsers.UhtPropertyParseOptions`  
`public enum UhtPropertyParseOptions`  
_public; L22-69_
- attrs: `[Flags]`
- desc: Options that customize the parsing of properties.
- L28 _public* enumerator_ `None = 0` — No options
- L33 _public* enumerator_ `NoAutoConst = 1 << 0` — Don't automatically mark properties as CPF_Const
- L38 _public* enumerator_ `ParseMacros = 1 << 1` — Parse for the property macros
- L43 _public* enumerator_ `FunctionNameIncluded = 1 << 2` — If set, then the name of the property will be parsed with the type
- L48 _public* enumerator_ `NameIncluded = 1 << 3` — If set, then the name of the property will be parsed with the type
- L53 _public* enumerator_ `CommaSeparatedName = 1 << 4` — When parsing delegates, the name is separated by commas
- L58 _public* enumerator_ `List = 1 << 5` — Multiple properties can be defined separated by commas
- L63 _public* enumerator_ `DontAddReturn = 1 << 6` — Don't add a return type to the property list (return values go at the end)
- L68 _public* enumerator_ `AddModuleRelativePath = 1 << 7` — If set, add the module relative path to the parameter's meta data

#### class `EpicGames.UHT.Parsers.UhtParsePropertyOptionsExtensions`  
`public static class UhtParsePropertyOptionsExtensions`  
_public; L75-111_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L84-87 _public method_ `public static bool HasAnyFlags(this UhtPropertyParseOptions inFlags, UhtPropertyParseOptions testFlags)` — Test to see if any of the specified flags are set
- L95-98 _public method_ `public static bool HasAllFlags(this UhtPropertyParseOptions inFlags, UhtPropertyParseOptions testFlags)` — Test to see if all of the specified flags are set
- L107-110 _public method_ `public static bool HasExactFlags(this UhtPropertyParseOptions inFlags, UhtPropertyParseOptions testFlags, UhtPropertyParseOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Parsers.UhtPropertyMacroType`  
`public enum UhtPropertyMacroType`  
_public; L116-163_
- desc: Macro type
- L122 _public* enumerator_ `None` — None found
- L127 _public* enumerator_ `LayoutArray` — Array
- L132 _public* enumerator_ `LayoutArrayEditorOnly` — Editor only array
- L137 _public* enumerator_ `LayoutBitfield` — Bit field
- L142 _public* enumerator_ `LayoutBitfieldEditorOnly` — Editor only bit field
- L147 _public* enumerator_ `LayoutField` — Field
- L152 _public* enumerator_ `LayoutFieldEditorOnly` — Editor only field
- L157 _public* enumerator_ `LayoutFieldInitialized` — Field with initializer
- L162 _public* enumerator_ `VerseField` — Verse property that isn't native

#### class `EpicGames.UHT.Parsers.UhtPropertyMacroTypeExtensions`  
`public static class UhtPropertyMacroTypeExtensions`  
_public; L168-263_
- desc: Extensions for working with the macro type
- L176 _public method_ `public static bool IsEditorOnly(this UhtPropertyMacroType propertyMacroType)` — Return true if the type is editor only
- L190 _public method_ `public static bool IsBitfield(this UhtPropertyMacroType propertyMacroType)` — Return true if the type is a bit field
- L203 _public method_ `public static bool IsArray(this UhtPropertyMacroType propertyMacroType)` — Return true if the type is an array
- L216 _public method_ `public static bool HasInitializer(this UhtPropertyMacroType propertyMacroType)` — Return true if the type has an initializer
- L229 _public method_ `public static bool IsVerseField(this UhtPropertyMacroType propertyMacroType)` — Return true if the type is a verse field and not native
- L242 _public method_ `public static StringView MacroName(this UhtPropertyMacroType propertyMacroType)` — Return the property macro name
- L261 _public method_ `public static KeyValuePair<StringView, UhtPropertyMacroType> MacroNameAndValue(this UhtPropertyMacroType propertyMacroType)` — Return the macro name and value

#### class `EpicGames.UHT.Parsers.UhtPropertySpecifierContext`  
`public class UhtPropertySpecifierContext : UhtSpecifierContext`  
_public; L277-303_
- inherits: `UhtSpecifierContext`
- desc: Context for property specifier parsing
- L282 _public property_ `public UhtPropertySettings PropertySettings { get; }` — The property settings being parsed
- L287 _public property_ `public bool SeenEditSpecifier { get; set; }` — If true, editor specifier seen
- L292 _public property_ `public bool SeenBlueprintWriteSpecifier { get; set; }` — If true, blueprint write specifier seen
- L297 _public property_ `public bool SeenBlueprintReadOnlySpecifier { get; set; }` — If true, blueprint readonly specifier seen
- L302 _public property_ `public bool SeenBlueprintGetterSpecifier { get; set; }` — If true, blueprint getter specifier seen

#### struct `EpicGames.UHT.Parsers.UhtThreadBorrower`  
`public readonly struct UhtThreadBorrower<T> : IDisposable where T : new()`  
_public; L308-342_
- inherits: `IDisposable`
- constraints: `where T : new()`
- desc: Helper class thread specified object cache
- L310 _private field_ `private static readonly ThreadLocal<List<T>> s_tls = new(() => [])`
- L311 _private field_ `private readonly T _instance`
- L316 _public property_ `public T Instance => ...` — The borrowed instance
- L321-333 _public ctor_ `public UhtThreadBorrower(bool _)` — Request a context
- L338-341 _public method_ `public void Dispose()` — Return the borrowed buffer to the cache

#### class `EpicGames.UHT.Parsers.UhtPreResolveProperty`  
`public class UhtPreResolveProperty : UhtProperty`  
_public; L348-414_
- inherits: `UhtProperty`
- desc: A parsed property is a property that was parsed but couldn't yet be resolved. It retains the list of tokens needed to resolve the type of the property. It will be replaced with the resolved property type during property resolution.
- L351 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L354 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L357 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L363-365 _public ctor_ `public UhtPreResolveProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property to be resolved
- L372-374 _public ctor_ `public UhtPreResolveProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L380-383 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L386-389 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L392-395 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L398-401 _public method_ `public override StringBuilder AppendFunctionThunkParameterGet(StringBuilder builder)` — (inheritdoc)
- L404-407 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L410-413 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)

#### record struct `EpicGames.UHT.Parsers.UhtPropertyCategoryExtraContext`  
`internal record struct UhtPropertyCategoryExtraContext(UhtPropertyCategory Category) : IUhtMessageExtraContext`  
_internal; L416-430_
- inherits: `IUhtMessageExtraContext`
- L420-428 _public property_ `public IEnumerable<object?>? MessageExtraContext { get; }` — (inheritdoc)

#### class `EpicGames.UHT.Parsers.UhtPropertyParser`  
`public static class UhtPropertyParser`  
_public; L435-1065_
- desc: Property parser
- L437 _private field_ `private static readonly Dictionary<StringView, UhtPropertyMacroType> s_macroTypes = ...`
- L437 _private field_ `private static readonly Dictionary< s_macroTypes = new( [ UhtPropertyMacroType.LayoutArray.MacroNameAndValue(), UhtPropertyMacroType.LayoutArrayEditorOnly.MacroNameAndValue(), UhtPropertyMacroType.LayoutBitfield.MacroNameAndValue(), UhtPropertyMacroTy ...`
- L458-478 _public method_ `public static void Parse(UhtParsingScope topScope, EPropertyFlags disallowPropertyFlags, UhtPropertyParseOptions options, UhtPropertyCategory category, UhtPropertyDelegate propertyDelegate)` — Parse the property
- L487-493 _private method_ `private static UhtProperty? ResolveProperty(UhtPropertyResolvePhase resolvePhase, UhtPropertySettings propertySettings)` — Resolve the given property. This method will resolve any immediate property during the parsing phase or resolve any previously parsed property to the final version.
- L495 _private field_ `private static readonly ThreadLocal<UhtPropertySettings> s_tlsPropertySettings = new(() => { return new UhtPropertySettings(); })`
- L502-533 _public method_ `public static void ResolveChildren(UhtType type, UhtPropertyParseOptions options)` — Given a type with children, resolve any children that couldn't be resolved during the parsing phase.
- L542-638 _public method_ `public static UhtProperty? ResolvePropertyType(UhtPropertyResolveArgs args, UhtPropertyType propertyType)` — Resolve the given property and finish parsing any postfix settings
- L640-822 _private method_ `private static void ParseInternal(UhtParsingScope topScope, UhtPropertyParseOptions options, UhtPropertySpecifierContext specifierContext, UhtPropertyDelegate propertyDelegate)`
- L831-914 _public method_ `public static void PreParseType(UhtPropertySpecifierContext specifierContext, bool isTemplateArgument)` — Parse the type elements excluding the type itself.
- L927-1026 _private method_ `private static UhtProperty Finalize(UhtParsingScope topScope, UhtPropertyParseOptions options, UhtPropertySpecifierContext specifierContext, ref UhtToken nameToken, UhtTypeTokens typeTokens, UhtPropertyMacroType propertyMacroType, UhtPropertyDelegate propertyDelegate)` — Finish creating the property
- L1028-1045 _private method_ `private static bool CheckForOptionalParts(IUhtTokenReader tokenReader, UhtPropertySettings propertySettings, ref UhtToken nameToken)`
- L1047-1054 _private method_ `private static void RequireBitfield(IUhtTokenReader tokenReader, UhtPropertySettings propertySettings, ref UhtToken nameToken)`
- L1056-1064 _private method_ `private static void RequireArray(IUhtTokenReader tokenReader, UhtPropertySettings propertySettings, ref UhtToken nameToken, char terminator)`

#### class `EpicGames.UHT.Parsers.PropertyKeywords`  
`static class PropertyKeywords`  
_internal*; L1068-1113_
- attrs: `[UnrealHeaderTool]`
- L1076-1094 _private method_ `private static UhtParseResult UPROPERTYKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Class)] [UhtKeyword(Extends = UhtTableNames.ScriptStruct)] [UhtKeyword(Extends = UhtTableNames.VModule)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute`
- L1097 _private field_ `private static readonly UhtPropertyDelegate s_propertyDelegate = PropertyParsed`
- L1099-1112 _private method_ `private static void PropertyParsed(UhtParsingScope topScope, UhtProperty property, ref UhtToken nameToken, UhtPropertyMacroType propertyMacroType)`

#### class `EpicGames.UHT.Parsers.UhtVerseTypeParser`  
`static class UhtVerseTypeParser`  
_internal*; L1116-1149_
- attrs: `[UnrealHeaderTool]`
- L1121-1124 _private method_ `private static UhtProperty? TValType(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TVal", Options = UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove`
- L1129-1132 _private method_ `private static UhtProperty? VerseTPtrType(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::TPtr", Options = UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060`
- L1137-1140 _private method_ `private static UhtProperty? VerseTaskType(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TVerseTask", Options = UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:`
- L1145-1148 _private method_ `private static UhtProperty? VerseTaskCall(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TVerseCall", Options = UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:`

#### class `EpicGames.UHT.Parsers.UhtDefaultPropertyParser`  
`static class UhtDefaultPropertyParser`  
_internal*; L1152-1291_
- attrs: `[UnrealHeaderTool]`
- L1157-1290 _private method_ `private static UhtProperty? DefaultProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Options = UhtPropertyTypeOptions.Default)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", `

#### Namespace-level symbols

- L272 _public delegate_ `public delegate void UhtPropertyDelegate(UhtParsingScope topScope, UhtProperty property, ref UhtToken nameToken, UhtPropertyMacroType propertyMacroType)` — Delegate invoked to handle a parsed property

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtScriptStructParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtScriptStructParser`  
`public static class UhtScriptStructParser`  
_public; L17-270_
- attrs: `[UnrealHeaderTool]`
- desc: USTRUCT parser object
- L24-27 _private method_ `private static UhtParseResult USTRUCTKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.Global)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`
- L33-53 _private method_ `private static UhtParseResult GENERATED_USTRUCT_BODYKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.ScriptStruct)] [UhtKeyword(Extends = UhtTableNames.ScriptStruct, Keyword = "GENERATED_BODY")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed m`
- L58-62 _private method_ `private static UhtParseResult RIGVM_METHODKeyword(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — attrs: `[UhtKeyword(Extends = UhtTableNames.ScriptStruct)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justifica`
- L65-160 _private method_ `private static UhtParseResult ParseUScriptStruct(UhtParsingScope parentScope, UhtToken keywordToken)`
- L162-269 _private method_ `private static void ParseRigVM(UhtParsingScope topScope)`

### `Source/Programs/Shared/EpicGames.UHT/Parsers/UhtSpecifierParser.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtSpecifierParser`  
`public class UhtSpecifierParser : IUhtMessageExtraContext`  
_public; L19-469_
- inherits: `IUhtMessageExtraContext`
- desc: Class responsible for parsing specifiers and the field meta data. To reduce allocations, one specifier parser is shared between all objects in a given header file. This makes the Action pattern being used a bit more obtuse, but it does help performance by reducing the allocations fairly significantly.
- L31 _private field_ `private static readonly ThreadLocal<UhtSpecifierParser?> s_tls = new(() => null)` — For a given header file, we share a common specifier parser to reduce the number of allocations. Before the parser can be reused, the ParseDeferred method must be called to dispatch that list.
- L33 _private field_ `private static readonly List<KeyValuePair<StringView, StringView>> s_emptyKVPValues = ...`
- L33 _private field_ `private static readonly List<KeyValuePair< s_emptyKVPValues = []`
- L35 _private field_ `private UhtSpecifierContext _specifierContext`
- L36 _private field_ `private IUhtTokenReader _tokenReader`
- L37 _private field_ `private UhtSpecifierTable _table`
- L38 _private field_ `private StringView _context`
- L39 _private field_ `private StringView _currentSpecifier = new()`
- L40 _private field_ `private List<DeferredSpecifier> _deferredSpecifiers = []`
- L41 _private field_ `private bool _isParsingFieldMetaData = false`
- L42 _private field_ `private List<KeyValuePair<StringView, StringView>>? _currentKVPValues = ...`
- L42 _private field_ `private List<KeyValuePair< _currentKVPValues = null`
- L43 _private field_ `private List<StringView>? _currentStringValues = null`
- L44 _private field_ `private int _umetaElementsParsed = 0`
- L46 _private field_ `private readonly Action _parseAction`
- L47 _private field_ `private readonly Action _parseFieldMetaDataAction`
- L48 _private field_ `private readonly Action _parseKVPValueAction`
- L49 _private field_ `private readonly Action _parseStringViewListAction`
- L58-69 _public method_ `public static UhtSpecifierParser GetThreadInstance(UhtSpecifierContext specifierContext, StringView context, UhtSpecifierTable table)` — Get the cached specifier parser
- L77-88 _public ctor_ `public UhtSpecifierParser(UhtSpecifierContext specifierContext, StringView context, UhtSpecifierTable table)` — Construct a new specifier parser
- L96-103 _public method_ `public void Reset(UhtSpecifierContext specifierContext, StringView context, UhtSpecifierTable table)` — Reset an existing parser to parse a new specifier block
- L109-117 _public method_ `public UhtSpecifierParser ParseSpecifiers()` — Perform the specifier parsing
- L123-139 _public method_ `public UhtSpecifierParser ParseFieldMetaData()` — Parse field meta data
- L144-151 _public method_ `public void ParseDeferred()` — Parse any deferred specifiers
- L156-172 _public property_ `public IEnumerable<object?>? MessageExtraContext { get; }` — (inheritdoc)
- L175-199 _private method_ `private void ParseInternal()`
- L201-219 _private method_ `private void ParseFieldMetaDataInternal()`
- L221-225 _private method_ `private void ParseKVPValueInternal()`
- L227-231 _private method_ `private void ParseStringViewListInternal()`
- L233-240 _private method_ `private void Dispatch(UhtSpecifier specifier, object? value)`
- L242-351 _private method_ `private bool TryParseValue(UhtSpecifierValueType valueType, out object? value)`
- L353-366 _private method_ `private KeyValuePair<StringView, StringView> ReadKVP()`
- L368-387 _private method_ `private List<StringView>? ReadValueList()`
- L389-397 _private method_ `private StringView ReadValue()`
- L406-468 _private method_ `private static bool ReadValue(IUhtTokenReader tokenReader, StringViewBuilder builder, bool respectQuotes)` — Parse the sequence of meta data

#### struct `EpicGames.UHT.Parsers.UhtSpecifierParser.DeferredSpecifier`  
`struct DeferredSpecifier`  
_private*; L21-25_
- L23 _public field_ `public UhtSpecifier _specifier`
- L24 _public field_ `public object? _value`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtClassSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtClassSpecifiers`  
`public static class UhtClassSpecifiers`  
_public; L17-366_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- desc: Collection of UCLASS specifiers
- L20-24 _private method_ `private static void NoExportSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L27-31 _private method_ `private static void IntrinsicSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L34-37 _private method_ `private static void ComponentWrapperClassSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L40-44 _private method_ `private static void WithinSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.SingleString)]`
- L47-51 _private method_ `private static void EditInlineNewSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L54-58 _private method_ `private static void NotEditInlineNewSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L61-65 _private method_ `private static void PlaceableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L68-72 _private method_ `private static void NotPlaceableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L75-79 _private method_ `private static void DefaultToInstancedSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L82-86 _private method_ `private static void HideDropdownSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L89-94 _private method_ `private static void HiddenSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L97-100 _private method_ `private static void DependsOnSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L103-107 _private method_ `private static void MinimalAPISpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L110-114 _private method_ `private static void ConstSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L117-121 _private method_ `private static void PartialSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L124-128 _private method_ `private static void PerObjectConfigSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L131-135 _private method_ `private static void PerPlatformConfigSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L138-142 _private method_ `private static void ConfigDoNotCheckDefaultsSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L145-149 _private method_ `private static void AbstractSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L152-156 _private method_ `private static void DeprecatedSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L159-163 _private method_ `private static void TransientSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L166-170 _private method_ `private static void NonTransientSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L173-178 _private method_ `private static void OptionalSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L181-186 _private method_ `private static void CustomConstructorSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L189-193 _private method_ `private static void ConfigSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.SingleString)]`
- L196-201 _private method_ `private static void DefaultConfigSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L204-209 _private method_ `private static void GlobalUserConfigSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L212-217 _private method_ `private static void ProjectUserConfigSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L220-223 _private method_ `private static void EditorConfigSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.SingleString)]`
- L226-230 _private method_ `private static void ShowCategoriesSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L233-237 _private method_ `private static void HideCategoriesSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L240-244 _private method_ `private static void ShowFunctionsSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L247-251 _private method_ `private static void HideFunctionsSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L254-258 _private method_ `private static void SparseClassDataTypesSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.SingleString)]`
- L261-268 _private method_ `private static void ClassGroupSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L271-276 _private method_ `private static void AutoExpandCategoriesSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L279-284 _private method_ `private static void AutoCollapseCategoriesSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L287-291 _private method_ `private static void PrioritizeCategoriesSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L294-298 _private method_ `private static void DontAutoCollapseCategoriesSpecifier(UhtSpecifierContext specifierContext, List<StringView> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.NonEmptyStringList)]`
- L301-306 _private method_ `private static void CollapseCategoriesSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L309-314 _private method_ `private static void DontCollapseCategoriesSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L317-322 _private method_ `private static void AdvancedClassDisplaySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L325-329 _private method_ `private static void ConversionRootSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L332-336 _private method_ `private static void NeedsDeferredDependencyLoadingSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L339-347 _private method_ `private static void MatchedSerializersSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L350-358 _private method_ `private static void InterfaceSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`
- L361-365 _private method_ `private static void CustomFieldNotifySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, ValueType = UhtSpecifierValueType.None)]`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtDefaultSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtDefaultSpecifiers`  
`public static class UhtDefaultSpecifiers`  
_public; L20-279_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "Attribute accessed method")]`
- desc: Collection of default specifiers that apply to everything
- L22-65 _private method_ `private static void SetMetaData(UhtSpecifierContext specifierContext, StringView key, StringView value)`
- L67-70 _private method_ `private static void SetMetaData(UhtSpecifierContext specifierContext, StringView key, bool value)`
- L74-80 _private method_ `private static void MetaSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.KeyValuePairList, When = UhtSpecifierWhen.Immediate)]`
- L83-86 _private method_ `private static void DisplayNameSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.String, When = UhtSpecifierWhen.Immediate)]`
- L89-92 _private method_ `private static void FriendlyNameSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.String, When = UhtSpecifierWhen.Immediate)]`
- L95-99 _private method_ `private static void BlueprintInternalUseOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L102-107 _private method_ `private static void BlueprintInternalUseOnlyHierarchicalSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L110-113 _private method_ `private static void BlueprintTypeSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L116-120 _private method_ `private static void NotBlueprintTypeSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L123-127 _private method_ `private static void BlueprintableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L130-133 _private method_ `private static void CallInEditorSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L136-140 _private method_ `private static void NotBlueprintableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L143-146 _private method_ `private static void CategorySpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.String, When = UhtSpecifierWhen.Immediate)]`
- L149-152 _private method_ `private static void ExperimentalSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L155-158 _private method_ `private static void EarlyAccessPreviewSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L161-164 _private method_ `private static void DocumentationPolicySpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.String, When = UhtSpecifierWhen.Immediate)]`
- L167-170 _private method_ `private static void SparseClassDataTypeSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.String, When = UhtSpecifierWhen.Immediate)]`
- L173-176 _private method_ `private static void StateStreamStaticStateSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L179-182 _private method_ `private static void StateStreamDynamicStateSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L185-188 _private method_ `private static void StateStreamHandleSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Default, ValueType = UhtSpecifierValueType.None, When = UhtSpecifierWhen.Immediate)]`
- L196-202 _private method_ `private static void ValidateNumeric(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Name = "UIMin", Extends = UhtTableNames.Default)] [UhtSpecifierValidator(Name = "UIMax", Extends = UhtTableNames.Default)] [UhtSpecifierValidator(Name = "ClampMin", Extends = UhtTableNames.Default)] [UhtSpecifierValid`
- L205-216 _private method_ `private static void DevelopmentStatusSpecifierValidator(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Extends = UhtTableNames.Default)]`
- L219-228 _private method_ `private static void DocumentationPolicySpecifierValidator(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Extends = UhtTableNames.Default)]`
- L231-246 _private method_ `private static void UnitsSpecifierValidator(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Extends = UhtTableNames.Default)]`
- L264-277 _private method_ `private static void LongPathNameMetaDataSpecifierValidator(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Name = "MustImplement", Extends = UhtTableNames.PropertyMember)] [UhtSpecifierValidator(Name = "ObjectMustImplement", Extends = UhtTableNames.PropertyMember)] [UhtSpecifierValidator(Name = "AllowedClasses", Extends = ` — Validator for metadata on various types which must be a long path name to another type/function/etc.

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtEnumSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtEnumSpecifiers`  
`public static class UhtEnumSpecifiers`  
_public; L17-32_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- desc: Collection of UENUM specifiers
- L20-24 _private method_ `private static void FlagsSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Enum, ValueType = UhtSpecifierValueType.None)]`
- L27-31 _private method_ `private static void MinimalAPISpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Enum, ValueType = UhtSpecifierValueType.None)]`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtFieldSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtFieldSpecifiers`  
`public static class UhtFieldSpecifiers`  
_public; L19-184_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- desc: Collection of UENUM specifiers
- L21-39 _private method_ `private static bool VerseCommonFieldKeys(UhtField fieldObj, StringView key, StringView value)`
- L41-74 _private method_ `private static void VerseCommonSpecifier(UhtField fieldObj, string what, List<KeyValuePair<StringView, StringView>> values, Func<StringView, StringView, bool> keyAndValueFunc)`
- L77-88 _private method_ `private static void VerseEnumSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Enum, Name = "Verse", ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L91-112 _private method_ `private static void VerseScriptStructSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, Name = "Verse", ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L115-136 _private method_ `private static void VerseClassSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Class, Name = "Verse", ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L139-150 _private method_ `private static void VerseInterfaceSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Interface, Name = "Verse", ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L153-164 _private method_ `private static void VerseNativeInterfaceSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.NativeInterface, Name = "Verse", ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L167-183 _private method_ `private static void VerseVModuleSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.VModule, Name = "Verse", ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtFunctionSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtFunctionSpecifiers`  
`public static class UhtFunctionSpecifiers`  
_public; L20-513_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "Attribute accessed method")]`
- desc: Collection of UFUNCTION/UDELEGATE specifiers
- L23-27 _private method_ `private static void BlueprintAuthorityOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L30-34 _private method_ `private static void BlueprintCallableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L37-41 _private method_ `private static void BlueprintCosmeticSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L44-57 _private method_ `private static void BlueprintGetterSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L60-85 _private method_ `private static void BlueprintImplementableEventSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L88-112 _private method_ `private static void BlueprintNativeEventSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L115-130 _private method_ `private static void BlueprintPureSpecifier(UhtSpecifierContext specifierContext, StringView? value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]`
- L133-145 _private method_ `private static void BlueprintSetterSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L148-169 _private method_ `private static void ClientSpecifier(UhtSpecifierContext specifierContext, StringView? value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]`
- L172-176 _private method_ `private static void CustomThunkSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L179-187 _private method_ `private static void ExecSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L190-200 _private method_ `private static void NetMulticastSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L203-207 _private method_ `private static void ReliableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L210-214 _private method_ `private static void SealedEventSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L217-238 _private method_ `private static void ServerSpecifier(UhtSpecifierContext specifierContext, StringView? value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]`
- L241-261 _private method_ `private static void RemoteSpecifier(UhtSpecifierContext specifierContext, StringView? value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]`
- L264-284 _private method_ `private static void ServiceRequestSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L287-307 _private method_ `private static void ServiceResponseSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L310-314 _private method_ `private static void UnreliableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L317-326 _private method_ `private static void WithValidationSpecifier(UhtSpecifierContext specifierContext, List<StringView>? value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.StringList)]`
- L329-333 _private method_ `private static void FieldNotifySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]`
- L336-360 _private method_ `private static void BlueprintProtectedSpecifierValidator(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Extends = UhtTableNames.Function)]`
- L363-373 _private method_ `private static void CommutativeAssociativeBinaryOperatorSpecifierValidator(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Extends = UhtTableNames.Function)]`
- L377-411 _private method_ `private static void ExpandsSpecifierValidator(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — attrs: `[UhtSpecifierValidator(Name = "ExpandBoolAsExecs", Extends = UhtTableNames.Function)] [UhtSpecifierValidator(Name = "ExpandEnumAsExecs", Extends = UhtTableNames.Function)]`
- L414-460 _private method_ `private static void VerseSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`
- L462-512 _private method_ `private static void ParseNetServiceIdentifiers(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> identifiers)`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtInterfaceClassSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtInterfaceClassSpecifiers`  
`sealed class UhtInterfaceClassSpecifiers`  
_internal*; L13-34_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- L16-19 _private method_ `private static void DependsOnSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Interface, ValueType = UhtSpecifierValueType.None)]`
- L22-26 _private method_ `private static void MinimalAPISpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Interface, ValueType = UhtSpecifierValueType.None)]`
- L29-33 _private method_ `private static void ConversionRootSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.Interface, ValueType = UhtSpecifierValueType.None)]`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyArgumentSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtPropertyArgumentSpecifiers`  
`public static class UhtPropertyArgumentSpecifiers`  
_public; L19-83_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- desc: Collection of property argument specifiers
- L23-27 _private method_ `private static void ConstSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyArgument, ValueType = UhtSpecifierValueType.None)]`
- L30-34 _private method_ `private static void RefSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyArgument, ValueType = UhtSpecifierValueType.None)]`
- L37-49 _private method_ `private static void NotReplicatedSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyArgument, ValueType = UhtSpecifierValueType.None)]`
- L52-56 _private method_ `private static void RequiredSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyArgument, ValueType = UhtSpecifierValueType.None)]`
- L59-80 _private method_ `private static void VerseSpecifier(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> values)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyArgument, ValueType = UhtSpecifierValueType.OptionalEqualsKeyValuePairList)]`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtPropertyMemberSpecifiers`  
`public static class UhtPropertyMemberSpecifiers`  
_public; L18-490_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- desc: Collection of property member specifiers
- L21-30 _private method_ `private static void EditAnywhereSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L33-42 _private method_ `private static void EditInstanceOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L45-54 _private method_ `private static void EditDefaultsOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L57-66 _private method_ `private static void VisibleAnywhereSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L69-78 _private method_ `private static void VisibleInstanceOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L81-90 _private method_ `private static void VisibleDefaultsOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L93-114 _private method_ `private static void BlueprintReadWriteSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L117-138 _private method_ `private static void BlueprintReadOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L141-158 _private method_ `private static void BlueprintSetterSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.SingleString)]`
- L161-173 _private method_ `private static void BlueprintGetterSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.SingleString)]`
- L176-180 _private method_ `private static void ConfigSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L183-187 _private method_ `private static void GlobalConfigSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L190-194 _private method_ `private static void LocalizedSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L197-201 _private method_ `private static void TransientSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L204-208 _private method_ `private static void DuplicateTransientSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L211-215 _private method_ `private static void TextExportTransientSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L218-223 _private method_ `private static void NonPIETransientSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L226-230 _private method_ `private static void NonPIEDuplicateTransientSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L233-237 _private method_ `private static void ExportSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L240-244 _private method_ `private static void EditInlineSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L247-251 _private method_ `private static void NoClearSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L254-258 _private method_ `private static void EditFixedSizeSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L261-269 _private method_ `private static void ReplicatedSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L272-287 _private method_ `private static void ReplicatedUsingSpecifier(UhtSpecifierContext specifierContext, StringView value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.SingleString)]`
- L290-298 _private method_ `private static void NotReplicatedSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L301-305 _private method_ `private static void RepRetrySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L308-312 _private method_ `private static void InterpSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L315-319 _private method_ `private static void NonTransactionalSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L322-327 _private method_ `private static void InstancedSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L330-334 _private method_ `private static void BlueprintAssignableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L337-341 _private method_ `private static void BlueprintCallableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L344-348 _private method_ `private static void BlueprintAuthorityOnlySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L351-355 _private method_ `private static void AssetRegistrySearchableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L358-362 _private method_ `private static void SimpleDisplaySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L365-369 _private method_ `private static void AdvancedDisplaySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L372-376 _private method_ `private static void SaveGameSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L379-383 _private method_ `private static void SkipSerializationSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L386-390 _private method_ `private static void ExperimentalOverridableLogicSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L393-397 _private method_ `private static void ExperimentalAlwaysOverridenSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L400-404 _private method_ `private static void ExperimentalNeverOverridenSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L407-415 _private method_ `private static void ExperimentalExternalObjectsSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L418-422 _private method_ `private static void ForcePostConstructLinkSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`
- L425-452 _private method_ `private static void GetterSpecifier(UhtSpecifierContext specifierContext, StringView? value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.OptionalString)]`
- L455-482 _private method_ `private static void SetterSpecifier(UhtSpecifierContext specifierContext, StringView? value)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.OptionalString)]`
- L485-489 _private method_ `private static void FieldNotifySpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]`

### `Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtScriptStructSpecifiers.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Parsers.UhtScriptStructSpecifiers`  
`public static class UhtScriptStructSpecifiers`  
_public; L16-91_
- attrs: `[UnrealHeaderTool] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- desc: Collection of USCRIPT specifiers
- L19-24 _private method_ `private static void NoExportSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)]`
- L27-31 _private method_ `private static void AtomicSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)]`
- L35-39 _private method_ `private static void ImmutableSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- L42-50 _private method_ `private static void HasDefaultsSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)]`
- L53-61 _private method_ `private static void HasNoOpConstructorSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)]`
- L64-72 _private method_ `private static void IsAlwaysAccessibleSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)]`
- L75-83 _private method_ `private static void IsCoreTypeSpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)]`
- L86-90 _private method_ `private static void MinimalAPISpecifier(UhtSpecifierContext specifierContext)` — attrs: `[UhtSpecifier(Extends = UhtTableNames.ScriptStruct, ValueType = UhtSpecifierValueType.None)]`

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtCodeGeneratorInjectorTable.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tables.UhtCodeGeneratorInjectionLocation`  
`public enum UhtCodeGeneratorInjectionLocation`  
_public; L14-24_
- desc: Location where code will be injected
- L19 _public* enumerator_ `Header` — Injection location will be in the generated.h after built-in code generation for the respective type
- L23 _public* enumerator_ `GeneratedMacro` — Injection location within the macros for the type.

#### class `EpicGames.UHT.Tables.UhtCodeGeneratorInjectorAttribute`  
`public sealed class UhtCodeGeneratorInjectorAttribute : Attribute`  
_public; L30-40_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = false)]`
- inherits: `Attribute`
- desc: Method attribute which defines a code generation injection behaviour.
- L35 _public property_ `public required Type UhtType { get; set; }` — The UhtType that the injector will be applied to.
- L39 _public property_ `public required UhtCodeGeneratorInjectionLocation Location { get; set; }` — Specifies the injection location for the injector to run in.

#### record struct `EpicGames.UHT.Tables.UhtCodeGeneratorInjectorDesire`  
`internal record struct UhtCodeGeneratorInjectorDesire(Type UhtType, UhtCodeGeneratorInjectionLocation Location)`  
_internal; L42-42_

#### class `EpicGames.UHT.Tables.UhtCodeGeneratorInjectorTable`  
`public sealed class UhtCodeGeneratorInjectorTable`  
_public; L52-150_
- desc: Holds a set of injectors discovered via reflection
- L54 _private field_ `private readonly Dictionary<UhtCodeGeneratorInjectorDesire, List<UhtCodeGeneratorInjectorDelegate>?> _injectorsTable = ...`
- L54 _private field_ `private readonly Dictionary< _injectorsTable = []`
- L55 _private field_ `private readonly List<Type> _supportedLeafTypes`
- L60-67 _public ctor_ `public UhtCodeGeneratorInjectorTable()` — Constructs UhtCodeGeneratorInjectorTable
- L69-95 _internal method_ `internal void Inject(StringBuilder builder, UhtType type, UhtCodeGeneratorInjectionLocation location)`
- L97-115 _internal method_ `internal void OnUhtCodeGeneratorInjectorAttribute(MethodInfo method, UhtCodeGeneratorInjectorAttribute attribute)`
- L117-149 _internal method_ `internal void Sort()`

#### Namespace-level symbols

- L47 _internal delegate_ `internal delegate void UhtCodeGeneratorInjectorDelegate(StringBuilder builder, UhtType type, int leadingTabs, string eolSequence)` — Entrypoint for code generation injector

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtEngineClassTable.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tables.UhtEngineClassAttribute`  
`public sealed class UhtEngineClassAttribute : Attribute`  
_public; L15-27_
- attrs: `[AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: This attribute is placed on classes that represent Unreal Engine classes.
- L21 _public property_ `public string? Name { get; set; }` — The name of the engine class excluding any prefix
- L26 _public property_ `public bool IsProperty { get; set; }` — If true, this class is a property

#### struct `EpicGames.UHT.Tables.UhtEngineClass`  
`public struct UhtEngineClass`  
_public; L32-43_
- desc: Represents an engine class in the engine class table
- L37 _public property_ `public string Name { get; set; }` — The name of the engine class excluding any prefix
- L42 _public property_ `public bool IsProperty { get; set; }` — If true, this class is a property

#### class `EpicGames.UHT.Tables.UhtEngineClassTable`  
`public class UhtEngineClassTable`  
_public; L48-81_
- desc: Table of all known engine class names.
- L53 _private field_ `private readonly Dictionary<StringView, UhtEngineClass> _engineClasses = ...` — Internal mapping from engine class name to information
- L53 _private field_ `private readonly Dictionary< _engineClasses = []` — Internal mapping from engine class name to information
- L60-67 _public method_ `public bool IsValidPropertyTypeName(StringView name)` — Test to see if the given class name is a property
- L73-80 _public method_ `public void OnEngineClassAttribute(UhtEngineClassAttribute engineClassAttribute)` — Add an entry to the table

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtExporterTable.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tables.UhtExporterOptions`  
`public enum UhtExporterOptions`  
_public; L22-42_
- attrs: `[Flags]`
- desc: Export options
- L28 _public* enumerator_ `None = 0` — No options
- L33 _public* enumerator_ `Default = 1 << 0` — The exporter should be run by default
- L41 _public* enumerator_ `CompileOutput = 1 << 1` — Generated CPP files that match any filter in the CppFilters property of this UhtExporter will be included in the compilation process. For this option, all custom generated files should be placed into the same folder as the default unreal generated files. Make sure the CppFilters property is set up properly and does not conflict with other exporters (including the default). Header files should be included as normal in code.

#### class `EpicGames.UHT.Tables.UhtExporterOptionsExtensions`  
`public static class UhtExporterOptionsExtensions`  
_public; L48-84_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L57-60 _public method_ `public static bool HasAnyFlags(this UhtExporterOptions inFlags, UhtExporterOptions testFlags)` — Test to see if any of the specified flags are set
- L68-71 _public method_ `public static bool HasAllFlags(this UhtExporterOptions inFlags, UhtExporterOptions testFlags)` — Test to see if all of the specified flags are set
- L80-83 _public method_ `public static bool HasExactFlags(this UhtExporterOptions inFlags, UhtExporterOptions testFlags, UhtExporterOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Tables.UhtExporterAttribute`  
`public sealed class UhtExporterAttribute : Attribute`  
_public; L90-127_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Defines an exporter
- L96 _public property_ `public string Name { get; set; }` — Name of the exporter
- L101 _public property_ `public string Description { get; set; }` — Description of the export. Used to display help
- L106 _public property_ `public string ModuleName { get; set; }` — Exporters in plugins need to specify a module name
- L111 _public property_ `public UhtExporterOptions Options { get; set; }` — Exporter options
- L116 _public property_ `public string[]? CppFilters { get; set; }` — Collection of filters used to delete old cpp files
- L121 _public property_ `public string[]? HeaderFilters { get; set; }` — Collection of filters used to delete old h files
- L126 _public property_ `public string[]? OtherFilters { get; set; }` — Collection of filters for other file types

#### struct `EpicGames.UHT.Tables.UhtExporter`  
`public readonly struct UhtExporter`  
_public; L132-191_
- desc: Defines an exporter in the table
- L138 _public property_ `public string Name { get; }` — Name of the exporter
- L143 _public property_ `public string Description { get; }` — Description of the export. Used to display help
- L148 _public property_ `public string ModuleName { get; }` — Exporters in plugins need to specify a module name
- L153 _public property_ `public UhtExporterOptions Options { get; }` — Exporter options
- L158 _public property_ `public UhtExporterDelegate Delegate { get; }` — Delegate to invoke to start export
- L163 _public property_ `public IReadOnlyList<string> CppFilters { get; }` — Collection of filters used to delete old cpp files
- L168 _public property_ `public IReadOnlyList<string> HeaderFilters { get; }` — Collection of filters used to delete old h files
- L173 _public property_ `public IReadOnlyList<string> OtherFilters { get; }` — Collection of filters for other file types
- L180-190 _public ctor_ `public UhtExporter(UhtExporterAttribute attribute, UhtExporterDelegate exporterDelegate)` — Construct an exporter table instance

#### class `EpicGames.UHT.Tables.UhtExporterTable`  
`public class UhtExporterTable : IEnumerable<UhtExporter>`  
_public; L196-261_
- inherits: `IEnumerable<UhtExporter>`
- desc: Exporter table
- L199 _private field_ `private readonly Dictionary<string, UhtExporter> _exporterValues = ...`
- L199 _private field_ `private readonly Dictionary< _exporterValues = new(StringComparer.OrdinalIgnoreCase)`
- L207-210 _public method_ `public bool TryGet(string name, out UhtExporter value)` — Return the exporter associated with the given name
- L219-236 _public method_ `public void OnExporterAttribute(Type type, MethodInfo methodInfo, UhtExporterAttribute exporterAttribute)` — Handle an exporter attribute
- L242-248 _public method_ `public IEnumerator<UhtExporter> GetEnumerator()` — Return an enumerator for all the defined exporters
- L254-260 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — Return an enumerator for all the defined exporters

#### Namespace-level symbols

- L16 _public delegate_ `public delegate void UhtExporterDelegate(IUhtExportFactory factory)` — Delegate to invoke to run exporter

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtKeywordTable.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tables.UhtKeywordAttribute`  
`public sealed class UhtKeywordAttribute : Attribute`  
_public; L18-50_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Invoke the given method when the keyword is parsed.
- L24 _public property_ `public string? Extends { get; set; }` — Keyword table/scope being extended
- L29 _public property_ `public string? Keyword { get; set; }` — Name of the keyword
- L34 _public property_ `public string? AllowText { get; set; }` — Text to be displayed to the user when referencing this keyword
- L39 _public property_ `public bool AllScopes { get; set; }` — If true, this applies to all scopes
- L44 _public property_ `public bool DisableUsageError { get; set; }` — If true, do not include in usage errors
- L49 _public property_ `public UhtCompilerDirective AllowedCompilerDirectives { get; set; }` — List of the allowed compiler directives.

#### class `EpicGames.UHT.Tables.UhtKeywordCatchAllAttribute`  
`public sealed class UhtKeywordCatchAllAttribute : Attribute`  
_public; L56-63_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Invoked as a last chance processor for a keyword
- L62 _public property_ `public string? Extends { get; set; }` — Table/scope to be extended

#### struct `EpicGames.UHT.Tables.UhtKeyword`  
`public readonly struct UhtKeyword`  
_public; L85-143_
- desc: Defines a keyword
- L91 _public property_ `public string Name { get; }` — Name of the keyword
- L96 _public property_ `public UhtKeywordDelegate Delegate { get; }` — Delegate to invoke
- L101 _public property_ `public string? AllowText { get; }` — Text to be displayed to the user when referencing this keyword
- L106 _public property_ `public bool AllScopes { get; }` — If true, this applies to all scopes
- L111 _public property_ `public bool DisableUsageError { get; }` — If true, do not include in usage errors
- L116 _public property_ `public UhtCompilerDirective AllowedCompilerDirectives { get; }` — List of the allowed compiler directives.
- L124-142 _public ctor_ `public UhtKeyword(string name, UhtKeywordDelegate keywordDelegate, UhtKeywordAttribute? attribute)` — Construct a new keyword

#### class `EpicGames.UHT.Tables.UhtKeywordTable`  
`public class UhtKeywordTable : UhtLookupTable<UhtKeyword>`  
_public; L148-192_
- inherits: `UhtLookupTable<UhtKeyword>`
- desc: Keyword table for a specific scope
- L154 _public property_ `public List<UhtKeywordCatchAllDelegate> CatchAlls { get; }` — List of catch-alls associated with this table
- L159-161 _public ctor_ `public UhtKeywordTable() : base(StringViewComparer.Ordinal)` — Construct a new keyword table
- L167-171 _public method_ `public UhtKeywordTable Add(UhtKeyword value)` — Add the given value to the lookup table. It will throw an exception if it is a duplicate.
- L177-181 _public method_ `public UhtKeywordTable AddCatchAll(UhtKeywordCatchAllDelegate catchAll)` — Add the given catch-all to the table.
- L187-191 _public method_ `public override void Merge(UhtLookupTableBase baseTable)` — Merge the given keyword table. Duplicates in the BaseTypeTable will be ignored.

#### class `EpicGames.UHT.Tables.UhtKeywordTables`  
`public class UhtKeywordTables : UhtLookupTables<UhtKeywordTable>`  
_public; L197-287_
- inherits: `UhtLookupTables<UhtKeywordTable>`
- desc: Table of all keyword tables
- L203-205 _public ctor_ `public UhtKeywordTables() : base("keywords")` — Construct the keyword tables
- L214-223 _public method_ `public void OnKeywordCatchAllAttribute(Type type, MethodInfo methodInfo, UhtKeywordCatchAllAttribute keywordCatchAllAttribute)` — Handle a keyword attribute
- L232-243 _public method_ `public void OnKeywordAttribute(Type type, MethodInfo methodInfo, UhtKeywordAttribute keywordAttribute)` — Handle a keyword attribute
- L250-286 _public method_ `public void LogUnhandledError(IUhtMessageSite messageSite, UhtToken token)` — Log an unhandled error

#### Namespace-level symbols

- L72 _public delegate_ `public delegate UhtParseResult UhtKeywordDelegate(UhtParsingScope topScope, UhtParsingScope actionScope, ref UhtToken token)` — Delegate to notify a keyword was parsed
- L80 _public delegate_ `public delegate UhtParseResult UhtKeywordCatchAllDelegate(UhtParsingScope topScope, ref UhtToken token)` — Delegate to invoke as a last chance processor for a keyword

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtLocTextDefaultValueTable.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tables.UhtLocTextDefaultValueAttribute`  
`public sealed class UhtLocTextDefaultValueAttribute : Attribute`  
_public; L29-36_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Attribute defining the loctext sanitizer
- L35 _public property_ `public string? Name { get; set; }` — Name of the sanitizer (i.e. LOCTEXT, NSLOCTEXT, ...)

#### struct `EpicGames.UHT.Tables.UhtLocTextDefaultValue`  
`public struct UhtLocTextDefaultValue`  
_public; L41-47_
- desc: Loctext sanitizer
- L46 _public property_ `public UhtLocTextDefaultValueDelegate Delegate { get; set; }` — Delegate to invoke

#### class `EpicGames.UHT.Tables.UhtLocTextDefaultValueTable`  
`public class UhtLocTextDefaultValueTable`  
_public; L52-88_
- desc: Table of loctext sanitizers
- L55 _private field_ `private readonly Dictionary<StringView, UhtLocTextDefaultValue> _locTextDefaultValues = ...`
- L55 _private field_ `private readonly Dictionary< _locTextDefaultValues = []`
- L63-66 _public method_ `public bool TryGet(StringView name, out UhtLocTextDefaultValue locTextDefaultValue)` — Return the loc text default value associated with the given name
- L74-87 _public method_ `public void OnLocTextDefaultValueAttribute(MethodInfo methodInfo, UhtLocTextDefaultValueAttribute locTextDefaultValueAttribute)` — Handle a loctext default value attribute

#### Namespace-level symbols

- L23 _public delegate_ `public delegate bool UhtLocTextDefaultValueDelegate(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — Delegate to invoke to sanitize a loctext default value

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtPropertyTypeTable.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tables.UhtPropertyTypeOptions`  
`public enum UhtPropertyTypeOptions`  
_public; L17-45_
- attrs: `[Flags]`
- desc: Property type options
- L23 _public* enumerator_ `None = 0` — No options
- L29 _public* enumerator_ `Simple = 1 << 0` — Simple property type with just the property type. (i.e. "int32 MyValue") Simple types are not required to parse the supplied token list.
- L34 _public* enumerator_ `CaseInsensitive = 1 << 1` — Use case insensitive string compares
- L39 _public* enumerator_ `Default = 1 << 2` — This property type is to be invoked when there are no keyword matches found
- L44 _public* enumerator_ `Immediate = 1 << 3` — This property type doesn't reference any engine types an can be resolved immediately

#### class `EpicGames.UHT.Tables.UhtPropertyTypeOptionsExtensions`  
`public static class UhtPropertyTypeOptionsExtensions`  
_public; L51-87_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L60-63 _public method_ `public static bool HasAnyFlags(this UhtPropertyTypeOptions inFlags, UhtPropertyTypeOptions testFlags)` — Test to see if any of the specified flags are set
- L71-74 _public method_ `public static bool HasAllFlags(this UhtPropertyTypeOptions inFlags, UhtPropertyTypeOptions testFlags)` — Test to see if all of the specified flags are set
- L83-86 _public method_ `public static bool HasExactFlags(this UhtPropertyTypeOptions inFlags, UhtPropertyTypeOptions testFlags, UhtPropertyTypeOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Tables.UhtPropertyTypeAttribute`  
`public sealed class UhtPropertyTypeAttribute : Attribute`  
_public; L100-112_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Property type attribute
- L106 _public property_ `public string? Keyword { get; set; }` — The expected keyword. Must be set unless this is the default processor
- L111 _public property_ `public UhtPropertyTypeOptions Options { get; set; }` — Options

#### struct `EpicGames.UHT.Tables.UhtPropertyType`  
`public struct UhtPropertyType`  
_public; L117-129_
- desc: Represents a property type as specified by the PropertyTypeAttribute
- L123 _public property_ `public UhtResolvePropertyDelegate Delegate { get; set; }` — Delegate to invoke
- L128 _public property_ `public UhtPropertyTypeOptions Options { get; set; }` — Options

#### class `EpicGames.UHT.Tables.UhtPropertyTypeTable`  
`public class UhtPropertyTypeTable`  
_public; L134-207_
- desc: Property type table
- L136 _private field_ `private readonly Dictionary<StringView, UhtPropertyType> _caseSensitive = ...`
- L136 _private field_ `private readonly Dictionary< _caseSensitive = []`
- L137 _private field_ `private readonly Dictionary<StringView, UhtPropertyType> _caseInsensitive = ...`
- L137 _private field_ `private readonly Dictionary< _caseInsensitive = new(StringViewComparer.OrdinalIgnoreCase)`
- L138 _private field_ `private UhtPropertyType? _default = null`
- L143-153 _public property_ `public UhtPropertyType Default { get; }` — Return the default processor
- L161-166 _public method_ `public bool TryGet(StringView name, out UhtPropertyType propertyType)` — Return the property type associated with the given name
- L174-206 _public method_ `public void OnPropertyTypeAttribute(MethodInfo methodInfo, UhtPropertyTypeAttribute propertyTypeAttribute)` — Handle a property type attribute

#### Namespace-level symbols

- L94 _public delegate_ `public delegate UhtProperty? UhtResolvePropertyDelegate(UhtPropertyResolveArgs args)` — Delegate invoked to resolve a tokenized type into a UHTProperty type

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtSpecifierTable.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tables.UhtSpecifierValueType`  
`public enum UhtSpecifierValueType`  
_public; L18-70_
- desc: Defines the different types specifiers relating to their allowed values
- L23 _public* enumerator_ `NotSet` — Internal value used to detect if the attribute has a valid value
- L28 _public* enumerator_ `None` — No values of any type are allowed
- L33 _public* enumerator_ `String` — A string value but can not be in the form of a list (i.e. =(bob))
- L38 _public* enumerator_ `OptionalString` — An optional string value but can not be in the form of a list
- L43 _public* enumerator_ `SingleString` — A string value or a single element string list
- L48 _public* enumerator_ `KeyValuePairList` — A list of values in key=value pairs
- L53 _public* enumerator_ `OptionalEqualsKeyValuePairList` — A list of values in key=value pairs but the equals is optional
- L58 _public* enumerator_ `StringList` — A list of values.
- L63 _public* enumerator_ `NonEmptyStringList` — A list of values and must contain at least one entry
- L69 _public* enumerator_ `Legacy` — attrs: `[Obsolete("Legacy specifier mode is obsolete, please use None")]` — Accepts a string list but the value is ignored by the specifier and is automatically deferred. This is for legacy UHT support.

#### enum `EpicGames.UHT.Tables.UhtSpecifierDispatchResults`  
`public enum UhtSpecifierDispatchResults`  
_public; L75-87_
- desc: Results from dispatching a specifier
- L81 _public* enumerator_ `Known` — Specifier was known and parsed
- L86 _public* enumerator_ `Unknown` — Specified was unknown

#### class `EpicGames.UHT.Tables.UhtSpecifierContext`  
`public class UhtSpecifierContext`  
_public; L92-153_
- desc: The specifier context provides the default and simplest information about the specifiers being processed
- L94 _private field_ `private UhtType? _type = null`
- L95 _private field_ `private IUhtTokenReader? _tokenReader = null`
- L96 _private field_ `private IUhtMessageSite? _messageSite = null`
- L97 _private field_ `private UhtMetaData? _metaData = null`
- L103 _public property_ `public UhtType Type { get; set; }` — Get the type containing the specifiers. For properties, this is the outer object and not the property itself.
- L108 _public property_ `public IUhtTokenReader TokenReader { get; set; }` — Return the currently active token reader
- L113 _public property_ `public UhtAccessSpecifier AccessSpecifier { get; set; }` — Current access specifier
- L118 _public property_ `public IUhtMessageSite MessageSite { get; set; }` — Message site for messages
- L123 _public property_ `public UhtMetaData MetaData { get; set; }` — Meta data currently being parsed.
- L128 _public property_ `public int MetaNameIndex { get; set; }` — Make data key index utilized by enumeration values
- L137-145 _public ctor_ `public UhtSpecifierContext(UhtParsingScope scope, IUhtMessageSite messageSite, UhtMetaData metaData, int metaNameIndex = UhtMetaData.IndexNone)` — Construct a new specifier context
- L150-152 _public ctor_ `public UhtSpecifierContext()` — Construct an empty context. Scope, MessageSite, and MetaData must be set at a later point

#### enum `EpicGames.UHT.Tables.UhtSpecifierWhen`  
`public enum UhtSpecifierWhen`  
_public; L158-169_
- desc: Specifiers are either processed immediately when the declaration is parse or deferred until later in the parsing of the object
- L163 _public* enumerator_ `Immediate` — Specifier is parsed when the meta data section is parsed.
- L168 _public* enumerator_ `Deferred` — Specifier is executed after more of the object is parsed (but usually before members are parsed)

#### class `EpicGames.UHT.Tables.UhtSpecifier`  
`public abstract class UhtSpecifier`  
_public; L175-200_
- desc: The specifier table contains an instance of UhtSpecifier which is used to dispatch the parsing of a specifier to the implementation
- L181 _public property_ `public string Name { get; set; }` — Name of the specifier
- L186 _public property_ `public UhtSpecifierValueType ValueType { get; set; }` — Expected value type
- L191 _public property_ `public UhtSpecifierWhen When { get; set; }` — When is the specifier executed
- L199 _public method_ `public abstract UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — Dispatch an instance of the specifier

#### class `EpicGames.UHT.Tables.UhtSpecifierNone`  
`public class UhtSpecifierNone : UhtSpecifier`  
_public; L211-235_
- inherits: `UhtSpecifier`
- desc: Specifier with no value
- L213 _private field_ `private readonly UhtSpecifierNoneDelegate _delegate`
- L221-227 _public ctor_ `public UhtSpecifierNone(string name, UhtSpecifierWhen when, UhtSpecifierNoneDelegate specifierDelegate)` — Construct the specifier
- L230-234 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierString`  
`public class UhtSpecifierString : UhtSpecifier`  
_public; L247-275_
- inherits: `UhtSpecifier`
- desc: Specifier with a string value
- L249 _private field_ `private readonly UhtSpecifierStringDelegate _delegate`
- L257-263 _public ctor_ `public UhtSpecifierString(string name, UhtSpecifierWhen when, UhtSpecifierStringDelegate specifierDelegate)` — Construct the specifier
- L266-274 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierOptionalString`  
`public class UhtSpecifierOptionalString : UhtSpecifier`  
_public; L287-311_
- inherits: `UhtSpecifier`
- desc: Specifier with an optional string value
- L289 _private field_ `private readonly UhtSpecifierOptionalStringDelegate _delegate`
- L297-303 _public ctor_ `public UhtSpecifierOptionalString(string name, UhtSpecifierWhen when, UhtSpecifierOptionalStringDelegate specifierDelegate)` — Construct the specifier
- L306-310 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierSingleString`  
`public class UhtSpecifierSingleString : UhtSpecifier`  
_public; L323-351_
- inherits: `UhtSpecifier`
- desc: Specifier with a string value
- L325 _private field_ `private readonly UhtSpecifierSingleStringDelegate _delegate`
- L333-339 _public ctor_ `public UhtSpecifierSingleString(string name, UhtSpecifierWhen when, UhtSpecifierSingleStringDelegate specifierDelegate)` — Construct the specifier
- L342-350 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierKeyValuePairList`  
`public class UhtSpecifierKeyValuePairList : UhtSpecifier`  
_public; L363-392_
- inherits: `UhtSpecifier`
- desc: Specifier with list of string keys and values
- L365 _private field_ `private readonly UhtSpecifierKeyValuePairListDelegate _delegate`
- L374-380 _public ctor_ `public UhtSpecifierKeyValuePairList(string name, UhtSpecifierWhen when, bool equalsOptional, UhtSpecifierKeyValuePairListDelegate specifierDelegate)` — Construct the specifier
- L383-391 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierLegacy`  
`public class UhtSpecifierLegacy : UhtSpecifier`  
_public; L404-431_
- inherits: `UhtSpecifier`
- desc: Specifier delegate for legacy UHT specifiers with no value. Will generate a information/deprecation message is a value is supplied
- L406 _private field_ `private readonly UhtSpecifierLegacyDelegate _delegate`
- L413-419 _public ctor_ `public UhtSpecifierLegacy(string name, UhtSpecifierLegacyDelegate specifierDelegate)` — Construct the specifier
- L422-430 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierStringList`  
`public class UhtSpecifierStringList : UhtSpecifier`  
_public; L443-467_
- inherits: `UhtSpecifier`
- desc: Specifier with an optional string list
- L445 _private field_ `private readonly UhtSpecifierStringListDelegate _delegate`
- L453-459 _public ctor_ `public UhtSpecifierStringList(string name, UhtSpecifierWhen when, UhtSpecifierStringListDelegate specifierDelegate)` — Construct the specifier
- L462-466 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierNonEmptyStringList`  
`public class UhtSpecifierNonEmptyStringList : UhtSpecifier`  
_public; L479-507_
- inherits: `UhtSpecifier`
- desc: Specifier with a list of string views
- L481 _private field_ `private readonly UhtSpecifierNonEmptyStringListDelegate _delegate`
- L489-495 _public ctor_ `public UhtSpecifierNonEmptyStringList(string name, UhtSpecifierWhen when, UhtSpecifierNonEmptyStringListDelegate specifierDelegate)` — Construct the specifier
- L498-506 _public method_ `public override UhtSpecifierDispatchResults Dispatch(UhtSpecifierContext specifierContext, object? value)` — (inheritdoc)

#### class `EpicGames.UHT.Tables.UhtSpecifierAttribute`  
`public sealed class UhtSpecifierAttribute : Attribute`  
_public; L513-534_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Defines a specifier method
- L518 _public property_ `public string? Name { get; set; }` — Name of the specifier. If not supplied, the method name must end in "Specifier" and the name will be the method name with "Specifier" stripped.
- L523 _public property_ `public string? Extends { get; set; }` — Name of the table/scope this specifier applies
- L528 _public property_ `public UhtSpecifierValueType ValueType { get; set; }` — Value type of the specifier
- L533 _public property_ `public UhtSpecifierWhen When { get; set; }` — When the specifier is dispatched

#### class `EpicGames.UHT.Tables.UhtSpecifierTable`  
`public class UhtSpecifierTable : UhtLookupTable<UhtSpecifier>`  
_public; L539-558_
- inherits: `UhtLookupTable<UhtSpecifier>`
- desc: Collection of specifiers for a given scope
- L545-547 _public ctor_ `public UhtSpecifierTable() : base(StringViewComparer.OrdinalIgnoreCase)` — Construct a new specifier table
- L553-557 _public method_ `public UhtSpecifierTable Add(UhtSpecifier specifier)` — Add the given value to the lookup table. It will throw an exception if it is a duplicate.

#### class `EpicGames.UHT.Tables.UhtSpecifierTables`  
`public class UhtSpecifierTables : UhtLookupTables<UhtSpecifierTable>`  
_public; L563-631_
- inherits: `UhtLookupTables<UhtSpecifierTable>`
- desc: Collection of all specifier tables
- L569-571 _public ctor_ `public UhtSpecifierTables() : base("specifiers")` — Construct the specifier table
- L580-630 _public method_ `public void OnSpecifierAttribute(Type type, MethodInfo methodInfo, UhtSpecifierAttribute specifierAttribute)` — Invoke for a method that has the specifier attribute

#### Namespace-level symbols

- L206 _public delegate_ `public delegate void UhtSpecifierNoneDelegate(UhtSpecifierContext specifierContext)` — Delegate for a specifier with no value
- L242 _public delegate_ `public delegate void UhtSpecifierStringDelegate(UhtSpecifierContext specifierContext, StringView value)` — Specifier delegate with a string value
- L282 _public delegate_ `public delegate void UhtSpecifierOptionalStringDelegate(UhtSpecifierContext specifierContext, StringView? value)` — Specifier delegate with an optional string value
- L318 _public delegate_ `public delegate void UhtSpecifierSingleStringDelegate(UhtSpecifierContext specifierContext, StringView value)` — Specifier delegate with a string value
- L358 _public delegate_ `public delegate void UhtSpecifierKeyValuePairListDelegate(UhtSpecifierContext specifierContext, List<KeyValuePair<StringView, StringView>> value)` — Specifier delegate with list of string keys and values
- L398 _public delegate_ `public delegate void UhtSpecifierLegacyDelegate(UhtSpecifierContext specifierContext)` — Specifier delegate with no value
- L438 _public delegate_ `public delegate void UhtSpecifierStringListDelegate(UhtSpecifierContext specifierContext, List<StringView>? value)` — Specifier delegate with an optional string list
- L474 _public delegate_ `public delegate void UhtSpecifierNonEmptyStringListDelegate(UhtSpecifierContext specifierContext, List<StringView> value)` — Specifier delegate with a list of string views

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtSpecifierValidatorTable.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tables.UhtSpecifierValidator`  
`public class UhtSpecifierValidator`  
_public; L24-47_
- desc: Defines a specifier validated created from the attribute
- L30 _public property_ `public string Name { get; set; }` — Name of the validator
- L35 _public property_ `public UhtSpecifierValidatorDelegate Delegate { get; set; }` — Delegate for the validator
- L42-46 _public ctor_ `public UhtSpecifierValidator(string name, UhtSpecifierValidatorDelegate specifierValidatorDelegate)` — Construct a new instance

#### class `EpicGames.UHT.Tables.UhtSpecifierValidatorAttribute`  
`public sealed class UhtSpecifierValidatorAttribute : Attribute`  
_public; L53-65_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Attribute used to create a specifier validator
- L59 _public property_ `public string? Name { get; set; }` — Name of the validator. If not supplied &quot;SpecifierValidator&quot; will be removed from the end of the method name
- L64 _public property_ `public string? Extends { get; set; }` — Name of the table/scope for the validator

#### class `EpicGames.UHT.Tables.UhtSpecifierValidatorTable`  
`public class UhtSpecifierValidatorTable : UhtLookupTable<UhtSpecifierValidator>`  
_public; L70-89_
- inherits: `UhtLookupTable<UhtSpecifierValidator>`
- desc: A table for validators for a given scope
- L76-78 _public ctor_ `public UhtSpecifierValidatorTable() : base(StringViewComparer.OrdinalIgnoreCase)` — Construct a new specifier table
- L84-88 _public method_ `public UhtSpecifierValidatorTable Add(UhtSpecifierValidator specifier)` — Add the given value to the lookup table. It will throw an exception if it is a duplicate.

#### class `EpicGames.UHT.Tables.UhtSpecifierValidatorTables`  
`public class UhtSpecifierValidatorTables : UhtLookupTables<UhtSpecifierValidatorTable>`  
_public; L94-122_
- inherits: `UhtLookupTables<UhtSpecifierValidatorTable>`
- desc: Collection of specifier validators
- L100-102 _public ctor_ `public UhtSpecifierValidatorTables() : base("specifier validators")` — Construct the validator tables
- L111-121 _public method_ `public void OnSpecifierValidatorAttribute(Type type, MethodInfo methodInfo, UhtSpecifierValidatorAttribute specifierValidatorAttribute)` — Handle the attribute appearing on a method

#### Namespace-level symbols

- L19 _public delegate_ `public delegate void UhtSpecifierValidatorDelegate(UhtType type, UhtMetaData metaData, UhtMetaDataKey key, StringView value)` — Delegate used to validate a specifier

### `Source/Programs/Shared/EpicGames.UHT/Tables/UhtStructDefaultValueTable.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tables.UhtStructDefaultValueOptions`  
`public enum UhtStructDefaultValueOptions`  
_public; L28-40_
- attrs: `[Flags]`
- desc: Options for structure default value sanitizer
- L34 _public* enumerator_ `None = 0` — No options
- L39 _public* enumerator_ `Default = 1 << 2` — This method is to be invoked when there are no keyword matches found

#### class `EpicGames.UHT.Tables.UhtStructDefaultValueOptionsExtensions`  
`public static class UhtStructDefaultValueOptionsExtensions`  
_public; L46-82_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L55-58 _public method_ `public static bool HasAnyFlags(this UhtStructDefaultValueOptions inFlags, UhtStructDefaultValueOptions testFlags)` — Test to see if any of the specified flags are set
- L66-69 _public method_ `public static bool HasAllFlags(this UhtStructDefaultValueOptions inFlags, UhtStructDefaultValueOptions testFlags)` — Test to see if all of the specified flags are set
- L78-81 _public method_ `public static bool HasExactFlags(this UhtStructDefaultValueOptions inFlags, UhtStructDefaultValueOptions testFlags, UhtStructDefaultValueOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Tables.UhtStructDefaultValueAttribute`  
`public sealed class UhtStructDefaultValueAttribute : Attribute`  
_public; L88-100_
- attrs: `[AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Structure default value sanitizer attribute
- L94 _public property_ `public string? Name { get; set; }` — Name of the structure. Not required for default processor.
- L99 _public property_ `public UhtStructDefaultValueOptions Options { get; set; }` — Options

#### struct `EpicGames.UHT.Tables.UhtStructDefaultValue`  
`public struct UhtStructDefaultValue`  
_public; L105-112_
- desc: Structure default value sanitizer
- L111 _public property_ `public UhtStructDefaultValueDelegate Delegate { get; set; }` — The delegate to invoke

#### class `EpicGames.UHT.Tables.UhtStructDefaultValueTable`  
`public class UhtStructDefaultValueTable`  
_public; L117-179_
- desc: Table of all structure default value specifiers
- L119 _private field_ `private readonly Dictionary<StringView, UhtStructDefaultValue> _structDefaultValues = ...`
- L119 _private field_ `private readonly Dictionary< _structDefaultValues = []`
- L120 _private field_ `private UhtStructDefaultValue? _default = null`
- L125-135 _public property_ `public UhtStructDefaultValue Default { get; }` — Fetch the default sanitizer
- L143-146 _public method_ `public bool TryGet(StringView name, out UhtStructDefaultValue structDefaultValue)` — Return the structure default value associated with the given name
- L154-178 _public method_ `public void OnStructDefaultValueAttribute(MethodInfo methodInfo, UhtStructDefaultValueAttribute structDefaultValueAttribute)` — Handle a structure default value sanitizer attribute

#### Namespace-level symbols

- L22 _public delegate_ `public delegate bool UhtStructDefaultValueDelegate(UhtStructProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — Delegate for invoking structure default value sanitizer

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtToken.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tokenizer.UhtTokenType`  
`public enum UhtTokenType`  
_public; L16-78_
- desc: Type of the token
- L22 _public* enumerator_ `EndOfFile` — End of file token.
- L27 _public* enumerator_ `EndOfDefault` — End of default value.
- L32 _public* enumerator_ `EndOfType` — End of type
- L37 _public* enumerator_ `EndOfDeclaration` — End of declaration
- L42 _public* enumerator_ `Line` — Line of text (when calling GetLine only)
- L47 _public* enumerator_ `Identifier` — Alphanumeric identifier.
- L52 _public* enumerator_ `Symbol` — Symbol.
- L57 _public* enumerator_ `FloatConst` — Floating point constant
- L62 _public* enumerator_ `DecimalConst` — Decimal Integer constant
- L67 _public* enumerator_ `HexConst` — Hex integer constant
- L72 _public* enumerator_ `CharConst` — Single character constant
- L77 _public* enumerator_ `StringConst` — String constant

#### class `EpicGames.UHT.Tokenizer.UhtTokenTypeExtensions`  
`public static class UhtTokenTypeExtensions`  
_public; L83-104_
- desc: Series of extension methods for the token type
- L91-103 _public method_ `public static bool IsEndType(this UhtTokenType tokenType)` — Return true if the token type is an end type

#### struct `EpicGames.UHT.Tokenizer.UhtToken`  
`public struct UhtToken`  
_public; L109-793_
- desc: Token declaration
- L115 _public const_ `public const int MaxNameLength = 1024` — Names/Identifiers can not be longer that the following
- L120 _public const_ `public const int MaxStringLength = 1024` — Strings can not be longer than the following.
- L125 _public property_ `public UhtTokenType TokenType { get; set; }` — Type of the token
- L130 _public property_ `public int UngetPos { get; set; }` — Position to restore the reader
- L135 _public property_ `public int UngetLine { get; set; }` — Line to restore the reader
- L140 _public property_ `public int InputStartPos { get; set; }` — Starting position of the token value
- L145 _public property_ `public readonly int InputEndPos => ...` — End position of the token value
- L150 _public property_ `public int InputLine { get; set; }` — Line containing the token
- L155 _public property_ `public StringView Value { get; set; }` — Token value
- L160 _public property_ `public bool IsInHeader { get; set; }` — If true, this token is part of the header input stream
- L166-175 _public ctor_ `public UhtToken(UhtTokenType tokenType)` — Construct a new token
- L187-196 _public ctor_ `public UhtToken(UhtTokenType tokenType, int ungetPos, int ungetLine, int inputStartPos, int inputLine, StringView value, bool isInHeader = true)` — Construct a new token
- L202-219 _public ctor_ `public UhtToken(UhtInputCacheReader reader)` — Construct a type from the cache
- L225-239 _public method_ `public readonly void Write(UhtInputCacheWriter writer)` — Write the output type
- L245-248 _public operator_ `public static implicit operator bool(UhtToken token)` — True if the token isn't an end token
- L254-257 _public method_ `public readonly bool IsEndType()` — Return true if the token is an end token
- L264-267 _public method_ `public readonly bool IsValue(char value)` — Test to see if the value matches the given character
- L275-278 _public method_ `public readonly bool IsValue(string value, bool ignoreCase = false)` — Test to see if the value matches the given string
- L286-289 _public method_ `public readonly bool IsValue(StringView value, bool ignoreCase = false)` — Test to see if the value matches the given string
- L297-300 _public method_ `public readonly bool ValueStartsWith(string value, bool ignoreCase = false)` — Test to see if the value starts with the given string
- L306-309 _public method_ `public readonly bool IsIdentifier()` — Return true if the token is an identifier
- L317-320 _public method_ `public readonly bool IsIdentifier(string identifier, bool ignoreCase = false)` — Return true if the identifier matches
- L328-331 _public method_ `public readonly bool IsIdentifier(StringView identifier, bool ignoreCase = false)` — Return true if the identifier matches
- L337-340 _public method_ `public readonly bool IsSymbol()` — Return true if the token is a symbol
- L347-350 _public method_ `public readonly bool IsSymbol(char symbol)` — Return true if the symbol matches
- L357-360 _public method_ `public readonly bool IsSymbol(string symbol)` — Return true if the symbol matches
- L367-370 _public method_ `public readonly bool IsSymbol(StringView symbol)` — Return true if the symbol matches
- L376-379 _public method_ `public readonly bool IsConstInt()` — Return true if the token is a constant integer
- L385-388 _public method_ `public readonly bool IsConstFloat()` — Return true if the token is a constant floag
- L395-415 _public method_ `public readonly bool GetConstInt(out int value)` — Get the integer value of the token. Only supported for decimal, hexadecimal, and floating point values
- L422-442 _public method_ `public readonly bool GetConstLong(out long value)` — Get the integer value of the token. Only supported for decimal, hexadecimal, and floating point values
- L449-466 _public method_ `public readonly bool GetConstFloat(out float value)` — Get the float value of the token. Only supported for decimal, hexadecimal, and floating point values
- L473-490 _public method_ `public readonly bool GetConstDouble(out double value)` — Get the double value of the token. Only supported for decimal, hexadecimal, and floating point values
- L496-499 _public method_ `public readonly bool IsConstString()` — Return true if the token is a constant string (or a char constant)
- L509-559 _public method_ `public readonly StringView GetUnescapedString(IUhtMessageSite messageSite)` — Return an un-escaped string. The surrounding quotes will be removed and escaped characters will be converted to the actual values.
- L566-582 _public method_ `public readonly StringView GetConstantValue(bool respectQuotes = false)` — Return a string representation of the token value. This will convert numeric values and format them.
- L589-655 _public method_ `public readonly StringView GetTokenString(bool respectQuotes = false)` — Return an un-escaped string. The surrounding quotes will be removed and escaped characters will be converted to the actual values.
- L662-670 _public method_ `public static string Join(IEnumerable<UhtToken> tokens)` — Join the given tokens into a string
- L678-695 _public method_ `public static string Join(char separator, IEnumerable<UhtToken> tokens)` — Join the given tokens into a string
- L703-720 _public method_ `public static string Join(string separator, IEnumerable<UhtToken> tokens)` — Join the given tokens into a string
- L726-736 _public method_ `public override readonly string ToString()` — Convert the token to a string. This will be the value.
- L738 _private const_ `private const NumberStyles DefaultNumberStyles = NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite | NumberStyles.AllowLeadingSign | NumberStyles.AllowDecimalPoint | NumberStyles.AllowThousands | NumberStyles.AllowExponent`
- L741-751 _private method_ `private readonly float GetFloatValue()`
- L753-763 _private method_ `private readonly double GetDoubleValue()`
- L765-787 _private* method_ `readonly long GetDecimalValue()`
- L789-792 _private* method_ `readonly long GetHexValue()`

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenBufferReader.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenBufferReader`  
`public sealed class UhtTokenBufferReader : IUhtTokenReader, IUhtMessageLineNumber`  
_public; L14-1047_
- inherits: `IUhtTokenReader, IUhtMessageLineNumber`
- desc: Token reader for source buffers
- L16 _private field_ `private static readonly StringView[] s_emptyComments = []`
- L18 _private field_ `private readonly IUhtMessageSite _messageSite`
- L19 _private field_ `private List<StringView>? _comments = null`
- L20 _private field_ `private readonly List<UhtToken> _recordedTokens = []`
- L21 _private field_ `private IUhtTokenPreprocessor? _tokenPreprocessor = null`
- L22 _private field_ `private UhtToken _currentToken = new()`
- L23 _private field_ `private readonly ReadOnlyMemory<char> _data`
- L24 _private field_ `private int _prevPos = 0`
- L25 _private field_ `private int _prevLine = 1`
- L26 _private field_ `private bool _hasToken = false`
- L27 _private field_ `private int _preCurrentTokenInputPos = 0`
- L28 _private field_ `private int _preCurrentTokenInputLine = 1`
- L29 _private field_ `private int _inputPos = 0`
- L30 _private field_ `private int _inputLine = 1`
- L31 _private field_ `private int _commentsDisableCount = 0`
- L32 _private field_ `private int _committedComments = 0`
- L33 _private field_ `private List<StringView>? _savedComments = null`
- L34 _private field_ `private int _savedInputPos = 0`
- L35 _private field_ `private int _savedInputLine = 0`
- L36 _private field_ `private bool _hasSavedState = false`
- L37 _private field_ `private bool _recordTokens = false`
- L38 _private field_ `private int _preprocessorPendingCommentsCount = 0`
- L45-49 _public ctor_ `public UhtTokenBufferReader(IUhtMessageSite messageSite, ReadOnlyMemory<char> input)` — Construct a new token reader
- L52 _private* property_ `IUhtMessageSession IUhtMessageSite.MessageSession => ...`
- L53 _private* property_ `IUhtMessageSource? IUhtMessageSite.MessageSource => ...`
- L54 _private* property_ `IUhtMessageLineNumber? IUhtMessageSite.MessageLineNumber => ...`
- L58 _private* property_ `int IUhtMessageLineNumber.MessageLineNumber => ...`
- L63-76 _public property_ `public bool IsEOF { get; }` — (inheritdoc)
- L79 _public property_ `public int InputPos => ...` — (inheritdoc)
- L82-90 _public property_ `public int InputLine { get; set; }` — (inheritdoc)
- L93-106 _public property_ `public ReadOnlySpan<StringView> Comments { get; }` — (inheritdoc)
- L109 _public property_ `public IUhtTokenPreprocessor? TokenPreprocessor { get; set; }` — (inheritdoc)
- L112-120 _public method_ `public ref UhtToken PeekToken()` — (inheritdoc)
- L123-130 _public method_ `public void SkipWhitespaceAndComments()` — (inheritdoc)
- L133-153 _public method_ `public void ConsumeToken()` — (inheritdoc)
- L156-161 _public method_ `public UhtToken GetToken()` — (inheritdoc)
- L164-167 _public method_ `public int GetReplayTokenIndex()` — (inheritdoc)
- L170-247 _public method_ `public StringView GetRawString(char terminator, UhtRawStringOptions options)` — (inheritdoc)
- L250-286 _public method_ `public UhtToken GetLine()` — (inheritdoc)
- L289-292 _public method_ `public StringView GetStringView(int startPos, int count)` — (inheritdoc)
- L295-304 _public method_ `public void ClearComments()` — (inheritdoc)
- L307-310 _public method_ `public void DisableComments()` — (inheritdoc)
- L313-316 _public method_ `public void EnableComments()` — (inheritdoc)
- L319-325 _public method_ `public void CommitPendingComments()` — (inheritdoc)
- L328-331 _public method_ `public bool IsFirstTokenInLine(ref UhtToken token)` — (inheritdoc)
- L334-350 _public method_ `public void SaveState()` — (inheritdoc)
- L353-369 _public method_ `public void RestoreState()` — (inheritdoc)
- L372-380 _public method_ `public void AbandonState()` — (inheritdoc)
- L383-390 _public method_ `public void EnableRecording()` — (inheritdoc)
- L393-400 _public method_ `public void RecordToken(ref UhtToken token)` — (inheritdoc)
- L403-411 _public method_ `public void DisableRecording()` — (inheritdoc)
- L414-424 _public property_ `public List<UhtToken> RecordedTokens { get; }` — (inheritdoc)
- L428-435 _private method_ `private void ClearAllComments()`
- L437-444 _private method_ `private void ClearPendingComments()`
- L446-463 _private method_ `private static bool IsFirstTokenInLine(ReadOnlySpan<char> span, int startPos)`
- L469-830 _private method_ `private UhtToken GetTokenInternal(bool enablePreprocessor)` — Get the next token
- L835-944 _private method_ `private void SkipWhitespaceAndCommentsInternal(ref bool persistGotInlineComment, bool enablePreprocessor)` — Skip all leading whitespace and collect any comments
- L946-1000 _private method_ `private bool IsNumeric(ReadOnlySpan<char> span, char c)`
- L1008-1011 _private method_ `private char InternalPeekChar(ReadOnlySpan<char> span)` — Fetch the next character in the input stream or zero if we have reached the end. The current offset in the buffer is not advanced. The method does not support UTF-8
- L1019-1022 _private method_ `private char InternalGetChar(ReadOnlySpan<char> span)` — Fetch the next character in the input stream or zero if we have reached the end. The current offset in the buffer is advanced. The method does not support UTF-8.
- L1027-1039 _private method_ `private void ClearToken()` — If we have a current token, then reset the pending comments and input position back to before the token.
- L1041-1045 _private method_ `private void AddComment(StringView comment)`

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReader.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tokenizer.UhtRawStringOptions`  
`public enum UhtRawStringOptions`  
_public; L17-34_
- attrs: `[Flags]`
- desc: Options for GetRawString method
- L23 _public* enumerator_ `None` — No options
- L28 _public* enumerator_ `RespectQuotes = 1 << 0` — Don't consider the terminator while in a quoted string
- L33 _public* enumerator_ `DontConsumeTerminator = 1 << 1` — Don't consume the terminator. It will be parsed later.

#### class `EpicGames.UHT.Tokenizer.UhtRawStringOptionsExtensions`  
`public static class UhtRawStringOptionsExtensions`  
_public; L40-76_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L49-52 _public method_ `public static bool HasAnyFlags(this UhtRawStringOptions inFlags, UhtRawStringOptions testFlags)` — Test to see if any of the specified flags are set
- L60-63 _public method_ `public static bool HasAllFlags(this UhtRawStringOptions inFlags, UhtRawStringOptions testFlags)` — Test to see if all of the specified flags are set
- L72-75 _public method_ `public static bool HasExactFlags(this UhtRawStringOptions inFlags, UhtRawStringOptions testFlags, UhtRawStringOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### interface `EpicGames.UHT.Tokenizer.IUhtTokenPreprocessor`  
`public interface IUhtTokenPreprocessor`  
_public; L81-103_
- desc: Interface invoked when the parser reaches a '#' preprocessor block
- L92 _public method_ `public bool ParsePreprocessorDirective(ref UhtToken token, bool isBeingIncluded, out bool clearComments, out bool illegalContentsCheck)` — Parse a preprocessor directive
- L97 _public method_ `public void SaveState()` — Save the current preprocessor state
- L102 _public method_ `public void RestoreState()` — Restore the current preprocessor state

#### interface `EpicGames.UHT.Tokenizer.IUhtTokenReader`  
`public interface IUhtTokenReader : IUhtMessageSite`  
_public; L108-253_
- inherits: `IUhtMessageSite`
- desc: Common token reader interfaces for all token reader. When creating extension methods, use the interface.
- L113 _public property_ `public bool IsEOF { get; }` — True if the reader is at the end of the stream
- L118 _public property_ `public int InputPos { get; }` — Current input position in the stream by characters
- L123 _public property_ `public int InputLine { get; set; }` — Current input line in the stream
- L128 _public property_ `public IUhtTokenPreprocessor? TokenPreprocessor { get; set; }` — Preprocessor attached to the token reader
- L135 _public method_ `public ref UhtToken PeekToken()` — If the reader doesn't have a current token, then read the next token and return a reference to it. Otherwise return a reference to the current token.
- L140 _public method_ `public void ConsumeToken()` — Mark the current token as being consumed. Any call to PeekToken or GetToken will read another token.
- L146 _public method_ `public UhtToken GetToken()` — Get the next token in the data. If there is a current token, then that token is returned and marked as consumed.
- L152 _public method_ `public int GetReplayTokenIndex()` — Method only implemented by the replay reader that returns the current token index
- L159 _public method_ `public bool IsFirstTokenInLine(ref UhtToken token)` — Tests to see if the given token is the first token of a line
- L164 _public method_ `public void SkipWhitespaceAndComments()` — Skip any whitespace and comments at the current buffer position
- L170 _public method_ `public UhtToken GetLine()` — Read the entire next line in the buffer
- L178 _public method_ `public StringView GetStringView(int startPos, int count)` — Get a view of the buffer being read
- L186 _public method_ `public StringView GetRawString(char terminator, UhtRawStringOptions options)` — Return a string terminated by the given character.
- L192 _public property_ `public ReadOnlySpan<StringView> Comments { get; }` — The current collection of parsed comments. This does not include any comments parsed as part of a call to PeekToken unless ConsumeToken has been invoked after a call to PeekToken.
- L198 _public method_ `public void ClearComments()` — Clear the current collection of comments. Any comments parsed by PeekToken prior to calling ConsomeToken will not be cleared.
- L204 _public method_ `public void DisableComments()` — Disable the processing of comments. This is often done when skipping a bulk of the buffer.
- L209 _public method_ `public void EnableComments()` — Enable comment collection.
- L215 _public method_ `public void CommitPendingComments()`
- L221 _public method_ `public void SaveState()` — Save the current parsing state. There is a limited number of states that can be saved. Invoke either RestoreState or AbandonState after calling SaveState.
- L226 _public method_ `public void RestoreState()` — Restore a previously saved state.
- L231 _public method_ `public void AbandonState()` — Abandon a previously saved state
- L236 _public method_ `public void EnableRecording()` — Enable the recording of tokens
- L241 _public method_ `public void DisableRecording()` — Disable the recording of tokens. Any currently recorded tokens will be removed
- L247 _public method_ `public void RecordToken(ref UhtToken token)` — Record the given token to the list of recorded tokens
- L252 _public property_ `public List<UhtToken> RecordedTokens { get; }` — Get the current collection of recorded tokens

#### class `EpicGames.UHT.Tokenizer.UhtTokenList`  
`public class UhtTokenList`  
_public; L258-354_
- desc: Represents a list of tokens. Follow the Next chain for each element in the list.
- L264 _public property_ `public UhtToken Token { get; set; }` — The token
- L269 _public property_ `public UhtTokenList? Next { get; set; }` — The next token in the list
- L274-285 _public property_ `public UhtTokenList Last { get; }` — Return the last token list entry
- L293-303 _public method_ `public void Join(StringBuilder builder, string separator = "")` — Join the tokens in the list
- L310-319 _public method_ `public string Join(string separator = "")` — Join the tokens in the list
- L325-331 _public method_ `public void RedirectTypeIdentifier(IUhtConfig config)` — Remap the last identifier
- L337-353 _public method_ `public UhtToken[] ToArray()` — Return the token list as an array

#### class `EpicGames.UHT.Tokenizer.UhtTokenListCache`  
`public static class UhtTokenListCache`  
_public; L359-402_
- desc: Token list cache. Token lists must be returned to the cache.
- L361 _private field_ `private static readonly ThreadLocal<UhtTokenList?> s_tls = new(() => null)`
- L368-382 _public method_ `public static UhtTokenList Borrow(UhtToken token)` — Borrow a token list
- L388-401 _public method_ `public static void Return(UhtTokenList identifier)` — Return a token list to the cache

#### struct `EpicGames.UHT.Tokenizer.UhtTokenDisableComments`  
`public readonly struct UhtTokenDisableComments : IDisposable`  
_public; L444-465_
- inherits: `IDisposable`
- desc: Helper struct to disable comment parsing. Should be used in a using block
- L446 _private field_ `private readonly IUhtTokenReader _tokenReader`
- L452-456 _public ctor_ `public UhtTokenDisableComments(IUhtTokenReader tokenReader)` — Construct instance
- L461-464 _public method_ `public void Dispose()` — Enable comments

#### struct `EpicGames.UHT.Tokenizer.UhtTokenSaveState`  
`public struct UhtTokenSaveState : IDisposable`  
_public; L470-524_
- inherits: `IDisposable`
- desc: Helper struct to save token reader state
- L472 _private field_ `private readonly IUhtTokenReader _tokenReader`
- L473 _private field_ `private bool _handled`
- L479-484 _public ctor_ `public UhtTokenSaveState(IUhtTokenReader tokenReader)` — Construct instance
- L489-495 _public method_ `public void Dispose()` — Restore the token reader state
- L501-509 _public method_ `public void RestoreState()` — Restore the token reader state
- L515-523 _public method_ `public void AbandonState()` — Abandon the saved state

#### Namespace-level symbols

- L408 _public delegate_ `public delegate void UhtTokenDelegate(ref UhtToken token)` — Delegate for when a token is parsed
- L415 _public delegate_ `public delegate bool UhtTokensUntilDelegate(ref UhtToken token)` — Delegate for when a token is parsed in an until block
- L421 _public delegate_ `public delegate void UhtTokensDelegate(IEnumerable<UhtToken> tokens)` — Delegate for an enumeration of tokens
- L427 _public delegate_ `public delegate void UhtTokenListDelegate(UhtTokenList tokenList)` — Delegate for cached token list
- L433 _public delegate_ `public delegate void UhtTokenConstFloatDelegate(float value)` — Delegate for a constant float
- L439 _public delegate_ `public delegate void UhtTokenConstDoubleDelegate(double value)` — Delegate for a constant double

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderFloatExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderFloatExtensions`  
`public static class UhtTokenReaderFloatExtensions`  
_public; L11-181_
- desc: Collection of token reader extensions for float values
- L19-29 _public method_ `public static bool TryOptionalConstFloat(this IUhtTokenReader tokenReader, out float value)` — Get the next token as a float. If the next token is not a float, no token is consumed.
- L36-40 _public method_ `public static IUhtTokenReader OptionalConstFloat(this IUhtTokenReader tokenReader)` — Get the next token as a float. If the next token is not a float, no token is consumed.
- L48-55 _public method_ `public static IUhtTokenReader OptionalConstFloat(this IUhtTokenReader tokenReader, UhtTokenConstFloatDelegate floatDelegate)` — Get the next token as a float. If the next token is not a float, no token is consumed.
- L63-70 _public method_ `public static IUhtTokenReader RequireConstFloat(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as a float. If the next token is not a float, an exception is thrown
- L78-85 _public method_ `public static float GetConstFloat(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as a float. If the next token is not a float, an exception is thrown
- L93-102 _public method_ `public static bool TryOptionalLeadingSignConstFloat(this IUhtTokenReader tokenReader, out float value)` — Get the next float. It also handles [+/-] token followed by an float.
- L110-119 _public method_ `public static bool TryOptionalConstFloatExpression(this IUhtTokenReader tokenReader, out float value)` — Get the next float. It also handles [+/-] token followed by an float.
- L126-133 _public method_ `public static float GetConstFloatExpression(this IUhtTokenReader tokenReader)` — Get the next float. It also handles [+/-] token followed by an float.
- L141-150 _public method_ `public static bool TryOptionalConstDoubleExpression(this IUhtTokenReader tokenReader, out double value)` — Get the next double. It also handles [+/-] token followed by an double.
- L158-166 _public method_ `public static IUhtTokenReader RequireConstDoubleExpression(this IUhtTokenReader tokenReader, UhtTokenConstDoubleDelegate doubleDelegate)` — Get the next double. It also handles [+/-] token followed by an double.
- L173-180 _public method_ `public static double GetConstDoubleExpression(this IUhtTokenReader tokenReader)` — Get the next double. It also handles [+/-] token followed by an double.

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderFlowControlExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderFlowControlExtensions`  
`public static class UhtTokenReaderFlowControlExtensions`  
_public; L13-384_
- desc: Collection of token reader extensions to help with flow control
- L26-34 _public method_ `public static bool TryOptionalList(this IUhtTokenReader tokenReader, char initiator, char terminator, char separator, bool allowTrailingSeparator, Action action)` — Parse an optional list
- L46-49 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char initiator, char terminator, char separator, bool allowTrailingSeparator, Action action)` — Parse a required list
- L62-66 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char initiator, char terminator, char separator, bool allowTrailingSeparator, object? exceptionContext, Action action)` — Parse a required list
- L77-80 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char terminator, char separator, bool allowTrailingSeparator, Action action)` — Parse a required list. Initiating token must have already been parsed
- L92-130 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char terminator, char separator, bool allowTrailingSeparator, object? exceptionContext, Action action)` — Parse a required list. Initiating token must have already been parsed
- L142-150 _public method_ `public static bool TryOptionalList(this IUhtTokenReader tokenReader, char initiator, char terminator, char separator, bool allowTrailingSeparator, UhtTokensDelegate tokensDelegate)` — Parse an optional list
- L162-165 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char initiator, char terminator, char separator, bool allowTrailingSeparator, UhtTokensDelegate tokensDelegate)` — Parse a required list
- L178-182 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char initiator, char terminator, char separator, bool allowTrailingSeparator, object? exceptionContext, UhtTokensDelegate tokensDelegate)` — Parse a required list
- L193-196 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char terminator, char separator, bool allowTrailingSeparator, UhtTokensDelegate tokensDelegate)` — Parse a required list. Initiating token must have already been parsed
- L208-255 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char terminator, char separator, bool allowTrailingSeparator, object? exceptionContext, UhtTokensDelegate tokensDelegate)` — Parse a required list. Initiating token must have already been parsed
- L265-289 _public method_ `public static IUhtTokenReader RequireList(this IUhtTokenReader tokenReader, char initiator, char terminator, object? exceptionContext = null)` — Consume a block of tokens bounded by the two given symbols.
- L298-305 _public method_ `public static IUhtTokenReader While(this IUhtTokenReader tokenReader, string text, Action action)` — Invoke action while the next token is the given string
- L314-321 _public method_ `public static IUhtTokenReader While(this IUhtTokenReader tokenReader, char text, Action action)` — Invoke action while the next token is the given string
- L329-346 _public method_ `public static int ConsumeUntil(this IUhtTokenReader tokenReader, string[] terminators)` — Consume tokens until one of the strings are found. Terminating token will not be consumed.
- L354-365 _public method_ `public static IUhtTokenReader ConsumeUntil(this IUhtTokenReader tokenReader, char terminator)` — Consume until the given terminator is found. Terminating token will be consumed
- L375-383 _public method_ `public static IUhtTokenReader ExceptionIf(this IUhtTokenReader tokenReader, string candidate, string message)` — Throw an exception if the given symbol is found in the token stream

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderGeneralExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderGeneralExtensions`  
`public static class UhtTokenReaderGeneralExtensions`  
_public; L14-494_
- desc: Collection of general token reader extensions
- L23-32 _public method_ `public static bool TryOptional(this IUhtTokenReader tokenReader, string text)` — Try to parse the given text
- L40-49 _public method_ `public static bool TryOptional(this IUhtTokenReader tokenReader, StringView text)` — Try to parse the given text
- L57-61 _public method_ `public static bool TryPeekOptional(this IUhtTokenReader tokenReader, string text)` — Try to parse the given text. However, the matching token will not be consumed.
- L69-78 _public method_ `public static bool TryOptional(this IUhtTokenReader tokenReader, char text)` — Try to parse the given text
- L87-98 _public method_ `public static bool TryOptional(this IUhtTokenReader tokenReader, char text, out UhtToken outToken)` — Try to parse the given text
- L106-110 _public method_ `public static bool TryPeekOptional(this IUhtTokenReader tokenReader, char text)` — Try to parse the given text. However, the matching token will not be consumed.
- L118-126 _public method_ `public static IUhtTokenReader Optional(this IUhtTokenReader tokenReader, string text)` — Parse optional text
- L135-144 _public method_ `public static IUhtTokenReader Optional(this IUhtTokenReader tokenReader, string text, Action action)` — Parse optional text
- L152-160 _public method_ `public static IUhtTokenReader Optional(this IUhtTokenReader tokenReader, char text)` — Parse optional text
- L169-178 _public method_ `public static IUhtTokenReader Optional(this IUhtTokenReader tokenReader, char text, Action action)` — Parse optional text
- L186-194 _public method_ `public static IUhtTokenReader OptionalStartsWith(this IUhtTokenReader tokenReader, string text)` — Parse optional token that starts with the given text
- L203-213 _public method_ `public static IUhtTokenReader OptionalStartsWith(this IUhtTokenReader tokenReader, string text, UhtTokenDelegate tokenDelegate)` — Parse optional token that starts with the given text
- L222-231 _public method_ `public static IUhtTokenReader OptionalEndsWith(this IUhtTokenReader tokenReader, string text, Action<string> action)` — Parse optional text that ends with with the given text
- L240-373 _public method_ `public static IUhtTokenReader OptionalAttributes(this IUhtTokenReader tokenReader, bool enableAlignAs, Action<string>? attributeAction = null)` — Parse attributes and optionally alignment specifier
- L383-395 _public method_ `public static IUhtTokenReader Require(this IUhtTokenReader tokenReader, string text, object? exceptionContext = null)` — Require the given text
- L405-408 _public method_ `public static IUhtTokenReader Require(this IUhtTokenReader tokenReader, string text, UhtTokenDelegate tokenDelegate)` — Require the given text
- L419-433 _public method_ `public static IUhtTokenReader Require(this IUhtTokenReader tokenReader, string text, object? exceptionContext, UhtTokenDelegate tokenDelegate)` — Require the given text
- L443-455 _public method_ `public static IUhtTokenReader Require(this IUhtTokenReader tokenReader, char text, object? exceptionContext = null)` — Require the given text
- L465-468 _public method_ `public static IUhtTokenReader Require(this IUhtTokenReader tokenReader, char text, UhtTokenDelegate tokenDelegate)` — Require the given text
- L479-493 _public method_ `public static IUhtTokenReader Require(this IUhtTokenReader tokenReader, char text, object? exceptionContext, UhtTokenDelegate tokenDelegate)` — Require the given text

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderIdentifierExtensions.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Tokenizer.UhtCppIdentifierOptions`  
`public enum UhtCppIdentifierOptions`  
_public; L14-26_
- attrs: `[Flags]`
- desc: Options when parsing identifier
- L20 _public* enumerator_ `None` — No options
- L25 _public* enumerator_ `AllowTemplates = 1 << 0` — Include template arguments when parsing identifier

#### class `EpicGames.UHT.Tokenizer.UhtGetCppIdentifierOptionsExtensions`  
`public static class UhtGetCppIdentifierOptionsExtensions`  
_public; L32-68_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L41-44 _public method_ `public static bool HasAnyFlags(this UhtCppIdentifierOptions inFlags, UhtCppIdentifierOptions testFlags)` — Test to see if any of the specified flags are set
- L52-55 _public method_ `public static bool HasAllFlags(this UhtCppIdentifierOptions inFlags, UhtCppIdentifierOptions testFlags)` — Test to see if all of the specified flags are set
- L64-67 _public method_ `public static bool HasExactFlags(this UhtCppIdentifierOptions inFlags, UhtCppIdentifierOptions testFlags, UhtCppIdentifierOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderIdentifierExtensions`  
`public static class UhtTokenReaderIdentifierExtensions`  
_public; L73-317_
- desc: Collection of token reader extensions for working with identifiers
- L80-89 _public method_ `public static bool TryOptionalIdentifier(this IUhtTokenReader tokenReader)` — Get the next token and verify that it is an identifier
- L97-108 _public method_ `public static bool TryOptionalIdentifier(this IUhtTokenReader tokenReader, out UhtToken identifier)` — Get the next token and verify that it is an identifier
- L116-126 _public method_ `public static IUhtTokenReader OptionalIdentifier(this IUhtTokenReader tokenReader, UhtTokenDelegate tokenDelegate)` — Parse an optional identifier
- L134-141 _public method_ `public static IUhtTokenReader OptionalNamespace(this IUhtTokenReader tokenReader, string namespaceText)` — Parse an optional namespace
- L150-159 _public method_ `public static IUhtTokenReader RequireIdentifier(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Parse a required identifier
- L167-170 _public method_ `public static IUhtTokenReader RequireIdentifier(this IUhtTokenReader tokenReader, UhtTokenDelegate tokenDelegate)` — Parse a required identifier
- L180-191 _public method_ `public static IUhtTokenReader RequireIdentifier(this IUhtTokenReader tokenReader, object? exceptionContext, UhtTokenDelegate tokenDelegate)` — Parse a required identifier
- L200-210 _public method_ `public static UhtToken GetIdentifier(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get a required identifier
- L219-225 _public method_ `public static IUhtTokenReader RequireCppIdentifier(this IUhtTokenReader tokenReader, UhtCppIdentifierOptions options, UhtTokenListDelegate tokenListDelegate)` — Parse a required cpp identifier
- L235-241 _public method_ `public static IUhtTokenReader RequireCppIdentifier(this IUhtTokenReader tokenReader, ref UhtToken initialIdentifier, UhtCppIdentifierOptions options, UhtTokenListDelegate tokenListDelegate)` — Parse a required cpp identifier
- L249-254 _public method_ `public static UhtTokenList GetCppIdentifier(this IUhtTokenReader tokenReader, UhtCppIdentifierOptions options = UhtCppIdentifierOptions.None)` — Get a required cpp identifier
- L263-316 _public method_ `public static UhtTokenList GetCppIdentifier(this IUhtTokenReader tokenReader, ref UhtToken initialIdentifier, UhtCppIdentifierOptions options = UhtCppIdentifierOptions.None)` — Get a required cpp identifier

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderIntegerExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderIntegerExtensions`  
`public static class UhtTokenReaderIntegerExtensions`  
_public; L19-239_
- desc: Collection of helper methods to parse integers
- L27-37 _public method_ `public static bool TryOptionalConstInt(this IUhtTokenReader tokenReader, out int value)` — Get the next token as an integer. If the next token is not an integer, no token is consumed.
- L44-48 _public method_ `public static IUhtTokenReader OptionalConstInt(this IUhtTokenReader tokenReader)` — Get the next token as an integer. If the next token is not an integer, an exception is thrown
- L56-63 _public method_ `public static IUhtTokenReader RequireConstInt(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as an integer. If the next token is not an integer, an exception is thrown
- L71-78 _public method_ `public static int GetConstInt(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as an integer. If the next token is not an integer, an exception is thrown
- L86-96 _public method_ `public static bool TryOptionalConstLong(this IUhtTokenReader tokenReader, out long value)` — Get the next token as an integer. If the next token is not an integer, no token is consumed.
- L103-112 _public method_ `public static IUhtTokenReader OptionalConstLong(this IUhtTokenReader tokenReader)` — Get the next token as an integer. If the next token is not an integer, an exception is thrown
- L120-127 _public method_ `public static IUhtTokenReader RequireConstLong(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as an integer. If the next token is not an integer, an exception is thrown
- L135-142 _public method_ `public static long GetConstLong(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as an integer. If the next token is not an integer, an exception is thrown
- L150-174 _public method_ `public static bool TryOptionalLeadingSignConstNumeric(this IUhtTokenReader tokenReader, UhtParseMergedSignToken tokenDelegate)` — Helper method to combine any leading sign with the next numeric token
- L182-191 _public method_ `public static bool TryOptionalConstIntExpression(this IUhtTokenReader tokenReader, out int value)` — Get the next integer. It also handled [+/-] token followed by an integer.
- L198-206 _public method_ `public static int GetConstIntExpression(this IUhtTokenReader tokenReader)` — Get the next integer. It also handled [+/-] token followed by an integer.
- L214-223 _public method_ `public static bool TryOptionalConstLongExpression(this IUhtTokenReader tokenReader, out long value)` — Get the next integer. It also handled [+/-] token followed by an integer.
- L230-238 _public method_ `public static int GetConstLongExpression(this IUhtTokenReader tokenReader)` — Get the next long. It also handled [+/-] token followed by an long.

#### Namespace-level symbols

- L14 _public delegate_ `public delegate bool UhtParseMergedSignToken(ref UhtToken token)` — Notification of signed token being parsed

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderSkipExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderSkipExtensions`  
`public static class UhtTokenReaderSkipExtensions`  
_public; L11-137_
- desc: Series of extensions to token reading that are far too specialized to be included in the reader.
- L19-24 _public method_ `public static IUhtTokenReader SkipOne(this IUhtTokenReader tokenReader)` — Skip a token regardless of the type.
- L36-62 _public method_ `public static IUhtTokenReader SkipBrackets(this IUhtTokenReader tokenReader, char initiator, char terminator, int initialNesting, object? exceptionContext = null)` — Skip any block of tokens wrapped by the given token symbols
- L75-111 _public method_ `public static IUhtTokenReader SkipBrackets(this IUhtTokenReader tokenReader, char initiator, char terminator, int initialNesting, Action<UhtToken> callback, object? exceptionContext = null)` — Skip any block of tokens wrapped by the given token symbols
- L120-136 _public method_ `public static IUhtTokenReader SkipUntil(this IUhtTokenReader tokenReader, char terminator, object? exceptionContext = null)` — Skip tokens until the given terminator is found. The terminator will not be consumed.

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderStringExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderStringExtensions`  
`public static class UhtTokenReaderStringExtensions`  
_public; L12-150_
- desc: Collection of token reader exceptions for handling strings
- L20-31 _public method_ `public static bool TryOptionalConstString(this IUhtTokenReader tokenReader, out StringView value)` — Get the next token as a string. If the next token is not a string, no token is consumed.
- L38-46 _public method_ `public static IUhtTokenReader OptionalConstString(this IUhtTokenReader tokenReader)` — Get the next token as a string. If the next token is not a string, no token is consumed.
- L54-63 _public method_ `public static IUhtTokenReader RequireConstString(this IUhtTokenReader tokenReader, object? exceptionContext)` — Verify that the next token is a string.
- L71-81 _public method_ `public static StringView GetConstString(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as a string. If the next token is not a string, an exception is thrown
- L90-100 _public method_ `public static StringView GetConstQuotedString(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get the next token as a quoted string. If the next token is not a string, an exception is thrown. Character constants are not considered strings by this routine.
- L108-123 _public method_ `public static StringView GetWrappedConstString(this IUhtTokenReader tokenReader, object? exceptionContext = null)` — Get a const string that can optionally be wrapped with a TEXT() macro
- L132-149 _public method_ `public static StringView GetTypedConstString(this IUhtTokenReader tokenReader, string typeName, object? exceptionContext = null)` — Get a typed const string that can optionally be wrapped with a TEXT() macro

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReaderUtilityExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReaderUtilityExtensions`  
`public static class UhtTokenReaderUtilityExtensions`  
_public; L14-228_
- desc: Collection of assorted utility token reader extensions
- L16 _private field_ `private static readonly HashSet<StringView> s_skipDeclarationWarningStrings = [ "GENERATED_BODY", "GENERATED_IINTERFACE_BODY", "GENERATED_UCLASS_BODY", "GENERATED_UINTERFACE_BODY", "GENERATED_USTRUCT_BODY", ]`
- L25 _private field_ `private static readonly HashSet<StringView> s_skipTypeWarningStrings = [ "RIGVM_METHOD", "UCLASS", "UDELEGATE", "UENUM", "UFUNCTION", "UINTERFACE", "UMETA", "UPROPERTY", "USTRUCT", ]`
- L44-55 _public method_ `public static bool TryOptionalAPIMacro(this IUhtTokenReader tokenReader, out UhtToken apiMacroToken)` — Try to parse an optional _API macro
- L64-87 _private method_ `private static bool CheckForUEMacro(IUhtMessageSite messageSite, ref UhtToken token, bool generateError)` — Check to see if we have reached an identifier that is a UE macro
- L95-192 _public method_ `public static void SkipDeclaration(this UhtParsingScope topScope, UhtToken token)` — Given a declaration/statement that starts with the given token, skip the declaration in the header.
- L194-227 _private method_ `private static bool IsProbablyAMacro(StringView identifier)`

### `Source/Programs/Shared/EpicGames.UHT/Tokenizer/UhtTokenReplayReader.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Tokenizer.UhtTokenReplayReader`  
`public sealed class UhtTokenReplayReader : IUhtTokenReader, IUhtMessageLineNumber`  
_public; L15-327_
- inherits: `IUhtTokenReader, IUhtMessageLineNumber`
- desc: Token reader to replay previously recorded token stream
- L17 _private* const_ `const int MaxSavedStates = 2`
- L24 _private field_ `private IUhtMessageSite _messageSite`
- L25 _private field_ `private ReadOnlyMemory<UhtToken> _tokens`
- L26 _private field_ `private ReadOnlyMemory<char> _data`
- L27 _private field_ `private int _currentTokenIndex = -1`
- L28 _private field_ `private bool _hasToken = false`
- L29 _private field_ `private UhtToken _currentToken = new()`
- L30 _private field_ `private readonly SavedState[] _savedStates = new SavedState[MaxSavedStates]`
- L31 _private field_ `private int _savedStateCount = 0`
- L32 _private field_ `private UhtTokenType _endTokenType = UhtTokenType.EndOfFile`
- L41-48 _public ctor_ `public UhtTokenReplayReader(IUhtMessageSite messageSite, ReadOnlyMemory<char> data, ReadOnlyMemory<UhtToken> tokens, UhtTokenType endTokenType)` — Construct new token reader
- L53-58 _public ctor_ `public UhtTokenReplayReader()` — Construct token replay reader intended for caching. Use Reset method to prepare it for use
- L68-79 _public method_ `public UhtTokenReplayReader Reset(IUhtMessageSite messageSite, ReadOnlyMemory<char> data, ReadOnlyMemory<UhtToken> tokens, UhtTokenType endTokenType)` — Reset a cached replay reader for replaying a new stream of tokens
- L82 _private* property_ `IUhtMessageSession IUhtMessageSite.MessageSession => ...`
- L83 _private* property_ `IUhtMessageSource? IUhtMessageSite.MessageSource => ...`
- L84 _private* property_ `IUhtMessageLineNumber? IUhtMessageSite.MessageLineNumber => ...`
- L89-99 _public property_ `public bool IsEOF { get; }` — (inheritdoc)
- L102-112 _public property_ `public int InputPos { get; }` — (inheritdoc)
- L115-126 _public property_ `public int InputLine { get; set; }` — (inheritdoc)
- L129 _public property_ `public IUhtTokenPreprocessor? TokenPreprocessor { get; set; }` — (inheritdoc)
- L132 _public property_ `public int LookAheadEnableCount { get; set; }` — (inheritdoc)
- L135 _public property_ `public ReadOnlySpan<StringView> Comments => ...` — (inheritdoc)
- L138-141 _public method_ `public void ClearComments()` — (inheritdoc)
- L144-147 _public method_ `public void ConsumeToken()` — (inheritdoc)
- L150-153 _public method_ `public void DisableComments()` — (inheritdoc)
- L156-159 _public method_ `public void EnableComments()` — (inheritdoc)
- L162-165 _public method_ `public void CommitPendingComments()` — (inheritdoc)
- L168-171 _public method_ `public UhtToken GetLine()` — (inheritdoc)
- L174-177 _public method_ `public StringView GetRawString(char terminator, UhtRawStringOptions options)` — (inheritdoc)
- L180-183 _public method_ `public StringView GetStringView(int startPos, int count)` — (inheritdoc)
- L186-191 _public method_ `public UhtToken GetToken()` — (inheritdoc)
- L194-197 _public method_ `public int GetReplayTokenIndex()` — (inheritdoc)
- L200-203 _public method_ `public bool IsFirstTokenInLine(ref UhtToken token)` — (inheritdoc)
- L206-213 _public method_ `public ref UhtToken PeekToken()` — (inheritdoc)
- L216-219 _public method_ `public void SkipWhitespaceAndComments()` — (inheritdoc)
- L222-230 _public method_ `public void SaveState()` — (inheritdoc)
- L233-247 _public method_ `public void RestoreState()` — (inheritdoc)
- L250-258 _public method_ `public void AbandonState()` — (inheritdoc)
- L261-264 _public method_ `public void EnableRecording()` — (inheritdoc)
- L267-270 _public method_ `public void DisableRecording()` — (inheritdoc)
- L273-276 _public method_ `public void RecordToken(ref UhtToken token)` — (inheritdoc)
- L279 _public property_ `public List<UhtToken> RecordedTokens => ...` — (inheritdoc)
- L283-301 _private* property_ `int IUhtMessageLineNumber.MessageLineNumber { get; }`
- L304-326 _private method_ `private ref UhtToken GetTokenInternal()`

#### struct `EpicGames.UHT.Tokenizer.UhtTokenReplayReader.SavedState`  
`private struct SavedState`  
_private; L18-22_
- L20 _public property_ `public int TokenIndex { get; set; }`
- L21 _public property_ `public bool HasToken { get; set; }`

#### struct `EpicGames.UHT.Tokenizer.UhtTokenReplayReaderBorrower`  
`public readonly struct UhtTokenReplayReaderBorrower : IDisposable`  
_public; L332-363_
- inherits: `IDisposable`
- desc: Borrow a thread specific token replay reader
- L334 _private field_ `private static readonly ThreadLocal<Stack<UhtTokenReplayReader>> s_tlsStack = new(() => new Stack<UhtTokenReplayReader>())`
- L336 _private field_ `private readonly UhtTokenReplayReader _reader`
- L341 _public property_ `public readonly IUhtTokenReader Reader => ...` — The borrowed reader
- L351-356 _public ctor_ `public UhtTokenReplayReaderBorrower(IUhtMessageSite messageSite, ReadOnlyMemory<char> data, ReadOnlyMemory<UhtToken> tokens, UhtTokenType endTokenType)` — Borrow a thread specific replay reader
- L359-362 _public method_ `public readonly void Dispose()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtAnsiStrProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtAnsiStrProperty`  
`public class UhtAnsiStrProperty : UhtProperty`  
_public; L19-141_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "AnsiStrProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FAnsiStrProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L31 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L34 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L37 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L43-48 _public ctor_ `public UhtAnsiStrProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L55-57 _public ctor_ `public UhtAnsiStrProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L63-66 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L69-73 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L76-81 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L84-87 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L90-104 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L109-140 _private method_ `private static UhtAnsiStrProperty? AnsiStrProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FAnsiString")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtArrayProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtArrayProperty`  
`public class UhtArrayProperty : UhtContainerBaseProperty`  
_public; L21-287_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "ArrayProperty", IsProperty = true)]`
- inherits: `UhtContainerBaseProperty`
- desc: Represents the FArrayProperty engine type
- L24 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L27 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L30 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L33 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L36 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L39 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L46-66 _public ctor_ `public UhtArrayProperty(UhtPropertySettings propertySettings, UhtProperty value) : base(propertySettings, value)` — Construct a new array property
- L73-75 _public ctor_ `public UhtArrayProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L81-84 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L87-102 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L104-112 _private method_ `private void UpdateCaps()`
- L115-121 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L124-145 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L148-151 _public method_ `public override IEnumerable<UhtChildProperty> EnumerateChildProperties(UhtCppIdentifier identifier, UhtChildPropertyOrder order)` — (inheritdoc)
- L154-157 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L160-165 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L168-171 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L174-178 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L181-184 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L187-201 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L204-223 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L226-233 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L238-285 _private method_ `private static UhtArrayProperty? ArrayProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TArray")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtBoolProperty.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtBoolType`  
`public enum UhtBoolType`  
_public; L18-45_
- desc: Type of boolean
- L24 _public* enumerator_ `Native` — Native bool
- L29 _public* enumerator_ `UInt8` — Used for all bitmask uint booleans
- L34 _public* enumerator_ `UInt16` — Currently unused
- L39 _public* enumerator_ `UInt32` — Currently unused
- L44 _public* enumerator_ `UInt64` — Currently unused

#### class `EpicGames.UHT.Types.UhtBoolProperty`  
`public class UhtBoolProperty : UhtProperty`  
_public; L52-348_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "BoolProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: Represents the FBoolProperty engine type
- L55 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L58-78 _protected property_ `protected override string CppTypeText { get; }` — (inheritdoc)
- L81-101 _protected property_ `protected override string PGetMacroText { get; }` — (inheritdoc)
- L106 _protected property_ `protected bool IsNativeBool => ...` — If true, the boolean is a native bool and not a UBOOL
- L109 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L112 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L117 _protected property_ `protected override bool CodeGenParamsAppendOffset => ...` — (inheritdoc)
- L123 _public property_ `public UhtBoolType BoolType { get; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Type of the boolean
- L129-140 _public property_ `public override string StrippedEngineName { get; }` — attrs: `[JsonIgnore]` — Return the engine name without and 'b' prefixes
- L147-156 _public ctor_ `public UhtBoolProperty(UhtPropertySettings propertySettings, UhtBoolType boolType) : base(propertySettings)` — Construct a new boolean property
- L163-166 _public ctor_ `public UhtBoolProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L172-176 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L179-211 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument = false)` — (inheritdoc)
- L214-217 _protected method_ `protected override StringBuilder AppendCommonDecl(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — (inheritdoc)
- L220-233 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L236-243 _protected method_ `protected override StringBuilder AppendConstInitDefImpl(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, Action<StringBuilder>? outerFunc, string? offset, int tabs)` — (inheritdoc)
- L246-259 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L262-288 _public method_ `public override StringBuilder AppendFullDecl(StringBuilder builder, UhtPropertyTextType textType, bool skipParameterName = false)` — (inheritdoc)
- L291-295 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L298-301 _protected method_ `protected override StringBuilder AppendTypedVerseArgumentUnmarshal(StringBuilder builder)` — (inheritdoc)
- L304-313 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L316-320 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L322-332 _private method_ `private StringBuilder AppendSetBit(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)`
- L338-346 _private method_ `private static UhtBoolProperty? BoolProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "bool", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppress`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtByteProperty.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtByteCppForm`  
`public enum UhtByteCppForm`  
_public; L21-33_
- desc: The form that the byte was defined
- L27 _public* enumerator_ `UnsignedInt8` — uint8
- L32 _public* enumerator_ `Utf8Char` — UTF8CHAR

#### class `EpicGames.UHT.Types.UhtByteProperty`  
`public class UhtByteProperty : UhtNumericProperty`  
_public; L40-280_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "ByteProperty", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FByteProperty
- L46 _public property_ `public UhtEnum? Enum { get; set; }` — attrs: `[JsonConverter(typeof(UhtNullableTypeSourceNameJsonConverter<UhtEnum>))]` — Referenced enumeration (TEnumAsByte)
- L49 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L52 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L55-72 _protected property_ `protected override string PGetMacroText { get; }` — (inheritdoc)
- L75 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L80 _public property_ `public UhtByteCppForm CppForm { get; init; }` — Form in which the uint8 was specified
- L83 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L86 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L94-109 _public ctor_ `public UhtByteProperty(UhtPropertySettings propertySettings, UhtByteCppForm cppForm = UhtByteCppForm.UnsignedInt8, UhtEnum? enumObj = null) : base(propertySettings)` — Construct a new property
- L116-120 _public ctor_ `public UhtByteProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L126-131 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L134-140 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L143-147 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L150-174 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L177-180 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L183-186 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L189-192 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L195-205 _public method_ `public override StringBuilder AppendFunctionThunkParameterArg(StringBuilder builder)` — (inheritdoc)
- L208-218 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L221-232 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L235-246 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L252-262 _private method_ `private static UhtProperty? UInt8Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "uint8", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppres`
- L267-278 _private method_ `private static UhtProperty? VerseChar8Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::char8", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtClassProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtClassProperty`  
`public class UhtClassProperty : UhtObjectProperty`  
_public; L19-178_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "ClassProperty", IsProperty = true)]`
- inherits: `UhtObjectProperty`
- desc: FClassProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L31-38 _public ctor_ `public UhtClassProperty(UhtPropertySettings propertySettings, UhtObjectCppForm cppForm, UhtClass referencedClass, EPropertyFlags extraFlags = EPropertyFlags.None) : this(new UhtNoValidateConstruct { }, propertySettings, cppForm, referencedClass, extraFlags)` — Construct a new property
- L48-53 _protected ctor_ `protected UhtClassProperty(UhtNoValidateConstruct _, UhtPropertySettings propertySettings, UhtObjectCppForm cppForm, UhtClass referencedClass, EPropertyFlags extraFlags) : base(_, propertySettings, cppForm, referencedClass, extraFlags)` — Construct a new property
- L60-62 _public ctor_ `public UhtClassProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L68-71 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L74-81 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L84-150 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L153-158 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L161-164 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L167-177 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtContainerProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtContainerBaseProperty`  
`public abstract class UhtContainerBaseProperty : UhtProperty`  
_public; L13-117_
- inherits: `UhtProperty`
- desc: Common base class for containers with a value
- L17 _public property_ `public UhtProperty ValueProperty { get; set; }` — (inheritdoc)
- L24-29 _protected ctor_ `protected UhtContainerBaseProperty(UhtPropertySettings propertySettings, UhtProperty value) : base(propertySettings)` — Construct a new property
- L36-39 _protected ctor_ `protected UhtContainerBaseProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L45-49 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L52-56 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L59-62 _protected method_ `protected override bool NeedsGCBarrierWhenPassedToFunctionImpl(UhtFunction function)` — (inheritdoc)
- L65-69 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L77-90 _protected method_ `protected static void PropagateFlagsFromInnerAndHandlePersistentInstanceMetadata(UhtProperty container, UhtMetaData? metaData, UhtProperty inner)` — Propagate flags and meta data to/from child properties
- L98-104 _protected method_ `protected static EPropertyFlags ResolveAndReturnNewFlags(UhtProperty child, UhtResolvePhase phase)` — Resolve the child and return any new flags
- L107-110 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L113-116 _public method_ `public override bool IsAllowedInOptionalClass([NotNullWhen(false)] out string? propPath)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtDelegateProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtDelegateProperty`  
`public class UhtDelegateProperty : UhtProperty`  
_public; L20-190_
- attrs: `[UhtEngineClass(Name = "DelegateProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FDelegatePropertyDelegateProperty
- L23 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L26 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L29 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L32 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L35 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L38 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L44 _public property_ `public UhtFunction Function { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtFunction>))]` — Referenced function
- L51-57 _public ctor_ `public UhtDelegateProperty(UhtPropertySettings propertySettings, UhtFunction function) : base(propertySettings)` — Construct new property
- L64-67 _public ctor_ `public UhtDelegateProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L73-77 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L80-90 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L93-96 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L99-103 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L106-121 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L124-127 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L130-133 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L136-139 _public method_ `public override StringBuilder AppendFunctionThunkParameterArg(StringBuilder builder)` — (inheritdoc)
- L142-145 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L148-152 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L155-158 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L161-168 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L171-189 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtDoubleProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtDoubleProperty`  
`public class UhtDoubleProperty : UhtNumericProperty`  
_public; L18-95_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "DoubleProperty", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FDoubleProperty
- L21 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L24 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L27 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L30 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L36-39 _public ctor_ `public UhtDoubleProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Create new property
- L46-48 _public ctor_ `public UhtDoubleProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L54-57 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L60-71 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument = false)` — (inheritdoc)
- L74-78 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L81-84 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L90-93 _private method_ `private static UhtDoubleProperty? DoubleProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "double", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppre`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtEnumProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtEnumProperty`  
`public class UhtEnumProperty : UhtProperty`  
_public; L23-375_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "EnumProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FEnumProperty
- L26 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L29 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L32 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L35 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L38 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L41 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L47 _public property_ `public UhtEnum Enum { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtEnum>))]` — Referenced enum
- L53 _public property_ `public UhtNumericProperty? UnderlyingProperty { get; set; }` — attrs: `[JsonIgnore]` — Underlying property set when the enum has an underlying integer type
- L59 _public property_ `public UhtEnumUnderlyingType UnderlyingType => ...` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Underlying type which defaults to Int32 if the referenced enum doesn't have an underlying type
- L66-80 _public ctor_ `public UhtEnumProperty(UhtPropertySettings propertySettings, UhtEnum enumObj) : base(propertySettings)` — Construct property
- L87-91 _public ctor_ `public UhtEnumProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L97-102 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L105-113 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L116-119 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L130-186 _public method_ `public static StringBuilder AppendEnumText(StringBuilder builder, UhtProperty property, UhtEnum enumObj, UhtPropertyTextType textType, bool isTemplateArgument)` — Append enum text
- L195-210 _public method_ `public static StringBuilder AppendEnumFunctionThunkParameterArg(StringBuilder builder, UhtProperty property, UhtEnum enumObj)` — Append the text for a function thunk call argument
- L220-237 _public method_ `public static bool SanitizeEnumDefaultValue(UhtProperty property, UhtEnum enumObj, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — Sanitize the default value for an enumeration
- L240-243 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L246-252 _public method_ `public override IEnumerable<UhtChildProperty> EnumerateChildProperties(UhtCppIdentifier identifier, UhtChildPropertyOrder order)` — (inheritdoc)
- L255-258 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L261-278 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L281-284 _public method_ `public override StringBuilder AppendFunctionThunkParameterArg(StringBuilder builder)` — (inheritdoc)
- L287-290 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L293-304 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L307-310 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L313-324 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L326-352 _private method_ `private UhtNumericProperty CreateUnderlyingProperty()`
- L358-373 _private method_ `private static UhtByteProperty? EnumProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TEnumAsByte")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtFieldPathProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtFieldPathProperty`  
`public class UhtFieldPathProperty : UhtProperty`  
_public; L18-157_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "FieldPathProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FFieldPathProperty
- L21 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L24 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L27 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L30 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L33 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L36 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L41 _public property_ `public string FieldClassName { get; set; }` — Class name without the prefix
- L48-52 _public ctor_ `public UhtFieldPathProperty(UhtPropertySettings propertySettings, string fieldClassName) : base(propertySettings)` — Construct new property
- L59-62 _public ctor_ `public UhtFieldPathProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L68-72 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L75-82 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L85-98 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L101-104 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L107-110 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L113-117 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L120-123 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L126-133 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L139-155 _private method_ `private static UhtFieldPathProperty? FieldPathProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TFieldPath", Options = UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtFloatProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtFloatProperty`  
`public class UhtFloatProperty : UhtNumericProperty`  
_public; L17-80_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "FloatProperty", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FFloatProperty
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L29 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L35-38 _public ctor_ `public UhtFloatProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L45-47 _public ctor_ `public UhtFloatProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L53-56 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L59-63 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L66-69 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L75-78 _private method_ `private static UhtFloatProperty? FloatProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "float", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppres`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtInt16Property.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtInt16Property`  
`public class UhtInt16Property : UhtNumericProperty`  
_public; L16-77_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "Int16Property", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FInt16Property
- L19 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L22 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L28 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L34-36 _public ctor_ `public UhtInt16Property(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct new property
- L43-45 _public ctor_ `public UhtInt16Property(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L51-54 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L57-60 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L63-66 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L72-75 _private method_ `private static UhtInt16Property? Int16Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "int16", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppres`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtInt64Property.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtInt64Property`  
`public class UhtInt64Property : UhtNumericProperty`  
_public; L16-93_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "Int64Property", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FInt64Property
- L19 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L22 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28-31 _public ctor_ `public UhtInt64Property(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct new property
- L38-40 _public ctor_ `public UhtInt64Property(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L46-49 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L52-63 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument = false)` — (inheritdoc)
- L66 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L69 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L72-76 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L79-82 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L88-91 _private method_ `private static UhtInt64Property? Int64Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "int64", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppres`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtInt8Property.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtInt8Property`  
`public class UhtInt8Property : UhtNumericProperty`  
_public; L16-77_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "Int8Property", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FInt8Property
- L19 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L22 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28-30 _public ctor_ `public UhtInt8Property(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L37-39 _public ctor_ `public UhtInt8Property(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L45-48 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L51 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L54 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L57-60 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L63-66 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L72-75 _private method_ `private static UhtInt8Property? Int8Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "int8", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppress`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtIntProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtIntProperty`  
`public class UhtIntProperty : UhtNumericProperty`  
_public; L16-89_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "IntProperty", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FIntProperty
- L19 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L22 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L28 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L34-37 _public ctor_ `public UhtIntProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct new property
- L44-46 _public ctor_ `public UhtIntProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L52-55 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L58-62 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L65-68 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L74-77 _private method_ `private static UhtIntProperty? Int32Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "int32", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppres`
- L84-87 _private method_ `private static UhtIntProperty? IntProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "int", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [UhtPropertyType(Keyword = "signed", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [UhtPropertyTyp`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtInterfaceProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtInterfaceProperty`  
`public class UhtInterfaceProperty : UhtProperty`  
_public; L23-233_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "InterfaceProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FInterfaceProperty
- L26 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L29 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L32 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L35 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L38 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L41 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L47 _public property_ `public UhtClass InterfaceClass { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtClass>))]` — Referenced interface class
- L54-64 _public ctor_ `public UhtInterfaceProperty(UhtPropertySettings propertySettings, UhtClass interfaceClass) : base(propertySettings)` — Create a new property
- L71-74 _public ctor_ `public UhtInterfaceProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L80-84 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L87-100 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L103-106 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L109-125 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L128-131 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L134-151 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L154-158 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L161-164 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L167-171 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L174-177 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L180-187 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L190-197 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L200-204 _public method_ `public override bool MustBeConstArgument([NotNullWhen(true)] out UhtType? errorType)` — (inheritdoc)
- L210-213 _private method_ `private static UhtInterfaceProperty? FScriptInterfaceProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FScriptInterface", Options = UhtPropertyTypeOptions.Simple)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE00`
- L218-231 _private method_ `private static UhtProperty? TScriptInterfaceProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TScriptInterface")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificatio`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtLargeWorldCoordinatesRealProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtLargeWorldCoordinatesRealProperty`  
`public class UhtLargeWorldCoordinatesRealProperty : UhtNumericProperty`  
_public; L17-84_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "LargeWorldCoordinatesRealProperty", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FLargeWorldCoordinatesRealProperty
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L29 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L35-38 _public ctor_ `public UhtLargeWorldCoordinatesRealProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct new property
- L45-47 _public ctor_ `public UhtLargeWorldCoordinatesRealProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L53-56 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L59-63 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L66-69 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L75-82 _private method_ `private static UhtLargeWorldCoordinatesRealProperty? LargeWorldCoordinatesRealProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FLargeWorldCoordinatesReal", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute access`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtLazyObjectPtrProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtLazyObjectPtrProperty`  
`public class UhtLazyObjectPtrProperty : UhtObjectPropertyBase`  
_public; L19-146_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "LazyObjectProperty", IsProperty = true)]`
- inherits: `UhtObjectPropertyBase`
- desc: FLazyObjectProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L31 _protected property_ `protected override bool PGetPassAsNoPtr => ...` — (inheritdoc)
- L34 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L37 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L40 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L47-52 _public ctor_ `public UhtLazyObjectPtrProperty(UhtPropertySettings propertySettings, UhtClass referencedClass) : base(new UhtNoValidateConstruct(), propertySettings, UhtObjectCppForm.NativeObject, referencedClass)` — Construct new property
- L59-61 _public ctor_ `public UhtLazyObjectPtrProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L67-70 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L73-82 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L85-88 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L91-94 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L97-101 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L104-111 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L114-124 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L130-144 _private method_ `private static UhtLazyObjectPtrProperty? LazyObjectPtrProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TLazyObjectPtr")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification `

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtMapProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtMapProperty`  
`public class UhtMapProperty : UhtContainerBaseProperty`  
_public; L21-359_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "MapProperty", IsProperty = true)]`
- inherits: `UhtContainerBaseProperty`
- desc: FMapProperty
- L24 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L27 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L30 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L33 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L36 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L39 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L44 _public property_ `public UhtProperty KeyProperty { get; set; }` — Key property
- L52-83 _public ctor_ `public UhtMapProperty(UhtPropertySettings propertySettings, UhtProperty key, UhtProperty value) : base(propertySettings, value)` — Construct new property
- L90-93 _public ctor_ `public UhtMapProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L99-103 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L106-128 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L130-138 _private method_ `private void UpdateCaps()`
- L141-145 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L148-158 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L161-182 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L185-198 _public method_ `public override IEnumerable<UhtChildProperty> EnumerateChildProperties(UhtCppIdentifier identifier, UhtChildPropertyOrder order)` — (inheritdoc)
- L201-204 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L207-216 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L219-223 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L226-230 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L233-236 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L239-247 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L250-254 _public method_ `public override void ValidateDeprecated()` — (inheritdoc)
- L257-260 _protected method_ `protected override bool NeedsGCBarrierWhenPassedToFunctionImpl(UhtFunction function)` — (inheritdoc)
- L263-267 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L270-278 _public method_ `public override bool ValidateStructPropertyOkForNet(UhtProperty referencingProperty)` — (inheritdoc)
- L281-292 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L297-357 _private method_ `private static UhtMapProperty? MapProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TMap")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtMulticastDelegateProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtMulticastDelegateProperty`  
`public abstract class UhtMulticastDelegateProperty : UhtProperty`  
_public; L17-150_
- attrs: `[UhtEngineClass(Name = "MulticastDelegateProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FMulticastDelegateProperty
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L29 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L35 _public property_ `public UhtFunction Function { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtFunction>))]` — Referenced function
- L42-49 _protected ctor_ `protected UhtMulticastDelegateProperty(UhtPropertySettings propertySettings, UhtFunction function) : base(propertySettings)` — Construct property
- L56-59 _protected ctor_ `protected UhtMulticastDelegateProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L65-69 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L72-82 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L85-88 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L91-95 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L98-114 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L117-120 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L123-126 _public method_ `public override StringBuilder AppendFunctionThunkParameterArg(StringBuilder builder)` — (inheritdoc)
- L129-133 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L136-139 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L142-149 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtMulticastInlineDelegateProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtMulticastInlineDelegateProperty`  
`public class UhtMulticastInlineDelegateProperty : UhtMulticastDelegateProperty`  
_public; L16-81_
- attrs: `[UhtEngineClass(Name = "MulticastInlineDelegateProperty", IsProperty = true)]`
- inherits: `UhtMulticastDelegateProperty`
- desc: FMulticastInlineDelegateProperty
- L19 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L22 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L32-34 _public ctor_ `public UhtMulticastInlineDelegateProperty(UhtPropertySettings propertySettings, UhtFunction function) : base(propertySettings, function)` — Construct new property
- L41-43 _public ctor_ `public UhtMulticastInlineDelegateProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L49-52 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L55-68 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L71-74 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L77-80 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtMulticastSparseDelegateProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtMulticastSparseDelegateProperty`  
`public class UhtMulticastSparseDelegateProperty : UhtMulticastDelegateProperty`  
_public; L16-81_
- attrs: `[UhtEngineClass(Name = "MulticastSparseDelegateProperty", IsProperty = true)]`
- inherits: `UhtMulticastDelegateProperty`
- desc: FMulticastSparseDelegateProperty
- L19 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L22 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L32-34 _public ctor_ `public UhtMulticastSparseDelegateProperty(UhtPropertySettings propertySettings, UhtFunction function) : base(propertySettings, function)` — Construct a new property
- L41-43 _public ctor_ `public UhtMulticastSparseDelegateProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L49-52 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L55-68 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L71-74 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L77-80 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtNameProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtNameProperty`  
`public class UhtNameProperty : UhtProperty`  
_public; L19-105_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "NameProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FNameProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L31 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L34 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L37 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L44-48 _public ctor_ `public UhtNameProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L55-57 _public ctor_ `public UhtNameProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L63-66 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L69-73 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L76-88 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L91-94 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L100-103 _private method_ `private static UhtNameProperty? NameProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FName", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppres`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtNumericProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtNumericProperty`  
`public abstract class UhtNumericProperty : UhtProperty`  
_public; L13-54_
- inherits: `UhtProperty`
- desc: Base class for all numeric properties
- L16 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L19 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L25-28 _protected ctor_ `protected UhtNumericProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct new property
- L35-37 _protected ctor_ `protected UhtNumericProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L43-46 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L49-53 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtObjectProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtObjectProperty`  
`public class UhtObjectProperty : UhtObjectPropertyBase`  
_public; L17-213_
- attrs: `[UhtEngineClass(Name = "ObjectProperty", IsProperty = true)]`
- inherits: `UhtObjectPropertyBase`
- desc: FObjectProperty
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L29-36 _public ctor_ `public UhtObjectProperty(UhtPropertySettings propertySettings, UhtObjectCppForm cppForm, UhtClass referencedClass, EPropertyFlags extraFlags = EPropertyFlags.None) : this(new UhtNoValidateConstruct { }, propertySettings, cppForm, referencedClass, extraFlags)` — Construct a new property
- L46-51 _protected ctor_ `protected UhtObjectProperty(UhtNoValidateConstruct _, UhtPropertySettings propertySettings, UhtObjectCppForm cppForm, UhtClass referencedClass, EPropertyFlags extraFlags) : base(_, propertySettings, cppForm, referencedClass, extraFlags)` — Construct a new property
- L58-60 _public ctor_ `public UhtObjectProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L66-69 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L72-86 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L89-92 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L95-153 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L156-159 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L162-165 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L168-172 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L175-182 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L185-202 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L205-212 _protected method_ `protected override void ValidateMember(UhtStruct structObj, UhtValidationOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtObjectPropertyBase.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtObjectCppForm`  
`public enum UhtObjectCppForm`  
_public; L22-104_
- desc: How the object property appeared in the code
- L28 _public* enumerator_ `NativeObject` — Existing native object raw pointer
- L33 _public* enumerator_ `NativeClass` — Existing native class raw pointer
- L38 _public* enumerator_ `TObjectPtrObject` — TObjectPtr for an object
- L43 _public* enumerator_ `TObjectPtrClass` — TObjectPtr for a class
- L48 _public* enumerator_ `TSoftObjectPtr` — TSoftObjectPtr
- L53 _public* enumerator_ `TSoftClassPtr` — TSoftClassPtr
- L58 _public* enumerator_ `TSubclassOf` — TSubclassOf
- L63 _public* enumerator_ `VerseType` — verse::type
- L68 _public* enumerator_ `VerseSubtype` — verse::subtype
- L73 _public* enumerator_ `VerseCastableType` — verse::castable_type
- L78 _public* enumerator_ `VerseCastableSubtype` — verse:castable_subtype
- L83 _public* enumerator_ `VerseConcreteType` — verse::concrete_type
- L88 _public* enumerator_ `VerseConcreteSubtype` — verse:concrete_subtype
- L93 _public* enumerator_ `VerseCastableConcreteType` — verse::castable_concrete_type
- L98 _public* enumerator_ `VerseCastableConcreteSubtype` — verse:castable_concrete_subtype
- L103 _public* enumerator_ `TInterfaceInstance` — TInterfaceInstance

#### class `EpicGames.UHT.Types.UhtObjectCppFormExtensions`  
`public static class UhtObjectCppFormExtensions`  
_public; L109-563_
- desc: Collection of extension methods for UhtObjectCppForm
- L118-145 _public method_ `public static bool IsValidForObjectProperty(this UhtObjectCppForm cppForm)` — Check to see if the given CPP form is valid for a object property
- L153-180 _public method_ `public static bool IsValidForClassProperty(this UhtObjectCppForm cppForm)` — Check to see if the given CPP form is valid for a class property
- L188-215 _public method_ `public static bool IsValidForVerseClassProperty(this UhtObjectCppForm cppForm)` — Check to see if the given CPP form is valid for a verse class property
- L222-249 _public method_ `public static UhtObjectCppForm GetSameTypeCppForm(this UhtObjectCppForm cppForm)` — Return a CppForm used when doing IsSameType checks
- L256-283 _public method_ `public static bool NeedsWhereClause(this UhtObjectCppForm cppForm)` — Returns true if this CppForm needs a verse where clause
- L291-324 _public method_ `public static string GetCodeGenParamsStruct(this UhtObjectCppForm cppForm)` — Return the params code gen name
- L332-369 _public method_ `public static string GetCodeGenParamsFlags(this UhtObjectCppForm cppForm)` — Return the params code gen flags
- L377-428 _public method_ `public static string GetPGetMacroText(this UhtObjectCppForm cppForm)` — Return the P_GET macro text based on the cpp form
- L436-463 _public method_ `public static UhtPGetArgumentType GetPGetArgumentType(this UhtObjectCppForm cppForm)` — Returns the PGET argument type for the given CppForm
- L471-498 _public method_ `public static bool GetPGetPassAsNoPtr(this UhtObjectCppForm cppForm)` — Return true if this form needs the NO_PTR option
- L505-562 _public method_ `public static (UhtClass, UhtClass?) InitializeProperty(this UhtObjectCppForm cppForm, UhtObjectPropertyBase property)` — Based on the cpp form, update the property settings

#### record struct `EpicGames.UHT.Types.UhtNoValidateConstruct`  
`public record struct UhtNoValidateConstruct()`  
_public; L569-569_
- desc: Helper struct used to create a unique argument list that performs no type specific validation

#### class `EpicGames.UHT.Types.UhtObjectPropertyBase`  
`public abstract class UhtObjectPropertyBase : UhtProperty`  
_public; L576-1039_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "ObjectPropertyBase", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FObjectPropertyBase
- L579 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L582 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L585 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L588 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L591 _protected property_ `protected override bool PGetPassAsNoPtr => ...` — (inheritdoc)
- L594 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L597 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L604 _public property_ `public UhtClass ReferencedClass { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtClass>))]` — Originally referenced class when property is created.
- L610 _public property_ `public UhtClass Class { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtClass>))]` — Referenced UCLASS that might later be changed depending on the type (i.e. Verse's TInterfaceInstance)
- L616 _public property_ `public UhtClass? MetaClass { get; set; }` — attrs: `[JsonConverter(typeof(UhtNullableTypeSourceNameJsonConverter<UhtClass>))]` — Referenced UCLASS for class properties
- L621 _public property_ `public UhtObjectCppForm CppForm { get; init; }` — The form that the object property appeared in the code
- L631-660 _protected ctor_ `protected UhtObjectPropertyBase(UhtNoValidateConstruct _, UhtPropertySettings propertySettings, UhtObjectCppForm cppForm, UhtClass referencedClass, EPropertyFlags extraFlags = EPropertyFlags.None) : base(propertySettings)` — Construct a property
- L667-673 _protected ctor_ `protected UhtObjectPropertyBase(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L679-686 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L689-702 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L705-708 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L711-720 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L723-730 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L733-749 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L752-756 _public method_ `public override void ValidateDeprecated()` — (inheritdoc)
- L759-763 _public method_ `public override bool MustBeConstArgument([NotNullWhen(true)] out UhtType? errorType)` — (inheritdoc)
- L766-771 _protected method_ `protected override bool NeedsGCBarrierWhenPassedToFunctionImpl(UhtFunction function)` — (inheritdoc)
- L779-809 _protected method_ `protected StringBuilder AppendVerseMangledType(StringBuilder builder, UhtClass type)` — Append the mangled name for all object types
- L817-906 _protected method_ `protected StringBuilder AppendTemplateType(StringBuilder builder)` — Append the template declaration for the given type
- L912-922 _private method_ `private static UhtClassProperty? SubclassOfProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TSubclassOf")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`
- L927-930 _private method_ `private static UhtProperty? TNonNullPtrType(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TNonNullPtr")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`
- L935-950 _private method_ `private static UhtProperty? ObjectPtrProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TObjectPtr")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "A`
- L955-958 _private method_ `private static UhtClassProperty? VerseTypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::type", Options = UhtPropertyTypeOptions.Simple)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Re`
- L963-969 _private method_ `private static UhtProperty? VerseSubTypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::subtype")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification `
- L974-977 _private method_ `private static UhtClassProperty? VerseCastableTypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::castable_type", Options = UhtPropertyTypeOptions.Simple)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "I`
- L982-988 _private method_ `private static UhtProperty? VerseCastableSubtypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::castable_subtype")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justi`
- L993-996 _private method_ `private static UhtClassProperty? VerseConcreteTypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::concrete_type", Options = UhtPropertyTypeOptions.Simple)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "I`
- L1001-1007 _private method_ `private static UhtProperty? VerseConcreteSubtypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::concrete_subtype")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justi`
- L1012-1015 _private method_ `private static UhtClassProperty? VerseCastableConcreteTypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::castable_concrete_type", Options = UhtPropertyTypeOptions.Simple)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("S`
- L1020-1026 _private method_ `private static UhtProperty? VerseCastableConcreteSubtypeProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::castable_concrete_subtype")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused paramete`
- L1031-1037 _private method_ `private static UhtProperty? TInterfaceInstanceProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TInterfaceInstance")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificat`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtOptionalProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtOptionalProperty`  
`public class UhtOptionalProperty : UhtContainerBaseProperty`  
_public; L21-257_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "OptionalProperty", IsProperty = true)]`
- inherits: `UhtContainerBaseProperty`
- desc: Represents the FOptionalProperty engine type
- L24 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L27 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L30 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L33 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L36 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L39 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L46-66 _public ctor_ `public UhtOptionalProperty(UhtPropertySettings propertySettings, UhtProperty value) : base(propertySettings, value)` — Construct a new Optional property
- L73-75 _public ctor_ `public UhtOptionalProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L81-84 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L87-102 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L104-112 _private method_ `private void UpdateCaps()`
- L115-121 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L124-150 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L153-156 _public method_ `public override IEnumerable<UhtChildProperty> EnumerateChildProperties(UhtCppIdentifier identifier, UhtChildPropertyOrder order)` — (inheritdoc)
- L159-162 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L165-169 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L172-175 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L178-192 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L195-211 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L214-221 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L226-255 _private method_ `private static UhtOptionalProperty? OptionalProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TOptional")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtSetProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtSetProperty`  
`public class UhtSetProperty : UhtContainerBaseProperty`  
_public; L20-267_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "SetProperty", IsProperty = true)]`
- inherits: `UhtContainerBaseProperty`
- desc: FSetProperty
- L23 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L26 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L29 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L32 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L35 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L38 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L45-59 _public ctor_ `public UhtSetProperty(UhtPropertySettings propertySettings, UhtProperty value) : base(propertySettings, value)` — Construct a new property
- L66-68 _public ctor_ `public UhtSetProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L74-77 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L80-95 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L97-105 _private method_ `private void UpdateCaps()`
- L108-114 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L117-134 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L137-140 _public method_ `public override IEnumerable<UhtChildProperty> EnumerateChildProperties(UhtCppIdentifier identifier, UhtChildPropertyOrder order)` — (inheritdoc)
- L143-156 _protected method_ `protected override StringBuilder AppendCommonDef(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — (inheritdoc)
- L159-165 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L168-171 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L174-178 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L181-184 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L187-194 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L197-205 _public method_ `public override bool ValidateStructPropertyOkForNet(UhtProperty referencingProperty)` — (inheritdoc)
- L208-219 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L224-265 _private method_ `private static UhtSetProperty? SetProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TSet")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtSoftClassProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtSoftClassProperty`  
`public class UhtSoftClassProperty : UhtSoftObjectProperty`  
_public; L19-106_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "SoftClassProperty", IsProperty = true)]`
- inherits: `UhtSoftObjectProperty`
- desc: FSoftClassProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L32-35 _public ctor_ `public UhtSoftClassProperty(UhtPropertySettings propertySettings, UhtClass referencedClass) : base(propertySettings, UhtObjectCppForm.TSoftClassPtr, referencedClass)` — Construct a new class property
- L42-44 _public ctor_ `public UhtSoftClassProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L50-53 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L56-64 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L67-76 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L79-82 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L85-88 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L94-104 _private method_ `private static UhtSoftClassProperty? SoftClassPtrProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TSoftClassPtr")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtSoftObjectProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtSoftObjectProperty`  
`public class UhtSoftObjectProperty : UhtObjectPropertyBase`  
_public; L18-128_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "SoftObjectProperty", IsProperty = true)]`
- inherits: `UhtObjectPropertyBase`
- desc: FSoftObjectProperty
- L21 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L24 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L31-34 _public ctor_ `public UhtSoftObjectProperty(UhtPropertySettings propertySettings, UhtClass referencedClass) : this(propertySettings, UhtObjectCppForm.TSoftObjectPtr, referencedClass)` — Construct a new property
- L42-47 _protected ctor_ `protected UhtSoftObjectProperty(UhtPropertySettings propertySettings, UhtObjectCppForm cppForm, UhtClass referencedClass) : base(new UhtNoValidateConstruct { }, propertySettings, cppForm, referencedClass)` — Construct a new property
- L54-56 _public ctor_ `public UhtSoftObjectProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L62-65 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L68-72 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L75-84 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L87-90 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L93-96 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L99-106 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L112-126 _private method_ `private static UhtSoftObjectProperty? SoftObjectPtrProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TSoftObjectPtr")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification `

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtStrProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtStrProperty`  
`public class UhtStrProperty : UhtProperty`  
_public; L19-143_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "StrProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FStrProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L31 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L34 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L37 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L43-47 _public ctor_ `public UhtStrProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L54-56 _public ctor_ `public UhtStrProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L62-65 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L68-72 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L75-80 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L83-86 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L89-103 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L109-142 _private method_ `private static UhtStrProperty? StrProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FString")] [UhtPropertyType(Keyword = "FMemoryImageString", Options = UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accesse`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtStructProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtStructProperty`  
`public class UhtStructProperty : UhtProperty`  
_public; L24-515_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "StructProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FStructProperty
- L27 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L30 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L33 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L36 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L39 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L42 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L48 _public property_ `public UhtScriptStruct ScriptStruct { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtScriptStruct>))]` — USTRUCT referenced by the property
- L55-62 _public ctor_ `public UhtStructProperty(UhtPropertySettings propertySettings, UhtScriptStruct scriptStruct) : base(propertySettings)` — Construct property
- L69-72 _public ctor_ `public UhtStructProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L78-82 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L85-100 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L102-122 _private method_ `private void UpdateCaps()`
- L125-128 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L131-139 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L142-145 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L148-161 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L164-167 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L170-175 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L178-181 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L184-204 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L207-214 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L217-224 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L227-238 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L241-248 _protected method_ `protected override void ValidateMember(UhtStruct structObj, UhtValidationOptions options)` — (inheritdoc)
- L251-254 _public method_ `public override bool ValidateStructPropertyOkForNet(UhtProperty referencingProperty)` — (inheritdoc)
- L257-281 _public method_ `public override bool IsAllowedInOptionalClass([NotNullWhen(false)] out string? propPath)` — (inheritdoc)
- L289-298 _public method_ `public virtual bool DefaultDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — Perform default, default value parsing
- L304-341 _private method_ `private static bool VectorStructDefaultValue(UhtStructProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — attrs: `[UhtStructDefaultValue(Name = "FVector")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "A`
- L346-375 _private method_ `private static bool RotatorStructDefaultValue(UhtStructProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — attrs: `[UhtStructDefaultValue(Name = "FRotator")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`
- L380-410 _private method_ `private static bool Vector2DStructDefaultValue(UhtStructProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — attrs: `[UhtStructDefaultValue(Name = "FVector2D")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = `
- L415-458 _private method_ `private static bool LinearColorStructDefaultValue(UhtStructProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — attrs: `[UhtStructDefaultValue(Name = "FLinearColor")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification`
- L463-506 _private method_ `private static bool ColorStructDefaultValue(UhtStructProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — attrs: `[UhtStructDefaultValue(Name = "FColor")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "At`
- L510-513 _private method_ `private static bool DefaultStructDefaultValue(UhtStructProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — attrs: `[UhtStructDefaultValue(Options = UhtStructDefaultValueOptions.Default)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`

#### class `EpicGames.UHT.Types.UhtTemplateStructProperty`  
`public class UhtTemplateStructProperty : UhtStructProperty`  
_public; L521-761_
- attrs: `[UnrealHeaderTool]`
- inherits: `UhtStructProperty`
- desc: FStructProperty
- L528 _public property_ `public string TemplateWrapperName { get; init; }` — When using the template wrapper pattern that provides a template wrapper to an existing structure that can reference types, this is the name of the template. For example, FInstancedStruct has TInstancedStruct as a wrapper template.
- L534 _public property_ `public UhtScriptStruct TemplateArgumentStruct { get; init; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtScriptStruct>))]` — The structure being wrapped by the template wrapper
- L543-547 _public ctor_ `public UhtTemplateStructProperty(UhtPropertySettings propertySettings, UhtScriptStruct scriptStruct, string templateWrapperName, UhtScriptStruct templateArgumentStruct) : base(propertySettings, scriptStruct)` — Construct property
- L554-558 _public ctor_ `public UhtTemplateStructProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L564-569 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L572-582 _public method_ `public override void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — (inheritdoc)
- L585-597 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L600-613 _public method_ `public override bool DefaultDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L619-637 _private method_ `private static UhtTemplateStructProperty? InstancedStructProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TInstancedStruct")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificatio`
- L642-665 _private method_ `private static UhtTemplateStructProperty? SubScriptStructOfProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TSubScriptStructOf")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificat`
- L670-759 _private method_ `private static UhtStructProperty? StateTreePropertyRefProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TStateTreePropertyRef")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justifi`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtTextProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtTextProperty`  
`public class UhtTextProperty : UhtProperty`  
_public; L19-798_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "TextProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FTextProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L31 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L34 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L37 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L43-48 _public ctor_ `public UhtTextProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L55-57 _public ctor_ `public UhtTextProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L63-66 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L69-73 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L76-127 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L130-133 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L139-142 _private method_ `private static UhtTextProperty? TextProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FText", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppres`
- L147-150 _private method_ `private static UhtProperty? MissingPrefixTextProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "Text", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate | UhtPropertyTypeOptions.CaseInsensitive)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification `
- L155-162 _private method_ `private static bool InvTextDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "INVTEXT")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`
- L167-171 _private method_ `private static bool LocTextDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCTEXT")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`
- L176-180 _private method_ `private static bool NoteLocTextDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "NOTELOCTEXT")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification`
- L185-215 _private method_ `private static bool NsLocTextDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "NSLOCTEXT")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification =`
- L220-252 _private method_ `private static bool NsNoteLocTextDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "NSNOTELOCTEXT")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificati`
- L257-268 _private method_ `private static bool LocTableDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCTABLE")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = `
- L273-298 _private method_ `private static bool LocGenFormatNamedDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_FORMAT_NAMED")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justi`
- L303-326 _private method_ `private static bool LocGenFormatOrderedDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_FORMAT_ORDERED")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Jus`
- L331-334 _private method_ `private static bool LocGenNumberDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_NUMBER")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificati`
- L339-342 _private method_ `private static bool LocGenNumberGroupedDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_NUMBER_GROUPED")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Jus`
- L347-350 _private method_ `private static bool LocGenNumberUngroupedDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_NUMBER_UNGROUPED")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", J`
- L355-358 _private method_ `private static bool LocGenNumberCustomDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_NUMBER_CUSTOM")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Just`
- L363-366 _private method_ `private static bool LocGenPercentDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_PERCENT")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificat`
- L371-374 _private method_ `private static bool LocGenPercentGroupedDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_PERCENT_GROUPED")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Ju`
- L379-382 _private method_ `private static bool LocGenPercentUngroupedDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_PERCENT_UNGROUPED")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", `
- L387-390 _private method_ `private static bool LocGenPercentCustomDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_PERCENT_CUSTOM")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Jus`
- L395-414 _private method_ `private static bool LocGenCurrencyDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_CURRENCY")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justifica`
- L419-422 _private method_ `private static bool LocGenDateLocalDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_DATE_LOCAL")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justifi`
- L427-430 _private method_ `private static bool LocGenDateUtcDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_DATE_UTC")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justifica`
- L435-438 _private method_ `private static bool LocGenTimeLocalDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_TIME_LOCAL")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justifi`
- L443-446 _private method_ `private static bool LocGenTimeUtcDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_TIME_UTC")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justifica`
- L451-454 _private method_ `private static bool LocGenDateTimeLocalDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_DATETIME_LOCAL")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Jus`
- L459-462 _private method_ `private static bool LocGenDateTimeUtcDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_DATETIME_UTC")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justi`
- L467-470 _private method_ `private static bool LocGenDateTimeCustomLocalDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_DATETIME_CUSTOM_LOCAL")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused paramete`
- L475-478 _private method_ `private static bool LocGenDateTimeCustomUtcDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_DATETIME_CUSTOM_UTC")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter"`
- L482-485 _private method_ `private static bool LocGenToUpperDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_TOUPPER")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- L489-492 _private method_ `private static bool LocGenToLowerDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)` — attrs: `[UhtLocTextDefaultValue(Name = "LOCGEN_TOLOWER")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]`
- L496-500 _private method_ `private static bool SanitizeDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue, bool allowNumerics)`
- L502-539 _private method_ `private static bool SanitizeDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken token, StringBuilder innerDefaultValue, bool allowNumerics)`
- L541-574 _private method_ `private static void FormatDecimal(ref UhtToken token, StringBuilder innerDefaultValue)`
- L576-588 _private method_ `private static void FormatFloat(ref UhtToken token, StringBuilder innerDefaultValue)`
- L598-706 _private method_ `private static bool LocGenNumberOrPercentDefaultValue(IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue, NumberStyle numberStyle)`
- L708-715 _private method_ `private static void FormatDateTimeStyle(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)`
- L717-782 _private method_ `private static bool LocGenDateTimeDefaultValue(IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue, bool isDate, bool isTime, bool isUtc, bool isCustom)`
- L784-795 _private method_ `private static bool LocGenTransformDefaultValue(UhtTextProperty property, IUhtTokenReader defaultValueReader, ref UhtToken macroToken, StringBuilder innerDefaultValue)`

#### enum `EpicGames.UHT.Types.UhtTextProperty.NumberStyle`  
`enum NumberStyle`  
_private*; L590-596_
- L592 _public* enumerator_ `None`
- L593 _public* enumerator_ `Grouped`
- L594 _public* enumerator_ `Ungrouped`
- L595 _public* enumerator_ `Custom`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtUInt16Property.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtUInt16Property`  
`public class UhtUInt16Property : UhtNumericProperty`  
_public; L17-85_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "UInt16Property", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FUInt16Property
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L29 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L35-37 _public ctor_ `public UhtUInt16Property(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L44-46 _public ctor_ `public UhtUInt16Property(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L52-55 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L58-61 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L64-67 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L73-83 _private method_ `private static UhtProperty? UInt16Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "uint16", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppre`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtUInt32Property.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtUInt32Property`  
`public class UhtUInt32Property : UhtNumericProperty`  
_public; L17-95_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "UInt32Property", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FUInt32Property
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L29 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L35-38 _public ctor_ `public UhtUInt32Property(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L45-47 _public ctor_ `public UhtUInt32Property(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L53-56 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L59-62 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L65-68 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L74-84 _private method_ `private static UhtProperty? UInt32Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "uint32", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppre`
- L90-93 _private method_ `private static UhtUInt32Property? UnsignedProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "unsigned", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [UhtPropertyType(Keyword = "unsigned int", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [Sup`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtUInt64Property.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtUInt64Property`  
`public class UhtUInt64Property : UhtNumericProperty`  
_public; L17-85_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "UInt64Property", IsProperty = true)]`
- inherits: `UhtNumericProperty`
- desc: FUInt64Property
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L29 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L35-37 _public ctor_ `public UhtUInt64Property(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L44-46 _public ctor_ `public UhtUInt64Property(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L52-55 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L58-61 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L64-67 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L73-83 _private method_ `private static UhtProperty? UInt64Property(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "uint64", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppre`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtUtf8StrProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtUtf8StrProperty`  
`public class UhtUtf8StrProperty : UhtProperty`  
_public; L19-141_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "Utf8StrProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FUtf8StrProperty
- L22 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L25 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L28 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L31 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L34 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L37 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L43-48 _public ctor_ `public UhtUtf8StrProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L55-57 _public ctor_ `public UhtUtf8StrProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L63-66 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L69-73 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L76-81 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L84-87 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L90-104 _protected method_ `protected override void ValidateFunctionArgument(UhtFunction function, UhtValidationOptions options)` — (inheritdoc)
- L109-140 _private method_ `private static UhtUtf8StrProperty? Utf8StrProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FUtf8String")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtVerseCellProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtVerseCellProperty`  
`public class UhtVerseCellProperty : UhtProperty`  
_public; L17-123_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "VerseCellProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FVCellProperty
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L29 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L32 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L35 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L40 _public property_ `public string Cell { get; set; }` — Referenced VCell type
- L47-50 _public ctor_ `public UhtVerseCellProperty(UhtPropertySettings propertySettings, string type) : base(propertySettings)` — Construct a new property
- L57-60 _public ctor_ `public UhtVerseCellProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L66-70 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L73-76 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L79-83 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L86-89 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L92-95 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L101-122 _private method_ `private static UhtVerseCellProperty? VerseProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "Verse::TWriteBarrier", Options = UhtPropertyTypeOptions.Immediate)] [UhtPropertyType(Keyword = "TWriteBarrier", Options = UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused `

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtVerseClassProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtVerseClassProperty`  
`public class UhtVerseClassProperty : UhtClassProperty`  
_public; L15-100_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "VerseClassProperty", IsProperty = true)]`
- inherits: `UhtClassProperty`
- desc: FVerseClassProperty
- L18 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L21 _public property_ `public override bool CodeGenWrapInRestValue => ...` — (inheritdoc)
- L30-37 _public ctor_ `public UhtVerseClassProperty(UhtPropertySettings propertySettings, UhtObjectCppForm cppForm, UhtClass referencedClass, EPropertyFlags extraFlags = EPropertyFlags.None) : base(new UhtNoValidateConstruct { }, propertySettings, cppForm, referencedClass, extraFlags)` — Construct a new property
- L44-46 _public ctor_ `public UhtVerseClassProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L52-55 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L58-64 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L67-73 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L79-86 _protected method_ `protected string RequiresConcreteValue()` — Returns either "true" or "false" if the type is a concrete type
- L92-99 _protected method_ `protected string RequiresCastableValue()` — Returns either "true" or "false" if the type is a castable type

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtVerseStringProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtVerseStringProperty`  
`public class UhtVerseStringProperty : UhtProperty`  
_public; L19-172_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "VerseStringProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FVerseStringProperty
- L25 _public property_ `public UhtProperty CharTypeProperty { get; init; }` — Defines the type of embedded character type. Currently only u8 is used.
- L28 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L31 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L34 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L37 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L40 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L43 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L49-57 _public ctor_ `public UhtVerseStringProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L64-67 _public ctor_ `public UhtVerseStringProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L73-77 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L80-93 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L96-99 _protected method_ `protected override bool NeedsGCBarrierWhenPassedToFunctionImpl(UhtFunction function)` — (inheritdoc)
- L102-106 _public method_ `public override void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — (inheritdoc)
- L109-112 _public method_ `public override bool ScanForInstancedReferenced(bool deepScan)` — (inheritdoc)
- L115-118 _public method_ `public override bool IsAllowedInOptionalClass([NotNullWhen(false)] out string? propPath)` — (inheritdoc)
- L121-127 _public method_ `public override IEnumerable<UhtType> EnumerateReferencedTypes()` — (inheritdoc)
- L130-134 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L137-140 _public method_ `public override IEnumerable<UhtChildProperty> EnumerateChildProperties(UhtCppIdentifier identifier, UhtChildPropertyOrder order)` — (inheritdoc)
- L143-146 _public method_ `public override void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — (inheritdoc)
- L149-152 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L155-162 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L168-171 _private method_ `private static UhtVerseStringProperty? VerseStringProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "verse::string", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [UhtPropertyType(Keyword = "FVerseString", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)]`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtVerseValueProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtVerseValueProperty`  
`public class UhtVerseValueProperty : UhtProperty`  
_public; L17-92_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "VerseValueProperty", IsProperty = true)]`
- inherits: `UhtProperty`
- desc: FVerseValueProperty
- L21 _public property_ `public override string EngineClassName => ...`
- L24 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L27 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L30 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L33 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L36 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L42-45 _public ctor_ `public UhtVerseValueProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new property
- L52-54 _public ctor_ `public UhtVerseValueProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L60-63 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L66-70 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L73-76 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L79-82 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L87-91 _private method_ `private static UhtVerseValueProperty? VerseProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "FVerseValue", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [S`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtVoidProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtVoidProperty`  
`public class UhtVoidProperty : UhtProperty`  
_public; L17-92_
- attrs: `[UnrealHeaderTool]`
- inherits: `UhtProperty`
- desc: Internal only void property for void return types
- L20 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L23 _protected property_ `protected override string CppTypeText => ...` — (inheritdoc)
- L26 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L32-34 _public ctor_ `public UhtVoidProperty(UhtPropertySettings propertySettings) : base(propertySettings)` — Construct a new void property
- L41-43 _public ctor_ `public UhtVoidProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L49-52 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L55-58 _public method_ `public override StringBuilder AppendFunctionThunkParameterGet(StringBuilder builder)` — (inheritdoc)
- L61-64 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L67-70 _public method_ `public override bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — (inheritdoc)
- L73-76 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L82-90 _private method_ `private static UhtVoidProperty? VoidProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "void", Options = UhtPropertyTypeOptions.Simple | UhtPropertyTypeOptions.Immediate)] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [Suppress`

### `Source/Programs/Shared/EpicGames.UHT/Types/Properties/UhtWeakObjectPtrProperty.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtWeakObjectPtrProperty`  
`public class UhtWeakObjectPtrProperty : UhtObjectPropertyBase`  
_public; L20-163_
- attrs: `[UnrealHeaderTool] [UhtEngineClass(Name = "WeakObjectProperty", IsProperty = true)]`
- inherits: `UhtObjectPropertyBase`
- desc: Represents a FWeakObjectProperty
- L23 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L26 _protected property_ `protected override string PGetMacroText => ...` — (inheritdoc)
- L29 _protected property_ `protected override bool PGetPassAsNoPtr => ...` — (inheritdoc)
- L32 _protected property_ `protected override UhtPGetArgumentType PGetTypeArgument => ...` — (inheritdoc)
- L35 _protected property_ `protected override string CodeGenParamsStruct => ...` — (inheritdoc)
- L38 _protected property_ `protected override string CodeGenParamsFlags => ...` — (inheritdoc)
- L46-52 _public ctor_ `public UhtWeakObjectPtrProperty(UhtPropertySettings propertySettings, UhtClass propertyClass, EPropertyFlags extraFlags = EPropertyFlags.None) : base(new UhtNoValidateConstruct { }, propertySettings, UhtObjectCppForm.NativeObject, propertyClass)` — Construct a new property
- L59-61 _public ctor_ `public UhtWeakObjectPtrProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L67-70 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L73-89 _public method_ `public override StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument)` — (inheritdoc)
- L92-95 _protected method_ `protected override StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L98-101 _protected method_ `protected override StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — (inheritdoc)
- L104-108 _public method_ `public override StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — (inheritdoc)
- L111-118 _public method_ `public override bool IsSameType(UhtProperty other)` — (inheritdoc)
- L121-133 _private method_ `private static UhtProperty CreateWeakProperty(UhtPropertySettings propertySettings, IUhtTokenReader tokenReader, UhtClass classObj, EPropertyFlags extraFlags = EPropertyFlags.None)`
- L138-147 _private method_ `private static UhtProperty? WeakObjectProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TWeakObjectPtr")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification `
- L152-161 _private method_ `private static UhtProperty? AutoWeakObjectProperty(UhtPropertyResolveArgs args)` — attrs: `[UhtPropertyType(Keyword = "TAutoWeakObjectPtr")] [SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")] [SuppressMessage("Style", "IDE0060:Remove unused parameter", Justificat`

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtClass.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtClassExportFlags`  
`public enum UhtClassExportFlags : int`  
_public; L22-110_
- attrs: `[Flags]`
- inherits: `int`
- desc: Series of flags not part of the engine's class flags that affect code generation or verification
- L28 _public* enumerator_ `None = 0` — No export flags
- L33 _public* enumerator_ `SelfHasReplicatedProperties = 1 << 0` — If set, the class itself has replicated properties.
- L38 _public* enumerator_ `SuperHasReplicatedProperties = 1 << 1` — If set, some super class has replicated properties.
- L43 _public* enumerator_ `HasReplciatedProperties = SelfHasReplicatedProperties | SuperHasReplicatedProperties` — If set, either the class itself or a super class has replicated properties
- L48 _public* enumerator_ `HasCustomConstructor = 1 << 2` — Custom constructor specifier present
- L53 _public* enumerator_ `HasDefaultConstructor = 1 << 3` — A default constructor was found in the class
- L58 _public* enumerator_ `HasObjectInitializerConstructor = 1 << 4` — An object initializer constructor was found in the class
- L63 _public* enumerator_ `HasCustomVTableHelperConstructor = 1 << 5` — A custom vtable helper constructor was found
- L68 _public* enumerator_ `HasConstructor = 1 << 6` — A constructor was found
- L73 _public* enumerator_ `HasGetLifetimeReplicatedProps = 1 << 7` — GetLifetimeReplicatedProps was found in the class
- L78 _public* enumerator_ `NoExport = 1 << 8` — Class should not be exported
- L83 _public* enumerator_ `HasCustomFieldNotify = 1 << 9` — Class has a custom field notify
- L88 _public* enumerator_ `HasFieldNotify = 1 << 10` — Class has a field notify
- L93 _public* enumerator_ `HasDestructor = 1 << 11` — Class has destructor
- L99 _public* enumerator_ `UsesGeneratedBodyLegacy = 1 << 12` — The GENERATED_UCLASS_BODY, GENERATED_UINTERFACE_BODY, and GENERATED_IINTERFACE_BODY macros use the legacy generated body. If this flag is set, generate the legacy instead of the GENERATED_BODY macros.
- L104 _public* enumerator_ `Final = 1 << 13` — Class is marked as final
- L109 _public* enumerator_ `VerseIsRootModule = 1 << 14` — Class is a verse root module.

#### class `EpicGames.UHT.Types.UhtClassExportFlagsExtensions`  
`public static class UhtClassExportFlagsExtensions`  
_public; L116-152_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L125-128 _public method_ `public static bool HasAnyFlags(this UhtClassExportFlags inFlags, UhtClassExportFlags testFlags)` — Test to see if any of the specified flags are set
- L136-139 _public method_ `public static bool HasAllFlags(this UhtClassExportFlags inFlags, UhtClassExportFlags testFlags)` — Test to see if all of the specified flags are set
- L148-151 _public method_ `public static bool HasExactFlags(this UhtClassExportFlags inFlags, UhtClassExportFlags testFlags, UhtClassExportFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtClassType`  
`public enum UhtClassType`  
_public; L157-178_
- desc: Type of the class
- L162 _public* enumerator_ `Class` — Class is a UCLASS
- L167 _public* enumerator_ `Interface` — Class is a UINTERFACE
- L172 _public* enumerator_ `NativeInterface` — Class is the native interface for a UINTERFACE
- L177 _public* enumerator_ `VModule` — Class is an implementation detail for a Verse module

#### enum `EpicGames.UHT.Types.UhtSerializerArchiveType`  
`public enum UhtSerializerArchiveType`  
_public; L184-206_
- attrs: `[Flags]`
- desc: Type of archive serializer found
- L190 _public* enumerator_ `None = 0` — No serializer found
- L195 _public* enumerator_ `Archive = 1 << 0` — Archive serializer found
- L200 _public* enumerator_ `StructuredArchiveRecord = 1 << 1` — Structured archive serializer found
- L205 _public* enumerator_ `All = Archive | StructuredArchiveRecord` — Mask of all serializer types

#### class `EpicGames.UHT.Types.UhtSerializerArchiveTypeExtensions`  
`public static class UhtSerializerArchiveTypeExtensions`  
_public; L212-248_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L221-224 _public method_ `public static bool HasAnyFlags(this UhtSerializerArchiveType inFlags, UhtSerializerArchiveType testFlags)` — Test to see if any of the specified flags are set
- L232-235 _public method_ `public static bool HasAllFlags(this UhtSerializerArchiveType inFlags, UhtSerializerArchiveType testFlags)` — Test to see if all of the specified flags are set
- L244-247 _public method_ `public static bool HasExactFlags(this UhtSerializerArchiveType inFlags, UhtSerializerArchiveType testFlags, UhtSerializerArchiveType matchFlags)` — Test to see if a specific set of flags have a specific value.

#### struct `EpicGames.UHT.Types.UhtDeclaration`  
`public struct UhtDeclaration`  
_public; L253-294_
- desc: A skipped declaration
- L259 _public property_ `public UhtCompilerDirective CompilerDirectives { get; set; }` — Compiler directives when declaration was parsed
- L266 _public field_ `public UhtToken[] Tokens` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1051:Do not declare visible instance fields", Justification = "<Pending>")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "<P` — Collection of tokens parsed in the declaration
- L271 _public property_ `public UhtFunction? Function { get; set; }` — If this declaration is part of a UFUNCTION, this will be set
- L277-282 _public ctor_ `public UhtDeclaration(UhtInputCacheReader reader)` — Construct a type from the cache
- L288-293 _public method_ `public readonly void Write(UhtInputCacheWriter writer)` — Write the output type

#### struct `EpicGames.UHT.Types.UhtFoundDeclaration`  
`public struct UhtFoundDeclaration`  
_public; L299-323_
- desc: Represents a declaration found by name
- L305 _public property_ `public UhtCompilerDirective CompilerDirectives { get; set; }` — Compiler directives when declaration was parsed
- L312 _public field_ `public UhtToken[] Tokens` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1051:Do not declare visible instance fields", Justification = "<Pending>")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "<P` — Collection of tokens parsed in the declaration
- L317 _public property_ `public int NameTokenIndex { get; set; }` — Token index for the matching name
- L322 _public property_ `public bool IsVirtual { get; set; }` — True if "virtual" was found prior to the matching name

#### class `EpicGames.UHT.Types.UhtClass`  
`public class UhtClass : UhtStruct`  
_public; L329-2413_
- attrs: `[UhtEngineClass(Name = "Class")]`
- inherits: `UhtStruct`
- desc: Instance of a UCLASS, UINTERFACE, or a native interface
- L331 _private field_ `private List<UhtDeclaration>? _declarations = null`
- L336 _public property_ `public string Config { get; set; }` — Configuration section
- L342 _public property_ `public UhtDefineScope SerializerDefineScope { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — If needed, the #if block define for the serializer
- L348 _public property_ `public UhtClass ClassWithin { get; set; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtClass>))]` — The class within
- L356 _public property_ `public EClassFlags ClassFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Class flags used to populate UMyClass::StaticClassFlags. Note that these may be different to those in the instance field UClass::ClassFlags which does not respect removing class flags in a derived class.
- L362 _public property_ `public EClassCastFlags ClassCastFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Class cast flags
- L368 _public property_ `public UhtClassExportFlags ClassExportFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Export flags not present in the engine
- L374 _public property_ `public UhtClassType ClassType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Type of the class
- L380 _public property_ `public UhtSerializerArchiveType SerializerArchiveType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Type of archivers present
- L385 _public property_ `public int PrologLineNumber { get; set; }` — Line number of the prolog
- L391 _public property_ `public IList<UhtDeclaration>? Declarations => ...` — attrs: `[JsonIgnore]` — Collection of functions and other declarations found in the class
- L397 _public property_ `public UhtClass? NativeInterface { get; set; }` — attrs: `[JsonIgnore]` — If this, this class is a UINTERFACE and NativeInterface is the associated native interface
- L402 _public property_ `public int GeneratedBodyLineNumber { get; set; }` — Line number o the generated body statement
- L408 _public property_ `public UhtAccessSpecifier GeneratedBodyAccessSpecifier { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Access of the generated body
- L413 _public property_ `public bool HasGeneratedBody { get; set; }` — True if GENERATED_BODY was used. If false, GENERATED_UCLASS_BODY was used.
- L419 _public property_ `public EClassFlags RemovedClassFlags { get; set; }` — Engine class flags removed
- L425 _public property_ `public string ClassWithinIdentifier { get; set; }` — attrs: `[JsonIgnore]` — Class within identifier
- L431 _public property_ `public List<string> ShowCategories { get; }` — attrs: `[JsonIgnore]` — Collection of show categories
- L437 _public property_ `public List<string> HideCategories { get; }` — attrs: `[JsonIgnore]` — Collection of hide categories
- L443 _public property_ `public List<string> AutoExpandCategories { get; }` — attrs: `[JsonIgnore]` — Collection of auto expand categories
- L449 _public property_ `public List<string> AutoCollapseCategories { get; }` — attrs: `[JsonIgnore]` — Collection of auto collapse categories
- L455 _public property_ `public List<string> PrioritizeCategories { get; }` — attrs: `[JsonIgnore]` — Collection of prioritize categories
- L461 _public property_ `public List<string> ShowFunctions { get; }` — attrs: `[JsonIgnore]` — Collection of show functions
- L467 _public property_ `public List<string> HideFunctions { get; }` — attrs: `[JsonIgnore]` — Collection of hide functions
- L473 _public property_ `public List<string> SparseClassDataTypes { get; }` — attrs: `[JsonIgnore]` — Sparse class data types
- L479 _public property_ `public List<string> ClassGroupNames { get; }` — attrs: `[JsonIgnore]` — Class group names
- L484 _public property_ `public UhtDefineScopeLink<UhtFunction>? FirstFunction { get; set; }` — After functions are fully resolved, points to the first non-delegate function in this class
- L490-494 _public method_ `public void AddClassFlags(EClassFlags flags)` — Add the given class flags
- L500-504 _public method_ `public void RemoveClassFlags(EClassFlags flags)` — Remove the given class flags
- L509-526 _public property_ `public override UhtEngineType EngineType { get; }` — attrs: `[JsonIgnore]` — (inheritdoc)
- L529 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L532 _public property_ `public override string EngineLinkClassName => ...` — (inheritdoc)
- L535 _public property_ `public override UhtClass? EngineClass => ...` — (inheritdoc)
- L537 _private field_ `private string? _nativeFunctionCallName`
- L542 _public property_ `public string NativeFunctionCallName => ...` — The name used to scope native function calls into this type e.g. UClassName or IInterfaceName
- L551 _public property_ `public override bool Deprecated => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L555-573 _protected property_ `protected override UhtSpecifierValidatorTable? SpecifierValidatorTable { get; }` — attrs: `[JsonIgnore]` — (inheritdoc)
- L579 _public property_ `public UhtClass? SuperClass => ...` — attrs: `[JsonConverter(typeof(UhtNullableTypeSourceNameJsonConverter<UhtClass>))]` — The super class
- L585 _public property_ `public bool IsActorClass => ...` — attrs: `[JsonIgnore]` — True if this class inherits from AActor
- L589-622 _public property_ `public override string EngineNamePrefix { get; }` — attrs: `[JsonIgnore]` — (inheritdoc)
- L627 _public property_ `public int VerseInterfacesLine { get; set; }` — Line number containing the VINTERFACES macro
- L633 _public property_ `public IReadOnlyList<UhtClass> VerseInterfaces => ...` — attrs: `[JsonConverter(typeof(UhtTypeReadOnlyListSourceNameJsonConverter<UhtClass>))]` — Verse interfaces directly specified on the interface definition
- L639 _public property_ `public IReadOnlyList<UhtClass> FlattenedVerseInterfaces => ...` — attrs: `[JsonConverter(typeof(UhtTypeReadOnlyListSourceNameJsonConverter<UhtClass>))]` — Flattened collection of all verse interfaces.
- L646 _public property_ `public List<UhtToken[]>? VerseInterfaceIdentifiers { get; set; }` — attrs: `[JsonIgnore] [SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "<Pending>")]` — List of all verse interfaces implemented by this interface
- L648 _private field_ `private static readonly List<UhtClass> s_emptyVerseInterfaces = []`
- L649 _private field_ `private List<UhtClass>? _verseInterfaces = null`
- L650 _private field_ `private List<UhtClass>? _flattenedVerseInterfaces = null`
- L659-662 _public ctor_ `public UhtClass(UhtHeaderFile headerFile, UhtNamespace namespaceObj, UhtType outer, int lineNumber) : base(headerFile, namespaceObj, outer, lineNumber)` — Construct a new instance of the class
- L669-697 _public ctor_ `public UhtClass(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L703-731 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L739-743 _public method_ `public void AddDeclaration(UhtCompilerDirective compilerDirectives, List<UhtToken> tokens, UhtFunction? function)` — Add the given list of tokens as a possible declaration
- L751-787 _public method_ `public bool TryGetDeclaration(string name, out UhtFoundDeclaration foundDeclaration)` — Search the declarations for a possible declaration match with the given name
- L794-804 _public method_ `public bool HierarchyHasAnyClassFlags(EClassFlags flagsToCheck)` — Checks to see if the class or any super class has the given flags.
- L815-824 _public method_ `public override void BindSuperAndBases()` — (inheritdoc)
- L827-1003 _protected method_ `protected override void ResolveSuper(UhtResolvePhase resolvePhase)` — (inheritdoc)
- L1005-1018 _private method_ `private void ValidateVerseInterfaces()`
- L1025-1032 _public method_ `public string GetNativeInterfaceName()` — Return the native interface name from an interface
- L1039-1046 _public method_ `public string GetInterfaceName()` — Return the interface name from a native interface
- L1049-1286 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L1289-1303 _protected method_ `protected override void ResolveChildren(UhtResolvePhase phase)` — (inheritdoc)
- L1308-1331 _protected method_ `protected void LinkFunctions()` — Create a linked list of functions across preprocessor definition changes
- L1334-1347 _protected method_ `protected override bool ScanForInstancedReferencedInternal(bool deepScan)` — (inheritdoc)
- L1349-1381 _private method_ `private void MergeCategories()`
- L1383-1422 _private method_ `private void MergeShowCategories()`
- L1424-1467 _private method_ `private void SetAndValidateWithinClass(UhtResolvePhase resolvePhase)`
- L1469-1521 _private method_ `private void SetAndValidateConfigName()`
- L1523-1528 _private method_ `private static List<string> GetStringListMetaData(UhtType? type, string key)`
- L1530-1545 _private method_ `private static void AppendStringListMetaData(UhtType? type, string key, List<string> stringList)`
- L1548-1551 _public method_ `public override StringBuilder AppendForwardDeclaration(StringBuilder builder)` — (inheritdoc)
- L1561-1774 _private method_ `private static bool TryMatchGetterSetter(UhtProperty property, bool setter, UhtDeclaration declaration, int nameIndex)` — Given a token stream, verify that it matches the expected signature for a getter/setter
- L1784-1794 _private method_ `private static Dictionary<string, List<GetterSetterToResolve>> AddGetterSetter(Dictionary<string, List<GetterSetterToResolve>>? gsToResolve, string name, UhtProperty property, bool setter)` — Add a requested getter/setter function name
- L1799-2060 _protected method_ `protected override UhtValidationOptions Validate(UhtValidationOptions options)` — (inheritdoc)
- L2062-2090 _private* method_ `static void ValidateBlueprintPopertyGetter(UhtProperty property, string functionName, UhtFunction? targetFunction)`
- L2092-2124 _private* method_ `static void ValidateBlueprintPopertySetter(UhtProperty property, string functionName, UhtFunction? targetFunction)`
- L2126-2172 _private* method_ `static void ValidateRepNotifyCallback(UhtProperty property, string functionName, UhtFunction? targetFunction)`
- L2174-2257 _private* method_ `void ValidateProperties()`
- L2264-2267 _private method_ `private bool CanImplementInBlueprints()` — Interface with blueprint data should declare explicitly Blueprintable or NotBlueprintable to be clear In the backward compatible case where they declare neither, both of these bools are false
- L2274-2277 _private method_ `private bool CannotImplementInBlueprints()` — Interface with blueprint data should declare explicitly Blueprintable or NotBlueprintable to be clear In the backward compatible case where they declare neither, both of these bools are false
- L2285-2289 _private method_ `private bool CannotImplementInBlueprints(bool canImplementInBlueprints)` — Interface with blueprint data should declare explicitly Blueprintable or NotBlueprintable to be clear In the backward compatible case where they declare neither, both of these bools are false
- L2293-2375 _public method_ `public override void CollectReferences(IUhtReferenceCollector collector)` — (inheritdoc)
- L2377-2390 _private method_ `private bool ImplementsInterface(UhtClass interfaceObj)`
- L2392-2412 _private method_ `private void BindVerseInterfaces()`

#### struct `EpicGames.UHT.Types.UhtClass.GetterSetterToResolve`  
`struct GetterSetterToResolve`  
_private*; L807-812_
- L809 _public property_ `public UhtProperty Property { get; set; }`
- L810 _public property_ `public bool Setter { get; set; }`
- L811 _public property_ `public bool Found { get; set; }`

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtEnum.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtEnumCppForm`  
`public enum UhtEnumCppForm`  
_public; L19-35_
- desc: How the enumeration was declared Must match UEnum::ECppForm
- L24 _public* enumerator_ `Regular` — enum Name {...}
- L29 _public* enumerator_ `Namespaced` — namespace Name { enum Type { ... } }
- L34 _public* enumerator_ `EnumClass` — enum class Name {...}

#### enum `EpicGames.UHT.Types.UhtEnumUnderlyingType`  
`public enum UhtEnumUnderlyingType`  
_public; L41-93_
- desc: Underlying type of the enumeration Match with UEnum::EUnderlyingType
- L47 _public* enumerator_ `Unspecified` — Not specified
- L52 _public* enumerator_ `Uint8` — Uint8
- L57 _public* enumerator_ `Uint16` — Uint16
- L62 _public* enumerator_ `Uint32` — Uint32
- L67 _public* enumerator_ `Uint64` — Uint64
- L72 _public* enumerator_ `Int8` — Int8
- L77 _public* enumerator_ `Int16` — Int16
- L82 _public* enumerator_ `Int32` — Int32
- L87 _public* enumerator_ `Int64` — Int64
- L92 _public* enumerator_ `Int` — Int

#### struct `EpicGames.UHT.Types.UhtEnumValue`  
`public struct UhtEnumValue`  
_public; L98-129_
- desc: Represents an enumeration value
- L103 _public property_ `public string Name { get; set; }` — Name of the enumeration value
- L108 _public property_ `public long Value { get; set; }` — Value of the enumeration or -1 if not parsed.
- L114-118 _public ctor_ `public UhtEnumValue(UhtInputCacheReader reader)` — Construct a type from the cache
- L124-128 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write the output type

#### enum `EpicGames.UHT.Types.UhtEnumExportFlags`  
`public enum UhtEnumExportFlags : int`  
_public; L135-147_
- attrs: `[Flags]`
- inherits: `int`
- desc: Series of flags not part of the engine's enum flags that affect code generation or verification
- L141 _public* enumerator_ `None = 0` — No export flags
- L146 _public* enumerator_ `MinimalAPI = 1 << 0` — Indicates that the StaticEnum function should be exported to other modules

#### class `EpicGames.UHT.Types.UhtEnumExportFlagsExtensions`  
`public static class UhtEnumExportFlagsExtensions`  
_public; L153-189_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L162-165 _public method_ `public static bool HasAnyFlags(this UhtEnumExportFlags inFlags, UhtEnumExportFlags testFlags)` — Test to see if any of the specified flags are set
- L173-176 _public method_ `public static bool HasAllFlags(this UhtEnumExportFlags inFlags, UhtEnumExportFlags testFlags)` — Test to see if all of the specified flags are set
- L185-188 _public method_ `public static bool HasExactFlags(this UhtEnumExportFlags inFlags, UhtEnumExportFlags testFlags, UhtEnumExportFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Types.UhtEnum`  
`public class UhtEnum : UhtField, IUhtMetaDataKeyConversion`  
_public; L195-609_
- attrs: `[UhtEngineClass(Name = "Enum")]`
- inherits: `UhtField, IUhtMetaDataKeyConversion`
- desc: Represents a UEnum
- L201 _public property_ `public EEnumFlags EnumFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Engine enumeration flags
- L207 _public property_ `public UhtEnumExportFlags EnumExportFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — UHT only script struct flags
- L213 _public property_ `public UhtEnumCppForm CppForm { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — C++ form of the enumeration
- L219 _public property_ `public UhtEnumUnderlyingType UnderlyingType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Underlying integer enumeration type
- L224 _public property_ `public string CppType { get; set; }` — Full enumeration type. For namespace enumerations, this includes the namespace name and the enum type name
- L229 _public property_ `public string FullyQualifiedCppType => ...` — Fully qualified cpp type name. Include enclosing namespace as well as CppType (which may include enum's own namespace)
- L230 _private field_ `private string? _fullyQualifiedCppType = null`
- L235 _public property_ `public List<UhtEnumValue> EnumValues { get; }` — Collection of enumeration values
- L241 _public property_ `public string? GeneratedMaxName { get; set; }` — If header didn't declare a max value, this is a generated name to be appended to the list of names in reflection data. This is a full name as returned by GetFullEnumName i.e. it may be namespaced.
- L246 _public property_ `public long? GeneratedMaxValue { get; set; }` — If header didn't declare a max value, and UHT was able to parse all values, this the value for GeneratedMaxName
- L250 _public property_ `public override UhtEngineType EngineType => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L253 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L256 _public property_ `public override string EngineLinkClassName => ...` — (inheritdoc)
- L259 _public property_ `public override UhtClass EngineClass => ...` — (inheritdoc)
- L263 _protected property_ `protected override UhtSpecifierValidatorTable? SpecifierValidatorTable => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L272-276 _public ctor_ `public UhtEnum(UhtHeaderFile headerFile, UhtNamespace namespaceObj, UhtType outer, int lineNumber) : base(headerFile, namespaceObj, outer, lineNumber)` — Construct a new enumeration
- L283-292 _public ctor_ `public UhtEnum(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L298-307 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L310-325 _public method_ `public override StringBuilder AppendForwardDeclaration(StringBuilder builder)` — (inheritdoc)
- L328-371 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L378-388 _public method_ `public bool IsValidEnumValue(long value)` — Test to see if the value is a known enum value
- L395-406 _public method_ `public int GetIndexByName(string name)` — Return the index of the given enumeration value name
- L414-426 _public method_ `public string GetMetaDataKey(string name, int nameIndex)` — Converts meta data name and index to a full meta data key name
- L434-448 _public method_ `public string GetFullEnumName(string shortEnumName)` — Given an enumeration value name, return the full enumeration name
- L455-470 _public method_ `public string GetShortEnumName(string longEnumName)` — Return the enum name without any namespacing
- L480-534 _private method_ `private string GenerateEnumPrefix()` — Return a prefix common to all members of this enumeration, or the enum name, without a trailing underscore. This should return the same strings as UEnum::GenerateEnumPrefix. Note that UEnum::GenerateEnumPrefix generates some surprising results, such as giving a namespaced enum such as ESomeEnum_WithUnderScore whose short names share no prefix the prefix ESomeEnum_, giving the generated max name of ESomeEnum_WithUnderScore::ESomeEnum_MAX
- L542-547 _public method_ `public int AddEnumValue(string shortEnumName, long value)` — Add a new enum value.
- L555-559 _private method_ `private string CleanEnumValueName(string name)` — Reconstruct the full enum name. Any existing enumeration name will be stripped and replaced with this enumeration name.
- L563-596 _protected method_ `protected override void ValidateDocumentationPolicy(UhtDocumentationPolicy policy)` — (inheritdoc)
- L600-608 _public method_ `public override void CollectReferences(IUhtReferenceCollector collector)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtField.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtFieldExportFlags`  
`public enum UhtFieldExportFlags : int`  
_public; L15-27_
- attrs: `[Flags]`
- inherits: `int`
- desc: Series of flags not part of the engine's field flags that affect code generation or verification
- L21 _public* enumerator_ `None = 0` — No export flags
- L26 _public* enumerator_ `NoVerseAlias = 1 << 0` — Do not generate an alias in the verse namespace

#### class `EpicGames.UHT.Types.UhtFieldExportFlagsExtensions`  
`public static class UhtFieldExportFlagsExtensions`  
_public; L33-69_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L42-45 _public method_ `public static bool HasAnyFlags(this UhtFieldExportFlags inFlags, UhtFieldExportFlags testFlags)` — Test to see if any of the specified flags are set
- L53-56 _public method_ `public static bool HasAllFlags(this UhtFieldExportFlags inFlags, UhtFieldExportFlags testFlags)` — Test to see if all of the specified flags are set
- L65-68 _public method_ `public static bool HasExactFlags(this UhtFieldExportFlags inFlags, UhtFieldExportFlags testFlags, UhtFieldExportFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtVerseNameMode`  
`public enum UhtVerseNameMode`  
_public; L74-90_
- desc: Controls how the verse name is appended to the builder
- L79 _public* enumerator_ `Default` — Default mode
- L84 _public* enumerator_ `Qualified` — Fully qualified mode
- L89 _public* enumerator_ `PackageRelative` — Used to generate the name but not including the package. Unlike the default. '/' is used instead of '_'

#### class `EpicGames.UHT.Types.UhtField`  
`public abstract class UhtField : UhtObject`  
_public; L95-329_
- inherits: `UhtObject`
- desc: Represents a UField
- L98 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L104 _public property_ `public UhtFieldExportFlags FieldExportFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — UHT only field flags
- L109 _public property_ `public string? VerseModule { get; set; }` — Name of the module containing the type
- L115 _public property_ `public string? VerseName { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Naming", "CA1721:Property names should not match get methods", Justification = "<Pending>")]` — Cased name of the verse field
- L120 _public property_ `public bool IsVerseField => ...` — Returns true if field is a verse element
- L125 _public property_ `public UhtNamespace Namespace { get; set; }` — Namespace where the field was defined
- L130 _public property_ `public string FullyQualifiedSourceName => ...` — Fully qualified name of the field in source, i.e. Namespace and SourceName concatenated.
- L131 _private field_ `private string? _fullyQualifiedSourceName = null`
- L140-143 _protected ctor_ `protected UhtField(UhtHeaderFile headerFile, UhtNamespace namespaceObj, UhtType outer, int lineNumber) : base(headerFile, outer, lineNumber)` — Construct a new field
- L150-156 _protected ctor_ `protected UhtField(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L162-169 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L176-181 _public method_ `public string GetVerseScopeAndName(UhtVerseNameMode mode)` — Return the scope and name of the verse type (scope:)name
- L188-195 _public method_ `public string GetEncodedVerseScopeAndName(UhtVerseNameMode mode)` — Return the encoded verse scope and name of the field
- L202-207 _public method_ `public string GetVerseScope(UhtVerseNameMode mode)` — Return the verse scope of the field
- L214-219 _public method_ `public string GetVerseName(UhtVerseNameMode mode)` — Return the verse name of the field
- L226-249 _public method_ `public virtual void AppendVerseScopeAndName(StringBuilder builder, UhtVerseNameMode mode)` — Append the scope and name of the verse type (scope:)name
- L256-259 _public method_ `public void AppendVerseScope(StringBuilder builder, UhtVerseNameMode mode)` — Append the verse scope part to the given builder
- L268-294 _private method_ `private void AppendVerseScopeInternal(StringBuilder builder, UhtVerseNameMode mode, bool isTopLevel)` — Append the verse scope to the given builder
- L302-308 _protected method_ `protected virtual void AppendVerseMyScope(StringBuilder builder, UhtVerseNameMode mode, bool isTopLevel)` — Helper method that appends only this path contribution to the verse path.
- L315-318 _protected method_ `protected virtual void AppendVerseName(StringBuilder builder, UhtVerseNameMode mode)` — Helper method that appends only this instance contribution to the verse path.
- L325-328 _public method_ `public virtual StringBuilder AppendForwardDeclaration(StringBuilder builder)` — Append the field's forward declaration

#### class `EpicGames.UHT.Types.UhtFieldStringBuilderExtensions`  
`public static class UhtFieldStringBuilderExtensions`  
_public; L334-392_
- desc: Helper extension methods for fields
- L343-351 _public method_ `public static StringBuilder AppendVerseUEVNIPackageName(this StringBuilder builder, UhtField fieldObj)` — Append the Verse UE VNI package name
- L359-367 _public method_ `public static StringBuilder AppendVerseUEPackageName(this StringBuilder builder, UhtField fieldObj)` — Append the Verse UE package name (without a leading forward slash)
- L376-380 _public method_ `public static StringBuilder AppendVerseScopeAndName(this StringBuilder builder, UhtField fieldObj, UhtVerseNameMode mode)` — Append the scope and name of the verse type (scope:)name
- L388-391 _public method_ `public static StringBuilder AppendForwardDeclaration(this StringBuilder builder, UhtField fieldObj)` — Append the fields forward declaration

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtFunction.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtFunctionExportFlags`  
`public enum UhtFunctionExportFlags : int`  
_public; L21-155_
- attrs: `[Flags]`
- inherits: `int`
- desc: Series of flags not part of the engine's function flags that affect code generation or verification
- L27 _public* enumerator_ `None = 0` — No export flags
- L32 _public* enumerator_ `Final = 1 << 0` — Function declaration included "final" keyword. Used to differentiate between functions that have FUNC_Final only because they're private
- L37 _public* enumerator_ `RequiredAPI = 1 << 1` — Function should be exported as a public API function
- L42 _public* enumerator_ `Inline = 1 << 2` — Export as an inline static C++ function
- L47 _public* enumerator_ `CppStatic = 1 << 3` — Export as a real C++ static function, causing thunks to call via ClassName::FuncName instead of this->FuncName
- L52 _public* enumerator_ `CustomThunk = 1 << 4` — Export no thunk function; the user will manually define a custom one
- L57 _public* enumerator_ `Virtual = 1 << 5` — Function is marked as virtual
- L62 _public* enumerator_ `Unreliable = 1 << 6` — The unreliable specified was present
- L67 _public* enumerator_ `SealedEvent = 1 << 7` — The function is a sealed event
- L72 _public* enumerator_ `ForceBlueprintImpure = 1 << 8` — Blueprint pure is being forced to false
- L77 _public* enumerator_ `AutoBlueprintPure = 1 << 9` — If set, the BlueprintPure was automatically set
- L83 _public* enumerator_ `ImplFound = 1 << 10` — If set, a method matching the CppImplName was found. The search is only performed if it differs from the function name.
- L88 _public* enumerator_ `ImplVirtual = 1 << 11` — If the ImplFound flag is set, then if this flag is set, the method is virtual
- L94 _public* enumerator_ `ValidationImplFound = 1 << 12` — If set, a method matching the CppValidationImplName was found. The search is only performed if CppImplName differs from the function name
- L99 _public* enumerator_ `ValidationImplVirtual = 1 << 13` — If the ValidationImplFound flag is set, then if this flag is set, the method id virtual.
- L104 _public* enumerator_ `DeclaredConst = 1 << 14` — Set true if the function itself is declared const. The is required for the automatic setting of BlueprintPure.
- L109 _public* enumerator_ `AutoFinal = 1 << 15` — Final flag was set automatically and should not be considered for validation
- L114 _public* enumerator_ `FieldNotify = 1 << 16` — Generate the entry for the FieldNotificationClassDescriptor
- L119 _public* enumerator_ `SawPropertyAccessor = 1 << 17` — True if the function specifier has a getter/setter specified
- L124 _public* enumerator_ `VerseNativeCallable = 1 << 18` — True if the function is verse function callable from native code
- L129 _public* enumerator_ `VerseDecides = 1 << 19` — True if the function is a decides function
- L134 _public* enumerator_ `VerseSuspends = 1 << 20` — True if the return value is wrapped with TVerseTask
- L139 _public* enumerator_ `VerseCallable = 1 << 21` — Function can be called from verse
- L144 _public* enumerator_ `VerseNoRollback = 1 << 22` — True if the function is a no_rollback function
- L149 _public* enumerator_ `VerseRTFMAlwaysOpen = 1 << 23` — True if the function is marked as rtfm_always_open
- L154 _public* enumerator_ `VerseExtensionMethod = 1 << 24` — True if the function is an extension method

#### class `EpicGames.UHT.Types.UhtFunctionExportFlagsExtensions`  
`public static class UhtFunctionExportFlagsExtensions`  
_public; L161-197_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L170-173 _public method_ `public static bool HasAnyFlags(this UhtFunctionExportFlags inFlags, UhtFunctionExportFlags testFlags)` — Test to see if any of the specified flags are set
- L181-184 _public method_ `public static bool HasAllFlags(this UhtFunctionExportFlags inFlags, UhtFunctionExportFlags testFlags)` — Test to see if all of the specified flags are set
- L193-196 _public method_ `public static bool HasExactFlags(this UhtFunctionExportFlags inFlags, UhtFunctionExportFlags testFlags, UhtFunctionExportFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtFunctionType`  
`public enum UhtFunctionType`  
_public; L202-219_
- desc: Type of function
- L208 _public* enumerator_ `Function` — UFUNCTION
- L213 _public* enumerator_ `Delegate` — UDELEGATE/DECLARE_DYNAMIC_...
- L218 _public* enumerator_ `SparseDelegate` — UDELEGATE/DECLARE_DYNAMIC_...SPARSE_...

#### class `EpicGames.UHT.Types.UhtFunctionTypeExtensions`  
`public static class UhtFunctionTypeExtensions`  
_public; L224-236_
- desc: Extension
- L232-235 _public method_ `public static bool IsDelegate(this UhtFunctionType functionType)` — Test to see if the function type is a delegate type

#### class `EpicGames.UHT.Types.UhtFunction`  
`public class UhtFunction : UhtStruct`  
_public; L241-1415_
- inherits: `UhtStruct`
- desc: Represents a UFUNCTION/delegate
- L243 _private field_ `private string? _strippedFunctionName = null`
- L248 _public field_ `public static readonly string GeneratedDelegateSignatureSuffix = "__DelegateSignature"` — Suffix added to delegate engine names
- L254 _public property_ `public EFunctionFlags FunctionFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Engine function flags
- L260 _public property_ `public UhtFunctionExportFlags FunctionExportFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — UHT specific function flags
- L266 _public property_ `public UhtFunctionType FunctionType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — The type of function
- L272 _public property_ `public override UhtStruct? InheritanceSuperStruct => ...` — attrs: `[JsonIgnore]` — Super struct type for inheritance, i.e. functions do not inherit properties from their Super
- L277 _public property_ `public int MacroLineNumber { get; set; }` — The line number for the macro.
- L282 _public property_ `public string? SparseOwningClassName { get; set; }` — Owning class name for sparse functions
- L287 _public property_ `public string? SparseDelegateName { get; set; }` — Sparse delegate name
- L293 _public property_ `public UhtFunction? SuperFunction => ...` — attrs: `[JsonConverter(typeof(UhtNullableTypeSourceNameJsonConverter<UhtFunction>))]` — The super function. Currently unused
- L298 _public property_ `public UhtDefineScopeLink<UhtFunction>? NextFunction { get; set; }` — After functions are fully resolved, points to the next function in the owning struct in each define scope.
- L302-318 _public property_ `public override UhtEngineType EngineType { get; }` — attrs: `[JsonIgnore]` — (inheritdoc)
- L321-337 _public property_ `public override string EngineClassName { get; }` — (inheritdoc)
- L340 _public property_ `public override string EngineLinkClassName => ...` — (inheritdoc)
- L343-359 _public property_ `public override UhtClass? EngineClass { get; }` — (inheritdoc)
- L365-369 _public property_ `public string StrippedFunctionName { get; set; }` — attrs: `[JsonIgnore]` — Stripped function name without the generated delegate suffix
- L373 _public property_ `public override bool Deprecated => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L377 _protected property_ `protected override UhtSpecifierValidatorTable? SpecifierValidatorTable => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L382 _public property_ `public ushort RPCId { get; set; }` — Identifier for an RPC call to a platform service
- L387 _public property_ `public ushort RPCResponseId { get; set; }` — Identifier for an RPC call expecting a response
- L392 _public property_ `public string CppImplName { get; set; }` — Name of the actual implementation
- L397 _public property_ `public string CppValidationImplName { get; set; }` — Name of the actual validation implementation
- L402 _public property_ `public string MarshalAndCallName { get; set; }` — Name of the wrapper function that marshals the arguments and does the indirect call
- L407 _public property_ `public string UnMarshalAndCallName { get; set; }` — Name for callback-style names
- L412 _public property_ `public string EndpointName { get; set; }` — Endpoint name
- L418 _public property_ `public bool HasReturnProperty => ...` — attrs: `[JsonIgnore]` — True if the function has a return value.
- L424 _public property_ `public UhtProperty? ReturnProperty => ...` — attrs: `[JsonIgnore]` — The return value property or null if the function doesn't have a return value
- L430 _public property_ `public bool HasParameters => ...` — attrs: `[JsonIgnore]` — True if the function has parameters.
- L436 _public property_ `public ReadOnlyMemory<UhtType> ParameterProperties => ...` — attrs: `[JsonIgnore]` — Return read only memory of all the function parameters
- L442-458 _public property_ `public bool HasAnyOutputs { get; }` — attrs: `[JsonIgnore]` — True if the function has any outputs including a return value
- L467-469 _public ctor_ `public UhtFunction(UhtHeaderFile headerFile, UhtNamespace namespaceObj, UhtType outer, int lineNumber) : base(headerFile, namespaceObj, outer, lineNumber)` — Construct a new instance of a function
- L476-492 _public ctor_ `public UhtFunction(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L498-515 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L518-536 _public method_ `public override void AddChild(UhtType type)` — (inheritdoc)
- L539-550 _public method_ `public override void AppendVerseScopeAndName(StringBuilder builder, UhtVerseNameMode mode)` — (inheritdoc)
- L553-608 _protected method_ `protected override void AppendVerseName(StringBuilder builder, UhtVerseNameMode mode)` — (inheritdoc)
- L612-741 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L746-1066 _protected method_ `protected override UhtValidationOptions Validate(UhtValidationOptions options)` — (inheritdoc)
- L1068-1142 _private method_ `private void LogRpcFunctionError(bool virtualError, string functionName)`
- L1144-1194 _private method_ `private void ValidateSpecifierFlags()`
- L1197-1277 _protected method_ `protected override void ValidateDocumentationPolicy(UhtDocumentationPolicy policy)` — (inheritdoc)
- L1285-1288 _private method_ `private static void AddParameterToolTip(StringView name, StringView text, Dictionary<StringView, StringView> paramMap)` — Add a parameter tooltip to the collection
- L1295-1303 _private method_ `private static void AddParameterToolTip(StringView text, Dictionary<StringView, StringView> paramMap)` — Add a parameter tooltip to the collection where the name of the parameter is the first word of the line
- L1310-1351 _private method_ `private static Dictionary<StringView, StringView> GetParameterToolTipsFromFunctionComment(StringView input)` — Parse the function comment looking for parameter documentation.
- L1355-1386 _public method_ `public override void CollectReferences(IUhtReferenceCollector collector)` — (inheritdoc)
- L1394-1414 _protected internal method_ `protected internal UhtPropertyParseOptions GetPropertyParseOptions(bool returnValue)` — Return the property parse options for the given function

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtHeaderFile.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtHeaderFileType`  
`public enum UhtHeaderFileType`  
_public; L18-40_
- desc: Represents the different directories where headers can appear
- L24 _public* enumerator_ `Classes` — Classes folder
- L29 _public* enumerator_ `Public` — Public folder
- L34 _public* enumerator_ `Internal` — Internal folder
- L39 _public* enumerator_ `Private` — Private folder

#### enum `EpicGames.UHT.Types.UhtHeaderFileExportFlags`  
`public enum UhtHeaderFileExportFlags : int`  
_public; L46-57_
- attrs: `[Flags]`
- inherits: `int`
- desc: Series of flags not part of the engine's class flags that affect code generation or verification
- L51 _public* enumerator_ `None = 0` — No export flags
- L56 _public* enumerator_ `Referenced = 0x00000001` — This header is being included by another header

#### class `EpicGames.UHT.Types.UhtHeaderFileExportFlagsExtensions`  
`public static class UhtHeaderFileExportFlagsExtensions`  
_public; L63-99_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L72-75 _public method_ `public static bool HasAnyFlags(this UhtHeaderFileExportFlags inFlags, UhtHeaderFileExportFlags testFlags)` — Test to see if any of the specified flags are set
- L83-86 _public method_ `public static bool HasAllFlags(this UhtHeaderFileExportFlags inFlags, UhtHeaderFileExportFlags testFlags)` — Test to see if all of the specified flags are set
- L95-98 _public method_ `public static bool HasExactFlags(this UhtHeaderFileExportFlags inFlags, UhtHeaderFileExportFlags testFlags, UhtHeaderFileExportFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtHeaderReferenceType`  
`public enum UhtHeaderReferenceType`  
_public; L104-116_
- desc: Type of reference being added
- L110 _public* enumerator_ `Include` — The header being referenced in a direct include
- L115 _public* enumerator_ `Passive` — The header being referenced is a passive reference (i.e. NoExportTypes.h or a header referenced by a header being included)

#### class `EpicGames.UHT.Types.UhtHeaderFile`  
`public class UhtHeaderFile : IUhtMessageSite, IUhtMessageLineNumber`  
_public; L121-596_
- inherits: `IUhtMessageSite, IUhtMessageLineNumber`
- desc: Represents a header file.
- L123 _private field_ `private readonly UhtSimpleMessageSite _messageSite`
- L124 _private field_ `private readonly UhtSourceFile _sourceFile`
- L125 _private field_ `private readonly List<UhtHeaderFile> _referencedHeaders = []`
- L126 _private field_ `private readonly List<UhtType> _children = []`
- L132 _public property_ `public StringView Data => ...` — attrs: `[JsonIgnore]` — Contents of the header
- L138 _public property_ `public string FilePath => ...` — attrs: `[JsonIgnore]` — Path of the header
- L144 _public property_ `public UhtSession Session => ...` — attrs: `[JsonIgnore]` — Currently running session
- L150 _public property_ `public UhtModule Module { get; }` — attrs: `[JsonIgnore]` — Module associated with the header
- L156 _public property_ `public string FileNameWithoutExtension { get; }` — attrs: `[JsonIgnore]` — File name without the extension
- L162 _public property_ `public string GeneratedHeaderFileName { get; }` — attrs: `[JsonIgnore]` — Required name for the generated.h file name. Used to validate parsed code
- L168 _public property_ `public bool IsNoExportTypes { get; }` — attrs: `[JsonIgnore]` — True if this header is NoExportTypes.h
- L173 _public property_ `public string ModuleRelativeFilePath { get; set; }` — The file path of the header relative to the module location
- L178 _public property_ `public string IncludeFilePath { get; set; }` — Include file path added as meta data to the types
- L184 _public property_ `public UhtHeaderFileType HeaderFileType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Location where the header file was found
- L190 _public property_ `public int HeaderFileTypeIndex { get; }` — attrs: `[JsonIgnore]` — Unique index of the header file
- L196 _public property_ `public bool WasCached { get; set; }` — attrs: `[JsonIgnore]` — If true, this header file came from the input cache
- L203 _public property_ `public UhtInputCacheEntry InputCacheEntry { get; set; }` — attrs: `[JsonIgnore]` — Contains the last write time of the source file or cached source. If the file was cached, then the data is the cached contents
- L209 _public property_ `public UhtHeaderFileExportFlags HeaderFileExportFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — UHT flags for the header
- L215 _public property_ `public IReadOnlyList<UhtType> Children => ...` — attrs: `[JsonConverter(typeof(UhtNullableTypeListJsonConverter<UhtType>))]` — Children types of this type
- L218 _public method_ `public override string ToString()` — (inheritdoc)
- L224 _public property_ `public bool ShouldExport => ...` — attrs: `[JsonIgnore]` — If true, the header file should be exported
- L230 _public property_ `public UhtReferenceCollector References { get; init; }` — attrs: `[JsonIgnore]` — Resource collector for the header file
- L236 _public property_ `public List<UhtHeaderFile> IncludedHeaders { get; }` — attrs: `[JsonIgnore]` — Collection of headers directly included by this header
- L241 _public property_ `public IUhtMessageSession MessageSession => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L245 _public property_ `public IUhtMessageSource? MessageSource => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L249 _public property_ `public IUhtMessageLineNumber? MessageLineNumber => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L254 _private* property_ `int IUhtMessageLineNumber.MessageLineNumber => ...` — attrs: `[JsonIgnore]`
- L262-273 _public ctor_ `public UhtHeaderFile(UhtModule module, string path)` — Construct a new header file
- L278-287 _public method_ `public void Read()` — Read the contents of the header
- L292-327 _public method_ `public void ReadFromCache()` — Attempt to read the file from the cache
- L334-344 _public method_ `public void AddReferencedHeader(string id, UhtHeaderReferenceType referenceType)` — Add a reference to the given header
- L350-353 _public method_ `public void AddReferencedHeader(UhtType type)` — Add a reference to the header that defines the given type
- L360-392 _public method_ `public void AddReferencedHeader(UhtHeaderFile headerFile, UhtHeaderReferenceType referenceType)` — Add a reference to the given header file
- L398 _public property_ `public IEnumerable<UhtHeaderFile> ReferencedHeadersNoLock => ...` — attrs: `[JsonIgnore]` — Return an enumerator without locking. This method can only be utilized AFTER all header parsing is complete.
- L404-416 _public property_ `public IEnumerable<UhtHeaderFile> ReferencedHeadersLocked { get; }` — attrs: `[JsonIgnore]` — Return an enumerator of all current referenced headers under a lock. This should be used during parsing.
- L422-428 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write the header to the archive writer
- L434-441 _public method_ `public void Read(UhtInputCacheReader reader)` — Read the header from the archive
- L447-450 _public method_ `public void AddChild(UhtType child)` — Add a type as a child
- L456-475 _public method_ `public void Resolve(UhtResolvePhase resolvePhase)` — Resolve all types owned by the header
- L480-486 _public method_ `public void BindSuperAndBases()` — Bind all the super structs and base classes
- L493-555 _public method_ `public void Validate(UhtValidationOptions options)` — Validate the state of the header file
- L560-570 _public method_ `public void CollectReferences()` — Collect all things referenced by the given header
- L572-577 _private method_ `private void Reset()`
- L579-583 _private method_ `private UhtHeaderFile? FindHeaderFile(string filePath)`
- L585-595 _private method_ `private void ReadHeaderFiles(UhtInputCacheReader reader, List<UhtHeaderFile> output)`

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtManifestFile.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtManifestFile`  
`public class UhtManifestFile : IUhtMessageSite`  
_public; L13-53_
- inherits: `IUhtMessageSite`
- desc: Represents the UHT manifest file
- L19 _public property_ `public UHTManifest? Manifest { get; set; }` — Loaded manifest from the json manifest file
- L21 _private field_ `private readonly UhtSourceFile _sourceFile`
- L26 _public property_ `public IUhtMessageSession MessageSession => ...` — (inheritdoc)
- L29 _public property_ `public IUhtMessageSource? MessageSource => ...` — (inheritdoc)
- L32 _public property_ `public IUhtMessageLineNumber? MessageLineNumber => ...` — (inheritdoc)
- L40-43 _public ctor_ `public UhtManifestFile(UhtSession session, string filePath)` — Construct a new manifest file
- L48-52 _public method_ `public void Read()` — Read the contents of the file

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtMetaData.cs` (EpicGames.UHT)


#### interface `EpicGames.UHT.Types.IUhtMetaDataKeyConversion`  
`public interface IUhtMetaDataKeyConversion`  
_public; L16-26_
- desc: UhtEnum types need to convert a meta data name index to the enum name
- L25 _public* method_ `string GetMetaDataKey(string name, int nameIndex)` — Convert a name and index into a full meta data name

#### struct `EpicGames.UHT.Types.UhtMetaDataKey`  
`public struct UhtMetaDataKey`  
_public; L31-90_
- desc: Uniquely identifies a meta data element
- L37 _public property_ `public string Name { get; set; }` — The name of the meta data
- L42 _public property_ `public int Index { get; set; }` — The index of the meta data name (i.e. enum value index) or -1 for the owning object meta data
- L49-53 _public ctor_ `public UhtMetaDataKey(string name, int index = UhtMetaData.IndexNone)` — Construct a new meta data key
- L59-63 _public ctor_ `public UhtMetaDataKey(UhtInputCacheReader reader)` — Read from the archive reader
- L69-73 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write to the archive writer
- L79-89 _public method_ `public override readonly string ToString()` — Convert the key to a string

#### class `EpicGames.UHT.Types.UhtMetaDataKeyComparer`  
`sealed class UhtMetaDataKeyComparer : IEqualityComparer<UhtMetaDataKey>, IComparer<UhtMetaDataKey>`  
_internal*; L95-136_
- inherits: `IEqualityComparer<UhtMetaDataKey>, IComparer<UhtMetaDataKey>`
- desc: Comparer for meta data keys
- L103-114 _public method_ `public int Compare([AllowNull] UhtMetaDataKey x, [AllowNull] UhtMetaDataKey y)` — Compare two keys
- L122-125 _public method_ `public bool Equals([AllowNull] UhtMetaDataKey x, [AllowNull] UhtMetaDataKey y)` — Test to see if two meta data keys are equal
- L132-135 _public method_ `public int GetHashCode([DisallowNull] UhtMetaDataKey obj)` — Get the hash code of the meta data key

#### class `EpicGames.UHT.Types.UhtMetaData`  
`public class UhtMetaData`  
_public; L142-648_
- desc: Represents a collection of key/value pairs. Each type has this collection and enumerations also have key/value pairs for each enumeration value index.
- L148 _private field_ `private static readonly UhtMetaDataKeyComparer s_comparer = new()` — Helper comparer for meta data keys
- L153 _public field_ `public static readonly UhtMetaData Empty = new(null, null)` — Empty collection of meta data
- L159 _public property_ `public UhtMetaData? Parent { get; set; }` — attrs: `[JsonIgnore]` — The meta data of the outer object for the type that owns this meta data
- L165 _public property_ `public IUhtMessageSite? MessageSite { get; set; }` — attrs: `[JsonIgnore]` — Message site associated with the meta data. That in combination with the line number is used to generate errors
- L171 _public property_ `public IUhtConfig? Config { get; set; }` — attrs: `[JsonIgnore]` — Configuration object used to redirect meta data
- L177 _public property_ `public int LineNumber { get; set; }` — attrs: `[JsonIgnore]` — Source code line number where the meta data is declared
- L184 _public property_ `public SortedList<UhtMetaDataKey, string>? Dictionary { get; set; }` — attrs: `[SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "")]` — Contains the meta data entries. Due to the small size of these dictionaries, a SortedList performs better than a Dictionary.
- L189 _internal property_ `internal IUhtMetaDataKeyConversion? KeyConversion { get; set; }` — Enumerations implement this interface so that the index part of the key can be converted to a string
- L194 _public const_ `public const int IndexNone = -1` — Index for a meta data key associated with the owning object
- L201-205 _public ctor_ `public UhtMetaData(IUhtMessageSite? messageSite, IUhtConfig? config)` — Construct new meta data
- L211-222 _public method_ `public void Read(UhtInputCacheReader reader)` — Read from the archive reader
- L228-244 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write to the archive writer
- L250-253 _public method_ `public bool IsEmpty()` — Test to see if the meta data object contains no entries
- L258-261 _public method_ `public void Clear()` — Remove all meta data entries
- L269-276 _public method_ `public bool ContainsKey(string name, int nameIndex = IndexNone)` — Test to see if the meta data contains the given key
- L284-294 _public method_ `public bool ContainsKeyHierarchical(string name, int nameIndex = IndexNone)` — Test to see if the meta data or parent meta data contains the given key
- L302-305 _public method_ `public bool TryGetValue(string name, [NotNullWhen(true)] out string? value)` — Attempt to get the value associated with the key
- L313-316 _public method_ `public bool TryGetValueHierarchical(string name, [NotNullWhen(true)] out string? value)` — Attempt to get the value associated with the key including parent meta data
- L325-333 _public method_ `public bool TryGetValue(string name, int nameIndex, [NotNullWhen(true)] out string? value)` — Attempt to get the value associated with the key
- L342-353 _public method_ `public bool TryGetValueHierarchical(string name, int nameIndex, [NotNullWhen(true)] out string? value)` — Attempt to get the value associated with the key including parent meta data
- L361-368 _public method_ `public string GetValueOrDefault(string name, int nameIndex = IndexNone)` — Get the string value of the given meta data key or the default value.
- L376-383 _public method_ `public string GetValueOrDefaultHierarchical(string name, int nameIndex = IndexNone)` — Get the string value of the given meta data searching the whole meta data chain.
- L391-394 _public method_ `public bool GetBoolean(string name, int nameIndex = IndexNone)` — Get the boolean value of the given meta data.
- L402-405 _public method_ `public bool GetBooleanHierarchical(string name, int nameIndex = IndexNone)` — Get the boolean value of the given meta data searching the whole meta data chain.
- L413-421 _public method_ `public double GetDouble(string name, int nameIndex = IndexNone)` — Get the double value of the given meta data.
- L429-436 _public method_ `public string[]? GetStringArray(string name, int nameIndex = IndexNone)` — Get the string array value of the given meta data.
- L444-451 _public method_ `public string[]? GetStringArrayHierarchical(string name, int nameIndex = IndexNone)` — Get the string array value of the given meta data searching the whole meta data chain.
- L458-461 _public method_ `public void Add(string name, string value)` — Add new meta data
- L469-472 _public method_ `public void Add(string name, int nameIndex, string value)` — Add new meta data
- L480-483 _public method_ `public void CheckedAdd(string name, int nameIndex, string value)` — Add new meta data
- L491-494 _public method_ `public void Add(string name, bool value, int nameIndex = IndexNone)` — Add new meta data
- L502-505 _public method_ `public void Add(string name, List<string> strings, char separator = ' ')` — Add new meta data
- L513-519 _public method_ `public void AddIfNotEmpty(string name, List<string> strings, char separator = ' ')` — Add new meta data if there are strings in the value.
- L525-535 _public method_ `public void Add(UhtMetaData metaData)` — Add the meta data from another meta data block
- L544-554 _private method_ `private void AddInternalWithRedirect(string name, int nameIndex, string value, bool checkValueChange)` — Add the given meta data but test for redirection of meta data name
- L563-576 _private method_ `private void AddInternal(SortedList<UhtMetaDataKey, string> dictionary, UhtMetaDataKey key, string value, bool checkValueChange)` — Add the value to the meta data
- L583-586 _public method_ `public void Remove(string name, int nameIndex = IndexNone)` — Remove the given meta data
- L593-596 _public method_ `public string GetKeyString(UhtMetaDataKey key)` — Given a key, return the full meta data name
- L605-619 _public method_ `public string GetKeyString(string name, int nameIndex)` — Given a key, return the full meta data name
- L625-641 _public method_ `public List<KeyValuePair<string, string>> GetSorted()` — Given a type, return an array of all the meta data formatted and sorted by name
- L643-647 _private method_ `private SortedList<UhtMetaDataKey, string> GetDictionary()`

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtModule.cs` (EpicGames.UHT)


#### record `EpicGames.UHT.Types.UhtModuleLinking`  
`public record UhtModuleLinking(IReadOnlyDictionary<UhtModule, int> ReferencedModules, IReadOnlyDictionary<UhtObject, int> LinkableObjects)`  
_public; L18-18_
- desc: Index assignments for other modules which are a dependency of this module, and objects which are linkable in this module from others.

#### class `EpicGames.UHT.Types.UhtModule`  
`public class UhtModule`  
_public; L23-330_
- desc: Represents a UHT module
- L25 _private field_ `private readonly List<UhtHeaderFile> _headers = []`
- L26 _private field_ `private readonly SortedDictionary<string, UhtPackage> _packages = ...`
- L26 _private field_ `private readonly SortedDictionary< _packages = []`
- L27 _private field_ `private readonly HashSet<string> _ubtModuleDependencies = []`
- L28 _private field_ `private readonly Lazy<UhtInputCache> _inputCache`
- L34 _public property_ `public UhtSession Session { get; }` — attrs: `[JsonIgnore]` — The running session
- L39 _public property_ `public UHTManifest.Module Module { get; }` — UHT module from UBT (1 to 1 relationship)
- L45 _public property_ `public UhtPackage ScriptPackage { get; }` — attrs: `[JsonIgnore]` — Primary /Script/ package
- L50 _public property_ `public string ShortName { get; }` — Name of the module based on the script package name with out the "/Script/" prefix
- L56 _public property_ `public string Api { get; }` — attrs: `[JsonIgnore]` — C++ API name for the module with a trailing space
- L62 _public property_ `public string NonAttributedApi { get; }` — attrs: `[JsonIgnore]` — C++ API non-attributed name for the module with a trailing space
- L67-80 _public property_ `public IEnumerable<UhtPackage> Packages { get; }` — Enumeration of all the packages in the module.
- L86 _public property_ `public IReadOnlyList<UhtHeaderFile> Headers => ...` — attrs: `[JsonIgnore]` — Collection of headers owned by the module
- L91 _public property_ `public IReadOnlySet<string> UBTModuleDependencies => ...` — Collection of module dependencies from UBT (may also include the names of modules not present in UHT)
- L97-121 _public property_ `public bool IsPartOfEngine { get; }` — attrs: `[JsonIgnore]` — True if the package is part of the engine
- L127 _public property_ `public bool IsPlugin => ...` — attrs: `[JsonIgnore]` — True if the package is a plugin
- L132 _public property_ `public UhtModuleLinking? Linking { get; set; }` — Information about linking objects between this module and others generated by UhtSession after reference collection.
- L139-206 _public ctor_ `public UhtModule(UhtSession session, UHTManifest.Module module)` — Create a new module from the given manifest module
- L213-219 _public method_ `public void PrepareHeaders(Action<UhtHeaderFile> addHeaderFileAction)` — Prepare to parse all the headers in the module. This creates all the UhtHeaderFiles and validates there are no conflicts.
- L227-243 _public method_ `public UhtPackage CreatePackage(string packageName, EPackageFlags packageFlags = EPackageFlags.None)` — Create a new package with the given name. Will return an existing instance if it already exists
- L251-260 _public method_ `public bool TryGetCachedInput(string fileName, out UhtInputCacheEntry entry)` — Try to fetch a cached version of the file from the input cache
- L268-315 _private method_ `private void PrepareHeaders(IEnumerable<string> headerFiles, UhtHeaderFileType headerFileType, Action<UhtHeaderFile> addHeaderFileAction)` — Given a collection of headers, create the UhtHeaders
- L326-329 _private method_ `private string GetNormalizedFullFilePath(string filePath)` — Return the normalized path converted to a full path if possible. Code should NOT depend on a full path being returned. In general, it is assumed that during normal UHT, all paths are already full paths. Only the test harness deals in relative paths.

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtNamespace.cs` (EpicGames.UHT)


#### record struct `EpicGames.UHT.Types.UhtNamespaceElement`  
`public record struct UhtNamespaceElement(StringView Name, UhtNamespace? Namespace)`  
_public; L15-17_
- desc: Represents an element that makes up a namespace. This includes a previously looked up namespace

#### class `EpicGames.UHT.Types.UhtNamespace`  
`public class UhtNamespace`  
_public; L22-110_
- desc: Represents a C++ namespace
- L28 _public property_ `public UhtNamespace? Parent { get; init; }` — Parent namespace. If null, then this is the global namespace
- L33 _public property_ `public string SourceName { get; init; }` — Name of this namespace
- L38 _public property_ `public string FullSourceName { get; init; }` — The full name of the namespace
- L43 _public property_ `public bool IsGlobal { get; init; }` — True if this is the global namespace
- L52-58 _public ctor_ `public UhtNamespace(UhtNamespace? parent, string sourceName, string fullSourceName, bool isGlobal)` — Construct a namespace instance
- L66-84 _public method_ `public StringBuilder AppendSingleLine(StringBuilder builder, Action<StringBuilder> body)` — Append the body inside the namespace on a single line
- L92-109 _public method_ `public StringBuilder AppendMultipleLines(StringBuilder builder, Action<StringBuilder> body)` — Append the body inside the namespace on multiple lines

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtObject.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtObject`  
`public abstract class UhtObject : UhtType`  
_public; L14-88_
- attrs: `[UhtEngineClass(Name = "Object")]`
- inherits: `UhtType`
- desc: Represents a UObject in the engine
- L21 _public property_ `public EInternalObjectFlags InternalObjectFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Internal object flags.
- L27 _public property_ `public int ObjectTypeIndex { get; }` — attrs: `[JsonIgnore]` — Unique index of the object
- L34 _public property_ `public UhtObject? AlternateObject { get; set; }` — attrs: `[JsonIgnore]` — The alternate object is used by the interface system where the native interface will update this setting to point to the UInterface derived companion object.
- L39 _public property_ `public int LinkOrder => ...` — Linkable top-level objects per packages should be in a specific order to simplify codegen and runtime initialization
- L48 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L54-57 _protected ctor_ `protected UhtObject(UhtModule module) : base(module)` — Construct a new instance of the object
- L65-68 _protected ctor_ `protected UhtObject(UhtHeaderFile headerFile, UhtType outer, int lineNumber) : base(headerFile, outer, lineNumber)` — Construct a new instance of the object
- L75-78 _protected ctor_ `protected UhtObject(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L84-87 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the type to the archive writer

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtPackage.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtPackage`  
`public class UhtPackage : UhtObject`  
_public; L14-63_
- attrs: `[UhtEngineClass(Name = "Package")]`
- inherits: `UhtObject`
- desc: Represents a UPackage in the engine
- L21 _public property_ `public int PackageTypeIndex { get; }` — attrs: `[JsonIgnore]` — Unique index of the package
- L27 _public property_ `public EPackageFlags PackageFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Engine package flags
- L31 _public property_ `public override UhtEngineType EngineType => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L34 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L37 _public property_ `public override UhtClass? EngineClass => ...` — (inheritdoc)
- L41 _public property_ `public override UhtPackage Package => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L49-54 _public ctor_ `public UhtPackage(UhtModule module, string packageName, EPackageFlags packageFlags) : base(module)` — Construct a new instance of a package
- L57-62 _public method_ `public override void AddChild(UhtType type)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtPartial.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtPartial`  
`public class UhtPartial : UhtStruct`  
_public; L20-284_
- inherits: `UhtStruct`
- desc: Represents an partial - a struct that extends a UObject-derived class with additional properties. Partials are similar to USTRUCTs but their properties are merged directly into the owner class.
- L22 _private field_ `private List<UhtDeclaration>? _declarations = null`
- L27 _public property_ `public string OwnerClassName { get; set; }` — Name of the class that this partial extends (e.g., "APlayerController")
- L33 _public property_ `public UhtClass? OwnerClass { get; set; }` — attrs: `[JsonConverter(typeof(UhtNullableTypeSourceNameJsonConverter<UhtClass>))]` — Reference to the partial class (resolved during resolution phase)
- L38 _public property_ `public int MacroDeclaredLineNumber { get; set; }` — Line number where GENERATED_BODY macro was found
- L42 _public property_ `public override UhtEngineType EngineType => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L45 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L48 _public property_ `public override string EngineLinkClassName => ...` — (inheritdoc)
- L51 _public property_ `public override UhtClass? EngineClass => ...` — (inheritdoc)
- L55 _public property_ `public override string EngineNamePrefix => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L60 _public property_ `public string NamespaceExportName => ...` — Namespace export name for partials
- L66 _public property_ `public IList<UhtDeclaration>? Declarations => ...` — attrs: `[JsonIgnore]` — Collection of functions and other declarations found in the partial
- L71 _public property_ `public bool HasBeginDestroy { get; set; }` — C++ code has BeginDestroy declared
- L76 _public property_ `public UhtDefineScopeLink<UhtFunction>? FirstFunction { get; set; }` — After functions are fully resolved, points to the first non-delegate function in this class
- L80 _protected property_ `protected override UhtSpecifierValidatorTable? SpecifierValidatorTable => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L89-91 _public ctor_ `public UhtPartial(UhtHeaderFile headerFile, UhtNamespace namespaceObj, UhtType outer, int lineNumber) : base(headerFile, namespaceObj, outer, lineNumber)` — Construct a new partial
- L98-104 _public ctor_ `public UhtPartial(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L110-117 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L122-171 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase resolvePhase)` — (inheritdoc)
- L174-184 _protected method_ `protected override void ResolveChildren(UhtResolvePhase phase)` — (inheritdoc)
- L189-212 _protected method_ `protected void LinkFunctions()` — Create a linked list of functions across preprocessor definition changes
- L219-222 _public method_ `public override StringBuilder AppendForwardDeclaration(StringBuilder builder)` — (inheritdoc)
- L229-241 _public method_ `public override void CollectReferences(IUhtReferenceCollector collector)` — (inheritdoc)
- L253-257 _public method_ `public void AddDeclaration(UhtCompilerDirective compilerDirectives, List<UhtToken> tokens, UhtFunction? function)` — Add a declaration to the partial (for functions and other declarations)
- L264-281 _protected method_ `protected override UhtValidationOptions Validate(UhtValidationOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtProperty.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtPropertyExportFlags`  
`public enum UhtPropertyExportFlags`  
_public; L24-130_
- attrs: `[Flags]`
- desc: Collection of UHT only flags associated with properties
- L29 _public* enumerator_ `Public = 1 << 0` — Property should be exported as public
- L34 _public* enumerator_ `Private = 1 << 1` — Property should be exported as private
- L39 _public* enumerator_ `Protected = 1 << 2` — Property should be exported as protected
- L44 _public* enumerator_ `ImpliedBlueprintPure = 1 << 3` — The BlueprintPure flag was set in software and should not be considered an error
- L49 _public* enumerator_ `GetterSpecified = 1 << 4` — If true, the property has a getter function
- L54 _public* enumerator_ `SetterSpecified = 1 << 5` — If true, the property has a setter function
- L59 _public* enumerator_ `GetterSpecifiedNone = 1 << 6` — If true, the getter has been disabled in the specifiers
- L64 _public* enumerator_ `SetterSpecifiedNone = 1 << 7` — If true, the setter has been disabled in the specifiers
- L69 _public* enumerator_ `GetterFound = 1 << 8` — If true, the getter function was found
- L74 _public* enumerator_ `SetterFound = 1 << 9` — If true, the property has a setter function
- L79 _public* enumerator_ `FieldNotify = 1 << 10` — Property is marked as a field notify
- L84 _public* enumerator_ `GetterSpecifiedAuto = 1 << 11` — If true, the property should have a generated getter function
- L89 _public* enumerator_ `SetterSpecifiedAuto = 1 << 12` — If true, the property should have a generated setter function
- L94 _public* enumerator_ `TVal = 1 << 13` — If true, the type is a TVal
- L99 _public* enumerator_ `TPtr = 1 << 14` — If true, the type is a TPtr
- L104 _public* enumerator_ `TVerseTask = 1 << 15` — If true, the type is a TVerseTask
- L109 _public* enumerator_ `TVerseCall = 1 << 16` — If true, the type is a TVerseCall
- L114 _public* enumerator_ `TNonNullPtr = 1 << 17` — If true, the type is a TNonNullPtr
- L119 _public* enumerator_ `VerseNamed = 1 << 18` — If true, this function argument is named
- L124 _public* enumerator_ `VerseDefaultValue = 1 << 19` — If true, this function argument has a default value
- L129 _public* enumerator_ `VerseField = 1 << 20` — This property is wrapped by UE_VERSE_FIELD

#### class `EpicGames.UHT.Types.UhtPropertyExportFlagsExtensions`  
`public static class UhtPropertyExportFlagsExtensions`  
_public; L136-172_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L145-148 _public method_ `public static bool HasAnyFlags(this UhtPropertyExportFlags inFlags, UhtPropertyExportFlags testFlags)` — Test to see if any of the specified flags are set
- L156-159 _public method_ `public static bool HasAllFlags(this UhtPropertyExportFlags inFlags, UhtPropertyExportFlags testFlags)` — Test to see if all of the specified flags are set
- L168-171 _public method_ `public static bool HasExactFlags(this UhtPropertyExportFlags inFlags, UhtPropertyExportFlags testFlags, UhtPropertyExportFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtPropertyCategory`  
`public enum UhtPropertyCategory`  
_public; L177-198_
- desc: The context of the property.
- L182 _public* enumerator_ `RegularParameter` — Function parameter for a function that isn't marked as NET
- L187 _public* enumerator_ `ReplicatedParameter` — Function parameter for a function that is marked as NET
- L192 _public* enumerator_ `Return` — Function return value
- L197 _public* enumerator_ `Member` — Class or a script structure member property

#### class `EpicGames.UHT.Types.UhtPropertyCategoryExtensions`  
`public static class UhtPropertyCategoryExtensions`  
_public; L203-230_
- desc: Helper methods for the property category
- L212-229 _public method_ `public static string GetHintText(this UhtPropertyCategory propertyCategory)` — Return the hint text for the property category

#### enum `EpicGames.UHT.Types.UhtPropertyAllocator`  
`public enum UhtPropertyAllocator`  
_public; L235-246_
- desc: Allocator used for container
- L240 _public* enumerator_ `Default` — Default allocator
- L245 _public* enumerator_ `MemoryImage` — Memory image allocator

#### enum `EpicGames.UHT.Types.UhtPointerType`  
`public enum UhtPointerType`  
_public; L251-263_
- desc: Type of pointer
- L257 _public* enumerator_ `None` — No pointer specified
- L262 _public* enumerator_ `Native` — Native pointer specified

#### enum `EpicGames.UHT.Types.UhtPropertyRefQualifier`  
`public enum UhtPropertyRefQualifier`  
_public; L268-285_
- desc: Type of reference
- L274 _public* enumerator_ `None` — Property is not a reference
- L279 _public* enumerator_ `ConstRef` — Property is a const reference
- L284 _public* enumerator_ `NonConstRef` — Property is a non-const reference

#### enum `EpicGames.UHT.Types.UhtPropertyOptions`  
`public enum UhtPropertyOptions`  
_public; L291-303_
- attrs: `[Flags]`
- desc: Options that customize the properties.
- L297 _public* enumerator_ `None = 0` — No property options
- L302 _public* enumerator_ `NoAutoConst = 1 << 0` — Don't automatically mark properties as CPF_Const

#### class `EpicGames.UHT.Types.UhtPropertyOptionsExtensions`  
`public static class UhtPropertyOptionsExtensions`  
_public; L309-345_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L318-321 _public method_ `public static bool HasAnyFlags(this UhtPropertyOptions inFlags, UhtPropertyOptions testFlags)` — Test to see if any of the specified flags are set
- L329-332 _public method_ `public static bool HasAllFlags(this UhtPropertyOptions inFlags, UhtPropertyOptions testFlags)` — Test to see if all of the specified flags are set
- L341-344 _public method_ `public static bool HasExactFlags(this UhtPropertyOptions inFlags, UhtPropertyOptions testFlags, UhtPropertyOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtPropertyCaps`  
`public enum UhtPropertyCaps`  
_public; L351-447_
- attrs: `[Flags]`
- desc: Property capabilities. Use the caps system instead of patterns such as "Property is UhtObjectProperty"
- L356 _public* enumerator_ `None = 0` — No property caps
- L361 _public* enumerator_ `PassCppArgsByRef = 1 << 0` — If true, the property will be passed by reference when generating the full type string
- L366 _public* enumerator_ `RequiresNullConstructorArg = 1 << 1` — If true, the an argument will need to be added to the constructor
- L371 _public* enumerator_ `CanBeContainerValue = 1 << 2` — If true, the property type can be TArray or TMap value
- L376 _public* enumerator_ `CanBeContainerKey = 1 << 3` — If true, the property type can be a TSet or TMap key
- L381 _public* enumerator_ `CanBeInstanced = 1 << 4` — True if the property can be instanced
- L386 _public* enumerator_ `CanExposeOnSpawn = 1 << 5` — True if the property can be exposed on spawn
- L391 _public* enumerator_ `CanHaveConfig = 1 << 6` — True if the property can have a config setting
- L396 _public* enumerator_ `CanBeBlueprintAssignable = 1 << 7` — True if the property allows the BlueprintAssignable flag.
- L401 _public* enumerator_ `CanBeBlueprintCallable = 1 << 8` — True if the property allows the BlueprintCallable flag.
- L406 _public* enumerator_ `CanBeBlueprintAuthorityOnly = 1 << 9` — True if the property allows the BlueprintAuthorityOnly flag.
- L411 _public* enumerator_ `IsParameterSupportedByBlueprint = 1 << 10` — True to see if the function parameter property is supported by blueprint
- L416 _public* enumerator_ `IsMemberSupportedByBlueprint = 1 << 11` — True to see if the member property is supported by blueprint
- L421 _public* enumerator_ `SupportsRigVM = 1 << 12` — True if the property supports RigVM
- L426 _public* enumerator_ `IsRigVMEnum = 1 << 13` — True if the property should codegen as an enumeration
- L431 _public* enumerator_ `IsRigVMArray = 1 << 14` — True if the property should codegen as an array
- L436 _public* enumerator_ `IsRigVMEnumAsByte = 1 << 15` — True if the property should codegen as a byte enumeration
- L441 _public* enumerator_ `CanBeOptionalValue = 1 << 16` — If true, the property type can be TOptional value
- L446 _public* enumerator_ `SupportsVerse = 1 << 17` — If true, the property type can be used in conjunction with verse

#### class `EpicGames.UHT.Types.UhtPropertyCapsExtensions`  
`public static class UhtPropertyCapsExtensions`  
_public; L453-489_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L462-465 _public method_ `public static bool HasAnyFlags(this UhtPropertyCaps inFlags, UhtPropertyCaps testFlags)` — Test to see if any of the specified flags are set
- L473-476 _public method_ `public static bool HasAllFlags(this UhtPropertyCaps inFlags, UhtPropertyCaps testFlags)` — Test to see if all of the specified flags are set
- L485-488 _public method_ `public static bool HasExactFlags(this UhtPropertyCaps inFlags, UhtPropertyCaps testFlags, UhtPropertyCaps matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtPropertyTextType`  
`public enum UhtPropertyTextType`  
_public; L494-595_
- desc: Text can be formatted in different context with slightly different results
- L499 _public* enumerator_ `Generic` — Generic type
- L504 _public* enumerator_ `GenericFunctionArgOrRetVal` — Generic function argument or return value
- L509 _public* enumerator_ `GenericFunctionArgOrRetValImpl` — Generic function argument or return value implementation (specific to booleans and will always return "bool")
- L514 _public* enumerator_ `ClassFunctionArgOrRetVal` — Class function argument or return value
- L519 _public* enumerator_ `EventFunctionArgOrRetVal` — Event function argument or return value
- L524 _public* enumerator_ `InterfaceFunctionArgOrRetVal` — Interface function argument or return value
- L529 _public* enumerator_ `Sparse` — Sparse property declaration
- L534 _public* enumerator_ `SparseShort` — Sparse property short name
- L539 _public* enumerator_ `ExportMember` — Class or structure member
- L544 _public* enumerator_ `EventParameterMember` — Members of the event parameters structure used by code generation to invoke events
- L549 _public* enumerator_ `EventParameterFunctionMember` — Members of the event parameters structure used by code generation to invoke functions
- L554 _public* enumerator_ `Construction` — Instance of the property is being constructed
- L559 _public* enumerator_ `FunctionThunkParameterArrayType` — Used to get the type argument for a function thunk. This is used for P_GET_ARRAY_*
- L564 _public* enumerator_ `FunctionThunkParameterArgType` — If the P_GET macro requires an argument, this is used to fetch that argument
- L569 _public* enumerator_ `FunctionThunkRetVal` — Used to get the return type for function thunks
- L574 _public* enumerator_ `RigVMType` — Basic RigVM type
- L579 _public* enumerator_ `GetterSetterArg` — Type expected in a getter/setter argument list
- L584 _public* enumerator_ `GetterRetVal` — Type expected from a getter
- L589 _public* enumerator_ `SetterParameterArgType` — Type expected as a setter argument
- L594 _public* enumerator_ `VerseMangledType` — Used when mangling a function

#### class `EpicGames.UHT.Types.UhtPropertyTextTypeExtensions`  
`public static class UhtPropertyTextTypeExtensions`  
_public; L600-631_
- desc: Extension methods for the property text type
- L608-617 _public method_ `public static bool IsParameter(this UhtPropertyTextType textType)` — Test to see if the text type is for a function
- L624-630 _public method_ `public static bool IsGetOrSet(this UhtPropertyTextType textType)` — Test to see if the text type is for a getter retVal or setter argType

#### enum `EpicGames.UHT.Types.UhtPGetArgumentType`  
`public enum UhtPGetArgumentType`  
_public; L637-650_
- desc: Specifies how the PGet argument type is to be formatted
- L641 _public* enumerator_ `None`
- L645 _public* enumerator_ `EngineClass`
- L649 _public* enumerator_ `TypeText`

#### interface `EpicGames.UHT.Types.IUhtPropertyMemberContext`  
`public interface IUhtPropertyMemberContext : IUhtObjectLinker`  
_public; L655-678_
- inherits: `IUhtObjectLinker`
- desc: Property member context provides extra context when formatting the member declaration and definitions.
- L660 _public property_ `public UhtStruct OuterStruct { get; }` — The outer/owning structure
- L665 _public property_ `public UhtCppIdentifier OuterIdentifier { get; }` — The OuterStruct's identifier
- L670 _public property_ `public bool IsLegacy { get; }` — If true, we are generating the legacy version of the property
- L677 _public method_ `public IoHash GetTypeHash(UhtObject obj)` — Return the hash code for a given object

#### record struct `EpicGames.UHT.Types.UhtChildProperty`  
`public record struct UhtChildProperty(UhtProperty Property, UhtCppIdentifier Identifier, string Offset = "0")`  
_public; L686-686_
- desc: Information about a child property mostly intended for code generation

#### class `EpicGames.UHT.Types.UhtPropertySettings`  
`public class UhtPropertySettings`  
_public; L692-961_
- attrs: `[DebuggerDisplay("Type = {TypeTokens}")]`
- desc: Property settings is a transient object used during the parsing of properties
- L698 _public property_ `public UhtPropertySettings? ParentSettings { get; set; }` — For nested properties, this points to the parent
- L703-714 _public property_ `public UhtPropertySettings RootSettings { get; }` — The root settings for a nested property
- L719 _public property_ `public string SourceName { get; set; }` — Source name of the property
- L724 _public property_ `public string EngineName { get; set; }` — Engine name of the property
- L729 _public property_ `public string VerseName { get; set; }` — Verse name of the property
- L734 _public property_ `public UhtMetaData MetaData { get; set; }` — Property's meta data
- L739 _public property_ `public UhtType Outer { get; set; }` — Property outer object
- L744 _public property_ `public int LineNumber { get; set; }` — Line number of the property declaration
- L749 _public property_ `public UhtPropertyCategory PropertyCategory { get; set; }` — Property category
- L754 _public property_ `public EPropertyFlags PropertyFlags { get; set; }` — Engine property flags
- L759 _public property_ `public EPropertyFlags DisallowPropertyFlags { get; set; }` — Property flags not allowed by the context of the property parsing
- L764 _public property_ `public UhtPropertyExportFlags PropertyExportFlags { get; set; }` — UHT specified property flags
- L769 _public property_ `public UhtDefineScope DefineScope { get; set; }` — #define scope of where the property exists
- L774 _public property_ `public UhtPropertyAllocator Allocator { get; set; }` — Allocator used for containers
- L779 _public property_ `public UhtPropertyOptions Options { get; set; }` — Options for property parsing
- L784 _public property_ `public UhtPointerType PointerType { get; set; }` — Property pointer type
- L789 _public property_ `public string? RepNotifyName { get; set; }` — Replication notify name
- L794 _public property_ `public string? ArrayDimensions { get; set; }` — If set, the array size of the property
- L799 _public property_ `public string? Setter { get; set; }` — Getter method
- L804 _public property_ `public string? Getter { get; set; }` — Setter method
- L810 _public property_ `public List<UhtToken>? DefaultValueTokens { get; set; }` — attrs: `[SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "")]` — Default value of the property
- L816 _public property_ `public UhtTypeTokensRef TypeTokens { get; set; }` — Collection of the tokens used to declare the property type. The type tokens are only valid for the outermost property.
- L821 _public property_ `public bool IsBitfield { get; set; }` — If true, the property is a bit field
- L827-830 _public ctor_ `public UhtPropertySettings()` — Construct a new, uninitialized version of the property settings
- L838-862 _public method_ `public void Reset(UhtPropertySettings parentPropertySettings, string sourceName, IUhtMessageSite messageSite)` — Construct property settings based on the property settings for a parent container
- L868-892 _public method_ `public void Copy(UhtPropertySettings propertySettings)` — Copy property settings
- L901-924 _public method_ `public void Reset(UhtType outer, int lineNumber, UhtPropertyCategory propertyCategory, EPropertyFlags disallowPropertyFlags)` — Reset the property settings. Used on a cached property settings object
- L932-960 _public method_ `public void Reset(UhtProperty property, UhtPropertyOptions options)` — Reset property settings based on the given property. Used to prepare a cached property settings for parsing.

#### class `EpicGames.UHT.Types.UhtProperty`  
`public abstract class UhtProperty : UhtType`  
_public; L969-2762_
- attrs: `[UhtEngineClass(Name = "Field", IsProperty = true)] [UhtEngineClass(Name = "Property", IsProperty = true)] [DebuggerDisplay("Name = {SourceName}, Type = {TypeTokens}")]`
- inherits: `UhtType`
- desc: Represents FProperty fields
- L975 _private field_ `private static readonly string[] s_casts = [ "(uint32)", "(int32)", "(uint16)", "(int16)", "(uint8)", "(int8)", "(int)", "(unsigned)", "(signed)", "(unsigned int)", "(signed int)", "static_cast<uint32>", "static_cast<int32>", "static_cast<uint ...` — Collection of recognized casts when parsing array dimensions
- L1004 _private field_ `private static readonly HashSet<string> s_invalidParamNames = new(StringComparer.OrdinalIgnoreCase) { "self" }` — Collection of invalid names for parameters
- L1009 _protected const_ `protected const string FunctionParameterThunkPrefix = "Z_Param_"` — Prefix used when declaring P_GET_ parameters
- L1016 _protected property_ `protected abstract string CppTypeText { get; }` — Simple native CPP type text. Will not include any template arguments
- L1021 _protected property_ `protected abstract string PGetMacroText { get; }` — P_GET_ macro name
- L1026 _protected property_ `protected virtual bool PGetPassAsNoPtr => ...` — If true, then references must be passed without a pointer
- L1031 _protected property_ `protected virtual UhtPGetArgumentType PGetTypeArgument => ...` — Type of the PGet argument if one is required
- L1036 _public property_ `public virtual bool CodeGenWrapInRestValue => ...` — If true, then with the new VM, wrap the type in a rest value
- L1041 _protected property_ `protected virtual string CodeGenParamsStruct => ...` — Name of the code generation structure used when doing params code gen
- L1046 _protected property_ `protected virtual string CodeGenParamsFlags => ...` — Flags to include when generating the params code gen structure
- L1051 _protected property_ `protected virtual bool CodeGenParamsAppendOffset => ...` — If true, add the offset to the start of the params declaration
- L1057 _public property_ `public string VerseNameOverride { get; set; }` — If set, the name was set via a UPROPERTY or UPARAM
- L1062 _public property_ `public string VerseName => ...` — Verse name of the property
- L1068 _public property_ `public UhtPropertyCategory PropertyCategory { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Property category
- L1074 _public property_ `public EPropertyFlags PropertyFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Engine property flags
- L1081 _public property_ `public UhtPropertyCaps PropertyCaps { get; set; }` — attrs: `[JsonIgnore] [JsonConverter(typeof(JsonStringEnumConverter))]` — Capabilities of the property. Use caps system instead of testing for specific property types.
- L1088 _public property_ `public EPropertyFlags DisallowPropertyFlags { get; set; }` — attrs: `[JsonIgnore] [JsonConverter(typeof(JsonStringEnumConverter))]` — Engine flags that are disallowed on this property
- L1094 _public property_ `public UhtPropertyExportFlags PropertyExportFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — UHT specified property flags
- L1100 _public property_ `public UhtPropertyRefQualifier RefQualifier { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Reference type of the property
- L1106 _public property_ `public UhtPointerType PointerType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Pointer type of the property
- L1112 _public property_ `public UhtPropertyAllocator Allocator { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Allocator to be used with containers
- L1118 _public property_ `public UhtTypeTokensRef TypeTokens { get; set; }` — attrs: `[JsonIgnore]` — Collection of tokens that declare the type of the property.
- L1123 _public property_ `public string? RepNotifyName { get; set; }` — Replication notify name
- L1128 _public property_ `public string? ArrayDimensions { get; set; }` — Fixed array size
- L1133 _public property_ `public string? Setter { get; set; }` — Property setter
- L1138 _public property_ `public string? Getter { get; set; }` — Property getter
- L1145 _public property_ `public List<UhtToken>? DefaultValueTokens { get; set; }` — attrs: `[JsonIgnore] [SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "<Pending>")]` — Default value of property
- L1150 _public property_ `public bool IsBitfield { get; set; }` — If true, this property is a bit field
- L1154 _public property_ `public override UhtEngineType EngineType => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L1158 _public property_ `public override UhtClass? EngineClass => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L1162 _public property_ `public override bool Deprecated => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L1168-1179 _public property_ `public virtual string StrippedEngineName { get; }` — attrs: `[JsonIgnore]` — Return the engine name without and 'b' prefixes
- L1183-1199 _protected property_ `protected override UhtSpecifierValidatorTable? SpecifierValidatorTable { get; }` — attrs: `[JsonIgnore]` — (inheritdoc)
- L1205 _public property_ `public bool IsStaticArray => ...` — attrs: `[JsonIgnore]` — If true, the property is a fixed/static array
- L1211 _public property_ `public bool IsEditorOnlyProperty => ...` — attrs: `[JsonIgnore]` — If true, the property is editor only
- L1216 _public property_ `public UhtDefineScopeLink<UhtProperty>? NextProperty { get; set; }` — After properties are fully resolved, points to the next property in the owning struct in each define scope.
- L1221 _public property_ `public bool HasGetterOrSetter => ...` — Returns whether this property has a setter or getter function and therefor needs to be wrapped in a template property type
- L1227-1242 _public property_ `public UhtProperty RootProperty { get; }` — Return the root property for the given property. If the property is outside of a container, return the property itself. Otherwise, return the property associated with the container.
- L1249-1253 _protected ctor_ `protected UhtProperty(UhtType outer, int lineNumber) : base(outer.HeaderFile, outer, lineNumber)` — Construct a new property
- L1259-1283 _protected ctor_ `protected UhtProperty(UhtPropertySettings propertySettings) : base(propertySettings.Outer.HeaderFile, propertySettings.Outer, propertySettings.LineNumber, propertySettings.MetaData)` — Construct a new property
- L1290-1318 _protected ctor_ `protected UhtProperty(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L1324-1349 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L1359-1363 _public method_ `public virtual StringBuilder AppendText(StringBuilder builder, UhtPropertyTextType textType, bool isTemplateArgument = false)` — Internal version of AppendText. Don't append any text to the builder to get the default behavior
- L1372-1435 _public method_ `public virtual StringBuilder AppendFullDecl(StringBuilder builder, UhtPropertyTextType textType, bool skipParameterName = false)` — Append the full declaration including such things as property name and const requirements
- L1498-1501 _public method_ `public virtual IEnumerable<UhtChildProperty> EnumerateChildProperties(UhtCppIdentifier identifier, UhtChildPropertyOrder order)` — Return a collection of child properties
- L1512-1519 _public method_ `public virtual StringBuilder AppendMetaData(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append the required code to declare the properties meta data
- L1532-1535 _protected method_ `protected virtual StringBuilder AppendCommonDecl(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append any code common to all code gen styles into the statics declaration
- L1545-1548 _protected method_ `protected virtual StringBuilder AppendCommonDef(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append any code common to all code gen styles outside of the statics definition
- L1558-1566 _public method_ `public virtual StringBuilder AppendParamsDecl(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append the required code to declare the property as a member
- L1576-1580 _public method_ `public static StringBuilder AppendParamsDecl(StringBuilder builder, UhtCppIdentifier identifier, int tabs, string paramsStructName)` — Append the required code to declare the property as a member
- L1591-1599 _public method_ `public virtual StringBuilder AppendParamsDef(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, string? offset, int tabs)` — Append the required code to define the property as a member
- L1610-1616 _protected method_ `protected virtual StringBuilder AppendParamsDefImpl(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, string? offset, int tabs)` — Append the required code to define the property as a member
- L1625-1628 _protected method_ `protected virtual StringBuilder AppendParamsDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — Append the required code to define the property as a member
- L1643-1686 _public method_ `public static StringBuilder AppendParamsDefStart(StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, string? offset, int tabs, string paramsStructName, string paramsGenFlags, bool appendOffset)` — Append the required start of code to define the property as a member
- L1696-1703 _public method_ `public static StringBuilder AppendParamsDefEnd(StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — Append the required end of code to define the property as a member
- L1714-1729 _protected method_ `protected static StringBuilder AppendParamsDefRef(StringBuilder builder, IUhtPropertyMemberContext context, UhtObject? obj, UhtSingletonType type, bool appendNull = false)` — Append the a type reference to the member definition
- L1739-1747 _public method_ `public virtual StringBuilder AppendParamsPtr(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append the required code to add the properties to a pointer array
- L1761-1770 _public method_ `public virtual StringBuilder AppendConstInitDecl(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append a declaration of the given property as a constinit variable. For non-compound properties this is simply a declaration of a single variable of the appropriate type. For compound properties this must be overridden to declare the inner/key/value property.
- L1783-1788 _public method_ `public static StringBuilder AppendConstInitDecl(StringBuilder builder, UhtProperty property, UhtCppIdentifier identifier, int tabs, string engineClassName)` — Append a declaration of the given property as a constinit variable. For non-compound properties this is simply a declaration of a single variable of the appropriate type. For compound properties this must be overridden to declare the inner/key/value property.
- L1800-1810 _public method_ `public virtual StringBuilder AppendConstInitDef(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, Action<StringBuilder>? outerFunc, string? offset, int tabs)` — Append a full definition of constinit variable(s) for this property
- L1822-1828 _protected method_ `protected virtual StringBuilder AppendConstInitDefImpl(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, Action<StringBuilder>? outerFunc, string? offset, int tabs)` — Append a full definition of constinit variable(s) for this property
- L1837-1844 _protected method_ `protected virtual StringBuilder AppendConstInitDefExtra(StringBuilder builder, IUhtPropertyMemberContext context, UhtCppIdentifier identifier)` — Append the required code to define the property as a member
- L1858-1950 _public method_ `public static StringBuilder AppendConstInitDefStart(StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, Action<StringBuilder>? outerFunc, string? offset, int tabs, string engineClassName)` — Append the required start of code to define a constinit property variable for the member
- L1959-1966 _public method_ `public static StringBuilder AppendConstInitDefEnd(StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context)` — Append the required end of code to define the property as a member
- L1976-1980 _public method_ `public virtual StringBuilder AppendConstInitPtr(StringBuilder builder, UhtCppIdentifier identifier, int tabs, string? post)` — Append an expression to get a pointer to the property object
- L1988-1998 _public method_ `public StringBuilder AppendGetNextProperty(StringBuilder builder, int tabs)` — If this property needs a different 'next property' pointer under different preprocessor definitions, append an inline function that returns the correct property in each preprocessor state.
- L2006-2051 _public method_ `public virtual StringBuilder AppendFunctionThunkParameterGet(StringBuilder builder)` — Append a P_GET macro
- L2058-2061 _public method_ `public virtual StringBuilder AppendFunctionThunkParameterArg(StringBuilder builder)` — Append the text for a function thunk call argument
- L2068-2077 _public method_ `public StringBuilder AppendFunctionThunkParameterName(StringBuilder builder)` — Append the name of a function thunk parameter
- L2086-2100 _public method_ `public StringBuilder AppendVerseArgumentUnmarshal(StringBuilder builder, bool isVerseVM)` — Append the Verse function unmarshaling for the given argument
- L2108-2111 _protected method_ `protected virtual StringBuilder AppendTypedVerseArgumentUnmarshal(StringBuilder builder)` — Append the Verse function marshaling for the given argument
- L2119 _public method_ `public abstract StringBuilder AppendNullConstructorArg(StringBuilder builder, bool isInitializer)` — Append the appropriate values to initialize the property to a "NULL" value;
- L2125-2130 _public method_ `public string GetUserFacingDecl()` — Return the basic declaration type text for user facing messages
- L2136-2141 _public method_ `public string GetRigVMType()` — Return the RigVM type
- L2149-2151 _public method_ `public virtual void AppendObjectHashes(StringBuilder builder, int startingLength, IUhtPropertyMemberContext context)` — Appends any applicable objects and child properties
- L2157-2168 _public method_ `public (bool WasMangled, string Result) GetMangledEngineName()` — Fetch the mangled name for a property
- L2180 _public method_ `public abstract bool SanitizeDefaultValue(IUhtTokenReader defaultValueReader, StringBuilder innerDefaultValue)` — Parse a default value for the property and return a sanitized string representation. All tokens in the token reader must be consumed. Otherwise the default value will be considered to be invalid.
- L2185-2283 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase phase)` — (inheritdoc)
- L2291-2294 _public method_ `public virtual bool ScanForInstancedReferenced(bool deepScan)` — Check properties to see if any instances are referenced. This method does NOT cache the result.
- L2299-2353 _protected method_ `protected override UhtValidationOptions Validate(UhtValidationOptions options)` — (inheritdoc)
- L2355-2358 _private method_ `private void LogShadowingError(UhtType shadows)`
- L2367-2487 _public method_ `public virtual void Validate(UhtStruct outerStruct, UhtProperty outermostProperty, UhtValidationOptions options)` — Validate the property settings
- L2492-2494 _public method_ `public virtual void ValidateDeprecated()` — Validate that we don't reference any deprecated classes
- L2499-2540 _protected method_ `protected virtual void ValidateFunctionArgument(UhtFunction func, UhtValidationOptions options)` — Verify function argument
- L2547-2606 _protected method_ `protected virtual void ValidateMember(UhtStruct structObj, UhtValidationOptions options)` — Validate member settings
- L2612-2632 _protected method_ `protected void ValidateDeprecatedClass(UhtClass? classObj)` — Generate an error if the class has been deprecated
- L2639-2642 _public method_ `public virtual bool ValidateStructPropertyOkForNet(UhtProperty referencingProperty)` — Check to see if the property is valid as a member of a networked structure
- L2649-2653 _public method_ `public virtual bool MustBeConstArgument([NotNullWhen(true)] out UhtType? errorType)` — Test to see if this property references something that requires the argument to be marked as const
- L2665-2669 _public method_ `public virtual bool IsAllowedInOptionalClass([NotNullWhen(false)] out string? propPath)` — Test to see if this property (and it's fields for a struct) are allowed in Optional classes. Due to how we choose to save the properties when saving (while filtering editor-only), just marking a struct property as allowed in optional (with AllowedInOptional metadata) won't force all nested properties to be serialized, so the whole hierarchy of properties must be non-EditorOnly or be marked with AllowedInOptional. So, this function checks itself and all children properties, looking for any EditorOnly properties without AllowedInOptional Additionally, if any bad property is found, it will return a string describing the path to the property
- L2674-2681 _public method_ `public override void CollectReferences(IUhtReferenceCollector collector)` — (inheritdoc)
- L2690-2692 _public method_ `public virtual void CollectReferencesInternal(IUhtReferenceCollector collector, bool addForwardDeclarations, bool isTemplateProperty)` — Collect the references for the property. This method is used by container properties to collect the contained property's references.
- L2698-2701 _public method_ `public virtual IEnumerable<UhtType> EnumerateReferencedTypes()` — Enumerate all reference types. This method is used exclusively by FindNoExportStructsRecursive
- L2709-2716 _public method_ `public bool NeedsGCBarrierWhenPassedToFunction(UhtFunction function)` — Determines whether or not GC barriers need to run after passing this to a function
- L2722-2725 _protected method_ `protected virtual bool NeedsGCBarrierWhenPassedToFunctionImpl(UhtFunction uhtFunction)` — Customization point for subclasses for NeedsGCBarrierWhenPassedToFunction
- L2734 _public method_ `public abstract bool IsSameType(UhtProperty other)` — Test to see if the two properties are the same type
- L2741-2760 _public method_ `public bool MatchesType(UhtProperty other)` — Test to see if the two properties are the same type and ConstParm/OutParm flags somewhat match

#### enum `EpicGames.UHT.Types.UhtProperty.UhtChildPropertyOrder`  
`public enum UhtChildPropertyOrder`  
_public; L1440-1451_
- desc: Specifies the order that the child properties are to be returned
- L1445 _public* enumerator_ `Forward` — Ordered from smallest to largest offset
- L1450 _public* enumerator_ `Reverse` — Ordered from largest to smallest offset

#### class `EpicGames.UHT.Types.UhtPropertyStringBuilderExtensions`  
`public static class UhtPropertyStringBuilderExtensions`  
_public; L2767-3160_
- desc: Assorted StringBuilder extensions for properties
- L2778-2786 _public method_ `public static StringBuilder AppendPropertyText(this StringBuilder builder, UhtProperty property, UhtPropertyTextType textType, bool isTemplateArgument = false)` — Add the given property text
- L2797-2800 _public method_ `public static StringBuilder AppendParamsDecl(this StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append the member declaration
- L2812-2815 _public method_ `public static StringBuilder AppendParamsDef(this StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, string? offset, int tabs)` — Append the member definition
- L2826-2829 _public method_ `public static StringBuilder AppendParamsPtr(this StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append the member pointer
- L2840-2843 _public method_ `public static StringBuilder AppendConstInitDecl(this StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, int tabs)` — Append a declaration of a constinit variable representing the given property.
- L2856-2859 _public method_ `public static StringBuilder AppendConstInitDef(this StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context, UhtCppIdentifier identifier, Action<StringBuilder>? outerFunc, string? offset, int tabs)` — Append a definition of the constinit variable representing the property
- L2870-2877 _public method_ `public static StringBuilder AppendConstInitPtr(this StringBuilder builder, UhtProperty? property, UhtCppIdentifier identifier, int tabs, string? post)` — Append an expression resolving to a pointer to the constinit object instance for this property
- L2887-2890 _public method_ `public static StringBuilder AppendFullDecl(this StringBuilder builder, UhtProperty property, UhtPropertyTextType textType, bool skipParameterName)` — Append the full declaration including such things as const, *, and &
- L2898-2901 _public method_ `public static StringBuilder AppendFunctionThunkParameterGet(this StringBuilder builder, UhtProperty property)` — Append the function thunk parameter get
- L2910-2913 _public method_ `public static StringBuilder AppendFunctionThunkParameterArrayType(this StringBuilder builder, UhtProperty property, bool isTemplateArgument = false)` — Append the function thunk parameter array type
- L2922-2925 _public method_ `public static StringBuilder AppendFunctionThunkParameterArgType(this StringBuilder builder, UhtProperty property, bool isTemplateArgument = false)` — Append the function thunk parameter argument type
- L2933-2936 _public method_ `public static StringBuilder AppendFunctionThunkParameterArg(this StringBuilder builder, UhtProperty property)` — Append the function thunk parameter argument
- L2944-2947 _public method_ `public static StringBuilder AppendFunctionThunkReturn(this StringBuilder builder, UhtProperty property)` — Append the function thunk return
- L2955-2958 _public method_ `public static StringBuilder AppendFunctionThunkParameterName(this StringBuilder builder, UhtProperty property)` — Append the function thunk parameter name
- L2966-2969 _public method_ `public static StringBuilder AppendSparse(this StringBuilder builder, UhtProperty property)` — Append the sparse type
- L2978-2982 _public method_ `public static StringBuilder AppendNullConstructorArg(this StringBuilder builder, UhtProperty property, bool isInitializer)` — Append the property's null constructor arg
- L2990-3001 _public method_ `public static StringBuilder AppendNotifyFunc(this StringBuilder builder, UhtProperty property)` — Append the replication notify function or a 'nullptr'
- L3009-3013 _public method_ `public static StringBuilder AppendFlags(this StringBuilder builder, EPropertyFlags propertyFlags)` — Append the parameter flags
- L3022-3033 _public method_ `public static StringBuilder AppendArrayDim(this StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context)` — Append the property array dimensions as a CPP_ARRAY_DIM macro or '1' if not a fixed array.
- L3044-3074 _public method_ `public static StringBuilder AppendObjectHash(this StringBuilder builder, int startingLength, UhtType referingType, IUhtPropertyMemberContext context, UhtObject? obj)` — Given an object, append the hash (if applicable) to the builder
- L3084-3087 _public method_ `public static StringBuilder AppendObjectHash(this StringBuilder builder, UhtType referingType, IUhtPropertyMemberContext context, UhtObject? obj)` — Given an object, append the hash (if applicable) to the builder
- L3096-3100 _public method_ `public static StringBuilder AppendObjectHashes(this StringBuilder builder, UhtProperty property, IUhtPropertyMemberContext context)` — Append the object hashes for all referenced objects
- L3110-3113 _public method_ `public static StringBuilder AppendSingletonName(this StringBuilder builder, IUhtSingletonNameProvider provider, UhtObject? type, UhtSingletonType singletonType)` — Append the singleton name for the given type
- L3121-3124 _public method_ `public static StringBuilder AppendPropertyGetterWrapperName(this StringBuilder builder, UhtProperty property)` — Append the getter wrapper name
- L3132-3135 _public method_ `public static StringBuilder AppendPropertySetterWrapperName(this StringBuilder builder, UhtProperty property)` — Append the setter wrapper name
- L3143-3146 _public method_ `public static StringBuilder AppendPropertyVerseMangledType(this StringBuilder builder, UhtProperty property)` — Append the mangled type for function name mangling
- L3156-3159 _public method_ `public static StringBuilder AppendVerseArgumentUnmarshal(this StringBuilder builder, UhtProperty property, bool isVerseVM)` — Append the Verse function marshaling for the given argument

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtScriptStruct.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtRigVMParameterFlags`  
`public enum UhtRigVMParameterFlags : int`  
_public; L20-77_
- attrs: `[Flags]`
- inherits: `int`
- desc: Flags to represent information about a RigVM parameter
- L25 _public* enumerator_ `None = 0` — No RigVM flags
- L30 _public* enumerator_ `Constant = 0x00000001` — "Constant" metadata specified
- L35 _public* enumerator_ `Input = 0x00000002` — "Input" metadata specified
- L40 _public* enumerator_ `Output = 0x00000004` — "Output" metadata specified
- L45 _public* enumerator_ `Singleton = 0x00000008` — "Singleton" metadata specified
- L50 _public* enumerator_ `EditorOnly = 0x00000010` — Set if the property is editor only
- L56 _public* enumerator_ `InputVariable = 0x00000020` — "ExternalVariable" metadata specified — marks an Input pin as a mutable input variable. The parameter is directionally an input but generates a non-const reference (T& instead of const T&).
- L61 _public* enumerator_ `IsEnum = 0x00010000` — Set if the property is an enum
- L66 _public* enumerator_ `IsArray = 0x00020000` — Set if the property is an array
- L71 _public* enumerator_ `IsEnumAsByte = 0x00040000` — Set if the property is an enum as byte
- L76 _public* enumerator_ `IsLazy = 0x00080000` — Computes the value lazily

#### class `EpicGames.UHT.Types.UhtRigVMParameterFlagsExtensions`  
`public static class UhtRigVMParameterFlagsExtensions`  
_public; L83-119_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L92-95 _public method_ `public static bool HasAnyFlags(this UhtRigVMParameterFlags inFlags, UhtRigVMParameterFlags testFlags)` — Test to see if any of the specified flags are set
- L103-106 _public method_ `public static bool HasAllFlags(this UhtRigVMParameterFlags inFlags, UhtRigVMParameterFlags testFlags)` — Test to see if all of the specified flags are set
- L115-118 _public method_ `public static bool HasExactFlags(this UhtRigVMParameterFlags inFlags, UhtRigVMParameterFlags testFlags, UhtRigVMParameterFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Types.UhtRigVMParameter`  
`public class UhtRigVMParameter`  
_public; L127-572_
- desc: The FRigVMParameter represents a single parameter of a method marked up with RIGVM_METHOD. Each parameter can be marked with Constant, Input or Output metadata - this struct simplifies access to that information.
- L133 _public property_ `public UhtProperty? Property { get; }` — attrs: `[JsonConverter(typeof(UhtTypeSourceNameJsonConverter<UhtProperty>))]` — Property associated with the RigVM parameter
- L138 _public property_ `public string Name { get; }` — Name of the property
- L143 _public property_ `public string Type { get; }` — Type of the property
- L149 _public property_ `public string? CastName { get; }` — attrs: `[JsonIgnore]` — Cast name
- L155 _public property_ `public string? CastType { get; }` — attrs: `[JsonIgnore]` — Cast type
- L161 _public property_ `public UhtRigVMParameterFlags ParameterFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Flags associated with the parameter
- L167 _public property_ `public bool Constant => ...` — attrs: `[JsonIgnore]` — True if the parameter is marked as "Constant"
- L173 _public property_ `public bool Input => ...` — attrs: `[JsonIgnore]` — True if the parameter is marked as "Input"
- L179 _public property_ `public bool Output => ...` — attrs: `[JsonIgnore]` — True if the parameter is marked as "Output"
- L185 _public property_ `public bool Singleton => ...` — attrs: `[JsonIgnore]` — True if the parameter is marked as "Singleton"
- L191 _public property_ `public bool InputVariable => ...` — attrs: `[JsonIgnore]` — True if the parameter is marked as "ExternalVariable" — a mutable input variable
- L197 _public property_ `public bool EditorOnly => ...` — attrs: `[JsonIgnore]` — True if the parameter is editor only
- L203 _public property_ `public bool IsEnum => ...` — attrs: `[JsonIgnore]` — True if the parameter is an enum
- L209 _public property_ `public bool IsEnumAsByte => ...` — attrs: `[JsonIgnore]` — True if the parameter is an enum as byte
- L215 _public property_ `public bool IsLazy => ...` — attrs: `[JsonIgnore]` — True if the parameter should be computed lazily
- L221 _public property_ `public bool IsArray => ...` — attrs: `[JsonIgnore]` — True if the parameter is an array
- L228-312 _public ctor_ `public UhtRigVMParameter(UhtProperty property, int index)` — Create a new RigVM parameter from a property
- L319-323 _public ctor_ `public UhtRigVMParameter(string name, string type)` — Create a new parameter
- L329-337 _public ctor_ `public UhtRigVMParameter(UhtInputCacheReader reader)` — Construct a type from the cache
- L343-351 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write the output type
- L358-361 _public method_ `public string NameOriginal(bool castName = false)` — Get the name of the parameter
- L369-372 _public method_ `public string TypeOriginal(bool castType = false, bool wrapLazyType = true)` — Get the type of the parameter
- L380-383 _public method_ `public string Declaration(bool castType = false, bool castName = false)` — Get the full declaration (type and name)
- L390-403 _public method_ `public string BaseType(bool castType = false)` — Return the base type without any template arguments
- L410-423 _public method_ `public string ExtendedType(bool castType = false)` — Template arguments of the type or type if not a template type.
- L430-444 _public method_ `public string TypeConstRef(bool castType = false)` — Return the type with a const reference
- L451-455 _public method_ `public string TypeRef(bool castType = false)` — Return the type with a reference
- L462-473 _public method_ `public string TypeNoRef(bool castType = false)` — Return the type without reference
- L480-483 _public method_ `public string TypeVariableRef(bool castType = false)` — Return the type as a reference
- L491-498 _public method_ `public string GetLazyType(string typeToWrap, bool wrapLazyType)` — Return the type wrapped with a lazy struct as needed
- L506-509 _public method_ `public string Variable(bool castType = false, bool castName = false)` — Return a variable declaration for the parameter
- L517-520 _public method_ `public bool IsConst()` — True if the parameter is constant. InputVariable params are mutable inputs — they emit T& not const T&, so they are not const even though they have the Input flag set.
- L526-529 _public method_ `public bool RequiresCast()` — Return true if the parameter requires a cast
- L535-550 _public method_ `public bool IsExecuteContext()` — Return true if the parameter is an execute context
- L556-571 _public method_ `public bool IsEmptyExecuteContext()` — Return true if the parameter is an empty execute context

#### class `EpicGames.UHT.Types.UhtRigVMMethodInfo`  
`public class UhtRigVMMethodInfo`  
_public; L578-650_
- desc: A single info dataset for a function marked with RIGVM_METHOD. This struct provides access to its name, the return type and all parameters.
- L580 _private field_ `private static readonly string s_noPrefix = String.Empty`
- L581 _private const_ `private const string ReturnPrefixInternal = "return "`
- L586 _public property_ `public string ReturnType { get; set; }` — Return type of the method
- L591 _public property_ `public string Name { get; set; }` — Name of the method
- L596 _public property_ `public List<UhtRigVMParameter> Parameters { get; }` — Method parameters
- L602-605 _public method_ `public string ReturnPrefix()` — If the method has a return value, return "return". Otherwise return nothing.
- L610 _public property_ `public bool IsPredicate { get; set; }` — Whether or not this method is a predicate.
- L616 _public property_ `public string DllStorage { get; set; }` — Is true if method has dll storage such as UE_API
- L621-623 _public ctor_ `public UhtRigVMMethodInfo()` — Construct a type from the cache
- L629-636 _public ctor_ `public UhtRigVMMethodInfo(UhtInputCacheReader reader)` — Construct a type from the cache
- L642-649 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write the output type

#### class `EpicGames.UHT.Types.UhtRigVMStructInfo`  
`public class UhtRigVMStructInfo`  
_public; L656-744_
- desc: An info dataset providing access to all functions marked with RIGVM_METHOD for each struct.
- L662 _public property_ `public bool HasGetUpgradeInfoMethod { get; set; }` — True if the GetUpgradeInfoMethod was found.
- L667 _public property_ `public bool HasGetNextAggregateNameMethod { get; set; }` — True if the GetNextAggregateNameMethod was found.
- L672 _public property_ `public string Name { get; set; }` — Engine name of the owning script struct
- L677 _public property_ `public string ExecuteContextType { get; set; }` — The name of the execute context to use for this struct's RigVM methods
- L682 _public property_ `public string ExecuteContextMember { get; set; }` — The name of a member on the struct providing an execute context
- L687 _public property_ `public bool HasAnyExecuteContextMember { get; set; }` — true if any of this structs members is an execute context (also an empty one)
- L692 _public property_ `public bool IsPure { get; set; }` — true if this struct has the Pure metadata (should receive const execute context)
- L697 _public property_ `public List<UhtRigVMParameter> Members { get; }` — List of the members
- L702 _public property_ `public List<UhtRigVMMethodInfo> Methods { get; }` — List of the methods
- L707-709 _public ctor_ `public UhtRigVMStructInfo()` — Construct a default instance
- L715-726 _public ctor_ `public UhtRigVMStructInfo(UhtInputCacheReader reader)` — Construct a type from the cache
- L732-743 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write the output type

#### enum `EpicGames.UHT.Types.UhtScriptStructExportFlags`  
`public enum UhtScriptStructExportFlags : int`  
_public; L750-792_
- attrs: `[Flags]`
- inherits: `int`
- desc: Series of flags not part of the engine's script struct flags that affect code generation or verification
- L756 _public* enumerator_ `None = 0` — No export flags
- L761 _public* enumerator_ `HasDefaults = 1 << 0` — "HasDefaults" specifier present
- L766 _public* enumerator_ `HasNoOpConstructor = 1 << 1` — "HasNoOpConstructor" specifier present
- L771 _public* enumerator_ `IsAlwaysAccessible = 1 << 2` — "IsAlwaysAccessible" specifier present
- L776 _public* enumerator_ `IsCoreType = 1 << 3` — "IsCoreType" specifier present
- L781 _public* enumerator_ `IsVerseParametric = 1 << 4` — "Parametric" specifier present
- L786 _public* enumerator_ `MinimalAPI = 1 << 5` — Indicates that the autogenerated functions of this struct will be DLL exported/imported
- L791 _public* enumerator_ `IsVersePersonaConstructible = 1 << 6` — Mark the verse structure as persona constructible.

#### class `EpicGames.UHT.Types.UhtScriptStructExportFlagsExtensions`  
`public static class UhtScriptStructExportFlagsExtensions`  
_public; L798-834_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L807-810 _public method_ `public static bool HasAnyFlags(this UhtScriptStructExportFlags inFlags, UhtScriptStructExportFlags testFlags)` — Test to see if any of the specified flags are set
- L818-821 _public method_ `public static bool HasAllFlags(this UhtScriptStructExportFlags inFlags, UhtScriptStructExportFlags testFlags)` — Test to see if all of the specified flags are set
- L830-833 _public method_ `public static bool HasExactFlags(this UhtScriptStructExportFlags inFlags, UhtScriptStructExportFlags testFlags, UhtScriptStructExportFlags matchFlags)` — Test to see if a specific set of flags have a specific value.

#### class `EpicGames.UHT.Types.UhtScriptStruct`  
`public class UhtScriptStruct : UhtStruct`  
_public; L840-1283_
- attrs: `[UhtEngineClass(Name = "ScriptStruct")]`
- inherits: `UhtStruct`
- desc: Represents the USTRUCT object
- L846 _public property_ `public EStructFlags ScriptStructFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Script struct engine flags
- L852 _public property_ `public UhtScriptStructExportFlags ScriptStructExportFlags { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — UHT only script struct flags
- L857 _public property_ `public int MacroDeclaredLineNumber { get; set; }` — Line number where GENERATED_BODY/GENERATED_USTRUCT_BODY macro was found
- L862 _public property_ `public UhtRigVMStructInfo? RigVMStructInfo { get; set; }` — RigVM structure info
- L866 _public property_ `public override UhtEngineType EngineType => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L872 _public property_ `public bool HasDefaults => ...` — attrs: `[JsonIgnore]` — True if the struct has the "HasDefaults" specifier
- L878 _public property_ `public bool IsAlwaysAccessible => ...` — attrs: `[JsonIgnore]` — True if the struct has the "IsAlwaysAccessible" specifier
- L884 _public property_ `public bool IsCoreType => ...` — attrs: `[JsonIgnore]` — True if the struct has the "IsCoreType" specifier
- L890 _public property_ `public bool HasNoOpConstructor => ...` — attrs: `[JsonIgnore]` — True if the struct has the "HasNoOpConstructor" specifier
- L893 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L896 _public property_ `public override string EngineLinkClassName => ...` — (inheritdoc)
- L899 _public property_ `public override UhtClass? EngineClass => ...` — (inheritdoc)
- L903 _public property_ `public override string EngineNamePrefix => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L909 _public property_ `public string NamespaceExportName => ...` — In certain cases (usually with NoExportTypes), a locally generated version of the structures is created and we do code generation based on it. In such cases, we can't use the namespace.
- L913 _protected property_ `protected override UhtSpecifierValidatorTable? SpecifierValidatorTable => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L919 _public property_ `public UhtScriptStruct? SuperScriptStruct => ...` — attrs: `[JsonConverter(typeof(UhtNullableTypeSourceNameJsonConverter<UhtScriptStruct>))]` — Super struct
- L928-930 _public ctor_ `public UhtScriptStruct(UhtHeaderFile headerFile, UhtNamespace namespaceObj, UhtType outer, int lineNumber) : base(headerFile, namespaceObj, outer, lineNumber)` — Construct a new script struct
- L937-943 _public ctor_ `public UhtScriptStruct(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L949-956 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L961-965 _public method_ `public override void BindSuperAndBases()` — (inheritdoc)
- L968-984 _protected method_ `protected override void ResolveSuper(UhtResolvePhase resolvePhase)` — (inheritdoc)
- L987-998 _protected method_ `protected override bool ResolveSelf(UhtResolvePhase resolvePhase)` — (inheritdoc)
- L1001-1064 _protected method_ `protected override void ResolveChildren(UhtResolvePhase phase)` — (inheritdoc)
- L1067-1080 _protected method_ `protected override bool ScanForInstancedReferencedInternal(bool deepScan)` — (inheritdoc)
- L1085-1125 _protected method_ `protected override UhtValidationOptions Validate(UhtValidationOptions options)` — (inheritdoc)
- L1127-1160 _private* method_ `void ValidateProperties()`
- L1164-1170 _protected method_ `protected override void AppendVerseMyScope(StringBuilder builder, UhtVerseNameMode mode, bool isTopLevel)` — (inheritdoc)
- L1173-1180 _protected method_ `protected override void AppendVerseName(StringBuilder builder, UhtVerseNameMode mode)` — (inheritdoc)
- L1183-1186 _public method_ `public override StringBuilder AppendForwardDeclaration(StringBuilder builder)` — (inheritdoc)
- L1189-1213 _public method_ `public override void CollectReferences(IUhtReferenceCollector collector)` — (inheritdoc)
- L1215-1282 _private method_ `private void CollectRigVMMembers()`

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtSourceFile.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtSourceFile`  
`public class UhtSourceFile : IUhtMessageSite, IUhtMessageSource`  
_public; L13-113_
- inherits: `IUhtMessageSite, IUhtMessageSource`
- desc: Represents a source file in UHT
- L15 _private field_ `private readonly UhtSimpleMessageSite _messageSite`
- L16 _private field_ `private UhtSourceFragment _sourceFragment`
- L21 _public property_ `public UhtSession Session { get; }` — The session associated with the source
- L26 _public property_ `public string FilePath { get; }` — The full file path
- L31 _public property_ `public string FileName { get; }` — The file name
- L36 _public property_ `public StringView Data => ...` — The contents of the source file
- L41 _public property_ `public UhtSourceFile? FragmentSourceFile => ...` — If this source is from a fragment, the original source file
- L46 _public property_ `public int FragmentLineNumber => ...` — If this source is from a fragment, the starting line of the fragment
- L51 _public property_ `public string FullFilePath => ...` — Full file path of the source file
- L55 _public property_ `public IUhtMessageSession MessageSession => ...` — (inheritdoc)
- L58 _public property_ `public IUhtMessageSource? MessageSource => ...` — (inheritdoc)
- L61 _public property_ `public IUhtMessageLineNumber? MessageLineNumber => ...` — (inheritdoc)
- L66 _public property_ `public string MessageFilePath => ...` — (inheritdoc)
- L69 _public property_ `public string MessageFullFilePath => ...` — (inheritdoc)
- L72 _public property_ `public bool MessageIsFragment => ...` — (inheritdoc)
- L75 _public property_ `public string MessageFragmentFilePath => ...` — (inheritdoc)
- L78 _public property_ `public string MessageFragmentFullFilePath => ...` — (inheritdoc)
- L81 _public property_ `public int MessageFragmentLineNumber => ...` — (inheritdoc)
- L89-95 _public ctor_ `public UhtSourceFile(UhtSession session, string filePath)` — Construct a new instance of a source file
- L100-103 _public method_ `public virtual void Read()` — Read the contents of the source file
- L109-112 _public method_ `public void SetSource(StringView source)` — Sets the source fragment from the given string

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtStruct.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Types.UhtStruct`  
`public abstract class UhtStruct : UhtField`  
_public; L23-559_
- attrs: `[UhtEngineClass(Name = "Struct")]`
- inherits: `UhtField`
- desc: Base class for all types that contain properties and functions. Also support the ability to specifier super class and base classes
- L30 _public property_ `public EGeneratedCodeVersion GeneratedCodeVersion { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Generated code version of the type. Set via specifiers
- L41-53 _public property_ `public IEnumerable<UhtProperty> Properties { get; }` — attrs: `[JsonIgnore]` — Return a collection of children that are properties NOTE: This method allocates memory to construct the enumerator. In code invoked a large number of times, the loop should be written directly into the code and not use this method. Also, the Linq version performs even worse.
- L64-76 _public property_ `public IEnumerable<UhtFunction> Functions { get; }` — attrs: `[JsonIgnore]` — Return a collection of children that are functions NOTE: This method allocates memory to construct the enumerator. In code invoked a large number of times, the loop should be written directly into the code and not use this method. Also, the Linq version performs even worse.
- L80 _public property_ `public virtual string EngineNamePrefix => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L83 _public property_ `public override string EngineClassName => ...` — (inheritdoc)
- L89 _public property_ `public UhtStruct? Super { get; set; }` — attrs: `[JsonConverter(typeof(UhtNullableTypeSourceNameJsonConverter<UhtStruct>))]` — Super type
- L95 _public property_ `public IReadOnlyList<UhtStruct> Bases => ...` — attrs: `[JsonConverter(typeof(UhtTypeReadOnlyListSourceNameJsonConverter<UhtStruct>))]` — Base types
- L101 _public property_ `public UhtToken[] SuperIdentifier { get; set; }` — attrs: `[JsonIgnore]` — Super identifier
- L108 _public property_ `public List<UhtToken[]>? BaseIdentifiers { get; set; }` — attrs: `[JsonIgnore] [SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "<Pending>")]` — Base identifiers
- L114 _public property_ `public UhtStruct? SuperStruct => ...` — attrs: `[JsonIgnore]` — Super struct type
- L120 _public property_ `public virtual UhtStruct? InheritanceSuperStruct => ...` — attrs: `[JsonIgnore]` — Super struct type for inheritance, i.e. functions do not inherit properties from their Super
- L125 _public property_ `public UhtDefineScopeLink<UhtProperty>? FirstProperty { get; set; }` — After properties are fully resolved, points to the first property in this struct
- L130 _public property_ `public UhtScriptStruct? SparseClassDataStruct { get; set; }` — For classes, struct type for sparse class data shared between all instances
- L135 _private field_ `private static readonly ThreadLocal<List<UhtType>> s_scanForInstanceReferencedStack = new(() => { return []; })` — Stack used to test to see if we are recursing in a ScanForInstanceReferenced call
- L147-149 _protected ctor_ `protected UhtStruct(UhtHeaderFile headerFile, UhtNamespace namespaceObj, UhtType outer, int lineNumber) : base(headerFile, namespaceObj, outer, lineNumber)` — Construct a new instance
- L156-161 _protected ctor_ `protected UhtStruct(UhtInputCacheReader reader, UhtType outer) : base(reader, outer)` — Construct a type from the cache
- L167-173 _public method_ `public override void Write(UhtInputCacheWriter writer)` — Write the output type
- L180-194 _public method_ `public bool IsChildOf(UhtStruct? baseStruct)` — Test to see if the given struct is derived from the base structure
- L196 _private field_ `private static readonly List<UhtStruct> s_emptyBases = []`
- L197 _private field_ `private List<UhtStruct>? _bases = null`
- L201-211 _protected method_ `protected override void ResolveSuper(UhtResolvePhase resolvePhase)` — (inheritdoc)
- L214-235 _protected method_ `protected override void ResolveChildren(UhtResolvePhase phase)` — (inheritdoc)
- L243-260 _public method_ `public bool ScanForInstancedReferenced(bool deepScan)` — Check properties to see if any instances are referenced. This method does NOT cache the result.
- L268-285 _protected method_ `protected virtual bool ScanForInstancedReferencedInternal(bool deepScan)` — Check properties to see if any instances are referenced. This method does NOT cache the result.
- L295-308 _public method_ `public void BindSuper(UhtToken[] superIdentifier, UhtFindOptions findOptions)` — Resolve super identifier
- L316-332 _public method_ `public void BindBases(List<UhtToken[]>? baseIdentifiers, UhtFindOptions findOptions)` — Resolve bases. Unlike super, this routine will not generate an error if the type can not be found. Having unrecognized types is expected.
- L337-342 _protected method_ `protected override UhtValidationOptions Validate(UhtValidationOptions options)` — (inheritdoc)
- L344-373 _private method_ `private static bool CheckUIMinMaxRangeFromMetaData(UhtType child)`
- L376-464 _protected method_ `protected override void ValidateDocumentationPolicy(UhtDocumentationPolicy policy)` — (inheritdoc)
- L466-550 _private method_ `private void ValidateSparseClassData()`
- L554-558 _public method_ `public override void CollectReferences(IUhtReferenceCollector collector)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Types/UhtType.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Types.UhtEngineType`  
`public enum UhtEngineType`  
_public; L22-74_
- desc: Enumeration for all the different engine types
- L28 _public* enumerator_ `Package` — Type is a package (UhtPackage)
- L33 _public* enumerator_ `Class` — Type is a class (UhtClass)
- L38 _public* enumerator_ `Interface` — Type is an interface (UhtClass)
- L43 _public* enumerator_ `NativeInterface` — Type is a native interface (UhtClass)
- L48 _public* enumerator_ `ScriptStruct` — Type is a script struct (UhtScriptStruct)
- L53 _public* enumerator_ `Enum` — Type is an enumeration (UhtEnum)
- L58 _public* enumerator_ `Function` — Type is a function (UhtFunction)
- L63 _public* enumerator_ `Delegate` — Type is a delegate (UhtFunction)
- L68 _public* enumerator_ `SparseDelegate` — Type is a sparse delegate (UhtFunction)
- L73 _public* enumerator_ `Property` — Type is a property (UhtProperty)

#### class `EpicGames.UHT.Types.UhtEngineTypeExtensions`  
`public static class UhtEngineTypeExtensions`  
_public; L79-298_
- desc: Collection of extension methods used to query information about the type
- L88-105 _public method_ `public static string ShortLowercaseText(this UhtEngineType engineType)` — Get the name of the type where shared distinctions aren't made between different class and function types.
- L113-130 _public method_ `public static string ShortCapitalizedText(this UhtEngineType engineType)` — Get the name of the type where shared distinctions aren't made between different class and function types.
- L138-155 _public method_ `public static string LowercaseText(this UhtEngineType engineType)` — Get the name of the type
- L163-180 _public method_ `public static string CapitalizedText(this UhtEngineType engineType)` — Get the name of the type
- L187-201 _public method_ `public static bool MustBeUnique(this UhtEngineType engineType)` — Return true if the type must be unique in the symbol table
- L208-224 _public method_ `public static UhtFindOptions MustBeUniqueFindOptions(this UhtEngineType engineType)` — Find options to be used when attempting to find a duplicate name
- L231-245 _public method_ `public static bool MustNotBeReserved(this UhtEngineType engineType)` — Return true if the type must not be a reserved name.
- L252-255 _public method_ `public static bool HasEngineName(this UhtEngineType engineType)` — Return true if the type should be added to the engine symbol table
- L262-272 _public method_ `public static bool AddChildrenToSymbolTable(this UhtEngineType engineType)` — Return true if the children of the type should be added to the symbol table
- L280-297 _public method_ `public static UhtFindOptions FindOptions(this UhtEngineType engineType)` — Convert the engine type to find options

#### enum `EpicGames.UHT.Types.UhtFindOptions`  
`public enum UhtFindOptions`  
_public; L304-410_
- attrs: `[Flags]`
- desc: Options to customize how symbols are found
- L309 _public* enumerator_ `None = 0` — No find options
- L314 _public* enumerator_ `EngineName = 1 << 0` — Search using the engine name. This is the default if neither engine/source is specified.
- L319 _public* enumerator_ `SourceName = 1 << 1` — Search using the source name. This can not be set if EngineName is also set.
- L324 _public* enumerator_ `Enum = 1 << 8` — Search for UhtEnum types
- L329 _public* enumerator_ `ScriptStruct = 1 << 9` — Search for UhtScriptStruct types
- L334 _public* enumerator_ `Class = 1 << 10` — Search for UhtClass types
- L339 _public* enumerator_ `DelegateFunction = 1 << 11` — Search for UhtFunction types that are delegate functions
- L344 _public* enumerator_ `Function = 1 << 12` — Search for UhtFunction types that are not delegate functions
- L349 _public* enumerator_ `Property = 1 << 13` — Search for UhtProperty types
- L354 _public* enumerator_ `PropertyOrFunction = Property | Function | DelegateFunction` — Search for any properties or functions
- L359 _public* enumerator_ `NoParents = 1 << 16` — Do not search the super chain
- L364 _public* enumerator_ `NoOuter = 1 << 17` — Do not search the outer chain
- L369 _public* enumerator_ `NoIncludes = 1 << 18` — Do not search include files
- L374 _public* enumerator_ `NoGlobal = 1 << 19` — Do not do a last resort global namespace search
- L379 _public* enumerator_ `NoSelf = 1 << 20` — Do not search the children of the starting point
- L384 _public* enumerator_ `ParentsOnly = NoOuter | NoIncludes | NoGlobal | NoSelf` — Only search the parent chain
- L389 _public* enumerator_ `SelfOnly = NoParents | NoOuter | NoIncludes | NoGlobal` — Search only the children of the starting type
- L394 _public* enumerator_ `CaseCompare = 1 << 21` — Case compare (usually for SourceName searches)
- L399 _public* enumerator_ `CaselessCompare = 1 << 22` — Caseless compare (usually for EngineName searches)
- L404 _public* enumerator_ `NamesMask = EngineName | SourceName` — Mask of name flags
- L409 _public* enumerator_ `TypesMask = Enum | ScriptStruct | Class | DelegateFunction | Function | Property` — Mask of type flags

#### class `EpicGames.UHT.Types.UhtFindOptionsExtensions`  
`public static class UhtFindOptionsExtensions`  
_public; L416-452_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L425-428 _public method_ `public static bool HasAnyFlags(this UhtFindOptions inFlags, UhtFindOptions testFlags)` — Test to see if any of the specified flags are set
- L436-439 _public method_ `public static bool HasAllFlags(this UhtFindOptions inFlags, UhtFindOptions testFlags)` — Test to see if all of the specified flags are set
- L448-451 _public method_ `public static bool HasExactFlags(this UhtFindOptions inFlags, UhtFindOptions testFlags, UhtFindOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtValidationOptions`  
`public enum UhtValidationOptions`  
_public; L458-491_
- attrs: `[Flags]`
- desc: Options during validation checks
- L464 _public* enumerator_ `None` — No validation options
- L470 _public* enumerator_ `Deprecated = 1 << 0` — Test to see if any referenced types have been deprecated. This should not be set when the parent object or property has already been marked as deprecated.
- L475 _public* enumerator_ `Shadowing = 1 << 1` — Test to see if the name of the property conflicts with another property in the super chain
- L480 _public* enumerator_ `IsKey = 1 << 2` — The property is part of a key in a TMap
- L485 _public* enumerator_ `IsValue = 1 << 3` — The property is part of a value in a TArray, TSet, or TMap
- L490 _public* enumerator_ `IsKeyOrValue = IsKey | IsValue` — The property is either a key or a value part of a TArray, TSet, or TMap

#### class `EpicGames.UHT.Types.UhtValidationOptionsExtensions`  
`public static class UhtValidationOptionsExtensions`  
_public; L497-533_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L506-509 _public method_ `public static bool HasAnyFlags(this UhtValidationOptions inFlags, UhtValidationOptions testFlags)` — Test to see if any of the specified flags are set
- L517-520 _public method_ `public static bool HasAllFlags(this UhtValidationOptions inFlags, UhtValidationOptions testFlags)` — Test to see if all of the specified flags are set
- L529-532 _public method_ `public static bool HasExactFlags(this UhtValidationOptions inFlags, UhtValidationOptions testFlags, UhtValidationOptions matchFlags)` — Test to see if a specific set of flags have a specific value.

#### enum `EpicGames.UHT.Types.UhtDefineScope`  
`public enum UhtDefineScope`  
_public; L541-583_
- attrs: `[Flags] [SuppressMessage("Usage", "CA2217:Do not mark enums with FlagsAttribute")]`
- desc: #define scope where the type was defined. This only includes macros such as WITH_EDITOR, WITH_EDITORONLY_DATA, and WITH_VERSE_VM. Not all types support the given options.
- L547 _public* enumerator_ `Invalid = -1` — The scope is invalid. Used during code generation.
- L552 _public* enumerator_ `None = 0` — Exists outside of a define scope
- L557 _public* enumerator_ `EditorOnlyData = 1 << 0` — Exists inside of a WITH_EDITORONLY_DATA block
- L562 _public* enumerator_ `VerseVM = 1 << 1` — Exists inside of a WITH_VERSE_VM block
- L567 _public* enumerator_ `Tests = 1 << 2` — Exists inside of a WITH_TESTS block
- L572 _public* enumerator_ `VerseBPVM = 1 << 3` — Exists inside of a WITH_VERSE_BPVM block
- L577 _public* enumerator_ `Editor = 1 << 4` — Exists inside of a WITH_EDITOR block
- L582 _public* enumerator_ `ScopeCount = 1 << 5` — Number of unique scope combinations

#### class `EpicGames.UHT.Types.UhtDefineScopeExtensions`  
`public static class UhtDefineScopeExtensions`  
_public; L589-649_
- desc: Helper methods for testing flags. These methods perform better than the generic HasFlag which hits the GC and stalls.
- L598-601 _public method_ `public static bool HasAnyFlags(this UhtDefineScope inFlags, UhtDefineScope testFlags)` — Test to see if any of the specified flags are set
- L609-612 _public method_ `public static bool HasAllFlags(this UhtDefineScope inFlags, UhtDefineScope testFlags)` — Test to see if all of the specified flags are set
- L621-624 _public method_ `public static bool HasExactFlags(this UhtDefineScope inFlags, UhtDefineScope testFlags, UhtDefineScope matchFlags)` — Test to see if a specific set of flags have a specific value.
- L631-648 _public method_ `public static UhtCompilerDirective GetCompilerDirective(this UhtDefineScope defineScope)` — Return the compiler directive the matches the given scope

#### enum `EpicGames.UHT.Types.UhtAccessSpecifier`  
`public enum UhtAccessSpecifier`  
_public; L654-676_
- desc: Access specifier for type
- L660 _public* enumerator_ `None` — No access specifier seen
- L665 _public* enumerator_ `Public` — Public type
- L670 _public* enumerator_ `Private` — Private type
- L675 _public* enumerator_ `Protected` — Protected type

#### enum `EpicGames.UHT.Types.UhtResolvePhase`  
`public enum UhtResolvePhase : int`  
_public; L681-708_
- inherits: `int`
- desc: Requested resolve phase
- L686 _public* enumerator_ `None` — Initial resolve phase
- L692 _public* enumerator_ `InvalidCheck = 1` — Check for any type that is invalid. Invalid items will be removed from the children. Used to detect things that looked like native interfaces but no interface was found
- L697 _public* enumerator_ `Bases` — Resolve any super references
- L702 _public* enumerator_ `Properties` — Resolve property types that reference other types
- L707 _public* enumerator_ `Final` — Final resolve phase for anything that needs fully resolved properties.

#### class `EpicGames.UHT.Types.UhtResolvePhaseExtensions`  
`public static class UhtResolvePhaseExtensions`  
_public; L713-731_
- desc: Extension methods of UhtResolvePhase
- L721-730 _public method_ `public static bool IsMultiThreadedResolvePhase(this UhtResolvePhase resolvePhase)` — Returns true if the phase should execute multi-threaded.

#### class `EpicGames.UHT.Types.UhtDocumentationPolicy`  
`public class UhtDocumentationPolicy`  
_public; L736-775_
- desc: Flags for required documentation
- L741 _public property_ `public bool ClassOrStructCommentRequired { get; set; }` — A tool tip must be defined
- L746 _public property_ `public bool FunctionToolTipsRequired { get; set; }` — Functions must have a tool tip
- L751 _public property_ `public bool MemberToolTipsRequired { get; set; }` — Property members must have a tool tip
- L756 _public property_ `public bool ParameterToolTipsRequired { get; set; }` — Function parameters must have a tool tip
- L761 _public property_ `public bool FloatRangesRequired { get; set; }` — Float properties must have a range specified
- L767-774 _public method_ `public void Write(IMemoryWriter writer)` — Write the structure contents

#### class `EpicGames.UHT.Types.UhtType`  
`public abstract class UhtType : IUhtMessageSite, IUhtMessageLineNumber`  
_public; L782-1502_
- attrs: `[DebuggerDisplay("SourceName = {SourceName}")]`
- inherits: `IUhtMessageSite, IUhtMessageLineNumber`
- desc: Base type for all UHT types. These mostly map to UnrealEngine types.
- L787 _private field_ `private static readonly List<UhtType> s_emptyTypeList = []` — Empty list of type used when children are requested but no children have been added.
- L793 _public property_ `public UhtSession Session => ...` — attrs: `[JsonIgnore]` — All UHT runs are associated with a given session. The session holds all the global information for a run.
- L799 _public property_ `public UhtModule Module { get; }` — attrs: `[JsonIgnore]` — UHT module of the package (1 to 1 relationship)
- L805 _public property_ `public UhtHeaderFile HeaderFile => ...` — attrs: `[JsonIgnore]` — The header file containing the type
- L811 _public property_ `public int TypeIndex { get; }` — attrs: `[JsonIgnore]` — Every type in a session is assigned a unique, non-zero id.
- L817 _public property_ `public UhtType? Outer { get; set; }` — attrs: `[JsonIgnore]` — The outer object containing this type. For example, the header file would be the outer for a class defined in the global scope.
- L823-834 _public property_ `public virtual UhtPackage Package { get; }` — attrs: `[JsonIgnore]` — The owning package of the type
- L839 _public property_ `public string SourceName { get; set; }` — The name of the type as it appears in the source file
- L844 _public property_ `public string EngineName { get; set; }` — The name of the type as used by the engines type system. If not set, will default to the source name
- L850 _public property_ `public abstract UhtEngineType EngineType { get; }` — attrs: `[JsonIgnore]` — Simple enumeration that can be used to detect the different types of objects
- L855 _public property_ `public abstract string EngineClassName { get; }` — The name of the engine's class for this type i.e. Class, Function
- L861 _public property_ `public virtual string EngineLinkClassName => ...` — The name of the engine's class for this type for linking with registration functions. i.e. EngineClassName may be VerseStruct, but EngineLinkClassName may be ScriptStruct
- L867 _public property_ `public abstract UhtClass? EngineClass { get; }` — Return the runtime type of this object in the engine after parsing, when the Session has references to such types available.
- L873 _public property_ `public virtual bool Deprecated => ...` — attrs: `[JsonIgnore]` — Return true if the type has been deprecated
- L878 _public property_ `public int LineNumber { get; set; }` — The line number of where the definition began
- L884 _public property_ `public UhtDefineScope DefineScope { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — #define scope where the type was defined. None means defined regardless of preprocessor definitions.
- L890 _public property_ `public bool IsValid { get; set; }` — attrs: `[JsonIgnore]` — If true, the type has not been marked as invalid.
- L896-904 _public property_ `public virtual string FullName { get; }` — attrs: `[JsonIgnore]` — Return a combination of the engine type name followed by the path name of the type
- L910-918 _public property_ `public string PathName { get; }` — attrs: `[JsonIgnore]` — Return the path name of the type which includes all parent outer objects excluding the header file
- L924 _public property_ `public string DocumentationPolicyName => ...` — attrs: `[JsonIgnore]` — Return the name of the documentation policy to be used
- L930 _protected property_ `protected virtual UhtSpecifierValidatorTable? SpecifierValidatorTable => ...` — attrs: `[JsonIgnore]` — Return the specifier validation table to be used to validate the meta data on this type
- L936 _public property_ `public UhtMetaData MetaData { get; set; }` — attrs: `[JsonConverter(typeof(UhtMetaDataConverter))]` — Meta data associated with the type
- L943 _public property_ `public List<UhtType> Children => ...` — attrs: `[JsonConverter(typeof(UhtNullableTypeListJsonConverter<UhtType>))]` — Children types of this type
- L949 _public method_ `public override string ToString()` — Helper to string method
- L951 _private field_ `private string? _engineName = null`
- L952 _private field_ `private List<UhtType>? _children = null`
- L953 _private field_ `private readonly UhtHeaderFile? _headerFile = null`
- L954 _private field_ `private int _resolveState = (int)UhtResolvePhase.None * 2`
- L959 _public property_ `public virtual IUhtMessageSession MessageSession => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L963 _public property_ `public virtual IUhtMessageSource? MessageSource => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L967 _public property_ `public IUhtMessageLineNumber? MessageLineNumber => ...` — attrs: `[JsonIgnore]` — (inheritdoc)
- L971 _private* property_ `int IUhtMessageLineNumber.MessageLineNumber => ...`
- L979-987 _protected ctor_ `protected UhtType(UhtModule module)` — Construct the base type information. This constructor is used exclusively by UhtPackage which is at the root of all type hierarchies.
- L996-1007 _protected ctor_ `protected UhtType(UhtHeaderFile headerFile, UhtType outer, int lineNumber, UhtMetaData? metaData = null)` — Construct instance of the type given a parent type.
- L1014-1031 _protected ctor_ `protected UhtType(UhtInputCacheReader reader, UhtType outer)` — Construct a type from the cache
- L1037-1045 _public method_ `public virtual void Write(UhtInputCacheWriter writer)` — Write the type to the archive writer
- L1051-1054 _public method_ `public virtual void AddChild(UhtType child)` — Add a type as a child
- L1060-1064 _public method_ `public void AddChildDirectly(UhtType child)` — Non-virtual method that always adds the child directly to the child list
- L1070-1086 _public method_ `public void MoveChildren(UhtType source)` — Move all children from the given source type to this type
- L1095-1140 _public method_ `public bool Resolve(UhtResolvePhase phase)` — Resolve the type. To customize behavior, override ResolveSuper, ResolveSelf, or ResolveChildren.
- L1146-1148 _protected method_ `protected virtual void ResolveSuper(UhtResolvePhase phase)` — Resolve any super types
- L1155-1158 _protected method_ `protected virtual bool ResolveSelf(UhtResolvePhase phase)` — Resolve self
- L1164-1170 _protected method_ `protected virtual void ResolveChildren(UhtResolvePhase phase)` — Resolve children
- L1177-1206 _public method_ `public static void ResolveChildren(List<UhtType> children, UhtResolvePhase phase)` — Helper method to resolve a list of types
- L1212-1230 _public method_ `public void RemoveInvalidChildren()` — Remove any invalid children that were previously marked bad. This is only executed on a UhtPackage
- L1235-1244 _public method_ `public virtual void BindSuperAndBases()` — Resolve all the super and base structures and classes
- L1256-1259 _public method_ `public UhtType? FindType(UhtFindOptions options, string name, IUhtMessageSite? messageSite = null, int lineNumber = -1)` — Find the given type in the type hierarchy
- L1268-1271 _public method_ `public UhtType? FindType(UhtFindOptions options, ref UhtToken name, IUhtMessageSite? messageSite = null)` — Find the given type in the type hierarchy
- L1281-1284 _public method_ `public UhtType? FindType(UhtFindOptions options, UhtTokenList identifiers, IUhtMessageSite? messageSite = null, int lineNumber = -1)` — Find the given type in the type hierarchy
- L1294-1297 _public method_ `public UhtType? FindType(UhtFindOptions options, UhtToken[] identifiers, IUhtMessageSite? messageSite = null, int lineNumber = -1)` — Find the given type in the type hierarchy
- L1306-1311 _protected method_ `protected virtual UhtValidationOptions Validate(UhtValidationOptions options)` — Validate the type settings
- L1313-1329 _private method_ `private void ValidateMetaData()`
- L1331-1363 _private method_ `private void ValidateDocumentationPolicy()`
- L1369-1371 _protected method_ `protected virtual void ValidateDocumentationPolicy(UhtDocumentationPolicy policy)` — Validate the documentation policy
- L1378-1388 _public method_ `public static void ValidateType(UhtType type, UhtValidationOptions options)` — Validate the given type. Validates itself and the children
- L1397-1404 _public method_ `public virtual void AppendPathName(StringBuilder builder, UhtType? stopOuter = null)` — Return the path name of the type which includes the outers
- L1406-1433 _private method_ `private void AppendPathNameInternal(StringBuilder builder, UhtType? stopOuter = null)`
- L1439-1444 _public method_ `public virtual void AppendFullName(StringBuilder builder)` — Get the full type name which is the engine class name followed by the path name
- L1450-1461 _public method_ `public string GetDisplayNameText()` — Finds the localized display name or native display name as a fallback.
- L1468-1492 _public method_ `public virtual string GetToolTipText(bool shortToolTip = false)` — Finds the localized tooltip or native tooltip as a fallback.
- L1499-1501 _public method_ `public virtual void CollectReferences(IUhtReferenceCollector collector)` — Collect all the references for the type

#### class `EpicGames.UHT.Types.UhtTypeStringBuilderExtensions`  
`public static class UhtTypeStringBuilderExtensions`  
_public; L1507-1551_
- desc: String builder extensions for UhtTypes
- L1515-1550 _public method_ `public static StringBuilder AppendOuterNames(this StringBuilder builder, UhtType? outer)` — Append all of the outer names associated with the type

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtBuffer.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtPoolBuffers`  
`public static class UhtPoolBuffers`  
_public; L13-38_
- desc: Rent and return pooled buffers
- L21-25 _public method_ `public static UhtPoolBuffer<T> Rent<T>(int size)` — Rent a new buffer
- L31-37 _public method_ `public static void Return<T>(UhtPoolBuffer<T> buffer)` — Return a buffer

#### struct `EpicGames.UHT.Utils.UhtPoolBuffer`  
`public struct UhtPoolBuffer<T>`  
_public; L44-89_
- desc: Pooled buffers
- L50 _private field_ `private readonly T[]? _block = null` — THe backing array
- L55 _public property_ `public Memory<T> Memory { get; set; }` — Memory region sized to the requested size
- L60 _public property_ `public readonly bool IsSet => ...` — Return true if we have a pool block
- L67-71 _public ctor_ `public UhtPoolBuffer(T[] block, int size)` — Create a pool buffer
- L76-79 _public method_ `public readonly T[] GetBlock()` — The backing array. The size of the array will normally be larger than the requested size.
- L85-88 _public method_ `public void Reset(int size)` — Reset the memory region to the given size

#### struct `EpicGames.UHT.Utils.UhtRentedPoolBuffer`  
`public struct UhtRentedPoolBuffer<T> : IDisposable`  
_public; L94-118_
- inherits: `IDisposable`
- desc: Helper class for using pattern to borrow and return a buffer.
- L100 _public property_ `public UhtPoolBuffer<T> Buffer { get; set; }` — The borrowed buffer
- L106-109 _public ctor_ `public UhtRentedPoolBuffer(int size)` — Borrow a buffer with the given size
- L114-117 _public method_ `public readonly void Dispose()` — Return the borrowed buffer to the cache

#### class `EpicGames.UHT.Utils.UhtPoolBufferStringBuilderExtensions`  
`public static class UhtPoolBufferStringBuilderExtensions`  
_public; L123-151_
- desc: Collection of helper methods to convert string builder to borrow buffers
- L130-136 _public method_ `public static UhtRentedPoolBuffer<char> RentPoolBuffer(this StringBuilder builder)` — Return a buffer initialized with the string builder.
- L145-150 _public method_ `public static UhtRentedPoolBuffer<char> RentPoolBuffer(this StringBuilder builder, int startIndex, int length)` — Return a buffer initialized with the string builder sub string.

#### class `EpicGames.UHT.Utils.UhtBuffer`  
`public class UhtBuffer`  
_public; L160-316_
- attrs: `[Obsolete("Use UhtPoolBuffer<T> instead of UhtBuffer")]`
- desc: Cached character buffer system. Invoke UhtBuffer.Borrow method to get a buffer of the given size. Invoke UhtBuffer.Return to return the buffer to the cache.
- L165 _private const_ `private const int MinSize = 1024 * 16` — Any requests of the given size or smaller will be placed in bucket zero with the given size.
- L170 _private field_ `private static readonly int s_buckedAdjustment = BitOperations.Log2((uint)MinSize)` — Adjustment to the bucket index to account for the minimum bucket size
- L175 _private field_ `private static readonly int s_bucketCount = 32 - s_buckedAdjustment` — Total number of supported buckets
- L180 _private field_ `private static readonly UhtBuffer?[] s_lookAsideArray = new UhtBuffer?[s_bucketCount]` — Bucket lookaside list
- L185 _private property_ `private int Bucket { get; }` — The bucket index associated with the buffer
- L190 _private property_ `private UhtBuffer? NextBuffer { get; set; }` — Single list link to the next cached buffer
- L198 _public field_ `public char[] Block` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1051:Do not declare visible instance fields", Justification = "<Pending>")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "<P` — The backing character block. The size of the array will normally be larger than the requested size.
- L203 _public property_ `public Memory<char> Memory { get; set; }` — Memory region sized to the requested size
- L211-216 _private ctor_ `private UhtBuffer(int size, int bucket, int bucketSize)` — Construct a new buffer
- L222-225 _public method_ `public void Reset(int size)` — Reset the memory region to the given size
- L232-253 _public method_ `public static UhtBuffer Borrow(int size)` — Borrow a new buffer of the given size
- L260-266 _public method_ `public static UhtBuffer Borrow(StringBuilder builder)` — Return a buffer initialized with the string builder.
- L275-280 _public method_ `public static UhtBuffer Borrow(StringBuilder builder, int startIndex, int length)` — Return a buffer initialized with the string builder sub string.
- L286-293 _public method_ `public static void Return(UhtBuffer buffer)` — Return the buffer to the cache. The buffer should no longer be accessed.
- L302-315 _private method_ `private static UhtBuffer BorrowInternal(int size, int bucket, int bucketSize)` — Internal helper to allocate a buffer

#### struct `EpicGames.UHT.Utils.UhtBorrowBuffer`  
`public struct UhtBorrowBuffer : IDisposable`  
_public; L322-366_
- attrs: `[Obsolete("Use UhtRentedPoolBuffer<T> instead of UhtBorrowBuffer")]`
- inherits: `IDisposable`
- desc: Helper class for using pattern to borrow and return a buffer.
- L328 _public property_ `public UhtBuffer Buffer { get; set; }` — The borrowed buffer
- L334-337 _public ctor_ `public UhtBorrowBuffer(int size)` — Borrow a buffer with the given size
- L343-346 _public ctor_ `public UhtBorrowBuffer(StringBuilder builder)` — Borrow a buffer populated with the builder contents
- L354-357 _public ctor_ `public UhtBorrowBuffer(StringBuilder builder, int startIndex, int length)` — Borrow a buffer populated with the builder contents
- L362-365 _public method_ `public readonly void Dispose()` — Return the borrowed buffer to the cache

#### class `EpicGames.UHT.Utils.UhtByteBuffer`  
`public class UhtByteBuffer`  
_public; L375-504_
- attrs: `[Obsolete("Use UhtPoolBuffer<T> instead of UhtByteBuffer")]`
- desc: Cached character buffer system. Invoke UhtBuffer.Borrow method to get a buffer of the given size. Invoke UhtBuffer.Return to return the buffer to the cache.
- L380 _private const_ `private const int MinSize = 1024 * 16` — Any requests of the given size or smaller will be placed in bucket zero with the given size.
- L385 _private field_ `private static readonly int s_buckedAdjustment = BitOperations.Log2((uint)MinSize)` — Adjustment to the bucket index to account for the minimum bucket size
- L390 _private field_ `private static readonly int s_bucketCount = 32 - s_buckedAdjustment` — Total number of supported buckets
- L395 _private field_ `private static readonly UhtByteBuffer?[] s_lookAsideArray = new UhtByteBuffer?[s_bucketCount]` — Bucket lookaside list
- L400 _private property_ `private int Bucket { get; }` — The bucket index associated with the buffer
- L405 _private property_ `private UhtByteBuffer? NextBuffer { get; set; }` — Single list link to the next cached buffer
- L413 _public field_ `public byte[] Block` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1051:Do not declare visible instance fields", Justification = "<Pending>")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "<P` — The backing character block. The size of the array will normally be larger than the requested size.
- L418 _public property_ `public Memory<byte> Memory { get; set; }` — Memory region sized to the requested size
- L426-431 _private ctor_ `private UhtByteBuffer(int size, int bucket, int bucketSize)` — Construct a new buffer
- L437-440 _public method_ `public void Reset(int size)` — Reset the memory region to the given size
- L447-468 _public method_ `public static UhtByteBuffer Borrow(int size)` — Borrow a new buffer of the given size
- L474-481 _public method_ `public static void Return(UhtByteBuffer buffer)` — Return the buffer to the cache. The buffer should no longer be accessed.
- L490-503 _private method_ `private static UhtByteBuffer BorrowInternal(int size, int bucket, int bucketSize)` — Internal helper to allocate a buffer

#### struct `EpicGames.UHT.Utils.UhtBorrowByteBuffer`  
`public struct UhtBorrowByteBuffer : IDisposable`  
_public; L510-534_
- attrs: `[Obsolete("Use UhtRentedPoolBuffer<T> instead of UhtBorrowByteBuffer")]`
- inherits: `IDisposable`
- desc: Helper class for using pattern to borrow and return a buffer.
- L516 _public property_ `public UhtByteBuffer Buffer { get; set; }` — The borrowed buffer
- L522-525 _public ctor_ `public UhtBorrowByteBuffer(int size)` — Borrow a buffer with the given size
- L530-533 _public method_ `public readonly void Dispose()` — Return the borrowed buffer to the cache

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtConfig.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Utils.UhtIssueBehavior`  
`public enum UhtIssueBehavior`  
_public; L14-30_
- desc: Describes whether issues will generate warnings or errors
- L19 _public* enumerator_ `Disallow` — An error will be generated.
- L24 _public* enumerator_ `AllowSilently` — Ignore the issue.
- L29 _public* enumerator_ `AllowAndLog` — Log a warning.

#### record `EpicGames.UHT.Utils.UhtIssueBehaviorSet`  
`public record UhtIssueBehaviorSet`  
_public; L35-98_
- desc: Collection of the behaviors for engine, engine plugin, and non engine projects
- L41 _public property_ `public UhtIssueBehavior Engine { get; init; }` — Behavior for engine projects that aren't engine plugins
- L46 _public property_ `public UhtIssueBehavior EnginePlugin { get; init; }` — Behavior for engine plugin projects
- L51 _public property_ `public UhtIssueBehavior NonEngine { get; init; }` — Behavior for non engine projects
- L59-64 _public ctor_ `public UhtIssueBehaviorSet(UhtIssueBehavior engine, UhtIssueBehavior enginePlugin, UhtIssueBehavior nonEngine)` — Construct a behavior set
- L71-76 _public ctor_ `public UhtIssueBehaviorSet(UhtIssueBehavior engine, UhtIssueBehavior nonEngine)` — Construct a behavior set where the engine plugin setting is the same as the engine setting
- L82-87 _public method_ `public void Write(IMemoryWriter writer)` — Write the structure contents
- L94-97 _public method_ `public UhtIssueBehavior GetBehavior(UhtModule module)` — Return the behavior based on the module type

#### interface `EpicGames.UHT.Utils.IUhtConfig`  
`public interface IUhtConfig`  
_public; L104-231_
- desc: Interface for accessing configuration data. Since UnrealBuildTool depends on EpicGames.UHT and all of the configuration support exists in UBT, configuration data must be accessed through an interface.
- L109 _public property_ `public EGeneratedCodeVersion DefaultGeneratedCodeVersion { get; }` — Default version of generated code. Defaults to oldest possible, unless specified otherwise in config.
- L114 _public property_ `public UhtIssueBehaviorSet NativePointerMemberBehavior { get; }` — Pointer warning for native pointers
- L119 _public property_ `public UhtIssueBehaviorSet ObjectPtrMemberBehavior { get; }` — Pointer warning for object pointers
- L124 _public property_ `public UhtIssueBehaviorSet MissingGeneratedHeaderIncludeBehavior { get; }` — Behavior for when generated headers aren't properly included.
- L129 _public property_ `public UhtIssueBehaviorSet EnumUnderlyingTypeNotSet { get; }` — Behavior for when enum underlying types aren't set for engine code.
- L134 _public property_ `public bool ShowDeprecations { get; }` — If true, deprecation warnings should be shown
- L139 _public property_ `public bool AreRigVMUObjectPropertiesEnabled { get; }` — If true, UObject properties are enabled in RigVM
- L144 _public property_ `public bool AreRigVMUInterfacePropertiesEnabled { get; }` — If true, UInterface properties are enabled in RigVM
- L149 _public property_ `public IReadOnlyDictionary<string, UhtDocumentationPolicy> DocumentationPolicies { get; }` — Collection of all known documentation policies
- L154 _public property_ `public string ValkyrieDevelopmentStatusKey { get; }` — Settings to use for the development status
- L159 _public property_ `public string ValkyrieDevelopmentStatusValueExperimental { get; }` — Settings to use for the development status
- L164 _public property_ `public string ValkyrieDeprecationStatusKey { get; }` — Settings to use for the deprecation status
- L169 _public property_ `public string ValkyrieDeprecationStatusValueDeprecated { get; }` — Settings to use for the deprecation status
- L174 _public property_ `public string DefaultDocumentationPolicy { get; }` — Default documentation policy to be used if none is specified
- L180 _public method_ `public void RedirectTypeIdentifier(ref UhtToken token)` — If the token references a remapped identifier, update the value in the token
- L188 _public method_ `public bool RedirectMetaDataKey(string key, out string newKey)` — Return the remapped key or the existing key
- L195 _public method_ `public bool IsValidUnits(StringView units)` — Test to see if the given units are valid.
- L202 _public method_ `public bool IsStructWithTPrefix(StringView name)` — Test to see if the structure name should be using a "T" prefix.
- L209 _public method_ `public int FindDelegateParameterCount(StringView delegateMacro)` — Test to see if the given macro has a parameter count as part of the name.
- L216 _public method_ `public StringView GetDelegateParameterCountString(int index)` — Get the parameter count string associated with the given index
- L223 _public method_ `public bool IsExporterEnabled(string name)` — Test to see if the exporter is enabled
- L230 _public method_ `public void Write(IMemoryWriter writer)` — Write the current configuration to the given writer. This is used to check and see if the configuration has changed forcing sources to be parsed.

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtCppIdentifier.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Utils.UhtCppIdentifier`  
`public readonly struct UhtCppIdentifier : ISpanFormattable`  
_public; L11-121_
- inherits: `ISpanFormattable`
- desc: C++ name that can be formatted
- L16 _public property_ `public string? Namespace { get; }` — Name of the namespace containing the definition with or without trailing "::"
- L21 _public property_ `public string? Prefix { get; }` — Optional prefix for the identifier
- L26 _public property_ `public string Name { get; }` — Name of the identifier
- L31 _public property_ `public string? Suffix { get; }` — Suffix for the identifier
- L37-40 _public ctor_ `public UhtCppIdentifier(string name)` — Construct a simple identifier
- L48-53 _public ctor_ `public UhtCppIdentifier(string? prefix, string name, string? suffix)` — Construct an identifier with an optional prefix and suffix
- L62-68 _public ctor_ `public UhtCppIdentifier(string? ns, string? prefix, string name, string? suffix)` — Construct an identifier with an optional prefix and suffix
- L75-81 _public ctor_ `public UhtCppIdentifier(string ns, UhtCppIdentifier id)` — Construct an identifier with an optional prefix and suffix
- L87-90 _public method_ `public UhtCppIdentifier MakeStatics()` — Return the "statics" version of the identifier
- L97-100 _public method_ `public UhtCppIdentifier AppendSuffix(string suffix)` — Append the given suffix to the existing identifier and return the resulting identifier
- L103 _public method_ `public string ToString(string? format, IFormatProvider? formatProvider)` — (inheritdoc)
- L106-120 _public method_ `public bool TryFormat(Span<char> destination, out int charsWritten, ReadOnlySpan<char> format, IFormatProvider? provider)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtException.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtException`  
`public class UhtException : Exception`  
_public; L12-68_
- inherits: `Exception`
- desc: Compiler exception that immediately stops the processing of the current header file.
- L17 _public property_ `public UhtMessage UhtMessage { get; set; }` — The generated message
- L22-24 _protected ctor_ `protected UhtException()` — Internal do nothing constructor
- L30-33 _public ctor_ `public UhtException(string message)` — Exception with a simple message. Context will be the current header file.
- L41-48 _public ctor_ `public UhtException(IUhtMessageSite messageSite, string message, object? extraContext = null)` — Exception with a simple message. Context from the given message site.
- L57-64 _public ctor_ `public UhtException(IUhtMessageSite messageSite, int lineNumber, string message, object? extraContext = null)` — Make an exception to be thrown
- L67 _public property_ `public override string Message => ...` — (inheritdoc)

#### class `EpicGames.UHT.Utils.UhtTokenException`  
`public class UhtTokenException : UhtException`  
_public; L73-109_
- inherits: `UhtException`
- desc: Exception where the current token isn't what was expected
- L84-90 _public ctor_ `public UhtTokenException(IUhtMessageSite messageSite, UhtToken got, object? expected, object? extraContext = null)` — Make a parsing error for when there is a mismatch between the expected token and what was parsed.
- L97-108 _private method_ `private static string FormatExtraContext(object? extraContext = null)` — Format any extra context supplied by the caller or the message site

#### class `EpicGames.UHT.Utils.UhtIceException`  
`public class UhtIceException : UhtException`  
_public; L114-124_
- inherits: `UhtException`
- desc: Internal compiler error exception
- L120-123 _public ctor_ `public UhtIceException(string message)` — Exception with a simple message. Context will be the current header file.

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtExport.cs` (EpicGames.UHT)


#### interface `EpicGames.UHT.Utils.IUhtExportFactory`  
`public interface IUhtExportFactory`  
_public; L21-109_
- desc: Factory object used to generate export tasks
- L27 _public property_ `public UhtSession Session { get; }` — Session being run
- L32 _public property_ `public UHTManifest.Module? PluginModule { get; }` — If this exporter is from a plugin, this points to the module of the plugin
- L40 _public method_ `public Task CreateTask(List<Task?>? prereqs, UhtExportTaskDelegate action)` — Create a task
- L47 _public method_ `public Task CreateTask(UhtExportTaskDelegate action)` — Create a task
- L56 _public method_ `public void CommitOutput(string filePath, StringBuilder builder)` — Commit the contents of the string builder as the output. If you have a string builder, use this method so that a temporary buffer can be used.
- L63 _public method_ `public void CommitOutput(string filePath, StringView output)` — Commit the value of the string as the output
- L71 _public method_ `public string MakePath(UhtHeaderFile headerFile, string suffix)` — Make a path for an output based on the header file name.
- L79 _public method_ `public string MakePath(UhtModule moduleObj, string suffix)` — Make a path for an output based on the module name.
- L87 _public method_ `public string MakePath(string fileName, string extension)` — Make a path for the given file name and extension. This is only valid for plugins.
- L93 _public method_ `public void AddExternalDependency(string filePath)` — Add an external dependency to the given file path
- L101 _public method_ `public string GetModuleShortestIncludePath(UhtModule moduleObj, string filePath)` — Return the shortest relative include path
- L108 _public method_ `public string GetPluginShortestIncludePath(string filePath)` — Return the shortest relative include path

#### Namespace-level symbols

- L16 _public delegate_ `public delegate void UhtExportTaskDelegate(IUhtExportFactory factory)` — Delegate invoked by a factory

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtFCString.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtFCString`  
`public static class UhtFCString`  
_public; L13-374_
- desc: Collection of helper methods to emulate UHT string functions
- L19 _public field_ `public static readonly char SubObjectDelimiter = ':'` — Delimiter between the subobjects
- L26-51 _public method_ `public static bool ToBool(StringView value)` — Test to see if the string is a boolean
- L58-80 _public method_ `public static bool ToBool(string? value)` — Test to see if the string is a boolean
- L87-90 _public method_ `public static bool IsDigit(char c)` — Test to see if the character is a digit
- L97-100 _public method_ `public static bool IsAlpha(char c)` — Test to see if the character is an alphabet character
- L107-110 _public method_ `public static bool IsAlnum(char c)` — Test to see if the character is a digit or alphabet character
- L117-120 _public method_ `public static bool IsHexAlphaDigit(char c)` — Test to see if the character is a hex digit (A-F)
- L127-130 _public method_ `public static bool IsHexDigit(char c)` — Test to see if the character is a hex digit (0-9a-f)
- L137-140 _public method_ `public static bool IsWhitespace(char c)` — Test to see if the character is whitespace
- L147-150 _public method_ `public static bool IsSign(char c)` — Test to see if the character is a sign
- L157-160 _public method_ `public static bool IsHexMarker(char c)` — Test to see if the character is a hex marker (xX)
- L167-170 _public method_ `public static bool IsFloatMarker(char c)` — Test to see if the character is a float marker (fF)
- L177-180 _public method_ `public static bool IsExponentMarker(char c)` — Test to see if the character is an exponent marker (eE)
- L187-190 _public method_ `public static bool IsUnsignedMarker(char c)` — Test to see if the character is an unsigned marker (uU)
- L197-200 _public method_ `public static bool IsLongMarker(char c)` — Test to see if the character is a long marker (lL)
- L207-234 _public method_ `public static bool IsNumeric(ReadOnlySpan<char> span)` — Test to see if the span is a numeric value
- L241-244 _public method_ `public static bool IsLinebreak(char c)` — Test to see if the character is a linebreak character
- L251-303 _public method_ `public static string UnescapeText(string text)` — Return an unescaped string
- L312-324 _public method_ `public static ReadOnlyMemory<char> TabsToSpaces(ReadOnlyMemory<char> input, int tabSpacing, bool emulateCrBug)` — Replace tabs to spaces in a string containing only a single line.
- L334-373 _public method_ `public static void TabsToSpaces(ReadOnlySpan<char> span, int tabSpacing, bool emulateCrBug, int tabIndex, StringBuilder builder)` — Replace tabs to spaces in a string containing zero or more lines.

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtFileManager.cs` (EpicGames.UHT)


#### interface `EpicGames.UHT.Utils.IUhtFileManager`  
`public interface IUhtFileManager`  
_public; L14-54_
- desc: Interface used to read/write files
- L21 _public method_ `public string GetFullFilePath(string filePath)` — Return the full file path for a partial path
- L29 _public method_ `public bool ReadSource(string filePath, out UhtSourceFragment fragment)` — Read the given source file
- L37 _public method_ `public bool ReadOutput(string filePath, out UhtPoolBuffer<char> output)` — Read the given source file
- L45 _public method_ `public bool WriteOutput(string filePath, ReadOnlySpan<char> contents)` — Write the given contents to the file
- L53 _public method_ `public bool RenameOutput(string oldFilePath, string newFilePath)` — Rename the given file

#### class `EpicGames.UHT.Utils.UhtStdFileManager`  
`public class UhtStdFileManager : IUhtFileManager`  
_public; L59-191_
- inherits: `IUhtFileManager`
- desc: Implementation of a file manager that reads/writes from disk
- L64-66 _public ctor_ `public UhtStdFileManager()` — Construct a new file manager
- L69-72 _public method_ `public string GetFullFilePath(string filePath)` — (inheritdoc)
- L75-84 _public method_ `public bool ReadSource(string filePath, out UhtSourceFragment fragment)` — (inheritdoc)
- L87-117 _public method_ `public bool ReadOutput(string filePath, out UhtPoolBuffer<char> output)` — (inheritdoc)
- L120-137 _public method_ `public bool WriteOutput(string filePath, ReadOnlySpan<char> contents)` — (inheritdoc)
- L140-151 _public method_ `public bool RenameOutput(string oldFilePath, string newFilePath)` — (inheritdoc)
- L159-190 _private method_ `private static bool ReadFile(string filePath, out StringView contents)` — Read the given source file

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtInputCache.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Utils.UhtInputCacheMarker`  
`enum UhtInputCacheMarker : int`  
_internal*; L17-21_
- inherits: `int`
- L19 _public* enumerator_ `EndOfType = 0x12340000`
- L20 _public* enumerator_ `EndOfTypeBase = 0x12340001`

#### struct `EpicGames.UHT.Utils.UhtInputFile`  
`struct UhtInputFile`  
_internal*; L26-78_
- desc: Tracks an input file
- L31 _public property_ `public string FileName { get; set; }` — Name of the file
- L36 _public property_ `public long LastWriteTimeUtc { get; set; }` — File write time
- L41 _public property_ `public int UncompressedSize { get; set; }` — Size of the uncompressed data
- L46 _public property_ `public long CacheStart { get; set; }` — Starting position in the cache file for this file
- L51 _public property_ `public long CacheEnd { get; set; }` — Ending position in the cache file for this file
- L57-64 _public ctor_ `public UhtInputFile(IMemoryReader reader)` — Construct an instance from a reader
- L70-77 _public method_ `public void Write(IMemoryWriter writer)` — Write the input file information

#### class `EpicGames.UHT.Utils.UhtInputCacheReader`  
`public sealed class UhtInputCacheReader : IDisposable`  
_public; L83-546_
- inherits: `IDisposable`
- desc: Populate the types from a cache entry
- L88 _public property_ `public UhtHeaderFile Header { get; init; }` — Header file being written
- L89 _private field_ `private readonly MemoryReader _reader`
- L90 _private field_ `private readonly List<UhtPackage> _packages = []`
- L91 _private field_ `private readonly List<ConstructorInfo> _types = []`
- L92 _private field_ `private readonly List<UhtNamespace> _namespaces = []`
- L93 _private field_ `private readonly List<UhtType> _objects = []`
- L94 _private field_ `private readonly byte[] _uncompressed`
- L101-115 _public ctor_ `public UhtInputCacheReader(UhtHeaderFile header, UhtInputCacheEntry entry)` — Construct a reader from a byte buffer
- L121-124 _public method_ `public bool ReadBoolean()` — Read a boolean
- L130-133 _public method_ `public sbyte ReadInt8()` — Reads a single byte from the stream
- L139-142 _public method_ `public short ReadInt16()` — Read an short
- L148-151 _public method_ `public int ReadInt32()` — Read an integer
- L157-160 _public method_ `public long ReadInt64()` — Read an long
- L166-169 _public method_ `public byte ReadUInt8()` — Reads a single byte from the stream
- L175-178 _public method_ `public ushort ReadUInt16()` — Reads a single unsigned short from the stream
- L184-187 _public method_ `public uint ReadUInt32()` — Reads a single unsigned int from the stream
- L193-196 _public method_ `public ulong ReadUInt64()` — Read an unsigned long
- L202-205 _public method_ `public string ReadString()` — Read a string
- L211-214 _public method_ `public string? ReadOptionalString()` — Read a string
- L220-223 _public method_ `public ReadOnlyMemory<byte>? ReadVariableLengthBytes()` — Reads a byte array from the stream
- L230-243 _public method_ `public T[] ReadFixedLengthArray<T>(int length, Func<UhtInputCacheReader, T> readItem)` — Writes a fixed length array
- L250-254 _public method_ `public T[] ReadVariableLengthArray<T>(Func<UhtInputCacheReader, T> readItem)` — Reads an array of items
- L261-269 _public method_ `public T[]? ReadOptionalVariableLengthArray<T>(Func<UhtInputCacheReader, T> readItem)` — Reads an array of items
- L278-288 _public method_ `public List<T> ReadList<T>(int length, Func<UhtInputCacheReader, T> readItem)` — Reads a list of items
- L296-300 _public method_ `public List<T> ReadList<T>(Func<UhtInputCacheReader, T> readItem)` — Reads a list of items
- L308-316 _public method_ `public List<T>? ReadOptionalList<T>(Func<UhtInputCacheReader, T> readItem)` — Reads a list of items
- L324-327 _public method_ `public T? ReadOptionalObject<T>(Func<UhtInputCacheReader, T> read) where T : class` — Reads an object, which may be null, from the archive. Does not handle de-duplicating object references.
- L333-336 _public method_ `public UhtToken[] ReadTokenArray()` — Read a token array
- L342-345 _public method_ `public UhtToken[]? ReadOptionalTokenArray()` — Read a token array
- L351-354 _public method_ `public List<UhtToken> ReadTokenList()` — Read a token list
- L360-363 _public method_ `public List<UhtToken>? ReadOptionalTokenList()` — Read a token list
- L369-376 _private method_ `private void CheckMarker(UhtInputCacheMarker marker)` — Verify that the marker is set as expected
- L381-391 _public method_ `public void ReadHeader()` — Read the contents of the header
- L396-416 _public method_ `public UhtNamespace ReadNamespace()` — Read a namespace from the stream
- L421-442 _private method_ `private UhtPackage ReadPackage()` — Read a package from the stream
- L448-498 _public method_ `public UhtType? ReadType()` — Read a type from the stream
- L506-509 _public method_ `public void AddType(UhtType type)` — Invoked by UhtType::UhtType to add the type to the table of objects. This is required just in case a constructor needs to write other types that reference this type.
- L511-537 _private method_ `private ConstructorInfo ReadTypeConstructor()`
- L542-545 _public method_ `public void Dispose()` — Dispose of this object

#### class `EpicGames.UHT.Utils.UhtInputCacheWriter`  
`public sealed class UhtInputCacheWriter : IDisposable`  
_public; L551-1016_
- inherits: `IDisposable`
- desc: Wrapper class for writing to the input cache
- L556 _public property_ `public UhtHeaderFile Header { get; init; }` — Header file being written
- L557 _private field_ `private readonly ChunkedMemoryWriter _writer`
- L558 _private field_ `private readonly Dictionary<UhtPackage, int> _packages = ...`
- L558 _private field_ `private readonly Dictionary< _packages = []`
- L559 _private field_ `private readonly Dictionary<Type, int> _types = ...`
- L559 _private field_ `private readonly Dictionary< _types = []`
- L560 _private field_ `private readonly Dictionary<UhtNamespace, int> _namespaces = ...`
- L560 _private field_ `private readonly Dictionary< _namespaces = []`
- L561 _private field_ `private readonly Dictionary<UhtType, int> _objects = ...`
- L561 _private field_ `private readonly Dictionary< _objects = []`
- L567-571 _public ctor_ `public UhtInputCacheWriter(UhtHeaderFile header)` — Construct a writer from a stream
- L577-580 _public method_ `public void WriteBoolean(bool value)` — Writes a bool to the output
- L586-589 _public method_ `public void WriteInt8(sbyte value)` — Writes a single signed byte to the output
- L595-598 _public method_ `public void WriteInt16(short value)` — Writes a single short to the output
- L604-607 _public method_ `public void WriteInt32(int value)` — Writes a single int to the output
- L613-616 _public method_ `public void WriteInt64(long value)` — Writes a single long to the output
- L622-625 _public method_ `public void WriteUInt8(byte value)` — Writes a single byte to the output
- L631-634 _public method_ `public void WriteUInt16(ushort value)` — Writes a single unsigned short to the output
- L640-643 _public method_ `public void WriteUInt32(ushort value)` — Writes a single unsigned int to the output
- L649-652 _public method_ `public void WriteUInt64(ulong value)` — Writes a single unsigned long to the output
- L658-661 _public method_ `public void WriteString(string value)` — Writes a string to the output
- L667-678 _public method_ `public void WriteOptionalString(string? value)` — Writes a string to the output
- L684-695 _public method_ `public void WriteString(ReadOnlySpan<char> value)` — Writes a string to the output
- L701-704 _public method_ `public void WriteVariableLengthBytes(ReadOnlySpan<byte> data)` — Writes an array of bytes to the output
- L711-717 _public method_ `public void WriteFixedLengthArray<T>(IReadOnlyList<T> list, Action<UhtInputCacheWriter, T> writeItem)` — Writes a fixed length array
- L724-730 _public method_ `public void WriteFixedLengthArray<T>(ReadOnlySpan<T> list, Action<UhtInputCacheWriter, T> writeItem)` — Writes a fixed length array
- L738-742 _public method_ `public void WriteVariableLengthArray<T>(IReadOnlyList<T> list, Action<UhtInputCacheWriter, T> writeItem)` — Write an array of items to the archive
- L750-754 _public method_ `public void WriteVariableLengthArray<T>(ReadOnlySpan<T> list, Action<UhtInputCacheWriter, T> writeItem)` — Write an array of items to the archive
- L762-771 _public method_ `public void WriteOptionalVariableLengthArray<T>(IReadOnlyList<T>? list, Action<UhtInputCacheWriter, T> writeItem)` — Write an array of items to the archive
- L777-780 _public method_ `public void WriteVariableLengthTokenArray(ReadOnlySpan<UhtToken> tokens)` — Write a token array
- L786-794 _public method_ `public void WriteOptionalVariableLengthTokenArray(IReadOnlyList<UhtToken>? tokens)` — Write a token array
- L802-813 _public method_ `public void WriteOptionalObject<T>(T? obj, Action<UhtInputCacheWriter> writeObject) where T : class` — Writes an object to the output, checking whether it is null or not. Does not preserve object references; each object written is duplicated.
- L819-822 _private method_ `private void WriteMarker(UhtInputCacheMarker marker)` — Write the marker to the stream (debug only)
- L828-873 _public method_ `public UhtInputCacheEntry WriteHeader(DateTime lastWriteTimeUtc)` — Write the contents of the header
- L879-898 _private method_ `private void WritePackage(UhtPackage package)` — Write the given package to the stream
- L904-922 _public method_ `public void WriteNamespace(UhtNamespace namespaceObj)` — Write the given namespace to the stream
- L928-994 _public method_ `public void WriteType(UhtType? type)` — Write the given type
- L1000-1007 _public method_ `public void WriteChildren(IReadOnlyList<UhtType> children)` — Write the given list of children to the
- L1012-1015 _public method_ `public void Dispose()` — Dispose of the object

#### struct `EpicGames.UHT.Utils.UhtInputCacheEntry`  
`public readonly struct UhtInputCacheEntry`  
_public; L1021-1038_
- desc: Information about a input cache entry
- L1027 _public property_ `public DateTime LastWriteTimeUtc { get; init; }` — The last write time for the header file for this entry
- L1032 _public property_ `public int UncompressedSize { get; init; }` — Size of the uncompressed data
- L1037 _public property_ `public ReadOnlyMemory<byte> CompressedData { get; init; }` — Binary archive of the cache entry

#### class `EpicGames.UHT.Utils.UhtInputCache`  
`public class UhtInputCache`  
_public; L1043-1244_
- desc: Helper class to read/write parsed headers
- L1048 _public const_ `public const string CacheFilename = ".inputcache.data"` — The filename of UHT input cache files.
- L1050 _private const_ `private const int CacheVersion = 2`
- L1051 _private field_ `private readonly Dictionary<string, UhtInputFile> _files = ...`
- L1051 _private field_ `private readonly Dictionary< _files = []`
- L1052 _private field_ `private readonly ReadOnlyMemory<byte> _data`
- L1054-1057 _private ctor_ `private UhtInputCache()`
- L1059-1066 _private ctor_ `private UhtInputCache(List<UhtInputFile> cachedFiles, ReadOnlyMemory<byte> data)`
- L1074-1088 _public method_ `public bool TryGetFile(string fileName, out UhtInputCacheEntry entry)` — Try to get a cached entry from the cache
- L1096-1161 _public method_ `public static UhtInputCache Read(UhtModule module, ReadOnlySpan<byte> configData)` — Read the input cache file for the given module
- L1168-1219 _public method_ `public static void Write(UhtModule module, ReadOnlySpan<byte> configData)` — Write the input cache file for the given module
- L1221-1224 _private method_ `private static void DeleteCache(UhtModule module)`
- L1226-1238 _private method_ `private static void DeleteCacheFile(FileReference file)`
- L1240-1243 _private method_ `private static FileReference GetCacheFileReference(UhtModule module)`

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtJsonConverters.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtMetaDataConverter`  
`public class UhtMetaDataConverter : JsonConverter<UhtMetaData>`  
_public; L15-48_
- inherits: `JsonConverter<UhtMetaData>`
- desc: JSON converter to output the meta data
- L25-28 _public method_ `public override UhtMetaData Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Read the JSON value
- L36-47 _public method_ `public override void Write(Utf8JsonWriter writer, UhtMetaData type, JsonSerializerOptions options)` — Write the JSON value

#### class `EpicGames.UHT.Utils.UhtTypeSourceNameJsonConverter`  
`public class UhtTypeSourceNameJsonConverter<T> : JsonConverter<T> where T : UhtType`  
_public; L54-79_
- inherits: `JsonConverter<T>`
- constraints: `where T : UhtType`
- desc: JSON converter to output the source name of a type
- L64-67 _public method_ `public override T Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Read the JSON value
- L75-78 _public method_ `public override void Write(Utf8JsonWriter writer, T type, JsonSerializerOptions options)` — Write the JSON value

#### class `EpicGames.UHT.Utils.UhtNullableTypeSourceNameJsonConverter`  
`public class UhtNullableTypeSourceNameJsonConverter<T> : JsonConverter<T> where T : UhtType`  
_public; L85-113_
- inherits: `JsonConverter<T>`
- constraints: `where T : UhtType`
- desc: Read/Write type source name for an optional type value
- L95-98 _public method_ `public override T Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Read the JSON value
- L106-112 _public method_ `public override void Write(Utf8JsonWriter writer, T? type, JsonSerializerOptions options)` — Write the JSON value

#### class `EpicGames.UHT.Utils.UhtTypeReadOnlyListSourceNameJsonConverter`  
`public class UhtTypeReadOnlyListSourceNameJsonConverter<T> : JsonConverter<IReadOnlyList<T>> where T : UhtType`  
_public; L119-149_
- inherits: `JsonConverter<IReadOnlyList<T>>`
- constraints: `where T : UhtType`
- desc: Read/Write type list source name for an optional type value
- L129-132 _public method_ `public override IReadOnlyList<T> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Read the JSON value
- L140-148 _public method_ `public override void Write(Utf8JsonWriter writer, IReadOnlyList<T> collection, JsonSerializerOptions options)` — Write the JSON value

#### class `EpicGames.UHT.Utils.UhtTypeListJsonConverter`  
`public class UhtTypeListJsonConverter<T> : JsonConverter<List<T>> where T : UhtType`  
_public; L155-185_
- inherits: `JsonConverter<List<T>>`
- constraints: `where T : UhtType`
- desc: Serialize a list of types
- L165-168 _public method_ `public override List<T> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Read the JSON value
- L176-184 _public method_ `public override void Write(Utf8JsonWriter writer, List<T> collection, JsonSerializerOptions options)` — Write the JSON value

#### class `EpicGames.UHT.Utils.UhtNullableTypeListJsonConverter`  
`public class UhtNullableTypeListJsonConverter<T> : JsonConverter<List<T>> where T : UhtType`  
_public; L191-224_
- inherits: `JsonConverter<List<T>>`
- constraints: `where T : UhtType`
- desc: Serialize a nullable list of types
- L201-204 _public method_ `public override List<T> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Read the JSON value
- L212-223 _public method_ `public override void Write(Utf8JsonWriter writer, List<T>? collection, JsonSerializerOptions options)` — Write the JSON value

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtMessage.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Utils.UhtMessageType`  
`public enum UhtMessageType`  
_public; L15-46_
- desc: Type of message
- L20 _public* enumerator_ `Error` — The message is an error and goes to the log and console
- L25 _public* enumerator_ `Warning` — The message is a warning and goes to the log and console
- L30 _public* enumerator_ `Info` — The message is for information only and goes to the log and console
- L35 _public* enumerator_ `Trace` — The message is for debugging and goes to the log only
- L40 _public* enumerator_ `Deprecation` — The message is an informational message about deprecated patterns
- L45 _public* enumerator_ `Ice` — The message is an internal error and goes to the log and console

#### interface `EpicGames.UHT.Utils.IUhtMessageSession`  
`public interface IUhtMessageSession`  
_public; L51-59_
- desc: A message session is the destination object for all generated messages
- L58 _public* method_ `void AddMessage(UhtMessage message)` — Add the given message

#### interface `EpicGames.UHT.Utils.IUhtMessageSource`  
`public interface IUhtMessageSource`  
_public; L64-95_
- desc: A message source represents the source file where the message occurred.
- L69 _public* property_ `string MessageFilePath { get; }` — File path of the file being parsed
- L74 _public* property_ `string MessageFullFilePath { get; }` — The full file path of being parsed
- L79 _public* property_ `bool MessageIsFragment { get; }` — If true, the source is a source fragment from the testing harness
- L84 _public* property_ `string MessageFragmentFilePath { get; }` — If this is a fragment, this is the container file path of the fragment
- L89 _public* property_ `string MessageFragmentFullFilePath { get; }` — If this is a fragment, this is the container full file path of the fragment
- L94 _public* property_ `int MessageFragmentLineNumber { get; }` — If this is a fragment, this is the line number in the container file where the fragment is defined.

#### interface `EpicGames.UHT.Utils.IUhtMessageLineNumber`  
`public interface IUhtMessageLineNumber`  
_public; L102-109_
- desc: A message site can automatically provide a line number where the site was defined in the source. If no line number is provided when the message is created or if the site doesn't support this interface, the line number of '1' will be used.
- L108 _public* property_ `int MessageLineNumber { get; }` — Line number where the type was defined.

#### interface `EpicGames.UHT.Utils.IUhtMessageExtraContext`  
`public interface IUhtMessageExtraContext`  
_public; L114-120_
- desc: This interface provides a mechanism for things to provide more context for an error
- L119 _public* property_ `IEnumerable<object?>? MessageExtraContext { get; }` — Enumeration of objects to add as extra context.

#### interface `EpicGames.UHT.Utils.IUhtMessageSite`  
`public interface IUhtMessageSite`  
_public; L127-144_
- desc: A message site is any object that can generate a message. In general, all types are also message sites. This provides a convenient method to log messages where the type was defined.
- L133 _public property_ `public IUhtMessageSession MessageSession { get; }` — Destination message session for the messages
- L138 _public property_ `public IUhtMessageSource? MessageSource { get; }` — Source file generating messages
- L143 _public property_ `public IUhtMessageLineNumber? MessageLineNumber { get; }` — Optional line number where type was defined

#### struct `EpicGames.UHT.Utils.UhtMessage`  
`public struct UhtMessage`  
_public; L149-272_
- desc: Represents a UHT message
- L154 _public property_ `public UhtMessageType MessageType { get; set; }` — The type of message
- L159 _public property_ `public IUhtMessageSource? MessageSource { get; set; }` — Optional message source for the message. Either the MessageSource or FilePath must be set.
- L164 _public property_ `public string? FilePath { get; set; }` — Optional file path for the message. Either the MessageSource or FilePath must be set.
- L169 _public property_ `public int LineNumber { get; set; }` — Line number where error occurred.
- L174 _public property_ `public string Message { get; set; }` — Text of the message
- L185-195 _public method_ `public static UhtMessage MakeMessage(UhtMessageType messageType, IUhtMessageSource? messageSource, string? filePath, int lineNumber, string message)` — Make a new message with the given settings
- L202-240 _public method_ `public static string FormatContext(object context)` — Format an object to be included in a message
- L248-271 _public method_ `public static void Append(StringBuilder builder, IUhtMessageExtraContext? messageExtraContextInterface, bool alwaysIncludeSeparator)` — Append message context

#### class `EpicGames.UHT.Utils.UhtEmptyMessageSite`  
`public class UhtEmptyMessageSite : IUhtMessageSite`  
_public; L277-287_
- inherits: `IUhtMessageSite`
- desc: A placeholder message site
- L280 _public property_ `public IUhtMessageSession MessageSession => ...` — (inheritdoc)
- L283 _public property_ `public IUhtMessageSource? MessageSource => ...` — (inheritdoc)
- L286 _public property_ `public IUhtMessageLineNumber? MessageLineNumber => ...` — (inheritdoc)

#### class `EpicGames.UHT.Utils.UhtSimpleMessageSite`  
`public class UhtSimpleMessageSite : IUhtMessageSite`  
_public; L292-316_
- inherits: `IUhtMessageSite`
- desc: Creates a message site from a message session interface and a message source interface
- L294 _private field_ `private readonly IUhtMessageSession _messageSession`
- L295 _private field_ `private IUhtMessageSource? _messageSource`
- L299 _public property_ `public IUhtMessageSession MessageSession => ...` — (inheritdoc)
- L301 _public property_ `public IUhtMessageSource? MessageSource { get; set; }` — (inheritdoc)
- L303 _public property_ `public IUhtMessageLineNumber? MessageLineNumber => ...` — (inheritdoc)
- L311-315 _public ctor_ `public UhtSimpleMessageSite(IUhtMessageSession messageSession, IUhtMessageSource? messageSource = null)` — Create a simple message site for the given session and source

#### class `EpicGames.UHT.Utils.UhtSimpleFileMessageSite`  
`public class UhtSimpleFileMessageSite : UhtSimpleMessageSite, IUhtMessageSource`  
_public; L321-350_
- inherits: `UhtSimpleMessageSite, IUhtMessageSource`
- desc: Simple message site for the given file.
- L325 _public property_ `public string MessageFilePath => ...` — (inheritdoc)
- L327 _public property_ `public string MessageFullFilePath => ...` — (inheritdoc)
- L329 _public property_ `public bool MessageIsFragment => ...` — (inheritdoc)
- L331 _public property_ `public string MessageFragmentFilePath => ...` — (inheritdoc)
- L333 _public property_ `public string MessageFragmentFullFilePath => ...` — (inheritdoc)
- L335 _public property_ `public int MessageFragmentLineNumber => ...` — (inheritdoc)
- L338 _private field_ `private readonly string _filePath`
- L345-349 _public ctor_ `public UhtSimpleFileMessageSite(IUhtMessageSession messageSession, string filePath) : base(messageSession, null)` — Create a simple file site

#### class `EpicGames.UHT.Utils.UhtMessageSiteExtensions`  
`public static class UhtMessageSiteExtensions`  
_public; L355-510_
- desc: Series of extensions for message sites.
- L363-377 _public method_ `public static int GetLineNumber(this IUhtMessageSite messageSite, int lineNumber = -1)` — Get the line number generating the error
- L386-389 _public method_ `public static void LogError(this IUhtMessageSite messageSite, int lineNumber, string message, object? extraContext = null)` — Log an error
- L397-400 _public method_ `public static void LogError(this IUhtMessageSite messageSite, string message, object? extraContext = null)` — Log an error
- L409-412 _public method_ `public static void LogWarning(this IUhtMessageSite messageSite, int lineNumber, string message, object? extraContext = null)` — Log a warning
- L420-423 _public method_ `public static void LogWarning(this IUhtMessageSite messageSite, string message, object? extraContext = null)` — Log a warning
- L432-435 _public method_ `public static void LogTrace(this IUhtMessageSite messageSite, int lineNumber, string message, object? extraContext = null)` — Log a message directly to the log
- L443-446 _public method_ `public static void LogTrace(this IUhtMessageSite messageSite, string message, object? extraContext = null)` — Log a message directly to the log
- L455-458 _public method_ `public static void LogInfo(this IUhtMessageSite messageSite, int lineNumber, string message, object? extraContext = null)` — Log information
- L466-469 _public method_ `public static void LogInfo(this IUhtMessageSite messageSite, string message, object? extraContext = null)` — Log a information
- L478-481 _public method_ `public static void LogDeprecation(this IUhtMessageSite messageSite, int lineNumber, string message, object? extraContext = null)` — Log deprecation
- L489-492 _public method_ `public static void LogDeprecation(this IUhtMessageSite messageSite, string message, object? extraContext = null)` — Log a deprecation
- L502-509 _private method_ `private static void LogMessage(UhtMessageType messageType, IUhtMessageSite messageSite, int lineNumber, string message, object? extraContext)` — Log a message

#### class `EpicGames.UHT.Utils.UhtTlsMessageExtraContext`  
`public sealed class UhtTlsMessageExtraContext : IUhtMessageExtraContext`  
_public; L515-553_
- inherits: `IUhtMessageExtraContext`
- desc: Thread based message context. Used to improve performance by avoiding allocations.
- L517 _private field_ `private Stack<object?>? _extraContexts`
- L518 _private field_ `private static readonly ThreadLocal<UhtTlsMessageExtraContext> s_tls = new(() => new UhtTlsMessageExtraContext())`
- L521 _private* property_ `IEnumerable<object?>? IUhtMessageExtraContext.MessageExtraContext => ...`
- L528-532 _public method_ `public void PushExtraContext(object? exceptionContext)` — Add an extra context
- L537-540 _public method_ `public void PopExtraContext()` — Pop the top most extra context
- L546 _public method_ `public static UhtTlsMessageExtraContext? GetTls()` — Get the extra context associated with this thread
- L552 _public method_ `public static IUhtMessageExtraContext? GetMessageExtraContext()` — Get the extra context interface

#### struct `EpicGames.UHT.Utils.UhtMessageContext`  
`public readonly struct UhtMessageContext : IDisposable`  
_public; L558-593_
- inherits: `IDisposable`
- desc: A "using" object to automate the push/pop of extra context to the thread's current extra context
- L560 _private field_ `private readonly UhtTlsMessageExtraContext? _stack`
- L566-570 _public ctor_ `public UhtMessageContext(object? extraContext)` — Construct a new entry
- L577-584 _public method_ `public void Reset(object? extraContext)` — Replace the extra context. This replaces the top level context and thus can have unexpected results if done when a more deeper context has been added
- L589-592 _public method_ `public void Dispose()` — Dispose the object and auto-remove the added context

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtNames.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtNames`  
`public static class UhtNames`  
_public; L12-120_
- desc: Collection of common name strings
- L15 _public const_ `public const string AdvancedClassDisplay = "AdvancedClassDisplay"`
- L16 _public const_ `public const string AdvancedDisplay = "AdvancedDisplay"`
- L17 _public const_ `public const string AllowPrivateAccess = "AllowPrivateAccess"`
- L18 _public const_ `public const string ArraySizeEnum = "ArraySizeEnum"`
- L19 _public const_ `public const string AutoCollapseCategories = "AutoCollapseCategories"`
- L20 _public const_ `public const string AutoExpandCategories = "AutoExpandCategories"`
- L21 _public const_ `public const string BlueprintGetter = "BlueprintGetter"`
- L22 _public const_ `public const string BlueprintInternalUseOnly = "BlueprintInternalUseOnly"`
- L23 _public const_ `public const string BlueprintSetter = "BlueprintSetter"`
- L24 _public const_ `public const string CallInEditor = "CallInEditor"`
- L25 _public const_ `public const string BlueprintType = "BlueprintType"`
- L26 _public const_ `public const string StateStreamStaticState = "StateStreamStaticState"`
- L27 _public const_ `public const string StateStreamDynamicState = "StateStreamDynamicState"`
- L28 _public const_ `public const string StateStreamHandle = "StateStreamHandle"`
- L29 _public const_ `public const string CannotImplementInterfaceInBlueprint = "CannotImplementInterfaceInBlueprint"`
- L30 _public const_ `public const string Category = "Category"`
- L31 _public const_ `public const string ClassGroupNames = "ClassGroupNames"`
- L32 _public const_ `public const string Comment = "Comment"`
- L33 _public const_ `public const string Constant = "Constant"`
- L34 _public const_ `public const string CppFromBpEvent = "CppFromBpEvent"`
- L35 _public const_ `public const string CustomThunk = "CustomThunk"`
- L36 _public const_ `public const string Deprecated = "Deprecated"`
- L37 _public const_ `public const string DeprecatedFunction = "DeprecatedFunction"`
- L38 _public const_ `public const string DisplayName = "DisplayName"`
- L39 _public const_ `public const string DocumentationPolicy = "DocumentationPolicy"`
- L40 _public const_ `public const string EditorConfig = "EditorConfig"`
- L41 _public const_ `public const string EditInline = "EditInline"`
- L42 _public const_ `public const string EnumDisplayNameFn = "EnumDisplayNameFn"`
- L43 _public const_ `public const string ExposeOnSpawn = "ExposeOnSpawn"`
- L44 _public const_ `public const string GetByRef = "GetByRef"`
- L45 _public const_ `public const string Hidden = "Hidden"`
- L46 _public const_ `public const string HideCategories = "HideCategories"`
- L47 _public const_ `public const string HideFunctions = "HideFunctions"`
- L48 _public const_ `public const string IgnoreCategoryKeywordsInSubclasses = "IgnoreCategoryKeywordsInSubclasses"`
- L49 _public const_ `public const string IncludePath = "IncludePath"`
- L50 _public const_ `public const string Input = "Input"`
- L51 _public const_ `public const string Interface = "Interface"`
- L52 _public const_ `public const string IsBlueprintBase = "IsBlueprintBase"`
- L53 _public const_ `public const string IsConversionRoot = "IsConversionRoot"`
- L54 _public const_ `public const string ModuleRelativePath = "ModuleRelativePath"`
- L55 _public const_ `public const string Name = "Name"`
- L56 _public const_ `public const string NativeConst = "NativeConst"`
- L57 _public const_ `public const string NativeConstTemplateArg = "NativeConstTemplateArg"`
- L58 _public const_ `public const string NoGetter = "NoGetter"`
- L59 _public const_ `public const string ObjectInitializerConstructorDeclared = "ObjectInitializerConstructorDeclared"`
- L60 _public const_ `public const string Output = "Output"`
- L61 _public const_ `public const string Pins = "Pins"`
- L62 _public const_ `public const string PrioritizeCategories = "PrioritizeCategories"`
- L63 _public const_ `public const string ReturnValue = "ReturnValue"`
- L64 _public const_ `public const string ShortToolTip = "ShortToolTip"`
- L65 _public const_ `public const string ShowCategories = "ShowCategories"`
- L66 _public const_ `public const string ShowFunctions = "ShowFunctions"`
- L67 _public const_ `public const string SparseClassDataTypes = "SparseClassDataTypes"`
- L68 _public const_ `public const string ToolTip = "ToolTip"`
- L69 _public const_ `public const string UIMin = "UIMin"`
- L70 _public const_ `public const string UIMax = "UIMax"`
- L71 _public const_ `public const string Visible = "Visible"`
- L74 _public const_ `public const string VerseProxySuffix = "__Proxy"`
- L75 _public const_ `public const string VerseNotNativePrefix = "__VerseOnly_"`
- L78 _public const_ `public const string WithHotReload = "WITH_HOT_RELOAD"`
- L79 _public const_ `public const string WithEditor = "WITH_EDITOR"`
- L80 _public const_ `public const string WithEditorOnlyData = "WITH_EDITORONLY_DATA"`
- L81 _public const_ `public const string WithEngine = "WITH_ENGINE"`
- L82 _public const_ `public const string WithCoreUObject = "WITH_COREUOBJECT"`
- L83 _public const_ `public const string WithVerseVM = "WITH_VERSE_VM"`
- L84 _public const_ `public const string WithVerseBPVM = "WITH_VERSE_BPVM"`
- L85 _public const_ `public const string WithTests = "WITH_TESTS"`
- L88 _public const_ `public const string Statics = "UHT_STATICS"`
- L89 _public const_ `public const string PropertyCppIdentifierPrefix = "NewProp_"`
- L92 _public field_ `public static readonly UhtCppIdentifier TypeId = new("Type")`
- L93 _public field_ `public static readonly UhtCppIdentifier StaticsTypeId = TypeId.MakeStatics()`
- L94 _public field_ `public static readonly UhtCppIdentifier PropPointersId = new("PropPointers")`
- L95 _public field_ `public static readonly UhtCppIdentifier StaticsPropPointersId = PropPointersId.MakeStatics()`
- L96 _public field_ `public static readonly UhtCppIdentifier SingletonFuncArrayId = new("SingletonFuncArray")`
- L97 _public field_ `public static readonly UhtCppIdentifier StaticsSingletonFuncArrayId = SingletonFuncArrayId.MakeStatics()`
- L98 _public field_ `public static readonly UhtCppIdentifier FuncInfoId = new("FuncInfo")`
- L99 _public field_ `public static readonly UhtCppIdentifier StaticsFuncInfoId = FuncInfoId.MakeStatics()`
- L100 _public field_ `public static readonly UhtCppIdentifier FuncsId = new("Funcs")`
- L101 _public field_ `public static readonly UhtCppIdentifier StaticsFuncsId = FuncsId.MakeStatics()`
- L102 _public field_ `public static readonly UhtCppIdentifier ClassInfoId = new("ClassInfo")`
- L103 _public field_ `public static readonly UhtCppIdentifier StaticsClassInfoId = ClassInfoId.MakeStatics()`
- L104 _public field_ `public static readonly UhtCppIdentifier ScriptStructInfoId = new("ScriptStructInfo")`
- L105 _public field_ `public static readonly UhtCppIdentifier StaticsScriptStructInfoId = ScriptStructInfoId.MakeStatics()`
- L106 _public field_ `public static readonly UhtCppIdentifier EnumInfoId = new("EnumInfo")`
- L107 _public field_ `public static readonly UhtCppIdentifier StaticsEnumInfoId = EnumInfoId.MakeStatics()`
- L108 _public field_ `public static readonly UhtCppIdentifier RigVMStructsId = new("RigVMStructs")`
- L109 _public field_ `public static readonly UhtCppIdentifier StaticsRigVMStructsId = RigVMStructsId.MakeStatics()`
- L110 _public field_ `public static readonly UhtCppIdentifier VerseFuncsId = new("VerseFuncs")`
- L111 _public field_ `public static readonly UhtCppIdentifier StaticsVerseFuncsId = VerseFuncsId.MakeStatics()`
- L112 _public field_ `public static readonly UhtCppIdentifier PartialInfoId = new("PartialInfo")`
- L113 _public field_ `public static readonly UhtCppIdentifier StaticsPartialInfoId = PartialInfoId.MakeStatics()`
- L116-119 _public method_ `public static UhtCppIdentifier GetPropertyIdentifier(UhtProperty? property)`

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtPropertyResolveArgs.cs` (EpicGames.UHT)


#### enum `EpicGames.UHT.Utils.UhtPropertyResolvePhase`  
`public enum UhtPropertyResolvePhase`  
_public; L15-27_
- desc: The phase of UHT where the property is being resolved
- L21 _public* enumerator_ `Parsing` — Resolved during the source processing phase. Immediate property types only.
- L26 _public* enumerator_ `Resolving` — Resolved during the resolve phase. Non-immediate property types only.

#### enum `EpicGames.UHT.Utils.UhtTemplateObjectMode`  
`public enum UhtTemplateObjectMode`  
_public; L32-48_
- desc: Controls what is returned from the parsing of a template object
- L37 _public* enumerator_ `Normal` — If the specified type. If the type is a native interface, return the UInterface
- L42 _public* enumerator_ `PreserveNativeInterface` — If a native interface is specified, return it
- L47 _public* enumerator_ `NativeInterfaceProxy` — The specified type must be an interface proxy

#### record struct `EpicGames.UHT.Utils.UhtPropertyResolveArgs`  
`public record struct UhtPropertyResolveArgs(UhtPropertyResolvePhase ResolvePhase, UhtPropertySettings PropertySettings, IUhtTokenReader TokenReader)`  
_public; L56-495_
- desc: Structure defining the arguments used in the delegate to resolve property types
- L62 _public property_ `public readonly UhtSession Session => ...` — Currently running UHT session
- L67 _public property_ `public readonly IUhtConfig Config => ...` — UHT configuration
- L72 _public property_ `public readonly UhtTypeTokensRef TypeTokens => ...`
- L77 _public property_ `public readonly bool IsTemplate => ...` — If true, a template argument is being resolved
- L83-98 _public method_ `public readonly bool SkipExpectedType()` — When processing type, make sure that the next token is the expected token
- L105-121 _public method_ `public readonly UhtProperty? ResolveProperty()` — Resolve the given property. This method will resolve any immediate property during the parsing phase or resolve any previously parsed property to the final version.
- L128-151 _public method_ `public readonly UhtProperty? ParseTemplateParam(StringView paramName)` — Parse a template parameter
- L157-180 _public method_ `public readonly UhtProperty? ParseWrappedType()` — For types such as TPtr or TVal, this method parses the template parameter and extracts the type
- L188-205 _public method_ `public readonly UhtProperty? ParseWrappedType(EPropertyFlags additionalFlags, UhtPropertyExportFlags additionalExportFlags)` — For types such as TPtr or TVal, this method parses the template parameter and extracts the type
- L212-266 _public method_ `public readonly UhtClass? ParseTemplateObject(UhtTemplateObjectMode mode)` — Parse a template type
- L274-284 _public method_ `public readonly UhtProperty? ParseTemplateObjectProperty(UhtTemplateObjectMode mode, Func<UhtClass, int, UhtProperty?> propertyFactory)` — Parse the token stream for a class type and then invoke the factory to create the property
- L290-321 _public method_ `public readonly UhtClass? ParseTemplateClass()` — Parse a template type
- L327-353 _public method_ `public readonly UhtScriptStruct? ParseTemplateScriptStruct()` — Parse a template type
- L363-416 _public method_ `public readonly void ConditionalLogPointerUsage(UhtIssueBehaviorSet behaviorSet, string pointerTypeDesc, int typeStartPos, string? alternativeTypeDesc)` — Logs message for Object pointers to convert UObject* to TObjectPtr or the reverse
- L422-465 _private method_ `private readonly bool ResolvePropertyType(out UhtPropertyType propertyType)` — Using the current type in the type tokens, try to locate a property type
- L472-494 _private method_ `private readonly int GetTypeTokenSegment()` — Given the current position of the token reader, return the segment being parsed

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtReferenceCollector.cs` (EpicGames.UHT)


#### interface `EpicGames.UHT.Utils.IUhtReferenceCollector`  
`public interface IUhtReferenceCollector`  
_public; L18-61_
- desc: Interface used to collect all the objects referenced by a given type. Not all types such as UhtPackage and UhtHeaderFile support collecting references due to assorted reasons.
- L27 _public* method_ `void AddObjectReference(UhtObject? obj, UhtSingletonType type)` — Add a reference to an object which needs to be linked. Depending on the type parameter and the configuration, it may be linked as a direct pointer, encoded pointer, or a pointer to a factory method. Also records the module the object is in as a module-module dependency
- L34 _public* method_ `void AddDeclaration(UhtObject obj, UhtSingletonType type)` — Add an object declaration
- L40 _public* method_ `void AddSingleton(UhtField field)` — Add a field as a singleton for exporting
- L46 _public* method_ `void AddExportType(UhtField field)` — Add a field as a type being exported
- L53 _public* method_ `void AddForwardDeclaration(UhtField field)` — Add a forward declaration. This is the preferred way of adding a forward declaration since the exporter will handle all the formatting requirements.
- L60 _public* method_ `void AddForwardDeclaration(UhtNamespace? namespaceObj, string? declaration)` — Add a forward declaration. The string can contain multiple declarations but must only exist on one line.

#### class `EpicGames.UHT.Utils.UhtUniqueReferenceCollection`  
`public class UhtUniqueReferenceCollection`  
_public; L66-168_
- desc: Maintains a list of referenced object indices.
- L71 _public property_ `public bool IsEmpty => ...` — Returns whether there is anything in this collection
- L76 _private property_ `private Dictionary<UhtObject, UhtSingletonTypeFlag> Uniques { get; }` — List of all unique references and the types required.
- L78 _private field_ `private static readonly UhtSingletonTypeFlag[] s_typeFlags = Enum.GetValues<UhtSingletonTypeFlag>()`
- L80 _private method_ `private static UhtSingletonType FlagToValue(UhtSingletonTypeFlag flag)`
- L94-104 _public method_ `public void Add(UhtObject? obj, UhtSingletonType type)` — Add the given object to the references
- L111-118 _public method_ `public IEnumerable<UhtObject> SortReferences(UhtSingletonTypeFlag typesFilter)` — Get references of a given set of types as a sorted enumerable.
- L125-167 _public method_ `public IReadOnlyList<string> GetSortedReferences(Func<int, UhtSingletonType, string?> referenceToString)` — Return the collection of references sorted by the API string returned by the delegate.

#### class `EpicGames.UHT.Utils.UhtReferenceCollector`  
`public class UhtReferenceCollector(UhtModule thisModule) : IUhtReferenceCollector`  
_public; L174-284_
- desc: Standard implementation of the reference collector interface. Used by a single header file in a module to collect references which are needed for the generated code for that particular header.
- L179 _public property_ `public HashSet<UhtModule> Modules { get; }` — Other modules encountered during reference collection for building module-to-module links
- L184 _public property_ `public UhtUniqueReferenceCollection InternalObjects { get; set; }` — Collection of unique object references in this module
- L189 _public property_ `public UhtUniqueReferenceCollection ExternalObjects { get; set; }` — Collection of unique object references in other modules
- L194 _public property_ `public UhtUniqueReferenceCollection Declaration { get; set; }` — Collection of unique declarations
- L199 _public property_ `public List<UhtField> Singletons { get; }` — Collection of singletons
- L204 _public property_ `public List<UhtField> ExportTypes { get; }` — Collection of types to export
- L209 _public property_ `public HashSet<UhtField> ForwardDeclarations { get; }` — Collection of fields needing forward declarations
- L214 _public property_ `public HashSet<string> ForwardDeclarationStrings { get; }` — Collection of forward declarations in text form
- L219 _public property_ `public HashSet<UhtHeaderFile> ReferencedHeaders { get; }` — Collection of referenced headers
- L222-240 _public method_ `public void AddObjectReference(UhtObject? obj, UhtSingletonType type)` — (inheritdoc)
- L243-246 _public method_ `public void AddDeclaration(UhtObject obj, UhtSingletonType type)` — (inheritdoc)
- L249-252 _public method_ `public void AddSingleton(UhtField field)` — (inheritdoc)
- L255-258 _public method_ `public void AddExportType(UhtField field)` — (inheritdoc)
- L261-264 _public method_ `public void AddForwardDeclaration(UhtField field)` — (inheritdoc)
- L267-283 _public method_ `public void AddForwardDeclaration(UhtNamespace? namespaceObj, string? declaration)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtSession.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Utils.UhtSourceFragment`  
`public struct UhtSourceFragment`  
_public; L30-52_
- desc: To support the testing framework, source files can be containing in other source files. A source fragment represents this possibility.
- L36 _public property_ `public UhtSourceFile? SourceFile { get; set; }` — When not null, this source comes from another source file
- L41 _public property_ `public string FilePath { get; set; }` — The file path of the source
- L46 _public property_ `public int LineNumber { get; set; }` — The line number of the fragment in the containing source file.
- L51 _public property_ `public StringView Data { get; set; }` — Data of the source file

#### struct `EpicGames.UHT.Utils.EngineVersion`  
`public struct EngineVersion`  
_public; L57-117_
- desc: A structure that represents an engine version.
- L62 _public property_ `public int MajorVersion { get; set; }` — The major engine version.
- L66 _public property_ `public int MinorVersion { get; set; }` — The minor engine version.
- L70 _public property_ `public int PatchVersion { get; set; }` — The patch engine version.
- L75 _public ctor_ `public EngineVersion()` — Build a default engine version (0.0.0).
- L80-85 _public ctor_ `public EngineVersion(int major, int minor, int patch)` — Build a new engine version with the given numbers.
- L92-107 _public method_ `public int CompareTo(EngineVersion other)` — Compares this engine version to another one.
- L113-116 _public method_ `public override string ToString()` — Generates a string representation of the engine version.

#### class `EpicGames.UHT.Utils.UhtExportFactory`  
`sealed class UhtExportFactory : IUhtExportFactory`  
_internal*; L122-616_
- inherits: `IUhtExportFactory`
- desc: Implementation of the export factory
- L134 _private field_ `private readonly UhtSession _session` — UHT session
- L139 _private field_ `private readonly UHTManifest.Module? _pluginModule` — Module associated with the plugin
- L145 _private field_ `private static readonly Semaphore s_writeRefSemaphore = new(32, 32)` — Limiter for the number of files being saved to the reference directory. The OS can get swamped on high core systems
- L150 _public field_ `public readonly UhtExporter Exporter` — Requesting exporter
- L155 _public property_ `public UhtSession Session => ...` — UHT Session
- L160 _public property_ `public UHTManifest.Module? PluginModule => ...` — Plugin module
- L165 _public property_ `public Dictionary<string, bool> ReferenceErrorMessages { get; }` — Collection of error from mismatches with the reference files
- L170 _public property_ `public List<Output> Outputs { get; }` — List of export outputs
- L175 _public property_ `public string ReferenceDirectory { get; set; }` — Directory for the reference output
- L180 _public property_ `public string VerifyDirectory { get; set; }` — Directory for the verify output
- L185 _public property_ `public HashSet<string> ExternalDependencies { get; }` — Collection of external dependencies
- L193-204 _public ctor_ `public UhtExportFactory(UhtSession session, UHTManifest.Module? pluginModule, UhtExporter exporter)` — Create a new instance of the export factory
- L213-218 _public method_ `public void CommitOutput(string filePath, StringBuilder builder)` — Commit the contents of the string builder as the output. If you have a string builder, use this method so that a temporary buffer can be used.
- L225-229 _public method_ `public void CommitOutput(string filePath, StringView output)` — Commit the value of the string as the output
- L237-256 _public method_ `public Task CreateTask(List<Task?>? prereqs, UhtExportTaskDelegate action)` — Create a task to export two files
- L263-266 _public method_ `public Task CreateTask(UhtExportTaskDelegate action)` — Create a task to export two files
- L274-277 _public method_ `public string MakePath(UhtHeaderFile headerFile, string suffix)` — Given a header file, generate the output file name.
- L285-288 _public method_ `public string MakePath(UhtModule module, string suffix)` — Given a package file, generate the output file name
- L296-303 _public method_ `public string MakePath(string fileName, string extension)` — Make a path for an output based on the package output directory.
- L309-312 _public method_ `public void AddExternalDependency(string filePath)` — Add an external dependency to the given file path
- L315-318 _public method_ `public string GetModuleShortestIncludePath(UhtModule moduleObj, string filePath)` — (inheritdoc)
- L321-328 _public method_ `public string GetPluginShortestIncludePath(string filePath)` — (inheritdoc)
- L330-358 _public method_ `public string GetShortestIncludePath(UHTManifest.Module moduleObj, string filePath)`
- L360-367 _private method_ `private string MakePath(UHTManifest.Module module, string fileName, string suffix)`
- L375-476 _internal method_ `internal void SaveIfChanged(string filePath, string tempFilePath, StringView exported)` — Helper method to test to see if the output has changed.
- L481-557 _public method_ `public void Run()` — Run the output exporter
- L564-567 _private method_ `private void RenameSource(UhtExportFactory.Output output)` — Given an output, rename the output file from the temporary file name to the final file name. If there exists a current final file, it will be replaced.
- L574-597 _private method_ `private void CullOutputDirectory(string outputDirectory, HashSet<string> knownOutputs)` — Given a directory and a list of known files, delete any unknown file that matches of the supplied filters
- L605-615 _private method_ `private static bool IsFilterMatch(string fileName, IEnumerable<string> filters)` — Test to see if the given filename (without directory), matches one of the given filters

#### struct `EpicGames.UHT.Utils.UhtExportFactory.Output`  
`public struct Output`  
_public; L124-129_
- L126 _public property_ `public string FilePath { get; set; }`
- L127 _public property_ `public string TempFilePath { get; set; }`
- L128 _public property_ `public bool Saved { get; set; }`

#### enum `EpicGames.UHT.Utils.UhtReferenceMode`  
`public enum UhtReferenceMode`  
_public; L622-638_
- desc: UHT supports the exporting of two reference output directories for testing. The reference version can be used to test modification to UHT and verify there are no output changes or just expected changes.
- L627 _public* enumerator_ `None` — Do not export any reference output files
- L632 _public* enumerator_ `Reference` — Export the reference copy
- L637 _public* enumerator_ `Verify` — Export the verify copy and compare to the reference copy

#### class `EpicGames.UHT.Utils.UhtCounter`  
`public class UhtCounter`  
_public; L643-659_
- desc: Helper class that implements a simple counter
- L645 _private field_ `private int _counter = 0`
- L650 _public property_ `public int Count => ...` — Return the current count
- L655-658 _public method_ `public void Increment()` — Increment the current count

#### class `EpicGames.UHT.Utils.UhtSession`  
`public partial class UhtSession : IUhtMessageSite, IUhtMessageSession`  
_public; L664-3159_
- inherits: `IUhtMessageSite, IUhtMessageSession`
- desc: Session object that represents a UHT run
- L682 _public property_ `public ILogger Logger { get; }` — Logger interface.
- L687 _public property_ `public IUhtFileManager? FileManager { get; set; }` — Interface used to read/write files
- L692 _public property_ `public string? EngineDirectory { get; set; }` — Location of the engine code
- L697 _public property_ `public string? ProjectFile { get; set; }` — If set, the name of the project file.
- L702 _public property_ `public string? ProjectDirectory { get; set; }` — Optional location of the project
- L707 _public property_ `public string? RootDirectory { get; set; }` — Root directory for the engine. This is usually just EngineDirectory without the Engine directory.
- L712 _public property_ `public string ReferenceDirectory { get; set; }` — Directory to store the reference output
- L717 _public property_ `public string VerifyDirectory { get; set; }` — Directory to store the verification output
- L722 _public property_ `public UhtReferenceMode ReferenceMode { get; set; }` — Mode for generating and/or testing reference output
- L727 _public property_ `public bool WarningsAsErrors { get; set; }` — If true, warnings are considered to be errors
- L732 _public property_ `public bool RelativePathInLog { get; set; }` — If true, include relative file paths in the log file
- L737 _public property_ `public bool GoWide { get; set; }` — If true, use concurrent tasks to run UHT
- L742 _public property_ `public bool FailIfGeneratedCodeChanges { get; set; }` — If any output file mismatches existing outputs, an error will be generated
- L747 _public property_ `public bool NoOutput { get; set; }` — If true, no output files will be saved
- L752 _public property_ `public bool CullOutput { get; set; }` — If true, cull the output for any extra files
- L757 _public property_ `public bool IncludeDebugOutput { get; set; }` — If true, include extra output in code generation
- L762 _public property_ `public bool NoDefaultExporters { get; set; }` — If true, disable all exporters which would normally be run by default
- L768 _public property_ `public bool CacheMessages { get; set; }` — If true, cache any error messages until the end of processing. This is used by the testing harness to generate more stable console output.
- L773 _public property_ `public bool ReportEmptyHeaders { get; set; }` — Report on any header that didn't contain any types
- L780 _public property_ `public UHTTargetSettings? TargetSettings => ...` — Access to target-wide settings for code generation etc.
- L785-789 _public property_ `public UhtCompiledInObjectFormat CompiledInObjectFormat { get; set; }` — What format of code to generate for compiled-in UObject instances such as UClass instances
- L790 _private field_ `private UhtCompiledInObjectFormat? _compiledInObjectFormat = null`
- L796-800 _public property_ `public bool EnableInputCacheRead { get; set; }` — If true, input cache read will be enabled from the UHT command line. Use Manifest.TargetSettings to query this setting.
- L801 _private field_ `private bool? _enableInputCacheRead = null`
- L807-811 _public property_ `public bool EnableInputCacheWrite { get; set; }` — If true, input cache write will be enabled from the UHT command line. Use Manifest.TargetSettings to query this setting.
- L812 _private field_ `private bool? _enableInputCacheWrite = null`
- L819 _public method_ `public bool IsUsingCompiledInObjectFormat(UhtCompiledInObjectFormat format)` — Returns whether UHT should generate a certain type of code for compiled-in object instances
- L825 _public property_ `public bool IsUsingMultipleCompiledInObjectFormats => ...` — Returns whether UHT is emitting code for multiple compiled-in object formats, and therefore such code should be surrounded by preprocessor checks
- L831 _public property_ `public UhtTables? Tables { get; set; }` — Collection of UHT tables
- L836 _public property_ `public IUhtConfig? Config { get; set; }` — Configuration for the session
- L841 _public property_ `public UhtManifestFile? ManifestFile { get; set; }` — Manifest file
- L846 _public property_ `public UHTManifest? Manifest => ...` — Manifest data from the manifest file
- L851 _public property_ `public ReadOnlyMemory<byte> ConfigData { get; set; }` — Block of configuration data from the config and manifest. Used by the input cache.
- L856 _public property_ `public IReadOnlyList<UhtModule> Modules => ...` — Collection of modules from the manifest
- L857 _private field_ `private readonly List<UhtModule> _modules = []`
- L863 _public property_ `public IReadOnlyList<UhtHeaderFile> HeaderFiles => ...` — Collection of header files from the manifest. The header files will also appear as the children of the packages
- L864 _private field_ `private readonly List<UhtHeaderFile> _headerFiles = []`
- L870 _public property_ `public IReadOnlyList<UhtHeaderFile> SortedHeaderFiles => ...` — Collection of header files topologically sorted. This will not be populated until after header files are parsed and resolved.
- L871 _private field_ `private readonly List<UhtHeaderFile> _sortedHeaderFiles = []`
- L876 _public property_ `public IReadOnlyDictionary<string, UhtHeaderFile> HeaderFileDictionary => ...` — Dictionary of stripped file name to the header file
- L877 _private field_ `private readonly Dictionary<string, UhtHeaderFile> _headerFileDictionary = ...`
- L877 _private field_ `private readonly Dictionary< _headerFileDictionary = new(StringComparer.OrdinalIgnoreCase)`
- L882 _public property_ `public EngineVersion EngineVersion => ...` — Gets the version of the engine this session belongs to.
- L883 _private field_ `private readonly Lazy<EngineVersion> _engineVersion`
- L888 _public property_ `public DateTime AssemblyDateTime { get; set; }` — Latest date/time for the main UHT assembly and the plugins
- L894 _public property_ `public UhtClass UObject => ...` — After headers are parsed, returns the UObject class.
- L895 _private field_ `private UhtClass? _uobject = null`
- L900 _public property_ `public UhtClass UPackage => ...` — After headers are parsed, returns the UPackage class.
- L901 _private field_ `private UhtClass? _upackage = null`
- L906 _public property_ `public UhtClass UClass => ...` — After headers are parsed, returns the UClass class.
- L907 _private field_ `private UhtClass? _uclass = null`
- L912 _public property_ `public UhtClass UVerseClass => ...` — After headers are parsed, returns the UClass class.
- L913 _private field_ `private UhtClass? _uverseclass = null`
- L918 _public property_ `public UhtClass UScriptStruct => ...` — After headers are parsed, returns the UScriptStruct class.
- L919 _private field_ `private UhtClass? _uscriptstruct = null`
- L924 _public property_ `public UhtClass UVerseStruct => ...` — After headers are parsed, returns the UScriptStruct class.
- L925 _private field_ `private UhtClass? _uversestruct = null`
- L930 _public property_ `public UhtClass UFunction => ...` — After headers are parsed, returns the UFunction class.
- L931 _private field_ `private UhtClass? _ufunction = null`
- L936 _public property_ `public UhtClass UDelegateFunction => ...` — After headers are parsed, returns the UDelegateFunction class.
- L937 _private field_ `private UhtClass? _udelegatefunction = null`
- L942 _public property_ `public UhtClass USparseDelegateFunction => ...` — After headers are parsed, returns the USparseDelegateFunction class.
- L943 _private field_ `private UhtClass? _usparsedelegatefunction = null`
- L948 _public property_ `public UhtClass UVerseFunction => ...` — After headers are parsed, returns the UFunction class.
- L949 _private field_ `private UhtClass? _uversefunction = null`
- L954 _public property_ `public UhtClass UEnum => ...` — After headers are parsed, returns the UEnum class.
- L955 _private field_ `private UhtClass? _uenum = null`
- L960 _public property_ `public UhtClass UVerseEnum => ...` — After headers are parsed, returns the UEnum class.
- L961 _private field_ `private UhtClass? _uverseenum = null`
- L966 _public property_ `public UhtClass UInterface => ...` — After headers are parsed, returns the UInterface class.
- L967 _private field_ `private UhtClass? _uinterface = null`
- L972 _public property_ `public UhtClass IInterface => ...` — After headers are parsed, returns the IInterface class.
- L973 _private field_ `private UhtClass? _iinterface = null`
- L979 _public property_ `public UhtClass? AActor { get; set; }` — After headers are parsed, returns the AActor class. Unlike such properties as "UObject", there is no requirement for AActor to be defined. May be null.
- L985 _public property_ `public UhtClass? INotifyFieldValueChanged { get; set; }` — After headers are parsed, return the INotifyFieldValueChanged interface. There is no requirement that this interface be defined.
- L991 _public property_ `public UhtScriptStruct? FInstancedStruct { get; set; }` — After headers are parsed, returns the FInstancedStruct script struct. Unlike such properties as "UObject", there is no requirement for FInstancedStruct to be defined. May be null.
- L997 _public property_ `public UhtScriptStruct? FSubScriptStructOf { get; set; }` — After headers are parsed, returns the FSubScriptStructOf script struct. Unlike such properties as "UObject", there is no requirement for FSubScriptStructOf to be defined. May be null.
- L1003 _public property_ `public UhtScriptStruct? FStateTreePropertyRef { get; set; }` — After headers are parsed, returns the FStateTreePropertyRef script struct. There is no requirement for FStateTreePropertyRef to be defined. May be null.
- L1009 _public property_ `public UhtEnum? EVerseNativeCallResult { get; set; }` — After headers are parsed, returns the EVerseNativeCallResult enumeration. There is no requirement for EVerseNativeCallResult to be defined. May be null.
- L1014 _public property_ `public UhtHeaderFile? NoExportTypesHeader { get; set; }` — NoExportTypes.h header in CoreUObject module.
- L1023-1031 _private method_ `private static T CheckNull<T>(T? type, string typeName) where T : class` — Given a nullable type, throw an exception if not set.
- L1036-1058 _private method_ `private void ResolveWellKnownTypes()` — Look up all the commonly needed types from the symbol table
- L1065 _public property_ `public UhtCounter ErrorCount { get; }` — The number of errors
- L1070 _public property_ `public UhtCounter WarningCount { get; }` — The number of warnings
- L1075 _public property_ `public bool HasErrors => ...` — True if any errors have occurred or warnings if warnings are to be treated as errors
- L1080 _public property_ `public UhtCounter FilesWritten { get; }` — Number of new/modified files written to disk
- L1085 _public property_ `public UhtCounter FilesRead { get; }` — Number of source files read directly from disk
- L1090 _public property_ `public UhtCounter FilesCacheRead { get; }` — Number of source files read from cache
- L1095 _public property_ `public UhtCounter FilesCacheReadErrors { get; }` — Number of source files failed to deserialize
- L1100 _public property_ `public UhtCounter FilesCacheWriteErrors { get; }` — Number of source files failed to serialize
- L1105 _public property_ `public UhtCounter CacheFilesRead { get; }` — Number of cache files read
- L1110 _public property_ `public UhtCounter CacheFilesWritten { get; }` — Number of cache files written
- L1115 _public property_ `public UhtCounter CacheFilesSkippedFNF { get; }` — Number of skipped caches files because they were not found
- L1120 _public property_ `public UhtCounter CacheFilesSkippedAssemblyDateTime { get; }` — Number of skipped caches files because the assembly time did not match
- L1125 _public property_ `public UhtCounter CacheFilesSkippedVersion { get; }` — Number of skipped caches files because version number mismatch
- L1130 _public property_ `public UhtCounter CacheFilesSkippedConfigChanged { get; }` — Number of skipped caches files because configuration changed
- L1135 _public property_ `public UhtCounter CacheFilesSkippedCorrupted { get; }` — Number of skipped caches files because file is corrupted
- L1138 _private field_ `private Task? _referenceDeleteTask = null`
- L1139 _private field_ `private Task[]? _inputCacheWriteTasks = null`
- L1140 _private field_ `private readonly Dictionary<string, bool> _exporterStates = ...`
- L1140 _private field_ `private readonly Dictionary< _exporterStates = new(StringComparer.OrdinalIgnoreCase)`
- L1141 _private field_ `private readonly Dictionary<string, EnumAndValue> _fullEnumValueLookup = ...`
- L1141 _private field_ `private readonly Dictionary< _fullEnumValueLookup = []`
- L1142 _private field_ `private readonly Dictionary<string, UhtEnum> _shortEnumValueLookup = ...`
- L1142 _private field_ `private readonly Dictionary< _shortEnumValueLookup = []`
- L1143 _private field_ `private JsonDocument? _projectJson = null`
- L1147 _public property_ `public IUhtMessageSession MessageSession => ...` — (inheritdoc)
- L1149 _public property_ `public IUhtMessageSource? MessageSource => ...` — (inheritdoc)
- L1151 _public property_ `public IUhtMessageLineNumber? MessageLineNumber => ...` — (inheritdoc)
- L1158-1164 _public ctor_ `public UhtSession(ILogger logger)` — Constructor
- L1197-1200 _public method_ `public int GetNextTypeIndex()` — Return the index for a newly defined type
- L1205 _public property_ `public int TypeCount => ...` — Return the number of types that have been defined. This includes all types.
- L1206 _private field_ `private readonly TypeCounter _typeCounter = new()`
- L1212-1215 _public method_ `public int GetNextHeaderFileTypeIndex()` — Return the index for a newly defined packaging
- L1220 _public property_ `public int HeaderFileTypeCount => ...` — Return the number of headers that have been defined
- L1221 _private field_ `private readonly TypeCounter _headerFileTypeCount = new()`
- L1227-1230 _public method_ `public int GetNextPackageTypeIndex()` — Return the index for a newly defined package
- L1235 _public property_ `public int PackageTypeCount => ...` — Return the number of UPackage types that have been defined
- L1236 _private field_ `private readonly TypeCounter _packageTypeCount = new()`
- L1242-1245 _public method_ `public int GetNextObjectTypeIndex()` — Return the index for a newly defined object
- L1250 _public property_ `public int ObjectTypeCount => ...` — Return the total number of UObject types that have been defined
- L1251 _private field_ `private readonly TypeCounter _objectTypeCount = new()`
- L1257 _public property_ `public UhtExporterTable ExporterTable => ...` — Return the collection of exporters
- L1264-1267 _public method_ `public UhtKeywordTable GetKeywordTable(string tableName)` — Return the keyword table for the given table name
- L1274-1277 _public method_ `public UhtSpecifierTable GetSpecifierTable(string tableName)` — Return the specifier table for the given table name
- L1284-1287 _public method_ `public UhtSpecifierValidatorTable GetSpecifierValidatorTable(string tableName)` — Return the specifier validator table for the given table name
- L1294-1297 _public method_ `public void LogUnhandledKeywordError(IUhtTokenReader tokenReader, UhtToken token)` — Generate an error for the given unhandled keyword
- L1304-1307 _public method_ `public bool IsValidPropertyTypeName(StringView name)` — Test to see if the given class name is a property
- L1315-1318 _public method_ `public bool TryGetLocTextDefaultValue(StringView name, out UhtLocTextDefaultValue locTextDefaultValue)` — Return the loc text default value associated with the given name
- L1323 _public property_ `public UhtPropertyType DefaultPropertyType => ...` — Return the default processor
- L1331-1334 _public method_ `public bool TryGetPropertyType(StringView name, out UhtPropertyType propertyType)` — Return the property type associated with the given name
- L1339 _public property_ `public UhtStructDefaultValue DefaultStructDefaultValue => ...` — Fetch the default sanitizer
- L1347-1350 _public method_ `public bool TryGetStructDefaultValue(StringView name, out UhtStructDefaultValue structDefaultValue)` — Return the structure default value associated with the given name
- L1357-1485 _public method_ `public void Run(string manifestFilePath, CommandLineArguments? arguments = null)` — Run UHT on the given manifest. Use the bHasError property to see if process was successful.
- L1494-1500 _public method_ `public void Try(IUhtMessageSource? messageSource, Action action)` — Try the given action. If an exception occurs that doesn't have the required context, use the supplied context to generate the message. If a previous error has occurred, the action will not be executed
- L1508-1518 _public method_ `public void TryNoErrorCheck(IUhtMessageSource? messageSource, Action action)` — Try the given action. If an exception occurs that doesn't have the required context, use the supplied context to generate the message.
- L1525-1531 _public method_ `public void ForEachHeader(Action<UhtHeaderFile> action, bool allowGoWide)` — Execute the given action on all the headers
- L1538-1554 _public method_ `public void ForEachHeaderNoErrorCheck(Action<UhtHeaderFile> action, bool allowGoWide)` — Execute the given action on all the headers
- L1562-1569 _public method_ `public UhtSourceFragment ReadSource(string filePath)` — Read the given source file
- L1577-1580 _public method_ `public bool ReadSource(string filePath, out UhtPoolBuffer<char> output)` — Read the given source file
- L1588-1591 _internal method_ `internal bool WriteSource(string filePath, ReadOnlySpan<char> contents)` — Write the given contents to the file
- L1598-1604 _public method_ `public void RenameSource(string oldFilePath, string newFilePath)` — Rename the given file
- L1612-1619 _public method_ `public UhtHeaderFile? FindHeaderFile(string name)` — Search for the given header file by just the file name
- L1625 _private field_ `private readonly ConcurrentDictionary<string, UhtNamespace> _namespaces = ...` — Collection of all defined namespaces
- L1625 _private field_ `private readonly ConcurrentDictionary< _namespaces = []` — Collection of all defined namespaces
- L1630 _public property_ `public UhtNamespace GlobalNamespace { get; }` — Global namespace
- L1639-1668 _public method_ `public UhtNamespace GetNamespace(List<UhtNamespaceElement> namespaceElements, Dictionary<string, UhtNamespace> headerNamespaceLookupCache)` — Get the given namespace
- L1675-1702 _public method_ `public UhtNamespace GetNamespace(string fullName)` — Given a complete string (no leading ::), return the namespace
- L1704-1720 _private method_ `private UhtNamespace GetNamespace(List<UhtNamespaceElement> namespaceElements, int index, string fullName, Dictionary<string, UhtNamespace>? headerNamespaceLookupCache)`
- L1724 _private field_ `private readonly List<UhtMessage> _messages = []`
- L1725 _private field_ `private Task? _messageTask = null`
- L1731-1766 _public method_ `public void AddMessage(UhtMessage message)` — Add a message to the collection of output messages
- L1773-1776 _public method_ `public void SignalError()` — Register than an error has happened
- L1784-1797 _public method_ `public void LogMessages()` — Log all the collected messages to the log/console. If messages aren't being cached, then this just waits until the flush task has completed. If messages are being cached, they are sorted by file name and line number to ensure the output is stable.
- L1802-1823 _private method_ `private void FlushMessages()` — Flush all pending messages to the logger
- L1829-1864 _private method_ `private void LogMessage(UhtMessage msg)` — Log the given message
- L1870-1879 _public method_ `public List<string> CollectMessages()` — Return all of the messages into a list
- L1885-1894 _private method_ `private IOrderedEnumerable<UhtMessage> FetchOrderedMessages()` — Return an ordered enumeration of all messages.
- L1905-1971 _private method_ `private void GetMessageParts(UhtMessage msg, out string filePath, out int lineNumber, out string fragmentPath, out string severity, out string message)` — Extract the part of a message
- L1978-1997 _private method_ `private void HandleException(IUhtMessageSource? messageSource, Exception e)` — Handle the given exception with the provided message context
- L2001 _private method_ `private static partial Regex GetEngineVersionFragmentRegex()` — attrs: `[GeneratedRegex(@"^\#define\s+ENGINE_(?<Name>[A-Z]+)_VERSION\s+(?<Number>\d+)\s*$")]`
- L2003-2061 _private method_ `private EngineVersion LoadEngineVersion()`
- L2064-2092 _private method_ `private void StepReadManifestFile(string manifestFilePath)`
- L2094-2111 _private method_ `private void StepPrepareModules()`
- L2113-2139 _private method_ `private void StepPrepareHeaders()`
- L2141-2178 _private method_ `private void StepParseHeaders()`
- L2180-2209 _private method_ `private void StepWriteInputCache()`
- L2211-2224 _private method_ `private void StepPopulateTypeTable()`
- L2226-2230 _private method_ `private void StepBindSuperAndBases()`
- L2232-2236 _private method_ `private void StepResolveBases()`
- L2238-2242 _private method_ `private void StepResolveInvalidCheck()`
- L2244-2248 _private method_ `private void StepResolveProperties()`
- L2250-2254 _private method_ `private void StepResolveFinal()`
- L2256-2260 _private method_ `private void StepResolveValidate()`
- L2262-2266 _private method_ `private void StepCollectReferences()`
- L2268-2301 _private method_ `private void StepLinkModules()`
- L2303-2316 _private method_ `private void ResolveAllHeaders(UhtResolvePhase resolvePhase)`
- L2318-2328 _private method_ `private void TryHeader(Action<UhtHeaderFile> action, UhtHeaderFile headerFile)`
- L2335 _private field_ `private static readonly HashSet<string> s_reservedNames = ["none"]` — Collection of reserved names
- L2340 _private field_ `private UhtSymbolTable _sourceNameSymbolTable = new(0)` — Symbol table for names as they appear in the C++ source. This is case sensitive
- L2345 _private field_ `private UhtSymbolTable _engineNameSymbolTable = new(0)` — Symbol table for the engine names derived from the source name. This is case insensitive
- L2350 _private field_ `private bool _symbolTablePopulated = false` — If true, the symbol tables have been created following parsing
- L2357-2378 _public method_ `public UhtEnum? FindRegularEnumValue(string name)` — Given the name of a regular enum value, return the enum type
- L2389-2399 _public method_ `public UhtType? FindType(UhtType? startingType, UhtFindOptions options, string name, IUhtMessageSite? messageSite = null, int lineNumber = -1)` — Find the given type in the type hierarchy
- L2409-2419 _public method_ `public UhtType? FindType(UhtType? startingType, UhtFindOptions options, ref UhtToken name, IUhtMessageSite? messageSite = null)` — Find the given type in the type hierarchy
- L2430-2457 _public method_ `public UhtType? FindType(UhtType? startingType, UhtFindOptions options, UhtTokenList identifiers, IUhtMessageSite? messageSite = null, int lineNumber = -1)` — Find the given type in the type hierarchy
- L2468-2493 _public method_ `public UhtType? FindType(UhtType? startingType, UhtFindOptions options, UhtToken[] identifiers, IUhtMessageSite? messageSite = null, int lineNumber = -1)` — Find the given type in the type hierarchy
- L2503-2543 _private method_ `private UhtType? FindTypeTwoNamesInternal(UhtType? startingType, UhtFindOptions options, string firstName, string secondName)` — Find the given type in the type hierarchy
- L2552-2580 _public method_ `public UhtType? FindTypeInternal(UhtType? startingType, UhtFindOptions options, string name)` — Find the given type in the type hierarchy
- L2586-2608 _private method_ `private void ValidateFindOptions(UhtFindOptions options)` — Verify that the options are valid. Will also check to make sure the symbol table has been populated.
- L2617-2646 _private method_ `private static void FindTypeError(IUhtMessageSite messageSite, int lineNumber, UhtFindOptions options, string name)` — Generate an error message for when a given symbol wasn't found. The text will contain the list of types that the symbol must be
- L2655-2662 _public method_ `public void ReplaceTypeInSymbolTable(UhtType oldType, UhtType newType)` — Given an existing and a new instance, replace the given type in the symbol table. This is used by the property resolution system to replace properties created during the parsing phase that couldn't be resoled until after all headers are parsed.
- L2668-2675 _public method_ `public void HideTypeInSymbolTable(UhtType typeToHide)` — Hide the given type in the symbol table
- L2677-2695 _private method_ `private void PopulateSymbolTable()`
- L2697-2772 _private method_ `private void AddTypeToSymbolTable(UhtType type)`
- L2783-2824 _private method_ `private void TopologicalHeaderVisit(List<TopologicalState> states, UhtHeaderFile visit, List<UhtHeaderFile> headerStack)`
- L2826-2849 _private method_ `private void TopologicalSortHeaderFiles()`
- L2851-2860 _private method_ `private void TopologicalStructVisitChildren(List<TopologicalState> states, UhtHeaderFile visit, List<UhtStruct> structStack)`
- L2862-2871 _private method_ `private void TopologicalStructVisitChildren(List<TopologicalState> states, UhtType visit, List<UhtStruct> structStack)`
- L2873-2925 _private method_ `private void TopologicalStructVisit(List<TopologicalState> states, UhtStruct visit, List<UhtStruct> structStack)`
- L2927-2946 _private method_ `private void RecursiveStructCheck()`
- L2950 _private field_ `private readonly HashSet<UhtScriptStruct> _scriptStructsValidForNet = []`
- L2960-3003 _public method_ `public bool ValidateScriptStructOkForNet(UhtProperty referencingProperty, UhtScriptStruct referencedScriptStruct)` — Validate that the given referenced script structure is valid for network operations. If the structure is valid, then the result will be cached. It not valid, errors will be generated each time the structure is referenced.
- L3013-3016 _public method_ `public void SetExporterStatus(string name, bool enabled)` — Enable/Disable an exporter. This overrides the default state of the exporter.
- L3024-3074 _public method_ `public bool IsPluginEnabled(string pluginName, bool includeTargetCheck)` — Test to see if the given exporter plugin is enabled.
- L3076-3145 _private method_ `private void StepExport()`
- L3154-3157 _public method_ `public bool IsIncompleteReturn(UhtProperty? property)` — Test to see if the given property is an incomplete return type

#### struct `EpicGames.UHT.Utils.UhtSession.EnumAndValue`  
`private struct EnumAndValue`  
_private; L671-675_
- desc: Pair that represents a specific value for an enumeration
- L673 _public property_ `public UhtEnum Enum { get; set; }`
- L674 _public property_ `public long Value { get; set; }`

#### class `EpicGames.UHT.Utils.UhtSession.TypeCounter`  
`private sealed class TypeCounter`  
_private; L1170-1191_
- desc: Helper class for returning a sequence of auto-incrementing indices
- L1176 _private field_ `private int _count = 0` — Current number of types
- L1182-1185 _public method_ `public int GetNext()` — Get the next type index
- L1190 _public property_ `public int Count => ...` — The number of times GetNext was called.

#### enum `EpicGames.UHT.Utils.UhtSession.TopologicalState`  
`private enum TopologicalState`  
_private; L2776-2781_
- L2778 _public* enumerator_ `Unmarked`
- L2779 _public* enumerator_ `Temporary`
- L2780 _public* enumerator_ `Permanent`

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtStringBuilderExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtStringBuilderExtensions`  
`static class UhtStringBuilderExtensions`  
_internal*; L12-421_
- L17 _public field_ `public static StringView TabsString = new(new string('\t', 128))` — String of tabs used to generate code with proper indentation
- L22 _public field_ `public static StringView SpacesString = new(new string(' ', 128))` — String of spaces used to generate code with proper indentation
- L31-42 _public method_ `public static StringBuilder AppendTabs(this StringBuilder builder, int tabs)` — Append tabs to the builder
- L51-62 _public method_ `public static StringBuilder AppendSpaces(this StringBuilder builder, int spaces)` — Append spaces to the builder
- L72-79 _public method_ `public static StringBuilder AppendEach<T>(this StringBuilder builder, IReadOnlyCollection<T> items, Action<StringBuilder, T> transform)` — Append a list of items, transforming each into a StringBuilder append operation
- L91-104 _public method_ `public static StringBuilder AppendEach<T>(this StringBuilder builder, IReadOnlyCollection<T> items, Action<StringBuilder> prefix, Action<StringBuilder, T> transform, Action<StringBuilder> suffix)` — Optionally append a list of items with a prefix and suffix. If the list is empty, the prefix and suffix are also omitted
- L114-117 _public method_ `public static StringBuilder AppendArrayView(this StringBuilder builder, UhtCppIdentifier identifier, int tabs, string? endl)` — Append an array view construction expression for the given variable
- L126-141 _public method_ `public static StringBuilder AppendUTF8LiteralString(this StringBuilder builder, bool useText, string? text)` — Append the given text as a UTF8 encoded string
- L149-160 _public method_ `public static StringBuilder AppendUTF8LiteralString(this StringBuilder builder, string? text)` — Append the given text as a UTF8 encoded string
- L168-276 _public method_ `public static StringBuilder AppendUTF8LiteralString(this StringBuilder builder, StringView text)` — Append the given text as a UTF8 encoded string
- L284-313 _public method_ `public static StringBuilder AppendEscapedUtf32(this StringBuilder builder, ulong c)` — Encode a single UTF32 value as UTF8 characters
- L322-325 _public method_ `public static StringBuilder AppendClassSourceNameOrInterfaceName(this StringBuilder builder, UhtClass classObj)` — Append the given name of the class but always encode interfaces as the native interface name (i.e. "I...")
- L334-348 _public method_ `public static StringBuilder AppendClassSourceNameOrInterfaceProxyName(this StringBuilder builder, UhtClass classObj)` — Append the given name of the class but always encode interfaces as the native interface proxy name (i.e. "I...")
- L356-420 _public method_ `public static StringBuilder AppendEncodedVerseName(this StringBuilder builder, ReadOnlySpan<char> name)` — Given a verse name, encode it so it can be represented as an FName

#### class `EpicGames.UHT.Utils.StringBuilderCache`  
`public class StringBuilderCache`  
_public; L426-500_
- desc: Provides a cache of StringBuilders
- L432 _public field_ `public static readonly StringBuilderCache Big = new(256, 256 * 1024)` — Cache of StringBuilders with large initial buffer sizes
- L437 _public field_ `public static readonly StringBuilderCache Small = new(256, 1 * 1024)` — Cache of StringBuilders with small initial buffer sizes
- L442 _private field_ `private readonly int _capacity` — Capacity of the cache
- L448 _private field_ `private readonly int _initialBufferSize` — Initial buffer size for new StringBuilders. Resetting StringBuilders might result in the initial chunk size being smaller.
- L453 _private field_ `private readonly Stack<StringBuilder> _stack` — Stack of cached StringBuilders
- L460-465 _public ctor_ `public StringBuilderCache(int capacity, int initialBufferSize)` — Create a new StringBuilder cache
- L471-482 _public method_ `public StringBuilder Borrow()` — Borrow a StringBuilder from the cache.
- L488-499 _public method_ `public void Return(StringBuilder builder)` — Return a StringBuilder to the cache

#### struct `EpicGames.UHT.Utils.BorrowStringBuilder`  
`public readonly struct BorrowStringBuilder : IDisposable`  
_public; L506-536_
- inherits: `IDisposable`
- desc: Structure to automate the borrowing and returning of a StringBuilder. Use some form of a "using" pattern.
- L512 _private property_ `private StringBuilderCache Cache { get; }` — Owning cache
- L517 _public property_ `public StringBuilder StringBuilder { get; }` — Borrowed string builder
- L523-527 _public ctor_ `public BorrowStringBuilder(StringBuilderCache cache)` — Borrow a string builder from the given cache
- L532-535 _public method_ `public void Dispose()` — Return the string builder to the cache

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtStringBuilderMetaDataExtensions.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtStringBuilderMetaDataExtensions`  
`static class UhtStringBuilderMetaDataExtensions`  
_internal*; L13-147_
- L18 _private field_ `private static readonly HashSet<string> s_hiddenMetaDataNames = new([UhtNames.Comment, UhtNames.ToolTip], StringComparer.OrdinalIgnoreCase)` — Names of meta data entries that will not appear in shipping builds for game code
- L29-36 _public method_ `public static StringBuilder AppendMetaDataArrayView(this StringBuilder builder, UhtMetaData metaData, UhtCppIdentifier identifier, int tabs, string endl)` — Append an array view construction expression for metadata if the metadata collection is not empty.
- L45-48 _public method_ `public static StringBuilder AppendMetaDataParams(this StringBuilder builder, UhtType type, UhtCppIdentifier identifier)` — Append the meta data parameters. This is intended to be used as arguments to a function call.
- L57-67 _public method_ `public static StringBuilder AppendMetaDataParams(this StringBuilder builder, UhtMetaData? metaData, UhtCppIdentifier identifier)` — Append the meta data parameters. This is intended to be used as arguments to a function call.
- L77-94 _public method_ `public static StringBuilder AppendMetaData(this StringBuilder builder, UhtType type, UhtCppIdentifier identifier, int tabs)` — Append the metadata definition, i.e. a definition for a array of structures containing name/value string pairs.
- L96-117 _private method_ `private static StringBuilder AppendMetaData(this StringBuilder builder, UhtType type, UhtCppIdentifier identifier, string declType, int tabs)`
- L129-146 _public method_ `public static StringBuilder AppendConditionalMetaData(this StringBuilder builder, UhtType type, UhtCppIdentifier identifier, IUhtPropertyMemberContext? propertyContext, UhtUsedDefineScopes<UhtProperty>? properties, int tabs)` — Append a metadata definition for a type with properties (e.g. a class or struct)

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtSymbolTable.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtSymbolTable`  
`internal sealed class UhtSymbolTable`  
_internal; L14-428_
- desc: Symbol table
- L71 _private field_ `private int _casedCount = 0` — Number of unique cased symbol names.
- L76 _private field_ `private readonly Dictionary<string, Lookup> _casedDictionary = ...` — Case name lookup table that returns the symbol index and the case index
- L76 _private field_ `private readonly Dictionary< _casedDictionary = new(StringComparer.Ordinal)` — Case name lookup table that returns the symbol index and the case index
- L81 _private field_ `private readonly Dictionary<string, int> _caselessDictionary = ...` — Caseless name lookup table that returns the symbol index
- L81 _private field_ `private readonly Dictionary< _caselessDictionary = new(StringComparer.OrdinalIgnoreCase)` — Caseless name lookup table that returns the symbol index
- L86 _private field_ `private readonly Symbol[] _symbols` — Collection of symbols in the table
- L92-95 _public ctor_ `public UhtSymbolTable(int typeCount)` — Constructs a new symbol table.
- L102-123 _public method_ `public void Add(UhtType type, string name)` — Add a new type to the symbol table
- L134-148 _public method_ `public void Replace(UhtType oldType, UhtType newType, string name)` — Replace an entry in the symbol table. This is used during property resolution to replace the parser property (which could not resolve the property prior to the symbol table being created) with the fully resolved property.
- L156-170 _public method_ `public void Hide(UhtType typeToHide, string name)` — Hide the given type in the symbol table
- L179-186 _public method_ `public UhtType? FindCasedType(UhtType? startingType, UhtFindOptions options, string name)` — Lookup the given name using cased string compare.
- L195-202 _public method_ `public UhtType? FindCaselessType(UhtType? startingType, UhtFindOptions options, string name)` — Lookup the given name using caseless string compare.
- L211-259 _private method_ `private UhtType? FindType(UhtType? startingType, UhtFindOptions options, Lookup lookup)` — Lookup the given name.
- L268-321 _private method_ `private UhtType? FindTypeSuperChain(UhtType startingType, UhtFindOptions options, ref Lookup lookup)` — Lookup the given name using the super class/struct chain.
- L330-361 _private method_ `private UhtType? FindTypeOuterChain(UhtType startingType, UhtFindOptions options, ref Lookup lookup)` — Lookup the given name using the outer chain
- L370-380 _private method_ `private UhtType? FindSymbolChain(UhtType owner, UhtFindOptions options, ref Lookup lookup)` — Lookup the given name
- L389-400 _private method_ `private UhtType? FindSymbolChain(UhtHeaderFile header, UhtFindOptions options, ref Lookup lookup)` — Lookup the given name
- L408-414 _private method_ `private void AddExisting(UhtType type, int casedIndex, int symbolIndex)` — Add a new type to the given symbol chain
- L423-427 _private method_ `private bool IsMatch(UhtFindOptions options, int symbolIndex, int casedIndex)` — Test to see if the given symbol matches the options

#### struct `EpicGames.UHT.Utils.UhtSymbolTable.Lookup`  
`struct Lookup`  
_private*; L21-34_
- desc: Represents symbol name lookup chain start. Symbol chains are based on the caseless name.
- L27 _public property_ `public int SymbolIndex { get; set; }` — The type index of the symbol
- L33 _public property_ `public int CasedIndex { get; set; }` — When searching the caseless chain, the cased index is used to match the symbol based on the case named.

#### struct `EpicGames.UHT.Utils.UhtSymbolTable.Symbol`  
`struct Symbol`  
_private*; L39-66_
- desc: Entry in the symbol table
- L45 _public property_ `public UhtType Type { get; set; }` — The type associated with the symbol
- L50 _public property_ `public UhtFindOptions MatchOptions { get; set; }` — Mask of different find options which will match this symbol
- L55 _public property_ `public int CasedIndex { get; set; }` — The case lookup index for matching by case
- L60 _public property_ `public int NextIndex { get; set; }` — The next index in the symbol change based on cassless lookup
- L65 _public property_ `public int LastIndex { get; set; }` — The last index in the chain. This index is only used when the symbol entry is also acting as the list

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtTables.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtTableNames`  
`public static class UhtTableNames`  
_public; L21-102_
- desc: Defines all the table names for the standard UHT types
- L26 _public const_ `public const string ClassBase = "ClassBase"` — The class base table is common to UCLASS, UINTERFACE and native interfaces
- L31 _public const_ `public const string Class = "Class"` — Table for UCLASS
- L36 _public const_ `public const string Default = "Default"` — Default table applied to all other tables
- L41 _public const_ `public const string Enum = "Enum"` — Table for UENUM
- L46 _public const_ `public const string Field = "Field"` — Table for all types considered a UField
- L51 _public const_ `public const string Function = "Function"` — Table for all functions
- L56 _public const_ `public const string Global = "Global"` — Table for the global/file scope
- L61 _public const_ `public const string Interface = "Interface"` — Table for UINTERFACE
- L66 _public const_ `public const string NativeInterface = "NativeInterface"` — Table for interfaces
- L71 _public const_ `public const string Object = "Object"` — Table for all UObject types
- L76 _public const_ `public const string PropertyArgument = "PropertyArgument"` — Table for properties that are function arguments
- L81 _public const_ `public const string PropertyMember = "PropertyMember"` — Table for properties that are struct/class members
- L86 _public const_ `public const string ScriptStruct = "ScriptStruct"` — Table for USTRUCT
- L91 _public const_ `public const string Struct = "Struct"` — Table for all UStruct objects (structs, classes, and functions)
- L96 _public const_ `public const string VModule = "VModule"` — Table for VModules
- L101 _public const_ `public const string Partial = "Partial"` — Table for UPARTIAL

#### class `EpicGames.UHT.Utils.UhtLookupTableBase`  
`public class UhtLookupTableBase`  
_public; L107-175_
- desc: Base class for table lookup system.
- L112 _public property_ `public UhtLookupTableBase? ParentTable { get; set; }` — This table inherits entries for the given table
- L117 _public property_ `public string TableName { get; set; }` — Name of the table
- L122-126 _public property_ `public string UserName { get; set; }` — User facing name of the table
- L131 _public property_ `public bool Internal { get; set; }` — Check to see if the table is internal
- L136 _public property_ `public bool Implemented { get; set; }` — If true, this table has been implemented and not just created on demand by another table
- L141 _private field_ `private string _userName = String.Empty` — Internal version of the user name. If it hasn't been set, then the table name will be used
- L147-149 _public method_ `public virtual void Merge(UhtLookupTableBase baseTable)` — Merge the lookup table. Duplicates will be ignored.
- L159-174 _public method_ `public static string GetSuffixedName(Type classType, MethodInfo methodInfo, string? inName, string suffix)` — Given a method name, try to extract the entry name for a table

#### class `EpicGames.UHT.Utils.UhtLookupTable`  
`public class UhtLookupTable<TValue> : UhtLookupTableBase`  
_public; L181-230_
- inherits: `UhtLookupTableBase`
- desc: Lookup tables provide a method of associating actions with given C++ keyword or UE specifier
- L187 _private field_ `private readonly Dictionary<StringView, TValue> _lookup` — Lookup dictionary for the specifiers
- L187 _private field_ `private readonly Dictionary< _lookup` — Lookup dictionary for the specifiers
- L192-195 _public ctor_ `public UhtLookupTable(StringViewComparer comparer)` — Construct a new table
- L202-206 _public method_ `public UhtLookupTable<TValue> Add(string key, TValue value)` — Add the given value to the lookup table. It will throw an exception if it is a duplicate.
- L214-217 _public method_ `public bool TryGetValue(StringView key, [MaybeNullWhen(false)] out TValue value)` — Attempt to fetch the value associated with the key
- L223-229 _public method_ `public override void Merge(UhtLookupTableBase baseTable)` — Merge the lookup table. Duplicates will be ignored.

#### class `EpicGames.UHT.Utils.UhtLookupTables`  
`public class UhtLookupTables<TTable> where TTable : UhtLookupTableBase, new()`  
_public; L236-351_
- constraints: `where TTable : UhtLookupTableBase, new()`
- desc: A collection of lookup tables by name.
- L242 _public property_ `public Dictionary<string, TTable> Tables { get; }` — Collection of named tables
- L247 _public property_ `public string Name { get; set; }` — The name of the group of tables
- L253-256 _public ctor_ `public UhtLookupTables(string name)` — Create a new group of tables
- L263-272 _public method_ `public TTable Get(string tableName)` — Given a table name, return the table. If not found, a new one will be added with the given name.
- L282-293 _public method_ `public TTable Create(string tableName, string userName, string? parentTableName, bool tableIsInternal = false)` — Create a table with the given information. If the table already exists, it will be initialized with the given data.
- L300-350 _public method_ `public void Merge()` — Merge the contents of all parent tables into their children. This is done so that the parent chain need not be searched when looking for table entries.

#### class `EpicGames.UHT.Utils.UhtStandardTables`  
`public static class UhtStandardTables`  
_public; L356-422_
- desc: Bootstraps the standard UHT tables
- L380-398 _public method_ `public static void InitStandardTables(UhtTables tables)` — Create all of the standard scope tables.
- L409-421 _public method_ `public static void CreateTables(UhtTables tables, string tableName, string tableUserName, EUhtCreateTablesFlags createTables, string? parentTableName, bool tableIsInternal = false)` — Creates a series of tables given the supplied setup

#### enum `EpicGames.UHT.Utils.UhtStandardTables.EUhtCreateTablesFlags`  
`public enum EUhtCreateTablesFlags`  
_public; L363-374_
- attrs: `[Flags]`
- desc: Enumeration that specifies if the table is a specifier and/or keyword table
- L368 _public* enumerator_ `Keyword = 1 << 0` — A keyword table will be created
- L373 _public* enumerator_ `Specifiers = 1 << 1` — A specifier table will be created

#### class `EpicGames.UHT.Utils.UnrealHeaderToolAttribute`  
`public sealed class UnrealHeaderToolAttribute : Attribute`  
_public; L428-436_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: This attribute must be applied to any class that contains other UHT attributes.
- L435 _public property_ `public string InitMethod { get; set; }` — If specified, this method will be invoked once during the scan for attributes. It can be used to perform some one time initialization.

#### class `EpicGames.UHT.Utils.UhtTables`  
`public class UhtTables`  
_public; L464-747_
- desc: UnrealHeaderTool avoids hard coding any table contents by using attributes to add entries to the tables. There are two basic styles of tables in UHT. The first style is just a simple association of a string and an attribute. For example, the engine class table is just a collection of all the engine class names supported by the engine. The second style is a table of tables. Depending on the context (i.e. is a "class" or "function" being parsed), attributes will "extend" a given table adding an entry to that table and every table the derives from that table. For example, the Keywords table will add "private" to the "ClassBase" table. Since the "Class", "Interface", and "NativeInterface" tables derive from "ClassBase", all of those tables will contain the keyword "private". See UhtTables.cs for a list of table names and how they relate to each other. Tables are implemented in the following source files: UhtEngineClassTable.cs - Collection of all the engine class names. UhtKeywordTable.cs 
- L469 _public property_ `public UhtSpecifierTables SpecifierTables { get; }` — Collection of specifier tables
- L474 _public property_ `public UhtSpecifierValidatorTables SpecifierValidatorTables { get; }` — Collection of specifier validator tables
- L479 _public property_ `public UhtKeywordTables KeywordTables { get; }` — Collection of keyword tables
- L484 _public property_ `public UhtPropertyTypeTable PropertyTypeTable { get; }` — Collection of property types
- L489 _public property_ `public UhtStructDefaultValueTable StructDefaultValueTable { get; }` — Collection of structure default values
- L494 _public property_ `public UhtEngineClassTable EngineClassTable { get; }` — Collection of engine class types
- L499 _public property_ `public UhtExporterTable ExporterTable { get; }` — Collection of exporters
- L504 _public property_ `public UhtLocTextDefaultValueTable LocTextDefaultValueTable { get; }` — Collection loc text default values
- L509 _public property_ `public UhtCodeGeneratorInjectorTable CodeGeneratorInjectorTable { get; }` — Collection of methods used to inject code into the code generator
- L514 _public property_ `public IReadOnlyList<Type> KnownTypes => ...` — Collection of all known UhtTypes
- L515 _private field_ `private readonly List<Type> _knownTypes = []`
- L520-525 _public ctor_ `public UhtTables()` — Construct a new table collection
- L531-538 _public method_ `public void AddPlugins(IEnumerable<string> pluginAssembliesFilePaths)` — Add a collection of plugin assembly file paths
- L545-565 _public method_ `public static bool IsUhtPlugin(string assemblyFilePath)` — Check to see if the assembly is a UHT plugin
- L572-580 _public method_ `public static Assembly? LoadAssembly(string assemblyFilePath)` — Load the given assembly from the file path
- L587-601 _private method_ `private static Assembly? FindAssemblyByName(string? name)` — Locate the assembly by name
- L607-620 _private method_ `private void CheckForAttributes(Assembly? assembly)` — Check for UHT attributes on all types in the given assembly
- L627-652 _public method_ `public void ValidateCacheableTypes(ILogger logger)` — Verify that all the known types support caching
- L658-675 _private method_ `private void CheckForAttributes(Type type)` — For the given type, look for any table related attributes
- L677-687 _private method_ `private void PerformPostInitialization()`
- L689-746 _private method_ `private void HandleUnrealHeaderToolAttribute(Type type, UnrealHeaderToolAttribute parserAttribute)`

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtTypeTokens.cs` (EpicGames.UHT)


#### struct `EpicGames.UHT.Utils.UhtTypeSegment`  
`public struct UhtTypeSegment`  
_public; L15-75_
- desc: Represents the decoded tokens for part of a type definition
- L21 _public property_ `public int Start { get; set; }` — Starting token index of this type
- L26 _public property_ `public int End { get; set; }` — Ending token index of this type (non-inclusive)
- L31 _public property_ `public int TypeStart { get; set; }` — Starting token index of the type
- L36 _public property_ `public int TypeEnd { get; set; }` — Ending token index of the type
- L41 _public property_ `public UhtFindOptions FindFilter { get; set; }` — Set if the type beings with 'class', 'struct', or 'enum'
- L46-48 _public ctor_ `public UhtTypeSegment()` — Construct a new type segment
- L54-61 _public ctor_ `public UhtTypeSegment(UhtInputCacheReader reader)` — Construct a type from the cache
- L67-74 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write the output type

#### struct `EpicGames.UHT.Utils.UhtTypeTokens`  
`public struct UhtTypeTokens`  
_public; L80-269_
- desc: Information about a parsed type
- L82 _private field_ `private readonly Memory<UhtTypeSegment> _segments`
- L87 _public property_ `public ReadOnlyMemory<UhtToken> AllTokens { get; set; }` — Collection of tokens that describe the type
- L92 _public property_ `public readonly ReadOnlyMemory<UhtTypeSegment> Segments => ...` — Collection of type segments
- L94-98 _private ctor_ `private UhtTypeTokens(ReadOnlyMemory<UhtToken> typeTokens, Memory<UhtTypeSegment> segments)`
- L105-112 _public method_ `public static UhtTypeTokens Gather(IUhtTokenReader tokenReader)` — Gather a type definition from the given token reader
- L121-136 _public method_ `public UhtToken ExtractTrailingIdentifier(IUhtMessageSite messageSite, UhtPropertySettings propertySettings)` — Extract the trailing token from the type string since it is the property/function name
- L139-142 _public method_ `public override readonly string ToString()` — (inheritdoc)
- L149-154 _public method_ `public static string ToString(ReadOnlySpan<UhtToken> tokens)` — Convert the token span to a string
- L156-268 _private method_ `private static int Gather(List<UhtToken> typeTokens, List<UhtTypeSegment> segments, IUhtTokenReader tokenReader, int depth)`

#### struct `EpicGames.UHT.Utils.UhtTypeTokensRef`  
`public readonly struct UhtTypeTokensRef`  
_public; L274-420_
- desc: Reference to a token segment
- L279 _public property_ `public readonly ReadOnlyMemory<UhtToken> AllTokens { get; }` — Collection of tokens that describe the type
- L284 _public property_ `public readonly ReadOnlyMemory<UhtTypeSegment> Segments { get; }` — Collection of type segments
- L290 _public property_ `public readonly int DeclarationSegmentIndex { get; }` — Index of the segment that contains only the declaration used to generate the property. This will not include such things as TPtr which themselves do not generate a property.
- L296 _public property_ `public readonly int FullDeclarationSegmentIndex { get; }` — Index of the full segment that includes not only the declaration used to generate the property, but any templates such as TPtr that wrap the property declaration.
- L302 _public property_ `public readonly UhtTypeSegment DeclarationSegment => ...` — The segment that contains only the declaration used to generate the property. This will not include such things as TPtr which themselves do not generate a property.
- L308 _public property_ `public readonly UhtTypeSegment FullDeclarationSegment => ...` — the full segment that includes not only the declaration used to generate the property, but any templates such as TPtr that wrap the property declaration.
- L315-323 _public property_ `public readonly ReadOnlyMemory<UhtToken> TypeTokens { get; }` — The tokens that represent the property's basic type. Example: "const USomeType*" has type tokens of "USomeType" Example: "const verse::my_verse_type*" has type tokens of "verse::my_verse_type"
- L328-336 _public property_ `public readonly ReadOnlyMemory<UhtToken> DeclarationTokens { get; }` — The collection of tokens that define this type
- L341-349 _public property_ `public readonly ReadOnlyMemory<UhtToken> FullDeclarationTokens { get; }` — The collection of tokens that define this type
- L356-362 _public ctor_ `public UhtTypeTokensRef(UhtTypeTokens typeTokens, int declarationSegmentIndex)` — Construct a new instance of a type tokens
- L369-375 _public ctor_ `public UhtTypeTokensRef(UhtTypeTokensRef typeTokens, int declarationSegmentIndex)` — Construct a new instance of a type tokens
- L383-389 _public ctor_ `public UhtTypeTokensRef(UhtTypeTokensRef typeTokens, int declarationSegmentIndex, int fullDeclarationSegmentIndex)` — Construct a new instance of a type tokens
- L397-403 _public ctor_ `public UhtTypeTokensRef(ReadOnlyMemory<UhtToken> allTokens, ReadOnlyMemory<UhtTypeSegment> segments, UhtInputCacheReader reader)` — Construct a new instance of a type tokens
- L409-413 _public method_ `public void Write(UhtInputCacheWriter writer)` — Write the output type
- L416-419 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### class `EpicGames.UHT.Utils.UhtTypeTokensStringBuilderExtensions`  
`public static class UhtTypeTokensStringBuilderExtensions`  
_public; L425-471_
- desc: Helper methods to append type tokens to a string builder
- L434-459 _public method_ `public static StringBuilder AppendTokens(this StringBuilder builder, ReadOnlySpan<UhtToken> tokens)` — Append the type tokens to the given builder
- L467-470 _public method_ `public static StringBuilder AppendTokens(this StringBuilder builder, ReadOnlyMemory<UhtToken> tokens)` — Append the type tokens to the given builder

### `Source/Programs/Shared/EpicGames.UHT/Utils/UhtUtilities.cs` (EpicGames.UHT)


#### class `EpicGames.UHT.Utils.UhtListExtensions`  
`public static class UhtListExtensions`  
_public; L19-90_
- desc: Extensions to List that provides some uniqueness support to list elements
- L28-36 _public method_ `public static bool AddUnique(this List<string> container, string value)` — Add the given value if it isn't already contained within the list
- L43-52 _public method_ `public static void AddUniqueRange(this List<string> container, IEnumerable<StringView>? values)` — Add the given values if they aren't already contained within the list
- L60-73 _public method_ `public static bool RemoveSwap(this List<string> container, string value)` — Remove the given value but swap the last entry into the eliminated slot
- L80-89 _public method_ `public static void RemoveSwapRange(this List<string> container, IEnumerable<StringView>? values)` — Remove a range of values from a container using swapping

#### struct `EpicGames.UHT.Utils.UhtEngineNameParts`  
`public struct UhtEngineNameParts`  
_public; L96-113_
- desc: UnrealEngine names often differ from the names in the source file. The following structure represents the different parts of the name
- L102 _public property_ `public StringView Prefix { get; set; }` — Any prefix removed from the source name to create the engine name
- L107 _public property_ `public StringView EngineName { get; set; }` — The name to be used by the Unreal Engine.
- L112 _public property_ `public bool IsDeprecated { get; set; }` — The name contained the "DEPRECATED" text which has been removed from the engine name

#### class `EpicGames.UHT.Utils.UhtUtilities`  
`public static class UhtUtilities`  
_public; L118-286_
- desc: Assorted utility functions
- L127-130 _private method_ `private static DateTime LatestDateTime(DateTime lhs, DateTime rhs)` — Return the latest of two date/times
- L137-152 _public method_ `public static DateTime GetLatestAssemblyDateTime(IEnumerable<string>? plugins)` — Return the latest date time between UBT and UHT assembly and all plugin assemblies
- L161-196 _public method_ `public static string MergeTypeNames(IEnumerable<string> typeNames, string andOr, bool quote = false)` — Given a collection of names, return a string containing the text of those names concatenated.
- L203-234 _public method_ `public static UhtEngineNameParts GetEngineNameParts(StringView sourceName)` — Split the given source name into the engine name parts
- L236 _private field_ `private static readonly SearchValues<char> s_pathNameDelimiters = SearchValues.Create(['.', ':'])`
- L245-273 _public method_ `public static bool IsValidLongPathName(StringView name)` — Returns whether the given string is a valid long path name for an object. See FSoftObjectPath::SetPath for reference. e.g. MyClass is a short name, but /Script/MyModule.MyClass is a full path name.
- L282-285 _public method_ `public static bool IsValidLongPathName(string name)` — Returns whether the given string is a valid long path name for an object. See FSoftObjectPath::SetPath for reference. e.g. MyClass is a short name, but /Script/MyModule.MyClass is a full path name.

#### class `EpicGames.UHT.Utils.StringViewBuilder`  
`public class StringViewBuilder`  
_public; L292-393_
- desc: String builder class that has support for StringView so that if a single instance of a StringView is appended, it is returned.
- L298 _private field_ `private StringView _stringView = new()` — When only a string view has been appended, this references that StringView
- L303 _private field_ `private StringBuilder? _stringBuilder = null` — Represents more complex data being appended
- L308 _private field_ `private bool _useStringBuilder = false` — Set to true when the builder has switched to a StringBuilder (NOTE: This can probably be removed)
- L313-326 _public property_ `public int Length { get; }` — The length of the appended data
- L332-335 _public method_ `public StringView ToStringView()` — Return the appended data as a StringView
- L341-344 _public method_ `public override string ToString()` — Return the appended data as a string
- L351-367 _public method_ `public StringViewBuilder Append(StringView text)` — Append a StringView
- L374-379 _public method_ `public StringViewBuilder Append(char c)` — Append a character
- L384-392 _private method_ `private void SwitchToStringBuilder()` — If not already done, switch the builder to using a StringBuilder

#### struct `EpicGames.UHT.Utils.Crc`  
`internal readonly struct Crc`  
_internal; L398-474_
- desc: Helper structure used to compute UE style CRC values
- L400 _private field_ `private static readonly uint[] s_table = [ 0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db7 ...`
- L419 _private field_ `private static readonly uint[] s_striHashTable = [ 0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9, 0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005, 0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61, 0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD, 0x4C11 ...`
- L445-454 _public method_ `public static uint StriHash(string text, uint crc = 0)` — Compute a crc from the given string and an initial CRC value.
- L462-473 _public method_ `public static uint Compute(byte[] text, uint crc = 0)` — Compute a crc from the given string and an initial CRC value

#### struct `EpicGames.UHT.Utils.VerseNameMangling`  
`internal readonly struct VerseNameMangling`  
_internal; L479-519_
- desc: Helper structure for verse name mangling
- L481 _private const_ `private const string MangledPrefix = "__verse_0x"`
- L482 _private field_ `private static readonly string[] s_internalNames = [MangledPrefix, "RetVal", "_RetVal", "$TEMP", "_Self"]`
- L484-487 _private method_ `private static bool ShouldMangleCasedName(string name)`
- L494-506 _public method_ `public static (bool WasMangled, string Result) MangleCasedName(string name)` — If required, generate the mangled name for a cased name
- L513-518 _public method_ `public static string EncodeVerseName(string name)` — Given a verse name, encode it
