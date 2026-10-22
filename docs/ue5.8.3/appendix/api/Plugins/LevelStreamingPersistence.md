# Plugins / LevelStreamingPersistence

- module root: `Plugins/Runtime/LevelStreamingPersistence/Source/LevelStreamingPersistence`
- headers: 5; symbols: 218
- symbol kinds: class=4, delegate=8, enum=1, enumerator=3, function=36, member=62, prototype=94, struct=9, typedef=1
- PrivateDependencyModuleNames: DeveloperSettings, PropertyPath
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/LevelStreamingPersistence/Source/LevelStreamingPersistence/Public/LevelStreamingPersistenceLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLevelStreamingPersistence, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLevelStreamingPersistence, Log, All);`

### `Plugins/Runtime/LevelStreamingPersistence/Source/LevelStreamingPersistence/Public/LevelStreamingPersistenceManager.h` (Public)


#### struct `FLevelStreamingPersistentObjectPrivateProperties`  
`struct FLevelStreamingPersistentObjectPrivateProperties`  
_L21-41_
- L23 _public prototype_ `FLevelStreamingPersistentObjectPrivateProperties() = default;`
- L24 _public prototype_ `FLevelStreamingPersistentObjectPrivateProperties(FLevelStreamingPersistentObjectPrivateProperties&& Other);`
- L27 _public member_ `FLevelStreamingPersistentObjectPropertyBag Snapshot;` — Initial snapshot used detect changed properties
- L30 _public member_ `FString SourceClassPathName;` — Object source class
- L32 _public member_ `TArray<uint8> PayloadData;` — Payload data containing serialized changed properties
- L34 _public member_ `TArray<const FProperty*> PersistentProperties;` — Persistent Properties
- L36 _public function_ `const UClass* GetSourceClass() const`
- L37 _public prototype_ `void ForEachPersistentProperty(TFunctionRef<void(const FProperty*)> Func) const;`
- L38 _public prototype_ `bool Sanitize(const ULevelStreamingPersistenceManager& InManager);`
- L39 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FLevelStreamingPersistentObjectPublicProperties`  
`struct FLevelStreamingPersistentObjectPublicProperties`  
_L43-63_
- L45 _public prototype_ `FLevelStreamingPersistentObjectPublicProperties() = default;`
- L46 _public prototype_ `FLevelStreamingPersistentObjectPublicProperties(FLevelStreamingPersistentObjectPublicProperties&& Other);`
- L49 _public member_ `TArray<const FProperty*> PropertiesToPersist;` — Properties to persist (computed once)
- L52 _public member_ `FString SourceClassPathName;` — Object source class
- L54 _public member_ `FLevelStreamingPersistentObjectPropertyBag PropertyBag;` — Public properties
- L56 _public member_ `TArray<const FProperty*> PersistentProperties;` — Persistent Properties
- L58 _public function_ `const UClass* GetSourceClass() const`
- L59 _public prototype_ `void ForEachPersistentProperty(TFunctionRef<void(const FProperty*)> Func) const;`
- L60 _public prototype_ `bool Sanitize(const ULevelStreamingPersistenceManager& InManager);`
- L61 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FRuntimeSpawnedActorSubobjectRecord`  
`struct FRuntimeSpawnedActorSubobjectRecord`  
_L65-76_
- L68 _public member_ `FString RelativePathName;` — Path from subobject to owning actor
- L70 _public member_ `FLevelStreamingPersistentObjectPrivateProperties PrivateProperties;` — Private properties (diff from subobject archetype)
- L72 _public member_ `FLevelStreamingPersistentObjectPublicProperties PublicProperties;` — Public properties (property bag)
- L74 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FRuntimeSpawnedActorRecord`  
`struct FRuntimeSpawnedActorRecord`  
_L78-93_
- L81 _public member_ `FString ClassPathName;` — Class to respawn
- L83 _public member_ `FTransform Transform;` — Transform relative to the owning level to spawn at
- L85 _public member_ `FLevelStreamingPersistentObjectPrivateProperties PrivateProperties;` — Private properties (diff from CDO baseline)
- L87 _public member_ `FLevelStreamingPersistentObjectPublicProperties PublicProperties;` — Public properties (property bag)
- L89 _public member_ `TArray<FRuntimeSpawnedActorSubobjectRecord> Subobjects;` — Records of default subobjects outered to this actor that have configured persistent properties
- L91 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FLevelStreamingPersistentPropertyValues`  
`struct FLevelStreamingPersistentPropertyValues`  
_L96-115_
- desc: Persistence values for a specific level
- L98 _public member_ `bool bIsMakingVisibleCacheValid = false;`
- L101 _public member_ `TWeakObjectPtr<ULevel> LastKnownLevel;` — Not serialized. Used to determine whether a level that's being made visible is becoming visible for the first time or not, i.e. is the level reused, or GCed and newly loaded.
- L102 _public member_ `TMap<FString, FLevelStreamingPersistentObjectPrivateProperties> ObjectsPrivatePropertyValues;`
- L103 _public member_ `TMap<FString, FLevelStreamingPersistentObjectPublicProperties> ObjectsPublicPropertyValues;`
- L109 _public member_ `TSet<FName> RemovedMapActors;` — FNames of map-placed actors removed from this level during gameplay. On load, matching actors are destroyed before BeginPlay. Which actor classes are tracked when destroyed is configured via LevelStreamingPersistenceSettings. Note that RemovedMapActors is built up from multiple events: map actors that were destroyed, and map actors marked for removal via features like EjectPlacedActor, RecreateActorInPersistentLevel.
- L111 _public member_ `TArray<FRuntimeSpawnedActorRecord> RuntimeSpawnedActors;` — Records of non-placed actors that were present when the level was saved, and that are configured to be respawnable in LevelStreamingPersistenceSettings.
- L113 _public prototype_ `void Serialize(FArchive& Ar);`

#### class `ULevelStreamingPersistentPropertiesInfo`  
`class ULevelStreamingPersistentPropertiesInfo : public UObject`  
_L119-162_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Helper class to access FLevelStreamingPersistentProperty's Properties
- L124 _public prototype_ `void Initialize();`
- L125 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L148 _public prototype_ `const UPropertyBag* GetPropertyBagFromClass(EPropertyType InAccessSpecifier, const UClass* InClass) const;` — Configurable persistent properties helper methods
- L149 _public prototype_ `void ForEachProperty(EPropertyType InAccessSpecifier, const UClass* InClass, TFunctionRef<void(FProperty*)> Func) const;`
- L150 _public prototype_ `bool HasProperties(EPropertyType InAccessSpecifier, const UClass* InClass) const;`
- L151 _public prototype_ `bool HasProperty(EPropertyType InAccessSpecifier, const FProperty* InProperty) const;`
- L154 _public prototype_ `bool SatisfiesFilters(EPropertyType InAccessSpecifier, const FProperty* InProperty, const UObject* InObject) const;` — Returns whether InObject satisfies the configured ObjectClassFilter and OuterClassFilter for InProperty.
- L158 _private member_ `TStaticArray<TMap<TObjectPtr<const UClass>, TSet<FProperty*>>, PropertyType_Count> ClassesProperties;` — Acceleration maps to find properties for a given class
- L159 _private member_ `TStaticArray<TMap<const UClass*, FInstancedPropertyBag>, PropertyType_Count> ObjectClassToPropertyBag;`
- L161 _private member_ `TStaticArray<TMap<FProperty*, FPropertyFilters>, PropertyType_Count> PropertyFiltersMap;` — Per-property object and outer class filters

#### enum `ULevelStreamingPersistentPropertiesInfo::EPropertyType`  
`enum EPropertyType`  
_L127-132_
- L129 _public enumerator_ `PropertyType_Public`
- L130 _public enumerator_ `PropertyType_Private`
- L131 _public enumerator_ `PropertyType_Count`

#### struct `ULevelStreamingPersistentPropertiesInfo::FPropertyFilters`  
`struct FPropertyFilters`  
_L136-145_
- desc: Per-property object/outer class filters, stored as soft paths to avoid loading classes at init time. Evaluation walks the class hierarchy and compares FSoftClassPath(Class) against each entry.
- L139 _public member_ `TArray<FSoftClassPath> ObjectClassFilter;` — If non-empty: only persist on objects that are, or derive from, any of these classes.
- L141 _public member_ `TArray<FSoftClassPath> OuterClassFilter;` — If non-empty: only persist on objects whose Outer is, or derives from, any of these classes.
- L143 _public function_ `bool IsEmpty() const`
- L144 _public prototype_ `bool PassesFilters(const UObject* Object) const;`

#### class `ULevelStreamingPersistenceManager`  
`class ULevelStreamingPersistenceManager : public UWorldSubsystem`  
_L165-347_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- L171 _public prototype_ `ULevelStreamingPersistenceManager(const FObjectInitializer&);`
- L172 _public function_ `~ULevelStreamingPersistenceManager()`
- L173 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L174 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L175 _public prototype_ `virtual void Deinitialize() override;`
- L184 _public prototype_ `bool SerializeTo(TArray<uint8>& OutPayload, const bool bForceUpdate = false);` — `UFUNCTION(BlueprintCallable, Category = "Level Streaming Persistence")` — Serialize the persistent properties of all streaming levels of the current map to byte array. This can be put in a SaveGame's property to save to file. @param OutPayload Byte array containing saved values for all streaming levels of the current map, and persistent level if enabled. @param bForceUpdate If true, will iterate all visible streaming levels to update their persistence data. Recommended for saving latest world snapshot.
- L198 _public prototype_ `bool InitializeFrom(const TArray<uint8>& InPayload);` — `UFUNCTION(BlueprintCallable, Category = "Level Streaming Persistence")` — Deserialize the persistent properties of all streaming levels of the current map from byte array. The payload should be from an earlier SerializeTo call, from an earlier play session of the same map. Call this only once per map. It's recommended to call this from a custom UWorldSubsystem::Initialize, early enough to restore properties on persistent level actors before they BeginPlay, and before initial streaming levels are made visible. You can also call this post-begin play, which is useful for blueprint only projects. Calling this post-begin play will overwrite properties on actors that have begun play. Currently, only native callbacks are provided: PostRestoreObject and PostRestoreLevel. @param InPayload Byte array containing saved values for all streaming levels of the current map, and persistent level if enabled. Should be from an earlier SerializeTo call, from the same map but earlier play session. @return Whether deserialization succeeded
- L202 _public prototype_ `template <typename ClassType, typename PropertyType> bool SetPropertyValue(const FString& InObjectPathName, const FName InPropertyName, const PropertyType& InPropertyValue);` — Sets property value and creates the entry if necessary, returns true on success.
- L206 _public prototype_ `template <typename PropertyType> bool TrySetPropertyValue(const FString& InObjectPathName, const FName InPropertyName, const PropertyType& InPropertyValue);` — Sets the property value on existing entries, returns true on success.
- L210 _public prototype_ `template<typename PropertyType> bool GetPropertyValue(const FString& InObjectPathName, const FName InPropertyName, PropertyType& OutPropertyValue) const;` — Gets the property value if found, returns true on success.
- L213 _public prototype_ `bool TrySetPropertyValueFromString(const FString& InObjectPathName, const FName InPropertyName, const FString& InPropertyValue);` — Sets the property value converted from the provided string value on existing entries, returns true on success.
- L216 _public prototype_ `bool GetPropertyValueAsString(const FString& InObjectPathName, const FName InPropertyName, FString& OutPropertyValue);` — Gets the property value and converts it to a string if found, returns true on success.
- L226 _public prototype_ `bool EjectPlacedActor(AActor* InActor);` — `UFUNCTION(BlueprintCallable, Category = "Level Streaming Persistence")` — Ejects a map-placed actor: it will be absent on next level reload, but stay alive for the current session. The actor class must be eligible for persistent destruction, see Level Streaming Persistence Settings. Use cases: treat the actor as destroyed while it's alive for animation purposes. The actor becomes eligible for runtime respawning if it passes your other checks, i.e. RuntimeRespawnedActorClasses and OnShouldPersistRuntimeActor. For handing over an actor for runtime respawning, also see RecreateActorInLevel and RecreateActorInPersistentLevel.
- L237 _public prototype_ `AActor* RecreateActorInLevel(AActor* InActor, ULevel* NewOwningLevel);` — `UFUNCTION(BlueprintCallable, Category = "Level Streaming Persistence")` — Captures persistent values for the actor, destroys it and respawns it into another level. Converting a map-placed actor into a runtime respawned one lets it cross boundaries. Deciding the correct method to mitigate visual pop, and restoring references, is left up to the callee. If the actor is map-placed, its class must be configured for persistent destruction. The actor class must be configured to be respawnable. In specific cases such as world already in tear-down, the respawning of the actor may fail while the original actor is still destroyed.
- L245 _public prototype_ `AActor* RecreateActorInPersistentLevel(AActor* InActor);` — `UFUNCTION(BlueprintCallable, Category = "Level Streaming Persistence")` — Calls RecreateActorInLevel passing the persistent level. Used for blueprint exposing the common route of moving an actor to the persistent level. If the actor is map-placed, its class must be configured for persistent destruction. In specific cases such as world already in tear-down, the respawning of the actor may fail while the original actor is still destroyed.
- L248 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const;`
- L252 _private prototype_ `void OnLevelBeginMakingInvisible(UWorld* World, const ULevelStreaming* StreamingLevel, ULevel* LoadedLevel);` — Level streaming visibility callbacks
- L253 _private prototype_ `void OnLevelBeginMakingVisible(UWorld* World, const ULevelStreaming* StreamingLevel, ULevel* LoadedLevel);`
- L256 _private prototype_ `void OnLevelAddedToWorld(ULevel* Level, UWorld* World);` — World callback for when a level has been fully added and made visible (actors have had BeginPlay).
- L259 _private prototype_ `void OnWorldActorsInitialized(const FActorsInitializedParams& Params);` — World callback for when the persistent levels actors are initialized, so persistent properties can be restored on them. Fires before the actors receive BeginPlay.
- L261 _private prototype_ `void OnActorDestroyed(AActor* DestroyedActor);` — World callback for when an actor is destroyed, to track runtime-destroyed actors for persistence.
- L263 _private prototype_ `int32 ReapplyRemovedActors(FLevelStreamingPersistentPropertyValues* LevelProperties, ULevel* InLevel, const bool bMarkAsGarbage);` — Redestroys actors in a level that were marked as removed when the level was previously visible. Will call Destroy on actors in play or MarkAsGarbage for actors outside play.
- L267 _private prototype_ `void BuildRuntimeSpawnedActorRecord(AActor* InActor, FRuntimeSpawnedActorRecord& OutRecord) const;` — Runtime-respawned actor persistence Makes a record of an actor that will be runtime respawned when the owning level gets reloaded. The record contains class, transform, and records for properties and subobjects.
- L269 _private prototype_ `AActor* SpawnActorFromRecord(const FRuntimeSpawnedActorRecord& InRecord, ULevel* InLevel) const;` — Respawns an actor from an actor record.
- L271 _private prototype_ `void PreloadRuntimeSpawnedActorClasses();` — Preloads a list of actor classes for which runtimed spawnable actor records have been deserialized.
- L273 _private prototype_ `int32 RestoreRuntimeSpawnedActors(FLevelStreamingPersistentPropertyValues* LevelProperties, ULevel* InLevel);` — Respawns all actors from actor records on a level properties entry.
- L278 _private prototype_ `void UpdateVisibleLevelsPersistentPropertyValues();` — Iterate all currently visible streaming levels to record the persistent properties of objects. Normally, these values are only updated for a level when it is made invisible. Call this to make sure that the latest gameplay state of all streaming levels, visible and invisible, is stored in the manager. You can then serialize this data, for example for save game purposes, by calling SerializeTo.
- L279 _private prototype_ `void RestoreVisibleLevelsPersistentPropertyValues();`
- L282 _private prototype_ `bool SaveLevelPersistentPropertyValues(const ULevel* InLevel);` — Save persistent properties
- L285 _private prototype_ `bool RestoreLevelPersistentPropertyValues(ULevel* InLevel);` — Restore persistent properties
- L286 _private prototype_ `int32 RestorePrivateProperties(UObject* InObject, const FLevelStreamingPersistentObjectPrivateProperties& InPersistentProperties, TArray<const FProperty*>& OutRestored) const;`
- L287 _private prototype_ `int32 RestorePublicProperties(UObject* InObject, const FLevelStreamingPersistentObjectPublicProperties& InPersistentProperties, TArray<const FProperty*>& OutRestored) const;`
- L290 _private prototype_ `bool BuildSnapshot(const UObject* InObject, FLevelStreamingPersistentObjectPropertyBag& OutSnapshot) const;` — Snapshot of persistent properties
- L291 _private prototype_ `bool DiffWithSnapshot(const UObject* InObject, const FLevelStreamingPersistentObjectPropertyBag& InSnapshot, TArray<const FProperty*>& OutChangedProperties) const;`
- L293 _private function_ `bool IsEnabled() const`
- L294 _private prototype_ `bool SplitObjectPath(const FString& InObjectPathName, FString& OutLevelPathName, FString& OutShortObjectPathName) const;`
- L295 _private prototype_ `const FString GetResolvedObjectPathName(const FString& InObjectPathName) const;`
- L296 _private prototype_ `bool CopyPropertyBagValueToObject(const FLevelStreamingPersistentObjectPropertyBag* InPropertyBag, UObject* InObject, FProperty* InObjectProperty) const;`
- L297 _private prototype_ `TPair<UObject*, FProperty*> GetObjectPropertyPair(const FString& InObjectPathName, const FName InPropertyName) const;`
- L299 _private prototype_ `void DumpContent() const;`
- L301 _private prototype_ `const FLevelStreamingPersistentObjectPropertyBag* GetPropertyBag(const FString& InObjectPathName) const;`
- L302 _private prototype_ `FLevelStreamingPersistentObjectPropertyBag* GetPropertyBag(const FString& InObjectPathName);`
- L303 _private prototype_ `bool SerializeManager(FArchive& Ar);`
- L306 _private prototype_ `template <typename ClassType> FLevelStreamingPersistentObjectPropertyBag* GetOrCreatePropertyBag(const FString& InObjectPathName, const FName InPropertyName);`
- L309 _private member_ `static class FAutoConsoleVariableRef EnableCommand;` — Console commands
- L310 _private member_ `static bool bIsEnabled;`
- L312 _private member_ `static class FAutoConsoleCommand SaveToFileCommand;`
- L313 _private member_ `static class FAutoConsoleCommand LoadFromFileCommand;`
- L314 _private member_ `static class FAutoConsoleCommand DumpContentCommand;`
- L315 _private member_ `static class FAutoConsoleCommand SetPropertyValueCommand;`
- L316 _private member_ `static class FAutoConsoleCommand GetPropertyValueCommand;`
- L320 _private member_ `mutable TMap<FString, FLevelStreamingPersistentPropertyValues> LevelsPropertyValues;` — Per-level Persistent property values
- L323 _private member_ `TSet<FString> LevelsPendingFinishRestore;` — Level paths that have pending destroys and respawns when made visible.
- L327 _private member_ `TSet<FSoftClassPath> RuntimeSpawnedActorClassPaths;` — Set of all class paths required to respawn runtime-spawned actors, populated on save and restored on load. This set is populated regardless of the setting whether to preload or not.
- L330 _private member_ `TArray<TObjectPtr<UClass>> PreloadedRuntimeSpawnedActorClasses;` — `UPROPERTY(Transient)` — Classes kept in memory to ensure they are available for runtime respawning, to avoid sync loads when making streaming levels visible.
- L333 _private member_ `ILevelStreamingPersistenceModule* PersistenceModule = nullptr;` — Persistence Module
- L335 _private member_ `FDelegateHandle ActorDestroyedHandle;`
- L339 _private member_ `TObjectPtr<ULevelStreamingPersistentPropertiesInfo> PersistentPropertiesInfo;` — `UPROPERTY(Transient)` — Persistent Properties Info
- L342 _private member_ `bool bUseTaggedPropertySerialization;` — Whether to use tagget property serialization
- L350 _function_ `template <typename PropertyType> bool ULevelStreamingPersistenceManager::TrySetPropertyValue(const FString& InObjectPathName, const FName InPropertyName, const PropertyType& InPropertyValue)`
- L365 _function_ `template <typename ClassType, typename PropertyType> bool ULevelStreamingPersistenceManager::SetPropertyValue(const FString& InObjectPathName, const FName InPropertyName, const PropertyType& InPropertyValue)`
- L380 _function_ `template<typename PropertyType> bool ULevelStreamingPersistenceManager::GetPropertyValue(const FString& InObjectPathName, const FName InPropertyName, PropertyType& OutPropertyValue) const`
- L388 _function_ `template <typename ClassType> FLevelStreamingPersistentObjectPropertyBag* ULevelStreamingPersistenceManager::GetOrCreatePropertyBag(const FString& InObjectPathName, const FName InPropertyName)`

