# CSharp / HordeServer

- project root: `Source/Programs/Horde/HordeServer`
- files: 102; symbols: 1875
- symbol kinds: class=199, const=37, ctor=136, delegate=1, enum=4, enumerator=25, event=1, field=287, indexer=1, interface=13, method=731, property=420, record=17, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/HordeServer/Accounts/AccountAclAction.cs` (HordeServer)


#### class `HordeServer.Accounts.AccountAclAction`  
`public static class AccountAclAction`  
_public; L10-31_
- desc: ACL actions valid for manipulating jobs
- L15 _public property_ `public static AclAction CreateAccount { get; }` — Ability to create new accounts
- L20 _public property_ `public static AclAction UpdateAccount { get; }` — Update an account settings
- L25 _public property_ `public static AclAction DeleteAccount { get; }` — Delete an account from the server
- L30 _public property_ `public static AclAction ViewAccount { get; }` — Ability to view account information

### `Source/Programs/Horde/HordeServer/Accounts/AccountCollection.cs` (HordeServer)


#### class `HordeServer.Accounts.PasswordHasher`  
`public static class PasswordHasher`  
_public; L23-96_
- desc: Password hasher
- L25 _private const_ `private const int SaltSize = 16`
- L26 _private const_ `private const int KeySize = 32`
- L27 _private const_ `private const int Iterations = 100000`
- L33-39 _public method_ `public static byte[] GenerateSalt()` — Generate a new salt for use with password hash
- L47-50 _public method_ `public static byte[] HashPassword(string password, byte[] salt)` — Create a hash for the given password
- L59-63 _public method_ `public static bool ValidatePassword(string password, byte[] salt, byte[] correctHash)` — Validate a password
- L71-79 _public method_ `public static byte[] SaltFromString(string? saltString)` — Convert a salt string to byte array
- L87-95 _public method_ `public static byte[] HashFromString(string? hashString)` — Convert a hash string to byte array

#### class `HordeServer.Accounts.AccountCollection`  
`public class AccountCollection : IAccountCollection`  
_public; L101-381_
- inherits: `IAccountCollection`
- desc: Collection of service account documents
- L196 _private* const_ `const int DuplicateKeyErrorCode = 11000`
- L198 _private field_ `private static readonly AccountId s_defaultAdminAccountId = AccountId.Parse("65d4f282ff286703e0609ccd")`
- L200 _private field_ `private bool _hasCreatedAdminAccount = false`
- L201 _private field_ `private readonly IMongoCollection<AccountDocument> _accounts`
- L203 _private* method_ `static string NormalizeLogin(string login)`
- L210-213 _public ctor_ `public AccountCollection(IMongoService mongoService)` — Constructor
- L216-250 _public method_ `public async Task<IAccount> CreateAsync( CreateAccountOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L253-273 _public method_ `public async ValueTask CreateAdminAccountAsync(string password, CancellationToken cancellationToken)` — (inheritdoc)
- L276-286 _public method_ `public async Task<IReadOnlyList<IAccount>> FindAsync(int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L289-294 _public method_ `public async Task<IAccount?> GetAsync(AccountId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L297-304 _public method_ `public async Task<IAccount?> FindByLoginAsync(string login, CancellationToken cancellationToken = default)` — (inheritdoc)
- L307-363 _private* method_ `async Task<AccountDocument?> TryUpdateAsync(AccountDocument document, UpdateAccountOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L366-373 _public method_ `public Task DeleteAsync(AccountId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L375-380 _private* method_ `static (string Salt, string Hash) CreateSaltAndHashPassword(string password)`

#### record `HordeServer.Accounts.AccountCollection.ClaimDocument`  
`record class ClaimDocument(string Type, string Value) : IUserClaim`  
_private*; L103-110_
- inherits: `IUserClaim`
- L105-106 _public ctor_ `public ClaimDocument(IUserClaim claim) : this(claim.Type, claim.Value)`
- L108-109 _public ctor_ `public ClaimDocument(AclClaimConfig claim) : this(claim.Type, claim.Value)`

#### class `HordeServer.Accounts.AccountCollection.AccountDocument`  
`private class AccountDocument : IAccount`  
_private; L115-194_
- inherits: `IAccount`
- desc: Concrete implementation of IHordeAccount
- L118 _private* field_ `AccountCollection? _accountCollection` — attrs: `[BsonIgnore]`
- L122 _public property_ `public AccountId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — (inheritdoc)
- L125 _public property_ `public string Name { get; set; }` — (inheritdoc)
- L128 _public property_ `public string Login { get; set; }` — (inheritdoc)
- L131 _public property_ `public string NormalizedLogin { get; set; }` — (inheritdoc)
- L134 _public property_ `public string? Email { get; set; }` — (inheritdoc)
- L137 _public property_ `public string? PasswordHash { get; set; }` — (inheritdoc)
- L140 _public property_ `public string? PasswordSalt { get; set; }` — (inheritdoc)
- L143 _public property_ `public List<ClaimDocument> Claims { get; set; }` — attrs: `[BsonElement("Claims2")]`
- L146 _public property_ `public bool Enabled { get; set; }` — (inheritdoc)
- L149 _public property_ `public string Description { get; set; }` — (inheritdoc)
- L152 _public property_ `public string SessionKey { get; set; }` — (inheritdoc)
- L155 _public property_ `public int UpdateIndex { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(0)]`
- L157 _private* property_ `IReadOnlyList<IUserClaim> IAccount.Claims => ...`
- L160-162 _private ctor_ `private AccountDocument()` — attrs: `[BsonConstructor]`
- L164-170 _public ctor_ `public AccountDocument(AccountId id, string name, string login)`
- L172-175 _public method_ `public void PostLoad(AccountCollection accountCollection)`
- L177-187 _public method_ `public bool ValidatePassword(string password)`
- L189 _public method_ `public async Task<IAccount?> RefreshAsync(CancellationToken cancellationToken)`
- L192 _public method_ `public async Task<IAccount?> TryUpdateAsync(UpdateAccountOptions options, CancellationToken cancellationToken)`

#### class `HordeServer.Accounts.LoginAlreadyTakenException`  
`public class LoginAlreadyTakenException : Exception`  
_public; L386-392_
- inherits: `Exception`
- desc: Exception thrown when a user name is already taken
- L388-391 _internal ctor_ `internal LoginAlreadyTakenException(string name) : base($"The login '{name}' is already taken")`

### `Source/Programs/Horde/HordeServer/Accounts/AccountsController.cs` (HordeServer)


#### class `HordeServer.Accounts.AccountsController`  
`public class AccountsController : HordeControllerBase`  
_public; L23-284_
- attrs: `[ApiController] [Authorize]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/accounts endpoint
- L25 _private* field_ `readonly IAccountCollection _accountCollection`
- L26 _private* field_ `readonly GlobalConfig _globalConfig`
- L27 _private* field_ `readonly IOptionsMonitor<ServerSettings> _settings`
- L32-37 _public ctor_ `public AccountsController(IAccountCollection accountCollection, IOptionsSnapshot<GlobalConfig> globalConfig, IOptionsMonitor<ServerSettings> settings)` — Constructor
- L45-55 _public method_ `public async Task<ActionResult<CreateAccountResponse>> CreateAccountAsync([FromBody] CreateAccountRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/accounts")] [ProducesResponseType(typeof(CreateAccountResponse), 200)]` — Create a new account
- L63-79 _public method_ `public async Task<ActionResult<List<GetAccountResponse>>> FindAccountsAsync([FromQuery] int? index = null, [FromQuery] int? count = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/accounts")] [ProducesResponseType(typeof(List<GetAccountResponse>), 200)]` — Gets a list of accounts
- L88-104 _public method_ `public async Task<ActionResult<object>> GetCurrentAccountAsync([FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/accounts/current")] [ProducesResponseType(typeof(GetAccountResponse), 200)] [ProducesResponseType(404)]` — Gets information about the current account
- L113-141 _public method_ `public async Task<ActionResult> UpdateCurrentAccountAsync(UpdateCurrentAccountRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/accounts/current")] [ProducesResponseType(200)] [ProducesResponseType(404)]` — Gets information about the current account
- L150-165 _public method_ `public async Task<ActionResult<object>> GetAccountAsync(AccountId id, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/accounts/{id}")] [ProducesResponseType(typeof(GetAccountResponse), 200)] [ProducesResponseType(404)]` — Gets information about an account by id
- L174-189 _public method_ `public async Task<ActionResult<object>> GetAccountEntitlementsAsync(AccountId id, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/accounts/{id}/entitlements")] [ProducesResponseType(typeof(GetAccountEntitlementsResponse), 200)] [ProducesResponseType(404)]` — Gets information about the current account
- L198-226 _public method_ `public async Task<ActionResult> UpdateAccountAsync(AccountId id, UpdateAccountRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/accounts/{id}")] [ProducesResponseType(200)] [ProducesResponseType(404)]` — Updates an account by id
- L234-243 _public method_ `public async Task<ActionResult> DeleteAccountAsync(AccountId id, CancellationToken cancellationToken = default)` — attrs: `[HttpDelete] [Route("/api/v1/accounts/{id}")] [ProducesResponseType(200)]` — Deletes an account by id
- L251-273 _public method_ `public async Task<ActionResult> CreateAdminAccountAsync(CreateAdminAccountRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [AllowAnonymous] [Route("/api/v1/accounts/admin/create")]` — Gets information about the current account
- L275-283 _private* method_ `static GetAccountResponse CreateGetAccountResponse(IAccount account)`

### `Source/Programs/Horde/HordeServer/Accounts/IAccount.cs` (HordeServer)


#### interface `HordeServer.Accounts.IAccount`  
`public interface IAccount`  
_public; L19-91_
- desc: An internal Horde account representing a user or service Service-to-service authentication always use this for authentication (for example, Robomerge accessing Horde) When external authentication is enabled (such as OpenID Connect) users cannot be authenticated through this.
- L24 _public* property_ `AccountId Id { get; }` — Unique internal ID for this Horde account
- L29 _public* property_ `string Name { get; }` — Full name of the user
- L34 _public* property_ `string Login { get; }` — A login ID or username
- L39 _public* property_ `string? Email { get; }` — Email associated with account
- L44 _public* property_ `string? PasswordHash { get; }` — Hashed password
- L49 _public* property_ `string? PasswordSalt { get; }` — Salt for password hash (if PasswordHash is set)
- L54 _public* property_ `bool Enabled { get; }` — If the account is active
- L59 _public* property_ `string Description { get; }` — Description of the account (who is it for, is there an owner etc)
- L65 _public* property_ `IReadOnlyList<IUserClaim> Claims { get; }` — Get list of claims
- L70 _public* property_ `string SessionKey { get; }` — Key for the current session. Refresh tokens are considered invalid when the session key no longer matches.
- L75 _public* method_ `bool ValidatePassword(string password)` — Validate that a password is correct for this account
- L82 _public* method_ `Task<IAccount?> RefreshAsync(CancellationToken cancellationToken = default)` — Get the latest version of this account
- L90 _public* method_ `Task<IAccount?> TryUpdateAsync(UpdateAccountOptions options, CancellationToken cancellationToken = default)` — Attempt to update settings for the account

#### record `HordeServer.Accounts.UpdateAccountOptions`  
`public record class UpdateAccountOptions( string? Name = null, string? Login = null, IReadOnlyList<IUserClaim>? Claims = null, string? Description = null, string? Email = null, string? Password = null, bool? Enabled = null, string? SessionKey = null)`  
_public; L104-104_
- desc: Options for updating an account

#### class `HordeServer.Accounts.AccountExtensions`  
`public static class AccountExtensions`  
_public; L117-169_
- desc: Extension methods for accounts
- L126-136 _public method_ `public static bool HasClaim(this IAccount account, string type, string value)` — Test whether a user has a particular claim
- L144 _public method_ `public static bool HasClaim(this IAccount account, AclClaimConfig claim)` — Test whether a user has a particular claim
- L154-168 _public method_ `public static async Task<IAccount?> UpdateAsync(this IAccount account, UpdateAccountOptions options, CancellationToken cancellationToken = default)` — Update settings for the account, retrying if the account object has changed

### `Source/Programs/Horde/HordeServer/Accounts/IAccountCollection.cs` (HordeServer)


#### interface `HordeServer.Accounts.IAccountCollection`  
`public interface IAccountCollection`  
_public; L14-63_
- desc: Interface for a collection of accounts
- L21 _public* method_ `Task<IAccount> CreateAsync(CreateAccountOptions options, CancellationToken cancellationToken = default)` — Adds a new account to the collection
- L30 _public* method_ `Task<IReadOnlyList<IAccount>> FindAsync(int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Searches service accounts
- L38 _public* method_ `Task<IAccount?> FindByLoginAsync(string login, CancellationToken cancellationToken = default)` — Get an account via login ID
- L46 _public* method_ `Task<IAccount?> GetAsync(AccountId id, CancellationToken cancellationToken = default)` — Get service account via ID
- L54 _public* method_ `Task DeleteAsync(AccountId id, CancellationToken cancellationToken = default)` — Delete a service account from the collection
- L62 _public* method_ `ValueTask CreateAdminAccountAsync(string password, CancellationToken cancellationToken)` — Creates the admin account when using Horde authentication

#### record `HordeServer.Accounts.CreateAccountOptions`  
`public record class CreateAccountOptions( string Name, string Login, IReadOnlyList<IUserClaim>? Claims = null, string? Description = null, string? Email = null, string? Password = null, bool? Enabled = null)`  
_public; L75-75_
- desc: Options for a new account

### `Source/Programs/Horde/HordeServer/Accounts/OAuthController.cs` (HordeServer)


#### class `HordeServer.Accounts.OAuthController`  
`public class OAuthController : Controller`  
_public; L34-563_
- attrs: `[ApiController] [Authorize] [ServiceFilter<OAuthControllerFilter>]`
- inherits: `Controller`
- desc: Controller for /api/v1/oauth2 endpoints
- L36 _private* field_ `readonly GlobalsService _globalsService`
- L37 _private* field_ `readonly IAccountCollection _accountCollection`
- L38 _private* field_ `readonly ServerSettings _serverSettings`
- L43-48 _public ctor_ `public OAuthController(GlobalsService globalsService, IAccountCollection accountCollection, IOptionsSnapshot<ServerSettings> serverSettings)` — Constructor
- L56-73 _public method_ `public ActionResult GetOpenIdConfiguration()` — attrs: `[HttpGet] [AllowAnonymous] [Route("/api/v1/oauth2/.well-known/openid-configuration")]` — Implements the OIDC discovery endpoint
- L81-103 _public method_ `public async Task<ActionResult> GetJwksAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [AllowAnonymous] [Route("/api/v1/oauth2/.well-known/jwks.json")]` — Query public signing keys for our JWTs
- L111-117 _public method_ `public ActionResult Authorize()` — attrs: `[HttpGet] [AllowAnonymous] [Route("/api/v1/oauth2/authorize")]` — Entry point for authorization. Displays the login page.
- L119-138 _private method_ `private static bool TryParseUrl(string candidate, out Uri uri)`
- L146-225 _public method_ `public async Task<ActionResult> LoginAsync(OAuthAuthorizeRequest request, [FromForm(Name = "username")] string? userName, [FromForm(Name = "password")] string? password, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [AllowAnonymous] [Route("/api/v1/oauth2/login")]` — Post interactive login credentials to the server in exchange for an authorization token
- L233-257 _public method_ `public async Task<ActionResult> LogoutAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/oauth2/logout")]` — Logs out of the current session
- L265-350 _public method_ `public async Task<ActionResult<OAuthGetTokenResponse>> ExchangeTokenAsync([FromForm] OAuthGetTokenRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [AllowAnonymous] [Route("/api/v1/oauth2/token")]` — Exchange a token for another token
- L352-370 _private* method_ `async Task<JwtPayload> ValidateTokenAsync(IGlobals globals, string? token)`
- L378-397 _public method_ `public async Task<ActionResult> GetUserInfoAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/oauth2/userinfo")]` — Get information about the logged in user
- L399-409 _private* method_ `static string? GetClaimOrDefault(JwtPayload payload, string claimType, string? claimDefault = null)`
- L411-419 _private* method_ `static bool TryParseAccountIdFromSubject(JwtPayload payload, out AccountId accountId)`
- L421-435 _private* method_ `static string ComputePkceVerifier(string? method, string code)`
- L440 _private* const_ `const string PurposeClaim = "purpose"`
- L441 _private* const_ `const string PkceCodeChallengeClaim = "pkce-code-challenge"`
- L442 _private* const_ `const string PkceCodeChallengeMethodClaim = "pkce-code-challenge-method"`
- L443 _private* const_ `const string SessionClaim = "session"`
- L444 _private* const_ `const string NonceClaim = "nonce"`
- L447 _private* const_ `const string AuthorizationCodePurpose = "auth"`
- L448 _private* const_ `const string AccessTokenPurpose = "access"`
- L449 _private* const_ `const string RefreshTokenPurpose = "refresh"`
- L450 _private* const_ `const string IdTokenPurpose = "id"`
- L453 _private* const_ `const string AccountSubjectPrefix = "account-id:"`
- L455-464 _private* method_ `string CreateAuthorizationToken(IGlobals globals, IAccount subject, string? pkceCode, string? pkceMethod, string? nonce)`
- L466-487 _private* method_ `string CreateAccessToken(IGlobals globals, IAccount subject, long expiresIn, string? nonce)`
- L489-493 _private* method_ `string CreateRefreshToken(IGlobals globals, IAccount subject, long expiresIn, string? nonce)`
- L495-502 _private* method_ `string CreateIdToken(IGlobals globals, IAccount subject, string? nonce)`
- L504-524 _private* method_ `static void GetUserInfoClaims(IAccount account, Dictionary<string, object> properties)`
- L526-529 _private* method_ `JwtPayload CreateJwtPayload(string purpose, IAccount subject, TimeSpan expiresIn, string? nonce)`
- L531-550 _private* method_ `JwtPayload CreateJwtPayload(string purpose, IAccount subject, long expiresIn, string? nonce)`
- L552-560 _private* method_ `static string CreateAndSignJwt(IGlobals globals, JwtPayload payload)`

#### class `HordeServer.Accounts.OAuthControllerFilter`  
`sealed class OAuthControllerFilter : ActionFilterAttribute`  
_internal*; L568-587_
- inherits: `ActionFilterAttribute`
- desc: Filters requests to the OAuth2 controller
- L570 _public property_ `public IOptionsSnapshot<ServerSettings> Settings { get; }`
- L572-575 _public ctor_ `public OAuthControllerFilter(IOptionsSnapshot<ServerSettings> settings)`
- L577-586 _public method_ `public override void OnActionExecuting(ActionExecutingContext context)`

### `Source/Programs/Horde/HordeServer/Accounts/OAuthMessages.cs` (HordeServer)


#### class `HordeServer.Accounts.OAuthAuthorizeRequest`  
`public class OAuthAuthorizeRequest`  
_public; L12-67_
- desc: Request to authorize a user using OAuth2
- L18 _public property_ `public string ClientId { get; set; }` — attrs: `[FromQuery(Name = "client_id")]` — Client identifier
- L24 _public property_ `public string RedirectUri { get; set; }` — attrs: `[FromQuery(Name = "redirect_uri")]` — Redirect URI that the response will be sent to
- L30 _public property_ `public string ResponseType { get; set; }` — attrs: `[FromQuery(Name = "response_type")]` — OAuth response type. Should be "code".
- L36 _public property_ `public string Scope { get; set; }` — attrs: `[FromQuery(Name = "scope")]` — Space separated list of the requested scope values. Should include openid.
- L42 _public property_ `public string? PkceCodeChallenge { get; set; }` — attrs: `[FromQuery(Name = "code_challenge")]` — PKCE code challenge.
- L48 _public property_ `public string? PkceCodeChallengeMethod { get; set; }` — attrs: `[FromQuery(Name = "code_challenge_method")]` — PKCE code challenge method. Should be "plain" or "S256".
- L54 _public property_ `public string ResponseMode { get; set; }` — attrs: `[FromQuery(Name = "response_mode")]` — Response method. Only "query" is supported by Horde.
- L60 _public property_ `public string? Nonce { get; set; }` — attrs: `[FromQuery(Name = "nonce")]` — Random string used to prevent replay attacks
- L66 _public property_ `public string? State { get; set; }` — attrs: `[FromQuery(Name = "state")]` — Optional application-defined state value.

#### class `HordeServer.Accounts.OAuthGetTokenRequest`  
`public class OAuthGetTokenRequest`  
_public; L72-103_
- desc: Response from a token exchange operation
- L78 _public property_ `public string? GrantType { get; set; }` — attrs: `[FromForm(Name = "grant_type")]` — Type of token being specified. Should be "authorization_code" or "refresh_token".
- L84 _public property_ `public string? AuthorizationToken { get; set; }` — attrs: `[FromForm(Name = "code")]` — Access token specified in the redirect.
- L90 _public property_ `public string? RefreshToken { get; set; }` — attrs: `[FromForm(Name = "refresh_token")]` — Refresh token specified in the redirect.
- L96 _public property_ `public string? RedirectUrl { get; set; }` — attrs: `[FromForm(Name = "redirect_url")]`
- L102 _public property_ `public string? PkceCodeVerifier { get; set; }` — attrs: `[FromForm(Name = "code_verifier")]` — Data that the PKCE code challenge was generated from

#### class `HordeServer.Accounts.OAuthGetTokenResponse`  
`public class OAuthGetTokenResponse`  
_public; L108-163_
- desc: Response from the OAuth2 token endpoint (https://datatracker.ietf.org/doc/html/rfc6749#section-5.1)
- L114 _public property_ `public string? AccessToken { get; set; }` — attrs: `[JsonPropertyName("access_token")]` — The access token return value
- L120 _public property_ `public string? TokenType { get; set; }` — attrs: `[JsonPropertyName("token_type")]` — Type of AccessToken. Typically "Bearer" for Horde responses.
- L126 _public property_ `public int? ExpiresIn { get; set; }` — attrs: `[JsonPropertyName("expires_in")]` — Expiry time in seconds for the access token
- L132 _public property_ `public string? Scope { get; set; }` — attrs: `[JsonPropertyName("scope")]`
- L138 _public property_ `public string? RefreshToken { get; set; }` — attrs: `[JsonPropertyName("refresh_token")]` — Refresh token
- L144 _public property_ `public int? RefreshTokenExpiresIn { get; set; }` — attrs: `[JsonPropertyName("refresh_token_expires_in")]` — TTL for the refresh token
- L150 _public property_ `public string? IdToken { get; set; }` — attrs: `[JsonPropertyName("id_token")]` — JWT with information about the authorized user
- L156 _public property_ `public string? Error { get; set; }` — attrs: `[JsonPropertyName("error")]` — Error code
- L162 _public property_ `public string? ErrorDescription { get; set; }` — attrs: `[JsonPropertyName("error_description")]` — The error description text

### `Source/Programs/Horde/HordeServer/Acls/AclService.cs` (HordeServer)


#### class `HordeServer.Acls.AclService`  
`public class AclService : IAclService`  
_public; L24-75_
- inherits: `IAclService`
- desc: Wraps functionality for manipulating permissions
- L26 _private field_ `private readonly GlobalsService _globalsService`
- L27 _private field_ `private readonly IOptionsMonitor<GlobalConfig> _globalConfig`
- L32-36 _public ctor_ `public AclService(GlobalsService globalsService, IOptionsMonitor<GlobalConfig> globalConfig)` — Constructor
- L45-52 _public method_ `public async ValueTask<string> IssueBearerTokenAsync(IEnumerable<Claim> claims, TimeSpan? expiry, CancellationToken cancellationToken = default)` — Issues a bearer token with the given claims
- L59-70 _public method_ `public static AgentId? GetAgentId(ClaimsPrincipal user)` — Gets the agent id associated with a particular user
- L73 _public method_ `public bool TryGetAclScope(AclScopeName scopeName, [NotNullWhen(true)] out AclConfig? scopeConfig)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Auditing/AuditLog.cs` (HordeServer)


#### class `HordeServer.Auditing.AuditLog`  
`class AuditLog<TSubject> : IAuditLog<TSubject>, IAsyncDisposable`  
_internal*; L20-293_
- inherits: `IAuditLog<TSubject>, IAsyncDisposable`
- L166 _private* field_ `readonly IMongoCollection<AuditLogMessage> _messages`
- L167 _private* field_ `readonly Channel<AuditLogMessage?> _messageChannel`
- L168 _private* field_ `readonly string _subjectProperty`
- L169 _private* field_ `readonly ILogger _logger`
- L170 _private* field_ `readonly BackgroundTask _backgroundTask`
- L172 _private* field_ `TaskCompletionSource? _flushEvent`
- L174 _public indexer_ `public IAuditLogChannel<TSubject> this[TSubject subject]`
- L176-188 _public ctor_ `public AuditLog(IMongoService mongoService, string collectionName, string subjectProperty, ILogger logger)`
- L190-194 _public method_ `public async ValueTask DisposeAsync()`
- L200-216 _internal method_ `internal async Task<int> FlushMessagesInternalAsync(CancellationToken cancellationToken)` — Flush any pending messages to database Exposed as internal for use in tests
- L218-239 _private* method_ `async Task WriteMessagesAsync(CancellationToken cancellationToken)`
- L241-252 _public method_ `public async Task FlushAsync(CancellationToken cancellationToken)`
- L254-276 _private* method_ `async IAsyncEnumerable<IAuditLogMessage<TSubject>> FindAsync(TSubject subject, DateTime? minTime = null, DateTime? maxTime = null, int? index = null, int? count = null, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L278-292 _private* method_ `async Task<long> DeleteAsync(TSubject subject, DateTime? minTime = null, DateTime? maxTime = null, CancellationToken cancellationToken = default)`

#### class `HordeServer.Auditing.AuditLog.AuditLogMessage`  
`class AuditLogMessage : IAuditLogMessage<TSubject>`  
_private*; L22-52_
- inherits: `IAuditLogMessage<TSubject>`
- L24 _public property_ `public ObjectId Id { get; set; }`
- L27 _public property_ `public TSubject Subject { get; set; }` — attrs: `[BsonElement("s")]`
- L30 _public property_ `public DateTime TimeUtc { get; set; }` — attrs: `[BsonElement("t")]`
- L33 _public property_ `public LogLevel Level { get; set; }` — attrs: `[BsonElement("l")]`
- L36 _public property_ `public string Data { get; set; }` — attrs: `[BsonElement("d")]`
- L38-42 _public ctor_ `public AuditLogMessage()`
- L44-51 _public ctor_ `public AuditLogMessage(TSubject subject, DateTime timeUtc, LogLevel level, string data)`

#### class `HordeServer.Auditing.AuditLog.AuditLogChannel`  
`class AuditLogChannel : IAuditLogChannel<TSubject>`  
_private*; L54-164_
- inherits: `IAuditLogChannel<TSubject>`
- L73 _public field_ `public readonly AuditLog<TSubject> Outer`
- L74 _public property_ `public TSubject Subject { get; }`
- L76 _private* field_ `readonly List<Scope> _scopes = new List<Scope>()`
- L78-82 _public ctor_ `public AuditLogChannel(AuditLog<TSubject> outer, TSubject subject)`
- L84 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull`
- L86 _public method_ `public bool IsEnabled(LogLevel logLevel)`
- L88-116 _private* method_ `LogEvent CreateEvent<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)`
- L118-137 _private* method_ `static void AppendMessage(LogEvent logEvent, int id, StringBuilder message, StringBuilder format, Dictionary<string, object?> properties)`
- L139-154 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)`
- L156 _public method_ `public IAsyncEnumerable<IAuditLogMessage> FindAsync(DateTime? minTime, DateTime? maxTime, int? index, int? count, CancellationToken cancellationToken = default)`
- L159 _public method_ `public Task<long> DeleteAsync(DateTime? minTime, DateTime? maxTime, CancellationToken cancellationToken = default)`
- L162 _public method_ `public Task FlushAsync(CancellationToken cancellationToken)`

#### class `HordeServer.Auditing.AuditLog.AuditLogChannel.Scope`  
`sealed class Scope : IDisposable`  
_private*; L56-71_
- inherits: `IDisposable`
- L58 _private* field_ `readonly AuditLogChannel _owner`
- L60 _public property_ `public LogEvent Message { get; }`
- L62-68 _public ctor_ `public Scope(AuditLogChannel owner, LogEvent message)`
- L70 _public method_ `public void Dispose()`

#### class `HordeServer.Auditing.AuditLogFactory`  
`class AuditLogFactory<TSubject> : IAuditLogFactory<TSubject>`  
_internal*; L295-310_
- inherits: `IAuditLogFactory<TSubject>`
- L297 _private* field_ `readonly IMongoService _mongoService`
- L298 _private* field_ `readonly ILogger<AuditLog<TSubject>> _logger`
- L300-304 _public ctor_ `public AuditLogFactory(IMongoService mongoService, ILogger<AuditLog<TSubject>> logger)`
- L306-309 _public method_ `public IAuditLog<TSubject> Create(string collectionName, string subjectProperty)`

### `Source/Programs/Horde/HordeServer/Authentication/AnonymousAuthHandler.cs` (HordeServer)


#### class `HordeServer.Authentication.AnonymousAuthenticationOptions`  
`class AnonymousAuthenticationOptions : AuthenticationSchemeOptions`  
_internal*; L16-18_
- inherits: `AuthenticationSchemeOptions`

#### class `HordeServer.Authentication.AnonymousAuthHandler`  
`class AnonymousAuthHandler : AuthenticationHandler<AnonymousAuthenticationOptions>`  
_internal*; L20-44_
- inherits: `AuthenticationHandler<AnonymousAuthenticationOptions>`
- L22 _public const_ `public const string AuthenticationScheme = "Anonymous"`
- L24-27 _public ctor_ `public AnonymousAuthHandler(IOptionsMonitor<AnonymousAuthenticationOptions> options, ILoggerFactory logger, UrlEncoder encoder) : base(options, logger, encoder)`
- L29-43 _protected method_ `protected override Task<AuthenticateResult> HandleAuthenticateAsync()`

#### class `HordeServer.Authentication.AnonymousExtensions`  
`static class AnonymousExtensions`  
_internal*; L46-52_
- L48-51 _public method_ `public static AuthenticationBuilder AddAnonymous(this AuthenticationBuilder builder, Action<AnonymousAuthenticationOptions> configure)`

### `Source/Programs/Horde/HordeServer/Authentication/ExternalJwtAuthHandler.cs` (HordeServer)


#### class `HordeServer.Authentication.ExternalJwtAuthHandler`  
`public class ExternalJwtAuthHandler`  
_public; L22-186_
- desc: JWT bearer handler capable of processing tokens generated by external OIDC providers (ie. access tokens issued by the OIDC server rather than the Horde server)
- L27 _public const_ `public const string AuthenticationScheme = "ExternalJwt"` — Default name of the authentication scheme
- L31 _private field_ `private readonly ConcurrentDictionary<string, IUser> _subToUser = ...`
- L31 _private field_ `private readonly ConcurrentDictionary< _subToUser = new()`
- L33 _private* field_ `readonly ServerSettings _settings`
- L38-41 _public ctor_ `public ExternalJwtAuthHandler(ServerSettings settings)` — Constructor
- L49-62 _private method_ `private Task OnMessageReceivedAsync(MessageReceivedContext context)` — Callback when JWT bearer request has been received Looks up and extracts the token from Authorization header. This cannot be done by the default JwtBearer handler as it can only handle "Bearer" prefix.
- L64-73 _private method_ `private Task OnAuthenticationFailedAsync(AuthenticationFailedContext context)`
- L80-135 _private method_ `private async Task OnTokenValidatedAsync(TokenValidatedContext context)` — Callback when JWT bearer token is being validated If user is not cached, it will look up additional info via /userinfo and cache it
- L137-143 _private method_ `private static void ReportError(ILogger logger, ResultContext<JwtBearerOptions> context, string message)`
- L149-170 _public method_ `public void AddHordeJwtBearerConfiguration(AuthenticationBuilder authBuilder)` — Registers this instance as a JWT handler

#### class `HordeServer.Authentication.ExternalJwtAuthHandler.StrictTokenHandler`  
`private class StrictTokenHandler : JwtSecurityTokenHandler`  
_private; L172-185_
- inherits: `JwtSecurityTokenHandler`
- L174-184 _public method_ `public override ClaimsPrincipal ValidateToken(string token, TokenValidationParameters validationParameters, out SecurityToken validatedToken)`

### `Source/Programs/Horde/HordeServer/Authentication/JwtAuthHandler.cs` (HordeServer)


#### class `HordeServer.Authentication.JwtAuthHandler`  
`class JwtAuthHandler : JwtBearerHandler, IAsyncDisposable`  
_internal*; L19-83_
- inherits: `JwtBearerHandler, IAsyncDisposable`
- desc: JWT handler for server-issued bearer tokens. These tokens are signed using a randomly generated key per DB instance.
- L24 _public const_ `public const string AuthenticationScheme = "ServerJwt"` — Default name of the authentication scheme
- L26 _private* field_ `readonly AsyncCachedValue<IGlobals> _globals`
- L28-32 _public ctor_ `public JwtAuthHandler(ILoggerFactory logger, UrlEncoder encoder, IOptionsMonitor<ServerSettings> settings, GlobalsService globalsService, IOptionsMonitorCache<JwtBearerOptions> optionsCache) : base(GetOptionsMonitor(settings.CurrentValue, optionsCache), logger, encoder)`
- L34-37 _public method_ `public async ValueTask DisposeAsync()`
- L39-47 _private method_ `private static IOptionsMonitor<JwtBearerOptions> GetOptionsMonitor(ServerSettings settings, IOptionsMonitorCache<JwtBearerOptions> optionsCache)`
- L49-82 _protected method_ `protected override async Task<AuthenticateResult> HandleAuthenticateAsync()`

### `Source/Programs/Horde/HordeServer/Authentication/OidcAuthHandler.cs` (HordeServer)


#### class `HordeServer.Authentication.OidcAuthHandler`  
`class OidcAuthHandler : OpenIdConnectHandler`  
_internal*; L22-119_
- inherits: `OpenIdConnectHandler`
- L24 _private* field_ `readonly IUserCollection _userCollection`
- L26-30 _public ctor_ `public OidcAuthHandler(IOptionsMonitor<OpenIdConnectOptions> options, ILoggerFactory logger, HtmlEncoder htmlEncoder, UrlEncoder encoder, IUserCollection userCollection) : base(options, logger, htmlEncoder, encoder)`
- L42-61 _private method_ `private static void MapUserInfoFieldToClaim(JsonElement userInfo, ClaimsIdentity identity, string claimName, string[] userInfoFields)` — Try to map a field found in user info as a claim If the claim is already set, it is skipped.
- L63-79 _public method_ `public static void AddUserInfoClaims(ServerSettings settings, JsonElement userInfo, ClaimsIdentity identity)`
- L81-90 _public method_ `public static void MapAdminClaim(ServerSettings settings, ClaimsIdentity identity)`
- L92-118 _protected method_ `protected override async Task<HandleRequestResult> HandleRemoteAuthenticateAsync()`

#### class `HordeServer.Authentication.OpenIdConnectHandlerExtensions`  
`static class OpenIdConnectHandlerExtensions`  
_internal*; L121-147_
- L130-140 _private* method_ `static void ApplyDefaultOptions(ServerSettings settings, OpenIdConnectOptions options, Action<OpenIdConnectOptions> handler)`
- L142-146 _public method_ `public static void AddHordeOpenId(this AuthenticationBuilder builder, ServerSettings settings, string authenticationScheme, string displayName, Action<OpenIdConnectOptions> handler)`

#### class `HordeServer.Authentication.OpenIdConnectHandlerExtensions.MapRolesClaimAction`  
`class MapRolesClaimAction : ClaimAction`  
_private*; L123-128_
- inherits: `ClaimAction`
- L125 _private field_ `private readonly ServerSettings _settings`
- L126 _public ctor_ `public MapRolesClaimAction(ServerSettings settings) : base(ClaimTypes.Role, ClaimTypes.Role)`
- L127 _public method_ `public override void Run(JsonElement userData, ClaimsIdentity identity, string issuer)`

### `Source/Programs/Horde/HordeServer/Authentication/OktaAuthHandler.cs` (HordeServer)


#### class `HordeServer.Authentication.OktaAuthHandler`  
`class OktaAuthHandler : OpenIdConnectHandler`  
_internal*; L22-109_
- inherits: `OpenIdConnectHandler`
- L24 _public const_ `public const string AuthenticationScheme = "Okta" + OpenIdConnectDefaults.AuthenticationScheme`
- L26 _private* field_ `readonly IUserCollection _userCollection`
- L28-32 _public ctor_ `public OktaAuthHandler(IOptionsMonitor<OpenIdConnectOptions> options, ILoggerFactory logger, HtmlEncoder htmlEncoder, UrlEncoder encoder, IUserCollection userCollection) : base(options, logger, htmlEncoder, encoder)`
- L34-80 _public method_ `public static void AddUserInfoClaims(JsonElement userInfo, ServerSettings settings, ClaimsIdentity identity)`
- L82-108 _protected method_ `protected override async Task<HandleRequestResult> HandleRemoteAuthenticateAsync()`

#### class `HordeServer.Authentication.OktaExtensions`  
`static class OktaExtensions`  
_internal*; L111-148_
- L129-141 _private* method_ `static void ApplyDefaultOktaOptions(OpenIdConnectOptions options, ServerSettings settings, Action<OpenIdConnectOptions> handler)`
- L143-147 _public method_ `public static void AddOkta(this AuthenticationBuilder builder, ServerSettings settings, string authenticationScheme, string displayName, Action<OpenIdConnectOptions> handler)`

#### class `HordeServer.Authentication.OktaExtensions.MapRolesClaimAction`  
`class MapRolesClaimAction : ClaimAction`  
_private*; L113-127_
- inherits: `ClaimAction`
- L115 _private* field_ `readonly ServerSettings _settings`
- L117-121 _public ctor_ `public MapRolesClaimAction(ServerSettings settings) : base(ClaimTypes.Role, ClaimTypes.Role)`
- L123-126 _public method_ `public override void Run(JsonElement userData, ClaimsIdentity identity, string issuer)`

### `Source/Programs/Horde/HordeServer/Authentication/ServiceAccountAuthHandler.cs` (HordeServer)


#### class `HordeServer.Authentication.ServiceAccountAuthOptions`  
`class ServiceAccountAuthOptions : AuthenticationSchemeOptions`  
_internal*; L18-20_
- inherits: `AuthenticationSchemeOptions`

#### class `HordeServer.Authentication.ServiceAccountAuthHandler`  
`class ServiceAccountAuthHandler : AuthenticationHandler<ServiceAccountAuthOptions>`  
_internal*; L22-73_
- inherits: `AuthenticationHandler<ServiceAccountAuthOptions>`
- L24 _public const_ `public const string AuthenticationScheme = "ServiceAccount"`
- L25 _public const_ `public const string Prefix = "ServiceAccount"`
- L27 _private field_ `private readonly IServiceAccountCollection _serviceAccountCollection`
- L29-34 _public ctor_ `public ServiceAccountAuthHandler(IOptionsMonitor<ServiceAccountAuthOptions> options, ILoggerFactory logger, UrlEncoder encoder, IServiceAccountCollection serviceAccountCollection) : base(options, logger, encoder)`
- L36-72 _protected method_ `protected override async Task<AuthenticateResult> HandleAuthenticateAsync()`

#### class `HordeServer.Authentication.ServiceAccountAuthExtensions`  
`static class ServiceAccountAuthExtensions`  
_internal*; L75-81_
- L77-80 _public method_ `public static AuthenticationBuilder AddServiceAccounts(this AuthenticationBuilder builder, Action<ServiceAccountAuthOptions> config)`

### `Source/Programs/Horde/HordeServer/Commands/Generate/ConfigDocsCommand.cs` (HordeServer)


#### class `HordeServer.Commands.Generate.DocsCommand`  
`class DocsCommand : Command`  
_internal*; L22-410_
- attrs: `[Command("generate", "configdocs", "Writes Markdown docs for server settings")]`
- inherits: `Command`
- L26 _public property_ `public DirectoryReference OutputDir { get; set; }` — attrs: `[CommandLine] [Description("Output directory for generated markdown files")]`
- L30 _public property_ `public FileReference? Agent { get; set; }` — attrs: `[CommandLine] [Description("Path to the agent executable, for gathering agent settings.")]`
- L34 _private* field_ `readonly IPluginCollection _pluginCollection`
- L36 _public ctor_ `public DocsCommand(IPluginCollection pluginCollection)`
- L39-77 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L103-181 _private* method_ `async Task WriteDocAsync(JsonSchemaType rootType, string title, string fileName, string linkRail, string? introduction, Dictionary<string, string> typeNameToLink, ILogger logger)`
- L183-224 _private* method_ `static void FindCustomTypes(JsonSchemaType type, List<JsonSchemaType> types, HashSet<string> visitedTypeNames)`
- L226-276 _private* method_ `static string GetMarkdownType(JsonSchemaType type, Dictionary<string, string> typeNameToLink)`
- L278-281 _private* method_ `static string GetMarkdownDescription(string? description)`
- L283-297 _private* method_ `static string GetHeadingName(JsonSchemaType type)`
- L299-310 _private* method_ `static string GetLink(JsonSchemaType type, Dictionary<string, string> typeNameToLink)`
- L313-318 _private* method_ `static string GetAnchorName(JsonSchemaType type)` — attrs: `[SuppressMessage("Globalization", "CA1308:Normalize strings to uppercase")]`
- L320-409 _private* method_ `async Task WriteAclDocAsync(IEnumerable<Assembly> assemblies, ILogger logger)`

#### record `HordeServer.Commands.Generate.DocsCommand.PageInfo`  
`record class PageInfo(string Title, string LinkRail, string FileName, string? Introduction = null)`  
_private*; L32-32_

#### class `HordeServer.Commands.Generate.DocsCommand.ObjectQueue`  
`class ObjectQueue`  
_private*; L79-101_
- L81 _private* field_ `readonly Stack<JsonSchemaType> _stack = new Stack<JsonSchemaType>()`
- L82 _private* field_ `readonly HashSet<string> _visited = new HashSet<string>(StringComparer.Ordinal)`
- L84-90 _public method_ `public void Add(JsonSchemaType type)`
- L92-98 _public method_ `public void Ignore(JsonSchemaType type)`
- L100 _public method_ `public bool TryPop([NotNullWhen(true)] out JsonSchemaType? obj)`

### `Source/Programs/Horde/HordeServer/Commands/Generate/ConfigSchemasCommand.cs` (HordeServer)


#### class `HordeServer.Commands.Generate.SchemasCommand`  
`class SchemasCommand : Command`  
_internal*; L15-41_
- attrs: `[Command("generate", "configschemas", "Writes JSON schemas for server settings")]`
- inherits: `Command`
- L19 _private* field_ `DirectoryReference? _outputDir = null!` — attrs: `[CommandLine("-OutputDir=")] [Description("Output directory to write schemas to. Defaults to the 'Schemas' subfolder of the application directory.")]`
- L21 _private* field_ `readonly IPluginCollection _pluginCollection`
- L23 _public ctor_ `public SchemasCommand(IPluginCollection pluginCollection)`
- L26-40 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeServer/Commands/Generate/CppApiCommand.cs` (HordeServer)


#### class `HordeServer.Commands.Generate.CppApiCommand`  
`class CppApiCommand : Command`  
_internal*; L22-292_
- attrs: `[Command("generate", "cppapi", "Outputs C++ source files describing the Horde API")]`
- inherits: `Command`
- L28 _private* field_ `static readonly string[] s_boilerplateLines = new[] { "// ---------------------------------------------------------------------------------------------------", "// This file is autogenerated by the Horde Server 'generate cppapi' command. Do not m ...`
- L38 _public property_ `public DirectoryReference? OutputDir { get; set; }` — attrs: `[CommandLine("-OutputDir=")] [Description("Specifies the output directory for generated files.")]`
- L40 _private* field_ `readonly IPluginCollection _pluginCollection`
- L42-45 _public ctor_ `public CppApiCommand(IPluginCollection pluginCollection)`
- L47-115 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)`
- L117 _private* field_ `static readonly Dictionary<Type, string> s_knownCppTypes = ...`
- L117 _private* field_ `static readonly Dictionary< s_knownCppTypes = new Dictionary<Type, string> { { typeof(bool), "bool" }, { typeof(int), "int32" }, { typeof(string), "FString" }, { typeof(StringId), "FString" }, }`
- L125-160 _public method_ `public static string GetCppType(Type type)`
- L162-194 _private* method_ `static void FindTypesFromController(Type controllerType, HashSet<Type> apiTypes)`
- L196-214 _private* method_ `static List<ApiTypeInfo> FindApiTypes(List<Type> types, XmlDocReader xmlDocReader)`
- L216-221 _private* method_ `static StreamWriter OpenOutputFile(FileReference outputFile, ILogger logger)`
- L223-229 _private* method_ `static void WriteBoilerplate(StreamWriter writer)`
- L231-261 _private* method_ `static void WriteHeader(FileReference outputFile, List<ApiTypeInfo> apiTypes, ILogger logger)`
- L263-291 _private* method_ `static void WriteSource(FileReference outputFile, List<ApiTypeInfo> apiTypes, ILogger logger)`

#### record `HordeServer.Commands.Generate.CppApiCommand.ApiPropertyInfo`  
`record class ApiPropertyInfo(string Name, Type Type, string Description)`  
_private*; L24-24_

#### record `HordeServer.Commands.Generate.CppApiCommand.ApiTypeInfo`  
`record class ApiTypeInfo(string Name, Type Type, string Description, List<ApiPropertyInfo> Properties)`  
_private*; L25-25_

#### record `HordeServer.Commands.Generate.CppApiCommand.ApiGroupInfo`  
`record class ApiGroupInfo(string Name, Dictionary<Type, ApiTypeInfo> Types)`  
_private*; L26-26_

### `Source/Programs/Horde/HordeServer/Commands/MongoCommands.cs` (HordeServer)


#### class `HordeServer.Commands.MongoUpgradeCommand`  
`class MongoUpgradeCommand(IConfiguration config) : Command`  
_internal*; L17-39_
- attrs: `[Command("mongo", "upgrade", "Upgrade database schema(s) by applying migration scripts")]`
- L20-38 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

#### class `HordeServer.Commands.MongoValidateCommand`  
`class MongoValidateCommand(IConfiguration config) : Command`  
_internal*; L42-75_
- attrs: `[Command("mongo", "validate", "Validate database schema versions")]`
- L45-74 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Commands/OpenCommand.cs` (HordeServer)


#### class `HordeServer.Commands.OpenCommand`  
`public class OpenCommand : Command`  
_public; L15-36_
- attrs: `[Command("open", "Open web browser to the server homepage")]`
- inherits: `Command`
- desc: Opens a web browser to the server homepage
- L17 _private* field_ `readonly IOptions<ServerSettings> _settings`
- L22-25 _public ctor_ `public OpenCommand(IOptions<ServerSettings> settings)` — Constructor
- L28-35 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Commands/ServerCommand.cs` (HordeServer)


#### class `HordeServer.Commands.ServerCommand`  
`class ServerCommand : Command`  
_internal*; L28-269_
- attrs: `[Command("server", "Runs the Horde Build server (default)")]`
- inherits: `Command`
- L30 _private* field_ `readonly ServerSettings _hordeSettings`
- L31 _private* field_ `readonly IConfiguration _config`
- L32 _private* field_ `string[] _args = Array.Empty<string>()`
- L34-38 _public ctor_ `public ServerCommand(ServerSettings settings, IConfiguration config)`
- L41-45 _public method_ `public override void Configure(CommandLineArguments arguments, ILogger logger)` — (inheritdoc)
- L48-71 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)
- L73-159 _private* method_ `static IHostBuilder CreateHostBuilderWithCert(string[] args, IConfiguration config, ServerSettings serverSettings, X509Certificate2? sslCert)`
- L213-254 _public method_ `public static X509Certificate2? ReadGrpcCertificate(ServerSettings hordeSettings)` — Gets the certificate to use for Grpc endpoints
- L256-260 _public method_ `public static IHostBuilder CreateHostBuilderForTesting(string[] args)`
- L262-268 _public method_ `public static IHostBuilder CreateMinimalHostBuilder(IConfiguration config)`

#### class `HordeServer.Commands.ServerCommand.CustomWindowsServiceLifetime`  
`sealed class CustomWindowsServiceLifetime : WindowsServiceLifetime, IHostLifetime`  
_private*; L163-207_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `WindowsServiceLifetime, IHostLifetime`
- L165 _private* field_ `readonly IHostApplicationLifetime _applicationLifetime`
- L166 _private* field_ `readonly ManualResetEventSlim _applicationStarted = new ManualResetEventSlim(false)`
- L167 _private* field_ `readonly TaskCompletionSource _serviceStarting = new TaskCompletionSource(TaskCreationOptions.RunContinuationsAsynchronously)`
- L168 _private* field_ `readonly ILogger _logger`
- L170-177 _public ctor_ `public CustomWindowsServiceLifetime(IHostEnvironment environment, IHostApplicationLifetime applicationLifetime, ILoggerFactory loggerFactory, IOptions<HostOptions> optionsAccessor) : base(environment, applicationLifetime, loggerFactory, optionsAccessor)`
- L179-187 _protected method_ `protected override void Dispose(bool disposing)`
- L189-193 _public method_ `public new async Task WaitForStartAsync(CancellationToken cancellationToken)`
- L195-206 _protected method_ `protected override void OnStart(string[] args)`

### `Source/Programs/Horde/HordeServer/Commands/Utility/SurgeryCommand.cs` (HordeServer)


#### class `HordeServer.Commands.SurgeryCommand`  
`public class SurgeryCommand : Command`  
_public; L17-53_
- attrs: `[Command("surgery", "Placeholder command to allow DB surgery", Advertise = false)]`
- inherits: `Command`
- desc: Scaffolding to construct a DB instance for scoped DB modifications
- L19 _private* field_ `readonly IOptions<ServerSettings> _settings`
- L24-27 _public ctor_ `public SurgeryCommand(IOptions<ServerSettings> settings)` — Constructor
- L30-42 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)
- L44-52 _private* method_ `async Task RunAsync(IMongoDatabase database, ILogger logger)`

### `Source/Programs/Horde/HordeServer/Configuration/ConfigService.cs` (HordeServer)


#### class `HordeServer.Configuration.ConfigService`  
`public sealed class ConfigService : IConfigService, IOptionsFactory<GlobalConfig>, IOptionsChangeTokenSource<GlobalConfig>, IHostedService, IAsyncDisposable`  
_public; L42-1061_
- inherits: `IConfigService, IOptionsFactory<GlobalConfig>, IOptionsChangeTokenSource<GlobalConfig>, IHostedService, IAsyncDisposable`
- desc: Service which processes runtime configuration data.
- L121 _private* field_ `readonly IRedisService _redisService`
- L122 _private* field_ `readonly ServerSettings _serverSettings`
- L123 _private* field_ `readonly Dictionary<string, IConfigSource> _sources`
- L123 _private* field_ `readonly Dictionary< _sources`
- L124 _private* field_ `readonly IPluginCollection _pluginCollection`
- L125 _private* field_ `readonly JsonSerializerOptions _jsonOptions`
- L126 _private* field_ `readonly RedisKey _snapshotKey = "config-v2"`
- L127 _private* field_ `readonly IEnumerable<IDefaultAclModifier> _defaultAclModifiers`
- L128 _private* field_ `readonly IHealthMonitor _health`
- L129 _private* field_ `readonly ILogger _logger`
- L131 _private* field_ `readonly ITicker _ticker`
- L132 _private* field_ `readonly TimeSpan _tickInterval = TimeSpan.FromMinutes(1.0)`
- L134 _private* field_ `readonly RedisChannel _updateChannel = RedisChannel.Literal("config-update-v2")`
- L135 _private* field_ `readonly BackgroundTask _updateTask`
- L137 _private* field_ `Task<ConfigState> _stateTask`
- L138 _private* field_ `readonly ChangeToken _changeToken = new ChangeToken()`
- L140 _private* field_ `readonly IServiceProvider _serviceProvider`
- L143 _private* property_ `string IOptionsChangeTokenSource<GlobalConfig>.Name => ...` — (inheritdoc)
- L148 _public event_ `public event Action<ConfigUpdateInfo>? OnConfigUpdate` — Event for notifications that the config has been updated
- L153-183 _public ctor_ `public ConfigService(IRedisService redisService, IOptions<ServerSettings> serverSettings, IEnumerable<IConfigSource> sources, IPluginCollection pluginCollection, IEnumerable<IDefaultAclModifier> aclModifiers, IClock clock, IHealthMonitor<ConfigService> health, ILogger<ConfigService> logger, IServiceProvider serviceProvider)` — Constructor
- L186-191 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L196-200 _public method_ `public async Task<GlobalConfig> WaitForInitialConfigAsync(CancellationToken cancellationToken = default)` — Wait for the initial config state to be read.
- L265-270 _private* method_ `ConfigContext CreateConfigContext(IReadOnlyDictionary<string, IConfigSource> sources, ILogger logger)`
- L272-288 _private* method_ `(Dictionary<Uri, OverrideConfigFile> OverrideFiles, ConfigContext Context) CreateOverrideContext(Dictionary<Uri, byte[]> files)`
- L290-296 _private* method_ `async Task<GlobalConfig> ReadAndPostLoadOverridesAsync(ConfigContext context, CancellationToken cancellationToken)`
- L298-313 _private* method_ `string FormatConfigException(Exception ex, ConfigContext context, string logMessage)`
- L318-339 _public method_ `public async Task<ConfigValidationResult> ValidateAsync(Dictionary<Uri, byte[]> files, CancellationToken cancellationToken)` — Validate a new set of config files. Parses and runs PostLoad methods on them.
- L342-365 _public method_ `public async Task<ConfigResolveResult> ResolveWithOverridesAsync(Dictionary<Uri, byte[]> files, CancellationToken cancellationToken)` — (inheritdoc)
- L368-378 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L381-388 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L394-397 _public method_ `public void OverrideConfig(GlobalConfig globalConfig)` — Accessor for tests to update the global config
- L404-411 _private* method_ `void Set(IoHash hash, GlobalConfig globalConfig)` — Updates the current config
- L414-419 _public method_ `public GlobalConfig Create(string name)` — (inheritdoc)
- L422 _public method_ `public IChangeToken GetChangeToken()` — (inheritdoc)
- L424-457 _private* method_ `async Task<ConfigState> GetStartupStateAsync()`
- L459-495 _private* method_ `async ValueTask TickSharedAsync(CancellationToken cancellationToken)`
- L497-525 _private* method_ `async Task WaitForUpdatesAsync(CancellationToken cancellationToken)`
- L533-549 _private* method_ `async Task<ConfigSnapshot?> CreateSnapshotGuardedAsync(IReadOnlyDictionary<Uri, string>? prevFiles, CancellationToken cancellationToken)` — Create a new snapshot object, catching any exceptions and sending notifications
- L551-559 _private* method_ `async Task NotifyConfigUpdateAsync(IReadOnlyDictionary<Uri, string> files, IReadOnlyDictionary<Uri, string>? prevFiles, Exception? exception, CancellationToken cancellationToken)`
- L561-564 _internal method_ `internal Uri GetGlobalConfigUri()`
- L569-586 _internal method_ `internal static Uri GetGlobalConfigUri(string configPath, string defaultConfigDir)` — Gets the path to the root config file
- L591-606 _private* method_ `TimeSpan GetConfigUpdateInterval(ConfigSnapshot? snapshot)` — Get the appropriate update interval for checking of new config updates
- L611-621 _private* method_ `IEnumerable<Uri> GetConfigSourceUris(ConfigSnapshot? snapshot)` — Enumerates all the known URIs for reading the given config snapshot.
- L628-673 _private* method_ `async Task<ConfigSnapshot> CreateSnapshotAsync(CancellationToken cancellationToken)` — Create a new snapshot object
- L675-714 _private* method_ `async Task<GlobalConfig> ReadGlobalConfigAsync(ConfigContext context, CancellationToken cancellationToken)`
- L716 _private* field_ `static readonly KeyValuePair<string, string>[] s_remapConfigValues = ...`
- L716 _private* field_ `static readonly KeyValuePair< s_remapConfigValues = new[] { KeyValuePair.Create("TelemetryStores", "Plugins.Analytics.Stores"), KeyValuePair.Create("PerforceClusters", "Plugins.Build.PerforceClusters"), KeyValuePair.Create("Devices", "Plugins.Build.Dev ...`
- L747-779 _private* method_ `static void CopyJsonNode(JsonObject rootObj, string sourcePath, string targetPath)`
- L781-784 _internal method_ `internal byte[] Serialize(GlobalConfig config)`
- L786-792 _internal method_ `internal GlobalConfig? Deserialize(byte[] data, bool withData)`
- L799-802 _private* method_ `static object GetSnapshotInfo(ReadOnlySpan<byte> span, ConfigSnapshot snapshot)` — Writes information about the current snapshot to the logger
- L810-851 _private* method_ `async Task<bool> IsOutOfDateAsync(ConfigSnapshot snapshot, CancellationToken cancellationToken)` — Checks if the given snapshot is out of date
- L853-862 _private* method_ `async Task WriteSnapshotAsync(ConfigSnapshot snapshot)`
- L864-868 _private* method_ `async Task<ReadOnlyMemory<byte>> ReadSnapshotDataAsync()`
- L870-879 _private* method_ `static ReadOnlyMemory<byte> SerializeSnapshot(ConfigSnapshot snapshot)`
- L881-888 _private* method_ `static ConfigSnapshot DeserializeSnapshot(ReadOnlyMemory<byte> data)`
- L890-902 _private* method_ `async Task UpdateConfigObjectAsync(ReadOnlyMemory<byte> data)`
- L904-919 _private* method_ `async Task<GlobalConfig> CreateGlobalConfigAsync(ReadOnlyMemory<byte> data, CancellationToken cancellationToken = default)`
- L933-997 _public method_ `public async Task ResolveConfigSecretsAsync(GlobalConfig config, CancellationToken cancellationToken)` — Convert string representations of secrets to concrete values in the config
- L999-1060 _private* method_ `static List<KeyValuePair<object, PropertyInfo>> GetPropertiesWithAttribute<T, TAttribute>(object obj) where TAttribute : Attribute`

#### class `HordeServer.Configuration.ConfigService.ConfigSnapshot`  
`class ConfigSnapshot`  
_private*; L46-56_
- attrs: `[ProtoContract]`
- L49 _public property_ `public byte[] Data { get; set; }` — attrs: `[ProtoMember(1)]`
- L52 _public property_ `public Dictionary<Uri, string> Dependencies { get; set; }` — attrs: `[ProtoMember(4)]`
- L55 _public property_ `public string ServerVersion { get; set; }` — attrs: `[ProtoMember(5)]`

#### class `HordeServer.Configuration.ConfigService.ChangeToken`  
`class ChangeToken : IChangeToken`  
_private*; L59-116_
- inherits: `IChangeToken`
- L90 _private* field_ `readonly List<Registration> _registrations = new List<Registration>()`
- L92 _public property_ `public bool ActiveChangeCallbacks => ...`
- L93 _public property_ `public bool HasChanged { get; set; }`
- L95-110 _public method_ `public void TriggerChange()`
- L112-115 _public method_ `public IDisposable RegisterChangeCallback(Action<object?> callback, object? state)`

#### class `HordeServer.Configuration.ConfigService.ChangeToken.Registration`  
`class Registration : IDisposable`  
_private*; L61-88_
- inherits: `IDisposable`
- L63 _private* field_ `readonly List<Registration> _registrations`
- L64 _private* field_ `readonly Action<object?> _callback`
- L65 _private* field_ `readonly object? _state`
- L67-77 _public ctor_ `public Registration(List<Registration> registrations, Action<object?> callback, object? state)`
- L79-85 _public method_ `public void Dispose()`
- L87 _public method_ `public void Trigger()`

#### record `HordeServer.Configuration.ConfigService.ConfigState`  
`record class ConfigState(IoHash Hash, GlobalConfig GlobalConfig)`  
_private*; L119-119_

#### class `HordeServer.Configuration.ConfigService.OverrideConfigFile`  
`class OverrideConfigFile : IConfigFile`  
_private*; L202-222_
- inherits: `IConfigFile`
- L204 _private* field_ `readonly byte[] _data`
- L206 _public property_ `public Uri Uri { get; }`
- L207 _public property_ `public string Revision => ...`
- L208 _public property_ `public IUser? Author => ...`
- L209 _public property_ `public bool WasRead { get; set; }`
- L211-215 _public ctor_ `public OverrideConfigFile(Uri uri, byte[] data)`
- L217-221 _public method_ `public ValueTask<ReadOnlyMemory<byte>> ReadAsync(CancellationToken cancellationToken)`

#### class `HordeServer.Configuration.ConfigService.OverrideConfigSource`  
`class OverrideConfigSource : IConfigSource`  
_private*; L224-263_
- inherits: `IConfigSource`
- L226 _private* field_ `readonly IConfigSource _inner`
- L227 _private* field_ `readonly Dictionary<Uri, OverrideConfigFile> _overrides`
- L227 _private* field_ `readonly Dictionary< _overrides`
- L229 _public property_ `public string Scheme => ...`
- L231 _public property_ `public TimeSpan UpdateInterval => ...`
- L233-237 _public ctor_ `public OverrideConfigSource(IConfigSource inner, Dictionary<Uri, OverrideConfigFile> overrides)`
- L239 _public method_ `public void Add(OverrideConfigFile file)`
- L241-258 _public method_ `public async Task<IConfigFile[]> GetFilesAsync(Uri[] uris, CancellationToken cancellationToken)`
- L261 _public method_ `public Task GetUpdateInfoAsync(IReadOnlyDictionary<Uri, string> files, IReadOnlyDictionary<Uri, string>? prevFiles, ConfigUpdateInfo updateInfo, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.ConfigService.SecretReplacementInfo`  
`class SecretReplacementInfo`  
_private*; L921-926_
- L923 _public property_ `public required string SecretName { get; init; }`
- L924 _public property_ `public required object SourceObject { get; init; }`
- L925 _public property_ `public required PropertyInfo Property { get; init; }`

### `Source/Programs/Horde/HordeServer/Dashboard/DashboardConfig.cs` (HordeServer)


#### class `HordeServer.Dashboard.DashboardConfig`  
`public class DashboardConfig`  
_public; L20-82_
- attrs: `[JsonSchema("https://unrealengine.com/horde/dashboard")] [JsonSchemaCatalog("Horde Dashboard", "Horde dashboard configuration file", new[] { "*.dashboard.json", "Dashboard/*.json" })] [ConfigDoc("*.dashboard.json", "[Horde](../../../README.md) > [Configuration](../../Config.md)", "Config/Schema/Dashboard.md")] [ConfigIncludeRoot] [ConfigMacroScope]`
- desc: Configuration for dashboard features
- L25 _public property_ `public bool ShowLandingPage { get; set; }` — Navigate to the landing page by default
- L30 _public property_ `public string LandingPageRoute { get; set; }` — Custom landing page route to direct users to
- L35 _public property_ `public bool ShowCI { get; set; }` — Enable CI functionality
- L40 _public property_ `public bool ShowAgents { get; set; }` — Whether to show functionality related to agents, pools, and utilization on the dashboard.
- L45 _public property_ `public bool ShowAgentRegistration { get; set; }` — Whether to show the agent registration page. When using registration tokens from elsewhere this is not needed.
- L50 _public property_ `public bool ShowPerforceServers { get; set; }` — Show the Perforce server option on the server menu
- L55 _public property_ `public bool ShowDeviceManager { get; set; }` — Show the device manager on the server menu
- L60 _public property_ `public bool ShowTests { get; set; }` — Show automated tests (legacy) on the server menu
- L65 _public property_ `public List<DashboardAgentCategoryConfig> AgentCategories { get; set; }` — Configuration for different agent pages
- L70 _public property_ `public List<DashboardPoolCategoryConfig> PoolCategories { get; set; }` — Configuration for different pool pages
- L75 _public property_ `public List<ConfigInclude> Include { get; set; }` — Includes for other configuration files
- L80 _public property_ `public List<ConfigMacro> Macros { get; set; }` — Macros within this configuration

#### class `HordeServer.Dashboard.DashboardAgentCategoryConfig`  
`public class DashboardAgentCategoryConfig`  
_public; L87-98_
- desc: Configuration for a category of agents
- L92 _public property_ `public string Name { get; set; }` — Name of the category
- L97 _public property_ `public Condition? Condition { get; set; }` — Condition string to be evaluated for this page

#### class `HordeServer.Dashboard.DashboardPoolCategoryConfig`  
`public class DashboardPoolCategoryConfig`  
_public; L103-114_
- desc: Configuration for a category of pools
- L108 _public property_ `public string Name { get; set; }` — Name of the category
- L113 _public property_ `public Condition? Condition { get; set; }` — Condition string to be evaluated for this page

### `Source/Programs/Horde/HordeServer/Dashboard/DashboardController.cs` (HordeServer)


#### class `HordeServer.Dashboard.DashboardController`  
`public class DashboardController : Controller`  
_public; L29-272_
- attrs: `[ApiController] [Route("[controller]")]`
- inherits: `Controller`
- desc: Dashboard authorization challenge controller
- L31 _private* field_ `readonly string _authenticationScheme`
- L32 _private* field_ `readonly ServerSettings _settings`
- L33 _private* field_ `readonly IDashboardPreviewCollection _previewCollection`
- L34 _private* field_ `readonly IAccountCollection _hordeAccounts`
- L35 _private* field_ `readonly IEnumerable<IPluginResponseFilter> _responseFilters`
- L36 _private* field_ `readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L41-49 _public ctor_ `public DashboardController(IDashboardPreviewCollection previewCollection, IAccountCollection hordeAccounts, IEnumerable<IPluginResponseFilter> responseFilters, IOptionsMonitor<ServerSettings> serverSettings, IOptionsSnapshot<GlobalConfig> globalConfig)` — Constructor
- L57-70 _public method_ `public async Task<IActionResult> GetChallengeAsync()` — attrs: `[HttpGet] [Route("/api/v1/dashboard/challenge")]` — Challenge endpoint for the dashboard, using cookie authentication scheme
- L79-82 _public method_ `public IActionResult Login([FromQuery] string? redirect)` — attrs: `[HttpGet] [Route("/api/v1/dashboard/login")]` — Login to server, redirecting to the specified URL on success
- L91-107 _public method_ `public IActionResult LoginV2([FromQuery] string? redirect)` — attrs: `[HttpGet] [Route("/api/v2/dashboard/login")]` — Login to server, redirecting to the specified Base64 encoded URL, which fixes some escaping issues on some auth providers, on success
- L116-133 _public method_ `public async Task<ActionResult> LogoutAsync([FromQuery] bool? dashboard)` — attrs: `[HttpGet] [Route("/api/v1/dashboard/logout")]` — Logout of the current account
- L142-173 _public method_ `public ActionResult<GetDashboardConfigResponse> GetDashbordConfig()` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/dashboard/config")]` — Query all the projects
- L182-203 _public method_ `public async Task<ActionResult<GetDashboardPreviewResponse>> CreateDashbordPreviewAsync([FromBody] CreateDashboardPreviewRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Authorize] [Route("/api/v1/dashboard/preview")]` — Create a new dashboard preview item
- L212-227 _public method_ `public async Task<ActionResult<GetDashboardPreviewResponse>> UpdateDashbordPreviewAsync([FromBody] UpdateDashboardPreviewRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Authorize] [Route("/api/v1/dashboard/preview")]` — Update a dashboard preview item
- L236-240 _public method_ `public async Task<ActionResult<List<GetDashboardPreviewResponse>>> GetDashbordPreviewsAsync([FromQuery] bool open = true, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/dashboard/previews")]` — Query dashboard preview items
- L242-254 _private* method_ `static GetDashboardPreviewResponse CreatePreviewResponse(IDashboardPreview preview)`
- L263-271 _public method_ `public ActionResult<List<AccountClaimMessage>> GetAccountGroupClaims()` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/dashboard/accountgroups")]` — Returns a list of valid user-defined groups from the current server config. These are any claims with the HordeClaimTypes.Group type.

### `Source/Programs/Horde/HordeServer/Dashboard/DashboardPreviewCollection.cs` (HordeServer)


#### interface `HordeServer.Dashboard.IDashboardPreview`  
`public interface IDashboardPreview`  
_public; L19-60_
- L24 _public property_ `public int Id { get; }` — The unique ID of the preview item
- L29 _public property_ `public DateTime CreatedAt { get; }` — When the preview item was created
- L34 _public property_ `public string Summary { get; }` — A summary of what the preview item changes
- L39 _public property_ `public int? DeployedCL { get; }` — The CL the preview was deployed in
- L44 _public property_ `public bool Open { get; }` — Whather the preview is under consideration, if false the preview item didn't pass muster
- L49 _public property_ `public string? ExampleLink { get; }` — An example of the preview site users can view the changes
- L54 _public property_ `public string? DiscussionLink { get; }` — Optional Link for discussion the preview item
- L59 _public property_ `public string? TrackingLink { get; }` — Optional Link for discussing the preview item

#### interface `HordeServer.Dashboard.IDashboardPreviewCollection`  
`public interface IDashboardPreviewCollection`  
_public; L65-97_
- desc: Collection of preview documents
- L74 _public* method_ `Task<IDashboardPreview> AddPreviewAsync(string summary, CancellationToken cancellationToken)` — Add a preview item
- L88 _public* method_ `Task<IDashboardPreview?> UpdatePreviewAsync(int previewId, string? summary = null, int? deployedCL = null, bool? open = null, string? exampleLink = null, string? discussionLink = null, string? trackingLink = null, CancellationToken cancellationToken = default)` — Update a dashboard preview item
- L96 _public* method_ `Task<List<IDashboardPreview>> FindPreviewsAsync(bool? open = null, CancellationToken cancellationToken = default)` — Finds preview items with the given criterial

#### class `HordeServer.Dashboard.DashboardPreviewCollection`  
`internal class DashboardPreviewCollection : IDashboardPreviewCollection`  
_internal; L99-233_
- inherits: `IDashboardPreviewCollection`
- L145 _private* field_ `readonly IMongoCollection<PreviewDocument> _previews`
- L146 _private* field_ `readonly ISingletonDocument<PreviewLedger> _ledgerSingleton`
- L148-152 _public ctor_ `public DashboardPreviewCollection(IMongoService mongoService)`
- L154-162 _public method_ `public async Task<IDashboardPreview> AddPreviewAsync(string summary, CancellationToken cancellationToken)`
- L164-172 _public method_ `public async Task<IDashboardPreview> UpdatePreviewAsync(string summary, CancellationToken cancellationToken)`
- L174-220 _public method_ `public async Task<IDashboardPreview?> UpdatePreviewAsync(int previewId, string? summary = null, int? deployedCL = null, bool? open = null, string? exampleLink = null, string? discussionLink = null, string? trackingLink = null, CancellationToken cancellationToken = default)`
- L222-232 _public method_ `public async Task<List<IDashboardPreview>> FindPreviewsAsync(bool? open = null, CancellationToken cancellationToken = default)`

#### class `HordeServer.Dashboard.DashboardPreviewCollection.PreviewLedger`  
`internal class PreviewLedger : SingletonBase`  
_internal; L102-105_
- attrs: `[SingletonDocument("dashboard-preview-ledger", "63f8e2154a2e859581b5bb24")]`
- inherits: `SingletonBase`
- L104 _public property_ `public int NextId { get; set; }`

#### class `HordeServer.Dashboard.DashboardPreviewCollection.PreviewDocument`  
`internal class PreviewDocument : IDashboardPreview`  
_internal; L107-143_
- inherits: `IDashboardPreview`
- L110 _public property_ `public int Id { get; set; }` — attrs: `[BsonId]`
- L112 _public property_ `public DateTime CreatedAt { get; set; }`
- L114 _public property_ `public string Summary { get; set; }`
- L116 _public property_ `public bool Open { get; set; }`
- L119 _public property_ `public int? DeployedCL { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L122 _public property_ `public string? ExampleLink { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L125 _public property_ `public string? DiscussionLink { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L128 _public property_ `public string? TrackingLink { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L131-134 _private ctor_ `private PreviewDocument()` — attrs: `[BsonConstructor]`
- L136-142 _public ctor_ `public PreviewDocument(int id, string summary)`

### `Source/Programs/Horde/HordeServer/GlobalSuppressions.cs` (HordeServer)
_(no declarations)_


### `Source/Programs/Horde/HordeServer/Parameters/ParametersController.cs` (HordeServer)


#### class `HordeServer.Parameters.ParametersController`  
`public class ParametersController : HordeControllerBase`  
_public; L18-55_
- attrs: `[ApiController] [AllowAnonymous]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/parameters endpoint. Provides configuration data to other tools.
- L20 _private field_ `private readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L25-28 _public ctor_ `public ParametersController(IOptionsSnapshot<GlobalConfig> globalConfig)` — Constructor
- L39-54 _public method_ `public ActionResult<object> GetParameters(string? path = null, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/parameters/{*path}")] [ProducesResponseType(typeof(object), 200)]` — Query side-wide parameters published for automatic configuration of external tools.

### `Source/Programs/Horde/HordeServer/Plugins/IPlugin.cs` (HordeServer)


#### interface `HordeServer.Plugins.IPlugin`  
`public interface IPlugin`  
_public; L13-29_
- desc: Interface for manipulating a plugin
- L18 _public* property_ `PluginName Name { get; }` — Name of the plugin
- L23 _public* property_ `IPluginMetadata Metadata { get; }` — Metadata for the plugin
- L28 _public* method_ `ILoadedPlugin Load()` — Load this plugin

#### interface `HordeServer.Plugins.ILoadedPlugin`  
`public interface ILoadedPlugin : IPlugin`  
_public; L34-58_
- inherits: `IPlugin`
- desc: Plugin which has been loaded
- L39 _public* property_ `Assembly Assembly { get; }` — Assembly containing the plugin's implementation
- L44 _public* property_ `Type ServerConfigType { get; }` — Type used for the server config.
- L49 _public* property_ `Type GlobalConfigType { get; }` — Type used for the global config.
- L57 _public* method_ `void ConfigureServices(IConfiguration configuration, IServerInfo serverInfo, IServiceCollection serviceCollection)` — Configure services for the plugin

#### class `HordeServer.Plugins.PluginExtensions`  
`public static class PluginExtensions`  
_public; L63-70_
- desc: Extension methods for plugins
- L68 _public method_ `public static void AddPlugin(this IServiceCollection serviceCollection, IServerInfo serverInfo, ILoadedPlugin plugin, IConfiguration configuration)` — Adds a plugin's services to a service collection

### `Source/Programs/Horde/HordeServer/Plugins/IPluginCollection.cs` (HordeServer)


#### interface `HordeServer.Plugins.IPluginCollection`  
`public interface IPluginCollection`  
_public; L10-21_
- desc: Interface for querying the state of plugins on the server
- L15 _public* property_ `IReadOnlyList<IPlugin> Plugins { get; }` — List of available plugins
- L20 _public* property_ `IReadOnlyList<ILoadedPlugin> LoadedPlugins { get; }` — List of the enabled plugins

### `Source/Programs/Horde/HordeServer/Plugins/IPluginMetadata.cs` (HordeServer)


#### interface `HordeServer.Plugins.IPluginMetadata`  
`public interface IPluginMetadata`  
_public; L11-32_
- desc: Information about a Horde plugin
- L16 _public* property_ `PluginName Name { get; }` — Name of the plugin
- L21 _public* property_ `string Description { get; }` — Description of the plugin
- L26 _public* property_ `IReadOnlyList<string> DependsOn { get; }` — Other plugins that this plugin depends on
- L31 _public* property_ `IReadOnlyList<string>? ImplementsSingletons { get; }` — Unique implementations of singleton features which this plugin provides

#### class `HordeServer.Plugins.PluginMetadata`  
`public class PluginMetadata : IPluginMetadata`  
_public; L37-52_
- inherits: `IPluginMetadata`
- desc: Information about a Horde plugin
- L40 _public property_ `public PluginName Name { get; set; }` — (inheritdoc)
- L43 _public property_ `public string Description { get; set; }` — (inheritdoc)
- L46 _public property_ `public List<string> DependsOn { get; set; }` — (inheritdoc)
- L47 _private* property_ `IReadOnlyList<string> IPluginMetadata.DependsOn => ...`
- L50 _public property_ `public List<string>? ImplementsSingletons { get; set; }` — (inheritdoc)
- L51 _private* property_ `IReadOnlyList<string>? IPluginMetadata.ImplementsSingletons => ...`

### `Source/Programs/Horde/HordeServer/Plugins/PluginCollection.cs` (HordeServer)


#### class `HordeServer.Plugins.PluginCollection`  
`public class PluginCollection : IPluginCollection`  
_public; L15-238_
- inherits: `IPluginCollection`
- desc: Concrete implementation of IPluginCollection
- L138 _public property_ `public IReadOnlyList<IPlugin> Plugins => ...` — (inheritdoc)
- L141 _public property_ `public IReadOnlyList<ILoadedPlugin> LoadedPlugins => ...` — (inheritdoc)
- L143 _private* field_ `readonly List<IPlugin> _plugins = new List<IPlugin>()`
- L144 _private* field_ `readonly List<ILoadedPlugin> _loadedPlugins = new List<ILoadedPlugin>()`
- L145 _private* field_ `readonly HashSet<PluginName> _loadedPluginNames = new HashSet<PluginName>()`
- L150-166 _public method_ `public ILoadedPlugin Add(Type startupType)` — Adds a plugin with the given startup class
- L182-204 _private method_ `private static void DependencyNodeVisit(DependencyNode current, Dictionary<PluginName, DependencyNode> nodes, List<ILoadedPlugin> result)`
- L209-230 _public method_ `public static IReadOnlyList<ILoadedPlugin> GetTopologicalSort(IReadOnlyList<ILoadedPlugin> plugins)` — Returns a topological sorted sequence of plugins by plugins they depend upon
- L236 _public method_ `public ILoadedPlugin Add<T>() where T : class, IPluginStartup` — Adds a plugin with the given startup class

#### class `HordeServer.Plugins.PluginCollection.StaticPlugin`  
`class StaticPlugin : IPlugin`  
_private*; L18-34_
- inherits: `IPlugin`
- L20 _public property_ `public PluginName Name => ...`
- L21 _public property_ `public IPluginMetadata Metadata => ...`
- L23 _private* field_ `readonly IPluginMetadata _metadata`
- L24 _private* field_ `readonly ILoadedPlugin _loadedPlugin`
- L26-30 _public ctor_ `public StaticPlugin(IPluginMetadata metadata, ILoadedPlugin loadedPlugin)`
- L32 _public method_ `public ILoadedPlugin Load()`

#### class `HordeServer.Plugins.PluginCollection.LoadedPlugin`  
`class LoadedPlugin<TServerConfig, TGlobalConfig, TStartup> : ILoadedPlugin where TServerConfig : PluginServerConfig, new() where TGlobalConfig : class, IPluginConfig, new() where TStartup : class, IPluginStartup`  
_private*; L37-135_
- attrs: `[DebuggerDisplay("{Name}")]`
- inherits: `ILoadedPlugin`
- constraints: `where TServerConfig : PluginServerConfig, new() where TGlobalConfig : class, IPluginConfig, new() where TStartup : class, IPluginStartup`
- L42 _private* field_ `readonly IPluginMetadata _metadata`
- L44 _public property_ `public PluginName Name => ...`
- L45 _public property_ `public IPluginMetadata Metadata => ...`
- L46 _public property_ `public Assembly Assembly => ...`
- L47 _public property_ `public Type ServerConfigType => ...`
- L48 _public property_ `public Type GlobalConfigType => ...`
- L50 _public ctor_ `public LoadedPlugin(IPluginMetadata metadata)`
- L53-63 _public method_ `public void ConfigureServices(IConfiguration config, IServerInfo serverInfo, IServiceCollection serviceCollection)`
- L65-118 _private* method_ `static TStartup CreateStartup(IConfiguration configuration, IServerInfo serverInfo)`
- L120-131 _private* method_ `static bool IsValidConstructor(ParameterInfo[] parameters)`
- L133 _public method_ `public ILoadedPlugin Load()`

#### enum `HordeServer.Plugins.PluginCollection.DependencyNodeState`  
`private enum DependencyNodeState`  
_private; L168-173_
- L170 _public* enumerator_ `None`
- L171 _public* enumerator_ `InProgress`
- L172 _public* enumerator_ `Done`

#### class `HordeServer.Plugins.PluginCollection.DependencyNode`  
`private class DependencyNode(ILoadedPlugin plugin, IReadOnlyList<PluginName> dependsOn)`  
_private; L175-180_
- L177 _public field_ `public readonly ILoadedPlugin Plugin = plugin`
- L178 _public field_ `public readonly IReadOnlyList<PluginName> DependsOn = dependsOn`
- L179 _public property_ `public DependencyNodeState State { get; set; }`

### `Source/Programs/Horde/HordeServer/Plugins/PluginConfigCollection.cs` (HordeServer)


#### class `HordeServer.Plugins.PluginConfigCollection`  
`public class PluginConfigCollection : Dictionary<PluginName, IPluginConfig>`  
_public; L16-35_
- attrs: `[JsonConverter(typeof(PluginConfigCollectionConverter))]`
- inherits: `Dictionary<PluginName, IPluginConfig>`
- desc: Collection of IPluginConfig objects.
- L21-34 _public method_ `public bool TryGetValue<T>(PluginName name, [NotNullWhen(true)] out T? value) where T : class, IPluginConfig` — Attempts to get a plugin config of a specific type

#### class `HordeServer.Plugins.PluginConfigCollectionConverter`  
`class PluginConfigCollectionConverter : JsonConverter<PluginConfigCollection>`  
_internal*; L40-97_
- inherits: `JsonConverter<PluginConfigCollection>`
- desc: Serializer to and from strongly typed plugin config classes
- L45 _public property_ `public Dictionary<PluginName, Type> NameToType { get; }` — Map of plugin names to the expected config type
- L48-84 _public method_ `public override PluginConfigCollection? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L87-96 _public method_ `public override void Write(Utf8JsonWriter writer, PluginConfigCollection value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Plugins/PluginOptionsFactory.cs` (HordeServer)


#### class `HordeServer.Plugins.PluginOptionsFactory`  
`sealed class PluginOptionsFactory<T> : IOptionsFactory<T>, IOptionsChangeTokenSource<T> where T : class, IPluginConfig, new()`  
_internal*; L15-50_
- inherits: `IOptionsFactory<T>, IOptionsChangeTokenSource<T>`
- constraints: `where T : class, IPluginConfig, new()`
- desc: Factory for accessing plugin config instances
- L18 _private* field_ `readonly PluginName _pluginName`
- L19 _private* field_ `readonly IOptionsMonitor<GlobalConfig> _globalConfig`
- L20 _private* field_ `readonly IOptionsChangeTokenSource<GlobalConfig> _globalConfigChangeTokenSource`
- L23 _private* property_ `string IOptionsChangeTokenSource<T>.Name => ...` — (inheritdoc)
- L28-31 _public ctor_ `public PluginOptionsFactory(PluginName pluginName, IServiceProvider serviceProvider) : this(pluginName, serviceProvider.GetRequiredService<IOptionsMonitor<GlobalConfig>>(), serviceProvider.GetRequiredService<IOptionsChangeTokenSource<GlobalConfig>>())` — Constructor
- L36-41 _public ctor_ `public PluginOptionsFactory(PluginName pluginName, IOptionsMonitor<GlobalConfig> globalConfig, IOptionsChangeTokenSource<GlobalConfig> globalConfigChangeTokenSource)` — Constructor
- L44 _public method_ `public T Create(string name)` — (inheritdoc)
- L48 _public method_ `public IChangeToken GetChangeToken()` — (inheritdoc)

#### class `HordeServer.Plugins.PluginOptionsFactoryExtensions`  
`public static class PluginOptionsFactoryExtensions`  
_public; L55-66_
- desc: Helper methods for registering
- L60-65 _public method_ `public static void AddPluginConfig<T>(this IServiceCollection services, PluginName name) where T : class, IPluginConfig, new()` — Register an options factory for the given plugin options type

### `Source/Programs/Horde/HordeServer/Properties/AssemblyInfo.cs` (HordeServer)
_(no declarations)_


### `Source/Programs/Horde/HordeServer/Server/AccountController.cs` (HordeServer)


#### class `HordeServer.Server.HordeAccountLoginViewModel`  
`public class HordeAccountLoginViewModel`  
_public; L31-42_
- desc: Model for Horde account login view
- L36 _public property_ `public string? FormPostUrl { get; set; }` — Where to post the form
- L41 _public property_ `public string? ErrorMessage { get; set; }` — Optional error message to display

#### class `HordeServer.Server.AccountStateViewModel`  
`public class AccountStateViewModel`  
_public; L47-67_
- desc: Model for Horde account state view
- L50 _public property_ `public bool IsAuthenticated { get; set; }` — Whether the current user is authenticated
- L53 _public property_ `public string? UserName { get; set; }` — Authenticated user's display name
- L56 _public property_ `public bool IsAdmin { get; set; }` — Whether the user has administrative write permissions
- L59 _public property_ `public List<ClaimViewModel> Claims { get; set; }` — List of security claims associated with the authenticated user
- L66 _public property_ `public Dictionary<string, List<UserAclPermission>> ScopeToPermissions { get; set; }` — Gets or sets the user's ACL permissions grouped by scope. Each scope contains a list of permissions showing which actions are authorized. Only scopes with at least one permission are displayed in the view.

#### class `HordeServer.Server.ClaimViewModel`  
`public class ClaimViewModel`  
_public; L72-83_
- desc: Model for Horde account state claim view
- L77 _public property_ `public string Type { get; set; }` — Gets or sets the claim type identifier (e.g., "name", "role", "sub").
- L82 _public property_ `public string Value { get; set; }` — Gets or sets the claim value associated with the claim type.

#### class `HordeServer.Server.AccountController`  
`public class AccountController : Controller`  
_public; L90-408_
- attrs: `[ApiController] [Route("[controller]")]`
- inherits: `Controller`
- desc: Controller managing account status
- L95 _private* const_ `const string StyleSheet = "body { font-family: 'Segoe UI', 'Roboto', arial, sans-serif; } " + "p { margin:20px; font-size:13px; } " + "h1 { margin: 20px; font-size: 32px; font-weight: 200; } " + "h2 { margin: 20px; font-size:  ...` — Style sheet for HTML responses
- L104 _private* field_ `readonly IUserCollection _users`
- L105 _private* field_ `readonly IAccountCollection _hordeAccounts`
- L106 _private* field_ `readonly string _authenticationScheme`
- L107 _private* field_ `readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L108 _private* field_ `readonly IOptionsMonitor<ServerSettings> _settings`
- L113-120 _public ctor_ `public AccountController(IUserCollection users, IAccountCollection hordeAccounts, IOptionsMonitor<ServerSettings> serverSettings, IOptionsSnapshot<GlobalConfig> globalConfig, IOptionsMonitor<ServerSettings> settings)` — Constructor
- L127-137 _public method_ `public static string GetAuthScheme(AuthMethod method)` — Get auth scheme name for a given auth method
- L144-163 _public method_ `public ActionResult State()` — attrs: `[HttpGet] [Route("/account")]` — Displays the current user's authentication status and permissions
- L171-174 _public method_ `public ViewResult LoggedOut()` — attrs: `[HttpGet] [Route("/account/logged-out")]` — Logged out page
- L182-194 _public method_ `public IActionResult UserPassLoginForm(string? returnUrl = null)` — attrs: `[HttpGet] [Route("/account/login/horde")]` — Show login form for username/password login
- L202-221 _public method_ `public async Task<IActionResult> UserPassLoginAsync(string? returnUrl = null)` — attrs: `[HttpPost] [Route("/account/login/horde")]` — Perform a login with username/password credentials
- L230-245 _public method_ `public async Task<IActionResult> UserDashboardLoginAsync([FromBody] DashboardLoginRequest request)` — attrs: `[HttpPost] [Route("/account/login/dashboard")]` — Dashboard login
- L247-255 _private method_ `private ViewResult LoginFormError(string message, string? returnUrl = null, HttpStatusCode statusCode = HttpStatusCode.BadRequest)`
- L263-326 _private* method_ `async Task<bool> SignInAsync(string? login, string? password)` — Sign into a Horde auth account
- L334-337 _public method_ `public IActionResult Login()` — attrs: `[HttpGet] [Route("/account/login")]` — Login to the server
- L345-358 _public method_ `public async Task<IActionResult> LogoutAsync()` — attrs: `[HttpGet] [Route("/account/logout")]` — Logout of the current account
- L366-370 _public method_ `public ActionResult<object> GetCurrentAccountEntitlements([FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/account/entitlements")] [ProducesResponseType(typeof(GetAccountEntitlementsResponse), 200)]` — Gets information about the current account
- L372-383 _internal method_ `internal static GetAccountEntitlementsResponse CreateGetAccountEntitlementsResponse(AclConfig rootAclConfig, Predicate<AclClaimConfig> predicate)`
- L390-407 _public method_ `public ActionResult<object> GetAccess([FromQuery] AclScopeName scope, [FromQuery] AclAction action, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/account/access")]` — Tests whether a user has a particular entitlement

### `Source/Programs/Horde/HordeServer/Server/AdminController.cs` (HordeServer)


#### class `HordeServer.Server.AdminSettings`  
`public class AdminSettings`  
_public; L20-36_
- desc: Object containing settings for the server
- L25 _public property_ `public string? DefaultServerAndPort { get; set; }` — The default perforce server
- L30 _public property_ `public string? DefaultUserName { get; set; }` — The default perforce username
- L35 _public property_ `public string? DefaultPassword { get; set; }` — The default perforce password

#### class `HordeServer.Server.ConformSettings`  
`public class ConformSettings`  
_public; L41-47_
- desc: The conform limit value
- L46 _public property_ `public int MaxCount { get; set; }` — Maximum number of conforms allowed at once

#### class `HordeServer.Server.AdminController`  
`public class AdminController : HordeControllerBase`  
_public; L55-237_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller managing account status
- L57 _private* field_ `readonly IAclService _aclService`
- L58 _private* field_ `readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L59 _private* field_ `readonly IOptions<ServerSettings> _serverSettings`
- L64-69 _public ctor_ `public AdminController(IAclService aclService, IOptionsSnapshot<GlobalConfig> globalConfig, IOptions<ServerSettings> serverSettings)` — Constructor
- L78-91 _public method_ `public async Task<ActionResult<string>> GetTokenAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/admin/token")]` — Issues a token for the given roles. Issues a token for the current user if not specified.
- L101-112 _public method_ `public async Task<ActionResult<string>> GetRoleTokenAsync([FromQuery] string roles, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/admin/roletoken")]` — Issues a token for the given roles. Issues a token for the current user if not specified.
- L121-133 _public method_ `public async Task<ActionResult<string>> GetRegistrationTokenAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/admin/registrationtoken")]` — Issues a token for the given roles. Issues a token for the current user if not specified.
- L142-154 _public method_ `public async Task<ActionResult<string>> GetSoftwareTokenAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/admin/softwaretoken")]` — Issues a token valid to upload new versions of the agent software.
- L163-175 _public method_ `public async Task<ActionResult<string>> GetSoftwareDownloadTokenAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/admin/softwaredownloadtoken")]` — Issues a token valid to download new versions of the agent software.
- L184-196 _public method_ `public async Task<ActionResult<string>> GetConfigTokenAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/admin/configtoken")]` — Issues a token valid to configure streams and projects
- L205-217 _public method_ `public async Task<ActionResult<string>> GetChainedJobTokenAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/admin/chainedjobtoken")]` — Issues a token valid to start chained jobs
- L224-236 _private method_ `private TimeSpan? GetDefaultExpiryTime(bool extended = false)` — Gets the default expiry time for a token

### `Source/Programs/Horde/HordeServer/Server/DebugController.cs` (HordeServer)


#### class `HordeServer.Server.DebugController`  
`public class DebugController : HordeControllerBase`  
_public; L35-407_
- attrs: `[ApiController] [Authorize] [DebugEndpoint] [Tags("Debug")]`
- inherits: `HordeControllerBase`
- desc: Controller providing some debug functionality
- L37 _private field_ `private static readonly Random s_random = new()`
- L39 _private field_ `private readonly IMongoService _mongoService`
- L40 _private field_ `private readonly ConfigService _configService`
- L41 _private field_ `private readonly IAgentScheduler _agentScheduler`
- L42 _private field_ `private readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L43 _private field_ `private readonly ILogger<DebugController> _logger`
- L48-60 _public ctor_ `public DebugController( IMongoService mongoService, ConfigService configService, IAgentScheduler agentScheduler, IOptionsSnapshot<GlobalConfig> globalConfig, ILogger<DebugController> logger)` — Constructor
- L68-86 _public method_ `public ActionResult GetServerEnvVars()` — attrs: `[HttpGet] [Route("/api/v1/debug/environment")]` — Prints all the environment variables
- L93-101 _public method_ `public ActionResult<object> GetAclScopes()` — attrs: `[HttpGet] [Route("/api/v1/debug/aclscopes")]` — Converts all legacy pools into config entries
- L108-116 _public method_ `public ActionResult<object> GetAppSettings()` — attrs: `[HttpGet] [Route("/api/v1/debug/appsettings")]` — Returns the fully parsed config object.
- L123-134 _public method_ `public ActionResult<object> GetConfig()` — attrs: `[HttpGet] [Route("/api/v1/debug/config")]` — Returns the fully parsed config object.
- L141-183 _public method_ `public async Task<ActionResult> GetDataAsync([FromQuery] string size = "1mb", CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/debug/randomdata")]` — Returns the fully parsed config object.
- L191-240 _public method_ `public ActionResult GenerateLogMessage( [FromQuery] string? logLevel = null, [FromQuery] int messageLen = 0, [FromQuery] int exceptionMessageLen = 0, [FromQuery] int argCount = 0, [FromQuery] int argLen = 10)` — attrs: `[HttpGet] [Route("/api/v1/debug/generate-log-msg")]` — Generate log message of varying size
- L248-258 _public method_ `public async Task<ActionResult<object>> GetDocumentsAsync(string name, [FromQuery] string? filter = null, [FromQuery] int index = 0, [FromQuery] int count = 10)` — attrs: `[HttpGet] [Route("/api/v1/debug/collections/{Name}")]` — Populate the database with test data
- L267-291 _public method_ `public async Task<ActionResult> StartCpuProfilerAsync()` — attrs: `[HttpGet] [Route("/api/v1/debug/profiler/cpu/start")]` — Start a CPU profiler session using dotTrace Only one profiling session can run at a time.
- L299-309 _public method_ `public ActionResult StopProfiler()` — attrs: `[HttpGet] [Route("/api/v1/debug/profiler/cpu/stop")]` — Stops a CPU profiler session
- L317-331 _public method_ `public ActionResult DownloadProfilingData()` — attrs: `[HttpGet] [Route("/api/v1/debug/profiler/cpu/download")]` — Downloads the captured CPU profiling snapshots
- L339-369 _public method_ `public async Task<ActionResult> TakeMemorySnapshotAsync()` — attrs: `[HttpGet] [Route("/api/v1/debug/profiler/mem/snapshot")]` — Take a memory snapshot using dotTrace
- L377-387 _public method_ `public ActionResult ThrowException()` — attrs: `[HttpGet] [Route("/api/v1/debug/exception")]` — Throws an exception to debug error handling
- L395-406 _public method_ `public async Task<ActionResult<object>> AgentSessionCleanupAsync(CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/debug/agent-orphaned-session-cleanup")]` — Clean up orphaned agent sessions

### `Source/Programs/Horde/HordeServer/Server/DowntimeService.cs` (HordeServer)


#### class `HordeServer.Server.DowntimeService`  
`public sealed class DowntimeService : IDowntimeService, IHostedService, IAsyncDisposable`  
_public; L17-104_
- inherits: `IDowntimeService, IHostedService, IAsyncDisposable`
- desc: Service which manages the downtime schedule
- L22-26 _public property_ `public bool IsDowntimeActive { get; set; }` — Whether the server is currently in downtime
- L28 _private* field_ `readonly IClock _clock`
- L29 _private* field_ `readonly IOptionsMonitor<GlobalConfig> _globalConfig`
- L30 _private* field_ `readonly ILogger _logger`
- L32 _private* field_ `readonly ITicker _ticker`
- L37-47 _public ctor_ `public DowntimeService(IClock clock, IOptionsMonitor<GlobalConfig> globalConfig, ILogger<DowntimeService> logger)` — Constructor
- L50 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L53 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L56 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L63-67 _private* method_ `ValueTask TickAsync(CancellationToken stoppingToken)` — Periodically called tick function
- L69-103 _internal method_ `internal void Tick()`

### `Source/Programs/Horde/HordeServer/Server/ExceptionController.cs` (HordeServer)


#### class `HordeServer.Server.ExceptionLoggingMiddleware`  
`public sealed class ExceptionLoggingMiddleware(RequestDelegate next, ILogger<ExceptionLoggingMiddleware> logger)`  
_public; L19-45_
- desc: Middleware that logs any unhandled exception and then rethrows it, so upstream handlers (developer exception page, exception filters, etc.) still see it.
- L24 _public const_ `public const string LoggedContextKey = "ExceptionLogged"` — Name of key to store in HttpContext to track if an exception has been logged
- L32-44 _public method_ `public async Task InvokeAsync(HttpContext context)` — Invokes the next middleware and logs any unhandled exception with request method, path, and trace identifier for correlation.

#### class `HordeServer.Server.ExceptionController`  
`public class ExceptionController(ILogger<ExceptionController> logger) : HordeControllerBase`  
_public; L52-99_
- attrs: `[ApiController] [Route("[controller]")]`
- desc: Controller managing account status
- L59-98 _public method_ `public ActionResult Exception()` — attrs: `[Route("/api/v1/exception")] [ApiExplorerSettings(IgnoreApi = true)]` — Outputs a diagnostic error response for an exception

### `Source/Programs/Horde/HordeServer/Server/GlobalConfig.cs` (HordeServer)


#### class `HordeServer.Server.GlobalConfig`  
`public class GlobalConfig`  
_public; L33-270_
- attrs: `[JsonSchema("https://unrealengine.com/horde/global")] [JsonSchemaCatalog("Horde Globals", "Horde global configuration file", new[] { "globals.json", "*.global.json" })] [ConfigDoc("Globals.json", "[Horde](../../../README.md) > [Configuration](../../Config.md)", "Config/Schema/Globals.md")] [ConfigIncludeRoot] [ConfigMacroScope]`
- desc: Global configuration
- L39 _public property_ `public ServerSettings ServerSettings { get; set; }` — attrs: `[JsonIgnore]` — Global server settings object
- L45 _public property_ `public string Revision { get; set; }` — attrs: `[JsonIgnore]` — Unique identifier for this config revision. Useful to detect changes.
- L50 _public property_ `public int Version { get; set; }` — Version number for the server. Values are indicated by the ConfigVersion.
- L56 _public property_ `public ConfigVersion VersionEnum => ...` — attrs: `[JsonIgnore]` — Version number for the server, as an enum.
- L61 _public property_ `public List<ConfigInclude> Include { get; set; }` — Other paths to include
- L66 _public property_ `public List<ConfigMacro> Macros { get; set; }` — Macros within the global scope
- L71 _public property_ `public DashboardConfig Dashboard { get; set; }` — Settings for the dashboard
- L76 _public property_ `public List<ScheduledDowntime> Downtime { get; set; }` — List of scheduled downtime
- L81 _public property_ `public PluginConfigCollection Plugins { get; set; }` — Plugin config objects
- L86 _public property_ `public JsonObject Parameters { get; set; }` — General parameters for other tools. Can be queried through the api/v1/parameters endpoint.
- L91 _public property_ `public bool ResolveSecrets { get; set; }` — Whether to enable resolving secrets in config properties
- L96 _public property_ `public AclConfig Acl { get; set; }` — Access control list
- L102 _public property_ `public IReadOnlyDictionary<AclScopeName, AclConfig> AclScopes => ...` — attrs: `[JsonIgnore]` — Accessor for the ACL scope lookup
- L104 _private field_ `private readonly Dictionary<AclScopeName, AclConfig> _aclLookup = ...`
- L104 _private field_ `private readonly Dictionary< _aclLookup = new Dictionary<AclScopeName, AclConfig>()`
- L107 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — (inheritdoc)
- L113-176 _public method_ `public void PostLoad(ServerSettings serverSettings, IReadOnlyList<ILoadedPlugin> loadedPlugins, IEnumerable<IDefaultAclModifier> defaultAclModifiers, ILogger? logger = null)` — Called after the config file has been read
- L181-195 _private* method_ `static AclConfig CreateRootAcl(IEnumerable<IDefaultAclModifier> defaultAclModifiers)` — Creates the default root ACL
- L197-214 _private* method_ `static void BuildAclScopeLookup(AclConfig acl, Dictionary<AclScopeName, AclConfig> aclLookup)`
- L221 _public method_ `public bool TryGetAclScope(AclScopeName scopeName, [NotNullWhen(true)] out AclConfig? scopeConfig)` — Authorizes a user to perform a given action
- L230 _public method_ `public bool Authorize(AclScopeName scopeName, AclAction action, ClaimsPrincipal user)` — Authorizes a user to perform a given action
- L233 _private* field_ `IReadOnlyList<string>? _cachedGroupClaims`
- L238-247 _public method_ `public IReadOnlyList<string> GetValidAccountGroupClaims()` — Gets all the valid HordeClaimTypes.Group claims referenced by ACL entries within the config object.
- L249-269 _private* method_ `static void FindGroupClaimsFromObject(AclConfig config, HashSet<string> groups)`

#### enum `HordeServer.Server.ScheduledDowntimeFrequency`  
`public enum ScheduledDowntimeFrequency`  
_public; L275-291_
- desc: How frequently the maintenance window repeats
- L280 _public* enumerator_ `Once` — Once
- L285 _public* enumerator_ `Daily` — Every day
- L290 _public* enumerator_ `Weekly` — Every week

#### class `HordeServer.Server.ScheduledDowntime`  
`public class ScheduledDowntime`  
_public; L296-420_
- desc: Settings for the maintenance window
- L301 _public property_ `public DateTimeOffset StartTime { get; set; }` — Start time
- L306 _public property_ `public DateTimeOffset FinishTime { get; set; }` — Finish time
- L311 _public property_ `public TimeSpan? Duration { get; set; }` — Duration of the maintenance window. An alternative to FinishTime.
- L316 _public property_ `public string? TimeZone { get; set; }` — The name of time zone to set the Coordinated Universal Time (UTC) offset for StartTime and FinishTime.
- L321 _public property_ `public ScheduledDowntimeFrequency Frequency { get; set; }` — Frequency that the window repeats
- L323-343 _internal method_ `internal void PostLoad()`
- L350-378 _public method_ `public (DateTimeOffset StartTime, DateTimeOffset FinishTime) GetNext(DateTimeOffset now)` — Gets the next scheduled downtime or the current one if it is active
- L385-419 _public method_ `public bool IsActive(DateTimeOffset now)` — Determines if this schedule is active

### `Source/Programs/Horde/HordeServer/Server/GlobalsService.cs` (HordeServer)


#### class `HordeServer.Server.GlobalsService`  
`public class GlobalsService`  
_public; L19-143_
- desc: Accessor for the global Globals singleton
- L68 _private* field_ `readonly IMongoService _mongoService`
- L69 _private* field_ `readonly string _jwtIssuer`
- L76-88 _public ctor_ `public GlobalsService(IMongoService mongoService, IOptions<ServerSettings> settings)` — Constructor
- L94-113 _public method_ `public async ValueTask<IGlobals> GetAsync(CancellationToken cancellationToken)` — Gets the current globals instance
- L115-121 _private* method_ `static Globals CreateGlobals()`
- L130-142 _public method_ `public async ValueTask<IGlobals?> TryUpdateAsync(IGlobals globals, string? configRevision, CancellationToken cancellationToken)` — Try to update the current globals object

#### class `HordeServer.Server.GlobalsService.Globals`  
`class Globals : SingletonBase, IGlobals`  
_private*; L25-66_
- attrs: `[SingletonDocument("globals", "5e3981cb28b8ec59cd07184a")]`
- inherits: `SingletonBase, IGlobals`
- desc: Global server settings
- L28 _public field_ `public GlobalsService _owner = null!` — attrs: `[BsonIgnore]`
- L30 _public property_ `public ObjectId InstanceId { get; set; }`
- L31 _public property_ `public string ConfigRevision { get; set; }`
- L32 _public property_ `public byte[]? JwtSigningKey { get; set; }`
- L33 _public property_ `public RSAParameters? RsaParameters { get; set; }`
- L34 _public property_ `public int? SchemaVersion { get; set; }`
- L37 _private* property_ `string IGlobals.JwtIssuer => ...` — attrs: `[BsonIgnore]`
- L40 _private* property_ `SecurityKey IGlobals.JwtSigningKey => ...` — attrs: `[BsonIgnore]`
- L43 _private* property_ `RsaSecurityKey IGlobals.RsaSigningKey => ...` — attrs: `[BsonIgnore]`
- L45-48 _public ctor_ `public Globals()`
- L50-53 _public method_ `public Globals Clone()`
- L55-58 _public method_ `public void RotateSigningKey()`
- L60-65 _public method_ `public void RotateRsaParameters()`

### `Source/Programs/Horde/HordeServer/Server/HealthService.cs` (HordeServer)


#### class `HordeServer.Server.HealthService`  
`public class HealthService : Health.HealthBase`  
_public; L14-61_
- inherits: `Health.HealthBase`
- desc: Implements the gRPC health checking protocol See https://github.com/grpc/grpc/blob/master/doc/health-checking.md for details
- L16 _private* field_ `readonly LifetimeService _lifetimeService`
- L22-25 _public ctor_ `public HealthService(LifetimeService lifetimeService)` — Constructor
- L36-48 _public method_ `public override Task<HealthCheckResponse> Check(HealthCheckRequest request, ServerCallContext context)` — Return server status, primarily intended for load balancers to decide if traffic should be routed to this process The supplied service name is currently ignored. For example, the gRPC health check for AWS ALB will pick up and react to the gRPC status code returned.
- L57-60 _public method_ `public override Task Watch(HealthCheckRequest request, IServerStreamWriter<HealthCheckResponse> responseStream, ServerCallContext context)` — Stream the server health status (not implemented)

### `Source/Programs/Horde/HordeServer/Server/IGlobals.cs` (HordeServer)


#### interface `HordeServer.Server.IGlobals`  
`public interface IGlobals`  
_public; L11-32_
- desc: Global server settings
- L16 _public* property_ `ObjectId InstanceId { get; }` — Unique instance id of this database
- L21 _public* property_ `string JwtIssuer { get; }` — Issuer for JWT keys. Can be overridden by config file.
- L26 _public property_ `public SecurityKey JwtSigningKey { get; }` — The signing key for this server cluster
- L31 _public property_ `public RsaSecurityKey RsaSigningKey { get; }` — RSA security key for this cluster

### `Source/Programs/Horde/HordeServer/Server/LifetimeController.cs` (HordeServer)


#### class `HordeServer.Server.LifetimeController`  
`public class LifetimeController : ControllerBase`  
_public; L13-53_
- attrs: `[ApiController] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for app lifetime related routes
- L18 _private* field_ `readonly LifetimeService _lifetimeService` — Singleton instance of the lifetime service
- L24-27 _public ctor_ `public LifetimeController(LifetimeService lifetimeService)` — Constructor
- L40-52 _public method_ `public Task<ActionResult> ServerReadinessAsync()` — attrs: `[HttpGet] [Route("/health/ready")]` — Readiness check for server When a SIGTERM has been received, the server is shutting down. To communicate the server is stopping to load balancers/orchestrators, this route will return either 503 or 200. The server will continue to serve requests, but it's assumed the load balancer has reacted and stopped sending traffic by the time the server process exits.

### `Source/Programs/Horde/HordeServer/Server/LifetimeService.cs` (HordeServer)


#### class `HordeServer.Server.LifetimeService`  
`public sealed class LifetimeService : ILifetimeService, IHostedService, IAsyncDisposable`  
_public; L17-236_
- inherits: `ILifetimeService, IHostedService, IAsyncDisposable`
- desc: Service containing an async task that allows long polling operations to complete early if the server is shutting down
- L22 _private* field_ `readonly ILogger<LifetimeService> _logger` — Writer for log output
- L27 _private* field_ `readonly TaskCompletionSource<bool> _stoppingTaskCompletionSource` — Task source for the server stopping
- L37 _private* field_ `readonly CancellationTokenRegistration _registration` — Registration token for the stopping event
- L39 _private* field_ `readonly IHostApplicationLifetime _lifetime`
- L40 _private* field_ `readonly IMongoService _mongoService`
- L41 _private* field_ `readonly IRedisService _redisService`
- L42 _private* field_ `readonly ITicker _ticker`
- L45 _private* field_ `readonly int? _shutdownMemoryThreshold = null` — (inheritdoc)
- L70-86 _public ctor_ `public LifetimeService(IOptionsMonitor<ServerSettings> settings, IHostApplicationLifetime lifetime, IHostEnvironment env, IMongoService mongoService, IRedisService redisService, IClock clock, ILogger<LifetimeService> logger)` — Constructor
- L89-93 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L96-99 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L102-105 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L107-127 _private method_ `private ValueTask CheckMemoryUsageAsync(CancellationToken cancellationToken)`
- L132-175 _private* method_ `void ApplicationStopping()` — Callback for the application stopping
- L180 _public property_ `public bool IsStopping { get; set; }` — Returns true if the server is stopping
- L185 _public property_ `public bool IsPreStopping { get; set; }` — Returns true if the server is stopping, but may not be removed from the load balancer yet
- L190 _public property_ `public Task StoppingTask => ...` — Gets an awaitable task for the server stopping
- L196-211 _public method_ `public async Task<bool> IsMongoDbConnectionHealthyAsync()` — Check if MongoDB can be reached
- L217-235 _public method_ `public async Task<bool> IsRedisConnectionHealthyAsync()` — Check if Redis can be reached

### `Source/Programs/Horde/HordeServer/Server/MetricService.cs` (HordeServer)


#### class `HordeServer.Server.MetricService`  
`public sealed class MetricService : IHostedService, IDisposable`  
_public; L14-72_
- inherits: `IHostedService, IDisposable`
- desc: Periodically send metrics for the CLR and other services that cannot be collected on a per-request basis
- L19-41 _public ctor_ `public MetricService(Meter meter)` — Constructor
- L44 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L47 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L50 _public method_ `public void Dispose()` — (inheritdoc)

#### struct `HordeServer.Server.MetricService.ThreadMetrics`  
`private struct ThreadMetrics`  
_private; L52-71_
- L54 _public field_ `public readonly int WorkerMin`
- L55 _public field_ `public readonly int WorkerMax`
- L56 _public field_ `public readonly int WorkerFree`
- L57 _public field_ `public readonly int WorkerBusy`
- L58 _public field_ `public readonly int IoMin`
- L59 _public field_ `public readonly int IoMax`
- L60 _public field_ `public readonly int IoFree`
- L61 _public field_ `public readonly int IoBusy`
- L63-70 _public ctor_ `public ThreadMetrics()`

### `Source/Programs/Horde/HordeServer/Server/MongoMigration.cs` (HordeServer)


#### enum `HordeServer.Server.SchemaVersionState`  
`public enum SchemaVersionState`  
_public; L18-49_
- desc: Indicates the version relationship between the application's defined schema and the database's applied schema. Used to determine if migrations or code updates are required.
- L28 _public* enumerator_ `VersionMatch = 0` — The application and database schemas are at the same version. - No action required - Application can operate normally - Represents the ideal state
- L38 _public* enumerator_ `DatabaseOutdated` — The application schema version is newer than the database version. - Database requires migration - Application should not run or process requests - Requires manual (or automated) migration intervention
- L48 _public* enumerator_ `ApplicationOutdated` — The database schema version is newer than the application version. - Application requires deployment of a newer version of itself - Can be a valid temporary state during rolling updates - Safe to continue operation

#### record `HordeServer.Server.SchemaVersionResult`  
`public record SchemaVersionResult(SchemaVersionState State, int AppVersion, int DatabaseVersion, List<MigrationDefinition> MissingMigrations)`  
_public; L58-58_
- desc: Results of comparing application and database schema versions

#### class `HordeServer.Server.MigrationDefinition`  
`public class MigrationDefinition(IMongoMigration migration, string plugin, int version, string name)`  
_public; L63-109_
- desc: A database migration with its metadata
- L66 _public property_ `public IMongoMigration Migration { get; }` — (inheritdoc)
- L69 _public property_ `public string Plugin { get; }` — (inheritdoc)
- L72 _public property_ `public int Version { get; }` — (inheritdoc)
- L75 _public property_ `public string Name { get; }` — (inheritdoc)
- L78-81 _public method_ `public override string ToString()` — (inheritdoc)
- L84-97 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L100-103 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L105-108 _private method_ `private bool Equals(MigrationDefinition other)`

#### class `HordeServer.Server.MigrationException`  
`public class MigrationException : Exception`  
_public; L114-121_
- inherits: `Exception`
- desc: Exception thrown during migration operations
- L117 _public ctor_ `public MigrationException(string message) : base(message)` — (inheritdoc)
- L120 _public ctor_ `public MigrationException(string message, Exception innerException) : base(message, innerException)` — (inheritdoc)

#### class `HordeServer.Server.MongoMigrator`  
`public class MongoMigrator`  
_public; L127-427_
- desc: Handles database schema migrations for MongoDB database This class is not thread-safe
- L129 _private field_ `private readonly Dictionary<string, HashSet<MigrationDefinition>> _migrations = ...`
- L129 _private field_ `private readonly Dictionary< _migrations = []`
- L130 _private field_ `private readonly IMongoService _mongoService`
- L131 _private field_ `private readonly ILogger<MongoMigrator> _logger`
- L142-146 _public ctor_ `public MongoMigrator(IMongoService mongoService, ILogger<MongoMigrator> logger)` — Constructor
- L153-171 _public method_ `public void AutoAddMigrations()` — Load all migrations Will scan all loaded assemblies via reflection and add any class decorated with MongoMigrationAttribute
- L178-207 _public method_ `public void AddMigration(IMongoMigration migration)` — Adds a new migration to be managed by this migrator
- L216-249 _public method_ `public async Task<bool> ValidateAllSchemasAsync(bool autoUpgrade, CancellationToken cancellationToken)` — Validates database schema versions for all plugins against application versions Logs error for outdated schemas with migration instructions.
- L256-266 _public method_ `public async Task<Dictionary<string, SchemaVersionResult>> GetAllSchemaStateAsync(CancellationToken cancellationToken)` — Retrieves the schema version states for all registered plugins
- L274-301 _public method_ `public async Task<SchemaVersionResult> GetSchemaStateAsync(string plugin, CancellationToken cancellationToken)` — Checks the current schema version state for a plugin
- L309-317 _public method_ `public IReadOnlyList<MigrationDefinition> GetMigrations(string plugin)` — Gets all migrations registered for a plugin
- L323-329 _public method_ `public async Task UpgradeAsync(CancellationToken cancellationToken)` — Upgrades all database schemas to latest version
- L337-357 _public method_ `public async Task UpgradeAsync(string plugin, int? toVersion, CancellationToken cancellationToken)` — Upgrades database schema for a plugin to specified version or latest if not specified
- L365-387 _public method_ `public async Task DowngradeAsync(string plugin, int toVersion, CancellationToken cancellationToken)` — Downgrades database schema for a plugin to specified version
- L389-412 _private method_ `private static void ValidateMigrations(string plugin, IReadOnlyList<MigrationDefinition> migrations)`
- L414-417 _private method_ `private async Task SetVersionAsync(string plugin, int version, CancellationToken cancellationToken)`
- L422-426 _private method_ `private async Task<int> GetVersionAsync(string plugin, CancellationToken cancellationToken)` — Get currently applied version of migrations for a plugin as stored in database

#### class `HordeServer.Server.MongoMigrator.MigrationState`  
`private class MigrationState : SingletonBase`  
_private; L134-137_
- attrs: `[SingletonDocument("mongo-migrations")]`
- inherits: `SingletonBase`
- L136 _public property_ `public Dictionary<string, int> Versions { get; set; }`

### `Source/Programs/Horde/HordeServer/Server/MongoService.cs` (HordeServer)


#### record `HordeServer.Server.MongoUpgradeTask`  
`record class MongoUpgradeTask(Func<CancellationToken, Task> UpgradeAsync, TaskCompletionSource CompletionSource)`  
_internal*; L38-38_
- desc: Task used to update indexes

#### class `HordeServer.Server.MongoService`  
`public sealed class MongoService : IMongoService, IHealthCheck, IAsyncDisposable`  
_public; L43-905_
- inherits: `IMongoService, IHealthCheck, IAsyncDisposable`
- desc: Singleton for accessing the database
- L48 _public property_ `public IMongoDatabase Database { get; set; }` — The database instance
- L53 _private* property_ `IMongoCollection<BsonDocument> SingletonsV1 { get; }` — Collection of singleton documents
- L58 _private* property_ `IMongoCollection<BsonDocument> SingletonsV2 { get; }` — Collection of singleton documents
- L63 _private* property_ `ServerSettings Settings { get; }` — Settings for the application
- L68 _private* field_ `readonly ILogger<MongoService> _logger` — Logger for this instance
- L73 _public property_ `public bool ReadOnlyMode { get; }` — Access the database in a read-only mode (don't create indices or modify content)
- L78 _private* field_ `ManagedProcessGroup? _mongoProcessGroup` — The mongo process group
- L83 _private* field_ `ManagedProcess? _mongoProcess` — The mongo process
- L88 _private* field_ `Task? _mongoOutputTask` — Task to read from the mongo process
- L93 _private* field_ `readonly ILoggerFactory _loggerFactory` — Factory for creating logger instances
- L98 _private* field_ `readonly Tracer _tracer` — Tracer
- L103 _private* const_ `const int DefaultMongoPort = 27017` — Default port for MongoDB connections
- L105 _private* field_ `static readonly RedisKey s_schemaLockKey = new RedisKey("server/schema-upgrade/lock")`
- L107 _private* field_ `readonly MongoClient _client`
- L108 _private* field_ `readonly IRedisService _redisService`
- L110 _private* field_ `readonly SemaphoreSlim _upgradeSema = new SemaphoreSlim(1)`
- L112 _private* field_ `CancellationTokenSource _upgradeCancellationSource = new CancellationTokenSource()`
- L113 _private* field_ `readonly Dictionary<string, Task> _collectionUpgradeTasks = ...`
- L113 _private* field_ `readonly Dictionary< _collectionUpgradeTasks = new Dictionary<string, Task>(StringComparer.Ordinal)`
- L114 _private* field_ `readonly Task<bool> _setSchemaVersionTask`
- L116 _private* field_ `static string? s_existingInstance`
- L121-219 _public ctor_ `public MongoService(IOptions<ServerSettings> settingsSnapshot, IRedisService redisService, MongoCommandTracer mongoTracer, Tracer tracer, ILogger<MongoService> logger, ILoggerFactory loggerFactory)` — Constructor
- L221 _internal const_ `internal const int CtrlCEvent = 0`
- L224 _internal method_ `internal static extern bool GenerateConsoleCtrlEvent(int eventId, int processGroupId)` — attrs: `[DllImport("kernel32.dll")]`
- L227-294 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L301-312 _private* method_ `static bool IsPortInUse(int portNumber)` — Checks if the given port is in use
- L319-385 _private* method_ `bool TryStartMongoServer(ILogger logger)` — Attempts to start a local instance of MongoDB
- L391-423 _private* method_ `async Task RelayMongoOutputAsync()` — Copies output from the mongo process to the logger
- L425-439 _private* method_ `static LogLevel ParseMongoLogLevel(string text)`
- L445-462 _private* method_ `void TraceMongoCommand(BsonDocument command)` — Logs a mongodb command, removing any fields we don't care about
- L469-489 _private* method_ `static X509Certificate2Collection ImportCertificateBundle(string fileName)` — Imports one or more certificates from a single PEM file
- L499-553 _private* method_ `bool CertificateValidationCallBack(object sender, X509Certificate? certificate, X509Chain? chain, SslPolicyErrors sslPolicyErrors)` — Provides additional diagnostic information for SSL certificate validation
- L559-562 _public method_ `public MongoClient GetClient()` — Get the MongoDB client
- L565-568 _public method_ `public IMongoCollection<T> GetCollection<T>(string name)` — (inheritdoc)
- L571-576 _public method_ `public IMongoCollection<T> GetCollection<T>(string name, Func<IndexKeysDefinitionBuilder<T>, IndexKeysDefinition<T>> keysFunc, bool unique = false)` — (inheritdoc)
- L579-601 _public method_ `public IMongoCollection<T> GetCollection<T>(string name, IEnumerable<MongoIndex<T>> indexes)` — (inheritdoc)
- L603-625 _private method_ `private async Task UpdateIndexesAsync<T>(string collectionName, IMongoCollection<T> collection, MongoIndex<T>[] newIndexes, CancellationToken cancellationToken)`
- L627-723 _private method_ `private async Task UpdateIndexesInternalAsync<T>(string collectionName, IMongoCollection<T> collection, MongoIndex<T>[] newIndexes, CancellationToken cancellationToken)`
- L725-757 _private* method_ `async Task<bool> SetSchemaVersionAsync(SemVer schemaVersion, CancellationToken cancellationToken)`
- L775-778 _public method_ `public Task<T> GetSingletonAsync<T>(CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L781-784 _public method_ `public Task<T> GetSingletonAsync<T>(Func<T> constructor, CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L787-795 _public method_ `public Task UpdateSingletonAsync<T>(Action<T> updater, CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L798-812 _public method_ `public async Task UpdateSingletonAsync<T>(Func<T, bool> updater, CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L815-818 _public method_ `public Task<bool> TryUpdateSingletonAsync<T>(T singletonObject, CancellationToken cancellationToken) where T : SingletonBase` — (inheritdoc)
- L828-859 _internal method_ `internal static async Task<T> GetSingletonStaticAsync<T>(IMongoCollection<BsonDocument> singletonsV1, IMongoCollection<BsonDocument> singletonsV2, Func<T> constructor, CancellationToken cancellationToken) where T : SingletonBase, new()` — Gets a singleton document by id
- L868-890 _internal method_ `internal static async Task<bool> TryUpdateSingletonStaticAsync<T>(IMongoCollection<BsonDocument> singletonsV2, T singletonObject, CancellationToken cancellationToken) where T : SingletonBase` — Attempts to update a singleton object
- L893-904 _public method_ `public async Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Server.MongoService.SingletonInfo`  
`class SingletonInfo<T> where T : SingletonBase`  
_private*; L759-772_
- constraints: `where T : SingletonBase`
- L761 _public field_ `public static readonly SingletonDocumentAttribute Attribute = GetAttribute()`
- L763-771 _private* method_ `static SingletonDocumentAttribute GetAttribute()`

#### class `HordeServer.Server.MongoSchemaDocument`  
`public class MongoSchemaDocument : SingletonBase`  
_public; L911-917_
- attrs: `[SingletonDocument("mongo-schema", "62470d8508d48eddfac7b55d")]`
- inherits: `SingletonBase`
- desc: Stores the version number of the latest server instance to have upgraded the database schema
- L916 _public property_ `public string? Version { get; set; }` — Current version number

### `Source/Programs/Horde/HordeServer/Server/Notices/INotice.cs` (HordeServer)


#### interface `HordeServer.Server.Notices.INotice`  
`public interface INotice`  
_public; L13-40_
- desc: User notice
- L18 _public property_ `public ObjectId Id { get; }` — Unique id for this notice
- L24 _public property_ `public UserId? UserId { get; }` — attrs: `[BsonIgnoreIfNull]` — User id of who created this notice, null for system created notices
- L29 _public property_ `public DateTime? StartTime { get; }` — Start time to display this message
- L34 _public property_ `public DateTime? FinishTime { get; }` — Finish time to display this message
- L39 _public property_ `public string Message { get; }` — Message to display

### `Source/Programs/Horde/HordeServer/Server/Notices/INoticeCollection.cs` (HordeServer)


#### interface `HordeServer.Server.Notices.INoticeCollection`  
`public interface INoticeCollection`  
_public; L15-61_
- desc: A collection of user specified notices
- L26 _public* method_ `Task<INotice?> AddNoticeAsync(string message, UserId? userId, DateTime? startTime, DateTime? finishTime, CancellationToken cancellationToken = default)` — Add a notice to the collection
- L37 _public* method_ `Task<bool> UpdateNoticeAsync(ObjectId id, string? message, DateTime? startTime, DateTime? finishTime, CancellationToken cancellationToken = default)` — Update an existing notice
- L45 _public* method_ `Task<INotice?> GetNoticeAsync(ObjectId noticeId, CancellationToken cancellationToken = default)` — Get a notice by id
- L52 _public* method_ `Task<List<INotice>> GetNoticesAsync(CancellationToken cancellationToken = default)` — Get all notices
- L60 _public* method_ `Task<bool> RemoveNoticeAsync(ObjectId id, CancellationToken cancellationToken = default)` — Remove a notice

### `Source/Programs/Horde/HordeServer/Server/Notices/NoticeAclAction.cs` (HordeServer)


#### class `HordeServer.Server.Notices.NoticeAclAction`  
`public static class NoticeAclAction`  
_public; L10-26_
- desc: ACL actions relating to notices
- L15 _public property_ `public static AclAction CreateNotice { get; }` — Ability to create new notices
- L20 _public property_ `public static AclAction UpdateNotice { get; }` — Ability to modify notices on the server
- L25 _public property_ `public static AclAction DeleteNotice { get; }` — Ability to delete notices

### `Source/Programs/Horde/HordeServer/Server/Notices/NoticeCollection.cs` (HordeServer)


#### class `HordeServer.Server.Notices.NoticeCollection`  
`public class NoticeCollection : INoticeCollection`  
_public; L18-112_
- inherits: `INoticeCollection`
- desc: Collection of notice documents
- L55 _private* field_ `readonly IMongoCollection<NoticeDocument> _notices`
- L60-63 _public ctor_ `public NoticeCollection(IMongoService mongoService)` — Constructor
- L66-71 _public method_ `public async Task<INotice?> AddNoticeAsync(string message, UserId? userId, DateTime? startTime, DateTime? finishTime, CancellationToken cancellationToken)` — (inheritdoc)
- L74-91 _public method_ `public async Task<bool> UpdateNoticeAsync(ObjectId id, string? message, DateTime? startTime, DateTime? finishTime, CancellationToken cancellationToken)` — (inheritdoc)
- L94-97 _public method_ `public async Task<INotice?> GetNoticeAsync(ObjectId noticeId, CancellationToken cancellationToken)` — (inheritdoc)
- L100-104 _public method_ `public async Task<List<INotice>> GetNoticesAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L107-111 _public method_ `public async Task<bool> RemoveNoticeAsync(ObjectId id, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Server.Notices.NoticeCollection.NoticeDocument`  
`class NoticeDocument : INotice`  
_private*; L24-53_
- inherits: `INotice`
- desc: Document representing a notice
- L27 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L30 _public property_ `public UserId? UserId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L33 _public property_ `public DateTime? StartTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L36 _public property_ `public DateTime? FinishTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L38 _public property_ `public string Message { get; set; }`
- L41-43 _private ctor_ `private NoticeDocument()` — attrs: `[BsonConstructor]`
- L45-52 _public ctor_ `public NoticeDocument(ObjectId id, string message, UserId? userId, DateTime? startTime, DateTime? finishTime)`

### `Source/Programs/Horde/HordeServer/Server/Notices/NoticeService.cs` (HordeServer)


#### class `HordeServer.Server.Notices.NoticeService`  
`public sealed class NoticeService`  
_public; L15-89_
- desc: Notice service
- L20 _private* field_ `readonly INoticeCollection _notices` — Notice collection
- L25-28 _public ctor_ `public NoticeService(INoticeCollection notices)` — Device service constructor
- L39-42 _public method_ `public Task<INotice?> AddNoticeAsync(string message, UserId? userId, DateTime? startTime, DateTime? finishTime, CancellationToken cancellationToken)` — Add a notice
- L53-56 _public method_ `public Task<bool> UpdateNoticeAsync(ObjectId id, string? message, DateTime? startTime, DateTime? finishTime, CancellationToken cancellationToken)` — Update an existing notice
- L64-67 _public method_ `public Task<INotice?> GetNoticeAsync(ObjectId noticeId, CancellationToken cancellationToken)` — Get a notice by id
- L74-77 _public method_ `public Task<List<INotice>> GetNoticesAsync(CancellationToken cancellationToken)` — Get all notices
- L85-88 _public method_ `public Task<bool> RemoveNoticeAsync(ObjectId id, CancellationToken cancellationToken)` — Remove an existing notice

### `Source/Programs/Horde/HordeServer/Server/Notices/NoticesController.cs` (HordeServer)


#### class `HordeServer.Server.Notices.NoticesController`  
`public class NoticesController : ControllerBase`  
_public; L27-179_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/notices endpoint
- L29 _private field_ `private readonly IUserCollection _userCollection`
- L30 _private field_ `private readonly NoticeService _noticeService`
- L31 _private field_ `private readonly ServerStatusService _statusService`
- L32 _private field_ `private readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L33 _private field_ `private readonly IClock _clock`
- L38-45 _public ctor_ `public NoticesController(NoticeService noticeService, ServerStatusService statusService, IUserCollection userCollection, IClock clock, IOptionsSnapshot<GlobalConfig> globalConfig)` — Constructor
- L54-65 _public method_ `public async Task<ActionResult> AddNoticeAsync(CreateNoticeRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost("/api/v1/notices")]` — Add a status message
- L74-82 _public method_ `public async Task<ActionResult> UpdateNoticeAsync(UpdateNoticeRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut("/api/v1/notices")]` — Update a status message
- L89-99 _public method_ `public async Task<ActionResult> DeleteNoticeAsync(string id, CancellationToken cancellationToken)` — attrs: `[HttpDelete("/api/v1/notices/{id}")]` — Remove a manually added status message
- L107-178 _public method_ `public async Task<List<GetNoticeResponse>> GetNoticesAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet("/api/v1/notices")]` — Gets the current status messages

### `Source/Programs/Horde/HordeServer/Server/RedisProcess.cs` (HordeServer)


#### class `HordeServer.Server.RedisProcess`  
`public sealed class RedisProcess : IAsyncDisposable`  
_public; L19-160_
- inherits: `IAsyncDisposable`
- desc: Runs a local instance of redis
- L21 _private* field_ `readonly DirectoryReference _tempDir`
- L22 _private* field_ `readonly ILogger _logger`
- L24 _private* field_ `int? _port`
- L25 _private* field_ `ManagedProcessGroup? _processGroup`
- L26 _private* field_ `ManagedProcess? _process`
- L27 _private* field_ `BackgroundTask? _relayTask`
- L33 _public property_ `public static FileReference RedisExe => ...` — attrs: `[SupportedOSPlatform("windows")]` — Path to the redis executable
- L38 _public property_ `public int Port => ...` — Selected port for the service
- L43-47 _public ctor_ `public RedisProcess(ILogger logger)` — Constructor
- L50-53 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L59-88 _public method_ `public void Start(string arguments)` — attrs: `[SupportedOSPlatform("windows")]` — Starts the redis process
- L93-114 _public method_ `public async ValueTask StopAsync()` — Stops the current process
- L117 _private* method_ `static extern uint DeleteFile(string lpFileName)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L119-128 _private* method_ `void DeleteTempFiles()`
- L133-140 _private* method_ `static int GetAvailablePort()` — Gets an unused port that can host the redis server
- L145-159 _private* method_ `async Task RelayOutputAsync(CancellationToken cancellationToken)` — Copies output from the redis process to the logger

### `Source/Programs/Horde/HordeServer/Server/RedisService.cs` (HordeServer)


#### class `HordeServer.Server.RedisService`  
`public sealed class RedisService : IRedisService, IAsyncDisposable`  
_public; L22-149_
- inherits: `IRedisService, IAsyncDisposable`
- desc: Manages the lifetime of a bundled Redis instance
- L27 _private* const_ `const int RedisPort = 6379` — Default Redis port
- L32 _public property_ `public RedisConnectionPool ConnectionPool { get; }` — Connection pool
- L37 _public property_ `public bool ReadOnlyMode { get; }` — Flag for whether the connection is read-only
- L39 _private* field_ `RedisProcess? _redisProcess`
- L40 _private* field_ `readonly ILogger<RedisService> _logger`
- L45-49 _public ctor_ `public RedisService(IOptions<ServerSettings> options, ILogger<RedisService> logger) : this(options.Value.RedisConnectionString, -1, logger)` — Constructor
- L57-78 _public ctor_ `public RedisService(string? connectionString, int dbNum, ILogger<RedisService> logger)` — Constructor
- L81-92 _public method_ `public async Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = default)` — (inheritdoc)
- L95-110 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L116-127 _private* method_ `static bool IsRunningOnDefaultPort()` — Checks if Redis is already running on the default port
- L133-148 _private* method_ `bool TryStartRedisProcess()` — Attempts to start a local instance of Redis

### `Source/Programs/Horde/HordeServer/Server/RequestTrackerService.cs` (HordeServer)


#### class `HordeServer.Server.RequestTrackerService`  
`public class RequestTrackerService`  
_public; L20-94_
- desc: Tracks open HTTP requests to ASP.NET Will block a pending shutdown until all requests in progress are finished (or graceful timeout is reached) This avoids interrupting long running requests such as artifact uploads.
- L25 _private field_ `private readonly ILogger<RequestTrackerService> _logger` — Writer for log output
- L27 _private* field_ `readonly ConcurrentDictionary<string, TrackedRequest> _requestsInProgress = ...`
- L27 _private* field_ `readonly ConcurrentDictionary< _requestsInProgress = new ConcurrentDictionary<string, TrackedRequest>()`
- L33-36 _public ctor_ `public RequestTrackerService(ILogger<RequestTrackerService> logger)` — Constructor
- L42-45 _public method_ `public void RequestStarted(HttpContext context)` — Called by the middleware when a request is started
- L51-54 _public method_ `public void RequestFinished(HttpContext context)` — Called by the middleware when a request is finished (no matter if an exception occurred or not)
- L60-63 _public method_ `public IReadOnlyDictionary<string, TrackedRequest> GetRequestsInProgress()` — Get current requests in progress
- L65-78 _private method_ `private string GetRequestsInProgressAsString()`
- L83-93 _public method_ `public void LogRequestsInProgress()` — Log all requests currently in progress

#### class `HordeServer.Server.TrackedRequest`  
`public class TrackedRequest`  
_public; L99-129_
- desc: Value object for tracked requests
- L104 _public property_ `public DateTime StartedAt { get; }` — When the request was received
- L109 _public property_ `public HttpRequest Request { get; }` — The HTTP request being tracked
- L115-119 _public ctor_ `public TrackedRequest(HttpRequest request)` — Constructor
- L125-128 _public method_ `public int GetTimeSinceStartInMs()` — How long the request has been running

#### class `HordeServer.Server.RequestTrackerMiddleware`  
`public class RequestTrackerMiddleware`  
_public; L134-173_
- desc: ASP.NET Middleware to track open requests
- L136 _private field_ `private readonly RequestDelegate _next`
- L142-145 _public ctor_ `public RequestTrackerMiddleware(RequestDelegate next)` — Constructor
- L153-172 _public method_ `public async Task InvokeAsync(HttpContext context, RequestTrackerService service)` — Invoked by ASP.NET framework itself

### `Source/Programs/Horde/HordeServer/Server/ReverseProxyDetection.cs` (HordeServer)


#### class `HordeServer.Server.ReverseProxyDetectionMiddleware`  
`public class ReverseProxyDetectionMiddleware(RequestDelegate next, ILogger<ReverseProxyDetectionMiddleware> logger, IOptionsMonitor<ServerSettings> settings)`  
_public; L19-47_
- desc: Middleware that detects if the server is running behind a load balancer or reverse proxy. If detected, logs an error if ServerSettings.ServerUrl is not configured.
- L21 _private const_ `private const int MaxWarnings = 5`
- L22 _private const_ `private const int MaxRequests = 5000`
- L23 _private field_ `private readonly List<string> _headers = ["X-Forwarded-For", "X-Forwarded-Proto", "X-Forwarded-Host", "X-Forwarded-Server",]`
- L24 _private field_ `private int _requestCount`
- L25 _private field_ `private int _warningCount`
- L30-46 _public method_ `public async Task InvokeAsync(HttpContext context)` — Processes an HTTP request to detect reverse proxy headers and validate server configuration

#### class `HordeServer.Server.ReverseProxyDetectionMiddlewareExtensions`  
`public static class ReverseProxyDetectionMiddlewareExtensions`  
_public; L52-61_
- desc: Extension methods for configuring the reverse proxy detection middleware.
- L57-60 _public method_ `public static IApplicationBuilder UseReverseProxyDetection(this IApplicationBuilder builder)` — Adds middleware to detect if the application is running behind a reverse proxy

### `Source/Programs/Horde/HordeServer/Server/SchemaController.cs` (HordeServer)


#### class `HordeServer.Server.SchemaController`  
`public class SchemaController : ControllerBase`  
_public; L19-116_
- attrs: `[ApiController] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/schema endpoint
- L40 _public property_ `public static Type[] ConfigSchemas { get; }` — Array of types included in the schema
- L42 _private* field_ `readonly JsonSchemaCache _schemaCache`
- L47-50 _public ctor_ `public SchemaController(JsonSchemaCache schemaCache)` — Constructor
- L52-66 _private* method_ `static Type[] FindSchemaTypes()`
- L74-91 _public method_ `public ActionResult GetCatalog()` — attrs: `[HttpGet] [Route("/api/v1/schema/catalog.json")]` — Get the catalog for config schema
- L100-115 _public method_ `public ActionResult GetSchema(string typeName)` — attrs: `[HttpGet] [Route("/api/v1/schema/types/{typeName}.json")]` — Gets a specific schema

#### class `HordeServer.Server.SchemaController.CatalogItem`  
`class CatalogItem`  
_private*; L21-27_
- L23 _public property_ `public string? Name { get; set; }`
- L24 _public property_ `public string? Description { get; set; }`
- L25 _public property_ `public string[]? FileMatch { get; set; }`
- L26 _public property_ `public Uri? Url { get; set; }`

#### class `HordeServer.Server.SchemaController.CatalogRoot`  
`class CatalogRoot`  
_private*; L29-35_
- L32 _public property_ `public string Schema { get; set; }` — attrs: `[JsonPropertyName("$schema")]`
- L33 _public property_ `public int Version { get; set; }`
- L34 _public property_ `public List<CatalogItem> Schemas { get; set; }`

### `Source/Programs/Horde/HordeServer/Server/ServerController.cs` (HordeServer)


#### class `HordeServer.Server.ServerController`  
`public class ServerController : HordeControllerBase`  
_public; L29-208_
- attrs: `[ApiController] [Authorize] [CppApi] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller managing account status
- L31 _private* field_ `readonly IAgentVersionProvider? _agentVersionProvider`
- L32 _private* field_ `readonly IPluginCollection _pluginCollection`
- L33 _private* field_ `readonly IServerInfo _serverInfo`
- L34 _private* field_ `readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L35 _private* field_ `readonly ILogger<ServerController> _logger`
- L40-47 _public ctor_ `public ServerController(IEnumerable<IAgentVersionProvider> agentVersionProviders, IPluginCollection pluginCollection, IServerInfo serverInfo, IOptionsSnapshot<GlobalConfig> globalConfig, ILogger<ServerController> logger)` — Constructor
- L55-59 _public method_ `public ActionResult GetVersion()` — attrs: `[HttpGet] [AllowAnonymous] [Route("/api/v1/server/version")]` — Get server version
- L68-90 _public method_ `public async Task<ActionResult<GetServerInfoResponse>> GetServerInfoAsync()` — attrs: `[HttpGet] [AllowAnonymous] [Route("/api/v1/server/info")] [ProducesResponseType(typeof(GetServerInfoResponse), 200)]` — Get server information
- L97-137 _private method_ `private string[]? GetUserAclsForPlugin(ILoadedPlugin plugin)` — Gets the list of ACL actions the current user has for a given plugin. Returns null if plugin doesn't support dashboard ACLs, or an array (possibly empty) of the user's granted ACL actions if it does.
- L145-151 _public method_ `public ActionResult<GetConnectionResponse> GetConnection()` — attrs: `[HttpGet] [AllowAnonymous] [Route("/api/v1/server/connection")]` — Gets connection information
- L159-168 _public method_ `public ActionResult<GetPortsResponse> GetPorts()` — attrs: `[HttpGet] [AllowAnonymous] [Route("/api/v1/server/ports")]` — Gets ports used by the server
- L170 _private const_ `private const string ServerAuthRoute = "/api/v1/server/auth"`
- L178-207 _public method_ `public ActionResult<GetAuthConfigResponse> GetAuthConfig()` — attrs: `[HttpGet] [AllowAnonymous] [Route(ServerAuthRoute)]` — Returns settings for automating auth against this server

### `Source/Programs/Horde/HordeServer/Server/ServerStatusController.cs` (HordeServer)


#### class `HordeServer.Server.ServerStatusUpdatesViewModel`  
`public class ServerStatusUpdatesViewModel`  
_public; L18-56_
- desc: ASP.NET view model for server status updates
- L23 _public property_ `public IReadOnlyList<SubsystemStatus> SubsystemStatuses { get; init; }` — Status for each subsystem
- L30-55 _public method_ `public static string ToRelativeTime(DateTimeOffset dateTime)` — Format a date/time to human-readable relative date

#### class `HordeServer.Server.ServerStatusController`  
`public class ServerStatusController : Controller`  
_public; L64-129_
- attrs: `[ApiController] [Authorize] [Tags("Server")]`
- inherits: `Controller`
- desc: Controller managing server status
- L66 _private field_ `private readonly ServerStatusService _serverStatus`
- L71-74 _public ctor_ `public ServerStatusController(ServerStatusService serverStatus)` — Constructor
- L83-109 _public method_ `public async Task<ActionResult<ServerStatusResponse>> GetUpdatesAsync([FromQuery] string? format = null)` — attrs: `[HttpGet] [Route("/api/v1/server/status")] [ProducesResponseType(typeof(ServerStatusResponse), 200)]` — Get the server status of Horde's internal subsystems
- L111-117 _private method_ `private ActionResult GetUpdatesHtml(IReadOnlyList<SubsystemStatus> subsystemStatuses)`
- L119-128 _private method_ `private static ServerStatusResult ConvertSubsystemResult(HealthStatus result)`

### `Source/Programs/Horde/HordeServer/Server/ServerStatusService.cs` (HordeServer)


#### class `HordeServer.Server.HealthMonitor`  
`internal class HealthMonitor<T> : IHealthMonitor<T>`  
_internal; L17-41_
- inherits: `IHealthMonitor<T>`
- L19 _private field_ `private readonly ServerStatusService _statusService`
- L20 _private field_ `private string _name`
- L22-24 _public ctor_ `public HealthMonitor(ServerStatusService statusService) : this(statusService, typeof(T).Name)`
- L26-30 _public ctor_ `public HealthMonitor(ServerStatusService statusService, string name)`
- L32-35 _public method_ `public void SetName(string name)`
- L37-40 _public method_ `public async Task UpdateAsync(HealthStatus result, string? message, DateTimeOffset? timestamp)`

#### record `HordeServer.Server.SubsystemStatus`  
`public record SubsystemStatus(string Id, string Name, List<SubsystemStatusUpdate> Updates)`  
_public; L49-57_
- desc: Represents status of a subsystem inside Horde
- L52-56 _public method_ `public override string ToString()` — (inheritdoc)

#### record `HordeServer.Server.SubsystemStatusUpdate`  
`public record SubsystemStatusUpdate(HealthStatus Result, string? Message, DateTimeOffset UpdatedAt)`  
_public; L65-65_
- desc: An individual status update for a subsystem

#### class `HordeServer.Server.ServerStatusService`  
`public class ServerStatusService : IHostedService`  
_public; L71-209_
- inherits: `IHostedService`
- desc: Tracks health and status of the Horde server itself Such as connectivity to external systems (MongoDB, Redis, Perforce etc).
- L76 _public const_ `public const int MaxHistoryLength = 10` — Max historical status updates to keep
- L78 _private field_ `private readonly IClock _clock`
- L79 _private field_ `private readonly IMongoService _mongoService`
- L80 _private field_ `private readonly IRedisService _redisService`
- L82 _private field_ `private readonly IHealthMonitor<MongoService> _mongoDbHealth`
- L83 _private field_ `private readonly ITicker _mongoDbHealthTicker`
- L85 _private field_ `private readonly IHealthMonitor<RedisService> _redisHealth`
- L86 _private field_ `private readonly ITicker _redisHealthTicker`
- L88 _private method_ `private static string RedisHashKey()`
- L97-108 _public ctor_ `public ServerStatusService(IMongoService mongoService, IRedisService redisService, IClock clock, ILogger<ServerStatusService> logger)` — Constructor
- L111-115 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L118-122 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L127-131 _internal method_ `internal async ValueTask UpdateMongoDbHealthAsync(CancellationToken cancellationToken)` — Checks health and connectivity to MongoDB database
- L136-140 _internal method_ `internal async ValueTask UpdateRedisHealthAsync(CancellationToken cancellationToken)` — Checks health and connectivity to Redis database
- L150-169 _public method_ `public async Task ReportAsync(Type type, string name, HealthStatus result, string? message = null, DateTimeOffset? timestamp = null)` — Report a status update for a given subsystem
- L171-187 _private method_ `private static async Task<SubsystemStatus> GetSubsystemStatusFromRedisAsync(IDatabase redis, string id, string name)`
- L193-208 _public method_ `public async Task<IReadOnlyList<SubsystemStatus>> GetSubsystemStatusesAsync()` — Get a list of status and updates for each subsystem

### `Source/Programs/Horde/HordeServer/ServerApp.cs` (HordeServer)


#### class `HordeServer.LoggerExtensions`  
`static class LoggerExtensions`  
_internal*; L37-78_
- L47-66 _public method_ `public static LoggerConfiguration Console(this LoggerSinkConfiguration sinkConfig, ServerSettings settings)`
- L68-77 _public method_ `public static LoggerConfiguration WithHordeConfig(this LoggerConfiguration configuration, ServerSettings settings)`

#### class `HordeServer.LoggerExtensions.DatadogVersionLogEnricher`  
`class DatadogVersionLogEnricher : Serilog.Core.ILogEventEnricher`  
_private*; L39-45_
- inherits: `Serilog.Core.ILogEventEnricher`
- L41-44 _public method_ `public void Enrich(Serilog.Events.LogEvent logEvent, Serilog.Core.ILogEventPropertyFactory propertyFactory)`

#### class `HordeServer.ServerApp`  
`class ServerApp`  
_internal*; L80-508_
- L82 _public property_ `public static SemVer Version { get; }`
- L84 _public property_ `public static string DeploymentEnvironment { get; }`
- L86 _public property_ `public static string SessionId { get; }`
- L88 _public property_ `public static DirectoryReference AppDir { get; }`
- L90 _public property_ `public static DirectoryReference DataDir => ...`
- L92 _public property_ `public static DirectoryReference ConfigDir => ...`
- L94 _public property_ `public static FileReference ServerConfigFile => ...`
- L96 _public field_ `public static Type[] ConfigSchemas = FindSchemaTypes()`
- L98 _public property_ `public static IPluginCollection Plugins => ...`
- L100 _private field_ `private static DirectoryReference s_dataDir = DirectoryReference.Combine(GetAppDir(), "Data")`
- L101 _private field_ `private static DirectoryReference s_configDir = DirectoryReference.Combine(GetAppDir(), "Defaults")`
- L102 _private field_ `private static FileReference? s_serverConfigFile`
- L103 _private field_ `private static IPluginCollection? s_pluginCollection`
- L105-116 _private* method_ `static Type[] FindSchemaTypes()`
- L118-129 _private* method_ `static SemVer GetVersion()`
- L131-235 _public method_ `public static async Task<int> Main(string[] args)`
- L237-240 _internal method_ `internal static void InitializePluginsForTests()`
- L254-319 _private* method_ `static IPluginCollection CreatePluginCollection(IConfiguration configuration, ILogger logger)` — Creates a plugin collection by loading and configuring plugins from assemblies based on configuration settings. The method performs the following steps: 1. Loads plugin configurations from the "Horde.Plugins" configuration section 2. Scans the application directory for DLL files matching the pattern "HordeServer.*.dll" 3. Loads each matching assembly and searches for types decorated with PluginAttribute 4. Enables plugins based on configuration settings and default values 5. Validates that all plugins enabled in configuration are found
- L322 _public method_ `public static IHostBuilder CreateHostBuilder(string[] args)`
- L328-336 _private* method_ `static string GetEnvironment()` — Gets the current environment
- L342-345 _private* method_ `static DirectoryReference GetAppDir()` — Get the application directory
- L350 _private* field_ `static readonly KeyValuePair<string, string>[] s_renamedConfigValues = ...` — List of config settings to rename to new locations
- L350 _private* field_ `static readonly KeyValuePair< s_renamedConfigValues = new[] { KeyValuePair.Create("Horde:UseLocalPerforceEnv", "Horde:Plugins:Build:UseLocalPerforceEnv"), KeyValuePair.Create("Horde:PerforceConnectionPoolSize", "Horde:Plugins:Build:PerforceConnectionPool ...` — List of config settings to rename to new locations
- L411-486 _private* method_ `static IConfiguration CreateConfig(bool readInstalledConfig, FileReference? serverConfigFile)` — Constructs a configuration object for the current environment
- L488-507 _private* method_ `static async Task CopyDefaultConfigFilesAsync(DirectoryReference sourceDir, DirectoryReference targetDir, CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeServer/ServerInfo.cs` (HordeServer)


#### class `HordeServer.ServerInfo`  
`class ServerInfo : IServerInfo`  
_internal*; L13-60_
- inherits: `IServerInfo`
- desc: Concrete implementation of IServerInfo
- L16 _public property_ `public SemVer Version => ...` — (inheritdoc)
- L19 _public property_ `public string Environment => ...` — (inheritdoc)
- L22 _public property_ `public string SessionId => ...` — (inheritdoc)
- L25 _public property_ `public DirectoryReference AppDir => ...` — (inheritdoc)
- L28 _public property_ `public DirectoryReference DataDir => ...` — (inheritdoc)
- L31 _public property_ `public IConfiguration Configuration => ...` — (inheritdoc)
- L34 _public property_ `public bool EnableDebugEndpoints => ...` — (inheritdoc)
- L37 _public property_ `public bool ReadOnlyMode => ...` — (inheritdoc)
- L40 _public property_ `public Uri ServerUrl => ...` — (inheritdoc)
- L43 _public property_ `public Uri DashboardUrl => ...` — (inheritdoc)
- L45 _private* field_ `readonly IConfiguration _configuration`
- L46 _private* field_ `readonly IOptions<ServerSettings> _serverSettings`
- L51-55 _public ctor_ `public ServerInfo(IConfiguration configuration, IOptions<ServerSettings> serverSettings)` — Constructor
- L58 _public method_ `public bool IsRunModeActive(RunMode mode)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/ServerSettings.cs` (HordeServer)


#### class `HordeServer.FeatureFlagSettings`  
`public class FeatureFlagSettings`  
_public; L21-23_
- desc: Feature flags to aid rollout of new features. Once a feature is running in its intended state and is stable, the flag should be removed. A name and date of when the flag was created is noted next to it to help encourage this behavior. Try having them be just a flag, a boolean.

#### class `HordeServer.ServerSettings`  
`public class ServerSettings`  
_public; L31-498_
- attrs: `[ConfigDoc("Server.json", "[Horde](../../README.md) > [Deployment](../Deployment.md) > [Server](Server.md)", "Deployment/ServerSettings.md", Introduction = "All Horde-specific settings are stored in a root object called 'Horde'. Other .NET functionality may be configured using properties in the root of this file." )]`
- desc: Global settings for the application
- L36 _public const_ `public const string SectionName = "Horde"` — Name of the section containing these settings
- L41 _public property_ `public RunMode[]? RunModes { get; set; }` — Modes that the server should run in. Runmodes can be used in a multi-server deployment to limit the operations that a particular instance will try to perform.
- L46 _public property_ `public string? DataDir { get; set; }` — Override the data directory used by Horde. Defaults to C:\ProgramData\HordeServer on Windows, {AppDir}/Data on other platforms.
- L53 _public property_ `public bool Installed { get; set; }` — Whether the server is running in 'installed' mode. In this mode, on Windows, the default data directory will use the common application data folder (C:\ProgramData\Epic\Horde), and configuration data will be read from here and the registry. This setting is overridden to false for local builds from appsettings.Local.json.
- L58 _public property_ `public int HttpPort { get; set; }` — Main port for serving HTTP.
- L63 _public property_ `public int HttpsPort { get; set; }` — Port for serving HTTP with TLS enabled. Disabled by default.
- L68 _public property_ `public int Http2Port { get; set; }` — Dedicated port for serving only HTTP/2.
- L73 _public property_ `public string? MongoConnectionString { get; set; }` — Connection string for the Mongo database
- L79-83 _public property_ `public string? DatabaseConnectionString { get; set; }` — attrs: `[Obsolete("Use MongoConnectionString instead")]` — MongoDB connection string
- L88 _public property_ `public string MongoDatabaseName { get; set; }` — MongoDB database name
- L92-96 _public property_ `public string DatabaseName { get; set; }` — attrs: `[Obsolete("Replace references to DatabaseName with MongoDatabaseName")]` — (inheritdoc)
- L101 _public property_ `public string? MongoPublicCertificate { get; set; }` — Optional certificate to trust in order to access the database (eg. AWS public cert for TLS)
- L105-109 _public property_ `public string? DatabasePublicCert { get; set; }` — attrs: `[Obsolete("Replace DatabasePublicCert with MongoPublicCertificate")]` — (inheritdoc)
- L115 _public property_ `public bool MongoReadOnlyMode { get; set; }` — Access the database in read-only mode (avoids creating indices or updating content) Useful for debugging a local instance of HordeServer against a production database.
- L119-123 _public property_ `public bool DatabaseReadOnlyMode { get; set; }` — attrs: `[Obsolete("Replace DatabaseReadOnlyMode with MongoReadOnlyMode")]` — (inheritdoc)
- L128 _public property_ `public bool MongoMigrationsEnabled { get; set; }` — Whether database schema migrations are enabled
- L134 _public property_ `public bool MongoMigrationsAutoUpgrade { get; set; }` — Whether database schema should automatically be applied Only recommended for dev or test environments
- L147 _public property_ `public int? ShutdownMemoryThreshold { get; set; }` — Shutdown the current server process if memory usage reaches this threshold (specified in MB) Usually set to 80-90% of available memory to avoid CLR heap using all of it. If a memory leak was to occur, it's usually better to restart the process rather than to let the GC work harder and harder trying to recoup memory. Should only be used when multiple server processes are running behind a load balancer and one can be safely restarted automatically by the underlying process handler (Docker, Kubernetes, AWS ECS, Supervisor etc). The shutdown behaves similar to receiving a SIGTERM and will wait for outstanding requests to finish.
- L152 _public property_ `public string? ServerPrivateCert { get; set; }` — Optional PFX certificate to use for encrypting agent SSL traffic. This can be a self-signed certificate, as long as it's trusted by agents.
- L159 _public property_ `public AuthMethod AuthMethod { get; set; }` — Type of authentication (e.g anonymous, OIDC, built-in Horde accounts) If "Horde" auth mode is used, be sure to configure "ServerUrl" as well.
- L165 _public property_ `public string? OidcProfileName { get; set; }` — Optional profile name to report through the /api/v1/server/auth endpoint. Allows sharing auth tokens between providers configured through the same profile name in OidcToken.exe config files.
- L170 _public property_ `public string? OidcAuthority { get; set; }` — OpenID Connect (OIDC) authority URL (required when OIDC is enabled)
- L175 _public property_ `public string? OidcAudience { get; set; }` — Audience for validating externally issued tokens (required when OIDC is enabled)
- L180 _public property_ `public string? OidcClientId { get; set; }` — Client ID for the OIDC authority (required when OIDC is enabled)
- L188 _public property_ `public string? OidcClientSecret { get; set; }` — Client secret for authenticating with the OIDC provider. Note: If you need authentication support in Unreal Build Tool or Unreal Game Sync, configure your OIDC client as a public client (using PKCE flow without a client secret) instead of a confidential client. These tools utilize the EpicGames.OIDC library which only supports public clients with authorization code flow + PKCE.
- L193 _public property_ `public string? OidcSigninRedirect { get; set; }` — Optional redirect url provided to OIDC login
- L199 _public property_ `public string[]? OidcLocalRedirectUrls { get; set; }` — Optional redirect url provided to OIDC login for external tools (typically to a local server) Default value is the local web server started during signin by EpicGames.OIDC library
- L206 _public property_ `public bool OidcDebugMode { get; set; }` — Debug mode for OIDC which logs reasons for why JWT tokens fail to authenticate Also turns off HTTPS requirement for OIDC metadata fetching. NOT FOR PRODUCTION USE!
- L211 _public property_ `public string[] OidcRequestedScopes { get; set; }` — OpenID Connect scopes to request when signing in
- L216 _public property_ `public string[] OidcClaimNameMapping { get; set; }` — List of fields in /userinfo endpoint to try map to the standard name claim (see System.Security.Claims.ClaimTypes.Name)
- L221 _public property_ `public string[] OidcClaimEmailMapping { get; set; }` — List of fields in /userinfo endpoint to try map to the standard email claim (see System.Security.Claims.ClaimTypes.Email)
- L226 _public property_ `public string[] OidcClaimHordeUserMapping { get; set; }` — List of fields in /userinfo endpoint to try map to the Horde user claim (see HordeClaimTypes.User)
- L231 _public property_ `public string[] OidcClaimHordePerforceUserMapping { get; set; }` — List of fields in /userinfo endpoint to try map to the Horde Perforce user claim (see HordeClaimTypes.PerforceUser)
- L236 _public property_ `public string[] OidcApiRequestedScopes { get; set; }` — API scopes to request when acquiring OIDC access tokens
- L249 _public property_ `public bool OidcAddDefaultScopesAndMappings { get; set; }` — Add common scopes and mappings to above OIDC config fields Provided as a workaround since .NET config will only *merge* array entries when combining multiple config sources. Due to this unwanted behavior, having hard-coded defaults makes such fields unchangeable. See https://github.com/dotnet/runtime/issues/36569 OidcRequestedScopes OidcClaimNameMapping OidcClaimEmailMapping OidcClaimHordeUserMapping OidcClaimHordePerforceUserMapping
- L255-271 _public method_ `public void AddDefaultOidcScopesAndMappings()` — Adds default scopes and claim mappings to the OIDC configuration if enabled. This method should be called after the initial configuration is loaded.
- L279-283 _public property_ `public Uri ServerUrl { get; set; }` — Base URL this Horde server is accessible from For example https://horde.mystudio.com. If not set, a default is used based on current hostname. It's important this URL matches where users and agents access the server as it's used for signing auth tokens etc. Must be configured manually when running behind a reverse proxy or load balancer
- L288-292 _public property_ `public string? JwtIssuer { get; set; }` — Name of the issuer in bearer tokens from the server
- L294 _internal method_ `internal bool IsDefaultServerUrlUsed()`
- L296 _private* field_ `Uri? _serverUrl`
- L297 _private* field_ `string? _jwtIssuer`
- L299-318 _private* method_ `Uri GetDefaultServerUrl()`
- L323 _public property_ `public int JwtExpiryTimeHours { get; set; }` — Length of time before JWT tokens expire, in hours
- L328 _public property_ `public int ExtendedJwtExpiryTimeHours { get; set; }` — Length of time before extended JWT tokens expire, in hours, defaults to 1 week
- L333 _public property_ `public string? AdminClaimType { get; set; }` — The claim type for administrators
- L338 _public property_ `public string? AdminClaimValue { get; set; }` — Value of the claim type for administrators
- L343 _public property_ `public bool CorsEnabled { get; set; }` — Whether to enable Cors, generally for development purposes
- L348 _public property_ `public string CorsOrigin { get; set; }` — Allowed Cors origin
- L353 _public property_ `public bool EnableDebugEndpoints { get; set; }` — Whether to enable debug/administrative REST API endpoints
- L358 _public property_ `public bool EnableNewAgentsByDefault { get; set; }` — Whether to automatically enable new agents by default. If false, new agents must manually be enabled before they can take on work.
- L363 _public property_ `public TimeSpan SchedulePollingInterval { get; set; }` — Interval between rebuilding the schedule queue with a DB query.
- L368 _public property_ `public TimeSpan NoResourceBackOffTime { get; set; }` — Interval between polling for new jobs
- L373 _public property_ `public TimeSpan InitiateJobBackOffTime { get; set; }` — Interval between attempting to assign agents to take on jobs
- L378 _public property_ `public TimeSpan UnknownErrorBackOffTime { get; set; }` — Interval between scheduling jobs when an unknown error occurs
- L385 _public property_ `public string? RedisConnectionString { get; set; }` — Config for connecting to Redis server(s). Setting it to null will disable Redis use and connection See format at https://stackexchange.github.io/StackExchange.Redis/Configuration.html
- L389-393 _public property_ `public string? RedisConnectionConfig { get; set; }` — attrs: `[Obsolete("Use RedisConnectionString instead")]` — (inheritdoc)
- L398 _public property_ `public bool RedisReadOnlyMode { get; set; }` — Whether to disable writes to Redis.
- L403 _public property_ `public string LogServiceWriteCacheType { get; set; }` — Overridden settings for storage backends. Useful for running against a production server with custom backends.
- L408 _public property_ `public bool LogJsonToStdOut { get; set; }` — Whether to log json to stdout
- L413 _public property_ `public bool LogSessionRequests { get; set; }` — Whether to log requests to the UpdateSession and QueryServerState RPC endpoints
- L418 _public property_ `public string? ScheduleTimeZone { get; set; }` — Timezone for evaluating schedules
- L423 _public property_ `public Uri DashboardUrl { get; set; }` — The URl to use for generating links back to the dashboard.
- L428 _public property_ `public string? HelpEmailAddress { get; set; }` — Help email address that users can contact with issues
- L433 _public property_ `public string? HelpSlackChannel { get; set; }` — Help slack channel that users can use for issues
- L441 _public property_ `public int? GlobalThreadPoolMinSize { get; set; }` — Set the minimum size of the global thread pool This value has been found in need of tweaking to avoid timeouts with the Redis client during bursts of traffic. Default is 16 for .NET Core CLR. The correct value is dependent on the traffic the Horde Server is receiving. For Epic's internal deployment, this is set to 40.
- L446 _public property_ `public string ConfigPath { get; set; }` — Path to the root config file. Relative to the server.json file by default.
- L451 _public property_ `public bool ForceConfigUpdateOnStartup { get; set; }` — Forces configuration data to be read and updated as part of appplication startup, rather than on a schedule. Useful when running locally.
- L456 _public property_ `public bool OpenBrowser { get; set; }` — Whether to open a browser on startup
- L461 _public property_ `public FeatureFlagSettings FeatureFlags { get; set; }` — Experimental features to enable on the server.
- L466 _public property_ `public OpenTelemetrySettings OpenTelemetry { get; set; }` — Options for OpenTelemetry
- L473-480 _public method_ `public bool IsRunModeActive(RunMode mode)` — Helper method to check if this process has activated the given mode
- L486-497 _public method_ `public void Validate(ILogger? logger = null)` — Validate the settings object does not contain any invalid fields

### `Source/Programs/Horde/HordeServer/ServiceAccounts/IServiceAccount.cs` (HordeServer)


#### interface `HordeServer.ServiceAccounts.IServiceAccount`  
`public interface IServiceAccount`  
_public; L18-60_
- desc: An internal Horde account representing a service Service-to-service authentication always use this for authentication (for example, Robomerge accessing Horde).
- L23 _public* property_ `ServiceAccountId Id { get; }` — Unique internal ID for this Horde account
- L28 _public* property_ `string Name { get; }` — Human-readable name for identifying this account
- L33 _public* property_ `string Description { get; }` — Description of the account (who is it for, is there an owner etc)
- L39 _public* property_ `IReadOnlyList<IUserClaim> Claims { get; }` — Get list of claims
- L44 _public* property_ `bool Enabled { get; }` — If the account is active
- L51 _public* method_ `Task<IServiceAccount?> RefreshAsync(CancellationToken cancellationToken = default)` — Get the latest version of this account
- L59 _public* method_ `Task<(IServiceAccount?, string?)> TryUpdateAsync(UpdateServiceAccountOptions options, CancellationToken cancellationToken = default)` — Attempt to update settings for the account

#### record `HordeServer.ServiceAccounts.UpdateServiceAccountOptions`  
`public record UpdateServiceAccountOptions( string? Name = null, string? Description = null, IReadOnlyList<IUserClaim>? Claims = null, bool? ResetToken = null, bool? Enabled = null)`  
_public; L70-70_
- desc: Options for updating an account

#### class `HordeServer.ServiceAccounts.AccountExtensions`  
`public static class AccountExtensions`  
_public; L80-132_
- desc: Extension methods for accounts
- L89-99 _public method_ `public static bool HasClaim(this IServiceAccount account, string type, string value)` — Test whether a user has a particular claim
- L107 _public method_ `public static bool HasClaim(this IServiceAccount account, AclClaimConfig claim)` — Test whether a user has a particular claim
- L117-131 _public method_ `public static async Task<(IServiceAccount?, string?)> UpdateAsync(this IServiceAccount account, UpdateServiceAccountOptions options, CancellationToken cancellationToken = default)` — Update settings for the account, retrying if the account object has changed

### `Source/Programs/Horde/HordeServer/ServiceAccounts/IServiceAccountCollection.cs` (HordeServer)


#### interface `HordeServer.ServiceAccounts.IServiceAccountCollection`  
`public interface IServiceAccountCollection`  
_public; L14-55_
- desc: Interface for a collection of accounts
- L21 _public* method_ `Task<(IServiceAccount, string)> CreateAsync(CreateServiceAccountOptions options, CancellationToken cancellationToken = default)` — Adds a new account to the collection
- L30 _public* method_ `Task<IReadOnlyList<IServiceAccount>> FindAsync(int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Searches service accounts
- L38 _public* method_ `Task<IServiceAccount?> FindBySecretTokenAsync(string secretToken, CancellationToken cancellationToken = default)` — Get service account via secret token
- L46 _public* method_ `Task<IServiceAccount?> GetAsync(ServiceAccountId id, CancellationToken cancellationToken = default)` — Get service account via ID
- L54 _public* method_ `Task DeleteAsync(ServiceAccountId id, CancellationToken cancellationToken = default)` — Delete a service account from the collection

#### record `HordeServer.ServiceAccounts.CreateServiceAccountOptions`  
`public record CreateServiceAccountOptions(string Name, string Description, IReadOnlyList<IUserClaim>? Claims = null, bool? Enabled = null)`  
_public; L64-64_
- desc: Options for creating a new service account

### `Source/Programs/Horde/HordeServer/ServiceAccounts/ServiceAccountAclAction.cs` (HordeServer)


#### class `HordeServer.ServiceAccounts.ServiceAccountAclAction`  
`public static class ServiceAccountAclAction`  
_public; L10-31_
- desc: ACL actions valid for manipulating jobs
- L15 _public property_ `public static AclAction CreateAccount { get; }` — Ability to create new accounts
- L20 _public property_ `public static AclAction UpdateAccount { get; }` — Update an account settings
- L25 _public property_ `public static AclAction DeleteAccount { get; }` — Delete an account from the server
- L30 _public property_ `public static AclAction ViewAccount { get; }` — Ability to view account information

### `Source/Programs/Horde/HordeServer/ServiceAccounts/ServiceAccountCollection.cs` (HordeServer)


#### class `HordeServer.ServiceAccounts.ServiceAccountCollection`  
`public class ServiceAccountCollection : IServiceAccountCollection`  
_public; L23-205_
- inherits: `IServiceAccountCollection`
- desc: Collection of service account documents
- L89 _private field_ `private readonly IMongoCollection<ServiceAccountDocument> _accounts`
- L95-98 _public ctor_ `public ServiceAccountCollection(IMongoService mongoService)` — Constructor
- L100 _private* method_ `static string CreateToken()`
- L104-122 _public method_ `public async Task<(IServiceAccount, string)> CreateAsync(CreateServiceAccountOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L125-135 _public method_ `public async Task<IReadOnlyList<IServiceAccount>> FindAsync(int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L138-143 _public method_ `public async Task<IServiceAccount?> GetAsync(ServiceAccountId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L146-151 _public method_ `public async Task<IServiceAccount?> FindBySecretTokenAsync(string secretToken, CancellationToken cancellationToken = default)` — (inheritdoc)
- L154-198 _private* method_ `async Task<(ServiceAccountDocument?, string?)> TryUpdateAsync(ServiceAccountDocument document, UpdateServiceAccountOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L201-204 _public method_ `public Task DeleteAsync(ServiceAccountId id, CancellationToken cancellationToken = default)` — (inheritdoc)

#### record `HordeServer.ServiceAccounts.ServiceAccountCollection.ClaimDocument`  
`record class ClaimDocument(string Type, string Value) : IUserClaim`  
_private*; L25-32_
- inherits: `IUserClaim`
- L27-28 _public ctor_ `public ClaimDocument(IUserClaim claim) : this(claim.Type, claim.Value)`
- L30-31 _public ctor_ `public ClaimDocument(AclClaimConfig claim) : this(claim.Type, claim.Value)`

#### class `HordeServer.ServiceAccounts.ServiceAccountCollection.ServiceAccountDocument`  
`private class ServiceAccountDocument : IServiceAccount`  
_private; L37-87_
- inherits: `IServiceAccount`
- desc: Concrete implementation of IHordeAccount
- L40 _private* field_ `ServiceAccountCollection? _accountCollection` — attrs: `[BsonIgnore]`
- L44 _public property_ `public ServiceAccountId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — (inheritdoc)
- L47 _public property_ `public string Name { get; set; }` — (inheritdoc)
- L49 _public property_ `public string SecretToken { get; set; }`
- L52 _public property_ `public List<ClaimDocument> Claims { get; set; }` — attrs: `[BsonElement("Claims2")]`
- L55 _public property_ `public bool Enabled { get; set; }` — (inheritdoc)
- L58 _public property_ `public string Description { get; set; }` — (inheritdoc)
- L61 _public property_ `public int UpdateIndex { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(0)]`
- L63 _private* property_ `IReadOnlyList<IUserClaim> IServiceAccount.Claims => ...`
- L66-68 _private ctor_ `private ServiceAccountDocument()` — attrs: `[BsonConstructor]`
- L70-75 _public ctor_ `public ServiceAccountDocument(ServiceAccountId id, string name, string description)`
- L77-80 _public method_ `public void PostLoad(ServiceAccountCollection accountCollection)`
- L82 _public method_ `public async Task<IServiceAccount?> RefreshAsync(CancellationToken cancellationToken)`
- L85 _public method_ `public async Task<(IServiceAccount?, string?)> TryUpdateAsync(UpdateServiceAccountOptions options, CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeServer/ServiceAccounts/ServiceAccountsController.cs` (HordeServer)


#### class `HordeServer.ServiceAccounts.ServiceAccountsController`  
`public class ServiceAccountsController : HordeControllerBase`  
_public; L23-190_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/serviceaccounts endpoint
- L25 _private* field_ `readonly IServiceAccountCollection _serviceAccountCollection`
- L26 _private* field_ `readonly GlobalConfig _globalConfig`
- L31-35 _public ctor_ `public ServiceAccountsController(IServiceAccountCollection accountCollection, IOptionsSnapshot<GlobalConfig> globalConfig)` — Constructor
- L43-54 _public method_ `public async Task<ActionResult<CreateServiceAccountResponse>> CreateServiceAccountAsync([FromBody] CreateServiceAccountRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/serviceaccounts")] [ProducesResponseType(typeof(CreateServiceAccountResponse), 200)]` — Create a new service account
- L62-78 _public method_ `public async Task<ActionResult<List<GetServiceAccountResponse>>> FindAccountsAsync([FromQuery] int? index = null, [FromQuery] int? count = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/serviceaccounts")] [ProducesResponseType(typeof(List<GetServiceAccountResponse>), 200)]` — Gets a list of accounts
- L87-102 _public method_ `public async Task<ActionResult<object>> GetAccountAsync(ServiceAccountId id, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/serviceaccounts/{id}")] [ProducesResponseType(typeof(GetServiceAccountResponse), 200)] [ProducesResponseType(404)]` — Gets information about an account by id
- L111-126 _public method_ `public async Task<ActionResult<object>> GetAccountEntitlementsAsync(ServiceAccountId id, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/serviceaccounts/{id}/entitlements")] [ProducesResponseType(typeof(GetAccountEntitlementsResponse), 200)] [ProducesResponseType(404)]` — Gets information about the current account
- L135-162 _public method_ `public async Task<ActionResult<UpdateServiceAccountResponse>> UpdateAccountAsync(ServiceAccountId id, UpdateServiceAccountRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/serviceaccounts/{id}")] [ProducesResponseType(200)] [ProducesResponseType(404)]` — Updates an account by id
- L170-179 _public method_ `public async Task<ActionResult> DeleteAccountAsync(ServiceAccountId id, CancellationToken cancellationToken = default)` — attrs: `[HttpDelete] [Route("/api/v1/serviceaccounts/{id}")] [ProducesResponseType(200)]` — Deletes an account by id
- L181-189 _private* method_ `static GetServiceAccountResponse CreateGetAccountResponse(IServiceAccount account)`

### `Source/Programs/Horde/HordeServer/Startup.cs` (HordeServer)


#### class `HordeServer.Startup`  
`class Startup : IServerStartup`  
_internal*; L89-1163_
- inherits: `IServerStartup`
- L91-95 _private* ctor_ `static Startup()`
- L210-213 _public ctor_ `public Startup(IConfiguration configuration)`
- L215 _public property_ `public IConfiguration Configuration { get; }`
- L217-223 _public method_ `public static void BindServerSettings(IConfiguration configuration, ServerSettings settings, ILogger? logger = null)`
- L256-656 _public method_ `public void ConfigureServices(IServiceCollection services)`
- L658-677 _private method_ `private static void ValidateOidcSettings(ServerSettings settings)`
- L679-686 _public method_ `public static void ConfigureFormatters()`
- L913 _private* field_ `static int s_haveConfiguredMongoDb = 0`
- L915-944 _public method_ `public static void ConfigureMongoDbClient()`
- L946-952 _private method_ `private static void OnAddHealthChecks(IServiceCollection services)`
- L955-1050 _public method_ `public static void Configure(IApplicationBuilder app, IWebHostEnvironment env, Microsoft.Extensions.Hosting.IHostApplicationLifetime lifetime, IOptions<ServerSettings> settings)`
- L1052-1055 _private* method_ `static bool IsSpaRequest(HttpContext context)`
- L1057-1066 _private* method_ `static void LaunchBrowser(IApplicationBuilder app)`
- L1068-1130 _private* method_ `static LogEventLevel GetRequestLoggingLevel(HttpContext context, double elapsedMs, Exception? ex)`
- L1141-1146 _public method_ `public static void AddServices(IServiceCollection serviceCollection, IConfiguration configuration)`
- L1148-1153 _public method_ `public static ServiceCollection CreateServiceCollection(IConfiguration configuration)`
- L1155-1162 _public method_ `public static ServiceCollection CreateServiceCollection(IConfiguration configuration, ILoggerProvider loggerProvider)`

#### class `HordeServer.Startup.GrpcExceptionInterceptor`  
`class GrpcExceptionInterceptor : Interceptor`  
_private*; L97-174_
- inherits: `Interceptor`
- L99 _private* field_ `readonly ILogger<GrpcExceptionInterceptor> _logger`
- L101-104 _public ctor_ `public GrpcExceptionInterceptor(ILogger<GrpcExceptionInterceptor> logger)`
- L106-109 _public method_ `public override Task<TResponse> UnaryServerHandler<TRequest, TResponse>(TRequest request, ServerCallContext context, UnaryServerMethod<TRequest, TResponse> continuation)`
- L111-114 _public method_ `public override Task<TResponse> ClientStreamingServerHandler<TRequest, TResponse>(IAsyncStreamReader<TRequest> requestStream, ServerCallContext context, ClientStreamingServerMethod<TRequest, TResponse> continuation) where TRequest : class where TResponse : class`
- L116-119 _public method_ `public override Task ServerStreamingServerHandler<TRequest, TResponse>(TRequest request, IServerStreamWriter<TResponse> responseStream, ServerCallContext context, ServerStreamingServerMethod<TRequest, TResponse> continuation) where TRequest : class where TResponse : class`
- L121-124 _public method_ `public override Task DuplexStreamingServerHandler<TRequest, TResponse>(IAsyncStreamReader<TRequest> requestStream, IServerStreamWriter<TResponse> responseStream, ServerCallContext context, DuplexStreamingServerMethod<TRequest, TResponse> continuation) where TRequest : class where TResponse : class`
- L126-131 _private* method_ `async Task<T> GuardAsync<T>(ServerCallContext context, Func<Task<T>> callFunc) where T : class`
- L133-148 _private* method_ `async Task GuardAsync(ServerCallContext context, Func<Task> callFunc)`
- L150-173 _private* method_ `async Task GuardInnerAsync(ServerCallContext context, Func<Task> callFunc)`

#### class `HordeServer.Startup.BsonSerializationProvider`  
`class BsonSerializationProvider : IBsonSerializationProvider`  
_private*; L176-190_
- inherits: `IBsonSerializationProvider`
- L178-189 _public method_ `public IBsonSerializer? GetSerializer(Type type)`

#### class `HordeServer.Startup.ObsoleteLoggingFilter`  
`class ObsoleteLoggingFilter : IActionFilter`  
_private*; L192-208_
- inherits: `IActionFilter`
- L194-196 _public method_ `public void OnActionExecuted(ActionExecutedContext context)`
- L198-207 _public method_ `public void OnActionExecuting(ActionExecutingContext context)`

#### class `HordeServer.Startup.AgentIdRedisConverter`  
`sealed class AgentIdRedisConverter : IRedisConverter<AgentId>`  
_private*; L228-235_
- inherits: `IRedisConverter<AgentId>`
- desc: Converter to/from Redis values
- L231 _public method_ `public AgentId FromRedisValue(RedisValue value)` — (inheritdoc)
- L234 _public method_ `public RedisValue ToRedisValue(AgentId value)` — (inheritdoc)

#### class `HordeServer.Startup.SwaggerSchemaFilter`  
`class SwaggerSchemaFilter : ISchemaFilter`  
_private*; L240-253_
- inherits: `ISchemaFilter`
- desc: Configure custom types for the public API documentation
- L242-252 _public method_ `public void Apply(OpenApiSchema schema, SchemaFilterContext context)`

#### class `HordeServer.Startup.CommitIdBsonSerializer`  
`public sealed class CommitIdBsonSerializer : SerializerBase<CommitId>`  
_public; L688-708_
- inherits: `SerializerBase<CommitId>`
- L691-701 _public method_ `public override CommitId Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L704-707 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, CommitId value)` — (inheritdoc)

#### class `HordeServer.Startup.BlobLocatorBsonSerializer`  
`public sealed class BlobLocatorBsonSerializer : SerializerBase<BlobLocator>`  
_public; L710-723_
- inherits: `SerializerBase<BlobLocator>`
- L713-716 _public method_ `public override BlobLocator Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L719-722 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, BlobLocator value)` — (inheritdoc)

#### class `HordeServer.Startup.RefNameBsonSerializer`  
`public sealed class RefNameBsonSerializer : SerializerBase<RefName>`  
_public; L725-738_
- inherits: `SerializerBase<RefName>`
- L728-731 _public method_ `public override RefName Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L734-737 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, RefName value)` — (inheritdoc)

#### class `HordeServer.Startup.IoHashBsonSerializer`  
`public sealed class IoHashBsonSerializer : SerializerBase<IoHash>`  
_public; L740-753_
- inherits: `SerializerBase<IoHash>`
- L743-746 _public method_ `public override IoHash Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L749-752 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, IoHash value)` — (inheritdoc)

#### class `HordeServer.Startup.NamespaceIdBsonSerializer`  
`public sealed class NamespaceIdBsonSerializer : SerializerBase<NamespaceId>`  
_public; L755-768_
- inherits: `SerializerBase<NamespaceId>`
- L758-761 _public method_ `public override NamespaceId Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L764-767 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, NamespaceId value)` — (inheritdoc)

#### class `HordeServer.Startup.AgentIdBsonSerializer`  
`public sealed class AgentIdBsonSerializer : SerializerBase<AgentId>`  
_public; L770-792_
- inherits: `SerializerBase<AgentId>`
- L773-785 _public method_ `public override AgentId Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L788-791 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, AgentId value)` — (inheritdoc)

#### class `HordeServer.Startup.AclActionBsonSerializer`  
`public sealed class AclActionBsonSerializer : SerializerBase<AclAction>`  
_public; L794-803_
- inherits: `SerializerBase<AclAction>`
- L797 _public method_ `public override AclAction Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L801 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, AclAction value)` — (inheritdoc)

#### class `HordeServer.Startup.AclScopeNameBsonSerializer`  
`public sealed class AclScopeNameBsonSerializer : SerializerBase<AclScopeName>`  
_public; L805-814_
- inherits: `SerializerBase<AclScopeName>`
- L808 _public method_ `public override AclScopeName Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L812 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, AclScopeName value)` — (inheritdoc)

#### class `HordeServer.Startup.SubResourceIdBsonSerializer`  
`sealed class SubResourceIdBsonSerializer<TValue, TConverter> : SerializerBase<TValue> where TValue : struct where TConverter : SubResourceIdConverter<TValue>, new()`  
_private*; L816-827_
- inherits: `SerializerBase<TValue>`
- constraints: `where TValue : struct where TConverter : SubResourceIdConverter<TValue>, new()`
- L818 _private* field_ `readonly TConverter _converter = new TConverter()`
- L821 _public method_ `public override TValue Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L825 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, TValue value)` — (inheritdoc)

#### class `HordeServer.Startup.SubResourceIdSerializer`  
`public class SubResourceIdSerializer : IBsonSerializer<SubResourceId>`  
_public; L832-861_
- inherits: `IBsonSerializer<SubResourceId>`
- desc: Serializer for subresource ids
- L835 _public property_ `public Type ValueType => ...` — (inheritdoc)
- L838-841 _public method_ `public object Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L844-848 _public method_ `public void Serialize(BsonSerializationContext context, BsonSerializationArgs args, object value)` — (inheritdoc)
- L851-854 _public method_ `public void Serialize(BsonSerializationContext context, BsonSerializationArgs args, SubResourceId id)` — (inheritdoc)
- L857-860 _private* method_ `SubResourceId IBsonSerializer<SubResourceId>.Deserialize(BsonDeserializationContext context, BsonDeserializationArgs vrgs)` — (inheritdoc)

#### class `HordeServer.Startup.SubResourceIdBsonSerializationProvider`  
`sealed class SubResourceIdBsonSerializationProvider : BsonSerializationProviderBase`  
_private*; L863-875_
- inherits: `BsonSerializationProviderBase`
- L866-874 _public method_ `public override IBsonSerializer? GetSerializer(Type type, IBsonSerializerRegistry serializerRegistry)` — (inheritdoc)

#### class `HordeServer.Startup.CommitTagBsonSerializer`  
`sealed class CommitTagBsonSerializer : SerializerBase<CommitTag>`  
_private*; L877-890_
- inherits: `SerializerBase<CommitTag>`
- L880-883 _public method_ `public override CommitTag Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L886-889 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, CommitTag value)` — (inheritdoc)

#### class `HordeServer.Startup.JsonObjectBsonSerializer`  
`sealed class JsonObjectBsonSerializer : SerializerBase<JsonObject>`  
_private*; L892-911_
- inherits: `SerializerBase<JsonObject>`
- L895-906 _public method_ `public override JsonObject Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L909 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, JsonObject value)` — (inheritdoc)

#### class `HordeServer.Startup.HostApplicationLifetime`  
`class HostApplicationLifetime : IHostApplicationLifetime`  
_private*; L1132-1139_
- inherits: `IHostApplicationLifetime`
- L1134 _public property_ `public CancellationToken ApplicationStarted => ...`
- L1135 _public property_ `public CancellationToken ApplicationStopped => ...`
- L1136 _public property_ `public CancellationToken ApplicationStopping => ...`
- L1138 _public method_ `public void StopApplication()`

### `Source/Programs/Horde/HordeServer/Users/UserCollection.cs` (HordeServer)


#### class `HordeServer.Users.UserCollectionV1`  
`class UserCollectionV1 : IUserCollection`  
_internal*; L25-224_
- inherits: `IUserCollection`
- desc: Manages user documents
- L82 _private* field_ `readonly IMongoCollection<UserDocument> _users`
- L87-91 _private* ctor_ `static UserCollectionV1()` — Static constructor
- L97-100 _public ctor_ `public UserCollectionV1(IMongoService mongoService)` — Constructor
- L103-106 _public method_ `public async Task<IUser?> GetUserAsync(UserId id, CancellationToken cancellationToken)` — (inheritdoc)
- L109-119 _public method_ `public async ValueTask<IUser?> GetCachedUserAsync(UserId? id, CancellationToken cancellationToken)` — (inheritdoc)
- L122-126 _public method_ `public async Task<IReadOnlyList<IUser>> FindUsersAsync(IEnumerable<UserId>? ids, string? nameRegex, int? index, int? count, CancellationToken cancellationToken)` — (inheritdoc)
- L129-133 _public method_ `public async Task<IUser?> FindUserByLoginAsync(string login, CancellationToken cancellationToken)` — (inheritdoc)
- L136-139 _public method_ `public Task<IUser?> FindUserByEmailAsync(string email, CancellationToken cancellationToken)` — (inheritdoc)
- L142-147 _public method_ `public async Task<IUser> FindOrAddUserByLoginAsync(string login, string? name, string? email, CancellationToken cancellationToken)` — (inheritdoc)
- L150-153 _public method_ `public async Task<IUserClaims> GetClaimsAsync(UserId userId, CancellationToken cancellationToken)` — (inheritdoc)
- L156-160 _public method_ `public async Task UpdateClaimsAsync(UserId userId, IEnumerable<IUserClaim> claims, CancellationToken cancellationToken)` — (inheritdoc)
- L163-166 _public method_ `public async Task<IUserSettings> GetSettingsAsync(UserId userId, CancellationToken cancellationToken)` — (inheritdoc)
- L169-202 _public method_ `public async Task UpdateSettingsAsync(UserId userId, bool? enableExperimentalFeatures, bool? alwaysTagPreflightCL = null, BsonValue? dashboardSettings = null, IEnumerable<JobId>? addPinnedJobIds = null, IEnumerable<JobId>? removePinnedJobIds = null, UpdateUserJobTemplateOptions? templateOptions = null, IEnumerable<BisectTaskId>? addBisectTaskIds = null, IEnumerable<BisectTaskId>? removeBisectTaskIds = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L208-223 _public method_ `public async IAsyncEnumerable<(IUser, IUserClaims, IUserSettings)> EnumerateDocumentsAsync([EnumeratorCancellation] CancellationToken cancellationToken)` — Enumerate all the documents in this collection

#### class `HordeServer.Users.UserCollectionV1.UserDocument`  
`class UserDocument : IUser, IUserClaims, IUserSettings`  
_private*; L27-56_
- inherits: `IUser, IUserClaims, IUserSettings`
- L29 _public property_ `public UserId Id { get; set; }`
- L31 _public property_ `public ClaimDocument PrimaryClaim { get; set; }`
- L32 _public property_ `public List<ClaimDocument> Claims { get; set; }`
- L35 _public property_ `public bool EnableExperimentalFeatures { get; set; }` — attrs: `[BsonDefaultValue(false), BsonIgnoreIfDefault]`
- L38 _public property_ `public bool AlwaysTagPreflightCL { get; set; }` — attrs: `[BsonDefaultValue(false), BsonIgnoreIfDefault]`
- L40 _public property_ `public BsonValue DashboardSettings { get; set; }`
- L41 _public property_ `public List<JobId> PinnedJobIds { get; set; }`
- L42 _public property_ `public List<BisectTaskId> PinnedBisectTaskIds { get; set; }`
- L44 _private* property_ `string IUser.Name => ...`
- L45 _private* property_ `string IUser.Login => ...`
- L46 _private* property_ `string? IUser.Email => ...`
- L48 _private* property_ `UserId IUserClaims.UserId => ...`
- L49 _private* property_ `IReadOnlyList<IUserClaim> IUserClaims.Claims => ...`
- L51 _private* property_ `UserId IUserSettings.UserId => ...`
- L52 _private* property_ `IReadOnlyList<JobId> IUserSettings.PinnedJobIds => ...`
- L53 _private* property_ `IReadOnlyList<BisectTaskId> IUserSettings.PinnedBisectTaskIds => ...`
- L55 _private* property_ `IReadOnlyList<IUserJobTemplateSettings>? IUserSettings.JobTemplateSettings => ...`

#### class `HordeServer.Users.UserCollectionV1.ClaimDocument`  
`class ClaimDocument : IUserClaim`  
_private*; L58-80_
- inherits: `IUserClaim`
- L60 _public property_ `public string Type { get; set; }`
- L61 _public property_ `public string Value { get; set; }`
- L63-67 _private ctor_ `private ClaimDocument()`
- L69-73 _public ctor_ `public ClaimDocument(string type, string value)`
- L75-79 _public ctor_ `public ClaimDocument(IUserClaim other)`

### `Source/Programs/Horde/HordeServer/Users/UserCollectionV2.cs` (HordeServer)


#### class `HordeServer.Users.UserCollectionV2`  
`class UserCollectionV2 : IUserCollection, IDisposable`  
_internal*; L28-444_
- inherits: `IUserCollection, IDisposable`
- desc: Manages user documents
- L193 _private* field_ `readonly IMongoCollection<UserDocument> _users`
- L194 _private* field_ `readonly IMongoCollection<UserClaimsDocument> _userClaims`
- L195 _private* field_ `readonly IMongoCollection<UserSettingsDocument> _userSettings`
- L196 _private* field_ `readonly ILogger<UserCollectionV2> _logger`
- L197 _private* field_ `readonly MemoryCache _userCache`
- L202-209 _private* ctor_ `static UserCollectionV2()` — Static constructor
- L216-230 _public ctor_ `public UserCollectionV2(IMongoService mongoService, ILogger<UserCollectionV2> logger)` — Constructor
- L233-236 _public method_ `public void Dispose()` — (inheritdoc)
- L239-254 _public method_ `public async Task<IUser?> GetUserAsync(UserId id, CancellationToken cancellationToken)` — (inheritdoc)
- L257-272 _public method_ `public async ValueTask<IUser?> GetCachedUserAsync(UserId? id, CancellationToken cancellationToken)` — (inheritdoc)
- L275-292 _public method_ `public async Task<IReadOnlyList<IUser>> FindUsersAsync(IEnumerable<UserId>? ids, string? nameRegex = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L295-300 _public method_ `public async Task<IUser?> FindUserByLoginAsync(string login, CancellationToken cancellationToken)` — (inheritdoc)
- L303-308 _public method_ `public async Task<IUser?> FindUserByEmailAsync(string email, CancellationToken cancellationToken)` — (inheritdoc)
- L311-339 _public method_ `public async Task<IUser> FindOrAddUserByLoginAsync(string login, string? name, string? email, CancellationToken cancellationToken)` — (inheritdoc)
- L342-347 _public method_ `public async Task<IUserClaims> GetClaimsAsync(UserId userId, CancellationToken cancellationToken)` — (inheritdoc)
- L350-355 _public method_ `public async Task UpdateClaimsAsync(UserId userId, IEnumerable<IUserClaim> claims, CancellationToken cancellationToken)` — (inheritdoc)
- L358-363 _public method_ `public async Task<IUserSettings> GetSettingsAsync(UserId userId, CancellationToken cancellationToken)` — (inheritdoc)
- L366-414 _public method_ `public async Task UpdateSettingsAsync(UserId userId, bool? enableExperimentalFeatures = null, bool? alwaysTagPreflightCL = null, BsonValue? dashboardSettings = null, IEnumerable<JobId>? addPinnedJobIds = null, IEnumerable<JobId>? removePinnedJobIds = null, UpdateUserJobTemplateOptions? templateOptions = null, IEnumerable<BisectTaskId>? addBisectTaskIds = null, IEnumerable<BisectTaskId>? removeBisectTaskIds = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L422-443 _public method_ `public async Task ResaveDocumentsAsync(UserCollectionV1 userCollectionV1, CancellationToken cancellationToken)` — Upgrade from V1 collection

#### class `HordeServer.Users.UserCollectionV2.UserDocument`  
`class UserDocument : IUser`  
_private*; L30-65_
- inherits: `IUser`
- L32 _public property_ `public UserId Id { get; set; }`
- L34 _public property_ `public string Name { get; set; }`
- L35 _public property_ `public string Login { get; set; }`
- L36 _public property_ `public string LoginUpper { get; set; }`
- L37 _public property_ `public string? Email { get; set; }`
- L38 _public property_ `public string? EmailUpper { get; set; }`
- L41 _public property_ `public bool? Hidden { get; set; }` — attrs: `[BsonIgnoreIfDefault]`
- L44-49 _private ctor_ `private UserDocument()` — attrs: `[BsonConstructor]`
- L51-54 _public ctor_ `public UserDocument(IUser other) : this(other.Id, other.Name, other.Login, other.Email)`
- L56-64 _public ctor_ `public UserDocument(UserId id, string name, string login, string? email)`

#### class `HordeServer.Users.UserCollectionV2.UserClaimsDocument`  
`class UserClaimsDocument : IUserClaims`  
_private*; L67-90_
- inherits: `IUserClaims`
- L69 _public property_ `public UserId Id { get; set; }`
- L70 _public property_ `public List<UserClaim> Claims { get; set; }`
- L72 _private* property_ `UserId IUserClaims.UserId => ...`
- L73 _private* property_ `IReadOnlyList<IUserClaim> IUserClaims.Claims => ...`
- L76-78 _private ctor_ `private UserClaimsDocument()` — attrs: `[BsonConstructor]`
- L80-83 _public ctor_ `public UserClaimsDocument(UserId id)`
- L85-89 _public ctor_ `public UserClaimsDocument(IUserClaims other) : this(other.UserId)`

#### class `HordeServer.Users.UserCollectionV2.JobTemplateSettingsDocument`  
`class JobTemplateSettingsDocument : IUserJobTemplateSettings`  
_private*; L92-126_
- inherits: `IUserJobTemplateSettings`
- L94 _public property_ `public StreamId StreamId { get; set; }`
- L96 _public property_ `public TemplateId TemplateId { get; set; }`
- L98 _public property_ `public string TemplateHash { get; set; }`
- L100 _public property_ `public List<string> Arguments { get; set; }`
- L101 _private* property_ `IReadOnlyList<string> IUserJobTemplateSettings.Arguments => ...`
- L103 _public property_ `public DateTime UpdateTimeUtc { get; set; }`
- L106-109 _private ctor_ `private JobTemplateSettingsDocument()` — attrs: `[BsonConstructor]`
- L118-125 _public ctor_ `public JobTemplateSettingsDocument(StreamId streamId, TemplateId templateId, string templateHash, List<string> arguments)` — Constructor

#### class `HordeServer.Users.UserCollectionV2.UserSettingsDocument`  
`class UserSettingsDocument : IUserSettings`  
_private*; L128-167_
- inherits: `IUserSettings`
- L130 _public property_ `public UserId Id { get; set; }`
- L133 _public property_ `public bool EnableExperimentalFeatures { get; set; }` — attrs: `[BsonDefaultValue(false), BsonIgnoreIfDefault]`
- L136 _public property_ `public bool AlwaysTagPreflightCL { get; set; }` — attrs: `[BsonDefaultValue(false), BsonIgnoreIfDefault]`
- L138 _public property_ `public BsonValue DashboardSettings { get; set; }`
- L139 _public property_ `public List<JobId> PinnedJobIds { get; set; }`
- L140 _public property_ `public List<BisectTaskId> PinnedBisectTaskIds { get; set; }`
- L142 _private* property_ `UserId IUserSettings.UserId => ...`
- L143 _private* property_ `IReadOnlyList<JobId> IUserSettings.PinnedJobIds => ...`
- L144 _private* property_ `IReadOnlyList<BisectTaskId> IUserSettings.PinnedBisectTaskIds => ...`
- L146 _public property_ `public List<JobTemplateSettingsDocument> JobTemplateSettings { get; set; }`
- L147 _private* property_ `IReadOnlyList<IUserJobTemplateSettings>? IUserSettings.JobTemplateSettings => ...`
- L150-152 _private ctor_ `private UserSettingsDocument()` — attrs: `[BsonConstructor]`
- L154-157 _public ctor_ `public UserSettingsDocument(UserId id)`
- L159-166 _public ctor_ `public UserSettingsDocument(IUserSettings other) : this(other.UserId)`

#### class `HordeServer.Users.UserCollectionV2.ClaimDocument`  
`class ClaimDocument : IUserClaim`  
_private*; L169-191_
- inherits: `IUserClaim`
- L171 _public property_ `public string Type { get; set; }`
- L172 _public property_ `public string Value { get; set; }`
- L174-178 _private ctor_ `private ClaimDocument()`
- L180-184 _public ctor_ `public ClaimDocument(string type, string value)`
- L186-190 _public ctor_ `public ClaimDocument(IUserClaim other)`

### `Source/Programs/Horde/HordeServer/Users/UserController.cs` (HordeServer)


#### class `HordeServer.Users.UserController`  
`public class UserController : ControllerBase`  
_public; L29-160_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/user endpoint
- L31 _private* field_ `readonly IUserCollection _userCollection`
- L32 _private* field_ `readonly IAvatarService? _avatarService`
- L33 _private* field_ `readonly IEnumerable<IPluginResponseFilter> _responseFilters`
- L34 _private* field_ `readonly IOptionsSnapshot<GlobalConfig> _globalConfig`
- L35 _private* field_ `readonly IOptionsMonitor<ServerSettings> _settings`
- L40-47 _public ctor_ `public UserController(IUserCollection userCollection, IAvatarService? avatarService, IEnumerable<IPluginResponseFilter> responseFilters, IOptionsSnapshot<GlobalConfig> globalConfig, IOptionsMonitor<ServerSettings> settings)` — Constructor
- L56-72 _public method_ `public async Task<ActionResult<object>> GetUserAsync([FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/user")] [ProducesResponseType(typeof(GetUserResponse), 200)]` — Gets information about the logged in user
- L74-94 _private* method_ `GetDashboardFeaturesResponse GetDashboardFeatures(GlobalConfig globalConfig, ServerSettings settings, ClaimsPrincipal principal)`
- L102-112 _public method_ `public async Task<ActionResult> UpdateUserAsync(UpdateUserRequest request)` — attrs: `[HttpPut] [Route("/api/v1/user")]` — Updates the logged in user
- L119-122 _public method_ `public ActionResult<object[]> GetUserClaims()` — attrs: `[HttpGet] [Route("/api/v1/user/claims")]` — Gets claims for the current user
- L129-132 _public method_ `public ActionResult<GetUserAclPermissionsResponse> GetUserAclPermissions()` — attrs: `[HttpGet] [Route("/api/v1/user/acl-permissions")]` — Gets ACL permissions for the current user
- L141-159 _public method_ `public static List<UserAclPermission> GetUserAclPermissions(GlobalConfig globalConfig, ClaimsPrincipal user)` — Get a list of ACL permissions for a user A scope is only included if the user is authorized for at least one action inside of it

### `Source/Programs/Horde/HordeServer/Users/UsersController.cs` (HordeServer)


#### class `HordeServer.Users.UsersController`  
`public class UsersController : HordeControllerBase`  
_public; L21-119_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/users endpoint
- L26 _private* property_ `IUserCollection UserCollection { get; set; }` — The user collection instance
- L31 _private* property_ `IAvatarService? AvatarService { get; set; }` — The avatar service
- L38-42 _public ctor_ `public UsersController(IUserCollection userCollection, IAvatarService? avatarService)` — Constructor
- L51-69 _public method_ `public async Task<ActionResult<object>> GetUserAsync(string id, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/users/{id}")] [ProducesResponseType(typeof(List<GetUserResponse>), 200)]` — Gets information about a user by id, specify "current" for id to get the currently logged in user
- L78-105 _public method_ `public async Task<ActionResult<List<GetUserResponse>>> FindUsersAsync( [FromQuery] string[]? ids = null, [FromQuery] string? nameRegex = null, [FromQuery] int index = 0, [FromQuery] int count = 100, [FromQuery] bool includeClaims = false, [FromQuery] bool includeAvatar = false, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/users")] [ProducesResponseType(typeof(List<GetUserResponse>), 200)]` — Gets a list of users
- L107-118 _private* method_ `UserId? ParseUserId(string id)`

### `Source/Programs/Horde/HordeServer/Utilities/AgentUtilities.cs` (HordeServer)


#### class `HordeServer.Utilities.AgentUtilities`  
`static class AgentUtilities`  
_internal*; L14-100_
- L21-44 _public method_ `public static string ReadVersion(byte[] data)` — Reads the version number from an archive
- L52-99 _public method_ `public static byte[] UpdateAppSettings(byte[] data, Dictionary<string, object> settings)` — Updates the agent app settings within the archive data

### `Source/Programs/Horde/HordeServer/Utilities/BloomFilter.cs` (HordeServer)


#### struct `HordeServer.Utilities.LogIndex`  
`struct LogIndex`  
_internal*; L8-73_
- L10 _private* const_ `const int NumHashes = 3`
- L11 _private* const_ `const int NgramLength = 3`
- L12 _private* const_ `const int NgramMask = (1 << (NgramLength * 8)) - 1`
- L19-42 _public method_ `public static IEnumerable<int> GetHashCodes(ReadOnlyMemory<byte> text)` — Enumerates the hash codes for a given block of text
- L49-59 _private* method_ `static byte ToLowerUtf8(byte value)` — Converts a character into a format for hashing
- L66-72 _private method_ `private static int Scramble(int value)` — Scramble the given number using a pseudo-RNG

#### class `HordeServer.Utilities.ReadOnlyBloomFilter`  
`public class ReadOnlyBloomFilter`  
_public; L78-135_
- desc: Read only implementation of a bloom filter
- L83 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Data for the bloom filter
- L89-92 _public ctor_ `public ReadOnlyBloomFilter(ReadOnlyMemory<byte> data)` — Constructor
- L99-111 _public method_ `public bool Contains(IEnumerable<int> hashCodes)` — Determines if the filter may contain a value
- L117-134 _public method_ `public double CalculateLoadFactor()` — Calculates the load of this filter (ie. the proportion of bits which are set)

#### class `HordeServer.Utilities.BloomFilter`  
`public class BloomFilter`  
_public; L140-227_
- desc: Implementation of a bloom filter
- L145 _public property_ `public byte[] Data { get; }` — The array of bits in the filter
- L151-160 _public ctor_ `public BloomFilter(int minSize)` — Constructs a new filter of the given size
- L166-173 _public ctor_ `public BloomFilter(byte[] data)` — Constructs a filter from raw data
- L179-186 _public method_ `public void Add(IEnumerable<int> hashCodes)` — Add a value to the filter
- L193-204 _public method_ `public bool Contains(IEnumerable<int> hashCodes)` — Determines if the filter may contain a value
- L210-226 _public method_ `public double CalculateLoadFactor()` — Calculates the load of this filter (ie. the proportion of bits which are set)

### `Source/Programs/Horde/HordeServer/Utilities/Clock.cs` (HordeServer)


#### class `HordeCommon.Clock`  
`public sealed class Clock : IClock, IAsyncDisposable`  
_public; L21-160_
- inherits: `IClock, IAsyncDisposable`
- desc: Implementation of IClock which returns the current time
- L97 _private* field_ `readonly IRedisService _redis`
- L98 _private* field_ `readonly TimeZoneInfo _timeZone`
- L99 _private* field_ `readonly List<TickerImpl> _tickers = new List<TickerImpl>()`
- L102 _public property_ `public DateTime UtcNow => ...` — (inheritdoc)
- L105 _public property_ `public TimeZoneInfo TimeZone => ...` — (inheritdoc)
- L110-116 _public ctor_ `public Clock(IRedisService redis, IOptions<ServerSettings> settings)` — Constructor
- L119-125 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L128-136 _public method_ `public ITicker AddTicker(string name, TimeSpan delay, Func<CancellationToken, ValueTask<TimeSpan?>> tickAsync, ILogger logger)` — (inheritdoc)
- L139-143 _public method_ `public ITicker AddSharedTicker(string name, TimeSpan delay, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — (inheritdoc)
- L145-159 _private* method_ `async ValueTask TriggerSharedAsync(RedisKey key, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, CancellationToken cancellationToken)`

#### class `HordeCommon.Clock.TickerImpl`  
`sealed class TickerImpl : ITicker, IAsyncDisposable`  
_private*; L23-95_
- inherits: `ITicker, IAsyncDisposable`
- L25 _private* field_ `readonly string _name`
- L26 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L27 _private* field_ `readonly Func<Task> _tickFunc`
- L28 _private* field_ `Task? _backgroundTask`
- L30-35 _public ctor_ `public TickerImpl(string name, TimeSpan delay, Func<CancellationToken, ValueTask<TimeSpan?>> triggerAsync, ILogger logger)`
- L37-42 _public method_ `public async Task StartAsync()`
- L44-52 _public method_ `public async Task StopAsync()`
- L54-58 _public method_ `public async ValueTask DisposeAsync()`
- L60-92 _public method_ `public async Task RunAsync(TimeSpan delay, Func<CancellationToken, ValueTask<TimeSpan?>> triggerAsync, ILogger logger)`
- L94 _public method_ `public override string ToString()`

#### class `HordeCommon.FakeClock`  
`public class FakeClock : IClock`  
_public; L166-286_
- inherits: `IClock`
- desc: Fake clock that doesn't advance by wall block time Requires manual ticking to progress. Used in tests.
- L223 _private* field_ `DateTime _utcNowPrivate`
- L224 _private* field_ `readonly List<TickerImpl> _triggers = new List<TickerImpl>()`
- L229-233 _public ctor_ `public FakeClock()` — Constructor
- L240-258 _public method_ `public async Task AdvanceAsync(TimeSpan period)` — Advance time by given amount Useful for letting time progress during tests
- L261-265 _public property_ `public DateTime UtcNow { get; set; }` — (inheritdoc)
- L268 _public property_ `public TimeZoneInfo TimeZone { get; set; }` — (inheritdoc)
- L271-274 _public method_ `public ITicker AddTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask<TimeSpan?>> tickAsync, ILogger logger)` — (inheritdoc)
- L277-285 _public method_ `public ITicker AddSharedTicker(string name, TimeSpan interval, Func<CancellationToken, ValueTask> tickAsync, ILogger logger)` — (inheritdoc)

#### class `HordeCommon.FakeClock.TickerImpl`  
`class TickerImpl : ITicker`  
_private*; L168-221_
- inherits: `ITicker`
- L170 _private* field_ `readonly FakeClock _outer`
- L171 _private* field_ `readonly string _name`
- L172 _private* field_ `readonly TimeSpan _interval`
- L173 _public property_ `public DateTime? NextTime { get; set; }`
- L174 _public property_ `public Func<CancellationToken, ValueTask<TimeSpan?>> TickAsync { get; }`
- L176-187 _public ctor_ `public TickerImpl(FakeClock outer, string name, TimeSpan interval, Func<CancellationToken, ValueTask<TimeSpan?>> tickAsync)`
- L189-193 _public method_ `public Task StartAsync()`
- L195-199 _public method_ `public Task StopAsync()`
- L201-208 _public method_ `public ValueTask DisposeAsync()`
- L210-220 _public method_ `public override string ToString()`

### `Source/Programs/Horde/HordeServer/Utilities/CompressionExtensions.cs` (HordeServer)


#### class `HordeServer.Utilities.CompressionExtensions`  
`static class CompressionExtensions`  
_internal*; L15-73_
- desc: Extension methods for compression
- L23-45 _public method_ `public static byte[] CompressBzip2(this ReadOnlyMemory<byte> memory, int compressionLevel = 4)` — Compress a block of data with bzip2
- L51-72 _public method_ `public static byte[] DecompressBzip2(this ReadOnlyMemory<byte> memory)` — Decompress the data

### `Source/Programs/Horde/HordeServer/Utilities/ConditionSerializer.cs` (HordeServer)


#### class `HordeServer.Utilities.ConditionSerializer`  
`public sealed class ConditionSerializer : IBsonSerializer<Condition>`  
_public; L13-47_
- inherits: `IBsonSerializer<Condition>`
- desc: Serializer for Condition objects
- L16 _public property_ `public Type ValueType => ...` — (inheritdoc)
- L19 _private* method_ `void IBsonSerializer.Serialize(BsonSerializationContext context, BsonSerializationArgs args, object value)` — (inheritdoc)
- L22 _private* method_ `object IBsonSerializer.Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L25-33 _public method_ `public Condition Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L36-46 _public method_ `public void Serialize(BsonSerializationContext context, BsonSerializationArgs args, Condition? value)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Utilities/ContentHashSerializer.cs` (HordeServer)


#### class `HordeServer.Utilities.ContentHashSerializer`  
`public sealed class ContentHashSerializer : IBsonSerializer<ContentHash>`  
_public; L12-47_
- inherits: `IBsonSerializer<ContentHash>`
- desc: Serializer for ContentHash objects
- L15 _public property_ `public Type ValueType => ...` — (inheritdoc)
- L18-21 _private* method_ `void IBsonSerializer.Serialize(BsonSerializationContext context, BsonSerializationArgs args, object value)` — (inheritdoc)
- L24-27 _private* method_ `object IBsonSerializer.Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L30-40 _public method_ `public ContentHash Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L43-46 _public method_ `public void Serialize(BsonSerializationContext context, BsonSerializationArgs args, ContentHash value)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Utilities/DateTimeOffsetStringSerializer.cs` (HordeServer)


#### class `HordeServer.Utilities.DateTimeOffsetStringSerializer`  
`class DateTimeOffsetStringSerializer : StructSerializerBase<DateTimeOffset>`  
_internal*; L14-37_
- inherits: `StructSerializerBase<DateTimeOffset>`
- desc: Serializer for DateTimeOffset structs, which writes data as a string
- L17-30 _public method_ `public override DateTimeOffset Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L33-36 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, DateTimeOffset value)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Utilities/DefaultDiscriminatorConvention.cs` (HordeServer)


#### class `HordeServer.Utilities.DefaultDiscriminatorConvention`  
`class DefaultDiscriminatorConvention : IDiscriminatorConvention`  
_internal*; L19-66_
- inherits: `IDiscriminatorConvention`
- desc: Implements a discriminator convention, which defaults to a specific concrete type if no discriminator is specified. This class should also be registered as the discriminator for the concrete type as well as the interface, because the default behavior of the serializer is to recognize that the concrete type is discriminated and fall back to trying to read the discriminator element, failing, and falling back to serializing it as the interface recursively until we get a stack overflow. Registering this as the discriminator for the concrete type prevents this, because we can discriminate the concrete type correctly.
- L24 _private* property_ `static IDiscriminatorConvention Inner { get; }` — The normal discriminator to use
- L29 _private* field_ `readonly Type _baseType` — The nominal type
- L34 _private* field_ `readonly Type _defaultType` — Default type to use if the inner discriminator returns the nominal type
- L41-45 _public ctor_ `public DefaultDiscriminatorConvention(Type baseType, Type defaultType)` — Constructor
- L48 _public property_ `public string ElementName => ...` — (inheritdoc)
- L51-59 _public method_ `public Type GetActualType(IBsonReader bsonReader, Type nominalType)` — (inheritdoc)
- L62-65 _public method_ `public BsonValue GetDiscriminator(Type nominalType, Type actualType)` — (inheritdoc)

#### class `HordeServer.Utilities.DefaultDiscriminatorConvention`  
`class DefaultDiscriminatorConvention<TBase, TDerived> : DefaultDiscriminatorConvention`  
_internal*; L71-80_
- inherits: `DefaultDiscriminatorConvention`
- desc: Generic version of DefaultDiscriminatorConvention
- L76-79 _public ctor_ `public DefaultDiscriminatorConvention() : base(typeof(TBase), typeof(TDerived))` — Constructor

### `Source/Programs/Horde/HordeServer/Utilities/JsonSchemaCache.cs` (HordeServer)


#### class `HordeServer.Utilities.JsonSchemaCache`  
`public class JsonSchemaCache`  
_public; L13-69_
- desc: Cache for Json schemas
- L15 _private* field_ `readonly JsonSchemaFactory _factory`
- L16 _private* field_ `readonly ConcurrentDictionary<Type, JsonSchema> _cachedSchemas = ...`
- L16 _private* field_ `readonly ConcurrentDictionary< _cachedSchemas = new ConcurrentDictionary<Type, JsonSchema>()`
- L21-52 _public ctor_ `public JsonSchemaCache(IPluginCollection pluginCollection)` — Constructor
- L57-68 _public method_ `public JsonSchema CreateSchema(Type type)` — Create a Json schema (or retrieve a cached schema)

### `Source/Programs/Horde/HordeServer/Utilities/JwtUtils.cs` (HordeServer)


#### class `HordeServer.Utilities.JwtUtils`  
`public static class JwtUtils`  
_public; L14-73_
- desc: Helper functions for dealing with JWTs
- L23-43 _public method_ `public static bool TryGetBearerToken(HttpRequest request, string bearerPrefix, [NotNullWhen(true)] out string? token)` — Gets the bearer token from an HTTP request
- L51-72 _public method_ `public static bool TryParseJwt(string token, [NotNullWhen(true)] out JwtSecurityToken? jwtToken)` — Tries to parse a JWT and check the issuer matches

### `Source/Programs/Horde/HordeServer/Utilities/LazyCache.cs` (HordeServer)


#### class `HordeServer.Utilities.LazyCacheOptions`  
`public class LazyCacheOptions`  
_public; L16-27_
- desc: Options for LazyCache{TKey, TValue}
- L21 _public property_ `public TimeSpan? RefreshTime { get; set; }` — Time after which a value will asynchronously be updated
- L26 _public property_ `public TimeSpan? MaxAge { get; set; }` — Maximum age of any returned value. This will prevent a cached value being returned.

#### class `HordeServer.Utilities.LazyCache`  
`public sealed class LazyCache<TKey, TValue> : IDisposable where TKey : notnull`  
_public; L34-124_
- inherits: `IDisposable`
- constraints: `where TKey : notnull`
- desc: Implements a cache which starts an asynchronous update of a value after a period of time.
- L43 _private* field_ `readonly ConcurrentDictionary<TKey, Item> _dictionary = ...`
- L43 _private* field_ `readonly ConcurrentDictionary< _dictionary = new ConcurrentDictionary<TKey, Item>()`
- L44 _private* field_ `readonly Func<TKey, Task<TValue>> _getValueAsync`
- L44 _private* field_ `readonly Func< _getValueAsync`
- L45 _private* field_ `readonly LazyCacheOptions _options`
- L52-56 _public ctor_ `public LazyCache(Func<TKey, Task<TValue>> getValueAsync, LazyCacheOptions options)` — Constructor
- L59-66 _public method_ `public void Dispose()` — (inheritdoc)
- L74-102 _public method_ `public Task<TValue> GetAsync(TKey key, TimeSpan? maxAge = null)` — Gets the value associated with a key
- L110-123 _private* method_ `static Task<TValue> InterlockedCreateTaskAsync(ref Task<TValue>? value, Func<Task<TValue>> createTask)` — Creates a task, guaranteeing that only one task will be assigned to the given slot. Creates a cold task and only starts it once the variable is set.

#### class `HordeServer.Utilities.LazyCache.Item`  
`class Item`  
_private*; L36-41_
- L38 _public field_ `public Task<TValue>? _currentTask`
- L39 _public field_ `public Stopwatch _timer = Stopwatch.StartNew()`
- L40 _public field_ `public Task<TValue>? _updateTask`

### `Source/Programs/Horde/HordeServer/Utilities/LazyCachedValue.cs` (HordeServer)


#### class `HordeServer.Utilities.LazyCachedValue`  
`public class LazyCachedValue<T> where T : class`  
_public; L12-87_
- constraints: `where T : class`
- desc: Stores a value that expires after a given time
- L17 _private* field_ `T? _value` — The current value
- L22 _private* field_ `readonly Func<T> _generator` — Generator for the new value
- L27 _private* field_ `readonly Stopwatch _timer = Stopwatch.StartNew()` — Time since the value was updated
- L32 _private* field_ `readonly TimeSpan _defaultMaxAge` — Default expiry time
- L37-41 _public ctor_ `public LazyCachedValue(Func<T> generator, TimeSpan maxAge)` — Default constructor
- L47-51 _public method_ `public void Set(T value)` — Sets the new value
- L57-60 _public method_ `public T GetCached()` — Tries to get the current value
- L66-75 _public method_ `public T GetCached(TimeSpan maxAge)` — Tries to get the current value
- L81-86 _public method_ `public T GetLatest()` — Gets the latest value, updating the cache

### `Source/Programs/Horde/HordeServer/Utilities/MongoCommandTracer.cs` (HordeServer)


#### class `HordeServer.Utilities.MongoCommandTracer`  
`public class MongoCommandTracer`  
_public; L18-291_
- desc: OpenTelemetry-based tracer listening for MongoDB command events
- L20 _private field_ `private readonly ConcurrentDictionary<int, TelemetrySpan> _requestToSpans = ...`
- L20 _private field_ `private readonly ConcurrentDictionary< _requestToSpans = new()`
- L21 _private field_ `private readonly ConcurrentDictionary<long, OperationSpanEntry> _operationToSpans = ...`
- L21 _private field_ `private readonly ConcurrentDictionary< _operationToSpans = new()`
- L22 _private field_ `private readonly Dictionary<string, MongoCommand> _strToCommand = ...`
- L22 _private field_ `private readonly Dictionary< _strToCommand = new()`
- L23 _private field_ `private readonly Tracer _tracer`
- L24 _private field_ `private readonly ILogger<MongoCommandTracer> _logger`
- L25 _private field_ `private readonly ConcurrentDictionary<string, byte> _unhandledCommands = ...`
- L25 _private field_ `private readonly ConcurrentDictionary< _unhandledCommands = new()`
- L55-83 _public ctor_ `public MongoCommandTracer(Tracer tracer, ILogger<MongoCommandTracer> logger)` — Constructor
- L89-94 _public method_ `public void Register(ClusterBuilder clusterBuilder)` — Registers event listeners from MongoDB's client
- L96-100 _internal method_ `internal IReadOnlySet<TelemetrySpan> GetSpans()`
- L102-105 _internal method_ `internal TelemetrySpan GetSpanByRequestId(int requestId)`
- L107-110 _internal method_ `internal TelemetrySpan GetSpanByOperationId(long operationId)`
- L112-177 _internal method_ `internal void OnEvent(CommandStartedEvent ev)`
- L179-226 _internal method_ `internal void OnEvent(CommandSucceededEvent ev)`
- L228-231 _internal method_ `internal void OnEvent(CommandFailedEvent ev)`
- L233-247 _private method_ `private MongoCommand? ResolveCommand(string name)`
- L249-278 _private method_ `private void EndSpan(int reqId, long? opId, Status status, TimeSpan? duration = null, Exception? exception = null, long? waitedMs = null)`
- L280-283 _private method_ `private static long? GetBsonDocumentLong(BsonDocument document, string key)`
- L285-290 _private method_ `private static long? GetCursorId(BsonDocument replyDocument)`

#### record `HordeServer.Utilities.MongoCommandTracer.OperationSpanEntry`  
`private record OperationSpanEntry(TelemetrySpan Span, int RequestId)`  
_private; L27-27_

#### record `HordeServer.Utilities.MongoCommandTracer.MongoCommand`  
`private record MongoCommand(MongoCommandType Type, string Name, string? StatementFieldName, string? CollectionFieldName = null)`  
_private; L28-28_

#### enum `HordeServer.Utilities.MongoCommandTracer.MongoCommandType`  
`private enum MongoCommandType`  
_private; L30-48_
- L32 _public* enumerator_ `Aggregate`
- L33 _public* enumerator_ `CreateIndexes`
- L34 _public* enumerator_ `Delete`
- L35 _public* enumerator_ `Distinct`
- L36 _public* enumerator_ `Find`
- L37 _public* enumerator_ `FindAndModify`
- L38 _public* enumerator_ `GetLastError`
- L39 _public* enumerator_ `GetMore`
- L40 _public* enumerator_ `Insert`
- L41 _public* enumerator_ `IsMaster`
- L42 _public* enumerator_ `KillCursors`
- L43 _public* enumerator_ `ListIndexes`
- L44 _public* enumerator_ `Ping`
- L45 _public* enumerator_ `SaslContinue`
- L46 _public* enumerator_ `SaslStart`
- L47 _public* enumerator_ `Update`

### `Source/Programs/Horde/HordeServer/Utilities/MongoQueryCache.cs` (HordeServer)


#### class `HordeServer.Utilities.MongoQueryCache`  
`class MongoQueryCache<TDocument> : IDisposable`  
_internal*; L20-89_
- inherits: `IDisposable`
- desc: Caches queries against a given collection
- L29 _private* field_ `readonly IMongoCollection<TDocument> _collection`
- L30 _private* field_ `readonly MemoryCache _cache`
- L31 _private* field_ `readonly TimeSpan _maxLatency`
- L33-41 _public ctor_ `public MongoQueryCache(IMongoCollection<TDocument> collection, TimeSpan maxLatency)`
- L43-46 _public method_ `public void Dispose()`
- L48-52 _private* method_ `async Task RefreshAsync(QueryState state, FilterDefinition<TDocument> filter, CancellationToken cancellationToken = default)`
- L54-88 _public method_ `public async Task<List<TDocument>> FindAsync(FilterDefinition<TDocument> filter, int index, int count)`

#### class `HordeServer.Utilities.MongoQueryCache.QueryState`  
`class QueryState`  
_private*; L22-27_
- L24 _public field_ `public Stopwatch _timer = Stopwatch.StartNew()`
- L25 _public field_ `public List<TDocument>? _results`
- L26 _public field_ `public Task? _queryTask`

### `Source/Programs/Horde/HordeServer/Utilities/MongoTracingCollection.cs` (HordeServer)


#### class `HordeServer.Utilities.MongoTracingCollection`  
`public class MongoTracingCollection<T> : IMongoCollection<T>`  
_public; L23-740_
- inherits: `IMongoCollection<T>`
- desc: Wrap a IMongoCollection with trace scopes Will capture the entire invocation of MongoDB calls, including serialization. The other command logging (not in this file) only deals with queries sent to the server at the protocol level.
- L25 _private field_ `private readonly IMongoCollection<T> _collection`
- L26 _private field_ `private readonly Task _upgradeTask`
- L27 _private field_ `private readonly Tracer _tracer`
- L35-40 _public ctor_ `public MongoTracingCollection(IMongoCollection<T> collection, Task indexCreationTask, Tracer tracer)` — Constructor
- L44-48 _public method_ `public IAsyncCursor<TResult> Aggregate<TResult>(PipelineDefinition<T, TResult> pipeline, AggregateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L51-55 _public method_ `public IAsyncCursor<TResult> Aggregate<TResult>(IClientSessionHandle session, PipelineDefinition<T, TResult> pipeline, AggregateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L58-63 _public method_ `public async Task<IAsyncCursor<TResult>> AggregateAsync<TResult>(PipelineDefinition<T, TResult> pipeline, AggregateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L66-72 _public method_ `public async Task<IAsyncCursor<TResult>> AggregateAsync<TResult>(IClientSessionHandle session, PipelineDefinition<T, TResult> pipeline, AggregateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L75-79 _public method_ `public void AggregateToCollection<TResult>(PipelineDefinition<T, TResult> pipeline, AggregateOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L82-86 _public method_ `public void AggregateToCollection<TResult>(IClientSessionHandle session, PipelineDefinition<T, TResult> pipeline, AggregateOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L89-94 _public method_ `public async Task AggregateToCollectionAsync<TResult>(PipelineDefinition<T, TResult> pipeline, AggregateOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L97-102 _public method_ `public async Task AggregateToCollectionAsync<TResult>(IClientSessionHandle session, PipelineDefinition<T, TResult> pipeline, AggregateOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L105-109 _public method_ `public BulkWriteResult<T> BulkWrite(IEnumerable<WriteModel<T>> requests, BulkWriteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L112-116 _public method_ `public BulkWriteResult<T> BulkWrite(IClientSessionHandle session, IEnumerable<WriteModel<T>> requests, BulkWriteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L119-124 _public method_ `public async Task<BulkWriteResult<T>> BulkWriteAsync(IEnumerable<WriteModel<T>> requests, BulkWriteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L127-132 _public method_ `public async Task<BulkWriteResult<T>> BulkWriteAsync(IClientSessionHandle session, IEnumerable<WriteModel<T>> requests, BulkWriteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L135-139 _public method_ `public long Count(FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L142-146 _public method_ `public long Count(IClientSessionHandle session, FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L149-154 _public method_ `public async Task<long> CountAsync(FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L157-162 _public method_ `public async Task<long> CountAsync(IClientSessionHandle session, FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L165-169 _public method_ `public long CountDocuments(FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L172-176 _public method_ `public long CountDocuments(IClientSessionHandle session, FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L179-184 _public method_ `public async Task<long> CountDocumentsAsync(FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L187-192 _public method_ `public async Task<long> CountDocumentsAsync(IClientSessionHandle session, FilterDefinition<T> filter, CountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L195-199 _public method_ `public DeleteResult DeleteMany(FilterDefinition<T> filter, CancellationToken cancellationToken = default)` — (inheritdoc)
- L202-206 _public method_ `public DeleteResult DeleteMany(FilterDefinition<T> filter, DeleteOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L209-213 _public method_ `public DeleteResult DeleteMany(IClientSessionHandle session, FilterDefinition<T> filter, DeleteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L216-221 _public method_ `public async Task<DeleteResult> DeleteManyAsync(FilterDefinition<T> filter, CancellationToken cancellationToken = default)` — (inheritdoc)
- L224-229 _public method_ `public async Task<DeleteResult> DeleteManyAsync(FilterDefinition<T> filter, DeleteOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L232-237 _public method_ `public async Task<DeleteResult> DeleteManyAsync(IClientSessionHandle session, FilterDefinition<T> filter, DeleteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L240-244 _public method_ `public DeleteResult DeleteOne(FilterDefinition<T> filter, CancellationToken cancellationToken = default)` — (inheritdoc)
- L247-251 _public method_ `public DeleteResult DeleteOne(FilterDefinition<T> filter, DeleteOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L254-258 _public method_ `public DeleteResult DeleteOne(IClientSessionHandle session, FilterDefinition<T> filter, DeleteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L261-266 _public method_ `public async Task<DeleteResult> DeleteOneAsync(FilterDefinition<T> filter, CancellationToken cancellationToken = default)` — (inheritdoc)
- L269-274 _public method_ `public async Task<DeleteResult> DeleteOneAsync(FilterDefinition<T> filter, DeleteOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L277-282 _public method_ `public async Task<DeleteResult> DeleteOneAsync(IClientSessionHandle session, FilterDefinition<T> filter, DeleteOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L285-289 _public method_ `public IAsyncCursor<TField> Distinct<TField>(FieldDefinition<T, TField> field, FilterDefinition<T> filter, DistinctOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L292-296 _public method_ `public IAsyncCursor<TField> Distinct<TField>(IClientSessionHandle session, FieldDefinition<T, TField> field, FilterDefinition<T> filter, DistinctOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L299-304 _public method_ `public async Task<IAsyncCursor<TField>> DistinctAsync<TField>(FieldDefinition<T, TField> field, FilterDefinition<T> filter, DistinctOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L307-312 _public method_ `public async Task<IAsyncCursor<TField>> DistinctAsync<TField>(IClientSessionHandle session, FieldDefinition<T, TField> field, FilterDefinition<T> filter, DistinctOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L315-319 _public method_ `public long EstimatedDocumentCount(EstimatedDocumentCountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L322-327 _public method_ `public async Task<long> EstimatedDocumentCountAsync(EstimatedDocumentCountOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L330-334 _public method_ `public IAsyncCursor<TProjection> FindSync<TProjection>(FilterDefinition<T> filter, FindOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L337-341 _public method_ `public IAsyncCursor<TProjection> FindSync<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, FindOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L344-349 _public method_ `public async Task<IAsyncCursor<TProjection>> FindAsync<TProjection>(FilterDefinition<T> filter, FindOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L352-357 _public method_ `public async Task<IAsyncCursor<TProjection>> FindAsync<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, FindOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L360-364 _public method_ `public TProjection FindOneAndDelete<TProjection>(FilterDefinition<T> filter, FindOneAndDeleteOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L367-371 _public method_ `public TProjection FindOneAndDelete<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, FindOneAndDeleteOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L374-379 _public method_ `public async Task<TProjection> FindOneAndDeleteAsync<TProjection>(FilterDefinition<T> filter, FindOneAndDeleteOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L382-387 _public method_ `public async Task<TProjection> FindOneAndDeleteAsync<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, FindOneAndDeleteOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L390-394 _public method_ `public TProjection FindOneAndReplace<TProjection>(FilterDefinition<T> filter, T replacement, FindOneAndReplaceOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L397-401 _public method_ `public TProjection FindOneAndReplace<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, T replacement, FindOneAndReplaceOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L404-409 _public method_ `public async Task<TProjection> FindOneAndReplaceAsync<TProjection>(FilterDefinition<T> filter, T replacement, FindOneAndReplaceOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L412-417 _public method_ `public async Task<TProjection> FindOneAndReplaceAsync<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, T replacement, FindOneAndReplaceOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L420-425 _public method_ `public TProjection FindOneAndUpdate<TProjection>(FilterDefinition<T> filter, UpdateDefinition<T> update, FindOneAndUpdateOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L428-432 _public method_ `public TProjection FindOneAndUpdate<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, UpdateDefinition<T> update, FindOneAndUpdateOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L435-440 _public method_ `public async Task<TProjection> FindOneAndUpdateAsync<TProjection>(FilterDefinition<T> filter, UpdateDefinition<T> update, FindOneAndUpdateOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L443-448 _public method_ `public async Task<TProjection> FindOneAndUpdateAsync<TProjection>(IClientSessionHandle session, FilterDefinition<T> filter, UpdateDefinition<T> update, FindOneAndUpdateOptions<T, TProjection> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L451-455 _public method_ `public void InsertOne(T document, InsertOneOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L458-462 _public method_ `public void InsertOne(IClientSessionHandle session, T document, InsertOneOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L465-470 _public method_ `public async Task InsertOneAsync(T document, CancellationToken cancellationToken)` — (inheritdoc)
- L473-478 _public method_ `public async Task InsertOneAsync(T document, InsertOneOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L481-486 _public method_ `public async Task InsertOneAsync(IClientSessionHandle session, T document, InsertOneOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L489-493 _public method_ `public void InsertMany(IEnumerable<T> documents, InsertManyOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L496-500 _public method_ `public void InsertMany(IClientSessionHandle session, IEnumerable<T> documents, InsertManyOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L503-508 _public method_ `public async Task InsertManyAsync(IEnumerable<T> documents, InsertManyOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L511-516 _public method_ `public async Task InsertManyAsync(IClientSessionHandle session, IEnumerable<T> documents, InsertManyOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L519-523 _public method_ `public IAsyncCursor<TResult> MapReduce<TResult>(BsonJavaScript map, BsonJavaScript reduce, MapReduceOptions<T, TResult> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L526-530 _public method_ `public IAsyncCursor<TResult> MapReduce<TResult>(IClientSessionHandle session, BsonJavaScript map, BsonJavaScript reduce, MapReduceOptions<T, TResult> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L533-538 _public method_ `public async Task<IAsyncCursor<TResult>> MapReduceAsync<TResult>(BsonJavaScript map, BsonJavaScript reduce, MapReduceOptions<T, TResult> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L541-546 _public method_ `public async Task<IAsyncCursor<TResult>> MapReduceAsync<TResult>(IClientSessionHandle session, BsonJavaScript map, BsonJavaScript reduce, MapReduceOptions<T, TResult> options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L549-552 _public method_ `public IFilteredMongoCollection<TDerivedDocument> OfType<TDerivedDocument>() where TDerivedDocument : T` — (inheritdoc)
- L555-559 _public method_ `public ReplaceOneResult ReplaceOne(FilterDefinition<T> filter, T replacement, ReplaceOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L562-566 _public method_ `public ReplaceOneResult ReplaceOne(FilterDefinition<T> filter, T replacement, UpdateOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L569-573 _public method_ `public ReplaceOneResult ReplaceOne(IClientSessionHandle session, FilterDefinition<T> filter, T replacement, ReplaceOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L576-580 _public method_ `public ReplaceOneResult ReplaceOne(IClientSessionHandle session, FilterDefinition<T> filter, T replacement, UpdateOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L583-588 _public method_ `public async Task<ReplaceOneResult> ReplaceOneAsync(FilterDefinition<T> filter, T replacement, ReplaceOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L591-596 _public method_ `public async Task<ReplaceOneResult> ReplaceOneAsync(FilterDefinition<T> filter, T replacement, UpdateOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L599-604 _public method_ `public async Task<ReplaceOneResult> ReplaceOneAsync(IClientSessionHandle session, FilterDefinition<T> filter, T replacement, ReplaceOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L607-612 _public method_ `public async Task<ReplaceOneResult> ReplaceOneAsync(IClientSessionHandle session, FilterDefinition<T> filter, T replacement, UpdateOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L615-619 _public method_ `public UpdateResult UpdateMany(FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L622-626 _public method_ `public UpdateResult UpdateMany(IClientSessionHandle session, FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L629-634 _public method_ `public async Task<UpdateResult> UpdateManyAsync(FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L637-642 _public method_ `public async Task<UpdateResult> UpdateManyAsync(IClientSessionHandle session, FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L645-649 _public method_ `public UpdateResult UpdateOne(FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L652-656 _public method_ `public UpdateResult UpdateOne(IClientSessionHandle session, FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L659-664 _public method_ `public async Task<UpdateResult> UpdateOneAsync(FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L667-672 _public method_ `public async Task<UpdateResult> UpdateOneAsync(IClientSessionHandle session, FilterDefinition<T> filter, UpdateDefinition<T> update, UpdateOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L675-679 _public method_ `public IChangeStreamCursor<TResult> Watch<TResult>(PipelineDefinition<ChangeStreamDocument<T>, TResult> pipeline, ChangeStreamOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L682-686 _public method_ `public IChangeStreamCursor<TResult> Watch<TResult>(IClientSessionHandle session, PipelineDefinition<ChangeStreamDocument<T>, TResult> pipeline, ChangeStreamOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L689-694 _public method_ `public async Task<IChangeStreamCursor<TResult>> WatchAsync<TResult>(PipelineDefinition<ChangeStreamDocument<T>, TResult> pipeline, ChangeStreamOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L697-702 _public method_ `public async Task<IChangeStreamCursor<TResult>> WatchAsync<TResult>(IClientSessionHandle session, PipelineDefinition<ChangeStreamDocument<T>, TResult> pipeline, ChangeStreamOptions options = null!, CancellationToken cancellationToken = default)` — (inheritdoc)
- L705-708 _public method_ `public IMongoCollection<T> WithReadConcern(ReadConcern readConcern)` — (inheritdoc)
- L711-714 _public method_ `public IMongoCollection<T> WithReadPreference(ReadPreference readPreference)` — (inheritdoc)
- L717-720 _public method_ `public IMongoCollection<T> WithWriteConcern(WriteConcern writeConcern)` — (inheritdoc)
- L724 _public property_ `public CollectionNamespace CollectionNamespace => ...` — (inheritdoc)
- L727 _public property_ `public IMongoDatabase Database => ...` — (inheritdoc)
- L730 _public property_ `public IBsonSerializer<T> DocumentSerializer => ...` — (inheritdoc)
- L733 _public property_ `public IMongoIndexManager<T> Indexes => ...` — (inheritdoc)
- L736 _public property_ `public MongoCollectionSettings Settings => ...` — (inheritdoc)
- L739 _public property_ `public IMongoSearchIndexManager SearchIndexes => ...` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Utilities/NullDiscriminatorConvention.cs` (HordeServer)


#### class `HordeServer.Utilities.NullDiscriminatorConvention`  
`public class NullDiscriminatorConvention : IDiscriminatorConvention`  
_public; L13-34_
- inherits: `IDiscriminatorConvention`
- desc: Prevent a discriminator being serialized for a type
- L18 _public property_ `public static NullDiscriminatorConvention Instance { get; }` — Instance of the convention
- L21-24 _public method_ `public Type GetActualType(IBsonReader bsonReader, Type nominalType)` — (inheritdoc)
- L27-30 _public method_ `public BsonValue? GetDiscriminator(Type nominalType, Type actualType)` — (inheritdoc)
- L33 _public property_ `public string? ElementName => ...` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Utilities/OpenTelemetry.cs` (HordeServer)


#### class `HordeServer.Utilities.OpenTelemetryDatadogLogEnricher`  
`public class OpenTelemetryDatadogLogEnricher : ILogEventEnricher`  
_public; L29-45_
- inherits: `ILogEventEnricher`
- desc: Serilog event enricher attaching trace and span ID for Datadog using current System.Diagnostics.Activity
- L32-44 _public method_ `public void Enrich(Serilog.Events.LogEvent logEvent, ILogEventPropertyFactory propertyFactory)` — (inheritdoc)

#### class `HordeServer.Utilities.OpenTelemetryHelper`  
`public static class OpenTelemetryHelper`  
_public; L50-237_
- desc: Helper for configuring OpenTelemetry
- L52 _private field_ `private static ResourceBuilder? s_resourceBuilder`
- L59-73 _public method_ `public static void Configure(IServiceCollection services, OpenTelemetrySettings settings)` — Configure OpenTelemetry in Horde and ASP.NET
- L75-172 _private method_ `private static void ConfigureTracing(TracerProviderBuilder builder, OpenTelemetrySettings settings)`
- L174-193 _private method_ `private static void ConfigureMetrics(MeterProviderBuilder builder, OpenTelemetrySettings settings)`
- L200-219 _public method_ `public static void ConfigureLogging(ILoggingBuilder builder, OpenTelemetrySettings settings)` — Configure .NET logging with OpenTelemetry
- L221-236 _private method_ `private static ResourceBuilder GetResourceBuilder(OpenTelemetrySettings settings)`

#### class `HordeServer.Utilities.OpenTelemetrySpanExtensions`  
`public static class OpenTelemetrySpanExtensions`  
_public; L242-284_
- desc: Extensions to handle Horde specific data types in the OpenTelemetry library
- L255-283 _public method_ `public static TelemetrySpan StartMongoDbSpan<T>(this Tracer tracer, string spanName, IMongoCollection<T>? collection = null, FilterDefinition<T>? filter = null, UpdateDefinition<T>? update = null, T? document = default)` — attrs: `[MethodImpl(MethodImplOptions.AggressiveInlining)]` — Start a MongoDB-based tracing span

#### class `HordeServer.Utilities.OpenTelemetryMeters`  
`public static class OpenTelemetryMeters`  
_public; L289-306_
- desc: Static initialization of all available OpenTelemetry meters
- L294 _public const_ `public const string HordeName = "Horde"` — Name of default Horde meter
- L300 _public property_ `public static string[] MeterNames => ...` — List of all source names configured in this class. They are needed at startup when initializing OpenTelemetry
- L305 _public field_ `public static readonly Meter Horde = new(HordeName)` — Default meter used in Horde

### `Source/Programs/Horde/HordeServer/Utilities/RawOutputFormatter.cs` (HordeServer)


#### class `HordeServer.Utilities.RawOutputFormatter`  
`public class RawOutputFormatter : OutputFormatter`  
_public; L17-77_
- inherits: `OutputFormatter`
- L19 _private field_ `private readonly ILogger _logger`
- L21-25 _public ctor_ `public RawOutputFormatter(ILogger logger)`
- L27-76 _public method_ `public override async Task WriteResponseBodyAsync(OutputFormatterWriteContext context)`

#### class `HordeServer.Utilities.RawOutputPropertyAttribute`  
`public sealed class RawOutputPropertyAttribute : Attribute`  
_public; L83-85_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Used to indicate that the field in question is what we want to return as a raw set of bytes

### `Source/Programs/Horde/HordeServer/Utilities/ReadOnlyTrie.cs` (HordeServer)


#### class `HordeServer.Logs.ReadOnlyTrie`  
`public class ReadOnlyTrie : IEnumerable<ulong>`  
_public; L14-270_
- inherits: `IEnumerable<ulong>`
- desc: A read-only trie of long values
- L39 _public delegate_ `public delegate bool VisitorDelegate(ulong value, ulong mask)` — Delegate for filtering values during a tree traversal
- L44 _private* const_ `const int Height = sizeof(ulong) * 2` — Height of the tree
- L49 _public property_ `public ushort[] NodeData { get; }` — Array of bitmasks for each node in the tree
- L54 _private* field_ `readonly int[] _firstChildIndex` — Array of child offsets for each node. Excludes the last layer of the tree.
- L59 _public property_ `public static ReadOnlyTrie Empty { get; }` — Empty index definition
- L65-69 _public ctor_ `public ReadOnlyTrie(ushort[] nodeData)` — Constructor
- L76-100 _public method_ `public bool Contains(ulong value)` — Tests whether the given value is in the trie
- L103-106 _public method_ `public IEnumerator<ulong> GetEnumerator()` — (inheritdoc)
- L109 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L116-179 _public method_ `public IEnumerable<ulong> EnumerateValues(VisitorDelegate predicate)` — Enumerate all values matching a given filter
- L187-190 _public method_ `public IEnumerable<ulong> EnumerateRange(ulong minValue, ulong maxValue)` — Enumerates all values in the trie between the given ranges
- L197-224 _private* method_ `static int[] CreateChildLookup(ushort[] nodeData)` — Creates a lookup for child node offsets from raw node data
- L231-239 _private* method_ `static int CountBits(ushort value)` — Count the number of set bits in the given value
- L246-251 _public method_ `public static ReadOnlyTrie Read(MemoryReader reader)` — Read a trie from the given buffer
- L257-260 _public method_ `public void Write(MemoryWriter writer)` — Write this trie to the given buffer
- L266-269 _public method_ `public int GetSerializedSize()` — Gets the serialized size of this trie

#### struct `HordeServer.Logs.ReadOnlyTrie.StackItem`  
`struct StackItem`  
_private*; L20-31_
- attrs: `[StructLayout(LayoutKind.Auto)]`
- desc: Stack item for traversing the tree
- L25 _public field_ `public int _index` — The current node index
- L30 _public field_ `public int _value` — Value in the current node (0-15)

#### class `HordeServer.Logs.LogTokenSetExtensions`  
`public static class LogTokenSetExtensions`  
_public; L275-296_
- desc: Extension methods for serializing tries
- L282-285 _public method_ `public static ReadOnlyTrie ReadTrie(this MemoryReader reader)` — Read a trie from the given buffer
- L292-295 _public method_ `public static void WriteTrie(this MemoryWriter writer, ReadOnlyTrie trie)` — Write this trie to the given buffer

### `Source/Programs/Horde/HordeServer/Utilities/ReadOnlyTrieBuilder.cs` (HordeServer)


#### class `HordeServer.Logs.ReadOnlyTrieBuilder`  
`public class ReadOnlyTrieBuilder`  
_public; L10-109_
- desc: Structure used for generating prefix trees
- L23 _private* field_ `readonly Node _root` — The root node
- L28-31 _public ctor_ `public ReadOnlyTrieBuilder()` — Default constructor
- L37-48 _public method_ `public void Add(ulong value)` — Adds a value to the trie
- L54-72 _public method_ `public bool Contains(ulong value)` — Searches for the given item in the trie
- L78-108 _public method_ `public ReadOnlyTrie Build()` — Creates a ReadOnlyTrie from this data

#### class `HordeServer.Logs.ReadOnlyTrieBuilder.Node`  
`class Node`  
_private*; L15-18_
- desc: Node within the trie
- L17 _public field_ `public Node?[]? _children`

### `Source/Programs/Horde/HordeServer/Utilities/SearchText.cs` (HordeServer)


#### class `HordeServer.Logs.SearchText`  
`public class SearchText`  
_public; L12-143_
- desc: Stores cached information about a utf8 search term
- L17 _public property_ `public string Text { get; }` — The search text
- L22 _public property_ `public ReadOnlyMemory<byte> Bytes { get; }` — The utf-8 bytes to search for
- L27 _private* field_ `readonly byte[] _searchBytes` — Normalized (lowercase) utf-8 bytes to search for
- L32 _private* field_ `readonly byte[] _skipTable` — Skip table for comparisons
- L38-76 _public ctor_ `public SearchText(string text)` — Constructor
- L84-95 _public method_ `public static IEnumerable<int> FindOcurrences(ReadOnlyMemory<byte> buffer, SearchText text)` — Find all ocurrences of the text in the given buffer
- L104-118 _public method_ `public static int FindNextOcurrence(ReadOnlySpan<byte> buffer, int offset, SearchText text)` — Perform a case sensitive search for the next occurerence of the search term in a given buffer
- L127-142 _public method_ `public static bool Matches(ReadOnlySpan<byte> buffer, int offset, SearchText text)` — Compare the search term against the given buffer

#### class `HordeServer.Logs.SearchTextExtensions`  
`public static class SearchTextExtensions`  
_public; L148-184_
- desc: Stores cached information about a utf8 search term
- L156-159 _public method_ `public static IEnumerable<int> FindOcurrences(this ReadOnlyMemory<byte> buffer, SearchText text)` — Find all ocurrences of the text in the given buffer
- L168-171 _public method_ `public static int FindNextOcurrence(this ReadOnlySpan<byte> buffer, int offset, SearchText text)` — Perform a case sensitive search for the next occurerence of the search term in a given buffer
- L180-183 _public method_ `public static bool Matches(this ReadOnlySpan<byte> buffer, int offset, SearchText text)` — Compare the search term against the given buffer

### `Source/Programs/Horde/HordeServer/Utilities/SizeLimitedJsonFormatter.cs` (HordeServer)


#### class `HordeServer.Utilities.SizeLimitedJsonFormatter`  
`sealed class SizeLimitedJsonFormatter : ITextFormatter`  
_internal*; L21-146_
- inherits: `ITextFormatter`
- desc: Wraps an ITextFormatter and enforces a maximum byte size on the formatted output. Uses three-tier truncation: Tier 1: output fits within the limit — pass through unchanged. Tier 2: strip redundant enricher properties (ExceptionInfo/ExceptionDetail) and retry. Tier 3: emit minimal JSON preserving RenderedMessage and full Exception stack trace.
- L23 _private* field_ `static readonly JsonSerializerOptions s_jsonOptions = new JsonSerializerOptions { Encoder = JavaScriptEncoder.UnsafeRelaxedJsonEscaping }`
- L25 _private* const_ `const string ExceptionInfoProperty = "ExceptionInfo"`
- L26 _private* const_ `const string ExceptionDetailProperty = "ExceptionDetail"`
- L28 _private* field_ `readonly ITextFormatter _inner`
- L29 _private* field_ `readonly int _maxBytes`
- L36-40 _public ctor_ `public SizeLimitedJsonFormatter(ITextFormatter inner, int maxBytes = 256 * 1024)` — Constructor
- L43-67 _public method_ `public void Format(LogEvent logEvent, TextWriter output)` — (inheritdoc)
- L73-119 _private* method_ `bool TryStripRedundantProperties(string formatted, int originalByteCount, out string? result)` — Attempts to strip ExceptionInfo and ExceptionDetail from the Properties object. Returns true if the stripped output fits within _maxBytes.
- L124-140 _private* method_ `static void WriteTier3Fallback(LogEvent logEvent, int originalByteCount, TextWriter output)` — Emits a minimal JSON object preserving RenderedMessage and the full Exception stack trace.
- L142-145 _private* method_ `static string EscapeJson(string value)`

### `Source/Programs/Horde/HordeServer/Utilities/StreamExtensions.cs` (HordeServer)


#### class `HordeServer.Utilities.StreamExtensions`  
`static class StreamExtensions`  
_internal*; L13-48_
- desc: Extension methods for working with streams
- L24-27 _public method_ `public static Task ReadFixedSizeDataAsync(this Stream stream, byte[] data, int offset, int length, CancellationToken cancellationToken = default)` — Reads data of a fixed size into the buffer. Throws an exception if the whole block cannot be read.
- L36-47 _public method_ `public static async Task ReadFixedSizeDataAsync(this Stream stream, Memory<byte> data, CancellationToken cancellationToken = default)` — Reads data of a fixed size into the buffer. Throws an exception if the whole block cannot be read.

### `Source/Programs/Horde/HordeServer/Utilities/StructuredException.cs` (HordeServer)


#### class `HordeServer.Utilities.StructuredException`  
`public class StructuredException : Exception`  
_public; L13-43_
- inherits: `Exception`
- desc: Exception class designed to allow logging structured log messages
- L18 _public property_ `public string Format { get; }` — Format string for the message
- L23 _public property_ `public IReadOnlyList<object> Args { get; }` — Arguments for holes in the format string
- L30-34 _public ctor_ `public StructuredException(string format, params object[] args)` — Constructor
- L39-42 _public method_ `public LogEvent ToLogEvent()` — Creates a log event from this exception

#### class `HordeServer.Utilities.StructuredHttpException`  
`public class StructuredHttpException : StructuredException`  
_public; L48-66_
- inherits: `StructuredException`
- desc: Exception class designed to allow logging structured log messages
- L53 _public property_ `public int StatusCode { get; }` — Status code
- L61-65 _public ctor_ `public StructuredHttpException(int statusCode, string format, params object[] args) : base(format, args)` — Constructor

### `Source/Programs/Horde/HordeServer/Utilities/ViewMap.cs` (HordeServer)


#### class `HordeServer.Utilities.ViewMap`  
`public class ViewMap`  
_public; L15-123_
- desc: Stores a mapping from one set of paths to another
- L20 _public property_ `public List<ViewMapEntry> Entries { get; }` — List of entries making up the view
- L25-28 _public ctor_ `public ViewMap()` — Default constructor
- L34-37 _public ctor_ `public ViewMap(ViewMap other)` — Constructor
- L45-56 _public method_ `public bool MatchFile(Utf8String file, Utf8StringComparer comparison)` — Determines if a file is included in the view
- L65-86 _public method_ `public bool TryMapFile(Utf8String sourceFile, Utf8StringComparer comparison, out Utf8String targetFile)` — Attempts to convert a source file to its target path
- L92-122 _public method_ `public List<Utf8String> GetRootPaths(Utf8StringComparer comparison)` — Gets the root paths from the view entries

#### class `HordeServer.Utilities.ViewMapEntry`  
`public class ViewMapEntry`  
_public; L128-295_
- desc: Entry within a ViewMap
- L133 _public property_ `public bool Include { get; }` — Whether to include files matching this pattern
- L138 _public property_ `public Utf8String Wildcard { get; }` — The wildcard string - either '*' or '...'
- L143 _public property_ `public Utf8String SourcePrefix { get; }` — The source part of the pattern before the wildcard
- L148 _public property_ `public Utf8String SourceSuffix { get; }` — The source part of the pattern after the wildcard. Perforce does not permit a slash to be in this part of the mapping.
- L153 _public property_ `public Utf8String TargetPrefix { get; }` — The target mapping for the pattern before the wildcard
- L158 _public property_ `public Utf8String TargetSuffix { get; }` — The target mapping for the pattern after the wildcard
- L163 _public property_ `public Utf8String Source => ...` — The full source pattern
- L168 _public property_ `public Utf8String Target => ...` — The full target pattern
- L174 _public method_ `public bool IsFileWildcard()` — Tests if the entry has a file wildcard ('*')
- L180 _public method_ `public bool IsPathWildcard()` — Tests if the entry has a path wildcard ('...')
- L186-189 _public ctor_ `public ViewMapEntry(ViewMapEntry other) : this(other.Include, other.Wildcard, other.SourcePrefix, other.SourceSuffix, other.TargetPrefix, other.TargetSuffix)` — Constructor
- L197-226 _public ctor_ `public ViewMapEntry(bool include, string source, string target)` — Constructor
- L237-245 _public ctor_ `public ViewMapEntry(bool include, Utf8String wildcard, Utf8String sourcePrefix, Utf8String sourceSuffix, Utf8String targetPrefix, Utf8String targetSuffix)` — Constructor
- L252-256 _public method_ `public Utf8String MapFile(Utf8String sourceFile)` — Maps a file to the target path
- L264-282 _public method_ `public bool MatchFile(Utf8String path, Utf8StringComparer comparison)` — Determine if a file matches the current entry
- L285-294 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Horde/HordeServer/Utilities/ZstdCompressionProvider.cs` (HordeServer)


#### class `HordeServer.Utilities.ZstdCompressionProvider`  
`class ZstdCompressionProvider : ICompressionProvider`  
_internal*; L11-24_
- inherits: `ICompressionProvider`
- desc: Compression provider for zstd responses
- L14 _public property_ `public string EncodingName => ...` — (inheritdoc)
- L17 _public property_ `public bool SupportsFlush => ...` — (inheritdoc)
- L20-23 _public method_ `public Stream CreateStream(Stream outputStream)` — (inheritdoc)
