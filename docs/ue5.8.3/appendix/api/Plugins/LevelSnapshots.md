# Plugins / LevelSnapshots

- module root: `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots`
- headers: 86; symbols: 1232
- symbol kinds: class=48, delegate=15, enum=15, enumerator=57, externvar=11, function=119, macro=4, member=260, namespace=186, prototype=436, struct=62, typedef=19
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Landscape, LevelSnapshotFilters, Projects, Settings, UnrealEd
- PublicDependencyModuleNames: Core, TraceLog

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/ApplySnapshotToEditorArchive.h` (Private)


#### class `UE::LevelSnapshots::Private::FApplySnapshotToEditorArchive`  
`class FApplySnapshotToEditorArchive : public FSnapshotArchive`  
_L15-89_
- inherits: `FSnapshotArchive`
- desc: For writing data into an editor object.
- L17 _private typedef_ `using Super = FSnapshotArchive;`
- L24 _public prototype_ `static void ApplyToExistingEditorWorldObject( FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, FSnapshotDataCache& Cache, UObject* InOriginalObject, UObject* InDeserializedVersion, const FPropertySelectionMap& InSelectionMapForResolvingSubobjects, TOptional<FClassDataIndex> ClassIndex = {} );` — Serializes selected snapshot data into an object that existed in the world. The property selection map contains a set of properties that are supposed to be serialized.
- L38 _public prototype_ `static void ApplyToEditorWorldObjectRecreatedWithArchetype( FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, FSnapshotDataCache& Cache, UObject* InOriginalObject, const FPropertySelectionMap& InSelectionMapForResolvingSubobjects );` — Serializes all snapshot data into an object that was recreated and was templated using the snapshot saved archetype / CDO. Because the object was recreated from an archetype, we can skip applying CDO's data into the object.
- L50 _public prototype_ `static void ApplyToEditorWorldObjectRecreatedWithoutArchetype( FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, FSnapshotDataCache& Cache, UObject* InOriginalObject, const FPropertySelectionMap& InSelectionMapForResolvingSubobjects, FClassDataIndex ClassIndex );` — Serializes all snapshot data into an object that was recreated and was templated using the snapshot saved archetype / CDO. Because the object was not recreated from any archetype, we must also apply the saved CDO's data to the object.
- L60 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`
- L66 _protected prototype_ `virtual UObject* ResolveObjectDependency(int32 ObjectIndex, UObject* CurrentValue) const override;`
- L71 _private prototype_ `FApplySnapshotToEditorArchive( FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InOriginalObject, const FPropertySelectionMap& InSelectionMapForResolvingSubobjects, TOptional<const FPropertySelection*> InSelectionSet, FSnapshotDataCache& Cache );`
- L80 _private prototype_ `bool ShouldSerializeAllProperties() const;`
- L83 _private member_ `const FPropertySelectionMap& SelectionMapForResolvingSubobjects;` — Needed so subobjects can be fully reconstructed
- L86 _private member_ `TOptional<const FPropertySelection*> SelectionSet;` — Immutable list of properties we are supposed to serialise. Serialize all properties if unset.
- L88 _private member_ `FSnapshotDataCache& Cache;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/ClassDefaults/ApplyClassDefaulDataArchive.h` (Private)


#### class `UE::LevelSnapshots::Private::FApplyClassDefaulDataArchive`  
`class FApplyClassDefaulDataArchive : public FBaseClassDefaultArchive`  
_L17-48_
- inherits: `FBaseClassDefaultArchive`
- desc: Used when we're taking a snapshot of the world.
- L19 _private typedef_ `using Super = FBaseClassDefaultArchive;`
- L23 _public prototype_ `static void SerializeClassDefaultObject(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InCDO);` — Archive will be used for reconstructing a CDO
- L25 _public prototype_ `static void RestoreChangedClassDefaults(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* ObjectToRestore);` — Archive will be used to to apply any non-object properties before the object receives its saved snapshot values. This is to handle when a CDO has changed its default values since a snapshot was taken.
- L26 _public prototype_ `static void RestoreSelectedChangedClassDefaults(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InObjectToRestore, const FPropertySelection& PropertiesToRestore);`
- L29 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`
- L41 _protected member_ `TOptional<const FPropertySelection*> SelectionSet;` — Immutable list of properties we are supposed to serialise. Serialize all properties if unset.
- L43 _protected prototype_ `FApplyClassDefaulDataArchive(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InObjectToRestore, ESerialisationMode InSerialisationMode, TOptional<const FPropertySelection*> InSelectionSet = {});`
- L46 _protected prototype_ `virtual UObject* ResolveObjectDependency(int32 ObjectIndex, UObject* CurrentValue) const override;`

#### enum `UE::LevelSnapshots::Private::FApplyClassDefaulDataArchive::ESerialisationMode`  
`enum class ESerialisationMode`  
_L34-38_
- L36 _public enumerator_ `RestoringCDO`
- L37 _public enumerator_ `RestoringChangedDefaults`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/ClassDefaults/BaseClassDefaultArchive.h` (Private)


#### class `UE::LevelSnapshots::Private::FBaseClassDefaultArchive`  
`class FBaseClassDefaultArchive : public FSnapshotArchive`  
_L15-24_
- inherits: `FSnapshotArchive`
- desc: Shared logic for serializing class defaults.
- L17 _private typedef_ `using Super = FSnapshotArchive;`
- L20 _protected prototype_ `FBaseClassDefaultArchive(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, bool bIsLoading, UObject* InObjectToRestore);`
- L23 _protected function_ `virtual void FixUpReference(UObject*& Value) const override` — Class archetypes do not need fixing up... they only reference assets and subobjects. Subobjects are handled entirely by the the archetype itself.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/ClassDefaults/TakeClassDefaultObjectSnapshotArchive.h` (Private)


#### class `UE::LevelSnapshots::Private::FTakeClassDefaultObjectSnapshotArchive`  
`class FTakeClassDefaultObjectSnapshotArchive final : public FBaseClassDefaultArchive`  
_L16-39_
- inherits: `FBaseClassDefaultArchive`
- desc: Used when we're taking a snapshot of the world.
- L18 _private typedef_ `using Super = FBaseClassDefaultArchive;`
- L21 _public prototype_ `static void SaveClassDefaultObject(FClassSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* SerializedObject);`
- L24 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`
- L30 _protected function_ `virtual UObject* ResolveObjectDependency(int32 ObjectIndex, UObject* CurrentValue) const override`
- L31 _protected function_ `virtual void OnAddObjectDependency(int32 ObjectIndex, UObject* Object) const override`
- L36 _private prototype_ `FTakeClassDefaultObjectSnapshotArchive(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InSerializedObject, TSet<const FProperty*> PropertiesToSkip);`
- L38 _private member_ `const TSet<const FProperty*> SkippedProperties;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/CustomSerialization/BaseCustomObjectProxyArchive.h` (Private)


#### class `UE::LevelSnapshots::CustomSerialization::FBaseCustomObjectProxyArchive`  
`class FBaseCustomObjectProxyArchive : public FNameAsStringProxyArchive`  
_L11-25_
- inherits: `FNameAsStringProxyArchive`
- desc: Primarily used for serializing object annotation data for implementing ICustomSnapshotSerializationData.
- L15 _public function_ `FBaseCustomObjectProxyArchive(FArchive& InInnerArchive) : FNameAsStringProxyArchive(InInnerArchive)`
- L19 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override = 0;`
- L20 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& Value) override = 0;`
- L22 _public prototype_ `virtual FArchive& operator<<(FWeakObjectPtr& Obj) override;`
- L23 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPtr& Value) override;`
- L24 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Obj) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace CustomSerialization` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/CustomSerialization/LoadCustomObjectProxyArchive.h` (Private)


#### class `UE::LevelSnapshots::CustomSerialization::FLoadCustomObjectProxyArchive`  
`class FLoadCustomObjectProxyArchive : public FBaseCustomObjectProxyArchive`  
_L10-19_
- inherits: `FBaseCustomObjectProxyArchive`
- L12 _private member_ `const TArray<FSoftObjectPath>& TargetArray;`
- L15 _public prototype_ `FLoadCustomObjectProxyArchive(FArchive& InInnerArchive, const TArray<FSoftObjectPath>& TargetArray);`
- L17 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L18 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& Value) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace CustomSerialization` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/CustomSerialization/SaveCustomObjectProxyArchive.h` (Private)


#### class `UE::LevelSnapshots::CustomSerialization::FSaveCustomObjectProxyArchive`  
`class FSaveCustomObjectProxyArchive : public FBaseCustomObjectProxyArchive`  
_L10-19_
- inherits: `FBaseCustomObjectProxyArchive`
- L12 _private member_ `TArray<FSoftObjectPath>& TargetArray;`
- L15 _public prototype_ `FSaveCustomObjectProxyArchive(FArchive& InInnerArchive, TArray<FSoftObjectPath>& TargetArray);`
- L17 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L18 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& Value) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace CustomSerialization` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/LoadSnapshotObjectArchive.h` (Private)


#### class `UE::LevelSnapshots::Private::FLoadSnapshotObjectArchive`  
`class FLoadSnapshotObjectArchive : public FSnapshotArchive`  
_L13-33_
- inherits: `FSnapshotArchive`
- desc: For writing data into an editor object.
- L15 _private typedef_ `using Super = FSnapshotArchive;`
- L18 _public prototype_ `static void ApplyToSnapshotWorldObject(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, FSnapshotDataCache& Cache, UObject* InObjectToRestore, FProcessObjectDependency ProcessObjectDependency, UPackage* InLocalisationSnapshotPackage);`
- L24 _protected prototype_ `virtual UObject* ResolveObjectDependency(int32 ObjectIndex, UObject* CurrentValue) const override;`
- L29 _private prototype_ `FLoadSnapshotObjectArchive(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InSerializedObject, FProcessObjectDependency ProcessObjectDependency, FSnapshotDataCache& Cache);`
- L31 _private member_ `FProcessObjectDependency ProcessObjectDependency;`
- L32 _private member_ `FSnapshotDataCache& Cache;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/SnapshotArchive.h` (Private)


#### class `UE::LevelSnapshots::Private::FSnapshotArchive`  
`class FSnapshotArchive : public FArchiveUObject`  
_L17-66_
- inherits: `FArchiveUObject`
- desc: Handles shared logic for saving and loading data for snapshots.
- L19 _private typedef_ `using Super = FArchiveUObject;`
- L24 _public prototype_ `virtual FString GetArchiveName() const override;`
- L25 _public prototype_ `virtual int64 TotalSize() override;`
- L26 _public prototype_ `virtual int64 Tell() override;`
- L27 _public prototype_ `virtual void Seek(int64 InPos) override;`
- L28 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`
- L29 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L30 _public prototype_ `virtual FArchive& operator<<(UObject*& Value) override;`
- L31 _public prototype_ `virtual void Serialize(void* Data, int64 Length) override;`
- L37 _protected prototype_ `virtual UObject* ResolveObjectDependency(int32 ObjectIndex, UObject* CurrentValue) const = 0;` — Allocates and serializes an object dependency, or gets the object, if it already exists.
- L39 _protected function_ `virtual void OnAddObjectDependency(int32 ObjectIndex, UObject* Object) const` — Called when an object dependency is saved.
- L41 _protected prototype_ `virtual void FixUpReference(UObject*& Value) const;`
- L43 _protected function_ `FWorldSnapshotData& GetSharedData() const`
- L44 _protected function_ `UObject* GetSerializedObject() const`
- L46 _protected member_ `EPropertyFlags ExcludedPropertyFlags;`
- L53 _protected prototype_ `FSnapshotArchive(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, bool bIsLoading, UObject* InSerializedObject);` — @param InObjectData Holds the array we're loading from or saving to @param InSharedData Used to store shared data, e.g. references @param bIsLoading Whether to load or save
- L57 _private member_ `UObject* SerializedObject;`
- L60 _private member_ `int64 DataIndex = 0;` — Where in ObjectData we're currently writing to.
- L63 _private member_ `FObjectSnapshotData& ObjectData;` — The object's serialized data
- L65 _private member_ `FWorldSnapshotData& SharedData;` — Stores shared data, e.g. FNames and FSoftObjectPaths

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Archive/TakeWorldObjectSnapshotArchive.h` (Private)


#### class `UE::LevelSnapshots::Private::FTakeWorldObjectSnapshotArchive`  
`class FTakeWorldObjectSnapshotArchive final : public FSnapshotArchive`  
_L15-45_
- inherits: `FSnapshotArchive`
- desc: Used when we're taking a snapshot of the world.
- L17 _private typedef_ `using Super = FSnapshotArchive;`
- L20 _public prototype_ `static void TakeSnapshot(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InOriginalObject);`
- L23 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`
- L24 _public function_ `virtual void MarkScriptSerializationStart(const UObject* Obj) override`
- L25 _public function_ `virtual void MarkScriptSerializationEnd(const UObject* Obj) override`
- L31 _protected function_ `virtual UObject* ResolveObjectDependency(int32 ObjectIndex, UObject* CurrentValue) const`
- L36 _private prototype_ `FTakeWorldObjectSnapshotArchive(FObjectSnapshotData& InObjectData, FWorldSnapshotData& InSharedData, UObject* InOriginalObject);`
- L38 _private member_ `UObject* Archetype;`
- L44 _private member_ `bool bIsSerializingScriptProperties = false;` — Whether currently serializing UPROPERTY()s on the SerializedObject. This is used to detect whether some custom properties are being serialized.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/Compression/CompressionUtil.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L12 _prototype_ `void Compress(FArchive& Ar, FWorldSnapshotData& Data);` (scope `UE::LevelSnapshots`) — Compresses the data when saving
- L15 _prototype_ `void Decompress(FArchive& Ar, FWorldSnapshotData& Data);` (scope `UE::LevelSnapshots`) — Decompresses the data when loading

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/CustomSerialization/CustomObjectSerializationWrapper.h` (Private)


#### class `UE::LevelSnapshots::Private::FRestoreObjectScope`  
`class FRestoreObjectScope`  
_L20-49_
- desc: Utility for calling final functions when using custom object serialization.
- L23 _private typedef_ `using FFinaliseRestorationCallback = TFunction<void()>;`
- L25 _private member_ `FFinaliseRestorationCallback Callback;`
- L27 _private prototype_ `FRestoreObjectScope() = delete;`
- L28 _private prototype_ `FRestoreObjectScope(const FRestoreObjectScope& Other) = delete;`
- L32 _public function_ `FRestoreObjectScope(FFinaliseRestorationCallback Callback) : Callback(MoveTemp(Callback))`
- L36 _public function_ `~FRestoreObjectScope()`
- L44 _public function_ `FRestoreObjectScope(FRestoreObjectScope&& Other) : Callback(Other.Callback)`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L51 _prototype_ `void TakeSnapshotOfActorCustomSubobjects( AActor* EditorActor, FCustomSerializationData& ActorSerializationData, FWorldSnapshotData& WorldData );` (scope `UE::LevelSnapshots::Private`)
- L57 _prototype_ `void TakeSnapshotForSubobject( UObject* Subobject, FWorldSnapshotData& WorldData );` (scope `UE::LevelSnapshots::Private`)
- L64 _prototype_ `[[nodiscard]] FRestoreObjectScope PreActorRestore_SnapshotWorld( AActor* EditorActor, FCustomSerializationData& ActorSerializationData, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, const FProcessObjectDependency& ProcessObjectDependency, UPackage* LocalisationSnapshotPackage );` (scope `UE::LevelSnapshots::Private`)
- L73 _prototype_ `[[nodiscard]] FRestoreObjectScope PreActorRestore_EditorWorld( AActor* EditorActor, FCustomSerializationData& ActorSerializationData, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, const FPropertySelectionMap& SelectionMap, UPackage* LocalisationSnapshotPackage );` (scope `UE::LevelSnapshots::Private`)
- L83 _prototype_ `[[nodiscard]] FRestoreObjectScope PreSubobjectRestore_SnapshotWorld( UObject* Subobject, const FSoftObjectPath& OriginalSubobjectPath, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, const FProcessObjectDependency& ProcessObjectDependency, UPackage* LocalisationSnapshotPackage );` (scope `UE::LevelSnapshots::Private`)
- L92 _prototype_ `[[nodiscard]] FRestoreObjectScope PreSubobjectRestore_EditorWorld( UObject* SnapshotObject, UObject* EditorObject, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, const FPropertySelectionMap& SelectionMap, UPackage* LocalisationSnapshotPackage );` (scope `UE::LevelSnapshots::Private`)
- L102 _typedef_ `using FHandleCustomSubobjectPair = TFunctionRef<void(UObject* SnapshotSubobject, UObject* EditorSubobject)>;` (scope `UE::LevelSnapshots::Private`)
- L103 _typedef_ `using FHandleUnmatchedCustomSnapshotSubobject = TFunctionRef<void(UObject* UnmatchedSnapshotSubobject)>;` (scope `UE::LevelSnapshots::Private`)
- L105 _prototype_ `void ForEachMatchingCustomSubobjectPair(const FWorldSnapshotData& WorldData, UObject* SnapshotObject, UObject* WorldObject, FHandleCustomSubobjectPair HandleCustomSubobjectPair, FHandleUnmatchedCustomSnapshotSubobject HandleUnmachtedCustomSnapshotSubobject);` (scope `UE::LevelSnapshots::Private`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/CustomSerialization/CustomSerializationDataManager.h` (Private)


#### class `UE::LevelSnapshots::Private::FCustomSerializationDataReader`  
`class FCustomSerializationDataReader : public ICustomSnapshotSerializationData`  
_L14-37_
- inherits: `ICustomSnapshotSerializationData`
- L18 _public prototype_ `FCustomSerializationDataReader(FCustomSerializationDataGetter_ReadOnly SerializationDataGetter, const FWorldSnapshotData& ConstWorldData);`
- L20 _public prototype_ `virtual void WriteObjectAnnotation(const FObjectAnnotator& Writer) override;`
- L21 _public prototype_ `virtual void ReadObjectAnnotation(const FObjectAnnotator& Reader) const override;`
- L22 _public prototype_ `virtual int32 AddSubobjectSnapshot(UObject* Subobject) override;`
- L23 _public prototype_ `virtual TSharedPtr<ISnapshotSubobjectMetaData> GetSubobjectMetaData(int32 Index) override;`
- L24 _public prototype_ `virtual const TSharedPtr<ISnapshotSubobjectMetaData> GetSubobjectMetaData(int32 Index) const override;`
- L25 _public prototype_ `virtual int32 GetNumSubobjects() const override;`
- L30 _protected member_ `TArray<TSharedPtr<ISnapshotSubobjectMetaData>> CachedSubobjectMetaData;` — To avoid dynamically allocating memory every time GetSubobjectMetaData is called, we cache the results here. Just to improve heap memory footprint a tiny bit.
- L33 _protected member_ `FCustomSerializationDataGetter_ReadOnly SerializationDataGetter_ReadOnly;` — Looks up actor or subobject  serialization data. Used instead of reference because some functions, like TakeSubobjectSnapshot, cause FWorldSnapshotData::CustomSubobjectSerializationData to reallocate.
- L36 _protected member_ `const FWorldSnapshotData& WorldData_ReadOnly;` — Needed to look up soft object paths by index

