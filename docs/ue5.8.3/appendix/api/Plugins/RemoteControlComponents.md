# Plugins / RemoteControlComponents

- module root: `Plugins/Experimental/RemoteControlComponents/Source/RemoteControlComponents`
- headers: 5; symbols: 117
- symbol kinds: class=3, delegate=2, function=6, member=15, prototype=89, struct=2
- PrivateDependencyModuleNames: Engine, RemoteControlUI, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, RemoteControl

### `Plugins/Experimental/RemoteControlComponents/Source/RemoteControlComponents/Private/RemoteControlComponentsContext.h` (Private)


#### struct `FRemoteControlComponentsContext`  
`struct FRemoteControlComponentsContext`  
_L21-62_
- desc: Remote Control Components Tracking Context: represents a World with a set of Actors which have properties exposed to a specific Preset. It currently works under the assumption that there's a single Preset per World, and that this info is runtime only. Both aspects might change in the future. Context is represented by: - a World - a Remote Control Preset - Tracked Actors with properties exposed to the Preset
- L25 _public prototype_ `FRemoteControlComponentsContext(UWorld* InWorld, URemoteControlPreset* InPreset);` — Create a Remote Control Context by passing a World and a Preset
- L28 _public prototype_ `bool RegisterActor(AActor* InActor);` — Adds an Actor to the list of tracked actors
- L31 _public prototype_ `bool UnregisterActor(AActor* InActor);` — Removes an Actor from the list of tracked actors
- L34 _public prototype_ `bool IsActorRegistered(const AActor* InActor) const;` — Checks if the specified Actor is tracked or not
- L37 _public prototype_ `bool CanRegisterActor(const AActor* InActor) const;` — An Actor can be registered if it has a Remote Control Tracker Component and its World and the World of this context coincide
- L40 _public prototype_ `bool IsValid() const;` — Context is valid if both World and Preset are valid
- L43 _public prototype_ `bool HasTrackedActors() const;` — True if the context currently has registered tracked actors
- L46 _public function_ `TArray<TWeakObjectPtr<AActor>> GetTrackedActors() const` — Get the array of currently tracked actors
- L49 _public prototype_ `UWorld* GetWorld() const;` — Get the World referenced by this context
- L52 _public prototype_ `URemoteControlPreset* GetPreset() const;` — Get the Remote Control Preset referenced by this context
- L55 _private member_ `TWeakObjectPtr<UWorld> WorldWeak;`
- L57 _private member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeak;`
- L59 _private member_ `TArray<TWeakObjectPtr<AActor>> TrackedActors;`
- L61 _private member_ `bool bIsValid = false;`

### `Plugins/Experimental/RemoteControlComponents/Source/RemoteControlComponents/Public/RemoteControlComponentsUtils.h` (Public)


#### class `FRemoteControlComponentsUtils`  
`class FRemoteControlComponentsUtils`  
_L16-99_
- L23 _public prototype_ `static void AddTrackerComponent(const TSet<TWeakObjectPtr<AActor>>& InActors, bool bInShouldTransact = true);` — Add a RemoteControlTrackerComponent to the specified Actors
- L26 _public prototype_ `static void RemoveTrackerComponent(const TSet<TWeakObjectPtr<AActor>>& InActors);` — Removes the RemoteControlTrackerComponent from the specified Actors
- L32 _public prototype_ `static void UnexposeAllProperties(AActor* InActor);` — Unexpose all Tracked Properties of the specified Actor. It will also stop tracking all unexposed properties.
- L40 _public prototype_ `static URemoteControlTrackerComponent* GetTrackerComponent(AActor* InActor, bool bInAddTrackerIfMissing = false);` — Gets the tracker component for the specified Actor. Tracker can be optionally added if missing. @param InActor: the Actor for which we want to retrieve the Tracker Component. Object @param bInAddTrackerIfMissing: if true, function will add a tracker component when one is missing @return The found or created tracker.
- L43 _public prototype_ `static URemoteControlPreset* GetCurrentPreset(const UObject* InObject);` — Gets the Remote Control Preset currently handling the specified Object
- L46 _public prototype_ `static URemoteControlPreset* GetCurrentPreset(const UWorld* InWorld);` — Gets the Remote Control Preset currently handling the specified World
- L49 _public prototype_ `static void RefreshTrackedProperties(AActor* InActor);` — Call this function on any Actor to ensure its exposed RC properties are actually tracked
- L59 _private prototype_ `static TWeakPtr<FRemoteControlProperty> ExposeProperty(URemoteControlPreset* InPreset, UObject* InOwnerObject, const FRCFieldPathInfo& InPathInfo);` — Expose a Property to the specified Preset @param InPreset the Preset where the property should be exposed @param InOwnerObject the object owning the property @param InPathInfo Field Path Info for the desire property @return The exposed property
- L67 _private prototype_ `static void UnexposeProperty(URemoteControlPreset* InPreset, UObject* InOwnerObject, const FRCFieldPathInfo& InPathInfo);` — Unexpose a Property in the specified Preset @param InPreset the Preset where the property is currently exposed @param InOwnerObject the object owning the property @param InPathInfo Field Path Info for the desire property
- L69 _private prototype_ `static TWeakPtr<FRemoteControlProperty> GetExposedProperty(URemoteControlPreset* InPreset, UObject* InOwnerObject, const FRCFieldPathInfo& InPathInfo);`
- L77 _private prototype_ `static FName GetExposedPropertyId(URemoteControlPreset* InPreset, UObject* InOwnerObject, const FRCFieldPathInfo& InPathInfo);` — Returns the field identifier for the exposed property described by the provided arguments. @param InPreset the Preset where the property is currently exposed @param InOwnerObject the object owning the property @param InPathInfo Field Path Info for the desire property
- L86 _private prototype_ `static void SetExposedPropertyId(URemoteControlPreset* InPreset, UObject* InOwnerObject, const FRCFieldPathInfo& InPathInfo, const FName& InPropertyId);` — Sets the field identifier for the exposed property described by the provided arguments. @param InPreset the Preset where the property is currently exposed @param InOwnerObject the object owning the property @param InPathInfo Field Path Info for the desire property @param InPropertyId The new Property Id value to be set
- L88 _private prototype_ `static FGuid GetPropertyGuid(TConstArrayView<UObject*> InOuterObjects, const FProperty* InProperty);`
- L89 _private prototype_ `static FGuid GetPropertyGuid(UObject* InOwnerObject, const FRCFieldPathInfo& InFieldPathInfo);`
- L98 _private prototype_ `static FGuid GetPresetPropertyGuid(URemoteControlPreset* InPreset, UObject* InOwnerObject, const FProperty* InProperty);` — Returns the ID of a property, if exposed in a Preset for the specified Owner Object @param InPreset The Preset containing the exposed Property @param InOwnerObject The Object owning the bound property @param InProperty The property to look for @return the ID of the property

### `Plugins/Experimental/RemoteControlComponents/Source/RemoteControlComponents/Public/RemoteControlTrackerComponent.h` (Public)


#### class `URemoteControlTrackerComponent`  
`class URemoteControlTrackerComponent : public UActorComponent`  
_L19-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- desc: A component keeping track of properties currently exposed to Remote Control. Supports auto-exposing of properties upon duplication. e.g. duplicating an Actor with this component will result in the same properties exposed by Source Actor to be automatically exposed by Duplicate Actor.
- L25 _public prototype_ `URemoteControlPreset* GetCurrentPreset() const;` — Gets the Current Preset this Tracker Component points to
- L28 _public prototype_ `bool HasTrackedProperties() const;` — returns true if Tracker Component has at least one tracked/exposed property
- L31 _public prototype_ `void AddTrackedProperty(const FRCFieldPathInfo& InFieldPathInfo, UObject* InOwnerObject);` — Add the specified property to the list of properties handled by this Tracker Component
- L34 _public prototype_ `void RemoveTrackedProperty(const FRCFieldPathInfo& InFieldPathInfo, UObject* InOwnerObject);` — Remove the specified property from the list of properties handled by this Tracker Component
- L37 _public prototype_ `void ExposeAllProperties();` — Expose all Tracked Properties handled by this component to the current Remote Control Preset
- L43 _public prototype_ `void UnexposeAllProperties();` — Unexpose all Tracked Properties handled by this component from the current Remote Control Preset. It will also stop tracking all unexposed properties.
- L49 _public prototype_ `void RefreshAllPropertyIds();` — Retrieves the Property Id for all the exposed tracked properties from the current Preset (Tracker --> Preset)
- L55 _public prototype_ `void WriteAllPropertyIdsToPreset();` — Writes the Property Id saved in the Tracker Properties onto the exposed properties of the current Preset (Preset --> Tracker)
- L58 _public prototype_ `bool IsTrackingProperty(const FRCFieldPathInfo& InFieldPathInfo, UObject* InOwnerObject) const;` — returns true if Tracker Component is tracking the property for the specified FieldPathInfo and Owner Object
- L61 _public prototype_ `AActor* GetTrackedActor() const;` — Get the Actor owning this Tracker Component
- L65 _protected prototype_ `virtual void OnComponentCreated() override;`
- L66 _protected prototype_ `virtual void OnComponentDestroyed(bool bInDestroyingHierarchy) override;`
- L70 _protected prototype_ `virtual void PostInitProperties() override;`
- L71 _protected prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L72 _protected prototype_ `virtual void PostEditImport() override;`
- L73 _protected prototype_ `virtual void PostLoad() override;`
- L74 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;`
- L76 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L81 _private prototype_ `void RegisterTrackedActor() const;`
- L82 _private prototype_ `void UnregisterTrackedActor() const;`
- L84 _private prototype_ `void OnTrackerDuplicated();`
- L86 _private prototype_ `void RefreshTracker();`
- L87 _private prototype_ `void RefreshExposedProperties();`
- L88 _private prototype_ `void MarkPropertiesForRefresh();`
- L89 _private prototype_ `void CleanupProperties();`
- L91 _private prototype_ `void RegisterPropertyIdChangeDelegate();`
- L92 _private prototype_ `void UnregisterPropertyIdChangeDelegate() const;`
- L93 _private prototype_ `void OnPropertyIdUpdated();`
- L95 _private prototype_ `int32 GetTrackedPropertyIndex(const FRCFieldPathInfo& InFieldPathInfo, UObject* InOwnerObject) const;`
- L98 _private member_ `TArray<FRemoteControlTrackerProperty> TrackedProperties;` — `UPROPERTY()`

