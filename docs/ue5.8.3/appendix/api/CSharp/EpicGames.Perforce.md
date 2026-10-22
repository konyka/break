# CSharp / EpicGames.Perforce

- project root: `Source/Programs/Shared/EpicGames.Perforce`
- files: 113; symbols: 1466
- symbol kinds: class=93, const=5, ctor=81, delegate=2, dtor=1, enum=50, enumerator=320, field=103, interface=4, method=379, operator=7, property=416, record struct=2, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Perforce/FileSpecList.cs` (EpicGames.Perforce)


#### struct `EpicGames.Perforce.FileSpecList`  
`public readonly struct FileSpecList : IEquatable<FileSpecList>`  
_public; L12-104_
- inherits: `IEquatable<FileSpecList>`
- desc: Wrapper for a list of filespecs. Allows implicit conversion from string (a single entry) or list.
- L17 _public property_ `public static FileSpecList Empty { get; }` — Empty filespec list
- L22 _public property_ `public static FileSpecList Any { get; }` — Matches any files in the depot
- L27 _public property_ `public IReadOnlyList<string> List { get; }` — The list of filespecs
- L33-36 _private ctor_ `private FileSpecList(IReadOnlyList<string> fileSpecList)` — Private constructor. Use implicit conversion operators below instead.
- L39 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L42-50 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L53 _public method_ `public bool Equals(FileSpecList other)` — (inheritdoc)
- L58 _public operator_ `public static bool operator ==(FileSpecList a, FileSpecList b)` — Test two filespecs for equality
- L63 _public operator_ `public static bool operator !=(FileSpecList a, FileSpecList b)` — Test two filespecs for inequality
- L69-72 _public operator_ `public static implicit operator FileSpecList(List<string> list)` — Implicit conversion operator from a list of filespecs
- L78-81 _public operator_ `public static implicit operator FileSpecList(string[] array)` — Implicit conversion operator from an array of filespecs
- L87-90 _public operator_ `public static implicit operator FileSpecList(string fileSpec)` — Implicit conversion operator from a single filespec
- L93-103 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Perforce/HangMonitor.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.HangMonitor`  
`public sealed class HangMonitor : IDisposable`  
_public; L15-127_
- inherits: `IDisposable`
- desc: Runs a background task that logs warnings if the Tick method isn't called within a certain time period
- L36 _private* field_ `readonly AsyncEvent _activeEvent = new()`
- L37 _private* field_ `readonly TimeSpan _interval`
- L38 _private* field_ `readonly string _context`
- L39 _private* field_ `readonly ILogger _logger`
- L40 _private* field_ `long _lastUpdateTicks`
- L41 _private* field_ `Scope? _scope`
- L42 _private* field_ `BackgroundTask? _hangTask`
- L50-55 _public ctor_ `public HangMonitor(TimeSpan interval, string context, ILogger logger)` — Constructor
- L58-65 _public method_ `public void Dispose()` — (inheritdoc)
- L71-84 _public method_ `public IDisposable Start(string activity)` — Start monitoring for hangs.
- L89-92 _public method_ `public void Tick()` — Marks the operation as ongoing
- L94-126 _private* method_ `async Task CheckStatusAsync(CancellationToken cancellationToken)`

#### class `EpicGames.Perforce.HangMonitor.Scope`  
`class Scope : IDisposable`  
_private*; L17-34_
- inherits: `IDisposable`
- L19 _private* field_ `readonly HangMonitor _hangMonitor`
- L20 _private* field_ `readonly string _activity`
- L22 _public property_ `public string Activity => ...`
- L24-28 _public ctor_ `public Scope(HangMonitor hangMonitor, string activity)`
- L30-33 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.Perforce/IPerforceConnection.cs` (EpicGames.Perforce)


#### interface `EpicGames.Perforce.IPerforceConnection`  
`public interface IPerforceConnection : IDisposable`  
_public; L13-48_
- inherits: `IDisposable`
- desc: Base interface for Perforce clients
- L18 _public* property_ `IPerforceSettings Settings { get; }` — Connection settings
- L23 _public* property_ `ILogger Logger { get; }` — Logger for this connection
- L28 _public* property_ `Tracer Tracer { get; }` — Tracer for this connection
- L40 _public* method_ `IPerforceOutput Command(string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, string? promptResponse, bool interceptIo)` — Queues a Perforce command to be executed
- L47 _public* method_ `PerforceRecord CreateRecord(List<KeyValuePair<string, object>> fields)` — Creates a record from a set of input fields

### `Source/Programs/Shared/EpicGames.Perforce/IPerforceOutput.cs` (EpicGames.Perforce)


#### interface `EpicGames.Perforce.IPerforceOutput`  
`public interface IPerforceOutput : IAsyncDisposable`  
_public; L20-38_
- inherits: `IAsyncDisposable`
- desc: Interface for the result of a Perforce operation
- L25 _public* property_ `ReadOnlyMemory<byte> Data { get; }` — Data containing the result
- L31 _public* method_ `Task<bool> ReadAsync(CancellationToken token)` — Waits until more data has been read into the buffer.
- L37 _public* method_ `void Discard(int numBytes)` — Discard bytes from the start of the result buffer

#### class `EpicGames.Perforce.PerforceOutput`  
`public static class PerforceOutput`  
_public; L43-827_
- desc: Utility methods for IPerforceOutput
- L62 _private* field_ `static readonly byte[] s_recordPrefix = [(byte)'{', (byte)'s', 4, 0, 0, 0, (byte)'c', (byte)'o', (byte)'d', (byte)'e', (byte)'s']` — Standard prefix for a returned record: record indicator, string, 4 bytes, 'code', string, [value]
- L83 _public method_ `public static IPerforceOutput FromData(ReadOnlyMemory<byte> data)` — Constructs an IPerforceOutput object from a block of data
- L90 _public method_ `public static IPerforceOutput FromResponse(PerforceResponse response)` — Constructs an IPerforceOutput object from a response
- L97-114 _public method_ `public static IPerforceOutput FromResponses(IEnumerable<PerforceResponse> responses)` — Constructs an IPerforceOutput object from a sequence of responses
- L121-163 _private method_ `private static string FormatDataAsString(ReadOnlySpan<byte> data)` — Formats the current contents of the buffer to a string
- L171-211 _private method_ `private static string FormatDataAsHexDump(ReadOnlySpan<byte> data, int maxLength = 1024)` — Formats the current contents of the buffer to a string
- L213 _private* field_ `static readonly byte[] s_connectionErrorPrefix = Encoding.UTF8.GetBytes("Perforce client error:")`
- L222-276 _public method_ `public static async IAsyncEnumerable<PerforceResponse> ReadStreamingResponsesAsync(this IPerforceOutput perforce, Type? statRecordType, [EnumeratorCancellation] CancellationToken cancellationToken)` — Read a list of responses from the child process
- L285-338 _public method_ `public static async Task<List<PerforceResponse>> ReadResponsesAsync(this IPerforceOutput perforce, Type? statRecordType, CancellationToken cancellationToken)` — Read a list of responses from the child process
- L347-375 _public method_ `public static async Task ReadRecordsAsync(this IPerforceOutput perforce, Action<PerforceRecord> handleRecord, CancellationToken cancellationToken)` — Read a list of responses from the child process
- L385-465 _public method_ `public static bool ParseRecord(ReadOnlyMemory<byte> buffer, ref int bufferPos, List<KeyValuePair<Utf8String, PerforceValue>> rows)` — attrs: `[SuppressMessage("Design", "CA1045:Do not pass types by reference", Justification = "<Pending>")]` — Reads from the buffer into a record object
- L475-546 _private* method_ `static bool TryReadResponse(ReadOnlyMemory<byte> buffer, ref int bufferPos, CachedRecordInfo? statRecordInfo, [NotNullWhen(true)] out PerforceResponse? response)` — Reads a response object from the buffer
- L556-663 _private* method_ `static bool TryReadTypedRecord(ReadOnlyMemory<byte> buffer, ref int bufferPos, CachedRecordInfo recordInfo, [NotNullWhen(true)] out object? record)` — Parse an individual record from the server.
- L665-707 _private* method_ `static object? GetNestedRecord(object? targetObject, Utf8String suffix, NestedRecordInfo[] nestedRecords)`
- L717-759 _private* method_ `static bool TryReadValue(ReadOnlyMemory<byte> buffer, ref int bufferPos, object? newRecord, TaggedPropertyInfo? tagInfo)` — Reads a value from the input buffer
- L768-779 _private* method_ `static bool TryReadByte(ReadOnlySpan<byte> buffer, ref int bufferPos, out byte value)` — Attempts to read a single byte from the buffer
- L788-799 _private* method_ `static bool TryReadInt(ReadOnlySpan<byte> buffer, ref int bufferPos, out int value)` — Attempts to read a single int from the buffer
- L808-826 _private* method_ `static bool TryReadString(ReadOnlyMemory<byte> buffer, ref int bufferPos, out Utf8String result)` — Attempts to read a string from the buffer

#### class `EpicGames.Perforce.PerforceOutput.ReadOnlyUtf8StringConstants`  
`static class ReadOnlyUtf8StringConstants`  
_private*; L48-57_
- desc: String constants for records
- L50 _public field_ `public static readonly Utf8String Code = new("code")`
- L51 _public field_ `public static readonly Utf8String Stat = new("stat")`
- L52 _public field_ `public static readonly Utf8String Info = new("info")`
- L53 _public field_ `public static readonly Utf8String Error = new("error")`
- L54 _public field_ `public static readonly Utf8String Io = new("io")`
- L55 _public field_ `public static readonly Utf8String Func = new("func")`
- L56 _public field_ `public static readonly Utf8String IsSparse = new("isSparse")`

#### class `EpicGames.Perforce.PerforceOutput.BufferedPerforceOutput`  
`class BufferedPerforceOutput : IPerforceOutput`  
_private*; L64-76_
- inherits: `IPerforceOutput`
- L66 _public property_ `public ReadOnlyMemory<byte> Data { get; set; }`
- L68-71 _public ctor_ `public BufferedPerforceOutput(ReadOnlyMemory<byte> data)`
- L73 _public method_ `public Task<bool> ReadAsync(CancellationToken cancellationToken)`
- L74 _public method_ `public void Discard(int numBytes)`
- L75 _public method_ `public ValueTask DisposeAsync()`

### `Source/Programs/Shared/EpicGames.Perforce/NativePerforceConnection.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.NativePerforceConnection`  
`public sealed class NativePerforceConnection : IPerforceConnection, IDisposable`  
_public; L24-753_
- inherits: `IPerforceConnection, IDisposable`
- desc: Experimental implementation of IPerforceConnection which wraps the native C++ API.
- L26 _private* const_ `const string NativeDll = "EpicGames.Perforce.Native"`
- L73 _private* delegate_ `delegate void OnBufferReadyFn(NativeReadBuffer readBuffer, [In, Out] NativeWriteBuffer writeBuffer)` — attrs: `[UnmanagedFunctionPointer(CallingConvention.Cdecl)]`
- L76 _private* method_ `static extern IntPtr Client_Create(NativeSettings? settings, NativeWriteBuffer writeBuffer, IntPtr onBufferReadyFnPtr)` — attrs: `[DllImport(NativeDll, CallingConvention = CallingConvention.Cdecl)]`
- L79 _private* method_ `static extern void Client_Command(IntPtr client, [MarshalAs(UnmanagedType.LPStr)] string command, int numArgs, IntPtr[] args, byte[]? inputData, int inputLength, byte[]? promptResponse, bool interceptIo)` — attrs: `[DllImport(NativeDll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, BestFitMapping = false, ThrowOnUnmappableChar = true)]`
- L82 _private* method_ `static extern void Client_CancelCommand(IntPtr client)` — attrs: `[DllImport(NativeDll, CallingConvention = CallingConvention.Cdecl)]`
- L85 _private* method_ `static extern void Client_Destroy(IntPtr client)` — attrs: `[DllImport(NativeDll, CallingConvention = CallingConvention.Cdecl)]`
- L302 _private* field_ `static int s_nextUniqueId`
- L304 _private* field_ `IntPtr _client`
- L305 _private* field_ `readonly int _uniqueId`
- L306 _private* field_ `readonly PinnedBuffer[] _buffers`
- L307 _private* field_ `readonly OnBufferReadyFn _onBufferReadyInst`
- L308 _private* field_ `readonly IntPtr _onBufferReadyFnPtr`
- L309 _private* field_ `Thread? _backgroundThread`
- L310 _private* field_ `readonly BlockingCollection<(Action, Response)?> _requests = []`
- L311 _private* field_ `readonly BlockingCollection<PinnedBuffer> _writeBuffers = []`
- L312 _private* field_ `Response? _currentResponse`
- L313 _private* field_ `readonly ManualResetEvent _responseCompleteEvent`
- L314 _private* field_ `readonly Stopwatch _stallTimer = new()`
- L315 _private* field_ `readonly HangMonitor _hangMonitor`
- L316 _private* field_ `bool _disposed`
- L319 _public property_ `public IPerforceSettings Settings { get; }` — (inheritdoc)
- L322 _public property_ `public ILogger Logger { get; set; }` — (inheritdoc)
- L325 _public property_ `public Tracer Tracer { get; set; }` — (inheritdoc)
- L333-336 _public ctor_ `public NativePerforceConnection(IPerforceSettings settings, ILogger logger, Tracer? tracer = null) : this(settings, 2, 128 * 1024, logger, tracer)` — Constructor
- L346-374 _public ctor_ `public NativePerforceConnection(IPerforceSettings settings, int bufferCount, int bufferSize, ILogger logger, Tracer? tracer = null)` — Constructor
- L379-393 _public method_ `public static async Task<NativePerforceConnection> CreateAsync(IPerforceSettings settings, ILogger logger, Tracer? tracer = null)` — Create an instance of the native client
- L399-414 _public method_ `public static bool IsSupported()` — Check whether the native client is supported on the current platform
- L416-433 _private* method_ `void GetNextWriteBuffer(NativeWriteBuffer nativeWriteBuffer, int minSize)`
- L438-441 _private* dtor_ `~NativePerforceConnection()` — Finalizer
- L444-448 _public method_ `public void Dispose()` — (inheritdoc)
- L451-493 _private* method_ `void Dispose(bool disposing)` — (inheritdoc)
- L498 _public property_ `public TimeSpan StallTime => ...` — Gets the amount of time stalled waiting for an output buffer in the last command
- L503-510 _private method_ `private async Task ConnectAsync()` — Initializes the connection, throwing an error on failure
- L516-556 _private method_ `private async Task<PerforceError?> TryConnectAsync()` — Tries to initialize the connection
- L563-592 _private* method_ `void BackgroundThreadProc()` — Background thread which sequences requests on a single thread. The Perforce API isn't async aware, but is primarily I/O bound, so this thread will mostly be idle. All processing C#-side is done using async tasks, whereas this thread blocks.
- L599-613 _private* method_ `void OnBufferReady(NativeReadBuffer readBuffer, [In, Out] NativeWriteBuffer writeBuffer)` — Callback for switching buffers
- L616-633 _public method_ `public IPerforceOutput Command(string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, string? promptResponse, bool interceptIo)` — (inheritdoc)
- L635-700 _private method_ `private void ExecCommand(string command, List<string> args, byte[]? inputData, string? promptResponse, bool interceptIo)`
- L702-710 _private* method_ `long GetAllocatedSize()`
- L715-749 _private* method_ `static string FormatSpec(byte[] inputData)` — Converts a Python marshalled data blob to a spec definition
- L752 _public method_ `public PerforceRecord CreateRecord(List<KeyValuePair<string, object>> fields)` — (inheritdoc)

#### class `EpicGames.Perforce.NativePerforceConnection.NativeSettings`  
`class NativeSettings`  
_private*; L29-51_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L32 _public field_ `public string? _serverAndPort` — attrs: `[MarshalAs(UnmanagedType.LPStr)]`
- L35 _public field_ `public string? _userName` — attrs: `[MarshalAs(UnmanagedType.LPStr)]`
- L38 _public field_ `public string? _password` — attrs: `[MarshalAs(UnmanagedType.LPStr)]`
- L41 _public field_ `public string? _hostName` — attrs: `[MarshalAs(UnmanagedType.LPStr)]`
- L44 _public field_ `public string? _clientName` — attrs: `[MarshalAs(UnmanagedType.LPStr)]`
- L47 _public field_ `public string? _appName` — attrs: `[MarshalAs(UnmanagedType.LPStr)]`
- L50 _public field_ `public string? _appVersion` — attrs: `[MarshalAs(UnmanagedType.LPStr)]`

#### class `EpicGames.Perforce.NativePerforceConnection.NativeReadBuffer`  
`class NativeReadBuffer`  
_private*; L55-62_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Compiler", "CA1812")]`
- L57 _public field_ `public IntPtr _data`
- L58 _public field_ `public int _length`
- L59 _public field_ `public int _count`
- L60 _public field_ `public int _maxLength`
- L61 _public field_ `public int _maxCount`

#### class `EpicGames.Perforce.NativePerforceConnection.NativeWriteBuffer`  
`class NativeWriteBuffer`  
_private*; L65-70_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L67 _public field_ `public IntPtr _data`
- L68 _public field_ `public int _maxLength`
- L69 _public field_ `public int _maxCount`

#### class `EpicGames.Perforce.NativePerforceConnection.PinnedBuffer`  
`class PinnedBuffer : IDisposable`  
_private*; L90-143_
- inherits: `IDisposable`
- desc: A buffer used for native code to stream data into
- L92 _private* field_ `static readonly byte[] s_guardBytes = [.. Enumerable.Repeat<byte>(0xfd, 16)]`
- L94 _public property_ `public byte[] AllocatedData { get; set; }`
- L95 _public property_ `public Memory<byte> Data { get; set; }`
- L96 _public property_ `public GCHandle Handle { get; set; }`
- L97 _public property_ `public IntPtr BasePtr { get; set; }`
- L98 _public property_ `public int MaxLength => ...`
- L100-104 _public ctor_ `public PinnedBuffer(int maxLength)`
- L106-115 _private* method_ `void AllocateBuffer(int maxLength)`
- L117-127 _public method_ `public void CheckGuardBytes()`
- L129-137 _public method_ `public void Resize(int maxLength)`
- L139-142 _public method_ `public void Dispose()`

#### class `EpicGames.Perforce.NativePerforceConnection.Response`  
`class Response : IPerforceOutput`  
_private*; L148-300_
- inherits: `IPerforceOutput`
- desc: Response object for a request
- L150 _private* field_ `readonly NativePerforceConnection _outer`
- L152 _private* field_ `PinnedBuffer? _buffer`
- L153 _private* field_ `int _bufferPos`
- L154 _private* field_ `int _bufferLen`
- L156 _private* field_ `PinnedBuffer? _nextBuffer`
- L157 _private* field_ `int _nextBufferPos`
- L158 _private* field_ `int _nextBufferLen`
- L160 _private* field_ `CancellationTokenRegistration _cancelRegistration`
- L161 _private* field_ `bool _cancelRegistered`
- L163 _public field_ `public Channel<(PinnedBuffer Buffer, int Length)> _readBuffers = Channel.CreateUnbounded<(PinnedBuffer, int)>()`
- L165 _public property_ `public ReadOnlyMemory<byte> Data => ...`
- L167-170 _public ctor_ `public Response(NativePerforceConnection outer)`
- L172-195 _public method_ `public async ValueTask DisposeAsync()`
- L197-212 _private* method_ `async Task<(PinnedBuffer?, int)> GetNextReadBufferAsync(CancellationToken token = default)`
- L214-292 _public method_ `public async Task<bool> ReadAsync(CancellationToken token)`
- L294-299 _public method_ `public void Discard(int numBytes)`

### `Source/Programs/Shared/EpicGames.Perforce/PerforceAttributes.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceTagAttribute`  
`public sealed class PerforceTagAttribute : Attribute`  
_public; L11-31_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attributes for fields that should be deserialized from P4 tags
- L16 _public property_ `public string Name { get; }` — The tag name
- L21 _public property_ `public bool Optional { get; set; }` — Whether this tag is required for a valid record
- L27-30 _public ctor_ `public PerforceTagAttribute(string name)` — Constructor

#### class `EpicGames.Perforce.PerforceEnumAttribute`  
`public sealed class PerforceEnumAttribute : Attribute`  
_public; L37-52_
- attrs: `[AttributeUsage(AttributeTargets.Field)]`
- inherits: `Attribute`
- desc: Specifies the name of an enum when converted into a P4 string
- L42 _public property_ `public string Name { get; }` — Name of the enum value
- L48-51 _public ctor_ `public PerforceEnumAttribute(string name)` — Constructor

#### class `EpicGames.Perforce.PerforceRecordListAttribute`  
`public sealed class PerforceRecordListAttribute : Attribute`  
_public; L58-60_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: When attached to a list field, indicates that a list of structures can be included in the record

### `Source/Programs/Shared/EpicGames.Perforce/PerforceChangeView.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceChangeView`  
`public class PerforceChangeView`  
_public; L13-63_
- desc: Represents a change view from a clientspec or stream
- L18 _public property_ `public List<PerforceChangeViewEntry> Entries { get; }` — List of entries for this change view
- L25-36 _public method_ `public bool IsVisible(string depotFile, int change)` — Determines if a file revision is visible
- L43-62 _public method_ `public static PerforceChangeView Parse(IEnumerable<string> lines, bool ignoreCase)` — Parse a change view from a specification

#### class `EpicGames.Perforce.PerforceChangeViewEntry`  
`public class PerforceChangeViewEntry`  
_public; L68-104_
- desc: Entry for a change view
- L73 _public property_ `public string Path { get; }` — Pattern to match
- L78 _public property_ `public long Change { get; }` — Change to be imported at
- L80 _private* field_ `readonly Regex _pathRegex`
- L85-96 _public ctor_ `public PerforceChangeViewEntry(string pattern, bool ignoreCase)` — Constructor
- L103 _public method_ `public bool Matches(string depotPath)` — Determine

