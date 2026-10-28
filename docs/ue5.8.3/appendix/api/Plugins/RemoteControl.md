# Plugins / RemoteControl

- module root: `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl`
- headers: 44; symbols: 1844
- symbol kinds: class=61, delegate=35, enum=16, enumerator=52, function=235, macro=4, member=359, namespace=10, prototype=989, struct=79, typedef=4
- PrivateDependencyModuleNames: AssetTools, Cbor, DeveloperSettings, Engine, MessageLog, RemoteControlInterception, Serialization, SharedSettingsWidgets, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RemoteControlCommon

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/Factories/RCDefaultValueFactories.h` (Private)


#### class `FLightIntensityDefaultValueFactory`  
`class FLightIntensityDefaultValueFactory : public IRCDefaultValueFactory`  
_L11-22_
- inherits: `IRCDefaultValueFactory`
- desc: A specialized default value factory for handling light components.
- L14 _public prototype_ `static TSharedRef<IRCDefaultValueFactory> MakeInstance();`
- L17 _public prototype_ `virtual bool CanResetToDefaultValue(UObject* InObject, const FRCResetToDefaultArgs& InArgs) const override;`
- L18 _public prototype_ `virtual void ResetToDefaultValue(UObject* InObject, FRCResetToDefaultArgs& InArgs) override;`
- L19 _public prototype_ `virtual bool SupportsClass(const UClass* InObjectClass) const override;`
- L20 _public prototype_ `virtual bool SupportsProperty(const FProperty* InProperty) const override;`

#### class `FOverrideMaterialsDefaultValueFactory`  
`class FOverrideMaterialsDefaultValueFactory : public IRCDefaultValueFactory`  
_L24-35_
- inherits: `IRCDefaultValueFactory`
- L27 _public prototype_ `static TSharedRef<IRCDefaultValueFactory> MakeInstance();`
- L30 _public prototype_ `virtual bool CanResetToDefaultValue(UObject* InObject, const FRCResetToDefaultArgs& InArgs) const override;`
- L31 _public prototype_ `virtual void ResetToDefaultValue(UObject* InObject, FRCResetToDefaultArgs& InArgs) override;`
- L32 _public prototype_ `virtual bool SupportsClass(const UClass* InObjectClass) const override;`
- L33 _public prototype_ `virtual bool SupportsProperty(const FProperty* InProperty) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/Factories/RemoteControlMaskingFactories.h` (Private)


#### class `FVectorMaskingFactory`  
`class FVectorMaskingFactory : public IRemoteControlMaskingFactory`  
_L10-25_
- reflection: `UE_DEPRECATED(5.5, "Deprecated in favor of RemoteControlMaskingUtil.")`
- inherits: `IRemoteControlMaskingFactory`
- L13 _public prototype_ `static TSharedRef<IRemoteControlMaskingFactory> MakeInstance();`
- L16 _public prototype_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive) override;`
- L17 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;`
- L18 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const override;`
- L22 _public prototype_ `FVectorMaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L23 _public prototype_ `FVectorMaskingFactory(const FVectorMaskingFactory&) = default;`
- L24 _public prototype_ `FVectorMaskingFactory(FVectorMaskingFactory&&) = default;`

#### class `FVector4MaskingFactory`  
`class FVector4MaskingFactory : public IRemoteControlMaskingFactory`  
_L30-45_
- reflection: `UE_DEPRECATED(5.5, "Deprecated in favor of RemoteControlMaskingUtil.")`
- inherits: `IRemoteControlMaskingFactory`
- L33 _public prototype_ `static TSharedRef<IRemoteControlMaskingFactory> MakeInstance();`
- L36 _public prototype_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive) override;`
- L37 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;`
- L38 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const override;`
- L42 _public prototype_ `FVector4MaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L43 _public prototype_ `FVector4MaskingFactory(const FVector4MaskingFactory&) = default;`
- L44 _public prototype_ `FVector4MaskingFactory(FVector4MaskingFactory&&) = default;`

#### class `FIntVectorMaskingFactory`  
`class FIntVectorMaskingFactory : public IRemoteControlMaskingFactory`  
_L50-65_
- reflection: `UE_DEPRECATED(5.5, "Deprecated in favor of RemoteControlMaskingUtil.")`
- inherits: `IRemoteControlMaskingFactory`
- L53 _public prototype_ `static TSharedRef<IRemoteControlMaskingFactory> MakeInstance();`
- L56 _public prototype_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive) override;`
- L57 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;`
- L58 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const override;`
- L62 _public prototype_ `FIntVectorMaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L63 _public prototype_ `FIntVectorMaskingFactory(const FIntVectorMaskingFactory&) = default;`
- L64 _public prototype_ `FIntVectorMaskingFactory(FIntVectorMaskingFactory&&) = default;`

#### class `FIntVector4MaskingFactory`  
`class FIntVector4MaskingFactory : public IRemoteControlMaskingFactory`  
_L70-85_
- reflection: `UE_DEPRECATED(5.5, "Deprecated in favor of RemoteControlMaskingUtil.")`
- inherits: `IRemoteControlMaskingFactory`
- L73 _public prototype_ `static TSharedRef<IRemoteControlMaskingFactory> MakeInstance();`
- L76 _public prototype_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive) override;`
- L77 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;`
- L78 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const override;`
- L82 _public prototype_ `FIntVector4MaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L83 _public prototype_ `FIntVector4MaskingFactory(const FIntVector4MaskingFactory&) = default;`
- L84 _public prototype_ `FIntVector4MaskingFactory(FIntVector4MaskingFactory&&) = default;`

#### class `FRotatorMaskingFactory`  
`class FRotatorMaskingFactory : public IRemoteControlMaskingFactory`  
_L90-105_
- reflection: `UE_DEPRECATED(5.5, "Deprecated in favor of RemoteControlMaskingUtil.")`
- inherits: `IRemoteControlMaskingFactory`
- L93 _public prototype_ `static TSharedRef<IRemoteControlMaskingFactory> MakeInstance();`
- L96 _public prototype_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive) override;`
- L97 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;`
- L98 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const override;`
- L102 _public prototype_ `FRotatorMaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L103 _public prototype_ `FRotatorMaskingFactory(const FRotatorMaskingFactory&) = default;`
- L104 _public prototype_ `FRotatorMaskingFactory(FRotatorMaskingFactory&&) = default;`

#### class `FColorMaskingFactory`  
`class FColorMaskingFactory : public IRemoteControlMaskingFactory`  
_L110-125_
- reflection: `UE_DEPRECATED(5.5, "Deprecated in favor of RemoteControlMaskingUtil.")`
- inherits: `IRemoteControlMaskingFactory`
- L113 _public prototype_ `static TSharedRef<IRemoteControlMaskingFactory> MakeInstance();`
- L116 _public prototype_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive) override;`
- L117 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;`
- L118 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const override;`
- L122 _public prototype_ `FColorMaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L123 _public prototype_ `FColorMaskingFactory(const FColorMaskingFactory&) = default;`
- L124 _public prototype_ `FColorMaskingFactory(FColorMaskingFactory&&) = default;`

#### class `FLinearColorMaskingFactory`  
`class FLinearColorMaskingFactory : public IRemoteControlMaskingFactory`  
_L130-145_
- reflection: `UE_DEPRECATED(5.5, "Deprecated in favor of RemoteControlMaskingUtil.")`
- inherits: `IRemoteControlMaskingFactory`
- L133 _public prototype_ `static TSharedRef<IRemoteControlMaskingFactory> MakeInstance();`
- L136 _public prototype_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive) override;`
- L137 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;`
- L138 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const override;`
- L142 _public prototype_ `FLinearColorMaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L143 _public prototype_ `FLinearColorMaskingFactory(const FLinearColorMaskingFactory&) = default;`
- L144 _public prototype_ `FLinearColorMaskingFactory(FLinearColorMaskingFactory&&) = default;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/PropertyIdHandler/BasePropertyIdHandler.h` (Private)


#### class `FBasePropertyIdHandler`  
`class FBasePropertyIdHandler : public IPropertyIdHandler`  
_L7-17_
- inherits: `IPropertyIdHandler`
- L11 _public prototype_ `virtual bool IsPropertySupported(const FProperty* InProperty) const override;`
- L12 _public prototype_ `virtual EPropertyBagPropertyType GetPropertyType(const FProperty* InProperty) const override;`
- L13 _public prototype_ `virtual FName GetPropertySuperTypeName(const FProperty* InProperty) const override;`
- L14 _public prototype_ `virtual FName GetPropertySubTypeName(const FProperty* InProperty) const override;`
- L15 _public prototype_ `virtual UObject* GetPropertyTypeObject(const FProperty* InProperty) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/PropertyIdHandler/EnumPropertyIdHandler.h` (Private)


#### class `FEnumPropertyIdHandler`  
`class FEnumPropertyIdHandler : public IPropertyIdHandler`  
_L7-17_
- inherits: `IPropertyIdHandler`
- L11 _public prototype_ `virtual bool IsPropertySupported(const FProperty* InProperty) const override;`
- L12 _public prototype_ `virtual EPropertyBagPropertyType GetPropertyType(const FProperty* InProperty) const override;`
- L13 _public prototype_ `virtual FName GetPropertySuperTypeName(const FProperty* InProperty) const override;`
- L14 _public prototype_ `virtual FName GetPropertySubTypeName(const FProperty* InProperty) const override;`
- L15 _public prototype_ `virtual UObject* GetPropertyTypeObject(const FProperty* InProperty) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/PropertyIdHandler/ObjectPropertyIdHandler.h` (Private)


#### class `FObjectPropertyIdHandler`  
`class FObjectPropertyIdHandler : public IPropertyIdHandler`  
_L7-17_
- inherits: `IPropertyIdHandler`
- L11 _public prototype_ `virtual bool IsPropertySupported(const FProperty* InProperty) const override;`
- L12 _public prototype_ `virtual EPropertyBagPropertyType GetPropertyType(const FProperty* InProperty) const override;`
- L13 _public prototype_ `virtual FName GetPropertySuperTypeName(const FProperty* InProperty) const override;`
- L14 _public prototype_ `virtual FName GetPropertySubTypeName(const FProperty* InProperty) const override;`
- L15 _public prototype_ `virtual UObject* GetPropertyTypeObject(const FProperty* InProperty) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/PropertyIdHandler/StructPropertyIdHandler.h` (Private)


#### class `FStructPropertyIdHandler`  
`class FStructPropertyIdHandler : public IPropertyIdHandler`  
_L7-17_
- inherits: `IPropertyIdHandler`
- L11 _public prototype_ `virtual bool IsPropertySupported(const FProperty* InProperty) const override;`
- L12 _public prototype_ `virtual EPropertyBagPropertyType GetPropertyType(const FProperty* InProperty) const override;`
- L13 _public prototype_ `virtual FName GetPropertySuperTypeName(const FProperty* InProperty) const override;`
- L14 _public prototype_ `virtual FName GetPropertySubTypeName(const FProperty* InProperty) const override;`
- L15 _public prototype_ `virtual UObject* GetPropertyTypeObject(const FProperty* InProperty) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlExposeRegistry.h` (Private)


#### struct `FRCEntityWrapper`  
`struct FRCEntityWrapper`  
_L18-50_
- reflection: `USTRUCT()`
- desc: Wrapper class used to serialize exposable entities in a generic way.
- L22 _public prototype_ `FRCEntityWrapper() = default;`
- L24 _public prototype_ `FRCEntityWrapper(const FRemoteControlEntity& InEntity, UScriptStruct* InEntityType);`
- L27 _public prototype_ `TSharedPtr<FRemoteControlEntity> Get();` — Get the wrapped entity.
- L30 _public prototype_ `TSharedPtr<const FRemoteControlEntity> Get() const;` — Get the wrapped entity.
- L33 _public prototype_ `const UScriptStruct* GetType() const;` — Get the type of the wrapped entity.
- L36 _public prototype_ `bool IsValid() const;` — Returns whether the type and the underlying data is valid.
- L39 _public prototype_ `bool Serialize(FArchive& Ar);`
- L41 _public prototype_ `bool operator==(const FGuid& WrappedId) const;`
- L42 _public prototype_ `bool operator==(const FRCEntityWrapper& Other) const;`
- L47 _private member_ `UScriptStruct* EntityType = nullptr;` — Holds the type of the wrapped entity.
- L49 _private member_ `TSharedPtr<FRemoteControlEntity> WrappedEntity;` — Pointer to underlying remote control property.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRCEntityWrapper> : public TStructOpsTypeTraitsBase2<FRCEntityWrapper>`  
_L52-59_
- inherits: `TStructOpsTypeTraitsBase2<FRCEntityWrapper>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L55-58_

#### class `URemoteControlExposeRegistry`  
`class URemoteControlExposeRegistry : public UObject`  
_L62-233_
- reflection: `UCLASS()`
- inherits: `UObject`
- L70 _public prototype_ `TArray<TSharedPtr<const FRemoteControlEntity>> GetExposedEntities() const;` — Get all the exposed entities.
- L75 _public prototype_ `TArray<TSharedPtr<const FRemoteControlEntity>> GetExposedEntities(UScriptStruct* EntityType) const;` — Get the exposed entities of a certain type.
- L80 _public prototype_ `TArray<TSharedPtr<FRemoteControlEntity>> GetExposedEntities(UScriptStruct* EntityType);` — Get the exposed entities of a certain type.
- L86 _public function_ `template <typename EntityType = FRemoteControlEntity> TArray<TSharedPtr<EntityType>> GetExposedEntities()` — Get the exposed entities of a certain type.
- L100 _public function_ `template <typename EntityType> TArray<TSharedPtr<EntityType>> GetExposedEntities() const` — Get the exposed entities of a certain type.
- L111 _public prototype_ `TSharedPtr<const FRemoteControlEntity> GetExposedEntity(const FGuid& ExposedEntityId, const UScriptStruct* EntityType = FRemoteControlEntity::StaticStruct()) const;` — Get an exposed entity from the registry. @param ExposedEntityId the id of the entity to get. @param EntityType the type of entity to search for. @return the exposed entity pointer, or an invalid pointer otherwise.
- L119 _public prototype_ `TSharedPtr<FRemoteControlEntity> GetExposedEntity(const FGuid& ExposedEntityId, const UScriptStruct* EntityType = FRemoteControlEntity::StaticStruct());` — Get an exposed entity from the registry. @param ExposedEntityId the id of the entity to get. @param EntityType the type of entity to search for. @return the exposed entity pointer, or an invalid pointer otherwise.
- L127 _public function_ `template <typename EntityType> TSharedPtr<const EntityType> GetExposedEntity(const FGuid& ExposedEntityId) const` — Get an exposed entity from the registry. @param ExposedEntityId the id of the entity to get. @return the exposed entity pointer, or an invalid pointer otherwise.
- L138 _public function_ `template <typename EntityType> TSharedPtr<EntityType> GetExposedEntity(const FGuid& ExposedEntityId)` — Get an exposed entity from the registry. @param ExposedEntityId the id of the entity to get. @return the exposed entity pointer, or an invalid pointer otherwise.
- L150 _public prototype_ `const UScriptStruct* GetExposedEntityType(const FGuid& ExposedEntityId) const;` — Get the type of an exposed entity. @param ExposedEntityId The id of the entity to find. @return the entity type (ie. FRemoteControlActor) or nullptr if not found.
- L155 _public function_ `const TSet<TObjectPtr<UScriptStruct>>& GetExposedEntityTypes() const` — Get all the exposed types in the registry (ie. FRemoteControlActor)
- L161 _public prototype_ `const bool IsEmpty() const;` — Returns true when Exposed Entities is empty.
- L168 _public prototype_ `TSharedPtr<FRemoteControlEntity> AddExposedEntity(FRemoteControlEntity&& EntityToExpose, UScriptStruct* EntityType);` — Add an entity to the set of exposed entities of its type. @param EntityToExpose the entity to expose. @param EntityType EntityType the type of the entity to expose.
- L173 _public prototype_ `void RemoveExposedEntity(const FGuid& Id);` — Remove an exposed entity from the registry using its id.
- L182 _public prototype_ `FName RenameExposedEntity(const FGuid& Id, FName NewLabel);` — Rename an exposed entity. @param Id the entity's id @param NewLabel the new label to assign to the entity. @return The assigned label, which might be suffixed if the label already exists in the registry or NAME_None if the entity was not found.
- L189 _public prototype_ `FGuid GetExposedEntityId(FName EntityLabel) const;` — Get an entity's id using it's label. @param EntityLabel the entity's label. @return The entity's id if found, otherwise an invalid guid.
- L196 _public prototype_ `FName GenerateUniqueLabel(FName BaseName) const;` — Generate a unique label using a base name. @param BaseName The base name to use. @param The generated name.
- L199 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L200 _public prototype_ `virtual void PostLoad() override;`
- L201 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L205 _public prototype_ `void CacheLabels();` — Cache labels for all exposed entities.
- L209 _private prototype_ `TSharedPtr<FRemoteControlEntity> GetEntity(const FGuid& EntityId);` — Get a raw pointer to an entity using its id.
- L212 _private prototype_ `TSharedPtr<const FRemoteControlEntity> GetEntity(const FGuid& EntityId) const;` — Get a raw pointer to an entity using its id.
- L217 _private member_ `TArray<FRCEntityWrapper> ExposedEntitiesArray;` — `UPROPERTY()` — Holds the exposed entities.
- L223 _private member_ `TSet<FRCEntityWrapper> ExposedEntities_DEPRECATED;` — `UE_DEPRECATED(5.5, "Changed to an ordered TArray.")` — `UPROPERTY()` — DEPRECATED 5.5 Holds the exposed entities. Instead refer to the new TArray<FRCEntityWrapper> URemoteControlExposeRegistry::ExposedEntities
- L228 _private member_ `TMap<FName, FGuid> LabelToIdCache;` — `UPROPERTY(Transient)` — Cache of label to ids.
- L232 _private member_ `TSet<TObjectPtr<UScriptStruct>> ExposedTypes;` — `UPROPERTY()` — Holds the types of entities exposed in the registry.

#### Free symbols / members of external scopes

- L56 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon1778dad60103`)
- L57 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon1778dad60103`)
- L92 _function_ `Algo::Transform(Entities, CastEntities, [](const TSharedPtr<FRemoteControlEntity>& InEntity){ return StaticCastSharedPtr<EntityType>(InEntity);});` (scope `URemoteControlExposeRegistry::GetExposedEntities`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlInterceptionHelpers.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `constexpr ERCAccess ToInternal(ERCIAccess Value)` — Internal helper for ERCIAccess->ERCAccess conversion
- L34 _function_ `constexpr ERCPayloadType ToInternal(ERCIPayloadType Value)` — Internal helper for ERCIPayloadType->ERCPayloadType conversion
- L49 _function_ `constexpr ERCModifyOperation ToInternal(ERCIModifyOperation Value)` — Internal helper for ERCIModifyOperation->ERCModifyOperation conversion
- L73 _function_ `constexpr ERCIAccess ToExternal(ERCAccess Value)` — Internal helper for ERCAccess->ERCIAccess conversion
- L97 _function_ `constexpr ERCIPayloadType ToExternal(ERCPayloadType Value)` — Internal helper for ERCIPayloadType->ERCPayloadType conversion
- L112 _function_ `constexpr ERCIModifyOperation ToExternal(ERCModifyOperation Value)` — Internal helper for ERCModifyOperation->ERCIModifyOperation conversion

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlInterceptionProcessor.h` (Private)


#### class `FRemoteControlInterceptionProcessor`  
`class FRemoteControlInterceptionProcessor : public IRemoteControlInterceptionFeatureProcessor`  
_L11-25_
- inherits: `IRemoteControlInterceptionFeatureProcessor`
- desc: Remote control interception processor feature
- L15 _public prototype_ `FRemoteControlInterceptionProcessor() = default;`
- L16 _public prototype_ `virtual ~FRemoteControlInterceptionProcessor() = default;`
- L20 _public prototype_ `virtual void SetObjectProperties(FRCIPropertiesMetadata& InProperties) override;` — IRemoteControlInterceptionCommands interface
- L21 _public prototype_ `virtual void ResetObjectProperties(FRCIObjectMetadata& InObject) override;`
- L22 _public prototype_ `virtual void InvokeCall(FRCIFunctionMetadata& InFunction) override;`
- L23 _public prototype_ `virtual void SetPresetController(FRCIControllerMetadata& InController) override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlModule.h` (Private)


#### class `FRemoteControlModule`  
`class FRemoteControlModule : public IRemoteControlModule`  
_L18-320_
- inherits: `IRemoteControlModule`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `virtual FOnPresetRegistered& OnPresetRegistered() override;`
- L28 _public prototype_ `virtual FOnPresetUnregistered& OnPresetUnregistered() override;`
- L29 _public prototype_ `virtual FOnError& OnError() override;`
- L30 _public prototype_ `virtual bool RegisterPreset(FName Name, URemoteControlPreset* Preset) override;`
- L31 _public prototype_ `virtual void UnregisterPreset(FName Name) override;`
- L32 _public prototype_ `virtual bool RegisterEmbeddedPreset(URemoteControlPreset* Preset, bool bReplaceExisting) override;`
- L33 _public prototype_ `virtual void UnregisterEmbeddedPreset(FName Name) override;`
- L34 _public prototype_ `virtual void UnregisterEmbeddedPreset(URemoteControlPreset* Preset) override;`
- L35 _public prototype_ `virtual bool CanResetToDefaultValue(UObject* InObject, const FRCResetToDefaultArgs& InArgs) const override;`
- L36 _public prototype_ `virtual bool HasDefaultValueCustomization(const UObject* InObject, const FProperty* InProperty) const override;`
- L37 _public prototype_ `virtual void ResetToDefaultValue(UObject* InObject, FRCResetToDefaultArgs& InArgs) override;`
- L39 _public prototype_ `virtual void PerformMasking(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) override;` — `UE_DEPRECATED(5.5, "PerformMasking is deprecated, masking is now applied where appropriate automatically.")`
- L40 _public prototype_ `virtual void RegisterMaskingFactoryForType(UScriptStruct* RemoteControlPropertyType, const TSharedPtr<IRemoteControlMaskingFactory>& InMaskingFactory) override;`
- L41 _public prototype_ `virtual void UnregisterMaskingFactoryForType(UScriptStruct* RemoteControlPropertyType) override;`
- L42 _public prototype_ `virtual bool SupportsMasking(const UScriptStruct* InStruct) const override;`
- L43 _public prototype_ `virtual bool SupportsMasking(const FProperty* InProperty) const override;`
- L44 _public prototype_ `virtual bool ResolveCall(const FString& ObjectPath, const FString& FunctionName, FRCCallReference& OutCallRef, FString* OutErrorText) override;`
- L45 _public prototype_ `virtual bool InvokeCall(FRCCall& InCall, ERCPayloadType InPayloadType = ERCPayloadType::Json, const TArray<uint8>& InInterceptPayload = TArray<uint8>()) override;`
- L46 _public prototype_ `virtual bool ResolveObject(ERCAccess AccessType, const FString& ObjectPath, const FString& PropertyName, FRCObjectReference& OutObjectRef, FString* OutErrorText = nullptr) override;`
- L47 _public prototype_ `virtual bool ResolveObjectProperty(ERCAccess AccessType, UObject* Object, FRCFieldPathInfo PropertyPath, FRCObjectReference& OutObjectRef, FString* OutErrorText = nullptr) override;`
- L48 _public prototype_ `virtual bool GetObjectProperties(const FRCObjectReference& ObjectAccess, IStructSerializerBackend& Backend) override;`
- L49 _public prototype_ `virtual bool SetObjectProperties(const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, ERCPayloadType InPayloadType, const TArray<uint8>& InPayload, ERCModifyOperation Operation, const ERCModifyOperationFlags ModifyOperationFlags = ERCModifyOperationFlags::None) override;`
- L50 _public prototype_ `virtual bool ResetObjectProperties(const FRCObjectReference& ObjectAccess, const bool bAllowIntercept) override;`
- L51 _public prototype_ `virtual bool InsertToObjectArrayProperty(int32 Index, const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, ERCPayloadType InPayloadType, const TArray<uint8>& InInterceptPayload) override;`
- L52 _public prototype_ `virtual bool RemoveFromObjectArrayProperty(int32 Index, const FRCObjectReference& ObjectAccess) override;`
- L53 _public prototype_ `virtual bool AppendToObjectArrayProperty(const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, ERCPayloadType InPayloadType, const TArray<uint8>& InInterceptPayload) override;`
- L54 _public prototype_ `virtual bool SetPresetController(const FName PresetName, const FName ControllerName, IStructDeserializerBackend& Backend, const TArray<uint8>& InPayload, const bool bAllowIntercept) override;`
- L55 _public prototype_ `virtual bool SetPresetController(const FName PresetName, class URCVirtualPropertyBase* VirtualProperty, IStructDeserializerBackend& Backend, const TArray<uint8>& InPayload, const bool bAllowIntercept) override;`
- L56 _public prototype_ `virtual TOptional<FExposedFunction> ResolvePresetFunction(const FResolvePresetFieldArgs& Args) const override;`
- L57 _public prototype_ `virtual TOptional<FExposedProperty> ResolvePresetProperty(const FResolvePresetFieldArgs& Args) const override;`
- L58 _public prototype_ `virtual URemoteControlPreset* ResolvePreset(FName PresetName) const override;`
- L59 _public prototype_ `virtual URemoteControlPreset* ResolvePreset(const FGuid& PresetId) const override;`
- L60 _public prototype_ `virtual URemoteControlPreset* CreateTransientPreset() override;`
- L61 _public prototype_ `virtual bool DestroyTransientPreset(FName PresetName) override;`
- L62 _public prototype_ `virtual bool DestroyTransientPreset(const FGuid& PresetId) override;`
- L63 _public prototype_ `virtual bool IsPresetTransient(FName PresetName) const override;`
- L64 _public prototype_ `virtual bool IsPresetTransient(const FGuid& PresetId) const override;`
- L65 _public prototype_ `virtual void GetPresets(TArray<TSoftObjectPtr<URemoteControlPreset>>& OutPresets) const override;`
- L66 _public prototype_ `virtual void GetPresetAssets(TArray<FAssetData>& OutPresetAssets, bool bIncludeTransient = true) const override;`
- L67 _public prototype_ `virtual void GetEmbeddedPresets(TArray<TWeakObjectPtr<URemoteControlPreset>>& OutEmbeddedPresets) const override;`
- L68 _public prototype_ `virtual const TMap<FName, FEntityMetadataInitializer>& GetDefaultMetadataInitializers() const override;`
- L69 _public prototype_ `virtual bool RegisterDefaultEntityMetadata(FName MetadataKey, FEntityMetadataInitializer MetadataInitializer) override;`
- L70 _public prototype_ `virtual void UnregisterDefaultEntityMetadata(FName MetadataKey) override;`
- L71 _public prototype_ `virtual bool PropertySupportsRawModificationWithoutEditor(FProperty* Property, UClass* OwnerClass = nullptr) const override;`
- L72 _public prototype_ `virtual bool PropertySupportsRawModification(FProperty* InProperty, const UObject* InObject, const bool bInWithEditor, FString* OutError = nullptr) const override;`
- L73 _public prototype_ `virtual void RegisterEntityFactory( const FName InFactoryName, const TSharedRef<IRemoteControlPropertyFactory>& InFactory) override;`
- L74 _public prototype_ `virtual void UnregisterEntityFactory( const FName InFactoryName ) override;`
- L75 _public prototype_ `virtual FGuid BeginManualEditorTransaction(const FText& InDescription, uint32 TypeHash) override;`
- L76 _public prototype_ `virtual int32 EndManualEditorTransaction(const FGuid& TransactionId) override;`
- L77 _public function_ `virtual const TMap<FName, TSharedPtr<IRemoteControlPropertyFactory>>& GetEntityFactories() const override`
- L78 _public prototype_ `virtual bool CanBeAccessedRemotely(UObject* Object) const override;`
- L79 _public prototype_ `virtual TSharedPtr<IPropertyIdHandler> GetPropertyIdHandlerFor(FProperty* InProperty) override;`
- L83 _protected prototype_ `virtual void RegisterPropertyIdPropertyHandlerImpl(const TSharedRef<IPropertyIdHandler>& InPropertyIdPropertyHandler) override;`
- L87 _private prototype_ `void RefreshEditorPostSetObjectProperties(const FRCObjectReference& ObjectAccess);` — Refreshes Editor related visuals like location Gizmo for relevant properties (like Location of a SceneComponent)
- L90 _private prototype_ `void CachePresets() const;` — Cache all presets in the project for the ResolvePreset function.
- L93 _private prototype_ `void OnAssetAdded(const FAssetData& AssetData);`
- L94 _private prototype_ `void OnAssetRemoved(const FAssetData& AssetData);`
- L95 _private prototype_ `void OnAssetRenamed(const FAssetData& AssetData, const FString&);`
- L96 _private prototype_ `void OnEmbeddedPresetRenamed(URemoteControlPreset* Preset);`
- L99 _private prototype_ `bool DestroyTransientPreset(URemoteControlPreset* Preset);` — Destroy a transient preset using an object reference.
- L110 _private prototype_ `static bool DeserializeDeltaModificationData(const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, ERCModifyOperation Operation, TArray<uint8>& OutData);` — Deserialize data for a non-EQUAL modification request and apply the operation to the resulting data. @param ObjectAccess Data about the object/property for which modification was requested. @param Backend Deserialization backend for the modification request. @param Operation Type of operation to apply to the value. @param OutData Buffer used to deserialize data from the backend and contain the result value. @return True if the data was successfully deserialized and modified.
- L115 _private prototype_ `void RegisterDefaultValueFactoryForType(UClass* RemoteControlPropertyType, const FName PropertyName, const TSharedPtr<IRCDefaultValueFactory>& InDefaultValueFactory);` — Register a default factory to handle that default value for the supported properties.
- L120 _private prototype_ `void UnregisterDefaultValueFactoryForType(UClass* RemoteControlPropertyType, const FName PropertyName);` — Unregister a previously registered default value factory.
- L125 _private prototype_ `void RegisterDefaultValueFactories();` — Register(s) default value factories of supported types.
- L130 _private prototype_ `void RegisterMaskingFactories();` — Register(s) masking factories of supported types.
- L135 _private prototype_ `void RegisterPropertyIdHandler();` — Register(s) masking factories of supported types.
- L140 _private prototype_ `void PopulateDisallowedFunctions();` — Populate the list of functions that cannot be called remotely.
- L145 _private prototype_ `bool CanInterceptFunction(const FRCCall& RCCall) const;` — Whether function can be intercepted by a remote control interceptor.
- L150 _private prototype_ `void LogOnce(ELogVerbosity::Type InVerbosity, const FString& LogDetails, const FString& FileName, int32 LineNumber) const;` — Used to log once per program execution. Called by the REMOTE_CONTROL_LOG_ONCE macro.
- L159 _private prototype_ `bool AddToArrayProperty(const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, TFunctionRef<int32(FScriptArrayHelper&)> ModifyFunction);` — Add an item to an array property, handling transactions and editor events automatically. @param ObjectAccess Reference to the array property to be modified. @param Backend Deserialization backend for the value to be added to the array. This will be deserialized into the array at the index provided by ModifyFunction. @param ModifyFunction Function which takes an array helper, attempts to modify the array, and returns the index of the new item (or INDEX_NONE if the request is invalid).
- L166 _private prototype_ `bool ModifyArrayProperty(const FRCObjectReference& ObjectAccess, TFunctionRef<bool(FScriptArrayHelper&)> ModifyFunction);` — Modify an array property, handling transactions and editor events automatically. @param ObjectAccess Reference to the array property to be modified. @param ModifyFunction Function which takes an array helper, attempts to modify the array, and returns true if the request was valid.
- L169 _private prototype_ `bool IsFunctionAllowed(UFunction* Function);` — Returns whether the function is allowed to be called remotely.
- L180 _private prototype_ `bool StartPropertyTransaction(FRCObjectReference& ObjectReference, const FText& InChangeDescription, bool& bOutGeneratedTransaction);` — Create a transaction to modify an object's property, taking into account any ongoing transactions before this one. @param ObjectReference A reference to the object to be modified. @param InChangeDescription The description of the transaction to be created. @param bOutGeneratedTransaction Set to true if a transaction needed to be created, else false. @return true if the property is ready to be modified, else false.
- L188 _private prototype_ `void SnapshotOrEndTransaction(FRCObjectReference& ObjectReference, bool bGeneratedTransaction);` — Depending on transaction mode, either snapshot the object to the transaction buffer or end the transaction. This should be called after StartPropertyTransaction and then modifying the object's properties. @param ObjectReference A reference to the object to be modified. @param bGeneratedTransaction The value of bOutGeneratedTransaction provided by StartPropertyTransaction.
- L194 _private prototype_ `void EndOngoingModificationIfMismatched(uint32 TypeHash);` — End the ongoing modification if one exists and is a mismatch for the new object to edit. @param TypeHash The type hash of the object we want to modify after this check.
- L197 _private prototype_ `void TestOrFinalizeOngoingChange(bool bForceEndChange = false);` — Finalize an ongoing change, triggering post edit change on the tracked object.
- L200 _private prototype_ `void HandleMapPreLoad(const FString& MapName);`
- L203 _private prototype_ `void HandleEnginePostInit();` — Callback to handle registering delegates once the engine has finished its startup.
- L206 _private prototype_ `void RegisterEditorDelegates();`
- L207 _private prototype_ `void UnregisterEditorDelegates();`
- L212 _private prototype_ `void RegisterLocalForwardingInterceptor();` — Registers the local forwarding interceptor.
- L215 _private prototype_ `void UnregisterLocalForwardingInterceptor();` — Unregisters the local forwarding interceptor.
- L218 _private prototype_ `void UnregisterConsoleObjects();` — Unregisters the console objects from the console manager.
- L222 _private member_ `mutable TMap<FName, TArray<FAssetData>> CachedPresetsByName;` — Cache of preset names to preset assets
- L225 _private member_ `mutable TMap<FGuid, FName> CachedPresetNamesById;` — Cache of ids to preset names.
- L231 _private member_ `TMap<FName, TWeakObjectPtr<URemoteControlPreset>> EmbeddedPresets;` — Listed of hosted (non-asset based) presets. We can assume that all hosted presets are "active," so the list should be relatively short.
- L234 _private member_ `TSet<FAssetData> TransientPresets;` — Temporary presets that aren't saved as assets or directly visible to the editor's user.
- L237 _private member_ `uint32 NextTransientPresetIndex = 0;` — Index of the next created transient preset, to avoid naming collisions.
- L240 _private member_ `TMap<FName, FEntityMetadataInitializer> DefaultMetadataInitializers;` — Map of registered default metadata initializers.
- L243 _private member_ `FOnPresetRegistered OnPresetRegisteredDelegate;` — Delegate for preset registration
- L246 _private member_ `FOnPresetUnregistered OnPresetUnregisteredDelegate;` — Delegate for preset unregistration
- L249 _private member_ `FOnError OnErrorDelegate;` — Delegate for errors to allow external custom handling.
- L252 _private member_ `TUniquePtr<IRemoteControlInterceptionFeatureProcessor> RCIProcessor;` — RC Processor feature instance
- L258 _private member_ `TUniquePtr<IRemoteControlInterceptionFeatureInterceptor> RCILocalForwardingInterceptor;` — RC Local Forwarding interceptor instance. When this is enabled it can locally emulate interception and forwarding to the RCI processor.
- L267 _private function_ `friend uint32 GetTypeHash(const FOngoingChange& Modification)`
- L288 _private member_ `TOptional<FOngoingChange> OngoingModification;` — Ongoing change that needs to end its transaction and call PostEditChange in the case of a property modification.
- L291 _private member_ `FTimerHandle OngoingChangeTimer;` — Handle to the timer that that ends the ongoing change in regards to PostEditChange and transactions.
- L294 _private member_ `FTSTicker::FDelegateHandle FallbackOngoingChangeTimer;` — Handle to the timer that that ends the ongoing change in regards to PostEditChange and transactions.
- L297 _private member_ `static constexpr float SecondsBetweenOngoingChangeCheck = 0.2f;` — Delay before we check if a modification is no longer ongoing.
- L302 _private member_ `TMap<FName, TSharedPtr<IRemoteControlPropertyFactory>> EntityFactories;` — Map of the factories which is responsible for the Remote Control property creation
- L305 _private member_ `TMap<TWeakObjectPtr<UScriptStruct>, TSharedPtr<IRemoteControlMaskingFactory>> MaskingFactories;` — Map of the factories which is responsible for the Remote Control property masking.
- L308 _private member_ `TSet<TSharedPtr<FRCMaskingOperation>> ActiveMaskingOperations;` — Holds the set of active masking operations.
- L311 _private member_ `TMap<FName, TSharedPtr<IRCDefaultValueFactory>> DefaultValueFactories;` — Map of the factories which is responsible for resetting the Remote Control property to its default value.
- L313 _private member_ `TSet<TSharedPtr<IPropertyIdHandler>> PropertyIdPropertyHandlers;`
- L316 _private member_ `TSet<TWeakObjectPtr<UFunction>> FunctionDisallowList;` — List of functions that can't be called remotely.
- L319 _private member_ `TArray<IConsoleObject*> ConsoleObjects;` — Keep track of the registered console objects for automatic unregistration on module shutdown.

