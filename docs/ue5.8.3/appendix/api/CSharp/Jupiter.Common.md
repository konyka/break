# CSharp / Jupiter.Common

- project root: `Source/Programs/UnrealCloudDDC/Jupiter.Common`
- files: 38; symbols: 608
- symbol kinds: class=92, const=9, ctor=45, enum=5, enumerator=22, field=53, interface=4, method=226, operator=10, property=136, struct=6
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/AWSCredentialsHelper.cs` (Jupiter.Common)


#### class `Jupiter.AWSCredentialsHelper`  
`public static class AWSCredentialsHelper`  
_public; L10-26_
- L12-25 _public method_ `public static AWSCredentials GetCredentials(AWSCredentialsSettings options, string sessionName)`

#### class `Jupiter.AWSCredentialsSettings`  
`public class AWSCredentialsSettings : IValidatableObject`  
_public; L28-69_
- inherits: `IValidatableObject`
- L30 _public property_ `public AWSCredentialsType AWSCredentialsType { get; set; }`
- L32 _public property_ `public string AssumeRoleArn { get; set; }`
- L33 _public property_ `public string AwsSecretKey { get; set; }`
- L34 _public property_ `public string AwsAccessKey { get; set; }`
- L36-68 _public method_ `public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)`

#### enum `Jupiter.AWSCredentialsType`  
`public enum AWSCredentialsType`  
_public; L71-76_
- L73 _public* enumerator_ `Basic`
- L74 _public* enumerator_ `AssumeRole`
- L75 _public* enumerator_ `AssumeRoleWebIdentity`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Authentication/Acl.cs` (Jupiter.Common)


#### enum `Jupiter.JupiterAclAction`  
`public enum JupiterAclAction`  
_public; L13-66_
- L18 _public* enumerator_ `ReadObject` — General read access to refs / blobs and so on
- L22 _public* enumerator_ `WriteObject` — General write access to upload refs / blobs etc
- L26 _public* enumerator_ `DeleteObject` — Access to delete blobs / refs etc
- L31 _public* enumerator_ `DeleteBucket` — Access to delete a particular bucket
- L35 _public* enumerator_ `DeleteNamespace` — Access to delete a whole namespace
- L40 _public* enumerator_ `ReadTransactionLog` — Access to read the transaction log
- L45 _public* enumerator_ `WriteTransactionLog` — Access to write the transaction log
- L50 _public* enumerator_ `ReadBuildPart` — Access to read build parts
- L55 _public* enumerator_ `WriteBuildPart` — Access to write build parts
- L60 _public* enumerator_ `AdminAction` — Access to perform administrative task
- L65 _public* enumerator_ `EnumerateBucket` — Access to enumerate all objects in a bucket

