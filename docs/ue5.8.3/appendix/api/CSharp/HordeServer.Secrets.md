# CSharp / HordeServer.Secrets

- project root: `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets`
- files: 14; symbols: 125
- symbol kinds: class=22, const=2, ctor=8, enum=2, enumerator=4, field=16, interface=1, method=29, property=41
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/ISecretProvider.cs` (HordeServer.Secrets)


#### interface `HordeServer.Secrets.ISecretProvider`  
`public interface ISecretProvider`  
_public; L8-22_
- desc: Interface for a service that can provide secret data
- L13 _public* property_ `string Name { get; }` — Name of this provider
- L21 _public* method_ `Task<string> GetSecretAsync(string path, SecretProviderConfig? config, CancellationToken cancellationToken)` — Gets values for a particular secret

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/Providers/AwsParameterStoreSecretProvider.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.Providers.AwsParameterStoreSecretProvider`  
`public class AwsParameterStoreSecretProvider : ISecretProvider`  
_public; L11-36_
- inherits: `ISecretProvider`
- desc: Fetches secrets from the AWS parameter store
- L14 _public property_ `public string Name => ...` — (inheritdoc)
- L16 _private* field_ `readonly IAmazonSimpleSystemsManagement _systemsManagement`
- L21-24 _public ctor_ `public AwsParameterStoreSecretProvider(IAmazonSimpleSystemsManagement systemsManagement)` — Constructor
- L27-35 _public method_ `public async Task<string> GetSecretAsync(string path, SecretProviderConfig? config, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/Providers/AzureKeyVaultConfig.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.Providers.AzureKeyVaultConfig`  
`public class AzureKeyVaultConfig`  
_public; L8-14_
- desc: Configuration for Azure Key Vault secrets.
- L13 _public property_ `public string? VaultUri { get; set; }` — The Uri to the Azure Key Vault.

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/Providers/AzureKeyVaultSecretProvider.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.Providers.AzureKeyVaultSecretProvider`  
`public class AzureKeyVaultSecretProvider : ISecretProvider`  
_public; L12-33_
- inherits: `ISecretProvider`
- desc: Fetches secrets from Azure Key Vault.
- L15 _public property_ `public string Name => ...` — (inheritdoc)
- L18-32 _public method_ `public async Task<string> GetSecretAsync(string path, SecretProviderConfig? config, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/Providers/HcpVaultConfig.cs` (HordeServer.Secrets)


#### enum `HordeServer.Secrets.Providers.HcpVaultCredentialsType`  
`public enum HcpVaultCredentialsType`  
_public; L8-19_
- desc: Credentials to use to log into HCP Vault.
- L13 _public* enumerator_ `PreSharedKey` — Use a pre-shared token provided by Vault for authentication.
- L18 _public* enumerator_ `AwsAuth` — Use AWS IAM credentials to authenticate against the Vault server.

#### class `HordeServer.Secrets.Providers.HcpVaultConfig`  
`public class HcpVaultConfig`  
_public; L24-66_
- desc: Configuration for HCP Vault secrets.
- L32 _public property_ `public string? PreSharedKey { get; set; }` — The Vault authentication token to use when the type of credentials is HcpVaultCredentialsType.PreSharedKey. More information on this token can be found in the API documentation for https://developer.hashicorp.com/vault/api-docs#authenticationX-Vault-Token
- L37 _public property_ `public string? EndPoint { get; set; }` — The address of the Vault server.
- L44 _public property_ `public string? AwsArnRole { get; set; }` — The optional AWS ARN to assume a role when logging into Vault. To be used when the type of credentials is HcpVaultCredentialsType.AwsAuth. When not set the AWS SDK default credential search will be used.
- L52 _public property_ `public string? AwsIamServerId { get; set; }` — The value for the X-Vault-AWS-IAM-Server-ID header when the Vault server is configured with https://developer.hashicorp.com/vault/api-docs/auth/aws#iam_server_id_header_valueiam_server_id_header_value . Most likely to be the Vault server's DNS name. To be used when the type of credentials is HcpVaultCredentialsType.AwsAuth.
- L60 _public property_ `public string? Role { get; set; }` — The name of the https://developer.hashicorp.com/vault/api-docs/auth/aws#role-4role in the Vault configuration for the login. This role name can be different to the name of the AWS IAM principal. To be used when the type of credentials is HcpVaultCredentialsType.AwsAuth. When not set the name of IAM principal will be used.
- L65 _public property_ `public HcpVaultCredentialsType Credentials { get; set; }` — Type of credentials to use.

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/Providers/HcpVaultSecretProvider.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.Providers.HcpVaultSecretProvider`  
`public class HcpVaultSecretProvider : ISecretProvider`  
_public; L23-245_
- inherits: `ISecretProvider`
- desc: Fetches secrets from a HashiCorp (HCP) Vault.
- L101 _public property_ `public string Name => ...` — (inheritdoc)
- L103 _private field_ `private readonly IHttpClientFactory _httpClientFactory`
- L104 _private field_ `private readonly ILogger _logger`
- L105 _private const_ `private const string HttpClientName = "HordeSecretProviderHcpVault"`
- L106 _private const_ `private const string AwsAssumeRoleSessionName = "HordeSecretProviderVaultSession"`
- L111-115 _public ctor_ `public HcpVaultSecretProvider(IHttpClientFactory httpClientFactory, ILogger<HcpVaultSecretProvider> logger)` — Constructor
- L117-120 _private method_ `private HttpClient GetHttpClient()`
- L122-128 _private method_ `private static async Task<string> GetAwsCallerArnAsync(AWSCredentials credentials, CancellationToken cancellationToken)`
- L130-151 _private method_ `private async Task<ImmutableCredentials> GetAwsCredentialsAsync(string? role, CancellationToken cancellationToken)`
- L153-173 _private method_ `private async Task<string> GetAwsSignedHeadersAsync(string? serverId, string? arnRole, CancellationToken cancellationToken)`
- L175-194 _private method_ `private async Task<string> GetTokenFromAwsAsync(HcpVaultConfig config, CancellationToken cancellationToken)`
- L196-217 _private method_ `private async Task<string> GetSecretAsync(Uri path, string token, CancellationToken cancellationToken)`
- L220-244 _public method_ `public async Task<string> GetSecretAsync(string path, SecretProviderConfig? config, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Secrets.Providers.HcpVaultSecretProvider.AwsAuthRequest`  
`private class AwsAuthRequest`  
_private; L31-66_
- desc: The login parameters to Vault when using AWS for authentication. The parameters for the https://developer.hashicorp.com/vault/api-docs/auth/aws#loginv1/auth/aws/login request.
- L38 _public property_ `public string Method { get; set; }` — attrs: `[JsonPropertyName("iam_http_request_method")]` — The https://developer.hashicorp.com/vault/api-docs/auth/aws#iam_http_request_methodHTTP method used in the signed request.
- L44 _public property_ `public string Body { get; set; }` — attrs: `[JsonPropertyName("iam_request_body")]` — Base64-encoded https://developer.hashicorp.com/vault/api-docs/auth/aws#iam_request_bodybody of the signed request.
- L51 _public property_ `public required string Headers { get; set; }` — attrs: `[JsonPropertyName("iam_request_headers")]` — Based64-encoded key/value pairs of https://developer.hashicorp.com/vault/api-docs/auth/aws#iam_request_headersheaders for the sts:GetCallerIdentity request.
- L58 _public property_ `public string Url { get; set; }` — attrs: `[JsonPropertyName("iam_request_url")]` — Base64-encoded of the https://developer.hashicorp.com/vault/api-docs/auth/aws#iam_request_urlHTTP URL used to sign the request.
- L65 _public property_ `public string Role { get; set; }` — attrs: `[JsonPropertyName("role")]` — Name of the https://developer.hashicorp.com/vault/api-docs/auth/aws#role-4role the login is attempted against. This is not the same as the AWS ARN Role.

#### class `HordeServer.Secrets.Providers.HcpVaultSecretProvider.AuthResponse`  
`private class AuthResponse`  
_private; L71-75_
- desc: The https://developer.hashicorp.com/vault/api-docs/auth/aws#sample-response-12response from the login request.
- L74 _public property_ `public AuthInfo? AuthInfo { get; set; }` — attrs: `[JsonPropertyName("auth")]`

#### class `HordeServer.Secrets.Providers.HcpVaultSecretProvider.AuthInfo`  
`private class AuthInfo`  
_private; L80-87_
- desc: The data from a successful login response.
- L86 _public property_ `public string? Token { get; set; }` — attrs: `[JsonPropertyName("client_token")]` — The token returned from a login request and to be used as the value for the X-Vault-Token header for following API calls.

#### class `HordeServer.Secrets.Providers.HcpVaultSecretProvider.SecretResponse`  
`private class SecretResponse`  
_private; L92-98_
- desc: The response from requesting a secret.
- L97 _public property_ `public Dictionary<string, Dictionary<string, object>> Data { get; set; }` — The key/value paris of all items for a given path to a secret.

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/SecretAclAction.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.SecretAclAction`  
`public static class SecretAclAction`  
_public; L10-16_
- desc: ACL actions for secrets
- L15 _public property_ `public static AclAction ViewSecret { get; }` — View a credential

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/SecretCollection.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.SecretCollection`  
`public class SecretCollection : ISecretCollection`  
_public; L13-45_
- inherits: `ISecretCollection`
- desc: Implementation of ISecretCollection
- L15 _private* field_ `readonly SecretCollectionInternal _secretCollectionInternal`
- L16 _private* field_ `readonly IOptionsSnapshot<SecretsConfig> _secretsConfig`
- L21-25 _public ctor_ `public SecretCollection(SecretCollectionInternal secretCollectionInternal, IOptionsSnapshot<SecretsConfig> secretsConfig)` — Constructor
- L28-31 _public method_ `public async Task<ISecretProperty?> ResolveAsync(string value, CancellationToken cancellationToken)` — (inheritdoc)
- L34-38 _public method_ `public async Task<ISecret?> GetAsync(SecretId secretId, object config, CancellationToken cancellationToken)` — (inheritdoc)
- L41-44 _public method_ `public async Task<ISecret?> GetAsync(SecretId secretId, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Secrets.SecretCollectionInternal`  
`public class SecretCollectionInternal`  
_public; L50-201_
- desc: Core implementation of ISecretCollection which exists as a global service.
- L78 _private* field_ `readonly Dictionary<string, ISecretProvider> _providers`
- L78 _private* field_ `readonly Dictionary< _providers`
- L83-86 _public ctor_ `public SecretCollectionInternal(IEnumerable<ISecretProvider> providers)` — Constructor
- L94-105 _public method_ `public async Task<ISecret?> GetAsync(SecretId secretId, SecretsConfig secretsConfig, CancellationToken cancellationToken)` — Resolve a secret to concrete values
- L113-163 _public method_ `public async Task<ISecret> GetAsync(SecretConfig config, Dictionary<string, SecretProviderConfig>? secretProviderConfigs, CancellationToken cancellationToken)` — Resolve a secret to concrete values
- L171-200 _public method_ `public async Task<ISecretProperty?> ResolveAsync(string value, SecretsConfig secretsConfig, CancellationToken cancellationToken)` — Resolves a string to a property of a secret

#### class `HordeServer.Secrets.SecretCollectionInternal.Secret`  
`class Secret : ISecret`  
_private*; L52-62_
- inherits: `ISecret`
- L54 _public property_ `public SecretId Id { get; }`
- L55 _public property_ `public IReadOnlyDictionary<string, string> Data { get; }`
- L57-61 _public ctor_ `public Secret(SecretId id, IReadOnlyDictionary<string, string> data)`

#### class `HordeServer.Secrets.SecretCollectionInternal.SecretProperty`  
`class SecretProperty : ISecretProperty`  
_private*; L64-76_
- inherits: `ISecretProperty`
- L66 _public property_ `public SecretId Id { get; }`
- L67 _public property_ `public string Name { get; }`
- L68 _public property_ `public string Value { get; }`
- L70-75 _public ctor_ `public SecretProperty(SecretId id, string name, string value)`

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/SecretConfig.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.SecretConfig`  
`public class SecretConfig`  
_public; L15-53_
- desc: Configuration for a secret value
- L20 _public property_ `public SecretId Id { get; set; }` — Identifier for this secret
- L25 _public property_ `public Dictionary<string, string> Data { get; set; }` — Key/value pairs associated with this secret
- L30 _public property_ `public List<ExternalSecretConfig> Sources { get; set; }` — Providers to source key/value pairs from
- L35 _public property_ `public AclConfig Acl { get; set; }` — Defines access to this particular secret
- L41-44 _public method_ `public void PostLoad(AclConfig parentAcl)` — Called after the config has been read
- L51 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — Authorizes a user to perform a given action

#### enum `HordeServer.Secrets.ExternalSecretFormat`  
`public enum ExternalSecretFormat`  
_public; L58-69_
- desc: Format describing how to parse external secret values
- L63 _public* enumerator_ `Text` — Secret is a plain text value which will be stored using the external secret key
- L68 _public* enumerator_ `Json` — Secret is a JSON formatted string containing key/value pairs

#### class `HordeServer.Secrets.ExternalSecretConfig`  
`public class ExternalSecretConfig`  
_public; L74-101_
- desc: Configuration for an external secret provider
- L80 _public property_ `public string ProviderConfig { get; set; }` — The name to look up a secret provider config. A config is mutually exclusive to Provider and to be used when a secret requires additional options than just the name of the provider
- L85 _public property_ `public string Provider { get; set; }` — Name of the provider to use
- L90 _public property_ `public ExternalSecretFormat Format { get; set; }` — Format of the secret
- L95 _public property_ `public string? Key { get; set; }` — Optional key indicating the parameter to set in the resulting data array. Required if Format is ExternalSecretFormat.Text.
- L100 _public property_ `public string Path { get; set; }` — Optional value indicating what to fetch from the provider

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/SecretProviderConfig.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.SecretProviderConfig`  
`public class SecretProviderConfig`  
_public; L10-31_
- desc: Common settings object for different secret providers
- L15 _public property_ `public string Name { get; set; }` — Name of the secret provider config
- L20 _public property_ `public string Provider { get; set; }` — Name of the provider
- L25 _public property_ `public HcpVaultConfig? HcpVault { get; set; }` — Configuration for HCP Vault
- L30 _public property_ `public AzureKeyVaultConfig? AzureKeyVault { get; set; }` — Configuration for Azure Key Vault

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/Secrets/SecretsController.cs` (HordeServer.Secrets)


#### class `HordeServer.Secrets.SecretsController`  
`public class SecretsController : HordeControllerBase`  
_public; L17-98_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/secrets endpoint
- L19 _private* field_ `readonly ISecretCollection _secretCollection`
- L20 _private* field_ `readonly IOptionsSnapshot<SecretsConfig> _secretsConfig`
- L25-29 _public ctor_ `public SecretsController(ISecretCollection secretCollection, IOptionsSnapshot<SecretsConfig> secretsConfig)` — Constructor
- L36-47 _public method_ `public ActionResult<GetSecretsResponse> GetSecrets()` — attrs: `[HttpGet] [Route("/api/v1/secrets")]` — Query all the secrets available for the current user
- L59-72 _public method_ `public async Task<ActionResult<object>> GetSecretAsync(SecretId secretId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/secrets/{secretId}")] [ProducesResponseType(typeof(GetSecretResponse), 200)]` — Retrieve information about a specific secret
- L84-97 _public method_ `public async Task<ActionResult<object>> ResolveSecretAsync(string value, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/secrets/resolve/{value}")] [ProducesResponseType(typeof(GetSecretPropertyResponse), 200)]` — Converts the string representation of a secret and property to a concrete value The format of the string is 'horde:secret:secret-id.property-name'

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/SecretsConfig.cs` (HordeServer.Secrets)


#### class `HordeServer.SecretsConfig`  
`public class SecretsConfig : IPluginConfig`  
_public; L17-91_
- inherits: `IPluginConfig`
- desc: Configuration for the secrets system
- L22 _public property_ `public List<SecretConfig> Secrets { get; set; }` — List of secrets
- L24 _private field_ `private readonly Dictionary<SecretId, SecretConfig> _secretLookup = ...`
- L24 _private field_ `private readonly Dictionary< _secretLookup = new Dictionary<SecretId, SecretConfig>()`
- L29 _public property_ `public List<SecretProviderConfig> ProviderConfigs { get; set; }` — List of configurations for secret providers
- L31 _private field_ `private readonly Dictionary<SecretId, Dictionary<string, SecretProviderConfig>> _providerConfigLookup = ...`
- L31 _private field_ `private readonly Dictionary< string`
- L31 _private field_ `private readonly Dictionary< _providerConfigLookup = new()`
- L34-66 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)
- L74 _public method_ `public bool TryGetSecret(SecretId secretId, [NotNullWhen(true)] out SecretConfig? config)` — Attempts to get a secret configuration from this object
- L83 _public method_ `public bool TryGetSecretProviderConfigs(SecretId secretId, [NotNullWhen(true)] out Dictionary<string, SecretProviderConfig>? config)` — Attempts to get a secret provider configuration from this object
- L89 _public method_ `public bool Authorize(SecretId secretId, AclAction action, ClaimsPrincipal user)` — Authorize access to a secret

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/SecretsPlugin.cs` (HordeServer.Secrets)


#### class `HordeServer.SecretsPlugin`  
`public class SecretsPlugin : IPluginStartup`  
_public; L18-53_
- attrs: `[Plugin("Secrets", GlobalConfigType = typeof(SecretsConfig), ServerConfigType = typeof(SecretsServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the secrets plugin
- L20 _private field_ `private readonly IServerInfo _serverInfo`
- L21 _private field_ `private readonly SecretsServerConfig _staticConfig`
- L26-30 _public ctor_ `public SecretsPlugin(IServerInfo serverInfo, SecretsServerConfig staticConfig)` — Constructor
- L33-34 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L37-52 _public method_ `public void ConfigureServices(IServiceCollection services)` — (inheritdoc)

#### class `HordeServer.SecretsPluginExtensions`  
`public static class SecretsPluginExtensions`  
_public; L58-71_
- desc: Helper methods for secrets config
- L63 _public method_ `public static void AddSecretsConfig(this IDictionary<PluginName, IPluginConfig> dictionary, SecretsConfig secretsConfig)` — Configures the secrets plugin
- L69 _public method_ `public static SecretsConfig GetSecretsConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the secrets plugin

### `Source/Programs/Horde/Plugins/Secrets/HordeServer.Secrets/SecretsServerConfig.cs` (HordeServer.Secrets)


#### class `HordeServer.SecretsServerConfig`  
`public class SecretsServerConfig : PluginServerConfig`  
_public; L10-16_
- inherits: `PluginServerConfig`
- desc: Static configuration for the secrets plugin
- L15 _public property_ `public bool WithAws { get; set; }` — Whether to enable Amazon Web Services (AWS) specific features