### `Plugins/Experimental/RemoteControlComponents/Source/RemoteControlComponents/Public/RemoteControlTrackerProperty.h` (Public)


#### struct `FRemoteControlTrackerProperty`  
`struct FRemoteControlTrackerProperty`  
_L15-94_
- reflection: `USTRUCT()`
- desc: Represents an exposed Remote Control Property tracked by a Remote Control Tracker Component Its Field Path Info and Owner are used to represent the RC Property.
- L20 _public prototype_ `FRemoteControlTrackerProperty();`
- L28 _public prototype_ `FRemoteControlTrackerProperty(const FRCFieldPathInfo& InFieldPathInfo, const TObjectPtr<UObject>& InOwnerObject, bool bInIsExposed = true);` — Creates and initializes a Tracked Property @param InFieldPathInfo: Field Path Info to reach the property @param InOwnerObject: the object owning the Tracked Property @param bInIsExposed: is the property already exposed? Default is true.
- L31 _public prototype_ `bool MatchesParameters(const FRCFieldPathInfo& InFieldPathInfo, const TObjectPtr<UObject>& InOwnerObject) const;` — Checks if this Tracked Property is matching the one described by the specified parameters
- L34 _public prototype_ `URemoteControlPreset* GetPreset() const;` — Returns the Remote Control Preset where this property is or will be exposed
- L37 _public prototype_ `bool IsExposedTo(const URemoteControlPreset* InPreset) const;` — Is the tracked property exposed to the specified Preset?
- L40 _public function_ `bool IsExposed() const` — Is this Tracked Property exposed?
- L43 _public prototype_ `void Expose(URemoteControlPreset* InRemoteControlPreset);` — Expose this Tracked Property to the specified Preset
- L46 _public prototype_ `void Unexpose();` — Unexpose this Tracked Property from its Preset
- L49 _public prototype_ `void ReadPropertyIdFromPreset();` — Retrieves the current Property Id for the currently tracked property
- L52 _public prototype_ `void WritePropertyIdToPreset() const;` — Writes the Property Id saved in this Tracker Property to the tracked property in the Preset
- L58 _public prototype_ `void MarkUnexposed();` — Marks this Tracked Property as not exposed, even if it might be. Useful to force refresh the state of a Tracked Property.
- L61 _public prototype_ `bool IsValid() const;` — Check if this property can still be exposed (internally verifies if Owner Object is valid)
- L63 _public function_ `const FRCFieldPathInfo& GetFieldPathInfo() const`
- L65 _public prototype_ `bool operator==(const FRemoteControlTrackerProperty& Other) const;`
- L67 _public prototype_ `bool operator!=(const FRemoteControlTrackerProperty& Other) const;`
- L73 _private prototype_ `void Resolve() const;` — Resolves the Tracked Property FieldPathInfo with its Owner
- L77 _private member_ `FRCFieldPathInfo FieldPathInfo;` — `UPROPERTY()` — Field Path Info, matching the same one found in the Remote Control Preset
- L81 _private member_ `FName PropertyId = NAME_None;` — `UPROPERTY()` — The Property Id of the exposed property tracked by this Tracker Property
- L85 _private member_ `TWeakObjectPtr<UObject> OwnerObject = nullptr;` — `UPROPERTY()` — Owner of the property handled by this Tracked Component
- L89 _private member_ `bool bIsExposed = false;` — `UPROPERTY()` — Is this Tracked Property exposed?
- L93 _private member_ `TWeakObjectPtr<URemoteControlPreset> CurrentPresetWeak = nullptr;` — `UPROPERTY()` — Caching the current Remote Control Preset