#### class `Jupiter.AclEntry`  
`public class AclEntry`  
_public; L68-128_
- L74 _public property_ `public List<string> Claims { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — Claims required to be present to be allowed to do the actions - if multiple claims are present *all* of them are required
- L80 _public property_ `public List<JupiterAclAction> Actions { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — The actions granted if the claims match
- L82-122 _public method_ `public IEnumerable<JupiterAclAction> Resolve(ClaimsPrincipal user)`
- L124-127 _public method_ `public IEnumerable<JupiterAclAction> Resolve(AuthorizationHandlerContext context)`

#### class `Jupiter.AclPolicy`  
`public class AclPolicy`  
_public; L131-285_
- L137 _public property_ `public List<string> Claims { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — Claims required to be present to be allowed to do the actions - if multiple claims are present *all* of them are required
- L143 _public property_ `public List<JupiterAclAction> Actions { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — The actions granted if the claims match
- L149 _public property_ `public string Name { get; set; }` — Debug name used to log information about the policy
- L154 _public property_ `public AclScope? Scope { get; set; }` — Description of the scope for which this policy applies (typically some set of namespaces and or buckets)
- L156-284 _public method_ `public IEnumerable<JupiterAclAction> Resolve(ClaimsPrincipal user, AccessScope scope, ILogger logger, out List<string> matchedClaims)`

#### class `Jupiter.AclScope`  
`public class AclScope`  
_public; L291-313_
- L298 _public property_ `public List<AclScopeEntry> Namespaces { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — List of one or more namespaces that the parent policy applies to
- L305 _public property_ `public List<AclScopeEntry> Buckets { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — List of one or more buckets that the parent policy applies to
- L312 _public property_ `public List<AclResourceScopeEntry> Resources { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — List of one or more resources (by-name and type) that this policy applies to

#### class `Jupiter.AclResourceScopeEntry`  
`public class AclResourceScopeEntry : AclScopeEntry`  
_public; L318-322_
- inherits: `AclScopeEntry`
- desc: Potential mapping of a scope for a set of resources
- L321 _public property_ `public string? ResourceType { get; set; }` — attrs: `[Required]`

#### class `Jupiter.AclScopeEntry`  
`public class AclScopeEntry`  
_public; L328-422_
- L332 _public property_ `public List<string> Values { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]`
- L334 _public property_ `public string? Match { get; set; }`
- L335 _private property_ `private Regex? Regex { get; set; }`
- L336 _public property_ `public bool Not { get; set; }`
- L338-421 _public method_ `public bool Matches(string scope, ILogger logger, string policyName)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Authentication/DisabledAuthenticationHandler.cs` (Jupiter.Common)


#### class `Jupiter.DisabledAuthenticationHandler`  
`public class DisabledAuthenticationHandler : AuthenticationHandler<TestAuthenticationOptions>`  
_public; L15-33_
- inherits: `AuthenticationHandler<TestAuthenticationOptions>`
- L17-21 _public ctor_ `public DisabledAuthenticationHandler(IOptionsMonitor<TestAuthenticationOptions> options, ILoggerFactory logger, UrlEncoder encoder) : base(options, logger, encoder)`
- L23 _public property_ `public static string AuthenticateScheme { get; }`
- L25-32 _protected method_ `protected override Task<AuthenticateResult> HandleAuthenticateAsync()`

#### class `Jupiter.TestAuthenticationExtensions`  
`public static class TestAuthenticationExtensions`  
_public; L35-44_
- L37-43 _public method_ `public static AuthenticationBuilder AddTestAuth(this AuthenticationBuilder builder, Action<TestAuthenticationOptions> configOptions)`

#### class `Jupiter.TestAuthenticationOptions`  
`public class TestAuthenticationOptions : AuthenticationSchemeOptions`  
_public; L46-58_
- inherits: `AuthenticationSchemeOptions`
- L48 _public property_ `public ClaimsIdentity Identity { get; }`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Authentication/GlobalAuthorizationHandler.cs` (Jupiter.Common)


#### class `Jupiter.GlobalAccessRequest`  
`public class GlobalAccessRequest`  
_public; L11-14_
- L13 _public property_ `public JupiterAclAction[] Actions { get; init; }`

#### class `Jupiter.GlobalAuthorizationHandler`  
`public class GlobalAuthorizationHandler : AuthorizationHandler<GlobalAccessRequirement, GlobalAccessRequest>`  
_public; L19-63_
- inherits: `AuthorizationHandler<GlobalAccessRequirement, GlobalAccessRequest>`
- desc: Verifies that you have access to acl actions that are not tied to a namespace
- L21 _private field_ `private readonly IOptionsMonitor<AuthSettings> _authSettings`
- L23-26 _public ctor_ `public GlobalAuthorizationHandler(IOptionsMonitor<AuthSettings> authSettings)`
- L28-62 _protected method_ `protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, GlobalAccessRequirement requirement, GlobalAccessRequest accessRequest)`

#### class `Jupiter.GlobalAccessRequirement`  
`public class GlobalAccessRequirement : IAuthorizationRequirement`  
_public; L65-68_
- inherits: `IAuthorizationRequirement`
- L67 _public const_ `public const string Name = "GlobalAccess"`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Authentication/NamespaceAuthorizationHandler.cs` (Jupiter.Common)


#### class `Jupiter.NamespaceAccessRequest`  
`public class NamespaceAccessRequest`  
_public; L12-16_
- L14 _public property_ `public NamespaceId Namespace { get; init; }`
- L15 _public property_ `public JupiterAclAction[] Actions { get; init; }`

#### class `Jupiter.NamespaceAuthorizationHandler`  
`public class NamespaceAuthorizationHandler : AuthorizationHandler<NamespaceAccessRequirement, NamespaceAccessRequest>`  
_public; L19-81_
- inherits: `AuthorizationHandler<NamespaceAccessRequirement, NamespaceAccessRequest>`
- L21 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L22 _private field_ `private readonly IOptionsMonitor<AuthSettings> _authSettings`
- L24-28 _public ctor_ `public NamespaceAuthorizationHandler(INamespacePolicyResolver namespacePolicyResolver, IOptionsMonitor<AuthSettings> authSettings)`
- L30-80 _protected method_ `protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, NamespaceAccessRequirement requirement, NamespaceAccessRequest accessRequest)`

#### class `Jupiter.NamespaceAccessRequirement`  
`public class NamespaceAccessRequirement : IAuthorizationRequirement`  
_public; L83-86_
- inherits: `IAuthorizationRequirement`
- L85 _public const_ `public const string Name = "NamespaceAccess"`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Authentication/ScopeAuthorizationHandler.cs` (Jupiter.Common)


#### class `Jupiter.ScopeAccessRequest`  
`public class ScopeAccessRequest`  
_public; L13-17_
- L15 _public property_ `public JupiterAclAction[] Actions { get; init; }`
- L16 _public property_ `public AccessScope AccessScope { get; init; }`

#### class `Jupiter.AccessScope`  
`public class AccessScope`  
_public; L19-41_
- L21-25 _public ctor_ `public AccessScope(NamespaceId? ns = null, BucketId? bucket = null)`
- L27-33 _public ctor_ `public AccessScope(NamespaceId? ns, BucketId? bucket, string resourceType, string resourceName)`
- L35 _public property_ `public static AccessScope GlobalScope { get; }`
- L36 _public property_ `public NamespaceId? Namespace { get; }`
- L37 _public property_ `public BucketId? Bucket { get; }`
- L39 _public property_ `public string? ResourceType { get; }`
- L40 _public property_ `public string? ResourceName { get; }`

#### class `Jupiter.ScopeAuthorizationHandler`  
`public class ScopeAuthorizationHandler : AuthorizationHandler<ScopeAccessRequirement, ScopeAccessRequest>`  
_public; L43-119_
- inherits: `AuthorizationHandler<ScopeAccessRequirement, ScopeAccessRequest>`
- L45 _private field_ `private readonly IOptionsMonitor<AuthSettings> _authSettings`
- L46 _private field_ `private readonly ILogger<ScopeAuthorizationHandler> _logger`
- L47 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L49-54 _public ctor_ `public ScopeAuthorizationHandler(IOptionsMonitor<AuthSettings> authSettings, ILogger<ScopeAuthorizationHandler> logger, INamespacePolicyResolver namespacePolicyResolver)`
- L56-118 _protected method_ `protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, ScopeAccessRequirement requirement, ScopeAccessRequest accessRequest)`

#### class `Jupiter.ScopeAccessRequirement`  
`public class ScopeAccessRequirement : IAuthorizationRequirement`  
_public; L121-124_
- inherits: `IAuthorizationRequirement`
- L123 _public const_ `public const string Name = "ScopeAccess"`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Authentication/ServiceAccountAuthentication.cs` (Jupiter.Common)


#### class `Jupiter.ServiceAccountAuthOptions`  
`class ServiceAccountAuthOptions : AuthenticationSchemeOptions`  
_internal*; L18-28_
- inherits: `AuthenticationSchemeOptions`
- L27 _public property_ `public List<ServiceAccounts> Accounts { get; set; }`

#### class `Jupiter.ServiceAccountAuthOptions.ServiceAccounts`  
`public class ServiceAccounts`  
_public; L20-25_
- L22 _public property_ `public string Token { get; set; }` — attrs: `[Required]`
- L24 _public property_ `public List<string> Claims { get; set; }`

#### class `Jupiter.ServiceAccountAuthHandler`  
`class ServiceAccountAuthHandler : AuthenticationHandler<ServiceAccountAuthOptions>`  
_internal*; L30-92_
- inherits: `AuthenticationHandler<ServiceAccountAuthOptions>`
- L32 _private field_ `private readonly IOptionsMonitor<ServiceAccountAuthOptions> _options`
- L33 _public const_ `public const string AuthenticationScheme = "ServiceAccount"`
- L34 _public const_ `public const string Prefix = "ServiceAccount"`
- L36-41 _public ctor_ `public ServiceAccountAuthHandler(IOptionsMonitor<ServiceAccountAuthOptions> options, ILoggerFactory logger, UrlEncoder encoder) : base(options, logger, encoder)`
- L43-91 _protected method_ `protected override async Task<AuthenticateResult> HandleAuthenticateAsync()`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/BaseProgram.cs` (Jupiter.Common)


#### class `Jupiter.BaseProgram`  
`public static class BaseProgram<T> where T : BaseStartup`  
_public; L18-153_
- constraints: `where T : BaseStartup`
- L20 _private property_ `private static IConfiguration Configuration { get; }`
- L22-47 _private method_ `private static IConfiguration GetConfigurationBuilder()`
- L50-93 _public method_ `public static int BaseMain(string[] args)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1000:Do not declare static members on generic types", Justification = "Keep logic for the base program together")]`
- L96-152 _public method_ `public static IHostBuilder CreateHostBuilder(string[] args)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1000:Do not declare static members on generic types", Justification = "Keep logic for the base program together")]`

#### class `Jupiter.DatadogLogEnricher`  
`class DatadogLogEnricher : ILogEventEnricher`  
_internal*; L155-180_
- inherits: `ILogEventEnricher`
- L157-179 _public method_ `public void Enrich(Serilog.Events.LogEvent logEvent, ILogEventPropertyFactory propertyFactory)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/BaseStartup.cs` (Jupiter.Common)


#### class `Jupiter.BaseStartup`  
`public abstract class BaseStartup`  
_public; L49-595_
- L51 _protected property_ `protected ILogger Logger { get; }`
- L53-58 _protected ctor_ `protected BaseStartup(IConfiguration configuration, ILogger logger)`
- L60-68 _protected method_ `protected static ILogger CreateLogger<T>()`
- L70 _protected property_ `protected IConfiguration Configuration { get; }`
- L72 _private property_ `private AuthSettings Auth { get; }`
- L75-450 _public method_ `public void ConfigureServices(IServiceCollection services)`
- L452-459 _public method_ `public static void ConfigureJsonOptions(JsonSerializerOptions options)`
- L461-464 _private method_ `private Meter CreateMeter(IServiceProvider provider)`
- L466-471 _private method_ `private Tracer CreateTracer(IServiceProvider provider)`
- L473-478 _private method_ `private void OnAddHealthChecks(IServiceCollection services)`
- L486 _protected method_ `protected abstract void OnAddHealthChecks(IServiceCollection services, IHealthChecksBuilder healthChecks)` — Register health checks for individual services
- L488 _protected method_ `protected abstract void OnAddAuthorization(AuthorizationOptions authorizationOptions, List<string> defaultSchemes)`
- L490-492 _protected method_ `protected virtual void OnAddControllers(MvcOptions options)`
- L494 _protected method_ `protected abstract void OnAddService(IServiceCollection services)`
- L497-510 _public method_ `public void Configure(IApplicationBuilder app, IWebHostEnvironment env)`
- L512-583 _private method_ `private void ConfigureMiddlewares(JupiterSettings jupiterSettings, IApplicationBuilder app, IWebHostEnvironment env)`
- L585 _public property_ `public virtual bool UseDeveloperExceptionPage { get; }`
- L587-589 _protected method_ `protected virtual void OnConfigureAppEarly(IApplicationBuilder app, IWebHostEnvironment env)`
- L591-594 _protected method_ `protected virtual void OnConfigureApp(IApplicationBuilder app, IWebHostEnvironment env)`

#### enum `Jupiter.SchemeImplementations`  
`public enum SchemeImplementations`  
_public; L664-669_
- L666 _public* enumerator_ `JWTBearer`
- L667 _public* enumerator_ `Okta`
- L668 _public* enumerator_ `ServiceAccount`

#### class `Jupiter.AuthSchemeEntry`  
`public class AuthSchemeEntry : IValidatableObject`  
_public; L671-740_
- inherits: `IValidatableObject`
- L677 _public property_ `public SchemeImplementations Implementation { get; set; }` — attrs: `[Required]` — The implementation to use, this controls which other configuration values needs to be set. For most servers JWTBearer should work fine.
- L682 _public property_ `public string OktaDomain { get; set; }` — The Okta domain (url to your okta server - do not include the authorization server id)
- L686 _public property_ `public string OktaAuthorizationServerId { get; set; }` — The Okta AuthorizationServerId, this is used if you have more then one authorization server within your Okta server. We recommend using a separate authorization server for each major set of systems to reduce blast radius of security issues.
- L691 _public property_ `public string JwtAuthority { get; set; }` — The JWT Authority (url to your IdP)
- L697 _public property_ `public string JwtAudience { get; set; }` — attrs: `[Required]` — The audience for the token, this is usually defined by your IdP
- L702 _public property_ `public string[] AllowedNamespaces { get; set; }` — The namespaces which these scheme is allowed to grant access to, all if this is omitted or empty
- L704-739 _public method_ `public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)`

#### class `Jupiter.ProviderInfo`  
`public class ProviderInfo`  
_public; L745-797_
- desc: The definition of how a specific oidc client works, should be the same as ProviderInfo in EpicGames.Okta. This will be read by EpicGames.Okta so its definition is authoritative.
- L750 _public property_ `public Uri ServerUri { get; set; }` — attrs: `[Required]` — The server uri to the IdP
- L756 _public property_ `public string ClientId { get; set; }` — attrs: `[Required]`
- L762 _public property_ `public string DisplayName { get; set; }` — attrs: `[Required]`
- L767 _public property_ `public Uri? RedirectUri { get; set; }` — The redirect uri - deprecated - use PossibleRedirectUri instead as supporting multiple ports is very useful when running on localhost were ports maybe taken
- L773 _public property_ `public List<Uri>? PossibleRedirectUri { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — List of redirect uris that can be used (are allow listed in the IdP). In priority order.
- L778 _public property_ `public bool LoadClaimsFromUserProfile { get; set; }` — attrs: `[Required]` — Enable to load claims from the user profile after the token has been read. Converted it from a thin token to a think token.
- L783 _public property_ `public string Scopes { get; set; }` — The scopes to request
- L788 _public property_ `public string? GenericErrorInformation { get; set; }` — A string added to the local error page when failing to login, usually a good place to tell users who and how to get help.
- L793 _public property_ `public bool UseDiscoveryDocument { get; set; }` — Can be disabled to not use the discovery documents that are part of the oidc standard to find endpoints.

#### class `Jupiter.ClientOidcConfiguration`  
`public class ClientOidcConfiguration`  
_public; L799-805_
- L801 _public property_ `public string? DefaultProvider { get; set; }`
- L804 _public property_ `public Dictionary<string, ProviderInfo> Providers { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]`

#### class `Jupiter.AuthSettings`  
`public class AuthSettings : IValidatableObject`  
_public; L807-876_
- inherits: `IValidatableObject`
- L812 _public property_ `public string DefaultScheme { get; set; }` — The name of the scheme to use by default
- L817 _public property_ `public bool Enabled { get; set; }` — Used to disable authentication, not recommended to set for anything other then local use cases
- L822 _public property_ `public bool RequireAcls { get; set; }` — Can be set to require acls to be used even if auth is disabled, mostly used for testing
- L825 _public property_ `public Dictionary<string, AuthSchemeEntry> Schemes { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]`
- L828 _public property_ `public List<AclEntry> Acls { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]`
- L833 _public property_ `public bool RemapNameClaim { get; set; }` — Remaps name claim from http://schemas.xmlsoap.org/ws/2005/05/identity/claims/name to http://schemas.xmlsoap.org/ws/2005/05/identity/claims/nameidentifier which is required for Okta
- L839 _public property_ `public List<AclPolicy> Policies { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — Setup policies for how access control is managed
- L844 _public property_ `public bool UseLegacyConfiguration { get; set; }` — Set to true to also consider the legacy configuration in the acl fields of this object as well as within the namespace policy for endpoints that support the acl policies
- L849 _public property_ `public ClientOidcConfiguration? ClientOidcConfiguration { get; set; }` — Configuration read by clients on how to interactively login locally
- L854 _public property_ `public string ClientOidcEncryptionKey { get; set; }` — The encryption key used to encrypt the configuration - usually not modified as you then need to also distribute this key. This needs to be exactly 16 bytes
- L856-875 _public method_ `public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)`

#### class `Jupiter.JupiterSettings`  
`public class JupiterSettings`  
_public; L878-941_
- L881 _public property_ `public bool ShowPII { get; set; }`
- L882 _public property_ `public bool DisableHealthChecks { get; set; }`
- L883 _public property_ `public bool HostSwaggerDocumentation { get; set; }`
- L891 _public property_ `public List<int> InternalApiPorts { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — Port used to host the internally accessible api (as well as the public api). This hosts both public and private namespaces
- L898 _public property_ `public List<int> CorpApiPorts { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — Port that hosts public and private namespaces
- L905 _public property_ `public List<int> PublicApiPorts { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]` — Port that only hosts the public namespaces
- L908 _public property_ `public bool UseRequestLogging { get; set; }`
- L915 _public property_ `public string CurrentSite { get; set; }` — attrs: `[Required] [Key]` — Name of the current site, has to be globally unique across all deployments
- L920 _public property_ `public string DomainSocketsRoot { get; set; }` — Used to move where domain sockets are allocated
- L925 _public property_ `public bool UseDomainSockets { get; set; }` — Enable to create unix domain sockets for inter process communication
- L930 _public property_ `public bool ChmodDomainSockets { get; set; }` — Enable to change access (chmod) the sockets to allow for anyone to access them
- L935 _public property_ `public bool AssumeLocalConnectionsHasFullAccess { get; set; }` — Assumes that any local connection should have full access, this is used only for tests
- L940 _public property_ `public int? PendingConnectionMax { get; set; }` — Set this to increase the max number of TCP connections that are allowed to be queued.

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Controllers/ErrorController.cs` (Jupiter.Common)


#### class `Jupiter.Controllers.ErrorController`  
`public class ErrorController : ControllerBase`  
_public; L12-42_
- attrs: `[ApiController] [ApiExplorerSettings(IgnoreApi = true)]`
- inherits: `ControllerBase`
- L15-41 _public method_ `public IActionResult Error()` — attrs: `[Route("/error")]`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/BlobContents.cs` (Jupiter.Common)


#### class `Jupiter.Implementation.BlobContents`  
`public sealed class BlobContents : IDisposable, IAsyncDisposable`  
_public; L10-79_
- inherits: `IDisposable, IAsyncDisposable`
- L12 _private field_ `private Stream? _stream`
- L13 _private field_ `private readonly IBufferedPayload? _bufferedPayload`
- L15-22 _public ctor_ `public BlobContents(Stream stream, long length, string? localPath = null, string? absolutePath = null)`
- L24-29 _public ctor_ `public BlobContents(byte[] payload)`
- L31-36 _public ctor_ `public BlobContents(IBufferedPayload payload)`
- L38-41 _public ctor_ `public BlobContents(Uri redirectUri)`
- L43 _public property_ `public Uri? RedirectUri { get; }`
- L45-60 _public property_ `public Stream Stream { get; }`
- L61 _public property_ `public long Length { get; }`
- L63 _public property_ `public string? LocalPath { get; }`
- L64 _public property_ `public string? AbsolutePath { get; }`
- L66 _public property_ `public IBufferedPayload? BufferedPayload => ...`
- L68-72 _public method_ `public void Dispose()`
- L74-78 _public method_ `public ValueTask DisposeAsync()`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/BlobId.cs` (Jupiter.Common)


#### class `Jupiter.Implementation.BlobId`  
`public class BlobId : ContentHash, IEquatable<BlobId>`  
_public; L21-165_
- attrs: `[TypeConverter(typeof(BlobIdentifierTypeConverter))] [JsonConverter(typeof(BlobIdentifierJsonConverter))] [CbConverter(typeof(BlobIdentifierCbConverter))]`
- inherits: `ContentHash, IEquatable<BlobId>`
- L24 _private const_ `private const int MultiThreadedSize = 1_000_000`
- L25 _private field_ `private string? _stringIdentifier`
- L27-29 _public ctor_ `public BlobId(byte[] identifier) : base(identifier)`
- L32-35 _public ctor_ `public BlobId(string identifier) : base(identifier)` — attrs: `[JsonConstructor]`
- L37-40 _public method_ `public override int GetHashCode()`
- L42-50 _public method_ `public bool Equals(BlobId? other)`
- L52-70 _public method_ `public override bool Equals(object? obj)`
- L72-80 _public method_ `public override string ToString()`
- L82-101 _public method_ `public static new BlobId FromBlob(byte[] blobMemory)`
- L103-122 _public method_ `public static BlobId FromBlob(in Memory<byte> blobMemory)`
- L124-127 _public method_ `public static BlobId FromContentHash(ContentHash testObjectHash)`
- L129-154 _public method_ `public static async Task<BlobId> FromStreamAsync(Stream stream, CancellationToken cancellationToken = default)`
- L156-159 _public method_ `public static BlobId FromIoHash(IoHash blobIdentifier)`
- L161-164 _public method_ `public IoHash AsIoHash()`

#### class `Jupiter.Implementation.BlobIdentifierTypeConverter`  
`public class BlobIdentifierTypeConverter : TypeConverter`  
_public; L167-206_
- inherits: `TypeConverter`
- L169-176 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)`
- L178-186 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)`
- L188-195 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)`
- L197-205 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)`

#### class `Jupiter.Implementation.BlobIdentifierJsonConverter`  
`public class BlobIdentifierJsonConverter : JsonConverter<BlobId>`  
_public; L208-225_
- inherits: `JsonConverter<BlobId>`
- L210-219 _public method_ `public override BlobId? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L221-224 _public method_ `public override void Write(Utf8JsonWriter writer, BlobId value, JsonSerializerOptions options)`

#### class `Jupiter.Implementation.BlobIdentifierCbConverter`  
`public class BlobIdentifierCbConverter : CbConverter<BlobId>`  
_public; L227-236_
- inherits: `CbConverter<BlobId>`
- L229 _public method_ `public override BlobId Read(CbField field)`
- L232 _public method_ `public override void Write(CbWriter writer, BlobId value)` — (inheritdoc)
- L235 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, BlobId value)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/BucketId.cs` (Jupiter.Common)


#### struct `Jupiter.Common.BucketId`  
`public struct BucketId : IEquatable<BucketId>`  
_public; L19-61_
- attrs: `[JsonConverter(typeof(BucketIdJsonConverter))] [TypeConverter(typeof(BucketIdTypeConverter))] [CbConverter(typeof(BucketIdCbConverter))]`
- inherits: `IEquatable<BucketId>`
- desc: Identifier for a storage bucket
- L24 _private* field_ `readonly StringId _inner` — The text representing this id
- L30-39 _public ctor_ `public BucketId(string input)` — Constructor
- L42 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L45 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L48 _public method_ `public bool Equals(BucketId other)` — (inheritdoc)
- L51 _public method_ `public override string ToString()` — (inheritdoc)
- L54 _public operator_ `public static bool operator ==(BucketId left, BucketId right)` — (inheritdoc)
- L57 _public operator_ `public static bool operator !=(BucketId left, BucketId right)` — (inheritdoc)
- L60 _private const_ `private const int MaxLength = 256`

#### class `Jupiter.Common.BucketIdJsonConverter`  
`sealed class BucketIdJsonConverter : JsonConverter<BucketId>`  
_internal*; L66-73_
- inherits: `JsonConverter<BucketId>`
- desc: Type converter for BucketId to and from JSON
- L69 _public method_ `public override BucketId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L72 _public method_ `public override void Write(Utf8JsonWriter writer, BucketId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `Jupiter.Common.BucketIdTypeConverter`  
`sealed class BucketIdTypeConverter : TypeConverter`  
_internal*; L78-85_
- inherits: `TypeConverter`
- desc: Type converter from strings to BucketId objects
- L81 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type? sourceType)` — (inheritdoc)
- L84 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object? value)` — (inheritdoc)

#### class `Jupiter.Common.BucketIdCbConverter`  
`sealed class BucketIdCbConverter : CbConverter<BucketId>`  
_internal*; L87-96_
- inherits: `CbConverter<BucketId>`
- L89 _public method_ `public override BucketId Read(CbField field)`
- L92 _public method_ `public override void Write(CbWriter writer, BucketId value)` — (inheritdoc)
- L95 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, BucketId value)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/BuildName.cs` (Jupiter.Common)