#### class `UE::LevelSnapshots::Private::FCustomSerializationDataWriter`  
`class FCustomSerializationDataWriter : public FCustomSerializationDataReader`  
_L39-58_
- inherits: `FCustomSerializationDataReader`
- L43 _public prototype_ `FCustomSerializationDataWriter(FCustomSerializationDataGetter_ReadWrite SerializationDataGetter, FWorldSnapshotData& WorldData, UObject* SerializedObject);`
- L45 _public prototype_ `virtual void WriteObjectAnnotation(const FObjectAnnotator& Writer) override;`
- L46 _public prototype_ `virtual int32 AddSubobjectSnapshot(UObject* Subobject) override;`
- L51 _private member_ `FCustomSerializationDataGetter_ReadWrite SerializationDataGetter_ReadWrite;` — Looks up actor or subobject  serialization data. Used instead of reference because some functions, like TakeSubobjectSnapshot, cause FWorldSnapshotData::CustomSubobjectSerializationData to reallocate.
- L54 _private member_ `FWorldSnapshotData& WorldData_ReadWrite;` — Needed to look up soft object paths by index
- L57 _private member_ `UObject* SerializedObject;` — Has no function: just used for validating.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L11 _delegate_ `DECLARE_DELEGATE_RetVal(const FCustomSerializationData*, FCustomSerializationDataGetter_ReadOnly);`
- L11 _prototype_ `DECLARE_DELEGATE_RetVal(const FCustomSerializationData*, FCustomSerializationDataGetter_ReadOnly);` (scope `UE::LevelSnapshots::Private`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal(FCustomSerializationData*, FCustomSerializationDataGetter_ReadWrite);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal(FCustomSerializationData*, FCustomSerializationDataGetter_ReadWrite);` (scope `UE::LevelSnapshots::Private`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/Hashing/ActorHashUtil.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L17 _externvar_ `extern FHashSettings GHashSettings;` (scope `UE::LevelSnapshots::Private`) — Updated by project settings
- L22 _prototype_ `void PopulateActorHash(FActorSnapshotHash& HashData, AActor* WorldActor);` (scope `UE::LevelSnapshots::Private`) — Computes and populates hash data for actor.
- L28 _prototype_ `bool HasMatchingHash(const FActorSnapshotHash& ActorData, AActor* WorldActor);` (scope `UE::LevelSnapshots::Private`) — Computes hash for actor and compares it to saved data. @return Whether the computed hash matches the saved hash.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/Hashing/HashArchive.h` (Private)


#### class `FArchiveHashBase`  
`class FArchiveHashBase : public FArchiveUObject`  
_L11-20_
- inherits: `FArchiveUObject`
- L15 _public prototype_ `FArchiveHashBase();`
- L18 _public prototype_ `virtual FArchive& operator<<(class FName& Name);`

#### class `FArchiveComputeFullMD5`  
`class FArchiveComputeFullMD5 : public FArchiveHashBase`  
_L28-49_
- inherits: `FArchiveHashBase`
- desc: First collects all serialized data, and then computes a Crc32 hash using GetCrc32. FArchiveComputeFullMD5 and FArchiveComputeIncrementalMD5 produce the same hash. They have roughly the same speed but sometimes one is faster than the other. Profile it if you want to know.
- L32 _public function_ `FArchiveComputeFullMD5() : FArchiveHashBase() , Writer(SerializedData)`
- L37 _public prototype_ `FMD5Hash GetMD5();`
- L38 _public function_ `const TArray<uint8>& GetSerializedData() const`
- L41 _public prototype_ `virtual void Serialize(void* Data, int64 Length);`
- L42 _public function_ `virtual FString GetArchiveName() const override`
- L47 _private member_ `TArray<uint8> SerializedData;`
- L48 _private member_ `FMemoryWriter Writer;`

#### class `FArchiveComputeIncrementalMD5`  
`class FArchiveComputeIncrementalMD5 : public FArchiveHashBase`  
_L57-71_
- inherits: `FArchiveHashBase`
- desc: Updates the MD5 hash with every Serialize call. FArchiveComputeFullMD5 and FArchiveComputeIncrementalMD5 produce the same hash. They have roughly the same speed but sometimes one is faster than the other. Profile it if you want to know.
- L61 _public prototype_ `FMD5Hash GetMD5();`
- L64 _public prototype_ `virtual void Serialize(void* Data, int64 Length);`
- L65 _public function_ `virtual FString GetArchiveName() const override`
- L70 _private member_ `FMD5 HashBuilder;`

#### class `FArchiveComputeFullCrc32`  
`class FArchiveComputeFullCrc32 : public FArchiveHashBase`  
_L96-119_
- inherits: `FArchiveHashBase`
- desc: First collects all serialized data, and then computes a Crc32 hash using GetCrc32. FArchiveComputeFullCrc32 is often a little faster than FArchiveComputeIncrementalCrc32; there are also many cases where it is slower though. Profile it if you're unsure. The difference can be is usually up to 30%. On i9 9100k, average computation time for 'average' actors is 0.2ms to 0.6ms. Both archives yield the same CRC. This archive has one advantage: before computing CRCs by calling GetCrc32, you can call GetSerializedData().Num() and compare. With this you may avoid having to compute CRCs altogether. Example of flexibility: bool AreActorsEqual(AActor* FirstActor, AActor* SecondActor) { FArchiveComputeFullCrc32 FirstArchive, SecondArchive; SerializeObjectState::SerializeWithoutObjectName(FirstArchive, FirstActor); SerializeObjectState::SerializeWithoutObjectName(SecondArchive, SecondActor); if (FirstArchive.GetSerializedData().Num() != SecondArchive.GetSerializedData().Num()) return false; // Save time by not computing CRC return FirstArchive.GetCrc32() == SecondArchive.GetCrc32(); }
- L100 _public function_ `FArchiveComputeFullCrc32(uint32 CRC = 0) : FArchiveHashBase() , Writer(SerializedData) , CRC(CRC)`
- L106 _public prototype_ `uint32 GetCrc32() const;`
- L107 _public function_ `const TArray<uint8>& GetSerializedData() const`
- L110 _public prototype_ `virtual void Serialize(void* Data, int64 Length);`
- L111 _public function_ `virtual FString GetArchiveName() const override`
- L116 _private member_ `TArray<uint8> SerializedData;`
- L117 _private member_ `FMemoryWriter Writer;`
- L118 _private member_ `uint32 CRC = 0;`

#### class `FArchiveComputeIncrementalCrc32`  
`class FArchiveComputeIncrementalCrc32 : public FArchiveHashBase`  
_L130-149_
- inherits: `FArchiveHashBase`
- desc: Computes a Crc32 hash with every Serialize call. FArchiveComputeFullCrc32 is often a little faster than FArchiveComputeIncrementalCrc32; there are also many cases where it is slower though. Profile it if you're unsure. The difference can be is usually up to 30%. On i9 9100k, average computation time for 'average' actors is 0.2ms to 0.6ms. Both archives yield the same CRC.
- L134 _public function_ `FArchiveComputeIncrementalCrc32(uint32 CRC = 0) : FArchiveHashBase() , CRC(CRC)`
- L139 _public prototype_ `uint32 GetCrc32() const;`
- L142 _public prototype_ `virtual void Serialize(void* Data, int64 Length);`
- L143 _public function_ `virtual FString GetArchiveName() const override`
- L148 _private member_ `uint32 CRC = 0;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/Hashing/SerializeObjectState.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SerializeObjectState`
- L13 _prototype_ `void SerializeWithSubobjects(FArchive& Archive, UObject* Root);` (scope `SerializeObjectState`) — Serializes the object and all its subobjects.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/Util/ClassDataUtil.h` (Private)


#### struct `UE::LevelSnapshots::Private::FSubobjectArchetypeFallbackInfo`  
`struct FSubobjectArchetypeFallbackInfo`  
_L31-36_
- desc: Gives info to retrieve class defaults for a subobject when it was not saved. Remember: Blueprints create new archetype objects for each component so the lookup depends on the context. These are basically just the args for UObject::GetArchetypeFromRequiredInfo.
- L33 _public member_ `UObject* SubobjectOuter;`
- L34 _public member_ `FName SubobjectName;`
- L35 _public member_ `EObjectFlags SubobjectFlags;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L39 _prototype_ `TOptional<TNonNullPtr<UObject>> GetSubobjectArchetype(FWorldSnapshotData& WorldData, FClassDataIndex ClassIndex, FSnapshotDataCache& Cache, const FSubobjectArchetypeFallbackInfo& FallbackInfo);` (scope `UE::LevelSnapshots::Private`) — Gets the archetype to use for constructing a subobject.
- L42 _prototype_ `TOptional<TNonNullPtr<FClassSnapshotData>> GetObjectArchetypeData(FWorldSnapshotData& WorldData, FClassDataIndex ClassIndex, FSnapshotDataCache& Cache, const FSubobjectArchetypeFallbackInfo& FallbackInfo);` (scope `UE::LevelSnapshots::Private`) — Gets an archetype that was saved when the snapshot was taken. Each subobject in actors can have their own archetypes.
- L45 _prototype_ `void SerializeClassDefaultsIntoActor(AActor* Actor, FWorldSnapshotData& WorldData, FClassDataIndex ClassIndex, FSnapshotDataCache& Cache);` (scope `UE::LevelSnapshots::Private`) — Retrieves and serializes class default data into the given actor, if any was saved in the snapshot.
- L47 _prototype_ `void SerializeClassDefaultsIntoSubobject(UObject* Object, FWorldSnapshotData& WorldData, FClassDataIndex ClassIndex, FSnapshotDataCache& Cache, const FSubobjectArchetypeFallbackInfo& FallbackInfo);` (scope `UE::LevelSnapshots::Private`) — Retrieves and serializes class default data into the given actor, if any was saved in the snapshot.
- L49 _prototype_ `void SerializeClassDefaultsInto(UObject* Object, FClassSnapshotData& DataToSerialize, FWorldSnapshotData& WorldData);` (scope `UE::LevelSnapshots::Private`) — Helper that serializes already retrieved class default data into an object. Checks whether this feature is enabled for this class.
- L52 _prototype_ `void SerializeSelectedClassDefaultsIntoSubobject(UObject* Object, FWorldSnapshotData& WorldData, FClassDataIndex ClassIndex, FSnapshotDataCache& Cache, const FSubobjectArchetypeFallbackInfo& FallbackInfo, const FPropertySelection& PropertiesToRestore);` (scope `UE::LevelSnapshots::Private`) — Serializes the class default data into the given subobject but only those allowed by PropertiesToRestore.
- L55 _prototype_ `FSoftClassPath GetClass(const FActorSnapshotData& Data, const FWorldSnapshotData& WorldData);` (scope `UE::LevelSnapshots::Private`) — Helper for getting an actor's class.
- L57 _prototype_ `FSoftClassPath GetClass(const FSubobjectSnapshotData& Data, const FWorldSnapshotData& WorldData);` (scope `UE::LevelSnapshots::Private`) — Helper for getting an actor's subobject's class.
- L60 _prototype_ `FClassDataIndex AddClassArchetype(FWorldSnapshotData& WorldData, UObject* SavedObject);` (scope `UE::LevelSnapshots::Private`) — Adds a class default entry in the world data

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/Util/ObjectDependencyUtil.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L18 _prototype_ `UObject* ResolveObjectDependencyForSnapshotWorld(FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, int32 ObjectPathIndex, const FProcessObjectDependency& ProcessObjectDependency, const FString& LocalisationNamespace);` (scope `UE::LevelSnapshots::Private`) — Resolves an object dependency for use in the snapshot world. If the object is a subobject, it gets fully serialized.
- L27 _prototype_ `UObject* ResolveObjectDependencyForEditorWorld(FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, int32 ObjectPathIndex, const FString& LocalisationNamespace, const FPropertySelectionMap& SelectionMap);` (scope `UE::LevelSnapshots::Private`) — Resolves an object dependency for use in the editor world. If the object is a subobject, it is serialized. Steps for serializing subobject: - If an equivalent object with the saved name and class exists, use that and serialize the properties in SelectionMap into it. - If object does not exist, allocate a new object and serialize all properties into it - If object exists but has different class, skip. Return null.
- L35 _prototype_ `UObject* ResolveObjectDependencyForClassDefaultObject(FWorldSnapshotData& WorldData, int32 ObjectPathIndex, UObject* CurrentValue);` (scope `UE::LevelSnapshots::Private`) — Resolves an object depedency when restoring a class default object. Simply resolves without further checks. @param WorldData Snapshot data @param ObjectPathIndex Identifier the reference in FWorldSnapshotData::SerializedObjectReferences @param CurrentValue The value currently saved in the uproperty that we're resolving for
- L45 _prototype_ `int32 AddObjectDependency(FWorldSnapshotData& WorldData, UObject* ReferenceFromOriginalObject, bool bCheckWhetherSubobject = true);` (scope `UE::LevelSnapshots::Private`) — Saves the object's path. Intended for external objects, e.g. to UMaterial in the content browser. @param ReferenceFromOriginalObject The reference as it was found in a property in the editor world @param bCheckWhetherSubobject If true, this will check the the object is a subobject of an actor and call AddSubobjectDependency.
- L54 _prototype_ `int32 AddCustomSubobjectDependency(FWorldSnapshotData& WorldData, UObject* ReferenceFromOriginalObject);` (scope `UE::LevelSnapshots::Private`) — Adds a subobject to SerializedObjectReferences and CustomSubobjectSerializationData. @return A valid index in SerializedObjectReferences and the corresponding subobject data.
- L57 _prototype_ `FCustomSerializationData* FindCustomSubobjectData(FWorldSnapshotData& WorldData, const FSoftObjectPath& ReferenceFromOriginalObject);` (scope `UE::LevelSnapshots::Private`) — Tries to find custom serialisation data. Use this when you already know that ReferenceFromOriginalObject is not an actor.
- L60 _prototype_ `const FCustomSerializationData* FindCustomActorOrSubobjectData(const FWorldSnapshotData& WorldData, UObject* OriginalObject);` (scope `UE::LevelSnapshots::Private`) — Tries to find custom serialisation data. Use when OriginalObject might be an actor .

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Data/Util/WorldDataUtil.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L19 _prototype_ `FWorldSnapshotData SnapshotWorld(UWorld* World);` (scope `UE::LevelSnapshots::Private`) — Captures the state of the world
- L22 _prototype_ `void ApplyToWorld( FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, UWorld* WorldToApplyTo, UPackage* LocalisationSnapshotPackage, const FPropertySelectionMap& PropertiesToSerialize, TFunctionRef<void()> OnPreApply, TFunctionRef<void()> OnPostApply );` (scope `UE::LevelSnapshots::Private`) — Applies the saved properties to WorldActor
- L33 _prototype_ `bool HasSavedComponentData(const FWorldSnapshotData& WorldData, const FSoftObjectPath& WorldActorPath, const UActorComponent* EditorOrSnapshotComponent);` (scope `UE::LevelSnapshots::Private`) — Whether the component was saved in the world data

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Filtering/Diffing/ApplySnapshotFilter.h` (Private)


#### class `UE::LevelSnapshots::Private::FApplySnapshotFilter`  
`class FApplySnapshotFilter`  
_L14-100_
- L18 _public prototype_ `static FApplySnapshotFilter Make(ULevelSnapshot* Snapshot, AActor* DeserializedSnapshotActor, AActor* WorldActor, const ULevelSnapshotFilter* Filter);`
- L20 _public prototype_ `void ApplyFilterToFindSelectedProperties(FPropertySelectionMap& MapToAddTo);`
- L60 _private prototype_ `FApplySnapshotFilter(ULevelSnapshot* Snapshot, AActor* DeserializedSnapshotActor, AActor* WorldActor, const ULevelSnapshotFilter* Filter);`
- L61 _private prototype_ `bool EnsureParametersAreValid() const;`
- L63 _private prototype_ `void AnalyseComponentRestoration(FPropertySelectionMap& MapToAddTo);`
- L66 _private prototype_ `void FilterActorPair(FPropertySelectionMap& MapToAddTo);` — Container types: actors, subobjects, structs, custom subobjects
- L67 _private prototype_ `EPropertySearchResult FilterSubobjectPair(FPropertySelectionMap& MapToAddTo, UObject* SnapshotSubobject, UObject* WorldSubobject);`
- L68 _private prototype_ `EPropertySearchResult FilterStructPair(FPropertyContainerContext& Parent, FStructProperty* StructProperty);`
- L69 _private prototype_ `EFilterObjectPropertiesResult FindAndFilterCustomSubobjectPairs(FPropertySelectionMap& MapToAddTo, UObject* SnapshotOwner, UObject* WorldOwner);`
- L72 _private prototype_ `void TrackChangedRootProperties(FPropertyContainerContext& ContainerContext, UObject* SnapshotObject, UObject* WorldObject);` — Start property recursion
- L73 _private prototype_ `TOptional<EPropertySearchResult> HandlePossibleStructProperty(FPropertyContainerContext& ContainerContext, FProperty* PropertyToHandle);`
- L74 _private prototype_ `EPropertySearchResult TrackChangedPropertiesInStruct(FPropertyContainerContext& ContainerContext);`
- L77 _private prototype_ `void PreApplyFilter(FPropertyContainerContext& ContainerContext, UObject* SnapshotObject, UObject* WorldObject);` — Registered callbacks for ILevelSnapshotsModule
- L78 _private prototype_ `void PostApplyFilter(FPropertyContainerContext& ContainerContext, UObject* SnapshotObject, UObject* WorldObject);`
- L79 _private prototype_ `void ExtendAnalysedProperties(FPropertyContainerContext& ContainerContext, UObject* SnapshotObject, UObject* WorldObject);`
- L82 _private prototype_ `TOptional<EPropertySearchResult> HandlePossibleSubobjectProperties(FPropertyContainerContext& ContainerContext, FProperty* PropertyToHandle);` — Subobject analysis
- L83 _private prototype_ `TOptional<EPropertySearchResult> TrackPossibleArraySubobjectProperties(FPropertyContainerContext& ContainerContext, FArrayProperty* PropertyToHandle);`
- L84 _private prototype_ `TOptional<EPropertySearchResult> TrackPossibleSetSubobjectProperties(FPropertyContainerContext& ContainerContext, FSetProperty* PropertyToHandle);`
- L85 _private prototype_ `TOptional<EPropertySearchResult> TrackPossibleMapSubobjectProperties(FPropertyContainerContext& ContainerContext, FMapProperty* PropertyToHandle);`
- L87 _private prototype_ `template<typename TCollectionData> TOptional<EPropertySearchResult> TrackPossibleSubobjectsInCollection(FPropertyContainerContext& ContainerContext, FObjectPropertyBase* ObjectProperty, TCollectionData& Detail);`
- L88 _private prototype_ `TOptional<EPropertySearchResult> TrackPossibleSubobjectProperties(FPropertyContainerContext& ContainerContext, FObjectPropertyBase* PropertyToHandle, void* SnapshotValuePtr, void* WorldValuePtr);`
- L91 _private prototype_ `EPropertySearchResult TrackPropertyIfChangedRecursive(FPropertyContainerContext& ContainerContext, FProperty* PropertyInCommon, bool bSkipEqualityTest = false);` — Single property analysis
- L92 _private prototype_ `EPropertySearchResult TrackChangedProperties(FPropertyContainerContext& ContainerContext, FProperty* PropertyInCommon);`
- L94 _private member_ `ULevelSnapshot* Snapshot;`
- L95 _private member_ `AActor* DeserializedSnapshotActor;`
- L96 _private member_ `AActor* WorldActor;`
- L97 _private member_ `const ULevelSnapshotFilter* Filter;`
- L99 _private member_ `TMap<UObject*, EPropertySearchResult> AnalysedSnapshotObjects;` — Every time an object is analysed, it is added here, so we do not analyse more than once.

#### enum `UE::LevelSnapshots::Private::FApplySnapshotFilter::EFilterObjectPropertiesResult`  
`enum class EFilterObjectPropertiesResult`  
_L24-28_
- L26 _public enumerator_ `HasCustomSubobjects`
- L27 _public enumerator_ `HasOnlyNormalProperties`

#### struct `UE::LevelSnapshots::Private::FApplySnapshotFilter::FPropertyContainerContext`  
`struct FPropertyContainerContext`  
_L30-52_
- L32 _public member_ `FPropertySelectionMap& MapToAddTo;`
- L33 _public member_ `FPropertySelection& SelectionToAddTo;`
- L35 _public member_ `UStruct* ContainerClass;`
- L36 _public member_ `void* SnapshotContainer;`
- L37 _public member_ `void* WorldContainer;`
- L38 _public member_ `UObject* AnalysedSnapshotObject;`
- L39 _public member_ `UObject* AnalysedWorldObject;`
- L44 _public member_ `TArray<FString> AuthoredPathInformation;` — Information passed to blueprints. Property name is appended to this. Example: [FooComponent] [BarStructPropertyName]...
- L47 _public member_ `FLevelSnapshotPropertyChain PropertyChain;` — Keeps track of the structs leading to this container
- L49 _public member_ `UClass* RootClass;` — Class that PropertyChain begins from.
- L51 _public prototype_ `FPropertyContainerContext(FPropertySelectionMap& MapToAddTo, FPropertySelection& SelectionToAddTo, UStruct* ContainerClass, void* SnapshotContainer, void* WorldContainer, UObject* AnalysedSnapshotObject, UObject* AnalysedWorldObject, const TArray<FString>& AuthoredPathInformation, const FLevelSnapshotPropertyChain& PropertyChain, UClass* RootClass);`

#### enum `UE::LevelSnapshots::Private::FApplySnapshotFilter::EPropertySearchResult`  
`enum class EPropertySearchResult`  
_L54-58_
- L56 _public enumerator_ `FoundProperties`
- L57 _public enumerator_ `NoPropertiesFound`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Filtering/Diffing/EquivalenceUtil.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L18 _typedef_ `typedef TFunctionRef<void(UActorComponent* SnapshotComponent, UActorComponent* WorldComponent)> FHandleMatchedActorComponent;` (scope `UE::LevelSnapshots::Private`)
- L19 _typedef_ `typedef TFunctionRef<void(UActorComponent*)> FHandleUnmatchedActorComponent;` (scope `UE::LevelSnapshots::Private`)
- L30 _prototype_ `void IterateRestorableComponents(ULevelSnapshot* Snapshot, AActor* SnapshotActor, AActor* WorldActor, FHandleMatchedActorComponent OnComponentsMatched, FHandleUnmatchedActorComponent OnSnapshotComponentUnmatched, FHandleUnmatchedActorComponent OnWorldComponentUnmatched);` (scope `UE::LevelSnapshots::Private`) — Iterates through both actors' component lists and calls the appropriate callback. @param SnapshotActor Actor stored in ULevelSnapshot's internal world @param WorldActor Actor stored in level viewport world @param OnComponentsMatched Called when component exists on both actors @param OnSnapshotComponentUnmatched Called when component exists on snapshot but not on editor world @param OnWorldComponentUnmatched Called when component exists in editor world but not in snapshot world
- L33 _prototype_ `UActorComponent* FindMatchingComponent(AActor* ActorToSearchOn, const FSoftObjectPath& ComponentPath);` (scope `UE::LevelSnapshots::Private`) — Tries to find an actor component by following its full outer path, e.g. /Game/Map.Map:PersistentLevel.SomeActor.SomeParentComp.SomeChildComp will find SomeChildComp with an outer SomeParentComp.
- L38 _prototype_ `bool HasOriginalChangedPropertiesSinceSnapshotWasTaken(ULevelSnapshot* Snapshot, AActor* SnapshotActor, AActor* WorldActor);` (scope `UE::LevelSnapshots::Private`) — Checks whether the original actor has any properties that changed since the snapshot was taken.
- L46 _prototype_ `bool AreSnapshotAndOriginalPropertiesEquivalent(ULevelSnapshot* Snapshot, const FProperty* LeafProperty, void* SnapshotContainer, void* WorldContainer, AActor* SnapshotActor, AActor* WorldActor);` (scope `UE::LevelSnapshots::Private`) — Checks whether the snapshot and original property value should be considered equal. Primitive properties are trivial. Special support is needed for object references. @param IgnoredProperties Properties to ignore
- L56 _prototype_ `bool AreObjectPropertiesEquivalent(ULevelSnapshot* Snapshot, const FObjectPropertyBase* ObjectProperty, void* SnapshotValuePtr, void* WorldValuePtr, AActor* SnapshotActor, AActor* WorldActor);` (scope `UE::LevelSnapshots::Private`) — Two object properties are equivalent if they are - both null - asset references and point to the same asset - actor or component references - subobject references where 1. the subobject have the same name, 2. have the same classes, and 3. the properties are equal
- L59 _prototype_ `bool AreReferencesEquivalent(ULevelSnapshot* Snapshot, UObject* SnapshotPropertyValue, UObject* OriginalPropertyValue, AActor* SnapshotActor, AActor* OriginalActor);` (scope `UE::LevelSnapshots::Private`) — Checks whether two pointers point to "equivalent" objects.
- L62 _prototype_ `bool AreActorsEquivalent(UObject* SnapshotPropertyValue, AActor* OriginalActorReference, const FWorldSnapshotData& WorldData, const FSnapshotDataCache& Cache);` (scope `UE::LevelSnapshots::Private`) — Checks whether the two actors are equivalent

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Filtering/SnapshotSelectionBuilder.h` (Private)


#### class `UE::LevelSnapshots::Private::FSnapshotSelectionBuilder`  
`class FSnapshotSelectionBuilder`  
_L16-35_
- desc: Algorithm for diffing a snapshot
- L20 _public prototype_ `static FPropertySelectionMap DiffAndFilterSnapshot(UWorld* InWorld, ULevelSnapshot* InSnapshot, const ULevelSnapshotFilter* Filter);`
- L24 _private member_ `UWorld* World;`
- L25 _private member_ `ULevelSnapshot* Snapshot;`
- L26 _private member_ `const ULevelSnapshotFilter* Filter;`
- L28 _private prototype_ `FSnapshotSelectionBuilder(UWorld* InWorld, ULevelSnapshot* InSnapshot, const ULevelSnapshotFilter* Filter);`
- L30 _private prototype_ `FPropertySelectionMap DiffAndFilterSnapshot() const;`
- L32 _private prototype_ `void FilterModified(const TArray<AActor*>& ModifiedActors, FPropertySelectionMap& Result) const;`
- L33 _private prototype_ `void FilterRemoved(const TArray<FSoftObjectPath>& RemovedActors, FPropertySelectionMap& Result) const;`
- L34 _private prototype_ `void FilterAdded(const TArray<AActor*>& AddedActors, FPropertySelectionMap& Result) const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/LevelSnapshotsModule.h` (Private)


#### class `UE::LevelSnapshots::Private::FLevelSnapshotsModule`  
`class FLevelSnapshotsModule : public ILevelSnapshotsModule`  
_L19-142_
- inherits: `ILevelSnapshotsModule`
- L23 _public prototype_ `static FLevelSnapshotsModule& GetInternalModuleInstance();`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `virtual void RegisterRestorabilityOverrider(TSharedRef<ISnapshotRestorabilityOverrider> Overrider) override;`
- L32 _public prototype_ `virtual void UnregisterRestorabilityOverrider(const TSharedRef<ISnapshotRestorabilityOverrider>& Overrider) override;`
- L33 _public prototype_ `virtual void AddSkippedSubobjectClasses(const TSet<UClass*>& Classes) override;`
- L34 _public prototype_ `virtual void RemoveSkippedSubobjectClasses(const TSet<UClass*>& Classes) override;`
- L35 _public prototype_ `virtual void RegisterPropertyComparer(UClass* Class, TSharedRef<IPropertyComparer> Comparer) override;`
- L36 _public prototype_ `virtual void UnregisterPropertyComparer(UClass* Class, const TSharedRef<IPropertyComparer>& Comparer) override;`
- L37 _public prototype_ `virtual void RegisterCustomObjectSerializer(UClass* Class, TSharedRef<ICustomObjectSnapshotSerializer> CustomSerializer, bool bIncludeBlueprintChildClasses = true);`
- L38 _public prototype_ `virtual void UnregisterCustomObjectSerializer(UClass* Class) override;`
- L39 _public prototype_ `virtual void RegisterGlobalActorFilter(TSharedRef<IActorSnapshotFilter> Filter) override;`
- L40 _public prototype_ `virtual void UnregisterGlobalActorFilter(const TSharedRef<IActorSnapshotFilter>& Filter) override;`
- L41 _public prototype_ `virtual void RegisterSnapshotLoader(TSharedRef<ISnapshotLoader> Loader) override;`
- L42 _public prototype_ `virtual void UnregisterSnapshotLoader(const TSharedRef<ISnapshotLoader>& Loader) override;`
- L43 _public prototype_ `virtual void RegisterRestorationListener(TSharedRef<IRestorationListener> Listener) override;`
- L44 _public prototype_ `virtual void UnregisterRestorationListener(const TSharedRef<IRestorationListener>& Listener) override;`
- L45 _public prototype_ `virtual void RegisterTakeSnapshotListener(TSharedRef<ITakeSnapshotListener> Extender) override;`
- L46 _public prototype_ `virtual void UnregisterTakeSnapshotListener(const TSharedRef<ITakeSnapshotListener>& Listener) override;`
- L47 _public prototype_ `virtual void RegisterSnapshotFilterExtender(TSharedRef<ISnapshotFilterExtender> Extender) override;`
- L48 _public prototype_ `virtual void UnregisterSnapshotFilterExtender(const TSharedRef<ISnapshotFilterExtender>& Listener) override;`
- L49 _public prototype_ `virtual void AddExplicitilySupportedProperties(const TSet<const FProperty*>& Properties) override;`
- L50 _public prototype_ `virtual void RemoveAdditionallySupportedProperties(const TSet<const FProperty*>& Properties) override;`
- L51 _public prototype_ `virtual void AddExplicitlyUnsupportedProperties(const TSet<const FProperty*>& Properties) override;`
- L52 _public prototype_ `virtual void RemoveExplicitlyUnsupportedProperties(const TSet<const FProperty*>& Properties) override;`
- L53 _public prototype_ `virtual void AddSkippedClassDefault(const UClass* Class) override;`
- L54 _public prototype_ `virtual void RemoveSkippedClassDefault(const UClass* Class) override;`
- L55 _public prototype_ `virtual bool ShouldSkipClassDefaultSerialization(const UClass* Class) const override;`
- L58 _public prototype_ `bool ShouldSkipSubobjectClass(const UClass* Class) const;`
- L60 _public prototype_ `const TArray<TSharedRef<ISnapshotRestorabilityOverrider>>& GetOverrides() const;`
- L61 _public prototype_ `bool IsPropertyExplicitlySupported(const FProperty* Property) const;`
- L62 _public prototype_ `bool IsPropertyExplicitlyUnsupported(const FProperty* Property) const;`
- L64 _public prototype_ `FPropertyComparerArray GetPropertyComparerForClass(UClass* Class) const;`
- L65 _public prototype_ `IPropertyComparer::EPropertyComparison ShouldConsiderPropertyEqual(const FPropertyComparerArray& Comparers, const FPropertyComparisonParams& Params) const;`
- L67 _public prototype_ `TSharedPtr<ICustomObjectSnapshotSerializer> GetCustomSerializerForClass(UClass* Class) const;`
- L69 _public prototype_ `bool CanModifyMatchedActor(const FCanModifyMatchedActorParams& Params, FText* ExclusionReason = nullptr) const;`
- L70 _public prototype_ `bool CanRecreateActor(const FCanRecreateActorParams& Params, FText* ExclusionReason = nullptr) const;`
- L71 _public prototype_ `bool CanDeleteActor(const AActor* EditorActor, FText* ExclusionReason = nullptr) const;`
- L73 _public prototype_ `virtual void AddCanTakeSnapshotDelegate(FName DelegateName, FCanTakeSnapshot Delegate) override;`
- L74 _public prototype_ `virtual void RemoveCanTakeSnapshotDelegate(FName DelegateName) override;`
- L75 _public prototype_ `virtual bool CanTakeSnapshot(const FPreTakeSnapshotEventData& Event) const override;`
- L77 _public prototype_ `void OnPostLoadSnapshotObject(const FPostLoadSnapshotObjectParams& Params);`
- L79 _public prototype_ `void OnPreApplySnapshot(const FPreApplySnapshotParams& Params);`
- L80 _public prototype_ `void OnPostApplySnapshot(const FPostApplySnapshotParams& Params);`
- L82 _public prototype_ `void OnPreApplySnapshotProperties(const FApplySnapshotPropertiesParams& Params);`
- L83 _public prototype_ `void OnPostApplySnapshotProperties(const FApplySnapshotPropertiesParams& Params);`
- L85 _public prototype_ `void OnPreApplySnapshotToActor(const FApplySnapshotToActorParams& Params);`
- L86 _public prototype_ `void OnPostApplySnapshotToActor(const FApplySnapshotToActorParams& Params);`
- L88 _public prototype_ `void OnPreCreateActor(UWorld* World, TSubclassOf<AActor> ActorClass, FActorSpawnParameters& InOutSpawnParams);`
- L89 _public prototype_ `void OnPostRecreateActor(AActor* Actor);`
- L91 _public prototype_ `void OnPreRemoveActor(const FPreRemoveActorParams& Params);`
- L92 _public prototype_ `void OnPostRemoveActors(const FPostRemoveActorsParams& Params);`
- L94 _public prototype_ `void OnPreRecreateComponent(const FPreRecreateComponentParams& Params);`
- L95 _public prototype_ `void OnPostRecreateComponent(UActorComponent* RecreatedComponent);`
- L97 _public prototype_ `void OnPreRemoveComponent(UActorComponent* ComponentToRemove);`
- L98 _public prototype_ `void OnPostRemoveComponent(const FPostRemoveComponentParams& Params);`
- L100 _public prototype_ `void OnPreTakeObjectSnapshot(const FPreTakeObjectSnapshotEvent& Params);`
- L101 _public prototype_ `void OnPostTakeObjectSnapshot(const FPostTakeObjectSnapshotEvent& Params);`
- L103 _public prototype_ `void PreApplyFilters(const FPreApplyFiltersParams& Params);`
- L104 _public prototype_ `FPostApplyFiltersResult PostApplyFilters(const FPostApplyFiltersParams& Params);`
- L115 _private member_ `TArray<TSharedRef<ISnapshotRestorabilityOverrider>> Overrides;` — Allows external modules to override what objects and properties are considered by the snapshot system.
- L118 _private member_ `TSet<UClass*> SkippedSubobjectClasses;` — Subobject classes we do not capture nor restore
- L120 _private member_ `TMap<FSoftClassPath, TArray<TSharedRef<IPropertyComparer>>> PropertyComparers;`
- L121 _private member_ `TMap<FSoftClassPath, FCustomSerializer> CustomSerializers;`
- L123 _private member_ `TArray<TSharedRef<IActorSnapshotFilter>> GlobalFilters;`
- L124 _private member_ `TArray<TSharedRef<ISnapshotLoader>> SnapshotLoaders;`
- L125 _private member_ `TArray<TSharedRef<IRestorationListener>> RestorationListeners;`
- L126 _private member_ `TArray<TSharedRef<ITakeSnapshotListener>> TakeSnapshotListenersListeners;`
- L127 _private member_ `TArray<TSharedRef<ISnapshotFilterExtender>> FilterExtenders;`
- L130 _private member_ `TSet<const FProperty*> SupportedProperties;` — Allows these properties even when the default behaviour would exclude them.
- L132 _private member_ `TSet<const FProperty*> UnsupportedProperties;` — Forbid these properties even when the default behaviour would include them.
- L135 _private member_ `TSet<FSoftClassPath> SkippedCDOs;` — Classes for which to not serialize class default
- L138 _private member_ `TMap<FName, FCanTakeSnapshot> CanTakeSnapshotDelegates;` — Map of named delegates for confirming that a level snapshot is possible.
- L140 _private prototype_ `void PreTakeSnapshot(const FPreTakeSnapshotEventData& Params);`
- L141 _private prototype_ `void PostTakeSnapshot(const FPostTakeSnapshotEventData& Params);`

#### struct `UE::LevelSnapshots::Private::FLevelSnapshotsModule::FCustomSerializer`  
`struct FCustomSerializer`  
_L108-112_
- L110 _public member_ `TSharedRef<ICustomObjectSnapshotSerializer> Serializer;`
- L111 _public member_ `bool bIncludeBlueprintChildren;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L17 _typedef_ `using FPropertyComparerArray = TArray<TSharedRef<IPropertyComparer>, TInlineAllocator<4>>;` (scope `UE::LevelSnapshots::Private`) — The array is used very often in many loops: optimize heap allocation

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Restoration/Actor/ActorUtil.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L21 _prototype_ `TOptional<TNonNullPtr<AActor>> GetDeserializedActor(const FSoftObjectPath& OriginalObjectPath, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, UPackage* LocalisationSnapshotPackage, bool bWarnIfNotFound = true);` (scope `UE::LevelSnapshots::Private`) — Allocates the actor, if no yet, and initialises it in the snapshot world.
- L24 _prototype_ `TOptional<TNonNullPtr<UClass>> GetActorClass(const FSoftObjectPath& OriginalActorPath, FWorldSnapshotData& WorldData, bool bWarnIfNotFound = true);` (scope `UE::LevelSnapshots::Private`) — Gets the actor class from the original actor soft path
- L26 _prototype_ `TOptional<TNonNullPtr<AActor>> GetPreallocatedIfCached(const FSoftObjectPath& OriginalActorPath, const FSnapshotDataCache& Cache);` (scope `UE::LevelSnapshots::Private`)
- L29 _prototype_ `TOptional<TNonNullPtr<AActor>> GetPreallocated(const FSoftObjectPath& OriginalActorPath, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, bool bWarnIfNotFound = true);` (scope `UE::LevelSnapshots::Private`) — Gets the actor allocated in the snapshot world or allocates it and all of its subobjects.
- L32 _prototype_ `void RestoreIntoExistingWorldActor(AActor* OriginalActor, FActorSnapshotData& ActorData, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, UPackage* InLocalisationSnapshotPackage, const FPropertySelectionMap& SelectedProperties);` (scope `UE::LevelSnapshots::Private`) — Restores selected properties into the actor and its subobjects: the actor existed before the snapshot was applied.
- L35 _prototype_ `void RestoreIntoRecreatedEditorWorldActor(AActor* OriginalActor, FActorSnapshotData& ActorData, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, UPackage* InLocalisationSnapshotPackage, const FPropertySelectionMap& SelectedProperties);` (scope `UE::LevelSnapshots::Private`) — Restores all properties into the actor and its subobjects: the actor was recreated as part of the restoration process.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Restoration/Component/BaseComponentRestorer.h` (Private)


#### class `UE::LevelSnapshots::Private::TBaseComponentRestorer`  
`template<typename TDerived> class TBaseComponentRestorer`  
_L32-183_
- desc: Helper for restoring components into an actor.
- L34 _private function_ `const TDerived* This() const`
- L37 _public function_ `TBaseComponentRestorer(AActor* ActorToRestore, const FSoftObjectPath& OriginalActorPath, FWorldSnapshotData& WorldData) : ActorToRestore(ActorToRestore) , OriginalActorPath(OriginalActorPath) , SnapshotData(WorldData.ActorData[OriginalActorPath]) , WorldData(WorldData)`
- L45 _public function_ `void RecreateSavedComponents() const` — Loops all saved component data and makes sure they are allocated.
- L61 _protected function_ `AActor* GetActorToRestore() const`
- L62 _protected function_ `const FSoftObjectPath& GetOriginalActorPath() const`
- L63 _protected function_ `const FActorSnapshotData& GetSnapshotData() const`
- L64 _protected function_ `FWorldSnapshotData& GetWorldData() const`
- L71 _protected function_ `UActorComponent* FindOrAllocateComponentInternal(const FSoftObjectPath& ComponentPath, FSubobjectSnapshotData& SubobjectData, const FComponentSnapshotData& ComponentData) const` — @param ComponentPath The original path of the component @param SubobjectData The subobject data associated with this component @param ComponentData The component data associated with this component
- L104 _private function_ `UActorComponent* AllocateComponent(const FSoftObjectPath& ComponentPath, FSubobjectSnapshotData& SubobjectData, const FComponentSnapshotData& ComponentData, UObject* ComponentOuter) const`
- L136 _private function_ `void AddToCorrectComponentArray(const FComponentSnapshotData& ComponentData, UActorComponent* Component) const`
- L160 _private function_ `UObject* FindOrAllocateComponentForComponentOuter(const FSoftObjectPath& ComponentOuterPath) const`
- L179 _private member_ `AActor* ActorToRestore;`
- L180 _private member_ `const FSoftObjectPath OriginalActorPath;`
- L181 _private member_ `const FActorSnapshotData& SnapshotData;`
- L182 _private member_ `FWorldSnapshotData& WorldData;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Restoration/Component/SnapshotComponentUtil.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L18 _prototype_ `void AddAndRemoveComponentsSelectedForRestore(AActor* MatchedEditorActor, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache, const FPropertySelectionMap& SelectionMap, UPackage* LocalisationSnapshotPackage);` (scope `UE::LevelSnapshots::Private`) — Adds and removes components on an actor that exists in the snapshot world (and existed the snapshot were applied).
- L21 _prototype_ `void AllocateMissingComponentsForRecreatedActor(AActor* RecreatedEditorActor, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache);` (scope `UE::LevelSnapshots::Private`) — Recreates all components an actor recreated in the editor world.
- L24 _prototype_ `void AllocateMissingComponentsForSnapshotActor(AActor* SnapshotActor, const FSoftObjectPath& OriginalActorPath, FWorldSnapshotData& WorldData, FSnapshotDataCache& Cache);` (scope `UE::LevelSnapshots::Private`) — Recreates all components on the actor in the snapshot world.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Restoration/Scope/ApplySnapshotPropertiesScope.h` (Private)


#### class `UE::LevelSnapshots::Private::FApplySnapshotPropertiesScope`  
`class FApplySnapshotPropertiesScope : public FNoncopyable`  
_L15-22_
- inherits: `FNoncopyable`
- desc: Convenience type that calls FLevelSnaphshotsModule::OnPreApplySnapshot and FLevelSnaphshotsModule::OnPostApplySnapshot.
- L17 _private member_ `const FApplySnapshotPropertiesParams Params;`
- L20 _public prototype_ `FApplySnapshotPropertiesScope(const FApplySnapshotPropertiesParams& InParams);`
- L21 _public prototype_ `~FApplySnapshotPropertiesScope();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Restoration/Scope/ApplySnapshotToActorScope.h` (Private)


#### class `UE::LevelSnapshots::Private::FApplySnapshotToActorScope`  
`class FApplySnapshotToActorScope : public FNoncopyable`  
_L15-22_
- inherits: `FNoncopyable`
- desc: Convenience type that calls FLevelSnaphshotsModule::OnPreApplySnapshot and FLevelSnaphshotsModule::OnPostApplySnapshot.
- L17 _private member_ `const FApplySnapshotToActorParams Params;`
- L20 _public prototype_ `FApplySnapshotToActorScope(const FApplySnapshotToActorParams& Params);`
- L21 _public prototype_ `~FApplySnapshotToActorScope();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Restoration/Scope/RemoveComponentScope.h` (Private)


#### class `UE::LevelSnapshots::Private::FRemoveComponentScope`  
`class FRemoveComponentScope : public FNoncopyable`  
_L15-22_
- inherits: `FNoncopyable`
- desc: Convenience type that calls FLevelSnaphshotsModule::OnPreRemoveComponent and FLevelSnaphshotsModule::OnPostRemoveComponent.
- L17 _private member_ `FPostRemoveComponentParams Params;`
- L20 _public prototype_ `FRemoveComponentScope(UActorComponent* RemovedComponent);`
- L21 _public prototype_ `~FRemoveComponentScope();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SnapshotConsoleVariables.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace ConsoleVariables` (scope `UE::LevelSnapshots`)
- L11 _externvar_ `extern TAutoConsoleVariable<FString> CVarBreakOnSnapshotActor;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Hit a debug break point when an actor with the given name is snapshot
- L14 _externvar_ `extern TAutoConsoleVariable<FString> CVarBreakOnDiffMatchedActor;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Hit a debug break point when a matched actor with the given name is discovered while diffing world
- L18 _externvar_ `extern TAutoConsoleVariable<FString> CVarBreakOnSerializedPropertyName;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Halt execution when encountering this property name during serialisation
- L22 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogTimeDiffingMatchedActors;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Enable logging of how long matched actors take to diff
- L25 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogTimeTakingSnapshots;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Enable logging of how long actors take to get snapshots taken of.
- L28 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogTimeRecreatingActors;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Enable logging of how it takes to recreate each actor ("Actors to Add").
- L31 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogTimeRestoringMatchedActors;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Enable logging of how it takes to serialize into matched actors ("Modified").
- L34 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogSelectionMap;` (scope `UE::LevelSnapshots::ConsoleVariables`) — Logs all filtered properties whenever a filter is applied

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/ActorGroupRestoration.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace ActorGroupRestoration` (scope `UE::LevelSnapshots::Private`)
- L9 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::ActorGroupRestoration`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/ActorLabelRestoration.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace ActorLabelRestoration` (scope `UE::LevelSnapshots::Private`)
- L9 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::ActorLabelRestoration`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/AssetUserDataRestoration.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace AssetUserDataRestoration` (scope `UE::LevelSnapshots::Private`)
- L9 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::AssetUserDataRestoration`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/AttachParentShowsTransformProperties.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace AttachParentShowsTransformPropertiesFix` (scope `UE::LevelSnapshots::Private`)
- L28 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::AttachParentShowsTransformPropertiesFix`) — By default only modified properties are shown. However in the below case we show the transform properties (Location, Rotation, and Scale) if one of the selected properties is the AttachParent. 1. Create cube 2. Rotate it to 40 degrees 3. Take a snapshot 4. Create new empty actor 5. Attach cube to empty actor 6. Rotate empty actor by 10 degrees 7. Apply the snapshot Result: After applying, the cube has a diff because its rotation is 50 degrees. The reason is because before applying the only thing that was different was the cube's attach parent. When the parent actor is removed, its world-space transform is retained; actors are removed first and then the properties of modified actors are saved. The solution is to add the cube's transform properties even though they're equal to the snapshot version. Users will see the property in the UI and can opt to not restore it.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/CollisionRestoration.h` (Private)


