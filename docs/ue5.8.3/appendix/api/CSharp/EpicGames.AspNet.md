# CSharp / EpicGames.AspNet

- project root: `Source/Programs/Shared/EpicGames.AspNet`
- files: 4; symbols: 64
- symbol kinds: class=13, const=4, ctor=6, field=10, interface=1, method=27, property=2, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.AspNet/CbConvertersAspnet.cs` (EpicGames.AspNet)


#### class `EpicGames.AspNet.CbConvertersAspNet`  
`public static class CbConvertersAspNet`  
_public; L14-24_
- desc: Provides methods for registering ASP.NET-specific compact binary converters
- L19-23 _public method_ `public static void AddAspnetConverters()` — Registers ASP.NET-specific converters for ProblemDetails and ValidationProblemDetails types

#### class `EpicGames.AspNet.CbProblemDetailsConverter`  
`class CbProblemDetailsConverter : CbConverter<ProblemDetails>`  
_internal*; L29-97_
- inherits: `CbConverter<ProblemDetails>`
- desc: Converter for asp.net problem details type
- L32-48 _public method_ `public override ProblemDetails Read(CbField field)` — (inheritdoc)
- L51-54 _public method_ `public override void Write(CbWriter writer, ProblemDetails problemDetails)` — (inheritdoc)
- L57-60 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, ProblemDetails problemDetails)` — (inheritdoc)
- L67-96 _private method_ `private static CbObject ToCbObject(ProblemDetails problemDetails)` — Converts a ProblemDetails instance to a CbObject representation