#### struct `Jupiter.Implementation.BuildName`  
`public readonly struct BuildName : IEquatable<BuildName>`  
_public; L19-52_
- attrs: `[JsonConverter(typeof(BuildNameJsonConverter))] [TypeConverter(typeof(BuildNameTypeConverter))] [CbConverter(typeof(BuildNameCbConverter))]`
- inherits: `IEquatable<BuildName>`
- desc: Identifier for a build
- L24 _private* field_ `readonly StringId _inner` — The text representing this id
- L30-33 _public ctor_ `public BuildName(string input)` — Constructor
- L36 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L39 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L42 _public method_ `public bool Equals(BuildName other)` — (inheritdoc)
- L45 _public method_ `public override string ToString()` — (inheritdoc)
- L48 _public operator_ `public static bool operator ==(BuildName left, BuildName right)` — (inheritdoc)
- L51 _public operator_ `public static bool operator !=(BuildName left, BuildName right)` — (inheritdoc)

#### class `Jupiter.Implementation.BuildNameJsonConverter`  
`sealed class BuildNameJsonConverter : JsonConverter<BuildName>`  
_internal*; L57-64_
- inherits: `JsonConverter<BuildName>`
- desc: Type converter for BucketId to and from JSON
- L60 _public method_ `public override BuildName Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L63 _public method_ `public override void Write(Utf8JsonWriter writer, BuildName value, JsonSerializerOptions options)` — (inheritdoc)

#### class `Jupiter.Implementation.BuildNameTypeConverter`  
`sealed class BuildNameTypeConverter : TypeConverter`  
_internal*; L69-76_
- inherits: `TypeConverter`
- desc: Type converter from strings to BucketId objects
- L72 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type? sourceType)` — (inheritdoc)
- L75 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object? value)` — (inheritdoc)

#### class `Jupiter.Implementation.BuildNameCbConverter`  
`sealed class BuildNameCbConverter : CbConverter<BuildName>`  
_internal*; L78-87_
- inherits: `CbConverter<BuildName>`
- L80 _public method_ `public override BuildName Read(CbField field)`
- L83 _public method_ `public override void Write(CbWriter writer, BuildName value)` — (inheritdoc)
- L86 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, BuildName value)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/ClientCredentialOAuthAuthenticator.cs` (Jupiter.Common)