#### class `UE::LevelSnapshots::Private::FCollisionRestoration`  
`class FCollisionRestoration : public IPropertyComparer, public ISnapshotLoader, public IRestorationListener`  
_L16-52_
- inherits: `IPropertyComparer,ISnapshotLoader,IRestorationListener`
- desc: UPrimitiveComponent::BodyInstance requires special logic for restoring & loading collision information.
- L24 _public prototype_ `static void Register(FLevelSnapshotsModule& Module);`
- L26 _public prototype_ `FCollisionRestoration();`
- L29 _public prototype_ `virtual EPropertyComparison ShouldConsiderPropertyEqual(const FPropertyComparisonParams& Params) const override;`
- L33 _public prototype_ `virtual void PostLoadSnapshotObject(const FPostLoadSnapshotObjectParams& Params) override;`
- L37 _public prototype_ `virtual void PostApplySnapshotProperties(const FApplySnapshotPropertiesParams& Params) override;`
- L42 _private prototype_ `bool HaveNonDefaultCollisionPropertiesChanged( const FPropertyComparisonParams& Params, UStaticMeshComponent* SnapshotObject, UStaticMeshComponent* WorldObject ) const;`
- L48 _private member_ `const FProperty* BodyInstanceProperty;`
- L49 _private member_ `const FProperty* ObjectTypeProperty;`
- L50 _private member_ `const FProperty* CollisionEnabledProperty;`
- L51 _private member_ `const FProperty* CollisionResponsesProperty;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/EngineTypesRestorationFence.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace EngineTypesRestorationFence` (scope `UE::LevelSnapshots::Private`)
- L10 _prototype_ `void RegisterSpecialEngineTypeSupport(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::EngineTypesRestorationFence`) — Adds support for special cases for misc engine types

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/GridPlacementRestoration.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace GridPlacementRestoration` (scope `UE::LevelSnapshots::Private`)
- L9 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::GridPlacementRestoration`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/LevelInstanceRestoration.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L10 _namespace_ `namespace LevelInstanceRestoration` (scope `UE::LevelSnapshots::Private`)
- L12 _prototype_ `void Register(ILevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::LevelInstanceRestoration`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/MaterialInstanceSupport.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace MaterialInstanceSupport` (scope `UE::LevelSnapshots::Private`)
- L9 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::MaterialInstanceSupport`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/PCGRestoration.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L8 _namespace_ `namespace PCGRestoration` (scope `UE::LevelSnapshots::Private`)
- L10 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::PCGRestoration`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/SpecialSupport/SpecialActorPropertySupport.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace SpecialActorPropertySupport` (scope `UE::LevelSnapshots::Private`)
- L9 _prototype_ `void Register(FLevelSnapshotsModule& Module);` (scope `UE::LevelSnapshots::Private::SpecialActorPropertySupport`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Util/ObjectDependencyCallback.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _typedef_ `using FProcessObjectDependency = TFunctionRef<void(int32 OriginalObjectIndex)>;` (scope `UE::LevelSnapshots`) — Callback used to traverse object dependencies while serializing objects. @param OriginalObjectDependency Index to FWorldSnapshotData::SerializedReferences

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Util/PropertyIterator.h` (Private)


#### class `UE::LevelSnapshots::Private::FPropertyIterator`  
`class FPropertyIterator`  
_L13-26_
- desc: Utility class for iterating all properties in a struct, including properties of sub-structs and collections containing structs.
- L15 _private member_ `TSet<UStruct*> VisitedSet;`
- L16 _private member_ `const EPropertyFlags SkipFlags;`
- L19 _public prototype_ `FPropertyIterator(UStruct* RootStruct, TFunctionRef<void(FProperty*)> PropertyCallback, TFunctionRef<void(UStruct*)> StructCallback, EPropertyFlags SkipFlags = CPF_Transient | CPF_Deprecated);`
- L23 _private prototype_ `void IterateProperties(UStruct* Struct, TFunctionRef<void(FProperty*)> Callback, TFunctionRef<void(UStruct*)> StructCallback);`
- L24 _private prototype_ `bool HandleStructProperty(FProperty* Property, TFunctionRef<void(FProperty*)> PropertyCallback, TFunctionRef<void(UStruct*)> StructCallback);`
- L25 _private prototype_ `void HandleCollectionProperties(FProperty* Property, TFunctionRef<void(FProperty*)> PropertyCallback, TFunctionRef<void(UStruct*)> StructCallback);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Util/SoftObjectPathUtil.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::LevelSnapshots`)
- L14 _prototype_ `FSoftObjectPath ExtractPathWithoutSubobjects(const FSoftObjectPath& ObjectPath);` (scope `UE::LevelSnapshots::Private`) — Given e.g. "/Game/MapName.MapName:PersistentLevel.StaticMeshActor_42.SomeComponent" returns everything before the colon, i.e. "/Game/MapName.MapName"
- L17 _prototype_ `FString ExtractLastSubobjectName(const FSoftObjectPath& ObjectPath);` (scope `UE::LevelSnapshots::Private`) — Finds the last subobject name in the path
- L20 _prototype_ `TOptional<FSoftObjectPath> ExtractActorFromPath(const FSoftObjectPath& OriginalObjectPath, bool& bIsPathToActorSubobject);` (scope `UE::LevelSnapshots::Private`) — If path contains an actor, return subobject path to that actor.
- L23 _prototype_ `bool IsPathToWorldObject(const FSoftObjectPath& OriginalObjectPath);` (scope `UE::LevelSnapshots::Private`) — Checks whether this is a soft object path to an object in an editor world
- L26 _prototype_ `TOptional<int32> FindDotAfterActorName(const FSoftObjectPath& OriginalObjectPath);` (scope `UE::LevelSnapshots::Private`) — Given a path such as "/Game/MapName.MapName:PersistentLevel.StaticMeshActor_42.SomeComponent" returns the index of "S" in "SomeComponent"
- L32 _prototype_ `TOptional<TNonNullPtr<FActorSnapshotData>> FindSavedActorDataUsingObjectPath(TMap<FSoftObjectPath, FActorSnapshotData>& ActorData, const FSoftObjectPath& OriginalObjectPath, bool& bIsPathToActorSubobject);` (scope `UE::LevelSnapshots::Private`) — If Path contains a path to an actor, returns that actor. Example: /Game/MapName.MapName:PersistentLevel.StaticMeshActor_42.StaticMeshComponent returns StaticMeshActor_42's data
- L39 _prototype_ `FSoftObjectPath SetActorInPath(AActor* NewActor, const FSoftObjectPath& OriginalObjectPath);` (scope `UE::LevelSnapshots::Private`) — Takes an existing path to an actor's subobjects and replaces the actor bit with the path to another actor. E.g. /Game/MapName.MapName:PersistentLevel.StaticMeshActor_42.StaticMeshComponent could become /Game/MapName.MapName:PersistentLevel.SomeOtherActor.StaticMeshComponent

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Private/Util/SortedScopedLog.h` (Private)


#### class `FConditionalSortedScopedLog`  
`class FConditionalSortedScopedLog : public FNoncopyable`  
_L32-100_
- inherits: `FNoncopyable`
- desc: Measures and sorts computing times. Use as follows: void Foo() { const bool bShouldLog = ... FConditionalSortedScopedLog Container(bShouldLog); for (...) { FScopedLogItem Log = Container.AddLogItem("Item_N") ... } } This will print something like this: LogStats:                  NDC_NantStage_2 - 42.983 ms LogStats:       BP_OffRoadVechicleStatic_4 - 14.094 ms LogStats:                      LightCard_2 - 1.795 ms
- L37 _public typedef_ `using FLoggedItem = TPair<double, FString>;`
- L38 _public typedef_ `using FLogFormatter = TFunction<void(FOutputDevice& OutputDevice, const FString DisplayUnitsString, const FString& Title, const TArray<FLoggedItem>& SortedItems)>;`
- L66 _public prototype_ `FConditionalSortedScopedLog( bool bCondition, FString Title = FString(), FLogFormatter Formatter = FFormatLog(), FOutputDevice* OutputDevice = GLog, bool bLargeTimesFirst = true, bool bLogTotalTime = true, EScopeLogTimeUnits Units = EScopeLogTimeUnits::Milliseconds);` — @param bCondition Determines whether anything will be printed or not. Typical use case: this condition depends on a console variable. @param Title This will be printed before the sorted list of items @param bLargeTimesFirst Whether to sort descending or ascending @param bLogTotalTime Whether to log the total time taken when this log is destroyed @param Units Whether to use seconds or milliseconds when printing time information @param Formatter Receives the final data and logs it. Useful for logging in a special format, such as @param OutputDevice Where to print to
- L74 _public prototype_ `~FConditionalSortedScopedLog();`
- L78 _public prototype_ `[[nodiscard]] FScopedLogItem AddScopedLogItem(FString Name, bool bItemLogCondition = true);` — Adds a log item. When it goes out of scope, its time is automatically added to LoggedItems.
- L80 _public function_ `void AddCustomMeasuredLogItem(bool bLogCondition, FString Name, double Time)`
- L82 _public prototype_ `void AddCustomMeasuredLogItem(FString Name, double Time);` — Adds a time you measured yourself
- L86 _private prototype_ `double GetDisplayScopedTime(double InScopedTime) const;`
- L87 _private prototype_ `FString GetDisplayUnitsString() const;`
- L89 _private member_ `bool bCondition;`
- L91 _private member_ `FString LogTitle;`
- L92 _private member_ `bool bLargeTimesFirst;`
- L93 _private member_ `const double StartTime;`
- L94 _private member_ `EScopeLogTimeUnits Units;`
- L95 _private member_ `FLogFormatter Formatter;`
- L96 _private member_ `FOutputDevice* Output;`
- L99 _private member_ `TArray<FLoggedItem> LoggedItems;` — Will be sorted later

#### struct `FConditionalSortedScopedLog::FFormatLog`  
`struct FFormatLog`  
_L41-44_
- desc: Simply logs to output device
- L43 _public prototype_ `void operator()(FOutputDevice& OutputDevice, const FString& DisplayUnitsString, const FString& Title, const TArray<FLoggedItem>& SortedItems);`

#### struct `FConditionalSortedScopedLog::FFormatCSV`  
`struct FFormatCSV`  
_L46-49_
- desc: Logs in CSV format
- L48 _public prototype_ `void operator()(FOutputDevice& OutputDevice, const FString& DisplayUnitsString, const FString& Title, const TArray<FLoggedItem>& SortedItems);`

#### enum `FConditionalSortedScopedLog::EScopeLogTimeUnits`  
`enum class EScopeLogTimeUnits`  
_L51-55_
- L53 _public enumerator_ `Milliseconds`
- L54 _public enumerator_ `Seconds`

#### class `FScopedLogItem`  
`class FScopedLogItem`  
_L103-121_
- desc: Tracks time for this item to be destroyed and logs it to the owning container.
- L107 _public prototype_ `FScopedLogItem(FConditionalSortedScopedLog& Container, bool bCondition, FString InName);`
- L108 _public prototype_ `~FScopedLogItem();`
- L110 _public prototype_ `FScopedLogItem(const FScopedLogItem&) = delete;`
- L111 _public prototype_ `FScopedLogItem(FScopedLogItem&&) = default;`
- L112 _public prototype_ `FScopedLogItem& operator=(const FScopedLogItem&) = delete;`
- L113 _public prototype_ `FScopedLogItem& operator=(FScopedLogItem&&) = delete;`
- L117 _private member_ `FConditionalSortedScopedLog& Container;`
- L118 _private member_ `const bool bCondition;`
- L119 _private member_ `const double StartTime;`
- L120 _private member_ `const FString Name;`

#### class `FSortedScopedLog`  
`class FSortedScopedLog : public FConditionalSortedScopedLog`  
_L124-137_
- inherits: `FConditionalSortedScopedLog`
- desc: Version of FConditionalSortedScopedLog that always logs.
- L128 _public function_ `FSortedScopedLog(FString Name = FString(), FLogFormatter Formatter = FFormatLog(), FOutputDevice* OutputDevice = GLog, bool bLargeTimesFirst = true, bool bLogTotalTime = true, EScopeLogTimeUnits Units = EScopeLogTimeUnits::Milliseconds ) : FConditionalSortedScopedLog(true, Name, Formatter, OutputDevice, bLargeTimesFirst, bLogTotalTime, Units)`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/ActorSnapshotData.h` (Public)


#### struct `FActorSnapshotData`  
`struct FActorSnapshotData`  
_L14-61_
- reflection: `USTRUCT()`
- desc: Holds saved actor data. See ActorUtil for operations.
- L21 _public member_ `FString ActorLabel;` — `UPROPERTY()` — The label of the actor when it was saved.
- L27 _public member_ `FSoftClassPath ActorClass_DEPRECATED;` — `UPROPERTY()` — The class the actor had when it was saved.
- L31 _public member_ `int32 ClassIndex = INDEX_NONE;` — `UPROPERTY()` — Valid index to FWorldSnapshotData::ClassData. Use to lookup class and archetype data.
- L35 _public member_ `FObjectSnapshotData SerializedActorData;` — `UPROPERTY()` — The actor's serialized data
- L41 _public member_ `FCustomSerializationData CustomActorSerializationData;` — `UPROPERTY()` — Data that was generated by some ICustomObjectSnapshotSerializer. Needed to restore custom subobjects.
- L47 _public member_ `TMap<int32, FComponentSnapshotData> ComponentData;` — `UPROPERTY()` — Additional component recreation info
- L51 _public member_ `TArray<int32> OwnedSubobjects;` — `UPROPERTY()` — Tracks all non-component subobjects. Valid index to FWorldSnapshotData::SerializedObjectReferences.
- L57 _public member_ `FActorSnapshotHash Hash;` — `UPROPERTY()` — Used to detect changes without loading actor into memory.
- L60 _public function_ `UE::LevelSnapshots::FClassDataIndex GetClassDataIndex() const` — "Type safety" for better self-documenting code

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/ClassDefaultObjectSnapshotData.h` (Public)


#### struct `FClassDefaultObjectSnapshotData`  
`struct FClassDefaultObjectSnapshotData : public FObjectSnapshotData`  
_L11-18_
- reflection: `USTRUCT()`
- inherits: `FObjectSnapshotData`
- desc: We save the CDO of every object to save space. This holds the CDO's saved data.
- L17 _public member_ `bool bSerializationSkippedCDO = false;` — `UPROPERTY()` — Whether no data was saved because somebody called ILevelSnapshotsModule::AddSkippedClassDefault

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/ClassSnapshotData.h` (Public)


#### enum `ESnapshotClassFlags`  
`enum class ESnapshotClassFlags : uint8`  
_L10-18_
- reflection: `UENUM()`
- L12 _public enumerator_ `NoFlags = 0x00000000`
- L17 _public enumerator_ `SerializationSkippedArchetypeData = 0x00000001` — There is no data available for the archetype because Level Snapshots was configured so, e.g. ILevelSnapshotsModule::AddSkippedClassDefault was called.

#### struct `FClassSnapshotData`  
`struct FClassSnapshotData : public FObjectSnapshotData`  
_L28-45_
- reflection: `USTRUCT()`
- inherits: `FObjectSnapshotData`
- desc: Holds class information for a specific use of a class. Usually it holds the class archetype. Actor classes have exactly one instance of FClassSnapshotData. Subobjects can have multiple instances of FClassSnapshotData; in actors each subobject has its own archetype.
- L34 _public member_ `FSoftClassPath ClassPath;` — `UPROPERTY()` — The class getting saved.
- L38 _public member_ `uint64 ClassFlags {};` — `UPROPERTY()` — Flags of ClassPath, i.e. the class whose archetype was serialized
- L42 _public member_ `ESnapshotClassFlags SnapshotFlags = ESnapshotClassFlags::NoFlags;` — `UPROPERTY()` — Special flags about this class
- L44 _public function_ `EObjectFlags GetClassFlags() const`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/ComponentSnapshotData.h` (Public)


#### struct `FComponentSnapshotData`  
`struct FComponentSnapshotData`  
_L9-16_
- reflection: `USTRUCT()`
- L15 _public member_ `EComponentCreationMethod CreationMethod {};` — `UPROPERTY()` — Describes how the component was created

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/CustomSerializationData.h` (Public)


#### struct `FCustomSubbjectSerializationData`  
`struct FCustomSubbjectSerializationData : public FObjectSnapshotData`  
_L10-25_
- reflection: `USTRUCT()`
- inherits: `FObjectSnapshotData`
- L16 _public member_ `int32 ObjectPathIndex = INDEX_NONE;` — `UPROPERTY()` — Valid index to FWorldSnapshotData::SerializedObjectReferences
- L20 _public member_ `int32 ClassIndex = INDEX_NONE;` — `UPROPERTY()` — Valid index to FWorldSnapshotData::ClassData. Use to lookup class and archetype data.
- L24 _public member_ `TArray<uint8> SubobjectAnnotationData;` — `UPROPERTY()` — Additional custom data saved by ICustomSnapshotSerializationData

#### struct `FCustomSerializationData`  
`struct FCustomSerializationData`  
_L28-39_
- reflection: `USTRUCT()`
- L34 _public member_ `TArray<uint8> RootAnnotationData;` — `UPROPERTY()` — Additional custom data saved by ICustomSnapshotSerializationData
- L38 _public member_ `TArray<FCustomSubbjectSerializationData> Subobjects;` — `UPROPERTY()` — Data for all subobjects

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/Hashing/ActorSnapshotHash.h` (Public)


#### struct `FActorSnapshotHash`  
`struct FActorSnapshotHash`  
_L11-57_
- reflection: `USTRUCT()`
- desc: Every actor is hashed when it is saved so we can quickly check whether an actor has changed.
- L20 _public member_ `double MicroSecondsForCrc = -1.0;` — `UPROPERTY()` — How many micro seconds it took to compute the actor CRC32 during saving. Used when loading actors. If the hash time is excessively high, it is more efficient simply to load the actor. Configured in project settings.
- L24 _public member_ `double MicroSecondsForMD5 = -1.0;` — `UPROPERTY()` — How many micro seconds it took to compute the MD5 hash.
- L28 _public member_ `int32 Crc32DataLength {};` — `UPROPERTY()` — How many bytes of data were in the data were used for CRC32. Used to avoid computing hash.
- L32 _public member_ `int32 MD5DataLength {};` — `UPROPERTY()` — How many bytes of data were in the data were used for MD5. Used to avoid computing hash.
- L39 _public member_ `uint32 Crc32 {};` — `UPROPERTY()` — Crc32 hash of actor when it was snapshot. Used to check for changes without loading actor. Sometimes MD5 is faster. Cost is 0.0003s on "average" actors, like world settings.
- L46 _public member_ `FMD5Hash MD5;` — MD5 hash of actor when it was snapshot. Used to check for changes without loading actor. Sometimes CRC32 is faster. Cost is 0.0003s on "average" actors, like world settings. CRC32 is generally to be preferred but we do MD5 to future proof cases where there may be collisions. Users can configure this in project settings.
- L48 _public function_ `bool HasCrc32() const`
- L49 _public function_ `bool HasMD5() const`
- L56 _public prototype_ `bool Serialize(FArchive& Archive);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FActorSnapshotHash> : public TStructOpsTypeTraitsBase2<FActorSnapshotHash>`  
_L60-66_
- inherits: `TStructOpsTypeTraitsBase2<FActorSnapshotHash>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L63-65_

#### Free symbols / members of external scopes

- L64 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anone1a700430103`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/LevelSnapshot.h` (Public)


#### enum `ECachedDiffResult`  
`enum class ECachedDiffResult : uint8`  
_L13-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `NotInitialized` — The actor was not yet analysed
- L18 _public enumerator_ `HadChanges` — Actor was analysed and had changes
- L20 _public enumerator_ `HadNoChanges` — Actor was analysed and had no changes

#### class `ULevelSnapshot`  
`class ULevelSnapshot : public UObject`  
_L26-195_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Holds the state of a world at a given time. This asset can be used to rollback certain properties in a UWorld.
- L31 _public prototype_ `DECLARE_DELEGATE_OneParam(FActorPathConsumer, const FSoftObjectPath& );`
- L32 _public prototype_ `DECLARE_DELEGATE_OneParam(FActorConsumer, AActor* );`
- L33 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FSnapshotEvent);`
- L36 _public prototype_ `bool SnapshotWorld(UWorld* TargetWorld);` — Captures the current state of the given world.
- L39 _public prototype_ `void ApplySnapshotToWorld(UWorld* TargetWorld, const FPropertySelectionMap& SelectionSet);` — Applies this snapshot to the given world. We assume the world matches. SelectionSet specifies which properties to roll back.
- L49 _public prototype_ `bool HasChangedSinceSnapshotWasTaken(AActor* WorldActor);` — Checks whether the given actor has changes to the snapshot version. First compares hashes and then proceeds comparing property values. In most cases, this function is faster than HasOriginalChangedPropertiesSinceSnapshotWasTaken because it tries to slow calls to GetDeserializedActor by comparing hashes first.
- L57 _public prototype_ `bool HasOriginalChangedPropertiesSinceSnapshotWasTaken(AActor* SnapshotActor, AActor* WorldActor);` — Checks whether the original actor has any properties that changed since the snapshot was taken by comparing properties. Use this function instead of HasChangedSinceSnapshotWasTaken if you've already called GetDeserializedActor. Otherwise HasChangedSinceSnapshotWasTaken should be faster in most cases.
- L60 _public prototype_ `FString GetActorLabel(const FSoftObjectPath& OriginalActorPath) const;` — Gets the display label of the path of the actor. This is useful for the LS UI to display actor names, especially of removed actors.
- L63 _public prototype_ `TOptional<TNonNullPtr<AActor>> GetDeserializedActor(const FSoftObjectPath& OriginalActorPath);` — Given an actor path in the world, gets the equivalent actor from the snapshot.
- L66 _public prototype_ `TOptional<TNonNullPtr<UClass>> GetActorClass(const FSoftObjectPath& OriginalActorPath);` — Given an actor path in the world, gets its class from the snapshot.
- L69 _public prototype_ `int32 GetNumSavedActors() const;` — Gets the number of actors saved by this snapshot.
- L79 _public prototype_ `void DiffWorld(UWorld* World, FActorPathConsumer HandleMatchedActor, FActorPathConsumer HandleRemovedActor, FActorConsumer HandleAddedActor);` — `UE_DEPRECATED(5.1, "Use DiffWorld that accepts FActorConsumer for HandleMatchedActor instead.")` — Compares this snapshot to the world and calls the appropriate callbacks: @param World to check in @param HandleMatchedActor Actor exists both in world and snapshot. Receives the original actor path. @param HandleRemovedActor Actor exists in snapshot but not in world. Receives the original actor path. @param HandleAddedActor Actor exists in world but not in snapshot. Receives reference to world actor.
- L80 _public prototype_ `void DiffWorld(UWorld* World, FActorConsumer HandleMatchedActor, FActorPathConsumer HandleRemovedActor, FActorConsumer HandleAddedActor);`
- L85 _public prototype_ `void SetSnapshotName(const FName& InSnapshotName);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")` — Sets the name of this snapshot.
- L87 _public prototype_ `void SetSnapshotDescription(const FString& InSnapshotDescription);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")`
- L90 _public function_ `FSoftObjectPath GetMapPath() const` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")`
- L92 _public function_ `FDateTime GetCaptureTime() const` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")`
- L94 _public function_ `FName GetSnapshotName() const` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")`
- L96 _public function_ `FString GetSnapshotDescription() const` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")`
- L98 _public function_ `const FWorldSnapshotData& GetSerializedData() const`
- L99 _public function_ `const FSnapshotDataCache& GetCache() const`
- L101 _public function_ `FSnapshotEvent& OnPreApplySnapshot()`
- L102 _public function_ `FSnapshotEvent& OnPostApplySnapshot()`
- L113 _public function_ `void EnableDiffCacheSupport()` — Indicates that user code is aware that ClearCachedDiffFlag must be called manually. In editor builds, the transaction system calls ClearCachedDiffFlag but in non-editor builds the transaction system does not exist. Enables the use of CachedDiffedActors.
- L116 _public prototype_ `void ResetDiffCacheToUninitialized(TArrayView<AActor*> ModifiedActors);` — Clears the diff state of the actor. Designed to be called by the transaction system (or manually in non-editor builds if EnableDiffCacheSupport has been called).
- L117 _public prototype_ `void ResetDiffCacheToUninitialized(UObject* ModifiedObject);`
- L120 _public prototype_ `virtual void BeginDestroy() override;`
- L125 _private prototype_ `FString GenerateDebugLogInfo() const;`
- L127 _private prototype_ `void EnsureWorldInitialised();`
- L128 _private prototype_ `void DestroyWorld();`
- L129 _private prototype_ `void CleanUpWorld();`
- L130 _private prototype_ `void ClearCache();`
- L132 _private prototype_ `void RecreateSnapshotWorld();`
- L135 _private member_ `FDelegateHandle Handle;` — Callback to destroy our world when editor (editor build) or play (game builds) world is destroyed.
- L137 _private member_ `FDelegateHandle OnObjectModifiedHandle;` — Callback to when an object is modified. Clears FActorSnapshotData::bHasBeenDiffed
- L143 _private member_ `TObjectPtr<UPackage> TransientWorldPackage;` — `UPROPERTY(Transient)` — Transient package that contains the world. Exists so calls to MarkPackageDirty, called e.g. by AActor::Modify, do not mark the snapshot dirty.
- L147 _private member_ `TObjectPtr<UWorld> RootSnapshotWorld;` — `UPROPERTY(Transient)` — The root world, equivalent to the persistent world, we will be adding temporary actors to
- L150 _private member_ `TArray<TObjectPtr<UWorld>> SnapshotSublevels;` — `UPROPERTY(Transient)` — Sublevels of RootSnapshotWorld
- L154 _private member_ `FWorldSnapshotData SerializedData;` — `UPROPERTY()` — The saved snapshot data
- L158 _private member_ `FSnapshotDataCache Cache;` — `UPROPERTY(Transient)` — Holds all loaded objects
- L170 _private member_ `bool bIsDiffCacheEnabled = false;` — `UPROPERTY(Transient)` — Only used in non-editor builds (should be wrapped in !WITH_EDITORONLY_DATA but UHT does not allow it). Indicates that user code is aware that ClearCachedDiffFlag must be called manually. In editor builds, the transaction system calls ClearCachedDiffFlag but in non-editor builds the transaction system does not exist. Enables the use of CachedDiffedActors.
- L174 _private member_ `TMap<TWeakObjectPtr<AActor>, ECachedDiffResult> CachedDiffedActors;` — `UPROPERTY(Transient)` — Caches whether an actor was diffed already
- L179 _private member_ `FSoftObjectPath MapPath;` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetMapPath", AssetRegistrySearchable, Category = "Level Snapshots")` — Path of the map that the snapshot was taken in
- L183 _private member_ `FDateTime CaptureTime;` — `UPROPERTY(AssetRegistrySearchable, BlueprintGetter = "GetCaptureTime", VisibleAnywhere, Category = "Level Snapshots")` — UTC Time that the snapshot was taken
- L187 _private member_ `FName SnapshotName;` — `UPROPERTY(AssetRegistrySearchable, BlueprintGetter = "GetSnapshotName", EditAnywhere, Category = "Level Snapshots")` — User defined name for the snapshot, can differ from the actual asset name.
- L191 _private member_ `FString SnapshotDescription;` — `UPROPERTY(AssetRegistrySearchable, BlueprintGetter = "GetSnapshotDescription", EditAnywhere, Category = "Level Snapshots")` — User defined description of the snapshot
- L193 _private member_ `FSnapshotEvent OnPreApplySnapshotDelegate;`
- L194 _private member_ `FSnapshotEvent OnPostApplySnapshotDelegate;`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FActorPathConsumer, const FSoftObjectPath& );`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FActorConsumer, AActor* );`
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE(FSnapshotEvent);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/ObjectSnapshotData.h` (Public)


#### struct `FObjectSnapshotData`  
`struct FObjectSnapshotData`  
_L10-22_
- reflection: `USTRUCT()`
- desc: Shared data all saved objects in Level Snapshots have.
- L15 _public member_ `TArray<uint8> SerializedData;` — `UPROPERTY()`
- L19 _public member_ `uint64 ObjectFlags = RF_Transactional;` — `UPROPERTY()` — Flags of the object that was serialized
- L21 _public function_ `EObjectFlags GetObjectFlags() const`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/SnapshotCustomVersion.h` (Public)


