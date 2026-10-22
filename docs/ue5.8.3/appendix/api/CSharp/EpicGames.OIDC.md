# CSharp / EpicGames.OIDC

- project root: `Source/Programs/Shared/EpicGames.OIDC`
- files: 15; symbols: 294
- symbol kinds: class=34, const=6, ctor=19, enum=3, enumerator=11, event=2, field=47, interface=8, method=104, property=55, record=3, struct=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.OIDC/FakeOidcTokenManager.cs` (EpicGames.OIDC)


#### class `EpicGames.OIDC.FakeOidcTokenManager`  
`public class FakeOidcTokenManager : IOidcTokenManager`  
_public; L15-140_
- inherits: `IOidcTokenManager`
- desc: A fake implementation of OidcTokenManager for testing Assumes just a single provider.
- L17 _private const_ `private const string AccessTokenPrefix = "fakeAccessToken"`
- L22 _public property_ `public string? RefreshToken { get; set; }` — Refresh token in use
- L27 _public property_ `public string? AccessToken { get; set; }` — Latest access token
- L32 _public property_ `public TimeSpan AccessTokenTtl { get; set; }` — Time to live for newly minted access token
- L37 _public property_ `public DateTimeOffset AccessTokenExpiry { get; set; }` — Expiry time for access token
- L39 _private field_ `private int _refreshCounter = 1`
- L40 _private field_ `private int _accessCounter = 1`
- L41 _private field_ `private readonly Func<DateTimeOffset> _utcNow`
- L46-49 _public ctor_ `public FakeOidcTokenManager(Func<DateTimeOffset> utcNow)` — Constructor
- L52-57 _public method_ `public Task<IOidcTokenInfo> LoginAsync(string providerIdentifier, CancellationToken cancellationToken = default)` — (inheritdoc)
- L60-63 _public method_ `public Task<IOidcTokenInfo> GetAccessToken(string providerIdentifier, CancellationToken cancellationToken = default)` — (inheritdoc)
- L66-86 _public method_ `public Task<IOidcTokenInfo?> TryGetAccessToken(string providerIdentifier, CancellationToken cancellationToken = default)` — (inheritdoc)
- L89-92 _public method_ `public Task<OidcStatus> GetStatusForProvider(string providerIdentifier, CancellationToken cancellationToken)` — (inheritdoc)
- L99-125 _public method_ `public void ValidateAccessToken(string? token)` — Validate a fake access token minted by this class
- L130-134 _private method_ `private void RefreshAccessToken()` — Perform fake refresh of the access token
- L136-139 _private method_ `private IOidcTokenInfo GetOidcTokenInfo()`

### `Source/Programs/Shared/EpicGames.OIDC/HttpOidcAuthHandler.cs` (EpicGames.OIDC)


#### class `EpicGames.OIDC.HttpOidcAuthHandler`  
`public sealed class HttpOidcAuthHandler : DelegatingHandler`  
_public; L16-88_
- inherits: `DelegatingHandler`
- desc: HTTP message handler which automatically refreshes access tokens as required.
- L21-28 _public ctor_ `public HttpOidcAuthHandler(HttpMessageHandler innerHandler, IOidcAuthState authState, HttpOidcAuthHandlerConfig config, ILogger<HttpOidcAuthHandler>? logger = null) : base(innerHandler)` — Constructor
- L30 _private field_ `private readonly IOidcAuthState _authState`
- L31 _private field_ `private readonly HttpOidcAuthHandlerConfig _config`
- L32 _private field_ `private readonly ILogger<HttpOidcAuthHandler>? _logger`
- L33 _private field_ `private readonly HttpRequestOptionsKey<bool> _allowInteractiveLogin`
- L36-87 _protected method_ `protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.OIDC/HttpOidcAuthHandlerConfig.cs` (EpicGames.OIDC)


#### record `EpicGames.OIDC.HttpOidcAuthHandlerConfig`  
`public sealed record HttpOidcAuthHandlerConfig( string AllowInteractiveLoginHeaderKey, bool AllowInteractiveLogin = true, string AuthenticationScheme = "Bearer", int MaxAttempts = 3 )`  
_public; L8-8_
- desc: Configuration for a HttpOidcAuthHandler.

### `Source/Programs/Shared/EpicGames.OIDC/ITokenStore.cs` (EpicGames.OIDC)


#### interface `EpicGames.OIDC.ITokenStore`  
`public interface ITokenStore : IDisposable`  
_public; L15-22_
- inherits: `IDisposable`
- L18 _public method_ `public bool TryGetRefreshToken(string oidcProvider, [MaybeNullWhen(false)] out string refreshToken)` — Always reads fresh from the backing store (disk/keychain).
- L21 _public method_ `public void AddRefreshToken(string oidcProvider, string refreshToken)` — Persists immediately to the backing store.

#### class `EpicGames.OIDC.TokenUtils`  
`public static class TokenUtils`  
_public; L27-31_
- desc: Shared utilities for safe token logging.
- L30 _public method_ `public static string Fingerprint(string token)` — First 8 hex chars of SHA-256 - enough for log correlation without leaking the token.

#### class `EpicGames.OIDC.TokenStoreFactory`  
`public static class TokenStoreFactory`  
_public; L33-72_
- L35-51 _public method_ `public static ITokenStore CreateTokenStore(IServiceProvider provider)`
- L53-71 _public method_ `public static ITokenStore CreateTokenStore(ILoggerFactory? loggerFactory = null)`

### `Source/Programs/Shared/EpicGames.OIDC/InMemoryTokenStore.cs` (EpicGames.OIDC)


#### class `EpicGames.OIDC.InMemoryTokenStore`  
`internal sealed class InMemoryTokenStore : ITokenStore`  
_internal; L10-38_
- inherits: `ITokenStore`
- desc: An in-memory token store without encryption, intended for testing
- L12 _private field_ `private readonly Dictionary<string, string> _providerToRefreshToken = ...`
- L12 _private field_ `private readonly Dictionary< _providerToRefreshToken = []`
- L15-25 _public method_ `public bool TryGetRefreshToken(string oidcProvider, out string refreshToken)` — (inheritdoc)
- L28-31 _public method_ `public void AddRefreshToken(string oidcProvider, string refreshToken)` — (inheritdoc)
- L34-37 _public method_ `public void Dispose()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.OIDC/MacOSTokenStore.cs` (EpicGames.OIDC)


#### class `EpicGames.OIDC.MacOSTokenStore`  
`internal sealed class MacOSTokenStore : ITokenStore`  
_internal; L12-40_
- inherits: `ITokenStore`
- L14-16 _public ctor_ `public MacOSTokenStore()`
- L18-30 _public method_ `public bool TryGetRefreshToken(string oidcProvider, out string refreshToken)`
- L32-35 _public method_ `public void AddRefreshToken(string oidcProvider, string refreshToken)`
- L37-39 _public method_ `public void Dispose()`

#### class `EpicGames.OIDC.KeychainHelper`  
`static class KeychainHelper`  
_internal*; L42-110_
- L44 _private const_ `private const string OidcTokenIdentifier = "EpicGames OidcToken"`
- L46-83 _private method_ `private static string? RunKeychainHandler(string verb, List<string> args)`
- L85-96 _public method_ `public static void AddKeychainItem(string dataToEncrypt, string itemIdentifier)`
- L98-109 _public method_ `public static string? GetKeychainItem(string itemIdentifier)`

### `Source/Programs/Shared/EpicGames.OIDC/OidcAuthState.cs` (EpicGames.OIDC)


#### interface `EpicGames.OIDC.IOidcAuthState`  
`public interface IOidcAuthState`  
_public; L15-47_
- desc: Interface to manage the state of OIDC authentication.
- L20 _public* event_ `event Action? OnStateChanged` — Event handler for the auth state changes.
- L25 _public* property_ `bool IsLoggedIn { get; }` — Is there a valid auth header available?
- L30 _public* property_ `string? CurrentAccessToken { get; }` — Get the current access token, if one exists.
- L35 _public* method_ `void Reset()` — Reset the current auth state.
- L41 _public* method_ `void Invalidate(string? accessToken)` — Marks the given access token as invalid, typically after having attempted to use it and got an unauthorized response.
- L46 _public* method_ `Task<string?> GetAccessTokenAsync(bool interactive, CancellationToken cancellationToken)` — Get a valid access token, if possible.

#### class `EpicGames.OIDC.OidcAuthState`  
`public sealed class OidcAuthState( IOidcTokenManager oidcTokenManager, IStaticAccessTokenProvider staticAccessTokenProvider, IClock clock, IOidcAuthStateConfig config, ILogger<OidcAuthState> logger ) : IOidcAuthState, IAsyncDisposable`  
_public; L52-313_
- desc: Class used to track the last obtained token for a given OIDC provider.
- L61 _public event_ `public event Action? OnStateChanged` — (inheritdoc)
- L64-71 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L74-90 _public property_ `public bool IsLoggedIn { get; }` — (inheritdoc)
- L93-110 _public property_ `public string? CurrentAccessToken { get; }` — (inheritdoc)
- L113-124 _public method_ `public void Reset()` — (inheritdoc)
- L130-145 _public method_ `public void Invalidate(string? accessToken)` — Marks the given access token as invalid, having attempted to use it and got an unauthorized response
- L150-183 _public method_ `public async Task<string?> GetAccessTokenAsync(bool interactive, CancellationToken cancellationToken)` — Gets the current access token
- L185 _private field_ `private readonly Lock _lockObject = new()`
- L186 _private field_ `private readonly IOidcTokenManager _oidcTokenManager = oidcTokenManager`
- L187 _private field_ `private readonly IStaticAccessTokenProvider _staticAccessTokenProvider = staticAccessTokenProvider`
- L188 _private field_ `private readonly IClock _clock = clock`
- L189 _private field_ `private readonly IOidcAuthStateConfig _config = config`
- L190 _private field_ `private readonly ILogger _logger = logger`
- L193 _private field_ `private int _currentAuthTaskId`
- L194 _private field_ `private bool _currentAuthInteractive`
- L195 _private field_ `private BackgroundTask? _currentAuthWorker`
- L196 _private field_ `private TaskCompletionSource<AuthState>? _currentAuthResult`
- L201-214 _private method_ `private bool TryGetCurrentAuthState([NotNullWhen(true)] out AuthState? authState)` — Gets the current auth state instance. Fails if the current auth task has not finished.
- L216-274 _private method_ `private async Task GetAuthStateHandlerAsync(int authTaskId, bool interactive, BackgroundTask? prevAuthTask, CancellationToken cancellationToken)`
- L276-304 _private method_ `private async Task<AuthState> GetAuthStateInternalAsync(bool interactive, CancellationToken cancellationToken)`

#### record `EpicGames.OIDC.OidcAuthState.AuthState`  
`private record AuthState(IClock Clock, IOidcTokenInfo? TokenInfo, bool Interactive)`  
_private; L306-312_
- L308-311 _public method_ `public bool IsAuthorized()`

### `Source/Programs/Shared/EpicGames.OIDC/OidcAuthStateConfig.cs` (EpicGames.OIDC)


#### interface `EpicGames.OIDC.IOidcAuthStateConfig`  
`public interface IOidcAuthStateConfig`  
_public; L11-17_
- desc: Interface defining configuration for an OidcAuthState.
- L16 _public* method_ `Task<string> GetOidcProviderAsync(CancellationToken cancellationToken)` — The OIDC provider associated with this auth state.

#### class `EpicGames.OIDC.OidcAuthStateConfig`  
`public sealed class OidcAuthStateConfig(string oidcProvider) : IOidcAuthStateConfig`  
_public; L22-26_
- desc: Configuration for an OidcAuthState.
- L25 _public method_ `public Task<string> GetOidcProviderAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.OIDC/OidcTokenInfo.cs` (EpicGames.OIDC)


#### interface `EpicGames.OIDC.IOidcTokenInfo`  
`public interface IOidcTokenInfo`  
_public; L10-30_
- desc: Interface describing an OIDC token.
- L15 _public property_ `public string? RefreshToken { get; }` — The refresh token.
- L19 _public property_ `public string? AccessToken { get; }` — The access token.
- L24 _public property_ `public DateTimeOffset TokenExpiry { get; }` — When the token expires.
- L29 _public method_ `public bool IsValid(DateTimeOffset currentTime)` — Determine if the token is valid at the given time.

#### class `EpicGames.OIDC.OidcTokenInfo`  
`public class OidcTokenInfo : IOidcTokenInfo`  
_public; L35-62_
- inherits: `IOidcTokenInfo`
- desc: An OIDC access token, refresh token, and expiry.
- L38 _public property_ `public string? RefreshToken { get; set; }` — (inheritdoc)
- L41 _public property_ `public string? AccessToken { get; set; }` — (inheritdoc)
- L44 _public property_ `public DateTimeOffset TokenExpiry { get; set; }` — (inheritdoc)
- L47-61 _public method_ `public bool IsValid(DateTimeOffset currentTime)` — (inheritdoc)

#### class `EpicGames.OIDC.AnonymousOidcTokenInfo`  
`public sealed class AnonymousOidcTokenInfo : IOidcTokenInfo`  
_public; L67-80_
- inherits: `IOidcTokenInfo`
- desc: A fake OIDC token info representing calls that allow anonymous callers.
- L70 _public property_ `public string? RefreshToken => ...` — (inheritdoc)
- L73 _public property_ `public string? AccessToken => ...` — (inheritdoc)
- L76 _public property_ `public DateTimeOffset TokenExpiry => ...` — (inheritdoc)
- L79 _public method_ `public bool IsValid(DateTimeOffset currentTime)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.OIDC/OidcTokenManager.cs` (EpicGames.OIDC)


#### record `EpicGames.OIDC.TokenRefreshResult`  
`public record TokenRefreshResult( bool IsError, string? Error, string? ErrorDescription, string? AccessToken, string? RefreshToken, DateTimeOffset AccessTokenExpiration)`  
_public; L32-32_
- desc: Result of an OIDC token refresh operation.

#### interface `EpicGames.OIDC.IOidcTokenManager`  
`public interface IOidcTokenManager`  
_public; L36-45_
- L38 _public method_ `public Task<IOidcTokenInfo> LoginAsync(string providerIdentifier, CancellationToken cancellationToken = default)`
- L40 _public method_ `public Task<IOidcTokenInfo> GetAccessToken(string providerIdentifier, CancellationToken cancellationToken = default)`
- L42 _public method_ `public Task<IOidcTokenInfo?> TryGetAccessToken(string providerIdentifier, CancellationToken cancellationToken = default)`
- L44 _public method_ `public Task<OidcStatus> GetStatusForProvider(string providerIdentifier, CancellationToken cancellationToken = default)`

#### class `EpicGames.OIDC.OidcTokenManager`  
`public class OidcTokenManager : IOidcTokenManager`  
_public; L47-142_
- inherits: `IOidcTokenManager`
- L49 _private field_ `private readonly Lock _lockObject = new()`
- L50 _private field_ `private readonly Dictionary<string, OidcTokenClient> _tokenClients = ...`
- L50 _private field_ `private readonly Dictionary< _tokenClients = new(StringComparer.OrdinalIgnoreCase)`
- L51 _private field_ `private readonly ITokenStore _tokenStore`
- L53-56 _public ctor_ `public OidcTokenManager(ITokenStore tokenStore)`
- L58-70 _public method_ `public OidcTokenClient FindOrAddClient(string name, ProviderInfo providerInfo)`
- L72-87 _public ctor_ `public OidcTokenManager(IOptionsMonitor<OidcTokenOptions> settings, ITokenStore tokenStore, IOidcTokenClientFactory tokenClientFactory, List<string>? allowedProviders = null) : this(tokenStore)`
- L89-92 _public method_ `public static OidcTokenManager CreateTokenManager(IConfiguration providerConfiguration, ITokenStore tokenStore, List<string>? allowedProviders = null, ILoggerFactory? loggerFactory = null)`
- L94-112 _private ctor_ `private OidcTokenManager(IConfiguration providerConfiguration, ITokenStore tokenStore, List<string>? allowedProviders = null, ILoggerFactory? loggerFactory = null) : this(tokenStore)`
- L114-117 _public method_ `public bool HasUnfinishedLogin()`
- L120-123 _public method_ `public Task<IOidcTokenInfo> LoginAsync(string providerIdentifier, CancellationToken cancellationToken = default)` — (inheritdoc)
- L126-129 _public method_ `public Task<IOidcTokenInfo> GetAccessToken(string providerIdentifier, CancellationToken cancellationToken = default)` — (inheritdoc)
- L132-135 _public method_ `public Task<IOidcTokenInfo?> TryGetAccessToken(string providerIdentifier, CancellationToken cancellationToken = default)` — (inheritdoc)
- L138-141 _public method_ `public Task<OidcStatus> GetStatusForProvider(string providerIdentifier, CancellationToken cancellationToken = default)` — (inheritdoc)

#### interface `EpicGames.OIDC.IOidcTokenClientFactory`  
`public interface IOidcTokenClientFactory`  
_public; L144-147_
- L146 _public* method_ `OidcTokenClient CreateTokenClient(string key, ProviderInfo providerInfo, TimeSpan loginTimeout)`

#### class `EpicGames.OIDC.OidcTokenClientFactory`  
`public class OidcTokenClientFactory(IServiceProvider provider) : IOidcTokenClientFactory`  
_public; L149-155_
- L151-154 _public method_ `public OidcTokenClient CreateTokenClient(string key, ProviderInfo providerInfo, TimeSpan loginTimeout)`

#### enum `EpicGames.OIDC.OidcStatus`  
`public enum OidcStatus`  
_public; L157-173_
- L162 _public* enumerator_ `Connected` — Both access and refresh token are valid
- L167 _public* enumerator_ `NotLoggedIn` — No refresh token is set and requires login
- L172 _public* enumerator_ `TokenRefreshRequired` — Access token has not been generated or has expired, and needs refreshing

#### class `EpicGames.OIDC.OidcHttpRequest`  
`public class OidcHttpRequest`  
_public; L178-211_
- desc: The data read from a http request into the oidc client, mostly a wrapper around the http.listener context
- L180-189 _public ctor_ `public OidcHttpRequest(HttpListenerContext context)`
- L192-201 _public ctor_ `public OidcHttpRequest(string rawUrl, string contentType, string httpMethod, Stream body, bool hasBody, Encoding bodyEncoding)`
- L203 _public property_ `public bool HasBody { get; init; }`
- L204 _public property_ `public string HttpMethod { get; init; }`
- L206 _public property_ `public string? RawUrl { get; init; }`
- L208 _public property_ `public string? ContentType { get; init; }`
- L209 _public property_ `public Stream Body { get; init; }`
- L210 _public property_ `public Encoding BodyEncoding { get; init; }`

#### interface `EpicGames.OIDC.IOidcHttpResponse`  
`public interface IOidcHttpResponse : IDisposable`  
_public; L216-239_
- inherits: `IDisposable`
- desc: Interface for the response writing that happens from the local http server, usually wraps a http.listener response
- L221 _public property_ `public long ContentLength64 { get; set; }` — The content length header value
- L225 _public property_ `public int StatusCode { get; set; }` — The status code header value
- L230 _public property_ `public Stream OutputStream { get; }` — The body of the response
- L235-238 _public method_ `public void Close()` — Used to explicitly close the response when finished

#### class `EpicGames.OIDC.OidcHttpResponse`  
`public sealed class OidcHttpResponse(HttpListenerContext context) : IOidcHttpResponse`  
_public; L245-267_
- desc: Implementation of a response writer for http listener
- L247 _private field_ `private readonly HttpListenerResponse _response = context.Response`
- L250 _public property_ `public long ContentLength64 { get; set; }` — (inheritdoc)
- L252 _public property_ `public int StatusCode { get; set; }` — (inheritdoc)
- L254 _public property_ `public Stream OutputStream => ...` — (inheritdoc)
- L257-260 _public method_ `public void Close()` — (inheritdoc)
- L263-266 _public method_ `public void Dispose()` — (inheritdoc)

#### class `EpicGames.OIDC.NullOidcHttpResponse`  
`public class NullOidcHttpResponse(Stream outputStream) : IOidcHttpResponse`  
_public; L270-297_
- L276-282 _protected method_ `protected virtual void Dispose(bool disposing)` — Dispose method
- L285-289 _public method_ `public void Dispose()` — (inheritdoc)
- L292 _public property_ `public long ContentLength64 { get; set; }` — (inheritdoc)
- L294 _public property_ `public int StatusCode { get; set; }` — (inheritdoc)
- L296 _public property_ `public Stream OutputStream { get; }` — (inheritdoc)

#### class `EpicGames.OIDC.OidcHttpServer`  
`public class OidcHttpServer : IDisposable`  
_public; L303-348_
- inherits: `IDisposable`
- L305 _private field_ `private readonly HttpListener _http = new()`
- L307-310 _public method_ `public virtual void Start()`
- L316-322 _protected method_ `protected virtual void Dispose(bool disposing)` — Dispose method
- L325-329 _public method_ `public void Dispose()` — (inheritdoc)
- L332-336 _public method_ `public virtual void Stop()`
- L338-341 _public method_ `public virtual void AddPrefixes(string prefix)`
- L343-347 _public method_ `public virtual async Task<(OidcHttpRequest, IOidcHttpResponse)> ProcessNextRequestAsync()`

#### class `EpicGames.OIDC.OidcTokenClient`  
`public class OidcTokenClient`  
_public; L350-945_
- L353 _private const_ `private const int RefreshHttpTimeoutSeconds = 30` — Max seconds the refresh HTTP call is allowed before cancellation.
- L356 _private const_ `private const int LockAcquireTimeoutSeconds = 60` — Max seconds to wait for another process to release the refresh lock.
- L358 _public property_ `public string Name => ...`
- L359 _public property_ `public string DisplayName => ...`
- L361 _private field_ `private readonly string _name`
- L362 _private field_ `private readonly ProviderInfo _providerInfo`
- L363 _private field_ `private readonly TimeSpan _loginTimeout`
- L364 _private field_ `private readonly ITokenStore _tokenStore`
- L365 _private field_ `private readonly ILogger<OidcTokenClient>? _logger`
- L366 _private field_ `private readonly Uri _authorityUri`
- L367 _private field_ `private readonly string _clientId`
- L368 _private field_ `private readonly string _scopes`
- L370 _private field_ `private string? _accessToken`
- L371 _private field_ `private DateTimeOffset _tokenExpiry`
- L373 _private field_ `private readonly List<Uri> _redirectUris`
- L374 _private field_ `private readonly string? _genericErrorInformation`
- L375 _private field_ `private readonly bool _useDiscoveryDocument`
- L377-408 _public ctor_ `public OidcTokenClient(string name, ProviderInfo providerInfo, TimeSpan loginTimeout, ITokenStore tokenStore, ILogger<OidcTokenClient>? logger = null)`
- L410-443 _private method_ `private async Task<OidcClientOptions> BuildClientOptionsAsync(Uri redirectUri, CancellationToken cancellationToken)`
- L445-466 _public method_ `public async Task<IOidcTokenInfo> LoginAsync(CancellationToken cancellationToken)`
- L468-550 _private method_ `private async Task<IOidcTokenInfo> DoLoginAsync(CancellationToken cancellationToken)`
- L552-555 _public method_ `public virtual OidcHttpServer CreateHttpServer()`
- L557-560 _public method_ `public virtual OidcClient DoCreateOidcClient(OidcClientOptions options)`
- L562-641 _private method_ `private async Task<LoginResult> ProcessHttpRequestAsync(OidcHttpServer http, AuthorizeState loginState, OidcClient oidcClient, CancellationToken cancellationToken)`
- L643-651 _private method_ `private static string GetSuccessPage()`
- L653-663 _private method_ `private static string GetFailurePage(LoginResult loginResult, string? generalErrorMessage = null)`
- L666-713 _public method_ `public virtual Process? OpenBrowser(string url)`
- L715-725 _private method_ `private static bool IsRunningWsl()`
- L730-736 _protected method_ `protected virtual async Task<TokenRefreshResult> DoRefreshAsync(string refreshToken, CancellationToken cancellationToken)` — Performs the OIDC token refresh via HTTP. Virtual for testability.
- L741-759 _protected method_ `protected virtual async Task<IDisposable> AcquireRefreshLockAsync(CancellationToken cancellationToken)` — Acquire machine-wide lock for the refresh operation. Virtual for testability.
- L761-826 _private method_ `private async Task<OidcTokenInfo?> TryDoRefreshTokenAsync(string refreshToken, CancellationToken cancellationToken)`
- L828-851 _private method_ `private async Task<DiscoveryDocumentResponse> GetDiscoveryDocumentAsync(CancellationToken cancellationToken)`
- L853-856 _public method_ `public async Task<IOidcTokenInfo> GetAccessTokenAsync(CancellationToken cancellationToken)`
- L858-918 _public method_ `public async Task<IOidcTokenInfo?> TryGetAccessTokenAsync(CancellationToken cancellationToken)`
- L920-924 _public method_ `public OidcStatus GetStatus()`
- L926-944 _public method_ `public static OidcStatus GetStatus(string? refreshToken, string? accessToken, DateTimeOffset accessTokenExpiry)`

#### class `EpicGames.OIDC.LoginFailedException`  
`public class LoginFailedException : Exception`  
_public; L947-954_
- inherits: `Exception`
- L949-952 _public ctor_ `public LoginFailedException(string message, string errorDescription) : base(message)`
- L953 _public property_ `public string ErrorDescription { get; }`

#### class `EpicGames.OIDC.HttpServerException`  
`public class HttpServerException : Exception`  
_public; L956-961_
- inherits: `Exception`
- L958-960 _public ctor_ `public HttpServerException(string message) : base(message)`

#### class `EpicGames.OIDC.NotLoggedInException`  
`public class NotLoggedInException : Exception`  
_public; L963-965_
- inherits: `Exception`

#### class `EpicGames.OIDC.OidcTokenOptions`  
`public class OidcTokenOptions`  
_public; L967-979_
- L969 _public property_ `public Dictionary<string, ProviderInfo> Providers { get; set; }`
- L971 _public property_ `public TimeSpan LoginTimeout { get; set; }`
- L973-978 _public method_ `public static OidcTokenOptions Bind(IConfiguration config)`

#### class `EpicGames.OIDC.ProviderInfo`  
`public class ProviderInfo`  
_public; L981-998_
- L983 _public property_ `public Uri ServerUri { get; set; }` — attrs: `[Required]`
- L985 _public property_ `public string ClientId { get; set; }` — attrs: `[Required]`
- L987 _public property_ `public string DisplayName { get; set; }` — attrs: `[Required]`
- L989 _public property_ `public Uri? RedirectUri { get; set; }`
- L991 _public property_ `public List<Uri>? PossibleRedirectUri { get; set; }`
- L992 _public property_ `public bool LoadClaimsFromUserProfile { get; set; }` — attrs: `[Required]`
- L994 _public property_ `public string Scopes { get; set; }`
- L995 _public property_ `public string? GenericErrorInformation { get; set; }`
- L996 _public property_ `public bool UseDiscoveryDocument { get; set; }`
- L997 _public property_ `public string? ClientSecret { get; set; }`

### `Source/Programs/Shared/EpicGames.OIDC/Properties/AssemblyInfo.cs` (EpicGames.OIDC)
_(no declarations)_


### `Source/Programs/Shared/EpicGames.OIDC/ProviderConfigurationFactory.cs` (EpicGames.OIDC)


#### class `EpicGames.OIDC.ProviderConfigurationFactory`  
`public static class ProviderConfigurationFactory`  
_public; L18-118_
- L20 _private* const_ `const string ConfigFileName = "oidc-configuration.json"`
- L22 _public property_ `public static IReadOnlyList<string> ConfigPaths { get; }`
- L29-52 _public method_ `public static IConfiguration ReadConfiguration(DirectoryInfo engineDir, DirectoryInfo? gameDir)`
- L54-64 _public method_ `public static IConfiguration MergeConfiguration(IEnumerable<(DirectoryInfo, DirectoryInfo?)> configurationPaths)`
- L66-103 _public method_ `public static async Task<ClientAuthConfigurationV1?> ReadRemoteAuthConfigurationAsync(Uri remoteUrl, string encryptionKey)`
- L105 _public const_ `public const string DefaultEncryptionKey = "892a27ef5cbf4894af2e6bd53a54aa48"`
- L107-117 _public method_ `public static IConfiguration BindOptions(ClientAuthConfigurationV1 remoteAuthConfig)`

#### class `EpicGames.OIDC.ClientAuthConfigurationV1`  
`public class ClientAuthConfigurationV1 : OidcTokenOptions`  
_public; L120-131_
- inherits: `OidcTokenOptions`
- L125 _public property_ `public string? DefaultProvider { get; set; }` — The provider in Providers to use by default
- L130 _public property_ `public string Method { get; set; }` — Can be set to "Anonymous" to indicate that auth is disabled. This is a horde specific convention.

#### class `EpicGames.OIDC.ProviderConfigurationStateContext`  
`internal partial class ProviderConfigurationStateContext : JsonSerializerContext`  
_internal; L134-136_
- attrs: `[JsonSerializable(typeof(ClientAuthConfigurationV1))]`
- inherits: `JsonSerializerContext`

### `Source/Programs/Shared/EpicGames.OIDC/StaticAccessTokenProvider.cs` (EpicGames.OIDC)


#### interface `EpicGames.OIDC.IStaticAccessTokenProvider`  
`public interface IStaticAccessTokenProvider`  
_public; L8-14_
- desc: Interface to support getting a static access token.
- L13 _public* property_ `string? AccessToken { get; }` — The static access token, if one exists, or null.

#### class `EpicGames.OIDC.NullStaticAccessTokenProvider`  
`public sealed class NullStaticAccessTokenProvider : IStaticAccessTokenProvider`  
_public; L19-23_
- inherits: `IStaticAccessTokenProvider`
- desc: Static access token provider that never provides a static access token.
- L22 _public property_ `public string? AccessToken => ...` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.OIDC/TokenStore.cs` (EpicGames.OIDC)


