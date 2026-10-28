# Plugins / MassSpawner

- module root: `Plugins/Runtime/MassGameplay/Source/MassSpawner`
- headers: 15; symbols: 414
- symbol kinds: class=12, delegate=6, enum=3, enumerator=8, externvar=4, function=127, macro=4, member=92, namespace=9, prototype=127, struct=20, typedef=2
- DynamicallyLoadedModuleNames: MassGameplayEditor
- PrivateDependencyModuleNames: Slate, UnrealEd
- PrivateIncludePathModuleNames: MassGameplayEditor
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassEntityEditor, MassSimulation, ZoneGraph

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Internal/MassSpawnerInternalTypes.h` (Internal)


#### class `UMassCreatedBySpawnerTrait`  
`class UMassCreatedBySpawnerTrait : public UMassEntityTraitBase`  
_L13-20_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UMassEntityTraitBase`
- L19 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### struct `FMassCreatedBySpawner`  
`struct FMassCreatedBySpawner : public FMassFragment`  
_L23-29_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FMassFragment`
- L28 _public member_ `TObjectPtr<AMassSpawner> Spawner;` — `UPROPERTY()`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassCreatedBySpawner> final`  
_L32-38_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L35-37_

#### Free symbols / members of external scopes

- L36 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anona4eb5eb80103`)

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/IMassSpawnerModule.h` (Public)


#### class `IMassSpawnerModule`  
`class IMassSpawnerModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassSpawnerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassAssortedFragmentsTrait.h` (Public)