#### Free symbols / members of external scopes

- L19 _typedef_ `using FLevelStreamingPersistentPropertyArray = TArray<FCustomPropertyListNode, TInlineAllocator<32>>;`
- L407 _function_ `if (ObjectPublicPropertyValues.PropertyBag.Initialize([this, ObjectClass]() { return PersistentPropertiesInfo->GetPropertyBagFromClass(ULevelStreamingPersistentPropertiesInfo::PropertyType_Public, ObjectClass); }))` (scope `ULevelStreamingPersistenceManager::GetOrCreatePropertyBag`)

### `Plugins/Runtime/LevelStreamingPersistence/Source/LevelStreamingPersistence/Public/LevelStreamingPersistenceModule.h` (Public)


#### class `ILevelStreamingPersistenceModule`  
`class ILevelStreamingPersistenceModule : public IModuleInterface`  
_L17-233_
- inherits: `IModuleInterface`
- desc: The public interface to Level Streaming Persistence Module. Contains hooks for native game code to override, to implement custom persistence conditions, and pre-save/post-restore tasks.
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FShouldPersistProperty, const UObject*, const FProperty*);` — Delegate for custom conditions per object class for whether a property should be saved. These conditions have to be met in addition to the property being configured in project settings, and passing the configuration's ObjectClassFilter and OuterClassFilter. Example use case: Only persist USceneComponent::RelativeLocation on root components. See: OnShouldPersistProperty<ClassType> and OnShouldPersistProperty(Class).
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(void, FPostRestorePersistedProperty, const UObject*, const FProperty*);` — Delegate for game logic per object class to run after a property value is restored. See: OnPostRestorePersistedProperty<ClassType> and OnPostRestorePersistedProperty(Class).
- L33 _public prototype_ `DECLARE_DELEGATE_OneParam(FPrePersistObject, const UObject*);` — Delegate for game logic per object class that is ran before the object is saved. Use this to do any custom preparation of serializable properties, like inventory to struct. See: OnPrePersistObject<ClassType> and OnPrePersistObject(Class).
- L38 _public prototype_ `DECLARE_DELEGATE_TwoParams(FPostRestoreObject, const UObject*, const TArray<const FProperty*>&);` — Delegate for game logic per object class that is ran after the object's properties are restored. Use this to do any custom post-restore logic from serializable properties, like struct to runtime inventory. See: OnPostRestoreObject<ClassType> and OnPostRestoreObject(Class).
- L44 _public prototype_ `DECLARE_DELEGATE_OneParam(FPrePersistLevel, const ULevel*);` — Delegate for game logic to run before a level is saved. Use this to do any preparation of serializable properties that relies on scope beyond single objects. For example: data to restore actor cross-references, copying world subsystem and game state data to persistent level actor, etc. See: PrePersistLevel.
- L50 _public prototype_ `DECLARE_DELEGATE_OneParam(FPostRestoreLevel, const ULevel*);` — Delegate for game logic to run after a level's state has been restored, so all the properties on objects within that level has been restored, and saved runtime actors have been respawned. As a usability detail, this delegate is also called when a level is first encountered and didn't have persisted data. This allows game code to treat this moment as 'initial values for level are finalized' (restored or don't need restore). See: PostRestoreLevel.
- L57 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldPersistRuntimeActor, const AActor*);` — Delegate for custom conditions per object class for whether a runtime actor should be saved. The actor has to pass this function in addition to the plugin being configured to treat that actor class as runtime respawnable. Use case: Skip actors that are in their (game specific) death animation See: OnShouldPersistRuntimeActor<ActorClass> and OnShouldPersistRuntimeActor(ActorClass).
- L61 _public function_ `template<typename ClassType> FShouldPersistProperty& OnShouldPersistProperty()` — Game code hook for whether an object's property should be persisted. Is called in addition to ObjectClassFilter and OuterClassFilter.
- L67 _public function_ `FShouldPersistProperty& OnShouldPersistProperty(const UClass* InClass)` — Game code hook for whether an object's property should be persisted. Is called in addition to ObjectClassFilter and OuterClassFilter.
- L74 _public function_ `template<typename ClassType> FShouldPersistRuntimeActor& OnShouldPersistRuntimeActor()` — Game code hook for whether a runtime-spawned actor should be recorded for persistence. Is called in addition to RuntimeRespawnedActorClasses settings.
- L80 _public function_ `FShouldPersistRuntimeActor& OnShouldPersistRuntimeActor(const UClass* InClass)` — Game code hook for whether a runtime-spawned actor should be recorded for persistence. Is called in addition to RuntimeRespawnedActorClasses settings.
- L87 _public function_ `template<typename ClassType> FPostRestorePersistedProperty& OnPostRestorePersistedProperty()` — Game code hook for after an object's property has been restored.
- L93 _public function_ `FPostRestorePersistedProperty& OnPostRestorePersistedProperty(const UClass* InClass)` — Game code hook for after an object's property has been restored.
- L100 _public function_ `template<typename ClassType> FPrePersistObject& OnPrePersistObject()` — Game code hook for before an object will be persisted. Gives an opportunity to do last second conversion of runtime state to serializable properties.
- L106 _public function_ `FPrePersistObject& OnPrePersistObject(const UClass* InClass)` — Game code hook for before an object will be persisted. Gives an opportunity to do last second conversion of runtime state to serializable properties.
- L115 _public function_ `template<typename ClassType> FPostRestoreObject& OnPostRestoreObject()` — Game code hook for after an object's properties are restored. Gives an opportunity to do custom initialization that depends on the restored properties. For map-placed actors and subobjects, if persistence data is initialized on map load the callback is fired before they BeginPlay. For runtime spawned actors, the callback is fired before BeginPlay on native default subobjects, but after BeginPlay on the actor itself and blueprint added (SCS) components.
- L123 _public function_ `FPostRestoreObject& OnPostRestoreObject(const UClass* InClass)` — Game code hook for after an object's properties are restored. Gives an opportunity to do custom initialization that depends on the restored properties. For map-placed actors and subobjects, if persistence data is initialized on map load the callback is fired before they BeginPlay. For runtime spawned actors, the callback is fired before BeginPlay on native default subobjects, but after BeginPlay on the actor itself and blueprint added (SCS) components.
- L129 _public member_ `FPrePersistLevel PrePersistLevel;` — Level-wide hook for before a streaming level will be persisted.
- L131 _public member_ `FPostRestoreLevel PostRestoreLevel;` — Level-wide hook for after a streaming level's state is restored. Gives an opportunity to restore inter-actor relations, after their individual state has been restored.
- L139 _public function_ `static inline ILevelStreamingPersistenceModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L149 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L156 _private function_ `bool ShouldPersistProperty(const UObject* InObject, const FProperty* InProperty) const`
- L171 _private function_ `bool ShouldPersistRuntimeActor(const AActor* InActor) const`
- L186 _private function_ `void PostRestorePersistedProperty(const UObject* InObject, const FProperty* InProperty) const`
- L199 _private member_ `TMap<TWeakObjectPtr<const UClass>, FShouldPersistProperty> ClassShouldPersistProperty;`
- L200 _private member_ `TMap<TWeakObjectPtr<const UClass>, FPostRestorePersistedProperty> ClassPostRestorePersistedProperty;`
- L201 _private member_ `TMap<TWeakObjectPtr<const UClass>, FShouldPersistRuntimeActor> ClassShouldPersistRuntimeActor;`
- L203 _private function_ `void PrePersistObject(const UObject* InObject) const`
- L216 _private function_ `void PostRestoreObject(const UObject* InObject, const TArray<const FProperty*>& RestoredProperties) const`
- L229 _private member_ `TMap<TWeakObjectPtr<const UClass>, FPrePersistObject> ClassPrePersistObject;`
- L230 _private member_ `TMap<TWeakObjectPtr<const UClass>, FPostRestoreObject> ClassPostRestoreObject;`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FShouldPersistProperty, const UObject*, const FProperty*);` — Delegate for custom conditions per object class for whether a property should be saved. These conditions have to be met in addition to the property being configured in project settings, and passing the configuration's ObjectClassFilter and OuterClassFilter. Example use case: Only persist USceneComponent::RelativeLocation on root components. See: OnShouldPersistProperty<ClassType> and OnShouldPersistProperty(Class).
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(void, FPostRestorePersistedProperty, const UObject*, const FProperty*);` — Delegate for game logic per object class to run after a property value is restored. See: OnPostRestorePersistedProperty<ClassType> and OnPostRestorePersistedProperty(Class).
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FPrePersistObject, const UObject*);` — Delegate for game logic per object class that is ran before the object is saved. Use this to do any custom preparation of serializable properties, like inventory to struct. See: OnPrePersistObject<ClassType> and OnPrePersistObject(Class).
- L38 _delegate_ `DECLARE_DELEGATE_TwoParams(FPostRestoreObject, const UObject*, const TArray<const FProperty*>&);` — Delegate for game logic per object class that is ran after the object's properties are restored. Use this to do any custom post-restore logic from serializable properties, like struct to runtime inventory. See: OnPostRestoreObject<ClassType> and OnPostRestoreObject(Class).
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FPrePersistLevel, const ULevel*);` — Delegate for game logic to run before a level is saved. Use this to do any preparation of serializable properties that relies on scope beyond single objects. For example: data to restore actor cross-references, copying world subsystem and game state data to persistent level actor, etc. See: PrePersistLevel.
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FPostRestoreLevel, const ULevel*);` — Delegate for game logic to run after a level's state has been restored, so all the properties on objects within that level has been restored, and saved runtime actors have been respawned. As a usability detail, this delegate is also called when a level is first encountered and didn't have persisted data. This allows game code to treat this moment as 'initial values for level are finalized' (restored or don't need restore). See: PostRestoreLevel.
- L57 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldPersistRuntimeActor, const AActor*);` — Delegate for custom conditions per object class for whether a runtime actor should be saved. The actor has to pass this function in addition to the plugin being configured to treat that actor class as runtime respawnable. Use case: Skip actors that are in their (game specific) death animation See: OnShouldPersistRuntimeActor<ActorClass> and OnShouldPersistRuntimeActor(ActorClass).