#### struct `FRemoteControlModule::FOngoingChange`  
`struct FOngoingChange`  
_L262-285_
- desc: Flags for a given RC change.
- L264 _public prototype_ `FOngoingChange(FRCObjectReference InReference);`
- L265 _public prototype_ `FOngoingChange(FRCCallReference InReference);`
- L280 _public member_ `TVariant<FRCObjectReference, FRCCallReference> Reference;` — Reference to either the property we're modifying or the function we're calling.
- L282 _public member_ `bool bHasStartedTransaction = false;` — Whether this change was triggered with a transaction or not.
- L284 _public member_ `bool bWasTriggeredSinceLastPass = true;` — Whether this change was triggered since the last tick of OngoingChangeTimer.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlPresetRebindingManager.h` (Private)


#### struct `FFindBindingForEntityArgs`  
`struct FFindBindingForEntityArgs`  
_L9-14_
- L11 _public member_ `const TSharedPtr<FRemoteControlEntity>& Entity;`
- L12 _public member_ `const TArray<UObject*>& PotentialMatches;`
- L13 _public member_ `const TMap<uint32, TSet<UObject*>>& ExistingEntityMatches;`

#### struct `FDefaultRebindingPolicy`  
`struct FDefaultRebindingPolicy`  
_L19-22_
- desc: Default rebinding policy: Find first object that supports the entity by using the entity's supported owner class.
- L21 _public prototype_ `static UObject* FindMatch(const FFindBindingForEntityArgs& Args);`

#### struct `FNameBasedRebindingPolicy`  
`struct FNameBasedRebindingPolicy`  
_L31-34_
- desc: Name based policy, attempts to find an object with a similar name in the set of available objects. ie. If the old binding was bound to StaticMeshComponent0, the policy will try to bind it to an object with a name that starts with StaticMeshComponent. If no object is found this way, it uses the default rebinding policy.
- L33 _public prototype_ `static UObject* FindMatch(const FFindBindingForEntityArgs& Args);`

#### class `FRemoteControlPresetRebindingManager`  
`class FRemoteControlPresetRebindingManager`  
_L39-111_
- desc: Handles rebinding RC entities that are invalid in the current level.
- L51 _public prototype_ `FRemoteControlPresetRebindingManager() = default;`
- L53 _public function_ `FRemoteControlPresetRebindingManager(FRebindingOptions InRebindingOptions) : RebindingOptions(MoveTemp(InRebindingOptions))`
- L63 _public prototype_ `void Rebind(URemoteControlPreset* Preset);` — Attempt rebinding a Preset's entities by first trying to find objects with the same name in the current map, then by searching for objects that support the underlying entity. @Note: Set RemoteControl.UseLegacyRebinding to 1 in order to use the legacy algorthm.
- L69 _public prototype_ `TArray<FGuid> RebindAllEntitiesUnderSameActor(URemoteControlPreset* Preset, const TSharedPtr<FRemoteControlEntity>& Entity, AActor* NewActor, bool bUseRebindingContext);` — Given a RC Entity, rebind all entities with the same owner to a new actor @return the unique identifiers of the rc entities that were rebound.
- L72 _private prototype_ `void Rebind_Legacy(URemoteControlPreset* Preset);`
- L73 _private prototype_ `void Rebind_NewAlgo(URemoteControlPreset* Preset);`
- L76 _private prototype_ `TMap<UClass*, TArray<TSharedPtr<FRemoteControlEntity>>> GroupByEntitySupportedOwnerClass(TConstArrayView<TSharedPtr<FRemoteControlEntity>> Entities) const;` — Group RC Entities by the entity's supported owner class.
- L82 _private prototype_ `void ReinitializeBindings(URemoteControlPreset* Preset) const;` — Attempt to rebind the existing bindings by trying to find an object of the same name in the new level. Especially useful for a duplicated level.
- L85 _private prototype_ `void RebindEntitiesForClass_Legacy(UClass* Class, const TArray<TSharedPtr<FRemoteControlEntity>>& UnboundEntities);` — Attempt to rebind all unbound entities.
- L87 _private prototype_ `void RebindEntitiesForActorClass_Legacy(URemoteControlPreset* Preset, UClass* Class, const TArray<TSharedPtr<FRemoteControlEntity>>& UnboundEntities);`
- L89 _private prototype_ `TArray<FGuid> RebindAllEntitiesUnderSameActor(URemoteControlPreset* Preset, URemoteControlBinding* InitialBinding, AActor* NewActor);`
- L90 _private prototype_ `TArray<FGuid> RebindAllEntitiesUnderSameActor_Legacy(URemoteControlPreset* Preset, const TSharedPtr<FRemoteControlEntity>& Entity, AActor* NewActor);`
- L107 _private member_ `FRebindingOptions RebindingOptions;` — Options to customize the rebinding behaviour.
- L110 _private member_ `FRebindingContext Context;` — Holds the necessary information to rebind the preset's entities.

#### struct `FRemoteControlPresetRebindingManager::FRebindingOptions`  
`struct FRebindingOptions`  
_L42-49_
- L48 _public member_ `bool bUseBindingNameAsHint = false;` — Whether to use the entity's binding name as a hint for finding a new object to bind. It is a slower but more accurate method to rebind entities.

#### struct `FRemoteControlPresetRebindingManager::FRebindingContext`  
`struct FRebindingContext`  
_L92-102_
- L94 _public function_ `void Reset()`
- L100 _public member_ `TMap<UClass*, TArray<UObject*>> ObjectsGroupedByRelevantClass;`
- L101 _public member_ `TMap<UClass*, TMap<uint32, TSet<UObject*>>> BoundObjectsBySupportedOwnerClass;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlPropertyHandle.h` (Private)


#### class `FRemoteControlPropertyHandle`  
`class FRemoteControlPropertyHandle : public IRemoteControlPropertyHandle`  
_L12-148_
- inherits: `IRemoteControlPropertyHandle`
- desc: The base implementation of a property handle
- L24 _public prototype_ `static TSharedPtr<IRemoteControlPropertyHandle> GetPropertyHandle(const TSharedPtr<FRemoteControlProperty>& InRCProperty, FProperty* InProperty, FProperty* InParentProperty = nullptr, const FString& InParentFieldPath = FString(), int32 InArrayIndex = 0);` — Gets a property handle for the specified property type @param InRCProperty		Remote control property. @param InProperty		Property being edited. @param InParentProperty	Parent property being edited. @param InParentFieldPath	Parent path from UObject to Field @param InArrayIndex		Array index of the property
- L27 _public prototype_ `FRemoteControlPropertyHandle(const TSharedPtr<FRemoteControlProperty>& InRCProperty, FProperty* InProperty, FProperty* InParentProperty = nullptr, const FString& InParentFieldPath = FString(), int32 InArrayIndex = 0);`
- L35 _public prototype_ `bool IsPropertyTypeOf(FFieldClass* ClassType) const;` — Returns whether or not a property is of a specific subclass of FProperty @param ClassType	The class type to check @param true if the property is a ClassType
- L43 _public prototype_ `void* GetValuePtr(void* InContainerAddress) const;` — Gets the value pointer with the appropriate type for the property set @param InContainerAddress value container address @return The location of the property value
- L51 _public prototype_ `void* GetContainerAddress(int32 OwnerIndex = 0) const;` — Gets the Container address for the property @param OwnerIndex index of the Owning object, default 0 @return The container pointer
- L56 _public prototype_ `TArray<void*> GetContainerAddresses() const;` — Gets properties container pointer array.
- L65 _public function_ `DECLARE_PROPERTY_ACCESSOR_STR(FText) DECLARE_PROPERTY_ACCESSOR_STR(FName) #undef DECLARE_PROPERTY_ACCESSOR_STR #define DECLARE_PROPERTY_ACCESSOR( ValueType ) \ virtual bool SetValue( ValueType InValue) override;`
- L97 _public function_ `virtual bool SetValue(UObject* InValue) override`
- L98 _public function_ `virtual bool SetValueInArray(UObject* InValue, int32 InIndex) override`
- L99 _public function_ `virtual bool GetValue(UObject*& OutValue) const override`
- L100 _public function_ `virtual bool GetValueInArray(UObject*& OutValue, int32 InIndex) const override`
- L102 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetChildHandle(FName ChildName, bool bRecurse = true) const override;`
- L103 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetChildHandle(int32 Index) const override;`
- L104 _public function_ `virtual int32 GetNumChildren() const override`
- L105 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetChildHandleByFieldPath(const FString& InFieldPath) override;`
- L107 _public function_ `virtual TSharedPtr<IRemoteControlPropertyHandleArray> AsArray() override`
- L108 _public function_ `virtual TSharedPtr<IRemoteControlPropertyHandleSet> AsSet() override`
- L109 _public function_ `virtual TSharedPtr<IRemoteControlPropertyHandleMap> AsMap() override`
- L111 _public prototype_ `virtual TSharedPtr<FRemoteControlProperty> GetRCProperty() const override;`
- L112 _public function_ `virtual int32 GetIndexInArray() const override`
- L114 _public function_ `virtual FProperty* GetProperty() const override`
- L115 _public function_ `virtual FProperty* GetParentProperty() const override`
- L116 _public function_ `virtual const FString& GetFieldPath() const override`
- L117 _public function_ `virtual const FString& GetParentFieldPath() const override`
- L119 _public function_ `virtual bool ShouldGenerateTransaction() const`
- L120 _public function_ `virtual void SetGenerateTransaction(bool bInGenerateTransaction)`
- L125 _protected member_ `TWeakPtr<FRemoteControlProperty> RCPropertyPtr;` — Represents a property exposed to remote control.
- L128 _protected member_ `const TWeakFieldPtr<FProperty> PropertyPtr;` — The property being edited
- L131 _protected member_ `const TWeakFieldPtr<FProperty> ParentPropertyPtr;` — The parent property being edited
- L134 _protected member_ `FString ParentFieldPath;` — The path from a UObject to a parent field
- L137 _protected member_ `int32 ArrayIndex;` — Array index of the property, in case of the static C Array
- L140 _protected member_ `FString FieldPath;` — The path from a UObject to a field
- L143 _protected member_ `bool bGenerateTransaction;` — Should the property handle generate transactions.
- L147 _protected member_ `TArray<TSharedPtr<IRemoteControlPropertyHandle>> Children;` — All struct children

#### class `FRemoteControlPropertyHandleInt`  
`class FRemoteControlPropertyHandleInt : public FRemoteControlPropertyHandle`  
_L156-190_
- inherits: `FRemoteControlPropertyHandle`
- desc: The integer implementation of a property handle
- L159 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleInt) static bool Supports(const FProperty* InProperty);`
- L169 _public prototype_ `virtual bool GetValue(int8& OutValue) const override;`
- L170 _public prototype_ `virtual bool SetValue(int8 InValue) override;`
- L172 _public prototype_ `virtual bool GetValue(int16& OutValue) const override;`
- L173 _public prototype_ `virtual bool SetValue(int16 InValue) override;`
- L175 _public prototype_ `virtual bool GetValue(int32& OutValue) const override;`
- L176 _public prototype_ `virtual bool SetValue(int32 InValue) override;`
- L178 _public prototype_ `virtual bool GetValue(int64& OutValues) const override;`
- L179 _public prototype_ `virtual bool SetValue(int64 InValue) override;`
- L181 _public prototype_ `virtual bool GetValue(uint16& OutValues) const override;`
- L182 _public prototype_ `virtual bool SetValue(uint16 InValue) override;`
- L184 _public prototype_ `virtual bool GetValue(uint32& OutValue) const override;`
- L185 _public prototype_ `virtual bool SetValue(uint32 InValue) override;`
- L187 _public prototype_ `virtual bool GetValue(uint64& OutValue) const override;`
- L188 _public prototype_ `virtual bool SetValue(uint64 InValue) override;`

#### class `FRemoteControlPropertyHandleFloat`  
`class FRemoteControlPropertyHandleFloat : public FRemoteControlPropertyHandle`  
_L195-211_
- inherits: `FRemoteControlPropertyHandle`
- desc: The float implementation of a property handle
- L198 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleFloat) static bool Supports(const FProperty* InProperty);`
- L208 _public prototype_ `virtual bool GetValue(float& OutValue) const override;`
- L209 _public prototype_ `virtual bool SetValue(float InValue) override;`

#### class `FRemoteControlPropertyHandleDouble`  
`class FRemoteControlPropertyHandleDouble : public FRemoteControlPropertyHandle`  
_L216-232_
- inherits: `FRemoteControlPropertyHandle`
- desc: The double implementation of a property handle
- L219 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleDouble) static bool Supports(const FProperty* InProperty);`
- L229 _public prototype_ `virtual bool GetValue(double& OutValue) const override;`
- L230 _public prototype_ `virtual bool SetValue(double InValue) override;`

#### class `FRemoteControlPropertyHandleBool`  
`class FRemoteControlPropertyHandleBool : public FRemoteControlPropertyHandle`  
_L237-253_
- inherits: `FRemoteControlPropertyHandle`
- desc: The bool implementation of a property handle
- L240 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleBool) static bool Supports(const FProperty* InProperty);`
- L250 _public prototype_ `virtual bool GetValue(bool& OutValue) const override;`
- L251 _public prototype_ `virtual bool SetValue(bool InValue) override;`

#### class `FRemoteControlPropertyHandleByte`  
`class FRemoteControlPropertyHandleByte : public FRemoteControlPropertyHandle`  
_L258-274_
- inherits: `FRemoteControlPropertyHandle`
- desc: The byte implementation of a property handle
- L261 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleByte) static bool Supports(const FProperty* InProperty);`
- L271 _public prototype_ `virtual bool GetValue(uint8& OutValue) const override;`
- L272 _public prototype_ `virtual bool SetValue(uint8 InValue) override;`

#### class `FRemoteControlPropertyHandleString`  
`class FRemoteControlPropertyHandleString : public FRemoteControlPropertyHandle`  
_L279-299_
- inherits: `FRemoteControlPropertyHandle`
- desc: The string implementation of a property handle
- L282 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleString) static bool Supports(const FProperty* InProperty);`
- L292 _public prototype_ `virtual bool GetValue(FString& OutValue) const override;`
- L293 _public prototype_ `virtual bool SetValue(const FString& InValue) override;`
- L294 _public prototype_ `virtual bool SetValue(const TCHAR* InValue) override;`
- L296 _public prototype_ `virtual bool GetValue(FName& OutValue) const override;`
- L297 _public prototype_ `virtual bool SetValue(const FName& InValue) override;`

#### class `FRemoteControlPropertyHandleName`  
`class FRemoteControlPropertyHandleName : public FRemoteControlPropertyHandle`  
_L304-324_
- inherits: `FRemoteControlPropertyHandle`
- desc: The name implementation of a property handle
- L307 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleName) static bool Supports(const FProperty* InProperty);`
- L317 _public prototype_ `virtual bool GetValue(FString& OutValue) const override;`
- L318 _public prototype_ `virtual bool SetValue(const FString& InValue) override;`
- L319 _public prototype_ `virtual bool SetValue(const TCHAR* InValue) override;`
- L321 _public prototype_ `virtual bool GetValue(FName& OutValue) const override;`
- L322 _public prototype_ `virtual bool SetValue(const FName& InValue) override;`

#### class `FRemoteControlPropertyHandleText`  
`class FRemoteControlPropertyHandleText : public FRemoteControlPropertyHandle`  
_L329-348_
- inherits: `FRemoteControlPropertyHandle`
- desc: The text implementation of a property handle
- L332 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleText) static bool Supports(const FProperty* InProperty);`
- L342 _public prototype_ `virtual bool GetValue(FText& OutValue) const override;`
- L343 _public prototype_ `virtual bool SetValue(const FText& InValue) override;`
- L345 _public prototype_ `virtual bool SetValue(const FString& InValue) override;`
- L346 _public prototype_ `virtual bool SetValue(const TCHAR* InValue) override;`

#### class `FRemoteControlPropertyHandleVector`  
`class FRemoteControlPropertyHandleVector : public FRemoteControlPropertyHandle`  
_L353-397_
- inherits: `FRemoteControlPropertyHandle`
- desc: The vector implementation of a property handle
- L356 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleVector) static bool Supports(const FProperty* InProperty);`
- L366 _public prototype_ `virtual bool GetValue(FVector& OutValue) const override;`
- L367 _public prototype_ `virtual bool SetValue(FVector InValue) override;`
- L369 _public prototype_ `virtual bool GetValue(FVector2D& OutValue) const override;`
- L370 _public prototype_ `virtual bool SetValue(FVector2D InValue) override;`
- L372 _public prototype_ `virtual bool GetValue(FVector4& OutValue) const override;`
- L373 _public prototype_ `virtual bool SetValue(FVector4 InValue) override;`
- L375 _public prototype_ `virtual bool GetValue(FQuat& OutValue) const override;`
- L376 _public prototype_ `virtual bool SetValue(FQuat InValue) override;`
- L380 _public prototype_ `bool SetX(float InValue);` — Set X value of the vector
- L383 _public prototype_ `bool SetY(float InValue);` — Set Y value of the vector
- L386 _public prototype_ `bool SetZ(float InValue);` — Set Z value of the vector
- L389 _public prototype_ `bool SetW(float InValue);` — Set W value of the vector
- L392 _public prototype_ `bool AreComponentsValid() const;` — Check if all vector components are valid
- L396 _private member_ `TArray< TWeakPtr<IRemoteControlPropertyHandle> > VectorComponents;` — Array of child struct vector components

#### class `FRemoteControlPropertyHandleRotator`  
`class FRemoteControlPropertyHandleRotator : public FRemoteControlPropertyHandle`  
_L402-440_
- inherits: `FRemoteControlPropertyHandle`
- desc: The rotator implementation of a property handle
- L405 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleRotator) static bool Supports(const FProperty* InProperty);`
- L415 _public prototype_ `virtual bool GetValue(FRotator& OutValue) const override;`
- L416 _public prototype_ `virtual bool SetValue(FRotator InValue) override;`
- L420 _public prototype_ `bool SetRoll(float InValue);` — Set roll value of the rotator
- L423 _public prototype_ `bool SetPitch(float InValue);` — Set pitch value of the rotator
- L426 _public prototype_ `bool SetYaw(float InValue);` — Set yaw value of the rotator
- L429 _public prototype_ `bool AreComponentsValid() const;` — Check if all rotator components are valid
- L433 _private member_ `TWeakPtr<IRemoteControlPropertyHandle> RollValue;` — Roll handle of the rotator
- L436 _private member_ `TWeakPtr<IRemoteControlPropertyHandle> PitchValue;` — Roll handle of the rotator
- L439 _private member_ `TWeakPtr<IRemoteControlPropertyHandle> YawValue;` — Roll handle of the rotator

#### class `FRemoteControlPropertyHandleArray`  
`class FRemoteControlPropertyHandleArray : public FRemoteControlPropertyHandle, public IRemoteControlPropertyHandleArray`  
_L445-466_
- inherits: `FRemoteControlPropertyHandle,IRemoteControlPropertyHandleArray`
- desc: The array implementation of a property handle
- L448 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleArray) static bool Supports(const FProperty* InProperty, int32 InArrayIndex = -1);`
- L459 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandleArray> AsArray() override;`
- L463 _public prototype_ `virtual int32 GetNumElements() const override;`
- L464 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetElement(int32 Index) override;`

#### class `FRemoteControlPropertyHandleSet`  
`class FRemoteControlPropertyHandleSet : public FRemoteControlPropertyHandle, public IRemoteControlPropertyHandleSet`  
_L471-491_
- inherits: `FRemoteControlPropertyHandle,IRemoteControlPropertyHandleSet`
- desc: The set implementation of a property handle
- L474 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleSet) static bool Supports(const FProperty* InProperty);`
- L484 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandleSet> AsSet() override;`
- L488 _public prototype_ `virtual int32 GetNumElements() override;`
- L489 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> FindElement(const void* ElementToFind) override;`

#### class `FRemoteControlPropertyHandleMap`  
`class FRemoteControlPropertyHandleMap : public FRemoteControlPropertyHandle, public IRemoteControlPropertyHandleMap`  
_L496-516_
- inherits: `FRemoteControlPropertyHandle,IRemoteControlPropertyHandleMap`
- desc: The map implementation of a property handle
- L499 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleMap) static bool Supports(const FProperty* InProperty);`
- L509 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandleMap> AsMap() override;`
- L513 _public prototype_ `virtual int32 GetNumElements() override;`
- L514 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> Find(const void* KeyPtr) override;`

#### class `FRemoteControlPropertyHandleColor`  
`class FRemoteControlPropertyHandleColor : public FRemoteControlPropertyHandle`  
_L521-556_
- inherits: `FRemoteControlPropertyHandle`
- desc: The color implementation of a property handle
- L524 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleColor) static bool Supports(const FProperty* InProperty);`
- L534 _public prototype_ `virtual bool GetValue(FColor& OutValue) const override;`
- L535 _public prototype_ `virtual bool SetValue(FColor InValue) override;`
- L539 _public prototype_ `bool SetR(uint8 InValue);` — Set R value of the color
- L542 _public prototype_ `bool SetG(uint8 InValue);` — Set G value of the color
- L545 _public prototype_ `bool SetB(uint8 InValue);` — Set B value of the color
- L548 _public prototype_ `bool SetA(uint8 InValue);` — Set A value of the color
- L551 _public prototype_ `bool AreComponentsValid() const;` — Check if all color components are valid
- L555 _private member_ `TArray< TWeakPtr<IRemoteControlPropertyHandle> > ColorComponents;` — Array of child struct color components

#### class `FRemoteControlPropertyHandleLinearColor`  
`class FRemoteControlPropertyHandleLinearColor : public FRemoteControlPropertyHandle`  
_L561-596_
- inherits: `FRemoteControlPropertyHandle`
- desc: The linear color implementation of a property handle
- L564 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleLinearColor) static bool Supports(const FProperty* InProperty);`
- L574 _public prototype_ `virtual bool GetValue(FLinearColor& OutValue) const override;`
- L575 _public prototype_ `virtual bool SetValue(FLinearColor InValue) override;`
- L579 _public prototype_ `bool SetR(float InValue);` — Set R value of the linear color
- L582 _public prototype_ `bool SetG(float InValue);` — Set G value of the linear color
- L585 _public prototype_ `bool SetB(float InValue);` — Set B value of the linear color
- L588 _public prototype_ `bool SetA(float InValue);` — Set A value of the linear color
- L591 _public prototype_ `bool AreComponentsValid() const;` — Check if all color components are valid
- L595 _private member_ `TArray< TWeakPtr<IRemoteControlPropertyHandle> > ColorComponents;` — Array of child struct color components

#### class `FRemoteControlPropertyHandleObject`  
`class FRemoteControlPropertyHandleObject : public FRemoteControlPropertyHandle`  
_L601-624_
- inherits: `FRemoteControlPropertyHandle`
- desc: The object implementation of a property handle
- L604 _public prototype_ `DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR(FRemoteControlPropertyHandleObject) static bool Supports(const FProperty* InProperty);`
- L614 _public prototype_ `virtual bool SetValue(UObject* InValue) override;`
- L615 _public prototype_ `virtual bool GetValue(UObject*& OutValue) const override;`
- L618 _public prototype_ `virtual bool SetValueInArray(UObject* InValue, int32 InIndex) override;` — This is currently used for the specific case in which we are setting a material inside the override materials of e.g. a Static Mesh
- L619 _public prototype_ `virtual bool GetValueInArray(UObject*& OutValue, int32 InIndex) const override;`
- L623 _public prototype_ `bool SetMaterialValue(UObject* InValue, int32 InIndex) const;` — Set a Material value using the handled Object

#### Free symbols / members of external scopes

- L60 _macro_ `#define DECLARE_PROPERTY_ACCESSOR_STR( ValueType ) \`
- L70 _macro_ `#define DECLARE_PROPERTY_ACCESSOR( ValueType ) \`
- L150 _macro_ `#define DECLARE_PROPERTY_ACCESSOR_CONSTRUCTOR( ClassName ) \`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlProtocolEntityInterpolator.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace RemoteControl` (scope `UE`)
- L8 _namespace_ `namespace ProtocolEntityInterpolator` (scope `UE::RemoteControl`)
- L10 _namespace_ `namespace Internal` (scope `UE::RemoteControl::ProtocolEntityInterpolator`)
- L19 _function_ `template <typename ValueType, typename PropertyType, typename RangeValueType> TArray<FRemoteControlProtocolEntity::TRangeMappingData<RangeValueType, ValueType>> ContainerPtrMapToValuePtrMap(PropertyType* InProperty, FProperty* Outer, TArray<FRemoteControlProtocolEntity::FRangeMappingData>& InRangeMappingBuffers, int32 InArrayIndex)` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal`) — Converts a map with the range buffer pointers to a map with value pointers. Range keys stay the same. For example, when we have an input map TArray<TPair<int32, uint8*>> where uint8* points to the float buffer (4 bytes). we need to convert it to value buffer where we convert uint8* to value pointer. In this case, is float*.
- L61 _function_ `template <class T, class U> static T Lerp(const T& A, const T& B, const U& Alpha)` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal`) — Wraps FMath::Lerp, allowing value specific specialization
- L68 _function_ `template <> bool Lerp(const bool& A, const bool& B, const float& Alpha)` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal`) — Specialization for bool, toggles at 0.5 Alpha instead of 1.0
- L75 _function_ `template <> FString Lerp(const FString& A, const FString& B, const float& Alpha)` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal`) — Specialization for FString, toggles at 0.5 Alpha instead of 1.0
- L82 _function_ `template <> FName Lerp(const FName& A, const FName& B, const float& Alpha)` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal`) — Specialization for FName, toggles at 0.5 Alpha instead of 1.0
- L89 _function_ `template <> FText Lerp(const FText& A, const FText& B, const float& Alpha)` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal`) — Specialization for FText, toggles at 0.5 Alpha instead of 1.0
- L96 _function_ `template <typename RangeValueType, typename ValueType, typename PropertyType> bool InterpolateValue(PropertyType* InProperty, FProperty* InOuter, TArray<FRemoteControlProtocolEntity::FRangeMappingData>& InRangeMappingBuffers, RangeValueType InProtocolValue, ValueType& OutResultValue, int32 InArrayIndex = 0)` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal`) — Interpolates the range of an entity, using the protocol value as alpha
- L102 _function_ `` (scope `UE::RemoteControl::ProtocolEntityInterpolator::Internal::InterpolateValue`)
- L158 _function_ `template <typename ValueType, typename PropertyType> bool InterpolateValue(FRemoteControlProtocolEntity* InEntity, PropertyType* InProperty, FProperty* InOuter, TArray<FRemoteControlProtocolEntity::FRangeMappingData>& InRangeMappingBuffers, double InProtocolValue, ValueType& OutResultValue, int32 InArrayIndex = 0)` (scope `UE::RemoteControl::ProtocolEntityInterpolator`) — Interpolates the range of an entity, using the protocol value as alpha

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlTransactionListenerHelper.h` (Private)


