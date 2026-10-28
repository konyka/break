# Plugins / SceneStateEvent

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent`
- headers: 12; symbols: 91
- symbol kinds: class=7, delegate=1, enum=1, enumerator=1, function=18, macro=4, member=15, namespace=2, prototype=37, struct=5
- PrivateDependencyModuleNames: Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Private/SceneStateEventSubsystem.h` (Private)


#### class `USceneStateEventSubsystem`  
`class USceneStateEventSubsystem : public UEngineSubsystem`  
_L13-32_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L18 _public prototype_ `static USceneStateEventSubsystem* Get();`
- L21 _public prototype_ `void RegisterEventStream(USceneStateEventStream* InEventStream);` — Adds the given event stream to the list of actively registered event streams
- L24 _public prototype_ `void UnregisterEventStream(USceneStateEventStream* InEventStream);` — Removes the given event stream from the list of actively registered event streams
- L27 _public prototype_ `void ForEachEventStream(TFunctionRef<void(USceneStateEventStream*)> InCallable);` — Iterates all valid event streams that are actively registered
- L31 _private member_ `TArray<TObjectPtr<USceneStateEventStream>> EventStreams;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/ISceneStateEventHandlerProvider.h` (Public)


#### class `USceneStateEventHandlerProvider`  
`class USceneStateEventHandlerProvider : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ISceneStateEventHandlerProvider`  
`class ISceneStateEventHandlerProvider`  
_L16-23_
- L22 _public prototype_ `virtual bool FindEventHandlerId(const FSceneStateEventSchemaHandle& InEventSchemaHandle, FGuid& OutHandlerId) const = 0;` — Find the Event Handler for the given Event Schema

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEvent.h` (Public)


#### struct `FSceneStateEvent`  
`struct FSceneStateEvent`  
_L11-42_
- reflection: `USTRUCT()`
- desc: Holds the name and payload data of an Event handled by Scene State
- L17 _public prototype_ `FSceneStateEvent() = default;`
- L19 _public function_ `const FGuid& GetId() const`
- L24 _public function_ `FConstStructView GetDataView() const`
- L29 _public function_ `FStructView GetDataViewMutable()`
- L37 _private member_ `FGuid Id;` — `UPROPERTY(meta=(IgnoreForMemberInitializationTest))` — Id of the Schema that was used to create this Event
- L41 _private member_ `FInstancedStruct Data;` — `UPROPERTY()` — Payload Data of the Event

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventHandler.h` (Public)


#### struct `FSceneStateEventHandler`  
`struct FSceneStateEventHandler`  
_L10-58_
- reflection: `USTRUCT(BlueprintType)`
- L14 _public prototype_ `FSceneStateEventHandler() = default;`
- L20 _public function_ `explicit FSceneStateEventHandler(EForceInit) : HandlerId(FGuid::NewGuid())` — Force init where Id is initialized to a new guid. This is used in TCppStructOps::Construct
- L25 _public function_ `bool operator==(const FSceneStateEventHandler& InOther) const`
- L35 _public function_ `const FGuid& GetHandlerId() const`
- L40 _public function_ `const FSceneStateEventSchemaHandle& GetEventSchemaHandle() const`
- L45 _public function_ `static FName GetSchemaHandlePropertyName()`
- L53 _private member_ `FGuid HandlerId;` — `UPROPERTY(meta=(IgnoreForMemberInitializationTest))` — Unique Identifier for this Handler
- L57 _private member_ `FSceneStateEventSchemaHandle SchemaHandle;` — `UPROPERTY(EditAnywhere, Category="Event")` — Handle to the Schema of the Event

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSceneStateEventHandler> : TStructOpsTypeTraitsBase2<FSceneStateEventHandler>`  
_L61-67_
- inherits: `TStructOpsTypeTraitsBase2<FSceneStateEventHandler>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L64-66_

#### Free symbols / members of external scopes