#### struct `UE::LevelSnapshots::FSnapshotCustomVersion`  
`struct FSnapshotCustomVersion`  
_L10-71_
- L67 _public member_ `const static FGuid GUID;`
- L70 _private prototype_ `FSnapshotCustomVersion() = delete;`

#### enum `UE::LevelSnapshots::FSnapshotCustomVersion::Type`  
`enum Type`  
_L12-65_
- L15 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L18 _public enumerator_ `SubobjectSupport = 1` — When subobject support was added. Specifically, USceneComponent::AttachParent were not captured.
- L21 _public enumerator_ `ActorHash = 2` — FSnapshotActorData now stores actor hash data to facilitate checking whether an actor has changed without loading the actor
- L24 _public enumerator_ `ClassArchetypeRefactor = 3` — FWorldSnapshotData::ClassDefaults was replaced by FWorldSnapshotData::ClassData.
- L27 _public enumerator_ `OoddleCompression = 4` — FWorldSnapshotData now compresses data using Oodle before it is saved to disk
- L30 _public enumerator_ `CustomSubobjectSoftObjectPathRefactor = 5` — Before this soft object references were saved by FCustomSerializationDataWriter using FObjectAndNameAsStringProxyArchive - if you moved the asset our data would get corrupted.
- L36 _public enumerator_ `SkipSubobjectReferencesWhenSerializingArchetypesRefactor = 6` — When serializing a class archetype, we now skip properties that contain subobjects by discovering reference properties with a reference collector archive. No migration needs to take place. This entry exists only for future proofing (in case something breaks).
- L43 _public enumerator_ `NonEditableComponentsAreCaptured = 7` — If FComponentEditorUtils::CanEditComponentInstance returned false, the snapshot would not be captured. Now, if FComponentEditorUtils::CanEditComponentInstance returns false the component will still be captured if it is a root component; otherwise the actor's transform cannot be restored. No migration needs to take place. This entry exists only for future proofing (in case something breaks).
- L46 _public enumerator_ `FixActorHashSerialize = 8` — FActorSnapshotHash::Serialize was not implemented correctly (typo with TStructOpsTypeTraits using WithSerialize instead of WithSerializer).
- L60 _public enumerator_ `FoliageTypesUnreadable = 9` — Change 21419024 of 16/08/2022 (which introduced CustomSubobjectSoftObjectPathRefactor above) causes UE::LevelSnapshots::Foliage::Private::FInstancedFoliageActorData to save foliage data in a bad format. Any foliage data from 16/08/2022 to 30/03/2023 is unusable. That means that 5.0 is not affected, 5.1 is broken, and 5.2 is fixed. The issue is that FInstancedFoliageActorData::Save, called by FFoliageSupport::OnTakeSnapshot, called AInstancedFoliageActor::ForEachFoliageInfo and saved the foliage types sequentially. The issue is that we differentiate between instanced subobject and asset foliage types; they were saved interleaved without tagging the data, which makes it impossible to read (e.g. subject1 > asset1 > asset2 > subject 2, etc.).
- L63 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L64 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/SnapshotDataCache.h` (Public)


#### struct `FActorSnapshotCache`  
`struct FActorSnapshotCache`  
_L11-32_
- reflection: `USTRUCT()`
- L16 _public member_ `TWeakObjectPtr<AActor> CachedSnapshotActor = nullptr;` — `UPROPERTY()`
- L25 _public member_ `bool bReceivedSerialisation = false;` — `UPROPERTY()` — Whether we already serialised the snapshot data into the actor. This exists because sometimes we need to preallocate an actor without serialisation. Example: When serializing another actor which referenced this actor.
- L31 _public member_ `TArray<int32> ObjectDependencies;` — `UPROPERTY()` — Stores all object dependencies. Only valid if bReceivedSerialisation == true.

#### struct `FSubobjectSnapshotCache`  
`struct FSubobjectSnapshotCache`  
_L35-46_
- reflection: `USTRUCT()`
- L41 _public member_ `TObjectPtr<UObject> SnapshotObject = nullptr;` — `UPROPERTY()` — Allocated in snapshot world
- L45 _public member_ `TWeakObjectPtr<UObject> EditorObject = nullptr;` — `UPROPERTY()` — Allocated in editor world

#### struct `FClassDefaultSnapshotCache`  
`struct FClassDefaultSnapshotCache`  
_L49-55_
- reflection: `USTRUCT()`
- L54 _public member_ `TObjectPtr<UObject> CachedLoadedClassDefault = nullptr;` — `UPROPERTY()`

#### struct `FSnapshotDataCache`  
`struct FSnapshotDataCache`  
_L59-101_
- reflection: `USTRUCT()`
- desc: Caches data for re-use.
- L64 _public member_ `TMap<FSoftObjectPath, FActorSnapshotCache> ActorCache;` — `UPROPERTY()`
- L67 _public member_ `TMap<FSoftObjectPath, FSubobjectSnapshotCache> SubobjectCache;` — `UPROPERTY()`
- L76 _public member_ `TArray<TObjectPtr<UObject>> ArchetypeObjects;` — `UPROPERTY()` — Caches each archetype object for faster lookup. Equal length as FWorldSnapshotData::ClassData and the indices correspond to another. Elements can be null in which case there is no cache, yet.
- L85 _public member_ `TArray<TOptional<FClassSnapshotData>> FallbackArchetypeData;` — Fallback for ClassData. Equal length as ClassData and the indices correspond to another. When we fail to archetype data in ClassData, we look for the most appropriate archetype and cache it here. Archetype data may be missing because this snapshot is old (was not saved) or because it was explicitly skipped by user config.
- L87 _public function_ `void InitFor(const FWorldSnapshotData& SnapshotData)`
- L94 _public function_ `void Reset()`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/SnapshotUtilTypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L10 _typedef_ `using FClassDataIndex = uint32;` (scope `UE::LevelSnapshots`) — An index to FWorldSnapshotData::ClassData.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/SnapshotVersion.h` (Public)


