# CSharp / EpicGames.Tracing

- project root: `Source/Programs/Shared/EpicGames.Tracing`
- files: 13; symbols: 293
- symbol kinds: class=26, const=22, ctor=26, field=57, interface=1, method=96, property=65
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.BinaryReaderExtensions`  
`public static class BinaryReaderExtensions`  
_public; L13-110_
- L15-24 _public method_ `public static byte[] ReadBytesStrict(this BinaryReader reader, int count)`
- L32-35 _internal method_ `internal static bool IsBitSet(byte value, int pos)` — Check if bit is set for a given byte
- L37-40 _internal method_ `internal static bool IsTwoByteUid(byte uidLow)`
- L42-45 _internal method_ `internal static byte GetHighByte(ushort a)`
- L47-50 _internal method_ `internal static byte GetLowByte(ushort a)`
- L52-55 _internal method_ `internal static ushort GetHighWord(uint a)`
- L57-60 _internal method_ `internal static ushort GetLowWord(uint a)`
- L62-65 _internal method_ `internal static ushort MakeShort(byte lowByte, byte highByte)`
- L67-80 _internal method_ `internal static ushort GetPackedUid(byte uidLow, byte uidHigh, out bool isTwoByteUidArg)`
- L82-95 _public method_ `public static ushort ReadPackedUid(this BinaryReader reader, out bool isTwoByteUid)`
- L97-104 _public method_ `public static void EnsureEntireStreamIsConsumed(this BinaryReader reader)`
- L106-109 _public method_ `public static bool IsEntireStreamConsumed(this BinaryReader reader)`

#### class `EpicGames.Tracing.UnrealInsights.BinaryWriterExtensions`  
`public static class BinaryWriterExtensions`  
_public; L112-137_
- L114-136 _public method_ `public static void WritePackedUid(this BinaryWriter writer, ushort uid)`

#### interface `EpicGames.Tracing.UnrealInsights.ITraceEvent`  
`public interface ITraceEvent`  
_public; L139-144_
- L141 _public* property_ `ushort Size { get; }`
- L142 _public* property_ `EventType Type { get; }`
- L143 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

#### class `EpicGames.Tracing.UnrealInsights.EnterScopeEvent`  
`public class EnterScopeEvent : ITraceEvent`  
_public; L146-151_
- inherits: `ITraceEvent`
- L148 _public property_ `public ushort Size => ...`
- L149 _public property_ `public EventType Type => ...`
- L150 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

#### class `EpicGames.Tracing.UnrealInsights.LeaveScopeEvent`  
`public class LeaveScopeEvent : ITraceEvent`  
_public; L153-158_
- inherits: `ITraceEvent`
- L155 _public property_ `public ushort Size => ...`
- L156 _public property_ `public EventType Type => ...`
- L157 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

#### class `EpicGames.Tracing.UnrealInsights.EnterScopeEventTimestamp`  
`public class EnterScopeEventTimestamp : ITraceEvent`  
_public; L160-186_
- inherits: `ITraceEvent`
- L162 _public property_ `public ushort Size => ...`
- L163 _public property_ `public EventType Type => ...`
- L164 _public property_ `public ulong Timestamp { get; }`
- L166-169 _public ctor_ `public EnterScopeEventTimestamp(ulong timestamp)`
- L171 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`
- L173-185 _public method_ `public static EnterScopeEventTimestamp Deserialize(BinaryReader reader)`

#### class `EpicGames.Tracing.UnrealInsights.LeaveScopeEventTimestamp`  
`public class LeaveScopeEventTimestamp : ITraceEvent`  
_public; L188-215_
- inherits: `ITraceEvent`
- L190 _public property_ `public ushort Size => ...`
- L191 _public property_ `public EventType Type => ...`
- L193 _private* field_ `readonly ulong _timestamp` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("CodeQuality", "IDE0052:Remove unread private members", Justification = "Serialize() unimplemented")]`
- L195-198 _public ctor_ `public LeaveScopeEventTimestamp(ulong timestamp)`
- L200 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`
- L202-214 _public method_ `public static LeaveScopeEventTimestamp Deserialize(BinaryReader reader)`

