# Plugins / ModelContextProtocolTests

- module root: `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolTests`
- headers: 4; symbols: 74
- symbol kinds: class=1, function=45, member=22, namespace=3, struct=3
- PrivateDependencyModuleNames: Analytics, AnalyticsET, CoreUObject, HTTP, HTTPServer, Json, JsonUtilities, ModelContextProtocol, ModelContextProtocolEngine
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolTests/Private/Mocks/MockAnalyticsProviderET.h` (Private)


#### class `FMockAnalyticsProviderET`  
`class FMockAnalyticsProviderET : public IAnalyticsProviderET`  
_L13-75_
- inherits: `IAnalyticsProviderET`
- desc: Minimal IAnalyticsProviderET mock that captures recorded events. Only RecordEvent is meaningful; all other interface methods are stubbed.
- L22 _public member_ `TArray<FRecordedEvent> RecordedEvents;`
- L24 _public function_ `const FAnalyticsEventAttribute* FindAttribute(const FRecordedEvent& Event, const FString& AttributeName) const`
- L33 _public function_ `virtual void SetAppID(FString&&) override`
- L34 _public function_ `virtual void SetAppVersion(FString&&) override`
- L35 _public function_ `virtual bool StartSession(FString, const TArray<FAnalyticsEventAttribute>&) override`
- L36 _public function_ `virtual bool ShouldRecordEvent(const FString&) const override`
- L38 _public function_ `virtual void RecordEvent(FString&& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override`
- L43 _public function_ `virtual void RecordEvent(FString&& EventName, const TArray<FAnalyticsEventAttribute>& Attributes, EAnalyticsRecordEventMode) override`
- L48 _public function_ `virtual void SetUrlDomain(const FString&, const TArray<FString>&) override`
- L49 _public function_ `virtual void SetUrlPath(const FString&) override`
- L50 _public function_ `virtual void SetHeader(const FString&, const FString&) override`
- L51 _public function_ `virtual void SetEventCallback(const OnEventRecorded&) override`
- L52 _public function_ `virtual void BlockUntilFlushed(float) override`
- L53 _public function_ `virtual const FAnalyticsET::Config& GetConfig() const override`
- L54 _public function_ `virtual void SetShouldRecordEventFunc(const ShouldRecordEventFunction&) override`
- L55 _public function_ `virtual FOnPreAnalyticsEventProcessed& OnPreAnalyticsEventProcessed() override`
- L56 _public function_ `virtual FOnAnalyticsEventQueued& OnAnalyticsEventQueued() override`
- L59 _public function_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>&) override`
- L60 _public function_ `virtual void EndSession() override`
- L61 _public function_ `virtual FString GetSessionID() const override`
- L62 _public function_ `virtual bool SetSessionID(const FString&) override`
- L63 _public function_ `virtual void FlushEvents() override`
- L64 _public function_ `virtual void SetUserID(const FString&) override`
- L65 _public function_ `virtual FString GetUserID() const override`
- L66 _public function_ `virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&&) override`
- L67 _public function_ `virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const override`
- L68 _public function_ `virtual int32 GetDefaultEventAttributeCount() const override`
- L69 _public function_ `virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int) const override`
- L72 _private member_ `FAnalyticsET::Config Config;`
- L73 _private member_ `FOnPreAnalyticsEventProcessed PreProcessedDelegate;`
- L74 _private member_ `FOnAnalyticsEventQueued QueuedDelegate;`

#### struct `FMockAnalyticsProviderET::FRecordedEvent`  
`struct FRecordedEvent`  
_L16-20_
- L18 _public member_ `FString EventName;`
- L19 _public member_ `TArray<FAnalyticsEventAttribute> Attributes;`

#### Free symbols / members of external scopes

- L27 _function_ `` (scope `FMockAnalyticsProviderET::FindAttribute`)

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolTests/Private/Mocks/MockModelContextProtocolResourceProvider.h` (Private)


#### struct `FMockModelContextProtocolResourceProvider`  
`struct FMockModelContextProtocolResourceProvider : IModelContextProtocolResourceProvider`  
_L8-50_
- inherits: `IModelContextProtocolResourceProvider`
- L10 _public member_ `TArray<FModelContextProtocolResourceDescriptor> Descriptors;`
- L11 _public member_ `TMap<FString, FModelContextProtocolResource> Resources;`
- L13 _public member_ `bool bListResourcesCalled = false;`
- L14 _public member_ `bool bReadResourceCalled = false;`
- L15 _public member_ `FString LastReadUri;`
- L17 _public function_ `virtual void ListResources(FModelContextProtocolResourceDescriptorList& OutResourceDescriptors) const override`
- L26 _public function_ `virtual TValueOrError<FModelContextProtocolResource, FString> ReadResource(const FString& Uri) const override`
- L38 _public function_ `void AddTextResource(const FString& Uri, const FString& Content, const TOptional<FString>& Name = {}, const TOptional<FString>& Title = {}, const TOptional<FString>& Description = {}, const TOptional<FString>& MimeType = {})` — Add a text resource with a fully described descriptor.
- L45 _public function_ `void AddBinaryResource(const FString& Uri, const TArray<uint8>& BlobContent, const TOptional<FString>& Name = {}, const TOptional<FString>& Title = {}, const TOptional<FString>& Description = {}, const TOptional<FString>& MimeType = {})` — Add a binary resource with a fully described descriptor.

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolTests/Private/Mocks/MockModelContextProtocolTool.h` (Private)


#### struct `FMockModelContextProtocolTool`  
`struct FMockModelContextProtocolTool : IModelContextProtocolTool`  
_L8-80_
- inherits: `IModelContextProtocolTool`
- L10 _public member_ `FString Name = TEXT("tes`
- L11 _public member_ `FString Description = TEXT("A t`
- L12 _public member_ `TSharedPtr<FJsonObject> InputSchema;`
- L13 _public member_ `TSharedPtr<FJsonObject> OutputSchema;`
- L15 _public member_ `TFunction<FModelContextProtocolToolResult(const TSharedPtr<FJsonObject>&)> RunFunction;`
- L17 _public member_ `bool bRunCalled = false;`
- L18 _public member_ `bool bRunAsyncCalled = false;`
- L19 _public member_ `bool bCancelAsyncCalled = false;`
- L20 _public member_ `TSharedPtr<FJsonObject> LastRunParams;`
- L21 _public member_ `FModelContextProtocolToolRequestId LastRunAsyncRequestId;`
- L22 _public member_ `FModelContextProtocolToolRequestId LastCancelledRequestId;`
- L24 _public function_ `virtual FString GetName() const override`
- L25 _public function_ `virtual FString GetDescription() const override`
- L26 _public function_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const override`
- L27 _public function_ `virtual TSharedPtr<FJsonObject> GetOutputJsonSchema() const override`
- L29 _public function_ `virtual FModelContextProtocolToolResult Run(const TSharedPtr<FJsonObject>& Params) override`
- L40 _public function_ `virtual void RunAsync(const FModelContextProtocolToolRequestId& RequestId, const TSharedPtr<FJsonObject>& Params, const FResultCallback& OnComplete) override`
- L47 _public function_ `virtual void CancelAsync(const FModelContextProtocolToolRequestId& RequestId) override`
- L54 _public function_ `static TSharedRef<FJsonObject> MakeTestInputSchema(const TMap<FString, FString>& Properties, const TArray<FString>& RequiredProperties = {})` — Create a JSON Schema object describing simple tool parameters.

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolTests/Private/ModelContextProtocolTestUtilities.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L15 _namespace_ `namespace Tests` (scope `UE::ModelContextProtocol`)
- L17 _function_ `inline FString GetTestBaseUrl()` (scope `UE::ModelContextProtocol::Tests`)
- L22 _function_ `inline FString JsonObjectToString(const TSharedRef<FJsonObject>& JsonObject)` (scope `UE::ModelContextProtocol::Tests`)
- L30 _function_ `inline TSharedRef<FJsonObject> MakeJsonRpcRequest(const FString& Method, const TSharedPtr<FJsonValue>& RequestId = MakeShared<FJsonValueNumber>(1), const TSharedPtr<FJsonObject>& Params = nullptr)` (scope `UE::ModelContextProtocol::Tests`)
- L46 _function_ `inline TSharedRef<FJsonObject> MakeJsonRpcNotification(const FString& Method, const TSharedPtr<FJsonObject>& Params = nullptr)` (scope `UE::ModelContextProtocol::Tests`)
- L59 _function_ `inline TSharedPtr<FJsonObject> ParseSseJsonResponse(FHttpResponsePtr Response)` (scope `UE::ModelContextProtocol::Tests`) — Parse the first SSE "data:" line from a text/event-stream response into a JSON object.
