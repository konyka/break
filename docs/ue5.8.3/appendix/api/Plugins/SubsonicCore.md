# Plugins / SubsonicCore

- module root: `Plugins/Experimental/Subsonic/Source/SubsonicCore`
- headers: 10; symbols: 262
- symbol kinds: class=4, delegate=1, enum=3, enumerator=6, externvar=5, function=34, macro=7, member=31, namespace=27, prototype=125, struct=14, typedef=5
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: AudioMixerCore, Core, GameplayTags, PropertyBindingUtils

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/ISubsonicEventRegistry.h` (Public)


#### class `UE::Subsonic::Core::ISubsonicEventRegistry`  
`class ISubsonicEventRegistry`  
_L21-46_
- desc: Registry interface for events and their associated collections/executors.
- L24 _public prototype_ `virtual ~ISubsonicEventRegistry() = default;`
- L26 _public prototype_ `static ISubsonicEventRegistry* Get();`
- L27 _public prototype_ `static ISubsonicEventRegistry& GetChecked();`
- L29 _public prototype_ `static void Initialize(TUniquePtr<ISubsonicEventRegistry>&& InRegistry);`
- L30 _public prototype_ `static void Deinitialize();`
- L32 _public prototype_ `virtual void OnCollectionRegistered(const FCollectionHandle& InHandle, Audio::FDeviceId DeviceId) = 0;`
- L33 _public prototype_ `virtual void OnCollectionUnregistered(const FCollectionHandle& InHandle, Audio::FDeviceId DeviceId) = 0;`
- L35 _public prototype_ `virtual void OnExecutorRegistered(const FSubsonicExecutor& InExecutor) = 0;`
- L36 _public prototype_ `virtual void OnExecutorUnregistered(const FSubsonicExecutor& InExecutor) = 0;`
- L38 _public prototype_ `virtual void OnEventPreExecute(const FSubsonicExecutor& InExecutor, const FEventHandle& InHandle) = 0;`
- L39 _public prototype_ `virtual void OnEventPostExecute(const FSubsonicExecutor& InExecutor, const FEventHandle& InHandle) = 0;`
- L41 _public prototype_ `virtual void OnEventSubscriberRegistered(ISubsonicEventSubscriberInterface& EventSubscriber) = 0;`
- L42 _public prototype_ `virtual void OnEventSubscriberUnregistered(ISubsonicEventSubscriberInterface& EventSubscriber) = 0;`
- L45 _private member_ `static TUniquePtr<ISubsonicEventRegistry> Instance;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SUBSONICCORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Subsonic` (scope `UE`)
- L10 _namespace_ `namespace Core` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicBindingUtils.h` (Public)


#### enum `UE::Subsonic::Core::BindingUtils::EStaleBindingResponse`  
`enum class EStaleBindingResponse : uint8`  
_L21-26_
- desc: Response returned by OnStaleBindingsDetected to indicate whether to remove all stale bindings (proceeding with the parameter structural change), revert the change, or rebind stale bindings to a renamed parameter (where applicable).
- L23 _public enumerator_ `RemoveBindings`
- L24 _public enumerator_ `Revert`
- L25 _public enumerator_ `Rebind`