#### class `FRCTransactionListenerHelper`  
`template <typename ...CallbackTypeArgs> class FRCTransactionListenerHelper`  
_L12-34_
- desc: Helper class which create a Listener and Register to the Manager @tparam CallbackTypeArgs Callback Args type
- L14 _private prototype_ `FRCTransactionListenerHelper() = delete;`
- L25 _public function_ `FRCTransactionListenerHelper(ERCTransaction::Type InType, const FGuid& PresetGuid, TMulticastDelegate<void(CallbackTypeArgs...)>& InDelegateToBroadcast, CallbackTypeArgs... InOrderedArgs)` — Create and Register a Listener to the ListenerManager @param InType When the broadcast should be called (Undo or Redo), see ERCTransactionType @param PresetGuid Preset Guid to check whether or not is Transient @param InDelegateToBroadcast Multicast delegate to broadcast @param InOrderedArgs Ordered arguments that should be passed to the MulticastDelegate

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/RemoteControlTransactionListenerManager.h` (Private)


#### enum `ERCTransaction::Type`  
`enum Type`  
_L16-21_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `Undo`
- L20 _public enumerator_ `Redo`

#### class `FRCTransactionListenerManager`  
`template <typename... CallbackArgs> class FRCTransactionListenerManager`  
_L29-270_
- desc: Collection of FRCTransactionListener which holds them and executes their Callback on the respective UTransBuffer Callback. @tparam CallbackArgs Callback Args type
- L84 _public function_ `static void CreateListenerAndRegister(ERCTransaction::Type InType, TMulticastDelegate<void(CallbackArgs...)>& InDelegateToBroadcast, CallbackArgs&&... InOrderedArgs)` — Create a listener with the parameter passed and Register it into the Manager to be called during Undo/Redo callbacks
- L96 _private function_ `static FRCTransactionListenerManager<CallbackArgs...>& Get()` — Return the only Instance for CallbackType and CallbackArgs of this class. @return Singleton of the class.
- L110 _public function_ `~FRCTransactionListenerManager()` — UnSubscribe to TransactionBuffer callback
- L131 _private function_ `void Register(FRCTransactionListener<CallbackArgs...>& Listener)` — Add the Listener to the PendingListener. @param Listener Listener to add to the PendingListeners
- L139 _private function_ `FRCTransactionListenerManager()` — Private constructor used to bind to TransactionBuffer callback
- L159 _private function_ `void ExecuteAllListeners(TArray<FRCTransactionListener<CallbackArgs...>>& InListeners, ERCTransaction::Type InTransactionType)` — Execute all the Listeners that are binded to the current TransactionId and have the same TransactionType. @param InListeners Listener binded to the current TransactionId. @param InTransactionType Current Transaction type (Undo or Redo).
- L175 _private function_ `void OnUndo(const FTransactionContext& InTransactionContext, bool bSucceeded)` — Gets executed when an Undo is attempted. @param InTransactionContext Transaction information. @param bSucceeded True if the Undo succeeded otherwise false.
- L193 _private function_ `void OnRedo(const FTransactionContext& InTransactionContext, bool bSucceeded)` — Gets executed when a Redo is attempted. @param InTransactionContext Transaction information. @param bSucceeded True if the Redo succeeded otherwise false.
- L209 _private function_ `void OnUndoBufferChanged()` — Gets executed when the undo buffer change.
- L217 _private function_ `void DeleteUnusedCallbacks()` — Delete from the Listeners all the Callbacks which are not binded to any Transaction inside the TransactionBuffer by their TransactionID.
- L248 _private function_ `void OnTransactionChanged(const FTransactionContext& InTransactionContext, ETransactionStateEventType InTransactionState)` — Gets executed when a transaction state changes. @param InTransactionContext Transaction information. @param InTransactionState Current state of the Transaction, see ETransactionStateEventType to know all types.
- L267 _private member_ `static TUniquePtr<FRCTransactionListenerManager<CallbackArgs...>> Instance;`
- L268 _private member_ `TArray<FRCTransactionListener<CallbackArgs...>> PendingListeners;`
- L269 _private member_ `TMap<FGuid, TArray<FRCTransactionListener<CallbackArgs...>>> Listeners;`
- L273 _prototype_ `template <typename... CallbackArgs> TUniquePtr<FRCTransactionListenerManager<CallbackArgs...>> FRCTransactionListenerManager<CallbackArgs...>::Instance(nullptr);`

#### class `FRCTransactionListenerManager::FRCTransactionListener`  
`template <typename... ListenerCallbackArgs> class FRCTransactionListener`  
_L37-77_
- desc: Helper class that stores a callback and its Args to then call it later on during Transaction Undo/Redo. Assign the Callback and the Args (if needed) before calling RegisterToCollection. @tparam ListenerCallbackArgs Args types to pass to the callback
- L39 _private prototype_ `FRCTransactionListener() = delete;`
- L49 _public function_ `FRCTransactionListener(ERCTransaction::Type InType, TMulticastDelegate<void(ListenerCallbackArgs...)>& InDelegateToBroadcast, ListenerCallbackArgs&&... InArgs) : Type(InType)` — Actual listener which holds the broadcast to make at Undo or Redo @param InType When the broadcast should be called (Undo or Redo) @param InDelegateToBroadcast Multicast delegate to broadcast @param InArgs Ordered arguments that should be passed to the MulticastDelegate
- L61 _public function_ `const TMulticastDelegate<void()>& OnUndoRedo()` — Getter for the holder of the callback called during Undo or Redo @return The UndoRedo Multicast Delegate
- L70 _public member_ `ERCTransaction::Type Type;` — Type of the transaction
- L76 _private member_ `TMulticastDelegate<void()> OnUndoRedoDelegate;` — Holds the callback to be executed during Undo or Redo

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ERCTransaction`
- L52 _function_ `` (scope `FRCTransactionListenerManager::FRCTransactionListener::FRCTransactionListener`)
- L228 _function_ `` (scope `FRCTransactionListenerManager::DeleteUnusedCallbacks`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Private/Serialization/PropertyMapStructDeserializerBackendWrapper.h` (Private)


#### class `FPropertyMapStructDeserializerBackendWrapper`  
`class FPropertyMapStructDeserializerBackendWrapper : public IStructDeserializerBackend`  
_L11-47_
- inherits: `IStructDeserializerBackend`
- desc: Wraps an existing IStructDeserializerBackend and passes calls through to it, but tracks which properties were successfully read in the process of deserialization.
- L26 _public function_ `FPropertyMapStructDeserializerBackendWrapper(IStructDeserializerBackend& InnerBackend) : InnerBackend(InnerBackend)` — Creates and initializes a new instance. @param InnerBackend The deserializer to wrap. This will actually handle deserializing the struct.
- L32 _public function_ `virtual const FString& GetCurrentPropertyName() const override`
- L33 _public function_ `virtual FString GetDebugString() const override`
- L34 _public function_ `virtual const FString& GetLastErrorMessage() const override`
- L35 _public function_ `virtual bool GetNextToken(EStructDeserializerBackendTokens& OutToken) override`
- L36 _public function_ `virtual void SkipArray() override`
- L37 _public function_ `virtual void SkipStructure() override`
- L38 _public prototype_ `virtual bool ReadProperty(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex) override;`
- L41 _public function_ `const TArray<FReadPropertyData>& GetReadProperties() const` — Get the array of properties that have been read so far during deserialization.
- L45 _private member_ `IStructDeserializerBackend& InnerBackend;`
- L46 _private member_ `TArray<FReadPropertyData> ReadProperties;`

#### struct `FPropertyMapStructDeserializerBackendWrapper::FReadPropertyData`  
`struct FReadPropertyData`  
_L15-19_
- L17 _public member_ `FProperty* Property;`
- L18 _public member_ `void* Data;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/Factories/IRCDefaultValueFactory.h` (Public)


#### struct `FRCResetToDefaultArgs`  
`struct FRCResetToDefaultArgs`  
_L10-35_
- desc: Holds the arguments required by the Reset Factories.
- L13 _public member_ `FProperty* Property;` — Holds a reference to the actual property.
- L16 _public member_ `FString Path;` — Holds the property path of the actual property.
- L19 _public member_ `int32 ArrayIndex;` — Holds the index of the property being modified incase it is embeded in an array.
- L22 _public member_ `bool bCreateTransaction;` — Determines whether should we notify the transaction manager or not.
- L26 _public function_ `FRCResetToDefaultArgs() : Property(nullptr) , Path(TEXT("")) , ArrayIndex(0) , bCreateTransaction(false)`
- L33 _public prototype_ `FRCResetToDefaultArgs(const FRCResetToDefaultArgs&);`
- L34 _public prototype_ `FRCResetToDefaultArgs& operator=(const FRCResetToDefaultArgs&);`

#### class `IRCDefaultValueFactory`  
`class IRCDefaultValueFactory : public TSharedFromThis<IRCDefaultValueFactory>`  
_L40-74_
- inherits: `TSharedFromThis<IRCDefaultValueFactory>`
- desc: Factory which resets the FRemoteControlProperty to its default values.
- L45 _public function_ `virtual ~IRCDefaultValueFactory()` — Virtual destructor
- L52 _public prototype_ `virtual bool CanResetToDefaultValue(UObject* InObject, const FRCResetToDefaultArgs& InArgs) const = 0;` — Returns true when the given object can be reset to its default value, false otherwise. @param InObject Reference to the exposed object. @param InArgs Arguments to be passed.
- L59 _public prototype_ `virtual void ResetToDefaultValue(UObject* InObject, FRCResetToDefaultArgs& InArgs) = 0;` — Performs actual data reset on the given remote object. @param InObject Reference to the exposed object. @param InArgs Arguments to be passed.
- L66 _public prototype_ `virtual bool SupportsClass(const UClass* InObjectClass) const = 0;` — Whether the factory support exposed entity. @param InObjectClass Reference to the exposed object class. @return true if the exposed object is supported by given factory
- L73 _public prototype_ `virtual bool SupportsProperty(const FProperty* InProperty) const = 0;` — Whether the factory support property. @param InProperty Reference to the exposed property. @return true if the exposed property is supported by given factory

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/Factories/IRemoteControlMaskingFactory.h` (Public)


#### struct `FRCMaskingOperation`  
`struct FRCMaskingOperation`  
_L13-75_
- reflection: `UE_DEPRECATED(5.5, "FRCMaskingOperation is deprecated, masking is now applied where appropriate automatically.")`
- desc: Reference to a UObject or one of its properties for the purpose of masking.
- L15 _public function_ `FRCMaskingOperation() : ModifyOperationFlags(ERCModifyOperationFlags::None)`
- L19 _public function_ `explicit FRCMaskingOperation(FRCFieldPathInfo InPathInfo, UObject* InObject, const ERCModifyOperationFlags InModifyOperationFlag = ERCModifyOperationFlags::None) : OperationId(FGuid::NewGuid()) , ObjectRef(ERCAccess::NO_ACCESS, InObject, InPathInfo) , ModifyOperationFlags(InModifyOperationFlag)`
- L27 _public function_ `explicit FRCMaskingOperation(const FRCObjectReference& InObjectRef, const ERCModifyOperationFlags InModifyOperationFlag = ERCModifyOperationFlags::None) : OperationId(FGuid::NewGuid()) , ObjectRef(InObjectRef) , ModifyOperationFlags(InModifyOperationFlag)`
- L34 _public function_ `bool HasMask(ERCMask InMaskBit) const`
- L39 _public function_ `bool IsValid() const`
- L56 _public member_ `FGuid OperationId;` — Unique identifier of the operation being performed.
- L59 _public member_ `ERCMask Masks = RC_AllMasks;` — Masks to be applied.
- L62 _public member_ `FRCObjectReference ObjectRef;` — Holds Object reference.
- L65 _public member_ `FVector4 PreMaskingCache = FVector4::Zero();` — Holds the state of this RC property before applying any masking.
- L68 _public member_ `const ERCModifyOperationFlags ModifyOperationFlags;` — Modify operation flags used when masking
- L72 _public prototype_ `FRCMaskingOperation(const FRCMaskingOperation&) = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L73 _public prototype_ `FRCMaskingOperation(FRCMaskingOperation&&) = default;`

#### class `IRemoteControlMaskingFactory`  
`class IRemoteControlMaskingFactory : public TSharedFromThis<IRemoteControlMaskingFactory>`  
_L81-115_
- reflection: `UE_DEPRECATED(5.5, "IRemoteControlMaskingFactory is deprecated, masking is now applied where appropriate automatically.")`
- inherits: `TSharedFromThis<IRemoteControlMaskingFactory>`
- desc: Factory which is responsible for masking support for FRemoteControlProperty.
- L86 _public function_ `virtual ~IRemoteControlMaskingFactory()` — Virtual destructor
- L95 _public function_ `virtual void ApplyMaskedValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation, bool bIsInteractive)` — Applies masked values to the given struct property. @param InMaskingOperation			Shared reference of the masking operation to perform. @param bIsInteractive				If bWithPropertyChangedEvents, defined if the property changed events are interactive or not. @param ModifyOperationFlags			(optional) Flags that specify how the property is modified when the value is applied.
- L101 _public prototype_ `virtual void CacheRawValues(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) = 0;` — Caches premasking values from the given struct property. @param InMaskingOperation Shared reference of the masking operation to perform.
- L108 _public prototype_ `virtual bool SupportsExposedEntity(UScriptStruct* ScriptStruct) const = 0;` — Whether the factory support exposed entity. @param ScriptStruct Static struct of exposed property. @return true if the script struct is supported by given factory
- L111 _public prototype_ `IRemoteControlMaskingFactory() = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L112 _public prototype_ `IRemoteControlMaskingFactory(const IRemoteControlMaskingFactory&) = default;`
- L113 _public prototype_ `IRemoteControlMaskingFactory(IRemoteControlMaskingFactory&&) = default;`

#### Free symbols / members of external scopes

- L44 _function_ `friend bool operator==(const FRCMaskingOperation& LHS, const FRCMaskingOperation& RHS)`
- L49 _function_ `friend uint32 GetTypeHash(const FRCMaskingOperation& MaskingOperation)`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/IPropertyIdHandler.h` (Public)


#### class `IPropertyIdHandler`  
`class IPropertyIdHandler`  
_L14-57_
- L17 _public prototype_ `virtual ~IPropertyIdHandler() = default;`
- L20 _public prototype_ `virtual bool IsPropertySupported(const FProperty* InProperty) const = 0;` — Whether this PropertyId Handler handles the given Property
- L23 _public prototype_ `virtual EPropertyBagPropertyType GetPropertyType(const FProperty* InProperty) const = 0;` — Get the PropertyBag type of the given property
- L29 _public prototype_ `virtual FName GetPropertySuperTypeName(const FProperty* InProperty) const = 0;` — Get the Property super type FName\n ex: Object/Struct/Enum or the primitive type if it is a primitive property (float/bool/etc...)
- L35 _public prototype_ `virtual FName GetPropertySubTypeName(const FProperty* InProperty) const = 0;` — Get the Property sub type FName\n ex: StaticMesh/Material or the primitive type if it is a primitive property (float/bool/etc...)
- L38 _public prototype_ `virtual UObject* GetPropertyTypeObject(const FProperty* InProperty) const = 0;` — Get the Property type Object
- L41 _public function_ `const FProperty* GetPropertyInsideContainer(const FProperty* InProperty) const` — Get the property inside the container if not inside any container return the property passed

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/IRemoteControlModule.h` (Public)


#### enum `ERCPayloadType`  
`enum class ERCPayloadType : uint8`  
_L46-50_
- desc: Deserialize payload type for interception purposes
- L48 _public enumerator_ `Cbor`
- L49 _public enumerator_ `Json`

#### struct `FRCCallReference`  
`struct FRCCallReference`  
_L55-85_
- desc: Reference to a function in a UObject
- L57 _public function_ `FRCCallReference() : Object(nullptr) , Function(nullptr) , PropertyWithSetter(nullptr)`
- L63 _public function_ `bool IsValid() const`
- L69 _public member_ `TWeakObjectPtr<UObject> Object;`
- L70 _public member_ `TWeakObjectPtr<UFunction> Function;`
- L71 _public member_ `TWeakFieldPtr<FProperty> PropertyWithSetter;`

#### enum `ERCTransactionMode`  
`enum class ERCTransactionMode : uint8`  
_L88-93_
- reflection: `UENUM()`
- L90 _public enumerator_ `NONE = 0`
- L91 _public enumerator_ `AUTOMATIC`
- L92 _public enumerator_ `MANUAL`

#### struct `FRCCall`  
`struct FRCCall`  
_L98-111_
- desc: Object to hold a UObject remote call
- L100 _public function_ `bool IsValid() const`
- L105 _public member_ `FRCCallReference CallRef;`
- L107 _public member_ `FStructOnScope ParamStruct;` — Payload for UFunctiom
- L109 _public member_ `TArray<uint8> ParamData;` — Payload for native function
- L110 _public member_ `ERCTransactionMode TransactionMode;`

#### struct `FResolvePresetFieldArgs`  
`struct FResolvePresetFieldArgs`  
_L116-120_
- desc: Object to hold information necessary to resolve a preset property/function.
- L118 _public member_ `FString PresetName;`
- L119 _public member_ `FString FieldLabel;`

#### struct `FResolvePresetControllerArgs`  
`struct FResolvePresetControllerArgs`  
_L125-129_
- desc: Arguments for resolving a Controller on a preset.
- L127 _public member_ `FString PresetName;`
- L128 _public member_ `FString ControllerName;`

#### enum `ERCAccess`  
`enum class ERCAccess : uint8`  
_L135-142_
- reflection: `UENUM()`
- desc: Requested access mode to a remote property
- L137 _public enumerator_ `NO_ACCESS`
- L138 _public enumerator_ `READ_ACCESS`
- L139 _public enumerator_ `WRITE_ACCESS`
- L140 _public enumerator_ `WRITE_TRANSACTION_ACCESS`
- L141 _public enumerator_ `WRITE_MANUAL_TRANSACTION_ACCESS`

#### enum `ERCModifyOperation`  
`enum class ERCModifyOperation : uint8`  
_L148-155_
- reflection: `UENUM()`
- desc: Type of operation to perform when setting a remote property's value
- L150 _public enumerator_ `EQUAL`
- L151 _public enumerator_ `ADD`
- L152 _public enumerator_ `SUBTRACT`
- L153 _public enumerator_ `MULTIPLY`
- L154 _public enumerator_ `DIVIDE`

#### enum `ERCWebSocketCompressionMode`  
`enum class ERCWebSocketCompressionMode : uint8`  
_L161-165_
- reflection: `UENUM()`
- desc: Type of compression applied to WebSocket traffic
- L163 _public enumerator_ `NONE`
- L164 _public enumerator_ `ZLIB`

#### struct `FRCObjectReference`  
`struct FRCObjectReference`  
_L170-231_
- desc: Reference to a UObject or one of its properties
- L173 _public typedef_ `using FPostSetObjectPropertyCallback = TFunction<bool(UObject* , const FRCFieldPathInfo& , bool )>;` — Callback type for post set object properties
- L175 _public prototype_ `FRCObjectReference() = default;`
- L177 _public function_ `FRCObjectReference(ERCAccess InAccessType, UObject* InObject) : Access(InAccessType) , Object(InObject)`
- L186 _public function_ `FRCObjectReference(ERCAccess InAccessType, UObject* InObject, FRCFieldPathInfo InPathInfo) : Access(InAccessType) , Object(InObject) , PropertyPathInfo(MoveTemp(InPathInfo))`
- L199 _public function_ `bool IsValid() const`
- L215 _public member_ `ERCAccess Access = ERCAccess::NO_ACCESS;` — Type of access on this object (read, write)
- L218 _public member_ `TWeakObjectPtr<UObject> Object;` — UObject owning the target property
- L221 _public member_ `TWeakFieldPtr<FProperty> Property;` — Actual property that is being referenced
- L224 _public member_ `void* ContainerAdress = nullptr;` — Address of the container of the property for serialization purposes in case of a nested property
- L227 _public member_ `TWeakObjectPtr<UStruct> ContainerType;` — Type of the container where the property resides
- L230 _public member_ `FRCFieldPathInfo PropertyPathInfo;` — Path to the property under the Object

#### class `IRemoteControlModule`  
`class IRemoteControlModule : public IModuleInterface`  
_L236-640_
- inherits: `IModuleInterface`
- desc: Interface for the remote control module.
- L245 _public function_ `static IRemoteControlModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L252 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetRegistered, FName );` — Delegate triggered when a preset has been registered
- L254 _public prototype_ `virtual FOnPresetRegistered& OnPresetRegistered() = 0;` — `UE_DEPRECATED(4.27, "OnPresetUnregistered is deprecated.")`
- L257 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetUnregistered, FName );` — Delegate triggered when a preset has been unregistered
- L259 _public prototype_ `virtual FOnPresetUnregistered& OnPresetUnregistered() = 0;` — `UE_DEPRECATED(4.27, "OnPresetUnregistered is deprecated.")`
- L262 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnError, const FString& , ELogVerbosity::Type );` — Delegate triggered when an error occurs, which aren't necessarily written to UE LOG
- L263 _public prototype_ `virtual FOnError& OnError() = 0;`
- L266 _public function_ `static void BroadcastError(const FString& Message, ELogVerbosity::Type Verbosity = ELogVerbosity::Error)` — Broadcast an error to the OnError delegate
- L276 _public prototype_ `virtual bool RegisterPreset(FName Name, URemoteControlPreset* Preset) = 0;` — `UE_DEPRECATED(4.27, "RegisterPreset is deprecated.")` — Register the preset with the module, enabling using the preset remotely using its name. @return whether registration was successful.
- L280 _public prototype_ `virtual void UnregisterPreset(FName Name) = 0;` — `UE_DEPRECATED(4.27, "UnregisterPreset is deprecated.")` — Unregister a preset
- L287 _public prototype_ `virtual bool RegisterEmbeddedPreset(URemoteControlPreset* Preset, bool bReplaceExisting = false) = 0;` — Registers a hosted (non-asset based) preset with an attached name. Embedded presets should only be registered while they are active. @return whether registration was successful.
- L292 _public prototype_ `virtual void UnregisterEmbeddedPreset(FName Name) = 0;` — Unregisters a hosted (non-asset based) preset with the given name.
- L293 _public prototype_ `virtual void UnregisterEmbeddedPreset(URemoteControlPreset* Preset) = 0;`
- L300 _public prototype_ `virtual bool CanResetToDefaultValue(UObject* InObject, const FRCResetToDefaultArgs& InArgs) const = 0;` — Returns true when the given object can be reset to its default value, false otherwise. @param InObject Reference to the exposed object. @param InArgs Arguments to be passed.
- L307 _public prototype_ `virtual bool HasDefaultValueCustomization(const UObject* InObject, const FProperty* InProperty) const = 0;` — Returns true when the given object and property has custom default value, false otherwise. @param InObject Reference to the exposed object. @param InProperty Reference to the exposed property.
- L314 _public prototype_ `virtual void ResetToDefaultValue(UObject* InObject, FRCResetToDefaultArgs& InArgs) = 0;` — Performs actual data reset on the given object. @param InObject Reference to the exposed object. @param InArgs Arguments to be passed.
- L322 _public prototype_ `virtual void PerformMasking(const TSharedRef<FRCMaskingOperation>& InMaskingOperation) = 0;` — `UE_DEPRECATED(5.5, "PerformMasking is deprecated, masking is now applied where appropriate automatically.")` — Performs the given masking operation. @param InMaskingOperation	Masking operation to be performed. @param ModifyOperationFlags	(optional) Flags that specify how the property is modified when the value is applied.
- L328 _public prototype_ `virtual void RegisterMaskingFactoryForType(UScriptStruct* RemoteControlPropertyType, const TSharedPtr<IRemoteControlMaskingFactory>& InMaskingFactory) = 0;` — `UE_DEPRECATED(5.5, "RegisterMaskingFactoryForType is deprecated, masking is now applied where appropriate automatically.")` — Register a masking factory to handle that masks the supported properties.
- L334 _public prototype_ `virtual void UnregisterMaskingFactoryForType(UScriptStruct* RemoteControlPropertyType) = 0;` — `UE_DEPRECATED(5.5, "UnregisterMaskingFactoryForType is deprecated, masking is now applied where appropriate automatically.")` — Unregister a previously registered masking factory.
- L339 _public prototype_ `virtual bool SupportsMasking(const UScriptStruct* InStruct) const = 0;` — Returns true if the given property can be masked, false otherwise.
- L344 _public prototype_ `virtual bool SupportsMasking(const FProperty* InProperty) const = 0;` — Returns true if the given property can be masked, false otherwise.
- L357 _public prototype_ `virtual bool ResolveCall(const FString& ObjectPath, const FString& FunctionName, FRCCallReference& OutCallRef, FString* OutErrorText = nullptr) = 0;` — Resolve a RemoteCall Object and Function. This will look for object and function to resolve. It will only successfully resolve function that are blueprint callable. The blueprint function name can be used. @param ObjectPath	The object path to the UObject we want to resolve @param FunctionName	The function name of the function we want to resolve @param OutCallRef	The RemoteCallReference in which the object and function will be resolved into @param OutErrorText	Optional pointer to an error text in case of resolving error. @return true if the resolving was successful
- L368 _public prototype_ `virtual bool InvokeCall(FRCCall& InCall, ERCPayloadType InPayloadType = ERCPayloadType::Json, const TArray<uint8>& InInterceptPayload = TArray<uint8>()) = 0;` — Invoke a Remote Call This is a thin wrapper around UObject::ProcessEvent This expects that the caller has already validated the call as it will assert otherwise. @param InCall the remote call structure to call. @param InPayloadType the payload type archive. @param InInterceptPayload the payload reference archive for the interception. @return true if the call was allowed and done.
- L379 _public prototype_ `virtual bool ResolveObject(ERCAccess AccessType, const FString& ObjectPath, const FString& PropertyName, FRCObjectReference& OutObjectRef, FString* OutErrorText = nullptr) = 0;` — Resolve a remote object reference to a property @param AccessType the requested access to the object, (i.e. read or write) @param ObjectPath the object path to resolve @param PropertyName the property to resolve, if any (specifying no property will return back the whole object when getting/setting it) @param OutObjectRef the object reference to resolve into @param OutErrorText an optional error string pointer to write errors into. @return true if resolving the object and its property succeeded or just the object if no property was specified.
- L390 _public prototype_ `virtual bool ResolveObjectProperty(ERCAccess AccessType, UObject* Object, FRCFieldPathInfo PropertyPath, FRCObjectReference& OutObjectRef, FString* OutErrorText = nullptr) = 0;` — Resolve a remote object reference to a property @param AccessType the requested access to the object, (i.e. read or write) @param Object the object to resolve the property on @param PropertyPath the path to or the name of the property to resolve. Specifying an empty path will return back the whole object when getting/setting it) @param OutObjectRef the object reference to resolve into @param OutErrorText an optional error string pointer to write errors into. @return true if resolving the object and its property succeeded or just the object if no property was specified.
- L398 _public prototype_ `virtual bool GetObjectProperties(const FRCObjectReference& ObjectAccess, IStructSerializerBackend& Backend) = 0;` — Serialize the Object Reference into the specified backend. @param ObjectAccess the object reference to serialize, it should be a read access reference. @param Backend the struct serializer backend to use to serialize the object properties. @return true if the serialization succeeded
- L410 _public prototype_ `virtual bool SetObjectProperties(const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, ERCPayloadType InPayloadType = ERCPayloadType::Json, const TArray<uint8>& InInterceptPayload = TArray<uint8>(), ERCModifyOperation Operation = ERCModifyOperation::EQUAL, const ERCModifyOperationFlags ModifyOperationFlags = ERCModifyOperationFlags::None) = 0;` — Deserialize the Object Reference from the specified backend. @param ObjectAccess the object reference to deserialize into, it should be a write access reference. if the object is WRITE_TRANSACTION_ACCESS, the setting will be wrapped in a transaction. @param Backend the struct deserializer backend to use to deserialize the object properties. @param InPayloadType the payload type archive. @param InInterceptPayload the payload reference archive for the interception. @param Operation the type of operation to perform when setting the value. @param ModifyOperationFlags (optional) Flags that specify how the property is modified when the value is applied. @return true if the deserialization succeeded
- L418 _public prototype_ `virtual bool ResetObjectProperties(const FRCObjectReference& ObjectAccess, const bool bAllowIntercept = false) = 0;` — Reset the property or the object the Object Reference is pointing to @param ObjectAccess the object reference to reset, it should be a write access reference @param bAllowIntercept interception flag, if that is set to true it should follow the interception path @return true if the reset succeeded.
- L428 _public prototype_ `virtual bool AppendToObjectArrayProperty(const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, ERCPayloadType InPayloadType = ERCPayloadType::Json, const TArray<uint8>& InInterceptPayload = TArray<uint8>()) = 0;` — Deserialize the Object Reference from the specified backend and append it to an array property. @param ObjectAccess the object reference to deserialize into, it should be a write access reference. if the object is WRITE_TRANSACTION_ACCESS, the setting will be wrapped in a transaction. @param Backend the struct deserializer backend to use to deserialize the object properties. @param InPayloadType the payload type archive. @param InInterceptPayload the payload reference archive for the interception. @return true if the operation succeeded
- L439 _public prototype_ `virtual bool InsertToObjectArrayProperty(int32 Index, const FRCObjectReference& ObjectAccess, IStructDeserializerBackend& Backend, ERCPayloadType InPayloadType = ERCPayloadType::Json, const TArray<uint8>& InInterceptPayload = TArray<uint8>()) = 0;` — Deserialize the Object Reference from the specified backend and insert it at the given position in an array property. @param Index The index into the array to insert at. @param ObjectAccess the object reference to deserialize into, it should be a write access reference. if the object is WRITE_TRANSACTION_ACCESS, the setting will be wrapped in a transaction. @param Backend the struct deserializer backend to use to deserialize the object properties. @param InPayloadType the payload type archive. @param InInterceptPayload the payload reference archive for the interception. @return true if the operation succeeded
- L447 _public prototype_ `virtual bool RemoveFromObjectArrayProperty(int32 Index, const FRCObjectReference& ObjectAccess) = 0;` — Remove an item from the referenced array. @param Index The index into the array to remove. @param ObjectAccess The reference to the array. If the object is WRITE_TRANSACTION_ACCESS, the operation will be wrapped in a transaction. @return true if the operation succeeded
- L458 _public prototype_ `virtual bool SetPresetController(const FName PresetName, const FName ControllerName, IStructDeserializerBackend& Backend, const TArray<uint8>& InPayload, const bool bAllowIntercept) = 0;` — Set a controller's value on a Remote Control Preset @param PresetName - The Remote Control Preset asset's name @param ControllerName - The name of the controller being manipulated @param Backend - the struct deserializer backend to use to deserialize the object properties. @param InPayload - the JSON payoad @param bAllowIntercept - Whether the call needs to be replicated to interceptors or invoked directly @return true if the operation succeeded
- L469 _public prototype_ `virtual bool SetPresetController(const FName PresetName, class URCVirtualPropertyBase* Controller, IStructDeserializerBackend& Backend, const TArray<uint8>& InPayload, const bool bAllowIntercept) = 0;` — Set a controller's value on a Remote Control Preset @param PresetName - The Remote Control Preset asset's name @param Controller - The controller object being manipulated @param Backend - the struct deserializer backend to use to deserialize the object properties. @param InPayload - the JSON payoad @param bAllowIntercept - Whether the call needs to be replicated to interceptors or invoked directly @return true if the operation succeeded
- L477 _public prototype_ `virtual TOptional<struct FExposedFunction> ResolvePresetFunction(const FResolvePresetFieldArgs& Args) const = 0;` — `UE_DEPRECATED(4.27, "This function is deprecated, please resolve directly on the preset.")` — Resolve the underlying function from a preset. @return the underlying function and objects that the property is exposed on.
- L486 _public prototype_ `virtual TOptional<struct FExposedProperty> ResolvePresetProperty(const FResolvePresetFieldArgs& Args) const = 0;` — `UE_DEPRECATED(4.27, "This function is deprecated, please resolve directly on the preset.")` — Resolve the underlying property from a preset. @return the underlying property and objects that the property is exposed on.
- L494 _public prototype_ `virtual URemoteControlPreset* ResolvePreset(FName PresetName) const = 0;` — Get a preset using its name. @arg PresetName name of the preset to resolve. @return the preset if found.
- L501 _public prototype_ `virtual URemoteControlPreset* ResolvePreset(const FGuid& PresetId) const = 0;` — Get a preset using its id. @arg PresetId id of the preset to resolve. @return the preset if found.
- L508 _public prototype_ `virtual URemoteControlPreset* CreateTransientPreset() = 0;` — Create a transient preset. Make sure to call DestroyTransientPreset when done with the preset or it will stay in memory. @return the new preset, or nullptr if it couldn't be created.
- L515 _public prototype_ `virtual bool DestroyTransientPreset(FName PresetName) = 0;` — Destroy a transient preset using its name. @arg PresetName name of the preset to destroy. @return true if a transient preset with that name existed and was destroyed.
- L522 _public prototype_ `virtual bool DestroyTransientPreset(const FGuid& PresetId) = 0;` — Destroy a transient preset using its id. @arg PresetId id of the preset to destroy. @return true if a transient preset with that name existed and was destroyed.
- L529 _public prototype_ `virtual bool IsPresetTransient(FName PresetName) const = 0;` — Check whether a preset is transient using its name. @arg PresetName name of the preset to check. @return true if the preset exists and is transient.
- L536 _public prototype_ `virtual bool IsPresetTransient(const FGuid& PresetId) const = 0;` — Check whether a preset is transient using its id. @arg PresetId id of the preset to check. @return true if the preset exists and is transient.
- L541 _public prototype_ `virtual void GetPresets(TArray<TSoftObjectPtr<URemoteControlPreset>>& OutPresets) const = 0;` — Get all the presets currently registered with the module.
- L547 _public prototype_ `virtual void GetPresetAssets(TArray<FAssetData>& OutPresetAssets, bool bIncludeTransient = true) const = 0;` — Get all the preset asset currently registered with the module. @arg bIncludeTransient Whether to include transient presets.
- L552 _public prototype_ `virtual void GetEmbeddedPresets(TArray<TWeakObjectPtr<URemoteControlPreset>>& OutEmbeddedPresets) const = 0;` — Gets all hosted presets currently registered with the module.
- L557 _public prototype_ `virtual const TMap<FName, FEntityMetadataInitializer>& GetDefaultMetadataInitializers() const = 0;` — Get the map of registered default entity metadata initializers.
- L566 _public prototype_ `virtual bool RegisterDefaultEntityMetadata(FName MetadataKey, FEntityMetadataInitializer MetadataInitializer) = 0;` — Register a default entity metadata which will show up in an entity's detail panel. The initializer will be called upon an entity being exposed or when a preset is loaded in order to update all existing entities that don't have that metadata key. @param MetadataKey The desired metadata key. @param MetadataInitializer The delegate to call to handle initializing the metadata.
- L572 _public prototype_ `virtual void UnregisterDefaultEntityMetadata(FName MetadataKey) = 0;` — Unregister a default entity metadata. @param MetadataKey The metadata entry to unregister.
- L578 _public prototype_ `virtual bool PropertySupportsRawModificationWithoutEditor(FProperty* Property, UClass* OwnerClass = nullptr) const = 0;` — `UE_DEPRECATED(5.4, "This function is deprecated, please use PropertySupportsRawModification.")` — Returns whether the property can be modified through SetObjectProperties when running without an editor.
- L588 _public prototype_ `virtual bool PropertySupportsRawModification(FProperty* InProperty, const UObject* InObject, const bool bInWithEditor, FString* OutError = nullptr) const = 0;` — Returns whether the property can be modified through SetObjectProperties or read through ResolveObjectProperties when running with or without an editor. @param InProperty Property to check @param InObject Object that owns the property @param bInWithEditor True if it should check if the property is supported in Editor, false to check for Packaged @param OutError Will contain the error in case it is not supported @return True if the property is supported both for read and write, false otherwise
- L595 _public prototype_ `virtual void RegisterEntityFactory( const FName InFactoryName, const TSharedRef<IRemoteControlPropertyFactory>& InFactory) = 0;` — Register factory @param InFactoryName the factory unique name @param InFactory Factory instance
- L601 _public prototype_ `virtual void UnregisterEntityFactory( const FName InFactoryName ) = 0;` — Remove factory by name @param InFactoryName the factory unique name
- L609 _public prototype_ `virtual FGuid BeginManualEditorTransaction(const FText& InDescription, uint32 TypeHash) = 0;` — Start a manual editor transaction originating from a remote request. @param InDescription A description of the transaction. @param TypeHash The type hash of the object or call to which the transaction applies, or 0 if not applicable (e.g. multiple objects being modified). @return The ID of the new transaction if one was created, or an invalid ID otherwise.
- L616 _public prototype_ `virtual int32 EndManualEditorTransaction(const FGuid& TransactionId) = 0;` — End a manual editor transaction originating from a remote request. @param TransactionId The ID of the transaction. If this doesn't match the current active transaction, the transaction won't be ended. @return INDEX_NONE if there was no transaction to end; otherwise, the number of remaining actions in the transaction (i.e. 1 means this was the last action and the transaction will end).
- L619 _public prototype_ `virtual const TMap<FName, TSharedPtr<IRemoteControlPropertyFactory>>& GetEntityFactories() const = 0;` — Get map of the factories which is responsible for the Remote Control property creation
- L625 _public prototype_ `virtual bool CanBeAccessedRemotely(UObject* InObject) const = 0;` — @return whether an object can be accessed remotely. @note Check Remote Control project settings to configure.
- L629 _public function_ `TSharedRef<InPropertyIdPropertyHandlerType> RegisterPropertyIdPropertyHandler(InArgTypes&&... InArgs)`
- L636 _public prototype_ `virtual TSharedPtr<IPropertyIdHandler> GetPropertyIdHandlerFor(FProperty* InProperty) = 0;`
- L639 _protected prototype_ `virtual void RegisterPropertyIdPropertyHandlerImpl(const TSharedRef<IPropertyIdHandler>& InKeyPropertyHandler) = 0;`