#### interface `Jupiter.Implementation.IAuthenticator`  
`public interface IAuthenticator`  
_public; L12-15_
- L14 _public method_ `public Task<string?> AuthenticateAsync(CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.ClientCredentialOAuthAuthenticator`  
`public class ClientCredentialOAuthAuthenticator : IAuthenticator`  
_public; L17-88_
- inherits: `IAuthenticator`
- L19-26 _public ctor_ `public ClientCredentialOAuthAuthenticator(IHttpClientFactory httpClientFactory, Uri authUrl, string clientId, string clientSecret, string scope)`
- L28 _private field_ `private string? _accessToken`
- L30 _private field_ `private readonly IHttpClientFactory _httpClientFactory`
- L31 _private field_ `private readonly Uri _authUrl`
- L32 _private field_ `private readonly string _clientId`
- L33 _private field_ `private readonly string _clientSecret`
- L34 _private field_ `private readonly string _scope`
- L35 _private field_ `private DateTime _expiresAt`
- L37-45 _public method_ `public async Task<string?> AuthenticateAsync(CancellationToken cancellationToken = default)`
- L47-59 _private method_ `private async Task PreAuthenticateAsync(CancellationToken cancellationToken = default)`
- L61-87 _private method_ `private async Task<(ClientCredentialsResponse, string)> DoAuthenticationRequestAsync(CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.ClientCredentialsResponse`  
`internal class ClientCredentialsResponse`  
_internal; L91-100_
- L93 _public property_ `public string? access_token { get; set; }`
- L95 _public property_ `public string? token_type { get; set; }`
- L97 _public property_ `public int? expires_in { get; set; }`
- L99 _public property_ `public string? scope { get; set; }`

#### class `Jupiter.Implementation.AuthenticationFailedException`  
`public class AuthenticationFailedException : Exception`  
_public; L102-105_
- inherits: `Exception`
- L104 _public ctor_ `public AuthenticationFailedException(string errorResult) : base(errorResult)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/ContentHash.cs` (Jupiter.Common)


#### class `Jupiter.Implementation.ContentHash`  
`public class ContentHash : IEquatable<ContentHash>, IEquatable<byte[]>`  
_public; L18-111_
- attrs: `[TypeConverter(typeof(ContentHashTypeConverter))] [JsonConverter(typeof(ContentHashJsonConverter))] [CbConverter(typeof(ContentHashCbConverter))]`
- inherits: `IEquatable<ContentHash>, IEquatable<byte[]>`
- L20 _protected property_ `protected ByteArrayComparer Comparer { get; }`
- L21 _protected property_ `protected byte[] Identifier { get; init; }`
- L22 _public const_ `public const int HashLength = 20`
- L24 _public property_ `public byte[] HashData => ...`
- L25-32 _public ctor_ `public ContentHash(byte[] identifier)`
- L35-48 _public ctor_ `public ContentHash(string identifier)` — attrs: `[JsonConstructor]`
- L50-53 _public method_ `public override int GetHashCode()`
- L55-63 _public method_ `public bool Equals(ContentHash? other)`
- L65-73 _public method_ `public bool Equals(byte[]? other)`
- L75-93 _public method_ `public override bool Equals(object? obj)`
- L95-98 _public method_ `public override string ToString()`
- L100-110 _public method_ `public static ContentHash FromBlob(byte[] blobMemory)`

