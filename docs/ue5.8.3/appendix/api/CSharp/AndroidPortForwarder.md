# CSharp / AndroidPortForwarder

- project root: `Source/Developer/Android/AndroidZenServerPlugin/AndroidPortForwarder`
- files: 5; symbols: 41
- symbol kinds: class=6, ctor=2, delegate=1, enum=1, enumerator=2, field=11, method=18
- access marked `*` is implicit (not written in source)

### `Source/Developer/Android/AndroidZenServerPlugin/AndroidPortForwarder/AndroidPortForwarder.cs` (AndroidPortForwarder)


#### class `AndroidZenServerPlugin.AndroidPortForwarder`  
`public sealed class AndroidPortForwarder : IDisposable`  
_public; L5-51_
- inherits: `IDisposable`
- L7 _private field_ `private CancellationTokenSource? TokenSource`
- L8 _private field_ `private AndroidPortForwarderAsync? ForwarderAsync`
- L9 _private field_ `private Task? StartMonitorTask`
- L11-23 _public method_ `public void StartMonitor(string ADBPath, uint? ADBServerPortOpt, uint ZenServerPort)`
- L25-50 _public method_ `public void Dispose()`

### `Source/Developer/Android/AndroidZenServerPlugin/AndroidPortForwarder/AndroidPortForwarderAsync.cs` (AndroidPortForwarder)


#### class `AndroidZenServerPlugin.AndroidPortForwarderAsync`  
`public sealed class AndroidPortForwarderAsync : IDisposable`  
_public; L11-208_
- inherits: `IDisposable`
- L13 _private field_ `private AdbClient? Client`
- L14 _private field_ `private DeviceMonitor? DeviceMonitor`
- L16-68 _public method_ `public async Task StartMonitorAsync(string ADBPath, uint? ADBServerPortOpt, uint ZenServerPort, CancellationToken CancellationToken)`
- L70-85 _public method_ `public void Dispose()`
- L87-107 _private method_ `private static async Task ForwardPortsToDeviceAsync(IAdbClient Client, DeviceData Device, uint Port, CancellationToken CancellationToken)`
- L109-134 _private method_ `private static async Task<bool> DoesDeviceNeedsZenStreamingAsync(IAdbClient Client, DeviceData Device, CancellationToken CancellationToken)`

#### class `AndroidZenServerPlugin.AndroidPortForwarderAsync.DetachedAdbCommandLineClient`  
`internal class DetachedAdbCommandLineClient(string AdbPath) : AdbCommandLineClient(AdbPath)`  
_internal; L140-207_
- L142-147 _private method_ `private bool ShouldRunAsDetached(string Filename, string Command, ICollection<string>? ErrorOutput, ICollection<string>? StandardOutput)`
- L149-172 _protected method_ `protected override int RunProcess(string Filename, string Command, ICollection<string>? ErrorOutput, ICollection<string>? StandardOutput, int Timeout)`
- L174-206 _protected method_ `protected override async Task<int> RunProcessAsync(string Filename, string Command, ICollection<string>? ErrorOutput, ICollection<string>? StandardOutput, CancellationToken CancellationToken = default)`

### `Source/Developer/Android/AndroidZenServerPlugin/AndroidPortForwarder/AndroidPortForwarderCLI.cs` (AndroidPortForwarder)
_(no declarations)_


### `Source/Developer/Android/AndroidZenServerPlugin/AndroidPortForwarder/ConsoleRedirector.cs` (AndroidPortForwarder)


#### class `AndroidZenServerPlugin.ConsoleRedirector`  
`internal sealed class ConsoleRedirector : IDisposable`  
_internal; L6-97_
- inherits: `IDisposable`
- L14 _public delegate_ `public delegate void OutputDelegate(LogLevel Level, string Line)`
- L16 _private field_ `private TextWriter OriginalOut`
- L17 _private field_ `private TextWriter OriginalError`
- L19-28 _public ctor_ `public ConsoleRedirector(OutputDelegate Delegate)`
- L30-36 _public method_ `public void Dispose()`
- L38-42 _private method_ `private void OnCurrentDomainOnUnhandledException(object _, UnhandledExceptionEventArgs args)`

#### enum `AndroidZenServerPlugin.ConsoleRedirector.LogLevel`  
`public enum LogLevel`  
_public; L8-12_
- L10 _public* enumerator_ `Info`
- L11 _public* enumerator_ `Error`

#### class `AndroidZenServerPlugin.ConsoleRedirector.DelegateWriter`  
`private sealed class DelegateWriter : StringWriter`  
_private; L44-96_
- inherits: `StringWriter`
- L46 _private field_ `private readonly LogLevel LogLevel`
- L47 _private field_ `private readonly OutputDelegate Delegate`
- L49-53 _public ctor_ `public DelegateWriter(OutputDelegate InDelegate, LogLevel InLogLevel)`
- L55-65 _public method_ `public override void Flush()`
- L67-71 _private method_ `private void FlushLine()`
- L73-83 _public method_ `public override void Write(char[] buffer, int index, int count)`
- L85-95 _public method_ `public override void Write(string? value)`

### `Source/Developer/Android/AndroidZenServerPlugin/AndroidPortForwarder/ZenServerAdapter.cs` (AndroidPortForwarder)


#### class `AndroidZenServerPlugin.ZenServerAdapter`  
`public static class ZenServerAdapter`  
_public; L7-57_
- L9 _private field_ `private static ConsoleRedirector? ConsoleRedirector`
- L10 _private field_ `private static AndroidPortForwarder? AndroidPortForwarder`
- L13-36 _private method_ `private static unsafe void StartAndroidPortForwarder(delegate*<void*, int, char*, void> LogCallback, void* UsrPtr, IntPtr ADBPathPtr, uint* ADBServerPortOptPtr, uint ZenServerPort)` — attrs: `[UnmanagedCallersOnly(EntryPoint = "StartAndroidPortForwarder")]`
- L39-46 _private method_ `private static void StopAndroidPortForwarder()` — attrs: `[UnmanagedCallersOnly(EntryPoint = "StopAndroidPortForwarder")]`
- L48-56 _private method_ `private static int LogLevelToInt(ConsoleRedirector.LogLevel Level)`