#### class `UMassAssortedFragmentsTrait`  
`class UMassAssortedFragmentsTrait : public UMassEntityTraitBase`  
_L16-29_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Assorted Fragments"))`
- inherits: `UMassEntityTraitBase`
- desc: Mass Agent Feature which appends a list of specified fragments.
- L22 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L25 _protected member_ `TArray<FInstancedStruct> Fragments;` — `UPROPERTY(Category="Mass", EditAnywhere, meta = (BaseStruct = "/Script/MassEntity.MassFragment", ExcludeBaseStruct))`
- L28 _protected member_ `TArray<FInstancedStruct> Tags;` — `UPROPERTY(Category="Mass", EditAnywhere, meta = (BaseStruct = "/Script/MassEntity.MassTag", ExcludeBaseStruct))`

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntityConfigAsset.h` (Public)


#### struct `FMassEntityConfig`  
`struct FMassEntityConfig`  
_L25-109_
- reflection: `USTRUCT()`
- desc: Describes a Mass agent to spawn. The struct can be embedded to allow last minute changes to the agent (i.e. for debugging). The agent config describes a unique list of features which are used to create an entity template. Derived configs can override parent features.
- L31 _public prototype_ `FMassEntityConfig();`
- L32 _public prototype_ `FMassEntityConfig(UObject& InOwner);`
- L37 _public prototype_ `const FMassEntityTemplate& GetOrCreateEntityTemplate(const UWorld& World) const;` — Create entity template based on the features included in this config. @param World in which we are creating the template.
- L39 _public prototype_ `void DestroyEntityTemplate(const UWorld& World) const;`
- L44 _public prototype_ `const FMassEntityTemplate& GetEntityTemplateChecked(const UWorld& World) const;` — Fetches the EntityTemplate for given World, fails a check if one cannot be found.
- L47 _public function_ `const UMassEntityConfigAsset* GetParent() const` — @return Parent config
- L49 _public function_ `void SetParentAsset(const UMassEntityConfigAsset& InParent)`
- L52 _public function_ `TConstArrayView<UMassEntityTraitBase*> GetTraits() const` — @return View to the array of features defined on this config
- L55 _public function_ `const UMassEntityTraitBase* FindTrait(TSubclassOf<UMassEntityTraitBase> TraitClass, const bool bExactMatch = false) const` — Looks for a trait of the indicated type, accepting all child classes as well, unless bExactMatch == true
- L61 _public prototype_ `void AddTrait(UMassEntityTraitBase& Trait);` — Adds Trait to the collection of traits hosted by this FMassEntityConfig instance
- L64 _public prototype_ `bool ValidateEntityTemplate(const UWorld& World);` — Validates if the entity template is well built
- L66 _public function_ `void SetOwner(UObject& InOwner)`
- L68 _public function_ `bool IsEmpty() const`
- L70 _public function_ `const FGuid& GetGuid() const`
- L74 _public prototype_ `void PostDuplicate(bool bDuplicateForPIE);` — Needs to be called when the given config is being duplicated - ensured the ConfigGuid remains unique
- L75 _public prototype_ `void ForceRegenerateGUID();`
- L77 _public prototype_ `UMassEntityTraitBase* FindMutableTrait(TSubclassOf<UMassEntityTraitBase> TraitClass, const bool bExactMatch = false);`
- L85 _protected prototype_ `void GetCombinedTraits(TArray<UMassEntityTraitBase*>& OutTraits, FMassEntityTemplateBuildContext* BuildContext = nullptr) const;` — Combines traits based on the config hierarchy and returns list of unique traits @param BuildContext if provided, will be used to store additional information for reporting back to the user
- L89 _protected prototype_ `UMassEntityTraitBase* FindTraitInternal(TSubclassOf<UMassEntityTraitBase> TraitClass, const bool bExactMatch = false) const;` — Looks for a trait of the indicated type, accepting all child classes as well, unless bExactMatch == true. Walks the parent chain iteratively and detects cycles - logs an error and returns nullptr if a parent is reached twice.
- L93 _protected member_ `TObjectPtr<const UMassEntityConfigAsset> Parent = nullptr;` — `UPROPERTY(Category = "Derived Traits", EditAnywhere)` — Reference to parent config asset
- L97 _protected member_ `TArray<TObjectPtr<UMassEntityTraitBase>> Traits;` — `UPROPERTY(Category = "Traits", EditAnywhere, Instanced)` — Array of unique traits of this config
- L100 _protected member_ `TObjectPtr<UObject> ConfigOwner = nullptr;` — `UPROPERTY(transient)`
- L104 _private member_ `FGuid ConfigGuid;` — `UPROPERTY(VisibleAnywhere, Category="Mass", meta = (IgnoreForMemberInitializationTest))`
- L107 _private prototype_ `void GetCombinedTraitsInternal(TArray<UMassEntityTraitBase*>& OutTraits, TArray<const UObject*>& Visited, FMassEntityTemplateBuildContext* BuildContext) const;`
- L108 _private prototype_ `const FMassEntityTemplate* GetEntityTemplateInternal(const UWorld& World, FMassEntityTemplateID& TemplateIDOut) const;`

#### class `UMassEntityConfigAsset`  
`class UMassEntityConfigAsset : public UDataAsset`  
_L116-166_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: Agent Config asset allows to create shared configs that can be used as base for derived configs. The asset can be used as is i.e. on a spawner, or you can use FMassEntityConfig to allow last minute changes at use site.
- L121 _public function_ `UMassEntityConfigAsset() : Config(*this)`
- L126 _public function_ `const FMassEntityConfig& GetConfig() const` — @return Agent config stored in this asset
- L129 _public function_ `FMassEntityConfig& GetMutableConfig()` — @return Mutable agent config stored in this asset
- L131 _public function_ `const FMassEntityTemplate& GetOrCreateEntityTemplate(const UWorld& World) const`
- L136 _public function_ `void DestroyEntityTemplate(const UWorld& World) const`
- L142 _public function_ `const UMassEntityTraitBase* FindTrait(TSubclassOf<UMassEntityTraitBase> TraitClass, const bool bExactMatch = false) const` — Looks for a trait of the indicated type, accepting all child classes as well, unless bExactMatch == true
- L149 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;` — Called upon asset's dupllication. Ensured the underlying config's ConfigGuid remains unique
- L152 _public prototype_ `void ValidateEntityConfig();` — `UFUNCTION(CallInEditor, Category = "Entity Config")`
- L159 _public prototype_ `UMassEntityTraitBase* AddTrait(TSubclassOf<UMassEntityTraitBase> TraitClass);` — Returns a mutable instance of given trait class. If an instance of the given class can be found in the hosted FMassEntityConfig then that instance is returned. Otherwise one will be created, added to the FMassEntityConfig and returned.
- L165 _protected member_ `FMassEntityConfig Config;` — `UPROPERTY(Category = "Entity Config", EditAnywhere)` — The config described in this asset.

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntityEQSSpawnPointsGenerator.h` (Public)


#### class `UMassEntityEQSSpawnPointsGenerator`  
`class UMassEntityEQSSpawnPointsGenerator : public UMassEntitySpawnDataGeneratorBase`  
_L16-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(DisplayName="EQS SpawnPoints Generator"))`
- inherits: `UMassEntitySpawnDataGeneratorBase`
- desc: Describes the SpawnPoints Generator when we want to leverage the points given by an EQS Query
- L21 _public prototype_ `UMassEntityEQSSpawnPointsGenerator();`
- L23 _public prototype_ `virtual void Generate(UObject& QueryOwner, TConstArrayView<FMassSpawnedEntityType> EntityTypes, int32 Count, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const override;`
- L28 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _protected prototype_ `void OnEQSQueryFinished(TSharedPtr<FEnvQueryResult> EQSResult, TArray<FMassEntitySpawnDataGeneratorResult> Results, FFinishedGeneratingSpawnDataSignature FinishedGeneratingSpawnPointsDelegate) const;`
- L34 _protected member_ `FEQSParametrizedQueryExecutionRequest EQSRequest;` — `UPROPERTY(Category = "Query", EditAnywhere)`

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntitySpawnDataGeneratorBase.h` (Public)


#### struct `FMassEntitySpawnDataGeneratorResult`  
`struct FMassEntitySpawnDataGeneratorResult`  
_L19-42_
- reflection: `USTRUCT()`
- desc: The result of the spawn point generator.
- L25 _public member_ `FInstancedStruct SpawnData;` — `UPROPERTY()` — Spawn data that is passed to the InitSpawnDataProcessor. E.g. the data could contain array of locations, one for each entity.
- L29 _public member_ `TSubclassOf<UMassProcessor> SpawnDataProcessor;` — `UPROPERTY()` — Processor that understands how to apply SpawnData to the spawned entities.
- L33 _public member_ `TArray<TSubclassOf<UMassProcessor>> PostSpawnProcessors;` — `UPROPERTY()` — Processors that are run for all entities after they entities for a MassSpawner are initialized.
- L37 _public member_ `int32 EntityConfigIndex = INDEX_NONE;` — `UPROPERTY()` — Index in the EntityTypes array passed to Generate().
- L41 _public member_ `int32 NumEntities = 0;` — `UPROPERTY()` — Number of entities to spawn.

#### class `UMassEntitySpawnDataGeneratorBase`  
`class UMassEntitySpawnDataGeneratorBase : public UObject`  
_L53-80_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: Base class for Mass Entity Spawn Points Generator. A Mass Spawn Points Generator can be of several type (EQS, ZoneGraph, Volume, Area, etc.) The concept is to override the GenerateSpawnPoints() method and requesting a certain number of Spawn Point Locations to the method.
- L63 _public prototype_ `virtual void Generate(UObject& QueryOwner, TConstArrayView<FMassSpawnedEntityType> EntityTypes, int32 Count, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const PURE_VIRTUAL(UMassEntitySpawnDataGeneratorBase::GenerateSpawnPoints, );` — Generate "Count" number of SpawnPoints and return as a list of position @param Count of point to generate @param FinishedGeneratingSpawnPointsDelegate is the callback to call once the generation is done
- L70 _public prototype_ `void BuildResultsFromEntityTypes(const int32 SpawnCount, TConstArrayView<FMassSpawnedEntityType> EntityTypes, TArray<FMassEntitySpawnDataGeneratorResult>& OutResults) const;` — Populates empty generator results from EntityTypes based on the provided proportions. @param SpawnCount How many entities to distributed among the EntityTypes @param EntityTypes Types of entities to generate data for. @param OutResults Generator result for each entity type that had > 0 entities assigned to it.
- L73 _protected function_ `int32 GetRandomSelectionSeed() const`
- L76 _protected member_ `int32 RandomSelectionSeed = 0;` — `UPROPERTY(Category = "Query", EditAnywhere, meta=(EditCondition="bUseCustomSeed"))`
- L79 _protected member_ `uint8 bUseCustomSeed : 1;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FFinishedGeneratingSpawnDataSignature, TConstArrayView<FMassEntitySpawnDataGeneratorResult>);`
- L45 _prototype_ `DECLARE_DELEGATE_OneParam(FFinishedGeneratingSpawnDataSignature, TConstArrayView<FMassEntitySpawnDataGeneratorResult>);`

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntityTemplate.h` (Public)


#### struct `FMassEntityTemplateID`  
`struct FMassEntityTemplateID`  
_L31-99_
- reflection: `USTRUCT()`
- desc: ID of the template an entity is using
- L35 _public function_ `FMassEntityTemplateID() : FlavorHash(0), TotalHash(InvalidHash)`
- L42 _private function_ `explicit FMassEntityTemplateID(const FGuid& InGuid, const int32 InFlavorHash = 0) : ConfigGuid(InGuid), FlavorHash(InFlavorHash)` — use FMassEntityTemplateIDFactory to access this constructor flavor
- L50 _public function_ `uint64 GetHash64() const`
- L55 _public function_ `void Invalidate()`
- L60 _public function_ `bool operator==(const FMassEntityTemplateID& Other) const`
- L65 _public function_ `bool operator!=(const FMassEntityTemplateID& Other) const`
- L80 _public function_ `bool IsValid() const`
- L85 _public prototype_ `FString ToString() const;`
- L89 _protected member_ `FGuid ConfigGuid;` — `UPROPERTY(VisibleAnywhere, Category="Mass")`
- L92 _protected member_ `uint32 FlavorHash;` — `UPROPERTY()`
- L95 _protected member_ `uint64 TotalHash;` — `UPROPERTY()`
- L98 _private member_ `static constexpr uint64 InvalidHash = 0;`