#### class `Jupiter.Implementation.ContentHashCbConverter`  
`public class ContentHashCbConverter : CbConverter<ContentHash>`  
_public; L113-122_
- inherits: `CbConverter<ContentHash>`
- L115 _public method_ `public override ContentHash Read(CbField field)`
- L118 _public method_ `public override void Write(CbWriter writer, ContentHash value)` — (inheritdoc)
- L121 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, ContentHash value)` — (inheritdoc)

#### class `Jupiter.Implementation.ContentHashJsonConverter`  
`public class ContentHashJsonConverter : JsonConverter<ContentHash>`  
_public; L124-141_
- inherits: `JsonConverter<ContentHash>`
- L126-135 _public method_ `public override ContentHash Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L137-140 _public method_ `public override void Write(Utf8JsonWriter writer, ContentHash value, JsonSerializerOptions options)`

#### class `Jupiter.Implementation.ContentHashTypeConverter`  
`public class ContentHashTypeConverter : TypeConverter`  
_public; L143-182_
- inherits: `TypeConverter`
- L145-152 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)`
- L154-162 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)`
- L164-171 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)`
- L173-181 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/ContentId.cs` (Jupiter.Common)


#### class `Jupiter.Implementation.ContentId`  
`public class ContentId : ContentHash, IEquatable<ContentId>`  
_public; L17-88_
- attrs: `[TypeConverter(typeof(ContentIdTypeConverter))] [JsonConverter(typeof(ContentIdJsonConverter))] [CbConverter(typeof(ContentIdCbConverter))]`
- inherits: `ContentHash, IEquatable<ContentId>`
- L19-21 _public ctor_ `public ContentId(byte[] identifier) : base(identifier)`
- L24-27 _public ctor_ `public ContentId(string identifier) : base(identifier)` — attrs: `[JsonConstructor]`
- L29-32 _public method_ `public override int GetHashCode()`
- L34-42 _public method_ `public bool Equals(ContentId? other)`
- L44-62 _public method_ `public override bool Equals(object? obj)`
- L64-67 _public method_ `public static ContentId FromContentHash(ContentHash contentHash)`
- L69-72 _public method_ `public static ContentId FromBlobIdentifier(BlobId blobIdentifier)`
- L74-77 _public method_ `public BlobId AsBlobIdentifier()`
- L79-82 _public method_ `public static ContentId FromIoHash(IoHash ioHash)`
- L84-87 _public method_ `public IoHash AsIoHash()`

#### class `Jupiter.Implementation.ContentIdTypeConverter`  
`public class ContentIdTypeConverter : TypeConverter`  
_public; L90-119_
- inherits: `TypeConverter`
- L92-103 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)`
- L105-118 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)`

#### class `Jupiter.Implementation.ContentIdJsonConverter`  
`public class ContentIdJsonConverter : JsonConverter<ContentId>`  
_public; L121-138_
- inherits: `JsonConverter<ContentId>`
- L123-132 _public method_ `public override ContentId? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L134-137 _public method_ `public override void Write(Utf8JsonWriter writer, ContentId value, JsonSerializerOptions options)`

#### class `Jupiter.Implementation.ContentIdCbConverter`  
`public class ContentIdCbConverter : CbConverter<ContentId>`  
_public; L140-149_
- inherits: `CbConverter<ContentId>`
- L142 _public method_ `public override ContentId Read(CbField field)`
- L145 _public method_ `public override void Write(CbWriter writer, ContentId value)` — (inheritdoc)
- L148 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, ContentId value)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/InstrumentedStream.cs` (Jupiter.Common)


#### class `Jupiter.Common.Implementation.InstrumentedStream`  
`public class InstrumentedStream : Stream`  
_public; L15-104_
- inherits: `Stream`
- desc: Wraps a stream and adds instrumentation for throughput which is written to a counter
- L17 _private field_ `private readonly Stream _streamImplementation`
- L18 _private field_ `private readonly string _sourceIdentifier`
- L19 _private field_ `private bool _started = false`
- L20 _private field_ `private long _totalBytesWritten = 0`
- L21 _private field_ `private DateTime _consumeStartedAt`
- L23 _private field_ `private static Histogram<double>? s_streamThroughputCounter`
- L25-34 _public ctor_ `public InstrumentedStream(Stream s, Meter meter, string sourceIdentifier)`
- L36-41 _public method_ `public override async ValueTask DisposeAsync()`
- L43-50 _public method_ `public override void Close()`
- L52-55 _public method_ `public override void Flush()`
- L57-67 _public method_ `public override int Read(byte[] buffer, int offset, int count)`
- L69-72 _public method_ `public override long Seek(long offset, SeekOrigin origin)`
- L74-77 _public method_ `public override void SetLength(long value)`
- L79-89 _public method_ `public override void Write(byte[] buffer, int offset, int count)`
- L91 _public property_ `public override bool CanRead => ...`
- L93 _public property_ `public override bool CanSeek => ...`
- L95 _public property_ `public override bool CanWrite => ...`
- L97 _public property_ `public override long Length => ...`
- L99-103 _public property_ `public override long Position { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/NamespacePolicyResolver.cs` (Jupiter.Common)


#### interface `Jupiter.Common.INamespacePolicyResolver`  
`public interface INamespacePolicyResolver`  
_public; L9-14_
- L11 _public method_ `public NamespacePolicy GetPoliciesForNs(NamespaceId ns)`
- L13 _public* property_ `static NamespaceId JupiterInternalNamespace => ...`

#### class `Jupiter.Common.NamespaceSettings`  
`public class NamespaceSettings`  
_public; L16-20_
- L19 _public property_ `public Dictionary<string, NamespacePolicy> Policies { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]`

#### class `Jupiter.Common.NamespacePolicy`  
`public class NamespacePolicy`  
_public; L22-73_
- L25 _public property_ `public List<AclEntry> Acls { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by the configuration system")]`
- L26 _public property_ `public string StoragePool { get; set; }`
- L28 _public property_ `public bool LastAccessTracking { get; set; }`
- L29 _public property_ `public bool OnDemandReplication { get; set; }`
- L30 _public property_ `public bool UseBlobIndexForExists { get; set; }`
- L31 _public property_ `public bool UseBlobIndexForSlowExists { get; set; }`
- L32 _public property_ `public bool IsPublicNamespace { get; set; }`
- L33 _public property_ `public NamespaceId? FallbackNamespace { get; set; }`
- L34 _public property_ `public bool PopulateFallbackNamespaceOnUpload { get; set; }`
- L36 _public property_ `public bool UseContentAddressedStorage { get; set; }`
- L41 _public property_ `public ulong? MaxFilesystemStorageBytes { get; set; }` — Set to limit the amount of bytes used for filesystem storage - PerNamespaceGc needs to be set in the Filesystem settings for this to be applicable
- L46 _public property_ `public bool? BypassCacheOnWrite { get; set; }` — When enabled blobs that are written are not saved in the cache, only read blobs would be saved. Useful for write heavy operations were we frequently only read parts of the data.
- L68 _public property_ `public StoragePoolGCMethod? GcMethod { get; set; }`
- L70 _public property_ `public TimeSpan DefaultTTL { get; set; }`
- L71 _public property_ `public bool AllowRedirectUris { get; set; }`
- L72 _public property_ `public bool AllowOverwritesOfRefs { get; set; }`

#### enum `Jupiter.Common.NamespacePolicy.StoragePoolGCMethod`  
`public enum StoragePoolGCMethod`  
_public; L48-66_
- L53 _public* enumerator_ `None` — Never run GC on this namespace
- L57 _public* enumerator_ `LastAccess` — Apply last access deletion, objects not used for a duration set in GCSettings will be removed
- L61 _public* enumerator_ `TTL` — Objects are removed after DefaultTTL time has passed, no matter if they are used or not
- L65 _public* enumerator_ `Always` — Always GC references to this namespace, used to opt in to cleaning out old data

#### class `Jupiter.Common.NamespacePolicyResolver`  
`public class NamespacePolicyResolver : INamespacePolicyResolver`  
_public; L75-117_
- inherits: `INamespacePolicyResolver`
- L77 _private field_ `private readonly IOptionsMonitor<NamespaceSettings> _namespaceSettings`
- L78 _private field_ `private readonly NamespacePolicy _internalNamespacePolicy`
- L80-94 _public ctor_ `public NamespacePolicyResolver(IOptionsMonitor<NamespaceSettings> namespaceSettings, IOptionsMonitor<AuthSettings> authSettings)`
- L96-116 _public method_ `public NamespacePolicy GetPoliciesForNs(NamespaceId ns)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/RefId.cs` (Jupiter.Common)