- L30 _function_ `friend uint32 GetTypeHash(const FSceneStateEventHandler& InEventHandler)`
- L65 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anon22bcc2750103`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventLibrary.h` (Public)


#### class `USceneStateEventLibrary`  
`class USceneStateEventLibrary : public UBlueprintFunctionLibrary`  
_L13-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static bool PushEvent(USceneStateEventStream* InEventStream, FSceneStateEventSchemaHandle InEventSchemaHandle, FInstancedStruct InEventData = FInstancedStruct());` — `UFUNCTION(BlueprintCallable, Category="Scene State|Event", meta=(BlueprintInternalUseOnly="true"))` — Pushes an event to the given event stream @param InEventStream the stream to push the event to @param InEventSchemaHandle handle to the event schema used to create the event @param InEventData the event payload. Must match the event schema struct @return true if the event was pushed successfully, false otherwise
- L36 _public prototype_ `static bool BroadcastEvent(UObject* WorldContextObject, FSceneStateEventSchemaHandle InEventSchemaHandle, FInstancedStruct InEventData = FInstancedStruct());` — `UFUNCTION(BlueprintCallable, Category="Scene State|Event", meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"))` — Broadcasts an event to the every registered event stream within a world. @param WorldContextObject context object to get the world @param InEventSchemaHandle handle to the event schema used to create the event @param InEventData the event payload. Must match the event schema struct @return true if the event was broadcasted successfully, false otherwise
- L45 _public prototype_ `static bool EventDataToStruct(UPARAM(Ref) const FInstancedStruct& InEventData, int32& OutStructValue);` — `UFUNCTION(BlueprintPure, CustomThunk, Category="Scene State|Event", meta=(CustomStructureParam="OutStructValue", BlueprintInternalUseOnly="true"))` — Converts the given event data instanced struct to the wild card if it matches struct types @param InEventData the event data instanced struct to convert @param OutStructValue the returned value (wild card) if it matches in struct with the event data @return true if the conversion succeeeded
- L49 _public prototype_ `static bool FindEvent(UObject* InContextObject, USceneStateEventStream* InEventStream, FSceneStateEventSchemaHandle InEventSchemaHandle, const FString& InEventHandlerId, bool bInCapturedEventsOnly, FInstancedStruct& OutEventData);` — `UFUNCTION(BlueprintPure, Category="Scene State|Event", meta=(BlueprintInternalUseOnly="true"))` — Finds a captured event within an Event Stream with option to look into any pushed event in that stream (not only captured)
- L53 _public prototype_ `static bool HasEvent(UObject* InContextObject, USceneStateEventStream* InEventStream, FSceneStateEventSchemaHandle InEventSchemaHandle, const FString& InEventHandlerId, bool bInCapturedEventsOnly);` — `UFUNCTION(BlueprintPure, Category="Scene State|Event", meta=(BlueprintInternalUseOnly="true"))` — Returns whether an event is present as a captured event (or optionally just pushed) within an Event Stream
- L58 _private prototype_ `static bool TryGetEventHandlerId(UObject* InContextObject, const FSceneStateEventSchemaHandle& InEventSchemaHandle, const FString& InEventHandlerId, FGuid& OutEventHandlerId);`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateEvent, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateEvent, Log, All);`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventSchema.h` (Public)


#### class `USceneStateEventSchemaObject`  
`class USceneStateEventSchemaObject : public UObject`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UObject`
- L20 _public prototype_ `USceneStateEventSchemaObject() = default;`
- L23 _public prototype_ `FSharedStruct CreateEvent(FInstancedStruct&& InEventData) const;` — Creates an event based on this event schema object, ensuring that the event data also matches the event schema struct
- L26 _public prototype_ `virtual void PostInitProperties() override;`
- L30 _public member_ `FGuid Id;` — `UPROPERTY(DuplicateTransient, TextExportTransient, meta=(IgnoreForMemberInitializationTest))`
- L33 _public member_ `FName Name;` — `UPROPERTY()`
- L36 _public member_ `TObjectPtr<UUserDefinedStruct> Struct;` — `UPROPERTY(Instanced)`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventSchemaCollection.h` (Public)