#### Free symbols / members of external scopes

- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteControl, Log, All);`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FString , FEntityMetadataInitializer, URemoteControlPreset* , const FGuid& );` — Delegate called to initialize an exposed entity metadata entry registered with the RegisterDefaultEntityMetadata method. Use RemoteControlPreset::GetExposedEntity to retrieve the entity that will contain the metadata. The delegate return value will be put into metadata map for the metadata key that was used when registering the default metadata entry.
- L36 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FString , FEntityMetadataInitializer, URemoteControlPreset* , const FGuid& );` — Delegate called to initialize an exposed entity metadata entry registered with the RegisterDefaultEntityMetadata method. Use RemoteControlPreset::GetExposedEntity to retrieve the entity that will contain the metadata. The delegate return value will be put into metadata map for the metadata key that was used when registering the default metadata entry.
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostPropertyModifiedRemotely, const FRCObjectReference& );` — Delegate called after a property has been modified through SetObjectProperties..
- L41 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostPropertyModifiedRemotely, const FRCObjectReference& );` — Delegate called after a property has been modified through SetObjectProperties..
- L73 _function_ `friend uint32 GetTypeHash(const FRCCallReference& CallRef)`
- L204 _function_ `friend bool operator==(const FRCObjectReference& LHS, const FRCObjectReference& RHS)`
- L209 _function_ `friend uint32 GetTypeHash(const FRCObjectReference& ObjectReference)`
- L252 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetRegistered, FName );` — Delegate triggered when a preset has been registered
- L257 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetUnregistered, FName );` — Delegate triggered when a preset has been unregistered
- L262 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnError, const FString& , ELogVerbosity::Type );` — Delegate triggered when an error occurs, which aren't necessarily written to UE LOG

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/IRemoteControlPropertyHandle.h` (Public)


#### class `IRemoteControlPropertyHandle`  
`class IRemoteControlPropertyHandle : public TSharedFromThis<IRemoteControlPropertyHandle>`  
_L15-196_
- inherits: `TSharedFromThis<IRemoteControlPropertyHandle>`
- desc: A handle to a property which is used to read and write the value
- L28 _public prototype_ `static TSharedPtr<IRemoteControlPropertyHandle> GetPropertyHandle(FName PresetName, FGuid PropertyId);` — Get the property handle based on field path @param PresetName Preset Name @param PropertyId Unique property Id @param FieldPath full path to the property field. @note @return IRemoteControlPropertyHandle pointer or nullptr
- L38 _public prototype_ `static TSharedPtr<IRemoteControlPropertyHandle> GetPropertyHandle(FName PresetName, FName PropertyLabel);` — Get the property handle based on field path @param PresetName Preset Name @param PropertyLabel Exposed property label @param FieldPath full path to the property field @return IRemoteControlPropertyHandle pointer or nullptr
- L41 _public prototype_ `virtual ~IRemoteControlPropertyHandle() = default;`
- L51 _public prototype_ `virtual bool GetValue(float& OutValue) const = 0;` — Gets the typed value of a property. If the property does not support the value type false is returned @param OutValue	The value that will be set if successful @return true if the operation supported and value read successfully or false if that is not supported by property handle or it can't be read
- L52 _public prototype_ `virtual bool GetValue(double& OutValue) const = 0;`
- L53 _public prototype_ `virtual bool GetValue(bool& OutValue) const = 0;`
- L54 _public prototype_ `virtual bool GetValue(int8& OutValue) const = 0;`
- L55 _public prototype_ `virtual bool GetValue(int16& OutValue) const = 0;`
- L56 _public prototype_ `virtual bool GetValue(int32& OutValue) const = 0;`
- L57 _public prototype_ `virtual bool GetValue(int64& OutValue) const = 0;`
- L58 _public prototype_ `virtual bool GetValue(uint8& OutValue) const = 0;`
- L59 _public prototype_ `virtual bool GetValue(uint16& OutValue) const = 0;`
- L60 _public prototype_ `virtual bool GetValue(uint32& OutValue) const = 0;`
- L61 _public prototype_ `virtual bool GetValue(uint64& OutValue) const = 0;`
- L62 _public prototype_ `virtual bool GetValue(FString& OutValue) const = 0;`
- L63 _public prototype_ `virtual bool GetValue(FText& OutValue) const = 0;`
- L64 _public prototype_ `virtual bool GetValue(FName& OutValue) const = 0;`
- L65 _public prototype_ `virtual bool GetValue(FVector& OutValue) const = 0;`
- L66 _public prototype_ `virtual bool GetValue(FVector2D& OutValue) const = 0;`
- L67 _public prototype_ `virtual bool GetValue(FVector4& OutValue) const = 0;`
- L68 _public prototype_ `virtual bool GetValue(FQuat& OutValue) const = 0;`
- L69 _public prototype_ `virtual bool GetValue(FRotator& OutValue) const = 0;`
- L70 _public prototype_ `virtual bool GetValue(FColor& OutValue) const = 0;`
- L71 _public prototype_ `virtual bool GetValue(FLinearColor& OutValue) const = 0;`
- L72 _public prototype_ `virtual bool GetValue(UObject*& OutValue) const = 0;`
- L73 _public prototype_ `virtual bool GetValueInArray(UObject*& OutValue, int32 InIndex) const = 0;`
- L83 _public prototype_ `virtual bool SetValue(float InValue) = 0;` — Sets the typed value of a property. If the property does not support the value type false is returned @param InValue The value to set @return true if the operation supported and value set successfully or false if that is not supported by property handle or it can't be set
- L84 _public prototype_ `virtual bool SetValue(double InValue) = 0;`
- L85 _public prototype_ `virtual bool SetValue(bool InValue) = 0;`
- L86 _public prototype_ `virtual bool SetValue(int8 InValue) = 0;`
- L87 _public prototype_ `virtual bool SetValue(int16 InValue) = 0;`
- L88 _public prototype_ `virtual bool SetValue(int32 InValue) = 0;`
- L89 _public prototype_ `virtual bool SetValue(int64 InValue) = 0;`
- L90 _public prototype_ `virtual bool SetValue(uint8 InValue) = 0;`
- L91 _public prototype_ `virtual bool SetValue(uint16 InValue) = 0;`
- L92 _public prototype_ `virtual bool SetValue(uint32 InValue) = 0;`
- L93 _public prototype_ `virtual bool SetValue(uint64 InValue) = 0;`
- L94 _public prototype_ `virtual bool SetValue(const FString& InValue) = 0;`
- L95 _public prototype_ `virtual bool SetValue(const FText& InValue) = 0;`
- L96 _public prototype_ `virtual bool SetValue(const FName& InValue) = 0;`
- L97 _public prototype_ `virtual bool SetValue(FVector InValue) = 0;`
- L98 _public prototype_ `virtual bool SetValue(FVector2D InValue) = 0;`
- L99 _public prototype_ `virtual bool SetValue(FVector4 InValue) = 0;`
- L100 _public prototype_ `virtual bool SetValue(FQuat InValue) = 0;`
- L101 _public prototype_ `virtual bool SetValue(FRotator InValue) = 0;`
- L102 _public prototype_ `virtual bool SetValue(FColor InValue) = 0;`
- L103 _public prototype_ `virtual bool SetValue(FLinearColor InValue) = 0;`
- L104 _public prototype_ `virtual bool SetValue(const TCHAR* InValue) = 0;`
- L105 _public prototype_ `virtual bool SetValue(UObject* InValue) = 0;`
- L106 _public prototype_ `virtual bool SetValueInArray(UObject* InValue, int32 InIndex) = 0;`
- L116 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetChildHandle(FName ChildName, bool bRecurse = true) const = 0;` — Gets a child handle of this handle.  Useful for accessing properties in structs. Array elements cannot be accessed in this way @param ChildName The name of the child @param bRecurse	Whether or not to recurse into children of children and so on. If false will only search all immediate children @return The property handle for the child if it exists
- L124 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetChildHandle(int32 Index) const = 0;` — Gets a child handle of this handle.  Useful for accessing properties in structs. @param The index of the child @return The property handle for the child if it exists
- L129 _public prototype_ `virtual int32 GetNumChildren() const = 0;` — @return The number of children the property handle has
- L138 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetChildHandleByFieldPath(const FString& InFieldPath) = 0;` — Gets handle by full field path For example the property could be ArrayOfVectors and the ArrayOfVectors[0].Y path needed for access of Y property from index 0 @param InFieldPath the path from a UObject to a parent field @return The property handle if it exists by given path
- L145 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandleArray> AsArray() = 0;` — Returns this handle as an array if possible @return the handle as an array if it is an array (static or dynamic)
- L150 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandleSet> AsSet() = 0;` — @return This handle as a set if possible
- L155 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandleMap> AsMap() = 0;` — @return This handle as a map if possible
- L160 _public prototype_ `virtual TSharedPtr<FRemoteControlProperty> GetRCProperty() const = 0;` — @return the property exposed to remote control.
- L165 _public prototype_ `virtual int32 GetIndexInArray() const = 0;` — @return The index of this element in an array;
- L170 _public prototype_ `virtual FProperty* GetProperty() const = 0;` — Gets the property being edited
- L175 _public prototype_ `virtual FProperty* GetParentProperty() const = 0;` — Gets the parent property being edited
- L180 _public prototype_ `virtual const FString& GetFieldPath() const = 0;` — Gets the path from a UObject to a field
- L185 _public prototype_ `virtual const FString& GetParentFieldPath() const = 0;` — Gets the path from a UObject to a parent field
- L190 _public prototype_ `virtual bool ShouldGenerateTransaction() const = 0;` — Should the property handle generate transactions.
- L195 _public prototype_ `virtual void SetGenerateTransaction(bool bInGenerateTransaction) = 0;` — Set transaction generation for this property handle.

#### class `IRemoteControlPropertyHandleArray`  
`class IRemoteControlPropertyHandleArray`  
_L201-215_
- desc: A handle to an array property which allows you to manipulate the array
- L204 _public prototype_ `virtual ~IRemoteControlPropertyHandleArray() = default;`
- L209 _public prototype_ `virtual int32 GetNumElements() const = 0;` — @return The number of elements in the array
- L214 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> GetElement(int32 Index) = 0;` — @return a handle to the element at the specified index

#### class `IRemoteControlPropertyHandleSet`  
`class IRemoteControlPropertyHandleSet`  
_L220-234_
- desc: A handle to a property which allows you to manipulate a Set
- L223 _public prototype_ `virtual ~IRemoteControlPropertyHandleSet() = default;`
- L228 _public prototype_ `virtual int32 GetNumElements() = 0;` — @return The number of elements in the set
- L233 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> FindElement(const void* ElementToFind) = 0;` — @return a handle to the element at the specified set value pointer

#### class `IRemoteControlPropertyHandleMap`  
`class IRemoteControlPropertyHandleMap`  
_L239-253_
- desc: A handle to a property which allows you to manipulate a Map
- L242 _public prototype_ `virtual ~IRemoteControlPropertyHandleMap() = default;`
- L247 _public prototype_ `virtual int32 GetNumElements() = 0;` — @return The number of elements in the map
- L252 _public prototype_ `virtual TSharedPtr<IRemoteControlPropertyHandle> Find(const void* KeyPtr) = 0;` — @return a handle to the element at the specified key value pointer

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RCModifyOperationFlags.h` (Public)


#### enum `ERCModifyOperationFlags`  
`enum class ERCModifyOperationFlags : uint8`  
_L11-21_
- reflection: `UENUM()`
- L14 _public enumerator_ `None = 0x00` — Properties are modified with Transactions and Property Changed events
- L17 _public enumerator_ `SkipPropertyChangeEvents = 0x01` — Properties are modified without Property Change events and implicitly without transactions
- L20 _public enumerator_ `SkipTransactions = 0x02` — Properties are modified without Transactions

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RCSignature.h` (Public)


#### struct `FRCSignatureField`  
`struct FRCSignatureField`  
_L15-55_
- reflection: `USTRUCT()`
- desc: Representation class of a Field (e.g. Property) in an Object
- L19 _public prototype_ `FRCSignatureField() = default;`
- L21 _public prototype_ `static FRCSignatureField CreateField(const FRCFieldPathInfo& InFieldPathInfo, const UObject* InOwnerObject, const FProperty* InProperty);`
- L23 _public prototype_ `void PostLoad();`
- L25 _public function_ `bool operator==(const FRCSignatureField& InOtherField) const`
- L34 _public member_ `FRCFieldPathInfo FieldPath;` — `UPROPERTY()` — Path Info for this Field
- L38 _public member_ `FString ObjectRelativePath;` — `UPROPERTY()` — Optional: Relative path from an owner (e.g. Actor) to the object owning the property (e.g. an Actor Component)
- L42 _public member_ `FSoftClassPath SupportedClass;` — `UPROPERTY()` — Object class holding the property
- L46 _public member_ `FPropertyBagPropertyDesc PropertyDesc;` — `UPROPERTY()` — Optional: Property Description of the field (if property)
- L50 _public member_ `TArray<FRCSignatureActionInstance> Actions;` — `UPROPERTY()` — Container holding the action instances for the field
- L54 _public member_ `bool bEnabled = true;` — `UPROPERTY()` — Whether to consider this field when applying a Signature

#### struct `FRCSignature`  
`struct FRCSignature`  
_L58-98_
- reflection: `USTRUCT()`
- L62 _public function_ `bool operator==(const FGuid& InSignatureId) const`
- L67 _public prototype_ `void PostLoad();`
- L73 _public prototype_ `int32 AddFields(TConstArrayView<FRCSignatureField> InFields);` — Adds the given fields to this signature and ensuring no repeated field is present @return the number of new fields added
- L81 _public prototype_ `int32 ApplySignature(URemoteControlPreset* InPreset, TConstArrayView<TWeakObjectPtr<UObject>> InObjects) const;` — Applies this Signature to the given Objects by exposing all this Signature's fields to the given preset @param InPreset the preset where these properties will be exposed to @param InObjects the objects whose properties or properties of its subojects to expose @return the number of properties affected in total
- L85 _public member_ `FText DisplayName;` — `UPROPERTY()` — User facing friendly name. Used as the Label when exposing
- L89 _public member_ `FGuid Id;` — `UPROPERTY(meta=(IgnoreForMemberInitializationTest))` — Unique Id identifying this Signature
- L93 _public member_ `TArray<FRCSignatureField> Fields;` — `UPROPERTY()` — The fields owned by this Signature
- L97 _public member_ `bool bEnabled = true;` — `UPROPERTY()` — Whether this Signature can be applied

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RCSignatureAction.h` (Public)


#### struct `FRCSignatureActionContext`  
`struct FRCSignatureActionContext`  
_L20-30_
- desc: The context for a Signature Action to execute
- L23 _public member_ `TObjectPtr<URemoteControlPreset> Preset = nullptr;` — The preset where the Signature is being applied
- L26 _public member_ `TObjectPtr<UObject> Object = nullptr;` — The object that the Signature is applying
- L29 _public member_ `TSharedPtr<FRemoteControlProperty> Property;` — The exposed property from the Signature

#### struct `FRCSignatureActionIcon`  
`struct FRCSignatureActionIcon`  
_L37-53_
- desc: Editor information on the Icon of a given Action Names are explicitly used over FSlateIcon to avoid a dependency on Slate Core API
- L40 _public member_ `FName StyleSetName;` — Name of the style set the icon can be found in
- L43 _public member_ `FName StyleName;` — Name of the style for the icon
- L46 _public member_ `FName OverlayStyleName;` — Name of the style for the overlay icon (if any)
- L49 _public member_ `FLinearColor BaseColor = FLinearColor::White;` — Color of the Base Icon
- L52 _public member_ `TOptional<FLinearColor> OverlayColor;` — Optional Color of the Overlay Icon (if any). Uses the Icon Color if not set

#### struct `FRCSignatureAction`  
`struct FRCSignatureAction`  
_L58-104_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: Base class of Actions that execute when Applying a Signature Field
- L62 _public prototype_ `virtual ~FRCSignatureAction() = default;`
- L68 _public function_ `virtual void Initialize(const FRCSignatureField& InField)` — Called when the Signature Action is first added to the action list or loaded @param InField the owner of the action list
- L77 _public function_ `virtual bool IsSupported(const FRCSignatureField& InField) const` — Determines whether this Action can execute under a given field @param InField the field that will contain this action if supported @return true if the action is supported
- L87 _public function_ `virtual bool Execute(const FRCSignatureActionContext& InContext) const` — Executes the Action logic @param InContext context of the action (preset, exposed property and uobject being used) @return true if the action did anything to the preset
- L94 _public function_ `virtual void PostEditChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged)` — Called whenever there's a change affecting the action in the Details Panel
- L99 _public function_ `virtual FRCSignatureActionIcon GetIcon() const` — Retrieves the icon to use to represent this Signature Action

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RCSignatureActionInstance.h` (Public)


#### struct `FRCSignatureActionInstance`  
`struct FRCSignatureActionInstance`  
_L20-43_
- reflection: `USTRUCT()`
- desc: Struct containing an Action Instance and handling its Execution
- L24 _public prototype_ `FRCSignatureActionInstance() = default;`
- L26 _public prototype_ `explicit FRCSignatureActionInstance(const UScriptStruct* InScriptStruct, const FRCSignatureField& InFieldOwner);`
- L28 _public prototype_ `const FRCSignatureAction* GetAction() const;`
- L30 _public prototype_ `TSharedRef<FStructOnScope> MakeStructOnScope();`
- L32 _public prototype_ `void PostLoad(const FRCSignatureField& InFieldOwner);`
- L34 _public prototype_ `bool Execute(const FRCSignatureActionContext& InContext) const;`
- L37 _public prototype_ `void PostEditChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged);`
- L42 _private member_ `TInstancedStruct<FRCSignatureAction> ActionInstance;` — `UPROPERTY()`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RCSignatureRegistry.h` (Public)