#### struct `FMassEntityTemplateData`  
`struct FMassEntityTemplateData`  
_L108-373_
- reflection: `USTRUCT()`
- desc: Serves as data used to define and build finalized FMassEntityTemplate instances. Describes composition and initial values of fragments for entities created with this data, and lets users modify and extend the data. Once finalized as FMassEntityTemplate the data will become immutable.
- L112 _public typedef_ `typedef TFunction<void(UObject& , FMassEntityView& , const EMassTranslationDirection )> FObjectFragmentInitializerFunction;`
- L114 _public prototype_ `FMassEntityTemplateData() = default;`
- L115 _public prototype_ `explicit FMassEntityTemplateData(const FMassEntityTemplate& InFinalizedTemplate);`
- L117 _public prototype_ `bool IsEmpty() const;`
- L119 _public prototype_ `TConstArrayView<FObjectFragmentInitializerFunction> GetObjectFragmentInitializers() const;`
- L120 _public prototype_ `const FString& GetTemplateName() const;`
- L121 _public prototype_ `const FMassArchetypeCompositionDescriptor& GetCompositionDescriptor() const;`
- L122 _public prototype_ `const FMassArchetypeSharedFragmentValues& GetSharedFragmentValues() const;`
- L123 _public prototype_ `TConstArrayView<FInstancedStruct> GetInitialFragmentValues() const;`
- L125 _public prototype_ `TArray<FMassEntityTemplateData::FObjectFragmentInitializerFunction>& GetMutableObjectFragmentInitializers();`
- L127 _public prototype_ `void SetTemplateName(const FString& Name);`
- L130 _public function_ `template<typename T> void AddFragment()`
- L136 _public function_ `void AddFragment(TNotNull<const UScriptStruct*> FragmentType)`
- L144 _public function_ `void AddFragment(const UScriptStruct& FragmentType)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L150 _public function_ `void AddFragment(FConstStructView Fragment)` — @todo this function is doing nothing if a given fragment's initial value has already been created. This seems inconsistent with the other AddFragment functions (especially AddFragment_GetRef).
- L167 _public function_ `template<typename T> T& AddFragment_GetRef()`
- L184 _public function_ `template<typename T> T* GetMutableFragment()`
- L192 _public function_ `template<typename T> void AddTag()`
- L198 _public function_ `void AddTag(TNotNull<const UScriptStruct*> TagType)`
- L205 _public function_ `void AddTag(const UScriptStruct& TagType)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L211 _public function_ `template<typename T> void RemoveTag()`
- L217 _public function_ `void RemoveTag(TNotNull<const UScriptStruct*> TagType)`
- L224 _public function_ `void RemoveTag(const UScriptStruct& TagType)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L229 _public prototype_ `FMassTagBitSet GetTags() const;`
- L230 _public prototype_ `FMassElementBitSet& GetMutableTags();`
- L233 _public function_ `template<typename T> void AddChunkFragment()`
- L239 _public function_ `void AddConstSharedFragment(const FConstSharedStruct& SharedFragment)`
- L260 _public function_ `void AddSharedFragment(const FSharedStruct& SharedFragment)`
- L282 _public function_ `template<UE::Mass::CFragment T> bool HasFragment() const`
- L287 _public function_ `bool HasFragment(TNotNull<const UScriptStruct*> ScriptStruct) const`
- L294 _public function_ `void HasFragment(const UScriptStruct& ScriptStruct)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L300 _public function_ `template<UE::Mass::CTag T> bool HasTag() const`
- L306 _public function_ `template<UE::Mass::CChunkFragment T> bool HasChunkFragment() const`
- L312 _public function_ `template<UE::Mass::CSharedFragment T> bool HasSharedFragment() const`
- L317 _public function_ `bool HasSharedFragment(TNotNull<const UScriptStruct*> ScriptStruct) const`
- L324 _public function_ `void HasSharedFragment(const UScriptStruct& ScriptStruct)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L330 _public function_ `template<UE::Mass::CConstSharedFragment T> bool HasConstSharedFragment() const`
- L335 _public function_ `bool HasConstSharedFragment(TNotNull<const UScriptStruct*> ScriptStruct) const`
- L342 _public function_ `void HasConstSharedFragment(const UScriptStruct& ScriptStruct)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L347 _public function_ `void Sort()`
- L354 _public prototype_ `bool SlowIsEquivalent(const FMassEntityTemplateData& Other) const;` — Compares contents of two archetypes (this and Other). Returns whether both are equivalent. @Note that the function can be slow, depending on how elaborate the template is. This function is meant for debugging purposes.
- L356 _public prototype_ `FMassArchetypeCreationParams& GetArchetypeCreationParams();`
- L358 _public prototype_ `UE::Mass::FEntityBuilder CreateEntityBuilder(const TSharedRef<FMassEntityManager>& InEntityManager) const;`
- L361 _protected member_ `FMassArchetypeCompositionDescriptor Composition;`
- L362 _protected member_ `FMassArchetypeSharedFragmentValues SharedFragmentValues;`
- L365 _protected member_ `TArray<FInstancedStruct> InitialFragmentValues;` — Initial fragment values, this is not part of the archetype as it is the spawner job to set them.
- L368 _protected member_ `TArray<FObjectFragmentInitializerFunction> ObjectInitializers;` — These functions will be called to initialize entity's UObject-based fragments
- L370 _protected member_ `FMassArchetypeCreationParams CreationParams;`
- L372 _protected member_ `FString TemplateName;`
- L432 _function_ `inline bool FMassEntityTemplateData::IsEmpty() const`
- L437 _function_ `inline TConstArrayView<FMassEntityTemplateData::FObjectFragmentInitializerFunction> FMassEntityTemplateData::GetObjectFragmentInitializers() const`
- L442 _function_ `inline const FString& FMassEntityTemplateData::GetTemplateName() const`
- L447 _function_ `inline const FMassArchetypeCompositionDescriptor& FMassEntityTemplateData::GetCompositionDescriptor() const`
- L452 _function_ `inline const FMassArchetypeSharedFragmentValues& FMassEntityTemplateData::GetSharedFragmentValues() const`
- L457 _function_ `inline TConstArrayView<FInstancedStruct> FMassEntityTemplateData::GetInitialFragmentValues() const`
- L462 _function_ `inline TArray<FMassEntityTemplateData::FObjectFragmentInitializerFunction>& FMassEntityTemplateData::GetMutableObjectFragmentInitializers()`
- L467 _function_ `inline void FMassEntityTemplateData::SetTemplateName(const FString& Name)`
- L472 _function_ `inline FMassTagBitSet FMassEntityTemplateData::GetTags() const`
- L477 _function_ `inline FMassElementBitSet& FMassEntityTemplateData::GetMutableTags()`
- L482 _function_ `inline FMassArchetypeCreationParams& FMassEntityTemplateData::GetArchetypeCreationParams()`

