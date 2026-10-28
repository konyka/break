# Plugins / AsyncMessageSystem

- module root: `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem`
- headers: 15; symbols: 259
- symbol kinds: class=12, delegate=1, enum=1, enumerator=3, function=18, macro=9, member=72, prototype=130, struct=10, typedef=2, union=1
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, GameplayTags

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Private/AsyncAction_ListenForMessage.h` (Private)


#### class `UAsyncAction_ListenForAsyncMessage`  
`class UAsyncAction_ListenForAsyncMessage : public UBlueprintAsyncActionBase`  
_L32-130_
- reflection: `UCLASS(BlueprintType, meta=(ExposedAsyncProxy = "AsyncMessageTask"))`
- inherits: `UBlueprintAsyncActionBase`
- desc: An async action for binding a listener to a message. The user will call the "StartListeningForAsyncMessage" function from blueprints, which will create the async action object and an exec pin will be created for any BP Assignable delegates on this object (FAsyncMessageReceivedDelegate). Those delegates can then fire when the message is received, and we can allow users to specify their own tick groups upon binding as well. We expose this as an async proxy (ExposedAsyncProxy) because then you can easily call the "StopListeningForAsyncMessage" function to unbind the listener. If for some reason there is a failure when binding to the message, this async task will be immedately marked as being ready for destruction.
- L46 _public prototype_ `static UAsyncAction_ListenForAsyncMessage* StartListeningForAsyncMessage( UObject* WorldContextObject, const FAsyncMessageId MessageId, TScriptInterface<IAsyncMessageBindingEndpointInterface> DesiredEndpoint, const TEnumAsByte<ETickingGroup> TickGroup = TG_PostUpdateWork);` — `UFUNCTION(BlueprintCallable, Category = "Async Messages", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true", AdvancedDisplay="TickGroup", DisplayName="Start Listening for Async Message"))` — Starts listening for an Async Message with the given ID during the given tick group. @param MessageId The ID of the Async Message which you would like to listen to @param DesiredEndpoint The endpoint which this listener should bind to. If nothing is provided, the default world endpoint will be used. @param TickGroup The tick group which you would like to receive the message in. Default is TG_PostUpdateWork.
- L56 _public prototype_ `void StopListeningForAsyncMessage();` — `UFUNCTION(BlueprintCallable, Category = "Async Messages")` — Stops the given message handle from receiving any more messages.
- L62 _public member_ `FAsyncMessageReceivedDelegate OnMessageReceived;` — `UPROPERTY(BlueprintAssignable)` — Delegate which executes when the bound message that this async action is listening for is broadcast.
- L67 _protected prototype_ `virtual void Activate() override;`
- L68 _protected prototype_ `virtual void SetReadyToDestroy() override;`
- L74 _protected prototype_ `void StartListeningForMessage();` — Binds a listener to for the MessageToListenFor message id to the HandleMessageReceived function
- L79 _protected prototype_ `void UnbindListener();` — Unbinds the listener handle for this async action so no more messages will be processed by it.
- L85 _protected prototype_ `void HandleMessageReceived(const FAsyncMessage& Message);` — The callback function which will call the OnMessageReceived delegate and give blueprints the oppurtunity to process the message.
- L90 _protected prototype_ `TSharedPtr<FAsyncGameplayMessageSystem> GetAssociatedMessageSystem() const;` — @return The gameplay message system associated with the outer world of this async action.
- L95 _protected prototype_ `TObjectPtr<UAsyncMessageWorldSubsystem> GetAssociatedSubsystem() const;` — @return The async message world subsystem associated with the outer world of this async action.
- L100 _protected member_ `TWeakObjectPtr<UWorld> WeakWorldPtr = nullptr;` — Weak pointer to the owning wold context to which this listener belongs
- L105 _protected member_ `TWeakPtr<FAsyncMessageBindingEndpoint> DesiredEndpoint = nullptr;` — The specific endpoint to start listening for this message on.
- L110 _protected member_ `FAsyncMessageId MessageToListenFor = FAsyncMessageId::Invalid;` — The async message id that this action should listen
- L117 _protected member_ `FAsyncMessageBindingOptions BindingOptions = {};` — The binding options to use when listening for this message. The tick group of this binding option is set on construction of this object in StartListeningForAsyncMessage.
- L122 _protected member_ `FAsyncMessageHandle BoundListenerHandle = FAsyncMessageHandle::Invalid;` — The listener handle which has been bound to the message
- L129 _protected member_ `FDelegateHandle OnMessageSystemShutdownDelegateHandle;` — Handle to a delegate which fires when the world subsystem which owns the message system that this async action is listening for shuts down. This allows us to clean up this async action and mark it as being ready for destruction.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncMessageReceivedDelegate, const FAsyncMessage&, Message);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncMessageReceivedDelegate, const FAsyncMessage&, Message);`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Private/AsyncMessageBlueprintLibrary.h` (Private)