#### struct `UE::Subsonic::Core::BindingUtils::FStalePropertyHandle`  
`struct FStalePropertyHandle`  
_L29-36_
- desc: Represents minimal information required to locate a stale binding entry.
- L32 _public member_ `FActionHandle Action;` — Action containing stale binding.
- L35 _public member_ `FName Property;` — Name of property on action that is stale

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SUBSONICCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Subsonic` (scope `UE`)
- L13 _namespace_ `namespace Core` (scope `UE::Subsonic`)
- L15 _namespace_ `namespace BindingUtils` (scope `UE::Subsonic::Core`)
- L39 _typedef_ `using FStaleBindingsMap = TMap<FName, TArray<FStalePropertyHandle>>;` (scope `UE::Subsonic::Core::BindingUtils`) — Map of stale parameter name to action pointing to stale property
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStaleBindingsDetected, const FStaleBindingsMap&, EStaleBindingResponse&);` — Fired when a structural parameter change (type or name change) creates stale editor bindings.
- L42 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStaleBindingsDetected, const FStaleBindingsMap&, EStaleBindingResponse&);` (scope `UE::Subsonic::Core::BindingUtils`) — Fired when a structural parameter change (type or name change) creates stale editor bindings.
- L47 _prototype_ `UE_INTERNAL bool ArePropertiesBindingCompatible(const FProperty* FromBag, const FProperty* ToAction);` (scope `UE::Subsonic::Core::BindingUtils`) — Checks whether a property bag value can be safely copied into a destination (action) property. Uses SameType for exact matching, with a fallback for object properties to allow subclass assignment. Does not currently handle inner-type variance for container properties (TArray, etc.).
- L52 _prototype_ `UE_INTERNAL FName FindRenameCandidate(const FSubsonicEventCollectionDefinition& Definition, FName OldParamName, const TArray<FStalePropertyHandle>& StaleEntries);` (scope `UE::Subsonic::Core::BindingUtils`) — For a stale parameter name, finds a likely rename candidate in the current bags: a parameter with a compatible type that is not already referenced by any existing binding on the affected actions. Returns NAME_None if no unique candidate is found.
- L56 _prototype_ `UE_INTERNAL TMap<FName, TArray<FStalePropertyHandle>> FindStaleBindings(const FSubsonicEventCollectionDefinition& Definition, const FCollectionHandle& ParentHandle);` (scope `UE::Subsonic::Core::BindingUtils`) — Returns map of parameter names to stale binding entries for bindings that are no longer valid (parameter removed or type no longer matches). Checks event-level bags first, then collection-level.
- L61 _prototype_ `UE_INTERNAL void PromptForStaleBindings(const FSubsonicEventCollectionDefinition& Definition, const FStaleBindingsMap& StaleBindings, EStaleBindingResponse& OutResponse);` (scope `UE::Subsonic::Core::BindingUtils`) — Prompts the user to handle stale bindings caused by a parameter rename or removal. Detects rename candidates and shows either a 3-option (rename/remove/revert) or 2-option (remove/revert) dialog. Sets OutResponse accordingly.

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicBuiltInParameters.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Subsonic` (scope `UE`)
- L7 _namespace_ `namespace BuiltInParameters` (scope `UE::Subsonic`)
- L9 _externvar_ `extern const FName Volume;` (scope `UE::Subsonic::BuiltInParameters`)
- L10 _externvar_ `extern const FName PitchShift;` (scope `UE::Subsonic::BuiltInParameters`)
- L11 _externvar_ `extern const FName HighpassCutoff;` (scope `UE::Subsonic::BuiltInParameters`)
- L12 _externvar_ `extern const FName LowpassCutoff;` (scope `UE::Subsonic::BuiltInParameters`)
- L13 _externvar_ `extern const FName FadeOutTime;` (scope `UE::Subsonic::BuiltInParameters`)

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicCoreLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSubsonic, Log, All);`

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicEventCollection.h` (Public)


#### struct `UE::Subsonic::Core::FSubsonicEventActionBoundProperties`  
`struct FSubsonicEventActionBoundProperties`  
_L30-36_
- reflection: `USTRUCT()`
- L35 _public member_ `TArray<FName> Properties;` — `UPROPERTY()`