### `Plugins/Runtime/LevelStreamingPersistence/Source/LevelStreamingPersistence/Public/LevelStreamingPersistenceSettings.h` (Public)


#### struct `FLevelStreamingPersistentProperty`  
`struct FLevelStreamingPersistentProperty`  
_L14-37_
- reflection: `USTRUCT()`
- L21 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, Category = Persistence, meta = (GetOptions = "ListClassProperties"))` — Name of the class's property. The property must be a direct member of the class and can't be nested. The property should be instance editable to support persistence.
- L25 _public member_ `bool bIsPublic = false;` — `UPROPERTY(EditAnywhere, Category = Persistence)` — Public: Accessible even when unloaded (if initialized).
- L31 _public member_ `TArray<FSoftClassPath> ObjectClassFilter;` — `UPROPERTY(EditAnywhere, Category = Persistence, meta = (AllowedClasses = "/Script/Engine.Actor, /Script/Engine.ActorComponent", AllowAbstract = "true"))` — If non-empty: this property will only be persisted on objects of any of these base classes. These can only be subclasses of the property's owner class. Example use case: only persist SceneComponent::RelativeLocation on UMySceneComponent. For more control, bind to ILevelStreamingPersistenceModule::Get().OnShouldPersistProperty natively.
- L36 _public member_ `TArray<FSoftClassPath> OuterClassFilter;` — `UPROPERTY(EditAnywhere, Category = Persistence, meta = (AllowedClasses = "/Script/Engine.Actor, /Script/Engine.ActorComponent", AllowAbstract = "true"))` — If non-empty: this property will only be persisted on objects with outers of any of these base classes. Example use case: only persist SceneComponent::RelativeLocation on AMyActor. For more control, bind to ILevelStreamingPersistenceModule::Get().OnShouldPersistProperty natively.

#### class `ULevelStreamingPersistenceSettings`  
`class ULevelStreamingPersistenceSettings : public UDeveloperSettings`  
_L40-102_
- reflection: `UCLASS(Config = Engine, DefaultConfig, meta=(DisplayName="Level Streaming Persistence"))`
- inherits: `UDeveloperSettings`
- L45 _public prototype_ `ULevelStreamingPersistenceSettings();`
- L47 _public function_ `FORCEINLINE bool ShouldRuntimeRespawnAnyActor() const`
- L52 _public prototype_ `bool ShouldPersistRuntimeActorClass(TSubclassOf<AActor> Class) const;`
- L54 _public function_ `FORCEINLINE bool ShouldPersistAnyActorDestruction() const`
- L59 _public function_ `FORCEINLINE bool ShouldIncludePersistentLevel() const`
- L60 _public function_ `FORCEINLINE bool CanRemoveActorsBeforeBeginPlay() const`
- L62 _public prototype_ `bool ShouldPersistActorDestruction(const AActor* Actor) const;`
- L67 _private member_ `bool bIncludePersistentLevel = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Persistent Level")` — If true, persistence data is also saved for actors in the persistent level. Off by default for backwards compatibility.
- L72 _private member_ `TArray<FSoftClassPath> RuntimeRespawnedActorClasses;` — `UPROPERTY(Config, EditAnywhere, Category = "Runtime Spawned Actors", meta = (AllowedClasses = "/Script/Engine.Actor"))` — Actor base classes to scan for at level-save time. Runtime-spawned instances of these classes will be recorded and respawned with their properties restored when the level reloads.
- L76 _private member_ `bool bPersistAllActorDestruction = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Destroyed Actors")` — If true, destruction of map actors of any class will be saved, to be destroyed on level reload.
- L79 _private member_ `TArray<FSoftClassPath> PersistedActorDestructionAllowList;` — `UPROPERTY(Config, EditAnywhere, Category = "Destroyed Actors", meta = (AllowedClasses = "/Script/Engine.Actor", EditCondition = "!bPersistAllActorDestruction"))` — If bPersistAllActorDestruction == false: specific actor base classes for map actors whose destruction is saved, to be redestroyed on level reload.
- L83 _private member_ `bool bCanRemoveActorsBeforeBeginPlay = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Destroyed Actors")` — If true, actors can be removed before BeginPlay by marking them as garbage before the level enters play. This can save performance in offline play by avoid the actor beginning, then ending play. In online play, actors are always destroyed after BeginPlay to allow proper net cleanup.
- L88 _private prototype_ `TArray<FString> ListClassProperties();` — `UFUNCTION()` — Populate property dropdown for entries in 'Properties'
- L94 _private member_ `TSet<FSoftClassPath> PropertyOwningClassFilter;` — `UPROPERTY(Config, EditAnywhere, Category = "Persisted Properties", meta = (AllowedClasses = "/Script/Engine.Actor, /Script/Engine.ActorComponent", AllowAbstract = "true"))` — Editor-only: These classes are used to populate the properties dropdown below.
- L99 _private member_ `TArray<FLevelStreamingPersistentProperty> Properties;` — `UPROPERTY(Config, EditAnywhere, Category = "Persisted Properties", DisplayName = "Properties")` — Persistence settings per property. Properties are populated based on PropertyOwningClassFilter.