#### class `UAsyncMessageSystemBlueprintLibrary`  
`class UAsyncMessageSystemBlueprintLibrary final : public UBlueprintFunctionLibrary`  
_L15-70_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for the Async Message System
- L33 _public prototype_ `static bool QueueAsyncMessageForBroadcast( UObject* WorldContextObject, const FAsyncMessageId& MessageId, const FInstancedStruct& Payload, TScriptInterface<IAsyncMessageBindingEndpointInterface> DesiredEndpoint);` — `UFUNCTION(BlueprintCallable, Category = "Async Messages", meta=(WorldContext="WorldContextObject", AutoCreateRefTerm = "Payload" ,ReturnDisplayName = "Success"))` — Queues the given async message for broadcast the next time that this message system processes its message queue @param MessageId		The message that you would like to queue for broadcasting @param Payload		The payload data of this message. This payload data will be COPIED to the message queue to to make it safe for listeners on other threads. @param DesiredEndpoint The endpoint which this listener should bind to. If nothing is provided, the default world endpoint will be used. @return True if this message had an listeners bound to it and it was successfully queued
- L46 _public prototype_ `static FString Conv_AsyncMessageIdToString(const FAsyncMessageId& MessageId);` — `UFUNCTION(BlueprintPure, Category = "Utilities|String", meta=(DisplayName = "To String (Async Message Id)", CompactNodeTitle = "->", BlueprintAutocast))` — Get the string representation of the given Async Message Id. @param MessageId The Message Id to get the string representation of @return The String representation of the give async message Id
- L57 _public prototype_ `static FString GetMessageNativeQueueCallstack(const FAsyncMessage& Message);` — `UFUNCTION(BlueprintPure, Category = "Async Messages|Debug")` — Gets the given message's callstack of when and where it was queued from native C++ code. Note: bShouldRecordQueueCallstackOnMessages must be enabled in the project settings for this to have accurate data @param Message The async message to get the callstack of to determine when and where it was queued. @return The callstack of where the message was queued from
- L68 _public prototype_ `static FString GetMessageBlueprintScriptCallstack(const FAsyncMessage& Message);` — `UFUNCTION(BlueprintPure, Category = "Async Messages|Debug")` — Gets the given message's callstack of when and where it was queued from in blueprints/script Note: bShouldRecordQueueCallstackOnMessages must be enabled in the project settings for this to have accurate data @param Message The async message to get the callstack of to determine when and where it was queued. @return The script callstack of where the message was queued from

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Private/AsyncMessageDeveloperSettings.h` (Private)


#### class `UAsyncMessageDeveloperSettings`  
`class UAsyncMessageDeveloperSettings final : public UDeveloperSettings`  
_L11-121_
- reflection: `UCLASS(Config=Game)`
- inherits: `UDeveloperSettings`
- L17 _public prototype_ `[[nodiscard]] bool GetShouldEnableWorldSubsystem() const;`
- L18 _public prototype_ `[[nodiscard]] bool GetShouldEnableWorldSubsystemInEditor() const;`
- L24 _public prototype_ `[[nodiscard]] bool ShouldDebugMessageOnQueue(const FAsyncMessageId& Message) const;` — @param Message The message to check if it should have its stack trace dumped to the log @return True if this message should dump its current stack trace to the log
- L29 _public prototype_ `[[nodiscard]] bool ShouldTriggerBreakPointOnMessageQueue() const;` — @return True if a breakpoint should be triggered when a message id with debugging enabled is queued for broadcast.
- L34 _public prototype_ `[[nodiscard]] bool ShouldPrintScriptCallstackOnMessageQueue() const;` — @return True if the Blueprint VM callstack should be printed when a message with debugging enabled is queued for broadcast.
- L41 _public prototype_ `[[nodiscard]] bool ShouldRecordQueueCallstackOnMessages() const;` — @return True if the callstack should be recorded as a property on the Async Message itself. This can make debugging where a message was queued from signifigantly easier if you are starting from the listener.
- L63 _private member_ `bool bMessageQueueDebugEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages|Debug")` — Enabled the conditional logging of stack traces and C++ breakpoints being triggered when certain messages are queued for broadcasting to the message system. This can make it easier to debug where messages are coming from, since the processing of messages is all deferred and it can be difficult to track down what is queuing a message in cooked/optimized builds. This will only work if the ENABLE_ASYNC_MESSAGES_DEBUG pre-processor definition is non-zero. By default, ENABLE_ASYNC_MESSAGES_DEBUG is "1" for any non-shipping or editor build (WITH_EDITOR || !UE_BUILD_SHIPPING). If you wish to override this behavior, then you can add a definition to your game's .build.cs file: PublicDefinitions.Add("ENABLE_ASYNC_MESSAGES_DEBUG=1"); @see AsyncMessageSystemBase.h @see FAsyncMessageSystemBase::QueueMessageForBroadcast
- L72 _private member_ `bool bTriggerDebugBreakpointWhenMessageQueued = false;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages|Debug", meta=(EditCondition="bMessageQueueDebugEnabled"))` — If true, then a native C++ breakpoint will be triggered when when certain messages are queued for broadcasting to the message system. @see FAsyncMessageSystemBase::QueueMessageForBroadcast
- L81 _private member_ `bool bPrintScriptCallstackWhenMessageQueued = false;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages|Debug", meta=(EditCondition="bMessageQueueDebugEnabled"))` — If true, then the script callstack will also be printed when certain messages are queued for broadcasting to the message system. @see FAsyncMessageSystemBase::QueueMessageForBroadcast
- L91 _private member_ `bool bShouldRecordQueueCallstackOnMessages = false;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages|Debug")` — If true, then the callstack at the time of a message being queued will be recorded and stored on the FAsyncMessage instance itself. This can make debugging listeners significantly easier if you need to get an idea of where a message is coming from. @see FAsyncMessageSystemBase::QueueMessageForBroadcast_Impl
- L101 _private member_ `bool bEnabledDebuggingForAllQueuedMessages = false;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages|Debug", meta=(EditCondition="bMessageQueueDebugEnabled"))` — If true, then ALL messages queued for broadcast will have their debug information processed. Note: This will likely have a large performance impact. If false, then only messages in the "EnabledDebugMessages" array will be debugged when queued.
- L108 _private member_ `TArray<FAsyncMessageId> EnabledDebugMessages;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages|Debug", meta=(EditCondition="bMessageQueueDebugEnabled && !bEnabledDebuggingForAllQueuedMessages"))` — Array of Async Message Id's which you would like to enable for debugging when they are queued for broadcasting to the message system.
- L114 _private member_ `bool bEnableWorldSubsystem = true;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages")` — If true, then the async message world subsystem will be enabled.
- L120 _private member_ `bool bEnableWorldSubsystemInEditor = false;` — `UPROPERTY(EditDefaultsOnly, Config, Category = "Async Messages")` — If true, then the async message subsystem will be created for editor worlds.

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Private/AsyncMessageSystemModule.h` (Private)


#### class `FAsyncMessageSystemModule`  
`class FAsyncMessageSystemModule final : public IModuleInterface`  
_L7-17_
- inherits: `IModuleInterface`
- L16 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncGameplayMessageSystem.h` (Public)


#### class `FAsyncGameplayMessageSystem`  
`class FAsyncGameplayMessageSystem final : public FAsyncMessageSystemBase`  
_L18-113_
- inherits: `FAsyncMessageSystemBase`
- desc: Implementation of an async message system which schedules the processing of messages based on tick groups and named thread async tasks, making it integrate nicely with common gameplay frameworks in Unreal.
- L24 _public prototype_ `explicit FAsyncGameplayMessageSystem(UWorld* OwningWorld);`
- L28 _private prototype_ `virtual void Startup_Impl() override;`
- L29 _private prototype_ `virtual void Shutdown_Impl() override;`
- L30 _private prototype_ `virtual void PostQueueMessage(const FAsyncMessageId MessageId, const TArray<FAsyncMessageBindingOptions>& OptionsBoundTo) override;`
- L36 _private prototype_ `void CreateTickFunctions();` — Creates and registers tick functions for this message system to the outer world.
- L41 _private prototype_ `void DestroyTickFunctions();` — Destroy any registered tick functions on this message system
- L49 _private prototype_ `void StartAsyncProcessForBinding(const FAsyncMessageBindingOptions& Options);` — Starts an async task to process the messages with listeners that have the given binding options. This should ONLY be called for binding options which are not tick groups. @param Options The options of which to start async processing for.
- L58 _private prototype_ `void EnableExecutionForTickGroupBinding(const FAsyncMessageBindingOptions& Options);` — Called when a message is queued with listeners who have bindings options set to use a Tick Group. This will request a tick function to execute once via the TaskSyncManager to process the message queue for the given group. @param Options The binding options that we want to enable the tick function for to process its listeners
- L66 _private prototype_ `UE::Tick::FActiveSyncWorkHandle* GetOrCreateWorkHandleForTickGroup(const ETickingGroup Group);` — Get or create the work handle required to request work from the task sync manager. @param Group The tick group to get the sync work handle for @return Pointer to the work handle which can then be used to request work. Nullptr if the work handle cannot be created.
- L73 _private prototype_ `void ProcessMessagesForTickGroup(const ETickingGroup TickGroup);` — Processes all pending messages in the queue for the given tick group. This is meant to be called from a FTickFunction. This will just create the necessary FAsyncMessageBindingOptions args to call the FAsyncMessageSystemBase::ProcessMessageQueueForBinding.
- L79 _private member_ `TWeakObjectPtr<UWorld> OuterWorld = nullptr;` — The world in which this message system belongs to. The tick functions of this message system will be registered to this world's persistent level.
- L86 _private member_ `TMap<ETickingGroup, TSharedPtr<FTickFunction>> TickFunctions;` — Tick functions which are created when this message system starts. There is one tick functions for each tick group that this message system supports and they will depend on one another to keep a deterministic ordering of ticking on this message system.
- L93 _private member_ `TMap<ETickingGroup, UE::Tick::FActiveSyncWorkHandle> WorkHandles;` — Handles that we can use to request work (in our case, process messages for a specific tick group) These handles need to be accessed behind the WorkHandleCreationCS
- L98 _private member_ `static constexpr ETickingGroup EarliestSupportedTickGroup = TG_PrePhysics;` — The tick group earliest in the frame which this message system supports.
- L103 _private member_ `static constexpr ETickingGroup LatestSupportedTickGroup = TG_PostUpdateWork;` — The tick group that is the latest in frame time which this message system will support
- L108 _private member_ `ETickingGroup CurrentTickGroup = EarliestSupportedTickGroup;` — Keep track of the state of what tick group is currently executing and what the last one was.
- L109 _private member_ `ETickingGroup LastTickedGroup = LatestSupportedTickGroup;`
- L112 _private member_ `FCriticalSection WorkHandleCreationCS;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessage.h` (Public)


