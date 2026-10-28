# Plugins / IOSAdjust

- module root: `Plugins/Runtime/Analytics/Adjust/Source/IOSAdjust`
- headers: 2; symbols: 33
- symbol kinds: class=2, function=3, member=6, prototype=22
- PrivateDependencyModuleNames: Analytics
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: Analytics

### `Plugins/Runtime/Analytics/Adjust/Source/IOSAdjust/Private/IOSAdjustProvider.h` (Private)


#### class `FAnalyticsProviderAdjust`  
`class FAnalyticsProviderAdjust : public IAnalyticsProvider`  
_L7-64_
- inherits: `IAnalyticsProvider`
- L11 _private member_ `FString AppToken;` — The AppToken given to you by Adjust dashboard
- L13 _private member_ `bool bHasSessionStarted;` — Tracks whether we need to start the session or restart it
- L15 _private member_ `FString UserId;` — Cached user id
- L17 _private member_ `TMap<FString, FString> EventMap;` — Event name to token mapping
- L20 _private member_ `static TSharedPtr<IAnalyticsProvider> Provider;` — Singleton for analytics
- L21 _private prototype_ `FAnalyticsProviderAdjust(const FString InAppToken, bool bInSandbox, const FString InLogLevel, const FString InDefaultTracker, bool bInEventBuffering, bool bSendInBackground, float InDelayStart);`
- L24 _public function_ `static TSharedPtr<IAnalyticsProvider> Create(const FString InAppToken, bool bInSandbox, const FString InLogLevel, const FString InDefaultTracker, bool bInEventBuffering, bool bSendInBackground, float InDelayStart)`
- L32 _public function_ `static void Destroy()`
- L37 _public prototype_ `virtual ~FAnalyticsProviderAdjust();`
- L39 _public prototype_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override;`
- L40 _public prototype_ `virtual void EndSession() override;`
- L41 _public prototype_ `virtual void FlushEvents() override;`
- L43 _public prototype_ `virtual void SetUserID(const FString& InUserID) override;`
- L44 _public prototype_ `virtual FString GetUserID() const override;`
- L46 _public prototype_ `virtual FString GetSessionID() const override;`
- L47 _public prototype_ `virtual bool SetSessionID(const FString& InSessionID) override;`
- L49 _public prototype_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;`
- L50 _public prototype_ `virtual void RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) override;`
- L51 _public prototype_ `virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) override;`
- L52 _public prototype_ `virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount) override;`
- L54 _public prototype_ `virtual void RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;`
- L55 _public prototype_ `virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;`
- L57 _public prototype_ `virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&& Attributes) override;`
- L58 _public prototype_ `virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const override;`
- L59 _public prototype_ `virtual int32 GetDefaultEventAttributeCount() const override;`
- L60 _public prototype_ `virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int AttributeIndex) const override;`
- L63 _private member_ `TArray<FAnalyticsEventAttribute> DefaultEventAttributes;`

### `Plugins/Runtime/Analytics/Adjust/Source/IOSAdjust/Public/IOSAdjust.h` (Public)


#### class `FAnalyticsIOSAdjust`  
`class FAnalyticsIOSAdjust : public IAnalyticsProviderModule`  
_L13-45_
- inherits: `IAnalyticsProviderModule`
- desc: The public interface to this module
- L26 _public function_ `static inline FAnalyticsIOSAdjust& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L40 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;` — IAnalyticsProviderModule interface. Creates the analytics provider given a configuration delegate. The keys required exactly match the field names in the Config object.
- L43 _private prototype_ `virtual void StartupModule() override;`
- L44 _private prototype_ `virtual void ShutdownModule() override;`