#### struct `FSnapshotFileVersionInfo`  
`struct FSnapshotFileVersionInfo`  
_L14-34_
- reflection: `USTRUCT()`
- desc: Holds file version information
- L19 _public prototype_ `void Initialize();` — Initialize this version info from the compiled in data
- L21 _public prototype_ `FString ToString() const;`
- L25 _public member_ `int32 FileVersionUE4 = VER_LATEST_ENGINE_UE4;` — `UPROPERTY()` — UE4 File version
- L29 _public member_ `int32 FileVersionUE5 = 0;` — `UPROPERTY()` — UE5 File version
- L33 _public member_ `int32 FileVersionLicensee = 0;` — `UPROPERTY()` — Licensee file version

#### struct `FSnapshotEngineVersionInfo`  
`struct FSnapshotEngineVersionInfo`  
_L38-62_
- reflection: `USTRUCT()`
- desc: Holds engine version information
- L43 _public prototype_ `void Initialize(const FEngineVersion& InVersion);` — Initialize this version info from the given version
- L45 _public prototype_ `FString ToString() const;`
- L49 _public member_ `uint16 Major = 0;` — `UPROPERTY()` — Major version number
- L53 _public member_ `uint16 Minor = 0;` — `UPROPERTY()` — Minor version number
- L57 _public member_ `uint16 Patch = 0;` — `UPROPERTY()` — Patch version number
- L61 _public member_ `uint32 Changelist = 0;` — `UPROPERTY()` — Changelist number. This is used to arbitrate when Major/Minor/Patch version numbers match

#### struct `FSnapshotCustomVersionInfo`  
`struct FSnapshotCustomVersionInfo`  
_L66-90_
- reflection: `USTRUCT()`
- desc: Holds custom version information
- L71 _public prototype_ `void Initialize(const FCustomVersion& InVersion);` — Initialize this version info from the given version
- L81 _public member_ `FName FriendlyName;` — `UPROPERTY()` — Friendly name of the version
- L85 _public member_ `FGuid Key;` — `UPROPERTY()` — Unique custom key
- L89 _public member_ `int32 Version = 0;` — `UPROPERTY()` — Custom version

#### struct `FSnapshotVersionInfo`  
`struct FSnapshotVersionInfo`  
_L94-120_
- reflection: `USTRUCT()`
- desc: Holds version information for a session
- L99 _public prototype_ `void Initialize(bool bWithoutSnapshotVersion = false);` — Initialize this version info from the compiled in data
- L100 _public prototype_ `bool IsInitialized() const;`
- L102 _public prototype_ `void ApplyToArchive(FArchive& Archive) const;`
- L104 _public prototype_ `FString ToString() const;`
- L107 _public prototype_ `int32 GetSnapshotCustomVersion() const;` — @return The saved version for this plugin or -1 if none is available.
- L111 _public member_ `FSnapshotFileVersionInfo FileVersion;` — `UPROPERTY()` — File version info
- L115 _public member_ `FSnapshotEngineVersionInfo EngineVersion;` — `UPROPERTY()` — Engine version info
- L119 _public member_ `TArray<FSnapshotCustomVersionInfo> CustomVersions;` — `UPROPERTY()` — Custom version info

#### Free symbols / members of external scopes

- L73 _function_ `friend FArchive& operator<<(FArchive& Archive, FSnapshotCustomVersionInfo& VersionInfo)`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/SubobjectSnapshotData.h` (Public)


#### struct `FSubobjectSnapshotData`  
`struct FSubobjectSnapshotData : public FObjectSnapshotData`  
_L12-40_
- reflection: `USTRUCT()`
- inherits: `FObjectSnapshotData`
- desc: Data saved for subobjects, such as components.
- L16 _public function_ `static FSubobjectSnapshotData MakeSkippedSubobjectData()`
- L25 _public member_ `int32 OuterIndex = INDEX_NONE;` — `UPROPERTY()` — Index to FWorldSnapshotData::SerializedObjectReferences
- L28 _public member_ `FSoftClassPath Class_DEPRECATED;` — `UPROPERTY()`
- L32 _public member_ `int32 ClassIndex = INDEX_NONE;` — `UPROPERTY()` — Valid index to FWorldSnapshotData::ClassData. Use to lookup class and archetype data.
- L36 _public member_ `bool bWasSkippedClass = false;` — `UPROPERTY()` — Whether this object was marked as unsupported when the snapshot was taken
- L39 _public function_ `UE::LevelSnapshots::FClassDataIndex GetClassDataIndex() const` — "Type safety" for better self-documenting code

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Data/WorldSnapshotData.h` (Public)


#### struct `FWorldSnapshotData`  
`struct FWorldSnapshotData`  
_L24-133_
- reflection: `USTRUCT()`
- desc: Holds saved world data. See WorldDataUtil for operations.
- L28 _public prototype_ `void ForEachOriginalActor(TFunctionRef<void(const FSoftObjectPath& ActorPath, const FActorSnapshotData& SavedData)> HandleOriginalActorPath) const;`
- L29 _public prototype_ `bool HasMatchingSavedActor(const FSoftObjectPath& OriginalObjectPath) const;`
- L32 _public prototype_ `bool Serialize(FArchive& Ar);`
- L33 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L38 _public member_ `TWeakObjectPtr<UWorld> SnapshotWorld;` — `UPROPERTY(Transient)` — The root world we will be adding deserialized snapshots actors to
- L41 _public member_ `TArray<TObjectPtr<UWorld>> SnapshotSublevels;` — `UPROPERTY(Transient)` — Sublevels of SnapshotWorld; excludes SnapshotWorld->PersistentLevel
- L48 _public member_ `FSnapshotVersionInfo SnapshotVersionInfo;` — `UPROPERTY()` — Stores versioning information we inject into archives. This is to support asset migration, like FArchive::UsingCustomVersion.
- L57 _public member_ `TMap<FSoftClassPath, FClassDefaultObjectSnapshotData> ClassDefaults_DEPRECATED;` — `UPROPERTY()` — We only save properties with values different from their CDO counterpart. Because of this, we need to save class defaults in the snapshot.
- L69 _public member_ `TArray<FClassSnapshotData> ClassData;` — `UPROPERTY()` — Saves class info, such as archetype data, for every object's class. Actor classes have exactly one entry FClassSnapshotData::FClassSnapshotData. For other classes, e.g. components, there may be multiple entries for the same class. This is because subobjects can have their own archtetypes (you can see this by looking a the reset to default button in the details panel). Added in 5.1.
- L78 _public member_ `TMap<FSoftObjectPath, FActorSnapshotData> ActorData;` — `UPROPERTY()` — Holds serialized actor data. Maps the original actor's path to its serialized data.
- L85 _public member_ `TArray<FName> SerializedNames;` — `UPROPERTY()` — Whenever an object needs to serialize a name, we add it to this array and serialize an index to this array.
- L99 _public member_ `TArray<FSoftObjectPath> SerializedObjectReferences;` — `UPROPERTY()` — Whenever an object needs to serialize an object reference, we keep the object path here and serialize an index to this array. External references, e.g. UDataAssets or UMaterials, are easily handled. Example: UStaticMesh /Game/Australia/StaticMeshes/MegaScans/Nature_Rock_vbhtdixga/vbhtdixga_LOD0.vbhtdixga_LOD0 Internal references, e.g. to subobjects and to other actors in the world, are a bit tricky. For internal references, we need to do some translation: Example original: UStaticMeshActor::StaticMeshComponent /Game/MapName.MapName:PersistentLevel.StaticMeshActor_42.StaticMeshComponent Example translated: UStaticMeshActor::StaticMeshComponent /Engine/Transient.World_21:PersistentLevel.StaticMeshActor_42.StaticMeshComponent
- L109 _public member_ `TMap<int32, FSubobjectSnapshotData> Subobjects;` — `UPROPERTY()` — Key: A valid index to SerializedObjectReferences. Value: Subobject information for the associated entry in SerializedObjectReferences. There is only an entry if the associated object is in fact a subobject. Actors and assets in particular do not get any entry. Added in 5.0.
- L118 _public member_ `TMap<int32, FCustomSerializationData> CustomSubobjectSerializationData;` — `UPROPERTY()` — Key: A valid index to SerializedObjectReferences Value: Data that was generated by some ICustomObjectSnapshotSerializer. Added in 5.0.
- L124 _public member_ `TMap<FName, int32> NameToIndex;` — `UPROPERTY(Transient)` — Binds every entry in SerializedNames to its index. Speeds up adding unique names.
- L128 _public member_ `TMap<FSoftObjectPath, int32> ReferenceToIndex;` — `UPROPERTY(Transient)` — Binds every entry in SerializedObjectReferences to its index. Speeds up adding unique references.
- L132 _public member_ `TMap<TObjectPtr<UObject>, uint32> ArchetypeToClassDataIndex;` — `UPROPERTY(Transient)` — Binds every archetype object for which we saved the class data in ClassData to its index. Speeds up adding unique classes.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FWorldSnapshotData> : public TStructOpsTypeTraitsBase2<FWorldSnapshotData>`  
_L136-143_
- inherits: `TStructOpsTypeTraitsBase2<FWorldSnapshotData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L139-142_

#### Free symbols / members of external scopes

- L140 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anond1ed1f970103`)
- L141 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anond1ed1f970103`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Filtering/AddedAndRemovedComponentInfo.h` (Public)


#### struct `UE::LevelSnapshots::FAddedAndRemovedComponentInfo`  
`struct FAddedAndRemovedComponentInfo`  
_L13-26_
- desc: Holds all properties that should be restored for an object.
- L19 _public member_ `TSet<TWeakObjectPtr<UActorComponent>> EditorWorldComponentsToRemove;` — New components added to the actor after the snapshot was taken. Remove them from the original actor. Point to instances in the editor world.
- L25 _public member_ `TSet<TWeakObjectPtr<UActorComponent>> SnapshotComponentsToAdd;` — Components that were removed from the actor after the snapshot was taken. Add them to the original actor. Point to instances in the snapshot world.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Filtering/CustomSubobjectRestorationInfo.h` (Public)


#### struct `UE::LevelSnapshots::FCustomSubobjectRestorationInfo`  
`struct FCustomSubobjectRestorationInfo`  
_L12-19_
- desc: Holds all properties that should be restored for an object.
- L18 _public member_ `TSet<TWeakObjectPtr<UObject>> CustomSnapshotSubobjectsToRestore;` — Subobjects from snapshot world which were discovered using ICustomObjectSnapshotSerializer. Recreate the equivalent subobject in the editor world.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Filtering/PropertySelection.h` (Public)


#### struct `FLevelSnapshotPropertyChain`  
`struct FLevelSnapshotPropertyChain : FArchiveSerializedPropertyChain`  
_L14-46_
- inherits: `FArchiveSerializedPropertyChain`
- desc: Uniquely identifies a property across structs. Primarily this is used by serialisation code hence we pass in FArchiveSerializedPropertyChain often. However, inheritance from FArchiveSerializedPropertyChain is an implementation detail.
- L16 _public typedef_ `using Super = FArchiveSerializedPropertyChain;`
- L23 _public prototype_ `FLevelSnapshotPropertyChain() = default;`
- L24 _public prototype_ `FLevelSnapshotPropertyChain(const FProperty* RootProperty);`
- L25 _public prototype_ `FLevelSnapshotPropertyChain(const FArchiveSerializedPropertyChain* ChainToLeaf, const FProperty* LeafProperty);`
- L27 _public prototype_ `FLevelSnapshotPropertyChain MakeAppended(const FProperty* Property) const;`
- L28 _public prototype_ `void AppendInline(const FProperty* Property);`
- L31 _public prototype_ `static TOptional<FLevelSnapshotPropertyChain> FindPathToProperty( const FProperty* InLeafProperty, const UStruct* InStructToSearch, const bool bIncludeLeafPropertyInChain = true);` — Returns an FLevelSnapshotPropertyChain given a leaf property and a UScriptStruct or UClass.
- L34 _public prototype_ `FString ToString() const;`
- L42 _public prototype_ `bool EqualsSerializedProperty(const FArchiveSerializedPropertyChain* ContainerChain, const FProperty* LeafProperty) const;` — Checks whether a given property being serialized corresponds to this chain. @param ContainerChain The chain of properties to the most nested owning struct: See FArchive::GetSerializedPropertyChain. @param LeafProperty The leaf property in the struct
- L44 _public prototype_ `bool IsEmpty() const;`
- L45 _public prototype_ `bool operator==(const FLevelSnapshotPropertyChain& InPropertyChain) const;`

#### struct `FPropertySelection`  
`struct FPropertySelection`  
_L49-109_
- desc: Holds all properties that should be restored for an object.
- L51 _public prototype_ `FPropertySelection() = default;`
- L52 _public prototype_ `FPropertySelection(const FProperty* SingleProperty);`
- L54 _public prototype_ `FPropertySelection(const TSet<const FProperty*>& Properties);` — Note: all properties must be root properties (i.e. not within structs or collections). Check yourself, this is not checked.
- L68 _public prototype_ `bool ShouldSerializeProperty(const FArchiveSerializedPropertyChain* ContainerChain, const FProperty* LeafProperty) const;` — Checks whether the given property should be serialized. It should be serialized if: - IsPropertySelected() returns true on the property - The property is inside of a collection for which IsPropertySelected() returns true - The property is not part of a struct for which IsPropertySelected() returns true; this happens when a struct implements a custom serializer and pushes other structs. As performance optimisation, we assume this function is called by FArchive::ShouldSkipProperty, i.e. ShouldSerializeProperty would return true on the elements of ContainerChain. @param ContainerChain The chain of properties to the most nested owning struct: See FArchive::GetSerializedPropertyChain. @param LeafProperty The leaf property in the struct
- L75 _public prototype_ `bool IsPropertySelected(const FArchiveSerializedPropertyChain* ContainerChain, const FProperty* LeafProperty) const;` — Checks whether the given property is in this selection. When serializing, you probably want to be using ShouldSerializeProperty. @param ContainerChain The chain of properties to the most nested owning struct: See FArchive::GetSerializedPropertyChain. @param LeafProperty The leaf property in the struct
- L77 _public prototype_ `bool IsEmpty() const;`
- L79 _public function_ `void SetHasCustomSerializedSubobjects(bool bValue)`
- L80 _public function_ `bool HasCustomSerializedSubobjects() const`
- L82 _public prototype_ `void AddProperty(const FLevelSnapshotPropertyChain& SelectedProperty);`
- L83 _public prototype_ `void RemoveProperty(const FArchiveSerializedPropertyChain* ContainerChain, const FProperty* LeafProperty);`
- L85 _public prototype_ `void RemoveProperty(FArchiveSerializedPropertyChain* ContainerChain);`
- L88 _public prototype_ `const TArray<TFieldPath<FProperty>>& GetSelectedLeafProperties() const;` — Gets a flat list of all selected properties. The result contains no information what nested struct a property came from.
- L90 _public prototype_ `const TArray<FLevelSnapshotPropertyChain>& GetSelectedProperties() const;`
- L94 _private prototype_ `int32 FindPropertyChain(const FArchiveSerializedPropertyChain* ContainerChain, const FProperty* LeafProperty) const;`
- L97 _private member_ `bool bHasCustomSerializedSubobjects = false;` — Whether some ICustomObjectSnapshotSerializer has changed subobjects
- L100 _private member_ `TArray<TFieldPath<FProperty>> SelectedLeafProperties;` — Duplicate version of SelectedProperties with the struct-path leading to the property left out. Needed to build UI more easily.
- L108 _private member_ `TArray<FLevelSnapshotPropertyChain> SelectedProperties;` — These are the properies that need to be restored. Key: First property name of property in chain. Value: All chains associated that have the Key property has first property. Mapping it out like this allows us to search less properties.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Filtering/PropertySelectionMap.h` (Public)