#### class `EpicGames.OIDC.TokenStoreStateContext`  
`internal partial class TokenStoreStateContext : JsonSerializerContext`  
_internal; L16-18_
- attrs: `[JsonSerializable(typeof(TokenStoreState))]`
- inherits: `JsonSerializerContext`

#### class `EpicGames.OIDC.TokenStoreState`  
`internal class TokenStoreState`  
_internal; L20-41_
- L22 _public property_ `public Dictionary<string, string> Providers { get; set; }`
- L23 _public property_ `public string Key { get; set; }`
- L26-30 _public ctor_ `public TokenStoreState(string key, Dictionary<string, string> providers)` — attrs: `[JsonConstructor]`
- L32-40 _public ctor_ `public TokenStoreState(byte[] key, Dictionary<string, byte[]> providers)`

#### class `EpicGames.OIDC.FilesystemTokenStore`  
`internal sealed class FilesystemTokenStore : ITokenStore`  
_internal; L46-160_
- inherits: `ITokenStore`
- desc: A generic token store that saves the offline token in a file on disk, this works on any platform
- L48 _private field_ `private readonly SymmetricAlgorithm _crypt = Aes.Create()`
- L50-52 _public ctor_ `public FilesystemTokenStore()`
- L54-57 _private method_ `private static FileInfo GetStorePath()`
- L59-94 _private method_ `private static void ReadStoreFromDisk(out Dictionary<string, byte[]> providers, out byte[]? iv)`
- L96-113 _private method_ `private static void WriteStoreToDisk(byte[] iv, Dictionary<string, byte[]> providers)`
- L115-129 _public method_ `public bool TryGetRefreshToken(string oidcProvider, out string refreshToken)`
- L131-145 _public method_ `public void AddRefreshToken(string oidcProvider, string refreshToken)`
- L147-154 _private* method_ `static byte[] GetSeed()`
- L156-159 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.OIDC/WindowsTokenStore.cs` (EpicGames.OIDC)


#### class `EpicGames.OIDC.WindowsTokenStoreStateContext`  
`internal partial class WindowsTokenStoreStateContext : JsonSerializerContext`  
_internal; L20-22_
- attrs: `[JsonSerializable(typeof(WindowsTokenStoreState))]`
- inherits: `JsonSerializerContext`

#### class `EpicGames.OIDC.WindowsTokenStoreState`  
`internal class WindowsTokenStoreState`  
_internal; L24-41_
- L26 _public property_ `public Dictionary<string, string> Providers { get; set; }`
- L29-32 _public ctor_ `public WindowsTokenStoreState(Dictionary<string, string> providers)` — attrs: `[JsonConstructor]`
- L34-40 _public ctor_ `public WindowsTokenStoreState(Dictionary<string, byte[]> providers)`

#### class `EpicGames.OIDC.WindowsTokenStore`  
`internal sealed class WindowsTokenStore : ITokenStore`  
_internal; L43-247_
- inherits: `ITokenStore`
- L45 _private field_ `private readonly ILogger<WindowsTokenStore>? _logger = null`
- L46 _private field_ `private readonly string? _storePathOverride`
- L48-50 _public ctor_ `public WindowsTokenStore()`
- L53-56 _public ctor_ `public WindowsTokenStore(ILogger<WindowsTokenStore> logger)` — attrs: `[ActivatorUtilitiesConstructor]`
- L59-63 _internal ctor_ `internal WindowsTokenStore(ILogger<WindowsTokenStore>? logger, string storePath)` — Test-only constructor that redirects the store to a custom path.
- L65-69 _private method_ `private FileInfo GetStorePath()`
- L71-130 _private method_ `private Dictionary<string, byte[]> ReadStoreFromDisk()`
- L132-165 _private method_ `private void WriteStoreToDisk(Dictionary<string, byte[]> providers, ILogger? logger)`
- L167-199 _public method_ `public bool TryGetRefreshToken(string oidcProvider, out string refreshToken)`
- L201-204 _private method_ `private static byte[] GetEntropy(string oidcProvider)`
- L206-242 _public method_ `public void AddRefreshToken(string oidcProvider, string refreshToken)`
- L244-246 _public method_ `public void Dispose()`

#### class `EpicGames.OIDC.CryptProtectDataHelper`  
`static class CryptProtectDataHelper`  
_internal*; L250-440_
- L253 _private method_ `private static extern IntPtr LocalFree(IntPtr hMem)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L313 _private method_ `private static extern bool CryptProtectData( ref DataBlob pDataIn, string szDataDescr, ref DataBlob pOptionalEntropy, IntPtr pvReserved, IntPtr pPromptStruct, CryptProtectFlags dwFlags, ref DataBlob pDataOut )` — attrs: `[ DllImport("Crypt32.dll", SetLastError = true, CharSet = CharSet.Auto) ] [return: MarshalAs(UnmanagedType.Bool)]`
- L329 _private method_ `private static extern bool CryptUnprotectData( ref DataBlob pDataIn, string szDataDescr, ref DataBlob pOptionalEntropy, IntPtr pvReserved, IntPtr pPromptStruct, CryptProtectFlags dwFlags, ref DataBlob pDataOut )` — attrs: `[ DllImport("Crypt32.dll", SetLastError = true, CharSet = CharSet.Auto) ] [return: MarshalAs(UnmanagedType.Bool)]`
- L339-388 _public method_ `public static byte[] DoCryptProtectData(byte[] dataToProtect, string description, byte[] entropy)`
- L390-439 _public method_ `public static byte[] DoCryptUnprotectData(byte[] dataToDecrypt, string description, byte[] entropy)`