#### struct `FMassEntityTemplate`  
`struct FMassEntityTemplate final : public TSharedFromThis<FMassEntityTemplate>`  
_L380-418_
- inherits: `TSharedFromThis<FMassEntityTemplate>`
- desc: A finalized and const wrapper for FMassEntityTemplateData, associated with a Mass archetype and template ID. Designed to never be changed. If a change is needed a copy of the hosted FMassEntityTemplateData needs to be made and used to create another finalized FMassEntityTemplate (via FMassEntityTemplateManager).
- L384 _public prototype_ `FMassEntityTemplate() = default;`
- L385 _public prototype_ `FMassEntityTemplate(const FMassEntityTemplateData& InData, FMassEntityManager& EntityManager, FMassEntityTemplateID InTemplateID);`
- L386 _public prototype_ `FMassEntityTemplate(FMassEntityTemplateData&& InData, FMassEntityManager& EntityManager, FMassEntityTemplateID InTemplateID);`
- L389 _public prototype_ `void SetArchetype(const FMassArchetypeHandle& InArchetype);` — InArchetype is expected to be valid. The function will crash-check it.
- L390 _public prototype_ `const FMassArchetypeHandle& GetArchetype() const;`
- L392 _public prototype_ `bool IsValid() const;`
- L394 _public prototype_ `void SetTemplateID(FMassEntityTemplateID InTemplateID);`
- L395 _public prototype_ `FMassEntityTemplateID GetTemplateID() const;`
- L397 _public prototype_ `FString DebugGetDescription(FMassEntityManager* EntityManager = nullptr) const;`
- L398 _public prototype_ `FString DebugGetArchetypeDescription(FMassEntityManager& EntityManager) const;`
- L400 _public prototype_ `static TSharedRef<FMassEntityTemplate> MakeFinalTemplate(FMassEntityManager& EntityManager, FMassEntityTemplateData&& TempTemplateData, FMassEntityTemplateID InTemplateID);`
- L405 _public prototype_ `TConstArrayView<FMassEntityTemplateData::FObjectFragmentInitializerFunction> GetObjectFragmentInitializers() const;`
- L406 _public prototype_ `const FString& GetTemplateName() const;`
- L407 _public prototype_ `const FMassArchetypeCompositionDescriptor& GetCompositionDescriptor() const;`
- L408 _public prototype_ `const FMassArchetypeSharedFragmentValues& GetSharedFragmentValues() const;`
- L409 _public prototype_ `TConstArrayView<FInstancedStruct> GetInitialFragmentValues() const;`
- L410 _public prototype_ `const FMassEntityTemplateData& GetTemplateData() const;`
- L412 _public prototype_ `UE::Mass::FEntityBuilder CreateEntityBuilder(const TSharedRef<FMassEntityManager>& InEntityManager) const;`
- L415 _private member_ `FMassEntityTemplateData TemplateData;`
- L416 _private member_ `FMassArchetypeHandle Archetype;`
- L417 _private member_ `FMassEntityTemplateID TemplateID;`
- L487 _function_ `inline const FMassArchetypeHandle& FMassEntityTemplate::GetArchetype() const`
- L492 _function_ `inline bool FMassEntityTemplate::IsValid() const`
- L497 _function_ `inline void FMassEntityTemplate::SetTemplateID(FMassEntityTemplateID InTemplateID)`
- L502 _function_ `inline FMassEntityTemplateID FMassEntityTemplate::GetTemplateID() const`
- L507 _function_ `inline TConstArrayView<FMassEntityTemplateData::FObjectFragmentInitializerFunction> FMassEntityTemplate::GetObjectFragmentInitializers() const`
- L512 _function_ `inline const FString& FMassEntityTemplate::GetTemplateName() const`
- L517 _function_ `inline const FMassArchetypeCompositionDescriptor& FMassEntityTemplate::GetCompositionDescriptor() const`
- L522 _function_ `inline const FMassArchetypeSharedFragmentValues& FMassEntityTemplate::GetSharedFragmentValues() const`
- L527 _function_ `inline TConstArrayView<FInstancedStruct> FMassEntityTemplate::GetInitialFragmentValues() const`
- L532 _function_ `inline const FMassEntityTemplateData& FMassEntityTemplate::GetTemplateData() const`

#### struct `FMassEntityTemplateIDFactory`  
`struct FMassEntityTemplateIDFactory`  
_L421-425_
- L423 _public prototype_ `static FMassEntityTemplateID Make(const FGuid& ConfigGuid);`
- L424 _public prototype_ `static FMassEntityTemplateID MakeFlavor(const FMassEntityTemplateID& SourceTemplateID, const int32 Flavor);`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Mass` (scope `UE`)
- L75 _function_ `friend uint32 GetTypeHash(const FMassEntityTemplateID& TemplateID)` — Note that since the function is 32-hashing a 64-bit value it's not guaranteed to produce globally unique values. But also note that it's still fine to use FMassEntityTemplateID as a TMap key type, since TMap is using 32bit hash to assign buckets rather than identify individual values.

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntityTemplateRegistry.h` (Public)


#### struct `FMassMissingTraitMessage`  
`struct FMassMissingTraitMessage`  
_L23-37_
- reflection: `USTRUCT()`
- L28 _public function_ `explicit FMassMissingTraitMessage(const UMassEntityTraitBase* InRequestingTrait = nullptr, const UStruct* InMissingType = nullptr, const UMassEntityTraitBase* InRemovedByTrait = nullptr) : RequestingTrait(InRequestingTrait), MissingType(InMissingType), RemovedByTrait(InRemovedByTrait)`
- L32 _public member_ `const UMassEntityTraitBase* RequestingTrait = nullptr;`
- L33 _public member_ `const UStruct* MissingType = nullptr;`
- L35 _public member_ `const UMassEntityTraitBase* RemovedByTrait = nullptr;` — if set indicates that the missing type has been explicitly removed by given trait.

#### struct `FMassDuplicateElementsMessage`  
`struct FMassDuplicateElementsMessage`  
_L40-48_
- reflection: `USTRUCT()`
- L44 _public member_ `const UMassEntityTraitBase* DuplicatingTrait = nullptr;`
- L45 _public member_ `const UMassEntityTraitBase* OriginalTrait = nullptr;`
- L46 _public member_ `const UStruct* Element = nullptr;`

#### enum `EFragmentInitialization`  
`enum class EFragmentInitialization : uint8`  
_L59-63_
- L61 _public enumerator_ `DefaultInitializer`
- L62 _public enumerator_ `NoInitializer`