#### struct `FAsyncMessage`  
`struct FAsyncMessage final`  
_L38-246_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single async message which has been queued for broadcasting, and listeners are interested in receiving the data from. Async Message Messages contain some data about when, where, and how the message was queued which make it possible to synchronize game state across multiple threads with messages.
- L43 _public prototype_ `FAsyncMessage() = default;`
- L45 _public prototype_ `FAsyncMessage( const FAsyncMessageId& MessageId, const FAsyncMessageId& MessageSourceId, const double MessageTimestamp, const uint64 CurrentFrame, const uint32 ThreadQueuedFrom, const uint32 MessageSequenceCounter, FConstStructView InPayloadData, TWeakPtr<FAsyncMessageBindingEndpoint> InBindingEndpoint);`
- L58 _public prototype_ `FAsyncMessageId GetMessageId() const;` — Returns this message's unique ID which listeners use to bind to it.
- L65 _public prototype_ `void SetMessageId(const FAsyncMessageId& NewMessageId);` — Sets the current message id which this FAsyncMessage represents to another message @param NewMessageId The new message Id to set
- L70 _public prototype_ `FAsyncMessageId GetMessageSourceId() const;` — Returns this the source message which caused this message to be queued
- L75 _public prototype_ `double GetQueueTimestamp() const;` — Returns the timestamp which this message message was queued on.
- L80 _public prototype_ `uint64 GetQueueFrame() const;` — Returns the frame (GFrameNumber) of which this message was queued for broadcast.
- L85 _public prototype_ `uint32 GetThreadQueuedFromThreadId() const;` — Returns the thread Id from which this message was queued from ( FPlatformTLS::GetCurrentThreadId() )
- L92 _public prototype_ `uint32 GetSequenceId() const;` — Returns the “sequence ID” of this message. If there are multiple of the same message queued for broadcast on a single frame, then this sequence ID can be used to order them and determine which was queued first if desired.
- L97 _public prototype_ `FStructView GetPayloadView();` — Get the mutable payload data associated with this async message.
- L102 _public prototype_ `FConstStructView GetPayloadView() const;` — Get the const payload data associated with this async message.
- L108 _public function_ `template<typename TDataType> TDataType* GetPayloadData() const` — Returns the typed data pointer of this message's payload. Nullptr if the payload is invalid.
- L116 _public prototype_ `TSharedPtr<FAsyncMessageBindingEndpoint> GetBindingEndpoint() const;` — Returns the endpoint which this message should be broadcast on.
- L118 _public function_ `inline void AddReferencedObjects(FReferenceCollector& Collector)`
- L129 _private member_ `FAsyncMessageId MessageId = FAsyncMessageId::Invalid;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Async Message", meta = (AllowPrivateAccess = "true"))` — The Async message Id which this message is a part of.
- L142 _private member_ `FAsyncMessageId MessageSourceId = FAsyncMessageId::Invalid;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Async Message", meta = (AllowPrivateAccess = "true"))` — The source of this message. This might be different from the "MessageId", because this could be a parent message which is being triggered by a child message. In that case, the "MessageId" would be the parent message, and the "MessageSourceId" would be the actual child message which had triggered. For example, if "message.colors.red" is a child message of "message.colors", then the "MessageId" would be "message.colors" and the MessageSourceId would be "message.colors.red". If the MessageSourceId and MessageId are the same value, then that means that this is the childmost message.
- L148 _private member_ `double QueueTime = 0.0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Async Message", meta = (AllowPrivateAccess = "true"))` — The time at which this message was queued ( FApp::GetCurrentTime() )
- L153 _private member_ `uint64 QueueFrame = 0;` — The frame at which this message was queued ( GFrameCounter )
- L158 _private member_ `uint32 ThreadQueuedFrom = 0;` — The ThreadId from which this message was queued from ( FPlatformTLS::GetCurrentThreadId() )
- L166 _private member_ `uint32 SequenceId = 0;` — The sequence of this specific message if there were multiple in the message queue at one time. This will allow async listeners to determine which message of this type was queued first if there are multiple.
- L183 _private member_ `FInstancedStruct PayloadCopy;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Async Message", meta = (DisplayName="Payload", AllowPrivateAccess = "true"))` — A copy of the payload data that is created upon construction of this message. This data is copied in the constructor of this message when the message is queued in order to make the data thread safe to access. If you would like to have more control over the payload data and how it is synconized (for example if you have a costly payload type which would be too expensive to copy) then you could make your payload struct contain a simple pointer and handle synchronization yourself with critical sections. TODO: When we copy the payload data, have it use a custom linear allocator on the owning message system to make it faster to copy and more cache friendly to the message system to iterate messages.
- L191 _private member_ `TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint = nullptr;` — Pointer to which endpoint this message should be broadcast on. Store this as a weak pointer because we don't want any messages to be keeping handlers from GC'ing if they are destroyed over time
- L234 _public prototype_ `const FString& GetNativeCallstack() const;`
- L236 _public prototype_ `const FString& GetBlueprintScriptCallstack() const;`
- L238 _public prototype_ `const uint32 GetDebugMessageId() const;`
- L240 _public prototype_ `void SetDebugData(FMessageDebugData* InData);`
- L244 _private member_ `FMessageDebugData* DebugData = nullptr;`

