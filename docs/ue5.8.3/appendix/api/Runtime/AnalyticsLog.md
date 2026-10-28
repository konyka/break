# Runtime / AnalyticsLog

- module root: `Source/Runtime/Analytics/AnalyticsLog`
- headers: 2; symbols: 27
- symbol kinds: class=2, function=1, member=5, namespace=2, prototype=17
- PrivateDependencyModuleNames: Analytics
- PublicDependencyModuleNames: Core

### `Source/Runtime/Analytics/AnalyticsLog/Private/AnalyticsProviderLog.h` (Private)


#### class `FAnalyticsProviderLog`  
`class FAnalyticsProviderLog : public IAnalyticsProvider`  
_L16-47_
- inherits: `IAnalyticsProvider`
- desc: Implementation of the IAnalyticsProvider interface that exports telemetry events to a file as Newline - delimited JSON By default,the log file is written to Saved/Telemetry folder of the application. FileName and FolderPath can be overridden in the configuration Here as a simple example of how a developer might implement and configure their own analytics provider for use with the StudioTelemerty plugin
- L20 _public prototype_ `FAnalyticsProviderLog(const FAnalyticsProviderConfigurationDelegate& GetConfigValue);`
- L21 _public prototype_ `~FAnalyticsProviderLog();`
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
- L42 _private member_ `FString UserID;`
- L43 _private member_ `FString SessionID;`
- L44 _private member_ `TArray<FAnalyticsEventAttribute> DefaultEventAttributes;`
- L45 _private member_ `TUniquePtr<FArchive> FileWriter;`
- L46 _private member_ `TUniquePtr<UE::Tasks::FPipe> WriterPipe;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Tasks` (scope `UE`)

### `Source/Runtime/Analytics/AnalyticsLog/Public/AnalyticsLog.h` (Public)


#### class `FAnalyticsLog`  
`class FAnalyticsLog : public IAnalyticsProviderModule`  
_L21-45_
- inherits: `IAnalyticsProviderModule`
- desc: Public implementation of IAnalyticsProviderModule that returns a JSON formatted FAnalayticsProviderLog object
- L32 _public function_ `static inline FAnalyticsLog& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already @return Returns singleton instance, loading the module on demand if needed
- L40 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;` — IAnalyticsProviderModule interface.
- L43 _private prototype_ `virtual void StartupModule() override;`
- L44 _private prototype_ `virtual void ShutdownModule() override;`