### `Source/Programs/Shared/EpicGames.Perforce/PerforceChildProcess.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceChildProcess`  
`public sealed class PerforceChildProcess : IPerforceOutput, IDisposable`  
_public; L18-206_
- inherits: `IPerforceOutput, IDisposable`
- desc: Wraps a call to a p4.exe child process, and allows reading data from it
- L23 _private* field_ `ManagedProcessGroup _childProcessGroup` — The process group
- L28 _private* field_ `ManagedProcess _childProcess` — The child process instance
- L33 _private* field_ `ITraceSpan _scope` — Scope object for tracing
- L38 _private* field_ `byte[] _buffer` — The buffer data
- L43 _private* field_ `int _bufferEnd` — End of the valid portion of the buffer (exclusive)
- L46 _public property_ `public ReadOnlyMemory<byte> Data => ...` — (inheritdoc)
- L51 _private* field_ `string? _tempFileName` — Temp file containing file arguments
- L62-86 _public ctor_ `public PerforceChildProcess(string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, IReadOnlyList<string> globalOptions, ILogger logger)` — Constructor
- L92-116 _public method_ `public static string GetExecutable()` — Gets the path to the P4.EXE executable
- L119-123 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L126-152 _public method_ `public void Dispose()` — (inheritdoc)
- L155-175 _public method_ `public async Task<bool> ReadAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L178-185 _public method_ `public void Discard(int numBytes)` — (inheritdoc)
- L192-205 _public method_ `public async Task<Tuple<bool, string>> TryReadToEndAsync(CancellationToken cancellationToken)` — Reads all output from the child process as a string

### `Source/Programs/Shared/EpicGames.Perforce/PerforceConnection.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceConnection`  
`public sealed class PerforceConnection : IPerforceConnection`  
_public; L21-377_
- inherits: `IPerforceConnection`
- desc: Stores settings for communicating with a Perforce server.
- L26 _public property_ `public static Tracer DefaultTracer { get; }` — Default tracer. A custom tracer can also be passed to constructor or factory methods.
- L33-36 _public method_ `public static Task<IPerforceConnection> CreateAsync(ILogger logger, Tracer? tracer = null)` — Create a new Perforce connection
- L45-48 _public method_ `public static Task<IPerforceConnection> CreateAsync(string? serverAndPort, string? userName, ILogger logger, Tracer? tracer = null)` — Create a new Perforce connection
- L58-61 _public method_ `public static Task<IPerforceConnection> CreateAsync(string? serverAndPort, string? userName, string? clientName, ILogger logger, Tracer? tracer = null)` — Create a new Perforce connection
- L73-76 _public method_ `public static Task<IPerforceConnection> CreateAsync(string? serverAndPort, string? userName, string? clientName, string? appName, string? appVersion, ILogger logger, Tracer? tracer = null)` — Create a new Perforce connection
- L84-94 _public method_ `public static async Task<IPerforceConnection> CreateAsync(IPerforceSettings settings, ILogger logger, Tracer? tracer = null)` — Create a new Perforce connection
- L96-120 _private* method_ `static PerforceSettings CombineSettings(string? serverAndPort, string? userName, string? clientName = null, string? appName = null, string? appVersion = null)`
- L125-152 _public property_ `public IPerforceSettings Settings { get; }` — (inheritdoc)
- L157-161 _public property_ `public string? ServerAndPort { get; set; }` — The current server and port
- L166-170 _public property_ `public string? UserName { get; set; }` — The current user name
- L175-179 _public property_ `public string? HostName { get; set; }` — The current host name
- L184-188 _public property_ `public string? ClientName { get; set; }` — The current client name
- L193-197 _public property_ `public string? AppName { get; set; }` — Name of this application, reported to server through -zprog arguments
- L202-206 _public property_ `public string? AppVersion { get; set; }` — Version of this application, reported to server through -zversion arguments
- L211 _public property_ `public List<string> GlobalOptions { get; }` — Additional options to append to the command line
- L214 _public property_ `public ILogger Logger { get; set; }` — (inheritdoc)
- L217 _public property_ `public Tracer Tracer { get; set; }` — (inheritdoc)
- L226-229 _public ctor_ `public PerforceConnection(string? serverAndPort, string? userName, ILogger logger, Tracer? tracer = null) : this(serverAndPort, userName, null, logger, tracer)` — Constructor
- L239-248 _public ctor_ `public PerforceConnection(string? serverAndPort, string? userName, string? clientName, ILogger logger, Tracer? tracer = null) : this(serverAndPort, userName, clientName, null, null, logger, tracer)` — Constructor
- L260-269 _public ctor_ `public PerforceConnection(string? serverAndPort, string? userName, string? clientName, string? appName, string? appVersion, ILogger logger, Tracer? tracer = null)` — Constructor
- L274-278 _public ctor_ `public PerforceConnection(IPerforceSettings settings, ILogger logger, Tracer? tracer = null) : this(settings.ServerAndPort, settings.UserName, settings.ClientName, settings.AppName, settings.AppVersion, logger, tracer)` — Constructor
- L284-288 _public ctor_ `public PerforceConnection(PerforceConnection other) : this(other.ServerAndPort, other.UserName, other.ClientName, other.AppName, other.AppVersion, other.Logger, other.Tracer)` — Constructor
- L291-293 _public method_ `public void Dispose()` — (inheritdoc)
- L295-324 _private* method_ `List<string> GetGlobalArguments()`
- L327-338 _public method_ `public IPerforceOutput Command(string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, string? promptResponse, bool interceptIo)` — (inheritdoc)
- L347-354 _public method_ `public async Task SetAsync(string name, string value, CancellationToken cancellationToken = default)` — Sets an environment variable
- L363-371 _public method_ `public async Task<Tuple<bool, string>> TrySetAsync(string name, string value, CancellationToken cancellationToken = default)` — Sets an environment variable
- L374 _public method_ `public PerforceRecord CreateRecord(List<KeyValuePair<string, object>> fields)` — (inheritdoc)

#### class `EpicGames.Perforce.PerforceConnectionExtensions`  
`public static class PerforceConnectionExtensions`  
_public; L382-4388_
- desc: Extension methods for PerforceConnection
- L390-394 _public method_ `public static Task<IPerforceConnection> WithClientAsync(this IPerforceConnection perforce, string? clientName)` — Create a new connection with a different client
- L401-404 _public method_ `public static Task<IPerforceConnection> WithoutClientAsync(this IPerforceConnection perforce)` — Create a new connection with a different client
- L408-424 _private method_ `private static void AddAttributes(IPerforceConnection perforce, TelemetrySpan span, string commandType, string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments)`
- L436-439 _public method_ `public static Task<List<PerforceResponse>> CommandAsync(this IPerforceConnection perforce, string command, IReadOnlyList<string> arguments, byte[]? inputData, Type? statRecordType, CancellationToken cancellationToken = default)` — Execute a command and parse the response
- L452-462 _public method_ `public static async Task<List<PerforceResponse>> CommandAsync(this IPerforceConnection perforce, string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, Type? statRecordType, CancellationToken cancellationToken = default)` — Execute a command and parse the response
- L476-492 _public method_ `public static async IAsyncEnumerable<PerforceResponse> StreamCommandAsync(this IPerforceConnection perforce, string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, Type? statRecordType, bool interceptIo, [EnumeratorCancellation] CancellationToken cancellationToken)` — Execute a command and parse the response
- L504-521 _public method_ `public static async IAsyncEnumerable<PerforceResponse<T>> StreamCommandAsync<T>(this IPerforceConnection perforce, string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments = null, byte[]? inputData = null, [EnumeratorCancellation] CancellationToken cancellationToken = default) where T : class` — Execute a command and parse the response
- L533-541 _public method_ `public static async Task RecordCommandAsync(this IPerforceConnection perforce, string command, IReadOnlyList<string> arguments, byte[]? inputData, Action<PerforceRecord> handleRecord, CancellationToken cancellationToken = default)` — Execute a command and parse the response
- L553-563 _public method_ `public static async Task<PerforceResponseList<T>> CommandAsync<T>(this IPerforceConnection connection, string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, CancellationToken cancellationToken = default) where T : class` — Execute a command and parse the response
- L574-577 _public method_ `public static Task<PerforceResponseList<T>> CommandAsync<T>(this IPerforceConnection connection, string command, List<string> arguments, byte[]? inputData, CancellationToken cancellationToken = default) where T : class` — Execute a command and parse the response
- L588-606 _public method_ `public static async Task<PerforceResponseList<T>> BatchedCommandAsync<T>(IPerforceConnection connection, string command, IReadOnlyList<string> commonArguments, IReadOnlyList<string> batchedArguments, CancellationToken cancellationToken = default) where T : class` — Execute a command and parse the response
- L618-630 _private* method_ `static async Task<PerforceResponse> SingleResponseCommandAsync(IPerforceConnection connection, string command, IReadOnlyList<string> arguments, byte[]? inputData, Type? statRecordType, CancellationToken cancellationToken = default)` — Attempts to execute the given command, returning the results from the server or the first PerforceResponse object.
- L642-645 _public method_ `public static async Task<PerforceResponse<T>> SingleResponseCommandAsync<T>(IPerforceConnection connection, string command, List<string> arguments, byte[]? inputData, CancellationToken cancellationToken = default) where T : class` — Attempts to execute the given command, returning the results from the server or the first PerforceResponse object.
- L659-662 _public method_ `public static async Task<List<AddRecord>> AddAsync(this IPerforceConnection connection, int changeNumber, FileSpecList fileSpecList, CancellationToken cancellationToken = default)` — Adds files to a pending changelist.
- L674-677 _public method_ `public static async Task<List<AddRecord>> AddAsync(this IPerforceConnection connection, int changeNumber, string? fileType, AddOptions options, FileSpecList fileSpecList, CancellationToken cancellationToken = default)` — Adds files to a pending changelist.
- L687-690 _public method_ `public static Task<PerforceResponseList<AddRecord>> TryAddAsync(this IPerforceConnection connection, int changeNumber, FileSpecList fileSpecList, CancellationToken cancellationToken = default)` — Adds files to a pending changelist.
- L702-731 _public method_ `public static Task<PerforceResponseList<AddRecord>> TryAddAsync(this IPerforceConnection connection, int changeNumber, string? fileType, AddOptions options, FileSpecList fileNames, CancellationToken cancellationToken = default)` — Adds files to a pending changelist.
- L744-747 _public method_ `public static async Task<ChangeRecord> CreateChangeAsync(this IPerforceConnection connection, ChangeRecord record, CancellationToken cancellationToken = default)` — Creates a changelist with the p4 change command.
- L756-785 _public method_ `public static async Task<PerforceResponse<ChangeRecord>> TryCreateChangeAsync(this IPerforceConnection connection, ChangeRecord record, CancellationToken cancellationToken = default)` — Creates a changelist with the p4 change command.
- L795-798 _public method_ `public static async Task UpdateChangeAsync(this IPerforceConnection connection, UpdateChangeOptions options, ChangeRecord record, CancellationToken cancellationToken = default)` — Updates an existing changelist.
- L808-826 _public method_ `public static Task<PerforceResponse> TryUpdateChangeAsync(this IPerforceConnection connection, UpdateChangeOptions options, ChangeRecord record, CancellationToken cancellationToken = default)` — Updates an existing changelist.
- L836-839 _public method_ `public static async Task DeleteChangeAsync(this IPerforceConnection connection, DeleteChangeOptions options, int changeNumber, CancellationToken cancellationToken = default)` — Deletes a changelist (p4 change -d)
- L849-863 _public method_ `public static Task<PerforceResponse> TryDeleteChangeAsync(this IPerforceConnection connection, DeleteChangeOptions options, int changeNumber, CancellationToken cancellationToken = default)` — Deletes a changelist (p4 change -d)
- L873-876 _public method_ `public static async Task<ChangeRecord> GetChangeAsync(this IPerforceConnection connection, GetChangeOptions options, int changeNumber, CancellationToken cancellationToken = default)` — Gets a changelist
- L886-899 _public method_ `public static Task<PerforceResponse<ChangeRecord>> TryGetChange(this IPerforceConnection connection, GetChangeOptions options, int changeNumber, CancellationToken cancellationToken = default)` — Gets a changelist
- L907-938 _private* method_ `static byte[] SerializeRecord(this IPerforceConnection connection, ChangeRecord input)` — Serializes a change record to a byte array
- L954-957 _public method_ `public static async Task<List<ChangesRecord>> GetChangesAsync(this IPerforceConnection connection, ChangesOptions options, int maxChanges, ChangeStatus status, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Enumerates changes on the server
- L971-974 _public method_ `public static async Task<List<ChangesRecord>> GetChangesAsync(this IPerforceConnection connection, ChangesOptions options, string? clientName, int maxChanges, ChangeStatus status, string? userName, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Enumerates changes on the server
- L989-992 _public method_ `public static async Task<List<ChangesRecord>> GetChangesAsync(this IPerforceConnection connection, ChangesOptions options, string? clientName, int minChangeNumber, int maxChanges, ChangeStatus status, string? userName, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Enumerates changes on the server
- L1004-1007 _public method_ `public static Task<PerforceResponseList<ChangesRecord>> TryGetChangesAsync(this IPerforceConnection connection, ChangesOptions options, int maxChanges, ChangeStatus status, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Enumerates changes on the server
- L1021-1024 _public method_ `public static Task<PerforceResponseList<ChangesRecord>> TryGetChangesAsync(this IPerforceConnection connection, ChangesOptions options, string? clientName, int maxChanges, ChangeStatus status, string? userName, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Enumerates changes on the server
- L1039-1092 _public method_ `public static Task<PerforceResponseList<ChangesRecord>> TryGetChangesAsync(this IPerforceConnection connection, ChangesOptions options, string? clientName, int minChangeNumber, int maxChanges, ChangeStatus status, string? userName, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Enumerates changes on the server
- L1106-1109 _public method_ `public static async Task<List<CleanRecord>> CleanAsync(this IPerforceConnection connection, CleanOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Cleans the workspace
- L1119-1155 _public method_ `public static async Task<PerforceResponseList<CleanRecord>> TryCleanAsync(this IPerforceConnection connection, CleanOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Cleans the workspace
- L1168-1171 _public method_ `public static async Task CreateClientAsync(this IPerforceConnection connection, ClientRecord record, CancellationToken cancellationToken = default)` — Creates a client
- L1180-1183 _public method_ `public static Task<PerforceResponse> TryCreateClientAsync(this IPerforceConnection connection, ClientRecord record, CancellationToken cancellationToken = default)` — Creates a client
- L1192-1195 _public method_ `public static async Task UpdateClientAsync(this IPerforceConnection connection, ClientRecord record, CancellationToken cancellationToken = default)` — Creates a client
- L1204-1207 _public method_ `public static Task<PerforceResponse> TryUpdateClientAsync(this IPerforceConnection connection, ClientRecord record, CancellationToken cancellationToken = default)` — Update a client
- L1217-1220 _public method_ `public static async Task DeleteClientAsync(this IPerforceConnection connection, DeleteClientOptions options, string clientName, CancellationToken cancellationToken = default)` — Deletes a client
- L1230-1244 _public method_ `public static Task<PerforceResponse> TryDeleteClientAsync(this IPerforceConnection connection, DeleteClientOptions options, string clientName, CancellationToken cancellationToken = default)` — Deletes a client
- L1254-1257 _public method_ `public static async Task SwitchClientToStreamAsync(this IPerforceConnection connection, string streamName, SwitchClientOptions options, CancellationToken cancellationToken = default)` — Changes the stream associated with a client
- L1267-1277 _public method_ `public static Task<PerforceResponse> TrySwitchClientToStreamAsync(this IPerforceConnection connection, string streamName, SwitchClientOptions options, CancellationToken cancellationToken = default)` — Changes the stream associated with a client
- L1286-1289 _public method_ `public static async Task SwitchClientToTemplateAsync(this IPerforceConnection connection, string templateName, CancellationToken cancellationToken = default)` — Changes a client to mirror a template
- L1298-1303 _public method_ `public static Task<PerforceResponse> TrySwitchClientToTemplateAsync(this IPerforceConnection connection, string templateName, CancellationToken cancellationToken = default)` — Changes a client to mirror a template
- L1312-1315 _public method_ `public static async Task<ClientRecord> GetClientAsync(this IPerforceConnection connection, string? clientName, CancellationToken cancellationToken = default)` — Queries the current client definition
- L1324-1332 _public method_ `public static Task<PerforceResponse<ClientRecord>> TryGetClientAsync(this IPerforceConnection connection, string? clientName, CancellationToken cancellationToken = default)` — Queries the current client definition
- L1342-1345 _public method_ `public static async Task<ClientRecord> GetStreamViewAsync(this IPerforceConnection connection, string streamName, int changeNumber, CancellationToken cancellationToken = default)` — Queries the view for a stream
- L1356-1359 _public method_ `public static async Task<ClientRecord> GetStreamViewAsync(this IPerforceConnection connection, string? clientName, string streamName, int changeNumber, CancellationToken cancellationToken = default)` — Queries the view for a stream
- L1369-1372 _public method_ `public static Task<PerforceResponse<ClientRecord>> TryGetStreamViewAsync(this IPerforceConnection connection, string streamName, int changeNumber, CancellationToken cancellationToken = default)` — Queries the view for a stream
- L1383-1397 _public method_ `public static Task<PerforceResponse<ClientRecord>> TryGetStreamViewAsync(this IPerforceConnection connection, string? clientName, string streamName, int changeNumber, CancellationToken cancellationToken = default)` — Queries the view for a stream
- L1405-1453 _private* method_ `static byte[] SerializeRecord(this IPerforceConnection connection, ClientRecord input)` — Serializes a client record to a byte array
- L1467-1470 _public method_ `public static async Task<List<ClientsRecord>> GetClientsAsync(this IPerforceConnection connection, ClientsOptions options, string? userName, CancellationToken cancellationToken = default)` — Queries the current client definition
- L1480-1483 _public method_ `public static Task<PerforceResponseList<ClientsRecord>> TryGetClientsAsync(this IPerforceConnection connection, ClientsOptions options, string? userName, CancellationToken cancellationToken = default)` — Queries the current client definition
- L1496-1499 _public method_ `public static async Task<List<ClientsRecord>> GetClientsAsync(this IPerforceConnection connection, ClientsOptions options, string? filter, int maxResults, string? stream, string? userName, CancellationToken cancellationToken = default)` — Queries the current client definition
- L1512-1554 _public method_ `public static Task<PerforceResponseList<ClientsRecord>> TryGetClientsAsync(this IPerforceConnection connection, ClientsOptions options, string? filter, int maxResults, string? stream, string? userName, CancellationToken cancellationToken = default)` — Queries the current client definition
- L1569-1572 _public method_ `public static async Task<List<DeleteRecord>> DeleteAsync(this IPerforceConnection connection, int changeNumber, DeleteOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'delete' command
- L1583-1606 _public method_ `public static async Task<PerforceResponseList<DeleteRecord>> TryDeleteAsync(this IPerforceConnection connection, int changeNumber, DeleteOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'delete' command
- L1619-1622 _public method_ `public static Task<DepotRecord> GetDepotAsync(this IPerforceConnection connection, string depotName, CancellationToken cancellationToken = default)` — Queries the current depot definition
- L1631-1635 _public method_ `public static Task<PerforceResponse<DepotRecord>> TryGetDepotAsync(this IPerforceConnection connection, string depotName, CancellationToken cancellationToken = default)` — Queries the current depot definition
- L1648-1651 _public method_ `public static async Task<DescribeRecord> DescribeAsync(this IPerforceConnection connection, int changeNumber, CancellationToken cancellationToken = default)` — Describes a single changelist
- L1660-1668 _public method_ `public static async Task<PerforceResponse<DescribeRecord>> TryDescribeAsync(this IPerforceConnection connection, int changeNumber, CancellationToken cancellationToken = default)` — Describes a single changelist
- L1679-1683 _public method_ `public static async Task<DescribeRecord> DescribeAsync(this IPerforceConnection connection, DescribeOptions options, int maxNumFiles, int changeNumber, CancellationToken cancellationToken = default)` — Describes a single changelist
- L1694-1702 _public method_ `public static async Task<PerforceResponse<DescribeRecord>> TryDescribeAsync(this IPerforceConnection connection, DescribeOptions options, int maxNumFiles, int changeNumber, CancellationToken cancellationToken = default)` — Describes a single changelist
- L1711-1714 _public method_ `public static async Task<List<DescribeRecord>> DescribeAsync(this IPerforceConnection connection, int[] changeNumbers, CancellationToken cancellationToken = default)` — Describes a set of changelists
- L1723-1731 _public method_ `public static Task<PerforceResponseList<DescribeRecord>> TryDescribeAsync(this IPerforceConnection connection, int[] changeNumbers, CancellationToken cancellationToken = default)` — Describes a set of changelists
- L1742-1745 _public method_ `public static async Task<List<DescribeRecord>> DescribeAsync(this IPerforceConnection connection, DescribeOptions options, int maxNumFiles, int[] changeNumbers, CancellationToken cancellationToken = default)` — Describes a set of changelists
- L1756-1784 _public method_ `public static Task<PerforceResponseList<DescribeRecord>> TryDescribeAsync(this IPerforceConnection connection, DescribeOptions options, int maxNumFiles, int[] changeNumbers, CancellationToken cancellationToken = default)` — Describes a set of changelists
- L1799-1802 _public method_ `public static async Task<List<DirsRecord>> GetDirsAsync(this IPerforceConnection connection, DirsOptions options, string? stream, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — List directories under a depot path
- L1813-1839 _public method_ `public static Task<PerforceResponseList<DirsRecord>> TryGetDirsAsync(this IPerforceConnection connection, DirsOptions options, string? stream, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — List directories under a depot path
- L1853-1856 _public method_ `public static async Task<List<EditRecord>> EditAsync(this IPerforceConnection connection, int changeNumber, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Opens files for edit
- L1866-1869 _public method_ `public static Task<PerforceResponseList<EditRecord>> TryEditAsync(this IPerforceConnection connection, int changeNumber, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Opens files for edit
- L1881-1884 _public method_ `public static async Task<List<EditRecord>> EditAsync(this IPerforceConnection connection, int changeNumber, string? fileType, EditOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Opens files for edit
- L1896-1917 _public method_ `public static Task<PerforceResponseList<EditRecord>> TryEditAsync(this IPerforceConnection connection, int changeNumber, string? fileType, EditOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Opens files for edit
- L1931-1934 _public method_ `public static async Task<List<FileLogRecord>> FileLogAsync(this IPerforceConnection connection, FileLogOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'filelog' command
- L1944-1947 _public method_ `public static Task<PerforceResponseList<FileLogRecord>> TryFileLogAsync(this IPerforceConnection connection, FileLogOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'filelog' command
- L1958-1961 _public method_ `public static async Task<List<FileLogRecord>> FileLogAsync(this IPerforceConnection connection, int maxChanges, FileLogOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'filelog' command
- L1972-1975 _public method_ `public static Task<PerforceResponseList<FileLogRecord>> TryFileLogAsync(this IPerforceConnection connection, int maxChanges, FileLogOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'filelog' command
- L1987-1990 _public method_ `public static async Task<List<FileLogRecord>> FileLogAsync(this IPerforceConnection connection, int changeNumber, int maxChanges, FileLogOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'filelog' command
- L2002-2046 _public method_ `public static async Task<PerforceResponseList<FileLogRecord>> TryFileLogAsync(this IPerforceConnection connection, int changeNumber, int maxChanges, FileLogOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'filelog' command
- L2060-2063 _public method_ `public static async Task<List<FilesRecord>> FilesAsync(this IPerforceConnection connection, FilesOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'files' command
- L2073-2076 _public method_ `public static Task<PerforceResponseList<FilesRecord>> TryFilesAsync(this IPerforceConnection connection, FilesOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'files' command
- L2087-2090 _public method_ `public static async Task<List<FilesRecord>> FilesAsync(this IPerforceConnection connection, FilesOptions options, int maxFiles, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'files' command
- L2101-2128 _public method_ `public static async Task<PerforceResponseList<FilesRecord>> TryFilesAsync(this IPerforceConnection connection, FilesOptions options, int maxFiles, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'files' command
- L2141-2144 _public method_ `public static IAsyncEnumerable<FStatRecord> FStatAsync(this IPerforceConnection connection, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'fstat' command
- L2154-2157 _public method_ `public static IAsyncEnumerable<FStatRecord> FStatAsync(this IPerforceConnection connection, FStatOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'fstat' command
- L2167-2170 _public method_ `public static IAsyncEnumerable<PerforceResponse<FStatRecord>> TryFStatAsync(this IPerforceConnection connection, FStatOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'fstat' command
- L2181-2184 _public method_ `public static IAsyncEnumerable<FStatRecord> FStatAsync(this IPerforceConnection connection, int maxFiles, FStatOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'fstat' command
- L2195-2198 _public method_ `public static IAsyncEnumerable<PerforceResponse<FStatRecord>> TryFStatAsync(this IPerforceConnection connection, int maxFiles, FStatOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'fstat' command
- L2213-2216 _public method_ `public static IAsyncEnumerable<FStatRecord> FStatAsync(this IPerforceConnection connection, int afterChangeNumber, int onlyChangeNumber, string? filter, string? fields, int maxFiles, FStatOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'fstat' command
- L2231-2347 _public method_ `public static IAsyncEnumerable<PerforceResponse<FStatRecord>> TryFStatAsync(this IPerforceConnection connection, int afterChangeNumber, int onlyChangeNumber, string? filter, string? fields, int maxFiles, FStatOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'fstat' command
- L2360-2363 _public method_ `public static IAsyncEnumerable<HaveRecord> HaveAsync(this IPerforceConnection connection, FileSpecList fileSpec, CancellationToken cancellationToken = default)` — Determine files currently synced to the client
- L2372-2377 _public method_ `public static IAsyncEnumerable<PerforceResponse<HaveRecord>> TryHaveAsync(this IPerforceConnection connection, FileSpecList fileSpec, CancellationToken cancellationToken = default)` — Determine files currently synced to the client
- L2390-2393 _public method_ `public static async Task<InfoRecord> GetInfoAsync(this IPerforceConnection connection, InfoOptions options, CancellationToken cancellationToken = default)` — Execute the 'info' command
- L2402-2411 _public method_ `public static Task<PerforceResponse<InfoRecord>> TryGetInfoAsync(this IPerforceConnection connection, InfoOptions options, CancellationToken cancellationToken = default)` — Execute the 'info' command
- L2424-2427 _public method_ `public static async Task<LoginRecord> LoginAsync(this IPerforceConnection connection, string password, CancellationToken cancellationToken = default)` — Log in to the server
- L2436-2439 _public method_ `public static Task<PerforceResponse<LoginRecord>> TryLoginAsync(this IPerforceConnection connection, string? password, CancellationToken cancellationToken = default)` — Attempts to log in to the server
- L2451-2535 _public method_ `public static async Task<PerforceResponse<LoginRecord>> TryLoginAsync(this IPerforceConnection connection, LoginOptions options, string? user, string? password, string? host, CancellationToken cancellationToken = default)` — Attempts to log in to the server
- L2537-2548 _private* method_ `static void DiscardPasswordPrompt(IPerforceOutput output)`
- L2556-2559 _public method_ `public static async Task<LoginRecord> GetLoginStateAsync(this IPerforceConnection connection, CancellationToken cancellationToken = default)` — Gets the state of the current user's login
- L2567-2570 _public method_ `public static async Task<PerforceResponse<LoginRecord>> TryGetLoginStateAsync(this IPerforceConnection connection, CancellationToken cancellationToken = default)` — Gets the state of the current user's login
- L2587-2635 _public method_ `public static async Task<PerforceResponseList<MergeRecord>> MergeAsync(this IPerforceConnection connection, MergeOptions options, int change, int maxFiles, string sourceFileSpec, string targetFileSpec, CancellationToken cancellationToken = default)` — Execute the 'merge' command
- L2652-2655 _public method_ `public static async Task<List<MoveRecord>> MoveAsync(this IPerforceConnection connection, int changeNumber, string? fileType, MoveOptions options, string sourceFileSpec, string targetFileSpec, CancellationToken cancellationToken = default)` — Opens files for move
- L2668-2697 _public method_ `public static async Task<PerforceResponseList<MoveRecord>> TryMoveAsync(this IPerforceConnection connection, int changeNumber, string? fileType, MoveOptions options, string sourceFileSpec, string targetFileSpec, CancellationToken cancellationToken = default)` — Opens files for move
- L2711-2714 _public method_ `public static IAsyncEnumerable<OpenedRecord> OpenedAsync(this IPerforceConnection connection, OpenedOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'opened' command
- L2724-2727 _public method_ `public static IAsyncEnumerable<PerforceResponse<OpenedRecord>> TryOpenedAsync(this IPerforceConnection connection, OpenedOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'opened' command
- L2741-2744 _public method_ `public static IAsyncEnumerable<OpenedRecord> OpenedAsync(this IPerforceConnection connection, OpenedOptions options, int changeNumber, string? clientName, string? userName, int maxResults, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'opened' command
- L2758-2797 _public method_ `public static IAsyncEnumerable<PerforceResponse<OpenedRecord>> TryOpenedAsync(this IPerforceConnection connection, OpenedOptions options, int changeNumber, string? clientName, string? userName, int maxResults, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'opened' command
- L2811-2814 _public method_ `public static async Task<PrintRecord> PrintAsync(this IPerforceConnection connection, string outputFile, string fileSpec, CancellationToken cancellationToken = default)` — Execute the 'print' command
- L2824-2827 _public method_ `public static Task<PerforceResponseList<PrintRecord>> TryPrintAsync(this IPerforceConnection connection, string outputFile, string fileSpec, CancellationToken cancellationToken = default)` — Execute the 'print' command
- L2836-2859 _public method_ `public static async Task<PerforceResponse<PrintRecord<byte[]>>> TryPrintDataAsync(this IPerforceConnection connection, string fileSpec, CancellationToken cancellationToken = default)` — Execute the 'print' command
- L2868-2891 _public method_ `public static async Task<PerforceResponse<PrintRecord<string[]>>> TryPrintLinesAsync(this IPerforceConnection connection, string fileSpec, CancellationToken cancellationToken = default)` — Execute the 'print' command
- L2901-2909 _private* method_ `static async Task<PerforceResponseList<PrintRecord>> TryPrintInternalAsync(this IPerforceConnection connection, string outputFile, string fileSpec, CancellationToken cancellationToken = default)` — Execute the 'print' command
- L2919-2924 _private* method_ `static Task<PerforceResponse<T>> TryPrintSingleInternalAsync<T>(this IPerforceConnection connection, string outputFile, string fileSpec, CancellationToken cancellationToken = default) where T : class` — Execute the 'print' command for a single file
- L2939-2942 _public method_ `public static async Task<string> GetPropertyAsync(this IPerforceConnection connection, string propertyName, CancellationToken cancellationToken = default)` — Execute the 'property' command for a single value
- L2951-2956 _public method_ `public static async Task<PerforceResponse<PropertyRecord>> TryGetSinglePropertyAsync(this IPerforceConnection connection, string propertyName, CancellationToken cancellationToken = default)` — Execute the 'property' command for a single value
- L2971-2976 _public method_ `public static async Task<List<ReconcileRecord>> ReconcileAsync(this IPerforceConnection connection, int changeNumber, ReconcileOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Open files for add, delete, and/or edit in order to reconcile a workspace with changes made outside of Perforce.
- L2987-3031 _public method_ `public static async Task<PerforceResponseList<ReconcileRecord>> TryReconcileAsync(this IPerforceConnection connection, int changeNumber, ReconcileOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Open files for add, delete, and/or edit in order to reconcile a workspace with changes made outside of Perforce.
- L3046-3049 _public method_ `public static async Task<List<ReopenRecord>> ReopenAsync(this IPerforceConnection connection, int? changeNumber, string? fileType, string fileSpec, CancellationToken cancellationToken = default)` — Reopen a file
- L3060-3083 _public method_ `public static async Task<PerforceResponseList<ReopenRecord>> TryReopenAsync(this IPerforceConnection connection, int? changeNumber, string? fileType, string fileSpec, CancellationToken cancellationToken = default)` — Reopen a file
- L3097-3101 _public method_ `public static Task<List<PerforceResponse>> ReloadClient(this IPerforceConnection connection, string clientName, string sourceServerId, CancellationToken cancellationToken = default)` — Reloads a client workspace
- L3116-3119 _public method_ `public static async Task<List<ResolveRecord>> ResolveAsync(this IPerforceConnection connection, int changeNumber, ResolveOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Resolve conflicts between file revisions.
- L3130-3182 _public method_ `public static async Task<PerforceResponseList<ResolveRecord>> TryResolveAsync(this IPerforceConnection connection, int changeNumber, ResolveOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Resolve conflicts between file revisions.
- L3198-3201 _public method_ `public static async Task<List<RevertRecord>> RevertAsync(this IPerforceConnection connection, int changeNumber, string? clientName, RevertOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Reverts files that have been added to a pending changelist.
- L3213-3244 _public method_ `public static async Task<PerforceResponseList<RevertRecord>> TryRevertAsync(this IPerforceConnection connection, int changeNumber, string? clientName, RevertOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Reverts files that have been added to a pending changelist.
- L3257-3261 _public method_ `public static async Task<ServerRecord> GetServerAsync(this IPerforceConnection connection, string serverId, CancellationToken cancellationToken = default)` — Gets information about the specified server
- L3270-3274 _public method_ `public static Task<PerforceResponse<ServerRecord>> TryGetServerAsync(this IPerforceConnection connection, string serverId, CancellationToken cancellationToken = default)` — Gets information about the specified server
- L3289-3292 _public method_ `public static async Task<List<ShelveRecord>> ShelveAsync(this IPerforceConnection connection, int changeNumber, ShelveOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Shelves a set of files
- L3303-3319 _public method_ `public static async Task<PerforceResponseList<ShelveRecord>> TryShelveAsync(this IPerforceConnection connection, int changeNumber, ShelveOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Shelves a set of files
- L3329-3338 _public method_ `public static async Task DeleteShelvedFilesAsync(this IPerforceConnection connection, int changeNumber, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Deletes files from a shelved changelist
- L3348-3358 _public method_ `public static Task<List<PerforceResponse>> TryDeleteShelvedFilesAsync(this IPerforceConnection connection, int changeNumber, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Deletes files from a shelved changelist
- L3372-3375 _public method_ `public static async Task<List<SizesRecord>> SizesAsync(this IPerforceConnection connection, SizesOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'sizes' command
- L3385-3388 _public method_ `public static Task<PerforceResponseList<SizesRecord>> TrySizesAsync(this IPerforceConnection connection, SizesOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'sizes' command
- L3399-3402 _public method_ `public static async Task<List<SizesRecord>> SizesAsync(this IPerforceConnection connection, SizesOptions options, int maxLines, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'sizes' command
- L3414-3452 _public method_ `public static async Task<PerforceResponseList<SizesRecord>> TrySizesAsync(this IPerforceConnection connection, SizesOptions options, int maxLines, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Execute the 'sizes' command
- L3466-3469 _public method_ `public static async Task<StreamRecord> GetStreamAsync(this IPerforceConnection connection, string streamName, bool includeView, CancellationToken cancellationToken = default)` — Queries information about a stream
- L3479-3489 _public method_ `public static Task<PerforceResponse<StreamRecord>> TryGetStreamAsync(this IPerforceConnection connection, string streamName, bool includeView, CancellationToken cancellationToken = default)` — Queries information about a stream
- L3498-3502 _public method_ `public static Task<PerforceResponse> TryUpdateStreamAsync(this IPerforceConnection connection, StreamRecord record, CancellationToken cancellationToken = default)` — Updates an existing stream
- L3510-3551 _private* method_ `static byte[] SerializeRecord(this IPerforceConnection connection, StreamRecord input)` — Serializes a client record to a byte array
- L3566-3569 _public method_ `public static async Task<List<StreamLogRecord>> GetStreamLogAsync(this IPerforceConnection connection, StreamLogOptions options, int? changeNumber, int? maxChanges, string[] streams, CancellationToken cancellationToken = default)` — List revision history of streams
- L3581-3615 _public method_ `public static Task<PerforceResponseList<StreamLogRecord>> TryGetStreamLogAsync(this IPerforceConnection connection, StreamLogOptions options, int? changeNumber, int? maxChanges, string[] streams, CancellationToken cancellationToken = default)` — List revision history of streams
- L3627-3630 _public method_ `public static async Task<List<StreamsRecord>> GetStreamsAsync(this IPerforceConnection connection, string? streamPath, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L3639-3642 _public method_ `public static Task<PerforceResponseList<StreamsRecord>> TryGetStreamsAsync(this IPerforceConnection connection, string? streamPath, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L3654-3657 _public method_ `public static async Task<List<StreamsRecord>> GetStreamsAsync(this IPerforceConnection connection, string? streamPath, int maxResults, string? filter, bool unloaded, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L3669-3695 _public method_ `public static async Task<PerforceResponseList<StreamsRecord>> TryGetStreamsAsync(this IPerforceConnection connection, string? streamPath, int maxResults, string? filter, bool unloaded, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L3709-3712 _public method_ `public static async Task<SubmitRecord> SubmitAsync(this IPerforceConnection connection, int changeNumber, SubmitOptions options, CancellationToken cancellationToken = default)` — Submits a pending changelist
- L3722-3749 _public method_ `public static async Task<PerforceResponse<SubmitRecord>> TrySubmitAsync(this IPerforceConnection connection, int changeNumber, SubmitOptions options, CancellationToken cancellationToken = default)` — Submits a pending changelist
- L3758-3761 _public method_ `public static async Task<SubmitRecord> SubmitShelvedAsync(this IPerforceConnection connection, int changeNumber, CancellationToken cancellationToken = default)` — Submits a shelved changelist
- L3770-3776 _public method_ `public static async Task<PerforceResponse<SubmitRecord>> TrySubmitShelvedAsync(this IPerforceConnection connection, int changeNumber, CancellationToken cancellationToken = default)` — Submits a pending changelist
- L3778-3814 _private* method_ `static PerforceResponse<SubmitRecord> ParseSubmitResponses(PerforceResponseList<SubmitRecord> responses, ILogger logger)`
- L3827-3830 _public method_ `public static IAsyncEnumerable<SyncRecord> SyncAsync(this IPerforceConnection connection, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3839-3842 _public method_ `public static IAsyncEnumerable<PerforceResponse<SyncRecord>> TrySyncAsync(this IPerforceConnection connection, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3852-3855 _public method_ `public static IAsyncEnumerable<SyncRecord> SyncAsync(this IPerforceConnection connection, SyncOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3865-3868 _public method_ `public static IAsyncEnumerable<PerforceResponse<SyncRecord>> TrySyncAsync(this IPerforceConnection connection, SyncOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3879-3882 _public method_ `public static IAsyncEnumerable<SyncRecord> SyncAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3893-3896 _public method_ `public static IAsyncEnumerable<PerforceResponse<SyncRecord>> TrySyncAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3912-3915 _public method_ `public static IAsyncEnumerable<SyncRecord> SyncAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, int numThreads, int batch, int batchSize, int min, int minSize, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3931-3937 _public method_ `public static IAsyncEnumerable<PerforceResponse<SyncRecord>> TrySyncAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, int numThreads, int batch, int batchSize, int min, int minSize, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3948-3953 _public method_ `public static async Task<List<SyncSummaryRecord>> SyncQuietAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3964-3967 _public method_ `public static Task<PerforceResponseList<SyncSummaryRecord>> TrySyncQuietAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server
- L3983-3986 _public method_ `public static async Task<List<SyncSummaryRecord>> SyncQuietAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, int numThreads, int batch, int batchSize, int min, int minSize, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server without returning detailed file info
- L4002-4005 _public method_ `public static async Task<PerforceResponseList<SyncSummaryRecord>> TrySyncQuietAsync(this IPerforceConnection connection, SyncOptions options, int maxFiles, int numThreads, int batch, int batchSize, int min, int minSize, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Syncs files from the server without returning detailed file info
- L4022-4089 _private method_ `private static IAsyncEnumerable<PerforceResponse<T>> SyncInternalAsync<T>(this IPerforceConnection connection, SyncOptions options, int maxFiles, int numThreads, int batch, int batchSize, int min, int minSize, FileSpecList fileSpecs, bool quiet, CancellationToken cancellationToken = default) where T : class` — Gets arguments for a sync command
- L4108-4111 _public method_ `public static async Task<List<UnshelveRecord>> UnshelveAsync(this IPerforceConnection connection, int changeNumber, int intoChangeNumber, string? usingBranchSpec, string? usingStream, string? forceParentStream, UnshelveOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Restore shelved files from a pending change into a workspace
- L4126-4158 _public method_ `public static async Task<PerforceResponseList<UnshelveRecord>> TryUnshelveAsync(this IPerforceConnection connection, int changeNumber, int intoChangeNumber, string? usingBranchSpec, string? usingStream, string? forceParentStream, UnshelveOptions options, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Restore shelved files from a pending change into a workspace
- L4171-4174 _public method_ `public static async Task<UserRecord> GetUserAsync(this IPerforceConnection connection, string userName, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L4183-4187 _public method_ `public static Task<PerforceResponseList<UserRecord>> TryGetUserAsync(this IPerforceConnection connection, string userName, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L4201-4204 _public method_ `public static async Task<List<UsersRecord>> GetUsersAsync(this IPerforceConnection connection, UsersOptions options, int maxResults, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L4214-4241 _public method_ `public static async Task<PerforceResponseList<UsersRecord>> TryGetUsersAsync(this IPerforceConnection connection, UsersOptions options, int maxResults, CancellationToken cancellationToken = default)` — Enumerates all streams in a depot
- L4254-4257 _public method_ `public static IAsyncEnumerable<WhereRecord> WhereAsync(this IPerforceConnection connection, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Retrieves the location of a file of set of files in the workspace
- L4266-4270 _public method_ `public static IAsyncEnumerable<PerforceResponse<WhereRecord>> TryWhereAsync(this IPerforceConnection connection, FileSpecList fileSpecs, CancellationToken cancellationToken = default)` — Retrieves the location of a file of set of files in the workspace
- L4284-4287 _public method_ `public static async Task UndoChangeAsync(this IPerforceConnection connection, int changeNumberToUndo, int changeNumber, CancellationToken cancellationToken = default)` — perform undo on a changelist (p4 undo -c [targetCL] //...@undoCL)
- L4297-4302 _public method_ `public static async Task<PerforceResponseList<UndoRecord>> TryUndoChangeAsync(this IPerforceConnection connection, int changeNumberToUndo, int changeNumber, CancellationToken cancellationToken = default)` — perform undo on a changelist (p4 undo -c [targetCL] //...@undoCL)
- L4316-4319 _public method_ `public static async Task<List<AnnotateRecord>> AnnotateAsync(this IPerforceConnection connection, string fileSpec, AnnotateOptions options, CancellationToken cancellationToken = default)` — Runs the annotate p4 command
- L4329-4351 _public method_ `public static Task<PerforceResponseList<AnnotateRecord>> TryAnnotateAsync(this IPerforceConnection connection, string fileSpec, AnnotateOptions options, CancellationToken cancellationToken = default)` — Runs the annotate p4 command
- L4363-4366 _public method_ `public static async Task<string?> GetCurrentStreamAsync(this IPerforceConnection connection, CancellationToken cancellationToken = default)` — Gets the current stream that a client is connected to
- L4374-4385 _public method_ `public static async Task<string?> TryGetCurrentStreamAsync(this IPerforceConnection connection, CancellationToken cancellationToken = default)` — Gets the current stream that a client is connected to

### `Source/Programs/Shared/EpicGames.Perforce/PerforceEnvironment.cs` (EpicGames.Perforce)


#### interface `EpicGames.Perforce.IPerforceEnvironment`  
`public interface IPerforceEnvironment`  
_public; L18-26_
- desc: Interface describing a set of perforce environment settings
- L25 _public* method_ `string? GetValue(string name)` — Get the value of a particular variable

#### class `EpicGames.Perforce.GlobalPerforceEnvironment`  
`public class GlobalPerforceEnvironment : IPerforceEnvironment`  
_public; L31-62_
- inherits: `IPerforceEnvironment`
- desc: The global Perforce environment
- L36 _protected property_ `protected Dictionary<string, string> Variables { get; }` — Environment variables in the global environment
- L41-54 _public ctor_ `public GlobalPerforceEnvironment()` — Constructor
- L57-61 _public method_ `public string? GetValue(string name)` — (inheritdoc)

#### class `EpicGames.Perforce.WindowsGlobalPerforceEnvironment`  
`class WindowsGlobalPerforceEnvironment : GlobalPerforceEnvironment`  
_internal*; L67-89_
- inherits: `GlobalPerforceEnvironment`
- desc: Default global environment used by Linux and MacOS, which reads settings from the registry.
- L69-88 _public ctor_ `public WindowsGlobalPerforceEnvironment()`

#### class `EpicGames.Perforce.PerforceEnvironmentFile`  
`public class PerforceEnvironmentFile : IPerforceEnvironment`  
_public; L95-145_
- attrs: `[DebuggerDisplay("{Location}")]`
- inherits: `IPerforceEnvironment`
- desc: Environment variables read from a file
- L100 _public property_ `public IPerforceEnvironment Parent { get; }` — The parent environment block
- L105 _public property_ `public FileReference Location { get; }` — Location of the file containing these variables
- L107 _private* field_ `readonly Dictionary<string, string> _variables = ...`
- L107 _private* field_ `readonly Dictionary< _variables = new(StringComparer.OrdinalIgnoreCase)`
- L114-131 _internal ctor_ `internal PerforceEnvironmentFile(IPerforceEnvironment parent, FileReference location)` — Constructor
- L134-144 _public method_ `public string? GetValue(string name)` — (inheritdoc)

#### class `EpicGames.Perforce.PerforceEnvironment`  
`public static class PerforceEnvironment`  
_public; L150-226_
- desc: Static methods for retrieving the Perforce environment
- L155 _public property_ `public static IPerforceEnvironment Default { get; }` — Default environment regardless of directroy.
- L157 _private* field_ `static readonly Dictionary<DirectoryReference, IPerforceEnvironment> s_directoryToEnvironment = ...`
- L157 _private* field_ `static readonly Dictionary< s_directoryToEnvironment = []`
- L159-191 _private* method_ `static IPerforceEnvironment CreateDefaultEnvironment()`
- L198-225 _public method_ `public static IPerforceEnvironment FromDirectory(DirectoryReference directory)` — Read the default Perforce settings reading any config file from the given directory

### `Source/Programs/Shared/EpicGames.Perforce/PerforceError.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.PerforceSeverityCode`  
`public enum PerforceSeverityCode`  
_public; L12-19_
- desc: Error severity codes. Taken from the p4java documentation.
- L14 _public* enumerator_ `Empty = 0`
- L15 _public* enumerator_ `Info = 1`
- L16 _public* enumerator_ `Warning = 2`
- L17 _public* enumerator_ `Failed = 3`
- L18 _public* enumerator_ `Fatal = 4`

#### enum `EpicGames.Perforce.PerforceGenericCode`  
`public enum PerforceGenericCode`  
_public; L24-41_
- desc: Generic error codes that can be returned by the Perforce server. Taken from the p4java documentation.
- L26 _public* enumerator_ `None = 0`
- L27 _public* enumerator_ `Usage = 1`
- L28 _public* enumerator_ `Unknown = 2`
- L29 _public* enumerator_ `Context = 3`
- L30 _public* enumerator_ `Illegal = 4`
- L31 _public* enumerator_ `NotYet = 5`
- L32 _public* enumerator_ `Protect = 6`
- L33 _public* enumerator_ `Empty = 17`
- L34 _public* enumerator_ `Fault = 33`
- L35 _public* enumerator_ `Client = 34`
- L36 _public* enumerator_ `Admin = 35`
- L37 _public* enumerator_ `Config = 36`
- L38 _public* enumerator_ `Upgrade = 37`
- L39 _public* enumerator_ `Comm = 38`
- L40 _public* enumerator_ `TooBig = 39`

#### class `EpicGames.Perforce.PerforceError`  
`public class PerforceError`  
_public; L48-84_
- desc: Represents a error return value from Perforce.
- L54 _public property_ `public PerforceSeverityCode Severity { get; set; }` — attrs: `[PerforceTagAttribute("severity")]` — The severity of this error
- L60 _public property_ `public PerforceGenericCode Generic { get; set; }` — attrs: `[PerforceTagAttribute("generic")]` — The generic error code associated with this message
- L66 _public property_ `public string Data { get; set; }` — attrs: `[PerforceTagAttribute("data")]` — The message text
- L71-74 _private ctor_ `private PerforceError()` — Private constructor for serialization
- L80-83 _public method_ `public override string ToString()` — Formats this error for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/PerforceException.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceException`  
`public class PerforceException : Exception`  
_public; L10-54_
- inherits: `Exception`
- desc: Represents an exception specific to perforce
- L15 _public property_ `public PerforceError? Error { get; set; }` — For errors returned by the server, contains the error record
- L21-24 _public ctor_ `public PerforceException(string message) : base(message)` — Constructor
- L31-34 _public ctor_ `public PerforceException(string format, params object[] args) : base(String.Format(format, args))` — Constructor
- L40-44 _public ctor_ `public PerforceException(PerforceError error) : base(error.ToString())` — Constructor
- L49-53 _public ctor_ `public PerforceException(string message, PerforceException innerException) : base(message, innerException)` — Constructor

### `Source/Programs/Shared/EpicGames.Perforce/PerforceInfo.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceInfo`  
`public class PerforceInfo`  
_public; L8-32_
- desc: Generic class for parsing "info" responses from Perforce
- L14 _public property_ `public string Data { get; set; }` — attrs: `[PerforceTag("data")]` — Message data
- L19-22 _private ctor_ `private PerforceInfo()` — Private constructor for serialization
- L28-31 _public method_ `public override string? ToString()` — Formats this error for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/PerforceIo.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.PerforceIoCommand`  
`public enum PerforceIoCommand`  
_public; L10-35_
- L16 _public* enumerator_ `Open` — attrs: `[PerforceEnum("open")]`
- L22 _public* enumerator_ `Write` — attrs: `[PerforceEnum("write")]`
- L28 _public* enumerator_ `Close` — attrs: `[PerforceEnum("close")]`
- L34 _public* enumerator_ `Unlink` — attrs: `[PerforceEnum("unlink")]`

#### class `EpicGames.Perforce.PerforceIo`  
`public class PerforceIo`  
_public; L40-59_
- L46 _public property_ `public int File { get; set; }` — attrs: `[PerforceTagAttribute("file")]` — The severity of this error
- L52 _public property_ `public PerforceIoCommand Command { get; set; }` — attrs: `[PerforceTagAttribute("command")]` — The generic error code associated with this message
- L58 _public property_ `public ReadOnlyMemory<byte> Payload { get; set; }` — attrs: `[PerforceTagAttribute("payload")]` — The message text

### `Source/Programs/Shared/EpicGames.Perforce/PerforceMetadataLogger.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceMetadataLogger`  
`public class PerforceMetadataLogger : ILogger`  
_public; L16-248_
- inherits: `ILogger`
- desc: Logger which adds Perforce depot path and changelist information to file annotations
- L32 _private* field_ `readonly ILogger _inner`
- L33 _private* field_ `readonly List<ClientView> _clients = []`
- L38 _public property_ `public ILogger Inner => ...` — Accessor for the inner logger
- L44-47 _public ctor_ `public PerforceMetadataLogger(ILogger inner)` — Constructor
- L55-60 _public method_ `public void AddClientView(DirectoryReference baseDir, string depotPath, int change)` — Adds a new client to be included in the mapping
- L65-68 _public method_ `public void AddClientView(DirectoryReference baseDir, PerforceViewMap viewMap, int change)` — Adds a new client to be included in the mapping
- L71-83 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)
- L86 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L89 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L91-121 _private* method_ `static bool ReadFirstLogProperty(ref Utf8JsonReader reader)`
- L123-148 _private* method_ `static bool ReadNextLogProperty(ref Utf8JsonReader reader)`
- L150 _private* field_ `static readonly Utf8String s_sourceFileType = LogValueType.SourceFile`
- L151 _private* field_ `static readonly Utf8String s_assetType = LogValueType.Asset`
- L153 _private* field_ `static readonly Utf8String s_file = new("file")`
- L155-214 _private* method_ `ReadOnlyMemory<byte> Annotate(ReadOnlyMemory<byte> data)`
- L216-247 _private* method_ `byte[]? GetAnnotations(ReadOnlySpan<byte> type, ReadOnlySpan<byte> text, string? file)`

#### class `EpicGames.Perforce.PerforceMetadataLogger.ClientView`  
`class ClientView`  
_private*; L18-30_
- L20 _public field_ `public readonly DirectoryReference BaseDir`
- L21 _public field_ `public readonly PerforceViewMap ViewMap`
- L22 _public field_ `public readonly int Change`
- L24-29 _public ctor_ `public ClientView(DirectoryReference baseDir, PerforceViewMap viewMap, int change)`

### `Source/Programs/Shared/EpicGames.Perforce/PerforceRecord.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.PerforceValueType`  
`public enum PerforceValueType`  
_public; L18-29_
- desc: The type of a value returned by Perforce
- L23 _public* enumerator_ `String` — A utf-8 encoded string
- L28 _public* enumerator_ `Integer` — A 32-bit integer

#### struct `EpicGames.Perforce.PerforceValue`  
`public readonly struct PerforceValue`  
_public; L34-227_
- desc: Wrapper for values returned by Perforce
- L39 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — The raw data for the value, including type, size, and payload
- L45-48 _public ctor_ `public PerforceValue(ReadOnlyMemory<byte> data)` — Constructor
- L54-64 _public ctor_ `public PerforceValue(string text)` — Create a value from a string
- L70 _public property_ `public bool IsEmpty => ...` — Determines if the value is empty
- L75-89 _public property_ `public PerforceValueType Type { get; }` — Accessor for the type of value stored by this struct
- L95-99 _public method_ `public bool AsBool()` — Converts the value to a boolean
- L105-142 _public method_ `public int AsInteger()` — Converts the value to an integer
- L148-160 _public method_ `public long AsLong()` — Converts this value to a long
- L166-170 _public method_ `public DateTimeOffset AsDateTimeOffset()` — Converts this value to a DateTimeOffset
- L176-187 _public method_ `public Utf8String AsString()` — Converts this value to a string
- L193-200 _public method_ `public int GetInteger()` — Gets the contents of this string
- L206-217 _public method_ `public Utf8String GetString()` — Gets the contents of this string
- L223-226 _public method_ `public override string ToString()` — Convert to a string

#### class `EpicGames.Perforce.PerforceRecord`  
`public class PerforceRecord`  
_public; L232-373_
- desc: Low-overhead record type for generic responses
- L237 _public property_ `public List<KeyValuePair<Utf8String, PerforceValue>> Rows { get; }` — The rows in this record
- L245-271 _public method_ `public static PerforceRecord FromFields(IEnumerable<KeyValuePair<string, object>> fields, bool numberedListElements)` — Create a record from a set of fields
- L278-315 _public method_ `public void CopyInto(Utf8String[] keys, PerforceValue[] values)` — Copy this record into the given array of values. This method is O(n) if every record key being in the list of keys in the same order, but O(n^2) if not.
- L321-337 _public method_ `public byte[] Serialize()` — Serialize to a single block of data
- L344-372 _public method_ `public static byte[] Serialize(List<KeyValuePair<string, object>> keyValuePairs)` — Serializes a list of key/value pairs into binary format.

### `Source/Programs/Shared/EpicGames.Perforce/PerforceReflection.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.StringConstants`  
`static class StringConstants`  
_internal*; L20-27_
- desc: String constants for perforce values
- L22 _public field_ `public static readonly Utf8String True = new("true")`
- L23 _public field_ `public static readonly Utf8String False = new("false")`
- L24 _public field_ `public static readonly Utf8String New = new("new")`
- L25 _public field_ `public static readonly Utf8String None = new("none")`
- L26 _public field_ `public static readonly Utf8String Default = new("default")`

#### record struct `EpicGames.Perforce.NestedRecordInfo`  
`record struct NestedRecordInfo(PropertyInfo PropertyInfo, CreateRecordDelegate CreateInstance)`  
_internal*; L38-38_
- desc: Information about a nested record

#### record struct `EpicGames.Perforce.TaggedPropertyNameAndRank`  
`record struct TaggedPropertyNameAndRank(Utf8String Tag, int Rank)`  
_internal*; L43-43_
- desc: Name and rank of a tagged property within a record

#### class `EpicGames.Perforce.TaggedPropertyInfo`  
`class TaggedPropertyInfo`  
_internal*; L48-124_
- desc: Stores cached information about a property with a PerforceTagAttribute attribute.
- L53 _public property_ `public Utf8String Tag { get; }` — Name of the tag. Specified in the attribute or inferred from the field name.
- L58 _public property_ `public bool Optional { get; }` — Whether this tag is optional or not.
- L63 _public property_ `public NestedRecordInfo[] ParentRecords { get; }` — List of nested records before getting to the target object
- L68 _public property_ `public PropertyInfo PropertyInfo { get; }` — The property containing the value of this data.
- L73 _public property_ `public Action<IMemoryWriter, object> Write { get; set; }` — Writes an instance of this field from an object
- L78 _public property_ `public Action<object, int> ReadFromInteger { get; set; }` — Parser for this field type
- L83 _public property_ `public Action<object, Utf8String> ReadFromString { get; set; }` — Parser for this field type
- L88 _public property_ `public ulong RequiredTagBitMask { get; }` — Index into the bitmask of required types
- L98-108 _public ctor_ `public TaggedPropertyInfo(Utf8String name, bool optional, NestedRecordInfo[] parentRecords, PropertyInfo propertyInfo, ulong requiredTagBitMask)` — Constructor
- L111-123 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Perforce.CachedRecordInfo`  
`class CachedRecordInfo`  
_internal*; L129-166_
- desc: Stores cached information about a record
- L134 _public property_ `public Type Type { get; }` — Type of the record
- L139 _public property_ `public CreateRecordDelegate CreateInstance { get; }` — Method to construct this record
- L144 _public property_ `public List<TaggedPropertyInfo> Properties { get; }` — List of fields in the record. These should be ordered to match P4 output for maximum efficiency.
- L149 _public property_ `public Dictionary<TaggedPropertyNameAndRank, TaggedPropertyInfo> NameAndRankToInfo { get; set; }` — Map of name to tag info
- L154 _public property_ `public ulong RequiredTagsBitMask { get; set; }` — Bitmask of all the required tags. Formed by bitwise-or'ing the RequiredTagBitMask fields for each required CachedTagInfo.
- L161-165 _public ctor_ `public CachedRecordInfo(Type type, CreateRecordDelegate createInstance)` — Constructor

#### class `EpicGames.Perforce.CachedEnumInfo`  
`class CachedEnumInfo`  
_internal*; L171-347_
- desc: Information about an enum
- L176 _public field_ `public Type _enumType` — The enum type
- L181 _public field_ `public bool _bHasFlagsAttribute` — Whether the enum has the [Flags] attribute
- L186 _public field_ `public Dictionary<Utf8String, int> _nameToValue = ...` — Map of name to value
- L186 _public field_ `public Dictionary< _nameToValue = []` — Map of name to value
- L191 _public field_ `public Dictionary<int, Utf8String> _valueToName = ...` — Map of value to name
- L191 _public field_ `public Dictionary< _valueToName = []` — Map of value to name
- L196 _public field_ `public List<KeyValuePair<string, int>> _nameValuePairs = ...` — List of name/value pairs
- L196 _public field_ `public List<KeyValuePair< _nameValuePairs = []` — List of name/value pairs
- L202-225 _public ctor_ `public CachedEnumInfo(Type enumType)` — Constructor
- L232 _public method_ `public Utf8String GetName(int value)` — Gets the name of a particular enum value
- L239-242 _public method_ `public object ParseInteger(int value)` — Parses the given integer as an enum
- L249-252 _public method_ `public object ParseString(Utf8String text)` — Parses the given text as an enum
- L259-298 _public method_ `public int ParseToInteger(Utf8String name)` — Parses the given text as an enum
- L305-346 _public method_ `public string GetEnumText(int value)` — Parses an enum value, using PerforceEnumAttribute markup for names.

#### class `EpicGames.Perforce.PerforceReflection`  
`static class PerforceReflection`  
_internal*; L352-675_
- desc: Utility methods for converting to/from native types
- L357 _public field_ `public static readonly DateTime UnixEpoch = new(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)` — Unix epoch; used for converting times back into C# datetime objects
- L362 _public const_ `public const int DefaultChange = -2` — Constant for the default changelist, where valid.
- L367 _private* field_ `static readonly ConcurrentDictionary<Type, CachedEnumInfo> s_enumTypeToInfo = ...` — Cached map of enum types to a lookup mapping from p4 strings to enum values.
- L367 _private* field_ `static readonly ConcurrentDictionary< s_enumTypeToInfo = new()` — Cached map of enum types to a lookup mapping from p4 strings to enum values.
- L372 _private* field_ `static readonly ConcurrentDictionary<Type, CachedRecordInfo> s_recordTypeToInfo = ...` — Cached set of record
- L372 _private* field_ `static readonly ConcurrentDictionary< s_recordTypeToInfo = new()` — Cached set of record
- L377 _public field_ `public static CachedRecordInfo InfoRecordInfo = GetCachedRecordInfo(typeof(PerforceInfo))` — Default type for info
- L382 _public field_ `public static CachedRecordInfo ErrorRecordInfo = GetCachedRecordInfo(typeof(PerforceError))` — Default type for errors
- L387 _public field_ `public static CachedRecordInfo IoRecordInfo = GetCachedRecordInfo(typeof(PerforceIo))` — Default type for errors
- L394-406 _public method_ `public static void Serialize(object obj, IMemoryWriter writer)` — Serializes a sequence of objects to a stream
- L408-413 _private* method_ `static void WriteIntegerWithTag(IMemoryWriter writer, int value)`
- L415-422 _private* method_ `static void WriteStringWithTag(IMemoryWriter writer, string str)`
- L424-430 _private* method_ `static void WriteUtf8StringWithTag(IMemoryWriter writer, Utf8String str)`
- L437-449 _private* method_ `static CachedEnumInfo GetCachedEnumInfo(Type enumType)` — Gets a mapping of flags to enum values for the given type
- L457-460 _public method_ `public static string GetEnumText(Type enumType, object value)` — Parses an enum value, using PerforceEnumAttribute markup for names.
- L467-485 _public method_ `public static CachedRecordInfo GetCachedRecordInfo(Type recordType)` — Gets reflection data for the given record type
- L487-586 _private* method_ `static void AddRecordProperties(Type recordType, CachedRecordInfo rootRecord, NestedRecordInfo[] parentRecords)`
- L588-601 _private* method_ `static CreateRecordDelegate GetCreateRecordDelegate(Type type)`
- L603-606 _private* method_ `static string ParseString(Utf8String str)`
- L608-621 _private* method_ `static DateTime ParseStringAsDateTime(Utf8String str)`
- L623-626 _private* method_ `static object ParseStringAsBool(Utf8String str)`
- L628-631 _private* method_ `static object ParseStringAsNullableBool(Utf8String str)`
- L633-657 _private* method_ `static object ParseStringAsInt(Utf8String str)`
- L659-668 _private* method_ `static long ParseStringAsLong(Utf8String str)`
- L670-674 _private* method_ `static DateTimeOffset ParseStringAsDateTimeOffset(Utf8String str)`

#### Namespace-level symbols

- L33 _public delegate_ `public delegate object CreateRecordDelegate()` — Delegate type for creating a record instance

### `Source/Programs/Shared/EpicGames.Perforce/PerforceResponse.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceResponse`  
`public class PerforceResponse`  
_public; L12-87_
- desc: Base class for returning untyped response data
- L17 _protected property_ `protected object InternalData { get; }` — Stores the response data
- L23-26 _public ctor_ `public PerforceResponse(object data)` — Constructor
- L32 _public property_ `public bool Succeeded => ...` — True if the response is successful
- L38 _public property_ `public bool Failed => ...` — True if the response is an error
- L43-50 _public property_ `public object Data { get; }` — Accessor for the successful response data. Throws an exception if the response is an error.
- L55 _public property_ `public PerforceInfo? Info => ...` — Returns the info data.
- L60 _public property_ `public PerforceError? Error => ...` — Returns the error data, or null if this is a succesful response.
- L65 _public property_ `public PerforceIo? Io => ...` — Returns the io data, or null if this is a regular response.
- L70-77 _public method_ `public void EnsureSuccess()` — Throws an exception if the response is an error
- L83-86 _public method_ `public override string? ToString()` — Returns a string representation of this object for debugging

#### class `EpicGames.Perforce.PerforceResponse`  
`public class PerforceResponse<T> : PerforceResponse where T : class`  
_public; L94-159_
- inherits: `PerforceResponse`
- constraints: `where T : class`
- desc: Represents a successful Perforce response of the given type, or an error. Throws a PerforceException with the error text if the response value is attempted to be accessed and an error has occurred.
- L100-103 _public ctor_ `public PerforceResponse(T data) : base(data)` — Constructor
- L109-112 _public ctor_ `public PerforceResponse(PerforceInfo info) : base(info)` — Constructor
- L118-121 _public ctor_ `public PerforceResponse(PerforceError error) : base(error)` — Constructor
- L127-131 _public ctor_ `public PerforceResponse(PerforceResponse untypedResponse) : base(untypedResponse.Error ?? untypedResponse.Info ?? (object)(T)untypedResponse.Data)` — Construct a typed response from an untyped response
- L136-158 _public property_ `public new T Data { get; }` — Accessor for the succcessful response data. Throws an exception if the response is an error.

#### class `EpicGames.Perforce.PerforceResponseExtensions`  
`public static class PerforceResponseExtensions`  
_public; L164-207_
- desc: Extension methods for responses
- L169-172 _public method_ `public static bool Succeeded<T>(this IEnumerable<PerforceResponse<T>> responses) where T : class` — Whether all responses in this list are successful
- L177-187 _public method_ `public static IEnumerable<PerforceError> GetErrors<T>(this IEnumerable<PerforceResponse<T>> responses) where T : class` — Sequence of all the error responses.
- L192-198 _public method_ `public static void EnsureSuccess<T>(this IEnumerable<PerforceResponse<T>> responses) where T : class` — Throws an exception if any response is an error
- L203-206 _public method_ `public static async Task<T> UnwrapAsync<T>(this Task<PerforceResponse<T>> response) where T : class` — Unwrap a task returning a response object

### `Source/Programs/Shared/EpicGames.Perforce/PerforceResponseList.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceResponseList`  
`public class PerforceResponseList<T> : List<PerforceResponse<T>> where T : class`  
_public; L13-88_
- inherits: `List<PerforceResponse<T>>`
- constraints: `where T : class`
- desc: Represents a list of responses from the Perforce server. Within the list, individual responses may indicate success or failure.
- L18-20 _public ctor_ `public PerforceResponseList()` — Default constructor
- L26-29 _public ctor_ `public PerforceResponseList(IEnumerable<PerforceResponse<T>> responses) : base(responses)` — Constructor
- L34 _public property_ `public bool Succeeded => ...` — Whether all responses in this list are successful
- L39 _public property_ `public PerforceError? FirstError => ...` — Returns the first error, or null.
- L44-58 _public property_ `public List<T> Data { get; }` — Sequence of all the data objects from the responses.
- L63-76 _public property_ `public IEnumerable<PerforceError> Errors { get; }` — Sequence of all the error responses.
- L81-87 _public method_ `public void EnsureSuccess()` — Throws an exception if any response is an error

### `Source/Programs/Shared/EpicGames.Perforce/PerforceSettings.cs` (EpicGames.Perforce)


#### interface `EpicGames.Perforce.IPerforceSettings`  
`public interface IPerforceSettings`  
_public; L13-59_
- desc: Settings for a new Perforce connection
- L18 _public property_ `public string ServerAndPort { get; }` — Server and port to connect to
- L23 _public property_ `public string UserName { get; }` — Username to log in with
- L28 _public property_ `public string? Password { get; }` — Password to use
- L33 _public property_ `public string? HostName { get; }` — Name of the current host
- L38 _public property_ `public string? ClientName { get; }` — Name of the client to use
- L43 _public property_ `public string? AppName { get; }` — The invoking application name
- L48 _public property_ `public string? AppVersion { get; }` — The invoking application version
- L53 _public property_ `public bool PreferNativeClient { get; }` — Whether to create a native client rather than running the p4 child process, if possible
- L58 _public property_ `public bool EnableHangMonitor { get; }` — Whether to monitor the connection for commands that are not producing any output

#### class `EpicGames.Perforce.PerforceSettings`  
`public class PerforceSettings : IPerforceSettings`  
_public; L64-172_
- inherits: `IPerforceSettings`
- desc: Settings for a new Perforce connection
- L66 _private* field_ `static readonly Assembly? s_entryAssembly = Assembly.GetEntryAssembly()`
- L68 _private* field_ `string? _appName`
- L69 _private* field_ `string? _appVersion`
- L74 _public property_ `public static IPerforceSettings Default { get; }` — The default settings
- L79 _public property_ `public static string? DefaultAppName { get; set; }` — Default app name to use for new settings objects
- L84 _public property_ `public static string? DefaultAppVersion { get; set; }` — Default version string to use for new settings objects
- L87 _public property_ `public string ServerAndPort { get; set; }` — (inheritdoc)
- L90 _public property_ `public string UserName { get; set; }` — (inheritdoc)
- L93 _public property_ `public string? Password { get; set; }` — (inheritdoc)
- L96 _public property_ `public string? HostName { get; set; }` — (inheritdoc)
- L99 _public property_ `public string? ClientName { get; set; }` — (inheritdoc)
- L102-106 _public property_ `public string? AppName { get; set; }` — (inheritdoc)
- L109-113 _public property_ `public string? AppVersion { get; set; }` — (inheritdoc)
- L116 _public property_ `public bool PreferNativeClient { get; set; }` — (inheritdoc)
- L119 _public property_ `public bool EnableHangMonitor { get; set; }` — (inheritdoc)
- L124-132 _public ctor_ `public PerforceSettings(IPerforceEnvironment environment)` — Default constructor
- L139-144 _public ctor_ `public PerforceSettings(string serverAndPort, string userName)` — Constructor
- L149-160 _public ctor_ `public PerforceSettings(IPerforceSettings other)` — Copy constructor
- L167-171 _public method_ `public static PerforceSettings FromDirectory(DirectoryReference directory)` — Get the Perforce settings for a particular directory, reading any necessary P4CONFIG and P4ENVIRO files

#### class `EpicGames.Perforce.PerforceSettingExtensions`  
`public static class PerforceSettingExtensions`  
_public; L177-220_
- desc: Extension methods for setting objects
- L182-198 _public method_ `public static IPerforceSettings MergeWith(this IPerforceSettings settings, string? newServerAndPort = null, string? newUserName = null, string? newClientName = null)` — Update common fields in a IPerforceSettings object
- L206-219 _public method_ `public static string GetArgumentsForExternalProgram(this IPerforceSettings settings, bool includeClient)` — Gets the command line arguments to launch an external program, such as P4V or P4VC

### `Source/Programs/Shared/EpicGames.Perforce/PerforceUtils.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceUtils`  
`public static class PerforceUtils`  
_public; L14-222_
- desc: Utility methods for dealing with Perforce paths
- L19 _public field_ `public static readonly HashSet<string> CodeExtensions = [ ".c", ".cc", ".cpp", ".inl", ".m", ".mm", ".rc", ".cs", ".csproj", ".h", ".hpp", ".inl", ".usf", ".ush", ".uproject", ".uplugin", ".sln", ".native.verse" ]` — Set of extensions to treat as code
- L46-56 _public method_ `public static bool IsCodeFile(string path)` — Tests if a path is a code file
- L61-69 _public method_ `public static string EscapePath(string path)` — Escape a path to Perforce syntax
- L74-83 _public method_ `public static string UnescapePath(string path)` — Remove escape characters from a path
- L88-129 _public method_ `public static Utf8String UnescapePath(Utf8String path)` — Remove escape characters from a UTF8 path
- L137-140 _public method_ `public static bool TryGetDepotName(string depotPath, [NotNullWhen(true)] out string? depotName)`
- L148-165 _public method_ `public static bool TryGetClientName(string clientPath, [NotNullWhen(true)] out string? clientName)`
- L172-183 _public method_ `public static string GetClientOrDepotDirectoryName(string clientFile)`
- L191-205 _public method_ `public static string GetClientRelativePath(string clientFile)` — Get the relative path of a client file (eg. //ClientName/Foo/Bar.txt -> Foo/Bar.txt)
- L213-221 _public method_ `public static string GetClientRelativePath(DirectoryReference workspaceRoot, FileReference workspaceFile)` — Get the relative path within a client from a filename

### `Source/Programs/Shared/EpicGames.Perforce/PerforceViewFilter.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceViewFilter`  
`public class PerforceViewFilter`  
_public; L14-64_
- desc: Filters a view of files
- L19 _public property_ `public List<PerforceViewFilterEntry> Entries { get; }` — List of entries making up the view
- L25-35 _public ctor_ `public PerforceViewFilter(IEnumerable<PerforceViewFilterEntry> entries)` — Construct from an existing set of entries
- L41-44 _public method_ `public static PerforceViewFilter Parse(IEnumerable<string> entries)` — Construct a view filter from a set of entries
- L52-63 _public method_ `public bool IncludeFile(string file, StringComparison comparison)` — Determines if a file is included in the view

#### class `EpicGames.Perforce.PerforceViewFilterEntry`  
`public class PerforceViewFilterEntry`  
_public; L69-203_
- desc: Entry within a view filter
- L74 _public property_ `public bool Include { get; }` — Whether to include files matching this pattern
- L79 _public property_ `public string Wildcard { get; }` — The wildcard string - either '*' or '...'
- L84 _public property_ `public string Prefix { get; }` — The part of pattern before the wildcard
- L89 _public property_ `public string Suffix { get; }` — The part of pattern after the wildcard. Perforce does not permit a slash to be in this part of the file spec filter.
- L95 _public method_ `public bool IsFileWildcard()` — Tests if the entry has a file wildcard ('*')
- L101 _public method_ `public bool IsPathWildcard()` — Tests if the entry has a path wildcard ('...')
- L108-130 _public ctor_ `public PerforceViewFilterEntry(bool include, string pathExpression)` — Constructor
- L139-145 _public ctor_ `public PerforceViewFilterEntry(bool include, string wildcard, string prefix, string suffix)` — Constructor
- L152-160 _public method_ `public static PerforceViewFilterEntry Parse(string entry)` — Parse a view filter entry from a string, as returned by spec documents
- L168-190 _public method_ `public bool MatchFile(string path, StringComparison comparison)` — Determine if a file matches the current entry
- L193-202 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Perforce/PerforceViewMap.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PerforceViewMap`  
`public class PerforceViewMap`  
_public; L14-171_
- desc: Stores a mapping from one set of paths to another
- L19 _public property_ `public List<PerforceViewMapEntry> Entries { get; }` — List of entries making up the view
- L24-27 _public ctor_ `public PerforceViewMap()` — Default constructor
- L33-36 _public ctor_ `public PerforceViewMap(IEnumerable<PerforceViewMapEntry> entries)` — Construct from an existing set of entries
- L42-45 _public ctor_ `public PerforceViewMap(PerforceViewMap other)` — Constructor
- L51-54 _public method_ `public static PerforceViewMap Parse(IEnumerable<string> entries)` — Construct a view map from a set of entries
- L60-68 _public method_ `public PerforceViewMap Invert()` — Gets the inverse of this mapping
- L76-87 _public method_ `public bool MatchFile(string file, StringComparison comparison)` — Determines if a file is included in the view
- L95-104 _public method_ `public IEnumerable<string> MapFiles(IEnumerable<string> sourceFiles, StringComparison comparison)` — Maps a set of files into the target files
- L113-134 _public method_ `public bool TryMapFile(string sourceFile, StringComparison comparison, out string targetFile)` — Attempts to convert a source file to its target path
- L140-170 _public method_ `public List<string> GetRootPaths(StringComparison comparison)` — Gets the root paths from the view entries

#### class `EpicGames.Perforce.PerforceViewMapEntry`  
`public class PerforceViewMapEntry`  
_public; L176-359_
- desc: Entry within a ViewMap
- L181 _public property_ `public bool Include { get; }` — Whether to include files matching this pattern
- L186 _public property_ `public string Wildcard { get; }` — The wildcard string - either '*' or '...'
- L191 _public property_ `public string SourcePrefix { get; }` — The source part of the pattern before the wildcard
- L196 _public property_ `public string SourceSuffix { get; }` — The source part of the pattern after the wildcard. Perforce does not permit a slash to be in this part of the mapping.
- L201 _public property_ `public string TargetPrefix { get; }` — The target mapping for the pattern before the wildcard
- L206 _public property_ `public string TargetSuffix { get; }` — The target mapping for the pattern after the wildcard
- L211 _public property_ `public string Source => ...` — The full source pattern
- L216 _public property_ `public string Target => ...` — The full target pattern
- L222 _public method_ `public bool IsFileWildcard()` — Tests if the entry has a file wildcard ('*')
- L228 _public method_ `public bool IsPathWildcard()` — Tests if the entry has a path wildcard ('...')
- L234-237 _public ctor_ `public PerforceViewMapEntry(PerforceViewMapEntry other) : this(other.Include, other.Wildcard, other.SourcePrefix, other.SourceSuffix, other.TargetPrefix, other.TargetSuffix)` — Constructor
- L245-275 _public ctor_ `public PerforceViewMapEntry(bool include, string source, string target)` — Constructor
- L286-294 _public ctor_ `public PerforceViewMapEntry(bool include, string wildcard, string sourcePrefix, string sourceSuffix, string targetPrefix, string targetSuffix)` — Constructor
- L301-309 _public method_ `public static PerforceViewMapEntry Parse(string entry)` — Parse a view map entry from a string, as returned by spec documents
- L316-320 _public method_ `public string MapFile(string sourceFile)` — Maps a file to the target path
- L328-346 _public method_ `public bool MatchFile(string path, StringComparison comparison)` — Determine if a file matches the current entry
- L349-358 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Perforce/Records/AddOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.AddOptions`  
`public enum AddOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the p4 add command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `DowngradeToAdd = 1` — Downgrade file open status to simple add.
- L26 _public* enumerator_ `IncludeWildcards = 2` — Force inclusion of wildcards in filenames.
- L31 _public* enumerator_ `NoIgnore = 4` — Do not perform any ignore checking; ignore any settings specified by P4IGNORE.
- L36 _public* enumerator_ `PreviewOnly = 8` — Preview which files would be opened for add, without actually changing any files or metadata.

### `Source/Programs/Shared/EpicGames.Perforce/Records/AddRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.AddRecord`  
`public class AddRecord`  
_public; L8-59_
- desc: Contains information about an added file
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace
- L26 _public property_ `public int WorkingRevision { get; set; }` — attrs: `[PerforceTag("workRev")]` — The working revision number of the file that was synced
- L32 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken when syncing the file
- L38 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — Type of the file
- L43-49 _private ctor_ `private AddRecord()` — Private constructor for serialization
- L55-58 _public method_ `public override string? ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/AnnotateLineRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.AnnotateLineRecord`  
`public class AnnotateLineRecord`  
_public; L10-52_
- L16 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]`
- L22 _public property_ `public int UpperRev { get; set; }` — attrs: `[PerforceTag("upper")]` — The upper changelist
- L28 _public property_ `public int LowerRev { get; set; }` — attrs: `[PerforceTag("lower")]` — The lower changelist
- L34 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time", Optional = true)]` — Timestamp of this modification
- L39-42 _private ctor_ `private AnnotateLineRecord()` — Private constructor for serialization
- L48-51 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/AnnotateOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.AnnotateOptions`  
`public enum AnnotateOptions`  
_public; L11-45_
- attrs: `[Flags]`
- L16 _public* enumerator_ `None = 0` — No options specified
- L23 _public* enumerator_ `IncludeDeletedFilesAndLines = 1` — includes both deleted files and lines no longer present at the head revision. In the latter case, both the starting and ending revision for each line is displayed.
- L28 _public* enumerator_ `IgnoreWhiteSpaceChanges = 2` — ignore whitespace changes
- L37 _public* enumerator_ `FollowIntegrations = 4` — follows all integrations into the file. If a line was introduced into the file by a merge, the source of the merge is displayed as the changelist that introduced the line. If the source itself was the result of an integration, that source is used instead, and so on.
- L43 _public* enumerator_ `OutputUserAndDate = 8` — directs the annotate command to output the user who modified the line in the file and the date it was modified.

### `Source/Programs/Shared/EpicGames.Perforce/Records/AnnotateRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.AnnotateRecord`  
`public class AnnotateRecord`  
_public; L11-101_
- L17 _public property_ `public int RevisionNumber { get; set; }` — attrs: `[PerforceTag("rev", Optional = true)]` — The revision number of this file
- L23 _public property_ `public int ChangeNumber { get; set; }` — attrs: `[PerforceTag("change", Optional = true)]` — The changelist responsible for this revision of the file
- L29 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type", Optional = true)]` — Type of the file
- L35 _public property_ `public string UpperCl { get; set; }` — attrs: `[PerforceTag("upper", Optional = true)]` — The upper changelist
- L41 _public property_ `public string LowerCl { get; set; }` — attrs: `[PerforceTag("lower", Optional = true)]` — The lower changelist
- L47 _public property_ `public string UserName { get; set; }` — attrs: `[PerforceTag("user", Optional = true)]` — Author of the changelist
- L53 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time", Optional = true)]` — Timestamp of this modification
- L59 _public property_ `public string ClientName { get; set; }` — attrs: `[PerforceTag("client", Optional = true)]` — Client that submitted this changelist
- L65 _public property_ `public string Data { get; set; }` — attrs: `[PerforceTag("data", Optional = true)]` — The actual line
- L71 _public property_ `public List<AnnotateLineRecord> LineRecord { get; }` — attrs: `[PerforceRecordList]`
- L76-84 _private ctor_ `private AnnotateRecord()` — Private constructor for serialization
- L90-100 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/ChangeRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ChangeRecord`  
`public class ChangeRecord`  
_public; L11-60_
- desc: Contains summary information about a changelist
- L17 _public property_ `public int Number { get; set; }` — attrs: `[PerforceTag("Change")]` — The changelist number. -1 for "new".
- L23 _public property_ `public DateTime Date { get; set; }` — attrs: `[PerforceTag("Date", Optional = true)]` — The date the change was last modified
- L29 _public property_ `public string? User { get; set; }` — attrs: `[PerforceTag("User")]` — The user that owns or submitted the change
- L35 _public property_ `public string? Client { get; set; }` — attrs: `[PerforceTag("Client")]` — The client that owns the change
- L41 _public property_ `public ChangeStatus Status { get; set; }` — attrs: `[PerforceTag("Status")]` — Current changelist status
- L47 _public property_ `public ChangeType Type { get; set; }` — attrs: `[PerforceTag("Type")]` — Whether the change is restricted or not
- L53 _public property_ `public string? Description { get; set; }` — attrs: `[PerforceTag("Description")]` — Description for the changelist
- L59 _public property_ `public List<string> Files { get; }` — attrs: `[PerforceTag("Files", Optional = true)]` — Files that are open in this changelist

### `Source/Programs/Shared/EpicGames.Perforce/Records/ChangeStatus.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ChangeStatus`  
`public enum ChangeStatus`  
_public; L8-32_
- desc: Indicates the status of a changelist
- L13 _public* enumerator_ `All` — Include all changes
- L19 _public* enumerator_ `Pending` — attrs: `[PerforceEnum("pending")]` — The change is still pending
- L25 _public* enumerator_ `Submitted` — attrs: `[PerforceEnum("submitted")]` — The change has been submitted
- L31 _public* enumerator_ `Shelved` — attrs: `[PerforceEnum("shelved")]` — The change is shelved

### `Source/Programs/Shared/EpicGames.Perforce/Records/ChangeType.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ChangeType`  
`public enum ChangeType`  
_public; L8-26_
- desc: The type of a changelist
- L13 _public* enumerator_ `Unspecified` — When creating a new changelist, leaves the changelist type unspecified.
- L19 _public* enumerator_ `Public` — attrs: `[PerforceEnum("public")]` — This change is visible to anyone
- L25 _public* enumerator_ `Restricted` — attrs: `[PerforceEnum("restricted")]` — This change is restricted

### `Source/Programs/Shared/EpicGames.Perforce/Records/ChangesOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ChangesOptions`  
`public enum ChangesOptions`  
_public; L11-47_
- attrs: `[Flags]`
- desc: Options for the 'changes' command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `IncludeIntegrations = 1` — Include changelists that affected files that were integrated with the specified files.
- L26 _public* enumerator_ `IncludeTimes = 2` — Display the time as well as the date of each change.
- L31 _public* enumerator_ `LongOutput = 4` — List long output, with the full text of each changelist description.
- L36 _public* enumerator_ `TruncatedLongOutput = 8` — List long output, with the full text of each changelist description truncated at 250 characters.
- L41 _public* enumerator_ `IncludeRestricted = 16` — View restricted changes (requires admin permission)
- L46 _public* enumerator_ `Reverse = 32` — Gets oldest changes first

### `Source/Programs/Shared/EpicGames.Perforce/Records/ChangesRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ChangesRecord`  
`public class ChangesRecord`  
_public; L12-61_
- attrs: `[DebuggerDisplay("{Number}: {Description}")]`
- desc: Contains summary information about a changelist
- L18 _public property_ `public int Number { get; set; }` — attrs: `[PerforceTag("change")]` — The changelist number
- L24 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time")]` — The date the change was last modified
- L30 _public property_ `public string User { get; set; }` — attrs: `[PerforceTag("user")]` — The user that owns or submitted the change
- L36 _public property_ `public string? Client { get; set; }` — attrs: `[PerforceTag("client")]` — The client that owns the change
- L42 _public property_ `public ChangeStatus Status { get; set; }` — attrs: `[PerforceTag("status")]` — Current changelist status
- L48 _public property_ `public ChangeType Type { get; set; }` — attrs: `[PerforceTag("changeType")]` — Whether the change is restricted or not
- L54 _public property_ `public string? Path { get; set; }` — attrs: `[PerforceTag("path", Optional = true)]` — The path affected by this change.
- L60 _public property_ `public string Description { get; set; }` — attrs: `[PerforceTag("desc")]` — Description for the changelist

### `Source/Programs/Shared/EpicGames.Perforce/Records/CleanOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.CleanOptions`  
`public enum CleanOptions`  
_public; L11-52_
- attrs: `[Flags]`
- desc: Options for the p4 clean command
- L16 _public* enumerator_ `None = 0` — User default options
- L21 _public* enumerator_ `Edited = 1` — Edited files: Find files in the workspace that have been modified and restore them to the last file version that has synced from the depot.
- L26 _public* enumerator_ `Added = 2` — Added files: Find files in the workspace that have no corresponding files in the depot and delete them.
- L31 _public* enumerator_ `Deleted = 4` — Deleted files: Find those files in the depot that do not exist in your workspace and add them to the workspace.
- L36 _public* enumerator_ `Preview = 8` — Preview the results of the operation without performing any action.
- L41 _public* enumerator_ `NoIgnoreChecking = 16` — Do not perform any ignore checking; ignore any settings specified by P4IGNORE for added files.
- L46 _public* enumerator_ `LocalSyntax = 32` — Include file paths in local syntax
- L51 _public* enumerator_ `ModifiedTimes = 64` — Use modified times to determine whether files are out of date (see https://community.perforce.com/s/article/15133)

### `Source/Programs/Shared/EpicGames.Perforce/Records/CleanRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.CleanRecord`  
`public class CleanRecord`  
_public; L8-39_
- desc: Record returned by the p4 clean command
- L14 _public property_ `public string? DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile", Optional = true)]` — Depot path of the file, according to the workspace mapping
- L20 _public property_ `public string? ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile", Optional = true)]` — Client path to the file (in local path syntax)
- L26 _public property_ `public string? LocalFile { get; set; }` — attrs: `[PerforceTag("localFile", Optional = true)]` — Path to the file in local syntax
- L32 _public property_ `public string? Revision { get; set; }` — attrs: `[PerforceTag("rev", Optional = true)]` — Revision of the file
- L38 _public property_ `public FileAction Action { get; set; }` — attrs: `[PerforceTag("action", Optional = true)]` — Action to be taken to the file

### `Source/Programs/Shared/EpicGames.Perforce/Records/ClientLineEndings.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ClientLineEndings`  
`public enum ClientLineEndings`  
_public; L8-44_
- desc: Specifies how to treat line endings on files synced to the client
- L13 _public* enumerator_ `Unspecified` — This value is not specified
- L19 _public* enumerator_ `Local` — attrs: `[PerforceEnum("local")]` — Use mode native to the client (default)
- L25 _public* enumerator_ `Unix` — attrs: `[PerforceEnum("unix")]` — UNIX-style (and Mac OS X) line endings: LF
- L31 _public* enumerator_ `Mac` — attrs: `[PerforceEnum("mac")]` — Mac pre-OS X: CR only
- L37 _public* enumerator_ `Windows` — attrs: `[PerforceEnum("win")]` — Windows-style: CR + LF.
- L43 _public* enumerator_ `Share` — attrs: `[PerforceEnum("share")]` — The share option normalizes mixed line-endings into UNIX line-end format.

### `Source/Programs/Shared/EpicGames.Perforce/Records/ClientOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ClientOptions`  
`public enum ClientOptions`  
_public; L11-101_
- attrs: `[Flags]`
- desc: Options for the client
- L16 _public* enumerator_ `None = 0` — No options are set
- L22 _public* enumerator_ `AllWrite = 1` — attrs: `[PerforceEnum("allwrite")]` — If set, unopened files in the workspace are left writable.
- L28 _public* enumerator_ `NoAllWrite = 2` — attrs: `[PerforceEnum("noallwrite")]` — Opposite of AllWrite.
- L34 _public* enumerator_ `Clobber = 4` — attrs: `[PerforceEnum("clobber")]` — If set, a p4 sync overwrites ("clobbers") writable-but-unopened files in the workspace that have the same name as the newly-synced files.
- L40 _public* enumerator_ `NoClobber = 8` — attrs: `[PerforceEnum("noclobber")]` — Opposite of Clobber.
- L46 _public* enumerator_ `Compress = 16` — attrs: `[PerforceEnum("compress")]` — If set, a p4 sync overwrites ("clobbers") writable-but-unopened files in the workspace that have the same name as the newly-synced files.
- L52 _public* enumerator_ `NoCompress = 32` — attrs: `[PerforceEnum("nocompress")]` — Opposite of Compress.
- L58 _public* enumerator_ `Locked = 64` — attrs: `[PerforceEnum("locked")]` — If set, a p4 sync overwrites ("clobbers") writable-but-unopened files in the workspace that have the same name as the newly-synced files.
- L64 _public* enumerator_ `Unlocked = 128` — attrs: `[PerforceEnum("unlocked")]` — Opposite of Locked.
- L70 _public* enumerator_ `ModTime = 256` — attrs: `[PerforceEnum("modtime")]` — For files without the +m (modtime) file type modifier, the modification date (on the local filesystem) of a newly synced file is the datestamp on the file when the file was last modified.
- L76 _public* enumerator_ `NoModTime = 512` — attrs: `[PerforceEnum("nomodtime")]` — For files without the +m (modtime) file type modifier, the modification date is the date and time of sync, regardless of version.
- L82 _public* enumerator_ `Rmdir = 1024` — attrs: `[PerforceEnum("rmdir")]` — If set, p4 sync deletes empty directories in a workspace if all files in the directory have been removed.
- L88 _public* enumerator_ `NoRmdir = 2048` — attrs: `[PerforceEnum("normdir")]` — Opposite of Rmdir.
- L94 _public* enumerator_ `AltSync = 4096` — attrs: `[PerforceEnum("altsync")]` — If set, and a Helix Core Virtual File Service (P4VFS) application is installed to make use of P4ALTSYNC, the client can create, delete, or update placeholders of the file metadata instead of always taking time to download the full file content.
- L100 _public* enumerator_ `NoAltSync = 8192` — attrs: `[PerforceEnum("noaltsync")]` — Opposite of AltSync.

### `Source/Programs/Shared/EpicGames.Perforce/Records/ClientRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ClientRecord`  
`public class ClientRecord`  
_public; L11-119_
- desc: Represents a Perforce clientspec
- L17 _public property_ `public string Name { get; set; }` — attrs: `[PerforceTag("Client")]` — The client workspace name, as specified in the P4CLIENT environment variable or its equivalents.
- L23 _public property_ `public string? Owner { get; set; }` — attrs: `[PerforceTag("Owner", Optional = true)]` — The Perforce user name of the user who owns the workspace.
- L29 _public property_ `public DateTime Update { get; set; }` — attrs: `[PerforceTag("Update", Optional = true)]` — The date the workspace specification was last modified.
- L35 _public property_ `public DateTime Access { get; set; }` — attrs: `[PerforceTag("Access", Optional = true)]` — The date and time that the workspace was last used in any way.
- L41 _public property_ `public string? Host { get; set; }` — attrs: `[PerforceTag("Host", Optional = true)]` — The name of the workstation on which this workspace resides.
- L47 _public property_ `public string? Description { get; set; }` — attrs: `[PerforceTag("Description", Optional = true)]` — A textual description of the workspace.
- L53 _public property_ `public string? ServerId { get; set; }` — attrs: `[PerforceTag("ServerID", Optional = true)]` — Name of the server containing this change.
- L59 _public property_ `public string Root { get; set; }` — attrs: `[PerforceTag("Root")]` — The directory (on the local host) relative to which all the files in the View: are specified.
- L65 _public property_ `public ClientOptions Options { get; set; }` — attrs: `[PerforceTag("Options")]` — A set of seven switches that control particular workspace options.
- L71 _public property_ `public ClientSubmitOptions SubmitOptions { get; set; }` — attrs: `[PerforceTag("SubmitOptions")]` — Options to govern the default behavior of p4 submit.
- L77 _public property_ `public ClientLineEndings LineEnd { get; set; }` — attrs: `[PerforceTag("LineEnd")]` — Configure carriage-return/linefeed (CR/LF) conversion.
- L83 _public property_ `public string? Stream { get; set; }` — attrs: `[PerforceTag("Stream", Optional = true)]` — Associates the workspace with the specified stream.
- L89 _public property_ `public string? Type { get; set; }` — attrs: `[PerforceTag("Type", Optional = true)]` — The type of client.
- L95 _public property_ `public List<string> View { get; }` — attrs: `[PerforceTag("View")]` — Specifies the mappings between files in the depot and files in the workspace.
- L100-105 _private ctor_ `private ClientRecord()` — Private constructor for serialization
- L113-118 _public ctor_ `public ClientRecord(string name, string owner, string root)` — Constructor

### `Source/Programs/Shared/EpicGames.Perforce/Records/ClientSubmitOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ClientSubmitOptions`  
`public enum ClientSubmitOptions`  
_public; L8-50_
- desc: Client options for controlling the default behavior of p4 submit
- L13 _public* enumerator_ `Unspecified` — This field is not set
- L19 _public* enumerator_ `SubmitUnchanged` — attrs: `[PerforceEnum("submitunchanged")]` — All open files (with or without changes) are submitted to the depot.
- L25 _public* enumerator_ `SubmitUnchangedAndReopen` — attrs: `[PerforceEnum("submitunchanged+reopen")]` — All open files (with or without changes) are submitted to the depot, and all files are automatically reopened in the default changelist.
- L31 _public* enumerator_ `RevertUnchanged` — attrs: `[PerforceEnum("revertunchanged")]` — Only those files with content, type, or resolved changes are submitted to the depot.
- L37 _public* enumerator_ `RevertUnchangedAndReopen` — attrs: `[PerforceEnum("revertunchanged+reopen")]` — Only those files with content, type, or resolved changes are submitted to the depot and reopened in the default changelist.
- L43 _public* enumerator_ `LeaveUnchanged` — attrs: `[PerforceEnum("leaveunchanged")]` — Only those files with content, type, or resolved changes are submitted to the depot. Any unchanged files are moved to the default changelist.
- L49 _public* enumerator_ `LeaveUnchangedAndReopen` — attrs: `[PerforceEnum("leaveunchanged+reopen")]` — Only those files with content, type, or resolved changes are submitted to the depot.

### `Source/Programs/Shared/EpicGames.Perforce/Records/ClientsOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ClientsOptions`  
`public enum ClientsOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the p4 clients command
- L16 _public* enumerator_ `None = 0` — No options
- L21 _public* enumerator_ `All = 1` — List all client workspaces, not just workspaces bound to this server
- L26 _public* enumerator_ `CaseSensitiveFilter = 2` — Treat the filter argument as case sensitive
- L31 _public* enumerator_ `WithTimes = 4` — Display the time as well as the date of the last update to the workspace.
- L36 _public* enumerator_ `Unloaded = 8` — List only client workspaces unloaded with p4 unload.

### `Source/Programs/Shared/EpicGames.Perforce/Records/ClientsRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ClientsRecord`  
`public class ClientsRecord`  
_public; L10-102_
- desc: Record returned by the p4 clients command
- L16 _public property_ `public string Name { get; set; }` — attrs: `[PerforceTag("client")]` — The client workspace name, as specified in the P4CLIENT environment variable or its equivalents.
- L22 _public property_ `public string Owner { get; set; }` — attrs: `[PerforceTag("Owner")]` — The Perforce user name of the user who owns the workspace.
- L28 _public property_ `public DateTime Update { get; set; }` — attrs: `[PerforceTag("Update")]` — The date the workspace specification was last modified.
- L34 _public property_ `public DateTime Access { get; set; }` — attrs: `[PerforceTag("Access")]` — The date and time that the workspace was last used in any way.
- L40 _public property_ `public string? Host { get; set; }` — attrs: `[PerforceTag("Host", Optional = true)]` — The name of the workstation on which this workspace resides.
- L46 _public property_ `public string? Description { get; set; }` — attrs: `[PerforceTag("Description", Optional = true)]` — A textual description of the workspace.
- L52 _public property_ `public string Root { get; set; }` — attrs: `[PerforceTag("Root")]` — The directory (on the local host) relative to which all the files in the View: are specified.
- L58 _public property_ `public ClientOptions Options { get; set; }` — attrs: `[PerforceTag("Options")]` — A set of seven switches that control particular workspace options.
- L64 _public property_ `public ClientSubmitOptions SubmitOptions { get; set; }` — attrs: `[PerforceTag("SubmitOptions")]` — Options to govern the default behavior of p4 submit.
- L70 _public property_ `public ClientLineEndings LineEnd { get; set; }` — attrs: `[PerforceTag("LineEnd")]` — Configure carriage-return/linefeed (CR/LF) conversion.
- L76 _public property_ `public string? Stream { get; set; }` — attrs: `[PerforceTag("Stream", Optional = true)]` — Associates the workspace with the specified stream.
- L82 _public property_ `public string? ServerId { get; set; }` — attrs: `[PerforceTag("ServerID", Optional = true)]` — The edge server ID
- L87-92 _private ctor_ `private ClientsRecord()` — Private constructor for serialization
- L98-101 _public method_ `public override string? ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/DeleteChangeOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.DeleteChangeOptions`  
`public enum DeleteChangeOptions`  
_public; L8-24_
- desc: Options for the DeleteChange command (p4 change -d)
- L13 _public* enumerator_ `None = 0` — No options are specified
- L18 _public* enumerator_ `Submitted = 1` — Forcibly delete a previously submitted changelist.
- L23 _public* enumerator_ `BeforeRenumber = 2` — If a changelist was renumbered on submit, and you know only the original changelist number, use OriginalChangeNumber and the original changelist number to view or edit the changelist.

### `Source/Programs/Shared/EpicGames.Perforce/Records/DeleteClientOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.DeleteClientOptions`  
`public enum DeleteClientOptions`  
_public; L11-27_
- attrs: `[Flags]`
- desc: Options for the p4 client -d command
- L16 _public* enumerator_ `None = 0` — No options
- L21 _public* enumerator_ `Force = 1` — Administrators can use the -f option to delete or modify locked workspaces owned by other users.
- L26 _public* enumerator_ `DeleteShelved = 2` — Allows the deletion of a client even when that client contains shelved changes. Requires the Force option.

### `Source/Programs/Shared/EpicGames.Perforce/Records/DeleteOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.DeleteOptions`  
`public enum DeleteOptions`  
_public; L11-32_
- attrs: `[Flags]`
- desc: Options for the p4 delete command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `KeepWorkspaceFiles = 1` — Keep existing workspace files; mark the file as open for edit even if the file is not in the client view.
- L26 _public* enumerator_ `PreviewOnly = 2` — Preview which files would be opened for edit, without actually changing any files or metadata.
- L31 _public* enumerator_ `WithoutSyncing = 4` — Perform the delete without syncing files

### `Source/Programs/Shared/EpicGames.Perforce/Records/DeleteRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.DeleteRecord`  
`public class DeleteRecord`  
_public; L8-59_
- desc: Information about a file opened for delete
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace
- L26 _public property_ `public int WorkingRevision { get; set; }` — attrs: `[PerforceTag("workRev")]` — The working revision number of the file that was synced
- L32 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken when syncing the file
- L38 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — Type of the file
- L43-49 _private ctor_ `private DeleteRecord()` — Private constructor for serialization
- L55-58 _public method_ `public override string? ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/DepotRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.DepotRecord`  
`public class DepotRecord`  
_public; L11-67_
- desc: Information about a file opened for delete
- L17 _public property_ `public string Depot { get; set; }` — attrs: `[PerforceTag("Depot")]` — Depot name
- L23 _public property_ `public string Owner { get; set; }` — attrs: `[PerforceTag("Owner", Optional = true)]` — Owner of the depot
- L29 _public property_ `public DateTime Date { get; set; }` — attrs: `[PerforceTag("Date", Optional = true)]` — Creation time
- L35 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("Type", Optional = true)]` — Depot Type
- L41 _public property_ `public string Description { get; set; }` — attrs: `[PerforceTag("Description", Optional = true)]` — Depot Description
- L48 _public property_ `public string StreamDepthString { get; set; }` — attrs: `[PerforceTag("StreamDepth", Optional = true)]` — Depot Stream Depth (number of slashes after depot that define the stream name) A string containing either an integer value or an example path (i.e. //depot/foo/bar represents a depth of 2)
- L53-66 _public method_ `public int GetStreamDepth()` — Helper to get Depot Stream Depth (number of slashes after depot that define the stream name) as an integer

### `Source/Programs/Shared/EpicGames.Perforce/Records/DescribeFileRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.DescribeFileRecord`  
`public class DescribeFileRecord`  
_public; L8-63_
- desc: Contains information about an individual file in a returned DescribeRecord
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the modified file in depot syntax
- L20 _public property_ `public FileAction Action { get; set; }` — attrs: `[PerforceTag("action")]` — The action performed on this file
- L26 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — The file type after this change
- L32 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev")]` — The revision number for this file
- L38 _public property_ `public long FileSize { get; set; }` — attrs: `[PerforceTag("fileSize", Optional = true)]` — Size of the file, or -1 if not specified
- L44 _public property_ `public string? Digest { get; set; }` — attrs: `[PerforceTag("digest", Optional = true)]` — Digest of the file, or null if not specified
- L49-53 _private ctor_ `private DescribeFileRecord()` — Private constructor for serialization
- L59-62 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/DescribeOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.DescribeOptions`  
`public enum DescribeOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the p4 describe command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `ShowDescriptionForRestrictedChanges = 1` — Force the display of descriptions for restricted changelists. This option requires admin permission.
- L26 _public* enumerator_ `Identity = 2` — Specifies that the changelist number is the Identity field of a changelist.
- L31 _public* enumerator_ `OriginalChangeNumber = 4` — If a changelist was renumbered on submit, and you know only the original changelist number, use -O and the original changelist number to describe the changelist.
- L36 _public* enumerator_ `Shelved = 8` — Display the names of files shelved for the specified changelist, including the diff of each file against its previous depot revision.

### `Source/Programs/Shared/EpicGames.Perforce/Records/DescribeRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.DescribeRecord`  
`public class DescribeRecord`  
_public; L11-85_
- desc: Detailed description of an individual changelist
- L17 _public property_ `public int Number { get; set; }` — attrs: `[PerforceTag("change")]` — The changelist number
- L23 _public property_ `public string User { get; set; }` — attrs: `[PerforceTag("user")]` — The user that owns or submitted the change
- L29 _public property_ `public string Client { get; set; }` — attrs: `[PerforceTag("client")]` — The workspace that contains or submitted the change
- L35 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time")]` — Time at which the change was submitted
- L41 _public property_ `public string Description { get; set; }` — attrs: `[PerforceTag("desc")]` — The changelist description
- L47 _public property_ `public ChangeStatus Status { get; set; }` — attrs: `[PerforceTag("status")]` — The change status (submitted, pending, etc...)
- L53 _public property_ `public ChangeType Type { get; set; }` — attrs: `[PerforceTag("changeType")]` — Whether the change is restricted or not
- L59 _public property_ `public string? Path { get; set; }` — attrs: `[PerforceTag("path", Optional = true)]` — Narrowest path which contains all files affected by this change
- L65 _public property_ `public List<DescribeFileRecord> Files { get; }` — attrs: `[PerforceRecordList]` — The files affected by this change
- L70-75 _private ctor_ `private DescribeRecord()` — Private constructor for serialization
- L81-84 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/DirsOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.DirsOptions`  
`public enum DirsOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the p4 dirs command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `OnlyMapped = 1` — Display only those directories that are mapped through the current client view.
- L26 _public* enumerator_ `OnlyHave = 2` — Include only those directories that contain files on the current client workspace’s p4 have list.
- L31 _public* enumerator_ `IncludeDeleted = 4` — Include subdirectories that contain only deleted files. By default, these directories are not displayed.
- L36 _public* enumerator_ `IgnoreCase = 8` — Ignore the case of the directory argument when listing directories in a case-sensitive server.

### `Source/Programs/Shared/EpicGames.Perforce/Records/DirsRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.DirsRecord`  
`public class DirsRecord`  
_public; L8-32_
- desc: Subdirectory under a requested depot path
- L14 _public property_ `public string Dir { get; set; }` — attrs: `[PerforceTag("dir")]` — The directory name
- L19-22 _private ctor_ `private DirsRecord()` — Private constructor for serialization
- L28-31 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/EditOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.EditOptions`  
`public enum EditOptions`  
_public; L11-27_
- attrs: `[Flags]`
- desc: Options for the p4 edit command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `KeepWorkspaceFiles = 1` — Keep existing workspace files; mark the file as open for edit even if the file is not in the client view.
- L26 _public* enumerator_ `PreviewOnly = 2` — Preview which files would be opened for edit, without actually changing any files or metadata.

### `Source/Programs/Shared/EpicGames.Perforce/Records/EditRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.EditRecord`  
`public class EditRecord`  
_public; L8-59_
- desc: Information about a file opened for edit
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace
- L26 _public property_ `public int WorkingRevision { get; set; }` — attrs: `[PerforceTag("workRev")]` — The working revision number of the file that was synced
- L32 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken when syncing the file
- L38 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — Type of the file
- L43-49 _private ctor_ `private EditRecord()` — Private constructor for serialization
- L55-58 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/FStatOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.FStatOptions`  
`public enum FStatOptions`  
_public; L11-117_
- attrs: `[Flags]`
- desc: Options for the Fstat command
- L16 _public* enumerator_ `None = 0x0` — No options specified
- L21 _public* enumerator_ `ReportDepotSyntax = 0x01` — For scripting purposes, report file information on a list of valid file arguments in full depot syntax with a valid revision number.
- L26 _public* enumerator_ `AllRevisions = 0x02` — Output all revisions for the given files, suppressing the other[...] and resolve[...] fields.
- L31 _public* enumerator_ `IncludeFileSizes = 0x04` — Output a fileSize field displaying the length of the file and a digest field for each revision.
- L36 _public* enumerator_ `ClientFileInPerforceSyntax = 0x08` — Display the clientFile in Perforce syntax, as opposed to local syntax.
- L41 _public* enumerator_ `ShowPendingIntegrations = 0x10` — Display pending integration record data for files open in the current workspace.
- L46 _public* enumerator_ `ShortenOutput = 0x20` — Shorten output by excluding client workspace data (for instance, the clientFile field).
- L51 _public* enumerator_ `ReverseOrder = 0x40` — Sort the output in reverse order.
- L56 _public* enumerator_ `OnlyMapped = 0x80` — Limit output to files mapped into the current workspace.
- L61 _public* enumerator_ `OnlyHave = 0x100` — Limit output to files on your have list; that is, to files synced to the current workspace.
- L66 _public* enumerator_ `OnlyOpenedBeforeHead = 0x200` — Limit output to files opened at revisions not at the head revision.
- L71 _public* enumerator_ `OnlyOpenInWorkspace = 0x400` — Limit output to open files in the current workspace.
- L76 _public* enumerator_ `OnlyOpenAndResolved = 0x800` — Limit output to open files that have been resolved.
- L81 _public* enumerator_ `OnlyShelved = 0x1000` — Limit output to shelved files.
- L86 _public* enumerator_ `OnlyUnresolved = 0x2000` — Limit output to open files that are unresolved.
- L91 _public* enumerator_ `SortByDate = 0x4000` — Sort by date.
- L96 _public* enumerator_ `SortByHaveRevision = 0x8000` — Sort by have revision.
- L101 _public* enumerator_ `SortByHeadRevision = 0x10000` — Sort by head revision.
- L106 _public* enumerator_ `SortByFileSize = 0x20000` — Sort by file size.
- L111 _public* enumerator_ `SortByFileType = 0x40000` — Sort by file type.
- L116 _public* enumerator_ `IncludeFilesInUnloadDepot = 0x80000` — Include files in the unload depot when displaying data.

### `Source/Programs/Shared/EpicGames.Perforce/Records/FStatRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.FStatRecord`  
`public class FStatRecord`  
_public; L10-152_
- desc: Record returned by the fstat command
- L16 _public property_ `public string? DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile", Optional = true)]` — Depot path to file
- L22 _public property_ `public string? ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile", Optional = true)]` — Local path to file (in local syntax by default, or in Perforce syntax with the FStatOptions.ClientFileInPerforceSyntax option)
- L28 _public property_ `public string? MovedFile { get; set; }` — attrs: `[PerforceTag("movedFile", Optional = true)]` — For move operations, shows the counterpart file
- L34 _public property_ `public string? Path { get; set; }` — attrs: `[PerforceTag("path", Optional = true)]` — Local path to file
- L40 _public property_ `public bool IsMapped { get; set; }` — attrs: `[PerforceTag("isMapped", Optional = true)]` — Set if the file is open for add and it is mapped to current client workspace
- L46 _public property_ `public bool Shelved { get; set; }` — attrs: `[PerforceTag("shelved", Optional = true)]` — Set if file is shelved
- L52 _public property_ `public FileAction HeadAction { get; set; }` — attrs: `[PerforceTag("headAction", Optional = true)]` — Action taken at head revision, if in depot
- L58 _public property_ `public string? HeadType { get; set; }` — attrs: `[PerforceTag("headType", Optional = true)]` — Head revision type, if in depot
- L64 _public property_ `public DateTime HeadTime { get; set; }` — attrs: `[PerforceTag("headTime", Optional = true)]` — Head revision changelist time, if in depot.
- L70 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev", Optional = true)]` — Revision for opened files
- L76 _public property_ `public int HeadRevision { get; set; }` — attrs: `[PerforceTag("headRev", Optional = true)]` — Head revision number, if in depot
- L82 _public property_ `public int HeadChange { get; set; }` — attrs: `[PerforceTag("headChange", Optional = true)]` — Head revision changelist number, if in depot
- L88 _public property_ `public DateTime HeadModTime { get; set; }` — attrs: `[PerforceTag("headModTime", Optional = true)]` — Head revision modification time (the time that the file was last modified on the client before submit), if in depot.
- L94 _public property_ `public int MovedRevision { get; set; }` — attrs: `[PerforceTag("movedRev", Optional = true)]` — Head revision of moved file
- L100 _public property_ `public int HaveRevision { get; set; }` — attrs: `[PerforceTag("haveRev", Optional = true)]` — Revision last synced to workspace, if on workspace
- L106 _public property_ `public string? Description { get; set; }` — attrs: `[PerforceTag("desc", Optional = true)]` — Changelist description (if using -e changelist and if the file was part of changelist)
- L112 _public property_ `public string? Digest { get; set; }` — attrs: `[PerforceTag("digest", Optional = true)]` — MD5 digest of a file (requires -Ol option)
- L118 _public property_ `public long FileSize { get; set; }` — attrs: `[PerforceTag("fileSize", Optional = true)]` — File length in bytes (requires -Ol option)
- L124 _public property_ `public FileAction Action { get; set; }` — attrs: `[PerforceTag("action", Optional = true)]` — Open action, if opened in your workspace
- L130 _public property_ `public string? Type { get; set; }` — attrs: `[PerforceTag("type", Optional = true)]` — Open type, if opened in your workspace
- L136 _public property_ `public string? ActionOwner { get; set; }` — attrs: `[PerforceTag("actionOwner", Optional = true)]` — User who opened the file, if opens
- L142 _public property_ `public int ChangeNumber { get; set; }` — attrs: `[PerforceTag("change", Optional = true)]` — Open changelist number, if opened in your workspace
- L148-151 _public method_ `public override string? ToString()` — Summarize this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/FileAction.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.FileAction`  
`public enum FileAction`  
_public; L8-81_
- desc: Actions applied to a file in a particular revision
- L14 _public* enumerator_ `None` — attrs: `[PerforceEnum("none")]`
- L20 _public* enumerator_ `Add` — attrs: `[PerforceEnum("add")]` — The file was added
- L26 _public* enumerator_ `Edit` — attrs: `[PerforceEnum("edit")]` — The file has been edited
- L32 _public* enumerator_ `Delete` — attrs: `[PerforceEnum("delete")]` — The file was deleted
- L38 _public* enumerator_ `Branch` — attrs: `[PerforceEnum("branch")]` — The file was branched from elsewhere in the depot
- L44 _public* enumerator_ `MoveAdd` — attrs: `[PerforceEnum("move/add")]` — The file at this path was added as part of a move from another location
- L50 _public* enumerator_ `MoveDelete` — attrs: `[PerforceEnum("move/delete")]` — The file at this path was deleted as part of a move into another location
- L56 _public* enumerator_ `Integrate` — attrs: `[PerforceEnum("integrate")]` — The file was merged with another file in the depot
- L62 _public* enumerator_ `Import` — attrs: `[PerforceEnum("import")]`
- L68 _public* enumerator_ `Purge` — attrs: `[PerforceEnum("purge")]` — The file was purged from the server
- L74 _public* enumerator_ `Archive` — attrs: `[PerforceEnum("archive")]` — The file was archived
- L80 _public* enumerator_ `Unknown` — attrs: `[PerforceEnum("unknown")]` — Unknown

### `Source/Programs/Shared/EpicGames.Perforce/Records/FileLogOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.FileLogOptions`  
`public enum FileLogOptions`  
_public; L11-47_
- attrs: `[Flags]`
- desc: Options for the filelog command
- L16 _public* enumerator_ `None = 0` — No options
- L21 _public* enumerator_ `ContentHistory = 1` — Display file content history instead of file name history.
- L26 _public* enumerator_ `FollowAcrossBranches = 2` — Follow file history across branches.
- L31 _public* enumerator_ `FullDescriptions = 4` — List long output, with the full text of each changelist description.
- L36 _public* enumerator_ `LongDescriptions = 8` — List long output, with the full text of each changelist description truncated at 250 characters.
- L41 _public* enumerator_ `DoNotFollowPromotedTaskStreams = 16` — When used with the ContentHistory option, do not follow content of promoted task streams.
- L46 _public* enumerator_ `IgnoreNonContributoryIntegrations = 32` — Display a shortened form of output by ignoring non-contributory integrations

### `Source/Programs/Shared/EpicGames.Perforce/Records/FileLogRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.FileLogRecord`  
`public class FileLogRecord`  
_public; L10-51_
- desc: Record output by the filelog command
- L16 _public property_ `public string DepotPath { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L22 _public property_ `public List<RevisionRecord> Revisions { get; }` — attrs: `[PerforceRecordList]` — Revisions of this file
- L27-30 _private ctor_ `private FileLogRecord()` — Private constructor for serialization
- L37-41 _public ctor_ `public FileLogRecord(string depotPath, List<RevisionRecord> revisions)` — Constructor
- L47-50 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/FileType.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.Managed.FileTypeBase`  
`public enum FileTypeBase : int`  
_public; L12-53_
- inherits: `int`
- desc: Base file type
- L17 _public* enumerator_ `Text = 0` — Text file
- L22 _public* enumerator_ `Binary = 1` — Non-text file
- L27 _public* enumerator_ `Symlink = 2` — Symbolic link
- L32 _public* enumerator_ `Apple = 3` — Multi-forked Macintosh file
- L37 _public* enumerator_ `Resource = 4` — Macintosh resource fork
- L42 _public* enumerator_ `Unicode = 5` — Unicode file
- L47 _public* enumerator_ `Utf16 = 6` — Unicode file, encoded as UTF-16
- L52 _public* enumerator_ `Utf8 = 7` — Unicode file, encoded as UTF-8

#### enum `EpicGames.Perforce.Managed.FileTypeModifiers`  
`public enum FileTypeModifiers : int`  
_public; L59-110_
- attrs: `[Flags]`
- inherits: `int`
- desc: Modifiers on top of the base filetype
- L64 _public* enumerator_ `AlwaysWritable = 0x8` — File is always writable on the client
- L69 _public* enumerator_ `Executable = 0x10` — Executable bit set on client
- L74 _public* enumerator_ `KeywordExpansion = 0x20` — RCS keyword expansion
- L79 _public* enumerator_ `KeywordExpansionOld = 0x40` — Old-style keyword expansion
- L84 _public* enumerator_ `ExclusiveOpen = 0x80` — Exclusive open (locking)
- L89 _public* enumerator_ `StoreFullRevisionsCompressed = 0x100` — Server stores the full compressed version of each file revision
- L94 _public* enumerator_ `StoreDeltas = 0x200` — Server stores deltas in RCS format
- L99 _public* enumerator_ `StoreFullRevisionsUncompressed = 0x400` — Server stores full file per revision, uncompressed
- L104 _public* enumerator_ `Modtime = 0x800` — Preserve original modtime
- L109 _public* enumerator_ `ArchiveTriggerRequired = 0x1000` — Archive trigger required

#### struct `EpicGames.Perforce.Managed.FileType`  
`public readonly struct FileType : IEquatable<FileType>`  
_public; L115-417_
- inherits: `IEquatable<FileType>`
- desc: Indicates the type of a file
- L120 _public const_ `public const int SerializedSize = sizeof(uint)` — Size of the object when serialized to memory
- L125 _public const_ `public const uint BaseMask = 7` — Mask for the base bits
- L130 _public const_ `public const uint ModifiersMask = 0xff & ~BaseMask` — Mask for the modifiers
- L135 _private* field_ `static readonly Utf8String[] s_baseNames = [ new Utf8String("text"), new Utf8String("binary"), new Utf8String("symlink"), new Utf8String("apple"), new Utf8String("resource"), new Utf8String("unicode"), new Utf8String("utf16"), new Utf8String(" ...` — Array of file type bases, with order matching FileTypeBase
- L150 _public property_ `public uint Encoded { get; }` — Encoded value of the filetype
- L155 _public property_ `public FileTypeBase Base => ...` — Base file type
- L160 _public property_ `public FileTypeModifiers Modifiers => ...` — File type modifiers
- L165 _public property_ `public int NumRevisions => ...` — Number of revisions to be stored
- L171-174 _public ctor_ `public FileType(uint encoded)` — Constructor
- L182-185 _public ctor_ `public FileType(FileTypeBase @base, FileTypeModifiers modifiers = 0, int numRevisions = 0)` — Constructor
- L192-202 _public method_ `public static FileType Parse(ReadOnlySpan<byte> text)` — Parse a string as a filetype
- L210-232 _public method_ `public static bool TryParse(ReadOnlySpan<byte> text, out FileType type)` — Try to parse a utf8 string as a filetype
- L240-253 _public method_ `public static bool TryParseBase(ReadOnlySpan<byte> text, out FileTypeBase @base)` — Try to parse a utf8 string as a filetype base
- L261-315 _public method_ `public static bool TryParseModifiers(ReadOnlySpan<byte> text, out (FileTypeModifiers, int) result)` — Try to parse modifiers from a utf8 string
- L323-326 _public operator_ `public static bool operator ==(FileType a, FileType b)` — Compares two filetypes for equality
- L334-337 _public operator_ `public static bool operator !=(FileType a, FileType b)` — Compares two filetypes for equality
- L340-343 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L346-349 _public method_ `public bool Equals(FileType other)` — (inheritdoc)
- L352-355 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L358-416 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Perforce.Managed.FileTypeExtensions`  
`public static class FileTypeExtensions`  
_public; L422-442_
- desc: Extension methods for file types
- L428-431 _public method_ `public static FileType ReadFileType(this MemoryReader reader)` — Constructor for reading a file info from disk
- L438-441 _public method_ `public static void WriteFileType(this MemoryWriter writer, FileType fileType)` — Save the file info to disk

### `Source/Programs/Shared/EpicGames.Perforce/Records/FilesOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.FilesOptions`  
`public enum FilesOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the p4 files command
- L16 _public* enumerator_ `None = 0` — Default options
- L21 _public* enumerator_ `AllRevisions = 1` — For each file, list all revisions within a specified revision range, rather than only the highest revision in the range.
- L26 _public* enumerator_ `LimitToArchiveDepots = 2` — Limit output to files in archive depots.
- L31 _public* enumerator_ `ExcludeDeleted = 4` — Exclude deleted, purged, or archived files; the files that remain are those available for syncing or integration.
- L36 _public* enumerator_ `IgnoreCase = 8` — Ignore the case of the file argument when listing files in a case sensitive server.

### `Source/Programs/Shared/EpicGames.Perforce/Records/FilesRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.FilesRecord`  
`public class FilesRecord`  
_public; L12-49_
- attrs: `[DebuggerDisplay("{DepotFile}#{Revision}")]`
- desc: Record returned by the p4 files command
- L18 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L24 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev")]` — File revision number
- L30 _public property_ `public int Change { get; set; }` — attrs: `[PerforceTag("change")]` — Changelist number that the file was modified in
- L36 _public property_ `public FileAction Action { get; set; }` — attrs: `[PerforceTag("action")]` — The action performed on this file
- L42 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — The file type after this change
- L48 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time", Optional = true)]` — Modification time (the time that the file was last modified on the client before submit), if in depot.

### `Source/Programs/Shared/EpicGames.Perforce/Records/GetChangeOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.GetChangeOptions`  
`public enum GetChangeOptions`  
_public; L8-19_
- desc: Options for the GetChange command (p4 change -o)
- L13 _public* enumerator_ `None = 0` — No options are specified
- L18 _public* enumerator_ `BeforeRenumber = 1` — If a changelist was renumbered on submit, and you know only the original changelist number, use OriginalChangeNumber and the original changelist number to view or edit the changelist.

### `Source/Programs/Shared/EpicGames.Perforce/Records/HaveRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.HaveRecord`  
`public class HaveRecord`  
_public; L12-43_
- attrs: `[DebuggerDisplay("{DepotFile}")]`
- desc: Record returned by the have command
- L18 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Depot path to file
- L24 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Client path to file
- L30 _public property_ `public string Path { get; set; }` — attrs: `[PerforceTag("path")]` — Local path to file
- L36 _public property_ `public int HaveRev { get; set; }` — attrs: `[PerforceTag("haveRev")]` — Revision of the file on the client
- L42 _public property_ `public int SyncTime { get; set; }` — attrs: `[PerforceTag("syncTime", Optional = true)]` — Time that the file was synced (local timestamp?)

### `Source/Programs/Shared/EpicGames.Perforce/Records/InfoOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.InfoOptions`  
`public enum InfoOptions`  
_public; L11-22_
- attrs: `[Flags]`
- desc: Options for the p4 info command
- L16 _public* enumerator_ `None = 0` — No addiional options
- L21 _public* enumerator_ `ShortOutput = 1` — Shortened output; exclude information that requires a database lookup.

### `Source/Programs/Shared/EpicGames.Perforce/Records/InfoRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.InfoRecord`  
`public class InfoRecord`  
_public; L11-103_
- desc: Contains information about the current client and server configuration
- L17 _public property_ `public string? UserName { get; set; }` — attrs: `[PerforceTag("userName", Optional = true)]` — The current user according to the Perforce environment
- L23 _public property_ `public string? ClientName { get; set; }` — attrs: `[PerforceTag("clientName", Optional = true)]` — The current client
- L29 _public property_ `public string? ClientHost { get; set; }` — attrs: `[PerforceTag("clientHost", Optional = true)]` — The current host
- L35 _public property_ `public string? ClientRoot { get; set; }` — attrs: `[PerforceTag("clientRoot", Optional = true)]` — Root directory for the current client
- L41 _public property_ `public string? ClientStream { get; set; }` — attrs: `[PerforceTag("clientStream", Optional = true)]` — Selected stream in the current client
- L47 _public property_ `public string? ServerAddress { get; set; }` — attrs: `[PerforceTag("serverAddress", Optional = true)]` — Address of the Perforce server
- L52 _public property_ `public string? ServerCluster { get; set; }` — attrs: `[PerforceTag("serverCluster", Optional = true)]` — Address of the Perforce server
- L58 _public property_ `public DateTimeOffset? ServerDate { get; set; }` — attrs: `[PerforceTag("serverDate", Optional = true)]` — Date and time on the server
- L64 _public property_ `public string? CaseHandling { get; set; }` — attrs: `[PerforceTag("caseHandling", Optional = true)]` — Case handling setting on the server
- L69 _public property_ `public bool IsCaseSensitive => ...` — Whether the server is case sensitive
- L74 _public property_ `public StringComparer PathComparer => ...` — How to compare paths on this server
- L79 _public property_ `public StringComparison PathComparison => ...` — How to compare paths on this server
- L84 _public property_ `public Utf8StringComparer Utf8PathComparer => ...` — How to compare paths on this server
- L90 _public property_ `public string? Services { get; set; }` — attrs: `[PerforceTag("serverServices", Optional = true)]` — List of services provided by this server
- L96 _public property_ `public string? ServerId { get; set; }` — attrs: `[PerforceTag("ServerID", Optional = true)]` — The server unique id
- L102 _public property_ `public int TimeZoneOffsetSecs { get; set; }` — attrs: `[PerforceTag("tzoffset", Optional = true)]` — Timezone offset from UTC, in seconds

### `Source/Programs/Shared/EpicGames.Perforce/Records/IntegrationAction.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.IntegrateAction`  
`public enum IntegrateAction`  
_public; L8-117_
- desc: Describes the action performed by the user when resolving the integration
- L14 _public* enumerator_ `BranchFrom` — attrs: `[PerforceEnum("branch from")]` — file did not previously exist; it was created as a copy of partner-file
- L20 _public* enumerator_ `BranchInto` — attrs: `[PerforceEnum("branch into")]` — partner-file did not previously exist; it was created as a copy of file.
- L26 _public* enumerator_ `MergeFrom` — attrs: `[PerforceEnum("merge from")]` — file was integrated from partner-file, accepting merge.
- L32 _public* enumerator_ `MergeInto` — attrs: `[PerforceEnum("merge into")]` — file was integrated into partner-file, accepting merge.
- L38 _public* enumerator_ `MovedFrom` — attrs: `[PerforceEnum("moved from")]` — file was integrated from partner-file, accepting theirs and deleting the original.
- L44 _public* enumerator_ `MovedInto` — attrs: `[PerforceEnum("moved into")]` — file was integrated into partner-file, accepting theirs and creating partner-file if it did not previously exist.
- L50 _public* enumerator_ `CopyFrom` — attrs: `[PerforceEnum("copy from")]` — file was integrated from partner-file, accepting theirs.
- L56 _public* enumerator_ `CopyInto` — attrs: `[PerforceEnum("copy into")]` — file was integrated into partner-file, accepting theirs.
- L62 _public* enumerator_ `Ignored` — attrs: `[PerforceEnum("ignored")]` — file was integrated from partner-file, accepting yours.
- L68 _public* enumerator_ `IgnoredBy` — attrs: `[PerforceEnum("ignored by")]` — file was integrated into partner-file, accepting yours.
- L74 _public* enumerator_ `DeleteFrom` — attrs: `[PerforceEnum("delete from")]` — file was integrated from partner-file, and partner-file had been previously deleted.
- L80 _public* enumerator_ `DeleteInto` — attrs: `[PerforceEnum("delete into")]` — file was integrated into partner-file, and file had been previously deleted.
- L86 _public* enumerator_ `EditFrom` — attrs: `[PerforceEnum("edit from")]` — file was integrated from partner-file, and file was edited within the p4 resolve process.
- L92 _public* enumerator_ `EditInto` — attrs: `[PerforceEnum("edit into")]` — file was integrated into partner-file, and partner-file was reopened for edit before submission.
- L98 _public* enumerator_ `AddFrom` — attrs: `[PerforceEnum("add from")]` — file was integrated from a deleted partner-file, and partner-file was reopened for add (that is, someone restored a deleted file by syncing back to a pre-deleted revision and adding the file).
- L104 _public* enumerator_ `AddInto` — attrs: `[PerforceEnum("add into")]` — file was integrated into previously nonexistent partner-file, and partner-file was reopened for add before submission.
- L110 _public* enumerator_ `Undid` — attrs: `[PerforceEnum("undid")]` — The resulting revision has "undid" the edited changes (content and history) from the previously submitted revision(s)
- L116 _public* enumerator_ `UndoneBy` — attrs: `[PerforceEnum("undone by")]` — The previous revision(s) have been "undone by" the resulting revision, known as the "undone" revision.

### `Source/Programs/Shared/EpicGames.Perforce/Records/IntegrationRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.IntegrationRecord`  
`public class IntegrationRecord`  
_public; L10-59_
- desc: Stores integration information for a file revision
- L16 _public property_ `public IntegrateAction Action { get; set; }` — attrs: `[PerforceTag("how")]` — The integration action performed for this file
- L22 _public property_ `public string OtherFile { get; set; }` — attrs: `[PerforceTag("file")]` — The partner file for this integration
- L28 _public property_ `public int StartRevisionNumber { get; set; }` — attrs: `[PerforceTag("srev")]` — Min revision of the partner file for this integration
- L34 _public property_ `public int EndRevisionNumber { get; set; }` — attrs: `[PerforceTag("erev")]` — Max revision of the partner file for this integration
- L39-42 _private ctor_ `private IntegrationRecord()` — Private constructor for serialization
- L48-58 _public method_ `public override string ToString()` — Summarize this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/LoginOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.LoginOptions`  
`public enum LoginOptions`  
_public; L11-34_
- attrs: `[Flags]`
- desc: Options for the login command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `AllHosts = 1` — Obtain a ticket that is valid for all IP addresses.
- L26 _public* enumerator_ `PrintTicket = 2` — Display the ticket, rather than storing it in the local ticket file.
- L33 _public* enumerator_ `Status = 4` — Display the status of the current ticket, if one exists. Use with -a to display status for all hosts, or with -h host to display status for a specfic host. Users with super access can provide a username argument to display the status of that username's ticket.

### `Source/Programs/Shared/EpicGames.Perforce/Records/LoginRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.LoginRecord`  
`public class LoginRecord`  
_public; L8-32_
- desc: Information about the logged in user
- L14 _public property_ `public string? User { get; set; }` — attrs: `[PerforceTag("User")]` — The current user according to the Perforce environment
- L19 _public property_ `public string? Ticket { get; set; }` — The ticket created for the user. Set only if LoginOptions.PrintTicket is set.
- L25 _public property_ `public long TicketExpiration { get; set; }` — attrs: `[PerforceTag("TicketExpiration", Optional = true)]` — Time at which the current ticket expires
- L31 _public property_ `public string? AuthedBy { get; set; }` — attrs: `[PerforceTag("AuthedBy", Optional = true)]` — Method by which the current user was authorized

### `Source/Programs/Shared/EpicGames.Perforce/Records/MergeOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.MergeOptions`  
`public enum MergeOptions`  
_public; L11-52_
- attrs: `[Flags]`
- desc: Options for the merge command
- L16 _public* enumerator_ `None = 0` — No options
- L21 _public* enumerator_ `Preview = 1` — Preview the merge
- L26 _public* enumerator_ `Force = 2` — Forces the operation
- L31 _public* enumerator_ `AsFiles = 4` — Performs the merge with files only
- L36 _public* enumerator_ `AsStreamSpec = 8` — Performs the merge as a stream spec
- L41 _public* enumerator_ `Stream = 16` — Use stream based merging
- L46 _public* enumerator_ `ReverseMapping = 32` — Revere the mapping direction
- L51 _public* enumerator_ `Source = 64` — Treat the from path as the source

### `Source/Programs/Shared/EpicGames.Perforce/Records/MergeRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.MergeRecord`  
`public class MergeRecord`  
_public; L10-34_
- desc: Response from a merge
- L16 _public property_ `public string FromFile { get; set; }` — attrs: `[PerforceTag("fromFile")]` — The file being merged from
- L21 _public property_ `public int? StartFromRev => ...` — The starting revision, as an integer (null if 'none')
- L27 _public property_ `public string StartFromRevText { get; set; }` — attrs: `[PerforceTag("startFromRev")]` — The first revision being merged (or 'none')
- L33 _public property_ `public int EndFromRev { get; set; }` — attrs: `[PerforceTag("endFromRev")]` — The last revision being merged

### `Source/Programs/Shared/EpicGames.Perforce/Records/MoveOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.MoveOptions`  
`public enum MoveOptions`  
_public; L11-32_
- attrs: `[Flags]`
- desc: Options for the p4 edit command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `KeepWorkspaceFiles = 1` — Keep existing workspace files; mark the file as open for edit even if the file is not in the client view.
- L26 _public* enumerator_ `RenameOnly = 2` — Rename existing files without altering content or type to a new target.
- L31 _public* enumerator_ `PreviewOnly = 4` — Preview which files would be opened for edit, without actually changing any files or metadata.

### `Source/Programs/Shared/EpicGames.Perforce/Records/MoveRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.MoveRecord`  
`public class MoveRecord`  
_public; L8-59_
- desc: Information about a file opened for move
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace
- L26 _public property_ `public int WorkingRevision { get; set; }` — attrs: `[PerforceTag("workRev", Optional = true)]` — The working revision number of the file that was synced
- L32 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken when syncing the file
- L38 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — Type of the file
- L43-49 _private ctor_ `private MoveRecord()` — Private constructor for serialization
- L55-58 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/OpenedOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.OpenedOptions`  
`public enum OpenedOptions`  
_public; L11-32_
- attrs: `[Flags]`
- desc: Options for the p4 opened command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `AllWorkspaces = 1` — List open files in all client workspaces
- L26 _public* enumerator_ `ShortOutput = 2` — Short output; do not output the revision number or file type. This option is more efficient, particularly when using the -a (all-workspaces) option at large sites.
- L31 _public* enumerator_ `Exclusive = 4` — List files opened exclusively

### `Source/Programs/Shared/EpicGames.Perforce/Records/OpenedRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.OpenedRecord`  
`public class OpenedRecord`  
_public; L12-79_
- attrs: `[DebuggerDisplay("{DepotFile}")]`
- desc: Record returned by the opened command
- L18 _public property_ `public string Stream { get; set; }` — attrs: `[PerforceTag("stream", Optional = true)]` — The stream spec opened for edit
- L24 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile", Optional = true)]` — Depot path to file. May be unset if this record describes a stream spec.
- L30 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile", Optional = true)]` — Client path to file (not returned if OpenedOptions.ShortOutput is set)
- L36 _public property_ `public string? MovedFile { get; set; }` — attrs: `[PerforceTag("movedFile", Optional = true)]` — For a move action (either move/add or move/delete) indicates the counterpart depot path
- L42 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev", Optional = true)]` — The revision of the file (not returned if OpenedOptions.ShortOutput is set)
- L48 _public property_ `public int HaveRevision { get; set; }` — attrs: `[PerforceTag("haveRev", Optional = true)]` — The synced revision of the file (may be 'none' for adds) (not returned if OpenedOptions.ShortOutput is set)
- L54 _public property_ `public FileAction Action { get; set; }` — attrs: `[PerforceTag("action", Optional = true)]` — Open action, if opened in your workspace
- L60 _public property_ `public int Change { get; set; }` — attrs: `[PerforceTag("change", Optional = true)]` — Change containing the open file
- L66 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type", Optional = true)]` — New filetype for the file
- L72 _public property_ `public string User { get; set; }` — attrs: `[PerforceTag("user")]` — User with the file open
- L78 _public property_ `public string Client { get; set; }` — attrs: `[PerforceTag("client", Optional = true)]` — Client with the file open

### `Source/Programs/Shared/EpicGames.Perforce/Records/PrintRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PrintRecord`  
`public class PrintRecord`  
_public; L10-53_
- desc: Record containing information about a printed file
- L16 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L22 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev")]` — Revision number of the file
- L28 _public property_ `public int ChangeNumber { get; set; }` — attrs: `[PerforceTag("change")]` — Change number of the file
- L34 _public property_ `public FileAction Action { get; set; }` — attrs: `[PerforceTag("action")]` — Last action to the file
- L40 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — File type
- L46 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time")]` — Submit time of the file
- L52 _public property_ `public long FileSize { get; set; }` — attrs: `[PerforceTag("fileSize", Optional = true)]` — Size of the file in bytes

#### class `EpicGames.Perforce.PrintRecord`  
`public class PrintRecord<T> : PrintRecord where T : class`  
_public; L59-65_
- inherits: `PrintRecord`
- constraints: `where T : class`
- desc: Information about a printed file, with its data
- L64 _public property_ `public T? Contents { get; set; }` — Data for the file

### `Source/Programs/Shared/EpicGames.Perforce/Records/PropertyRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.PropertyRecord`  
`public class PropertyRecord`  
_public; L10-23_
- desc: Contains information about a Perforce property
- L16 _public property_ `public string Name { get; set; }` — attrs: `[PerforceTag("name")]` — The name of the property
- L22 _public property_ `public string Value { get; set; }` — attrs: `[PerforceTag("value")]` — The value of the property

### `Source/Programs/Shared/EpicGames.Perforce/Records/ReconcileOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ReconcileOptions`  
`public enum ReconcileOptions`  
_public; L11-57_
- attrs: `[Flags]`
- desc: Options for the p4 reconcile command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `Edit = 1` — Find files in the client workspace that have been modified outside of Perforce, and open them for edit.
- L26 _public* enumerator_ `Add = 2` — Find files in the client workspace that are not under Perforce control and open them for add.
- L31 _public* enumerator_ `Delete = 4` — Find files missing from the client workspace, but present on the server; open these files for delete, but only if these files are in the user's have list.
- L36 _public* enumerator_ `PreviewOnly = 8` — Preview which files would be opened for add, without actually changing any files or metadata.
- L41 _public* enumerator_ `AllowWildcards = 16` — Add filenames that contain special (wildcard) characters.
- L46 _public* enumerator_ `NoIgnore = 32` — Do not perform any ignore checking.
- L51 _public* enumerator_ `LocalFileSyntax = 64` — Display output in local file syntax with relative paths, similar to the workspace-centric view of p4 status.
- L56 _public* enumerator_ `UseFileModification = 128` — use file modification time before digest to optimize

### `Source/Programs/Shared/EpicGames.Perforce/Records/ReconcileRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ReconcileRecord`  
`public class ReconcileRecord`  
_public; L8-59_
- desc: Information about a reconciled file
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace
- L26 _public property_ `public int WorkingRevision { get; set; }` — attrs: `[PerforceTag("workRev")]` — The working revision number of the file that was synced
- L32 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken when syncing the file
- L38 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — Type of the file
- L43-49 _private ctor_ `private ReconcileRecord()` — Private constructor for serialization
- L55-58 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/ReopenRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ReopenRecord`  
`public class ReopenRecord`  
_public; L8-10_
- desc: Record returned from a reopen command

### `Source/Programs/Shared/EpicGames.Perforce/Records/ReshelveOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ReshelveOptions`  
`public enum ReshelveOptions`  
_public; L11-27_
- attrs: `[Flags]`
- desc: Options for the p4 reshelve command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `Force = 1` — When the same file already exists in the target changelist, force the overwriting of it.
- L26 _public* enumerator_ `Promote = 2` — Promote the new or target changelist where it can be accessed by other edge servers participating in the multi-server configuration. Once a shelved change has been promoted, all subsequent local modifications to the shelf are also pushed to the commit server and remain until the shelf is deleted.

### `Source/Programs/Shared/EpicGames.Perforce/Records/ResolveOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ResolveOptions`  
`public enum ResolveOptions`  
_public; L11-67_
- attrs: `[Flags]`
- desc: Options for the p4 resolve command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `Automatic = 1` — Automatically accept the Perforce-recommended file revision.
- L26 _public* enumerator_ `AcceptYours = 2` — Accept Yours, ignore theirs.
- L31 _public* enumerator_ `AcceptTheirs = 4` — Accept Theirs.
- L36 _public* enumerator_ `SafeAccept = 8` — If either yours or theirs is different from base, (and the changes are in common) accept that revision. If both are different from base, skip this file.
- L41 _public* enumerator_ `ForceAccept = 16` — Automatically accept the Perforce-recommended file revision.
- L46 _public* enumerator_ `IgnoreWhitespaceOnly = 32` — Ignore whitespace-only changes (for instance, a tab replaced by eight spaces)
- L51 _public* enumerator_ `IgnoreWhitespace = 64` — Ignore whitespace altogether (for instance, deletion of tabs or other whitespace)
- L56 _public* enumerator_ `IgnoreLineEndings = 128` — Ignore differences in line-ending convention
- L61 _public* enumerator_ `ResolveAgain = 256` — Allow already resolved, but not yet submitted, files to be resolved again.
- L66 _public* enumerator_ `PreviewOnly = 512` — List the files that need resolving without actually performing the resolve.

### `Source/Programs/Shared/EpicGames.Perforce/Records/ResolveRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ResolveRecord`  
`public class ResolveRecord`  
_public; L8-76_
- desc: Information about a resolved file
- L14 _public property_ `public string? ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile", Optional = true)]` — Path to the file in the workspace
- L20 _public property_ `public string? FromFile { get; set; }` — attrs: `[PerforceTag("fromFile", Optional = true)]` — Path to the depot file that needs to be resolved
- L26 _public property_ `public string? ToFile { get; set; }` — attrs: `[PerforceTag("toFile", Optional = true)]` — Target file for the resolve
- L32 _public property_ `public string? How { get; set; }` — attrs: `[PerforceTag("how", Optional = true)]` — How the file was resolved
- L38 _public property_ `public int FromRevisionStart { get; set; }` — attrs: `[PerforceTag("startFromRev", Optional = true)]` — Start range of changes to be resolved
- L44 _public property_ `public int FromRevisionEnd { get; set; }` — attrs: `[PerforceTag("endFromRev", Optional = true)]` — Ending range of changes to be resolved
- L50 _public property_ `public string? ResolveType { get; set; }` — attrs: `[PerforceTag("resolveType", Optional = true)]` — The type of resolve to perform
- L56 _public property_ `public string? ContentResolveType { get; set; }` — attrs: `[PerforceTag("contentResolveType", Optional = true)]` — For content resolves, the type of resolve to be performed
- L61-66 _private ctor_ `private ResolveRecord()` — Private constructor for serialization
- L72-75 _public method_ `public override string? ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/RevertOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.RevertOptions`  
`public enum RevertOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the revert command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `Unchanged = 1` — Revert only those files that haven’t changed (in terms of content or filetype) since they were opened.
- L26 _public* enumerator_ `KeepWorkspaceFiles = 2` — Keep workspace files; the file(s) are removed from any changelists and Perforce records that the files as being no longer open, but the file(s) are unchanged in the client workspace.
- L31 _public* enumerator_ `PreviewOnly = 4` — List the files that would be reverted without actually performing the revert.
- L36 _public* enumerator_ `DeleteAddedFiles = 8` — Files that are open for add are to be deleted (wiped) from the workspace when reverted.

### `Source/Programs/Shared/EpicGames.Perforce/Records/RevertRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.RevertRecord`  
`public class RevertRecord`  
_public; L8-59_
- desc: Information about a reverted file
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace
- L26 _public property_ `public int HaveRevision { get; set; }` — attrs: `[PerforceTag("haveRev")]` — The revision number that is now in the workspace
- L32 _public property_ `public string OldAction { get; set; }` — attrs: `[PerforceTag("oldAction")]` — The previous action that the file was opened as
- L38 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken to revert the file
- L43-49 _private ctor_ `private RevertRecord()` — Private constructor for serialization
- L55-58 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/RevisionRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.RevisionRecord`  
`public class RevisionRecord`  
_public; L11-98_
- desc: Stores a revision record for a file
- L17 _public property_ `public int RevisionNumber { get; set; }` — attrs: `[PerforceTag("rev")]` — The revision number of this file
- L23 _public property_ `public int ChangeNumber { get; set; }` — attrs: `[PerforceTag("change")]` — The changelist responsible for this revision of the file
- L29 _public property_ `public FileAction Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action performed to the file in this revision
- L35 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — Type of the file
- L41 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time")]` — Timestamp of this modification
- L47 _public property_ `public string UserName { get; set; }` — attrs: `[PerforceTag("user")]` — Author of the changelist
- L53 _public property_ `public string ClientName { get; set; }` — attrs: `[PerforceTag("client")]` — Client that submitted this changelist
- L59 _public property_ `public long FileSize { get; set; }` — attrs: `[PerforceTag("fileSize", Optional = true)]` — Size of the file, or -1 if not specified
- L65 _public property_ `public string? Digest { get; set; }` — attrs: `[PerforceTag("digest", Optional = true)]` — Digest of the file, or null if not specified
- L71 _public property_ `public string Description { get; set; }` — attrs: `[PerforceTag("desc")]` — Description of this changelist
- L77 _public property_ `public List<IntegrationRecord> Integrations { get; }` — attrs: `[PerforceRecordList]` — Integration records for this revision
- L82-88 _private ctor_ `private RevisionRecord()` — Private constructor for serialization
- L94-97 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/ServerRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ServerRecord`  
`public class ServerRecord`  
_public; L10-35_
- desc: Represents a Perforce clientspec
- L16 _public property_ `public string ServerId { get; set; }` — attrs: `[PerforceTag("ServerID")]` — The server id
- L22 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("Type")]` — The server type
- L28 _public property_ `public string? Name { get; set; }` — attrs: `[PerforceTag("Name", Optional = true)]` — The P4NAME used by this server (optional).
- L34 _public property_ `public string? Address { get; set; }` — attrs: `[PerforceTag("Address", Optional = true)]` — The P4PORT used by this server (optional).

### `Source/Programs/Shared/EpicGames.Perforce/Records/ShelveOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.ShelveOptions`  
`public enum ShelveOptions`  
_public; L11-27_
- attrs: `[Flags]`
- desc: Options for the p4 shelve command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `OnlyChanged = 1` — Only shelve files that have changed
- L26 _public* enumerator_ `Overwrite = 2` — Force the overwriting of any existing shelved files in a pending changelist with the contents of their client workspace copies.

### `Source/Programs/Shared/EpicGames.Perforce/Records/ShelveRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.ShelveRecord`  
`public class ShelveRecord`  
_public; L8-51_
- desc: Contains information about a shelved file
- L14 _public property_ `public int Change { get; set; }` — attrs: `[PerforceTag("change", Optional = true)]` — The changelist containing the shelved file
- L20 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L26 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev")]` — The revision number of the file that was shelved
- L32 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — The action to be applied to the file
- L37-41 _private ctor_ `private ShelveRecord()` — Private constructor for serialization
- L47-50 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/SizeOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.SizesOptions`  
`public enum SizesOptions`  
_public; L12-49_
- attrs: `[Flags]`
- desc: Options for the sizes command
- L17 _public* enumerator_ `None = 0` — No options are set
- L22 _public* enumerator_ `AllRevisions = 1` — For each file, list all revisions within a specified revision range, rather than only the highest revision in the range.
- L27 _public* enumerator_ `LimitToArchiveDepots = 2` — Display files in archive depots.
- L32 _public* enumerator_ `CalculateSum = 4` — Calculate the sum of the file sizes for the specified file argument.
- L37 _public* enumerator_ `DisplayForShelvedFilesOnly = 8` — Display size information for shelved files only. If you use this option, revision specifications are not permitted.
- L42 _public* enumerator_ `ExcludeLazyCopies = 16` — When calculating size information, exclude lazy copies.
- L48 _public* enumerator_ `FileSizeAsExpectedInTheWorkspace = 32` — Reports the file size as expected in the workspace, defaulting to the client's environment, accounting for line-endings, charset conversion of unicode/utf8/utf16 filetypes (including the BOM for utf8 type files) and keyword expansion for +k type files.

### `Source/Programs/Shared/EpicGames.Perforce/Records/SizesRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.SizesRecord`  
`public class SizesRecord`  
_public; L8-33_
- desc: Record returned by the sizes command
- L14 _public property_ `public string? DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile", Optional = true)]` — Depot path to file
- L20 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev", Optional = true)]` — Revision for opened file(s)
- L26 _public property_ `public long Size { get; set; }` — attrs: `[PerforceTag("fileSize")]` — Size for file(s)
- L32 _public property_ `public int Count { get; set; }` — attrs: `[PerforceTag("fileCount", Optional = true)]` — Count of file(s)

### `Source/Programs/Shared/EpicGames.Perforce/Records/StreamLogOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.StreamLogOptions`  
`public enum StreamLogOptions`  
_public; L11-42_
- attrs: `[Flags]`
- desc: Options for the 'streamlog' command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `IncludeHistory = 1` — Include inherited stream history (-i)
- L26 _public* enumerator_ `DisplayStreamContent = 2` — Display the stream content history instead of stream name history (-h)
- L31 _public* enumerator_ `IncludeTimes = 4` — Display the time as well as the date (-t)
- L36 _public* enumerator_ `LongOutput = 8` — List long output, with the full text of each changelist description (-l)
- L41 _public* enumerator_ `TruncatedLongOutput = 16` — List long output, with the full text of each changelist description truncated at 250 characters (-L)

### `Source/Programs/Shared/EpicGames.Perforce/Records/StreamLogRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.StreamLogRecord`  
`public class StreamLogRecord`  
_public; L12-43_
- attrs: `[DebuggerDisplay("{Number}: {Description}")]`
- desc: Contains summary information about a stream log record
- L18 _public property_ `public int Number { get; set; }` — attrs: `[PerforceTag("change")]` — The changelist number
- L24 _public property_ `public DateTime Time { get; set; }` — attrs: `[PerforceTag("time")]` — The date the change was last modified
- L30 _public property_ `public string User { get; set; }` — attrs: `[PerforceTag("user")]` — The user that owns or submitted the change
- L36 _public property_ `public string? Client { get; set; }` — attrs: `[PerforceTag("client")]` — The client that owns the change
- L42 _public property_ `public string Description { get; set; }` — attrs: `[PerforceTag("desc")]` — Description for the changelist

### `Source/Programs/Shared/EpicGames.Perforce/Records/StreamOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.StreamOptions`  
`public enum StreamOptions`  
_public; L11-77_
- attrs: `[Flags]`
- desc: Options for a stream
- L16 _public* enumerator_ `None = 0` — No options are set
- L22 _public* enumerator_ `Unlocked = 1` — attrs: `[PerforceEnum("unlocked")]` — Enable other users' ability to edit or delete the stream. If locked, the stream specification cannot be deleted, and only its owner can modify it.
- L28 _public* enumerator_ `Locked = 2` — attrs: `[PerforceEnum("locked")]` — Disable other users' ability to edit or delete the stream. If locked, the stream specification cannot be deleted, and only its owner can modify it.
- L34 _public* enumerator_ `AllSubmit = 4` — attrs: `[PerforceEnum("allsubmit")]` — Specifies that all users can submit changes to the stream.
- L40 _public* enumerator_ `OwnerSubmit = 8` — attrs: `[PerforceEnum("ownersubmit")]` — Specifies that only the owner of the stream can submit changes to the stream.
- L46 _public* enumerator_ `ToParent = 16` — attrs: `[PerforceEnum("toparent")]` — Specifies whether integrations from the stream to its parent are expected.
- L52 _public* enumerator_ `NoToParent = 32` — attrs: `[PerforceEnum("notoparent")]` — Specifies whether integrations from the stream to its parent are expected.
- L58 _public* enumerator_ `FromParent = 64` — attrs: `[PerforceEnum("fromparent")]` — Specifies whether integrations to the stream from its parent are expected.
- L64 _public* enumerator_ `NoFromParent = 128` — attrs: `[PerforceEnum("notoparent")]` — Specifies whether integrations to the stream from its parent are expected.
- L70 _public* enumerator_ `MergeAny = 256` — attrs: `[PerforceEnum("mergeany")]` — Specifies whether the merge flow is restricted or whether merge is permitted from any other stream.
- L76 _public* enumerator_ `MergeDown = 512` — attrs: `[PerforceEnum("mergedown")]` — Specifies whether the merge flow is restricted or whether merge is permitted from any other stream.

### `Source/Programs/Shared/EpicGames.Perforce/Records/StreamRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.StreamRecord`  
`public class StreamRecord`  
_public; L11-121_
- desc: Represents a Perforce stream spec
- L17 _public property_ `public string Stream { get; set; }` — attrs: `[PerforceTag("Stream")]` — The stream path
- L23 _public property_ `public string Name { get; set; }` — attrs: `[PerforceTag("Name")]` — The stream name
- L29 _public property_ `public string Owner { get; set; }` — attrs: `[PerforceTag("Owner")]` — The Perforce user name of the user who owns the stream.
- L35 _public property_ `public DateTime Update { get; set; }` — attrs: `[PerforceTag("Update", Optional = true)]` — The date the stream specification was last modified.
- L41 _public property_ `public DateTime Access { get; set; }` — attrs: `[PerforceTag("Access", Optional = true)]` — The date and time that the stream was last used in any way.
- L47 _public property_ `public string? Parent { get; set; }` — attrs: `[PerforceTag("Parent", Optional = true)]` — The parent stream
- L53 _public property_ `public string? Type { get; set; }` — attrs: `[PerforceTag("Type", Optional = true)]` — The stream type
- L59 _public property_ `public string? Description { get; set; }` — attrs: `[PerforceTag("Description", Optional = true)]` — A textual description of the stream.
- L65 _public property_ `public StreamOptions Options { get; set; }` — attrs: `[PerforceTag("Options")]` — Options for this stream
- L71 _public property_ `public string? ParentView { get; set; }` — attrs: `[PerforceTag("ParentView", Optional = true)]` — Parent view
- L77 _public property_ `public List<string> Paths { get; }` — attrs: `[PerforceTag("Paths")]` — List of paths in the stream spec
- L83 _public property_ `public List<string> View { get; }` — attrs: `[PerforceTag("View", Optional = true)]` — Computed view for the stream
- L89 _public property_ `public List<string> ChangeView { get; }` — attrs: `[PerforceTag("ChangeView", Optional = true)]` — Specific changelists to import
- L94-99 _private ctor_ `private StreamRecord()` — Private constructor for serialization
- L111-120 _public ctor_ `public StreamRecord(string stream, string owner, string name, string parent, string type, string parentView, List<string> paths)` — Constructor

### `Source/Programs/Shared/EpicGames.Perforce/Records/StreamType.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.StreamType`  
`public enum StreamType`  
_public; L8-39_
- desc: Type of a Perforce stream
- L14 _public* enumerator_ `Mainline` — attrs: `[PerforceEnum("mainline")]` — A mainline stream
- L20 _public* enumerator_ `Development` — attrs: `[PerforceEnum("development")]` — A development stream
- L26 _public* enumerator_ `Release` — attrs: `[PerforceEnum("release")]` — A release stream
- L32 _public* enumerator_ `Virtual` — attrs: `[PerforceEnum("virtual")]` — A virtual stream
- L38 _public* enumerator_ `Task` — attrs: `[PerforceEnum("task")]` — A task stream

### `Source/Programs/Shared/EpicGames.Perforce/Records/StreamsOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.StreamsOptions`  
`public enum StreamsOptions`  
_public; L11-72_
- attrs: `[Flags]`
- desc: Options for a stream definition
- L17 _public* enumerator_ `Locked = 1` — attrs: `[PerforceEnum("locked")]` — The stream is locked
- L23 _public* enumerator_ `Unlocked = 2` — attrs: `[PerforceEnum("unlocked")]` — The stream is unlocked
- L29 _public* enumerator_ `OwnerSubmit = 4` — attrs: `[PerforceEnum("ownersubmit")]` — Only the owner may submit to the stream
- L35 _public* enumerator_ `AllSubmit = 8` — attrs: `[PerforceEnum("allsubmit")]` — Anyone may submit to the stream
- L41 _public* enumerator_ `ToParent = 16` — attrs: `[PerforceEnum("toparent")]` — Integrations from this stream to its parent are expected
- L47 _public* enumerator_ `NotToParent = 32` — attrs: `[PerforceEnum("notoparent")]` — Integrations from this stream from its parent are expected
- L53 _public* enumerator_ `FromParent = 64` — attrs: `[PerforceEnum("fromparent")]` — Integrations from this stream from its parent are expected
- L59 _public* enumerator_ `NotFromParent = 128` — attrs: `[PerforceEnum("nofromparent")]` — Integrations from this stream from its parent are expected
- L65 _public* enumerator_ `MergeDown = 256` — attrs: `[PerforceEnum("mergedown")]` — Undocumented?
- L71 _public* enumerator_ `MergeAny = 512` — attrs: `[PerforceEnum("mergeany")]` — Undocumented?

### `Source/Programs/Shared/EpicGames.Perforce/Records/StreamsRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.StreamsRecord`  
`public class StreamsRecord`  
_public; L10-108_
- desc: Contains information about a stream, as returned by the 'p4 streams' command
- L16 _public property_ `public string Stream { get; set; }` — attrs: `[PerforceTag("Stream")]` — Path to the stream
- L22 _public property_ `public DateTime Update { get; set; }` — attrs: `[PerforceTag("Update")]` — Last time the stream definition was updated
- L28 _public property_ `public DateTime Access { get; set; }` — attrs: `[PerforceTag("Access")]` — Last time the stream definition was accessed
- L34 _public property_ `public string Owner { get; set; }` — attrs: `[PerforceTag("Owner")]` — Owner of this stream
- L40 _public property_ `public string Name { get; set; }` — attrs: `[PerforceTag("Name")]` — Name of the stream. This may be modified after the stream is initially created, but it's underlying depot path will not change.
- L46 _public property_ `public string? Parent { get; set; }` — attrs: `[PerforceTag("Parent", Optional = true)]` — The parent stream
- L52 _public property_ `public StreamType Type { get; set; }` — attrs: `[PerforceTag("Type")]` — Type of the stream
- L58 _public property_ `public string? Description { get; set; }` — attrs: `[PerforceTag("desc", Optional = true)]` — User supplied description of the stream
- L64 _public property_ `public StreamsOptions Options { get; set; }` — attrs: `[PerforceTag("Options")]` — Options for the stream definition
- L70 _public property_ `public bool? FirmerThanParent { get; set; }` — attrs: `[PerforceTag("firmerThanParent")]` — Whether this stream is more stable than the parent stream
- L76 _public property_ `public bool ChangeFlowsToParent { get; set; }` — attrs: `[PerforceTag("changeFlowsToParent")]` — Whether changes from this stream flow to the parent stream
- L82 _public property_ `public bool ChangeFlowsFromParent { get; set; }` — attrs: `[PerforceTag("changeFlowsFromParent")]` — Whether changes from this stream flow from the parent stream
- L88 _public property_ `public string? BaseParent { get; set; }` — attrs: `[PerforceTag("baseParent", Optional = true)]` — The mainline branch associated with this stream
- L93-98 _private ctor_ `private StreamsRecord()` — Private constructor for serialization
- L104-107 _public method_ `public override string? ToString()` — Summarize this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/SubmitOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.SubmitOptions`  
`public enum SubmitOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the 'submit' command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `ReopenAsEdit = 1` — Reopen files for edit in the default changelist after submission.
- L26 _public* enumerator_ `SubmitUnchanged = 2` — All open files (with or without changes) are submitted to the depot. This is the default behavior of Helix Server.
- L31 _public* enumerator_ `RevertUnchanged = 4` — Only those files with content or type changes are submitted to the depot. Unchanged files are reverted.
- L36 _public* enumerator_ `LeaveUnchanged = 8` — Only those files with content or type changes are submitted to the depot. Any unchanged files are moved to the default changelist.

### `Source/Programs/Shared/EpicGames.Perforce/Records/SubmitRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.SubmitRecord`  
`public class SubmitRecord`  
_public; L8-46_
- desc: Contains information about a submitted changelist
- L14 _public property_ `public int OriginalChangeNumber { get; set; }` — attrs: `[PerforceTag("change", Optional = true)]` — Original changelist number
- L20 _public property_ `public int SubmittedChangeNumber { get; set; }` — attrs: `[PerforceTag("submittedChange", Optional = true)]` — Submitted changelist number
- L26-36 _public method_ `public void Merge(SubmitRecord other)` — Merge another submit record into this one. Perforce outputs multiple records for a submit command, so we merge them together for convenience.
- L42-45 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/SwitchClientOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.SwitchClientOptions`  
`public enum SwitchClientOptions`  
_public; L11-22_
- attrs: `[Flags]`
- desc: Options for the p4 client -s command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `IgnoreOpenFiles = 1` — Ignore files which are open for edit

### `Source/Programs/Shared/EpicGames.Perforce/Records/SyncAction.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.SyncAction`  
`public enum SyncAction`  
_public; L8-33_
- desc: Action performed to the file during a sync
- L14 _public* enumerator_ `Unknown` — attrs: `[PerforceEnum("none")]` — Unknown value
- L20 _public* enumerator_ `Added` — attrs: `[PerforceEnum("added")]` — The file was added during the sync
- L26 _public* enumerator_ `Updated` — attrs: `[PerforceEnum("updated")]` — The file was updated during the sync
- L32 _public* enumerator_ `Deleted` — attrs: `[PerforceEnum("deleted")]` — The file was deleted during the sync

### `Source/Programs/Shared/EpicGames.Perforce/Records/SyncOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.SyncOptions`  
`public enum SyncOptions`  
_public; L11-57_
- attrs: `[Flags]`
- desc: Options for the p4 sync command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `Force = 1` — Force the sync. Perforce performs the sync even if the client workspace already has the file at the specified revision. If the file is writable, it is overwritten.
- L26 _public* enumerator_ `KeepWorkspaceFiles = 2` — Keep existing workspace files; update the have list without updating the client workspace.
- L31 _public* enumerator_ `FullDepotSyntax = 4` — For scripting purposes, perform the sync on a list of valid file arguments in full depot syntax with a valid revision number.
- L36 _public* enumerator_ `PreviewOnly = 8` — Preview mode: Display the results of the sync without actually performing the sync.
- L41 _public* enumerator_ `NetworkPreviewOnly = 16` — Preview mode: Display a summary of the expected network traffic associated with a sync, without performing the sync.
- L46 _public* enumerator_ `DoNotUpdateHaveList = 32` — Populate a client workspace, but do not update the have list. Any file that is already synced or opened is bypassed with a warning message.
- L51 _public* enumerator_ `ReopenMovedFiles = 64` — Reopen files that are mapped to new locations in the depot, in the new location.
- L56 _public* enumerator_ `Safe = 128` — Safe sync: Compare the content in your client workspace against what was last synced.

### `Source/Programs/Shared/EpicGames.Perforce/Records/SyncRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.SyncRecord`  
`public class SyncRecord`  
_public; L12-61_
- attrs: `[DebuggerDisplay("{DepotFile}")]`
- desc: Information about a synced file
- L18 _public property_ `public Utf8String DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L24 _public property_ `public Utf8String Path { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace. Note: despite being a property called 'clientFile', this is not in client syntax.
- L30 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev")]` — The revision number of the file that was synced
- L36 _public property_ `public SyncAction Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken when syncing the file
- L42 _public property_ `public long FileSize { get; set; }` — attrs: `[PerforceTag("fileSize", Optional = true)]` — Size of the file
- L48 _public property_ `public long TotalFileSize { get; set; }` — attrs: `[PerforceTag("totalFileSize", Optional = true)]` — Stores the total size of all files that are being synced (only set for the first sync record)
- L54 _public property_ `public long TotalFileCount { get; set; }` — attrs: `[PerforceTag("totalFileCount", Optional = true)]` — Stores the total number of files that will be synced (only set for the first sync record)
- L60 _public property_ `public int Change { get; set; }` — attrs: `[PerforceTag("change", Optional = true)]` — Change that modified the file

### `Source/Programs/Shared/EpicGames.Perforce/Records/SyncSummaryRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.SyncSummaryRecord`  
`public class SyncSummaryRecord`  
_public; L8-27_
- desc: Information about a sync operation
- L14 _public property_ `public long TotalFileSize { get; set; }` — attrs: `[PerforceTag("totalFileSize")]` — The total size of all files synced
- L20 _public property_ `public long TotalFileCount { get; set; }` — attrs: `[PerforceTag("totalFileCount")]` — The total number of files synced
- L26 _public property_ `public int Change { get; set; }` — attrs: `[PerforceTag("change")]` — The changelist that was synced to

### `Source/Programs/Shared/EpicGames.Perforce/Records/UndoRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.UndoRecord`  
`public class UndoRecord`  
_public; L8-59_
- desc: Information about a file opened for Undo
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in the workspace
- L26 _public property_ `public int WorkingRevision { get; set; }` — attrs: `[PerforceTag("workRev")]` — The working revision number of the file that was synced
- L32 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Action taken when syncing the file
- L38 _public property_ `public string Type { get; set; }` — attrs: `[PerforceTag("type")]` — Type of the file
- L43-49 _private ctor_ `private UndoRecord()` — Private constructor for serialization
- L55-58 _public method_ `public override string? ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/UnshelveOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.UnshelveOptions`  
`public enum UnshelveOptions`  
_public; L11-27_
- attrs: `[Flags]`
- desc: Options for the p4 unshelve command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `ForceOverwrite = 1` — Force the overwriting of writable (but unopened) files during the unshelve operation.
- L26 _public* enumerator_ `PreviewOnly = 2` — Preview the results of the unshelve operation without actually restoring the files to your workspace.

### `Source/Programs/Shared/EpicGames.Perforce/Records/UnshelveRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.UnshelveRecord`  
`public class UnshelveRecord`  
_public; L8-45_
- desc: Information about an unshelved file
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public int Revision { get; set; }` — attrs: `[PerforceTag("rev")]` — The revision number of the file
- L26 _public property_ `public string Action { get; set; }` — attrs: `[PerforceTag("action")]` — Open action for the file
- L31-35 _private ctor_ `private UnshelveRecord()` — Private constructor for serialization
- L41-44 _public method_ `public override string ToString()` — Format this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/UpdateChangeOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.UpdateChangeOptions`  
`public enum UpdateChangeOptions`  
_public; L11-27_
- attrs: `[Flags]`
- desc: Options for the UpdateChange command
- L16 _public* enumerator_ `None = 0` — No options are specified
- L21 _public* enumerator_ `Force = 2` — Allows the description, modification date, or user of a submitted changelist to be edited. Editing a submitted changelist requires admin or super access.
- L26 _public* enumerator_ `Submitted = 4` — Update a submitted changelist. Only the Jobs:, Description:, or Type: fields can be updated, and only the submitter of the changelist can update the changelist.

### `Source/Programs/Shared/EpicGames.Perforce/Records/UserRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.UserRecord`  
`public class UserRecord`  
_public; L11-80_
- desc: Contains information about a Perforce user
- L17 _public property_ `public string UserName { get; set; }` — attrs: `[PerforceTag("User")]` — The name for the user
- L23 _public property_ `public string Email { get; set; }` — attrs: `[PerforceTag("Email")]` — Registered email address for reviews
- L29 _public property_ `public DateTime Update { get; set; }` — attrs: `[PerforceTag("Update", Optional = true)]` — Last time the user's information was updated
- L35 _public property_ `public DateTime Access { get; set; }` — attrs: `[PerforceTag("Access", Optional = true)]` — Last time the user's information was accessed
- L41 _public property_ `public string FullName { get; set; }` — attrs: `[PerforceTag("FullName")]` — The user's full name
- L47 _public property_ `public List<string> Reviews { get; }` — attrs: `[PerforceTag("Reviews", Optional = true)]` — Paths which the user is watching
- L53 _public property_ `public string? Type { get; set; }` — attrs: `[PerforceTag("Type", Optional = true)]` — The type of user
- L59 _public property_ `public string? AuthMethod { get; set; }` — attrs: `[PerforceTag("AuthMethod")]` — Method used to authenticate
- L64-70 _private ctor_ `private UserRecord()` — Private constructor for serialization
- L76-79 _public method_ `public override string ToString()` — Summarize this record for display in the debugger

### `Source/Programs/Shared/EpicGames.Perforce/Records/UsersOptions.cs` (EpicGames.Perforce)


#### enum `EpicGames.Perforce.UsersOptions`  
`public enum UsersOptions`  
_public; L11-37_
- attrs: `[Flags]`
- desc: Options for the p4 users command
- L16 _public* enumerator_ `None = 0` — No options specified
- L21 _public* enumerator_ `IncludeServiceUsers = 1` — Include service users in list.
- L26 _public* enumerator_ `OnlyMasterServer = 2` — On replica servers, only user information from the master server are reported.
- L31 _public* enumerator_ `IncludeLoginInfo = 4` — Login information: includes time of last password change and login ticket expiry, if applicable. You must be a Helix server superuser to use this option.
- L36 _public* enumerator_ `OnlyReplicaServer = 8` — On replica servers, only users who have used this replica server are reported.

### `Source/Programs/Shared/EpicGames.Perforce/Records/UsersRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.UsersRecord`  
`public class UsersRecord`  
_public; L12-49_
- attrs: `[DebuggerDisplay("{FullName}")]`
- desc: Contains information about a Perforce user
- L18 _public property_ `public string UserName { get; set; }` — attrs: `[PerforceTag("User")]` — The name for the user
- L24 _public property_ `public string Email { get; set; }` — attrs: `[PerforceTag("Email")]` — Registered email address for reviews
- L30 _public property_ `public DateTime Update { get; set; }` — attrs: `[PerforceTag("Update", Optional = true)]` — Last time the user's information was updated
- L36 _public property_ `public DateTime Access { get; set; }` — attrs: `[PerforceTag("Access", Optional = true)]` — Last time the user's information was accessed
- L42 _public property_ `public string FullName { get; set; }` — attrs: `[PerforceTag("FullName")]` — The user's full name
- L48 _public property_ `public string? Type { get; set; }` — attrs: `[PerforceTag("Type", Optional = true)]` — The type of user

### `Source/Programs/Shared/EpicGames.Perforce/Records/WhereRecord.cs` (EpicGames.Perforce)


#### class `EpicGames.Perforce.WhereRecord`  
`public class WhereRecord`  
_public; L8-52_
- desc: Contains information about a file's location in the workspace
- L14 _public property_ `public string DepotFile { get; set; }` — attrs: `[PerforceTag("depotFile")]` — Path to the file in the depot
- L20 _public property_ `public string ClientFile { get; set; }` — attrs: `[PerforceTag("clientFile")]` — Path to the file in client syntax
- L26 _public property_ `public string Path { get; set; }` — attrs: `[PerforceTag("path")]` — Path to the file on dist
- L32 _public property_ `public bool Unmap { get; set; }` — attrs: `[PerforceTag("unmap", Optional = true)]` — Indicates that the given file or path is being unmapped from the workspace
- L37-42 _private ctor_ `private WhereRecord()` — Private constructor for serialization
- L48-51 _public method_ `public override string ToString()` — Summarize this record for display in the debugger