#### struct `FAsyncMessage::FMessageDebugData`  
`struct FMessageDebugData`  
_L202-232_
- L208 _public member_ `TArray<uint64> NativeCallstack;` — The native stack back trace at the time of this message being queued. Populated by FPlatformStackWalk::CaptureStackBackTrace in FAsyncMessageSystemBase::QueueMessageForBroadcast_Impl.
- L214 _public member_ `mutable FString NativeCallstackAsString;` — A debugging nicety. This is a string which holds the callstack from where this message was queued from. Mutable so that we can cache the value in GetOrCreateNativeCallstackAsString.
- L219 _public member_ `FString BlueprintScriptCallstack;` — A debugging nicety. This is a string which holds the blueprint/script callstack from where this message was queued from.
- L225 _public member_ `uint32 MessageId = 0u;` — Unique int id assigned at the time of creation. Each message gets a unique ID which can then be used to look up the debug data on the message store.
- L231 _public prototype_ `const FString& GetOrCreateNativeCallstackAsString() const;` — Generates and caches the FString version of the platform callstack @return the Cachced string which represents the callstack.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`
- L25 _macro_ `#define ENABLE_ASYNC_MESSAGES_DEBUG WITH_EDITOR || !UE_BUILD_SHIPPING`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageBindingComponent.h` (Public)


#### class `UAsyncMessageBindingEndpointInterface`  
`class UAsyncMessageBindingEndpointInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IAsyncMessageBindingEndpointInterface`  
`class IAsyncMessageBindingEndpointInterface`  
_L23-36_
- desc: Interface to implement which will allow users to specify which binding endpoint should be used in any script functions for the async message system.
- L32 _public function_ `virtual TSharedPtr<FAsyncMessageBindingEndpoint> GetEndpoint() const` — @return Pointer to the specific binding endpoint which you would like to set for your message or listener.

#### class `UAsyncMessageBindingComponent`  
`class UAsyncMessageBindingComponent : public UActorComponent, public IAsyncMessageBindingEndpointInterface`  
_L46-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories=(Object,Replication,Navigation), Meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IAsyncMessageBindingEndpointInterface`
- desc: A blueprint component which will allow you to specify a specific endpoint to use when queueing messages or binding listeners to the Async Message System. By default, this will create an endpoint on InitializeComponent (making it ready for use during Begin Play) and destroy it on UninitializeComponent.
- L55 _protected prototype_ `virtual void InitializeComponent() override;`
- L56 _protected prototype_ `virtual void UninitializeComponent() override;`
- L60 _protected prototype_ `virtual TSharedPtr<FAsyncMessageBindingEndpoint> GetEndpoint() const override;`
- L63 _protected prototype_ `virtual void CreateEndpoint();`
- L64 _protected prototype_ `virtual void CleanupEndpoint();`
- L66 _protected member_ `TSharedPtr<FAsyncMessageBindingEndpoint> Endpoint = nullptr;`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageBindingEndpoint.h` (Public)


#### class `FAsyncMessageBindingEndpoint`  
`class FAsyncMessageBindingEndpoint final : public TSharedFromThis<FAsyncMessageBindingEndpoint>`  
_L26-99_
- inherits: `TSharedFromThis<FAsyncMessageBindingEndpoint>`
- desc: The message binding endpoint is what stores the actual map of listeners and what Message Id's they are bound to. When binding to a message or queueing a message for broadcast, you can specify the endpoint. Listeners will only receive the messages queued for their own endpoints. This makes it easy to filter messages to a specific endpoint. These endpoints can be utilized within the game frame in a rather customizable way. One example would be to add create an Actor Component which has an endpoint. This way, you could send messages directly to a single specific actor.
- L31 _public prototype_ `FAsyncMessageBindingEndpoint() = default;`
- L33 _public typedef_ `using FMessageCallbackFunc = TFunction<void(const FAsyncMessage&)>;`
- L73 _public prototype_ `FAsyncMessageBoundData* GetBoundDataForMessage(const FAsyncMessageId& MessageId);` — Returns data about listeners bound to the given async message id. @param MessageId The message id to find bindings for. @return A pointer to the bound message data. Nullptr if there are no listeners bound to this message.
- L80 _public prototype_ `FAsyncMessageBoundData& FindOrAddMessageData(const FAsyncMessageId& MessageId);` — Finds or adds a binding to the given message id. @param MessageId @return
- L85 _public prototype_ `uint32 GetNumberOfBoundListeners() const;` — @return The total number of bound listeners to this endpoint
- L91 _public prototype_ `bool IsHandleBound(const FAsyncMessageHandle& Handle) const;` — @param Handle The message handle to check if it is bound to this endpoint @return True if the given handle is bound to this endpoint
- L98 _private member_ `TMap<FAsyncMessageId, FAsyncMessageBindingEndpoint::FAsyncMessageBoundData> BoundMessageListenerMap;` — Map of message ID's to their associated message data.

#### struct `FAsyncMessageBindingEndpoint::FAsyncMessageIndividualListener`  
`template <typename CallbackFuncSignature> struct FAsyncMessageIndividualListener`  
_L39-51_
- desc: Data stored about a single individual listener of a message
- L44 _public member_ `FAsyncMessageHandle Handle;` — The handle to this individual listener assigned when it is bound to this message system.
- L50 _public member_ `CallbackFuncSignature Callback;` — The delegate that listeners can bind to if they want to be called when this message is broadcast.