#### struct `FPropertySelectionMap`  
`struct FPropertySelectionMap`  
_L17-113_
- desc: Binds an object to its selected properties
- L24 _public prototype_ `void AddDeletedActorToRespawn(const FSoftObjectPath& Original);` — Respawn the actor from the data in the snapshot.
- L25 _public prototype_ `void RemoveDeletedActorToRespawn(const FSoftObjectPath& Original);`
- L28 _public prototype_ `void AddNewActorToDespawn(AActor* WorldActor);` — Destroy the given actors when a snapshot is applied.
- L29 _public prototype_ `void RemoveNewActorToDespawn(AActor* WorldActor);`
- L34 _public prototype_ `bool AddObjectProperties(UObject* WorldObject, const FPropertySelection& SelectedProperties);` — Binds properties to an object which are supposed to be rolled back.
- L35 _public prototype_ `void RemoveObjectPropertiesFromMap(UObject* WorldObject);`
- L49 _public prototype_ `void MarkSubobjectForRestoringReferencesButSkipProperties(UObject* WorldSubbject);` — Tracks a subobject so we only restore references pointing to it but not serialize its properties. When applying a snapshot to world and resolving subobjects, it is unclear whether a resolved references is either 1. a reference to a preexisting, valid subobject: for it we use only restored selected properties. 2. a reference to an old, deleted subobject which still exists in memory: for it we restore all properties. See SnapshotUtil::Object::ResolveObjectDependencyForEditorWorld for more info.
- L50 _public prototype_ `bool IsSubobjectMarkedForReferenceRestorationOnly(const FSoftObjectPath& WorldSubobjectPath) const;`
- L53 _public prototype_ `void AddComponentSelection(AActor* EditorWorldActor, const UE::LevelSnapshots::FAddedAndRemovedComponentInfo& ComponentSelection);`
- L54 _public prototype_ `void RemoveComponentSelection(AActor* EditorWorldActor);`
- L59 _public prototype_ `void AddCustomEditorSubobjectToRecreate(UObject* EditorWorldOwner, UObject* SnapshotSubobject);` — Recreate a Custom subobject that exists in snapshot world but is missing from editor world. Used for subobjects discovered via ICustomObjectSnapshotSerializer
- L60 _public prototype_ `void RemoveCustomEditorSubobjectToRecreate(UObject* EditorWorldOwner, UObject* SnapshotSubobject);`
- L64 _public prototype_ `UE::LevelSnapshots::FRestorableObjectSelection GetObjectSelection(const FSoftObjectPath& EditorWorldObject) const;`
- L65 _public prototype_ `TArray<FSoftObjectPath> GetKeys() const;`
- L66 _public prototype_ `void ForEachModifiedObject(TFunctionRef<void(const FSoftObjectPath&)> Callback) const;`
- L67 _public prototype_ `bool HasAnyModifiedActors() const;`
- L69 _public prototype_ `bool HasChanges(AActor* EditorWorldActor) const;`
- L70 _public prototype_ `bool HasChanges(UActorComponent* EditorWorldComponent) const;`
- L71 _public prototype_ `bool HasChanges(UObject* EditorWorldObject) const;`
- L73 _public function_ `int32 GetKeyCount() const`
- L74 _public function_ `const TSet<FSoftObjectPath>& GetDeletedActorsToRespawn() const`
- L75 _public function_ `const TSet<TWeakObjectPtr<AActor>>& GetNewActorsToDespawn() const`
- L77 _public prototype_ `void Empty(bool bCanShrink = true);`
- L80 _public prototype_ `TArray<UObject*> GetDirectSubobjectsWithProperties(UObject* Root) const;` — Gets the direct subobjects of root that have selected properties. You can recursively call this function with the element of the result array.
- L88 _private member_ `TMap<FSoftObjectPath, FPropertySelection> EditorWorldObjectToSelectedProperties;` — Maps an editor world actor to the properties that should be restored to values in a snapshot. The properties are located in the actor itself. Subobjects have a separate key.
- L93 _private member_ `TMap<FSoftObjectPath, UE::LevelSnapshots::FAddedAndRemovedComponentInfo> EditorActorToComponentSelection;` — Maps an editor world actor to the components that should be added or removed.
- L98 _private member_ `TMap<FSoftObjectPath, UE::LevelSnapshots::FCustomSubobjectRestorationInfo> EditorWorldObjectToCustomSubobjectSelection;` — Maps an editor world object to the custom subobjects discovered by ICustomObjectSnapshotSerializer which need restoring.
- L103 _private member_ `TSet<FSoftObjectPath> SubobjectsMarkedForReferencesRestorationOnly;` — Contains objects which we do not serialize into: only replace references to them.
- L109 _private member_ `TSet<FSoftObjectPath> DeletedActorsToRespawn;` — These actors were removed since the snapshot was taken. Re-create them. This contains the original objects paths stored in the snapshot.
- L112 _private member_ `TSet<TWeakObjectPtr<AActor>> NewActorsToDespawn;` — These actors were added since the snapshot was taken. Remove them.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Filtering/RestorableObjectSelection.h` (Public)


#### class `UE::LevelSnapshots::FRestorableObjectSelection`  
`class FRestorableObjectSelection`  
_L18-36_
- L22 _private member_ `const FSoftObjectPath ObjectPath;`
- L23 _private member_ `const FPropertySelectionMap& Owner;`
- L25 _private function_ `FRestorableObjectSelection(const FSoftObjectPath& ObjectPath, const FPropertySelectionMap& Owner) : ObjectPath(ObjectPath), Owner(Owner)`
- L33 _public prototype_ `const FPropertySelection* GetPropertySelection() const;`
- L34 _public prototype_ `const FAddedAndRemovedComponentInfo* GetComponentSelection() const;`
- L35 _public prototype_ `const FCustomSubobjectRestorationInfo* GetCustomSubobjectSelection() const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/ILevelSnapshotsModule.h` (Public)


#### struct `UE::LevelSnapshots::FPreTakeSnapshotEventData`  
`struct FPreTakeSnapshotEventData`  
_L21-25_
- L23 _public member_ `ULevelSnapshot* Snapshot;`
- L24 _public member_ `UWorld* World;`

#### struct `UE::LevelSnapshots::FPostTakeSnapshotEventData`  
`struct FPostTakeSnapshotEventData`  
_L27-31_
- L29 _public member_ `ULevelSnapshot* Snapshot;`
- L30 _public member_ `UWorld* World;`

#### class `UE::LevelSnapshots::ILevelSnapshotsModule`  
`class ILevelSnapshotsModule : public IModuleInterface`  
_L33-157_
- inherits: `IModuleInterface`
- L37 _public function_ `static ILevelSnapshotsModule& Get()`
- L42 _public function_ `static bool IsAvailable()`
- L48 _public prototype_ `DECLARE_EVENT_OneParam(ILevelSnapshotsModule, FPreTakeSnapshotEvent, const FPreTakeSnapshotEventData&);`
- L50 _public function_ `FPreTakeSnapshotEvent& OnPreTakeSnapshot()` — Called before a snapshot is taken.
- L52 _public prototype_ `DECLARE_EVENT_OneParam(ILevelSnapshotsModule, FPostTakeSnapshotEvent, const FPostTakeSnapshotEventData&);`
- L54 _public function_ `FPostTakeSnapshotEvent& OnPostTakeSnapshot()` — Called after a snapshot is taken
- L57 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanTakeSnapshot, const FPreTakeSnapshotEventData&);`
- L59 _public prototype_ `virtual void AddCanTakeSnapshotDelegate(FName DelegateName, FCanTakeSnapshot Delegate) = 0;` — Add a named delegate that determines if we can take a snapshot.
- L62 _public prototype_ `virtual void RemoveCanTakeSnapshotDelegate(FName DelegateName) = 0;` — Remove previously added named delegate that determines if we can take a snapshot.
- L65 _public prototype_ `virtual bool CanTakeSnapshot(const FPreTakeSnapshotEventData& Event) const = 0;` — Queries the attached snapshot delegate and determines if we can take a snapshot.
- L69 _public prototype_ `virtual void AddSkippedSubobjectClasses(const TSet<UClass*>& Classes) = 0;` — Snapshots will no longer capture nor restore subobjects of this class. Subclasses are implicitly skipped as well.
- L70 _public prototype_ `virtual void RemoveSkippedSubobjectClasses(const TSet<UClass*>& Classes) = 0;`
- L74 _public prototype_ `virtual void RegisterRestorabilityOverrider(TSharedRef<ISnapshotRestorabilityOverrider> Overrider) = 0;` — Registers callbacks that override which actors, components, and properties are restored by default.
- L76 _public prototype_ `virtual void UnregisterRestorabilityOverrider(const TSharedRef<ISnapshotRestorabilityOverrider>& Overrider) = 0;` — Unregisters an overrider previously registered.
- L80 _public prototype_ `virtual void RegisterPropertyComparer(UClass* Class, TSharedRef<IPropertyComparer> Comparer) = 0;` — Registers a callback for deciding whether a property should be considered changed. Applies to all sub-classes.
- L81 _public prototype_ `virtual void UnregisterPropertyComparer(UClass* Class, const TSharedRef<IPropertyComparer>& Comparer) = 0;`
- L92 _public prototype_ `virtual void RegisterCustomObjectSerializer(UClass* Class, TSharedRef<ICustomObjectSnapshotSerializer> CustomSerializer, bool bIncludeBlueprintChildClasses = true) = 0;` — Registers callbacks for snapshotting / restoring certain classes. There can only be one per class. The typical use case using  Level Snapshots for restoring subobjects you want recreate / find manually. @param Class The class to register. This must be a native class (because Blueprint classes may be reinstanced when recompiled - not supported atm). @param CustomSerializer Your callbacks @param bIncludeBlueprintChildClasses Whether to use 'CustomSerializer' for Blueprint child classes of 'Class'
- L93 _public prototype_ `virtual void UnregisterCustomObjectSerializer(UClass* Class) = 0;`
- L97 _public prototype_ `virtual void RegisterGlobalActorFilter(TSharedRef<IActorSnapshotFilter> Filter) = 0;` — Registers callbacks for external systems to decide whether a given actor can be modified, recreated, or removed from the world.
- L98 _public prototype_ `virtual void UnregisterGlobalActorFilter(const TSharedRef<IActorSnapshotFilter>& Filter) = 0;`
- L102 _public prototype_ `virtual void RegisterSnapshotLoader(TSharedRef<ISnapshotLoader> Loader) = 0;` — Register an object that will receive callbacks when a snapshot is loaded
- L103 _public prototype_ `virtual void UnregisterSnapshotLoader(const TSharedRef<ISnapshotLoader>& Loader) = 0;`
- L107 _public prototype_ `virtual void RegisterRestorationListener(TSharedRef<IRestorationListener> Listener) = 0;` — Registers an object that will receive callbacks when a snapshot is applied.
- L108 _public prototype_ `virtual void UnregisterRestorationListener(const TSharedRef<IRestorationListener>& Listener) = 0;`
- L112 _public prototype_ `virtual void RegisterTakeSnapshotListener(TSharedRef<ITakeSnapshotListener> Extender) = 0;` — Registers an object that listens for when objects are snapshot.
- L113 _public prototype_ `virtual void UnregisterTakeSnapshotListener(const TSharedRef<ITakeSnapshotListener>& Listener) = 0;`
- L117 _public prototype_ `virtual void RegisterSnapshotFilterExtender(TSharedRef<ISnapshotFilterExtender> Extender) = 0;` — Registers an object that can decide to display additional properties to the user that default snapshot behaviour does not display.
- L118 _public prototype_ `virtual void UnregisterSnapshotFilterExtender(const TSharedRef<ISnapshotFilterExtender>& Listener) = 0;`
- L125 _public prototype_ `virtual void AddExplicitilySupportedProperties(const TSet<const FProperty*>& Properties) = 0;` — Adds properties that snapshots will capture and restore from now on. This allows support for properties that are skipped by default. Important: Only add add native properties; Blueprint properties may be invalidated (and left dangeling) when recompiled.
- L126 _public prototype_ `virtual void RemoveAdditionallySupportedProperties(const TSet<const FProperty*>& Properties) = 0;`
- L132 _public prototype_ `virtual void AddExplicitlyUnsupportedProperties(const TSet<const FProperty*>& Properties) = 0;` — Stops snapshots from capturing / restoring these properties. Important: Only add add native properties; Blueprint properties may be invalidated (and left dangeling) when recompiled.
- L133 _public prototype_ `virtual void RemoveExplicitlyUnsupportedProperties(const TSet<const FProperty*>& Properties) = 0;`
- L149 _public prototype_ `virtual void AddSkippedClassDefault(const UClass* Class) = 0;` — Disable CDO serialization for a class and all of its subclasses. Snapshots saves the CDO of every saved object class. Actors use it as Template when spawned. For all other objects (i.e. subobjects), Serialize(FArchive&) is called with the saved CDO data and then Serialize(FArchive&) is called again with the actual object's data. This is so changes to CDOs can be detected. This function disables the above process. You would use it e.g. when your class implements a custom Serialize(FArchive&) function which conditionally serializes data depending on whether the serialized object has the RF_ClassDefaultObject flag. Doing so would trigger an ensure in the snapshot archive code because the data would not be read in the same order as it was written. Note: Level Snapshots will no longer detect changes made to the class default values of skipped classes.
- L150 _public prototype_ `virtual void RemoveSkippedClassDefault(const UClass* Class) = 0;`
- L151 _public prototype_ `virtual bool ShouldSkipClassDefaultSerialization(const UClass* Class) const = 0;`
- L155 _protected member_ `FPreTakeSnapshotEvent PreTakeSnapshot;`
- L156 _protected member_ `FPostTakeSnapshotEvent PostTakeSnapshot;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L48 _delegate_ `DECLARE_EVENT_OneParam(ILevelSnapshotsModule, FPreTakeSnapshotEvent, const FPreTakeSnapshotEventData&);`
- L52 _delegate_ `DECLARE_EVENT_OneParam(ILevelSnapshotsModule, FPostTakeSnapshotEvent, const FPostTakeSnapshotEventData&);`
- L57 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanTakeSnapshot, const FPreTakeSnapshotEventData&);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/LevelSnapshotsEngineSubsystem.h` (Public)


#### struct `FLevelSnapshotEvent_Blueprint`  
`struct FLevelSnapshotEvent_Blueprint`  
_L21-28_
- reflection: `USTRUCT(BlueprintType, DisplayName = "LevelSnapshotEvent")`
- L27 _public member_ `TObjectPtr<ULevelSnapshot> Snapshot;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — The affected snapshot

#### struct `FPreTakeSnapshotEventData_Blueprint`  
`struct FPreTakeSnapshotEventData_Blueprint : public FLevelSnapshotEvent_Blueprint`  
_L31-31_
- reflection: `USTRUCT(DisplayName = "PreTakeSnapshotEventData")`
- inherits: `FLevelSnapshotEvent_Blueprint`

#### struct `FPostTakeSnapshotEventData_Blueprint`  
`struct FPostTakeSnapshotEventData_Blueprint : public FLevelSnapshotEvent_Blueprint`  
_L33-33_
- reflection: `USTRUCT(DisplayName = "PostTakeSnapshotEventData")`
- inherits: `FLevelSnapshotEvent_Blueprint`

#### struct `FPreApplySnapshotEventData_Blueprint`  
`struct FPreApplySnapshotEventData_Blueprint : public FLevelSnapshotEvent_Blueprint`  
_L36-36_
- reflection: `USTRUCT(DisplayName = "PreApplySnapshotEventData")`
- inherits: `FLevelSnapshotEvent_Blueprint`

#### struct `FPostApplySnapshotEventData_Blueprint`  
`struct FPostApplySnapshotEventData_Blueprint : public FLevelSnapshotEvent_Blueprint`  
_L38-38_
- reflection: `USTRUCT(DisplayName = "PostApplySnapshotEventData")`
- inherits: `FLevelSnapshotEvent_Blueprint`

#### class `ULevelSnapshotsEngineSubsystem`  
`class ULevelSnapshotsEngineSubsystem : public UEngineSubsystem`  
_L42-79_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Exposes some native Level Snapshots events to Blueprint scripting.
- L47 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreTakeSnapshotEvent, const FPreTakeSnapshotEventData_Blueprint&, EventData);`
- L50 _public member_ `FPreTakeSnapshotEvent OnPreTakeSnapshot;` — `UPROPERTY(BlueprintAssignable, Category = "Level Snapshots")` — Called before a level snapshot captures the world's data.
- L52 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPostTakeSnapshotEvent, const FPostTakeSnapshotEventData_Blueprint&, EventData);`
- L55 _public member_ `FPostTakeSnapshotEvent OnPostTakeSnapshot;` — `UPROPERTY(BlueprintAssignable, Category = "Level Snapshots")` — Called after a level snapshot captures the world's data.
- L57 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreApplySnapshotEvent, const FPreApplySnapshotEventData_Blueprint&, EventData);`
- L60 _public member_ `FPreApplySnapshotEvent OnPreApplySnapshot;` — `UPROPERTY(BlueprintAssignable, Category = "Level Snapshots")` — Called before a level snapshot is applied to a world.
- L62 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPostApplySnapshotEvent, const FPostApplySnapshotEventData_Blueprint&, EventData);`
- L65 _public member_ `FPostApplySnapshotEvent OnPostApplySnapshot;` — `UPROPERTY(BlueprintAssignable, Category = "Level Snapshots")` — Called after a level snapshot was applied to a world.
- L68 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L69 _public prototype_ `virtual void Deinitialize() override;`
- L75 _private member_ `TSharedPtr<UE::LevelSnapshots::IRestorationListener> RestorationListener;` — Exposes some events to Blueprints. Created by Initialize and Reset() by Deinitialize.
- L77 _private prototype_ `void HandleOnPreTakeSnapshot(const UE::LevelSnapshots::FPreTakeSnapshotEventData& EventData);`
- L78 _private prototype_ `void HandleOnPostTakeSnapshot(const UE::LevelSnapshots::FPostTakeSnapshotEventData& EventData);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L47 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreTakeSnapshotEvent, const FPreTakeSnapshotEventData_Blueprint&, EventData);`
- L52 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPostTakeSnapshotEvent, const FPostTakeSnapshotEventData_Blueprint&, EventData);`
- L57 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreApplySnapshotEvent, const FPreApplySnapshotEventData_Blueprint&, EventData);`
- L62 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPostApplySnapshotEvent, const FPostApplySnapshotEventData_Blueprint&, EventData);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/LevelSnapshotsFilteringLibrary.h` (Public)


#### class `ULevelSnapshotsFilteringLibrary`  
`class ULevelSnapshotsFilteringLibrary : public UBlueprintFunctionLibrary`  
_L18-37_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static FPropertySelectionMap DiffAndFilterSnapshot(UWorld* InWorld, ULevelSnapshot* InSnapshot, const ULevelSnapshotFilter* Filter = nullptr);` — Diffs the snapshot with the given world and returns the changes that pass the filter.
- L30 _public prototype_ `static void ApplyFilterToFindSelectedProperties( ULevelSnapshot* Snapshot, FPropertySelectionMap& MapToAddTo, AActor* WorldActor, AActor* DeserializedSnapshotActor, const ULevelSnapshotFilter* Filter );` — Goes through the properties of the actors and their components calling IsPropertyValid on them. This function does not recursively check object references, e.g. 'Instanced' uproperties. These properties are currently unsupported by the snapshot framework.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/LevelSnapshotsFunctionLibrary.h` (Public)