#### struct `Jupiter.Implementation.RefId`  
`public readonly struct RefId : IEquatable<RefId>`  
_public; L19-96_
- attrs: `[TypeConverter(typeof(IoHashKeyTypeConverter))] [JsonConverter(typeof(IoHashKeyJsonConverter))] [CbConverter(typeof(IoHashKeyCbConverter))]`
- inherits: `IEquatable<RefId>`
- L21-37 _public ctor_ `public RefId(string key)`
- L39-50 _private* method_ `static bool IsValidCharacter(char c)`
- L51 _private* field_ `readonly string _text`
- L53-55 _public ctor_ `public RefId(byte[] hash) : this(StringUtils.FormatAsHexLowerString(hash))`
- L57-60 _public method_ `public bool Equals(RefId other)`
- L62-65 _public method_ `public override bool Equals(object? obj)`
- L67-70 _public method_ `public override int GetHashCode()`
- L72-75 _public method_ `public override string ToString()`
- L77-80 _public operator_ `public static bool operator ==(RefId left, RefId right)`
- L82-85 _public operator_ `public static bool operator !=(RefId left, RefId right)`
- L87-90 _public method_ `public static RefId FromName(string s)`
- L92-95 _public method_ `public IoHash AsIoHash()`

#### class `Jupiter.Implementation.IoHashKeyTypeConverter`  
`public sealed class IoHashKeyTypeConverter : TypeConverter`  
_public; L98-120_
- inherits: `TypeConverter`
- L101-109 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L111-119 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)`

#### class `Jupiter.Implementation.IoHashKeyJsonConverter`  
`public class IoHashKeyJsonConverter : JsonConverter<RefId>`  
_public; L122-139_
- inherits: `JsonConverter<RefId>`
- L124-133 _public method_ `public override RefId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L135-138 _public method_ `public override void Write(Utf8JsonWriter writer, RefId value, JsonSerializerOptions options)`

#### class `Jupiter.Implementation.IoHashKeyCbConverter`  
`sealed class IoHashKeyCbConverter : CbConverter<RefId>`  
_internal*; L141-150_
- inherits: `CbConverter<RefId>`
- L143 _public method_ `public override RefId Read(CbField field)`
- L146 _public method_ `public override void Write(CbWriter writer, RefId value)` — (inheritdoc)
- L149 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, RefId value)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/SecretResolver.cs` (Jupiter.Common)


#### interface `Jupiter.Common.Implementation.ISecretResolver`  
`public interface ISecretResolver`  
_public; L18-21_
- L20 _public* method_ `string Resolve(string value)`

#### class `Jupiter.Common.Implementation.SecretResolver`  
`public class SecretResolver : ISecretResolver`  
_public; L23-142_
- inherits: `ISecretResolver`
- L25 _private field_ `private readonly IServiceProvider _serviceProvider`
- L26 _private field_ `private readonly ILogger _logger`
- L28-32 _public ctor_ `public SecretResolver(IServiceProvider serviceProvider, ILogger<SecretResolver> logger)`
- L34-45 _public method_ `public string Resolve(string value)`
- L47-59 _private method_ `private string ResolveUsingProvider(string providerId, string providerPath, string originalValue)`
- L61-104 _private method_ `private string ResolveAWSSecret(string providerPath)`
- L115-127 _private method_ `private static string ResolveAKVSecret(string providerPath)` — AKV = Azure Key Vault. Uses DefaultAzureCredential to get a secret from Azure Key Vault. Using DefaultAzureCredential lets us debug using VisualStudioCredential and deploy to an app service that uses ManagedIdentityCredential.
- L129-141 _private method_ `private static bool SplitByFirstSeparator(string fullPath, char sep, out string left, out string? right)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Implementation/StreamingBodyPayload.cs` (Jupiter.Common)


#### interface `Jupiter.Common.Implementation.IBufferedPayload`  
`public interface IBufferedPayload : IDisposable`  
_public; L14-18_
- inherits: `IDisposable`
- L16 _public* method_ `Stream GetStream()`
- L17 _public* property_ `long Length { get; }`

#### class `Jupiter.Common.Implementation.MemoryBufferedPayload`  
`public sealed class MemoryBufferedPayload : IBufferedPayload`  
_public; L23-53_
- inherits: `IBufferedPayload`
- desc: Streaming request that is streamed into memory
- L25 _private field_ `private readonly byte[] _buffer`
- L27-30 _public ctor_ `public MemoryBufferedPayload(byte[] source)`
- L32-40 _public method_ `public static async Task<MemoryBufferedPayload> CreateAsync(Tracer tracer, Stream s, CancellationToken cancellationToken)`
- L42-45 _public method_ `public void Dispose()`
- L47-50 _public method_ `public Stream GetStream()`
- L52 _public property_ `public long Length => ...`

#### class `Jupiter.Common.Implementation.FilesystemBufferedPayloadWriter`  
`public sealed class FilesystemBufferedPayloadWriter : IDisposable`  
_public; L58-102_
- inherits: `IDisposable`
- desc: Helper to generate a filesystem buffered payload from a stream
- L60 _private field_ `private FileInfo? _tempFile`
- L62-65 _private ctor_ `private FilesystemBufferedPayloadWriter(string filesystemRoot, string debugPrefix)`
- L67-73 _public method_ `public void Dispose()`
- L75-86 _public method_ `public FilesystemBufferedPayload Done()`
- L88-96 _public method_ `public Stream GetWritableStream()`
- L98-101 _public method_ `public static FilesystemBufferedPayloadWriter Create(string filesystemTempPayloadRoot, string debugPrefix)`

#### class `Jupiter.Common.Implementation.FilesystemBufferedPayload`  
`public sealed class FilesystemBufferedPayload : IBufferedPayload`  
_public; L107-158_
- inherits: `IBufferedPayload`
- desc: A streaming request backed by a temporary file on disk
- L109 _private field_ `private readonly FileInfo _tempFile`
- L110 _private field_ `private long _length`
- L112 _public property_ `public FileInfo TempFile => ...`
- L114-117 _private ctor_ `private FilesystemBufferedPayload(string filesystemRoot, string debugPrefix)`
- L119-124 _internal ctor_ `internal FilesystemBufferedPayload(FileInfo bufferFile)`
- L126-142 _public method_ `public static async Task<FilesystemBufferedPayload> CreateAsync(Tracer tracer, Stream s, string filesystemRoot, string debugPrefix, CancellationToken cancellationToken)`
- L144-150 _public method_ `public void Dispose()`
- L152-155 _public method_ `public Stream GetStream()`
- L157 _public property_ `public long Length => ...`

#### class `Jupiter.Common.Implementation.BufferedPayloadOptions`  
`public class BufferedPayloadOptions`  
_public; L160-171_
- L165 _public property_ `public long MemoryBufferSize { get; set; }` — If the request is smaller then MemoryBufferSize we buffer it in memory rather then as a file
- L170 _public property_ `public string FilesystemTempPayloadRoot { get; set; }` — The default root to create temporary buffered files under, defaults to %TEMP%/temp-payloads or /tmp/temp-payloads

#### class `Jupiter.Common.Implementation.BufferedPayloadFactory`  
`public class BufferedPayloadFactory`  
_public; L173-225_
- L175 _private field_ `private readonly IOptionsMonitor<BufferedPayloadOptions> _options`
- L176 _private field_ `private readonly Tracer _tracer`
- L178-184 _public ctor_ `public BufferedPayloadFactory(IOptionsMonitor<BufferedPayloadOptions> options, Tracer tracer)`
- L186-196 _public method_ `public Task<IBufferedPayload> CreateFromRequestAsync(HttpRequest request, string debugPrefix, CancellationToken cancellationToken)`
- L198-214 _public method_ `public async Task<IBufferedPayload> CreateFromStreamAsync(Stream s, long contentLength, string debugPrefix, CancellationToken cancellationToken)`
- L216-219 _public method_ `public async Task<IBufferedPayload> CreateFilesystemBufferedPayloadAsync(Stream s, string debugPrefix, CancellationToken cancellationToken)`
- L221-224 _public method_ `public FilesystemBufferedPayloadWriter CreateFilesystemBufferedPayloadWriter(string debugPrefix)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/InternalApiFilterAttribute.cs` (Jupiter.Common)


#### class `Jupiter.Implementation.InternalApiFilterAttribute`  
`public sealed class InternalApiFilterAttribute : Attribute, IResourceFilter`  
_public; L12-31_
- attrs: `[AttributeUsage(AttributeTargets.Method | AttributeTargets.Class)]`
- inherits: `Attribute, IResourceFilter`
- L14-26 _public method_ `public void OnResourceExecuting(ResourceExecutingContext context)`
- L28-30 _public method_ `public void OnResourceExecuted(ResourceExecutedContext context)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/NamespaceId.cs` (Jupiter.Common)


#### struct `Jupiter.Common.NamespaceId`  
`public readonly struct NamespaceId : IEquatable<NamespaceId>`  
_public; L19-61_
- attrs: `[LogValueType] [JsonSchemaString] [JsonConverter(typeof(NamespaceIdJsonConverter))] [TypeConverter(typeof(NamespaceIdTypeConverter))]`
- inherits: `IEquatable<NamespaceId>`
- desc: Identifier for a storage namespace
- L24 _public property_ `public StringId Text { get; }` — The text representing this id
- L30-33 _public ctor_ `public NamespaceId(string text) : this(new Utf8String(text))` — Constructor
- L39-42 _public ctor_ `public NamespaceId(Utf8String text)` — Constructor
- L45 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L48 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L51 _public method_ `public bool Equals(NamespaceId other)` — (inheritdoc)
- L54 _public method_ `public override string ToString()` — (inheritdoc)
- L57 _public operator_ `public static bool operator ==(NamespaceId left, NamespaceId right)` — (inheritdoc)
- L60 _public operator_ `public static bool operator !=(NamespaceId left, NamespaceId right)` — (inheritdoc)

#### class `Jupiter.Common.NamespaceIdJsonConverter`  
`sealed class NamespaceIdJsonConverter : JsonConverter<NamespaceId>`  
_internal*; L66-73_
- inherits: `JsonConverter<NamespaceId>`
- desc: Type converter for NamespaceId to and from JSON
- L69 _public method_ `public override NamespaceId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L72 _public method_ `public override void Write(Utf8JsonWriter writer, NamespaceId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `Jupiter.Common.NamespaceIdTypeConverter`  
`sealed class NamespaceIdTypeConverter : TypeConverter`  
_internal*; L78-85_
- inherits: `TypeConverter`
- desc: Type converter from strings to NamespaceId objects
- L81 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L84 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/NamespaceNotFoundException.cs` (Jupiter.Common)