#### struct `FAsyncMessageBindingEndpoint::FAsyncMessageBoundData`  
`struct FAsyncMessageBoundData`  
_L56-65_
- desc: Data store for everything related to a single message
- L64 _public member_ `TMap<FAsyncMessageBindingOptions, TArray<FAsyncMessageIndividualListener<FMessageCallbackFunc>>> ListenerMap;` — A map of listeners for this message, ordered by their binding options. This lets us keep track of how many binders are listening for this message on a specific tick group or thread id

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageBindingOptions.h` (Public)


#### struct `FAsyncMessageBindingOptions`  
`struct FAsyncMessageBindingOptions final`  
_L23-133_
- desc: Options used to specify when a binder would like to receive a message when it is broadcast. If you would like your listener to receive its messages within a specific tick group on the game thread, create the options with a TickGroup and it will set UseTickGroup. If you would like your listener to receive its messages within a specific named thread and/or pool of named threads create the options with a named thread (including advanced variants) and it will set UseNamedThreads. If you would like your listener to receive its messages from within a specifc set of UE::Tasks priority thread pools create the options with a task priority and extended priority and it will set UseTaskPriorities.
- L27 _public prototype_ `FAsyncMessageBindingOptions();`
- L28 _public prototype_ `FAsyncMessageBindingOptions(const ETickingGroup DesiredTickGroup);`
- L29 _public prototype_ `FAsyncMessageBindingOptions(const ENamedThreads::Type NamedThreads);`
- L30 _public prototype_ `FAsyncMessageBindingOptions(const UE::Tasks::ETaskPriority InTaskPriority, const UE::Tasks::EExtendedTaskPriority InExtendedTaskPriority);`
- L55 _public function_ `EBindingType GetType() const` — Determines which type of configuration this listener follows
- L62 _public prototype_ `void SetTickGroup(const ETickingGroup DesiredTickGroup);` — Set this binding to receive a message on the main game thread during the specific tick group
- L65 _public prototype_ `ETickingGroup GetTickGroup() const;` — If type is UseTickGroup, this binding will receive a message on the main game thread during the specific tick group
- L69 _public prototype_ `void SetNamedThreads(const ENamedThreads::Type NamedThreads);` — Set this binding to receive a message on a set of named threads
- L72 _public prototype_ `ENamedThreads::Type GetNamedThreads() const;` — If type is UseNamedThreads, this will be used to determine which set of named threads you would like to use
- L76 _public prototype_ `void SetTaskPriorities(const UE::Tasks::ETaskPriority InTaskPriority, const UE::Tasks::EExtendedTaskPriority InExtendedTaskPriority = UE::Tasks::EExtendedTaskPriority::None);` — Set this binding to receive a message on a thread with the matching task priority and extended priority
- L79 _public prototype_ `UE::Tasks::ETaskPriority GetTaskPriority() const;` — If type is UseTaskPriorities, this will be used to determine the task priority you would like to use
- L82 _public prototype_ `UE::Tasks::EExtendedTaskPriority GetExtendedTaskPriority() const;` — If type is UseTaskPriorities, this will be used to determine the extended task priority you would like to use
- L91 _private member_ `EBindingType Type = EBindingType::UseTickGroup;` — The type of binding options which should be used to determine where a listener would like to receive its messages.
- L116 _public function_ `bool operator==(const FAsyncMessageBindingOptions& Other) const`
- L123 _public function_ `bool operator!=(const FAsyncMessageBindingOptions& Other) const`

#### enum `FAsyncMessageBindingOptions::EBindingType`  
`enum class EBindingType : uint8`  
_L35-52_
- desc: Determines which type of configuration this listener follows
- L40 _public enumerator_ `UseTickGroup = 0` — If set, then this binding will receive a message on the main game thread during the specific tick group.
- L45 _public enumerator_ `UseNamedThreads = 1` — If set, then this binding will receive a message on a thread matching these named thread options.
- L51 _public enumerator_ `UseTaskPriorities = 2` — If set, then this binding will receive a message on a thread determined by the UE::Tasks::ETaskPriority and UE::Tasks::EExtendedTaskPriority.

#### union `FAsyncMessageBindingOptions::(anonymous)`  
``  
_L94-112_

#### struct `FAsyncMessageBindingOptions::__anondc4fd200010a::(anonymous)`  
``  
_L101-111_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`
- L98 _member_ `int32 ThreadOrGroup;` (scope `FAsyncMessageBindingOptions::__anondc4fd200010a`) — Based on type, this identifies the thread identifier in which the binding object would like to receive a callback, or the tick group on game thread
- L105 _member_ `UE::Tasks::ETaskPriority TaskPriority;` (scope `FAsyncMessageBindingOptions::__anondc4fd200010a::__anondc4fd2000208`) — Identifies the UE::Tasks task priority which this binding would like to receive a callback on
- L110 _member_ `UE::Tasks::EExtendedTaskPriority ExtendedTaskPriority;` (scope `FAsyncMessageBindingOptions::__anondc4fd200010a::__anondc4fd2000208`) — Identifies the UE::Tasks extended priority which this binding would like to receive a callback on
- L128 _function_ `friend inline uint32 GetTypeHash(const FAsyncMessageBindingOptions& Opts)`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageHandle.h` (Public)


#### struct `FAsyncMessageHandle`  
`struct FAsyncMessageHandle final`  
_L22-103_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle used to identify a bound listener to an Async Message. These handles are unique to each bound listener and created by the owning FAsyncMessageSystemBase that the Message was bound to.
- L33 _public prototype_ `FAsyncMessageHandle() = default;` — Default constructor of a Message handle. This default handle will be invalid. Valid handles should only be created from an operating async message system (@see FAsyncMessageSystemBase).
- L38 _public prototype_ `bool IsValid() const;` — Returns true if this Message handle has a valid internal ID.
- L43 _public prototype_ `uint32 GetId() const;` — Returns the internal ID of this handle.
- L48 _public prototype_ `FAsyncMessageId GetBoundMessageId() const;` — Returns the Message in which this handle is bound to.
- L53 _public prototype_ `FString ToString() const;` — Returns a formatted string which represents this handle's data.
- L55 _public prototype_ `bool operator==(const FAsyncMessageHandle& Other) const;`
- L56 _public prototype_ `bool operator!=(const FAsyncMessageHandle& Other) const;`
- L57 _public prototype_ `bool operator>=(const FAsyncMessageHandle& Other) const;`
- L58 _public prototype_ `bool operator<(const FAsyncMessageHandle& Other) const;`
- L64 _public prototype_ `TSharedPtr<FAsyncMessageBindingEndpoint> GetBindingEndpoint() const;` — @return A pointer to the endpoint which this handle is bound to.
- L70 _public member_ `static const FAsyncMessageHandle Invalid;` — Represents an invalid handle which cannot have any Message listeners bound to it and means that no more Messages will be received.
- L77 _private prototype_ `FAsyncMessageHandle( const uint32 InHandleValue, const FAsyncMessageId BoundMessageId, TWeakPtr<FAsyncMessageBindingEndpoint> InBindingEndpoint);` — Private constructor for use by the message system
- L85 _private member_ `static constexpr uint32 InvalidHandleIndex = 0u;` — Internal index for message handles which we consider to be invalid.
- L91 _private member_ `uint32 InternalHandle = FAsyncMessageHandle::InvalidHandleIndex;` — `UPROPERTY(VisibleAnywhere, Category="Async Message")` — The value of this internal handle.
- L97 _private member_ `FAsyncMessageId BoundMessage = FAsyncMessageId::Invalid;` — `UPROPERTY(VisibleAnywhere, Category="Async Message")` — The async message that this handle is bound to.
- L102 _private member_ `TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint = nullptr;` — The endpoint which this handle is bound to.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageId.h` (Public)


