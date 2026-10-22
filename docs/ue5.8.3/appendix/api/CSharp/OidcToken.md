# CSharp / OidcToken

- project root: `Source/Programs/OidcToken`
- files: 2; symbols: 64
- symbol kinds: class=11, ctor=3, enum=2, enumerator=9, field=5, method=9, property=25
- access marked `*` is implicit (not written in source)

### `Source/Programs/OidcToken/Program.cs` (OidcToken)


#### class `OidcToken.GetHordeAuthConfigResponse`  
`class GetHordeAuthConfigResponse`  
_internal*; L22-32_
- L24 _public property_ `public string Method { get; set; }`
- L25 _public property_ `public string ProfileName { get; set; }`
- L26 _public property_ `public string ServerUrl { get; set; }`
- L27 _public property_ `public string ClientId { get; set; }`
- L28 _public property_ `public List<string> LocalRedirectUrls { get; set; }`
- L29 _public property_ `public string[]? Scopes { get; set; }`
- L31 _public method_ `public bool IsAnonymous()`

#### class `OidcToken.OidcTokenStateContext`  
`internal partial class OidcTokenStateContext : JsonSerializerContext`  
_internal; L37-39_
- attrs: `[JsonSourceGenerationOptions(PropertyNameCaseInsensitive = true)] [JsonSerializable(typeof(GetHordeAuthConfigResponse))] [JsonSerializable(typeof(Dictionary<string, object>), TypeInfoPropertyName = "SettingsDict")]`
- inherits: `JsonSerializerContext`

#### class `OidcToken.Program`  
`class Program`  
_internal*; L41-318_
- L43-282 _private* method_ `static async Task<int> Main(string[] args)`
- L284-317 _private* method_ `static async Task<GetHordeAuthConfigResponse> ReadHordeConfigurationAsync(Uri hordeUrl)`

#### class `OidcToken.ExitCodeHelper`  
`static class ExitCodeHelper`  
_internal*; L320-353_

#### enum `OidcToken.ExitCodeHelper.ExitCode`  
`public enum ExitCode`  
_public; L322-352_
- L327 _public* enumerator_ `Success = 0` — Successful run
- L331 _public* enumerator_ `UnknownError = 1` — Unknown error
- L335 _public* enumerator_ `UnableToStartHttpServer = 2` — Unable to start the http server, mostly likely a port collision
- L339 _public* enumerator_ `NetworkError = 3` — Network error, likely caused by bad or lack of network connection. Includes DNS resolve issues.
- L343 _public* enumerator_ `UnableToParseConfiguration = 9` — Successfully fetched a remote configuration but there were some parsing or logic issue with it
- L347 _public* enumerator_ `UnableToAllocateToken = 10` — Something went wrong when trying to allocate a new access token. Most often the refresh token is expired, and we are running with --unattended so we can not trigger a new interactive login.
- L351 _public* enumerator_ `AuthIsDisabled= 11` — Auth is disabled according to the remote configuration

### `Source/Programs/OidcToken/TokenService.cs` (OidcToken)


#### class `OidcToken.TokenServiceStateContext`  
`internal partial class TokenServiceStateContext : JsonSerializerContext`  
_internal; L25-27_
- attrs: `[JsonSerializable(typeof(ZenAddOidcTokenRequest))] [JsonSerializable(typeof(TokenResultFile))] [JsonSerializable(typeof(TokenStatusFile))]`
- inherits: `JsonSerializerContext`

#### class `OidcToken.TokenResultFile`  
`internal class TokenResultFile`  
_internal; L29-41_
- L31 _public property_ `public string Token { get; set; }`
- L32 _public property_ `public DateTimeOffset ExpiresAt { get; set; }`
- L33 _public property_ `public DateTime ExpiresAtUtc { get; set; }`
- L35-40 _public ctor_ `public TokenResultFile(string token, DateTimeOffset expiresAt)`