#### struct `FMassEntityTemplateBuildContext`  
`struct FMassEntityTemplateBuildContext`  
_L65-411_
- L67 _public function_ `explicit FMassEntityTemplateBuildContext(FMassEntityTemplateData& InTemplate, FMassEntityTemplateID InTemplateID = FMassEntityTemplateID()) : TemplateData(InTemplate) , TemplateID(InTemplateID)`
- L72 _public function_ `void SetTemplateName(const FString& Name)`
- L81 _public function_ `template<typename T> T& AddFragment_GetRef()`
- L88 _public function_ `template<typename T> void AddFragment()`
- L94 _public function_ `void AddFragment(FConstStructView InFragment)`
- L102 _public function_ `template<typename T> void AddTag()`
- L109 _public function_ `void AddTag(TNotNull<const UScriptStruct*> TagType)`
- L117 _public function_ `void AddTag(const UScriptStruct& TagType)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L123 _public function_ `template<typename T> void AddChunkFragment()`
- L129 _public function_ `void AddConstSharedFragment(const FConstSharedStruct& InSharedFragment)`
- L136 _public function_ `void AddSharedFragment(const FSharedStruct& InSharedFragment)`
- L149 _public function_ `void RemoveTag(TNotNull<const UScriptStruct*> TagType)` — Removes given tag from collected data. More precisely: it will store the information and apply upon template creation (an optimization). WARNING: use with caution and only in cases where you know for certain what the given tag does and which processors rely on it. Using this functionality makes most sense for removing tags that specifically mean that entities having it are to be processed by a given processor.
- L160 _public function_ `void RemoveTag(const UScriptStruct& TagType)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L166 _public function_ `template<typename T> void RemoveTag()`
- L172 _public function_ `template<typename T> T* GetFragment()`
- L178 _public function_ `template<typename T> bool HasFragment() const`
- L184 _public function_ `bool HasFragment(TNotNull<const UScriptStruct*> ScriptStruct) const`
- L191 _public function_ `void HasFragment(const UScriptStruct& ScriptStruct)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L197 _public function_ `template<typename T> bool HasTag() const`
- L203 _public function_ `template<typename T> bool HasChunkFragment() const`
- L210 _public function_ `template<typename T> bool HasSharedFragment() const`
- L216 _public function_ `bool HasSharedFragment(TNotNull<const UScriptStruct*> ScriptStruct) const`
- L223 _public function_ `void HasSharedFragment(const UScriptStruct& ScriptStruct)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L229 _public function_ `template<typename T> bool HasConstSharedFragment() const`
- L235 _public function_ `bool HasConstSharedFragment(TNotNull<const UScriptStruct*> ScriptStruct) const`
- L242 _public function_ `void HasConstSharedFragment(const UScriptStruct& ScriptStruct)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L251 _public function_ `template<typename T> void AddTranslator()`
- L261 _public function_ `template<typename T> void RequireFragment()`
- L268 _public function_ `template<typename T> void RequireTag()`
- L274 _public function_ `void AddDependency(const UStruct* Dependency)`
- L282 _public function_ `FMassEntityTemplateID GetTemplateID() const`
- L283 _public function_ `TArray<FMassEntityTemplateData::FObjectFragmentInitializerFunction>& GetMutableObjectFragmentInitializers()`
- L295 _public prototype_ `bool BuildFromTraits(TConstArrayView<UMassEntityTraitBase*> Traits, const UWorld& World);` — Builds context from a list of traits @param Traits is the list of all the traits to build an entity @param World owning the MassEntitySubsystem for which the entity template is built @return true if there were no validation errors
- L307 _public function_ `bool IsInspectingData() const`
- L312 _public function_ `constexpr bool IsInspectingData() const`
- L319 _public function_ `void EnableDataInvestigationMode()`
- L326 _public function_ `void RegisterOverriddenTrait(TNotNull<UMassEntityTraitBase*> Trait)`
- L338 _protected prototype_ `bool ValidateBuildContext(const UWorld& World);` — Validate the build context for fragment trait ownership and trait fragment missing dependency @param World owning the MassEntitySubsystem for which the entity template is validated against @return true if there were no validation errors
- L340 _protected function_ `void TypeAdded(TNotNull<const UStruct*> Type)`
- L347 _protected function_ `void TypeAdded(const UScriptStruct& Type)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L359 _protected prototype_ `bool SetTraitBeingProcessed(const UMassEntityTraitBase* Trait);` — Return true if the given trait can be used. The function will fail if a trait instance of the given class has already been processed. The function will also fail the very same trait instance is used multiple times. Note that it's ok for Trait to be nullptr to indicate the subsequent additions to the build context are procedural in nature and are not associated with any traits. In that case it's ok to have multiple SetTraitBeingProcessed(nullptr) calls.
- L361 _protected function_ `void ResetBuildTimeData()`
- L376 _protected member_ `TArray<FTraitData> TraitsData;`
- L377 _protected member_ `TSet<const UMassEntityTraitBase*> TraitsProcessed;`
- L378 _protected member_ `TSet<const UMassEntityTraitBase*> IgnoredTraits;`
- L379 _protected member_ `TSet<const UMassEntityTraitBase*> OverriddenTraits;`
- L396 _protected member_ `TArray<FRemovedType> RemovedTypes;` — These tags will be removed from the resulting entity template @see RemoveTag for more details
- L398 _protected member_ `bool bBuildInProgress = false;`
- L400 _protected member_ `FMassEntityTemplateData& TemplateData;`
- L401 _protected member_ `FMassEntityTemplateID TemplateID;`
- L409 _private member_ `bool bIsInspectingData = false;` — This being set to `true` indicates that the context is being used to gather information, not to create actual entity templates.

#### struct `FMassEntityTemplateBuildContext::FTraitData`  
`struct FTraitData`  
_L370-375_
- L372 _public member_ `const UMassEntityTraitBase* Trait = nullptr;`
- L373 _public member_ `TArray<const UStruct*> TypesAdded;`
- L374 _public member_ `TArray<const UStruct*> TypesRequired;`

#### struct `FMassEntityTemplateBuildContext::FRemovedType`  
`struct FRemovedType`  
_L381-391_
- L383 _public member_ `const UStruct* TypeRemoved = nullptr;`
- L385 _public member_ `const UMassEntityTraitBase* Remover = nullptr;`
- L387 _public function_ `bool operator==(const FRemovedType& Other) const`

