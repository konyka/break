# CSharp / HordeServer.ExamplePlugin

- project root: `Source/Programs/Horde/Plugins/ExamplePlugin/HordeServer.ExamplePlugin`
- files: 4; symbols: 16
- symbol kinds: class=5, ctor=2, field=2, method=6, property=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/ExamplePlugin/HordeServer.ExamplePlugin/ExamplePlugin.cs` (HordeServer.ExamplePlugin)


#### class `HordeServer.ExamplePlugin`  
`public class ExamplePlugin : IPluginStartup`  
_public; L13-32_
- attrs: `[Plugin("ExamplePlugin", EnabledByDefault = false, GlobalConfigType = typeof(ExamplePluginConfig), ServerConfigType = typeof(ExamplePluginServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the ExamplePlugin
- L18-20 _public ctor_ `public ExamplePlugin()` — Constructor
- L23-25 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L28-31 _public method_ `public void ConfigureServices(IServiceCollection serviceCollection)` — (inheritdoc)

#### class `HordeServer.ExamplePluginExtensions`  
`public static class ExamplePluginExtensions`  
_public; L37-50_
- desc: Helper methods for ExamplePlugin plugin config
- L42 _public method_ `public static void AddExamplePluginConfig(this IDictionary<PluginName, IPluginConfig> dictionary, ExamplePluginConfig examplePluginConfig)` — Configures the ExamplePlugin plugin
- L48 _public method_ `public static ExamplePluginConfig GetExamplePluginConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the ExamplePlugin plugin

### `Source/Programs/Horde/Plugins/ExamplePlugin/HordeServer.ExamplePlugin/ExamplePluginConfig.cs` (HordeServer.ExamplePlugin)


#### class `HordeServer.ExamplePluginConfig`  
`public class ExamplePluginConfig : IPluginConfig`  
_public; L10-21_
- inherits: `IPluginConfig`
- desc: Configuration for the ExamplePlugin plugin
- L15 _public property_ `public string GreetingMessage { get; set; }` — The Greeting provided by the example plugin
- L18-20 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/ExamplePlugin/HordeServer.ExamplePlugin/ExamplePluginController.cs` (HordeServer.ExamplePlugin)


#### class `HordeServer.ExamplePluginController`  
`public class ExamplePluginController : HordeControllerBase`  
_public; L17-42_
- attrs: `[Authorize] [ApiController]`
- inherits: `HordeControllerBase`
- L19 _private* field_ `readonly IOptionsSnapshot<ExamplePluginConfig> _examplePluginConfig`
- L20 _private* field_ `readonly ILogger _logger`
- L25-29 _public ctor_ `public ExamplePluginController(IOptionsSnapshot<ExamplePluginConfig> examplePluginConfig, ILogger<ExamplePluginController> logger)` — Constructor
- L36-41 _public method_ `public ActionResult GetGreeting()` — attrs: `[HttpGet] [Route("/api/v1/exampleplugin/greeting")]` — Example plugin endpoint which returns message provided in

### `Source/Programs/Horde/Plugins/ExamplePlugin/HordeServer.ExamplePlugin/ExamplePluginServerConfig.cs` (HordeServer.ExamplePlugin)


#### class `HordeServer.ExamplePluginServerConfig`  
`public class ExamplePluginServerConfig : PluginServerConfig`  
_public; L10-12_
- inherits: `PluginServerConfig`
- desc: Server configuration for the ExamplePlugin
