# CSharp / EpicGames.Core

- project root: `Source/Programs/Shared/EpicGames.Core`
- files: 141; symbols: 4309
- symbol kinds: class=332, const=54, ctor=240, dtor=1, enum=33, enumerator=416, event=1, field=621, indexer=9, interface=26, method=1924, operator=72, property=545, record struct=2, struct=33
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Core/AppContainer.cs` (EpicGames.Core)


#### class `EpicGames.Core.AppContainerException`  
`public class AppContainerException : Exception`  
_public; L17-28_
- inherits: `Exception`
- desc: Exception for AppContainer
- L20-22 _public ctor_ `public AppContainerException(string? message) : base(message)` — (inheritdoc)
- L25-27 _public ctor_ `public AppContainerException(string? message, Exception? innerException) : base(message, innerException)` — (inheritdoc)

#### class `EpicGames.Core.AppContainer`  
`public sealed class AppContainer : IDisposable`  
_public; L34-313_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `IDisposable`
- desc: Manages a setup and initialization of an AppContainer on Windows
- L73 _private method_ `private static extern IntPtr FreeSid(IntPtr pSid)` — attrs: `[DllImport("advapi32.dll")]`
- L76 _private method_ `private static extern bool ConvertSidToStringSid(IntPtr pSid, out IntPtr ptrSid)` — attrs: `[DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]`
- L79 _private method_ `private static extern bool DeleteProcThreadAttributeList(IntPtr lpAttributeList)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L82 _private* method_ `static extern IntPtr LocalFree(IntPtr hMem)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L86 _private method_ `private static extern bool UpdateProcThreadAttribute( IntPtr lpAttributeList, uint dwFlags, IntPtr attribute, IntPtr lpValue, IntPtr cbSize, IntPtr lpPreviousValue, IntPtr lpReturnSize)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L97 _private method_ `private static extern bool InitializeProcThreadAttributeList( IntPtr lpAttributeList, int dwAttributeCount, int dwFlags, ref IntPtr lpSize)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L104 _private method_ `private static extern HRESULT CreateAppContainerProfile( [MarshalAs(UnmanagedType.LPWStr)] string pszAppContainerName, [MarshalAs(UnmanagedType.LPWStr)] string pszDisplayName, [MarshalAs(UnmanagedType.LPWStr)] string pszDescription, [In] SID_AND_ATTRIBUTES[] pCapabilities, uint dwCapabilityCount, out IntPtr ppSidAppContainerSid)` — attrs: `[DllImport("userenv.dll", SetLastError = false, ExactSpelling = true)]`
- L113 _private method_ `private static extern HRESULT GetAppContainerFolderPath( [MarshalAs(UnmanagedType.LPWStr)] string pszAppContainerSid, [MarshalAs(UnmanagedType.LPWStr)] out string ppszPath)` — attrs: `[DllImport("userenv.dll", SetLastError = false, ExactSpelling = true)]`
- L118 _private method_ `private static extern HRESULT DeleteAppContainerProfile([MarshalAs(UnmanagedType.LPWStr)] string pszAppContainerName)` — attrs: `[DllImport("userenv.dll", SetLastError = false, ExactSpelling = true)]`
- L121 _private method_ `private static extern HRESULT DeriveAppContainerSidFromAppContainerName([MarshalAs(UnmanagedType.LPWStr)] string pszAppContainerName, out IntPtr ppsidAppContainerSid)` — attrs: `[DllImport("userenv.dll", SetLastError = false, ExactSpelling = true)]`
- L123-143 _private method_ `private static string ManagedConvertSidToStringSid(IntPtr sid)`
- L145-153 _private method_ `private static HRESULT HResultFromWin32(uint errorCode)`
- L160 _public property_ `public string ContainerName { get; }` — Name of the container
- L162 _private field_ `private readonly IntPtr _sid`
- L163 _private field_ `private IntPtr _attribList`
- L164 _private field_ `private bool _isDisposed`
- L166-170 _private ctor_ `private AppContainer(string containerName, IntPtr sid)`
- L173-190 _public method_ `public void Dispose()` — (inheritdoc)
- L201-216 _public method_ `public static AppContainer Create(string containerName, string displayName, string description, bool errorIfExists = false)` — Create an AppContainer
- L223-230 _public method_ `public static void Delete(string containerName)` — Delete an AppContainer
- L237-247 _public method_ `public DirectoryInfo GetFolderPath()` — Get home directory path for the AppContainer
- L254-263 _public method_ `public void AddDirectoryAccess(DirectoryInfo dirInfo, FileSystemRights rights)` — Grant permissions to a directory for current AppContainer
- L270-312 _internal method_ `internal IntPtr GetAttributeList()` — Get attribute list for use in STARTUPINFOEX struct given to CreateProcess

#### enum `EpicGames.Core.AppContainer.HRESULT`  
`private enum HRESULT : uint`  
_private; L37-42_
- inherits: `uint`
- L39 _public* enumerator_ `S_FALSE = 0x0001`
- L40 _public* enumerator_ `S_OK = 0x0000`
- L41 _public* enumerator_ `E_INVALIDARG = 0x80070057`

#### enum `EpicGames.Core.AppContainer.PROC_THREAD_ATTRIBUTES`  
`private enum PROC_THREAD_ATTRIBUTES`  
_private; L44-47_
- L46 _public* enumerator_ `PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES = 0x00020009`

#### enum `EpicGames.Core.AppContainer.Win32Error`  
`private enum Win32Error : uint`  
_private; L49-52_
- inherits: `uint`
- L51 _public* enumerator_ `ERROR_ALREADY_EXISTS = 0x000000B7`

#### struct `EpicGames.Core.AppContainer.SID_AND_ATTRIBUTES`  
`private struct SID_AND_ATTRIBUTES`  
_private; L56-60_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Win32 API naming convention")]`
- L58 _public field_ `public IntPtr Sid`
- L59 _public field_ `public int Attributes`

#### struct `EpicGames.Core.AppContainer.SECURITY_CAPABILITIES`  
`private struct SECURITY_CAPABILITIES`  
_private; L64-70_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Win32 API naming convention")]`
- L66 _public field_ `public IntPtr AppContainerSid`
- L67 _public field_ `public IntPtr Capabilities`
- L68 _public field_ `public uint CapabilityCount`
- L69 _public field_ `public uint Reserved`

### `Source/Programs/Shared/EpicGames.Core/ArrayExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.ArrayExtensions`  
`public static class ArrayExtensions`  
_public; L10-29_
- desc: Extension methods for arrays.
- L20-28 _public method_ `public static TOut[] ConvertAll<TIn, TOut>(this TIn[] input, Func<TIn, TOut> func)` — Converts an array of elements to a different type

### `Source/Programs/Shared/EpicGames.Core/AssemblyUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.AssemblyUtils`  
`public static class AssemblyUtils`  
_public; L15-124_
- desc: Utilities for dealing with assembly loading
- L23-26 _public method_ `public static string GetOriginalLocation(this Assembly thisAssembly)` — Gets the original location (path and filename) of an assembly. This method is using Assembly.Location property to properly resolve original assembly path in case shadow copying is enabled.
- L31 _public property_ `public static FileVersionInfo ExecutableVersion => ...` — Version info of the executable which runs this code.
- L37-47 _public method_ `public static void InstallRecursiveAssemblyResolver(string rootDirectory)` — Installs an assembly resolver, which will load *any* assembly which exists recursively within the supplied folder.
- L53-82 _public method_ `public static void AddFileToAssemblyCache(string assemblyPath)` — Adds a file to the assembly cache.
- L84-115 _private method_ `private static void AddAssemblyCacheResolverIfNecessary()`
- L118 _private field_ `private static readonly Dictionary<string, string> s_assemblyLocationCache = ...`
- L118 _private field_ `private static readonly Dictionary< s_assemblyLocationCache = new(StringComparer.OrdinalIgnoreCase)`
- L120 _private field_ `private static readonly Dictionary<string, DateTime> s_assemblyWriteTimes = ...`
- L120 _private field_ `private static readonly Dictionary< s_assemblyWriteTimes = new(StringComparer.OrdinalIgnoreCase)`
- L122 _private field_ `private static bool s_addedToAssemblyResolver = false`

### `Source/Programs/Shared/EpicGames.Core/AsyncEvent.cs` (EpicGames.Core)


#### class `EpicGames.Core.AsyncEvent`  
`public class AsyncEvent`  
_public; L11-84_
- desc: Wrapper to allow awaiting an event being signalled, similar to an AutoResetEvent.
- L16 _private* field_ `TaskCompletionSource<bool> _source = new(TaskCreationOptions.RunContinuationsAsynchronously)` — Completion source to wait on
- L21 _public method_ `public void Set()` — Legacy name for Pulse.
- L26-42 _public method_ `public void Pulse()` — Pulse the event, allowing any captured copies of the task to continue.
- L47-61 _public method_ `public void Reset()` — Resets an event which is latched to the set state.
- L66-69 _public method_ `public void Latch()` — Move the task to completed without returning it to an unset state. A call to Reset() is required to clear it.
- L75-78 _public method_ `public bool IsSet()` — Determines if this event is set
- L83 _public property_ `public Task Task => ...` — Waits for this event to be set

### `Source/Programs/Shared/EpicGames.Core/AsyncPipeline.cs` (EpicGames.Core)


#### class `EpicGames.Core.AsyncPipeline`  
`public sealed class AsyncPipeline : IAsyncDisposable`  
_public; L15-124_
- inherits: `IAsyncDisposable`
- desc: Manages a set of async tasks forming a pipeline, which can be cancelled and awaited as a complete unit. The first exception thrown by an individual task is captured and reported back to the main thread.
- L17 _private* field_ `readonly List<Task> _tasks`
- L18 _private* field_ `readonly CancellationToken _cancellationToken`
- L19 _private* field_ `CancellationTokenSource _cancellationSource`
- L20 _private* field_ `ExceptionDispatchInfo? _exceptionDispatchInfo`
- L25 _public property_ `public bool IsFaulted => ...` — Tests whether the pipeline has failed
- L31-36 _public ctor_ `public AsyncPipeline(CancellationToken cancellationToken)` — Constructor
- L39-64 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L70-75 _public method_ `public Task AddTask(Func<CancellationToken, Task> taskFunc)` — Adds a new task to the pipeline.
- L82-90 _public method_ `public Task[] AddTasks(int count, Func<CancellationToken, Task> taskFunc)` — Adds several tasks to the pipeline.
- L92-111 _private* method_ `async Task RunGuardedAsync(Func<CancellationToken, Task> taskFunc)`
- L116-123 _public method_ `public async Task WaitForCompletionAsync()` — Waits for all tasks to complete, and throws any exceptions

#### class `EpicGames.Core.AsyncPipelineExtensions`  
`public static class AsyncPipelineExtensions`  
_public; L129-215_
- desc: Extension methods for async pipelines
- L138 _public method_ `public static Task AddTask<T>(this AsyncPipeline pipeline, ChannelReader<T> reader, Func<T, CancellationToken, ValueTask> taskFunc)` — Adds a worker to process items from a channel
- L150 _public method_ `public static Task AddTask<TInput, TOutput>(this AsyncPipeline pipeline, ChannelReader<TInput> reader, ChannelWriter<TOutput> writer, Func<TInput, CancellationToken, ValueTask<TOutput>> taskFunc)` — Adds a worker to process items from a channel
- L161-169 _public method_ `public static Task[] AddTasks<T>(this AsyncPipeline pipeline, int count, ChannelReader<T> reader, Func<T, CancellationToken, ValueTask> taskFunc)` — Adds a worker to process items from a channel
- L181-189 _public method_ `public static Task[] AddTasks<TInput, TOutput>(this AsyncPipeline pipeline, int count, ChannelReader<TInput> reader, ChannelWriter<TOutput> writer, Func<TInput, CancellationToken, ValueTask<TOutput>> taskFunc)` — Adds a worker to process items from a channel
- L191-201 _private* method_ `static async Task ProcessItemsAsync<T>(ChannelReader<T> reader, Func<T, CancellationToken, ValueTask> taskFunc, CancellationToken cancellationToken)`
- L203-214 _private* method_ `static async Task ProcessItemsAsync<TInput, TOutput>(ChannelReader<TInput> reader, ChannelWriter<TOutput> writer, Func<TInput, CancellationToken, ValueTask<TOutput>> taskFunc, CancellationToken cancellationToken)`

### `Source/Programs/Shared/EpicGames.Core/AsyncQueue.cs` (EpicGames.Core)


#### class `EpicGames.Core.AsyncQueue`  
`public sealed class AsyncQueue : IAsyncDisposable`  
_public; L14-80_
- inherits: `IAsyncDisposable`
- desc: Manages a set of tasks run in the background on a fixed number of tasks. Similar to AsyncThreadPoolWorkQueue.
- L16 _private* field_ `readonly List<Task> _workerTasks = []`
- L17 _private* field_ `readonly Channel<Func<CancellationToken, Task>> _queuedTasks = ...`
- L17 _private* field_ `readonly Channel<Func< _queuedTasks = Channel.CreateUnbounded<Func<CancellationToken, Task>>()`
- L18 _private* field_ `readonly CancellationTokenSource _cancellationSource = new()`
- L24-30 _public ctor_ `public AsyncQueue(int numWorkers)` — Constructor
- L36-40 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — Finish executing all the tasks and wait for them to complete
- L43-49 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L55 _public method_ `public void Enqueue(Func<CancellationToken, Task> task)` — Enqueue a task to be executed
- L61-79 _private method_ `private async Task RunWorkerAsync()` — Worker executing tasks. Any exception encountered will be bubbled up as all calls are awaited.

### `Source/Programs/Shared/EpicGames.Core/AsyncThreadPoolWorkQueue.cs` (EpicGames.Core)


#### class `EpicGames.Core.AsyncThreadPoolWorkQueue`  
`public sealed class AsyncThreadPoolWorkQueue : IDisposable`  
_public; L15-141_
- inherits: `IDisposable`
- desc: Allows queuing a large number of async tasks to the default thread pool In contrast to ThreadPoolWorkQueue, the number of concurrent workers can be set
- L20 _private field_ `private readonly Lock _lockObject = new()` — Object used for controlling access to updating _lockObject
- L25 _private field_ `private readonly ManualResetEvent _emptyEvent = new(true)` — Event which indicates whether the queue is empty.
- L30 _private field_ `private readonly int _numWorkers` — Number of concurrent workers that will process tasks
- L35 _private field_ `private int _numOutstandingTasks` — Number of tasks remaining in the queue. This is updated in an atomic way.
- L40 _private* field_ `readonly Channel<Func<CancellationToken, Task>> _tasks = ...` — Channel used as the queue for tasks
- L40 _private* field_ `readonly Channel<Func< _tasks = Channel.CreateUnbounded<Func<CancellationToken, Task>>()` — Channel used as the queue for tasks
- L46-49 _public ctor_ `public AsyncThreadPoolWorkQueue(int numWorkers)` — Constructor
- L54-57 _public method_ `public void Dispose()` — Dispose
- L63-70 _public method_ `public async Task EnqueueAsync(Func<CancellationToken, Task> task)` — Enqueue a task to be executed
- L77-98 _public method_ `public async Task ExecuteAsync(CancellationToken cancellationToken = default)` — Execute all enqueued tasks In contrast to Parallel.ForEachAsync, new tasks can be enqueued during execution.
- L104-120 _private method_ `private async Task WorkerAsync(CancellationToken cancellationToken)` — Worker executing tasks. Any exception encountered will be bubbled up as all calls are awaited.
- L127-140 _private method_ `private void SetEventState()` — When the number of outstanding tasks transitions between 0 and 1 and vice-versa, we need to set the event based on the actual counter. While the adjustment of the counter happens with interlocked instructions, the setting of the event must be done under a lock to serialize the set/reset

### `Source/Programs/Shared/EpicGames.Core/AsyncUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.AsyncUtils`  
`public static class AsyncUtils`  
_public; L14-246_
- desc: Utility functions for manipulating async tasks
- L21-24 _public method_ `public static Task AsTask(this CancellationToken token)` — Converts a cancellation token to a waitable task
- L31-34 _public method_ `public static Task<T> AsTask<T>(this CancellationToken token)` — Converts a cancellation token to a waitable task
- L40-49 _public method_ `public static async Task IgnoreCanceledExceptionsAsync(this Task task)` — Waits for a task to complete, ignoring any cancellation exceptions
- L57-64 _public method_ `public static async Task<T> AbandonOnCancelAsync<T>(this Task<T> task, CancellationToken cancellationToken)` — Returns a task that will be abandoned if a cancellation token is activated. This differs from the normal cancellation pattern in that the task will run to completion, but waiting for it can be cancelled.
- L73-85 _public method_ `public static bool TryGetResult<T>(this Task<T> task, out T result)` — Attempts to get the result of a task, if it has finished
- L93-96 _public method_ `public static Task DelayNoThrow(TimeSpan time, CancellationToken token)` — Waits for a time period to elapse or the task to be cancelled, without throwing an cancellation exception
- L102-132 _public method_ `public static void RemoveCompleteTasks(this List<Task> tasks)` — Removes all the complete tasks from a list, allowing each to throw exceptions as necessary
- L139-158 _public method_ `public static List<T> RemoveCompleteTasks<T>(this List<Task<T>> tasks)` — Removes all the complete tasks from a list, allowing each to throw exceptions as necessary
- L167-196 _public method_ `public static async IAsyncEnumerable<T> PrefetchAsync<T>(this IAsyncEnumerable<T> source, [EnumeratorCancellation] CancellationToken cancellationToken)` — Starts prefetching the next item from an async enumerator while the current one is being processes
- L206-216 _public method_ `public static IAsyncEnumerable<T> Prefetch<T>(this IAsyncEnumerable<T> source, int count, CancellationToken cancellationToken = default)` — Starts prefetching a number of items from an async enumerator while the current one is being processes
- L223 _public method_ `public static Task WaitOneAsync(this WaitHandle handle, CancellationToken cancellationToken = default)` — Waits for a native wait handle to be signaled
- L231-245 _public method_ `public static async Task WaitOneAsync(this WaitHandle handle, int timeoutMs, CancellationToken cancellationToken = default)` — Waits for a native wait handle to be signaled

### `Source/Programs/Shared/EpicGames.Core/BackgroundTask.cs` (EpicGames.Core)


#### class `EpicGames.Core.BackgroundTask`  
`public sealed class BackgroundTask : IAsyncDisposable`  
_public; L12-106_
- inherits: `IAsyncDisposable`
- desc: Runs a task in the background and allows stopping it on demand
- L14 _private* field_ `readonly Func<CancellationToken, Task> _runTask`
- L14 _private* field_ `readonly Func< _runTask`
- L15 _private* field_ `Task? _task`
- L16 _private* field_ `readonly CancellationTokenSource _cancellationTokenSource = new()`
- L21 _public property_ `public Task? Task => ...` — Accessor for the underlying task
- L27-30 _public ctor_ `public BackgroundTask(Func<CancellationToken, Task> runTask)` — Constructor. Note that the task does not start until Start is called.
- L33-37 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L44-49 _public method_ `public static BackgroundTask StartNew(Func<CancellationToken, Task> runTask)` — Creates and starts a new background task instance
- L56-61 _public method_ `public static BackgroundTask<T> StartNew<T>(Func<CancellationToken, Task<T>> runTask)` — Creates and starts a new background task instance
- L66-73 _public method_ `public void Start()` — Starts the task
- L79-92 _public method_ `public async Task StopAsync(CancellationToken cancellationToken = default)` — Signals the cancellation token and waits for the task to finish
- L98-105 _public method_ `public async Task WaitAsync(CancellationToken cancellationToken)` — Waits for the task to complete

#### class `EpicGames.Core.BackgroundTask`  
`public sealed class BackgroundTask<T> : IAsyncDisposable`  
_public; L111-180_
- inherits: `IAsyncDisposable`
- desc: Runs a task in the background and allows stopping it on demand
- L113 _private* field_ `readonly Func<CancellationToken, Task<T>> _runTask`
- L113 _private* field_ `readonly Func< _runTask`
- L114 _private* field_ `Task<T>? _task`
- L115 _private* field_ `readonly CancellationTokenSource _cancellationTokenSource = new()`
- L120 _public property_ `public Task<T>? Task => ...` — Accessor for the underlying task
- L126-129 _public ctor_ `public BackgroundTask(Func<CancellationToken, Task<T>> runTask)` — Constructor. Note that the task does not start until Start is called.
- L132-136 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L141-148 _public method_ `public void Start()` — Starts the task
- L154-167 _public method_ `public async Task StopAsync(CancellationToken cancellationToken = default)` — Signals the cancellation token and waits for the task to finish
- L172-179 _public method_ `public Task<T> WaitAsync(CancellationToken cancellationToken = default)` — Waits for the task to complete

### `Source/Programs/Shared/EpicGames.Core/BinaryArchive.cs` (EpicGames.Core)


#### class `EpicGames.Core.BinaryArchive`  
`public static class BinaryArchive`  
_public; L15-437_
- desc: Common functionality for dealing with generic type serialization in binary archives
- L77 _private* field_ `static readonly ConcurrentDictionary<Type, TypeSerializer> s_typeToSerializerInfo = ...`
- L77 _private* field_ `static readonly ConcurrentDictionary< s_typeToSerializerInfo = new() { [typeof(byte)] = TypeSerializer.Create(reader => reader.ReadByte(), (writer, value) => writer.WriteByte(value)), [typeof(sbyte)] = TypeSerializer.Create(reader => reader.ReadSignedByte(), (wri ...`
- L90 _private* field_ `static readonly ConcurrentDictionary<Type, ContentHash> s_typeToDigest = ...`
- L90 _private* field_ `static readonly ConcurrentDictionary< s_typeToDigest = new()`
- L91 _private* field_ `static readonly ConcurrentDictionary<ContentHash, Type> s_digestToType = ...`
- L91 _private* field_ `static readonly ConcurrentDictionary< s_digestToType = new()`
- L93-96 _private* method_ `static MethodInfo GetMethodInfo(Expression<Action> expr)`
- L98-101 _private* method_ `static MethodInfo GetMethodInfo<T>(Expression<Action<T>> expr)`
- L103-106 _private* method_ `static MethodInfo GetGenericMethodInfo<T, T1>(Expression<Action<T, T1>> expr)`
- L108 _private* field_ `static readonly MethodInfo s_readBoolMethodInfo = GetMethodInfo<BinaryArchiveReader>(x => x.ReadBool())`
- L109 _private* field_ `static readonly MethodInfo s_readArrayMethodInfo = GetGenericMethodInfo<BinaryArchiveReader, Func<int>>((x, y) => x.ReadArray(y))`
- L110 _private* field_ `static readonly MethodInfo s_readPolymorphicObjectMethodInfo = GetMethodInfo(() => ReadObject(null!))`
- L111 _private* field_ `static readonly MethodInfo s_writeBoolMethodInfo = GetMethodInfo<BinaryArchiveWriter>(x => x.WriteBool(false))`
- L112 _private* field_ `static readonly MethodInfo s_writeArrayMethodInfo = GetGenericMethodInfo<BinaryArchiveWriter, Action<int>>((x, y) => x.WriteArray(null!, y))`
- L113 _private* field_ `static readonly MethodInfo s_writePolymorphicObjectMethodInfo = GetMethodInfo(() => WritePolymorphicObject(null!, null!))`
- L121-132 _public method_ `public static void Write<T>(this BinaryArchiveWriter writer, T value)` — Writes an arbitrary type to the given archive. May be an object or value type.
- L138-143 _public method_ `public static void RegisterType(Type type)` — Registers the given type. Allows serializing/deserializing it through calls to ReadType/WriteType.
- L149-158 _public method_ `public static void RegisterTypes(Assembly assembly)` — Registers all types in the given assembly with the BinarySerializableAttribute attribute for serialization
- L165-168 _public method_ `public static Type? ReadType(this BinaryArchiveReader reader)` — Reads a tyoe from the archive
- L175-178 _public method_ `public static void WriteType(this BinaryArchiveWriter writer, Type type)` — Writes a type to an archive
- L180-190 _private* method_ `static object? ReadNewPolymorphicObject(BinaryArchiveReader reader)`
- L197-200 _public method_ `public static object? ReadObject(this BinaryArchiveReader reader)` — Reads an object from the archive
- L202-209 _private* method_ `static void WriteNewPolymorphicObject(BinaryArchiveWriter writer, object value)`
- L211-214 _private* method_ `static void WritePolymorphicObject(this BinaryArchiveWriter writer, object value)`
- L222-237 _private* method_ `static TypeSerializer FindOrAddSerializerInfo(Type type, Type? converterType = null)` — Finds an existing serializer for the given type, or creates one
- L245-324 _private* method_ `static TypeSerializer CreateTypeSerializer(Type type, Type? converterType = null)` — Creates a serializer for the given type
- L326-372 _private* method_ `static void GenerateClassWriterMethod(DynamicMethod writerMethod, List<PropertyInfo> properties)`
- L374-417 _private* method_ `static void GenerateClassReaderMethod(DynamicMethod readerMethod, ConstructorInfo constructorInfo, List<PropertyInfo> properties)`
- L419-426 _private* method_ `static void GenerateConverterReaderForwardingMethod(DynamicMethod readerMethod, FieldInfo converterField, MethodInfo targetMethod)`
- L428-436 _private* method_ `static void GenerateConverterWriterForwardingMethod(DynamicMethod writerMethod, FieldInfo converterField, MethodInfo targetMethod)`

#### class `EpicGames.Core.BinaryArchive.Instantiator`  
`class Instantiator<T> where T : class, new()`  
_private*; L17-20_
- constraints: `where T : class, new()`
- L19 _public field_ `public static T Instance = new()`

#### class `EpicGames.Core.BinaryArchive.TypeSerializer`  
`sealed class TypeSerializer`  
_private*; L22-75_
- L24 _public property_ `public MethodInfo ReadMethodInfo { get; }`
- L25 _public property_ `public Func<BinaryArchiveReader, object> ReadMethod { get; }`
- L26 _public property_ `public MethodInfo WriteMethodInfo { get; }`
- L27 _public property_ `public Action<BinaryArchiveWriter, object> WriteMethod { get; }`
- L29-37 _public ctor_ `public TypeSerializer(MethodInfo readMethodInfo, MethodInfo writeMethodInfo)`
- L39-53 _private* method_ `static Func<BinaryArchiveReader, object> CreateBoxedReadMethod(Type type, MethodInfo methodInfo)`
- L55-67 _private* method_ `static Action<BinaryArchiveWriter, object> CreateBoxedWriteMethod(Type type, MethodInfo methodInfo)`
- L69-74 _public method_ `public static TypeSerializer Create<T>(Expression<Func<BinaryArchiveReader, T>> readerExpr, Expression<Action<BinaryArchiveWriter, T>> writerExpr)`

### `Source/Programs/Shared/EpicGames.Core/BinaryArchiveAttributes.cs` (EpicGames.Core)


#### class `EpicGames.Core.BinaryIgnoreAttribute`  
`public sealed class BinaryIgnoreAttribute : Attribute`  
_public; L11-19_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Instructs the serializer to ignore this property during serialization
- L16-18 _public ctor_ `public BinaryIgnoreAttribute()` — Constructor

#### class `EpicGames.Core.BinarySerializableAttribute`  
`public sealed class BinarySerializableAttribute : Attribute`  
_public; L25-33_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Marks this class as supporting binary serialization. Used to automatically register types via BinaryArchive.RegisterTypes().
- L30-32 _public ctor_ `public BinarySerializableAttribute()` — Constructor

#### class `EpicGames.Core.BinaryConverterAttribute`  
`public sealed class BinaryConverterAttribute : Attribute`  
_public; L39-54_
- attrs: `[AttributeUsage(AttributeTargets.Property | AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Instructs the serializer to use a specific converter for this property or class
- L44 _public property_ `public Type Type { get; }` — The serializer type
- L50-53 _public ctor_ `public BinaryConverterAttribute(Type type)` — Constructor

### `Source/Programs/Shared/EpicGames.Core/BinaryArchiveReader.cs` (EpicGames.Core)


#### class `EpicGames.Core.BinaryArchiveReader`  
`public sealed class BinaryArchiveReader : IDisposable`  
_public; L16-675_
- inherits: `IDisposable`
- desc: Reads data from a binary output stream. Similar to the NET Framework BinaryReader class, but supports fast serialization of object graphs and container types, and supports nullable objects. Significantly faster than BinaryReader due to the expectation that the whole stream is in memory before deserialization.
- L21 _private* field_ `Stream? _stream` — The input stream.
- L26 _private* field_ `byte[]? _buffer` — The input buffer
- L31 _private* field_ `int _bufferPos` — Current position within the buffer
- L36 _private* field_ `readonly List<object?> _objects = []` — List of previously serialized objects
- L42-45 _public ctor_ `public BinaryArchiveReader(byte[] buffer)` — Constructor
- L51-54 _public ctor_ `public BinaryArchiveReader(FileReference fileName)` — Constructor
- L60-64 _public ctor_ `public BinaryArchiveReader(Stream stream)` — Constructor
- L69-75 _public method_ `public void Dispose()` — Dispose of the stream owned by this reader
- L81-84 _public method_ `public bool ReadBool()` — Reads a bool from the stream
- L90-95 _public method_ `public byte ReadByte()` — Reads a single byte from the stream
- L101-104 _public method_ `public sbyte ReadSignedByte()` — Reads a single signed byte from the stream
- L110-113 _public method_ `public short ReadShort()` — Reads a single short from the stream
- L119-124 _public method_ `public ushort ReadUnsignedShort()` — Reads a single unsigned short from the stream
- L131-134 _public method_ `public int ReadInt()` — attrs: `[MethodImpl(MethodImplOptions.AggressiveInlining)]` — Reads a single int from the stream
- L141-146 _public method_ `public uint ReadUnsignedInt()` — attrs: `[MethodImpl(MethodImplOptions.AggressiveInlining)]` — Reads a single unsigned int from the stream
- L152-155 _public method_ `public long ReadLong()` — Reads a single long from the stream
- L161-166 _public method_ `public ulong ReadUnsignedLong()` — Reads a single unsigned long from the stream
- L172-175 _public method_ `public double ReadDouble()` — Reads a double (64 bit floating point value) from the stream
- L181-195 _public method_ `public string? ReadString()` — Reads a string from the stream
- L201-204 _public method_ `public LogEvent ReadLogEvent()` — Reads a LogEvent from the stream
- L210-213 _public method_ `public byte[]? ReadByteArray()` — Reads a byte array from the stream
- L219-222 _public method_ `public short[]? ReadShortArray()` — Reads a short array from the stream
- L228-231 _public method_ `public int[]? ReadIntArray()` — Reads an int array from the stream
- L238-251 _private method_ `private T[]? ReadPrimitiveArray<T>(int elementSize) where T : struct` — Reads an array of primitive types from the stream
- L258-261 _public method_ `public byte[] ReadFixedSizeByteArray(int length)` — Reads a byte array from the stream
- L268-271 _public method_ `public short[] ReadFixedSizeShortArray(int length)` — Reads a short array from the stream
- L278-281 _public method_ `public int[] ReadFixedSizeIntArray(int length)` — Reads an int array from the stream
- L289-294 _private method_ `private T[] ReadFixedSizePrimitiveArray<T>(int elementSize, int elementCount) where T : struct` — Reads an array of primitive types from the stream
- L301-305 _private method_ `private void ReadBulkData(Array data, int size)` — Reads bulk data from the stream into the given buffer
- L311-327 _public method_ `public T[]? ReadArray<T>(Func<T> readElement)` — Reads an array of items
- L335-351 _public method_ `public List<T>? ReadList<T>(Func<T> readElement)` — Reads a list of items
- L359-375 _public method_ `public HashSet<T>? ReadHashSet<T>(Func<T> readElement)` — Reads a hashset of items
- L384-400 _public method_ `public HashSet<T>? ReadHashSet<T>(Func<T> readElement, IEqualityComparer<T> comparer)` — Reads a hashset of items
- L408-424 _public method_ `public SortedSet<T>? ReadSortedSet<T>(Func<T> readElement)` — Reads a sortedset of items
- L433-449 _public method_ `public SortedSet<T>? ReadSortedSet<T>(Func<T> readElement, IComparer<T> comparer)` — Reads a sortedset of items
- L459-475 _public method_ `public Dictionary<TK, TV>? ReadDictionary<TK, TV>(Func<TK> readKey, Func<TV> readValue) where TK : notnull` — Reads a dictionary of items
- L486-502 _public method_ `public Dictionary<TK, TV>? ReadDictionary<TK, TV>(Func<TK> readKey, Func<TV> readValue, IEqualityComparer<TK> comparer) where TK : notnull` — Reads a dictionary of items
- L509-519 _public method_ `public Nullable<T> ReadNullable<T>(Func<T> readValue) where T : struct` — Reads a nullable object from the archive
- L527-537 _public method_ `public T? ReadOptionalObject<T>(Func<T> read) where T : class` — Reads an object, which may be null, from the archive. Does not handle de-duplicating object references.
- L548-565 _public method_ `public T? ReadObjectReference<T>(Func<T> createObject, Action<T> readObject) where T : class` — Reads an object reference from the stream. Each referenced object will only be serialized once using the supplied delegates. Reading an object instance is done in two phases; first the object is created and its reference stored in the unique object list, then the object contents are read. This allows the object to serialize a reference to itself.
- L573-594 _public method_ `public object? ReadUntypedObjectReference(Func<object?> readObject)` — Reads an object reference from the stream. Each object will only be serialized once using the supplied delegate; subsequent reads reference the original. Since the reader only receives the object reference when the CreateObject delegate returns, it is not possible for the object to serialize a reference to itself.
- L603-624 _public method_ `public object? ReadUntypedObjectReference(Func<BinaryArchiveReader, object?> readObject)` — attrs: `[MethodImpl(MethodImplOptions.AggressiveInlining)]` — Reads an object reference from the stream. Each object will only be serialized once using the supplied delegate; subsequent reads reference the original. Since the reader only receives the object reference when the CreateObject delegate returns, it is not possible for the object to serialize a reference to itself.
- L633 _public method_ `public T? ReadObjectReference<T>(Func<T> readObject) where T : class` — Reads an object reference from the stream. Each object will only be serialized once using the supplied delegate; subsequent reads reference the original. Since the reader only receives the object reference when the CreateObject delegate returns, it is not possible for the object to serialize a reference to itself.
- L643 _public method_ `public T? ReadObjectReference<T>(Func<BinaryArchiveReader, T> readObject) where T : class` — attrs: `[MethodImpl(MethodImplOptions.AggressiveInlining)]` — Reads an object reference from the stream. Each object will only be serialized once using the supplied delegate; subsequent reads reference the original. Since the reader only receives the object reference when the CreateObject delegate returns, it is not possible for the object to serialize a reference to itself.
- L652-659 _public method_ `public static T NotNull<T>(T? param) where T : class` — attrs: `[return: NotNull]` — Helper method for validating that deserialized objects are not null
- L667-674 _public method_ `public static T NotNullStruct<T>(T? param) where T : struct` — Helper method for validating that deserialized objects are not null

### `Source/Programs/Shared/EpicGames.Core/BinaryArchiveWriter.cs` (EpicGames.Core)


#### class `EpicGames.Core.BinaryArchiveWriter`  
`public sealed class BinaryArchiveWriter : IDisposable`  
_public; L14-589_
- inherits: `IDisposable`
- desc: Writes data to a binary output stream. Similar to the NET Framework BinaryWriter class, but supports fast serialization of object graphs and container types, and supports nullable objects.
- L35 _private* field_ `static readonly ReferenceComparer s_referenceComparerInstance = new()` — Instance of the ReferenceComparer class which can be shared by all archive writers
- L40 _private* field_ `Stream? _stream` — The output stream being written to
- L45 _private* field_ `byte[] _buffer` — Buffer for data to be written to the stream
- L50 _private* field_ `int _bufferPos` — Current position within the output buffer
- L55 _private* field_ `readonly Dictionary<object, int> _objectToUniqueId = ...` — Map of object instance to unique id
- L55 _private* field_ `readonly Dictionary< _objectToUniqueId = new(s_referenceComparerInstance)` — Map of object instance to unique id
- L61-65 _public ctor_ `public BinaryArchiveWriter(Stream stream)` — Constructor
- L71-74 _public ctor_ `public BinaryArchiveWriter(FileReference fileName) : this(File.Open(fileName.FullName, FileMode.Create, FileAccess.Write, FileShare.Read))` — Constructor
- L79-84 _public method_ `public void Dispose()` — Flushes this stream, and disposes the stream
- L89-96 _public method_ `public void Flush()` — Writes all buffered data to disk
- L102-112 _private method_ `private void EnsureSpace(int numBytes)` — Ensures there is a minimum amount of space in the output buffer
- L118-121 _public method_ `public void WriteBool(bool value)` — Writes a bool to the output
- L127-134 _public method_ `public void WriteByte(byte value)` — Writes a single byte to the output
- L140-143 _public method_ `public void WriteSignedByte(sbyte value)` — Writes a single signed byte to the output
- L149-152 _public method_ `public void WriteShort(short value)` — Writes a single short to the output
- L158-166 _public method_ `public void WriteUnsignedShort(ushort value)` — Writes a single unsigned short to the output
- L172-175 _public method_ `public void WriteInt(int value)` — Writes a single int to the output
- L181-191 _public method_ `public void WriteUnsignedInt(uint value)` — Writes a single unsigned int to the output
- L197-200 _public method_ `public void WriteLong(long value)` — Writes a single long to the output
- L206-220 _public method_ `public void WriteUnsignedLong(ulong value)` — Writes a single unsigned long to the output
- L226-229 _public method_ `public void WriteDouble(double value)` — Writes a double (64 bit floating point value) to the stream
- L235-247 _public method_ `public void WriteString(string? value)` — Writes a string to the output
- L253-256 _public method_ `public void WriteLogEvent(LogEvent value)` — Writes a LogEvent to the output
- L262-265 _public method_ `public void WriteByteArray(byte[]? data)` — Writes an array of bytes to the output
- L271-274 _public method_ `public void WriteShortArray(short[]? data)` — Writes an array of shorts to the output
- L280-283 _public method_ `public void WriteIntArray(int[]? data)` — Writes an array of ints to the output
- L290-301 _private method_ `private void WritePrimitiveArray<T>(T[]? data, int elementSize) where T : struct` — Writes an array of primitive types to the output.
- L307-310 _public method_ `public void WriteFixedSizeByteArray(byte[] data)` — Writes an array of bytes to the output
- L316-319 _public method_ `public void WriteFixedSizeShortArray(short[] data)` — Writes an array of shorts to the output
- L325-328 _public method_ `public void WriteFixedSizeIntArray(int[] data)` — Writes an array of ints to the output
- L335-338 _private method_ `private void WriteFixedSizePrimitiveArray<T>(T[] data, int elementSize) where T : struct` — Writes an array of primitive types to the output.
- L345-365 _private method_ `private void WriteBulkData(Array data, int size)` — Writes primitive data from the given array to the output buffer.
- L373-387 _public method_ `public void WriteArray<T>(T[]? items, Action<T> writeElement)` — Write an array of items to the archive
- L395-409 _public method_ `public void WriteList<T>(IReadOnlyList<T>? items, Action<T> writeElement)` — Write a list of items to the archive
- L417-431 _public method_ `public void WriteHashSet<T>(HashSet<T> set, Action<T> writeElement)` — Writes a hashset of items
- L439-453 _public method_ `public void WriteSortedSet<T>(SortedSet<T> set, Action<T> writeElement)` — Writes a sortedset of items
- L463-478 _public method_ `public void WriteDictionary<TK, TV>(IReadOnlyDictionary<TK, TV> dictionary, Action<TK> writeKey, Action<TV> writeValue) where TK : notnull` — Writes a dictionary of items
- L486-497 _public method_ `public void WriteNullable<T>(Nullable<T> item, Action<T> writeValue) where T : struct` — Writes a nullable object to the archive
- L505-516 _public method_ `public void WriteOptionalObject<T>(T obj, Action writeObject) where T : class` — Writes an object to the output, checking whether it is null or not. Does not preserve object references; each object written is duplicated.
- L521-524 _public method_ `public void WriteNullObjectReference()` — Writes a null object reference to the output.
- L531-537 _public method_ `public void WriteObjectReference(object? obj, Action writeObject)` — Writes an object to the output. If the specific instance has already been written, preserves the reference to that.
- L544-547 _public method_ `public void WriteObjectReference<T>(T obj, Action writeObject) where T : class?` — Writes an object to the output. If the specific instance has already been written, preserves the reference to that.
- L554-560 _public method_ `public void WriteObjectReference<T>(T obj, Action<BinaryArchiveWriter, T> writeObject) where T : class?` — Writes an object to the output. If the specific instance has already been written, preserves the reference to that.
- L567-588 _private method_ `private bool WriteObjectReferenceUniqueId(object? obj)` — Writes a unique id for the given object.

#### class `EpicGames.Core.BinaryArchiveWriter.ReferenceComparer`  
`class ReferenceComparer : IEqualityComparer<object>`  
_private*; L19-30_
- inherits: `IEqualityComparer<object>`
- desc: Comparer which tests for reference equality between two objects
- L21-24 _private* method_ `bool IEqualityComparer<object>.Equals(object? a, object? b)`
- L26-29 _private* method_ `int IEqualityComparer<object>.GetHashCode(object x)`

### `Source/Programs/Shared/EpicGames.Core/BinaryConverter.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IBinaryConverter`  
`public interface IBinaryConverter`  
_public; L12-18_
- desc: Base interface for a binary converter. Implementations must derive from IBinaryConverter{TValue} instead
- L17 _public* property_ `int Version { get; }` — Converter version number

#### interface `EpicGames.Core.IBinaryConverter`  
`public interface IBinaryConverter<TValue> : IBinaryConverter`  
_public; L24-39_
- inherits: `IBinaryConverter`
- desc: Interface for converting serializing object to and from a binary format
- L31 _public* method_ `TValue Read(BinaryArchiveReader reader)` — Reads a value from the archive
- L38 _public* method_ `void Write(BinaryArchiveWriter writer, TValue value)` — Writes a value to the archive

#### class `EpicGames.Core.BinaryConverter`  
`public static class BinaryConverter`  
_public; L44-98_
- desc: Registration of IBinaryConverter instances
- L49 _private* field_ `static readonly ConcurrentDictionary<Type, Type> s_typeToConverterType = ...` — Map from type to the converter type
- L49 _private* field_ `static readonly ConcurrentDictionary< s_typeToConverterType = new()` — Map from type to the converter type
- L56-62 _public method_ `public static void RegisterConverter(Type type, Type converterType)` — Explicitly register the converter for a type. If Type is a generic type, the converter should also be a generic type with the same type arguments.
- L70-97 _public method_ `public static bool TryGetConverterType(Type type, out Type? converterType)` — Attempts to get the converter for a particular type

### `Source/Programs/Shared/EpicGames.Core/BinaryFormatterUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.BinaryFormatterUtils`  
`public static class BinaryFormatterUtils`  
_public; L11-56_
- desc: Utility functions for serializing using the DataContractSerializer xml (previously BinaryFormatter which is no longer supported)
- L18-23 _public method_ `public static T Load<T>(FileReference location)` — Load an object from a file on disk, using DataContractSerializer
- L30-36 _public method_ `public static void Save(FileReference location, object obj)` — Saves a file to disk, using DataContractSerializer
- L43-55 _public method_ `public static void SaveIfDifferent(FileReference location, object obj)` — Saves a file to disk using DataContractSerializer, without updating the timestamp if it hasn't changed

### `Source/Programs/Shared/EpicGames.Core/BinaryReaderExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.BinaryReaderExtensions`  
`public static class BinaryReaderExtensions`  
_public; L12-221_
- desc: Extension methods for BinaryReader
- L20-23 _public method_ `public static T ReadObject<T>(this BinaryReader reader) where T : class, IBinarySerializable` — Read an objects from a binary reader
- L30-33 _public method_ `public static string[]? ReadStringArray(this BinaryReader reader)` — Read an array of strings from a binary reader
- L41-44 _public method_ `public static T[]? ReadArray<T>(this BinaryReader reader) where T : class, IBinarySerializable` — Read an array of objects from a binary reader
- L53-67 _public method_ `public static T[]? ReadArray<T>(this BinaryReader reader, Func<T> readElement)` — Read an array of objects from a binary reader
- L74-77 _public method_ `public static List<string>? ReadStringList(this BinaryReader reader)` — Read a list of strings from a binary reader
- L85-88 _public method_ `public static List<T>? ReadList<T>(this BinaryReader reader) where T : class, IBinarySerializable` — Read a list of objects from a binary reader
- L97-111 _public method_ `public static List<T>? ReadList<T>(this BinaryReader reader, Func<T> readElement)` — Read a list of objects from a binary reader
- L122-138 _public method_ `public static Dictionary<TKey, TValue>? ReadDictionary<TKey, TValue>(this BinaryReader reader, Func<TKey> readKey, Func<TValue> readValue) where TKey : notnull` — Read a list of objects from a binary reader
- L147-157 _public method_ `public static T? ReadNullable<T>(this BinaryReader reader, Func<T> readItem) where T : class` — Read a nullable object from a binary reader
- L165-220 _public method_ `public static object? ReadObject(this BinaryReader reader, Type objectType)` — Reads a value of a specific type from a binary reader

### `Source/Programs/Shared/EpicGames.Core/BinaryWriterExtensions.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IBinarySerializable`  
`public interface IBinarySerializable`  
_public; L14-21_
- desc: Interface that can be implemented by objects to support BinaryWriter container functionality. Also implies that derived objects will have a constructor taking a single BinaryReader argument (similar to how the system ISerializable interface assumes a specific constructor)
- L20 _public* method_ `void Write(BinaryWriter writer)` — Write an item

#### class `EpicGames.Core.BinaryWriterExtensions`  
`public static class BinaryWriterExtensions`  
_public; L26-234_
- desc: Extension methods for BinaryWriter class
- L33-36 _public method_ `public static void Write(this BinaryWriter writer, IBinarySerializable item)` — Writes an item implementing the IBinarySerializable interface to a binary writer. Included for symmetry with standard Writer.Write(X) calls.
- L43-46 _public method_ `public static void Write(this BinaryWriter writer, string[] items)` — Writes an array of strings to a binary writer.
- L54-57 _public method_ `public static void Write<T>(this BinaryWriter writer, T[] items) where T : class, IBinarySerializable` — Writes an array to a binary writer.
- L66-80 _public method_ `public static void Write<T>(this BinaryWriter writer, T[] items, Action<T> writeElement)` — Writes an array to a binary writer.
- L87-90 _public method_ `public static void Write(this BinaryWriter writer, List<string> items)` — Writes a list of strings to a binary writer.
- L98-101 _public method_ `public static void Write<T>(this BinaryWriter writer, List<T> items) where T : class, IBinarySerializable` — Writes a list to a binary writer.
- L110-124 _public method_ `public static void Write<T>(this BinaryWriter writer, List<T> items, Action<T> writeElement)` — Writes a list to a binary writer.
- L136-151 _public method_ `public static void Write<TKey, TValue>(this BinaryWriter writer, Dictionary<TKey, TValue> items, Action<TKey> writeKey, Action<TValue> writeValue) where TKey : notnull` — Write a dictionary to a binary writer
- L161-172 _public method_ `public static void WriteNullable<T>(this BinaryWriter writer, T item, Action writeItem) where T : class` — Read a nullable object from a binary reader
- L180-233 _public method_ `public static void Write(this BinaryWriter writer, Type fieldType, object value)` — Writes a value of a specific type to a binary writer

### `Source/Programs/Shared/EpicGames.Core/Boxed.cs` (EpicGames.Core)


#### class `EpicGames.Core.Boxed`  
`public class Boxed<T>`  
_public; L9-48_
- desc: Explicitly boxes a value type, allowing it to be passed by reference to (and modified in) an async method.
- L14 _public property_ `public T Value { get; set; }` — The struct value
- L20-23 _public ctor_ `public Boxed(T value)` — Default constructor
- L26-29 _public method_ `public override string? ToString()` — (inheritdoc)
- L35-38 _public operator_ `public static implicit operator T(Boxed<T> boxed)` — Implicit conversion of a boxed value to value type
- L44-47 _public operator_ `public static implicit operator Boxed<T>(T value)` — Implicit conversion of a boxed value to value type

### `Source/Programs/Shared/EpicGames.Core/BuzHash.cs` (EpicGames.Core)


#### class `EpicGames.Core.BuzHash`  
`public class BuzHash`  
_public; L12-355_
- desc: Rolling hash by cyclic polynomial
- L14 _private* field_ `static readonly uint[] s_table = [ 0x458be752, 0xc10748cc, 0xfbbcdbb8, 0x6ded5b68, 0xb10a82b5, 0x20d75648, 0xdfc5665f, 0xa8428801, 0x7ebf5191, 0x841135c7, 0x65cc53b3, 0x280a597c, 0x16f60255, 0xc78cbc3e, 0x294415f5, 0xb938d494, 0xec85 ...`
- L42 _private* field_ `uint _state`
- L47-50 _public ctor_ `public BuzHash() : this(0)` — Constructor
- L56-59 _public ctor_ `public BuzHash(uint state)` — Constructor
- L64-67 _public method_ `public void Reset()` — Resets the state of the
- L73-76 _public method_ `public void Add(byte value)` — Add a byte to the window and update the hash
- L82-85 _public method_ `public void Add(ReadOnlySpan<byte> span)` — Add a byte to the window and update the hash
- L93-96 _public method_ `public static uint Add(uint state, byte value)` — Static method for updating a hash given a particular byte value
- L104-115 _public method_ `public static unsafe uint Add(uint state, ReadOnlySpan<byte> data)` — Static method for appending a range of data to a hash value
- L122-125 _public method_ `public void Sub(byte value, int count)` — Removes a byte from the start of the hash window
- L133-136 _public method_ `public static uint Sub(uint state, byte value, int count)` — Removes a byte from the start of the hash window
- L145-156 _public method_ `public static unsafe uint Sub(uint state, ReadOnlySpan<byte> data, int count)` — Static method for appending a range of data to a hash value
- L162-168 _public method_ `public void Update(ReadOnlySpan<byte> data)` — Update the hash with the given data
- L180-204 _public method_ `public static unsafe int Update(ReadOnlySpan<byte> prev, ReadOnlySpan<byte> next, int windowSize, uint threshold, ref uint state)` — Consume data from a source until the hash is below a certain threshold
- L214-233 _public method_ `public static List<(int, uint)> FindSplitPoints(ReadOnlySpan<byte> span, int minSize, int maxSize, int targetSize)` — Finds split points from a buffer.
- L243-274 _public method_ `public static unsafe List<(int, uint)> FindCandidateSplitPoints(ReadOnlySpan<byte> span, int windowSize, uint threshold)` — Finds candidate chunk points from a buffer, ignoring minimum/maximum chunk sizes. Can be used to precalculate chunking points when hashing in parallel.
- L280-283 _public method_ `public uint Get()` — Gets the current hash value
- L285-289 _private* method_ `static uint Rol32(uint v, int n)`
- L296-299 _public method_ `public static uint GetThreshold(int targetSize)` — Gets the threshold below which hash values should statistically occur on average after the given number of entries
- L310-354 _public method_ `public static int FindChunkLength(ReadOnlySpan<byte> inputData, int minSize, int maxSize, int targetSize, out uint rollingHash)` — Gets the length of a chunk up to the next content-defined boundary

### `Source/Programs/Shared/EpicGames.Core/ByteArrayBuilder.cs` (EpicGames.Core)


#### class `EpicGames.Core.ByteArrayBuilder`  
`public class ByteArrayBuilder : IMemoryWriter`  
_public; L12-183_
- inherits: `IMemoryWriter`
- desc: Class for building byte sequences, similar to StringBuilder. Allocates memory in chunks to avoid copying data.
- L30 _private* field_ `readonly List<Chunk> _chunks = []`
- L31 _private* field_ `readonly int _chunkSize`
- L32 _private* field_ `Chunk _currentChunk`
- L37 _public property_ `public int Length { get; set; }` — Length of the current sequence
- L43-46 _public ctor_ `public ByteArrayBuilder(int chunkSize) : this(chunkSize, chunkSize)` — Constructor
- L53-58 _public ctor_ `public ByteArrayBuilder(int initialSize = 4096, int chunkSize = 4096)` — Constructor
- L63-69 _public method_ `public void Clear()` — Clear the current builder
- L72 _public method_ `public Span<byte> GetSpan(int sizeHint)` — (inheritdoc)
- L75-84 _public method_ `public Memory<byte> GetMemory(int sizeHint)` — (inheritdoc)
- L87-96 _public method_ `public void Advance(int length)` — (inheritdoc)
- L102-108 _public method_ `public void AppendTo(ReadOnlySequenceBuilder<byte> builder)` — Appends data in this builder to the given sequence
- L114-124 _public method_ `public ReadOnlyMemory<byte> AsMemory()` — Gets a contiguous, non-owned buffer containing the current data. Will merge together current chunks if necessary.
- L130-135 _public method_ `public ReadOnlySequence<byte> AsSequence()` — Gets a sequence representing the bytes that have been written so far
- L142-146 _public method_ `public ReadOnlySequence<byte> AsSequence(int offset)` — Gets a sequence representing the bytes that have been written so far, starting at the given offset
- L154-158 _public method_ `public ReadOnlySequence<byte> AsSequence(int offset, int length)` — Gets a sequence representing the bytes that have been written so far, starting at the given offset and
- L164-171 _public method_ `public void CopyTo(Span<byte> span)` — Copies the data to the given output span
- L177-182 _public method_ `public byte[] ToByteArray()` — Create a byte array from the sequence

#### class `EpicGames.Core.ByteArrayBuilder.Chunk`  
`class Chunk`  
_private*; L14-28_
- L16 _public field_ `public readonly int RunningIndex`
- L17 _public field_ `public readonly byte[] Data`
- L18 _public property_ `public int Length { get; set; }`
- L20-24 _public ctor_ `public Chunk(int runningIndex, int size)`
- L26 _public property_ `public ReadOnlySpan<byte> WrittenSpan => ...`
- L27 _public property_ `public ReadOnlyMemory<byte> WrittenMemory => ...`

### `Source/Programs/Shared/EpicGames.Core/ByteString.cs` (EpicGames.Core)


#### struct `EpicGames.Core.ByteString`  
`public readonly struct ByteString : IEquatable<ByteString>, IComparable<ByteString>`  
_public; L19-141_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(ByteStringJsonConverter))] [TypeConverter(typeof(ByteStringTypeConverter))]`
- inherits: `IEquatable<ByteString>, IComparable<ByteString>`
- desc: Wraps a sequence of bytes that can be manipulated with value-like semantics
- L24 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Underlying data for this string
- L29 _public property_ `public ReadOnlySpan<byte> Span => ...` — Accessor for the data underlying this string
- L35 _public ctor_ `public ByteString(ReadOnlyMemory<byte> data)` — Constructor
- L42 _public method_ `public static ByteString Parse(ReadOnlySpan<byte> text)` — Parses a byte string from a hexadecimal string
- L49 _public method_ `public static ByteString Parse(Utf8String text)` — Parses a byte string from a hexadecimal string
- L56 _public method_ `public static ByteString Parse(string text)` — Parses a byte string from a hexadecimal string
- L64-77 _public method_ `public static bool TryParse(ReadOnlySpan<byte> text, out ByteString byteString)` — Attempts to parse a hexadecimal string as a byte string
- L85 _public method_ `public static bool TryParse(Utf8String text, out ByteString byteString)` — Attempts to parse a hexadecimal string as a byte string
- L93-106 _public method_ `public static bool TryParse(string text, out ByteString byteString)` — Attempts to parse a hexadecimal string as a byte string
- L109 _public method_ `public int CompareTo(ByteString other)` — (inheritdoc)
- L112 _public method_ `public override bool Equals([NotNullWhen(true)] object? obj)` — (inheritdoc)
- L115 _public method_ `public bool Equals(ByteString other)` — (inheritdoc)
- L118-123 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L126 _public method_ `public override string ToString()` — (inheritdoc)
- L131 _public method_ `public Utf8String ToUtf8String()` — Creates a Utf8 string representing the bytes in this string
- L134 _public operator_ `public static bool operator ==(ByteString left, ByteString right)`
- L135 _public operator_ `public static bool operator !=(ByteString left, ByteString right)`
- L136 _public operator_ `public static bool operator <(ByteString left, ByteString right)`
- L137 _public operator_ `public static bool operator <=(ByteString left, ByteString right)`
- L138 _public operator_ `public static bool operator >(ByteString left, ByteString right)`
- L139 _public operator_ `public static bool operator >=(ByteString left, ByteString right)`

#### class `EpicGames.Core.ByteStringJsonConverter`  
`sealed class ByteStringJsonConverter : JsonConverter<ByteString>`  
_internal*; L146-153_
- inherits: `JsonConverter<ByteString>`
- desc: Type converter for ClusterId to and from JSON
- L149 _public method_ `public override ByteString Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L152 _public method_ `public override void Write(Utf8JsonWriter writer, ByteString value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Core.ByteStringTypeConverter`  
`sealed class ByteStringTypeConverter : TypeConverter`  
_internal*; L158-192_
- inherits: `TypeConverter`
- desc: Type converter from strings to ClusterId objects
- L161-169 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type? sourceType)` — (inheritdoc)
- L172-191 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object? value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/CancellationTask.cs` (EpicGames.Core)


#### class `EpicGames.Core.CancellationTask`  
`public sealed class CancellationTask : IDisposable`  
_public; L12-46_
- inherits: `IDisposable`
- desc: Wrapper class to create a waitable task out of a cancellation token
- L17 _private* field_ `readonly TaskCompletionSource<bool> _completionSource` — Completion source for the task
- L22 _private* field_ `readonly CancellationTokenRegistration _registration` — Registration handle with the cancellation token
- L28-32 _public ctor_ `public CancellationTask(CancellationToken token)` — Constructor
- L37 _public property_ `public Task Task => ...` — The task that can be waited on
- L42-45 _public method_ `public void Dispose()` — Dispose of any allocated resources

### `Source/Programs/Shared/EpicGames.Core/CertificateUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.CertificateUtils`  
`public static class CertificateUtils`  
_public; L14-52_
- desc: Utility methods for certificates
- L22-51 _public method_ `public static byte[] CreateSelfSignedCert(string dnsName, string friendlyName)` — Create a self signed cert for the agent

### `Source/Programs/Shared/EpicGames.Core/ChannelWithRefCount.cs` (EpicGames.Core)


#### class `EpicGames.Core.ChannelWithRefCount`  
`public class ChannelWithRefCount<T> : Channel<T>`  
_public; L12-50_
- inherits: `Channel<T>`
- desc: Implements a Channel{T} which signals completion according to a reference count.
- L14 _private* field_ `int _count = 1`
- L19 _public event_ `public event Action? OnComplete` — Called when the channel is completed
- L24-28 _internal ctor_ `internal ChannelWithRefCount(Channel<T> inner)` — Constructor
- L33-37 _public method_ `public ChannelWithRefCount<T> AddRef()` — Adds a new reference to the channel
- L42-49 _public method_ `public void Release()` — Releases a reference to the channel

#### class `EpicGames.Core.ChannelExtensions`  
`public static class ChannelExtensions`  
_public; L55-62_
- desc: Extension methods for Channel{T}
- L60 _public method_ `public static ChannelWithRefCount<T> WithRefCount<T>(this Channel<T> channel)` — Creates a channel whose completion state is controlled by a reference count

### `Source/Programs/Shared/EpicGames.Core/Clock.cs` (EpicGames.Core)


#### interface `EpicGames.Core.ITicker`  
`public interface ITicker : IAsyncDisposable`  
_public; L14-25_
- inherits: `IAsyncDisposable`
- desc: Base interface for a scheduled event
- L19 _public* method_ `Task StartAsync()` — Start the ticker
- L24 _public* method_ `Task StopAsync()` — Stop the ticker

#### interface `EpicGames.Core.IClock`  
`public interface IClock`  
_public; L30-62_
- desc: Interface representing time and scheduling events which is pluggable during testing. In normal use, the Clock implementation below is used.
- L35 _public* property_ `DateTime UtcNow { get; }` — Return time expressed as the Coordinated Universal Time (UTC)
- L40 _public* property_ `TimeZoneInfo TimeZone { get; }` — Time zone for schedules etc...
- L50 _public* method_ `ITicker AddTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask<TimeSpan?>> tickAsync, ILogger logger)` — Create an event that will trigger after the given time
- L61 _public* method_ `ITicker AddSharedTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — Create a ticker shared between all server processes. Callback can be run inside any available process but will still only be called once per tick.

#### class `EpicGames.Core.NullTicker`  
`public sealed class NullTicker : ITicker`  
_public; L67-77_
- inherits: `ITicker`
- desc: Placeholder interface for ITicker
- L70 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L73 _public method_ `public Task StartAsync()` — (inheritdoc)
- L76 _public method_ `public Task StopAsync()` — (inheritdoc)

#### class `EpicGames.Core.DefaultClock`  
`public class DefaultClock : IClock`  
_public; L82-101_
- inherits: `IClock`
- desc: A default implementation of IClock for normal production use
- L85 _public property_ `public DateTime UtcNow => ...` — (inheritdoc)
- L88 _public property_ `public TimeZoneInfo TimeZone => ...` — (inheritdoc)
- L91-94 _public method_ `public ITicker AddTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask<TimeSpan?>> tickAsync, ILogger logger)` — (inheritdoc)
- L97-100 _public method_ `public ITicker AddSharedTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — (inheritdoc)

#### class `EpicGames.Core.StubClock`  
`public class StubClock : IClock`  
_public; L106-140_
- inherits: `IClock`
- desc: A stub implementation of IClock. Intended for testing to override time.
- L108 _private field_ `private DateTime _utcNow = DateTime.UtcNow`
- L111-115 _public property_ `public DateTime UtcNow { get; set; }` — (inheritdoc)
- L118 _public property_ `public TimeZoneInfo TimeZone { get; set; }` — (inheritdoc)
- L121-124 _public method_ `public ITicker AddTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask<TimeSpan?>> tickAsync, ILogger logger)` — (inheritdoc)
- L127-130 _public method_ `public ITicker AddSharedTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — (inheritdoc)
- L136-139 _public method_ `public void Advance(TimeSpan delta)` — Advance the time

#### class `EpicGames.Core.ClockExtensions`  
`public static class ClockExtensions`  
_public; L145-200_
- desc: Extension methods for IClock
- L156-166 _public method_ `public static ITicker AddTicker(this IClock clock, string name, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — Create an event that will trigger after the given time
- L176 _public method_ `public static ITicker AddTicker<T>(this IClock clock, TimeSpan interval, Func<CancellationToken, ValueTask<TimeSpan?>> tickAsync, ILogger logger)` — Create an event that will trigger after the given time
- L187 _public method_ `public static ITicker AddTicker<T>(this IClock clock, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — Create an event that will trigger after the given time
- L198 _public method_ `public static ITicker AddSharedTicker<T>(this IClock clock, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — Create a ticker shared between all server pods

### `Source/Programs/Shared/EpicGames.Core/CommandHost.cs` (EpicGames.Core)


#### interface `EpicGames.Core.ICommand`  
`public interface ICommand`  
_public; L16-38_
- desc: Interface for commands
- L23 _public* method_ `void Configure(CommandLineArguments arguments, ILogger logger)` — Configure this object with the given command line arguments
- L30 _public* method_ `List<KeyValuePair<string, string>> GetParameters(CommandLineArguments arguments)` — Gets all command line parameters to show in help for this command
- L37 _public* method_ `Task<int> ExecuteAsync(ILogger logger)` — Execute this command

#### interface `EpicGames.Core.ICommandFactory`  
`public interface ICommandFactory`  
_public; L43-69_
- desc: Interface describing a command that can be exectued
- L48 _public property_ `public IReadOnlyList<string> Names { get; }` — Names for this command
- L53 _public property_ `public string Description { get; }` — Short description for the mode. Will be displayed in the help text.
- L58 _public property_ `public bool Advertise { get; }` — Whether to include this command in help text
- L63 _public property_ `public bool AcceptsPositionalArguments { get; }` — Whether the command accepts positional arguments
- L68 _public method_ `public ICommand CreateInstance(IServiceProvider serviceProvider)` — Create a command instance

#### class `EpicGames.Core.CommandAttribute`  
`public sealed class CommandAttribute : Attribute`  
_public; L76-120_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute used to specify names of program modes, and help text
- L81 _public property_ `public string[] Names { get; }` — Names for this command
- L86 _public property_ `public string Description { get; }` — Short description for the mode. Will be displayed in the help text.
- L91 _public property_ `public bool Advertise { get; set; }` — Whether to include the command in help listings
- L96 _public property_ `public bool AcceptsPositionalArguments { get; set; }` — Whether the command takes positional arguments
- L103-107 _public ctor_ `public CommandAttribute(string name, string description)` — Constructor
- L115-119 _public ctor_ `public CommandAttribute(string category, string name, string description)` — Constructor

#### class `EpicGames.Core.Command`  
`public abstract class Command : ICommand`  
_public; L126-142_
- inherits: `ICommand`
- desc: Base class for all commands that can be executed by HordeAgent
- L129-132 _public method_ `public virtual void Configure(CommandLineArguments arguments, ILogger logger)` — (inheritdoc)
- L135-138 _public method_ `public virtual List<KeyValuePair<string, string>> GetParameters(CommandLineArguments arguments)` — (inheritdoc)
- L141 _public method_ `public abstract Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

#### class `EpicGames.Core.CommandFactory`  
`class CommandFactory : ICommandFactory`  
_internal*; L147-167_
- inherits: `ICommandFactory`
- desc: Default implementation of a command factory
- L149 _public property_ `public IReadOnlyList<string> Names { get; }`
- L150 _public property_ `public string Description { get; }`
- L151 _public property_ `public bool Advertise { get; }`
- L152 _public property_ `public bool AcceptsPositionalArguments { get; }`
- L154 _public property_ `public Type Type { get; }`
- L156-163 _public ctor_ `public CommandFactory(string[] names, string description, bool advertise, bool acceptsPositionalArguments, Type type)`
- L165 _public method_ `public ICommand CreateInstance(IServiceProvider serviceProvider)`
- L166 _public method_ `public override string ToString()`

#### class `EpicGames.Core.CommandHost`  
`public static class CommandHost`  
_public; L172-336_
- desc: Entry point for dispatching commands
- L179-194 _public method_ `public static void AddCommandsFromAssembly(this IServiceCollection services, Assembly assembly)` — Adds services for executing the
- L204-318 _public method_ `public static async Task<int> RunAsync(CommandLineArguments args, IServiceProvider serviceProvider, Type? defaultCommandType, string? toolDescription = null)` — Entry point for executing registered command types in a particular assembly
- L324-335 _private* method_ `static void PrintCommands(IEnumerable<ICommandFactory> attributes)` — Print a formatted list of all the available commands

### `Source/Programs/Shared/EpicGames.Core/CommandLineArguments.cs` (EpicGames.Core)


#### class `EpicGames.Core.CommandLineArgumentListView`  
`class CommandLineArgumentListView`  
_internal*; L24-40_
- desc: Helper class to visualize an argument list
- L30 _public property_ `public string[] Arguments { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.RootHidden)]` — The list of arguments
- L36-39 _public ctor_ `public CommandLineArgumentListView(CommandLineArguments argumentList)` — Constructor

#### class `EpicGames.Core.CommandLineArgumentException`  
`public class CommandLineArgumentException : Exception`  
_public; L45-74_
- inherits: `Exception`
- desc: Exception thrown for invalid command line arguments
- L51-54 _public ctor_ `public CommandLineArgumentException(string message) : base(message)` — Constructor
- L61-64 _public ctor_ `public CommandLineArgumentException(string message, Exception innerException) : base(message, innerException)` — Constructor
- L70-73 _public method_ `public override string ToString()` — Converts this exception to a string

#### class `EpicGames.Core.CommandLineArguments`  
`public class CommandLineArguments : IReadOnlyList<string>, IReadOnlyCollection<string>, IEnumerable<string>, IEnumerable`  
_public; L85-1451_
- attrs: `[DebuggerDisplay("Count = {Count}")] [DebuggerTypeProxy(typeof(CommandLineArgumentListView))] [JsonConverter(typeof(CommandLineArgumentsJsonConverter))]`
- inherits: `IReadOnlyList<string>, IReadOnlyCollection<string>, IEnumerable<string>, IEnumerable`
- desc: Stores a list of command line arguments, allowing efficient ad-hoc queries of particular options (eg. "-Flag") and retreival of typed values (eg. "-Foo=Bar"), as well as attribute-driven application to fields with the [CommandLine] attribute applied. Also tracks which arguments have been retrieved, allowing the display of diagnostic messages for invalid arguments.
- L111 _private* field_ `readonly string[] _arguments` — The raw array of arguments
- L116 _private* field_ `readonly BitArray _flagArguments` — Bitmask indicating which arguments are flags rather than values
- L121 _private* field_ `readonly BitArray _usedArguments` — Bitmask indicating which arguments have been used, via calls to GetOption(), GetValues() etc...
- L126 _private* field_ `readonly Dictionary<string, int> _argumentToFirstIndex` — Dictionary of argument names (or prefixes, in the case of "-Foo=" style arguments) to their index into the arguments array.
- L126 _private* field_ `readonly Dictionary< _argumentToFirstIndex` — Dictionary of argument names (or prefixes, in the case of "-Foo=" style arguments) to their index into the arguments array.
- L131 _private* field_ `readonly int[] _nextArgumentIndex` — For each argument which is seen more than once, keeps a list of indices for the second and subsequent arguments.
- L136 _private* field_ `readonly List<int> _positionalArgumentIndices = []` — List of positional arguments
- L141 _private* field_ `static readonly char[] s_valueSeparators = ['=', ':']` — Array of characters that separate argument names from values
- L147-217 _public ctor_ `public CommandLineArguments(string[] arguments)` — Constructor
- L222 _public property_ `public int Count => ...` — The number of arguments in this list
- L229 _public indexer_ `public string this[int index]` — Access an argument by index
- L236-239 _public method_ `public bool HasBeenUsed(int index)` — Determines if an argument has been used
- L245-248 _public method_ `public void MarkAsUsed(int index)` — Marks an argument as having been used
- L254-257 _public method_ `public void MarkAsUnused(int index)` — Marks an argument as not having been used
- L264-273 _public method_ `public bool HasOption(string option)` — Checks if the given option (eg. "-Foo") was specified on the command line.
- L280-284 _public method_ `public bool HasValue(string prefix)` — Checks for an argument prefixed with the given string is present.
- L290-293 _public method_ `public int GetPositionalArgumentCount()` — Gets the positional argument at the given index
- L300-303 _public method_ `public int GetPositionalArgumentIndex(int num)` — Gets the index of the numbered positional argument
- L310-325 _public method_ `public bool TryGetPositionalArgument([NotNullWhen(true)] out string? argument)` — Attempts to read the next unused positional argument
- L331-341 _public method_ `public string[] GetPositionalArguments()` — Returns all the positional arguments, and marks them as used
- L347-350 _public method_ `public void RemovePositionalArguments(int count)` — Consume positional arguments from command line
- L357-365 _public method_ `public string GetString(string prefix)` — Gets the value specified by an argument with the given prefix. Throws an exception if the argument was not specified.
- L372-380 _public method_ `public int GetInteger(string prefix)` — Gets the value specified by an argument with the given prefix. Throws an exception if the argument was not specified.
- L387-395 _public method_ `public FileReference GetFileReference(string prefix)` — Gets the value specified by an argument with the given prefix. Throws an exception if the argument was not specified.
- L402-410 _public method_ `public DirectoryReference GetDirectoryReference(string prefix)` — Gets the value specified by an argument with the given prefix. Throws an exception if the argument was not specified.
- L417-425 _public method_ `public T GetEnum<T>(string prefix) where T : struct` — Gets the value specified by an argument with the given prefix. Throws an exception if the argument was not specified.
- L434-442 _public method_ `public string? GetStringOrDefault(string prefix, string? defaultValue)` — attrs: `[return: NotNullIfNotNull(nameof(defaultValue))]` — Gets the value specified by an argument with the given prefix, or a default value.
- L450-458 _public method_ `public int GetIntegerOrDefault(string prefix, int defaultValue)` — Gets the value specified by an argument with the given prefix, or a default value.
- L467-475 _public method_ `public FileReference? GetFileReferenceOrDefault(string prefix, FileReference? defaultValue)` — attrs: `[return: NotNullIfNotNull(nameof(defaultValue))]` — Gets the value specified by an argument with the given prefix, or a default value.
- L484-492 _public method_ `public DirectoryReference? GetDirectoryReferenceOrDefault(string prefix, DirectoryReference? defaultValue)` — attrs: `[return: NotNullIfNotNull(nameof(defaultValue))]` — Gets the value specified by an argument with the given prefix, or a default value.
- L500-508 _public method_ `public T GetEnumOrDefault<T>(string prefix, T defaultValue) where T : struct` — Gets the value specified by an argument with the given prefix, or a default value.
- L516-535 _public method_ `public bool TryGetValue(string prefix, [NotNullWhen(true)] out string? value)` — Tries to gets the value specified by an argument with the given prefix.
- L543-563 _public method_ `public bool TryGetValue(string prefix, out int value)` — Tries to gets the value specified by an argument with the given prefix.
- L571-591 _public method_ `public bool TryGetValue(string prefix, [NotNullWhen(true)] out FileReference? value)` — Tries to gets the value specified by an argument with the given prefix.
- L599-619 _public method_ `public bool TryGetValue(string prefix, [NotNullWhen(true)] out DirectoryReference? value)` — Tries to gets the value specified by an argument with the given prefix.
- L627-647 _public method_ `public bool TryGetValue<T>(string prefix, out T value) where T : struct` — Tries to gets the value specified by an argument with the given prefix.
- L654-667 _public method_ `public IEnumerable<string> GetValues(string prefix)` — Returns all arguments with the given prefix.
- L675-684 _public method_ `public IEnumerable<string> GetValues(string prefix, char separator)` — Returns all arguments with the given prefix, allowing multiple arguments to be specified in a single argument with a separator character.
- L692-721 _private method_ `private static string GetArgumentPrefix(ArgumentTarget target, CommandLineAttribute attribute)` — Gets the prefix for a particular argument
- L727-730 _public method_ `public void ApplyTo(object targetObject)` — Applies these arguments to fields with the [CommandLine] attribute in the given object.
- L737-848 _public method_ `public void ApplyTo(object targetObject, ILogger logger)` — Applies these arguments to fields with the [CommandLine] attribute in the given object.
- L854-859 _public method_ `public T ApplyTo<T>(ILogger logger) where T : new()` — Applies these arguments to fields with the [CommandLine] attribute in the given object.
- L861 _private field_ `private static readonly ConcurrentDictionary<Type, Lazy<List<ArgumentTarget>>> s_cachedArgumentTargetsForType = ...`
- L861 _private field_ `private static readonly ConcurrentDictionary< s_cachedArgumentTargetsForType = []`
- L862-903 _private* method_ `static List<ArgumentTarget> GetArgumentTargetsForType(Type? targetType)`
- L910-952 _public method_ `public static List<KeyValuePair<string, string>> GetParameters(Type type)` — Gets help text for the arguments of a given type
- L959-993 _public method_ `public static string Quote(string argument)` — Quotes a command line argument, if necessary
- L1000-1012 _public method_ `public static string Join(IEnumerable<string> arguments)` — Joins the given arguments into a command line
- L1019-1057 _public method_ `public static string[] Split(string commandLine)` — Splits a command line into individual arguments
- L1064-1075 _public method_ `public CommandLineArguments Append(IEnumerable<string> appendArguments)` — Appends the given arguments to the current argument list
- L1083-1115 _public method_ `public CommandLineArguments Remove(string prefix, out List<string> values)` — Retrieves all arguments with the given prefix, and returns the remaining a list of strings
- L1120-1123 _public method_ `public void CheckAllArgumentsUsed()` — Checks that there are no unused arguments (and warns if there are)
- L1128-1152 _public method_ `public void CheckAllArgumentsUsed(ILogger logger)` — Checks that there are no unused arguments (and warns if there are)
- L1158-1161 _public method_ `public bool AreAnyArgumentsUsed()` — Checks to see if any arguments are used
- L1167-1176 _public method_ `public IEnumerable<string> GetUnusedArguments()` — Checks to see if any arguments are used
- L1182-1185 _public method_ `public int CountValueArguments()` — Count the number of value (non-flag) arguments on the command line
- L1191-1205 _private method_ `private static void CheckValidPrefix(string prefix)` — Checks that a given string is a valid argument prefix
- L1217-1265 _private method_ `private static bool ApplyArgument(object targetObject, ArgumentTarget target, string argumentText, string valueText, string? previousArgumentText, ILogger logger)` — Parses and assigns a value to a field
- L1274-1377 _private method_ `private static bool TryParseValue(Type fieldType, string text, [NotNullWhen(true)] out object? value)` — Attempts to parse the given string to a value
- L1383-1386 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — Obtains an enumerator for the argument list
- L1392-1395 _public method_ `public IEnumerator<string> GetEnumerator()` — Obtains an enumerator for the argument list
- L1401-1404 _public method_ `public string[] GetRawArray()` — Gets the raw argument array
- L1412-1436 _public method_ `public static void Append(StringBuilder commandLine, string argument)` — Takes a command line argument and adds quotes if necessary
- L1442-1450 _public method_ `public override string ToString()` — Converts this string to

#### class `EpicGames.Core.CommandLineArguments.ArgumentTarget`  
`class ArgumentTarget`  
_private*; L90-106_
- desc: Information about a property or field that can receive an argument
- L92 _public property_ `public MemberInfo Member { get; }`
- L93 _public property_ `public Type ValueType { get; }`
- L94 _public property_ `public Action<object?, object?> SetValue { get; }`
- L95 _public property_ `public Func<object?, object?> GetValue { get; }`
- L96 _public property_ `public CommandLineAttribute[] Attributes { get; }`
- L98-105 _public ctor_ `public ArgumentTarget(MemberInfo member, Type valueType, Action<object?, object?> setValue, Func<object?, object?> getValue, CommandLineAttribute[] attributes)`

#### class `EpicGames.Core.CommandLineArgumentsJsonConverter`  
`public class CommandLineArgumentsJsonConverter : JsonConverter<CommandLineArguments>`  
_public; L1456-1495_
- inherits: `JsonConverter<CommandLineArguments>`
- desc: Serializes command-line arguments to and from an array of strings.
- L1459-1483 _public method_ `public override CommandLineArguments? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L1486-1494 _public method_ `public override void Write(Utf8JsonWriter writer, CommandLineArguments value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/CommandLineAttribute.cs` (EpicGames.Core)


#### class `EpicGames.Core.CommandLineAttribute`  
`public sealed class CommandLineAttribute : Attribute`  
_public; L11-63_
- attrs: `[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Attribute to indicate the name of a command line argument
- L17 _public property_ `public string? Prefix { get; set; }` — Prefix for the option, with a leading '-' and trailing '=' character if a value is expected.
- L23 _public property_ `public string? Value { get; set; }` — Specifies a fixed value for this argument. Specifying an alternate value is not permitted.
- L28 _public property_ `public bool Required { get; set; }` — Whether this argument is required
- L33 _public property_ `public bool MarkUsed { get; set; }` — Whether this argument is required
- L38 _public property_ `public bool Positional { get; set; }` — Accepts positional arguments (ie. without a preceding hyphen)
- L43 _public property_ `public char ListSeparator { get; set; }` — For collection types, specifies the separator character between multiple arguments
- L48 _public property_ `public string? Description { get; set; }` — Description of the operation.
- L54-62 _public ctor_ `public CommandLineAttribute(string? prefix = null)` — Constructor

### `Source/Programs/Shared/EpicGames.Core/CommandLineExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.CommandLineExtensions`  
`public static class CommandLineExtensions`  
_public; L11-135_
- desc: Extensions to StringBuilder for building command lines
- L18-21 _private* method_ `static bool NeedsEscaping(string argument)` — Determines if the given argument needs to be escaped
- L28-47 _public method_ `public static void AppendArgument(this StringBuilder builder, string argument)` — Appends command line argument with a prefixed space. The argument may contain spaces or quotes.
- L55-71 _public method_ `public static void AppendArgument(this StringBuilder builder, string name, string value)` — Appends command line argument with a prefixed space. The argument may contain spaces or quotes.
- L79-134 _public method_ `public static void AppendCommandLineArgumentWithoutSpace(this StringBuilder builder, string argument)` — Appends an escaped command line argument. The argument may contain spaces or quotes, and is escaped according to the rules in https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-commandlinetoargvw.

### `Source/Programs/Shared/EpicGames.Core/CondensedGraphBuilder.cs` (EpicGames.Core)


#### class `EpicGames.Core.CondensedGraphBuilder`  
`public class CondensedGraphBuilder<T> where T : notnull`  
_public; L23-358_
- constraints: `where T : notnull`
- desc: Builds a condensed graph for a directed graph using Kosaraju-Sharir's algorithm. Each strongly connected component (SCC) in the input is collapsed into a single node, producing a directed acyclic graph (DAG). Vertices that are not part of any cycle form their own single-element SCCs. Build() returns false if the input graph is already a DAG (no cycles found), or true if cycles were detected and the condensed differs from the input. In both cases GetSCCs() and GetNodeToSCCIndex() are fully populated. GetCondensedEdges() is only populated when Build() returns true (matching the C++ TryConstructcondensedGraph contract). The output SCCs are ordered so that every edge in the condensed graph points from a lower SCC index to a higher one (root-to-leaf topological order).
- L28 _private field_ `private Func<T, string>? _nodeToString = ...` — Functor returning a node's name. Used for diagnostic logging.
- L28 _private field_ `private Func< _nodeToString = null` — Functor returning a node's name. Used for diagnostic logging.
- L33 _private field_ `private readonly List<GraphNode> _nodes = []` — List of all graph nodes in insertion order.
- L38 _private field_ `private readonly Dictionary<T, GraphNode> _nodeMap = ...` — Maps each user-provided node to its internal GraphNode.
- L38 _private field_ `private readonly Dictionary< _nodeMap = []` — Maps each user-provided node to its internal GraphNode.
- L45 _private field_ `private readonly List<T[]> _resultSCCs = []` — Output: list of strongly connected components. Each SCC is an array of original nodes. Ordered root-to-leaf: condensed edges always point from lower to higher SCC index. Always populated after Build().
- L51 _private field_ `private readonly Dictionary<T, int> _resultNodeToSCCIndex = ...` — Output: maps each original node to the index of its SCC in ResultSCCs. Always populated after Build().
- L51 _private field_ `private readonly Dictionary< _resultNodeToSCCIndex = []` — Output: maps each original node to the index of its SCC in ResultSCCs. Always populated after Build().
- L57 _private field_ `private readonly List<int[]> _resultCondensedEdges = []` — Output: adjacency list of the condensed graph. ResultCondensedEdges[i] holds the SCC indices that SCC i has outgoing edges to. Only populated when Build() returns true.
- L62 _public property_ `public Func<T, string>? NodeToString { get; set; }` — Function to go from a node to the string output. Can be used for logging.
- L70-73 _public ctor_ `public CondensedGraphBuilder(List<Tuple<T, T>> edges)` — Initializes the builder and constructs the internal graph from the provided edges. All nodes referenced by edges (both source and destination) are included. Self-edges are discarded.
- L82-272 _public method_ `public bool Build()` — Runs Kosaraju-Sharir's algorithm to compute the condensed graph.
- L279 _public method_ `public List<T[]> GetSCCs()` — Returns the list of strongly connected components (valid after calling Build()). Each SCC is an array of original nodes. Ordered root-to-leaf in the condensed graph. Always populated, even when Build() returns false.
- L285 _public method_ `public IReadOnlyDictionary<T, int> GetNodeToSCCIndex()` — Returns a mapping from each original node to the index of its SCC in GetSCCs() (valid after calling Build()). Always populated, even when Build() returns false.
- L292 _public method_ `public List<int[]> GetCondensedEdges()` — Returns the adjacency list of the condensed graph (valid after calling Build()). GetCondensedEdges()[i] lists the SCC indices that SCC i has outgoing edges to. Only populated when Build() returns true; empty when Build() returns false.
- L298-329 _private method_ `private void CreateGraph(List<Tuple<T, T>> edges)` — Constructs the internal graph from the provided edge list. Nodes are added in the order they first appear. Self-edges are discarded.

#### enum `EpicGames.Core.CondensedGraphBuilder.VisitStatus`  
`private enum VisitStatus : byte`  
_private; L331-336_
- inherits: `byte`
- L333 _public* enumerator_ `NotVisited = 0`
- L334 _public* enumerator_ `InProgress = 1`
- L335 _public* enumerator_ `Visited = 2`

#### class `EpicGames.Core.CondensedGraphBuilder.GraphNode`  
`private class GraphNode`  
_private; L338-357_
- L341 _public field_ `public T _data` — User-provided node object.
- L344 _public field_ `public int _index` — Position in the Nodes list; used as an array index during Build().
- L347 _public field_ `public List<GraphNode> _links = []` — Outgoing edges in the original graph.
- L350 _public field_ `public List<GraphNode> _transposeLinks = []` — Incoming edges in the original graph (outgoing edges in the transpose graph).
- L352-356 _public ctor_ `public GraphNode(T data, int index)`

### `Source/Programs/Shared/EpicGames.Core/ConsoleUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.ConsoleUtils`  
`public static class ConsoleUtils`  
_public; L10-83_
- desc: Utility methods for writing to the console
- L15-37 _public property_ `public static int WindowWidth { get; }` — Gets the width of the window for formatting purposes
- L43-46 _public method_ `public static void WriteLineWithWordWrap(string text)` — Writes the given text to the console as a sequence of word-wrapped lines
- L54-60 _public method_ `public static void WriteLineWithWordWrap(string text, int initialIndent, int hangingIndent)` — Writes the given text to the console as a sequence of word-wrapped lines
- L66-71 _public method_ `public static void WriteWarning(string text)` — Writes an colored warning message to the console
- L77-82 _public method_ `public static void WriteError(string text)` — Writes an colored error message to the console

### `Source/Programs/Shared/EpicGames.Core/ContentHash.cs` (EpicGames.Core)


#### class `EpicGames.Core.ContentHash`  
`public class ContentHash : IEquatable<ContentHash>`  
_public; L22-313_
- attrs: `[JsonConverter(typeof(ContentHashJsonConverter))]`
- inherits: `IEquatable<ContentHash>`
- desc: Stores the hash value for a piece of content as a byte array, allowing it to be used as a dictionary key
- L27 _public const_ `public const int LengthMD5 = 16` — Length of an MD5 hash
- L32 _public const_ `public const int LengthSHA1 = 20` — Length of a SHA1 hash
- L37 _public property_ `public static ContentHash Empty { get; }` — Retrieves an empty content hash
- L42-46 _public property_ `public byte[] Bytes { get; set; }` — The bytes compromising this hash
- L52-55 _public ctor_ `public ContentHash(byte[] bytes)` — Constructor
- L62-65 _public method_ `public override bool Equals(object? other)` — Compares two content hashes for equality
- L72-82 _public method_ `public bool Equals(ContentHash? other)` — Compares two content hashes for equality
- L90-100 _public operator_ `public static bool operator ==(ContentHash? a, ContentHash? b)` — Compares two content hash objects for equality
- L108-111 _public operator_ `public static bool operator !=(ContentHash? a, ContentHash? b)` — Compares two content hash objects for inequality
- L119-122 _public method_ `public static ContentHash Compute(byte[] data, HashAlgorithm algorithm)` — Creates a content hash for a block of data, using a given algorithm.
- L132-135 _public method_ `public static ContentHash Compute(byte[] data, int offset, int count, HashAlgorithm algorithm)` — Creates a content hash for a block of data, using a given algorithm.
- L143-146 _public method_ `public static ContentHash Compute(string text, HashAlgorithm algorithm)` — Creates a content hash for a string, using a given algorithm.
- L154-160 _public method_ `public static ContentHash Compute(FileReference location, HashAlgorithm algorithm)` — Creates a content hash for a file, using a given algorithm.
- L167-173 _public method_ `public static ContentHash MD5(byte[] data)` — Creates a content hash for a block of data using MD5
- L182-188 _public method_ `public static ContentHash MD5(byte[] data, int offset, int count)` — Creates a content hash for a block of data using MD5
- L195-201 _public method_ `public static ContentHash MD5(string text)` — Creates a content hash for a string using MD5.
- L208-214 _public method_ `public static ContentHash MD5(FileReference location)` — Creates a content hash for a file, using a given algorithm.
- L221-227 _public method_ `public static ContentHash SHA1(byte[] data)` — Creates a content hash for a block of data using SHA1
- L234-240 _public method_ `public static ContentHash SHA1(string text)` — Creates a content hash for a string using SHA1.
- L247-253 _public method_ `public static ContentHash SHA1(FileReference location)` — Creates a content hash for a file using SHA1.
- L260-268 _public method_ `public static ContentHash Parse(string text)` — Parse a hash from a string
- L276-289 _public method_ `public static bool TryParse(string text, [NotNullWhen(true)] out ContentHash? hash)` — Parse a hash from a string
- L295-303 _public method_ `public override int GetHashCode()` — Computes a hash code for this digest
- L309-312 _public method_ `public override string ToString()` — Formats this hash as a string

#### class `EpicGames.Core.ContentHashJsonConverter`  
`public class ContentHashJsonConverter : JsonConverter<ContentHash>`  
_public; L318-331_
- inherits: `JsonConverter<ContentHash>`
- desc: Converts ContentHash values to and from JSON
- L321-324 _public method_ `public override ContentHash Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L327-330 _public method_ `public override void Write(Utf8JsonWriter writer, ContentHash value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Core.ContentHashExtensionMethods`  
`public static class ContentHashExtensionMethods`  
_public; L336-372_
- desc: Utility methods for serializing ContentHash objects
- L343-353 _public method_ `public static void WriteContentHash(this BinaryArchiveWriter writer, ContentHash? hash)` — Writes a ContentHash to a binary archive
- L360-371 _public method_ `public static ContentHash? ReadContentHash(this BinaryArchiveReader reader)` — Reads a ContentHash from a binary archive

### `Source/Programs/Shared/EpicGames.Core/CsProjBuildHook.cs` (EpicGames.Core)


#### interface `EpicGames.Core.CsProjBuildHook`  
`public interface CsProjBuildHook : IMsBuildRegistration`  
_public; L18-65_
- inherits: `IMsBuildRegistration`
- desc: This interface exists to allow the CsProjBuilder in EpicGames.MsBuild to call back out into EpicGames.Build. It is EXTREMELY important that any type definitions that must be referenced or implemented in EpicGames.Build for use by EpicGame.MsBuild *NOT* be defined in EpicGames.MsBuild. If they are, there is a strong chance of running into an issue gathering types (Assembly.GetTypes()) on EpicGames.Build.
- L26 _public* method_ `DateTime GetLastWriteTime(DirectoryReference basePath, string relativeFilePath)` — Test the cache for a given file to get the last write time of the given file
- L34 _public* method_ `DateTime GetLastWriteTime(string basePath, string relativeFilePath)` — Test the cache for a given file to get the last write time of the given file
- L41 _public* method_ `DirectoryReference GetBuildRecordDirectory(DirectoryReference basePath)` — Return the build record directory for the given base path (i.e. engine dir or project dir)
- L48 _public* method_ `void ValidateRecursively(Dictionary<FileReference, CsProjBuildRecordEntry> buildRecords, FileReference projectPath)` — Validate the given build records for the project
- L54 _public* method_ `void SetValidBuildRecords(IReadOnlyDictionary<FileReference, CsProjBuildRecordEntry> records)` — (Optional) Sets of existing build records that are valid
- L59 _public* property_ `IReadOnlyDictionary<FileReference, CsProjBuildRecordEntry> ValidBuildRecords { get; }` — (Optional) Collection of existing build records for projects already been registered as valid, which could be skipped when building
- L64 _public* property_ `DirectoryReference EngineDirectory { get; }` — Unreal engine directory

### `Source/Programs/Shared/EpicGames.Core/CsProjBuildRecord.cs` (EpicGames.Core)


#### class `EpicGames.Core.CsProjBuildRecordRef`  
`public class CsProjBuildRecordRef`  
_public; L16-27_
- desc: The list of references projects needs to be both the path to the project and the target build time from that project.
- L21 _public property_ `public string ProjectPath { get; set; }` — Name of the referenced project
- L26 _public property_ `public DateTime TargetBuildTime { get; set; }` — The time that the target assembly was built (read from the file after the build)

#### class `EpicGames.Core.CsProjBuildRecord`  
`public class CsProjBuildRecord`  
_public; L34-123_
- desc: Acceleration structure: used to encapsulate a full set of dependencies for an msbuild project - explicit and globbed These files are written to Intermediate/ScriptModules
- L39 _public field_ `public static readonly int CurrentVersion = 7` — Version number making it possible to quickly invalidate written records.
- L44 _public field_ `public static readonly string CurrentConfiguration = "Debug"` — Build configuration for valid written records
- L54 _public property_ `public int Version { get; set; }` — Version number for this record
- L59 _public property_ `public Version RuntimeVersion { get; set; }` — .NET runtime version when the target assembly was built
- L64 _public property_ `public string? ProjectPath { get; set; }` — Path to the .csproj project file, relative to the location of the build record .json file
- L69 _public property_ `public DateTime TargetBuildTime { get; set; }` — The time that the target assembly was built (read from the file after the build)
- L74 _public property_ `public string TargetConfiguration { get; set; }` — The build configuration for the target assembly when built
- L81 _public property_ `public string? TargetPath { get; set; }` — assembly (dll) location
- L86 _public property_ `public List<CsProjBuildRecordRef> ProjectReferencesAndTimes { get; set; }` — Paths to referenced projects and the target build time in that project
- L91 _public property_ `public HashSet<string> Dependencies { get; set; }` — file dependencies. Any globs are resolved
- L122 _public property_ `public List<Glob> Globs { get; set; }` — List of globs

#### class `EpicGames.Core.CsProjBuildRecord.Glob`  
`public class Glob`  
_public; L96-117_
- desc: A glob pattern
- L101 _public property_ `public string? ItemType { get; set; }` — Type of item
- L106 _public property_ `public List<string>? Include { get; set; }` — Paths to include
- L111 _public property_ `public List<string>? Exclude { get; set; }` — Paths to exclude
- L116 _public property_ `public List<string>? Remove { get; set; }`

#### enum `EpicGames.Core.CsProjBuildRecordStatus`  
`public enum CsProjBuildRecordStatus`  
_public; L130-146_
- desc: Represents the status of a build record. When read from disk, the status will start as being unknown. Then through the validation process, it will either become valid or invalid.
- L135 _public* enumerator_ `Unknown` — Status of the build record is unknown
- L140 _public* enumerator_ `Valid` — The build record is valid and doesn't require rebuild
- L145 _public* enumerator_ `Invalid` — The build record is invalid

#### class `EpicGames.Core.CsProjBuildRecordEntry`  
`public class CsProjBuildRecordEntry`  
_public; L153-188_
- desc: Represents a runtime build record entry that isn't persisted. Aside from the build record, it contains the project file and build record file reference. Also the "need to build" status of the record.
- L159 _public property_ `public FileReference ProjectFile { get; }` — Location of the csproj file
- L164 _public property_ `public FileReference BuildRecordFile { get; }` — Location of the build record
- L169 _public property_ `public CsProjBuildRecord BuildRecord { get; }` — The persisted build record
- L174 _public property_ `public CsProjBuildRecordStatus Status { get; set; }` — Status of the build record
- L182-187 _public ctor_ `public CsProjBuildRecordEntry(FileReference projectFile, FileReference buildRecordFile, CsProjBuildRecord buildRecord)` — Construct a new entry

### `Source/Programs/Shared/EpicGames.Core/Digest.cs` (EpicGames.Core)


#### struct `EpicGames.Core.Digest`  
`public readonly struct Digest : IEquatable<Digest>`  
_public; L17-148_
- inherits: `IEquatable<Digest>`
- desc: Struct representing a weakly typed hash value. Counterpart to Digest{T} - a strongly typed digest.
- L22 _public property_ `public ReadOnlyMemory<byte> Memory { get; }` — Memory storing the digest data
- L27 _public property_ `public ReadOnlySpan<byte> Span => ...` — Accessor for the span of memory storing the data
- L33-36 _public ctor_ `public Digest(ReadOnlyMemory<byte> memory)` — Constructor
- L43-47 _public method_ `public static Digest<T> Compute<T>(byte[] data) where T : DigestTraits, new()` — Creates a content hash for a block of data, using a given algorithm.
- L54-57 _public method_ `public static Digest<T> Compute<T>(string text) where T : DigestTraits, new()` — Creates a content hash for a block of data, using a given algorithm.
- L64-75 _public method_ `public static Digest<T> Compute<T>(ReadOnlySpan<byte> data) where T : DigestTraits, new()` — Creates a content hash for a block of data, using a given algorithm.
- L82-85 _public method_ `public static Digest Parse(string text)` — Parses a digest from the given hex string
- L92-95 _public method_ `public static Digest<T> Parse<T>(string text) where T : DigestTraits, new()` — Parses a digest from the given hex string
- L98 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L101 _public method_ `public bool Equals(Digest other)` — (inheritdoc)
- L104 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L107 _public method_ `public override string ToString()` — (inheritdoc)
- L115-118 _public operator_ `public static bool operator ==(Digest a, Digest b)` — Test two hash values for equality
- L126-129 _public operator_ `public static bool operator !=(Digest a, Digest b)` — Test two hash values for equality
- L135-138 _public operator_ `public static implicit operator Digest(ReadOnlyMemory<byte> memory)` — Implicit conversion operator from memory objects
- L144-147 _public operator_ `public static implicit operator Digest(byte[] memory)` — Implicit conversion operator from byte arrays

#### class `EpicGames.Core.DigestTraits`  
`public abstract class DigestTraits`  
_public; L153-174_
- desc: Traits for a hashing algorithm
- L158 _public property_ `public int Length { get; }` — Length of the produced hash
- L164-167 _protected ctor_ `protected DigestTraits(int length)` — Constructor
- L173 _public method_ `public abstract HashAlgorithm CreateAlgorithm()` — Creates a HashAlgorithm object

#### class `EpicGames.Core.Md5`  
`public class Md5 : DigestTraits`  
_public; L179-196_
- inherits: `DigestTraits`
- desc: Traits for the MD5 hash algorithm
- L184 _public const_ `public new const int Length = 16` — Length of the produced digest
- L189-192 _public ctor_ `public Md5() : base(Length)` — Constructor
- L195 _public method_ `public override HashAlgorithm CreateAlgorithm()` — (inheritdoc)

#### class `EpicGames.Core.Sha1`  
`public class Sha1 : DigestTraits`  
_public; L201-218_
- inherits: `DigestTraits`
- desc: Traits for the SHA1 hash algorithm
- L206 _public const_ `public new const int Length = 20` — Length of the produced digest
- L211-214 _public ctor_ `public Sha1() : base(Length)` — Constructor
- L217 _public method_ `public override HashAlgorithm CreateAlgorithm()` — (inheritdoc)

#### class `EpicGames.Core.Sha256`  
`public class Sha256 : DigestTraits`  
_public; L223-240_
- inherits: `DigestTraits`
- desc: Traits for the SHA1 hash algorithm
- L228 _public const_ `public new const int Length = 32` — Length of the produced digest
- L233-236 _public ctor_ `public Sha256() : base(Length)` — Constructor
- L239 _public method_ `public override HashAlgorithm CreateAlgorithm()` — (inheritdoc)

#### struct `EpicGames.Core.Digest`  
`public readonly struct Digest<T> : IEquatable<Digest<T>> where T : DigestTraits, new()`  
_public; L245-326_
- inherits: `IEquatable<Digest<T>>`
- constraints: `where T : DigestTraits, new()`
- desc: Generic HashValue implementation
- L250 _public property_ `public static T Traits { get; }` — Traits instance
- L255 _public property_ `public static int Length => ...` — Length of a hash value
- L260 _public property_ `public static Digest<T> Zero => ...` — Zero digest value
- L265 _public property_ `public ReadOnlyMemory<byte> Memory { get; }` — Memory storing the digest data
- L270 _public property_ `public ReadOnlySpan<byte> Span => ...` — Accessor for the span of memory storing the data
- L276-279 _public ctor_ `public Digest(ReadOnlyMemory<byte> memory)` — Constructor
- L282 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L285 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L288 _public method_ `public override string ToString()` — (inheritdoc)
- L291 _public method_ `public bool Equals(Digest<T> other)` — (inheritdoc)
- L299 _public operator_ `public static bool operator ==(Digest<T> a, Digest<T> b)` — Test two hash values for equality
- L307 _public operator_ `public static bool operator !=(Digest<T> a, Digest<T> b)` — Test two hash values for equality
- L313-316 _public operator_ `public static implicit operator Digest<T>(ReadOnlyMemory<byte> memory)` — Implicit conversion operator from memory objects
- L322-325 _public operator_ `public static implicit operator Digest<T>(byte[] memory)` — Implicit conversion operator from byte arrays

#### class `EpicGames.Core.DigestExtensions`  
`public static class DigestExtensions`  
_public; L331-374_
- desc: Extension methods for dealing with digests
- L338-341 _public method_ `public static Digest ReadDigest(this MemoryReader reader)` — Read a digest from a memory reader
- L349-352 _public method_ `public static Digest<T> ReadDigest<T>(this MemoryReader reader) where T : DigestTraits, new()` — Read a strongly-typed digest from a memory reader
- L359-362 _public method_ `public static void WriteDigest(this MemoryWriter writer, Digest digest)` — Write a digest to a memory writer
- L370-373 _public method_ `public static void WriteDigest<T>(this MemoryWriter writer, Digest<T> digest) where T : DigestTraits, new()` — Write a strongly typed digest to a memory writer

### `Source/Programs/Shared/EpicGames.Core/DirectoryReference.cs` (EpicGames.Core)


#### class `EpicGames.Core.DirectoryReference`  
`public class DirectoryReference : FileSystemReference, IEquatable<DirectoryReference>, IComparable<DirectoryReference>`  
_public; L21-408_
- attrs: `[Serializable] [TypeConverter(typeof(DirectoryReferenceTypeConverter))] [JsonConverter(typeof(DirectoryReferenceJsonConverter))]`
- inherits: `FileSystemReference, IEquatable<DirectoryReference>, IComparable<DirectoryReference>`
- desc: Representation of an absolute directory path. Allows fast hashing and comparisons.
- L38-41 _public ctor_ `public DirectoryReference(string inPath) : base(FixTrailingPathSeparator(Path.GetFullPath(inPath)))` — Default constructor.
- L47-50 _public ctor_ `public DirectoryReference(DirectoryInfo inInfo) : base(FixTrailingPathSeparator(inInfo.FullName))` — Construct a DirectoryReference from a DirectoryInfo object.
- L57-61 _public ctor_ `public DirectoryReference(string fullName, Sanitize sanitize) : base(fullName)` — Constructor for creating a directory object directly from two strings.
- L69-87 _private method_ `private static string FixTrailingPathSeparator(string dirName)` — Ensures that the correct trailing path separator is appended. On Windows, the root directory (eg. C:\) always has a trailing path separator, but no other path does.
- L93 _public method_ `public string GetDirectoryName()` — Gets the top level directory name
- L99-122 _public property_ `public DirectoryReference? ParentDirectory { get; }` — Gets the directory containing this object
- L128-136 _public method_ `public static void AddDirectoryToPath(DirectoryReference path)` — Add a directory to the PATH environment variable
- L142 _public method_ `public static DirectoryReference GetTempPath()` — Returns the path of the current user's temporary folder
- L149-153 _public method_ `public static DirectoryReference? GetSpecialFolder(Environment.SpecialFolder folder)` — Gets the path for a special folder
- L159 _public method_ `public bool IsRootDirectory()` — Determines whether this path represents a root directory in the filesystem
- L167 _public method_ `public static DirectoryReference Combine(DirectoryReference baseDirectory, params string[] fragments)` — Combine several fragments with a base directory, to form a new directory name
- L175-189 _public operator_ `public static bool operator ==(DirectoryReference? a, DirectoryReference? b)` — Compares two filesystem object names for equality. Uses the canonical name representation, not the display name representation.
- L197 _public operator_ `public static bool operator !=(DirectoryReference? a, DirectoryReference? b)` — Compares two filesystem object names for inequality. Uses the canonical name representation, not the display name representation.
- L200 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L207 _public method_ `public bool Equals(DirectoryReference? obj)` — Compares against another object for equality.
- L210 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L213 _public method_ `public int CompareTo(DirectoryReference? other)` — (inheritdoc)
- L216 _public operator_ `public static bool operator <(DirectoryReference left, DirectoryReference right)` — (inheritdoc)
- L219 _public operator_ `public static bool operator <=(DirectoryReference left, DirectoryReference right)` — (inheritdoc)
- L222 _public operator_ `public static bool operator >(DirectoryReference left, DirectoryReference right)` — (inheritdoc)
- L225 _public operator_ `public static bool operator >=(DirectoryReference left, DirectoryReference right)` — (inheritdoc)
- L232 _public method_ `public static void Move(DirectoryReference sourceDir, DirectoryReference destinationDir)` — Moves a directory from one location to another
- L240-253 _public method_ `public static void Copy(DirectoryReference sourceDir, DirectoryReference destinationDir)` — Copies a directory from one location to another
- L260-273 _public method_ `public static long GetTotalSize(DirectoryReference dirPath)` — Calculates the total size in bytes of all files in a directory and its subdirectories
- L280 _public method_ `public static DirectoryReference MakeRemote(string absolutePath)` — Helper function to create a remote directory reference. Unlike normal DirectoryReference objects, these aren't converted to a full path in the local filesystem.
- L288 _public method_ `public static DirectoryReference? FromFile(FileReference? file)` — attrs: `[return: NotNullIfNotNull(nameof(file))]` — Gets the parent directory for a file, or returns null if it's null.
- L295 _public method_ `public static DirectoryReference? FromString(string? directoryName)` — Create a DirectoryReference from a string. If the string is null or whitespace, returns a null DirectoryReference.
- L302 _public method_ `public static DirectoryReference FindCorrectCase(DirectoryReference location)` — Finds the correct case to match the location of this file on disk. Uses the given case for parts of the path that do not exist.
- L308 _public method_ `public DirectoryInfo ToDirectoryInfo()` — Constructs a DirectoryInfo object from this reference
- L316 _public method_ `public static DirectoryReference GetCurrentDirectory()` — Finds the current directory
- L322 _public method_ `public static void CreateDirectory(DirectoryReference location)` — Creates a directory
- L328 _public method_ `public static void Delete(DirectoryReference location)` — Deletes a directory
- L335 _public method_ `public static void Delete(DirectoryReference location, bool bRecursive)` — Deletes a directory
- L342 _public method_ `public static bool Exists(DirectoryReference location)` — Checks whether the directory exists
- L349 _public method_ `public static IEnumerable<FileReference> EnumerateFiles(DirectoryReference baseDir)` — Enumerate files from a given directory
- L357 _public method_ `public static IEnumerable<FileReference> EnumerateFiles(DirectoryReference baseDir, string pattern)` — Enumerate files from a given directory
- L366 _public method_ `public static IEnumerable<FileReference> EnumerateFiles(DirectoryReference baseDir, string pattern, SearchOption option)` — Enumerate files from a given directory
- L373 _public method_ `public static IEnumerable<DirectoryReference> EnumerateDirectories(DirectoryReference baseDir)` — Enumerate subdirectories in a given directory
- L381 _public method_ `public static IEnumerable<DirectoryReference> EnumerateDirectories(DirectoryReference baseDir, string pattern)` — Enumerate subdirectories in a given directory
- L390 _public method_ `public static IEnumerable<DirectoryReference> EnumerateDirectories(DirectoryReference baseDir, string pattern, SearchOption option)` — Enumerate subdirectories in a given directory
- L396-405 _public method_ `public static void SetCurrentDirectory(DirectoryReference location)` — Sets the current directory

#### enum `EpicGames.Core.DirectoryReference.Sanitize`  
`public enum Sanitize`  
_public; L26-32_
- desc: Special value used to invoke the non-sanitizing constructor overload
- L31 _public* enumerator_ `None` — Dummy value

#### class `EpicGames.Core.DirectoryReferenceTypeConverter`  
`class DirectoryReferenceTypeConverter : TypeConverter`  
_internal*; L413-446_
- inherits: `TypeConverter`
- desc: Type converter to/from strings
- L416-419 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L422-429 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L432-435 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L438-445 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Core.DirectoryReferenceJsonConverter`  
`internal class DirectoryReferenceJsonConverter : JsonConverter<DirectoryReference>`  
_internal; L448-474_
- inherits: `JsonConverter<DirectoryReference>`
- L450-454 _public method_ `public override DirectoryReference? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L456-463 _public method_ `public override DirectoryReference ReadAsPropertyName(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L465-468 _public method_ `public override void Write(Utf8JsonWriter writer, DirectoryReference value, JsonSerializerOptions options)`
- L470-473 _public method_ `public override void WriteAsPropertyName(Utf8JsonWriter writer, [DisallowNull] DirectoryReference value, JsonSerializerOptions options)`

#### class `EpicGames.Core.DirectoryReferenceExtensionMethods`  
`public static class DirectoryReferenceExtensionMethods`  
_public; L479-530_
- desc: Extension methods for passing DirectoryReference arguments
- L486 _public method_ `public static void Write(this BinaryWriter writer, DirectoryReference directory)` — Manually serialize a file reference to a binary stream.
- L493-497 _public method_ `public static DirectoryReference? ReadDirectoryReference(this BinaryReader reader)` — Manually deserialize a directory reference from a binary stream.
- L504 _public method_ `public static DirectoryReference ReadDirectoryReferenceNotNull(this BinaryReader reader)` — Manually deserialize a directory reference from a binary stream.
- L511 _public method_ `public static void WriteDirectoryReference(this BinaryArchiveWriter writer, DirectoryReference? directory)` — Writes a directory reference to a binary archive
- L518-522 _public method_ `public static DirectoryReference? ReadDirectoryReference(this BinaryArchiveReader reader)` — Reads a directory reference from a binary archive
- L529 _public method_ `public static DirectoryReference ReadDirectoryReferenceNotNull(this BinaryArchiveReader reader)` — Reads a directory reference from a binary archive

### `Source/Programs/Shared/EpicGames.Core/DirectoryUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.DirectoryUtils`  
`public static class DirectoryUtils`  
_public; L11-58_
- desc: Utility functions for manipulating directories
- L18-57 _public method_ `public static DirectoryInfo FindCorrectCase(DirectoryInfo info)` — Finds the on-disk case of a a directory

### `Source/Programs/Shared/EpicGames.Core/EnumerableExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.EnumerableExtensions`  
`public static class EnumerableExtensions`  
_public; L11-150_
- desc: Extension methods for IEnumerable{T}
- L17-23 _public method_ `public static void DisposeAll(this IEnumerable<IDisposable> sequence)` — Dispose all elements in a sequence
- L32-48 _public method_ `public static IEnumerable<IReadOnlyList<TElement>> Batch<TElement>(this IEnumerable<TElement> sequence, int batchSize)` — Split the sequence into batches of at most the given size
- L57-78 _public method_ `public static TElement MinBy<TElement>(this IEnumerable<TElement> sequence, Func<TElement, int> selector)` — Finds the minimum element by a given field
- L87-108 _public method_ `public static TElement MaxBy<TElement>(this IEnumerable<TElement> sequence, Func<TElement, int> selector)` — Finds the maximum element by a given field
- L119-149 _public method_ `public static IEnumerable<(TKey, TOldValue?, TNewValue?)> Zip<TKey, TOldValue, TNewValue>(this IReadOnlyDictionary<TKey, TOldValue>? oldDictionary, IReadOnlyDictionary<TKey, TNewValue>? newDictionary) where TKey : notnull where TOldValue : class where TNewValue : class` — Zips two dictionaries, returning a sequence of keys with the old and new values (or null if they have been removed).

### `Source/Programs/Shared/EpicGames.Core/ExceptionUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.ExceptionUtils`  
`public static class ExceptionUtils`  
_public; L13-147_
- desc: Methods for adding context information to exceptions
- L18 _private* const_ `const string ContextEntryName = "EpicGames.Context"` — Unique key name for adding context to exceptions thrown inside Epic apps
- L26-35 _public method_ `public static void AddContext(Exception ex, string message)` — Adds a context message to a list stored on the given exception. Intended to be used in situations where supplying additional context for an exception is valuable, but wrapping it would remove information.
- L44-47 _public method_ `public static void AddContext(Exception ex, string format, params object[] args)` — Adds a context message to a list stored on the given exception. Intended to be used in situations where supplying additional context for an exception is valuable, but wrapping it would remove information.
- L54-64 _public method_ `public static IEnumerable<string> GetContext(Exception ex)` — Enumerates the context lines from the given exception
- L71-95 _public method_ `public static string FormatException(Exception ex)` — Formats an exception for display in the log, including additional lines of context that were attached to it.
- L102-146 _public method_ `public static string FormatExceptionDetails(Exception ex)` — Formats a detailed information about where an exception occurs, including any inner exceptions

### `Source/Programs/Shared/EpicGames.Core/FatalErrorException.cs` (EpicGames.Core)


#### class `EpicGames.Core.FatalErrorException`  
`public class FatalErrorException : Exception`  
_public; L10-65_
- inherits: `Exception`
- desc: Base class for user-facing fatal errors. These errors are shown to the user prior to termination, without a callstack, and may dictate the program exit code.
- L15 _public property_ `public int ExitCode { get; set; }` — Exit code for the process
- L21-24 _public ctor_ `public FatalErrorException(string message) : base(message)` — Constructor
- L31-34 _public ctor_ `public FatalErrorException(Exception innerException, string message) : base(message, innerException)` — Constructor
- L41-44 _public ctor_ `public FatalErrorException(string format, params object[] arguments) : base(String.Format(format, arguments))` — Constructor
- L52-55 _public ctor_ `public FatalErrorException(Exception innerException, string format, params object[] arguments) : base(String.Format(format, arguments), innerException)` — Constructor which wraps another exception
- L61-64 _public method_ `public override string ToString()` — Returns the string representing the exception. Our build exceptions do not show the callstack since they are used to report known error conditions.

### `Source/Programs/Shared/EpicGames.Core/FileFilter.cs` (EpicGames.Core)


#### enum `EpicGames.Core.FileFilterType`  
`public enum FileFilterType`  
_public; L16-27_
- desc: Indicates whether files which match a pattern should be included or excluded
- L21 _public* enumerator_ `Include` — Include files matching this pattern
- L26 _public* enumerator_ `Exclude` — Exclude files matching this pattern

#### class `EpicGames.Core.FileFilter`  
`public class FileFilter`  
_public; L35-658_
- attrs: `[TypeConverter(typeof(FileFilterConverter))]`
- desc: Stores a set of rules, similar to p4 path specifications, which can be used to efficiently filter files in or out of a set. The rules are merged into a tree with nodes for each path fragments and rule numbers in each leaf, allowing tree traversal in an arbitrary order to how they are applied.
- L40 _private* field_ `readonly FileFilterNode _rootNode` — Root node for the tree.
- L45 _private* field_ `readonly FileFilterNode _defaultNode` — The default node, which will match any path
- L50 _private* field_ `readonly List<FileFilterNode> _rules = []` — Terminating nodes for each rule added to the filter
- L55-61 _public ctor_ `public FileFilter(FileFilterType defaultType = FileFilterType.Exclude)` — Default constructor
- L67-74 _public ctor_ `public FileFilter(FileFilter other) : this(other._defaultNode.Type)` — Copy constructor
- L81-88 _public ctor_ `public FileFilter(IEnumerable<string> lines, FileFilterType defaultType = FileFilterType.Exclude) : this(defaultType)` — Constructs a file filter from a p4-style filespec. Exclude lines are prefixed with a - character.
- L94-103 _public method_ `public static FileFilter? Parse(string? text)` — Parse a filter pattern, determining the default rule type from the initial rule
- L109-119 _public method_ `public static FileFilter? Parse(IReadOnlyList<string>? rules)` — Parse a filter pattern, determining the default rule type from the initial rule
- L125-135 _public method_ `public void AddRule(string rule)` — Adds an include or exclude rule to the filter
- L142-165 _public method_ `public void AddRule(string rule, params string[] allowTags)` — Adds an include or exclude rule to the filter. The rule may be
- L171-177 _public method_ `public void AddRules(IEnumerable<string> rules)` — Adds several rules to the filter
- L184-190 _public method_ `public void AddRules(IEnumerable<string> rules, FileFilterType type)` — Adds several rules to the filter
- L198-204 _public method_ `public void AddRules(IEnumerable<string> rules, params string[] tags)` — Adds several rules in the given lines. Rules may be prefixed with conditions of the syntax {Key=Value, Key2=Value2}, which will be evaluated using variables in the given dictionary before being added.
- L212-215 _public method_ `public void AddRuleForFile(FileReference file, DirectoryReference baseDirectory, FileFilterType type)` — Adds a rule which matches a filename relative to a given base directory.
- L223-229 _public method_ `public void AddRuleForFiles(IEnumerable<FileReference> files, DirectoryReference baseDirectory, FileFilterType type)` — Adds rules for files which match the given names
- L237-255 _public method_ `public void ReadRulesFromFile(FileReference fileName, string sectionName, params string[] allowTags)` — Reads a configuration file split into sections
- L261-264 _public method_ `public void Include(string pattern)` — Adds an include rule to the filter
- L270-276 _public method_ `public void Include(IEnumerable<string> patterns)` — Adds several exclude rules to the filter
- L282-285 _public method_ `public void Exclude(string pattern)` — Adds an exclude rule to the filter
- L291-297 _public method_ `public void Exclude(IEnumerable<string> patterns)` — Adds several exclude rules to the filter
- L304-315 _public method_ `public static string NormalizePath(string path)` — Normalizes a path to use forward slashes as a path separator
- L322-394 _public method_ `public void AddRule(string pattern, FileFilterType type)` — Adds an include or exclude rule to the filter
- L401-408 _public method_ `public bool Matches(string fileName)` — Determines whether the given file matches the filter
- L415-422 _public method_ `public bool PossiblyMatches(string folderName)` — Determines whether it's possible for anything within the given folder name to match the filter. Useful to early out of recursive file searches.
- L429-432 _public method_ `public IEnumerable<string> ApplyTo(IEnumerable<string> fileNames)` — Applies the filter to each element in a sequence, and returns the list of files that match
- L440-443 _public method_ `public IEnumerable<FileReference> ApplyTo(DirectoryReference baseDirectory, IEnumerable<FileReference> fileNames)` — Applies the filter to each element in a sequence, and returns the list of files that match
- L451 _public method_ `public List<FileReference> ApplyToDirectory(DirectoryReference directoryName, bool bIgnoreSymlinks)` — Finds a list of files within a given directory which match the filter.
- L460-468 _public method_ `public List<FileInfo> ApplyToDirectory(DirectoryInfo directoryInfo, bool bIgnoreSymlinks)` — Finds a list of files within a given directory which match the filter.
- L477 _public method_ `public List<FileReference> ApplyToDirectory(DirectoryReference directoryName, string prefixPath, bool bIgnoreSymlinks)` — Finds a list of files within a given directory which match the filter.
- L487-495 _public method_ `public List<FileInfo> ApplyToDirectory(DirectoryInfo directoryInfo, string prefixPath, bool bIgnoreSymlinks)` — Finds a list of files within a given directory which match the filter.
- L502-514 _public method_ `public static int FindWildcardIndex(string pattern)` — Checks whether the given pattern contains a supported wildcard. Useful for distinguishing explicit file references from opportunistic file references.
- L521-531 _public method_ `public static List<FileReference> ResolveWildcard(string pattern)` — Resolve an individual wildcard to a set of files
- L539-544 _public method_ `public static List<FileReference> ResolveWildcard(DirectoryReference baseDir, string pattern)` — Resolve an individual wildcard to a set of files
- L554-572 _private* method_ `void FindMatchesFromDirectory(DirectoryInfo currentDirectory, string namePrefix, bool bIgnoreSymlinks, List<FileInfo> matchingFileNames)` — Finds a list of files within a given directory which match the filter.
- L582-616 _private* method_ `static FileFilterNode FindMatchingNode(FileFilterNode currentNode, string[] tokens, int tokenIdx, FileFilterNode currentBestNode)` — Finds the node which matches a given list of tokens.
- L626-657 _private* method_ `static int HighestPossibleIncludeMatch(FileFilterNode currentNode, string[] tokens, int tokenIdx, int currentBestRuleNumber)` — Returns the highest possible rule number which can match the given list of input tokens, assuming that the list of input tokens is incomplete.

#### class `EpicGames.Core.FileFilterConverter`  
`class FileFilterConverter : TypeConverter`  
_internal*; L663-678_
- inherits: `TypeConverter`
- desc: Type converter for FileFilter objects. Allows parsing filters from command line arguments.
- L666 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L670-677 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/FileFilterNode.cs` (EpicGames.Core)


#### class `EpicGames.Core.FileFilterNode`  
`class FileFilterNode`  
_internal*; L11-116_
- desc: Node within a filter tree. Each node matches a single path fragment - a folder or file name, with an include or exclude rule consisting of a sequence of nodes.
- L16 _public field_ `public readonly FileFilterNode? Parent` — Node which this is parented to. Null for the root node.
- L21 _public field_ `public readonly string Pattern` — Pattern to match for this node. May contain * or ? wildcards.
- L26 _public property_ `public int MaxIncludeRuleNumber { get; set; }` — Highest include rule number matched by this node or any child nodes.
- L31 _public property_ `public int MaxExcludeRuleNumber { get; set; }` — Highest exclude rule number matched by this node or any child nodes.
- L36 _public property_ `public List<FileFilterNode> Branches { get; set; }` — Child branches of this node, distinct by the the pattern for each.
- L41 _public property_ `public int RuleNumber { get; set; }` — If a path matches the sequence of nodes ending in this node, the number of the rule which added it. -1 if this was not the last node in a rule.
- L46 _public property_ `public FileFilterType Type { get; set; }` — Whether a rule terminating in this node should include files or exclude files.
- L51-57 _public ctor_ `public FileFilterNode(FileFilterNode? inParent, string inPattern)` — Default constructor.
- L62-72 _public method_ `public bool IsMatch(string token)` — Determine if the given token matches the pattern in this node
- L77-106 _private* method_ `static bool IsMatch(string token, int tokenIdx, string pattern, int patternIdx)` — Determine if a given token matches a pattern, starting from the given positions within each string.
- L112-115 _public method_ `public override string ToString()` — Debugger visualization

### `Source/Programs/Shared/EpicGames.Core/FilePattern.cs` (EpicGames.Core)


#### class `EpicGames.Core.FilePatternException`  
`public class FilePatternException : Exception`  
_public; L16-31_
- inherits: `Exception`
- desc: Invalid file pattern exception
- L21-24 _public ctor_ `public FilePatternException(string message) : base(message)` — Constructor
- L27-30 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Core.FilePatternSourceFileNotUnderBaseDirException`  
`public class FilePatternSourceFileNotUnderBaseDirException : FilePatternException`  
_public; L36-45_
- inherits: `FilePatternException`
- desc: Exception thrown to indicate that a source file is not under the given base directory
- L41-44 _public ctor_ `public FilePatternSourceFileNotUnderBaseDirException(string message) : base(message)` — Constructor

#### class `EpicGames.Core.FilePatternSourceFileMissingException`  
`public class FilePatternSourceFileMissingException : FilePatternException`  
_public; L50-59_
- inherits: `FilePatternException`
- desc: Exception thrown to indicate that a source file is missing
- L55-58 _public ctor_ `public FilePatternSourceFileMissingException(string message) : base(message)` — Constructor

#### class `EpicGames.Core.FilePattern`  
`public class FilePattern`  
_public; L64-465_
- desc: Encapsulates a pattern containing the '?', '*', and '...' wildcards.
- L69 _public property_ `public DirectoryReference BaseDirectory { get; }` — Base directory for all matched files
- L74 _public property_ `public IReadOnlyList<string> Tokens { get; }` — List of tokens in the pattern. Every second token is a wildcard, other tokens are string fragments. Always has an odd number of elements. Path separators are normalized to the host platform format.
- L80-84 _public ctor_ `public FilePattern(FileReference file)` — Constructs a file pattern which matches a single file
- L91-167 _public ctor_ `public FilePattern(DirectoryReference rootDirectory, string pattern)` — Constructs a file pattern from the given string, resolving relative paths to the given directory.
- L173-194 _public method_ `public FilePattern AsDirectoryPattern()` — A pattern without wildcards may match either a single file or directory based on context. This pattern resolves to the later as necessary, producing a new pattern.
- L200-210 _public method_ `public FileReference GetSingleFile()` — For a pattern that does not contain wildcards, returns the single file location
- L216-220 _public method_ `public bool EndsWithDirectorySeparator()` — Checks whether this pattern is explicitly a directory, ie. is terminated with a directory separator
- L226-229 _public method_ `public bool ContainsWildcards()` — Determines whether the pattern contains wildcards
- L236-253 _public method_ `public bool IsCompatibleWith(FilePattern other)` — Tests whether a pattern is compatible with another pattern (that is, that the number and type of wildcards match)
- L259-284 _public method_ `public string GetRegexPattern()` — Converts this pattern to a C# regex format string, which matches paths relative to the base directory formatted with native directory separators
- L290-308 _public method_ `public string GetRegexReplacementPattern()` — Creates a regex replacement pattern
- L316-428 _public method_ `public static Dictionary<FileReference, FileReference> CreateMapping(HashSet<FileReference>? files, ref FilePattern sourcePattern, ref FilePattern targetPattern)` — Creates a file mapping between a set of source patterns and a target pattern. All patterns should have a matching order and number of wildcards.
- L436-455 _public method_ `public static List<FileReference> CheckInputFiles(IEnumerable<FileReference> inputFiles, DirectoryReference baseDirectory)` — Checks that the given input files all exist and are under the given base directory
- L461-464 _public method_ `public override string ToString()` — Formats the pattern as a string

### `Source/Programs/Shared/EpicGames.Core/FileReference.cs` (EpicGames.Core)


#### class `EpicGames.Core.FileReference`  
`public class FileReference : FileSystemReference, IEquatable<FileReference>, IComparable<FileReference>`  
_public; L24-827_
- attrs: `[Serializable] [TypeConverter(typeof(FileReferenceTypeConverter))] [JsonConverter(typeof(FileReferenceJsonConverter))]`
- inherits: `FileSystemReference, IEquatable<FileReference>, IComparable<FileReference>`
- desc: Representation of an absolute file path. Allows fast hashing and comparisons.
- L41-48 _public ctor_ `public FileReference(string inPath) : base(Path.GetFullPath(inPath))` — Default constructor.
- L54-57 _public ctor_ `public FileReference(FileInfo inInfo) : base(inInfo.FullName)` — Construct a FileReference from a FileInfo object.
- L64-68 _public ctor_ `public FileReference(string fullName, Sanitize sanitize) : base(fullName)` — Default constructor.
- L75 _public method_ `public static FileReference? FromString(string? fileName)` — Create a FileReference from a string. If the string is null or whitespace, returns a null FileReference.
- L81 _public method_ `public string GetFileName()` — Gets the file name without path information
- L87 _public method_ `public string GetFileNameWithoutExtension()` — Gets the file name without path information or an extension
- L93-106 _public method_ `public string GetFileNameWithoutAnyExtensions()` — Gets the file name without path or any extensions
- L112 _public method_ `public string GetExtension()` — Gets the extension for this filename
- L119 _public method_ `public FileReference ChangeExtension(string? extension)` — Change the file's extension to something else
- L125-145 _public property_ `public DirectoryReference Directory { get; }` — Gets the directory containing this file
- L153 _public method_ `public static FileReference Combine(DirectoryReference baseDirectory, params string[] fragments)` — Combine several fragments with a base directory, to form a new filename
- L161 _public operator_ `public static FileReference operator +(FileReference a, string b)` — Append a string to the end of a filename
- L169-183 _public operator_ `public static bool operator ==(FileReference? a, FileReference? b)` — Compares two filesystem object names for equality. Uses the canonical name representation, not the display name representation.
- L191 _public operator_ `public static bool operator !=(FileReference? a, FileReference? b)` — Compares two filesystem object names for inequality. Uses the canonical name representation, not the display name representation.
- L194 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L201 _public method_ `public bool Equals(FileReference? obj)` — Compares against another object for equality.
- L204 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L207 _public method_ `public int CompareTo(FileReference? other)` — (inheritdoc)
- L210 _public operator_ `public static bool operator <(FileReference left, FileReference right)` — (inheritdoc)
- L213 _public operator_ `public static bool operator <=(FileReference left, FileReference right)` — (inheritdoc)
- L216 _public operator_ `public static bool operator >(FileReference left, FileReference right)` — (inheritdoc)
- L219 _public operator_ `public static bool operator >=(FileReference left, FileReference right)` — (inheritdoc)
- L227 _public method_ `public static FileReference MakeRemote(string absolutePath)` — Helper function to create a remote file reference. Unlike normal FileReference objects, these aren't converted to a full path in the local filesystem, but are left as they are passed in.
- L233-243 _public method_ `public static void MakeWriteable(FileReference location)` — Makes a file location writeable;
- L251-267 _public method_ `public static Encoding GetEncoding(FileReference location, out int skipBytes)` — Get the encoding of a file by checking for BOM bytes
- L274 _public method_ `public static Encoding GetEncoding(FileReference location)` — Get the encoding of a file by checking for BOM bytes
- L282-297 _public method_ `public static async Task<Encoding> GetEncodingAsync(FileReference location, CancellationToken cancellationToken = default)` — Get the encoding of a file by checking for BOM bytes
- L304 _public method_ `public static FileReference FindCorrectCase(FileReference location)` — Finds the correct case to match the location of this file on disk. Uses the given case for parts of the path that do not exist.
- L310 _public method_ `public FileInfo ToFileInfo()` — Constructs a FileInfo object from this reference
- L319 _public method_ `public static void Copy(FileReference sourceLocation, FileReference targetLocation)` — Copies a file from one location to another
- L327 _public method_ `public static void Copy(FileReference sourceLocation, FileReference targetLocation, bool bOverwrite)` — Copies a file from one location to another
- L332 _public method_ `public static void Delete(FileReference location)` — Deletes this file
- L338 _public method_ `public static bool Exists(FileReference location)` — Determines whether the given filename exists
- L345 _public method_ `public static FileAttributes GetAttributes(FileReference location)` — Gets the attributes for a file
- L352 _public method_ `public static DateTime GetLastWriteTime(FileReference location)` — Gets the time that the file was last written to
- L359 _public method_ `public static DateTime GetLastWriteTimeUtc(FileReference location)` — Gets the time that the file was last written to
- L366 _public method_ `public static void Move(FileReference sourceLocation, FileReference targetLocation)` — Moves a file from one location to another
- L374 _public method_ `public static void Move(FileReference sourceLocation, FileReference targetLocation, bool overwrite)` — Moves a file from one location to another
- L382 _public method_ `public static FileStream Open(FileReference location, FileMode mode)` — Opens a FileStream on the specified path with read/write access
- L391 _public method_ `public static FileStream Open(FileReference location, FileMode mode, FileAccess access)` — Opens a FileStream on the specified path
- L401 _public method_ `public static FileStream Open(FileReference location, FileMode mode, FileAccess access, FileShare share)` — Opens a FileStream on the specified path
- L408 _public method_ `public static byte[] ReadAllBytes(FileReference location)` — Reads the contents of a file
- L416 _public method_ `public static Task<byte[]> ReadAllBytesAsync(FileReference location, CancellationToken cancellationToken = default)` — Reads the contents of a file
- L423 _public method_ `public static string ReadAllText(FileReference location)` — Reads the contents of a file
- L431-451 _public method_ `public static string ReadAllText(FileReference location, Encoding encoding)` — Reads the contents of a file
- L459 _public method_ `public static Task<string> ReadAllTextAsync(FileReference location, CancellationToken cancellationToken = default)` — Reads the contents of a file
- L468 _public method_ `public static Task<string> ReadAllTextAsync(FileReference location, Encoding encoding, CancellationToken cancellationToken = default)` — Reads the contents of a file
- L475 _public method_ `public static string[] ReadAllLines(FileReference location)` — Reads the contents of a file
- L483 _public method_ `public static string[] ReadAllLines(FileReference location, Encoding encoding)` — Reads the contents of a file
- L491 _public method_ `public static Task<string[]> ReadAllLinesAsync(FileReference location, CancellationToken cancellationToken = default)` — Reads the contents of a file
- L500 _public method_ `public static Task<string[]> ReadAllLinesAsync(FileReference location, Encoding encoding, CancellationToken cancellationToken = default)` — Reads the contents of a file
- L507 _public method_ `public static void SetAttributes(FileReference location, FileAttributes attributes)` — Sets the attributes for a file
- L514 _public method_ `public static void SetLastWriteTime(FileReference location, DateTime lastWriteTime)` — Sets the time that the file was last written to
- L521 _public method_ `public static void SetLastWriteTimeUtc(FileReference location, DateTime lastWriteTimeUtc)` — Sets the time that the file was last written to
- L528 _public method_ `public static void SetLastAccessTime(FileReference location, DateTime lastWriteTime)` — Sets the time that the file was last accessed.
- L535 _public method_ `public static void SetLastAccessTimeUtc(FileReference location, DateTime lastWriteTimeUtc)` — Sets the time that the file was last accessed.
- L542 _public method_ `public static void WriteAllBytes(FileReference location, byte[] contents)` — Writes the contents of a file
- L550 _public method_ `public static Task WriteAllBytesAsync(FileReference location, byte[] contents, CancellationToken cancellationToken = default)` — Writes the contents of a file
- L558-570 _public method_ `public static bool WriteAllBytesIfDifferent(FileReference location, byte[] contents)` — Writes the data to the given file, if it's different from what's there already. Returns true if contents were written.
- L579-591 _public method_ `public static async Task<bool> WriteAllBytesIfDifferentAsync(FileReference location, byte[] contents, CancellationToken cancellationToken = default)` — Writes the data to the given file, if it's different from what's there already. Returns true if contents were written.
- L599-611 _public method_ `public static bool WriteAllTextIfDifferent(FileReference location, string contents)` — Writes the string to the given file, if it's different from what's there already. Returns true if contents were written.
- L620-632 _public method_ `public static async Task<bool> WriteAllTextIfDifferentAsync(FileReference location, string contents, CancellationToken cancellationToken = default)` — Writes the string to the given file, if it's different from what's there already. Returns true if contents were written.
- L639 _public method_ `public static void WriteAllLines(FileReference location, IEnumerable<string> contents)` — Writes the contents of a file
- L647 _public method_ `public static void WriteAllLines(FileReference location, IEnumerable<string> contents, Encoding encoding)` — Writes the contents of a file
- L654 _public method_ `public static void WriteAllLines(FileReference location, string[] contents)` — Writes the contents of a file
- L662 _public method_ `public static void WriteAllLines(FileReference location, string[] contents, Encoding encoding)` — Writes the contents of a file
- L670 _public method_ `public static Task WriteAllLinesAsync(FileReference location, IEnumerable<string> contents, CancellationToken cancellationToken = default)` — Writes the contents of a file
- L679 _public method_ `public static Task WriteAllLinesAsync(FileReference location, IEnumerable<string> contents, Encoding encoding, CancellationToken cancellationToken = default)` — Writes the contents of a file
- L687 _public method_ `public static Task WriteAllLinesAsync(FileReference location, string[] contents, CancellationToken cancellationToken = default)` — Writes the contents of a file
- L696 _public method_ `public static Task WriteAllLinesAsync(FileReference location, string[] contents, Encoding encoding, CancellationToken cancellationToken = default)` — Writes the contents of a file
- L703 _public method_ `public static void WriteAllText(FileReference location, string contents)` — Writes the contents of a file
- L711 _public method_ `public static void WriteAllText(FileReference location, string contents, Encoding encoding)` — Writes the contents of a file
- L719 _public method_ `public static Task WriteAllTextAsync(FileReference location, string contents, CancellationToken cancellationToken = default)` — Writes the contents of a file
- L728 _public method_ `public static Task WriteAllTextAsync(FileReference location, string contents, Encoding encoding, CancellationToken cancellationToken = default)` — Writes the contents of a file
- L735 _public method_ `public static void AppendAllLines(FileReference location, IEnumerable<string> contents)` — Appends the contents to a file
- L743 _public method_ `public static void AppendAllLines(FileReference location, IEnumerable<string> contents, Encoding encoding)` — Appends the contents to a file
- L751 _public method_ `public static Task AppendAllLinesAsync(FileReference location, IEnumerable<string> contents, CancellationToken cancellationToken = default)` — Appends the contents to a file
- L760 _public method_ `public static Task AppendAllLinesAsync(FileReference location, IEnumerable<string> contents, Encoding encoding, CancellationToken cancellationToken = default)` — Appends the contents to a file
- L767 _public method_ `public static void AppendAllLines(FileReference location, string[] contents)` — Appends the contents to a file
- L775 _public method_ `public static void AppendAllLines(FileReference location, string[] contents, Encoding encoding)` — Appends the contents to a file
- L783 _public method_ `public static Task AppendAllLinesAsync(FileReference location, string[] contents, CancellationToken cancellationToken = default)` — Appends the contents to a file
- L792 _public method_ `public static Task AppendAllLinesAsync(FileReference location, string[] contents, Encoding encoding, CancellationToken cancellationToken = default)` — Appends the contents to a file
- L799 _public method_ `public static void AppendAllText(FileReference location, string contents)` — Appends the contents to a file
- L807 _public method_ `public static void AppendAllText(FileReference location, string contents, Encoding encoding)` — Appends the contents to a file
- L815 _public method_ `public static Task AppendAllTextAsync(FileReference location, string contents, CancellationToken cancellationToken = default)` — Appends the contents to a file
- L824 _public method_ `public static Task AppendAllTextAsync(FileReference location, string contents, Encoding encoding, CancellationToken cancellationToken = default)` — Appends the contents to a file

#### enum `EpicGames.Core.FileReference.Sanitize`  
`public enum Sanitize`  
_public; L29-35_
- desc: Dummy enum to allow invoking the constructor which takes a sanitized full path
- L34 _public* enumerator_ `None` — Dummy value

#### class `EpicGames.Core.FileReferenceTypeConverter`  
`class FileReferenceTypeConverter : TypeConverter`  
_internal*; L832-865_
- inherits: `TypeConverter`
- desc: Type converter to/from strings
- L835-838 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L841-848 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L851-854 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L857-864 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Core.FileReferenceJsonConverter`  
`internal class FileReferenceJsonConverter : JsonConverter<FileReference>`  
_internal; L867-893_
- inherits: `JsonConverter<FileReference>`
- L869-873 _public method_ `public override FileReference? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L875-882 _public method_ `public override FileReference ReadAsPropertyName(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L884-887 _public method_ `public override void Write(Utf8JsonWriter writer, FileReference value, JsonSerializerOptions options)`
- L889-892 _public method_ `public override void WriteAsPropertyName(Utf8JsonWriter writer, [DisallowNull] FileReference value, JsonSerializerOptions options)`

#### class `EpicGames.Core.FileReferenceExtensionMethods`  
`public static class FileReferenceExtensionMethods`  
_public; L898-1017_
- desc: Extension methods for FileReference functionality
- L905 _public method_ `public static void Write(this BinaryWriter writer, FileReference file)` — Manually serialize a file reference to a binary stream.
- L913-930 _public method_ `public static void Write(this BinaryWriter writer, FileReference file, Dictionary<FileReference, int> fileToUniqueId)` — Serializes a file reference, using a lookup table to avoid serializing the same name more than once.
- L937 _public method_ `public static FileReference ReadFileReference(this BinaryReader reader)` — Manually deserialize a file reference from a binary stream.
- L944-948 _public method_ `public static FileReference? ReadFileReferenceOrNull(this BinaryReader reader)` — Manually deserialize a file reference from a binary stream.
- L956 _public method_ `public static FileReference ReadFileReference(this BinaryReader reader, List<FileReference> uniqueFiles)` — Deserializes a file reference, using a lookup table to avoid writing the same name more than once.
- L964-981 _public method_ `public static FileReference? ReadFileReferenceOrNull(this BinaryReader reader, List<FileReference> uniqueFiles)` — Deserializes a file reference, using a lookup table to avoid writing the same name more than once.
- L988-998 _public method_ `public static void WriteFileReference(this BinaryArchiveWriter writer, FileReference? file)` — Writes a FileReference to a binary archive
- L1005 _public method_ `public static FileReference ReadFileReference(this BinaryArchiveReader reader)` — Reads a FileReference from a binary archive
- L1012-1016 _public method_ `public static FileReference? ReadFileReferenceOrNull(this BinaryArchiveReader reader)` — Reads a FileReference from a binary archive

### `Source/Programs/Shared/EpicGames.Core/FileSet.cs` (EpicGames.Core)


#### class `EpicGames.Core.FileSet`  
`public abstract class FileSet : IEnumerable<FileReference>`  
_public; L15-248_
- inherits: `IEnumerable<FileReference>`
- desc: Describes a tree of files represented by some arbitrary type. Allows manipulating files/directories in a functional manner; filtering a view of a certain directory, mapping files from one location to another, etc... before actually realizing those changes on disk.
- L20 _public property_ `public static FileSet Empty { get; }` — An empty fileset
- L25 _public property_ `public string Path { get; }` — Path of this tree
- L31-34 _protected ctor_ `protected FileSet(string path)` — Constructor
- L40 _public method_ `public abstract IEnumerable<KeyValuePair<string, FileReference>> EnumerateFiles()` — Enumerate files in the current tree
- L46 _public method_ `public abstract IEnumerable<KeyValuePair<string, FileSet>> EnumerateDirectories()` — Enumerate subtrees in the current tree
- L54-57 _public method_ `public static FileSet FromFile(DirectoryReference directory, string file)` — Creates a file tree from a given set of files
- L64-67 _public method_ `public static FileSet FromFiles(IEnumerable<(string, FileReference)> files)` — Creates a file tree from a given set of files
- L75-78 _public method_ `public static FileSet FromFile(DirectoryReference directory, FileReference file)` — Creates a file tree from a given set of files
- L85-88 _public method_ `public static FileSet FromFile(FileReference file)` — Creates a file tree from a given file
- L96-99 _public method_ `public static FileSet FromFiles(DirectoryReference directory, IEnumerable<FileReference> files)` — Creates a file tree from a given set of files
- L106-109 _public method_ `public static FileSet FromDirectory(DirectoryReference directory)` — Creates a file tree from a folder on disk
- L116-119 _public method_ `public static FileSet FromDirectory(DirectoryInfo directoryInfo)` — Creates a file tree from a folder on disk
- L126-129 _public method_ `public FileSet Filter(string rules)` — Create a tree containing files filtered by any of the given wildcards
- L136-139 _public method_ `public FileSet Filter(params string[] rules)` — Create a tree containing files filtered by any of the given wildcards
- L146-149 _public method_ `public FileSet Filter(params FileFilter[] filters)` — Create a tree containing files filtered by any of the given file filter objects
- L156-159 _public method_ `public FileSet Except(string filter)` — Create a tree containing the exception of files with another tree
- L166-169 _public method_ `public FileSet Except(params string[] rules)` — Create a tree containing the exception of files with another tree
- L177-180 _public method_ `public static FileSet Union(FileSet lhs, FileSet rhs)` — Create a tree containing the union of files with another tree
- L188-191 _public method_ `public static FileSet Except(FileSet lhs, FileSet rhs)` — Create a tree containing the exception of files with another tree
- L194-197 _public operator_ `public static FileSet operator +(FileSet lhs, FileSet rhs)` — (inheritdoc)
- L200-203 _public operator_ `public static FileSet operator -(FileSet lhs, FileSet rhs)` — (inheritdoc)
- L209-214 _public method_ `public Dictionary<string, FileReference> Flatten()` — Flatten to a map of files in a target directory
- L216-226 _private method_ `private void FlattenInternal(string pathPrefix, Dictionary<string, FileReference> pathToSourceFile)`
- L232-241 _public method_ `public Dictionary<FileReference, FileReference> Flatten(DirectoryReference outputDir)` — Flatten to a map of files in a target directory
- L244 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L247 _public method_ `public IEnumerator<FileReference> GetEnumerator()` — (inheritdoc)

#### class `EpicGames.Core.FileSetFromFiles`  
`class FileSetFromFiles : FileSet`  
_internal*; L253-300_
- inherits: `FileSet`
- desc: File tree from a known set of files
- L255 _private* field_ `readonly Dictionary<string, FileReference> _files = ...`
- L255 _private* field_ `readonly Dictionary< _files = []`
- L256 _private* field_ `readonly Dictionary<string, FileSetFromFiles> _subTrees = ...`
- L256 _private* field_ `readonly Dictionary< _subTrees = []`
- L257 _internal field_ `internal static readonly char[] Separator = ['/', '\\']`
- L263-266 _private ctor_ `private FileSetFromFiles(string path) : base(path)` — Private constructor
- L272-293 _public ctor_ `public FileSetFromFiles(IEnumerable<(string, FileReference)> inputFiles) : this(String.Empty)` — Creates a tree from a given set of files
- L296 _public method_ `public override IEnumerable<KeyValuePair<string, FileReference>> EnumerateFiles()` — (inheritdoc)
- L299 _public method_ `public override IEnumerable<KeyValuePair<string, FileSet>> EnumerateDirectories()` — (inheritdoc)

#### class `EpicGames.Core.FileSetFromDirectory`  
`sealed class FileSetFromDirectory : FileSet`  
_internal*; L305-331_
- inherits: `FileSet`
- desc: File tree enumerated from the contents of an existing directory
- L307 _private* field_ `readonly DirectoryInfo _directoryInfo`
- L312-315 _public ctor_ `public FileSetFromDirectory(DirectoryInfo directoryInfo) : this(directoryInfo, "/")` — Constructor
- L320-324 _public ctor_ `public FileSetFromDirectory(DirectoryInfo directoryInfo, string path) : base(path)` — Constructor
- L327 _public method_ `public override IEnumerable<KeyValuePair<string, FileReference>> EnumerateFiles()` — (inheritdoc)
- L330 _public method_ `public override IEnumerable<KeyValuePair<string, FileSet>> EnumerateDirectories()` — (inheritdoc)

#### class `EpicGames.Core.FileSetFromUnion`  
`class FileSetFromUnion : FileSet`  
_internal*; L336-390_
- inherits: `FileSet`
- desc: File tree enumerated from the combination of two separate trees
- L338 _private* field_ `readonly FileSet _lhs`
- L339 _private* field_ `readonly FileSet _rhs`
- L346-351 _public ctor_ `public FileSetFromUnion(FileSet lhs, FileSet rhs) : base(lhs.Path)` — Constructor
- L354-370 _public method_ `public override IEnumerable<KeyValuePair<string, FileReference>> EnumerateFiles()` — (inheritdoc)
- L373-389 _public method_ `public override IEnumerable<KeyValuePair<string, FileSet>> EnumerateDirectories()` — (inheritdoc)

#### class `EpicGames.Core.FileSetFromExcept`  
`class FileSetFromExcept : FileSet`  
_internal*; L395-436_
- inherits: `FileSet`
- desc: File tree enumerated from the combination of two separate trees
- L397 _private* field_ `readonly FileSet _lhs`
- L398 _private* field_ `readonly FileSet _rhs`
- L405-410 _public ctor_ `public FileSetFromExcept(FileSet lhs, FileSet rhs) : base(lhs.Path)` — Constructor
- L413-417 _public method_ `public override IEnumerable<KeyValuePair<string, FileReference>> EnumerateFiles()` — (inheritdoc)
- L420-435 _public method_ `public override IEnumerable<KeyValuePair<string, FileSet>> EnumerateDirectories()` — (inheritdoc)

#### class `EpicGames.Core.FileSetFromFilter`  
`class FileSetFromFilter : FileSet`  
_internal*; L441-486_
- inherits: `FileSet`
- desc: File tree which includes only those files which match any given filter
- L443 _private* field_ `readonly FileSet _inner`
- L444 _private* field_ `readonly FileFilter[] _filters`
- L451-456 _public ctor_ `public FileSetFromFilter(FileSet inner, params FileFilter[] filters) : base(inner.Path)` — Constructor
- L459-469 _public method_ `public override IEnumerable<KeyValuePair<string, FileReference>> EnumerateFiles()` — (inheritdoc)
- L472-485 _public method_ `public override IEnumerable<KeyValuePair<string, FileSet>> EnumerateDirectories()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/FileSystemReference.cs` (EpicGames.Core)


#### class `EpicGames.Core.FileSystemReference`  
`public abstract class FileSystemReference`  
_public; L16-402_
- attrs: `[Serializable]`
- desc: Base class for file system objects (files or directories).
- L21 _public property_ `public string FullName { get; }` — The path to this object. Stored as an absolute path, with O/S preferred separator characters, and no trailing slash for directories.
- L26 _public property_ `public static StringComparer Comparer { get; }` — The comparer to use for file system references
- L31 _public property_ `public static StringComparison Comparison { get; }` — The comparison to use for file system references
- L36-39 _protected ctor_ `protected FileSystemReference(string fullName)` — Direct constructor for a path
- L42-59 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L70 _private field_ `private int _hashCode` — attrs: `[NonSerialized]` — Lazy initialized hash code
- L76-170 _protected method_ `protected static string CombineStrings(DirectoryReference baseDirectory, params string[] fragments)` — attrs: `[MethodImpl(MethodImplOptions.AggressiveOptimization)]` — Create a full path by concatenating multiple strings
- L177 _public method_ `public bool HasExtension(string extension)` — Checks whether this name has the given extension.
- L186 _public method_ `public bool IsUnderDirectory(DirectoryReference other)` — Determines if the given object is at or under the given directory
- L194 _public method_ `public static bool Exists(FileSystemReference location)` — Checks to see if this exists as either a file or directory This is helpful for Mac, because a binary may be a .app which is a directory
- L202 _public method_ `public bool ContainsName(string name, int offset)` — Searches the path fragments for the given name. Only complete fragments are considered a match.
- L211-249 _public method_ `public bool ContainsName(string name, int offset, int length)` — Searches the path fragments for the given name. Only complete fragments are considered a match.
- L257 _public method_ `public bool ContainsName(string name, DirectoryReference baseDir)` — Determines if the given object is under the given directory, within a subfolder of the given name. Useful for masking out directories by name.
- L265 _public method_ `public bool ContainsAnyNames(IEnumerable<string> names, DirectoryReference baseDir)` — Determines if the given object is under the given directory, within a subfolder of the given name. Useful for masking out directories by name.
- L273-285 _public method_ `public string MakeRelativeTo(DirectoryReference directory)` — attrs: `[MethodImpl(MethodImplOptions.AggressiveOptimization)]` — Creates a relative path from the given base directory
- L294-388 _public method_ `public void MakeRelativeTo(ref StackStringBuilder outBuilder, DirectoryReference directory)` — attrs: `[MethodImpl(MethodImplOptions.AggressiveOptimization)]` — Creates a relative path from the given base directory
- L395 _public method_ `public string ToNormalizedPath()` — Normalize the path to using forward slashes
- L401 _public method_ `public override string ToString()` — Returns a string representation of this filesystem object

### `Source/Programs/Shared/EpicGames.Core/FileTransaction.cs` (EpicGames.Core)


#### class `EpicGames.Core.FileTransaction`  
`public static class FileTransaction`  
_public; L14-139_
- desc: Methods for implementing transactions that replace a files contents, while supporting a fallback path if the operation is interrupted.
- L21-52 _public method_ `public static FileStream? OpenRead(FileReference file)` — Opens a file for reading, recovering from a partial transaction if necessary.
- L59-71 _public method_ `public static byte[]? ReadAllBytes(FileReference file)` — Reads all data from a file into a byte array
- L78-90 _public method_ `public static async Task<byte[]?> ReadAllBytesAsync(FileReference file)` — Reads all data from a file into a byte array
- L97-102 _public method_ `public static FileTransactionStream OpenWrite(FileReference file)` — Opens a file for writing. Call FileTransactionStream.CompleteTransaction on the returned stream to flush its state.
- L110 _public method_ `public static Task WriteAllBytesAsync(FileReference file, ReadOnlyMemory<byte> data, CancellationToken cancellationToken = default)` — Writes data from a byte array into a file, as a transaction
- L118-128 _public method_ `public static async Task WriteAllBytesAsync(FileReference file, ReadOnlySequence<byte> data, CancellationToken cancellationToken = default)` — Writes data from a byte sequence into a file, as a transaction
- L135-138 _private* method_ `static FileReference GetIncomingFile(FileReference file)` — Gets the name of the temp file to use for writing

#### class `EpicGames.Core.FileTransactionStream`  
`public class FileTransactionStream : Stream`  
_public; L144-267_
- inherits: `Stream`
- desc: Stream used to write to a new copy of a file in an atomic transaction
- L146 _private* field_ `readonly Stream _inner`
- L147 _private* field_ `readonly FileReference _file`
- L148 _private* field_ `FileReference? _finalFile`
- L150-155 _internal ctor_ `internal FileTransactionStream(Stream inner, FileReference outputFile, FileReference finalFile)`
- L160-174 _public method_ `public void CompleteTransaction()` — Marks the transaction as complete, and moves the file to its final location
- L177-185 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)
- L188-193 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L196 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L199 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L202 _public property_ `public override bool CanTimeout => ...` — (inheritdoc)
- L205 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L208 _public property_ `public override long Length => ...` — (inheritdoc)
- L211 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L214 _public property_ `public override int ReadTimeout { get; set; }` — (inheritdoc)
- L217 _public property_ `public override int WriteTimeout { get; set; }` — (inheritdoc)
- L220-224 _public method_ `public override void Close()` — (inheritdoc)
- L227 _public method_ `public override void CopyTo(Stream destination, int bufferSize)` — (inheritdoc)
- L230 _public method_ `public override Task CopyToAsync(Stream destination, int bufferSize, CancellationToken cancellationToken)` — (inheritdoc)
- L233 _public method_ `public override void Flush()` — (inheritdoc)
- L236 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L239 _public method_ `public override Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L242 _public method_ `public override ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — (inheritdoc)
- L245 _public method_ `public override int ReadByte()` — (inheritdoc)
- L248 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L251 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L254 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)
- L257 _public method_ `public override void Write(ReadOnlySpan<byte> buffer)` — (inheritdoc)
- L260 _public method_ `public override Task WriteAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L263 _public method_ `public override ValueTask WriteAsync(ReadOnlyMemory<byte> buffer, CancellationToken cancellationToken = default)` — (inheritdoc)
- L266 _public method_ `public override void WriteByte(byte value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/FileUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.WrappedFileOrDirectoryException`  
`public class WrappedFileOrDirectoryException(Exception inner, string message) : Exception(message, inner)`  
_public; L23-27_
- desc: Exception used to represent caught file/directory exceptions.
- L26 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Core.FileLockInfoWin32`  
`public class FileLockInfoWin32( int processId, string? fileName, string appName, DateTime startTime, string? commandLine, int parentProcessId, string? parentFileName, string? parentCommandLine)`  
_public; L40-122_
- desc: Information about a locked file
- L53 _public property_ `public int ProcessId => ...` — Process id
- L58 _public property_ `public string? FileName => ...` — Path to the process holding the lock
- L63 _public property_ `public string AppName => ...` — Name of the application
- L68 _public property_ `public DateTime StartTime => ...` — Time at which the process started
- L73 _public property_ `public string? CommandLine => ...` — Command-line arguments used to start the process (may be null if unavailable)
- L78 _public property_ `public int ParentProcessId => ...` — Parent process id (0 if unavailable or parent has exited)
- L83 _public property_ `public string? ParentFileName => ...` — Path to the parent process (may be null if parent has exited)
- L88 _public property_ `public string? ParentCommandLine => ...` — Parent process command-line (may be null if parent has exited)
- L91-121 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Core.FileUtils`  
`public static class FileUtils`  
_public; L127-1173_
- desc: Utility functions for manipulating files. Where these methods have similar functionality to those in the NET Framework, they generally go the extra mile to produce concise, specific error messages where possible.
- L132 _public property_ `public static IEqualityComparer<string> PlatformPathComparer { get; }` — Comparer that should be used for native path comparisons
- L137 _public property_ `public static IEqualityComparer<Utf8String> PlatformPathComparerUtf8 { get; }` — Utf8 string comparer that should be used for native path comparisons
- L144-162 _public method_ `public static string ReadAllText(FileReference file)` — Read all text for a file
- L169-183 _public method_ `public static FileInfo FindCorrectCase(FileInfo info)` — Finds the on-disk case of a a file
- L189-200 _public method_ `public static void CreateDirectoryTree(DirectoryReference directory)` — Creates a directory tree, with all intermediate branches
- L207-232 _public method_ `public static string? GetFileLockInfo(string fileName)` — Gets information about the processes that have a file locked
- L238-248 _public method_ `public static void ForceDeleteFile(string fileName)` — Deletes a file, whether it's read-only or not
- L254-276 _public method_ `public static void ForceDeleteFile(FileInfo file)` — Deletes a file, whether it's read-only or not
- L282-292 _public method_ `public static void ForceDeleteFile(FileReference location)` — Deletes a file, whether it's read-only or not
- L298-308 _public method_ `public static void ForceDeleteDirectory(string directoryName)` — Deletes a directory and all its contents. Attempts to handle directories with long filenames (> 260 chars) on Windows.
- L314-328 _public method_ `public static void ForceDeleteDirectory(DirectoryInfo directory)` — Deletes a directory and all its contents. Attempts to handle directories with long filenames (> 260 chars) on Windows.
- L334-337 _public method_ `public static void ForceDeleteDirectory(DirectoryReference location)` — Deletes a directory and all its contents. Attempts to handle directories with long filenames (> 260 chars) on Windows.
- L343-357 _private* method_ `static void ForceDeleteDirectoryInternal(DirectoryInfo directory)` — Helper method to delete a directory and throw a WrappedFileOrDirectoryException on failure.
- L363-366 _public method_ `public static void ForceDeleteDirectoryContents(string directory)` — Deletes the contents of a directory, without deleting the directory itself. Attempts to handle directories with long filenames (> 260 chars) on Windows.
- L372-406 _public method_ `public static void ForceDeleteDirectoryContents(DirectoryInfo directory)` — Deletes the contents of a directory, without deleting the directory itself. Attempts to handle directories with long filenames (> 260 chars) on Windows.
- L412-415 _public method_ `public static void ForceDeleteDirectoryContents(DirectoryReference directory)` — Deletes the contents of a directory, without deleting the directory itself. Attempts to handle directories with long filenames (> 260 chars) on Windows.
- L422-425 _public method_ `public static void ForceMoveFile(string sourceFileName, string targetFileName)` — Moves a file from one location to another. Creates the destination directory, and removes read-only files in the target location if necessary.
- L432-473 _public method_ `public static void ForceMoveFile(FileReference sourceLocation, FileReference targetLocation)` — Moves a file from one location to another. Creates the destination directory, and removes read-only files in the target location if necessary.
- L481-512 _public method_ `public static Encoding GetEncoding(ReadOnlySpan<byte> bytes, out int skipBytes)` — Get the encoding of a span and number of bytes to skip at the start of the buffer
- L519 _public method_ `public static Encoding GetEncoding(ReadOnlySpan<byte> bytes)` — Get the encoding of a span
- L527-543 _public method_ `public static Encoding GetEncoding(string filePath, out int skipBytes)` — Get the encoding of a file
- L550 _public method_ `public static Encoding GetEncoding(string filePath)` — Get the encoding of a span
- L557-562 _public method_ `public static int GetFileMode_Mac(string fileName)` — Gets the file mode on Mac
- L569-572 _public method_ `public static void SetFileMode_Mac(string fileName, ushort mode)` — Sets the file mode on Mac
- L579-584 _public method_ `public static int GetFileMode_Linux(string fileName)` — Gets the file mode on Linux
- L591-594 _public method_ `public static void SetFileMode_Linux(string fileName, ushort mode)` — Sets the file mode on Linux
- L616 _private* const_ `const uint FILE_ATTRIBUTE_READONLY = 0x01`
- L617 _private* const_ `const uint FILE_ATTRIBUTE_DIRECTORY = 0x10`
- L618 _private* const_ `const uint FILE_ATTRIBUTE_NORMAL = 0x80`
- L621 _private* method_ `static extern IntPtr FindFirstFileW(string FileName, ref WIN32_FIND_DATA FindData)` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]`
- L625 _private* method_ `static extern bool FindNextFileW(IntPtr FindHandle, ref WIN32_FIND_DATA FindData)` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)] [return: MarshalAs(UnmanagedType.Bool)]`
- L629 _private* method_ `static extern bool FindClose(IntPtr findHandle)` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)] [return: MarshalAs(UnmanagedType.Bool)]`
- L633 _private* method_ `static extern bool DeleteFileW(string lpFileName)` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)] [return: MarshalAs(UnmanagedType.Bool)]`
- L637 _private* method_ `static extern bool RemoveDirectory(string lpPathName)` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)] [return: MarshalAs(UnmanagedType.Bool)]`
- L641 _private* method_ `static extern bool SetFileAttributesW(string lpFileName, uint dwFileAttributes)` — attrs: `[DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)] [return: MarshalAs(UnmanagedType.Bool)]`
- L643 _private* field_ `static readonly IntPtr INVALID_HANDLE_VALUE = new(-1)`
- L645 _private* const_ `const int ERROR_FILE_NOT_FOUND = 2`
- L646 _private* const_ `const int ERROR_PATH_NOT_FOUND = 3`
- L647 _private* const_ `const int ERROR_ACCESS_DENIED = 5`
- L648 _private* const_ `const int ERROR_SHARING_VIOLATION = 32`
- L649 _private* const_ `const int ERROR_DIR_NOT_EMPTY = 145`
- L653-706 _private method_ `private static void ForceDeleteLongDirectoryContentsWin32(string dirName)` — attrs: `[SupportedOSPlatform("windows")]`
- L709-741 _private method_ `private static void ForceDeleteLongDirectoryWin32(string dirName)` — attrs: `[SupportedOSPlatform("windows")]`
- L748-850 _private method_ `private static string? GetDirectoryLockInfo(string dirName)` — attrs: `[SupportedOSPlatform("windows")]` — Enumerates remaining files in a directory after RemoveDirectory fails and gathers lock info. Returns null if no useful diagnostics could be gathered.
- L853 _internal method_ `internal static extern int GetFileAttributesW(string lpFileName)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]`
- L860-893 _public method_ `public static void ForceDeleteFileWin32(string fileName)` — attrs: `[SupportedOSPlatform("windows")]` — Force-delete a file (Windows only)
- L899-909 _private method_ `private static bool TryDeleteFileWin32(string fileName, out int errorCode)` — attrs: `[SupportedOSPlatform("windows")]` — Attempt to delete a file, returning true on success or if the file does not exist.
- L922 _private* field_ `static readonly int RM_SESSION_KEY_LEN = Marshal.SizeOf<Guid>()`
- L923 _private* field_ `static readonly int CCH_RM_SESSION_KEY = RM_SESSION_KEY_LEN * 2`
- L924 _private* const_ `const int CCH_RM_MAX_APP_NAME = 255`
- L925 _private* const_ `const int CCH_RM_MAX_SVC_NAME = 63`
- L958 _private* method_ `static extern int RmRegisterResources(uint pSessionHandle, uint nFiles, string[] rgsFilenames, uint nApplications, [In] RM_UNIQUE_PROCESS[]? rgApplications, uint nServices, string[]? rgsServiceNames)` — attrs: `[DllImport("rstrtmgr.dll", CharSet = CharSet.Unicode)]`
- L962 _private* method_ `static extern int RmStartSession(out uint pSessionHandle, int dwSessionFlags, StringBuilder strSessionKey)` — attrs: `[DllImport("rstrtmgr.dll", CharSet = CharSet.Auto)]`
- L966 _private* method_ `static extern int RmEndSession(uint pSessionHandle)` — attrs: `[DllImport("rstrtmgr.dll")]`
- L969 _private* method_ `static extern int RmGetList(uint dwSessionHandle, out uint pnProcInfoNeeded, ref uint pnProcInfo, [In, Out] RM_PROCESS_INFO[] rgAffectedApps, ref uint lpdwRebootReasons)` — attrs: `[DllImport("rstrtmgr.dll")]`
- L976 _private* method_ `static extern SafeProcessHandle OpenProcess( int processAccess, bool bInheritHandle, int processId )` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L984 _private* method_ `static extern bool GetProcessTimes(SafeProcessHandle hProcess, out FILETIME lpCreationTime, out FILETIME lpExitTime, out FILETIME lpKernelTime, out FILETIME lpUserTime)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L995-1085 _public method_ `public static List<FileLockInfoWin32> GetFileLockInfoWin32(string fileName)` — attrs: `[SupportedOSPlatform("windows")]` — Gets a list of processes that have a handle to the given file open
- L1087-1090 _private method_ `private static long FileTimeToTicks(FILETIME fileTime)`
- L1128 _private* method_ `static extern int stat64(string pathname, stat64_t stat)` — attrs: `[DllImport("libSystem.dylib")]`
- L1131 _private* method_ `static extern int chmod(string path, ushort mode)` — attrs: `[DllImport("libSystem.dylib")]`
- L1165 _private* method_ `static extern int stat64_linux(int ver, string pathname, stat64_linux_t stat)` — attrs: `[DllImport("libc", EntryPoint = "__xstat64")]`
- L1168 _private* method_ `static extern int chmod_linux(string path, ushort mode)` — attrs: `[DllImport("libc", EntryPoint = "chmod")]`

#### struct `EpicGames.Core.FileUtils.WIN32_FIND_DATA`  
`struct WIN32_FIND_DATA`  
_private*; L600-614_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L602 _public field_ `public uint dwFileAttributes`
- L603 _public field_ `public System.Runtime.InteropServices.ComTypes.FILETIME ftCreationTime`
- L604 _public field_ `public System.Runtime.InteropServices.ComTypes.FILETIME ftLastAccessTime`
- L605 _public field_ `public System.Runtime.InteropServices.ComTypes.FILETIME ftLastWriteTime`
- L606 _public field_ `public uint nFileSizeHigh`
- L607 _public field_ `public uint nFileSizeLow`
- L608 _public field_ `public uint dwReserved0`
- L609 _public field_ `public uint dwReserved1`
- L611 _public field_ `public string cFileName` — attrs: `[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]`
- L613 _public field_ `public string cAlternateFileName` — attrs: `[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 14)]`

#### struct `EpicGames.Core.FileUtils.RM_UNIQUE_PROCESS`  
`struct RM_UNIQUE_PROCESS`  
_private*; L916-920_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L918 _public field_ `public int dwProcessId`
- L919 _public field_ `public FILETIME ProcessStartTime`

#### enum `EpicGames.Core.FileUtils.RM_APP_TYPE`  
`enum RM_APP_TYPE`  
_private*; L927-936_
- L929 _public* enumerator_ `RmUnknownApp = 0`
- L930 _public* enumerator_ `RmMainWindow = 1`
- L931 _public* enumerator_ `RmOtherWindow = 2`
- L932 _public* enumerator_ `RmService = 3`
- L933 _public* enumerator_ `RmExplorer = 4`
- L934 _public* enumerator_ `RmConsole = 5`
- L935 _public* enumerator_ `RmCritical = 1000`

#### struct `EpicGames.Core.FileUtils.RM_PROCESS_INFO`  
`struct RM_PROCESS_INFO`  
_private*; L939-955_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L941 _public field_ `public RM_UNIQUE_PROCESS Process`
- L944 _public field_ `public string strAppName` — attrs: `[MarshalAs(UnmanagedType.ByValTStr, SizeConst = CCH_RM_MAX_APP_NAME + 1)]`
- L947 _public field_ `public string strServiceShortName` — attrs: `[MarshalAs(UnmanagedType.ByValTStr, SizeConst = CCH_RM_MAX_SVC_NAME + 1)]`
- L949 _public field_ `public RM_APP_TYPE ApplicationType`
- L950 _public field_ `public uint AppStatus`
- L951 _public field_ `public uint TSSessionId`
- L954 _public field_ `public bool bRestartable` — attrs: `[MarshalAs(UnmanagedType.Bool)]`

#### struct `EpicGames.Core.FileUtils.timespec_t`  
`struct timespec_t`  
_private*; L1097-1101_
- L1099 _public field_ `public ulong tv_sec`
- L1100 _public field_ `public ulong tv_nsec`

#### class `EpicGames.Core.FileUtils.stat64_t`  
`class stat64_t`  
_private*; L1104-1125_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L1106 _public field_ `public uint st_dev`
- L1107 _public field_ `public ushort st_mode`
- L1108 _public field_ `public ushort st_nlink`
- L1109 _public field_ `public ulong st_ino`
- L1110 _public field_ `public uint st_uid`
- L1111 _public field_ `public uint st_gid`
- L1112 _public field_ `public uint st_rdev`
- L1113 _public field_ `public timespec_t st_atimespec`
- L1114 _public field_ `public timespec_t st_mtimespec`
- L1115 _public field_ `public timespec_t st_ctimespec`
- L1116 _public field_ `public timespec_t st_birthtimespec`
- L1117 _public field_ `public ulong st_size`
- L1118 _public field_ `public ulong st_blocks`
- L1119 _public field_ `public uint st_blksize`
- L1120 _public field_ `public uint st_flags`
- L1121 _public field_ `public uint st_gen`
- L1122 _public field_ `public uint st_lspare`
- L1123 _public field_ `public ulong st_qspare1`
- L1124 _public field_ `public ulong st_qspare2`

#### class `EpicGames.Core.FileUtils.stat64_linux_t`  
`class stat64_linux_t`  
_private*; L1142-1161_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L1144 _public field_ `public ulong st_dev`
- L1145 _public field_ `public ulong st_ino`
- L1146 _public field_ `public ulong st_nlink`
- L1147 _public field_ `public uint st_mode`
- L1148 _public field_ `public uint st_uid`
- L1149 _public field_ `public uint st_gid`
- L1150 _public field_ `public int pad0`
- L1151 _public field_ `public ulong st_rdev`
- L1152 _public field_ `public long st_size`
- L1153 _public field_ `public long st_blksize`
- L1154 _public field_ `public long st_blocks`
- L1155 _public field_ `public timespec_t st_atime`
- L1156 _public field_ `public timespec_t st_mtime`
- L1157 _public field_ `public timespec_t st_ctime`
- L1158 _public field_ `public long glibc_reserved0`
- L1159 _public field_ `public long glibc_reserved1`
- L1160 _public field_ `public long glibc_reserved2`

### `Source/Programs/Shared/EpicGames.Core/GuidUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.GuidUtils`  
`public static class GuidUtils`  
_public; L10-75_
- desc: Utility methods for serializing GUIDs in UE format. UE stores GUIDs as 4 x 32-bit LE values, whereas NET stores GUIDs as 1 x 32-bit LE, 2 x 16-bit LE, 8 x 8-bit values.
- L20-42 _public method_ `public static Guid ReadGuidUnrealOrder(ReadOnlySpan<byte> span)` — Reads a GUID serialized in UE order
- L47-74 _public method_ `public static void WriteGuidUnrealOrder(Span<byte> span, Guid guid)` — Reads a GUID serialized in UE order

### `Source/Programs/Shared/EpicGames.Core/HelpUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.HelpUtils`  
`public static class HelpUtils`  
_public; L15-194_
- desc: Utility functions for showing help for objects
- L20 _public property_ `public static int WindowWidth => ...` — Gets the width of the window for formatting purposes
- L27-30 _public method_ `public static void PrintHelp(string title, Type type)` — Prints help for the given object type
- L38-67 _public method_ `public static void PrintHelp(string? title, string? description, List<KeyValuePair<string, string>> parameters)` — Prints help for a command
- L74-86 _public method_ `public static string GetDescription(Type type)` — Gets the description from a type
- L92-95 _public method_ `public static void PrintParagraph(string text)` — Prints a paragraph of text using word wrapping
- L102-109 _public method_ `public static void PrintParagraph(string text, int maxWidth)` — Prints a paragraph of text using word wrapping
- L118-127 _public method_ `public static void PrintTable(List<KeyValuePair<string, string>> items, int indent, int minFirstColumnWidth)` — Prints an argument list to the console
- L137-146 _public method_ `public static void PrintTable(List<KeyValuePair<string, string>> items, int indent, int minFirstColumnWidth, int maxWidth, ILogger logger)` — Prints a table of items to a logging device
- L163-193 _public method_ `public static void FormatTable(IReadOnlyList<KeyValuePair<string, string>> items, int indent, int minFirstColumnWidth, int maxWidth, List<string> lines)` — Formats the given parameters as so: -Param1 Param1 Description -Param2 Param2 Description, this description is longer and splits onto a separate line. -Param3 Param3 Description continues as before.

### `Source/Programs/Shared/EpicGames.Core/HttpClientExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.HttpClientExtensions`  
`public static class HttpClientExtensions`  
_public; L24-178_
- desc: Extension methods for consuming REST APIs via JSON objects
- L34-41 _public method_ `public static async Task<TResponse> GetAsync<TResponse>(this HttpClient client, string url, CancellationToken cancellationToken)` — Gets a resource from an HTTP endpoint and parses it as a JSON object
- L44-51 _public method_ `public static async Task<TResponse> GetAsync<TResponse>(this HttpClient client, Uri url, CancellationToken cancellationToken)` — (inheritdoc)
- L62-66 _public method_ `public static async Task<HttpResponseMessage> PostAsync<TRequest>(this HttpClient client, string url, TRequest request, CancellationToken cancellationToken)` — Posts an object to an HTTP endpoint as a JSON object
- L69-73 _public method_ `public static async Task<HttpResponseMessage> PostAsync<TRequest>(this HttpClient client, Uri url, TRequest request, CancellationToken cancellationToken)` — (inheritdoc)
- L85-92 _public method_ `public static async Task<TResponse> PostAsync<TResponse, TRequest>(this HttpClient client, string url, TRequest request, CancellationToken cancellationToken)` — Posts an object to an HTTP endpoint as a JSON object, and parses the response object
- L95-102 _public method_ `public static async Task<TResponse> PostAsync<TResponse, TRequest>(this HttpClient client, Uri url, TRequest request, CancellationToken cancellationToken)` — (inheritdoc)
- L113-117 _public method_ `public static async Task<HttpResponseMessage> PutAsync<TRequest>(this HttpClient client, string url, TRequest request, CancellationToken cancellationToken)` — Puts an object to an HTTP endpoint as a JSON object
- L120-124 _public method_ `public static async Task<HttpResponseMessage> PutAsync<TRequest>(this HttpClient client, Uri url, TRequest request, CancellationToken cancellationToken)` — (inheritdoc)
- L136-143 _public method_ `public static async Task<TResponse> PutAsync<TResponse, TRequest>(this HttpClient client, string url, TRequest request, CancellationToken cancellationToken)` — Puts an object to an HTTP endpoint as a JSON object, and parses the response object
- L146-153 _public method_ `public static async Task<TResponse> PutAsync<TResponse, TRequest>(this HttpClient client, Uri url, TRequest request, CancellationToken cancellationToken)` — (inheritdoc)
- L161-164 _private method_ `private static StringContent ToJsonContent<T>(T obj)` — Converts an object to a JSON http content object
- L173-177 _private method_ `private static async Task<T> ParseJsonContentAsync<T>(HttpResponseMessage message, CancellationToken cancellationToken)` — Parses a HTTP response as a JSON object

#### class `EpicGames.Core.HttpRequestMessageExtensions`  
`public static class HttpRequestMessageExtensions`  
_public; L183-212_
- desc: Extension methods for HttpRequestMessage
- L185 _private field_ `private static readonly HashSet<string> s_sensitiveKeys = new(StringComparer.OrdinalIgnoreCase) { "x-amz-security-token", "Signature", "AWSAccessKeyId" }`
- L195-211 _public method_ `public static Uri? RedactedRequestUri(this HttpRequestMessage request)` — Returns a new URI with sensitive query parameters redacted from the request URI.

#### class `EpicGames.Core.HttpMessageHandlers`  
`public static class HttpMessageHandlers`  
_public; L217-316_
- desc: Class that can/should be used to Create http message handlers. Under the hood, same handler will be used to reduce redundant dns lookup calls
- L222 _public property_ `public static bool UseIpv6DnsResolving { get; set; }` — Set to false to disable ipv6 dns resolving
- L227-237 _public method_ `public static HttpMessageHandler CreateDefaultHandler()` — Creates default http message handler resolving both ipv4/6 dns.
- L243-246 _public method_ `public static HttpMessageHandler CreateIpv4OnlyHandler()` — Creates a http message handler that only resolves ipv4 dns and skips ipv6 This can be used to prevent long stalls on networks where ipv6 is not supported
- L248-256 _private method_ `private static SocketsHttpHandler InternalCreateDefaultHandler()`
- L258-303 _private method_ `private static SocketsHttpHandler InternalCreateIpv4OnlyHandler()`
- L314 _private field_ `private static readonly Lazy<SocketsHttpHandler> s_defaultHandler = new(InternalCreateDefaultHandler)`
- L315 _private field_ `private static readonly Lazy<SocketsHttpHandler> s_ipv4OnlyHandler = new(InternalCreateIpv4OnlyHandler)`

#### class `EpicGames.Core.HttpMessageHandlers.NonOwningHandler`  
`private sealed class NonOwningHandler : DelegatingHandler`  
_private; L305-312_
- inherits: `DelegatingHandler`
- L307 _public ctor_ `public NonOwningHandler(HttpMessageHandler inner)`
- L310 _protected method_ `protected override void Dispose(bool disposing)`

### `Source/Programs/Shared/EpicGames.Core/IMemoryAllocator.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IMemoryAllocator`  
`public interface IMemoryAllocator<T>`  
_public; L16-25_
- desc: Interface for an explicit memory allocator. Meant for use with large memory blocks, where objects would typically be allocated on the LOH and waiting for GC can cause excessive memory usage.
- L24 _public* method_ `IMemoryOwner<T> Alloc(int minSize, object? tag)` — Allocate a block of memory of the given minimum size

#### class `EpicGames.Core.ManagedHeapAllocator`  
`public class ManagedHeapAllocator : IMemoryAllocator<byte>`  
_public; L31-71_
- inherits: `IMemoryAllocator<byte>`
- desc: Implementation of IMemoryAllocator{Byte} which creates regular arrays on the managed heap. Note that these allocations are subject to GC, and will not be freed immediately.
- L57 _private* field_ `long _allocatedSize`
- L62 _public property_ `public static ManagedHeapAllocator Shared { get; }` — Default shared instance
- L67 _public property_ `public long AllocatedSize => ...` — Currently allocated size using this heap
- L70 _public method_ `public IMemoryOwner<byte> Alloc(int minSize, object? tag)` — (inheritdoc)

#### class `EpicGames.Core.ManagedHeapAllocator.MemoryOwner`  
`class MemoryOwner : IMemoryOwner<byte>`  
_private*; L33-55_
- inherits: `IMemoryOwner<byte>`
- L35 _private* field_ `readonly ManagedHeapAllocator _outer`
- L37 _public property_ `public Memory<byte> Memory { get; set; }`
- L39-44 _public ctor_ `public MemoryOwner(ManagedHeapAllocator outer, int size)`
- L46-54 _public method_ `public void Dispose()`

#### class `EpicGames.Core.PoolAllocator`  
`public class PoolAllocator : IMemoryAllocator<byte>`  
_public; L76-92_
- inherits: `IMemoryAllocator<byte>`
- desc: Implementation of IMemoryAllocator{Byte} which rents blocks from a memory pool.
- L78 _private* field_ `readonly MemoryPool<byte> _pool`
- L83 _public property_ `public static PoolAllocator Shared { get; }` — Shared allocator instance
- L88 _public ctor_ `public PoolAllocator(MemoryPool<byte> pool)` — Constructor
- L91 _public method_ `public IMemoryOwner<byte> Alloc(int minSize, object? tag)` — (inheritdoc)

#### class `EpicGames.Core.GlobalHeapAllocator`  
`public class GlobalHeapAllocator : IMemoryAllocator<byte>`  
_public; L97-154_
- inherits: `IMemoryAllocator<byte>`
- desc: Implementation of IMemoryAllocator{Byte} which returns blocks from the global heap
- L140 _private* field_ `long _allocatedSize`
- L145 _public property_ `public static GlobalHeapAllocator Shared { get; }` — Shared heap allocator
- L150 _public property_ `public long AllocatedSize => ...` — Currently allocated size using this heap
- L153 _public method_ `public IMemoryOwner<byte> Alloc(int minSize, object? tag)` — (inheritdoc)

#### class `EpicGames.Core.GlobalHeapAllocator.Allocation`  
`unsafe class Allocation : MemoryManager<byte>`  
_private*; L99-138_
- inherits: `MemoryManager<byte>`
- L101 _private* field_ `readonly GlobalHeapAllocator _outer`
- L102 _private* field_ `IntPtr _handle`
- L103 _private* field_ `int _length`
- L105-112 _public ctor_ `public Allocation(GlobalHeapAllocator outer, int size)`
- L114 _private* method_ `byte* GetPointer()`
- L117 _public method_ `public override Span<byte> GetSpan()` — (inheritdoc)
- L120 _public method_ `public override MemoryHandle Pin(int elementIndex)` — (inheritdoc)
- L123 _public method_ `public override void Unpin()` — (inheritdoc)
- L126-137 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)

#### class `EpicGames.Core.VirtualMemoryAllocator`  
`public class VirtualMemoryAllocator : IMemoryAllocator<byte>`  
_public; L159-206_
- inherits: `IMemoryAllocator<byte>`
- desc: Implementation of IMemoryAllocator{Byte} which returns memory backed by memory mapped files
- L205 _public method_ `public IMemoryOwner<byte> Alloc(int minSize, object? tag)` — (inheritdoc)

#### class `EpicGames.Core.VirtualMemoryAllocator.Allocation`  
`unsafe class Allocation : MemoryManager<byte>`  
_private*; L161-202_
- inherits: `MemoryManager<byte>`
- L163 _private* field_ `MemoryMappedFile? _file`
- L164 _private* field_ `MemoryMappedViewAccessor? _viewAccessor`
- L165 _private* field_ `byte* _pointer`
- L166 _private* field_ `readonly int _length`
- L168-174 _public ctor_ `public Allocation(int length)`
- L177 _public method_ `public override Span<byte> GetSpan()` — (inheritdoc)
- L180 _public method_ `public override MemoryHandle Pin(int elementIndex)` — (inheritdoc)
- L183 _public method_ `public override void Unpin()` — (inheritdoc)
- L186-201 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)

#### class `EpicGames.Core.TrackingMemoryAllocator`  
`public class TrackingMemoryAllocator : IMemoryAllocator<byte>`  
_public; L211-276_
- inherits: `IMemoryAllocator<byte>`
- desc: Implementation of IMemoryAllocator{Byte} which collects stats on the allocations performed.
- L257 _private* field_ `readonly Lock _lockObject = new()`
- L258 _private* field_ `readonly IMemoryAllocator<byte> _inner`
- L259 _private* field_ `long _allocatedSize`
- L260 _private* field_ `readonly LinkedList<MemoryAllocation> _allocations = new()`
- L265 _public property_ `public long AllocatedSize => ...` — Total size of allocated memory
- L270 _public ctor_ `public TrackingMemoryAllocator(IMemoryAllocator<byte> inner)` — Constructor
- L274 _public method_ `public IMemoryOwner<byte> Alloc(int minSize, object? tag)` — (inheritdoc)

#### class `EpicGames.Core.TrackingMemoryAllocator.MemoryAllocation`  
`sealed class MemoryAllocation : IMemoryOwner<byte>`  
_private*; L214-255_
- inherits: `IMemoryOwner<byte>`
- L216 _private* field_ `readonly TrackingMemoryAllocator _allocator`
- L217 _private* field_ `readonly LinkedListNode<MemoryAllocation> _node`
- L218 _private* field_ `readonly object? _tag`
- L219 _private* field_ `IMemoryOwner<byte> _allocation`
- L221 _public property_ `public Memory<byte> Memory => ...`
- L223-234 _public ctor_ `public MemoryAllocation(TrackingMemoryAllocator allocator, IMemoryOwner<byte> allocation, object? tag)`
- L237-250 _public method_ `public void Dispose()` — (inheritdoc)
- L253 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/IMsBuildRegistration.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IMsBuildRegistration`  
`public interface IMsBuildRegistration`  
_public; L8-20_
- desc: See CsProjBuildHook.
- L14 _public* property_ `DirectoryReference DotnetDirectory { get; }` — The directory of the dotnet install shipped with Unreal Engine.
- L19 _public* property_ `FileReference DotnetPath { get; }` — The dotnet executable that comprises part of the dotnet install shipped with Unreal Engine.

### `Source/Programs/Shared/EpicGames.Core/IReadOnlyMemoryOwner.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IReadOnlyMemoryOwner`  
`public interface IReadOnlyMemoryOwner<T> : IDisposable`  
_public; L11-17_
- inherits: `IDisposable`
- desc: Handle to a shared block of memory with a concrete lifetime
- L16 _public property_ `public ReadOnlyMemory<T> Memory { get; }` — The underlying memory object

#### class `EpicGames.Core.ReadOnlyMemoryOwner`  
`public static class ReadOnlyMemoryOwner`  
_public; L22-123_
- desc: Extension methods for IReadOnlyMemoryOwner{T}
- L48-51 _public method_ `public static IReadOnlyMemoryOwner<T> Create<T>(T[] memory, IDisposable? owner = null)` — Wrap an array as a IReadOnlyMemoryOwner{T}
- L56-59 _public method_ `public static IReadOnlyMemoryOwner<T> Create<T>(ReadOnlyMemory<T> memory, IDisposable? owner = null)` — Wrap a ReadOnlyMemory{T} as a IReadOnlyMemoryOwner{T}
- L85 _public method_ `public static Stream AsStream(this IReadOnlyMemoryOwner<byte> owner)` — Create a stream to wrap a storage object. The object will be disposed when the stream is closed.
- L110-122 _public method_ `public static IReadOnlyMemoryOwner<T> Slice<T>(this IReadOnlyMemoryOwner<T> owner, int offset, int? length)` — Creates a slice of an existing memory object.

#### class `EpicGames.Core.ReadOnlyMemoryOwner.DefaultReadOnlyMemoryOwner`  
`class DefaultReadOnlyMemoryOwner<T> : IReadOnlyMemoryOwner<T>`  
_private*; L24-43_
- inherits: `IReadOnlyMemoryOwner<T>`
- L26 _private* field_ `ReadOnlyMemory<T>? _memory`
- L27 _private* field_ `IDisposable? _owner`
- L29 _public property_ `public ReadOnlyMemory<T> Memory => ...`
- L31-35 _public ctor_ `public DefaultReadOnlyMemoryOwner(ReadOnlyMemory<T> memory, IDisposable? owner)`
- L37-42 _public method_ `public void Dispose()`

#### class `EpicGames.Core.ReadOnlyMemoryOwner.ReadOnlyMemoryOwnerStream`  
`class ReadOnlyMemoryOwnerStream : ReadOnlyMemoryStream`  
_private*; L62-78_
- inherits: `ReadOnlyMemoryStream`
- L64 _private* field_ `readonly IReadOnlyMemoryOwner<byte> _owner`
- L66 _public ctor_ `public ReadOnlyMemoryOwnerStream(IReadOnlyMemoryOwner<byte> owner) : base(owner.Memory)`
- L69-77 _protected method_ `protected override void Dispose(bool disposing)`

#### class `EpicGames.Core.ReadOnlyMemoryOwner.ReadOnlyMemoryOwnerSlice`  
`class ReadOnlyMemoryOwnerSlice<T> : IReadOnlyMemoryOwner<T>`  
_private*; L88-101_
- inherits: `IReadOnlyMemoryOwner<T>`
- L90 _private* field_ `readonly IReadOnlyMemoryOwner<T> _inner`
- L92 _public property_ `public ReadOnlyMemory<T> Memory { get; }`
- L94-98 _public ctor_ `public ReadOnlyMemoryOwnerSlice(IReadOnlyMemoryOwner<T> inner, ReadOnlyMemory<T> memory)`
- L100 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.Core/JsonElementExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.JsonElementExtensions`  
`public static class JsonElementExtensions`  
_public; L13-201_
- desc: Extensions for parsing values out of generic dictionary objects
- L22-26 _public method_ `public static bool HasStringProperty(this JsonElement element, ReadOnlySpan<byte> name, string value)` — Checks if the element has a property with the given value
- L35-39 _public method_ `public static bool HasStringProperty(this JsonElement element, string name, string value)` — Checks if the element has a property with the given value
- L49-62 _public method_ `public static bool TryGetProperty(this JsonElement element, ReadOnlySpan<byte> name, JsonValueKind valueKind, [NotNullWhen(true)] out JsonElement value)` — Gets a property value of a certain type
- L72-85 _public method_ `public static bool TryGetProperty(this JsonElement element, string name, JsonValueKind valueKind, [NotNullWhen(true)] out JsonElement value)` — Gets a property value of a certain type
- L94-107 _public method_ `public static bool TryGetStringProperty(this JsonElement element, ReadOnlySpan<byte> name, [NotNullWhen(true)] out string? value)` — Gets a string property value
- L116-119 _public method_ `public static bool TryGetStringProperty(this JsonElement element, string name, [NotNullWhen(true)] out string? value)` — Gets a string property value
- L128-144 _public method_ `public static bool TryGetNestedProperty(this JsonElement element, ReadOnlySpan<byte> name, [NotNullWhen(true)] out JsonElement outElement)` — Gets a property value from a document or subdocument, indicated with dotted notation
- L153-156 _public method_ `public static bool TryGetNestedProperty(this JsonElement element, string name, [NotNullWhen(true)] out JsonElement outElement)` — Gets a property value from a document or subdocument, indicated with dotted notation
- L165-178 _public method_ `public static bool TryGetNestedProperty(this JsonElement element, string name, out int outValue)` — Gets an int32 value from the document
- L187-200 _public method_ `public static bool TryGetNestedProperty(this JsonElement element, string name, [NotNullWhen(true)] out string? outValue)` — Gets a string value from the document

### `Source/Programs/Shared/EpicGames.Core/JsonExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.JsonExtensions`  
`public static class JsonExtensions`  
_public; L15-219_
- desc: Utility methods for utf8 json reader/writer
- L23-35 _public method_ `public static bool TryReadNextPropertyName(scoped ref Utf8JsonReader reader, out ReadOnlySpan<byte> propertyName)` — Tries to read a property name then move to the value token
- L42-168 _public method_ `public static ReadOnlySpan<byte> GetUtf8String(this Utf8JsonReader reader)` — Reads a Utf8 string from the current json token
- L170-198 _private* method_ `static int GetUtf8Bytes(int c, Span<byte> output)`
- L200-218 _private* method_ `static int GetUtf8ByteCount(int c)`

### `Source/Programs/Shared/EpicGames.Core/JsonKnownTypes.cs` (EpicGames.Core)


#### class `EpicGames.Core.JsonDiscriminatorAttribute`  
`public sealed class JsonDiscriminatorAttribute : Attribute`  
_public; L15-30_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Sets a name used to discriminate between classes derived from a base class
- L20 _public property_ `public string Name { get; }` — Name to use to discriminate between different classes
- L26-29 _public ctor_ `public JsonDiscriminatorAttribute(string name)` — Constructor

#### class `EpicGames.Core.JsonKnownTypesAttribute`  
`public sealed class JsonKnownTypesAttribute : Attribute`  
_public; L36-51_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Marks a class as the base class of a hierarchy, allowing any known subclasses to be serialized for it.
- L41 _public property_ `public Type[] Types { get; }` — Array of derived classes
- L47-50 _public ctor_ `public JsonKnownTypesAttribute(params Type[] types)` — Constructor

#### class `EpicGames.Core.JsonKnownTypesConverter`  
`public class JsonKnownTypesConverter<T> : JsonConverter<T>`  
_public; L56-198_
- inherits: `JsonConverter<T>`
- desc: Serializer for polymorphic objects
- L61 _private* const_ `const string TypePropertyName = "Type"` — Name of the 'Type' field used to store discriminators in the serialized objects
- L66 _private* field_ `readonly Dictionary<string, Type> _discriminatorToType` — Mapping from discriminator to class type
- L66 _private* field_ `readonly Dictionary< _discriminatorToType` — Mapping from discriminator to class type
- L71 _private* field_ `readonly Dictionary<Type, JsonEncodedText> _typeToDiscriminator` — Mapping from class type to discriminator
- L71 _private* field_ `readonly Dictionary< _typeToDiscriminator` — Mapping from class type to discriminator
- L77-93 _public ctor_ `public JsonKnownTypesConverter(IEnumerable<Type> knownTypes)` — Constructor
- L100-103 _public method_ `public override bool CanConvert(Type typeToConvert)` — Determines whether the given type can be converted
- L112-132 _public method_ `public override T Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Reads an object from the given input stream
- L142-165 _private* method_ `static bool TryGetPropertyRespectingCase(JsonElement element, string propertyName, JsonSerializerOptions options, out JsonElement outElement)` — Finds a property within an object, ignoring case
- L173-197 _public method_ `public override void Write(Utf8JsonWriter writer, T value, JsonSerializerOptions options)` — Writes an object to the given output stream

#### class `EpicGames.Core.JsonKnownTypesConverterFactory`  
`public class JsonKnownTypesConverterFactory : JsonConverterFactory`  
_public; L203-228_
- inherits: `JsonConverterFactory`
- desc: Factory for JsonKnownTypes converters
- L210-214 _public method_ `public override bool CanConvert(Type typeToConvert)` — Determines whether it's possible to create a converter for the given type
- L222-227 _public method_ `public override JsonConverter CreateConverter(Type typeToConvert, JsonSerializerOptions options)` — Creates a converter for the given type

### `Source/Programs/Shared/EpicGames.Core/JsonObject.cs` (EpicGames.Core)


#### class `EpicGames.Core.OrderedDictionaryExtensions`  
`public static class OrderedDictionaryExtensions`  
_public; L25-88_
- desc: Extension methods for OrderedDictionary to have functionality more similar to Dictionary.
- L34-43 _public method_ `public static bool TryGetValue(this OrderedDictionary dictionary, object key, [NotNullWhen(true)] out object? value)` — Tries to get a value associated with a key in the OrderedDictionary.
- L45-73 _private method_ `private static object? DeepCopyHelper(object? original)`
- L79-87 _public method_ `public static OrderedDictionary CreateDeepCopy(this OrderedDictionary dictionary)` — Creates a deep copy of all the elements in an OrderedDictionary.

#### class `EpicGames.Core.JsonObject`  
`public class JsonObject`  
_public; L93-966_
- desc: Stores a JSON object in memory
- L95 _private* field_ `readonly OrderedDictionary _rawOrderedObject`
- L100-103 _public ctor_ `public JsonObject()` — Default constructor. Use this to create new JsonObject elements and use the AddOrSetFieldValue API to add values to this JsonObject.
- L110-120 _private ctor_ `private JsonObject(OrderedDictionary inRawObject, bool createCopy)` — Construct a JSON object from the OrderedDictionary obtained from reading a file on disk or parsing valid json text.
- L126-133 _public ctor_ `public JsonObject(JsonElement element)` — Constructor
- L140-165 _public method_ `public override bool Equals(object? obj)` — Override of the Equals method to check for equality between 2 JsonObject instances.
- L171-174 _public method_ `public override int GetHashCode()` — Returns the calculated hash code for a JsonObject instance.
- L181-216 _public method_ `public static object? ParseElement(JsonElement element)` — Parse an individual element
- L218-242 _private method_ `private static SystemJsonNode ToJsonNode(object? obj)`
- L248-256 _public method_ `public SystemJsonObject ToSystemJsonObject()` — Converts a JsonObject instance to a System.Text.Json.Nodes.JsonObject instance. Users can then use .NET facilities like Utf8JsonWriter to interact with this JsonObject.
- L258-289 _private* method_ `static JsonDocument ParseUtf8File(string path)`
- L295-306 _public method_ `public static JsonObject Read(FileReference file)` — Read a JSON file from disk and construct a JsonObject from it
- L314-333 _public method_ `public static bool TryRead(FileReference fileName, [NotNullWhen(true)] out JsonObject? result)` — Tries to read a JSON file from disk
- L340-355 _public method_ `public static JsonObject Parse(string text)` — Parse a JsonObject from the given raw text string
- L363-375 _public method_ `public static bool TryParse(string text, [NotNullWhen(true)] out JsonObject? result)` — Try to parse a JsonObject from the given raw text string
- L380 _public property_ `public IEnumerable<string> KeyNames => ...` — List of key names in this object
- L387-395 _public method_ `public string GetStringField(string fieldName)` — Gets a string field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L403-416 _public method_ `public bool TryGetStringField(string fieldName, [NotNullWhen(true)] out string? result)` — Tries to read a string field by the given name from the object
- L423-431 _public method_ `public string[] GetStringArrayField(string fieldName)` — Gets a string array field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L439-452 _public method_ `public bool TryGetStringArrayField(string fieldName, [NotNullWhen(true)] out string[]? result)` — Tries to read a string array field by the given name from the object
- L459-467 _public method_ `public bool GetBoolField(string fieldName)` — Gets a boolean field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L475-488 _public method_ `public bool TryGetBoolField(string fieldName, out bool result)` — Tries to read a bool field by the given name from the object
- L495-503 _public method_ `public int GetIntegerField(string fieldName)` — Gets an integer field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L511-520 _public method_ `public bool TryGetIntegerField(string fieldName, out int result)` — Tries to read an integer field by the given name from the object
- L528-537 _public method_ `public bool TryGetUnsignedIntegerField(string fieldName, out uint result)` — Tries to read an unsigned integer field by the given name from the object
- L544-552 _public method_ `public double GetDoubleField(string fieldName)` — Gets a double field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L560-569 _public method_ `public bool TryGetDoubleField(string fieldName, out double result)` — Tries to read a double field by the given name from the object
- L576-584 _public method_ `public T GetEnumField<T>(string fieldName) where T : struct` — Gets an enum field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L592-601 _public method_ `public bool TryGetEnumField<T>(string fieldName, out T result) where T : struct` — Tries to read an enum field by the given name from the object
- L610-652 _public method_ `public bool TryGetEnumArrayField<T>(string fieldName, [NotNullWhen(true)] out T[]? result, [NotNullWhen(false)] out string? errors) where T : struct` — Tries to read an enum array field by the given name from the object
- L660 _public method_ `public bool TryGetEnumArrayField<T>(string fieldName, [NotNullWhen(true)] out T[]? result) where T : struct` — Tries to read an enum array field by the given name from the object
- L668-676 _public method_ `public JsonObject GetObjectField(string fieldName)` — Gets an object field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L684-697 _public method_ `public bool TryGetObjectField(string fieldName, [NotNullWhen(true)] out JsonObject? result)` — Tries to read an object field by the given name from the object
- L704-712 _public method_ `public JsonObject[] GetObjectArrayField(string fieldName)` — Gets an object array field by the given name from the object, throwing an exception if it is not there or cannot be parsed.
- L720-733 _public method_ `public bool TryGetObjectArrayField(string fieldName, [NotNullWhen(true)] out JsonObject[]? result)` — Tries to read an object array field by the given name from the object
- L740-743 _public method_ `public bool ContainsField(string fieldName)` — Checks if the provided field exists in this Json object.
- L749-759 _public method_ `public void RemoveField(string fieldName)` — Removes a field from the given json object.
- L766-773 _public method_ `public void AddOrSetFieldValue(string fieldName, int value)` — Sets the integer value of a field if it exists. Otherwise, adds the field and value.
- L780-787 _public method_ `public void AddOrSetFieldValue(string fieldName, uint value)` — Sets the unsigned integer value of a field if it exists. Otherwise, adds the field and value.
- L794-801 _public method_ `public void AddOrSetFieldValue(string fieldName, double value)` — Sets the double value of a field if it exists. Otherwise, adds the field and value.
- L808-815 _public method_ `public void AddOrSetFieldValue(string fieldName, bool value)` — Sets the bool value of a field if it exists. Otherwise, adds the field and value.
- L823-832 _public method_ `public void AddOrSetFieldValue(string fieldName, string? value)` — Sets the string value of a field if it exists. Otherwise, adds the field and value. Note: If a null string is passed in as a value, it will be replaced with an empty string "" instead to ensure the field can still be added or set.
- L839-847 _public method_ `public void AddOrSetFieldValue<T>(string fieldName, T value) where T : Enum` — Sets the enum value of a field if it exists. Otherwise, adds the field and value.
- L854-862 _public method_ `public void AddOrSetFieldValue(string fieldName, JsonObject? value)` — Sets the JsonObject value of a field if it exists. Otherwise, adds the field and value.
- L869-883 _public method_ `public void AddOrSetFieldValue(string fieldName, string?[]? value)` — Sets the string array value of a field if it exists. Otherwise, adds the field and value.
- L890-907 _public method_ `public void AddOrSetFieldValue(string fieldName, JsonObject[]? value)` — Sets the JsonObject array value of a field if it exists. Otherwise, adds the field and value.
- L914-928 _public method_ `public void AddOrSetFieldValue<T>(string fieldName, T[]? value) where T : Enum` — Sets the enum array value of a field if it exists. Otherwise, adds the field and value.
- L935-965 _public method_ `public string ToJsonString()` — Converts this Json Object to a string representation. This follows formatting of UE .uplugin files with 4 spaces for tabs and indentation enabled. IMPORTANT: If this JsonObject contains HTML, the returned string should NOT be used directly for HTML or a script. Read the note below.

### `Source/Programs/Shared/EpicGames.Core/JsonSchema.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IJsonSchemaWriter`  
`public interface IJsonSchemaWriter`  
_public; L13-47_
- desc: Interface used to write JSON schema types. This is abstracted to allow multiple passes over the document structure, in order to optimize multiple references to the same type definition.
- L16 _public* method_ `void WriteStartObject()` — (inheritdoc)
- L19 _public* method_ `void WriteStartObject(string name)` — (inheritdoc)
- L22 _public* method_ `void WriteEndObject()` — (inheritdoc)
- L25 _public* method_ `void WriteStartArray()` — (inheritdoc)
- L28 _public* method_ `void WriteStartArray(string name)` — (inheritdoc)
- L31 _public* method_ `void WriteEndArray()` — (inheritdoc)
- L34 _public* method_ `void WriteBoolean(string name, bool value)` — (inheritdoc)
- L37 _public* method_ `void WriteString(string key, string value)` — (inheritdoc)
- L40 _public* method_ `void WriteStringValue(string name)` — (inheritdoc)
- L46 _public* method_ `void WriteType(JsonSchemaType type)` — Serialize a type to JSON

#### class `EpicGames.Core.JsonSchema`  
`public class JsonSchema`  
_public; L52-296_
- desc: Implementation of a JSON schema. Implements draft 04 (latest supported by Visual Studio 2019).
- L179 _public property_ `public string? Id { get; set; }` — Identifier for the schema
- L184 _public property_ `public JsonSchemaType RootType { get; set; }` — The root schema type
- L191-195 _public ctor_ `public JsonSchema(string? id, JsonSchemaType rootType)` — Constructor
- L201-250 _public method_ `public void Write(Utf8JsonWriter writer)` — Write this schema to a byte array
- L256-262 _public method_ `public void Write(Stream stream)` — Write this schema to a stream
- L268-274 _public method_ `public void Write(FileReference file)` — Writes this schema to a file
- L282-286 _public method_ `public static JsonSchema FromType(Type type, XmlDocReader? xmlDocReader)` — Constructs a Json schema from a type
- L291-295 _public method_ `public static JsonSchema CreateSchema(Type type, XmlDocReader? xmlDocReader)` — Create a Json schema (or retrieve a cached schema)

#### class `EpicGames.Core.JsonSchema.JsonTypeRefCollector`  
`class JsonTypeRefCollector : IJsonSchemaWriter`  
_private*; L54-104_
- inherits: `IJsonSchemaWriter`
- L59 _public property_ `public Dictionary<JsonSchemaType, int> TypeRefCount { get; }` — Reference counts for each type (max of 2)
- L62 _public method_ `public void WriteBoolean(string name, bool value)` — (inheritdoc)
- L65 _public method_ `public void WriteString(string key, string value)` — (inheritdoc)
- L68 _public method_ `public void WriteStringValue(string name)` — (inheritdoc)
- L71 _public method_ `public void WriteStartObject()` — (inheritdoc)
- L74 _public method_ `public void WriteStartObject(string name)` — (inheritdoc)
- L77 _public method_ `public void WriteEndObject()` — (inheritdoc)
- L80 _public method_ `public void WriteStartArray()` — (inheritdoc)
- L83 _public method_ `public void WriteStartArray(string name)` — (inheritdoc)
- L86 _public method_ `public void WriteEndArray()` — (inheritdoc)
- L89-103 _public method_ `public void WriteType(JsonSchemaType type)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchema.JsonSchemaWriter`  
`class JsonSchemaWriter : IJsonSchemaWriter`  
_private*; L109-174_
- inherits: `IJsonSchemaWriter`
- desc: Implementation of IJsonSchemaWriter
- L114 _private* field_ `readonly Utf8JsonWriter _jsonWriter` — Raw Json output
- L119 _private* field_ `readonly Dictionary<JsonSchemaType, string> _typeToDefinition` — Mapping of type to definition name
- L119 _private* field_ `readonly Dictionary< _typeToDefinition` — Mapping of type to definition name
- L126-130 _public ctor_ `public JsonSchemaWriter(Utf8JsonWriter writer, Dictionary<JsonSchemaType, string> typeToDefinition)` — Constructor
- L133 _public method_ `public void WriteBoolean(string name, bool value)` — (inheritdoc)
- L136 _public method_ `public void WriteString(string key, string value)` — (inheritdoc)
- L139 _public method_ `public void WriteStringValue(string name)` — (inheritdoc)
- L142 _public method_ `public void WriteStartObject()` — (inheritdoc)
- L145 _public method_ `public void WriteStartObject(string name)` — (inheritdoc)
- L148 _public method_ `public void WriteEndObject()` — (inheritdoc)
- L151 _public method_ `public void WriteStartArray()` — (inheritdoc)
- L154 _public method_ `public void WriteStartArray(string name)` — (inheritdoc)
- L157 _public method_ `public void WriteEndArray()` — (inheritdoc)
- L163-173 _public method_ `public void WriteType(JsonSchemaType type)` — Writes a type, either inline or as a reference to a definition elsewhere

### `Source/Programs/Shared/EpicGames.Core/JsonSchemaAttributes.cs` (EpicGames.Core)


#### class `EpicGames.Core.JsonSchemaAttribute`  
`public sealed class JsonSchemaAttribute : Attribute`  
_public; L11-26_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute setting the identifier for a schema
- L16 _public property_ `public string Id { get; }` — The schema identifier
- L22-25 _public ctor_ `public JsonSchemaAttribute(string id)` — Constructor

#### class `EpicGames.Core.JsonSchemaCatalogAttribute`  
`public sealed class JsonSchemaCatalogAttribute : Attribute`  
_public; L32-74_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute setting catalog entries for a schema
- L37 _public property_ `public string Name { get; }` — The schema name
- L42 _public property_ `public string Description { get; }` — Description of the schema
- L47 _public property_ `public string[]? FileMatch { get; }` — File patterns to match
- L56-60 _public ctor_ `public JsonSchemaCatalogAttribute(string name, string description, string? fileMatch) : this(name, description, (fileMatch == null) ? (string[]?)null : [fileMatch])` — Constructor
- L68-73 _public ctor_ `public JsonSchemaCatalogAttribute(string name, string description, string[]? fileMatch)` — Constructor

#### class `EpicGames.Core.JsonSchemaTypeAttribute`  
`public abstract class JsonSchemaTypeAttribute : Attribute`  
_public; L79-81_
- inherits: `Attribute`
- desc: Attribute setting properties for a type to be serialized as a string

#### class `EpicGames.Core.JsonSchemaAnyAttribute`  
`public sealed class JsonSchemaAnyAttribute : JsonSchemaTypeAttribute`  
_public; L87-89_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Property)]`
- inherits: `JsonSchemaTypeAttribute`
- desc: Attribute allowing any possible value in a json schema

#### class `EpicGames.Core.JsonSchemaStringAttribute`  
`public sealed class JsonSchemaStringAttribute : JsonSchemaTypeAttribute`  
_public; L95-101_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Property)]`
- inherits: `JsonSchemaTypeAttribute`
- desc: Attribute setting properties for a type to be serialized as a string
- L100 _public property_ `public JsonSchemaStringFormat? Format { get; set; }` — Format of the string

### `Source/Programs/Shared/EpicGames.Core/JsonSchemaFactory.cs` (EpicGames.Core)


#### class `EpicGames.Core.JsonSchemaFactory`  
`public class JsonSchemaFactory`  
_public; L13-223_
- desc: Factory for creating Json schema elements from native properties and types
- L18 _public property_ `public XmlDocReader? XmlDocReader { get; }` — Reader for XML documentation
- L23 _public property_ `public Dictionary<Type, JsonSchemaType> TypeCache { get; }` — Cache of known types
- L28-31 _public ctor_ `public JsonSchemaFactory(XmlDocReader? xmlDocReader)` — Constructor
- L36-40 _public method_ `public JsonSchema CreateSchema(Type type)` — Creates a schema object for the given type
- L45-57 _public method_ `public virtual JsonSchemaType CreateSchemaType(PropertyInfo propertyInfo)` — Constructs a schema type for the given property
- L62-165 _public method_ `public virtual JsonSchemaType CreateSchemaType(Type type)` — Constructs a schema type from the given type object
- L170-182 _protected method_ `protected JsonSchemaEnum CreateEnumSchemaType(Type type)` — Create an enum schema type
- L187-202 _protected method_ `protected void SetOneOfProperties(JsonSchemaOneOf obj, Type type, Type[] knownTypes)` — Set a one-of schema element to the known types
- L207-222 _protected method_ `protected void SetObjectProperties(JsonSchemaObject obj, Type type)` — Fill out the properties for a schema object

### `Source/Programs/Shared/EpicGames.Core/JsonSchemaType.cs` (EpicGames.Core)


#### class `EpicGames.Core.JsonSchemaType`  
`public abstract class JsonSchemaType`  
_public; L11-28_
- desc: Base class for Json schema types
- L16 _public property_ `public string? Name { get; set; }` — Name for this type, if stored in a standalone definition
- L21 _public property_ `public string? Description { get; set; }` — Description of this type
- L27 _public method_ `public abstract void Write(IJsonSchemaWriter writer)` — Write this type to the given archive

#### class `EpicGames.Core.JsonSchemaPrimitiveType`  
`public abstract class JsonSchemaPrimitiveType : JsonSchemaType`  
_public; L33-35_
- inherits: `JsonSchemaType`
- desc: Base class for types that cannot contain references to other types

#### class `EpicGames.Core.JsonSchemaAny`  
`public class JsonSchemaAny : JsonSchemaPrimitiveType`  
_public; L40-46_
- inherits: `JsonSchemaPrimitiveType`
- desc: Represents any type in a Json schema
- L43-45 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchemaBoolean`  
`public class JsonSchemaBoolean : JsonSchemaPrimitiveType`  
_public; L51-58_
- inherits: `JsonSchemaPrimitiveType`
- desc: Represents a boolean in a Json schema
- L54-57 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchemaInteger`  
`public class JsonSchemaInteger : JsonSchemaPrimitiveType`  
_public; L63-70_
- inherits: `JsonSchemaPrimitiveType`
- desc: Represents an integer in a Json schema
- L66-69 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchemaNumber`  
`public class JsonSchemaNumber : JsonSchemaPrimitiveType`  
_public; L75-82_
- inherits: `JsonSchemaPrimitiveType`
- desc: Represents a number of any type in a Json schema
- L78-81 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### enum `EpicGames.Core.JsonSchemaStringFormat`  
`public enum JsonSchemaStringFormat`  
_public; L87-118_
- desc: Format for a string element schema
- L92 _public* enumerator_ `DateTime` — A date/time value
- L97 _public* enumerator_ `Email` — Internet email address, see RFC 5322, section 3.4.1.
- L102 _public* enumerator_ `HostName` — Internet host name, see RFC 1034, section 3.1.
- L107 _public* enumerator_ `Ipv4` — IPv4 address, according to dotted-quad ABNF syntax as defined in RFC 2673, section 3.2.
- L112 _public* enumerator_ `Ipv6` — IPv6 address, as defined in RFC 2373, section 2.2.
- L117 _public* enumerator_ `Uri` — A universal resource identifier (URI), according to RFC3986.

#### class `EpicGames.Core.JsonSchemaString`  
`public class JsonSchemaString : JsonSchemaPrimitiveType`  
_public; L123-161_
- inherits: `JsonSchemaPrimitiveType`
- desc: Represents a string in a Json schema
- L128 _public property_ `public JsonSchemaStringFormat? Format { get; set; }` — Optional string describing the formatting of this type
- L133 _public property_ `public string? Pattern { get; set; }` — Pattern for matched strings
- L140-144 _public ctor_ `public JsonSchemaString(JsonSchemaStringFormat? format = null, string? pattern = null)` — Constructor
- L147-160 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchemaEnum`  
`public class JsonSchemaEnum : JsonSchemaType`  
_public; L166-197_
- inherits: `JsonSchemaType`
- desc: Represents an enum in a Json schema
- L171 _public property_ `public List<string> Values { get; }` — Values for the enum
- L176 _public property_ `public List<string> Descriptions { get; }` — Descriptions for each enum value
- L181-185 _public ctor_ `public JsonSchemaEnum(IEnumerable<string> values, IEnumerable<string> descriptions)` — Constructor
- L188-196 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchemaArray`  
`public class JsonSchemaArray : JsonSchemaType`  
_public; L202-225_
- inherits: `JsonSchemaType`
- desc: Represents an array in a Json schema
- L207 _public property_ `public JsonSchemaType ItemType { get; }` — The type of each element
- L212-215 _public ctor_ `public JsonSchemaArray(JsonSchemaType itemType)` — Constructor
- L218-224 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchemaProperty`  
`public class JsonSchemaProperty`  
_public; L230-276_
- desc: Property within a JsonSchemaObject
- L235 _public property_ `public string Name { get; set; }` — Name of this property
- L240 _public property_ `public string CamelCaseName => ...` — The camelcase name for this property
- L245 _public property_ `public string? Description { get; set; }` — Description of the property
- L250 _public property_ `public JsonSchemaType Type { get; set; }` — The property type
- L255-260 _public ctor_ `public JsonSchemaProperty(string name, string? description, JsonSchemaType type)` — Constructor
- L266-275 _public method_ `public void Write(IJsonSchemaWriter writer)` — Writes a property to a schema

#### class `EpicGames.Core.JsonSchemaObject`  
`public class JsonSchemaObject : JsonSchemaType`  
_public; L281-318_
- inherits: `JsonSchemaType`
- desc: Represents an object in a Json schema
- L286 _public property_ `public List<JsonSchemaProperty> Properties { get; }` — Properties to allow in this object
- L291 _public property_ `public JsonSchemaType? AdditionalProperties { get; set; }` — Type for additional properties
- L294-317 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

#### class `EpicGames.Core.JsonSchemaOneOf`  
`public class JsonSchemaOneOf : JsonSchemaType`  
_public; L323-342_
- inherits: `JsonSchemaType`
- desc: Represents one of a set of object types in a Json schema
- L328 _public property_ `public List<JsonSchemaType> Types { get; }` — List of valid types
- L331-341 _public method_ `public override void Write(IJsonSchemaWriter writer)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/JsonTracer.cs` (EpicGames.Core)


#### class `EpicGames.Core.JsonTracerSpanContext`  
`public class JsonTracerSpanContext : ISpanContext`  
_public; L20-35_
- inherits: `ISpanContext`
- L22-25 _public method_ `public IEnumerable<KeyValuePair<string, string>> GetBaggageItems()`
- L27 _public property_ `public string TraceId { get; }`
- L28 _public property_ `public string SpanId { get; }`
- L30-34 _public ctor_ `public JsonTracerSpanContext(string traceId, string spanId)`

#### class `EpicGames.Core.JsonTracerSpan`  
`public class JsonTracerSpan : ISpan`  
_public; L37-267_
- inherits: `ISpan`
- L42 _private field_ `private static long s_nextIdCounter = 0` — Used to monotonically update ids
- L47 _private field_ `private static readonly string s_processGuidStr = Guid.NewGuid().ToString()` — Unique GUID for this process so IDs are always unique
- L52-55 _private method_ `private static string NextId()` — A simple-as-possible (consecutive for repeatability) id generator.
- L59 _public property_ `public JsonTracerSpanContext Context => ...`
- L61 _private* property_ `ISpanContext ISpan.Context => ...`
- L63 _public property_ `public string OperationName { get; set; }`
- L65 _private field_ `private readonly JsonTracer _tracer`
- L66 _private field_ `private readonly JsonTracerSpanContext _jsonTracerContext`
- L67 _private field_ `private DateTimeOffset _finishTimestamp`
- L68 _private field_ `private bool _finished`
- L69 _private field_ `private readonly Dictionary<string, object> _tags`
- L69 _private field_ `private readonly Dictionary< _tags`
- L70 _private field_ `private readonly List<JsonTracerSpan.Reference> _references`
- L72 _public property_ `public DateTimeOffset StartTimestamp { get; }`
- L73 _public property_ `public Dictionary<string, object> Tags => ...`
- L78-89 _public property_ `public DateTimeOffset FinishTimestamp { get; }` — The finish time of the span; only valid after a call to Finish().
- L97 _public property_ `public string? ParentId { get; }` — The spanId of the span's first OpenTracing.References.ChildOf reference, or the first reference of any type, or null if no reference exists.
- L99 _private field_ `private readonly Lock _lock = new()`
- L101-128 _public ctor_ `public JsonTracerSpan(JsonTracer jsonTracer, string operationName, DateTimeOffset startTimestamp, Dictionary<string, object>? initialTags, List<Reference>? references)`
- L130 _public method_ `public ISpan SetTag(string key, string value)`
- L131 _public method_ `public ISpan SetTag(string key, bool value)`
- L132 _public method_ `public ISpan SetTag(string key, int value)`
- L133 _public method_ `public ISpan SetTag(string key, double value)`
- L135-139 _public method_ `public ISpan SetTag(BooleanTag tag, bool value)`
- L141-145 _public method_ `public ISpan SetTag(IntOrStringTag tag, string value)`
- L147-151 _public method_ `public ISpan SetTag(IntTag tag, int value)`
- L153-157 _public method_ `public ISpan SetTag(StringTag tag, string value)`
- L159-167 _private method_ `private JsonTracerSpan SetObjectTag(string key, object value)`
- L169 _public method_ `public ISpan Log(IEnumerable<KeyValuePair<string, object>> fields)`
- L170 _public method_ `public ISpan Log(DateTimeOffset timestamp, IEnumerable<KeyValuePair<string, object>> fields)`
- L171 _public method_ `public ISpan Log(string message)`
- L172 _public method_ `public ISpan Log(DateTimeOffset timestamp, string message)`
- L174 _public method_ `public ISpan SetBaggageItem(string key, string value)`
- L175 _public method_ `public string GetBaggageItem(string key)`
- L177-182 _public method_ `public ISpan SetOperationName(string operationName)`
- L184-187 _public method_ `public void Finish()`
- L189-198 _public method_ `public void Finish(DateTimeOffset finishTimestamp)`
- L200-218 _private method_ `private static JsonTracerSpanContext? FindPreferredParentRef(IList<Reference> references)`
- L220-226 _private method_ `private void CheckForFinished(string format, params object[] args)`

#### class `EpicGames.Core.JsonTracerSpan.Reference`  
`public sealed class Reference : IEquatable<Reference>`  
_public; L229-266_
- inherits: `IEquatable<Reference>`
- L232 _public property_ `public JsonTracerSpanContext Context { get; }`
- L237 _public property_ `public string ReferenceType { get; }` — See OpenTracing.References.
- L239-243 _public ctor_ `public Reference(JsonTracerSpanContext context, string referenceType)`
- L245-248 _public method_ `public override bool Equals(object? obj)`
- L250-255 _public method_ `public bool Equals(Reference? other)`
- L258-264 _public method_ `public override int GetHashCode()`

#### class `EpicGames.Core.JsonTracerSpanBuilder`  
`public class JsonTracerSpanBuilder : ISpanBuilder`  
_public; L269-400_
- inherits: `ISpanBuilder`
- L271 _private field_ `private readonly JsonTracer _tracer`
- L272 _private field_ `private readonly string _operationName`
- L273 _private field_ `private DateTimeOffset _startTimestamp = DateTimeOffset.MinValue`
- L274 _private field_ `private readonly List<JsonTracerSpan.Reference> _references = []`
- L275 _private field_ `private readonly Dictionary<string, object> _tags = ...`
- L275 _private field_ `private readonly Dictionary< _tags = []`
- L276 _private field_ `private bool _ignoreActiveSpan`
- L278-282 _public ctor_ `public JsonTracerSpanBuilder(JsonTracer tracer, string operationName)`
- L284-292 _public method_ `public ISpanBuilder AsChildOf(ISpanContext? parent)`
- L294-302 _public method_ `public ISpanBuilder AsChildOf(ISpan? parent)`
- L304-312 _public method_ `public ISpanBuilder AddReference(string referenceType, ISpanContext? referencedContext)`
- L314-318 _public method_ `public ISpanBuilder IgnoreActiveSpan()`
- L320-324 _public method_ `public ISpanBuilder WithTag(string key, string value)`
- L326-330 _public method_ `public ISpanBuilder WithTag(string key, bool value)`
- L332-336 _public method_ `public ISpanBuilder WithTag(string key, int value)`
- L338-342 _public method_ `public ISpanBuilder WithTag(string key, double value)`
- L344-348 _public method_ `public ISpanBuilder WithTag(BooleanTag tag, bool value)`
- L350-354 _public method_ `public ISpanBuilder WithTag(IntOrStringTag tag, string value)`
- L356-360 _public method_ `public ISpanBuilder WithTag(IntTag tag, int value)`
- L362-366 _public method_ `public ISpanBuilder WithTag(StringTag tag, string value)`
- L368-372 _public method_ `public ISpanBuilder WithStartTimestamp(DateTimeOffset timestamp)`
- L374-377 _public method_ `public IScope StartActive()`
- L379-383 _public method_ `public IScope StartActive(bool finishSpanOnDispose)`
- L385-399 _public method_ `public ISpan Start()`

#### class `EpicGames.Core.JsonTracer`  
`public class JsonTracer : ITracer`  
_public; L402-514_
- inherits: `ITracer`
- L404 _public property_ `public IScopeManager ScopeManager { get; }`
- L405 _public property_ `public ISpan? ActiveSpan => ...`
- L407 _private field_ `private readonly Lock _lock = new()`
- L408 _private field_ `private readonly List<JsonTracerSpan> _finishedSpans = []`
- L409 _private field_ `private readonly DirectoryReference? _telemetryDir`
- L411-415 _public ctor_ `public JsonTracer(DirectoryReference? telemetryDir = null)`
- L417-427 _public method_ `public static JsonTracer? TryRegisterAsGlobalTracer()`
- L429-432 _public method_ `public ISpanBuilder BuildSpan(string operationName)`
- L434-437 _public method_ `public void Inject<TCarrier>(ISpanContext spanContext, IFormat<TCarrier> format, TCarrier carrier)`
- L439-442 _public method_ `public ISpanContext Extract<TCarrier>(IFormat<TCarrier> format, TCarrier carrier)`
- L444-464 _public method_ `public void Flush()`
- L466-472 _public method_ `public List<JsonTracerSpan> GetFinishedSpans()`
- L474-505 _public method_ `public void GetFinishedSpansAsJson(JsonWriter writer)`
- L507-513 _internal method_ `internal void AppendFinishedSpan(JsonTracerSpan jsonTracerSpan)`

### `Source/Programs/Shared/EpicGames.Core/JsonWriter.cs` (EpicGames.Core)


#### enum `EpicGames.Core.JsonWriterStyle`  
`public enum JsonWriterStyle`  
_public; L14-25_
- desc: Specifies how to format JSON output
- L19 _public* enumerator_ `Compact` — Omit spaces between elements
- L24 _public* enumerator_ `Readable` — Put each value on a newline, and indent output

#### class `EpicGames.Core.JsonWriter`  
`public sealed class JsonWriter : IDisposable`  
_public; L30-433_
- inherits: `IDisposable`
- desc: Writer for JSON data, which indents the output text appropriately, and adds commas and newlines between fields
- L32 _private* field_ `TextWriter _writer`
- L33 _private* field_ `readonly bool _leaveOpen`
- L34 _private* field_ `readonly JsonWriterStyle _style`
- L35 _private* field_ `bool _bRequiresComma`
- L36 _private* field_ `string _indent`
- L43-47 _public ctor_ `public JsonWriter(string fileName, JsonWriterStyle style = JsonWriterStyle.Readable) : this(new StreamWriter(new FileStream(fileName, FileMode.Create, FileAccess.Write, FileShare.Read)))` — Constructor
- L54-58 _public ctor_ `public JsonWriter(FileReference fileName, JsonWriterStyle style = JsonWriterStyle.Readable) : this(new StreamWriter(new FileStream(fileName.FullName, FileMode.Create, FileAccess.Write, FileShare.Read)))` — Constructor
- L66-72 _public ctor_ `public JsonWriter(TextWriter writer, bool leaveOpen = false, JsonWriterStyle style = JsonWriterStyle.Readable)` — Constructor
- L77-84 _public method_ `public void Dispose()` — Dispose of any managed resources
- L86-92 _private method_ `private void IncreaseIndent()`
- L94-100 _private method_ `private void DecreaseIndent()`
- L105-114 _public method_ `public void WriteObjectStart()` — Write the opening brace for an object
- L120-129 _public method_ `public void WriteObjectStart(string objectName)` — Write the name and opening brace for an object
- L134-143 _public method_ `public void WriteObjectEnd()` — Write the closing brace for an object
- L148-156 _public method_ `public void WriteArrayStart()` — Write the opening bracket for an unnamed array
- L162-171 _public method_ `public void WriteArrayStart(string arrayName)` — Write the name and opening bracket for an array
- L176-184 _public method_ `public void WriteArrayEnd()` — Write the closing bracket for an array
- L186-192 _private method_ `private void WriteLine()`
- L194-204 _private method_ `private void WriteLine(string line)`
- L211-219 _public method_ `public void WriteStringArrayField(string name, IEnumerable<string> values)` — Write an array of strings
- L226-229 _public method_ `public void WriteEnumArrayField<T>(string name, IEnumerable<T> values) where T : struct` — Write an array of enum values
- L235-243 _public method_ `public void WriteValue(int value)` — Write a value with no field name, for the contents of an array
- L249-257 _public method_ `public void WriteValue(string value)` — Write a value with no field name, for the contents of an array
- L264-272 _public method_ `public void WriteValue(string name, string? value)` — Write a field name and string value
- L279-282 _public method_ `public void WriteValue(string name, int value)` — Write a field name and integer value
- L289-292 _public method_ `public void WriteValue(string name, uint value)` — Write a field name and unsigned integer value
- L299-302 _public method_ `public void WriteValue(string name, double value)` — Write a field name and double value
- L309-312 _public method_ `public void WriteValue(string name, bool value)` — Write a field name and bool value
- L320-323 _public method_ `public void WriteEnumValue<T>(string name, T value) where T : struct` — Write a field name and enum value
- L325-335 _private* method_ `void WriteCommaNewline()`
- L337-343 _private* method_ `void WriteName(string name)`
- L345-353 _private* method_ `void WriteValueInternal(string name, string value)`
- L355-364 _private* method_ `void WriteEscapedString(string? value)`
- L371-432 _public method_ `public static string EscapeString(string value)` — Escapes a string for serializing to JSON

### `Source/Programs/Shared/EpicGames.Core/ListExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.ListExtensions`  
`public static class ListExtensions`  
_public; L13-122_
- desc: Extension methods for lists
- L22-26 _public method_ `public static void SortBy<TElement, TField>(this List<TElement> list, Func<TElement, TField> selector)` — Sorts a list by a particular field
- L36-39 _public method_ `public static void SortBy<TElement, TField>(this List<TElement> list, Func<TElement, TField> selector, IComparer<TField> comparer)` — Sorts a list by a particular field
- L47-50 _public method_ `public static void AddAll<TElement>(this List<TElement> list, params TElement[] arguments)` — Add all arguments to the list
- L58-61 _public method_ `public static void AddDefinition(this List<string> list, string definitionName, string value)` — Add to a list of definitions with the form of "Name=Value".
- L69-72 _public method_ `public static void AddDefinition(this List<string> list, string definitionName, bool bValue)` — Add to a list of definitions with the form of "Name=Value" where Value is 1 or 0 based on bValue.
- L80-83 _public method_ `public static void AddDefinition(this List<string> list, string definitionName, int value)` — Add to a list of definitions with the form of "Name=Value".
- L92-96 _public method_ `public static List<TOutput> ConvertAll<TInput, TOutput>(this List<TInput> input) where TInput : TOutput` — Convert all elements of a list to a base type
- L105-108 _public method_ `public static async Task<List<TOutput>> ConvertAllAsync<TInput, TOutput>(this Task<List<TInput>> input) where TInput : TOutput` — Convert all elements of a list to a base type
- L118-121 _public method_ `public static async Task<List<TOutput>> ConvertAllAsync<TInput, TOutput>(this Task<List<TInput>> input, Converter<TInput, TOutput> converter)` — Convert all elements of a list to a base type

### `Source/Programs/Shared/EpicGames.Core/ListSegment.cs` (EpicGames.Core)


#### class `EpicGames.Core.ListSegment`  
`public static class ListSegment`  
_public; L14-20_
- desc: Static methods for ListSegment{T}
- L19 _public method_ `public static ListSegment<T> Empty<T>()` — An empty list segment of the given element type

#### struct `EpicGames.Core.ListSegment`  
`public readonly struct ListSegment<T> : IEnumerable<T>, IEnumerable, IReadOnlyCollection<T>, IReadOnlyList<T>`  
_public; L26-215_
- inherits: `IEnumerable<T>, IEnumerable, IReadOnlyCollection<T>, IReadOnlyList<T>`
- desc: Delimits a section of a list
- L32 _public property_ `public IList<T> List { get; }` — Gets the original array containing the range of elements that the list segment delimits.
- L38 _public property_ `public int Offset { get; }` — Gets the position of the first element in the range delimited by the list segment, relative to the start of the original list.
- L43 _public property_ `public int Count { get; }` — Gets the number of elements in the range delimited by the array segment.
- L46 _public property_ `public bool IsReadOnly => ...` — (inheritdoc)
- L52-57 _public ctor_ `public ListSegment(IList<T> list)` — Initializes a new instance of the System.ArraySegment`1 structure that delimits all the elements in the specified array.
- L65-79 _public ctor_ `public ListSegment(IList<T> list, int offset, int length)`
- L85-96 _public method_ `public ListSegment<T> Slice(int offset)` — Create a new slice of this list segment
- L103-122 _public method_ `public ListSegment<T> Slice(int offset, int count)` — Create a new slice of this list segment
- L130-148 _public indexer_ `public T this[int index] { get; set; }`
- L154-157 _public operator_ `public static implicit operator ListSegment<T>(List<T> list)`
- L211 _public method_ `public IEnumerator<T> GetEnumerator()` — (inheritdoc)
- L214 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

#### struct `EpicGames.Core.ListSegment.Enumerator`  
`struct Enumerator : IEnumerator<T>, IEnumerator`  
_private*; L162-208_
- inherits: `IEnumerator<T>, IEnumerator`
- desc: Enumerator implementation
- L164 _private* field_ `readonly IList<T> _list`
- L165 _private* field_ `int _index`
- L166 _private* field_ `readonly int _maxIndex`
- L169-179 _public property_ `public readonly T Current { get; }` — (inheritdoc)
- L185-190 _public ctor_ `public Enumerator(ListSegment<T> segment)` — Constructor
- L193-195 _private* method_ `readonly void IDisposable.Dispose()` — (inheritdoc)
- L198-201 _public method_ `public bool MoveNext()` — (inheritdoc)
- L204 _private* property_ `readonly object? IEnumerator.Current => ...` — (inheritdoc)
- L207 _private* method_ `void IEnumerator.Reset()` — (inheritdoc)

#### class `EpicGames.Core.ListSegmentExtensions`  
`public static class ListSegmentExtensions`  
_public; L220-295_
- desc: Extension method to slice a list
- L228-231 _public method_ `public static ListSegment<T> AsSegment<T>(this IList<T> list)` — Create a fixed size list segment
- L240-243 _public method_ `public static ListSegment<T> AsSegment<T>(this IList<T> list, int offset)` — Create a fixed size list segment
- L253-256 _public method_ `public static ListSegment<T> AsSegment<T>(this IList<T> list, int offset, int length)` — Create a fixed size list segment
- L265-269 _public method_ `public static ListSegment<T> AsSegment<T>(this IList<T> list, Range range)` — Create a fixed size list segment
- L278-281 _public method_ `public static ListSegment<T> Slice<T>(this List<T> list, int offset)` — Take a slice from a list
- L291-294 _public method_ `public static ListSegment<T> Slice<T>(this List<T> list, int offset, int length)` — Take a slice from a list

### `Source/Programs/Shared/EpicGames.Core/Logging/DefaultConsoleLogger.cs` (EpicGames.Core)


#### class `EpicGames.Core.DefaultConsoleLogger`  
`public class DefaultConsoleLogger : ILogger`  
_public; L14-205_
- inherits: `ILogger`
- desc: Simple implementation of ILogger which formats output to the console similar to Serilog's 'Code' style.
- L21 _private* const_ `const string AnsiReset = "\x1b[0m"`
- L23 _private* const_ `const string AnsiTime = "\x1b[38;5;0246m"`
- L25 _private* const_ `const string AnsiTrace = "\x1b[37m"`
- L26 _private* const_ `const string AnsiDebug = "\x1b[37m"`
- L27 _private* const_ `const string AnsiInformation = "\x1b[37;1m"`
- L28 _private* const_ `const string AnsiWarning = "\x1b[38;5;0229m"`
- L29 _private* const_ `const string AnsiError = "\x1b[38;5;0197m\x1b[48;5;0238m"`
- L31 _private* const_ `const string AnsiNull = "\x1b[38;5;0038m"`
- L32 _private* const_ `const string AnsiBool = "\x1b[38;5;0038m"`
- L33 _private* const_ `const string AnsiNumber = "\x1b[38;5;151m"`
- L34 _private* const_ `const string AnsiString = "\x1b[38;5;0216m"`
- L36 _private* field_ `readonly LogLevel _minLevel`
- L42-45 _public ctor_ `public DefaultConsoleLogger(LogLevel minLevel = LogLevel.Debug)` — Constructor
- L48 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L51 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L54-59 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)
- L61-115 _private* method_ `static void Write<TState>(LogLevel logLevel, TState state, Exception? exception, Func<TState, Exception?, string> formatter, TextWriter textWriter)`
- L117-192 _private* method_ `static ReadOnlySpan<char> WriteToken(ReadOnlySpan<char> fmt, IEnumerable<KeyValuePair<string, object>> properties, TextWriter writer)`
- L194-204 _private* method_ `static object? GetPropertyValue(IEnumerable<KeyValuePair<string, object>> enumerable, ReadOnlySpan<char> name)`

#### class `EpicGames.Core.DefaultConsoleLogger.Disposable`  
`sealed class Disposable : IDisposable`  
_private*; L16-19_
- inherits: `IDisposable`
- L18 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.Core/Logging/ForwardingLogger.cs` (EpicGames.Core)


#### class `EpicGames.Core.ForwardingLogger`  
`public class ForwardingLogger : ILogger`  
_public; L12-82_
- inherits: `ILogger`
- desc: Logger which forwards output to several other loggers
- L32-35 _public property_ `public IReadOnlyList<ILogger> Loggers { get; }` — The loggers that are being written to
- L41-44 _public ctor_ `public ForwardingLogger(params ILogger[] loggers)` — Constructor
- L47-59 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L62-72 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L75-81 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)

#### class `EpicGames.Core.ForwardingLogger.DisposableList`  
`class DisposableList : List<IDisposable>, IDisposable`  
_private*; L17-27_
- inherits: `List<IDisposable>, IDisposable`
- desc: List of IDisposable instances
- L20-26 _public method_ `public void Dispose()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/Logging/ILogCursor.cs` (EpicGames.Core)


#### interface `EpicGames.Core.ILogCursor`  
`public interface ILogCursor`  
_public; L12-47_
- desc: Allows querying the input text from the current cursor position
- L17-20 _public* property_ `string? CurrentLine { get; }` — Text for the current line
- L25-28 _public* property_ `int CurrentLineNumber { get; }` — The current line number
- L33-36 _public* property_ `int Length { get; }` — Returns the line count
- L43-46 _public* indexer_ `string? this[int offset] { get; }` — Index to find the string at the given offset

#### class `EpicGames.Core.LogCursorExtensions`  
`public static partial class LogCursorExtensions`  
_public; L52-350_
- desc: Extension methods for log cursors
- L80-83 _public method_ `public static ILogCursor Rebase(this ILogCursor cursor, int offset)` — Creates a new log cursor based at an offset from the current line
- L92-96 _public method_ `public static bool TryGetLine(this ILogCursor cursor, int offset, [NotNullWhen(true)] out string? nextLine)` — Attempts to get a line at the given offset
- L104 _public method_ `public static bool Contains(this ILogCursor cursor, string text)` — Tests whether the current line contains the given text
- L113-117 _public method_ `public static bool Contains(this ILogCursor cursor, int offset, string text)` — Tests whether the current line contains the given text
- L125 _public method_ `public static bool StartsWith(this ILogCursor cursor, string text)` — Tests whether the current line starts with the given text
- L134-138 _public method_ `public static bool StartsWith(this ILogCursor cursor, int offset, string text)` — Tests whether the current line starts with the given text
- L146-149 _public method_ `public static bool IsMatch(this ILogCursor cursor, Regex pattern)` — Determines if the current line matches the given regex
- L158-162 _public method_ `public static bool IsMatch(this ILogCursor cursor, int offset, Regex pattern)` — Determines if the line at the given offset matches the given regex
- L171-174 _public method_ `public static bool TryMatch(this ILogCursor cursor, Regex pattern, [NotNullWhen(true)] out Match? outMatch)` — Determines if the current line matches the given regex
- L184-202 _public method_ `public static bool TryMatch(this ILogCursor cursor, int offset, Regex pattern, [NotNullWhen(true)] out Match? outMatch)` — Determines if the line at the given offset matches the given regex
- L211-218 _public method_ `public static int MatchForwards(this ILogCursor cursor, int offset, Regex pattern)` — Matches lines forward from the given offset while the given pattern matches
- L227-238 _public method_ `public static int MatchForwardsUntil(this ILogCursor cursor, int offset, Regex pattern)` — Matches lines forwards from the given offset until the given pattern matches
- L248-267 _public method_ `public static int MatchForwardsLimited(this ILogCursor cursor, int offset, Regex pattern, int maxLines)` — Matches lines forwards from the given offset until the given pattern matches
- L275-291 _public method_ `public static bool IsBlank(this ILogCursor cursor, int offset)` — Tests if a line consists only of whitespace
- L300-320 _public method_ `public static bool IsAligned(this ILogCursor cursor, int offset, string? firstLine)` — Check if a line at a given offset is left-aligned with at least this indent of another line
- L329-349 _public method_ `public static bool IsHanging(this ILogCursor cursor, int offset, string? firstLine)` — Check if a line at a given offset is left-aligned with at least this indent of another line

#### class `EpicGames.Core.LogCursorExtensions.RebasedLogCursor`  
`class RebasedLogCursor : ILogCursor`  
_private*; L57-72_
- inherits: `ILogCursor`
- desc: Implementation of ILogCursor which positions the cursor at a fixed offset from the inner cursor
- L59 _private* field_ `readonly ILogCursor _inner`
- L60 _private* field_ `readonly int _baseLineNumber`
- L62-66 _public ctor_ `public RebasedLogCursor(ILogCursor inner, int baseLineNumber)`
- L68 _public indexer_ `public string? this[int index]`
- L69 _public property_ `public string? CurrentLine => ...`
- L70 _public property_ `public int CurrentLineNumber => ...`
- L71 _public property_ `public int Length => ...`

### `Source/Programs/Shared/EpicGames.Core/Logging/ILoggerIndent.cs` (EpicGames.Core)


#### interface `EpicGames.Core.ILoggerIndent`  
`public interface ILoggerIndent`  
_public; L14-20_
- desc: Class to apply a log indent for the lifetime of an object
- L19 _public* property_ `string Indent { get; }` — The indent to apply

#### class `EpicGames.Core.DefaultLoggerIndentHandler`  
`public class DefaultLoggerIndentHandler : ILogger`  
_public; L25-204_
- inherits: `ILogger`
- desc: Wrapper class for ILogger classes which supports LoggerStatusScope
- L143 _private* field_ `readonly ILogger _inner` — The internal logger
- L148 _private* field_ `readonly List<Scope> _scopes = []` — Current list of indents
- L153 _public property_ `public ILogger Inner => ...` — The inner logger
- L158-162 _public property_ `public string Indent { get; set; }` — The current indent text
- L168-172 _public ctor_ `public DefaultLoggerIndentHandler(ILogger inner)` — Constructor
- L175-184 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L187-190 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L193-203 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)

#### class `EpicGames.Core.DefaultLoggerIndentHandler.Scope`  
`class Scope : IDisposable`  
_private*; L30-66_
- inherits: `IDisposable`
- desc: Scoped indent message
- L35 _private* field_ `readonly DefaultLoggerIndentHandler _owner` — Owning object
- L40 _public property_ `public ILoggerIndent Indent { get; }` — The indent scope object
- L45-54 _public ctor_ `public Scope(DefaultLoggerIndentHandler owner, ILoggerIndent indent)` — Constructor
- L59-65 _public method_ `public void Dispose()` — Remove this indent from the list

#### struct `EpicGames.Core.DefaultLoggerIndentHandler.FormattedLogValues`  
`readonly struct FormattedLogValues<TState> : IEnumerable<KeyValuePair<string, object>>`  
_private*; L72-138_
- inherits: `IEnumerable<KeyValuePair<string, object>>`
- desc: Struct to wrap a formatted set of log values with applied indent
- L77 _private* field_ `readonly string _indent` — The indent to apply
- L82 _private* field_ `readonly TState _state` — The inner state
- L87 _private* field_ `readonly Func<TState, Exception?, string> _formatter` — Formatter for the inner state
- L87 _private* field_ `readonly Func< Exception` — Formatter for the inner state
- L87 _private* field_ `readonly Func< _formatter` — Formatter for the inner state
- L95-100 _public ctor_ `public FormattedLogValues(string indent, TState state, Func<TState, Exception?, string> formatter)` — Constructor
- L103-120 _public method_ `public IEnumerator<KeyValuePair<string, object>> GetEnumerator()` — (inheritdoc)
- L123-126 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L134-137 _public method_ `public static string Format(FormattedLogValues<TState> values, Exception? exception)` — Formats an instance of this object

#### class `EpicGames.Core.LoggerIndentExtensions`  
`public static class LoggerIndentExtensions`  
_public; L209-241_
- desc: Extension methods for creating an indent
- L237-240 _public method_ `public static IDisposable? BeginIndentScope(this ILogger logger, string indent)` — Create an indent

#### class `EpicGames.Core.LoggerIndentExtensions.LoggerIndent`  
`class LoggerIndent : ILoggerIndent`  
_private*; L214-229_
- inherits: `ILoggerIndent`
- desc: Class to apply a log indent for the lifetime of an object
- L219 _public property_ `public string Indent { get; }` — The previous indent
- L225-228 _public ctor_ `public LoggerIndent(string indent)` — Constructor

### `Source/Programs/Shared/EpicGames.Core/Logging/ILoggerProgress.cs` (EpicGames.Core)


#### interface `EpicGames.Core.ILoggerProgress`  
`public interface ILoggerProgress : IDisposable`  
_public; L12-29_
- inherits: `IDisposable`
- desc: Manages a status message for a long running operation, which can be updated with progress. Typically transient on consoles, and written to the same line.
- L17-20 _public* property_ `string Message { get; }` — Prefix message for the status
- L25-28 _public* property_ `string Progress { get; set; }` — The current

#### class `EpicGames.Core.LoggerProgressExtensions`  
`public static class LoggerProgressExtensions`  
_public; L34-138_
- desc: Extension methods for status objects
- L134-137 _public method_ `public static ILoggerProgress BeginProgressScope(this ILogger logger, string message)` — Begins a new progress scope

#### class `EpicGames.Core.LoggerProgressExtensions.LoggerProgress`  
`class LoggerProgress : ILoggerProgress`  
_private*; L39-126_
- inherits: `ILoggerProgress`
- desc: Concrete implementation of ILoggerProgress
- L44 _private field_ `private readonly ILogger _logger` — The logger to output to
- L49-52 _public property_ `public string Message { get; }` — Prefix message for the status
- L57-71 _public property_ `public string Progress { get; set; }` — The current
- L76 _private* field_ `string _lastOutput = String.Empty` — The last string that was output
- L81 _private* field_ `string _progressInternal = String.Empty` — Backing storage for the Progress string
- L86 _private* field_ `readonly Stopwatch _timer = Stopwatch.StartNew()` — Timer since the last update
- L93-100 _public ctor_ `public LoggerProgress(ILogger logger, string message)` — Constructor
- L105-108 _public method_ `public void Dispose()` — Dispose of this object
- L113-125 _private* method_ `void Flush()` — Flushes the current output to the log

### `Source/Programs/Shared/EpicGames.Core/Logging/ILoggerProperty.cs` (EpicGames.Core)


#### class `EpicGames.Core.LoggerPropertyExtensions`  
`public static class LoggerPropertyExtensions`  
_public; L12-78_
- desc: Extension methods for more convenient attaching of properties to log messages
- L72-77 _public method_ `public static LogScopedPropertyBuilder WithProperty(this ILogger logger, string key, object value)` — Creates a new log scope and attaches a key/value property Additional properties can be added with LogScopedPropertyBuilder.WithProperty.

#### struct `EpicGames.Core.LoggerPropertyExtensions.LogScopedPropertyBuilder`  
`public readonly struct LogScopedPropertyBuilder`  
_public; L18-53_
- desc: Builder struct for attaching properties to log messages Wraps and disposes log scope.
- L20 _private field_ `private readonly Dictionary<string, object> _properties`
- L20 _private field_ `private readonly Dictionary< _properties`
- L21 _private field_ `private readonly ILogger _logger`
- L27-31 _public ctor_ `public LogScopedPropertyBuilder(ILogger logger)` — Constructor
- L39-43 _public method_ `public LogScopedPropertyBuilder WithProperty(string key, object value)` — Set a key/value property for current log scope
- L49-52 _public method_ `public IDisposable? BeginScope()` — Starts new scope on underlying logger, passing previously set properties

### `Source/Programs/Shared/EpicGames.Core/Logging/JsonLogEvent.cs` (EpicGames.Core)


#### struct `EpicGames.Core.JsonLogEvent`  
`public readonly struct JsonLogEvent : IEnumerable<KeyValuePair<string, object?>>`  
_public; L15-412_
- inherits: `IEnumerable<KeyValuePair<string, object?>>`
- desc: Defines a preformatted Json log event, which can pass through raw Json data directly or format it as a regular string
- L20 _public property_ `public LogLevel Level { get; }` — The log level
- L25 _public property_ `public EventId EventId { get; }` — The event id, if set
- L30 _public property_ `public int LineIndex { get; }` — Index of this line
- L35 _public property_ `public int LineCount { get; }` — Number of lines in a multi-line message
- L40 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — The utf-8 encoded JSON event
- L45-48 _public ctor_ `public JsonLogEvent(LogEvent logEvent) : this(logEvent.Level, logEvent.Id, logEvent.LineIndex, logEvent.LineCount, logEvent.ToJsonBytes())` — Constructor
- L53-60 _public ctor_ `public JsonLogEvent(LogLevel level, EventId eventId, int lineIndex, int lineCount, ReadOnlyMemory<byte> data)` — Constructor
- L66-75 _public method_ `public static JsonLogEvent FromLoggerState<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — Creates a json log event from the given logger parameters
- L82-90 _public method_ `public static JsonLogEvent Parse(ReadOnlyMemory<byte> data)` — Parse an event from the given data
- L98-109 _public method_ `public static bool TryParse(ReadOnlyMemory<byte> data, out JsonLogEvent logEvent)` — Tries to parse a Json log event from the given string
- L117-121 _public method_ `public static bool TryParse(string text, out JsonLogEvent logEvent)` — Tries to parse a Json log event from the given string
- L123-190 _private* method_ `static bool TryParseInternal(ReadOnlyMemory<byte> data, out JsonLogEvent logEvent)`
- L192 _private* field_ `static readonly sbyte[] s_firstCharToLogLevel`
- L193 _private* field_ `static readonly byte[][] s_logLevelNames`
- L196-211 _private* ctor_ `static JsonLogEvent()`
- L213-221 _private* method_ `static LogLevel ParseLevel(ReadOnlySpan<byte> level)`
- L223 _private* field_ `static readonly Utf8String s_newlineEscaped = new("\\n")`
- L228-247 _public method_ `public Utf8String GetRenderedMessage()` — Gets the rendered message from the event data
- L253-295 _public method_ `public string GetLegacyLogLine()` — Gets the event data rendered as a legacy unreal log line of the format: [timestamp][frame number]LogChannel: LogVerbosity: Message
- L301-323 _public method_ `public int GetMessageLineCount()` — Count the number of lines in the message field of a log event
- L330-345 _private* method_ `static int CountLines(ReadOnlySpan<byte> str)` — Counts the number of newlines in an escaped JSON string
- L353-357 _public method_ `public static string Format(JsonLogEvent state, Exception? ex)` — Formats an event as a string
- L364-368 _public method_ `public IEnumerable<JsonProperty> FindPropertiesOfType(Utf8String type)` — Find all properties of the given type in a particular log line
- L376-402 _public method_ `public static IEnumerable<JsonProperty> FindPropertiesOfType(JsonElement line, Utf8String type)` — Find all properties of the given type in a particular log line
- L405 _public method_ `public override string ToString()` — (inheritdoc)
- L408 _public method_ `public IEnumerator<KeyValuePair<string, object?>> GetEnumerator()` — (inheritdoc)
- L411 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

#### class `EpicGames.Core.JsonLogEventExtensions`  
`public static class JsonLogEventExtensions`  
_public; L417-428_
- desc: Extension methods for JsonLogEvent
- L424-427 _public method_ `public static void LogJsonLogEvent(this ILogger logger, JsonLogEvent jsonLogEvent)` — Logs a JsonLogEvent to the given logger

### `Source/Programs/Shared/EpicGames.Core/Logging/KnownLogEvents.cs` (EpicGames.Core)


#### class `EpicGames.Core.KnownLogEvents`  
`public static class KnownLogEvents`  
_public; L11-433_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Naming", "CA1707:Identifiers should not contain underscores", Justification = "Intentional")]`
- desc: Well known log events
- L16 _public property_ `public static EventId None { get; }` — Unset
- L21 _public property_ `public static EventId Generic { get; }` — Generic error
- L26 _public property_ `public static EventId Exception { get; }` — Generic exception
- L31 _public property_ `public static EventId ExitCode { get; }` — Exit code error
- L36 _public property_ `public static EventId Compiler { get; }` — Compiler error
- L41 _public property_ `public static EventId Compiler_Summary { get; }` — Compiler summary line (eg. 'XYZ failed to compile')
- L46 _public property_ `public static EventId RulesAssembly { get; }` — TargetRules or ModuleRules error
- L51 _public property_ `public static EventId Validation { get; }` — Validation messages
- L56 _public property_ `public static EventId CircularDependency { get; }` — Circular dependency messages
- L61 _public property_ `public static EventId UHT { get; }` — UHT compiler message
- L66 _public property_ `public static EventId UBA { get; }` — UBA message
- L71 _public property_ `public static EventId Linker { get; }` — Linker error
- L76 _public property_ `public static EventId Linker_UndefinedSymbol { get; }` — Linker: Undefined symbol
- L81 _public property_ `public static EventId Linker_DuplicateSymbol { get; }` — Linker: Multiply defined symbol
- L86 _public property_ `public static EventId Engine { get; }` — Engine error
- L91 _public property_ `public static EventId Engine_LogChannel { get; }` — Engine log channel
- L96 _public property_ `public static EventId Engine_Crash { get; }` — Engine: Crash dump
- L101 _public property_ `public static EventId Engine_AssetLog { get; }` — Engine: UE_ASSET_LOG output
- L106 _public property_ `public static EventId Engine_Localization { get; }` — Engine: Localization commandlet output
- L111 _public property_ `public static EventId Engine_AppError { get; }` — Engine: appErrorf called
- L116 _public property_ `public static EventId Engine_AssertionFailed { get; }` — Engine: Assertion failed
- L121 _public property_ `public static EventId Engine_ShaderCompiler { get; }` — Engine: Shader compiler output
- L126 _public property_ `public static EventId AutomationTool { get; }` — UAT error
- L131 _public property_ `public static EventId AutomationTool_Crash { get; }` — UAT: Crash dump
- L136 _public property_ `public static EventId AutomationTool_CrashExitCode { get; }` — UAT: Exit code indicating a crash
- L141 _public property_ `public static EventId AutomationTool_SourceFileLine { get; }` — UAT: Source file with line number
- L146 _public property_ `public static EventId AutomationTool_MissingCopyright { get; }` — UAT: Missing copyright notice
- L151 _public property_ `public static EventId AutomationTool_PerforceCase { get; }` — UAT: Mismatched Perforce case
- L156 _public property_ `public static EventId AutomationTool_UnacceptableWords { get; }` — UAT: Unacceptable words
- L161 _public property_ `public static EventId AutomationTool_BuildGraphScript { get; }` — UAT: BuildGraph script parsing error
- L166 _public property_ `public static EventId AutomationTool_CodeSign { get; }` — UAT: CodeSign message
- L171 _public property_ `public static EventId MSBuild { get; }` — MSBuild: Generic error
- L176 _public property_ `public static EventId MSTest { get; }` — Microsoft: Generic MSTest error
- L181 _public property_ `public static EventId Microsoft { get; }` — Microsoft: Generic Visual Studio error
- L186 _public property_ `public static EventId Gauntlet { get; }` — Error message from Gauntlet
- L191 _public property_ `public static EventId Gauntlet_TestEvent { get; }` — Error message from Gauntlet test events
- L196 _public property_ `public static EventId Gauntlet_DeviceEvent { get; }` — Error message from Gauntlet device events
- L201 _public property_ `public static EventId Gauntlet_UnrealEngineTestEvent { get; }` — Error message from Gauntlet Unreal Engine test events
- L206 _public property_ `public static EventId Gauntlet_BuildDropEvent { get; }` — Error message from Gauntlet build drop events
- L211 _public property_ `public static EventId Gauntlet_FatalEvent { get; }` — Fatal Error message from Gauntlet events
- L216 _public property_ `public static EventId Systemic { get; }` — A systemic event, relating to the health of the farm
- L221 _public property_ `public static EventId Systemic_Perforce { get; }` — A systemic event relating to Perforce
- L226 _public property_ `public static EventId Systemic_Xge { get; }` — A systemic event from XGE
- L231 _public property_ `public static EventId Systemic_Xge_Standalone { get; }` — Builds will run in standalone mode
- L236 _public property_ `public static EventId Systemic_Xge_ServiceNotRunning { get; }` — BuildService.exe is not running
- L241 _public property_ `public static EventId Systemic_Xge_BuildFailed { get; }` — General build failed error
- L246 _public property_ `public static EventId Systemic_Xge_CacheLimit { get; }` — Cache size reached
- L251 _public property_ `public static EventId Systemic_Xge_DetailedLogging { get; }` — Current logging level may impact performance
- L256 _public property_ `public static EventId Systemic_Xge_TaskMetadata { get; }` — Metadata about an XGE task (local or remote execution, start/end time etc)
- L261 _public property_ `public static EventId Systemic_SlowDDC { get; }` — DDC is slow
- L266 _public property_ `public static EventId Systemic_Horde { get; }` — Internal Horde error
- L271 _public property_ `public static EventId Systemic_Horde_ArtifactUpload { get; }` — Artifact upload failed
- L276 _public property_ `public static EventId Systemic_Horde_Compute { get; }` — Internal Horde error
- L281 _public property_ `public static EventId Systemic_Horde_Http { get; }` — HTTP error
- L286 _public property_ `public static EventId Systemic_PdbUtil { get; }` — Harmless pdbutil error
- L291 _public property_ `public static EventId Systemic_MSBuild { get; }` — A systemic event from MSBuild
- L296 _public property_ `public static EventId Systemic_XCode { get; }` — A systemic event from XCode
- L301 _public property_ `public static EventId Systemic_RoboMergeGateLocked { get; }` — Robomerge gate is locked
- L306 _public property_ `public static EventId Systemic_MissingXgeControlWorker { get; }` — XGEControlWorker is missing
- L311 _public property_ `public static EventId Systemic_LogParserBottleneck { get; }` — Log parser is taking a significant amount of time; may be bottleneck.
- L316 _public property_ `public static EventId Systemic_LogEventMatcher { get; }` — Exception parsing a log event.
- L321 _public property_ `public static EventId Systemic_HostDownIOException { get; }` — Host is down during I/O operation, usually meaning a share isn't accessible.
- L328 _public property_ `public static EventId Systemic_SignToolTimeStampServer { get; }` — Microsoft SignTool cannot reach specified timestamp server Signing performs a looping retry using different servers and throws when all retries attempts have been exhausted.
- L335 _public property_ `public static EventId Systemic_SignTool { get; }` — Microsoft SignTool generic error Usually preceded by another type of error.
- L342 _public property_ `public static EventId Systemic_MissingFileList { get; }` — Missing file list error Usually due to a volume that is not mounted or some of other IO error
- L347 _public property_ `public static EventId Systemic_OutOfDiskSpace { get; }` — Out of disk space
- L352 _public property_ `public static EventId Systemic_ManagedWorkspace { get; }` — Error moving files to cache
- L357 _public property_ `public static EventId Systemic_UbaCacheResponseTimeout { get; }` — Generic timeout message emmitted by UBA
- L362 _public property_ `public static EventId Systemic_Docker { get; }` — Docker messages that are unactionable and can be ignored
- L367 _public property_ `public static EventId Systemic_Max { get; }` — Maximum code for systemic events. Add new events in the 700-799 range.
- L372 _public property_ `public static EventId Sanitizer { get; }` — Generic Sanitizer Error
- L377 _public property_ `public static EventId Sanitizer_Thread { get; }` — Thread Sanitizer Error
- L382 _public property_ `public static EventId Sanitizer_Address { get; }` — Address Sanitizer Error
- L387 _public property_ `public static EventId Sanitizer_RaceDetector { get; }` — RaceDetector Sanitizer Error
- L392 _public property_ `public static EventId WorldLeak { get; }` — World Leak Error
- L397 _public property_ `public static EventId Horde { get; }` — Horde error codes
- L402 _public property_ `public static EventId Horde_InvalidPreflight { get; }` — Invalid preflight change
- L407 _public property_ `public static EventId Horde_BlobRead { get; }` — Information about blobs being read
- L412 _public property_ `public static EventId Horde_BuildHealth_Ignore { get; }` — Event used to supporess the logging from the Horde build health service, regardless of log level
- L417 _public property_ `public static EventId Horde_Max { get; }` — Maximum code for Horde events. Add new events in the 1000-1099 range.
- L422 _public property_ `public static EventId ZenCli { get; }` — An event while running zen cli
- L427 _public property_ `public static EventId ZenCli_Event { get; }` — Strongly typed zen cli event
- L432 _public property_ `public static EventId ZenCli_Max { get; }` — Maximum code for zencli events. Add new events in the 1100-1200 range.

### `Source/Programs/Shared/EpicGames.Core/Logging/LegacyEventLogger.cs` (EpicGames.Core)


#### class `EpicGames.Core.LegacyEventLogger`  
`sealed class LegacyEventLogger : ILogger, IDisposable`  
_internal*; L14-167_
- inherits: `ILogger, IDisposable`
- desc: Wrapper around a custom logger interface which flushes the event parser when switching between legacy and native structured logging. Also support threading the log messages to minimize performance overhead
- L16 _private field_ `private volatile ILogger _inner`
- L17 _private field_ `private readonly LogEventParser _parser`
- L18 _private field_ `private ThreadingState? _state`
- L20 _public property_ `public LogEventParser Parser => ...`
- L22-26 _public ctor_ `public LegacyEventLogger(ILogger inner)`
- L28-33 _public method_ `public void Dispose()`
- L39-47 _public method_ `public void SetInnerLogger(ILogger inner)` — Set inner logger to transfer log calls to
- L52-56 _public method_ `public void EnableThreaded()` — Enable background logging (idempotent).
- L61-65 _public method_ `public void DisableThreaded()` — Disable background logging and drain queued items (idempotent).
- L68 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull`
- L70 _public method_ `public bool IsEnabled(LogLevel logLevel)`
- L72-112 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)`

#### class `EpicGames.Core.LegacyEventLogger.ThreadingState`  
`private sealed class ThreadingState`  
_private; L114-166_
- L116 _public field_ `public readonly ChannelWriter<Action> Writer`
- L117 _private field_ `private readonly ChannelReader<Action> _reader`
- L118 _private field_ `private readonly Thread _thread`
- L120-158 _public ctor_ `public ThreadingState()`
- L160-165 _public method_ `public void Stop()`

### `Source/Programs/Shared/EpicGames.Core/Logging/Log.cs` (EpicGames.Core)


#### enum `EpicGames.Core.LogEventType`  
`public enum LogEventType`  
_public; L26-65_
- desc: Log Event Type
- L32 _public* enumerator_ `Fatal = LogLevel.Critical` — The log event is a fatal error
- L37 _public* enumerator_ `Error = LogLevel.Error` — The log event is an error
- L42 _public* enumerator_ `Warning = LogLevel.Warning` — The log event is a warning
- L47 _public* enumerator_ `Console = LogLevel.Information` — Output the log event to the console
- L52 _public* enumerator_ `Log = LogLevel.Debug` — Output the event to the on-disk log
- L57 _public* enumerator_ `Verbose = LogLevel.Trace` — The log event should only be displayed if verbose logging is enabled
- L63 _public* enumerator_ `VeryVerbose = LogLevel.Trace` — The log event should only be displayed if very verbose logging is enabled

#### enum `EpicGames.Core.LogFormatOptions`  
`public enum LogFormatOptions`  
_public; L71-87_
- attrs: `[Flags]`
- desc: Options for formatting messages
- L76 _public* enumerator_ `None = 0` — Format normally
- L81 _public* enumerator_ `NoSeverityPrefix = 1` — Never write a severity prefix. Useful for pre-formatted messages that need to be in a particular format for, eg. the Visual Studio output window
- L86 _public* enumerator_ `NoConsoleOutput = 2` — Do not output text to the console

#### class `EpicGames.Core.Log`  
`public static class Log`  
_public; L101-786_
- desc: UAT/UBT Custom log system. This lets you use any TraceListeners you want, but you should only call the static methods below, not call Trace.XXX directly, as the static methods This allows the system to enforce the formatting and filtering conventions we desire. For posterity, we cannot use the Trace or TraceSource class directly because of our special log requirements: 1. We possibly capture the method name of the logging event. This cannot be done as a macro, so must be done at the top level so we know how many layers of the stack to peel off to get the real function. 2. We have a verbose filter we would like to apply to all logs without having to have each listener filter individually, which would require our string formatting code to run every time. 3. We possibly want to ensure severity prefixes are logged, but Trace.WriteXXX does not allow any severity info to be passed down.
- L106 _private field_ `private static readonly DefaultLogger s_defaultLogger = new()` — Singleton instance of the default output logger
- L111 _private field_ `private static readonly LegacyEventLogger s_legacyLogger = new(s_defaultLogger)` — Logger instance which parses events and forwards them to the main logger.
- L116 _public property_ `public static LogEventParser EventParser => ...` — Accessor for the global event parser from legacy events
- L121 _public property_ `public static ILogger Logger => ...` — Logger instance
- L126-130 _public property_ `public static LogEventType OutputLevel { get; set; }` — When true, verbose logging is enabled.
- L135-139 _public property_ `public static bool IncludeTimestamps { get; set; }` — Whether to include timestamps on each line of log output
- L144 _public property_ `public static bool IncludeSeverityPrefix { get; set; }` — When true, warnings and errors will have a WARNING: or ERROR: prefix, respectively.
- L149 _public property_ `public static bool IncludeProgramNameWithSeverityPrefix { get; set; }` — When true, warnings and errors will have a prefix suitable for display by MSBuild (avoiding error messages showing as (EXEC : Error : ")
- L154-158 _public property_ `public static bool ColorConsoleOutput { get; set; }` — When true, will detect warnings and errors and set the console output color to yellow and red.
- L163-167 _public property_ `public static bool IncludeStartingTimestamp { get; set; }` — When true, a timestamp will be written to the log file when the first listener is added
- L174 _public property_ `public static bool BackupLogFiles { get; set; }` — When true, create a backup of any text log file that would be overwritten by a new log Log.txt will be backed up with its UTC creation time in the name e.g. Log-backup-2021.10.29-19.53.17.txt
- L180 _public property_ `public static int LogFileBackupCount { get; set; }` — The number of backups to be preserved - when there are more than this, the oldest backups will be deleted. Backups will not be deleted if BackupLogFiles is false.
- L185 _public property_ `public static FileReference? OutputFile => ...` — Path to the log file being written to. May be null.
- L190 _private field_ `private static readonly ConcurrentDictionary<string, bool> s_writeOnceSet = ...` — A collection of strings that have been already written once
- L190 _private field_ `private static readonly ConcurrentDictionary< s_writeOnceSet = new()` — A collection of strings that have been already written once
- L196-199 _public method_ `public static void SetInnerLogger(ILogger logger)` — Overrides the logger used for formatting output, after event parsing
- L205-208 _public method_ `public static async Task FlushAsync()` — Flush the current log output
- L213-216 _public method_ `public static void EnableThreaded()` — Enable threaded logging. This can be used for performance reasons to prevent stalls when lots of logging is made from multiple threads
- L221-224 _public method_ `public static void DisableThreaded()` — Disable threaded logging. will flush queued log entries and get back to synchronous logging
- L230-276 _public method_ `public static void BackupLogFile(FileReference outputFile)` — Backup an existing log file if it already exists at the output path
- L285-288 _public method_ `public static void AddFileWriter(string name, FileReference outputFile)` — Adds a trace listener that writes to a log file. If a StartupTraceListener was in use, this function will copy its captured data to the log file(s) and remove the startup listener from the list of registered listeners.
- L297-300 _public method_ `public static void AddFileWriterWithoutBackup(string name, FileReference outputFile)` — Adds a trace listener that writes to a log file. If a StartupTraceListener was in use, this function will copy its captured data to the log file(s) and remove the startup listener from the list of registered listeners.
- L305-308 _public method_ `public static void AddStartupTraceListener()` — Adds a StartupTraceListener to the collection in a safe manner.
- L313-316 _public method_ `public static void RemoveStartupTraceListener()` — Removes a StartupTraceListener from the collection in a safe manner.
- L322-325 _public method_ `public static bool HasFileWriter()` — Determines if a TextWriterTraceListener has been added to the list of trace listeners
- L332-349 _private method_ `private static string GetSeverityPrefix(LogEventType severity)` — Converts a LogEventType into a log prefix. Only used when bLogSeverity is true.
- L360-443 _private method_ `private static void WriteLinePrivate(bool bWriteOnce, LogEventType verbosity, LogFormatOptions formatOptions, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes a formatted message to the console. All other functions should boil down to calling this method.
- L453-459 _public method_ `public static void WriteLineIf(bool condition, LogEventType verbosity, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Similar to Trace.WriteLineIf
- L468-471 _public method_ `public static void WriteLine(LogEventType verbosity, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Similar to Trace.WriteLine
- L481-484 _public method_ `public static void WriteLine(LogEventType verbosity, LogFormatOptions formatOptions, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Similar to Trace.WriteLine
- L491-499 _public method_ `public static void WriteException(Exception ex, FileReference? logFileName)` — Formats an exception for display in the log. The exception message is shown as an error, and the stack trace is included in the log.
- L508-511 _public method_ `public static void TraceError(string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogError with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes an error message to the console.
- L520-523 _public method_ `public static void TraceErrorTask(FileReference file, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes an error message to the console, in a format suitable for Visual Studio to parse.
- L533-536 _public method_ `public static void TraceErrorTask(FileReference file, int line, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes an error message to the console, in a format suitable for Visual Studio to parse.
- L546-549 _public method_ `public static void TraceVerbose(string format, params object?[] args)` — attrs: `[Conditional("TRACE")] [StringFormatMethod("Format")] [Obsolete("Use Logger.LogDebug with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes a verbose message to the console.
- L558-561 _public method_ `public static void TraceInformation(string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogInformation with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes a message to the console.
- L570-573 _public method_ `public static void TraceWarning(string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogWarning with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes a warning message to the console.
- L582-585 _public method_ `public static void TraceWarningTask(FileReference file, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes a warning message to the console, in a format suitable for Visual Studio to parse.
- L595-598 _public method_ `public static void TraceWarningTask(FileReference file, int line, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes a warning message to the console, in a format suitable for Visual Studio to parse.
- L607-610 _public method_ `public static void TraceConsoleTask(FileReference file, int line, string format, params object?[] args)` — Writes a message to the console.
- L620-623 _public method_ `public static void TraceVeryVerbose(string format, params object?[] args)` — attrs: `[Conditional("TRACE")] [StringFormatMethod("Format")] [Obsolete("Use Logger.LogTrace with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes a very verbose message to the console.
- L633-636 _public method_ `public static void TraceLog(string format, params object?[] args)` — attrs: `[Conditional("TRACE")] [StringFormatMethod("Format")] [Obsolete("Use Logger.LogDebug with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes a message to the log only.
- L645-648 _public method_ `public static void WriteLineOnce(LogEventType verbosity, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Similar to Trace.WriteLine
- L658-661 _public method_ `public static void WriteLineOnce(LogEventType verbosity, LogFormatOptions options, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Similar to Trace.WriteLine
- L669-672 _public method_ `public static void TraceErrorOnce(string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes an error message to the console.
- L681-684 _public method_ `public static void TraceVerboseOnce(string format, params object?[] args)` — attrs: `[Conditional("TRACE")] [StringFormatMethod("Format")]` — Writes a verbose message to the console.
- L692-695 _public method_ `public static void TraceInformationOnce(string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes a message to the console.
- L703-706 _public method_ `public static void TraceWarningOnce(string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes a warning message to the console.
- L715-718 _public method_ `public static void TraceWarningOnce(FileReference file, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes a warning message to the console.
- L728-731 _public method_ `public static void TraceWarningOnce(FileReference file, int line, string format, params object?[] args)` — attrs: `[StringFormatMethod("Format")]` — Writes a warning message to the console.
- L740-743 _public method_ `public static void TraceVeryVerboseOnce(string format, params object?[] args)` — attrs: `[Conditional("TRACE")] [StringFormatMethod("Format")]` — Writes a very verbose message to the console.
- L752-755 _public method_ `public static void TraceLogOnce(string format, params object?[] args)` — attrs: `[Conditional("TRACE")] [StringFormatMethod("Format")]` — Writes a message to the log only.
- L763-766 _public method_ `public static void PushStatus(string message)` — attrs: `[Conditional("TRACE")]` — Enter a scope with the given status message. The message will be written to the console without a newline, allowing it to be updated through subsequent calls to UpdateStatus(). The message will be written to the log immediately. If another line is written while in a status scope, the initial status message is flushed to the console first.
- L773-776 _public method_ `public static void UpdateStatus(string message)` — attrs: `[Conditional("TRACE")]` — Updates the current status message. This will overwrite the previous status line.
- L782-785 _public method_ `public static void PopStatus()` — attrs: `[Conditional("TRACE")]` — Updates the Pops the top status message from the stack. The mess

#### class `EpicGames.Core.LoggerScopeCollection`  
`public sealed class LoggerScopeCollection`  
_public; L791-846_
- desc: Base implementation for loggers which handles creation of LogEvents from log commands
- L816 _private* field_ `readonly List<Scope> _scopes = []`
- L821 _public method_ `public bool IsEmpty()` — Tests whether the collection is empty
- L827 _public method_ `public IDisposable BeginScope<TState>(TState state)` — Creates a scope with the given state
- L833-845 _public method_ `public IEnumerable<KeyValuePair<string, object?>> GetProperties()` — Enumerates all current properties

#### class `EpicGames.Core.LoggerScopeCollection.Scope`  
`class Scope : IDisposable`  
_private*; L793-814_
- inherits: `IDisposable`
- L795 _private* field_ `readonly LoggerScopeCollection _outer`
- L796 _private* field_ `readonly IEnumerable<KeyValuePair<string, object?>>? _properties`
- L796 _private* field_ `readonly IEnumerable<KeyValuePair< _properties`
- L798 _public property_ `public IEnumerable<KeyValuePair<string, object?>>? Properties => ...`
- L800-810 _public ctor_ `public Scope(LoggerScopeCollection outer, object? value)`
- L812 _public method_ `public void Dispose()`

#### class `EpicGames.Core.CaptureLogger`  
`public class CaptureLogger : ILogger`  
_public; L851-897_
- inherits: `ILogger`
- desc: Logger which captures the output for rendering later
- L853 _private* field_ `readonly LoggerScopeCollection _scopeCollection = new()`
- L858 _public property_ `public List<LogEvent> Events { get; }` — List of captured events
- L864 _public method_ `public string Render()` — Renders the captured events as a single string
- L870 _public method_ `public string Render(string newLine)` — Renders the captured events as a single string
- L876 _public method_ `public List<string> RenderLines()` — Renders all the captured events
- L882 _public method_ `public void RenderTo(ILogger logger)` — Renders all the captured events to another logger
- L885 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L888 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L891-896 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)

#### class `EpicGames.Core.DefaultLogger`  
`class DefaultLogger : ILogger, IDisposable`  
_internal*; L902-1487_
- inherits: `ILogger, IDisposable`
- desc: Default log output device
- L935 _private field_ `private readonly LoggerScopeCollection _scopeCollection = new()`
- L936 _private field_ `private readonly Lock _syncObject = new()`
- L941-944 _public property_ `public LogLevel OutputLevel { get; set; }` — Minimum level for outputting messages
- L949-952 _public property_ `public bool IncludeTimestamps { get; set; }` — Whether to include timestamps on each line of log output
- L957-960 _public property_ `public bool ColorConsoleOutput { get; set; }` — When true, will detect warnings and errors and set the console output color to yellow and red.
- L965-968 _public property_ `public bool WriteJsonToStdOut { get; set; }` — Whether to write JSON to stdout
- L973-976 _public property_ `public bool IncludeStartingTimestamp { get; set; }` — When true, a timestamp will be written to the log file when the first listener is added
- L977 _private field_ `private bool _includeStartingTimestampWritten = false`
- L982-985 _public property_ `public FileReference? OutputFile { get; set; }` — Path to the log file being written to. May be null.
- L990 _private property_ `private static bool AllowStatusUpdates { get; set; }` — Whether console output is redirected. This prevents writing status updates that rely on moving the cursor.
- L995 _private field_ `private readonly Stopwatch _timer = Stopwatch.StartNew()` — When configured, this tracks time since initialization to prepend a timestamp to each log.
- L1000 _private field_ `private readonly Stack<StatusMessage> _statusMessageStack = new()` — Stack of status scope information.
- L1005 _private field_ `private string _statusText = ""` — The currently visible status text
- L1010 _public property_ `public LogEventParser EventParser { get; }` — Parser for transforming legacy log output into structured events
- L1015 _private field_ `private readonly Stopwatch _statusTimer = new()` — Last time a status message was pushed to the stack
- L1020 _private field_ `private Task _writeTask` — Background task for writing to files
- L1025 _private field_ `private Channel<JsonLogEvent> _eventChannel = Channel.CreateUnbounded<JsonLogEvent>()` — Channel for new log events
- L1030 _private field_ `private ImmutableArray<FileStream> _jsonStreams = []` — Output streams for structured log data
- L1035-1050 _public ctor_ `public DefaultLogger()` — Constructor
- L1053-1057 _public method_ `public void Dispose()` — (inheritdoc)
- L1063-1074 _public method_ `public async Task FlushAsync()` — Flush the log queue
- L1079-1101 _private* method_ `async Task WriteFilesAsync()` — Background task to write events to sinks
- L1109-1128 _private method_ `private TextWriterTraceListener AddTextWriter(string name, FileReference outputFile)` — Adds a trace listener that writes to a log file
- L1134-1150 _private method_ `private void AddJsonWriter(FileReference outputFile)` — Adds a JSON stream to the collection
- L1155-1165 _public method_ `public void AddStartupTraceListener()` — Adds a StartupTraceListener to the collection in a safe manner.
- L1170-1178 _private method_ `private void WriteInitialTimestamp()` — Write a timestamp to the log, once. To be called when a new listener is added.
- L1183-1195 _public method_ `public StartupTraceListener? RemoveStartupTraceListener()` — Removes a StartupTraceListener from the collection in a safe manner.
- L1197-1203 _public method_ `public void AddFileWriter(string name, FileReference outputFile)`
- L1212-1223 _public method_ `public void AddFileWriterWithoutBackup(string name, FileReference outputFile)` — Adds a trace listener that writes to a log file. If a StartupTraceListener was in use, this function will copy its captured data to the log file(s) and remove the startup listener from the list of registered listeners.
- L1229-1235 _public method_ `public bool HasFileWriter()` — Determines if a TextWriterTraceListener has been added to the list of trace listeners
- L1238 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L1242-1245 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L1248-1355 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)
- L1360-1377 _private* method_ `void FlushStatusHeading()` — Flushes the current status text before writing out a new log line or status message
- L1385-1402 _public method_ `public void PushStatus(string message)` — attrs: `[Conditional("TRACE")]` — Enter a scope with the given status message. The message will be written to the console without a newline, allowing it to be updated through subsequent calls to UpdateStatus(). The message will be written to the log immediately. If another line is written while in a status scope, the initial status message is flushed to the console first.
- L1409-1422 _public method_ `public void UpdateStatus(string message)` — attrs: `[Conditional("TRACE")]` — Updates the current status message. This will overwrite the previous status line.
- L1428-1443 _public method_ `public void PopStatus()` — attrs: `[Conditional("TRACE")]` — Updates the Pops the top status message from the stack. The mess
- L1449-1486 _private method_ `private void SetStatusText(string newStatusText)` — Update the status text. For internal use only; does not modify the StatusMessageStack objects.

#### class `EpicGames.Core.DefaultLogger.StatusMessage`  
`class StatusMessage`  
_private*; L908-933_
- attrs: `[DebuggerDisplay("{_headingText}")]`
- desc: Temporary status message displayed on the console.
- L913 _public field_ `public string _headingText` — The heading for this status message.
- L918 _public field_ `public string _currentText` — The current status text.
- L923 _public field_ `public bool _hasFlushedHeadingText` — Whether the heading has been written to the console. Before the first time that lines are output to the log in the midst of a status scope, the heading will be written on a line of its own first.
- L928-932 _public ctor_ `public StatusMessage(string headingText, string currentText)` — Constructor

#### class `EpicGames.Core.DefaultLoggerProvider`  
`public sealed class DefaultLoggerProvider : ILoggerProvider`  
_public; L1492-1504_
- inherits: `ILoggerProvider`
- desc: Provider for default logger instances
- L1495-1498 _public method_ `public ILogger CreateLogger(string categoryName)` — (inheritdoc)
- L1501-1503 _public method_ `public void Dispose()` — (inheritdoc)

#### class `EpicGames.Core.DefaultLoggerExtensions`  
`public static class DefaultLoggerExtensions`  
_public; L1509-1519_
- desc: Extension methods to support the default logger
- L1515-1518 _public method_ `public static void AddEpicDefault(this ILoggingBuilder builder)` — Adds a regular Epic logger to the builder

### `Source/Programs/Shared/EpicGames.Core/Logging/LogBuffer.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogBuffer`  
`public class LogBuffer : ILogCursor`  
_public; L11-146_
- inherits: `ILogCursor`
- desc: Implementation of ILogCursor used to parse events from a stream of lines
- L13 _private* field_ `int _lineNumber`
- L14 _private* field_ `readonly string?[] _history`
- L15 _private* field_ `int _historyIdx`
- L16 _private* field_ `int _historyCount`
- L17 _private* field_ `readonly List<string?> _nextLines`
- L23-28 _public ctor_ `public LogBuffer(int historySize)` — Constructor
- L33-37 _public property_ `public bool NeedMoreData { get; set; }` — Whether the buffer needs more data
- L40 _public property_ `public string? CurrentLine => ...` — (inheritdoc)
- L43 _public property_ `public int CurrentLineNumber => ...` — (inheritdoc)
- L48 _public property_ `public int Length => ...` — Number of forward lines in the buffer
- L54-58 _public method_ `public void AddLine(string? line)` — Add a new line to the buffer
- L64-68 _public method_ `public void AddLines(IEnumerable<string?> lines)` — Add a collection of lines to the buffer
- L74-80 _public method_ `public void Advance(int count)` — Move forward a given number of lines
- L85-106 _public method_ `public void MoveNext()` — Move to the next line
- L109-139 _public indexer_ `public string? this[int offset] { get; }` — (inheritdoc)
- L142-145 _public method_ `public override string? ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/Logging/LogEvent.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogEventPropertyName`  
`public static class LogEventPropertyName`  
_public; L20-47_
- desc: Static read-only utf8 strings for parsing log events
- L23 _public field_ `public static readonly Utf8String Time = new("time")`
- L24 _public field_ `public static readonly Utf8String Frame = new("frame")`
- L25 _public field_ `public static readonly Utf8String Level = new("level")`
- L26 _public field_ `public static readonly Utf8String Id = new("id")`
- L27 _public field_ `public static readonly Utf8String Line = new("line")`
- L28 _public field_ `public static readonly Utf8String LineCount = new("lineCount")`
- L29 _public field_ `public static readonly Utf8String Message = new("message")`
- L30 _public field_ `public static readonly Utf8String Format = new("format")`
- L31 _public field_ `public static readonly Utf8String Properties = new("properties")`
- L33 _public field_ `public static readonly Utf8String Type = new("$type")`
- L34 _public field_ `public static readonly Utf8String Text = new("$text")`
- L36 _public field_ `public static readonly Utf8String File = new("file")`
- L37 _public field_ `public static readonly Utf8String Identifier = new("identifier")`
- L38 _public field_ `public static readonly Utf8String RelativePath = new("relativePath")`
- L39 _public field_ `public static readonly Utf8String DepotPath = new("depotPath")`
- L40 _public field_ `public static readonly Utf8String Target = new("target")`
- L42 _public field_ `public static readonly Utf8String Exception = new("exception")`
- L43 _public field_ `public static readonly Utf8String Trace = new("trace")`
- L44 _public field_ `public static readonly Utf8String InnerException = new("innerException")`
- L45 _public field_ `public static readonly Utf8String InnerExceptions = new("innerExceptions")`

#### class `EpicGames.Core.LogEvent`  
`public class LogEvent : IEnumerable<KeyValuePair<string, object?>>`  
_public; L53-640_
- attrs: `[JsonConverter(typeof(LogEventConverter))]`
- inherits: `IEnumerable<KeyValuePair<string, object?>>`
- desc: Epic representation of a log event. Can be serialized to/from Json for the Horde dashboard, and passed directly through ILogger interfaces.
- L58 _public property_ `public DateTime Time { get; set; }` — Time that the event was emitted
- L63 _public property_ `public ulong Frame { get; set; }` — Frame that the event was emitted, or 0 when not applicable
- L68 _public property_ `public LogLevel Level { get; set; }` — The log level
- L73 _public property_ `public EventId Id { get; set; }` — Unique id associated with this event. See KnownLogEvents for possible values.
- L78 _public property_ `public int LineIndex { get; set; }` — Index of the line within a multi-line message
- L83 _public property_ `public int LineCount { get; set; }` — Number of lines in the message
- L88 _public property_ `public string Message { get; set; }` — The formatted message
- L93 _public property_ `public string? Format { get; set; }` — Message template string
- L98 _public property_ `public IEnumerable<KeyValuePair<string, object?>>? Properties { get; set; }` — Map of property name to value
- L103 _public property_ `public LogException? Exception { get; }` — The exception value
- L130 _private* field_ `static readonly JsonSerializerOptions s_jsonSerializerOptions = new() { PropertyNamingPolicy = JsonNamingPolicy.CamelCase, DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull }`
- L135-138 _public ctor_ `public LogEvent(DateTime time, LogLevel level, EventId eventId, string message, string? format, IEnumerable<KeyValuePair<string, object?>>? properties, LogException? exception) : this(time, level, eventId, 0, 1, message, format, properties, exception)` — Constructor
- L143-146 _public ctor_ `public LogEvent(DateTime time, LogLevel level, EventId eventId, int lineIndex, int lineCount, string message, string? format, IEnumerable<KeyValuePair<string, object?>>? properties, LogException? exception) : this(time, 0, level, eventId, lineIndex, lineCount, message, format, properties, exception)` — Constructor
- L151-163 _public ctor_ `public LogEvent(DateTime time, ulong frame, LogLevel level, EventId eventId, int lineIndex, int lineCount, string message, string? format, IEnumerable<KeyValuePair<string, object?>>? properties, LogException? exception)` — Constructor
- L170 _public method_ `public void AddProperty(string name, object? value)` — Add a new property to this event
- L177-194 _public method_ `public void AddProperties(IEnumerable<KeyValuePair<string, object?>> properties)` — Add new properties to this event
- L201-209 _public method_ `public object GetProperty(string name)` — Gets an untyped property with the given name
- L217 _public method_ `public T GetProperty<T>(string name)` — Gets a property with the given name
- L225-241 _public method_ `public bool TryGetProperty(string name, [NotNullWhen(true)] out object? value)` — Finds a property with the given name
- L250-263 _public method_ `public bool TryGetProperty<T>(string name, [NotNullWhen(true)] out T value)` — Finds a typed property with the given name
- L270-275 _public method_ `public static LogEvent Read(ReadOnlySpan<byte> data)` — Read a log event from a utf-8 encoded json byte array
- L283-339 _public method_ `public static LogEvent Read(ref Utf8JsonReader reader)` — Read a log event from Json
- L341-355 _private* method_ `static Dictionary<string, object?> ReadProperties(ref Utf8JsonReader reader)`
- L357-389 _private* method_ `static object? ReadPropertyValue(ref Utf8JsonReader reader)`
- L391-399 _private* method_ `static List<object?> ReadArrayPropertyValue(ref Utf8JsonReader reader)`
- L401-427 _private* method_ `static object ReadObjectPropertyValue(ref Utf8JsonReader reader)`
- L433-495 _public method_ `public void Write(Utf8JsonWriter writer)` — Writes a log event to Json
- L502-526 _private* method_ `static void WriteException(ref Utf8JsonWriter writer, LogException exception)` — Writes an exception to a json object
- L531 _public method_ `public static LogEvent Create(LogLevel level, string format, params object[] args)` — Create a new log event
- L537 _public method_ `public static LogEvent Create(LogLevel level, EventId eventId, string format, params object[] args)` — Create a new log event
- L543-550 _public method_ `public static LogEvent Create(LogLevel level, EventId eventId, Exception? exception, string format, params object[] args)` — Create a new log event
- L555-575 _public method_ `public static LogEvent FromState<TState>(LogLevel level, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — Creates a log event from an ILogger parameters
- L581-598 _public method_ `public IEnumerator<KeyValuePair<string, object?>> GetEnumerator()` — Enumerates all the properties in this object
- L604-610 _private* method_ `System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()` — Enumerates all the properties in this object
- L615-623 _public method_ `public byte[] ToJsonBytes()` — Serialize a message template to JOSN
- L628-636 _public method_ `public string ToJson()` — Serialize a message template to JOSN
- L639 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Core.LogEvent.MergedPropertyList`  
`class MergedPropertyList : IEnumerable<KeyValuePair<string, object?>>`  
_private*; L105-128_
- inherits: `IEnumerable<KeyValuePair<string, object?>>`
- L107 _private* field_ `readonly HashSet<string> _names = []`
- L108 _private* field_ `readonly List<KeyValuePair<string, object?>> _properties = ...`
- L108 _private* field_ `readonly List<KeyValuePair< _properties = []`
- L110-119 _public method_ `public void AddRange(IEnumerable<KeyValuePair<string, object?>> properties)`
- L122 _public method_ `public IEnumerator<KeyValuePair<string, object?>> GetEnumerator()` — (inheritdoc)
- L126 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

#### class `EpicGames.Core.LogException`  
`public sealed class LogException`  
_public; L645-707_
- desc: Information about an exception in a log event
- L650 _public property_ `public string Message { get; set; }` — Exception message
- L655 _public property_ `public string Trace { get; set; }` — Stack trace for the exception
- L660 _public property_ `public LogException? InnerException { get; set; }` — Optional inner exception information
- L665 _public property_ `public List<LogException> InnerExceptions { get; }` — Multiple inner exceptions, in the case of an AggregateException
- L672-676 _public ctor_ `public LogException(string message, string trace)` — Constructor
- L683-706 _public method_ `public static LogException? FromException(Exception? exception)` — attrs: `[return: NotNullIfNotNull(nameof(exception))]` — Constructor

#### interface `EpicGames.Core.ILogEventSink`  
`public interface ILogEventSink`  
_public; L712-719_
- desc: Interface for a log event sink
- L718 _public* method_ `void ProcessEvent(LogEvent logEvent)` — Process log event

#### class `EpicGames.Core.FilteringEventSink`  
`public class FilteringEventSink : ILogEventSink`  
_public; L724-755_
- inherits: `ILogEventSink`
- desc: Simple filtering log event sink with a callback for convenience
- L729 _public property_ `public IReadOnlyList<LogEvent> LogEvents => ...` — Log events received
- L731 _private field_ `private readonly List<LogEvent> _logEvents = []`
- L732 _private field_ `private readonly int[] _includeEventIds`
- L733 _private field_ `private readonly Action<LogEvent>? _eventCallback`
- L740-744 _public ctor_ `public FilteringEventSink(int[] includeEventIds, Action<LogEvent>? eventCallback = null)` — Constructor
- L747-754 _public method_ `public void ProcessEvent(LogEvent logEvent)` — (inheritdoc)

#### class `EpicGames.Core.LogEventConverter`  
`public class LogEventConverter : JsonConverter<LogEvent>`  
_public; L760-773_
- inherits: `JsonConverter<LogEvent>`
- desc: Converter for serialization of LogEvent instances to Json streams
- L763-766 _public method_ `public override LogEvent Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L769-772 _public method_ `public override void Write(Utf8JsonWriter writer, LogEvent value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/Logging/LogEventBuilder.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogEventSpan`  
`public class LogEventSpan`  
_public; L14-60_
- desc: Stores information about a span within a line
- L19-22 _public property_ `public int Offset { get; }` — Starting offset within the line
- L27-30 _public property_ `public string Text { get; }` — Text for this span
- L35-38 _public property_ `public Dictionary<string, object> Properties { get; }` — Storage for properties
- L45-50 _public ctor_ `public LogEventSpan(int offset, string text)` — Constructor
- L56-59 _public method_ `public override string ToString()` — Converts this object to a string. This determines how the span will be rendered by the default console logger, so should return the original text.

#### class `EpicGames.Core.LogEventLine`  
`public class LogEventLine`  
_public; L65-164_
- desc: Individual line in the log output
- L70-73 _public property_ `public string Text { get; }` — The raw text
- L78-81 _public property_ `public Dictionary<string, LogEventSpan> Spans { get; }` — List of spans for markup
- L87-91 _public ctor_ `public LogEventLine(string text)` — Constructor
- L100-105 _public method_ `public LogEventSpan AddSpan(int offset, int length, string name)` — Adds a span containing markup on the source text
- L112-115 _public method_ `public LogEventSpan AddSpan(Group group, string name)` — Adds a span containing markup for a regex match group
- L121-124 _public method_ `public LogEventSpan AddSpan(Group group)` — Adds a span naming a regex match group, using the name of the group
- L131-141 _public method_ `public LogEventSpan? TryAddSpan(Group group, string name)` — Adds a span naming a regex match group, using the name of the group
- L147-157 _public method_ `public LogEventSpan? TryAddSpan(Group group)` — Adds a span naming a regex match group, using the name of the group
- L160-163 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Core.LogEventBuilder`  
`public class LogEventBuilder`  
_public; L169-506_
- desc: Allows building log events by annotating a window of lines around the current cursor position.
- L204 _public property_ `public ILogCursor Current { get; set; }` — The current cursor position
- L209 _public property_ `public ILogCursor Next { get; set; }` — The next cursor position
- L214 _private* field_ `List<LogLine>? _lines` — Events which have been parsed so far
- L219 _private* field_ `List<LogSpan>? _spans` — Spans for the current line
- L224 _private* field_ `Dictionary<string, object>? _properties` — Additional properties for this line
- L224 _private* field_ `Dictionary< _properties` — Additional properties for this line
- L231-240 _public ctor_ `public LogEventBuilder(ILogCursor cursor, int lineCount = 1)` — Starts building a log event at the current cursor position
- L246-269 _private* method_ `LogLine CreateLine()` — Creates a log event from the current line
- L279-295 _public method_ `public void Annotate(string name, int offset, int length, object? value = null)` — Adds a span containing markup on the source text
- L303-306 _public method_ `public void Annotate(string name, Group group, object? value = null)` — Adds a span containing markup for a regex match group
- L313-316 _public method_ `public void Annotate(Group group, object? value = null)` — Adds a span naming a regex match group, using the name of the group
- L324-332 _public method_ `public bool TryAnnotate(string name, Group group, object? value = null)` — Adds a span naming a regex match group, using the name of the group
- L339-347 _public method_ `public bool TryAnnotate(Group group, object? value = null)` — Adds a span naming a regex match group, using the name of the group
- L354-358 _public method_ `public void AddProperty(string name, object value)` — Adds an additional named property
- L360-370 _private* method_ `string? GetFirstLine()`
- L376 _public method_ `public bool IsNextLineAligned()` — Check if the next line is aligned or indented from the first line
- L382 _public method_ `public bool IsNextLineHanging()` — Check if the next line is indented from the first line
- L387-397 _public method_ `public void MoveNext()` — Complete the current line and move to the next
- L403-409 _public method_ `public void MoveNext(int count)` — Advance by the given number of lines
- L415-437 _public method_ `public LogEvent[] ToArray(LogLevel level, EventId eventId)` — Returns an array of log events
- L439-473 _private* method_ `static LogEvent CreateEvent(DateTime time, LogLevel level, EventId eventId, int lineIndex, int lineCount, LogLine line)`
- L483-486 _public method_ `public LogEventMatch ToMatch(LogEventPriority priority, LogLevel level, EventId eventId, bool isComplete = true)` — Creates a match object at the given priority
- L495-505 _public method_ `public LogEventMatch ToMatchWithHangingLines(LogEventPriority priority, LogLevel level, EventId eventId)` — Creates a match object at the given priority with hanging lines

#### class `EpicGames.Core.LogEventBuilder.LogSpan`  
`class LogSpan`  
_private*; L171-185_
- L173 _public field_ `public string _name`
- L174 _public field_ `public int _offset`
- L175 _public field_ `public int _length`
- L176 _public field_ `public object? _value`
- L178-184 _public ctor_ `public LogSpan(string name, int offset, int length, object? value)`

#### class `EpicGames.Core.LogEventBuilder.LogLine`  
`class LogLine`  
_private*; L187-199_
- L189 _public field_ `public string _message`
- L190 _public field_ `public string? _format`
- L191 _public field_ `public Dictionary<string, object>? _properties`
- L191 _public field_ `public Dictionary< _properties`
- L193-198 _public ctor_ `public LogLine(string message, string? format, Dictionary<string, object>? properties)`

### `Source/Programs/Shared/EpicGames.Core/Logging/LogEventMarkup.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogEventMarkup`  
`public static class LogEventMarkup`  
_public; L13-112_
- desc: Extension methods to allow adding markup to log event spans
- L16 _public property_ `public static LogValue Channel => ...`
- L17 _public property_ `public static LogValue Severity => ...`
- L18 _public property_ `public static LogValue Message => ...`
- L19 _public property_ `public static LogValue LineNumber => ...`
- L20 _public property_ `public static LogValue ColumnNumber => ...`
- L21 _public property_ `public static LogValue Symbol => ...`
- L22 _public property_ `public static LogValue ErrorCode => ...`
- L23 _public property_ `public static LogValue ToolName => ...`
- L24 _public property_ `public static LogValue ScreenshotTest => ...`
- L27 _private* field_ `static readonly char[] s_pathChars = ['/', '\\']`
- L29-56 _private* method_ `static string RemoveRelativeDirs(string path)`
- L61-81 _public method_ `public static void AnnotateSourceFile(this LogEventBuilder builder, Group group, string? baseDir)` — Marks a span of text as a source file
- L86-89 _public method_ `public static void AnnotateAsset(this LogEventBuilder builder, Group group)` — Marks a span of text as a source file
- L94-111 _public method_ `public static void AnnotateSymbol(this LogEventBuilder builder, Group group)` — Marks a span of text as a symbol

### `Source/Programs/Shared/EpicGames.Core/Logging/LogEventParser.cs` (EpicGames.Core)


#### enum `EpicGames.Core.LogEventPriority`  
`public enum LogEventPriority`  
_public; L18-59_
- desc: Confidence of a matched log event being the correct derivation
- L23 _public* enumerator_ `None` — Unspecified priority
- L28 _public* enumerator_ `Lowest` — Lowest confidence match
- L33 _public* enumerator_ `Low` — Low confidence match
- L38 _public* enumerator_ `BelowNormal` — Below normal confidence match
- L43 _public* enumerator_ `Normal` — Normal confidence match
- L48 _public* enumerator_ `AboveNormal` — Above normal confidence match
- L53 _public* enumerator_ `High` — High confidence match
- L58 _public* enumerator_ `Highest` — Highest confidence match

#### class `EpicGames.Core.LogEventMatch`  
`public class LogEventMatch`  
_public; L64-100_
- desc: Information about a matched event
- L69 _public property_ `public LogEventPriority Priority { get; }` — Confidence of the match
- L74 _public property_ `public List<LogEvent> Events { get; }` — Matched events
- L79 _public property_ `public bool IsComplete { get; }` — Match is complete
- L84-89 _public ctor_ `public LogEventMatch(LogEventPriority priority, LogEvent logEvent, bool isComplete)` — Constructor
- L94-99 _public ctor_ `public LogEventMatch(LogEventPriority priority, IEnumerable<LogEvent> events, bool isComplete)` — Constructor

#### interface `EpicGames.Core.ILogEventMatcher`  
`public interface ILogEventMatcher`  
_public; L105-122_
- desc: Interface for a class which matches error strings
- L112 _public* method_ `LogEventMatch? Match(ILogCursor cursor)` — Attempt to match events from the given input buffer
- L121 _public* method_ `string GetMatcherName()` — Get a name for this matcher, used to support dynamic matcher toggling. Names must not contain whitespace characters.

#### record struct `EpicGames.Core.IgnorePatternEntry`  
`public readonly record struct IgnorePatternEntry(Regex Pattern, string SourceFile)`  
_public; L129-140_
- desc: An ignore pattern with metadata about its source file
- L134 _public operator_ `public static implicit operator Regex(IgnorePatternEntry entry)` — Implicit conversion to Regex for backward compatibility with code that expects IgnorePatterns to contain Regex objects.
- L139 _public operator_ `public static implicit operator IgnorePatternEntry(Regex pattern)` — Implicit conversion from Regex for backward compatibility with code that adds Regex objects directly.

#### class `EpicGames.Core.IgnorePatternEntryExtensions`  
`public static class IgnorePatternEntryExtensions`  
_public; L145-157_
- desc: Extension methods for backward compatibility with code that passes Regex collections to IgnorePatternEntry lists.
- L150-156 _public method_ `public static void AddRange(this List<IgnorePatternEntry> list, IEnumerable<Regex> patterns)` — Add a range of Regex objects as ignore pattern entries.

#### class `EpicGames.Core.LogEventParser`  
`public partial class LogEventParser : IDisposable`  
_public; L167-1075_
- inherits: `IDisposable`
- desc: Turns raw text output into structured logging events
- L172 _private* field_ `static readonly TimeSpan s_ignorePatternTimeout = TimeSpan.FromMilliseconds(200)` — Timeout applied to each ignore pattern regex match.
- L177 _protected property_ `protected static TimeSpan IgnorePatternTimeout => ...` — Timeout applied to each ignore pattern regex match. Exposed for derived classes.
- L182 _public property_ `public IEnumerable<ILogEventMatcher> EnabledMatchers => ...` — A list of enabled event matchers for this parser.
- L187 _public property_ `public List<IgnorePatternEntry> IgnorePatterns { get; }` — List of patterns to ignore
- L192 _private field_ `private readonly List<ILogEventMatcher> _matchers = []` — A list of matchers all matchers, including disabled matchers.
- L198 _private field_ `private readonly List<ILogEventMatcher> _enabledMatchers = []` — A list of enabled matchers, to allow quicker iteration when parsing log lines. It's expected that we'll parse significantly more log lines than we will toggle matcher states.
- L204 _private field_ `private readonly Dictionary<string, int> _matcherNameToEnabled = ...` — A mapping of matcher names to how many times they've been enabled / disabled. A negative value indicates a status of disabled. Items not present are enabled by default.
- L204 _private field_ `private readonly Dictionary< _matcherNameToEnabled = new(StringComparer.OrdinalIgnoreCase)` — A mapping of matcher names to how many times they've been enabled / disabled. A negative value indicates a status of disabled. Items not present are enabled by default.
- L209 _private field_ `private readonly Stack<(string MatcherName, string? GroupName, bool Enabled)> _matcherToggleLayers = []` — The layers of enabling / disabling matchers, so we can undo applications.
- L214 _private* field_ `readonly LogBuffer _buffer` — Buffer of input lines
- L219 _private* field_ `readonly ByteArrayBuilder _partialLine = new()` — Buffer for holding partial line data
- L224 _private* field_ `int _matchingEnabled` — Whether matching is currently enabled
- L229 _private* field_ `ILogger _logger` — The inner logger
- L234 _private* field_ `readonly List<ILogEventSink> _logEventSinks = []` — Log events sinks in addition to _logger
- L239 _private* field_ `readonly Stopwatch _timer = Stopwatch.StartNew()` — Timer for the parser being active
- L244 _private* field_ `readonly Stopwatch _activeTimer = new()` — Amount of time that the log parser has been processing events
- L249 _private* field_ `int _linesParsed = 0` — Number of lines parsed in the last interval
- L254 _private* field_ `ILogEventMatcher? _incompleteMatcher` — Incomplete matcher being processed
- L259 _private* field_ `int _incompleteEventCount` — Incomplete event count being processed
- L264-268 _public property_ `public ILogger Logger { get; set; }` — Public accessor for the logger
- L279 _public method_ `public static partial Regex MatcherToggleRegex()` — attrs: `[GeneratedRegex("^(?:<|\\\\u003C)-- logeventparser (layer=(?<LayerName>\\S+)? )?((?<Action>suspend|resume) (?<MatcherName>\\S+)|(?<Action>pop)) --(?:>|\\\\u003E)$", RegexOptions.IgnoreCase | RegexOptions.ExplicitCapture)]` — The pattern matcher toggle commands must conform to.
- L286-295 _public ctor_ `public LogEventParser(ILogger logger, List<ILogEventSink>? logEventSinks = null)` — Constructor
- L298-302 _public method_ `public void Dispose()` — (inheritdoc)
- L308-314 _protected method_ `protected virtual void Dispose(bool disposing)` — Standard Dispose pattern method
- L320-326 _public method_ `public void AddMatchers(IEnumerable<ILogEventMatcher> matchers)` — Add the selected matchers to the log event parser
- L332-342 _public method_ `public void AddMatchersFromAssembly(Assembly assembly)` — Enumerate all the types that implement ILogEventMatcher in the given assembly, and create instances of them
- L350-382 _public method_ `public async Task ReadIgnorePatternsAsync(DirectoryReference rootDir)` — attrs: `[Obsolete("Use ReadIgnorePatternsFromWorkspaceAsync or DiscoverIgnorePatternFiles instead")]` — Read ignore patterns from the given root directory
- L389-416 _public method_ `public async Task ReadIgnorePatternsAsync(FileReference ignorePatternFile)` — Read ignore patterns from a single file
- L418-429 _private* method_ `static void AddRestrictedDirs(List<DirectoryReference> directories, string subFolder)`
- L431-449 _private* method_ `static IgnorePatternEntry? FindMatchingIgnorePattern(List<IgnorePatternEntry> ignorePatterns, string line, ILogger logger)`
- L458-474 _private* method_ `void WriteIgnoredLine(string line, IgnorePatternEntry ignoredBy, LogLevel originalLevel)` — Writes a line that was suppressed by an ignore pattern, including structured properties identifying which pattern file and regex caused the suppression.
- L482-495 _private* method_ `bool TryIgnoreStructuredEvent(JsonLogEvent jsonEvent)` — Checks whether a structured JSON log event should be suppressed by an ignore pattern. Only events at Warning level or above are checked. If a matching pattern is found, the event is re-logged at Information level (preventing build health issue creation).
- L501-554 _public method_ `public static List<FileReference> DiscoverIgnorePatternFiles(DirectoryReference workspaceDir, string enginePath = "Engine")` — Discover all IgnorePatterns.txt files in a workspace by scanning Engine, project, and Restricted/Platforms subdirectories.
- L560-577 _public method_ `public static List<FileReference> DiscoverLegacyIgnorePatternFiles(DirectoryReference workspaceDir, string enginePath = "Engine")` — Legacy ignore pattern file discovery - scans only Engine + Engine/Restricted/* + Engine/Platforms/*. Use DiscoverIgnorePatternFiles for expanded workspace-wide scanning.
- L582-609 _public method_ `public async Task ReadIgnorePatternsFromWorkspaceAsync(DirectoryReference workspaceDir, string enginePath = "Engine")` — Read ignore patterns from the workspace, scanning Engine and project directories
- L614-641 _public method_ `public async Task ReadIgnorePatternsAsync(IEnumerable<FileReference> additionalFiles)` — Read ignore patterns from additional file paths
- L647-694 _public method_ `public void WriteLine(string line)` — Writes a line to the event filter
- L700-736 _public method_ `public void WriteData(ReadOnlyMemory<byte> data)` — Writes data to the log parser
- L741-751 _public method_ `public void Flush()` — Flushes the current contents of the parser
- L756-766 _private method_ `private void AddMatcher(ILogEventMatcher matcher)` — Add the new matcher, making sure its enabled state is correct.
- L771-796 _private method_ `private void PushToggle(string matcherName, string layerName, bool enabled)` — Set the given matcher to the given enabled state.
- L798-823 _private method_ `private void PopToggle(string layerName)`
- L828-844 _private method_ `private void RecalculateEnabledMatchers()` — Clear and repopulate the list of enabled matchers.
- L850-870 _private method_ `private void AddLine(ReadOnlyMemory<byte> data)` — Adds a raw utf-8 string to the buffer
- L875-879 _private method_ `private void FlushPartialLine()` — Writes the current partial line data, with the given data appended to it, then clear the buffer
- L886-911 _private method_ `private bool HandleLogEventParserCommand(string line)` — Check for and handle a log event parser command.
- L918-1003 _private* method_ `void ProcessData(bool bFlush, bool disableMatching = false)` — Process any data in the buffer
- L1010-1031 _private* method_ `bool ProcessIncomplete(bool bFlush)` — Process any incomplete match
- L1037-1058 _private method_ `private (ILogEventMatcher?, LogEventMatch?) MatchEvent()` — Try to match an event from the current buffer
- L1064-1074 _protected method_ `protected virtual void WriteEvents(IEnumerable<LogEvent> logEvents)` — Writes an event to the log

### `Source/Programs/Shared/EpicGames.Core/Logging/LogIndent.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogIndent`  
`public static class LogIndent`  
_public; L11-59_
- desc: Static class for tracking a stack of log indent prefixes
- L31 _private* field_ `static readonly AsyncLocal<State?> s_currentState = new()` — The current state value
- L36 _public property_ `public static string Current => ...` — Gets the current indent string
- L42-50 _public method_ `public static void Push(string indent)` — Push a new indent onto the stack
- L55-58 _public method_ `public static void Pop()` — Pops an indent off the stack

#### class `EpicGames.Core.LogIndent.State`  
`class State`  
_private*; L16-26_
- desc: Tracks the current state
- L18 _public property_ `public State? PrevState { get; }`
- L19 _public property_ `public string Indent { get; }`
- L21-25 _public ctor_ `public State(State? prevState, string indent)`

### `Source/Programs/Shared/EpicGames.Core/Logging/LogIndentScope.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogIndentScope`  
`public sealed class LogIndentScope : IDisposable`  
_public; L10-37_
- inherits: `IDisposable`
- desc: Class to apply a log indent for the lifetime of an object
- L15 _private* field_ `bool _disposed` — Whether the object has been disposed
- L21-24 _public ctor_ `public LogIndentScope(string indent)` — Constructor
- L29-36 _public method_ `public void Dispose()` — Restore the log indent to normal

### `Source/Programs/Shared/EpicGames.Core/Logging/LogStatusScope.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogStatusScope`  
`public sealed class LogStatusScope : IDisposable`  
_public; L11-94_
- inherits: `IDisposable`
- desc: Writes a status message to the log, which can be updated with a progress indicator as a slow task is being performed.
- L16 _private* field_ `string _message` — The base status message
- L22-26 _public ctor_ `public LogStatusScope(string message)` — Constructor
- L33-36 _public ctor_ `public LogStatusScope(string format, params object[] args) : this(String.Format(format, args))` — Constructor
- L42-46 _public method_ `public void SetMessage(string message)` — Updates the base status message passed into the constructor.
- L53-56 _public method_ `public void SetMessage(string format, params object[] args)` — Updates the base status message passed into the constructor.
- L62-68 _public method_ `public void SetProgress(string progress)` — Appends a progress string to the status message. Overwrites any previous progress message.
- L75-81 _public method_ `public void SetProgress(string format, params object[] args)` — Appends a progress string to the status message. Overwrites any previous progress message.
- L86-93 _public method_ `public void Dispose()` — Pops the status message from the log.

### `Source/Programs/Shared/EpicGames.Core/Logging/LogValue.cs` (EpicGames.Core)


#### class `EpicGames.Core.LogValueType`  
`public static class LogValueType`  
_public; L13-32_
- desc: Different types of log values (stored in the $type field of log properties)
- L16 _public field_ `public static readonly Utf8String Asset = new("Asset")`
- L17 _public field_ `public static readonly Utf8String SourceFile = new("SourceFile")`
- L18 _public field_ `public static readonly Utf8String Object = new("Object")`
- L19 _public field_ `public static readonly Utf8String Channel = new("Channel")`
- L20 _public field_ `public static readonly Utf8String Severity = new("Severity")`
- L21 _public field_ `public static readonly Utf8String Message = new("Message")`
- L22 _public field_ `public static readonly Utf8String LineNumber = new("Line")`
- L23 _public field_ `public static readonly Utf8String ColumnNumber = new("Column")`
- L24 _public field_ `public static readonly Utf8String Symbol = new("Symbol")`
- L25 _public field_ `public static readonly Utf8String ErrorCode = new("ErrorCode")`
- L26 _public field_ `public static readonly Utf8String ToolName = new("ToolName")`
- L27 _public field_ `public static readonly Utf8String ScreenshotTest = new("ScreenshotTest")`
- L28 _public field_ `public static readonly Utf8String DepotPath = new("DepotPath")`
- L29 _public field_ `public static readonly Utf8String Link = new("Link")`
- L30 _public field_ `public static readonly Utf8String IgnoredLine = new("IgnoredLine")`

#### class `EpicGames.Core.LogValueTypeAttribute`  
`public sealed class LogValueTypeAttribute : Attribute`  
_public; L38-49_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct)]`
- inherits: `Attribute`
- desc: Attribute indicating that a type should be tagged in log output
- L43 _public property_ `public string? Name { get; }` — Name to use for the type tag
- L48 _public ctor_ `public LogValueTypeAttribute(string? name = null)` — Constructor

#### class `EpicGames.Core.LogValue`  
`public sealed class LogValue`  
_public; L54-150_
- desc: Information for a structured value for use in log events
- L59 _public property_ `public Utf8String Type { get; set; }` — Type of the event
- L64 _public property_ `public string Text { get; set; }` — Rendering of the value
- L69 _public property_ `public Dictionary<Utf8String, object?>? Properties { get; }` — Properties associated with the value
- L77-82 _public ctor_ `public LogValue(Utf8String type, string text, Dictionary<Utf8String, object?>? properties = null)` — Constructor
- L89-92 _public method_ `public static LogValue SourceFile(FileReference file, string text)` — Construct a source file log value with an overridden display text
- L98-101 _public method_ `public static LogValue Link(Uri target)` — Constructs a value which contains a hyperlink to an external page
- L108-111 _public method_ `public static LogValue Link(Uri target, string text)` — Constructs a value which contains a hyperlink to an external page
- L118 _public method_ `public static LogValue FromObject(object obj)` — Creates a LogValue from an object, overriding the type and display text for it
- L127-143 _public method_ `public static LogValue FromObject(Utf8String type, string text, object obj)` — Creates a LogValue from an object, overriding the type and display text for it
- L146-149 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/Logging/LogValueFormatter.cs` (EpicGames.Core)


#### interface `EpicGames.Core.ILogValueFormatter`  
`public interface ILogValueFormatter`  
_public; L18-26_
- desc: Formatter for objects of a given type
- L25 _public* method_ `void Format(object value, Utf8JsonWriter writer)` — Format an object to a JSON output stream

#### class `EpicGames.Core.LogValueFormatterAttribute`  
`public sealed class LogValueFormatterAttribute : Attribute`  
_public; L32-47_
- attrs: `[AttributeUsage(AttributeTargets.Struct | AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Specifies a type to use for serializing objects to a log event
- L37 _public property_ `public Type Type { get; }` — Type of the formatter
- L43-46 _public ctor_ `public LogValueFormatterAttribute(Type type)` — Constructor

#### class `EpicGames.Core.LogValueFormatter`  
`public static class LogValueFormatter`  
_public; L52-408_
- desc: Utility methods for manipulating formatters
- L276 _private* field_ `static readonly StringFormatter s_stringFormatter = new()`
- L278 _private* field_ `static readonly ConcurrentDictionary<Type, ILogValueFormatter> s_formatters = ...`
- L278 _private* field_ `static readonly ConcurrentDictionary< s_formatters = GetDefaultFormatters()`
- L280-297 _private* method_ `static ConcurrentDictionary<Type, ILogValueFormatter> GetDefaultFormatters()`
- L305-311 _public method_ `public static void WriteTypedValue(Utf8JsonWriter writer, string type, string text)` — Writes a typed
- L318-321 _public method_ `public static void RegisterFormatter(Type type, ILogValueFormatter formatter)` — Registers a formatter for a particular type
- L327-330 _public method_ `public static void RegisterTypeAnnotation<T>(string type)` — Registers a formatter for a particular type that adds a $type field to the serialized output
- L337-353 _public method_ `public static ILogValueFormatter GetFormatter(Type type)` — Gets a formatter for the specified type
- L355-375 _private* method_ `static ILogValueFormatter GetFormatterUncached(Type type)`
- L377-390 _private* method_ `static bool TryGetEnumerableType(Type type, [NotNullWhen(true)] out Type? elementType)`
- L397-407 _public method_ `public static void Format(object? value, Utf8JsonWriter writer)` — Formats a value to a Json log stream

#### class `EpicGames.Core.LogValueFormatter.BoolFormatter`  
`class BoolFormatter : ILogValueFormatter`  
_private*; L54-57_
- inherits: `ILogValueFormatter`
- L56 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.Int32Formatter`  
`class Int32Formatter : ILogValueFormatter`  
_private*; L59-62_
- inherits: `ILogValueFormatter`
- L61 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.UInt32Formatter`  
`class UInt32Formatter : ILogValueFormatter`  
_private*; L64-67_
- inherits: `ILogValueFormatter`
- L66 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.Int64Formatter`  
`class Int64Formatter : ILogValueFormatter`  
_private*; L69-72_
- inherits: `ILogValueFormatter`
- L71 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.UInt64Formatter`  
`class UInt64Formatter : ILogValueFormatter`  
_private*; L74-77_
- inherits: `ILogValueFormatter`
- L76 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.FloatFormatter`  
`class FloatFormatter : ILogValueFormatter`  
_private*; L79-82_
- inherits: `ILogValueFormatter`
- L81 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.DoubleFormatter`  
`class DoubleFormatter : ILogValueFormatter`  
_private*; L84-87_
- inherits: `ILogValueFormatter`
- L86 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.StringFormatter`  
`class StringFormatter : ILogValueFormatter`  
_private*; L89-92_
- inherits: `ILogValueFormatter`
- L91 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.ActivityFormatter`  
`class ActivityFormatter : ILogValueFormatter`  
_private*; L94-123_
- inherits: `ILogValueFormatter`
- L96-101 _public method_ `public void Format(object value, Utf8JsonWriter writer)`
- L103-122 _private* method_ `static void Format(Activity activity, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.EnumerableFormatter`  
`class EnumerableFormatter : ILogValueFormatter`  
_private*; L125-140_
- inherits: `ILogValueFormatter`
- L127 _private* field_ `readonly ILogValueFormatter _elementFormatter`
- L129 _public ctor_ `public EnumerableFormatter(ILogValueFormatter elementFormatter)`
- L131-139 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.StructuredLogValueFormatter`  
`class StructuredLogValueFormatter : ILogValueFormatter`  
_private*; L142-217_
- inherits: `ILogValueFormatter`
- L144-159 _public method_ `public void Format(object value, Utf8JsonWriter writer)`
- L161-216 _private* method_ `static void WritePropertyValue(object? value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.AnnotateTypeFormatter`  
`class AnnotateTypeFormatter : ILogValueFormatter`  
_private*; L219-232_
- inherits: `ILogValueFormatter`
- L221 _private* field_ `readonly Utf8String _type`
- L223 _public ctor_ `public AnnotateTypeFormatter(string type)`
- L225-231 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.DictionaryFormatter`  
`class DictionaryFormatter : ILogValueFormatter`  
_private*; L234-247_
- inherits: `ILogValueFormatter`
- L236-246 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.Utf8DictionaryFormatter`  
`class Utf8DictionaryFormatter : ILogValueFormatter`  
_private*; L249-262_
- inherits: `ILogValueFormatter`
- L251-261 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

#### class `EpicGames.Core.LogValueFormatter.FileReferenceFormatter`  
`class FileReferenceFormatter : ILogValueFormatter`  
_private*; L264-274_
- inherits: `ILogValueFormatter`
- L266-273 _public method_ `public void Format(object value, Utf8JsonWriter writer)`

### `Source/Programs/Shared/EpicGames.Core/Logging/MessageTemplate.cs` (EpicGames.Core)


#### class `EpicGames.Core.MessageTemplate`  
`public static class MessageTemplate`  
_public; L14-296_
- desc: Utility class for dealing with message templates
- L19 _public const_ `public const string FormatPropertyName = "{OriginalFormat}"` — The default property name for the message template format string in an enumerable log state parameter
- L27-32 _public method_ `public static string Render(string format, IEnumerable<KeyValuePair<string, object?>>? properties)` — Renders a format string
- L40-121 _public method_ `public static void Render(string format, IEnumerable<KeyValuePair<string, object?>>? properties, StringBuilder result)` — Renders a format string to the end of a string builder
- L128-133 _public method_ `public static string Escape(string text)` — Escapes a string for use in a message template
- L140-150 _public method_ `public static void Escape(ReadOnlySpan<char> text, StringBuilder result)` — Escapes a span of characters and appends the result to a string
- L157-162 _public method_ `public static string Unescape(string text)` — Unescapes a string from a message template
- L169-180 _public method_ `public static void Unescape(ReadOnlySpan<char> text, StringBuilder result)` — Unescape a string and append the result to a string builder
- L187-214 _public method_ `public static List<(int, int)>? ParsePropertyNames(string format)` — Finds locations of property names from the given format string
- L223-256 _public method_ `public static void ParsePropertyValues(string format, object[] args, Dictionary<string, object?> properties)` — Parse the ordered arguments into a dictionary of named properties
- L265-295 _public method_ `public static bool TryGetPropertyValue(ReadOnlySpan<char> name, IEnumerable<KeyValuePair<string, object?>> properties, out object? value)` — Attempts to get a named property value from the given dictionary

### `Source/Programs/Shared/EpicGames.Core/Logging/PrefixLogger.cs` (EpicGames.Core)


#### class `EpicGames.Core.PrefixLogger`  
`public class PrefixLogger : ILogger`  
_public; L12-52_
- inherits: `ILogger`
- desc: ILogger implementation that adds a prefix to the start of each line
- L14 _private* field_ `readonly string _prefix`
- L15 _private* field_ `readonly ILogger _inner`
- L22-26 _public ctor_ `public PrefixLogger(string prefix, ILogger inner)` — Constructor
- L29 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L32 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L35-51 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/Logging/StartupTraceListener.cs` (EpicGames.Core)


#### class `EpicGames.Core.StartupTraceListener`  
`internal class StartupTraceListener : TraceListener`  
_internal; L11-49_
- inherits: `TraceListener`
- desc: Captures all log output during startup until a log file writer has been created
- L13 _private* field_ `readonly StringBuilder _buffer = new()`
- L19-25 _public method_ `public void CopyTo(TraceListener other)` — Copy the contents of the buffered output to another trace listener
- L31-38 _public method_ `public override void Write(string? message)` — Write a message to the buffer
- L44-48 _public method_ `public override void WriteLine(string? message)` — Write a message to the buffer, followed by a newline

### `Source/Programs/Shared/EpicGames.Core/ManagedProcess.cs` (EpicGames.Core)


#### enum `EpicGames.Core.ManagedProcessFlags`  
`public enum ManagedProcessFlags`  
_public; L23-34_
- attrs: `[Flags]`
- desc: Flags for the managed process
- L28 _public* enumerator_ `None = 0` — No flags
- L33 _public* enumerator_ `MergeOutputPipes = 1` — Merge stdout and stderr

#### class `EpicGames.Core.ManagedProcessGroup`  
`public sealed class ManagedProcessGroup : IDisposable`  
_public; L39-228_
- inherits: `IDisposable`
- desc: Tracks a set of processes, and destroys them when the object is disposed.
- L43 _private* const_ `const uint JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE = 0x00002000`
- L44 _private* const_ `const uint JOB_OBJECT_LIMIT_BREAKAWAY_OK = 0x00000800`
- L96 _private* method_ `static extern SafeFileHandle CreateJobObject(IntPtr securityAttributes, IntPtr name)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L98 _private* const_ `const int JobObjectBasicAccountingInformation = 1`
- L99 _private* const_ `const int JobObjectExtendedLimitInformation = 9`
- L102 _private* method_ `static extern int SetInformationJobObject(SafeFileHandle hJob, int jobObjectInfoClass, IntPtr lpJobObjectInfo, int cbJobObjectInfoLength)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L105 _private* method_ `static extern bool QueryInformationJobObject(SafeFileHandle hJob, int JobObjectInformationClass, out JOBOBJECT_BASIC_ACCOUNTING_INFORMATION lpJobObjectInformation, int cbJobObjectInformationLength, out int lpReturnLength)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L108 _private* method_ `static extern bool QueryInformationJobObject(SafeFileHandle hJob, int JobObjectInformationClass, out JOBOBJECT_EXTENDED_LIMIT_INFORMATION lpJobObjectInformation, int cbJobObjectInformationLength, out int lpReturnLength)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L111 _private* method_ `static extern int AssignProcessToJobObject(SafeFileHandle? hJob, IntPtr hProcess)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L114 _private* method_ `static extern bool IsProcessInJob(IntPtr hProcess, IntPtr hJob, out bool result)` — attrs: `[DllImport("kernel32.dll")]`
- L117 _private* method_ `static extern IntPtr GetCurrentProcess()` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L125-129 _public property_ `public SafeFileHandle? JobHandle { get; set; }` — Handle to the native job object that this process is added to. This handle is closed by the Dispose() method (and will automatically be closed by the OS on process exit), resulting in the child process being killed.
- L134 _internal property_ `internal static bool SupportsJobObjects => ...` — Determines support for using job objects
- L139-167 _public ctor_ `public ManagedProcessGroup(bool bKillOnJobClose = true)` — Constructor
- L173 _public method_ `public void AddProcess(Process process)` — Adds a process to this group
- L179-194 _public method_ `public void AddProcess(IntPtr processHandle)` — Adds a process to this group
- L199 _public property_ `public TimeSpan TotalProcessorTime => ...` — Returns the total CPU time usage for this job.
- L207 _public property_ `public long PeakProcessMemoryUsed => ...` — Returns the the peak memory for a process for this job.
- L215 _public property_ `public long PeakJobMemoryUsed => ...` — Returns the the peak memory for this job.
- L223-227 _public method_ `public void Dispose()` — Dispose of the process group

#### struct `EpicGames.Core.ManagedProcessGroup.JOBOBJECT_BASIC_LIMIT_INFORMATION`  
`struct JOBOBJECT_BASIC_LIMIT_INFORMATION`  
_private*; L47-58_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L49 _public field_ `public Int64 PerProcessUserTimeLimit`
- L50 _public field_ `public Int64 PerJobUserTimeLimit`
- L51 _public field_ `public UInt32 LimitFlags`
- L52 _public field_ `public UIntPtr MinimumWorkingSetSize`
- L53 _public field_ `public UIntPtr MaximumWorkingSetSize`
- L54 _public field_ `public UInt32 ActiveProcessLimit`
- L55 _public field_ `public Int64 Affinity`
- L56 _public field_ `public UInt32 PriorityClass`
- L57 _public field_ `public UInt32 SchedulingClass`

#### struct `EpicGames.Core.ManagedProcessGroup.IO_COUNTERS`  
`struct IO_COUNTERS`  
_private*; L61-69_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L63 _public field_ `public UInt64 ReadOperationCount`
- L64 _public field_ `public UInt64 WriteOperationCount`
- L65 _public field_ `public UInt64 OtherOperationCount`
- L66 _public field_ `public UInt64 ReadTransferCount`
- L67 _public field_ `public UInt64 WriteTransferCount`
- L68 _public field_ `public UInt64 OtherTransferCount`

#### struct `EpicGames.Core.ManagedProcessGroup.JOBOBJECT_EXTENDED_LIMIT_INFORMATION`  
`struct JOBOBJECT_EXTENDED_LIMIT_INFORMATION`  
_private*; L72-80_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L74 _public field_ `public JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation`
- L75 _public field_ `public IO_COUNTERS IoInfo`
- L76 _public field_ `public UIntPtr ProcessMemoryLimit`
- L77 _public field_ `public UIntPtr JobMemoryLimit`
- L78 _public field_ `public UIntPtr PeakProcessMemoryUsed`
- L79 _public field_ `public UIntPtr PeakJobMemoryUsed`

#### struct `EpicGames.Core.ManagedProcessGroup.JOBOBJECT_BASIC_ACCOUNTING_INFORMATION`  
`struct JOBOBJECT_BASIC_ACCOUNTING_INFORMATION`  
_private*; L83-93_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L85 _public field_ `public UInt64 TotalUserTime`
- L86 _public field_ `public UInt64 TotalKernelTime`
- L87 _public field_ `public UInt64 ThisPeriodTotalUserTime`
- L88 _public field_ `public UInt64 ThisPeriodTotalKernelTime`
- L89 _public field_ `public UInt32 TotalPageFaultCount`
- L90 _public field_ `public UInt32 TotalProcesses`
- L91 _public field_ `public UInt32 ActiveProcesses`
- L92 _public field_ `public UInt32 TotalTerminatedProcesses`

#### class `EpicGames.Core.ManagedProcess`  
`public sealed class ManagedProcess : IDisposable`  
_public; L235-1467_
- inherits: `IDisposable`
- desc: Encapsulates a managed child process, from which we can read the console output. Uses job objects to ensure that the process will be terminated automatically by the O/S if the current process is terminated, and polls pipe reads to avoid blocking on unmanaged code if the calling thread is terminated. Currently only implemented for Windows; makes heavy use of P/Invoke.
- L287 _private* method_ `static extern int CloseHandle(IntPtr hObject)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L290 _private* method_ `static extern int CreatePipe(out SafeFileHandle hReadPipe, out SafeFileHandle hWritePipe, SECURITY_ATTRIBUTES lpPipeAttributes, uint nSize)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L293 _private* method_ `static extern int SetHandleInformation(SafeFileHandle hObject, int dwMask, int dwFlags)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L295 _private* const_ `const int HANDLE_FLAG_INHERIT = 1`
- L297 _private* const_ `const int STARTF_USESTDHANDLES = 0x00000100`
- L315 _private* method_ `static extern int CreateProcess( string? lpApplicationName, StringBuilder lpCommandLine, IntPtr lpProcessAttributes, IntPtr lpThreadAttributes, bool bInheritHandles, ProcessCreationFlags dwCreationFlags, IntPtr lpEnvironment, string? lpCurrentDirectory, STARTUPINFOEX lpStartupInfo, PROCESS_INFORMATION lpProcessInformation)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L319 _private* method_ `static extern int ResumeThread(IntPtr hThread)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L322 _private* method_ `static extern IntPtr GetCurrentProcess()` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L324 _private* const_ `const int DUPLICATE_SAME_ACCESS = 2`
- L327 _private* method_ `static extern int DuplicateHandle( IntPtr hSourceProcessHandle, SafeHandle hSourceHandle, IntPtr hTargetProcess, out SafeFileHandle targetHandle, int dwDesiredAccess, [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle, int dwOptions )` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L338 _private* method_ `static extern int GetExitCodeProcess(SafeProcessHandle hProcess, out int lpExitCode)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L341 _private* method_ `static extern int TerminateProcess(SafeHandleZeroOrMinusOneIsInvalid hProcess, uint uExitCode)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L343 _private* const_ `const uint INFINITE = 0xFFFFFFFF`
- L344 _private* const_ `const uint WAIT_FAILED = 0xFFFFFFFF`
- L347 _private* method_ `static extern uint WaitForSingleObject(SafeHandleZeroOrMinusOneIsInvalid hHandle, uint dwMilliseconds)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L351 _private* method_ `static extern bool GetProcessTimes(SafeHandleZeroOrMinusOneIsInvalid hProcess, out System.Runtime.InteropServices.ComTypes.FILETIME lpCreationTime, out System.Runtime.InteropServices.ComTypes.FILETIME lpExitTime, out System.Runtime.InteropServices.ComTypes.FILETIME lpKernelTime, out System.Runtime.InteropServices.ComTypes.FILETIME lpUserTime)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L358 _private* method_ `static extern ushort GetActiveProcessorGroupCount()` — attrs: `[DllImport("kernel32.dll")]`
- L361 _private* method_ `static extern uint GetActiveProcessorCount(ushort GroupNumber)` — attrs: `[DllImport("kernel32.dll")]`
- L374 _private* method_ `static extern int SetThreadGroupAffinity(IntPtr hThread, GROUP_AFFINITY GroupAffinity, GROUP_AFFINITY? PreviousGroupAffinity)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L376 _private* const_ `const int ERROR_ACCESS_DENIED = 5`
- L385-398 _private* method_ `static DateTime FileTimeToDateTime(System.Runtime.InteropServices.ComTypes.FILETIME time)` — Converts FILETIME to DateTime.
- L403 _public property_ `public int Id { get; set; }` — The process id
- L408 _private* field_ `SafeProcessHandle? _processHandle` — Handle for the child process.
- L413 _private* field_ `SafeFileHandle? _stdInWrite` — The write end of the child process' stdin pipe.
- L418 _private* field_ `SafeFileHandle? _stdOutRead` — The read end of the child process' stdout pipe.
- L423 _private* field_ `SafeFileHandle? _stdErrRead` — The read end of the child process' stderr pipe.
- L428 _public property_ `public Stream StdIn { get; set; }` — Input stream for the child process.
- L433 _public property_ `public Stream StdOut { get; set; }` — Output stream for the child process.
- L438 _public property_ `public StreamReader StdOutText { get; set; }` — Reader for the process' output stream.
- L443 _public property_ `public Stream StdErr { get; set; }` — Output stream for the child process.
- L448 _public property_ `public StreamReader StdErrText { get; set; }` — Reader for the process' output stream.
- L453 _private* field_ `Process? _frameworkProcess` — Standard process implementation for non-Windows platforms.
- L458 _private* field_ `Task? _frameworkOutputTask` — Task to read from stdout and stderr
- L463 _private* field_ `Channel<ChannelBuffer>? _frameworkChannel` — Merged output and error write stream for the framework child process. We use a channel rather than a pipe here to support cancellation, which is not supported by async pipes on Windows.
- L468 _private* field_ `ObjectPool<ChannelBuffer>? _frameworkBufferPool` — Pool of buffer objects output from the framework
- L474 _private* field_ `CancellationTokenSource? _frameworkCancellationSource` — Cancellation token for background threads
- L481 _private* field_ `static readonly Lock s_lockObject = new()` — Static lock object. This is used to synchronize the creation of child processes - in particular, the inheritance of stdout/stderr write pipes. If processes inherit pipes meant for other processes, they won't be closed until both terminate.
- L486 _private* field_ `ManagedProcessGroup? _accountingProcessGroup` — Used to perform CPU usage and resource accounting of all children process involved in a single compilation unit.
- L488 _private* field_ `byte[] _buffer = []`
- L489 _private* field_ `int _bufferPos = 0`
- L490 _private* field_ `int _bufferLen = 0`
- L491 _private* field_ `bool _bCarriageReturn = false`
- L570-578 _public ctor_ `public ManagedProcess(ManagedProcessGroup? group, string fileName, string commandLine, string? workingDirectory, IReadOnlyDictionary<string, string>? environment, byte[]? input, ProcessPriorityClass priority, AppContainer? appContainer = null, ManagedProcessFlags flags = ManagedProcessFlags.MergeOutputPipes) : this(group, fileName, commandLine, workingDirectory, environment, priority, appContainer, flags)` — Spawns a new managed process.
- L591-611 _public ctor_ `public ManagedProcess(ManagedProcessGroup? group, string fileName, string commandLine, string? workingDirectory, IReadOnlyDictionary<string, string>? environment, ProcessPriorityClass priority, AppContainer? appContainer = null, ManagedProcessFlags flags = ManagedProcessFlags.MergeOutputPipes)` — Spawns a new managed process.
- L613 _private* field_ `static readonly int s_processorGroupCount = GetActiveProcessorGroupCount()`
- L618 _private* field_ `static int s_processorGroupCounter = 0` — A counter used to decide which processor group the next process should be assigned to
- L631-852 _private method_ `private void CreateManagedProcessWin32(ManagedProcessGroup? group, string fileName, string commandLine, string? workingDirectory, IReadOnlyDictionary<string, string>? environment, ProcessPriorityClass priority, AppContainer? appContainer, ManagedProcessFlags? managedFlags)` — Spawns a new managed process using Win32 native functions.
- L863-934 _private method_ `private void CreateManagedProcessPortable(string fileName, string commandLine, string? workingDirectory, IReadOnlyDictionary<string, string>? environment, ProcessPriorityClass priority, ManagedProcessFlags flags)` — Spawns a new managed process using Win32 native functions.
- L942-957 _private* method_ `async Task CopyPipeAsync(Stream source, ChannelWriter<ChannelBuffer> target, CancellationToken cancellationToken)` — Copy data from one pipe to another.
- L962-1010 _public method_ `public void Dispose()` — Free the managed resources for this process
- L1019-1028 _public method_ `public int Read(byte[] buffer, int offset, int count)` — Reads data from the process output
- L1038-1041 _public method_ `public async ValueTask<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)` — Reads data from the process output
- L1049-1052 _public method_ `public Task CopyToAsync(Stream outputStream, CancellationToken cancellationToken)` — Copy the process output to the given stream
- L1061-1069 _public method_ `public Task CopyToAsync(Action<byte[], int, int> writeOutput, int bufferSize, CancellationToken cancellationToken)` — Copy the process output to the given stream
- L1078-1100 _public method_ `public async Task CopyToAsync(Func<byte[], int, int, CancellationToken, Task> writeOutputAsync, int bufferSize, CancellationToken cancellationToken)` — Copy the process output to the given stream
- L1107-1160 _public method_ `public async ValueTask<string?> ReadLineAsync(CancellationToken cancellationToken = default)` — Reads an individual line from the process
- L1166-1217 _public method_ `public List<string> ReadAllLines()` — Read all the output from the process. Does not return until the process terminates.
- L1223-1226 _public method_ `public async Task<string?> ReadLineAsync()` — Reads a single line asynchronously
- L1231 _public property_ `public TimeSpan TotalProcessorTime => ...` — Total amount of time spent by the CPU
- L1236 _public property_ `public long PeakMemoryUsed => ...` — Peak memory used
- L1244-1268 _public method_ `public bool TryReadLine([NotNullWhen(true)] out string? line, CancellationToken? token = null)` — Block until the process outputs a line of text, or terminates.
- L1274-1287 _public method_ `public void WaitForExit()` — Waits for the process to exit
- L1300-1311 _public method_ `public async Task WaitForExitAsync(CancellationToken cancellationToken = default)` — Waits for the process to exit
- L1316-1334 _public property_ `public int ExitCode { get; }` — The exit code of the process. Throws an exception if the process has not terminated.
- L1336 _private field_ `private DateTime _frameworkStartTime = DateTime.MinValue`
- L1337 _private field_ `private DateTime _frameworkExitTime = DateTime.MinValue`
- L1342-1360 _public property_ `public DateTime StartTime { get; }` — The creation time of the process.
- L1365-1383 _public property_ `public DateTime ExitTime { get; }` — The exit time of the process. Throws an exception if the process has not terminated.
- L1388-1414 _public property_ `public bool HasExited { get; }` — Returns true if the process has exited
- L1420-1433 _public method_ `public static Dictionary<string, string> GetCurrentEnvVars()` — Gets all the current environment variables
- L1439-1466 _public method_ `public void Kill(bool killDescendants = true)` — Kill the process if it's still running, optionally kill child processes

#### class `EpicGames.Core.ManagedProcess.SECURITY_ATTRIBUTES`  
`class SECURITY_ATTRIBUTES`  
_private*; L240-245_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L242 _public field_ `public int nLength`
- L243 _public field_ `public IntPtr lpSecurityDescriptor`
- L244 _public field_ `public int bInheritHandle`

#### class `EpicGames.Core.ManagedProcess.PROCESS_INFORMATION`  
`class PROCESS_INFORMATION`  
_private*; L248-254_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L250 _public field_ `public IntPtr hProcess`
- L251 _public field_ `public IntPtr hThread`
- L252 _public field_ `public uint dwProcessId`
- L253 _public field_ `public uint dwThreadId`

#### class `EpicGames.Core.ManagedProcess.STARTUPINFO`  
`class STARTUPINFO`  
_private*; L257-277_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L259 _public field_ `public int cb`
- L260 _public field_ `public string? lpReserved`
- L261 _public field_ `public string? lpDesktop`
- L262 _public field_ `public string? lpTitle`
- L263 _public field_ `public uint dwX`
- L264 _public field_ `public uint dwY`
- L265 _public field_ `public uint dwXSize`
- L266 _public field_ `public uint dwYSize`
- L267 _public field_ `public uint dwXCountChars`
- L268 _public field_ `public uint dwYCountChars`
- L269 _public field_ `public uint dwFillAttribute`
- L270 _public field_ `public uint dwFlags`
- L271 _public field_ `public short wShowWindow`
- L272 _public field_ `public short cbReserved2`
- L273 _public field_ `public IntPtr lpReserved2`
- L274 _public field_ `public SafeHandle? hStdInput`
- L275 _public field_ `public SafeHandle? hStdOutput`
- L276 _public field_ `public SafeHandle? hStdError`

#### class `EpicGames.Core.ManagedProcess.STARTUPINFOEX`  
`class STARTUPINFOEX`  
_private*; L280-284_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L282 _public field_ `public STARTUPINFO? StartupInfo`
- L283 _public field_ `public IntPtr lpAttributeList`

#### enum `EpicGames.Core.ManagedProcess.ProcessCreationFlags`  
`enum ProcessCreationFlags : int`  
_private*; L300-311_
- attrs: `[Flags]`
- inherits: `int`
- L302 _public* enumerator_ `CREATE_NO_WINDOW = 0x08000000`
- L303 _public* enumerator_ `CREATE_SUSPENDED = 0x00000004`
- L304 _public* enumerator_ `NORMAL_PRIORITY_CLASS = 0x00000020`
- L305 _public* enumerator_ `IDLE_PRIORITY_CLASS = 0x00000040`
- L306 _public* enumerator_ `HIGH_PRIORITY_CLASS = 0x00000080`
- L307 _public* enumerator_ `REALTIME_PRIORITY_CLASS = 0x00000100`
- L308 _public* enumerator_ `BELOW_NORMAL_PRIORITY_CLASS = 0x00004000`
- L309 _public* enumerator_ `ABOVE_NORMAL_PRIORITY_CLASS = 0x00008000`
- L310 _public* enumerator_ `EXTENDED_STARTUPINFO_PRESENT = 0x00080000`

#### class `EpicGames.Core.ManagedProcess.GROUP_AFFINITY`  
`class GROUP_AFFINITY`  
_private*; L364-371_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L366 _public field_ `public ulong Mask`
- L367 _public field_ `public ushort Group`
- L368 _public field_ `public ushort Reserved0`
- L369 _public field_ `public ushort Reserved1`
- L370 _public field_ `public ushort Reserved2`

#### class `EpicGames.Core.ManagedProcess.ChannelBuffer`  
`class ChannelBuffer`  
_private*; L493-497_
- L495 _public field_ `public byte[] _data = new byte[1024]`
- L496 _public field_ `public int _length = 0`

#### class `EpicGames.Core.ManagedProcess.ChannelReadStream`  
`class ChannelReadStream : Stream`  
_private*; L499-556_
- inherits: `Stream`
- L501 _private* field_ `readonly ChannelReader<ChannelBuffer> _reader`
- L502 _private* field_ `readonly ObjectPool<ChannelBuffer> _bufferPool`
- L504 _private* field_ `ChannelBuffer? _currentBuf = null`
- L505 _private* field_ `int _currentPos = 0`
- L507-511 _public ctor_ `public ChannelReadStream(ChannelReader<ChannelBuffer> reader, ObjectPool<ChannelBuffer> bufferPool)`
- L513 _public property_ `public override bool CanRead => ...`
- L514 _public property_ `public override bool CanSeek => ...`
- L515 _public property_ `public override bool CanWrite => ...`
- L516 _public property_ `public override long Length => ...`
- L517 _public property_ `public override long Position { get; set; }`
- L518 _public method_ `public override void Flush()`
- L519 _public method_ `public override long Seek(long offset, SeekOrigin origin)`
- L520 _public method_ `public override void SetLength(long value)`
- L521 _public method_ `public override void Write(byte[] buffer, int offset, int count)`
- L523-528 _public method_ `public override int Read(byte[] buffer, int offset, int count)`
- L530-555 _public method_ `public override async ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken)`

#### class `EpicGames.Core.ManagedProcess.ProcessWaitHandle`  
`class ProcessWaitHandle : WaitHandle`  
_private*; L1289-1295_
- inherits: `WaitHandle`
- L1291-1294 _public ctor_ `public ProcessWaitHandle(SafeProcessHandle processHandle)`

### `Source/Programs/Shared/EpicGames.Core/Md5Hash.cs` (EpicGames.Core)


#### struct `EpicGames.Core.Md5Hash`  
`public readonly struct Md5Hash : IEquatable<Md5Hash>, IComparable<Md5Hash>`  
_public; L18-165_
- attrs: `[TypeConverter(typeof(Md5HashTypeConverter))]`
- inherits: `IEquatable<Md5Hash>, IComparable<Md5Hash>`
- desc: Struct representing a strongly typed Md5Hash value
- L23 _public const_ `public const int NumBytes = 16` — Length of an Md5Hash
- L28 _public const_ `public const int NumBits = NumBytes * 8` — Length of the hash in bits
- L33 _public property_ `public ReadOnlyMemory<byte> Memory { get; }` — Memory storing the digest data
- L38 _public property_ `public ReadOnlySpan<byte> Span => ...` — Span for the underlying memory
- L43 _public property_ `public static Md5Hash Zero { get; }` — Hash consisting of zeroes
- L49-57 _public ctor_ `public Md5Hash(ReadOnlyMemory<byte> memory)` — Constructor
- L64-72 _public method_ `public static Md5Hash Compute(ReadOnlySpan<byte> data)` — Creates a content hash for a block of data, using a given algorithm.
- L79-85 _public method_ `public static Md5Hash Compute(Stream stream)` — Creates a content hash for the input Stream object
- L92-95 _public method_ `public static Md5Hash Parse(string text)` — Parses a digest from the given hex string
- L102-105 _public method_ `public static Md5Hash Parse(Utf8String text)` — Parses a digest from the given hex string
- L108-122 _public method_ `public int CompareTo(Md5Hash other)` — (inheritdoc)
- L125 _public method_ `public bool Equals(Md5Hash other)` — (inheritdoc)
- L128 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L131 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L134 _public method_ `public override string ToString()` — (inheritdoc)
- L139 _public operator_ `public static bool operator ==(Md5Hash a, Md5Hash b)` — Test two hash values for equality
- L144 _public operator_ `public static bool operator !=(Md5Hash a, Md5Hash b)` — Test two hash values for equality
- L149 _public operator_ `public static bool operator >(Md5Hash a, Md5Hash b)` — Tests whether A > B
- L154 _public operator_ `public static bool operator <(Md5Hash a, Md5Hash b)` — Tests whether A is less than B
- L159 _public operator_ `public static bool operator >=(Md5Hash a, Md5Hash b)` — Tests whether A is greater than or equal to B
- L164 _public operator_ `public static bool operator <=(Md5Hash a, Md5Hash b)` — Tests whether A is less than or equal to B

#### class `EpicGames.Core.Md5HashExtensions`  
`public static class Md5HashExtensions`  
_public; L170-191_
- desc: Extension methods for dealing with Md5Hash values
- L177-180 _public method_ `public static Md5Hash ReadMd5Hash(this MemoryReader reader)` — Read an Md5Hash from a memory reader
- L187-190 _public method_ `public static void WriteMd5Hash(this MemoryWriter writer, Md5Hash hash)` — Write an Md5Hash to a memory writer

#### class `EpicGames.Core.Md5HashTypeConverter`  
`sealed class Md5HashTypeConverter : TypeConverter`  
_internal*; L196-209_
- inherits: `TypeConverter`
- desc: Type converter from strings to Md5Hash objects
- L199-202 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L205-208 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/MemoryMappedFileCache.cs` (EpicGames.Core)


#### class `EpicGames.Core.MemoryMappedFileCache`  
`public sealed class MemoryMappedFileCache : IDisposable`  
_public; L16-302_
- inherits: `IDisposable`
- desc: Manages a cache of memory mapped file handles
- L151 _private* field_ `readonly Lock _lockObject = new()`
- L152 _private* field_ `readonly Dictionary<FileReference, MappedFile> _pathToMappedFile = ...`
- L152 _private* field_ `readonly Dictionary< _pathToMappedFile = []`
- L153 _private* field_ `readonly LinkedList<MappedFile> _mappedFiles = new()`
- L155 _private* field_ `long _mappedSize`
- L157 _private* field_ `readonly long _maxMappedSize`
- L158 _private* field_ `readonly int _maxMappedCount`
- L165-169 _public ctor_ `public MemoryMappedFileCache(long maxMappedSize = 1024L * 1024 * 1024, int maxMappedCount = 128)` — Constructor
- L174-180 _public method_ `public void Clear()` — Removes any cached files
- L183 _public method_ `public void Dispose()` — (inheritdoc)
- L192-203 _public method_ `public IReadOnlyMemoryOwner<byte> Read(FileReference file, int offset, int? length)` — Maps data for a file into memory
- L209-228 _public method_ `public void Delete(FileReference file)` — Delete a file from the store
- L233-259 _private* method_ `MappedFile? FindOrAddMappedFile(FileReference key)` — Finds an existing mapped file or adds a new one for the given path
- L266-279 _private* method_ `void UnmapFiles(long maxMappedSize, int maxMappedCount)` — Discard mapped files until only a certain size is mapped in memory
- L284-301 _public method_ `public void WriteRefStats(ILogger logger)` — Prints stats about the number of outstanding references to items in the cache

#### class `EpicGames.Core.MemoryMappedFileCache.MappedFile`  
`class MappedFile : IDisposable`  
_private*; L19-116_
- inherits: `IDisposable`
- L21 _public property_ `public FileReference Key { get; }`
- L22 _public property_ `public LinkedListNode<MappedFile> ListNode { get; }`
- L24 _private* field_ `readonly MemoryMappedFileCache _cache`
- L25 _private* field_ `readonly FileInfo _fileInfo`
- L27 _private* field_ `MemoryMappedFile? _memoryMappedFile`
- L28 _private* field_ `MemoryMappedViewAccessor? _memoryMappedViewAccessor`
- L29 _private* field_ `MemoryMappedView? _memoryMappedView`
- L31 _private* field_ `int _refCount = 1`
- L32 _private* field_ `ReadOnlyMemory<byte> _data`
- L33 _private* field_ `bool _deleteOnDispose`
- L35 _public property_ `public int RefCount => ...`
- L37 _public property_ `public ulong MappedSize => ...`
- L39-62 _public ctor_ `public MappedFile(MemoryMappedFileCache cache, FileReference locator, FileInfo fileInfo)`
- L64-83 _public method_ `public void Dispose()`
- L85-95 _public method_ `public ReadOnlyMemory<byte> GetData(int offset, int? length)`
- L97-100 _public method_ `public void AddRef()`
- L102-108 _public method_ `public void Release()`
- L110-113 _public method_ `public void DeleteOnDispose()`
- L115 _public method_ `public override string ToString()`

#### class `EpicGames.Core.MemoryMappedFileCache.MappedFileHandle`  
`class MappedFileHandle : IReadOnlyMemoryOwner<byte>`  
_private*; L119-149_
- inherits: `IReadOnlyMemoryOwner<byte>`
- L121 _private* field_ `MappedFile? _mappedFile`
- L122 _private* field_ `ReadOnlyMemory<byte> _data`
- L124 _public property_ `public ReadOnlyMemory<byte> Memory => ...`
- L126-131 _public ctor_ `public MappedFileHandle(MappedFile? mappedFile, ReadOnlyMemory<byte> data)`
- L133-137 _public method_ `public MappedFileHandle Clone()`
- L139-148 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.Core/MemoryMappedView.cs` (EpicGames.Core)


#### class `EpicGames.Core.MemoryMappedView`  
`public sealed unsafe class MemoryMappedView : IDisposable`  
_public; L16-141_
- inherits: `IDisposable`
- desc: Implements an unmarshlled view of a memory mapped file
- L42 _private* const_ `const uint FILE_MAP_COPY = 0x0001`
- L43 _private* const_ `const uint FILE_MAP_WRITE = 0x0002`
- L44 _private* const_ `const uint FILE_MAP_READ = 0x0004`
- L45 _private* const_ `const uint FILE_MAP_EXECUTE = 0x0020`
- L48 _private* method_ `static extern unsafe void* MapViewOfFile(SafeMemoryMappedFileHandle handle, uint desiredAccess, uint fileOffsetHigh, uint fileOffsetLow, long numberOfBytes)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L51 _private* method_ `static extern unsafe bool UnmapViewOfFile(void* ptr)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L53 _private* field_ `byte* _data`
- L54 _private* field_ `Action? _disposeMethod`
- L63-102 _public ctor_ `public MemoryMappedView(MemoryMappedFile memoryMappedFile, long offset, long length, MemoryMappedFileAccess access = MemoryMappedFileAccess.ReadWrite)` — Create a view of a memory mapped file
- L108-112 _public ctor_ `public MemoryMappedView(MemoryMappedViewAccessor memoryMappedViewAccessor)` — Constructor
- L117 _public method_ `public byte* GetPointer()` — Gets a pointer to the data
- L125-129 _public method_ `public Memory<byte> GetMemory(long offset, int length)` — Gets a memory object for the given range
- L132-140 _public method_ `public void Dispose()` — (inheritdoc)

#### class `EpicGames.Core.MemoryMappedView.MemoryWrapper`  
`sealed unsafe class MemoryWrapper : MemoryManager<byte>`  
_private*; L18-40_
- inherits: `MemoryManager<byte>`
- L20 _private field_ `private readonly byte* _pointer`
- L21 _private field_ `private readonly int _length`
- L23-27 _public ctor_ `public MemoryWrapper(byte* pointer, int length)`
- L30 _public method_ `public override Span<byte> GetSpan()` — (inheritdoc)
- L33 _public method_ `public override MemoryHandle Pin(int elementIndex)` — (inheritdoc)
- L36 _public method_ `public override void Unpin()` — (inheritdoc)
- L39 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/MemoryReader.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IMemoryReader`  
`public interface IMemoryReader`  
_public; L13-27_
- desc: Interface for reading from data in memory
- L20 _public* method_ `ReadOnlyMemory<byte> GetMemory(int minSize = 1)` — Gets a block of memory with at least the given size
- L26 _public* method_ `void Advance(int length)` — Updates the current position within the input buffer

#### class `EpicGames.Core.MemoryReader`  
`public class MemoryReader : IMemoryReader`  
_public; L32-72_
- inherits: `IMemoryReader`
- desc: Reads data from a memory buffer
- L37-40 _public property_ `public ReadOnlyMemory<byte> RemainingMemory { get; set; }` — The memory to read from
- L45 _public property_ `public ReadOnlySpan<byte> RemainingSpan => ...` — Returns the memory at the current offset
- L51-54 _public ctor_ `public MemoryReader(ReadOnlyMemory<byte> memory)` — Constructor
- L59-65 _public method_ `public void CheckEmpty()` — Checks that we've used the exact buffer length
- L68 _public method_ `public ReadOnlyMemory<byte> GetMemory(int minSize)` — (inheritdoc)
- L71 _public method_ `public void Advance(int length)` — (inheritdoc)

#### class `EpicGames.Core.MemoryReaderExtensions`  
`public static class MemoryReaderExtensions`  
_public; L77-509_
- desc: Extension methods for IMemoryReader
- L85 _public method_ `public static ReadOnlySpan<byte> GetSpan(this IMemoryReader reader, int minSize)` — Gets a span of data with the given length
- L92-95 _public method_ `public static bool ReadBoolean(this IMemoryReader reader)` — Read a boolean from the buffer
- L102-107 _public method_ `public static sbyte ReadInt8(this IMemoryReader reader)` — Reads a byte from the buffer
- L114-119 _public method_ `public static byte ReadUInt8(this IMemoryReader reader)` — Reads a byte from the buffer
- L126-131 _public method_ `public static short ReadInt16(this IMemoryReader reader)` — Reads an int16
- L138-143 _public method_ `public static ushort ReadUInt16(this IMemoryReader reader)` — Reads a uint16
- L150-155 _public method_ `public static int ReadInt32(this IMemoryReader reader)` — Reads an int32
- L162-167 _public method_ `public static uint ReadUInt32(this IMemoryReader reader)` — Reads a uint32
- L174-179 _public method_ `public static long ReadInt64(this IMemoryReader reader)` — Reads an int64
- L186-191 _public method_ `public static ulong ReadUInt64(this IMemoryReader reader)` — Reads an int64
- L197-201 _public method_ `public static DateTime ReadDateTime(this IMemoryReader reader)` — Reads a DateTime from the memory buffer
- L207-212 _public method_ `public static Guid ReadGuidNetOrder(this IMemoryReader reader)` — Reads a GUID from the memory buffer using NET-ordered serialization.
- L218-223 _public method_ `public static Guid ReadGuidUnrealOrder(this IMemoryReader reader)` — Reads a GUID from the memory buffer using UE-ordered serialization.
- L230-234 _public method_ `public static ReadOnlyMemory<byte> ReadVariableLengthBytes(this IMemoryReader reader)` — Reads a sequence of bytes from the buffer
- L240-244 _public method_ `public static ReadOnlyMemory<byte> ReadVariableLengthBytesWithInt32Length(this IMemoryReader reader)` — Writes a variable length span of bytes
- L252-257 _public method_ `public static ReadOnlyMemory<byte> ReadFixedLengthBytes(this IMemoryReader reader, int length)` — Reads a sequence of bytes from the buffer
- L265-274 _public method_ `public static void ReadList<T>(this IMemoryReader reader, List<T> list, Func<T> readItem)` — Reads a variable length list
- L281-286 _public method_ `public static List<T> ReadList<T>(this IMemoryReader reader, Func<T> readItem)` — Reads a variable length list
- L293-304 _public method_ `public static List<T> ReadList<T>(this IMemoryReader reader, Func<IMemoryReader, T> readItem)` — Reads a variable length list
- L311-315 _public method_ `public static T[] ReadVariableLengthArray<T>(this IMemoryReader reader, Func<T> readItem)` — Reads a variable length array
- L322-326 _public method_ `public static T[] ReadVariableLengthArray<T>(this IMemoryReader reader, Func<IMemoryReader, T> readItem)` — Reads a variable length array
- L333-337 _public method_ `public static T[] ReadVariableLengthArrayWithInt32Length<T>(this IMemoryReader reader, Func<T> readItem)` — Reads a variable length array
- L346-359 _public method_ `public static T[] ReadFixedLengthArray<T>(this IMemoryReader reader, int length, Func<T> readItem)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter")]` — Writes a fixed length array
- L367-380 _public method_ `public static T[] ReadFixedLengthArray<T>(this IMemoryReader reader, int length, Func<IMemoryReader, T> readItem)` — Writes a fixed length array
- L389-400 _public method_ `public static void ReadDictionary<TKey, TValue>(this IMemoryReader reader, Dictionary<TKey, TValue> dictionary, Func<TKey> readKey, Func<TValue> readValue) where TKey : notnull` — Reads a dictionary from the writer
- L409-420 _public method_ `public static void ReadDictionary<TKey, TValue>(this IMemoryReader reader, Dictionary<TKey, TValue> dictionary, Func<IMemoryReader, TKey> readKey, Func<IMemoryReader, TValue> readValue) where TKey : notnull` — Reads a dictionary from the writer
- L429-434 _public method_ `public static Dictionary<TKey, TValue> ReadDictionary<TKey, TValue>(this IMemoryReader reader, Func<TKey> readKey, Func<TValue> readValue, IEqualityComparer<TKey>? comparer = null) where TKey : notnull` — Reads a dictionary from the writer
- L443-448 _public method_ `public static Dictionary<TKey, TValue> ReadDictionary<TKey, TValue>(this IMemoryReader reader, Func<IMemoryReader, TKey> readKey, Func<IMemoryReader, TValue> readValue, IEqualityComparer<TKey>? comparer = null) where TKey : notnull` — Reads a dictionary from the writer
- L455 _public method_ `public static string ReadString(this IMemoryReader reader)` — Read a string from memory
- L463-476 _public method_ `public static string ReadString(this IMemoryReader reader, Encoding encoding)` — Read a string from memory
- L483 _public method_ `public static string? ReadOptionalString(this IMemoryReader reader)` — Read a string from memory
- L491-508 _public method_ `public static string? ReadOptionalString(this IMemoryReader reader, Encoding encoding)` — Read a string from memory

### `Source/Programs/Shared/EpicGames.Core/MemoryReaderStream.cs` (EpicGames.Core)


#### class `EpicGames.Core.MemoryReaderStream`  
`public class MemoryReaderStream : Stream`  
_public; L11-74_
- inherits: `Stream`
- desc: Implementation of Stream which reads data from a IMemoryReader
- L13 _private* field_ `readonly IMemoryReader _reader`
- L18-21 _public ctor_ `public MemoryReaderStream(IMemoryReader reader)` — Constructor
- L24 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L27 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L30 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L33 _public property_ `public override long Length => ...` — (inheritdoc)
- L36 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L39 _public method_ `public override void Flush()` — (inheritdoc)
- L42-61 _public method_ `public override int Read(Span<byte> buffer)` — (inheritdoc)
- L64 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L67 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L70 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L73 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/MemoryWriter.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IMemoryWriter`  
`public interface IMemoryWriter : IBufferWriter<byte>`  
_public; L17-23_
- inherits: `IBufferWriter<byte>`
- desc: Interface for serializing to a memory buffer
- L22 _public* property_ `int Length { get; }` — Length of the written data

#### class `EpicGames.Core.MemoryWriter`  
`public class MemoryWriter : IMemoryWriter`  
_public; L28-76_
- inherits: `IMemoryWriter`
- desc: Writes into a fixed size memory block
- L33 _private* field_ `readonly Memory<byte> _memory` — The memory block to write to
- L38 _private* field_ `int _length` — Length of the data that has been written
- L43 _public property_ `public ReadOnlyMemory<byte> WrittenMemory => ...` — Returns the memory that was written to
- L49-52 _public ctor_ `public MemoryWriter(Memory<byte> memory)` — Constructor
- L57-63 _public method_ `public void CheckEmpty()` — Checks that we've used the exact buffer length
- L66 _public property_ `public int Length => ...` — (inheritdoc)
- L69 _public method_ `public Span<byte> GetSpan(int sizeHint)` — (inheritdoc)
- L72 _public method_ `public Memory<byte> GetMemory(int sizeHint)` — (inheritdoc)
- L75 _public method_ `public void Advance(int length)` — (inheritdoc)

#### class `EpicGames.Core.ArrayMemoryWriter`  
`public class ArrayMemoryWriter : IMemoryWriter`  
_public; L81-148_
- inherits: `IMemoryWriter`
- desc: Writes into an expandable memory block
- L83 _private* field_ `byte[] _data`
- L84 _private* field_ `int _length`
- L89 _public property_ `public Span<byte> WrittenSpan => ...` — Returns the span that has been written to
- L94 _public property_ `public Memory<byte> WrittenMemory => ...` — Returns the memory that has been written to
- L100-103 _public ctor_ `public ArrayMemoryWriter(int initialSize)` — Constructor
- L106 _public property_ `public int Length => ...` — (inheritdoc)
- L111-114 _public method_ `public void Clear()` — Resets the current contents of the buffer
- L120-127 _public method_ `public void Resize(int newLength)` — Resize the underlying buffer, updating the current length.
- L130 _public method_ `public Span<byte> GetSpan(int sizeHint = 0)` — (inheritdoc)
- L133-141 _public method_ `public Memory<byte> GetMemory(int minSize = 0)` — (inheritdoc)
- L144-147 _public method_ `public void Advance(int length)` — (inheritdoc)

#### class `EpicGames.Core.PooledMemoryWriter`  
`public class PooledMemoryWriter : IMemoryWriter, IDisposable`  
_public; L153-253_
- inherits: `IMemoryWriter, IDisposable`
- desc: Writes into an expandable memory block
- L155 _private* field_ `readonly MemoryPool<byte> _pool`
- L156 _private* field_ `IMemoryOwner<byte> _owner`
- L157 _private* field_ `Memory<byte> _memory`
- L158 _private* field_ `int _length`
- L163 _public property_ `public Span<byte> WrittenSpan => ...` — Returns the span that has been written to
- L168 _public property_ `public Memory<byte> WrittenMemory => ...` — Returns the memory that has been written to
- L174-177 _public ctor_ `public PooledMemoryWriter(int initialSize = 4096) : this(MemoryPool<byte>.Shared, initialSize)` — Constructor
- L184-188 _public ctor_ `public PooledMemoryWriter(MemoryPool<byte> pool, int initialSize = 4096)` — Constructor
- L191-195 _public method_ `public void Dispose()` — (inheritdoc)
- L201-204 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method
- L207 _public property_ `public int Length => ...` — (inheritdoc)
- L212-215 _public method_ `public void Clear()` — Resets the current contents of the buffer
- L220-228 _public method_ `public void Clear(int minSize)` — Resets the current contents of the buffer
- L231 _public method_ `public Span<byte> GetSpan(int sizeHint = 0)` — (inheritdoc)
- L234-246 _public method_ `public Memory<byte> GetMemory(int minSize = 0)` — (inheritdoc)
- L249-252 _public method_ `public void Advance(int length)` — (inheritdoc)

#### class `EpicGames.Core.ChunkedMemoryWriterBase`  
`public abstract class ChunkedMemoryWriterBase : IMemoryWriter`  
_public; L258-481_
- inherits: `IMemoryWriter`
- desc: Class for building byte sequences, similar to StringBuilder. Allocates memory in chunks to avoid copying data.
- L305 _private* field_ `readonly List<Chunk> _chunks = []`
- L306 _private* field_ `readonly int _chunkSize`
- L307 _private* field_ `Chunk _currentChunk`
- L312 _protected property_ `protected IReadOnlyList<Chunk> Chunks => ...` — Accessor for the allocated chunks
- L317 _public property_ `public int Length { get; set; }` — Length of the current sequence
- L322-327 _protected ctor_ `protected ChunkedMemoryWriterBase(Chunk initialChunk, int chunkSize)` — Constructor
- L332 _protected method_ `protected abstract Chunk CreateChunk(int runningIndex, int size)` — Creates a new chunk for the buffer
- L337-346 _public method_ `public void Clear()` — Clear the current builder
- L349 _public method_ `public Span<byte> GetSpan(int minSize)` — (inheritdoc)
- L352 _public method_ `public Memory<byte> GetMemory(int sizeHint)` — (inheritdoc)
- L361-384 _public method_ `public Memory<byte> GetMemory(int usedSize, int desiredSize)` — Gets a block of memory to write to, preserving existing (but uncommitted) data in previously returned buffers.
- L387-396 _public method_ `public void Advance(int length)` — (inheritdoc)
- L402-408 _public method_ `public void AppendTo(ReadOnlySequenceBuilder<byte> builder)` — Appends data in this builder to the given sequence
- L414-419 _public method_ `public ReadOnlySequence<byte> AsSequence()` — Gets a sequence representing the bytes that have been written so far
- L426-430 _public method_ `public ReadOnlySequence<byte> AsSequence(int offset)` — Gets a sequence representing the bytes that have been written so far, starting at the given offset
- L438-443 _public method_ `public ReadOnlySequence<byte> AsSequence(int offset, int length)` — Gets a sequence representing the bytes that have been written so far, starting at the given offset and
- L449-456 _public method_ `public void CopyTo(Span<byte> span)` — Copies the data to the given output span
- L463-469 _public method_ `public async Task CopyToAsync(Stream stream, CancellationToken cancellationToken = default)` — Copies the data to a stream
- L475-480 _public method_ `public byte[] ToByteArray()` — Create a byte array from the sequence

#### class `EpicGames.Core.ChunkedMemoryWriterBase.Chunk`  
`protected class Chunk`  
_protected; L263-303_
- desc: Describes a chunk of data in the output stream
- L268 _public property_ `public int RunningIndex { get; }` — Start position in the sequence
- L273 _public property_ `public Memory<byte> Data { get; }` — Data for this chunk
- L278 _public property_ `public int Length { get; set; }` — Used length of the chunk
- L283-287 _public ctor_ `public Chunk(int runningIndex, Memory<byte> data)` — Constructor
- L292 _public method_ `public virtual void Release()` — Release any resources managed by this chunk. Note that ChunkedMemoryWriterBase does not implement IDisposable directly; derived classes should call Clear() on Dispose() if needed.
- L297 _public property_ `public ReadOnlySpan<byte> WrittenSpan => ...` — Span that has been written to
- L302 _public property_ `public ReadOnlyMemory<byte> WrittenMemory => ...` — Memory that has been written to

#### class `EpicGames.Core.ChunkedArrayMemoryWriter`  
`public sealed class ChunkedArrayMemoryWriter : ChunkedMemoryWriterBase`  
_public; L486-507_
- inherits: `ChunkedMemoryWriterBase`
- desc: Class for building byte sequences, similar to StringBuilder. Allocates memory in chunks to avoid copying data.
- L492-494 _public ctor_ `public ChunkedArrayMemoryWriter(int chunkSize = 4096) : this(chunkSize, chunkSize)` — Constructor
- L501-503 _public ctor_ `public ChunkedArrayMemoryWriter(int initialChunkSize, int nextChunkSize) : base(new Chunk(0, new byte[initialChunkSize]), nextChunkSize)` — Constructor
- L506 _protected method_ `protected override Chunk CreateChunk(int runningIndex, int size)` — (inheritdoc)

#### class `EpicGames.Core.ChunkedMemoryWriter`  
`public sealed class ChunkedMemoryWriter : ChunkedMemoryWriterBase, IDisposable`  
_public; L512-567_
- inherits: `ChunkedMemoryWriterBase, IDisposable`
- desc: Class for building byte sequences, similar to StringBuilder. Allocates memory in chunks using a pool allocator to avoid copying data.
- L527 _private* field_ `readonly IMemoryAllocator<byte> _allocator`
- L533-535 _public ctor_ `public ChunkedMemoryWriter(int chunkSize) : this(chunkSize, chunkSize)` — Constructor
- L542-545 _public ctor_ `public ChunkedMemoryWriter(int initialSize = 4096, int chunkSize = 4096) : this(PoolAllocator.Shared, initialSize, chunkSize)` — Constructor
- L553-557 _public ctor_ `public ChunkedMemoryWriter(IMemoryAllocator<byte> allocator, int initialSize = 4096, int chunkSize = 4096) : base(new PooledChunk(0, allocator.Alloc(initialSize, null)), chunkSize)` — Constructor
- L560 _protected method_ `protected override Chunk CreateChunk(int runningIndex, int size)` — (inheritdoc)
- L563-566 _public method_ `public void Dispose()` — (inheritdoc)

#### class `EpicGames.Core.ChunkedMemoryWriter.PooledChunk`  
`class PooledChunk : Chunk`  
_private*; L514-525_
- inherits: `Chunk`
- L516 _public field_ `public readonly IMemoryOwner<byte> Owner`
- L518-522 _public ctor_ `public PooledChunk(int runningIndex, IMemoryOwner<byte> owner) : base(runningIndex, owner.Memory)`
- L524 _public method_ `public override void Release()`

#### class `EpicGames.Core.RefCountedMemoryWriter`  
`public sealed class RefCountedMemoryWriter : ChunkedMemoryWriterBase, IDisposable`  
_public; L572-709_
- inherits: `ChunkedMemoryWriterBase, IDisposable`
- desc: Implementation of ChunkedMemoryWriterBase which takes pages from a IMemoryAllocator{Byte}
- L605 _private* field_ `readonly IMemoryAllocator<byte> _allocator`
- L606 _private* field_ `readonly object? _allocationTag`
- L614-616 _public ctor_ `public RefCountedMemoryWriter(IMemoryAllocator<byte> allocator, int chunkSize, object? allocationTag = null) : this(allocator, chunkSize, chunkSize, allocationTag)` — Constructor
- L625-630 _public ctor_ `public RefCountedMemoryWriter(IMemoryAllocator<byte> allocator, int initialSize, int chunkSize, object? allocationTag) : base(new BufferChunk(0, RefCountedHandle.Create(allocator.Alloc(initialSize, allocationTag))), chunkSize)` — Constructor
- L633 _protected method_ `protected override Chunk CreateChunk(int runningIndex, int size)` — (inheritdoc)
- L636-639 _public method_ `public void Dispose()` — (inheritdoc)
- L644 _public method_ `public IRefCountedHandle<ReadOnlyMemory<byte>> AsRefCountedMemory()` — Returns a contiguous block of memory containing the written data
- L649 _public method_ `public IRefCountedHandle<ReadOnlyMemory<byte>> AsRefCountedMemory(int offset)` — Returns a contiguous block of memory containing the written data
- L654-672 _public method_ `public IRefCountedHandle<ReadOnlyMemory<byte>> AsRefCountedMemory(int offset, int length)` — Returns a contiguous block of memory containing the written data
- L677 _public method_ `public IRefCountedHandle<ReadOnlySequence<byte>> AsRefCountedSequence()` — Creates a reference counted sequence from the allocated data
- L682 _public method_ `public IRefCountedHandle<ReadOnlySequence<byte>> AsRefCountedSequence(int offset)` — Creates a reference counted sequence from the allocated data
- L687-708 _public method_ `public IRefCountedHandle<ReadOnlySequence<byte>> AsRefCountedSequence(int offset, int length)` — Creates a reference counted sequence from the allocated data

#### class `EpicGames.Core.RefCountedMemoryWriter.BufferChunk`  
`class BufferChunk : Chunk`  
_private*; L574-588_
- inherits: `Chunk`
- L576 _public field_ `public readonly IRefCountedHandle<Memory<byte>> Handle`
- L578-582 _public ctor_ `public BufferChunk(int runningIndex, IRefCountedHandle<Memory<byte>> handle) : base(runningIndex, handle.Target)`
- L584-587 _public method_ `public override void Release()`

#### class `EpicGames.Core.RefCountedMemoryWriter.ArrayDisposer`  
`class ArrayDisposer : IDisposable`  
_private*; L590-603_
- inherits: `IDisposable`
- L592 _private* field_ `readonly IDisposable[] _handles`
- L594 _public ctor_ `public ArrayDisposer(IDisposable[] handles)`
- L596-602 _public method_ `public void Dispose()`

#### class `EpicGames.Core.MemoryWriterExtensions`  
`public static class MemoryWriterExtensions`  
_public; L714-1120_
- desc: Extension methods for IMemoryWriter
- L721 _public method_ `public static Span<byte> GetSpan(this IMemoryWriter writer, int minSize)` — Writes a byte to memory
- L728-733 _public method_ `public static Memory<byte> GetMemoryAndAdvance(this IMemoryWriter writer, int length)` — Writes a byte to memory
- L740 _public method_ `public static Span<byte> GetSpanAndAdvance(this IMemoryWriter writer, int length)` — Writes a byte to memory
- L747-750 _public method_ `public static void WriteBoolean(this IMemoryWriter writer, bool value)` — Writes a boolean to memory
- L757-760 _public method_ `public static void WriteInt8(this IMemoryWriter writer, sbyte value)` — Writes a byte to memory
- L767-771 _public method_ `public static void WriteUInt8(this IMemoryWriter writer, byte value)` — Writes a byte to memory
- L778-783 _public method_ `public static void WriteInt16(this IMemoryWriter writer, short value)` — Writes an int16 to the memory
- L790-795 _public method_ `public static void WriteUInt16(this IMemoryWriter writer, ushort value)` — Writes a uint16 to the memory
- L802-807 _public method_ `public static void WriteInt32(this IMemoryWriter writer, int value)` — Writes an int32 to the memory
- L814-819 _public method_ `public static void WriteUInt32(this IMemoryWriter writer, uint value)` — Writes a uint32 to the memory
- L826-831 _public method_ `public static void WriteInt64(this IMemoryWriter writer, long value)` — Writes an int64 to the memory
- L838-843 _public method_ `public static void WriteUInt64(this IMemoryWriter writer, ulong value)` — Writes a uint64 to the memory
- L850-854 _public method_ `public static void WriteDateTime(this IMemoryWriter writer, DateTime value)` — Writes a DateTime to the memory writer
- L861-869 _public method_ `public static void WriteGuidNetOrder(this IMemoryWriter writer, Guid guid)` — Writes a Guid to the memory writer using NET order serialization.
- L876-880 _public method_ `public static void WriteGuidUnrealOrder(this IMemoryWriter writer, Guid guid)` — Writes a Guid to the memory writer (uses UE rather than NET serialization order).
- L887-891 _public method_ `public static void WriteFixedLengthBytes(this IMemoryWriter writer, ReadOnlySpan<byte> span)` — Appends a span of bytes to the buffer, without a length field.
- L898-902 _public method_ `public static void WriteFixedLengthBytes(this IMemoryWriter writer, ReadOnlySequence<byte> sequence)` — Appends a sequence of bytes to the buffer, without a length field.
- L910-913 _public method_ `public static void WriteList<T>(this IMemoryWriter writer, IReadOnlyList<T> list, Action<T> writeItem)` — Writes a variable length array
- L921-924 _public method_ `public static void WriteList<T>(this IMemoryWriter writer, IReadOnlyList<T> list, Action<IMemoryWriter, T> writeItem)` — Writes a variable length array
- L931-937 _public method_ `public static void WriteVariableLengthBytes(this IMemoryWriter writer, ReadOnlySpan<byte> bytes)` — Writes a variable length span of bytes
- L944-950 _public method_ `public static void WriteVariableLengthBytes(this IMemoryWriter writer, ReadOnlySequence<byte> sequence)` — Appends a sequence of bytes to the buffer, without a length field.
- L957-961 _public method_ `public static void WriteVariableLengthBytesWithInt32Length(this IMemoryWriter writer, ReadOnlySpan<byte> bytes)` — Writes a variable length span of bytes
- L969-973 _public method_ `public static void WriteVariableLengthArray<T>(this IMemoryWriter writer, IReadOnlyList<T> list, Action<T> writeItem)` — Writes a variable length array
- L981-985 _public method_ `public static void WriteVariableLengthArray<T>(this IMemoryWriter writer, IReadOnlyList<T> list, Action<IMemoryWriter, T> writeItem)` — Writes a variable length array
- L993-997 _public method_ `public static void WriteVariableLengthArrayWithInt32Length<T>(this IMemoryWriter writer, T[] array, Action<T> writeItem)` — Writes a variable length array
- L1006-1012 _public method_ `public static void WriteFixedLengthArray<T>(this IMemoryWriter writer, IReadOnlyList<T> list, Action<T> writeItem)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter")]` — Writes a fixed length array
- L1019-1025 _public method_ `public static void WriteFixedLengthArray<T>(this IMemoryWriter writer, IReadOnlyList<T> list, Action<IMemoryWriter, T> writeItem)` — Writes a fixed length array
- L1034-1042 _public method_ `public static void WriteDictionary<TKey, TValue>(this IMemoryWriter writer, IReadOnlyDictionary<TKey, TValue> dictionary, Action<TKey> writeKey, Action<TValue> writeValue) where TKey : notnull` — Writes a dictionary to the writer
- L1051-1059 _public method_ `public static void WriteDictionary<TKey, TValue>(this IMemoryWriter writer, IReadOnlyDictionary<TKey, TValue> dictionary, Action<IMemoryWriter, TKey> writeKey, Action<IMemoryWriter, TValue> writeValue) where TKey : notnull` — Writes a dictionary to the writer
- L1066 _public method_ `public static void WriteString(this IMemoryWriter writer, string str)` — Write a string to memory
- L1074-1084 _public method_ `public static void WriteString(this IMemoryWriter writer, string str, Encoding encoding)` — Write a string to memory
- L1091 _public method_ `public static void WriteOptionalString(this IMemoryWriter writer, string? str)` — Write a nullable string to memory
- L1099-1119 _public method_ `public static void WriteOptionalString(this IMemoryWriter writer, string? str, Encoding encoding)` — Write a nullable string to memory

### `Source/Programs/Shared/EpicGames.Core/MemoryWriterStream.cs` (EpicGames.Core)


#### class `EpicGames.Core.MemoryWriterStream`  
`public class MemoryWriterStream : Stream`  
_public; L11-69_
- inherits: `Stream`
- desc: Implementation of Stream which writes data to a IMemoryWriter
- L13 _private* field_ `readonly IMemoryWriter _writer`
- L14 _private* field_ `long _length`
- L19-22 _public ctor_ `public MemoryWriterStream(IMemoryWriter writer)` — Constructor
- L25 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L28 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L31 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L34 _public property_ `public override long Length => ...` — (inheritdoc)
- L37 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L40 _public method_ `public override void Flush()` — (inheritdoc)
- L43 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L46 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L49 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L52-65 _public method_ `public override void Write(ReadOnlySpan<byte> buffer)` — (inheritdoc)
- L68 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/ParallelTask.cs` (EpicGames.Core)


#### class `EpicGames.Core.ParallelTask`  
`public static class ParallelTask`  
_public; L14-75_
- desc: Async equivalents for parallel methods
- L24-27 _public method_ `public static Task ForAsync(int fromInclusive, int toExclusive, Action<int> action)` — Execute a large number of tasks in parallel over a collection. Parallel.ForEach() method isn't generally compatible with asynchronous programming, because any exceptions are thrown on the
- L37-50 _public method_ `public static Task ForEachAsync<T>(IEnumerable<T> collection, Action<T> action)` — Execute a large number of tasks in parallel over a collection. Parallel.ForEach() method isn't generally compatible with asynchronous programming, because any exceptions are thrown on the
- L61-74 _public method_ `public static Task ForEachAsync<T>(IEnumerable<T> collection, Func<T, Task> action, int maxDegreeOfParallelism)` — Execute a large number of tasks in parallel over a collection. Parallel.ForEach() method isn't generally compatible with asynchronous programming, because any exceptions are thrown on the

### `Source/Programs/Shared/EpicGames.Core/ProcessUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.ProcessUtils`  
`public static class ProcessUtils`  
_public; L19-563_
- desc: Includes utilities for managing processes
- L21 _private* const_ `const uint PROCESS_TERMINATE = 0x0001`
- L22 _internal const_ `internal const int PROCESS_VM_READ = 0x0010`
- L23 _internal const_ `internal const int PROCESS_QUERY_LIMITED_INFORMATION = 0x1000`
- L26 _private* method_ `static extern SafeProcessHandle OpenProcess(uint dwDesiredAccess, bool bInheritHandle, uint processId)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L30 _private* method_ `static extern bool TerminateProcess(SafeProcessHandle hProcess, uint uExitCode)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L34 _private* method_ `static extern int QueryFullProcessImageName([In] SafeProcessHandle hProcess, [In] int dwFlags, [Out] StringBuilder lpExeName, ref int lpdwSize)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L38 _private* method_ `static extern bool EnumProcesses([MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U4)][In][Out] uint[] processIds, int arraySizeBytes, [MarshalAs(UnmanagedType.U4)] out int bytesCopied)` — attrs: `[DllImport("Psapi.dll", SetLastError = true)]`
- L40 _private* const_ `const uint WAIT_FAILED = 0xffffffff`
- L43 _private* method_ `static extern uint WaitForMultipleObjects(int nCount, IntPtr[] lpHandles, bool bWaitAll, uint dwMilliseconds)` — attrs: `[DllImport("kernel32.dll")]`
- L65 _private* const_ `const int ProcessBasicInformationClass = 0`
- L68 _private method_ `private static extern int NtQueryInformationProcess(IntPtr processHandle, int processInformationClass, ref ProcessBasicInformation processInformation, int processInformationLength, out int returnLength)` — attrs: `[DllImport("ntdll.dll")]`
- L71 _private* method_ `static extern bool ReadProcessMemory( IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int dwSize, out int lpNumberOfBytesRead)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L79 _private* method_ `static extern bool ReadProcessMemory( IntPtr hProcess, IntPtr lpBaseAddress, ref IntPtr lpBuffer, int dwSize, out int lpNumberOfBytesRead)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L93-103 _public method_ `public static bool TerminateProcesses(Predicate<FileReference> predicate, ILogger logger, CancellationToken cancellationToken)` — Attempts to terminate all processes matching a predicate
- L113-198 _private* method_ `static bool TerminateProcessesWin32(Predicate<FileReference> predicate, ILogger logger, CancellationToken cancellationToken)` — attrs: `[SupportedOSPlatform("windows")]` — Attempts to terminate all processes matching a predicate
- L207-284 _private* method_ `static bool TerminateProcessesGenericPlatform(Predicate<FileReference> predicate, ILogger logger, CancellationToken cancellationToken)` — Attempts to terminate all processes matching a predicate
- L291-301 _public method_ `public static Process? GetParentProcess(Process process)` — Gets the parent process of a specified process
- L304-318 _private* method_ `static Process? GetParentProcessWin32(Process process)` — attrs: `[SupportedOSPlatform("windows")]`
- L325-335 _public method_ `public static IEnumerable<Process> GetAncestorProcesses(Process process)` — Gets all ancestor processes of a specified windows process
- L338-346 _private* method_ `static IEnumerable<Process> GetAncestorProcessesWin32(Process process)` — attrs: `[SupportedOSPlatform("windows")]`
- L354-372 _public method_ `public static string? GetProcessCommandLine(SafeProcessHandle hProcess)` — attrs: `[SupportedOSPlatform("windows")]` — Gets the command line for a process by reading its PEB (Windows only)
- L380-391 _public method_ `public static string? GetProcessCommandLine(int processId)` — attrs: `[SupportedOSPlatform("windows")]` — Gets the command line for a process by process ID (Windows only)
- L399-413 _public method_ `public static string? GetProcessImageName(SafeProcessHandle hProcess)` — attrs: `[SupportedOSPlatform("windows")]` — Gets the full image path for a process (Windows only)
- L421-432 _public method_ `public static string? GetProcessImageName(int processId)` — attrs: `[SupportedOSPlatform("windows")]` — Gets the full image path for a process by process ID (Windows only)
- L440-452 _public method_ `public static int GetParentProcessId(SafeProcessHandle hProcess)` — attrs: `[SupportedOSPlatform("windows")]` — Gets the parent process ID for a process (Windows only)
- L458-486 _private method_ `private static bool GetProcessBasicInfo(SafeProcessHandle hProcess, out IntPtr pebBaseAddress, out int parentPid)` — attrs: `[SupportedOSPlatform("windows")]` — Gets basic process information including PEB address and parent PID
- L492-562 _private method_ `private static string? GetProcessCommandLineFromPeb(IntPtr hProcess, IntPtr pebBaseAddress)` — attrs: `[SupportedOSPlatform("windows")]` — Gets the command line for a process by reading its PEB

#### struct `EpicGames.Core.ProcessUtils.ProcessBasicInformation`  
`struct ProcessBasicInformation`  
_private*; L46-55_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L49 _public field_ `public IntPtr _exitStatus`
- L50 _public field_ `public IntPtr _pebBaseAddress`
- L51 _public field_ `public IntPtr _affinityMask`
- L52 _public field_ `public IntPtr _basePriority`
- L53 _public field_ `public IntPtr _uniqueProcessId`
- L54 _public field_ `public IntPtr _inheritedFromUniqueProcessId`

#### struct `EpicGames.Core.ProcessUtils.UnicodeString`  
`struct UnicodeString`  
_private*; L58-63_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L60 _public field_ `public ushort _length`
- L61 _public field_ `public ushort _maximumLength`
- L62 _public field_ `public IntPtr _buffer`

### `Source/Programs/Shared/EpicGames.Core/ProgressTextReader.cs` (EpicGames.Core)


#### class `EpicGames.Core.ProgressValue`  
`public class ProgressValue`  
_public; L12-113_
- desc: Keeps track of progress reporting of a child process
- L14 _private* field_ `Tuple<string, float> _state = ...`
- L14 _private* field_ `Tuple< _state = null!`
- L15 _private* field_ `readonly Stack<Tuple<float, float>> _ranges = ...`
- L15 _private* field_ `readonly Stack<Tuple< _ranges = new()`
- L20-23 _public ctor_ `public ProgressValue()` — CTOR
- L28-34 _public method_ `public void Clear()` — Reset the progress tracking
- L39 _public property_ `public Tuple<string, float> Current => ...` — The current state
- L45-51 _public method_ `public void Set(string message)` — Add new message
- L58-68 _public method_ `public void Set(string message, float fraction)` — Add a new message with a fraction of how far it has progressed
- L74-77 _public method_ `public void Set(float fraction)` — Update a new fraction of progress without updating the message
- L83-86 _public method_ `public void Increment(float fraction)` — Increment the current progress
- L92-95 _public method_ `public void Push(float maxFraction)` — Push a new range with a max fraction which indicates of far this scope can go
- L100-106 _public method_ `public void Pop()` — Pop the latest range as that step is now completed
- L108-112 _private* method_ `float RelativeToAbsoluteFraction(float fraction)`

#### class `EpicGames.Core.ProgressTextReader`  
`public static class ProgressTextReader`  
_public; L118-294_
- desc: Parses child process output that contains the @progress directives to indicate their progress
- L123 _public const_ `public const string DirectivePrefix = "@progress "` — The directive used to indicate progress
- L131-173 _public method_ `public static string? ParseLine(string line, ProgressValue value)` — Parse progress value from a text line
- L175-221 _private* method_ `static void ProcessInternal(string line, ref bool skipLine, ProgressValue value)`
- L223-263 _private* method_ `static List<string> ParseTokens(string line)`
- L265-293 _private* method_ `static bool ReadFraction(List<string> tokens, ref int tokenIdx, out float fraction)`

### `Source/Programs/Shared/EpicGames.Core/QueryStringBuilder.cs` (EpicGames.Core)


#### class `EpicGames.Core.QueryStringBuilder`  
`public class QueryStringBuilder`  
_public; L12-46_
- desc: Utility class for creating Http query strings
- L14 _private* field_ `readonly StringBuilder _builder = new()`
- L19-28 _public method_ `public void Add(string key, string value)` — Adds a new argument to the query string
- L33-42 _public method_ `public void Add(string key, IEnumerable<string>? values)` — Adds a set of arguments to the query string
- L45 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/ReadOnlyHashSet.cs` (EpicGames.Core)


#### class `EpicGames.Core.ReadOnlyHashSet`  
`public class ReadOnlyHashSet<T> : IReadOnlyCollection<T>`  
_public; L14-95_
- attrs: `[Obsolete("ReadOnlyHashSet<T> is obsolete, please replace with IReadOnlySet<T>")]`
- inherits: `IReadOnlyCollection<T>`
- desc: Wrapper around the HashSet container that only allows read operations
- L19 _private* field_ `readonly HashSet<T> _inner` — The mutable hashset
- L25-28 _public ctor_ `public ReadOnlyHashSet(HashSet<T> inner)` — Constructor
- L34-37 _public ctor_ `public ReadOnlyHashSet(IEnumerable<T> elements)` — Constructor
- L44-47 _public ctor_ `public ReadOnlyHashSet(IEnumerable<T> elements, IEqualityComparer<T> comparer)` — Constructor
- L52 _public property_ `public int Count => ...` — Number of elements in the set
- L57 _public property_ `public IEqualityComparer<T> Comparer => ...` — The comparer for elements in the set
- L64-67 _public method_ `public bool Contains(T item)` — Tests whether a given item is in the set
- L73-76 _public method_ `public IEnumerator<T> GetEnumerator()` — Gets an enumerator for set elements
- L82-85 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — Gets an enumerator for set elements
- L91-94 _public operator_ `public static implicit operator ReadOnlyHashSet<T>(HashSet<T> hashSet)` — Implicit conversion operator from hashsets

### `Source/Programs/Shared/EpicGames.Core/ReadOnlyListExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.ReadOnlyListExtensions`  
`public static class ReadOnlyListExtensions`  
_public; L11-125_
- desc: Extension methods for functionality on List{T} but missing from IReadOnlyList{T}
- L20-23 _public method_ `public static int BinarySearch<T>(this IReadOnlyList<T> list, T item)` — Performs a binary search on the given list
- L33-36 _public method_ `public static int BinarySearch<T>(this IReadOnlyList<T> list, T item, IComparer<T> comparer)` — Performs a binary search on the given list
- L47-50 _public method_ `public static int BinarySearch<TItem, TField>(this IReadOnlyList<TItem> list, Func<TItem, TField> projection, TField item)` — Binary searches a list based on a projection
- L62-85 _public method_ `public static int BinarySearch<TItem, TField>(this IReadOnlyList<TItem> list, Func<TItem, TField> projection, TField item, IComparer<TField> comparer)` — Binary searches a list based on a projection
- L95-103 _public method_ `public static List<TOutput> ConvertAll<TInput, TOutput>(this IReadOnlyList<TInput> input, Func<TInput, TOutput> convert)` — Converts a read only list to a different type
- L112-124 _public method_ `public static int FindIndex<T>(this IReadOnlyList<T> list, Predicate<T> predicate)` — Finds the index of the first element matching a predicate

### `Source/Programs/Shared/EpicGames.Core/ReadOnlyMemoryArray.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IReadOnlyMemoryArray`  
`public interface IReadOnlyMemoryArray : IReadOnlyList<ReadOnlyMemory<byte>>`  
_public; L13-26_
- inherits: `IReadOnlyList<ReadOnlyMemory<byte>>`
- desc: Interface for an array of ReadOnlyMemory{Byte} objects which are embedded within another ReadOnlyMemory{Byte} instance.
- L18 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — The underlying data storing the memory array
- L25 _public* method_ `int GetOffset(int index)` — Gets the offset of an element within the

#### struct `EpicGames.Core.UniformReadOnlyMemoryArray`  
`public readonly struct UniformReadOnlyMemoryArray : IReadOnlyMemoryArray`  
_public; L31-83_
- inherits: `IReadOnlyMemoryArray`
- desc: Represents an array of uniformly sized ReadOnlyMemory{Byte} objects in a parent ReadOnlyMemory{Byte} instance.
- L34 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — (inheritdoc)
- L39 _public property_ `public int ElementSize { get; }` — Size of each element
- L44-48 _public ctor_ `public UniformReadOnlyMemoryArray(ReadOnlyMemory<byte> data, int elementSize)` — Constructor
- L53 _public method_ `public static int Measure(ReadOnlySpan<byte> span, int elementSize)` — Gets the size of serialized data
- L56 _public property_ `public int Count => ...` — (inheritdoc)
- L59 _public method_ `public int GetOffset(int index)` — (inheritdoc)
- L62-70 _public indexer_ `public ReadOnlyMemory<byte> this[int index] { get; }` — (inheritdoc)
- L73-79 _public method_ `public IEnumerator<ReadOnlyMemory<byte>> GetEnumerator()` — (inheritdoc)
- L82 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

#### struct `EpicGames.Core.JaggedReadOnlyMemoryArray`  
`public readonly struct JaggedReadOnlyMemoryArray : IReadOnlyMemoryArray`  
_public; L88-142_
- inherits: `IReadOnlyMemoryArray`
- desc: Represents an array of variably sized ReadOnlyMemory{Byte} objects in a parent ReadOnlyMemory{Byte} instance.
- L91 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — (inheritdoc)
- L96-100 _public ctor_ `public JaggedReadOnlyMemoryArray(ReadOnlyMemory<byte> data)` — Constructor
- L105-109 _public method_ `public static int Measure(ReadOnlySpan<byte> span)` — Gets the size of serialized data
- L112 _public property_ `public int Count => ...` — (inheritdoc)
- L115-123 _public indexer_ `public ReadOnlyMemory<byte> this[int index] { get; }` — (inheritdoc)
- L126 _public method_ `public int GetOffset(int index)` — (inheritdoc)
- L129-138 _public method_ `public IEnumerator<ReadOnlyMemory<byte>> GetEnumerator()` — (inheritdoc)
- L141 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/ReadOnlyMemoryStream.cs` (EpicGames.Core)


#### class `EpicGames.Core.ReadOnlyMemoryStream`  
`public class ReadOnlyMemoryStream : Stream`  
_public; L11-81_
- inherits: `Stream`
- desc: Stream which reads from a ReadOnlyMemory{Byte}
- L16 _private* field_ `readonly ReadOnlyMemory<byte> _memory` — The buffer to read from
- L22-25 _public ctor_ `public ReadOnlyMemoryStream(ReadOnlyMemory<byte> memory)` — Constructor
- L28 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L31 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L34 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L37 _public property_ `public override long Length => ...` — (inheritdoc)
- L40 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L43-45 _public method_ `public override void Flush()` — (inheritdoc)
- L48-54 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L57-74 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L77 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L80 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/ReadOnlySequenceBuilder.cs` (EpicGames.Core)


#### class `EpicGames.Core.ReadOnlySequence`  
`public static class ReadOnlySequence`  
_public; L12-20_
- desc: Static utility methods
- L19 _public method_ `public static ReadOnlySequence<T> Create<T>(IReadOnlyList<ReadOnlyMemory<T>> segments)` — Create a sequence from a list of segments

#### class `EpicGames.Core.ReadOnlySequenceBuilder`  
`public class ReadOnlySequenceBuilder<T>`  
_public; L26-104_
- desc: Utility class to combine buffers into a ReadOnlySequence{T}
- L42 _private* field_ `readonly List<ReadOnlyMemory<T>> _segments = []`
- L47 _public property_ `public long Length { get; set; }` — Current length of the sequence
- L54-72 _internal method_ `internal static ReadOnlySequence<T> Create(IReadOnlyList<ReadOnlyMemory<T>> segments)` — Create a sequence from a list of segments
- L78-85 _public method_ `public void Append(ReadOnlyMemory<T> memory)` — Append a block of memory to the end of the sequence
- L91-97 _public method_ `public void Append(ReadOnlySequence<T> sequence)` — Append another sequence to the end of this one
- L103 _public method_ `public ReadOnlySequence<T> Construct()` — Construct a sequence from the added blocks

#### class `EpicGames.Core.ReadOnlySequenceBuilder.Segment`  
`class Segment : ReadOnlySequenceSegment<T>`  
_private*; L28-40_
- inherits: `ReadOnlySequenceSegment<T>`
- L30-34 _public ctor_ `public Segment(long runningIndex, ReadOnlyMemory<T> memory)`
- L36-39 _public method_ `public void SetNext(Segment next)`

#### class `EpicGames.Core.ReadOnlySequenceExtensions`  
`public static class ReadOnlySequenceExtensions`  
_public; L109-127_
- desc: Extension methods for ReadOnlySequence{T}
- L116-126 _public method_ `public static ReadOnlyMemory<T> AsSingleSegment<T>(this ReadOnlySequence<T> sequence)` — Gets the data from a sequence as a contiguous block of memory

### `Source/Programs/Shared/EpicGames.Core/ReadOnlySequenceStream.cs` (EpicGames.Core)


#### class `EpicGames.Core.ReadOnlySequenceStream`  
`public class ReadOnlySequenceStream : Stream`  
_public; L12-96_
- inherits: `Stream`
- desc: Stream which reads from a ReadOnlyMemory{Byte}
- L17 _private* field_ `readonly ReadOnlySequence<byte> _source` — The buffer to read from
- L22 _private* field_ `ReadOnlySequence<byte> _remaining` — Remaining sequence to read
- L28-32 _public ctor_ `public ReadOnlySequenceStream(ReadOnlySequence<byte> sequence)` — Constructor
- L35 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L38 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L41 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L44 _public property_ `public override long Length => ...` — (inheritdoc)
- L47-51 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L54-56 _public method_ `public override void Flush()` — (inheritdoc)
- L59-66 _public method_ `public override int Read(Span<byte> buffer)` — (inheritdoc)
- L69 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L72-89 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L92 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L95 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/RefCountedHandle.cs` (EpicGames.Core)


#### interface `EpicGames.Core.IRefCountedHandle`  
`public interface IRefCountedHandle : IDisposable`  
_public; L12-18_
- inherits: `IDisposable`
- desc: Disposable reference to an underlying resource. The underlying resource is disposed once the last reference to it is disposed.
- L17 _public* method_ `IRefCountedHandle AddRef()` — Increment the reference count and returns a new handle to it

#### interface `EpicGames.Core.IRefCountedHandle`  
`public interface IRefCountedHandle<T> : IRefCountedHandle`  
_public; L24-41_
- inherits: `IRefCountedHandle`
- desc: Disposable reference to an underlying resource.
- L29 _public* property_ `int RefCount { get; }` — Accessor for the current ref count, for debugging purposes.
- L34 _public* property_ `T Target { get; }` — Target of the reference
- L37 _public* method_ `new IRefCountedHandle<T> AddRef()` — (inheritdoc)
- L40 _public* method_ `IRefCountedHandle IRefCountedHandle.AddRef()` — (inheritdoc)

#### class `EpicGames.Core.RefCountedHandle`  
`public static class RefCountedHandle`  
_public; L46-71_
- desc: Utility methods for creating ref counted handles
- L51-54 _public method_ `public static IRefCountedHandle<T> Create<T>(T target) where T : IDisposable` — Creates a reference counted handle to a disposable resource.
- L59-62 _public method_ `public static IRefCountedHandle<T> Create<T>(T target, IDisposable? owner)` — Creates a reference counted handle to a resource with an explicit disposer.
- L67-70 _public method_ `public static IRefCountedHandle<Memory<T>> Create<T>(IMemoryOwner<T> target) where T : struct` — Creates a reference counted handle to a memory owner.

#### class `EpicGames.Core.RefCountedHandle`  
`public sealed class RefCountedHandle<T> : IRefCountedHandle<T>`  
_public; L76-122_
- inherits: `IRefCountedHandle<T>`
- desc: Concrete implementation of IRefCountedHandle{T}
- L78 _private* field_ `readonly RefCountedDisposer? _refCountedDisposer`
- L79 _private* field_ `T _target`
- L82 _public property_ `public int RefCount => ...` — (inheritdoc)
- L85 _public property_ `public T Target => ...` — (inheritdoc)
- L92-96 _public ctor_ `public RefCountedHandle(T target, IDisposable? owner)` — Constructor
- L98-102 _private ctor_ `private RefCountedHandle(T value, RefCountedDisposer disposer)`
- L105-112 _public method_ `public void Dispose()` — (inheritdoc)
- L115-121 _public method_ `public IRefCountedHandle<T> AddRef()` — (inheritdoc)

#### class `EpicGames.Core.RefCountedDisposer`  
`public sealed class RefCountedDisposer`  
_public; L127-166_
- desc: Tracks a ref count value and disposes of a resource once the reference count is zero
- L129 _private* field_ `IDisposable? _owner`
- L130 _private* field_ `int _value = 1`
- L135 _public property_ `public int RefCount => ...` — Current reference count
- L140-144 _public ctor_ `public RefCountedDisposer(IDisposable? owner, int initialValue = 1)` — Constructor
- L150 _public method_ `public int AddRef()` — Increment the current value
- L156-165 _public method_ `public int Release()` — Decrement the current value

### `Source/Programs/Shared/EpicGames.Core/RegistryConfigurationSource.cs` (EpicGames.Core)


#### class `EpicGames.Core.RegistryConfigurationSource`  
`public class RegistryConfigurationSource : IConfigurationSource`  
_public; L16-47_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `IConfigurationSource`
- desc: Configuration source which reads values from the Registry on Windows
- L18 _private* field_ `readonly RegistryKey _baseKey`
- L19 _private* field_ `readonly string _keyPath`
- L20 _private* field_ `readonly string _baseConfigName`
- L21 _private* field_ `readonly Func<string, bool>? _filter`
- L21 _private* field_ `readonly Func< _filter`
- L30-36 _public ctor_ `public RegistryConfigurationSource(RegistryKey baseKey, string keyPath, string baseConfigName, Func<string, bool>? filter = null)` — Constructor
- L42 _public method_ `public string GetRegistryKey()` — Get the registry key used
- L45 _public method_ `public IConfigurationProvider Build(IConfigurationBuilder builder)` — (inheritdoc)

#### class `EpicGames.Core.RegistryConfigProvider`  
`class RegistryConfigProvider : ConfigurationProvider`  
_internal*; L49-101_
- inherits: `ConfigurationProvider`
- L51 _private* field_ `readonly RegistryKey _baseKey`
- L52 _private* field_ `readonly string _keyPath`
- L53 _private* field_ `readonly string _baseConfigName`
- L54 _private* field_ `readonly Func<string, bool>? _filter`
- L54 _private* field_ `readonly Func< _filter`
- L56-62 _public ctor_ `public RegistryConfigProvider(RegistryKey baseKey, string keyPath, string baseConfigName, Func<string, bool>? filter)`
- L64-72 _public method_ `public override void Load()`
- L75-100 _private* method_ `static void GetValues(RegistryKey baseKey, string keyPath, string baseConfigName, Func<string, bool>? filter, Dictionary<string, string?> data)` — attrs: `[SupportedOSPlatform("windows")]`

### `Source/Programs/Shared/EpicGames.Core/RuntimePlatform.cs` (EpicGames.Core)


#### class `EpicGames.Core.RuntimePlatform`  
`public static class RuntimePlatform`  
_public; L12-84_
- desc: Allows testing different platforms
- L19 _public property_ `public static bool IsLinux => ...` — attrs: `[Obsolete("Replace with OperatingSystem.IsLinux()")] [SupportedOSPlatformGuard("linux")]` — Whether we are currently running on Linux.
- L26 _public property_ `public static bool IsMac => ...` — attrs: `[Obsolete("Replace with OperatingSystem.IsMacOS()")] [SupportedOSPlatformGuard("macos")]` — Whether we are currently running on a MacOS platform.
- L33 _public property_ `public static bool IsWindows => ...` — attrs: `[Obsolete("Replace with OperatingSystem.IsWindows()")] [SupportedOSPlatformGuard("windows")]` — Whether we are currently running a Windows platform.
- L59 _public field_ `public static readonly Type Current = OperatingSystem.IsWindows() ? Type.Windows : OperatingSystem.IsMacOS() ? Type.Mac : Type.Linux` — The current runtime platform
- L64 _public field_ `public static readonly string ExeExtension = OperatingSystem.IsWindows() ? ".exe" : ""` — The extension executables have on the current platform
- L67 _private method_ `private static extern IntPtr GetModuleHandle(string lpModuleName)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Auto)]`
- L70 _private method_ `private static extern IntPtr GetProcAddress(IntPtr hModule, string procName)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Ansi)]`
- L75-83 _public method_ `public static bool IsRunningOnWine()` — The current runtime platform is Windows but we're running on Wine

#### enum `EpicGames.Core.RuntimePlatform.Type`  
`public enum Type`  
_public; L38-54_
- desc: The platform type
- L43 _public* enumerator_ `Windows` — Windows
- L48 _public* enumerator_ `Linux` — Linux
- L53 _public* enumerator_ `Mac` — Mac

### `Source/Programs/Shared/EpicGames.Core/ScopeProfiler.cs` (EpicGames.Core)


#### class `EpicGames.Core.ScopeProfiler`  
`public class ScopeProfiler`  
_public; L13-81_
- desc: A stub/no-op scope-profiler API that can be replaced by another implementation to record execution of instrumented scopes.
- L18 _public property_ `public static ScopeProfiler Instance { get; }` — Static instance of the profiler
- L26 _public method_ `public void InitializeAndStart(string programName, string hostAddress, int maxThreadCount)`
- L31 _public method_ `public void StopAndShutdown()`
- L38 _public method_ `public void StartScope(string name, bool bIsStall)` — Start a stacked scope. Must start and end on the same thread
- L43 _public method_ `public void EndScope()` — End a stacked scope. Must start and end on the same thread.
- L55 _public method_ `public void AddSpanAtTime(string name, ulong id, bool bStall, uint beginThreadId, uint endThreadId, ulong startTime, ulong endTime)` — Record an un-stacked time span at a specified time.
- L62 _public method_ `public void Plot(string name, double value)` — Record a value against a particular name, to be plotted over time
- L68-71 _public method_ `public ulong FastTime()` — Generate a timestamp value for the current moment.
- L77-80 _public method_ `public uint GetCurrentThreadId()` — Retrieve the profiler's identifier for the current thread

### `Source/Programs/Shared/EpicGames.Core/SemVer.cs` (EpicGames.Core)


#### struct `EpicGames.Core.SemVer`  
`public readonly struct SemVer : IEquatable<SemVer>, IComparable<SemVer>`  
_public; L11-231_
- inherits: `IEquatable<SemVer>, IComparable<SemVer>`
- desc: Wrapper for a semver version string (https://semver.org/)
- L27 _private* field_ `readonly string _text`
- L28 _private* field_ `readonly int _length`
- L30 _private* property_ `ReadOnlySpan<char> Span => ...`
- L33 _private* field_ `static readonly Regex s_pattern = new(@"^((0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)(?:-((?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\.(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?)(?:\+([0-9a-zA-Z-]+(?:\.[0-9a-zA-Z-]+)*))?$")`
- L38-42 _private ctor_ `private SemVer(string text, int length)` — Constructor
- L49-57 _public method_ `public static SemVer Parse(string text)` — Parses the given string as a semantic version
- L65-78 _public method_ `public static bool TryParse(string text, out SemVer semVer)` — Attempt to parse the given string as a semantic version
- L81 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L84 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L87 _public method_ `public bool Equals(SemVer other)` — (inheritdoc)
- L90 _public method_ `public int CompareTo(SemVer other)` — (inheritdoc)
- L93 _public method_ `public override string ToString()` — (inheritdoc)
- L101 _public method_ `public static int Compare(SemVer lhs, SemVer rhs)` — Compare two versions
- L103-156 _private* method_ `static int Compare(ReadOnlySpan<char> lhs, ReadOnlySpan<char> rhs)`
- L158-166 _private* method_ `static Field GetField(ReadOnlySpan<char> text, int pos)`
- L168-183 _private* method_ `static int CompareFields(ReadOnlySpan<char> lhs, ReadOnlySpan<char> rhs)`
- L185-188 _private* method_ `static int CompareNumericFields(ReadOnlySpan<char> lhs, ReadOnlySpan<char> rhs)`
- L190-200 _private* method_ `static bool IsNumeric(ReadOnlySpan<char> field)`
- L205 _public operator_ `public static bool operator ==(SemVer lhs, SemVer rhs)` — Compares two versions for equality
- L210 _public operator_ `public static bool operator !=(SemVer lhs, SemVer rhs)` — Compares two versions for inequality
- L215 _public operator_ `public static bool operator <(SemVer lhs, SemVer rhs)` — Tests if one version has lower precedence than another
- L220 _public operator_ `public static bool operator <=(SemVer lhs, SemVer rhs)` — Tests if one version has lower or equal precedence to another
- L225 _public operator_ `public static bool operator >(SemVer lhs, SemVer rhs)` — Tests if one version has greater precedence than another
- L230 _public operator_ `public static bool operator >=(SemVer lhs, SemVer rhs)` — Tests if one version has greater or equal precedence to another

#### struct `EpicGames.Core.SemVer.Field`  
`readonly ref struct Field`  
_private*; L13-25_
- L15 _public field_ `public readonly int Pos`
- L16 _public field_ `public readonly ReadOnlySpan<char> Text`
- L18-22 _public ctor_ `public Field(int pos, ReadOnlySpan<char> text)`
- L24 _public property_ `public int End => ...`

### `Source/Programs/Shared/EpicGames.Core/SemaphoreSlimExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.SemaphoreSlimExtensions`  
`public static class SemaphoreSlimExtensions`  
_public; L12-57_
- desc: Extension method to wrap a semaphore in a using statement
- L40-44 _public method_ `public static IDisposable WaitDisposable(this SemaphoreSlim semaphore, CancellationToken cancellationToken = default)` — Returns a disposable semaphore handle
- L52-56 _public method_ `public static async Task<IDisposable> WaitDisposableAsync(this SemaphoreSlim semaphore, CancellationToken cancellationToken = default)` — Returns a disposable semaphore handle

#### struct `EpicGames.Core.SemaphoreSlimExtensions.ReleaseWrapper`  
`struct ReleaseWrapper : IDisposable`  
_private*; L14-32_
- inherits: `IDisposable`
- L16 _private field_ `private readonly SemaphoreSlim _semaphore`
- L17 _private field_ `private int _disposed`
- L19-23 _public ctor_ `public ReleaseWrapper(SemaphoreSlim semaphore)`
- L25-31 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.Core/Sha1Hash.cs` (EpicGames.Core)


#### struct `EpicGames.Core.Sha1Hash`  
`public readonly struct Sha1Hash : IEquatable<Sha1Hash>, IComparable<Sha1Hash>`  
_public; L20-180_
- attrs: `[JsonConverter(typeof(Sha1HashJsonConverter))] [TypeConverter(typeof(Sha1HashTypeConverter))]`
- inherits: `IEquatable<Sha1Hash>, IComparable<Sha1Hash>`
- desc: Struct representing a strongly typed Sha1Hash value.
- L25 _public const_ `public const int NumBytes = 20` — Length of an Sha1Hash
- L30 _public const_ `public const int NumBits = NumBytes * 8` — Length of the hash in bits
- L31 _private* field_ `readonly ulong _a`
- L32 _private* field_ `readonly ulong _b`
- L33 _private* field_ `readonly uint _c`
- L38 _public property_ `public static Sha1Hash Zero { get; }` — Hash consisting of zeroes
- L44-47 _public ctor_ `public Sha1Hash(ReadOnlySpan<byte> span) : this(BinaryPrimitives.ReadUInt64BigEndian(span), BinaryPrimitives.ReadUInt64BigEndian(span.Slice(8)), BinaryPrimitives.ReadUInt32BigEndian(span.Slice(16)))` — Constructor
- L55-60 _public ctor_ `public Sha1Hash(ulong a, ulong b, uint c)` — Constructor
- L67-75 _public method_ `public static Sha1Hash Compute(ReadOnlySpan<byte> data)` — Creates a content hash for a block of data, using a given algorithm.
- L82-85 _public method_ `public static Sha1Hash Parse(string text)` — Parses a digest from the given hex string
- L92-95 _public method_ `public static Sha1Hash Parse(ReadOnlySpan<byte> text)` — Parses a digest from the given hex string
- L98-112 _public method_ `public int CompareTo(Sha1Hash other)` — (inheritdoc)
- L115 _public method_ `public bool Equals(Sha1Hash other)` — (inheritdoc)
- L118 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L121 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L124 _public method_ `public Utf8String ToUtf8String()` — (inheritdoc)
- L127 _public method_ `public override string ToString()` — (inheritdoc)
- L133-138 _public method_ `public byte[] ToByteArray()` — Convert the hash to a byte array
- L144-149 _public method_ `public void CopyTo(Span<byte> span)` — Copies this hash into a span
- L154 _public operator_ `public static bool operator ==(Sha1Hash a, Sha1Hash b)` — Test two hash values for equality
- L159 _public operator_ `public static bool operator !=(Sha1Hash a, Sha1Hash b)` — Test two hash values for equality
- L164 _public operator_ `public static bool operator >(Sha1Hash a, Sha1Hash b)` — Tests whether A > B
- L169 _public operator_ `public static bool operator <(Sha1Hash a, Sha1Hash b)` — Tests whether A is less than B
- L174 _public operator_ `public static bool operator >=(Sha1Hash a, Sha1Hash b)` — Tests whether A is greater than or equal to B
- L179 _public operator_ `public static bool operator <=(Sha1Hash a, Sha1Hash b)` — Tests whether A is less than or equal to B

#### class `EpicGames.Core.Sha1HashExtensions`  
`public static class Sha1HashExtensions`  
_public; L185-210_
- desc: Extension methods for dealing with Sha1Hash values
- L192-197 _public method_ `public static Sha1Hash ReadSha1Hash(this IMemoryReader reader)` — Read an Sha1Hash from a memory reader
- L204-209 _public method_ `public static void WriteSha1Hash(this IMemoryWriter writer, Sha1Hash hash)` — Write an Sha1Hash to a memory writer

#### class `EpicGames.Core.Sha1HashJsonConverter`  
`sealed class Sha1HashJsonConverter : JsonConverter<Sha1Hash>`  
_internal*; L215-222_
- inherits: `JsonConverter<Sha1Hash>`
- desc: Type converter for Sha1Hash to and from JSON
- L218 _public method_ `public override Sha1Hash Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L221 _public method_ `public override void Write(Utf8JsonWriter writer, Sha1Hash value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Core.Sha1HashTypeConverter`  
`sealed class Sha1HashTypeConverter : TypeConverter`  
_internal*; L227-240_
- inherits: `TypeConverter`
- desc: Type converter from strings to Sha1Hash objects
- L230-233 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L236-239 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/SingleInstanceMutex.cs` (EpicGames.Core)


#### class `EpicGames.Core.SingleInstanceMutex`  
`public class SingleInstanceMutex : IDisposable`  
_public; L14-170_
- inherits: `IDisposable`
- desc: System-wide (global) mutex that is thread- and async-safe.
- L19 _private field_ `private Mutex? _globalMutex` — The global mutex instance
- L24 _private field_ `private readonly SingleThreadTaskScheduler _scheduler = new()` — A single-threaded scheduler to run the mutex acquire / release on, to make this class safe for use within an async context.
- L29-33 _public method_ `public void Dispose()` — Release the mutex and dispose of the object
- L39-52 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method
- L54-57 _private method_ `private Task<bool> RunActionOnScheduler(Func<bool> action, CancellationToken cancellationToken = default)`
- L59-102 _private method_ `private bool GetMutex(string mutexName, bool wait, CancellationToken cancellationToken = default)`
- L109-114 _public method_ `public static IDisposable Acquire(string name)` — Acquires a global mutex with the given name.
- L122-137 _public method_ `public static async Task<IDisposable> AcquireAsync(string name, CancellationToken cancellationToken = default)` — Acquires a global mutex with the given name.
- L145-169 _public method_ `public static bool TryAcquire(string name, [NotNullWhen(true)] out IDisposable? mutex)` — Tries to acquire a global mutex with the given name if it's available.

### `Source/Programs/Shared/EpicGames.Core/SingleThreadTaskScheduler.cs` (EpicGames.Core)


#### class `EpicGames.Core.SingleThreadTaskScheduler`  
`public sealed class SingleThreadTaskScheduler : TaskScheduler, IDisposable`  
_public; L16-90_
- inherits: `TaskScheduler, IDisposable`
- desc: A task scheduler that runs with a single thread. Allows for use of the TPL whilst running Tasks on a consistent thread, useful for anything that requires thread affinity, such as global mutexes.
- L21-30 _public ctor_ `public SingleThreadTaskScheduler()` — Creates a single-thread task scheduler.
- L33 _public property_ `public override int MaximumConcurrencyLevel => ...` — (inheritdoc)
- L36-42 _public method_ `public void Dispose()` — (inheritdoc)
- L45-48 _protected method_ `protected override IEnumerable<Task> GetScheduledTasks()` — (inheritdoc)
- L51-54 _protected method_ `protected override void QueueTask(Task task)` — (inheritdoc)
- L57-65 _protected method_ `protected override bool TryExecuteTaskInline(Task task, bool taskWasPreviouslyQueued)` — (inheritdoc)
- L67-85 _private method_ `private void ThreadEntryPoint()`
- L87 _private field_ `private readonly CancellationTokenSource _cancellationTokenSource`
- L88 _private field_ `private readonly Thread _thread`
- L89 _private field_ `private readonly BlockingCollection<Task> _tasks = []`

### `Source/Programs/Shared/EpicGames.Core/SocketExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.SocketExtensions`  
`public static class SocketExtensions`  
_public; L14-68_
- desc: Extension methods for sockets
- L23-29 _public method_ `public static async Task ReceiveMessageAsync(this Socket socket, Memory<byte> buffer, SocketFlags socketFlags, CancellationToken cancellationToken)` — Reads a complete buffer from the given socket, retrying reads until the buffer is full.
- L38-50 _public method_ `public static async Task<bool> TryReceiveMessageAsync(this Socket socket, Memory<byte> buffer, SocketFlags socketFlags, CancellationToken cancellationToken)` — Reads a complete buffer from the given socket, retrying reads until the buffer is full.
- L60-67 _public method_ `public static async Task SendMessageAsync(this Socket socket, ReadOnlyMemory<byte> buffer, SocketFlags socketFlags, CancellationToken cancellationToken)` — Sends a complete buffer over the given socket.

### `Source/Programs/Shared/EpicGames.Core/StackStringBuilder.cs` (EpicGames.Core)


#### struct `EpicGames.Core.StackStringBuilder`  
`public ref struct StackStringBuilder`  
_public; L15-126_
- desc: StringBuffer that can only live on the stack and does not make any allocations as long as initial buffer is big enough Usage: Span<char> initial = stackalloc char[512]; using StackStringBuilder sb = new(initial); sb.Append("Foo");
- L17 _private field_ `private Span<char> _chars`
- L18 _private field_ `private int _pos`
- L19 _private field_ `private char[]? _arrayToReturnToPool`
- L25-28 _public ctor_ `public StackStringBuilder(Span<char> initialBuffer)` — Ctor
- L33 _public property_ `public int Length => ...` — Length of string buffer
- L39 _public indexer_ `public ref char this[int index]` — Access a character by index
- L45-48 _public method_ `public void Resize(int newSize)` — Resize string buffer
- L54-63 _public method_ `public void Append(char c)` — Append character
- L69-78 _public method_ `public void Append(ReadOnlySpan<char> s)` — Append span of characters
- L85-88 _public method_ `public void Replace(char from, char to)` — Replaces all character of from to to
- L94-97 _public method_ `public override string ToString()` — To string
- L103 _public method_ `public ReadOnlySpan<char> AsSpan()` — As span
- L108-116 _public method_ `public void Dispose()` — Dispose buffer
- L118-125 _private method_ `private void Grow(int requiredAdditionalCapacity)`

### `Source/Programs/Shared/EpicGames.Core/StreamUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.StreamUtils`  
`public static class StreamUtils`  
_public; L14-147_
- desc: Utility methods for streams
- L22-35 _public method_ `public static async Task<int> ReadGreedyAsync(this Stream stream, Memory<byte> buffer, CancellationToken cancellationToken = default)` — Issues read calls until the given buffer has been filled with data or the stream is at an end
- L42-53 _public method_ `public static void ReadFixedLengthBytes(this Stream stream, Span<byte> buffer)` — Reads a fixed amount of data from a stream, throwing an exception if the entire buffer cannot be read.
- L61-72 _public method_ `public static async Task ReadFixedLengthBytesAsync(this Stream stream, Memory<byte> buffer, CancellationToken cancellationToken = default)` — Reads a fixed amount of data from a stream, throwing an exception if the entire buffer cannot be read.
- L80-85 _public method_ `public static async Task<byte[]> ReadAllBytesAsync(this Stream stream, CancellationToken cancellationToken = default)` — Read the contents of a file async using double buffering
- L97-106 _public method_ `public static async Task ReadAllBytesAsync(this Stream stream, long fileSizeHint, int minBufferSize, int maxBufferSize, Func<ReadOnlyMemory<byte>, Task> callback, CancellationToken cancellationToken = default)` — Read the contents of a file async using double buffering
- L116-146 _public method_ `public static async Task ReadAllBytesAsync(this Stream stream, int bufferLength, Func<ReadOnlyMemory<byte>, Task> callback, CancellationToken cancellationToken = default)` — Read the contents of a file async using double buffering

### `Source/Programs/Shared/EpicGames.Core/StreamWrapper.cs` (EpicGames.Core)


#### class `EpicGames.Core.StreamWrapper`  
`public class StreamWrapper : Stream`  
_public; L15-137_
- inherits: `Stream`
- desc: Stream implementation that wraps another stream, allowing derived classes to override some methods of their chosing.
- L17 _private* field_ `readonly Stream _inner`
- L22 _protected property_ `protected Stream Inner => ...` — Accessor for the wrapped stream
- L25 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L28 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L31 _public property_ `public override bool CanTimeout => ...` — (inheritdoc)
- L34 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L37 _public property_ `public override long Length => ...` — (inheritdoc)
- L40 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L43 _public property_ `public override int ReadTimeout { get; set; }` — (inheritdoc)
- L46 _public property_ `public override int WriteTimeout { get; set; }` — (inheritdoc)
- L52 _public ctor_ `public StreamWrapper(Stream inner)` — Constructor
- L55-63 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)
- L66-73 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L76 _public method_ `public override IAsyncResult BeginRead(byte[] buffer, int offset, int count, AsyncCallback? callback, object? state)` — (inheritdoc)
- L79 _public method_ `public override IAsyncResult BeginWrite(byte[] buffer, int offset, int count, AsyncCallback? callback, object? state)` — (inheritdoc)
- L82 _public method_ `public override void Close()` — (inheritdoc)
- L85 _public method_ `public override void CopyTo(Stream destination, int bufferSize)` — (inheritdoc)
- L88 _public method_ `public override Task CopyToAsync(Stream destination, int bufferSize, CancellationToken cancellationToken)` — (inheritdoc)
- L91 _public method_ `public override int EndRead(IAsyncResult asyncResult)` — (inheritdoc)
- L94 _public method_ `public override void EndWrite(IAsyncResult asyncResult)` — (inheritdoc)
- L97 _public method_ `public override void Flush()` — (inheritdoc)
- L100 _public method_ `public override Task FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L103 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L106 _public method_ `public override int Read(Span<byte> buffer)` — (inheritdoc)
- L109 _public method_ `public override Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L112 _public method_ `public override ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — (inheritdoc)
- L115 _public method_ `public override int ReadByte()` — (inheritdoc)
- L118 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L121 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L124 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)
- L127 _public method_ `public override void Write(ReadOnlySpan<byte> buffer)` — (inheritdoc)
- L130 _public method_ `public override Task WriteAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L133 _public method_ `public override ValueTask WriteAsync(ReadOnlyMemory<byte> buffer, CancellationToken cancellationToken = default)` — (inheritdoc)
- L136 _public method_ `public override void WriteByte(byte value)` — (inheritdoc)

#### class `EpicGames.Core.StreamWrapperExtensions`  
`public static class StreamWrapperExtensions`  
_public; L142-187_
- desc: Extension methods for StreamWrapper
- L186 _public method_ `public static Stream WrapOwnership(this Stream stream, IDisposable resource)` — Wraps ownership of another resource with a stream

#### class `EpicGames.Core.StreamWrapperExtensions.StreamResourceOwner`  
`class StreamResourceOwner : StreamWrapper`  
_private*; L144-178_
- inherits: `StreamWrapper`
- L146 _private* field_ `IDisposable? _resource`
- L148-152 _public ctor_ `public StreamResourceOwner(Stream inner, IDisposable resource) : base(inner)`
- L155-163 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)
- L166-171 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L173-177 _private* method_ `void DisposeResource()`

### `Source/Programs/Shared/EpicGames.Core/StringComparerUE.cs` (EpicGames.Core)


#### class `EpicGames.Core.StringComparerUE`  
`public class StringComparerUE : IComparer<string>, IEqualityComparer<string>`  
_public; L11-70_
- inherits: `IComparer<string>, IEqualityComparer<string>`
- desc: Comparer for String objects. However, it implements UE style ignore case compare
- L16 _public property_ `public static StringComparerUE Ordinal { get; }` — Static instance of an ordinal String comparer
- L21 _public property_ `public static StringComparerUE OrdinalIgnoreCase { get; }` — Static instance of an ordinal String comparer which ignores case
- L26 _public property_ `public StringComparison ComparisonType { get; }` — The comparison type
- L32-35 _public ctor_ `public StringComparerUE(StringComparison comparisonType)` — Constructor
- L38-41 _public method_ `public bool Equals(string? x, string? y)` — (inheritdoc)
- L44-47 _public method_ `public int GetHashCode(string obj)` — (inheritdoc)
- L50-69 _public method_ `public int Compare(string? x, string? y)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/StringUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.StringUtils`  
`public static class StringUtils`  
_public; L14-811_
- desc: Utility methods for strings
- L19 _private* field_ `static readonly sbyte[] s_hexDigits = CreateHexDigitsTable()` — Array mapping from ascii index to hexadecimal digits.
- L24 _private* field_ `static readonly byte[] s_hexDigitToUtf8Byte = Encoding.UTF8.GetBytes("0123456789abcdef")` — Hex digits to utf8 byte
- L29 _private* field_ `static readonly string[] s_byteSizes = ["B", "KB", "MB", "GB", "TB", "PB", "EB"]` — Array mapping human readable size of bytes, 1024^x. long max is within the range of Exabytes.
- L34-54 _private* method_ `static sbyte[] CreateHexDigitsTable()` — Static constructor. Initializes the HexDigits array.
- L62-70 _public method_ `public static string Indent(string text, string indent)` — Indents a string by a given indent
- L78-85 _public method_ `public static string ExpandProperties(string text, Dictionary<string, string> properties)` — Expand all the property references (of the form $(PropertyName)) in a string.
- L93-125 _public method_ `public static string ExpandProperties(string text, Func<string, string?> getPropertyValue)` — Expand all the property references (of the form $(PropertyName)) in a string.
- L128-131 _public method_ `public static IEnumerable<string> WordWrap(string text, int maxWidth)` — (inheritdoc)
- L141-165 _public method_ `public static IEnumerable<string> WordWrap(string text, int initialIndent, int hangingIndent, int maxWidth)` — Takes a given sentence and wraps it on a word by word basis so that no line exceeds the set maximum line length. Words longer than a line are broken up. Returns the sentence as a list of individual lines.
- L170-216 _private* method_ `static int GetWordWrapLineEnd(string text, int minIdx, int maxWidth)` — Gets the next character index to end a word-wrapped line on
- L224-228 _public method_ `public static void AppendLine(this StringBuilder builder, string format, params object[] args)` — Extension method to allow formatting a string to a stringbuilder and appending a newline
- L236-256 _public method_ `public static string FormatList(IReadOnlyList<string> arguments, string conjunction = "and")` — Formats a list of strings in the style "1, 2, 3 and 4"
- L264-267 _public method_ `public static string FormatList(IEnumerable<string> arguments, string conjunction = "and")` — Formats a list of strings in the style "1, 2, 3 and 4"
- L275-293 _public method_ `public static string FormatList(string[] items, int maxCount)` — Formats a list of items
- L301-304 _public method_ `public static string CreateObjectList<T>(this IEnumerable<T> objects, string prefix)` — Generates a string suitable for debugging a list of objects using ToString(). Lists one per line with the prefix string on the first line.
- L311-314 _public method_ `public static int GetHexDigit(byte character)` — Parses a hexadecimal digit
- L321-324 _public method_ `public static int GetHexDigit(char character)` — Parses a hexadecimal digit
- L330 _public method_ `public static byte[] ParseHexString(string text)` — Parses a hexadecimal string into an array of bytes
- L336-344 _public method_ `public static byte[] ParseHexString(ReadOnlySpan<char> text)` — Parses a hexadecimal string into an array of bytes
- L350-358 _public method_ `public static byte[] ParseHexString(ReadOnlySpan<byte> text)` — Parses a hexadecimal string into an array of bytes
- L366-379 _public method_ `public static bool TryParseHexString(ReadOnlySpan<char> text, [NotNullWhen(true)] out byte[]? outBytes)` — Parses a hexadecimal string into an array of bytes
- L387-405 _public method_ `public static bool TryParseHexString(ReadOnlySpan<char> text, Span<byte> bytes)` — Parses a hexadecimal string into an array of bytes
- L413-426 _public method_ `public static bool TryParseHexString(ReadOnlySpan<byte> text, [NotNullWhen(true)] out byte[]? outBytes)` — Parses a hexadecimal string into an array of bytes
- L434-452 _public method_ `public static bool TryParseHexString(ReadOnlySpan<byte> text, Span<byte> bytes)` — Parses a hexadecimal string into an array of bytes
- L460-463 _public method_ `public static int ParseHexByte(ReadOnlySpan<byte> text, int idx)` — Parse a hex byte from the given offset into a span of utf8 characters
- L470-473 _public method_ `public static string FormatHexString(byte[] bytes)` — Formats an array of bytes as a hexadecimal string
- L480-491 _public method_ `public static string FormatHexString(ReadOnlySpan<byte> bytes)` — Formats an array of bytes as a hexadecimal string
- L498-507 _public method_ `public static Utf8String FormatUtf8HexString(ReadOnlySpan<byte> bytes)` — Formats an array of bytes as a hexadecimal string
- L514-521 _public method_ `public static void FormatUtf8HexString(ReadOnlySpan<byte> bytes, Span<byte> characters)` — Formats an array of bytes as a hexadecimal string
- L528-541 _public method_ `public static void FormatLittleEndianUtf8HexString(uint value, Span<byte> characters)` — Formats a 32-bit unsigned integer as a hexadecimal string
- L548-553 _public method_ `public static Utf8String FormatUtf8HexString(uint value)` — Formats a 32-bit unsigned integer as a hexadecimal string
- L560-570 _public method_ `public static void FormatUtf8HexString(uint value, Span<byte> characters)` — Formats a 32-bit unsigned integer as a hexadecimal string
- L577-581 _public method_ `public static void FormatUtf8HexString(ulong value, Span<byte> characters)` — Formats a 32-bit unsigned integer as a hexadecimal string
- L588-598 _public method_ `public static string QuoteArgument(this string str)` — Quotes a string as a command line argument
- L605-615 _public method_ `public static string StripQuoteArgument(this string str)` — Removes the quotes from the beginning and end of a string (if any), can be used to reverse String.QuoteArgument
- L623-633 _public method_ `public static string FormatBytesString(long bytes, int decimalPlaces = 2)` — Formats bytes into a human readable string
- L641-651 _public method_ `public static string FormatBytesString(ulong bytes, int decimalPlaces = 2)` — Formats bytes into a human readable string
- L658-679 _public method_ `public static long ParseBytesString(string bytesString)` — Converts a bytes string into bytes. E.g 1.2KB -> 1229
- L687-700 _public method_ `public static bool TryParseBytesString(string bytesString, out long? bytes)` — Converts a bytes string into bytes. E.g 1.5KB -> 1536
- L706-745 _public method_ `public static string ParseEscapeCodes(string line)` — Parses a string to remove VT100 escape codes
- L753-760 _public method_ `public static string Truncate(string text, int maxLength)` — Truncates the given string to the maximum length, appending an elipsis if it is longer than allowed.
- L768-810 _public method_ `public static int CompareIgnoreCaseUe(ReadOnlySpan<char> x, ReadOnlySpan<char> y)` — Compare two strings using UnrealEngine's ignore case algorithm

### `Source/Programs/Shared/EpicGames.Core/StringView.cs` (EpicGames.Core)


#### struct `EpicGames.Core.StringView`  
`public readonly struct StringView : IEquatable<StringView>`  
_public; L11-181_
- inherits: `IEquatable<StringView>`
- desc: View of a character string. Allows comparing/manipulating substrings without unnecessary memory allocations.
- L16 _public property_ `public ReadOnlyMemory<char> Memory { get; }` — Memory containing the characters
- L21 _public property_ `public ReadOnlySpan<char> Span => ...` — Span for the sequence of characters
- L26 _public property_ `public int Length => ...` — Length of the sequence of characters
- L32-35 _public ctor_ `public StringView(StringView text)` — Constructor
- L42-45 _public ctor_ `public StringView(StringView text, int index)` — Constructor
- L53-56 _public ctor_ `public StringView(StringView text, int index, int count)` — Constructor
- L62-65 _public ctor_ `public StringView(ReadOnlyMemory<char> memory)` — Constructor
- L72-75 _public ctor_ `public StringView(ReadOnlyMemory<char> memory, int index)` — Constructor
- L83-86 _public ctor_ `public StringView(ReadOnlyMemory<char> memory, int index, int count)` — Constructor
- L92-95 _public ctor_ `public StringView(string text)` — Constructor
- L102-105 _public ctor_ `public StringView(string text, int index)` — Constructs a view onto a substring of the given string
- L113-116 _public ctor_ `public StringView(string text, int index, int count)` — Constructs a view onto a substring of the given string
- L124-127 _public operator_ `public static bool operator ==(StringView x, StringView y)` — Equality comparer
- L135-138 _public operator_ `public static bool operator !=(StringView x, StringView y)` — Inequality comparer
- L141-144 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L147-150 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L153-156 _public method_ `public int GetHashCode(StringComparison comparisonType)` — (inheritdoc)
- L159-162 _public method_ `public override string ToString()` — (inheritdoc)
- L165-168 _public method_ `public bool Equals(StringView other)` — (inheritdoc)
- L171-174 _public method_ `public bool Equals(StringView? other, StringComparison comparisonType)` — (inheritdoc)
- L180 _public operator_ `public static implicit operator StringView(string text)` — Implicit conversion operator from a regular string

#### class `EpicGames.Core.StringViewComparer`  
`public class StringViewComparer : IComparer<StringView>, IEqualityComparer<StringView>`  
_public; L186-229_
- inherits: `IComparer<StringView>, IEqualityComparer<StringView>`
- desc: Comparer for StringView objects
- L191 _public property_ `public static StringViewComparer Ordinal { get; }` — Static instance of an ordinal StringView comparer
- L196 _public property_ `public static StringViewComparer OrdinalIgnoreCase { get; }` — Static instance of an ordinal StringView comparer which ignores case
- L201 _public property_ `public StringComparison ComparisonType { get; }` — The comparison type
- L207-210 _public ctor_ `public StringViewComparer(StringComparison comparisonType)` — Constructor
- L213-216 _public method_ `public bool Equals(StringView x, StringView y)` — (inheritdoc)
- L219-222 _public method_ `public int GetHashCode(StringView obj)` — (inheritdoc)
- L225-228 _public method_ `public int Compare(StringView x, StringView y)` — (inheritdoc)

#### class `EpicGames.Core.StringViewComparerUe`  
`public class StringViewComparerUe : IComparer<StringView>, IEqualityComparer<StringView>`  
_public; L234-284_
- inherits: `IComparer<StringView>, IEqualityComparer<StringView>`
- desc: Comparer for StringView objects. However, it implements UE style ignore case compare
- L239 _public property_ `public static StringViewComparerUe Ordinal { get; }` — Static instance of an ordinal StringView comparer
- L244 _public property_ `public static StringViewComparerUe OrdinalIgnoreCase { get; }` — Static instance of an ordinal StringView comparer which ignores case
- L249 _public property_ `public StringComparison ComparisonType { get; }` — The comparison type
- L255-258 _public ctor_ `public StringViewComparerUe(StringComparison comparisonType)` — Constructor
- L261-264 _public method_ `public bool Equals(StringView x, StringView y)` — (inheritdoc)
- L267-270 _public method_ `public int GetHashCode(StringView obj)` — (inheritdoc)
- L273-283 _public method_ `public int Compare(StringView x, StringView y)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/SystemUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.SystemUtils`  
`public static class SystemUtils`  
_public; L17-583_
- desc: Utilities for querying system hardware information such as processor counts, memory availability, and CPU utilization.
- L34 _private* method_ `static extern bool GetLogicalProcessorInformationEx(LogicalProcessorRelationship relationshipType, IntPtr buffer, ref uint returnedLength)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("kernel32.dll", SetLastError = true)]`
- L39 _private* method_ `static extern int sysctlbyname(string name, out int oldp, ref ulong oldlenp, IntPtr newp, ulong newlen)` — attrs: `[SupportedOSPlatform("macos")] [DllImport("libc")]`
- L43 _private* method_ `static extern int sysctlbyname(string name, out ulong oldp, ref ulong oldlenp, IntPtr newp, ulong newlen)` — attrs: `[SupportedOSPlatform("macos")] [DllImport("libc")]`
- L49-106 _public method_ `public static int GetLogicalProcessorCount()` — Gets the number of logical cores. We use this rather than Environment.ProcessorCount when possible to handle machines with > 64 cores (the single group limit available to the .NET framework).
- L112-174 _public method_ `public static int GetPhysicalProcessorCount()` — Gets the number of physical cores, excluding hyper threading.
- L180-191 _public method_ `public static bool IsAsymmetricalProcessor()` — Gets if the processor has asymmetrical cores (Windows only)
- L202-207 _public method_ `public static long GetAvailableMemoryBytes()` — Gets the total memory bytes available, based on what is known to the garbage collector.
- L227 _private* method_ `static extern bool GlobalMemoryStatusEx(ref MemoryStatusEx lpBuffer)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("kernel32.dll", SetLastError = true)]`
- L294 _private* method_ `static extern int host_statistics64(IntPtr hostPriv, int flavor, out VmStatistics64 hostInfo64Out, ref uint hostInfoCount)` — attrs: `[SupportedOSPlatform("macos")] [DllImport("libc")]`
- L299 _private* method_ `static extern IntPtr mach_host_self()` — attrs: `[SupportedOSPlatform("macos")] [DllImport("libc")]`
- L306-310 _public method_ `public static long GetTotalSystemMemoryBytes()` — Gets the total system memory in bytes based on what is known to the garbage collector.
- L317-356 _public method_ `public static long GetFreeMemoryBytes()` — Gets the total memory bytes free, based on what is known to the garbage collector.
- L365-401 _public method_ `public static long GetCurrentCommittedMemoryBytes()` — Gets the current amount of committed (virtual) memory in bytes. On Windows, this is the total page file usage (RAM + page file consumed by all processes). On Linux, this is the Committed_AS value from /proc/meminfo. On macOS, this is an approximation based on wired + active + inactive + compressor pages.
- L410-437 _public method_ `public static long GetMaxCommittedMemoryBytes()` — Gets the maximum amount of memory that can be committed in bytes (commit limit). On Windows, this is the total page file size (RAM + page file capacity). On Linux, this is the CommitLimit value from /proc/meminfo. On macOS, this is the total physical RAM (hw.memsize).
- L441-461 _private* method_ `static long ReadProcMemInfoKilobytes(string key)` — attrs: `[SupportedOSPlatform("linux")]`
- L469 _private* method_ `static extern int PdhOpenQueryW([MarshalAs(UnmanagedType.LPWStr)] string? szDataSource, UIntPtr dwUserData, out IntPtr phQuery)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("pdh.dll", SetLastError = true, CharSet = CharSet.Auto)]`
- L473 _private* method_ `static extern uint PdhAddCounter(IntPtr hQuery, string szFullCounterPath, IntPtr dwUserData, out IntPtr phCounter)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("pdh.dll", SetLastError = true, CharSet = CharSet.Auto)]`
- L477 _private* method_ `static extern uint PdhCollectQueryData(IntPtr phQuery)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("pdh.dll", SetLastError = true)]`
- L488 _private* method_ `static extern uint PdhGetFormattedCounterValue(IntPtr phCounter, uint dwFormat, IntPtr lpdwType, out PdhFmtCounterValue pValue)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("pdh.dll", SetLastError = true)]`
- L490 _private* field_ `static IntPtr s_cpuQuery`
- L491 _private* field_ `static IntPtr s_cpuTotal`
- L492 _private* field_ `static bool s_cpuInitialized = false`
- L499-543 _public method_ `public static bool GetTotalCpuUtilization(out float utilization)` — Gives the current CPU utilization.
- L549-580 _private* method_ `static string RunProcessAndReturnStdOut(string command, string args)`

#### enum `EpicGames.Core.SystemUtils.LogicalProcessorRelationship`  
`enum LogicalProcessorRelationship`  
_private*; L22-30_
- attrs: `[SupportedOSPlatform("windows")]`
- L24 _public* enumerator_ `RelationProcessorCore`
- L25 _public* enumerator_ `RelationNumaNode`
- L26 _public* enumerator_ `RelationCache`
- L27 _public* enumerator_ `RelationProcessorPackage`
- L28 _public* enumerator_ `RelationGroup`
- L29 _public* enumerator_ `RelationAll = 0xffff`

#### struct `EpicGames.Core.SystemUtils.MemoryStatusEx`  
`struct MemoryStatusEx`  
_private*; L212-223_
- attrs: `[SupportedOSPlatform("windows")] [StructLayout(LayoutKind.Sequential)]`
- L214 _public field_ `public uint _dwLength`
- L215 _public field_ `public uint _dwMemoryLoad`
- L216 _public field_ `public ulong _ullTotalPhys`
- L217 _public field_ `public ulong _ullAvailPhys`
- L218 _public field_ `public ulong _ullTotalPageFile`
- L219 _public field_ `public ulong _ullAvailPageFile`
- L220 _public field_ `public ulong _ullTotalVirtual`
- L221 _public field_ `public ulong _ullAvailVirtual`
- L222 _public field_ `public ulong _ullAvailExtendedVirtual`

#### struct `EpicGames.Core.SystemUtils.VmStatistics64`  
`struct VmStatistics64`  
_private*; L231-289_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L234 _public field_ `public int _freeCount`
- L236 _public field_ `public int _activeCount`
- L238 _public field_ `public int _inactiveCount`
- L240 _public field_ `public int _wireCount`
- L242 _public field_ `public ulong _zeroFillCount`
- L244 _public field_ `public ulong _reactivations`
- L246 _public field_ `public ulong _pageins`
- L248 _public field_ `public ulong _pageouts`
- L250 _public field_ `public ulong _faults`
- L252 _public field_ `public ulong _cowFaults`
- L254 _public field_ `public ulong _lookups`
- L256 _public field_ `public ulong _hits`
- L258 _public field_ `public ulong _purges`
- L260 _public field_ `public int _purgeableCount`
- L268 _public field_ `public int _speculativeCount`
- L272 _public field_ `public ulong _decompressions`
- L274 _public field_ `public ulong _compressions`
- L276 _public field_ `public ulong _swapins`
- L278 _public field_ `public ulong _swapouts`
- L280 _public field_ `public int _compressorPageCount`
- L282 _public field_ `public int _throttledCount`
- L284 _public field_ `public int _externalPageCount`
- L286 _public field_ `public int _internalPageCount`
- L288 _public field_ `public ulong _totalUncompressedPagesInCompressor`

#### struct `EpicGames.Core.SystemUtils.PdhFmtCounterValue`  
`struct PdhFmtCounterValue`  
_private*; L480-484_
- attrs: `[SupportedOSPlatform("windows")]`
- L482 _public field_ `public uint _cStatus`
- L483 _public field_ `public double _doubleValue`

### `Source/Programs/Shared/EpicGames.Core/Telemetry/DataRouterTelemetryService.cs` (EpicGames.Core)


#### class `EpicGames.Core.Telemetry.DataRouterEvent`  
`public abstract class DataRouterEvent`  
_public; L20-124_
- desc: Abstract base class for a data router event
- L25 _protected property_ `protected string AppId { get; set; }` — The app's id
- L30 _protected property_ `protected string AppVersion { get; set; }` — The app's version
- L35 _protected property_ `protected string AppEnvironment { get; set; }` — The app's environment
- L40 _protected property_ `protected string UploadType { get; set; }` — The upload type
- L45 _protected property_ `protected string UserId { get; set; }` — The user's id
- L50 _protected property_ `protected string SessionId { get; set; }` — The session's id
- L57-61 _public property_ `public DateTime TimeStamp { get; set; }` — attrs: `[JsonPropertyName("DateOffset")] [JsonConverter(typeof(DateOffsetDataRouterEventConverter))]` — The TimeStamp of when the event was added to queue UNTIL we serialize so we use the name TimeStamp in code, and serialize as DateOffset
- L66-69 _public property_ `public abstract string EventName { get; }` — The name of the event
- L75-78 _protected ctor_ `protected DataRouterEvent(DateTime? inTimeStamp = null)` — Constructor
- L90-99 _protected ctor_ `protected DataRouterEvent(string inAppId, string inAppVersion, string inAppEnvironment, string inUploadType, string inUserId, string inSessionId, DateTime? inTimeStamp = null)` — Constructor
- L106-113 _public method_ `public virtual string GetUrlParameters()` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1055:URI-like return values should not be strings", Justification = "Legacy interoperability")]` — Generates url parameter strings for this event
- L120-123 _public method_ `public void OverrideAppId(string appId)` — Direct access to override the App ID. This is used to redirect telemetry data in Databricks.

#### class `EpicGames.Core.Telemetry.DataRouterPost`  
`public class DataRouterPost`  
_public; L129-138_
- desc: Object to post data router events
- L134-137 _public property_ `public List<object> Events { get; }` — List of objects to force polymorphic JSON serialization

#### class `EpicGames.Core.Telemetry.SerializedDataRouterPost`  
`public class SerializedDataRouterPost`  
_public; L143-153_
- desc: Object to serialize data router post events
- L148-151 _public property_ `public List<string> EventsSerialized { get; }` — Used in conjunction with a JsonSerializer class to mimic serialization of DataRouterPost

#### class `EpicGames.Core.Telemetry.SerializedDataRouterPostConverter`  
`public class SerializedDataRouterPostConverter : JsonConverter<SerializedDataRouterPost>`  
_public; L159-191_
- inherits: `JsonConverter<SerializedDataRouterPost>`
- desc: Implementation of JsonConverter for SerializedDataRouterPost. Matches output of serializing a DataRouterPost. https://confluence.it.epicgames.com/display/DPE/Data+Router
- L169-172 _public method_ `public override SerializedDataRouterPost? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Reader
- L180-190 _public method_ `public override void Write(Utf8JsonWriter writer, SerializedDataRouterPost value, JsonSerializerOptions options)` — Writer

#### class `EpicGames.Core.Telemetry.DateOffsetDataRouterEventConverter`  
`public class DateOffsetDataRouterEventConverter : JsonConverter<DateTime>`  
_public; L196-234_
- inherits: `JsonConverter<DateTime>`
- desc: DateTime converter for data router events
- L206-209 _public method_ `public override DateTime Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Reader
- L217-233 _public method_ `public override void Write(Utf8JsonWriter writer, DateTime value, JsonSerializerOptions options)` — Writer

#### class `EpicGames.Core.Telemetry.UnixTimestampDataRouterEventConverter`  
`public class UnixTimestampDataRouterEventConverter : JsonConverter<DateTime>`  
_public; L239-265_
- inherits: `JsonConverter<DateTime>`
- desc: DateTime converter for data router events to convert to Unix timestamp
- L249-252 _public method_ `public override DateTime Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Reader
- L260-264 _public method_ `public override void Write(Utf8JsonWriter writer, DateTime value, JsonSerializerOptions options)` — Writer

#### class `EpicGames.Core.Telemetry.DurationDataRouterEventConverter`  
`public class DurationDataRouterEventConverter : JsonConverter<TimeSpan>`  
_public; L270-295_
- inherits: `JsonConverter<TimeSpan>`
- desc: TimeSpan converter for data router events to convert to seconds
- L280-283 _public method_ `public override TimeSpan Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — Reader
- L291-294 _public method_ `public override void Write(Utf8JsonWriter writer, TimeSpan value, JsonSerializerOptions options)` — Writer

#### class `EpicGames.Core.Telemetry.DataRouterTelemetryService`  
`public class DataRouterTelemetryService : ITelemetryService<DataRouterEvent>`  
_public; L302-637_
- inherits: `ITelemetryService<DataRouterEvent>`
- desc: Implementation for TelemetryService using DataRouter. FlushEvents() should be called before application exits otherwise some events may remain unsent https://confluence.it.epicgames.com/display/DPE/Data+Router
- L307-311 _public property_ `public bool IsDryRun { get; set; }` — Denotes if this is a dry run
- L316 _protected property_ `protected ILogger<DataRouterTelemetryService> Logger { get; }` — Logging interface
- L321 _protected property_ `protected HttpClient HttpClient { get; }` — The http client to use for connections
- L326 _protected property_ `protected ConcurrentQueue<DataRouterEvent> EventsQueue { get; }` — The queue of pending data router events
- L331-351 _public property_ `public int AutoFlushIntervalMilliseconds { get; set; }` — Interval to flush events, in milliseconds
- L352 _private field_ `private int _autoFlushIntervalMilliseconds = 60 * 1000`
- L357 _private const_ `private const int MaxEventSize = 2 * 1000 * 1000` — Max size of json body for sending telemetry events
- L362 _public property_ `public Uri BaseAddress { get; set; }` — Base url address to post events to
- L364 _private field_ `private readonly Timer _autoFlushTimer = new()`
- L369-380 _public property_ `public static int DataRouterPostEmptyJsonLength { get; }` — Length of an empty data router post when serialized to json
- L381 _private field_ `private static int s_dataRouterPostEmptyJsonLength = -1`
- L386-403 _private method_ `private void SetHttpClientHeaders()` — Sets up the default request headers for the http client
- L410-429 _public ctor_ `public DataRouterTelemetryService(HttpClient inHttpClient, Uri inBaseAddress)` — Constructor
- L436-444 _private method_ `private async void AutoFlushEventsAsync(object? sender, ElapsedEventArgs e)` — Async function to automatically flush events
- L445 _private field_ `private Task? _prevFlushTask = null`
- L448-451 _public method_ `public virtual void RecordEvent(DataRouterEvent eventData)` — (inheritdoc)
- L454-463 _public method_ `public void FlushEvents()` — (inheritdoc)
- L471-512 _private method_ `private void CreateBatchedSerializedDataRouterPosts(DataRouterPost inPost, string postURI, out List<SerializedDataRouterPost> outPostsList)` — Creates a batch of post events
- L520-525 _private method_ `private async Task<HttpResponseMessage> PostRequestAsync(string postDataKey, string jsonBody)` — Async function to post a single request
- L531-535 _private method_ `private async Task<HttpResponseMessage> HeadRequestAsync()` — Async function to issue a single async head request
- L541-611 _public method_ `public virtual async Task FlushEventsAsync()` — Async function to flush events
- L614-618 _public method_ `public void Dispose()` — (inheritdoc)
- L624-636 _protected method_ `protected virtual void Dispose(bool disposing)` — Standard Dispose pattern method

### `Source/Programs/Shared/EpicGames.Core/Telemetry/DefaultTelemetryHttpClient.cs` (EpicGames.Core)


#### class `EpicGames.Core.Telemetry.HttpClientDefaults`  
`public static class HttpClientDefaults`  
_public; L14-50_
- desc: Static class to set http client defaults
- L21-30 _public method_ `public static Polly.Retry.AsyncRetryPolicy<HttpResponseMessage> GetRetryPolicy()` — When services can be used, utilize this helper to get this policy that handles retries ex. ServicesCollection.AddHttpClient<TelemetryService>().AddPolicyHandler(HttpClientDefaults.GetPolicy());
- L36-49 _public method_ `public static HttpClient GetClient()` — Creates a HttpClient with the default retry policy

### `Source/Programs/Shared/EpicGames.Core/Telemetry/SimpleJsonTelemetry.cs` (EpicGames.Core)


#### class `EpicGames.Core.Telemetry.SimpleJsonTelemetry`  
`public class SimpleJsonTelemetry : IDisposable`  
_public; L14-86_
- inherits: `IDisposable`
- desc: Simple telemetry wrapper for accessing JSON data
- L16 _private field_ `private readonly HttpClient _httpClient`
- L17 _private field_ `private bool _disposed = false`
- L22-28 _public ctor_ `public SimpleJsonTelemetry(string server)` — Constructor
- L33-36 _private* dtor_ `~SimpleJsonTelemetry()` — Destructor
- L41-59 _public method_ `public async Task<T?> GetAsync<T>(string endPoint) where T : new()` — Fetch the data at a given endpoint and return it as string
- L64-68 _public method_ `public void Dispose()` — Implement IDisposable.
- L74-85 _protected method_ `protected virtual void Dispose(bool disposing)` — Implement IDisposable.

### `Source/Programs/Shared/EpicGames.Core/Telemetry/TelemetryService.cs` (EpicGames.Core)


#### interface `EpicGames.Core.Telemetry.ITelemetryService`  
`public interface ITelemetryService<T> : IDisposable where T : class`  
_public; L15-27_
- inherits: `IDisposable`
- constraints: `where T : class`
- desc: Base interface for a TelemetryService. Derived from IDisposable as we want to make sure implementation handles flushing remaining events in the case that the service is disposed of. This usually would happen in a using block with an instance of the ITelemetryService derived class. If registering as part of a servicescollection, Flush should still be called in shutdown code.
- L21 _public method_ `public void RecordEvent(T eventData)` — Record an event to be processed
- L26 _public method_ `public void FlushEvents()` — Function to flush pending events

### `Source/Programs/Shared/EpicGames.Core/ThreadPoolWorkQueue.cs` (EpicGames.Core)


#### class `EpicGames.Core.ThreadPoolWorkQueue`  
`public sealed class ThreadPoolWorkQueue : IDisposable`  
_public; L13-189_
- inherits: `IDisposable`
- desc: Allows queuing a large number of tasks to a thread pool and waiting for them all to complete.
- L18 _private* field_ `readonly Lock _lockObject = new()` — Object used for controlling access to updating _lockObject
- L23 _private* field_ `int _numOutstandingJobs` — Number of jobs remaining in the queue. This is updated in an atomic way.
- L29 _private* field_ `ManualResetEvent? _emptyEvent = new(true)` — Event which indicates whether the queue is empty.
- L35 _private* field_ `readonly ConcurrentBag<Exception> _exceptions = []` — Exceptions which occurred while executing tasks
- L40-42 _public ctor_ `public ThreadPoolWorkQueue()` — Default constructor
- L47-65 _public method_ `public void Dispose()` — Waits for the queue to drain, and disposes of it
- L70 _public property_ `public int NumRemaining => ...` — Returns the number of items remaining in the queue
- L76-88 _public method_ `public void Enqueue(Action actionToExecute)` — Adds an item to the queue
- L94-111 _private* method_ `void Execute(object? actionToExecute)` — Internal method to execute an action
- L116-120 _private* method_ `ManualResetEvent GetEmptyEvent()` — Atomically read the contents of _emptyEvent, throwing an exception if it's already null (indicating that the object has been disposed)
- L125-129 _public method_ `public void Wait()` — Waits for all queued tasks to finish
- L136-139 _public method_ `public bool Wait(int millisecondsTimeout)` — Waits for all queued tasks to finish, or the timeout to elapse
- L146-154 _public method_ `public bool Wait(TimeSpan timeout)` — Waits for all queued tasks to finish, or the timeout to elapse
- L159-165 _public method_ `public void RethrowExceptions()` — Checks for any exceptions which ocurred in queued tasks, and re-throws them on the current thread
- L172-188 _private method_ `private void SetEventState()` — When the number of outstanding jobs transitions between 0 and 1 and visa-versa, we need to set the event based on the actual counter. While the adjustment of the counter happens with interlocked instructions, the setting of the event must be done under a lock to serialize the set/reset

### `Source/Programs/Shared/EpicGames.Core/TraceSpan.cs` (EpicGames.Core)


#### interface `EpicGames.Core.ITraceSpan`  
`public interface ITraceSpan : IDisposable`  
_public; L17-25_
- inherits: `IDisposable`
- desc: Interface for a trace span
- L24 _public* method_ `void AddMetadata(string name, string value)` — Adds additional metadata to this scope

#### interface `EpicGames.Core.ITraceSink`  
`public interface ITraceSink`  
_public; L30-45_
- desc: Sink for tracing information
- L39 _public* method_ `ITraceSpan Create(string operation, string? resource, string? service)` — Create a new trace span
- L44 _public* method_ `void Flush()` — Flush all the current trace data

#### class `EpicGames.Core.JsonTraceSink`  
`public class JsonTraceSink : ITraceSink`  
_public; L50-174_
- inherits: `ITraceSink`
- desc: Default implementation of ITraceSink. Writes trace information to a JSON file on application exit if the UE_TELEMETRY_DIR environment variable is set.
- L86 _private* field_ `readonly DirectoryReference _telemetryDir` — Output directory for telemetry info
- L91 _private* field_ `readonly List<TraceSpanImpl> _spans = []` — The current scope provider
- L97-100 _public ctor_ `public JsonTraceSink(DirectoryReference telemetryDir)` — Constructor
- L105-110 _public method_ `public ITraceSpan Create(string name, string? resource = null, string? service = null)` — Creates a scope using the current provider
- L115-129 _public method_ `public void Flush()` — Saves all the scope information to a file
- L131-173 _private method_ `private void FlushImpl()`

#### class `EpicGames.Core.JsonTraceSink.TraceSpanImpl`  
`class TraceSpanImpl : ITraceSpan`  
_private*; L52-81_
- inherits: `ITraceSpan`
- L54 _public property_ `public string Name { get; }`
- L55 _public property_ `public string? Resource { get; }`
- L56 _public property_ `public string? Service { get; }`
- L57 _public property_ `public DateTimeOffset StartTime { get; }`
- L58 _public property_ `public DateTimeOffset? FinishTime { get; set; }`
- L59 _public property_ `public Dictionary<string, string> Metadata { get; }`
- L61-67 _public ctor_ `public TraceSpanImpl(string name, string? resource, string? service)`
- L69-72 _public method_ `public void AddMetadata(string name, string value)`
- L74-80 _public method_ `public void Dispose()`

#### class `EpicGames.Core.TraceSpan`  
`public static class TraceSpan`  
_public; L179-276_
- desc: Methods for creating ITraceScope instances
- L210 _private* field_ `static readonly List<ITraceSink> s_sinks = GetDefaultSinks()` — The sinks to use
- L216-227 _private* method_ `static List<ITraceSink> GetDefaultSinks()` — Build a list of default sinks
- L233-236 _public method_ `public static void AddSink(ITraceSink sink)` — Adds a new sink
- L242-245 _public method_ `public static void RemoveSink(ITraceSink sink)` — Remove a sink from the current list
- L250-264 _public method_ `public static ITraceSpan Create(string operation, string? resource = null, string? service = null)` — Creates a scope using the current provider
- L269-275 _public method_ `public static void Flush()` — Saves all the scope information to a file

#### class `EpicGames.Core.TraceSpan.CombinedTraceSpan`  
`class CombinedTraceSpan : ITraceSpan`  
_private*; L181-205_
- inherits: `ITraceSpan`
- L183 _private* field_ `readonly ITraceSpan[] _spans`
- L185-188 _public ctor_ `public CombinedTraceSpan(ITraceSpan[] spans)`
- L190-196 _public method_ `public void AddMetadata(string name, string value)`
- L198-204 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.Core/UHTTypes.cs` (EpicGames.Core)


#### enum `EpicGames.Core.EGeneratedCodeVersion`  
`public enum EGeneratedCodeVersion`  
_public; L23-44_
- desc: Defines the version of the code generation to be used. This MUST be kept in sync with EGeneratedBodyVersion defined in Engine\Source\Programs\UnrealHeaderTool\Private\GeneratedCodeVersion.h.
- L28 _public* enumerator_ `None` — Version not set or the default is to be used.
- L33 _public* enumerator_ `V1`
- L38 _public* enumerator_ `V2`
- L43 _public* enumerator_ `VLatest = V2`

#### enum `EpicGames.Core.EPackageOverrideType`  
`public enum EPackageOverrideType`  
_public; L49-57_
- desc: Build module override type to add additional PKG flags if necessary, mirrored in ModuleRules.cs, enum PackageOverrideType
- L51 _public* enumerator_ `None`
- L52 _public* enumerator_ `EditorOnly`
- L53 _public* enumerator_ `EngineDeveloper`
- L54 _public* enumerator_ `GameDeveloper`
- L55 _public* enumerator_ `EngineUncookedOnly`
- L56 _public* enumerator_ `GameUncookedOnly`

#### enum `EpicGames.Core.UHTModuleType`  
`public enum UHTModuleType`  
_public; L62-75_
- desc: Type of module. This should be sorted by the order in which we expect modules to be built.
- L64 _public* enumerator_ `Program`
- L65 _public* enumerator_ `EngineRuntime`
- L66 _public* enumerator_ `EngineUncooked`
- L67 _public* enumerator_ `EngineDeveloper`
- L68 _public* enumerator_ `EngineEditor`
- L69 _public* enumerator_ `EngineThirdParty`
- L70 _public* enumerator_ `GameRuntime`
- L71 _public* enumerator_ `GameUncooked`
- L72 _public* enumerator_ `GameDeveloper`
- L73 _public* enumerator_ `GameEditor`
- L74 _public* enumerator_ `GameThirdParty`

#### enum `EpicGames.Core.UHTVerseScope`  
`public enum UHTVerseScope`  
_public; L80-101_
- desc: Describes the origin and visibility of Verse code
- L85 _public* enumerator_ `PublicAPI` — Created by Epic and only public definitions will be visible to public users
- L90 _public* enumerator_ `InternalAPI` — Created by Epic and is entirely hidden from public users
- L95 _public* enumerator_ `PublicUser` — Created by a public user
- L100 _public* enumerator_ `InternalUser` — Created by an Epic internal user

#### enum `EpicGames.Core.UhtCompiledInObjectFormat`  
`public enum UhtCompiledInObjectFormat`  
_public; L108-135_
- attrs: `[Flags]`
- desc: Types of code to generate to initialize compiled-in UObject instances. Flags to allow multiple formats to be generated at once for development/debugging.
- L113 _public* enumerator_ `None = 0x0` — No flags, should not be configured as a desired output type.
- L118 _public* enumerator_ `Params = 0x1` — Generate params structs which will be used to initialize UObjects on the heap at runtime.
- L124 _public* enumerator_ `ConstInit = 0x2` — Generate declarations of constinit variables of UObject-derived types allowing these objects to be stored in the binary's data segment.
- L129 _public* enumerator_ `Default = Params` — Default setting to use
- L134 _public* enumerator_ `All = Params | ConstInit` — Generate all possible types at once for comparison

#### record struct `EpicGames.Core.UHTTargetSettings`  
`public record struct UHTTargetSettings`  
_public; L140-195_
- desc: Per-target settings for UHT to control features that need to be the same across all modules.
- L142-144 _public ctor_ `public UHTTargetSettings()`
- L147-152 _public ctor_ `public UHTTargetSettings(BinaryArchiveReader reader) : this()` — attrs: `[SetsRequiredMembers]`
- L154-159 _public method_ `public readonly void Write(BinaryArchiveWriter writer)`
- L161-166 _public method_ `public readonly void Write(IMemoryWriter writer)`
- L172 _public property_ `public UhtCompiledInObjectFormat CompiledInObjectFormat { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — What type of code to generate for compiled-on UObject instances such as UClass instances.
- L178 _public property_ `public bool GenerateEnumMaxValues { get; set; }` — Whether to generate a name for the maximum value of UENUMs where one was not found in the authored code. If this is false, the UEnum code will generate it at runtime if it can do so without creating a collision.
- L184 _public property_ `public bool ValidateModuleDependencies { get; set; }` — Placeholder value to control whether or not UHT validates module dependencies from UBT to find missing dependencies which are needed because of generated code (e.g. FStructBaseChain references)
- L189 _public property_ `public bool EnableInputCacheRead { get; set; }` — If true, enable the input cache read
- L194 _public property_ `public bool EnableInputCacheWrite { get; set; }` — If true, enable the input cache write

#### class `EpicGames.Core.UHTManifest`  
`public class UHTManifest`  
_public; L197-310_
- L278 _public property_ `public bool IsGameTarget { get; set; }` — True if the current target is a game target
- L283 _public property_ `public string RootLocalPath { get; set; }` — The engine path on the local machine
- L288 _public property_ `public string TargetName { get; set; }` — Name of the target currently being compiled
- L293 _public property_ `public string ExternalDependenciesFile { get; set; }` — File to contain additional dependencies that the generated code depends on
- L298 _public property_ `public UHTTargetSettings TargetSettings { set; get; }` — Target-wide settings for UHT/code generation.
- L303 _public property_ `public List<Module> Modules { get; set; }` — List of modules
- L309 _public property_ `public List<string> UhtPlugins { get; set; }` — List of active UHT plugins. Only used by the C# version of UHT. This list contains plugins from only modules listed above.

#### class `EpicGames.Core.UHTManifest.Module`  
`public class Module`  
_public; L199-273_
- L201 _public property_ `public string Name { get; set; }`
- L203 _public property_ `public UHTModuleType ModuleType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- L205 _public property_ `public EPackageOverrideType OverrideModuleType { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- L206 _public property_ `public string BaseDirectory { get; set; }`
- L207 _public property_ `public List<string> IncludePaths { get; set; }`
- L208 _public property_ `public string OutputDirectory { get; set; }`
- L209 _public property_ `public List<string> ClassesHeaders { get; set; }`
- L210 _public property_ `public List<string> PublicHeaders { get; set; }`
- L211 _public property_ `public List<string> InternalHeaders { get; set; }`
- L212 _public property_ `public List<string> PrivateHeaders { get; set; }`
- L213 _public property_ `public List<string> PublicDefines { get; set; }`
- L216 _public property_ `public List<string> ModuleDependencies { get; set; }`
- L217 _public property_ `public string? GeneratedCPPFilenameBase { get; set; }`
- L218 _public property_ `public bool SaveExportedHeaders { get; set; }`
- L221 _public property_ `public EGeneratedCodeVersion GeneratedCodeVersion { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))] [JsonPropertyName("UHTGeneratedCodeVersion")]`
- L222 _public property_ `public string VersePath { get; set; }`
- L224 _public property_ `public UHTVerseScope VerseScope { get; set; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- L225 _public property_ `public bool HasVerse { get; set; }`
- L226 _public property_ `public string VerseMountPoint { get; set; }`
- L227 _public property_ `public string VersePackageName { get; set; }`
- L228 _public property_ `public string VerseDirectoryPath { get; set; }`
- L229 _public property_ `public List<string> VerseDependencies { get; set; }`
- L230 _public property_ `public bool AlwaysExportStructs { get; set; }`
- L231 _public property_ `public bool AlwaysExportEnums { get; set; }`
- L232 _public property_ `public bool AllowUETypesInNamespaces { get; set; }`
- L233 _public property_ `public bool MinimizeGeneratedIncludes { get; set; }`
- L235-238 _public method_ `public override string ToString()`
- L240-261 _public method_ `public bool TryGetDefine(string name, out string? value)`
- L263-272 _public method_ `public bool TryGetDefine(string name, out int value)`

### `Source/Programs/Shared/EpicGames.Core/UnrealEngineTypes.cs` (EpicGames.Core)


#### enum `EpicGames.Core.CompilationResult`  
`public enum CompilationResult`  
_public; L22-88_
- desc: Standard return codes used by UBT and UHT This MUST be kept in sync with EGeneratedBodyVersion defined in Engine\Source\Runtime\Core\Public\Misc\CompilationResult.h
- L27 _public* enumerator_ `Succeeded = 0` — Compilation succeeded
- L32 _public* enumerator_ `Canceled = 1` — Build was canceled, this is used on the engine side only
- L37 _public* enumerator_ `UpToDate = 2` — All targets were up to date, used only with -canskiplink
- L42 _public* enumerator_ `CrashOrAssert = 3` — The process has most likely crashed. This is what UE returns in case of an assert
- L47 _public* enumerator_ `FailedDueToHeaderChange = 4` — Compilation failed because generated code changed which was not supported
- L52 _public* enumerator_ `FailedDueToEngineChange = 5` — Compilation failed due to the engine modules needing to be rebuilt
- L57 _public* enumerator_ `OtherCompilationError = 6` — Compilation failed due to compilation errors
- L62 _public* enumerator_ `LiveCodingLimitError = 7` — Compilation failed due to live coding action limit being exceeded
- L67 _public* enumerator_ `RulesError = 8` — Compilation failed due to TargetRules or ModuleRules errors
- L72 _public* enumerator_ `ActionGraphInvalid = 9` — Compilation failed due to invalid action graph
- L77 _public* enumerator_ `ConflictingInstance = 10` — Another instance of UBT was already running
- L82 _public* enumerator_ `Unsupported` — Compilation is not supported in the current build
- L87 _public* enumerator_ `Unknown` — Unknown error

#### class `EpicGames.Core.CompilationResultExtensions`  
`public static class CompilationResultExtensions`  
_public; L93-105_
- desc: Helper extensions for CompilationResult
- L101-104 _public method_ `public static bool Succeeded(this CompilationResult Result)` — Test to see if the return code is a success

#### enum `EpicGames.Core.EClassFlags`  
`public enum EClassFlags : uint`  
_public; L114-308_
- attrs: `[Flags]`
- inherits: `uint`
- desc: Flags describing a class. This MUST be kept in sync with EClassFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\ObjectMacros.h
- L119 _public* enumerator_ `None = 0x00000000u` — No Flags
- L124 _public* enumerator_ `Abstract = 0x00000001u` — Class is abstract and can't be instantiated directly.
- L129 _public* enumerator_ `DefaultConfig = 0x00000002u` — Save object configuration only to Default INIs, never to local INIs. Must be combined with "Config"
- L134 _public* enumerator_ `Config = 0x00000004u` — Load object configuration at construction time.
- L139 _public* enumerator_ `Transient = 0x00000008u` — This object type can't be saved; null it out at save time.
- L144 _public* enumerator_ `Optional = 0x00000010u` — This object type may not be available in certain context. (i.e. game runtime or in certain configuration). Optional class data is saved separately to other object types. (i.e. might use sidecar files)
- L149 _public* enumerator_ `MatchedSerializers = 0x00000020u`
- L154 _public* enumerator_ `ProjectUserConfig = 0x00000040u` — Indicates that the config settings for this class will be saved to Project/User*.ini (similar to "GlobalUserConfig")
- L159 _public* enumerator_ `Native = 0x00000080u` — Class is a native class - native interfaces will have "Native" set, but not RF_MarkAsNative
- L164 _public* enumerator_ `Partial = 0x00000100u` — Class is a partial class
- L169 _public* enumerator_ `NotPlaceable = 0x00000200u` — Do not allow users to create in the editor.
- L174 _public* enumerator_ `PerObjectConfig = 0x00000400u` — Handle object configuration on a per-object basis, rather than per-class.
- L179 _public* enumerator_ `ReplicationDataIsSetUp = 0x00000800u` — Whether SetUpRuntimeReplicationData still needs to be called for this class
- L184 _public* enumerator_ `EditInlineNew = 0x00001000u` — Class can be constructed from editinline New button.
- L189 _public* enumerator_ `CollapseCategories = 0x00002000u` — Display properties in the editor without using categories.
- L194 _public* enumerator_ `Interface = 0x00004000u` — Class is an interface
- L199 _public* enumerator_ `PerPlatformConfig = 0x00008000u` — Config for this class is overridden in platform inis, reload when previewing platforms
- L204 _public* enumerator_ `Const = 0x00010000u` — all properties and functions in this class are const and should be exported as const
- L209 _public* enumerator_ `NeedsDeferredDependencyLoading = 0x00020000u` — Class flag indicating objects of this class need deferred dependency loading
- L214 _public* enumerator_ `CompiledFromBlueprint = 0x00040000u` — Indicates that the class was created from blueprint source material
- L219 _public* enumerator_ `MinimalAPI = 0x00080000u` — Indicates that only the bare minimum bits of this class should be DLL exported/imported
- L224 _public* enumerator_ `RequiredAPI = 0x00100000u` — Indicates this class must be DLL exported/imported (along with all of it's members)
- L229 _public* enumerator_ `DefaultToInstanced = 0x00200000u` — Indicates that references to this class default to instanced. Used to be subclasses of UComponent, but now can be any UObject
- L234 _public* enumerator_ `TokenStreamAssembled = 0x00400000u` — Indicates that the parent token stream has been merged with ours.
- L239 _public* enumerator_ `HasInstancedReference = 0x00800000u` — Class has component properties.
- L244 _public* enumerator_ `Hidden = 0x01000000u` — Don't show this class in the editor class browser or edit inline new menus.
- L249 _public* enumerator_ `Deprecated = 0x02000000u` — Don't save objects of this class when serializing
- L254 _public* enumerator_ `HideDropDown = 0x04000000u` — Class not shown in editor drop down for class selection
- L259 _public* enumerator_ `GlobalUserConfig = 0x08000000u` — Class settings are saved to [AppData]/..../Blah.ini (as opposed to "DefaultConfig")
- L264 _public* enumerator_ `Intrinsic = 0x10000000u` — Class was declared directly in C++ and has no boilerplate generated by UnrealHeaderTool
- L269 _public* enumerator_ `Constructed = 0x20000000u` — Class has already been constructed (maybe in a previous DLL version before hot-reload).
- L274 _public* enumerator_ `ConfigDoNotCheckDefaults = 0x40000000u` — Indicates that object configuration will not check against ini base/defaults when serialized
- L279 _public* enumerator_ `NewerVersionExists = 0x80000000u` — Class has been consigned to oblivion as part of a blueprint recompile, and a newer version currently exists.
- L284 _public* enumerator_ `Inherit = Transient | Optional | DefaultConfig | Config | Partial | PerObjectConfig | ConfigDoNotCheckDefaults | NotPlaceable | Const | HasInstancedReference | Deprecated | DefaultToInstanced | GlobalUserConfig | ProjectUserConfig | NeedsDeferredDependencyLoading` — Flags to inherit from base class
- L290 _public* enumerator_ `RecompilerClear = Inherit | Abstract | Native | Intrinsic | TokenStreamAssembled` — These flags will be cleared by the compiler when the class is parsed during script compilation
- L295 _public* enumerator_ `ShouldNeverBeLoaded = Native | Optional | Intrinsic | TokenStreamAssembled` — These flags will be cleared by the compiler when the class is parsed during script compilation
- L300 _public* enumerator_ `ScriptInherit = Inherit | EditInlineNew | CollapseCategories` — These flags will be inherited from the base class only for non-intrinsic classes
- L305 _public* enumerator_ `SaveInCompiledInClasses = Abstract | DefaultConfig | GlobalUserConfig | ProjectUserConfig | PerPlatformConfig | Config | Transient | Optional | Native | Partial | NotPlaceable | PerObjectConfig | ConfigDoNotCheckDefaults | EditInlineNew | CollapseCategories | Interface | DefaultToInstanced | HasInstancedReference | Hidden | Deprecated | HideDropDown | Intrinsic | Const | MinimalAPI | RequiredAPI | MatchedSerializers | NeedsDeferredDependencyLoading` — This is used as a mask for the flags put into generated code for "compiled in" classes.

#### class `EpicGames.Core.EClassFlagsExtensions`  
`public static class EClassFlagsExtensions`  
_public; L313-329_
- desc: Extension message for EClassFlags
- L315-318 _public method_ `public static bool HasAnyFlags(this EClassFlags InFlags, EClassFlags TestFlags)`
- L320-323 _public method_ `public static bool HasAllFlags(this EClassFlags InFlags, EClassFlags TestFlags)`
- L325-328 _public method_ `public static bool HasExactFlags(this EClassFlags InFlags, EClassFlags TestFlags, EClassFlags MatchFlags)`

#### enum `EpicGames.Core.EClassCastFlags`  
`public enum EClassCastFlags : ulong`  
_public; L338-407_
- attrs: `[Flags]`
- inherits: `ulong`
- desc: Flags used for quickly casting classes of certain types; all class cast flags are inherited This MUST be kept in sync with EClassCastFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\ObjectMacros.h
- L340 _public* enumerator_ `None = 0x0000000000000000`
- L342 _public* enumerator_ `UField = 0x0000000000000001`
- L343 _public* enumerator_ `FInt8Property = 0x0000000000000002`
- L344 _public* enumerator_ `UEnum = 0x0000000000000004`
- L345 _public* enumerator_ `UStruct = 0x0000000000000008`
- L346 _public* enumerator_ `UScriptStruct = 0x0000000000000010`
- L347 _public* enumerator_ `UClass = 0x0000000000000020`
- L348 _public* enumerator_ `FByteProperty = 0x0000000000000040`
- L349 _public* enumerator_ `FIntProperty = 0x0000000000000080`
- L350 _public* enumerator_ `FFloatProperty = 0x0000000000000100`
- L351 _public* enumerator_ `FUInt64Property = 0x0000000000000200`
- L352 _public* enumerator_ `FClassProperty = 0x0000000000000400`
- L353 _public* enumerator_ `FUInt32Property = 0x0000000000000800`
- L354 _public* enumerator_ `FInterfaceProperty = 0x0000000000001000`
- L355 _public* enumerator_ `FNameProperty = 0x0000000000002000`
- L356 _public* enumerator_ `FStrProperty = 0x0000000000004000`
- L357 _public* enumerator_ `FProperty = 0x0000000000008000`
- L358 _public* enumerator_ `FObjectProperty = 0x0000000000010000`
- L359 _public* enumerator_ `FBoolProperty = 0x0000000000020000`
- L360 _public* enumerator_ `FUInt16Property = 0x0000000000040000`
- L361 _public* enumerator_ `UFunction = 0x0000000000080000`
- L362 _public* enumerator_ `FStructProperty = 0x0000000000100000`
- L363 _public* enumerator_ `FArrayProperty = 0x0000000000200000`
- L364 _public* enumerator_ `FInt64Property = 0x0000000000400000`
- L365 _public* enumerator_ `FDelegateProperty = 0x0000000000800000`
- L366 _public* enumerator_ `FNumericProperty = 0x0000000001000000`
- L367 _public* enumerator_ `FMulticastDelegateProperty = 0x0000000002000000`
- L368 _public* enumerator_ `FObjectPropertyBase = 0x0000000004000000`
- L369 _public* enumerator_ `FWeakObjectProperty = 0x0000000008000000`
- L370 _public* enumerator_ `FLazyObjectProperty = 0x0000000010000000`
- L371 _public* enumerator_ `FSoftObjectProperty = 0x0000000020000000`
- L372 _public* enumerator_ `FTextProperty = 0x0000000040000000`
- L373 _public* enumerator_ `FInt16Property = 0x0000000080000000`
- L374 _public* enumerator_ `FDoubleProperty = 0x0000000100000000`
- L375 _public* enumerator_ `FSoftClassProperty = 0x0000000200000000`
- L376 _public* enumerator_ `UPackage = 0x0000000400000000`
- L377 _public* enumerator_ `ULevel = 0x0000000800000000`
- L378 _public* enumerator_ `AActor = 0x0000001000000000`
- L379 _public* enumerator_ `APlayerController = 0x0000002000000000`
- L380 _public* enumerator_ `APawn = 0x0000004000000000`
- L381 _public* enumerator_ `USceneComponent = 0x0000008000000000`
- L382 _public* enumerator_ `UPrimitiveComponent = 0x0000010000000000`
- L383 _public* enumerator_ `USkinnedMeshComponent = 0x0000020000000000`
- L384 _public* enumerator_ `USkeletalMeshComponent = 0x0000040000000000`
- L385 _public* enumerator_ `UBlueprint = 0x0000080000000000`
- L386 _public* enumerator_ `UDelegateFunction = 0x0000100000000000`
- L387 _public* enumerator_ `UStaticMeshComponent = 0x0000200000000000`
- L388 _public* enumerator_ `FMapProperty = 0x0000400000000000`
- L389 _public* enumerator_ `FSetProperty = 0x0000800000000000`
- L390 _public* enumerator_ `FEnumProperty = 0x0001000000000000`
- L391 _public* enumerator_ `USparseDelegateFunction = 0x0002000000000000`
- L392 _public* enumerator_ `FMulticastInlineDelegateProperty = 0x0004000000000000`
- L393 _public* enumerator_ `FMulticastSparseDelegateProperty = 0x0008000000000000`
- L394 _public* enumerator_ `FFieldPathProperty = 0x0010000000000000`
- L397 _public* enumerator_ `FLargeWorldCoordinatesRealProperty = 0x0080000000000000`
- L398 _public* enumerator_ `FOptionalProperty = 0x0100000000000000`
- L399 _public* enumerator_ `FVValueProperty = 0x0200000000000000`
- L400 _public* enumerator_ `FVRestValueProperty = 0x0400000000000000`
- L401 _public* enumerator_ `FVerseStringProperty = 0x0800000000000000`
- L402 _public* enumerator_ `FUtf8StrProperty = 0x1000000000000000`
- L403 _public* enumerator_ `FAnsiStrProperty = 0x2000000000000000`
- L404 _public* enumerator_ `FVCellProperty = 0x4000000000000000`
- L406 _public* enumerator_ `AllFlags = UInt64.MaxValue`

#### class `EpicGames.Core.EClassCastFlagsExtensions`  
`public static class EClassCastFlagsExtensions`  
_public; L412-428_
- desc: Helper extensions for EClassCastFlags
- L414-417 _public method_ `public static bool HasAnyFlags(this EClassCastFlags InFlags, EClassCastFlags TestFlags)`
- L419-422 _public method_ `public static bool HasAllFlags(this EClassCastFlags InFlags, EClassCastFlags TestFlags)`
- L424-427 _public method_ `public static bool HasExactFlags(this EClassCastFlags InFlags, EClassCastFlags TestFlags, EClassCastFlags MatchFlags)`

#### enum `EpicGames.Core.EEnumFlags`  
`public enum EEnumFlags : uint`  
_public; L437-442_
- attrs: `[Flags]`
- inherits: `uint`
- desc: Flags describing a UEnum This MUST be kept in sync with EEnumFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\ObjectMacros.h
- L439 _public* enumerator_ `None`
- L440 _public* enumerator_ `Flags = 1 << 0`
- L441 _public* enumerator_ `NewerVersionExists = 1 << 1`

#### class `EpicGames.Core.EEnumFlagsExtensions`  
`public static class EEnumFlagsExtensions`  
_public; L447-463_
- desc: Helper extensions for EEnumFlags
- L449-452 _public method_ `public static bool HasAnyFlags(this EEnumFlags InFlags, EEnumFlags TestFlags)`
- L454-457 _public method_ `public static bool HasAllFlags(this EEnumFlags InFlags, EEnumFlags TestFlags)`
- L459-462 _public method_ `public static bool HasExactFlags(this EEnumFlags InFlags, EEnumFlags TestFlags, EEnumFlags MatchFlags)`

#### enum `EpicGames.Core.EFunctionFlags`  
`public enum EFunctionFlags : uint`  
_public; L472-636_
- attrs: `[Flags]`
- inherits: `uint`
- desc: Function flags. This MUST be kept in sync with EFunctionFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\Script.h
- L474 _public* enumerator_ `None = 0x00000000`
- L479 _public* enumerator_ `Final = 0x00000001` — Function is final (prebindable, non-overridable function).
- L484 _public* enumerator_ `RequiredAPI = 0x00000002` — Indicates this function is DLL exported/imported.
- L489 _public* enumerator_ `BlueprintAuthorityOnly = 0x00000004` — Function will only run if the object has network authority
- L494 _public* enumerator_ `BlueprintCosmetic = 0x00000008` — Function is cosmetic in nature and should not be invoked on dedicated servers
- L502 _public* enumerator_ `Net = 0x00000040` — Function is network-replicated.
- L507 _public* enumerator_ `NetReliable = 0x00000080` — Function should be sent reliably on the network.
- L512 _public* enumerator_ `NetRequest = 0x00000100` — Function is sent to a net service
- L517 _public* enumerator_ `Exec = 0x00000200` — Executable from command line.
- L522 _public* enumerator_ `Native = 0x00000400` — Native function.
- L527 _public* enumerator_ `Event = 0x00000800` — Event function.
- L532 _public* enumerator_ `NetResponse = 0x00001000` — Function response from a net service
- L537 _public* enumerator_ `Static = 0x00002000` — Static function.
- L542 _public* enumerator_ `NetMulticast = 0x00004000` — Function is networked multicast Server -> All Clients
- L547 _public* enumerator_ `UbergraphFunction = 0x00008000` — Function is used as the merge 'ubergraph' for a blueprint, only assigned when using the persistent 'ubergraph' frame
- L552 _public* enumerator_ `MulticastDelegate = 0x00010000` — Function is a multi-cast delegate signature (also requires Delegate to be set!)
- L557 _public* enumerator_ `Public = 0x00020000` — Function is accessible in all classes (if overridden, parameters must remain unchanged).
- L562 _public* enumerator_ `Private = 0x00040000` — Function is accessible only in the class it is defined in (cannot be overridden, but function name may be reused in subclasses. IOW: if overridden, parameters don't need to match, and Super.Func() cannot be accessed since it's private.)
- L567 _public* enumerator_ `Protected = 0x00080000` — Function is accessible only in the class it is defined in and subclasses (if overridden, parameters much remain unchanged).
- L572 _public* enumerator_ `Delegate = 0x00100000` — Function is delegate signature (either single-cast or multi-cast, depending on whether MulticastDelegate is set.)
- L577 _public* enumerator_ `NetServer = 0x00200000` — Function is executed on servers (set by replication code if passes check)
- L582 _public* enumerator_ `HasOutParms = 0x00400000` — function has out (pass by reference) parameters
- L587 _public* enumerator_ `HasDefaults = 0x00800000` — function has structs that contain defaults
- L592 _public* enumerator_ `NetClient = 0x01000000` — function is executed on clients
- L597 _public* enumerator_ `DLLImport = 0x02000000` — function is imported from a DLL
- L602 _public* enumerator_ `BlueprintCallable = 0x04000000` — function can be called from blueprint code
- L607 _public* enumerator_ `BlueprintEvent = 0x08000000` — function can be overridden/implemented from a blueprint
- L612 _public* enumerator_ `BlueprintPure = 0x10000000` — function can be called from blueprint code, and is also pure (produces no side effects). If you set this, you should set BlueprintCallable as well.
- L617 _public* enumerator_ `EditorOnly = 0x20000000` — function can only be called from an editor script.
- L622 _public* enumerator_ `Const = 0x40000000` — function can be called from blueprint code, and only reads state (never writes state)
- L627 _public* enumerator_ `NetValidate = 0x80000000` — function must supply a _Validate implementation
- L629 _public* enumerator_ `AllFlags = 0xFFFFFFFF`
- L632 _public* enumerator_ `FuncInherit = Exec | Event | BlueprintCallable | BlueprintEvent | BlueprintAuthorityOnly | BlueprintCosmetic | Const`
- L633 _public* enumerator_ `FuncOverrideMatch = Exec | Final | Static | Public | Protected | Private`
- L634 _public* enumerator_ `NetFuncFlags = Net | NetReliable | NetServer | NetClient | NetMulticast`
- L635 _public* enumerator_ `AccessSpecifiers = Public | Private | Protected`

#### class `EpicGames.Core.EFunctionFlagsExtensions`  
`public static class EFunctionFlagsExtensions`  
_public; L641-657_
- desc: Helper extensions for EFunctionFlags
- L643-646 _public method_ `public static bool HasAnyFlags(this EFunctionFlags InFlags, EFunctionFlags TestFlags)`
- L648-651 _public method_ `public static bool HasAllFlags(this EFunctionFlags InFlags, EFunctionFlags TestFlags)`
- L653-656 _public method_ `public static bool HasExactFlags(this EFunctionFlags InFlags, EFunctionFlags TestFlags, EFunctionFlags MatchFlags)`

#### enum `EpicGames.Core.EInternalObjectFlags`  
`public enum EInternalObjectFlags : int`  
_public; L666-750_
- attrs: `[Flags]`
- inherits: `int`
- desc: Objects flags for internal use(GC, low level UObject code) This MUST be kept in sync with EInternalObjectFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\ObjectMacros.h
- L668 _public* enumerator_ `None = 0`
- L674 _public* enumerator_ `ReachabilityFlag0 = 1 << 14` — One of the flags used by Garbage Collector to determine UObject's reachability state
- L679 _public* enumerator_ `ReachabilityFlag1 = 1 << 15` — One of the flags used by Garbage Collector to determine UObject's reachability state
- L684 _public* enumerator_ `ReachabilityFlag2 = 1 << 16` — One of the flags used by Garbage Collector to determine UObject's reachability state
- L689 _public* enumerator_ `AutoRTFMConstructionAborted = 1 << 17` — Object was constructed in an AutoRTFM transaction that has been aborted
- L694 _public* enumerator_ `LoaderImport = 1 << 20` — Object is ready to be imported by another package during loading
- L699 _public* enumerator_ `Garbage = 1 << 21` — Garbage from logical point of view and should not be referenced. This flag is mirrored in EObjectFlags as RF_Garbage for performance
- L704 _public* enumerator_ `AsyncLoadingPhase1 = 1 << 22` — Object is being asynchronously loaded.
- L709 _public* enumerator_ `ReachableInCluster = 1 << 23` — External reference to object in cluster exists
- L714 _public* enumerator_ `ClusterRoot = 1 << 24` — Root of a cluster
- L719 _public* enumerator_ `Native = 1 << 25` — Native (UClass only).
- L724 _public* enumerator_ `Async = 1 << 26` — Object exists only on a different thread than the game thread.
- L729 _public* enumerator_ `AsyncLoadingPhase2 = 1 << 27` — Object is being asynchronously loaded.
- L734 _public* enumerator_ `Unreachable = 1 << 28` — Object is not reachable on the object graph.
- L739 _public* enumerator_ `RefCounted = 1 << 29` — Object currently has ref-counts associated with it.
- L744 _public* enumerator_ `RootSet = 1 << 30` — Object will not be garbage collected, even if unreferenced.
- L749 _public* enumerator_ `PendingConstruction = 1 << 31` — Object didn't have its class constructor called yet (only the UObjectBase one to initialize its most basic members)

#### class `EpicGames.Core.EInternalObjectFlagsExtensions`  
`public static class EInternalObjectFlagsExtensions`  
_public; L755-771_
- desc: Helper extensions for EInternalObjectFlags
- L757-760 _public method_ `public static bool HasAnyFlags(this EInternalObjectFlags InFlags, EInternalObjectFlags TestFlags)`
- L762-765 _public method_ `public static bool HasAllFlags(this EInternalObjectFlags InFlags, EInternalObjectFlags TestFlags)`
- L767-770 _public method_ `public static bool HasExactFlags(this EInternalObjectFlags InFlags, EInternalObjectFlags TestFlags, EInternalObjectFlags MatchFlags)`

#### enum `EpicGames.Core.EPackageFlags`  
`public enum EPackageFlags : ulong`  
_public; L780-928_
- attrs: `[Flags]`
- inherits: `ulong`
- desc: Package flags, passed into UPackage::SetPackageFlags and related functions This MUST be kept in sync with EPackageFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\ObjectMacros.h
- L785 _public* enumerator_ `None = 0x00000000` — No flags
- L790 _public* enumerator_ `NewlyCreated = 0x00000001` — Newly created package, not saved yet. In editor only.
- L795 _public* enumerator_ `ClientOptional = 0x00000002` — Purely optional for clients.
- L800 _public* enumerator_ `ServerSideOnly = 0x00000004` — Only needed on the server side.
- L805 _public* enumerator_ `CompiledIn = 0x00000010` — This package is from "compiled in" classes.
- L810 _public* enumerator_ `ForDiffing = 0x00000020` — This package was loaded just for the purposes of diffing
- L815 _public* enumerator_ `EditorOnly = 0x00000040` — This is editor-only package (for example: editor module script package)
- L820 _public* enumerator_ `Developer = 0x00000080` — Developer module
- L825 _public* enumerator_ `UncookedOnly = 0x00000100` — Loaded only in uncooked builds (i.e. runtime in editor)
- L830 _public* enumerator_ `Cooked = 0x00000200` — Package is cooked
- L835 _public* enumerator_ `ContainsNoAsset = 0x00000400` — Package doesn't contain any asset object (although asset tags can be present)
- L840 _public* enumerator_ `NotExternallyReferenceable = 0x00000800` — Objects in this package cannot be referenced in a different plugin or mount point (i.e /Game -> /Engine)
- L845 _public* enumerator_ `AccessSpecifierEpicInternal = 0x00001000` — Objects in this package can only be referenced in a different plugin or mount point by Epic
- L850 _public* enumerator_ `UnversionedProperties = 0x00002000` — Uses unversioned property serialization instead of versioned tagged property serialization
- L855 _public* enumerator_ `ContainsMapData = 0x00004000` — Contains map data (UObjects only referenced by a single ULevel) but is stored in a different package
- L860 _public* enumerator_ `IsSaving = 0x00008000` — Temporarily set on a package while it is being saved.
- L865 _public* enumerator_ `Compiling = 0x00010000` — package is currently being compiled
- L870 _public* enumerator_ `ContainsMap = 0x00020000` — Set if the package contains a ULevel/ UWorld object
- L875 _public* enumerator_ `RequiresLocalizationGather = 0x00040000` — Set if the package contains any data to be gathered by localization
- L882 _public* enumerator_ `PlayInEditor = 0x00100000` — Set if the package was created for the purpose of PIE
- L887 _public* enumerator_ `ContainsScript = 0x00200000` — Package is allowed to contain UClass objects
- L892 _public* enumerator_ `DisallowExport = 0x00400000` — Editor should not export asset in this package
- L902 _public* enumerator_ `CookGenerated = 0x08000000` — This package This package was generated by the cooker and does not exist in the WorkspaceDomain
- L907 _public* enumerator_ `DynamicImports = 0x10000000` — This package should resolve dynamic imports from its export at runtime.
- L912 _public* enumerator_ `RuntimeGenerated = 0x20000000` — This package contains elements that are runtime generated, and may not follow standard loading order rules
- L917 _public* enumerator_ `ReloadingForCooker = 0x40000000` — This package is reloading in the cooker, try to avoid getting data we will never need. We won't save this package.
- L922 _public* enumerator_ `FilterEditorOnly = 0x80000000` — Package has editor-only data filtered out
- L927 _public* enumerator_ `TransientFlags = NewlyCreated | IsSaving | ReloadingForCooker` — Transient Flags are cleared when serializing to or from PackageFileSummary

#### class `EpicGames.Core.EPackageFlagsExtensions`  
`public static class EPackageFlagsExtensions`  
_public; L933-949_
- desc: Helper extensions for EPackageFlags
- L935-938 _public method_ `public static bool HasAnyFlags(this EPackageFlags InFlags, EPackageFlags TestFlags)`
- L940-943 _public method_ `public static bool HasAllFlags(this EPackageFlags InFlags, EPackageFlags TestFlags)`
- L945-948 _public method_ `public static bool HasExactFlags(this EPackageFlags InFlags, EPackageFlags TestFlags, EPackageFlags MatchFlags)`

#### enum `EpicGames.Core.EPropertyFlags`  
`public enum EPropertyFlags : ulong`  
_public; L959-1324_
- attrs: `[Flags]`
- inherits: `ulong`
- desc: Flags associated with each property in a class, overriding the property's default behavior. This MUST be kept in sync with EPropertyFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\ObjectMacros.h
- L961 _public* enumerator_ `None = 0`
- L966 _public* enumerator_ `Edit = 0x0000000000000001` — Property is user-settable in the editor.
- L971 _public* enumerator_ `ConstParm = 0x0000000000000002` — This is a constant function parameter
- L976 _public* enumerator_ `BlueprintVisible = 0x0000000000000004` — This property can be read by blueprint code
- L981 _public* enumerator_ `ExportObject = 0x0000000000000008` — Object can be exported with actor.
- L986 _public* enumerator_ `BlueprintReadOnly = 0x0000000000000010` — This property cannot be modified by blueprint code
- L991 _public* enumerator_ `Net = 0x0000000000000020` — Property is relevant to network replication.
- L996 _public* enumerator_ `EditFixedSize = 0x0000000000000040` — Indicates that elements of an array can be modified, but its size cannot be changed.
- L1001 _public* enumerator_ `Parm = 0x0000000000000080` — Function/When call parameter.
- L1006 _public* enumerator_ `OutParm = 0x0000000000000100` — Value is copied out after function call.
- L1011 _public* enumerator_ `ZeroConstructor = 0x0000000000000200` — memset is fine for construction
- L1016 _public* enumerator_ `ReturnParm = 0x0000000000000400` — Return value.
- L1021 _public* enumerator_ `DisableEditOnTemplate = 0x0000000000000800` — Disable editing of this property on an archetype/sub-blueprint
- L1026 _public* enumerator_ `NonNullable = 0x0000000000001000` — Object property can never be null
- L1031 _public* enumerator_ `Transient = 0x0000000000002000` — Property is transient: shouldn't be saved or loaded, except for Blueprint CDOs.
- L1036 _public* enumerator_ `Config = 0x0000000000004000` — Property should be loaded/saved as permanent profile.
- L1041 _public* enumerator_ `RequiredParm = 0x0000000000008000` — Parameter is required in blueprint. Not linking the parameter with a node will result in a compile error.
- L1046 _public* enumerator_ `DisableEditOnInstance = 0x0000000000010000` — Disable editing on an instance of this class
- L1051 _public* enumerator_ `EditConst = 0x0000000000020000` — Property is uneditable in the editor.
- L1056 _public* enumerator_ `GlobalConfig = 0x0000000000040000` — Load config from base class, not subclass.
- L1061 _public* enumerator_ `InstancedReference = 0x0000000000080000` — Property is a component references.
- L1066 _public* enumerator_ `ExperimentalExternalObjects = 0x0000000000100000` — Property saves objects in separate files, breaks hard links and reload them based on discovery.
- L1071 _public* enumerator_ `DuplicateTransient = 0x0000000000200000` — Property should always be reset to the default value during any type of duplication (copy/paste, binary duplication, etc.)
- L1079 _public* enumerator_ `SaveGame = 0x0000000001000000` — Property should be serialized for save games, this is only checked for game-specific archives with ArIsSaveGame
- L1084 _public* enumerator_ `NoClear = 0x0000000002000000` — Hide clear (and browse) button.
- L1091 _public* enumerator_ `ReferenceParm = 0x0000000008000000` — Value is passed by reference; "OutParam" and "Param" should also be set.
- L1096 _public* enumerator_ `BlueprintAssignable = 0x0000000010000000` — MC Delegates only. Property should be exposed for assigning in blueprint code
- L1101 _public* enumerator_ `Deprecated = 0x0000000020000000` — Property is deprecated. Read it from an archive, but don't save it.
- L1106 _public* enumerator_ `IsPlainOldData = 0x0000000040000000` — If this is set, then the property can be memcopied instead of CopyCompleteValue / CopySingleValue
- L1111 _public* enumerator_ `RepSkip = 0x0000000080000000` — Not replicated. For non replicated properties in replicated structs
- L1116 _public* enumerator_ `RepNotify = 0x0000000100000000` — Notify actors when a property is replicated
- L1121 _public* enumerator_ `Interp = 0x0000000200000000` — interpolatable property for use with cinematics
- L1126 _public* enumerator_ `NonTransactional = 0x0000000400000000` — Property isn't transacted
- L1131 _public* enumerator_ `EditorOnly = 0x0000000800000000` — Property should only be loaded in the editor
- L1136 _public* enumerator_ `NoDestructor = 0x0000001000000000` — No destructor
- L1143 _public* enumerator_ `AutoWeak = 0x0000004000000000` — Only used for weak pointers, means the export type is autoweak
- L1148 _public* enumerator_ `ContainsInstancedReference = 0x0000008000000000` — Property contains component references.
- L1153 _public* enumerator_ `AssetRegistrySearchable = 0x0000010000000000` — asset instances will add properties with this flag to the asset registry automatically
- L1158 _public* enumerator_ `SimpleDisplay = 0x0000020000000000` — The property is visible by default in the editor details view
- L1163 _public* enumerator_ `AdvancedDisplay = 0x0000040000000000` — The property is advanced and not visible by default in the editor details view
- L1168 _public* enumerator_ `Protected = 0x0000080000000000` — property is protected from the perspective of script
- L1173 _public* enumerator_ `BlueprintCallable = 0x0000100000000000` — MC Delegates only. Property should be exposed for calling in blueprint code
- L1178 _public* enumerator_ `BlueprintAuthorityOnly = 0x0000200000000000` — MC Delegates only. This delegate accepts (only in blueprint) only events with BlueprintAuthorityOnly.
- L1183 _public* enumerator_ `TextExportTransient = 0x0000400000000000` — Property shouldn't be exported to text format (e.g. copy/paste)
- L1188 _public* enumerator_ `NonPIEDuplicateTransient = 0x0000800000000000` — Property should only be copied in PIE
- L1193 _public* enumerator_ `ExposeOnSpawn = 0x0001000000000000` — Property is exposed on spawn
- L1198 _public* enumerator_ `PersistentInstance = 0x0002000000000000` — A object referenced by the property is duplicated like a component. (Each actor should have an own instance.)
- L1203 _public* enumerator_ `UObjectWrapper = 0x0004000000000000` — Property was parsed as a wrapper class like TSubclassOf<T>, FScriptInterface etc., rather than a USomething*
- L1208 _public* enumerator_ `HasGetValueTypeHash = 0x0008000000000000` — This property can generate a meaningful hash value.
- L1213 _public* enumerator_ `NativeAccessSpecifierPublic = 0x0010000000000000` — Public native access specifier
- L1218 _public* enumerator_ `NativeAccessSpecifierProtected = 0x0020000000000000` — Protected native access specifier
- L1223 _public* enumerator_ `NativeAccessSpecifierPrivate = 0x0040000000000000` — Private native access specifier
- L1228 _public* enumerator_ `SkipSerialization = 0x0080000000000000` — Property shouldn't be serialized, can still be exported to text
- L1233 _public* enumerator_ `TObjectPtr = 0x0100000000000000` — Property is a TObjectPtr instead of a USomething*. Need to differentiate between TObjectclassOf and TObjectPtr
- L1238 _public* enumerator_ `TObjectPtrWrapper = TObjectPtr | UObjectWrapper` — TObjectPtr properties are both wrapped and TObjectPtr
- L1243 _public* enumerator_ `ExperimentalOverridableLogic = 0x0200000000000000` — ****Experimental*** Property will use different logic to serialize knowing what changes are done against its default use the overridable information provided by the overridable manager on the object
- L1248 _public* enumerator_ `ExperimentalAlwaysOverriden = 0x0400000000000000` — ****Experimental*** Property should never inherit from the parent when using overridable serialization
- L1253 _public* enumerator_ `ExperimentalNeverOverriden = 0x0800000000000000` — ****Experimental*** Property should never be overridden when using overridable serialization
- L1258 _public* enumerator_ `AllowSelfReference = 0x1000000000000000` — Enables the instancing graph self referencing logic, delegates and verse function are already using this
- L1263 _public* enumerator_ `ForcePostConstructLink = 0x2000000000000000` — Use to force native UCLASS properties to be included in the PostConstructLink chain in a derived Blueprint class, regardless of whether it differs from the native class constructor-initialized value
- L1268 _public* enumerator_ `NativeAccessSpecifiers = NativeAccessSpecifierPublic | NativeAccessSpecifierProtected | NativeAccessSpecifierPrivate` — All Native Access Specifier flags
- L1273 _public* enumerator_ `ParmFlags = Parm | OutParm | ReturnParm | ReferenceParm | ConstParm | RequiredParm` — All parameter flags
- L1278 _public* enumerator_ `PropagateKeepInInner = NonNullable` — Flags to keep in the inner type when propagating container flags
- L1283 _public* enumerator_ `PropagateToArrayInner = ExportObject | PersistentInstance | InstancedReference | ContainsInstancedReference | Config | EditConst | Deprecated | EditorOnly | AutoWeak | UObjectWrapper | TObjectPtr` — Flags that are propagated to properties inside array container
- L1288 _public* enumerator_ `PropagateToOptionalInner = ExportObject | PersistentInstance | InstancedReference | ContainsInstancedReference | Config | EditConst | Deprecated | EditorOnly | AutoWeak | UObjectWrapper | Edit` — Flags that are propagated to properties inside optional container
- L1293 _public* enumerator_ `PropagateToMapValue = ExportObject | PersistentInstance | InstancedReference | ContainsInstancedReference | Config | EditConst | Deprecated | EditorOnly | AutoWeak | UObjectWrapper | TObjectPtr | Edit` — Flags that are propagated to value properties inside map container
- L1298 _public* enumerator_ `PropagateToMapKey = ExportObject | PersistentInstance | InstancedReference | ContainsInstancedReference | Config | EditConst | Deprecated | EditorOnly | AutoWeak | UObjectWrapper | TObjectPtr | Edit` — Flags that are propagated to key properties inside map container
- L1303 _public* enumerator_ `PropagateToSetElement = ExportObject | PersistentInstance | InstancedReference | ContainsInstancedReference | Config | EditConst | Deprecated | EditorOnly | AutoWeak | UObjectWrapper | TObjectPtr | Edit` — Flags that are propagated to properties inside set container
- L1308 _public* enumerator_ `InterfaceClearMask = ExportObject | InstancedReference | ContainsInstancedReference` — The flags that should never be set on interface properties
- L1313 _public* enumerator_ `DevelopmentAssets = EditorOnly` — All the properties that can be stripped for final release console builds
- L1318 _public* enumerator_ `ComputedFlags = IsPlainOldData | NoDestructor | ZeroConstructor | HasGetValueTypeHash` — All the properties that should never be loaded or saved
- L1323 _public* enumerator_ `AllFlags = UInt64.MaxValue` — Mask of all property flags

#### class `EpicGames.Core.EPropertyFlagsExtensions`  
`public static class EPropertyFlagsExtensions`  
_public; L1329-1405_
- desc: Helper extensions for EPropertyFlags
- L1331 _private field_ `private static readonly Lazy<List<string>> BitNames = new(() => { List<string> Out = []; FieldInfo[] Fields = typeof(EPropertyFlags).GetFields(); for (int Bit = 0; Bit < 64; ++Bit) { bool bFound = false; ulong Mask = (ulong)1 << Bit; foreach (FieldInfo F ...`
- L1364-1367 _public method_ `public static bool HasAnyFlags(this EPropertyFlags InFlags, EPropertyFlags TestFlags)`
- L1369-1372 _public method_ `public static bool HasAllFlags(this EPropertyFlags InFlags, EPropertyFlags TestFlags)`
- L1374-1377 _public method_ `public static bool HasExactFlags(this EPropertyFlags InFlags, EPropertyFlags TestFlags, EPropertyFlags MatchFlags)`
- L1379-1404 _public method_ `public static List<string> ToStringList(this EPropertyFlags InFlags, bool bIncludePrefix = true)`

#### enum `EpicGames.Core.EStructFlags`  
`public enum EStructFlags`  
_public; L1414-1539_
- attrs: `[Flags]`
- desc: Flags describing a struct This MUST be kept in sync with EStructFlags defined in Engine\Source\Runtime\CoreUObject\Public\UObject\Class.h
- L1416 _public* enumerator_ `NoFlags = 0x00000000`
- L1417 _public* enumerator_ `Native = 0x00000001`
- L1422 _public* enumerator_ `IdenticalNative = 0x00000002` — If set, this struct will be compared using native code
- L1424 _public* enumerator_ `HasInstancedReference = 0x00000004`
- L1426 _public* enumerator_ `NoExport = 0x00000008`
- L1431 _public* enumerator_ `Atomic = 0x00000010` — Indicates that this struct should always be serialized as a single unit
- L1436 _public* enumerator_ `Immutable = 0x00000020` — Indicates that this struct uses binary serialization; it is unsafe to add/remove members from this struct without incrementing the package version
- L1441 _public* enumerator_ `AddStructReferencedObjects = 0x00000040` — If set, native code needs to be run to find referenced objects
- L1446 _public* enumerator_ `RequiredAPI = 0x00000200` — Indicates that this struct should be exportable/importable at the DLL layer. Base structs must also be exportable for this to work.
- L1451 _public* enumerator_ `NetSerializeNative = 0x00000400` — If set, this struct will be serialized using the CPP net serializer
- L1456 _public* enumerator_ `SerializeNative = 0x00000800` — If set, this struct will be serialized using the CPP serializer
- L1461 _public* enumerator_ `CopyNative = 0x00001000` — If set, this struct will be copied using the CPP operator=
- L1466 _public* enumerator_ `IsPlainOldData = 0x00002000` — If set, this struct will be copied using memcpy
- L1471 _public* enumerator_ `NoDestructor = 0x00004000` — If set, this struct has no destructor and non will be called. IsPlainOldData implies NoDestructor
- L1476 _public* enumerator_ `ZeroConstructor = 0x00008000` — If set, this struct will not be constructed because it is assumed that memory is zero before construction.
- L1481 _public* enumerator_ `ExportTextItemNative = 0x00010000` — If set, native code will be used to export text
- L1486 _public* enumerator_ `ImportTextItemNative = 0x00020000` — If set, native code will be used to export text
- L1491 _public* enumerator_ `PostSerializeNative = 0x00040000` — If set, this struct will have PostSerialize called on it after CPP serializer or tagged property serialization is complete
- L1496 _public* enumerator_ `SerializeFromMismatchedTag = 0x00080000` — If set, this struct will have SerializeFromMismatchedTag called on it if a mismatched tag is encountered.
- L1501 _public* enumerator_ `NetDeltaSerializeNative = 0x00100000` — If set, this struct will be serialized using the CPP net delta serializer
- L1506 _public* enumerator_ `PostScriptConstruct = 0x00200000` — If set, this struct will be have PostScriptConstruct called on it after a temporary object is constructed in a running blueprint
- L1511 _public* enumerator_ `NetSharedSerialization = 0x00400000` — If set, this struct can share net serialization state across connections
- L1516 _public* enumerator_ `Trashed = 0x00800000` — If set, this struct has been cleaned and sanitized (trashed) and should not be used
- L1521 _public* enumerator_ `NewerVersionExists = 0x01000000` — If set, this structure has been replaced via reinstancing
- L1526 _public* enumerator_ `CanEditChange = 0x02000000` — If set, this struct will have CanEditChange on it in the editor to determine if a child property can be edited
- L1531 _public* enumerator_ `Inherit = HasInstancedReference | Atomic` — Struct flags that are automatically inherited
- L1536 _public* enumerator_ `ComputedFlags = NetDeltaSerializeNative | NetSerializeNative | SerializeNative | PostSerializeNative | CopyNative | IsPlainOldData | NoDestructor | ZeroConstructor | IdenticalNative | AddStructReferencedObjects | ExportTextItemNative | ImportTextItemNative | SerializeFromMismatchedTag | PostScriptConstruct | NetSharedSerialization` — Flags that are always computed, never loaded or done with code generation

#### class `EpicGames.Core.EStructFlagsExtensions`  
`public static class EStructFlagsExtensions`  
_public; L1544-1560_
- desc: Helper extensions for EStructFlags
- L1546-1549 _public method_ `public static bool HasAnyFlags(this EStructFlags InFlags, EStructFlags TestFlags)`
- L1551-1554 _public method_ `public static bool HasAllFlags(this EStructFlags InFlags, EStructFlags TestFlags)`
- L1556-1559 _public method_ `public static bool HasExactFlags(this EStructFlags InFlags, EStructFlags TestFlags, EStructFlags MatchFlags)`

#### enum `EpicGames.Core.EVerseClassFlags`  
`public enum EVerseClassFlags : uint`  
_public; L1568-1594_
- attrs: `[Flags]`
- inherits: `uint`
- desc: Extra flags for verse classes and structures Keep these flags in sync with VVMVerseClassFlags.h
- L1570 _public* enumerator_ `None = 0x00000000`
- L1571 _public* enumerator_ `NativeBound = 0x00000001`
- L1572 _public* enumerator_ `UniversallyAccessible = 0x00000002`
- L1573 _public* enumerator_ `Concrete = 0x00000004`
- L1574 _public* enumerator_ `Module = 0x00000008`
- L1575 _public* enumerator_ `UHTNative = 0x00000010`
- L1576 _public* enumerator_ `Tuple = 0x00000020`
- L1577 _public* enumerator_ `EpicInternal = 0x00000040`
- L1578 _public* enumerator_ `HasInstancedSemantics = 0x00000080`
- L1579 _public* enumerator_ `FinalSuper = 0x00000100`
- L1580 _public* enumerator_ `Castable = 0x00000200`
- L1581 _public* enumerator_ `EpicInternalConstructor = 0x00000400`
- L1582 _public* enumerator_ `Persistable = 0x00000800u`
- L1583 _public* enumerator_ `Parametric = 0x00001000u`
- L1584 _public* enumerator_ `PersonaConstructible = 0x00004000u`
- L1585 _public* enumerator_ `HasVar = 0x00008000u`
- L1586 _public* enumerator_ `InheritsFromBlueprint = 0x00010000u`
- L1587 _public* enumerator_ `HasTransientSubobjects = 0x00020000u`
- L1590 _public* enumerator_ `ErrInoperable = 0x40000000`
- L1591 _public* enumerator_ `ErrIncomplete = 0x80000000`
- L1593 _public* enumerator_ `Err = (ErrIncomplete | ErrInoperable)`

### `Source/Programs/Shared/EpicGames.Core/UserSecurityUtils.cs` (EpicGames.Core)


#### class `EpicGames.Core.UserSecurityUtils`  
`public static class UserSecurityUtils`  
_public; L11-35_
- desc: Provides utility methods for checking user security contexts and permissions
- L17-34 _public method_ `public static bool IsAdministrator()` — Checks if the current process is running with administrator privileges on Windows

### `Source/Programs/Shared/EpicGames.Core/Utf8String.cs` (EpicGames.Core)


#### struct `EpicGames.Core.Utf8String`  
`public readonly struct Utf8String : IEquatable<Utf8String>, IComparable<Utf8String>`  
_public; L12-364_
- inherits: `IEquatable<Utf8String>, IComparable<Utf8String>`
- desc: Represents a memory region which can be treated as a utf-8 string.
- L17 _public field_ `public static readonly Utf8String Empty = new()` — An empty string
- L22 _public property_ `public ReadOnlyMemory<byte> Memory { get; }` — The data represented by this string
- L27 _public property_ `public ReadOnlySpan<byte> Span => ...` — Returns read only span for this string
- L32 _public property_ `public bool IsEmpty => ...` — Determines if this string is empty
- L37 _public property_ `public int Length => ...` — Returns the length of this string
- L44 _public indexer_ `public byte this[int index]` — Allows indexing individual bytes of the data
- L50-53 _public ctor_ `public Utf8String(string text)` — Constructor
- L59-65 _public ctor_ `public Utf8String(ReadOnlySpan<char> text)` — Constructor
- L71-74 _public ctor_ `public Utf8String(ReadOnlyMemory<byte> memory)` — Constructor
- L82-85 _public ctor_ `public Utf8String(byte[] buffer, int offset, int length)` — Constructor
- L91-101 _public method_ `public Utf8String Clone()` — Duplicate this string
- L109-112 _public operator_ `public static bool operator ==(Utf8String a, Utf8String b)` — Tests two strings for equality
- L120-123 _public operator_ `public static bool operator !=(Utf8String a, Utf8String b)` — Tests two strings for inequality
- L126 _public method_ `public bool Equals(Utf8String other)` — (inheritdoc)
- L129 _public method_ `public int CompareTo(Utf8String other)` — (inheritdoc)
- L132 _public operator_ `public static bool operator <(Utf8String left, Utf8String right)` — (inheritdoc)
- L135 _public operator_ `public static bool operator <=(Utf8String left, Utf8String right)` — (inheritdoc)
- L138 _public operator_ `public static bool operator >(Utf8String left, Utf8String right)` — (inheritdoc)
- L141 _public operator_ `public static bool operator >=(Utf8String left, Utf8String right)` — (inheritdoc)
- L144 _public method_ `public bool Contains(Utf8String str)` — (inheritdoc)
- L147 _public method_ `public bool Contains(Utf8String str, Utf8StringComparer comparer)` — (inheritdoc)
- L150-153 _public method_ `public int IndexOf(byte character)` — (inheritdoc)
- L156-166 _public method_ `public int IndexOf(char character)` — (inheritdoc)
- L169 _public method_ `public int IndexOf(char character, int index)` — (inheritdoc)
- L172-184 _public method_ `public int IndexOf(char character, int index, int count)` — (inheritdoc)
- L187-190 _public method_ `public int IndexOf(Utf8String str)` — (inheritdoc)
- L193-203 _public method_ `public int IndexOf(Utf8String str, Utf8StringComparer comparer)` — (inheritdoc)
- L206-209 _public method_ `public int LastIndexOf(byte character)` — (inheritdoc)
- L212-222 _public method_ `public int LastIndexOf(char character)` — (inheritdoc)
- L229-232 _public method_ `public bool StartsWith(Utf8String other)` — Tests if this string starts with another string
- L240-243 _public method_ `public bool StartsWith(Utf8String other, Utf8StringComparer comparer)` — Tests if this string ends with another string
- L250-253 _public method_ `public bool EndsWith(Utf8String other)` — Tests if this string ends with another string
- L261-264 _public method_ `public bool EndsWith(Utf8String other, Utf8StringComparer comparer)` — Tests if this string ends with another string
- L267 _public method_ `public Utf8String Slice(int start)` — (inheritdoc)
- L270 _public method_ `public Utf8String Slice(int start, int count)` — (inheritdoc)
- L273-276 _public method_ `public Utf8String Substring(int start)` — (inheritdoc)
- L279-282 _public method_ `public Utf8String Substring(int start, int count)` — (inheritdoc)
- L289-293 _public method_ `public override bool Equals(object? obj)` — Tests if this string is equal to the other object
- L299 _public method_ `public override int GetHashCode()` — Returns the hash code of this string
- L305-308 _public method_ `public override string ToString()` — Gets the string represented by this data
- L315-334 _public method_ `public static uint ParseUnsignedInt(Utf8String text)` — Parse a string as an unsigned integer
- L342-357 _public operator_ `public static Utf8String operator +(Utf8String a, Utf8String b)` — Appends two strings
- L363 _public operator_ `public static implicit operator ReadOnlySpan<byte>(Utf8String str)` — Implict conversion to a span of bytes

#### class `EpicGames.Core.Utf8StringComparer`  
`public abstract class Utf8StringComparer : IEqualityComparer<Utf8String>, IComparer<Utf8String>`  
_public; L369-492_
- inherits: `IEqualityComparer<Utf8String>, IComparer<Utf8String>`
- desc: Comparison classes for utf8 strings
- L468 _public property_ `public static Utf8StringComparer Ordinal { get; }` — Static instance of the ordinal utf8 ordinal comparer
- L473 _public property_ `public static Utf8StringComparer OrdinalIgnoreCase { get; }` — Static instance of the case-insensitive utf8 ordinal string comparer
- L476 _public method_ `public bool Equals(Utf8String strA, Utf8String strB)` — (inheritdoc)
- L479 _public method_ `public abstract bool Equals(ReadOnlySpan<byte> strA, ReadOnlySpan<byte> strB)` — (inheritdoc)
- L482 _public method_ `public int GetHashCode(Utf8String str)` — (inheritdoc)
- L485 _public method_ `public abstract int GetHashCode(ReadOnlySpan<byte> str)` — (inheritdoc)
- L488 _public method_ `public int Compare(Utf8String strA, Utf8String strB)` — (inheritdoc)
- L491 _public method_ `public abstract int Compare(ReadOnlySpan<byte> strA, ReadOnlySpan<byte> strB)` — (inheritdoc)

#### class `EpicGames.Core.Utf8StringComparer.OrdinalComparer`  
`sealed class OrdinalComparer : Utf8StringComparer`  
_private*; L374-398_
- inherits: `Utf8StringComparer`
- desc: Ordinal comparer for utf8 strings
- L377-380 _public method_ `public override bool Equals(ReadOnlySpan<byte> strA, ReadOnlySpan<byte> strB)` — (inheritdoc)
- L383-391 _public method_ `public override int GetHashCode(ReadOnlySpan<byte> str)` — (inheritdoc)
- L394-397 _public method_ `public override int Compare(ReadOnlySpan<byte> strA, ReadOnlySpan<byte> strB)` — (inheritdoc)

#### class `EpicGames.Core.Utf8StringComparer.OrdinalIgnoreCaseComparer`  
`sealed class OrdinalIgnoreCaseComparer : Utf8StringComparer`  
_private*; L403-463_
- inherits: `Utf8StringComparer`
- desc: Comparison between ReadOnlyUtf8String objects that ignores case for ASCII characters
- L406-422 _public method_ `public override bool Equals(ReadOnlySpan<byte> strA, ReadOnlySpan<byte> strB)` — (inheritdoc)
- L425-433 _public method_ `public override int GetHashCode(ReadOnlySpan<byte> str)` — (inheritdoc)
- L436-452 _public method_ `public override int Compare(ReadOnlySpan<byte> spanA, ReadOnlySpan<byte> spanB)` — (inheritdoc)
- L459-462 _private* method_ `static byte ToUpper(byte character)` — Convert a character to uppercase

#### class `EpicGames.Core.Utf8StringExtensions`  
`public static class Utf8StringExtensions`  
_public; L497-572_
- desc: Extension methods for ReadOnlyUtf8String objects
- L503-506 _public method_ `public static Utf8String ReadUtf8String(this IMemoryReader reader)` — Reads a null-terminated utf8 string from the buffer, without copying it
- L512-515 _public method_ `public static Utf8String ReadUtf8StringWithoutCopy(this IMemoryReader reader)` — Reads a null-terminated utf8 string from the buffer, without copying it
- L522-525 _public method_ `public static void WriteUtf8String(this IMemoryWriter writer, Utf8String str)` — Reads a null-terminated utf8 string from the buffer, without copying it
- L531-548 _public method_ `public static Utf8String ReadNullTerminatedUtf8String(this IMemoryReader reader)` — Reads a null-terminated utf8 string from the buffer, without copying it
- L555-561 _public method_ `public static void WriteNullTerminatedUtf8String(this IMemoryWriter writer, Utf8String str)` — Writes a null-terminated utf8 string to the buffer
- L568-571 _public method_ `public static int GetNullTerminatedSize(this Utf8String str)` — Determines the size of a serialized utf-8 string

### `Source/Programs/Shared/EpicGames.Core/Utf8StringBuilder.cs` (EpicGames.Core)


#### class `EpicGames.Core.Utf8StringBuilder`  
`public class Utf8StringBuilder`  
_public; L11-180_
- desc: Represents a memory region which can be treated as a utf-8 string.
- L13 _private* field_ `readonly ArrayMemoryWriter _writer`
- L18-31 _public property_ `public int Length { get; set; }` — Returns the length of this string
- L36 _public property_ `public Span<byte> WrittenSpan => ...` — Accessor for the written span
- L41 _public property_ `public Memory<byte> WrittenMemory => ...` — Accessor for the written memory
- L46 _public property_ `public Utf8String WrittenString => ...` — Accessor for the written data
- L51-54 _public ctor_ `public Utf8StringBuilder() : this(256)` — Constructor
- L59-62 _public ctor_ `public Utf8StringBuilder(int initialSize) : this(new ArrayMemoryWriter(initialSize))` — Constructor
- L67-70 _public ctor_ `public Utf8StringBuilder(ArrayMemoryWriter writer)` — Constructor
- L76-79 _public method_ `public void Append(byte ch)` — Append a character to the end of this builder
- L85-95 _public method_ `public void Append(char ch)` — Append a character to the end of this builder
- L101-104 _public method_ `public void Append(Utf8String text)` — Appends a string to the end of this builder
- L110 _public method_ `public void Append(int value)` — Appends an integer to the end of this builder
- L116 _public method_ `public void Append(uint value)` — Appends an integer to the end of this builder
- L122-133 _public method_ `public void Append(long value)` — Appends an unsigned long to the end of this builder
- L139-157 _public method_ `public void Append(ulong value)` — Appends an unsigned long to the end of this builder
- L163-167 _public method_ `public void Append(ReadOnlySpan<char> text)` — Appends a string to the end of this builder
- L173-176 _public method_ `public Utf8String ToUtf8String()` — Converts the written memory to a utf8 string
- L179 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/VarInt.cs` (EpicGames.Core)


#### class `EpicGames.Core.VarInt`  
`public static class VarInt`  
_public; L11-248_
- desc: Methods for reading VarUInt values
- L19 _public method_ `public static ulong Read(ReadOnlySpan<byte> buffer)` — attrs: `[Obsolete("Call ReadSigned or ReadUnsigned instead")]` — Read a variable-length unsigned integer.
- L28 _public method_ `public static ulong Read(ReadOnlySpan<byte> buffer, out int bytesRead)` — attrs: `[Obsolete("Call ReadSigned or ReadUnsigned instead")]` — Read a variable-length unsigned integer.
- L35 _public method_ `public static long ReadSigned(ReadOnlySpan<byte> buffer)` — Read a variable-length signed integer.
- L43-47 _public method_ `public static long ReadSigned(ReadOnlySpan<byte> buffer, out int bytesRead)` — Read a variable-length signed integer.
- L54 _public method_ `public static ulong ReadUnsigned(ReadOnlySpan<byte> buffer)` — Read a variable-length unsigned integer.
- L62-66 _public method_ `public static ulong ReadUnsigned(ReadOnlySpan<byte> buffer, out int bytesRead)` — Read a variable-length unsigned integer.
- L74-83 _internal method_ `internal static ulong ReadUnsignedKnownSize(ReadOnlySpan<byte> buffer, int numBytes)` — Read a variable-length unsigned integer.
- L90-95 _public method_ `public static int Measure(ReadOnlySpan<byte> buffer)` — Measure the length in bytes (1-9) of an encoded variable-length integer.
- L102-106 _public method_ `public static int Measure(byte b)` — Measure the length in bytes (1-9) of an encoded variable-length integer.
- L114 _public method_ `public static int Measure(uint value)` — attrs: `[Obsolete("Use MeasureSigned or MeasureUnsigned instead")]` — Measure the number of bytes required to encode the input.
- L122 _public method_ `public static int Measure(ulong value)` — attrs: `[Obsolete("Use MeasureSigned or MeasureUnsigned instead")]` — Measure the number of bytes required to encode the input.
- L129-132 _public method_ `public static int MeasureSigned(long value)` — Measure the number of bytes (1-9) required to encode the input.
- L139-142 _public method_ `public static int MeasureUnsigned(int value)` — Measure the number of bytes (1-5) required to encode the 32-bit input.
- L149-152 _public method_ `public static int MeasureUnsigned(uint value)` — Measure the number of bytes (1-5) required to encode the 32-bit input.
- L159-162 _public method_ `public static int MeasureUnsigned(ulong value)` — Measure the number of bytes (1-9) required to encode the 64-bit input.
- L171 _public method_ `public static int Write(Span<byte> buffer, long value)` — attrs: `[Obsolete("Use WriteUnsigned or WriteSigned instead")]` — Write a variable-length unsigned integer.
- L180 _public method_ `public static int Write(Span<byte> buffer, ulong value)` — attrs: `[Obsolete("Use WriteUnsigned or WriteSigned instead")]` — Write a variable-length unsigned integer.
- L188-192 _public method_ `public static int WriteSigned(Span<byte> buffer, long value)` — Write a variable-length unsigned integer.
- L200 _public method_ `public static int WriteUnsigned(Span<byte> buffer, int value)` — Write a variable-length unsigned integer.
- L208 _public method_ `public static int WriteUnsigned(Span<byte> buffer, long value)` — Write a variable-length unsigned integer.
- L216-227 _public method_ `public static int WriteUnsigned(Span<byte> buffer, ulong value)` — Write a variable-length unsigned integer.
- L234-237 _public method_ `public static long DecodeSigned(ulong value)` — Decode a signed VarInt value from an unsigned value
- L244-247 _public method_ `public static ulong EncodeSigned(long value)` — Encode a signed VarInt value into an unsigned value

#### class `EpicGames.Core.VarIntExtensions`  
`public static class VarIntExtensions`  
_public; L253-317_
- desc: Extension methods for writing VarInt values
- L260-264 _public method_ `public static long ReadSignedVarInt(this IMemoryReader reader)` — Read an unsigned VarInt from the given reader
- L271-277 _public method_ `public static ulong ReadUnsignedVarInt(this IMemoryReader reader)` — Read an unsigned VarInt from the given reader
- L284-287 _public method_ `public static void WriteSignedVarInt(this IMemoryWriter writer, int value)` — Writes a signed VarInt to a byte array
- L294-297 _public method_ `public static void WriteSignedVarInt(this IMemoryWriter writer, long value)` — Writes a signed VarInt to a byte array
- L304 _public method_ `public static void WriteUnsignedVarInt(this IMemoryWriter writer, int value)` — Writes a unsigned VarInt to a byte array
- L311-316 _public method_ `public static void WriteUnsignedVarInt(this IMemoryWriter writer, ulong value)` — Writes a unsigned VarInt to a byte array

### `Source/Programs/Shared/EpicGames.Core/VersionNumber.cs` (EpicGames.Core)


#### class `EpicGames.Core.VersionNumber`  
`public class VersionNumber : IComparable<VersionNumber>`  
_public; L17-247_
- attrs: `[Serializable] [JsonConverter(typeof(VersionNumberJsonConverter))]`
- inherits: `IComparable<VersionNumber>`
- desc: Stores a numeric version consisting of any number of components.
- L22 _private* field_ `static readonly char[] s_delimiters = ['.', ',']` — Set of delimiters for version numbers
- L27 _public property_ `public IReadOnlyList<int> Components => ...` — The individual version components
- L29 _private* field_ `readonly int[] _components`
- L35-42 _public ctor_ `public VersionNumber(params int[] components)` — Constructor
- L49-52 _public method_ `public int GetComponent(int idx)` — Returns the component at the given index
- L59-63 _public method_ `public override bool Equals(object? obj)` — Tests two objects for equality. VersionNumber behaves like a value type.
- L69-77 _public method_ `public override int GetHashCode()` — Returns a hash of the version number.
- L85-88 _public operator_ `public static bool operator ==(VersionNumber? lhs, VersionNumber? rhs)` — Compares whether two versions are equal.
- L96-99 _public operator_ `public static bool operator !=(VersionNumber? lhs, VersionNumber? rhs)` — Compares whether two versions are not equal.
- L107-110 _public operator_ `public static bool operator <(VersionNumber lhs, VersionNumber rhs)` — Compares whether one version is less than another.
- L118-121 _public operator_ `public static bool operator <=(VersionNumber lhs, VersionNumber rhs)` — Compares whether one version is less or equal to another.
- L129-132 _public operator_ `public static bool operator >(VersionNumber lhs, VersionNumber rhs)` — Compares whether one version is greater than another.
- L140-143 _public operator_ `public static bool operator >=(VersionNumber lhs, VersionNumber rhs)` — Compares whether one version is greater or equal to another.
- L150-153 _public method_ `public int CompareTo(VersionNumber? other)` — Comparison function for IComparable
- L161-188 _public method_ `public static int Compare(VersionNumber lhs, VersionNumber rhs)` — Compares two version numbers and returns an integer indicating their order
- L195-203 _public method_ `public static VersionNumber Parse(string text)` — Parses the version number from a string
- L211-227 _public method_ `public static bool TryParse(string text, [NotNullWhen(true)] out VersionNumber? outNumber)` — Parses the version number from a string
- L233-246 _public method_ `public override string ToString()` — Returns a string version number, eg. 1.4

#### class `EpicGames.Core.VersionNumberJsonConverter`  
`internal class VersionNumberJsonConverter : JsonConverter<VersionNumber>`  
_internal; L249-275_
- inherits: `JsonConverter<VersionNumber>`
- L251-255 _public method_ `public override VersionNumber? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L257-264 _public method_ `public override VersionNumber ReadAsPropertyName(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L266-269 _public method_ `public override void Write(Utf8JsonWriter writer, VersionNumber value, JsonSerializerOptions options)`
- L271-274 _public method_ `public override void WriteAsPropertyName(Utf8JsonWriter writer, [DisallowNull] VersionNumber value, JsonSerializerOptions options)`

### `Source/Programs/Shared/EpicGames.Core/VersionNumberRange.cs` (EpicGames.Core)


#### class `EpicGames.Core.VersionNumberRange`  
`public class VersionNumberRange`  
_public; L10-59_
- desc: Range of version numbers
- L15 _public property_ `public VersionNumber Min { get; }` — Minimum version number
- L20 _public property_ `public VersionNumber Max { get; }` — Maximum version number
- L27-31 _public ctor_ `public VersionNumberRange(VersionNumber min, VersionNumber max)` — Constructor
- L38-41 _public method_ `public bool Contains(VersionNumber version)` — Tests whether this range contains the given version
- L49-52 _public method_ `public static VersionNumberRange Parse(string minText, string maxText)` — Parse a version range from two strings
- L55-58 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Core/Win32ExceptionWithCode.cs` (EpicGames.Core)


#### class `EpicGames.Core.Win32ExceptionWithCode`  
`class Win32ExceptionWithCode : Win32Exception`  
_internal*; L11-45_
- inherits: `Win32Exception`
- desc: Wrapper for Win32Exception which includes the error code in the exception message
- L17-20 _public ctor_ `public Win32ExceptionWithCode(int code) : base(code)` — Constructor
- L26-29 _public ctor_ `public Win32ExceptionWithCode(string message) : base(message)` — Constructor
- L36-39 _public ctor_ `public Win32ExceptionWithCode(int code, string message) : base(code, message)` — Constructor
- L44 _public property_ `public override string Message => ...` — Returns the exception message. Overriden to include the error code in the message.

### `Source/Programs/Shared/EpicGames.Core/XmlDocReader.cs` (EpicGames.Core)


#### class `EpicGames.Core.XmlDocReader`  
`public class XmlDocReader`  
_public; L16-141_
- desc: Cache for XML documentation
- L18 _private* field_ `readonly ConcurrentDictionary<Assembly, XmlDocument?> _cachedDocumentation = ...`
- L18 _private* field_ `readonly ConcurrentDictionary< _cachedDocumentation = new()`
- L23-26 _public method_ `public void Add(Assembly assembly, XmlDocument? xmlDoc)` — Adds a parsed file as the documentation for a particular assembly
- L31-34 _public method_ `public string? GetDescription(Type type)` — Gets a property description from Xml documentation file
- L39-42 _public method_ `public string? GetDescription(PropertyInfo propertyInfo)` — Gets a property description from Xml documentation file
- L47-50 _public method_ `public string? GetDescription(Type type, string field)` — Gets a property description from Xml documentation file
- L59-101 _private* method_ `string? GetSummaryFromXmlDoc(Type type, string qualifier, string? member)` — Gets a description from Xml documentation file
- L103-114 _private* method_ `static IEnumerable<Type> FindBaseTypes(Type type)`
- L116-140 _private* method_ `bool TryReadXmlDoc(Assembly assembly, [NotNullWhen(true)] out XmlDocument? xmlDoc)`

### `Source/Programs/Shared/EpicGames.Core/ZipArchiveExtensions.cs` (EpicGames.Core)


#### class `EpicGames.Core.ZipArchiveExtensions`  
`public static class ZipArchiveExtensions`  
_public; L14-81_
- desc: Additional functionality around System.IO.Compression.ZipArchive to support non-Windows filesystems
- L24-44 _public method_ `public static ZipArchiveEntry CreateEntryFromFile_CrossPlatform(this ZipArchive destination, string sourceFileName, string entryName, CompressionLevel compressionLevel)` — Create a zip archive entry, preserving platform mode bits
- L52-80 _public method_ `public static void ExtractToFile_CrossPlatform(this ZipArchiveEntry entry, string targetFileName, bool overwrite)` — Extract a zip archive entry, preserving platform mode bits