#### struct `FMassEntityTemplateRegistry`  
`struct FMassEntityTemplateRegistry`  
_L417-461_
- desc: Represents a repository storing all the FMassEntityTemplate that have been created and registered as part of FMassEntityConfig processing or via custom code (like we do in InstancedActors plugin).
- L420 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FStructToTemplateBuilderDelegate, const UWorld* , const FConstStructView , FMassEntityTemplateBuildContext& );` — @todo consider TFunction instead
- L422 _public prototype_ `explicit FMassEntityTemplateRegistry(UObject* InOwner = nullptr);`
- L427 _public prototype_ `void Initialize(const TSharedPtr<FMassEntityManager>& InEntityManager);` — Initializes and stores the EntityManager the templates will be associated with. Needs to be called before any template operations. Note that the function will only let users set the EntityManager once. Once it's set the subsequent calls will have no effect. If attempting to set a different EntityManaget an ensure will trigger.
- L429 _public prototype_ `void ShutDown();`
- L431 _public prototype_ `UWorld* GetWorld() const;`
- L433 _public prototype_ `static FStructToTemplateBuilderDelegate& FindOrAdd(const UScriptStruct& DataType);`
- L436 _public prototype_ `void DebugReset();` — Removes all the cached template instances
- L438 _public prototype_ `const TSharedRef<FMassEntityTemplate>* FindTemplateFromTemplateID(FMassEntityTemplateID TemplateID) const;`
- L443 _public prototype_ `const TSharedRef<FMassEntityTemplate>& FindOrAddTemplate(FMassEntityTemplateID TemplateID, FMassEntityTemplateData&& TemplateData);` — Adds a template based on TemplateData
- L445 _public prototype_ `void DestroyTemplate(FMassEntityTemplateID TemplateID);`
- L447 _public function_ `FMassEntityManager& GetEntityManagerChecked()`
- L450 _protected member_ `static TMap<const UScriptStruct*, FStructToTemplateBuilderDelegate> StructBasedBuilders;`
- L452 _protected member_ `TMap<FMassEntityTemplateID, TSharedRef<FMassEntityTemplate>> TemplateIDToTemplateMap;`
- L458 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;` — EntityManager the hosted templates are associated with. Storing instead of fetching at runtime to ensure all templates are tied to the same EntityManager
- L460 _protected member_ `TWeakObjectPtr<UObject> Owner;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define ENSURE_SUPPORTED_TRAIT_OPERATION() ensureMsgf(bBuildInProgress == false, TEXT("This method is not expected to be called as "\`
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace Mass` (scope `UE`)
- L51 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L53 _externvar_ `extern const FName TraitFailedValidation;` (scope `UE::Mass::Debug`)
- L54 _externvar_ `extern const FName TraitIgnored;` (scope `UE::Mass::Debug`)
- L55 _externvar_ `extern const FName TraitOverridden;` (scope `UE::Mass::Debug`)
- L420 _delegate_ `DECLARE_DELEGATE_ThreeParams(FStructToTemplateBuilderDelegate, const UWorld* , const FConstStructView , FMassEntityTemplateBuildContext& );` — @todo consider TFunction instead

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntityTraitBase.h` (Public)


#### class `UMassEntityTraitBase`  
`class UMassEntityTraitBase : public UObject`  
_L18-84_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, EditInlineNew, CollapseCategories, config = Mass, defaultconfig)`
- inherits: `UObject`
- desc: Base class for Mass Entity Traits. An entity trait is a set of fragments that create a logical trait tha makes sense to end use (i.e. replication, visualization). The template building method allows to configure some fragments based on properties or cached values. For example, a fragment can be added based on a referenced asset, or some memory hungry settings can be cached and just and index stored on a fragment.
- L51 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const PURE_VIRTUAL(UMassEntityTraitBase::BuildTemplate, return; );` — Appends items into the entity template required for the trait.
- L53 _public function_ `virtual void DestroyTemplate(const UWorld& World) const`
- L64 _public prototype_ `virtual bool ValidateTemplate(const FMassEntityTemplateBuildContext& BuildContext, const UWorld& World, FAdditionalTraitRequirements& OutTraitRequirements) const;` — Called once all traits have been processed and fragment requirements have been checked. Override this function to perform additional Trait's configuration validation. Returning `false` will indicate that the trait instance is not happy with the validation results - this result will be treated as an error. @param OutTraitRequirements contains requirements declared by this trait and gives ValidateTemplate a chance to add to the dependencies based on the state of BuildContext, which by this point should contain all the elements added by all the relevant traits. @return whether the validation was successful
- L67 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewTraitType, UMassEntityTraitBase&);`
- L68 _public function_ `static FOnNewTraitType& GetOnNewTraitTypeEvent()`
- L74 _protected prototype_ `virtual void PostInitProperties() override;`
- L77 _private member_ `static FOnNewTraitType OnNewTraitTypeEvent;`
- L83 _public member_ `EProcessorExecutionFlags ValidTargetConfig = EProcessorExecutionFlags::AllNetModes;` — `UPROPERTY(EditAnywhere, Category=Mass)` — Configures which configurations are targeted by this trait. Use it to have different configurations for client and server, for example.

#### struct `UMassEntityTraitBase::FAdditionalTraitRequirements`  
`struct FAdditionalTraitRequirements`  
_L27-47_
- desc: This is a type wrapping an existing TArray to limit how users can interact with the contained data. We essentially limit users to just adding elements, no other operations.
- L29 _public function_ `explicit FAdditionalTraitRequirements(TArray<const UStruct*>& InTargetContainer) : TargetContainer(InTargetContainer)`
- L36 _public prototype_ `FAdditionalTraitRequirements(const FAdditionalTraitRequirements&) = delete;` — Copying constructor and assignment deleted to prevent users storing copies of the type, which wouldn't be safe due to this type hosting a reference to an array that can go out of scope.
- L37 _public prototype_ `FAdditionalTraitRequirements& operator=(const FAdditionalTraitRequirements&) = delete;`
- L39 _public function_ `FAdditionalTraitRequirements& Add(const UScriptStruct* RequiredType)`
- L46 _private member_ `TArray<const UStruct*>& TargetContainer;`

#### Free symbols / members of external scopes

- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewTraitType, UMassEntityTraitBase&);`

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntityZoneGraphSpawnPointsGenerator.h` (Public)