#### class `OidcToken.TokenStatusFile`  
`internal class TokenStatusFile`  
_internal; L43-54_
- L45 _public property_ `public string Service { get; set; }`
- L47 _public property_ `public OidcStatus Status { get; set; }`
- L49-53 _public ctor_ `public TokenStatusFile(string service, OidcStatus status)`

#### class `OidcToken.ZenAddOidcTokenRequest`  
`internal class ZenAddOidcTokenRequest`  
_internal; L57-61_
- L59 _public property_ `public string? ProviderName { get; set; }`
- L60 _public property_ `public string? RefreshToken { get; set; }`

#### class `OidcToken.TokenService`  
`internal class TokenService : IHostedService`  
_internal; L63-262_
- inherits: `IHostedService`
- L65 _private field_ `private readonly ILogger<TokenService> Logger`
- L66 _private field_ `private readonly IHostApplicationLifetime AppLifetime`
- L67 _private field_ `private readonly IOptionsMonitor<TokenServiceOptions> Settings`
- L68 _private field_ `private readonly IOidcTokenManager TokenManager`
- L69 _private field_ `private int? ExitCode`
- L71-77 _public ctor_ `public TokenService(ILogger<TokenService> logger, IHostApplicationLifetime appLifetime, IOptionsMonitor<TokenServiceOptions> settings, IOidcTokenManager tokenManager)`
- L79-112 _public method_ `public Task StartAsync(CancellationToken cancellationToken)`
- L114-210 _public method_ `public async Task Main()`
- L212-225 _private method_ `private async Task OutputToken(string token, DateTimeOffset expiresAt)`
- L227-255 _private method_ `private async Task OutputStatus(string service, OidcStatus status)`
- L257-261 _public method_ `public Task StopAsync(CancellationToken cancellationToken)`

#### class `OidcToken.UnableToAllocateTokenException`  
`internal class UnableToAllocateTokenException : Exception`  
_internal; L264-266_
- inherits: `Exception`

#### class `OidcToken.TokenServiceOptions`  
`internal class TokenServiceOptions: IValidatableObject`  
_internal; L268-346_
- inherits: `IValidatableObject`
- L279 _public property_ `public string Service { get; set; }` — attrs: `[Required]` — The provider identifier you wish to login to
- L284 _public property_ `public Uri? HordeUrl { get; set; }` — URL of the horde server to read provider information from
- L289 _public property_ `public string? AuthConfigUrl { get; set; }` — URL of the server to read provider information from
- L294 _public property_ `public string AuthEncryptionKey { get; set; }` — The encryption key used for the remote auth, the default key is usually used to avoid having to ship this config value. This needs to be a 16 byte string hex encoded string.
- L299 _public property_ `public TokenServiceMode Mode { get; set; }` — attrs: `[Required]` — The mode we are running OidcToken in
- L304 _public property_ `public bool ResultToConsole { get; set; }` — Set to output results to stdout (can be combined with a file)
- L309 _public property_ `public string OutFile { get; set; }` — A path to were we output a file with our results, format will depend on mode. Set to empty string to disable.
- L314 _public property_ `public bool Unattended { get; set; }` — If set this indicates we should not expect a user to be present
- L319 _public property_ `public bool Zen { get; set; }` — If set this indicates a zen instance exists and we should share the token with it
- L324 _public property_ `public string ZenUrl { get; set; }` — The url to the zen server that we should share a token with (if Zen flag is set)
- L329 _public property_ `public string? Project { get; set; }` — Path to the game root directory
- L334 _public property_ `public string? ConfigPath { get; set; }` — Path to the configuration file to use if you know exactly which config to use
- L336-345 _public method_ `public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)`

#### enum `OidcToken.TokenServiceOptions.TokenServiceMode`  
`public enum TokenServiceMode`  
_public; L270-274_
- L272 _public* enumerator_ `Query`
- L273 _public* enumerator_ `GetToken`