#### struct `EpicGames.OIDC.CryptProtectDataHelper.DataBlob`  
`private struct DataBlob`  
_private; L256-260_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L258 _public field_ `public int cbData`
- L259 _public field_ `public IntPtr pbData`

#### enum `EpicGames.OIDC.CryptProtectDataHelper.CryptProtectFlags`  
`private enum CryptProtectFlags`  
_private; L263-286_
- attrs: `[Flags]`
- L268 _public* enumerator_ `CryptprotectUiForbidden = 0x1`
- L272 _public* enumerator_ `CryptprotectLocalMachine = 0x4`
- L276 _public* enumerator_ `CryptprotectCredSync = 0x8`
- L279 _public* enumerator_ `CryptprotectAudit = 0x10`
- L282 _public* enumerator_ `CryptprotectNoRecovery = 0x20`
- L285 _public* enumerator_ `CryptprotectVerifyProtection = 0x40`

#### enum `EpicGames.OIDC.CryptProtectDataHelper.CryptProtectPromptFlags`  
`private enum CryptProtectPromptFlags`  
_private; L289-296_
- attrs: `[Flags]`
- L292 _public* enumerator_ `CryptprotectPromptOnUnprotect = 0x1`
- L295 _public* enumerator_ `CryptprotectPromptOnProtect = 0x2`

#### struct `EpicGames.OIDC.CryptProtectDataHelper.CryptprotectPromptstruct`  
`private struct CryptprotectPromptstruct`  
_private; L299-305_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L301 _public field_ `public int cbSize`
- L302 _public field_ `public CryptProtectPromptFlags dwPromptFlags`
- L303 _public field_ `public IntPtr hwndApp`
- L304 _public field_ `public string szPrompt`
