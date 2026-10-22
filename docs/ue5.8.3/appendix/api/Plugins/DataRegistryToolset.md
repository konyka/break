# Plugins / DataRegistryToolset

- module root: `Plugins/Experimental/Toolsets/DataRegistryToolset/Source/DataRegistryToolset`
- headers: 1; symbols: 23
- symbol kinds: class=1, member=13, prototype=7, struct=2
- PrivateDependencyModuleNames: CoreUObject, DataRegistry, Engine, GameplayTags, Json, ToolsetRegistry
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/DataRegistryToolset/Source/DataRegistryToolset/Private/DataRegistryTools.h` (Private)


#### struct `FDataRegistryInfo`  
`struct FDataRegistryInfo`  
_L18-46_
- reflection: `USTRUCT(BlueprintType)`
- desc: Detailed information about a single Data Registry.
- L24 _public member_ `FString RegistryName;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — The registry name.
- L28 _public member_ `FString Description;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Human-readable description.
- L32 _public member_ `TObjectPtr<const UScriptStruct> ItemStruct;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — The UScriptStruct used for items in this registry. May be null.
- L36 _public member_ `int32 ItemCount = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Number of item IDs known to this registry.
- L41 _public member_ `EDataRegistryAvailability Availability = EDataRegistryAvailability::DoesNotExist;` — `UPROPERTY(VisibleAnywhere, Category = "DataRegistry")` — Lowest availability across all sources on this registry. DoesNotExist indicates the registry has not been initialized.
- L45 _public member_ `FString IdFormat;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Base GameplayTag of the ID format, if any.

#### struct `FDataRegistrySourceSummary`  
`struct FDataRegistrySourceSummary`  
_L50-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: Summary information about a single UDataRegistrySource entry.
- L56 _public member_ `TObjectPtr<const UClass> SourceClass;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Class of the source.
- L60 _public member_ `FString DebugString;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Human-readable description of the source.
- L64 _public member_ `FSoftObjectPath SourceAssetPath;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Path to the underlying asset, if any.
- L68 _public member_ `EDataRegistryAvailability Availability = EDataRegistryAvailability::DoesNotExist;` — `UPROPERTY(VisibleAnywhere, Category = "DataRegistry")` — Availability of this source.
- L72 _public member_ `bool bIsInitialized = false;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Whether the source is initialized.
- L76 _public member_ `bool bIsTransient = false;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Whether this is a runtime-only (transient) source.
- L80 _public member_ `FString ParentSourceDebugString;` — `UPROPERTY(BlueprintReadWrite, Category = "DataRegistry")` — Debug string of the parent (original) source, if this is a transient child. Empty otherwise.

#### class `UDataRegistryTools`  
`class UDataRegistryTools : public UToolsetDefinition`  
_L85-154_
- reflection: `UCLASS(BlueprintType, Hidden)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for querying and inspecting Data Registries.
- L97 _public prototype_ `static TArray<FString> ListRegistries(const UScriptStruct* StructFilter = nullptr);` — `UFUNCTION(meta = (AICallable), Category = "DataRegistry")` — Returns the names of all registered Data Registries. @param StructFilter If non-null, only registries whose item struct inherits from this struct are returned. @return A list of registry names.
- L105 _public prototype_ `static FDataRegistryInfo GetRegistryInfo(const FString& RegistryName);` — `UFUNCTION(meta = (AICallable), Category = "DataRegistry")` — Returns detailed information about a specific registry. @param RegistryName The registry name. @return Detailed info including description and id format.
- L113 _public prototype_ `static FString GetSchema(const FString& RegistryName);` — `UFUNCTION(meta = (AICallable), Category = "DataRegistry")` — Returns the item struct schema as JSON. @param RegistryName The registry name. @return A JSON string describing the struct's fields and types.
- L121 _public prototype_ `static TArray<FString> ListItems(const FString& RegistryName);` — `UFUNCTION(meta = (AICallable), Category = "DataRegistry")` — Returns all item names in a Data Registry. @param RegistryName The registry name. @return All item names defined on the registry, in registry order.
- L131 _public prototype_ `static TArray<FDataRegistrySourceSummary> ListDataSources(const FString& RegistryName);` — `UFUNCTION(meta = (AICallable), Category = "DataRegistry")` — Returns the editor-defined sources configured on a Data Registry. These are the sources as authored on the registry asset, before any runtime expansion of meta sources. @param RegistryName The registry name. @return A list of source summaries, in definition order.
- L141 _public prototype_ `static TArray<FDataRegistrySourceSummary> ListRuntimeSources(const FString& RegistryName);` — `UFUNCTION(meta = (AICallable), Category = "DataRegistry")` — Returns the runtime sources for a Data Registry. This is the expanded list including transient child sources generated from meta sources. Will equal ListDataSources when the registry has no meta sources. @param RegistryName The registry name. @return A list of source summaries, in runtime order.
- L152 _public prototype_ `static TMap<FString, FInstancedStruct> GetItems( const FString& RegistryName, const TArray<FString>& ItemNames);` — `UFUNCTION(meta = (AICallable), Category = "DataRegistry")` — Returns cached item data. Items must be loaded in the registry cache to be returned. @param RegistryName The registry name. @param ItemNames Item names to retrieve. @return A map from item name to its struct data. Names that were not found in the cache are simply omitted from the result.