#### class `ULevelSnapshotsFunctionLibrary`  
`class ULevelSnapshotsFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-58_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static ULevelSnapshot* TakeLevelSnapshot(const UObject* WorldContextObject, const FName NewSnapshotName = "NewLevelSnapshot", const FString De` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots", meta = (WorldContext = "WorldContextObject"))`
- L21 _public prototype_ `static ULevelSnapshot* TakeLevelSnapshot_Internal(const UObject* WorldContextObject, const FName NewSnapshotName = "NewLevelSnapshot", UPackage* InPackage = nullptr, const FString De`
- L25 _public prototype_ `static void ApplySnapshotToWorld(const UObject* WorldContextObject, ULevelSnapshot* Snapshot, ULevelSnapshotFilter* OptionalFilter);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots", meta = (WorldContext = "WorldContextObject"))` — Applies the snapshot to the world. If no filter is specified, the entire snapshot is applied.
- L32 _public prototype_ `static void ApplyFilterToFindSelectedProperties( ULevelSnapshot* Snapshot, FPropertySelectionMap& MapToAddTo, AActor* WorldActor, AActor* DeserializedSnapshotActor, const ULevelSnapshotFilter* Filter, bool bAllowUnchangedProperties = false, bool bAllowNonEditableProperties = false );` — `UE_DEPRECATED(5.1, "Use ULevelSnapshotsFilteringLibrary::ApplyFilterToFindSelectedProperties instead.")` — Goes through the properties of the actors and their components calling IsPropertyValid on them. This function does not recursively check object references, e.g. 'Instanced' uproperties. These properties are currently unsupported by the snapshot framework.
- L51 _public prototype_ `static void ForEachMatchingCustomSubobjectPair( ULevelSnapshot* Snapshot, UObject* SnapshotRootObject, UObject* WorldRootObject, TFunctionRef<void(UObject* SnapshotSubobject, UObject* EditorWorldSubobject)> HandleCustomSubobjectPair, TFunctionRef<void(UObject* UnmatchedSnapshotSubobject)> HandleUnmatchedSnapshotSubobject );` — Recursively gets all subobjects which should be serialized using an ICustomObjectSnapshotSerializer implementation from an external module. @param Snapshot The snapshot in which to look @param SnapshotRootObject Snapshot version of the object to look in. Either an actor, component, or a custom serialized subobject. @param WorldRootObject Editor version of the object to look in. Either an actor, component, or a custom serialized subobject. @param HandleCustomSubobjectPair Called when two custom subobjects are matched @param HandleUnmatchedSnapshotSubobject Called when a custom snapshot subobject exists but no corresponding editor subobject exists

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/LevelSnapshotsLog.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define SCOPED_SNAPSHOT_TRACE(TraceName) TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(TraceName, LevelSnapshotsChannel)`
- L12 _macro_ `#define SCOPED_SNAPSHOT_TRACE(TraceName)`
- L16 _macro_ `#define SCOPED_SNAPSHOT_CORE_TRACE(TraceName) SCOPED_SNAPSHOT_TRACE(SnapshotCore_##TraceName)` — Use inside 'implementation' modules, like this one or filters
- L18 _macro_ `#define SCOPED_SNAPSHOT_EDITOR_TRACE(TraceName) SCOPED_SNAPSHOT_TRACE(SnapshotEditor_##TraceName)` — Use inside editor modules
- L20 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogLevelSnapshots, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogLevelSnapshots, Log, All);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/PropertyInfoHelpers.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _externvar_ `extern float GFloatComparisonPrecision;` (scope `UE::LevelSnapshots`)
- L15 _externvar_ `extern double GDoubleComparisonPrecision;` (scope `UE::LevelSnapshots`)
- L17 _prototype_ `FProperty* GetParentProperty(const FProperty* Property);` (scope `UE::LevelSnapshots`)
- L20 _prototype_ `bool IsPropertyContainer(const FProperty* Property);` (scope `UE::LevelSnapshots`) — Returns true if the property is a struct, map, array, set, etc
- L22 _prototype_ `bool IsPropertyCollection(const FProperty* Property);` (scope `UE::LevelSnapshots`) — Returns true if the property is a set, array, map, etc but NOT a struct
- L25 _prototype_ `bool IsPropertyInContainer(const FProperty* Property);` (scope `UE::LevelSnapshots`) — Is the property an element of a struct, set, array, map, etc
- L27 _prototype_ `bool IsPropertyInCollection(const FProperty* Property);` (scope `UE::LevelSnapshots`) — Is the property an element of a set, array, map, etc
- L29 _prototype_ `bool IsPropertyInStruct(const FProperty* Property);` (scope `UE::LevelSnapshots`)
- L31 _prototype_ `bool IsPropertyInMap(const FProperty* Property);` (scope `UE::LevelSnapshots`)
- L34 _prototype_ `bool IsPropertyComponentOrSubobject(const FProperty* Property);` (scope `UE::LevelSnapshots`) — A quick property flag check. Assumes the property flags are properly set/deserialized
- L36 _prototype_ `void UpdateDecimalComparisionPrecision(float FloatPrecision, double DoublePrecision);` (scope `UE::LevelSnapshots`)
- L37 _prototype_ `bool AreNumericPropertiesNearlyEqual(const FNumericProperty* Property, const void* ValuePtrA, const void* ValuePtrB);` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/ClassRestorationSkipper.h` (Public)


#### class `UE::LevelSnapshots::FClassRestorationSkipper`  
`class FClassRestorationSkipper : public ISnapshotRestorabilityOverrider`  
_L12-34_
- inherits: `ISnapshotRestorabilityOverrider`
- desc: Disallows provided classes. Uses callback to obtain class list so the logic is reusable outside the module.
- L16 _public function_ `DECLARE_DELEGATE_RetVal(const FSkippedClassList&, FGetSkippedClassList) FClassRestorationSkipper(FGetSkippedClassList SkippedClassListCallback) : GetSkippedClassListCallback(SkippedClassListCallback)`
- L26 _public prototype_ `virtual ERestorabilityOverride IsActorDesirableForCapture(const AActor* Actor) override;`
- L27 _public prototype_ `virtual ERestorabilityOverride IsComponentDesirableForCapture(const UActorComponent* Component) override;`
- L32 _private member_ `FGetSkippedClassList GetSkippedClassListCallback;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE_RetVal(const FSkippedClassList&, FGetSkippedClassList) FClassRestorationSkipper(FGetSkippedClassList SkippedClassListCallback) : GetSkippedClassListCallback(SkippedClassListCallback) { check(SkippedClassListCallback.IsBound()); }`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/IActorSnapshotFilter.h` (Public)


#### struct `UE::LevelSnapshots::FCanRecreateActorParams`  
`struct FCanRecreateActorParams`  
_L18-34_
- desc: Params for deciding whether an actor should be recreated
- L21 _public member_ `UWorld* EditorWorld;` — The world the snapshot is being applied to
- L24 _public member_ `UClass* Class;` — The actor's class
- L26 _public member_ `FSoftObjectPath ActorPath;` — The object path of the actor
- L28 _public member_ `EObjectFlags ObjectFlags;` — The flags of the actor
- L30 _public member_ `const FWorldSnapshotData& WorldData;` — All world data of the snapshot
- L33 _public member_ `FDeserializedActorGetter DeserializeFromSnapshotFunc;` — If you need access to the actor's data, you can call this function.

#### struct `UE::LevelSnapshots::FCanModifyMatchedActorParams`  
`struct FCanModifyMatchedActorParams`  
_L37-43_
- desc: Params for deciding whether an existing actor should have its properties modified.
- L40 _public member_ `AActor& MatchedEditorWorldActor;` — The actor in the editor world which is being considered for restoration.
- L42 _public member_ `const FWorldSnapshotData& WorldData;` — All world data of the snapshot

#### class `UE::LevelSnapshots::IActorSnapshotFilter`  
`class IActorSnapshotFilter`  
_L48-103_
- desc: Can decide whether a given actor can be added to or removed from the world.
- L74 _public function_ `virtual FFilterResultData CanModifyMatchedActor(const FCanModifyMatchedActorParams& Params)` — Called to check whether a matched actor is allowed to have any of its data restored.
- L77 _public function_ `virtual FFilterResultData CanRecreateMissingActor(const FCanRecreateActorParams& Params)` — Whether the actor is allowed to be recreated. Called when diffing to world.
- L85 _public function_ `virtual FFilterResultData CanDeleteNewActor(const AActor* EditorActor)` — Whether the actor is allowed to be removed. Called when diffing to world.
- L95 _public function_ `virtual EFilterResult CanRecreateActor(const FCanRecreateActorParams& Params)` — `UE_DEPRECATED(5.2, "Use CanRecreateMissingActor instead.")` — Whether the actor is allowed to be recreated. Called when diffing to world.
- L99 _public function_ `virtual EFilterResult CanDeleteActor(const AActor* EditorActor)` — `UE_DEPRECATED(5.2, "Use CanDeleteNewActor instead.")` — Whether the actor is allowed to be removed. Called when diffing to world.
- L102 _public prototype_ `virtual ~IActorSnapshotFilter() = default;`

#### enum `UE::LevelSnapshots::IActorSnapshotFilter::EFilterResult`  
`enum class EFilterResult`  
_L52-60_
- L55 _public enumerator_ `Allow` — The object in question is included but only if nobody else returned Disallow.
- L57 _public enumerator_ `DoNotCare` — Let other filters decide. If every override return DoNotCare, default snapshot behaviour is applied.
- L59 _public enumerator_ `Disallow` — The object in question is never suitable and is not included. Other filters cannot override this.

#### struct `UE::LevelSnapshots::IActorSnapshotFilter::FFilterResultData`  
`struct FFilterResultData`  
_L62-71_
- L65 _public member_ `EFilterResult InclusionResult;` — Determines what to do with the actor data
- L67 _public member_ `FText ExclusionReason;` — The reason for InclusionResult == Disallow, if any. Displayed to the user.
- L69 _public prototype_ `FFilterResultData() = default;`
- L70 _public function_ `FFilterResultData(EFilterResult Result, FText ExclusionReason = FText::GetEmpty()) : InclusionResult(Result), ExclusionReason(MoveTemp(ExclusionReason))`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L15 _typedef_ `using FDeserializedActorGetter = TFunctionRef<TOptional<TNonNullPtr<AActor>>()>;` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/ICustomObjectSnapshotSerializer.h` (Public)


#### class `UE::LevelSnapshots::ICustomObjectSnapshotSerializer`  
`class ICustomObjectSnapshotSerializer`  
_L28-121_
- desc: External modules can implement this interface to customise how specific classes are snapshot and restored. Implementations of this interface can be registered with the Level Snapshots module. One instance handles on type of class. ISnapshotObjectSerializer handles the serialisation of the object you're registered to. You can use it to add custom annotation data you need to restoring object info. You can also save & restore subobjects you wish to manually restore, provided they're not automatically restored by Level Snapshots. The following subobjects are handled by default: - Actor components - UProperty exposed UObject* references or collections with CPF_Edit flag, e.g. e.g. UPROPERTY(EditAnywhere) TArray<UObject*>.
- L41 _public function_ `virtual void OnTakeSnapshot(UObject* EditorObject, ICustomSnapshotSerializationData& DataStorage)` — Called when taking a snapshot of an object with the class this implementation is registered to. You can use DataStorage to add any data additional meta data needed and add subobjects you want to restore manually. Note that all uproperties will still be restored normally as with all other objects. @param EditorObject The object being snapshotted. Same as DataStorage->GetSerializedObject(). @param DataStorage Data to save for EditorObject: serialize extra data about EditorObject and add subobjects.
- L57 _public function_ `virtual UObject* FindOrRecreateSubobjectInSnapshotWorld(UObject* SnapshotObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage)` — Called when creating objects for the temporary snapshot world. This is called for every subobject added using ISnapshotObjectSerializer::AddSubobjectDependency. This function must either find the subobject in SnapshotObject or recreate it. If the object is recreated, you must fix up any property references yourself. After this function is called, properties will be serialized into this function's return value. After this, OnPostSerializeSnapshotSubobject is called. @param SnapshotObject The outer of the subobject @param ObjectData The data saved for the subobject. It's the data associated with the index returned by AddSubobjectSnapshot. @param DataStorage The data saved for the outer @result The found or recreated subobject. If null, the subobject is skipped.
- L72 _public function_ `virtual UObject* FindOrRecreateSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage)` — Called when applying into the editor world. This is called for every subobject added using ISnapshotObjectSerializer::AddSubobjectDependency. This function must either find the subobject in EditorObject or recreate it. If the object is recreated, you must fix up any property references yourself. After this function is called, properties will be serialized into this function's return value. After this, OnPostSerializeEditorSubobject is called. @param SnapshotObject The outer of the subobject @param ObjectData The data saved for the subobject. It's the data associated with the index returned by AddSubobjectSnapshot. @param DataStorage The data saved for the outer @result The found or recreated subobject. If null, the subobject is skipped.
- L84 _public function_ `virtual UObject* FindSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage)` — Similar to FindOrRecreateSubobjectInEditorWorld, only that the subobject is not recreated if not present. Called when diffing against the world. @param SnapshotObject The outer of the subobject @param ObjectData The data saved for the subobject. It's the data associated with the index returned by AddSubobjectSnapshot. @param DataStorage The data saved for the outer @result The subobject in the editor world. If you return null, the subobject will be recreated.
- L90 _public function_ `virtual void OnPostSerializeSnapshotSubobject(UObject* Subobject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage)` — Optional. Called after GetOrRecreateSubobjectInSnapshotWorld when all properties have been serialized into the subobject. You can do any post processing here.
- L93 _public function_ `virtual void OnPostSerializeEditorSubobject(UObject* Subobject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage)` — Optional. Called after GetOrRecreateSubobjectInEditorWorld when all properties have been serialized into the subobject. You can do any post processing here.
- L98 _public function_ `virtual void PreApplyToSnapshotObject(UObject* Object, const ICustomSnapshotSerializationData& DataStorage)` — Optional. Called before properties are applied to anobject for which this interface was registered. Called on the object in the transient snapshot world.
- L101 _public function_ `virtual void PostApplyToSnapshotObject(UObject* Object, const ICustomSnapshotSerializationData& DataStorage)` — Optional. Called after properties are applied to an object for which this interface was registered. Called on the object in the transient snapshot world.
- L106 _public function_ `virtual void PreApplyToEditorObject(UObject* Object, const ICustomSnapshotSerializationData& DataStorage, const FPropertySelectionMap& SelectionMap)` — Optional. Called before properties are applied to anobject for which this interface was registered. Called on the object in the editor world.
- L113 _public function_ `virtual void PostApplyToEditorObject(UObject* Object, const ICustomSnapshotSerializationData& DataStorage, const FPropertySelectionMap& SelectionMap)` — Optional. Called after properties are applied to an object for which this interface was registered. Called on the object in the editor world.
- L120 _public prototype_ `virtual ~ICustomObjectSnapshotSerializer() = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/IPropertyComparer.h` (Public)


#### class `UE::LevelSnapshots::IPropertyComparer`  
`class IPropertyComparer`  
_L20-42_
- desc: Defines a callback for deciding whether a property has changed. This is useful for cases where certain properties are disabled by others. For an example see FStaticMeshCollisionPropertyComparer.
- L34 _public prototype_ `virtual ~IPropertyComparer() = default;`
- L41 _public function_ `virtual EPropertyComparison ShouldConsiderPropertyEqual(const FPropertyComparisonParams& Params) const` — Decides whether the property should be considered equal. Note that this is only called on root properties. For performance reasons, this is not called on nested struct properties. This is not a big restriction because you can just check the structs content yourself.

#### enum `UE::LevelSnapshots::IPropertyComparer::EPropertyComparison`  
`enum class EPropertyComparison`  
_L24-32_
- L27 _public enumerator_ `TreatEqual` — The properties are equal.
- L29 _public enumerator_ `TreatUnequal` — The properties are not equal.
- L31 _public enumerator_ `CheckNormally` — Check the property normally.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/IRestorationListener.h` (Public)


#### struct `UE::LevelSnapshots::FRestorationListenerBaseParams`  
`struct FRestorationListenerBaseParams`  
_L19-27_
- L22 _public member_ `const FPropertySelectionMap& SelectedProperties;` — All of the user's selected properties
- L24 _public function_ `FRestorationListenerBaseParams(const FPropertySelectionMap& SelectedProperties) : SelectedProperties(SelectedProperties)`

#### struct `UE::LevelSnapshots::FApplySnapshotSharedParams`  
`struct FApplySnapshotSharedParams : FRestorationListenerBaseParams`  
_L29-36_
- inherits: `FRestorationListenerBaseParams`
- L31 _public member_ `ULevelSnapshot& LevelSnapshot;`
- L32 _public function_ `FApplySnapshotSharedParams(ULevelSnapshot& LevelSnapshot, const FPropertySelectionMap& SelectedProperties) : FRestorationListenerBaseParams(SelectedProperties) , LevelSnapshot(LevelSnapshot)`

#### struct `UE::LevelSnapshots::FPreApplySnapshotParams`  
`struct FPreApplySnapshotParams : FApplySnapshotSharedParams`  
_L37-37_
- inherits: `FApplySnapshotSharedParams`

#### struct `UE::LevelSnapshots::FPostApplySnapshotParams`  
`struct FPostApplySnapshotParams : FApplySnapshotSharedParams`  
_L38-38_
- inherits: `FApplySnapshotSharedParams`

#### struct `UE::LevelSnapshots::FPreRemoveActorParams`  
`struct FPreRemoveActorParams : FRestorationListenerBaseParams`  
_L40-48_
- inherits: `FRestorationListenerBaseParams`
- L42 _public member_ `AActor* ActorToRemove;`
- L44 _public function_ `FPreRemoveActorParams(const FPropertySelectionMap& SelectedProperties, AActor* ActorToRemove) : FRestorationListenerBaseParams(SelectedProperties), ActorToRemove(ActorToRemove)`

#### struct `UE::LevelSnapshots::FPostRemoveActorsParams`  
`struct FPostRemoveActorsParams : FRestorationListenerBaseParams`  
_L49-49_
- inherits: `FRestorationListenerBaseParams`

#### struct `UE::LevelSnapshots::FApplySnapshotPropertiesParams`  
`struct FApplySnapshotPropertiesParams`  
_L51-71_
- L54 _public member_ `UObject* Object;` — The object that receives serialized data.
- L57 _public member_ `const FPropertySelectionMap& SelectedProperties;` — All of the user's selected properties
- L60 _public member_ `TOptional<const FPropertySelection*> PropertySelection;` — Only valid when bWasRecreated = false
- L63 _public member_ `bool bWasRecreated;` — Whether Object did not yet exist in the world and was recreated
- L65 _public function_ `FApplySnapshotPropertiesParams(UObject* Object, const FPropertySelectionMap& SelectedProperties, TOptional<const FPropertySelection*> PropertySelection, bool bWasRecreated) : Object(Object), SelectedProperties(SelectedProperties), PropertySelection(PropertySelection), bWasRecreated(bWasRecreated)`

#### struct `UE::LevelSnapshots::FApplySnapshotToActorParams`  
`struct FApplySnapshotToActorParams`  
_L73-89_
- L76 _public member_ `AActor* Actor;` — The actor that is modified
- L79 _public member_ `const FPropertySelectionMap& SelectedProperties;` — All of the user's selected properties
- L82 _public member_ `bool bWasRecreated;` — Whether Object did not yet exist in the world and was recreated
- L84 _public function_ `FApplySnapshotToActorParams(AActor* Actor, const FPropertySelectionMap& SelectedProperties, bool bWasRecreated) : Actor(Actor), SelectedProperties(SelectedProperties), bWasRecreated(bWasRecreated)`

#### struct `UE::LevelSnapshots::FPreRecreateComponentParams`  
`struct FPreRecreateComponentParams`  
_L91-108_
- L94 _public member_ `AActor* Owner;` — The actor that will own the component
- L96 _public member_ `FName ComponentName;` — The name the component will have.
- L98 _public member_ `UClass* ComponentClass;` — The class the component will have.
- L100 _public member_ `EComponentCreationMethod CreationMethod;` — The creation method that will be set for the component.
- L102 _public function_ `FPreRecreateComponentParams(AActor* Owner, FName ComponentName, UClass* ComponentClass, EComponentCreationMethod CreationMethod) : Owner(Owner), ComponentName(ComponentName), ComponentClass(ComponentClass), CreationMethod(CreationMethod)`

#### struct `UE::LevelSnapshots::FPostRemoveComponentParams`  
`struct FPostRemoveComponentParams`  
_L110-129_
- L113 _public member_ `AActor* Owner;` — The actor the component was removed from
- L115 _public member_ `FName ComponentName;` — The old component's name
- L121 _public member_ `TWeakObjectPtr<UActorComponent> DestroyedComponent;` — Pointer to the still allocated component. Only use in the callback function. Do not store the object: it is pending kill and will be garbage collected.
- L123 _public function_ `FPostRemoveComponentParams(AActor* Owner, FName ComponentName, TWeakObjectPtr<UActorComponent> DestroyedComponent) : Owner(Owner), ComponentName(ComponentName), DestroyedComponent(DestroyedComponent)`

#### class `UE::LevelSnapshots::IRestorationListener`  
`class IRestorationListener`  
_L140-238_
- desc: Exposes callbacks for when: - An object is serialized (PreApplySnapshot and PostApplySnapshot) - A component is added back to an actor (PreRecreateComponent and PostRecreateComponent) - A component is removed from an actor (PreRemoveComponent and PostRemoveComponent) In all callbacks, you will receive a non-const UObject. You are free to modify them. Keep the user's expectations in mind: generally only properties that were selected should change. You should generally ensure that relevant systems are updated.
- L145 _public function_ `virtual void PreApplySnapshot(const FPreApplySnapshotParams& Params)` — Called before the snapshot is applied. Except for the changes made by this event, the world has not been changed, yet.
- L148 _public function_ `virtual void PostApplySnapshot(const FPostApplySnapshotParams& Params)` — Called after all snapshot data was applied. The world is nearly completely changed (the only thing remaining is executing this event).
- L161 _public function_ `virtual void PreApplySnapshotProperties(const FApplySnapshotPropertiesParams& Params)` — Called before applying snapshot data to an object. For actors, this function is always called. For subobjects, such as components, this is only called when there are changed properties. If this is called on a recreated component, then Params.bWasRecreated will be true; this function will be called after both PreRecreateComponent and PostRecreateComponent have been called.
- L169 _public function_ `virtual void PostApplySnapshotProperties(const FApplySnapshotPropertiesParams& Params)` — Called after applying snapshot data to an object. For actors, this function is always called. For subobjects, such as components, this is only called when there were changed properties.
- L177 _public function_ `virtual void PreApplySnapshotToActor(const FApplySnapshotToActorParams& Params)` — Called before an actor receives any property or component change. Called before PreApplySnapshotProperties, PreRecreateComponent, and PreRemoveComponent.
- L183 _public function_ `virtual void PostApplySnapshotToActor(const FApplySnapshotToActorParams& Params)` — Called after an actor has received all property and component changes. Called after PostApplySnapshotProperties, PostRecreateComponent, and PostRemoveComponent.
- L191 _public function_ `virtual void PreRecreateActor(UWorld* World, TSubclassOf<AActor> ActorClass, FActorSpawnParameters& InOutSpawnParameters)` — Called before an actor is recreated to the world and gives the opportunity to override settings. You cannot override the Name.
- L194 _public function_ `virtual void PostRecreateActor(AActor* RecreatedActor)` — Called after an actor is recreated to the world (but before any data is applied to it)
- L198 _public function_ `virtual void PreRemoveActor(AActor* ActorToRemove)` — `UE_DEPRECATED(5.1, "Use PreRemoveActor(const FPreRemoveActorParams& Params) instead")`
- L201 _public function_ `virtual void PreRemoveActor(const FPreRemoveActorParams& Params)` — Called before an actor is removed from the world.
- L204 _public function_ `virtual void PostRemoveActors(const FPostRemoveActorsParams& Params)` — Called after all actors have been removed from the world
- L213 _public function_ `virtual void PreRecreateComponent(const FPreRecreateComponentParams& Params)` — Called before a component is recreated on an actor. PreApplySnapshot and PostApplySnapshot will be called after PostRecreateComponent has executed.
- L220 _public function_ `virtual void PostRecreateComponent(UActorComponent* RecreatedComponent)` — Called after a component has been recreated on an actor. PreApplySnapshot and PostApplySnapshot will be called after PostRecreateComponent has executed.
- L228 _public function_ `virtual void PreRemoveComponent(UActorComponent* ComponentToRemove)` — Called before a component is removed from an actor.
- L233 _public function_ `virtual void PostRemoveComponent(const FPostRemoveComponentParams& Params)` — Called after a component is removed from an actor.
- L237 _public prototype_ `virtual ~IRestorationListener() = default;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/ISnapshotFilterExtender.h` (Public)