#### class `UMassEntityZoneGraphSpawnPointsGenerator`  
`class UMassEntityZoneGraphSpawnPointsGenerator : public UMassEntitySpawnDataGeneratorBase`  
_L18-39_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(DisplayName="ZoneGraph SpawnPoints Generator"))`
- inherits: `UMassEntitySpawnDataGeneratorBase`
- desc: Describes the SpawnPoints Generator when we want to spawn directly on Zone Graph
- L23 _public prototype_ `virtual void Generate(UObject& QueryOwner, TConstArrayView<FMassSpawnedEntityType> EntityTypes, int32 Count, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const override;`
- L26 _protected prototype_ `void GeneratePointsForZoneGraphData(const ::AZoneGraphData& ZoneGraphData, TArray<FVector>& Locations, const FRandomStream& RandomStream) const;`
- L30 _protected member_ `FZoneGraphTagFilter TagFilter;` — `UPROPERTY(EditAnywhere, Category = "ZoneGraph Generator Config")` — Tags to filter which lane to use to generate points on
- L34 _protected member_ `float MinGap = 100;` — `UPROPERTY(EditAnywhere, Category = "ZoneGraph Generator Config")` — Minimum gap for spawning entities on a given lanes
- L38 _protected member_ `float MaxGap = 300;` — `UPROPERTY(EditAnywhere, Category = "ZoneGraph Generator Config")` — Maximum gap for spawning entities on a given lanes

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassSpawnLocationProcessor.h` (Public)


#### class `UMassSpawnLocationProcessor`  
`class UMassSpawnLocationProcessor : public UMassProcessor`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L17 _public prototype_ `UMassSpawnLocationProcessor();`
- L20 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L21 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L23 _protected member_ `FMassEntityQuery EntityQuery;`
- L24 _protected member_ `FRandomStream RandomStream;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSSPAWNER_API`

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassSpawner.h` (Public)


#### class `AMassSpawner`  
`class AMassSpawner : public AActor`  
_L21-162_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Object, Actor, Input, Rendering, LOD, Cooking, Collision, HLOD, Partition))`
- inherits: `AActor`
- desc: A spawner you can put on a map and configure it to spawn different things
- L25 _public prototype_ `AMassSpawner();`
- L28 _protected prototype_ `virtual void BeginPlay() override;`
- L29 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L30 _protected prototype_ `virtual void PostLoad() override;`
- L31 _protected prototype_ `virtual void PostRegisterAllComponents() override;`
- L32 _protected prototype_ `virtual void BeginDestroy() override;`
- L37 _public prototype_ `void DEBUG_Spawn();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Debug")`
- L41 _public prototype_ `void DEBUG_Clear();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Debug")` — Remove all the entities
- L46 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L49 _protected prototype_ `void RegisterEntityTemplates();`
- L56 _public prototype_ `void DoSpawning();` — `UFUNCTION(BlueprintCallable, Category = "Spawning")` — Starts the spawning of all the agent types of this spawner
- L62 _public prototype_ `void DoDespawning();` — `UFUNCTION(BlueprintCallable, Category = "Spawning")` — Despawn all mass agent that was spawned by this spawner
- L69 _public prototype_ `void DoDespawning(TConstArrayView<FMassEntityHandle> EntitiesToIgnore);` — Despawn all mass agent that was spawned by this spawner, except EntitiesToIgnore. Any EntitiesToIgnore previously spawned by this spawner will remain spawned and tracked by this spawner.
- L72 _public prototype_ `void ClearTemplates();` — `UFUNCTION(BlueprintCallable, Category = "Spawning")`
- L75 _public prototype_ `void UnloadConfig();` — `UFUNCTION(BlueprintCallable, Category = "Spawning")`
- L82 _public prototype_ `bool DespawnEntity(const FMassEntityHandle Entity);` — If given entity has been spawned by this MassSpawner instance then it will get destroyed and all the book keeping updated. Otherwise the call has no effect. @return true if the entity got removed. False otherwise.
- L89 _public function_ `void ScaleSpawningCount(float Scale)` — `UFUNCTION(BlueprintCallable, Category = "Spawning")` — Scales the spawning counts @param Scale is the number to multiply the all counts of each agent types
- L92 _public prototype_ `int32 GetCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Spawning")`
- L95 _public prototype_ `float GetSpawningCountScale() const;` — `UFUNCTION(BlueprintCallable, Category = "Spawning")`
- L99 _public member_ `FMassSpawnerOnSpawningFinishedEvent OnSpawningFinishedEvent;` — `UPROPERTY(BlueprintAssignable)` — Called once DoSpawning completes and all entities have been spawned.
- L103 _public member_ `FMassSpawnerOnDespawningFinishedEvent OnDespawningFinishedEvent;` — `UPROPERTY(BlueprintAssignable)` — Called once DoDespawning completes and all mass agents spawned by this spawner have been despawned.
- L106 _protected prototype_ `void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues);`
- L107 _protected prototype_ `void SpawnGeneratedEntities(TConstArrayView<FMassEntitySpawnDataGeneratorResult> Results);`
- L108 _protected prototype_ `void OnSpawnDataGenerationFinished(TConstArrayView<FMassEntitySpawnDataGeneratorResult> Results, FMassSpawnDataGenerator* FinishedGenerator);`
- L110 _protected prototype_ `int32 GetSpawnCount() const;`
- L111 _protected prototype_ `UMassProcessor* GetPostSpawnProcessor(TSubclassOf<UMassProcessor> ProcessorClass);`
- L122 _protected member_ `int32 Count;` — `UPROPERTY(EditAnywhere, Category = "Mass|Spawn")`
- L126 _protected member_ `TArray<FMassSpawnedEntityType> EntityTypes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mass|Spawn")` — Array of entity types to spawn. These define which entities to spawn.
- L130 _protected member_ `TArray<FMassSpawnDataGenerator> SpawnDataGenerators;` — `UPROPERTY(EditAnywhere, Category = "Mass|Spawn")` — Array of entity spawn generators. These define where to spawn entities.
- L133 _protected member_ `uint32 bAutoSpawnOnBeginPlay : 1;` — `UPROPERTY(Category = "Mass|Spawn", EditAnywhere)`
- L138 _protected member_ `uint32 bOverrideSchematics : 1;` — `UPROPERTY(Category = "Mass|Simulation", EditAnywhere)` — By default TickSchematics will be appended to the simulation's schematics. If this property is set to true the TickSchematics will override the original simulation schematics
- L141 _protected member_ `TArray<TObjectPtr<UMassProcessor>> PostSpawnProcessors;` — `UPROPERTY()`
- L145 _protected member_ `float SpawningCountScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|Spawn")` — Scale of the spawning count
- L147 _protected member_ `FDelegateHandle SimulationStartedHandle;`
- L149 _protected member_ `FDelegateHandle OnPostWorldInitDelegateHandle;`
- L151 _protected member_ `TArray<FSpawnedEntities> AllSpawnedEntities;`
- L153 _protected member_ `TArray<FMassEntitySpawnDataGeneratorResult> AllGeneratedResults;`
- L155 _protected member_ `TSharedPtr<FStreamableHandle> StreamingHandle;`
- L160 _private member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()`

#### struct `AMassSpawner::FSpawnedEntities`  
`struct FSpawnedEntities`  
_L115-119_
- L117 _public member_ `FMassEntityTemplateID TemplateID;`
- L118 _public member_ `TArray<FMassEntityHandle> Entities;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSSPAWNER_API`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMassSpawnerOnSpawningFinishedEvent);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMassSpawnerOnSpawningFinishedEvent);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMassSpawnerOnDespawningFinishedEvent);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMassSpawnerOnDespawningFinishedEvent);`
- L164 _namespace_ `namespace UE`
- L164 _namespace_ `namespace MassSpawner` (scope `UE`)
- L166 _externvar_ `extern float ScalabilitySpawnDensityMultiplier;` (scope `UE::MassSpawner`)

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassSpawnerSubsystem.h` (Public)


#### class `UMassSpawnerSubsystem`  
`class UMassSpawnerSubsystem : public UMassSubsystemBase`  
_L19-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- L24 _public prototype_ `UMassSpawnerSubsystem();`
- L33 _public prototype_ `TSharedPtr<FMassEntityManager::FEntityCreationContext> SpawnEntities(const FMassEntityTemplate& EntityTemplate, const uint32 NumberToSpawn, TArray<FMassEntityHandle>& OutEntities);` — Spawns entities of the kind described by the given EntityTemplate. The spawned entities are fully initialized meaning the EntityTemplate.InitializationPipeline gets run for all spawned entities. @param EntityTemplate template to use for spawning entities @param NumberToSpawn number of entities to spawn @param OutEntities where the IDs of created entities get added. Note that the contents of OutEntities get overridden by the function. @return shared pointer to the entity creation context, that, one released, will cause all the accumulated observers and commands executed
- L35 _public prototype_ `TSharedPtr<FMassEntityManager::FEntityCreationContext> SpawnEntities(FMassEntityTemplateID TemplateID, const uint32 NumberToSpawn, FConstStructView SpawnData, TSubclassOf<UMassProcessor> InitializerClass, TArray<FMassEntityHandle>& OutEntities);`
- L37 _public prototype_ `void DestroyEntities(TConstArrayView<FMassEntityHandle> Entities);`
- L39 _public function_ `const FMassEntityTemplateRegistry& GetTemplateRegistryInstance() const`
- L40 _public function_ `FMassEntityTemplateRegistry& GetMutableTemplateRegistryInstance()`
- L42 _public prototype_ `const FMassEntityTemplate* GetMassEntityTemplate(FMassEntityTemplateID TemplateID) const;`
- L44 _public function_ `FMassEntityManager& GetEntityManagerChecked()`
- L52 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UWorldSubsystem BEGIN
- L53 _protected prototype_ `virtual void Deinitialize() override;`
- L56 _protected prototype_ `TSharedPtr<FMassEntityManager::FEntityCreationContext> DoSpawning(const FMassEntityTemplate& EntityTemplate, const int32 NumToSpawn, FConstStructView SpawnData, TSubclassOf<UMassProcessor> InitializerClass, TArray<FMassEntityHandle>& OutEntities);`
- L58 _protected prototype_ `UMassProcessor* GetSpawnDataInitializer(TSubclassOf<UMassProcessor> InitializerClass);`
- L61 _protected member_ `TArray<TObjectPtr<UMassProcessor>> SpawnDataInitializers;` — `UPROPERTY()`
- L63 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L65 _protected member_ `FMassEntityTemplateRegistry TemplateRegistryInstance;`

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassSpawnerTypes.h` (Public)


#### struct `FMassTransformsSpawnData`  
`struct FMassTransformsSpawnData`  
_L24-43_
- reflection: `USTRUCT()`
- L28 _public function_ `FMassTransformsSpawnData() : bRandomize(true)`
- L33 _public typedef_ `using FTransformsContainerType = TArray<FTransform>;` — declaring the type used to be able to statically test it against other types
- L34 _public member_ `FTransformsContainerType Transforms;`
- L42 _public member_ `bool bRandomize : 1;` — When true, Transforms will be assigned to entities as if pre-shuffled. If Transforms >= Entities, this provides the best chance for a good spread of entity transforms and transforms choices will be guaranteed unique. If Transforms < Entities, the same transform will be used for multiple entities and a warning logged. When false, Transforms will be assigned in order to spawned entities.

#### struct `FMassSpawnedEntityType`  
`struct FMassSpawnedEntityType`  
_L49-75_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes an entity type to spawn.
- L55 _public member_ `TSoftObjectPtr<UMassEntityConfigAsset> EntityConfig;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mass|Spawn")` — Asset that describes the entity
- L59 _public member_ `float Proportion = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mass|Spawn", meta = (ClampMin = 0.0f, UIMin = 0.0f))` — Proportion of the count that should be this agent type, (the proportions will be normalized with other sibling agent types)
- L61 _public function_ `bool IsLoaded() const`
- L63 _public function_ `void UnloadEntityConfig()`
- L69 _public prototype_ `const UMassEntityConfigAsset* GetEntityConfig() const;`
- L70 _public prototype_ `UMassEntityConfigAsset* GetEntityConfig();`
- L74 _private member_ `mutable TObjectPtr<UMassEntityConfigAsset> EntityConfigPtr = nullptr;` — `UPROPERTY(Transient)`

#### struct `FMassSpawnDataGenerator`  
`struct FMassSpawnDataGenerator`  
_L78-95_
- reflection: `USTRUCT(BlueprintType)`
- L84 _public member_ `TSubclassOf<UMassEntitySpawnDataGeneratorBase> GeneratorClass;` — `UPROPERTY()` — The Generator to use to generate the spawn the points
- L87 _public member_ `TObjectPtr<UMassEntitySpawnDataGeneratorBase> GeneratorInstance = nullptr;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Category = "Mass|Generator")`
- L91 _public member_ `float Proportion = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mass|Generator", meta = (ClampMin = 0.0f, UIMin = 0.0f))` — Proportion of the spawn points that should be generated by this generator, (the proportions will be normalized with other sibling generators)
- L94 _public member_ `bool bDataGenerated = false;` — Runtime value to know if we received the generated data for this generator

#### struct `FReplicationTemplateIDFragment`  
`struct FReplicationTemplateIDFragment : public FMassFragment`  
_L98-104_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L103 _public member_ `FMassEntityTemplateID ID;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassSpawner, Warning, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassSpawner, Warning, All);`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MassSpawner` (scope `UE`)
- L20 _prototype_ `uint32 HashTraits(TConstArrayView<UMassEntityTraitBase*> CombinedTraits);` (scope `UE::MassSpawner`)

### `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassTranslator.h` (Public)


#### enum `EMassTranslationDirection`  
`enum class EMassTranslationDirection : uint8`  
_L13-20_
- reflection: `UENUM()`
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `InitializationOnly = 1`
- L17 _public enumerator_ `ActorToMass = 1 << 1`
- L18 _public enumerator_ `MassToActor = 1 << 2`
- L19 _public enumerator_ `BothWays = ActorToMass | MassToActor`

#### class `UMassTranslator`  
`class UMassTranslator : public UMassProcessor`  
_L29-60_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UMassProcessor`
- desc: A class that's responsible for translation between UObjects and Mass. A translator knows how to initialize fragments related to the UClass that the given translator cares about. It can also be used at runtime to copy values from UObjects to fragments and back.
- L34 _protected prototype_ `UMassTranslator();`
- L43 _public function_ `void AppendRequiredTags(FMassTagBitSet& InOutTags) const` — `UE_DEPRECATED(5.8, "This function is deprecated, please fetch the tags directly with GetRequiredTags and append then wherever you want.")` — Fetches the FMassTag-derived types required by this Translator. And entity needs these tags to be processed by this Translator instance. @todo might want this function on the MassProcessor level. TBD @param InOutTags - this translator's expected tags will be added to this parameter
- L48 _public function_ `FMassTagBitSet GetRequiredTags() const`
- L54 _protected prototype_ `void AddRequiredTagsToQuery(FMassEntityQuery& EntityQuery);`
- L59 _protected member_ `FMassTagBitSet RequiredTags;` — These are the tag fragments expected by this translator that let other code (like entity traits) hint to the system which translators they'd want their entity to be processed by.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSSPAWNER_API`
- L21 _prototype_ `ENUM_CLASS_FLAGS(EMassTranslationDirection);`
