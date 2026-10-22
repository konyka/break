# Plugins / AnalyticsBlueprintLibrary

- module root: `Plugins/Runtime/Analytics/AnalyticsBlueprintLibrary/Source/AnalyticsBlueprintLibrary`
- headers: 2; symbols: 37
- symbol kinds: class=2, function=1, member=2, prototype=31, struct=1
- PrivateDependencyModuleNames: Analytics
- PublicDependencyModuleNames: Core, CoreUObject, Engine
- PublicIncludePathModuleNames: Analytics

### `Plugins/Runtime/Analytics/AnalyticsBlueprintLibrary/Source/AnalyticsBlueprintLibrary/Classes/AnalyticsBlueprintLibrary.h` (Public)


#### struct `FAnalyticsEventAttr`  
`struct FAnalyticsEventAttr`  
_L12-21_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint accessible version of the analytics event struct
- L17 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Analytics")`
- L20 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Analytics")`

#### class `UAnalyticsBlueprintLibrary`  
`class UAnalyticsBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L24-144_
- reflection: `UCLASS(meta=(ScriptName="AnalyticsLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L31 _private prototype_ `static bool StartSession();` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Starts an analytics session without any custom attributes specified
- L35 _private prototype_ `static bool StartSessionWithAttributes(const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Starts an analytics session with custom attributes specified
- L39 _private prototype_ `static void EndSession();` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Ends an analytics session
- L43 _private prototype_ `static void FlushEvents();` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Requests that any cached events be sent immediately
- L47 _private prototype_ `static void RecordEvent(const FString& EventName);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an event has happened by name without any attributes (an event counter)
- L51 _private prototype_ `static void RecordEventWithAttribute(const FString& EventName, const FString& AttributeName, const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an event has happened by name with a single attribute
- L55 _private prototype_ `static void RecordEventWithAttributes(const FString& EventName, const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an event has happened by name with a single attribute
- L59 _private prototype_ `static void RecordItemPurchase(const FString& ItemId, const FString& Currency, int32 PerItemCost, int32 ItemQuantity);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game item was purchased using the specified in-game currency
- L63 _private prototype_ `static void RecordSimpleItemPurchase(const FString& ItemId, int32 ItemQuantity);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game item was purchased
- L67 _private prototype_ `static void RecordSimpleItemPurchaseWithAttributes(const FString& ItemId, int32 ItemQuantity, const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game item was purchased with attributes
- L71 _private prototype_ `static void RecordSimpleCurrencyPurchase(const FString& GameCurrencyType, int32 GameCurrencyAmount);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game currency was purchased using real-world money
- L75 _private prototype_ `static void RecordSimpleCurrencyPurchaseWithAttributes(const FString& GameCurrencyType, int32 GameCurrencyAmount, const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game currency was purchased using real-world money
- L79 _private prototype_ `static void RecordCurrencyPurchase(const FString& GameCurrencyType, int32 GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game currency was purchased using real-world money
- L83 _private prototype_ `static void RecordCurrencyGiven(const FString& GameCurrencyType, int32 GameCurrencyAmount);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game currency was granted by the game with no real-world money being involved
- L87 _private prototype_ `static void RecordCurrencyGivenWithAttributes(const FString& GameCurrencyType, int32 GameCurrencyAmount, const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an in-game currency was granted by the game with no real-world money being involved
- L91 _private prototype_ `static FAnalyticsEventAttr MakeEventAttribute(const FString& AttributeName, const FString& AttributeValue);` — `UFUNCTION(BlueprintPure, Category="Analytics")` — Builds a struct from the attribute name and value
- L95 _private prototype_ `static FString GetSessionId();` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Gets the current session id from the analytics provider
- L99 _private prototype_ `static void SetSessionId(const FString& SessionId);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Sets the session id (if supported) on the analytics provider
- L103 _private prototype_ `static FString GetUserId();` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Gets the current user id from the analytics provider
- L107 _private prototype_ `static void SetUserId(const FString& UserId);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Sets the user id (if supported) on the analytics provider
- L111 _private prototype_ `static void SetAge(int32 Age);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Sets the user's age (if supported) on the analytics provider
- L115 _private prototype_ `static void SetLocation(const FString& Location);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Sets the user's location (if supported) on the analytics provider
- L119 _private prototype_ `static void SetGender(const FString& Gender);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Sets the user's gender (if supported) on the analytics provider
- L123 _private prototype_ `static void SetBuildInfo(const FString& BuildInfo);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Sets the game's build info (if supported) on the analytics provider
- L127 _private prototype_ `static void RecordErrorWithAttributes(const FString& Error, const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an error event has happened with attributes
- L131 _private prototype_ `static void RecordError(const FString& Error);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records an error event has happened
- L135 _private prototype_ `static void RecordProgressWithFullHierarchyAndAttributes(const FString& ProgressType, const TArray<FString>& ProgressNames, const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records a user progress event has happened with a full list of progress hierarchy names and with attributes
- L139 _private prototype_ `static void RecordProgressWithAttributes(const FString& ProgressType, const FString& ProgressName, const TArray<FAnalyticsEventAttr>& Attributes);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records a user progress event has happened with attributes
- L143 _private prototype_ `static void RecordProgress(const FString& ProgressType, const FString& ProgressName);` — `UFUNCTION(BlueprintCallable, Category="Analytics")` — Records a user progress event has happened

### `Plugins/Runtime/Analytics/AnalyticsBlueprintLibrary/Source/AnalyticsBlueprintLibrary/Public/AnalyticsBlueprintLibraryModule.h` (Public)


#### class `FAnalyticsBlueprintLibraryModule`  
`class FAnalyticsBlueprintLibraryModule : public IModuleInterface`  
_L10-31_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline FAnalyticsBlueprintLibraryModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _private prototype_ `virtual void StartupModule() override;`
- L30 _private prototype_ `virtual void ShutdownModule() override;`