#### class `Jupiter.Common.NamespaceNotFoundException`  
`public class NamespaceNotFoundException : Exception`  
_public; L7-20_
- inherits: `Exception`
- L9 _public property_ `public NamespaceId Namespace { get; }`
- L11-14 _public ctor_ `public NamespaceNotFoundException(NamespaceId @namespace) : base($"Could not find namespace {@namespace}")`
- L16-19 _public ctor_ `public NamespaceNotFoundException(NamespaceId @namespace, string message) : base(message)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/PollingService.cs` (Jupiter.Common)


#### class `Jupiter.PollingService`  
`public abstract class PollingService<T> : IHostedService, IAsyncDisposable`  
_public; L13-193_
- inherits: `IHostedService, IAsyncDisposable`
- L25 _private field_ `private readonly ILogger _logger`
- L26 _private field_ `private readonly string _serviceName`
- L27 _private field_ `private readonly TimeSpan _pollFrequency`
- L28 _private field_ `private readonly T _state`
- L29 _private field_ `private readonly bool _startAtRandomTime`
- L30 _private field_ `private readonly CancellationTokenSource _stopPolling = new CancellationTokenSource()`
- L31 _private field_ `private readonly ManualResetEvent _hasFinishedRunning = new ManualResetEvent(true)`
- L32 _private field_ `private volatile bool _alreadyRunning = false`
- L33 _private field_ `private Timer? _timer`
- L34 _private field_ `private bool _disposed = false`
- L36-52 _protected ctor_ `protected PollingService(string serviceName, TimeSpan pollFrequency, T state, ILogger logger, bool startAtRandomTime = false)`
- L54 _public property_ `public bool Running => ...`
- L56 _public property_ `public T State => ...`
- L58-61 _protected method_ `protected virtual bool ShouldStartPolling()`
- L63-80 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)`
- L82-146 _private method_ `private static void OnUpdate(object? state, ILogger logger)`
- L148 _public method_ `public abstract Task<bool> OnPollAsync(T state, CancellationToken cancellationToken)`
- L150-153 _protected method_ `protected virtual Task OnStopping(T state)`
- L155-158 _protected method_ `protected virtual Task OnStartingAsync(T state)`
- L160-175 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)`
- L177-192 _public method_ `public async ValueTask DisposeAsync()`

#### struct `Jupiter.PollingService.ThreadState`  
`private struct ThreadState`  
_private; L15-23_
- L17 _public property_ `public string ServiceName { get; set; }`
- L18 _public property_ `public TimeSpan PollFrequency { get; set; }`
- L20 _public property_ `public CancellationToken StopPollingToken { get; set; }`
- L21 _public property_ `public T ServiceState { get; set; }`
- L22 _public property_ `public PollingService<T> Instance { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/RawOutputFormatter.cs` (Jupiter.Common)


#### class `Jupiter.RawOutputFormatter`  
`public class RawOutputFormatter : OutputFormatter`  
_public; L15-75_
- inherits: `OutputFormatter`
- L17 _private field_ `private readonly ILogger _logger`
- L19-23 _public ctor_ `public RawOutputFormatter(ILogger logger)`
- L25-74 _public method_ `public override async Task WriteResponseBodyAsync(OutputFormatterWriteContext context)`

#### class `Jupiter.RawOutputPropertyAttribute`  
`public sealed class RawOutputPropertyAttribute : Attribute`  
_public; L81-83_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Used to indicate that the field in question is what we want to return as a raw set of bytes

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/RemoteServiceException.cs` (Jupiter.Common)


#### class `Jupiter.Common.RemoteServiceException`  
`public class RemoteServiceException : Exception`  
_public; L7-12_
- inherits: `Exception`
- L9-11 _public ctor_ `public RemoteServiceException(string message, Exception cause) : base(message, cause)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/RequiredContentTypeAttribute.cs` (Jupiter.Common)


#### class `Jupiter.RequiredContentTypeAttribute`  
`public sealed class RequiredContentTypeAttribute : Attribute, IActionConstraint`  
_public; L11-29_
- attrs: `[AttributeUsage(AttributeTargets.Method)]`
- inherits: `Attribute, IActionConstraint`
- L13 _public property_ `public string[] MediaTypeNames { get; }`
- L15-18 _public ctor_ `public RequiredContentTypeAttribute(params string[] mediaTypeNames)`
- L20 _public property_ `public int Order => ...`
- L22-28 _public method_ `public bool Accept(ActionConstraintContext context)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/StringId.cs` (Jupiter.Common)


#### struct `Jupiter.Common.StringId`  
`public readonly struct StringId : IEquatable<StringId>, IEquatable<string>, IEquatable<ReadOnlyMemory<char>>`  
_public; L20-322_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(StringIdJsonConverter))] [TypeConverter(typeof(StringIdTypeConverter))]`
- inherits: `IEquatable<StringId>, IEquatable<string>, IEquatable<ReadOnlyMemory<char>>`
- desc: Normalized string identifier for a resource
- L36 _public const_ `public const int MaxLength = 64` — Maximum length for a string id
- L41 _public property_ `public Utf8String Text { get; }` — The text representing this id
- L46 _public property_ `public ReadOnlySpan<byte> Span => ...` — Accessor for the string bytes
- L51 _public property_ `public ReadOnlyMemory<byte> Memory => ...` — Accessor for the string bytes
- L57-60 _public ctor_ `public StringId(string text) : this(new Utf8String(text))` — Constructor
- L66-74 _public ctor_ `public StringId(Utf8String text)` — Constructor
- L82-85 _public ctor_ `public StringId(Utf8String text, Validate validate)` — attrs: `[SuppressMessage("Style", "IDE0060:Remove unused parameter")]` — Constructor
- L90 _public property_ `public bool IsEmpty => ...` — Checks whether this StringId is set
- L97-135 _public method_ `public static StringId Sanitize(string text)` — Generates a new string id from the given text
- L143 _public method_ `public static bool TryParse(string text, out StringId id)` — Validates the given string as a StringId, normalizing it if necessary.
- L153 _public method_ `public static bool TryParse(string text, out StringId id, [NotNullWhen(false)] out string? errorMessage)` — Validates the given string as a StringId, normalizing it if necessary.
- L162 _public method_ `public static bool TryParse(Utf8String text, out StringId id)` — Validates the given string as a StringId, normalizing it if necessary.
- L172-175 _public method_ `public static bool TryParse(Utf8String text, out StringId id, [NotNullWhen(false)] out string? errorMessage)` — Validates the given string as a StringId, normalizing it if necessary.
- L185-223 _public method_ `public static bool TryParse(Utf8String text, int maxLength, out StringId id, [NotNullWhen(false)] out string? errorMessage)` — Validates the given string as a StringId, normalizing it if necessary.
- L230-243 _private* method_ `static Utf8String ToLower(Utf8String text)` — Converts an utf8 string to lowercase
- L250 _public method_ `public static bool IsValidCharacter(char character)` — Checks whether the given character is valid within a string id
- L257-272 _public method_ `public static bool IsValidCharacter(byte character)` — Checks whether the given character is valid within a string id
- L275 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L278 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L281 _public method_ `public bool Equals(StringId other)` — (inheritdoc)
- L284 _public method_ `public bool Equals(string? other)` — (inheritdoc)
- L287-302 _public method_ `public bool Equals(ReadOnlyMemory<char> other)` — (inheritdoc)
- L305 _public method_ `public override string ToString()` — (inheritdoc)
- L313 _public operator_ `public static bool operator ==(StringId left, StringId right)` — Compares two string ids for equality
- L321 _public operator_ `public static bool operator !=(StringId left, StringId right)` — Compares two string ids for inequality