#### class `USceneStateEventSchemaCollection`  
`class USceneStateEventSchemaCollection : public UObject`  
_L12-34_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Scene State Event Schema Collection")`
- inherits: `UObject`
- desc: Holds a collection of Event Schemas to group common event types in one place
- L18 _public prototype_ `USceneStateEventSchemaObject* GetEventSchema(const FGuid& InEventSchemaId) const;` — Gets the event schema matching a given id
- L20 _public function_ `TConstArrayView<USceneStateEventSchemaObject*> GetEventSchemas() const`
- L25 _public function_ `static FName GetEventSchemasName()`
- L33 _private member_ `TArray<TObjectPtr<USceneStateEventSchemaObject>> EventSchemas;` — `UPROPERTY(EditAnywhere, Instanced, Category="Event Schema")` — Event schemas owned by this collection

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventSchemaHandle.h` (Public)


#### struct `FSceneStateEventSchemaHandle`  
`struct FSceneStateEventSchemaHandle`  
_L16-52_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle to an Event Schema
- L21 _public prototype_ `UUserDefinedStruct* GetEventStruct() const;` — Get the struct of the Event Schema. Can be null if it's an event with no parameters
- L24 _public prototype_ `USceneStateEventSchemaObject* GetEventSchema() const;` — Resolves the event schema soft object pointer
- L27 _public prototype_ `FStructView GetDefaultDataView() const;` — Get the default data view of the Event Schema struct. Can be invalid if it's an event with no parameters
- L29 _public function_ `bool operator==(const FSceneStateEventSchemaHandle& InOther) const`
- L34 _public function_ `static FName GetEventSchemaPropertyName()`
- L39 _public function_ `static FName GetEventStructPropertyName()`
- L47 _private member_ `TSoftObjectPtr<USceneStateEventSchemaObject> EventSchema;` — `UPROPERTY(EditAnywhere, Category="Event")` — Soft reference to the event schema
- L51 _private member_ `TSoftObjectPtr<UUserDefinedStruct> EventStruct;` — `UPROPERTY(EditAnywhere, Category="Event")` — Hold a soft reference to the struct within the event schema, if the event schema has a valid struct

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEEVENT_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventStream.h` (Public)