#### struct `UE::Subsonic::Core::FSubsonicEventActionBase`  
`struct FSubsonicEventActionBase`  
_L39-91_
- reflection: `USTRUCT(MinimalAPI, BlueprintType, meta = (Abstract, Hidden))`
- L43 _public prototype_ `virtual ~FSubsonicEventActionBase() = default;`
- L46 _public prototype_ `UE_INTERNAL const TMap<FName, FSubsonicEventActionBoundProperties>& GetBindings() const;`
- L47 _public prototype_ `UE_INTERNAL static FName GetBindingsParameterName();`
- L50 _public prototype_ `static FName GenerateDefaultBaseIdentifier(const FEventHandle& OwnerHandle);` — Computes a reasonable default base identifiable name from the provided owning event handle.
- L54 _public prototype_ `virtual FText GetDisplayInfo() const;` — Returns display info that is custom to the given action instance to be shown adjacent to the action, for example, in the Subsonic Event Editor action tree.
- L58 _public prototype_ `static void InitializeDefaultActionName(TInstancedStruct<FSubsonicEventActionBase>& ActionConfig, const FEventHandle& OwnerHandle);` — Initializes default property names on a newly created action config. Computes a base name from context, then delegates to the virtual InitializeDefaultName.
- L63 _public prototype_ `virtual void InitializeDefaultName(const UScriptStruct* ActionStruct, FName BaseName);` — Virtual hook for per-action-type customization of default property names. Called by InitializeDefaultActionName with the computed base name. Base implementation sets the first FNameProperty named "Name" to BaseName via reflection.
- L69 _public prototype_ `FName GetBoundParameterForProperty(FName PropertyName) const;` — Returns the parameter name that the given action property is currently bound to, or NAME_None if unbound.
- L72 _public prototype_ `void AddPropertyBinding(FName ParameterName, FName PropertyName);` — Binds an action property to a named parameter, replacing any previous binding for that property.
- L76 _public prototype_ `bool RemoveAllPropertyBindingsToParameter(FName ParameterName);` — Removes all property bindings associated with the parameter of the given name. Returns true if binding was found and removed, false if not.
- L79 _public prototype_ `void RemovePropertyBinding(FName PropertyName);` — Removes any binding for the given action property.
- L83 _protected function_ `virtual void Execute(const FSubsonicExecutor& InExecutor, const FActionHandle& InHandle) const`
- L87 _protected member_ `TMap<FName, FSubsonicEventActionBoundProperties> Bindings;` — `UPROPERTY()`

#### struct `UE::Subsonic::Core::FSubsonicEventActionDefinition`  
`struct FSubsonicEventActionDefinition`  
_L95-113_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- desc: Action definition iteratively executed per Subsonic event.
- L99 _public prototype_ `const TInstancedStruct<FSubsonicEventActionBase>& GetAction() const;`
- L102 _public prototype_ `void SetAction(TInstancedStruct<FSubsonicEventActionBase> NewAction);`
- L105 _public prototype_ `UE_INTERNAL FSubsonicEventActionBase* GetMutableActionBase();` — Returns a mutable pointer to the underlying action base, or nullptr if no action is set.
- L112 _private member_ `TInstancedStruct<FSubsonicEventActionBase> Action;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions", meta = (AllowPrivateAccess))`

#### struct `UE::Subsonic::Core::FSubsonicEvent`  
`struct FSubsonicEvent`  
_L116-173_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- L120 _public prototype_ `virtual ~FSubsonicEvent() = default;`
- L123 _public prototype_ `UE_INTERNAL static FName GetActionCollectionPropertyName();`
- L124 _public prototype_ `UE_INTERNAL static FName GetParametersPropertyName();`
- L127 _public prototype_ `const TArray<FSubsonicEventActionDefinition>& GetActionCollection() const;`
- L130 _public prototype_ `const FInstancedPropertyBag& GetParameters() const;`
- L134 _public prototype_ `bool GetAutoAudition() const;`
- L137 _public prototype_ `bool GetIsPublic() const;`
- L140 _public prototype_ `UE_INTERNAL TArray<FSubsonicEventActionDefinition>& GetMutableActionCollection();`
- L141 _public prototype_ `UE_INTERNAL void SetAutoAudition(bool bInAutoAudition);`
- L142 _public prototype_ `UE_INTERNAL void SetIsPublic(bool bInIsPublic);`
- L150 _private prototype_ `UE_INTERNAL void BindParameter(const FInstancedPropertyBag& InSourceParameters, FName Name);`
- L151 _private prototype_ `UE_INTERNAL void UnbindParameter(FName Name);`
- L157 _private prototype_ `UE_INTERNAL void Execute(const FSubsonicExecutor& InExecutor, const FEventHandle& InHandle) const;` — Called by executor, iterates through all actions on the given event definition. Asserts if the provided executor and handle have mismatched collection contexts.
- L160 _private member_ `bool bIsPublic = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event", meta = (AllowPrivateAccess))`
- L165 _private member_ `bool bAutoAudition = false;` — `UPROPERTY(EditAnywhere, Transient, Category = "Event", meta = (EditCondition = bIsPublic))` — If true, execute this event as soon as an audition executor is created.
- L168 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category = "Event")`
- L172 _private member_ `TArray<FSubsonicEventActionDefinition> ActionCollection;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions", meta = (AllowPrivateAccess))`