#### class `EpicGames.Tracing.UnrealInsights.TraceImportantEventHeader`  
`public class TraceImportantEventHeader`  
_public; L217-244_
- L219 _public property_ `public ushort Uid { get; }`
- L220 _public property_ `public ushort EventSize { get; }`
- L222 _public const_ `public const ushort HeaderSize = sizeof(ushort) + sizeof(ushort)`
- L224-231 _public ctor_ `public TraceImportantEventHeader(ushort uid, ushort eventSize)`
- L233-237 _public method_ `public void Serialize(BinaryWriter writer)`
- L239-243 _public method_ `public static TraceImportantEventHeader Deserialize(BinaryReader reader)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events/CpuProfiler.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.Events.CpuProfilerEventSpecEvent`  
`public class CpuProfilerEventSpecEvent : ITraceEvent`  
_public; L9-44_
- inherits: `ITraceEvent`
- L11 _public field_ `public static readonly EventType EventType = new(0, "CpuProfiler", "EventSpec", EventType.FlagImportant | EventType.FlagMaybeHasAux | EventType.FlagNoSync, [ new EventTypeField(0, 4, EventTypeField.TypeInt32, "Id"), new EventTypeField(4, 0, Even ...`
- L17 _public property_ `public ushort Size => ...`
- L18 _public property_ `public EventType Type => ...`
- L20 _public property_ `public uint Id { get; }`
- L21 _private* field_ `readonly string _name`
- L23 _private field_ `private readonly GenericEvent _genericEvent`
- L25-37 _public ctor_ `public CpuProfilerEventSpecEvent(uint id, string name)`
- L39-43 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

#### class `EpicGames.Tracing.UnrealInsights.Events.CpuProfilerEventBatchEvent`  
`public class CpuProfilerEventBatchEvent : ITraceEvent`  
_public; L46-67_
- inherits: `ITraceEvent`
- L48 _public field_ `public static readonly EventType EventType = new(0, "CpuProfiler", "EventBatch", EventType.FlagMaybeHasAux | EventType.FlagNoSync, [new EventTypeField(0, 0, EventTypeField.TypeArray, "Data")])`
- L51 _public property_ `public ushort Size => ...`
- L52 _public property_ `public EventType Type => ...`
- L54 _private* field_ `readonly GenericEvent _genericEvent`
- L56-60 _public ctor_ `public CpuProfilerEventBatchEvent(byte[] data)`
- L62-66 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

#### class `EpicGames.Tracing.UnrealInsights.Events.CpuProfilerScopeEvent`  
`public class CpuProfilerScopeEvent`  
_public; L69-87_
- L71 _public property_ `public ulong Timestamp { get; }`
- L72 _public property_ `public bool IsEnterScope { get; }`
- L73 _public property_ `public uint? SpecId { get; }`
- L75-80 _public ctor_ `public CpuProfilerScopeEvent(ulong timestamp, bool isEnterScope, uint? specId)`
- L82-86 _public method_ `public override string ToString()`