#### enum `Jupiter.Common.StringId.Validate`  
`public enum Validate`  
_public; L25-31_
- desc: Enum used to disable validation on string arguments
- L30 _public* enumerator_ `None` — No validation required

#### class `Jupiter.Common.StringIdJsonConverter`  
`sealed class StringIdJsonConverter : JsonConverter<StringId>`  
_internal*; L327-334_
- inherits: `JsonConverter<StringId>`
- desc: Class which serializes StringId types
- L330 _public method_ `public override StringId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L333 _public method_ `public override void Write(Utf8JsonWriter writer, StringId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `Jupiter.Common.StringIdTypeConverter`  
`sealed class StringIdTypeConverter : TypeConverter`  
_internal*; L339-352_
- inherits: `TypeConverter`
- desc: Class which serializes StringId types
- L342 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L345 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L348 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L351 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/StringIdConverter.cs` (Jupiter.Common)


#### class `Jupiter.Common.StringIdConverter`  
`public abstract class StringIdConverter<T> where T : struct`  
_public; L18-29_
- constraints: `where T : struct`
- desc: Base class for converting to and from types containing a StringId. Useful pattern for reducing boilerplate with strongly typed records.
- L23 _public method_ `public abstract StringId ToStringId(T value)` — Converts a type to a StringId
- L28 _public method_ `public abstract T FromStringId(StringId id)` — Constructs a type from a StringId

#### class `Jupiter.Common.StringIdConverterAttribute`  
`public sealed class StringIdConverterAttribute : Attribute`  
_public; L35-46_
- attrs: `[AttributeUsage(AttributeTargets.Struct)]`
- inherits: `Attribute`
- desc: Attribute declaring a StringIdConverter{T} for a particular type
- L40 _public property_ `public Type ConverterType { get; }` — The converter type
- L45 _public ctor_ `public StringIdConverterAttribute(Type converterType)` — Constructor

#### class `Jupiter.Common.StringIdCbConverter`  
`public sealed class StringIdCbConverter<TValue, TConverter> : CbConverter<TValue> where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L51-72_
- inherits: `CbConverter<TValue>`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Converter to compact binary objects
- L53 _private* field_ `readonly TConverter _converter = new TConverter()`
- L56-59 _public method_ `public override TValue Read(CbField field)` — (inheritdoc)
- L62-65 _public method_ `public override void Write(CbWriter writer, TValue value)` — (inheritdoc)
- L68-71 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, TValue value)` — (inheritdoc)

#### class `Jupiter.Common.StringIdTypeConverter`  
`public sealed class StringIdTypeConverter<TValue, TConverter> : TypeConverter where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L77-117_
- inherits: `TypeConverter`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Class which serializes types with a StringIdConverter{T} to Json
- L79 _private* field_ `readonly TConverter _converter = new TConverter()`
- L82-85 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L88-99 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L102 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L105-116 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `Jupiter.Common.StringIdJsonConverter`  
`public sealed class StringIdJsonConverter<TValue, TConverter> : JsonConverter<TValue> where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L122-141_
- inherits: `JsonConverter<TValue>`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Class which serializes types with a StringIdConverter{T} to Json
- L124 _private* field_ `readonly TConverter _converter = new TConverter()`
- L127 _public method_ `public override TValue Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L131 _public method_ `public override void Write(Utf8JsonWriter writer, TValue value, JsonSerializerOptions options)` — (inheritdoc)
- L135 _public method_ `public override TValue ReadAsPropertyName(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L139 _public method_ `public override void WriteAsPropertyName(Utf8JsonWriter writer, TValue value, JsonSerializerOptions options)` — (inheritdoc)

#### class `Jupiter.Common.StringIdJsonConverterFactory`  
`public sealed class StringIdJsonConverterFactory : JsonConverterFactory`  
_public; L146-161_
- inherits: `JsonConverterFactory`
- desc: Creates constructors for types with a StringIdConverter{T} to Json
- L149 _public method_ `public override bool CanConvert(Type typeToConvert)` — (inheritdoc)
- L152-160 _public method_ `public override JsonConverter? CreateConverter(Type type, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/SuppressExceptionMiddleware.cs` (Jupiter.Common)


#### class `Jupiter.Common.SuppressExceptionMiddleware`  
`public class SuppressExceptionMiddleware`  
_public; L11-50_
- L13 _private field_ `private readonly ILogger _logger`
- L14 _private field_ `private readonly RequestDelegate _next`
- L16-20 _public ctor_ `public SuppressExceptionMiddleware(RequestDelegate next, ILogger<SuppressExceptionMiddleware> logger)`
- L22-49 _public method_ `public async Task InvokeAsync(HttpContext context)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Utils/ListExtensions.cs` (Jupiter.Common)


#### class `Jupiter.Common.Utils.ListExtensions`  
`public static class ListExtensions`  
_public; L8-24_
- L10-23 _public method_ `public static void Shuffle<T>(this IList<T> list)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Utils/RequestUtil.cs` (Jupiter.Common)


#### class `Jupiter.RequestUtil`  
`public static class RequestUtil`  
_public; L14-49_
- L16 _private field_ `private static Histogram<double>? s_streamThroughputCounter`
- L18-48 _public method_ `public static async Task<byte[]> ReadRawBodyAsync(HttpRequest request)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Utils/Sha1Utils.cs` (Jupiter.Common)


#### class `Jupiter.Sha1Utils`  
`public static class Sha1Utils`  
_public; L10-35_
- L12-15 _public method_ `public static async Task<string> GetSHA1AsStringAsync(byte[] payload)`
- L17-21 _public method_ `public static byte[] GetSHA1(byte[] payload)`
- L23-27 _public method_ `public static byte[] GetSHA1(byte[] payload, int offset, int count)`
- L29-34 _public method_ `public static string GetSHA1AsString(byte[] payload)`

#### class `Jupiter.ByteArrayComparer`  
`public class ByteArrayComparer : EqualityComparer<byte[]>, IComparer<byte[]>`  
_public; L37-102_
- inherits: `EqualityComparer<byte[]>, IComparer<byte[]>`
- L39-64 _public method_ `public override bool Equals(byte[]? a, byte[]? b)`
- L65-74 _public method_ `public override int GetHashCode(byte[] a)`
- L76-101 _public method_ `public int Compare(byte[]? x, byte[]? y)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Utils/StreamUtils.cs` (Jupiter.Common)


#### class `Jupiter.Utils.StreamUtils`  
`public static class StreamUtils`  
_public; L11-27_
- L13-26 _public method_ `public static async Task<byte[]> ToByteArrayAsync(this Stream s, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Utils/StringUtils.cs` (Jupiter.Common)


#### class `Jupiter.StringUtils`  
`public static class StringUtils`  
_public; L8-55_
- L10-13 _public method_ `public static int GetHexVal(char hex)`
- L15-25 _public method_ `public static string FormatAsHexString(byte[] data)`
- L27-37 _public method_ `public static string FormatAsHexLowerString(Span<byte> data)`
- L39-54 _public method_ `public static byte[] ToHashFromHexString(string hex)`

### `Source/Programs/UnrealCloudDDC/Jupiter.Common/Utils/TaskUtils.cs` (Jupiter.Common)


#### class `Jupiter.TaskUtils`  
`public static class TaskUtils`  
_public; L9-29_
- L11-28 _public method_ `public static byte[] CombineIntoSingleBuffer(List<byte[]> tasks)`