#### class `URCSignatureRegistry`  
`class URCSignatureRegistry : public UObject`  
_L10-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L15 _public function_ `TConstArrayView<FRCSignature> GetSignatures() const`
- L25 _public prototype_ `const FRCSignature* FindSignature(const FGuid& InSignatureId) const;` — Find an existing Signature matching the given id @param InSignatureId the id of the signature to find @return const pointer to the signature if found, nullptr otherwise
- L32 _public prototype_ `FRCSignature* FindSignatureMutable(const FGuid& InSignatureId);` — Find an existing Signature matching the given id @param InSignatureId the id of the signature to find @return pointer to the signature if found, nullptr otherwise
- L35 _public prototype_ `FRCSignature& AddSignature();` — Adds a new Signature to this registry
- L42 _public prototype_ `int32 RemoveSignature(const FGuid& InSignatureId);` — Removes the Signature with the matching Signature Id @param InSignatureId the id of the signature to remove @return the number of signatures removed
- L45 _public prototype_ `void EmptySignatures();` — Removes all the Signature in this registry
- L48 _public prototype_ `virtual void PostLoad() override;`
- L54 _private member_ `TArray<FRCSignature> Signatures;` — `UPROPERTY()` — Holds all the Signatures in this Registry

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RCVirtualProperty.h` (Public)


#### class `URCVirtualPropertyBase`  
`class URCVirtualPropertyBase : public UObject`  
_L23-389_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Base class for dynamic virtual properties Remote Control Virtual Properties using Property Bag and FInstancedPropertyBag to serialize FProperties values and UStruct
- L32 _protected prototype_ `virtual const uint8* GetContainerPtr() const;` — Return pointer to memory const container
- L35 _protected prototype_ `virtual uint8* GetContainerPtr();` — Return pointer to memory container
- L38 _protected prototype_ `virtual const uint8* GetValuePtr() const;` — Return pointer to const value
- L41 _protected prototype_ `virtual uint8* GetValuePtr();` — Return pointer to value
- L44 _protected prototype_ `virtual const FPropertyBagPropertyDesc* GetBagPropertyDesc() const;` — Return Pointer to Bag Property Description
- L47 _protected prototype_ `virtual const FInstancedPropertyBag* GetPropertyBagInstance() const;` — Pointer to Instanced property which is holds  bag of properties
- L50 _protected function_ `virtual void OnPreChangePropertyValue()` — Notifies pre change for Virtual Property value
- L53 _protected function_ `virtual void OnModifyPropertyValue()` — Notifies post change for Virtual Property value
- L57 _public function_ `virtual void Init()` — Initialization routine. Called after the parent container has setup data for this property
- L59 _public function_ `virtual void InitPropertyBagPropertyDescription(FPropertyBagPropertyDesc& InOutPropertyDesc)`
- L65 _public function_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap)` — @brief Called internally when entity Ids are renewed. @param InEntityIdMap Map of old Id to new Id.
- L68 _public prototype_ `virtual const FProperty* GetProperty() const;` — Returns const FProperty for this RC virtual property
- L71 _public prototype_ `virtual FProperty* GetProperty();` — Returns FProperty for this RC virtual property
- L74 _public prototype_ `EPropertyBagPropertyType GetValueType() const;` — Return property bag property type
- L81 _public prototype_ `FString GetMetadataValue(FName Key) const;` — Get the meta-data matching the given key. NOTE: This meta-data is available at runtime and is different from the property bag property's meta-data @return the value mapped to the key
- L87 _public prototype_ `void SetMetadataValue(FName Key, FString Data);` — Adds/sets the meta-data with the given key and value. NOTE: This meta-data is available at runtime and is different from the property bag property's meta-data
- L93 _public prototype_ `void RemoveMetadataValue(FName Key);` — Removes the meta-data matching the given key. NOTE: This meta-data is available at runtime and is different from the property bag property's meta-data
- L96 _public prototype_ `const UObject* GetValueTypeObjectWeakPtr() const;` — Return pointer to object that defines the Enum, Struct, or Class.
- L103 _public prototype_ `void SerializeToBackend(IStructSerializerBackend& OutBackend);` — Serialize Virtual Property to given Backend @param OutBackend Struct Serialize Backend
- L110 _public prototype_ `bool DeserializeFromBackend(IStructDeserializerBackend& InBackend);` — Deserialize Virtual Property from a given Backend @param InBackend  - Deserializer containing a payload with value data
- L113 _public prototype_ `bool IsNumericType() const;` — Whether this Virtual Property is a numeric type, i.e. an Integral or Floating point type
- L116 _public prototype_ `bool IsVectorType() const;` — Whether this Virtual Property represents an FVector
- L119 _public prototype_ `bool IsVector2DType() const;` — Whether this Virtual Property represents an FVector2D
- L122 _public prototype_ `bool IsColorType() const;` — Whether this Virtual Property represents an FColor
- L125 _public prototype_ `bool IsLinearColorType() const;` — Whether this Virtual Property represents an FColor
- L128 _public prototype_ `bool IsRotatorType() const;` — Whether this Virtual Property represents an FRotator
- L131 _public prototype_ `bool IsValueEqual(URCVirtualPropertyBase* InVirtualProperty) const;` — Compare this virtual property value with given property value
- L134 _public prototype_ `bool IsValueGreaterThan(URCVirtualPropertyBase* InVirtualProperty) const;` — Operator > comparison of self with a given virtual property
- L137 _public prototype_ `bool IsValueGreaterThanOrEqualTo(URCVirtualPropertyBase* InVirtualProperty) const;` — Operator >= comparison of self with a given virtual property
- L140 _public prototype_ `bool IsValueLesserThan(URCVirtualPropertyBase* InVirtualProperty) const;` — Operator < comparison of self with a given virtual property
- L143 _public prototype_ `bool IsValueLesserThanOrEqualTo(URCVirtualPropertyBase* InVirtualProperty) const;` — Operator <= comparison of self with a given virtual property
- L152 _public prototype_ `bool CopyCompleteValue(const FProperty* InTargetProperty, uint8* InTargetValuePtr);` — Copy this virtual property's data onto a given FProperty @param InTargetProperty - The property onto which our value is to be copied @param InTargetValuePtr - The memory location for the target property @return true if copied successfully
- L162 _public prototype_ `bool CopyCompleteValue(const FProperty* InTargetProperty, uint8* InTargetValuePtr, bool bPassByteEnumPropertyComparison);` — Copy this virtual property's data onto a given FProperty @param InTargetProperty - The property onto which our value is to be copied @param InTargetValuePtr - The memory location for the target property @param bPassByteEnumPropertyComparison - Go to the copy if the Property and the Target property are Enum and Byte @return true if copied successfully
- L170 _public prototype_ `bool CopyCompleteValue(URCVirtualPropertyBase* InVirtualProperty);` — Copy this virtual property's data onto a given Virtual Property @param InVirtualProperty - The virtual property onto which our value is to be copied @return true if copied successfully
- L174 _public prototype_ `bool GetValueBool(bool& OutBoolValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Bool value from Virtual Property
- L178 _public prototype_ `bool GetValueInt8(int8& OutInt8) const;` — `UFUNCTION()` — Get Int8 value from Virtual Property
- L182 _public prototype_ `bool GetValueByte(uint8& OutByte) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Byte value from Virtual Property
- L186 _public prototype_ `bool GetValueEnum(uint8& OutByte) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get raw Enum value from Virtual Property
- L190 _public prototype_ `bool GetValueInt16(int16& OutInt16) const;` — `UFUNCTION()` — Get Int16 value from Virtual Property
- L194 _public prototype_ `bool GetValueUint16(uint16& OutUInt16) const;` — `UFUNCTION()` — Get Uint16 value from Virtual Property
- L198 _public prototype_ `bool GetValueInt32(int32& OutInt32) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Int32 value from Virtual Property
- L202 _public prototype_ `bool GetValueUInt32(uint32& OutUInt32) const;` — `UFUNCTION()` — Get Uint32 value from Virtual Property
- L206 _public prototype_ `bool GetValueInt64(int64& OuyInt64) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Int64 value from Virtual Property
- L210 _public prototype_ `bool GetValueUint64(uint64& OuyUInt64) const;` — `UFUNCTION()` — Get Uint64 value from Virtual Property
- L214 _public prototype_ `bool GetValueFloat(float& OutFloat) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Float value from Virtual Property
- L218 _public prototype_ `bool GetValueDouble(double& OutDouble) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Double value from Virtual Property
- L222 _public prototype_ `bool GetValueString(FString& OutStringValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get String value from Virtual Property
- L226 _public prototype_ `bool GetValueName(FName& OutNameValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Name value from Virtual Property
- L230 _public prototype_ `bool GetValueText(FText& OutTextValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Text value from Virtual Property
- L234 _public prototype_ `bool GetValueNumericInteger(int64& OutInt64Value) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Numeric value from Virtual Property
- L238 _public prototype_ `bool GetValueVector(FVector& OutVector) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Vector value from Virtual Property
- L242 _public prototype_ `bool GetValueVector2D(FVector2D& OutVector2D) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Vector2D value from Virtual Property
- L246 _public prototype_ `bool GetValueRotator(FRotator& OutRotator) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Rotator value from Virtual Property
- L250 _public prototype_ `bool GetValueColor(FColor& OutColor) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Color value from Virtual Property
- L254 _public prototype_ `bool GetValueLinearColor(FLinearColor& OutLinearColor) const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get LinearColor value from Virtual Property
- L258 _public prototype_ `UObject* GetValueObject() const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Get Object value from Virtual Property
- L264 _public prototype_ `FString GetDisplayValueAsString() const;` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Infers correct type internally, fetches value from memory and returns the value as a string that can be immediately used for dispaly (without needing to create a generic readonly property widget)
- L268 _public prototype_ `bool SetValueBool(const bool InBoolValue);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Bool value from Virtual Property
- L272 _public prototype_ `bool SetValueInt8(const int8 InInt8);` — `UFUNCTION()` — Set Int8 value from Virtual Property
- L276 _public prototype_ `bool SetValueByte(const uint8 InByte);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Byte value from Virtual Property
- L280 _public prototype_ `bool SetValueInt16(const int16 InInt16);` — `UFUNCTION()` — Set Int16 value from Virtual Property
- L284 _public prototype_ `bool SetValueUint16(const uint16 InUInt16);` — `UFUNCTION()` — Set Uint16 value from Virtual Property
- L288 _public prototype_ `bool SetValueInt32(const int32 InInt32);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Int32 value from Virtual Property
- L292 _public prototype_ `bool SetValueUInt32(const uint32 InUInt32);` — `UFUNCTION()` — Set Uint32 value from Virtual Property
- L296 _public prototype_ `bool SetValueInt64(const int64 InInt64);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Int64 value from Virtual Property
- L300 _public prototype_ `bool SetValueUint64(const uint64 InUInt64);` — `UFUNCTION()` — Set Uint64 value from Virtual Property
- L304 _public prototype_ `bool SetValueFloat(const float InFloat);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Float value from Virtual Property
- L308 _public prototype_ `bool SetValueDouble(const double InDouble);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Double value from Virtual Property
- L312 _public prototype_ `bool SetValueString(const FString& InStringValue);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set String value from Virtual Property
- L316 _public prototype_ `bool SetValueName(const FName& InNameValue);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Name value from Virtual Property
- L320 _public prototype_ `bool SetValueText(const FText& InTextValue);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Text value from Virtual Property
- L324 _public prototype_ `bool SetValueNumericInteger(const int64 InInt64Value);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Numeric value from Virtual Property
- L328 _public prototype_ `bool SetValueVector(const FVector& InVector);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Vector value from Virtual Property
- L332 _public prototype_ `bool SetValueVector2D(const FVector2D& InVector2D);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Vector2D value from Virtual Property
- L336 _public prototype_ `bool SetValueRotator(const FRotator& InRotator);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Rotator value from Virtual Property
- L340 _public prototype_ `bool SetValueColor(const FColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set Color value from Virtual Property
- L344 _public prototype_ `bool SetValueLinearColor(const FLinearColor& InLinearColor);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Behaviour")` — Set LinearColor value from Virtual Property
- L348 _public prototype_ `FName GetPropertyName() const;` — `UFUNCTION(BlueprintPure, Category = "Remote Control Behaviour")` — Get FProperty Name
- L351 _public prototype_ `static FName GetVirtualPropertyTypeDisplayName(const EPropertyBagPropertyType InValueType, UObject* InValueTypeObject);` — Fetches a user-friendly representation of the Virtual Property's type name (i.e. Controller type), given a Property Bag type and value object (for structures)
- L354 _public prototype_ `void SetDisplayIndex(const int32 InDisplayIndex);` — Updates the display index of the virtual property (transaction aware)
- L356 _public function_ `virtual void UpdateEntityUsage(const URemoteControlPreset* InPreset, TMap<FGuid, TSet<UObject*>>& InEntityToBehavior) const`
- L361 _public member_ `FName PropertyName;` — `UPROPERTY()` — Unique property name
- L365 _public member_ `FGuid Id;` — `UPROPERTY()` — Property Id
- L369 _public member_ `FName FieldId;` — `UPROPERTY()` — Property Field Id
- L373 _public member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeakPtr;` — `UPROPERTY()` — Pointer to Remote Control Preset
- L377 _public member_ `FName DisplayName;` — `UPROPERTY()` — Unique user friendly name of the controller, used as identifier in some API.
- L381 _public member_ `FText Description;` — `UPROPERTY()` — Controller description
- L385 _public member_ `int32 DisplayIndex;` — `UPROPERTY()` — User configurable Display Index for this Virtual Property (as Logic Controller) when represented as a row in the RC Logic Controllers list
- L388 _public member_ `TMap<FName, FString> Metadata;` — `UPROPERTY()`

#### class `URCVirtualPropertyInContainer`  
`class URCVirtualPropertyInContainer : public URCVirtualPropertyBase`  
_L396-409_
- reflection: `UCLASS()`
- inherits: `URCVirtualPropertyBase`
- desc: Remote Control Virtual Property which is stores in container with many properties Where Property Bag has more then one Property
- L402 _protected prototype_ `virtual const FInstancedPropertyBag* GetPropertyBagInstance() const override;`
- L408 _public member_ `TWeakObjectPtr<URCVirtualPropertyContainerBase> ContainerWeakPtr;` — `UPROPERTY()` — Pointer to container where stores Virtual Properties

#### class `URCVirtualPropertySelfContainer`  
`class URCVirtualPropertySelfContainer : public URCVirtualPropertyBase`  
_L416-495_
- reflection: `UCLASS()`
- inherits: `URCVirtualPropertyBase`
- desc: Remote Control Virtual Property which is stores in self defined Property Bag In this case SelfContainer holds only single property in the Property Bag
- L429 _public prototype_ `void AddProperty(const FName InPropertyName, const EPropertyBagPropertyType InValueType, UObject* InValueTypeObject = nullptr);` — Adds a new property to the bag. If property with this name already in bag the function just return @param InPropertyName				Name of the property @param InValueType					Property Type @param InValueTypeObject				Property Type object if exists
- L439 _public prototype_ `bool DuplicateProperty(const FName& InPropertyName, const FProperty* InSourceProperty);` — Duplicates property from give Property. If property with this name already in bag the function just return @param InPropertyName				Name of the property @param InSourceProperty				Source FProperty for duplication @return true if property duplicated successfully
- L450 _public prototype_ `bool DuplicatePropertyWithCopy(const FName& InPropertyName, const FProperty* InSourceProperty, const uint8* InSourceContainerPtr);` — Duplicates property from give Property and copy the value. If property with this name already in bag the function just return @param InPropertyName				Name of the property @param InSourceProperty				Source FProperty for duplication @param InSourceContainerPtr			Pointer to source container @return true if property duplicated and value copied successfully
- L459 _public prototype_ `bool DuplicatePropertyWithCopy(URCVirtualPropertyBase* InVirtualProperty);` — Duplicates property from given Virtual Property. If property with this name already in bag the function just return @param InVirtualProperty				Virtual Property to duplicate from @return true if property duplicated and value copied successfully
- L469 _public prototype_ `bool UpdateValueWithProperty(const FProperty* InProperty, const void* InPropertyContainer);` — Update property bag value using the property and the container passed. @param InProperty Property used to update the bag property value @param InPropertyContainer Container to take the value using the property @return true if SetValue of the bag returned Success otherwise false
- L478 _public prototype_ `bool UpdateValueWithProperty(const URCVirtualPropertyBase* InVirtualProperty);` — Update property bag value using URCVirtualPropertyBase passed. @param InVirtualProperty Virtual Property to update from @return true if value copied successfully
- L481 _public prototype_ `void Reset();` — Resets the property bag instance to empty and remove Virtual Property data
- L484 _public prototype_ `TSharedPtr<FStructOnScope> CreateStructOnScope();` — Creates new Struct on Scope for this Property Bag UStruct and Memory
- L488 _protected prototype_ `virtual const FInstancedPropertyBag* GetPropertyBagInstance() const override;`
- L494 _private member_ `FInstancedPropertyBag Bag;` — `UPROPERTY()` — Instanced property bag for store a bag of properties.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RCVirtualPropertyContainer.h` (Public)


#### struct `FRCVirtualPropertyCategory`  
`struct FRCVirtualPropertyCategory`  
_L22-34_
- reflection: `USTRUCT()`
- desc: Describes a category into which properties can be placed.
- L27 _public member_ `FGuid Id = FGuid();` — `UPROPERTY()`
- L30 _public member_ `FText Name = FText::GetEmpty();` — `UPROPERTY()`
- L33 _public member_ `int32 DisplayIndex = INDEX_NONE;` — `UPROPERTY()`

#### class `URCVirtualPropertyContainerBase`  
`class URCVirtualPropertyContainerBase : public UObject`  
_L40-233_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Container for more then one Virtual Property
- L59 _public prototype_ `virtual URCVirtualPropertyInContainer* AddProperty(const FName& InPropertyName, TSubclassOf<URCVirtualPropertyInContainer> InPropertyClass, const EPropertyBagPropertyType InValueType, UObject* InValueTypeObject = nullptr, TArray<FPropertyBagPropertyDescMetaData> MetaData = TArray<FPropertyBagPropertyDescMetaData>());` — Add property to this container. That will add property to Property Bag and Create Remote Control Virtual Property @param InPropertyName				Property Name to add @param InPropertyClass				Class of the Virtual Property @param InValueType					Property Type @param InValueTypeObject				Property Type object if exists @param MetaData                      Property Metadata used by Slate widgets (eg: Delta, LinearDeltaSensitivity, etc) @return Virtual Property Object
- L71 _public prototype_ `virtual URCVirtualPropertyInContainer* DuplicateProperty(const FName& InPropertyName, const FProperty* InSourceProperty, TSubclassOf<URCVirtualPropertyInContainer> InPropertyClass);` — Duplicates a property from given FProperty. That will add property to Property Bag and Create Remote Control Virtual Property @param InPropertyName				Name of the property @param InSourceProperty				Source FProperty for duplication @param InPropertyClass				Class of the Virtual Property @return Virtual Property Object
- L84 _public prototype_ `virtual URCVirtualPropertyInContainer* DuplicatePropertyWithCopy(const FName& InPropertyName, const FProperty* InSourceProperty, const uint8* InSourceContainerPtr, TSubclassOf<URCVirtualPropertyInContainer> InPropertyClass);` — Duplicates a property from a given FProperty and copies the property value That will add property to Property Bag and Create Remote Control Virtual Property @param InPropertyName				Name of the property @param InSourceProperty				Source FProperty for duplication @param InPropertyClass				Class of the Virtual Property @param InSourceContainerPtr			Pointer to source container @return Virtual Property Object
- L94 _public prototype_ `virtual URCVirtualPropertyInContainer* DuplicateVirtualProperty(URCVirtualPropertyInContainer* InVirtualProperty);` — Given a virtual property this funciton duplicates it (via DuplicateObject) and syncs the internal Controller Container and PropertyBag containers as well. @param InVirtualProperty				Virtual Property to be duplicated @return Virtual Property Object
- L99 _public prototype_ `bool HasVirtualProperty(const URCVirtualPropertyBase* InVirtualProperty) const;` — Returns whether this container contains the given property.
- L104 _public prototype_ `virtual bool RemoveProperty(const FName& InPropertyName);` — Removes a property from the container by name if it exists.
- L107 _public prototype_ `virtual void Reset();` — Resets the property bag instance to empty and remove Virtual Properties
- L112 _public prototype_ `virtual URCVirtualPropertyBase* GetVirtualProperty(const FName InPropertyName) const;` — Returns virtual property by specified name.
- L117 _public prototype_ `URCVirtualPropertyBase* GetVirtualProperty(const FGuid& InId) const;` — Returns virtual property by unique Id.
- L122 _public prototype_ `virtual URCVirtualPropertyBase* GetVirtualPropertyByDisplayName(const FName InDisplayName) const;` — Returns virtual property by user-friendly display name (Controller Name)
- L127 _public prototype_ `virtual URCVirtualPropertyBase* GetVirtualPropertyByFieldId(const FName InFieldId) const;` — Returns the first found virtual property matching the specified Field Id
- L132 _public prototype_ `virtual URCVirtualPropertyBase* GetVirtualPropertyByFieldId(const FName InFieldId, const EPropertyBagPropertyType InType) const;` — Returns the first virtual property matching the specified Field Id and ValueType
- L137 _public prototype_ `virtual TArray<URCVirtualPropertyBase*> GetVirtualPropertiesByFieldId(const FName InFieldId) const;` — Returns all virtual properties with the specified Field Id
- L142 _public prototype_ `int32 GetNumVirtualProperties() const;` — Returns number of virtual properties.
- L147 _public prototype_ `const UPropertyBag* GetPropertyBagStruct() const;` — Returns the Property Bag Struct of this Container
- L152 _public prototype_ `FStructView GetPropertyBagMutableValue();` — Creates new Struct View for this Property Bag UStruct and Memory
- L157 _public prototype_ `TSharedPtr<FStructOnScope> CreateStructOnScope();` — Creates new Struct on Scope for this Property Bag UStruct and Memory
- L162 _public prototype_ `FName SetControllerDisplayName(FGuid InGuid, FName InNewName);` — Rename the controller with the given InGuid with the InNewName passed as candidate and return the new name
- L167 _public prototype_ `static FName GenerateUniquePropertyName(const FName& InPropertyName, const EPropertyBagPropertyType InValueType, UObject* InValueTypeObject, const URCVirtualPropertyContainerBase* InContainer);` — Generates unique name for the property for specified property container
- L172 _public prototype_ `static FName GenerateUniquePropertyName(const FName& InPropertyName, const URCVirtualPropertyContainerBase* InContainer);` — Generates unique name for the property for specified property container
- L177 _public prototype_ `static FName GenerateUniqueDisplayName(const FName& InPropertyName, const URCVirtualPropertyContainerBase* InContainer);` — Generates unique display name for the controllers
- L183 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap);` — @brief Called internally when entity Ids are renewed. @param InEntityIdMap Map of old Id to new Id.
- L186 _public prototype_ `void CacheControllersLabels();` — Cache this preset's controllers labels.
- L189 _public prototype_ `void FixAndCacheControllersLabels();` — Fix controllers labels for older presets.
- L193 _public prototype_ `virtual void PostEditUndo();` — Called after applying a transaction to the object. Used to broadcast Undo related container changes to UI.
- L196 _public function_ `virtual void OnPreChangePropertyValue(const FPropertyChangedEvent& PropertyChangedEvent)` — Delegate when the value is being scrubbed in UI
- L199 _public prototype_ `virtual void OnModifyPropertyValue(const FPropertyChangedEvent& PropertyChangedEvent);` — Delegate when object changed
- L203 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVirtualPropertyContainerModified);` — Returns the delegate that notifies changes to the virtual property container
- L204 _public function_ `FOnVirtualPropertyContainerModified& OnVirtualPropertyContainerModified()`
- L207 _private prototype_ `void AddVirtualProperty(URCVirtualPropertyBase* InVirtualProperty);`
- L212 _protected member_ `FInstancedPropertyBag Bag;` — `UPROPERTY()` — Holds bag of properties.
- L217 _public member_ `TSet<TObjectPtr<URCVirtualPropertyBase>> VirtualProperties;` — `UPROPERTY()` — Set of the virtual properties
- L221 _public member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeakPtr;` — `UPROPERTY()` — Pointer to Remote Control Preset
- L224 _public member_ `FOnVirtualPropertyContainerModified OnVirtualPropertyContainerModifiedDelegate;` — Delegate that notifies changes to the virtual property container
- L227 _public member_ `TArray<FRCVirtualPropertyCategory> Categories;` — `UPROPERTY()`
- L232 _private member_ `TMap<FName, FGuid> ControllerLabelToIdCache;` — `UPROPERTY(Transient)` — Map of Controller Name to GUID.

#### Free symbols / members of external scopes

- L203 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVirtualPropertyContainerModified);` — Returns the delegate that notifies changes to the virtual property container

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlActor.h` (Public)


#### struct `FRemoteControlActor`  
`struct FRemoteControlActor : public FRemoteControlEntity`  
_L20-72_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRemoteControlEntity`
- desc: Represents an actor exposed in the panel.
- L24 _public prototype_ `FRemoteControlActor() = default;`
- L26 _public function_ `FRemoteControlActor(URemoteControlPreset* InOwner, FName InLabel, const TArray<URemoteControlBinding*>& InBindings) : FRemoteControlEntity(InOwner, InLabel, InBindings)`
- L36 _public function_ `virtual void BindObject(UObject* InObjectToBind) override`
- L44 _public function_ `virtual uint32 GetUnderlyingEntityIdentifier() const override`
- L49 _public function_ `virtual UClass* GetSupportedBindingClass() const override`
- L52 _public function_ `AActor* GetActor() const`
- L61 _public function_ `void SetActor(AActor* InActor)`
- L71 _public member_ `FSoftObjectPath Path;` — `UPROPERTY(BlueprintReadOnly, Category = "RemoteControlEntity")` — Path to the exposed object.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlBinding.h` (Public)


#### class `URemoteControlBinding`  
`class URemoteControlBinding : public UObject`  
_L35-97_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UObject`
- desc: Acts as a bridge between an exposed property/function and an object to act on.
- L43 _public prototype_ `virtual void SetBoundObject(const TSoftObjectPtr<UObject>& InObject) PURE_VIRTUAL(URemoteControlBinding::SetBoundObject,);` — Set the object this binding should represent.
- L48 _public prototype_ `virtual void UnbindObject(const TSoftObjectPtr<UObject>& InBoundObject) PURE_VIRTUAL(URemoteControlBinding::UnbindObject,);` — Unset the underlying object this binding currently represents.
- L54 _public prototype_ `virtual UObject* Resolve() const PURE_VIRTUAL(URemoteControlBinding::Resolve, return nullptr;);` — Resolve the bound object for the current map. @Note Will return the PIE object when in a PIE session.
- L61 _public prototype_ `virtual UObject* ResolveForWorld(const UWorld* InWorld) const PURE_VIRTUAL(URemoteControlBinding::ResolveForWorld, return nullptr;);` — Return the Entity Object in the given world @param InWorld World where to retrieve the object @return The object in the given world or nullptr if not found
- L66 _public prototype_ `virtual bool IsValid() const PURE_VIRTUAL(URemoteControlBinding::IsValid, return false;);` — Whether this binding represents a valid object.
- L71 _public prototype_ `virtual bool IsBound(const TSoftObjectPtr<UObject>& Object) const PURE_VIRTUAL(URemoteControlBinding::IsBound, return false;);` — Check if the object is bound.
- L77 _public prototype_ `virtual bool PruneDeletedObjects() PURE_VIRTUAL(URemoteControlBinding::PruneDeletedObjects, return false;);` — Remove objects that were deleted from the binding. @return true if at least one object was removed from this binding's objects.
- L82 _public prototype_ `FSoftObjectPath GetLastBoundObjectPath() const;` — Get the last object this binding was pointing to.
- L89 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category=Default)` — The name of this binding. Defaults to the bound object's name.
- L96 _protected member_ `mutable FSoftObjectPath LastBoundObjectPath;` — `UPROPERTY()` — The path to the last object that was bound.

#### class `URemoteControlLevelIndependantBinding`  
`class URemoteControlLevelIndependantBinding : public URemoteControlBinding`  
_L100-126_
- reflection: `UCLASS(BlueprintType)`
- inherits: `URemoteControlBinding`
- L106 _public prototype_ `virtual void PostLoad() override;`
- L110 _public prototype_ `virtual void SetBoundObject(const TSoftObjectPtr<UObject>& InObject) override;`
- L111 _public prototype_ `virtual void UnbindObject(const TSoftObjectPtr<UObject>& InBoundObject) override;`
- L112 _public prototype_ `virtual UObject* Resolve() const override;`
- L113 _public prototype_ `virtual UObject* ResolveForWorld(const UWorld* InWorld) const override;`
- L114 _public prototype_ `virtual bool IsValid() const override;`
- L115 _public prototype_ `virtual bool IsBound(const TSoftObjectPtr<UObject>& Object) const override;`
- L116 _public prototype_ `virtual bool PruneDeletedObjects() override;`
- L125 _private member_ `TSoftObjectPtr<UObject> BoundObject;` — `UPROPERTY()` — Holds the bound object.

#### struct `FRemoteControlInitialBindingContext`  
`struct FRemoteControlInitialBindingContext`  
_L129-194_
- reflection: `USTRUCT()`
- L137 _public member_ `TSoftClassPtr<UObject> SupportedClass;` — `UPROPERTY()` — The class that's supported by this binding.
- L143 _public member_ `FName ComponentName;` — `UPROPERTY()` — Name of the component if any.
- L149 _public member_ `FString SubObjectPath;` — `UPROPERTY()` — Path to the subobject if any.
- L155 _public member_ `TSoftClassPtr<AActor> OwnerActorClass;` — `UPROPERTY()` — The class of the actor that's targeted by this binding or the class of the actor that owns the component that is targeted.
- L161 _public member_ `FName OwnerActorName;` — `UPROPERTY()` — Name of the initial actor that was targetted by this binding.
- L163 _public function_ `bool IsEmpty() const`
- L185 _public function_ `bool HasValidComponentName() const`
- L190 _public function_ `bool HasValidSubObjectPath() const`

#### class `URemoteControlLevelDependantBinding`  
`class URemoteControlLevelDependantBinding : public URemoteControlBinding`  
_L197-284_
- reflection: `UCLASS(BlueprintType)`
- inherits: `URemoteControlBinding`
- L203 _public prototype_ `virtual void PostLoad() override;`
- L207 _public prototype_ `virtual void SetBoundObject(const TSoftObjectPtr<UObject>& BoundObject) override;`
- L208 _public prototype_ `virtual void UnbindObject(const TSoftObjectPtr<UObject>& BoundObject) override;`
- L209 _public prototype_ `virtual UObject* Resolve() const override;`
- L210 _public prototype_ `virtual UObject* ResolveForWorld(const UWorld* InWorld) const override;`
- L211 _public prototype_ `virtual bool IsValid() const override;`
- L212 _public prototype_ `virtual bool IsBound(const TSoftObjectPtr<UObject>& Object) const override;`
- L213 _public prototype_ `virtual bool PruneDeletedObjects() override;`
- L220 _public prototype_ `void SetBoundObject(const TSoftObjectPtr<ULevel>& Level, const TSoftObjectPtr<UObject>& BoundObject);` — Set the bound object by specifying the level it resides in. @Note Useful is you want to set the bound object without loading the level/object.
- L225 _public prototype_ `void SetBoundObject_OverrideContext(const TSoftObjectPtr<UObject>& InObject);` — Set the bound object and reinitialize the context used for rebinding purposes.
- L231 _public prototype_ `void InitializeForNewLevel();` — Initialize this binding to be used with the new current level. Copies the binding from the last successful resolve in case the level was duplicated.
- L236 _public prototype_ `UClass* GetSupportedOwnerClass() const;` — Get the suppported class of the bound object or of the owner of the bound object in the case of a bound component.
- L239 _public prototype_ `UWorld* GetCurrentWorld(bool bAllowPIE = false) const;` — Get the current world associated with the preset or the editor world as a fallback.
- L243 _private prototype_ `TSoftObjectPtr<UObject> ResolveForCurrentWorld(bool bAllowPIE = false) const;` — Attempt resolving the binding for the current world.
- L246 _private prototype_ `void UpdateBindingContext(UObject* InObject) const;` — Update this binding's context with the object passed as argument.
- L252 _private member_ `TMap<TSoftObjectPtr<ULevel>, TSoftObjectPtr<UObject>> BoundObjectMap_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "BoundObjectMap is deprecated, please use BoundObjectMapByPath instead."))`
- L255 _private member_ `mutable TMap<TSoftObjectPtr<UWorld>, TSoftObjectPtr<ULevel>> SubLevelSelectionMap_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "SubLevelSelectionMap is deprecated, please use SubLevelSelectionMapByPath instead."))`
- L262 _private member_ `TMap<FSoftObjectPath, TSoftObjectPtr<UObject>> BoundObjectMapByPath;` — `UPROPERTY()` — The map bound objects with their level as key.
- L270 _private member_ `mutable TMap<FSoftObjectPath, TSoftObjectPtr<ULevel>> SubLevelSelectionMapByPath;` — `UPROPERTY()` — Keeps track of which sublevel was last used when binding in a particular world. Used in the case where a binding points to objects that end up in the same world but in different sublevels, this ensures that we know which object was last
- L277 _private member_ `mutable TSoftObjectPtr<ULevel> LevelWithLastSuccessfulResolve;` — `UPROPERTY()` — Caches the last level that had a successful resolve. Used to decide which level to use when reinitializing this binding in a new level.
- L280 _private member_ `mutable FRemoteControlInitialBindingContext BindingContext;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RemoteControlBinding` (scope `UE`)
- L20 _prototype_ `bool IsValidObjectForRebinding(UObject* InObject, UWorld* PresetWorld);` (scope `UE::RemoteControlBinding`) — @return whether an object is a valid rebinding target.
- L24 _prototype_ `bool IsValidActorForRebinding(AActor* InActor, UWorld* PresetWorld);` (scope `UE::RemoteControlBinding`) — @return whether an actor is a valid rebinding target.
- L28 _prototype_ `bool IsValidSubObjectForRebinding(UObject* InComponent, UWorld* PresetWorld);` (scope `UE::RemoteControlBinding`) — @return whether a subobject is a valid rebinding target.
- L171 _function_ `friend bool operator==(const FRemoteControlInitialBindingContext& LHS, const FRemoteControlInitialBindingContext& RHS)`
- L180 _function_ `friend bool operator!=(const FRemoteControlInitialBindingContext& LHS, const FRemoteControlInitialBindingContext& RHS)`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlEntity.h` (Public)


#### struct `FRemoteControlEntity`  
`struct FRemoteControlEntity`  
_L16-168_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base class for exposed objects, properties, functions etc...
- L20 _public prototype_ `FRemoteControlEntity() = default;`
- L22 _public function_ `virtual ~FRemoteControlEntity()`
- L25 _public prototype_ `const UScriptStruct* GetStruct() const;` — Get the type of this remote control entity.
- L33 _public prototype_ `FName Rename(FName NewLabel);` — Change this entity's label. @param NewLabel the desired label. @return The assigned label. @note The returned label can be different from the desired one if the label was already tkaen in the preset.
- L38 _public function_ `FName GetLabel() const` — Get the label of this entity.
- L43 _public function_ `FGuid GetId() const` — Get the id of this entity.
- L48 _public function_ `URemoteControlPreset* GetOwner()` — Get the preset that owns this entity.
- L53 _public prototype_ `TArray<UObject*> GetBoundObjects() const;` — Get all resolved bindings under this entity.
- L58 _public prototype_ `UObject* GetBoundObject() const;` — Resolve the first binding for this entity.
- L65 _public prototype_ `UObject* GetBoundObjectForWorld(const UWorld* InWorld) const;` — Return the Entity Object in the given world @param InWorld World where to retrieve the object @return The object in the given world or nullptr if not found
- L70 _public prototype_ `const TArray<TWeakObjectPtr<URemoteControlBinding>>& GetBindings() const;` — Get the unresolved bindings of this exposed entity.
- L75 _public prototype_ `const TMap<FName, FString>& GetMetadata() const;` — Get the entity's metadata.
- L80 _public prototype_ `void RemoveMetadataEntry(FName Key);` — Remove a metadata entry.
- L85 _public prototype_ `void SetMetadataValue(FName Key, FString Value);` — Find or add a value in the entity's metadata map.
- L91 _public prototype_ `virtual void BindObject(UObject* InObjectToBind);` — Change the object this exposed entity is currently pointing to. @Note You should call CanBindObject before calling this method.
- L96 _public function_ `virtual bool CanBindObject(const UObject* InObjectToBind) const` — Return whether this entity supports binding to a given object.
- L101 _public prototype_ `virtual bool IsBound() const;` — Returns whether this entity can be resolved using its bound objects.
- L107 _public function_ `virtual uint32 GetUnderlyingEntityIdentifier() const` — Get an identifier for the underlying entity. This is used to figure out if two remote control entities have the same underlying field/actor.
- L116 _public function_ `virtual UClass* GetSupportedBindingClass() const` — Get the class of the object that can hold this field.
- L121 _public prototype_ `FSoftObjectPath GetLastBindingPath() const;` — Get the last valid binding path for this entity.
- L123 _public prototype_ `bool operator==(const FRemoteControlEntity& InEntity) const;`
- L124 _public prototype_ `bool operator==(FGuid InEntityId) const;`
- L132 _protected member_ `TMap<FName, FString> UserMetadata;` — `UPROPERTY()` — User specified metadata for this entity.
- L138 _protected member_ `TArray<TWeakObjectPtr<URemoteControlBinding>> Bindings;` — `UPROPERTY()` — The bound objects that are exposed or that hold the exposed entity.
- L141 _protected prototype_ `FRemoteControlEntity(URemoteControlPreset* InPreset, FName InLabel, const TArray<URemoteControlBinding*>& InBindings);`
- L145 _protected member_ `TWeakObjectPtr<URemoteControlPreset> Owner;` — `UPROPERTY(BlueprintReadOnly, Category = "RemoteControlEntity")` — The preset that owns this entity.
- L152 _protected member_ `FName Label;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RemoteControlEntity")` — This exposed entity's alias.
- L158 _protected member_ `FGuid Id;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RemoteControlEntity")` — Unique identifier for this entity
- L163 _protected prototype_ `DECLARE_DELEGATE_OneParam(FOnEntityModified, const FGuid&);` — Delegate called when the label of this entity changes or if one of its binding is updated.
- L164 _protected member_ `FOnEntityModified OnEntityModifiedDelegate;`

#### Free symbols / members of external scopes

- L163 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEntityModified, const FGuid&);` — Delegate called when the label of this entity changes or if one of its binding is updated.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlEntityFactory.h` (Public)


#### class `IRemoteControlPropertyFactory`  
`class IRemoteControlPropertyFactory : public TSharedFromThis<IRemoteControlPropertyFactory>`  
_L15-44_
- inherits: `TSharedFromThis<IRemoteControlPropertyFactory>`
- desc: Factory which is creates the instances of FRemoteControlProperty
- L19 _public function_ `virtual ~IRemoteControlPropertyFactory()` — Virtual destructor
- L29 _public prototype_ `virtual TSharedPtr<FRemoteControlProperty> CreateRemoteControlProperty(URemoteControlPreset* Preset, UObject* Object, FRCFieldPathInfo FieldPath, FRemoteControlPresetExposeArgs Args) = 0;` — Expose a property from given preset @param Preset the remote control preset object. @param Object the object that holds the property. @param FieldPath The name/path to the property. @param Args Optional arguments used to expose the property. @return The exposed property.
- L36 _public function_ `virtual void PostSetObjectProperties(UObject* Object, bool bInSuccess) const` — Post set property action @param Object the object that holds the property. @param bInSuccess Whether the property was set.
- L43 _public prototype_ `virtual bool SupportExposedClass(UClass* Class) const = 0;` — Whether the factory support exposed object @param Class class to expose @return true if the object is supported by given factory

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlField.h` (Public)


#### enum `EExposedFieldType`  
`enum class EExposedFieldType : uint8`  
_L18-23_
- reflection: `UENUM()`
- desc: The type of the exposed field.
- L20 _public enumerator_ `Invalid`
- L21 _public enumerator_ `Property`
- L22 _public enumerator_ `Function`

#### struct `FRemoteControlField`  
`struct FRemoteControlField : public FRemoteControlEntity`  
_L29-145_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRemoteControlEntity`
- desc: Represents a property or function that has been exposed to remote control.
- L33 _public prototype_ `FRemoteControlField() = default;`
- L36 _public prototype_ `FRemoteControlField(const FRemoteControlField&) = default;`
- L37 _public prototype_ `FRemoteControlField(FRemoteControlField&&) = default;`
- L38 _public prototype_ `FRemoteControlField& operator=(const FRemoteControlField&) = default;`
- L39 _public prototype_ `FRemoteControlField& operator=(FRemoteControlField&&) = default;`
- L48 _public prototype_ `TArray<UObject*> ResolveFieldOwners(const TArray<UObject*>& SectionObjects) const;` — `UE_DEPRECATED(4.27, "Please use GetBoundObjects.")` — Resolve the field's owners using the section's top level objects. @param SectionObjects The top level objects of the section. @return The list of UObjects that own the exposed field.
- L51 _public prototype_ `virtual void BindObject(UObject* InObjectToBind) override;`
- L52 _public prototype_ `virtual bool CanBindObject(const UObject* InObjectToBind) const override;`
- L57 _public prototype_ `virtual void ClearMask(ERCMask InMaskBit);` — `UE_DEPRECATED(5.6, "ClearMask is deprecated. Use per-protocol-binding masking instead.")` — Disables the given mask.
- L61 _public prototype_ `virtual void EnableMask(ERCMask InMaskBit);` — `UE_DEPRECATED(5.6, "EnableMask is deprecated. Use per-protocol-binding masking instead.")` — Enables the given mask.
- L65 _public prototype_ `virtual bool HasMask(ERCMask InMaskBit) const;` — `UE_DEPRECATED(5.6, "HasMask is deprecated. Use per-protocol-binding masking instead.")` — Returns true if the given mask is enabled, false otherwise.
- L69 _public function_ `virtual bool SupportsMasking() const` — `UE_DEPRECATED(5.6, "SupportsMasking is deprecated. Use per-protocol-binding masking instead.")` — Returns true if this field supports masking.
- L73 _public prototype_ `ERCMask GetActiveMasks() const;` — `UE_DEPRECATED(5.6, "GetActiveMasks is deprecated. Use per-protocol-binding masking instead.")` — Retrieves the enabled masks.
- L76 _public function_ `bool IsEditorOnly() const` — Returns whether the field is only available in editor.
- L83 _public member_ `EExposedFieldType FieldType = EExposedFieldType::Invalid;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RemoteControlEntity")` — The field's type.
- L89 _public member_ `FName FieldName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RemoteControlEntity")` — The exposed field's name.
- L95 _public member_ `FName PropertyId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RemoteControlEntity")` — The exposed field's identifier.
- L101 _public member_ `FRCFieldPathInfo FieldPathInfo;` — `UPROPERTY()` — Path information pointing to this field
- L105 _public member_ `TArray<FString> ComponentHierarchy_DEPRECATED;` — `UPROPERTY()`
- L114 _public member_ `TSet<FRemoteControlProtocolBinding> ProtocolBindings;` — `UPROPERTY()` — Stores the bound protocols for this exposed field It could store any types of the implemented protocols such as DMX, OSC, MIDI, etc The map holds protocol bindings stores the protocol mapping and protocol-specific mapping
- L121 _protected member_ `FSoftClassPath OwnerClass;` — `UPROPERTY()` — The class of the object that can have this field.
- L125 _protected member_ `bool bIsEditorOnly = false;` — `UPROPERTY()` — Whether the field is only available in editor.
- L130 _protected member_ `uint8 ActiveMasks_DEPRECATED = (uint8)RC_AllMasks;` — `UE_DEPRECATED(5.6, "ActiveMasks is deprecated. Use per-protocol-binding masking instead.")` — `UPROPERTY()` — Holds the actively enabled masks.
- L133 _protected prototype_ `FRemoteControlField(URemoteControlPreset* InPreset, EExposedFieldType InType, FName InLabel, FRCFieldPathInfo InFieldPathInfo, const TArray<URemoteControlBinding*> InBindings);`
- L134 _protected prototype_ `void PostSerialize(const FArchive& Ar);`
- L143 _private prototype_ `TArray<UObject*> ResolveFieldOwnersUsingComponentHierarchy(const TArray<UObject*>& SectionObjects) const;` — Resolve the field's owners using the section's top level objects and the deprecated component hierarchy. @param SectionObjects The top level objects of the section. @return The list of UObjects that own the exposed field.