#### class `EpicGames.AspNet.CbValidationProblemDetailsConverter`  
`class CbValidationProblemDetailsConverter : CbConverter<ValidationProblemDetails>`  
_internal*; L102-204_
- inherits: `CbConverter<ValidationProblemDetails>`
- desc: Converter for asp.net validation problem details type
- L105-136 _public method_ `public override ValidationProblemDetails Read(CbField field)` — (inheritdoc)
- L139-142 _public method_ `public override void Write(CbWriter writer, ValidationProblemDetails validationProblemDetails)` — (inheritdoc)
- L145-148 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, ValidationProblemDetails validationProblemDetails)` — (inheritdoc)
- L155-203 _private method_ `private static CbObject ToCbObject(ValidationProblemDetails validationProblemDetails)` — Converts a ValidationProblemDetails instance to a CbObject representation

### `Source/Programs/Shared/EpicGames.AspNet/ClientSendSlowException.cs` (EpicGames.AspNet)


#### class `EpicGames.AspNet.ClientSendSlowExceptionUtil`  
`public static class ClientSendSlowExceptionUtil`  
_public; L11-38_
- desc: Utility methods for detecting and handling slow client send exceptions
- L18-37 _public method_ `public static bool MaybeThrowSlowSendException(BadHttpRequestException e)` — Checks if a BadHttpRequestException indicates a slow client send and throws ClientSendSlowException if so

#### class `EpicGames.AspNet.ClientSendSlowException`  
`public class ClientSendSlowException : Exception`  
_public; L43-52_
- inherits: `Exception`
- desc: Exception thrown when a client is sending data too slowly
- L49-51 _public ctor_ `public ClientSendSlowException(Exception? innerException) : base("Client was sending data to slowly", innerException)` — Initializes a new instance of the ClientSendSlowException class

### `Source/Programs/Shared/EpicGames.AspNet/CompactBinaryFormatter.cs` (EpicGames.AspNet)


#### class `EpicGames.AspNet.CustomMediaTypeNames`  
`public static partial class CustomMediaTypeNames`  
_public; L20-41_
- desc: Global constants
- L25 _public const_ `public const string UnrealCompactBinary = "application/x-ue-cb"` — Media type for compact binary
- L30 _public const_ `public const string UnrealCompressedBuffer = "application/x-ue-comp"` — Media type for compressed buffers
- L35 _public const_ `public const string JupiterInlinedPayload = "application/x-jupiter-inline"` — Media type for Jupiter inline payload
- L40 _public const_ `public const string UnrealCompactBinaryPackage = "application/x-ue-cbpkg"` — Media type for compact binary packages

#### class `EpicGames.AspNet.CbInputFormatter`  
`public class CbInputFormatter : InputFormatter`  
_public; L46-121_
- inherits: `InputFormatter`
- desc: Converter to allow reading compact binary objects as request bodies
- L51-54 _public ctor_ `public CbInputFormatter()` — Constructor
- L57-60 _protected method_ `protected override bool CanReadType(Type type)` — (inheritdoc)
- L63-99 _public method_ `public override async Task<InputFormatterResult> ReadRequestBodyAsync(InputFormatterContext context)` — (inheritdoc)
- L107-120 _private* method_ `static string FormatHexDump(byte[] data, int maxLength)` — Formats a byte array as a hexadecimal dump with line breaks every 16 bytes

#### class `EpicGames.AspNet.CbOutputFormatter`  
`public class CbOutputFormatter : OutputFormatter`  
_public; L126-156_
- inherits: `OutputFormatter`
- desc: Converter to allow writing compact binary objects as responses
- L131-134 _public ctor_ `public CbOutputFormatter()` — Constructor
- L137-140 _protected method_ `protected override bool CanWriteType(Type? type)` — (inheritdoc)
- L143-155 _public method_ `public override async Task WriteResponseBodyAsync(OutputFormatterWriteContext context)` — (inheritdoc)

#### class `EpicGames.AspNet.CbPreferredOutputFormatter`  
`public class CbPreferredOutputFormatter : CbOutputFormatter`  
_public; L162-169_
- inherits: `CbOutputFormatter`
- desc: Special version of CbOutputFormatter which returns native CbObject encoded data. Can be inserted at a high priority in the output formatter list to prevent transcoding to json.
- L165-168 _protected method_ `protected override bool CanWriteType(Type? type)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.AspNet/ServerTimings.cs` (EpicGames.AspNet)


#### struct `EpicGames.AspNet.ServerTimingMetric`  
`public struct ServerTimingMetric`  
_public; L18-84_
- desc: Represents a server timing metric for performance monitoring
- L23 _private field_ `private readonly string _metricName` — The name of the metric
- L28 _private field_ `private readonly double? _duration` — The duration in milliseconds
- L33 _private field_ `private readonly string? _description` — Optional description of the metric
- L38 _private field_ `private string? _serverTimingMetric` — Cached string representation of the server timing metric
- L46-53 _public ctor_ `public ServerTimingMetric(string metricName, double? duration, string? description)` — Initializes a new instance of the ServerTimingMetric struct
- L59-83 _public method_ `public override string ToString()` — Converts the metric to its string representation

#### interface `EpicGames.AspNet.IServerTiming`  
`public interface IServerTiming`  
_public; L89-111_
- desc: Interface for managing server timing metrics
- L97 _public method_ `public void AddServerTimingMetric(string metricName, double? duration, string? description)` — Adds a server timing metric
- L105 _public method_ `public ServerTimingMetricScoped CreateServerTimingMetricScope(string metricName, string? description)` — Creates a scoped metric that measures duration automatically
- L110 _public property_ `public IReadOnlyCollection<ServerTimingMetric> Metrics { get; }` — Gets the collection of all recorded metrics

#### class `EpicGames.AspNet.ServerTimingMetricScoped`  
`public sealed class ServerTimingMetricScoped : IDisposable`  
_public; L116-160_
- inherits: `IDisposable`
- desc: Scoped server timing metric that automatically records duration when disposed
- L121 _private field_ `private readonly IServerTiming _timingManager` — The timing manager that will receive the metric when disposed
- L126 _private field_ `private readonly string _metricName` — The name of the metric
- L131 _private field_ `private readonly string? _description` — Optional description of the metric
- L136 _private field_ `private readonly DateTime _startTime` — The start time of the metric measurement
- L144-150 _internal ctor_ `internal ServerTimingMetricScoped(IServerTiming timingManager, string metricName, string? description)` — Initializes a new instance of the ServerTimingMetricScoped class
- L155-159 _public method_ `public void Dispose()` — Disposes the scoped metric and records the duration

#### class `EpicGames.AspNet.ServerTiming`  
`public class ServerTiming : IServerTiming`  
_public; L165-186_
- inherits: `IServerTiming`
- desc: Default implementation of server timing metrics
- L170 _private field_ `private readonly ConcurrentBag<ServerTimingMetric> _metrics = []` — Thread-safe collection of recorded metrics
- L173-176 _public method_ `public void AddServerTimingMetric(string metricName, double? duration, string? description)` — (inheritdoc)
- L179-182 _public method_ `public ServerTimingMetricScoped CreateServerTimingMetricScope(string metricName, string? description)` — (inheritdoc)
- L185 _public property_ `public IReadOnlyCollection<ServerTimingMetric> Metrics => ...` — (inheritdoc)

#### class `EpicGames.AspNet.ServerTimingMiddleware`  
`public class ServerTimingMiddleware`  
_public; L191-275_
- desc: Middleware for adding server timing headers to HTTP responses
- L196 _private field_ `private readonly RequestDelegate _next` — The next request delegate in the middleware pipeline
- L202-205 _public ctor_ `public ServerTimingMiddleware(RequestDelegate next)` — Initializes a new instance of the ServerTimingMiddleware class
- L212-223 _public method_ `public async Task InvokeAsync(HttpContext context)` — Invokes the middleware to add server timing headers
- L230-233 _public method_ `public static bool AllowsTrailers(HttpRequest request)` — Checks if the request supports trailer headers
- L241-252 _private method_ `private async Task HandleServerTimingAsTrailerHeaderAsync(HttpContext context, IServerTiming serverTiming)` — Handles server timing by adding metrics as HTTP trailer headers
- L260-274 _private method_ `private Task HandleServerTimingAsResponseHeadersAsync(HttpContext context, IServerTiming serverTiming)` — Handles server timing by adding metrics as HTTP response headers

#### class `EpicGames.AspNet.ServerTimingServiceCollectionExtensions`  
`public static class ServerTimingServiceCollectionExtensions`  
_public; L280-293_
- desc: Extension methods for adding server timing services
- L287-292 _public method_ `public static IServiceCollection AddServerTiming(this IServiceCollection services)` — Adds server timing services to the service collection
