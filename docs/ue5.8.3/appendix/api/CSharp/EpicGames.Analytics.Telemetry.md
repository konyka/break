# CSharp / EpicGames.Analytics.Telemetry

- project root: `Source/Programs/Shared/EpicGames.Analytics.Telemetry`
- files: 6; symbols: 31
- symbol kinds: class=4, const=1, ctor=5, field=3, method=10, property=6, record=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Analytics.Telemetry/AbstractTelemetryRecord.cs` (EpicGames.Analytics.Telemetry)


#### record `EpicGames.Analytics.AbstractTelemetryRecord`  
`public abstract record AbstractTelemetryRecord`  
_public; L12-102_
- desc: Describes the base elements required for telemetry.
- L19 _public const_ `public const string TelemetryTimestampColumnName = "telemetry_timestamp"` — Canonical column name for TelemetryTimestamp. Read-side query code references this constant so consumer plugins (StructuredAnalytics, PerformanceTrends, ...) never carry a string literal that could drift from the wire format.
- L29 _public property_ `public string EventName { get; init; }` — attrs: `[Column("event_name")]` — The telemetry event name.
- L35 _public property_ `public int SchemaVersion { get; init; }` — attrs: `[Column("schema_version")]` — The schema version of the telemetry.
- L41 _public property_ `public DateTime TelemetryTimestamp { get; init; }` — attrs: `[Column(TelemetryTimestampColumnName)]` — When the telemetry record was created. Stamped to DateTime.UtcNow by the constructor so any record instance implicitly carries a value; producers can override via record-init for backfill / replay scenarios. Distinct from datarouter's zz_received_timestamp column, which captures the upstream pipeline's receive time.
- L55-60 _public method_ `public Hashtable ToHashtable()` — Produces a hashtable representation of the telemetry record.
- L70-75 _protected ctor_ `protected AbstractTelemetryRecord()` — No arg constructor for ORM construction.
- L82-87 _protected ctor_ `protected AbstractTelemetryRecord(string eventName, int schemaVersion)` — Constructor.
- L94-99 _protected method_ `protected virtual void WriteProperties(Hashtable hashtable)` — Template pattern method that appends serializable properties to the in hashtable.

### `Source/Programs/Shared/EpicGames.Analytics.Telemetry/AnalyticsTableGenAttribute.cs` (EpicGames.Analytics.Telemetry)


#### class `EpicGames.Analytics.Telemetry.AnalyticsTableGenAttribute`  
`public sealed class AnalyticsTableGenAttribute : System.Attribute`  
_public; L11-11_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct)]`
- inherits: `System.Attribute`
- desc: Attribute to annoatate that table generation should run on the type.

### `Source/Programs/Shared/EpicGames.Analytics.Telemetry/AnalyticsTelemetryHelpers.cs` (EpicGames.Analytics.Telemetry)


#### class `EpicGames.Analytics.AnalyticsTelemetryHelpers`  
`public static class AnalyticsTelemetryHelpers`  
_public; L10-54_
- desc: Common utilities for working with telemetry records.
- L19-26 _public method_ `public static Hashtable MergeLeftCopy(Hashtable left, Hashtable right, bool overrideTarget = true)` — Merges the right hashtable into the left, without mutating the left hashtable.
- L35-53 _public method_ `public static Hashtable MergeLeft(Hashtable left, Hashtable right, bool overrideTarget = true)` — Merges the right hashtable into the left.

### `Source/Programs/Shared/EpicGames.Analytics.Telemetry/ColumnValidator.cs` (EpicGames.Analytics.Telemetry)


#### class `EpicGames.Analytics.ColumnValidator`  
`public static class ColumnValidator<T>`  
_public; L16-148_
- desc: Utility class used to validate the payload contents against specific record types, ensuring the presence of ColumnAttribute within different payload types.
- L18 _private field_ `private static readonly Lock s_initLock = new()`
- L19 _private field_ `private static HashSet<string>? s_columnKeys = null`
- L20 _private field_ `private static HashSet<string>? s_propertyKeys = null`
- L22-62 _private method_ `private static void InitializeKeys()`
- L66-86 _private method_ `private static HashSet<string> ReplicateAsHashSet(Hashtable source, bool fuzzyReplication)`
- L88-103 _private method_ `private static bool HasCompleteKeySet(Hashtable source, HashSet<string> comparisonKeys, bool fuzzyMatch, List<string>? missingColumns)`
- L116-126 _public method_ `public static bool HasCompleteColumnSet(Hashtable source, List<string>? missingColumns)` — Validates whether an source payload of Hashtable type contains all the columns.
- L138-147 _public method_ `public static bool HasCompletePropertySet(Hashtable source, bool fuzzyMatch, List<string>? missingColumns)` — Validates whether an source payload of Hashtable type contains all the columns.

### `Source/Programs/Shared/EpicGames.Analytics.Telemetry/CorrelatableTelemetryRecord.cs` (EpicGames.Analytics.Telemetry)


#### record `EpicGames.Analytics.CorrelatableTelemetryRecord`  
`public record CorrelatableTelemetryRecord : AbstractTelemetryRecord`  
_public; L12-72_
- inherits: `AbstractTelemetryRecord`
- desc: Record that describes a telemetry that can be correlated inter and intra session.
- L20 _public property_ `public string? SessionId { get; init; }` — attrs: `[Column("session_id")]` — A unique id used to correlate telemetry within a session.
- L26 _public property_ `public string? SessionLabel { get; init; }` — attrs: `[Column("session_label")]` — A label used to correlate telemetry across sessions.
- L36 _protected ctor_ `protected CorrelatableTelemetryRecord() : base()` — No arg constructor for ORM construction.
- L45-49 _public ctor_ `public CorrelatableTelemetryRecord(string eventName, int schemaVersion, string? sessionId, string? sessionLabel) : base(eventName, schemaVersion)` — Constructor for correlatable telemetry.
- L56-69 _protected method_ `protected override void WriteProperties(Hashtable hashtable)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Analytics.Telemetry/TelemetryEventAttribute.cs` (EpicGames.Analytics.Telemetry)


#### class `EpicGames.Analytics.Telemetry.TelemetryEventAttribute`  
`public sealed class TelemetryEventAttribute : Attribute`  
_public; L13-28_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, AllowMultiple = false, Inherited = false)]`
- inherits: `Attribute`
- desc: Attribute to declare the event name for a telemetry record type. This allows mapping from event names (e.g., "State.JobSummary") to their corresponding types for schema resolution when processing JSON telemetry events.
- L18 _public property_ `public string EventName { get; }` — The event name for this telemetry type (e.g., "State.JobSummary")
- L24-27 _public ctor_ `public TelemetryEventAttribute(string eventName)` — Constructor