#### struct `FRemoteControlProperty`  
`struct FRemoteControlProperty : public FRemoteControlField`  
_L151-266_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRemoteControlField`
- desc: Represents a property exposed to remote control.
- L156 _public prototype_ `FRemoteControlProperty() = default;`
- L159 _public prototype_ `FRemoteControlProperty(FName InLabel, FRCFieldPathInfo FieldPathInfo, TArray<FString> InComponentHierarchy);` — `UE_DEPRECATED(4.27, "This constructor is deprecated. Use the other constructor.")`
- L161 _public prototype_ `FRemoteControlProperty(URemoteControlPreset* InPreset, FName InLabel, FRCFieldPathInfo InFieldPathInfo, const TArray<URemoteControlBinding*>& InBindings);`
- L164 _public prototype_ `virtual uint32 GetUnderlyingEntityIdentifier() const override;`
- L165 _public prototype_ `virtual UClass* GetSupportedBindingClass() const override;`
- L166 _public prototype_ `virtual bool IsBound() const override;`
- L171 _public prototype_ `virtual bool SupportsMasking() const override;` — `UE_DEPRECATED(5.6, "SupportsMasking is deprecated. Use per-protocol-binding masking instead.")`
- L179 _public prototype_ `virtual bool CheckIsBoundToPropertyPath(const FString& InPropertyPath) const;` — Check whether given property path is bound to the property @param InPropertyPath Given Property Path return true if the property bound to given path
- L186 _public prototype_ `virtual bool CheckIsBoundToString(const FString& InPath) const;` — Check whether given property string is bound to the property @param InPathString Given Property String, this is the path without duplicates return true if the property bound to given path
- L193 _public prototype_ `virtual bool ContainsBoundObjects(TArray<UObject*> InObjects) const;` — Check whether any of the given objects are bound to this property @param InObjects Objects to check return true if at least one object is bound to the property
- L199 _public function_ `virtual void PostLoad()` — Called on Post Load on Owner UObject. Useful to initialize specific functionality of the inherit property classes
- L206 _public function_ `virtual void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InEvent)` — Should be called when property changed on bound object @param InObject Edited object @param InEvent  Change Event
- L213 _public prototype_ `FProperty* GetProperty() const;` — Get the underlying property. @return The exposed property or nullptr if it couldn't be resolved. @note This field's binding must be valid to get the property.
- L220 _public prototype_ `void* GetFieldContainerAddress() const;` — Get the container address. @return The container address of the value exposed by this field or nullptr if it couldn't be resolved. @note This field's binding must be valid to get the container address.
- L226 _public prototype_ `TSharedPtr<IRemoteControlPropertyHandle> GetPropertyHandle() const;` — Get the property handle with ability set and get property value directly. @return The property handle for exposed property.
- L231 _public prototype_ `void EnableEditCondition();` — Enable the edit condition for the underlying property on the owner objects.
- L234 _public prototype_ `bool IsEditableInPackaged(FString* OutError = nullptr) const;` — Returns whether the property is editable in a packaged build.
- L237 _public prototype_ `bool IsEditableInEditor(FString* OutError = nullptr) const;` — Returns whether the property is editable in the Editor.
- L240 _public prototype_ `bool IsEditable(FString* OutError = nullptr) const;` — Returns whether the property is editable, will check for editor or packaged automatically
- L242 _public prototype_ `bool Serialize(FArchive& Ar);`
- L243 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L247 _public member_ `static FName MetadataKey_Min;` — Key for the metadata's Min entry.
- L249 _public member_ `static FName MetadataKey_Max;` — Key for the metadata's Max entry.
- L253 _private prototype_ `void InitializeMetadata();` — Assign the default metadata for this exposed property. (ie. Min, Max...)
- L258 _private member_ `bool bIsEditableInPackaged = false;` — `UPROPERTY()` — Whether the property is blueprint read only.
- L263 _private member_ `FRCFieldPathInfo CachedEditConditionPath;` — Cached edit condition path used to enable the exposed property's edit condition.

#### struct `FRemoteControlFunction`  
`struct FRemoteControlFunction : public FRemoteControlField`  
_L272-346_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRemoteControlField`
- desc: Represents a function exposed to remote control.
- L276 _public prototype_ `FRemoteControlFunction() = default;`
- L279 _public prototype_ `FRemoteControlFunction(FName InLabel, FRCFieldPathInfo FieldPathInfo, UFunction* InFunction);` — `UE_DEPRECATED(4.27, "This constructor is deprecated. Use the other constructor.")`
- L281 _public prototype_ `FRemoteControlFunction(URemoteControlPreset* InPreset, FName InLabel, FRCFieldPathInfo InFieldPathInfo, UFunction* InFunction, const TArray<URemoteControlBinding*>& InBindings);`
- L284 _public prototype_ `virtual uint32 GetUnderlyingEntityIdentifier() const override;`
- L285 _public prototype_ `virtual UClass* GetSupportedBindingClass() const override;`
- L286 _public prototype_ `virtual bool IsBound() const override;`
- L290 _public function_ `bool IsCallableInPackaged() const` — Returns whether the function is callable in a packaged build.
- L293 _public prototype_ `UFunction* GetFunction() const;` — Returns the underlying exposed function.
- L300 _public prototype_ `void RegenerateArguments();` — Recreates the function arguments but tries to preserve old values when possible. Useful for updating function arguments after a blueprint recompile.
- L304 _public prototype_ `bool Serialize(FArchive& Ar);`
- L305 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L313 _public member_ `mutable TObjectPtr<UFunction> Function_DEPRECATED = nullptr;` — `UPROPERTY()`
- L319 _public member_ `TSharedPtr<class FStructOnScope> FunctionArguments;` — The function arguments.
- L323 _private prototype_ `void AssignDefaultFunctionArguments();` — Parse function metadata to get the function's default parameters
- L327 _private prototype_ `static uint32 HashFunctionArguments(UFunction* InFunction);` — Hash function arguments using their type and size.
- L333 _private member_ `bool bIsCallableInPackaged = false;` — `UPROPERTY()` — Whether the function is callable in a packaged build.
- L337 _private member_ `FSoftObjectPath FunctionPath;` — `UPROPERTY()` — The exposed function.
- L340 _private member_ `mutable TWeakObjectPtr<UFunction> CachedFunction;` — Cached resolved underlying function used to avoid doing a findobject while serializing.
- L344 _private member_ `uint32 CachedFunctionArgsHash = 0;` — Hash of the underlying function arguments used to check if it has changed after a recompile.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRemoteControlFunction> : public TStructOpsTypeTraitsBase2<FRemoteControlFunction>`  
_L348-355_
- inherits: `TStructOpsTypeTraitsBase2<FRemoteControlFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L351-354_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRemoteControlProperty> : public TStructOpsTypeTraitsBase2<FRemoteControlProperty>`  
_L357-364_
- inherits: `TStructOpsTypeTraitsBase2<FRemoteControlProperty>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L360-363_

#### Free symbols / members of external scopes

- L352 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon5b946f910103`)
- L353 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon5b946f910103`)
- L361 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon5b946f910203`)
- L362 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon5b946f910203`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlFieldMetadata.h` (Public)


#### struct `FRCFieldMetadata`  
`struct FRCFieldMetadata`  
_L10-16_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FRCFieldMetadata() = default;`
- L15 _public function_ `virtual ~FRCFieldMetadata()`

#### struct `FRCMetadata_byte`  
`struct FRCMetadata_byte : public FRCFieldMetadata`  
_L19-31_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L24 _public member_ `uint8 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L27 _public member_ `uint8 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L30 _public member_ `uint8 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_uint16`  
`struct FRCMetadata_uint16 : public FRCFieldMetadata`  
_L35-47_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L40 _public member_ `uint16 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L43 _public member_ `uint16 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L46 _public member_ `uint16 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_uint32`  
`struct FRCMetadata_uint32 : public FRCFieldMetadata`  
_L50-62_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L55 _public member_ `uint32 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L58 _public member_ `uint32 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L61 _public member_ `uint32 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_uint64`  
`struct FRCMetadata_uint64 : public FRCFieldMetadata`  
_L65-77_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L70 _public member_ `uint64 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L73 _public member_ `uint64 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L76 _public member_ `uint64 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_int8`  
`struct FRCMetadata_int8 : public FRCFieldMetadata`  
_L80-92_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L85 _public member_ `int8 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L88 _public member_ `int8 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L91 _public member_ `int8 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_int16`  
`struct FRCMetadata_int16 : public FRCFieldMetadata`  
_L95-107_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L100 _public member_ `int16 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L103 _public member_ `int16 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L106 _public member_ `int16 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_int32`  
`struct FRCMetadata_int32 : public FRCFieldMetadata`  
_L110-122_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L115 _public member_ `int32 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L118 _public member_ `int32 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L121 _public member_ `int32 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_int64`  
`struct FRCMetadata_int64 : public FRCFieldMetadata`  
_L125-137_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L130 _public member_ `int64 Min = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L133 _public member_ `int64 Max = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L136 _public member_ `int64 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_float`  
`struct FRCMetadata_float : public FRCFieldMetadata`  
_L140-152_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L145 _public member_ `float Min = 0.0f;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L148 _public member_ `float Max = 0.0f;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L151 _public member_ `float DefaultValue = 0.0f;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_double`  
`struct FRCMetadata_double : public FRCFieldMetadata`  
_L155-167_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L160 _public member_ `double Min = 0.0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L163 _public member_ `double Max = 0.0;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L166 _public member_ `double DefaultValue = 0.0;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_FString`  
`struct FRCMetadata_FString : public FRCFieldMetadata`  
_L170-176_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L175 _public member_ `FString DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_FName`  
`struct FRCMetadata_FName : public FRCFieldMetadata`  
_L179-185_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L184 _public member_ `FName DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_UObject`  
`struct FRCMetadata_UObject : public FRCFieldMetadata`  
_L188-194_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L193 _public member_ `TSoftObjectPtr<class UObject> DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_UClass`  
`struct FRCMetadata_UClass : public FRCFieldMetadata`  
_L197-203_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L202 _public member_ `TSoftClassPtr<UClass> DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_UScriptStruct`  
`struct FRCMetadata_UScriptStruct : public FRCFieldMetadata`  
_L206-212_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L211 _public member_ `TSoftObjectPtr<class UScriptStruct> DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_bool`  
`struct FRCMetadata_bool : public FRCFieldMetadata`  
_L215-221_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L220 _public member_ `bool DefaultValue = false;` — `UPROPERTY(EditAnywhere, Category=Default)`

#### struct `FRCMetadata_FVector`  
`struct FRCMetadata_FVector : public FRCFieldMetadata`  
_L224-236_
- reflection: `USTRUCT()`
- inherits: `FRCFieldMetadata`
- L229 _public member_ `FVector DefaultValue = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L232 _public member_ `FVector MinimumValue = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Default)`
- L235 _public member_ `FVector MaximumValue = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Default)`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlFieldPath.h` (Public)


#### struct `FRCFieldResolvedData`  
`struct FRCFieldResolvedData`  
_L14-35_
- desc: Small container for the resolved data of a remote control field segment
- L17 _public member_ `UStruct* Struct = nullptr;` — Type of that segment owner
- L20 _public member_ `void* ContainerAddress = nullptr;` — Container address of this segment
- L23 _public member_ `FProperty* Field = nullptr;` — Resolved field for this segment
- L26 _public member_ `int32 MapIndex = INDEX_NONE;` — Index resolved from the key of the segment.
- L29 _public function_ `bool IsValid() const` — Returns validity of the resolved data

#### struct `FRCFieldPathSegment`  
`struct FRCFieldPathSegment`  
_L39-95_
- reflection: `USTRUCT()`
- desc: RemoteControl Path segment holding a property layer
- L44 _public prototype_ `FRCFieldPathSegment() = default;`
- L47 _public prototype_ `FRCFieldPathSegment(FStringView SegmentName);` — Builds a segment from a name.
- L50 _public prototype_ `bool IsResolved() const;` — Returns true if a Field was found for a given owner
- L58 _public prototype_ `FString ToString(bool bDuplicateContainer = false) const;` — Converts this segment to a string FieldName, FieldName[Index] If bDuplicateContainer is asked, format will be different if its indexed FieldName.FieldName[Index]  -> This is to bridge for PathToProperty
- L64 _private prototype_ `void ClearResolvedData();` — Reset resolved pointers
- L70 _public member_ `FName Name;` — `UPROPERTY()` — Name of the segment
- L74 _public member_ `int32 ArrayIndex = INDEX_NONE;` — `UPROPERTY()` — Container index if any.
- L84 _public member_ `FString ValuePropertyName;` — `UPROPERTY()` — Value property name, in case a map is being indexed. ie. The path Var.Var_Value[0] will populate ValuePropertyName with "Var" This is needed because sometimes the value's property name will differ from the name before. For example a map property named Test_1 will generate the following path: Test_1.Test_Value[0]
- L91 _public member_ `FString MapKey;` — `UPROPERTY()` — Holds the key in case of a path containing an indexed map. ie. Field path MapProp["mykey"] will fill MapKey with "mykey"
- L94 _public member_ `FRCFieldResolvedData ResolvedData;` — Resolved Data of the segment

#### struct `FRCFieldPathInfo`  
`struct FRCFieldPathInfo`  
_L124-229_
- reflection: `USTRUCT()`
- desc: Holds a path from a UObject to a field. Has facilities to resolve for a given owner. Example Usage Create a path to relative location's x value, then resolve it on an static mesh component. FRCFieldPathInfo Path("RelativeLocation.X")); bool bResolved = Path.Resolve(MyStaticMeshComponent); if (bResolved) { FRCFieldResolvedData Data = Path.GetResolvedData(); // Data.ContainerAddress corresponds to &MyStaticMeshComponent.RelativeLocation // Data.Field corresponds to FFloatProperty (X) // Data.Struct corresponds to FVector } Other example paths: "MyStructProperty.NestedArrayProperty[3]" "RelativeLocation" "RelativeLocation.X" Supports array/set/map indexing. @Note Only String keys are currently supported for map key indexing. ie. MyStructProperty.MyStringToVectorMap["MyKey"].X Be aware that MyStringToVectorMap[2] will not correspond to the key 2 in the map, but to the index 2 of the map. This behaviour is intended to match PropertyHandle's GeneratePathToProperty method.
- L129 _public prototype_ `FRCFieldPathInfo() = default;`
- L137 _public prototype_ `FRCFieldPathInfo(const FString& PathInfo, bool bSkipDuplicates = false);` — Builds a path info from a string of format with '.' delimiters Optionally can reduce duplicates when dealing with containers If true -> Struct.ArrayName.ArrayName[2].Member will collapse to Struct.ArrayName[2].Member This is when being used with PathToProperty
- L142 _public prototype_ `FRCFieldPathInfo(FProperty* Property);` — Builds a path info from a property.
- L144 _public function_ `bool operator == (const FRCFieldPathInfo& Other) const`
- L149 _public function_ `bool operator != (const FRCFieldPathInfo& Other) const`
- L156 _public prototype_ `bool Resolve(UObject* Owner);` — Go through each segment and finds the property associated + container address for a given UObject owner
- L159 _public prototype_ `bool IsResolved() const;` — Returns true if last segment was resolved
- L162 _public prototype_ `bool IsEqual(FStringView OtherPath) const;` — Returns true if the hash of the string corresponds to the string we were built with
- L165 _public prototype_ `bool IsEqual(const FRCFieldPathInfo& OtherPath) const;` — Returns true if hash of both PathInfo matches
- L172 _public prototype_ `FString ToString(int32 EndSegment = INDEX_NONE) const;` — Converts this PathInfo to a string Walks the full path by default If EndSegment is not none, will stop at the desired segment
- L179 _public prototype_ `FString ToPathPropertyString(int32 EndSegment = INDEX_NONE) const;` — Converts this PathInfo to a string of PathToProperty format Struct.ArrayName.ArrayName[Index] If EndSegment is not none, will stop at the desired segment
- L182 _public function_ `int32 GetSegmentCount() const` — Returns the number of segment in this path
- L185 _public prototype_ `const FRCFieldPathSegment& GetFieldSegment(int32 Index) const;` — Gets a segment from this path
- L191 _public prototype_ `FRCFieldResolvedData GetResolvedData() const;` — Returns the resolved data of the last segment If last segment is not resolved, data won't be valid
- L194 _public prototype_ `FName GetFieldName() const;` — Returns last segment's name
- L197 _public prototype_ `FPropertyChangedEvent ToPropertyChangedEvent(EPropertyChangeType::Type InChangeType = EPropertyChangeType::Unspecified) const;` — Builds a property change event from all the segments
- L200 _public prototype_ `void ToEditPropertyChain(FEditPropertyChain& OutPropertyChain) const;` — Builds an EditPropertyChain from the segments
- L204 _public prototype_ `TSharedRef<FPropertyPath> ToPropertyPath() const;` — Converts this RCPath to a property path.
- L215 _private prototype_ `void Initialize(const FString& PathInfo, bool bCleanDuplicates);` — Initialize from a string of format with '.' delimiters Optionally can reduce duplicates when dealing with containers If true -> Struct.ArrayName.ArrayName[2].Member will collapse to Struct.ArrayName[2].Member This is when being used with PathToProperty
- L218 _private prototype_ `bool ResolveInternalRecursive(UStruct* OwnerType, void* ContainerAddress, int32 SegmentIndex);` — Recursively resolves all segment until the final one
- L224 _public member_ `TArray<FRCFieldPathSegment> Segments;` — `UPROPERTY()` — List of segments to point to a given field
- L228 _public member_ `uint32 PathHash = 0;` — `UPROPERTY()` — Hash created from the string we were built from to quickly compare to paths

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlFunctionLibrary.h` (Public)


#### struct `FRemoteControlOptionalExposeArgs`  
`struct FRemoteControlOptionalExposeArgs`  
_L14-30_
- reflection: `USTRUCT(Blueprintable)`
- L22 _public member_ `FString DisplayName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RemoteControlPreset")` — The display name of the exposed entity in the panel.
- L29 _public member_ `FString GroupName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RemoteControlPreset")` — The name of the group to expose the entity in. If it does not exist, a group with that name will be created.

#### struct `FColorWheelColorBase`  
`struct FColorWheelColorBase`  
_L34-49_
- reflection: `USTRUCT(Blueprintable)`
- desc: Base data for a color represented as its position on a color wheel.
- L42 _public member_ `FVector2D Position = FVector2D::ZeroVector;` — `UPROPERTY()` — The position on the unit circle. Magnitude should be in range [0, 1].
- L48 _public member_ `double Value = 0.0;` — `UPROPERTY()` — The color's value component (as in HSV).

#### struct `FColorWheelColor`  
`struct FColorWheelColor : public FColorWheelColorBase`  
_L53-62_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FColorWheelColorBase`
- desc: A color as represented by a position on a color wheel.
- L61 _public member_ `double Alpha = 0.0;` — `UPROPERTY()` — The color's alpha component.

#### struct `FColorGradingWheelColor`  
`struct FColorGradingWheelColor : public FColorWheelColorBase`  
_L66-75_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FColorWheelColorBase`
- desc: A color value as represented by a position on a color grading wheel.
- L74 _public member_ `double Luminance = 0.0;` — `UPROPERTY()` — The color's luminance component, which is separate from the HSV color itself.

#### class `URemoteControlFunctionLibrary`  
`class URemoteControlFunctionLibrary : public UBlueprintFunctionLibrary`  
_L78-138_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L92 _public prototype_ `static bool ExposeProperty(URemoteControlPreset* Preset, UObject* SourceObject, const FString& Property, FRemoteControlOptionalExposeArgs Args);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlPreset")` — Expose a property in a remote control preset. @param Preset the preset to expose the property in. @param SourceObject the object that contains the property to expose. @param Property the name or path of the property to expose. @param Args optional arguments. @return Whether the operation was successful.
- L103 _public prototype_ `static bool ExposeFunction(URemoteControlPreset* Preset, UObject* SourceObject, const FString& Function, FRemoteControlOptionalExposeArgs Args);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlPreset")` — Expose a function in a remote control preset. @param Preset the preset to expose the property in. @param SourceObject the object that contains the property to expose. @param Function the name of the function to expose. @param Args optional arguments. @return Whether the operation was successful.
- L113 _public prototype_ `static bool ExposeActor(URemoteControlPreset* Preset, AActor* Actor, FRemoteControlOptionalExposeArgs Args);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlPreset")` — Expose an actor in a remote control preset. @param Preset the preset to expose the property in. @param Actor the actor to expose. @param Args optional arguments. @return Whether the operation was successful.
- L125 _public prototype_ `static bool ApplyColorWheelDelta(UObject* TargetObject, const FString& PropertyName, const FColorWheelColor& DeltaValue, const FColorWheelColor& ReferenceColor, bool bIsInteractive);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Color")` — Add/subtract from the value of an FLinearColor property using a delta value based on color wheel coordinates. @param TargetObject the object that contains the property to modify. @param PropertyName the name of the property to modify. @param DeltaValue the amount to change the color by. @param ReferenceColor if the color's current position on the wheel is ambiguous as calculated from RGB values (e.g. black), use this reference color's position instead. @param bIsInteractive if true, this is treated as an interactive change. If false, it will be treated as the final value set change. @return Whether the operation was successful.
- L137 _public prototype_ `static bool ApplyColorGradingWheelDelta(UObject* TargetObject, const FString& PropertyName, const FColorGradingWheelColor& DeltaValue, const FColorGradingWheelColor& ReferenceColor, bool bIsInteractive, float MinValue = 0.f, float MaxValue = 2.f);` — `UFUNCTION(BlueprintCallable, Category = "Remote Control Color")` — Add/subtract from the value of an FVector4 property interpreted as RGBV using a delta value based on color wheel coordinates. @param TargetObject the object that contains the property to modify. @param PropertyName the name of the property to modify. @param DeltaValue the amount to change the color by. @param ReferenceColor if the color's current position on the wheel is ambiguous as calculated from RGB values (e.g. black), use this reference color's position instead. @param bIsInteractive if true, this is treated as an interactive change. If false, it will be treated as the final value set change. @return Whether the operation was successful.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlInstanceMaterial.h` (Public)


#### struct `FRemoteControlInstanceMaterial`  
`struct FRemoteControlInstanceMaterial : public FRemoteControlProperty`  
_L20-61_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRemoteControlProperty`
- desc: Represents a material instance property that has been exposed to remote control.
- L25 _public prototype_ `FRemoteControlInstanceMaterial() = default;`
- L29 _public prototype_ `FRemoteControlInstanceMaterial(URemoteControlPreset* InPreset, FName InLabel, UDEditorParameterValue* InEditorParameterValue, const FRCFieldPathInfo& InOriginalFieldPathInfo, UObject* InInstance, const FRCFieldPathInfo& InFieldPath, const TArray<URemoteControlBinding*>& InBindings);`
- L38 _public prototype_ `virtual void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InEvent) override;`
- L40 _public prototype_ `virtual bool CheckIsBoundToPropertyPath(const FString& InPath) const override;`
- L41 _public prototype_ `virtual bool ContainsBoundObjects(TArray<UObject*> InObjects) const override;`
- L42 _public prototype_ `virtual void PostLoad() override;`
- L48 _public member_ `TObjectPtr<UClass> OriginalClass = nullptr;` — `UPROPERTY()` — Stores original binding class
- L52 _public member_ `FMaterialParameterInfo ParameterInfo;` — `UPROPERTY()` — Stores original material parameter info
- L56 _public member_ `FRCFieldPathInfo OriginalFieldPathInfo;` — `UPROPERTY()` — Store original property path
- L60 _public member_ `FSoftObjectPath InstancePath;` — `UPROPERTY()` — Store path to Material Instance

#### class `FRemoteControlInstanceMaterialFactory`  
`class FRemoteControlInstanceMaterialFactory : public IRemoteControlPropertyFactory`  
_L63-73_
- inherits: `IRemoteControlPropertyFactory`
- L66 _public prototype_ `static TSharedRef<IRemoteControlPropertyFactory> MakeInstance();`
- L69 _public prototype_ `virtual TSharedPtr<FRemoteControlProperty> CreateRemoteControlProperty(URemoteControlPreset* Preset, UObject* Object, FRCFieldPathInfo FieldPath, FRemoteControlPresetExposeArgs Args) override;`
- L70 _public prototype_ `virtual void PostSetObjectProperties(UObject* Object, bool bInSuccess) const override;`
- L71 _public prototype_ `virtual bool SupportExposedClass(UClass* Class) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlLogger.h` (Public)


#### enum `EVerbosityLevel`  
`enum class EVerbosityLevel`  
_L13-18_
- desc: Log verbosity level
- L15 _public enumerator_ `Log`
- L16 _public enumerator_ `Warning`
- L17 _public enumerator_ `Error`

#### class `FRemoteControlLogger`  
`class FRemoteControlLogger : public TSharedFromThis<FRemoteControlLogger>`  
_L24-79_
- inherits: `TSharedFromThis<FRemoteControlLogger>`
- desc: Remote control logger. Generated Log UI and collect logs from APIs and protocols
- L28 _public function_ `static FRemoteControlLogger& Get()` — Get singleton logger instance
- L39 _public typedef_ `using FLogCallback = TFunctionRef<FText(void)>;` — Callback for logging, it should return FText to log
- L41 _public prototype_ `FRemoteControlLogger();`
- L42 _public prototype_ `virtual ~FRemoteControlLogger() = default;`
- L51 _public prototype_ `void Log(const FName& InputType, FLogCallback InLogTextCallback, EVerbosityLevel Verbosity = EVerbosityLevel::Log);` — Log the message @param InputType Type of the log, protocol, api, webapi @param InLogTextCallback	Log callback which should return the Text to log @param Verbosity			Log level
- L57 _public prototype_ `void EnableLog(const bool bEnable);` — Enable/Disable the log for Remote Control @param bEnable enable flag
- L60 _public function_ `bool IsEnabled() const` — Return the current state of the log
- L63 _public prototype_ `void ClearLog() const;` — Removes all messages from log
- L67 _public function_ `TSharedPtr<IMessageLogListing> GetMessageLogListing() const` — Log listening interface
- L74 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;` — Log listening interface
- L78 _private member_ `bool bIsEnabled = false;` — Is the logger enabled

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlObjectVersion.h` (Public)


#### struct `FRemoteControlObjectVersion`  
`struct FRemoteControlObjectVersion`  
_L8-46_
- desc: Custom serialization version for changes to remote control objects
- L42 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L45 _private function_ `FRemoteControlObjectVersion()`

#### enum `FRemoteControlObjectVersion::Type`  
`enum Type`  
_L10-39_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 4.26
- L16 _public enumerator_ `RemovedComponentChain` — Properties can now be directly exposed on components
- L19 _public enumerator_ `ConvertRCFieldsToRCEntities` — RCProperties and RCFunctions now inherit from FRemoteControlEntity
- L22 _public enumerator_ `ConvertTargetsToBindings` — Converted FRemoteControlTarget to URemoteControlBinding, put RCFields in the expose registry.
- L25 _public enumerator_ `AddedRebindingFunctionality` — ExposedEntities can now be rebound.
- L28 _public enumerator_ `AddedFieldFlags` — Added property/function flags to RemoteControlField
- L31 _public enumerator_ `AddedPerPresetModifyOperationFlags` — Instead of the global 'Protocol Generates Transactions' setting, each preset can now specify its modify operation flags
- L34 _public enumerator_ `ChangedExposedEntitiesSetToAnOrderedTArray` — Change FRCEntityWrapper::ExposedEntities' Set to an Array to retain ordering across sessions
- L37 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L38 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlPreset.h` (Public)


#### struct `FRemoteControlPresetExposeArgs`  
`struct FRemoteControlPresetExposeArgs`  
_L40-51_
- desc: Arguments used to expose an entity (Actor, property, function, etc.)
- L42 _public prototype_ `FRemoteControlPresetExposeArgs();`
- L43 _public prototype_ `FRemoteControlPresetExposeArgs(FString Label, FGuid GroupId, bool bEnableEditCondition = true);`
- L46 _public member_ `FString Label;` — (Optional) The label to use for the new exposed entity.
- L48 _public member_ `FGuid GroupId;` — (Optional) The group in which to put the field.
- L50 _public member_ `bool bEnableEditCondition;` — Whether to automatically enable the edit condition for the exposed property.

#### struct `FRemoteControlPropertyIdArgs`  
`struct FRemoteControlPropertyIdArgs`  
_L54-85_
- desc: Arguments used to expose an entity (Actor, property, function, etc.)
- L56 _public prototype_ `FRemoteControlPropertyIdArgs() = default;`
- L58 _public function_ `bool IsValid() const`
- L66 _public member_ `FName PropertyId;` — PropertyId
- L69 _public member_ `FName SuperType;` — SuperType of the Property
- L72 _public member_ `FName SubType;` — SubType of the Property
- L75 _public member_ `TObjectPtr<UObject> SourceObject;` — (Optional) The source object to use for special cases.
- L78 _public member_ `UClass* SourceClass;` — (Optional) The class of the source object to use for special cases.
- L81 _public member_ `TObjectPtr<URCVirtualPropertySelfContainer> VirtualProperty;` — (Optional) The virtual property to use for all the cases.
- L84 _public member_ `TMap<FGuid, TObjectPtr<URCVirtualPropertySelfContainer>> RealProperties;` — Map with the Guid of the RCField and as its value the real PropContainer of the real property

#### struct `FRCCachedFieldData`  
`struct FRCCachedFieldData`  
_L91-102_
- reflection: `USTRUCT()`
- desc: Data cached for every exposed field.
- L97 _public member_ `FGuid LayoutGroupId;` — `UPROPERTY()` — The group the field is in.
- L101 _public member_ `FName OwnerObjectAlias;` — `UPROPERTY()` — The target that owns this field.

#### struct `FExposedProperty`  
`struct FExposedProperty`  
_L108-117_
- reflection: `UE_DEPRECATED(4.27, "FExposedProperty is deprecated. Please use FRemoteControlProperty::GetBoundObjects to access an exposed property's owner objects.")`
- desc: Holds an exposed property and owner objects.
- L110 _public function_ `bool IsValid() const`
- L115 _public member_ `FProperty* Property;`
- L116 _public member_ `TArray<UObject*> OwnerObjects;`

#### struct `FExposedFunction`  
`struct FExposedFunction`  
_L123-133_
- reflection: `UE_DEPRECATED(4.27, "FExposedFunction is deprecated. Please use FRemoteControlFunction::GetBoundObjects to access an exposed function's owner objects.")`
- desc: Holds an exposed function, its default parameters and owner objects.
- L125 _public function_ `bool IsValid() const`
- L130 _public member_ `UFunction* Function;`
- L131 _public member_ `TSharedPtr<class FStructOnScope> DefaultParameters;`
- L132 _public member_ `TArray<UObject*> OwnerObjects;`

#### struct `FRCPresetGuidRenewGuard`  
`struct FRCPresetGuidRenewGuard`  
_L138-147_
- desc: Temporarily prevent Remote Control Presets from renewing it's guids during duplicate operation.
- L140 _public prototype_ `FRCPresetGuidRenewGuard();`
- L141 _public prototype_ `~FRCPresetGuidRenewGuard();`
- L143 _public prototype_ `static bool IsAllowingPresetGuidRenewal();`
- L146 _private member_ `bool bPreviousValue;`

#### struct `FRemoteControlPresetGroup`  
`struct FRemoteControlPresetGroup`  
_L153-207_
- reflection: `USTRUCT()`
- desc: Represents a group of field and offers operations to operate on the fields inside of that group.
- L157 _public function_ `FRemoteControlPresetGroup() :TagColor(ForceInit)`
- L161 _public function_ `FRemoteControlPresetGroup(FName InName, FGuid InId) : Name(InName) , Id(MoveTemp(InId)) , TagColor(MakeSimilarSaturatedColor())`
- L168 _public prototype_ `const TArray<FGuid>& GetFields() const;` — Get the fields under this group.
- L171 _public prototype_ `TArray<FGuid>& AccessFields();` — Get the fields under this group (Non-const)
- L183 _private function_ `static FLinearColor MakeSimilarSaturatedColor(float InSaturationLevel = 0.5f)` — Makes a random but similar saturated color.
- L193 _public member_ `FName Name;` — `UPROPERTY()` — Name of this group.
- L197 _public member_ `FGuid Id;` — `UPROPERTY()` — This group's ID.
- L201 _public member_ `FLinearColor TagColor;` — `UPROPERTY()` — Color Tag for this group.
- L206 _private member_ `TArray<FGuid> Fields;` — `UPROPERTY()` — The list of exposed fields under this group.

#### struct `FRemoteControlPresetLayout`  
`struct FRemoteControlPresetLayout`  
_L211-360_
- reflection: `USTRUCT()`
- desc: Layout that holds groups of fields.
- L224 _public prototype_ `FRemoteControlPresetLayout() = default;`
- L225 _public prototype_ `FRemoteControlPresetLayout(URemoteControlPreset* OwnerPreset);`
- L228 _public prototype_ `FRemoteControlPresetGroup& GetDefaultGroup();` — Get or create the default group.
- L230 _public function_ `TArray<FGuid>& GetDefaultGroupOrder()` — Return the DefaultGroupOrder
- L232 _public function_ `void SetDefaultGroupOrder(const TArray<FGuid>& InNewDefaultGroupOrder)` — Set the All group order
- L234 _public prototype_ `bool IsDefaultGroup(FGuid GroupId) const;` — Returns true when the given group id is a default one.
- L237 _public prototype_ `FLinearColor GetTagColor(FGuid GroupId);` — Returns the tag color of the given group id.
- L244 _public prototype_ `FRemoteControlPresetGroup* GetGroup(FGuid GroupId);` — Get a group by searching by ID. @param GroupId the id to use. @return A pointer to the found group or nullptr.
- L252 _public prototype_ `FRemoteControlPresetGroup* GetGroupByName(FName GroupName);` — Get a group by searching by name. @param GroupName the name to use. @return A pointer to the found group or nullptr.
- L256 _public prototype_ `FRemoteControlPresetGroup& CreateGroup(FName GroupName, FGuid GroupId);` — `UE_DEPRECATED(4.27, "This function was deprecated, use the overload that doesn't accept a group id.")` — Create a group by giving it a name and ID
- L259 _public prototype_ `FRemoteControlPresetGroup& CreateGroup(FName GroupName = NAME_None);` — Create a group in the layout with a given name.
- L267 _public prototype_ `FRemoteControlPresetGroup* FindGroupFromField(FGuid FieldId);` — Search for a group that contains a certain field. @param FieldId the field to search a group for. @return A pointer to the found group or nullptr.
- L270 _public prototype_ `void SwapGroups(FGuid OriginGroupId, FGuid TargetGroupId);` — Swap two groups.
- L273 _public prototype_ `void SwapFields(const FFieldSwapArgs& InFieldSwapArgs);` — Swap fields across groups or in the same one.
- L276 _public prototype_ `void SwapFieldsDefaultGroup(const FFieldSwapArgs& FieldSwapArgs, const FGuid InFieldRealGroup, TArray<FGuid> InEntities);` — Swap fields across groups or in the same one for the default group.
- L279 _public prototype_ `void DeleteGroup(FGuid GroupId);` — Delete a group from the layout.
- L282 _public prototype_ `void RenameGroup(FGuid GroupId, FName NewGroupName);` — Rename a group in the layout.
- L285 _public prototype_ `const TArray<FRemoteControlPresetGroup>& GetGroups() const;` — Get this layout's groups.
- L291 _public prototype_ `TArray<FRemoteControlPresetGroup>& AccessGroups();` — Non-Const getter for this layout's groups. @Note Use carefully, as adding/removing groups should be done using their respective methods.
- L294 _public prototype_ `void AddField(FGuid GroupId, FGuid FieldId);` — Append a field to the group's field list.
- L297 _public prototype_ `void InsertFieldAt(FGuid GroupId, FGuid FieldId, int32 Index);` — Insert a field in the group.
- L300 _public prototype_ `void RemoveField(FGuid GroupId, FGuid FieldId);` — Remove a field using the field's name.
- L303 _public prototype_ `void RemoveFieldAt(FGuid GroupId, int32 Index);` — Remove a field at a provided index.
- L306 _public prototype_ `URemoteControlPreset* GetOwner();` — Get the preset that owns this layout.
- L312 _public prototype_ `void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap);` — @brief Called internally when entity Ids are renewed. @param InEntityIdMap Map of old Id to new Id.
- L315 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupAdded, const FRemoteControlPresetGroup& );` — Layout operation delegates
- L316 _public function_ `FOnGroupAdded& OnGroupAdded()`
- L318 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupDeleted, FRemoteControlPresetGroup );`
- L319 _public function_ `FOnGroupDeleted& OnGroupDeleted()`
- L321 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupOrderChanged, const TArray<FGuid>& );`
- L322 _public function_ `FOnGroupOrderChanged& OnGroupOrderChanged()`
- L324 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGroupRenamed, const FGuid& , FName );`
- L325 _public function_ `FOnGroupRenamed& OnGroupRenamed()`
- L327 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFieldAdded, const FGuid& , const FGuid& , int32 );`
- L328 _public function_ `FOnFieldAdded& OnFieldAdded()`
- L330 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFieldDeleted, const FGuid& , const FGuid& , int32 );`
- L331 _public function_ `FOnFieldDeleted& OnFieldDeleted()`
- L333 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFieldOrderChanged, const FGuid& , const TArray<FGuid>& );`
- L334 _public function_ `FOnFieldOrderChanged& OnFieldOrderChanged()`
- L338 _private prototype_ `FRemoteControlPresetGroup& CreateGroupInternal(FName GroupName, FGuid GroupId);` — Create a group by providing a name and ID.
- L342 _private member_ `TArray<FGuid> DefaultGroupOrder;` — `UPROPERTY()` — Keep the ALL group order since its not saved in the normal workflow
- L346 _private member_ `TArray<FRemoteControlPresetGroup> Groups;` — `UPROPERTY()` — The list of groups under this layout.
- L350 _private member_ `TWeakObjectPtr<URemoteControlPreset> Owner = nullptr;` — `UPROPERTY()` — The preset that owns this layout.
- L353 _private member_ `FOnGroupAdded OnGroupAddedDelegate;` — Layout operation delegates
- L354 _private member_ `FOnGroupDeleted OnGroupDeletedDelegate;`
- L355 _private member_ `FOnGroupOrderChanged OnGroupOrderChangedDelegate;`
- L356 _private member_ `FOnGroupRenamed OnGroupRenamedDelegate;`
- L357 _private member_ `FOnFieldAdded OnFieldAddedDelegate;`
- L358 _private member_ `FOnFieldDeleted OnFieldDeletedDelegate;`
- L359 _private member_ `FOnFieldOrderChanged OnFieldOrderChangedDelegate;`

