# Runtime / AnalyticsHorde

- module root: `Source/Runtime/Analytics/AnalyticsHorde`
- headers: 1; symbols: 5
- symbol kinds: class=1, function=1, prototype=3
- PrivateDependencyModuleNames: Analytics, AnalyticsET, Core

### `Source/Runtime/Analytics/AnalyticsHorde/Public/AnalyticsHorde.h` (Public)


#### class `FAnalyticsHorde`  
`class FAnalyticsHorde : public IAnalyticsProviderModule`  
_L14-50_
- inherits: `IAnalyticsProviderModule`
- desc: Public implementation of IAnalyticsProviderModule
- L26 _public function_ `static inline FAnalyticsHorde& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L45 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;` — IAnalyticsProviderModule interface. Creates the analytics provider given a configuration delegate. The keys required exactly match the field names in the Config object.
- L48 _private prototype_ `virtual void StartupModule() override;`
- L49 _private prototype_ `virtual void ShutdownModule() override;`