#### struct `FAsyncMessageId`  
`struct FAsyncMessageId final`  
_L22-105_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a single message which can be bound to and queued in the async message system. This ID is what you use to bind to (listen for) messages which are being broadcast, as well as actually queue the message for broadcasting. Internally this is simply a FGameplayTag, which is how this Message's parent hierarchy is determined.
- L27 _public prototype_ `FAsyncMessageId() = default;`
- L36 _public prototype_ `FAsyncMessageId(const FName MessageName);` — Constructs a MessageId from the given FName. Note: This will internally be requesting a gameplay tag representation of this FName, and will ensure if it is not found. @param MessageName The FName representation of this MessageId
- L43 _public prototype_ `FAsyncMessageId(const FGameplayTag& MessageTag);` — Constructs a FAsyncMessageId from the FName associated with the given Gameplay Tag. @param MessageTag The gameplay tag to construct a Message Id from
- L44 _public prototype_ `~FAsyncMessageId() = default;`
- L49 _public prototype_ `[[nodiscard]] bool IsValid() const;` — @return True if this is a valid MessageId which can be used to bind and queue messages.
- L54 _public prototype_ `[[nodiscard]] FName GetMessageName() const;` — @return The raw FName which represents this MessageId
- L59 _public prototype_ `[[nodiscard]] FString ToString() const;` — @return FString representation of this MessageId
- L67 _public prototype_ `[[nodiscard]] FAsyncMessageId GetParentMessageId() const;` — Returns the parent of this async message. The parent is parsed out of the underlying FName which represents this message by '.' delimeters. For example, the parent of "message.id.test" is "message.id" , and the parent of "message.id" is "message". If there are no '.' delimeters in the message's name then it does not have a parent, and this will return FAsyncMessageId::Invalid
- L69 _public function_ `bool operator==(const FAsyncMessageId& Other) const`
- L74 _public function_ `bool operator!=(const FAsyncMessageId& Other) const`
- L88 _public member_ `static const FAsyncMessageId Invalid;` — Represents an invalid message ID which cannot be bound to.
- L96 _public prototype_ `static void WalkMessageHierarchy(const FAsyncMessageId StartingMessage, TFunctionRef<void(const FAsyncMessageId MessageId)> ForEachMessageFunc);` — Walks up the parent heirarchy of the given Startingmessage. This will iterate up the parent message chain and calling the given ForEachMessageFunc for it so long as it is valid. This does include the given starting message!
- L104 _protected member_ `FGameplayTag InternalMessageTag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Messages")` — The FName which represents this async message ID

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`
- L79 _function_ `friend inline uint32 GetTypeHash(const FAsyncMessageId& InMessageId)`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageStore.h` (Public)


#### class `FAsyncMessageStore`  
`class FAsyncMessageStore final`  
_L19-108_
- desc: Implementation for the actual storage of async messages for different binding methods. This will store a message queue for each type of supports Binding option for listeners, allowing listeners to be in control over when they receive messages from the queue (what tick group, thread ID, etc).
- L22 _public prototype_ `FAsyncMessageStore() = default;`
- L23 _public prototype_ `~FAsyncMessageStore() = default;`
- L29 _public prototype_ `uint32 EnqueueMessage(FAsyncMessage&& MessageToQueue, OUT TArray<FAsyncMessageBindingOptions>& BindingTypesAddedTo);`
- L31 _public prototype_ `[[nodiscard]] TOptional<FAsyncMessage> GetNextMessageForBindingOption(const FAsyncMessageBindingOptions& Binding);`
- L33 _public prototype_ `void AddMessageToBinding(const FAsyncMessageId& MessageId, const FAsyncMessageBindingOptions& Binding);`
- L39 _public prototype_ `bool RemoveMessageFromBinding(const FAsyncMessageId& MessageId, const FAsyncMessageBindingOptions& Binding);` — Removes the given message ID from the specified message binding. This is called when an message handler is unbound
- L46 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Adds references to objects stored in the message queue to the GC collection This will include the FInstancedStruct payload data on the message queue to prevent objects from being destroyed if they are referenced in a message paylod.
- L54 _protected member_ `mutable FCriticalSection MessageQueueCriticalSection;` — CS for when access to the MessageBindingQueues is required to enqueue or dequeue messages accordingly.
- L84 _protected member_ `TMap<FAsyncMessageBindingOptions, FBindingOptionsMessageQueue> MessageBindingQueues;` — Tracks the binding options to their associated message queues. Each binding option needs its own message queue so that we can enable the listeners of the messages to control _when_ they receive an message during the frame.
- L91 _protected member_ `std::atomic<uint32> NextDebugMessageId = 1u;` — Unique ID assigned to a message if we are recording its queue callstack. 0 would be an invalid message id.
- L98 _protected prototype_ `uint32 CreateDebugMessageData();` — Creates and adds a debug messsage to the MessageDebugCallstacks map. Records the current native and BP/script callstacks @return Debug message Id which can be used to look it up in the MessageDebugCallstacks map.
- L106 _protected member_ `TMap<uint32, TTuple<uint32, FAsyncMessage::FMessageDebugData>> MessageDebugCallstacks;` — A map of DebugMessageId's to their associated debug data. The uint32 in the TTuple is the number of remaining message queues to be processed for that message. It is decremented every time the message queue is processed, and when it reaches zero is removed from this map.