#### struct `FRemoteControlPresetLayout::FFieldSwapArgs`  
`struct FFieldSwapArgs`  
_L216-222_
- desc: Arguments for swapping fields across groups.
- L218 _public member_ `FGuid OriginGroupId;`
- L219 _public member_ `FGuid TargetGroupId;`
- L220 _public member_ `TArray<FGuid> DraggedFieldsIds;`
- L221 _public member_ `FGuid TargetFieldId;`

#### class `URemoteControlPreset`  
`class URemoteControlPreset : public UObject`  
_L366-1147_
- reflection: `UCLASS(BlueprintType, EditInlineNew)`
- inherits: `UObject`
- desc: Holds exposed functions and properties.
- L374 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostLoadRemoteControlPreset, URemoteControlPreset* );` — Callback for post remote control preset load, called by URemoteControlPreset::PostLoad function
- L375 _public member_ `static FOnPostLoadRemoteControlPreset OnPostLoadRemoteControlPreset;`
- L378 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostInitPropertiesRemoteControlPreset, URemoteControlPreset* );` — Callback for post init properties of remote control preset, called by URemoteControlPreset::PostInitProperties function
- L379 _public member_ `static FOnPostInitPropertiesRemoteControlPreset OnPostInitPropertiesRemoteControlPreset;`
- L381 _public prototype_ `URemoteControlPreset();`
- L384 _public prototype_ `virtual void PostInitProperties() override;`
- L385 _public prototype_ `virtual void PostLoad() override;`
- L386 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L387 _public prototype_ `virtual void BeginDestroy() override;`
- L390 _public prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);`
- L397 _public function_ `const FGuid& GetPresetId() const` — Get this preset's unique ID.
- L402 _public prototype_ `FName GetPresetName() const;` — Returns the FName that represents this asset or hosted preset.
- L410 _public prototype_ `TWeakPtr<FRemoteControlActor> ExposeActor(AActor* Actor, FRemoteControlPresetExposeArgs Args = FRemoteControlPresetExposeArgs());` — Expose an actor on this preset. @param Actor the actor to expose. @param Args The arguments used to expose the actor. @return The exposed actor.
- L418 _public prototype_ `TSharedPtr<FRemoteControlProperty> FindExposedProperty(UObject* InOuterObject, const FRCFieldPathInfo& InFieldPath) const;` — Gets a given object's property exposed property guid in this preset @param InOuterObject the object to check @param InFieldPath the path to the property @return The exposed property if found, nullptr otherwise
- L427 _public prototype_ `TWeakPtr<FRemoteControlProperty> ExposeProperty(UObject* Object, FRCFieldPathInfo FieldPath, FRemoteControlPresetExposeArgs Args = FRemoteControlPresetExposeArgs());` — Expose a property on this preset. @param Object the object that holds the property. @param FieldPath The name/path to the property. @param Args Optional arguments used to expose the property. @return The exposed property.
- L436 _public prototype_ `TWeakPtr<FRemoteControlFunction> ExposeFunction(UObject* Object, UFunction* Function, FRemoteControlPresetExposeArgs Args = FRemoteControlPresetExposeArgs());` — Expose a function on this preset. @param Object the object that holds the property. @param Function The function to expose. @param Args Optional arguments used to expose the property. @return The exposed function.
- L442 _public function_ `template <typename ExposableEntityType = FRemoteControlEntity> TArray<TWeakPtr<const ExposableEntityType>> GetExposedEntities() const` — Get the exposed entities of a certain type.
- L459 _public function_ `template <typename ExposableEntityType = FRemoteControlEntity> TArray<TWeakPtr<ExposableEntityType>> GetExposedEntities()` — Get the exposed entities of a certain type.
- L473 _public function_ `TArray<TWeakPtr<FRemoteControlEntity>> GetExposedEntities(UScriptStruct* EntityType)`
- L487 _public function_ `template <typename ExposableEntityType = FRemoteControlEntity> TWeakPtr<const ExposableEntityType> GetExposedEntity(const FGuid& ExposedEntityId) const` — Get a copy of an exposed entity on the preset. @param ExposedEntityId The id of the entity to get. @note ExposableEntityType must derive from FRemoteControlEntity.
- L499 _public function_ `template <typename ExposableEntityType = FRemoteControlEntity> TWeakPtr<ExposableEntityType> GetExposedEntity(const FGuid& ExposedEntityId)` — Get a pointer to an exposed entity on the preset. @param ExposedEntityId The id of the entity to get. @note ExposableEntityType must derive from FRemoteControlEntity.
- L506 _public prototype_ `const UScriptStruct* GetExposedEntityType(const FGuid& ExposedEntityId) const;` — Get the type of an exposed entity by querying with its id. (ie. FRemoteControlActor)
- L509 _public prototype_ `const TSet<TObjectPtr<UScriptStruct>>& GetExposedEntityTypes() const;` — Get all types of exposed entities currently exposed. (ie. FRemoteControlActor)
- L512 _public prototype_ `const bool HasEntities() const;` — Returns true when Exposed Entities is populated.
- L515 _public prototype_ `bool IsExposed(const FGuid& ExposedEntityId) const;` — Returns whether an entity is exposed on the preset.
- L524 _public prototype_ `FName RenameExposedEntity(const FGuid& ExposedEntityId, FName NewLabel);` — Change the label of an entity. @param ExposedEntityId the id of the entity to rename. @param NewLabel the new label to assign to the entity. @return The assigned label, which might be suffixed if the label already exists in the registry, or NAME_None if the entity was not found.
- L530 _public prototype_ `FGuid GetExposedEntityId(FName Label) const;` — Get the ID of an exposed entity using its label. @return an invalid guid if the exposed entity was not found.
- L536 _public prototype_ `TOptional<FRemoteControlField> GetField(FGuid FieldId) const;` — `UE_DEPRECATED(4.27, "Use GetExposedEntity<FRemoteControlField> instead.")` — Get a field ptr using it's id.
- L542 _public prototype_ `TOptional<FRemoteControlFunction> GetFunction(FName FunctionLabel) const;` — `UE_DEPRECATED(4.27, "Use GetExposedEntity<FRemoteControlFunction> instead.")` — Get an exposed function using its label.
- L548 _public prototype_ `TOptional<FRemoteControlProperty> GetProperty(FName PropertyLabel) const;` — `UE_DEPRECATED(4.27, "Use GetExposedEntity<FRemoteControlProperty> instead.")` — Get an exposed property using its label.
- L554 _public prototype_ `TOptional<FRemoteControlFunction> GetFunction(FGuid FunctionId) const;` — `UE_DEPRECATED(4.27, "Use GetExposedEntity<FRemoteControlFunction> instead.")` — Get an exposed function using its id.
- L560 _public prototype_ `TOptional<FRemoteControlProperty> GetProperty(FGuid PropertyId) const;` — `UE_DEPRECATED(4.27, "Use GetExposedEntity<FRemoteControlProperty> instead.")` — Get an exposed property using its id.
- L568 _public prototype_ `void RenameField(FName OldFieldLabel, FName NewFieldLabel);` — `UE_DEPRECATED(4.27, "Use RenameExposedEntity instead.")` — Rename a field. @param OldFieldLabel the target field's label. @param NewFieldLabel the field's new label.
- L578 _public prototype_ `TOptional<FExposedProperty> ResolveExposedProperty(FName PropertyLabel) const;` — `UE_DEPRECATED(4.27, "Use FRemoteControlProperty::GetProperty and FRemoteControlProperty::ResolveFieldOwners instead.")` — Resolve a remote controlled property to its FProperty and owner objects. @param Alias the target's alias that contains the remote controlled property. @param PropertyLabel the label of the remote controlled property. @return The resolved exposed property if found.
- L589 _public prototype_ `TOptional<FExposedFunction> ResolveExposedFunction(FName FunctionLabel) const;` — `UE_DEPRECATED(4.27, "Use FRemoteControlFunction::ResolveFieldOwners instead.")` — Resolve a remote controlled function to its UFunction and owner objects. @param Alias the target's alias that contains the remote controlled function. @param FunctionLabel the label of the remote controlled function. @return The resolved exposed function if found.
- L596 _public prototype_ `void Unexpose(FName EntityLabel);` — Unexpose an entity from the preset. @param EntityLabel The label of the entity to unexpose.
- L602 _public prototype_ `void Unexpose(const FGuid& EntityId);` — Unexpose an entity from the preset. @param EntityId the entity's id.
- L605 _public prototype_ `void CacheLayoutData();` — Cache this preset's layout data.
- L608 _public prototype_ `void CacheControllersLabels() const;` — Cache this preset's controllers labels.
- L612 _public prototype_ `TArray<UObject*> ResolvedBoundObjects(FName FieldLabel);` — `UE_DEPRECATED(4.27, "ResolvedBoundObjects is deprecated, you can now resolve bound objects using FRemoteControlEntity.")` — Resolves exposed property/function bounded objects
- L617 _public prototype_ `void RebindUnboundEntities();` — Attempt to rebind all currently unbound properties.
- L622 _public prototype_ `void RebindAllEntitiesUnderSameActor(const FGuid& EntityId, AActor* NewActor, bool bUseRebindingContext = true);` — Given a RC Entity, rebind all entities with the same owner to a new actor.
- L627 _public prototype_ `void RenewEntityIds();` — Renews all exposed entity guids. Necessary when duplicating.
- L632 _public prototype_ `void RenewControllerIds();` — Renews all controller guids. Necessary when duplicating.
- L640 _public prototype_ `FName SetControllerDisplayName(FGuid InControllerGuid, const FName& InNewName) const;` — Rename the given controller with the new name if the name is unique @param InControllerGuid Id of the controller to rename @param InNewName New name for the controller @return New name of the controller
- L642 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetEntityEvent, URemoteControlPreset* , const FGuid& );`
- L643 _public function_ `FOnPresetEntityEvent& OnEntityExposed()`
- L644 _public function_ `FOnPresetEntityEvent& OnEntityUnexposed()`
- L646 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetExposedPropertiesModified, URemoteControlPreset* , const TSet<FGuid>& );`
- L650 _public function_ `FOnPresetExposedPropertiesModified& OnExposedPropertiesModified()` — Delegate called with the list of exposed property that were modified in the last frame.
- L652 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetEntitiesUpdatedEvent, URemoteControlPreset* , const TSet<FGuid>& );`
- L656 _public function_ `FOnPresetEntitiesUpdatedEvent& OnEntitiesUpdated()` — Delegate called when the exposed entity wrapper itself is updated (ie. binding change, rename)
- L658 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntityRebind, const FGuid&) FOnEntityRebind& OnEntityRebind()`
- L661 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetPropertyExposed, URemoteControlPreset* , FName );`
- L663 _public function_ `FOnPresetPropertyExposed& OnPropertyExposed()` — `UE_DEPRECATED(4.27, "This delegate is deprecated, use OnEntityExposed instead.")`
- L665 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetPropertyUnexposed, URemoteControlPreset* , FName );`
- L667 _public function_ `FOnPresetPropertyUnexposed& OnPropertyUnexposed()` — `UE_DEPRECATED(4.27, "This delegate is deprecated, use OnEntityUnexposed instead.")`
- L669 _public typedef_ `using FGuidToGuidMap = TMap<FGuid, FGuid>;` — Workaround for delegate macro.
- L671 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyIdsRenewed, URemoteControlPreset* , const FGuidToGuidMap& );`
- L672 _public function_ `FOnPropertyIdsRenewed& OnPropertyIdsRenewed()`
- L674 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPresetFieldRenamed, URemoteControlPreset* , FName , FName );`
- L675 _public function_ `FOnPresetFieldRenamed& OnFieldRenamed()`
- L677 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetMetadataModified, URemoteControlPreset* );`
- L678 _public function_ `FOnPresetMetadataModified& OnMetadataModified()`
- L680 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnActorPropertyModified, URemoteControlPreset* , FRemoteControlActor& , UObject* , FProperty* );`
- L681 _public function_ `FOnActorPropertyModified& OnActorPropertyModified()`
- L683 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetLayoutModified, URemoteControlPreset* );`
- L684 _public function_ `FOnPresetLayoutModified& OnPresetLayoutModified()`
- L686 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControllerAdded, URemoteControlPreset* , const FName , const FGuid& );`
- L687 _public function_ `FOnControllerAdded& OnControllerAdded()`
- L689 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerRemoved, URemoteControlPreset* , const FGuid& );`
- L690 _public function_ `FOnControllerRemoved& OnControllerRemoved()`
- L692 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControllerRenamed, URemoteControlPreset* , const FName , const FName );`
- L693 _public function_ `FOnControllerRenamed& OnControllerRenamed()`
- L695 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerIdsRenewed, URemoteControlPreset* , const FGuidToGuidMap& );`
- L696 _public function_ `FOnControllerIdsRenewed& OnControllerIdsRenewed()`
- L698 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerModified, URemoteControlPreset* , const TSet<FGuid>& );`
- L699 _public function_ `FOnControllerModified& OnControllerModified()`
- L702 _public prototype_ `void NotifyExposedPropertyChanged(FName PropertyLabel);` — `UE_DEPRECATED(4.27, "This function is deprecated.")`
- L704 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L713 _public prototype_ `FName GetEntityName(const FName InDesiredName, UObject* InObject, const FRCFieldPathInfo& InFieldPath) const;` — Get entity name from given Desired or UObject + Field Path @param InDesiredName		Given name, it might be none @param InObject			Bound object input @param InFieldPath		Bound field path @return Computing name of the entity
- L716 _public prototype_ `FName GenerateUniqueLabel(const FName InDesiredName) const;` — Generate label from Registry
- L719 _public function_ `URCSignatureRegistry* GetSignatureRegistry() const` — Returns the preset's signature registry
- L727 _public member_ `FRemoteControlPresetLayout Layout;` — `UPROPERTY()` — The visual layout for this preset.
- L731 _public member_ `TMap<FString, FString> Metadata;` — `UPROPERTY()` — This preset's metadata.
- L735 _public member_ `TArray<TObjectPtr<URemoteControlBinding>> Bindings;` — `UPROPERTY(EditAnywhere, Category = "Remote Control Preset")` — This preset's list of objects that are exposed or that have exposed fields.
- L739 _public member_ `TArray<TObjectPtr<UObject>> UserData;` — `UPROPERTY()` — This preset's user data
- L743 _public member_ `TWeakObjectPtr<const UWorld> SelectedWorld = nullptr;` — Current selected world used only in the editor to let you switch world
- L751 _public prototype_ `URCVirtualPropertyBase* GetController(const FName InPropertyName) const;` — Fetches a controller by internal property name.
- L754 _public prototype_ `URCVirtualPropertyBase* GetController(const FGuid& InId) const;` — Fetches a controller by unique Id.
- L757 _public prototype_ `TArray<URCVirtualPropertyBase*> GetControllers() const;` — Fetches all controller
- L760 _public prototype_ `URCVirtualPropertyBase* GetControllerByDisplayName(const FName InDisplayName) const;` — Fetches a virtual property by specified name.
- L763 _public prototype_ `URCVirtualPropertyBase* GetControllerByFieldId(const FName InFieldId) const;` — Fetches the first found Controller matching the specified Field Id
- L766 _public prototype_ `URCVirtualPropertyBase* GetControllerByFieldId(const FName InFieldId, const EPropertyBagPropertyType InType) const;` — Fetches the first Controller matching the specified Field Id and ValueType
- L769 _public prototype_ `TArray<URCVirtualPropertyBase*> GetControllersByFieldId(const FName InFieldId) const;` — Fetches an array of all Controllers with the specified Field Id.
- L772 _public prototype_ `TArray<EPropertyBagPropertyType> GetControllersTypesByFieldId(const FName InFieldId) const;` — Fetches an array of all Controllers Types with the specified Field Id.
- L775 _public prototype_ `URCVirtualPropertyInContainer* AddController(TSubclassOf<URCVirtualPropertyInContainer> InPropertyClass, const EPropertyBagPropertyType InValueType, UObject* InValueTypeObject = nullptr, const FName InPropertyName = NAME_None);` — Adds a Virtual Property (Controller) to the Remote Control Preset
- L778 _public prototype_ `bool HasController(const URCVirtualPropertyBase* InController) const;` — Returns true if the preset contains this controller.
- L781 _public prototype_ `bool RemoveController(const FName& InPropertyName);` — Removes a given Virtual Property (by Name) from the Remote Control preset
- L784 _public prototype_ `URCVirtualPropertyInContainer* DuplicateController(URCVirtualPropertyInContainer* InVirtualProperty);` — Duplicates a given Virtual Property from the Remote Control preset
- L787 _public prototype_ `void ResetControllers();` — Removes all virtual properties held by this Remote Control preset
- L790 _public prototype_ `int32 GetNumControllers() const;` — Returns the number of Virtual Properties contained in this Remote Control preset
- L794 _public prototype_ `TSharedPtr<FStructOnScope> GetControllerContainerStructOnScope();` — Returns the Struct On Scope of the Controller Container (value ptr of the virtual properties)* Currently used by the UI class SRCControllerPanelList for user value entry via the RC Controllers panel
- L797 _public function_ `URCVirtualPropertyContainerBase* GetControllerContainer() const` — Returns the Property Bag Struct of this Container
- L803 _public prototype_ `void SetControllerContainer(URCVirtualPropertyContainerBase* InControllerContainer);` — Sets the Controller Container (holds all Virtual Properties)
- L806 _public function_ `bool IsControllerContainerValid()` — Checks whether the Controller Container (which holds all Virtual Properties) is currently valid
- L814 _public prototype_ `void OnNotifyPreChangeVirtualProperty(const FPropertyChangedEvent& PropertyChangedEvent);` — Called when a virtual property's value is being scrubbed by the user in the UI. This call is routed to the Controller for evaluating associated Logic & Behaviours
- L817 _public prototype_ `void OnModifyController(const FPropertyChangedEvent& PropertyChangedEvent);` — Called when a virtual property is modified. This call is routed to the Controller for evaluating associated Logic & Behaviours
- L820 _public prototype_ `FOnVirtualPropertyContainerModified& OnVirtualPropertyContainerModified() const;`
- L825 _private member_ `TObjectPtr<URCVirtualPropertyContainerBase> ControllerContainer;` — `UPROPERTY(Instanced)` — Holds virtual controllers properties, behaviours and actions
- L836 _private prototype_ `void OnExpose(const FExposeInfo& Info);`
- L837 _private prototype_ `void OnUnexpose(FGuid UnexposedFieldId);`
- L840 _private prototype_ `void CacheFieldLayoutData();`
- L843 _private prototype_ `void RegisterDelegates();`
- L844 _private prototype_ `void UnregisterDelegates();`
- L847 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& Event);`
- L848 _private prototype_ `void OnPreObjectPropertyChanged(UObject* Object, const class FEditPropertyChain& PropertyChain);`
- L849 _private prototype_ `void OnObjectTransacted(UObject* InObject, const FTransactionObjectEvent& InTransactionEvent);`
- L852 _private prototype_ `void FixAndCacheControllersLabels() const;` — Fix controllers labels for older presets.
- L856 _private prototype_ `void OnActorDeleted(AActor* Actor);`
- L857 _private prototype_ `void OnPieEvent(bool);`
- L858 _private prototype_ `void OnReplaceObjects(const TMap<UObject*, UObject*>& ReplacementObjectMap);`
- L859 _private prototype_ `void OnMapChange(uint32 );`
- L860 _private prototype_ `void OnBlueprintRecompiled(UBlueprint* Blueprint);`
- L863 _private prototype_ `void OnPackageReloaded(EPackageReloadPhase Phase, FPackageReloadedEvent* Event);` — Handles a package reloaded, used to detect a multi-user session being joined in order to update entities.
- L866 _private prototype_ `void CleanUpBindings();` — Remove deleted actors from bindings
- L870 _private prototype_ `void OnBeginFrame();`
- L871 _private prototype_ `void OnEndFrame();`
- L874 _private prototype_ `void OnMapLoadFinished(UWorld* LoadedWorld);` — Handles dynamic level change.
- L877 _private prototype_ `FRemoteControlField* GetFieldPtr(FGuid FieldId);` — Get a field ptr using it's id.
- L880 _private prototype_ ``
- L881 _private prototype_ `TSharedPtr<FRemoteControlEntity> FindEntityById(const FGuid& EntityId, const UScriptStruct* EntityType = FRemoteControlEntity::StaticStruct());`
- L882 _private prototype_ `TArray<TSharedPtr<FRemoteControlEntity>> GetEntities(UScriptStruct* EntityType);`
- L883 _private prototype_ `TArray<TSharedPtr<const FRemoteControlEntity>> GetEntities(UScriptStruct* EntityType) const;`
- L887 _public prototype_ `TSharedPtr<FRemoteControlEntity> Expose(FRemoteControlEntity&& Entity, UScriptStruct* EntityType, const FGuid& GroupId);` — Expose an entity in the registry.
- L893 _public prototype_ `void PerformChainReaction(const FRemoteControlPropertyIdArgs& InArgs) const;` — Calls to the PropertyIdRegistry PerformChainReaction to update the value(s) of the property(ies) that are bound to a PropertyIdAction. @param InArgs Argument used to update the property(ies) value.
- L899 _public prototype_ `void UpdateIdentifiedField(const TSharedRef<FRemoteControlField>& InFieldToIdentify) const;` — Calls to the PropertyIdRegistry UpdateIdentifiedField to updates a field from the set of identified fields. @param InFieldToIdentify the entity to identify.
- L902 _public prototype_ `URemoteControlBinding* FindOrAddBinding(const TSoftObjectPtr<UObject>& Object);` — Try to get a binding and creates a new one if it doesn't exist.
- L908 _public function_ `TObjectPtr<URemoteControlPropertyIdRegistry> GetPropertyIdRegistry() const` — Get the PropertyIdRegistry. @return The PropertyIdRegistry of this Preset.
- L911 _public function_ `void SetModifyOperationFlagsForProtocols(ERCModifyOperationFlags InOperationFlags)` — Sets how this preset modifies properties when changed by protocols
- L914 _public function_ `ERCModifyOperationFlags GetModifyOperationFlagsForProtocols() const` — Returns how this preset modifies properties when changed by protocols
- L917 _public prototype_ `void UpdateEntityUsage();` — Updates the usage of entities by controllers. Specifically the number of controlling behaviors.
- L920 _public function_ `const TMap<FGuid, int32>& GetEntityUsage() const` — Returns a map of the number of times exposed entities are used by behaviors.
- L926 _public prototype_ `bool IsEntityBound(const FGuid& InEntityGuid) const;` — Returns true if an entity is bound to a controller/behavior.
- L929 _public prototype_ `int32 GetEntityBoundCount(const FGuid& InEntityGuid) const;` — Returns the number of behaviors an entity is bound to.
- L932 _public prototype_ `int32 GetNextControllerDisplayIndex() const;` — The display index to put it at the bottom of the list.
- L937 _private prototype_ `URemoteControlBinding* FindMatchingBinding(const URemoteControlBinding* InBinding, UObject* InObject);` — Find a binding that has the same boundobjectmap but that currently points to the object passed as argument.
- L940 _private prototype_ `void OnEntityModified(const FGuid& EntityId);` — Handler called upon an entity being modified.
- L943 _private prototype_ `void InitializeEntitiesMetadata();` — Initialize entities metadata based on the module's externally registered initializers.
- L946 _private prototype_ `void InitializeEntityMetadata(const TSharedPtr<FRemoteControlEntity>& Entity);` — Initialize an entity's metadata based on the module's externally registered initializers.
- L949 _private prototype_ `void InitializeEntityMetadata(URCVirtualPropertyBase* Controller);` — Initialize an controllers's metadata based on the module's externally registered initializers.
- L952 _private prototype_ `void RegisterEntityDelegates();` — Register delegates for all exposed entities.
- L955 _private prototype_ `void RegisterOnCompileEvent(const TSharedPtr<FRemoteControlFunction>& RCFunction);` — Register an event triggered when the exposed function's owner blueprint is compiled.
- L958 _private prototype_ `void CreatePropertyWatcher(const TSharedPtr<FRemoteControlProperty>& RCProperty);` — Create a property watcher that will trigger the property change delegate upon having a different value from the last frame.
- L961 _private prototype_ `bool PropertyShouldBeWatched(const TSharedPtr<FRemoteControlProperty>& RCProperty) const;` — Returns whether a given property should have a watcher that checks for property changes across frames.
- L964 _private prototype_ `void CreatePropertyWatchers();` — Create property watchers for exposed properties that need them.
- L967 _private prototype_ `void RemoveUnusedBindings();` — Remove bindings that do not have properties pointing to them.
- L970 _private prototype_ `void PostLoadProperties();` — Call post load function for exposed properties.
- L973 _private prototype_ `void HandleDisplayClusterConfigChange(UObject* DisplayClusterConfigData);` — Handle a change on a ndisplay config data, used to replace bindings.
- L978 _private member_ `FGuid PresetId;` — `UPROPERTY(AssetRegistrySearchable)` — Preset unique ID
- L982 _private member_ `ERCModifyOperationFlags ModifyOperationFlagsForProtocols = ERCModifyOperationFlags::SkipPropertyChangeEvents | ERCModifyOperationFlags::SkipTransactions;` — `UPROPERTY()` — Defines how this preset modifies properties when changed by protocols
- L986 _private member_ `TMap<FGuid, FRCCachedFieldData> FieldCache;` — `UPROPERTY(Transient)` — The cache for information about an exposed field.
- L990 _private member_ `TMap<FName, FGuid> NameToGuidMap;` — `UPROPERTY(Transient)` — Map of Field Name to GUID.
- L994 _private member_ `TObjectPtr<URemoteControlExposeRegistry> Registry = nullptr;` — `UPROPERTY(Instanced)` — Holds exposed entities on the preset.
- L998 _private member_ `TObjectPtr<URCSignatureRegistry> Signatures = nullptr;` — `UPROPERTY(Instanced)` — Holds all signatures on the preset.
- L1002 _private member_ `TObjectPtr<URemoteControlPropertyIdRegistry> PropertyIdRegistry = nullptr;` — `UPROPERTY(Transient)` — Holds identities of exposed entities on the preset.
- L1005 _private member_ `FOnPresetEntityEvent OnEntityExposedDelegate;` — Delegate triggered when an entity is exposed.
- L1007 _private member_ `FOnPresetEntityEvent OnEntityUnexposedDelegate;` — Delegate triggered when an entity is unexposed from the preset.
- L1009 _private member_ `FOnPresetEntitiesUpdatedEvent OnEntitiesUpdatedDelegate;` — Delegate triggered when entities are modified and may need to be re-resolved.
- L1011 _private member_ `FOnEntityRebind OnEntityRebindDelegate;` — Delegate triggered when an Entity is rebound
- L1013 _private member_ `FOnPresetExposedPropertiesModified OnPropertyChangedDelegate;` — Delegate triggered when an exposed property value has changed.
- L1015 _private member_ `FOnPresetPropertyExposed OnPropertyExposedDelegate;` — Delegate triggered when a new property has been exposed.
- L1017 _private member_ `FOnPresetPropertyUnexposed OnPropertyUnexposedDelegate;` — Delegate triggered when a property has been unexposed.
- L1019 _private member_ `FOnPropertyIdsRenewed OnPropertyIdsRenewedDelegate;` — Delegate triggered when the property guids are renewed.
- L1021 _private member_ `FOnPresetFieldRenamed OnPresetFieldRenamed;` — Delegate triggered when a field has been renamed.
- L1023 _private member_ `FOnPresetMetadataModified OnMetadataModifiedDelegate;` — Delegate triggered when the preset's metadata has been modified.
- L1025 _private member_ `FOnActorPropertyModified OnActorPropertyModifiedDelegate;` — Delegate triggered when an exposed actor's property is modified.
- L1027 _private member_ `FOnPresetLayoutModified OnPresetLayoutModifiedDelegate;` — Delegate triggered when the layout is modified.
- L1029 _private member_ `FOnControllerAdded OnControllerAddedDelegate;` — Delegate triggered when a controller is added
- L1031 _private member_ `FOnControllerRemoved OnControllerRemovedDelegate;` — Delegate triggered when a controller is removed
- L1033 _private member_ `FOnControllerRenamed OnControllerRenamedDelegate;` — Delegate triggered when a Controller is renamed
- L1035 _private member_ `FOnControllerIdsRenewed OnControllerIdsRenewedDelegate;` — Delegate triggered when a Controller guids are renewed.
- L1037 _private member_ `FOnControllerModified OnControllerModifiedDelegate;` — Delegate triggered when a Controller has been changed
- L1047 _private member_ `TMap<FGuid, FPreObjectsModifiedCache> PreObjectsModifiedCache;` — Caches object modifications during a frame.
- L1048 _private member_ `TMap<FGuid, FPreObjectsModifiedCache> PreObjectsModifiedActorCache;`
- L1058 _private member_ `TMap<FGuid, FPreMaterialModifiedCache> PreMaterialModifiedCache;` — Caches material modifications during a frame.
- L1061 _private member_ `TSet<FGuid> PerFrameModifiedProperties;` — Cache properties that were modified during a frame.
- L1064 _private member_ `TSet<FGuid> PerFrameUpdatedEntities;` — Cache entities updated during a frame.
- L1067 _private member_ `bool bOngoingRemoteModification = false;` — Whether there is an ongoing remote modification happening.
- L1070 _private member_ `bool bReentryGuard = false;` — Used for OnObjectPropertyChanged to avoid being called by itself.
- L1073 _private member_ `bool bPendingPostInitNotify = false;` — Whether OnPostInitPropertiesRemoteControlProperties delegate is pending broadcast because it wasn't broadcast in URemoteControlPreset::PostInitProperties()
- L1076 _private member_ `TMap<FGuid, int32> BoundEntityIds;` — Transient list of the currently bound entity ids and the number of times they are bound.
- L1079 _private member_ `TPimplPtr<FRemoteControlPresetRebindingManager> RebindingManager;` — Holds manager that handles rebinding unbound entities upon load or map change.
- L1105 _private member_ `TMap<FGuid, FRCPropertyWatcher> PropertyWatchers;` — Map of property watchers that should trigger the RC property change delegate upon change.
- L1108 _private member_ `int32 PropertyChangeWatchFrameCounter = 0;` — Frame counter for delaying property change checks.
- L1112 _public prototype_ `static UWorld* GetWorld(const URemoteControlPreset* Preset = nullptr, bool bAllowPIE = false);`
- L1113 _public prototype_ `UWorld* GetWorld(bool bAllowPIE = false) const;`
- L1114 _public prototype_ `UWorld* GetEmbeddedWorld() const;`
- L1117 _public prototype_ `bool IsEmbeddedPreset() const;` — Returns true if the preset is hosted within another asset.
- L1120 _public function_ `const TArray<FName>& GetDetailsTabIdentifierOverrides() const`
- L1121 _public function_ `void SetDetailsTabIdentifierOverrides(const TArray<FName>& NewOverrides)`
- L1128 _public member_ `FString NewControllerCategory;` — Transient value for the default category for new properties. Not automatically set by the preset. Used when adding controllers.
- L1133 _private member_ `TArray<FName> DetailsTabIdentifierOverrides;` — `UPROPERTY()`
- L1138 _private member_ `TSet<TWeakObjectPtr<UBlueprint>> BlueprintsWithRegisteredDelegates;` — List of blueprints for which we have registered events.
- L1141 _private member_ `TSet<URemoteControlBinding*> PerFrameBindingsToClean;` — List of bindings for which we need to remove stale object pointers.

