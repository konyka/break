# CSharp / HordeServer.Symbols

- project root: `Source/Programs/Horde/Plugins/Symbols/HordeServer.Symbols`
- files: 6; symbols: 22
- symbol kinds: class=5, ctor=1, field=4, method=6, property=6
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Symbols/HordeServer.Symbols/Properties/AssemblyInfo.cs` (HordeServer.Symbols)
_(no declarations)_


### `Source/Programs/Horde/Plugins/Symbols/HordeServer.Symbols/Symbols/SymbolStoreAclAction.cs` (HordeServer.Symbols)


#### class `HordeServer.Symbols.SymbolStoreAclAction`  
`public static class SymbolStoreAclAction`  
_public; L10-16_
- desc: ACL actions which apply to symbols
- L15 _public property_ `public static AclAction ReadSymbols { get; }` — Ability to download symbols

### `Source/Programs/Horde/Plugins/Symbols/HordeServer.Symbols/Symbols/SymbolStoreConfig.cs` (HordeServer.Symbols)


#### class `HordeServer.Symbols.SymbolStoreConfig`  
`public class SymbolStoreConfig`  
_public; L14-54_
- desc: Configuration for a symbol store
- L19 _public property_ `public SymbolStoreId Id { get; set; }` — Identifier for this store
- L24 _public property_ `public NamespaceId NamespaceId { get; set; }` — Configuration for the symbol store backend
- L29 _public property_ `public bool Public { get; set; }` — Whether to make this store available without auth
- L34 _public property_ `public AclConfig Acl { get; set; }` — Access to the symbol store
- L39-53 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — Authorize a user to perform the given action

### `Source/Programs/Horde/Plugins/Symbols/HordeServer.Symbols/Symbols/SymbolsController.cs` (HordeServer.Symbols)


#### class `HordeServer.Tools.SymbolsController`  
`public class SymbolsController : HordeControllerBase`  
_public; L20-71_
- attrs: `[ApiController] [TryAuthorize]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/symbols endpoint
- L22 _private* field_ `readonly StorageService _storageService`
- L23 _private* field_ `readonly IOptionsSnapshot<SymbolsConfig> _symbolsConfig`
- L28-32 _public ctor_ `public SymbolsController(StorageService storageService, IOptionsSnapshot<SymbolsConfig> symbolsConfig)` — Constructor
- L42-70 _public method_ `public async Task<ActionResult> ReadFileAsync(SymbolStoreId storeId, string path, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/symbols/{storeId}/{*path}")]` — Reads a file from the symbol store.

### `Source/Programs/Horde/Plugins/Symbols/HordeServer.Symbols/SymbolsConfig.cs` (HordeServer.Symbols)


#### class `HordeServer.Symbols.SymbolsConfig`  
`public class SymbolsConfig : IPluginConfig`  
_public; L15-44_
- inherits: `IPluginConfig`
- desc: Configuration for the tools system
- L20 _public property_ `public List<SymbolStoreConfig> Stores { get; set; }` — List of symbol stores
- L22 _private* field_ `readonly Dictionary<SymbolStoreId, SymbolStoreConfig> _storeLookup = ...`
- L22 _private* field_ `readonly Dictionary< _storeLookup = new Dictionary<SymbolStoreId, SymbolStoreConfig>()`
- L25-37 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)
- L42 _public method_ `public bool TryGetStore(SymbolStoreId storeId, [NotNullWhen(true)] out SymbolStoreConfig? store)` — Finds a store by id

### `Source/Programs/Horde/Plugins/Symbols/HordeServer.Symbols/SymbolsPlugin.cs` (HordeServer.Symbols)


#### class `HordeServer.SymbolsPlugin`  
`public class SymbolsPlugin : IPluginStartup`  
_public; L14-23_
- attrs: `[Plugin("Symbols", GlobalConfigType = typeof(SymbolsConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the symbols plugin
- L17-18 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L21-22 _public method_ `public void ConfigureServices(IServiceCollection services)` — (inheritdoc)
