# Plugins / DisplayClusterMessageInterception

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMessageInterceptor`
- headers: 2; symbols: 39
- symbol kinds: class=2, delegate=1, function=2, member=17, prototype=14, struct=3
- PrivateDependencyModuleNames: Concert, ConcertSyncClient, ConcertSyncCore, ConcertTransport, Core, CoreUObject, DisplayCluster, Engine, Messaging

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMessageInterceptor/Private/DisplayClusterMessageInterceptor.h` (Private)


#### struct `FInterceptedMessageDescriptor`  
`struct FInterceptedMessageDescriptor`  
_L18-27_
- L20 _public function_ `FInterceptedMessageDescriptor(TArray<FTopLevelAssetPath>&& InMessageTypes, FName InAnnotation) : MessageTypes(MoveTemp(InMessageTypes)) , Annotation(InAnnotation)`
- L25 _public member_ `TArray<FTopLevelAssetPath> MessageTypes;`
- L26 _public member_ `FName Annotation;`

#### class `FDisplayClusterMessageInterceptor`  
`class FDisplayClusterMessageInterceptor : public TSharedFromThis<FDisplayClusterMessageInterceptor, ESPMode::ThreadSafe> , public IMessageInterceptor , public IMessageSender`  
_L33-98_
- inherits: `TSharedFromThis<FDisplayClusterMessageInterceptor,ESPMode::ThreadSafe>,IMessageInterceptor,IMessageSender`
- desc: Display Cluster Message Interceptor Intercept message bus messages to process them in sync across the display cluster
- L38 _public prototype_ `FDisplayClusterMessageInterceptor();`
- L40 _public prototype_ `void Setup(IDisplayClusterClusterManager* InClusterManager, const FMessageInterceptionSettings& InInterceptionSettings);`
- L42 _public prototype_ `void Start(TSharedPtr<IMessageBus, ESPMode::ThreadSafe> InBus);`
- L43 _public prototype_ `void Stop();`
- L45 _public prototype_ `void SyncMessages();`
- L46 _public prototype_ `void HandleClusterEvent(const FDisplayClusterClusterEventJson& InEvent);`
- L47 _public prototype_ `void HandleClusterNodeFailure(const FString& NodeId);`
- L50 _public prototype_ `virtual FName GetDebugName() const override;` — IMessageInterceptor interface
- L51 _public prototype_ `virtual const FGuid& GetInterceptorId() const override;`
- L52 _public prototype_ `virtual bool InterceptMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context) override;`
- L55 _public prototype_ `virtual FMessageAddress GetSenderAddress() override;` — IMessageSender interface
- L56 _public prototype_ `virtual void NotifyMessageError(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const FString& Error) override;`
- L59 _private prototype_ `void Purge();` — Purge the message map and force their forwarding.
- L62 _private member_ `bool bIsIntercepting;` — Currently intercepting message bus.
- L65 _private member_ `FGuid InterceptorId;` — InterceptorId needed by message bus.
- L68 _private member_ `FMessageAddress Address;` — Sender address needed by message bus.
- L71 _private member_ `TSharedPtr<IMessageBus, ESPMode::ThreadSafe> InterceptedBus;` — The bus this interceptor is intercepting messages on.
- L74 _private member_ `IDisplayClusterClusterManager* ClusterManager;` — The cluster manager to sync messages across.
- L77 _private member_ `FCriticalSection ContextQueueCS;` — Critical section for the intercepted messages.
- L80 _private member_ `FMessageInterceptionSettings InterceptionSettings;` — Settings to be used for interception
- L83 _private member_ `TArray<FInterceptedMessageDescriptor> InterceptedMessages;` — Description of messages we intercept
- L97 _private member_ `TMap<FString, FContextSync> ContextMap;` — The intercepted message map (MessageId-to-MessageContext).

#### struct `FDisplayClusterMessageInterceptor::FContextSync`  
`struct FContextSync`  
_L86-94_
- desc: Holds intercepted messages and their current sync state across the cluster.
- L88 _public function_ `FContextSync(TSharedPtr<IMessageContext, ESPMode::ThreadSafe> InContext) : ContextPtr(InContext)`
- L92 _public member_ `TSet<FString> NodesReceived;`
- L93 _public member_ `TSharedPtr<IMessageContext, ESPMode::ThreadSafe> ContextPtr;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterInterception, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterInterception, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMessageInterceptor/Public/DisplayClusterMessageInterceptionSettings.h` (Public)


#### struct `FMessageInterceptionSettings`  
`struct FMessageInterceptionSettings`  
_L10-31_
- reflection: `USTRUCT()`
- L22 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(config, EditAnywhere, Category = "Interception Settings")` — Indicates if message interception is enabled.
- L26 _public member_ `bool bInterceptMultiUserMessages = true;` — `UPROPERTY(config, EditAnywhere, Category = "Interception Settings", meta=(EditCondition = "bIsEnabled"))` — Indicates whether messages from multi user are intercepted.
- L30 _public member_ `float TimeoutSeconds = 1.0f;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Interception Settings")` — Maximum seconds to keep intercepted message to be synchronized across cluster.

#### class `UDisplayClusterMessageInterceptionSettings`  
`class UDisplayClusterMessageInterceptionSettings : public UObject`  
_L35-47_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L46 _public member_ `FMessageInterceptionSettings InterceptionSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Interception Settings", meta = (ShowOnlyInnerProperties))` — Settings related to interception. @note Settings from primary node will be synchronized across the cluster