#### struct `URemoteControlPreset::FExposeInfo`  
`struct FExposeInfo`  
_L828-833_
- desc: Holds information about an exposed field.
- L830 _public member_ `FName Alias;`
- L831 _public member_ `FGuid FieldId;`
- L832 _public member_ `FGuid LayoutGroupId;`

#### struct `URemoteControlPreset::FPreObjectsModifiedCache`  
`struct FPreObjectsModifiedCache`  
_L1039-1044_
- L1041 _public member_ `TArray<UObject*> Objects;`
- L1042 _public member_ `FProperty* Property;`
- L1043 _public member_ `FProperty* MemberProperty;`

#### struct `URemoteControlPreset::FPreMaterialModifiedCache`  
`struct FPreMaterialModifiedCache`  
_L1051-1055_
- desc: A struct representing a material object modified that is housed by a container (eg. array, set, map).
- L1053 _public member_ `int32 ArrayIndex;`
- L1054 _public member_ `bool bHadValue;`

#### struct `URemoteControlPreset::FRCPropertyWatcher`  
`struct FRCPropertyWatcher`  
_L1084-1103_
- desc: Property watcher that triggers a delegate when the watched property is modified.
- L1086 _public prototype_ `FRCPropertyWatcher(const TSharedPtr<FRemoteControlProperty>& InWatchedProperty, FSimpleDelegate&& InOnWatchedValueChanged);`
- L1089 _public prototype_ `void CheckForChange();` — Checks if the property value has changed since the last frame and updates the last frame value.
- L1093 _private prototype_ `TOptional<FRCFieldResolvedData> GetWatchedPropertyResolvedData() const;` — Optionally resolve the property path if possible.
- L1095 _private prototype_ `void SetLastFrameValue(const FRCFieldResolvedData& ResolvedData);` — Store the latest property value in LastFrameValue.
- L1098 _private member_ `FSimpleDelegate OnWatchedValueChanged;` — Delegate called when the watched property changes values.
- L1100 _private member_ `TWeakPtr<FRemoteControlProperty> WatchedProperty;` — Weak pointer to the remote control property.
- L1102 _private member_ `TArray<uint8> LastFrameValue;` — Latest property value as bytes.

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVirtualPropertyContainerModified);`
- L37 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVirtualPropertyContainerModified);`
- L173 _function_ `friend bool operator==(const FRemoteControlPresetGroup& LHS, const FRemoteControlPresetGroup& RHS)`
- L315 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupAdded, const FRemoteControlPresetGroup& );` — Layout operation delegates
- L318 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupDeleted, FRemoteControlPresetGroup );`
- L321 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGroupOrderChanged, const TArray<FGuid>& );`
- L324 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGroupRenamed, const FGuid& , FName );`
- L327 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFieldAdded, const FGuid& , const FGuid& , int32 );`
- L330 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnFieldDeleted, const FGuid& , const FGuid& , int32 );`
- L333 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFieldOrderChanged, const FGuid& , const TArray<FGuid>& );`
- L374 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostLoadRemoteControlPreset, URemoteControlPreset* );` — Callback for post remote control preset load, called by URemoteControlPreset::PostLoad function
- L378 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostInitPropertiesRemoteControlPreset, URemoteControlPreset* );` — Callback for post init properties of remote control preset, called by URemoteControlPreset::PostInitProperties function
- L449 _function_ `` (scope `URemoteControlPreset::GetExposedEntities`)
- L642 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetEntityEvent, URemoteControlPreset* , const FGuid& );`
- L646 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetExposedPropertiesModified, URemoteControlPreset* , const TSet<FGuid>& );`
- L652 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetEntitiesUpdatedEvent, URemoteControlPreset* , const TSet<FGuid>& );`
- L658 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntityRebind, const FGuid&) FOnEntityRebind& OnEntityRebind() { return OnEntityRebindDelegate; } DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetPropertyExposed, URemoteControlPreset* , FName );`
- L661 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetPropertyExposed, URemoteControlPreset* , FName );`
- L665 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPresetPropertyUnexposed, URemoteControlPreset* , FName );`
- L671 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPropertyIdsRenewed, URemoteControlPreset* , const FGuidToGuidMap& );`
- L674 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPresetFieldRenamed, URemoteControlPreset* , FName , FName );`
- L677 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetMetadataModified, URemoteControlPreset* );`
- L680 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnActorPropertyModified, URemoteControlPreset* , FRemoteControlActor& , UObject* , FProperty* );`
- L683 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetLayoutModified, URemoteControlPreset* );`
- L686 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControllerAdded, URemoteControlPreset* , const FName , const FGuid& );`
- L689 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerRemoved, URemoteControlPreset* , const FGuid& );`
- L692 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControllerRenamed, URemoteControlPreset* , const FName , const FName );`
- L695 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerIdsRenewed, URemoteControlPreset* , const FGuidToGuidMap& );`
- L698 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerModified, URemoteControlPreset* , const TSet<FGuid>& );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlPresetActor.h` (Public)


#### class `ARemoteControlPresetActor`  
`class ARemoteControlPresetActor : public AActor`  
_L14-28_
- reflection: `UCLASS(HideCategories = (Rendering, Physics, LOD, Activation, Input, Replication, Collision, Actor, Cooking))`
- inherits: `AActor`
- desc: Actor that wraps a remote control preset, allows linking a specific preset to a level.
- L19 _public prototype_ `ARemoteControlPresetActor();`
- L23 _public member_ `TObjectPtr<URemoteControlPreset> Preset;` — `UPROPERTY(EditAnywhere, Category="General")`
- L27 _private member_ `FDelegateHandle OnActorDeletedDelegateHandle;` — Delegate handle for actor deletion callback.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlPropertyIdRegistry.h` (Public)


#### struct `FRCPropertyIdWrapper`  
`struct FRCPropertyIdWrapper`  
_L26-97_
- reflection: `USTRUCT()`
- desc: Wrapper class used to serialize identities of exposable entities in a generic way.
- L30 _public prototype_ `FRCPropertyIdWrapper() = default;`
- L32 _public prototype_ `FRCPropertyIdWrapper(const TSharedRef<FRemoteControlProperty>& InRCProperty);`
- L37 _public prototype_ `const FGuid& GetEntityId() const;` — Get the type of the wrapped entity. @return Entity Id of this PropertyIdWrapper.
- L42 _public prototype_ `FName GetPropertyId() const;` — Get the type of the wrapped entity. @return PropertyId of this PropertyIdWrapper.
- L47 _public prototype_ `void SetPropertyId(FName InNewPropertyId);` — Get the type of the wrapped entity. @param InNewPropertyId The new PropertyId to assign to this PropertyIdWrapper.
- L52 _public prototype_ `const FName& GetSuperType() const;` — Get the super type of the wrapped property. @return The super type of this PropertyIdWrapper.
- L57 _public prototype_ `const FName& GetSubType() const;` — Get the sub type of the wrapped entity. @return The sub type of this PropertyIdWrapper.
- L62 _public prototype_ `bool IsValid() const;` — Returns whether the type and the underlying data is valid. @return True if EntityId and either SuperType or SubType is valid, false otherwise.
- L67 _public prototype_ `bool IsValidPropertyId() const;` — Returns whether the type and the underlying data is valid. @return True if the PropertyId is different from the default value.
- L72 _public prototype_ `bool operator==(const FGuid& WrappedId) const;`
- L74 _public prototype_ `bool operator==(const FRCPropertyIdWrapper& Other) const;`
- L77 _private prototype_ `void UpdateTypes(const TSharedRef<FRemoteControlProperty>& InRCProperty, UObject* InOwner, FProperty* InProperty);`
- L82 _private member_ `FGuid EntityId;` — `UPROPERTY()` — Entity identifier of the remote control property.
- L86 _private member_ `FName PropertyId;` — `UPROPERTY()` — Holds the field identifier of the remote control property.
- L90 _private member_ `FName SuperType;` — `UPROPERTY()` — Holds the type of the wrapped property.
- L94 _private member_ `FName SubType;` — `UPROPERTY()` — Holds the type of the wrapped object.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRCPropertyIdWrapper> : public TStructOpsTypeTraitsBase2<FRCPropertyIdWrapper>`  
_L99-106_
- inherits: `TStructOpsTypeTraitsBase2<FRCPropertyIdWrapper>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L102-105_

#### class `URemoteControlPropertyIdRegistry`  
`class URemoteControlPropertyIdRegistry : public UObject`  
_L112-230_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Holds a Registry of the PropertyId PropertyId
- L120 _public prototype_ `void Initialize();` — Initialize the Registry with the given Preset.
- L122 _public prototype_ `URemoteControlPreset* GetSourcePreset() const;`
- L125 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L132 _public prototype_ `void PerformChainReaction(const FRemoteControlPropertyIdArgs& InArgs);` — Update the value(s) of the property(ies) that are bound to a PropertyIdAction. @param InArgs Argument used to update the property(ies) value.
- L138 _public prototype_ `void AddIdentifiedField(const TSharedRef<FRemoteControlField>& InFieldToIdentify);` — Add a field to the set of identified fields. @param InFieldToIdentify the entity to identify.
- L144 _public prototype_ `bool IsEmpty() const;` — Check if there is any PropertyId Field. @return True if the Registry is Empty, false otherwise.
- L150 _public prototype_ `void UpdateIdentifiedField(const TSharedRef<FRemoteControlField>& InFieldToIdentify);` — Updates a field from the set of identified fields. @param InFieldToIdentify the entity to identify.
- L156 _public prototype_ `void RemoveIdentifiedField(const FGuid& InEntityId);` — Remove an identified field from the registry using its id. @param InEntityId Id of the Property to remove.
- L162 _public prototype_ `TSet<FName> GetFieldIdsNameList() const;` — Get the list of existing Property Ids. @return The list of existing Property Ids that has a valid FieldId.
- L169 _public prototype_ `TSet<FName> GetFullPropertyIdsNamePossibilitiesList() const;` — Returns all the possible Ids that can be used. @return A Set with the possible Ids to use.
- L176 _public prototype_ `TSet<FGuid> GetEntityIdsForPropertyId(const FName& InPropertyId) const;` — Return all EntityIds that has the given PropertyId. @param InPropertyId Property Id to match. @return The list of existing EntityIds that has the given PropertyId.
- L182 _public prototype_ `TSet<FGuid> GetEntityIdsList();` — Get the list of existing Property Ids. @return The list of existing Property Ids that has a valid FieldId.
- L192 _public prototype_ `bool Contains(FName InContainerPropertyId, FName InTargetPropertyId) const;` — Returns whether the 2 Ids are equal or if the Target one is contained in the Container one.\n ex: 100.A and 100 will return true but not the other way around. @param InContainerPropertyId Container PropertyId, will create sub-string from this to later check if the target one is equal to one of them. @param InTargetPropertyId Target Id to check if it is part of the container one. @return True if the PropertyIds are equal or if the Target one is contained in at least 1 sub-string of the Container one.
- L201 _public prototype_ `TSet<FName> GetPossiblePropertyIds(FName InPropId) const;` — Returns the possible Ids based on given one.\n ex: 100.A.B will return 100 and 100.A and 100.A.B @param InPropId Property Id used to generate all the other Ids that can be used with this one. @return A Set with the possible Ids to use.
- L203 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyIdUpdated) FOnPropertyIdUpdated& OnPropertyIdUpdated()`
- L208 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyIdActionNeedsRefresh) FOnPropertyIdActionNeedsRefresh& OnPropertyIdActionNeedsRefresh()` — Callback for refreshing the UI when an identity is updated.
- L216 _public prototype_ `void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap);` — @brief Called internally when entity Ids are renewed. @param InEntityIdMap Map of old Id to new Id.
- L221 _private member_ `TSet<FRCPropertyIdWrapper> IdentifiedFields;` — `UPROPERTY(Transient)` — Holds the identified fields.
- L224 _private member_ `FOnPropertyIdUpdated OnPropertyIdUpdatedDelegate;` — Delegate triggered when a property has its field Id changed.
- L228 _private member_ `FOnPropertyIdActionNeedsRefresh OnPropertyIdActionNeedsRefreshDelegate;` — Delegate triggered when PropertyID UI needs to refresh.

#### Free symbols / members of external scopes

- L103 _enumerator_ `WithSerializer = false` (scope `TStructOpsTypeTraits::__anon77f42ff80103`)
- L104 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon77f42ff80103`)
- L203 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyIdUpdated) FOnPropertyIdUpdated& OnPropertyIdUpdated() { return OnPropertyIdUpdatedDelegate; } #if WITH_EDITOR DECLARE_MULTICAST_DELEGATE(FOnPropertyIdActionNeedsRefresh) FOnPropertyIdActionNeedsRefresh& OnPropertyIdActionNeedsRefresh() { return OnPropertyIdActionNeedsRefreshDelegate; };`
- L208 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyIdActionNeedsRefresh) FOnPropertyIdActionNeedsRefresh& OnPropertyIdActionNeedsRefresh() { return OnPropertyIdActionNeedsRefreshDelegate; };` — Callback for refreshing the UI when an identity is updated.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlProtocolBinding.h` (Public)


#### enum `ERCBindingStatus`  
`enum class ERCBindingStatus : uint8`  
_L42-47_
- reflection: `UENUM()`
- desc: Status of the binding
- L44 _public enumerator_ `Unassigned`
- L45 _public enumerator_ `Awaiting`
- L46 _public enumerator_ `Bound`

#### struct `FRemoteControlProtocolMapping`  
`struct FRemoteControlProtocolMapping`  
_L57-324_
- reflection: `USTRUCT()`
- desc: Mapping of the range of the values for the protocol This class holds a generic range buffer. For example, it could be FFloatProperty 4 bytes Or it could be any UScripStruct, like FVector - 12 bytes Or any custom struct, arrays, maps, sets, or primitive properties
- L67 _public prototype_ `FRemoteControlProtocolMapping() = default;`
- L68 _public prototype_ `FRemoteControlProtocolMapping(FProperty* InProperty, uint8 InRangeValueSize, const FGuid& InMappingId = FGuid::NewGuid());`
- L70 _public prototype_ `bool operator==(const FRemoteControlProtocolMapping& InProtocolMapping) const;`
- L71 _public prototype_ `bool operator==(FGuid InProtocolMappingId) const;`
- L75 _public function_ `const FGuid& GetId() const` — Get Binding Range Id.
- L78 _public function_ `bool IsValid() const` — Get validity of the mapping (based on the Id)
- L82 _public function_ `template <typename ValueType> ValueType GetRangeValue()` — Get Binding Range Value
- L92 _public function_ `GetRangeValue()`
- L100 _public function_ `template <typename ValueType> void SetRangeValue(ValueType InRangeValue)` — Set Binding Range Value based on template value input
- L110 _public function_ `SetRangeValue(ValueType InRangeValue)`
- L120 _public function_ `template <typename ValueType> bool CanGetMappingValueAsPrimitive() const` — Returns true if one can get mapping value as primitive for the specified type
- L138 _public function_ `GetMappingValueAsPrimitive()`
- L165 _public function_ `template <typename ValueType> void SetMappingValueAsPrimitive(ValueType InMappingPropertyValue)` — Set primitive Mapping Property Value based on template value input
- L177 _public function_ `SetMappingValueAsPrimitive(ValueType InMappingPropertyValue)`
- L188 _public function_ `template <typename PropertyType> bool CopyRawRangeData(const TSharedPtr<IPropertyHandle>& InPropertyHandle)` — Copies the underlying InterpolationRangePropertyData to the given destination, using the input property for type information
- L202 _public function_ `template <typename PropertyType> bool SetRawRangeData(const TSharedPtr<IPropertyHandle>& InPropertyHandle)` — Sets the underlying InterpolationRangePropertyData to the given source, using the input property for type information
- L214 _public function_ `bool SetRawRangeData(URemoteControlPreset* InOwningPreset, const FProperty* InProperty, const void* InSource)` — Sets the underlying InterpolationRangePropertyData to the given source, using the input property for type information
- L227 _public function_ `template <typename PropertyType> bool CopyRawMappingData(const TSharedPtr<IPropertyHandle>& InPropertyHandle)` — Copies the underlying InterpolationMappingPropertyData to the given destination, using the input property for type information
- L242 _public function_ `template <typename PropertyType> bool SetRawMappingData(const TSharedPtr<IPropertyHandle>& InPropertyHandle)` — Sets the underlying InterpolationMappingPropertyData to the given source, using the input property for type information
- L256 _public function_ `bool SetRawMappingData(URemoteControlPreset* InOwningPreset, const FProperty* InProperty, const void* InSource)` — Sets the underlying InterpolationMappingPropertyData to the given source, using the input property for type information
- L269 _public prototype_ `TSharedPtr<FStructOnScope> GetMappingPropertyAsStructOnScope();` — Get Mapping value as a Struct on Scope, only in case BoundProperty is FStructProperty
- L274 _private prototype_ `template <typename PropertyType> bool PropertySizeMatchesData(const TArray<uint8>& InSource, const PropertyType* InProperty);` — Checks that the source data matches the expected size of the property
- L277 _private prototype_ `bool PropertySizeMatchesData(const TArray<uint8>& InSource, const FName& InPropertyTypeName);` — Checks that the source data matches the expected size of the property
- L280 _private prototype_ `void RefreshCachedData(const FName& InRangePropertyTypeName);` — Refreshes (deserializes) mapping data to cache. If the RangePropertyTypeName is NAME_None, it is not set.
- L285 _private member_ `FGuid Id;` — `UPROPERTY()` — Unique Id of the current binding
- L294 _private member_ `TArray<uint8> InterpolationRangePropertyData;` — `UPROPERTY()` — The current integer value of the mapping range. It could be a float, int32, uint8, etc. That is based on protocol input data. For example, it could be uint8 in the case of one-byte mapping. In this case, the range value could be from 0 up to 255, which bound to InterpolationMappingPropertyData
- L301 _private member_ `TArray<uint8> InterpolationMappingPropertyData;` — `UPROPERTY()` — Holds the serialized mapped property data. It could be a primitive value for FNumericProperty, or a text representation for a struct.
- L308 _private member_ `TArray<uint8> InterpolationRangePropertyDataCache;` — `UPROPERTY(Transient)` — Holds the range property data buffer. This is the cached raw data as opposed to the serialized data.
- L315 _private member_ `TArray<uint8> InterpolationMappingPropertyDataCache;` — `UPROPERTY(Transient)` — Holds the mapped property data buffer. This is the cached raw data as opposed to the serialized data, so it doesn't contain type information.
- L319 _private member_ `int32 InterpolationMappingPropertyElementNum = 1;` — `UPROPERTY()` — The element count if the Mapping is an array.
- L323 _private member_ `TFieldPath<FProperty> BoundPropertyPath;` — `UPROPERTY()` — Holds the bound property path
- L328 _function_ `template <> inline void FRemoteControlProtocolMapping::SetMappingValueAsPrimitive<FString>(FString InMappingPropertyValue)` — Set primitive Mapping Property String Value based on template value input
- L340 _function_ `template <> inline void FRemoteControlProtocolMapping::SetMappingValueAsPrimitive<FName>(FName InMappingPropertyValue)` — Set primitive Mapping Property Name Value based on template value input
- L349 _function_ `template <> inline void FRemoteControlProtocolMapping::SetMappingValueAsPrimitive<FText>(FText InMappingPropertyValue)` — Set primitive Mapping Property Text Value based on template value input
- L358 _function_ `template <> inline bool FRemoteControlProtocolMapping::PropertySizeMatchesData<FBoolProperty>(const TArray<uint8>& InSource, const FBoolProperty* InProperty)`
- L364 _function_ `template <> inline bool FRemoteControlProtocolMapping::PropertySizeMatchesData<FNumericProperty>(const TArray<uint8>& InSource, const FNumericProperty* InProperty)`
- L370 _function_ `template <> inline bool FRemoteControlProtocolMapping::PropertySizeMatchesData<FStructProperty>(const TArray<uint8>& InSource, const FStructProperty* InProperty)`
- L377 _function_ `template <typename PropertyType> bool FRemoteControlProtocolMapping::PropertySizeMatchesData(const TArray<uint8>& InSource, const PropertyType* InProperty)`

#### struct `FRemoteControlProtocolEntity`  
`struct FRemoteControlProtocolEntity`  
_L387-594_
- reflection: `USTRUCT()`
- desc: These structures serve both as properties mapping as well as UI generation Protocols should implement it based on the parameters they need.
- L392 _public function_ `virtual ~FRemoteControlProtocolEntity()`
- L399 _public prototype_ `void Init(URemoteControlPreset* InOwner, FGuid InPropertyId);` — Initialize after allocation @param InOwner The preset that owns this entity. @param InPropertyId exposed property id.
- L402 _public function_ `const FGuid& GetPropertyId() const` — Get exposed property id
- L412 _public prototype_ `bool ApplyProtocolValueToProperty(const double InProtocolValue);` — `UE_DEPRECATED(5.5, "ApplyProtocolValueToProperty is deprecated. Instead please refer to UE::RemoteControl::ProtocolEntityProcessor::ProcessEntities")` — Interpolate and apply protocol value to the property @param InProtocolValue				Double value from the protocol @param ModifyOperationFlags			(optional) Flags that specify how the property is modified when the value is applied. @return								True if the value was applied successfully
- L419 _public function_ `virtual FName GetRangePropertyName() const` — Get bound range property. For example, the range could be bound to FFloatProperty or FIntProperty, etc. It could be 0.f bound to FStructProperty or 0 bound to FBoolProperty where 0.f or 0 are Range PropertyName Each protocol defines its own binding property type.
- L422 _public prototype_ `virtual uint8 GetRangePropertySize() const;` — Get Size of the range property value
- L425 _public prototype_ `virtual const FString& GetRangePropertyMaxValue() const;` — Get the upper most value for the range property type, used for normalization
- L428 _public function_ `bool IsEnabled() const` — Get the state of the binding.
- L431 _public function_ `ERCBindingStatus GetBindingStatus() const` — Get current binding state of the entity
- L437 _public prototype_ `ERCBindingStatus ToggleBindingStatus();` — Toggle the binding @return Current binding state
- L440 _public prototype_ `void ResetDefaultBindingState();` — Reset the binding set to default
- L443 _public function_ `void SetEnabled(bool bInEnable)` — Set to enable or disable input.
- L449 _public function_ `virtual bool IsSame(const FRemoteControlProtocolEntity* InOther)` — Checks if this entity has the same values as the Other. Used to check for duplicate inputs.
- L454 _public prototype_ `virtual void ClearMask(ERCMask InMaskBit);` — Disables the given mask.
- L456 _public prototype_ `virtual void EnableMask(ERCMask InMaskBit);` — Enables the given mask.
- L458 _public prototype_ `virtual bool HasMask(ERCMask InMaskBit) const;` — Returns true if the given mask is enabled, false otherwise.
- L461 _public function_ `ERCMask GetOverridenMask() const` — Returns the overriden masks.
- L465 _public prototype_ `const FName GetPropertyName(const FName& ForColumnName);` — Retrieves the name of property corresponding to the given column name.
- L468 _public function_ `virtual void RegisterProperties()` — Register(s) all the properties (to be exposed) of this protocol entity.
- L472 _public function_ `const TWeakObjectPtr<URemoteControlPreset>& GetOwner() const` — Returns the preset that owns this protocol entity
- L538 _public prototype_ `TArray<FRangeMappingData> GetRangeMappingBuffers();` — Get Ranges and Mapping Value pointers
- L541 _public member_ `double ProtocolValue = 0.0;` — The current protocol value. Useful to test if the value changed
- L554 _private prototype_ `bool GetInterpolatedPropertyBuffer(FProperty* InProperty, double InProtocolValue, TArray<uint8>& OutBuffer);` — `UE_DEPRECATED(5.5, "Deprecated in favor of the overload that specifies the OwnerObject of the property.")` — Serialize interpolated property value to Cbor buffer @param InProperty Property to apply serialization @param InProtocolValue double value from the protocol @param OutBuffer serialized buffer @return true if serialized correctly
- L560 _protected member_ `TWeakObjectPtr<URemoteControlPreset> Owner;` — `UPROPERTY()` — The preset that owns this entity.
- L564 _protected member_ `FGuid PropertyId;` — `UPROPERTY()` — Exposed property Id
- L567 _protected member_ `bool bIsEnabled = true;` — State of the binding, set to false to ignore input.
- L575 _protected member_ `TSet<FRemoteControlProtocolMapping> Mappings;` — `UPROPERTY()` — Property mapping ranges set Stores protocol mapping for this protocol binding entity
- L579 _protected member_ `uint8 OverridenMasks = static_cast<uint8>(ERCMask::NoMask);` — `UPROPERTY()` — Holds the overriden masks.
- L586 _protected member_ `TMap<FName, FName> ColumnsToProperties;` — Holds column specific properties for this protocol.
- L593 _private member_ `ERCBindingStatus BindingStatus = ERCBindingStatus::Unassigned;` — `UPROPERTY()` — Binding status of this protocol entity

#### struct `FRemoteControlProtocolEntity::FRangeMappingData`  
`struct FRangeMappingData`  
_L475-514_
- desc: Container for range and mapping value pointers, and an optional number of elements (arrays, strings).
- L477 _public member_ `TArray<uint8> Range;`
- L478 _public member_ `TArray<uint8> Mapping;`
- L481 _public member_ `mutable int32 NumElements = 1;` — Number of elements represented in the mapping data (for arrays, etc.).
- L483 _public prototype_ `FRangeMappingData() = default;`
- L485 _public function_ `FRangeMappingData(const uint8* InRange, const uint8* InMapping, int32 InRangeSize = sizeof(uint8), int32 InMappingSize = sizeof(uint8), int32 InNumMappingElements = 1) : NumElements(InNumMappingElements)`
- L497 _public function_ `FRangeMappingData(const TArray<uint8>& InRange, const uint8* InMapping, int32 InMappingSize = sizeof(uint8), const int32 InNumMappingElements = 1) : Range(TArray<uint8>(InRange)) , NumElements(InNumMappingElements)`
- L507 _public function_ `FRangeMappingData(const TArray<uint8>& InRange, const TArray<uint8>& InMapping, const int32 InNumMappingElements = 1) : Range(TArray<uint8>(InRange)) , Mapping(TArray<uint8>(InMapping)) , NumElements(InNumMappingElements)`

#### struct `FRemoteControlProtocolEntity::TRangeMappingData`  
`template <typename RangeType, typename MappingType> struct TRangeMappingData`  
_L518-535_
- desc: Templated container for range and mapping values.
- L520 _public member_ `RangeType Range;`
- L521 _public member_ `MappingType Mapping;`
- L523 _public prototype_ `TRangeMappingData() = default;`
- L525 _public function_ `TRangeMappingData(const RangeType& InRange, const MappingType& InMapping) : Range(InRange) , Mapping(InMapping)`
- L530 _public function_ `explicit TRangeMappingData(const FRangeMappingData& InRangeMappingData)`

#### struct `FRemoteControlProtocolBinding`  
`struct FRemoteControlProtocolBinding`  
_L600-729_
- reflection: `USTRUCT()`
- desc: Struct which holds the bound struct and serialized struct archive
- L607 _public prototype_ `FRemoteControlProtocolBinding() = default;`
- L608 _public prototype_ `FRemoteControlProtocolBinding(const FName InProtocolName, const FGuid& InPropertyId, TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> InRemoteControlProtocolEntityPtr, const FGuid& InBindingId = FGuid::NewGuid());`
- L610 _public prototype_ `bool operator==(const FRemoteControlProtocolBinding& InProtocolBinding) const;`
- L611 _public prototype_ `bool operator==(FGuid InProtocolBindingId) const;`
- L615 _public function_ `const FGuid& GetId() const` — Get protocol binding id
- L618 _public function_ `FName GetProtocolName() const` — Get protocol bound protocol name, such as MIDI, DMX, OSC, etc
- L621 _public function_ `const FGuid& GetPropertyId() const` — Get exposed property id
- L624 _public prototype_ `TSharedPtr<FStructOnScope> GetStructOnScope() const;` — Get bound struct scope wrapper
- L627 _public function_ `TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> GetRemoteControlProtocolEntityPtr() const` — Get pointer to the StructOnScope
- L633 _public prototype_ `void AddMapping(const FRemoteControlProtocolMapping& InProtocolMapping);` — Add binding mapping to the protocol bound struct @param InProtocolMapping input mapping with value range and value data
- L640 _public prototype_ `int32 RemoveMapping(const FGuid& InMappingId);` — Remove the bound struct mapping based on given mapping id @param InMappingId mapping unique id @return The number of elements removed.
- L645 _public prototype_ `void ClearMappings();` — Empty all mapping for the bound struct
- L652 _public prototype_ `FRemoteControlProtocolMapping* FindMapping(const FGuid& InMappingId);` — Remove the bound struct mapping based on given mapping id @param InMappingId mapping unique id @return FRemoteControlProtocolMapping struct pointer
- L659 _public prototype_ `void ForEachMapping(FGetProtocolMappingCallback InCallback);` — Loop through all mappings @param InCallback mapping reference callback with mapping struct reference as an argument @return FRemoteControlProtocolMapping struct pointer
- L668 _public function_ `template <typename T> bool SetRangeToMapping(const FGuid& InMappingId, T InRangeValue)` — Set range value which is bound to mapping struct @param InMappingId mapping unique id @param InRangeValue range property value @return true if it was set successfully
- L689 _public prototype_ `bool SetPropertyDataToMapping(const FGuid& InMappingId, const void* InPropertyValuePtr);` — Set mapping property data to bound mapping struct. Range data could be a value container of the primitive value like FFloatProperty. And it could be more complex Properties such as FStructProperty data pointer. @param InMappingId mapping unique id @param InPropertyValuePtr property value pointer @return true if it was set successfully
- L693 _public function_ `template <typename ValueType> static bool IsRangeTypeSupported()` — Checks if the given ValueType is supported
- L697 _public function_ `template <typename PropertyType> static bool IsRangePropertyTypeSupported()` — Checks if the given PropertyType (FProperty) is supported
- L700 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom struct serialize
- L703 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& InCollector);`
- L707 _private prototype_ `FRemoteControlProtocolEntity* GetRemoteControlProtocolEntity();` — Return FRemoteControlProtocolEntity pointer from RemoteControlProtocolEntityPtr
- L712 _protected member_ `FGuid Id;` — `UPROPERTY()` — Binding Id
- L716 _protected member_ `FName ProtocolName;` — `UPROPERTY()` — Protocol name which we using for binding
- L720 _protected member_ `FGuid PropertyId;` — `UPROPERTY()` — Property Unique ID
- L724 _protected member_ `FName MappingPropertyName;` — `UPROPERTY()` — Property name which we using for protocol range mapping
- L728 _private member_ `TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> RemoteControlProtocolEntityPtr;` — Pointer to struct on scope

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FRemoteControlProtocolBinding> : public TStructOpsTypeTraitsBase2<FRemoteControlProtocolBinding>`  
_L735-742_
- inherits: `TStructOpsTypeTraitsBase2<FRemoteControlProtocolBinding>`
- desc: TypeTraits to define FRemoteControlProtocolBinding with a Serialize function

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L738-741_

#### Free symbols / members of external scopes

- L26 _typedef_ `using FGetProtocolMappingCallback = TFunctionRef<void(FRemoteControlProtocolMapping&)>;`
- L30 _macro_ `#define EXPOSE_PROTOCOL_PROPERTY(ColumnName, ClassName, MemberName) \`
- L739 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anondeda8c1a0103`)
- L740 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anondeda8c1a0103`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControl/Public/RemoteControlProtocolEntityProcessor.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RemoteControl` (scope `UE`)
- L12 _namespace_ `namespace ProtocolEntityProcessor` (scope `UE::RemoteControl`)
- L15 _prototype_ `bool DoesScriptStructSupportMasking(const UScriptStruct* InStruct);` (scope `UE::RemoteControl::ProtocolEntityProcessor`) — Returns true if the script struct supports masking
- L18 _prototype_ `bool DoesPropertySupportMasking(const FProperty* Property);` (scope `UE::RemoteControl::ProtocolEntityProcessor`) — Returns true if the property supports masking.
- L21 _prototype_ `void ProcessEntities(const TMap<TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>>, double>& EntityToValueMap);` (scope `UE::RemoteControl::ProtocolEntityProcessor`) — Processes provided entities and their respective protocol values