### `Plugins/Experimental/RemoteControlComponents/Source/RemoteControlComponents/Public/Subsystems/RemoteControlComponentsSubsystem.h` (Public)


#### class `URemoteControlComponentsSubsystem`  
`class URemoteControlComponentsSubsystem : public UEngineSubsystem`  
_L18-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- L24 _public prototype_ `static URemoteControlComponentsSubsystem* Get();` — Get this subsystem instance
- L27 _public prototype_ `void RegisterPreset(URemoteControlPreset* InRemoteControlPreset);` — Register the specified Preset, along with the World it resides in.
- L30 _public prototype_ `void UnregisterPreset(URemoteControlPreset* InRemoteControlPreset);` — Unregister the specified Preset
- L33 _public prototype_ `void RegisterTrackedActor(AActor* InActor);` — Marks the specified Actor as a Tracked Actor, so that the Subsystem knows about it
- L36 _public prototype_ `void UnregisterTrackedActor(AActor* InActor);` — Removes the specified Actor from the tracked actors register
- L39 _public prototype_ `bool IsActorTracked(const AActor* InActor) const;` — Checks if the specified Actor is currently being tracked by the subsystem
- L42 _public prototype_ `bool IsPresetRegistered(const URemoteControlPreset* InPreset) const;` — Checks if the specified Preset is currently registered
- L45 _public prototype_ `URemoteControlPreset* GetRegisteredPreset(const UWorld* InWorld) const;` — Returns the Preset currently associated with the specified World
- L48 _public prototype_ `URemoteControlPreset* GetRegisteredPreset(const UObject* InObject) const;` — Returns the Preset currently associated with the specified Object
- L50 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorRegisterStateUpdate, AActor* ) FOnActorRegisterStateUpdate& OnTrackedActorRegistered()`
- L55 _public function_ `FOnActorRegisterStateUpdate& OnTrackedActorUnregistered()` — Fires whenever an actor is unregistered from Tracking
- L57 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivePresetChanged, URemoteControlPreset* ) FOnActivePresetChanged& OnActivePresetChanged()`
- L62 _private member_ `FOnActorRegisterStateUpdate OnTrackedActorRegisteredDelegate;`
- L63 _private member_ `FOnActorRegisterStateUpdate OnTrackedActorUnregisteredDelegate;`
- L64 _private member_ `FOnActivePresetChanged OnActivePresetChangedDelegate;`
- L67 _private prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L68 _private prototype_ `virtual void Deinitialize() override;`
- L71 _private prototype_ `void OnLevelChanged(ULevel* InNewLevel, ULevel* InOldLevel, UWorld* InWorld);`
- L72 _private prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);`
- L73 _private prototype_ `void OnLevelActorDeleted(AActor* InActor);`
- L75 _private prototype_ `void ClearData();`
- L77 _private prototype_ `void OnEntityExposed(URemoteControlPreset* InRemoteControlPreset, const FGuid& InGuid);`
- L78 _private prototype_ `void OnEntityUnexposed(URemoteControlPreset* InRemoteControlPreset, const FGuid& InGuid);`
- L80 _private prototype_ `void CacheActorsToBeTracked(const TSet<TWeakObjectPtr<AActor>>& InActors);`
- L81 _private prototype_ `void RegisterPendingActors(const UWorld* InWorld);`
- L83 _private prototype_ `bool IsRegisteredActor(const AActor* InActor) const;`
- L84 _private prototype_ `bool IsRegisteredTrackedActor(const AActor* InActor) const;`
- L86 _private prototype_ `TSharedPtr<FRemoteControlComponentsContext> GetTrackedActorContext(const UWorld* InWorld) const;`
- L89 _private member_ `TArray<TWeakObjectPtr<AActor>> ActorsPendingRegister;` — Utility container used to store actors for later tracking in case registering doesn't work right away
- L91 _private member_ `TMap<FObjectKey, TSharedPtr<FRemoteControlComponentsContext>> TrackedActorsContextMap;`

#### Free symbols / members of external scopes

- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorRegisterStateUpdate, AActor* ) FOnActorRegisterStateUpdate& OnTrackedActorRegistered() { return OnTrackedActorRegisteredDelegate; } FOnActorRegisterStateUpdate& OnTrackedActorUnregistered() { return OnTrackedActorUnregisteredDelegate; } DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivePresetChanged, URemoteControlPreset* ) FOnActivePresetChanged& OnActivePresetChanged() { return OnActivePresetChangedDelegate; } private: FOnActorRegisterStateUpdate OnTrackedActorRegisteredDelegate;`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivePresetChanged, URemoteControlPreset* ) FOnActivePresetChanged& OnActivePresetChanged() { return OnActivePresetChangedDelegate; } private: FOnActorRegisterStateUpdate OnTrackedActorRegisteredDelegate;`