#### class `EpicGames.Tracing.UnrealInsights.Events.CpuProfilerSerializer`  
`public class CpuProfilerSerializer`  
_public; L92-193_
- desc: Stateful serializer that can serialize/deserialize the data argument in CpuProfiler.EventBatch events
- L94 _private field_ `private readonly ulong _cycleFrequency`
- L95 _public property_ `public List<CpuProfilerScopeEvent> ScopeEvents { get; }`
- L97-100 _public ctor_ `public CpuProfilerSerializer(ulong cycleFrequency)`
- L102-137 _public method_ `public void Read(byte[] eventBatchData)`
- L139-179 _public method_ `public List<byte[]> Write()`
- L181-185 _internal method_ `internal static ulong EncodeTimestamp(ulong timestamp, bool isScopeEnter)`
- L187-192 _internal method_ `internal static (ulong Timestamp, bool IsScopeEnter) DecodeTimestamp(ulong value)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events/Diagnostics.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.Events.DiagnosticsSession2Event`  
`public class DiagnosticsSession2Event : ITraceEvent`  
_public; L7-47_
- inherits: `ITraceEvent`
- L9 _public field_ `public static readonly EventType EventType = new(0, "Diagnostics", "Session2", EventType.FlagImportant | EventType.FlagMaybeHasAux | EventType.FlagNoSync, [ new EventTypeField(0, 0, EventTypeField.TypeAnsiString, "Platform"), new EventTypeField( ...`
- L21 _public property_ `public ushort Size => ...`
- L22 _public property_ `public EventType Type => ...`
- L23 _private field_ `private readonly GenericEvent _genericEvent`
- L25-40 _public ctor_ `public DiagnosticsSession2Event(string platform, string appName, string commandLine, string branch, string buildVersion, int changeList, int configurationType, int targetType)`
- L42-46 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events/GenericEvent.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.Events.Field`  
`public class Field`  
_public; L9-36_
- L11 _public property_ `public bool? Bool { get; }`
- L12 _public property_ `public int? Int { get; }`
- L13 _public property_ `public long? Long { get; }`
- L14 _public property_ `public double? Float { get; }`
- L15 _public property_ `public string? String { get; }`
- L16 _private* field_ `readonly byte[]? _array`
- L17-20 _public method_ `public byte[]? GetArray()`
- L22 _private ctor_ `private Field(bool value)`
- L23 _private ctor_ `private Field(int value)`
- L24 _private ctor_ `private Field(long value)`
- L25 _private ctor_ `private Field(float value)`
- L26 _private ctor_ `private Field(double value)`
- L27 _private ctor_ `private Field(string value)`
- L28 _private ctor_ `private Field(byte[] value)`
- L29 _public method_ `public static Field FromBool(bool value)`
- L30 _public method_ `public static Field FromInt(int value)`
- L31 _public method_ `public static Field FromLong(long value)`
- L32 _public method_ `public static Field FromFloat(float value)`
- L33 _public method_ `public static Field FromDouble(double value)`
- L34 _public method_ `public static Field FromString(string value)`
- L35 _public method_ `public static Field FromArray(byte[] value)`

#### class `EpicGames.Tracing.UnrealInsights.Events.GenericEvent`  
`public class GenericEvent : ITraceEvent`  
_public; L41-357_
- inherits: `ITraceEvent`
- desc: Represents a generic event in the stream with fields stored dynamically
- L43 _public property_ `public uint Serial { get; }`
- L44 _private* field_ `readonly Field[] _fields`
- L45 _public method_ `public Field[] GetFields()`
- L46 _public property_ `public EventType Type => ...`
- L47 _private field_ `private readonly EventType _eventType`
- L49-54 _public ctor_ `public GenericEvent(uint serial, Field[] fields, EventType eventType)`
- L56-99 _public property_ `public ushort Size { get; }`
- L102-212 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter")]`
- L215-325 _public method_ `public static GenericEvent Deserialize(ushort uid, BinaryReader reader, EventType eventType)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter")]`
- L327-333 _private method_ `private static uint SetBits(uint word, uint value, int pos, int size)`
- L335-339 _private method_ `private static uint ReadBits(uint word, int pos, int size)`
- L341-347 _internal method_ `internal static (ushort Uid, int FieldIndex, int Size) DeserializeAuxHeader(uint header)`
- L349-356 _internal method_ `internal static uint SerializeAuxHeader(ushort uid, int fieldIndex, int size)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events/Logging.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.Events.LoggingLogMessage`  
`public class LoggingLogMessage : ITraceEvent`  
_public; L8-24_
- inherits: `ITraceEvent`
- L10 _public field_ `public static readonly EventType EventType = new(0, "Logging", "LogMessage", EventType.FlagMaybeHasAux | EventType.FlagNoSync, [ new EventTypeField(0, 8, EventTypeField.TypeInt64, "LogPoint"), new EventTypeField(8, 8, EventTypeField.TypeInt64, " ...`
- L17 _public property_ `public ushort Size => ...`
- L18 _public property_ `public EventType Type => ...`
- L20-23 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events/Memory.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.Events.MemoryMemoryScopeEvent`  
`public class MemoryMemoryScopeEvent : ITraceEvent`  
_public; L8-20_
- inherits: `ITraceEvent`
- L10 _public field_ `public static readonly EventType EventType = new(0, "Memory", "MemoryScope", EventType.FlagNone, [new EventTypeField(0, 4, EventTypeField.TypeInt32, "Id")])`
- L13 _public property_ `public ushort Size => ...`
- L14 _public property_ `public EventType Type => ...`
- L16-19 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events/NewEvent.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.Events.EventTypeField`  
`public class EventTypeField`  
_public; L14-165_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("CodeQuality", "IDE0052:Remove unread private members")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Performance", "CA1823:Avoid unused private fields")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles")]`
- L16 _public property_ `public ushort Offset { get; set; }`
- L17 _public property_ `public ushort Size { get; set; }`
- L18 _public property_ `public byte TypeInfo { get; set; }`
- L19 _public property_ `public byte NameSize { get; set; }`
- L20 _public property_ `public string Name { get; set; }`
- L21 _public const_ `public const ushort StructSize = 2 + 2 + 1 + 1`
- L22 _private field_ `private static readonly byte Field_CategoryMask = ToOctalByte("300")`
- L23 _private field_ `private static readonly byte Field_Integer = ToOctalByte("000")`
- L24 _private field_ `private static readonly byte Field_Float = ToOctalByte("100")`
- L25 _private field_ `private static readonly byte Field_Array = ToOctalByte("200")`
- L27 _private field_ `private static readonly byte Field_Pow2SizeMask = ToOctalByte("003")`
- L28 _private field_ `private static readonly byte Field_8 = ToOctalByte("000")`
- L29 _private field_ `private static readonly byte Field_16 = ToOctalByte("001")`
- L30 _private field_ `private static readonly byte Field_32 = ToOctalByte("002")`
- L31 _private field_ `private static readonly byte Field_64 = ToOctalByte("003")`
- L32 _private field_ `private static readonly byte Field_Ptr = ToOctalByte("003")`
- L34 _private field_ `private static readonly byte Field_SpecialMask = ToOctalByte("030")`
- L35 _private field_ `private static readonly byte Field_Pod = ToOctalByte("000")`
- L36 _private field_ `private static readonly byte Field_String = ToOctalByte("010")`
- L38 _public field_ `public static readonly byte TypeBool = (byte)(Field_Pod | Field_Integer | Field_8)`
- L39 _public field_ `public static readonly byte TypeInt8 = (byte)(Field_Pod | Field_Integer | Field_8)`
- L40 _public field_ `public static readonly byte TypeInt16 = (byte)(Field_Pod | Field_Integer | Field_16)`
- L41 _public field_ `public static readonly byte TypeInt32 = (byte)(Field_Pod | Field_Integer | Field_32)`
- L42 _public field_ `public static readonly byte TypeInt64 = (byte)(Field_Pod | Field_Integer | Field_64)`
- L43 _public field_ `public static readonly byte TypePointer = (byte)(Field_Pod | Field_Integer | Field_Ptr)`
- L44 _public field_ `public static readonly byte TypeFloat32 = (byte)(Field_Pod | Field_Float | Field_32)`
- L45 _public field_ `public static readonly byte TypeFloat64 = (byte)(Field_Pod | Field_Float | Field_64)`
- L46 _public field_ `public static readonly byte TypeAnsiString = (byte)(Field_String | Field_Integer | Field_Array | Field_8)`
- L47 _public field_ `public static readonly byte TypeWideString = (byte)(Field_String | Field_Integer | Field_Array | Field_16)`
- L48 _public field_ `public static readonly byte TypeArray = (byte)(Field_Array)`
- L50-53 _public method_ `public static byte ToOctalByte(string Value)`
- L55-113 _public method_ `public static string TypeInfoToString(byte ByteInfo)`
- L115-122 _public ctor_ `public EventTypeField(ushort Offset, ushort Size, byte TypeInfo, byte NameSize)`
- L124-131 _public ctor_ `public EventTypeField(ushort Offset, ushort Size, byte TypeInfo, string Name)`
- L133-136 _public method_ `public bool IsArray()`
- L138-141 _public method_ `public bool IsAuxData()`
- L143-147 _public method_ `public void SetName(string Name)`
- L149-159 _public method_ `public void ValidateSize()`
- L161-164 _public method_ `public override string ToString()`

#### class `EpicGames.Tracing.UnrealInsights.Events.EventType`  
`public class EventType : ITraceEvent`  
_public; L167-389_
- inherits: `ITraceEvent`
- L169 _public property_ `public ushort NewEventUid { get; set; }`
- L170 _public property_ `public string LoggerName { get; set; }`
- L171 _public property_ `public string EventName { get; set; }`
- L172 _public property_ `public byte Flags { get; set; }`
- L173 _public property_ `public List<EventTypeField> Fields { get; set; }`
- L175 _public property_ `public string Name => ...`
- L177 _private field_ `private int _eventSize`
- L179 _public const_ `public const byte FlagNone = 0`
- L180 _public const_ `public const byte FlagImportant = 1 << 0`
- L181 _public const_ `public const byte FlagMaybeHasAux = 1 << 1`
- L182 _public const_ `public const byte FlagNoSync = 1 << 2`
- L184-192 _public ctor_ `public EventType(ushort newEventUid, string loggerName, string eventName, byte flags, List<EventTypeField> fields)`
- L194-201 _public ctor_ `public EventType(string loggerName, string eventName, byte flags)`
- L203-206 _public method_ `public static EventType WellKnown(ushort uid, string name)`
- L208-211 _private method_ `private static EventType Self()`
- L213-218 _public method_ `public void AddEventType(ushort offset, ushort size, byte typeInfo, string name)`
- L220-223 _public method_ `public bool IsWellKnown()`
- L225-228 _public method_ `public bool IsImportant()`
- L230-233 _public method_ `public bool MaybeHasAux()`
- L235-238 _public method_ `public bool IsNoSync()`
- L240 _public property_ `public bool HasSerial => ...`
- L242 _public property_ `public int NumAuxFields => ...`
- L249-252 _public method_ `public ushort GetEventSize()` — Size of events as seen in the stream For size of this NewEvent event, see GetSize()
- L254-257 _public method_ `public override string ToString()`
- L259-280 _public method_ `public string ToStringDetailed()`
- L282-296 _public property_ `public ushort Size { get; }`
- L298 _public property_ `public EventType Type => ...`
- L300-303 _public method_ `public override int GetHashCode()`
- L305-308 _protected method_ `protected bool Equals(EventType other)`
- L310-328 _public method_ `public override bool Equals(object? obj)`
- L330-358 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`
- L360-388 _public method_ `public static (ushort, EventType) Deserialize(BinaryReader reader)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Events/Trace.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.Events.TraceNewTraceEvent`  
`public class TraceNewTraceEvent : ITraceEvent`  
_public; L7-50_
- inherits: `ITraceEvent`
- L9 _public field_ `public static readonly EventType EventType = new(0, "$Trace", "NewTrace", EventType.FlagImportant | EventType.FlagNoSync, [ new EventTypeField(0, 8, EventTypeField.TypeInt64, "StartCycle"), new EventTypeField(8, 8, EventTypeField.TypeInt64, "Cyc ...`
- L17 _public property_ `public ulong StartCycle { get; set; }`
- L18 _public property_ `public ulong CycleFrequency { get; set; }`
- L19 _public property_ `public ushort Endian { get; set; }`
- L20 _public property_ `public byte PointerSize { get; set; }`
- L22 _public property_ `public ushort Size => ...`
- L23 _public property_ `public EventType Type => ...`
- L25-31 _public ctor_ `public TraceNewTraceEvent(ulong startCycle, ulong cycleFrequency, ushort endian, byte pointerSize)`
- L33-40 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`
- L42-49 _public method_ `public static TraceNewTraceEvent Deserialize(BinaryReader reader)`

#### class `EpicGames.Tracing.UnrealInsights.Events.TraceThreadInfoEvent`  
`public class TraceThreadInfoEvent : ITraceEvent`  
_public; L52-84_
- inherits: `ITraceEvent`
- L54 _public field_ `public static readonly EventType EventType = new(0, "$Trace", "ThreadInfo", EventType.FlagImportant | EventType.FlagMaybeHasAux | EventType.FlagNoSync, [ new EventTypeField(0, 4, EventTypeField.TypeInt32, "ThreadId"), new EventTypeField(4, 4, Ev ...`
- L62 _public property_ `public ushort Size => ...`
- L63 _public property_ `public EventType Type => ...`
- L64 _private field_ `private readonly GenericEvent _genericEvent`
- L66-77 _public ctor_ `public TraceThreadInfoEvent(int threadId, int systemId, int sortHint, string name)`
- L79-83 _public method_ `public void Serialize(ushort uid, BinaryWriter writer)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Reader.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.PredefinedEventUid`  
`public static class PredefinedEventUid`  
_public; L12-31_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Naming", "CA1707:Identifiers should not contain underscores")]`
- L14 _public const_ `public const ushort NewEvent = 0`
- L15 _public const_ `public const ushort AuxData = 1`
- L17 _public const_ `public const ushort AuxDataTerminal = 3`
- L18 _public const_ `public const ushort EnterScope = 4`
- L19 _public const_ `public const ushort LeaveScope = 5`
- L22 _public const_ `public const ushort EnterScope_T = 8`
- L26 _public const_ `public const ushort LeaveScope_T = 12`
- L30 _public const_ `public const ushort WellKnownNum = 16`

#### class `EpicGames.Tracing.UnrealInsights.UnrealInsightsReader`  
`public class UnrealInsightsReader`  
_public; L33-201_
- L35 _public property_ `public Dictionary<ushort, EventType> EventTypes { get; }`
- L36 _public property_ `public Dictionary<ushort, List<ITraceEvent>> EventsPerThread { get; }`
- L38 _internal property_ `internal int NumTransportPacketsRead { get; set; }`
- L40-44 _public ctor_ `public UnrealInsightsReader()`
- L46-74 _public method_ `public void Read(Stream stream)`
- L84-106 _public method_ `public Dictionary<ushort, MemoryStream> Demux(BinaryReader reader)` — Demultiplex the stream into one continuous buffer per thread. This avoids dealing with blocks that span multiple transport packets. It's a naive and simple enough for our parsing purposes but it definitely won't read larger trace files.
- L108-171 _public method_ `public List<ITraceEvent> ReadEvents(int threadId, BinaryReader reader)`
- L173-192 _public method_ `public Dictionary<ushort, List<ITraceEvent>> GetEventsPerUid()`
- L194-200 _public method_ `public void PrintEventSummary()`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/StreamHeader.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.StreamHeader`  
`public class StreamHeader`  
_public; L8-80_
- L10 _public const_ `public const uint MagicTrc = 1414677317`
- L11 _public const_ `public const uint MagicTrc2 = 1414677298`
- L13 _private* field_ `uint _magicFourCc`
- L14 _private* field_ `ushort _metadataSize`
- L15 _private* field_ `ushort _metadataField0`
- L16 _private* field_ `ushort _controlPort`
- L18 _private* field_ `byte _transportVersion`
- L19 _private* field_ `byte _protocolVersion`
- L21-23 _private ctor_ `private StreamHeader()`
- L25-32 _public method_ `public static StreamHeader Default()`
- L34-53 _public method_ `public void Serialize(BinaryWriter writer)`
- L55-79 _public method_ `public static StreamHeader Deserialize(BinaryReader reader)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/TraceUtils.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.TraceUtils`  
`public static class TraceUtils`  
_public; L7-43_
- L9-24 _public method_ `public static ulong Read7BitUint(BinaryReader reader)`
- L26-42 _public method_ `public static int Write7BitUint(BinaryWriter writer, ulong value)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/TransportPacket.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.TransportPacket`  
`public class TransportPacket`  
_public; L10-116_
- L12 _public const_ `public const int ThreadIdEvents = 0`
- L13 _public const_ `public const int ThreadIdInternal = 1`
- L14 _public const_ `public const int ThreadIdImportants = ThreadIdInternal`
- L16 _private const_ `private const ushort EncodedMarker = 0x8000`
- L17 _private const_ `private const ushort PartialMarker = 0x4000`
- L18 _private const_ `private const ushort ThreadIdMask = PartialMarker - 1`
- L20 _public property_ `public ushort PacketSize { get; set; }`
- L21 _public property_ `public ushort ThreadIdAndMarkers { get; set; }`
- L22 _public property_ `public ushort DecodedSize { get; set; }`
- L23 _private* field_ `byte[] _data = []`
- L24-27 _public method_ `public byte[] GetData()`
- L29-31 _private ctor_ `private TransportPacket()`
- L33-36 _public method_ `public bool IsEncoded()`
- L38-41 _public method_ `public bool IsPartial()`
- L43-46 _public method_ `public ushort GetThreadId()`
- L48-66 _public method_ `public static bool IsNormalThread(ushort threadId)`
- L68-84 _public method_ `public void Serialize(BinaryWriter writer, IEnumerable<(ushort, ITraceEvent)> events)`
- L86-89 _public method_ `public override string ToString()`
- L91-97 _public method_ `public static TransportPacket Create(ushort packetSize, ushort threadId)`
- L99-115 _public method_ `public static TransportPacket Deserialize(BinaryReader reader)`

### `Source/Programs/Shared/EpicGames.Tracing/UnrealInsights/Writer.cs` (EpicGames.Tracing)


#### class `EpicGames.Tracing.UnrealInsights.UnrealInsightsWriter`  
`public class UnrealInsightsWriter`  
_public; L12-111_
- L14 _private* field_ `readonly Dictionary<EventType, ushort> _eventTypeToUids = ...`
- L14 _private* field_ `readonly Dictionary< _eventTypeToUids = []`
- L15 _private* field_ `readonly Dictionary<ushort, EventType> _uidToEventTypes = ...`
- L15 _private* field_ `readonly Dictionary< _uidToEventTypes = []`
- L16 _private* field_ `readonly Dictionary<ushort, List<ITraceEvent>> _threadToEvents = ...`
- L16 _private* field_ `readonly Dictionary< _threadToEvents = []`
- L18 _private field_ `private ushort _uidCounter = PredefinedEventUid.WellKnownNum`
- L19 _private field_ `private readonly Lock _lock = new()`
- L21-36 _public ctor_ `public UnrealInsightsWriter()`
- L38-62 _public method_ `public void AddEvent(ushort threadId, ITraceEvent @event)`
- L64-68 _private method_ `private void RegisterEventType(ushort uid, EventType eventType)`
- L70-87 _public method_ `public void Write(BinaryWriter writer)`
- L89-100 _private method_ `private void WriteHeader(BinaryWriter writer)`
- L102-110 _private method_ `private void WriteThread(ushort threadId, BinaryWriter writer)`
