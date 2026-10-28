# Plugins / AnalyticsMulticast

- module root: `Plugins/Runtime/Analytics/AnalyticsMulticast/Source/AnalyticsMulticast`
- headers: 1; symbols: 9
- symbol kinds: class=1, function=2, member=1, prototype=4, struct=1
- PrivateDependencyModuleNames: Analytics, DeveloperSettings
- PublicDependencyModuleNames: Core, CoreUObject, Engine
- PublicIncludePathModuleNames: Analytics

### `Plugins/Runtime/Analytics/AnalyticsMulticast/Source/AnalyticsMulticast/Public/AnalyticsMulticast.h` (Public)


#### class `FAnalyticsMulticast`  
`class FAnalyticsMulticast : public IAnalyticsProviderModule`  
_L16-76_
- inherits: `IAnalyticsProviderModule`
- desc: Exposes a multicast provider that multicasts analytics events to multiple providers. Configured using a comma separated list of provider modules. Each module then uses The supplied configuration delegate to configure itself.
- L28 _public function_ `static inline FAnalyticsMulticast& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L65 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const;` — IAnalyticsProviderModule interface. Creates the analytics provider given a configuration delegate. The keys required exactly match the field names in the Config object. When a particular provider module is loaded, it will create an instance and use the provided Configuration delegate to configure each provider.
- L71 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const Config& ConfigValues, const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const;` — Construct an analytics provider directly from a config object (and a delegate to provide configuration to each configured provider).
- L74 _private prototype_ `virtual void StartupModule() override;`
- L75 _private prototype_ `virtual void ShutdownModule() override;`

#### struct `FAnalyticsMulticast::Config`  
`struct Config`  
_L44-51_
- desc: Defines required configuration values for multicast analytics provider. Basically, you provide a list of provider modules that define the providers you want to multicast events to. Beyond that, each provider module created will use the provided configuration delegate to configure itself, so that configuration delegate must be able to configure each specific provider as well (see CreateAnalyticsProvider function below).
- L47 _public member_ `FString ProviderModuleNames;` — Comma separated list of analytics provider modules
- L50 _public function_ `static FString GetKeyNameForProviderModuleNames()` — KeyName required for APIKey configuration.
