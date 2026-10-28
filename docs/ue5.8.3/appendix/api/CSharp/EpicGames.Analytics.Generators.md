# CSharp / EpicGames.Analytics.Generators

- project root: `Source/Programs/Shared/EpicGames.Analytics.Generators`
- files: 2; symbols: 24
- symbol kinds: class=3, const=3, ctor=1, field=6, method=9, property=1, record struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Analytics.Generators/AnalyticsSourceGenHelper.cs` (EpicGames.Analytics.Generators)


#### class `EpicGames.Analytics.Generators.AnalyticsSourceGenHelper`  
`public static class AnalyticsSourceGenHelper`  
_public; L11-98_
- desc: General source gen helper associated with analytics tables.
- L16 _public const_ `public const string AnalyticsTableGenNamespace = "EpicGames.Analytics.Generated"` — Analytics Generator namespace.
- L21 _public const_ `public const string AnalyticsTableGenPrefix = "AnalyticsTableGen"` — Analytics Generator prefix used in generated files.
- L26 _public const_ `public const string AnalyticsTableGenSourcePrefix = "AGen"` — Shorthand prefix used in generated files.
- L32-52 _public method_ `public static string GenerateAnalyticsTableGenVersionFile()` — Generates the version file for the table gen.
- L59-97 _public method_ `public static string GenerateAnalyticsTable(AnalyticsTableToGenerate analyticstableToGenerate)` — Constructs a analytics table source file from the provided object.

### `Source/Programs/Shared/EpicGames.Analytics.Generators/AnalyticsTableGenerator.cs` (EpicGames.Analytics.Generators)


#### record struct `EpicGames.Analytics.Generators.AnalyticsTableToGenerate`  
`public readonly record struct AnalyticsTableToGenerate`  
_public; L17-53_
- desc: DTO that describes a analytics table.
- L22 _public field_ `public readonly string Name` — The name of the telemetry record.
- L27 _public field_ `public readonly string Schema` — The schema/database name (e.g., "ingest").
- L32 _public field_ `public readonly string TableName` — The table name (e.g., "horde.state_job_summary").
- L37 _public field_ `public readonly List<Tuple<string, string>> ColumnsNames` — The column names.
- L37 _public field_ `public readonly List<Tuple< ColumnsNames` — The column names.
- L46-52 _public ctor_ `public AnalyticsTableToGenerate(string name, string schema, string tableName, List<Tuple<string, string>> propsValues)` — Constructor.

#### class `EpicGames.Analytics.Generators.AnalyticsTableGenerator`  
`public class AnalyticsTableGenerator : ISourceGenerator`  
_public; L59-248_
- attrs: `[Generator]`
- inherits: `ISourceGenerator`
- desc: Generator class.
- L62 _private field_ `private static readonly DiagnosticDescriptor s_descriptor = new(id: "HORDEATG01", title: "Unexpected Error", messageFormat: "Error for object: {0}", category: "Design", defaultSeverity: DiagnosticSeverity.Warning, isEnabledByDefault: true)`
- L66-69 _public method_ `public void Initialize(GeneratorInitializationContext context)` — (inheritdoc)
- L72-126 _public method_ `public void Execute(GeneratorExecutionContext context)` — (inheritdoc)
- L142-151 _private method_ `private static string? BuildFullNamespace(INamespaceSymbol? symbol)`
- L154-213 _private method_ `private static AnalyticsTableToGenerate? BuildAnalyticsTable(INamedTypeSymbol telemetrySymbol)`
- L215-234 _private method_ `private static IEnumerable<INamedTypeSymbol> GetAllNamedTypes(INamespaceSymbol ns)`
- L236-247 _private method_ `private static IEnumerable<INamedTypeSymbol> GetAllNestedTypes(INamedTypeSymbol type)`

#### class `EpicGames.Analytics.Generators.AnalyticsTableGenerator.SyntaxReceiver`  
`private class SyntaxReceiver : ISyntaxReceiver`  
_private; L128-139_
- inherits: `ISyntaxReceiver`
- L130 _public property_ `public List<TypeDeclarationSyntax> CandidateTypes { get; }`
- L132-138 _public method_ `public void OnVisitSyntaxNode(SyntaxNode syntaxNode)`
