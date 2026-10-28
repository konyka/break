# Plugins / PLUGIN_NAME

- module root: `Plugins/Editor/PluginBrowser/Templates/ThirdPartyLibrary/Source/PLUGIN_NAME`
- headers: 1; symbols: 4
- symbol kinds: class=1, member=1, prototype=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, PLUGIN_NAMELibrary, Projects

### `Plugins/Editor/PluginBrowser/Templates/ThirdPartyLibrary/Source/PLUGIN_NAME/Public/PLUGIN_NAME.h` (Public)


#### class `FPLUGIN_NAMEModule`  
`class FPLUGIN_NAMEModule : public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `void* ExampleLibraryHandle;` — Handle to the test dll we will load
