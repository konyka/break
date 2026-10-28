# Runtime / AnalyticsSwrve

- module root: `Source/Runtime/Analytics/AnalyticsSwrve`
- headers: 1; symbols: 15
- symbol kinds: class=1, function=6, member=3, prototype=4, struct=1
- PrivateDependencyModuleNames: Analytics, HTTP, Json
- PublicDependencyModuleNames: Core

### `Source/Runtime/Analytics/AnalyticsSwrve/Public/AnalyticsSwrve.h` (Public)


#### class `FAnalyticsSwrve`  
`class FAnalyticsSwrve : public IAnalyticsProviderModule`  
_L18-80_
- inherits: `IAnalyticsProviderModule`
- desc: The public interface to this module
- L30 _public function_ `static inline FAnalyticsSwrve& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L70 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const;` — IAnalyticsProviderModule interface. Creates the analytics provider given a configuration delegate. The keys required exactly match the field names in the Config object.
- L75 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const Config& ConfigValues) const;` — Construct an analytics provider directly from a config object.
- L78 _private prototype_ `virtual void StartupModule() override;`
- L79 _private prototype_ `virtual void ShutdownModule() override;`

#### struct `FAnalyticsSwrve::Config`  
`struct Config`  
_L40-59_
- desc: Defines required configuration values for Swrve analytics provider.
- L43 _public member_ `FString APIKeySwrve;` — Swrve API Key - Get from your account manager
- L45 _public member_ `FString APIServerSwrve;` — Swrve API Server - Defaults if empty to GetDefaultAPIServer. FAnalytics::Debug build types default to GetDefaultAPIServerDebug.
- L47 _public member_ `FString AppVersionSwrve;` — AppVersion - defines the app version passed to the provider. By default this will be FEngineVersion::Current().GetChangelist(). If you provide your own, ".<FEngineVersion::Current().GetChangelist()>" is appended to it.
- L50 _public function_ `static FString GetKeyNameForAPIKey()` — KeyName required for APIKey configuration.
- L52 _public function_ `static FString GetKeyNameForAPIServer()` — KeyName required for APIServer configuration.
- L54 _public function_ `static FString GetKeyNameForAppVersion()` — KeyName required for AppVersion configuration.
- L56 _public function_ `static FString GetDefaultAPIServer()` — Default value if no APIServer configuration is provided.
- L58 _public function_ `static FString GetDefaultAPIServerDebug()` — Default value if BuildType == Debug if no APIServer configuration is provided.
