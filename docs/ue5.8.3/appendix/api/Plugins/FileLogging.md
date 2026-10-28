# Plugins / FileLogging

- module root: `Plugins/Runtime/Analytics/FileLogging/Source/FileLogging`
- headers: 2; symbols: 44
- symbol kinds: class=2, function=1, member=12, prototype=29
- PrivateDependencyModuleNames: Analytics
- PublicDependencyModuleNames: Core, CoreUObject, Engine
- PublicIncludePathModuleNames: Analytics

### `Plugins/Runtime/Analytics/FileLogging/Source/FileLogging/Private/FileLoggingProvider.h` (Private)


#### class `FAnalyticsProviderFileLogging`  
`class FAnalyticsProviderFileLogging : public IAnalyticsProvider`  
_L11-75_
- inherits: `IAnalyticsProvider`
- L15 _private member_ `FString AnalyticsFilePath;` — Path where analytics files are saved out
- L17 _private member_ `bool bHasSessionStarted;` — Tracks whether we need to start the session or restart it
- L19 _private member_ `bool bHasWrittenFirstEvent;` — Whether an event was written before or not
- L21 _private member_ `FString UserId;` — Id representing the user the analytics are recording for
- L23 _private member_ `FString SessionId;` — Unique Id representing the session the analytics are recording for
- L25 _private member_ `int32 Age;` — Holds the Age if set
- L27 _private member_ `FString Location;` — Holds the Location of the user if set
- L29 _private member_ `FString Gender;` — Holds the Gender of the user if set
- L31 _private member_ `FString BuildInfo;` — Holds the build info if set
- L33 _private member_ `FArchive* FileArchive;` — The file archive used to write the data
- L36 _public prototype_ `FAnalyticsProviderFileLogging();`
- L37 _public prototype_ `virtual ~FAnalyticsProviderFileLogging();`
- L39 _public prototype_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override;`
- L40 _public prototype_ `virtual void EndSession() override;`
- L41 _public prototype_ `virtual void FlushEvents() override;`
- L43 _public prototype_ `virtual void SetUserID(const FString& InUserID) override;`
- L44 _public prototype_ `virtual FString GetUserID() const override;`
- L46 _public prototype_ `virtual FString GetSessionID() const override;`
- L47 _public prototype_ `virtual bool SetSessionID(const FString& InSessionID) override;`
- L49 _public prototype_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;`
- L51 _public prototype_ `virtual void RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) override;`
- L53 _public prototype_ `virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) override;`
- L55 _public prototype_ `virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount) override;`
- L57 _public prototype_ `virtual void SetBuildInfo(const FString& InBuildInfo) override;`
- L58 _public prototype_ `virtual void SetGender(const FString& InGender) override;`
- L59 _public prototype_ `virtual void SetLocation(const FString& InLocation) override;`
- L60 _public prototype_ `virtual void SetAge(const int32 InAge) override;`
- L62 _public prototype_ `virtual void RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;`
- L63 _public prototype_ `virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;`
- L64 _public prototype_ `virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;`
- L65 _public prototype_ `virtual void RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;`
- L66 _public prototype_ `virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;`
- L68 _public prototype_ `virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&& Attributes) override;`
- L69 _public prototype_ `virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const override;`
- L70 _public prototype_ `virtual int32 GetDefaultEventAttributeCount() const override;`
- L71 _public prototype_ `virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int AttributeIndex) const override;`
- L74 _private member_ `TArray<FAnalyticsEventAttribute> DefaultEventAttributes;`

### `Plugins/Runtime/Analytics/FileLogging/Source/FileLogging/Public/FileLogging.h` (Public)


#### class `FAnalyticsFileLogging`  
`class FAnalyticsFileLogging : public IAnalyticsProviderModule`  
_L14-49_
- inherits: `IAnalyticsProviderModule`
- desc: The public interface to this module
- L18 _private member_ `TSharedPtr<IAnalyticsProvider> FileLoggingProvider;` — Singleton for analytics
- L30 _public function_ `static inline FAnalyticsFileLogging& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L44 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;` — IAnalyticsProviderModule interface. Creates the analytics provider given a configuration delegate. The keys required exactly match the field names in the Config object.
- L47 _private prototype_ `virtual void StartupModule() override;`
- L48 _private prototype_ `virtual void ShutdownModule() override;`