#### struct `UE::LevelSnapshots::FPreApplyFiltersParams`  
`struct FPreApplyFiltersParams`  
_L14-22_
- L17 _public member_ `UObject* SnapshotObject;` — The editor object being filtered
- L19 _public member_ `UObject* EditorObject;` — The snapshot world object being filtered
- L21 _public member_ `ULevelSnapshot* Snapshot;` — The snapshot on which the filtering occurs

#### struct `UE::LevelSnapshots::FPostApplyFiltersParams`  
`struct FPostApplyFiltersParams`  
_L24-37_
- L26 _public member_ `const FPropertySelection& SelectedProperties;`
- L28 _public member_ `UObject* SnapshotObject;` — The editor object being filtered
- L30 _public member_ `UObject* EditorObject;` — The snapshot world object being filtered
- L32 _public function_ `FPostApplyFiltersParams(const FPropertySelection& SelectedProperties, UObject* SnapshotObject, UObject* EditorObject) : SelectedProperties(SelectedProperties) , SnapshotObject(SnapshotObject) , EditorObject(EditorObject)`

#### struct `UE::LevelSnapshots::FPostApplyFiltersResult`  
`struct FPostApplyFiltersResult`  
_L39-57_
- L42 _public member_ `TArray<FLevelSnapshotPropertyChain> AdditionalPropertiesToFilter;` — Additional properties that should be displayed to the user. They will only be shown if they pass the user's filters.
- L44 _public member_ `TArray<FLevelSnapshotPropertyChain> AdditionalPropertiesToForcefullyShow;` — Additional properties that should always be displayed to the user regardless of whether they pass the property filter or not.
- L46 _public function_ `void Combine(FPostApplyFiltersResult Result)`

#### class `UE::LevelSnapshots::ISnapshotFilterExtender`  
`class ISnapshotFilterExtender`  
_L89-103_
- desc: Allows you to receive callbacks when an object is filtered and to display additional properties in the results view. This is used whenever a selection set is built. By default only modified properties are shown. However, sometimes you may want to include unmodified properties, too. Example 1: Transforms and parenting 1. Create cube 2. Rotate it to 40 degrees 3. Take a snapshot 4. Create new empty actor 5. Attach cube to empty actor 6. Rotate empty actor by 10 degrees 7. Apply the snapshot Result: After applying, the cube has a diff because its rotation is 50 degrees. The reason is because before applying the only thing that was different was the cube's attach parent. When the parent actor is removed, its world-space transform is retained; actors are removed first and then the properties of modified actors are saved. The solution is, using this interface, to add the cube's transform properties even though they're equal to the snapshot version. Users will see the property in the UI and can opt to not restore it. Example 2: AMediaPlate Media plates add a transient UAssetUserData object to a component. In OnPreSaveWorld and OnPostSaveWorld the UAssetUserData would be removed and added back. Similar behaviour should occur for Level Snapshots when filtering and applying (events about applying are exposed by IRestorationListener). Note that Level Snapshots restores TArrays either fully or not at all. For this reason, IPropertyComparer may not always be an option for you; this interf
- L97 _public function_ `virtual void PreApplyFilters(const FPreApplyFiltersParams& Params)` — Called before the object is filtered. PreFilterObject is be executed recursively on subobjects before the corresponding call to PostFilterObject is made.
- L100 _public function_ `virtual FPostApplyFiltersResult PostApplyFilters(const FPostApplyFiltersParams& Params)` — Called after all properties have been filtered on the given object pair.
- L102 _public prototype_ `virtual ~ISnapshotFilterExtender() = default;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/ISnapshotLoader.h` (Public)


#### struct `UE::LevelSnapshots::FPostLoadSnapshotObjectParams`  
`struct FPostLoadSnapshotObjectParams`  
_L12-23_
- L15 _public member_ `UObject* SnapshotObject;` — The object that received its properties
- L17 _public member_ `const FWorldSnapshotData& SnapshotData;` — All saved snapshot data. Typical use case is getting the saved version info
- L19 _public function_ `FPostLoadSnapshotObjectParams(UObject* SnapshotObject, const FWorldSnapshotData& SnapshotData) : SnapshotObject(SnapshotObject), SnapshotData(SnapshotData)`

#### class `UE::LevelSnapshots::ISnapshotLoader`  
`class ISnapshotLoader`  
_L28-36_
- desc: Receives callbacks when an object is loaded into the snapshot world. Gives the opportunity to call custom fix up functions.
- L33 _public function_ `virtual void PostLoadSnapshotObject(const FPostLoadSnapshotObjectParams& Params)` — Called after an object has received all its properties.
- L35 _public prototype_ `virtual ~ISnapshotLoader() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/ISnapshotRestorabilityOverrider.h` (Public)


#### class `UE::LevelSnapshots::ISnapshotRestorabilityOverrider`  
`class ISnapshotRestorabilityOverrider`  
_L23-44_
- desc: Exposes callbacks for deciding whether an actor or component is exposed to the snapshot system. Supported actors, components, or properties are: - Captured and saved when a snapshot is taken - Passed to filters - Show up in the results view - Restored when a snapshot is applied To see which actors, components, and subobjects are supported by default, see FSnapshotRestorability.
- L37 _public prototype_ `virtual ~ISnapshotRestorabilityOverrider() = default;`
- L40 _public function_ `virtual ERestorabilityOverride IsActorDesirableForCapture(const AActor* Actor)` — Should this actor be visible to the snapshot system?
- L43 _public function_ `virtual ERestorabilityOverride IsComponentDesirableForCapture(const UActorComponent* Component)` — Should this component be visible to the snapshot system?

#### enum `UE::LevelSnapshots::ISnapshotRestorabilityOverrider::ERestorabilityOverride`  
`enum class ERestorabilityOverride`  
_L27-35_
- L30 _public enumerator_ `Allow` — The object in question is included but only if nobody else returned Disallow.
- L32 _public enumerator_ `DoNotCare` — Let other overrides decide. If every override return DoNotCare, default snapshot behaviour is applied.
- L34 _public enumerator_ `Disallow` — The object in question is never suitable and is not included. Other overriders cannot override this.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Interfaces/ITakeSnapshotListener.h` (Public)


#### struct `UE::LevelSnapshots::FTakeObjectSnapshotEvent`  
`struct FTakeObjectSnapshotEvent`  
_L15-18_
- L17 _public member_ `UObject* Object;`

#### struct `UE::LevelSnapshots::FPreTakeObjectSnapshotEvent`  
`struct FPreTakeObjectSnapshotEvent : FTakeObjectSnapshotEvent`  
_L20-21_
- inherits: `FTakeObjectSnapshotEvent`

#### struct `UE::LevelSnapshots::FPostTakeObjectSnapshotEvent`  
`struct FPostTakeObjectSnapshotEvent : FTakeObjectSnapshotEvent`  
_L22-23_
- inherits: `FTakeObjectSnapshotEvent`

#### class `UE::LevelSnapshots::ITakeSnapshotListener`  
`class ITakeSnapshotListener`  
_L26-41_
- desc: Exposes callbacks for when a snapshot is taken
- L31 _public function_ `virtual void PreTakeObjectSnapshot(const FPreTakeObjectSnapshotEvent& Params)` — Called before an object's data is recorded by a snapshot.
- L33 _public function_ `virtual void PostTakeObjectSnapshot(const FPostTakeObjectSnapshotEvent& Params)` — Called after an object's data is recorded by a snapshot.
- L36 _public function_ `virtual void PreTakeSnapshot(const FPreTakeSnapshotEventData& Params)` — Called before a snapshot is taken for a world.
- L38 _public function_ `virtual void PostTakeSnapshot(const FPostTakeSnapshotEventData& Params)` — Called after a snapshot is taken for a world.
- L40 _public prototype_ `virtual ~ITakeSnapshotListener() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Params/ObjectSnapshotSerializationData.h` (Public)


#### class `UE::LevelSnapshots::ISnapshotSubobjectMetaData`  
`class ISnapshotSubobjectMetaData`  
_L15-28_
- desc: Manages meta data needed by external modules to restore objects
- L20 _public prototype_ `virtual FSoftObjectPath GetOriginalPath() const = 0;` — Gets the soft path for the object when it was snapshot
- L23 _public prototype_ `virtual void WriteObjectAnnotation(const FObjectAnnotator& Writer) = 0;` — Add data needed for restoring the object
- L25 _public prototype_ `virtual void ReadObjectAnnotation(const FObjectAnnotator& Reader) const = 0;` — Read data needed for restoring the object
- L27 _public prototype_ `virtual ~ISnapshotSubobjectMetaData() = default;`

#### class `UE::LevelSnapshots::ICustomSnapshotSerializationData`  
`class ICustomSnapshotSerializationData`  
_L33-66_
- desc: Utility for saving / restoring properties of an object.
- L38 _public prototype_ `virtual void WriteObjectAnnotation(const FObjectAnnotator& Writer) = 0;` — Add data needed for restoring the object.
- L41 _public prototype_ `virtual void ReadObjectAnnotation(const FObjectAnnotator& Reader) const = 0;` — Read data needed for restoring the object
- L55 _public prototype_ `virtual int32 AddSubobjectSnapshot(UObject* Subobject) = 0;` — Causes the properties of the subobject to be saved. You can add additional meta data needed for restoring by calling GetSubobjectMetaData with this function's result and using ISnapshotSubobjectMetaData::ISnapshotSubobjectMetaData. You need to make sure of the following, or this function will fail: 1. 'Subobject' must be of a subobject of GetSerializedObject() 2. 'Subobject' cannot be visible to standard Level Snapshots serialisation. A subobject is visible if it contained within a uproperty (object reference or collection of references) with the CPF_Edit flag. You can explicitly disallow uproperties using the Level Snapshots module.
- L58 _public prototype_ `virtual TSharedPtr<ISnapshotSubobjectMetaData> GetSubobjectMetaData(int32 Index) = 0;` — Gets the meta data stored for a subobject previously added using AddSubobjectDependency.
- L60 _public prototype_ `virtual const TSharedPtr<ISnapshotSubobjectMetaData> GetSubobjectMetaData(int32 Index) const = 0;`
- L63 _public prototype_ `virtual int32 GetNumSubobjects() const = 0;` — Gets all saved subobject handles.
- L65 _public prototype_ `virtual ~ICustomSnapshotSerializationData() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FObjectAnnotator, FArchive&);`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FObjectAnnotator, FArchive&);` (scope `UE::LevelSnapshots`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/Params/PropertyComparisonParams.h` (Public)


#### struct `UE::LevelSnapshots::FPropertyComparisonParams`  
`struct FPropertyComparisonParams`  
_L15-50_
- L17 _public member_ `ULevelSnapshot* Snapshot;`
- L20 _public member_ `UClass* InspectedClass;` — The class we're looking at. This is not necessarily the class LeafProperty resides in.
- L22 _public member_ `const FProperty* LeafProperty;` — The property being checked
- L25 _public member_ `void* SnapshotContainer;` — Parameter for FProperty::ContainerPtrToValuePtr.
- L27 _public member_ `void* WorldContainer;` — Parameter for FProperty::ContainerPtrToValuePtr.
- L30 _public member_ `UObject* SnapshotObject;` — Either an AActor, UActorComponent, or a subobject of the two.
- L32 _public member_ `UObject* WorldObject;` — Either an AActor, UActorComponent, or a subobject of the two.
- L35 _public member_ `AActor* SnapshotActor;` — Snapshot version of the actor
- L37 _public member_ `AActor* WorldActor;` — Actor currently in the world
- L39 _public function_ `FPropertyComparisonParams(ULevelSnapshot* Snapshot, UClass* InspectedClass, const FProperty* LeafProperty, void* SnapshotContainer, void* WorldContainer, UObject* SnapshotObject, UObject* WorldObject, AActor* SnapshotActor, AActor* WorldActor) : Snapshot(Snapshot) , InspectedClass(InspectedClass) , LeafProperty(LeafProperty) , SnapshotContainer(SnapshotContainer) , WorldContainer(WorldContainer) , SnapshotObject(SnapshotObject) , WorldObject(WorldObject) , SnapshotActor(SnapshotActor) , WorldActor(WorldActor)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Restorability/SnapshotRestorability.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L18 _namespace_ `namespace Restorability` (scope `UE::LevelSnapshots`)
- L21 _prototype_ `bool IsActorDesirableForCapture(const AActor* Actor);` (scope `UE::LevelSnapshots::Restorability`) — Is this actor captured by the snapshot system?
- L23 _prototype_ `bool IsActorRestorable(const AActor* Actor);` (scope `UE::LevelSnapshots::Restorability`) — Can this actor be restored? Stronger requirement than IsActorDesirableForCapture: we may capture the data but not support restoring it at the moment.
- L26 _prototype_ `bool IsComponentDesirableForCapture(const UActorComponent* Component);` (scope `UE::LevelSnapshots::Restorability`) — Is this component captured by the snapshot system?
- L29 _prototype_ `bool IsSubobjectClassDesirableForCapture(const UClass* SubobjectClass);` (scope `UE::LevelSnapshots::Restorability`) — Is this subobject class captured by the snapshot system?
- L31 _prototype_ `bool IsSubobjectDesirableForCapture(const UObject* Subobject);` (scope `UE::LevelSnapshots::Restorability`) — Is this subobject captured by the snapshot system?
- L34 _prototype_ `bool IsPropertyDesirableForCapture(const FProperty* Property);` (scope `UE::LevelSnapshots::Restorability`) — Can the property be captured?
- L36 _prototype_ `bool IsPropertyExplicitlyUnsupportedForCapture(const FProperty* Property);` (scope `UE::LevelSnapshots::Restorability`) — Is this property never captured by the snapshot system?
- L38 _prototype_ `bool IsPropertyExplicitlySupportedForCapture(const FProperty* Property);` (scope `UE::LevelSnapshots::Restorability`) — Is this property always captured by the snapshot system?
- L41 _prototype_ `bool ShouldConsiderMatchedActorForRestoration(const FCanModifyMatchedActorParams& Params, FText* ExclusionReason = nullptr);` (scope `UE::LevelSnapshots::Restorability`) — The actor exists in the world and the snapshot. Should we show it in the list of modified actors?
- L43 _prototype_ `bool ShouldConsiderRemovedActorForRecreation(const FCanRecreateActorParams& Params, FText* ExclusionReason = nullptr);` (scope `UE::LevelSnapshots::Restorability`) — The actor was removed from the snapshot. Should we show it in the list of removed actors?
- L45 _prototype_ `bool ShouldConsiderNewActorForRemoval(const AActor* Actor, FText* ExclusionReason = nullptr);` (scope `UE::LevelSnapshots::Restorability`) — The actor did not exist in the snapshot. Should we show it in the list of added actors?
- L48 _prototype_ `bool IsRestorableProperty(const FProperty* LeafProperty);` (scope `UE::LevelSnapshots::Restorability`) — Is this property captured by the snapshot system?

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Settings/HashSettings.h` (Public)


#### enum `EHashAlgorithmChooseBehavior::Type`  
`enum Type : int`  
_L11-25_
- L16 _public enumerator_ `UseFastest` — Use whichever algorithm is faster
- L20 _public enumerator_ `UseCrc32` — Always use CRC32 (only works if CRC32 is enabled)
- L24 _public enumerator_ `UseMD5` — Always use MD5 (only works if MD5 is enabled)

#### struct `FHashSettings`  
`struct FHashSettings`  
_L30-79_
- reflection: `USTRUCT()`
- L48 _public member_ `double HashCutoffSeconds = 0.3;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")` — Performance trade-off. Used when filtering a snapshot. For filtering, we need to load every actor into memory. Loading actors takes a long time. Instead when a snapshot is taken, we compute its hash. When filtering, we can recompute the hash using the actor in the editor world. If they match, we can skip loading the saved actor data. For most actors, it takes about 600 micro seconds to compute a hash. However, there are outliers which can take more. For such actors, it can be faster to just load the saved actor data into memory. Actors for which hashing took more than this configured variable, we skip hashing altogether and immediately load the actor data.
- L52 _public member_ `bool bUseHashForLoading = true;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")` — Whether to compare world actor's to its saved hash when loading a snapshot. Boosts performance.
- L63 _public member_ `bool bCanUseCRC = true;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")` — Whether Level Snapshots will compute CRC32 hashes (when taking and analysing snapshots) Speed: CRC32 < MD5 < SHA1. Disabling this option results in: 1. Taking a snapshot will be faster (CRC32 will no longer be computed when snapshot is taken) 2. When loading a snapshot, CRC32 is no longer available to quickly check whether an actor has changed.
- L74 _public member_ `bool bCanUseMD5 = true;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")` — Whether Level Snapshots will compute MD5 hashes (when taking and analysing snapshots). Speed: CRC32 < MD5 < SHA1. Disabling this option results in: 1. Taking a snapshot will be faster (MD5 will no longer be computed when snapshot is taken) 2. When loading a snapshot, MD5 is no longer available to quickly check whether an actor has changed.
- L78 _public member_ `TEnumAsByte<EHashAlgorithmChooseBehavior::Type> SnapshotDiffAlgorithm = EHashAlgorithmChooseBehavior::UseFastest;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")` — Which hash algorithm to use when comparing a snapshot to the world.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace EHashAlgorithmChooseBehavior`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Settings/LevelSnapshotsSettings.h` (Public)


#### class `ULevelSnapshotsSettings`  
`class ULevelSnapshotsSettings : public UObject`  
_L11-69_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- L16 _public prototype_ `static ULevelSnapshotsSettings* Get();`
- L19 _public prototype_ `virtual void PostInitProperties() override;`
- L21 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public member_ `FSkippedClassList SkippedClasses;` — `UPROPERTY(config, EditAnywhere, Category = "Level Snapshots|Behavior")` — Specifies classes and properties that should never be captured nor restored.
- L34 _public member_ `float FloatComparisonPrecision = 1e-03f;` — `UPROPERTY(Config, EditAnywhere, Category = "Level Snapshots|Behavior", meta = (ClampMin = "0.00000001", ClampMax = "0.1"))` — Used when comparing float properties. Floats that have changes beyond this point do not show up as changed.
- L38 _public member_ `double DoubleComparisonPrecision = 1e-03;` — `UPROPERTY(Config, EditAnywhere, Category = "Level Snapshots|Behavior", meta = (ClampMin = "0.00000001", ClampMax = "0.1"))` — Used when comparing double properties. Doubles that have changes beyond this point do not show up as changed.
- L56 _public member_ `FHashSettings HashSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Level Snapshots|Performance", meta = (ClampMin = "1"))` — Performance trade-off. Used when filtering a snapshot. For filtering, we need to load every actor into memory. Loading actors takes a long time. Instead when a snapshot is taken, we compute its hash. When filtering, we can recompute the hash using the actor in the editor world. If they match, we can skip loading the saved actor data. For most actors, it takes about 600 micro seconds to compute a hash. However, there are outliers which can take more. For such actors, it can be faster to just load the saved actor data into memory. Actors for which hashing took more than this configured variable, we skip hashing altogether and immediately load the actor data.
- L68 _public member_ `FSnapshotCompressionSettings CompressionSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Level Snapshots|Compression", meta = (ClampMin = "1"))` — Specifies the compression settings to use when a snapshot is saved. These settings affect the time: - taken to save a snapshot - taken to load a snapshot You can safely change these settings even if you're already saved snapshots with different settings.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Settings/SkippedClassList.h` (Public)


#### struct `FSkippedClassList`  
`struct FSkippedClassList`  
_L10-17_
- reflection: `USTRUCT()`
- L16 _public member_ `TSet<FSoftClassPath> SkippedClasses;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")` — These actor and component classes are skipped.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Settings/SnapshotCompressionSettings.h` (Public)


#### enum `ESnapshotCompressionLevel`  
`enum class ESnapshotCompressionLevel : int8`  
_L11-26_
- reflection: `UENUM()`
- desc: ESnapshotCompressionLevel and ESnapshotCompressor copied from OodleDataCompression.h - there is no UENUM version at time of duplication
- L13 _public enumerator_ `HyperFast4 = -4`
- L14 _public enumerator_ `HyperFast3 = -3`
- L15 _public enumerator_ `HyperFast2 = -2`
- L16 _public enumerator_ `HyperFast1 = -1`
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `SuperFast = 1`
- L19 _public enumerator_ `VeryFast = 2`
- L20 _public enumerator_ `Fast = 3`
- L21 _public enumerator_ `Normal = 4`
- L22 _public enumerator_ `Optimal1 = 5`
- L23 _public enumerator_ `Optimal2 = 6`
- L24 _public enumerator_ `Optimal3 = 7`
- L25 _public enumerator_ `Optimal4 = 8`

#### enum `ESnapshotCompressor`  
`enum class ESnapshotCompressor : uint8`  
_L29-41_
- reflection: `UENUM()`
- L34 _public enumerator_ `Selkie = 1` — Lower compression but fastest decodes
- L36 _public enumerator_ `Mermaid = 2` — Mid-level compression with fast decoding
- L38 _public enumerator_ `Kraken = 3` — High compression with fast decoding
- L40 _public enumerator_ `Leviathan = 4` — Highest compression ration

#### struct `FSnapshotCompressionSettings`  
`struct FSnapshotCompressionSettings`  
_L50-78_
- reflection: `USTRUCT()`
- L61 _public member_ `ESnapshotCompressionLevel CompressionLevel = ESnapshotCompressionLevel::Normal;` — `UPROPERTY(EditAnywhere, Category = "Compression")` — Trade-off between compression ratio and time. You usually do not want anything higher than Normal. Normal > Optimal approx. reduces compressed size about 1-2% but increases computation time by about 10x. Each subsequent step has diminishing returns.
- L77 _public member_ `ESnapshotCompressor CompressorAlgorithm = ESnapshotCompressor::Kraken;` — `UPROPERTY(EditAnywhere, Category = "Compression")` — Specifies the algorithm to use for compressing & decompressing snapshot data. Test in July, 2022 for 5.1: A 112 mb size snapshot was compressed with Optimal4 setting: - Selkie		15.8s	14.3mb - Mermaid		23.6s	10.9mb - Kraken 		1m19s	9.3mb - Leviathan 	1m51s	9.0mb Decompression took about 2.7s for each algorithm. @see http://www.radgametools.com/oodlecompressors.htm

#### Free symbols / members of external scopes

- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L43 _namespace_ `namespace Compression` (scope `UE::LevelSnapshots`)
- L45 _function_ `FORCEINLINE FOodleDataCompression::ECompressionLevel CastCompressionLevel(ESnapshotCompressionLevel Value)` (scope `UE::LevelSnapshots::Compression`)
- L46 _function_ `FORCEINLINE FOodleDataCompression::ECompressor CastCompressor(ESnapshotCompressor Value)` (scope `UE::LevelSnapshots::Compression`)