#### struct `FAsyncMessageStore::FBindingOptionsMessageQueue`  
`struct FBindingOptionsMessageQueue`  
_L57-76_
- desc: The message queue for a single set of binding options
- L59 _public function_ `FBindingOptionsMessageQueue()`
- L64 _public function_ `~FBindingOptionsMessageQueue()`
- L72 _public member_ `TMap<FAsyncMessageId, uint32> MessagesWithTheseBindings;` — Keep track of what messages are bound within this interface so that we can quickly find which queues require which messages. The value of this map is how many times it has been bound.
- L75 _public member_ `TSharedPtr<TArray<FAsyncMessage>> MessageQueue;` — The queue of messages for this binding option

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageSystemBase.h` (Public)


#### class `FAsyncMessageSystemBase`  
`class FAsyncMessageSystemBase : public TSharedFromThis<FAsyncMessageSystemBase>`  
_L25-335_
- inherits: `TSharedFromThis<FAsyncMessageSystemBase>`
- desc: Base abstract implementation of an async message system which can be used to easily pass signals and messages across different threads in Unreal.
- L37 _public prototype_ `template<class TMessageSystemType, typename... TArgs> [[nodiscard]] static inline TSharedPtr<TMessageSystemType, ESPMode::ThreadSafe> CreateMessageSystem(TArgs&&... Args);` — Creates a new shared pointer to a message system of type TMessageSystemType and calls the "Startup" function on it. Make sure to call the "Shutdown" function on the message system prior to its destruction.
- L39 _public typedef_ `using FMessageCallbackFunc = TFunction<void(const FAsyncMessage&)>;`
- L46 _protected prototype_ `FAsyncMessageSystemBase() = default;` — We have a protected constructor on the message system because you should always use the "CreateMessageSystem" function above to make one. This allows us to ensure the virtual "Startup" function is called.
- L51 _public prototype_ `virtual ~FAsyncMessageSystemBase();`
- L63 _public prototype_ `FAsyncMessageHandle BindListener( const FAsyncMessageId MessageId, FMessageCallbackFunc&& Callback, const FAsyncMessageBindingOptions& Options = {}, TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint = nullptr);` — Binds the given callback to this message so that when an message of type MessageId is broadcast, it will be executed. @param MessageId		The async message to bind to @param Callback		The callback which should be executed when 'MessageId' is broadcast. @param Options		Options describing when the listener would like to receive this callback (what tick group or named async thread) @return Async Message handle which can be used to unbind this listener. If the listener is not unbound, then a weak reference to it will be checked and cleaned up when this message system is shut down. If the listener goes out of scope and the callback function is no longer valid, it will be unbound.
- L83 _public prototype_ `template <typename TOwner = UObject> FAsyncMessageHandle BindListener( const FAsyncMessageId MessageId, TWeakObjectPtr<TOwner> WeakOwnerObject, void(TOwner::* Callback)(const FAsyncMessage&), const FAsyncMessageBindingOptions& Options = {}, TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint = nullptr);` — Binds the given callback to this message so that when an message of type MessageId is broadcast, it will be executed. @param MessageId			The async message to bind to @param WeakOwnerObject	The object that owns the bound listener callback. If this object is not valid at the time this message is called, then nothing will happen (the Callback delegate will not be execute on it) @param Callback			The callback which should be executed when 'MessageId' is broadcast. @param Options		Options describing when the listener would like to receive this callback (what tick group or named async thread) @return Async Message handle which can be used to unbind this listener. If the listener is not unbound, then a weak reference to it will be checked and cleaned up when this message system is shut down. If the listener goes out of scope and the callback function is no longer valid, it will be unbound.
- L104 _public prototype_ `template <typename TOwner> FAsyncMessageHandle BindListener( const FAsyncMessageId MessageId, TWeakPtr<TOwner> WeakObject, void(TOwner::* Callback)(const FAsyncMessage&), const FAsyncMessageBindingOptions& Options = {}, TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint = nullptr);` — Binds the given callback to this message so that when an message of type MessageId is broadcast, it will be executed. @param MessageId		The async message to bind to @param WeakObject	The object that owns the bound listener callback. If this object is not valid at the time this message is called, then nothing will happen (the Callback delegate will not be execute on it) @param Callback		The callback which should be executed when 'MessageId' is broadcast. @param Options		Options describing when the listener would like to receive this callback (what tick group or named async thread) @return Async message handle which can be used to unbind this listener. If the listener is not unbound, then a weak reference to it will be checked and cleaned up when this message system is shut down. If the listener goes out of scope and the callback function is no longer valid, it will be unbound.
- L118 _public prototype_ `void UnbindListener(const FAsyncMessageHandle& HandleToUnbind);` — Unbinds the given listener from its message so that it will no longer receive callbacks when that message is broadcast. Listeners will be marked for unbinding and removed from the listener map the next time that this system is processed.
- L130 _public prototype_ `bool QueueMessageForBroadcast( const FAsyncMessageId MessageId, FConstStructView PayloadData = nullptr, TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint = nullptr);` — Queues the given async message for broadcast the next time that this message system processes its message queue @param MessageId		The message that you would like to queue for broadcasting @param PayloadData	Pointer to the payload data of this message. This payload data will be COPIED to the message queue to to make it safe for listeners on other threads. @return True if this message had an listeners bound to it and it was successfully queued
- L140 _public prototype_ `void ProcessMessageQueueForBinding(const FAsyncMessageBindingOptions& Options);` — Processes all async message on within the queue for the given binding options. @param Options Which async message binding queue to process the messages from.
- L148 _protected prototype_ `void Startup();` — Provides an opportunity for this message system to run any startup logic which it may need to. Utilize this to start any tick groups or other async background tasks which may need to occur.
- L157 _public prototype_ `void Shutdown();` — Manual shutdown of this message system. Once this is called, no more listeners can be bound and no more messages can be queued. Use this to clean up any background work which may need to be done that was created in Startup.
- L159 _public prototype_ `void AddReferencedObjects(class UObject* InReferencer, FReferenceCollector& Collector);`
- L167 _protected prototype_ `virtual void Startup_Impl() = 0;` — Provides an opportunity to run any startup logic that subclasses of this Base message system may need, such as creating tick groups for specific binding options.
- L172 _protected prototype_ `virtual void Shutdown_Impl() = 0;` — Allows you to clean up anything you may need to with which was created during startup.
- L178 _protected prototype_ `[[nodiscard]] virtual bool BindListener_Impl( const FAsyncMessageHandle& HandleToBindTo, const FAsyncMessageId MessageId, FMessageCallbackFunc&& Callback, const FAsyncMessageBindingOptions& Options);` — Handles binding the message callback to the given async message handle. This will return true if the binding was successful and false if it failed for some reason (the message system could be shutting down, the MessageId could be invalid, etc.
- L188 _protected prototype_ `virtual void UnbindListener_Impl(const FAsyncMessageHandle& HandleToUnbind);` — Marks the given handle as ready to be unbound. Enqueues this handle to a queue which will be processed on the next call to ProcessUnbindHandleRequests.
- L195 _protected prototype_ `virtual bool QueueMessageForBroadcast_Impl( const FAsyncMessageId MessageId, FConstStructView PayloadData, TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint);` — Actually queues the message for broadcasting. Note: The payload data provided will be copied to make it safe for listeners on different threads.
- L207 _protected prototype_ `virtual void PostQueueMessage(const FAsyncMessageId MessageId, const TArray<FAsyncMessageBindingOptions>& OptionsBoundTo) = 0;` — Called after an message was queued (from QueueMessageForBroadcast_Impl). This forces child classes of the message system to handle the queuing of messages and kick of some scheduling for actually processing the queues accordingly. @param MessageId			The message which was queued @param OptionsBoundTo	All of the binding options that this message was queued for.
- L215 _protected prototype_ `virtual void ProcessMessageQueueForBinding_Impl(const FAsyncMessageBindingOptions& Options);` — Actual implementation of how we process the message queue. This will dequeue all messages out fo the message store for the given binding type, and broadcast their callbacks for each message and it's heirarhcy. @param Options The binding options which we are currently interested in processing messages for
- L221 _protected prototype_ `virtual void PreProcessMessagesQueue(const FAsyncMessageBindingOptions& Options);` — Allow an opportunity to pre-process any messages or bindings which may have occurred before the actual processing of the message queue
- L226 _protected prototype_ `void ProcessUnbindHandleRequests();` — Unbind any handles which have been flagged for removal in "UnbindListener"
- L233 _protected prototype_ `void ProcessListenersPendingBinding();` — Iterate through the PendingBoundListenerQueue and bind the callback functions as necessary. We need to defer the adding of listeners in order to support binding new listeners in response to an message which is currently being processed (otherwise we would be modifying the listener array as we iterate it)
- L239 _protected prototype_ `[[nodiscard]] FAsyncMessageHandle GenerateNextValidMessageHandle( const FAsyncMessageId ForMessageId, TWeakPtr<FAsyncMessageBindingEndpoint> Endpoint);` — Generates a new async message handle by atomically incrementing the NextMessageHandleId. If the new value of NextMessageHandleId is above the max allowed handle id, it will be wrapped.
- L246 _protected member_ `mutable FCriticalSection MessageListenerMapCS;` — Critical section for when the message listeners map is changed (listeners are bound/unbound)
- L252 _protected member_ `std::atomic<uint32> NextMessageHandleId = FAsyncMessageHandle::InvalidHandleIndex + 1u;` — The message handle which we should use to create next New handles can be created any time that we bind a listener, which can be on any thread
- L262 _protected member_ `std::atomic<uint32> NextMessageSequence = 0;` — The message sequence count. Each time an message is queued, we will increment this. Doing this will allow you to determine if a message was queued for broadcast before or after another of the same type or binding option, which can be useful if you are receiving the same message multiple times on a single frame. This is reset back to zero every time we process a binding in ProcessMessageQueueForBinding_Impl.
- L267 _protected member_ `std::atomic<bool> bIsShuttingDown = false;` — A quick flag to check if this system is in the process of shutting down.
- L273 _protected member_ `TSharedPtr<FAsyncMessageBindingEndpoint> DefaultBindingEndpoint = nullptr;` — The default binding endpoint for this message system. When listeners are bound or messages are queued which do not specify a specific endpoint, this one will be used.
- L279 _protected member_ `FAsyncMessageStore MessageStore;` — Where we store the messages when they are queued for broadcasting and where we can process individual sets of FAsyncMessageBindingOptions for their messages
- L306 _protected member_ `TMpscQueue<FPendingBoundListener<FMessageCallbackFunc>> PendingBoundListenerQueue;` — A queue of listeners which are pending to be added. Listeners are added to this queue during FAsyncMessageSystemBase::BindListener_Impl. We do this because otherwise, we would be modifying the array of listeners whilst iterating it, which would cause an error as well as some undefined behavior if you bind another object to the same message.
- L312 _protected member_ `TMpscQueue<FAsyncMessageHandle> MessageHandlesPendingRemoval;` — message handles that are currently queued for removal. Handles get added to this queue by UnbindListener_Impl, and the queue is processed in PreProcessMessagesQueue
- L323 _protected member_ `TSet<FAsyncMessageHandle> IncompleteBoundHandlesToRemove;` — A set of handles which have been marked for removal, but their associated listeners have not been fully bound yet (their binding endpoint does not have any data about them yet). Handles in this set will be skipped if they are seen during ProcessListenersPendingBinding, as they have already been marked for removal. This should only be utilized behind the MessageListenerMapCS scope lock
- L330 _public prototype_ `[[nodiscard]] static FAsyncMessageHandle GenerateHandleAtIndex( const uint32 Index, const FAsyncMessageId& ForId, TWeakPtr<FAsyncMessageBindingEndpoint> Endpoint);` — A test-only helper function to quickly create an message handle from an index.
- L342 _function_ `template <class TMessageSystemType, typename ... TArgs> TSharedPtr<TMessageSystemType, ESPMode::ThreadSafe> FAsyncMessageSystemBase::CreateMessageSystem(TArgs&&... Args)`
- L355 _function_ `template <typename TOwner> FAsyncMessageHandle FAsyncMessageSystemBase::BindListener( const FAsyncMessageId MessageId, TWeakObjectPtr<TOwner> WeakOwnerObject, void(TOwner::* Callback)(const FAsyncMessage&), const FAsyncMessageBindingOptions& Options, TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint )`
- L388 _function_ `template <typename TOwner> FAsyncMessageHandle FAsyncMessageSystemBase::BindListener( const FAsyncMessageId MessageId, TWeakPtr<TOwner> WeakObject, void(TOwner::* Callback)(const FAsyncMessage&), const FAsyncMessageBindingOptions& Options, TWeakPtr<FAsyncMessageBindingEndpoint> BindingEndpoint )`

#### struct `FAsyncMessageSystemBase::FPendingBoundListener`  
`template <typename TCallbackFuncSignature> struct FPendingBoundListener`  
_L286-296_
- desc: Stores data about a listener which has been bound but cannot be added at the time of which FAsyncMessageSystemBase::BindListener_Impl would be called, and needs to be deferred.
- L289 _public member_ `const FAsyncMessageId MessageId;` — The message which this listener desires to be bound to
- L292 _public member_ `FAsyncMessageBindingEndpoint::FAsyncMessageIndividualListener<TCallbackFuncSignature> Data;` — The data for this message, populated in FAsyncMessageSystemBase::BindListener_Impl
- L295 _public member_ `FAsyncMessageBindingOptions Options = {};` — Binding options that this listener requires

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`
- L371 _function_ `` (scope `FAsyncMessageSystemBase::BindListener`)

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageSystemLogs.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAsyncMessageSystem, Log, All);`

### `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Public/AsyncMessageWorldSubsystem.h` (Public)


#### class `UAsyncMessageWorldSubsystem`  
`class UAsyncMessageWorldSubsystem : public UWorldSubsystem`  
_L25-81_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType)`
- inherits: `UWorldSubsystem`
- desc: A world subsystem which will create a unique message system per-world and allow for easy access to the message system interface for gameplay code. An example of using the message system like this is: TSharedPtr<FAsyncMessageSystemBase> Sys = UAsyncMessageWorldSubsystem::GetSharedMessageSystem(GetWorld()); Sys->QueueMessageForBroadcast(MessageToQueue, MessagePayloadToQueue);
- L41 _public prototype_ `template<class TMessageSystemType = FAsyncMessageSystemBase> static TSharedPtr<TMessageSystemType> GetSharedMessageSystem(const UWorld* InWorld);` — Static helper function to get the message system for a world. @tparam TMessageSystemType	The type of message system to create, must be a subclass of FAsyncMessageSystemBase @param InWorld				The world to get the message system of @return						Shared pointer to the given world's message system. Null if the given world is invalid.
- L50 _public prototype_ `template<class TMessageSystemType = FAsyncMessageSystemBase> TSharedPtr<TMessageSystemType> GetSharedMessageSystem() const;` — Returns the message system for this world subsystem. @tparam TMessageSystemType	The type of message system to create, must be a subclass of FAsyncMessageSystemBase @return						Shared pointer to this world subsystem's current message system
- L56 _public member_ `TMulticastDelegate<void()> OnShutdownMessageSystem;` — Delegate which is broadcast when this subsystem's message system is shutdown. Can be used to clean up any bindings to this subsystem's message system when the world goes out of scope
- L58 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L62 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L63 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L64 _protected prototype_ `virtual void Deinitialize() override;`
- L69 _protected prototype_ `void InitMessageSystem();` — Creates the MessageSystem for this world subsystem.
- L74 _protected prototype_ `void ShutdownMessageSystem();` — Shutdown and cleans up this worlds message system.
- L80 _protected member_ `TSharedPtr<FAsyncMessageSystemBase, ESPMode::ThreadSafe> MessageSystem = nullptr;` — Instance of the message system for this world subsystem. This shares the lifetime of this subsystem and will be released in ShutdownMessageSystem, upon Deinitialize of this subsystem.
- L88 _function_ `template <class TMessageSystemType> TSharedPtr<TMessageSystemType> UAsyncMessageWorldSubsystem::GetSharedMessageSystem(const UWorld* InWorld)`
- L104 _function_ `template <class TMessageSystemType> TSharedPtr<TMessageSystemType> UAsyncMessageWorldSubsystem::GetSharedMessageSystem() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ASYNCMESSAGESYSTEM_API`