### `Plugins/Runtime/LevelStreamingPersistence/Source/LevelStreamingPersistence/Public/LevelStreamingPersistentObjectPropertyBag.h` (Public)


#### struct `FLevelStreamingPersistentObjectPropertyBag`  
`struct FLevelStreamingPersistentObjectPropertyBag`  
_L9-50_
- L11 _public prototype_ `FLevelStreamingPersistentObjectPropertyBag() = default;`
- L12 _public prototype_ `FLevelStreamingPersistentObjectPropertyBag(FLevelStreamingPersistentObjectPropertyBag&& InOther);`
- L13 _public prototype_ `bool Initialize(TFunctionRef<const UPropertyBag* ()> InFunc);`
- L14 _public function_ `bool IsValid() const`
- L15 _public function_ `const UPropertyBag* GetPropertyBagStruct() const`
- L16 _public prototype_ `const FProperty* FindPropertyByName(const FName InPropertyName) const;`
- L17 _public prototype_ `const FProperty* CopyPropertyValueFromObject(const UObject* InObject, const FProperty* InObjectProperty);`
- L18 _public prototype_ `const FProperty* CopyPropertyValueFromPropertyBag(const FLevelStreamingPersistentObjectPropertyBag& InPropertyBag, const FProperty* InProperty);`
- L19 _public prototype_ `const FProperty* CopyPropertyValueToObject(UObject* InObject, const FProperty* InObjectProperty) const;`
- L20 _public prototype_ `const FProperty* GetCompatibleProperty(const FProperty* InObjectProperty) const;`
- L21 _public prototype_ `bool ComparePropertyValueWithObject(const UObject* InObject, const FProperty* InObjectProperty, bool& bOutIsIdentical) const;`
- L22 _public prototype_ `void ForEachProperty(TFunctionRef<void(const FProperty*)> Func) const;`
- L23 _public prototype_ `void DumpContent(TFunctionRef<void(const FProperty*, const FString&)> Func, const TArray<const FProperty*>* InDumpProperties = nullptr);`
- L24 _public prototype_ `void Serialize(FArchive& Ar);`
- L28 _public prototype_ `template<typename PropertyType> bool SetPropertyValue(const FName InPropertyName, const PropertyType& InPropertyValue);`
- L31 _public prototype_ `template<typename PropertyType> bool GetPropertyValue(const FName InPropertyName, PropertyType& OutPropertyValue) const;`
- L33 _public prototype_ `bool SetPropertyValueFromString(const FName InPropertyName, const FString& InPropertyValue);`
- L34 _public prototype_ `bool GetPropertyValueAsString(const FName InPropertyName, FString& OutPropertyValueAsString) const;`
- L38 _private prototype_ `template<typename PropertyType> EPropertyBagResult SetValue(const FName InPropertyName, const PropertyType& InPropertyValue);`
- L41 _private prototype_ `template<typename PropertyType> TValueOrError<PropertyType, EPropertyBagResult> GetValue(const FName InPropertyName) const;`
- L44 _private prototype_ `template<typename PropertyType> TValueOrError<PropertyType, EPropertyBagResult> GetValueStruct(const FName InPropertyName) const;`
- L49 _private member_ `FInstancedPropertyBag PropertyBag;`
- L53 _function_ `template<typename PropertyType> TValueOrError<PropertyType, EPropertyBagResult> FLevelStreamingPersistentObjectPropertyBag::GetValueStruct(const FName InPropertyName) const`
- L64 _function_ `template<typename PropertyType> bool FLevelStreamingPersistentObjectPropertyBag::SetPropertyValue(const FName InPropertyName, const PropertyType& InPropertyValue)`
- L79 _function_ `template<typename PropertyType> bool FLevelStreamingPersistentObjectPropertyBag::GetPropertyValue(const FName InPropertyName, PropertyType& OutPropertyValue) const`

#### struct `FLevelStreamingPersistentObjectPropertyBag::TPropertyBagPropertyType`  
`template<typename PropertyType> struct TPropertyBagPropertyType`  
_L47-47_
- L47 _public member_ `template<typename PropertyType> struct TPropertyBagPropertyType { static const EPropertyBagPropertyType Value = EPropertyBagPropertyType::None; };`