#### class `USceneStateEventStream`  
`class USceneStateEventStream : public UObject`  
_L18-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Holds and keeps track of Events added at Runtime
- L24 _public prototype_ `bool Register();` — Registers the Event Stream to the Event Subsystem to listen to Broadcast Events
- L27 _public prototype_ `void Unregister();` — Registers the Event Stream from the Event Subsystem
- L30 _public prototype_ `void PushEvent(FSharedStruct&& InEvent);` — Pushes a new event into the stream
- L33 _public prototype_ `void PushEvent(const FSharedStruct& InEvent);` — Pushes a new event into the stream
- L36 _public prototype_ `bool ConsumeEventBySchema(const FSceneStateEventSchemaHandle& InEventSchemaHandle);` — Consumes the first (oldest) Event that was pushed that matches the given Schema
- L39 _public prototype_ `const FSceneStateEvent* FindEventBySchema(const FSceneStateEventSchemaHandle& InEventSchemaHandle) const;` — Finds the first (oldest) Event that was pushed that matches the given Schema
- L42 _public prototype_ `FSceneStateEvent* FindCapturedEvent(const FGuid& InHandlerId);` — Finds the event that is captured by the Handler with the given Id
- L45 _public prototype_ `void CaptureEvents(TConstArrayView<FSceneStateEventHandler> InEventHandlers);` — Removes the Events (first/oldest) that match the given Event Handlers and moves them to the Captured Event map
- L48 _public prototype_ `void ResetCapturedEvents(TConstArrayView<FSceneStateEventHandler> InEventHandlers);` — Cleanup the Captured Events that match the given Event Handlers
- L52 _private prototype_ `int32 GetEventIndexBySchema(const FSceneStateEventSchemaHandle& InEventSchemaHandle) const;` — Returns the index of the first event matching the event schema
- L56 _private member_ `TArray<FSharedStruct> Events;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Active Events kept in push order
- L60 _private member_ `TMap<FGuid, FSharedStruct> CapturedEvents;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Map of the Handler Id to the Event it has captured

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENESTATEEVENT_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventTemplate.h` (Public)


#### struct `FSceneStateEventTemplate`  
`struct FSceneStateEventTemplate`  
_L13-50_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines a handle to an event schema and the payload event data to copy to events to push
- L17 _public function_ `const FSceneStateEventSchemaHandle& GetEventSchemaHandle() const`
- L22 _public function_ `const FInstancedStruct& GetEventData() const`
- L29 _public prototype_ `void SyncEventData();` — Syncs the event data to match the event schema struct
- L32 _public function_ `static FName GetEventSchemaHandlePropertyName()`
- L37 _public function_ `static FName GetEventDataPropertyName()`
- L45 _private member_ `FSceneStateEventSchemaHandle EventSchemaHandle;` — `UPROPERTY(EditAnywhere, Category="Event")` — Handle to the event schema to use
- L49 _private member_ `FInstancedStruct EventData;` — `UPROPERTY(EditAnywhere, Category="Event", meta=(StructTypeConst))` — Data initialized to the event schema, if it has a valid event struct

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATEEVENT_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEvent/Public/SceneStateEventUtils.h` (Public)


#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SCENESTATEEVENT_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L25 _prototype_ `bool PushEvent(USceneStateEventStream* InEventStream, const FSceneStateEventSchemaHandle& InEventSchemaHandle, FInstancedStruct&& InEventData);` (scope `UE::SceneState`) — Pushes an event to the given event stream @param InEventStream the stream to push the event to @param InEventSchemaHandle handle to the event schema used to create the event @param InEventData the event payload. Must match the event schema struct @return true if the event was pushed successfully, false otherwise
- L33 _prototype_ `bool PushEvent(USceneStateEventStream* InEventStream, const FSceneStateEventTemplate& InEventTemplate);` (scope `UE::SceneState`) — Pushes an event to the given event stream @param InEventStream the stream to push the event to @param InEventTemplate the template used to create the event @return true if the event was pushed successfully, false otherwise
- L40 _prototype_ `const UWorld* GetContextWorld(const UObject* InObject);` (scope `UE::SceneState`) — Retrieves a context world for a given object. @param InObject the context object to look a context world for @return the context world or GWorld as fallback if no explicit world was found.
- L49 _prototype_ `bool BroadcastEvent(const UObject* InEventContext, const FSceneStateEventSchemaHandle& InEventSchemaHandle, FInstancedStruct&& InEventData);` (scope `UE::SceneState`) — Broadcasts an event to the every registered event stream within a given scope. @param InEventContext required scope to which the event will be broadcasted to. Only Event Streams within this scope will receive the broadcast event. @param InEventSchemaHandle handle to the event schema used to create the event @param InEventData the event payload. Must match the event schema struct @return true if the event was broadcasted successfully, false otherwise
- L57 _prototype_ `bool BroadcastEvent(const UObject* InEventContext, const FSceneStateEventTemplate& InEventTemplate);` (scope `UE::SceneState`) — Broadcasts an event to the every registered event stream within a given scope. @param InEventContext required scope to which the event will be broadcasted to. Only Event Streams within this scope will receive the broadcast event. @param InEventTemplate the template used to create the event @return true if the event was broadcasted successfully, false otherwise