#### struct `UE::Subsonic::Core::FSubsonicEventCollectionDefinition`  
`struct FSubsonicEventCollectionDefinition final`  
_L177-318_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- L184 _public prototype_ `FSubsonicEventCollectionDefinition() = default;` — Generates empty, invalid event collection. Required to be public to support UObject reflection. To produce a valid definition natively without UObject support, call static Create function below.
- L186 _public prototype_ `FSubsonicEventCollectionDefinition(FSubsonicEventCollectionDefinition&& Definition);`
- L187 _public prototype_ `FSubsonicEventCollectionDefinition(const FSubsonicEventCollectionDefinition& Definition) = delete;`
- L189 _public prototype_ `FSubsonicEventCollectionDefinition& operator=(FSubsonicEventCollectionDefinition&& Definition);`
- L190 _public prototype_ `FSubsonicEventCollectionDefinition& operator=(const FSubsonicEventCollectionDefinition& Definition) = delete;`
- L192 _public prototype_ `~FSubsonicEventCollectionDefinition();`
- L197 _public prototype_ `static FSubsonicEventCollectionDefinition Create(FName Name, TMap<FGameplayTag, FSubsonicEvent> InEvents, Audio::FDeviceId DeviceId);` — Create a collection definition with a valid transient Id for tracking within the Subsonic System. Used to create and register definitions outside of UObject reflection.
- L201 _public prototype_ `UE_INTERNAL FSubsonicEventActionDefinition* AddAction(const FEventHandle& InHandle, int32 InsertIndex = INDEX_NONE);` — Adds action to event with handle if it exists. If insert index set to less than 0 (default), adds to end of collection array.
- L204 _public prototype_ `UE_INTERNAL FSubsonicEvent* AddEvent(const FGameplayTag& InTag = { }, FSubsonicEvent NewEvent = {});` — Adds event with given tag if does not yet exists. Returns pointer to new event if added, null if none added.
- L208 _public prototype_ `UE_INTERNAL void AssignId();` — Assigns a universal CollectionId to the given collection.
- L212 _public prototype_ `UE_INTERNAL bool ClearActions(const FEventHandle& InHandle);` — Clears all actions under the given event
- L215 _public prototype_ `UE_INTERNAL void ClearEvents();` — Removes all events in the given collection.
- L219 _public prototype_ `UE_INTERNAL bool ContainsBinding(FName EventName, FName ParameterName) const;` — Returns true if binding exists with the given parameter name on either the collection or event with the given name, false if not. Also returns false if event with the given name is not found.
- L224 _public prototype_ `UE_INTERNAL BindingUtils::FOnStaleBindingsDetected& GetOnStaleBindingsDetectedDelegate();` — Fired when a structural parameter change creates stale editor bindings. The handler should show appropriate UI and return the desired response. If unbound, stale bindings are removed automatically.
- L227 _public prototype_ `bool ContainsEvent(FName Name) const;`
- L228 _public prototype_ `bool ContainsEvent(const FGameplayTag& EventTag) const;`
- L229 _public prototype_ `bool ContainsEvent(const FEventHandle& InHandle) const;`
- L232 _public prototype_ `const FSubsonicEventActionDefinition* FindAction(const FActionHandle& InHandle) const;` — Returns pointer to action at handle if it exists
- L235 _public prototype_ `const FSubsonicEvent* FindEvent(FName Name) const;` — Returns event with the given name.
- L236 _public prototype_ `const FSubsonicEvent* FindEvent(const FGameplayTag& EventTag) const;`
- L237 _public prototype_ `const FSubsonicEvent* FindEvent(const FEventHandle& InHandle) const;`
- L241 _public prototype_ `UE_INTERNAL FSubsonicEventActionDefinition* FindMutableAction(const FActionHandle& InHandle);` — Returns pointer to action at handle if it exists
- L244 _public prototype_ `UE_INTERNAL FSubsonicEvent* FindMutableEvent(const FEventHandle& InHandle);` — Returns mutable pointer to event at handle if it exists
- L247 _public prototype_ `uint32 GetCollectionId() const;`
- L249 _public prototype_ `const TMap<FGameplayTag, FSubsonicEvent>& GetEvents() const;`
- L252 _public prototype_ `static uint32 GetInvalidId();` — Returns Id of invalid (default constructed or unregistered/reset collection).
- L255 _public prototype_ `static FName GetEventsPropertyName();`
- L256 _public prototype_ `static FName GetParametersPropertyName();`
- L260 _public prototype_ `const FInstancedPropertyBag& GetParameters() const;`
- L263 _public prototype_ `bool IsValid() const;`
- L266 _public prototype_ `UE_INTERNAL void Register(const Core::FCollectionHandle& InHandle, Audio::FDeviceId InDeviceId);` — Register's the given collection with the SubsonicEventRegistry.
- L270 _public prototype_ `UE_INTERNAL bool RemoveAction(const FActionHandle& InHandle);` — Removes action at given handle and returns if successful.
- L273 _public prototype_ `UE_INTERNAL bool RemoveEvent(const FEventHandle& InHandle);` — Removes event at given handle and returns if successful.
- L279 _public prototype_ `UE_INTERNAL bool RemoveStaleBindings(const FCollectionHandle& ParentHandle, bool bPromptRemoval = false);` — Removes all stale property bindings. Defined as stale if type or name of mapped property does not match that of target parameter. If bPromptRemoval is set, delegate is executed enabling editors to prompt user to cancel removal. Returns whether or not removal succeeded.
- L282 _public prototype_ `UE_INTERNAL void BindAllParameters();` — Binds all parameters across all events in the collection.
- L286 _public prototype_ `UE_INTERNAL void Unregister();` — Unregisters collection, leaving it in clear, invalid state.
- L290 _private member_ `BindingUtils::FOnStaleBindingsDetected OnStaleBindingsDetected;`
- L292 _private prototype_ `UE_INTERNAL void BindParameter(FName Parameter);`
- L293 _private prototype_ `UE_INTERNAL void UnbindParameter(FName Parameter);`
- L297 _private prototype_ `UE_INTERNAL bool RemoveAllPropertyBindingsToParameter(FName ParamName);` — Removes all editor bindings to the given parameter name from all actions in all events. Returns whether or not any bindings were removed.
- L306 _private member_ `uint32 CollectionId = INDEX_NONE;` — Unique Collection Id assigned post initialization of struct properties or via static initializer Independent from UObject identifier to allow for transient construction without having to utilize UObject wrapper.
- L309 _private member_ `Audio::FDeviceId DeviceId = INDEX_NONE;` — Device associated with the given event collection
- L312 _private member_ `TMap<FGameplayTag, FSubsonicEvent> Events;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Events", meta = (AllowPrivateAccess))`
- L316 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<UE::Subsonic::Core::FSubsonicEventCollectionDefinition> : public TStructOpsTypeTraitsBase2<UE::Subsonic::Core::FSubsonicEventCollectionDefinition>`  
_L324-328_
- inherits: `TStructOpsTypeTraitsBase2<UE::Subsonic::Core::FSubsonicEventCollectionDefinition>`
- desc: Required to be in global namespace still for UHT compatibility with namespaced Unreal reflected types

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L327-327_

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SUBSONICCORE_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Subsonic` (scope `UE`)
- L20 _namespace_ `namespace Core` (scope `UE::Subsonic`)
- L327 _enumerator_ `enum { WithCopy = false };` (scope `TStructOpsTypeTraits::__anone5db7a4f0103`)

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicEventSubscriberInterface.h` (Public)


#### class `UE::Subsonic::Core::USubsonicEventSubscriberInterface`  
`class USubsonicEventSubscriberInterface : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (DisplayName = "Subsonic Event Subscriber Interface", CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for all subscribers that respond to Subsonic events.

#### class `UE::Subsonic::Core::ISubsonicEventSubscriberInterface`  
`class ISubsonicEventSubscriberInterface : public IInterface`  
_L24-41_
- inherits: `IInterface`
- L29 _public prototype_ `virtual void OnCollectionRegistered(const FCollectionHandle& InCollection);`
- L30 _public prototype_ `virtual void OnCollectionUnregistered(const FCollectionHandle& InCollection);`
- L32 _public prototype_ `virtual void OnEventPreExecute(const FSubsonicExecutor& InExecutor, const FEventHandle& InHandle);`
- L33 _public prototype_ `virtual void OnEventPostExecute(const FSubsonicExecutor& InExecutor, const FEventHandle& InHandle);`
- L35 _public prototype_ `virtual void OnExecutorRegistered(const FSubsonicExecutor& InExecutor);`
- L36 _public prototype_ `virtual void OnExecutorUnregistered(const FSubsonicExecutor& InExecutor);`
- L39 _protected prototype_ `virtual void Register();`
- L40 _protected prototype_ `virtual void Unregister();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SUBSONICCORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Subsonic` (scope `UE`)
- L10 _namespace_ `namespace Core` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicExecutor.h` (Public)


#### enum `ESubsonicExecutionScope`  
`enum class ESubsonicExecutionScope : uint8`  
_L25-29_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `Global`
- L28 _public enumerator_ `Executor`

#### struct `UE::Subsonic::Core::FSubsonicExecutor`  
`struct FSubsonicExecutor final : public TSharedFromThis<FSubsonicExecutor>`  
_L38-97_
- inherits: `TSharedFromThis<FSubsonicExecutor>`
- desc: Execution object that tracks explicit execution context for any caller of events related to a given collection. RAII design that automatically registers and unregisters with the Subsonic Event Registry, and by extension, any implemented and active subscribers. This enables subscribers to track and manage data related to event requests from a given executor instance in a data-oriented fashion.
- L44 _private prototype_ `FSubsonicExecutor();`
- L45 _private prototype_ `FSubsonicExecutor(const FSubsonicExecutor&) = delete;`
- L46 _private prototype_ `FSubsonicExecutor(FSubsonicExecutor&&) = delete;`
- L47 _private prototype_ `FSubsonicExecutor& operator=(const FSubsonicExecutor& InOther) = delete;`
- L48 _private prototype_ `FSubsonicExecutor& operator=(FSubsonicExecutor&& InOther) = delete;`
- L51 _public prototype_ `~FSubsonicExecutor();`
- L60 _public typedef_ `using FCollectionAccessorPtr = TUniquePtr<ICollectionAccessor>;`
- L62 _public prototype_ `static TSharedRef<FSubsonicExecutor> Create(Audio::FDeviceId InDeviceId, FCollectionAccessorPtr&& CollectionPtr);`
- L64 _public prototype_ `bool ExecuteEvent(FName EventName) const;`
- L66 _public prototype_ `static uint32 GetInvalidId();`
- L68 _public prototype_ `const FSubsonicEventCollectionDefinition* GetCollection() const;`
- L69 _public prototype_ `FCollectionHandle GetCollectionHandle() const;`
- L70 _public prototype_ `Audio::FDeviceId GetDeviceId() const;`
- L71 _public prototype_ `uint32 GetId() const;`
- L73 _public prototype_ `bool IsValid() const;`
- L75 _public prototype_ `FString ToString() const;`
- L77 _public prototype_ `void Unregister();`
- L81 _public prototype_ `void SetParameters(FSubsonicParameterStore InParams);` — Sets trigger-time parameters on this executor. Actions will merge these with their authored parameters when Execute() is called. Cleared on Unregister().
- L84 _public prototype_ `const FSubsonicParameterStore& GetParameters() const;` — Returns the current trigger-time parameter store.
- L87 _private prototype_ `void Register();`
- L89 _private member_ `FCollectionAccessorPtr CollectionAccessor;`
- L91 _private member_ `Audio::FDeviceId DeviceId;`
- L93 _private member_ `uint32 ExecutorId = GetInvalidId();`
- L96 _private member_ `FSubsonicParameterStore Parameters;` — Trigger-time parameters stored here before ExecuteEvent is called.

#### struct `UE::Subsonic::Core::FSubsonicExecutor::ICollectionAccessor`  
`struct ICollectionAccessor`  
_L53-59_
- L55 _public prototype_ `virtual ~ICollectionAccessor() = default;`
- L57 _public prototype_ `virtual const FSubsonicEventCollectionDefinition* GetDefinition() const = 0;`
- L58 _public prototype_ `virtual FCollectionHandle GetHandle() const = 0;`

#### struct `UE::Subsonic::Core::FExecutorScopeKey`  
`struct FExecutorScopeKey`  
_L102-139_
- desc: Key consisting of executor ID and Audio DeviceId (holds CollectionHandle in builds with logging enabled for debugging). Provides easily readable, hashable key while not providing direct executor ccess, enabling subscribers to organize data based in hashed executor scope related to execution context.
- L104 _public member_ `uint32 ExecutorId = FSubsonicExecutor::GetInvalidId();`
- L105 _public member_ `Audio::FDeviceId DeviceId = INDEX_NONE;`
- L108 _public member_ `FCollectionHandle CollectionHandle;`
- L111 _public prototype_ `FExecutorScopeKey() = default;`
- L112 _public function_ `FExecutorScopeKey(const FSubsonicExecutor& InExecutor) : ExecutorId(InExecutor.GetId()) , DeviceId(InExecutor.GetDeviceId()) #if !NO_LOGGING , CollectionHandle(InExecutor.GetCollectionHandle()) #endif`
- L131 _public function_ `FString ToString() const`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API SUBSONICCORE_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Subsonic` (scope `UE`)
- L32 _namespace_ `namespace Core` (scope `UE::Subsonic`)
- L121 _function_ `friend uint32 GetTypeHash(const FExecutorScopeKey& Key)` (scope `UE::Subsonic::Core`)
- L126 _function_ `friend bool operator==(const FExecutorScopeKey& A, const FExecutorScopeKey& B)` (scope `UE::Subsonic::Core`)

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicHandles.h` (Public)


#### struct `UE::Subsonic::Core::FCollectionHandle`  
`struct FCollectionHandle`  
_L18-42_
- L22 _public member_ `FName CollectionName;` — Owning Collection definition's name (for action initialization and logging/debugging)
- L26 _public prototype_ `static uint32 GetInvalidId();` — Returns invalid Id of a handle
- L29 _public member_ `uint32 CollectionId = GetInvalidId();` — Owning Collection's instance id
- L41 _public prototype_ `FString ToString() const;`

#### struct `UE::Subsonic::Core::FEventHandle`  
`struct FEventHandle`  
_L44-63_
- L47 _public member_ `FCollectionHandle Collection;` — Parent collection handle
- L50 _public member_ `FName EventName;` — Owning event name
- L62 _public prototype_ `FString ToString() const;`

#### struct `UE::Subsonic::Core::FActionHandle`  
`struct FActionHandle`  
_L65-84_
- L68 _public member_ `FEventHandle Event;` — Parent event handle
- L71 _public member_ `int32 Index = INDEX_NONE;` — Owning action's index within a given event
- L83 _public prototype_ `FString ToString() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SUBSONICCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Subsonic` (scope `UE`)
- L12 _namespace_ `namespace Core` (scope `UE::Subsonic`)
- L31 _function_ `friend uint32 GetTypeHash(const FCollectionHandle& Handle)` (scope `UE::Subsonic::Core`)
- L36 _function_ `friend bool operator==(const FCollectionHandle& A, const FCollectionHandle& B)` (scope `UE::Subsonic::Core`)
- L52 _function_ `friend uint32 GetTypeHash(const FEventHandle& Handle)` (scope `UE::Subsonic::Core`)
- L57 _function_ `friend bool operator==(const FEventHandle& A, const FEventHandle& B)` (scope `UE::Subsonic::Core`)
- L73 _function_ `friend uint32 GetTypeHash(const FActionHandle& Handle)` (scope `UE::Subsonic::Core`)
- L78 _function_ `friend bool operator==(const FActionHandle& A, const FActionHandle& B)` (scope `UE::Subsonic::Core`)

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicParameterStore.h` (Public)


#### struct `UE::Subsonic::FSubsonicParameterStore`  
`struct FSubsonicParameterStore`  
_L17-32_
- reflection: `USTRUCT(BlueprintType)`
- desc: A parameter store for Subsonic runtime parameters, backed by an FInstancedPropertyBag. Priority layers (lowest to highest): Authored < TriggerTime < Runtime.
- L21 _public prototype_ `bool HasParameter(FName Name) const;`
- L22 _public prototype_ `void RemoveParameter(FName Name);`
- L23 _public prototype_ `void Reset();`
- L24 _public prototype_ `bool IsEmpty() const;`
- L28 _public prototype_ `void MergeFrom(const FSubsonicParameterStore& Other);` — Overlay: properties in Other are added to this store and their values overwrite any existing values with the same name.
- L31 _public member_ `FInstancedPropertyBag Bag;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SUBSONICCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicCore/Public/SubsonicSubscriberDataStore.h` (Public)


#### class `UE::Subsonic::Core::TSubscriberDataStore`  
`template <typename DataType> class TSubscriberDataStore`  
_L15-182_
- desc: Generalized scope- and executor-keyed data store. Stores a DataType instance per scope level (Global, Executor) and provides convenience accessors, executor tracking, and iteration.
- L18 _private typedef_ `using FDataMap = TMap<FName, DataType>;`
- L19 _private typedef_ `using FNameDataPair = TPair<FName, DataType>;`
- L20 _private typedef_ `using FKeyDataMapPair = TPair<FExecutorScopeKey, FDataMap>;`
- L22 _private member_ `FDataMap GlobalStore;`
- L23 _private member_ `TMap<FExecutorScopeKey, FDataMap> ExecutorDataStore;`
- L27 _public function_ `void Empty()` — Empties all scoped stores
- L35 _public function_ `void Empty(TFunctionRef<void(FName, DataType&)> ReleaseFunc)` — Empties all scoped stores, running the provided release function on all data values prior to destruction.
- L48 _public function_ `DataType* Find(FName GlobalName)` — Finds associated data with a given global identifier
- L54 _public function_ `const DataType* Find(FName GlobalName) const` — Finds data associated with a given global identifier
- L60 _public function_ `DataType* Find(const FExecutorScopeKey& Key, FName Name)` — Finds data associated with a given executor and name
- L71 _public function_ `const DataType* Find(const FExecutorScopeKey& Key, FName Name) const` — Finds data associated with a given executor and name
- L83 _public function_ `DataType& FindOrAdd(FName Name)` — Finds or adds data associated with a given global identifier
- L89 _public function_ `DataType& FindOrAdd(const FExecutorScopeKey& Key, FName Name)` — Finds or adds data associated with a given executor & name.
- L96 _public function_ `void ForEach(const FExecutorScopeKey& InKey, TFunctionRef<void(FName, DataType&)> InFunc)` — Iterate on all data values associated with the given key with all names.
- L106 _public function_ `void ForEach(const FExecutorScopeKey& InKey, TFunctionRef<void(FName, DataType&)> InFunc) const` — Iterate on all data values associated with the given key with all names.
- L116 _public function_ `void ForEach(TFunctionRef<void(const FExecutorScopeKey&, const FName&, DataType&)> InFunc)` — Iterate on all executor-scoped data maps with their associated keys.
- L129 _public function_ `void ForEach(TFunctionRef<void(const FExecutorScopeKey&, const FName&, const DataType&)> InFunc) const` — Iterate on all executor-scoped data with their associated keys.
- L142 _public function_ `void ForEach(TFunctionRef<void(FName, DataType&)> InFunc)` — Iterate on all values at global scope with all names.
- L149 _public function_ `void ForEach(TFunctionRef<void(FName, const DataType&)> InFunc) const` — Iterate on all values at global scope with all names.
- L156 _public function_ `int32 Remove(FName Name)` — Removes the named data at the global scope level.
- L162 _public function_ `int32 Remove(const FExecutorScopeKey& Key, FName Name)` — Removes data associated with the given name at the executor scope level.
- L178 _public function_ `int32 Remove(const FExecutorScopeKey& Key)` — Removes all named data at the executor scope level.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Subsonic` (scope `UE`)
- L10 _namespace_ `namespace Core` (scope `UE::Subsonic`)
- L40 _function_ `` (scope `UE::Subsonic::Core::TSubscriberDataStore::Empty`)
- L100 _function_ `auto FuncOnValues = [&InFunc](FNameDataPair& Pair)` (scope `UE::Subsonic::Core::TSubscriberDataStore::ForEach`)
- L110 _function_ `auto FuncOnValues = [&InFunc](const FNameDataPair& Pair)` (scope `UE::Subsonic::Core::TSubscriberDataStore::ForEach`)
- L119 _function_ `` (scope `UE::Subsonic::Core::TSubscriberDataStore::ForEach`)
- L121 _function_ `` (scope `UE::Subsonic::Core::TSubscriberDataStore::ForEach::__anon0949b5fc0402`)
- L134 _function_ `` (scope `UE::Subsonic::Core::TSubscriberDataStore::ForEach::__anon0949b5fc0602`)
