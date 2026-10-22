# Runtime / MassEntity

- module root: `Source/Runtime/MassEntity`
- headers: 58; symbols: 4243
- symbol kinds: class=23, delegate=12, enum=46, enumerator=155, externvar=4, function=1266, macro=102, member=784, namespace=126, prototype=1389, struct=203, typedef=128, variable=5
- DynamicallyLoadedModuleNames: MassEntityTestSuite
- PrivateDependencyModuleNames: EditorSubsystem, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, MassCore, TraceLog

### `Source/Runtime/MassEntity/Internal/MassArchetypeData.h` (Internal)


#### struct `UE::Mass::FChunkSparseElements`  
`struct FChunkSparseElements`  
_L30-162_
- L32 _public prototype_ `FChunkSparseElements() = default;`
- L33 _public function_ `FChunkSparseElements(const uint32 NumEntitiesPerChunk)`
- L38 _public function_ `void Init(const uint32 NumEntitiesPerChunk)`
- L44 _public prototype_ `bool Add(const FMassRawEntityInChunkData& EntityInChunkHandle, TNotNull<const UScriptStruct*> ElementType);` — @return whether it is the first instance of ElementType added to this chunk, i.e. SparseElementsPresent has been modified
- L46 _public prototype_ `bool Remove(const FMassRawEntityInChunkData& EntityInChunkHandle, TNotNull<const UScriptStruct*> ElementType);` — @return whether it is the last instance of ElementType removes from this chunk, i.e. SparseElementsPresent has been modified
- L48 _public prototype_ `bool UpdateElementsPresenceOnEntityRemoval(const int32 IndexWithinChunk);` — @return whether SparseElementsPresent has been modified
- L51 _public prototype_ `bool BatchAdd(TNotNull<const UScriptStruct*> ElementType, int32 SubchunkStart, int32 RangeLength);` — @return whether these are the first instances of ElementType added to this chunk, i.e. SparseElementsPresent has been modified
- L53 _public prototype_ `bool BatchRemove(TNotNull<const UScriptStruct*> ElementType, int32 SubchunkStart, int32 RangeLength);` — @return whether these are the last instances of ElementType removed this chunk, i.e. SparseElementsPresent has been modified
- L55 _public function_ `bool IsEmpty() const`
- L60 _public prototype_ `bool Contains(const FMassRawEntityInChunkData& EntityInChunkHandle, TNotNull<const UScriptStruct*> ElementType) const;`
- L62 _public function_ `bool Contains(TNotNull<const UScriptStruct*> ElementType) const` — @return whether anything in the chunk potentially has the element
- L67 _public function_ `bool HasElementsInRange(int32 IndexWithinChunk, int32 Num) const`
- L85 _public prototype_ `bool MoveElementsFrom(FChunkSparseElements& OriginalSparseElements, int32 OriginalIndexWithinChunk, int32 NewIndexWithinChunk, int32 Num);` — Moves Num sparse elements bitsets from OriginalSparseElements, starting at index OriginalIndexWithinChunk to `this` FChunkSparseElements instances, starting at index NewIndexWithinChunk @return true if any bits have been added to or remove from SparseElementsPresent, both from `this` and OriginalSparseElements (if it's not the same).
- L87 _public function_ `const FMassElementBitSet& GetSparseElementsPresent() const`
- L92 _public function_ `FMassElementBitSet& GetElementsForEntity(const FMassRawEntityInChunkData& EntityInChunkHandle)`
- L98 _public function_ `const FMassElementBitSet& GetElementsForEntity(const FMassRawEntityInChunkData& EntityInChunkHandle) const`
- L104 _public function_ `FMassElementBitSet& GetElementsForEntityUnsafe(const int32 Index)`
- L115 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Reports the size of memory allocations owned by this instance, including the per-entity bitset payloads and the FElementCounter dense arrays. Returns 0 when the instance has not been initialized (i.e. IsEmpty() == true).
- L118 _private member_ `FMassElementBitSet SparseElementsPresent;`
- L119 _private member_ `TArray<FMassElementBitSet> PerEntityElements;`
- L161 _private member_ `FElementCounter SparseElementTypesCount;`

#### struct `UE::Mass::FChunkSparseElements::FElementCounter`  
`struct FElementCounter`  
_L121-160_
- L123 _public function_ `uint16& Get(const int32 TypeIndex)`
- L151 _public function_ `SIZE_T GetAllocatedSize() const`
- L157 _private member_ `int32 LastAccessedDenseIndex = INDEX_NONE;`
- L158 _private member_ `TArray<uint16, TInlineAllocator<16>> DenseCounters;`
- L159 _private member_ `TArray<uint16, TInlineAllocator<16>> DenseIndexToElementIndex;`

#### struct `FMassArchetypeChunk`  
`struct FMassArchetypeChunk`  
_L166-359_
- desc: This type represents a single chunk within an archetype
- L169 _private member_ `uint8* RawMemory = nullptr;`
- L170 _private member_ `SIZE_T AllocSize = 0;`
- L171 _private member_ `int32 NumInstances = 0;`
- L172 _private member_ `int32 SerialModificationNumber = 0;`
- L173 _private member_ `TArray<FInstancedStruct> ChunkFragmentData;`
- L174 _private member_ `FMassArchetypeSharedFragmentValues SharedFragmentValues;`
- L175 _private member_ `TArray<uint16, TInlineAllocator<256>> ElementTypeCounts;`
- L176 _private member_ `UE::Mass::FChunkSparseElements SparseElements;`
- L179 _public function_ `explicit FMassArchetypeChunk(const SIZE_T InAllocSize, TConstArrayView<FInstancedStruct> InChunkFragmentTemplates, const FMassArchetypeSharedFragmentValues& InSharedFragmentValues) : AllocSize(InAllocSize) , ChunkFragmentData(InChunkFragmentTemplates) , SharedFragmentValues(InSharedFragmentValues)`
- L189 _public function_ `~FMassArchetypeChunk()`
- L200 _public function_ `FMassEntityHandle& GetEntityArrayElementRef(int32 ChunkBase, int32 IndexWithinChunk)` — Returns the Entity array element at the specified index
- L208 _public function_ `const FMassEntityHandle* GetEntityArray(int32 ChunkBase) const`
- L216 _public function_ `uint8* GetRawMemory() const`
- L221 _public function_ `int32 GetNumInstances() const`
- L226 _public function_ `bool HasSparseElements() const`
- L231 _public function_ `UE::Mass::FChunkSparseElements& GetSparseElements(const uint32 NumEntitiesPerChunk)`
- L245 _public function_ `UE::Mass::FChunkSparseElements& GetSparseElementsUnsafe()` — Note that the returned FChunkSparseElements instance might not be initialized. It's caller's responsibility to call FChunkSparseElements.IsEmpty to verify the instance's state. Call GetSparseElements(uint32) if you need a guaranteed initialized instance.
- L251 _public function_ `const UE::Mass::FChunkSparseElements& GetSparseElementsUnsafe() const` — The caller is responsible for checking whether SparseElements.IsEmpty
- L261 _public function_ `SIZE_T GetAllocatedSize() const` — Reports the size of memory allocations owned by this chunk, excluding the raw chunk buffer (which is accounted for separately via FMassArchetypeData::GetChunkAllocSize). Currently covers the per-chunk SparseElements bookkeeping.
- L266 _public function_ `bool DoesMatchComposition(const FMassElementBitSet& RequiredAllSparseElements, const FMassElementBitSet& RequiredAnySparseElements) const`
- L276 _public function_ `void AddMultipleInstances(uint32 Count)`
- L282 _public function_ `void RemoveMultipleInstances(uint32 Count)`
- L297 _public function_ `void AddInstance()`
- L302 _public function_ `void RemoveInstance()`
- L307 _public function_ `int32 GetSerialModificationNumber() const`
- L312 _public function_ `FStructView GetMutableChunkFragmentViewChecked(const int32 Index)`
- L317 _public function_ `FInstancedStruct* FindMutableChunkFragment(const UScriptStruct* Type)`
- L325 _public function_ `void Recycle(TConstArrayView<FInstancedStruct> InChunkFragmentsTemplate, const FMassArchetypeSharedFragmentValues& InSharedFragmentValues)`
- L339 _public function_ `bool IsValidSubChunk(const int32 StartIndex, const int32 Length) const`
- L345 _public function_ `int32 DebugGetChunkFragmentCount() const`
- L351 _public function_ `FMassArchetypeSharedFragmentValues& GetMutableSharedFragmentValues()`
- L355 _public function_ `const FMassArchetypeSharedFragmentValues& GetSharedFragmentValues() const`

#### struct `FMassArchetypeFragmentConfig`  
`struct FMassArchetypeFragmentConfig`  
_L362-371_
- desc: Information for a single fragment type in an archetype
- L364 _public member_ `const UScriptStruct* FragmentType = nullptr;`
- L365 _public member_ `int32 ArrayOffsetWithinChunk = 0;`
- L367 _public function_ `void* GetFragmentData(uint8* ChunkBase, int32 IndexWithinChunk) const`

#### struct `FMassArchetypeData`  
`struct FMassArchetypeData`  
_L375-874_
- desc: An archetype is defined by a collection of unique fragment types (no duplicates). Order doesn't matter, there will only ever be one FMassArchetypeData per unique set of fragment types per entity manager subsystem
- L379 _private member_ `FMassElementBitSet CompositionBitSet;` — One-stop-shop variable describing composition of entities hosted by the archetype
- L380 _private member_ `mutable FMassElementBitSet CachedSparseElementsBitSet;`
- L383 _private member_ `TArray<FInstancedStruct> ChunkFragmentsTemplate;` — Pre-created default chunk fragment templates
- L385 _private member_ `TArray<FMassArchetypeFragmentConfig, TInlineAllocator<16>> FragmentConfigs;`
- L387 _private member_ `TArray<FMassArchetypeChunk> Chunks;`
- L392 _private member_ `TMap<int32, int32> EntityMap;` — Entity ID to index within archetype @TODO: Could be folded into FEntityData in the entity manager at the expense of a bit of loss of encapsulation and extra complexity during archetype changes
- L394 _private member_ `TMap<const UScriptStruct*, int32> FragmentIndexMap;`
- L396 _private member_ `UE::Mass::FArchetypeGroups Groups;`
- L398 _private member_ `int32 NumEntitiesPerChunk;`
- L399 _private member_ `uint32 TotalBytesPerEntity = 0;`
- L400 _private member_ `int32 EntityListOffsetWithinChunk;`
- L406 _private member_ `uint32 CreatedArchetypeDataVersion = 0;` — Archetype version at which this archetype was created, useful for query to do incremental archetype matching. Note that it's set once and never changed afterward.
- L413 _private member_ `uint32 ArchetypeVersion = 0;` — The current version of this archetype, this value is incremented whenever an entity is added to or removed from this archetype and when any operation modifies the order of hosted entities (e.g compaction). This value can be checked to see if the archetype has changed in any way after an operation.
- L421 _private member_ `uint32 EntityOrderVersion = 0;` — Incremented whenever an operation modifies the order of hosted entities, for example entity removal and compaction. Unlike ArchetypeVersion - this value is only incremented when the order changes. E.g adding an entity to the archetype will not increment this value since it does not modify entity order. This value is used to validate stored entity ranges, including FMassArchetypeEntityCollection.
- L424 _private member_ `const uint32 ChunkMemorySize = 0;` — Defaults to UMassEntitySettings.ChunkMemorySize. In near future will support being set via constructor.
- L430 _private member_ `UE::Mass::FSparseElementsStorage* SparseElementsStorage = nullptr;` — Points to the EntityManager-owned SparseElementsStorage. This is why it's safe to use a raw pointer here, because that's the manager that the sole owner and creator of FMassArchetypeData instances
- L432 _private prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(ChunkIterationDetector);`
- L434 _private member_ `mutable bool bSparseElementsBitSetDirty = false;`
- L438 _private member_ `TArray<FName> DebugNames;` — Arrays of names the archetype is referred as.
- L445 _private member_ `FColor DebugColor;` — Color to be used when representing this archetype. If not set with FMassArchetypeCreationParams will be deterministically set based on archetype's composition. Can be overridden at any point via SetDebugColor.
- L453 _public prototype_ `explicit FMassArchetypeData(const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());`
- L455 _public function_ `TConstArrayView<FMassArchetypeFragmentConfig> GetFragmentConfigs() const`
- L459 _public prototype_ `const FMassElementBitSet& GetCompositionBitSet() const;`
- L460 _public prototype_ `FMassArchetypeCompositionDescriptor GetCompositionDescriptor() const;`
- L462 _public function_ `FORCEINLINE const FMassArchetypeSharedFragmentValues& GetSharedFragmentValues(int32 EntityIndex) const`
- L469 _public function_ `FORCEINLINE const FMassArchetypeSharedFragmentValues& GetSharedFragmentValues(FMassEntityHandle Entity) const`
- L474 _public prototype_ `const UE::Mass::FArchetypeGroups& GetGroups() const;`
- L475 _public prototype_ `bool IsInGroup(const UE::Mass::FArchetypeGroupHandle GroupHandle) const;`
- L476 _public prototype_ `bool IsInGroupOfType(const UE::Mass::FArchetypeGroupType GroupType) const;`
- L479 _public prototype_ `void ForEachFragmentType(TFunction< void(const UScriptStruct* )> Function) const;` — Method to iterate on all the fragment types
- L484 _public function_ `bool HasFragmentType(const UScriptStruct* FragmentType) const` — checks whether a given fragment type is part of this archetype's entities' composition
- L493 _public function_ `bool HasTagType(const UScriptStruct* TagType) const` — checks whether a given tag type is part of this archetype's entities' composition
- L502 _public function_ `bool HasElement(TNotNull<const UScriptStruct*> ElementType) const` — checks whether a given element type is part of this archetype's entities' composition
- L507 _public function_ `bool DoesContainEntitiesWithSparseElement(const UScriptStruct* ElementType) const`
- L512 _public prototype_ `bool IsEquivalent(const FMassElementBitSet& OtherCompositionBitSet, const UE::Mass::FArchetypeGroups& OtherGroups) const;`
- L514 _public prototype_ `void Initialize(const FMassEntityManager& EntityManager, const FMassElementBitSet& InCompositionBitSet , const uint32 ArchetypeDataVersion, UE::Mass::FSparseElementsStorage& InSparseElementsStorage);`
- L521 _public prototype_ `void InitializeWithSimilar(const FMassEntityManager& EntityManager, const FMassArchetypeData& BaseArchetype , FMassElementBitSet&& InCompositionBitSet, const UE::Mass::FArchetypeGroups& InGroups, const uint32 ArchetypeDataVersion , UE::Mass::FSparseElementsStorage& InSparseElementsStorage);` — A special way of initializing an archetype resulting in a copy of BaseArchetype's setup with OverrideTags replacing original tags of BaseArchetype
- L525 _public prototype_ `void AddEntity(FMassEntityHandle Entity, const FMassArchetypeSharedFragmentValues& InSharedFragmentValues);`
- L526 _public prototype_ `void RemoveEntity(FMassEntityHandle Entity);`
- L532 _public prototype_ `FStructView AddSparseElementToEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType);` — @return if ElementType is a tag the function will return an empty struct view. Otherwise, the function will return a valid view to the element owned by the entity, provided it does own one, or an empty view otherwise.
- L534 _public prototype_ `void RemoveSparseElementFromEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType);` — Works with all sparse element types (fragments and tags).
- L536 _public prototype_ `void RemoveSparseElementFromEntity(FMassEntityHandle EntityHandle, const FMassElementBitSet& SparseElementsBitSet);` — Removes all sparse elements indicated by SparseElementsBitSet from the given entity. Works with all sparse element types (fragments and tags).
- L540 _public prototype_ `FStructView GetMutableSparseElementDataForEntity(TNotNull<const UScriptStruct*> ElementType, const FMassEntityHandle EntityHandle) const;` — Expects non-tag sparse element type. Will assert if the assumption is broken. @todo this method is const but returns mutable data (const doesn't propagate through the SparseElementsStorage raw pointer indirection). Consider making non-const to match GetMutableFragmentDataForEntity's convention.
- L542 _public prototype_ `FConstStructView GetSparseElementDataForEntity(TNotNull<const UScriptStruct*> ElementType, const FMassEntityHandle EntityHandle) const;` — Expects non-tag sparse element type. Will assert if the assumption is broken.
- L544 _public prototype_ `FMassElementBitSet GetSparseElementsBitSetForEntity(const FMassEntityHandle EntityHandle) const;` — @return a bitset indicating all sparse elements (both tags and fragments) owned by the given entity
- L546 _public prototype_ `void* GetMutableFragmentDataForEntityChecked(TNotNull<const UScriptStruct*> FragmentType, const FMassEntityHandle EntityHandle);`
- L547 _public prototype_ `void* GetMutableFragmentDataForEntity(TNotNull<const UScriptStruct*> FragmentType, const FMassEntityHandle EntityHandle);`
- L548 _public prototype_ `const void* GetFragmentDataForEntityChecked(TNotNull<const UScriptStruct*> FragmentType, const FMassEntityHandle EntityHandle) const;`
- L549 _public prototype_ `const void* GetFragmentDataForEntity(TNotNull<const UScriptStruct*> FragmentType, const FMassEntityHandle EntityHandle) const;`
- L551 _public prototype_ `bool HasSparseElementForEntity(TNotNull<const UScriptStruct*> ElementType, const FMassEntityHandle EntityHandle) const;`
- L552 _public prototype_ `bool HasSparseElementForEntity(TNotNull<const UScriptStruct*> ElementType, const FMassEntityInChunkDataHandle& EntityInChunkHandle) const;`
- L553 _public prototype_ `bool DoesEntityMatchSparseComposition(const FMassEntityInChunkDataHandle& EntityInChunkHandle , const FMassElementBitSet& RequiredAllSparseElements , const FMassElementBitSet& RequiredAnySparseElements , const FMassElementBitSet& RequiredNoneSparseElements) const;`
- L557 _public prototype_ `bool ContainsAnySparseData() const;`
- L558 _public prototype_ `bool ContainsSparseElement(TNotNull<const UScriptStruct*> ElementType) const;`
- L559 _public prototype_ `const FMassElementBitSet& GetSparseElementsBitSet() const;`
- L561 _public function_ `FORCEINLINE const int32* GetInternalIndexForEntity(const int32 EntityIndex) const`
- L565 _public function_ `FORCEINLINE int32 GetInternalIndexForEntityChecked(const int32 EntityIndex) const`
- L569 _public function_ `int32 GetNumEntitiesPerChunk() const`
- L573 _public function_ `SIZE_T GetBytesPerEntity() const`
- L578 _public function_ `int32 GetNumEntities() const`
- L583 _public function_ `SIZE_T GetChunkAllocSize() const`
- L588 _public function_ `int32 GetChunkCount() const`
- L592 _public prototype_ `int32 GetNonEmptyChunkCount() const;`
- L594 _public function_ `FORCEINLINE static int32 CalculateRangeLength(FMassArchetypeEntityCollection::FArchetypeEntityRange EntityRange, const FMassArchetypeChunk& Chunk)`
- L601 _public function_ `int32 CalculateRangeLength(FMassArchetypeEntityCollection::FArchetypeEntityRange EntityRange) const`
- L608 _public prototype_ `uint32 GetCreatedArchetypeDataVersion() const;`
- L609 _public prototype_ `uint32 GetEntityOrderVersion() const;`
- L610 _public prototype_ `uint32 GetArchetypeVersion() const;`
- L612 _public prototype_ `void ExecuteFunction(FMassExecutionContext& RunContext, const FMassExecuteFunction& Function, const FMassQueryRequirementIndicesMapping& RequirementMapping , FMassArchetypeEntityCollection::FConstEntityRangeArrayView EntityRangeContainer, const FMassChunkConditionFunction& ChunkCondition);`
- L614 _public prototype_ `void ExecuteFunction(FMassExecutionContext& RunContext, const FMassExecuteFunction& Function, const FMassQueryRequirementIndicesMapping& RequirementMapping , const FMassChunkConditionFunction& ChunkCondition, UE::Mass::FExecutionLimiter* ExecutionLimiter = nullptr);`
- L617 _public prototype_ `void ExecutionFunctionForChunk(FMassExecutionContext& RunContext, const FMassExecuteFunction& Function, const FMassQueryRequirementIndicesMapping& RequirementMapping , const FMassArchetypeEntityCollection::FArchetypeEntityRange& EntityRange, const FMassChunkConditionFunction& ChunkCondition = FMassChunkConditionFunction());`
- L624 _public prototype_ `int32 CompactEntities(const double TimeAllowed);` — Compacts entities to fill up chunks as much as possible @return number of entities moved around
- L633 _public prototype_ `void MoveEntityToAnotherArchetype(FMassEntityHandle Entity, FMassArchetypeData& NewArchetype, const FMassArchetypeSharedFragmentValues* SharedFragmentValuesOverride = nullptr);` — Moves the entity from this archetype to another, will only copy all matching fragment types. Uses an internally-cached fragment index mapping for the source->target archetype pair. @param Entity is the entity to move @param NewArchetype the archetype to move to @param SharedFragmentValuesOverride if provided will override all given Entity's shared fragment values
- L641 _public prototype_ `template<typename TStruct> void SetFragmentsData(const FMassEntityHandle Entity, TConstArrayView<TStruct> FragmentSources);` — Set all fragment sources data on specified entity, will check if there are fragment sources type that does not exist in the archetype @param Entity is the entity to set the data of all fragments @param FragmentSources are the fragments to copy the data from
- L648 _public prototype_ `template<typename TStruct> void SetFragmentData(FMassArchetypeEntityCollection::FConstEntityRangeArrayView EntityRangeContainer, const TStruct& FragmentSource);` — For all entities indicated by EntityCollection the function sets the value of fragment of type FragmentSource.GetScriptStruct to the value represented by FragmentSource.GetMemory
- L651 _public prototype_ `void GetRequirementsFragmentMapping(TConstArrayView<FMassFragmentRequirementDescription> Requirements, FMassFragmentIndicesMapping& OutFragmentIndices) const;` — Returns conversion from given Requirements to archetype's fragment indices
- L654 _public prototype_ `void GetRequirementsChunkFragmentMapping(TConstArrayView<FMassFragmentRequirementDescription> ChunkRequirements, FMassFragmentIndicesMapping& OutFragmentIndices) const;` — Returns conversion from given ChunkRequirements to archetype's chunk fragment indices
- L657 _public prototype_ `void GetRequirementsConstSharedFragmentMapping(TConstArrayView<FMassFragmentRequirementDescription> Requirements, FMassFragmentIndicesMapping& OutFragmentIndices) const;` — Returns conversion from given const shared requirements to archetype's const shared fragment indices
- L660 _public prototype_ `void GetRequirementsSharedFragmentMapping(TConstArrayView<FMassFragmentRequirementDescription> Requirements, FMassFragmentIndicesMapping& OutFragmentIndices) const;` — Returns conversion from given shared requirements to archetype's shared fragment indices
- L662 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L665 _public prototype_ `SIZE_T GetSparseElementsBookkeepingAllocatedSize() const;` — Sum of FChunkSparseElements::GetAllocatedSize across all chunks; subset of GetAllocatedSize.
- L667 _public prototype_ `void ExportEntityHandles(const TConstArrayView<FMassArchetypeEntityCollection::FArchetypeEntityRange> Ranges, TArray<FMassEntityHandle>& InOutHandles) const;`
- L669 _public prototype_ `void ExportEntityHandles(TArray<FMassEntityHandle>& InOutHandles) const;`
- L671 _public prototype_ `void ListEntitiesForEachChunk(TFunctionRef<void(TConstArrayView<FMassEntityHandle>)> Function) const;`
- L674 _public prototype_ `FString DebugGetDescription() const;` — Converts the list of fragments into a user-readable debug string
- L677 _public function_ `void CopyDebugNamesFrom(const FMassArchetypeData& Other)` — Copies debug names from another archetype data.
- L686 _public prototype_ `void DebugGetEntityMemoryNumbers(SIZE_T& OutActiveChunksMemorySize, SIZE_T& OutActiveEntitiesMemorySize) const;` — Fetches how much memory is allocated for active chunks, and how much of that memory is actually occupied
- L689 _public function_ `void AddUniqueDebugName(const FName& Name)` — Adds new debug name associated with the archetype.
- L695 _public function_ `bool IsUnnamedArchetype() const` — Whether the archetype was created using the default name (NAME_None)
- L701 _public function_ `TConstArrayView<FName> GetDebugNames() const` — @return array of debug names associated with this archetype.
- L709 _public prototype_ `FString GetCombinedDebugNamesAsString() const;` — @return string of all debug names combined
- L714 _public prototype_ `void DebugPrintArchetype(FOutputDevice& Ar);` — Prints out debug information about the archetype
- L722 _public prototype_ `void DebugPrintEntity(FMassEntityHandle Entity, FOutputDevice& Ar, const TCHAR* InPrefix = TEXT("")) const;` — Prints out fragment's values for the specified entity. @param Entity The entity for which we want to print fragment values @param Ar The output device @param InPrefix Optional prefix to remove from fragment names
- L724 _public prototype_ `const FMassArchetypeChunk& DebugGetChunk(const int32 Index) const;`
- L727 _public prototype_ `void SetDebugColor(const FColor InDebugColor);`
- L729 _public prototype_ `void REMOVEME_GetArrayViewForFragmentInChunk(int32 ChunkIndex, const UScriptStruct* FragmentType, void*& OutChunkBase, int32& OutNumEntities);`
- L733 _public function_ `FORCEINLINE const int32* GetFragmentIndex(const UScriptStruct* FragmentType) const` — low level api
- L737 _public function_ `FORCEINLINE int32 GetFragmentIndexChecked(const UScriptStruct* FragmentType) const`
- L742 _public function_ `FORCEINLINE void* GetFragmentData(const int32 FragmentIndex, const FMassRawEntityInChunkData RawEntityInChunkHandle) const`
- L747 _public function_ `FORCEINLINE bool IsValidHandle(const FMassEntityInChunkDataHandle Handle) const`
- L752 _public function_ `FORCEINLINE void* GetFragmentData(const int32 FragmentIndex, const FMassEntityInChunkDataHandle EntityInChunkHandle) const`
- L758 _public function_ `FORCEINLINE FMassRawEntityInChunkData MakeRawEntityHandle(int32 EntityIndex) const`
- L766 _public function_ `FORCEINLINE FMassRawEntityInChunkData MakeRawEntityHandle(const FMassEntityHandle Entity) const`
- L771 _public function_ `FORCEINLINE FMassEntityInChunkDataHandle MakeEntityHandle(int32 EntityIndex) const`
- L782 _public function_ `FORCEINLINE FMassEntityInChunkDataHandle MakeEntityHandle(const FMassEntityHandle Entity) const`
- L787 _public function_ `bool IsInitialized() const`
- L794 _public prototype_ `void BatchDestroyEntityChunks(FMassArchetypeEntityCollection::FConstEntityRangeArrayView EntityRangeContainer, TArray<FMassEntityHandle>& OutEntitiesRemoved);` — batched api
- L795 _public prototype_ `void BatchAddEntities(TConstArrayView<FMassEntityHandle> Entities, const FMassArchetypeSharedFragmentValues& SharedFragmentValues , TArray<FMassArchetypeEntityCollection::FArchetypeEntityRange>& OutNewRanges);`
- L800 _public prototype_ `void BatchMoveEntitiesToAnotherArchetype(const FMassArchetypeEntityCollection& EntityCollection, FMassArchetypeData& NewArchetype , TArray<FMassEntityHandle>& OutEntitiesBeingMoved, TArray<FMassArchetypeEntityCollection::FArchetypeEntityRange>* OutNewChunks = nullptr , const FMassArchetypeSharedFragmentValues* SharedFragmentValuesToAdd = nullptr , const FMassSharedFragmentBitSet* SharedFragmentToRemoveBitSet = nullptr , const FMassConstSharedFragmentBitSet* ConstSharedFragmentToRemoveBitSet = nullptr);` — @param SharedFragmentValuesOverride if provided will override shared fragment values for the entities being moved
- L805 _public prototype_ `void BatchSetFragmentValues(TConstArrayView<FMassArchetypeEntityCollection::FArchetypeEntityRange> EntityCollection, const FMassGenericPayloadViewSlice& Payload);`
- L808 _public prototype_ `void BatchAddSparseElementToEntities(const FMassArchetypeEntityCollection& EntityCollection, TNotNull<const UScriptStruct*> ElementType);` — Works with all sparse element types (fragments and tags).
- L810 _public prototype_ `void BatchRemoveSparseElementFromEntities(const FMassArchetypeEntityCollection& EntityCollection, TNotNull<const UScriptStruct*> ElementType);` — Works with all sparse element types (fragments and tags).
- L816 _public prototype_ `SetSharedFragmentsData(Entity, MakeArrayView(SharedFragmentValueOverrides));`
- L832 _public member_ `FMassEntityInChunkDataHandle EntityInChunkHandle = MakeEntityHandle(Entity.Index);`
- L837 _public prototype_ `NewSharedFragmentValues.Sort();`
- L839 _public prototype_ `SetSharedFragmentsData(Entity, EntityInChunkHandle, MoveTemp(NewSharedFragmentValues));`
- L843 _protected prototype_ `void SetSharedFragmentsData(FMassEntityHandle Entity, FMassEntityInChunkDataHandle EntityInChunkHandle, FMassArchetypeSharedFragmentValues&& SharedFragmentValues);`
- L845 _protected prototype_ `FMassArchetypeEntityCollection::FArchetypeEntityRange PrepareNextEntitiesSpanInternal(TConstArrayView<FMassEntityHandle> Entities, const FMassArchetypeSharedFragmentValues& InSharedFragmentValues, const int32 StartingChunk = 0);`
- L846 _protected prototype_ `void BatchRemoveEntitiesInternal(const int32 ChunkIndex, const int32 StartIndexWithinChunk, const int32 NumberToRemove);`
- L854 _protected prototype_ `void MoveFragmentsToAnotherArchetypeInternal(FMassArchetypeData& TargetArchetype, FMassArchetypeChunk& TargetChunk, int32 NewIndexWithinChunk , FMassArchetypeChunk& SourceChunk, int32 OriginalIndexWithinChunk, int32 ElementsNum);`
- L856 _protected prototype_ `void MoveFragmentsToNewLocationInternal(FTransientChunkLocation Target, const FTransientChunkLocation Source, const int32 NumberToMove);`
- L857 _protected prototype_ `void ConfigureFragments(const FMassEntityManager& EntityManager);`
- L859 _protected function_ `FORCEINLINE void* GetFragmentData(const int32 FragmentIndex, uint8* ChunkRawMemory, const int32 IndexWithinChunk) const`
- L864 _protected prototype_ `void BindEntityRequirements(FMassExecutionContext& RunContext, const FMassFragmentIndicesMapping& EntityFragmentsMapping, FMassArchetypeChunk& Chunk, const int32 SubchunkStart, const int32 SubchunkLength);`
- L865 _protected prototype_ `void BindChunkFragmentRequirements(FMassExecutionContext& RunContext, const FMassFragmentIndicesMapping& ChunkFragmentsMapping, FMassArchetypeChunk& Chunk);`
- L866 _protected prototype_ `void BindConstSharedFragmentRequirements(FMassExecutionContext& RunContext, const FMassArchetypeSharedFragmentValues& SharedFragmentValues, const FMassFragmentIndicesMapping& ChunkFragmentsMapping);`
- L867 _protected prototype_ `void BindSharedFragmentRequirements(FMassExecutionContext& RunContext, FMassArchetypeSharedFragmentValues& SharedFragmentValues, const FMassFragmentIndicesMapping& ChunkFragmentsMapping);`
- L869 _protected prototype_ `FMassArchetypeChunk& GetOrAddChunk(const FMassArchetypeSharedFragmentValues& SharedFragmentValues, int32& OutAbsoluteIndex, int32& OutIndexWithinChunk);`
- L872 _private prototype_ `int32 AddEntityInternal(FMassEntityHandle Entity, const FMassArchetypeSharedFragmentValues& InSharedFragmentValues);`
- L873 _private prototype_ `void RemoveEntityInternal(const int32 AbsoluteIndex);`
- L912 _function_ `inline const UE::Mass::FArchetypeGroups& FMassArchetypeData::GetGroups() const`
- L917 _function_ `inline bool FMassArchetypeData::IsInGroup(const UE::Mass::FArchetypeGroupHandle GroupHandle) const`
- L927 _function_ `inline bool FMassArchetypeData::IsInGroupOfType(const UE::Mass::FArchetypeGroupType GroupType) const`
- L932 _function_ `inline uint32 FMassArchetypeData::GetCreatedArchetypeDataVersion() const`
- L937 _function_ `inline uint32 FMassArchetypeData::GetEntityOrderVersion() const`
- L942 _function_ `inline uint32 FMassArchetypeData::GetArchetypeVersion() const`
- L947 _function_ `inline const FMassElementBitSet& FMassArchetypeData::GetCompositionBitSet() const`
- L952 _function_ `inline FMassArchetypeCompositionDescriptor FMassArchetypeData::GetCompositionDescriptor() const`
- L958 _function_ `template<typename TStruct> void FMassArchetypeData::SetFragmentsData(const FMassEntityHandle Entity, TConstArrayView<TStruct> FragmentSources)`
- L984 _function_ `template<typename TStruct> void FMassArchetypeData::SetFragmentData(FMassArchetypeEntityCollection::FConstEntityRangeArrayView EntityRangeContainer, const TStruct& FragmentSource)`
- L1035 _function_ `inline bool FMassArchetypeData::ContainsAnySparseData() const`
- L1040 _function_ `inline bool FMassArchetypeData::ContainsSparseElement(TNotNull<const UScriptStruct*> ElementType) const`
- L1045 _function_ `inline const FMassElementBitSet& FMassArchetypeData::GetSparseElementsBitSet() const`

#### struct `FMassArchetypeData::FTransientChunkLocation`  
`struct FTransientChunkLocation`  
_L848-852_
- L850 _public member_ `uint8* RawChunkMemory;`
- L851 _public member_ `int32 IndexWithinChunk;`

#### struct `FMassArchetypeHelper`  
`struct FMassArchetypeHelper`  
_L877-907_
- L879 _public function_ `FORCEINLINE static FMassArchetypeData* ArchetypeDataFromHandle(const FMassArchetypeHandle& ArchetypeHandle)`
- L883 _public function_ `FORCEINLINE static FMassArchetypeData& ArchetypeDataFromHandleChecked(const FMassArchetypeHandle& ArchetypeHandle)`
- L888 _public function_ `FORCEINLINE static FMassArchetypeHandle ArchetypeHandleFromData(const TSharedPtr<FMassArchetypeData>& Archetype)`
- L900 _public prototype_ `static bool DoesArchetypeMatchRequirements(const FMassArchetypeData& Archetype, const FMassFragmentRequirements& Requirements , const bool bBailOutOnFirstFail = true, FOutputDevice* OutputDevice = nullptr);`
- L904 _public prototype_ `static bool DoesArchetypeMatchRequirements(const FMassArchetypeData& Archetype, const FMassFragmentRequirements& Requirements);`
- L905 _public prototype_ `static bool DoesArchetypeMatchRequirements(const FMassArchetypeCompositionDescriptor& ArchetypeComposition, const FMassFragmentRequirements& Requirements);`
- L906 _public prototype_ `static bool DoesArchetypeMatchRequirements(const FMassElementBitSet& ArchetypeCompositionBitSet, const FMassFragmentRequirements& Requirements);`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Mass` (scope `UE`)
- L28 _prototype_ `uint32 SanitizeChunkMemorySize(const uint32 InChunkMemorySize, const bool bLogMismatch = true);` (scope `UE::Mass`)
- L320 _function_ `` (scope `FMassArchetypeChunk::FindMutableChunkFragment`)

### `Source/Runtime/MassEntity/Private/MassEntityManagerConstants.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mass` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mass`)
- L10 _variable_ `constexpr int32 InvalidEntityIndex = 0;` (scope `UE::Mass::Private`) — Index 0 is a sentinel for an Empty/Unset EntityHandle

### `Source/Runtime/MassEntity/Public/MassArchetypeGroup.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MassEntity/Public/MassArchetypeGroupCommands.h` (Public)


#### struct `UE::Mass::Command::FGroupEntities`  
`struct FGroupEntities : public FMassBatchedEntityCommand`  
_L23-51_
- inherits: `FMassBatchedEntityCommand`
- L25 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L26 _public function_ `FGroupEntities() : Super(EMassCommandOperationType::ChangeComposition DEBUG_NAME("GroupEntities"))`
- L30 _public function_ `void Add(FArchetypeGroupHandle GroupHandle, TArray<FMassEntityHandle>&& Entities)`
- L36 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L50 _protected member_ `TMap<FArchetypeGroupHandle, TArray<FMassEntityHandle>> Groups;`

#### Free symbols / members of external scopes

- L9 _macro_ `# define DEBUG_NAME(Name) , FName(TEXT(Name))`
- L10 _macro_ `# define DEBUG_NAME_PARAM(Name) , const FName InDebugName = TEXT(Name)`
- L11 _macro_ `# define FORWARD_DEBUG_NAME_PARAM , InDebugName`
- L13 _macro_ `# define DEBUG_NAME(Name)`
- L14 _macro_ `# define DEBUG_NAME_PARAM(Name)`
- L15 _macro_ `# define FORWARD_DEBUG_NAME_PARAM`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mass` (scope `UE`)
- L18 _namespace_ `namespace Command` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassArchetypeTypes.h` (Public)


#### struct `FMassArchetypeHandle`  
`struct FMassArchetypeHandle final`  
_L40-65_
- desc: An opaque handle to an archetype
- L42 _public prototype_ `FMassArchetypeHandle() = default;`
- L43 _public prototype_ `bool IsValid() const;`
- L45 _public prototype_ `bool operator==(const FMassArchetypeHandle& Other) const;`
- L46 _public prototype_ `bool operator!=(const FMassArchetypeHandle& Other) const;`
- L50 _public prototype_ `void Reset();`
- L55 _public prototype_ `const FMassElementBitSet& GetCompositionBitSetChecked() const;` — Returns the composition bitset for the archetype, asserts if archetype is invalid
- L58 _private prototype_ `FMassArchetypeHandle(const TSharedPtr<FMassArchetypeData>& InDataPtr);`
- L60 _private member_ `TSharedPtr<FMassArchetypeData> DataPtr;`
- L417 _function_ `inline bool FMassArchetypeHandle::IsValid() const`
- L422 _function_ `inline bool FMassArchetypeHandle::operator==(const FMassArchetypeHandle& Other) const`
- L427 _function_ `inline bool FMassArchetypeHandle::operator!=(const FMassArchetypeHandle& Other) const`
- L432 _function_ `inline void FMassArchetypeHandle::Reset()`
- L437 _function_ `inline FMassArchetypeHandle::FMassArchetypeHandle(const TSharedPtr<FMassArchetypeData>& InDataPtr) : DataPtr(InDataPtr)`

#### struct `FMassArchetypeVersionedHandle`  
`struct FMassArchetypeVersionedHandle final`  
_L67-90_
- L69 _public prototype_ `FMassArchetypeVersionedHandle() = default;`
- L70 _public prototype_ `FMassArchetypeVersionedHandle(const FMassArchetypeHandle& InHandle);`
- L71 _public prototype_ `FMassArchetypeVersionedHandle(FMassArchetypeHandle&& InHandle);`
- L73 _public prototype_ `bool IsValid() const;`
- L74 _public prototype_ `bool operator==(const FMassArchetypeVersionedHandle& Other) const;`
- L75 _public prototype_ `bool operator!=(const FMassArchetypeVersionedHandle& Other) const;`
- L76 _public prototype_ `bool IsUpToDate() const;`
- L78 _public prototype_ `operator FMassArchetypeHandle() const;`
- L82 _private member_ `FMassArchetypeHandle ArchetypeHandle;`
- L89 _private member_ `uint32 HandleVersion = 0;` — This value indicates whether the target archetype had its entities moved around since the handle creations. The information is useful in a couple of scenarios (like making sure an entity collection is up to date), but in most cases the users should not concern themselves with this value. Note that the value is not used as part of hash calculation, it's effectively transient.
- L397 _function_ `inline bool FMassArchetypeVersionedHandle::IsValid() const`
- L402 _function_ `inline bool FMassArchetypeVersionedHandle::operator==(const FMassArchetypeVersionedHandle& Other) const`
- L407 _function_ `inline bool FMassArchetypeVersionedHandle::operator!=(const FMassArchetypeVersionedHandle& Other) const`
- L412 _function_ `inline FMassArchetypeVersionedHandle::operator FMassArchetypeHandle() const`

#### struct `FMassArchetypeEntityCollection`  
`struct FMassArchetypeEntityCollection`  
_L99-246_
- desc: A struct that converts an arbitrary array of entities of given Archetype into a sequence of continuous entity chunks. The goal is to have the user create an instance of this struct once and run through a bunch of systems. The runtime code usually uses FMassArchetypeChunkIterator to iterate on the chunk collection.
- L176 _public typedef_ `using FEntityRangeArray = TArray<FArchetypeEntityRange>;`
- L177 _public typedef_ `using FConstEntityRangeArrayView = TConstArrayView<FArchetypeEntityRange>;`
- L180 _private member_ `FEntityRangeArray Ranges;`
- L182 _private member_ `FMassArchetypeVersionedHandle Archetype;` — entity indices indicated by EntityRanges are only valid with given Archetype
- L185 _public prototype_ `FMassArchetypeEntityCollection() = default;`
- L186 _public prototype_ `FMassArchetypeEntityCollection(const FMassArchetypeHandle& InArchetype, TConstArrayView<FMassEntityHandle> InEntities, EDuplicatesHandling DuplicatesHandling);`
- L188 _public prototype_ `FMassArchetypeEntityCollection(const FMassArchetypeHandle& InArchetype, const FMassEntityHandle EntityHandle);` — optimized, special case for a single-entity
- L189 _public prototype_ `FMassArchetypeEntityCollection(FMassArchetypeHandle&& InArchetype, const FMassEntityHandle EntityHandle);`
- L190 _public prototype_ `explicit FMassArchetypeEntityCollection(const FMassArchetypeHandle& InArchetypeHandle, const EInitializationType Initialization = EInitializationType::GatherAll);`
- L191 _public prototype_ `explicit FMassArchetypeEntityCollection(TSharedPtr<FMassArchetypeData>& InArchetype, const EInitializationType Initialization = EInitializationType::GatherAll);`
- L192 _public function_ `FMassArchetypeEntityCollection(const FMassArchetypeHandle& InArchetypeHandle, FEntityRangeArray&& InEntityRanges) : Ranges(Forward<FEntityRangeArray>(InEntityRanges)) , Archetype(InArchetypeHandle)`
- L197 _public prototype_ `FConstEntityRangeArrayView GetRanges() const;`
- L198 _public prototype_ `FMassArchetypeHandle GetArchetype() const;`
- L199 _public prototype_ `bool IsEmpty() const;`
- L200 _public prototype_ `bool IsUpToDate() const;`
- L203 _public prototype_ `bool IsSet() const;` — `UE_DEPRECATED(5.6, "This function is deprecated. Use !IsEmpty() instead.")`
- L205 _public function_ `void Reset()`
- L212 _public prototype_ `bool IsSame(const FMassArchetypeEntityCollection& Other) const;` — The comparison function that checks if Other is identical to this. Intended for diagnostics/debugging.
- L213 _public prototype_ `bool IsSameArchetype(const FMassArchetypeEntityCollection& Other) const;`
- L224 _public prototype_ `template<typename T> requires std::is_same_v<typename TDecay<T>::Type, FMassArchetypeEntityCollection> void Append(T&& Other);` — Appends ranges of the given FMassArchetypeEntityCollection instance. Note that it can be safely done only when both collections host entities of the same archetype, and both were created with the same version of said archetype. Additionally, we don't expect the operation to produce overlapping entity ranges and this assumption is only verified in debug builds (i.e. use it only when you're certain no range overlaps are possible).
- L231 _public prototype_ `bool ExportEntityHandles(TArray<FMassEntityHandle>& InOutHandles) const;` — Converts stored entity ranges to FMassEntityHandles and appends them to InOutHandles. Note that the operation is only supported for already created entities (i.e. not "reserved") @return whether any entity handles have been actually exported
- L233 _public prototype_ `static bool DoesContainOverlappingRanges(FConstEntityRangeArrayView Ranges);`
- L236 _public prototype_ `int32 DebugCountEntities() const;`
- L241 _protected prototype_ `void BuildEntityRanges(TStridedView<const int32> TrueIndices);`
- L242 _protected prototype_ `static FArchetypeEntityRange CreateRangeForEntity(const FMassArchetypeHandle& InArchetype, const FMassEntityHandle EntityHandle);`
- L245 _private prototype_ `void GatherChunksFromArchetype();`
- L443 _function_ `inline FMassArchetypeEntityCollection::FConstEntityRangeArrayView FMassArchetypeEntityCollection::GetRanges() const`
- L448 _function_ `inline FMassArchetypeHandle FMassArchetypeEntityCollection::GetArchetype() const`
- L453 _function_ `inline bool FMassArchetypeEntityCollection::IsEmpty() const`
- L458 _function_ `inline bool FMassArchetypeEntityCollection::IsUpToDate() const`
- L463 _function_ `inline bool FMassArchetypeEntityCollection::IsSet() const`
- L468 _function_ `inline bool FMassArchetypeEntityCollection::IsSameArchetype(const FMassArchetypeEntityCollection& Other) const`
- L475 _function_ `template<typename T> requires std::is_same_v<typename TDecay<T>::Type, FMassArchetypeEntityCollection> void FMassArchetypeEntityCollection::Append(T&& Other)`

#### struct `FMassArchetypeEntityCollection::FArchetypeEntityRange`  
`struct FArchetypeEntityRange`  
_L102-160_
- L104 _public member_ `int32 ChunkIndex = INDEX_NONE;`
- L108 _public member_ `int32 SubchunkStart = 0;` — The index of the first entity within the specified chunk that starts this subchunk.
- L114 _public member_ `int32 Length = 0;` — The number of entities in this subchunk. If Length is 0 or negative, it indicates that the range covers all remaining entities in the chunk starting from SubchunkStart.
- L116 _public prototype_ `FArchetypeEntityRange() = default;`
- L117 _public function_ `explicit FArchetypeEntityRange(const int32 InChunkIndex, const int32 InSubchunkStart = 0, const int32 InLength = 0) : ChunkIndex(InChunkIndex), SubchunkStart(InSubchunkStart), Length(InLength)`
- L122 _public function_ `bool IsSet() const` — Note that we consider invalid-length chunks valid as long as ChunkIndex and SubchunkStart are valid
- L128 _public function_ `bool IsAdjacentAfter(const FArchetypeEntityRange& Other) const` — Checks if given InRange comes right after this instance
- L133 _public function_ `bool IsOverlapping(const FArchetypeEntityRange& Other) const`
- L143 _public function_ `bool operator==(const FArchetypeEntityRange& Other) const`
- L147 _public function_ `bool operator!=(const FArchetypeEntityRange& Other) const`
- L152 _public function_ `bool operator<(const FArchetypeEntityRange& Other) const`

#### enum `FMassArchetypeEntityCollection::EDuplicatesHandling`  
`enum EDuplicatesHandling`  
_L162-168_
- L164 _public enumerator_ `NoDuplicates` — indicates that the caller guarantees there are no duplicates in the input Entities collection
- L166 _public enumerator_ `FoldDuplicates` — note that in no-shipping builds a `check` will fail if duplicates are present.

#### enum `FMassArchetypeEntityCollection::EInitializationType`  
`enum EInitializationType`  
_L170-174_
- L172 _public enumerator_ `GatherAll` — default behavior, makes given FMassArchetypeEntityCollection instance represent all entities of the given archetype
- L173 _public enumerator_ `DoNothing` — meant for procedural population by external code (like child classes)

#### struct `FMassArchetypeEntityCollectionWithPayload`  
`struct FMassArchetypeEntityCollectionWithPayload`  
_L248-278_
- L250 _public function_ `explicit FMassArchetypeEntityCollectionWithPayload(const FMassArchetypeEntityCollection& InEntityCollection) : Entities(InEntityCollection)`
- L255 _public function_ `explicit FMassArchetypeEntityCollectionWithPayload(FMassArchetypeEntityCollection&& InEntityCollection) : Entities(MoveTempIfPossible(InEntityCollection))`
- L260 _public prototype_ `static void CreateEntityRangesWithPayload(const FMassEntityManager& EntityManager, const TConstArrayView<FMassEntityHandle> Entities , const FMassArchetypeEntityCollection::EDuplicatesHandling DuplicatesHandling, FMassGenericPayloadView Payload , TArray<FMassArchetypeEntityCollectionWithPayload>& OutEntityCollections);`
- L264 _public function_ `const FMassArchetypeEntityCollection& GetEntityCollection() const`
- L268 _public function_ `const FMassGenericPayloadViewSlice& GetPayload() const`
- L274 _private prototype_ `FMassArchetypeEntityCollectionWithPayload(const FMassArchetypeHandle& InArchetype, TStridedView<const int32> TrueIndices, FMassGenericPayloadViewSlice&& Payload);`
- L276 _private member_ `FMassArchetypeEntityCollection Entities;`
- L277 _private member_ `FMassGenericPayloadViewSlice PayloadSlice;`

#### struct `FMassArchetypeChunkIterator`  
`struct FMassArchetypeChunkIterator`  
_L287-319_
- desc: The type used to iterate over given archetype's chunks, be it full, continuous chunks or sparse subchunks. It hides this details from the rest of the system.
- L290 _private member_ `FMassArchetypeEntityCollection::FConstEntityRangeArrayView EntityRanges;`
- L291 _private member_ `int32 CurrentChunkIndex = 0;`
- L294 _public function_ `explicit FMassArchetypeChunkIterator(const FMassArchetypeEntityCollection::FConstEntityRangeArrayView& InEntityRanges) : EntityRanges(InEntityRanges), CurrentChunkIndex(0)`
- L299 _public function_ `operator bool() const`
- L303 _public function_ `FMassArchetypeChunkIterator& operator++()`
- L309 _public function_ `const FMassArchetypeEntityCollection::FArchetypeEntityRange* operator->() const`
- L314 _public function_ `const FMassArchetypeEntityCollection::FArchetypeEntityRange& operator*() const`

#### struct `FMassRawEntityInChunkData`  
`struct FMassRawEntityInChunkData`  
_L324-334_
- L326 _public prototype_ `FMassRawEntityInChunkData() = default;`
- L327 _public prototype_ `FMassRawEntityInChunkData(uint8* InChunkRawMemory, const int32 InIndexWithinChunk);`
- L329 _public prototype_ `bool IsSet() const;`
- L330 _public prototype_ `bool operator==(const FMassRawEntityInChunkData& Other) const;`
- L332 _public member_ `uint8* const ChunkRawMemory = nullptr;`
- L333 _public member_ `const int32 IndexWithinChunk = INDEX_NONE;`
- L490 _function_ `inline FMassRawEntityInChunkData::FMassRawEntityInChunkData(uint8* InChunkRawMemory, const int32 InIndexWithinChunk) : ChunkRawMemory(InChunkRawMemory), IndexWithinChunk(InIndexWithinChunk)`
- L494 _function_ `inline bool FMassRawEntityInChunkData::IsSet() const`
- L499 _function_ `inline bool FMassRawEntityInChunkData::operator==(const FMassRawEntityInChunkData & Other) const`

#### struct `FMassEntityInChunkDataHandle`  
`struct FMassEntityInChunkDataHandle : FMassRawEntityInChunkData`  
_L343-361_
- inherits: `FMassRawEntityInChunkData`
- desc: This is an extension of FMassRawEntityInChunkData that provides additional safety features. It can be used to detect that the underlying data has changed.
- L345 _public prototype_ `FMassEntityInChunkDataHandle() = default;`
- L346 _public prototype_ `FMassEntityInChunkDataHandle(FMassEntityInChunkDataHandle&&) = default;`
- L347 _public prototype_ `FMassEntityInChunkDataHandle(const FMassEntityInChunkDataHandle&) = default;`
- L348 _public prototype_ `FMassEntityInChunkDataHandle& operator=(const FMassEntityInChunkDataHandle&);`
- L349 _public prototype_ `FMassEntityInChunkDataHandle& operator=(FMassEntityInChunkDataHandle&&);`
- L350 _public prototype_ `FMassEntityInChunkDataHandle(uint8* InChunkRawMemory, const int32 InIndexWithinChunk, const int32 InChunkIndex, const int32 InChunkSerialNumber);`
- L351 _public prototype_ `FMassEntityInChunkDataHandle(const FMassEntityInChunkDataHandle& Source, const int32 InIndexWithinChunk);`
- L353 _public prototype_ `bool IsValid(const FMassArchetypeData* ArchetypeData) const;`
- L354 _public prototype_ `bool IsValid(const FMassArchetypeHandle& ArchetypeHandle) const;`
- L355 _public prototype_ `bool operator==(const FMassEntityInChunkDataHandle& Other) const;`
- L357 _public prototype_ `int32 GetAbsoluteIndex(const int32 NumEntitiesPerChunk) const;`
- L359 _public member_ `const int32 ChunkIndex = INDEX_NONE;`
- L360 _public member_ `const int32 ChunkSerialNumber = INDEX_NONE;`
- L504 _function_ `inline FMassEntityInChunkDataHandle& FMassEntityInChunkDataHandle::operator=(const FMassEntityInChunkDataHandle& Other)`
- L510 _function_ `inline FMassEntityInChunkDataHandle& FMassEntityInChunkDataHandle::operator=(FMassEntityInChunkDataHandle&& Other)`
- L516 _function_ `inline FMassEntityInChunkDataHandle::FMassEntityInChunkDataHandle(uint8* InChunkRawMemory, const int32 InIndexWithinChunk, const int32 InChunkIndex, const int32 InChunkSerialNumber) : FMassRawEntityInChunkData(InChunkRawMemory, InIndexWithinChunk) , ChunkIndex(InChunkIndex), ChunkSerialNumber(InChunkSerialNumber)`
- L522 _function_ `inline FMassEntityInChunkDataHandle::FMassEntityInChunkDataHandle(const FMassEntityInChunkDataHandle& Source, const int32 InIndexWithinChunk) : FMassRawEntityInChunkData(Source.ChunkRawMemory, InIndexWithinChunk) , ChunkIndex(Source.ChunkIndex), ChunkSerialNumber(Source.ChunkSerialNumber)`
- L528 _function_ `inline bool FMassEntityInChunkDataHandle::operator==(const FMassEntityInChunkDataHandle& Other) const`
- L535 _function_ `inline int32 FMassEntityInChunkDataHandle::GetAbsoluteIndex(const int32 NumEntitiesPerChunk) const`

#### struct `FMassQueryRequirementIndicesMapping`  
`struct FMassQueryRequirementIndicesMapping`  
_L368-380_
- L370 _public prototype_ `FMassQueryRequirementIndicesMapping() = default;`
- L372 _public member_ `FMassFragmentIndicesMapping EntityFragments;`
- L373 _public member_ `FMassFragmentIndicesMapping ChunkFragments;`
- L374 _public member_ `FMassFragmentIndicesMapping ConstSharedFragments;`
- L375 _public member_ `FMassFragmentIndicesMapping SharedFragments;`
- L376 _public function_ `inline bool IsEmpty() const`

#### struct `FMassChunkProcessingQueueParams`  
`struct FMassChunkProcessingQueueParams`  
_L382-392_
- L384 _public member_ `FMassExecutionContext* SourceContext = nullptr;`
- L385 _public member_ `FMassEntityQuery* SourceQuery = nullptr;`
- L386 _public member_ `FMassArchetypeData* Archetype = nullptr;`
- L387 _public member_ `const FMassArchetypeEntityCollection::FArchetypeEntityRange EntityRange;`
- L388 _public member_ `const FMassExecuteFunction* ExecuteFunction = nullptr;`
- L389 _public member_ `const FMassChunkConditionFunction* ChunkCondition = nullptr;`
- L390 _public member_ `const FMassQueryRequirementIndicesMapping* RequirementMapping = nullptr;`
- L391 _public member_ `bool bParallelExecution = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MASSENTITY_API`
- L31 _typedef_ `using FMassEntityExecuteFunction = TFunction< void(FMassExecutionContext& , int32 ) >;`
- L32 _typedef_ `using FMassExecuteFunction = TFunction< void(FMassExecutionContext& ) >;`
- L33 _typedef_ `using FMassChunkConditionFunction = TFunction< bool(const FMassExecutionContext& ) >;`
- L34 _typedef_ `using FMassQueueChunkFunction = TFunction< void(FMassChunkProcessingQueueParams&&) >;`
- L366 _typedef_ `using FMassFragmentIndicesMapping = TArray<int32, TInlineAllocator<16>>;`

### `Source/Runtime/MassEntity/Public/MassBitSetRegistry.h` (Public)


#### struct `TTypeBitSetTraits`  
`template <> struct TTypeBitSetTraits<FMassTag> final`  
_L12-20_
- desc: Specialization of TTypeBitSetTraits for FMassTag
- L16 _public member_ `template<typename TTestedType> static constexpr bool IsValidType = UE::Mass::CTag<TTestedType>;` — Compile-time check to ensure that TTestedType is a valid Mass Tag
- L19 _public member_ `static constexpr bool RequiresBaseType = true;` — Indicates that a base type is required for inheritance checks
- L28 _public member_ `template<typename TTestedType> static constexpr bool IsValidType = UE::Mass::CFragment<TTestedType>;` — Compile-time check to ensure that TTestedType is a valid Mass Fragment

#### struct `TTypeBitSetTraits`  
`template <> struct TTypeBitSetTraits<FMassFragment> final`  
_L24-32_
- desc: Specialization of TTypeBitSetTraits for FMassFragment
- L16 _public member_ `template<typename TTestedType> static constexpr bool IsValidType = UE::Mass::CTag<TTestedType>;` — Compile-time check to ensure that TTestedType is a valid Mass Tag
- L19 _public member_ `static constexpr bool RequiresBaseType = true;` — Indicates that a base type is required for inheritance checks
- L28 _public member_ `template<typename TTestedType> static constexpr bool IsValidType = UE::Mass::CFragment<TTestedType>;` — Compile-time check to ensure that TTestedType is a valid Mass Fragment

#### struct `UE::Mass::Private::TBitTypeRegistry`  
`template<typename T, typename TUStructType = UScriptStruct> struct TBitTypeRegistry`  
_L49-148_
- desc: Template class for registering and managing bitsets for Mass types (e.g., Fragments and Tags). Provides functionality to create builders for constructing bitsets. The type hosts a FStructTracker instance that stores information on all the types used to build bitsets via it, and only those types - as opposed to TStructTypeBitSet, which is using the same FStructTracker throughout the engine's instance lifetime. @param T the base Mass type (e.g., FMassFragment or FMassTag). @param TUStructType the Unreal Engine struct type, default is UScriptStruct.
- L52 _public typedef_ `using FBitSetBuilder = TTypeBitSetBuilder<T, TUStructType, TTypeBitSetTraits<T>::RequiresBaseType>;` — Alias for the bitset builder specific to the type T
- L55 _public typedef_ `using FBitSet = typename FBitSetBuilder::FConstBitSet;` — The type representing the runtime-used bitset. Const by design.
- L82 _public function_ `TBitTypeRegistry() : StructTracker([](){ return StructUtils::GetAsUStruct<T>(); })` — Constructor that initializes the struct tracker. Uses a lambda to retrieve the UStruct representing the base type T.
- L83 _public function_ `: StructTracker([](){ return StructUtils::GetAsUStruct<T>(); })`
- L92 _public function_ `[[nodiscard]] inline FBitSetBuilder MakeBuilder(FBitSet& BitSet) const` — Creates a bitset builder for an existing bitset. @param BitSet the bitset instance to modify @return A new FBitSetBuilder instance
- L101 _public function_ `[[nodiscard]] inline FBitSetFactory MakeBuilder() const` — Creates a factory for building new bitsets, essentially a FBitSetBuilder-BitSet combo. @return A new FBitSetFactory instance.
- L111 _public function_ `inline int32 RegisterType(TNotNull<const UScriptStruct*> Type)` — Registers a type with the struct tracker. @param Type the UScriptStruct representing the type to register. @return The index assigned to the registered type.
- L122 _public function_ `template<typename TType> inline int32 RegisterType()` — Template method to register a type with the struct tracker. @param TType the type to register. @return The index assigned to the registered type.
- L147 _public member_ `mutable FBitSetStructTracker StructTracker;` — Struct tracker for managing types

#### struct `UE::Mass::Private::TBitTypeRegistry::FBitSetFactory`  
`struct FBitSetFactory : FBitSetBuilder`  
_L63-76_
- inherits: `FBitSetBuilder`
- desc: Factory type for creating and initializing bitsets. Inherits from FBitSetBuilder to provide building capabilities. Use this type when you want to build a bitset from scratch (i.e. when you don't have a FBitSet instance you want to modify).
- L69 _public function_ `FBitSetFactory(FStructTracker& InStructTracker) : FBitSetBuilder(InStructTracker, BitSetInstance)` — Constructor that initializes the builder with a new bitset instance. @param InStructTracker the struct tracker to use for managing types.
- L75 _public member_ `FBitSet BitSetInstance;` — The bitset instance being built

#### struct `UE::Mass::Private::TBitTypeRegistry::FBitSetStructTracker`  
`struct FBitSetStructTracker : public FStructTracker`  
_L131-144_
- inherits: `FStructTracker`
- desc: Specialized struct tracker for bitsets, disabling serialization. Inherits from FStructTracker.
- L138 _public function_ `FBitSetStructTracker(const UStruct* InBaseType, const FTypeValidation& InTypeValidation = FTypeValidation()) : FStructTracker(InBaseType, InTypeValidation)` — Constructor that initializes the base type and optional type validation function. @param InBaseType the base UStruct type. @param InTypeValidation Optional function for type validation.

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Mass` (scope `UE`)
- L36 _namespace_ `namespace Private` (scope `UE::Mass`)
- L152 _typedef_ `using FFragmentBitRegistry = Private::TBitTypeRegistry<FMassFragment>;` (scope `UE::Mass`) — Alias for the fragment bit registry
- L154 _typedef_ `using FFragmentBitSetBuilder = FFragmentBitRegistry::FBitSetBuilder;` (scope `UE::Mass`) — Alias for the fragment bitset builder
- L156 _typedef_ `using FFragmentBitSetReader = const FFragmentBitSetBuilder;` (scope `UE::Mass`) — Alias for a read-only fragment bitset builder
- L158 _typedef_ `using FFragmentBitSetFactory = FFragmentBitRegistry::FBitSetFactory;` (scope `UE::Mass`) — Alias for the fragment bitset factory
- L161 _typedef_ `using FTagBitRegistry = Private::TBitTypeRegistry<FMassTag>;` (scope `UE::Mass`) — Alias for the tag bit registry
- L163 _typedef_ `using FTagBitSetBuilder = FTagBitRegistry::FBitSetBuilder;` (scope `UE::Mass`) — Alias for the tag bitset builder
- L165 _typedef_ `using FTagBitSetReader = const FTagBitSetBuilder;` (scope `UE::Mass`) — Alias for a read-only tag bitset builder
- L167 _typedef_ `using FTagBitSetFactory = FTagBitRegistry::FBitSetFactory;` (scope `UE::Mass`) — Alias for the tag bitset factory
- L171 _prototype_ `template<> FFragmentBitRegistry::TBitTypeRegistry();` (scope `UE::Mass::FFragmentBitRegistry`) — Explicit template instantiation declarations for the registries
- L174 _prototype_ `template<> FTagBitRegistry::TBitTypeRegistry();` (scope `UE::Mass::FTagBitRegistry`)
- L178 _typedef_ `using FMassFragmentBitSet_WIP = UE::Mass::FFragmentBitRegistry::FBitSet;`
- L179 _typedef_ `using FMassTagBitSet_WIP = UE::Mass::FTagBitRegistry::FBitSet;`

### `Source/Runtime/MassEntity/Public/MassCommandBuffer.h` (Public)


#### struct `UE::Mass::Deprecation::TOverridesExecute`  
`template <typename TCommand> requires std::is_base_of_v<FMassBatchedCommand, TCommand> struct TOverridesExecute : std::bool_constant<IsExecuteOverridden<TCommand>()>`  
_L42-44_
- inherits: `std::bool_constant<IsExecuteOverridden<TCommand>()>`

#### struct `FMassCommandBuffer`  
`struct FMassCommandBuffer`  
_L98-460_
- L100 _public prototype_ `FMassCommandBuffer();`
- L101 _public prototype_ `~FMassCommandBuffer();`
- L105 _public function_ `template< template<typename... TArgs> typename TCommand, typename... TArgs > void PushCommand(const FMassEntityHandle Entity, TArgs&&... InArgs)` — Adds a new entry to a given TCommand batch command instance
- L117 _public function_ `template<typename TCommand, typename... TArgs> void PushCommand(TArgs&&... InArgs)`
- L130 _public function_ `template< typename TCommand> void PushCommand(const FMassEntityHandle Entity)` — Adds a new entry to a given TCommand batch command instance
- L141 _public function_ `template< typename TCommand> void PushCommand(TConstArrayView<FMassEntityHandle> Entities)`
- L159 _public function_ `FMassBatchedCommand& PushUniqueCommand(TUniquePtr<FMassBatchedCommand>&& CommandInstance)` — Ordinary PushCommand calls try to reuse existing command instances (as stored in CommandInstances) based on their type. This command lets callers add a manually configured command instance, that might not be distinguishable from other commands based solely on its type. For example, when you implement a command type that has member properties that control how the given command works or what exactly it does.
- L176 _public function_ `TCommand& PushUniqueCommand(ArgsType&&... Args)`
- L183 _public function_ `template<typename T> void AddFragment(FMassEntityHandle Entity)`
- L191 _public function_ `void AddFragment_RuntimeCheck(FMassEntityHandle Entity)` — `UE_DEPRECATED(5.8, "Use AddFragment instead")`
- L198 _public function_ `template<typename T> void RemoveFragment(FMassEntityHandle Entity)`
- L206 _public function_ `void RemoveFragment_RuntimeCheck(FMassEntityHandle Entity)` — `UE_DEPRECATED(5.8, "Use RemoveFragment instead")`
- L214 _public function_ `template<typename T> void AddTag(FMassEntityHandle Entity)` — the convenience function equivalent to calling PushCommand<FMassCommandAddTag<T>>(Entity)
- L221 _public function_ `template<typename T> void AddTag(TConstArrayView<FMassEntityHandle> Entities)`
- L229 _public function_ `void AddTag_RuntimeCheck(FMassEntityHandle Entity)` — `UE_DEPRECATED(5.8, "Use AddTag instead")`
- L237 _public function_ `template<typename T> void RemoveTag(FMassEntityHandle Entity)` — the convenience function equivalent to calling PushCommand<FMassCommandRemoveTag<T>>(Entity)
- L244 _public function_ `template<typename T> void RemoveTag(TConstArrayView<FMassEntityHandle> Entities)`
- L252 _public function_ `void RemoveTag_RuntimeCheck(FMassEntityHandle Entity)` — `UE_DEPRECATED(5.8, "Use RemoveTag instead")`
- L260 _public function_ `template<typename TOld, typename TNew> void SwapTags(FMassEntityHandle Entity)` — the convenience function equivalent to calling PushCommand<FMassCommandSwapTags<TOld, TNew>>(Entity)
- L269 _public function_ `void SwapTags_RuntimeCheck(FMassEntityHandle Entity)` — `UE_DEPRECATED(5.8, "Use SwapTags instead")`
- L278 _public function_ `template<typename... TTypes> void AddElements(FMassEntityHandle Entity)` — Adds any mix of non-shared element types (fragments, tags, sparse) to an entity. Batches via PushCommand.
- L285 _public function_ `template<typename... TTypes> void AddElements(TConstArrayView<FMassEntityHandle> Entities)` — Adds any mix of non-shared element types (fragments, tags, sparse) to entities. Batches via PushCommand.
- L292 _public function_ `template<typename... TTypes> void AddElementsWithSharedFragments(FMassEntityHandle Entity, FMassArchetypeSharedFragmentValues&& SharedValues)` — Adds non-shared element types AND shared fragment values to an entity. Per-hash grouping for batching.
- L301 _public function_ `template<typename... TElements> void AddFragmentInstancesWithSharedFragments(FMassEntityHandle Entity, FMassArchetypeSharedFragmentValues&& SharedValues, TElements&&... InElements)` — Adds element types with per-entity values AND shared fragment values to an entity in a single move. Per-hash grouping. TElements accepts FMassFragment types (per-entity values required) and FMassTag types including sparse (tags participate in composition but are excluded from the value payload due to zero-size storage).
- L307 _public function_ `void AddElements(FMassEntityHandle Entity, TConstArrayView<const UScriptStruct*> ElementTypes)` — Adds any mix of non-shared element types to an entity. Types provided at runtime. Uses PushUniqueCommand.
- L313 _public function_ `void AddElements(TConstArrayView<FMassEntityHandle> Entities, TConstArrayView<const UScriptStruct*> ElementTypes)` — Adds any mix of non-shared element types to entities. Types provided at runtime. Uses PushUniqueCommand.
- L320 _public function_ `template<typename... TTypes> void RemoveElements(FMassEntityHandle Entity)` — Removes any mix of element types (fragments, tags, shared, const shared, sparse) from an entity. Batches via PushCommand.
- L327 _public function_ `template<typename... TTypes> void RemoveElements(TConstArrayView<FMassEntityHandle> Entities)` — Removes any mix of element types (fragments, tags, shared, const shared, sparse) from entities. Batches via PushCommand.
- L333 _public function_ `void RemoveElements(FMassEntityHandle Entity, TConstArrayView<const UScriptStruct*> ElementTypes)` — Removes any mix of element types from an entity. Types provided at runtime. Uses PushUniqueCommand.
- L339 _public function_ `void RemoveElements(TConstArrayView<FMassEntityHandle> Entities, TConstArrayView<const UScriptStruct*> ElementTypes)` — Removes any mix of element types from entities. Types provided at runtime. Uses PushUniqueCommand.
- L344 _public function_ `void DestroyEntity(FMassEntityHandle Entity)`
- L349 _public function_ `void DestroyEntities(TConstArrayView<FMassEntityHandle> InEntitiesToDestroy)`
- L354 _public function_ `void DestroyEntities(TArray<FMassEntityHandle>&& InEntitiesToDestroy)`
- L359 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L366 _public prototype_ `void MoveAppend(FMassCommandBuffer& InOutOther);` — Appends the commands from the passed buffer into this one @param InOutOther the source buffer to copy the commands from. Note that after the call the InOutOther will be emptied due to the function using Move semantics
- L368 _public function_ `bool HasPendingCommands() const`
- L372 _public function_ `bool IsFlushing() const`
- L384 _public function_ `void CancelCommands()` — Removes any pending command instances This could be required for CommandBuffers that are queued to flush their commands on the game thread but the EntityManager is no longer available. In such scenario we need to cancel commands to avoid an ensure for unprocessed commands when the buffer gets destroyed.
- L389 _public function_ `bool IsInOwnerThread() const`
- L401 _public prototype_ `void ForceUpdateCurrentThreadID();` — Updates the OwnerThreadId which indicates that the given command buffer instance is being used in a different thread now. Use this with extreme caution, it's not a tool to be used every time we get "Commands can be pushed only in the same thread where the command buffer was created." error. It's meant to be used when there's a possibility the code owning the buffer has been moved to another thread (like in ParallelFor).
- L407 _private function_ `template<typename T> T& CreateOrAddCommand()`
- L431 _private prototype_ `bool Flush(FMassEntityManager& EntityManager);` — Executes all accumulated commands. @return whether any commands have actually been executed
- L432 _private prototype_ `void CleanUp();`
- L434 _private member_ `FTransactionallySafeCriticalSection AppendingCommandsCS;`
- L436 _private prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(PendingBatchCommandsDetector);`
- L441 _private member_ `TArray<TUniquePtr<FMassBatchedCommand>> CommandInstances;` — Commands created for this specific command buffer. All commands in the array are unique (by type) and reusable with subsequent PushCommand calls
- L447 _private member_ `TArray<TUniquePtr<FMassBatchedCommand>> AppendedCommandInstances;` — Commands appended to this command buffer (via FMassCommandBuffer::MoveAppend). These commands are just naive list of commands, potentially containing duplicates with multiple MoveAppend calls. Once appended these commands are not being reused and consumed, destructively, during flushing
- L449 _private member_ `int32 ActiveCommandsCounter = 0;`
- L452 _private member_ `bool bIsFlushing = false;` — Indicates that this specific MassCommandBuffer is currently flushing its contents
- L459 _private member_ `uint32 OwnerThreadId;` — Identifies the thread where given FMassCommandBuffer instance was created. Adding commands from other threads is not supported and we use this value to check that. Note that it could be const since we set it in the constructor, but we need to recache on server forking.

#### Free symbols / members of external scopes

- L23 _macro_ `#define COMMAND_PUSHING_CHECK() \`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Mass` (scope `UE`)
- L29 _namespace_ `namespace Deprecation` (scope `UE::Mass`)
- L33 _function_ `template <typename TCommand> constexpr bool IsExecuteOverridden()` (scope `UE::Mass::Deprecation`)
- L35 _typedef_ `using TResolved = decltype(&TCommand::Execute);` (scope `UE::Mass::Deprecation::IsExecuteOverridden`)
- L36 _typedef_ `using TBase = decltype(&FMassBatchedCommand::Execute);` (scope `UE::Mass::Deprecation::IsExecuteOverridden`)
- L48 _macro_ `#define ASSERT_EXECUTE_DEPRECATION(CommandType) \`
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace Mass` (scope `UE`)
- L51 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L69 _function_ `template<typename TCommand, typename... TArgs> void CallCheckBreakpoints(TArgs&&... InArgs)` (scope `UE::Mass::Debug`)
- L83 _function_ `template<typename TCommand, typename... TArgs > void CallCheckBreakpointsByInstance(TArgs&&... InArgs)` (scope `UE::Mass::Debug`)

### `Source/Runtime/MassEntity/Public/MassCommands.h` (Public)


#### enum `EMassCommandOperationType`  
`enum class EMassCommandOperationType : uint8`  
_L114-125_
- reflection: `UENUM()`
- desc: Enum used by MassBatchCommands to declare their "type". This data is later used to group commands so that command effects are applied in a controllable fashion Important: if changed make sure to update FMassCommandBuffer::Flush.CommandTypeOrder as well
- L116 _public enumerator_ `None` — default value. Commands marked this way will always be executed last. Programmers are encouraged to instead use one of the meaningful values below.
- L117 _public enumerator_ `Create` — signifies commands performing entity creation
- L118 _public enumerator_ `Add` — signifies commands adding fragments or tags to entities
- L119 _public enumerator_ `Remove` — signifies commands removing fragments or tags from entities
- L120 _public enumerator_ `ChangeComposition` — signifies commands both adding and removing fragments and/or tags from entities
- L121 _public enumerator_ `Set` — signifies commands setting values to pre-existing fragments. The fragments might be added if missing,
- L123 _public enumerator_ `Destroy` — depending on specific command, so this group will always be executed after the Add group
- L124 _public enumerator_ `MAX`

#### enum `EMassCommandCheckTime`  
`enum class EMassCommandCheckTime : bool`  
_L127-131_
- L129 _public enumerator_ `RuntimeCheck = true`
- L130 _public enumerator_ `CompileTimeCheck = false`

#### struct `UE::Mass::Command::TCommandTraits`  
`template<typename T> struct TCommandTraits final`  
_L176-182_

#### enum `UE::Mass::Command::TCommandTraits::(anonymous)`  
``  
_L179-181_

#### struct `FMassBatchedCommand`  
`struct FMassBatchedCommand`  
_L185-257_
- L187 _public prototype_ `FMassBatchedCommand() = default;`
- L188 _public function_ `explicit FMassBatchedCommand(EMassCommandOperationType OperationType) : OperationType(OperationType)`
- L192 _public function_ `FMassBatchedCommand(EMassCommandOperationType OperationType, FName DebugName) : OperationType(OperationType) , DebugName(DebugName)`
- L197 _public function_ `virtual ~FMassBatchedCommand()`
- L203 _public function_ `virtual void Execute(FMassEntityManager& EntityManager) const` — `UE_DEPRECATED(5.7, "Mass Commands: CONST Execute function is deprecated in 5.7 and will be removed by 5.9. Use Run instead.")`
- L208 _public function_ `virtual void Run(FMassEntityManager& EntityManager)`
- L215 _public function_ `virtual void Reset()`
- L220 _public function_ `bool HasWork() const`
- L224 _public function_ `EMassCommandOperationType GetOperationType() const`
- L231 _public function_ `static uint32 GetCommandIndex()`
- L237 _public prototype_ `virtual SIZE_T GetAllocatedSize() const = 0;`
- L240 _public prototype_ `virtual int32 GetNumOperationsStat() const = 0;`
- L241 _public function_ `FName GetFName() const`
- L248 _protected member_ `bool bHasWork = false;`
- L249 _protected member_ `EMassCommandOperationType OperationType = EMassCommandOperationType::None;`
- L252 _protected member_ `FName DebugName;`
- L256 _private member_ `static std::atomic<uint32> CommandsCounter;`

#### struct `FMassBatchedEntityCommand`  
`struct FMassBatchedEntityCommand : public FMassBatchedCommand`  
_L259-310_
- inherits: `FMassBatchedCommand`
- L261 _public typedef_ `using Super = FMassBatchedCommand;`
- L263 _public prototype_ `FMassBatchedEntityCommand() = default;`
- L268 _public function_ `void Add(FMassEntityHandle Entity)`
- L275 _public function_ `void Add(TConstArrayView<FMassEntityHandle> Entities)`
- L282 _public function_ `void Add(TArray<FMassEntityHandle>&& Entities)`
- L290 _protected function_ `virtual SIZE_T GetAllocatedSize() const`
- L295 _protected function_ `virtual void Reset() override`
- L302 _protected function_ `virtual int32 GetNumOperationsStat() const override`
- L308 _protected prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(EntitiesAccessDetector);`
- L309 _protected member_ `TArray<FMassEntityHandle> TargetEntities;`

#### struct `FMassCommandDestroyEntities`  
`struct FMassCommandDestroyEntities : public FMassBatchedEntityCommand`  
_L326-352_
- inherits: `FMassBatchedEntityCommand`
- desc: Destroys entities. Uses PushCommand for cross-chunk batching. Example: // Single entity: Context.Defer().DestroyEntity(EntityHandle); // All entities in chunk: Context.Defer().DestroyEntities(Context.GetEntities()); Breakpoint support: Yes — CheckDestroyEntityBreakpoints called at PushCommand time.
- L328 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L330 _public function_ `FMassCommandDestroyEntities() : Super(EMassCommandOperationType::Destroy DEBUG_NAME("DestroyEntities"))`
- L337 _public function_ `template<typename T> static bool CheckBreakpoints(T Entity)`
- L344 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`

#### struct `FMassCommandAddElement`  
`struct FMassCommandAddElement : public FMassBatchedEntityCommand`  
_L376-393_
- inherits: `FMassBatchedEntityCommand`
- desc: Adds a single element type (fragment, tag, or sparse) to entities at runtime. Requires PushUniqueCommand — each call creates a separate command instance (no cross-call batching). Shared/const shared fragments are rejected at runtime (they require values). When to use: when the element type is only known at runtime and you need to add a single type. Prefer FMassCommandAddElements<T...> when types are known at compile time (better batching). Example: // Single entity: FMassCommandAddElement& Cmd = Context.Defer().PushUniqueCommand<FMassCommandAddElement>(FMyFragment::StaticStruct()); Cmd.Add(EntityHandle); // All entities in chunk: Cmd.Add(Context.GetEntities()); Supported types: FMassFragment, FMassTag, FMassSparseFragment, FMassSparseTag. Rejected types: FMassSharedFragment, FMassConstSharedFragment, FMassChunkFragment. Breakpoint support: No (runtime types — use FMassCommandAddElements<T...> for breakpoints).
- L378 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L380 _public function_ `FMassCommandAddElement(const TNotNull<const UScriptStruct*> InElementType) : Super(EMassCommandOperationType::Add DEBUG_NAME("AddElement")) , ElementType(InElementType)`
- L386 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L392 _protected member_ `TNotNull<const UScriptStruct*> ElementType;`

#### struct `UE::Mass::Command::TCommandTraits`  
`template<> struct UE::Mass::Command::TCommandTraits<FMassCommandAddElement> final`  
_L396-402_

#### enum `UE::Mass::Command::TCommandTraits::(anonymous)`  
``  
_L399-401_

#### struct `FMassCommandRemoveElement`  
`struct FMassCommandRemoveElement : public FMassBatchedEntityCommand`  
_L422-439_
- inherits: `FMassBatchedEntityCommand`
- desc: Removes a single element type from entities at runtime. Requires PushUniqueCommand — each call creates a separate command instance (no cross-call batching). Supports all element types including shared and const shared fragments. When to use: when the element type is only known at runtime and you need to remove a single type. Prefer FMassCommandRemoveElements<T...> when types are known at compile time (better batching, single entity move). Example: // Single entity: FMassCommandRemoveElement& Cmd = Context.Defer().PushUniqueCommand<FMassCommandRemoveElement>(FMyFragment::StaticStruct()); Cmd.Add(EntityHandle); // All entities in chunk: Cmd.Add(Context.GetEntities()); Supported types: all FMassElement subtypes (fragments, tags, shared, const shared, sparse). Breakpoint support: No (runtime types — use FMassCommandRemoveElements<T...> for breakpoints).
- L424 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L426 _public function_ `FMassCommandRemoveElement(const TNotNull<const UScriptStruct*> InElementType) : Super(EMassCommandOperationType::Remove DEBUG_NAME("RemoveElement")) , ElementType(InElementType)`
- L432 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L438 _protected member_ `TNotNull<const UScriptStruct*> ElementType;`

#### struct `UE::Mass::Command::TCommandTraits`  
`template<> struct UE::Mass::Command::TCommandTraits<FMassCommandRemoveElement> final`  
_L442-448_

#### enum `UE::Mass::Command::TCommandTraits::(anonymous)`  
``  
_L445-447_

#### struct `FMassCommandRemoveElementList`  
`struct FMassCommandRemoveElementList : public FMassBatchedEntityCommand`  
_L471-526_
- inherits: `FMassBatchedEntityCommand`
- desc: Removes any mix of element types from entities at runtime. Element types are provided as UScriptStruct* at construction time. Requires PushUniqueCommand — each call creates a separate command instance (no cross-call batching, but entities batch within a single instance via Add()). Performs a single entity move for all non-sparse types + in-place sparse removal. When to use: when element types are only known at runtime and you need to remove multiple types at once. Prefer FMassCommandRemoveElements<T...> when types are known at compile time (cross-chunk batching). Example: const UScriptStruct* Types[] = { FMyFragment::StaticStruct(), FMyTag::StaticStruct() }; // Single entity: FMassCommandRemoveElementList& Cmd = Context.Defer().PushUniqueCommand<FMassCommandRemoveElementList>(Types); Cmd.Add(EntityHandle); // All entities in chunk via convenience: Context.Defer().RemoveElements(Context.GetEntities(), Types); Supported types: all FMassElement subtypes (fragments, tags, shared, const shared, sparse). Breakpoint support: No (runtime types).
- L473 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L475 _public function_ `FMassCommandRemoveElementList(TConstArrayView<const UScriptStruct*> InElementTypes) : Super(EMassCommandOperationType::Remove DEBUG_NAME("RemoveElementList"))`
- L492 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L512 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L518 _protected function_ `virtual int32 GetNumOperationsStat() const override`
- L524 _protected member_ `FMassElementBitSet NonSparseTypes;`
- L525 _protected member_ `TArray<const UScriptStruct*> SparseTypes;`

#### struct `UE::Mass::Command::TCommandTraits`  
`template<> struct UE::Mass::Command::TCommandTraits<FMassCommandRemoveElementList> final`  
_L529-535_

#### enum `UE::Mass::Command::TCommandTraits::(anonymous)`  
``  
_L532-534_

#### struct `FMassCommandRemoveElements`  
`template<typename... TTypes> struct FMassCommandRemoveElements : public FMassBatchedEntityCommand`  
_L559-638_
- inherits: `FMassBatchedEntityCommand`
- desc: Removes any mix of element types from entities. This is the preferred command for element removal. Types are template parameters — uses PushCommand for efficient cross-chunk batching (one Run() for all entities across all chunks that push into this command). Performs a single entity move for all non-sparse types. When to use: whenever you need to remove fragments, tags, shared fragments, and/or sparse elements from entities and the types are known at compile time. Replaces FMassCommandRemoveFragments and FMassCommandRemoveTags. Example: // All entities in chunk: Context.Defer().PushCommand<FMassCommandRemoveElements<FMyFragment, FMyTag, FMyConstShared>>(Context.GetEntities()); // Single entity: Context.Defer().PushCommand<FMassCommandRemoveElements<FMyFragment, FMyTag>>(EntityHandle); // Via convenience: Context.Defer().RemoveElements<FMyFragment, FMyTag, FMyConstShared>(Context.GetEntities()); Supported types: all FMassElement subtypes (fragments, tags, shared, const shared, sparse). Breakpoint support: Yes — CheckFragmentRemoveBreakpoints called per entity at PushCommand time. Entity moves: 1 move for all non-sparse types combined. Sparse removal is in-place (no move).
- L561 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L563 _public function_ `FMassCommandRemoveElements() : Super(EMassCommandOperationType::Remove DEBUG_NAME("RemoveElements"))`
- L573 _public function_ `static bool CheckBreakpoints(const FMassEntityHandle Entity)` — Function pointer forces the non-template overload of CheckFragmentRemoveBreakpoints. Without it, MSVC deduces TFragments=UScriptStruct* from StaticStruct() return type, matching the variadic template overload which then calls UScriptStruct*::StaticStruct() and fails.
- L579 _public function_ `static bool CheckBreakpoints(TConstArrayView<FMassEntityHandle> Entities)`
- L596 _private function_ `template<typename T> void CategorizeElementType()`
- L610 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L631 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L636 _protected member_ `FMassElementBitSet NonSparseTypes;`
- L637 _protected member_ `TArray<const UScriptStruct*> SparseTypes;`

#### struct `FMassCommandAddElements`  
`template<typename... TTypes> struct FMassCommandAddElements : public FMassBatchedEntityCommand`  
_L664-745_
- inherits: `FMassBatchedEntityCommand`
- desc: Adds any mix of non-shared element types to entities. This is the preferred command for element addition. Types are template parameters — uses PushCommand for efficient cross-chunk batching (one Run() for all entities across all chunks that push into this command). Performs a single entity move for all non-sparse types. Shared/const shared fragments cannot be added — they require values (use AddSharedFragmentToEntity). When to use: whenever you need to add fragments, tags, and/or sparse elements to entities and the types are known at compile time. Replaces FMassCommandAddFragments and FMassCommandAddTags. Example: // All entities in chunk: Context.Defer().PushCommand<FMassCommandAddElements<FMyFragment, FMyTag>>(Context.GetEntities()); // Single entity: Context.Defer().PushCommand<FMassCommandAddElements<FMyFragment, FMyTag>>(EntityHandle); // Via convenience: Context.Defer().AddElements<FMyFragment, FMyTag>(Context.GetEntities()); Supported types: FMassFragment, FMassTag, FMassSparseFragment, FMassSparseTag. Rejected types: FMassSharedFragment, FMassConstSharedFragment (compile-time static_assert), FMassChunkFragment (runtime). Breakpoint support: Yes — CheckFragmentAddBreakpoints called per entity at PushCommand time. Entity moves: 1 move for all non-sparse types combined. Sparse addition is in-place (no move).
- L669 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L671 _public function_ `FMassCommandAddElements() : Super(EMassCommandOperationType::Add DEBUG_NAME("AddElements"))`
- L681 _public function_ `static bool CheckBreakpoints(const FMassEntityHandle Entity)` — Function pointer forces the non-template overload of CheckFragmentAddBreakpoints. Without it, MSVC deduces TFragments=UScriptStruct* from StaticStruct() return type, matching the variadic template overload which then calls UScriptStruct*::StaticStruct() and fails.
- L687 _public function_ `static bool CheckBreakpoints(TConstArrayView<FMassEntityHandle> Entities)`
- L703 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L723 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L730 _private function_ `template<typename T> void CategorizeElementType()`
- L743 _private member_ `FMassElementBitSet NonSparseTypes;`
- L744 _private member_ `TArray<const UScriptStruct*> SparseTypes;`

#### struct `FMassCommandAddElementList`  
`struct FMassCommandAddElementList : public FMassBatchedEntityCommand`  
_L769-824_
- inherits: `FMassBatchedEntityCommand`
- desc: Adds any mix of non-shared element types to entities at runtime. Element types are provided as UScriptStruct* at construction time. Requires PushUniqueCommand — each call creates a separate command instance (no cross-call batching, but entities batch within a single instance via Add()). Performs a single entity move for all non-sparse types + in-place sparse addition. When to use: when element types are only known at runtime and you need to add multiple types at once. Prefer FMassCommandAddElements<T...> when types are known at compile time (cross-chunk batching). Example: const UScriptStruct* Types[] = { FMyFragment::StaticStruct(), FMyTag::StaticStruct() }; // Single entity: FMassCommandAddElementList& Cmd = Context.Defer().PushUniqueCommand<FMassCommandAddElementList>(Types); Cmd.Add(EntityHandle); // All entities in chunk via convenience: Context.Defer().AddElements(Context.GetEntities(), Types); Supported types: FMassFragment, FMassTag, FMassSparseFragment, FMassSparseTag. Rejected types: shared/const shared and chunk fragments are rejected at runtime by BatchChangeCompositionForEntities (no compile-time check). Breakpoint support: No (runtime types).
- L771 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L773 _public function_ `FMassCommandAddElementList(TConstArrayView<const UScriptStruct*> InElementTypes) : Super(EMassCommandOperationType::Add DEBUG_NAME("AddElementList"))`
- L790 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L810 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L816 _protected function_ `virtual int32 GetNumOperationsStat() const override`
- L822 _protected member_ `FMassElementBitSet NonSparseTypes;`
- L823 _protected member_ `TArray<const UScriptStruct*> SparseTypes;`

#### struct `UE::Mass::Command::TCommandTraits`  
`template<> struct UE::Mass::Command::TCommandTraits<FMassCommandAddElementList> final`  
_L827-833_

#### enum `UE::Mass::Command::TCommandTraits::(anonymous)`  
``  
_L830-832_

#### struct `FMassCommandAddElementsWithSharedFragments`  
`template<typename... TTypes> struct FMassCommandAddElementsWithSharedFragments : public FMassBatchedCommand`  
_L857-979_
- inherits: `FMassBatchedCommand`
- desc: Adds any mix of non-shared element types AND shared fragment values to existing entities. Types are template parameters for non-shared elements. Shared fragment values are provided at runtime. Entities are grouped by shared fragment value hash for efficient per-group archetype changes. Performs a single entity move per group (non-sparse composition + shared values combined). When to use: when you need to add fragments/tags AND shared fragment values to existing entities in a single operation. Replaces separate AddElements + BatchAddSharedFragmentsForEntities calls. Example: FMassArchetypeSharedFragmentValues SharedValues; SharedValues.Add(EntityManager->GetOrCreateConstSharedFragment(FMySharedFragment(42))); Context.Defer().PushCommand<FMassCommandAddElementsWithSharedFragments<FMyFragment, FMyTag>>( EntityHandle, MoveTemp(SharedValues)); Supported types (TTypes): FMassFragment + FMassTag (including sparse). Rejected types (TTypes): FMassSharedFragment, FMassConstSharedFragment (use shared values param instead), FMassChunkFragment. Breakpoint support: No (composition-only command). Entity moves: 1 move per shared-value group. Sparse addition is in-place.
- L866 _public typedef_ `using Super = FMassBatchedCommand;`
- L868 _public function_ `FMassCommandAddElementsWithSharedFragments() : Super(EMassCommandOperationType::Add DEBUG_NAME("AddElementsWithSharedFragments"))`
- L876 _public function_ `void Add(FMassEntityHandle Entity, FMassArchetypeSharedFragmentValues&& InSharedFragments)` — @note Callers must not Add() the same entity with different shared values — it would end up in two hash groups, and the second group's archetype move would overwrite the first group's without merging fragment values.
- L886 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L916 _protected function_ `virtual void Reset() override`
- L922 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L935 _protected function_ `virtual int32 GetNumOperationsStat() const override`
- L948 _private function_ `template<typename T> void CategorizeElementType()`
- L976 _private member_ `FMassElementBitSet NonSparseTypes;`
- L977 _private member_ `TArray<const UScriptStruct*> SparseTypes;`
- L978 _private member_ `TMap<uint32, FPerSharedFragmentsHashData> Data;`

#### struct `FMassCommandAddElementsWithSharedFragments::FPerSharedFragmentsHashData`  
`struct FPerSharedFragmentsHashData`  
_L961-974_
- L963 _public function_ `FPerSharedFragmentsHashData(FMassArchetypeSharedFragmentValues&& InSharedFragmentValues) : SharedFragmentValues(MoveTemp(InSharedFragmentValues))`
- L967 _public function_ `SIZE_T GetAllocatedSize() const`
- L972 _public member_ `TArray<FMassEntityHandle> TargetEntities;`
- L973 _public member_ `FMassArchetypeSharedFragmentValues SharedFragmentValues;`

#### struct `FMassCommandAddFragmentInstancesWithSharedFragments`  
`template<typename TSharedFragmentValues, typename... TTypes> struct FMassCommandAddFragmentInstancesWithSharedFragments : public FMassBatchedCommand`  
_L1009-1170_
- inherits: `FMassBatchedCommand`
- desc: Adds fragment types with per-entity values AND shared fragment values to existing entities in a single entity move. Extends FMassCommandAddFragmentInstances with shared fragment value support; entities are partitioned by shared fragment value hash at Add() time and dispatched in one BatchAddFragmentInstancesForEntities call per group. When no shared fragment values are needed, prefer FMassCommandAddFragmentInstances — its flat single-batch storage avoids the per-Add hash computation and TMap overhead. Uses PushCommand for cross-chunk batching. Note: TSharedFragmentValues is always FMassArchetypeSharedFragmentValues but is a template param to maintain uniform PushCommand interface (all params in one typename... list). When to use: when you need to add fragments with initial values AND shared fragment values to existing entities in one operation. Replaces separate AddFragmentInstances + deferred lambda AddConstSharedFragmentToEntity calls. Example: FMassArchetypeSharedFragmentValues SharedValues; SharedValues.Add(EntityManager->GetOrCreateConstSharedFragment(FMySharedFragment(42))); Context.Defer().PushCommand<FMassCommandAddFragmentInstancesWithSharedFragments>( EntityHandle, MoveTemp(SharedValues), FMyFragmentA(1), FMyFragmentB(2.0f)); Supported types (TTypes): FMassFragment + FMassTag (including sparse). Tags are included in composition but excluded from value payload (zero-size storage). Shared fragments via FMassArchetypeSharedFragmentValues. Breakpoint support: Yes -- Che
- L1021 _public typedef_ `using Super = FMassBatchedCommand;`
- L1023 _public function_ `FMassCommandAddFragmentInstancesWithSharedFragments(EMassCommandOperationType OperationType = EMassCommandOperationType::Set DEBUG_NAME_PARAM("AddFragmentInstancesWithSharedFragments")) : Super(OperationType FORWARD_DEBUG_NAME_PARAM)`
- L1031 _public function_ `void Add(FMassEntityHandle Entity, FMassArchetypeSharedFragmentValues&& InSharedFragments, TTypes... InFragments)` — @note Callers must not Add() the same entity with different shared values — it would end up in two hash groups, and the second group's archetype move would overwrite the first group's without merging fragment values.
- L1047 _public function_ `static bool CheckBreakpoints(const FMassEntityHandle Entity, TTypes... InFragments)`
- L1059 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L1070 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L1111 _protected function_ `virtual void Reset() override`
- L1118 _protected function_ `virtual int32 GetNumOperationsStat() const override`
- L1129 _protected member_ `FMassFragmentBitSet FragmentsAffected;`
- L1130 _protected member_ `FMassTagBitSet TagsAffected;`
- L1131 _protected member_ `TArray<const UScriptStruct*> SparseTypes;`
- L1150 _protected member_ `TMap<uint32, FPerSharedFragmentsHashData> Data;`
- L1154 _private function_ `template<typename T> void CategorizeElementType()`

#### struct `FMassCommandAddFragmentInstancesWithSharedFragments::FPerSharedFragmentsHashData`  
`struct FPerSharedFragmentsHashData`  
_L1133-1148_
- L1135 _public function_ `FPerSharedFragmentsHashData(FMassArchetypeSharedFragmentValues&& InSharedFragmentValues) : SharedFragmentValues(MoveTemp(InSharedFragmentValues))`
- L1140 _public function_ `SIZE_T GetAllocatedSize() const`
- L1145 _public member_ `TArray<FMassEntityHandle> TargetEntities;`
- L1146 _public member_ `mutable UE::Mass::TMultiArray<TTypes...> Fragments;`
- L1147 _public member_ `FMassArchetypeSharedFragmentValues SharedFragmentValues;`

#### struct `FMassCommandAddFragmentsInternal`  
`template<EMassCommandCheckTime CheckTime, typename... TTypes> struct UE_DEPRECATED(5.8, "Use FMassCommandAddElements instead — supports any mix of element types in a single operation.") FMassCommandAddFragmentsInternal : public FMassBatchedEntityCommand`  
_L1176-1204_
- inherits: `FMassBatchedEntityCommand`
- L1181 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L1182 _public function_ `FMassCommandAddFragmentsInternal() : Super(EMassCommandOperationType::Add DEBUG_NAME("AddFragments")) , FragmentsAffected(UE::Mass::Utils::ConstructFragmentBitSet<CheckTime, TTypes...>())`
- L1189 _public function_ `template<typename T> static bool CheckBreakpoints(T Entity, TTypes... InFragments)`
- L1196 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L1203 _protected member_ `FMassFragmentBitSet FragmentsAffected;`

#### struct `FMassCommandRemoveFragmentsInternal`  
`template<EMassCommandCheckTime CheckTime, typename... TTypes> struct UE_DEPRECATED(5.8, "Use FMassCommandRemoveElements instead — supports any mix of element types and performs a single entity move.") FMassCommandRemoveFragmentsInternal : public FMassBatchedEntityCommand`  
_L1210-1237_
- inherits: `FMassBatchedEntityCommand`
- L1214 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L1215 _public function_ `FMassCommandRemoveFragmentsInternal() : Super(EMassCommandOperationType::Remove DEBUG_NAME("RemoveFragments")) , FragmentsAffected(UE::Mass::Utils::ConstructFragmentBitSet<CheckTime, TTypes...>())`
- L1222 _public function_ `template<typename T> static bool CheckBreakpoints(T Entity, TTypes... InFragments)`
- L1229 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L1236 _protected member_ `FMassFragmentBitSet FragmentsAffected;`

#### struct `FMassCommandChangeTags`  
`struct FMassCommandChangeTags : public FMassBatchedEntityCommand`  
_L1245-1275_
- inherits: `FMassBatchedEntityCommand`
- L1247 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L1248 _public function_ `FMassCommandChangeTags() : Super(EMassCommandOperationType::ChangeComposition DEBUG_NAME("ChangeTags"))`
- L1259 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L1268 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L1273 _protected member_ `FMassTagBitSet TagsToAdd;`
- L1274 _protected member_ `FMassTagBitSet TagsToRemove;`

#### struct `FMassCommandAddTagsInternal`  
`template<EMassCommandCheckTime CheckTime, typename... TTypes> struct UE_DEPRECATED(5.8, "Use FMassCommandAddElements instead — supports any mix of element types in a single operation.") FMassCommandAddTagsInternal : public FMassCommandChangeTags`  
_L1278-1291_
- inherits: `FMassCommandChangeTags`
- L1283 _public typedef_ `using Super = FMassCommandChangeTags;`
- L1284 _public function_ `FMassCommandAddTagsInternal() : Super( EMassCommandOperationType::Add, UE::Mass::Utils::ConstructTagBitSet<CheckTime, TTypes...>(), {} DEBUG_NAME("AddTags"))`

#### struct `FMassCommandRemoveTagsInternal`  
`template<EMassCommandCheckTime CheckTime, typename... TTypes> struct UE_DEPRECATED(5.8, "Use FMassCommandRemoveElements instead — supports any mix of element types and performs a single entity move.") FMassCommandRemoveTagsInternal : public FMassCommandChangeTags`  
_L1300-1320_
- inherits: `FMassCommandChangeTags`
- L1304 _public typedef_ `using Super = FMassCommandChangeTags;`
- L1305 _public function_ `FMassCommandRemoveTagsInternal() : Super( EMassCommandOperationType::Remove, {}, UE::Mass::Utils::ConstructTagBitSet<CheckTime, TTypes...>() DEBUG_NAME("RemoveTags"))`
- L1315 _public function_ `template<typename T> static bool CheckBreakpoints(T Entity, TTypes... InFragments)`

#### struct `FMassCommandSwapTagsInternal`  
`template<EMassCommandCheckTime CheckTime, typename TOld, typename TNew> struct FMassCommandSwapTagsInternal : public FMassCommandChangeTags`  
_L1344-1356_
- inherits: `FMassCommandChangeTags`
- desc: Atomically swaps one tag for another on entities. Removes TOld and adds TNew in a single composition change. Uses PushCommand for cross-chunk batching. Example: // All entities in chunk: Context.Defer().SwapTags<FOldTag, FNewTag>(Context.GetEntities()); // Single entity: Context.Defer().SwapTags<FOldTag, FNewTag>(EntityHandle); Supported types: FMassTag subtypes only (compile-time static_assert). Breakpoint support: No. Entity moves: 1 move (both tag changes applied together).
- L1348 _public typedef_ `using Super = FMassCommandChangeTags;`
- L1349 _public function_ `FMassCommandSwapTagsInternal() : Super( EMassCommandOperationType::ChangeComposition, UE::Mass::Utils::ConstructTagBitSet<CheckTime, TNew>(), UE::Mass::Utils::ConstructTagBitSet<CheckTime, TOld>() DEBUG_NAME("SwapTags"))`

#### struct `FMassCommandAddFragmentInstances`  
`template<typename... TOthers> struct FMassCommandAddFragmentInstances : public FMassBatchedEntityCommand`  
_L1383-1494_
- inherits: `FMassBatchedEntityCommand`
- desc: Adds fragments with initial values to entities. Each entity receives typed fragment data. Tags (FMassTag, FMassSparseTag) are also accepted — they participate in the composition change but are excluded from the value payload (tags have zero-size storage). Uses PushCommand for cross-chunk batching. Sparse fragments are supported (handled internally). All entities are accumulated in a single flat batch and dispatched in one BatchAddFragmentInstancesForEntities call. When to use: when you need to add fragments AND set their initial values in one operation, optionally adding tags in the same entity move. For composition-only changes (no values), prefer FMassCommandAddElements<T...>. For adding shared fragment values in the same move, use FMassCommandAddFragmentInstancesWithSharedFragments. Example: // Add fragments with values + tags in a single entity move: Context.Defer().PushCommand<FMassCommandAddFragmentInstances>(EntityHandle, FMyFragmentA(42), FMyTag()); Supported types: FMassFragment + FMassTag (including sparse). Tag instances are accepted by Add() for uniform syntax but their values are ignored. Breakpoint support: Yes — CheckFragmentAddBreakpoints called at PushCommand time.
- L1399 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L1401 _public function_ `FMassCommandAddFragmentInstances(EMassCommandOperationType OperationType = EMassCommandOperationType::Set DEBUG_NAME_PARAM("AddFragmentInstanceList")) : Super(OperationType FORWARD_DEBUG_NAME_PARAM)`
- L1408 _public function_ `template<typename... TInstances> void Add(FMassEntityHandle Entity, TInstances... InFragments)`
- L1415 _public function_ `static bool CheckBreakpoints(const FMassEntityHandle Entity, TOthers... InFragments)`
- L1427 _protected function_ `virtual void Reset() override`
- L1433 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L1438 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L1471 _protected member_ `mutable UE::Mass::TMultiArray<TOthers...> Fragments;`
- L1472 _protected member_ `FMassFragmentBitSet FragmentsAffected;`
- L1473 _protected member_ `FMassTagBitSet TagsAffected;`
- L1474 _protected member_ `TArray<const UScriptStruct*> SparseTypes;`
- L1478 _private function_ `template<typename T> void CategorizeElementType()`

#### struct `FMassCommandBuildEntity`  
`template<typename... TOthers> struct FMassCommandBuildEntity : public FMassCommandAddFragmentInstances<TOthers...>`  
_L1509-1566_
- inherits: `FMassCommandAddFragmentInstances<TOthers...>`
- desc: Builds reserved entities with fragment values (and optionally tags). Entities must be pre-reserved via EntityManager->ReserveEntity(). Uses PushCommand for cross-chunk batching. Example: FMassEntityHandle Entity = EntityManager->ReserveEntity(); Context.Defer().PushCommand<FMassCommandBuildEntity>(Entity, FMyFragmentA(42), FMyTag()); Supported types: FMassFragment + FMassTag (including sparse). Breakpoint support: Yes — CheckCreateEntityBreakpoints called at PushCommand time.
- L1511 _public typedef_ `using Super = FMassCommandAddFragmentInstances<TOthers...>;`
- L1513 _public function_ `FMassCommandBuildEntity() : Super(EMassCommandOperationType::Create DEBUG_NAME("BuildEntity"))`
- L1519 _public function_ `static bool CheckBreakpoints(TOthers... InFragments)`
- L1527 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`

#### struct `FMassCommandBuildEntityWithSharedFragments`  
`template<typename TSharedFragmentValues, typename... TOthers> struct FMassCommandBuildEntityWithSharedFragments : public FMassCommandAddFragmentInstancesWithSharedFragments<TSharedFragmentValues, TOthers...>`  
_L1589-1657_
- inherits: `FMassCommandAddFragmentInstancesWithSharedFragments<TSharedFragmentValues,TOthers...>`
- desc: Builds reserved entities with fragment values AND shared fragment values. Entities with the same shared fragment values are grouped for efficient archetype creation. Inherits data management from FMassCommandAddFragmentInstancesWithSharedFragments; only Run() differs. Uses PushCommand for cross-chunk batching. Note: TSharedFragmentValues is always FMassArchetypeSharedFragmentValues but is a template param to maintain uniform PushCommand interface (all params in one typename... list). Example: FMassEntityHandle Entity = EntityManager->ReserveEntity(); FMassArchetypeSharedFragmentValues SharedValues; SharedValues.Add(EntityManager->GetOrCreateConstSharedFragment(FMySharedFragment(42))); Context.Defer().PushCommand<FMassCommandBuildEntityWithSharedFragments>( Entity, MoveTemp(SharedValues), FMyFragmentA(1), FMyFragmentB(2.0f)); Supported types: FMassFragment + FMassTag (including sparse). Shared fragments via FMassArchetypeSharedFragmentValues. Breakpoint support: Yes — CheckCreateEntityBreakpoints called at PushCommand time.
- L1591 _public typedef_ `using Super = FMassCommandAddFragmentInstancesWithSharedFragments<TSharedFragmentValues, TOthers...>;`
- L1593 _public function_ `FMassCommandBuildEntityWithSharedFragments() : Super(EMassCommandOperationType::Create DEBUG_NAME("BuildEntityWithSharedFragments"))`
- L1599 _public function_ `static bool CheckBreakpoints(TOthers... InFragments)`
- L1607 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`

#### struct `FMassDeferredCommand`  
`template<EMassCommandOperationType OpType> struct FMassDeferredCommand : public FMassBatchedCommand`  
_L1686-1737_
- inherits: `FMassBatchedCommand`
- desc: Stores a lambda to execute at flush time. Maximum flexibility, no type safety. The OpType template parameter controls execution ordering relative to other commands. Multiple lambdas of the same OpType batch into a single command instance. When to use: as a last resort when no typed command fits the use case, or for complex multi-step operations that can't be expressed as a single composition change. Prefer typed commands (AddElements, RemoveElements, etc.) when possible. Example: Context.Defer().PushCommand<FMassDeferredSetCommand>([Entity](FMassEntityManager& Manager) { FMassEntityView View(Manager, Entity); View.GetFragmentData<FMyFragment>().Value = 42; }); Variants (by execution order): FMassDeferredCreateCommand, FMassDeferredAddCommand, FMassDeferredRemoveCommand, FMassDeferredChangeCompositionCommand, FMassDeferredSetCommand, FMassDeferredDestroyCommand. Breakpoint support: No. No type safety. No validation.
- L1688 _public typedef_ `using Super = FMassBatchedCommand;`
- L1689 _public typedef_ `using FExecFunction = TFunction<void(FMassEntityManager& EntityManager)>;`
- L1691 _public function_ `FMassDeferredCommand() : Super(OpType DEBUG_NAME("BatchedDeferredCommand"))`
- L1695 _public function_ `void Add(FExecFunction&& ExecFunction)`
- L1701 _public function_ `void Add(const FExecFunction& ExecFunction)`
- L1708 _protected function_ `virtual SIZE_T GetAllocatedSize() const`
- L1713 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L1723 _protected function_ `virtual void Reset() override`
- L1730 _protected function_ `virtual int32 GetNumOperationsStat() const override`
- L1736 _protected member_ `TArray<FExecFunction> DeferredFunctions;`

#### Free symbols / members of external scopes

- L134 _macro_ `# define DEBUG_NAME(Name) , FName(TEXT(Name))`
- L135 _macro_ `# define DEBUG_NAME_PARAM(Name) , const FName InDebugName = TEXT(Name)`
- L136 _macro_ `# define FORWARD_DEBUG_NAME_PARAM , InDebugName`
- L138 _macro_ `# define DEBUG_NAME(Name)`
- L139 _macro_ `# define DEBUG_NAME_PARAM(Name)`
- L140 _macro_ `# define FORWARD_DEBUG_NAME_PARAM`
- L143 _namespace_ `namespace UE`
- L143 _namespace_ `namespace Mass` (scope `UE`)
- L143 _namespace_ `namespace Utils` (scope `UE::Mass`)
- L146 _function_ `template<typename BitSetType, EMassCommandCheckTime CheckTime, typename... TTypes> BitSetType ConstructBitSet()` (scope `UE::Mass::Utils`)
- L161 _function_ `template<EMassCommandCheckTime CheckTime, typename... TTypes> FMassFragmentBitSet ConstructFragmentBitSet()` (scope `UE::Mass::Utils`)
- L167 _function_ `template<EMassCommandCheckTime CheckTime, typename... TTypes> FMassTagBitSet ConstructTagBitSet()` (scope `UE::Mass::Utils`)
- L173 _namespace_ `namespace UE`
- L173 _namespace_ `namespace Mass` (scope `UE`)
- L173 _namespace_ `namespace Command` (scope `UE::Mass`)
- L180 _enumerator_ `RequiresUniqueHandling = false` (scope `UE::Mass::Command::TCommandTraits::__anonff9272f30103`)
- L400 _enumerator_ `RequiresUniqueHandling = true` (scope `UE::Mass::Command::TCommandTraits::__anonff9272f30203`)
- L446 _enumerator_ `RequiresUniqueHandling = true` (scope `UE::Mass::Command::TCommandTraits::__anonff9272f30303`)
- L533 _enumerator_ `RequiresUniqueHandling = true` (scope `UE::Mass::Command::TCommandTraits::__anonff9272f30403`)
- L575 _typedef_ `using FCheckFn = bool(*)(const FMassEntityHandle&, const UScriptStruct*);` (scope `FMassCommandRemoveElements::CheckBreakpoints`)
- L598 _typedef_ `using FClean = UE::Mass::Clean<T>;` (scope `FMassCommandRemoveElements::CategorizeElementType`)
- L683 _typedef_ `using FCheckFn = bool(*)(const FMassEntityHandle&, const UScriptStruct*);` (scope `FMassCommandAddElements::CheckBreakpoints`)
- L732 _typedef_ `using FClean = UE::Mass::Clean<T>;` (scope `FMassCommandAddElements::CategorizeElementType`)
- L831 _enumerator_ `RequiresUniqueHandling = true` (scope `UE::Mass::Command::TCommandTraits::__anonff9272f30503`)
- L950 _typedef_ `using FClean = UE::Mass::Clean<T>;` (scope `FMassCommandAddElementsWithSharedFragments::CategorizeElementType`)
- L1052 _typedef_ `using FCheckFn = bool(*)(const FMassEntityHandle&, const UScriptStruct*);` (scope `FMassCommandAddFragmentInstancesWithSharedFragments::CheckBreakpoints`) — Function pointer to force non-template overload resolution. Without this, MSVC deduces TFragments=UScriptStruct* from StaticStruct() return type, matching the variadic template overload instead of the (FMassEntityHandle, const UScriptStruct*) overload.
- L1156 _typedef_ `using FClean = UE::Mass::Clean<T>;` (scope `FMassCommandAddFragmentInstancesWithSharedFragments::CategorizeElementType`)
- L1207 _typedef_ `template<typename... TTypes> using FMassCommandAddFragments = FMassCommandAddElements<TTypes...>;`
- L1240 _typedef_ `template<typename... TTypes> using FMassCommandRemoveFragments = FMassCommandRemoveElements<TTypes...>;`
- L1294 _typedef_ `template<typename T> using FMassCommandAddTag = FMassCommandAddElements<T>;`
- L1297 _typedef_ `template<typename... TTypes> using FMassCommandAddTags = FMassCommandAddElements<TTypes...>;`
- L1323 _typedef_ `template<typename T> using FMassCommandRemoveTag = FMassCommandRemoveElements<T>;`
- L1326 _typedef_ `template<typename... TTypes> using FMassCommandRemoveTags = FMassCommandRemoveElements<TTypes...>;`
- L1359 _typedef_ `template<typename TOld, typename TNew> using FMassCommandSwapTags = FMassCommandSwapTagsInternal<EMassCommandCheckTime::CompileTimeCheck, TOld, TNew>;`
- L1420 _typedef_ `using FCheckFn = bool(*)(const FMassEntityHandle&, const UScriptStruct*);` (scope `FMassCommandAddFragmentInstances::CheckBreakpoints`) — Function pointer to force non-template overload resolution. Without this, MSVC deduces TFragments=UScriptStruct* from StaticStruct() return type, matching the variadic template overload instead of the (FMassEntityHandle, const UScriptStruct*) overload.
- L1480 _typedef_ `using FClean = UE::Mass::Clean<T>;` (scope `FMassCommandAddFragmentInstances::CategorizeElementType`)
- L1739 _typedef_ `using FMassDeferredCreateCommand = FMassDeferredCommand<EMassCommandOperationType::Create>;`
- L1740 _typedef_ `using FMassDeferredAddCommand = FMassDeferredCommand<EMassCommandOperationType::Add>;`
- L1741 _typedef_ `using FMassDeferredRemoveCommand = FMassDeferredCommand<EMassCommandOperationType::Remove>;`
- L1742 _typedef_ `using FMassDeferredChangeCompositionCommand = FMassDeferredCommand<EMassCommandOperationType::ChangeComposition>;`
- L1743 _typedef_ `using FMassDeferredSetCommand = FMassDeferredCommand<EMassCommandOperationType::Set>;`
- L1744 _typedef_ `using FMassDeferredDestroyCommand = FMassDeferredCommand<EMassCommandOperationType::Destroy>;`

### `Source/Runtime/MassEntity/Public/MassDebugLogging.h` (Public)


#### struct `FMassDebugLogFragment`  
`struct FMassDebugLogFragment : public FMassFragment`  
_L20-26_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L25 _public member_ `TWeakObjectPtr<const UObject> LogOwner = nullptr;` — `UPROPERTY()`

#### struct `UE::Mass::Debug::FLoggingContext`  
`struct FLoggingContext`  
_L30-88_
- L33 _public function_ `explicit FLoggingContext(const FMassExecutionContext& InContext, bool bInLogEverythingWhenRecording = true) : DebugFragmentsView(InContext.GetFragmentView<FMassDebugLogFragment>()) , EntityListView(InContext.GetEntities()) , bLogEverythingWhenRecording(bInLogEverythingWhenRecording)`
- L40 _public function_ `inline bool ShouldLogEntity(int32 EntityIndex, FColor* OutEntityColor = nullptr) const`
- L56 _public function_ `inline const UObject* GetLogOwner(int32 EntityIndex, const UObject* FallbackOwner = nullptr) const`
- L64 _private member_ `const TConstArrayView<FMassDebugLogFragment> DebugFragmentsView;`
- L65 _private member_ `const TConstArrayView<FMassEntityHandle> EntityListView;`
- L70 _private member_ `const bool bLogEverythingWhenRecording = true;` — If true, ShouldLogEntity will return true when the visual logger is recording If false, ShouldLogEntity will rely only on the MassDebugger

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Mass` (scope `UE`)
- L28 _namespace_ `namespace Debug` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassDebugger.h` (Public)


#### struct `UE::Mass::Debug::FArchetypeStats`  
`struct FArchetypeStats`  
_L37-57_
- L40 _public member_ `int32 EntitiesCount = 0;` — Number of active entities of the archetype.
- L42 _public member_ `int32 EntitiesCountPerChunk = 0;` — Number of entities that fit per chunk.
- L44 _public member_ `int32 ChunksCount = 0;` — Number of allocated chunks.
- L46 _public member_ `SIZE_T AllocatedSize = 0;` — Total amount of memory taken by this archetype. Includes SparseElementsBookkeepingSize.
- L48 _public member_ `SIZE_T WastedEntityMemory = 0;` — How much memory allocated for entities is being unused
- L50 _public member_ `SIZE_T BytesPerEntity = 0;` — Total amount of memory needed by a single entity
- L56 _public member_ `SIZE_T SparseElementsBookkeepingSize = 0;` — Memory used by per-chunk sparse element bookkeeping (FChunkSparseElements). Reported as a subset of AllocatedSize so it can be displayed separately. Will be zero for archetypes whose chunks carry no sparse elements.

#### struct `FMassGenericDebugEvent`  
`struct FMassGenericDebugEvent`  
_L63-77_
- reflection: `USTRUCT()`
- L66 _public function_ `explicit FMassGenericDebugEvent(const UObject* InContext = nullptr) #if WITH_EDITORONLY_DATA : Context(InContext) #endif`
- L75 _public member_ `const UObject* Context = nullptr;` — note that it's not a uproperty since these events are only intended to be used instantly, never stored

#### enum `EMassDebugMessageSeverity`  
`enum class EMassDebugMessageSeverity : uint8`  
_L94-102_
- L96 _public enumerator_ `Error`
- L97 _public enumerator_ `Warning`
- L98 _public enumerator_ `Info`
- L100 _public enumerator_ `Default` — the following two need to remain last
- L101 _public enumerator_ `MAX = Default`

#### struct `UE::Mass::Debug::FQueryRequirementsView`  
`struct FQueryRequirementsView`  
_L106-118_
- L108 _public member_ `TConstArrayView<FMassFragmentRequirementDescription> FragmentRequirements;`
- L109 _public member_ `TConstArrayView<FMassFragmentRequirementDescription> ChunkRequirements;`
- L110 _public member_ `TConstArrayView<FMassFragmentRequirementDescription> ConstSharedRequirements;`
- L111 _public member_ `TConstArrayView<FMassFragmentRequirementDescription> SharedRequirements;`
- L112 _public member_ `const FMassTagBitSet& RequiredAllTags;`
- L113 _public member_ `const FMassTagBitSet& RequiredAnyTags;`
- L114 _public member_ `const FMassTagBitSet& RequiredNoneTags;`
- L115 _public member_ `const FMassTagBitSet& RequiredOptionalTags;`
- L116 _public member_ `const FMassExternalSubsystemBitSet& RequiredConstSubsystems;`
- L117 _public member_ `const FMassExternalSubsystemBitSet& RequiredMutableSubsystems;`

#### struct `FMassDebugger`  
`struct FMassDebugger`  
_L156-457_
- L191 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnBreakpointsChanged);`
- L192 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnEntitySelected, const FMassEntityManager&, const FMassEntityHandle);`
- L193 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnMassEntityManagerEvent, const FMassEntityManager&);`
- L194 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnEnvironmentEvent, const FEnvironment&);`
- L195 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnDebugEvent, const FName , FConstStructView , const EMassDebugMessageSeverity );`
- L197 _public prototype_ `static TConstArrayView<FMassEntityQuery*> GetProcessorQueries(const UMassProcessor& Processor);`
- L200 _public prototype_ `static TConstArrayView<FMassEntityQuery*> GetUpToDateProcessorQueries(const FMassEntityManager& EntityManager, UMassProcessor& Processor);` — fetches all queries registered for given Processor. Note that in order to get up to date information FMassEntityQuery::CacheArchetypes will be called on each query
- L202 _public prototype_ `static UE::Mass::Debug::FQueryRequirementsView GetQueryRequirements(const FMassEntityQuery& Query);`
- L203 _public prototype_ `static void GetQueryExecutionRequirements(const FMassEntityQuery& Query, FMassExecutionRequirements& OutExecutionRequirements);`
- L204 _public prototype_ `static TArray<FMassEntityHandle> GetEntitiesMatchingQuery(const FMassEntityManager& EntityManager, const FMassEntityQuery& Query);`
- L206 _public prototype_ `static void ForEachArchetype(const FMassEntityManager& EntityManager, const UE::Mass::Debug::FArchetypeFunction& Function);`
- L207 _public prototype_ `static TArray<FMassArchetypeHandle> GetAllArchetypes(const FMassEntityManager& EntityManager);`
- L208 _public prototype_ `static FMassArchetypeCompositionDescriptor GetArchetypeComposition(const FMassArchetypeHandle& ArchetypeHandle);`
- L209 _public prototype_ `static FMassElementBitSet GetArchetypeSparseElementsBitset(const FMassArchetypeHandle& ArchetypeHandle);`
- L211 _public prototype_ `static uint64 GetArchetypeTraceID(const FMassArchetypeData& ArchetypeData);`
- L212 _public prototype_ `static uint64 GetArchetypeTraceID(const FMassArchetypeHandle& ArchetypeHandle);`
- L214 _public prototype_ `static TConstArrayView<FMassEntityHandle> GetEntitiesViewOfArchetype( const FMassArchetypeData& ArchetypeData, const FMassArchetypeChunk& Chunk);`
- L218 _public prototype_ `static const FMassArchetypeData* GetArchetypeData(const FMassArchetypeHandle& ArchetypeHandle);`
- L219 _public prototype_ `static void EnumerateChunks(const FMassArchetypeData& Archetype, TFunctionRef<void(const FMassArchetypeChunk&)> Fn);`
- L221 _public prototype_ `static void GetArchetypeEntityStats(const FMassArchetypeHandle& ArchetypeHandle, UE::Mass::Debug::FArchetypeStats& OutStats);`
- L222 _public prototype_ `static const TConstArrayView<FName> GetArchetypeDebugNames(const FMassArchetypeHandle& ArchetypeHandle);`
- L223 _public prototype_ `static TArray<FMassEntityHandle> GetEntitiesOfArchetype(const FMassArchetypeHandle& ArchetypeHandle);`
- L225 _public prototype_ `static TConstArrayView<UMassCompositeProcessor::FDependencyNode> GetProcessingGraph(const UMassCompositeProcessor& GraphOwner);`
- L226 _public prototype_ `static TConstArrayView<TObjectPtr<UMassProcessor>> GetHostedProcessors(const UMassCompositeProcessor& GraphOwner);`
- L228 _public prototype_ `static FString GetSingleRequirementDescription(const FMassFragmentRequirementDescription& Requirement);`
- L229 _public prototype_ `static FString GetRequirementsDescription(const FMassFragmentRequirements& Requirements);`
- L230 _public prototype_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements& Requirements, const FMassArchetypeHandle& ArchetypeHandle);`
- L231 _public prototype_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements& Requirements, const FMassElementBitSet& ArchetypeCompositionBitSet);`
- L232 _public function_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements& Requirements, const FMassArchetypeCompositionDescriptor& ArchetypeComposition)`
- L237 _public prototype_ `static void OutputArchetypeDescription(FOutputDevice& Ar, const FMassArchetypeHandle& Archetype);`
- L238 _public prototype_ `static void OutputEntityDescription(FOutputDevice& Ar, const FMassEntityManager& EntityManager, const int32 EntityIndex, const TCHAR* InPrefix = TEXT(""));`
- L239 _public prototype_ `static void OutputEntityDescription(FOutputDevice& Ar, const FMassEntityManager& EntityManager, const FMassEntityHandle Entity, const TCHAR* InPrefix = TEXT(""));`
- L241 _public prototype_ `static void SelectEntity(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L242 _public prototype_ `static FMassEntityHandle GetSelectedEntity(const FMassEntityManager& EntityManager);`
- L244 _public prototype_ `static void HighlightEntity(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L245 _public prototype_ `static FMassEntityHandle GetHighlightedEntity(const FMassEntityManager& EntityManager);`
- L247 _public member_ `static FOnBreakpointsChanged OnBreakpointsChangedDelegate;`
- L248 _public member_ `static FOnEntitySelected OnEntitySelectedDelegate;`
- L250 _public member_ `static FOnMassEntityManagerEvent OnEntityManagerInitialized;`
- L251 _public member_ `static FOnMassEntityManagerEvent OnEntityManagerDeinitialized;`
- L252 _public member_ `static FOnEnvironmentEvent OnProcessorProviderRegistered;`
- L254 _public member_ `static FOnDebugEvent OnDebugEvent;`
- L256 _public function_ `static void DebugEvent(const FName EventName, FConstStructView Payload, const EMassDebugMessageSeverity SeverityOverride = EMassDebugMessageSeverity::Default)`
- L262 _public function_ `template<typename TMessage, typename... TArgs> static void DebugEvent(TArgs&&... InArgs)`
- L272 _public prototype_ `static int32 RegisterEntityManager(FMassEntityManager& EntityManager);` — Registers given EntityManager with the debugger, creating a new entry in ActiveEnvironments. @return the index of newly created environment
- L273 _public prototype_ `static void UnregisterEntityManager(FMassEntityManager& EntityManager);`
- L279 _public prototype_ `static bool IsEntityManagerInitialized(const FMassEntityManager& EntityManager);` — Confirms that the initialization state of the EntityManager is Initialized. @return true if EntityManager is initialized, false otherwise
- L288 _public prototype_ `static void RegisterProcessorDataProvider(FName ProviderName, const TSharedRef<FMassEntityManager>& EntityManager, const UE::Mass::Debug::FProcessorProviderFunction& ProviderFunction);` — Registers the given ProviderFunction with the existing FEnvironment associated with the provided EntityManager. If one doesn't exist yet, it will be created (i.e. will automatically call RegisterEntityManager() with the provided EntityManager). The function will be called during data collection for the given FEnvironment. NOTE: there's no UnregisterProcessorDataProvider, the registered providers will automatically get removed along with the rest of the data associated with the relevant EntityManager as part of UnregisterEntityManager call.
- L290 _public function_ `static TConstArrayView<FEnvironment> GetEnvironments()`
- L294 _public prototype_ `static FEnvironment* FindEnvironmentForEntityManager(const FMassEntityManager& EntityManager);`
- L299 _public prototype_ `static bool DoesArchetypeMatchRequirements(const FMassArchetypeHandle& ArchetypeHandle, const FMassFragmentRequirements& Requirements, FOutputDevice& OutputDevice);` — Determines whether given Archetype matches given Requirements. In case of a mismatch description of failed conditions will be added to OutputDevice.
- L304 _public prototype_ `static UE::Mass::Debug::FBreakpointHandle ShouldProcessorBreak(const FMassEntityManager& EntityManager, const UMassProcessor* Processor, FMassEntityHandle Entity);` — Checks if a processor should break on execute for a given entity. Returns the Id for the breakpoint if one is found, or 0.
- L309 _public prototype_ `static bool HasAnyProcessorBreakpoints(const FMassEntityManager& EntityManager, const UMassProcessor* Processor);` — Checks if a processor has any breakpoints set for any entity.
- L314 _public prototype_ `static UE::Mass::Debug::FBreakpointHandle ShouldBreakOnFragmentWrite(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Checks if a break should be triggered for a processor that's about to write a given fragment on an entity. Returns the Id for the breakpoint if one is found (Invalid otherwise).
- L319 _public prototype_ `static UE::Mass::Debug::FBreakpoint* FindBreakpoint(const FMassEntityManager& EntityManager, UE::Mass::Debug::FBreakpointHandle Handle);` — Find a breakpoint by Handle. Returns the pointer to the Breakpoint, or nullptr if none found.
- L324 _public prototype_ `static TArray<UE::Mass::Debug::FBreakpoint>& GetBreakpoints(const FMassEntityManager& EntityManager);` — Get all the breakpoints for a given environment.
- L329 _public prototype_ `static void RefreshBreakpoints();` — Refresh breakpoint flags after changes to breakpoint instances.
- L335 _public prototype_ `static bool HasAnyFragmentWriteBreakpoints(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType = nullptr);` — Checks if there are any breakpoints set for writing a fragment for any entity Use FragmentType = nullptr (default) to check for ANY fragment types.
- L340 _public prototype_ `static UE::Mass::Debug::FBreakpoint& CreateBreakpoint(const FMassEntityManager& EntityManager);` — Create a default-constructed breakpoint
- L345 _public prototype_ `static void SetProcessorBreakpoint(const FMassEntityManager& EntityManager, TNotNull<const UMassProcessor*>, FMassEntityHandle Entity);` — Sets a break to be triggered on processor execute for an entity.
- L350 _public prototype_ `static void SetFragmentWriteBreakpoint(const FMassEntityManager& EntityManager, TNotNull<const UScriptStruct*> FragmentType, FMassEntityHandle Entity);` — Sets a break to be triggered for a processor that's about to write a given fragment on an entity.
- L355 _public prototype_ `static void SetFragmentWriteBreakForSelectedEntity(const FMassEntityManager& EntityManager, TNotNull<const UScriptStruct*> FragmentType);` — Sets or removes a break before a write to a given fragment on whichever entity is selected at the time.
- L360 _public prototype_ `static void SetBreakpointEnabled(UE::Mass::Debug::FBreakpointHandle Handle, bool bEnable);` — Enable or Disable a breakpoint with a given Id.
- L365 _public prototype_ `static void ClearProcessorBreakpoint(const FMassEntityManager& EntityManager, const UMassProcessor* Processor, FMassEntityHandle Entity);` — Clears a breakpoint triggered on processor execute for an entity.
- L370 _public prototype_ `static void ClearAllProcessorBreakpoints(const FMassEntityManager& EntityManager, const UMassProcessor* Processor);` — Clears all breakpoints set for a given processor.
- L375 _public prototype_ `static void ClearFragmentWriteBreak(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Clears a fragment write breakpoint for a given fragment type and entity.
- L380 _public prototype_ `static void ClearAllFragmentWriteBreak(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType);` — Clears all write breakpoints set for a given fragment type.
- L385 _public prototype_ `static void ClearAllEntityBreakpoints(const FMassEntityManager& EntityManager, FMassEntityHandle Entity);` — Clears all breakpoints set for a given entity.
- L391 _public prototype_ `static void BreakOnFragmentWriteForSelectedEntity(FName FragmentName);` — Sets a write breakpoint for the specified fragment on the selcected entity @see SelectEntity
- L396 _public prototype_ `static const UScriptStruct* GetFragmentTypeFromName(FName FragmentName);` — Gets the UScriptStruct type for fragment of the specified name.
- L401 _public prototype_ `static TSharedPtr<FStructOnScope> GetFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Finds the fragment data of the specified type in the entity data. Returns nullptr if not found.
- L406 _public prototype_ `static bool GetFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity, TSharedPtr<FStructOnScope>& OutStructData);` — Finds the fragment data of the specified type in the entity data. Returns false if not found.
- L411 _public prototype_ `static const FMassArchetypeSharedFragmentValues& GetSharedFragmentValues(const FMassEntityManager& EntityManager, FMassEntityHandle Entity);` — Get the shared fragment value container for this entity
- L416 _public prototype_ `static TSharedPtr<FStructOnScope> GetSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Finds the shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L421 _public prototype_ `static bool GetSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity, TSharedPtr<FStructOnScope>& OutStructData);` — Finds the shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L426 _public prototype_ `static TSharedPtr<FStructOnScope> GetConstSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Finds the const shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L431 _public prototype_ `static bool GetConstSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity, TSharedPtr<FStructOnScope>& OutStructData);` — Finds the const shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L436 _public prototype_ `static void ClearAllBreakpoints();` — Clears all breakpoints in all environments.
- L441 _public prototype_ `static void RemoveBreakpoint(UE::Mass::Debug::FBreakpointHandle Handle);` — Remove a single breakpoint by Id
- L446 _public prototype_ `static void ShutdownDebugger();` — Destroy all debug environments and shutdown cleanly.
- L450 _private member_ `static TArray<FEnvironment> ActiveEnvironments;` — @todo: contain static data in an instanced struct and setup/teardown in startup/shutdown module
- L451 _private member_ `static UE::FTransactionallySafeMutex EntityManagerRegistrationLock;`
- L452 _private member_ `static TMap<FName, const UScriptStruct*> FragmentsByName;`
- L453 _private member_ `static TArray<FName> CommandNames;`
- L455 _private prototype_ `static FEnvironment& GetActiveEnvironmentChecked(const FMassEntityManager& EntityManager);`
- L456 _private prototype_ `static FEnvironment* GetActiveEnvironment(const FMassEntityManager& EntityManager);`
- L469 _public function_ `static FString GetSingleRequirementDescription(const FMassFragmentRequirementDescription&)`
- L473 _public function_ `static FString GetRequirementsDescription(const FMassFragmentRequirements&)`
- L477 _public function_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements&, const FMassArchetypeHandle&)`
- L481 _public function_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements&, const FMassArchetypeCompositionDescriptor&)`

#### struct `FMassDebugger::FEnvironment`  
`struct FEnvironment`  
_L158-189_
- L160 _public member_ `TWeakPtr<const FMassEntityManager> EntityManager;`
- L161 _public member_ `TWeakPtr<FMassEntityManager> MutableEntityManager;`
- L162 _public member_ `TMap<FName, UE::Mass::Debug::FProcessorProviderFunction> ProcessorProviders;`
- L163 _public member_ `FMassEntityHandle SelectedEntity;`
- L164 _public member_ `FMassEntityHandle HighlightedEntity;`
- L166 _public member_ `bool bHasBreakpoint = false;`
- L168 _public member_ `TArray<UE::Mass::Debug::FBreakpoint> Breakpoints;`
- L170 _public prototype_ `UE::Mass::Debug::FBreakpoint* FindBreakpointByHandle(UE::Mass::Debug::FBreakpointHandle Handle);`
- L173 _public member_ `TSet<TObjectKey<const UMassProcessor>> ProcessorsWithBreakpoints;` — quick lookup to skip processors and fragments with no breakpoints set
- L174 _public member_ `TSet<TObjectKey<const UScriptStruct>> FragmentsWithBreakpoints;`
- L177 _public member_ `FDelegateHandle TraceStartedDelegateHandle;`
- L180 _public prototype_ `explicit FEnvironment(FMassEntityManager& InEntityManager);`
- L181 _public prototype_ `~FEnvironment();`
- L183 _public function_ `bool IsValid() const`
- L188 _public prototype_ `void ClearBreakpoints();`

#### struct `FMassDebugger`  
`struct FMassDebugger`  
_L467-485_
- L191 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnBreakpointsChanged);`
- L192 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnEntitySelected, const FMassEntityManager&, const FMassEntityHandle);`
- L193 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnMassEntityManagerEvent, const FMassEntityManager&);`
- L194 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnEnvironmentEvent, const FEnvironment&);`
- L195 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnDebugEvent, const FName , FConstStructView , const EMassDebugMessageSeverity );`
- L197 _public prototype_ `static TConstArrayView<FMassEntityQuery*> GetProcessorQueries(const UMassProcessor& Processor);`
- L200 _public prototype_ `static TConstArrayView<FMassEntityQuery*> GetUpToDateProcessorQueries(const FMassEntityManager& EntityManager, UMassProcessor& Processor);` — fetches all queries registered for given Processor. Note that in order to get up to date information FMassEntityQuery::CacheArchetypes will be called on each query
- L202 _public prototype_ `static UE::Mass::Debug::FQueryRequirementsView GetQueryRequirements(const FMassEntityQuery& Query);`
- L203 _public prototype_ `static void GetQueryExecutionRequirements(const FMassEntityQuery& Query, FMassExecutionRequirements& OutExecutionRequirements);`
- L204 _public prototype_ `static TArray<FMassEntityHandle> GetEntitiesMatchingQuery(const FMassEntityManager& EntityManager, const FMassEntityQuery& Query);`
- L206 _public prototype_ `static void ForEachArchetype(const FMassEntityManager& EntityManager, const UE::Mass::Debug::FArchetypeFunction& Function);`
- L207 _public prototype_ `static TArray<FMassArchetypeHandle> GetAllArchetypes(const FMassEntityManager& EntityManager);`
- L208 _public prototype_ `static FMassArchetypeCompositionDescriptor GetArchetypeComposition(const FMassArchetypeHandle& ArchetypeHandle);`
- L209 _public prototype_ `static FMassElementBitSet GetArchetypeSparseElementsBitset(const FMassArchetypeHandle& ArchetypeHandle);`
- L211 _public prototype_ `static uint64 GetArchetypeTraceID(const FMassArchetypeData& ArchetypeData);`
- L212 _public prototype_ `static uint64 GetArchetypeTraceID(const FMassArchetypeHandle& ArchetypeHandle);`
- L214 _public prototype_ `static TConstArrayView<FMassEntityHandle> GetEntitiesViewOfArchetype( const FMassArchetypeData& ArchetypeData, const FMassArchetypeChunk& Chunk);`
- L218 _public prototype_ `static const FMassArchetypeData* GetArchetypeData(const FMassArchetypeHandle& ArchetypeHandle);`
- L219 _public prototype_ `static void EnumerateChunks(const FMassArchetypeData& Archetype, TFunctionRef<void(const FMassArchetypeChunk&)> Fn);`
- L221 _public prototype_ `static void GetArchetypeEntityStats(const FMassArchetypeHandle& ArchetypeHandle, UE::Mass::Debug::FArchetypeStats& OutStats);`
- L222 _public prototype_ `static const TConstArrayView<FName> GetArchetypeDebugNames(const FMassArchetypeHandle& ArchetypeHandle);`
- L223 _public prototype_ `static TArray<FMassEntityHandle> GetEntitiesOfArchetype(const FMassArchetypeHandle& ArchetypeHandle);`
- L225 _public prototype_ `static TConstArrayView<UMassCompositeProcessor::FDependencyNode> GetProcessingGraph(const UMassCompositeProcessor& GraphOwner);`
- L226 _public prototype_ `static TConstArrayView<TObjectPtr<UMassProcessor>> GetHostedProcessors(const UMassCompositeProcessor& GraphOwner);`
- L228 _public prototype_ `static FString GetSingleRequirementDescription(const FMassFragmentRequirementDescription& Requirement);`
- L229 _public prototype_ `static FString GetRequirementsDescription(const FMassFragmentRequirements& Requirements);`
- L230 _public prototype_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements& Requirements, const FMassArchetypeHandle& ArchetypeHandle);`
- L231 _public prototype_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements& Requirements, const FMassElementBitSet& ArchetypeCompositionBitSet);`
- L232 _public function_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements& Requirements, const FMassArchetypeCompositionDescriptor& ArchetypeComposition)`
- L237 _public prototype_ `static void OutputArchetypeDescription(FOutputDevice& Ar, const FMassArchetypeHandle& Archetype);`
- L238 _public prototype_ `static void OutputEntityDescription(FOutputDevice& Ar, const FMassEntityManager& EntityManager, const int32 EntityIndex, const TCHAR* InPrefix = TEXT(""));`
- L239 _public prototype_ `static void OutputEntityDescription(FOutputDevice& Ar, const FMassEntityManager& EntityManager, const FMassEntityHandle Entity, const TCHAR* InPrefix = TEXT(""));`
- L241 _public prototype_ `static void SelectEntity(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L242 _public prototype_ `static FMassEntityHandle GetSelectedEntity(const FMassEntityManager& EntityManager);`
- L244 _public prototype_ `static void HighlightEntity(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L245 _public prototype_ `static FMassEntityHandle GetHighlightedEntity(const FMassEntityManager& EntityManager);`
- L247 _public member_ `static FOnBreakpointsChanged OnBreakpointsChangedDelegate;`
- L248 _public member_ `static FOnEntitySelected OnEntitySelectedDelegate;`
- L250 _public member_ `static FOnMassEntityManagerEvent OnEntityManagerInitialized;`
- L251 _public member_ `static FOnMassEntityManagerEvent OnEntityManagerDeinitialized;`
- L252 _public member_ `static FOnEnvironmentEvent OnProcessorProviderRegistered;`
- L254 _public member_ `static FOnDebugEvent OnDebugEvent;`
- L256 _public function_ `static void DebugEvent(const FName EventName, FConstStructView Payload, const EMassDebugMessageSeverity SeverityOverride = EMassDebugMessageSeverity::Default)`
- L262 _public function_ `template<typename TMessage, typename... TArgs> static void DebugEvent(TArgs&&... InArgs)`
- L272 _public prototype_ `static int32 RegisterEntityManager(FMassEntityManager& EntityManager);` — Registers given EntityManager with the debugger, creating a new entry in ActiveEnvironments. @return the index of newly created environment
- L273 _public prototype_ `static void UnregisterEntityManager(FMassEntityManager& EntityManager);`
- L279 _public prototype_ `static bool IsEntityManagerInitialized(const FMassEntityManager& EntityManager);` — Confirms that the initialization state of the EntityManager is Initialized. @return true if EntityManager is initialized, false otherwise
- L288 _public prototype_ `static void RegisterProcessorDataProvider(FName ProviderName, const TSharedRef<FMassEntityManager>& EntityManager, const UE::Mass::Debug::FProcessorProviderFunction& ProviderFunction);` — Registers the given ProviderFunction with the existing FEnvironment associated with the provided EntityManager. If one doesn't exist yet, it will be created (i.e. will automatically call RegisterEntityManager() with the provided EntityManager). The function will be called during data collection for the given FEnvironment. NOTE: there's no UnregisterProcessorDataProvider, the registered providers will automatically get removed along with the rest of the data associated with the relevant EntityManager as part of UnregisterEntityManager call.
- L290 _public function_ `static TConstArrayView<FEnvironment> GetEnvironments()`
- L294 _public prototype_ `static FEnvironment* FindEnvironmentForEntityManager(const FMassEntityManager& EntityManager);`
- L299 _public prototype_ `static bool DoesArchetypeMatchRequirements(const FMassArchetypeHandle& ArchetypeHandle, const FMassFragmentRequirements& Requirements, FOutputDevice& OutputDevice);` — Determines whether given Archetype matches given Requirements. In case of a mismatch description of failed conditions will be added to OutputDevice.
- L304 _public prototype_ `static UE::Mass::Debug::FBreakpointHandle ShouldProcessorBreak(const FMassEntityManager& EntityManager, const UMassProcessor* Processor, FMassEntityHandle Entity);` — Checks if a processor should break on execute for a given entity. Returns the Id for the breakpoint if one is found, or 0.
- L309 _public prototype_ `static bool HasAnyProcessorBreakpoints(const FMassEntityManager& EntityManager, const UMassProcessor* Processor);` — Checks if a processor has any breakpoints set for any entity.
- L314 _public prototype_ `static UE::Mass::Debug::FBreakpointHandle ShouldBreakOnFragmentWrite(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Checks if a break should be triggered for a processor that's about to write a given fragment on an entity. Returns the Id for the breakpoint if one is found (Invalid otherwise).
- L319 _public prototype_ `static UE::Mass::Debug::FBreakpoint* FindBreakpoint(const FMassEntityManager& EntityManager, UE::Mass::Debug::FBreakpointHandle Handle);` — Find a breakpoint by Handle. Returns the pointer to the Breakpoint, or nullptr if none found.
- L324 _public prototype_ `static TArray<UE::Mass::Debug::FBreakpoint>& GetBreakpoints(const FMassEntityManager& EntityManager);` — Get all the breakpoints for a given environment.
- L329 _public prototype_ `static void RefreshBreakpoints();` — Refresh breakpoint flags after changes to breakpoint instances.
- L335 _public prototype_ `static bool HasAnyFragmentWriteBreakpoints(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType = nullptr);` — Checks if there are any breakpoints set for writing a fragment for any entity Use FragmentType = nullptr (default) to check for ANY fragment types.
- L340 _public prototype_ `static UE::Mass::Debug::FBreakpoint& CreateBreakpoint(const FMassEntityManager& EntityManager);` — Create a default-constructed breakpoint
- L345 _public prototype_ `static void SetProcessorBreakpoint(const FMassEntityManager& EntityManager, TNotNull<const UMassProcessor*>, FMassEntityHandle Entity);` — Sets a break to be triggered on processor execute for an entity.
- L350 _public prototype_ `static void SetFragmentWriteBreakpoint(const FMassEntityManager& EntityManager, TNotNull<const UScriptStruct*> FragmentType, FMassEntityHandle Entity);` — Sets a break to be triggered for a processor that's about to write a given fragment on an entity.
- L355 _public prototype_ `static void SetFragmentWriteBreakForSelectedEntity(const FMassEntityManager& EntityManager, TNotNull<const UScriptStruct*> FragmentType);` — Sets or removes a break before a write to a given fragment on whichever entity is selected at the time.
- L360 _public prototype_ `static void SetBreakpointEnabled(UE::Mass::Debug::FBreakpointHandle Handle, bool bEnable);` — Enable or Disable a breakpoint with a given Id.
- L365 _public prototype_ `static void ClearProcessorBreakpoint(const FMassEntityManager& EntityManager, const UMassProcessor* Processor, FMassEntityHandle Entity);` — Clears a breakpoint triggered on processor execute for an entity.
- L370 _public prototype_ `static void ClearAllProcessorBreakpoints(const FMassEntityManager& EntityManager, const UMassProcessor* Processor);` — Clears all breakpoints set for a given processor.
- L375 _public prototype_ `static void ClearFragmentWriteBreak(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Clears a fragment write breakpoint for a given fragment type and entity.
- L380 _public prototype_ `static void ClearAllFragmentWriteBreak(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType);` — Clears all write breakpoints set for a given fragment type.
- L385 _public prototype_ `static void ClearAllEntityBreakpoints(const FMassEntityManager& EntityManager, FMassEntityHandle Entity);` — Clears all breakpoints set for a given entity.
- L391 _public prototype_ `static void BreakOnFragmentWriteForSelectedEntity(FName FragmentName);` — Sets a write breakpoint for the specified fragment on the selcected entity @see SelectEntity
- L396 _public prototype_ `static const UScriptStruct* GetFragmentTypeFromName(FName FragmentName);` — Gets the UScriptStruct type for fragment of the specified name.
- L401 _public prototype_ `static TSharedPtr<FStructOnScope> GetFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Finds the fragment data of the specified type in the entity data. Returns nullptr if not found.
- L406 _public prototype_ `static bool GetFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity, TSharedPtr<FStructOnScope>& OutStructData);` — Finds the fragment data of the specified type in the entity data. Returns false if not found.
- L411 _public prototype_ `static const FMassArchetypeSharedFragmentValues& GetSharedFragmentValues(const FMassEntityManager& EntityManager, FMassEntityHandle Entity);` — Get the shared fragment value container for this entity
- L416 _public prototype_ `static TSharedPtr<FStructOnScope> GetSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Finds the shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L421 _public prototype_ `static bool GetSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity, TSharedPtr<FStructOnScope>& OutStructData);` — Finds the shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L426 _public prototype_ `static TSharedPtr<FStructOnScope> GetConstSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity);` — Finds the const shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L431 _public prototype_ `static bool GetConstSharedFragmentData(const FMassEntityManager& EntityManager, const UScriptStruct* FragmentType, FMassEntityHandle Entity, TSharedPtr<FStructOnScope>& OutStructData);` — Finds the const shared fragment data of the specified type in the entity data. Returns nullptr if not found.
- L436 _public prototype_ `static void ClearAllBreakpoints();` — Clears all breakpoints in all environments.
- L441 _public prototype_ `static void RemoveBreakpoint(UE::Mass::Debug::FBreakpointHandle Handle);` — Remove a single breakpoint by Id
- L446 _public prototype_ `static void ShutdownDebugger();` — Destroy all debug environments and shutdown cleanly.
- L450 _private member_ `static TArray<FEnvironment> ActiveEnvironments;` — @todo: contain static data in an instanced struct and setup/teardown in startup/shutdown module
- L451 _private member_ `static UE::FTransactionallySafeMutex EntityManagerRegistrationLock;`
- L452 _private member_ `static TMap<FName, const UScriptStruct*> FragmentsByName;`
- L453 _private member_ `static TArray<FName> CommandNames;`
- L455 _private prototype_ `static FEnvironment& GetActiveEnvironmentChecked(const FMassEntityManager& EntityManager);`
- L456 _private prototype_ `static FEnvironment* GetActiveEnvironment(const FMassEntityManager& EntityManager);`
- L469 _public function_ `static FString GetSingleRequirementDescription(const FMassFragmentRequirementDescription&)`
- L473 _public function_ `static FString GetRequirementsDescription(const FMassFragmentRequirements&)`
- L477 _public function_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements&, const FMassArchetypeHandle&)`
- L481 _public function_ `static FString GetArchetypeRequirementCompatibilityDescription(const FMassFragmentRequirements&, const FMassArchetypeCompositionDescriptor&)`

#### Free symbols / members of external scopes

- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Mass` (scope `UE`)
- L35 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L59 _typedef_ `using FProcessorProviderFunction = TFunction<void(TArray<const UMassProcessor*>&)>;` (scope `UE::Mass::Debug`)
- L81 _namespace_ `namespace UE`
- L81 _namespace_ `namespace Mass` (scope `UE`)
- L81 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L83 _externvar_ `extern bool bAllowProceduralDebuggedEntitySelection;` (scope `UE::Mass::Debug`)
- L84 _externvar_ `extern bool bAllowBreakOnDebuggedEntity;` (scope `UE::Mass::Debug`)
- L85 _externvar_ `extern bool bTestSelectedEntityAgainstProcessorQueries;` (scope `UE::Mass::Debug`)
- L86 _typedef_ `using FArchetypeFunction = TFunction<void(FMassArchetypeHandle)>;` (scope `UE::Mass::Debug`)
- L89 _macro_ `#define MASS_IF_ENTITY_DEBUGGED(Manager, EntityHandle) (FMassDebugger::GetSelectedEntity(Manager) == EntityHandle)`
- L90 _macro_ `#define MASS_BREAK_IF_ENTITY_DEBUGGED(Manager, EntityHandle) { if (UE::Mass::Debug::bAllowBreakOnDebuggedEntity && MASS_IF_ENTITY_DEBUGGED(Manager, EntityHandle)) { PLATFORM_BREAK();} }`
- L91 _macro_ `#define MASS_BREAK_IF_ENTITY_INDEX(EntityHandle, InIndex) { if (UE::Mass::Debug::bAllowBreakOnDebuggedEntity && EntityHandle.Index == InIndex) { PLATFORM_BREAK();} }`
- L92 _macro_ `#define MASS_SET_ENTITY_DEBUGGED(Manager, EntityHandle) { if (UE::Mass::Debug::bAllowProceduralDebuggedEntitySelection) {FMassDebugger::SelectEntity(Manager, EntityHandle); }}`
- L104 _namespace_ `namespace UE`
- L104 _namespace_ `namespace Mass` (scope `UE`)
- L104 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L120 _prototype_ `FString DebugGetFragmentAccessString(EMassFragmentAccess Access);` (scope `UE::Mass::Debug`)
- L121 _prototype_ `extern void DebugOutputDescription(TConstArrayView<UMassProcessor*> Processors, FOutputDevice& Ar);` (scope `UE::Mass::Debug`)
- L123 _prototype_ `extern bool HasDebugEntities();` (scope `UE::Mass::Debug`)
- L124 _prototype_ `extern bool IsDebuggingSingleEntity();` (scope `UE::Mass::Debug`)
- L131 _prototype_ `extern bool GetDebugEntitiesRange(int32& OutBegin, int32& OutEnd);` (scope `UE::Mass::Debug`) — Populates OutBegin and OutEnd with entity index ranges as set by mass.debug.SetDebugEntityRange or mass.debug.DebugEntity console commands. @return whether any range has been configured.
- L132 _prototype_ `extern bool IsDebuggingEntity(FMassEntityHandle Entity, FColor* OutEntityColor = nullptr);` (scope `UE::Mass::Debug`)
- L133 _prototype_ `extern FColor GetEntityDebugColor(FMassEntityHandle Entity);` (scope `UE::Mass::Debug`)
- L140 _prototype_ `extern UWorld* GetDebugDrawWorld(const FMassExecutionContext& Context);` (scope `UE::Mass::Debug`) — Fetches the right world to draw the debug drawing in, depending on the state of mass.debug.ServerPIEDebugDrawMode. Makes sense only in PIE, nop for other cases. Will return nullptr if drawing shouldn't be attempted, for example when mass.debug.ServerPIEDebugDrawMode = 1 and the call is on client.
- L142 _function_ `inline EMessageSeverity::Type MassSeverityToMessageSeverity(EMessageSeverity::Type OriginalSeverity, EMassDebugMessageSeverity MassSeverity)` (scope `UE::Mass::Debug`)
- L191 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnBreakpointsChanged);`
- L192 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnEntitySelected, const FMassEntityManager&, const FMassEntityHandle);`
- L193 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnMassEntityManagerEvent, const FMassEntityManager&);`
- L194 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnEnvironmentEvent, const FEnvironment&);`
- L195 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnDebugEvent, const FName , FConstStructView , const EMassDebugMessageSeverity );`
- L487 _namespace_ `namespace UE`
- L487 _namespace_ `namespace Mass` (scope `UE`)
- L487 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L492 _macro_ `#define MASS_IF_ENTITY_DEBUGGED(a, b) false`
- L493 _macro_ `#define MASS_BREAK_IF_ENTITY_DEBUGGED(a, b)`
- L494 _macro_ `#define MASS_BREAK_IF_ENTITY_INDEX(a, b)`
- L495 _macro_ `#define MASS_SET_ENTITY_DEBUGGED(a, b)`

### `Source/Runtime/MassEntity/Public/MassDebuggerBreakpoints.h` (Public)


#### struct `UE::Mass::Debug::FBreakpointHandle`  
`struct FBreakpointHandle`  
_L28-64_
- L30 _public member_ `int32 Handle = 0;`
- L32 _public function_ `FBreakpointHandle(int32 InHandle) : Handle(InHandle)`
- L37 _public prototype_ `FBreakpointHandle() = default;`
- L44 _public function_ `bool IsValid() const`
- L49 _public function_ `operator bool() const`
- L54 _public function_ `static FBreakpointHandle CreateHandle()`
- L60 _public function_ `static FBreakpointHandle Invalid()`

#### struct `UE::Mass::Debug::FBreakpoint`  
`struct FBreakpoint`  
_L66-372_
- L70 _public prototype_ `FBreakpoint();`
- L85 _public prototype_ `static FString TriggerTypeToString(FBreakpoint::ETriggerType InType);`
- L86 _public prototype_ `static bool StringToTriggerType(const FString& InString, FBreakpoint::ETriggerType& OutType);`
- L96 _public prototype_ `static FString FilterTypeToString(FBreakpoint::EFilterType InType);`
- L97 _public prototype_ `static bool StringToFilterType(const FString& InString, FBreakpoint::EFilterType& OutType);`
- L99 _public typedef_ `using TriggerVariant = TVariant< TObjectKey<const UMassProcessor>, TObjectKey<const UScriptStruct> >;`
- L104 _public typedef_ `using FilterVariant = TVariant< FMassEntityHandle, FMassFragmentRequirements >;`
- L109 _public member_ `FBreakpointHandle Handle;`
- L110 _public member_ `mutable uint64 HitCount = 0;`
- L111 _public member_ `ETriggerType TriggerType = ETriggerType::None;`
- L112 _public member_ `EFilterType FilterType = EFilterType::None;`
- L113 _public member_ `TriggerVariant Trigger;`
- L114 _public member_ `FilterVariant Filter;`
- L115 _public member_ `bool bEnabled = false;`
- L124 _public prototype_ `bool ApplyEntityFilterByFragments(const TArray<const UScriptStruct*>& Fragments) const;` — Apply the breakpoint Filter based on a list of fragment types @param Fragments	Array of fragment types to evaluate the breakpoint filter against @return True if the filter is set to an applicable type it evaluates to true for the provided Fragments
- L133 _public prototype_ `bool ApplyEntityFilterByArchetype(const FMassArchetypeHandle& ArchetypeHandle) const;` — Apply the breakpoint Filter based on an FMassArchetypeHandle @param ArchetypeHandle	The archetype to evaluate breakpoint filter against @return True if the filter is set to an applicable type it evaluates to true for the provided ArchetypeHandle
- L143 _public prototype_ `bool ApplyEntityFilter(const FMassEntityManager& EntityManager, const FMassEntityHandle& Entity) const;` — Evaluate the breakpoint filter against a specific entity @param EntityManager	The FMassEntityManager that owns the entity @param Entity	The handle of the entity against which to evaluate the filter @return True if the filter is set to an applicable type it evaluates to true for the provided Entity
- L153 _public prototype_ `static bool CheckFragmentAddBreakpoints(const FMassEntityHandle& Handle, const UScriptStruct* FragmentType);` — Checks if a fragment add on a given entity should trigger a breakpoint @param FMassEntityHandle	The entity being modified @param FragmentType	The type of fragment being added @return True if any breakpoints are set and enabled that match this event
- L164 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpoints(const FMassEntityHandle& Handle, TFragments... InFragments)` — Checks if a fragment add on a given entity should trigger a breakpoint (templated version) @param Handle	The entity being modified @param InFragments	variadic list of fragment types being added @return True if any breakpoints are set and enabled that match this event
- L181 _public prototype_ `static bool CheckFragmentAddBreakpoints(TConstArrayView<FMassEntityHandle> Entities, const UScriptStruct* FragmentType);` — Checks if a fragment add on a group of entities should trigger a breakpoint @param Entities	The list of entities being modified @param FragmentType	The type of fragment being added @return True if any breakpoints are set and enabled that match this event
- L192 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpoints(TConstArrayView<FMassEntityHandle> Entities, TFragments... InFragments)` — Checks if a fragment add on a group of entities should trigger a breakpoint (templated version) @param Entities	The list of entities being modified @param InFragments	variadic list of fragment types being added @return True if any breakpoints are set and enabled that match this event
- L211 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpointsByInstances(const FMassEntityHandle& Handle, TFragments... InFragments)` — Checks if a fragment add on a group of entities should trigger a breakpoint (fragment instance version) @param Handle	The entity being modified @param InFragments	variadic list of fragment instance references being added @return True if any breakpoints are set and enabled that match this event
- L229 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpointsByInstances(TConstArrayView<FMassEntityHandle> Entities, TFragments... InFragments)` — Checks if a fragment add on a group of entities should trigger a breakpoint (fragment instance version) @param Entities	The list of entities being modified @param InFragments	variadic list of fragment instance references being added @return True if any breakpoints are set and enabled that match this event
- L247 _public prototype_ `static bool CheckFragmentRemoveBreakpoints(const FMassEntityHandle& Handle, const UScriptStruct* FragmentType);` — Checks if a fragment remove on a given entity should trigger a breakpoint @param FMassEntityHandle	The entity being modified @param FragmentType	The type of fragment being removed @return True if any breakpoints are set and enabled that match this event
- L258 _public function_ `template<typename... TFragments> static bool CheckFragmentRemoveBreakpoints(const FMassEntityHandle& Handle, TFragments... InFragments)` — Checks if a fragment remove on a given entity should trigger a breakpoint (templated version) @param Handle	The entity being modified @param InFragments	variadic list of fragment types being removed @return True if any breakpoints are set and enabled that match this event
- L275 _public prototype_ `static bool CheckFragmentRemoveBreakpoints(TConstArrayView<FMassEntityHandle> Entities, const UScriptStruct* FragmentType);` — Checks if a fragment remove on a group of entities should trigger a breakpoint @param Entities	The list of entities being modified @param FragmentType	The type of fragment being removed @return True if any breakpoints are set and enabled that match this event
- L286 _public function_ `template<typename... TFragments> static bool CheckFragmentRemoveBreakpoints(TConstArrayView<FMassEntityHandle> Entities, TFragments... InFragments)` — Checks if a fragment remove on a group of entities should trigger a breakpoint (templated version) @param Entities	The list of entities being modified @param InFragments	variadic list of fragment types being removed @return True if any breakpoints are set and enabled that match this event
- L302 _public prototype_ `static bool CheckCreateEntityBreakpoints(TArray<const UScriptStruct*> Fragments);` — Checks if an entity creation event should trigger a breakpoint @param Fragments	array of fragment types that compose the entity being created @return True if any breakpoints are set and enabled that match this event
- L312 _public function_ `template<typename... TFragments> static bool CheckCreateEntityBreakpoints(TFragments... InFragments)` — Checks if an entity creation event should trigger a breakpoint (templated version) @param InFragments	variadic list of fragment types that compose the entity being created @return True if any breakpoints are set and enabled that match this event
- L329 _public prototype_ `static bool CheckCreateEntityBreakpoints(const FMassArchetypeHandle& ArchetypeHandle);` — Checks if an entity creation event should trigger a breakpoint (archetype version) @param ArchetypeHandle	The archetype of the entity being created @return True if any breakpoints are set and enabled that match this event
- L338 _public prototype_ `static bool CheckDestroyEntityBreakpoints(const FMassEntityHandle& Entity);` — Checks if an entity destruction event should trigger a breakpoint @param Entity	The entity being destroyed @return True if any breakpoints are set and enabled that match this event
- L347 _public prototype_ `static bool CheckDestroyEntityBreakpoints(TConstArrayView<FMassEntityHandle> Entities);` — Checks if an entity destruction event should trigger a breakpoint @param Entities	The array entities being destroyed @return True if any breakpoints are set and enabled that match this event
- L352 _public prototype_ `static void DisableActiveBreakpoint();` — Disable the currently-active breakpoint (if any)
- L359 _public function_ `static inline bool HasBreakpoint()` — Checks if any breakpoints are currently set @return True if there are any breakpoints set in the mass debugger even if they're disabled (so the hit count can still increment).
- L367 _public prototype_ `static void DebugBreak();` — Triggers a breakpoint in the attached debugger (if present)
- L370 _private member_ `static bool bHasBreakpoint;`
- L371 _private member_ `static FBreakpointHandle LastBreakpointHandle;`

#### enum `UE::Mass::Debug::FBreakpoint::ETriggerType`  
`enum class ETriggerType : uint8`  
_L72-84_
- L74 _public enumerator_ `None`
- L75 _public enumerator_ `ProcessorExecute`
- L76 _public enumerator_ `FragmentWrite`
- L77 _public enumerator_ `EntityCreate`
- L78 _public enumerator_ `EntityDestroy`
- L79 _public enumerator_ `FragmentAdd`
- L80 _public enumerator_ `FragmentRemove`
- L81 _public enumerator_ `TagAdd`
- L82 _public enumerator_ `TagRemove`
- L83 _public enumerator_ `MAX`

#### enum `UE::Mass::Debug::FBreakpoint::EFilterType`  
`enum class EFilterType : uint8`  
_L88-94_
- L90 _public enumerator_ `None`
- L91 _public enumerator_ `SpecificEntity`
- L92 _public enumerator_ `SelectedEntity`
- L93 _public enumerator_ `Query`

#### struct `UE::Mass::Debug::FBreakpointHandle`  
`struct FBreakpointHandle`  
_L379-381_
- L30 _public member_ `int32 Handle = 0;`
- L32 _public function_ `FBreakpointHandle(int32 InHandle) : Handle(InHandle)`
- L37 _public prototype_ `FBreakpointHandle() = default;`
- L44 _public function_ `bool IsValid() const`
- L49 _public function_ `operator bool() const`
- L54 _public function_ `static FBreakpointHandle CreateHandle()`
- L60 _public function_ `static FBreakpointHandle Invalid()`

#### struct `UE::Mass::Debug::FBreakpoint`  
`struct FBreakpoint`  
_L383-391_
- L70 _public prototype_ `FBreakpoint();`
- L85 _public prototype_ `static FString TriggerTypeToString(FBreakpoint::ETriggerType InType);`
- L86 _public prototype_ `static bool StringToTriggerType(const FString& InString, FBreakpoint::ETriggerType& OutType);`
- L96 _public prototype_ `static FString FilterTypeToString(FBreakpoint::EFilterType InType);`
- L97 _public prototype_ `static bool StringToFilterType(const FString& InString, FBreakpoint::EFilterType& OutType);`
- L99 _public typedef_ `using TriggerVariant = TVariant< TObjectKey<const UMassProcessor>, TObjectKey<const UScriptStruct> >;`
- L104 _public typedef_ `using FilterVariant = TVariant< FMassEntityHandle, FMassFragmentRequirements >;`
- L109 _public member_ `FBreakpointHandle Handle;`
- L110 _public member_ `mutable uint64 HitCount = 0;`
- L111 _public member_ `ETriggerType TriggerType = ETriggerType::None;`
- L112 _public member_ `EFilterType FilterType = EFilterType::None;`
- L113 _public member_ `TriggerVariant Trigger;`
- L114 _public member_ `FilterVariant Filter;`
- L115 _public member_ `bool bEnabled = false;`
- L124 _public prototype_ `bool ApplyEntityFilterByFragments(const TArray<const UScriptStruct*>& Fragments) const;` — Apply the breakpoint Filter based on a list of fragment types @param Fragments	Array of fragment types to evaluate the breakpoint filter against @return True if the filter is set to an applicable type it evaluates to true for the provided Fragments
- L133 _public prototype_ `bool ApplyEntityFilterByArchetype(const FMassArchetypeHandle& ArchetypeHandle) const;` — Apply the breakpoint Filter based on an FMassArchetypeHandle @param ArchetypeHandle	The archetype to evaluate breakpoint filter against @return True if the filter is set to an applicable type it evaluates to true for the provided ArchetypeHandle
- L143 _public prototype_ `bool ApplyEntityFilter(const FMassEntityManager& EntityManager, const FMassEntityHandle& Entity) const;` — Evaluate the breakpoint filter against a specific entity @param EntityManager	The FMassEntityManager that owns the entity @param Entity	The handle of the entity against which to evaluate the filter @return True if the filter is set to an applicable type it evaluates to true for the provided Entity
- L153 _public prototype_ `static bool CheckFragmentAddBreakpoints(const FMassEntityHandle& Handle, const UScriptStruct* FragmentType);` — Checks if a fragment add on a given entity should trigger a breakpoint @param FMassEntityHandle	The entity being modified @param FragmentType	The type of fragment being added @return True if any breakpoints are set and enabled that match this event
- L164 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpoints(const FMassEntityHandle& Handle, TFragments... InFragments)` — Checks if a fragment add on a given entity should trigger a breakpoint (templated version) @param Handle	The entity being modified @param InFragments	variadic list of fragment types being added @return True if any breakpoints are set and enabled that match this event
- L181 _public prototype_ `static bool CheckFragmentAddBreakpoints(TConstArrayView<FMassEntityHandle> Entities, const UScriptStruct* FragmentType);` — Checks if a fragment add on a group of entities should trigger a breakpoint @param Entities	The list of entities being modified @param FragmentType	The type of fragment being added @return True if any breakpoints are set and enabled that match this event
- L192 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpoints(TConstArrayView<FMassEntityHandle> Entities, TFragments... InFragments)` — Checks if a fragment add on a group of entities should trigger a breakpoint (templated version) @param Entities	The list of entities being modified @param InFragments	variadic list of fragment types being added @return True if any breakpoints are set and enabled that match this event
- L211 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpointsByInstances(const FMassEntityHandle& Handle, TFragments... InFragments)` — Checks if a fragment add on a group of entities should trigger a breakpoint (fragment instance version) @param Handle	The entity being modified @param InFragments	variadic list of fragment instance references being added @return True if any breakpoints are set and enabled that match this event
- L229 _public function_ `template<typename... TFragments> static bool CheckFragmentAddBreakpointsByInstances(TConstArrayView<FMassEntityHandle> Entities, TFragments... InFragments)` — Checks if a fragment add on a group of entities should trigger a breakpoint (fragment instance version) @param Entities	The list of entities being modified @param InFragments	variadic list of fragment instance references being added @return True if any breakpoints are set and enabled that match this event
- L247 _public prototype_ `static bool CheckFragmentRemoveBreakpoints(const FMassEntityHandle& Handle, const UScriptStruct* FragmentType);` — Checks if a fragment remove on a given entity should trigger a breakpoint @param FMassEntityHandle	The entity being modified @param FragmentType	The type of fragment being removed @return True if any breakpoints are set and enabled that match this event
- L258 _public function_ `template<typename... TFragments> static bool CheckFragmentRemoveBreakpoints(const FMassEntityHandle& Handle, TFragments... InFragments)` — Checks if a fragment remove on a given entity should trigger a breakpoint (templated version) @param Handle	The entity being modified @param InFragments	variadic list of fragment types being removed @return True if any breakpoints are set and enabled that match this event
- L275 _public prototype_ `static bool CheckFragmentRemoveBreakpoints(TConstArrayView<FMassEntityHandle> Entities, const UScriptStruct* FragmentType);` — Checks if a fragment remove on a group of entities should trigger a breakpoint @param Entities	The list of entities being modified @param FragmentType	The type of fragment being removed @return True if any breakpoints are set and enabled that match this event
- L286 _public function_ `template<typename... TFragments> static bool CheckFragmentRemoveBreakpoints(TConstArrayView<FMassEntityHandle> Entities, TFragments... InFragments)` — Checks if a fragment remove on a group of entities should trigger a breakpoint (templated version) @param Entities	The list of entities being modified @param InFragments	variadic list of fragment types being removed @return True if any breakpoints are set and enabled that match this event
- L302 _public prototype_ `static bool CheckCreateEntityBreakpoints(TArray<const UScriptStruct*> Fragments);` — Checks if an entity creation event should trigger a breakpoint @param Fragments	array of fragment types that compose the entity being created @return True if any breakpoints are set and enabled that match this event
- L312 _public function_ `template<typename... TFragments> static bool CheckCreateEntityBreakpoints(TFragments... InFragments)` — Checks if an entity creation event should trigger a breakpoint (templated version) @param InFragments	variadic list of fragment types that compose the entity being created @return True if any breakpoints are set and enabled that match this event
- L329 _public prototype_ `static bool CheckCreateEntityBreakpoints(const FMassArchetypeHandle& ArchetypeHandle);` — Checks if an entity creation event should trigger a breakpoint (archetype version) @param ArchetypeHandle	The archetype of the entity being created @return True if any breakpoints are set and enabled that match this event
- L338 _public prototype_ `static bool CheckDestroyEntityBreakpoints(const FMassEntityHandle& Entity);` — Checks if an entity destruction event should trigger a breakpoint @param Entity	The entity being destroyed @return True if any breakpoints are set and enabled that match this event
- L347 _public prototype_ `static bool CheckDestroyEntityBreakpoints(TConstArrayView<FMassEntityHandle> Entities);` — Checks if an entity destruction event should trigger a breakpoint @param Entities	The array entities being destroyed @return True if any breakpoints are set and enabled that match this event
- L352 _public prototype_ `static void DisableActiveBreakpoint();` — Disable the currently-active breakpoint (if any)
- L359 _public function_ `static inline bool HasBreakpoint()` — Checks if any breakpoints are currently set @return True if there are any breakpoints set in the mass debugger even if they're disabled (so the hit count can still increment).
- L367 _public prototype_ `static void DebugBreak();` — Triggers a breakpoint in the attached debugger (if present)
- L370 _private member_ `static bool bHasBreakpoint;`
- L371 _private member_ `static FBreakpointHandle LastBreakpointHandle;`

#### enum `UE::Mass::Debug::FBreakpoint::ETriggerType`  
`enum class ETriggerType : uint8`  
_L385-387_
- L74 _public enumerator_ `None`
- L75 _public enumerator_ `ProcessorExecute`
- L76 _public enumerator_ `FragmentWrite`
- L77 _public enumerator_ `EntityCreate`
- L78 _public enumerator_ `EntityDestroy`
- L79 _public enumerator_ `FragmentAdd`
- L80 _public enumerator_ `FragmentRemove`
- L81 _public enumerator_ `TagAdd`
- L82 _public enumerator_ `TagRemove`
- L83 _public enumerator_ `MAX`

#### enum `UE::Mass::Debug::FBreakpoint::EFilterType`  
`enum class EFilterType : uint8`  
_L388-390_
- L90 _public enumerator_ `None`
- L91 _public enumerator_ `SpecificEntity`
- L92 _public enumerator_ `SelectedEntity`
- L93 _public enumerator_ `Query`

#### Free symbols / members of external scopes

- L9 _macro_ `#define MASS_BREAKPOINT(bShouldBreak) \`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Mass` (scope `UE`)
- L26 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L39 _function_ `friend bool operator==(const FBreakpointHandle& A, const FBreakpointHandle& B)` (scope `UE::Mass::Debug`)
- L377 _namespace_ `namespace UE`
- L377 _namespace_ `namespace Mass` (scope `UE`)
- L377 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L394 _macro_ `#define MASS_BREAKPOINT(...) \`

### `Source/Runtime/MassEntity/Public/MassElement.h` (Public)


#### enum `UE::Mass::EElementType`  
`enum class EElementType : uint8`  
_L18-26_
- L20 _public enumerator_ `Fragment`
- L21 _public enumerator_ `Tag`
- L22 _public enumerator_ `ChunkFragment`
- L23 _public enumerator_ `SharedFragment`
- L24 _public enumerator_ `ConstSharedFragment`
- L25 _public enumerator_ `MAX`

#### struct `UE::Mass::TElementTraits`  
`template<typename TElementType> struct TElementTraits`  
_L29-30_

#### struct `UE::Mass::TBitSetTraits`  
`template<typename TBitSetType> struct TBitSetTraits`  
_L33-34_

#### struct `UE::Mass::FElementBitSet`  
`struct FElementBitSet : public FElementBitSetBase`  
_L36-131_
- inherits: `FElementBitSetBase`
- L43 _public function_ `FElementBitSet(const FElementBitSetBase& OtherBitSet) : FElementBitSetBase(OtherBitSet)`
- L49 _public prototype_ `template<typename TBitSet> TBitSet Get() const;`
- L52 _public prototype_ `template<typename TElementType> bool HasAny() const;`
- L55 _public prototype_ `template<typename TElementType> bool HasAll() const;`
- L58 _public prototype_ `bool HasAnySharedElements() const;` — @todo this is a temporary construct, until shared fragments get removed as a concept
- L60 _public prototype_ `bool ContainsOnlyTagsAndFragments() const;`
- L61 _public prototype_ `FElementBitSet GetFragmentsAndTags() const;`
- L62 _public prototype_ `FElementBitSet GetSparseElements() const;`
- L63 _public prototype_ `FElementBitSet GetSharedFragments() const;`
- L65 _public function_ `static EElementType DetermineElementType(const TNotNull<const UStruct*> ElementType)`
- L92 _public prototype_ `static void OnTypeRegistered(const TNotNull<const UStruct*> Type, int32 Index);`
- L94 _public prototype_ `static void OnModuleInitialized();`
- L96 _public function_ `static void OnModuleShutdown()`
- L101 _public function_ `static const FElementBitSet& GetAllFragmentsAndTags()`
- L106 _public function_ `static const FElementBitSet& GetAllSharedFragments()`
- L111 _public function_ `static const FElementBitSet& GetAllSparseElements()`
- L117 _protected member_ `static TStaticArray<FElementBitSetBase, static_cast<uint8>(EElementType::MAX)> ElementTypeBitArrays;`
- L118 _protected member_ `static FElementBitSet AllSharedFragmentsBitSet;`
- L119 _protected member_ `static FElementBitSet AllFragmentsAndTagsBitSet;`
- L120 _protected member_ `static FElementBitSet AllSparseElementsBitSet;`
- L121 _protected member_ `static FDelegateHandle OnTypeRegisteredDelegateHandle;`
- L127 _public function_ `static FElementBitSetBase& GetTypeBitArray(const EElementType ElementType)` — Fetches FElementBitSetBase containing all known specific element types
- L134 _function_ `template<typename TBitSet> inline TBitSet FElementBitSet::Get() const`
- L140 _function_ `template<typename TElementType> bool FElementBitSet::HasAny() const`
- L146 _function_ `template<typename TElementType> bool FElementBitSet::HasAll() const`
- L151 _function_ `inline bool FElementBitSet::HasAnySharedElements() const`
- L156 _function_ `inline bool FElementBitSet::ContainsOnlyTagsAndFragments() const`
- L161 _function_ `inline FElementBitSet FElementBitSet::GetFragmentsAndTags() const`
- L166 _function_ `inline FElementBitSet FElementBitSet::GetSparseElements() const`
- L171 _function_ `inline FElementBitSet FElementBitSet::GetSharedFragments() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSENTITY_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mass` (scope `UE`)
- L180 _function_ `inline bool DoesContainOnlySharedFragments(const FElementBitSet& BitSet)` (scope `UE::Mass`) — @return whether BitSet indicates only shared fragment types (both const and mutable)
- L186 _function_ `inline bool DoContainEquivalentSharedFragments(const FElementBitSet& BitSetA, const FElementBitSet& BitSetB)` (scope `UE::Mass`) — @return whether shared fragment type information stored by both bitsets is equivalent
- L192 _macro_ `#define DECLARE_NEWTYPEBITSET(ContainerTypeName, BaseType, ElementTypeEnumValue) struct ContainerTypeName : public FElementBitSetBase \`
- L218 _prototype_ `DECLARE_NEWTYPEBITSET(FFragmentBitSet, FMassFragment, EElementType::Fragment);` (scope `UE::Mass`)
- L219 _prototype_ `DECLARE_NEWTYPEBITSET(FTagBitSet, FMassTag, EElementType::Tag);` (scope `UE::Mass`)
- L220 _prototype_ `DECLARE_NEWTYPEBITSET(FChunkFragmentBitSet, FMassChunkFragment, EElementType::ChunkFragment);` (scope `UE::Mass`)
- L221 _prototype_ `DECLARE_NEWTYPEBITSET(FSharedFragmentBitSet, FMassSharedFragment, EElementType::SharedFragment);` (scope `UE::Mass`)
- L222 _prototype_ `DECLARE_NEWTYPEBITSET(FConstSharedFragmentBitSet, FMassConstSharedFragment, EElementType::ConstSharedFragment);` (scope `UE::Mass`)
- L227 _typedef_ `using FMassElementBitSet = UE::Mass::FElementBitSet;`
- L228 _typedef_ `using FMassFragmentBitSet = UE::Mass::FFragmentBitSet;`
- L229 _typedef_ `using FMassTagBitSet = UE::Mass::FTagBitSet;`
- L230 _typedef_ `using FMassChunkFragmentBitSet = UE::Mass::FChunkFragmentBitSet;`
- L231 _typedef_ `using FMassSharedFragmentBitSet = UE::Mass::FSharedFragmentBitSet;`
- L232 _typedef_ `using FMassConstSharedFragmentBitSet = UE::Mass::FConstSharedFragmentBitSet;`

### `Source/Runtime/MassEntity/Public/MassEntityBuilder.h` (Public)


#### struct `UE::Mass::FEntityBuilder`  
`struct FEntityBuilder`  
_L60-337_
- desc: FEntityBuilder is a utility struct that provides a convenient way to create and configure entities in the Mass framework. It bridges multiple APIs from FMassEntityManager, MassSpawnerSubsystem, MassEntityTemplates, and other related components, allowing for streamlined entity creation and configuration. Key Features: - Can be seamlessly used in place of FMassEntityHandle, allowing for consistent and intuitive usage. - An entity only gets created once Commit() is called - Copyable, but copied instances represent new entities without carrying over the reserved entity handle. Example Usage: { FEntityBuilder Builder(EntityManager); Builder.Add<FTransformFragment>(FTransform(FVector(100, 200, 300))) .Commit();	// the entity gets reserved and built by this call } { FEntityBuilder Builder(EntityManager); FMassEntityHandle ReservedEntity = Builder; // Entity handle reserved, can be used for commands. Builder.Add_GetRef<FTransformFragment>().GetMutableTransform().SetTranslation(FVector(100, 200, 300)); Builder.Commit(); // Entity creation is finalized at this point. } // Example of chaining with FMassEntityManager's MakeEntityBuilder() method: FMassEntityHandle NewEntity = EntityManager.MakeEntityBuilder() .Add<FMassStaticRepresentationTag>() .Add<FTransformFragment>() .Add<FAgentRadiusFragment>(FAgentRadiusFragment{ .Radius = 35.f}) .Add<FMassVelocityFragment>() .Commit(); Current Limitations: - Committing entities while Mass's processing is in progress is not yet supported; this fun
- L63 _public prototype_ `explicit FEntityBuilder(FMassEntityManager& InEntityManager);` — Constructs a FEntityBuilder using a reference to a FMassEntityManager.
- L66 _public prototype_ `explicit FEntityBuilder(const TSharedRef<FMassEntityManager>& InEntityManager);` — Constructs a FEntityBuilder using a shared reference to a FMassEntityManager.
- L69 _public prototype_ `FEntityBuilder(const FEntityBuilder& Other);` — Copy constructor - copies-create a new instance that represents a new entity and does not carry over reserved handle.
- L72 _public prototype_ `FEntityBuilder& operator=(const FEntityBuilder& Other);` — Assignment operator - copies represent new entities, with no carryover of reserved handle from the original.
- L75 _public prototype_ `FEntityBuilder& operator=(FEntityBuilder&& Other);` — Move assignment operator - moves over all the data from Other, including the internal state (like whether the entity handle has already been reserved)
- L78 _public prototype_ `~FEntityBuilder();` — Destructor - automatically commits entity creation if not explicitly aborted or committed beforehand.
- L81 _public prototype_ `static FEntityBuilder Make(const TSharedRef<FMassEntityManager>& InEntityManager , const FMassArchetypeCompositionDescriptor& Composition , TConstArrayView<FInstancedStruct> InitialFragmentValues = {} , TConstArrayView<FConstSharedStruct> ConstSharedFragments = {} , TConstArrayView<FSharedStruct> SharedFragments = {});` — Creates an instance of FEntityBuilder and populates it with provided data
- L88 _public prototype_ `static FEntityBuilder Make(const TSharedRef<FMassEntityManager>& InEntityManager , const FMassArchetypeCompositionDescriptor& Composition , TArray<FInstancedStruct>&& InitialFragmentValues , TArray<FConstSharedStruct>&& ConstSharedFragments , TArray<FSharedStruct>&& SharedFragments);` — Creates an instance of FEntityBuilder and populates it with provided data, using move-semantics on said data
- L98 _public prototype_ `FEntityBuilder& SetForceDeferredCommit(bool bNewValue);` — Configured given EntityBuilder instance's commit behavior. Using `true` will result in all Commit calls resulting in issuing Mass commands, regardless of EntityManager.IsProcessing() value.
- L104 _public prototype_ `FMassEntityHandle Commit();` — Finalizes the creation of the entity with the specified fragments and configurations. Note that this function needs to be called manually, no automated entity creation will take place upon builder's destruction.
- L111 _public prototype_ `FMassEntityHandle CommitAndReprepare();` — A wrapper for "Commit" call that, once that's done, prepares the builder for another commit, forgetting the handle for the entity just created, and reverting the state back to "ReadyToCommit" @see Commit
- L114 _public prototype_ `void Reprepare();` — if the builder is in "Committed" state it will roll back to ReadyToSubmit and reset the stored entity handle
- L120 _public prototype_ `void Reset(const bool bReleaseEntityHandleIfReserved = true);` — Resets the builder to its initial state, discarding all previous entity configurations. @param bReleaseEntityHandleIfReserved configures what to do with the reserved entity handle, if it's valid.
- L128 _public prototype_ `bool SetReservedEntityHandle(const FMassEntityHandle ReservedEntityHandle);` — Stores ReservedEntityHandle as the cached EntityHandle. The ReservedEntityHandle is expected to be valid and represent a reserved entity. These expectations will be checked via ensures. If the existing EntityHandle also represents a valid, reserved entity, that handle will be released. @return whether the ReservedEntityHandle has been stored.
- L135 _public prototype_ `bool AppendDataFromEntity(const FMassEntityHandle SourceEntityHandle, EIncludeSparseElements IncludeSparseElements = EIncludeSparseElements::Yes);` — Appends all element types and values stored by the entity indicated by SourceEntityHandle. @param SourceEntityHandle valid handle for a fully constructed, built entity. @return whether the operation was successful
- L142 _public prototype_ `bool CopyDataFromEntity(const FMassEntityHandle SourceEntityHandle, EIncludeSparseElements IncludeSparseElements = EIncludeSparseElements::Yes);` — Copies all element types and values stored by the entity indicated by SourceEntityHandle. Any existing builder data will be overridden @param SourceEntityHandle valid handle for a fully constructed, built entity. @return whether the operation was successful
- L152 _public prototype_ `template<typename T, typename... TArgs> T& Add_GetRef(TArgs&&... InArgs) requires (CElement<T> && !(CTag<T> || CChunkFragment<T>));` — Adds a fragment of type T to the entity and returns a reference to it, constructing it with the provided arguments. The function will assert if an element of type T already exists. @param T - The type of fragment to add. @param InArgs - Constructor arguments for initializing the fragment. @return A reference to the added fragment.
- L160 _public prototype_ `template<typename T, typename... TArgs> T& GetOrCreate(TArgs&&... InArgs) requires (CElement<T> && !(CTag<T> || CChunkFragment<T>));` — Adds a fragment of type T to the entity and returns a reference to it, constructing it with the provided arguments. If a fragment of the given type already exists then it will be overriden and its reference returned. @return A reference to the added fragment.
- L167 _public prototype_ `template<CTag T> FEntityBuilder& Add();` — Adds a tag of type T to the entity. @return Reference to this FEntityBuilder for method chaining.
- L174 _public prototype_ `template<CChunkFragment T> FEntityBuilder& Add();` — Adds a chunk fragment of type T to the entity. @return Reference to this FEntityBuilder for method chaining.
- L181 _public prototype_ `template<typename T, typename... TArgs> FEntityBuilder& Add(TArgs&&... InArgs) requires (CElement<T> && !(CTag<T> || CChunkFragment<T>));` — Adds a fragment of type T to the entity, constructing it with the provided arguments. @return Reference to this FEntityBuilder for method chaining.
- L186 _public prototype_ `FEntityBuilder& Add(const FInstancedStruct& ElementInstance);` — Adds a fragment instance to the Entity Builder, treating the contents according to its type
- L187 _public prototype_ `FEntityBuilder& Add(FInstancedStruct&& ElementInstance);`
- L190 _public prototype_ `FEntityBuilder& Add(TNotNull<const UScriptStruct*> ElementType);` — Adds the ElementType to the target archetype's composition
- L205 _public prototype_ `FEntityBuilder& AddRelation(UE::Mass::FTypeHandle RelationTypeHandle, FMassEntityHandle OtherEntity, Relations::ERelationRole InputEntityRole = Relations::ERelationRole::Object);` — Adds information about a specific relation instance to be added once the entity gets created. The function will simply store the information without any checks for validity or duplication. If you want to override existing relation data call ForEachRelation.
- L209 _public prototype_ `template<UE::Mass::CRelation T> FEntityBuilder& AddRelation(FMassEntityHandle OtherEntity, Relations::ERelationRole InputEntityRole = Relations::ERelationRole::Object);` — templated helper function for calling the other AddRelation function
- L217 _public prototype_ `void ForEachRelation(const TFunctionRef<bool(FPendingRelationParams&)>& Operator);` — Calls the provided Operator function for every stored pending relation data instance. The return value of the Operator is used to determine whether the relation data instance should be kept (meaning: return `false` for each element you want to remove). The potential element removal is stable.
- L225 _public prototype_ `template<typename T> T* Find() requires (CElement<T> && !(CTag<T> || CChunkFragment<T>));` — Finds and retrieves a pointer to a fragment of type T if it exists. @param T - The type of fragment to find. @return Pointer to the fragment, or nullptr if it does not exist.
- L232 _public prototype_ `void ConfigureArchetypeCreation(const FMassArchetypeCreationParams& InCreationParams);` — Advanced functionality. Can be used to provide additional parameters that will be used to create the entity's target archetype. Note that these parameters will take effect only if the target archetype doesn't exist yet.
- L235 _public prototype_ `[[nodiscard]] FMassEntityHandle GetEntityHandle() const;` — Converts the builder to a FMassEntityHandle, reserving the entity handle if not already committed.
- L237 _public prototype_ `[[nodiscard]] FMassArchetypeHandle GetArchetypeHandle();`
- L240 _public prototype_ `bool IsValid() const;` — Checks whether the builder is in a valid, expected state
- L243 _public prototype_ `bool HasReservedEntityHandle() const;` — @return whether the builder has an entity handle reserved and the data has not been committed yet
- L246 _public prototype_ `bool IsCommitted() const;` — @return whether the builder has already committed the data
- L249 _public prototype_ `TSharedRef<FMassEntityManager> GetEntityManager();` — @return the EntityManager instance this entity builder is working for
- L252 _public prototype_ `static bool GetDefaultValueOfForceDeferredCommit();` — Retrieves the default value used to initialize EntityBuilder.bForceDeferred
- L257 _protected prototype_ `void CacheSharedFragmentValue();`
- L258 _protected prototype_ `void CacheArchetypeHandle();`
- L259 _protected prototype_ `void InvalidateCachedData();`
- L273 _private prototype_ `template<typename TInstancedStruct> FEntityBuilder& AddInternal(TInstancedStruct&& ElementInstance);`
- L276 _private prototype_ `template<typename T> bool HandleTypeInstance(const UScriptStruct* Type, TArray<FInstancedStruct>*& OutTargetContainer, bool& bOutAlreadyInComposition);`
- L278 _private member_ `TSharedRef<FMassEntityManager> EntityManager;`
- L279 _private member_ `mutable FMassEntityHandle EntityHandle;`
- L281 _private member_ `FMassArchetypeCompositionDescriptor Composition;`
- L283 _private member_ `FMassArchetypeSharedFragmentValues CachedSharedFragmentValues;`
- L284 _private member_ `FMassArchetypeHandle CachedArchetypeHandle;`
- L287 _private member_ `FMassArchetypeCreationParams ArchetypeCreationParams;` — stores optional FMassArchetypeCreationParams, that will be used if the target archetype doesn't exist yet
- L290 _private function_ `template<CFragment T> TArray<FInstancedStruct>& GetInstancedStructContainerInternal()`
- L296 _private function_ `template<CSharedFragment T> TArray<FInstancedStruct>& GetInstancedStructContainerInternal()`
- L306 _private function_ `template<CConstSharedFragment T> TArray<FInstancedStruct>& GetInstancedStructContainerInternal()`
- L313 _private prototype_ `void ConditionallyReleaseEntityHandle();` — Releases reserved handle if it has not been committed yet
- L315 _private prototype_ `void CacheEntityHandle() const;`
- L317 _private prototype_ `static void CreateEntityImpl(FMassEntityManager& EntityManager, FMassEntityHandle EntityHandle, const FMassArchetypeHandle& ArchetypeHandle , const FMassArchetypeSharedFragmentValues& SharedFragmentValues, TConstArrayView<FInstancedStruct> Fragments, TConstArrayView<FPendingRelationParams> RelationsParams , const FMassElementBitSet& CompositionBitSet);`
- L321 _private member_ `TArray<FInstancedStruct> Fragments;`
- L322 _private member_ `TArray<FInstancedStruct> SharedFragments;`
- L323 _private member_ `TArray<FInstancedStruct> ConstSharedFragments;`
- L324 _private member_ `TArray<FPendingRelationParams> RelationsParams;`
- L333 _private member_ `EState State = EState::Empty;`
- L336 _private member_ `uint8 bForceDeferred : 1 = false;` — if set will make entity creation always performed with Mass commands
- L359 _function_ `template<CTag T> FEntityBuilder& FEntityBuilder::Add()`
- L368 _function_ `template<CChunkFragment T> FEntityBuilder& FEntityBuilder::Add()`
- L377 _function_ `template<typename T, typename... TArgs> FEntityBuilder& FEntityBuilder::Add(TArgs&&... InArgs) requires (CElement<T> && !(CTag<T> || CChunkFragment<T>))`
- L384 _function_ `template<typename T, typename... TArgs> T& FEntityBuilder::Add_GetRef(TArgs&&... InArgs) requires (CElement<T> && !(CTag<T> || CChunkFragment<T>))`
- L401 _function_ `template<typename T, typename... TArgs> T& FEntityBuilder::GetOrCreate(TArgs&&... InArgs) requires (CElement<T> && !(CTag<T> || CChunkFragment<T>))`
- L426 _function_ `template<typename T> T* FEntityBuilder::Find() requires (CElement<T> && !(CTag<T> || CChunkFragment<T>))`
- L440 _function_ `template<UE::Mass::CRelation T> FEntityBuilder& FEntityBuilder::AddRelation(const FMassEntityHandle OtherEntity, const Relations::ERelationRole InputEntityRole)`
- L445 _function_ `inline bool FEntityBuilder::IsValid() const`
- L450 _function_ `inline bool FEntityBuilder::HasReservedEntityHandle() const`
- L455 _function_ `inline bool FEntityBuilder::IsCommitted() const`
- L460 _function_ `inline TSharedRef<FMassEntityManager> FEntityBuilder::GetEntityManager()`
- L465 _function_ `inline void FEntityBuilder::ConfigureArchetypeCreation(const FMassArchetypeCreationParams& InCreationParams)`
- L470 _function_ `inline FEntityBuilder& FEntityBuilder::SetForceDeferredCommit(const bool bNewValue)`

#### struct `UE::Mass::FEntityBuilder::FPendingRelationParams`  
`struct FPendingRelationParams`  
_L193-198_
- desc: type used to store parameters for relations to be created once the target entity is created.
- L195 _public member_ `UE::Mass::FTypeHandle RelationTypeHandle;`
- L196 _public member_ `FMassEntityHandle OtherEntity;`
- L197 _public member_ `Relations::ERelationRole OtherEntityRole;`

#### struct `UE::Mass::FEntityBuilder::FStructInstanceFindingPredicate`  
`struct FStructInstanceFindingPredicate`  
_L261-269_
- L264 _public function_ `template<typename TInstancedStruct> bool operator()(const TInstancedStruct& Instance) const`
- L268 _public member_ `const UScriptStruct* SearchedType = nullptr;`

#### enum `UE::Mass::FEntityBuilder::EState`  
`enum class EState : uint8`  
_L326-332_
- L328 _public enumerator_ `Empty`
- L329 _public enumerator_ `ReadyToCommit`
- L330 _public enumerator_ `Committed`
- L331 _public enumerator_ `Invalid`

#### struct `UE::Mass::FScopedEntityBuilder`  
`struct FScopedEntityBuilder : FEntityBuilder`  
_L339-353_
- inherits: `FEntityBuilder`
- L344 _public function_ `template<typename... TArgs> FScopedEntityBuilder(TArgs&&... InArgs) : FEntityBuilder(Forward<TArgs>(InArgs)...)`
- L349 _public function_ `~FScopedEntityBuilder()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSENTITY_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mass` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassEntityCollection.h` (Public)


#### struct `UE::Mass::FEntityCollection`  
`struct FEntityCollection`  
_L25-201_
- desc: Type represents a collection of arbitrary EntityHandles. Under the hood the type stores also an array of FMassArchetypeEntityCollection instances. These cached collections can be tested for being up to date, and re-created on demand, based on stored entity handles. The type is intended to be used to collect entities available through different means: individual handles, handle arrays and or FMassArchetypeEntityCollection instances. Such accumulated handles can at any moment be turned into an array of up-to-date FMassArchetypeEntityCollection instance, which in turn is how entity sets are provided to MassEntityManager's batched API. The biggest win while using this type is that the user doesn't have to worry about FMassArchetypeEntityCollection instances going out of date (which happens whenever the target archetype is touched in a way that changes internal entity indices). The type automatically updates the collections and caches the result.
- L27 _public prototype_ `FEntityCollection() = default;`
- L33 _public prototype_ `explicit FEntityCollection(FMassArchetypeEntityCollection&& InEntityCollection);` — The following constructor are equivalent to using the default constructor and subsequently calling AppendCollection or AppendHandles.
- L34 _public prototype_ `explicit FEntityCollection(const FMassArchetypeEntityCollection& InEntityCollection);`
- L35 _public prototype_ `explicit FEntityCollection(const TConstArrayView<FMassEntityHandle> InEntityHandles);`
- L36 _public prototype_ `FEntityCollection(const TConstArrayView<FMassEntityHandle> InEntityHandles, FMassArchetypeEntityCollection&& InEntityCollection);`
- L44 _public prototype_ `void AppendHandles(TConstArrayView<FMassEntityHandle> Handles);` — Appends Handles to stored EntityHandles. Results in marking cached FMassArchetypeEntityCollection as dirty.
- L53 _public prototype_ `void AppendHandles(TConstArrayView<FMassEntityHandle> Handles, FMassArchetypeEntityCollection&& InEntityCollection);` — Appends Handles to stored EntityHandles. The second parameter is relevant if, at the moment of calling, the cached FMassArchetypeEntityCollection instances are in sync with stored entity handles (meaning all entities stored in EntityHandles are also captured by one of FMassArchetypeEntityCollection). If that's the case then the InEntityCollection gets stored along with existing collections. Otherwise, InEntityCollection will be ignored.
- L58 _public prototype_ `void AppendHandles(TArray<FMassEntityHandle>&& Handles);` — Appends Handles to stored EntityHandles. Results in marking cached FMassArchetypeEntityCollection as dirty.
- L63 _public prototype_ `void AddHandle(FMassEntityHandle Handle);` — Appends the Handle to stored EntityHandles. Results in marking cached FMassArchetypeEntityCollection as dirty.
- L71 _public function_ `template<typename T> requires std::is_same_v<typename TDecay<T>::Type, FMassArchetypeEntityCollection> void AppendCollection(T&& InEntityCollection)` — Based on the provided FMassArchetypeEntityCollection creates an array of entity handles and stores them. If up to this point the cached FMassArchetypeEntityCollection-s are consistent with stored EntityHandles then InEntityCollection gets stored as well, and stored collections are not marked as dirty.
- L96 _public prototype_ `bool UpdateAndRemoveDuplicates(const FMassEntityManager& EntityManager, bool bForceOperation = false);` — Results in duplicate handles being removed from EntityHandles, the cached collections being up-to-date and CollectionCreationDuplicatesHandling being set to FMassArchetypeEntityCollection::NoDuplicates @param bForceOperation by default the entity handles will be re-exported only if CollectionCreationDuplicatesHandling == FMassArchetypeEntityCollection::FoldDuplicates (which means we cannot rule out that there are duplicates). Using bForceOperation = true will perform the operation regardless. @return whether any duplicates were detected
- L101 _public function_ `void MarkDirty()`
- L106 _public function_ `bool IsEmpty() const`
- L117 _public prototype_ `bool IsUpToDate() const;` — Checks if cached collection data is up to date If CachedCollections are not up-to-date we reset them to cache the information (and make the subsequent tests cheaper) Note that, depending on the contents, the test might be non-trivial. Use responsibly.
- L122 _public function_ `TConstArrayView<FMassEntityHandle> GetEntityHandlesView() const`
- L131 _public function_ `TConstArrayView<FMassArchetypeEntityCollection> GetCachedPerArchetypeCollections() const` — Retrieves the view to current contents of CachedCollections, which may be out of date. If you need valid, up-to-date collections call GetUpToDatePerArchetypeCollections instead.
- L140 _public function_ `TConstArrayView<FMassArchetypeEntityCollection> GetUpToDatePerArchetypeCollections(const FMassEntityManager& EntityManager) const` — Fetches up-to-date FMassArchetypeEntityCollection instances matching stored entity handles.
- L149 _public function_ `TArray<FMassArchetypeEntityCollection> ConsumeArchetypeCollections(const FMassEntityManager& EntityManager) &&` — Updates cached archetype collections and returns the container with move semantics
- L157 _private function_ `template<typename T> requires std::is_same_v<typename TDecay<T>::Type, FMassArchetypeEntityCollection> void ConditionallyStoreCollection(const bool bWasEmpty, T&& InEntityCollection)`
- L181 _private prototype_ `void ConditionallyUpdate(const FMassEntityManager& EntityManager) const;`
- L187 _private member_ `TArray<FMassEntityHandle> EntityHandles;` — these are the entities represented by given instance of FEntityCollection. EntityHandles are the authority, source of truth regarding the contents
- L195 _private member_ `mutable TArray<FMassArchetypeEntityCollection> CachedCollections;` — Cached per-archetype collections of entities. Can go our of date due to operations performed on this FEntityCollection instance (in this case we reset cached CachedCollections) or due to the stored entities being moved between archetypes.
- L200 _private member_ `FMassArchetypeEntityCollection::EDuplicatesHandling CollectionCreationDuplicatesHandling = FMassArchetypeEntityCollection::NoDuplicates;` — Stores information whether we can expect duplicates in EntityHandles when building CachedCollections

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassEntityConcepts.h` (Public)


#### struct `UE::Mass::Private::TElementTypeHelper`  
`template<CElement T> struct TElementTypeHelper`  
_L49-57_
- L51 _public typedef_ `using Type = std::conditional_t<CFragment<T>, FMassFragment , std::conditional_t<CTag<T>, FMassTag , std::conditional_t<CChunkFragment<T>, FMassChunkFragment , std::conditional_t<CSharedFragment<T>, FMassSharedFragment , std::conditional_t<CConstSharedFragment<T>, FMassConstSharedFragment , void>>>>>;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mass` (scope `UE`)
- L13 _typedef_ `template<typename T> using Clean = typename TRemoveReference<T>::Type;` (scope `UE::Mass`)
- L46 _namespace_ `namespace Private` (scope `UE::Mass`)
- L61 _typedef_ `template<typename T> using TElementType = typename Private::TElementTypeHelper<T>::Type;` (scope `UE::Mass`)
- L64 _function_ `template<typename T> bool IsSparse()` (scope `UE::Mass`)
- L74 _macro_ `#define MASS_STATIC_CHECK_FRAGMENT(T) \` — Provides two targeted static_assert checks instead of the single combined CFragment concept check. The first failing assert gives the user a clear, specific error message rather than the full concept failure wall. Place this macro where static_assert(UE::Mass::CFragment<T>, ...) was used.

### `Source/Runtime/MassEntity/Public/MassEntityElementTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MassEntity/Public/MassEntityFragments.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MassEntity/Public/MassEntityHandle.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MassEntity/Public/MassEntityLinkFragments.h` (Public)


#### struct `FMassEntityLinkFragment`  
`struct FMassEntityLinkFragment : public FMassConstSharedFragment`  
_L15-21_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Add this to an entity to link it to another entity. Groups entities that access the same LinkedEntityHandle indirectly for better cache behavior. Use this to minimize random access when many entities access the same shared data.
- L18 _public member_ `FMassEntityHandle LinkedEntityHandle;` — `UPROPERTY()`

### `Source/Runtime/MassEntity/Public/MassEntityMacros.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MassEntity/Public/MassEntityManager.h` (Public)


#### struct `FMassEntityManager`  
`struct FMassEntityManager : public TSharedFromThis<FMassEntityManager>, public FGCObject`  
_L97-1659_
- inherits: `TSharedFromThis<FMassEntityManager>,FGCObject`
- desc: The type responsible for hosting Entities managing Archetypes. Entities are stored as FEntityData entries in a chunked array. Each valid entity is assigned to an Archetype that stored fragments associated with a given entity at the moment. FMassEntityManager supplies API for entity creation (that can result in archetype creation) and entity manipulation. Even though synchronized manipulation methods are available in most cases the entity operations are performed via a command buffer. The default command buffer can be obtained with a Defer() call. @see FMassCommandBuffer for more details. FMassEntityManager are meant to be stored with a TSharedPtr or TSharedRef. Some of Mass API pass around FMassEntityManager& but programmers can always use AsShared() call to obtain a shared ref for a given manager instance (as supplied by deriving from TSharedFromThis<FMassEntityManager>). IMPORTANT: if you create your own FMassEntityManager instance remember to call Initialize() before using it.
- L103 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewArchetypeDelegate, const FMassArchetypeHandle&);`
- L107 _private member_ `constexpr static int32 NumReservedEntities = 1;` — Index 0 is reserved so we can treat that index as an invalid entity handle
- L134 _public typedef_ `using FStructInitializationCallback = TFunctionRef<void(void* Fragment, const UScriptStruct& FragmentType)>;`
- L136 _public member_ `const static FMassEntityHandle InvalidEntity;`
- L138 _public prototype_ `explicit FMassEntityManager(UObject* InOwner = nullptr);`
- L139 _public prototype_ `FMassEntityManager(const FMassEntityManager& Other) = delete;`
- L140 _public prototype_ `virtual ~FMassEntityManager();`
- L143 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L144 _public function_ `virtual FString GetReferencerName() const override`
- L149 _public prototype_ `void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize);`
- L153 _public prototype_ `void Initialize();` — `UE_DEPRECATED(5.8, "Single threaded entity storage is being removed. Use Initialize(FMassEntityManagerStorageInitParams) with FMassEntityManager_InitParams_Concurrent instead.")` — Default to use single threaded implementation
- L154 _public prototype_ `void Initialize(const FMassEntityManagerStorageInitParams& InitializationParams);`
- L155 _public prototype_ `void PostInitialize();`
- L156 _public prototype_ `void Deinitialize();`
- L162 _public prototype_ `FMassArchetypeHandle CreateArchetype(TConstArrayView<const UScriptStruct*> FragmentsAndTagsList, const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());` — A special, relaxed but slower version of CreateArchetype functions that allows FragmentAngTagsList to contain both fragments and tags.
- L172 _public prototype_ `FMassArchetypeHandle CreateArchetype(FMassArchetypeHandle SourceArchetype, TConstArrayView<const UScriptStruct*> FragmentsAndTagsList);` — A special, relaxed but slower version of CreateArchetype functions that allows FragmentAngTagsList to contain both fragments and tags. This version takes an original archetype and copies it layout, then appends any fragments and tags from the provided list if they're not already in the original archetype. @param SourceArchetype The archetype where the composition will be copied from. @param FragmentsAndTagsList The list of fragments and tags to add to the copied composition.
- L183 _public prototype_ `FMassArchetypeHandle CreateArchetype(FMassArchetypeHandle SourceArchetype, TConstArrayView<const UScriptStruct*> FragmentsAndTagsList, const FMassArchetypeCreationParams& CreationParams);` — A special, relaxed but slower version of CreateArchetype functions that allows FragmentAngTagsList to contain both fragments and tags. This version takes an original archetype and copies it layout, then appends any fragments and tags from the provided list if they're not already in the original archetype. @param SourceArchetype The archetype where the composition will be copied from. @param FragmentsAndTagsList The list of fragments and tags to add to the copied composition. @param CreationParams Additional arguments used to create the new archetype.
- L193 _public prototype_ `FMassArchetypeHandle CreateArchetype(const FMassArchetypeCompositionDescriptor& Composition, const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());` — CreateArchetype from a composition descriptor and initial values @param Composition of fragment, tag and chunk fragment types @param CreationParams Parameters used during archetype construction @return a handle of a new archetype
- L202 _public prototype_ `FMassArchetypeHandle CreateArchetype(const FMassElementBitSet& ElementBitSet, const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());` — CreateArchetype from a mass element bitset and initial values @param ElementBitSet Bitset of fragment, tag and chunk fragment types @param CreationParams Parameters used during archetype construction @return a handle of a new archetype
- L214 _public prototype_ `FMassArchetypeHandle CreateArchetype(const TSharedPtr<FMassArchetypeData>& SourceArchetype, const FMassFragmentBitSet& InFragments);` — Creates an archetype like SourceArchetype + InFragments. @param SourceArchetype the archetype used to initially populate the list of fragments of the archetype being created. @param InFragments list of unique fragments to add to fragments fetched from SourceArchetype. Note that adding an empty list is not supported and doing so will result in failing a `check` @return a handle of a new archetype @note it's caller's responsibility to ensure that NewFragmentList is not empty and contains only fragment types that SourceArchetype doesn't already have. If the caller cannot guarantee it use of AddFragment functions family is recommended.
- L227 _public prototype_ `FMassArchetypeHandle CreateArchetype(const TSharedPtr<FMassArchetypeData>& SourceArchetype, const FMassFragmentBitSet& InFragments, const FMassArchetypeCreationParams& CreationParams);` — Creates an archetype like SourceArchetype + InFragments. @param SourceArchetype the archetype used to initially populate the list of fragments of the archetype being created. @param InFragments list of unique fragments to add to fragments fetched from SourceArchetype. Note that adding an empty list is not supported and doing so will result in failing a `check` @param CreationParams Parameters used during archetype construction @return a handle of a new archetype @note it's caller's responsibility to ensure that NewFragmentList is not empty and contains only fragment types that SourceArchetype doesn't already have. If the caller cannot guarantee it use of AddFragment functions family is recommended.
- L237 _public prototype_ `FMassArchetypeHandle GetOrCreateSuitableArchetype(const FMassArchetypeHandle& ArchetypeHandle , const FMassSharedFragmentBitSet& SharedFragmentBitSet , const FMassConstSharedFragmentBitSet& ConstSharedFragmentBitSet , const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());` — A helper function to be used when creating entities with shared fragments provided, or when adding shared fragments to existing entities @param ArchetypeHandle that's the assumed target archetype. But we'll be making sure its composition matches SharedFragmentsBitSet @param SharedFragmentBitSet indicates which shared fragments we want the target archetype to have. If ArchetypeHandle doesn't have these a new archetype will be created.
- L242 _public prototype_ `FMassArchetypeHandle GetOrCreateSuitableArchetype(const FMassArchetypeHandle& ArchetypeHandle , const FMassElementBitSet& SharedElementsBitSet , const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());`
- L247 _public prototype_ `FMassArchetypeHandle GetArchetypeForEntity(FMassEntityHandle EntityHandle) const;` — Fetches the archetype for a given EntityHandle. If EntityHandle is not valid it will still return a handle, just with an invalid archetype
- L252 _public prototype_ `FMassArchetypeHandle GetArchetypeForEntityUnsafe(FMassEntityHandle EntityHandle) const;` — Fetches the archetype for a given EntityHandle. Note that it's callers responsibility the given EntityHandle handle is valid. If you can't ensure that call GetArchetypeForEntity.
- L259 _public prototype_ `void GetMatchingArchetypes(const FMassFragmentRequirements& Requirements, TArray<FMassArchetypeHandle>& OutValidArchetypes) const;` — Searches through all known archetypes and matches them to the provided requirements. All archetypes that pass the requirement check are returned. @param Requirements The set of fragments and tags that need to be on available in the request form on an archetype before it's added. @param OutValidArchetypes Archetypes that pass the requirements test are added here.
- L265 _public prototype_ `static void ForEachArchetypeElementType(const FMassArchetypeHandle& ArchetypeHandle, TFunctionRef< bool(const UScriptStruct* )> Function);` — Method to iterate on all the element (fragments, tags, etc.) types of an archetype. Note that sparse elements are not archetype characteristics and therefore not included in this call.
- L268 _public prototype_ `static void ForEachArchetypeFragmentType(const FMassArchetypeHandle& ArchetypeHandle, TFunction< void(const UScriptStruct* )> Function);` — Method to iterate on all the fragment types of an archetype
- L271 _public prototype_ `static void ForEachArchetypeChunkEntityList(const FMassArchetypeHandle& ArchetypeHandle, TFunctionRef<void(TConstArrayView<FMassEntityHandle> )> Function);` — List all entities in an archetype per chunk.
- L277 _public prototype_ `void DoEntityCompaction(const double TimeAllowed);` — Go through all archetypes and compact entities @param TimeAllowed to do entity compaction, once it reach that time it will stop and return
- L284 _public prototype_ `FMassEntityHandle CreateEntity(const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {});` — Creates fully built entity ready to be used by the subsystem @param ArchetypeHandle you want this entity to be @param SharedFragmentValues to be associated with the entity @return FMassEntityHandle id of the newly created entity
- L291 _public prototype_ `FMassEntityHandle CreateEntity(TConstArrayView<FInstancedStruct> FragmentInstanceList, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {}, const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());` — Creates fully built entity ready to be used by the subsystem @param FragmentInstanceList is the fragments to create the entity from and initialize values @param SharedFragmentValues to be associated with the entity @return FMassEntityHandle id of the newly created entity
- L293 _public typedef_ `using FEntityCreationContext = UE::Mass::ObserverManager::FCreationContext;`
- L310 _public prototype_ `TSharedRef<FEntityCreationContext> GetOrMakeCreationContext();` — The main use-case for this function is to create a blank FEntityCreationContext and hold on to it while creating a bunch of entities (with multiple calls to BatchCreate* and/or BatchBuild*) and modifying them (with mutating batched API) while not causing multiple Observers to trigger. All the observers will be triggered at one go, once the FEntityCreationContext instance gets destroyed. !Important note: the "Creation Context" is a specialized wrapper for an "Observers Lock" (@see GetOrMakeObserversLock). As long as the creation context is alive all the operations will be assumed to affect the newly created entities. The consequence of that is operations performed on already existing entities won't be tracked, as long as the creation context is alive. Note that you can hold a FMassObserverManager::FObserverLock instance while the creation lock gets destroyed, the observers lock is a lower-level concept than the creation context. @return the existing (if valid) or a newly created creation context
- L323 _public prototype_ `TSharedRef<UE::Mass::ObserverManager::FObserverLock> GetOrMakeObserversLock();` — Fetches the observers lock (as hosted by FMassObserverManager). If one is not currently active, one will be created. While the lock is active all the observers notifications are suspended, and will be sent out when FMassObserverManager::FObserverLock instance gets destroyed. Locking observers needs to be used when entities are being configured with multiple operations, and we want observers to be triggered only once all the operations are executed. Note that while the observers are locked we're unable to send "Remove" notifications, so once the lock is released and the observers get notified, the data being removed won't be available anymore (which is a difference in behavior as compared to removal notifications while the observers are not locked).
- L331 _public prototype_ `TSharedRef<FEntityCreationContext> BatchCreateReservedEntities(const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues, TConstArrayView<FMassEntityHandle> ReservedEntities);` — A version of CreateEntity that's creating a number of entities (Count) in one go @param ArchetypeHandle you want this entity to be @param SharedFragmentValues to be associated with the entities @param ReservedEntities a list of reserved entities that have not yet been assigned to an archetype. @return a creation context that will notify all the interested observers about newly created fragments once the context is released
- L333 _public function_ `inline TSharedRef<FEntityCreationContext> BatchCreateReservedEntities(const FMassArchetypeHandle& ArchetypeHandle, TConstArrayView<FMassEntityHandle> OutEntities)`
- L345 _public prototype_ `TSharedRef<FEntityCreationContext> BatchCreateEntities(const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues, const int32 Count, TArray<FMassEntityHandle>& InOutEntities);` — A version of CreateEntity that's creating a number of entities (Count) in one go @param ArchetypeHandle you want this entity to be @param SharedFragmentValues to be associated with the entities @param Count number of entities to create @param InOutEntities the newly created entities are appended to given array, i.e. the pre-existing content of OutEntities won't be affected by the call @return a creation context that will notify all the interested observers about newly created fragments once the context is released
- L346 _public function_ `inline TSharedRef<FEntityCreationContext> BatchCreateEntities(const FMassArchetypeHandle& ArchetypeHandle, const int32 Count, TArray<FMassEntityHandle>& InOutEntities)`
- L354 _public prototype_ `void DestroyEntity(FMassEntityHandle EntityHandle);` — Destroys a fully built entity, use ReleaseReservedEntity if entity was not yet built. @param EntityHandle identifying the entity to destroy
- L359 _public prototype_ `FMassEntityHandle ReserveEntity();` — Reserves an entity in the subsystem, the entity is still not ready to be used by the subsystem, need to call BuildEntity() @return FMassEntityHandle id of the reserved entity
- L367 _public prototype_ `void BuildEntity(FMassEntityHandle EntityHandle, const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {});` — Builds an entity for it to be ready to be used by the subsystem @param EntityHandle identifying the entity to build, which was retrieved with ReserveEntity() method @param ArchetypeHandle you want this entity to be @param SharedFragmentValues to be associated with the entity
- L375 _public prototype_ `void BuildEntity(FMassEntityHandle EntityHandle, TConstArrayView<FInstancedStruct> FragmentInstanceList, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {});` — Builds an entity for it to be ready to be used by the subsystem @param EntityHandle identifying the entity to build, which was retrieved with ReserveEntity() method @param FragmentInstanceList is the fragments to create the entity from and initialize values @param SharedFragmentValues to be associated with the entity
- L380 _public prototype_ `void ReleaseReservedEntity(FMassEntityHandle EntityHandle);` — Releases a previously reserved entity handle that was not yet built, otherwise call DestroyEntity @param EntityHandle to release
- L388 _public prototype_ `void BatchDestroyEntities(TConstArrayView<FMassEntityHandle> InEntities);` — Destroys all the entities in the provided array of entities. The function will also gracefully handle entities that have been reserved but not created yet. @note the function doesn't handle duplicates in InEntities. @param InEntities to destroy
- L395 _public prototype_ `void BatchDestroyEntityChunks(const FMassArchetypeEntityCollection& Collection);` — Destroys all the entities provided via the Collection. The function will also gracefully handle entities that have been reserved but not created yet. @param Collection to destroy
- L396 _public prototype_ `void BatchDestroyEntityChunks(TConstArrayView<FMassArchetypeEntityCollection> Collections);`
- L403 _public prototype_ `void BatchGroupEntities(const UE::Mass::FArchetypeGroupHandle GroupHandle, TConstArrayView<FMassArchetypeEntityCollection> Collections);` — Assigns all entities indicated by Collections to a given archetype group. Note that depending on their individual composition each entity can end up in a different archetype. @param GroupHandle indicates the target group. Passing an invalid group handle will get logged as warning and ignored.
- L410 _public prototype_ `void BatchGroupEntities(const UE::Mass::FArchetypeGroupHandle GroupHandle, TConstArrayView<FMassEntityHandle> InEntities);` — Assigns all entities indicated by InEntities to a given archetype group. Note that depending on their individual composition each entity can end up in a different archetype. @param GroupHandle indicates the target group. Passing an invalid group handle will get logged as warning and ignored.
- L416 _public prototype_ `UE::Mass::FArchetypeGroupType FindOrAddArchetypeGroupType(const FName GroupName);` — Fetches FArchetypeGroupType instance (copy) associated with the given GroupName. A new group type is created if GroupName has not been used in the past.
- L418 _public prototype_ `const UE::Mass::FArchetypeGroups& GetGroupsForArchetype(const FMassArchetypeHandle& ArchetypeHandle) const;`
- L420 _public prototype_ `void AddFragmentToEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> FragmentType);`
- L421 _public prototype_ `void AddFragmentToEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> FragmentType, const FStructInitializationCallback& Initializer);`
- L427 _public prototype_ `void AddFragmentListToEntity(FMassEntityHandle EntityHandle, TConstArrayView<const UScriptStruct*> FragmentList);` — Ensures that only unique fragments are added. @note It's caller's responsibility to ensure EntityHandle's and FragmentList's validity.
- L429 _public prototype_ `void AddFragmentInstanceListToEntity(FMassEntityHandle EntityHandle, TConstArrayView<FInstancedStruct> FragmentInstanceList);`
- L430 _public prototype_ `void RemoveFragmentFromEntity(FMassEntityHandle EntityHandle, const UScriptStruct* FragmentType);`
- L431 _public prototype_ `void RemoveFragmentListFromEntity(FMassEntityHandle EntityHandle, TConstArrayView<const UScriptStruct*> FragmentList);`
- L433 _public prototype_ `void AddTagToEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> TagType);`
- L434 _public prototype_ `void RemoveTagFromEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> TagType);`
- L435 _public prototype_ `void SwapTagsForEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> FromFragmentType, TNotNull<const UScriptStruct*> ToFragmentType);`
- L442 _public prototype_ `FStructView AddSparseElementToEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType);` — Adds sparse element indicated by ElementType to the entity indicated by EntityHandle. Works with tags too, but returns an empty struct view For more information on Sparse Elements see FSparseElementsStorage
- L450 _public function_ `template<UE::Mass::CFragment T> requires UE::Mass::CSparse<T> T& AddSparseElementToEntity(FMassEntityHandle EntityHandle)` — Adds a sparse fragment to the entity and returns a reference to the newly created fragments. This function can only fail if EntityHandle doesn't represent a valid, active entity.
- L458 _public function_ `template<UE::Mass::CTag T> requires UE::Mass::CSparse<T> void AddSparseElementToEntity(FMassEntityHandle EntityHandle)`
- L463 _public prototype_ `void RemoveSparseElementFromEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType);`
- L465 _public function_ `template<UE::Mass::CSparse T> void RemoveSparseElementFromEntity(FMassEntityHandle EntityHandle)`
- L474 _public prototype_ `void AddSparseElementsToEntity(FMassEntityHandle EntityHandle, const FMassElementBitSet& ElementsBitset);` — Adds sparse elements indicated by ElementsBitset to the entity indicated by EntityHandle. For more information on Sparse Elements see FSparseElementsStorage
- L480 _public prototype_ `void BatchAddElementToEntities(TConstArrayView<FMassEntityHandle> Entities, TNotNull<const UScriptStruct*> ElementType);` — Adds ElementType to the entities, treating it accordingly based on which element type it represents (i.e. Fragment or Tag). The function will assert on unhandled types.
- L487 _public prototype_ `void AddElementToEntity(FMassEntityHandle Entity, TNotNull<const UScriptStruct*> ElementType);` — Adds ElementType to the entity, treating it accordingly based on which element type it represents (i.e. Fragment or Tag). This function handles sparse elements. The function will assert on unhandled types.
- L493 _public prototype_ `void BatchRemoveElementFromEntities(TConstArrayView<FMassEntityHandle> Entities, TNotNull<const UScriptStruct*> ElementType);` — Removes ElementType from the entities, treating it accordingly based on which element type it represents (i.e. Fragment or Tag). The function will assert on unhandled types.
- L499 _public prototype_ `void RemoveElementFromEntity(FMassEntityHandle Entity, TNotNull<const UScriptStruct*> ElementType);` — Removes ElementType from the entity, treating it accordingly based on which element type it represents (i.e. Fragment or Tag). The function will assert on unhandled types.
- L502 _public prototype_ `bool DoesEntityHaveElement(FMassEntityHandle Entity, TNotNull<const UScriptStruct*> ElementType) const;` — @return whether Entity has an element of ElementType
- L505 _public function_ `template<UE::Mass::CElement T> bool DoesEntityHaveElement(FMassEntityHandle Entity) const`
- L517 _public prototype_ `bool SwapConstSharedFragmentForEntity(const FMassEntityHandle EntityHandle, const FConstSharedStruct& InConstSharedFragment);` — Adds a new const shared fragment to the given entity if it doesn't have a shared fragment of the given type, moves it to its new archetype and notify observers. In case a fragment of that type is already present, then it replaces it, moves the entity to its new chunk within the archetype and notifies the observers. @return whether the Fragment value is valid and successfully assigned to the entity (added or replaced)
- L527 _public prototype_ `bool AddConstSharedFragmentToEntity(const FMassEntityHandle EntityHandle, const FConstSharedStruct& InConstSharedFragment);` — Adds a new const shared fragment to the given entity. Note that it only works if the given entity doesn't have a shared fragment of the given type. The function will give a soft "pass" if the entity has the shared fragment of the same value. Setting shared fragment value (i.e. changing) is not supported and the function will log a warning if that's attempted. @return whether the entity has the Fragment value assigned to it, regardless of its original state (i.e. the function will return true also if the entity already had the same values associated with it)
- L534 _public prototype_ `bool RemoveConstSharedFragmentFromEntity(const FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ConstSharedFragmentType);` — Removes a const shared fragment of the given type from the entity. Will do nothing if entity did not have the shared fragment. @return True if fragment removed from entity, false otherwise.
- L537 _public function_ `template<UE::Mass::CConstSharedFragment T> bool RemoveConstSharedFragmentFromEntity(const FMassEntityHandle EntityHandle)`
- L543 _public function_ `bool RemoveConstSharedFragmentFromEntity(const FMassEntityHandle EntityHandle, const UScriptStruct& ConstSharedFragmentType)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L556 _public prototype_ `bool AddSharedFragmentToEntity(const FMassEntityHandle EntityHandle, const FSharedStruct& InSharedFragment);` — Adds a new shared fragment to the given entity. Note that it only works if the given entity doesn't have a shared fragment of the given type. The function will give a soft "pass" if the entity has the shared fragment of the same value. Setting shared fragment value (i.e. changing) is not supported and the function will log a warning if that's attempted. @return whether the entity has the Fragment value assigned to it, regardless of its original state (i.e. the function will return true also if the entity already had the same values associated with it)
- L563 _public prototype_ `bool RemoveSharedFragmentFromEntity(const FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> SharedFragmentType);` — Removes a shared fragment of the given type from the entity. Will do nothing if entity did not have the shared fragment. @return True if fragment removed from entity, false otherwise.
- L566 _public function_ `bool RemoveSharedFragmentFromEntity(const FMassEntityHandle EntityHandle, const UScriptStruct& SharedFragmentType)` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L575 _public prototype_ `void RemoveEntityFromGroupType(FMassEntityHandle EntityHandle, UE::Mass::FArchetypeGroupType GroupType);` — Removes EntityHandle from any-and-all groups of given type - i.e. the entity will be moved to an archetype not in any of the groups of the given type.
- L580 _public prototype_ `UE::Mass::FArchetypeGroupHandle GetGroupForEntity(FMassEntityHandle EntityHandle, UE::Mass::FArchetypeGroupType GroupType) const;` — @return the group handle of the specific group of type GroupType that the entity belongs to
- L586 _public prototype_ `TConstArrayView<FMassEntityHandle> BatchReserveEntities(const int32 Count, TArray<FMassEntityHandle>& InOutEntities);` — Reserves Count number of entities and appends them to InOutEntities @return a view into InOutEntities containing only the freshly reserved entities
- L593 _public prototype_ `int32 BatchReserveEntities(TArrayView<FMassEntityHandle> InOutEntities);` — Reserves number of entities corresponding to number of entries in the provided array view InOutEntities. As a result InOutEntities gets filled with handles of reserved entities @return the number of entities reserved
- L595 _public prototype_ `TSharedRef<FEntityCreationContext> BatchBuildEntities( const FMassArchetypeEntityCollectionWithPayload& EncodedEntitiesWithPayload , const FMassFragmentBitSet& FragmentsAffected , const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {} , const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());`
- L601 _public prototype_ `TSharedRef<FEntityCreationContext> BatchBuildEntities( const FMassArchetypeEntityCollectionWithPayload& EncodedEntitiesWithPayload , const FMassArchetypeCompositionDescriptor& Composition , const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {} , const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());`
- L607 _public prototype_ `TSharedRef<FEntityCreationContext> BatchBuildEntities( const FMassArchetypeEntityCollectionWithPayload& EncodedEntitiesWithPayload , const FMassElementBitSet& Composition , const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {} , const FMassArchetypeCreationParams& CreationParams = FMassArchetypeCreationParams());`
- L613 _public prototype_ `void BatchChangeCompositionForEntities( TConstArrayView<FMassArchetypeEntityCollection> EntityCollections , const FMassElementBitSet& ElementsToAdd , const FMassElementBitSet& ElementsToRemove);`
- L623 _public prototype_ `void BatchChangeCompositionForEntities( TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, const FMassElementBitSet& ElementsToAdd, const FMassElementBitSet& ElementsToRemove, const FMassArchetypeSharedFragmentValues& SharedFragmentValuesToAdd);` — Overload that also adds shared fragment values during the same entity move. ElementsToAdd must include the shared fragment bits from SharedFragmentValuesToAdd. Sparse element types must not appear in ElementsToAdd; use the dedicated sparse element APIs instead.
- L629 _public function_ `void BatchChangeTagsForEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, const FMassTagBitSet& TagsToAdd, const FMassTagBitSet& TagsToRemove)`
- L634 _public function_ `void BatchChangeFragmentCompositionForEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, const FMassFragmentBitSet& FragmentsToAdd, const FMassFragmentBitSet& FragmentsToRemove)`
- L640 _public prototype_ `void BatchAddFragmentInstancesForEntities(TConstArrayView<FMassArchetypeEntityCollectionWithPayload> EntityCollections, const FMassFragmentBitSet& FragmentsAffected);`
- L646 _public prototype_ `void BatchAddFragmentInstancesForEntities(TConstArrayView<FMassArchetypeEntityCollectionWithPayload> EntityCollections, const FMassFragmentBitSet& FragmentsAffected, const FMassTagBitSet& TagsToAdd);` — Adds fragment types with per-entity values AND tags to entities in a single entity move. Tags are included in the composition change but excluded from value payload (tags have zero-size storage).
- L652 _public prototype_ `void BatchAddFragmentInstancesForEntities(TConstArrayView<FMassArchetypeEntityCollectionWithPayload> EntityCollections, const FMassFragmentBitSet& FragmentsAffected, const FMassTagBitSet& TagsToAdd, const FMassArchetypeSharedFragmentValues& SharedFragmentValuesToAdd);` — Adds fragment types with per-entity values, tags, and shared fragment values — all in a single entity move. Tags are included in composition but excluded from value payload. Shared fragment values are set per-chunk.
- L658 _public prototype_ `void BatchAddFragmentInstancesForEntities(TConstArrayView<FMassArchetypeEntityCollectionWithPayload> EntityCollections, const FMassFragmentBitSet& FragmentsAffected, const FMassArchetypeSharedFragmentValues& SharedFragmentValuesToAdd);` — Adds fragment types, sets their per-entity values, and adds shared fragment values — all in a single entity move. Combines the functionality of BatchAddFragmentInstancesForEntities and BatchAddSharedFragmentsForEntities.
- L663 _public prototype_ `void BatchAddSharedFragmentsForEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, const FMassArchetypeSharedFragmentValues& AddedFragmentValues);` — Adds a new const and non-const shared fragments to all entities provided via EntityCollections
- L665 _public prototype_ `void BatchAddSparseElementToEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TNotNull<const UScriptStruct*> ElementType);`
- L667 _public prototype_ `void BatchRemoveSparseElementFromEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TNotNull<const UScriptStruct*> ElementType);` — @todo add a version with FMassArchetypeEntityCollectionWithPayload to add pre-configured fragment instances
- L675 _public prototype_ `void BatchRemoveSharedFragmentFromEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, const FMassSharedFragmentBitSet& ToRemove);` — Removes the specified shared fragment types from all entities in the provided collections. Entities are moved to new archetypes without the removed shared fragment types. @param EntityCollections the entity collections to process @param ToRemove bitset of shared fragment types to remove
- L683 _public prototype_ `void BatchRemoveConstSharedFragmentFromEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, const FMassConstSharedFragmentBitSet& ToRemove);` — Removes the specified const shared fragment types from all entities in the provided collections. Entities are moved to new archetypes without the removed shared fragment types. @param EntityCollections the entity collections to process @param ToRemove bitset of const shared fragment types to remove
- L692 _public prototype_ `void AddCompositionToEntity_GetDelta(FMassEntityHandle EntityHandle, FMassArchetypeCompositionDescriptor& InOutDescriptor, const FMassArchetypeSharedFragmentValues* AddedSharedFragmentValues = nullptr);` — Adds elements indicated by InOutDescriptor to the entity indicated by EntityHandle. The function also figures out which elements in InOutDescriptor are missing from the current composition of the given entity and then returns the resulting delta via InOutDescriptor. If InOutDescriptor indicates shared fragments to be added the caller is required to provide matching values for the indicated shared fragment types, via AddedSharedFragmentValues.
- L693 _public prototype_ `void RemoveCompositionFromEntity(FMassEntityHandle EntityHandle, const FMassArchetypeCompositionDescriptor& InDescriptor);`
- L695 _public prototype_ `FMassArchetypeCompositionDescriptor GetArchetypeComposition(const FMassArchetypeHandle& ArchetypeHandle) const;`
- L703 _public prototype_ `void MoveEntityToAnotherArchetype(FMassEntityHandle EntityHandle, FMassArchetypeHandle NewArchetypeHandle, const FMassArchetypeSharedFragmentValues* SharedFragmentValuesOverride = nullptr);` — Moves an entity over to a new archetype by copying over fragments common to both archetypes @param EntityHandle indicates the entity to move @param NewArchetypeHandle the handle to the new archetype @param SharedFragmentValuesOverride if provided will override all given entity's shared fragment values
- L710 _public prototype_ `void SetEntityFragmentValues(FMassEntityHandle EntityHandle, TArrayView<const FInstancedStruct> FragmentInstanceList);` — Copies values from FragmentInstanceList over to target entity's fragment. Caller is responsible for ensuring that the given entity does have given fragments. Failing this assumption will cause a check-fail. @param EntityHandle indicates the target entity
- L713 _public prototype_ `template<UE::Mass::CStructType TStruct> void SetEntityFragmentValues(FMassEntityHandle EntityHandle, TConstArrayView<TStruct> FragmentInstanceList);`
- L718 _public prototype_ `void BatchSetEntityFragmentValues(const FMassArchetypeEntityCollection& SparseEntities, TArrayView<const FInstancedStruct> FragmentInstanceList);` — Copies values from FragmentInstanceList over to fragments of given entities collection. The caller is responsible for ensuring that the given entity archetype (FMassArchetypeEntityCollection .Archetype) does have given fragments. Failing this assumption will cause a check-fail.
- L721 _public prototype_ `template<UE::Mass::CStructType TStruct> void BatchSetEntityFragmentValues(const FMassArchetypeEntityCollection& SparseEntities, TConstArrayView<TStruct> FragmentInstanceList);`
- L723 _public prototype_ `void BatchSetEntityFragmentValues(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TArrayView<const FInstancedStruct> FragmentInstanceList);`
- L726 _public prototype_ `template<UE::Mass::CStructType TStruct> void BatchSetEntityFragmentValues(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TConstArrayView<TStruct> FragmentInstanceList);`
- L732 _public prototype_ `bool IsEntityActive(FMassEntityHandle EntityHandle) const;` — @return whether the given handle represents a valid and built entity (i.e., the handle is valid and the entity represent has been constructed already)
- L738 _public prototype_ `bool IsEntityValid(FMassEntityHandle EntityHandle) const;` — @return whether the given entity handle is valid, i.e. it points to a valid spot in the entity storage and the handle's serial number is up to date
- L741 _public prototype_ `bool IsEntityBuilt(FMassEntityHandle EntityHandle) const;` — whether the entity handle represents an entity that has been fully built (expecting a valid EntityHandle)
- L747 _public prototype_ `bool IsEntityReserved(FMassEntityHandle EntityHandle) const;` — @return whether the given EntityHandle is valid and the entity it represents is in `Reserved` state (i.e. it will also fail if the entity has already been `Created`)
- L750 _public function_ `inline void CheckIfEntityIsValid(FMassEntityHandle EntityHandle) const` — Asserts that IsEntityValid
- L757 _public function_ `inline void CheckIfEntityIsActive(FMassEntityHandle EntityHandle) const` — Asserts that IsEntityBuilt
- L765 _public prototype_ `FMassEntityHandle CreateEntityIndexHandle(const int32 EntityIndex) const;` — Generate valid, up-to-date entity handle for the entity at given index.
- L768 _public function_ `template<typename FragmentType> FragmentType& GetFragmentDataChecked(FMassEntityHandle EntityHandle) const`
- L775 _public function_ `template<typename FragmentType> FragmentType* GetFragmentDataPtr(FMassEntityHandle EntityHandle) const`
- L788 _public function_ `FStructView GetFragmentDataStruct(FMassEntityHandle EntityHandle, const UScriptStruct* FragmentType) const` — Returns a FStructView for the given fragment on the specified entity. The view points directly into archetype chunk storage. WARNING: For initializing fragments on newly created entities, prefer the CreateEntity(TConstArrayView<FInstancedStruct>,...) overload which sets initial values atomically. The two-step pattern (CreateEntity + GetFragmentDataStruct + mutate) is only safe when no processors are running (e.g., during BeginPlay or subsystem Initialize). @return an empty FStructView if the entity does not have the fragment.
- L796 _public function_ `template<typename ConstSharedFragmentType> ConstSharedFragmentType* GetConstSharedFragmentDataPtr(FMassEntityHandle EntityHandle) const`
- L804 _public function_ `template<typename ConstSharedFragmentType> ConstSharedFragmentType& GetConstSharedFragmentDataChecked(FMassEntityHandle EntityHandle) const`
- L811 _public function_ `FConstStructView GetConstSharedFragmentDataStruct(FMassEntityHandle EntityHandle, const UScriptStruct* ConstSharedFragmentType) const`
- L822 _public function_ `template<typename SharedFragmentType> TConstArrayView<FSharedStruct> GetSharedFragmentsOfType()`
- L832 _public function_ `template<typename SharedFragmentType> SharedFragmentType* GetSharedFragmentDataPtr(FMassEntityHandle EntityHandle) const`
- L841 _public function_ `template<typename SharedFragmentType> SharedFragmentType& GetSharedFragmentDataChecked(FMassEntityHandle EntityHandle) const`
- L848 _public function_ `FConstStructView GetSharedFragmentDataStruct(FMassEntityHandle EntityHandle, const UScriptStruct* SharedFragmentType) const`
- L859 _public function_ `template<typename T> FConstStructView GetElementDataStruct(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> FragmentType) const`
- L880 _public prototype_ `FStructView GetMutableSparseElementDataForEntity(TNotNull<const UScriptStruct*> ElementType, const FMassEntityHandle EntityHandle);`
- L881 _public prototype_ `FConstStructView GetSparseElementDataForEntity(TNotNull<const UScriptStruct*> ElementType, const FMassEntityHandle EntityHandle) const;`
- L883 _public prototype_ `FMassElementBitSet GetSparseElementsBitSetForEntity(const FMassEntityHandle EntityHandle) const;`
- L885 _public function_ `uint32 GetArchetypeDataVersion() const`
- L893 _public prototype_ `FMassExecutionContext CreateExecutionContext(const float DeltaSeconds);` — Creates and initializes a FMassExecutionContext instance.
- L895 _public function_ `FScopedProcessing NewProcessingScope()`
- L905 _public function_ `bool IsProcessing() const` — Indicates whether there are processors out there performing operations on this instance of MassEntityManager. Used to ensure that mutating operations (like entity destruction) are not performed while processors are running, which rely on the assumption that the data layout doesn't change during calculations.
- L910 _public function_ `FMassCommandBuffer& Defer() const`
- L919 _public prototype_ `void FlushCommands(const TSharedPtr<FMassCommandBuffer>& InCommandBuffer);` — @param InCommandBuffer if not set then the default command buffer will be flushed. If set and there's already a command buffer being flushed (be it the main one or a previously requested one) then this command buffer will be queued itself.
- L921 _public prototype_ `void FlushCommands();`
- L928 _public prototype_ `void AppendCommands(const TSharedPtr<FMassCommandBuffer>& InOutCommandBuffer);` — Depending on the current state of Manager's command buffer the function will either move all the commands out of InOutCommandBuffer into the main command buffer or append it to the list of command buffers waiting to be flushed. @note as a consequence of the call InOutCommandBuffer can get its contents emptied due some of the underlying code using Move semantics
- L932 _private function_ `template<typename T, typename... TArgs> const FSharedStruct& GetOrCreateSharedFragmentByHash(const uint32 Hash, TArgs&&... InArgs)`
- L939 _private function_ `template<typename T> const FConstSharedStruct& GetOrCreateConstSharedFragmentByHash(const uint32 Hash, const T& Fragment)`
- L946 _private function_ `template<typename T> const FSharedStruct& GetOrCreateSharedFragmentByHash(const uint32 Hash, const T& Fragment)`
- L952 _private function_ `const FConstSharedStruct& GetOrCreateConstSharedFragmentByHash(const uint32 Hash, const UScriptStruct* InScriptStruct, const uint8* InStructMemory)`
- L957 _private function_ `const FSharedStruct& GetOrCreateSharedFragmentByHash(const uint32 Hash, const UScriptStruct* InScriptStruct, const uint8* InStructMemory)`
- L963 _private function_ `template<typename T, typename... TArgs> const FConstSharedStruct& GetOrCreateConstSharedFragmentByHash(const uint32 Hash, TArgs&&... InArgs)`
- L977 _private prototype_ `FMassEntityHandle CreateEntityAsyncUnsafe(const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {});` — Creates fully built entity ready to be used by the subsystem Does not check for synchronous execution and should only be used by processors through the execution context This should only ever be used by FMassExecutionContext which will validate data access safety. @param ArchetypeHandle the archetype you want this entity to be @param SharedFragmentValues to be associated with the entity @return FMassEntityHandle id of the newly created entity
- L987 _private prototype_ `void BuildEntityAsyncUnsafe(const FMassArchetypeHandle& ArchetypeHandle, const FMassEntityHandle& ReservedEntityHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {});` — Fully buils an entity with a reserved handle ready to be used by the subsystem Does not check for synchronous execution and should only be used by processors through the execution context This should only ever be used by FMassExecutionContext which will validate data access safety. @param ArchetypeHandle the archetype you want this entity to be @param ReservedEntityHandle the already reserved handle to use for the new enetity @param SharedFragmentValues to be associated with the entity
- L998 _private prototype_ `void BatchCreateEntitiesAsyncUnsafe(const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues, const int32 Count, TArray<FMassEntityHandle>& InOutEntities);` — A version of CreateEntity that's creating a number of entities (Count) in one go Unsafe version only for use in processors via ExecutionContext Note: this does not create or return a FEntityCreationContext because it's assumed that observers are already locked by the processing phase. @param ArchetypeHandle you want this entity to be @param SharedFragmentValues to be associated with the entities @param Count number of entities to create @param InOutEntities the newly created entities are appended to given array, i.e. the pre-existing content of OutEntities won't be affected by the call
- L999 _private function_ `void BatchCreateEntitiesAsyncUnsafe(const FMassArchetypeHandle& ArchetypeHandle, const int32 Count, TArray<FMassEntityHandle>& InOutEntities)`
- L1008 _public function_ `template<typename CallableT> void ForEachArchetype(int32 BeginRange, int32 EndRange, const CallableT& Callable) const`
- L1048 _public function_ `template<typename T> const FConstSharedStruct& GetOrCreateConstSharedFragment(const T& Fragment)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when an instance of the desired const shared fragment type is available and that can be used directly to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) e.g., USTRUCT() struct FIntConstSharedFragment : public FMassConstSharedFragment { GENERATED_BODY() UPROPERTY() int32 Value = 0; }; FIntConstSharedFragment Fragment; Fragment.Value = 123; const FConstSharedStruct SharedStruct = EntityManager.GetOrCreateConstSharedFragment(Fragment); @params Fragment Instance of the desired fragment type @return FConstSharedStruct to the matching, or newly created shared fragment
- L1079 _public function_ `template<typename T> const FSharedStruct& GetOrCreateSharedFragment(const T& Fragment)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when an instance of the desired shared fragment type is available and that can be used directly to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) e.g., USTRUCT() struct FIntSharedFragment : public FMassSharedFragment { GENERATED_BODY() UPROPERTY() int32 Value = 0; }; FIntSharedFragment Fragment; Fragment.Value = 123; const FSharedStruct SharedStruct = EntityManager.GetOrCreateSharedFragment(Fragment); @params Fragment Instance of the desired fragment type @return FSharedStruct to the matching, or newly created shared fragment
- L1110 _public function_ `template<typename T, typename... TArgs> const FConstSharedStruct& GetOrCreateConstSharedFragment(TArgs&&... InArgs)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when values can be provided as constructor arguments for the desired const shared fragment type and that can be used directly to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) e.g., USTRUCT() struct FIntConstSharedFragment : public FMassConstSharedFragment { GENERATED_BODY() FIntConstSharedFragment(const int32 InValue) : Value(InValue) {} UPROPERTY() int32 Value = 0; }; const FConstSharedStruct SharedStruct = EntityManager.GetOrCreateConstSharedFragment<FIntConstSharedFragment>(123); @params InArgs List of arguments provided to the constructor of the desired fragment type @return FConstSharedStruct to the matching, or newly created shared fragment
- L1142 _public function_ `template<typename T, typename... TArgs> const FSharedStruct& GetOrCreateSharedFragment(TArgs&&... InArgs)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when values can be provided as constructor arguments for the desired shared fragment type and that can be used directly to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) e.g., USTRUCT() struct FIntSharedFragment : public FMassSharedFragment { GENERATED_BODY() FIntSharedFragment(const int32 InValue) : Value(InValue) {} UPROPERTY() int32 Value = 0; }; const FSharedStruct SharedStruct = EntityManager.GetOrCreateSharedFragment<FIntSharedFragment>(123); @params InArgs List of arguments provided to the constructor of the desired fragment type @return FSharedStruct to the matching, or newly created shared fragment
- L1163 _public function_ `const FConstSharedStruct& GetOrCreateConstSharedFragment(const UScriptStruct& InScriptStruct, const uint8* InStructMemory)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when the reflection data and the memory of an instance of the desired const shared fragment type is available and that can be used directly to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) e.g., FSharedStruct SharedStruct = EntityManager.GetOrCreateConstSharedFragment(*StructView.GetScriptStruct(), StructView.GetMemory()); @params InScriptStruct Reflection data structure associated to the desired fragment type @params InStructMemory Actual data of the desired fragment type @return FConstSharedStruct to the matching, or newly created shared fragment
- L1183 _public function_ `const FSharedStruct& GetOrCreateSharedFragment(const UScriptStruct& InScriptStruct, const uint8* InStructMemory)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when the reflection data and the memory of an instance of the desired shared fragment type is available and that can be used directly to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) e.g., FSharedStruct SharedStruct = EntityManager.GetOrCreateSharedFragment(*StructView.GetScriptStruct(), StructView.GetMemory()); @params InScriptStruct Reflection data structure associated to the desired fragment type @params InStructMemory Actual data of the desired fragment type @return FSharedStruct to the matching, or newly created shared fragment
- L1227 _public function_ `template<typename T, typename... TArgs> const FConstSharedStruct& GetOrCreateConstSharedFragment(const FConstStructView HashingHelperStruct, TArgs&&... InArgs)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when a different struct should be used to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) and values can be provided as constructor arguments for the desired const shared fragment type e.g., USTRUCT() struct FIntConstSharedFragmentParams { GENERATED_BODY() FIntConstSharedFragmentParams(const int32 InValue) : Value(InValue) {} UPROPERTY() int32 Value = 0; }; USTRUCT() struct FIntConstSharedFragment : public FMassConstSharedFragment { GENERATED_BODY() FIntConstSharedFragment(const FIntConstSharedFragmentParams& InParams) : Value(InParams.Value) {} int32 Value = 0; }; FIntConstSharedFragmentParams Params(123); const FConstSharedStruct SharedStruct = EntityManager.GetOrCreateConstSharedFragment<FIntConstSharedFragment>(FConstStructView::Make(Params), Params); @params HashingHelperStruct Struct view passed to UE::StructUtils::GetStructInstanceCrc32 to compute the CRC @params InArgs List of arguments provided to the constructor of the desired fragment type @return FConstSharedStruct to the matching, or newly created shared fragment
- L1272 _public function_ `template<typename T, typename... TArgs> const FSharedStruct& GetOrCreateSharedFragment(const FConstStructView HashingHelperStruct, TArgs&&... InArgs)` — Returns or creates a shared struct associated to a given shared fragment set of values identified internally by a CRC. Use this overload when a different struct should be used to compute a CRC (i.e., UE::StructUtils::GetStructInstanceCrc32) and values can be provided as constructor arguments for the desired shared fragment type e.g., USTRUCT() struct FIntSharedFragmentParams { GENERATED_BODY() FInSharedFragmentParams(const int32 InValue) : Value(InValue) {} UPROPERTY() int32 Value = 0; }; USTRUCT() struct FIntSharedFragment : public FMassSharedFragment { GENERATED_BODY() FIntSharedFragment(const FIntConstSharedFragmentParams& InParams) : Value(InParams.Value) {} int32 Value = 0; }; FIntSharedFragmentParams Params(123); const FSharedStruct SharedStruct = EntityManager.GetOrCreateSharedFragment<FIntSharedFragment>(FConstStructView::Make(Params), Params); @params HashingHelperStruct Struct view passed to UE::StructUtils::GetStructInstanceCrc32 to compute the CRC @params InArgs List of arguments provided to the constructor of the desired fragment type @return FSharedStruct to the matching, or newly created shared fragment
- L1282 _public prototype_ `template<UE::Mass::CSharedFragment T> void ForEachSharedFragment(TFunctionRef< void(T& ) > ExecuteFunction);`
- L1285 _public prototype_ `template<UE::Mass::CSharedFragment T> void ForEachSharedFragmentConditional(TFunctionRef< bool(T& ) > ConditionFunction, TFunctionRef< void(T& ) > ExecuteFunction);`
- L1288 _public prototype_ `template<UE::Mass::CConstSharedFragment T> void ForEachConstSharedFragment(TFunctionRef< void(const T& ) > ExecuteFunction);`
- L1291 _public prototype_ `template<UE::Mass::CConstSharedFragment T> void ForEachConstSharedFragmentConditional(TFunctionRef< bool(const T& ) > ConditionFunction, TFunctionRef< void(const T& ) > ExecuteFunction);`
- L1297 _public function_ `UE::Mass::FSparseElementIterator CreateSparseElementsIterator(TNotNull<const UScriptStruct*> ElementType)` — Creates UE::Mass::FSparseElementIterator instance that can be used to iterate over all instances of a given sparse element fragment Note: works only for sparse fragments, as tags contain no data.
- L1306 _public function_ `template<UE::Mass::CSparse T> requires UE::Mass::CFragment<T> UE::Mass::FSparseElementIterator CreateSparseElementsIterator()`
- L1314 _public prototype_ `UE::Mass::FRelationManager& GetRelationManager();`
- L1317 _public prototype_ `template<UE::Mass::CRelation T> bool BatchCreateRelations(TArrayView<FMassEntityHandle> Subjects, TArrayView<FMassEntityHandle> Objects);`
- L1318 _public prototype_ `bool BatchCreateRelations(const UE::Mass::FTypeHandle RelationTypeHandle, TArrayView<FMassEntityHandle> Subjects, TArrayView<FMassEntityHandle> Objects);`
- L1323 _public prototype_ `void OnNewTypeRegistered(UE::Mass::FTypeHandle RegisteredTypeHandle);`
- L1326 _protected prototype_ `void OnRelationTypeRegistered(UE::Mass::FTypeHandle RegisteredTypeHandle, const UE::Mass::FRelationTypeTraits& RelationTypeTraits);`
- L1332 _public prototype_ `[[nodiscard]] UE::Mass::FEntityBuilder MakeEntityBuilder();`
- L1337 _public prototype_ `const UE::Mass::FTypeManager& GetTypeManager() const;`
- L1338 _public prototype_ `UE::Mass::FTypeManager& GetTypeManager();`
- L1340 _public function_ `FMassObserverManager& GetObserverManager()`
- L1345 _public function_ `FOnNewArchetypeDelegate& GetOnNewArchetypeEvent()`
- L1353 _public function_ `UWorld* GetWorld() const` — Fetches the world associated with the Owner. @note that it's ok for a given EntityManager to not have an owner or the owner not being part of a UWorld, depending on the use case
- L1357 _public function_ `UObject* GetOwner() const`
- L1362 _public prototype_ `bool IsDuringEntityCreation() const;`
- L1364 _public prototype_ `void SetDebugName(const FString& NewDebugGame);`
- L1366 _public prototype_ `void DebugPrintArchetypes(FOutputDevice& Ar, const bool bIncludeEmpty = true) const;`
- L1367 _public prototype_ `void DebugGetArchetypesStringDetails(FOutputDevice& Ar, const bool bIncludeEmpty = true) const;`
- L1368 _public prototype_ `void DebugGetArchetypeFragmentTypes(const FMassArchetypeHandle& Archetype, TArray<const UScriptStruct*>& InOutFragmentList) const;`
- L1369 _public prototype_ `int32 DebugGetArchetypeEntitiesCount(const FMassArchetypeHandle& Archetype) const;`
- L1370 _public prototype_ `int32 DebugGetArchetypeEntitiesCountPerChunk(const FMassArchetypeHandle& Archetype) const;`
- L1371 _public prototype_ `int32 DebugGetEntityCount() const;`
- L1372 _public prototype_ `int32 DebugGetArchetypesCount() const;`
- L1373 _public prototype_ `void DebugRemoveAllEntities();`
- L1374 _public prototype_ `void DebugForceArchetypeDataVersionBump();`
- L1375 _public prototype_ `void DebugGetArchetypeStrings(const FMassArchetypeHandle& Archetype, TArray<FName>& OutFragmentNames, TArray<FName>& OutTagNames);`
- L1377 _public prototype_ `FMassEntityHandle DebugGetEntityIndexHandle(const int32 EntityIndex) const;` — `UE_DEPRECATED(5.7, "Using CreateEntityIndexHandle instead.")`
- L1378 _public prototype_ `const FString& DebugGetName() const;`
- L1387 _public prototype_ `void DebugEnableDebugFeature(EDebugFeatures Features);`
- L1388 _public prototype_ `void DebugDisableDebugFeature(EDebugFeatures Features);`
- L1389 _public prototype_ `bool DebugHasAllDebugFeatures(EDebugFeatures Features) const;`
- L1391 _public prototype_ `FMassRequirementAccessDetector& GetRequirementAccessDetector();`
- L1394 _public prototype_ `UE::Mass::FStorageType& DebugGetEntityStorageInterface();` — For use by the friend MassDebugger
- L1396 _public prototype_ `const UE::Mass::FStorageType& DebugGetEntityStorageInterface() const;` — For use by the friend MassDebugger
- L1398 _public prototype_ `bool DebugHasCommandsToFlush() const;`
- L1400 _public prototype_ `UE::Mass::FSparseElementsStorage& DebugGetSparseElementsStorage();`
- L1405 _protected prototype_ `void OnPostFork(EForkProcessRole Role);` — Called on the child process upon process's forking
- L1407 _protected prototype_ `void GetMatchingArchetypes(const FMassFragmentRequirements& Requirements, TArray<FMassArchetypeHandle>& OutValidArchetypes, const uint32 FromArchetypeDataVersion) const;`
- L1413 _protected prototype_ `FMassArchetypeHandle InternalCreateSimilarArchetype(const TSharedPtr<FMassArchetypeData>& SourceArchetype, FMassElementBitSet&& NewCompositionBitSet);` — A "similar" archetype is an archetype exactly the same as SourceArchetype except for one composition aspect like Fragments or "Tags"
- L1414 _protected prototype_ `FMassArchetypeHandle InternalCreateSimilarArchetype(const TSharedPtr<FMassArchetypeData>& SourceArchetype, const UE::Mass::FArchetypeGroups& GroupsOverride);`
- L1415 _protected prototype_ `FMassArchetypeHandle InternalCreateSimilarArchetype(const FMassArchetypeData& SourceArchetypeRef, FMassArchetypeCompositionDescriptor&& NewComposition, const UE::Mass::FArchetypeGroups& GroupsOverride);`
- L1417 _protected prototype_ `void InternalAppendFragmentsAndTagsToArchetypeCompositionDescriptor(FMassArchetypeCompositionDescriptor& InOutComposition, TConstArrayView<const UScriptStruct*> FragmentsAndTagsList) const;`
- L1421 _private prototype_ `void InternalBatchRemoveSharedFragmentsFromEntities( TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, const FMassElementBitSet& ElementsToRemoveBitSet, const FMassSharedFragmentBitSet* SharedFragmentToRemoveBitSet, const FMassConstSharedFragmentBitSet* ConstSharedFragmentToRemoveBitSet);`
- L1427 _private prototype_ `void InternalBuildEntity(FMassEntityHandle EntityHandle, const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues);`
- L1428 _private prototype_ `void InternalReleaseEntity(FMassEntityHandle EntityHandle);`
- L1434 _private prototype_ `FMassElementBitSet InternalAddFragmentListToEntityChecked(FMassEntityHandle EntityHandle, const FMassElementBitSet& FragmentList);` — Adds fragments in FragmentList to the entity indicated by EntityHandle. Only the unique fragments will be added. @return Bitset for the added fragments (might be empty or a subset of `InFragments` depending on the current archetype fragments)
- L1440 _private prototype_ `void InternalAddFragmentListToEntity(FMassEntityHandle EntityHandle, const FMassElementBitSet& FragmentList);` — Similar to InternalAddFragmentListToEntity but expects NewFragmentList not overlapping with current entity's fragment list. It's callers responsibility to ensure that's true. Failing this will cause a `check` fail.
- L1442 _private prototype_ `void* InternalGetFragmentDataChecked(FMassEntityHandle EntityHandle, const UScriptStruct* FragmentType) const;` — Note that it's the caller's responsibility to ensure `FragmentType` is a kind of FMassFragment
- L1444 _private prototype_ `void* InternalGetFragmentDataPtr(FMassEntityHandle EntityHandle, const UScriptStruct* FragmentType) const;` — Note that it's the caller's responsibility to ensure `FragmentType` is a kind of FMassFragment
- L1446 _private prototype_ `const FConstSharedStruct* InternalGetConstSharedFragmentPtr(FMassEntityHandle EntityHandle, const UScriptStruct* ConstSharedFragmentType) const;` — Note that it's the caller's responsibility to ensure `ConstSharedFragmentType` is a kind of FMassSharedFragment
- L1448 _private prototype_ `const FSharedStruct* InternalGetSharedFragmentPtr(FMassEntityHandle EntityHandle, const UScriptStruct* SharedFragmentType) const;` — Note that it's the caller's responsibility to ensure `SharedFragmentType` is a kind of FMassSharedFragment
- L1450 _private prototype_ `TSharedPtr<FMassEntityManager::FEntityCreationContext> InternalBatchCreateReservedEntities(const FMassArchetypeHandle& ArchetypeHandle , const FMassArchetypeSharedFragmentValues& SharedFragmentValues, TConstArrayView<FMassEntityHandle> ReservedEntities , const bool bCreateContext);`
- L1454 _private function_ `UE::Mass::FStorageType& GetEntityStorageInterface() const`
- L1485 _private prototype_ `bool DebugDoCollectionsOverlapCreationContext(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections) const;`
- L1491 _private typedef_ `using FEntityStorageContainerType = TVariant< FEmptyVariantState, UE::Mass::FSingleThreadedEntityStorage, UE::Mass::FConcurrentEntityStorage>;`
- L1496 _private member_ `mutable FEntityStorageContainerType EntityStorage;`
- L1498 _private member_ `UE::Mass::FStorageType* DebugEntityStoragePtr = nullptr;`
- L1501 _private member_ `std::atomic<int32> ProcessingScopeCount = 0;`
- L1504 _private member_ `uint32 ArchetypeDataVersion = 0;` — the "version" number increased every time an archetype gets added
- L1507 _private member_ `TMap<uint32, TArray<TSharedPtr<FMassArchetypeData>>> FragmentHashToArchetypeMap;` — Map of hash of sorted fragment list to archetypes with that hash
- L1510 _private member_ `TMap<const UScriptStruct*, TArray<TSharedPtr<FMassArchetypeData>>> FragmentTypeToArchetypeMap;` — Map to list of archetypes that contain the specified fragment type
- L1514 _private member_ `TArray<TSharedPtr<FMassArchetypeData>> AllArchetypes;` — Contains all archetypes ever created. The array always growing and a given archetypes remains at a given index throughout its lifetime, and the index is never reused for another archetype.
- L1596 _private member_ `TSharedFragmentsContainer<FConstSharedStruct> ConstSharedFragmentsContainer;`
- L1597 _private member_ `TSharedFragmentsContainer<FSharedStruct> SharedFragmentsContainer;`
- L1599 _private member_ `FMassObserverManager ObserverManager;`
- L1601 _private member_ `TSharedRef<UE::Mass::FTypeManager> TypeManager;`
- L1602 _private member_ `UE::Mass::FRelationManager RelationManager;`
- L1605 _private member_ `UE::Mass::FSparseElementsStorage SparseElementsStorage;` — Stores sparse elements instances. Not accessible from outside on purpose.
- L1607 _private member_ `TMap<const FName, const int32> GroupNameToTypeIndex;`
- L1609 _private member_ `TArray<const FName> GroupTypes;` — @todo we'll probably have some "GroupTypeInformation" here in the future
- L1612 _private member_ `FMassRequirementAccessDetector RequirementAccessDetector;`
- L1613 _private member_ `FString DebugName;`
- L1614 _private member_ `EDebugFeatures EnabledDebugFeatures = EDebugFeatures::All;`
- L1617 _private member_ `TWeakObjectPtr<UObject> Owner;`
- L1619 _private member_ `FOnNewArchetypeDelegate OnNewArchetypeEvent;`
- L1621 _private member_ `FDelegateHandle OnPostForkHandle;`
- L1630 _private member_ `static constexpr int32 NumCommandBuffers = 2;` — This index will be enough to control which buffer is available for pushing commands since flashing is taking place in the game thread and pushing commands to the buffer fetched by Defer() is only supported also on the game thread (due to checking the cached thread ID). The whole CL aims to support non-mass code trying to push commands while the flushing is going on (as triggered by MassObservers reacting to the commands being flushed currently).
- L1631 _private member_ `TStaticArray<TSharedPtr<FMassCommandBuffer>, NumCommandBuffers> DeferredCommandBuffers;`
- L1632 _private member_ `uint8 OpenedCommandBufferIndex = 0;`
- L1633 _private member_ `std::atomic<bool> bCommandBufferFlushingInProgress = false;`
- L1634 _private member_ `bool bFirstCommandFlush = true;`
- L1643 _private member_ `EInitializationState InitializationState = EInitializationState::Uninitialized;`
- L1650 _public function_ `void AddElementToEntities(TConstArrayView<FMassEntityHandle> Entities, TNotNull<const UScriptStruct*> ElementType)` — `UE_DEPRECATED(5.8, "Use BatchAddElementToEntities instead")`
- L1655 _public function_ `void RemoveElementFromEntities(TConstArrayView<FMassEntityHandle> Entities, TNotNull<const UScriptStruct*> ElementType)` — `UE_DEPRECATED(5.8, "Use BatchRemoveElementFromEntities instead")`
- L1670 _function_ `template<UE::Mass::CSharedFragment T> void FMassEntityManager::ForEachSharedFragment(TFunctionRef< void(T& ) > ExecuteFunction)`
- L1682 _function_ `template<UE::Mass::CSharedFragment T> void FMassEntityManager::ForEachSharedFragmentConditional(TFunctionRef< bool(T& ) > ConditionFunction, TFunctionRef< void(T& ) > ExecuteFunction)`
- L1698 _function_ `template<UE::Mass::CConstSharedFragment T> void FMassEntityManager::ForEachConstSharedFragment(TFunctionRef< void(const T& ) > ExecuteFunction)`
- L1710 _function_ `template<UE::Mass::CConstSharedFragment T> void FMassEntityManager::ForEachConstSharedFragmentConditional(TFunctionRef< bool(const T& ) > ConditionFunction, TFunctionRef< void(const T& ) > ExecuteFunction)`
- L1725 _function_ `inline const UE::Mass::FTypeManager& FMassEntityManager::GetTypeManager() const`
- L1730 _function_ `inline UE::Mass::FTypeManager& FMassEntityManager::GetTypeManager()`
- L1735 _function_ `inline bool FMassEntityManager::IsDuringEntityCreation() const`
- L1740 _function_ `inline TSharedRef<FMassObserverManager::FObserverLock> FMassEntityManager::GetOrMakeObserversLock()`
- L1745 _function_ `inline UE::Mass::FRelationManager& FMassEntityManager::GetRelationManager()`
- L1751 _function_ `template<UE::Mass::CRelation T> bool FMassEntityManager::BatchCreateRelations(TArrayView<FMassEntityHandle> Subjects, TArrayView<FMassEntityHandle> Objects)`
- L1756 _function_ `inline void FMassEntityManager::SetEntityFragmentValues(FMassEntityHandle EntityHandle, TArrayView<const FInstancedStruct> FragmentInstanceList)`
- L1761 _function_ `inline void FMassEntityManager::BatchSetEntityFragmentValues(const FMassArchetypeEntityCollection& SparseEntities, TArrayView<const FInstancedStruct> FragmentInstanceList)`
- L1766 _function_ `inline void FMassEntityManager::BatchSetEntityFragmentValues(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TArrayView<const FInstancedStruct> FragmentInstanceList)`
- L1771 _prototype_ `extern template void FMassEntityManager::SetEntityFragmentValues<FInstancedStruct>(FMassEntityHandle EntityHandle, TConstArrayView<FInstancedStruct> FragmentInstanceList);`
- L1772 _prototype_ `extern template void FMassEntityManager::SetEntityFragmentValues<FStructView>(FMassEntityHandle EntityHandle, TConstArrayView<FStructView> FragmentInstanceList);`
- L1773 _prototype_ `extern template void FMassEntityManager::SetEntityFragmentValues<FConstStructView>(FMassEntityHandle EntityHandle, TConstArrayView<FConstStructView> FragmentInstanceList);`
- L1774 _prototype_ `extern template void FMassEntityManager::BatchSetEntityFragmentValues<FInstancedStruct>(const FMassArchetypeEntityCollection& SparseEntities, TConstArrayView<FInstancedStruct> FragmentInstanceList);`
- L1775 _prototype_ `extern template void FMassEntityManager::BatchSetEntityFragmentValues<FStructView>(const FMassArchetypeEntityCollection& SparseEntities, TConstArrayView<FStructView> FragmentInstanceList);`
- L1776 _prototype_ `extern template void FMassEntityManager::BatchSetEntityFragmentValues<FConstStructView>(const FMassArchetypeEntityCollection& SparseEntities, TConstArrayView<FConstStructView> FragmentInstanceList);`
- L1777 _prototype_ `extern template void FMassEntityManager::BatchSetEntityFragmentValues<FInstancedStruct>(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TConstArrayView<FInstancedStruct> FragmentInstanceList);`
- L1778 _prototype_ `extern template void FMassEntityManager::BatchSetEntityFragmentValues<FStructView>(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TConstArrayView<FStructView> FragmentInstanceList);`
- L1779 _prototype_ `extern template void FMassEntityManager::BatchSetEntityFragmentValues<FConstStructView>(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, TConstArrayView<FConstStructView> FragmentInstanceList);`

#### struct `FMassEntityManager::FScopedProcessing`  
`struct FScopedProcessing`  
_L110-133_
- L112 _public function_ `explicit FScopedProcessing(std::atomic<int32>& InProcessingScopeCount) : ScopedProcessingCount(InProcessingScopeCount)`
- L123 _public function_ `~FScopedProcessing()`
- L132 _private member_ `std::atomic<int32>& ScopedProcessingCount;`

#### enum `FMassEntityManager::EDebugFeatures`  
`enum class EDebugFeatures`  
_L1380-1385_
- L1382 _public enumerator_ `None`
- L1383 _public enumerator_ `TraceProcessors = 1 << 0` — Used to track information about processors such as their name.
- L1384 _public enumerator_ `All = TraceProcessors`

#### struct `FMassEntityManager::GetEntityStorageInterface::StorageSelector`  
`struct StorageSelector`  
_L1458-1475_
- L1460 _public function_ `UE::Mass::IEntityStorageInterface* operator()(FEmptyVariantState&) const`
- L1466 _public function_ `UE::Mass::IEntityStorageInterface* operator()(FSingleThreadedEntityStorage& Storage) const PRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L1471 _public function_ `UE::Mass::IEntityStorageInterface* operator()(FConcurrentEntityStorage& Storage) const`

#### struct `FMassEntityManager::TSharedFragmentsContainer`  
`template<typename TSharedStructType> struct TSharedFragmentsContainer`  
_L1521-1594_
- desc: This is a struct wrapping shared fragment management to ensure consistency between how shared and const shared fragment are added and fetched, across all the functions that do that
- L1523 _public function_ `TArray<TSharedStructType>* Find(const UScriptStruct* Type)`
- L1528 _public function_ `TSharedStructType& FindOrAdd(const uint32 Hash, const UScriptStruct* Type, const uint8* Data)`
- L1547 _public function_ `template<typename T, typename... TArgs> TSharedStructType& FindOrAdd(const uint32 Hash, TArgs&&... InArgs)`
- L1568 _public function_ `TSharedStructType& operator[](const int32 Index)`
- L1573 _public function_ `TArrayView<TSharedStructType> GetAllInstances()`
- L1579 _private function_ `int32 Add(TSharedStructType&& SharedStruct)`
- L1589 _private member_ `TArray<TSharedStructType> Instances;`
- L1591 _private member_ `TMultiMap<uint32, int32> HashToInstanceIndexMap;` — Hash/Index in array pair
- L1593 _private member_ `TMap<const UScriptStruct*, TArray<TSharedStructType>> TypeToInstanceMap;` — Maps specific struct type to a collection of FSharedStruct instances of that type

#### enum `FMassEntityManager::EInitializationState`  
`enum class EInitializationState : uint8`  
_L1636-1641_
- L1638 _public enumerator_ `Uninitialized`
- L1639 _public enumerator_ `Initialized`
- L1640 _public enumerator_ `Deinitialized`

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_API MASSENTITY_API`
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Mass` (scope `UE`)
- L49 _namespace_ `namespace Private` (scope `UE::Mass`)
- L53 _namespace_ `namespace ObserverManager` (scope `UE::Mass`)
- L69 _macro_ `#define REQUESTED_MASS_CONCURRENT_RESERVE 1`
- L72 _macro_ `#define WITH_MASS_CONCURRENT_RESERVE (REQUESTED_MASS_CONCURRENT_RESERVE || WITH_EDITOR)`
- L74 _namespace_ `namespace UE`
- L74 _namespace_ `namespace Mass` (scope `UE`)
- L77 _typedef_ `using FStorageType = IEntityStorageInterface;` (scope `UE::Mass`)
- L103 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewArchetypeDelegate, const FMassArchetypeHandle&);`
- L119 _function_ `` (scope `FMassEntityManager::FScopedProcessing::FScopedProcessing`)
- L1666 _prototype_ `ENUM_CLASS_FLAGS(FMassEntityManager::EDebugFeatures);`

### `Source/Runtime/MassEntity/Public/MassEntityManagerStorage.h` (Public)


#### struct `FMassEntityManager_InitParams_SingleThreaded`  
`FMassEntityManager_InitParams_SingleThreaded`  
_L19-19_
- reflection: `UE_DEPRECATED(5.8, "Single threaded entity storage is being removed. Use FMassEntityManager_InitParams_Concurrent instead.")`

#### struct `FMassEntityManager_InitParams_Concurrent`  
`struct FMassEntityManager_InitParams_Concurrent`  
_L31-44_
- desc: Initialization parameters to configure MassEntityManager to concurrently reserve entities Only supported in editor builds. Expected static memory requirement for array of Page pointers can be computed: MaxPages = MaxEntityCount / MaxEntitiesPerPage MemorySize = MaxPages * sizeof(Page**) For default values, expectation is 128kB
- L37 _public member_ `uint32 MaxEntityCount = 1 << 30;` — Maximum supported entities by the MassEntityManager Must be multiple of 2
- L43 _public member_ `uint32 MaxEntitiesPerPage = 1 << 16;` — Number of entities per chunk Must be multiple of 2

#### class `UE::Mass::IEntityStorageInterface`  
`class IEntityStorageInterface`  
_L56-132_
- desc: Interface that abstracts the storage system for Mass Entities in the EntityManager This may be temporary until the concurrent mechanism has been vetted for performance
- L68 _public prototype_ `virtual ~IEntityStorageInterface() = default;`
- L70 _public prototype_ `virtual FMassArchetypeData* GetArchetype(int32 Index) = 0;`
- L71 _public prototype_ `virtual const FMassArchetypeData* GetArchetype(int32 Index) const = 0;`
- L72 _public prototype_ `virtual TSharedPtr<FMassArchetypeData>& GetArchetypeAsShared(int32 Index) = 0;`
- L73 _public prototype_ `virtual const TSharedPtr<FMassArchetypeData>& GetArchetypeAsShared(int32 Index) const = 0;`
- L75 _public prototype_ `virtual void SetArchetypeFromShared(int32 Index, TSharedPtr<FMassArchetypeData>& Archetype) = 0;`
- L76 _public prototype_ `virtual void SetArchetypeFromShared(int32 Index, const TSharedPtr<FMassArchetypeData>& Archetype) = 0;`
- L82 _public prototype_ `virtual EEntityState GetEntityState(int32 Index) const = 0;` — Returns true if the given entity at index is currently reserved False if free or assigned an archetype
- L84 _public prototype_ `virtual int32 GetSerialNumber(int32 Index) const = 0;`
- L87 _public prototype_ `virtual bool IsValidIndex(int32 Index) const = 0;` — Checks if index can be used to access entity data
- L93 _public prototype_ `virtual bool IsValidHandle(FMassEntityHandle EntityHandle) const = 0;` — Checks if the given handle is valid in the context od this storage, i.e. whether the index is valid and the serial number associated with it matches the handle's
- L95 _public prototype_ `virtual bool IsEntityActive(FMassEntityHandle EntityHandle) const = 0;`
- L97 _public prototype_ `virtual SIZE_T GetAllocatedSize() const = 0;`
- L100 _public prototype_ `virtual bool IsValid(int32 Index) const = 0;` — Checks if entity at Index is built
- L103 _public prototype_ `virtual FMassEntityHandle AcquireOne() = 0;` — Produce a single entity handle
- L108 _public prototype_ `int32 Acquire(const int32 Count, TArray<FMassEntityHandle>& OutEntityHandles);` — @return number of entities actually added
- L109 _public prototype_ `virtual int32 Acquire(TArrayView<FMassEntityHandle> OutEntityHandles) = 0;`
- L111 _public prototype_ `virtual int32 Release(TConstArrayView<FMassEntityHandle> Handles) = 0;`
- L112 _public prototype_ `virtual int32 ReleaseOne(FMassEntityHandle Handles) = 0;`
- L118 _public prototype_ `virtual int32 ForceRelease(TConstArrayView<FMassEntityHandle> Handles) = 0;` — Bypasses Serial Number Check Only use if caller has ensured serial number matches or for debug purposes
- L119 _public prototype_ `virtual int32 ForceReleaseOne(FMassEntityHandle Handle) = 0;`
- L125 _public prototype_ `virtual int32 Num() const = 0;` — Returns the number of entities that are not free For debug purposes only. In multi-threaded environments, the result is going to be out of date
- L131 _public prototype_ `virtual int32 ComputeFreeSize() const = 0;` — Returns the number of entities that are free For debug purposes only. In multi-threaded environments, the result is going to be out of date

#### enum `UE::Mass::IEntityStorageInterface::EEntityState`  
`enum class EEntityState`  
_L59-67_
- L62 _public enumerator_ `Free` — Entity index refers to an entity that is free to be reserved or created
- L64 _public enumerator_ `Reserved` — Entity index refers to a reserved entity
- L66 _public enumerator_ `Created` — Entity index refers to an entity assigned to an archetype

#### class `UE::Mass::FSingleThreadedEntityStorage`  
`FSingleThreadedEntityStorage final : public IEntityStorageInterface`  
_L143-194_
- reflection: `UE_DEPRECATED(5.8, "Single threaded entity storage is being removed. Use FConcurrentEntityStorage instead.")`
- inherits: `IEntityStorageInterface`
- L147 _public prototype_ `void Initialize(const FMassEntityManager_InitParams_SingleThreaded&);`
- L149 _public prototype_ `virtual FMassArchetypeData* GetArchetype(int32 Index) override;`
- L150 _public prototype_ `virtual const FMassArchetypeData* GetArchetype(int32 Index) const override;`
- L151 _public prototype_ `virtual TSharedPtr<FMassArchetypeData>& GetArchetypeAsShared(int32 Index) override;`
- L152 _public prototype_ `virtual const TSharedPtr<FMassArchetypeData>& GetArchetypeAsShared(int32 Index) const override;`
- L153 _public prototype_ `virtual void SetArchetypeFromShared(int32 Index, TSharedPtr<FMassArchetypeData>&) override;`
- L154 _public prototype_ `virtual void SetArchetypeFromShared(int32 Index, const TSharedPtr<FMassArchetypeData>&) override;`
- L155 _public prototype_ `virtual EEntityState GetEntityState(int32 Index) const override;`
- L156 _public prototype_ `virtual int32 GetSerialNumber(int32 Index) const override;`
- L157 _public prototype_ `virtual bool IsValidIndex(int32 Index) const override;`
- L158 _public prototype_ `virtual bool IsValidHandle(FMassEntityHandle EntityHandle) const override;`
- L159 _public prototype_ `virtual bool IsEntityActive(FMassEntityHandle EntityHandle) const override;`
- L160 _public prototype_ `virtual SIZE_T GetAllocatedSize() const override;`
- L161 _public prototype_ `virtual bool IsValid(int32 Index) const override;`
- L162 _public prototype_ `virtual FMassEntityHandle AcquireOne() override;`
- L164 _public prototype_ `virtual int32 Acquire(TArrayView<FMassEntityHandle> OutEntityHandles) override;`
- L165 _public prototype_ `virtual int32 Release(TConstArrayView<FMassEntityHandle> Handles) override;`
- L166 _public prototype_ `virtual int32 ReleaseOne(FMassEntityHandle Handle) override;`
- L167 _public prototype_ `virtual int32 ForceRelease(TConstArrayView<FMassEntityHandle> Handles) override;`
- L168 _public prototype_ `virtual int32 ForceReleaseOne(FMassEntityHandle Handle) override;`
- L169 _public prototype_ `virtual int32 Num() const override;`
- L170 _public prototype_ `virtual int32 ComputeFreeSize() const override;`
- L183 _private member_ `std::atomic<int32> NextSerialNumber = 0;`
- L186 _private function_ `int32 GenerateSerialNumber()`
- L192 _private member_ `TChunkedArray<FEntityData> Entities;`
- L193 _private member_ `TArray<int32> EntityFreeIndexList;`

#### struct `UE::Mass::FSingleThreadedEntityStorage::FEntityData`  
`struct FEntityData`  
_L173-181_
- L175 _public member_ `TSharedPtr<FMassArchetypeData> CurrentArchetype;`
- L176 _public member_ `int32 SerialNumber = 0;`
- L178 _public prototype_ `~FEntityData();`
- L179 _public prototype_ `void Reset();`
- L180 _public prototype_ `bool IsValid() const;`

#### class `UE::Mass::FConcurrentEntityStorage`  
`class FConcurrentEntityStorage final : public IEntityStorageInterface`  
_L205-284_
- inherits: `IEntityStorageInterface`
- desc: This storage backend allows for entities to be concurrently reserved. Reserved entities can also be concurrently freed. Creation of entities (i.e. assignment of an archetype and addition of data into chunks) cannot be done concurrently with this implementation.
- L209 _public prototype_ `void Initialize(const FMassEntityManager_InitParams_Concurrent& InInitializationParams);`
- L213 _public prototype_ `virtual FMassArchetypeData* GetArchetype(int32 Index) override;`
- L214 _public prototype_ `virtual const FMassArchetypeData* GetArchetype(int32 Index) const override;`
- L215 _public prototype_ `virtual TSharedPtr<FMassArchetypeData>& GetArchetypeAsShared(int32 Index) override;`
- L216 _public prototype_ `virtual const TSharedPtr<FMassArchetypeData>& GetArchetypeAsShared(int32 Index) const override;`
- L217 _public prototype_ `virtual void SetArchetypeFromShared(int32 Index, TSharedPtr<FMassArchetypeData>& Archetype) override;`
- L218 _public prototype_ `virtual void SetArchetypeFromShared(int32 Index, const TSharedPtr<FMassArchetypeData>& Archetype) override;`
- L219 _public prototype_ `virtual EEntityState GetEntityState(int32 Index) const override;`
- L220 _public prototype_ `virtual int32 GetSerialNumber(int32 Index) const override;`
- L221 _public prototype_ `virtual bool IsValidIndex(int32 Index) const override;`
- L222 _public prototype_ `virtual bool IsValidHandle(FMassEntityHandle EntityHandle) const override;`
- L223 _public prototype_ `virtual bool IsEntityActive(FMassEntityHandle EntityHandle) const override;`
- L224 _public prototype_ `virtual SIZE_T GetAllocatedSize() const override;`
- L225 _public prototype_ `virtual bool IsValid(int32 Index) const override;`
- L226 _public prototype_ `virtual FMassEntityHandle AcquireOne() override;`
- L228 _public prototype_ `virtual int32 Acquire(TArrayView<FMassEntityHandle> OutEntityHandles) override;`
- L229 _public prototype_ `virtual int32 Release(TConstArrayView<FMassEntityHandle> Handles) override;`
- L230 _public prototype_ `virtual int32 ReleaseOne(FMassEntityHandle Handle) override;`
- L231 _public prototype_ `virtual int32 ForceRelease(TConstArrayView<FMassEntityHandle> Handles) override;`
- L232 _public prototype_ `virtual int32 ForceReleaseOne(FMassEntityHandle Handle) override;`
- L233 _public prototype_ `virtual int32 Num() const override;`
- L234 _public prototype_ `virtual int32 ComputeFreeSize() const override;`
- L237 _public prototype_ `static bool DebugAssumptionsSelfTest();` — @return whether the assumptions are still valid
- L258 _private prototype_ `EEntityState GetEntityStateInternal(const FEntityData& EntityData) const;`
- L260 _private prototype_ `FEntityData& LookupEntity(int32 Index);`
- L261 _private prototype_ `const FEntityData& LookupEntity(int32 Index) const;`
- L264 _private prototype_ `uint64 ComputePageSize() const;` — Returns size of a page in bytes
- L269 _private prototype_ `bool AddPage();` — @return whether the operation was successful. Will return false when OOM
- L272 _private member_ `uint32 EntityCount = 0;` — Number of allocated Entities (only used for viewing in the debugger).
- L273 _private member_ `uint32 MaximumEntityCountShift = 0;`
- L274 _private member_ `uint32 MaxEntitiesPerPage = 0;`
- L275 _private member_ `uint32 MaxEntitiesPerPageShift = 0;`
- L276 _private member_ `uint32 PageCount = 0;`
- L278 _private member_ `UE::FTransactionallySafeMutex PageAllocateMutex;` — ALWAYS acquire FreeListMutex before this one
- L280 _private member_ `FEntityData** EntityPages = nullptr;` — Pointer to array of pages
- L282 _private member_ `TArray<int32> EntityFreeIndexList;`
- L283 _private member_ `UE::FTransactionallySafeMutex FreeListMutex;`

#### struct `UE::Mass::FConcurrentEntityStorage::FEntityData`  
`struct FEntityData`  
_L241-256_
- L243 _public member_ `static constexpr int MaxGenerationBits = 30;`
- L245 _public member_ `TSharedPtr<FMassArchetypeData> CurrentArchetype;`
- L247 _public member_ `uint32 GenerationId : MaxGenerationBits = 0;` — Generation ID or version of the entity in this slot
- L249 _public member_ `uint32 bIsAllocated : 1 = 0;` — 1 if the entity is NOT free
- L251 _public prototype_ `~FEntityData();`
- L253 _public prototype_ `int32 GetSerialNumber() const;` — Converts EntityData state into a SerialNumber for public usage
- L255 _public prototype_ `bool operator==(const FEntityData& Other) const;`

#### Free symbols / members of external scopes

- L47 _typedef_ `using FMassEntityManagerStorageInitParams = TVariant<FMassEntityManager_InitParams_SingleThreaded, FMassEntityManager_InitParams_Concurrent>;`
- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassEntityQuery.h` (Public)


#### struct `FMassEntityQuery`  
`struct FMassEntityQuery : public FMassFragmentRequirements, public FMassSubsystemRequirements`  
_L50-404_
- inherits: `FMassFragmentRequirements,FMassSubsystemRequirements`
- desc: FMassEntityQuery is a structure that is used to trigger calculations on cached set of valid archetypes as described by requirements. See the parent classes FMassFragmentRequirements and FMassSubsystemRequirements for setting up the required fragments and subsystems. A query to be considered valid needs declared at least one EMassFragmentPresence::All, EMassFragmentPresence::Any EMassFragmentPresence::Optional fragment requirement.
- L52 _public member_ `static constexpr int32 ArchetypeMatchOverrideSize = MASS_ACHETYPE_OVERRIDE_MAX_SIZE;`
- L53 _public member_ `static constexpr uint32 ArchetypeMatchOverrideAlignment = MASS_ACHETYPE_OVERRIDE_MAX_ALIGNMENT;`
- L80 _public prototype_ `FMassEntityQuery() = default;`
- L81 _public prototype_ `FMassEntityQuery(UMassProcessor& Owner);`
- L82 _public prototype_ `FMassEntityQuery(const TSharedPtr<FMassEntityManager>& EntityManager);`
- L83 _public prototype_ `FMassEntityQuery(const TSharedRef<FMassEntityManager>& EntityManager, std::initializer_list<UScriptStruct*> InitList);`
- L84 _public prototype_ `FMassEntityQuery(const TSharedRef<FMassEntityManager>& EntityManager, TConstArrayView<const UScriptStruct*> InitList);`
- L86 _public prototype_ `void RegisterWithProcessor(UMassProcessor& Owner);`
- L89 _public prototype_ `void ForEachEntityChunk(FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction);` — Runs ExecuteFunction on all entities matching Requirements
- L98 _public prototype_ `void ForEachEntityChunk(FMassExecutionContext& ExecutionContext, UE::Mass::FExecutionLimiter& Limiter, const FMassExecuteFunction& ExecuteFunction);` — Runs ExecuteFunction on entities matching Requirements up to the EntityLimit specified in the ExecutionLimiter. Resumes from last index set in Limiter. Will always complete the current chunk once the limit is reached. Does not account for changes to entity count or organization between iterations (Entities could be skipped). Identical to the unlimited version if the Limit exceeds the number of applicable entities.
- L104 _public prototype_ `void ForEachEntityChunk(const FMassArchetypeEntityCollection& EntityCollection , FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction);` — Executes provided ExecuteFunction for entities in EntityCollection. If EntityCollection's archetype doesn't match the query's requirements then ExecuteFunction won't be executed.
- L107 _public prototype_ `void ForEachEntityChunk(FMassArchetypeEntityCollection&& EntityCollection , FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction);`
- L113 _public prototype_ `void ParallelForEachEntityChunk(FMassExecutionContext& ExecutionContext , const FMassExecuteFunction& ExecuteFunction, const EParallelExecutionFlags Flags = EParallelExecutionFlags::Default);` — Attempts to process every chunk of every affected archetype in parallel.
- L116 _public prototype_ `void ForEachEntityChunkInCollections(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections , FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction);`
- L119 _public prototype_ `void ParallelForEachEntityChunkInCollection(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections , FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction , const EParallelExecutionFlags Flags = EParallelExecutionFlags::Default);`
- L126 _public prototype_ `void CacheArchetypes();` — Will gather all archetypes from InEntityManager matching this->Requirements. Note that no work will be done if the cached data is up to date (as tracked by EntitySubsystemHash and ArchetypeDataVersion properties).
- L128 _public function_ `void Clear()`
- L136 _public function_ `inline void DirtyCachedData()`
- L144 _public function_ `FMassSubsystemRequirements& AddSubsystemRequirement(const TSubclassOf<USubsystem> SubsystemClass, const EMassFragmentAccess AccessMode)`
- L150 _public function_ `bool DoesRequireGameThreadExecution() const`
- L157 _public function_ `void RequireMutatingWorldAccess()`
- L162 _public function_ `bool IsEmpty() const`
- L167 _public function_ `const TArray<FMassArchetypeHandle>& GetArchetypes() const`
- L177 _public prototype_ `uint64 CalculateArchetypeEntityOrderHash();` — Calculates a hash of the entity order revisions in all archetypes. If returned value ever differs from a previous call it indicates that one or more archetypes associated with this query have been updated by having the entity order changed.
- L184 _public prototype_ `uint64 CalculateArchetypeVersionHash();` — Calculates a hash of the version of all archetypes. If returned value ever differs from a previous call it indicates that one or more archetypes associated with this query have been updated by having entities added, removed or re-ordered.
- L191 _public prototype_ `int32 GetNumMatchingEntities();` — Goes through ValidArchetypes and sums up the number of entities contained in them. Note that the function is not const because calling it can result in re-caching of ValidArchetypes @return the number of entities this given query would process if called "now"
- L198 _public prototype_ `int32 GetNumMatchingEntities(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections);` — Sums the entity range lengths for each collection in EntityCollections, where the collection's archetype matches the query's requirements. @return the number of entities this given query would process if called "now" for EntityCollections
- L205 _public prototype_ `bool HasMatchingEntities();` — Checks if any of ValidArchetypes has any entities. Note that the function is not const because calling it can result in re-caching of ValidArchetypes @return "true" if any of the ValidArchetypes has any entities, "false" otherwise
- L211 _public prototype_ `TArray<FMassArchetypeEntityCollection> CreateMatchingEntitiesCollection();` — Creates an array of FMassArchetypeEntityCollection instances that identify all the entities currently matching this query.
- L216 _public prototype_ `TArray<FMassEntityHandle> GetMatchingEntityHandles();` — Fetches entity handles of all the entities currently matching this query.
- L223 _public prototype_ `void SetChunkFilter(const FMassChunkConditionFunction& InFunction);` — Sets a chunk filter condition that will be applied to each chunk of all valid archetypes. Note that this condition won't be applied when a specific entity collection is used (via FMassArchetypeEntityCollection ) The value returned by InFunction controls whether to allow execution (true) or block it (false).
- L225 _public function_ `void ClearChunkFilter()`
- L230 _public function_ `bool HasChunkFilter() const`
- L235 _public prototype_ `void GroupBy(UE::Mass::FArchetypeGroupType GroupType);`
- L236 _public prototype_ `void GroupBy(UE::Mass::FArchetypeGroupType GroupType, const TFunction<bool(const UE::Mass::FArchetypeGroupID, const UE::Mass::FArchetypeGroupID)>& Predicate);`
- L237 _public prototype_ `void ResetGrouping();`
- L243 _public prototype_ `bool IsGrouping() const;` — @return whether the query is configured to use archetype group information to group and sort archetypes to be processed.
- L247 _public prototype_ `template<typename T> requires TArchetypeMatchOverrideConcept<T> void SetArchetypeMatchOverride(const T& Override);`
- L250 _public prototype_ `const TSharedPtr<FMassEntityManager>& GetEntityManager() const;`
- L256 _public prototype_ `const FMassQueryRequirementIndicesMapping& GetRequirementsMappingForArchetype(const FMassArchetypeHandle ArchetypeHandle) const;` — If ArchetypeHandle is among ValidArchetypes then the function retrieves requirements mapping cached for it, otherwise an empty mapping will be returned (and the requirements binding will be done the slow way).
- L258 _public prototype_ `void ExportRequirements(FMassExecutionRequirements& OutRequirements) const;`
- L264 _public function_ `void SetParallelCommandBufferEnabled(const bool bInAllowParallelCommands)` — Controls whether ParallelForEachEntityChunk creates separate command buffers for each job. @see bAllowParallelCommands for more details
- L273 _public prototype_ `void DebugEnableEntityOwnerLogging();` — Configures the query to support per-entity logging based on their individual UObject "owners", as declared via debug fragments.
- L275 _public function_ `void AddCreatedArchetype(const FMassElementBitSet& InComposition)`
- L280 _public function_ `void AddCreatedArchetype(FMassElementBitSet&& InComposition)`
- L285 _public function_ `FMassEntityCreationRequirements& GetEntityCreationRequirements()`
- L295 _private prototype_ `void SortArchetypes(const int32 FirstNewArchetypeIndex = 0);` — Incrementally sorts all ValidArchetypes to fill OrderedArchetypeIndices with the expected order of archetype processing. This function will only ever get called when there are actual sorting steps registered (@see GroupBy)
- L300 _private prototype_ `void BuildOrderedArchetypeIndices(const int32 FirstNewArchetypeIndex = 0);` — An alternative to SortArchetypes that will get called in the absence of archetype sorting steps to maintain OrderedArchetypeIndices and have it reflect the order of ValidArchetypes.
- L305 _private prototype_ `uint64 CalculateArchetypeHash_Internal(TFunctionRef<uint32(const FMassArchetypeData*)> HashValueGetter);` — Internal function to hash any value for all archetypes associated with this query.
- L312 _private member_ `FMassChunkConditionFunction ChunkCondition;` — This function represents a condition that will be called for every chunk to be processed before the actual execution function is called. The chunk fragment requirements are already bound and ready to be used by the time ChunkCondition is executed.
- L314 _private member_ `uint32 EntitySubsystemHash = 0;`
- L315 _private member_ `uint32 LastUpdatedArchetypeDataVersion = 0;`
- L317 _private member_ `TArray<FMassArchetypeHandle> ValidArchetypes;`
- L318 _private member_ `TArray<int32> OrderedArchetypeIndices;`
- L319 _private member_ `TArray<FMassQueryRequirementIndicesMapping> ArchetypeFragmentMapping;`
- L331 _private member_ `TArray<FArchetypeGroupingStep> GroupSortingSteps;`
- L332 _private member_ `TArray<TArray<UE::Mass::FArchetypeGroupID>> CachedGroupIDs;`
- L334 _private member_ `FMassEntityCreationRequirements EntityCreationRequirements;`
- L344 _private member_ `uint8 bAllowParallelCommands : 1 = true;` — Controls whether ParallelForEachEntityChunk created dedicated command buffer for each job. This is required to ensure thread safety. Disable by calling SetParallelCommandBufferEnabled(false) if execution function doesn't issue commands. Disabling will save some performance since it will avoid dynamic allocation of command buffers. @Note that disabling parallel commands will result in no command buffer getting passed to execution which in turn will cause crashes if the underlying code does try to issue commands.
- L345 _private member_ `uint8 bRequiresMutatingWorldAccess : 1 = false;`
- L347 _private member_ `uint8 bHasArchetypeMatchOverride : 1 = false;`
- L350 _private member_ `EMassExecutionContextType ExpectedContextType = EMassExecutionContextType::Local;`
- L353 _private member_ `uint8 bRegistered : 1 = false;`
- L357 _private member_ `FArchetypeMatchOverride ArchetypeMatchOverride;`
- L365 _public prototype_ `FMassEntityQuery(std::initializer_list<UScriptStruct*> InitList);` — `UE_DEPRECATED(5.6, "This type of FMassEntityQuery is no longer supported. Use one of the other constructors instead.")`
- L368 _public prototype_ `FMassEntityQuery(TConstArrayView<const UScriptStruct*> InitList);` — `UE_DEPRECATED(5.6, "This type of FMassEntityQuery is no longer supported. Use one of the other constructors instead.")`
- L377 _public prototype_ `void ForEachEntityChunk(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction);` — `UE_DEPRECATED(5.6, "ForEachEntityChunk is deprecated. New version doesn't require the FMassEntityManager parameter")`
- L380 _public prototype_ `void ForEachEntityChunk(const FMassArchetypeEntityCollection& EntityCollection, FMassEntityManager& EntityManager , FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction);` — `UE_DEPRECATED(5.6, "ForEachEntityChunk is deprecated. New version doesn't require the FMassEntityManager parameter")`
- L384 _public prototype_ `void ParallelForEachEntityChunk(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext , const FMassExecuteFunction& ExecuteFunction, const EParallelForMode ParallelMode = Default);` — `UE_DEPRECATED(5.6, "ParallelForEachEntityChunk is deprecated. New version doesn't require the FMassEntityManager parameter. Also ParallelMode parameter changed type, usee EParallelExecutionFlags instead.")`
- L388 _public prototype_ `void ForEachEntityChunkInCollections(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections, FMassEntityManager& EntityManager , FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction);` — `UE_DEPRECATED(5.6, "ForEachEntityChunkInCollections is deprecated. New version doesn't require the FMassEntityManager parameter")`
- L392 _public prototype_ `void ParallelForEachEntityChunkInCollection(TConstArrayView<FMassArchetypeEntityCollection> EntityCollections , FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext, const FMassExecuteFunction& ExecuteFunction , const EParallelForMode ParallelMode);` — `UE_DEPRECATED(5.6, "ParallelForEachEntityChunkInCollection is deprecated. New version doesn't require the FMassEntityManager parameter. Also ParallelMode parameter changed type, usee EParallelExecutionFlags instead.")`
- L397 _public prototype_ `void CacheArchetypes(const FMassEntityManager& InEntityManager);` — `UE_DEPRECATED(5.6, "This flavor of CacheArchetypes is deprecated. EntityQueries are not tied to a specific EntityManager instance and there's no need to pass it in as a parameter")`
- L400 _public prototype_ `int32 GetNumMatchingEntities(FMassEntityManager& InEntityManager);` — `UE_DEPRECATED(5.6, "This flavor of GetNumMatchingEntities is deprecated. EntityQueries are not tied to a specific EntityManager instance and there's no need to pass it in as a parameter")`
- L403 _public prototype_ `bool HasMatchingEntities(FMassEntityManager& InEntityManager);` — `UE_DEPRECATED(5.6, "This flavor of HasMatchingEntities is deprecated. EntityQueries are not tied to a specific EntityManager instance and there's no need to pass it in as a parameter")`
- L413 _function_ `template <typename T> requires TArchetypeMatchOverrideConcept<T> void FMassEntityQuery::SetArchetypeMatchOverride(const T& Context)`
- L432 _function_ `inline void FMassEntityQuery::SetChunkFilter(const FMassChunkConditionFunction& InFunction)`
- L438 _function_ `inline bool FMassEntityQuery::IsGrouping() const`
- L443 _function_ `inline const TSharedPtr<FMassEntityManager>& FMassEntityQuery::GetEntityManager() const`

#### struct `FMassEntityQuery::FArchetypeMatchOverride`  
`struct FArchetypeMatchOverride`  
_L58-64_
- L60 _public typedef_ `using MatchFunction = bool (*)(const void* , const FMassArchetypeCompositionDescriptor&);`
- L62 _public member_ `MatchFunction Match = nullptr;`
- L63 _public member_ `TAlignedBytes<ArchetypeMatchOverrideSize, ArchetypeMatchOverrideAlignment> Data;`

#### enum `FMassEntityQuery::EParallelExecutionFlags`  
`enum class EParallelExecutionFlags`  
_L67-78_
- L70 _public enumerator_ `Default = 0` — Use whatever the whole system has been configured for.
- L72 _public enumerator_ `Force = 1 << 0` — Force parallel execution of a processor for each chunk even when parallel execution has been disabled.
- L77 _public enumerator_ `AutoBalance = 1 << 1` — The default behavior for parallel execution assigns each chunk to a thread before execution. This implicitly assumes all chunks take roughly the same amount of time to process. If chunks vary in the time it takes to process this flag can be used to queue chunks so threads can pick them up as soon as possible. This makes starting the processing of a chunk more expensive but can result in better overall utilization of threads.

#### struct `FMassEntityQuery::FArchetypeGroupingStep`  
`struct FArchetypeGroupingStep`  
_L321-330_
- L323 _public prototype_ `FArchetypeGroupingStep() = default;`
- L324 _public function_ `FArchetypeGroupingStep(UE::Mass::FArchetypeGroupType InGroupType, const TFunction<bool(const UE::Mass::FArchetypeGroupID, const UE::Mass::FArchetypeGroupID)>& InPredicate) : GroupType(InGroupType), Predicate(InPredicate)`
- L328 _public member_ `UE::Mass::FArchetypeGroupType GroupType;`
- L329 _public member_ `TFunction<bool(const UE::Mass::FArchetypeGroupID, const UE::Mass::FArchetypeGroupID)> Predicate;`

#### enum `FMassEntityQuery::EParallelForMode`  
`enum EParallelForMode`  
_L370-374_
- L372 _public enumerator_ `Default = static_cast<int32>(EParallelExecutionFlags::Default)`
- L373 _public enumerator_ `ForceParallelExecution = static_cast<int32>(EParallelExecutionFlags::Force)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MASSENTITY_API`
- L21 _macro_ `#define WITH_ARCHETYPE_MATCH_OVERRIDE (WITH_EDITOR)`
- L25 _macro_ `#define MASS_ACHETYPE_OVERRIDE_MAX_SIZE 16`
- L29 _macro_ `#define MASS_ACHETYPE_OVERRIDE_MAX_ALIGNMENT 8`
- L406 _prototype_ `ENUM_CLASS_FLAGS(FMassEntityQuery::EParallelExecutionFlags);`
- L424 _function_ `` (scope `FMassEntityQuery::SetArchetypeMatchOverride`)

### `Source/Runtime/MassEntity/Public/MassEntityRelations.h` (Public)


#### enum `UE::Mass::Relations::ERemovalPolicy`  
`enum class ERemovalPolicy : uint8`  
_L23-36_
- L26 _public enumerator_ `CleanUp` — only update the book-keeping
- L28 _public enumerator_ `Destroy` — when a given relation gets removed destroy the source entity (eg destroy the child when ChildOf relation gets removed)
- L30 _public enumerator_ `Splice` — external code will be called to patch up what remains off the relation
- L32 _public enumerator_ `Custom` — the user will provide the observer processor
- L34 _public enumerator_ `MAX`
- L35 _public enumerator_ `Default = CleanUp`

#### enum `UE::Mass::Relations::EExternalMappingRequired`  
`enum class EExternalMappingRequired : uint8`  
_L38-43_
- L40 _public enumerator_ `No`
- L41 _public enumerator_ `Yes`
- L42 _public enumerator_ `Default = Yes`

#### enum `UE::Mass::Relations::ERelationRole`  
`enum class ERelationRole : uint8`  
_L45-50_
- L47 _public enumerator_ `Subject`
- L48 _public enumerator_ `Object`
- L49 _public enumerator_ `MAX`

#### struct `UE::Mass::Relations::FRoleTraits`  
`struct FRoleTraits`  
_L61-102_
- L67 _public member_ `const UScriptStruct* Element = nullptr;` — The element type that will be added to the participating entity. Can remain empty. Every entity will get the relation tag as well, the FRelationTypeTraits.RelationTagType
- L72 _public member_ `ERemovalPolicy DestructionPolicy = ERemovalPolicy::Default;` — What to do when entities serving this role are destroyed. This value affects the whole relation, including other participants.
- L79 _public member_ `bool bExclusive = true;` — "Exclusive" means there can be only one participant like this in a relation. For example, there can be only one parent in our ChildOf relation (bExclusive = true, on the "parent" participant, i.e. the `Object`) while there can be multiple children (bExclusive = false for the `Subject`)
- L93 _public member_ `EExternalMappingRequired RequiresExternalMapping = EExternalMappingRequired::Default;` — Declares whether this relation-specific implementation details provide dedicated mechanism for mapping other roles for entities serving as this role, the role these traits affect. It essentially answers whether this role needs the system to find other relation participants (`Yes`) or it can handle the task with custom code (like via the Element, option `No`). Defaulting to `Yes` to provide reliable, out-of-the-box functionality required for fetching participants of relation instances. Set to `No` if you want to save memory by not automatically populating and utilizing FRelationData.RoleMap. @todo this functionality is not plugged in yet.
- L95 _public function_ `bool operator==(const FRoleTraits& Other) const`

#### struct `UE::Mass::Relations::FRelationTypeTraits`  
`struct FRelationTypeTraits`  
_L104-174_
- L106 _public prototype_ `FRelationTypeTraits(TNotNull<const UScriptStruct*> InRelationTagType);`
- L107 _public prototype_ `FRelationTypeTraits(const FRelationTypeTraits& Other, TNotNull<const UScriptStruct*> NewRelationTagType);`
- L108 _public prototype_ `FRelationTypeTraits(const FRelationTypeTraits& Other) = default;`
- L110 _public function_ `TNotNull<const UScriptStruct*> GetRelationTagType() const`
- L115 _public function_ `FName GetFName() const`
- L120 _public member_ `FName RelationName;`
- L123 _public prototype_ `bool IsValid() const;` — Checks whether the traits are configured properly.
- L127 _private member_ `TNotNull<const UScriptStruct*> RelationTagType;` — can only be set during creation since we use the same type to create UE::Mass::FTypeHandle for the relation type
- L135 _public member_ `TNotNull<const UScriptStruct*> RelationFragmentType;` — The fragment type that will be automatically added to each relation entity created to represent relation instances @todo we can switch this to an array of fragment types or FInstancedStructs, bitsets or even FMassArchetypeCompositionDescriptor, but first we need to see how our use-cases shape up.
- L142 _public member_ `bool bCreateRelationEntitiesInHierarchy = false;` — Whether to use hierarchical archetype groups for the relation entities Set this to true of you want to do any data calculations with data stored in the relation entities, and them being processed in hierarchy order being a requirements
- L144 _public member_ `TStaticArray<FRoleTraits, static_cast<uint8>(ERelationRole::MAX)> RoleTraits;`
- L146 _public member_ `bool bHierarchical = false;`
- L148 _public member_ `FArchetypeGroupType RegisteredGroupType;`
- L154 _public member_ `TFunction<bool(FMassEntityManager&)> RegisterObserversDelegate;` — Is set, gets called upon type's registration to register appropriate observers. Return value indicates whether the entity manager should register default observes as well.
- L163 _public member_ `TWeakObjectPtr<UClass> RelationEntityCreationObserverClass;` — Processor classes to be instantiated when the relation type gets registered. These will get auto-created only if RegisterObserversDelegate is empty or returns `true` The default values point to generic observer classes that implement the generic policies and behavior. Nulling-out any of these member variables will result in the given functionality not being implemented by the system and makes the user responsible for supplying it.
- L164 _public member_ `TWeakObjectPtr<UClass> RelationEntityDestructionObserverClass;`
- L165 _public member_ `TWeakObjectPtr<UClass> SubjectEntityDestructionObserverClass;`
- L166 _public member_ `TWeakObjectPtr<UClass> ObjectEntityDestructionObserverClass;`
- L168 _public prototype_ `void SetDebugInFix(FString&& InFix);`
- L170 _public prototype_ `FString DebugDescribeRelation(FMassEntityHandle A, FMassEntityHandle B) const;`
- L172 _private member_ `FString DebugInFix;`

#### struct `FMassRelation`  
`struct FMassRelation : public FMassTag`  
_L185-188_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Structs extending FMassRelation represent a "concept" or a relation. These structs are not intended to be stored in Mass. @see FMassRelationFragment for ways of storing relation-specific data

#### struct `FMassRelationFragment`  
`struct FMassRelationFragment : public FMassFragment`  
_L198-228_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Relation fragment base. Every relation entity will get an instance of this type or a type derived from it (as configured via FRelationTypeTraits.RelationFragmentType
- L208 _public member_ `FMassEntityHandle Subject;` — This is the "who" part of the relation. Examples: - the Child in a ChildOf relation - the Character in a HasWeapon relation - the Employee in a WorksFor relation
- L216 _public member_ `FMassEntityHandle Object;` — This is the "what" or "target" part of the relation. Examples: - the Parent in a ChildOf relation - the Weapon in a HasWeapon relation - the Company in a WorksFor relation
- L218 _public function_ `FMassEntityHandle GetRole(const int32 Index) const`
- L223 _public function_ `FMassEntityHandle GetRole(const UE::Mass::Relations::ERelationRole Role) const`

#### struct `FMassRelationMappingFragment`  
`struct FMassRelationMappingFragment : public FMassFragment`  
_L231-234_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`

#### struct `FMassRelationRoleInstanceHandle`  
`struct alignas(8) FMassRelationRoleInstanceHandle`  
_L239-329_
- desc: @todo we might want to promote the internals to FEntityIdentifier and have FMassEntityHandle derive from that.
- L241 _public member_ `static constexpr int32 EntityIndexBits = 30;`
- L242 _public member_ `static constexpr int32 EntityIndexMask = (1 << 30) - 1;`
- L243 _public member_ `static constexpr int32 TypeMask = ~EntityIndexMask;`
- L245 _public prototype_ `FMassRelationRoleInstanceHandle() = default;`
- L247 _public function_ `static FMassRelationRoleInstanceHandle Create(UE::Mass::Relations::ERelationRole Role, const FMassEntityHandle RoleHandle, const FMassEntityHandle RelationEntityHandle)`
- L261 _public function_ `int32 GetRoleEntityIndex() const`
- L265 _public prototype_ `FMassEntityHandle GetRoleEntityHandle(const FMassEntityManager& EntityManager) const;`
- L267 _public function_ `int32 GetRelationEntityIndex() const`
- L271 _public prototype_ `FMassEntityHandle GetRelationEntityHandle(const FMassEntityManager& EntityManager) const;`
- L273 _public function_ `UE::Mass::Relations::ERelationRole GetRole() const`
- L283 _public function_ `FString DebugGetDescription() const`
- L289 _public prototype_ `bool IsValid() const = delete;` — We're unable to tell if a given relation instance handle is valid just by looking at a handle. Only the RelationManager can answer this question. Use IsSet as first filter
- L306 _public function_ `bool operator==(const FMassRelationRoleInstanceHandle& Other) const`
- L312 _private member_ `uint32 RelationEntity = 0;`
- L313 _private member_ `uint32 RoleEntity = 0;`
- L315 _private function_ `void SetRoleEntityIndex(const int32 InIndex)`
- L320 _private function_ `void SetRelationEntityIndex(const int32 InIndex)`
- L325 _private function_ `void SetRole(UE::Mass::Relations::ERelationRole InRole)`

#### struct `FMassRelationRoleInstanceHandle::FMassRelationRoleInstanceHandleFinder`  
`struct FMassRelationRoleInstanceHandleFinder`  
_L291-304_
- L293 _public function_ `FMassRelationRoleInstanceHandleFinder(const FMassEntityHandle EntityHandle) : EntityIndex(EntityHandle.Index)`
- L298 _public function_ `bool operator()(const FMassRelationRoleInstanceHandle& Element) const`
- L303 _public member_ `const int32 EntityIndex;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSENTITY_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mass` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mass` (scope `UE`)
- L21 _namespace_ `namespace Relations` (scope `UE::Mass`)
- L52 _function_ `inline FString LexToString(const ERelationRole Value)` (scope `UE::Mass::Relations`)
- L278 _function_ `friend FString LexToString(const FMassRelationRoleInstanceHandle Handle)`
- L331 _namespace_ `namespace UE`
- L331 _namespace_ `namespace Mass` (scope `UE`)
- L334 _function_ `template<> inline bool IsA<FMassRelation>(const UStruct* Struct)` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassEntitySettings.h` (Public)


#### class `UMassEntitySettings`  
`class UMassEntitySettings : public UMassModuleSettings`  
_L21-119_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig, DisplayName = "Mass Entity")`
- inherits: `UMassModuleSettings`
- desc: Implements the settings for the MassEntity module
- L27 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSettingsChange, const FPropertyChangedEvent& );`
- L29 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnInitialized);`
- L31 _public prototype_ `UMassEntitySettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L33 _public prototype_ `void BuildProcessorListAndPhases();`
- L34 _public prototype_ `void AddToActiveProcessorsList(TSubclassOf<UMassProcessor> ProcessorClass);`
- L36 _public prototype_ `TConstArrayView<FMassProcessingPhaseConfig> GetProcessingPhasesConfig();`
- L37 _public function_ `const FMassProcessingPhaseConfig& GetProcessingPhaseConfig(const EMassProcessingPhase ProcessingPhase) const`
- L43 _public function_ `FOnInitialized& GetOnInitialized()`
- L49 _public function_ `static FOnInitialized& GetOnInitializedEvent()` — `UE_DEPRECATED(5.8, "Use the instance method GetOnInitialized")`
- L56 _public function_ `FOnSettingsChange& GetOnSettingsChange()`
- L61 _public function_ `bool IsInitialized2() const`
- L67 _public function_ `static bool IsInitialized()` — `UE_DEPRECATED(5.8, "Use the instance method IsInitialized2")`
- L76 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L77 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L80 _protected prototype_ `virtual void PostInitProperties() override;`
- L81 _protected prototype_ `virtual void BeginDestroy() override;`
- L83 _protected prototype_ `void OnPostEngineInit();`
- L84 _protected prototype_ `void BuildPhases();`
- L85 _protected prototype_ `void BuildProcessorList();`
- L88 _private prototype_ `void OnModulePackagesUnloaded(TConstArrayView<UPackage*> Packages);`
- L92 _public member_ `uint32 ChunkMemorySize = 128 * 1024;` — `UPROPERTY(EditDefaultsOnly, Category = Mass, config, AdvancedDisplay)`
- L100 _public member_ `FString DumpDependencyGraphFileName;` — `UPROPERTY(EditDefaultsOnly, Category = Mass, Transient)` — The name of the file to dump the processor dependency graph. T The dot file will be put in the project log folder. To generate a svg out of that file, simply run dot executable with following parameters: -Tsvg -O filename.dot
- L104 _public member_ `FMassProcessingPhaseConfig ProcessingPhasesConfig[static_cast<uint8>(EMassProcessingPhase::MAX)];` — `UPROPERTY(EditDefaultsOnly, Category = Mass, config)` — Lets users configure processing phases including the composite processor class to be used as a container for the phases' processors.
- L108 _public member_ `TArray<TObjectPtr<UMassProcessor>> ProcessorCDOs;` — `UPROPERTY(VisibleAnywhere, Category = Mass, Transient, Instanced, EditFixedSize)` — This list contains all the processors available in the given binary (including plugins). The contents are sorted by display name.
- L112 _protected member_ `FOnSettingsChange OnSettingsChange;`
- L115 _protected member_ `bool bInitialized = false;`
- L116 _protected member_ `bool bEngineInitialized = false;`
- L118 _protected member_ `FOnInitialized OnInitializedEvent;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define GET_MASS_CONFIG_VALUE(a) \`
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSettingsChange, const FPropertyChangedEvent& );`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInitialized);`

### `Source/Runtime/MassEntity/Public/MassEntitySubsystem.h` (Public)


#### class `UMassEntitySubsystem`  
`class UMassEntitySubsystem : public UMassSubsystemBase`  
_L18-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: The sole responsibility of this world subsystem class is to host the default instance of FMassEntityManager for a given UWorld. All the gameplay-related use cases of Mass (found in MassGameplay and related plugins) use this by default.
- L23 _private prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L24 _private prototype_ `virtual void PostInitialize() override;`
- L25 _private prototype_ `virtual void Deinitialize() override;`
- L29 _public prototype_ `UMassEntitySubsystem();`
- L32 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L35 _public function_ `const FMassEntityManager& GetEntityManager() const`
- L40 _public function_ `FMassEntityManager& GetMutableEntityManager()`
- L47 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSENTITY_API`

### `Source/Runtime/MassEntity/Public/MassEntityTrace.h` (Public)


#### class `FMassTrace`  
`class FMassTrace : public FNoncopyable`  
_L26-71_
- inherits: `FNoncopyable`
- L45 _public prototype_ `static void SetRecordingTime(double InRecordingTime);` — Set the current world elapsed time (recording time) for subsequent trace events. Should be called once per frame/phase from code that has UWorld access. This allows Mass trace events to be aligned with the RewindDebugger's ElapsedTime-based scrub time, which pauses when the simulation pauses.
- L47 _public prototype_ `static uint64 OutputBeginPhaseWithID(const TCHAR* PhaseName);`
- L48 _public prototype_ `static void OutputBeginPhaseRegion(const TCHAR* PhaseName);`
- L49 _public prototype_ `static void OutputEndPhaseRegion(const TCHAR* PhaseName);`
- L50 _public prototype_ `static void OutputEndPhaseRegion(uint64 PhaseId);`
- L52 _public prototype_ `static void OnPhaseBegin(uint64 PhaseId);`
- L53 _public prototype_ `static void OnPhaseEnd(uint64 PhaseId);`
- L55 _public prototype_ `static uint64 OutputRegisterArchetype(uint64 ArchetypeID, const FMassArchetypeCompositionDescriptor& CompositionDescriptor);`
- L56 _public prototype_ `static uint64 RegisterArchetype(const FMassArchetypeHandle& ArchetypeHandle);`
- L57 _public prototype_ `static uint64 RegisterArchetype(const FMassArchetypeData& Data);`
- L59 _public prototype_ `static void OutputRegisterFragment(const UScriptStruct* Struct);`
- L60 _public prototype_ `static void RegisterFragment(const UScriptStruct* Struct);`
- L62 _public prototype_ `static void EntityCreated(FMassEntityHandle Entity, const FMassArchetypeData& Archetype);`
- L63 _public prototype_ `static void EntityMoved(FMassEntityHandle Entity, const FMassArchetypeData& NewArchetype);`
- L64 _public prototype_ `static void EntityDestroyed(FMassEntityHandle Entity);`
- L65 _public prototype_ `static void EntitiesDestroyed(TConstArrayView<FMassEntityHandle> Entities);`
- L67 _public prototype_ `static void QueryCreated(const FMassEntityQuery* Query);`
- L68 _public prototype_ `static void QueryDestroyed(const FMassEntityQuery* Query);`
- L69 _public prototype_ `static void QueryRegisteredToProcessor(const FMassEntityQuery* Query, TNotNull<const UMassProcessor*> Processor);`
- L70 _public prototype_ `static void QueryArchetypeAdded(const FMassEntityQuery* Query, const FMassArchetypeHandle& Archetype);`

#### struct `FMassTrace::FScopedQueryForEachTrace`  
`struct FScopedQueryForEachTrace`  
_L29-39_
- L31 _public prototype_ `FScopedQueryForEachTrace(const FMassEntityQuery* InQuery);`
- L32 _public prototype_ `~FScopedQueryForEachTrace();`
- L34 _public prototype_ `void ReportArchetype(const FMassArchetypeData& Archetype);`
- L35 _public member_ `const FMassEntityQuery* Query = nullptr;`
- L36 _public member_ `int32 ArchetypeCount = 0;`
- L37 _public member_ `int32 ChunkCount = 0;`
- L38 _public member_ `int32 EntityCount = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_MASS_TRACE_ENABLED (UE_TRACE_ENABLED && WITH_MASSENTITY_DEBUG && !IS_PROGRAM && !UE_BUILD_SHIPPING)`
- L73 _macro_ `#define UE_TRACE_MASS_ARCHETYPE_CREATED(Archetype) \`
- L76 _macro_ `#define UE_TRACE_MASS_ENTITY_CREATED(Entity, Archetype) \`
- L79 _macro_ `#define UE_TRACE_MASS_ENTITIES_CREATED(EntityHandles, Archetype) \`
- L85 _macro_ `#define UE_TRACE_MASS_ENTITY_MOVED(Entity, NewArchetype) \`
- L88 _macro_ `#define UE_TRACE_MASS_ENTITIES_MOVED(EntityHandles, NewArchetype) \`
- L94 _macro_ `#define UE_TRACE_MASS_ENTITY_DESTROYED(Entity) \`
- L97 _macro_ `#define UE_TRACE_MASS_ENTITIES_DESTROYED(EntityHandles) \`
- L102 _macro_ `#define UE_TRACE_MASS_PHASE_BEGIN(PhaseID) \`
- L105 _macro_ `#define UE_TRACE_MASS_PHASE_END(PhaseID) \`
- L108 _macro_ `#define UE_TRACE_MASS_QUERY_CREATED() \`
- L111 _macro_ `#define UE_TRACE_MASS_QUERY_DESTROYED() \`
- L114 _macro_ `#define UE_TRACE_MASS_QUERY_REGISTERED_TO_PROCESSOR(Processor) \`
- L117 _macro_ `#define UE_TRACE_MASS_QUERY_ARCHETYPE_ADDED(Archetype) \`
- L120 _macro_ `#define UE_TRACE_MASS_SET_RECORDING_TIME(RecordingTime) \`
- L123 _macro_ `#define UE_TRACE_SCOPED_MASS_QUERY_FOR_EACH() \`
- L126 _macro_ `#define UE_TRACE_SCOPED_MASS_QUERY_FOR_EACH_REPORT_ARCHETYPE(Archetype) \`
- L131 _macro_ `#define UE_TRACE_MASS_ARCHETYPE_CREATED(PhaseID)`
- L132 _macro_ `#define UE_TRACE_MASS_ENTITY_CREATED(Entity, Archetype)`
- L133 _macro_ `#define UE_TRACE_MASS_ENTITIES_CREATED(EntityHandles, Archetype)`
- L134 _macro_ `#define UE_TRACE_MASS_ENTITY_MOVED(Entity, NewArchetype)`
- L135 _macro_ `#define UE_TRACE_MASS_ENTITIES_MOVED(EntityHandles, NewArchetype)`
- L136 _macro_ `#define UE_TRACE_MASS_ENTITY_DESTROYED(Entity)`
- L137 _macro_ `#define UE_TRACE_MASS_ENTITIES_DESTROYED(EntityHandles)`
- L138 _macro_ `#define UE_TRACE_MASS_PHASE_BEGIN(PhaseID)`
- L139 _macro_ `#define UE_TRACE_MASS_PHASE_END(PhaseID)`
- L140 _macro_ `#define UE_TRACE_MASS_QUERY_CREATED()`
- L141 _macro_ `#define UE_TRACE_MASS_QUERY_DESTROYED()`
- L142 _macro_ `#define UE_TRACE_MASS_QUERY_REGISTERED_TO_PROCESSOR(Processor)`
- L143 _macro_ `#define UE_TRACE_MASS_QUERY_ARCHETYPE_ADDED(Archetype)`
- L144 _macro_ `#define UE_TRACE_MASS_SET_RECORDING_TIME(RecordingTime)`
- L145 _macro_ `#define UE_TRACE_SCOPED_MASS_QUERY_FOR_EACH()`
- L146 _macro_ `#define UE_TRACE_SCOPED_MASS_QUERY_FOR_EACH_REPORT_ARCHETYPE(Archetype)`

### `Source/Runtime/MassEntity/Public/MassEntityTypes.h` (Public)


#### struct `UE::Mass::FExecutionLimiter`  
`struct FExecutionLimiter`  
_L43-64_
- desc: FExecutionLimiter is used to limit the execution of a query to a set entity count.
- L48 _public function_ `explicit FExecutionLimiter(int32 InEntityLimit) : EntityLimit(InEntityLimit) , ChunkIndex(INDEX_NONE) , ArchetypeIndex(INDEX_NONE) , MaxChunkIndex(INDEX_NONE) , EntityCountRemaining(0)`
- L57 _public member_ `int32 EntityLimit;`
- L60 _private member_ `int32 ChunkIndex;`
- L61 _private member_ `int32 ArchetypeIndex;`
- L62 _private member_ `int32 MaxChunkIndex;`
- L63 _private member_ `int32 EntityCountRemaining;`

#### enum `UE::Mass::EIncludeSparseElements`  
`enum class EIncludeSparseElements : uint8`  
_L66-70_
- L68 _public enumerator_ `No`
- L69 _public enumerator_ `Yes`

#### struct `FMassArchetypeCompositionDescriptor`  
`struct FMassArchetypeCompositionDescriptor`  
_L76-325_
- desc: The type summarily describing a composition of an entity or an archetype. It contains information on both the fragments and tags
- L78 _public prototype_ `FMassArchetypeCompositionDescriptor() = default;`
- L79 _public function_ `FMassArchetypeCompositionDescriptor(const FMassFragmentBitSet& InFragments, const FMassTagBitSet& InTags, const FMassChunkFragmentBitSet& InChunkFragments, const FMassSharedFragmentBitSet& InSharedFragments, const FMassConstSharedFragmentBitSet& InConstSharedFragments) : Fragments(InFragments) , Tags(InTags) , ChunkFragments(InChunkFragments) , SharedFragments(InSharedFragments) , ConstSharedFragments(InConstSharedFragments)`
- L93 _public function_ `FMassArchetypeCompositionDescriptor(TConstArrayView<const UScriptStruct*> InFragments, const FMassTagBitSet& InTags, const FMassChunkFragmentBitSet& InChunkFragments, const FMassSharedFragmentBitSet& InSharedFragments, const FMassConstSharedFragmentBitSet& InConstSharedFragments) : FMassArchetypeCompositionDescriptor(FMassFragmentBitSet(InFragments), InTags, InChunkFragments, InSharedFragments, InConstSharedFragments)`
- L102 _public function_ `FMassArchetypeCompositionDescriptor(TConstArrayView<FInstancedStruct> InFragmentInstances, const FMassTagBitSet& InTags, const FMassChunkFragmentBitSet& InChunkFragments, const FMassSharedFragmentBitSet& InSharedFragments, const FMassConstSharedFragmentBitSet& InConstSharedFragments) : FMassArchetypeCompositionDescriptor(FMassFragmentBitSet(InFragmentInstances), InTags, InChunkFragments, InSharedFragments, InConstSharedFragments)`
- L111 _public function_ `FMassArchetypeCompositionDescriptor(FMassFragmentBitSet&& InFragments, FMassTagBitSet&& InTags, FMassChunkFragmentBitSet&& InChunkFragments, FMassSharedFragmentBitSet&& InSharedFragments, FMassConstSharedFragmentBitSet&& InConstSharedFragments) : Fragments(MoveTemp(InFragments)) , Tags(MoveTemp(InTags)) , ChunkFragments(MoveTemp(InChunkFragments)) , SharedFragments(MoveTemp(InSharedFragments)) , ConstSharedFragments(MoveTemp(InConstSharedFragments))`
- L125 _public function_ `FMassArchetypeCompositionDescriptor(FMassElementBitSet&& InElements) : ElementsBitSet(MoveTemp(InElements))`
- L133 _public function_ `FMassArchetypeCompositionDescriptor(const FMassElementBitSet& InElements) : ElementsBitSet(InElements)` — Constructor deliberately not marked as explicit to support near-future change where we get rid of FMassArchetypeCompositionDescriptor since it's just a wrapper for FMassElementBitSet now.
- L137 _public prototype_ `explicit FMassArchetypeCompositionDescriptor(const FMassArchetypeHandle& ArchetypeHandle);`
- L139 _public function_ `void Reset()`
- L147 _public function_ `bool IsEquivalent(const FMassArchetypeCompositionDescriptor& OtherDescriptor) const` — Compares contents of two FMassArchetypeCompositionDescriptor instances, ignoring the trailing empty bits in the bitsets
- L155 _public function_ `bool IsIdentical(const FMassArchetypeCompositionDescriptor& OtherDescriptor) const` — Checks whether contents of two FMassArchetypeCompositionDescriptor instances are identical.
- L160 _public function_ `bool IsEmpty() const`
- L165 _public function_ `bool HasAll(const FMassArchetypeCompositionDescriptor& OtherDescriptor) const`
- L170 _public function_ `void Append(const FMassArchetypeCompositionDescriptor& OtherDescriptor)`
- L175 _public function_ `void Remove(const FMassArchetypeCompositionDescriptor& OtherDescriptor)`
- L184 _public function_ `FMassArchetypeCompositionDescriptor CalculateDifference(const FMassArchetypeCompositionDescriptor& OtherDescriptor) const` — Finds all the elements contained in `this` while missing in `OtherDescriptor` and returns the data as a FMassArchetypeCompositionDescriptor instance
- L189 _public function_ `uint32 CalculateHash() const`
- L195 _public function_ `static uint32 CalculateHash(const FMassFragmentBitSet& InFragments, const FMassTagBitSet& InTags , const FMassChunkFragmentBitSet& InChunkFragments, const FMassSharedFragmentBitSet& InSharedFragmentBitSet , const FMassConstSharedFragmentBitSet& InConstSharedFragmentBitSet)` — `UE_DEPRECATED(5.8, "This function is deprecated. Use FMassArchetypeCompositionDescriptor::CalculateHash() instead")`
- L202 _public prototype_ `int32 CountStoredTypes() const;`
- L204 _public prototype_ `void DebugOutputDescription(FOutputDevice& Ar) const;`
- L207 _public prototype_ `template<typename T> auto GetContainer() const;`
- L211 _public function_ `auto& GetContainer()` — `UE_DEPRECATED(5.8, "Mutable GetContainer is deprecated")`
- L217 _public prototype_ `template<typename T> bool Contains() const;`
- L219 _public prototype_ `bool Contains(TNotNull<const UScriptStruct*> ElementType) const;`
- L222 _public prototype_ `template<typename T> void Add();`
- L224 _public prototype_ `void Add(TNotNull<const UScriptStruct*> ElementType);`
- L227 _public prototype_ `template<typename T> void Remove();`
- L229 _public prototype_ `void Remove(TNotNull<const UScriptStruct*> ElementType);`
- L231 _public prototype_ `FMassFragmentBitSet DebugGetFragments() const;`
- L232 _public prototype_ `FMassTagBitSet DebugGetTags() const;`
- L233 _public prototype_ `FMassChunkFragmentBitSet DebugGetChunkFragments() const;`
- L234 _public prototype_ `FMassSharedFragmentBitSet DebugGetSharedFragments() const;`
- L235 _public prototype_ `FMassConstSharedFragmentBitSet DebugGetConstSharedFragments() const;`
- L238 _public prototype_ `FMassFragmentBitSet GetFragments() const;` — `UE_DEPRECATED(5.8, "Getting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L240 _public prototype_ `FMassTagBitSet GetTags() const;` — `UE_DEPRECATED(5.8, "Getting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L242 _public prototype_ `FMassChunkFragmentBitSet GetChunkFragments() const;` — `UE_DEPRECATED(5.8, "Getting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L244 _public prototype_ `FMassSharedFragmentBitSet GetSharedFragments() const;` — `UE_DEPRECATED(5.8, "Getting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L246 _public prototype_ `FMassConstSharedFragmentBitSet GetConstSharedFragments() const;` — `UE_DEPRECATED(5.8, "Getting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L253 _public prototype_ `void SetFragments(const FMassFragmentBitSet& InBitSet);` — `UE_DEPRECATED(5.8, "Setting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")` — Functions setting specific type of bits. These functions are a lot slower now. Consider changing your code to work directly on FMassElementBitSet
- L255 _public prototype_ `void SetTags(const FMassTagBitSet& InBitSet);` — `UE_DEPRECATED(5.8, "Setting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L257 _public prototype_ `void SetChunkFragments(const FMassChunkFragmentBitSet& InBitSet);` — `UE_DEPRECATED(5.8, "Setting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L259 _public prototype_ `void SetSharedFragments(const FMassSharedFragmentBitSet& InBitSet);` — `UE_DEPRECATED(5.8, "Setting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L261 _public prototype_ `void SetConstSharedFragments(const FMassConstSharedFragmentBitSet& InBitSet);` — `UE_DEPRECATED(5.8, "Setting a subset of composition's bitsets is slow now. Consider refactoring your code to work directly on FMassElementBitSet")`
- L263 _public prototype_ `void SetAllSharedElements(const FMassElementBitSet& InBitSet);`
- L265 _public function_ `FMassElementBitSet GetAllSharedFragments() const`
- L270 _public function_ `const FMassElementBitSet& GetElementsBitSet() const`
- L275 _public function_ `FMassElementBitSet& GetElementsBitSet()`
- L281 _public member_ `FMassFragmentBitSet Fragments;` — `UE_DEPRECATED(5.7, "Direct access to FMassArchetypeCompositionDescriptor's bitsets is deprecated. Use any of the newly added getters instead.")`
- L284 _public member_ `FMassTagBitSet Tags;` — `UE_DEPRECATED(5.7, "Direct access to FMassArchetypeCompositionDescriptor's bitsets is deprecated. Use any of the newly added getters instead.")`
- L287 _public member_ `FMassChunkFragmentBitSet ChunkFragments;` — `UE_DEPRECATED(5.7, "Direct access to FMassArchetypeCompositionDescriptor's bitsets is deprecated. Use any of the newly added getters instead.")`
- L290 _public member_ `FMassSharedFragmentBitSet SharedFragments;` — `UE_DEPRECATED(5.7, "Direct access to FMassArchetypeCompositionDescriptor's bitsets is deprecated. Use any of the newly added getters instead.")`
- L293 _public member_ `FMassConstSharedFragmentBitSet ConstSharedFragments;` — `UE_DEPRECATED(5.7, "Direct access to FMassArchetypeCompositionDescriptor's bitsets is deprecated. Use any of the newly added getters instead.")`
- L296 _protected member_ `FMassElementBitSet ElementsBitSet;`
- L300 _public function_ `template<typename TBitSet> TBitSet Get() const`
- L305 _public function_ `void SetElementsBitSet()`
- L315 _public function_ `template<typename TElementType> bool HasAny() const`
- L321 _public function_ `template<typename TElementType> bool HasAll() const`
- L1013 _function_ `template<typename T> auto FMassArchetypeCompositionDescriptor::GetContainer() const`
- L1042 _function_ `template<typename T> bool FMassArchetypeCompositionDescriptor::Contains() const`
- L1047 _function_ `inline bool FMassArchetypeCompositionDescriptor::Contains(TNotNull<const UScriptStruct*> ElementType) const`
- L1053 _function_ `template<typename T> void FMassArchetypeCompositionDescriptor::Add()`
- L1058 _function_ `inline void FMassArchetypeCompositionDescriptor::Add(TNotNull<const UScriptStruct*> ElementType)`
- L1064 _function_ `template<typename T> void FMassArchetypeCompositionDescriptor::Remove()`
- L1069 _function_ `inline void FMassArchetypeCompositionDescriptor::Remove(TNotNull<const UScriptStruct*> ElementType)`
- L1074 _function_ `inline FMassFragmentBitSet FMassArchetypeCompositionDescriptor::DebugGetFragments() const`
- L1079 _function_ `inline FMassTagBitSet FMassArchetypeCompositionDescriptor::DebugGetTags() const`
- L1084 _function_ `inline FMassChunkFragmentBitSet FMassArchetypeCompositionDescriptor::DebugGetChunkFragments() const`
- L1089 _function_ `inline FMassSharedFragmentBitSet FMassArchetypeCompositionDescriptor::DebugGetSharedFragments() const`
- L1094 _function_ `inline FMassConstSharedFragmentBitSet FMassArchetypeCompositionDescriptor::DebugGetConstSharedFragments() const`
- L1099 _function_ `inline FMassFragmentBitSet FMassArchetypeCompositionDescriptor::GetFragments() const`
- L1104 _function_ `inline FMassTagBitSet FMassArchetypeCompositionDescriptor::GetTags() const`
- L1109 _function_ `inline FMassChunkFragmentBitSet FMassArchetypeCompositionDescriptor::GetChunkFragments() const`
- L1114 _function_ `inline FMassSharedFragmentBitSet FMassArchetypeCompositionDescriptor::GetSharedFragments() const`
- L1119 _function_ `inline FMassConstSharedFragmentBitSet FMassArchetypeCompositionDescriptor::GetConstSharedFragments() const`
- L1124 _function_ `inline void FMassArchetypeCompositionDescriptor::SetFragments(const FMassFragmentBitSet& InBitSet)`
- L1129 _function_ `inline void FMassArchetypeCompositionDescriptor::SetTags(const FMassTagBitSet& InBitSet)`
- L1134 _function_ `inline void FMassArchetypeCompositionDescriptor::SetChunkFragments(const FMassChunkFragmentBitSet& InBitSet)`
- L1139 _function_ `inline void FMassArchetypeCompositionDescriptor::SetSharedFragments(const FMassSharedFragmentBitSet& InBitSet)`
- L1144 _function_ `inline void FMassArchetypeCompositionDescriptor::SetConstSharedFragments(const FMassConstSharedFragmentBitSet& InBitSet)`
- L1149 _function_ `inline void FMassArchetypeCompositionDescriptor::SetAllSharedElements(const FMassElementBitSet& InBitSet)`

#### struct `FMassArchetypeSharedFragmentValues`  
`struct FMassArchetypeSharedFragmentValues`  
_L339-681_
- desc: Wrapper for const and non-const shared fragment containers that tracks which struct types it holds (via a FMassSharedFragmentBitSet). Note that having multiple instances of a given struct type is not supported and Add* functions will fetch the previously added fragment instead of adding a new one. Shared fragment TYPES contribute to archetype composition (two archetypes with different shared fragment type sets are distinct). Shared fragment VALUES are stored per-chunk — entities within the same archetype but with different shared values are placed in separate chunks. Chunk selection uses IsEquivalent() which compares by pointer identity (hash of backing struct memory addresses). When shared fragments are obtained via GetOrCreateConstSharedFragment/GetOrCreateSharedFragment, identical values are deduplicated (same pointer), so IsEquivalent effectively acts as value comparison in the expected usage path.
- L341 _public prototype_ `FMassArchetypeSharedFragmentValues() = default;`
- L343 _public function_ `FMassArchetypeSharedFragmentValues(const FMassArchetypeSharedFragmentValues& Other) : HashCache(Other.HashCache) , bSorted(Other.bSorted) , StoredElementsBitSet(Other.StoredElementsBitSet) , ConstSharedFragments(Other.ConstSharedFragments) , SharedFragments(Other.SharedFragments)`
- L352 _public function_ `FMassArchetypeSharedFragmentValues(FMassArchetypeSharedFragmentValues&& Other) : HashCache(Other.HashCache) , bSorted(Other.bSorted) , StoredElementsBitSet(MoveTemp(Other.StoredElementsBitSet)) , ConstSharedFragments(MoveTemp(Other.ConstSharedFragments)) , SharedFragments(MoveTemp(Other.SharedFragments))`
- L361 _public function_ `FMassArchetypeSharedFragmentValues& operator=(const FMassArchetypeSharedFragmentValues& Other)`
- L376 _public function_ `FMassArchetypeSharedFragmentValues& operator=(FMassArchetypeSharedFragmentValues&& Other) noexcept`
- L396 _public prototype_ `static FMassArchetypeSharedFragmentValues CreateCombined(const FMassArchetypeSharedFragmentValues& Original , const FMassElementBitSet& NewSharedElementComposition, const FMassArchetypeSharedFragmentValues* SharedFragmentValuesModification);` — @param SharedFragmentValuesModification if provided will be used to override or add values already existing in Original. Needs to be consistent with NewSharedElementComposition, meaning, not add anything that's not already in the bitset. Also, if NewSharedElementComposition contains elements not in Original, then SharedFragmentValuesModification has to provide a value for it.
- L402 _public function_ `bool DoesMatchComposition(const FMassArchetypeCompositionDescriptor& InDescriptor) const` — @return whether the stored shared fragment values exactly match shared fragment types indicated by InDescriptor
- L407 _public function_ `bool DoesMatchComposition(const FMassElementBitSet& CompositionBitSet) const`
- L412 _public function_ `inline bool IsEquivalent(const FMassArchetypeSharedFragmentValues& OtherSharedFragmentValues) const`
- L423 _public prototype_ `bool HasSameValues(const FMassArchetypeSharedFragmentValues& Other) const;` — Compares contents of `this` and the Other, and allows different order of elements in both containers. Note that the function ignores "nulls", i.e. empty FConstSharedStruct and FSharedStruct instances. The function does care however about matching "mode", meaning ConstSharedFragments and SharedFragments arrays are compared independently.
- L425 _public function_ `inline bool ContainsType(const UScriptStruct* FragmentType) const`
- L432 _public function_ `template<typename T> inline bool ContainsType() const`
- L448 _public function_ `void Add(const FConstSharedStruct& Fragment)` — Adds Fragment to the collection. Method will ensure if a fragment of the given FMassConstSharedFragment subclass has already been added.
- L459 _public prototype_ `FConstSharedStruct Add_GetRef(const FConstSharedStruct& Fragment);` — Adds Fragment to the collection. Method will ensure if a fragment of the given FMassConstSharedFragment subclass has already been added. In that case the method will return the previously added instance if the given type has been added as a CONST shared fragment and if not it will return an empty FConstSharedStruct.
- L462 _public function_ `FConstSharedStruct AddConstSharedFragment(const FConstSharedStruct& Fragment)` — `UE_DEPRECATED(5.6, "Use Add or Add_GetRef instead depending on whether you need the return value.")`
- L471 _public function_ `void Add(const FSharedStruct& Fragment)` — Adds Fragment to the collection. Method will ensure if a fragment of the given FMassSharedFragment subclass has already been added.
- L482 _public prototype_ `FSharedStruct Add_GetRef(const FSharedStruct& Fragment);` — Adds Fragment to the collection. Method will ensure if a fragment of the given FMassSharedFragment subclass has already been added. In that case the method will return the previously added instance if the given type has been added as a NON-CONST shared fragment and if not it will return an empty FSharedStruct.
- L485 _public function_ `FSharedStruct AddSharedFragment(const FSharedStruct& Fragment)` — `UE_DEPRECATED(5.6, "Use Add or Add_GetRef instead depending on whether you need the return value.")`
- L497 _public function_ `template<typename TSharedStruct> void ReplaceSharedFragments(TArrayView<TSharedStruct> Fragments)` — Finds instances of fragment types given by Fragments and replaces their values with contents of respective element of Fragments. Note that it's callers responsibility to ensure every fragment type in Fragments already has an instance in this FMassArchetypeSharedFragmentValues instance. Failing that assumption will result in ensure failure.
- L527 _public prototype_ `int32 Append(const FMassArchetypeSharedFragmentValues& Other);` — Appends contents of Other to `this` instance. All common fragments will get overridden with values in Other. Note that changing a fragments "role" (being const or non-const) is not supported and the function will fail an ensure when that is attempted. @return number of fragments added or changed
- L529 _public prototype_ `int32 Remove(const FMassElementBitSet& ElementBitSet);`
- L535 _public function_ `int32 Remove(const FMassSharedFragmentBitSet& SharedFragmentToRemoveBitSet)` — Note that the function removes the shared fragments by type @return number of fragments types removed
- L544 _public function_ `int32 Remove(const FMassConstSharedFragmentBitSet& ConstSharedFragmentToRemoveBitSet)` — Note that the function removes the const shared fragments by type @return number of fragments types removed
- L553 _public function_ `int32 Remove(const FMassArchetypeCompositionDescriptor& InDescriptor)` — Remove all the shared and const shared fragments indicated by InDescriptor @return number of fragments types removed
- L558 _public function_ `int32 Remove(const FMassArchetypeSharedFragmentValues& Other)`
- L563 _public function_ `inline const TArray<FConstSharedStruct>& GetConstSharedFragments() const`
- L568 _public function_ `inline TArray<FSharedStruct>& GetMutableSharedFragments()`
- L575 _public prototype_ `template<typename TSharedStruct> TArray<TSharedStruct>& GetMutableFragmentsContainer();` — depending on TSharedStruct returns Shared or ConstShared fragment container
- L577 _public function_ `inline const TArray<FSharedStruct>& GetSharedFragments() const`
- L582 _public function_ `FConstSharedStruct GetConstSharedFragmentStruct(const UScriptStruct* StructType) const`
- L588 _public function_ `FSharedStruct GetSharedFragmentStruct(const UScriptStruct* StructType)`
- L594 _public function_ `FConstSharedStruct GetSharedFragmentStruct(const UScriptStruct* StructType) const`
- L600 _public function_ `const FMassElementBitSet& GetBitSet() const`
- L606 _public function_ `FMassSharedFragmentBitSet GetSharedFragmentBitSet() const` — `UE_DEPRECATED(5.8, "This function is deprecated. Use GetBitSet instead")`
- L612 _public function_ `FMassConstSharedFragmentBitSet GetConstSharedFragmentBitSet() const` — `UE_DEPRECATED(5.8, "This function is deprecated. Use GetBitSet instead")`
- L617 _public function_ `inline void DirtyHashCache()`
- L626 _public function_ `inline uint32 CacheHash() const` — Returns the cached-or-calculated hash
- L648 _public prototype_ `uint32 CalculateHash() const;`
- L649 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L651 _public function_ `void Sort()`
- L661 _public prototype_ `bool IsSorted() const;`
- L663 _public prototype_ `bool IsEmpty() const;`
- L665 _public prototype_ `void Reset();`
- L668 _protected member_ `mutable uint32 HashCache = UINT32_MAX;`
- L673 _protected member_ `mutable bool bSorted = true;` — We consider empty FMassArchetypeSharedFragmentValues a sorted container.Same goes for a container containing a single element, @see DirtyHashCache
- L675 _protected member_ `FMassElementBitSet StoredElementsBitSet;`
- L676 _protected member_ `TArray<FConstSharedStruct> ConstSharedFragments;`
- L677 _protected member_ `TArray<FSharedStruct> SharedFragments;`
- L680 _private member_ `mutable FTransactionallySafeRWLock HashLock;`
- L1155 _function_ `inline SIZE_T FMassArchetypeSharedFragmentValues::GetAllocatedSize() const`
- L1162 _function_ `inline bool FMassArchetypeSharedFragmentValues::IsSorted() const`
- L1167 _function_ `inline bool FMassArchetypeSharedFragmentValues::IsEmpty() const`
- L1172 _function_ `inline void FMassArchetypeSharedFragmentValues::Reset()`
- L1184 _function_ `template<> inline TArray<FSharedStruct>& FMassArchetypeSharedFragmentValues::GetMutableFragmentsContainer<FSharedStruct>()`
- L1190 _function_ `template<> inline TArray<FConstSharedStruct>& FMassArchetypeSharedFragmentValues::GetMutableFragmentsContainer<FConstSharedStruct>()`

#### enum `EMassObservedOperation`  
`enum class EMassObservedOperation : uint8`  
_L687-703_
- reflection: `UENUM()`
- desc: The enum is used to categorize any operation an entity can be a subject to.
- L689 _public enumerator_ `AddElement` — when an element (a fragment, tag...) is added to an existing entity
- L690 _public enumerator_ `RemoveElement` — when an element (a fragment, tag...) is removed from an existing entity
- L691 _public enumerator_ `DestroyEntity` — when an entity is destroyed, which is a special case of RemoveElement, because the entity gets all of its elements removed
- L692 _public enumerator_ `CreateEntity` — when an entity is created, which is a special case of AddElement, because the entity gets all of its elements added
- L698 _public enumerator_ `MAX`
- L701 _public enumerator_ `Add UMETA(Deprecated, DisplayName="DEPRECATED_Add")` — the following values are deprecated. Use one of the values above
- L702 _public enumerator_ `Remove UMETA(Deprecated, DisplayName="DEPRECATED_Remove")`

#### enum `EMassObservedOperationFlags`  
`enum class EMassObservedOperationFlags : uint8`  
_L705-716_
- L707 _public enumerator_ `None = 0`
- L708 _public enumerator_ `AddElement = 1 << static_cast<uint8>(EMassObservedOperation::AddElement)`
- L709 _public enumerator_ `RemoveElement = 1 << static_cast<uint8>(EMassObservedOperation::RemoveElement)`
- L710 _public enumerator_ `CreateEntity = 1 << static_cast<uint8>(EMassObservedOperation::CreateEntity)`
- L711 _public enumerator_ `DestroyEntity = 1 << static_cast<uint8>(EMassObservedOperation::DestroyEntity)`
- L713 _public enumerator_ `Add = AddElement | CreateEntity`
- L714 _public enumerator_ `Remove = RemoveElement | DestroyEntity`
- L715 _public enumerator_ `All = Add | Remove`

#### enum `EMassExecutionContextType`  
`enum class EMassExecutionContextType : uint8`  
_L720-725_
- L722 _public enumerator_ `Local`
- L723 _public enumerator_ `Processor`
- L724 _public enumerator_ `MAX`

#### struct `FMassGenericPayloadView`  
`struct FMassGenericPayloadView`  
_L731-763_
- desc: Note that this is a view and is valid only as long as the source data is valid. Used when flushing mass commands to wrap different kinds of data into a uniform package so that it can be passed over to a common interface.
- L733 _public prototype_ `FMassGenericPayloadView() = default;`
- L734 _public function_ `FMassGenericPayloadView(TArray<FStructArrayView>& SourceData) : Content(SourceData)`
- L737 _public function_ `FMassGenericPayloadView(TArrayView<FStructArrayView> SourceData) : Content(SourceData)`
- L741 _public function_ `int32 Num() const`
- L746 _public function_ `void Reset()`
- L751 _public function_ `inline void Swap(const int32 A, const int32 B)`
- L760 _public prototype_ `void SwapElementsToEnd(int32 StartIndex, int32 NumToMove);` — Moves NumToMove elements to the back of the viewed collection.
- L762 _public member_ `TArrayView<FStructArrayView> Content;`

#### struct `FMassGenericPayloadViewSlice`  
`struct FMassGenericPayloadViewSlice`  
_L769-797_
- desc: Used to indicate a specific slice of a preexisting FMassGenericPayloadView, it's essentially an access pattern Note: accessing content generates copies of FStructArrayViews stored (still cheap, those are just views).
- L771 _public prototype_ `FMassGenericPayloadViewSlice() = default;`
- L772 _public function_ `FMassGenericPayloadViewSlice(const FMassGenericPayloadView& InSource, const int32 InStartIndex, const int32 InCount) : Source(InSource), StartIndex(InStartIndex), Count(InCount)`
- L777 _public function_ `FStructArrayView operator[](const int32 Index) const`
- L783 _public function_ `int32 Num() const` — @return the number of "layers" (i.e. number of original arrays) this payload has been built from
- L788 _public function_ `bool IsEmpty() const`
- L794 _private member_ `FMassGenericPayloadView Source;`
- L795 _private member_ `const int32 StartIndex = 0;`
- L796 _private member_ `const int32 Count = 0;`

#### struct `UE::Mass::TMultiTypeList`  
`template<typename T, typename... TOthers> struct TMultiTypeList : TMultiTypeList<TOthers...>`  
_L806-821_
- inherits: `TMultiTypeList<TOthers...>`
- desc: A statically-typed list of related types. Used mainly to differentiate type collections at compile-type as well as efficiently produce TStructTypeBitSet representing given collection.
- L808 _public typedef_ `using Super = TMultiTypeList<TOthers...>;`
- L809 _public typedef_ `using FType = std::remove_const_t<typename TRemoveReference<T>::Type>;`
- L816 _public function_ `template<typename TBitSetType> constexpr static void PopulateBitSet(TBitSetType& OutBitSet)`

#### enum `UE::Mass::TMultiTypeList::(anonymous)`  
``  
_L811-813_

#### struct `UE::Mass::TMultiTypeList`  
`template<typename T> struct TMultiTypeList<T>`  
_L825-838_
- desc: Single-type specialization of TMultiTypeList.
- L808 _public typedef_ `using Super = TMultiTypeList<TOthers...>;`
- L809 _public typedef_ `using FType = std::remove_const_t<typename TRemoveReference<T>::Type>;`
- L816 _public function_ `template<typename TBitSetType> constexpr static void PopulateBitSet(TBitSetType& OutBitSet)`

#### enum `UE::Mass::TMultiTypeList::(anonymous)`  
``  
_L829-831_

#### struct `UE::Mass::TMultiArray`  
`template<typename T, typename... TOthers> struct TMultiArray : TMultiArray<TOthers...>`  
_L846-920_
- inherits: `TMultiArray<TOthers...>`
- desc: The type hosts a statically-typed collection of TArrays, where each TArray is strongly-typed (i.e. it contains instances of given structs rather than structs wrapped up in FInstancedStruct). This type lets us do batched fragment values setting by simply copying data rather than setting per-instance.
- L848 _public typedef_ `using FType = std::remove_const_t<typename TRemoveReference<T>::Type>;`
- L849 _public typedef_ `using Super = TMultiArray<TOthers...>;`
- L856 _public function_ `SIZE_T GetAllocatedSize() const`
- L861 _public function_ `int GetNumArrays() const`
- L868 _public function_ `template<typename... TInstances> void Add(const FType& Item, TInstances... Rest)` — TInstances might be different from TOthers if move semantics were used
- L876 _public function_ `template<typename... TInstances> void Add(FType&& Item, TInstances... Rest)` — TInstances might be different from TOthers if move semantics were used
- L883 _public function_ `template<typename AllocatorType = FDefaultAllocator> void GetAsGenericMultiArray(TArray<FStructArrayView, AllocatorType>& A)`
- L892 _public function_ `template<typename AllocatorType = FDefaultAllocator> void GetAsNonTagGenericMultiArray(TArray<FStructArrayView, AllocatorType>& A)` — Like GetAsGenericMultiArray but skips FMassTag-derived types (including FMassSparseTag). Tags have zero-size storage and must be excluded from payload arrays passed to BatchSetFragmentValues.
- L901 _public function_ `void GatherAffectedFragments(FMassFragmentBitSet& OutBitSet) const`
- L908 _public function_ `void GetheredAffectedFragments(FMassFragmentBitSet& OutBitSet) const` — `UE_DEPRECATED(5.8, "Function name's spelling has been fixed. Use GatherAffectedFragments now")`
- L913 _public function_ `void Reset()`
- L919 _public member_ `TArray<FType> FragmentInstances;`
- L939 _public function_ `void Add(const FType& Item)`
- L944 _public function_ `void Add(FType&& Item)`

#### enum `UE::Mass::TMultiArray::(anonymous)`  
``  
_L852-854_

#### struct `UE::Mass::TMultiArray`  
`template<typename T> struct TMultiArray<T>`  
_L924-982_
- desc: TMultiArray single-type specialization
- L848 _public typedef_ `using FType = std::remove_const_t<typename TRemoveReference<T>::Type>;`
- L849 _public typedef_ `using Super = TMultiArray<TOthers...>;`
- L856 _public function_ `SIZE_T GetAllocatedSize() const`
- L861 _public function_ `int GetNumArrays() const`
- L868 _public function_ `template<typename... TInstances> void Add(const FType& Item, TInstances... Rest)` — TInstances might be different from TOthers if move semantics were used
- L876 _public function_ `template<typename... TInstances> void Add(FType&& Item, TInstances... Rest)` — TInstances might be different from TOthers if move semantics were used
- L883 _public function_ `template<typename AllocatorType = FDefaultAllocator> void GetAsGenericMultiArray(TArray<FStructArrayView, AllocatorType>& A)`
- L892 _public function_ `template<typename AllocatorType = FDefaultAllocator> void GetAsNonTagGenericMultiArray(TArray<FStructArrayView, AllocatorType>& A)` — Like GetAsGenericMultiArray but skips FMassTag-derived types (including FMassSparseTag). Tags have zero-size storage and must be excluded from payload arrays passed to BatchSetFragmentValues.
- L901 _public function_ `void GatherAffectedFragments(FMassFragmentBitSet& OutBitSet) const`
- L908 _public function_ `void GetheredAffectedFragments(FMassFragmentBitSet& OutBitSet) const` — `UE_DEPRECATED(5.8, "Function name's spelling has been fixed. Use GatherAffectedFragments now")`
- L913 _public function_ `void Reset()`
- L919 _public member_ `TArray<FType> FragmentInstances;`
- L939 _public function_ `void Add(const FType& Item)`
- L944 _public function_ `void Add(FType&& Item)`

#### enum `UE::Mass::TMultiArray::(anonymous)`  
`enum`  
_L927-927_

#### struct `FMassArchetypeCreationParams`  
`struct FMassArchetypeCreationParams`  
_L987-1006_
- L989 _public prototype_ `FMassArchetypeCreationParams() = default;`
- L990 _public function_ `explicit FMassArchetypeCreationParams(const FName DebugName) : DebugName(DebugName)`
- L995 _public prototype_ `explicit FMassArchetypeCreationParams(const struct FMassArchetypeData& Archetype);`
- L998 _public member_ `int32 ChunkMemorySize = 0;` — Created archetype will have chunks of this size. 0 denotes "use default" (see UE::Mass::ChunkSize)
- L1001 _public member_ `FName DebugName;` — Name to identify the archetype while debugging
- L1004 _public member_ `FColor DebugColor{0};`

#### Free symbols / members of external scopes

- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMass, Warning, All);`
- L28 _delegate_ `DECLARE_STATS_GROUP(TEXT("Mass"), STATGROUP_Mass, STATCAT_Advanc`
- L29 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Mass Total Frame Time"), STAT_Mass_Total, STATGROUP_M`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Mass` (scope `UE`)
- L38 _variable_ `template<typename T> static constexpr bool TAlwaysFalse = false;` (scope `UE::Mass`)
- L499 _typedef_ `using FDecayedSharedStruct = TDecay<TSharedStruct>::Type;` (scope `FMassArchetypeSharedFragmentValues::ReplaceSharedFragments`)
- L643 _function_ `friend inline uint32 GetTypeHash(const FMassArchetypeSharedFragmentValues& SharedFragmentValues)`
- L717 _prototype_ `ENUM_CLASS_FLAGS(EMassObservedOperationFlags);`
- L718 _prototype_ `FString LexToString(const EMassObservedOperationFlags Value);`
- L799 _namespace_ `namespace UE`
- L799 _namespace_ `namespace Mass` (scope `UE`)
- L812 _enumerator_ `Ordinal = Super::Ordinal + 1` (scope `UE::Mass::TMultiTypeList::__anonff9a24130103`)
- L830 _enumerator_ `Ordinal = 0` (scope `UE::Mass::TMultiTypeList::__anonff9a24130203`)
- L853 _enumerator_ `Ordinal = Super::Ordinal + 1` (scope `UE::Mass::TMultiArray::__anonff9a24130303`)
- L927 _enumerator_ `enum { Ordinal = 0 }; SIZE_T GetAllocatedSize() const { return FragmentInstances.GetAllocatedSize(); } int GetNumArrays() const` (scope `UE::Mass::TMultiArray::__anonff9a24130403`)

### `Source/Runtime/MassEntity/Public/MassEntityUtils.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mass` (scope `UE`)
- L12 _namespace_ `namespace Utils` (scope `UE::Mass`)
- L16 _prototype_ `extern EProcessorExecutionFlags GetProcessorExecutionFlagsForWorld(const UWorld& World);` (scope `UE::Mass::Utils`) — returns the current execution mode for the processors calculated from the world network mode
- L19 _prototype_ `extern EProcessorExecutionFlags DetermineProcessorExecutionFlags(const UWorld* World, EProcessorExecutionFlags ExecutionFlagsOverride = EProcessorExecutionFlags::None);` (scope `UE::Mass::Utils`) — based on the given World (which can be null) and 'ExecutionFlagsOverride', the function determines the execution flags to use
- L22 _prototype_ `uint8 DetermineProcessorSupportedTickTypes(const UWorld* World);` (scope `UE::Mass::Utils`) — based on the given World (which can be null), the function determines additional level tick types for the processing phases
- L28 _prototype_ `extern void CreateEntityCollections(const FMassEntityManager& EntityManager, const TConstArrayView<FMassEntityHandle> Entities , const FMassArchetypeEntityCollection::EDuplicatesHandling DuplicatesHandling, TArray<FMassArchetypeEntityCollection>& OutEntityCollections);` (scope `UE::Mass::Utils`) — Fills OutEntityCollections with per-archetype FMassArchetypeEntityCollection instances. @param DuplicatesHandling used to inform the function whether to expect duplicates.
- L52 _function_ `template<typename TPred, typename TSwap> inline void AbstractSort(const int32 NumElements, TPred&& Predicate, TSwap&& SwapFunctor)` (scope `UE::Mass::Utils`) — AbstractSort is a sorting function that only needs to know how many items there are, how to compare items at individual locations - where location is in [0, NumElements) - and how to swap two elements at given locations. The main use case is to sort multiple arrays while keeping them in sync. For example: TArray<float> Lead = { 3.1, 0.2, 2.6, 1.0 }; TArray<UObject*> Payload = { A, B, C, D }; AbstractSort(Lead.Num()											// NumElements , [&Lead](const int32 LHS, const int32 RHS)					// Predicate { return Lead[LHS] < Lead[RHS]; } , [&Lead, &Payload](const int32 A, const int32 B)			// SwapFunctor { Swap(Lead[A], Lead[B]); Swap(Payload[A], Payload[B]); } );
- L84 _prototype_ `extern FMassEntityManager* GetEntityManager(const UObject* WorldContextObject);` (scope `UE::Mass::Utils`)
- L85 _prototype_ `extern FMassEntityManager* GetEntityManager(const UWorld* World);` (scope `UE::Mass::Utils`)
- L86 _prototype_ `extern FMassEntityManager& GetEntityManagerChecked(const UWorld& World);` (scope `UE::Mass::Utils`)

### `Source/Runtime/MassEntity/Public/MassEntityView.h` (Public)


#### struct `FMassEntityView`  
`struct FMassEntityView`  
_L23-186_
- reflection: `USTRUCT()`
- desc: The type representing a single entity in a single archetype. It's of a very transient nature so we guarantee it's validity only within the scope it has been created in. Don't store it.
- L27 _public prototype_ `FMassEntityView() = default;`
- L35 _public prototype_ `FMassEntityView(const FMassArchetypeHandle& ArchetypeHandle, FMassEntityHandle Entity);` — Resolves Entity against ArchetypeHandle. Note that this approach requires the caller to ensure that Entity indeed belongs to ArchetypeHandle. If not the call will fail a check. As a remedy calling the FMassEntityManager-flavored constructor is recommended since it will first find the appropriate archetype for Entity.
- L41 _public prototype_ `FMassEntityView(const FMassEntityManager& EntityManager, FMassEntityHandle Entity);` — Finds the archetype Entity belongs to and then resolves against it. The caller is responsible for ensuring that the given Entity is in fact a valid ID tied to any of the archetypes
- L47 _public prototype_ `static FMassEntityView TryMakeView(const FMassEntityManager& EntityManager, FMassEntityHandle Entity);` — If the given handle represents a valid entity the function will create a FMassEntityView just like a constructor would. If the entity is not valid the produced view will be "unset".
- L49 _public function_ `FMassEntityHandle GetEntity() const`
- L56 _public function_ `template<typename T> T& GetFragmentData() const` — will fail a check if the viewed entity doesn't have the given fragment
- L67 _public function_ `template<typename T> T* GetFragmentDataPtr() const` — if the viewed entity doesn't have the given fragment the function will return null
- L76 _public function_ `FStructView GetFragmentDataStruct(const UScriptStruct* FragmentType) const`
- L84 _public function_ `template<UE::Mass::CSparse T> requires UE::Mass::CFragment<T> const T* GetSparseFragmentDataPtr() const`
- L91 _public function_ `template<UE::Mass::CSparse T> requires UE::Mass::CFragment<T> T* GetSparseFragmentDataPtr()`
- L98 _public function_ `template<typename T> const T* GetConstSharedFragmentDataPtr() const` — if the viewed entity doesn't have the given const shared fragment the function will return null
- L108 _public function_ `template<typename T> const T& GetConstSharedFragmentData() const` — will fail a check if the viewed entity doesn't have the given const shared fragment
- L116 _public function_ `FConstStructView GetConstSharedFragmentDataStruct(const UScriptStruct* FragmentType) const`
- L124 _public function_ `template<UE::Mass::CSharedFragment T> T& GetSharedFragmentData() const` — will fail a check if the viewed entity doesn't have the given shared fragment
- L131 _public function_ `template<UE::Mass::CSharedFragment T> T* GetSharedFragmentDataPtr() const` — if the viewed entity doesn't have the given shared fragment the function will return null
- L136 _public function_ `FStructView GetSharedFragmentDataStruct(const UScriptStruct* FragmentType) const`
- L143 _public function_ `template<typename T> bool HasTag() const`
- L148 _public prototype_ `bool HasTag(TNotNull<const UScriptStruct*> TagType) const;`
- L149 _public function_ `bool HasTag(const UScriptStruct& TagType) const`
- L154 _public prototype_ `bool HasFragment(TNotNull<const UScriptStruct*> FragmentType) const;`
- L156 _public function_ `template<UE::Mass::CFragment T> bool HasFragment() const`
- L161 _public prototype_ `bool HasElement(TNotNull<const UScriptStruct*> ElementType, const UE::Mass::EIncludeSparseElements IncludeSparseElements = UE::Mass::EIncludeSparseElements::Yes) const;`
- L163 _public function_ `template<UE::Mass::CSparse T> bool HasElement(const UE::Mass::EIncludeSparseElements IncludeSparseElements = UE::Mass::EIncludeSparseElements::Yes) const`
- L168 _public prototype_ `bool IsSet() const;`
- L169 _public prototype_ `bool IsValid() const;`
- L170 _public prototype_ `bool operator==(const FMassEntityView& Other) const;`
- L173 _protected prototype_ `void* GetFragmentPtr(const UScriptStruct& FragmentType) const;`
- L174 _protected prototype_ `void* GetFragmentPtrChecked(const UScriptStruct& FragmentType) const;`
- L175 _protected prototype_ `const void* GetConstSharedFragmentPtr(const UScriptStruct& FragmentType) const;`
- L176 _protected prototype_ `const void* GetConstSharedFragmentPtrChecked(const UScriptStruct& FragmentType) const;`
- L177 _protected prototype_ `void* GetSharedFragmentPtr(const UScriptStruct& FragmentType) const;`
- L178 _protected prototype_ `void* GetSharedFragmentPtrChecked(const UScriptStruct& FragmentType) const;`
- L179 _protected prototype_ `FStructView GetSparseFragmentPtr(TNotNull<const UScriptStruct*> FragmentType);`
- L180 _protected prototype_ `FConstStructView GetSparseFragmentPtr(TNotNull<const UScriptStruct*> FragmentType) const;`
- L183 _private member_ `FMassEntityHandle Entity;`
- L184 _private member_ `FMassEntityInChunkDataHandle EntityDataHandle;`
- L185 _private member_ `FMassArchetypeData* Archetype = nullptr;`
- L191 _function_ `inline bool FMassEntityView::IsSet() const`
- L196 _function_ `inline bool FMassEntityView::IsValid() const`
- L201 _function_ `inline bool FMassEntityView::operator==(const FMassEntityView& Other) const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSENTITY_API`

### `Source/Runtime/MassEntity/Public/MassExecutionContext.h` (Public)


#### struct `FMassExecutionContext`  
`struct FMassExecutionContext`  
_L44-1003_
- L69 _private typedef_ `using FFragmentView = TFragmentView<TArrayView<FMassFragment>>;`
- L70 _private member_ `TArray<FFragmentView, TInlineAllocator<8>> FragmentViews;`
- L72 _private typedef_ `using FChunkFragmentView = TFragmentView<FStructView>;`
- L73 _private member_ `TArray<FChunkFragmentView, TInlineAllocator<4>> ChunkFragmentViews;`
- L75 _private typedef_ `using FConstSharedFragmentView = TFragmentView<FConstStructView>;`
- L76 _private member_ `TArray<FConstSharedFragmentView, TInlineAllocator<4>> ConstSharedFragmentViews;`
- L78 _private typedef_ `using FSharedFragmentView = TFragmentView<FStructView>;`
- L79 _private member_ `TArray<FSharedFragmentView, TInlineAllocator<4>> SharedFragmentViews;`
- L81 _private member_ `FMassElementBitSet RequestedSparseElementsAccess;`
- L86 _private member_ `FMassEntityView LinkedEntityView;` — linked entity to allow access to fragments on an entity not in the query, must be bound before access
- L89 _private member_ `FMassEntityView CachedIndirectEntityView;` — Used for indirect fragment access
- L91 _private member_ `TUniquePtr<FMassSubsystemAccess> SubsystemAccessPtr;`
- L94 _private member_ `TSharedPtr<FMassCommandBuffer> DeferredCommandBuffer;` — mz@todo make this shared ptr thread-safe and never auto-flush in MT environment.
- L95 _private member_ `TArrayView<FMassEntityHandle> EntityListView;`
- L99 _private member_ `FMassArchetypeEntityCollection EntityCollection;` — If set this indicates the exact archetype and its chunks to be processed. @todo this data should live somewhere else, preferably be just a parameter to Query.ForEachEntityChunk function
- L102 _private member_ `FInstancedStruct AuxData;` — @todo rename to "payload"
- L103 _private member_ `float DeltaTimeSeconds = 0.0f;`
- L104 _private member_ `FMassElementBitSet CurrentArchetypeCompositionBitSet;`
- L106 _private member_ `FColor DebugColor;`
- L109 _private member_ `TSharedRef<FMassEntityManager> EntityManager;`
- L137 _private member_ `TArray<FQueryTransientRuntime, TInlineAllocator<2>> QueriesStack;` — We usually expect the queries to go only a single layer deep, so 2 elements here should suffice most of the time
- L140 _private member_ `uint32 IteratorSerialNumberGenerator = 0;` — Track the serial number for FEntityIterator creation
- L142 _private member_ `EMassExecutionContextType ExecutionType = EMassExecutionContextType::Local;`
- L146 _private member_ `bool bFlushDeferredCommands = true;` — Used to control when the context is allowed to flush commands collected in DeferredCommandBuffer. This mechanism is mainly utilized to avoid numerous small flushes in favor of fewer larger ones.
- L149 _private member_ `bool bHasSparseRequirements = false;` — cached value of current query's HasSparseRequirements()
- L152 _private member_ `FMassArchetypeData* ArchetypeDataPtr = nullptr;` — Extremely transient, needs to be kept private. Used for direct access to sparse elements API
- L153 _private member_ `FMassEntityInChunkDataHandle ChunkEntityIndex;`
- L156 _private member_ `FString DebugExecutionDescription;`
- L160 _private member_ `TWeakObjectPtr<UMassProcessor> DebugProcessor;` — js@todo make this more generic
- L164 _private member_ `const FMassEntityCreationRequirements* ActiveEntityCreationRequirements = nullptr;` — Active permissions for archetype creation (processor-level when no query is active; query-level otherwise)
- L166 _private function_ `TArrayView<FFragmentView> GetMutableRequirements()`
- L170 _private function_ `TArrayView<FChunkFragmentView> GetMutableChunkRequirements()`
- L174 _private function_ `TArrayView<FConstSharedFragmentView> GetMutableConstSharedRequirements()`
- L178 _private function_ `TArrayView<FSharedFragmentView> GetMutableSharedRequirements()`
- L183 _private function_ `void GetSubsystemRequirementBits(FMassExternalSubsystemBitSet& OutConstSubsystemsBitSet, FMassExternalSubsystemBitSet& OutMutableSubsystemsBitSet)`
- L188 _private function_ `void SetSubsystemRequirementBits(const FMassExternalSubsystemBitSet& InConstSubsystemsBitSet, const FMassExternalSubsystemBitSet& InMutableSubsystemsBitSet)`
- L193 _private prototype_ `FStructView GetSparseElementInternal(TNotNull<const UScriptStruct*> ElementType, const FMassEntityHandle EntityHandle) const;`
- L200 _private prototype_ `FMassExecutionContext& operator=(const FMassExecutionContext& Other);` — Explicit assignment used by copy ctor and internal helpers. Intentionally does NOT copy QueriesStack (callers manage it explicitly) or processing callbacks (set by FProcessorWorker on the copy after construction).
- L203 _public prototype_ `explicit FMassExecutionContext(FMassEntityManager& InEntityManager, const float InDeltaTimeSeconds = 0.f, const bool bInFlushDeferredCommands = true);`
- L204 _public prototype_ `FMassExecutionContext(FMassExecutionContext&& Other);`
- L205 _public prototype_ `FMassExecutionContext(const FMassExecutionContext& Other);`
- L206 _public prototype_ `FMassExecutionContext(const FMassExecutionContext& Other, FMassEntityQuery& Query, const TSharedPtr<FMassCommandBuffer>& InCommandBuffer = {});`
- L207 _public prototype_ `~FMassExecutionContext();`
- L210 _public prototype_ `static FMassExecutionContext& GetDummyInstance();` — For internal use only, should never be exported as part of API
- L212 _public prototype_ `FMassEntityManager& GetEntityManagerChecked() const;`
- L213 _public prototype_ `const TSharedRef<FMassEntityManager>& GetSharedEntityManager();`
- L216 _public function_ `const FString& DebugGetExecutionDesc() const`
- L220 _public function_ `void DebugSetExecutionDesc(const FString& Description)`
- L224 _public function_ `void DebugSetExecutionDesc(FString&& Description)`
- L229 _public function_ `UMassProcessor* DebugGetProcessor() const`
- L233 _public function_ `void DebugSetProcessor(UMassProcessor* Processor)`
- L239 _public prototype_ `void PushQuery(FMassEntityQuery& InQuery);`
- L240 _public prototype_ `void PopQuery(const FMassEntityQuery& InQuery);`
- L241 _public prototype_ `const FMassEntityQuery& GetCurrentQuery() const;`
- L242 _public prototype_ `bool IsCurrentQuery(const FMassEntityQuery& Query) const;`
- L243 _public prototype_ `void ApplyFragmentRequirements(const FMassEntityQuery& RequestingQuery);`
- L244 _public prototype_ `void ClearFragmentViews(const FMassEntityQuery& RequestingQuery);`
- L250 _public prototype_ `bool ExecuteSparseElementsFilter(const FSparseEntityIterator& EntityIt) const;` — @return whether the entity indicated via FSparseEntityIterator meets the sparse element requirements. Will always return true if there are no sparse requirements
- L349 _public prototype_ `FEntityIterator CreateEntityIterator();` — Creates an Entity Iterator for the current chunk. Supports range-based for loop and can be used directly as an entity index for the current chunk.
- L409 _public prototype_ `FSparseEntityIterator CreateSparseEntityIterator();` — Creates an entity iterator for the current chunk that's configured to skip entities that are not matching the current query's sparse element requirements.
- L414 _public prototype_ `void SetFlushDeferredCommands(const bool bNewFlushDeferredCommands);` — Sets bFlushDeferredCommands. Note that setting to True while the system is being executed doesn't result in immediate commands flushing
- L415 _public prototype_ `void SetDeferredCommandBuffer(const TSharedPtr<FMassCommandBuffer>& InDeferredCommandBuffer);`
- L416 _public prototype_ `void SetEntityCollection(const FMassArchetypeEntityCollection& InEntityCollection);`
- L417 _public prototype_ `void SetEntityCollection(FMassArchetypeEntityCollection&& InEntityCollection);`
- L418 _public prototype_ `void ClearEntityCollection();`
- L419 _public prototype_ `void SetAuxData(const FInstancedStruct& InAuxData);`
- L421 _public prototype_ `void SetExecutionType(EMassExecutionContextType InExecutionType);`
- L422 _public prototype_ `EMassExecutionContextType GetExecutionType() const;`
- L425 _public prototype_ `void BindLinkedEntity(const FMassEntityLinkFragment& EntityLinkFragment);` — Binds a linked entity with a specific link type, use this if you already have the link fragment you wish to bind
- L427 _public prototype_ `void BindLinkedEntity();` — Binds a linked entity with the link type specified in the current query
- L429 _public prototype_ `float GetDeltaTimeSeconds() const;`
- L431 _public prototype_ `UWorld* GetWorld() const;`
- L433 _public function_ `TSharedPtr<FMassCommandBuffer> GetSharedDeferredCommandBuffer() const`
- L437 _public function_ `FMassCommandBuffer& Defer() const`
- L443 _public function_ `TConstArrayView<FMassEntityHandle> GetEntities() const`
- L447 _public function_ `int32 GetNumEntities() const`
- L452 _public function_ `FMassEntityHandle GetEntity(const int32 Index) const`
- L457 _public function_ `void ForEachEntityInChunk(const FMassEntityExecuteFunction& EntityExecuteFunction)`
- L465 _public function_ `bool DoesArchetypeHaveElement(TNotNull<const UScriptStruct*> ElementType) const`
- L471 _public function_ `bool DoesArchetypeHaveElement(const UScriptStruct& ElementType) const` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L477 _public function_ `template<UE::Mass::CElement T> bool DoesArchetypeHaveElement() const`
- L482 _public function_ `bool DoesArchetypeHaveFragment(TNotNull<const UScriptStruct*> FragmentType) const`
- L488 _public function_ `bool DoesArchetypeHaveFragment(const UScriptStruct& ElementType) const` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L494 _public function_ `template<UE::Mass::CFragment T> bool DoesArchetypeHaveFragment() const`
- L499 _public function_ `bool DoesArchetypeHaveTag(TNotNull<const UScriptStruct*> TagType) const`
- L505 _public function_ `bool DoesArchetypeHaveTag(const UScriptStruct& ElementType) const` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L511 _public function_ `template<UE::Mass::CTag T> bool DoesArchetypeHaveTag() const`
- L517 _public function_ `FColor DebugGetArchetypeColor() const`
- L528 _public prototype_ `bool SetCurrentChunk(int32 ChunkIndex, const FMassArchetypeChunk& Chunk);` — @return whether the given chunk is fine to be processed, i.e. `false` indicates the chunk should be skipped
- L530 _public prototype_ `int32 GetChunkSerialModificationNumber() const;`
- L533 _public function_ `template<typename T> T* GetMutableChunkFragmentPtr()`
- L544 _public function_ `template<typename T> T& GetMutableChunkFragment()`
- L552 _public function_ `template<typename T> const T* GetChunkFragmentPtr() const`
- L562 _public function_ `template<typename T> const T& GetChunkFragment() const`
- L570 _public function_ `const void* GetConstSharedFragmentPtr(const UScriptStruct& SharedFragmentType) const` — Shared fragment related operations
- L577 _public function_ `template<typename T> const T* GetConstSharedFragmentPtr() const`
- L586 _public function_ `template<typename T> const T& GetConstSharedFragment() const`
- L594 _public function_ `template<typename T> T* GetMutableSharedFragmentPtr()`
- L604 _public function_ `template<typename T> const T* GetSharedFragmentPtr() const`
- L613 _public function_ `template<typename T> T& GetMutableSharedFragment()`
- L621 _public function_ `template<typename T> const T& GetSharedFragment() const`
- L630 _public function_ `template<typename TFragment> TArrayView<TFragment> GetMutableFragmentView()` — Fragments related operations
- L640 _public function_ `template<typename TFragment> TConstArrayView<TFragment> GetFragmentView() const`
- L648 _public function_ `TConstArrayView<FMassFragment> GetFragmentView(const UScriptStruct* FragmentType) const`
- L655 _public function_ `TArrayView<FMassFragment> GetMutableFragmentView(const UScriptStruct* FragmentType)`
- L664 _public function_ `template<typename TFragmentBase> TConstArrayView<TFragmentBase> GetFragmentView(TNotNull<const UScriptStruct*> FragmentType) const`
- L672 _public function_ `template<typename TFragmentBase> TArrayView<TFragmentBase> GetMutableFragmentView(TNotNull<const UScriptStruct*> FragmentType)`
- L680 _public function_ `template<typename T> T* GetLinkedEntityFragmentPtr()`
- L691 _public function_ `template<typename T> const T* GetLinkedEntityConstFragmentPtr()`
- L702 _public function_ `template<typename T> T* GetIndirectFragmentPtr(const FMassEntityHandle& FragmentOwner)`
- L717 _public function_ `template<typename T> const T* GetIndirectConstFragmentPtr(const FMassEntityHandle& FragmentOwner)`
- L732 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T* GetMutableSubsystem()`
- L738 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T& GetMutableSubsystemChecked()`
- L744 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T* GetSubsystem()`
- L750 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T& GetSubsystemChecked()`
- L756 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T* GetMutableSubsystem(const TSubclassOf<USubsystem> SubsystemClass)`
- L762 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T& GetMutableSubsystemChecked(const TSubclassOf<USubsystem> SubsystemClass)`
- L768 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T* GetSubsystem(const TSubclassOf<USubsystem> SubsystemClass)`
- L774 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T& GetSubsystemChecked(const TSubclassOf<USubsystem> SubsystemClass)`
- L784 _public function_ `template<UE::Mass::CSparse TFragment> requires UE::Mass::CFragment<TFragment> TFragment* GetMutableSparseElement(const FEntityIterator& EntityIterator) const`
- L794 _public function_ `template<UE::Mass::CSparse TFragmentBase> requires UE::Mass::CFragment<TFragmentBase> TFragmentBase* GetMutableSparseElement(TNotNull<const UScriptStruct*> ElementType, const FEntityIterator& EntityIterator) const`
- L804 _public function_ `FStructView GetMutableSparseElement(TNotNull<const UScriptStruct*> ElementType, const FEntityIterator& EntityIterator) const`
- L816 _public function_ `template<UE::Mass::CSparse TFragment> requires UE::Mass::CFragment<TFragment> const TFragment* GetSparseElement(const FEntityIterator& EntityIterator) const`
- L825 _public function_ `template<UE::Mass::CSparse TFragmentBase> requires UE::Mass::CFragment<TFragmentBase> const TFragmentBase* GetSparseElement(TNotNull<const UScriptStruct*> ElementType, const FEntityIterator& EntityIterator) const`
- L835 _public function_ `FConstStructView GetSparseElement(TNotNull<const UScriptStruct*> ElementType, const FEntityIterator& EntityIterator) const`
- L845 _public prototype_ `bool HasSparseElement(TNotNull<const UScriptStruct*> ElementType, const FEntityIterator& EntityIterator) const;`
- L848 _public function_ `const FMassArchetypeEntityCollection& GetEntityCollection() const` — Sparse chunk related operation
- L853 _public function_ `const FInstancedStruct& GetAuxData() const`
- L857 _public function_ `FInstancedStruct& GetMutableAuxData()`
- L863 _public function_ `template<typename TFragment> bool ValidateAuxDataType() const`
- L869 _public prototype_ `void FlushDeferred();`
- L871 _public prototype_ `void ClearExecutionData();`
- L873 _public prototype_ `void SetCurrentArchetype(FMassArchetypeData& Archetype);`
- L875 _public function_ `void SetCurrentArchetypeCompositionDescriptor(const FMassArchetypeCompositionDescriptor& Descriptor)`
- L879 _public function_ `void StoreCurrentArchetypeComposition(const FMassElementBitSet& CompositionBitSet)`
- L888 _public prototype_ `FMassEntityHandle CreateEntity(const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {});` — Validates creation request by the active FMassEntityCreationRequirements and creates an entity of the declared archetype. Will assert on validation failure.
- L889 _public prototype_ `void BuildEntity(const FMassArchetypeHandle& ArchetypeHandle, const FMassEntityHandle& EntityHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues = {});`
- L891 _public prototype_ `void BatchCreateEntities(const FMassArchetypeHandle& ArchetypeHandle, const FMassArchetypeSharedFragmentValues& SharedFragmentValues, const int32 Count, TArray<FMassEntityHandle>& InOutEntities);`
- L893 _public function_ `void BatchCreateEntities(const FMassArchetypeHandle& ArchetypeHandle, const int32 Count, TArray<FMassEntityHandle>& InOutEntities)`
- L900 _public function_ `void SetActiveArchetypeRequirements(const FMassEntityCreationRequirements* InRequirements)` — Set/restore by processor and query push/pop
- L906 _public function_ `void DebugSetColor(FColor InColor)`
- L921 _public prototype_ `bool CacheSubsystemRequirements(const FMassSubsystemRequirements& SubsystemRequirements);` — Processes SubsystemRequirements to fetch and cache all the indicated subsystems. If a UWorld is required to fetch a specific subsystem then the one associated with the stored EntityManager will be used. @param SubsystemRequirements indicates all the subsystems that are expected to be accessed. Requesting a subsystem not indicated by the SubsystemRequirements will result in a failure. @return `true` if all required subsystems have been found, `false` otherwise.
- L924 _protected function_ `void SetSubsystemRequirements(const FMassSubsystemRequirements& SubsystemRequirements)`
- L929 _protected prototype_ `void SetFragmentRequirements(const FMassFragmentRequirements& FragmentRequirements);`
- L931 _protected function_ `void ClearFragmentViews()`
- L951 _protected prototype_ `bool ExecuteSparseElementsFilterImpl(const FSparseEntityIterator& EntityIt) const;`
- L952 _protected prototype_ `bool ExecuteSparseChunkFilterImpl(const FMassArchetypeChunk& Chunk) const;`
- L955 _protected member_ `TFunction<void(const FMassEntityQuery*)> PreQueryCallbackFunc;`
- L956 _protected member_ `TFunction<void(const FMassEntityQuery*)> PostQueryCallbackFunc;`
- L958 _protected member_ `FMassQueueChunkFunction ChunkQueueFunc;`
- L961 _public function_ `void SetPreQueryCallback(TFunction<void(const FMassEntityQuery*)> Function)`
- L966 _public function_ `void PreQueryCallback(const FMassEntityQuery* SourceQuery)`
- L974 _public function_ `void SetPostQueryCallback(TFunction<void(const FMassEntityQuery*)> Function)`
- L979 _public function_ `bool HasChunkQueueFunc() const`
- L984 _public function_ `void QueueChunkChecked(FMassChunkProcessingQueueParams&& Params)`
- L991 _public function_ `void SetChunkQueueFunc(FMassQueueChunkFunction&& InChunkQueueFunc)`
- L996 _public function_ `void PostQueryCallback(const FMassEntityQuery* SourceQuery)`
- L1008 _function_ `inline FMassEntityManager& FMassExecutionContext::GetEntityManagerChecked() const`
- L1013 _function_ `inline const TSharedRef<FMassEntityManager>& FMassExecutionContext::GetSharedEntityManager()`
- L1018 _function_ `inline void FMassExecutionContext::SetFlushDeferredCommands(const bool bNewFlushDeferredCommands)`
- L1023 _function_ `inline void FMassExecutionContext::SetDeferredCommandBuffer(const TSharedPtr<FMassCommandBuffer>& InDeferredCommandBuffer)`
- L1028 _function_ `inline void FMassExecutionContext::ClearEntityCollection()`
- L1033 _function_ `inline void FMassExecutionContext::SetAuxData(const FInstancedStruct& InAuxData)`
- L1038 _function_ `inline float FMassExecutionContext::GetDeltaTimeSeconds() const`
- L1043 _function_ `inline void FMassExecutionContext::SetExecutionType(EMassExecutionContextType InExecutionType)`
- L1049 _function_ `inline EMassExecutionContextType FMassExecutionContext::GetExecutionType() const`
- L1054 _function_ `inline const FMassEntityQuery& FMassExecutionContext::GetCurrentQuery() const`
- L1060 _function_ `inline bool FMassExecutionContext::IsCurrentQuery(const FMassEntityQuery& Query) const`
- L1065 _function_ `inline void FMassExecutionContext::ApplyFragmentRequirements(const FMassEntityQuery& RequestingQuery)`
- L1071 _function_ `inline void FMassExecutionContext::ClearFragmentViews(const FMassEntityQuery& RequestingQuery)`
- L1077 _function_ `inline bool FMassExecutionContext::ExecuteSparseElementsFilter(const FSparseEntityIterator& EntityIt) const`
- L1082 _function_ `inline int32 FMassExecutionContext::GetChunkSerialModificationNumber() const`

#### struct `FMassExecutionContext::TFragmentView`  
`template< typename ViewType > struct TFragmentView`  
_L51-68_
- L53 _public member_ `FMassFragmentRequirementDescription Requirement;`
- L54 _public member_ `ViewType FragmentView;`
- L56 _public function_ `TFragmentView()`
- L59 _public function_ `explicit TFragmentView(const FMassFragmentRequirementDescription& InRequirement) : Requirement(InRequirement)`
- L64 _public function_ `bool operator==(const UScriptStruct* FragmentType) const`

#### struct `FMassExecutionContext::FQueryTransientRuntime`  
`struct FQueryTransientRuntime`  
_L111-134_
- L113 _public member_ `TNotNull<FMassEntityQuery*> Query;`
- L114 _public member_ `FMassExternalSubsystemBitSet ConstSubsystemsBitSet;`
- L115 _public member_ `FMassExternalSubsystemBitSet MutableSubsystemsBitSet;`
- L118 _public member_ `const FMassEntityCreationRequirements* PreviousEntityCreationRequirements = nullptr;` — used to restore creation requirements on query pop, storing the previous value to easily restore processor creation requirements
- L122 _public member_ `static constexpr uint32 MaxFragmentBreakpointCount = 8;` — MaxBreakFragmentCount needs to be bigger than the greatest number of fragments a query has a write requirement for to that can have a breakpoint set
- L123 _public member_ `TStaticArray<const UScriptStruct*, MaxFragmentBreakpointCount> FragmentTypesToBreakOn;`
- L125 _public member_ `bool bCheckProcessorBreaks = false;`
- L126 _public member_ `int32 BreakFragmentsCount = 0;`
- L130 _public member_ `uint32 IteratorSerialNumber = 0;` — Serial number to ensure iterator consistency (subsequent calls to CreateEntityIterator should not pass equivalency test)
- L133 _public prototype_ `static FQueryTransientRuntime& GetDummyInstance();` — Helper function to create an empty instance with a valid Query ptr

#### struct `FMassExecutionContext::FEntityIterator`  
`struct FEntityIterator`  
_L256-343_
- desc: Iterator to easily loop through entities in the current chunk. Supports ranged for and can be used directly as an entity index for the current chunk.
- L258 _public function_ `inline int32 operator*() const`
- L263 _public function_ `inline bool operator!=(const int& Other) const`
- L268 _public function_ `inline operator int32() const`
- L273 _public function_ `inline operator bool() const`
- L278 _public function_ `inline bool operator<(const int32 Other) const`
- L283 _public function_ `inline FEntityIterator& operator++()`
- L296 _public function_ `inline void operator++(int)`
- L301 _public function_ `FEntityIterator&& begin()`
- L306 _public function_ `FEntityIterator end() const`
- L313 _public prototype_ `FEntityIterator();`
- L314 _public prototype_ `FEntityIterator(FEntityIterator&&) = default;`
- L316 _public prototype_ `FEntityIterator& operator=(const FEntityIterator&) = delete;`
- L317 _public prototype_ `FEntityIterator& operator=(FEntityIterator&&) = delete;`
- L322 _public prototype_ `FEntityIterator(const FEntityIterator&) = delete;` — Iterator copying is disabled to avoid additional checks to detect if entity chunk being iterated on changed. This decision is to be reconsidered when valid iterator-copying scenarios emerge.
- L324 _public function_ `FMassEntityHandle GetEntityHandle() const`
- L331 _protected prototype_ `FEntityIterator(FMassExecutionContext& InExecutionContext);`
- L332 _protected prototype_ `FEntityIterator(FMassExecutionContext& InExecutionContext, FQueryTransientRuntime& InQueryRuntime);`
- L335 _protected prototype_ `void TestBreakpoints();`
- L338 _protected member_ `const FMassExecutionContext& ExecutionContext;`
- L339 _protected member_ `const FQueryTransientRuntime& QueryRuntime;`
- L340 _protected member_ `int32 EntityIndex = INDEX_NONE;`
- L341 _protected member_ `const int32 NumEntities = INDEX_NONE;`
- L342 _protected member_ `const uint32 SerialNumber = 0;`

#### struct `FMassExecutionContext::FSparseEntityIterator`  
`struct FSparseEntityIterator : FEntityIterator`  
_L356-403_
- inherits: `FEntityIterator`
- desc: A flavor of FEntityIterator that skips all the entities that don't match current query's sparse element requirements. This means that if there are no sparse requirements then FSparseEntityIterator will behave like a regular FEntityIterator but less efficiently so.
- L359 _public prototype_ `FSparseEntityIterator() = default;` — Note that the default constructor results in an "invalid" (i.e. useless) iterator.
- L361 _public function_ `explicit FSparseEntityIterator(FEntityIterator&& Source) : FEntityIterator(MoveTemp(Source))`
- L370 _public function_ `FSparseEntityIterator& operator++()`
- L387 _public function_ `void operator++(int)`
- L392 _public function_ `FSparseEntityIterator&& begin()`
- L397 _public function_ `FSparseEntityIterator end() const`

#### Free symbols / members of external scopes

- L24 _macro_ `#define MASS_CHECK_IF_VALID(View, Type) \`
- L28 _macro_ `#define MASS_CHECK_IF_READWRITE(View) \`
- L33 _macro_ `#define MASS_CHECK_IF_SPARSE_REQUIREMENT(ElementType) \`
- L538 _function_ `FChunkFragmentView* FoundChunkFragmentData = ChunkFragmentViews.FindByPredicate([Type](const FChunkFragmentView& Element) { return Element.Requirement.StructType == Type; } );` (scope `FMassExecutionContext::GetMutableChunkFragmentPtr`)
- L557 _function_ `const FChunkFragmentView* FoundChunkFragmentData = ChunkFragmentViews.FindByPredicate([Type](const FChunkFragmentView& Element) { return Element.Requirement.StructType == Type; } );` (scope `FMassExecutionContext::GetChunkFragmentPtr`)
- L572 _function_ `const FConstSharedFragmentView* FoundSharedFragmentData = ConstSharedFragmentViews.FindByPredicate([&SharedFragmentType](const FConstSharedFragmentView& Element) { return Element.Requirement.StructType == &SharedFragmentType; });` (scope `FMassExecutionContext::GetConstSharedFragmentPtr`)
- L581 _function_ `const FConstSharedFragmentView* FoundSharedFragmentData = ConstSharedFragmentViews.FindByPredicate([](const FConstSharedFragmentView& Element) { return Element.Requirement.StructType == T::StaticStruct(); });` (scope `FMassExecutionContext::GetConstSharedFragmentPtr`)
- L598 _function_ `FSharedFragmentView* FoundSharedFragmentData = SharedFragmentViews.FindByPredicate([](const FSharedFragmentView& Element) { return Element.Requirement.StructType == T::StaticStruct(); });` (scope `FMassExecutionContext::GetMutableSharedFragmentPtr`)
- L608 _function_ `const FSharedFragmentView* FoundSharedFragmentData = SharedFragmentViews.FindByPredicate([](const FSharedFragmentView& Element) { return Element.Requirement.StructType == T::StaticStruct(); });` (scope `FMassExecutionContext::GetSharedFragmentPtr`)
- L633 _function_ `const FFragmentView* View = FragmentViews.FindByPredicate([FragmentType](const FFragmentView& Element) { return Element.Requirement.StructType == FragmentType; });` (scope `FMassExecutionContext::GetMutableFragmentView`)
- L643 _function_ `const FFragmentView* View = FragmentViews.FindByPredicate([FragmentType](const FFragmentView& Element) { return Element.Requirement.StructType == FragmentType; });` (scope `FMassExecutionContext::GetFragmentView`)
- L1087 _typedef_ `using FMassSparseEntityIterator = FMassExecutionContext::FSparseEntityIterator;`

### `Source/Runtime/MassEntity/Public/MassExecutor.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mass` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Mass` (scope `UE`)
- L19 _namespace_ `namespace Executor` (scope `UE::Mass`)
- L22 _prototype_ `void Run(FMassRuntimePipeline& RuntimePipeline, FProcessingContext& ProcessingContext);` (scope `UE::Mass::Executor`) — Executes processors in a given RuntimePipeline
- L25 _prototype_ `void Run(UMassProcessor& Processor, FProcessingContext& ProcessingContext);` (scope `UE::Mass::Executor`) — Executes given Processor. Used mainly for triggering calculations via MassCompositeProcessors, e.g processing phases
- L32 _prototype_ `void RunSparseEntities(FMassRuntimePipeline& RuntimePipeline, FProcessingContext& ProcessingContext, FMassArchetypeHandle Archetype, TConstArrayView<FMassEntityHandle> Entities);` (scope `UE::Mass::Executor`) — Similar to the Run function, but instead of using all the entities hosted by ProcessingContext.EntitySubsystem it is processing only the entities given by EntityID via the Entities input parameter. Note that all the entities need to be of Archetype archetype. Under the hood the function converts Archetype-Entities pair to FMassArchetypeEntityCollection and calls RunWithCollection.
- L35 _function_ `inline void RunSparse(FMassRuntimePipeline& RuntimePipeline, FProcessingContext& ProcessingContext, FMassArchetypeHandle Archetype, TConstArrayView<FMassEntityHandle> Entities)` (scope `UE::Mass::Executor`) — `UE_DEPRECATED(5.8, "Use RunSparseEntities instead.")`
- L43 _prototype_ `void RunWithCollection(FMassRuntimePipeline& RuntimePipeline, FProcessingContext& ProcessingContext, const FMassArchetypeEntityCollection& EntityCollection);` (scope `UE::Mass::Executor`) — Similar to the Run function, but instead of using all the entities hosted by ProcessingContext.EntitySubsystem it is processing only the entities given via the EntityCollection input parameter.
- L46 _function_ `inline void RunSparse(FMassRuntimePipeline& RuntimePipeline, FProcessingContext& ProcessingContext, const FMassArchetypeEntityCollection& EntityCollection)` (scope `UE::Mass::Executor`) — `UE_DEPRECATED(5.8, "Use RunWithCollection instead.")`
- L52 _prototype_ `void RunProcessorsView(TArrayView<UMassProcessor* const> Processors, FProcessingContext& ProcessingContext, TConstArrayView<FMassArchetypeEntityCollection> EntityCollections = {});` (scope `UE::Mass::Executor`) — Executes given Processors array view. This function gets called under the hood by the rest of Run* functions
- L60 _prototype_ `FGraphEventRef TriggerParallelTasks(UMassProcessor& Processor, FProcessingContext&& ProcessingContext, TFunction<void()> OnDoneNotification , ENamedThreads::Type CurrentThread = ENamedThreads::GameThread , TFunction<void()> OnPreCommandFlushNotification = TFunction<void()>());` (scope `UE::Mass::Executor`) — Triggers tasks executing Processor (and potentially it's children) and returns the task graph event representing the task (the event will be "completed" once all the processors finish running). @param OnDoneNotification will be called after all the processors are done, just after flushing the command buffer. @param OnPreCommandFlushNotification will be called after all the processors are done, just before flushing the command buffer.
- L65 _prototype_ `FGraphEventRef TriggerParallelTasks(UMassProcessor& Processor, FProcessingContext& ProcessingContext, TFunction<void()> OnDoneNotification , ENamedThreads::Type CurrentThread = ENamedThreads::GameThread);` (scope `UE::Mass::Executor`) — `UE_DEPRECATED(5.6, "lvalue flavor of TriggerParallelTasks has been deprecated. Use the rvalue version.")`

### `Source/Runtime/MassEntity/Public/MassExternalSubsystemTraits.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MassEntity/Public/MassObserverManager.h` (Public)


#### struct `FMassObserversMap`  
`struct FMassObserversMap`  
_L43-58_
- reflection: `USTRUCT()`
- desc: A wrapper type for a TMap to support having array-of-maps UPROPERTY members in FMassObserverManager
- L48 _public function_ `TMap<TObjectPtr<const UScriptStruct>, FMassRuntimePipeline>& operator*()` — a helper accessor simplifying access while still keeping Container private
- L53 _public prototype_ `void DebugAddUniqueProcessors(TArray<const UMassProcessor*>& OutProcessors) const;`
- L57 _private member_ `TMap<TObjectPtr<const UScriptStruct>, FMassRuntimePipeline> Container;` — `UPROPERTY()`

#### struct `FMassObserverManager`  
`struct FMassObserverManager`  
_L66-312_
- reflection: `USTRUCT()`
- desc: A type that encapsulates logic related to notifying interested parties of entity composition changes. Upon creation it reads information from UMassObserverRegistry and instantiates processors interested in handling given fragment type addition or removal.
- L71 _public typedef_ `using FObserverLock = UE::Mass::ObserverManager::FObserverLock;` — convenience aliases
- L72 _public typedef_ `using FBufferedNotification = UE::Mass::ObserverManager::FBufferedNotification;`
- L73 _public typedef_ `using FCreationNotificationHandle = UE::Mass::ObserverManager::FCreationNotificationHandle;`
- L74 _public typedef_ `using FCreationContext = UE::Mass::ObserverManager::FCreationContext;`
- L76 _public prototype_ `FMassObserverManager();`
- L78 _public prototype_ `FMassEntityManager& GetEntityManager();`
- L80 _public function_ `bool HasObserversForBitSet(const FMassElementBitSet& InQueriedBitSet, const EMassObservedOperation Operation) const`
- L85 _public function_ `bool HasObserversForComposition(const FMassElementBitSet& InQueriedBitSet, const EMassObservedOperation Operation) const`
- L90 _public function_ `bool HasObserversForComposition(const FMassArchetypeCompositionDescriptor& Composition, const EMassObservedOperation Operation) const`
- L96 _public prototype_ `bool OnPostEntitiesCreated(const FMassArchetypeEntityCollection& EntityCollection);` — @return whether there are observers watching affected elements
- L99 _public prototype_ `bool OnPostEntityCreated(const FMassEntityHandle Entity, const FMassElementBitSet& ElementsBitSet);` — @return whether there are observers watching affected elements
- L101 _public function_ `bool OnPostEntityCreated(const FMassEntityHandle Entity, const FMassArchetypeCompositionDescriptor& Composition)`
- L107 _public prototype_ `bool OnPreEntitiesDestroyed(const FMassArchetypeEntityCollection& EntityCollection);` — @return whether there are observers watching affected elements
- L110 _public prototype_ `bool OnPreEntitiesDestroyed(UE::Mass::FProcessingContext& ProcessingContext, const FMassArchetypeEntityCollection& EntityCollection);` — @return whether there are observers watching affected elements
- L113 _public prototype_ `bool OnPreEntityDestroyed(const FMassEntityHandle Entity, const FMassElementBitSet& ElementsBitSet);` — @return whether there are observers watching affected elements
- L115 _public function_ `bool OnPreEntityDestroyed(const FMassArchetypeCompositionDescriptor& ArchetypeComposition, const FMassEntityHandle Entity)`
- L121 _public function_ `bool OnPostCompositionAdded(const FMassEntityHandle Entity, const FMassElementBitSet& CompositionBitSet)` — @return whether there are observers watching affected elements
- L127 _public function_ `bool OnPreCompositionRemoved(const FMassEntityHandle Entity, const FMassElementBitSet& CompositionBitSet)` — @return whether there are observers watching affected elements
- L133 _public function_ `bool OnPostCompositionAdded(const FMassEntityHandle Entity, const FMassArchetypeCompositionDescriptor& Composition)` — @return whether there are observers watching affected elements
- L139 _public function_ `bool OnPreCompositionRemoved(const FMassEntityHandle Entity, const FMassArchetypeCompositionDescriptor& Composition)` — @return whether there are observers watching affected elements
- L170 _protected prototype_ `bool OnCompositionChanged(FCollectionRefOrHandle&& EntityCollection, const FMassElementBitSet& Composition , const EMassObservedOperation Operation, UE::Mass::FProcessingContext* ProcessingContext = nullptr);`
- L174 _public function_ `bool OnCompositionChanged(const FMassArchetypeEntityCollection& EntityCollection, const FMassArchetypeCompositionDescriptor& Composition , const EMassObservedOperation Operation, UE::Mass::FProcessingContext* ProcessingContext = nullptr)`
- L181 _public function_ `bool OnCompositionChanged(FMassEntityHandle EntityHandle, const FMassArchetypeCompositionDescriptor& Composition , const EMassObservedOperation Operation, UE::Mass::FProcessingContext* ProcessingContext = nullptr)`
- L189 _public function_ `template<typename T, typename U = std::decay_t<T>> requires (std::is_same_v<U, FMassFragmentBitSet> || std::is_same_v<U, FMassTagBitSet>) bool OnCompositionChanged(const FMassArchetypeEntityCollection& EntityCollection, T&& BitSet , const EMassObservedOperation Operation, UE::Mass::FProcessingContext* ProcessingContext = nullptr)`
- L196 _public function_ `template<typename T, typename U = std::decay_t<T>> requires (std::is_same_v<U, FMassFragmentBitSet> || std::is_same_v<U, FMassTagBitSet>) bool OnCompositionChanged(const FMassEntityHandle Entity, T&& BitSet , const EMassObservedOperation Operation, UE::Mass::FProcessingContext* ProcessingContext = nullptr)`
- L202 _public prototype_ `void AddObserverInstance(TNotNull<const UScriptStruct*> ElementType, EMassObservedOperationFlags OperationFlags, TNotNull<UMassProcessor*> ObserverProcessor);`
- L203 _public prototype_ `void AddObserverInstance(const UScriptStruct& ElementType, EMassObservedOperation Operation, UMassProcessor& ObserverProcessor);`
- L204 _public prototype_ `void AddObserverInstance(TNotNull<UMassObserverProcessor*> ObserverProcessor);`
- L205 _public prototype_ `void RemoveObserverInstance(TNotNull<UMassObserverProcessor*> ObserverProcessor);`
- L206 _public prototype_ `void RemoveObserverInstance(TNotNull<const UScriptStruct*> ElementType, EMassObservedOperationFlags OperationFlags, TNotNull<UMassProcessor*> ObserverProcessor);`
- L207 _public prototype_ `void RemoveObserverInstance(const UScriptStruct& ElementType, EMassObservedOperation Operation, UMassProcessor& ObserverProcessor);`
- L209 _public prototype_ `void ReleaseCreationHandle(UE::Mass::ObserverManager::FCreationNotificationHandle InCreationNotificationHandle);`
- L211 _public prototype_ `void DebugGatherUniqueProcessors(TArray<const UMassProcessor*>& OutProcessors) const;`
- L215 _protected prototype_ `explicit FMassObserverManager(FMassEntityManager& Owner);`
- L217 _protected prototype_ `void Initialize();`
- L218 _protected prototype_ `void DeInitialize();`
- L223 _protected prototype_ `static void HandleElementsImpl(UE::Mass::FProcessingContext& ProcessingContext, TConstArrayView<FMassArchetypeEntityCollection> EntityCollections , FMassObserverExecutionContext&& ObserverContext, FMassObserversMap& HandlersContainer);`
- L227 _protected prototype_ `bool OnCollectionsCreatedImpl(UE::Mass::FProcessingContext& ProcessingContext, TConstArrayView<FMassArchetypeEntityCollection> EntityCollections);` — Coalesces all the elements observed in all the collections and executes all the observers at once
- L229 _protected prototype_ `void OnPostFork(EForkProcessRole);`
- L231 _protected prototype_ `void OnModulePackagesUnloaded(TConstArrayView<UPackage*> Packages);`
- L233 _protected prototype_ `TSharedRef<FObserverLock> GetOrMakeObserverLock();`
- L234 _protected prototype_ `TSharedPtr<FObserverLock> GetObserverLock() const;`
- L235 _protected function_ `bool IsLocked() const`
- L239 _protected prototype_ `TSharedRef<FCreationContext> GetOrMakeCreationContext();`
- L240 _protected prototype_ `TSharedRef<FCreationContext> GetOrMakeCreationContext(TConstArrayView<FMassEntityHandle> ReservedEntities, FMassArchetypeEntityCollection&& EntityCollection);`
- L241 _protected prototype_ `TSharedPtr<FCreationContext> GetCreationContext() const;`
- L257 _protected prototype_ `void ResumeExecution(FObserverLock& LockBeingReleased);` — Resumes observer triggering. All notifications collected in lock's BufferedNotifications will be processed at this point. Note that due to all the notifications being sent our are being sent post-factum the "OnPreRemove" observers won't be able to access the data being removed, since the remove operation has already been performed. All the instances of removal-observers being triggered will be logged. Intended to be called automatically by ~FObserverLock
- L264 _protected member_ `TWeakPtr<FObserverLock> ActiveObserverLock;` — Never access directly, use GetOrMakeObserverLock or GetOrMakeCreationContext instead. The Mass Processing Phase synchronously creates a lock before dispatching parallel mass tasks Lock should be thread-safe for creation, fetching, and adding items.
- L265 _protected member_ `int32 LocksCount = 0;`
- L266 _protected member_ `TWeakPtr<FCreationContext> ActiveCreationContext;`
- L268 _protected member_ `FMassElementBitSet ObservedElements[static_cast<uint8>(EMassObservedOperation::MAX)];`
- L271 _protected member_ `FMassObserversMap ElementObservers[static_cast<uint8>(EMassObservedOperation::MAX)];` — `UPROPERTY()`
- L273 _protected member_ `FDelegateHandle ModulesUnloadedHandle;`
- L279 _protected member_ `FMassEntityManager& EntityManager;` — The owning EntityManager. No need for it to be a UPROPERTY since by design we don't support creation of FMassObserverManager outside a FMassEntityManager instance
- L282 _protected member_ `uint32 LockedNotificationSerialNumber = 1;`
- L283 _protected member_ `uint32 DebugNonTrivialResumeExecutionCount = 0;`
- L288 _public prototype_ `void OnPostFragmentOrTagAdded(const UScriptStruct& FragmentOrTagType, const FMassArchetypeEntityCollection& EntityCollection);` — `UE_DEPRECATED(5.6, "*FragmentOrTag* functions have been deprecated. Use OnCompositionChanged instead.")`
- L290 _public prototype_ `void OnPreFragmentOrTagRemoved(const UScriptStruct& FragmentOrTagType, const FMassArchetypeEntityCollection& EntityCollection);` — `UE_DEPRECATED(5.6, "*FragmentOrTag* functions have been deprecated. Use OnCompositionChanged instead.")`
- L292 _public prototype_ `void OnFragmentOrTagOperation(const UScriptStruct& FragmentOrTagType, const FMassArchetypeEntityCollection& EntityCollection, const EMassObservedOperation Operation);` — `UE_DEPRECATED(5.6, "*FragmentOrTag* functions have been deprecated. Use OnCompositionChanged instead.")`
- L294 _public prototype_ `bool OnPostEntitiesCreated(UE::Mass::FProcessingContext& InProcessingContext, TConstArrayView<FMassArchetypeEntityCollection> EntityCollections);` — `UE_DEPRECATED(5.6, "Use the other OnPostEntitiesCreated implementation.")`
- L296 _public prototype_ `bool OnCompositionChanged(UE::Mass::FProcessingContext& InProcessingContext, const FMassArchetypeEntityCollection& EntityCollection , const FMassArchetypeCompositionDescriptor& Composition, const EMassObservedOperation Operation);` — `UE_DEPRECATED(5.6, "Use the other OnCompositionChanged implementation.")`
- L300 _protected prototype_ `void HandleSingleEntityImpl(const UScriptStruct& FragmentType, const FMassArchetypeEntityCollection& EntityCollection, FMassObserversMap& HandlersContainer);` — `UE_DEPRECATED(5.6, "Use HandleElementsImpl instead.")`
- L302 _protected prototype_ `static void HandleElementsImpl(UE::Mass::FProcessingContext& ProcessingContext, TConstArrayView<FMassArchetypeEntityCollection> EntityCollections , TArrayView<const UScriptStruct*> ObservedTypes, FMassObserversMap& HandlersContainer);` — `UE_DEPRECATED(5.7, "Use the implementation with the FMassObserverExecutionContext parameter")`
- L305 _protected prototype_ `static void HandleFragmentsImpl(UE::Mass::FProcessingContext& ProcessingContext, const FMassArchetypeEntityCollection& EntityCollection , TArrayView<const UScriptStruct*> ObservedTypes, FMassObserversMap& HandlersContainer);` — `UE_DEPRECATED(5.7, "Use the HandleElementsImpl implementation with the FMassObserverExecutionContext parameter")`
- L309 _protected prototype_ `bool OnCollectionsCreatedImpl(UE::Mass::FProcessingContext& ProcessingContext, TArray<FMassArchetypeEntityCollection>&& EntityCollections);` — `UE_DEPRECATED(5.7, "Rvalue ref implementation is no longer available, it didn't do anything special. Please use the other OnCollectionsCreatedImpl implementation instead.")`
- L326 _function_ `inline FMassEntityManager& FMassObserverManager::GetEntityManager()`
- L331 _function_ `inline TSharedPtr<FMassObserverManager::FObserverLock> FMassObserverManager::GetObserverLock() const`
- L336 _function_ `inline TSharedPtr<FMassObserverManager::FCreationContext> FMassObserverManager::GetCreationContext() const`

#### struct `FMassObserverManager::FCollectionRefOrHandle`  
`struct FCollectionRefOrHandle`  
_L151-169_
- desc: helper struct for holding either a single entity handle or an archetype collection reference. The type is highly transient, do not store instances of it. Its only function is to allow us to have a single OnCompositionChange implementation rather than having two separate implementations, one for entity handle, the other for archetype collection.
- L155 _public member_ `static FMassArchetypeEntityCollection DummyCollection;`
- L156 _public function_ `explicit FCollectionRefOrHandle(FMassEntityHandle InEntityHandle) : EntityHandle(InEntityHandle) , EntityCollection(DummyCollection)`
- L162 _public function_ `explicit FCollectionRefOrHandle(const FMassArchetypeEntityCollection& InEntityCollection) : EntityCollection(InEntityCollection)`
- L167 _public member_ `FMassEntityHandle EntityHandle;`
- L168 _public member_ `const FMassArchetypeEntityCollection& EntityCollection;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMassObserverManager> : public TStructOpsTypeTraitsBase2<FMassObserverManager>`  
_L315-321_
- inherits: `TStructOpsTypeTraitsBase2<FMassObserverManager>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L318-320_

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Mass` (scope `UE`)
- L26 _namespace_ `namespace ObserverManager` (scope `UE::Mass`)
- L319 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon4896ebc40103`)

### `Source/Runtime/MassEntity/Public/MassObserverNotificationTypes.h` (Public)


#### enum `UE::Mass::ObserverManager::EObservedOperationNotification`  
`EObservedOperationNotification : uint8`  
_L22-27_
- reflection: `UE_DEPRECATED(5.7, "The type is no longer being used, replaced by EMassObservedOperation")`
- L24 _public enumerator_ `Add = static_cast<uint8>(EMassObservedOperation::Add)`
- L25 _public enumerator_ `Remove = static_cast<uint8>(EMassObservedOperation::Remove)`
- L26 _public enumerator_ `Create`

#### struct `UE::Mass::ObserverManager::FBufferedNotification`  
`struct FBufferedNotification`  
_L38-166_
- desc: The type represents a single "operation", as observed by the registered observers, an operation that has been performed while the FObserverLock was active. Instances of FBufferedNotification contain all the information needed to send out the necessary notification once the observers lock gets released. Note that the type contains information necessary to sent our notification. In case of "Remove" notifications the operations has already been performed, and the data being removed is no longer available to the observers, and instances of FBufferedNotification do not host this information either.
- L43 _public member_ `EMassObservedOperation Type;`
- L44 _public member_ `FMassElementBitSet CompositionChange;`
- L45 _public typedef_ `using FEntitiesContainer = TVariant<FEntityCollection, FMassEntityHandle>;`
- L46 _public member_ `FEntitiesContainer AffectedEntities;`
- L48 _public function_ `FBufferedNotification(const EMassObservedOperation InType, FMassElementBitSet&& Composition, FEntitiesContainer&& Entities) : Type(InType) , CompositionChange(Forward<FMassElementBitSet>(Composition)) , AffectedEntities(MoveTemp(Entities))`
- L56 _public function_ `template<typename TEntities> FBufferedNotification(const EMassObservedOperation InType, FMassElementBitSet&& Composition, TEntities&& Entities) : Type(InType) , CompositionChange(MoveTemp(Composition)) , AffectedEntities(TInPlaceType<typename TDecay<TEntities>::Type>(), Forward<TEntities>(Entities))`
- L63 _public function_ `FBufferedNotification(const EMassObservedOperation InType, FMassElementBitSet&& Composition, const FMassArchetypeEntityCollection& Entities) : Type(InType) , CompositionChange(MoveTemp(Composition)) , AffectedEntities(TInPlaceType<typename TDecay<FEntityCollection>::Type>(), Entities)`
- L71 _public function_ `template<typename TEntities> FBufferedNotification(const EMassObservedOperation InType, TEntities&& Entities) : Type(InType) , AffectedEntities(TInPlaceType<typename TDecay<TEntities>::Type>(), Forward<TEntities>(Entities))`
- L77 _public function_ `FBufferedNotification(const EMassObservedOperation InType, const FMassArchetypeEntityCollection& Entities) : Type(InType) , AffectedEntities(TInPlaceType<typename TDecay<FEntityCollection>::Type>(), Entities)`
- L83 _public function_ `bool IsCreationNotification() const`
- L88 _public function_ `void AddHandle(const FMassEntityHandle EntityHandle)`
- L98 _public function_ `inline void AppendEntities(const FMassEntityHandle EntityHandle)`
- L103 _public function_ `void AppendEntities(const TConstArrayView<FMassEntityHandle> InEntityHandles)`
- L115 _public function_ `void AppendEntities(const TConstArrayView<FMassEntityHandle> InEntityHandles, FMassArchetypeEntityCollection&& EntityCollection)`
- L130 _public function_ `template<typename T> requires std::is_same_v<typename TDecay<T>::Type, FMassArchetypeEntityCollection> void AppendEntities(T&& InEntityCollection)`
- L142 _public function_ `void DirtyAffectedEntities()`
- L150 _public function_ `static bool AreCompositionsEqual(const FMassElementBitSet& A, const FMassElementBitSet& B)`
- L157 _private function_ `template<typename TEntities> FEntityCollection& ConvertStoredHandleToCollection(TEntities&& InEntities)`

#### struct `UE::Mass::ObserverManager::FBufferedNotification::FEmptyComposition`  
`struct FEmptyComposition`  
_L40-42_

#### struct `UE::Mass::ObserverManager::FCreationNotificationHandle`  
`struct FCreationNotificationHandle`  
_L169-192_
- desc: Simple handle type representing a entity creation notification as stored by FObserverLock
- L171 _public function_ `bool IsSet() const`
- L176 _public function_ `operator int() const`
- L189 _private member_ `uint32 SerialNumber = 0;` — set upon creation to the value of LockedNotificationSerialNumber. This property's value is checked when the creation handle gets "released" via FMassObserverManager::ReleaseCreationHandle
- L191 _private member_ `int32 OpIndex = INDEX_NONE;`

#### struct `UE::Mass::ObserverManager::FObserverLock`  
`struct FObserverLock`  
_L207-379_
- desc: Once created with MassObserverManager.GetOrMakeObserverLock will prevent triggering observers and instead buffer all the notifications to be sent. Once the FObserverLock gets released it will call MassObserverManager.ResumeExecution that will send out all the buffered notifications. @note that due to the buffering, all the "Remove" operation observers will be sent out later than usually - without locking those observers get triggered before the removal operation is performed, and as such have access to the data "about to be removed". Removal observers sent out after lock release won't have access to that information. There's a special path for freshly created entities, see FCreationContext for more details.
- L209 _public prototype_ `FObserverLock() = default;`
- L210 _public prototype_ `~FObserverLock();`
- L212 _public function_ `TWeakPtr<FMassEntityManager> GetWeakEntityManager() const`
- L217 _public function_ `void MarkCreationNotificationDirty(FCreationNotificationHandle CreationHandle)`
- L224 _public function_ `const FBufferedNotification& GetCreationNotification(FCreationNotificationHandle CreationHandle) const`
- L232 _public function_ `FTransactionallySafeCriticalSection& GetNotificationLock()`
- L238 _private prototype_ `explicit FObserverLock(FMassObserverManager& ObserverManager);`
- L240 _private function_ `int32 GetOrCreateCreationNotification()`
- L252 _private function_ `bool ReleaseCreationNotification(FCreationNotificationHandle CreationHandle)`
- L269 _private function_ `int32 AddCreatedEntity(FMassEntityHandle CreatedEntity)`
- L286 _private function_ `int32 AddCreatedEntities(const TConstArrayView<FMassEntityHandle> InCreatedEntities)`
- L303 _private function_ `int32 AddCreatedEntities(const TConstArrayView<FMassEntityHandle> InCreatedEntities, FMassArchetypeEntityCollection&& InEntityCollection)`
- L322 _private function_ `template<typename T> requires std::is_same_v<typename TDecay<T>::Type, FMassArchetypeEntityCollection> int32 AddCreatedEntitiesCollection(T&& InEntityCollection)`
- L340 _private function_ `template<typename TEntities> void AddNotification(const EMassObservedOperation OperationType, TEntities&& Entities, FMassElementBitSet&& OverlapBitSet)`
- L358 _private prototype_ `void ForceUpdateCurrentThreadID();` — To be called in case of processor forking.
- L364 _private member_ `uint32 OwnerThreadId;` — Identifies the thread where given FObserverLock instance was created. All subsequent operations are expected to be run in the same thread.
- L366 _private member_ `int32 CreationNotificationIndex = INDEX_NONE;`
- L368 _private member_ `TArray<FBufferedNotification> BufferedNotifications;`
- L370 _private member_ `FMassArchetypeEntityCollection::EDuplicatesHandling CollectionCreationDuplicatesHandling = FMassArchetypeEntityCollection::EDuplicatesHandling::NoDuplicates;`
- L373 _private member_ `TWeakPtr<FMassEntityManager> WeakEntityManager;` — Point to outer EntityManager. Used to obtain ObserverManager in type's destructor
- L376 _private member_ `uint32 LockSerialNumber = 0;`
- L378 _private member_ `FTransactionallySafeCriticalSection NotificationLock;`

#### struct `UE::Mass::ObserverManager::FCreationContext`  
`struct FCreationContext`  
_L385-441_
- desc: A dedicated structure for ensuring the "on entities creation" observers get notified only once all other initialization operations are done and this creation context instance gets released.
- L387 _public prototype_ `TArray<FMassArchetypeEntityCollection> GetEntityCollections(const FMassEntityManager& EntityManager) const;`
- L390 _public prototype_ `bool DebugAreEntityCollectionsUpToDate() const;` — Function for debugging/testing purposes. We don't expect users to ever call it, always get collections via GetEntityCollections
- L392 _public prototype_ `~FCreationContext();`
- L394 _public prototype_ `static TSharedRef<FCreationContext> DebugCreateDummyCreationContext();`
- L397 _public prototype_ `TConstArrayView<FMassArchetypeEntityCollection> GetEntityCollections() const;` — `UE_DEPRECATED(5.6, "Use the other GetEntityCollections flavor insteand")`
- L399 _public prototype_ `int32 GetSpawnedNum() const;` — `UE_DEPRECATED(5.6, "Functionality no longer available")`
- L401 _public prototype_ `bool IsDirty() const;` — `UE_DEPRECATED(5.6, "Do not use, internal use only")`
- L403 _public prototype_ `void AppendEntities(const TConstArrayView<FMassEntityHandle>);` — `UE_DEPRECATED(5.6, "Manually adding entities directly to the creation context is not longer supported and is not taking place automatically")`
- L405 _public prototype_ `void AppendEntities(const TConstArrayView<FMassEntityHandle>, FMassArchetypeEntityCollection&&);` — `UE_DEPRECATED(5.6, "Manually adding entities directly to the creation context is not longer supported and is not taking place automatically")`
- L411 _public function_ `void MarkDirty()` — `UE_DEPRECATED_FORGAME(5.6, "Do not use, internal use only")` — Called in response to composition mutating operation - these operations invalidate stored collections
- L417 _private prototype_ `FCreationContext();`
- L419 _private function_ `FCreationContext(TSharedRef<FObserverLock>&& InLock) : Lock(Forward<TSharedRef<FObserverLock>>(InLock))`
- L423 _private function_ `FCreationContext(const TSharedRef<FObserverLock>& InLock) : Lock(InLock)`
- L428 _private function_ `TSharedRef<FObserverLock> GetObserverLock() const`
- L433 _private function_ `bool IsValid() const`
- L439 _private member_ `TSharedRef<FObserverLock> Lock;`
- L440 _private member_ `FCreationNotificationHandle CreationHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSENTITY_API`
- L12 _macro_ `#define UE_CHECK_OWNER_THREADID() checkf(OwnerThreadId == FPlatformTLS::GetCurrentThreadId(), TEXT("%hs: all FObserverLock operations are expected to be run in a single thread"), __FUNCTION__)`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mass` (scope `UE`)
- L18 _namespace_ `namespace ObserverManager` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassObserverProcessor.h` (Public)


#### struct `FMassObserverExecutionContext`  
`struct FMassObserverExecutionContext`  
_L21-57_
- reflection: `USTRUCT()`
- desc: Instances of the type will be fed into FMassRuntimePipeline.AuxData and at execution time will be available to observer processors via FMassExecutionContext.GetAuxData()
- L25 _public prototype_ `FMassObserverExecutionContext() = default;`
- L26 _public function_ `FMassObserverExecutionContext(const EMassObservedOperation InOperation, const TArrayView<const UScriptStruct*> InTypesInOperation) : Operation(InOperation), TypesInOperation(InTypesInOperation)`
- L31 _public function_ `EMassObservedOperation GetOperationType() const`
- L36 _public function_ `TConstArrayView<const UScriptStruct*> GetTypesInOperation() const`
- L41 _public function_ `const UScriptStruct* GetCurrentType() const`
- L46 _public function_ `bool IsValid() const`
- L54 _private member_ `EMassObservedOperation Operation = EMassObservedOperation::MAX;`
- L55 _private member_ `TArrayView<const UScriptStruct*> TypesInOperation;`
- L56 _private member_ `int32 CurrentTypeIndex = INDEX_NONE;`

#### class `UMassObserverProcessor`  
`class UMassObserverProcessor : public UMassProcessor`  
_L82-130_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UMassProcessor`
- desc: Base class for Processors that are used as "observers" of entity operations. An observer declares the types of Mass elements it cares about (Fragments and Tags supported) - via the ObservedTypes array - and the types of operations it wants to be notified of - via ObservedOperations. When an observed operation takes place the processor's regular execution will take place, with ExecutionContext's "auxiliary data" (obtained by calling GetAuxData) being filled with an instance of FMassObserverExecutionContext, that can be used to get information about the type being handled and the kind of operation. To observe multiple types, populate the ObservedTypes array in the constructor: @code UMyObserver::UMyObserver() { ObservedTypes = { FMyFragment::StaticStruct(), FOtherFragment::StaticStruct() }; ObservedOperations = EMassObservedOperationFlags::Add; } @endcode When multiple observed types are added simultaneously, Execute() fires exactly once per entity batch thanks to deduplication in FMassObserverManager::HandleElementsImpl.
- L87 _public prototype_ `UMassObserverProcessor();`
- L88 _public prototype_ `explicit UMassObserverProcessor(const FObjectInitializer& ObjectInitializer);`
- L90 _public prototype_ `EMassObservedOperationFlags GetObservedOperations() const;`
- L95 _public prototype_ `TNotNull<const UScriptStruct*> GetSingleObservedTypeChecked() const;` — Observers support observing multiple fragments now, but if you know there's only one you can fetch it with this function. The function will assert if the processor is configured to observe more types.
- L96 _public prototype_ `const UScriptStruct* GetSingleObservedType() const;`
- L98 _public prototype_ `TNotNull<const UScriptStruct*> GetObservedTypeChecked() const;` — `UE_DEPRECATED(5.8, "UMassObserverProcessor::GetObservedTypeChecked is deprecated now. Use GetSingleObservedTypeChecked")`
- L99 _public prototype_ `TConstArrayView<const UScriptStruct*> GetObservedTypes() const;`
- L102 _protected prototype_ `virtual void PostInitProperties() override;`
- L108 _protected prototype_ `virtual void Register();` — Called from PostInitProperties on the CDO when ObservedOperations is set. By default, registers this class for all entries in ObservedTypes. Override to customize registration.
- L111 _private prototype_ `void InitObserverDefaults();`
- L117 _protected member_ `TObjectPtr<const UScriptStruct> ObservedType;` — `UE_DEPRECATED(5.8, "UMassObserverProcessor::ObservedType is deprecated. Use ObservedTypes instead")` — `UPROPERTY()` — Determines which Fragment or Tag type this given UMassObserverProcessor will be observing (single-type legacy).
- L121 _protected member_ `TArray<TObjectPtr<const UScriptStruct>> ObservedTypes;` — `UPROPERTY()` — Fragment or Tag types this observer watches. Populate this array in the constructor.
- L124 _protected member_ `bool bAutoRegisterWithObserverRegistry = true;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)`
- L127 _protected member_ `EMassObservedOperation Operation = EMassObservedOperation::MAX;` — `UE_DEPRECATED(5.7, "UMassObserverProcessor::Operation is deprecated. Use ObservedOperations instead")`
- L129 _protected member_ `EMassObservedOperationFlags ObservedOperations = EMassObservedOperationFlags::None;`
- L136 _function_ `inline EMassObservedOperationFlags UMassObserverProcessor::GetObservedOperations() const`
- L141 _function_ `inline TNotNull<const UScriptStruct*> UMassObserverProcessor::GetSingleObservedTypeChecked() const`
- L148 _function_ `inline const UScriptStruct* UMassObserverProcessor::GetSingleObservedType() const`
- L154 _function_ `inline TNotNull<const UScriptStruct*> UMassObserverProcessor::GetObservedTypeChecked() const`
- L159 _function_ `inline TConstArrayView<const UScriptStruct*> UMassObserverProcessor::GetObservedTypes() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSENTITY_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mass` (scope `UE`)
- L11 _namespace_ `namespace ObserverManager` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassObserverRegistry.h` (Public)


#### struct `FMassProcessorClassCollection`  
`struct FMassProcessorClassCollection`  
_L19-25_
- reflection: `USTRUCT(meta = (Deprecated = "5.7", DeprecationMessage = "FMassProcessorClassCollection is no longer being used and will be removed in the upcoming engine release"))`
- desc: A wrapper type for a TArray to support having map-of-arrays UPROPERTY members in FMassEntityObserverClassesMap
- L24 _public member_ `TArray<TSubclassOf<UMassProcessor>> ClassCollection;` — `UPROPERTY()`

#### struct `FMassEntityObserverClassesMap`  
`struct FMassEntityObserverClassesMap`  
_L31-49_
- reflection: `USTRUCT(meta = (Deprecated = "5.7", DeprecationMessage = "FMassEntityObserverClassesMap is no longer being used and will be removed in the upcoming engine release"))`
- desc: A wrapper type for a TMap to support having array-of-maps UPROPERTY members in UMassObserverRegistry
- L36 _public function_ `const TMap<TObjectPtr<const UScriptStruct>, FMassProcessorClassCollection>& operator*() const` — a helper accessor simplifying access while still keeping Container private
- L41 _public function_ `TMap<TObjectPtr<const UScriptStruct>, FMassProcessorClassCollection>& operator*()`
- L48 _private member_ `TMap<TObjectPtr<const UScriptStruct>, FMassProcessorClassCollection> Container;` — `UPROPERTY()`

#### class `UMassObserverRegistry`  
`class UMassObserverRegistry : public UObject`  
_L52-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L57 _public prototype_ `UMassObserverRegistry();`
- L59 _public function_ `static UMassObserverRegistry& GetMutable()`
- L63 _public function_ `static const UMassObserverRegistry& Get()`
- L68 _public prototype_ `void RegisterObserver(TNotNull<const UScriptStruct*> ObservedType, uint8 OperationFlags, const TSubclassOf<UMassProcessor>& ObserverClass);`
- L70 _public function_ `void RegisterObserver(TNotNull<const UScriptStruct*> ObservedType, EMassObservedOperationFlags OperationFlags, const TSubclassOf<UMassProcessor>& ObserverClass)`
- L75 _public prototype_ `void RegisterObserver(const UScriptStruct& ObservedType, EMassObservedOperation Operation, const TSubclassOf<UMassProcessor>& ObserverClass);`
- L77 _public typedef_ `using FObserverClassesMap = TMap<TObjectKey<const UScriptStruct>, TArray<FSoftClassPath>>;`
- L80 _protected prototype_ `void OnModulePackagesUnloaded(TConstArrayView<UPackage*> Packages);`
- L82 _protected member_ `FDelegateHandle ModulesUnloadedHandle;`
- L85 _protected member_ `FObserverClassesMap ElementObserverMaps[static_cast<uint8>(EMassObservedOperation::MAX)];`
- L89 _protected member_ `FMassEntityObserverClassesMap FragmentObservers[static_cast<uint8>(EMassObservedOperation::MAX)];` — `UE_DEPRECATED(5.7, "Use ElementObserverMaps instead")` — `UPROPERTY()`
- L93 _protected member_ `FMassEntityObserverClassesMap TagObservers[static_cast<uint8>(EMassObservedOperation::MAX)];` — `UE_DEPRECATED(5.7, "Use ElementObserverMaps instead")` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSENTITY_API`

### `Source/Runtime/MassEntity/Public/MassProcessingContext.h` (Public)


#### struct `UE::Mass::FProcessingContext`  
`struct FProcessingContext`  
_L13-59_
- L16 _public prototype_ `FProcessingContext() = default;` — `UE_DEPRECATED_FORGAME(5.6, "This constructor is deprecated. Use one of the other ones.")`
- L18 _public prototype_ `FProcessingContext(const FProcessingContext&) = default;` — `UE_DEPRECATED_FORGAME(5.6, "This constructor is deprecated. Use one of the other ones.")`
- L20 _public prototype_ `FProcessingContext(FProcessingContext&&) = default;`
- L22 _public prototype_ `explicit FProcessingContext(FMassEntityManager& InEntityManager, const float InDeltaSeconds = 0.f, const bool bInFlushCommandBuffer = true);`
- L23 _public prototype_ `explicit FProcessingContext(const TSharedRef<FMassEntityManager>& InEntityManager, const float InDeltaSeconds = 0.f, const bool bInFlushCommandBuffer = true);`
- L24 _public prototype_ `explicit FProcessingContext(TSharedRef<FMassEntityManager>&& InEntityManager, const float InDeltaSeconds = 0.f, const bool bInFlushCommandBuffer = true);`
- L25 _public prototype_ `explicit FProcessingContext(const TSharedPtr<FMassEntityManager>& InEntityManager, const float InDeltaSeconds = 0.f, const bool bInFlushCommandBuffer = true);`
- L26 _public prototype_ `~FProcessingContext();`
- L28 _public prototype_ `[[nodiscard]] FMassExecutionContext& GetExecutionContext() &;`
- L29 _public prototype_ `[[nodiscard]] FMassExecutionContext&& GetExecutionContext() &&;`
- L30 _public prototype_ `bool GetWillFlushCommands() const;`
- L31 _public prototype_ `float GetDeltaSeconds() const;`
- L33 _public prototype_ `void SetCommandBuffer(TSharedPtr<FMassCommandBuffer>&& InCommandBuffer);`
- L34 _public prototype_ `void SetCommandBuffer(const TSharedPtr<FMassCommandBuffer>& InCommandBuffer);`
- L36 _public prototype_ `const TSharedRef<FMassEntityManager>& GetEntityManager() const;`
- L39 _public member_ `TSharedRef<FMassEntityManager> EntityManager;` — `UE_DEPRECATED_FORGAME(5.6, "Direct access to FProcessingContext.EntityManager has been deprecated. Use GetEntityManager instead.")`
- L42 _public member_ `float DeltaSeconds = 0.f;` — `UE_DEPRECATED_FORGAME(5.6, "Direct access to FProcessingContext.DeltaSeconds has been deprecated. Set it via the constructor instead, read via the getter.")`
- L44 _public member_ `FInstancedStruct AuxData;`
- L51 _public member_ `bool bFlushCommandBuffer = true;` — `UE_DEPRECATED_FORGAME(5.6, "Direct access to FProcessingContext.bFlushCommandBuffer has been deprecated. Set it via the constructor instead, read via the GetWillFlushCommands getter.")` — If set to "true" the MassExecutor will flush commands at the end of given execution function. If "false" the caller is responsible for manually flushing the commands.
- L54 _public member_ `TSharedPtr<FMassCommandBuffer> CommandBuffer;` — `UE_DEPRECATED_FORGAME(5.6, "Direct access to FProcessingContext's CommandBuffer has been deprecated. Use SetCommandBuffer()")`
- L57 _protected member_ `alignas(FMassExecutionContext) uint8 ExecutionContextBuffer[sizeof(FMassExecutionContext)];`
- L58 _protected member_ `FMassExecutionContext* ExecutionContextPtr = nullptr;`
- L66 _function_ `inline FProcessingContext::FProcessingContext(FMassEntityManager& InEntityManager, const float InDeltaSeconds, const bool bInFlushCommandBuffer) : FProcessingContext( (InEntityManager.AsShared()), InDeltaSeconds, bInFlushCommandBuffer)` — @todo remove the deprecation disabling once CommandBuffer and EntityManager are moved to `protected` and un-deprecated (around UE5.8)
- L72 _function_ `inline FProcessingContext::FProcessingContext(const TSharedRef<FMassEntityManager>& InEntityManager, const float InDeltaSeconds, const bool bInFlushCommandBuffer) : EntityManager(InEntityManager) , DeltaSeconds(InDeltaSeconds) , bFlushCommandBuffer(bInFlushCommandBuffer)`
- L80 _function_ `inline FProcessingContext::FProcessingContext(TSharedRef<FMassEntityManager>&& InEntityManager, const float InDeltaSeconds, const bool bInFlushCommandBuffer) : EntityManager(MoveTemp(InEntityManager)) , DeltaSeconds(InDeltaSeconds) , bFlushCommandBuffer(bInFlushCommandBuffer)`
- L88 _function_ `inline FProcessingContext::FProcessingContext(const TSharedPtr<FMassEntityManager>& InEntityManager, const float InDeltaSeconds, const bool bInFlushCommandBuffer) : FProcessingContext(InEntityManager.ToSharedRef(), InDeltaSeconds, bInFlushCommandBuffer)`
- L94 _function_ `inline FMassExecutionContext& FProcessingContext::GetExecutionContext() &`
- L114 _function_ `inline FMassExecutionContext&& FProcessingContext::GetExecutionContext() &&`
- L128 _function_ `inline void FProcessingContext::SetCommandBuffer(TSharedPtr<FMassCommandBuffer>&& InCommandBuffer)`
- L137 _function_ `inline void FProcessingContext::SetCommandBuffer(const TSharedPtr<FMassCommandBuffer>& InCommandBuffer)`
- L146 _function_ `inline const TSharedRef<FMassEntityManager>& FProcessingContext::GetEntityManager() const`
- L151 _function_ `inline bool FProcessingContext::GetWillFlushCommands() const`
- L156 _function_ `inline float FProcessingContext::GetDeltaSeconds() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassProcessingPhaseManager.h` (Public)


#### struct `FMassProcessingPhaseConfig`  
`struct FMassProcessingPhaseConfig`  
_L29-51_
- reflection: `USTRUCT()`
- L34 _public member_ `FName PhaseName;` — `UPROPERTY(EditAnywhere, Category = Mass, config)`
- L37 _public member_ `TSubclassOf<UMassCompositeProcessor> PhaseGroupClass = UMassCompositeProcessor::StaticClass();` — `UPROPERTY(EditAnywhere, Category = Mass, config, NoClear)`
- L40 _public member_ `TArray<TObjectPtr<UMassProcessor>> ProcessorCDOs;` — `UPROPERTY(Transient)`
- L46 _public member_ `TObjectPtr<UMassCompositeProcessor> PhaseProcessor = nullptr;` — `UPROPERTY(Transient)` — this processor is available only in editor since it's used to present the user the order in which processors will be executed when given processing phase gets triggered
- L49 _public member_ `FText Description;` — `UPROPERTY(VisibleAnywhere, Category = Mass, Transient)`

#### struct `FMassProcessingPhase`  
`struct FMassProcessingPhase : public FTickFunction`  
_L54-123_
- inherits: `FTickFunction`
- L56 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhaseEvent, const float );`
- L58 _public prototype_ `FMassProcessingPhase();`
- L59 _public prototype_ `FMassProcessingPhase(const FMassProcessingPhase& Other) = delete;`
- L60 _public prototype_ `FMassProcessingPhase& operator=(const FMassProcessingPhase& Other) = delete;`
- L64 _protected prototype_ `virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;` — FTickFunction interface
- L65 _protected prototype_ `virtual FString DiagnosticMessage() override;`
- L66 _protected prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;`
- L69 _protected prototype_ `void OnParallelExecutionDone(const float DeltaTime);`
- L71 _protected function_ `bool IsConfiguredForParallelMode() const`
- L75 _protected function_ `void ConfigureForParallelMode()`
- L79 _protected function_ `void ConfigureForSingleThreadMode()`
- L84 _protected function_ `bool ShouldTick(const ELevelTick TickType) const`
- L90 _public prototype_ `void Initialize(FMassProcessingPhaseManager& InPhaseManager, const EMassProcessingPhase InPhase, const ETickingGroup InTickGroup, UMassCompositeProcessor& InPhaseProcessor);`
- L91 _public function_ `void AddSupportedTickType(const ELevelTick TickType)`
- L95 _public function_ `void RemoveSupportedTickType(const ELevelTick TickType)`
- L101 _public prototype_ `const UMassCompositeProcessor* DebugGetPhaseProcessor() const;`
- L108 _protected member_ `TObjectPtr<UMassCompositeProcessor> PhaseProcessor = nullptr;` — composite processor representing work to be performed. GC-referenced via AddReferencedObjects
- L110 _protected member_ `UE::Mass::FProcessingQueue ProcessingQueue;`
- L112 _protected member_ `EMassProcessingPhase Phase = EMassProcessingPhase::MAX;`
- L113 _protected member_ `FOnPhaseEvent OnPhaseStart;`
- L114 _protected member_ `FOnPhaseEvent OnPhaseEnd;`
- L117 _private member_ `FMassProcessingPhaseManager* PhaseManager = nullptr;`
- L118 _private member_ `std::atomic<bool> bIsDuringMassProcessing = false;`
- L119 _private member_ `TSharedPtr<FMassObserverManager::FObserverLock> ObserversLockPtr;`
- L121 _private member_ `bool bRunInParallelMode = true;`
- L122 _private member_ `uint8 SupportedTickTypes = 0;`
- L357 _function_ `inline const UMassCompositeProcessor* FMassProcessingPhase::DebugGetPhaseProcessor() const`

#### struct `FMassPhaseProcessorConfigurationHelper`  
`struct FMassPhaseProcessorConfigurationHelper`  
_L126-154_
- L128 _public function_ `FMassPhaseProcessorConfigurationHelper(UMassCompositeProcessor& InOutPhaseProcessor, const FMassProcessingPhaseConfig& InPhaseConfig, UObject& InProcessorOuter, EMassProcessingPhase InPhase) : PhaseProcessor(InOutPhaseProcessor), PhaseConfig(InPhaseConfig), ProcessorOuter(InProcessorOuter), Phase(InPhase)`
- L136 _public prototype_ `void Configure(TArrayView<UMassProcessor* const> DynamicProcessors, TArray<TWeakObjectPtr<UMassProcessor>>& InOutRemovedDynamicProcessors , EProcessorExecutionFlags InWorldExecutionFlags, const TSharedRef<FMassEntityManager>& EntityManager , FMassProcessorDependencySolver::FResult& InOutOptionalResult);` — @param InWorldExecutionFlags - provide EProcessorExecutionFlags::None to let underlying code decide
- L140 _public member_ `UMassCompositeProcessor& PhaseProcessor;`
- L141 _public member_ `const FMassProcessingPhaseConfig& PhaseConfig;`
- L142 _public member_ `UObject& ProcessorOuter;`
- L143 _public member_ `EMassProcessingPhase Phase;`
- L144 _public member_ `bool bInitializeCreatedProcessors = true;`
- L145 _public member_ `bool bIsGameRuntime = true;`
- L151 _public prototype_ `void Configure(TArrayView<UMassProcessor* const> DynamicProcessors, EProcessorExecutionFlags InWorldExecutionFlags , const TSharedPtr<FMassEntityManager>& EntityManager = TSharedPtr<FMassEntityManager>() , FMassProcessorDependencySolver::FResult* OutOptionalResult = nullptr);` — `UE_DEPRECATED(5.6, "This flavor of Configure is deprecated. Please use the one using a TSharedRef<FMassEntityManager> parameter instead")`

#### struct `FMassProcessingPhaseManager`  
`struct FMassProcessingPhaseManager : public FGCObject, public TSharedFromThis<FMassProcessingPhaseManager>`  
_L164-351_
- inherits: `FGCObject,TSharedFromThis<FMassProcessingPhaseManager>`
- desc: MassProcessingPhaseManager owns separate FMassProcessingPhase instances for every ETickingGroup. When activated via Start function it registers and enables the FMassProcessingPhase instances which themselves are tick functions that host UMassCompositeProcessor which they trigger as part of their Tick function. MassProcessingPhaseManager serves as an interface to said FMassProcessingPhase instances and allows initialization with collections of processors (via Initialize function) as well as registering arbitrary functions to be called when a particular phase starts or ends (via GetOnPhaseStart and GetOnPhaseEnd functions).
- L167 _public prototype_ `explicit FMassProcessingPhaseManager(EProcessorExecutionFlags InProcessorExecutionFlags = EProcessorExecutionFlags::None);`
- L168 _public prototype_ `FMassProcessingPhaseManager(const FMassProcessingPhaseManager& Other) = delete;`
- L169 _public prototype_ `FMassProcessingPhaseManager& operator=(const FMassProcessingPhaseManager& Other) = delete;`
- L171 _public function_ `const TSharedPtr<FMassEntityManager>& GetEntityManager() const`
- L175 _public function_ `FMassEntityManager& GetEntityManagerRef()`
- L182 _public function_ `FMassProcessingPhase::FOnPhaseEvent& GetOnPhaseStart(const EMassProcessingPhase Phase)` — Retrieves OnPhaseStart multicast delegate's reference for a given Phase
- L187 _public function_ `FMassProcessingPhase::FOnPhaseEvent& GetOnPhaseEnd(const EMassProcessingPhase Phase)` — Retrieves OnPhaseEnd multicast delegate's reference for a given Phase
- L196 _public prototype_ `void Initialize(UObject& InOwner, TConstArrayView<FMassProcessingPhaseConfig> ProcessingPhasesConfig, const FString& DependencyGraphFileName = TEXT(""));` — Populates hosted FMassProcessingPhase instances with Processors read from MassEntitySettings configuration. Calling this function overrides previous configuration of Phases.
- L199 _public prototype_ `void Deinitialize();` — Needs to be called before destruction, ideally before owner's BeginDestroy (a FGCObject's limitation)
- L201 _public prototype_ `const FGraphEventRef& TriggerPhase(const EMassProcessingPhase Phase, const float DeltaTime, const FGraphEventRef& MyCompletionGraphEvent , ENamedThreads::Type CurrentThread = ENamedThreads::GameThread);`
- L207 _public prototype_ `void Start(UWorld& World);` — Stores EntityManager associated with given world's MassEntitySubsystem and kicks off phase ticking.
- L212 _public prototype_ `void Start(const TSharedRef<FMassEntityManager>& InEntityManager);` — Stores InEntityManager as the entity manager. It also kicks off phase ticking if the given InEntityManager is tied to a UWorld.
- L213 _public prototype_ `void Stop();`
- L214 _public function_ `bool IsRunning() const`
- L227 _public prototype_ `bool IsPaused() const;` — Determine if this Phase Manager is currently paused. While paused, phases will transition as usual, but processors will not be executed. @return True if this PhaseManager is currently paused; else False
- L233 _public prototype_ `void Pause();` — Pause this phase manager at the earliest opportunity (on next FrameEnd phase end). This allows the current phase cycle to complete before the pause takes effect.
- L238 _public prototype_ `void Resume();` — Unpause this phase manager at the earliest opportunity (on next PrePhysics phase start).
- L240 _public prototype_ `FString GetName() const;`
- L243 _public prototype_ `void RegisterDynamicProcessor(UMassProcessor& Processor);` — Registers a dynamic processor. This needs to be a fully formed processor and will be slotted in during the next tick.
- L245 _public prototype_ `void UnregisterDynamicProcessor(UMassProcessor& Processor);` — Removes a previously registered dynamic processor of throws an assert if not found.
- L257 _public function_ `FTickFunction& GetProcessingPhaseTickFunction(EMassProcessingPhase Phase)`
- L264 _public function_ `const FTickFunction& GetProcessingPhaseTickFunction(EMassProcessingPhase Phase) const`
- L272 _public prototype_ `TConstArrayView<FMassProcessingPhase> DebugGetProcessingPhases() const;`
- L273 _public prototype_ `TConstArrayView<FPhaseGraphBuildState> DebugGetProcessingGraphBuildStates() const;`
- L278 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L279 _protected function_ `virtual FString GetReferencerName() const override`
- L285 _protected prototype_ `void RegisterDynamicProcessorInternal(TNotNull<UMassProcessor*> Processor);`
- L286 _protected prototype_ `void UnregisterDynamicProcessorInternal(TNotNull<UMassProcessor*> Processor);`
- L287 _protected prototype_ `void HandlePendingDynamicProcessorOperations(const int32 PhaseIndex);`
- L290 _protected prototype_ `virtual void EnableTickFunctions(const UWorld& World);` — Override this function if you want to modify how the phase tick functions get executed.
- L293 _protected prototype_ `void CreatePhases();` — Creates phase processors instances for each declared phase name, based on MassEntitySettings
- L301 _protected prototype_ `void OnPhaseStart(FMassProcessingPhase& Phase);` — Called by the given Phase at the very start of its execution function (the FMassProcessingPhase::ExecuteTick), even before the FMassProcessingPhase.OnPhaseStart broadcast delegate
- L307 _protected prototype_ `void OnPhaseEnd(FMassProcessingPhase& Phase);` — Called by the given Phase at the very end of its execution function (the FMassProcessingPhase::ExecuteTick), after the FMassProcessingPhase.OnPhaseEnd broadcast delegate
- L309 _protected prototype_ `void OnNewArchetype(const FMassArchetypeHandle& NewArchetype);`
- L312 _protected member_ `FMassProcessingPhase ProcessingPhases[static_cast<uint8>(EMassProcessingPhase::MAX)];`
- L313 _protected member_ `FPhaseGraphBuildState ProcessingGraphBuildStates[static_cast<uint8>(EMassProcessingPhase::MAX)];`
- L314 _protected member_ `TArray<FMassProcessingPhaseConfig> ProcessingPhasesConfig;`
- L315 _protected member_ `TArray<TObjectPtr<UMassProcessor>> DynamicProcessors;`
- L316 _protected member_ `TArray<TWeakObjectPtr<UMassProcessor>> RemovedDynamicProcessors;`
- L323 _protected typedef_ `using FDynamicProcessorOperation = TPair<TStrongObjectPtr<UMassProcessor>, EDynamicProcessorOperationType>;` — using TStrongObjectPtr to not worry about GC while the processor instances are waiting in PendingDynamicProcessors
- L324 _protected member_ `TMpscQueue<FDynamicProcessorOperation> PendingDynamicProcessors[static_cast<uint8>(EMassProcessingPhase::MAX)];`
- L326 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L328 _protected member_ `EMassProcessingPhase CurrentPhase = EMassProcessingPhase::MAX;`
- L330 _protected member_ `TWeakObjectPtr<UObject> Owner;`
- L332 _protected member_ `FDelegateHandle OnNewArchetypeHandle;`
- L334 _protected member_ `EProcessorExecutionFlags ProcessorExecutionFlags = EProcessorExecutionFlags::None;`
- L335 _protected member_ `bool bIsAllowedToTick = false;`
- L337 _protected member_ `bool bIsPaused = false;`
- L338 _protected member_ `bool bIsPauseTogglePending = false;`
- L341 _protected member_ `FDelegateHandle OnDebugEntityManagerInitializedHandle;`
- L342 _protected member_ `FDelegateHandle OnDebugEntityManagerDeinitializedHandle;`
- L344 _protected prototype_ `void OnDebugEntityManagerInitialized(const FMassEntityManager&);`
- L345 _protected prototype_ `void OnDebugEntityManagerDeinitialized(const FMassEntityManager&);`
- L350 _public prototype_ `void Start(const TSharedPtr<FMassEntityManager>& InEntityManager);` — `UE_DEPRECATED(5.6, "This flavor of Start is deprecated. Please use the one using a TSharedRef<FMassEntityManager> parameter instead")`
- L362 _function_ `inline TConstArrayView<FMassProcessingPhase> FMassProcessingPhaseManager::DebugGetProcessingPhases() const`
- L367 _function_ `inline TConstArrayView<FMassProcessingPhaseManager::FPhaseGraphBuildState> FMassProcessingPhaseManager::DebugGetProcessingGraphBuildStates() const`
- L373 _function_ `inline bool FMassProcessingPhaseManager::IsPaused() const`

#### struct `FMassProcessingPhaseManager::FPhaseGraphBuildState`  
`struct FPhaseGraphBuildState`  
_L247-255_
- L249 _public member_ `FMassProcessorDependencySolver::FResult LastResult;`
- L250 _public member_ `bool bNewArchetypes = true;`
- L251 _public member_ `bool bProcessorsNeedRebuild = true;`
- L252 _public member_ `bool bInitialized = false;`
- L254 _public prototype_ `void Reset();`

#### enum `FMassProcessingPhaseManager::EDynamicProcessorOperationType`  
`enum class EDynamicProcessorOperationType : uint8`  
_L317-321_
- L319 _public enumerator_ `Add`
- L320 _public enumerator_ `Remove`

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhaseEvent, const float );`

### `Source/Runtime/MassEntity/Public/MassProcessingQueue.h` (Public)


#### struct `UE::Mass::FProcessingQueue`  
`struct FProcessingQueue`  
_L19-152_
- L23 _public prototype_ `void AddProcessor(TNotNull<UMassProcessor*> InProcessor);` — Add a processor to the queue and resolve dependencies
- L26 _public prototype_ `void AddProcessors(FMassRuntimePipeline& InPipeline);` — Add processors from a pipeline to the queue and resolve dependencies
- L29 _public prototype_ `void AddProcessors(TConstArrayView<UMassProcessor*> InProcessors);` — Add processors to the queue and resolve dependencies
- L32 _public prototype_ `void SetProcessors(TConstArrayView<UMassProcessor*> InProcessors);` — Clear the processing queue and re-initialize with the provided array
- L38 _public prototype_ `void Execute(FProcessingContext&& ProcessingContext, TFunction<void()> OnDoneNotification, ENamedThreads::Type CurrentThread, TFunction<void()> OnPreCommandFlushNotification);` — Immediately execute the processors in the queue. Blocks the calling thread until completion.
- L46 _public prototype_ `FGraphEventRef Execute_GetEventRef(FProcessingContext&& ProcessingContext, TFunction<void()> OnDoneNotification, ENamedThreads::Type CurrentThread, TFunction<void()> OnPreCommandFlushNotification);` — Immediately execute the processors in the queue. Will block the calling threa when bBlockMainThread is true. Returns a graph event the caller can chain on.
- L49 _public prototype_ `void InitQueue();` — Resolve dependencies and build the contention matrices for the current processor list
- L52 _public member_ `bool bBlockMainThread = false;` — Should Execute(...) await the completion of all processors before returning
- L58 _private prototype_ `void RunMainThread(FMassExecutionContext& ExecutionContext);`
- L59 _private prototype_ `void Run(FMassExecutionContext& ExecutionContext);`
- L67 _private prototype_ `void FinalizeAsyncCleanup(FMassExecutionContext& ExecutionContext, const TFunction<void()>& OnDoneNotification, const TFunction<void()>& OnPreCommandFlushNotification);` — Post-runner cleanup shared by blocking and non-blocking paths: spin on the entity manager's processing flag, merge worker command buffers into the execution context, fire callbacks, and flush deferred commands. Callers must ensure any FScopedProcessing they own is destroyed before invoking this (the IsProcessing spin assumes the only outstanding scope was their own).
- L80 _private prototype_ `FQueuedProcessor* GetNextReadyProcessor(TArray<int32>& InOutRemainingIndices);` — Gets the next processor that is ready to execute, sets its state to running and updates contention tracking and other bookkeeping
- L82 _private prototype_ `bool IsComplete() const;`
- L83 _private member_ `std::atomic<int32> PendingMainThreadProcessorCount;`
- L84 _private member_ `std::atomic<int32> PendingProcessorCount;`
- L85 _private member_ `std::atomic<int32> CompletedProcessorCount;`
- L87 _private member_ `std::atomic<int32> ActiveProcessorCount{0};`
- L88 _private member_ `std::atomic<int32> ExecutionConcurrencyHWM{0};`
- L89 _private member_ `std::atomic<int32> ActiveChunkCount{0};`
- L90 _private member_ `std::atomic<int32> ExecutionChunkHWM{0};`
- L94 _private prototype_ `void Release(int32 RequestorIndex);` — Removes RequestorIndex from ActiveItems
- L97 _private prototype_ `bool TryReserve(int32 RequestorIndex);` — Checks if bits in Contention collide with bits in ActiveItems, if not, adds RequestorIndex to ActiveItems
- L99 _private prototype_ `void Reserve(int32 RequestorIndex);` — TryReserve then if that fails, wait until contending items are released and try again
- L102 _private prototype_ `bool ReleaseAndTryReserve(int32 IndexToRelease, int32 IndexToReserve);` — Release a reservation and immediately attempt TryReserve on a different index
- L104 _private prototype_ `void ReleaseAndReserve(int32 IndexToRelease, int32 IndexToReserve);` — ReleaseAndReserve, then if that fails immediately Reserve (which will wait)
- L106 _private prototype_ `bool TryActivateChunk(FQueuedChunk& InChunk, int32 DirectChunkContentionIndex);`
- L107 _private prototype_ `void DeactivateChunk(FQueuedChunk& InChunk);`
- L110 _private prototype_ `void ProcessorFinished(FQueuedProcessor& CompletedProcessor);` — Report that a processor is finished, set its internal state and update queue bookkeeping
- L117 _private prototype_ `void MakeProcessorWorker(FMassExecutionContext& ExecutionContext, FQueuedProcessor* AssignedProcessor = nullptr, bool bInLine = false);` — Make a processor worker and immediately execute the assigned processor If bInline is true then the processor is executed immediately on this thread and this method won't return until it's complete Otherwise, a task is created to run the processor worker and execute the processor asynchronously.
- L118 _private prototype_ `void MakeChunkWorker(FQueuedChunk* AssignedChunk = nullptr, bool bInline = false);`
- L119 _private prototype_ `TSharedPtr<FMassCommandBuffer> GetOrCreateCommandBuffer();`
- L120 _private prototype_ `void ReturnCommandBufferToPool(TSharedPtr<FMassCommandBuffer>& InCommandBuffer);`
- L121 _private prototype_ `void InitializeExplicitDependencies();`
- L122 _private prototype_ `bool CheckForValidDependencies();`
- L125 _private prototype_ `int32 ComputeGraphDepthRecursive(int32 ProcessorIndex, TArray<int32>& Memo);` — Recursively computes dependency depth
- L128 _private member_ `FContentionMatrix ContentionMatrix;` — Tracks all global contention
- L131 _private member_ `FActiveContentionTracker ActiveContentionTracker{ ContentionMatrix };` — Tracks active global contention
- L133 _private member_ `FContentionMatrix ChunkContentionMatrix;`
- L135 _private member_ `FActiveChunkTracker ActiveChunkContentionTracker;` — Only tracks possible contention of direct chunk access (i.e. contention that can only occur accessing the same chunk)
- L137 _private member_ `TArray<FQueuedProcessor> ProcessorQueue;`
- L140 _private member_ `TArray<int32> RemainingMainThreadProcessorIndices;` — array of indices in ProcessorQueue that still need to execute on the main thread
- L143 _private member_ `TArray<int32> RemainingProcessorIndices;` — array of indices in ProcessorQueue that still need to execute
- L145 _private member_ `bool bProcessorListDirty = false;`
- L146 _private member_ `FMassRuntimePipeline Processors;`
- L147 _private member_ `int32 MainThreadProcessorCount = 0;`
- L149 _private member_ `FRWLock CommandBuffersLock;`
- L150 _private member_ `std::atomic<uint32> QueueChangeTracker{ 0 };`
- L151 _private member_ `TArray<TSharedPtr<FMassCommandBuffer>> CommandBufferPool;`

#### enum `UE::Mass::FProcessingQueue::EThreadFlag`  
`enum class EThreadFlag : uint8`  
_L71-77_
- L73 _public enumerator_ `MainThread = 1 << 0`
- L74 _public enumerator_ `OffMainThread = 1 << 1`
- L76 _public enumerator_ `Any = MainThread | OffMainThread`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MASSENTITY_API`
- L15 _macro_ `#define MASS_CONCURRENCY_STATS (!UE_BUILD_SHIPPING) && MASS_DO_PARALLEL`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassProcessingQueueTypes.h` (Public)


#### struct `UE::Mass::FContentionMatrix`  
`struct FContentionMatrix`  
_L33-132_
- desc: Dynamically sized bit-matrix to track contention between items.
- L36 _public typedef_ `using WordType = uint64;`
- L37 _public member_ `static constexpr int32 BitsPerWord = 64;`
- L38 _public member_ `static constexpr int32 BitsPerWordLog2 = 6;`
- L40 _public prototype_ `FContentionMatrix() = default;`
- L42 _public function_ `explicit FContentionMatrix(int32 InNumElements)`
- L51 _public function_ `void Init(int32 InNumElements)` — Resizes the matrix to hold InNumElements. This clears all existing data.
- L66 _public function_ `FORCEINLINE int32 GetSize() const`
- L71 _public function_ `FORCEINLINE int32 GetWordsPerRow() const`
- L77 _public function_ `FORCEINLINE void Clear()` — Zero the entire matrix.
- L83 _public function_ `void Set(int32 RowIndex, int32 ColumnIndex)` — Set contends(i,j) = true
- L97 _public function_ `void SetMutual(int32 RowIndex, int32 ColumnIndex)` — Set contends(i,j) = true and contends(j,i) = true
- L104 _public function_ `FORCEINLINE bool Test(int32 RowIndex, int32 ColumnIndex) const` — Test contention(i,j)
- L116 _public function_ `FORCEINLINE const WordType* GetRowWordPointer(int32 RowIndex) const` — raw pointer to the start of the row's words.
- L123 _private member_ `int32 NumElements = 0;`
- L124 _private member_ `int32 WordsPerRow = 0;`
- L126 _private member_ `TArray<WordType> MatrixBits;`
- L128 _private function_ `FORCEINLINE bool IsValidIndex(int32 Index) const`

#### struct `UE::Mass::FQueuedChunk`  
`struct FQueuedChunk`  
_L137-173_
- desc: A single chunk processing callback generated by FMassEntityQuery::ForEachEntityChunk.
- L147 _public prototype_ `FQueuedChunk() = default;`
- L148 _public prototype_ `FQueuedChunk(FProcessorWorker* InOwningProcessorWorker, FMassChunkProcessingQueueParams&& InParams);`
- L149 _public prototype_ `FQueuedChunk(FQueuedChunk&& Other) noexcept;`
- L151 _public prototype_ `FQueuedChunk(const FQueuedChunk&) = delete;`
- L152 _public prototype_ `FQueuedChunk& operator=(const FQueuedChunk&) = delete;`
- L153 _public prototype_ `FQueuedChunk& operator=(FQueuedChunk&& Other) = delete;`
- L155 _public function_ `uint64 GetChunkID() const`
- L160 _public function_ `bool IsSameArchetypeChunk(const FQueuedChunk& Other) const`
- L165 _public member_ `EState State = EState::Pending;`
- L166 _public member_ `int32 ActiveChunkSlotIndex = INDEX_NONE;`
- L169 _public member_ `int32 RemainingDependencyCount = 0;` — Count of how many "ProcessAfter" chunks remain (includes "ProcessBefore" from other chunks/processors)
- L170 _public member_ `FProcessorWorker* OwningProcessorWorker = nullptr;`
- L171 _public member_ `const FQueryInfo* QueryInfo = nullptr;`
- L172 _public member_ `FMassChunkProcessingQueueParams Params;`

#### enum `UE::Mass::FQueuedChunk::EState`  
`enum class EState : uint8`  
_L139-145_
- L141 _public enumerator_ `Pending`
- L142 _public enumerator_ `Running`
- L143 _public enumerator_ `Complete`
- L144 _public enumerator_ `MAX`

#### class `UE::Mass::FActiveChunkTracker`  
`class FActiveChunkTracker`  
_L176-407_
- desc: Tracks which FQueuedChunks are active to manage contention
- L179 _public typedef_ `using WordType = uint64;`
- L180 _public member_ `static constexpr int32 MaxActiveChunks = UE_MASS_MAX_ACTIVE_CHUNKS;`
- L181 _public member_ `static constexpr uint64 InvalidChunkID = 0;`
- L182 _public prototype_ `FActiveChunkTracker() = default;`
- L184 _public function_ `void Init(const FContentionMatrix& InMatrix)`
- L207 _public function_ `bool TryAcquireAccess(FQueuedChunk& Chunk, int32 DirectChunkContentionIndex)` — Checks active contention and reserves the chunk's contention index if safe
- L328 _public function_ `void ReleaseAccess(FQueuedChunk& Chunk, int32 DirectChunkContentionIndex)`
- L371 _private prototype_ `void OnSlotExhausted();` — Logs a once-per-process warning when the tracker runs out of slots. Defined out-of-line to keep logging deps out of this header.
- L373 _private member_ `const FContentionMatrix* MatrixRef = nullptr;`
- L374 _private member_ `int32 WordsPerRow = 0;`
- L376 _private member_ `alignas(64) std::atomic<uint64> ChunkIDs[MaxActiveChunks];`
- L377 _private member_ `std::atomic_flag SlotLocks[MaxActiveChunks];`
- L378 _private member_ `int32 SlotRefCounts[MaxActiveChunks];`
- L380 _private member_ `std::atomic_flag SlotAssignmentLock;`
- L381 _private member_ `TArray<WordType> BitmaskBuffer;`
- L383 _private function_ `FORCEINLINE WordType* GetSlotBits(int32 SlotIndex)`
- L388 _private function_ `FORCEINLINE void LockSlot(int32 SlotIndex)`
- L396 _private function_ `FORCEINLINE void UnlockSlot(int32 SlotIndex)`
- L401 _private function_ `FORCEINLINE void AddJobToBitmask(WordType* SlotBits, int32 JobIndex)`

#### struct `UE::Mass::FActiveContentionTracker`  
`struct FActiveContentionTracker`  
_L412-538_
- desc: Uses a pre-calculated FContentionMatrix to help dynamically track active contending items
- L415 _public typedef_ `using WordType = uint64;`
- L416 _public member_ `static constexpr int32 BitsPerWord = 64;`
- L417 _public member_ `static constexpr int32 BitsPerWordLog2 = 6;`
- L419 _public function_ `FActiveContentionTracker(const FContentionMatrix& InMatrix) : Matrix(InMatrix)`
- L425 _public function_ `void Init()`
- L431 _public function_ `bool TryActivate(int32 ItemIndex)`
- L459 _public function_ `FORCEINLINE bool Deactivate(int32 ItemIndex)`
- L466 _public function_ `FORCEINLINE bool HasAnyActiveContention(int32 ItemIndex)`
- L479 _public function_ `FORCEINLINE int32 GetActiveContentionCount(int32 ItemIndex)`
- L492 _private member_ `const FContentionMatrix& Matrix;`
- L493 _private member_ `TArray<int32> ActiveContenderCount;`
- L495 _private member_ `FCriticalSection ActiveContenderCriticalSection;`
- L497 _private function_ `FORCEINLINE bool IsValidIndex(int32 Index) const`
- L502 _private function_ `void UpdateContentionCounts(int32 ItemIndex, int32 Delta)`

#### struct `UE::Mass::FActiveChunkSet`  
`struct FActiveChunkSet`  
_L541-719_
- desc: Tracks which chunks are actively being processed with a refcount
- L550 _public member_ `static constexpr int32 Capacity = 32;`
- L551 _public member_ `static constexpr uint64 EmptyValue = 0;`
- L552 _public member_ `const int32 MaxSlots;`
- L554 _public function_ `FActiveChunkSet(int32 InMaxSlots) : MaxSlots(InMaxSlots)`
- L573 _public function_ `bool TryAddExclusive(uint64 ID)` — Adds an ID to the set. Returns true if added, false if it was already present.
- L622 _public function_ `int32 AddGetRefCount(uint64 ID)` — Adds the ID to the set if not present Increments the refcount for the ID Returns the new refcount
- L670 _public function_ `void Remove(uint64 ID)` — Decrement the refcount for ID and remove it if the count is 0
- L702 _public function_ `bool Contains(uint64 ID) const` — Checks if the ID exists in the set.
- L717 _private member_ `alignas(64) std::atomic<uint64> Slots[Capacity];` — alignas(64) to avoid false sharing
- L718 _private member_ `alignas(64) std::atomic<int32> RefCounts[Capacity];`

#### struct `UE::Mass::FActiveChunkSet::FChunkSlot`  
`struct FChunkSlot`  
_L544-548_
- L546 _public member_ `uint64 Index;`

#### struct `UE::Mass::FChangeScope`  
`template <typename T> struct FChangeScope`  
_L726-742_
- desc: Increments a change-tracking atomic variable when leaving a scope. Used with FChangeListener for efficient synchronization of workers waiting for resources.
- L728 _public function_ `explicit FChangeScope(std::atomic<T>& InTrackingValue) : Tracker(InTrackingValue)`
- L732 _public prototype_ `FChangeScope(const FChangeScope&) = delete;`
- L733 _public prototype_ `FChangeScope& operator=(const FChangeScope&) = delete;`
- L734 _public prototype_ `FChangeScope(FChangeScope&& Other) = delete;`
- L736 _public function_ `~FChangeScope()`
- L741 _private member_ `std::atomic<T>& Tracker;`

#### struct `UE::Mass::FChangeListener`  
`template <typename T> struct FChangeListener`  
_L751-782_
- desc: Busy-waits for an atomic variable (incremented by FChangeScope) to change. The spin marks itself oversubscribed so the scheduler can bring up a standby worker to make progress on the queue - it mitigates, but does not eliminate, the busy-wait (and can't help once the worker pool is already saturated).
- L753 _public function_ `explicit FChangeListener(std::atomic<T>& InValueToTrack) : ValueToTrack(InValueToTrack)`
- L760 _public function_ `void WaitForChange()`
- L780 _private member_ `std::atomic<T>& ValueToTrack;`
- L781 _private member_ `T InitialValue;`

#### struct `UE::Mass::FDataAccess`  
`struct FDataAccess`  
_L785-799_
- desc: Single struct to specify data access for a query
- L787 _public member_ `FElementBitSet DirectReadsElements;`
- L788 _public member_ `FElementBitSet DirectWritesElements;`
- L789 _public member_ `FElementBitSet IndirectReadsElements;`
- L790 _public member_ `FElementBitSet IndirectWritesElements;`
- L791 _public member_ `FMassExternalSubsystemBitSet ReadsSubsystems;`
- L792 _public member_ `FMassExternalSubsystemBitSet WritesSubsystems;`
- L794 _public prototype_ `void Add(const FDataAccess& Other);`
- L795 _public prototype_ `bool SubsystemsCollide(const FDataAccess& Other) const;`
- L796 _public prototype_ `bool CollidesWithIndirect(const FDataAccess& Other) const;`
- L797 _public prototype_ `bool CollidesWithDirect(const FDataAccess& Other) const;`
- L798 _public prototype_ `void SetFragmentWriteRequirements(const FMassFragmentRequirements& FragmentRequirements);`

#### struct `UE::Mass::FQueryInfo`  
`struct FQueryInfo`  
_L802-817_
- desc: Stores processing queue-specific data about a FMassEntityQuery
- L804 _public member_ `bool bChunksRequireGameThread = false;`
- L807 _public member_ `int32 QueryContentionIndex = INDEX_NONE;` — Contention index to run the query (gather chunks but not execute)
- L810 _public member_ `int32 ChunkGlobalContentionIndex = INDEX_NONE;` — Contention index for cross-chunk contention on each chunk processed
- L813 _public member_ `int32 ChunkContentionIndex = INDEX_NONE;` — Contention index for direct chunk contention on each chunk processed
- L815 _public member_ `FDataAccess DataAccess;`
- L816 _public member_ `const FMassEntityQuery* SourceQuery = nullptr;`

#### struct `UE::Mass::FQueuedProcessor`  
`struct FQueuedProcessor`  
_L820-911_
- desc: A single processor managed by the processing queue.
- L837 _public member_ `EState State = EState::MAX;` — Current state in the execution pipeline
- L839 _public member_ `TNotNull<UMassProcessor*> Processor;`
- L846 _public member_ `bool bAggregateThreadRequirements = true;` — If the processor or any query requires game thread execution, then aggregate that requirement to all queries and the processor itself. Useful for emulating the legacy processor behavior.
- L853 _public member_ `bool bAggregateRequirements;` — Aggregate all data access requirements of the processor and queries to all queries and the processor itself Useful for emulating the legacy processor behavior. Set from bAggregateRequirements on the input processor.
- L856 _public member_ `int32 ContentionIndex = INDEX_NONE;` — Contention table index for this processor (does not include query requirements)
- L859 _public member_ `int32 QueryCount = 1;` — Queries will follow te owning processor in the contention table, count is used to get the correct index
- L862 _public member_ `std::atomic<int32> RemainingDependencyCount{ 0 };` — Explicit dependencies remaining (ExecuteBefore/ExecuteAfter)
- L865 _public member_ `int32 DependencyCount = 0;` — Total explicit dependency count (ExecuteBefore/ExecuteAfter)
- L868 _public member_ `TArray<int32, TInlineAllocator<8>> DependentProcessorIndices;` — Indices of items that depend explicitly on this processor (within the FProcessingQueue's processor array)
- L874 _public member_ `int32 GraphDepth = 0;` — The length of the longest dependency chain starting from this processor. 0 = Leaf node (nothing depends on this).
- L876 _public member_ `FDataAccess DataAccess;`
- L878 _public member_ `TArray<FQueryInfo> QueryInfos;`
- L879 _public member_ `int32 CurrentQueryIndex = INDEX_NONE;`
- L881 _public member_ `bool bRequiresGameThread = true;`
- L883 _public prototype_ `void InitThreadRequirement();`
- L884 _public prototype_ `void InitWriteContention(FContentionMatrix& ContentionMatrix, FQueuedProcessor& Other);`
- L885 _public prototype_ `void InitWriteContention(FContentionMatrix& ContentionMatrix, int32 MyQueryIndex, FQueuedProcessor& Other);`
- L886 _public prototype_ `void InitCrossChunkWriteContention(FContentionMatrix& ContentionMatrix, int32 MyQueryIndex, FQueuedProcessor& Other, int32 OtherQueryIndex);`
- L887 _public prototype_ `void InitChunkWriteContention(FContentionMatrix& ContentionMatrix, int32 MyQueryIndex, FQueuedProcessor& Other, int32 OtherQueryIndex);`
- L889 _public prototype_ `explicit FQueuedProcessor(TNotNull<UMassProcessor*> InProcessor);`
- L891 _public prototype_ `void PrepareForExecute();`
- L893 _public prototype_ `const FQueryInfo& GetCurrentQueryInfo() const;`
- L894 _public prototype_ `void SetCurrentQuery(const FMassEntityQuery* SourceQuery);`
- L897 _public prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(ChunkQueueAccessDetector);` — Multithreading access detector to ensure ChunkQueue is not altered concurrently
- L900 _public member_ `TArray<FQueuedChunk> ChunkQueue;` — Chunks that could not be executed immediately during the query and were queued.
- L903 _public member_ `TArray<int32> PendingChunkIndices;` — List of indices into ChunkQueue that have not been processed yet.
- L906 _public member_ `TArray<UE::Tasks::FTask> DispatchedChunkTasks;` — Async chunk tasks dispatched during the current query
- L908 _public member_ `FProcessorWorker* DebugCurrentProcessorWorker = nullptr;`

#### enum `UE::Mass::FQueuedProcessor::EState`  
`enum class EState : uint8`  
_L822-835_
- L825 _public enumerator_ `WaitingForDependencies` — Initialized, and waiting for explicit ordering dependencies
- L828 _public enumerator_ `Ready` — Explicit dependencies met, ready to activate (will activate when at the front of the queue and no contending items are active)
- L831 _public enumerator_ `Running` — Currently running
- L833 _public enumerator_ `Completed`
- L834 _public enumerator_ `MAX`

#### class `UE::Mass::FProcessorWorker`  
`class FProcessorWorker`  
_L914-952_
- desc: A worker to execute queued processors
- L917 _public prototype_ `FProcessorWorker(FProcessingQueue& InQueue, const FMassExecutionContext& InExecutionContext, bool bInInlineExecution = false);`
- L918 _public prototype_ `~FProcessorWorker();`
- L920 _public prototype_ `void AssignProcessor(FQueuedProcessor* QueuedProcessor);`
- L922 _public prototype_ `void QueueChunk(FMassChunkProcessingQueueParams&& Params);`
- L923 _public function_ `const FQueryInfo& GetCurrentQueryInfo() const`
- L928 _public prototype_ `void ExecuteProcessor();`
- L929 _public prototype_ `void WaitForQueryResources();`
- L930 _public prototype_ `void ProcessChunks();`
- L931 _public prototype_ `void Cleanup();`
- L932 _public prototype_ `void ChunkDone(FQueuedChunk* InChunk);`
- L939 _public prototype_ `void ExecuteChunkInline(FMassChunkProcessingQueueParams&& Params);` — Force-inline mode: execute a single chunk immediately on the calling thread without touching the chunk queue, contention tracker, or ChunksRemaining counter. Replaces the QueueChunk callback path entirely when mass.ForceInlineProcessorExecution is set.
- L941 _public member_ `FProcessingQueue& OwningQueue;`
- L942 _public member_ `const FMassExecutionContext& GlobalExecutionContext;`
- L943 _public member_ `bool bInlineExecution = false;`
- L944 _public member_ `FQueuedProcessor* RunningProcessor = nullptr;`
- L945 _public member_ `std::atomic<int32> ChunksRemaining{ 0 };`
- L946 _public member_ `TSharedPtr<FMassCommandBuffer> CommandBuffer;`
- L947 _public member_ `int32 GlobalChunkContentionIndex = INDEX_NONE;`
- L950 _public member_ `FMassExecutionContext* DebugCurrentExecutionContext = nullptr;`

#### class `UE::Mass::FChunkWorker`  
`class FChunkWorker`  
_L955-975_
- desc: A worker to process queued chunks
- L959 _public prototype_ `FChunkWorker(FProcessingQueue& InQueue, FQueuedChunk* InChunk, bool UseChunkCommandBuffer = false);`
- L960 _public prototype_ `~FChunkWorker();`
- L961 _public prototype_ `void ExecuteChunk(bool bInlineExecution);`
- L962 _public prototype_ `void Cleanup();`
- L963 _public function_ `void AssignChunk(FQueuedChunk* InChunk)`
- L967 _public prototype_ `TSharedPtr<FMassCommandBuffer>& GetOrCreateCommandBuffer();`
- L969 _public member_ `FProcessingQueue& OwningQueue;`
- L970 _public member_ `FQueuedChunk* Chunk = nullptr;`
- L971 _public member_ `bool bUseContextCommandBuffer = false;`
- L974 _public member_ `TSharedPtr<FMassCommandBuffer> CommandBuffer;` — The buffer is created in the thread this worker uses, and registered with the queue to be merged/flushed

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSENTITY_API`
- L15 _macro_ `#define UE_MASS_MAX_ACTIVE_CHUNKS 512`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassProcessingTypes.h` (Public)


#### enum `EProcessorExecutionFlags`  
`enum class EProcessorExecutionFlags : uint8`  
_L23-34_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L25 _public enumerator_ `None = 0 UMETA(Hidden)`
- L26 _public enumerator_ `Standalone = 1 << 0`
- L27 _public enumerator_ `Server = 1 << 1`
- L28 _public enumerator_ `Client = 1 << 2`
- L29 _public enumerator_ `Editor = 1 << 3`
- L30 _public enumerator_ `EditorWorld = 1 << 4`
- L31 _public enumerator_ `AllNetModes = Standalone | Server | Client UMETA(Hidden)`
- L32 _public enumerator_ `AllWorldModes = Standalone | Server | Client | EditorWorld UMETA(Hidden)`
- L33 _public enumerator_ `All = Standalone | Server | Client | Editor | EditorWorld UMETA(Hidden)`

#### struct `FProcessorAuxDataBase`  
`struct FProcessorAuxDataBase`  
_L38-41_
- reflection: `USTRUCT()`

#### struct `FMassProcessingContext_DEPRECATED`  
`struct FMassProcessingContext_DEPRECATED`  
_L44-56_
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "5.6"))`
- L49 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY()`
- L52 _public member_ `FInstancedStruct AuxData;` — `UPROPERTY()`
- L55 _public member_ `bool bFlushCommandBuffer = true;` — `UPROPERTY()`

#### struct `FMassRuntimePipeline`  
`struct FMassRuntimePipeline`  
_L68-170_
- reflection: `USTRUCT()`
- desc: Runtime-usable array of MassProcessor copies
- L74 _private member_ `TArray<TObjectPtr<UMassProcessor>> Processors;` — `UPROPERTY()`
- L76 _private member_ `EProcessorExecutionFlags ExecutionFlags = EProcessorExecutionFlags::None;`
- L79 _public prototype_ `explicit FMassRuntimePipeline(EProcessorExecutionFlags WorldExecutionFlags = EProcessorExecutionFlags::None);`
- L80 _public prototype_ `FMassRuntimePipeline(TConstArrayView<TObjectPtr<UMassProcessor>> SeedProcessors, EProcessorExecutionFlags WorldExecutionFlags);`
- L81 _public prototype_ `FMassRuntimePipeline(TConstArrayView<UMassProcessor*> SeedProcessors, EProcessorExecutionFlags WorldExecutionFlags);`
- L83 _public prototype_ `void Reset();`
- L84 _public prototype_ `void Initialize(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager);`
- L87 _public prototype_ `void SetProcessors(TArrayView<UMassProcessor*> InProcessors);` — Copies the given array over to this FMassRuntimePipeline instance.
- L90 _public prototype_ `void SetProcessors(TArray<TObjectPtr<UMassProcessor>>&& InProcessors);` — Directly moves the contents of given array to the Processors member array.
- L93 _public prototype_ `void CreateFromArray(TConstArrayView<const UMassProcessor*> InProcessors, UObject& InOwner);` — Creates runtime copies of UMassProcessors given in InProcessors input parameter, using InOwner as new UMassProcessors' outer.
- L96 _public prototype_ `void InitializeFromArray(TConstArrayView<const UMassProcessor*> InProcessors, UObject& InOwner, const TSharedRef<FMassEntityManager>& EntityManager);` — Calls CreateFromArray and calls Initialize on all processors afterwards.
- L100 _public prototype_ `void InitializeFromClassArray(TConstArrayView<TSubclassOf<UMassProcessor>> InProcessorClasses, UObject& InOwner, const TSharedRef<FMassEntityManager>& EntityManager);` — Creates runtime instances of UMassProcessors for each processor class given via InProcessorClasses. The instances will be created with InOwner as outer.
- L104 _public prototype_ `void AppendOrOverrideRuntimeProcessorCopies(TConstArrayView<const UMassProcessor*> InProcessors, UObject& InOwner);` — Creates a runtime instance of every processors in the given InProcessors array. If a processor of that class already exists in Processors array it gets overridden. Otherwise it gets added to the end of the collection.
- L112 _public prototype_ `void AppendUniqueRuntimeProcessorCopies(TConstArrayView<const UMassProcessor*> InProcessors, UObject& InOwner, const TSharedRef<FMassEntityManager>& EntityManager);` — Creates a runtime instance of every processors in the given array if there's no processor of that class in Processors already. Call this function when adding processors to an already configured FMassRuntimePipeline instance. If you're creating one from scratch calling any of the InitializeFrom* methods will be more efficient (and will produce same results) or call AppendOrOverrideRuntimeProcessorCopies. NOTE: there's a change in functionality since 5.6 - the function will no longer create duplicates for processors returning true from ShouldAllowMultipleInstances
- L115 _public prototype_ `void AppendProcessor(UMassProcessor& InProcessor);` — Adds InProcessor(s) to Processors without any additional checks
- L116 _public prototype_ `void AppendProcessors(TArrayView<TObjectPtr<UMassProcessor>> InProcessors);`
- L117 _public prototype_ `void AppendProcessors(TArray<TObjectPtr<UMassProcessor>>&& InProcessors);`
- L120 _public prototype_ `bool AppendUniqueProcessor(UMassProcessor& Processor);` — @return true if the given processor has indeed been added, i.e. will return false if Processor was already part of the pipeline.
- L123 _public prototype_ `void AppendProcessor(TSubclassOf<UMassProcessor> ProcessorClass, UObject& InOwner);` — Creates an instance of ProcessorClass and adds it to Processors without any additional checks
- L126 _public prototype_ `bool RemoveProcessor(const UMassProcessor& InProcessor);` — @return whether the given processor has been removed from hosted processors collection
- L129 _public prototype_ `UMassCompositeProcessor* FindTopLevelGroupByName(const FName GroupName);` — goes through Processor looking for a UMassCompositeProcessor instance which GroupName matches the one given as the parameter
- L131 _public prototype_ `bool HasProcessorOfExactClass(TSubclassOf<UMassProcessor> InClass) const;`
- L132 _public prototype_ `bool IsEmpty() const;`
- L134 _public prototype_ `int32 Num() const;`
- L135 _public prototype_ `TConstArrayView<TObjectPtr<UMassProcessor>> GetProcessors() const;`
- L136 _public function_ `TConstArrayView<UMassProcessor*> GetProcessorsView() const`
- L140 _public prototype_ `TArrayView<TObjectPtr<UMassProcessor>> GetMutableProcessors();`
- L143 _public prototype_ `TArray<TObjectPtr<UMassProcessor>>&& MoveProcessorsArray();` — Returns Processors array using move semantics. This operation clears out this FMassRuntimePipeline instance.
- L151 _public prototype_ `void SortByExecutionPriority();` — Sorts processors aggregates in Processors array so that the ones with higher ExecutionPriority are executed first The function will also remove nullptrs, if any, before sorting.
- L157 _public prototype_ `void Initialize(UObject& Owner);` — `UE_DEPRECATED(5.6, "This flavor of Initialize is deprecated. Please use the one requiring a FMassEntityManager parameter")`
- L160 _public prototype_ `void InitializeFromArray(TConstArrayView<const UMassProcessor*> InProcessors, UObject& InOwner);` — `UE_DEPRECATED(5.6, "This flavor of InitializeFromArray is deprecated. Please use the one requiring a FMassEntityManager parameter")`
- L163 _public prototype_ `void InitializeFromClassArray(TConstArrayView<TSubclassOf<UMassProcessor>> InProcessorClasses, UObject& InOwner);` — `UE_DEPRECATED(5.6, "This flavor of InitializeFromClassArray is deprecated. Please use the one requiring a FMassEntityManager parameter")`
- L166 _public prototype_ `void AppendUniqueRuntimeProcessorCopies(TConstArrayView<const UMassProcessor*> InProcessors, UObject& InOwner);` — `UE_DEPRECATED(5.6, "This flavor of AppendUniqueRuntimeProcessorCopies is deprecated. Please use the one requiring a FMassEntityManager parameter")`
- L169 _public prototype_ `void SetProcessors(TArray<UMassProcessor*>&& InProcessors);` — `UE_DEPRECATED(5.6, "This flavor of SetProcessors is deprecated. Please use one of the others.")`
- L204 _function_ `inline FMassRuntimePipeline::FMassRuntimePipeline(EProcessorExecutionFlags WorldExecutionFlags) : ExecutionFlags(WorldExecutionFlags)`
- L210 _function_ `inline bool FMassRuntimePipeline::IsEmpty() const`
- L215 _function_ `inline int32 FMassRuntimePipeline::Num() const`
- L220 _function_ `inline TConstArrayView<TObjectPtr<UMassProcessor>> FMassRuntimePipeline::GetProcessors() const`
- L225 _function_ `inline TArrayView<TObjectPtr<UMassProcessor>> FMassRuntimePipeline::GetMutableProcessors()`
- L230 _function_ `inline TArray<TObjectPtr<UMassProcessor>>&& FMassRuntimePipeline::MoveProcessorsArray()`

#### enum `EMassProcessingPhase`  
`enum class EMassProcessingPhase : uint8`  
_L173-182_
- reflection: `UENUM()`
- L175 _public enumerator_ `PrePhysics`
- L176 _public enumerator_ `StartPhysics`
- L177 _public enumerator_ `DuringPhysics`
- L178 _public enumerator_ `EndPhysics`
- L179 _public enumerator_ `PostPhysics`
- L180 _public enumerator_ `FrameEnd`
- L181 _public enumerator_ `MAX`

#### struct `FMassProcessorOrderInfo`  
`struct FMassProcessorOrderInfo`  
_L184-199_
- L194 _public member_ `FName Name;`
- L195 _public member_ `UMassProcessor* Processor = nullptr;`
- L196 _public member_ `EDependencyNodeType NodeType = EDependencyNodeType::Invalid;`
- L197 _public member_ `TArray<FName> Dependencies;`
- L198 _public member_ `int32 SequenceIndex = INDEX_NONE;`

#### enum `FMassProcessorOrderInfo::EDependencyNodeType`  
`enum class EDependencyNodeType : uint8`  
_L186-192_
- L188 _public enumerator_ `Invalid`
- L189 _public enumerator_ `Processor`
- L190 _public enumerator_ `GroupStart`
- L191 _public enumerator_ `GroupEnd`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSENTITY_API`
- L14 _macro_ `#define MASS_DO_PARALLEL !UE_SERVER`
- L35 _prototype_ `ENUM_CLASS_FLAGS(EProcessorExecutionFlags);`
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace Mass` (scope `UE`)
- L62 _typedef_ `using FMassProcessingContext = UE::Mass::FProcessingContext;`

### `Source/Runtime/MassEntity/Public/MassProcessor.h` (Public)


#### enum `EProcessorCompletionStatus`  
`enum class EProcessorCompletionStatus : uint8`  
_L33-39_
- L35 _public enumerator_ `Invalid`
- L36 _public enumerator_ `Threaded`
- L37 _public enumerator_ `Postponed`
- L38 _public enumerator_ `Done`

#### struct `FMassProcessorExecutionOrder`  
`struct FMassProcessorExecutionOrder`  
_L42-55_
- reflection: `USTRUCT()`
- L48 _public member_ `FName ExecuteInGroup = FName();` — `UPROPERTY(EditAnywhere, Category = Processor, config)` — Determines which processing group this processor will be placed in. Leaving it empty ("None") means "top-most group for my ProcessingPhase"
- L51 _public member_ `TArray<FName> ExecuteBefore;` — `UPROPERTY(EditAnywhere, Category = Processor, config)`
- L54 _public member_ `TArray<FName> ExecuteAfter;` — `UPROPERTY(EditAnywhere, Category = Processor, config)`

#### enum `EActivationState`  
`enum class EActivationState : uint8`  
_L58-63_
- reflection: `UENUM()`
- L60 _public enumerator_ `Inactive`
- L61 _public enumerator_ `Active`
- L62 _public enumerator_ `OneShot` — one-shot processor will auto-disable itself after the next CallExecute call

#### enum `EMassQueryBasedPruning`  
`enum class EMassQueryBasedPruning : uint8`  
_L71-76_
- reflection: `UENUM()`
- desc: Values determining whether a processor wants to be pruned at runtime. The value is not used when processing graph is generated for project configuration purposes or debug-time graph visualization purposes This behavior can be overridden by UMassProcessor::ShouldAllowQueryBasedPruning child class overrides
- L73 _public enumerator_ `Prune` — pruning will always be applied at runtime
- L74 _public enumerator_ `Never` — pruning will never be applied at runtime
- L75 _public enumerator_ `Default = Prune`

#### class `UMassProcessor`  
`class UMassProcessor : public UObject`  
_L79-357_
- reflection: `UCLASS(abstract, EditInlineNew, CollapseCategories, config = Mass, defaultconfig, ConfigDoNotCheckDefaults, MinimalAPI)`
- inherits: `UObject`
- L85 _public prototype_ `UMassProcessor();`
- L86 _public prototype_ `explicit UMassProcessor(const FObjectInitializer& ObjectInitializer);`
- L88 _public prototype_ `bool IsInitialized() const;`
- L91 _public prototype_ `void CallInitialize(const TNotNull<UObject*> Owner, const TSharedRef<FMassEntityManager>& EntityManager);` — Calls InitializeInternal and handles initialization bookkeeping.
- L93 _public prototype_ `virtual FGraphEventRef DispatchProcessorTasks(const TSharedPtr<FMassEntityManager>& EntityManager, FMassExecutionContext& ExecutionContext, const FGraphEventArray& Prerequisites = FGraphEventArray());`
- L95 _public prototype_ `EProcessorExecutionFlags GetExecutionFlags() const;`
- L98 _public prototype_ `bool ShouldExecute(const EProcessorExecutionFlags CurrentExecutionFlags) const;` — Whether this processor should execute according the CurrentExecutionFlags parameters
- L99 _public prototype_ `void CallExecute(FMassEntityManager& EntityManager, FMassExecutionContext& Context);`
- L105 _public prototype_ `bool ShouldAllowMultipleInstances() const;` — Controls whether there can be multiple instances of a given class in a single FMassRuntimePipeline and during dependency solving.
- L107 _public prototype_ `void DebugOutputDescription(FOutputDevice& Ar) const;`
- L108 _public prototype_ `virtual void DebugOutputDescription(FOutputDevice& Ar, int32 Indent) const;`
- L109 _public prototype_ `virtual FString GetProcessorName() const;`
- L122 _public prototype_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const;` — Indicates whether this processor can ever be pruned while considered for a phase processing graph. A processor can get pruned if none of its registered queries interact with archetypes instantiated at the moment of graph building. This can also happen for special processors that don't register any queries - if that's the case override this function to return an appropriate value or use QueryBasedPruning to configure the expected behavior. By default, the processor will be the subject of pruning when bRuntimeMode == true. @param bRuntimeMode indicates whether the pruning is being done for game runtime (true) or editor-time presentation (false)
- L124 _public prototype_ `virtual EMassProcessingPhase GetProcessingPhase() const;`
- L125 _public prototype_ `virtual void SetProcessingPhase(EMassProcessingPhase Phase);`
- L126 _public prototype_ `bool DoesRequireGameThreadExecution() const;`
- L128 _public prototype_ `const FMassProcessorExecutionOrder& GetExecutionOrder() const;`
- L132 _public prototype_ `virtual void ExportRequirements(FMassExecutionRequirements& OutRequirements) const;` — By default,  fetches requirements declared entity queries registered via RegisterQuery. Processors can override this function to supply additional requirements
- L134 _public prototype_ `const FMassSubsystemRequirements& GetProcessorRequirements() const;`
- L135 _public prototype_ `const FMassEntityCreationRequirements& GetProcessorEntityCreationRequirements() const;`
- L142 _public prototype_ `int16 GetExecutionPriority() const;` — @return the current value of ExecutionPriority @see SetExecutionPriority @see ExecutionPriority
- L150 _public prototype_ `void SetExecutionPriority(const int16 NewExecutionPriority);` — Sets new ExecutionPriority for this processor. The change will take effect the next time the processing graph is built Note that at this point this operation does not cause processing graph rebuilding, so this function should be used before processor's initialization or as part of code that will cause processing graph rebuilding anyway. @see ExecutionPriority
- L154 _public prototype_ `void RegisterQuery(FMassEntityQuery& Query);` — Adds Query to RegisteredQueries list. Query is required to be a member variable of this processor. Not meeting this requirement will cause check failure and the query won't be registered.
- L156 _public prototype_ `void MarkAsDynamic();`
- L157 _public prototype_ `bool IsDynamic() const;`
- L163 _public prototype_ `void MakeActive();` — Marks processor as "Active" (@see ActivationState for details). If called during Mass processing the call will take effect next phase.
- L168 _public prototype_ `void MakeOneShot();` — Marks processor as "One Shot" (@see ActivationState for details). If called during Mass processing the call will take effect next phase. The processor will auto-disable after execution.
- L172 _public prototype_ `void MakeInactive();` — Deactivate the processor, it will no longer execute its `Execute` function.
- L174 _public prototype_ `bool IsActive() const;`
- L176 _public prototype_ `bool ShouldAutoAddToGlobalList() const;`
- L178 _public prototype_ `bool ShouldShowUpInSettings() const;`
- L185 _public prototype_ `void SetShouldAutoRegisterWithGlobalList(const bool bAutoRegister);` — Sets bAutoRegisterWithProcessingPhases. Setting it to true will result in this processor class being always instantiated to be automatically evaluated every frame. @see FMassProcessingPhaseManager Note that calling this function is only valid on CDOs. Calling it on a regular instance will fail an ensure and have no other effect, i.e. CDO's value won't change
- L187 _public prototype_ `void GetArchetypesMatchingOwnedQueries(const FMassEntityManager& EntityManager, TArray<FMassArchetypeHandle>& OutArchetype);`
- L188 _public prototype_ `bool DoesAnyArchetypeMatchOwnedQueries(const FMassEntityManager& EntityManager);`
- L189 _public prototype_ `int32 GetOwnedQueriesNum() const;`
- L194 _public prototype_ `bool HasEntityCreationRequirements();` — Indicates whether or not this processor has declared in its requirements that it creates entities.
- L199 _public prototype_ `void ExportArchetypesCreated(TArray<FMassArchetypeHandle>& OutArchetypes);` — Export the cached archetypes (by handle) that this processor can create
- L204 _public prototype_ `void ResolveRequestedArchetypes(const FMassEntityManager& EntityManager);` — Resolves all the created archetype handles and creates the archetypes if they don't exist
- L209 _public prototype_ `void ClearArchetypesCreatedHandles();` — Clears the archetypes created cache to force it to rebuild before next use
- L213 _public member_ `FString StatId;`
- L218 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager);` — Called to initialize the processor's internal state. Override to perform custom steps.
- L225 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager);` — Called internally during processor's initialization so that child classes configure their owned queries with requirements. This function is called before the processor gets considered by Mass dependency solver, and the requirement information stored in queries is crucial for that process.
- L227 _protected prototype_ `virtual void PostInitProperties() override;`
- L233 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context);` — Called during the processing phase to which this processor is registered. Default implementation requires that AutoExecuteQuery is populated with a QueryExecutor.
- L238 _protected member_ `FMassProcessorExecutionOrder ExecutionOrder;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)` — Configures when this given processor can be executed in relation to other processors and processing groups, within its processing phase.
- L244 _protected member_ `EMassProcessingPhase ProcessingPhase = EMassProcessingPhase::PrePhysics;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)` — Processing phase this processor will be automatically run as part of. Needs to be set before the processor gets registered with MassProcessingPhaseManager, otherwise it will have no effect. This property is usually read via a given class's CDO, so it's recommended to set it in the constructor.
- L248 _protected member_ `uint8 ExecutionFlags;` — `UPROPERTY(EditAnywhere, Category = "Pipeline", meta = (Bitmask, BitmaskEnum = "/Script/MassEntity.EProcessorExecutionFlags"), config)` — Whether this processor should be executed on StandAlone or Server or Client
- L252 _protected member_ `uint8 bAutoRegisterWithProcessingPhases : 1 = true;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)` — Configures whether this processor should be automatically included in the global list of processors executed every tick (see ProcessingPhase and ExecutionOrder).
- L256 _protected member_ `uint8 bAllowMultipleInstances : 1 = false;` — Meant as a class property, make sure to set it in subclass' constructor. Controls whether there can be multiple instances of a given class in a single FMassRuntimePipeline and during dependency solving.
- L259 _protected member_ `uint8 bRequiresGameThreadExecution : 1 = false;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)`
- L264 _protected member_ `uint8 bAggregateRequirements : 1 = false;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)` — Combine all query and processor requirements when resolving contention in FProcessingQueue A value of true is legacy mode
- L270 _protected member_ `uint8 bCanShowUpInSettings : 1 = true;` — `UPROPERTY(config)` — Used to permanently remove a given processor class from PipeSetting's listing. Used primarily for test-time processor classes, but can also be used by project-specific code to prune the processor list.
- L283 _private member_ `uint8 bIsDynamic : 1 = false;` — Gets set to true when an instance of the processor gets added to the phase processing as a "dynamic processor". Once set it's never expected to be cleared out to `false` thus the private visibility of the member variable. A "dynamic" processor is a one that has bAutoRegisterWithProcessingPhases == false, meaning it's not automatically added to the processing graph. Additionally, making processors dynamic allows one to have multiple instances of processors of the same class. @see MarkAsDynamic() @see IsDynamic()
- L286 _private member_ `uint8 bInitialized : 1 = false;` — Used to track whether Initialized has been called.
- L289 _private member_ `uint8 bQueryHasEntityCreationRequirements : 1 = false;` — Cache presence of entity creation requirements in owned queries.
- L292 _private member_ `uint8 bCreatedArchetypeHandlesResolved : 1 = false;` — Tracks if created archetypes handles are resolved
- L304 _private member_ `EActivationState ActivationState = EActivationState::Active;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)` — Processors can be activated/deactivated at runtime. Deactivating a running processor will not disrupt the processing graph since the disabled processor's dependencies will get passed down to the subsequent processors depending on this one. Deactivating processor's CDO will result in every instance starting off as disabled. Those will still be considered while building the processor dependency graph and one included in the processing graph will function just as the processor instances disabled at runtime (i.e. won't run, but pass down their dependencies). A special type of activation is "One Shot" mode - it works just like "Active" state, but it will auto-disable itself upon completion of the next CallExecute call.
- L315 _protected member_ `int16 ExecutionPriority = 0;` — `UPROPERTY(EditDefaultsOnly, Category = Processor, config)` — Denoted how important it is for this processor to be executed as soon as possible within a processing graph. The larger the number the higher the priority. It's used in two ways: - used when sorting nodes that otherwise seem similar in terms of "which processor to pick for execution next" - affects the priority of the dependencies - if this super-important processor is waiting for processor A and B, then A and B become super important as well.
- L322 _protected member_ `EMassQueryBasedPruning QueryBasedPruning = EMassQueryBasedPruning::Default;` — Determines whether given processor wants to be pruned from the execution graph when there are no archetypes matching its requirements. Defaults to EMassQueryBasedPruning::Prune, @see EMassQueryBasedPruning
- L329 _protected member_ `FMassSubsystemRequirements ProcessorRequirements;` — A query representing elements this processor is accessing in Execute function outside of query execution
- L332 _protected member_ `FMassEntityCreationRequirements ProcessorEntityCreationRequirements;` — Archetypes this processor can create when no query is on the stack
- L335 _protected member_ `TSharedPtr<UE::Mass::FQueryExecutor> AutoExecuteQuery;` — A QueryExecutor that can optionally be run in lieu of overriding the Execute function.
- L341 _private member_ `TArray<FMassEntityQuery*> OwnedQueries;` — Stores processor's queries registered via RegisterQuery. @note that it's safe to store pointers here since RegisterQuery does verify that a given registered query is a member variable of a given processor
- L344 _private member_ `FString DebugDescription;`
- L352 _public prototype_ `virtual void Initialize(UObject& Owner) final;` — `UE_DEPRECATED(5.6, "Initialize is deprecated. Override InitializeInternal(UObject&, const TSharedRef<FMassEntityManager>&) instead. If you want to call the function, use CallInitialize.")`
- L354 _public function_ `virtual void ConfigureQueries() final` — `UE_DEPRECATED(5.6, "This flavor of ConfigureQueries is deprecated. Override ConfigureQueries(const TSharedRef<FMassEntityManager>&) instead.")`
- L477 _function_ `inline bool UMassProcessor::IsInitialized() const`
- L482 _function_ `inline EProcessorExecutionFlags UMassProcessor::GetExecutionFlags() const`
- L487 _function_ `inline bool UMassProcessor::ShouldExecute(const EProcessorExecutionFlags CurrentExecutionFlags) const`
- L492 _function_ `inline bool UMassProcessor::ShouldAllowMultipleInstances() const`
- L497 _function_ `inline int32 UMassProcessor::GetOwnedQueriesNum() const`
- L502 _function_ `inline void UMassProcessor::DebugOutputDescription(FOutputDevice& Ar) const`
- L507 _function_ `inline bool UMassProcessor::DoesRequireGameThreadExecution() const`
- L512 _function_ `inline const FMassProcessorExecutionOrder& UMassProcessor::GetExecutionOrder() const`
- L517 _function_ `inline const FMassSubsystemRequirements& UMassProcessor::GetProcessorRequirements() const`
- L522 _function_ `inline const FMassEntityCreationRequirements& UMassProcessor::GetProcessorEntityCreationRequirements() const`
- L527 _function_ `inline int16 UMassProcessor::GetExecutionPriority() const`
- L532 _function_ `inline void UMassProcessor::SetExecutionPriority(const int16 NewExecutionPriority)`
- L537 _function_ `inline void UMassProcessor::MarkAsDynamic()`
- L542 _function_ `inline bool UMassProcessor::IsDynamic() const`
- L547 _function_ `inline void UMassProcessor::MakeActive()`
- L552 _function_ `inline void UMassProcessor::MakeOneShot()`
- L557 _function_ `inline void UMassProcessor::MakeInactive()`
- L562 _function_ `inline bool UMassProcessor::IsActive() const`
- L567 _function_ `inline bool UMassProcessor::ShouldAutoAddToGlobalList() const`
- L573 _function_ `inline bool UMassProcessor::ShouldShowUpInSettings() const`

#### class `UMassCompositeProcessor`  
`class UMassCompositeProcessor : public UMassProcessor`  
_L361-471_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L378 _public prototype_ `UMassCompositeProcessor();`
- L380 _public prototype_ `void SetChildProcessors(TArrayView<UMassProcessor*> InProcessors);`
- L381 _public prototype_ `void SetChildProcessors(TArray<TObjectPtr<UMassProcessor>>&& InProcessors);`
- L383 _public prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& InEntityManager) override;`
- L384 _public prototype_ `virtual void DebugOutputDescription(FOutputDevice& Ar, int32 Indent = 0) const override;`
- L385 _public prototype_ `virtual void SetProcessingPhase(EMassProcessingPhase Phase) override;`
- L387 _public prototype_ `void SetGroupName(FName NewName);`
- L388 _public prototype_ `FName GetGroupName() const;`
- L390 _public prototype_ `virtual void SetProcessors(TArrayView<UMassProcessor*> InProcessorInstances, const TSharedPtr<FMassEntityManager>& EntityManager = nullptr);`
- L395 _public prototype_ `virtual void BuildFlatProcessingGraph(TConstArrayView<FMassProcessorOrderInfo> SortedProcessors);` — Builds flat processing graph that's being used for multithreading execution of hosted processors.
- L404 _public prototype_ `void UpdateProcessorsCollection(TArrayView<FMassProcessorOrderInfo> InOutOrderedProcessors, EProcessorExecutionFlags InWorldExecutionFlags = EProcessorExecutionFlags::None);` — Adds processors in InOutOrderedProcessors to ChildPipeline. Note that this operation is non-destructive for the existing processors - the ones of classes found in InOutOrderedProcessors will be retained and used instead of the instances provided via InOutOrderedProcessors. Respective entries in InOutOrderedProcessors will be updated to reflect the reuse. The described behavior however is available only for processors with bAllowMultipleInstances == false.
- L409 _public prototype_ `void AddGroupedProcessor(FName RequestedGroupName, UMassProcessor& SubProcessor);` — adds SubProcessor to an appropriately named group. If RequestedGroupName == None then SubProcessor will be added directly to ChildPipeline. If not then the indicated group will be searched for in ChildPipeline and if it's missing it will be created and AddGroupedProcessor will be called recursively
- L411 _public prototype_ `virtual FGraphEventRef DispatchProcessorTasks(const TSharedPtr<FMassEntityManager>& EntityManager, FMassExecutionContext& ExecutionContext, const FGraphEventArray& Prerequisites = FGraphEventArray()) override;`
- L413 _public prototype_ `bool IsEmpty() const;`
- L415 _public prototype_ `virtual FString GetProcessorName() const override;`
- L417 _public prototype_ `TConstArrayView<UMassProcessor*> GetChildProcessorsView() const;`
- L420 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L421 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L429 _protected prototype_ `UMassCompositeProcessor* FindOrAddGroupProcessor(FName RequestedGroupName, FString* OutRemainingGroupName = nullptr);` — RequestedGroupName can indicate a multi-level group name, like so: A.B.C We need to extract the highest-level group name ('A' in the example), and see if it already exists. If not, create it. @param RequestedGroupName name of the group for which we want to find or create the processor. @param OutRemainingGroupName contains the group name after cutting the high-level group. In the used example it will contain "B.C". This value is then used to recursively create subgroups
- L433 _protected member_ `FMassRuntimePipeline ChildPipeline;` — `UPROPERTY(VisibleAnywhere, Category=Mass)`
- L437 _protected member_ `FName GroupName;` — `UPROPERTY()` — Group name that will be used when resolving processor dependencies and grouping
- L440 _protected member_ `bool bDebugLogNewProcessingGraph = false;`
- L443 _protected member_ `TArray<FDependencyNode> FlatProcessingGraph;`
- L463 _protected member_ `TArray<FProcessorCompletion> CompletionStatus;`
- L470 _public prototype_ `void SetChildProcessors(TArray<UMassProcessor*>&& InProcessors);` — `UE_DEPRECATED(5.6, "This flavor of SetChildProcessors is deprecated. Please use one of the others.")`
- L582 _function_ `inline FName UMassCompositeProcessor::GetGroupName() const`
- L587 _function_ `inline bool UMassCompositeProcessor::IsEmpty() const`
- L592 _function_ `inline TConstArrayView<UMassProcessor*> UMassCompositeProcessor::GetChildProcessorsView() const`

#### struct `UMassCompositeProcessor::FDependencyNode`  
`struct FDependencyNode`  
_L367-375_
- L369 _public member_ `FName Name;`
- L370 _public member_ `UMassProcessor* Processor = nullptr;`
- L371 _public member_ `TArray<int32> Dependencies;`
- L373 _public member_ `int32 SequenceIndex = INDEX_NONE;`

#### struct `UMassCompositeProcessor::FProcessorCompletion`  
`struct FProcessorCompletion`  
_L445-462_
- L447 _public member_ `FGraphEventRef CompletionEvent;`
- L448 _public member_ `EProcessorCompletionStatus Status = EProcessorCompletionStatus::Invalid;`
- L450 _public function_ `bool IsDone() const`
- L455 _public function_ `void Wait()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MASSENTITY_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassProcessorDependencySolver.h` (Public)


#### struct `TMassExecutionAccess`  
`template<typename T> struct TMassExecutionAccess`  
_L27-53_
- L29 _public member_ `T Read;`
- L30 _public member_ `T Write;`
- L32 _public function_ `T& operator[](const uint32 OpIndex)`
- L38 _public function_ `const T& operator[](const uint32 OpIndex) const`
- L44 _public function_ `TConstArrayView<T> AsArrayView() const`
- L49 _public function_ `bool IsEmpty() const`
- L62 _public member_ `FMassConstSharedFragmentBitSet Read;`
- L63 _public function_ `TConstArrayView<FMassConstSharedFragmentBitSet> AsArrayView() const`

#### struct `TMassExecutionAccess`  
`template<> struct TMassExecutionAccess<FMassConstSharedFragmentBitSet>`  
_L60-71_
- desc: TMassExecutionAccess specialization for FMassConstSharedFragmentBitSet to enforce lack of access (not needed) and no "Write" component (conceptually doesn't make sense).
- L29 _public member_ `T Read;`
- L30 _public member_ `T Write;`
- L32 _public function_ `T& operator[](const uint32 OpIndex)`
- L38 _public function_ `const T& operator[](const uint32 OpIndex) const`
- L44 _public function_ `TConstArrayView<T> AsArrayView() const`
- L49 _public function_ `bool IsEmpty() const`
- L62 _public member_ `FMassConstSharedFragmentBitSet Read;`
- L63 _public function_ `TConstArrayView<FMassConstSharedFragmentBitSet> AsArrayView() const`

#### struct `FMassExecutionRequirements`  
`struct FMassExecutionRequirements`  
_L73-93_
- L75 _public prototype_ `void Append(const FMassExecutionRequirements& Other);`
- L76 _public prototype_ `void CountResourcesUsed();`
- L77 _public prototype_ `int32 GetTotalBitsUsedCount();`
- L78 _public prototype_ `bool IsEmpty() const;`
- L79 _public prototype_ `FMassArchetypeCompositionDescriptor AsCompositionDescriptor() const;`
- L81 _public member_ `TMassExecutionAccess<FMassFragmentBitSet> Fragments;`
- L82 _public member_ `TMassExecutionAccess<FMassFragmentBitSet> IndirectFragments;`
- L83 _public member_ `TMassExecutionAccess<FMassChunkFragmentBitSet> ChunkFragments;`
- L84 _public member_ `TMassExecutionAccess<FMassSharedFragmentBitSet> SharedFragments;`
- L85 _public member_ `TMassExecutionAccess<FMassConstSharedFragmentBitSet> ConstSharedFragments;`
- L86 _public member_ `TMassExecutionAccess<FMassExternalSubsystemBitSet> RequiredSubsystems;`
- L88 _public member_ `TMassExecutionAccess<FMassElementBitSet> SparseElements;` — Sparse elements - treated like indirect fragments (archetype-agnostic access)
- L89 _public member_ `FMassTagBitSet RequiredAllTags;`
- L90 _public member_ `FMassTagBitSet RequiredAnyTags;`
- L91 _public member_ `FMassTagBitSet RequiredNoneTags;`
- L92 _public member_ `int32 ResourcesUsedCount = INDEX_NONE;`

#### struct `FMassProcessorDependencySolver`  
`struct FMassProcessorDependencySolver`  
_L95-259_
- L210 _public prototype_ `FMassProcessorDependencySolver(TArrayView<UMassProcessor* const> InProcessors, const bool bIsGameRuntime = true);`
- L211 _public prototype_ `void ResolveDependencies(TArray<FMassProcessorOrderInfo>& OutResult, TSharedPtr<FMassEntityManager> EntityManager = nullptr, FResult* InOutOptionalResult = nullptr);`
- L213 _public prototype_ `static void CreateSubGroupNames(FName InGroupName, TArray<FString>& SubGroupNames);`
- L216 _public prototype_ `static bool IsResultUpToDate(const FResult& InResult, TSharedPtr<FMassEntityManager> EntityManager);` — Determines whether the dependency solving that produced InResult will produce different results if run with a given EntityManager
- L218 _public function_ `bool IsSolvingForSingleThread() const`
- L232 _protected prototype_ `bool PerformSolverStep(FResourceUsage& ResourceUsage, TArray<int32>& InOutIndicesRemaining, TArray<int32>& OutNodeIndices);` — Traverses InOutIndicesRemaining in search of the first RootNode's node that has no dependencies left. Once found the node's index gets added to OutNodeIndices, removed from dependency lists from all other nodes and the function quits. @return 'true' if a dependency-less node has been found and added to OutNodeIndices; 'false' otherwise.
- L234 _protected prototype_ `int32 CreateNodes(UMassProcessor& Processor);`
- L235 _protected prototype_ `void BuildDependencies();`
- L236 _protected prototype_ `void Solve(TArray<FMassProcessorOrderInfo>& OutResult);`
- L237 _protected prototype_ `void LogNode(const FNode& Node, int Indent = 0);`
- L240 _protected prototype_ `void GatherSubsystemInformation(const UE::Mass::FTypeManager& TypeManager);` — Finds out which subsystems handle multithreaded RW operations, and caches the result in MultiThreadedSystemsBitSet
- L242 _protected member_ `TArrayView<UMassProcessor* const> Processors;`
- L251 _protected member_ `const bool bSingleThreadTarget = !MASS_DO_PARALLEL;` — indicates whether we're generating processor order to be run in single-threaded or multithreaded environment (usually this means Dedicated Server vs Any other configuration). In Single-Threaded mode we can skip a bunch of expensive, fine-tuning tests. @Note currently the value depends on MASS_DO_PARALLEL and there's no way to configure it otherwise, but there's nothing inherently stopping us from letting users configure it.
- L252 _protected member_ `const bool bGameRuntime = true;`
- L253 _protected member_ `FString DependencyGraphFileName;`
- L254 _protected member_ `TArray<FNode> AllNodes;`
- L255 _protected member_ `TMap<FName, int32> NodeIndexMap;`
- L258 _protected member_ `FMassExternalSubsystemBitSet MultiThreadedSystemsBitSet;` — Stores the subsystems we know of that handle multithreaded access well - we filter those out, we don't need to consider them.

#### struct `FMassProcessorDependencySolver::FNode`  
`struct FNode`  
_L97-149_
- L99 _public function_ `FNode(const FName InName, UMassProcessor* InProcessor, const int32 InNodeIndex = INDEX_NONE) : Name(InName), Processor(InProcessor), NodeIndex(InNodeIndex)`
- L104 _public function_ `bool IsGroup() const`
- L112 _public prototype_ `bool IncreaseWaitingNodesCount(TArrayView<FNode> InAllNodes, const int32 IterationsLimit, TArray<int32>& OutCycleIndices);` — @return `true` when everything's fine, `false` when cycles have been encountered. If that happens `OutCycleIndices` gets filled with the relevant node indices.
- L113 _public prototype_ `bool IncreaseWaitingNodesCountAndPriority(TArrayView<FNode> InAllNodes, const int32 IterationsLimit, TArray<int32>& OutCycleIndices , const int32 InChildPriority = TNumericLimits<int32>::Min());`
- L115 _public function_ `void UpdateExecutionPriority(const int32 ChildExecutionPriority)`
- L124 _public member_ `FName Name;`
- L125 _public member_ `UMassProcessor* Processor = nullptr;`
- L126 _public member_ `TArray<int32> OriginalDependencies;`
- L127 _public member_ `TArray<int32> TransientDependencies;`
- L128 _public member_ `TArray<FName> ExecuteBefore;`
- L129 _public member_ `TArray<FName> ExecuteAfter;`
- L130 _public member_ `FMassExecutionRequirements Requirements;`
- L131 _public member_ `int32 NodeIndex = INDEX_NONE;`
- L133 _public member_ `int32 TotalWaitingNodes = 0;` — indicates how often given node can be found in dependencies sequence for other nodes
- L141 _public member_ `int32 MaxExecutionPriority = 0;` — The highest execution priority across this node and all nodes in its logical dependency chain. Nodes that are only dependencies due to resource contention (i.e. blocking shared resources) are excluded from this calculation. Note: we use int32 rather than UMassProcessor.ExecutionPriority's int16 to avoid overflow when propagating priorities in UpdateExecutionPriority.
- L146 _public member_ `int32 SequencePositionIndex = 0;` — indicates how deep within dependencies graph this give node is, or in other words, what's the longest sequence from this node to a dependency-less "parent" node
- L147 _public member_ `TArray<int32> SubNodeIndices;`
- L148 _public member_ `TArray<FMassArchetypeHandle> ValidArchetypes;`

#### struct `FMassProcessorDependencySolver::FResourceUsage`  
`struct FResourceUsage`  
_L152-188_
- L154 _public prototype_ `FResourceUsage(const TArray<FNode>& InAllNodes);`
- L156 _public prototype_ `bool CanAccessRequirements(const FMassExecutionRequirements& TestedRequirements, const TArray<FMassArchetypeHandle>& InArchetypes) const;`
- L157 _public prototype_ `void SubmitNode(const int32 NodeIndex, FNode& InOutNode);`
- L170 _private member_ `FMassExecutionRequirements Requirements;`
- L171 _private member_ `TMassExecutionAccess<FResourceAccess> FragmentsAccess;`
- L172 _private member_ `TMassExecutionAccess<FResourceAccess> IndirectFragmentsAccess;`
- L173 _private member_ `TMassExecutionAccess<FResourceAccess> ChunkFragmentsAccess;`
- L174 _private member_ `TMassExecutionAccess<FResourceAccess> SharedFragmentsAccess;`
- L175 _private member_ `TMassExecutionAccess<FResourceAccess> RequiredSubsystemsAccess;`
- L176 _private member_ `TMassExecutionAccess<FResourceAccess> SparseElementsAccess;`
- L177 _private member_ `TConstArrayView<FNode> AllNodesView;`
- L180 _private prototype_ `template<typename TBitSet> void HandleElementType(TMassExecutionAccess<FResourceAccess>& ElementAccess , const TMassExecutionAccess<TBitSet>& TestedRequirements, FMassProcessorDependencySolver::FNode& InOutNode, const int32 NodeIndex, bool bSkipArchetypeOverlapTest = false);`
- L184 _private prototype_ `template<typename TBitSet> static bool CanAccess(const TMassExecutionAccess<TBitSet>& StoredElements, const TMassExecutionAccess<TBitSet>& TestedElements);`
- L187 _private prototype_ `bool HasArchetypeConflict(TMassExecutionAccess<FResourceAccess> ElementAccess, const TArray<FMassArchetypeHandle>& InArchetypes) const;` — Determines whether any of the Elements' (i.e. Fragment, Tag,...) users operate on any of the archetypes given via InArchetypes

#### struct `FMassProcessorDependencySolver::FResourceUsage::FResourceUsers`  
`struct FResourceUsers`  
_L160-163_
- L162 _public member_ `TArray<int32> Users;`

#### struct `FMassProcessorDependencySolver::FResourceUsage::FResourceAccess`  
`struct FResourceAccess`  
_L165-168_
- L167 _public member_ `TArray<FResourceUsers> Access;`

#### struct `FMassProcessorDependencySolver::FResult`  
`struct FResult`  
_L193-208_
- desc: Optionally returned by ResolveDependencies and contains information about processors that have been pruned and other potentially useful bits. To be used in a transient fashion.
- L195 _public member_ `FString DependencyGraphFileName;`
- L196 _public member_ `TArray<TObjectPtr<UMassProcessor>> PrunedProcessors;`
- L197 _public member_ `int32 MaxSequenceLength = 0;`
- L198 _public member_ `uint32 ArchetypeDataVersion = 0;`
- L200 _public member_ `TArray<TSubclassOf<UMassProcessor>> PrunedProcessorClasses;` — `UE_DEPRECATED(5.6, "This property is deprecated, replaced by PrunedProcessors")`
- L202 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSENTITY_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mass` (scope `UE`)
- L19 _namespace_ `namespace EMassAccessOperation`
- L21 _variable_ `constexpr uint32 Read = 0;` (scope `EMassAccessOperation`)
- L22 _variable_ `constexpr uint32 Write = 1;` (scope `EMassAccessOperation`)
- L23 _variable_ `constexpr uint32 MAX = 2;` (scope `EMassAccessOperation`)

### `Source/Runtime/MassEntity/Public/MassQueryExecutor.h` (Public)


#### struct `UE::Mass::FQueryDefinitionBase`  
`struct FQueryDefinitionBase`  
_L17-21_
- desc: Interface for QueryDefinition templates. Not intended for other direct inheritance.
- L19 _public prototype_ `virtual void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) = 0;`
- L20 _public prototype_ `virtual void SetupForExecute(FMassExecutionContext& Context) = 0;`

#### struct `UE::Mass::FQueryExecutor`  
`struct FQueryExecutor`  
_L26-142_
- desc: A MassEntityQuery wrapper with type-safe data access.
- L29 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, FQueryExecutor>::IsDerived>::Type> static TSharedPtr<T> CreateQuery(FMassEntityQuery& InQuery, UObject* InLogOwner = nullptr)`
- L48 _public prototype_ `explicit FQueryExecutor(FMassEntityQuery& InQuery, UObject* InLogOwner = nullptr);`
- L49 _public prototype_ `virtual ~FQueryExecutor() = default;`
- L52 _public prototype_ `virtual void Execute(FMassExecutionContext& Context) = 0;` — Override with logic to perform against the entities returned by this query.
- L56 _protected function_ `inline UObject* GetLogOwner()`
- L62 _protected function_ `template<typename TAccessors, typename TFunc> inline void ForEachEntityChunk(FMassExecutionContext& ExecutionContext, TAccessors& Accessors, const TFunc&& ExecuteFunction)`
- L75 _protected function_ `template<typename TAccessors, typename TFunc> inline void ParallelForEachEntityChunk(FMassExecutionContext& ExecutionContext, const TAccessors& Accessors, const TFunc&& ExecuteFunction)`
- L91 _protected function_ `template<typename TAccessors, typename TFunc> inline void ForEachEntity(FMassExecutionContext& ExecutionContext, TAccessors& Accessors, const TFunc&& ExecuteFunction)`
- L108 _protected function_ `template<typename TAccessors, typename TFunc> inline void ParallelForEachEntity(FMassExecutionContext& ExecutionContext, TAccessors& Accessors, const TFunc&& ExecuteFunction)`
- L125 _protected prototype_ `FQueryExecutor();`
- L127 _private member_ `static FMassEntityQuery DummyQuery;`
- L129 _private prototype_ `void ConfigureQuery(FMassSubsystemRequirements& ProcessorRequirements);`
- L130 _private prototype_ `void CallExecute(FMassExecutionContext& Context);`
- L132 _private member_ `TNotNull<FMassEntityQuery*> BoundQuery;`
- L133 _private member_ `TWeakObjectPtr<UObject> LogOwner;`
- L136 _private member_ `FQueryDefinitionBase* AccessorsPtr;` — AccessorsPtr is only allowed to point to a member variable of this struct and will assert in all other cases.
- L139 _private prototype_ `void ValidateAccessors();`
- L140 _private member_ `uint32 DebugSize = 0;`

#### struct `UE::Mass::FQueryDefinition`  
`template<typename... Accessors> struct FQueryDefinition : public FQueryDefinitionBase`  
_L177-217_
- inherits: `FQueryDefinitionBase`
- desc: Defines the entity compositions to return in the query and provides type-safe data access to entity and subsystem data. Must be a member variable of a QueryExecutor
- L179 _public function_ `FQueryDefinition(FQueryExecutor& Owner)`
- L184 _public member_ `TTuple<Accessors...> AccessorTuple{};`
- L186 _public function_ `virtual void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) override`
- L195 _public function_ `virtual void SetupForExecute(FMassExecutionContext& Context) override`
- L203 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L212 _public function_ `template <typename TFragment> constexpr auto& Get()`

#### struct `UE::Mass::FMutableFragmentAccess`  
`template<typename TFragment> struct FMutableFragmentAccess`  
_L220-254_
- L225 _public typedef_ `using FragmentType = TFragment;`
- L227 _public prototype_ `FMutableFragmentAccess() = default;`
- L229 _public function_ `inline TArrayView<TFragment>& Get()`
- L234 _public function_ `inline TFragment& operator[](int32 Index)`
- L239 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements)`
- L244 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L248 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L253 _public member_ `TArrayView<TFragment> View;`

#### struct `UE::Mass::FConstFragmentAccess`  
`template<typename TFragment> struct FConstFragmentAccess`  
_L257-291_
- L262 _public typedef_ `using FragmentType = TFragment;`
- L264 _public prototype_ `FConstFragmentAccess() = default;`
- L266 _public function_ `inline const TConstArrayView<TFragment>& Get() const`
- L271 _public function_ `inline const TFragment& operator[](int32 Index) const`
- L276 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L281 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L285 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L290 _public member_ `TConstArrayView<TFragment> View;`

#### struct `UE::Mass::FMutableOptionalFragmentAccess`  
`template<typename TFragment> struct FMutableOptionalFragmentAccess`  
_L294-338_
- L299 _public typedef_ `using FragmentType = TFragment;`
- L301 _public prototype_ `FMutableOptionalFragmentAccess() = default;`
- L303 _public function_ `inline TArrayView<TFragment>& Get()`
- L308 _public function_ `inline TFragment& operator[](int32 Index)`
- L313 _public function_ `inline int32 Num() const`
- L318 _public function_ `inline operator bool() const`
- L323 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L328 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L332 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L337 _public member_ `TArrayView<TFragment> View;`

#### struct `UE::Mass::FConstOptionalFragmentAccess`  
`template<typename TFragment> struct FConstOptionalFragmentAccess`  
_L341-385_
- L346 _public typedef_ `using FragmentType = TFragment;`
- L348 _public prototype_ `FConstOptionalFragmentAccess() = default;`
- L350 _public function_ `inline const TConstArrayView<TFragment>& Get() const`
- L355 _public function_ `inline const TFragment& operator[](int32 Index) const`
- L360 _public function_ `inline int32 Num() const`
- L365 _public function_ `inline operator bool() const`
- L370 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L375 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L379 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L384 _public member_ `TConstArrayView<TFragment> View;`

#### struct `UE::Mass::FMassTagRequired`  
`template<typename TTag> struct FMassTagRequired`  
_L388-409_
- L393 _public typedef_ `using FragmentType = TTag;`
- L395 _public prototype_ `FMassTagRequired() = default;`
- L397 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L402 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L406 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`

#### struct `UE::Mass::FMassTagBlocked`  
`template<typename TFragment> struct FMassTagBlocked`  
_L412-428_
- L414 _public typedef_ `using FragmentType = TFragment;`
- L416 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L421 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L425 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`

#### struct `UE::Mass::FMutableSharedFragmentAccess`  
`template<typename TFragment> struct FMutableSharedFragmentAccess`  
_L431-472_
- L436 _public typedef_ `using FragmentType = TFragment;`
- L438 _public prototype_ `FMutableSharedFragmentAccess() = default;`
- L440 _public function_ `inline TFragment& Get() const`
- L446 _public function_ `inline TFragment& operator*() const`
- L452 _public function_ `inline TFragment* operator->() const`
- L457 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L462 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L466 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L471 _public member_ `TFragment* Fragment = nullptr;`

#### struct `UE::Mass::FConstSharedFragmentAccess`  
`template<typename TFragment> struct FConstSharedFragmentAccess`  
_L475-516_
- L480 _public typedef_ `using FragmentType = TFragment;`
- L482 _public prototype_ `FConstSharedFragmentAccess() = default;`
- L484 _public function_ `inline const TFragment& Get() const`
- L490 _public function_ `inline const TFragment& operator*() const`
- L496 _public function_ `inline const TFragment* operator->() const`
- L501 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L506 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L510 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L515 _public member_ `const TFragment* Fragment = nullptr;`

#### struct `UE::Mass::FMutableChunkFragmentAccess`  
`template<typename TFragment> struct FMutableChunkFragmentAccess`  
_L519-560_
- L524 _public typedef_ `using FragmentType = TFragment;`
- L526 _public prototype_ `FMutableChunkFragmentAccess() = default;`
- L528 _public function_ `inline TFragment& Get() const`
- L534 _public function_ `inline TFragment& operator*() const`
- L540 _public function_ `inline TFragment* operator->() const`
- L545 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L550 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L554 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L559 _public member_ `TFragment* Fragment = nullptr;`

#### struct `UE::Mass::FConstChunkFragmentAccess`  
`template<typename TFragment> struct FConstChunkFragmentAccess`  
_L563-604_
- L568 _public typedef_ `using FragmentType = TFragment;`
- L570 _public prototype_ `FConstChunkFragmentAccess() = default;`
- L572 _public function_ `inline const TFragment& Get() const`
- L578 _public function_ `inline const TFragment& operator*() const`
- L584 _public function_ `inline const TFragment* operator->() const`
- L589 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L594 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L598 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L603 _public member_ `const TFragment* Fragment = nullptr;`

#### struct `UE::Mass::FMutableOptionalChunkFragmentAccess`  
`template<typename TFragment> struct FMutableOptionalChunkFragmentAccess`  
_L607-653_
- L612 _public typedef_ `using FragmentType = TFragment;`
- L614 _public prototype_ `FMutableOptionalChunkFragmentAccess() = default;`
- L616 _public function_ `inline TFragment* Get() const`
- L622 _public function_ `inline TFragment& operator*() const`
- L628 _public function_ `inline TFragment* operator->() const`
- L633 _public function_ `inline operator bool()`
- L638 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L643 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L647 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L652 _public member_ `TFragment* Fragment = nullptr;`

#### struct `UE::Mass::FConstOptionalChunkFragmentAccess`  
`template<typename TFragment> struct FConstOptionalChunkFragmentAccess`  
_L656-702_
- L661 _public typedef_ `using FragmentType = TFragment;`
- L663 _public prototype_ `FConstOptionalChunkFragmentAccess() = default;`
- L665 _public function_ `inline const TFragment* Get()`
- L671 _public function_ `inline const TFragment& operator*() const`
- L677 _public function_ `inline const TFragment* operator->() const`
- L682 _public function_ `inline operator bool() const`
- L687 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L692 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L696 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L701 _public member_ `const TFragment* Fragment = nullptr;`

#### struct `UE::Mass::FMutableSubsystemAccess`  
`template<typename TSubsystem, typename = typename TEnableIf<TIsDerivedFrom<TSubsystem, USubsystem>::IsDerived>::Type> struct FMutableSubsystemAccess`  
_L705-751_
- L710 _public typedef_ `using FragmentType = TSubsystem;`
- L712 _public prototype_ `FMutableSubsystemAccess() = default;`
- L714 _public function_ `TSubsystem& Get() const`
- L720 _public function_ `inline TSubsystem& operator*() const`
- L726 _public function_ `inline TSubsystem* operator->() const`
- L731 _public function_ `inline operator bool() const`
- L736 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L741 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L746 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L750 _public member_ `TSubsystem* Subsystem = nullptr;`

#### struct `UE::Mass::FConstSubsystemAccess`  
`template<typename TSubsystem, typename = typename TEnableIf<TIsDerivedFrom<TSubsystem, USubsystem>::IsDerived>::Type> struct FConstSubsystemAccess`  
_L754-800_
- L759 _public typedef_ `using FragmentType = TSubsystem;`
- L761 _public prototype_ `FConstSubsystemAccess() = default;`
- L763 _public function_ `const TSubsystem& Get() const`
- L769 _public function_ `inline const TSubsystem& operator*() const`
- L775 _public function_ `inline const TSubsystem* operator->() const`
- L780 _public function_ `inline operator bool() const`
- L785 _public function_ `inline void ConfigureQuery(FMassEntityQuery& EntityQuery, FMassSubsystemRequirements& ProcessorRequirements) const`
- L790 _public function_ `inline void SetupForExecute(FMassExecutionContext& Context)`
- L795 _public function_ `inline void SetupForChunk(FMassExecutionContext& Context)`
- L799 _public member_ `const TSubsystem* Subsystem = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSENTITY_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mass` (scope `UE`)
- L65 _function_ `` (scope `UE::Mass::FQueryExecutor::ForEachEntityChunk`)
- L67 _function_ `` (scope `UE::Mass::FQueryExecutor::ForEachEntityChunk::__anon98a39b860102`)
- L78 _function_ `` (scope `UE::Mass::FQueryExecutor::ParallelForEachEntityChunk`)
- L82 _function_ `` (scope `UE::Mass::FQueryExecutor::ParallelForEachEntityChunk::__anon98a39b860302`)
- L94 _function_ `` (scope `UE::Mass::FQueryExecutor::ForEachEntity`)
- L96 _function_ `` (scope `UE::Mass::FQueryExecutor::ForEachEntity::__anon98a39b860502`)
- L111 _function_ `` (scope `UE::Mass::FQueryExecutor::ParallelForEachEntity`)
- L114 _function_ `` (scope `UE::Mass::FQueryExecutor::ParallelForEachEntity::__anon98a39b860702`)
- L152 _function_ `template <typename T, typename U, typename... Us> constexpr auto GetIndexRecursive()` (scope `UE::Mass`)
- L166 _function_ `template <typename T, typename U, typename... Us> constexpr auto GetAccessorIndex()` (scope `UE::Mass`)
- L189 _function_ `` (scope `UE::Mass::FQueryDefinition::ConfigureQuery`)
- L198 _function_ `` (scope `UE::Mass::FQueryDefinition::SetupForExecute`)
- L206 _function_ `` (scope `UE::Mass::FQueryDefinition::SetupForChunk`)

### `Source/Runtime/MassEntity/Public/MassRelationCommands.h` (Public)


#### struct `FMassCommandMakeRelation`  
`template<typename TRelation> struct FMassCommandMakeRelation : public FMassBatchedEntityCommand`  
_L19-73_
- inherits: `FMassBatchedEntityCommand`
- L21 _public typedef_ `using Super = FMassBatchedEntityCommand;`
- L23 _public function_ `FMassCommandMakeRelation(EMassCommandOperationType OperationType = EMassCommandOperationType::Add DEBUG_NAME_PARAM("MakeRelation")) : Super(OperationType FORWARD_DEBUG_NAME_PARAM)`
- L27 _public function_ `void Add(const FMassEntityHandle ChildEntity, const FMassEntityHandle ParentEntity)`
- L33 _public function_ `void Add(TConstArrayView<FMassEntityHandle> ChildEntities, TConstArrayView<FMassEntityHandle> ParentEntities)`
- L55 _protected function_ `virtual void Reset() override`
- L61 _protected function_ `virtual SIZE_T GetAllocatedSize() const override`
- L66 _protected function_ `virtual void Run(FMassEntityManager& EntityManager) override`
- L72 _protected member_ `TArray<FMassEntityHandle> Parents;`

#### Free symbols / members of external scopes

- L9 _macro_ `# define DEBUG_NAME(Name) , FName(TEXT(Name))`
- L10 _macro_ `# define DEBUG_NAME_PARAM(Name) , const FName InDebugName = TEXT(Name)`
- L11 _macro_ `# define FORWARD_DEBUG_NAME_PARAM , InDebugName`
- L13 _macro_ `# define DEBUG_NAME(Name)`
- L14 _macro_ `# define DEBUG_NAME_PARAM(Name)`
- L15 _macro_ `# define FORWARD_DEBUG_NAME_PARAM`

### `Source/Runtime/MassEntity/Public/MassRelationManager.h` (Public)


#### struct `UE::Mass::FRelationData`  
`struct FRelationData`  
_L21-71_
- L23 _public prototype_ `FRelationData(const FRelationTypeTraits& InTraits);`
- L25 _public member_ `const FRelationTypeTraits Traits;`
- L61 _public member_ `TMap<FMassEntityHandle, FRelationInstanceData> RoleMap;`
- L63 _public prototype_ `TArray<FMassEntityHandle> GetParticipants(const FMassEntityManager& EntityManager, const FMassEntityHandle RoleEntity, ERelationRole QueriedRole) const;`
- L66 _public prototype_ `bool HasParticipants(const FMassEntityManager& EntityManager, FMassEntityHandle RoleEntity, ERelationRole QueriedRole) const;` — Returns true if RoleEntity has at least one valid participant in the queried role. No allocation.
- L69 _public prototype_ `void ForEachParticipant(const FMassEntityManager& EntityManager, FMassEntityHandle RoleEntity, ERelationRole QueriedRole, TFunctionRef<void(FMassEntityHandle)> Callback) const;` — Callback-based enumeration of participants. Same iteration as GetParticipants but invokes a callback per valid entity instead of building a TArray.

#### struct `UE::Mass::FRelationData::FRelationInstanceData`  
`struct FRelationInstanceData`  
_L27-60_
- L29 _public member_ `TStaticArray<TArray<FMassRelationRoleInstanceHandle>, static_cast<uint32>(ERelationRole::MAX)> RelationEntityContainers;`
- L31 _public function_ `bool IsEmpty() const`
- L41 _public function_ `TArray<FMassRelationRoleInstanceHandle>& operator[](const int32 Index)`
- L46 _public function_ `const TArray<FMassRelationRoleInstanceHandle>& operator[](const int32 Index) const`
- L51 _public function_ `TArray<FMassRelationRoleInstanceHandle>& operator[](const ERelationRole Index)`
- L56 _public function_ `const TArray<FMassRelationRoleInstanceHandle>& operator[](const ERelationRole Index) const`

#### struct `UE::Mass::FRelationManager`  
`struct FRelationManager`  
_L74-173_
- L76 _public prototype_ `explicit FRelationManager(FMassEntityManager& EntityManager);`
- L79 _public prototype_ `template<UE::Mass::CRelation T> FMassEntityHandle CreateRelationInstance(FMassEntityHandle Subject, FMassEntityHandle Object);`
- L80 _public prototype_ `FMassEntityHandle CreateRelationInstance(const FTypeHandle RelationTypeHandle, FMassEntityHandle Subject, FMassEntityHandle Object);`
- L83 _public prototype_ `TArray<FMassEntityHandle> CreateRelationInstances(TNotNull<const UScriptStruct*> RelationType, TArrayView<FMassEntityHandle> Subjects, TArrayView<FMassEntityHandle> Objects);` — Creates a relation type handle with RelationType, and calls the other CreateRelationInstances implementation
- L90 _public prototype_ `TArray<FMassEntityHandle> CreateRelationInstances(const FTypeHandle RelationTypeHandle, TArrayView<FMassEntityHandle> Subjects, TArrayView<FMassEntityHandle> Objects);` — Creates valid relation instances of type RelationTypeHandle, binding Subjects and Objects Note that the input arrays can have their order modified by the function, all the relation pairs that are not valid, are moved to the back of the arrays The number of elements in Subjects and Objects must match.
- L92 _public prototype_ `bool DestroyRelationInstance(const FTypeHandle RelationTypeHandle, const FMassEntityHandle Subject, const FMassEntityHandle Object);`
- L93 _public prototype_ `bool DestroyRelationInstance(FMassRelationRoleInstanceHandle RelationHandle) const;`
- L96 _public prototype_ `[[nodiscard]] TArray<FMassEntityHandle> GetRelationSubjects(TNotNull<const UScriptStruct*> RelationType, const FMassEntityHandle ObjectEntity) const;` — Fetch all the entities that are "subjects" in instances of the given relation type, where ObjectEntity is the "object" of the relation
- L97 _public prototype_ `[[nodiscard]] TArray<FMassEntityHandle> GetRelationSubjects(const FTypeHandle RelationTypeHandle, const FMassEntityHandle ObjectEntity) const;`
- L100 _public prototype_ `[[nodiscard]] TArray<FMassEntityHandle> GetRelationObjects(TNotNull<const UScriptStruct*> RelationType, const FMassEntityHandle SubjectEntity) const;` — Fetch all the entities that are "objects" in instances of the given relation type, where SubjectEntity is the "subject" of the relation
- L101 _public prototype_ `[[nodiscard]] TArray<FMassEntityHandle> GetRelationObjects(const FTypeHandle RelationTypeHandle, const FMassEntityHandle SubjectEntity) const;`
- L103 _public prototype_ `[[nodiscard]] TArray<FMassEntityHandle> GetRelationEntities(TConstArrayView<FMassRelationRoleInstanceHandle> RelationEntitiesContainer) const;`
- L104 _public prototype_ `void GetRelationEntities(TConstArrayView<FMassRelationRoleInstanceHandle> RelationEntitiesContainer, TArray<FMassEntityHandle>& InOutEntityHandles) const;`
- L105 _public prototype_ `[[nodiscard]] TArray<FMassEntityHandle> GetRoleEntities(TConstArrayView<FMassRelationRoleInstanceHandle> RelationEntitiesContainer) const;`
- L106 _public prototype_ `void GetRoleEntities(TConstArrayView<FMassRelationRoleInstanceHandle> RelationEntitiesContainer, TArray<FMassEntityHandle>& InOutEntityHandles) const;`
- L108 _public prototype_ `FTypeHandle GetRelationTypeHandle(TNotNull<const UScriptStruct*> RelationType) const;`
- L111 _public prototype_ `void ForEachRelationSubject(const FTypeHandle RelationTypeHandle, FMassEntityHandle ObjectEntity, TFunctionRef<void(FMassEntityHandle)> Callback) const;` — Callback-based enumeration of subjects for a given object in a relation. Zero allocation.
- L115 _public prototype_ `void ForEachRelationObject(const FTypeHandle RelationTypeHandle, FMassEntityHandle SubjectEntity, TFunctionRef<void(FMassEntityHandle)> Callback) const;` — Callback-based enumeration of objects for a given subject in a relation. Zero allocation.
- L119 _public prototype_ `bool HasRelationSubjects(const FTypeHandle RelationTypeHandle, FMassEntityHandle ObjectEntity) const;` — Returns true if ObjectEntity has at least one subject in this relation type. No allocation.
- L122 _public prototype_ `bool HasRelationObjects(const FTypeHandle RelationTypeHandle, FMassEntityHandle SubjectEntity) const;` — Returns true if SubjectEntity has at least one object in this relation type. No allocation.
- L124 _public prototype_ `bool IsSubjectOfRelation(const FTypeHandle RelationTypeHandle, const FMassEntityHandle Subject, const FMassEntityHandle Object) const;`
- L125 _public prototype_ `bool IsSubjectOfRelation(const FRelationData& RelationDataInstance, const FMassEntityHandle Subject, const FMassEntityHandle Object) const;`
- L126 _public prototype_ `bool IsSubjectOfRelationRecursive(const FTypeHandle RelationTypeHandle, const FMassEntityHandle Subject, const FMassEntityHandle Object) const;`
- L127 _public prototype_ `bool IsSubjectOfRelationRecursive(const FRelationData& RelationDataInstance, const FMassEntityHandle Subject, const FMassEntityHandle Object) const;`
- L130 _public prototype_ `void OnRelationTypeRegistered(const FTypeHandle RegisteredTypeHandle, const FRelationTypeTraits& RelationTypeTraits);`
- L132 _public prototype_ `const FRelationData& GetRelationDataChecked(const FTypeHandle RelationTypeHandle) const;`
- L133 _public prototype_ `FRelationData& GetRelationDataChecked(const FTypeHandle RelationTypeHandle);`
- L137 _protected prototype_ `FRelationData& CreateRelationData(const FTypeHandle RelationTypeHandle);`
- L139 _protected prototype_ `TArray<FMassEntityHandle> GetRelationObjects(const FRelationData& RelationData, const FMassEntityHandle SubjectEntity) const;`
- L140 _protected prototype_ `TArray<FMassEntityHandle> GetRelationSubjects(const FRelationData& RelationData, const FMassEntityHandle ObjectEntity) const;`
- L142 _protected prototype_ `const FRelationData* GetRelationData(const FTypeHandle RelationTypeHandle) const;`
- L167 _protected prototype_ `void GatherHierarchy(const FRelationData& RelationData, const FMassEntityHandle SubjectHandle, FHierarchyEntitiesContainer& SubSubjects, uint32 Depth = 0) const;`
- L169 _protected member_ `FMassEntityManager& EntityManager;`
- L170 _protected member_ `const FTypeManager& TypeManager;`
- L172 _protected member_ `TMap<FTypeHandle, FRelationData> RelationsDataMap;`
- L179 _function_ `template<UE::Mass::CRelation T> FMassEntityHandle FRelationManager::CreateRelationInstance(FMassEntityHandle Subject, FMassEntityHandle Object)`
- L185 _function_ `inline FMassEntityHandle FRelationManager::CreateRelationInstance(const FTypeHandle RelationTypeHandle, FMassEntityHandle Subject, FMassEntityHandle Object)`
- L191 _function_ `inline TArray<FMassEntityHandle> FRelationManager::CreateRelationInstances(TNotNull<const UScriptStruct*> RelationType, TArrayView<FMassEntityHandle> Subjects, TArrayView<FMassEntityHandle> Objects)`
- L202 _function_ `inline FTypeHandle FRelationManager::GetRelationTypeHandle(TNotNull<const UScriptStruct*> RelationType) const`
- L211 _function_ `inline const FRelationData* FRelationManager::GetRelationData(const FTypeHandle RelationTypeHandle) const`
- L216 _function_ `inline const FRelationData& FRelationManager::GetRelationDataChecked(const FTypeHandle RelationTypeHandle) const`
- L221 _function_ `inline FRelationData& FRelationManager::GetRelationDataChecked(const FTypeHandle RelationTypeHandle)`
- L226 _function_ `inline TArray<FMassEntityHandle> FRelationManager::GetRelationSubjects(TNotNull<const UScriptStruct*> RelationType, const FMassEntityHandle ObjectEntity) const`
- L232 _function_ `inline TArray<FMassEntityHandle> FRelationManager::GetRelationSubjects(const FTypeHandle RelationTypeHandle, const FMassEntityHandle ObjectEntity) const`
- L238 _function_ `inline TArray<FMassEntityHandle> FRelationManager::GetRelationObjects(TNotNull<const UScriptStruct*> RelationType, const FMassEntityHandle SubjectEntity) const`
- L244 _function_ `inline TArray<FMassEntityHandle> FRelationManager::GetRelationObjects(const FTypeHandle RelationTypeHandle, const FMassEntityHandle SubjectEntity) const`

#### struct `UE::Mass::FRelationManager::FHierarchyEntitiesContainer`  
`struct FHierarchyEntitiesContainer`  
_L144-165_
- L146 _public prototype_ `void StoreUnique(const uint32 Depth, TArray<FMassEntityHandle>& InOutArray);`
- L147 _public prototype_ `void StoreUnique(const uint32 Depth, FMassEntityHandle Handle);`
- L149 _public function_ `TArray<FMassEntityHandle>& operator[](const uint32 Depth)`
- L153 _public function_ `const TArray<FMassEntityHandle>& operator[](const uint32 Depth) const`
- L158 _public function_ `uint32 Num() const`
- L163 _protected member_ `TArray<TArray<FMassEntityHandle>> ContainerPerLevel;`
- L164 _protected member_ `TSet<FMassEntityHandle> ExistingElements;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSENTITY_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassRelationObservers.h` (Public)


#### class `UMassRelationObserver`  
`class UMassRelationObserver : public UMassObserverProcessor`  
_L18-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L23 _public prototype_ `UMassRelationObserver();`
- L28 _public prototype_ `virtual bool ConfigureRelationObserver(UE::Mass::FTypeHandle InRegisteredTypeHandle, const UE::Mass::FRelationTypeTraits& Traits);` — @return whether the configuration was successful. Failed observers won't get added to the observer manager and will get destroyed promptly.
- L31 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L32 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L34 _protected member_ `FMassEntityQuery EntityQuery;`
- L35 _protected member_ `UE::Mass::FTypeHandle RelationTypeHandle;`
- L37 _protected member_ `EMassFragmentAccess ObservedTypeAccess = EMassFragmentAccess::ReadWrite;` — Relevant only when the primary observed type is a fragment
- L38 _protected member_ `EMassFragmentAccess RelationFragmentAccessType = EMassFragmentAccess::ReadWrite;`
- L39 _protected member_ `bool bAutoAddRelationFragmentRequirement = true;`
- L40 _protected member_ `bool bAutoAddRelationTagRequirement = true;`
- L42 _protected member_ `FString DebugDescription;`

#### class `UMassRelationEntityCreation`  
`class UMassRelationEntityCreation : public UMassRelationObserver`  
_L46-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRelationObserver`
- L50 _public member_ `static constexpr int32 RelationCreationObserverExecutionPriority = 1024;`
- L52 _public prototype_ `UMassRelationEntityCreation();`
- L55 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UMassRelationEntityGuardDog`  
`class UMassRelationEntityGuardDog : public UMassRelationObserver`  
_L60-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRelationObserver`
- desc: Debug-time, detects relation elements being removed from the relation entities, which is not supposed to be done
- L64 _public prototype_ `UMassRelationEntityGuardDog();`
- L67 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UMassRelationEntityDestruction`  
`class UMassRelationEntityDestruction : public UMassRelationObserver`  
_L72-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRelationObserver`
- desc: cleans up data, removes enties in RoleMap if Entry.IsEmpty
- L76 _public prototype_ `UMassRelationEntityDestruction();`
- L79 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UMassRelationRoleDestruction`  
`class UMassRelationRoleDestruction : public UMassRelationObserver`  
_L83-109_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRelationObserver`
- L88 _public prototype_ `UMassRelationRoleDestruction();`
- L90 _public prototype_ `virtual bool ConfigureRelationObserver(UE::Mass::FTypeHandle InRegisteredTypeHandle, const UE::Mass::FRelationTypeTraits& Traits) override;`
- L91 _public prototype_ `static void AddObserverInstances(FMassObserverManager& GetObserverManager, UE::Mass::FTypeHandle InRegisteredTypeHandle, const UE::Mass::FRelationTypeTraits& Traits);`
- L94 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L95 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L97 _protected member_ `FMassExecuteFunction ExecuteFunction;`
- L102 _protected member_ `UE::Mass::Relations::ERelationRole RelationRole = UE::Mass::Relations::ERelationRole::MAX;` — indicates which side of the relation the given destructor handles. MAX indicates both sides.
- L108 _protected member_ `const UScriptStruct* ExcludedRelationFragmentType = nullptr;` — indicates the relation-specific fragment, that characterizes relation-entities. We use this information to filer these entities out - this observer is meant to only handle "role" entities

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSENTITY_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mass` (scope `UE`)
- L11 _namespace_ `namespace Relations` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassRequirementAccessDetector.h` (Public)


#### struct `FMassRequirementAccessDetector`  
`struct FMassRequirementAccessDetector`  
_L14-77_
- L16 _public prototype_ `void Initialize();`
- L17 _public prototype_ `void RequireAccess(const FMassEntityQuery& Query);`
- L18 _public prototype_ `void ReleaseAccess(const FMassEntityQuery& Query);`
- L21 _private typedef_ `using FDetectorMethod = bool (FRWAccessDetector::*)() const;`
- L23 _private function_ `template<typename TBitSet> void Operation(const TBitSet& BitSet, FDetectorMethod Op)`
- L37 _private function_ `void Acquire(TConstArrayView<FMassFragmentRequirementDescription> Requirements)`
- L55 _private function_ `void Release(TConstArrayView<FMassFragmentRequirementDescription> Requirements)`
- L74 _private prototype_ `void AddDetectors(const FStructTracker& StructTracker);` — @Note the function is not thread-safe and meant to be only called internally on game thread (see FMassRequirementAccessDetector::Initialize)
- L76 _private member_ `TMap<const UStruct*, TSharedRef<FRWAccessDetector>> Detectors;`

#### struct `UE::Mass::Debug::FScopedRequirementAccessDetector`  
`struct FScopedRequirementAccessDetector`  
_L85-98_
- L88 _public prototype_ `FScopedRequirementAccessDetector(const FMassEntityQuery& InQuery);`
- L89 _public prototype_ `~FScopedRequirementAccessDetector();`
- L91 _public member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L92 _public member_ `const FMassEntityQuery& Query;`

#### Free symbols / members of external scopes

- L83 _namespace_ `namespace UE`
- L83 _namespace_ `namespace Mass` (scope `UE`)
- L83 _namespace_ `namespace Debug` (scope `UE::Mass`)

### `Source/Runtime/MassEntity/Public/MassRequirements.h` (Public)


#### struct `UE::Mass::ErrorReporting::FScopedOutputDevice`  
`struct FScopedOutputDevice`  
_L27-34_
- desc: Helper struct that can be used to set up a threadsafe global output device so nested calls can use UE::Mass::ErrorReporting::GetOutputDevice() to report error messages.
- L29 _public prototype_ `explicit FScopedOutputDevice(FOutputDevice& OutputDevice);`
- L30 _public prototype_ `~FScopedOutputDevice();`
- L33 _private member_ `FOutputDevice* ActiveOutputDevice = nullptr;`

#### enum `EMassFragmentAccess`  
`enum class EMassFragmentAccess : uint8`  
_L39-51_
- reflection: `UENUM()`
- L42 _public enumerator_ `None` — no binding required
- L45 _public enumerator_ `ReadOnly` — We want to read the data from the fragment
- L48 _public enumerator_ `ReadWrite` — We want to read and write the data for the fragment
- L50 _public enumerator_ `MAX`

#### enum `EMassFragmentPresence`  
`enum class EMassFragmentPresence : uint8`  
_L54-69_
- reflection: `UENUM()`
- L57 _public enumerator_ `All` — All the required fragments must be present
- L60 _public enumerator_ `Any` — One of the required fragments must be present
- L63 _public enumerator_ `None` — None of the required fragments can be present
- L66 _public enumerator_ `Optional` — If fragment is present we'll use it
- L68 _public enumerator_ `MAX`

#### struct `FMassFragmentRequirementDescription`  
`struct FMassFragmentRequirementDescription`  
_L72-88_
- L74 _public prototype_ `FMassFragmentRequirementDescription() = default;`
- L75 _public prototype_ `FMassFragmentRequirementDescription(const UScriptStruct* InStruct, const EMassFragmentAccess InAccessMode, const EMassFragmentPresence InPresence);`
- L77 _public prototype_ `bool RequiresBinding() const;`
- L78 _public prototype_ `bool IsOptional() const;`
- L81 _public prototype_ `int32 GetStructureSize() const;` — these functions are used for sorting. See FScriptStructSortOperator
- L83 _public prototype_ `FName GetFName() const;`
- L85 _public member_ `const UScriptStruct* StructType = nullptr;`
- L86 _public member_ `EMassFragmentAccess AccessMode = EMassFragmentAccess::None;`
- L87 _public member_ `EMassFragmentPresence Presence = EMassFragmentPresence::Optional;`
- L965 _function_ `inline FMassFragmentRequirementDescription::FMassFragmentRequirementDescription(const UScriptStruct* InStruct, const EMassFragmentAccess InAccessMode, const EMassFragmentPresence InPresence) : StructType(InStruct) , AccessMode(InAccessMode) , Presence(InPresence)`
- L973 _function_ `inline bool FMassFragmentRequirementDescription::RequiresBinding() const`
- L978 _function_ `inline bool FMassFragmentRequirementDescription::IsOptional() const`
- L983 _function_ `inline int32 FMassFragmentRequirementDescription::GetStructureSize() const`
- L988 _function_ `inline FName FMassFragmentRequirementDescription::GetFName() const`

#### struct `FMassSubsystemRequirements`  
`struct FMassSubsystemRequirements`  
_L93-176_
- desc: FMassSubsystemRequirements is a structure that declares runtime subsystem access type given calculations require.
- L100 _public function_ `template<typename T> FMassSubsystemRequirements& AddSubsystemRequirement(const EMassFragmentAccess AccessMode)`
- L125 _public function_ `FMassSubsystemRequirements& AddSubsystemRequirement(const TSubclassOf<USubsystem> SubsystemClass, const EMassFragmentAccess AccessMode, const bool bGameThreadOnly)`
- L146 _public function_ `FMassSubsystemRequirements& AddSubsystemRequirement(const TSubclassOf<USubsystem> SubsystemClass, const EMassFragmentAccess AccessMode, const TSharedRef<FMassEntityManager>& EntityManager)`
- L152 _public function_ `FMassSubsystemRequirements& AddSubsystemRequirement(const TSubclassOf<USubsystem> SubsystemClass, const EMassFragmentAccess AccessMode)` — `UE_DEPRECATED(5.6, "This flavor of FMassSubsystemRequirements::AddSubsystemRequirement is deprecated. Use one of the other flavors, or call FMassEntityQuery::AddSubsystemRequirement if applicable.")`
- L157 _public prototype_ `void Reset();`
- L159 _public prototype_ `const FMassExternalSubsystemBitSet& GetRequiredConstSubsystems() const;`
- L160 _public prototype_ `const FMassExternalSubsystemBitSet& GetRequiredMutableSubsystems() const;`
- L161 _public prototype_ `bool IsEmpty() const;`
- L163 _public prototype_ `bool DoesRequireGameThreadExecution() const;`
- L164 _public prototype_ `void ExportRequirements(FMassExecutionRequirements& OutRequirements) const;`
- L169 _protected prototype_ `static bool IsGameThreadOnlySubsystem(const TSubclassOf<USubsystem> SubsystemClass, const TSharedRef<FMassEntityManager>& EntityManager);`
- L171 _protected member_ `FMassExternalSubsystemBitSet RequiredConstSubsystems;`
- L172 _protected member_ `FMassExternalSubsystemBitSet RequiredMutableSubsystems;`
- L175 _private member_ `bool bRequiresGameThreadExecution = false;`
- L993 _function_ `inline const FMassExternalSubsystemBitSet& FMassSubsystemRequirements::GetRequiredConstSubsystems() const`
- L998 _function_ `inline const FMassExternalSubsystemBitSet& FMassSubsystemRequirements::GetRequiredMutableSubsystems() const`
- L1003 _function_ `inline bool FMassSubsystemRequirements::IsEmpty() const`
- L1008 _function_ `inline bool FMassSubsystemRequirements::DoesRequireGameThreadExecution() const`

#### struct `FMassFragmentRequirements`  
`struct FMassFragmentRequirements`  
_L181-878_
- desc: FMassFragmentRequirements is a structure that describes properties required of an archetype that's a subject of calculations.
- L186 _public prototype_ `FMassFragmentRequirements() = default;`
- L187 _public prototype_ `explicit FMassFragmentRequirements(const TSharedPtr<FMassEntityManager>& EntityManager);`
- L188 _public prototype_ `explicit FMassFragmentRequirements(const TSharedRef<FMassEntityManager>& EntityManager);`
- L190 _public prototype_ `void Initialize(const TSharedRef<FMassEntityManager>& EntityManager);`
- L192 _public function_ `FMassFragmentRequirements& AddElementRequirement(TNotNull<const UScriptStruct*> ElementType, const EMassFragmentAccess AccessMode, const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L201 _public function_ `FMassFragmentRequirements& AddRequirement(const UScriptStruct* FragmentType, const EMassFragmentAccess AccessMode, const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L243 _public function_ `template<typename T> FMassFragmentRequirements& AddRequirement(const EMassFragmentAccess AccessMode, const EMassFragmentPresence Presence = EMassFragmentPresence::All)` — FMassFragmentRequirements ref returned for chaining
- L283 _public function_ `FMassFragmentRequirements& AddTagRequirement(TNotNull<const UScriptStruct*> TagType, const EMassFragmentPresence Presence)`
- L314 _public function_ `void AddTagRequirement(const UScriptStruct& TagType, const EMassFragmentPresence Presence)`
- L320 _public function_ `template<typename T> FMassFragmentRequirements& AddTagRequirement(const EMassFragmentPresence Presence)`
- L355 _public function_ `template<EMassFragmentPresence Presence> FMassFragmentRequirements& AddTagRequirements(const FMassTagBitSet& TagBitSet)` — actual implementation in specializations
- L363 _public prototype_ `FMassFragmentRequirements& ClearTagRequirements(const FMassTagBitSet& TagsToRemoveBitSet);` — Clears given tags out of all collected requirements, including negative ones
- L369 _public function_ `template<UE::Mass::CSparse T> FMassFragmentRequirements& AddSparseRequirement(const EMassFragmentPresence Presence = EMassFragmentPresence::All)` — Adds given sparse element type as a requirement.
- L397 _public function_ `FMassFragmentRequirements& AddSparseRequirement(TNotNull<const UScriptStruct*> ElementType, const EMassFragmentPresence Presence = EMassFragmentPresence::All)` — Adds given sparse element type as a requirement.
- L424 _public function_ `template<typename T> FMassFragmentRequirements& AddChunkRequirement(const EMassFragmentAccess AccessMode, const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L450 _public function_ `FMassFragmentRequirements& AddChunkRequirement(TNotNull<const UScriptStruct*> ChunkFragmentType, const EMassFragmentAccess AccessMode, const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L476 _public function_ `template<typename T> FMassFragmentRequirements& AddConstSharedRequirement(const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L502 _public function_ `FMassFragmentRequirements& AddConstSharedRequirement(const UScriptStruct* FragmentType, const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L534 _public function_ `template<typename T> FMassFragmentRequirements& AddSharedRequirement(const EMassFragmentAccess AccessMode, const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L568 _public function_ `FMassFragmentRequirements& AddSharedRequirement(TNotNull<const UScriptStruct*> SharedFragmentType, const EMassFragmentAccess AccessMode, const EMassFragmentPresence Presence = EMassFragmentPresence::All)`
- L609 _public function_ `FMassFragmentRequirements& AddLinkedEntityRequirement(TNotNull<const UScriptStruct*> FragmentType, const EMassFragmentAccess AccessMode, TNotNull<const UScriptStruct*> LinkType = FMassEntityLinkFragment::StaticStruct())` — Adds an access requirement for a fragment on a linked entity. This is a specialization of Indirect fragment access that requires the target entity be "Linked" To link an entity, add a FMassEntityLinkFragment to the entities you want to link from and set the LinkedEntityHandle to the target entity. FMassEntityLinkFragment can be inherited to support specific link types and multiple linked entities. Linking entities this way will group all entities that link to the target entity in memory for better cache behavior when iterating through query results.
- L659 _public function_ `template<UE::Mass::CFragment T, typename TLinkFragment = FMassEntityLinkFragment> FMassFragmentRequirements& AddLinkedEntityRequirement(const EMassFragmentAccess AccessMode)` — Adds an access requirement for a fragment on a linked entity. This is a specialization of Indirect fragment access that requires the target entity be "Linked" To link an entity, add a FMassEntityLinkFragment to the entities you want to link from and set the LinkedEntityHandle to the target entity. FMassEntityLinkFragment can be inherited to support specific link types and multiple linked entities. Linking entities this way will group all entities that link to the target entity in memory for better cache behavior when iterating through query results.
- L666 _public function_ `template<UE::Mass::CFragment T> bool HasConstIndirectEntityRequirement()`
- L673 _public function_ `template<UE::Mass::CFragment T> bool HasMutableIndirectEntityRequirement()`
- L683 _public function_ `FMassFragmentRequirements& AddIndirectFragmentRequirement(TNotNull<const UScriptStruct*> FragmentType, const EMassFragmentAccess AccessMode)` — Adds an access requirement for a fragment on another entity. This is used to enforce access requirements in the dependency solver, not to discover entities/archetypes. Use FMassExecutionContext::GetIndirectFragmentPtr to access fragments indirectly in your processor.
- L709 _public function_ `template<UE::Mass::CFragment T> FMassFragmentRequirements& AddIndirectFragmentRequirement(const EMassFragmentAccess AccessMode)` — Adds an access requirement for a fragment on another entity. This is used to enforce access requirements in the dependency solver, not to discover entities/archetypes. Use FMassExecutionContext::GetIndirectFragmentPtr to access fragments indirectly in your processor.
- L715 _public prototype_ `void Reset();`
- L724 _public prototype_ `bool CheckValidity() const;` — The function validates requirements we make for queries. See the FMassFragmentRequirements struct description for details. Even though the code of the function is non-trivial the consecutive calls will be essentially free due to the result being cached (note that the caching gets invalidated if the composition changes). Note: sparse-elements-only requirements are not valid. Use FMassSparseElementIterator instead @return whether this query's requirements follow the rules.
- L726 _public prototype_ `TConstArrayView<FMassFragmentRequirementDescription> GetFragmentRequirements() const;`
- L727 _public prototype_ `TConstArrayView<FMassFragmentRequirementDescription> GetChunkFragmentRequirements() const;`
- L728 _public prototype_ `TConstArrayView<FMassFragmentRequirementDescription> GetConstSharedFragmentRequirements() const;`
- L729 _public prototype_ `TConstArrayView<FMassFragmentRequirementDescription> GetSharedFragmentRequirements() const;`
- L730 _public prototype_ `const FMassFragmentBitSet& GetRequiredAllFragments() const;`
- L731 _public prototype_ `const FMassFragmentBitSet& GetRequiredAnyFragments() const;`
- L732 _public prototype_ `const FMassFragmentBitSet& GetRequiredOptionalFragments() const;`
- L733 _public prototype_ `const FMassFragmentBitSet& GetRequiredNoneFragments() const;`
- L734 _public prototype_ `const FMassFragmentBitSet& GetIndirectReadOnlyFragments() const;`
- L735 _public prototype_ `const FMassFragmentBitSet& GetIndirectReadWriteFragments() const;`
- L736 _public prototype_ `const FMassTagBitSet& GetRequiredAllTags() const;`
- L737 _public prototype_ `const FMassTagBitSet& GetRequiredAnyTags() const;`
- L738 _public prototype_ `const FMassTagBitSet& GetRequiredNoneTags() const;`
- L739 _public prototype_ `const FMassTagBitSet& GetRequiredOptionalTags() const;`
- L740 _public prototype_ `const FMassChunkFragmentBitSet& GetRequiredAllChunkFragments() const;`
- L741 _public prototype_ `const FMassChunkFragmentBitSet& GetRequiredOptionalChunkFragments() const;`
- L742 _public prototype_ `const FMassChunkFragmentBitSet& GetRequiredNoneChunkFragments() const;`
- L743 _public prototype_ `const FMassSharedFragmentBitSet& GetRequiredAllSharedFragments() const;`
- L744 _public prototype_ `const FMassSharedFragmentBitSet& GetRequiredOptionalSharedFragments() const;`
- L745 _public prototype_ `const FMassSharedFragmentBitSet& GetRequiredNoneSharedFragments() const;`
- L746 _public prototype_ `const FMassConstSharedFragmentBitSet& GetRequiredAllConstSharedFragments() const;`
- L747 _public prototype_ `const FMassConstSharedFragmentBitSet& GetRequiredOptionalConstSharedFragments() const;`
- L748 _public prototype_ `const FMassConstSharedFragmentBitSet& GetRequiredNoneConstSharedFragments() const;`
- L749 _public prototype_ `const FMassElementBitSet& GetRequiredAllSparseElements() const;`
- L750 _public prototype_ `const FMassElementBitSet& GetRequiredAnySparseElements() const;`
- L751 _public prototype_ `const FMassElementBitSet& GetRequiredOptionalSparseElements() const;`
- L752 _public prototype_ `const FMassElementBitSet& GetRequiredNoneSparseElements() const;`
- L754 _public prototype_ `bool IsInitialized() const;`
- L755 _public prototype_ `bool IsEmpty() const;`
- L756 _public prototype_ `bool HasPositiveRequirements() const;`
- L757 _public prototype_ `bool HasNegativeRequirements() const;`
- L758 _public prototype_ `bool HasOptionalRequirements() const;`
- L759 _public prototype_ `bool HasSparseRequirements() const;`
- L760 _public prototype_ `bool HasLinkedEntityRequirements() const;`
- L767 _public prototype_ `bool DoesArchetypeMatchRequirements(const FMassArchetypeHandle& ArchetypeHandle) const;` — Note that DoesArchetypeMatchRequirements functions do not check sparse elements. Sparse elements are not a part of immutable composition of a given archetype and can change at runtime, and as such cannot be used for filtering archetypes when the results of that filtering get cached (like in FMassEntityQuery)
- L768 _public prototype_ `bool DoesArchetypeMatchRequirements(const FMassElementBitSet& ArchetypeCompositionBitSet) const;`
- L769 _public function_ `bool DoesArchetypeMatchRequirements(const FMassArchetypeCompositionDescriptor& ArchetypeComposition) const`
- L773 _public prototype_ `bool DoesMatchAnyOptionals(const FMassElementBitSet& ArchetypeCompositionBitSet) const;`
- L774 _public function_ `bool DoesMatchAnyOptionals(const FMassArchetypeCompositionDescriptor& ArchetypeComposition) const`
- L779 _public prototype_ `bool DoesRequireGameThreadExecution() const;`
- L780 _public prototype_ `void ExportRequirements(FMassExecutionRequirements& OutRequirements) const;`
- L785 _protected prototype_ `void SortRequirements();`
- L787 _protected prototype_ `void IncrementChangeCounter();`
- L788 _protected prototype_ `void ConsumeIncrementalChangesCount();`
- L789 _protected prototype_ `bool HasIncrementalChanges() const;`
- L796 _protected prototype_ `bool IsGameThreadOnlySharedFragment(TNotNull<const UScriptStruct*> SharedFragmentType) const;` — A helper function that passes the query over to CachedEntityManager. Main purpose is to have the implementation in cpp and not include the EntityManager header here @todo this function always returns True at the moment, proper implementation waiting for implementation of "type trait information" (WIP)
- L800 _protected member_ `TArray<FMassFragmentRequirementDescription> FragmentRequirements;`
- L801 _protected member_ `TArray<FMassFragmentRequirementDescription> ChunkFragmentRequirements;`
- L802 _protected member_ `TArray<FMassFragmentRequirementDescription> ConstSharedFragmentRequirements;`
- L803 _protected member_ `TArray<FMassFragmentRequirementDescription> SharedFragmentRequirements;`
- L804 _protected member_ `FMassTagBitSet RequiredAllTags;`
- L805 _protected member_ `FMassTagBitSet RequiredAnyTags;`
- L806 _protected member_ `FMassTagBitSet RequiredNoneTags;`
- L811 _protected member_ `FMassTagBitSet RequiredOptionalTags;` — note that optional tags have meaning only if there are no other strict requirements, i.e. everything is optional, so we're looking for anything matching any of the optionals (both tags as well as fragments).
- L812 _protected member_ `FMassFragmentBitSet RequiredAllFragments;`
- L813 _protected member_ `FMassFragmentBitSet RequiredAnyFragments;`
- L814 _protected member_ `FMassFragmentBitSet RequiredOptionalFragments;`
- L815 _protected member_ `FMassFragmentBitSet RequiredNoneFragments;`
- L822 _protected member_ `FMassElementBitSet RequiredAllSparseElements;` — Sparse elements. These can only be tested at runtime - i.e. the results cannot be cached, since as the entities move between archetypes the individual archetypes may or may not contain entities with given sparse elements
- L823 _protected member_ `FMassElementBitSet RequiredAnySparseElements;`
- L824 _protected member_ `FMassElementBitSet RequiredOptionalSparseElements;`
- L825 _protected member_ `FMassElementBitSet RequiredNoneSparseElements;`
- L827 _protected member_ `FMassChunkFragmentBitSet RequiredAllChunkFragments;`
- L828 _protected member_ `FMassChunkFragmentBitSet RequiredOptionalChunkFragments;`
- L829 _protected member_ `FMassChunkFragmentBitSet RequiredNoneChunkFragments;`
- L830 _protected member_ `FMassSharedFragmentBitSet RequiredAllSharedFragments;`
- L831 _protected member_ `FMassSharedFragmentBitSet RequiredOptionalSharedFragments;`
- L832 _protected member_ `FMassSharedFragmentBitSet RequiredNoneSharedFragments;`
- L833 _protected member_ `FMassConstSharedFragmentBitSet RequiredAllConstSharedFragments;`
- L834 _protected member_ `FMassConstSharedFragmentBitSet RequiredOptionalConstSharedFragments;`
- L835 _protected member_ `FMassConstSharedFragmentBitSet RequiredNoneConstSharedFragments;`
- L843 _protected member_ `FMassFragmentBitSet IndirectReadOnlyFragments;` — Fragments that will be accessed on other entities along with this query. These do not affect which entities are discovered by this query, but inform the dependency solver to avoid write contention on these fragments. Used by Linked entity access and Indirect entity access.
- L844 _protected member_ `FMassFragmentBitSet IndirectReadWriteFragments;`
- L850 _protected member_ `TArray<FMassFragmentRequirementDescription> LinkedEntityFragmentRequirements;` — Requirements for fragments on Linked entities. Queries will only discover entities with a linked entity that meets these requirements.
- L852 _protected member_ `TSharedPtr<FMassEntityManager> CachedEntityManager;`
- L855 _private prototype_ `void CacheProperties() const;`
- L856 _private member_ `mutable uint16 bPropertiesCached : 1 = false;`
- L857 _private member_ `mutable uint16 bHasPositiveRequirements : 1 = false;`
- L858 _private member_ `mutable uint16 bHasNegativeRequirements : 1 = false;`
- L864 _private member_ `mutable uint16 bHasOptionalRequirements : 1 = false;` — Indicates that the requirements specify only optional elements, which means any composition having any one of the optional elements will be accepted. Note that RequiredNone* requirements are handled separately and if specified still need to be satisfied.
- L865 _private member_ `mutable uint16 bHasSparseRequirements : 1 = false;`
- L867 _private member_ `uint16 bInitialized : 1 = false;`
- L868 _private member_ `uint16 IncrementalChangesCount = 0;`
- L870 _private member_ `bool bRequiresGameThreadExecution = false;`
- L874 _public prototype_ `FMassFragmentRequirements(std::initializer_list<UScriptStruct*> InitList);` — `UE_DEPRECATED(5.6, "This type of FMassFragmentRequirements is no longer supported. Use one of the other constructors instead.")`
- L877 _public prototype_ `FMassFragmentRequirements(TConstArrayView<const UScriptStruct*> InitList);` — `UE_DEPRECATED(5.6, "This type of FMassFragmentRequirements is no longer supported. Use one of the other constructors instead.")`
- L1019 _function_ `template<> inline FMassFragmentRequirements& FMassFragmentRequirements::AddTagRequirements<EMassFragmentPresence::All>(const FMassTagBitSet& TagBitSet)`
- L1028 _function_ `template<> inline FMassFragmentRequirements& FMassFragmentRequirements::AddTagRequirements<EMassFragmentPresence::Any>(const FMassTagBitSet& TagBitSet)`
- L1037 _function_ `template<> inline FMassFragmentRequirements& FMassFragmentRequirements::AddTagRequirements<EMassFragmentPresence::None>(const FMassTagBitSet& TagBitSet)`
- L1046 _function_ `template<> inline FMassFragmentRequirements& FMassFragmentRequirements::AddTagRequirements<EMassFragmentPresence::Optional>(const FMassTagBitSet& TagBitSet)`
- L1054 _function_ `inline TConstArrayView<FMassFragmentRequirementDescription> FMassFragmentRequirements::GetFragmentRequirements() const`
- L1059 _function_ `inline TConstArrayView<FMassFragmentRequirementDescription> FMassFragmentRequirements::GetChunkFragmentRequirements() const`
- L1064 _function_ `inline TConstArrayView<FMassFragmentRequirementDescription> FMassFragmentRequirements::GetConstSharedFragmentRequirements() const`
- L1069 _function_ `inline TConstArrayView<FMassFragmentRequirementDescription> FMassFragmentRequirements::GetSharedFragmentRequirements() const`
- L1074 _function_ `inline const FMassFragmentBitSet& FMassFragmentRequirements::GetRequiredAllFragments() const`
- L1079 _function_ `inline const FMassFragmentBitSet& FMassFragmentRequirements::GetRequiredAnyFragments() const`
- L1084 _function_ `inline const FMassFragmentBitSet& FMassFragmentRequirements::GetRequiredOptionalFragments() const`
- L1089 _function_ `inline const FMassFragmentBitSet& FMassFragmentRequirements::GetRequiredNoneFragments() const`
- L1094 _function_ `inline const FMassTagBitSet& FMassFragmentRequirements::GetRequiredAllTags() const`
- L1099 _function_ `inline const FMassTagBitSet& FMassFragmentRequirements::GetRequiredAnyTags() const`
- L1104 _function_ `inline const FMassTagBitSet& FMassFragmentRequirements::GetRequiredNoneTags() const`
- L1109 _function_ `inline const FMassTagBitSet& FMassFragmentRequirements::GetRequiredOptionalTags() const`
- L1114 _function_ `inline const FMassChunkFragmentBitSet& FMassFragmentRequirements::GetRequiredAllChunkFragments() const`
- L1119 _function_ `inline const FMassChunkFragmentBitSet& FMassFragmentRequirements::GetRequiredOptionalChunkFragments() const`
- L1124 _function_ `inline const FMassChunkFragmentBitSet& FMassFragmentRequirements::GetRequiredNoneChunkFragments() const`
- L1129 _function_ `inline const FMassSharedFragmentBitSet& FMassFragmentRequirements::GetRequiredAllSharedFragments() const`
- L1134 _function_ `inline const FMassSharedFragmentBitSet& FMassFragmentRequirements::GetRequiredOptionalSharedFragments() const`
- L1139 _function_ `inline const FMassSharedFragmentBitSet& FMassFragmentRequirements::GetRequiredNoneSharedFragments() const`
- L1144 _function_ `inline const FMassConstSharedFragmentBitSet& FMassFragmentRequirements::GetRequiredAllConstSharedFragments() const`
- L1149 _function_ `inline const FMassConstSharedFragmentBitSet& FMassFragmentRequirements::GetRequiredOptionalConstSharedFragments() const`
- L1154 _function_ `inline const FMassConstSharedFragmentBitSet& FMassFragmentRequirements::GetRequiredNoneConstSharedFragments() const`
- L1159 _function_ `inline const FMassElementBitSet& FMassFragmentRequirements::GetRequiredAllSparseElements() const`
- L1164 _function_ `inline const FMassElementBitSet& FMassFragmentRequirements::GetRequiredAnySparseElements() const`
- L1169 _function_ `inline const FMassElementBitSet& FMassFragmentRequirements::GetRequiredOptionalSparseElements() const`
- L1174 _function_ `inline const FMassElementBitSet& FMassFragmentRequirements::GetRequiredNoneSparseElements() const`
- L1179 _function_ `inline const FMassFragmentBitSet& FMassFragmentRequirements::GetIndirectReadOnlyFragments() const`
- L1184 _function_ `inline const FMassFragmentBitSet& FMassFragmentRequirements::GetIndirectReadWriteFragments() const`
- L1189 _function_ `inline bool FMassFragmentRequirements::IsInitialized() const`
- L1194 _function_ `inline bool FMassFragmentRequirements::HasPositiveRequirements() const`
- L1199 _function_ `inline bool FMassFragmentRequirements::HasNegativeRequirements() const`
- L1204 _function_ `inline bool FMassFragmentRequirements::HasOptionalRequirements() const`
- L1209 _function_ `inline bool FMassFragmentRequirements::HasSparseRequirements() const`
- L1214 _function_ `inline bool FMassFragmentRequirements::HasLinkedEntityRequirements() const`
- L1219 _function_ `inline bool FMassFragmentRequirements::DoesRequireGameThreadExecution() const`
- L1224 _function_ `inline void FMassFragmentRequirements::IncrementChangeCounter()`
- L1230 _function_ `inline void FMassFragmentRequirements::ConsumeIncrementalChangesCount()`
- L1235 _function_ `inline bool FMassFragmentRequirements::HasIncrementalChanges() const`

#### struct `FMassEntityCreationRequirements`  
`struct FMassEntityCreationRequirements`  
_L884-960_
- desc: Specifies entity archetypes that can be created. Does NOT imply a filtering constraint; this is purely an access declaration.
- L888 _public function_ `void AddCreatedArchetype(const FMassElementBitSet& InComposition)` — Add by exact composition
- L893 _public function_ `void AddCreatedArchetype(FMassElementBitSet&& InComposition)`
- L899 _public prototype_ `void ExportRequirements(FMassExecutionRequirements& OutRequirements) const;` — Export as "write" access to all fragment types contained in the declared archetypes
- L902 _public prototype_ `void ResolveArchetypes(const FMassEntityManager& EntityManager);` — Populates ArchetypeHandles with all created entity archetypes (EntityManager creates those that don't exist)
- L905 _public function_ `const TArray<FMassArchetypeHandle>& GetCreatedArchetypes()` — Gets the cached array of archetype handles allowed
- L911 _public function_ `bool Contains(const FMassElementBitSet& Composition) const` — Returns true if the required composition list containsthe provided composition
- L920 _public function_ `void ClearCreatedArchetypeHandles()` — Clear the list of created archetype handles to force an update
- L925 _public function_ `void Reset()`
- L931 _public function_ `bool IsEmpty() const`
- L936 _public function_ `const TArray<FMassElementBitSet>& GetCompositions() const`
- L941 _public function_ `bool HasAny(const FMassEntityCreationRequirements& Other) const`
- L958 _private member_ `TArray<FMassArchetypeHandle> ArchetypeHandles;`
- L959 _private member_ `TArray<FMassElementBitSet> Compositions;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mass` (scope `UE`)
- L18 _namespace_ `namespace ErrorReporting` (scope `UE::Mass`)
- L20 _prototype_ `extern FOutputDevice& GetOutputDevice();` (scope `UE::Mass::ErrorReporting`)
- L212 _function_ `checkf(FragmentRequirements.FindByPredicate([FragmentType](const FMassFragmentRequirementDescription& Item) { return Item.StructType == FragmentType; }) == nullptr , TEXT("Duplicated requirements are not` (scope `FMassFragmentRequirements::AddRequirement`)
- L246 _function_ `checkf(FragmentRequirements.FindByPredicate([](const FMassFragmentRequirementDescription& Item) { return Item.StructType == T::StaticStruct(); }) == nullptr , TEXT("Duplicated requirements are not sup` (scope `FMassFragmentRequirements::AddRequirement`)
- L428 _function_ `checkf(ChunkFragmentRequirements.FindByPredicate([](const FMassFragmentRequirementDescription& Item) { return Item.StructType == T::StaticStruct(); }) == nullptr , TEXT("Duplicated requirements are not sup` (scope `FMassFragmentRequirements::AddChunkRequirement`)
- L453 _function_ `checkf(ChunkFragmentRequirements.FindByPredicate([&ChunkFragmentType](const FMassFragmentRequirementDescription& Item) { return Item.StructType == ChunkFragmentType; }) == nullptr , TEXT("Duplicated requirements are not sup` (scope `FMassFragmentRequirements::AddChunkRequirement`)
- L480 _function_ `checkf(ConstSharedFragmentRequirements.FindByPredicate([](const FMassFragmentRequirementDescription& Item) { return Item.StructType == T::StaticStruct(); }) == nullptr , TEXT("Duplicated requirements are not sup` (scope `FMassFragmentRequirements::AddConstSharedRequirement`)
- L511 _function_ `checkf(ConstSharedFragmentRequirements.FindByPredicate([FragmentType](const FMassFragmentRequirementDescription& Item) { return Item.StructType == FragmentType; }) == nullptr , TEXT("Duplicated requirements are no` (scope `FMassFragmentRequirements::AddConstSharedRequirement`)
- L538 _function_ `checkf(SharedFragmentRequirements.FindByPredicate([](const FMassFragmentRequirementDescription& Item) { return Item.StructType == T::StaticStruct(); }) == nullptr , TEXT("Duplicated requirements are not sup` (scope `FMassFragmentRequirements::AddSharedRequirement`)
- L572 _function_ `checkf(SharedFragmentRequirements.FindByPredicate([&SharedFragmentType](const FMassFragmentRequirementDescription& Item) { return Item.StructType == SharedFragmentType; }) == nullptr , TEXT("Duplicated requirements are not supp` (scope `FMassFragmentRequirements::AddSharedRequirement`)
- L613 _function_ `checkfSlow(LinkedEntityFragmentRequirements.FindByPredicate([FragmentType](const FMassFragmentRequirementDescription& Item) { return Item.StructType == FragmentType; }) == nullptr , TEXT("Duplicated linked entity require` (scope `FMassFragmentRequirements::AddLinkedEntityRequirement`)
- L618 _function_ `` (scope `FMassFragmentRequirements::AddLinkedEntityRequirement`)
- L914 _function_ `` (scope `FMassEntityCreationRequirements::Contains`)
- L1013 _function_ `inline uint32 GetTypeHash(const FMassSubsystemRequirements& Instance)`

### `Source/Runtime/MassEntity/Public/MassSettings.h` (Public)


#### class `UMassModuleSettings`  
`class UMassModuleSettings : public UObject`  
_L17-22_
- reflection: `UCLASS(MinimalAPI, Abstract, config = Mass, defaultconfig, collapseCategories)`
- inherits: `UObject`
- desc: A common parent for Mass's per-module settings. Classes extending this class will automatically get registered with the Mass Settings and show under its section in Project Settings.
- L21 _protected prototype_ `virtual void PostInitProperties() override;`

#### class `UMassSettings`  
`class UMassSettings : public UDeveloperSettings`  
_L26-36_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig, DisplayName = "Mass", AutoExpandCategories = "Mass")`
- inherits: `UDeveloperSettings`
- L31 _public prototype_ `void RegisterModuleSettings(UMassModuleSettings& SettingsCDO);`
- L35 _public member_ `TMap<FName, TObjectPtr<UMassModuleSettings>> ModuleSettings;` — `UPROPERTY(VisibleAnywhere, Category = "Mass", NoClear, EditFixedSize, meta = (EditInline))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSENTITY_API`

### `Source/Runtime/MassEntity/Public/MassSparseElementsStorage.h` (Public)


#### struct `UE::Mass::FSparseElementsStorage`  
`struct FSparseElementsStorage`  
_L45-389_
- desc: Storage type for hosting instances of sparse elements. Sparse elements are optional tags and fragments that can be added to an entity without causing it to change archetypes. Sparse elements are not part of Archetype's composition - instead, data on which entity has which elements is stored per archetype chunk. Sparse tags live there (since they don't contain any data per instance). Sparse fragment instances live in FSparseElementsStorage. FSparseElementsStorage provides a way iterate through all instances of a given sparse element type, using UE::Mass::FSparseElementIterator. To create one call FMassEntityManager::CreateSparseElementsIterator Sparse fragment instances are stored in per-type pools (FSparseElementsStorage::FTypePool) which store data in chunks (FSparseElementsStorage::FPackedStructDataChunk), and each chunk contains uniform array of instances of the hosted struct type, along with a bitset indicating which elements are valid (i.e. "set"). Do not use directly. The storage is to be accessed via FMassEntityManager and other means that forward their calls to the entity manager.
- L270 _public prototype_ `void Deinitialize();`
- L276 _public prototype_ `FSparseElementIterator CreateElementIterator(TNotNull<const UScriptStruct*> ElementType);` — Creates and instance of FSparseElementIterator that can be used to iterate over all available instances of sparse fragment of type ElementType
- L278 _public prototype_ `FStructView AddElementToEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType);`
- L282 _public function_ `template<CSparse T> requires CFragment<T> T& AddElementToEntity(FMassEntityHandle EntityHandle)`
- L287 _public function_ `FStructView AddElementInstanceToEntity(FMassEntityHandle EntityHandle, const FConstStructView Instance)`
- L296 _public prototype_ `bool RemoveElementFromEntity(FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType);`
- L300 _public function_ `template<CSparse T> requires CFragment<T> bool RemoveElementFromEntity(FMassEntityHandle EntityHandle)`
- L308 _public prototype_ `void BatchAddElementToEntities(TArray<FMassEntityHandle>& InOutEntityHandles, TNotNull<const UScriptStruct*> ElementType, TArray<FStructView>* OutAddedElements = nullptr);` — @param InOutEntityHandles may get modified by the function - sorted and invalid handles removed
- L309 _public prototype_ `void BatchAddElementToEntities(TArrayView<const FMassEntityHandle> InEntityHandles, TNotNull<const UScriptStruct*> ElementType, TArray<FStructView>* OutAddedElements = nullptr);`
- L313 _public function_ `template<CSparse T> requires CFragment<T> void BatchAddElementToEntities(TArray<FMassEntityHandle>& InOutEntityHandles, TArray<FStructView>* OutAddedElements = nullptr)`
- L318 _public prototype_ `void BatchAddElementInstancesToEntities(TArrayView<const FMassEntityHandle> InEntityHandles, const FStructArrayView& FragmentPayload);`
- L322 _public prototype_ `void BatchAddElementInstancesToEntities(TArrayView<const FMassEntityHandle> InEntityHandles, FConstStructView FragmentInstance);` — Adds FragmentInstance (type and values) to each entity indicated by InEntityHandles
- L328 _public prototype_ `int32 BatchRemoveElementFromEntities(TArray<FMassEntityHandle>& InOutEntityHandles, TNotNull<const UScriptStruct*> ElementType);` — @param InOutEntityHandles may get modified by the function - sorted and invalid handles removed @return num element instances actually removed
- L329 _public prototype_ `int32 BatchRemoveElementFromEntities(TArrayView<const FMassEntityHandle> InEntityHandles, TNotNull<const UScriptStruct*> ElementType);`
- L334 _public function_ `template<CSparse T> requires CFragment<T> int32 BatchRemoveElementFromEntities(TArray<FMassEntityHandle>& InOutEntityHandles)` — @return num element instances actually removed
- L340 _public prototype_ `void RemoveEntity(FMassEntityHandle EntityHandle, const FMassElementBitSet& Elements);` — Clears sparse elements instances belonging to entities indicated by EntityHandles
- L345 _public function_ `uint32 GetNumElementsOfType(TNotNull<const UScriptStruct*> ElementType) const` — Returns the total number of instances of the given sparse element type
- L353 _public function_ `template<CSparse T> requires CFragment<T> uint32 GetNumElementsOfType() const`
- L361 _public function_ `bool HasAnyElementsOfType(TNotNull<const UScriptStruct*> ElementType) const` — Checks whether there are any instances of the given sparse element type
- L369 _public function_ `template<CSparse T> requires CFragment<T> bool HasAnyElementsOfType() const`
- L374 _public prototype_ `FStructView GetMutableElementDataForEntity(const FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType);`
- L375 _public prototype_ `FConstStructView GetElementDataForEntity(const FMassEntityHandle EntityHandle, TNotNull<const UScriptStruct*> ElementType) const;`
- L377 _public prototype_ `void ConfigureType(TNotNull<const UScriptStruct*> ElementType, FTypeConfig& Config);`
- L381 _private prototype_ `template<typename TContainer> void BatchAddElementToEntities(TContainer InEntityHandles, TNotNull<const UScriptStruct*> ElementType, TArray<FStructView>* OutAddedElements);`
- L383 _private member_ `TSparseArray<FTypePool> TypePools;`
- L386 _private prototype_ `FTypePool& GetOrCreateTypePool(TNotNull<const UScriptStruct*> ElementType, const int32 InTypeIndex = INDEX_NONE);` — @param InTypeIndex if INDEX_NONE then the index will be calculated based on ElementType
- L387 _private prototype_ `const FTypePool* GetTypePool(TNotNull<const UScriptStruct*> ElementType) const;`
- L388 _private prototype_ `FTypePool* GetTypePool(TNotNull<const UScriptStruct*> ElementType);`
- L474 _function_ `inline FSparseElementIterator FSparseElementsStorage::CreateElementIterator(TNotNull<const UScriptStruct*> ElementType)`

#### struct `UE::Mass::FSparseElementsStorage::FTypeConfig`  
`struct FTypeConfig`  
_L52-106_
- L54 _public function_ `FTypeConfig(TNotNull<const UScriptStruct*> InElementType) : AllocSizePerElement(InElementType->GetStructureSize()) , ElementType(InElementType)`
- L59 _public prototype_ `FTypeConfig(const FTypeConfig&) = default;`
- L61 _public function_ `SIZE_T GetElementSize() const`
- L66 _public function_ `const UScriptStruct* GetType() const`
- L75 _public function_ `uint32 SetElementsPerChunk(uint32 InElementsPerChunk)` — Converts down to a power of 2 and sets ElementsPerChunk and ChunkIndexShift @return actual value used for ElementsPerChunk
- L87 _public function_ `uint32 GetChunkIndexShift() const`
- L92 _public function_ `uint32 GetElementsPerChunk() const`
- L99 _private prototype_ `FTypeConfig();`
- L100 _private member_ `static constexpr int32 DefaultChunkIndexShift = 7;`
- L101 _private member_ `uint32 ChunkIndexShift = DefaultChunkIndexShift;`
- L102 _private member_ `uint32 ElementsPerChunk = 1 << DefaultChunkIndexShift;`
- L103 _private member_ `uint32 ElementIndexMask = (1 << DefaultChunkIndexShift) - 1;`
- L104 _private member_ `const SIZE_T AllocSizePerElement = 0;`
- L105 _private member_ `TNotNull<const UScriptStruct*> ElementType;`

#### struct `UE::Mass::FSparseElementsStorage::FPackedStructDataChunk`  
`struct FPackedStructDataChunk`  
_L109-213_
- L111 _public member_ `uint8* RawMemory = nullptr;`
- L112 _public member_ `TBitArray<> OccupationMask;`
- L113 _public member_ `uint32 NumElements = 0;`
- L115 _public prototype_ `FPackedStructDataChunk() = default;`
- L117 _public prototype_ `FPackedStructDataChunk(const FPackedStructDataChunk&) = delete;`
- L118 _public prototype_ `FPackedStructDataChunk& operator=(const FPackedStructDataChunk&) = delete;`
- L121 _public function_ `FPackedStructDataChunk(FPackedStructDataChunk&& Other) : RawMemory(Other.RawMemory) , OccupationMask(MoveTemp(Other.OccupationMask)) , NumElements(Other.NumElements)` — Move constructor required since the array holding FPackedStructDataChunk instances will get reallocated
- L130 _public function_ `FPackedStructDataChunk& operator=(FPackedStructDataChunk&& Other)`
- L149 _public function_ `~FPackedStructDataChunk()`
- L158 _public function_ `void Init(const int32 MaxElements, const SIZE_T ElementSize)`
- L164 _public function_ `bool IsInitialized() const`
- L169 _public function_ `bool HasElement(const uint32 ElementIndex)`
- L176 _public function_ `uint8* GetElement(const uint32 ElementIndex, const SIZE_T ElementSize)` — ElementIndex is verified by the caller
- L182 _public function_ `const uint8* GetElement(const uint32 ElementIndex, const SIZE_T ElementSize) const`
- L189 _public function_ `uint8* Add(const uint32 ElementIndex, const SIZE_T ElementSize)` — returns uninitialized memory, to be initialized by the caller
- L197 _public function_ `uint8* Remove(const uint32 ElementIndex, const SIZE_T ElementSize)`
- L209 _private function_ `uint8* GetElementUnsafe(const uint32 ElementIndex, const SIZE_T ElementSize) const`

#### struct `UE::Mass::FSparseElementsStorage::FTypePool`  
`struct FTypePool`  
_L215-267_
- L217 _public prototype_ `FTypePool() = default;`
- L218 _public function_ `FTypePool(const FTypeConfig& InConfig) : Config(InConfig)`
- L222 _public prototype_ `~FTypePool();`
- L224 _public prototype_ `TNotNull<uint8*> Add(uint32 EntityIndex);`
- L225 _public prototype_ `TNotNull<uint8*> Add(uint32 EntityIndex, TNotNull<const uint8*> SourceData);`
- L226 _public prototype_ `TNotNull<uint8*> AddMove(uint32 EntityIndex, TNotNull<uint8*> SourceData);`
- L227 _public prototype_ `FStructView Add_GetView(uint32 EntityIndex);`
- L228 _public prototype_ `bool Remove(uint32 EntityIndex);`
- L229 _public prototype_ `FConstStructView Get(uint32 EntityIndex) const;`
- L230 _public prototype_ `FStructView GetMutable(uint32 EntityIndex);`
- L231 _public prototype_ `FStructView GetOrCreateMutable(uint32 EntityIndex);`
- L233 _public function_ `uint32 GetNumElements() const`
- L238 _public prototype_ `static FTypePool& GetDummyPool();`
- L243 _private function_ `uint32 GetChunkIndex(const uint32 EntityIndex) const`
- L248 _private function_ `uint32 GetElementIndex(const uint32 EntityIndex) const`
- L253 _private prototype_ `FPackedStructDataChunk* GetPackedData(uint32 ChunkIndex);`
- L254 _private prototype_ `const FPackedStructDataChunk* GetPackedData(uint32 ChunkIndex) const;`
- L255 _private prototype_ `FPackedStructDataChunk& GetOrCreatePackedData(uint32 ChunkIndex);`
- L257 _private function_ `void GetChunkAndElementIndex(const uint32 EntityIndex, uint32& OutChunkIndex, uint32& OutElementIndex) const`
- L263 _private member_ `TArray<FPackedStructDataChunk> Chunks;`
- L265 _private member_ `uint32 NumElements = 0;` — stores total number of instances of the given sparse element type
- L266 _private member_ `const FTypeConfig Config;`

#### struct `UE::Mass::FSparseElementIterator`  
`struct FSparseElementIterator`  
_L392-469_
- desc: To iterate over continuous lists of sparse elements of specific types
- L394 _public function_ `FSparseElementIterator() : Pool(FSparseElementsStorage::FTypePool::GetDummyPool())`
- L401 _private function_ `FSparseElementIterator(const FSparseElementsStorage::FTypePool& InPool) : Pool(InPool), ChunkIndex(0)` — instances to be created only via FSparseElementsStorage
- L407 _public function_ `bool IsValid() const`
- L413 _public function_ `explicit operator bool() const`
- L418 _public function_ `void operator++()`
- L444 _public function_ `FStructView GetElementView() const`
- L453 _public function_ `FStructView operator*() const`
- L458 _public function_ `int32 GetEntityIndex() const`
- L463 _public prototype_ `FMassEntityHandle GetEntityHandle(const FMassEntityManager& EntityManager) const;`
- L466 _private member_ `const FSparseElementsStorage::FTypePool& Pool;`
- L467 _private member_ `int32 ChunkIndex = INDEX_NONE;`
- L468 _private member_ `uint32 ElementIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MASSENTITY_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Mass` (scope `UE`)

### `Source/Runtime/MassEntity/Public/MassSubsystemAccess.h` (Public)


#### struct `FMassSubsystemAccess`  
`struct FMassSubsystemAccess`  
_L23-250_
- L25 _public prototype_ `explicit FMassSubsystemAccess(FMassEntityManager* InEntityManager = nullptr);`
- L28 _public prototype_ `explicit FMassSubsystemAccess(UWorld* InWorld);` — `UE_DEPRECATED(5.8, "Use FMassSubsystemAccess(FMassEntityManager*) constructor instead.")`
- L34 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T* GetMutableSubsystem()`
- L47 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T& GetMutableSubsystemChecked()`
- L55 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T* GetSubsystem()`
- L67 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T& GetSubsystemChecked()`
- L78 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T* GetMutableSubsystem(const TSubclassOf<USubsystem> SubsystemClass)`
- L92 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> T& GetMutableSubsystemChecked(const TSubclassOf<USubsystem> SubsystemClass)`
- L101 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T* GetSubsystem(const TSubclassOf<USubsystem> SubsystemClass)`
- L114 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> const T& GetSubsystemChecked(const TSubclassOf<USubsystem> SubsystemClass)`
- L125 _public prototype_ `bool CacheSubsystemRequirements(const FMassSubsystemRequirements& SubsystemRequirements);`
- L126 _public prototype_ `void SetSubsystemRequirements(const FMassSubsystemRequirements& SubsystemRequirements);`
- L128 _public function_ `void GetSubsystemRequirementBits(FMassExternalSubsystemBitSet& OutConstSubsystemsBitSet, FMassExternalSubsystemBitSet& OutMutableSubsystemsBitSet)`
- L134 _public function_ `void SetSubsystemRequirementBits(const FMassExternalSubsystemBitSet& InConstSubsystemsBitSet, const FMassExternalSubsystemBitSet& InMutableSubsystemsBitSet)`
- L141 _public function_ `template<typename T> static constexpr bool DoesRequireWorld()`
- L151 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> static T* FetchSubsystemInstance(UWorld* World)`
- L175 _public function_ `template<typename T, typename = typename TEnableIf<TIsDerivedFrom<T, USubsystem>::IsDerived>::Type> static T* FetchSubsystemInstance()`
- L193 _public prototype_ `static USubsystem* FetchSubsystemInstance(UWorld* World, TSubclassOf<USubsystem> SubsystemClass);`
- L197 _protected function_ `template<typename T> T* GetSubsystemInternal(const int32 SystemIndex)`
- L222 _protected function_ `template<typename T> T* GetSubsystemInternal(const int32 SystemIndex, const TSubclassOf<USubsystem> SubsystemClass)`
- L239 _protected prototype_ `UWorld* GetWorld() const;`
- L240 _protected prototype_ `bool CacheSubsystem(const uint32 SystemIndex);`
- L242 _protected member_ `FMassExternalSubsystemBitSet ConstSubsystemsBitSet;`
- L243 _protected member_ `FMassExternalSubsystemBitSet MutableSubsystemsBitSet;`
- L244 _protected member_ `TArray<USubsystem*> Subsystems;`
- L249 _protected member_ `FMassEntityManager* EntityManager = nullptr;` — Non-owning. Lifetime is guaranteed by the owning FMassExecutionContext which holds a TSharedRef<FMassEntityManager>. Raw pointer avoids atomic ref-count overhead on copy (FMassSubsystemAccess is deep-copied when FMassExecutionContext is copied).

### `Source/Runtime/MassEntity/Public/MassSubsystemBase.h` (Public)


#### struct `UE::Mass::Subsystems::FInitializationState`  
`struct FInitializationState`  
_L19-24_
- L21 _public member_ `uint8 bInitializeCalled : 1 = false;`
- L22 _public member_ `uint8 bPostInitializeCalled : 1 = false;`
- L23 _public member_ `uint8 bOnWorldBeginPlayCalled : 1 = false;`

#### class `UMassSubsystemBase`  
`class UMassSubsystemBase : public UWorldSubsystem`  
_L36-77_
- reflection: `UCLASS(Abstract, config = Mass, defaultconfig, MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: The sole responsibility of this world subsystem class is to serve functionality common to all Mass-related UWorldSubsystem-based subsystems, like whether the subsystems should get created at all.
- L41 _public prototype_ `static bool AreRuntimeMassSubsystemsAllowed(UObject* Outer);`
- L42 _public function_ `UE::Mass::Subsystems::FInitializationState GetInitializationState() const`
- L49 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L50 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L51 _protected prototype_ `virtual void PostInitialize() override;`
- L52 _protected prototype_ `virtual void Deinitialize() override;`
- L53 _protected prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L60 _protected prototype_ `void HandleLateCreation();` — Needs to be called in Initialize for subsystems we want to behave properly when dynamically added after UWorld::BeginPlay (for example via GameplayFeatureActions). This is required for subsystems relying on their PostInitialize and/or OnWorldBeginPlay called.
- L67 _protected function_ `template <UE::Mass::CSubsystem T> void OverrideSubsystemTraits(FSubsystemCollectionBase& Collection)` — Registers given subsystem class as part of Mass type information. Needs to be called as part of Initialize override. Note that calling the function is only required if the registered traits differ from the parent class'.
- L76 _protected member_ `UE::Mass::Subsystems::FInitializationState InitializationState;` — Tracks which initialization function had already been called. Requires the child classes to call Super implementation for their Initialize, PostInitialize, Deinitialize and OnWorldBeginPlayCalled overrides

#### class `UMassTickableSubsystemBase`  
`class UMassTickableSubsystemBase : public UTickableWorldSubsystem`  
_L84-125_
- reflection: `UCLASS(Abstract, config = Mass, defaultconfig, MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- desc: The sole responsibility of this tickable world subsystem class is to serve functionality common to all Mass-related UTickableWorldSubsystem-based subsystems, like whether the subsystems should get created at all.
- L89 _public function_ `UE::Mass::Subsystems::FInitializationState GetInitializationState() const`
- L96 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L97 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L98 _protected prototype_ `virtual void PostInitialize() override;`
- L99 _protected prototype_ `virtual void Deinitialize() override;`
- L100 _protected prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L108 _protected function_ `template <UE::Mass::CSubsystem T> void OverrideSubsystemTraits(FSubsystemCollectionBase& Collection)` — Registers given subsystem class as part of Mass type information. Needs to be called as part of Initialize override. Note that calling the function is only required if the registered traits differ from the parent class'.
- L117 _protected prototype_ `void HandleLateCreation();` — Needs to be called in Initialize for subsystems we want to behave properly when dynamically added after UWorld::BeginPlay (for example via GameplayFeatureActions). This is required for subsystems relying on their PostInitialize and/or OnWorldBeginPlay called.
- L124 _private member_ `UE::Mass::Subsystems::FInitializationState InitializationState;` — Tracks which initialization function had already been called. Requires the child classes to call Super implementation for their Initialize, PostInitialize, Deinitialize and OnWorldBeginPlayCalled overrides

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSENTITY_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mass` (scope `UE`)
- L17 _namespace_ `namespace Subsystems` (scope `UE::Mass`)
- L26 _prototype_ `void RegisterSubsystemType(FSubsystemCollectionBase& Collection, TSubclassOf<USubsystem> SubsystemClass, FSubsystemTypeTraits&& Traits);` (scope `UE::Mass::Subsystems`)
- L27 _prototype_ `void RegisterSubsystemType(TSharedRef<FMassEntityManager> EntityManager, TSubclassOf<USubsystem> SubsystemClass, FSubsystemTypeTraits&& Traits);` (scope `UE::Mass::Subsystems`)

### `Source/Runtime/MassEntity/Public/MassTestableEnsures.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MassEntity/Public/MassTypeManager.h` (Public)


#### struct `UE::Mass::FTypeHandle`  
`struct FTypeHandle`  
_L26-67_
- desc: Handle for identifying and managing types in the type manager
- L28 _public prototype_ `FTypeHandle() = default;`
- L29 _public prototype_ `FTypeHandle(const FTypeHandle&) = default;`
- L31 _public prototype_ `bool operator==(const FTypeHandle&) const = default;`
- L33 _public prototype_ `bool IsValid() const;`
- L35 _public function_ `const UClass* GetClass() const`
- L40 _public function_ `const UScriptStruct* GetScriptStruct() const`
- L50 _public function_ `FName GetFName() const`
- L56 _public function_ `FString ToString() const`
- L64 _private prototype_ `explicit FTypeHandle(TObjectKey<const UStruct> InTypeKey);`
- L66 _private member_ `TObjectKey<const UStruct> TypeKey;`
- L269 _function_ `inline bool FTypeHandle::IsValid() const`

#### struct `UE::Mass::FEmptyTypeTraits`  
`struct FEmptyTypeTraits`  
_L70-72_
- desc: Placeholder to be used when no traits have been specified nor the type is known

#### struct `UE::Mass::FSubsystemTypeTraits`  
`struct FSubsystemTypeTraits`  
_L75-93_
- desc: Traits of USubsystem-based types
- L77 _public prototype_ `FSubsystemTypeTraits() = default;`
- L81 _public function_ `template <typename T> static FSubsystemTypeTraits Make()` — Factory function for creating traits specific to a given subsystem type
- L90 _public member_ `bool bGameThreadOnly = true;` — Whether the subsystem must  be run on the Game Thread
- L92 _public member_ `bool bThreadSafeWrite = false;` — Whether the subsystem supports thread-safe write operations

#### struct `UE::Mass::FSharedFragmentTypeTraits`  
`struct FSharedFragmentTypeTraits`  
_L96-111_
- desc: Traits of Shared Fragment types
- L98 _public prototype_ `FSharedFragmentTypeTraits() = default;`
- L102 _public function_ `template<CSharedFragment T> static FSharedFragmentTypeTraits Make()` — Factory function for creating traits specific to a given shared fragment type
- L110 _public member_ `bool bGameThreadOnly = true;` — Whether the shared fragment has to be used only on the Game Thread

#### struct `UE::Mass::FTypeInfo`  
`struct FTypeInfo`  
_L117-138_
- desc: Wrapper for metadata and traits about specific types. The type is used by the TypeManager to uniformly store information for all types.
- L119 _public typedef_ `using FTypeTraits = TVariant<FEmptyTypeTraits , FSubsystemTypeTraits , FSharedFragmentTypeTraits , FRelationTypeTraits>;`
- L124 _public member_ `FName TypeName;`
- L125 _public member_ `FTypeTraits Traits;`
- L128 _public prototype_ `const FSubsystemTypeTraits* GetAsSystemTraits() const;` — Fetches stored data as FSubsystemTypeTraits, if applicable, or null otherwise
- L131 _public prototype_ `const FSharedFragmentTypeTraits* GetAsSharedFragmentTraits() const;` — Fetches stored data as FSharedFragmentTypeTraits, if applicable, or null otherwise
- L134 _public prototype_ `const FRelationTypeTraits* GetAsRelationTraits() const;` — Fetches stored data as FRelationTypeTraits, if applicable, or null otherwise
- L137 _public prototype_ `const FRelationTypeTraits& GetAsRelationTraitsChecked() const;` — Fetches stored data as FRelationTypeTraits. Will complain if stored data is not of FRelationTypeTraits type
- L277 _function_ `inline const FSubsystemTypeTraits* FTypeInfo::GetAsSystemTraits() const`
- L282 _function_ `inline const FSharedFragmentTypeTraits* FTypeInfo::GetAsSharedFragmentTraits() const`
- L287 _function_ `inline const FRelationTypeTraits* FTypeInfo::GetAsRelationTraits() const`
- L292 _function_ `inline const FRelationTypeTraits& FTypeInfo::GetAsRelationTraitsChecked() const`

#### struct `UE::Mass::FTypeManager`  
`struct FTypeManager : TSharedFromThis<FTypeManager>`  
_L140-264_
- inherits: `TSharedFromThis<FTypeManager>`
- L142 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterBuiltInTypes, FTypeManager& );`
- L167 _public prototype_ `explicit FTypeManager(FMassEntityManager& InEntityManager);`
- L169 _public prototype_ `void RegisterBuiltInTypes();`
- L174 _public prototype_ `bool IsEmpty() const;` — @return whether the type manager instance has any types registered at all.
- L177 _public prototype_ `FTypeHandle RegisterType(TNotNull<const UStruct*> InType, FSubsystemTypeTraits&&);` — Register traits for given subsystem type
- L179 _public prototype_ `FTypeHandle RegisterType(TNotNull<const UStruct*> InType, FSharedFragmentTypeTraits&&);` — Register traits for given shared fragments type
- L181 _public prototype_ `FTypeHandle RegisterType(FRelationTypeTraits&&);` — Register traits for given relation type
- L185 _public prototype_ `template<CSharedFragment T> FTypeHandle RegisterType();` — Registration helper for shared fragments
- L189 _public prototype_ `template<typename T> requires TIsDerivedFrom<typename TRemoveReference<T>::Type, USubsystem>::Value FTypeHandle RegisterType();` — Registration helper for subsystems
- L194 _public prototype_ `const FTypeInfo* GetTypeInfo(FTypeHandle TypeHandle) const;` — @return stored traits for the type represented by TypeHandle, or null if the type is unknown
- L199 _public prototype_ `const FTypeInfo* GetTypeInfo(TObjectKey<const UStruct> TypeKey) const;` — @return stored traits for the type represented by TypeKey, or null if the type is unknown
- L201 _public prototype_ `const FRelationTypeTraits& GetRelationTypeChecked(const FTypeHandle TypeHandle) const;`
- L202 _public prototype_ `const FRelationTypeTraits& GetRelationTypeChecked(const TNotNull<const UScriptStruct*> RelationOrElementType) const;`
- L203 _public prototype_ `FTypeHandle GetRelationTypeHandle(const TNotNull<const UScriptStruct*> RelationOrElementType) const;`
- L204 _public prototype_ `bool IsValidRelationType(const TNotNull<const UScriptStruct*> RelationOrElementType) const;`
- L207 _public typedef_ `using FTypeInfoConstIterator = TMap<FTypeHandle, FTypeInfo>::TConstIterator;` — Alias for the iterator type that can be used to iterate all of stored type traits information
- L214 _public typedef_ `using FSubsystemTypeConstIterator = TSet<FTypeHandle>::TConstIterator;` — Alias for the iterator type that can be used to iterate over stored subsystem types. Note that this iterator will only point to types, not type trait data. Contents of this iterator need to be used with GetTypeInfo to get actual traits data.
- L216 _public prototype_ `FTypeInfoConstIterator MakeIterator() const;`
- L217 _public prototype_ `FSubsystemTypeConstIterator MakeSubsystemIterator() const;`
- L219 _public prototype_ `FMassEntityManager& GetEntityManager();`
- L221 _public prototype_ `static FTypeHandle MakeTypeHandle(TNotNull<const UStruct*> InTypeKey);`
- L227 _public member_ `static FOnRegisterBuiltInTypes OnRegisterBuiltInTypes;` — Broadcasts as part of FTypeManager::RegisterBuiltInTypes call, giving a chance to the external code to register additional types that are supposed to be available from the very start.
- L240 _public prototype_ `static FStaticTypeRegistrationHandle RegisterStaticType(TNotNull<const UStruct*> InType, FSubsystemTypeTraits&& TypeTraits);` — Register a type statically with an RAII handle. Destroying the returned handle removes the type from the static registry (future TypeManager instances won't see it).
- L241 _public prototype_ `static FStaticTypeRegistrationHandle RegisterStaticType(TNotNull<const UStruct*> InType, FSharedFragmentTypeTraits&& TypeTraits);`
- L245 _public prototype_ `template<CSubsystem T> static FStaticTypeRegistrationHandle RegisterStaticType();` — RAII static registration for subsystem types. T must derive from USubsystem.
- L249 _public prototype_ `template<CSharedFragment T> static FStaticTypeRegistrationHandle RegisterStaticType();` — RAII static registration for shared fragment types. T must satisfy CSharedFragment.
- L253 _private prototype_ `FTypeHandle RegisterTypeInternal(TNotNull<const UStruct*> InType, FTypeInfo&&);` — Register traits for given type
- L255 _private member_ `FMassEntityManager& OuterEntityManager;`
- L258 _private member_ `TMap<FTypeHandle, FTypeInfo> TypeDataMap;` — Mapping of types to their info
- L261 _private member_ `TSet<FTypeHandle> SubsystemTypes;` — Contains all registered subsystem types. Can be used to filter access to TypeDataMap
- L263 _private member_ `bool bBuiltInTypesRegistered = false;`
- L297 _function_ `inline bool FTypeManager::IsEmpty() const`
- L302 _function_ `inline FTypeManager::FTypeInfoConstIterator FTypeManager::MakeIterator() const`
- L307 _function_ `inline FTypeManager::FSubsystemTypeConstIterator FTypeManager::MakeSubsystemIterator() const`
- L313 _function_ `template<CSharedFragment T> FTypeHandle FTypeManager::RegisterType()`
- L320 _function_ `template<typename T> requires TIsDerivedFrom<typename TRemoveReference<T>::Type, USubsystem>::Value FTypeHandle FTypeManager::RegisterType()`
- L325 _function_ `inline const FTypeInfo* FTypeManager::GetTypeInfo(FTypeHandle TypeHandle) const`
- L330 _function_ `inline const FTypeInfo* FTypeManager::GetTypeInfo(TObjectKey<const UStruct> TypeKey) const`
- L335 _function_ `inline const FRelationTypeTraits& FTypeManager::GetRelationTypeChecked(const FTypeHandle RelationHandle) const`
- L342 _function_ `inline const FRelationTypeTraits& FTypeManager::GetRelationTypeChecked(const TNotNull<const UScriptStruct*> RelationOrElementType) const`
- L347 _function_ `inline FMassEntityManager& FTypeManager::GetEntityManager()`
- L357 _function_ `inline FTypeHandle FTypeManager::MakeTypeHandle(TNotNull<const UStruct*> InTypeKey)`
- L366 _function_ `template<CSubsystem T> FTypeManager::FStaticTypeRegistrationHandle FTypeManager::RegisterStaticType()`
- L372 _function_ `template<CSharedFragment T> FTypeManager::FStaticTypeRegistrationHandle FTypeManager::RegisterStaticType()`

#### struct `UE::Mass::FTypeManager::FStaticTypeRegistrationHandle`  
`struct FStaticTypeRegistrationHandle`  
_L149-165_
- desc: Move-only, ref-counted handle for a static type registration. The static registry tracks how many handles reference each type — the entry is only removed when the last handle for that type is destroyed. Already-initialized FTypeManager instances are unaffected.
- L151 _public prototype_ `FStaticTypeRegistrationHandle() = default;`
- L152 _public prototype_ `~FStaticTypeRegistrationHandle();`
- L154 _public prototype_ `FStaticTypeRegistrationHandle(FStaticTypeRegistrationHandle&& InOther);`
- L155 _public prototype_ `FStaticTypeRegistrationHandle& operator=(FStaticTypeRegistrationHandle&& InOther);`
- L157 _public prototype_ `FStaticTypeRegistrationHandle(const FStaticTypeRegistrationHandle&) = delete;`
- L158 _public prototype_ `FStaticTypeRegistrationHandle& operator=(const FStaticTypeRegistrationHandle&) = delete;`
- L160 _public prototype_ `bool IsValid() const;`
- L164 _private member_ `TObjectKey<const UStruct> RegisteredType;`
- L352 _function_ `inline bool FTypeManager::FStaticTypeRegistrationHandle::IsValid() const`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MASSENTITY_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Mass` (scope `UE`)
- L45 _function_ `friend inline uint32 GetTypeHash(const FTypeHandle& InHandle)` (scope `UE::Mass`)
- L142 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterBuiltInTypes, FTypeManager& );`

### `Source/Runtime/MassEntity/Public/Relations/MassChildOf.h` (Public)


#### struct `FMassChildOfRelation`  
`struct FMassChildOfRelation : public FMassRelation`  
_L19-22_
- reflection: `USTRUCT()`
- inherits: `FMassRelation`

#### struct `FMassChildOfFragment`  
`struct FMassChildOfFragment : public FMassFragment`  
_L25-31_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L30 _public member_ `FMassEntityHandle Parent;` — `UPROPERTY(VisibleAnywhere, Category = Mass)`

#### class `UMassChildOfRelationEntityCreation`  
`class UMassChildOfRelationEntityCreation : public UMassRelationEntityCreation`  
_L34-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRelationEntityCreation`
- L39 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSENTITY_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mass` (scope `UE`)
- L12 _namespace_ `namespace Relations` (scope `UE::Mass`)
- L14 _externvar_ `extern FTypeHandle ChildOfHandle;` (scope `UE::Mass::Relations`)
- L15 _prototype_ `void RegisterChildOfRelation();` (scope `UE::Mass::Relations`)

### `Source/Runtime/MassEntity/Public/TypeBitSetBuilder.h` (Public)


#### struct `TTypeBitSetTraits`  
`template <typename TBaseType> struct TTypeBitSetTraits final`  
_L13-21_
- desc: Traits configuring finer details of TTypeBitSetBuilder behavior. Provides a way to enforce compile-time checks and validations.
- L20 _public member_ `template <typename TTestedType> static constexpr bool IsValidType = TIsDerivedFrom<TTestedType, TBaseType>::IsDerived;` — Static constexpr boolean to verify if a tested type is valid. Ensures that the tested type is derived from the base type.

#### struct `TTypeBitSetBuilder`  
`template<typename TBaseStruct, typename TUStructType = UScriptStruct, bool bTestInheritanceAtRuntime=WITH_STRUCTUTILS_DEBUG, typename TContainer=FStructTypeBitSet::FBitSetContainer> struct TTypeBitSetBuilder : TTypeBitSetBase<TTypeBitSetBuilder<TBaseStruct, TUStructType, bTestInheritanceAtRuntime>, TBaseStruct, TUStructType, TContainer&, bTestInheritanceAtRuntime>`  
_L33-613_
- inherits: `TTypeBitSetBase<TTypeBitSetBuilder<TBaseStruct,TUStructType,bTestInheritanceAtRuntime>,TBaseStruct,TUStructType,TContainer&,bTestInheritanceAtRuntime>`
- desc: TTypeBitSetBuilder is a template class for building and managing type-specific bitsets. It extends TTypeBitSetBase to provide functionalities specific to bitset building. @param TBaseStruct the base struct type that all stored types must derive from. @param TUStructType Unreal's struct type, typically UScriptStruct or UClass. @param bTestInheritanceAtRuntime flag to enable runtime inheritance checks. @param TContainer the container type for storing bitsets (default is FStructTypeBitSet::FBitSetContainer).
- L36 _public typedef_ `using Super = TTypeBitSetBase<TTypeBitSetBuilder, TBaseStruct, TUStructType, TContainer&, bTestInheritanceAtRuntime>;` — Define the base class for easier reference
- L38 _public typedef_ `using FBaseStruct = TBaseStruct;` — Alias for the base struct type
- L40 _public typedef_ `using FTraits = TTypeBitSetTraits<TBaseStruct>;` — Traits for compile-time checks
- L61 _public typedef_ `using FConstBitSet = const FBitSet;` — Alias for a const bitset, this is the type to use to represent the stored bit set
- L83 _public function_ `TTypeBitSetBuilder(FStructTracker& InStructTracker, FConstBitSet& Source) : Super(const_cast<FBitSet&>(Source)) , StructTracker(InStructTracker)` — Constructor that initializes the builder with a struct tracker and a source bitset. @param InStructTracker the struct tracker to use. @param Source the source bitset to initialize from.
- L96 _private function_ `TTypeBitSetBuilder(FStructTracker& InStructTracker, FConstBitSet& Source, const int32 BitToSet) : Super(const_cast<FBitSet&>(Source)) , StructTracker(InStructTracker)` — Private constructor used internally to initialize with a specific bit index. @param InStructTracker the struct tracker to use. @param Source the source bitset to initialize from. @param BitToSet the bit index to set.
- L110 _public function_ `TTypeBitSetBuilder& operator=(const TTypeBitSetBuilder& Source)` — Assignment operator to copy the bitset from another builder. Ensures that both builders use the same struct tracker. @param Source the other builder to copy from. @return Reference to this builder.
- L123 _public function_ `int32 GetTypeIndex(TNotNull<const TUStructType*> InStructType) const` — Retrieves the index of a struct type within the struct tracker. If the type is not registered, it will be added. @param InStructType the struct type to get the index for. @return The index of the struct type.
- L141 _public function_ `int32 GetTypeIndex(const TUStructType& InStructType) const` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L152 _public function_ `static int32 GetTypeIndex(const FStructTracker& InStructTracker, TNotNull<const TUStructType*> InStructType)` — Static method to get the type index for a given struct type. @param InStructTracker the struct tracker to use. @param InStructType the struct type to get the index for. @return The index of the struct type.
- L170 _public function_ `int32 GetTypeIndex(const FStructTracker& InStructTracker, const TUStructType& InStructType) const` — `UE_DEPRECATED(5.8, "Use overload taking TNotNull")`
- L182 _public function_ `template<typename T> static int32 GetTypeIndex(FStructTracker& InStructTracker)` — Template method to get the type index for a specific C++ type. Ensures at compile-time that the type is valid. @param T the C++ type to get the index for. @return The index of the struct type.
- L196 _public function_ `template<typename T> int32 GetTypeIndex() const` — Template method to get the type index for a specific C++ type. Ensures at compile-time that the type is valid. @param T the C++ type to get the index for. @return The index of the struct type.
- L210 _public function_ `template<typename T> static TTypeBitSetBuilder GetTypeBitSet(const TUStructType& InStructType)` — Template method to create a bitset for a specific C++ type. @param T the C++ type. @param InStructType the Unreal struct type. @return A new TTypeBitSetBuilder instance with the specified type.
- L221 _public function_ `const TUStructType* GetTypeAtIndex(const int32 Index)` — Retrieves the struct type at a given index from the struct tracker. @param Index the index of the struct type. @return Pointer to the struct type.
- L232 _public function_ `template<typename T> inline int32 Add()` — Template method to add a struct type to the bitset. @param T the C++ type to add. @return The index of the added struct type.
- L246 _public function_ `template<typename T> inline int32 Remove()` — Template method to remove a struct type from the bitset. @param T the C++ type to remove. @return The index of the removed struct type.
- L258 _public function_ `inline void Remove(const TTypeBitSetBuilder& Other)` — Removes all bits set in another builder's bitset from this builder's bitset. @param Other the other builder whose bits to remove.
- L269 _public function_ `template<typename T> inline bool Contains() const` — Template method to check if a struct type is contained in the bitset. @param T the C++ type to check. @return True if the type is contained; false otherwise.
- L281 _public function_ `inline TTypeBitSetBuilder operator-(const TTypeBitSetBuilder& Other) const` — Subtracts another builder's bitset from this builder's bitset. @param Other the other builder. @return A new builder with the result.
- L293 _public function_ `inline TTypeBitSetBuilder operator+(const TTypeBitSetBuilder& Other) const` — Adds another builder's bitset to this builder's bitset. @param Other the other builder. @return A new builder with the result.
- L305 _public function_ `inline TTypeBitSetBuilder operator&(const TTypeBitSetBuilder& Other) const` — Performs a bitwise AND with another builder's bitset. @param Other the other builder. @return A new builder with the result.
- L315 _public function_ `inline TTypeBitSetBuilder operator|(const TTypeBitSetBuilder& Other) const` — Performs a bitwise OR with another builder's bitset. @param Other the other builder. @return A new builder with the result.
- L325 _public function_ `inline TTypeBitSetBuilder GetOverlap(const TTypeBitSetBuilder& Other) const` — Gets the overlap between this builder's bitset and another's. @param Other the other builder. @return A new builder representing the overlap.
- L335 _public function_ `inline bool IsEquivalent(const TTypeBitSetBuilder& Other) const` — Checks if this builder's bitset is equivalent to another's. @param Other the other builder. @return True if equivalent; false otherwise.
- L345 _public function_ `inline bool HasAll(const TTypeBitSetBuilder& Other) const` — Checks if this builder's bitset has all bits set in another's. @param Other the other builder. @return True if all bits are set; false otherwise.
- L355 _public function_ `inline bool HasAny(const TTypeBitSetBuilder& Other) const` — Checks if this builder's bitset has any bits set in another's. @param Other the other builder. @return True if any bits are set; false otherwise.
- L365 _public function_ `inline bool HasNone(const TTypeBitSetBuilder& Other) const` — Checks if this builder's bitset has none of the bits set in another's. @param Other the other builder. @return True if no bits are set; false otherwise.
- L374 _public function_ `bool IsEmpty() const` — Checks if the bitset is empty. @return True if empty; false otherwise.
- L384 _public function_ `inline bool IsBitSet(const int32 BitIndex) const` — Checks if a specific bit is set in the bitset. @param BitIndex the index of the bit to check. @return True if the bit is set; false otherwise.
- L393 _public function_ `int32 CountStoredTypes() const` — Counts the number of set bits in the bitset. @return The number of set bits.
- L402 _public function_ `int32 GetMaxNum() const` — Retrieves the maximum number of types tracked by the struct tracker. @return The maximum number of types.
- L412 _public function_ `static int32 GetMaxNum(const FStructTracker& StructTracker)` — Static method to get the maximum number of types from a struct tracker. @param StructTracker the struct tracker to query. @return The maximum number of types.
- L422 _public function_ `inline bool operator==(const TTypeBitSetBuilder& Other) const` — Equality operator to compare two builders. @param Other the other builder to compare. @return True if equal; false otherwise.
- L432 _public function_ `inline bool operator!=(const TTypeBitSetBuilder& Other) const` — Inequality operator to compare two builders. @param Other the other builder to compare. @return True if not equal; false otherwise.
- L441 _public function_ `operator FConstBitSet() const` — Conversion operator to a const bitset. @return A const reference to the bitset.
- L454 _public function_ `template<typename TOutStructType, typename Allocator> void ExportTypes(TArray<const TOutStructType*, Allocator>& OutTypes) const` — Exports the types stored in the bitset to an output array. Note: This method can be slow due to the use of weak pointers in the struct tracker. @param TOutStructType the output struct type. @param Allocator the allocator for the output array. @param OutTypes the array to populate with struct types.
- L474 _public function_ `void ExportTypes(TFunctionRef<bool(const TUStructType*)> Callback) const` — Lists all types used by this bitset, calling the provided callback for each one. Returning false from the callback will early-out of iterating over the types. Note: This method can be slow due to the use of weak pointers in the struct tracker. @param Callback the callback function to call for each type.
- L492 _public function_ `SIZE_T GetAllocatedSize() const` — Retrieves the allocated size of the bitset. @return The allocated size in bytes.
- L501 _public function_ `FString DebugGetStringDesc() const` — Provides a debug string description of the bitset contents. @return A string describing the contents of the bitset.
- L517 _public function_ `void DebugGetStringDesc(FOutputDevice& Ar) const` — Provides a debug string description of the bitset contents, via the provided FOutputDevice. @param Ar the output device to write to.
- L533 _public function_ `void DebugGetIndividualNames(TArray<FName>& OutFNames) const` — Gets the names of individual struct types in the bitset. @param OutFNames Array to populate with struct type names.
- L549 _public function_ `FName DebugGetStructTypeName(const int32 StructTypeIndex) const` — Retrieves the name of a struct type at a given index. @param StructTypeIndex the index of the struct type. @return The name of the struct type.
- L558 _public function_ `TConstArrayView<TWeakObjectPtr<const TUStructType>> DebugGetAllStructTypes() const` — Retrieves all registered struct types as a view. @return Array view of weak pointers to struct types.
- L569 _public function_ `static FName DebugGetStructTypeName(const FStructTracker& StructTracker, const int32 StructTypeIndex)` — Static method to retrieve the name of a struct type at a given index from a struct tracker. @param StructTracker the struct tracker to use. @param StructTypeIndex the index of the struct type. @return The name of the struct type.
- L579 _public function_ `static TConstArrayView<TWeakObjectPtr<const TUStructType>> DebugGetAllStructTypes(const FStructTracker& StructTracker)` — Static method to retrieve all registered struct types from a struct tracker. @param StructTracker the struct tracker to use. @return Array view of weak pointers to struct types.
- L586 _protected function_ `const TBitArray<>& DebugGetStructTypesBitArray() const` — For unit testing purposes only
- L591 _protected function_ `TBitArray<>& DebugGetMutableStructTypesBitArray()`
- L602 _protected function_ `FStructTracker& GetStructTracker() const` — Retrieves the struct tracker used by this builder. @return Reference to the struct tracker.
- L612 _private member_ `FStructTracker& StructTracker;` — Reference to the struct tracker used. It's TTypeBitSetBuilder's instance creator responsibility to ensure that the instance doesn't outlive the referenced object.

#### struct `TTypeBitSetBuilder::FBitSet`  
`struct FBitSet : TContainer`  
_L47-57_
- inherits: `TContainer`
- desc: Internal bitset class extending TContainer. Used to ensure proper comparison of bitsets.
- L53 _public function_ `inline bool operator==(const FBitSet& Other) const` — Equality operator to compare bitsets. Uses CompareSetBits to compare the set bits, ignoring missing bits.
