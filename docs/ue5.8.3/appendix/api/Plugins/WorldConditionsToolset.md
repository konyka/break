# Plugins / WorldConditionsToolset

- module root: `Plugins/Experimental/Toolsets/WorldConditionsToolset/Source/WorldConditionsToolset`
- headers: 3; symbols: 21
- symbol kinds: class=3, delegate=1, member=1, namespace=4, prototype=12
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, ToolsetRegistry, UnrealEd, WorldConditions
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/WorldConditionsToolset/Source/WorldConditionsToolset/Private/WorldConditionQueryConverter.h` (Private)


#### class `UE::WorldConditionsToolset::FWorldConditionQueryConverter`  
`class FWorldConditionQueryConverter : public UE::ToolsetRegistry::FToolsetJsonConverter`  
_L15-24_
- inherits: `UE::ToolsetRegistry::FToolsetJsonConverter`
- desc: JSON converter for FWorldConditionQueryDefinition. Serializes the query's UPROPERTYs via the ToolsetJson pipeline, plus a description convenience field. On deserialization, rebuilds the SharedDefinition via Initialize().
- L18 _public prototype_ `virtual FString GetName() const override;`
- L19 _public prototype_ `virtual bool CanConvertProperty(TNotNull<const FProperty*> Property) override;`
- L20 _public prototype_ `virtual TSharedPtr<FJsonObject> PropertyToJsonSchema(TNotNull<const FProperty*> Property) override;`
- L21 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToDefault(TNotNull<const FProperty*> Property, const FString& DefaultString) override;`
- L22 _public prototype_ `virtual TSharedPtr<FJsonValue> PropertyToJsonData(TNotNull<FProperty*> Property, const void* Value) override;`
- L23 _public prototype_ `virtual bool JsonDataToProperty(const TSharedPtr<FJsonValue>& JsonValue, TNotNull<FProperty*> Property, void* OutValue, UObject* Outer) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace WorldConditionsToolset` (scope `UE`)

### `Plugins/Experimental/Toolsets/WorldConditionsToolset/Source/WorldConditionsToolset/Private/WorldConditionTools.h` (Private)


#### class `UWorldConditionTools`  
`class UWorldConditionTools : public UToolsetDefinition`  
_L13-34_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UToolsetDefinition`
- desc: Inspect WorldCondition (FWorldConditionQueryDefinition, FWorldConditionBase) structs.
- L24 _public prototype_ `static FText GetQueryDescription(const FWorldConditionQueryDefinition& QueryDefinition);` — `UFUNCTION(meta = (AICallable), Category = "WorldConditions")` — Returns a human-readable description of a world condition query. @param QueryDefinition The query definition to describe. @return Text description of all conditions in the query.
- L33 _public prototype_ `static FText GetConditionDescription(const FInstancedStruct& Condition);` — `UFUNCTION(meta = (AICallable), Category = "WorldConditions")` — Returns a human-readable description of a single world condition. The condition must be passed as an FInstancedStruct containing an FWorldConditionBase-derived struct. @param Condition The instanced struct holding the world condition. @return Text description of the condition, or empty if invalid.

### `Plugins/Experimental/Toolsets/WorldConditionsToolset/Source/WorldConditionsToolset/Public/WorldConditionsToolset.h` (Public)


#### class `FWorldConditionsToolsetModule`  
`class FWorldConditionsToolsetModule : public IModuleInterface`  
_L13-23_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `void Register();`
- L22 _private member_ `TSharedPtr<UE::ToolsetRegistry::FToolsetJsonConverter> WorldConditionQueryConverter;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldConditionsToolset, Log, Log);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldConditionsToolset, Log, Log);`
