# Runtime / AnalyticsCSV

- module root: `Source/Runtime/Analytics/AnalyticsCSV`
- headers: 2; symbols: 31
- symbol kinds: class=2, function=1, member=8, namespace=2, prototype=17, typedef=1
- PrivateDependencyModuleNames: Analytics
- PublicDependencyModuleNames: Core

### `Source/Runtime/Analytics/AnalyticsCSV/Private/AnalyticsProviderCSV.h` (Private)


#### class `FAnalyticsProviderCSV`  
`class FAnalyticsProviderCSV : public IAnalyticsProvider`  
_L16-53_
- inherits: `IAnalyticsProvider`
- desc: Implementation of the IAnalyticsProvider interface that exports telemetry events to named CSV files By default, the log files are written to Saved/Telemetry folder of the application. FolderPath can be overridden in the configuration For safety, there is MaxEvents number of event files that will be opened
- L20 _public prototype_ `FAnalyticsProviderCSV(const FAnalyticsProviderConfigurationDelegate& GetConfigValue);`
- L21 _public prototype_ `~FAnalyticsProviderCSV();`
- L23 _public prototype_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes = {}) override;`
- L24 _public prototype_ `virtual void EndSession() override;`
- L26 _public prototype_ `virtual void FlushEvents() override;`
- L28 _public prototype_ `virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&& Attributes) override;`
- L29 _public prototype_ `virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const override;`
- L30 _public prototype_ `virtual int32 GetDefaultEventAttributeCount() const override;`
- L31 _public prototype_ `virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int AttributeIndex) const override;`
- L32 _public prototype_ `virtual bool SetSessionID(const FString& InSessionID) override;`
- L33 _public prototype_ `virtual void SetUserID(const FString& InUserID) override;`
- L35 _public prototype_ `virtual FString GetSessionID() const override;`
- L36 _public prototype_ `virtual FString GetUserID() const override;`
- L38 _public prototype_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes = {}) override;`
- L42 _private typedef_ `using TArchives = TMap < FString, TSharedPtr<FArchive>>;`
- L44 _private member_ `FString UserID;`
- L45 _private member_ `FString SessionID;`
- L46 _private member_ `FString FolderPath;`
- L47 _private member_ `TArray<FAnalyticsEventAttribute> DefaultEventAttributes;`
- L48 _private member_ `int32 MaxEvents = 16;`
- L49 _private member_ `TUniquePtr<UE::Tasks::FPipe> WriterPipe;`
- L50 _private member_ `TArchives Archives;`
- L51 _private member_ `bool SessionStarted = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Tasks` (scope `UE`)

### `Source/Runtime/Analytics/AnalyticsCSV/Public/AnalyticsCSV.h` (Public)


#### class `FAnalyticsCSV`  
`class FAnalyticsCSV : public IAnalyticsProviderModule`  
_L21-45_
- inherits: `IAnalyticsProviderModule`
- desc: Public implementation of IAnalyticsProviderModule that returns a FAnalyticsProviderCSV object
- L32 _public function_ `static inline FAnalyticsCSV& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already @return Returns singleton instance, loading the module on demand if needed
- L40 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;` — IAnalyticsProviderModule interface.
- L43 _private prototype_ `virtual void StartupModule() override;`
- L44 _private prototype_ `virtual void ShutdownModule() override;`
