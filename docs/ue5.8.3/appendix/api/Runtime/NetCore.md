# Runtime / NetCore

- module root: `Source/Runtime/Net/Core`
- headers: 47; symbols: 2361
- symbol kinds: class=63, delegate=10, enum=51, enumerator=233, externvar=16, function=550, macro=187, member=489, namespace=98, prototype=526, struct=74, typedef=58, union=4, variable=2
- PublicDependencyModuleNames: Core, CoreUObject, NetCommon, TraceLog

### `Source/Runtime/Net/Core/Classes/Net/Core/Analytics/NetAnalyticsAggregatorConfig.h` (Public)


#### struct `FNetAnalyticsDataConfig`  
`struct FNetAnalyticsDataConfig`  
_L16-27_
- reflection: `USTRUCT()`
- desc: Configuration for FNetAnalyticsData - enabling/disabling analytics data, based on DataName
- L22 _public member_ `FName DataName;` — `UPROPERTY(config)` — The name of the analytics data type (should match analytics stat name)
- L26 _public member_ `bool bEnabled = false;` — `UPROPERTY(config)` — Whether or not the specified analytics data type, is enabled

#### class `UNetAnalyticsAggregatorConfig`  
`class UNetAnalyticsAggregatorConfig : public UObject`  
_L33-44_
- reflection: `UCLASS(config=Engine, PerObjectConfig)`
- inherits: `UObject`
- desc: Configuration for FNetAnalyticsAggregator - loaded PerObjectConfig, for each NetDriverName
- L38 _protected prototype_ `void OverridePerObjectConfigSection(FString& SectionName) override;`
- L43 _public member_ `TArray<FNetAnalyticsDataConfig> NetAnalyticsData;` — `UPROPERTY(config)` — Registers FNetAnalyticsData data holders, by DataName - and specifies whether they are enabled or disabled

### `Source/Runtime/Net/Core/Classes/Net/Serialization/FastArraySerializer.h` (Public)


#### class `TFastArrayTypeHelper`  
`template <typename FastArrayType> class TFastArrayTypeHelper`  
_L231-260_
- desc: Helper to get auto-deduced FastArrayItemType from FastArraySerializer
- L241 _private member_ `static constexpr auto FastArrayTypePtr = [] { if constexpr (TModels_V<CGetFastArrayItemTypeFuncable, FastArrayType>) { return FastArrayType::GetFastArrayItemTypePtr(); } else { return static_cast<int*>(nullptr); } }();` — Helper to always return a Type even if GetFastArrayItemTypePtr is not defined
- L242 _private function_ ``
- L254 _public typedef_ `using FastArrayItemType = typename TRemovePointer<typename std::decay<decltype(FastArrayTypePtr)>::type>::Type;`
- L259 _public function_ `static constexpr bool HasValidFastArrayItemType()` — Returns true if auto detected FastArrayItemType is a valid FastArrayItemType

#### struct `TFastArrayTypeHelper::CGetFastArrayItemTypeFuncable`  
`struct CGetFastArrayItemTypeFuncable`  
_L234-238_
- L237 _public prototype_ `template <typename InFastArrayType, typename...> auto Requires(InFastArrayType* FastArray) -> decltype(FastArray->GetFastArrayItemTypePtr());`

#### class `FNetFastTArrayBaseState`  
`class FNetFastTArrayBaseState : public INetDeltaBaseState`  
_L263-294_
- inherits: `INetDeltaBaseState`
- desc: Custom INetDeltaBaseState used by Fast Array Serialization
- L267 _public function_ `FNetFastTArrayBaseState() : ArrayReplicationKey(INDEX_NONE)`
- L271 _public function_ `virtual bool IsStateEqual(INetDeltaBaseState* OtherState)`
- L285 _public function_ `virtual void CountBytes(FArchive& Ar) const override`
- L291 _public member_ `TMap<int32, int32> IDToCLMap;` — Maps an element's Replication ID to Index.
- L293 _public member_ `int32 ArrayReplicationKey;`

#### struct `FFastArraySerializerItem`  
`struct FFastArraySerializerItem`  
_L298-365_
- reflection: `USTRUCT()`
- desc: Base struct for items using Fast TArray Replication
- L302 _public function_ `FFastArraySerializerItem() : ReplicationID(INDEX_NONE), ReplicationKey(INDEX_NONE), MostRecentArrayReplicationKey(INDEX_NONE)`
- L308 _public function_ `FFastArraySerializerItem(const FFastArraySerializerItem &InItem) : ReplicationID(INDEX_NONE), ReplicationKey(INDEX_NONE), MostRecentArrayReplicationKey(INDEX_NONE)`
- L314 _public function_ `FFastArraySerializerItem& operator=(const FFastArraySerializerItem& In)`
- L326 _public member_ `int32 ReplicationID;` — `UPROPERTY(NotReplicated)`
- L329 _public member_ `int32 ReplicationKey;` — `UPROPERTY(NotReplicated)`
- L332 _public member_ `int32 MostRecentArrayReplicationKey;` — `UPROPERTY(NotReplicated)`
- L341 _public function_ `inline void PreReplicatedRemove(const struct FFastArraySerializer& InArraySerializer)` — Called right before deleting element during replication. @param InArraySerializer	Array serializer that owns the item and has triggered the replication call NOTE: intentionally not virtual; invoked via templated code, @see FExampleItemEntry
- L349 _public function_ `inline void PostReplicatedAdd(const struct FFastArraySerializer& InArraySerializer)` — Called after adding and serializing a new element @param InArraySerializer	Array serializer that owns the item and has triggered the replication call NOTE: intentionally not virtual; invoked via templated code, @see FExampleItemEntry
- L356 _public function_ `inline void PostReplicatedChange(const struct FFastArraySerializer& InArraySerializer)` — Called after updating an existing element with new data @param InArraySerializer	Array serializer that owns the item and has triggered the replication call NOTE: intentionally not virtual; invoked via templated code, @see FExampleItemEntry
- L364 _public function_ `inline FString GetDebugString()` — Called when logging LogNetFastTArray (log or lower verbosity) @param InArraySerializer	Array serializer that owns the item and has triggered the replication call NOTE: intentionally not virtual; invoked via templated code, @see FExampleItemEntry

#### struct `FFastArraySerializerGuidReferences`  
`struct FFastArraySerializerGuidReferences`  
_L368-381_
- desc: Struct for holding guid references
- L371 _public member_ `TSet<FNetworkGUID> UnmappedGUIDs;` — List of guids that were unmapped so we can quickly check
- L374 _public member_ `TSet<FNetworkGUID> MappedDynamicGUIDs;` — List of guids that were mapped so we can move them to unmapped when necessary (i.e. actor channel closes)
- L377 _public member_ `TArray<uint8> Buffer;` — Buffer of data to re-serialize when the guids are mapped
- L380 _public member_ `int32 NumBufferBits;` — Number of bits in the buffer

#### struct `FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair`  
`struct FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair`  
_L387-392_
- desc: Struct used only in FFastArraySerializer::FastArrayDeltaSerialize, however, declaring it within the templated function causes crashes on some clang compilers
- L389 _public function_ `FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair(int32 _idx, int32 _id) : Idx(_idx), ID(_id)`
- L390 _public member_ `int32 Idx;`
- L391 _public member_ `int32 ID;`

#### enum `EFastArraySerializerDeltaFlags`  
`enum class EFastArraySerializerDeltaFlags : uint8`  
_L395-403_
- reflection: `UENUM()`
- L397 _public enumerator_ `None` — No flags.
- L398 _public enumerator_ `HasBeenSerialized = 1 << 0` — Set when serialization at least once (i.e., this struct has been written or read).
- L399 _public enumerator_ `HasDeltaBeenRequested = 1 << 1` — Set if users requested Delta Serialization for this struct.
- L400 _public enumerator_ `IsUsingDeltaSerialization = 1 << 2` — This will remain unset until we've serialized at least once.

#### struct `FFastArraySerializer`  
`struct FFastArraySerializer`  
_L408-745_
- reflection: `USTRUCT()`
- desc: Base struct for wrapping the array used in Fast TArray Replication
- L412 _public prototype_ `FFastArraySerializer();`
- L413 _public prototype_ `~FFastArraySerializer();`
- L416 _public member_ `TMap<int32, int32> ItemMap;` — Maps Element ReplicationID to Array Index.
- L420 _public member_ `int32 IDCounter;` — `UPROPERTY(NotReplicated, Transient)` — Counter used to assign IDs to new elements.
- L424 _public member_ `int32 ArrayReplicationKey;` — `UPROPERTY(NotReplicated)` — Counter used to track array replication.
- L427 _public member_ `TMap<int32, FFastArraySerializerGuidReferences> GuidReferencesMap;` — List of items that need to be re-serialized when the referenced objects are mapped
- L430 _public member_ `TMap<int32, FGuidReferencesMap> GuidReferencesMap_StructDelta;` — List of items that need to be re-serialized when the referenced objects are mapped.
- L434 _public member_ `UObject* OwningObject;` — Object that is replicating this fast array
- L437 _public member_ `int32 RepIndex;` — Property index of this array in the owning object's replication layout
- L441 _public function_ `void MarkItemDirty(FFastArraySerializerItem & Item)` — This must be called if you add or change an item in the array
- L457 _public function_ `void MarkArrayDirty()` — This must be called if you just remove something from the array
- L467 _public function_ `void IncrementArrayReplicationKey()`
- L494 _public prototype_ `template<typename Type, typename SerializerType> static bool FastArrayDeltaSerialize(TArray<Type>& Items, FNetDeltaSerializeInfo& Parms, SerializerType& ArraySerializer);` — Performs "standard" delta serialization on the items in the FastArraySerializer. This method relies more on the INetSerializeCB interface and custom logic and sends all properties that aren't marked as SkipRep, regardless of whether or not they've changed. This will be less CPU intensive, but require more bandwidth. @param Items				Array of items owned by ArraySerializer. @param Parms				Set of parms that dictate what serialization will do / return. @param ArraySerializer	The typed subclass of FFastArraySerializer that we're serializing.
- L501 _public function_ `inline void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize)` — Called before removing elements and after the elements themselves are notified.  The indices are valid for this function call only! NOTE: intentionally not virtual; invoked via templated code, @see FExampleItemEntry
- L508 _public function_ `inline void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize)` — Called after adding all new elements and after the elements themselves are notified.  The indices are valid for this function call only! NOTE: intentionally not virtual; invoked via templated code, @see FExampleItemEntry
- L515 _public function_ `inline void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize)` — Called after updating all existing elements with new data and after the elements themselves are notified. The indices are valid for this function call only! NOTE: intentionally not virtual; invoked via templated code, @see FExampleItemEntry
- L544 _public function_ `template<typename Type, typename SerializerType> bool ShouldWriteFastArrayItem(const Type& Item, const bool bIsWritingOnClient) const` — Helper function for FastArrayDeltaSerialize to consolidate the logic of whether to consider writing an item in a fast TArray during network serialization. For client replay recording, we don't want to write any items that have been added to the array predictively.
- L549 _public function_ `void SetDeltaSerializationEnabled(const bool bEnabled)`
- L568 _public function_ `const EFastArraySerializerDeltaFlags GetDeltaSerializationFlags() const`
- L573 _public function_ `static const int32 GetMaxNumberOfAllowedChangesPerUpdate()`
- L578 _public function_ `static const int32 GetMaxNumberOfAllowedDeletionsPerUpdate()`
- L584 _public function_ `void CachePushModelState(UObject* Object, const uint16 PropertyRepIndex)`
- L596 _private member_ `static int32 MaxNumberOfAllowedChangesPerUpdate;`
- L597 _private member_ `static int32 MaxNumberOfAllowedDeletionsPerUpdate;`
- L598 _private member_ `static FAutoConsoleVariableRef CVarMaxNumberOfAllowedChangesPerUpdate;`
- L599 _private member_ `static FAutoConsoleVariableRef CVarMaxNumberOfAllowedDeletionsPerUpdate;`
- L735 _private prototype_ `template<typename Type, typename SerializerType> static bool FastArrayDeltaSerialize_DeltaSerializeStructs(TArray<Type>& Items, FNetDeltaSerializeInfo& Parms, SerializerType& ArraySerializer);` — Performs "struct delta" serialization on the items in the FastArraySerializer. This method relies more directly on FRepLayout for management, and will only send properties that have changed since the last update. This is potentially more CPU intensive since we'll be doing comparisons, but should require less bandwidth. For this method to work, the following **must** be true: - Your array of FFastArraySerializerItems must be a top level UPROPERTY within your FFastArraySerializer. - Your array of FFastArraySerializerItems must **not** be marked RepSkip. - Your array of FFastArraySerializerItems must be the **only** replicated array of FFastArraySerializerItems within the FastArraySerializer. Note, it's OK to have multiple arrays of items, as long as only one is replicated (all others **must** be marked RepSkip). - Your FFastArraySerializer must not be nested in a static array. - Your array of FFastArraySerializerItem must not be nested in a static array. @param Items				Array of items owned by ArraySerializer. @param Parms				Set of parms that dictate what serialization will do / return. @param ArraySerializer	The typed subclass of FFastArraySerializer that we're serializing.
- L740 _private member_ `int32 CachedNumItems;` — Cached item counts, used for fast sanity checking when writing.
- L741 _private member_ `int32 CachedNumItemsToConsiderForWriting;`
- L744 _private member_ `EFastArraySerializerDeltaFlags DeltaFlags;` — `UPROPERTY(NotReplicated, Transient)`
- L1207 _function_ `template<typename Type, typename SerializerType > bool FFastArraySerializer::FastArrayDeltaSerialize(TArray<Type> &Items, FNetDeltaSerializeInfo& Parms, SerializerType& ArraySerializer)` — The function that implements Fast TArray Replication
- L1645 _function_ `template<typename Type, typename SerializerType> bool FFastArraySerializer::FastArrayDeltaSerialize_DeltaSerializeStructs(TArray<Type>& Items, FNetDeltaSerializeInfo& Parms, SerializerType& ArraySerializer)`

#### struct `FFastArraySerializer::FPostReplicatedReceiveParameters`  
`struct FPostReplicatedReceiveParameters`  
_L521-527_
- desc: If a function with the signature void PostReplicatedReceive(const FFastArraySerializer::FPostReplicatedReceiveParameters& Parameters) is defined in the derived struct It will be called after each call to NetDeltaSerialize on the receiving end, including if we have mapped some unmapped objects
- L524 _public member_ `int32 OldArraySize;` — This is the size that the array had before the receive.
- L526 _public member_ `uint32 bHasMoreUnmappedReferences : 1U;` — `UE_DEPRECATED(5.4, "This is unsafe to use and will be removed.")`

#### struct `FFastArraySerializer::CPostReplicatedReceiveFuncable`  
`struct CPostReplicatedReceiveFuncable`  
_L533-537_
- desc: Concept used to detect if PostReplicatedReceive is defined or not
- L536 _public prototype_ `template <typename InFastArrayType, typename...> auto Requires(InFastArrayType* FastArray, const FFastArraySerializer::FPostReplicatedReceiveParameters& Parameters) -> decltype(FastArray->PostReplicatedReceive(Parameters));`

#### struct `FFastArraySerializer::FFastArraySerializerHeader`  
`struct FFastArraySerializerHeader`  
_L602-619_
- desc: Struct containing common header data that is written / read when serializing Fast Arrays.
- L605 _public member_ `int32 ArrayReplicationKey;` — The current ArrayReplicationKey.
- L608 _public member_ `int32 BaseReplicationKey;` — The previous ArrayReplicationKey.
- L611 _public member_ `int32 NumChanged;` — The number of changed elements (adds or removes).
- L618 _public member_ `TArray<int32, TInlineAllocator<8>> DeletedIndices;` — The list of deleted elements. When writing, this will be treated as IDs that are translated to indices prior to serialization. When reading, this will be actual indices.

#### struct `FFastArraySerializer::TFastArraySerializeHelper`  
`template<typename Type, typename SerializerType> struct TFastArraySerializeHelper`  
_L626-714_
- desc: Helper struct that contains common methods / logic for standard Fast Array serialization and Delta Struct Fast Array serialization.
- L629 _public member_ `UScriptStruct* Struct;` — Array element type struct.
- L632 _public member_ `TArray<Type>& Items;` — Set of array elements we're serializing.
- L635 _public member_ `SerializerType& ArraySerializer;` — The actual FFastArraySerializer struct we're serializing.
- L638 _public member_ `FNetDeltaSerializeInfo& Parms;` — Cached DeltaSerialize params.
- L645 _public prototype_ `void ConditionalRebuildItemMap();` — Conditionally rebuilds the ID to Index map for items. This is generally only necessary on first serialization, or if we receive deletes and can no longer trust our ordering is correct.
- L648 _public prototype_ `int32 CalcNumItemsForConsideration() const;` — Calculates the number of Items that actually need to be written.
- L651 _public prototype_ `void ConditionalLogSerializerState(const TMap<int32, int32>* OldIDToKeyMap) const;` — Conditionally logs the important state of the serializer. For debug purposes only.
- L661 _public prototype_ `bool ConditionalCreateNewDeltaState(const TMap<int32, int32>& OldIDToKeyMap, const int32 BaseReplicationKey);` — Checks to see if the ArrayReplicationKey has changed, and if so creates a new DeltaState that is passed out to the caller. Note, this state may just be a copy of a previous state, or a brand new state. @return	True if the keys were different and a state was created. False if the keys were the same, and we can skip serialization.
- L668 _public prototype_ `void BuildChangedAndDeletedBuffers( TMap<int32, int32>& NewIDToKeyMap, const TMap<int32, int32>* OldIDToKeyMap, TArray<FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair, TInlineAllocator<8>>& ChangedElements, TArray<int32, TInlineAllocator<8>>& DeletedElements);` — Iterates over the current set of properties, comparing their keys with our old state, to figure out which have changed and need to be serialized. Also populates a list of elements that are no longer in our list (by ID).
- L677 _public prototype_ `void BuildChangedAndDeletedBuffersFromDefault( TMap<int32, int32>& NewIDToKeyMap, TArray<FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair, TInlineAllocator<8>>& ChangedElements) const;` — Variant of BuildChangedAndDeletedBuffersFromDefault used when we initialize from the default state which we are not suppose to modify
- L682 _public prototype_ `void WriteDeltaHeader(FFastArraySerializerHeader& Header) const;` — Writes out a FFastArraySerializerHeader
- L685 _public prototype_ `bool ReadDeltaHeader(FFastArraySerializerHeader& Header) const;` — Reads in a FFastArraySerializerHeader
- L693 _public prototype_ `template<typename GuidMapType> void PostReceiveCleanup( FFastArraySerializerHeader& Header, TArray<int32, TInlineAllocator<8>>& ChangedIndices, TArray<int32, TInlineAllocator<8>>& AddedIndices, GuidMapType& GuidMap);` — Manages any cleanup work that needs to be done after receiving elements, such as looking for items that were implicitly deleted, removing all deleted items, firing off any PostReceive / PostDeleted events, etc.
- L701 _public function_ `template<typename FastArrayType = SerializerType> inline typename TEnableIf<TModels_V<CPostReplicatedReceiveFuncable, FastArrayType, const FFastArraySerializer::FPostReplicatedReceiveParameters>, void>::Type CallPostReplicatedReceiveOrNot(int32 OldArraySize)` — Conditionally invoke PostReplicatedReceive method depending on if is defined or not
- L710 _public function_ `template<typename FastArrayType = SerializerType> inline typename TEnableIf<!TModels_V<CPostReplicatedReceiveFuncable, FastArrayType, const FFastArraySerializer::FPostReplicatedReceiveParameters>, void>::Type CallPostReplicatedReceiveOrNot(int32)`
- L748 _function_ `template<typename Type, typename SerializerType> void FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::ConditionalRebuildItemMap()`
- L776 _function_ `template<typename Type, typename SerializerType> int32 FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::CalcNumItemsForConsideration() const`
- L793 _function_ `template<typename Type, typename SerializerType> void FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::ConditionalLogSerializerState(const TMap<int32, int32>* OldIDToKeyMap) const`
- L819 _function_ `template<typename Type, typename SerializerType> bool FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::ConditionalCreateNewDeltaState(const TMap<int32, int32>& OldIDToKeyMap, const int32 BaseReplicationKey)`
- L857 _function_ `template<typename Type, typename SerializerType> void FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::BuildChangedAndDeletedBuffersFromDefault( TMap<int32, int32>& NewIDToKeyMap, TArray<FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair, TInlineAllocator<8>>& ChangedElements) const`
- L896 _function_ `template<typename Type, typename SerializerType> void FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::BuildChangedAndDeletedBuffers( TMap<int32, int32>& NewIDToKeyMap, const TMap<int32, int32>* OldIDToKeyMap, TArray<FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair, TInlineAllocator<8>>& ChangedElements, TArray<int32, TInlineAllocator<8>>& DeletedElements)`
- L980 _function_ `template<typename Type, typename SerializerType> void FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::WriteDeltaHeader(FFastArraySerializerHeader& Header) const`
- L1013 _function_ `template<typename Type, typename SerializerType> bool FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::ReadDeltaHeader(FFastArraySerializerHeader& Header) const`
- L1078 _function_ `template<typename Type, typename SerializerType> template<typename GuidMapType> void FFastArraySerializer::TFastArraySerializeHelper<Type, SerializerType>::PostReceiveCleanup( FFastArraySerializerHeader& Header, TArray<int32, TInlineAllocator<8>>& ChangedIndices, TArray<int32, TInlineAllocator<8>>& AddedIndices, GuidMapType& GuidMap)`

#### struct `FFastArrayDeltaSerializeParams`  
`struct FFastArrayDeltaSerializeParams`  
_L1626-1642_
- L1628 _public member_ `FNetDeltaSerializeInfo& DeltaSerializeInfo;`
- L1629 _public member_ `FFastArraySerializer& ArraySerializer;`
- L1631 _public member_ `const TFunction<void(void*, const FFastArrayDeltaSerializeParams&)> PreReplicatedRemove;`
- L1632 _public member_ `const TFunction<void(void*, const FFastArrayDeltaSerializeParams&)> PostReplicatedAdd;`
- L1633 _public member_ `const TFunction<void(void*, const FFastArrayDeltaSerializeParams&)> PostReplicatedChange;`
- L1634 _public member_ `const TFunction<void(void*, const FFastArrayDeltaSerializeParams&, const uint32)> ReceivedItem;`
- L1636 _public member_ `TArray<FFastArraySerializer_FastArrayDeltaSerialize_FIdxIDPair, TInlineAllocator<8>>* WriteChangedElements = nullptr;`
- L1637 _public member_ `FNetFastTArrayBaseState* WriteBaseState = nullptr;`
- L1638 _public member_ `TArray<int32, TInlineAllocator<8>>* ReadChangedElements = nullptr;`
- L1639 _public member_ `TArray<int32, TInlineAllocator<8>>* ReadAddedElements = nullptr;`
- L1640 _public member_ `int32 ReadNumChanged = INDEX_NONE;`
- L1641 _public member_ `int32 ReadArrayReplicationKey = INDEX_NONE;`

#### struct `FFastArraySerializer::FastArrayDeltaSerialize_DeltaSerializeStructs::FFastArrayItemCallbackHelper`  
`struct FFastArrayItemCallbackHelper`  
_L1657-1681_
- desc: These methods are exposed on FastArraySerializerItems, but they aren't virtual. Further, we may not know the exact type when we want to call them, and won't safely be able to cast to the type in non-templated code. Maybe this defeats the purpose of having them not virtual in the first place. However, for now ReceivedItem and PostReplicatedChanged are the only ones that will actually be called in this way, whereas PostReplicatedAdd and PreReplicatedRemove will still be called from templated code.
- L1659 _public function_ `static void PreReplicatedRemove(void* FastArrayItem, const struct FFastArrayDeltaSerializeParams& Params)`
- L1664 _public function_ `static void PostReplicatedAdd(void* FastArrayItem, const struct FFastArrayDeltaSerializeParams& Params)`
- L1669 _public function_ `static void PostReplicatedChange(void* FastArrayItem, const struct FFastArrayDeltaSerializeParams& Params)`
- L1674 _public function_ `static void ReceivedItem(void* FastArrayItem, const FFastArrayDeltaSerializeParams& Params, const uint32 ReplicationID)`

#### Free symbols / members of external scopes

- L33 _macro_ `#define UE_FAST_ARRAY_COMPILE_LOG_LEVEL All`
- L38 _macro_ `#define UE_FAST_ARRAY_RUNTIME_LOG_LEVEL Warning`
- L41 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetFastTArray, UE_FAST_ARRAY_RUNTIME_LOG_LEVEL, UE_FAST_ARRAY_COMPILE_LOG_LEVEL);`
- L43 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("NetSerializeFast Array"), STAT_NetSerializeFastArray, STATGROUP_Se`
- L44 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("NetSerializeFast Array BuildMap"), STAT_NetSerializeFastArray_BuildMap, STA`
- L45 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("NetSerializeFast Array Delta Struct"), STAT_NetSerializeFastArray_DeltaStruct,`
- L404 _prototype_ `ENUM_CLASS_FLAGS(EFastArraySerializerDeltaFlags);`
- L1876 _macro_ `#define UE_NET_DECLARE_FASTARRAY(FastArrayType, FastArrayItemArrayMemberName, Api) \`
- L1880 _macro_ `#define UE_NET_DECLARE_FASTARRAY(FastArrayType, FastArrayItemArrayMemberName, Api) static constexpr auto GetFastArrayItemTypePtr() { return static_cast<decltype(FastArrayType::FastArrayItemArrayMemberName)::ElementType*>(nullptr); };;`

### `Source/Runtime/Net/Core/Classes/Net/Serialization/FastArraySerializerImplementation.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_NET_IMPLEMENT_FASTARRAY(FastArrayType) \`
- L20 _macro_ `#define UE_NET_IMPLEMENT_FASTARRAY_STUB(FastArrayType) \`
- L27 _macro_ `#define UE_NET_IMPLEMENT_FASTARRAY(...)`
- L28 _macro_ `#define UE_NET_IMPLEMENT_FASTARRAY_STUB(...)`

### `Source/Runtime/Net/Core/Private/Net/Core/Connection/RPCDoSDetectionConfig.h` (Private)


#### struct `FRPCAnalyticsThreshold`  
`struct FRPCAnalyticsThreshold`  
_L16-31_
- reflection: `USTRUCT()`
- desc: Specifies time or count thresholds for when an RPC should be included in analytics
- L22 _public member_ `FName RPC;` — `UPROPERTY()` — The RPC name
- L26 _public member_ `int32 CountPerSec = -1;` — `UPROPERTY()` — The number of calls to an RPC's per second, before including in analytics
- L30 _public member_ `double TimePerSec = 0.0;` — `UPROPERTY()` — Time spent executing an RPC per second, before including in analytics (can specify more than 1 second, for long running RPC's)

#### class `URPCDoSDetectionConfig`  
`class URPCDoSDetectionConfig : public UObject`  
_L38-94_
- reflection: `UCLASS(config=Engine, PerObjectConfig)`
- inherits: `UObject`
- desc: Configuration for FRPCDoSDetection - using PerObjectConfig, to hack a single hardcoded section name
- L43 _private prototype_ `void OverridePerObjectConfigSection(FString& SectionName) override;`
- L51 _public prototype_ `static URPCDoSDetectionConfig* Get(FName NetDriverName);` — Singleton for getting a per-NetDriver instance of this config section/object @param NetDriverName		The NetDriver name used for getting the correct config section
- L56 _public prototype_ `static const TCHAR* GetConfigSectionName();` — Returns the section name used by this class in the config file
- L61 _public member_ `bool bRPCDoSDetection;` — `UPROPERTY(config)` — Whether or not RPC DoS detection is presently enabled
- L65 _public member_ `bool bRPCDoSAnalytics;` — `UPROPERTY(config)` — Whether or not analytics for RPC DoS detection is enabled
- L69 _public member_ `int32 HitchTimeQuotaMS;` — `UPROPERTY(config)` — The amount of time since the previous frame, for detecting hitches, to prevent false positives from built-up packets
- L73 _public member_ `int32 HitchSuspendDetectionTimeMS;` — `UPROPERTY(config)` — The amount of time to suspend RPC DoS Detection, once a hitch is encountered, prevent false positives from built-up packets
- L77 _public member_ `TArray<FString> DetectionSeverity;` — `UPROPERTY(config)` — Names of the different RPC DoS detection states, for escalating severity, depending on the amount of RPC spam
- L81 _public member_ `int32 InitialConnectToleranceMS;` — `UPROPERTY(config)` — The amount of time since the client connected, before time-based checks should become active (to reduce false positives)
- L85 _public member_ `TArray<FName> RPCBlockAllowlist;` — `UPROPERTY(config)` — List of RPC's which should never be blocked
- L89 _public member_ `TArray<FRPCAnalyticsThreshold> RPCAnalyticsThresholds;` — `UPROPERTY(config)` — Custom thresholds for when specific RPC's should be included in analytics
- L93 _public member_ `double RPCAnalyticsOverrideChance;` — `UPROPERTY(config)` — Specifies a random chance, between 0.0 and 1.0, for when RPCAnalyticsThresholds should be overridden (adds to separate analytics)

### `Source/Runtime/Net/Core/Private/Net/Core/Misc/NetCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetCore, Log, All);`

### `Source/Runtime/Net/Core/Private/Net/Core/PushModel/Types/PushModelPerNetDriverState.h` (Private)


#### class `UEPushModelPrivate::FPushModelPerNetDriverState`  
`class FPushModelPerNetDriverState`  
_L15-93_
- L19 _public function_ `FPushModelPerNetDriverState(const uint16 InNumberOfProperties) : PropertyDirtyStates(true, InNumberOfProperties) , bRecentlyCollectedGarbage(false) , bHasDirtyProperties(true)`
- L26 _public function_ `FPushModelPerNetDriverState(FPushModelPerNetDriverState&& Other) : PropertyDirtyStates(MoveTemp(Other.PropertyDirtyStates)) , bRecentlyCollectedGarbage(Other.bRecentlyCollectedGarbage)`
- L32 _public prototype_ `FPushModelPerNetDriverState(const FPushModelPerNetDriverState& Other) = delete;`
- L33 _public prototype_ `FPushModelPerNetDriverState& operator=(const FPushModelPerNetDriverState& Other) = delete;`
- L35 _public function_ `void SetRecentlyCollectedGarbage()`
- L40 _public function_ `void ResetDirtyStates()`
- L47 _public function_ `void CountBytes(FArchive& Ar) const`
- L52 _public function_ `bool IsPropertyDirty(const uint16 RepIndex) const`
- L57 _public function_ `TConstSetBitIterator<> GetDirtyProperties() const`
- L62 _public function_ `bool DidRecentlyCollectGarbage() const`
- L67 _public function_ `void MarkPropertiesDirty(const TBitArray<>& OtherBitArray)`
- L73 _public function_ `void MarkPropertyDirty(const uint16 RepIndex)`
- L79 _public function_ `bool HasDirtyProperties() const`
- L90 _private member_ `TBitArray<> PropertyDirtyStates;` — Current state of our push model properties. Note, bits will be allocated for all replicated properties, not just push model properties.
- L91 _private member_ `uint8 bRecentlyCollectedGarbage : 1;`
- L92 _private member_ `uint8 bHasDirtyProperties : 1;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UEPushModelPrivate`

### `Source/Runtime/Net/Core/Private/Net/Core/PushModel/Types/PushModelPerObjectState.h` (Private)


#### class `UEPushModelPrivate::FPushModelPerObjectState`  
`class FPushModelPerObjectState`  
_L22-155_
- desc: This is a "state" for a given Object that is being tracked by a Push Model Object Manager. This state is shared across all NetDrivers, and so has a 1:1 mapping with actual UObjects.
- L32 _public function_ `FPushModelPerObjectState(const FObjectKey InObjectKey, const uint16 InNumberOfProperties) : ObjectKey(InObjectKey) , DirtiedThisFrame(true, InNumberOfProperties) , bHasDirtyProperties(true)` — Creates a new FPushModelPerObjectState. @param InObjectKey			An ObjectKey that can uniqely identify the object we're representing. @param InNumberOfProperties	The total number of replicated properties this object has.
- L39 _public function_ `FPushModelPerObjectState(FPushModelPerObjectState&& Other) : ObjectKey(Other.ObjectKey) , DirtiedThisFrame(MoveTemp(Other.DirtiedThisFrame)) , PerNetDriverStates(MoveTemp(Other.PerNetDriverStates)) , bHasDirtyProperties(Other.bHasDirtyProperties)`
- L48 _public prototype_ `FPushModelPerObjectState(const FPushModelPerObjectState& Other) = delete;`
- L49 _public prototype_ `FPushModelPerObjectState& operator=(const FPushModelPerObjectState& Other) = delete;`
- L56 _public function_ `void SetRecentlyCollectedGarbage()` — Currently, there are no notifications when a property gets nulled out from Garbage Collection. This should'nt happen frequently in networked scenarios as it can cause other bugs with things like Dormancy. However, it is easily reproducible on Clients recording Replays.
- L64 _public function_ `void MarkPropertyDirty(const uint16 RepIndex)`
- L74 _public function_ `void PushDirtyStateToNetDrivers()` — Pushes the current dirty state of the Push Model Object to each of the Net Driver States. and then reset the dirty state.
- L88 _public function_ `FPushModelPerNetDriverState& GetPerNetDriverState(FNetPushPerNetDriverId DriverId)`
- L93 _public function_ `const FPushModelPerNetDriverState& GetPerNetDriverState(FNetPushPerNetDriverId DriverId) const`
- L98 _public function_ `FNetPushPerNetDriverId AddPerNetDriverState()`
- L106 _public function_ `void RemovePerNetDriverState(const FNetPushPerNetDriverId DriverId)`
- L111 _public function_ `const bool HasAnyNetDriverStates()`
- L116 _public function_ `void CountBytes(FArchive& Ar) const`
- L126 _public function_ `const int32 GetNumberOfProperties() const`
- L131 _public function_ `const FObjectKey& GetObjectKey() const`
- L136 _public function_ `bool HasDirtyProperties() const`
- L144 _private member_ `const FObjectKey ObjectKey;` — A unique ID for the object.
- L149 _private member_ `TBitArray<> DirtiedThisFrame;` — Bitfield tracking which properties we've dirtied since the last time our state was pushed to NetDrivers. Note, bits will be allocated for all replicated properties, not just push model properties.
- L152 _private member_ `TSparseArray<FPushModelPerNetDriverState> PerNetDriverStates;` — Set of NetDriver states that have been requested and are currently tracking the object.
- L154 _private member_ `uint8 bHasDirtyProperties : 1;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UEPushModelPrivate`

### `Source/Runtime/Net/Core/Private/Net/Core/PushModel/Types/PushModelUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UEPushModelPrivate`
- L14 _function_ `static const int32 GetNumWordsInBitArray(const TBitArray<>& BitArray)` (scope `UEPushModelPrivate`)
- L19 _function_ `static void ResetBitArray(TBitArray<>& ToReset)` (scope `UEPushModelPrivate`)
- L24 _function_ `static void SetBitArray(TBitArray<>& ToSet)` (scope `UEPushModelPrivate`)
- L29 _function_ `static void BitwiseOrBitArrays(const TBitArray<>& MaskBitArray, TBitArray<>& ResultBitArray)` (scope `UEPushModelPrivate`)
- L43 _function_ `static bool AreAnyBitsSet(const TBitArray<>& BitArray)` (scope `UEPushModelPrivate`)

### `Source/Runtime/Net/Core/Private/Net/Core/Trace/Reporters/NetTraceReporter.h` (Private)


#### struct `FNetTraceReporter`  
`struct FNetTraceReporter`  
_L9-33_
- L11 _public member_ `static uint32 NetTraceReporterVersion;`
- L13 _public prototype_ `static void ReportInitEvent(uint32 NetTraceVersion);`
- L14 _public prototype_ `static void ReportPacketContent(FNetTracePacketContentEvent* Events, uint32 EventCount, const FNetTracePacketInfo& PacketInfo);`
- L15 _public prototype_ `static void ReportPacketDropped(const FNetTracePacketInfo& PacketInfo);`
- L16 _public prototype_ `static void ReportPacket(const FNetTracePacketInfo& PacketInfo, uint32 PacketBits);`
- L17 _public prototype_ `static void ReportAnsiName(UE::Net::FNetDebugNameId NameId, uint32 NameSize, const char* Name);`
- L18 _public prototype_ `static void ReportObjectCreated(uint32 GameInstanceId, uint64 NetObjectId, UE::Net::FNetDebugNameId NameId, uint64 TypeIdentifier, uint32 OwnerId);`
- L19 _public prototype_ `static void ReportObjectExists(uint32 GameInstanceId, uint64 NetObjectId, UE::Net::FNetDebugNameId NameId, uint64 TypeIdentifier, uint32 OwnerId);`
- L20 _public prototype_ `static void ReportObjectDestroyed(uint32 GameInstanceId, uint64 NetObjectId);`
- L21 _public prototype_ `static void ReportConnectionCreated(uint32 GameInstanceId, uint32 ConnectionId);`
- L22 _public prototype_ `static void ReportConnectionStateUpdated(uint32 GameInstanceId, uint32 ConnectionId, uint8 ConnectionStateValue);`
- L23 _public prototype_ `static void ReportConnectionUpdated(uint32 GameInstanceId, uint32 ConnectionId, const TCHAR* AddressString, const TCHAR* OwningActor);`
- L24 _public prototype_ `static void ReportConnectionClosed(uint32 GameInstanceId, uint32 ConnectionId);`
- L25 _public prototype_ `static void ReportPacketStatsCounter(uint32 GameInstanceId, uint32 ConnectionId, UE::Net::FNetDebugNameId CounterNameId, uint32 StatValue);`
- L26 _public prototype_ `static void ReportFrameStatsCounter(uint32 GameInstanceId, UE::Net::FNetDebugNameId CounterNameId, uint32 StatValue);`
- L27 _public prototype_ `static void ReportInstanceUpdated(uint32 GameInstanceId, bool bIsServer, const TCHAR* Name);`
- L28 _public prototype_ `static void ReportInstanceDestroyed(uint32 GameInstanceId);`
- L29 _public prototype_ `static void ReportObjectPolled(uint32 GameInstanceId, uint64 NetObjectId, uint64 Cycles, bool bIsWaste);`
- L30 _public prototype_ `static void ReportObjectQuantized(uint32 GameInstanceId, uint64 NetObjectId, uint64 Cycles);`
- L31 _public prototype_ `static void ReportObjectWritten(uint32 GameInstanceId, uint64 NetObjectId, uint64 Cycles);`
- L32 _public prototype_ `static void ReportSubObject(uint32 GameInstanceId, uint64 ParentObjectId, uint64 SubObjectId);`

### `Source/Runtime/Net/Core/Public/Net/Core/Analytics/NetAnalytics.h` (Public)


#### struct `FLocalNetAnalyticsStruct`  
`struct FLocalNetAnalyticsStruct : public FVirtualDestructor`  
_L105-107_
- inherits: `FVirtualDestructor`
- desc: For use with TThreadedNetAnalyticsData - this struct is subclassed, and used to define/hold the analytics variables, that will be tracked/aggregated. This base type is required, due to how TThreadedNetAnalyticsData handles tracking of local analytics variables.

#### struct `FNetAnalyticsData`  
`struct FNetAnalyticsData : public FVirtualDestructor, public TSharedFromThis<FNetAnalyticsData, NetAnalyticsThreadSafety>`  
_L113-148_
- inherits: `FVirtualDestructor,TSharedFromThis<FNetAnalyticsData,NetAnalyticsThreadSafety>`
- desc: Subclassed struct which holds net analytics data which is aggregated or to-be-aggregated, and dispatched upon SendAnalytics
- L120 _protected member_ `FNetAnalyticsAggregator* Aggregator;` — The parent aggregator responsible for this data instance
- L127 _public prototype_ `FNetAnalyticsData();` — Default constructor
- L128 _public prototype_ `virtual ~FNetAnalyticsData();`
- L133 _public prototype_ `virtual void SendAnalytics() = 0;` — Dispatches the aggregated analytics data - no further data should be added
- L140 _protected prototype_ `virtual void InternalSendAnalytics();` — Called by the Net Analytics Aggregator, when ready to send analytics - some implementations don't send immediately
- L145 _protected function_ `virtual void NotifyFinalRelease()` — Called just before the last shared reference to this data is released - used to trigger analytics send in threadsafe version

#### struct `TBasicNetAnalyticsData`  
`template<class TDataStruct> struct TBasicNetAnalyticsData : public FNetAnalyticsData, protected TDataStruct`  
_L158-173_
- inherits: `FNetAnalyticsData,TDataStruct`
- desc: Basic single-threaded-only (i.e. good for NetConnection level code) analytics data holder, which just wraps around a simple struct, which defines the analytics variables and implements their aggregation. The passed in struct will have to implement a CommitAnalytics function, which implements aggregation of the struct data, and the class which references this net analytics data will have to trigger this classes CommitAnalytics on the locally stored struct, when finished collecting local analytics data.
- L169 _public function_ `void CommitAnalytics(TDataStruct& AnalyticsVars)` — Called by the class/code which is locally collecting analytics data, to commit the local data for aggregation when done. @param AnalyticsVars		The local analytics variables to be committed/aggregated

#### struct `FThreadedNetAnalyticsData`  
`struct FThreadedNetAnalyticsData : public FNetAnalyticsData`  
_L182-199_
- inherits: `FNetAnalyticsData`
- desc: Special subclass of FNetAnalyticsData that is designed for thread-safety and infrequent access (e.g. at NetConnection Close only). This is to future-proof for netcode multithreading, where PacketHandler level code is expected to run outside of the Game Thread. The last thread to release this analytics data, triggers SendAnalytics - thread safety is partially provided by shared pointer atomics.
- L187 _public prototype_ `FThreadedNetAnalyticsData();` — Default constructor
- L191 _protected prototype_ `virtual void InternalSendAnalytics() override;`
- L193 _protected prototype_ `virtual void NotifyFinalRelease() override;`
- L198 _protected member_ `TAtomic<bool> bReadyToSend;` — Whether or not a thread has signaled that analytics are ready to be sent

#### struct `TThreadedNetAnalyticsData`  
`template<class TDataStruct> struct TThreadedNetAnalyticsData : public FThreadedNetAnalyticsData, protected TDataStruct`  
_L213-307_
- inherits: `FThreadedNetAnalyticsData,TDataStruct`
- desc: Special subclass of FThreadedNetAnalyticsData, which implements multithreaded synchronization, using Thread Local Storage (TLS), providing a complete solution for aggregating net analytics data, by caching a local copy of TDataStruct in TLS (one per thread), and automatically aggregating all instances upon NetDriver Shutdown. The passed in struct will have to implement a CommitAnalytics function, which implements aggregation of the struct data. Every time you need to update analytics, use GetLocalData to access the variables - don't permanently store the return value. There is a performance cost both to looking up thread_local's, and to mapping TDataStruct for TThreadedNetAnalyticsData. This code must only be enabled in a multithreaded environment, due to the unnecessary performance cost in single-threaded code.
- L224 _public function_ `TThreadedNetAnalyticsData() : ThreadLocalData()` — Default constructor
- L234 _public function_ `TDataStruct* GetLocalData()` — Returns the current threads TDataStruct instance, for this net analytics data - creating/registering it, if necessary. @return	The current threads TDataStruct instance
- L253 _protected function_ `TDataStruct* AddLocalData(TMap<FThreadedNetAnalyticsData*, FLocalNetAnalyticsStruct*>& LocalNetAnalyticsMap)` — Handles creation/registration of a new TDataStruct instance - as well as occasional cleanup of stale TLS data. @param LocalNetAnalyticsMap	Reference to the TLS map linking local net analytics vars, to a (potentially stale) net analytics data pointer @return						The newly created TDataStruct instance
- L289 _protected function_ `virtual void NotifyFinalRelease() override`
- L306 _protected member_ `TQueue<TDataStruct*, EQueueMode::Mpsc> ThreadLocalData;` — Every thread creates an instance of TDataStruct locally, and queues the pointer here for later processing/deletion

#### struct `FNetAnalyticsDataDeleter`  
`struct FNetAnalyticsDataDeleter`  
_L313-324_
- desc: Custom deleter for FNetAnalyticsData shared pointers
- L315 _public function_ `inline void operator()(FNetAnalyticsData* Data)`

#### class `FNetAnalyticsAggregator`  
`class FNetAnalyticsAggregator`  
_L330-414_
- desc: Central object (usually within NetDriver) which handles registration/retrieval/type-checking of net analytics data holders.
- L336 _public prototype_ `FNetAnalyticsAggregator(TSharedPtr<IAnalyticsProvider> InProvider, FName InNetDriverName);` — Base constructor
- L338 _public prototype_ `FNetAnalyticsAggregator() = delete;`
- L343 _public prototype_ `void Init();` — Initialize the net analytics aggregator
- L348 _public prototype_ `void InitConfig();` — Initialize the net analytics aggregator config - must support hotfixing
- L353 _public prototype_ `void AppendGameInstanceAttributes(TArray<FAnalyticsEventAttribute>& OutAttributes);` — Adds game and engine specific attributes to the passed in array.
- L359 _public prototype_ `void SendAnalytics();` — Tells the analytics data holders to finish aggregating their analytics data, and to dispatch it. Only called once, at NetDriver shutdown.
- L373 _public prototype_ `TNetAnalyticsDataPtr<> RegisterAnalyticsData_Internal(TNetAnalyticsDataRef<> InData, const FName& InDataName, FString InTypeName);` — Use REGISTER_NET_ANALYTICS instead. Internal function, which registers a net analytics data holder, with an associated key name, and does type checking to ensure there have been no mixups with the data holder type. NOTE: May return nullptr! Analytics can be selectively enabled/disabled, based on the specified analytics data name. @param InData		The analytics data shared reference to be registered @param InDataName	The name given for referencing the analytics data @param InTypeName	Compile-time derived type name for the analytics data - for type checking @return				Returns the newly added analytics data shared reference
- L377 _public function_ `const TSharedPtr<IAnalyticsProvider>& GetAnalyticsProvider()` — Accessor for AnalyticsProvider
- L383 _public function_ `FName GetNetDriverName() const` — Accessor for NetDriverName
- L390 _public typedef_ `using FAnalyticsAppender = TFunction<void(TArray<FAnalyticsEventAttribute>&)>;`
- L391 _public prototype_ `void SetAnalyticsAppender(FAnalyticsAppender AppenderFunction);`
- L395 _private member_ `TSharedPtr<IAnalyticsProvider> AnalyticsProvider;` — The analytics provider we are aggregating data for
- L398 _private member_ `FName NetDriverName;` — The name of the NetDriver which owns this analytics aggregator - for retrieving NetDriver-specific config values
- L401 _private member_ `TMap<FName, TNetAnalyticsDataRef<>> AnalyticsDataMap;` — Maps net analytics data holders, to their specified name
- L404 _private member_ `TMap<FName, FString> AnalyticsDataTypeMap;` — Maps analytics data holder names, to their type name - to verify types and prevent miscasting
- L407 _private member_ `TMap<FName, bool> AnalyticsDataConfigMap;` — Maps analytics data holder names, to a config value specifying whether that data holder is enabled or not
- L410 _private member_ `FAnalyticsAppender AnalyticsAppender;` — Optional functor that can be used to append game specific attributes to your analytics
- L413 _private member_ `bool bSentAnalytics;` — Whether or not analytics was already sent

#### Free symbols / members of external scopes

- L57 _macro_ `#define NET_ANALYTICS_MULTITHREADING 0`
- L61 _variable_ `inline constexpr const ESPMode NetAnalyticsThreadSafety = ESPMode::ThreadSafe;`
- L69 _typedef_ `template<class T=FNetAnalyticsData> using TNetAnalyticsDataRef = TSharedRef<T, NetAnalyticsThreadSafety>;` — Typedefs
- L70 _typedef_ `template<class T=FNetAnalyticsData> using TNetAnalyticsDataRef = TSharedRef<T, NetAnalyticsThreadSafety>;` — Typedefs
- L71 _typedef_ `template<class T=FNetAnalyticsData> using TNetAnalyticsDataRef = TSharedRef<T, NetAnalyticsThreadSafety>;` — Typedefs
- L87 _macro_ `#define REGISTER_NET_ANALYTICS(Aggregator, AnalyticsDataType, InDataName) \` — Registers a named FNetAnalyticsData instance with the net analytics aggregator. Implemented this way, to support runtime name/type checks, without relying on statics. NOTE: May return nullptr! The analytics aggregator can selectively enable/disable analytics, based on the analytics data name @param Aggregator			The net analytics aggregator to register with @param AnalyticsDataType		The net analytics data type to create and register @param InDataName			The name associated with this analytics data - for looking it up @return						Returns a shared pointer to the newly created net analytics data instance
- L96 _externvar_ `extern TAtomic<uint8> GNetAnalyticsCounter;` — Counter used to detect when a new FNetAnalyticsAggregator (i.e. new NetDriver) has been created - to trigger cleanup of TLS data
- L237 _typedef_ `typedef TMap<FThreadedNetAnalyticsData*, FLocalNetAnalyticsStruct*> FLocalNetAnalyticsStructMap;` (scope `TThreadedNetAnalyticsData::GetLocalData`) — Maps this threads net analytics variables, to the net analytics data handler which owns them - for fast lookup
- L258 _typedef_ `typedef TMap<TNetAnalyticsDataWeakPtr<FThreadedNetAnalyticsData>, FThreadedNetAnalyticsData*> FThreadedNetAnalyticsDataMap;` (scope `TThreadedNetAnalyticsData::AddLocalData`) — Maps a weak net analytics data pointer, to its own raw pointer - to cleanup stale entries in LocalNetAnalyticsMap

### `Source/Runtime/Net/Core/Public/Net/Core/Analytics/NetStatsUtils.h` (Public)


#### class `UE::Net::TSampleProducer`  
`template<typename ConsumerType> class TSampleProducer`  
_L29-97_
- desc: Inherited class for a sample producer, which outputs samples to a consumer of the specified class. The consumer must implement: void AddSample(double Val) If the consumer wants to peek at each individual measurement that makes up the sample (for e.g. determining Min/Max measurements), then the consumer must implement: void PeekMeasurement(double TimeVal, double Val) @param ConsumerType	The type which will be used for consuming samples.
- L55 _public function_ `void SetConsumer(ConsumerType* InConsumer)` — Sets the consumer object to output samples to. @param InConsumer	The consumer object
- L66 _protected function_ `void OutputSample(double Value)` — Called by subclasses to output a sample to the consumer. @param Value		The sample value being output
- L81 _protected function_ `template<typename InnerConsumerType=ConsumerType, typename = typename TEnableIf<TModels_V<CPeekMeasurements, InnerConsumerType>>::Type> inline void PeekMeasurement(double TimeVal, double Value)`
- L90 _protected function_ `template<typename InnerConsumerType=ConsumerType, typename = typename TEnableIf<!TModels_V<CPeekMeasurements, InnerConsumerType>>::Type, int32 UnusedParamForODR=0> inline void PeekMeasurement(double TimeVal, double Value)`
- L96 _private member_ `ConsumerType* Consumer;` — The consumer object that receives samples

#### struct `UE::Net::TSampleProducer::CSampleConsumer`  
`struct CSampleConsumer`  
_L31-37_
- L34 _public prototype_ `template<typename T> auto Requires(T& A) -> decltype( A.AddSample(0.0) );`

#### struct `UE::Net::TSampleProducer::CPeekMeasurements`  
`struct CPeekMeasurements`  
_L39-45_
- L42 _public prototype_ `template<typename T> auto Requires(T& A) -> decltype( A.PeekMeasurement(0.0, 0.0) );`

#### enum `UE::Net::EBinnedValueMode`  
`enum class EBinnedValueMode : uint8`  
_L102-109_
- desc: The type of moving value to calculate/track
- L105 _public enumerator_ `MovingAvg` — Tracks a moving average
- L108 _public enumerator_ `MovingSum` — Tracks a moving sum

#### class `UE::Net::FBinnedMovingValueBase`  
`class FBinnedMovingValueBase`  
_L115-181_
- desc: Base class for moving values, implementing non-templatized data-structure/methods. See TBinnedMovingValue.
- L128 _protected prototype_ `FBinnedMovingValueBase() = delete;`
- L129 _protected prototype_ `explicit FBinnedMovingValueBase(const TArrayView<FBin> InBins, double InTimePerBin, EBinnedValueMode InMode);`
- L138 _protected prototype_ `void AddMeasurement_Implementation(double TimeVal, double Value, TOptional<double>& OutSample);` — Internal implementation for AddMeasurement, which outputs a sample if the bins have filled and rolled back over to FirstBinIndex. @param TimeVal		The time value associated with the measurement, for time-based binning @param Value			The measurement value @param OutSample		Outputs a sample, if all bins have filled and rolled back over to FirstBinIndex
- L146 _public prototype_ `double GetSample() const;` — Gets a sample of the calculated moving value, based on current bin data. @return	Outputs the calculated sample value
- L151 _public prototype_ `void Reset();` — Resets the accumulated bin/sample data.
- L154 _private prototype_ `void ResetNewAndSkippedBins(int32 BinIdx, TOptional<double>& OutSample);`
- L159 _private member_ `const TArrayView<FBin> BinsView;` — A view of the allocated bins, for collecting moving values
- L162 _private member_ `const double TimePerBin = 0.0;` — The amount of time tracked by each individual bin
- L165 _private member_ `const double BinRange = 0.0;` — The total range of all bins
- L168 _private member_ `const EBinnedValueMode SampleMode = EBinnedValueMode::MovingAvg;` — The mode for sample calculations - typically moving average, or moving sum
- L171 _private member_ `int32 FirstBinIndex = INDEX_NONE;` — The index of the first bin that a value was stored in, to detect when all bins are rolled over
- L174 _private member_ `int32 LastWrittenBinIndex = INDEX_NONE;` — The index of the last bin to be written to
- L177 _private member_ `double TotalSum = 0.0;` — The total summed value of all bins
- L180 _private member_ `int32 TotalCount = 0;` — The total count of all bins

#### struct `UE::Net::FBinnedMovingValueBase::FBin`  
`struct FBin`  
_L118-125_
- L121 _public member_ `double Sum = 0.0;` — Sum of all values in this bin
- L124 _public member_ `int32 Count = 0;` — Number of values in this bin

#### class `UE::Net::TBinnedMovingValue`  
`template<typename ConsumerType, int32 NumBins, EBinnedValueMode InMode> class TBinnedMovingValue : public FBinnedMovingValueBase, public TSampleProducer<ConsumerType>`  
_L199-247_
- inherits: `FBinnedMovingValueBase,TSampleProducer<ConsumerType>`
- desc: Tracks/stores a moving average or moving sum over a period of time, binning the accumulated values into different time periods, for smoothing and balancing the memory/accuracy cost of dropping old values as they fall out of the measured time period. Use TBinnedMovingAvg/TBinnedMovingSum aliases, instead of using this directly. Measurements are input using AddMeasurement, and samples/values are output to the specified consumer, which is set using SetConsumer. Samples are automatically output when all of the data bins fill and are rolled over - this guarantees perfect accuracy over the full time period. Samples can be manually output using Flush, but this can be less accurate depending on the use case - see Flush for more information. @param ConsumerType	The type which will be used for consuming samples. @param NumBins		The number of bins to use. @param InMode		Internal
- L207 _public function_ `explicit TBinnedMovingValue(double TimePerBin) : FBinnedMovingValueBase(MakeArrayView(Bins, NumBins), TimePerBin, InMode)` — Main constructor @param TimePerBin	The amount of time that each bin represents.
- L218 _public function_ `void AddMeasurement(double TimeVal, double Value)` — Inputs a measurement value and the approximate time it was measured. @param TimeVal		The time of the measurement. @param Value			The measurement value
- L239 _public function_ `void Flush()` — Flushes a sample from the current bin values to the consumer. Since this is a moving value, none of the bins are reset when a sample is output (so the flushed sample can partially reflect old values), and the current bin will have been reset recently so it can be filled (so the flushed value may not reflect the full time period). The user must consider whether this is accurate/suitable for their use case.
- L246 _private member_ `FBin Bins[NumBins] = {};` — Allocation for the bins which collect moving values

#### class `UE::Net::TBinnedDeltaMovingValue`  
`template<typename ConsumerType, int32 NumBins, EBinnedValueMode InMode> class TBinnedDeltaMovingValue : private TBinnedMovingValue<ConsumerType, NumBins, InMode>`  
_L260-300_
- inherits: `TBinnedMovingValue<ConsumerType,NumBins,InMode>`
- desc: Version of TBinnedMovingValue which takes permanently incrementing values (e.g. frame count), and uses the delta since the previous value as the measurement (this means the very first value is not measured). Use TDeltaBinnedMovingAvg/TDeltaBinnedMovingSum aliases, instead of using this directly. @param ConsumerType	The type which will be used for consuming samples. @param NumBins		The number of bins to use. @param InMode		Internal
- L262 _private typedef_ `using Super = TBinnedMovingValue<ConsumerType, NumBins, InMode>;`
- L277 _public function_ `void AddMeasurement(double TimeVal, double Value)` — Inputs a value whose delta is calculated for measurement, and the approximate time it was measured. @param TimeVal		The time of the measurement. @param Value			The value to calculate the delta of, for measurement
- L290 _public function_ `void Reset()` — Resets the accumulated bin/sample data (the very first value after this is not measured).
- L299 _private member_ `double LastValue = std::numeric_limits<double>::min();` — The last input value, for tracking deltas

#### enum `UE::Net::EMinMaxValueMode`  
`enum EMinMaxValueMode`  
_L352-362_
- desc: Determines how Min/Max values are calculated, for FSampleMinMaxAvg
- L355 _public enumerator_ `PerSample` — Min/Max values are calculated based on the final (possibly averaged/summed) sample
- L358 _public enumerator_ `PerMeasurement` — Min/Max values are calculated based on every individual measurement accumulated in the sample (TSampleProducer only!)
- L361 _public enumerator_ `PerTimeSeconds` — Min/Max values are calculated based on the average of measurements accumulated over the specified time period (TSampleProducer only!)

#### class `UE::Net::FSampleMinMaxAvg`  
`class FSampleMinMaxAvg`  
_L370-458_
- desc: Base class for tracking the minimum, maximum and average of the passed in measurement values. This base class can handle reading. The TSampleMinMaxAvg subclass is compatible as a consumer for TSampleProducer, and is used for writing.
- L375 _private prototype_ `void AddSample_Internal(double Value);`
- L381 _public prototype_ `void Reset();` — Resets the accumulated sample data
- L388 _public function_ `double GetMin() const` — Gets the minimum sample value encountered @return	The minimum sample value
- L398 _public function_ `double GetMax() const` — Gets the maximum sample value encountered @return	The maximum sample value
- L408 _public function_ `double GetCurrent() const` — Gets the current/latest sample value @return	The current sample value
- L418 _public function_ `double GetAvg() const` — Gets the average sample value @return	The average sample value
- L428 _public function_ `double GetSum() const` — Gets the sum of all sample values tracked @return	The sum of samples
- L438 _public function_ `int32 GetSampleCount() const` — Gets the number of samples tracked @return	The number of samples
- L445 _private member_ `double MinValue = std::numeric_limits<double>::max();` — The minimum sample value encountered
- L448 _private member_ `double MaxValue = std::numeric_limits<double>::min();` — The maximum sample value encountered
- L451 _private member_ `double CurrentValue = 0.0;` — The current sample value
- L454 _private member_ `double TotalSum = 0.0;` — The total sum of all samples
- L457 _private member_ `int32 TotalCount = 0;` — The number of samples tracked

#### class `UE::Net::TSampleMinMaxAvg`  
`template<> class TSampleMinMaxAvg<EMinMaxValueMode::PerSample> : public FSampleMinMaxAvg`  
_L471-491_
- inherits: `FSampleMinMaxAvg`
- L477 _public function_ `void AddSample(double Value)` — Inputs a sample (usually from a TSampleProducer)
- L500 _public function_ `inline void AddSample(double Value)` — Inputs a sample (usually from a TSampleProducer)
- L505 _public function_ `void PeekMeasurement(double TimeVal, double Value)`
- L562 _private member_ `double MinMaxPeriodStart = 0.0;` — The time at which the last Min/Max averaging period started
- L565 _private member_ `double MinMaxPeriodSum = 0.0;` — The sum of measurements during the current Min/Max averaging period
- L568 _private member_ `int32 MinMaxPeriodCount = 0;` — The number of measurements during the current Min/Max averaging period

#### class `UE::Net::TSampleMinMaxAvg`  
`template<> class TSampleMinMaxAvg<EMinMaxValueMode::PerMeasurement> : public FSampleMinMaxAvg`  
_L494-517_
- inherits: `FSampleMinMaxAvg`
- L477 _public function_ `void AddSample(double Value)` — Inputs a sample (usually from a TSampleProducer)
- L500 _public function_ `inline void AddSample(double Value)` — Inputs a sample (usually from a TSampleProducer)
- L505 _public function_ `void PeekMeasurement(double TimeVal, double Value)`
- L562 _private member_ `double MinMaxPeriodStart = 0.0;` — The time at which the last Min/Max averaging period started
- L565 _private member_ `double MinMaxPeriodSum = 0.0;` — The sum of measurements during the current Min/Max averaging period
- L568 _private member_ `int32 MinMaxPeriodCount = 0;` — The number of measurements during the current Min/Max averaging period

#### class `UE::Net::TSampleMinMaxAvg`  
`template<int32 MinMaxTimeSeconds> class TSampleMinMaxAvg<EMinMaxValueMode::PerTimeSeconds, MinMaxTimeSeconds> : public FSampleMinMaxAvg`  
_L520-569_
- inherits: `FSampleMinMaxAvg`
- L477 _public function_ `void AddSample(double Value)` — Inputs a sample (usually from a TSampleProducer)
- L500 _public function_ `inline void AddSample(double Value)` — Inputs a sample (usually from a TSampleProducer)
- L505 _public function_ `void PeekMeasurement(double TimeVal, double Value)`
- L562 _private member_ `double MinMaxPeriodStart = 0.0;` — The time at which the last Min/Max averaging period started
- L565 _private member_ `double MinMaxPeriodSum = 0.0;` — The sum of measurements during the current Min/Max averaging period
- L568 _private member_ `int32 MinMaxPeriodCount = 0;` — The number of measurements during the current Min/Max averaging period

#### class `UE::Net::FUsingNetStatsUtils`  
`class FUsingNetStatsUtils`  
_L574-590_
- desc: Class level 'using namespace UE::Net', for NetStatsUtils.h types. Inherit as protected.
- L577 _public typedef_ `template<typename ConsumerType> using TSampleProducer = TSampleProducer<ConsumerType>;`
- L578 _public typedef_ `template<typename ConsumerType> using TSampleProducer = TSampleProducer<ConsumerType>;`
- L579 _public typedef_ `template<typename ConsumerType, int32 NumBins, EBinnedValueMode InMode> using TBinnedMovingValue = TBinnedMovingValue<ConsumerType, NumBins, InMode>;`
- L581 _public typedef_ `template<typename ConsumerType, int32 NumBins, EBinnedValueMode InMode> using TBinnedDeltaMovingValue = TBinnedDeltaMovingValue<ConsumerType, NumBins, InMode>;`
- L583 _public typedef_ `template<typename ConsumerType, int32 NumBins> using TBinnedMovingAvg = TBinnedMovingAvg<ConsumerType, NumBins>;`
- L584 _public typedef_ `template<typename ConsumerType, int32 NumBins> using TBinnedMovingAvg = TBinnedMovingAvg<ConsumerType, NumBins>;`
- L585 _public typedef_ `template<typename ConsumerType, int32 NumBins> using TBinnedMovingAvg = TBinnedMovingAvg<ConsumerType, NumBins>;`
- L586 _public typedef_ `template<typename ConsumerType, int32 NumBins> using TBinnedMovingAvg = TBinnedMovingAvg<ConsumerType, NumBins>;`
- L587 _public typedef_ `template<typename ConsumerType, int32 NumBins> using TDeltaBinnedMovingAvg = TDeltaBinnedMovingAvg<ConsumerType, NumBins>;`
- L588 _public typedef_ `using FSampleMinMaxAvg = FSampleMinMaxAvg;`
- L589 _public typedef_ `template<EMinMaxValueMode Mode, int32 MinMaxTimeSeconds=1> using TSampleMinMaxAvg = TSampleMinMaxAvg<Mode, MinMaxTimeSeconds>;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Net` (scope `UE`)
- L306 _typedef_ `template<typename ConsumerType, int32 NumBins> using TBinnedMovingAvg = TBinnedMovingValue<ConsumerType, NumBins, EBinnedValueMode::MovingAvg>;` (scope `UE::Net`) — Alias for tracking a moving average. See TBinnedMovingValue.
- L312 _typedef_ `template<typename ConsumerType, int32 NumBins> using TDeltaBinnedMovingAvg = TBinnedDeltaMovingValue<ConsumerType, NumBins, EBinnedValueMode::MovingAvg>;` (scope `UE::Net`) — Alias for tracking a moving average using the delta of the input value. See TBinnedDeltaMovingValue/TBinnedMovingValue.
- L318 _typedef_ `template<typename ConsumerType, int32 NumBins> using TBinnedMovingSum = TBinnedMovingValue<ConsumerType, NumBins, EBinnedValueMode::MovingSum>;` (scope `UE::Net`) — Alias for tracking a moving sum. See TBinnedMovingValue.
- L324 _typedef_ `template<typename ConsumerType, int32 NumBins> using TDeltaBinnedMovingSum = TBinnedDeltaMovingValue<ConsumerType, NumBins, EBinnedValueMode::MovingSum>;` (scope `UE::Net`) — Alias for tracking a moving sum using the delta of the input value. See TBinnedDeltaMovingValue/TBinnedMovingValue.
- L332 _namespace_ `namespace TBinParms`
- L334 _function_ `static constexpr int32 NumBins(int32 InNumBins)` (scope `TBinParms`)
- L339 _function_ `static constexpr double TimePerBin(double InBinSize)` (scope `TBinParms`)
- L346 _namespace_ `namespace UE`
- L346 _namespace_ `namespace Net` (scope `UE`)
- L598 _namespace_ `namespace TSampleParms`
- L600 _function_ `static constexpr int32 TimeSeconds(int32 InTimeSeconds)` (scope `TSampleParms`)

### `Source/Runtime/Net/Core/Public/Net/Core/Analytics/RPCDoSDetectionAnalytics.h` (Public)


#### struct `FMaxRPCDoSEscalation`  
`struct FMaxRPCDoSEscalation`  
_L39-67_
- desc: Per-player tracking of the maximum RPC DoS escalation state
- L42 _public member_ `FString PlayerIP;` — The IP of the player
- L45 _public member_ `FString PlayerUID;` — The UID of the player
- L48 _public member_ `int32 MaxSeverityIndex = 0;` — The index of the maximum severity state that was reached
- L51 _public member_ `FString MaxSeverityCategory;` — The name of the maximum severity state that was reached
- L54 _public member_ `int32 MaxAnalyticsSeverityIndex = 0;` — The index of the maximum severity state that was confirmed for analytics
- L57 _public member_ `FString MaxAnalyticsSeverityCategory;` — The name of the maximum severity state that was confirmed for analytics
- L61 _public function_ `bool operator == (const FMaxRPCDoSEscalation& A) const`

#### struct `FRPCAnalytics`  
`struct FRPCAnalytics`  
_L73-135_
- desc: Per-RPC analytics for any RPC Tracking that is active within the RPC DoS Detection instance.
- L76 _public member_ `FName RPCName;` — The name of the RPC
- L79 _public member_ `int32 MaxCountPerSec = 0;` — The maximum number of calls to the RPC per second
- L83 _public member_ `double MaxTimePerSec = 0.0;` — The maximum amount of time spent executing the RPC per second (may be larger than a second, if an RPC is long-running)
- L86 _public member_ `uint8 MaxTimeGameThreadCPU = 0;` — The Game Thread CPU Usage, at the approximate time that MaxTimePerSec was set (used to detect CPU Saturation, not RPC cost)
- L90 _public member_ `double MaxSinglePacketRPCTime = 0.0;` — The maximum amount of time spent executing a packet which contains only calls to this RPC
- L93 _public member_ `int32 SinglePacketRPCCount = 0;` — The number of calls to this RPC within the packet, at the time that MaxSinglePacketRPCTime was set
- L96 _public member_ `uint8 SinglePacketGameThreadCPU = 0;` — The Game Thread CPU Usage, at the approximate time that MaxSinglePacketRPCTime was set (used to detect CPU Saturation, not RPC cost)
- L100 _public member_ `int32 BlockedCount = 0;` — Counts the total number of times calls to this RPC were blocked
- L106 _public member_ `FString PlayerIP;` — The IP of the player
- L109 _public member_ `FString PlayerUID;` — The UID of the player
- L113 _public function_ `bool operator == (const FRPCAnalytics& A) const`
- L127 _public function_ `bool WithinMinAnalyticsThreshold() const` — Whether or not the current RPC's analytics meet any of the minimum hardcoded thresholds, for inclusion in analytics. @return		Whether or not minimum analytics inclusion thresholds are met

#### struct `FRPCDoSAnalyticsVars`  
`struct FRPCDoSAnalyticsVars`  
_L140-183_
- desc: Container class for separating analytics variables and processing, from the main RPC DoS Detection code
- L145 _public prototype_ `FRPCDoSAnalyticsVars();` — Default constructor
- L147 _public prototype_ `bool operator == (const FRPCDoSAnalyticsVars& A) const;`
- L149 _public prototype_ `void CommitAnalytics(FRPCDoSAnalyticsVars& AggregatedData);`
- L154 _public member_ `FString PlayerIP;` — The IP of the player
- L157 _public member_ `FString PlayerUID;` — The UID of the player
- L160 _public member_ `int32 MaxSeverityIndex = 0;` — The index of the maximum severity state that was reached
- L163 _public member_ `FString MaxSeverityCategory;` — The name of the maximum severity state that was reached
- L166 _public member_ `int32 MaxAnalyticsSeverityIndex = 0;` — The index of the maximum severity state confirmed for analytics that was reached
- L169 _public member_ `FString MaxAnalyticsSeverityCategory;` — The name of the maximum severity state confirmed for analytics that was reached
- L173 _public member_ `TArray<TSharedPtr<FRPCAnalytics>> RPCTrackingAnalytics;` — Analytics for RPC's that are being tracked
- L176 _public member_ `const int32 MaxRPCAnalytics;` — The maximum number of RPC tracking analytics entries
- L182 _public member_ `TArray<FMaxRPCDoSEscalation> MaxPlayerSeverity;` — (Not filled until final commit) The maximum RPC DoS severity state reached, for each player

#### class `FRPCDoSAnalyticsSender`  
`class FRPCDoSAnalyticsSender`  
_L189-198_
- desc: Class which is responsible for sending the actual analytics events (for implementation outside of NetCore, to avoid Analytics dependency)
- L192 _public function_ `virtual void SendAnalytics(FNetAnalyticsAggregator* Aggregator, FRPCDoSAnalyticsData* Data)`
- L194 _public function_ `virtual void FireEvent_ServerRPCDoSEscalation(FNetAnalyticsAggregator* Aggregator, FRPCDoSAnalyticsData* Data, int32 SeverityIndex, const FString& SeverityCategory, int32 WorstCountPerSec, double WorstTimePerSec, const FString& InPlayerIP, const FString& InPlayerUID, const TArray<FName>& InRPCGroup, double InRPCGroupTime=0.0)`

#### struct `FRPCDoSAnalyticsData`  
`struct FRPCDoSAnalyticsData : public TBasicNetAnalyticsData<FRPCDoSAnalyticsVars>`  
_L203-237_
- inherits: `TBasicNetAnalyticsData<FRPCDoSAnalyticsVars>`
- desc: RPC DoS Detection implementation for basic aggregated net analytics data
- L206 _public member_ `TSharedPtr<FRPCDoSAnalyticsSender> AnalyticsSender;` — Implementation responsible for the analytics send event
- L209 _public member_ `int8 WorstAnalyticsState = 0;` — The worst RPC DoS severity state that has been active and passed confirmation thresholds - mirrors RPCDosDetection.WorstAnalyticsState
- L215 _public prototype_ `void SetAnalyticsSender(TSharedPtr<FRPCDoSAnalyticsSender> InSender);`
- L217 _public prototype_ `FRPCDoSAnalyticsVars* GetVars();`
- L219 _public prototype_ `virtual void SendAnalytics() override;`
- L234 _public prototype_ `void FireEvent_ServerRPCDoSEscalation(int32 SeverityIndex, const FString& SeverityCategory, int32 WorstCountPerSec, double WorstTimePerSec, const FString& InPlayerIP, const FString& InPlayerUID, const TArray<FName>& InRPCGroup, double InRPCGroupTime=0.0);` — Triggers RPC DoS Escalation analytics. This code is separate to the RPC DoS Analytics aggregation, but is implemented here to keep the RPC DoS analytics in one place. @param SeverityIndex		The numeric value of the RPC DoS severity category, that the NetDriver escalated to @param SeverityCategory	The name of the RPC DoS severity category, that the NetDriver escalated to @param WorstCountPerSec	The worst per second RPC execution count that may have triggered this escalation @param WorstTimePerSec	The worst per second RPC execution time that may have triggered this escalation (for ranking) @param InPlayerIP		The IP of the player @param InPlayerUID		The UID of the player @apram InRPCGroup		Lists lightweight tracking RPC's contributing to escalation, which couldn't be individually timed @param InRPCGroupTime	The amount of time the whole RPC group spent executing

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FModifyRPCDoSAnalytics, UObject* , TArray<FAnalyticsEventAttribute>& );` — Multicast delegate for modifying/adding-to RPC DoS analytics events. @param World			The World the RPC DoS Analytics and NetConnection is active in. @param InOutAttrs	Specifies the analytics attributes array for performing modifications/additions
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FModifyRPCDoSAnalytics, UObject* , TArray<FAnalyticsEventAttribute>& );` — Multicast delegate for modifying/adding-to RPC DoS analytics events. @param World			The World the RPC DoS Analytics and NetConnection is active in. @param InOutAttrs	Specifies the analytics attributes array for performing modifications/additions
- L28 _externvar_ `extern FModifyRPCDoSAnalytics GModifyRPCDoSAnalytics;` — Globally accessible multicast delegate, for modifying/adding-to the RPC DoS analytics event
- L31 _externvar_ `extern FModifyRPCDoSAnalytics GModifyRPCDoSEscalationAnalytics;` — Globally accessible multicast delegate, for modifying/adding-to the RPC DoS escalation analytics event

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/ConnectionHandle.h` (Public)


#### class `UE::Net::FConnectionHandle`  
`class FConnectionHandle`  
_L16-44_
- desc: The handle is unique per netdriver. The child connection ID is not unique with respect to other handles with a different parent connection ID. Child connection are not assigned proper connection IDs as we will never replicate to them. Only parent connections will be replicated to. When there is need to deal with child connections in replication scenarios the ConnectionHandle can aid with that.
- L20 _public prototype_ `inline FConnectionHandle() = default;` — Initializes an invalid handle.
- L21 _public prototype_ `explicit FConnectionHandle(uint32 InParentConnectionId);`
- L22 _public prototype_ `FConnectionHandle(uint32 InParentConnectionId, uint32 InChildConnectionId);`
- L24 _public prototype_ `bool operator==(const FConnectionHandle& Other) const;`
- L27 _public prototype_ `bool IsValid() const;` — Returns true if this is a valid handle.
- L29 _public prototype_ `bool IsParentConnection() const;` — Returns true if the handle is valid and represents a parent connection.
- L31 _public prototype_ `bool IsChildConnection() const;` — Returns true if the handle is valid and represents a child connection.
- L34 _public prototype_ `uint32 GetParentConnectionId() const;` — Returns the parent connection id for all types of valid handles.
- L36 _public prototype_ `uint32 GetChildConnectionId() const;` — Returns a non-zero ID for a valid child connection handle, zero for parent connections and invalid handles.
- L41 _private member_ `uint32 ParentConnectionId = 0;`
- L43 _private member_ `uint32 ChildConnectionId = 0;` — For a valid handle a ChildConnectionId of zero indicates it's the parent connection itself.
- L46 _function_ `inline FConnectionHandle::FConnectionHandle(uint32 InParentConnectionId) : ParentConnectionId(InParentConnectionId) , ChildConnectionId(0)`
- L52 _function_ `inline FConnectionHandle::FConnectionHandle(uint32 InParentConnectionId, uint32 InChildConnectionId) : ParentConnectionId(InParentConnectionId) , ChildConnectionId(InChildConnectionId)`
- L58 _function_ `inline bool FConnectionHandle::operator==(const FConnectionHandle& Other) const`
- L63 _function_ `inline bool FConnectionHandle::IsValid() const`
- L68 _function_ `inline bool FConnectionHandle::IsParentConnection() const`
- L73 _function_ `inline bool FConnectionHandle::IsChildConnection() const`
- L78 _function_ `inline uint32 FConnectionHandle::GetParentConnectionId() const`
- L83 _function_ `inline uint32 FConnectionHandle::GetChildConnectionId() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Net` (scope `UE`)
- L88 _function_ `inline uint32 GetTypeHash(const FConnectionHandle& Handle)` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/EscalationStates.h` (Public)


#### enum `EQuotaType`  
`enum class EQuotaType : uint8`  
_L123-127_
- desc: The type of state change quota/thresholds to check
- L125 _public enumerator_ `EscalateQuota` — Check quota for escalating to a higher state
- L126 _public enumerator_ `DeescalateQuota` — Check quota for de-escalating to a lower state

#### struct `FHasHitAnyQuotaParms`  
`struct FHasHitAnyQuotaParms`  
_L132-150_
- desc: Parameters for FEscalationState.HasHitAnyQuota
- L134 _public typedef_ `using FEscalationCounter = UE::Net::FEscalationCounter;`
- L137 _public member_ `const TArrayView<TArrayView<int32>>& RegisteredCounters;` — The list of custom registered counters, by category, for any custom processing implementation
- L140 _public member_ `const TArrayView<FEscalationCounter>(&PerPeriodHistory)[16];` — The per-period historical counters being compared against (excludes SecondCounters and FrameCounters)
- L143 _public member_ `const TArrayView<FEscalationCounter>& SecondCounters;` — The current seconds counters for factoring-in to comparisons (excludes FrameCounters)
- L146 _public member_ `const TArrayView<FEscalationCounter>& FrameCounters;` — The current frames counters for factoring-in to comparisons
- L149 _public member_ `EQuotaType QuotaType;` — The type of state change quota/thresholds to check

#### struct `FEscalationState`  
`struct FEscalationState : public FStateStruct`  
_L158-252_
- reflection: `USTRUCT()`
- inherits: `FStateStruct`
- desc: Base struct which defines an escalation state, which is subclassed to implement custom state variables and (de-)escalation quota's. NOTE: Subclasses must also implement the TEscalationStateStatics interface.
- L177 _public member_ `bool bLogEscalate = false;` — `UPROPERTY(config)` — Whether or not to log when escalating to this state
- L181 _public member_ `bool bDormant = false;` — `UPROPERTY(config)` — This escalation state is considered to be dormant/inactive - and the escalation manager may no longer need ticking in this state
- L185 _public member_ `int16 CooloffTime = -1;` — `UPROPERTY(config)` — The amount of time, in seconds, before the current severity state cools off and de-escalates
- L189 _public member_ `int16 AutoEscalateTime = -1;` — `UPROPERTY(config)` — The amount of time, in seconds, spent in the current severity state before it automatically escalates to the next state
- L197 _protected member_ `int8 HighestTimePeriod = 0;` — `UPROPERTY()` — Cached value for the highest time period in this config state
- L201 _protected member_ `TArray<int8> AllTimePeriods;` — `UPROPERTY()` — Cached value for all different time periods in this state
- L208 _public prototype_ `bool IsDormant() const;` — Whether or not this escalation state is a 'dormant' state, which allows the escalation manager to disable ticking
- L215 _public prototype_ `int8 GetHighestTimePeriod() const;` — Gets the highest counter time period specified by escalation state settings (used for limiting 'CountersPerPeriodHistory' size) @return		The highest counter time period in the state config settings
- L222 _public prototype_ `const TArray<int8>& GetAllTimePeriods() const;` — Gets all counter time periods specified by the escalation state settings @return		All of the time periods in the state config settings
- L226 _protected prototype_ `virtual void ValidateConfigInternal() override;`
- L235 _protected prototype_ `void ValidateTimePeriod(int8& Value, const TCHAR* PropertyName, EValidateTime Requirement=EValidateTime::Optional);` — Validate that the specified escalation time period is within thresholds, and clamp it if necessary @param Value			The time period value to validate @param PropertyName	The name of the property, for logging @param Requirement	Whether the time period value must be set, or is optional
- L248 _private function_ `virtual bool HasHitAnyQuota(FHasHitAnyQuotaParms Parms) const` — Whether or not the specified per-period counters have hit escalation quota's specified by this state. NOTE: This quota check should not be used in high performance code - it should be decomposed into non-virtual calls in a subclass, which are then used directly in code which needs them - to avoid virtual calls. @param Parms		Parameters needed for performing quota checks @return			Whether or not any escalation quota has been hit

#### enum `FEscalationState::EValidateTime`  
`enum class EValidateTime : uint8`  
_L167-171_
- L169 _public enumerator_ `Optional`
- L170 _public enumerator_ `MustBeSet`

#### struct `TEscalationStateStatics`  
`template<class T> struct TEscalationStateStatics`  
_L258-275_
- desc: Static interface which FEscalateState subclasses must implement (called during construction, so virtuals won't do)
- L263 _public function_ `static inline const TCHAR* GetConfigSection()` — Gets the base configuration section name escalation states will use (not the full/complete section name)
- L271 _public function_ `static inline UClass* GetBaseConfigClass()` — Gets the UEscalationManagerConfig subclass escalation states are associated with

#### struct `UE::Net::FEscalationCounter`  
`struct FEscalationCounter`  
_L301-343_
- desc: Struct containing escalation counters covering any time period (e.g. frame/second/arbitrary-period)
- L304 _public member_ `int32 Counter = 0;` — Counter for the number of times an event occurred that could lead to an escalation
- L307 _public member_ `double AccumTime = 0.0;` — Accumulated time spent executing code that could lead to an escalation
- L311 _public member_ `double DebugAccumTime = 0.0;` — Debug version of the value above, using more accurate timing, for testing accuracy of approximate time
- L319 _public function_ `void ResetCounters()` — Reset the values of this escalation counter
- L334 _public function_ `void AccumulateCounter(const FEscalationCounter& InCounter)` — Accumulate another escalation counter into this one @param InCounter		The escalation counter to accumulate with

#### enum `UE::Net::ESeverityUpdate`  
`enum class ESeverityUpdate : uint8`  
_L348-353_
- desc: Escalation severity update types
- L350 _public enumerator_ `Escalate` — Escalating to a higher escalation state
- L351 _public enumerator_ `AutoEscalate` — Automatic/non-quota escalation to a higher escalation state, e.g. when too much time was spent in a lower state
- L352 _public enumerator_ `Deescalate` — Deescalating to a lower escalation state

#### enum `UE::Net::EEscalateReason`  
`enum class EEscalateReason : uint8`  
_L358-363_
- desc: The reason for a severity update
- L360 _public enumerator_ `QuotaLimit` — Escalation quota's were hit (followed by additional ReasonContext)
- L361 _public enumerator_ `AutoEscalate` — Automatic escalation from a lower state, e.g. after spending too much time in a lower state
- L362 _public enumerator_ `Deescalate` — Deescalation to a lower state

#### enum `UE::Net::EEscalateResult`  
`enum class EEscalateResult : uint8`  
_L368-373_
- desc: The result of an UpdateSeverity call
- L370 _public enumerator_ `Escalated` — Escalated to a higher/more-severe state
- L371 _public enumerator_ `Deescalated` — De-escalated to a lower/less-severe state
- L372 _public enumerator_ `NoChange` — No state change occurred

#### class `UE::Net::FEscalationManager`  
`class FEscalationManager`  
_L379-602_
- desc: Manages initialization/application of escalation states, and tracking various counters/timers used to calculate state change quotas/thresholds.
- L448 _private prototype_ `FEscalationManager(FEscalationManagerParms Parms);`
- L450 _private prototype_ `void InitParms(FEscalationManagerInitParms Parms);`
- L452 _private prototype_ `FEscalationManager() = delete;`
- L459 _private prototype_ `void InitConfig(FStateConfigParms ConfigParms);` — Loads configuration settings using the specified parameters, and initializes severity states @param ConfigParms	Specifies the parameters for the config section/object
- L469 _private prototype_ `EEscalateResult UpdateSeverity(ESeverityUpdate Update, EEscalateReason Reason, FString ReasonContext=TEXT(""));` — Updates the current escalation manager severity state @param Update			Whether or not we are escalating or de-escalating the severity state @param Reason			The reason for the escalation change @param ReasonContext		Additional customizable context for the escalation change @return					The result of the severity update. Escalation/Deescalation, or NoChange
- L478 _private prototype_ `void RecalculatePeriodHistory(const TArray<int8>& InTimePeriods, TArrayView<FEscalationCounter>(&OutPerPeriodHistory)[16], int32 StartPerSecHistoryIdx=INDEX_NONE);` — Recalculates cached counter history information, after an interval or state change which affects time period tracking. @param InTimePeriods				The time period values which need caching (e.g. a period of 2 seconds, and a period of 8 seconds). @param OutPerPeriodHistory		Outputs the recalculated counter cache, for the specified time periods (e.g. elements 1 and 7 only). @param StartPerSecHistoryIdx		The index in CounterPerSecHistory to start calculating from
- L481 _private prototype_ `int32 GetHighestHistoryRequirement() const;`
- L486 _private prototype_ `void ResetAllCounters();` — Resets all counters - typically when entering dormancy
- L488 _private prototype_ `int32 AddNewCounter_Internal(int32 Count, const TArrayView<FEscalationCounter>& CountersPerPeriodAlloc);`
- L497 _public function_ `FEscalationCounter& GetFrameCounter(int32 CounterIndex)` — Accessor for the current frames counter (this is the primary place where counters are incremented). @param CounterTndex	The index of the counter @return				The current frames counter, of the specified index
- L507 _public prototype_ `void CheckQuotas();` — Checks if any escalation quota's have been hit, and if so, updates/escalates the severity state
- L515 _public prototype_ `void TickRealtime(double TimeSeconds);` — Ticks the escalation manager NOTE: This takes the current time, in seconds, rather than DeltaTime. @param TimeSeconds	The (can be approximate) current time
- L522 _public function_ `bool DoesRequireTick() const` — Whether or not calls to Tick are presently required @return	Whether Tick is required
- L533 _public prototype_ `bool IsDormant() const;` — Whether or not the current state is a dormant state, which does not require ticking
- L538 _public prototype_ `const UEscalationManagerConfig* GetBaseConfig() const;` — Returns a reference to the BaseConfig object
- L543 _public prototype_ `void SetManagerContext(FString InManagerContext);` — Sets a new ManagerContext value
- L548 _public prototype_ `void SetNotifySeverityUpdate(FNotifySeverityUpdate&& InNotifySeverityUpdate);` — Sets a new NotifySeverityUpdate value
- L553 _private member_ `const UEscalationManagerConfig* BaseConfig = nullptr;` — The state configuration object for this manager
- L556 _private member_ `FString ManagerContext;` — Extra context to use when logging severity state updates (e.g. Player IP)
- L559 _private member_ `FNotifySeverityUpdate NotifySeverityUpdate;` — The callback to use to notify of state severity escalation/de-escalation
- L562 _private member_ `int32 NumCounters = 0;` — The number of different counter types this escalation manager keeps track of
- L565 _private member_ `bool bEnabled = false;` — Whether or not this escalation manager is enabled
- L569 _private member_ `TStructOnScopeLite<FEscalationState> State;` — The managers escalation state
- L572 _private member_ `int8 ActiveState = 0;` — The currently active escalation severity state settings
- L575 _private member_ `double LastMetEscalationConditions = 0.0;` — The last time the previous severity states escalation conditions were met (to prevent bouncing up/down between states)
- L579 _private member_ `TArrayView<FEscalationCounter> FrameCounters;` — Per-frame counters
- L582 _private member_ `TArrayView<FEscalationCounter> SecondCounters;` — Per-second counters (approximate - may cover more than one second, in the case of expensive/long-running counted events)
- L585 _private member_ `double LastPerSecQuotaBegin = 0.0;` — Timestamp for the last time per-second quota counting began
- L588 _private member_ `TArray<TArrayView<FEscalationCounter>> CountersPerSecHistory;` — Stores enough per second quota history, to allow all EscalationSeverity states to recalculate if their CooloffTime is reached
- L591 _private member_ `TArray<FEscalationCounter> CountersPerSecHistoryAlloc;` — Allocation for the above array, to reduce indirection
- L594 _private member_ `int32 LastCountersPerSecHistoryIdx = 0;` — The last written index of CountersPerSecHistory
- L597 _private member_ `TArrayView<FEscalationCounter> CountersPerPeriodHistory[16] = {};` — Counter history which is precalculated/cached from CountersPerSecHistory, for tracking per-period time (up to a maximum of 16s)
- L601 _private member_ `const TArrayView<TArrayView<int32>> RegisteredCounters;` — Lists of registered counters, per category

#### class `UE::Net::FEscalationManager::TStructOnScopeLite`  
`template<typename T, typename = decltype(TBaseStructure<T>::Get())> class TStructOnScopeLite final : public FStructOnScope`  
_L389-428_
- inherits: `FStructOnScope`
- desc: Simple type wrapper for FStructOnScope, without any allocation and without owning the memory
- L392 _public function_ `TStructOnScopeLite(const UStruct* InScriptStruct, uint8* Data) : FStructOnScope(InScriptStruct, Data)`
- L398 _public function_ `T* Get() const`
- L403 _public function_ `T* operator->() const`
- L408 _public function_ `explicit operator bool() const`
- L414 _public function_ `template<typename U> U* Cast()`
- L424 _public function_ `template<typename U> const U* Cast() const`

#### struct `UE::Net::FEscalationManager::FEscalationManagerParms`  
`struct FEscalationManagerParms`  
_L431-437_
- L433 _public member_ `int32 NumCounters = 0;`
- L434 _public member_ `const TArrayView<TArrayView<int32>> RegisteredCountersCache = {};`
- L435 _public member_ `const UStruct* StateStruct = nullptr;`
- L436 _public member_ `uint8* StateMemory = nullptr;`

#### struct `UE::Net::FEscalationManager::FEscalationManagerInitParms`  
`struct FEscalationManagerInitParms`  
_L439-444_
- L441 _public member_ `const TArrayView<FEscalationCounter> FrameCounters = {};`
- L442 _public member_ `const TArrayView<FEscalationCounter> SecondCounters = {};`
- L443 _public member_ `const TArrayView<FEscalationCounter> CountersPerPeriodHistoryAlloc = {};`

#### enum `UE::Net::EEmptyCategories`  
`enum EEmptyCategories : uint32`  
_L605-608_
- desc: Default value for TEscalationManager's CounterCategoriesEnum
- L607 _public enumerator_ `Max`

#### class `UE::Net::TEscalationManager`  
`template<typename CountersEnum, typename EscalationStateType, typename CounterCategoriesEnum=EEmptyCategories> class TEscalationManager final : public FEscalationManager`  
_L618-743_
- inherits: `FEscalationManager`
- desc: Manages initialization/application of escalation states for the specified escalation state type, and allocation/tracking of the specified counters/timers used to calculate state change quotas/thresholds. The different counter types are specified in sequential order in the 'CountersEnum' enum, followed by a final/unused Max value.
- L635 _private function_ `template<typename T, typename TEnableIf<TModels_V<CHasEnumPreallocNum, T>>::Type* = nullptr> inline static constexpr int32 GetCounterNumPrealloc()` — 'typename = typename TEnableIf' does not work here, unusually
- L641 _private function_ `template<typename T, typename TEnableIf<!TModels_V<CHasEnumPreallocNum, T>>::Type* = nullptr> inline static constexpr int32 GetCounterNumPrealloc()`
- L647 _private member_ `static constexpr int32 TNum = (int32)CountersEnum::Max;` — The number of static counters in the specified enum (Max must come after the last static counter)
- L650 _private member_ `static constexpr int32 TNumPrealloc = GetCounterNumPrealloc<CountersEnum>();` — The number of counters to preallocate inline, for newly added counters
- L653 _private member_ `static constexpr int32 TNumCategories = (int32)CounterCategoriesEnum::Max;` — The number of categories in the counter categories enum
- L660 _public function_ `TEscalationManager() : FEscalationManager( FEscalationManagerParms { TNum, MakeArrayView(RegisteredCountersCacheAlloc, TNumCategories), EscalationStateType::StaticStruct(), (uint8*)&StateAlloc` — Base constructor
- L688 _public function_ `void Init(FString ConfigContext)` — Initializes the escalation manager @param ConfigContext		Additional context to use for state configuration (e.g. NetDriver name, to separate config for each NetDriver)
- L703 _public function_ `int32 AddNewCounter(int32 Count=1)` — Dynamically adds a new counter not specified in CountersEnum, and returns its index. If NumPrealloc (or Max if not specified) is exceeded, counter tracking will switch from inline allocation to the heap. @param Count		The number of counters to add @return			The index of the first added counter
- L722 _public function_ `void RegisterCounterCategory(int32 CategoryIndex, int32 CounterIndex)` — Registers a counter for automatic processing under the specified counter category, as set by CounterCategoriesEnum (each category can implement a different type of custom processing, in HasHitAnyQuota) @param CategoryIndex		The processing category the counter should be registered under @param CounterIndex		The index of the counter to register
- L736 _private member_ `EscalationStateType StateAlloc;`
- L738 _private member_ `TArray<FEscalationCounter, TInlineAllocator<TNumPrealloc>> FrameCountersAlloc;`
- L739 _private member_ `TArray<FEscalationCounter, TInlineAllocator<TNumPrealloc>> SecondCountersAlloc;`
- L740 _private member_ `TArray<FEscalationCounter, TInlineAllocator<TNumPrealloc * UE_ARRAY_COUNT(CountersPerPeriodHistory)>> CountersPerPeriodAlloc;`
- L741 _private member_ `TArray<int32, TInlineAllocator<TNumPrealloc>> RegisteredCountersAlloc[FMath::Max(TNumCategories, 1)];`
- L742 _private member_ `TArrayView<int32> RegisteredCountersCacheAlloc[FMath::Max(TNumCategories, 1)];`

#### struct `UE::Net::TEscalationManager::CHasEnumPreallocNum`  
`struct CHasEnumPreallocNum`  
_L625-631_
- L628 _public prototype_ `template<typename T> auto Requires() -> decltype( T::NumPrealloc );`

#### class `UEscalationManagerConfig`  
`class UEscalationManagerConfig : public UStatePerObjectConfig`  
_L755-770_
- reflection: `UCLASS(config=Engine, PerObjectConfig, MinimalAPI)`
- inherits: `UStatePerObjectConfig`
- desc: Base class for defining escalation state configuration. Subclass and override 'InitConfigDefaultsInternal' to initialize EscalationSeverity and bEnabled (and other custom config variables).
- L760 _private prototype_ `virtual void LoadStateConfig() override;`
- L766 _public member_ `TArray<FString> EscalationSeverity;` — `UPROPERTY(config)` — Names of the different states for escalating severity, depending on conditions for each state
- L769 _public member_ `TArray<TStructOnScope<FEscalationState>> EscalationSeverityState;` — The different states of escalating severity, depending on the escalation thresholds that have been met

#### Free symbols / members of external scopes

- L104 _macro_ `#define ESCALATION_QUOTA_DEBUG 0` — Time Quota debugging
- L110 _namespace_ `namespace UE`
- L112 _namespace_ `namespace Net` (scope `UE`)
- L278 _namespace_ `namespace UE`
- L280 _namespace_ `namespace Net` (scope `UE`)
- L295 _typedef_ `using FNotifySeverityUpdate = TUniqueFunction<void(const FEscalationState& OldState, const FEscalationState& NewState, ESeverityUpdate UpdateType)>;` (scope `UE::Net`) — Callback notifying when the escalation state has been updated @param OldState		The old state being escalated from (same as new state - but different object - on first initialization) @param NewState		The new/active escalation state @param UpdateType	Whether the update was an escalation (including auto-escalation) or de-escalation

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/NetCloseResult.h` (Public)


#### enum `ENetCloseResult`  
`enum class ENetCloseResult : uint32`  
_L23-396_
- reflection: `UENUM()`
- desc: Network Close results (can occur before NetDriver/NetConnection creation, and can be success or error) Licensees should use ENetCloseResult::Extended, and specify an ErrorContext value to FNetCloseResult, to specify custom results NOTE: If you modify this, run the enum-checking smoke test to verify you didn't forget to update anything else: System.Core.Networking.FNetCloseResult.EnumTest
- L28 _public enumerator_ `NetDriverAlreadyExists` — A relevant net driver has already been created for this service
- L31 _public enumerator_ `NetDriverCreateFailure` — The net driver creation failed
- L34 _public enumerator_ `NetDriverListenFailure` — The net driver failed its Listen() call
- L37 _public enumerator_ `ConnectionLost` — A connection to the net driver has been lost
- L40 _public enumerator_ `ConnectionTimeout` — A connection to the net driver has timed out
- L43 _public enumerator_ `FailureReceived` — The net driver received an NMT_Failure message
- L46 _public enumerator_ `OutdatedClient` — The client needs to upgrade their game
- L49 _public enumerator_ `OutdatedServer` — The server needs to upgrade their game
- L52 _public enumerator_ `PendingConnectionFailure` — There was an error during connection to the game
- L55 _public enumerator_ `NetGuidMismatch` — NetGuid mismatch
- L58 _public enumerator_ `NetChecksumMismatch` — Network checksum mismatch
- L64 _public enumerator_ `SecurityMalformedPacket` — The packet didn't follow protocol
- L67 _public enumerator_ `SecurityInvalidData` — The packet contained invalid data
- L70 _public enumerator_ `SecurityClosed` — The connection had issues (possibly malicious) and was closed
- L76 _public enumerator_ `Unknown` — Default state (do not move the position of this in enum)
- L79 _public enumerator_ `Success` — Close was successful, happening under normal conditions
- L82 _public enumerator_ `Extended` — Extended/custom ErrorContext state. To be interpreted by code
- L88 _public enumerator_ `HostClosedConnection` — Host closed the connection
- L91 _public enumerator_ `Disconnect` — Disconnected remotely
- L94 _public enumerator_ `Upgrade` — Client needs to upgrade
- L97 _public enumerator_ `PreLoginFailure` — PreLogin failed
- L100 _public enumerator_ `JoinFailure` — Join failed
- L103 _public enumerator_ `JoinSplitFailure` — JoinSplit failed
- L106 _public enumerator_ `AddressResolutionFailed` — Address Rssolution Failed
- L112 _public enumerator_ `RPCDoS` — RPC DoS Detection kicked the player
- L115 _public enumerator_ `Cleanup` — NetConnection Cleanup was triggered
- L118 _public enumerator_ `MissingLevelPackage` — UpdateLevelVisibility missing level package
- L121 _public enumerator_ `PacketHandlerIncomingError` — PacketHandler Error processing incoming packet
- L124 _public enumerator_ `ZeroLastByte` — Packet had zeros in the last byte
- L127 _public enumerator_ `ZeroSize` — Zero size packet
- L130 _public enumerator_ `ReadHeaderFail` — Failed to read PacketHeader
- L133 _public enumerator_ `ReadHeaderExtraFail` — Failed to read extra PacketHeader information
- L136 _public enumerator_ `AckSequenceMismatch` — Sequence mismatch while processing acks
- L139 _public enumerator_ `BunchBadChannelIndex` — Bunch channel index exceeds maximum channel limit
- L142 _public enumerator_ `BunchChannelNameFail` — Bunch channel name serialization failed
- L145 _public enumerator_ `BunchWrongChannelType` — Bunch specified wrong channel type for an existing channel
- L148 _public enumerator_ `BunchHeaderOverflow` — Bunch header serialization overflowed
- L151 _public enumerator_ `BunchDataOverflow` — Bunch data serialization overflowed
- L154 _public enumerator_ `BunchServerPackageMapExports` — Server received bHasPackageMapExports packet
- L157 _public enumerator_ `BunchPrematureControlChannel` — Received control channel bunch before control channel was created
- L160 _public enumerator_ `BunchPrematureChannel` — Received non-control-channel bunch when not yet ready
- L163 _public enumerator_ `BunchPrematureControlClose` — Received control channel close before open
- L166 _public enumerator_ `UnknownChannelType` — Unknown channel type specified
- L169 _public enumerator_ `PrematureSend` — Attempted to send data before handshake is complete
- L172 _public enumerator_ `CorruptData` — Server received corrupt data from the client - or there was otherwise an error during channel processing
- L175 _public enumerator_ `SocketSendFailure` — Socket send failure
- L178 _public enumerator_ `BadChildConnectionIndex` — Failed to find splitscreen player matching ChildConnection NetPlayerIndex
- L181 _public enumerator_ `LogLimitInstant` — Log limiting per-second checks insta-kicked the player
- L184 _public enumerator_ `LogLimitSustained` — Log limiting repeated threshold hits kicked the player
- L187 _public enumerator_ `EncryptionFailure` — Encryption failure
- L190 _public enumerator_ `EncryptionTokenMissing` — EncryptionToken is missing
- L196 _public enumerator_ `ReceivedNetGUIDBunchFail` — ReceiveNetGUIDBunch serialization failed
- L199 _public enumerator_ `ReceivedNetExtBunchFail` — ReceiveNetExtBunch serialization failed
- L202 _public enumerator_ `MaxReliableExceeded` — Too many reliable bunches queued
- L205 _public enumerator_ `ReceivedNextBunchFail` — ReceivedNextBunch serialization failed
- L208 _public enumerator_ `ReceivedNextBunchQueueFail` — Queued ReceivedNextBunch serialization failed
- L211 _public enumerator_ `PartialInitialReliableDestroy` — Reliable partial initial bunch attempting to destroy incomplete reliable partial bunch
- L214 _public enumerator_ `PartialMergeReliableDestroy` — Reliable partial merge bunch attempting to destroy incomplete reliable partial bunch
- L217 _public enumerator_ `PartialInitialNonByteAligned` — Partial initial bunch which is not byte aligned
- L220 _public enumerator_ `PartialNonByteAligned` — Non-final partial bunch which is not byte aligned
- L223 _public enumerator_ `PartialFinalPackageMapExports` — Final partial bunch has package map exports
- L226 _public enumerator_ `PartialTooLarge` — Partial bunch exceeded maximum partial bunch size
- L229 _public enumerator_ `AlreadyOpen` — Received open bunch when channel already open
- L232 _public enumerator_ `ReliableBeforeOpen` — Received reliable bunch before channel was fully open
- L235 _public enumerator_ `ReliableBufferOverflow` — Reliable buffer overflowed when attempting to send
- L238 _public enumerator_ `RPCReliableBufferOverflow` — Reliable buffer overflowed when attempting to send RPC
- L244 _public enumerator_ `ControlChannelClose` — Control channel closing
- L247 _public enumerator_ `ControlChannelEndianCheck` — Endianness check failed
- L250 _public enumerator_ `ControlChannelPlayerChannelFail` — The ActorChannel for the connections PlayerController failed
- L253 _public enumerator_ `ControlChannelMessageUnknown` — Received unknown control channel message
- L256 _public enumerator_ `ControlChannelMessageFail` — Failed to read control channel message
- L259 _public enumerator_ `ControlChannelMessagePayloadFail` — Failed to read control channel message payload
- L262 _public enumerator_ `ControlChannelBunchOverflowed` — Control channel send bunch overflowed
- L265 _public enumerator_ `ControlChannelQueueBunchOverflowed` — Queued control channel send bunch overflowed
- L271 _public enumerator_ `ClientHasMustBeMappedGUIDs` — Client tried to set bHasMustBeMappedGUIDs
- L274 _public enumerator_ `ClientSentDestructionInfo` — Client tried to send a destruction info
- L277 _public enumerator_ `UnregisteredMustBeMappedGUID` — Received MustBeMappedGUID that isn't registered
- L280 _public enumerator_ `ObjectReplicatorReceivedBunchFail` — FObjectReplicator ReceivedBunch failed
- L283 _public enumerator_ `ContentBlockFail` — Content block serialization failed
- L286 _public enumerator_ `ContentBlockHeaderRepLayoutFail` — Content block header bOutHasRepLayout serialization failed
- L289 _public enumerator_ `ContentBlockHeaderIsActorFail` — Content block header bIsActor serialization failed
- L292 _public enumerator_ `ContentBlockHeaderObjFail` — Content block header object serialization failed
- L295 _public enumerator_ `ContentBlockHeaderPrematureEnd` — Reached end of bunch prematurely, after reading content block header
- L298 _public enumerator_ `ContentBlockHeaderSubObjectActor` — Content block header sub-object was an Actor
- L301 _public enumerator_ `ContentBlockHeaderBadParent` — Content block header sub-object not in parent actor
- L304 _public enumerator_ `ContentBlockHeaderInvalidCreate` — The client tried to create a sub-object
- L307 _public enumerator_ `ContentBlockHeaderStablyNamedFail` — Content block header bStablyNamed serialization failed
- L310 _public enumerator_ `ContentBlockHeaderNoSubObjectClass` — Content block header unable to ready sub-object class
- L313 _public enumerator_ `ContentBlockHeaderUObjectSubObject` — Content block header sub-object was UObject base class
- L316 _public enumerator_ `ContentBlockHeaderAActorSubObject` — Content block header sub-object was an AActor subclass
- L319 _public enumerator_ `ContentBlockHeaderFail` — Content block header serialization failed
- L322 _public enumerator_ `ContentBlockPayloadBitsFail` — Content block payload NumPayloadBits serialization failed
- L325 _public enumerator_ `FieldHeaderRepIndex` — Field header RepIndex serialization failed
- L328 _public enumerator_ `FieldHeaderBadRepIndex` — Field header RepIndex exceeds maximum index limit
- L331 _public enumerator_ `FieldHeaderPayloadBitsFail` — Field header payload NumPayloadBits serialization failed
- L334 _public enumerator_ `FieldPayloadFail` — Field payload serialization failed
- L337 _public enumerator_ `ReplicationChannelCountMaxedOut` — Replication Channel Count was exceeded and channel creation failed
- L342 _public enumerator_ `BeaconControlFlowError` — Control flow error
- L345 _public enumerator_ `BeaconUnableToParsePacket` — Unable to parse expected packet structure
- L348 _public enumerator_ `BeaconAuthenticationFailure` — Failed to verify user authentication
- L351 _public enumerator_ `BeaconLoginInvalidIdError` — Login Failure, invalid ID
- L354 _public enumerator_ `BeaconLoginInvalidAuthHandlerError` — Login Failure, unable to process authentication
- L357 _public enumerator_ `BeaconAuthError` — Unable to authenticate for beacon, wrong PlayerId
- L360 _public enumerator_ `BeaconSpawnClientWorldPackageNameError` — Join failure, existing ClientWorldPackageName
- L363 _public enumerator_ `BeaconSpawnExistingActorError` — Join failure, existing beacon actor
- L366 _public enumerator_ `BeaconSpawnFailureError` — Join failure, couldn't spawn client beacon actor
- L369 _public enumerator_ `BeaconSpawnNetGUIDAckNoActor` — Join failure, no actor at NetGUIDAck
- L372 _public enumerator_ `BeaconSpawnNetGUIDAckNoHost` — Join failure, no host object at NetGUIDAck
- L375 _public enumerator_ `BeaconSpawnUnexpectedError` — Join failure, unexpected control message
- L381 _public enumerator_ `IrisProtocolMismatch` — Protocol mismatch in Iris preventing a critical object instantiation
- L384 _public enumerator_ `IrisNetRefHandleError` — When a specific handle caused a reading error
- L389 _public enumerator_ `FaultDisconnect` — Net Fault Recovery failed to recover from a fault, and is triggering a disconnect
- L395 _public enumerator_ `NotRecoverable` — Marks a PacketHandler/HandlerComponent error, that is not recoverable

#### Free symbols / members of external scopes

- L398 _prototype_ `DECLARE_NETRESULT_ENUM(ENetCloseResult);`
- L401 _prototype_ `const TCHAR* LexToString(ENetCloseResult Enum);`
- L404 _prototype_ `ENetCloseResult FromNetworkFailure(ENetworkFailure::Type Val);` — Converts from ENetworkFailure to ENetCloseResult
- L407 _prototype_ `ENetworkFailure::Type ToNetworkFailure(ENetCloseResult Val);` — Converts from ENetCloseResult to ENetworkFailure
- L411 _prototype_ `ENetCloseResult FromSecurityEvent(ESecurityEvent::Type Val);` — Converts from ESecurityEvent to ENetCloseResult
- L415 _namespace_ `namespace UE`
- L417 _namespace_ `namespace Net` (scope `UE`)
- L425 _typedef_ `using FNetCloseResult = TNetResult<ENetCloseResult>;` (scope `UE::Net`) — FNetCloseResult TNetResult alias using ENetCloseResult, for use with NetConnection Close errors and recoverable network faults.

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/NetConnectionFaultRecoveryBase.h` (Public)


#### struct `FNetFaultState`  
`struct FNetFaultState : public FEscalationState`  
_L39-86_
- reflection: `USTRUCT()`
- inherits: `FEscalationState`
- desc: Generic escalation state definition used to implement attempted recovery from faults/errors in the NetConnection level netcode. Fault handlers may have their own separate escalation tracking.
- L48 _public member_ `bool bCloseConnection = false;` — `UPROPERTY(config)` — Whether or not the current escalation state should immediately Close the connection
- L55 _public member_ `int16 EscalateQuotaFaultsPerPeriod = -1;` — `UPROPERTY(config)` — The number of faults per period before the next stage of escalation is triggered
- L59 _public member_ `int8 EscalateQuotaFaultPercentPerPeriod = -1;` — `UPROPERTY(config)` — Percentage of faults out of total number of recent packets, before the next stage of escalation is triggered
- L63 _public member_ `int16 DescalateQuotaFaultsPerPeriod = -1;` — `UPROPERTY(config)` — The number of faults per period before de-escalating into this state (adds hysteresis/lag to state changes)
- L67 _public member_ `int8 DescalateQuotaFaultPercentPerPeriod = -1;` — `UPROPERTY(config)` — Percentage of faults out of total number of recent packets, before de-escalating into this state (adds hysteresis/lag to state changes)
- L71 _public member_ `int8 EscalateQuotaTimePeriod = -1;` — `UPROPERTY(config)` — The time period to use for determining escalation/de-escalation quotas (Max: 16)
- L75 _public prototype_ `static const TCHAR* GetConfigSection();`
- L76 _public prototype_ `static UClass* GetBaseConfigClass();`
- L80 _protected prototype_ `virtual EInitStateDefaultsResult InitConfigDefaultsInternal() override;`
- L81 _protected prototype_ `virtual void ApplyImpliedValuesInternal() override;`
- L82 _protected prototype_ `virtual void ValidateConfigInternal() override;`
- L85 _private prototype_ `virtual bool HasHitAnyQuota(FHasHitAnyQuotaParms Parms) const override;`

#### enum `UE::Net::ENetFaultCounters`  
`enum class ENetFaultCounters : uint8`  
_L98-106_
- desc: Defines the static counters used for FNetFaultState escalation manager implementation. Custom counters (such as from PacketHandler's, Oodle/AES) can be dynamically added.
- L100 _public enumerator_ `PacketCount` — Total number of packets received per-period
- L101 _public enumerator_ `NetConnPacketFault` — Faults encountered by low level NetConnection packet processing (signifying packet corruption - excludes PacketHandler)
- L103 _public enumerator_ `Max`
- L105 _public enumerator_ `NumPrealloc = 6`

#### enum `UE::Net::ENetFaultCounterCategory`  
`enum class ENetFaultCounterCategory : uint8`  
_L113-122_
- desc: Categories that Net Fault Counters can optionally be registered into, so that they are automatically tracked for escalation management. Primarily used by custom counters (e.g. Oodle/AES), to plug into the main NetConnection Fault Recovery escalation quota tracking.
- L119 _public enumerator_ `NetworkCorruption` — Only worst value counter is used for quota checks, as network corruption should only affect outermost packet layer (Oodle/AES level primarily - but can occur at NetConnection level, if there are no compression/encryption handlers)
- L121 _public enumerator_ `Max`

#### class `UE::Net::FNetConnectionFaultRecoveryBaseFixLayout`  
`class FNetConnectionFaultRecoveryBaseFixLayout`  
_L147-151_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L150 _public prototype_ `virtual ~FNetConnectionFaultRecoveryBaseFixLayout() = default;`

#### class `UE::Net::FNetConnectionFaultRecoveryBase`  
`class FNetConnectionFaultRecoveryBase : public FNetConnectionFaultRecoveryBaseFixLayout`  
_L156-241_
- inherits: `FNetConnectionFaultRecoveryBaseFixLayout`
- desc: Implements the base/public interface for FNetConnectionFaultRecovery - defined here, to eliminate the need for Engine dependencies.
- L159 _public typedef_ `using FNetFaultEscalationHandler = TEscalationManager<ENetFaultCounters, FNetFaultState, ENetFaultCounterCategory>;`
- L168 _public prototype_ `EHandleNetResult NotifyHandledFault(FNetResult&& InResult);` — (For Counter Categories) Use this to notify fault recovery of a successfully handled fault it should be aware of, within HandleNetResult; this is required for escalation tracking, if that fault type is registered with a counter category. @param InResult	The successfully handled result, passed on to fault recovery @return			Returns whether or not fault recovery handled the fault (this value should be returned by the calling HandleNetResult)
- L176 _public function_ `FNetResultManager& GetFaultManager()` — Accessor for FaultManager
- L184 _public prototype_ `EHandleNetResult HandleNetResult(FNetCloseResult&& InResult);` — Convenience Forwarding function for FNetResultManager.HandleNetResult, taking FNetCloseResult/ENetCloseResult
- L189 _public prototype_ `int32 AddNewCounter(int32 Count=1);` — Passthrough for TEscalationManager.AddNewCounter (with caching, NetFaultEscalationManager has not been initialized yet)
- L194 _public prototype_ `FEscalationCounter& GetFrameCounter(int32 CounterIndex);` — Passthrough for FEscalationManager.GetFrameCounter
- L199 _public prototype_ `void RegisterCounterCategory(ENetFaultCounterCategory Category, int32 CounterIndex);` — Passthrough for TEscalationManager.RegisterCounterCategory (with caching, NetFaultEscalationManager has not been initialized yet)
- L203 _private function_ `virtual void InitEscalationManager()`
- L210 _protected member_ `bool bDisconnected = false;` — Whether or not fault recovery has disconnected the NetConnection
- L213 _protected member_ `int32 LastCounterIndex = static_cast<int32>(ENetFaultCounters::Max);` — Tracks the index of the last added counter, before NetFaultEscalationManager is created
- L216 _protected member_ `TUniquePtr<FNetFaultEscalationHandler> NetFaultEscalationManager;` — The escalation manager instance used for tracking/implementing recovery for the various fault types
- L223 _protected function_ `friend bool operator == (const FPendingCategoryRegister& A, const FPendingCategoryRegister& B)`
- L230 _protected member_ `TArray<FPendingCategoryRegister> PendingCategories;` — Tracks counter categories and indexes that are pending registration, before NetFaultEscalationManager is created
- L233 _protected member_ `TPimplPtr<FNetResult, EPimplPtrMode::DeepCopy> TrackedFaults;` — Net Faults which are currently being tracked (reset when escalation manager reaches base/normal state)
- L236 _protected member_ `TArray<uint32, TInlineAllocator<FMath::Max(static_cast<int32>(ENetFaultCounters::Max), 8)>> TrackedFaultEnumHashes;` — Enum/fast-lookup version of TrackedFaults, using GetTypeHash
- L240 _protected member_ `FNetResultManager FaultManager;` — Fault Manager for attempting to recover from connection faults, before triggering Close

#### struct `UE::Net::FNetConnectionFaultRecoveryBase::FPendingCategoryRegister`  
`struct FPendingCategoryRegister`  
_L218-227_
- L220 _public member_ `int32 CategoryIndex = 0;`
- L221 _public member_ `int32 CounterIndex = 0;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Net` (scope `UE`)
- L89 _namespace_ `namespace UE`
- L91 _namespace_ `namespace Net` (scope `UE`)
- L130 _function_ `inline uint8 ToInt(ENetFaultCounters CounterVal)` (scope `UE::Net`) — Inline integer conversion of ENetFaultCounters @param CounterVal	The value to convert to an integer @return				The integer value of the specified ENetFaultCounters value
- L141 _function_ `inline uint8 ToInt(ENetFaultCounterCategory CategoryVal)` (scope `UE::Net`) — Inline integer conversion of ENetFaultCounterCategory @param CounterVal	The value to convert to an integer @return				The integer value of the specified ENetFaultCounterCategory value

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/NetEnums.h` (Public)


#### enum `UE::Net::EJoinFlags`  
`enum class EJoinFlags`  
_L12-16_
- L14 _public enumerator_ `None`
- L15 _public enumerator_ `NoPawn = 1`

#### enum `ENetworkFailure::Type`  
`enum Type : int`  
_L24-48_
- L27 _public enumerator_ `NetDriverAlreadyExists` — A relevant net driver has already been created for this service
- L29 _public enumerator_ `NetDriverCreateFailure` — The net driver creation failed
- L31 _public enumerator_ `NetDriverListenFailure` — The net driver failed its Listen() call
- L33 _public enumerator_ `ConnectionLost` — A connection to the net driver has been lost
- L35 _public enumerator_ `ConnectionTimeout` — A connection to the net driver has timed out
- L37 _public enumerator_ `FailureReceived` — The net driver received an NMT_Failure message
- L39 _public enumerator_ `OutdatedClient` — The client needs to upgrade their game
- L41 _public enumerator_ `OutdatedServer` — The server needs to upgrade their game
- L43 _public enumerator_ `PendingConnectionFailure` — There was an error during connection to the game
- L45 _public enumerator_ `NetGuidMismatch` — NetGuid mismatch
- L47 _public enumerator_ `NetChecksumMismatch` — Network checksum mismatch

#### enum `EReplicationSystem`  
`enum class EReplicationSystem : uint8`  
_L85-90_
- reflection: `UENUM(BlueprintType)`
- L87 _public enumerator_ `Default`
- L88 _public enumerator_ `Generic`
- L89 _public enumerator_ `Iris`

#### enum `ESecurityEvent::Type`  
`enum Type`  
_L95-100_
- L97 _public enumerator_ `Malformed_Packet = 0` — The packet didn't follow protocol
- L98 _public enumerator_ `Invalid_Data = 1` — The packet contained invalid data
- L99 _public enumerator_ `Closed = 2` — The connection had issues (potentially malicious) and was closed

#### enum `UE::Net::ENetConnectionTraits`  
`enum class ENetConnectionTraits : uint32`  
_L128-136_
- desc: Traits of a UNetConnection that are of importance to propagate to replication systems not depending on Engine.
- L131 _public enumerator_ `None = 0U` — No traits. Must be zero.
- L133 _public enumerator_ `ReplayRecording = 1U` — The connection is for replay recording
- L135 _public enumerator_ `ReplayPlayback = 2U` — The connection is for replay playback

#### enum `UE::Net::EProxyType`  
`enum class EProxyType : uint8`  
_L139-146_
- L141 _public enumerator_ `None = 0`
- L143 _public enumerator_ `Backend` — Replicate objects from different game servers into the world.
- L145 _public enumerator_ `Frontend` — Replicate objects to clients that were replicated into the world by another replication system.

#### enum `UE::Net::ENetRefHandleError`  
`enum class ENetRefHandleError : uint32`  
_L151-158_
- desc: Error types used when reporting an error on a specific Iris handle
- L153 _public enumerator_ `None = 0x00`
- L154 _public enumerator_ `BitstreamCorrupted` — An error while reading detected an irrecoverable bitstream corruption. Client was forced to disconnect
- L155 _public enumerator_ `ReplicationDisabled` — An error while reading was recoverable but prevents this NetObject from replicating.
- L156 _public enumerator_ `BlockedByMustBeMapped` — An object is blocked due to MustBeMapped references not resolving fast enough
- L157 _public enumerator_ `BlockedByCreationParents` — An object is blocked waiting on creation parents that do not exist yet on the client.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)
- L22 _namespace_ `namespace ENetworkFailure`
- L51 _namespace_ `namespace ENetworkFailure`
- L53 _function_ `inline const TCHAR* ToString(ENetworkFailure::Type FailureType)` (scope `ENetworkFailure`)
- L93 _namespace_ `namespace ESecurityEvent`
- L103 _function_ `inline const TCHAR* ToString(const ESecurityEvent::Type EnumVal)` (scope `ESecurityEvent`) — @return the stringified version of the enum passed in
- L124 _namespace_ `namespace UE`
- L124 _namespace_ `namespace Net` (scope `UE`)
- L137 _prototype_ `ENUM_CLASS_FLAGS(ENetConnectionTraits);` (scope `UE::Net`)
- L160 _function_ `inline const TCHAR* LexToString(ENetRefHandleError NetRefHandleError)` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/NetResult.h` (Public)


#### enum `UE::Net::ENetResultString`  
`enum class ENetResultString : uint8`  
_L41-51_
- desc: Conversion types for TNetResult::ToString
- L44 _public enumerator_ `WithoutChain` — Only include the base TNetResult in the string
- L47 _public enumerator_ `WithChain` — Include the whole chain of TNetResult's in the string
- L50 _public enumerator_ `ResultEnumOnly` — Only include the raw result enum in the string

#### struct `UE::Net::FNetResult`  
`struct FNetResult`  
_L63-281_
- desc: Base/non-templatized implementation for TNetResult
- L68 _private function_ `inline FNetResult(uint64 InResult, const UEnum* InResultEnumObj) : Result(InResult) , ResultEnumObj(InResultEnumObj) , RawResultEnumObj(InResultEnumObj)`
- L75 _private function_ `inline FNetResult(uint64 InResult, const UEnum* InResultEnumObj, const FString& InErrorContext) : Result(InResult) , ResultEnumObj(InResultEnumObj) , RawResultEnumObj(InResultEnumObj) , ErrorContext(InErrorContext)`
- L83 _private function_ `inline FNetResult(uint64 InResult, const UEnum* InResultEnumObj, FString&& InErrorContext) : Result(InResult) , ResultEnumObj(InResultEnumObj) , RawResultEnumObj(InResultEnumObj) , ErrorContext(MoveTemp(InErrorContext))`
- L92 _public prototype_ `FNetResult(const FNetResult&) = default;`
- L93 _public prototype_ `FNetResult& operator=(const FNetResult&) = default;`
- L94 _public prototype_ `FNetResult(FNetResult&&) = default;`
- L95 _public prototype_ `FNetResult& operator=(FNetResult&&) = default;`
- L96 _public prototype_ `~FNetResult() = default;`
- L101 _public function_ `bool operator == (const FNetResult& A) const`
- L107 _public function_ `bool operator != (const FNetResult& A) const`
- L158 _public prototype_ `FString DynamicToString(ENetResultString ConversionType=ENetResultString::WithoutChain) const;` — Use UEnum reflection to convert result to human readable string (ExportText style). Use ToString instead, when casting is possible. @param ConversionType	The type of string conversion to perform (e.g. whether or not to include the whole chain of results) @return					Returns the result converted to a string
- L171 _public function_ `void AddChainResult(FNetResult&& InResult)` — Chains a new result to an existing result, putting the new result at the end of the chain. @param InResult		The result to chain to this one. Should use MoveTemp.
- L190 _public function_ `template<typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type> void AddChainResult(TNetResult<T>&& InResult)` — Chains a new result to an existing result, putting the new result at the end of the chain. @param InResult		The result to chain to this one. Should use MoveTemp.
- L211 _public function_ `template<typename ResultEnum, typename = typename TEnableIf<TIsEnum<ResultEnum>::Value>::Type> bool HasChainResult(ResultEnum A) const` — Determines whether the specified enum result is contained within this result chain NOTE: Does not check the error code @param A		The result to search for @return		Whether or not the result exists in the chain
- L268 _private member_ `uint64 Result = 0;` — Base result value
- L271 _private member_ `TWeakObjectPtr<const UEnum> ResultEnumObj;` — Weak pointer to the UEnum for the result values type
- L274 _private member_ `const void* RawResultEnumObj = nullptr;` — Raw pointer to the result UEnum type, for comparison only
- L277 _private member_ `FString ErrorContext;` — Error context, intended to be interpreted by code
- L280 _private member_ `TPimplPtr<FNetResult, EPimplPtrMode::DeepCopy> NextResult;` — If multiple sequential results (typically errors) are returned, accumulate them as a linked list

#### struct `UE::Net::FNetResult::FConstIterator`  
`struct FConstIterator final`  
_L229-263_
- desc: Chain iterator
- L231 _public function_ `FConstIterator(const FNetResult& InResult) : CurResult(&InResult)`
- L236 _public function_ `explicit operator bool() const`
- L241 _public function_ `const FNetResult& operator *() const`
- L248 _public function_ `const FNetResult* operator ->() const`
- L253 _public function_ `void operator ++()`
- L262 _private member_ `const FNetResult* CurResult;`

#### struct `UE::Net::TNetResult`  
`template<typename ResultEnum> struct TNetResult final : public FNetResult`  
_L329-460_
- inherits: `FNetResult`
- desc: Generic result struct for Network Results (e.g. Close and failures) - partially adapted from FOnlineError/FResult. ResultEnum must have LexToString implemented, and DECLARE_NETRESULT_ENUM(ResultEnum) must be declared for each enum type. NOTE: Support for using results to modify control flow, depends on how they are implemented in the netcode.
- L334 _public typedef_ `using UnderlyingResultType = __underlying_type(ResultEnum);`
- L342 _public function_ `TNetResult(ResultEnum InResult=ResultEnum::Unknown) : FNetResult(static_cast<UnderlyingResultType>(InResult), StaticEnum<ResultEnum>())` — Default constructor @param InResult			The type of result
- L357 _public function_ `TNetResult(ResultEnum InResult, const FString& InErrorContext) : FNetResult(static_cast<UnderlyingResultType>(InResult), StaticEnum<ResultEnum>())` — Main constructor, specifying full result (usually error) @param InResult			The type of result @param InErrorContext	Additional context associated with error results (to be interpreted by code)
- L373 _public function_ `FString ToString(ENetResultString ConversionType=ENetResultString::WithoutChain) const` — Convert result to human readable string (ExportText style) @param ConversionType	The type of string conversion to perform (e.g. whether or not to include the whole chain of results) @return					Returns the result converted to a string
- L405 _public function_ `bool WasSuccessful() const`
- L410 _public function_ `ResultEnum GetResult() const`
- L415 _public function_ `const FString& GetErrorContext() const`
- L428 _public function_ `bool HasChainResult(const TNetResult& A) const` — Determines whether the specified result is contained within this result chain NOTE: Also checks against the error code @param A		The result to search for @return		Whether or not the result exists in the chain
- L444 _public function_ `bool operator == (ResultEnum A) const`
- L449 _public function_ `bool operator != (ResultEnum A) const`
- L456 _private function_ `static const TCHAR* DefaultErrorContext(ResultEnum InResult)` — Default ErrorContext based on ResultEnum

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Net` (scope `UE`)
- L32 _prototype_ `template<typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type> TNetResult<T>* Cast(FNetResult* InResult);` (scope `UE::Net`) — Expose FNetResult friend functions for Argument Dependent Lookup
- L35 _prototype_ `template<typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type> const TNetResult<T>* Cast(const FNetResult* InResult);` (scope `UE::Net`)
- L53 _namespace_ `namespace Private` (scope `UE::Net`)
- L55 _prototype_ `void NetResultToString(FString& OutResultStr, const TCHAR* LexResult, const FString& ErrorContext, ENetResultString ConversionType);` (scope `UE::Net::Private`)
- L120 _function_ `template<typename T, typename> friend TNetResult<T>* Cast(FNetResult* InResult)` (scope `UE::Net`) — Casts an FNetResult to a TNetResult<T>, with enum type checking @param InResult	The FNetResult to cast @return			Returns the resulting TNetResult<T>
- L139 _function_ `template<typename T, typename> friend const TNetResult<T>* Cast(const FNetResult* InResult)` (scope `UE::Net`) — Casts an FNetResult to a TNetResult<T>, with enum type checking @param InResult	The FNetResult to cast @return			Returns the resulting TNetResult<T>
- L160 _function_ `friend uint32 GetTypeHash(FNetResult const& Hash)` (scope `UE::Net`)
- L289 _function_ `inline void AddToChainResultPtr(TPimplPtr<FNetResult, EPimplPtrMode::DeepCopy>& ResultPtr, FNetResult&& Result)` (scope `UE::Net`) — Chains a new result to the result pointer, putting it at the end of the chain - or assigns it to the result pointer, if not set. @param ResultPtr		The result pointer to chain or assign the new result to. @param Result		The result to chain to the result pointer. Should use MoveTemp.
- L308 _function_ `inline FNetResult AddToAndConsumeChainResultPtr(TPimplPtr<FNetResult, EPimplPtrMode::DeepCopy>& ResultPtr, FNetResult&& Result)` (scope `UE::Net`) — Chains a new result to the end of the result pointer (or takes its place if not set), then consumes/moves/returns the pointer result @param ResultPtr		The result pointer to consume and chain the new result to. @param Result		The result to chain to the consumed result pointer. Should use MoveTemp. @return				Returns the final result, which is either the combined result pointer and new result, or just the new result
- L469 _macro_ `#define DECLARE_NETRESULT_ENUM(EnumType) \` — Exposes TNetResult friend functions to Argument-Dependent-Lookup, so these functions are found when 'EnumType' is passed as a parameter. This is normally automatic when TNetResult is passed as a parameter, but it's not automatic when 'EnumType' is implicitly casted, e.g: AddToChainResultPtr(Bunch.ExtendedError, ENetCloseResult::MaxReliableExceeded); @param EnumType		The TNetResult enum type being declared

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/NetResultManager.h` (Public)


#### enum `UE::Net::EHandleNetResult`  
`enum class EHandleNetResult : uint8`  
_L25-30_
- desc: The result of a HandleNetResult call
- L27 _public enumerator_ `Closed` — The connection was closed (certain code paths should return early)
- L28 _public enumerator_ `Handled` — The result was handled, but (if a fault) has not yet resulted in a connection Close
- L29 _public enumerator_ `NotHandled` — The result was not handled (no result handler or 'unhandled result' callback handled it)

#### enum `UE::Net::EAddResultHandlerPos`  
`enum class EAddResultHandlerPos : uint8`  
_L35-39_
- desc: The position to add a new FNetResultHandler, in the list of result handlers
- L37 _public enumerator_ `First` — Places the new handler at the start of the list (higher precedence)
- L38 _public enumerator_ `Last` — Places the new handler at the end of the list (lower precedence)

#### class `UE::Net::FNetResultManager`  
`class FNetResultManager final`  
_L47-108_
- desc: Net Result Manager Handles arbitrary net results, which may attempt recovery from errors instead of e.g. immediately closing the NetConnection
- L55 _public typedef_ `using FUnhandledResultFunc = TUniqueFunction<EHandleNetResult(FNetResult&& InResult)>;` — Callback for handling results which no FNetResultHandler took ownership of @param InResult		Specifies the result
- L59 _public prototype_ `FNetResultManager() = default;`
- L61 _public prototype_ `FNetResultManager(FNetResultManager&) = delete;`
- L62 _public prototype_ `FNetResultManager& operator=(const FNetResultManager&) = delete;`
- L63 _public prototype_ `FNetResultManager(FNetResultManager&&) = delete;`
- L64 _public prototype_ `FNetResultManager& operator=(FNetResultManager&&) = delete;`
- L72 _public prototype_ `void AddResultHandler(TUniquePtr<FNetResultHandler>&& InResultHandler, EAddResultHandlerPos Position=EAddResultHandlerPos::Last);` — Adds a new result handler to the result manager (owned by the result manager) @param InResultHandler	The new result handler to be added @param Position			The position/precedence in the result handler list, to place the new handler
- L80 _public prototype_ `void AddResultHandlerPtr(FNetResultHandler* InResultHandler, EAddResultHandlerPos Position=EAddResultHandlerPos::Last);` — Adds a new result handler pointer to the result manager (not owned by the result manager) @param InResultHandler	The new result handler to be added @param Position			The position/precedence in the result handler list, to place the new handler
- L90 _public prototype_ `EHandleNetResult HandleNetResult(FNetResult&& InResult);` — Takes a net result and passes it around to the result handlers and callbacks until it is handled, or returns 'EHandleNetResult::NotHandled'. NOTE: InResult is moved when result is Closed/Handled, and not moved when result is NotHandled. @param InResult		Specifies the result @return				Whether or not the result has handled or resulted in a close, or went unhandled
- L97 _public prototype_ `void SetUnhandledResultCallback(FUnhandledResultFunc InCallback);` — Sets a callback for handling net results which no result handlers have dealt with @param InCallback	The callback to use for unhandled results
- L101 _private member_ `TArray<FNetResultHandler*, TInlineAllocator<8>> ResultHandlers;` — The list of result handlers, for attempting to handle results with
- L104 _private member_ `TArray<TUniquePtr<FNetResultHandler>> OwnedResultHandlers;` — Result handlers passed to and owned by the result manager
- L107 _private member_ `FUnhandledResultFunc UnhandledResultCallback;` — The callback for handling results which no result handler has dealt with

#### class `UE::Net::FNetResultHandler`  
`class FNetResultHandler`  
_L117-154_
- desc: Net Result Handler Result handlers implement result tracking and recovery attempts for select fault types, with the ability to expand custom result handling, within NetDriver subclasses or other arbitrary parts of the netcode.
- L122 _public prototype_ `FNetResultHandler() = default;`
- L123 _public prototype_ `virtual ~FNetResultHandler() = default;`
- L125 _public prototype_ `FNetResultHandler(const FNetResultHandler&) = delete;`
- L126 _public prototype_ `FNetResultHandler& operator=(const FNetResultHandler&) = delete;`
- L127 _public prototype_ `FNetResultHandler(FNetResultHandler&&) = delete;`
- L128 _public prototype_ `FNetResultHandler& operator=(FNetResultHandler&&) = delete;`
- L134 _public function_ `virtual void Init()` — Initializes the result handler
- L146 _public function_ `virtual EHandleNetResult HandleNetResult(FNetResult&& InCloseResult)` — Takes a net result and either handles it or returns 'EHandleNetResult::NotHandled'. NOTE: InResult is moved when result is Closed/Handled, and not moved when result is NotHandled. @param InResult		Specifies the result @return				Whether or not the result has handled or resulted in close, or went unhandled
- L153 _protected member_ `FNetResultManager* ResultManager = nullptr;` — The Result Manager which the result handler is assigned to

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/RPCDoSDetection.h` (Public)


#### struct `FRPCDoSCounters`  
`struct FRPCDoSCounters`  
_L63-105_
- desc: Struct containing RPC counters covering any time period (e.g. frame/second/arbitrary-period)
- L66 _public member_ `int32 RPCCounter = 0;` — Counter for the number of RPCs received
- L69 _public member_ `double AccumRPCTime = 0.0;` — Accumulated time spent executing RPCs
- L73 _public member_ `double DebugAccumRPCTime = 0.0;` — Debug version of the value above, using more accurate timing, for testing accuracy of approximate time
- L81 _public function_ `void ResetRPCCounters()` — Reset the values of this RPC counter
- L96 _public function_ `void AccumulateCounter(const FRPCDoSCounters& InCounter)` — Accumulate another RPC counter into this one @param InCounter		The RPC counter to accumulate with

#### enum `ERPCBlockState`  
`enum class ERPCBlockState : uint8`  
_L110-116_
- desc: The status of blocking for an individual RPC
- L112 _public enumerator_ `Unchecked` — The status for this RPC has not been checked
- L113 _public enumerator_ `OnAllowList` — The RPC is allow listed and can't be blocked
- L114 _public enumerator_ `NotBlocked` — The RPC is not blocked
- L115 _public enumerator_ `Blocked` — The RPC is blocked

#### struct `FRPCTrackingInfo`  
`struct FRPCTrackingInfo`  
_L121-151_
- desc: Live tracking information for individual RPC's, for timing of RPC's, analytics, and handling blocking
- L124 _public member_ `FRPCDoSCounters PerPeriodHistory[16] = {};` — Contains up to 'HistoryCount' seconds of counter/timing data for the RPC. [0] = last second of data, [15] = last 16 seconds of data.
- L127 _public member_ `uint8 HistoryCount = 0;` — The number of valid 'PerPeriodHistory' entries
- L130 _public member_ `uint8 LastTrackedSecondIncrement = 0;` — The last time this RPC was called/tracked (based on 'SecondsIncrementer'). Indirect index to the active PerPeriodHistory entry.
- L133 _public member_ `ERPCBlockState BlockState = ERPCBlockState::Unchecked;` — Whether or not the RPC is currently being blocked, after having hit a blocking quota.
- L136 _public member_ `TSharedPtr<FRPCAnalytics> RPCTrackingAnalyticsEntry;` — Caches a pointer to analytics for this RPC, if it's within analytics thresholds
- L145 _public function_ `uint8 GetCurrentHistoryIdx() const` — Gets the active 'PerPeriodHistory' index, based on LastTrackedSecondIncrement. @return	The currently active 'PerPeriodHistory' index.

#### struct `FActiveRPCTrackingInfo`  
`struct FActiveRPCTrackingInfo`  
_L156-163_
- desc: Stores a reference to active/valid FRPCTrackingInfo entries, for occasional cleanup.
- L159 _public member_ `const void* Key = nullptr;` — The 'RPCTracking' map key for this entry (UFunction pointer, which may not point to a valid UFunction, hence void*)
- L162 _public member_ `const FRPCTrackingInfo* TrackingInfo = nullptr;` — Direct pointer to the RPC tracking info, for checking if it's expired

#### struct `FRPCDoSState`  
`struct FRPCDoSState`  
_L170-289_
- reflection: `USTRUCT()`
- desc: Stores the RPC DoS detection state (either settings from the config file, or the active DDoS detection state)
- L176 _public member_ `bool bLogEscalate = false;` — `UPROPERTY(config)` — Whether or not to log when escalating to this state
- L180 _public member_ `bool bSendEscalateAnalytics = false;` — `UPROPERTY(config)` — Whether or not to send analytics when escalating to this state
- L184 _public member_ `bool bKickPlayer = false;` — `UPROPERTY(config)` — Whether or not to kick the player when they escalate to this state
- L188 _public member_ `bool bTrackRecentRPCs = false;` — `UPROPERTY(config)` — Whether or not to keep a temporary record of recent RPC's, for potential logging/analytics
- L195 _public member_ `int16 EscalateQuotaRPCsPerFrame = -1;` — `UPROPERTY(config)` — The number of RPC's per frame before the next stage of DoS detection is triggered
- L199 _public member_ `int16 EscalateTimeQuotaMSPerFrame = -1;` — `UPROPERTY(config)` — The amount of time spent executing RPC's per frame, before the next stage of DoS detection is triggered
- L203 _public member_ `int16 EscalateQuotaRPCsPerPeriod = -1;` — `UPROPERTY(config)` — The number of RPC's per EscalateQuotaPeriod before the next stage of DoS detection is triggered
- L207 _public member_ `int16 EscalateTimeQuotaMSPerPeriod = -1;` — `UPROPERTY(config)` — The amount of time spent executing RPC's per EscalateQuotaPeriod, before the next stage of DoS detection is triggered
- L211 _public member_ `int8 EscalateQuotaTimePeriod = -1;` — `UPROPERTY(config)` — The time period to use for determining RPC count and time escalation quotas (Max: 16)
- L218 _public member_ `int8 EscalationCountTolerance = 1;` — `UPROPERTY(config)` — The number of times this stage must be escalated to, before it is 'confirmed' as having been escalated to (for analytics)
- L222 _public member_ `int16 EscalationTimeToleranceMS = -1;` — `UPROPERTY(config)` — The maximum time spent executing RPC's per frame, before this escalation stage is automatically 'confirmed' for analytics
- L229 _public member_ `int16 RPCRepeatLimitPerPeriod = -1;` — `UPROPERTY(config)` — The limit for the number of times a single RPC can be repeated, over the time period specified by RPCRepeatTimeLimitPeriod
- L233 _public member_ `int16 RPCRepeatLimitMSPerPeriod = -1;` — `UPROPERTY(config)` — The limit for the number of milliseconds a single RPC can spend executing, over the time period specified by RPCRepeatTimeLimitPeriod
- L237 _public member_ `int8 RPCRepeatLimitTimePeriod = -1;` — `UPROPERTY(config)` — The time period to use for measuring excessive execution time for a single RPC (Max: 16)
- L242 _public member_ `int16 CooloffTime = -1;` — `UPROPERTY(config)` — The amount of time, in seconds, before the current DoS severity category cools off and de-escalates
- L246 _public member_ `int16 AutoEscalateTime = -1;` — `UPROPERTY(config)` — The amount of time, in seconds, spent in the current DoS severity category before it automatically escalates to the next category
- L252 _public member_ `double EscalateTimeQuotaSecsPerFrame = 0.0;` — EscalateTimeQuotaMSPerFrame converted to seconds
- L255 _public member_ `double EscalateTimeQuotaSecsPerPeriod = 0.0;` — EscalateTimeQuotaMSPerPeriod converted to seconds
- L258 _public member_ `double RPCRepeatLimitSecsPerPeriod = 0.0;` — RPCRepeatLimitMSPerPeriod converted to seconds
- L261 _public member_ `double EscalationTimeToleranceSeconds = 0.0;` — EscalationTimeToleranceMS converted to seconds
- L265 _public prototype_ `virtual ~FRPCDoSState() = default;`
- L270 _public prototype_ `virtual void ApplyImpliedValues();` — Some configuration values are implicitly enabled by other configuration values - this function applies them
- L279 _public prototype_ `bool HasHitQuota_Count(const FRPCDoSCounters(&PerPeriodHistory)[16], FRPCDoSCounters& InFrameCounter) const;` — Whether or not the specified per-period counters have hit count escalation quota's specified by this state. @param PerPeriodHistory		The per-period historical counters being compared against @param InFrameCounter		The current frames counter for factoring-in to comparisons @return						Whether or not the count escalation quota has been hit
- L288 _public prototype_ `bool HasHitQuota_Time(const FRPCDoSCounters(&PerPeriodHistory)[16], FRPCDoSCounters& InFrameCounter) const;` — Whether or not the specified per-period counters have hit time escalation quota's specified by this state. @param PerPeriodHistory		The per-period historical counters being compared against @param InFrameCounter		The current frames counter for factoring-in to comparisons @return						Whether or not the time escalation quota has been hit

#### struct `FRPCDoSStateConfig`  
`struct FRPCDoSStateConfig : public FRPCDoSState`  
_L295-362_
- reflection: `USTRUCT()`
- inherits: `FRPCDoSState`
- desc: Configuration for RPC DoS Detection states
- L300 _public member_ `FString SeverityCategory;` — The name of the RPC DoS severity level this config section represents
- L307 _private member_ `int8 HighestTimePeriod = 0;` — Cached value for the highest time period in this config state
- L310 _private member_ `TArray<int8> AllTimePeriods;` — Cached value for all different time periods in this state
- L317 _public member_ `bool bEscalationConfirmed = false;` — Whether or not reaching this escalation stage has been 'confirmed' for analytics
- L320 _public member_ `int16 EscalationCount = 0;` — The number of times this stage has been escalated to
- L324 _public prototype_ `virtual void ApplyImpliedValues() override;`
- L334 _public prototype_ `bool LoadStructConfig(const TCHAR* SectionName, const TCHAR* InFilename=nullptr);` — Uses reflection to load all struct config variables from the specified ini section. NOTE: Reflection does not work with multiple inheritance. @param SectionName	The ini section name containing the struct configuration @param InFilename	The ini filename to read from @return				Whether or not the struct config variables were read successfully
- L339 _public prototype_ `void ValidateConfig();` — Validates loaded struct config variables
- L346 _public prototype_ `int8 GetHighestTimePeriod() const;` — Gets the highest counter time period specified by RPC DoS state settings (used for limiting 'CounterPerPeriodHistory' size) @return		The highest counter time period in the state config settings
- L353 _public prototype_ `const TArray<int8>& GetAllTimePeriods() const;` — Gets all counter time periods specified by the RPC DoS state settings @return		All of the time periods in the state config settings
- L361 _public prototype_ `void ApplyState(FRPCDoSState& Target);` — Applies the loaded config state, to an object implementing RPC DoS State's. NOTE: Does not use reflection, as this does not work with multiple inheritance. @param Target	The object implementing FRPCDoSState, to apply the config settings to.

#### enum `ERPCNotifyResult`  
`enum class ERPCNotifyResult : uint8`  
_L369-373_
- desc: Result of NotifyReceivedRPC, for specifying whether the RPC should execute or should be blocked
- L371 _public enumerator_ `ExecuteRPC` — Allow the RPC to execute
- L372 _public enumerator_ `BlockRPC` — Block the RPC from executing

#### enum `ERPCDoSSeverityUpdate`  
`enum class ERPCDoSSeverityUpdate : uint8`  
_L378-383_
- desc: RPC DoS escalation severity update types
- L380 _public enumerator_ `Escalate` — Escalating to a higher RPC DoS escalation state
- L381 _public enumerator_ `AutoEscalate` — Automatic/non-RPC escalation to a higher RPC DoS escalation state, e.g. when too much time was spent in a lower state
- L382 _public enumerator_ `Deescalate` — Deescalating to a lower RPC DoS escalation state

#### enum `ERPCDoSEscalateReason`  
`enum class ERPCDoSEscalateReason : uint8`  
_L388-394_
- desc: The reason for an RPC DoS severity update
- L390 _public enumerator_ `CountLimit` — RPC Count quota's were hit
- L391 _public enumerator_ `TimeLimit` — RPC Time quota's were hit
- L392 _public enumerator_ `AutoEscalate` — Automatic escalation from a lower state, e.g. after spending too much time in a lower state
- L393 _public enumerator_ `Deescalate` — Deescalation to a lower state

#### enum `EPostSequentialRPCType`  
`enum class EPostSequentialRPCType : uint8`  
_L399-403_
- desc: The type of a call to PostSequentialRPC
- L401 _public enumerator_ `MidPacket` — End of RPC sequence while still processing packet
- L402 _public enumerator_ `PostPacket` — End of RPC sequence after a packet has finished processing

#### class `FRPCDoSDetection`  
`class FRPCDoSDetection : protected FRPCDoSState`  
_L416-1275_
- inherits: `FRPCDoSState`
- desc: RPC DoS detection Implements DoS detection for NetConnection RPC's, using an escalating series of detection states depending on the severity of the DoS, to prevent false positives and minimize any performance impact. RPC's are profiled based on count and execution time, with careful implementation of tracking to balance lookup speed, memory usage, timing, and analytics tracking.
- L456 _public prototype_ `void Init(FName NetDriverName, TSharedPtr<FNetAnalyticsAggregator>& AnalyticsAggregator, TSharedPtr<FRPCDoSAnalyticsSender> AnalyticsSender, FGetRPCDoSAddress&& InAddressFunc, FGetRPCDoSPlayerUID&& InPlayerUIDFunc, FRPCDoSKickPlayer&& InKickPlayerFunc);` — Initialize RPC DoS Detection, inputting callbacks for retrieving external information necessary for analytics. @param NetDriverName			The name of the NetDriver which RPC DoS Detection belongs to (e.g. GameNetDriver) @param AnalyticsAggregator	Reference to the NetDriver analytics aggregator @param AnalyticsSender		Reference to the Engine implementation of RPC DoS Analytics sending @param InAddressFunc			Callback for getting the current NetConnection address. @param InPlayerUIDFunc		Callback for getting the current NetConnection player UID. @param InKickPlayerFunc		Callback for kicking the player after a bad enough RPC DoS.
- L464 _public prototype_ `void InitConfig(FName NetDriverName);` — Initializes configuration settings for RPC DoS Detection - with support for hot reloading @param NetDriverName		The name of the NetDriver which RPC DoS Detection belongs to (e.g. GameNetDriver)
- L472 _public prototype_ `void PreTickDispatch(double TimeSeconds);` — Called prior to the packet-loop TickDispatch @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L479 _public function_ `void PreReceivedPacket(double TimeSeconds)` — Called prior to the current NetConnection receiving a packet. @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L512 _public function_ `ERPCNotifyResult NotifyReceivedRPC(UObject* Object, const UFunction* Function, FName FunctionName)` — If RPC monitoring is enabled, provides a notification for every RPC that is received, with the ability to block it. @param Object			The UObject the RPC will be called on @param Function			The UFunction representing the RPC @param FunctionName		The cached name of the function @return					Whether or not to block the RPC
- L553 _public function_ `void LightweightReceivedRPC(const UFunction* Function, FName FunctionName)` — If RPC monitoring is disabled, does extremely lightweight tracking of RPC calls, for monitoring tracking triggers, and to allow a chance for deducing full RPC tracking information if monitoring is enabled while receiving (so that e.g. if an RPC DoS attack enables monitoring, information on the RPC responsible can be recovered). @param Function			The UFunction representing the RPC @param FunctionName		The cached name of the function
- L585 _public function_ `void PostReceivedRPC()` — Called after the current NetConnection receives an RPC.
- L624 _public prototype_ `void PostSequentialRPC(EPostSequentialRPCType SequenceType, double TimeSeconds, FRPCDoSCounters* RPCCounter, FRPCTrackingInfo* RPCTrackingInfo);` — Called after the same RPC was received once or multiple times sequentially, for optimal timing @param SequenceType		The type of sequential RPC call (a sequence stopping mid-packet, or at the end of the packet) @param TimeSeconds		The current time, in seconds (may be approximate) @param RPCCounter		Cached pointer to the currently active counter, for this RPC @param RPCTrackingInfo	Cached pointer to the tracking info, for this RPC
- L632 _public function_ `void PostReceivedPacket(double TimeSeconds)` — Called after the current NetConnection receives a packet. @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L661 _public prototype_ `void PostReceivedRPCPacket(double TimeSeconds);` — Called after the current NetConnection receives a packet, when RPC DoS Detection is active and the packet contains an RPC. NOTE: Timing is approximate - may include multiple-RPC and non-RPC packet processing time - but low cost @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L666 _public prototype_ `void PostTickDispatch();` — Called after the packet-loop TickDispatch
- L671 _public prototype_ `void NotifyClose();` — Triggered upon NetConnection Close (for committing analytics)
- L680 _public prototype_ `void TrackBlockedRPC(FName RPCName);` — Tracks a blocked RPC for aggregated logging. Below the log threshold, logs individually. Above the threshold, accumulates counts for per-tick aggregated logging. @param RPCName	The name of the RPC that was blocked
- L688 _public function_ `bool ShouldMonitorReceivedRPC() const` — Whether or not monitoring of received RPC's (i.e. calling of NotifyReceivedRPC) should be performed @return		Whether or not to monitor received RPC's.
- L700 _public function_ `bool IsRPCDoSDetectionEnabled() const` — Whether or not RPC DoS Detection is enabled
- L710 _public prototype_ `void SetAddressFunc(FGetRPCDoSAddress&& InAddressFunc);` — Overrides the current AddressFunc @param InAddressFunc		The new AddressFunc
- L717 _public prototype_ `void SetPlayerUIDFunc(FGetRPCDoSPlayerUID&& InPlayerUIDFunc);` — Overrides the current PlayerUIDFunc @param InPlayerUIDFunc	The new PlayerUIDFunc
- L724 _public prototype_ `void SetKickPlayerFunc(FRPCDoSKickPlayer&& InKickPlayerFunc);` — Overrides the current KickPlayerFunc @param InKickPlayerFunc	The new KickPlayerFunc
- L731 _private function_ `void PreSequentialRPC()` — Called when we begin receiving the same RPC once or multiple times sequentially.
- L749 _private prototype_ `void UpdateSeverity_Private(ERPCDoSSeverityUpdate Update, ERPCDoSEscalateReason Reason);` — Updates the current RPC DoS detection severity state @param Update	Whether or not we are escalating or de-escalating the severity state @param Reason	The reason for the escalation change
- L756 _private prototype_ `void InitState(double TimeSeconds);` — Initializes a newly active escalation state @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L761 _private function_ `void CondCheckCountQuota()` — Heavily rate limited RPC count quota checks
- L780 _private function_ `void CondCheckTimeQuota(double TimeSeconds)` — Heavily rate limited RPC time quota checks @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L803 _private prototype_ `ERPCNotifyResult CheckRPCTracking(const UFunction* Function, FName FunctionName);` — When RPC monitoring and tracking are enabled, tracks every RPC received. WARNING: Potentially expensive! RPC DoS Detection should be configured, so that tracking is rarely enabled. @param Function			The UFunction representing the RPC @param FunctionName		The cached name of the function @return					Whether or not to block the RPC
- L812 _private prototype_ `void RecalculatePeriodHistory(const TArray<int8>& InTimePeriods, FRPCDoSCounters(&OutPerPeriodHistory)[16], int32 StartPerSecHistoryIdx=INDEX_NONE);` — Recalculates cached RPC counter history information, after an interval or state change which affects time period tracking. @param InTimePeriods				The time period values which need caching (e.g. a period of 2 seconds, and a period of 8 seconds). @param OutPerPeriodHistory		Outputs the recalculated RPC counter cache, for the specified time periods (e.g. elements 1 and 7 only). @param StartPerSecHistoryIdx		The index in CounterPerSecHistory to start calculating from
- L821 _private prototype_ `void EnableRPCTracking(double TimeSeconds);` — Enables tracking of individual RPC's. @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L830 _private prototype_ `void EnableForcedRPCTracking(const UFunction* Function, FName FunctionName, double TimeSeconds);` — Enables forced tracking of individual RPC's @param Function		The function which triggered forced RPC tracking @param FunctionName	The name of the function which triggered forced RPC tracking @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L837 _private prototype_ `void DisableRPCTracking(double TimeSeconds);` — Disables tracking of individual RPC's. @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L846 _private function_ `FRPCTrackingInfo& FindOrAddRPCTracking(const UFunction* InFunc, bool& bOutNewTracking)` — Adds or retrieves the specified RPC from tracking @param InFunc			The RPC UFunction for tracking @param bOutNewTracking	Whether or not the RPC was newly added to tracking @return					Returns the RPC tracking info
- L867 _private prototype_ `void ClearStaleRPCTracking(double TimeSeconds);` — Used to periodically clear stale RPC tracking. @param TimeSeconds	Cached/approximate timestamp, to save grabbing a new timestamp
- L873 _private prototype_ `void CachePlayerAddress();` — Caches the player address, based on AddressFunc
- L878 _private prototype_ `void CachePlayerUID();` — Caches the player UID, based on PlayerUIDFunc
- L885 _private function_ `const FString& GetPlayerAddress()` — Returns the net address for the owning NetConnection. @return	The net address for the owning connection.
- L895 _private function_ `const FString& GetPlayerUID()` — Returns the unique id for the owning player. @return	The unique id for the owning player.
- L971 _private member_ `FTickScope TickScopePrivate;` — Scoped variables/functions accessible during TickDispatch
- L975 _private function_ `inline FTickScope& GetTickScope()` — Gets a reference to the TickDispatch scoped variable/function accessor
- L1007 _private member_ `FPacketScope PacketScopePrivate;` — Scoped variables/functions accessible while receiving an individual packet
- L1011 _private function_ `inline FPacketScope& GetPacketScope()` — Gets a reference to the packet receive scoped variable/function accessor
- L1103 _private member_ `FSequentialRPCScope SequentialRPCScopePrivate;` — Scoped variables/functions accessible while receiving the same RPC individually/sequentially
- L1106 _private function_ `inline FSequentialRPCScope& GetSequentialRPCScope()` — Gets a reference to the sequential RPC scoped variable/function accessor
- L1120 _private member_ `bool bRPCDoSDetection = false;` — Whether or not RPC DoS detection is presently enabled
- L1123 _private member_ `bool bRPCDoSAnalytics = false;` — Whether or not analytics for RPC DoS detection is enabled
- L1126 _private member_ `int32 HitchTimeQuotaMS = 0;` — The amount of time since the previous frame, for detecting hitches, to prevent false positives from built-up packets
- L1129 _private member_ `int32 HitchSuspendDetectionTimeMS = 0;` — The amount of time to suspend RPC DoS Detection, once a hitch is encountered, to prevent false positives from built-up packets
- L1132 _private member_ `TArray<FName> RPCBlockAllowList;` — List of RPC's which should never be blocked
- L1135 _private member_ `FName ForcedRPCTracking;` — If the related CVar is set, the name of the RPC which should forcibly enable tracking.
- L1138 _private member_ `double ForcedRPCTrackingChance = 1.0;` — Specifies the chance (between 0.0 and 1.0) that tracking will be enabled, when encountering the ForcedRPCTracking RPC
- L1141 _private member_ `double ForcedRPCTrackingLength = 0.0;` — Specifies the length of time forced RPC tracking should be enabled (disabled the next tick, if 0.0)
- L1144 _private member_ `double ForcedRPCTrackingEndTime = 0.0;` — Specifies the time at which forced RPC tracking should end, if tracking isn't enabled by the active state
- L1148 _private member_ `FGetRPCDoSAddress AddressFunc;` — Callback used for getting the address of the NetConnection the RPC DoS Detection is associated with
- L1151 _private member_ `FString CachedAddress;` — Player IP cached from AddressFunc
- L1154 _private member_ `FGetRPCDoSPlayerUID PlayerUIDFunc;` — Callback used for getting the unique id of the NetConnection the RPC DoS Detection is associated with
- L1157 _private member_ `FString CachedPlayerUID;` — Player UID cached from PlayerUIDFunc
- L1160 _private member_ `FRPCDoSKickPlayer KickPlayerFunc;` — Callback used for kicking the player after a bad enough RPC DoS
- L1164 _private member_ `TArray<FRPCDoSStateConfig> DetectionSeverity;` — The different RPC DoS detection states, of escalating severity, depending on the amount of RPC spam
- L1167 _private member_ `int8 ActiveState = 0;` — The currently active RPC DoS severity state settings
- L1170 _private member_ `int8 WorstActiveState = 0;` — The worst RPC DoS severity state that has been active
- L1173 _private member_ `int8 WorstAnalyticsState = 0;` — The worst RPC DoS severity state that has been active and passed confirmation thresholds - used for limiting analytics events
- L1176 _private member_ `double LastMetEscalationConditions = 0.0;` — The last time the previous severity states escalation conditions were met (to prevent bouncing up/down between states)
- L1179 _private member_ `bool bHitchSuspendDetection = false;` — Whether or not RPC DoS Detection has been suspended, due to a hitch impairing the accuracy of measurements
- L1182 _private member_ `double HitchSuspendDetectionStartTime = 0.0;` — Timestamp for when RPC DoS Detection was suspended, due to a hitch
- L1186 _private member_ `FRPCDoSCounters SecondCounter;` — Per-second RPC counting (approximate - may cover more than one second, in the case of expensive/long-running RPCs)
- L1189 _private member_ `double LastPerSecQuotaBegin = 0.0;` — Timestamp for the last time per-second quota counting began
- L1192 _private member_ `TArray<FRPCDoSCounters> CounterPerSecHistory;` — Stores enough per second quota history, to allow all DetectionSeverity states to recalculate if their CooloffTime is reached
- L1195 _private member_ `int32 LastCounterPerSecHistoryIdx = 0;` — The last written index of CounterPerSecHistory
- L1198 _private member_ `FRPCDoSCounters CounterPerPeriodHistory[16] = {};` — Counter history which is precalculated/cached from CounterPerSecHistory, for tracking per-period time (up to a maximum of 16s)
- L1201 _private member_ `uint8 SecondsIncrementer = 0;` — Wrapping count of seconds passed, for RPC tracking
- L1205 _private member_ `double ReceivedPacketEndTime = 0.0;` — Cached free/external timestamp, for when the last received packet finished processing
- L1208 _private member_ `double LastPreTickDispatchTime = 0.0;` — Cached PreTickDispatch timestamp, to reuse for minimizing timestamp retrieval
- L1211 _private member_ `uint32 RPCIntervalCounter = 0;` — Unbounded RPC counter, for performing RPC checks at every 'x' intervals
- L1214 _private member_ `double NextTimeQuotaCheck = 0.0;` — Timestamp for when time quota's should next be checked
- L1217 _private member_ `static constexpr double TimeQuotaCheckInterval = 0.005;` — Interval for time quota checks, in seconds
- L1221 _private member_ `bool bRPCTrackingEnabled = false;` — Whether or not RPC Tracking has been enabled by RPC DoS escalation or other checks
- L1224 _private member_ `int8 MaxRPCTrackingPeriod = 0;` — The runtime maximum number of seconds of RPC tracking that is used
- L1227 _private member_ `TMap<const void*, TSharedPtr<FRPCTrackingInfo>> RPCTracking;` — Maps UFunction pointers to live function tracking structs (NOTE: Treats the UFunction's as potentially invalid/GC'd, hence void*)
- L1230 _private member_ `TArray<FActiveRPCTrackingInfo> ActiveRPCTracking;` — Stores a reference to active/valid RPCTracking entries, for faster cleanup - as the above map stores values sparsely.
- L1233 _private member_ `static constexpr int32 DefaultActiveRPCTrackingSize = 128;` — Default size for ActiveRPCTracking, to minimize realloc
- L1236 _private member_ `double LastRPCTrackingClean = 0.0;` — The last time RPCTracking was cleaned out
- L1240 _private member_ `FRPCDoSAnalyticsVars AnalyticsVars;` — The locally cached/updated analytics variables, for the RPC DoS Detection - aggregated upon connection Close
- L1243 _private member_ `TNetAnalyticsDataPtr<FRPCDoSAnalyticsData> RPCDoSAnalyticsData;` — The net analytics data holder for the RPC DoS analytics, which is where analytics variables are aggregated upon Close
- L1246 _private member_ `double AnalyticsMinTimePerSecThreshold = 0.0;` — The minimum RPC time per second threshold, for doing analytics updates/checks
- L1249 _private member_ `double LastAnalyticsThresholdRecalc = 0.0;` — The last time the 'AnalyticsMinTimePerSecThreshold' was recalculated
- L1256 _private prototype_ `void FlushBlockedRPCLogs();` — Flushes aggregated blocked RPC log data. Called once per tick from PostTickDispatch. If the per-tick log threshold was reached, prints one aggregated log line and resets counts (not map keys).
- L1261 _private prototype_ `void ResetBlockedRPCTracking();` — Fully resets blocked RPC tracking state, including wiping the map. Called on cooldown/de-escalation.
- L1265 _private member_ `TMap<FName, int32> BlockedRPCCounts;` — Accumulated blocked RPC counts, keyed by RPC name. Counts reset per-tick on flush; map wiped on de-escalation.
- L1268 _private member_ `FName CachedBlockedRPCName;` — Cached RPC name for fast-path blocked RPC tracking (avoids map lookup when the same RPC is blocked repeatedly)
- L1271 _private member_ `int32* CachedBlockedRPCCount = nullptr;` — Cached pointer to the count in BlockedRPCCounts for CachedBlockedRPCName
- L1274 _private member_ `int32 BlockedRPCLogCounter = 0;` — Number of individual blocked RPC log messages emitted this tick

#### struct `FRPCDoSDetection::FLightweightRPCTracking`  
`struct FLightweightRPCTracking`  
_L423-443_
- desc: Lightweight RPC tracking state
- L426 _public member_ `static constexpr int32 TrackingNum = 256;` — The size of the tracking static arrays - must be 256 in case Count wraps (unlikely, but saves some checks)
- L439 _public member_ `FLightweightRPCEntry RPC[TrackingNum] = {};` — Static array of tracked RPC's
- L442 _public member_ `uint8 Count = 0;` — The number of tracked RPC's in the static array

#### struct `FRPCDoSDetection::FLightweightRPCTracking::FLightweightRPCEntry`  
`struct FLightweightRPCEntry`  
_L428-435_
- L431 _public member_ `const UFunction* Function;` — The function being tracked
- L434 _public member_ `FName Name;` — Name of the function being tracked

#### class `FRPCDoSDetection::TScopeBase`  
`template<class T> class TScopeBase`  
_L904-936_
- desc: Base class for setting code scope activity
- L908 _public function_ `inline void SetActive(bool bInVal)` — Sets whether or not the current code scope is active
- L922 _public function_ `inline bool IsActive() const` — Whether or not the current code scope is active
- L928 _public function_ `inline void Reset()` — Resets the properties covered by this scope, at both the start/end of the scope
- L935 _private member_ `bool bScopeActive = false;` — Whether or not the current code scope is active

#### class `FRPCDoSDetection::FTickScope`  
`class FTickScope : public TScopeBase<FTickScope>`  
_L939-968_
- inherits: `TScopeBase<FTickScope>`
- desc: Variables and functions that should only be accessible during TickDispatch
- L943 _public function_ `inline void UpdateSeverity(FRPCDoSDetection& This, ERPCDoSSeverityUpdate Update, ERPCDoSEscalateReason Reason)` — Wrapper for UpdateSeverity which forces FTickScope acquisition
- L949 _public function_ `inline void CondCheckCountQuota(FRPCDoSDetection& This)` — Wrapper for CondCheckCountQuota which forces FTickScope acquisition
- L955 _public function_ `inline void CondCheckTimeQuota(FRPCDoSDetection& This, double TimeSeconds)` — Wrapper for CondCheckTimeQuota which forces FTickScope acquisition
- L960 _public function_ `void Reset()`
- L967 _public member_ `FRPCDoSCounters FrameCounter;` — Per-frame RPC counting (multiple disjointed packets may be processed for same connection, during a frame)

#### class `FRPCDoSDetection::FPacketScope`  
`class FPacketScope : public TScopeBase<FPacketScope>`  
_L988-1004_
- inherits: `TScopeBase<FPacketScope>`
- desc: Variables and functions that should only be accessible while receiving an individual packet
- L992 _public member_ `bool bPacketContainsRPC = false;` — Whether or not the current packet being received, contains an RPC
- L995 _public member_ `double ReceivedPacketStartTime = 0.0;` — Cached free/external timestamp, for when the current received packet began processing
- L999 _public function_ `void Reset()`

#### class `FRPCDoSDetection::FSequentialRPCScope`  
`class FSequentialRPCScope : public TScopeBase<FSequentialRPCScope>`  
_L1023-1100_
- inherits: `TScopeBase<FSequentialRPCScope>`
- desc: Variables and functions that should only be accessible while receiving the same RPC individually/sequentially
- L1027 _public function_ `inline void CondCheckCountQuota(FRPCDoSDetection& This)` — Wrapper for CondCheckCountQuota which forces FSequentialRPCScope acquisition
- L1033 _public function_ `inline void CondCheckTimeQuota(FRPCDoSDetection& This, double TimeSeconds)` — Wrapper for CondCheckTimeQuota which forces FSequentialRPCScope acquisition
- L1039 _public function_ `inline ERPCNotifyResult CheckRPCTracking(FRPCDoSDetection& This, const UFunction* Function, FName FunctionName)` — Wrapper for CheckRPCTracking which forces FSequentialRPCScope acquisition
- L1045 _public function_ `inline FRPCTrackingInfo& FindOrAddRPCTracking(FRPCDoSDetection& This, const UFunction* InFunc, bool& bOutNewTracking)` — Wrapper for FindOrAddRPCTracking which forces FSequentialRPCScope acquisition
- L1050 _public function_ `void Reset()`
- L1069 _public member_ `bool bReceivedPacketRPCUnique = true;` — Whether or not the packet only contains references to the same unique RPC (may be multiple RPC calls to same RPC)
- L1072 _public member_ `int32 ReceivedPacketRPCCount = 0;` — Counts the number of RPC's in the current packet, for unique-RPC analytics
- L1075 _public member_ `FLightweightRPCTracking LightweightRPCTracking;` — State for lightweight tracking of RPC's
- L1079 _public member_ `FName PostReceivedRPCName;` — Temporarily caches the currently active RPC name, while processing a packet
- L1082 _public member_ `FRPCTrackingInfo* PostReceivedRPCTracking = nullptr;` — Temporarily caches the currently active RPC tracking, while processing a packet
- L1085 _public member_ `FRPCDoSCounters* PostReceivedRPCCounter = nullptr;` — Temporarily caches the currently active RPC counter, while processing a packet
- L1088 _public member_ `int32 PostReceivedRPCBlockCount = 0;` — Temporarily caches the number of blocked RPC calls for the current RPC, while processing a packet
- L1091 _public member_ `double LastReceivedRPCTimeCache = 0.0;` — Temporarily caches timestamps for sequentially executed RPC's, to minimize new timestamp generation.
- L1095 _public member_ `double DebugReceivedRPCStartTime = 0.0;` — Direct/accurate timestamp of RPC receive start time, for debugging against approximate RPC timestamps
- L1098 _public member_ `double DebugReceivedRPCEndTime = 0.0;` — Direct/accurate timestamp of RPC receive end time, for debugging against approximate RPC timestamps

#### Free symbols / members of external scopes

- L16 _macro_ `#define RPC_QUOTA_DEBUG 0` — Count/Time Quota debugging
- L19 _macro_ `#define RPC_DOS_DEV_STATS 0` — Whether or not CSV stats should be enabled for the RPC DoS checks (development only - for stress testing the RPC DoS code)
- L22 _macro_ `#define RPC_DOS_SCOPE_DEBUG 1` — Tick/Packet scope correctness debugging
- L32 _typedef_ `using FGetRPCDoSAddress = TUniqueFunction<FString()>;` — Callback usually passed in by the NetConnection, for getting the address of the owning connection @return	The address of the owning NetConnection
- L39 _typedef_ `using FGetRPCDoSPlayerUID = TUniqueFunction<FString()>;` — Callback usually passed in by the NetConnection, for getting the unique id of the owning player/connection @return	The unique id of the owning player/connection
- L44 _typedef_ `using FRPCDoSKickPlayer = TUniqueFunction<void()>;` — Callback usually passed in by the NetConection, for kicking the player after exceeding RPC DoS kick thresholds
- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace Net` (scope `UE`)
- L53 _externvar_ `extern int32 GRPCDoSScopeDebugging;` (scope `UE::Net`) — Whether or not debugging/ensures for RPC DoS Tick/Packet scopes should be enabled

### `Source/Runtime/Net/Core/Public/Net/Core/Connection/StateStruct.h` (Public)


#### enum `EInitStateDefaultsResult`  
`enum class EInitStateDefaultsResult : uint8`  
_L97-101_
- desc: The result of a call to InitConfigDefaults
- L99 _public enumerator_ `Initialized` — Default values have been set for the struct
- L100 _public enumerator_ `NotInitialized` — Default values have not been set for the struct

#### struct `FStateConfigParms`  
`struct FStateConfigParms`  
_L107-120_
- desc: Parameters for creating/getting and initializing a new UStatePerObjectConfig instance
- L110 _public member_ `const TCHAR* ConfigSection = nullptr;` — The base configuration section name to use (not the full/complete section name)
- L113 _public member_ `FString ConfigContext;` — Additional context for the configuration section (e.g. the NetDriver name, if configuration differs between NetDriver's)
- L116 _public member_ `UClass* ConfigClass = nullptr;` — The UStatePerObjectConfig subclass which will be created
- L119 _public member_ `UStruct* StateStruct = nullptr;` — The FStateStruct subclass struct object (StaticStruct), which will be used for initializing new states

#### struct `FStateStruct`  
`struct FStateStruct`  
_L127-195_
- reflection: `USTRUCT()`
- desc: Base struct used for states, which is subclassed to define/implement custom states.
- L138 _private member_ `FString StateName;` — `UPROPERTY()` — The name of the state this config section represents (valid/usable during InitConfigDefaults)
- L142 _public prototype_ `virtual ~FStateStruct() = default;`
- L149 _public prototype_ `FString GetStateName() const;` — Returns the name of this state @return	The name of this state
- L158 _private function_ `EInitStateDefaultsResult InitConfigDefaults()` — Initializes the default settings for this state. Overridden by config settings. @return	Whether or not default settings were set.
- L166 _private function_ `void ApplyImpliedValues()` — Some configuration values are implicitly enabled by other configuration values - this function applies them
- L174 _private function_ `void ValidateConfig()` — Validates loaded struct config variables
- L183 _protected function_ `virtual EInitStateDefaultsResult InitConfigDefaultsInternal()`
- L188 _protected function_ `virtual void ApplyImpliedValuesInternal()`
- L192 _protected function_ `virtual void ValidateConfigInternal()`

#### class `UStatePerObjectConfig`  
`class UStatePerObjectConfig : public UObject`  
_L202-325_
- reflection: `UCLASS(config=Engine, PerObjectConfig, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for loading and initializing state configuration
- L213 _public prototype_ `static const UStatePerObjectConfig* Get(FStateConfigParms ConfigParms);` — Singleton for getting a named instance of this config section/object @param ConfigParms	Specifies the parameters for the config section/object to get/create, and how it should be created @return				Returns a cached or newly created instance of the config section/object
- L222 _public prototype_ `static void ApplyState(const FStructOnScope& ConfigState, FStateStruct* TargetState);` — Applies the specified config state, to an object implementing FStateStruct's. NOTE: Reflection does not work with multiple inheritance. @param ConfigState	The configuration state containing the settings to be applied @param TargetState	The object implementing FStateStruct, to apply the config settings to.
- L229 _public prototype_ `virtual void DebugDump() const;` — Debug function which prints the entire state configuration to the log
- L242 _protected function_ `template<typename U, typename = typename TEnableIf<TIsDerivedFrom<U, FStateStruct>::IsDerived, void>::Type> void RegisterStateConfig(const TArray<FString>& StateNames, TArray<TStructOnScope<U>>& OutStates)` — Registers an array of state names to an array of state instances (of a type derived from FStateStruct). Should be called during LoadStateConfig in subclasses. @param StateNames	The (usually configurable) array of state names defining the state instances to be created @param OutStates		The array of state instances to be initialized based on StateNames
- L252 _private function_ `virtual void LoadStateConfig()` — Implement in subclasses to call RegisterStateConfig, in order to load states
- L259 _private function_ `void InitConfigDefaults()` — Initializes the default settings for this class. Overridden by config settings.
- L267 _private function_ `virtual void InitConfigDefaultsInternal()` — Implement in subclasses to initialize the default settings for this class. Overridden by config settings.
- L272 _private prototype_ `void RegisterStateConfig(const TArray<FString>& StateNames, TArray<TStructOnScope<FStateStruct>>& OutStates);`
- L274 _private prototype_ `virtual void OverridePerObjectConfigSection(FString& SectionName) override;`
- L285 _private prototype_ `static UStatePerObjectConfig* GetArchetype(FStateConfigParms ConfigParms, FString FullSection, FString FormattedName);` — Internal singleton for getting the custom archetype/default-object instance for a config section/object (to allow custom default values) @param ConfigParms		Specifies the parameters for the config section/object to get/create, and how it should be created @param FullSection		The full section name used by the config section/object @param FormattedName		The base formatted object name to use, for unique/singleton object lookup/caching @return					Returns a cached or newly created instance of the config section/object archetype
- L296 _private prototype_ `static bool LoadStructConfig(FStructOnScope& OutStruct, const TCHAR* SectionName, const TCHAR* InFilename=nullptr);` — Uses reflection to load all struct config variables from the specified ini section. NOTE: Reflection does not work with multiple inheritance. @param OutStruct		The struct to load the settings into @param SectionName	The ini section name containing the struct configuration @param InFilename	The ini filename to read from @return				Whether or not the struct config variables were read successfully
- L310 _private member_ `FStateConfigParms ConfigParms;` — Cached parameters that were used to create this instance
- L314 _private member_ `TArray<FStateConfigRegister> RegisteredStateConfigs;` — Stores a list of state name arrays registered to state instance arrays, to allow debug dumping of values
- L319 _private member_ `FString PerObjectConfigSection;` — `UPROPERTY()` — Overrides the config section name, using the CDO
- L324 _public member_ `bool bEnabled;` — `UPROPERTY(config)` — Whether or not this state configuration instance is enabled (states will not load, if not)

#### struct `UStatePerObjectConfig::FStateConfigRegister`  
`struct FStateConfigRegister`  
_L301-305_
- L303 _public member_ `const TArray<FString>& StateNames;`
- L304 _public member_ `TArray<TStructOnScope<FStateStruct>>& States;`

### `Source/Runtime/Net/Core/Public/Net/Core/DirtyNetObjectTracker/GlobalDirtyNetObjectTracker.h` (Public)


#### class `UE::Net::FGlobalDirtyNetObjectTracker`  
`class FGlobalDirtyNetObjectTracker`  
_L16-118_
- L49 _public typedef_ `using FDirtyPropertyStorage = TArray<FNetBitArrayBase::StorageWordType, TInlineAllocator<4>>;`
- L50 _public typedef_ `using FDirtyHandleAndPropertyMap = TMap<FNetHandle, FDirtyPropertyStorage>;`
- L54 _public prototype_ `static bool IsUsingPerPropertyDirtyTracking();` — Returns true if we are tracking dirtiness per property.
- L57 _public prototype_ `static void MarkNetObjectStateDirty(FNetHandle, const int32, const int32);` — Marks an object as dirty. Assumes Init() has been called.
- L60 _public function_ `inline static void MarkNetObjectStateDirty(FNetHandle Handle)` — Marks an object as dirty. Assumes Init() has been called.
- L66 _public prototype_ `DECLARE_DELEGATE(FPreResetDelegate);` — Delegate called on pollers that haven't gathered dirty state before it resets
- L69 _public prototype_ `static FPollHandle CreatePoller(FPreResetDelegate InPreResetDelegate);` — Create a poller which is assumed to call PollDirtyNetObjects(). Assumes Init() has been called.
- L76 _public prototype_ `static const TSet<FNetHandle>& GetDirtyNetObjects(const FPollHandle& Handle);` — Returns the objects with dirty state. The reference can only be assumed to be valid until the next call to ResetDirtyNetObjects(). A matching call to ResetDirtyNetObjects() is required but should not be called until all pollers have had the chance to call GetDirtyNetObjects(). Assumes Init() has been called.
- L83 _public prototype_ `static const FDirtyHandleAndPropertyMap& GetDirtyNetObjectsAndProperties(const FPollHandle& Handle);` — Returns the objects with dirty state including per property dirtiness. The reference can only be assumed to be valid until the next call to ResetDirtyNetObjects(). A matching call to ResetDirtyNetObjects() is required but should not be called until all pollers have had the chance to call GetDirtyNetObjects(). Assumes Init() has been called.
- L88 _public prototype_ `static void LockDirtyListUntilReset(const FPollHandle& Handle);` — Detect any updates to the dirty list until all pollers have gathered and reset the list.
- L95 _public prototype_ `static void ResetDirtyNetObjects(const FPollHandle&);` — Clears the set of dirty net objects. GetDirtyNetObjects() must be called first. Some synchronization is needed between pollers such that all pollers have the chance to call GetDirtyNetObjects() first. It may be a good idea to have the polling done in a NetDriver TickFlush() or similar and resetting done in PostTickFlush(). Assumes Init() has been called.
- L101 _public prototype_ `static bool ResetDirtyNetObjectsIfSinglePoller(const FPollHandle&);` — Reset the list of dirty net objects but only if there is a single poller registered in the system. Returns true if the reset was executed.
- L107 _protected prototype_ `static void Init();` — If push model is compiled in Init() creates a new instance that is used by functions that need it. Checks that no instance exists.
- L110 _protected prototype_ `static void Deinit();` — Destroys the instance if it exists.
- L114 _private prototype_ `static void DestroyPoller(uint32 HandleIndex);` — Called by NetPollHandle destructor.
- L117 _private member_ `static FPimpl* Instance;`

#### struct `UE::Net::FGlobalDirtyNetObjectTracker::FPollHandle`  
`struct FPollHandle`  
_L19-47_
- L22 _public prototype_ `FPollHandle() = default;`
- L23 _public prototype_ `FPollHandle(FPollHandle&&);`
- L24 _public prototype_ `~FPollHandle();`
- L26 _public prototype_ `FPollHandle& operator=(FPollHandle&&);`
- L28 _public prototype_ `FPollHandle(const FPollHandle&) = delete;`
- L29 _public prototype_ `FPollHandle& operator=(const FPollHandle&) = delete;`
- L31 _public prototype_ `bool IsValid() const;`
- L34 _public prototype_ `void Destroy();` — Destroy the handle, making it invalid in the process.
- L44 _private prototype_ `explicit FPollHandle(uint32 InIndex);`
- L46 _private member_ `uint32 Index = InvalidIndex;`
- L130 _function_ `inline FGlobalDirtyNetObjectTracker::FPollHandle::FPollHandle(uint32 InIndex) : Index(InIndex)`
- L135 _function_ `inline FGlobalDirtyNetObjectTracker::FPollHandle::FPollHandle(FPollHandle&& Other)`
- L141 _function_ `inline FGlobalDirtyNetObjectTracker::FPollHandle& FGlobalDirtyNetObjectTracker::FPollHandle::operator=(FPollHandle&& Other)`
- L154 _function_ `inline FGlobalDirtyNetObjectTracker::FPollHandle::~FPollHandle()`
- L159 _function_ `inline bool FGlobalDirtyNetObjectTracker::FPollHandle::IsValid() const`
- L164 _function_ `inline void FGlobalDirtyNetObjectTracker::FPollHandle::Destroy()`

#### enum `UE::Net::FGlobalDirtyNetObjectTracker::FPollHandle::(anonymous)`  
``  
_L40-42_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Net` (scope `UE`)
- L14 _prototype_ `void MarkNetObjectStateDirty(FNetHandle NetHandle, int32 StartRepIndex, int32 EndRepIndex);` (scope `UE::Net`)
- L41 _enumerator_ `InvalidIndex = ~0U` (scope `UE::Net::FGlobalDirtyNetObjectTracker::FPollHandle::__anondd6b52b50103`)
- L66 _delegate_ `DECLARE_DELEGATE(FPreResetDelegate);` — Delegate called on pollers that haven't gathered dirty state before it resets
- L120 _function_ `inline void MarkNetObjectStateDirty(FNetHandle NetHandle)` (scope `UE::Net`)
- L125 _function_ `inline void MarkNetObjectStateDirty(FNetHandle NetHandle, int32 StartRepIndex, int32 EndRepIndex)` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/DDoSDetection.h` (Public)


#### struct `FDDoSPacketCounters`  
`struct FDDoSPacketCounters`  
_L25-59_
- desc: Struct containing the per-second packet counters
- L28 _public member_ `int32 NonConnPacketCounter;` — Counter for non-NetConnection packets received, since the last per second quota period began
- L31 _public member_ `int32 NetConnPacketCounter;` — Counter for NetConnection packets received, since the last per second quota period began
- L34 _public member_ `int32 DisconnPacketCounter;` — Counter for recently-disconnected NetConnection packets received, since the last per second quota period beegan
- L37 _public member_ `int32 BadPacketCounter;` — Counter for bad non-NetConnection packets received, since the last per second quota period began
- L40 _public member_ `int32 ErrorPacketCounter;` — Counter for non-DDoS packet errors received
- L43 _public member_ `int32 DroppedPacketCounter;` — Counter for the number of packets (of any type) dropped, since the last per second quota period began
- L46 _public member_ `int32 WorstFrameReceiveTimeMS;` — The worst per-frame packet receive time in milliseconds, over the ~1 second this packet counter history represents
- L49 _public function_ `FDDoSPacketCounters() : NonConnPacketCounter(0) , NetConnPacketCounter(0) , DisconnPacketCounter(0) , BadPacketCounter(0) , ErrorPacketCounter(0) , DroppedPacketCounter(0) , WorstFrameReceiveTimeMS(0)`

#### struct `FDDoSState`  
`struct FDDoSState`  
_L65-124_
- desc: Stores the DDoS detection state (either settings from the config file, or the active DDoS detection state)
- L68 _public member_ `bool bSendEscalateAnalytics;` — Whether or not to send analytics when escalating to this state
- L71 _public member_ `int32 EscalateQuotaPacketsPerSec;` — The number of packets/sec before the next stage of DDoS detection is triggered
- L74 _public member_ `int32 EscalateQuotaDisconnPacketsPerSec;` — The number of recently disconnected NetConnection packets/sec, before the next stage of DDoS detection is triggered.
- L77 _public member_ `int32 EscalateQuotaBadPacketsPerSec;` — The number of bad (failed to process correctly) packets/sec, before the next stage of DDoS detection is triggered
- L80 _public member_ `int16 EscalateTimeQuotaMSPerFrame;` — The amount of time spent processing packets, before the next stage of DDoS detection is triggered
- L83 _public member_ `int32 PacketLimitPerFrame;` — The limit for the number of non-NetConnection packets to process, each frame
- L86 _public member_ `int32 PacketTimeLimitMSPerFrame;` — The limit for time spent processing non-NetConnection packets, each frame (counts all packets time, non-NetConn and NetConn)
- L89 _public member_ `int32 NetConnPacketTimeLimitMSPerFrame;` — The limit for time spent processing NetConnection packets, each frame (counts all packets time, non-NetConn and NetConn)
- L92 _public member_ `int32 CooloffTime;` — The amount of time, in seconds, before the current DDoS severity category cools off and de-escalates
- L95 _public function_ `FDDoSState() : bSendEscalateAnalytics(true) , EscalateQuotaPacketsPerSec(-1) , EscalateQuotaDisconnPacketsPerSec(-1) , EscalateQuotaBadPacketsPerSec(-1) , EscalateTimeQuotaMSPerFrame(-1) , PacketLimitPerFrame(-1) , PacketTimeLimitMSPerFrame(-1) , NetConnPacketTimeLimitMSPerFrame(-1) , CooloffTime(-1)`
- L115 _public function_ `bool HasHitQuota(FDDoSPacketCounters& InCounter, int32 TimePassedMS) const` — Whether or not the specified counters and time passed has hit any of the quota's @param InCounter		The counters to check against @param TimePassedMS	The amount of time passed in milliseconds, since the beginning of this state @return				Whether or not the quota was hit

#### struct `FDDoSStateConfig`  
`struct FDDoSStateConfig : public FDDoSState`  
_L129-165_
- inherits: `FDDoSState`
- desc: DDoS detection state, with functions for applying the state to active DDoS detection
- L132 _public member_ `FString SeverityCategory;` — The name of the DDoS severity level this config section represents
- L135 _public function_ `FDDoSStateConfig() : SeverityCategory(TEXT(""))`
- L140 _public function_ `void ApplyState(FDDoSState& Target)`
- L157 _public function_ `void ApplyAdjustedState(FDDoSState& Target, float FrameAdjustment)` — Applies only the per-frame adjusted state (based on expected vs actual framerate), to active DDoS protection. ApplyState should be called, first.

#### class `FDDoSDetection`  
`class FDDoSDetection : protected FDDoSPacketCounters, protected FDDoSState`  
_L172-371_
- inherits: `FDDoSPacketCounters,FDDoSState`
- desc: The main DDoS detection tracking class, for counting packets and applying restrictions. Implemented separate to the NetDriver, to allow wider use e.g. potentially at socket level, if useful.
- L178 _public prototype_ `FDDoSDetection();` — Default constructor
- L186 _public prototype_ `void Init(int32 MaxTickRate);` — Initializes the DDoS detection settings @param MaxTickRate	The maximum tick rate of the server
- L191 _public prototype_ `void InitConfig();` — Initializes the settings from the .ini file - must support reloading of settings on-the-fly
- L196 _public prototype_ `void SetMaxTickRate(int32 MaxTickRate);` — Initialize the expected tick rate.
- L203 _public prototype_ `void UpdateSeverity(bool bEscalate);` — Updates the current DDoS detection severity state @param bEscalate		Whether or not we are escalating or de-escalating the severity state
- L209 _public prototype_ `void PreFrameReceive(float DeltaTime);` — Triggered before packet receive begins, during the current frame
- L214 _public prototype_ `void PostFrameReceive();` — Triggered after packet receive ends, during the current frame
- L220 _public function_ `void CondCheckNonConnQuotasAndLimits()` — Rate limited call to CheckNonConnQuotasAndLimits
- L232 _public function_ `void CondCheckNetConnLimits()` — Rate limited call to CheckNetConnLimits
- L245 _public function_ `bool CheckLogRestrictions()` — Accessor for bDDoSLogRestrictions - doubles as a per-frame logspam counter, automatically disabling logs after a quota
- L253 _public function_ `bool IsDDoSDetectionEnabled() const`
- L254 _public function_ `bool IsDDoSAnalyticsEnabled() const`
- L255 _public function_ `bool ShouldBlockNonConnPackets() const`
- L256 _public function_ `bool ShouldBlockNetConnPackets() const`
- L258 _public function_ `void IncNonConnPacketCounter()`
- L259 _public function_ `int32 GetNonConnPacketCounter() const`
- L260 _public function_ `void IncNetConnPacketCounter()`
- L261 _public function_ `int32 GetNetConnPacketCounter() const`
- L262 _public function_ `void IncDisconnPacketCounter()`
- L263 _public function_ `int32 GetDisconnPacketCounter() const`
- L264 _public function_ `void IncBadPacketCounter()`
- L265 _public function_ `int32 GetBadPacketCounter() const`
- L266 _public function_ `void IncErrorPacketCounter()`
- L267 _public function_ `int32 GetErrorPacketCounter() const`
- L268 _public function_ `void IncDroppedPacketCounter(int32 Count=1)`
- L269 _public function_ `int32 GetDroppedPacketCounter() const`
- L277 _protected prototype_ `bool CheckNonConnQuotasAndLimits();` — Performs periodic checks on trigger quota's and packet limits, for non-NetConnection packets @return	Whether or not non-NetConnection packet limits have been reached
- L284 _protected function_ `bool CheckNetConnLimits()` — Performs periodic checks on NetConnection packet limits @return	Whether or not NetColnnection packet limits have been reached
- L294 _protected member_ `bool bDDoSDetection;` — Whether or not DDoS detection is presently enabled
- L297 _protected member_ `bool bDDoSAnalytics;` — Whether or not analytics for DDoS detection is enabled
- L300 _protected member_ `bool bHitFrameNonConnLimit;` — Whether or not the current frame has reached non-NetConnection packet limits, and should block non-NetConnection packets
- L303 _protected member_ `bool bHitFrameNetConnLimit;` — Whether or not the current frame has reached NetConnection packet limits, and should block ALL further packets
- L307 _protected member_ `TArray<FDDoSStateConfig> DetectionSeverity;` — The different DDoS detection states, of escalating severity, depending on the strength of the DDoS
- L310 _protected member_ `int8 ActiveState;` — The currently active DDoS severity state settings
- L313 _protected member_ `int8 WorstActiveState;` — The worst DDoS severity state that has been active - used for limiting analytics events
- L316 _protected member_ `double LastMetEscalationConditions;` — The last time the previous severity states escalation conditions were met (to prevent bouncing up/down between states)
- L319 _protected member_ `bool bMetEscalationConditionsThisFrame;` — Limit checking previous states escalation conditions to once per frame
- L323 _protected member_ `bool bDDoSLogRestrictions;` — Whether or not restriction of log messages from non-NetConnection packets is enabled
- L326 _protected member_ `int32 DDoSLogSpamLimit;` — The maximum number of non-NetConnection triggered log messages per frame, before further logs are dropped this frame
- L329 _protected member_ `int32 LogHitCounter;` — Counter for log restriction hits, in the current frame
- L333 _protected member_ `int32 HitchTimeQuotaMS;` — The amount of time since the previous frame, for detecting frame hitches, to prevent DDoS detection false positives
- L336 _protected member_ `int8 HitchFrameTolerance;` — The number of frames spent hitching, before disabling false positive detection, and treating packet buildup as potential DDoS
- L339 _protected member_ `int32 HitchFrameCount;` — The number of consecutive frames spent hitching
- L343 _protected member_ `double LastPerSecQuotaBegin;` — Timestamp for the last time per-second quota counting began
- L346 _protected member_ `TArray<FDDoSPacketCounters> CounterPerSecHistory;` — Stores enough per second quota history, to allow all DetectionSeverity states to recalculate if their CooloffTime is reached
- L349 _protected member_ `int32 LastCounterPerSecHistoryIdx;` — The last written index of CounterPerSecHistory
- L353 _protected member_ `double StartFrameRecvTimestamp;` — The timestamp for the start of the current frames receive
- L356 _protected member_ `double EndFrameRecvTimestamp;` — Timestamp for the end of the last frames receive loop
- L359 _protected member_ `int32 StartFramePacketCount;` — Counts the packets from the start of the current frame
- L362 _protected member_ `double ExpectedFrameTime;` — The expected time between frames (1.0 / MaxTickRate) - used for adjusting limits/quota's based on DeltaTime
- L365 _protected member_ `float FrameAdjustment;` — The current frames adjustment/deviation, from ExpectedFrameTime
- L370 _public member_ `FDDoSSeverityEscalation NotifySeverityEscalation;` — Analytics delegate for notifying of severity state escalations

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FDDoSSeverityEscalation, FString );` — Delegate for allowing analytics to receive notification of detected DDoS attacks
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FDDoSSeverityEscalation, FString );` — Delegate for allowing analytics to receive notification of detected DDoS attacks

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/GuidReferences.h` (Public)


#### class `FGuidReferences`  
`class FGuidReferences`  
_L49-143_
- desc: References to Objects (including Actors, Components, etc.) are replicated as NetGUIDs, since the literal memory pointers will be different across game instances. In these cases, actual replicated data for the Object will be handled elsewhere (either on its own Actor channel, or on its Owning Actor's channel, as a replicated subobject). As Objects are replicated and received, these GUID References will become "mapped", and the networking system will update the corresponding properties with pointers to the appropriate objects. As Objects are destroyed (due to game play, actor channels closing, relevancy, etc.), GUID References will be "unmapped", and their corresponding properties will nulled out. The process of Mapping and Unmapping can happen numerous times for the same object (e.g., if an Actor goes in and out of relevancy repeatedly). This class helps manage those references for specific replicated properties. A FGuidReferences instance will be created for each Replicated Property that is a reference to an object. Guid References may also be nested in properties (like dynamic arrays), so we'll recursively track those as well.
- L52 _public prototype_ `FGuidReferences( FBitReader& InReader, FBitReaderMark& InMark, const TSet<FNetworkGUID>& InUnmappedGUIDs, const TSet<FNetworkGUID>& InMappedDynamicGUIDs, const int32 InParentIndex, const int32 InCmdIndex, UPackageMap* InPackageMap );`
- L62 _public function_ `FGuidReferences( FGuidReferencesMap* InArray, const int32 InParentIndex, const int32 InCmdIndex, UPackageMap* InPackageMap ): ParentIndex(InParentIndex), CmdIndex(InCmdIndex), NumBufferBits(0), Array(InArray), PackageMap(InPackageMap)`
- L76 _public prototype_ `~FGuidReferences();`
- L78 _public prototype_ `FGuidReferences& operator=(const FGuidReferences& Other) = delete;`
- L79 _public prototype_ `FGuidReferences(const FGuidReferences& Other);`
- L81 _public prototype_ `FGuidReferences& operator=(FGuidReferences&&);`
- L82 _public prototype_ `FGuidReferences(FGuidReferences&& Other);`
- L84 _public function_ `void CountBytes(FArchive& Ar) const`
- L101 _public function_ `const TSet<FNetworkGUID>& GetUnmappedGUIDs() const` — Get the set of GUIDs for objects that haven't been loaded / created yet.
- L104 _public prototype_ `void AddUnmappedGUID(FNetworkGUID InGUID);` — Starts tracking InGUID if not already and calls UPackageMap::AddUnmappedNetGUIDReference if bRemapStableSubobjects is enabled.
- L107 _public prototype_ `void RemoveUnmappedGUID(FNetworkGUID InGUID);` — Stops tracking a GUID and calls UPackageMap::RemoveUnmappedNetGUIDReference if bRemapStableSubobjects is enabled.
- L110 _public prototype_ `bool UpdateUnmappedGUIDs(UPackageMap* InPackageMap, UObject* OriginalObject, const FProperty* Property, int32 AbsOffset);` — Called by FRepLayout to update GUID tracking when updating unmapped objects.
- L113 _public member_ `int32 ParentIndex;` — The Property Command index of the top level property that references the GUID.
- L116 _public member_ `int32 CmdIndex;` — The Property Command index of the actual property that references the GUID.
- L118 _public member_ `int32 NumBufferBits;`
- L122 _private member_ `TSet<FNetworkGUID> UnmappedGUIDs;` — GUIDs for objects that haven't been loaded / created yet.
- L126 _public member_ `TSet<FNetworkGUID> MappedDynamicGUIDs;` — GUIDs for dynamically spawned objects that have already been created.
- L129 _public member_ `TArray<uint8> Buffer;` — A copy of the last network data read related to this GUID Reference.
- L135 _public member_ `FGuidReferencesMap* Array;` — If this FGuidReferences instance is owned by an Array Property that contains nested GUID References, then this will be a valid FGuidReferencesMap containing the nested FGuidReferences.
- L139 _private member_ `TWeakObjectPtr<UPackageMap> PackageMap;` — Stored PackageMap reference to update with tracked UnmappedGUIDs.
- L142 _private prototype_ `void TrackAllUnmappedGUIDs() const;` — Calls UPackageMap::AddUnmappedNetGUIDReference for all GUIDs in UnmappedGUIDs, if bRemapStableSubobjects si enabled.

#### Free symbols / members of external scopes

- L21 _typedef_ `using FGuidReferencesMap = TMap<int32, FGuidReferences>;`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Net` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::Net`)
- L25 _externvar_ `extern bool bRemapStableSubobjects;` (scope `UE::Net::Private`)

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/NetCVars.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Net` (scope `UE`)
- L10 _externvar_ `extern int32 CVar_ForceConnectionViewerPriority;` (scope `UE::Net`)
- L11 _externvar_ `extern bool bAutoRegisterReplicatedProperties;` (scope `UE::Net`)
- L12 _externvar_ `extern bool bEnsureForMissingProperties;` (scope `UE::Net`)
- L13 _externvar_ `extern bool bReplicateCustomDeltaPropertiesInRepIndexOrder;` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/NetConditionGroupManager.h` (Public)


#### class `UE::Net::FNetConditionGroupManager`  
`class FNetConditionGroupManager`  
_L49-91_
- desc: Manage the membership of subobject's replicated with a COND_NetGroup condition. For a COND_NetGroup subobject to be replicated to a connection, they both need to be part of the same netcondition group. A netcondition group is simply an FName. This manager holds onto the groups the subobject is a part of, while the connection's player controller is where we hold information on the user's groups. Groups are inclusive and non-binding so subobject's can be part of multiple groups at the same time. As long as a player is a member of one of the subobject's group, that subobject will be replicated to that connection.
- L54 _public prototype_ `void RegisterSubObjectInGroup(UObject* SubObject, FName NetConditionGroup);` — Add a subobject into a netcondition group
- L57 _public prototype_ `void RegisterSubObjectInMultipleGroups(UObject* SubObject, TArrayView<FName> NetConditionGroups);` — Add a subobject to many netcondition groups
- L60 _public prototype_ `void UnregisterSubObjectFromGroup(UObject* SubObject, FName NetConditionGroup);` — Remove a subobject from a netcondition group
- L63 _public prototype_ `void UnregisterSubObjectFromMultipleGroups(UObject* SubObject, TArrayView<FName> NetConditionGroups);` — Remove a subobject from many netcondition groups
- L66 _public prototype_ `void UnregisterSubObjectFromAllGroups(UObject* SubObject);` — Remove the subobject from all groups it was included into
- L69 _public function_ `TArrayView<const FName> GetSubObjectNetConditionGroups(FObjectKey SubObjectKey) const` — Return the groups the subobject is a part of. Will be empty if it wasn't added to any.
- L75 _public prototype_ `void CountBytes(FArchive& Ar) const;`
- L90 _private member_ `TMap<FObjectKey, FSubObjectGroupInfo> SubObjectGroupMap;` — Map of the subobjects and the groups they are a part of

#### struct `UE::Net::FNetConditionGroupManager::FSubObjectGroupInfo`  
`struct FSubObjectGroupInfo`  
_L84-87_
- L86 _public member_ `TArray<FName, TInlineAllocator<DEFAULT_NETGROUP_INLINE_SIZE>> NetGroups;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Net` (scope `UE`)
- L26 _externvar_ `extern const FName NetGroupOwner;` (scope `UE::Net`) — Replicate a subobject to it's owning connection.
- L29 _externvar_ `extern const FName NetGroupReplay;` (scope `UE::Net`) — Replicate a subobject to the replay recording connection
- L32 _prototype_ `bool IsSpecialNetConditionGroup(FName NetConditionGroup);` (scope `UE::Net`) — Returns true if the netcondition is one of the special explicit groups.
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Net` (scope `UE`)
- L81 _macro_ `#define DEFAULT_NETGROUP_INLINE_SIZE 4` — Sets the inlined array size of each subobject entry.  Configure it to the average groups the subobjects are registered to make them quicker to access.

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/NetContext.h` (Public)


#### class `UE::Net::FNetContext`  
`class FNetContext`  
_L18-36_
- desc: Stateless class that provides misc network context information
- L26 _public function_ `static bool IsInsideNetRPC()` — Tells true if we are inside code executed from a remote RPC. Will be false if the RPC is executed locally.
- L32 _private prototype_ `FNetContext() = delete;`
- L33 _private prototype_ `~FNetContext() = delete;`
- L35 _private member_ `static bool bIsInRPCStack;`

#### class `UE::Net::FScopedNetContextRPC`  
`class FScopedNetContextRPC`  
_L40-50_
- desc: Used by friendly class to set the right network context
- L48 _private prototype_ `FScopedNetContextRPC();`
- L49 _private prototype_ `~FScopedNetContextRPC();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Net` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Net`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/NetSubObjectRegistry.h` (Public)


#### struct `UE::Net::FSubObjectRegistry`  
`struct FSubObjectRegistry`  
_L28-123_
- desc: Stores the SubObjects to replicate and the network condition dictating to which connection they can replicate to.
- L43 _public prototype_ `FSubObjectRegistry::EResult AddSubObjectUnique(UObject* InSubObject, ELifetimeCondition InNetCondition);` — Adds a subobject and returns if it's a new entry or existing entry
- L46 _public prototype_ `bool RemoveSubObject(UObject* InSubObject);` — Remove the subobject from the replicated list. Returns true if the subobject had been registered.
- L48 _public function_ `bool IsEmpty() const`
- L49 _public function_ `int32 Num() const`
- L55 _public prototype_ `void CleanRegistryIndexes(const TArrayView<int32>& IndexesToClean);` — Remove all the indexes specified by the passed array @param IndexesToClean Array of indexes sorted from smallest to biggest. The sorted order is assumed to have been done by the caller
- L58 _public prototype_ `ELifetimeCondition GetNetCondition(UObject* SubObject) const;` — Find the NetCondition of a SubObject. Returns COND_MAX if not registered
- L115 _public function_ `const TArray<FSubObjectRegistry::FEntry>& GetRegistryList() const` — Returns the list of registered subobjects
- L118 _public prototype_ `bool IsSubObjectInRegistry(const UObject* SubObject) const;` — Returns true if the subobject is contained in this list
- L122 _private member_ `TArray<FEntry> Registry;`

#### enum `UE::Net::FSubObjectRegistry::EResult`  
`enum class EResult : uint8`  
_L32-40_
- L35 _public enumerator_ `NewEntry` — SubObject is new in the registry
- L37 _public enumerator_ `AlreadyRegistered` — SubObject already was in the registry
- L39 _public enumerator_ `NetConditionConflict` — SubObject was already registered but the NetCondition passed is different from the entry

#### struct `UE::Net::FSubObjectRegistry::FEntry`  
`struct FEntry`  
_L60-112_
- L69 _private member_ `FWeakObjectPtr SubObject;`
- L77 _public member_ `FObjectKey Key;` — Store the object key info for fast access later
- L80 _public member_ `ELifetimeCondition NetCondition = COND_None;` — The network condition that chooses which connection this subobject can be replicated to. Default is none which means all connections receive it.
- L84 _public member_ `FName SubObjectClassName;` — Cached name of the subobject class, for minidump debugging
- L87 _public member_ `FName SubObjectName;` — Cached name of the subobject, for minidump debugging
- L90 _public function_ `FEntry(UObject* InSubObject, ELifetimeCondition InNetCondition = COND_None) : SubObject(InSubObject) , Key(InSubObject) , NetCondition(InNetCondition) #if UE_NET_REPACTOR_NAME_DEBUG , SubObjectClassName(InSubObject != nullptr ? ((UObjectBase*)((UObjectBase*)InSubObject)->GetClass())->GetFName() : NAME_None) , SubObjectName(InSubObject != nullptr ? ((UObjectBase*)InSubObject)->GetFName() : NAME_None) #endif`
- L101 _public function_ `inline bool operator==(const FEntry& rhs) const`
- L102 _public function_ `inline bool operator==(const UObject* rhs) const`
- L104 _public function_ `inline UObject* GetSubObject() const`

#### struct `UE::Net::FReplicatedComponentInfo`  
`struct FReplicatedComponentInfo`  
_L126-161_
- desc: Keep track of replicated components and their subobject list
- L129 _public member_ `UActorComponent* Component = nullptr;` — Component that will be replicated
- L132 _public member_ `FObjectKey Key;` — Store the object key info for fast access later
- L135 _public member_ `ELifetimeCondition NetCondition = COND_None;` — NetCondition of the component
- L138 _public member_ `FSubObjectRegistry SubObjects;` — Collection of subobjects replicated with this component
- L142 _public member_ `FName ComponentClassName;` — Cached name of the component class, for minidump debugging
- L145 _public member_ `FName ComponentName;` — Cached name of the component, for minidump debugging
- L148 _public function_ `FReplicatedComponentInfo(UActorComponent* InComponent, ELifetimeCondition InNetCondition = COND_None) : Component(InComponent) , Key((UObject*)InComponent) , NetCondition(InNetCondition) #if UE_NET_REPACTOR_NAME_DEBUG , ComponentClassName(InComponent != nullptr ? ((UObjectBase*)((UObjectBase*)InComponent)->GetClass())->GetFName() : NAME_None) , ComponentName(InComponent != nullptr ? ((UObjectBase*)InComponent)->GetFName() : NAME_None) #endif`
- L159 _public function_ `bool operator==(const FReplicatedComponentInfo& rhs) const`
- L160 _public function_ `bool operator==(const UActorComponent* rhs) const`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_NET_SUBOBJECTLIST_WEAKPTR 1`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Net` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/PacketAudit.h` (Public)


#### class `FPacketAudit`  
`class FPacketAudit`  
_L73-252_
- desc: FPacketAudit Uses inter-process-communication, to audit every stage of packet processing, for verifying that packets are processing properly, and that the client/server are in sync at every stage of reading/writing. Since this relies on IPC, it is only suitable for testing on a single machine. IMPORTANT: Only supports interaction between a single server, and a single client.
- L95 _private function_ `FPacketAudit()` — Default constructor
- L102 _private prototype_ `FPacketAudit(FPlatformProcess::FSemaphore* InGameMutex);` — Default constructor
- L107 _private prototype_ `~FPacketAudit();` — Default destructor
- L113 _public prototype_ `static void Init();` — Initialize GPacketAudtor
- L118 _public prototype_ `static void Destruct();` — Destroy GPacketAuditor
- L127 _public function_ `static inline void AddStage(FString StageName, FBitWriter& OutPacket, bool bByteAligned=false)` — On the send side, marks a named stage during packet writing, which should be audited on the receive side. @param StageName		The unique name to provide this stage of packet writing @param OutPacket		The packet the data is being written to - used for gathering audit information @param bByteAligned	Whether or not to treat the packet as if it is byte aligned (used in rare circumstances)
- L144 _public function_ `static inline void CheckStage(FString StageName, FBitReader& InPacket, bool bByteAligned=false)` — On the receive side, checks to see that a named stage was marked for auditing on the send side, and audits the packet data. @param StageName		The unique name to this stage of packet processing @param InPacket		The packet the data is being read from - used for gathering audit information @param bByteAligned	Whether or not to treat the packet as if it is byte aligned (used in rare circumstances)
- L159 _public function_ `static inline void NotifyLowLevelSend(FBitWriter& OutPacket)` — Low level netcode hook, notifying of outgoing packets @param OutPacket		The current outgoing packet
- L174 _public function_ `static inline void NotifyLowLevelReceive(FBitReader& InPacket)` — Low level netcode hook, notifying of incoming packets @param InPacket		The current incoming packet
- L186 _public function_ `static inline void NotifyLowLevelSend(uint8* Data, uint32 DataLen, uint32 DataLenBits)`
- L200 _public function_ `static inline void NotifyLowLevelReceive(uint8* Data, uint32 DataLen)`
- L214 _protected prototype_ `void AddStage_Internal(FString StageName, FBitWriter& OutPacket, bool bByteAligned);`
- L216 _protected prototype_ `void CheckStage_Internal(FString StageName, FBitReader& InPacket, bool bByteAligned);`
- L218 _protected prototype_ `void NotifyLowLevelSend_Internal(FBitWriter& OutPacket);`
- L220 _protected prototype_ `void NotifyLowLevelReceive_Internal(FBitReader& InPacket);`
- L230 _protected prototype_ `static uint32 PacketCRC(uint8* Data, uint32 DataLenBits);` — Gets the CRC of a packet, zeroing any unwritten bits in the last byte beforehand. @param Data			The packet data @param DataLenBits	The length of the data, in bits @return				Returns the CRC of the packet
- L236 _protected prototype_ `void DumpAuditData(FScopedAuditAccess& AuditLock, uint32 InPacketCRC=0);` — Dumps the collected packet audit data to the log
- L242 _protected member_ `FPlatformProcess::FSemaphore* GameMutex;` — Mutex used for enforcing a single instance of client/server packet auditing
- L245 _protected member_ `FPlatformProcess::FSemaphore* SharedMutex;` — Mutex used for exclusive access to shared memory
- L248 _protected member_ `FPlatformMemory::FSharedMemoryRegion* SendSharedMemory;` — Shared memory region for packet sends
- L251 _protected member_ `FPlatformMemory::FSharedMemoryRegion* ReceiveSharedMemory;` — Shared memory region for packet receives

#### struct `FPacketAudit::FScopedAuditAccess`  
`struct FScopedAuditAccess`  
_L80-88_
- desc: Provides scoped exclusive access to GSendPacketAudits and GReceivePacketAudits within the .cpp file
- L82 _public prototype_ `FScopedAuditAccess(FPacketAudit& InAudtor);`
- L84 _public prototype_ `~FScopedAuditAccess();`
- L87 _private member_ `FPacketAudit& Auditor;`

#### Free symbols / members of external scopes

- L59 _externvar_ `extern FPacketAudit* GPacketAuditor;` — The handler for managing packet auditing

### `Source/Runtime/Net/Core/Public/Net/Core/Misc/ResizableCircularQueue.h` (Public)


#### class `TResizableCircularQueue`  
`template<typename T, typename AllocatorT = FDefaultAllocator> class TResizableCircularQueue`  
_L20-127_
- desc: Simple ResizableCircularQueue. Relies on unsigned arithmetics and ever increasing head and tail indices to avoid having to store an extra element or maintain explicit empty state. InitialCapacity must be a power of two.
- L23 _public typedef_ `typedef T ElementT;`
- L26 _public prototype_ `explicit TResizableCircularQueue(SIZE_T InitialCapacity);` — Construct Empty Queue with the given initial Capacity, Capacity must be a power of two since we rely on unsigned arithmetics for wraparound
- L27 _public function_ `inline TResizableCircularQueue() : TResizableCircularQueue(0U)`
- L28 _public prototype_ `~TResizableCircularQueue();`
- L31 _public function_ `bool IsEmpty() const` — Returns true if the queue is empty
- L34 _public function_ `SIZE_T Count() const` — Gets the number of elements in the queue.
- L37 _public function_ `SIZE_T AllocatedCapacity() const` — Current allocated Capacity
- L40 _public prototype_ `void Enqueue(const ElementT& SrcData);` — Push single element to the back of the Queue
- L47 _public prototype_ `ElementT& EnqueueDefaulted_GetRef();` — Push single default constructed element to the back of the Queue, returning a reference to it. @see Enqueue_GetRef
- L54 _public prototype_ `ElementT& Enqueue_GetRef();` — Push single element to the back of the Queue, returning a reference to it. POD types will not be initialized. @see EnqueueDefaulted_GetRef
- L61 _public prototype_ `ElementT& Enqueue();` — Push single element to the back of the Queue, returning a reference to it. POD types will not be initialized. @see Enqueue_GetRef, EnqueueDefaulted_GetRef
- L64 _public prototype_ `void Pop();` — Pop elements from the front of the queue
- L67 _public prototype_ `void Pop(SIZE_T Count);` — Pop Count elements from the front of the queue
- L70 _public prototype_ `void PopNoCheck();` — Unchecked version, Pop a single element from the front of the queue
- L73 _public prototype_ `void PopNoCheck(SIZE_T Count);` — Unchecked version, Pop Count elements from the front of the queue
- L76 _public function_ `const ElementT& PeekAtOffset(SIZE_T Offset = 0) const` — Peek with the given offset from the front of the queue
- L79 _public function_ `ElementT& PokeAtOffset(SIZE_T Offset = 0)` — Poke at the element with the given offset from the front of the queue
- L82 _public function_ `const ElementT& Peek() const` — Peek at front element
- L85 _public function_ `ElementT& Poke()` — Peek at front element
- L88 _public function_ `const ElementT& PeekAtOffsetNoCheck(SIZE_T Offset = 0) const` — Unchecked version, Peek with the given offset from the front of the queue
- L91 _public function_ `ElementT& PokeAtOffsetNoCheck(SIZE_T Offset = 0)` — Unchecked version, Peek with the given offset from the front of the queue
- L94 _public function_ `const ElementT& PeekNoCheck() const` — Peek at front element with no check
- L97 _public prototype_ `void Trim();` — Trim memory usage to the next power of two for the current size
- L100 _public prototype_ `void Reset();` — Empty queue without releasing memory
- L103 _public prototype_ `void Empty();` — Empty queue and release memory
- L117 _private prototype_ `void SetCapacity(SIZE_T NewCapacity);` — Resize buffer maintaining validity of stored data.
- L119 _private typedef_ `typedef uint32 IndexT;`
- L120 _private typedef_ `typedef TArray<ElementT, AllocatorT> StorageT;`
- L122 _private member_ `IndexT Head;`
- L123 _private member_ `IndexT Tail;`
- L125 _private member_ `IndexT IndexMask;`
- L126 _private member_ `StorageT Storage;`
- L131 _function_ `template<typename T, typename AllocatorT> TResizableCircularQueue<T, AllocatorT>::TResizableCircularQueue(SIZE_T InitialCapacity) : Head(0u) , Tail(0u) , IndexMask(0u)`
- L145 _function_ `template<typename T, typename AllocatorT> TResizableCircularQueue<T, AllocatorT>::~TResizableCircularQueue()`
- L152 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::Enqueue(const ElementT& SrcData)`
- L167 _function_ `template<typename T, typename AllocatorT> typename TResizableCircularQueue<T, AllocatorT>::ElementT& TResizableCircularQueue<T, AllocatorT>::EnqueueDefaulted_GetRef()`
- L184 _function_ `template<typename T, typename AllocatorT> typename TResizableCircularQueue<T, AllocatorT>::ElementT& TResizableCircularQueue<T, AllocatorT>::Enqueue_GetRef()`
- L204 _function_ `template<typename T, typename AllocatorT> typename TResizableCircularQueue<T, AllocatorT>::ElementT& TResizableCircularQueue<T, AllocatorT>::Enqueue()`
- L211 _function_ `TResizableCircularQueue<T, AllocatorT>::Pop(SIZE_T PopCount)`
- L220 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::Pop()`
- L229 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::PopNoCheck()`
- L242 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::PopNoCheck(SIZE_T Count)`
- L268 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::SetCapacity(SIZE_T RequiredCapacity)`
- L320 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::Trim()`
- L333 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::Reset()`
- L341 _function_ `template<typename T, typename AllocatorT> void TResizableCircularQueue<T, AllocatorT>::Empty()`

#### enum `TResizableCircularQueue::(anonymous)`  
``  
_L107-110_

#### Free symbols / members of external scopes

- L108 _enumerator_ `bConstructElements = (TIsPODType<T>::Value ? 0U : 1U)` (scope `TResizableCircularQueue::__anon62d7807f0103`)
- L109 _enumerator_ `bDestructElements = (std::is_trivially_destructible_v<T> ? 0U : 1U)` (scope `TResizableCircularQueue::__anon62d7807f0103`)
- L270 _typedef_ `using SizeType = typename StorageT::SizeType;` (scope `TResizableCircularQueue::SetCapacity`)

### `Source/Runtime/Net/Core/Public/Net/Core/NetBitArray.h` (Public)


#### class `UE::Net::FNetBitArrayBase`  
`class FNetBitArrayBase`  
_L44-67_
- L50 _public typedef_ `typedef uint32 StorageWordType;`
- L51 _public member_ `static constexpr uint32 WordBitCount = sizeof(StorageWordType)*8U;`
- L54 _public member_ `static constexpr uint32 InvalidIndex = ~0U;` — Returned from various methods to indicate failure.
- L57 _public function_ `static constexpr StorageWordType AndOp(StorageWordType A, StorageWordType B)` — Some WordOps that can be passed to Combine() and ForAllSetBits()
- L58 _public function_ `static constexpr StorageWordType AndNotOp(StorageWordType A, StorageWordType B)`
- L59 _public function_ `static constexpr StorageWordType OrOp(StorageWordType A, StorageWordType B)`
- L60 _public function_ `static constexpr StorageWordType XorOp(StorageWordType A, StorageWordType B)`
- L63 _public function_ `static uint32 RoundUpToMaxWordBitCount(uint32 Value)` — Round up to a value that uses all available bits in a single NetBitArray Word

#### enum `UE::Net::FNetBitArrayBase::ENoResetNoValidateType`  
`enum ENoResetNoValidateType`  
_L47-47_
- L47 _public enumerator_ `enum ENoResetNoValidateType { NoResetNoValidate }; enum EResetOnInitType { ResetOnInit }; typedef uint32 StorageWordType; static constexpr uint32 WordBitCount = sizeof(StorageWordType)*8U; static constexpr uint32 InvalidIndex = ~0U;`

#### enum `UE::Net::FNetBitArrayBase::EResetOnInitType`  
`enum EResetOnInitType`  
_L48-48_
- L48 _public enumerator_ `enum EResetOnInitType { ResetOnInit }; typedef uint32 StorageWordType; static constexpr uint32 WordBitCount = sizeof(StorageWordType)*8U; static constexpr uint32 InvalidIndex = ~0U;`

#### class `UE::Net::FNetBitArray`  
`class FNetBitArray : public FNetBitArrayBase`  
_L73-328_
- inherits: `FNetBitArrayBase`
- desc: Simple bit array with internal storage. Has very little error checking as it is used in performance critical code.
- L77 _public prototype_ `FNetBitArray();` — Creates an empty NetBitArray.
- L80 _public prototype_ `explicit FNetBitArray(uint32 BitCount);` — Creates an array with size BitCount bits.
- L83 _public prototype_ `explicit FNetBitArray(uint32 BitCountIn, const ENoResetNoValidateType);` — Construct NetBitArray with the given BitCount but doesn't zero the allocated memory. Useful when the entire bit array will be overwritten before being read.
- L86 _public prototype_ `bool operator==(const FNetBitArray& Other) const;` — Return true if equal including BitCount and padding bits
- L92 _public prototype_ `void Init(uint32 BitCount);` — Sets a new size and resets the array's contents. @param BitCount - The number of bits in the array after the operation.
- L97 _public prototype_ `void InitAndCopy(const FNetBitArray& Source);` — Initialize a bit array with another array.
- L98 _public prototype_ `void InitAndCopy(const FNetBitArrayView& Source);`
- L102 _public prototype_ `void Empty();` — Release all memory and set capacity to 0 bits
- L110 _public prototype_ `void SetNumBits(uint32 BitCount);` — Sets the number of bits to BitCount. If the array grows the new bits will be cleared. Existing bits will remain intact. @param BitCount - The number of bits in the array after the operation.
- L118 _public prototype_ `void AddBits(uint32 BitCount);` — Grows the size with the specified number of bits. New bits will be cleared. @param BitCount - The number of bits to add to the array. @see SetNumBits
- L121 _public prototype_ `uint32 GetNumBits() const;` — Returns the number of bits
- L124 _public prototype_ `uint32 GetNumWords() const;` — Returns the number of words in our storage
- L130 _public function_ `inline const StorageWordType* GetDataChecked(uint32 MaxWordIterationCount) const UE_LIFETIMEBOUND` — Returns a pointer to the internal storage but validates that the array buffer is the expected size. Use this before directly iterating over one or multiple buffers and ensure they all support the max iteration index.
- L140 _public function_ `inline StorageWordType* GetDataChecked(uint32 MaxWordIterationCount) UE_LIFETIMEBOUND` — Returns a pointer to the internal storage but validates that the array buffer is the expected size. Use this before directly iterating over one or multiple buffers and ensure they all support the max iteration index.
- L147 _public function_ `inline const StorageWordType* GetData() const UE_LIFETIMEBOUND` — Returns a pointer to the internal storage. It's safer to use GetWord() or GetDataChecked() instead.
- L150 _public function_ `inline StorageWordType* GetData() UE_LIFETIMEBOUND` — Returns a pointer to the internal storage. It's safer to use GetWord() or GetDataChecked() instead.
- L153 _public function_ `inline StorageWordType GetWord(uint32 WordIndex) const UE_LIFETIMEBOUND` — Read an entire word. Useful when you want to read 'WordBitCount(32)' bits at once
- L160 _public function_ `inline StorageWordType& GetWord(uint32 WordIndex) UE_LIFETIMEBOUND` — Access an entire word. Useful when you want to write 'WordBitCount(32)' bits at once
- L168 _public function_ `void Reset()` — `UE_DEPRECATED(5.5, "Use ClearAllBits instead.")` — Clear all bits in the array.
- L171 _public prototype_ `void ClearAllBits();` — Clear all bits in the array.
- L174 _public prototype_ `void SetAllBits();` — Sets all bits in the array, but clears padding bits.
- L177 _public function_ `bool IsBitSet(uint32 Index) const` — Return if a specified bit is set or not
- L180 _public prototype_ `bool IsAnyBitSet() const;` — Returns true if any bit is set in the bitset. Note: Padding bits in storage are expected to be zero.
- L183 _public prototype_ `bool IsAnyBitSet(uint32 StartIndex, uint32 Count) const;` — Returns true if any bit is set in the specified range. The range will be clamped if needed.  Note: Padding bits in storage are expected to be zero.
- L186 _public prototype_ `bool IsNoBitSet() const;` — Returns true if no bit is set in the bitset. Note: Padding bits in storage are expected to be zero.
- L189 _public prototype_ `void SetBit(uint32 Index);` — Set the bit with the specified index
- L192 _public prototype_ `void SetBitValue(uint32 Index, bool bValue);` — Set the bit with the specified index to bValue
- L195 _public prototype_ `void SetBits(uint32 StartIndex, uint32 Count);` — Set the bit with the specified index to bValue
- L198 _public prototype_ `void ClearBits(uint32 StartIndex, uint32 Count);` — Clear the bits in the specified range
- L201 _public prototype_ `void ClearBit(uint32 Index);` — Clear the bit with the specified index
- L204 _public prototype_ `inline void OrBitValue(uint32 Index, bool bValue);` — Do an Or operation on the specified index
- L207 _public prototype_ `inline void AndBitValue(uint32 Index, bool bValue);` — Do an And operation on the specified index
- L210 _public prototype_ `bool GetBit(uint32 Index) const;` — Get the bit with the specified index
- L213 _public prototype_ `uint32 FindFirstZero() const;` — Find first zero bit. Returns InvalidIndex if no zero bit was found
- L216 _public prototype_ `uint32 FindFirstOne() const;` — Find first set bit. Returns InvalidIndex if no zero bit was found
- L219 _public prototype_ `uint32 FindFirstZero(uint32 StartIndex) const;` — Find first zero bit starting from StartIndex. Returns InvalidIndex if no zero bit was found.
- L222 _public prototype_ `uint32 FindFirstOne(uint32 StartIndex) const;` — Find first set bit starting from StartIndex. Returns InvalidIndex if no set bit was found.
- L225 _public prototype_ `uint32 FindLastZero() const;` — Find last zero bit. Returns InvalidIndex if no zero bit was found.
- L228 _public prototype_ `uint32 FindLastOne() const;` — Find last set bit. Returns InvalidIndex if no set bit was found.
- L231 _public prototype_ `FString ToString() const;` — Only prints the amount of set bits in the array. @see FNetBitArrayPrinter for more print options
- L244 _public prototype_ `uint32 GetSetBitIndices(uint32 StartIndex, uint32 Count, uint32* OutIndices, uint32 OutIndicesCapacity) const;` — Retrieves set bits in the provided range and returns how many indices were written to OutIndices. If OutIndices is filled to its capacity the search for set bits will end. OutIndices may be modified beyond the returned count but within the capacity. @param StartIndex Which bit index to start searching for set bits. @param Count How many bits to check. The count will be clamped to number of bits in the array so you can pass ~0U to check all bits. @param OutIndices Where to store the indices of the set bits. Indices with lower numbers will be stored first. @param OutIndicesCapacity How many indices can be stored in OutIndices. @returns Number of indices OutIndices was populated with.
- L247 _public prototype_ `uint32 CountSetBits(uint32 StartIndex = 0, uint32 Count = ~0U) const;` — Counts the number of set bits in this array in the provided range.
- L250 _public prototype_ `void Copy(const FNetBitArray& Other);` — Copy bits from other bit array. The other array must have the same bit count.
- L251 _public prototype_ `void Copy(const FNetBitArrayView& Other);`
- L261 _public prototype_ `template<typename WordOpFunctor> void Set(const FNetBitArray& First, WordOpFunctor&& WordOp, const FNetBitArray& Second);` — Overwrite this bit array with the result of a word operation from two other arrays @param First The first bit array to pass in the word operation @param WordOp The operation to perform on the two bit arrays @param Second The second bit array to pass in the word operation @see FNetBitArrayHelper::AndOp, FNetBitArrayHelper::AndNotOp, FNetBitArrayHelper::OrOp, FNetBitArrayHelper::XorOp
- L270 _public prototype_ `template<typename WordOpFunctor> void Combine(const FNetBitArray& Other, WordOpFunctor&& WordOp);` — Combine this array with another array using a word operation functor. Bit counts need to match. @param Other The other array to combine with. @param WordOpFunctor The operation to perform for each word to combine. Signature is StorageWordType(StorageWordType ThisWord, StorageWordType OtherWord). @see FNetBitArrayHelper::AndOp, FNetBitArrayHelper::AndNotOp, FNetBitArrayHelper::OrOp, FNetBitArrayHelper::XorOp
- L282 _public prototype_ `template<typename WordOpFunctor1, typename WordOpFunctor2> void CombineMultiple(WordOpFunctor1&& Op, const FNetBitArray& ArrayA, WordOpFunctor2&& Op2, const FNetBitArray& ArrayB);` — Combine this array with the result of a bitwise operation of two other arrays. eg: ThisArray = ThisArray Op (ArrayA Op2 ArrayB) @param Op Operation to execute on the word of this array and the result of the operation on the two other arrays @param ArrayA The first bit array to execute the other operation on @param Op2 The operation to execute on the word of the read-only array passed in parameter @param ArrayB The second bit array to execute the other operation on @see FNetBitArrayHelper::AndOp, FNetBitArrayHelper::AndNotOp, FNetBitArrayHelper::OrOp, FNetBitArrayHelper::XorOp
- L286 _public prototype_ `template<typename T> void ForAllSetBits(T&& Functor) const;` — Iterate over all set bits and invoke functor with signature void(uint32 BitIndex).
- L290 _public prototype_ `template<typename T> void ForAllSetBitsInRange(const uint32 StartBit, const uint32 EndBit, T&& Functor) const;` — Iterate over all set bits and invoke functor with signature void(uint32 BitIndex). EndBit is clamped to the the number of bits in the array minus one.
- L294 _public prototype_ `template<typename T> void ForAllUnsetBits(T&& Functor) const;` — Iterate over all the zero bits and invoke functor with signature void(uint32 BitIndex).
- L298 _public prototype_ `template<typename T, typename V> static void ForAllSetBits(const FNetBitArray& A, const FNetBitArray& B, T&& WordOpFunctor, V&& Functor);` — Iterate over all words and execute Functor, with signature void(uint32 BitIndex), for all set bits after executing WordOpFunctor
- L302 _public prototype_ `template <typename WordOpFunctor1, typename WordOpFunctor2, typename UserFunctor> static void ForAllSetBitsMultiple(const FNetBitArray& A, WordOpFunctor1&& Op1, const FNetBitArray& B, WordOpFunctor2&& Op2, const FNetBitArray& C, UserFunctor&& Functor);` — Call the functor for every bit still set after the following operation: "A Op1 (B Op2 C)"
- L306 _public prototype_ `template<typename T, typename V> static void ForAllExclusiveBits(const FNetBitArray& A, const FNetBitArray& B, T&& FunctorA, V&& FunctorB);` — Compare two BitArrays bit by bit and invoke FunctorA(BitIndex) for bits set only in array A and invoke FunctorB(BitIndex) for bits set only in array B.
- L310 _public prototype_ `template<typename T, typename V, typename Predicate> static void ForAllExclusiveBitsByPredicate(const FNetBitArray& A, const FNetBitArray& B, T&& FunctorA, V&& FunctorB, Predicate&& Pred);` — Compare two BitArrays bit by bit. Where they differ and Predicate(BitIndex) returns true FunctorA(BitIndex) is invoked for bits set only in array A and FunctorB(BitIndex) is invoked for bits set only in array B.
- L316 _public prototype_ `Private::FNetBitArrayRangedForConstIterator begin() const;` — DO NOT USE DIRECTLY Range-based for loop support iterating over set bits and returning the index to the set bit.
- L317 _public prototype_ `Private::FNetBitArrayRangedForConstIterator end() const;`
- L320 _private function_ `StorageWordType GetLastWordMask() const`
- L321 _private prototype_ `void ClearPaddingBits();`
- L324 _private prototype_ `void Reserve(uint32 BitCount);` — Sets a new size but doesn't initialize the contents with zero'd memory.
- L326 _private member_ `TArray<StorageWordType> Storage;`
- L327 _private member_ `uint32 BitCount;`
- L1097 _function_ `inline FNetBitArray::FNetBitArray() : BitCount(0)`
- L1102 _function_ `inline bool FNetBitArray::operator==(const FNetBitArray& Other) const`
- L1112 _function_ `inline FNetBitArray::FNetBitArray(uint32 InBitCount) : BitCount(InBitCount)`
- L1118 _function_ `inline FNetBitArray::FNetBitArray(uint32 InBitCount, const FNetBitArrayBase::ENoResetNoValidateType) : BitCount(InBitCount)`
- L1124 _function_ `inline void FNetBitArray::Init(uint32 InBitCount)`
- L1133 _function_ `inline void FNetBitArray::Reserve(uint32 InBitCount)`
- L1142 _function_ `inline void FNetBitArray::InitAndCopy(const FNetBitArray& Source)`
- L1149 _function_ `inline void FNetBitArray::InitAndCopy(const FNetBitArrayView& Source)`
- L1156 _function_ `inline void FNetBitArray::Empty()`
- L1162 _function_ `inline void FNetBitArray::SetNumBits(uint32 InBitCount)`
- L1171 _function_ `inline void FNetBitArray::AddBits(uint32 AdditionalBitCount)`
- L1176 _function_ `inline uint32 FNetBitArray::GetNumBits() const`
- L1181 _function_ `inline uint32 FNetBitArray::GetNumWords() const`
- L1186 _function_ `inline void FNetBitArray::ClearAllBits()`
- L1191 _function_ `inline void FNetBitArray::SetAllBits()`
- L1197 _function_ `inline bool FNetBitArray::IsAnyBitSet() const`
- L1202 _function_ `inline bool FNetBitArray::IsAnyBitSet(uint32 StartIndex, uint32 Count) const`
- L1207 _function_ `inline bool FNetBitArray::IsNoBitSet() const`
- L1212 _function_ `inline void FNetBitArray::SetBit(uint32 Index)`
- L1217 _function_ `inline void FNetBitArray::SetBitValue(uint32 Index, bool bValue)`
- L1222 _function_ `inline void FNetBitArray::SetBits(uint32 StartIndex, uint32 Count)`
- L1227 _function_ `inline void FNetBitArray::ClearBits(uint32 StartIndex, uint32 Count)`
- L1232 _function_ `inline void FNetBitArray::ClearBit(uint32 Index)`
- L1237 _function_ `inline bool FNetBitArray::GetBit(uint32 Index) const`
- L1242 _function_ `inline void FNetBitArray::OrBitValue(uint32 Index, bool bValue)`
- L1247 _function_ `inline void FNetBitArray::AndBitValue(uint32 Index, bool bValue)`
- L1252 _function_ `inline uint32 FNetBitArray::FindFirstZero() const`
- L1257 _function_ `inline uint32 FNetBitArray::FindFirstOne() const`
- L1262 _function_ `inline uint32 FNetBitArray::FindFirstZero(uint32 StartIndex) const`
- L1267 _function_ `inline uint32 FNetBitArray::FindFirstOne(uint32 StartIndex) const`
- L1272 _function_ `inline uint32 FNetBitArray::FindLastZero() const`
- L1277 _function_ `inline uint32 FNetBitArray::FindLastOne() const`
- L1282 _function_ `inline uint32 FNetBitArray::GetSetBitIndices(uint32 StartIndex, uint32 Count, uint32* OutIndices, uint32 OutIndicesCapacity) const`
- L1287 _function_ `inline uint32 FNetBitArray::CountSetBits(uint32 StartIndex, uint32 Count) const`
- L1292 _function_ `inline void FNetBitArray::Copy(const FNetBitArray& Other)`
- L1302 _function_ `inline void FNetBitArray::Copy(const FNetBitArrayView& Other)`
- L1312 _function_ `template<typename WordOpFunctor> inline void FNetBitArray::Set(const FNetBitArray& First, WordOpFunctor&& WordOp, const FNetBitArray& Second)`
- L1319 _function_ `template<typename WordOpFunctor> inline void FNetBitArray::Combine(const FNetBitArray& Other, WordOpFunctor&& WordOp)`
- L1325 _function_ `template<typename WordOpFunctor1, typename WordOpFunctor2> inline void FNetBitArray::CombineMultiple(WordOpFunctor1&& Op, const FNetBitArray& ArrayA, WordOpFunctor2&& Op2, const FNetBitArray& ArrayB)`
- L1332 _function_ `template<typename T> inline void FNetBitArray::ForAllSetBits(T&& Functor) const`
- L1337 _function_ `template<typename T> inline void FNetBitArray::ForAllSetBitsInRange(const uint32 StartBit, const uint32 EndBit, T&& Functor) const`
- L1342 _function_ `template<typename T> inline void FNetBitArray::ForAllUnsetBits(T&& Functor) const`
- L1347 _function_ `template <typename T, typename V> inline void FNetBitArray::ForAllSetBits(const FNetBitArray& A, const FNetBitArray& B, T&& WordOpFunctor, V&& Functor)`
- L1353 _function_ `template<typename WordOpFunctor1, typename WordOpFunctor2, typename UserFunctor> inline void FNetBitArray::ForAllSetBitsMultiple(const FNetBitArray& A, WordOpFunctor1&& Op1, const FNetBitArray& B, WordOpFunctor2&& Op2, const FNetBitArray& C, UserFunctor&& Functor)`
- L1360 _function_ `template <typename T, typename V> inline void FNetBitArray::ForAllExclusiveBits(const FNetBitArray& A, const FNetBitArray& B, T&& FunctorA, V&& FunctorB)`
- L1366 _function_ `template <typename T, typename V, typename Predicate> inline void FNetBitArray::ForAllExclusiveBitsByPredicate(const FNetBitArray& A, const FNetBitArray& B, T&& FunctorA, V&& FunctorB, Predicate&& Pred)`
- L1372 _function_ `inline void FNetBitArray::ClearPaddingBits()`
- L1384 _function_ `inline Private::FNetBitArrayRangedForConstIterator FNetBitArray::begin() const`
- L1389 _function_ `inline Private::FNetBitArrayRangedForConstIterator FNetBitArray::end() const`

#### class `UE::Net::FNetBitArrayView`  
`class FNetBitArrayView : public FNetBitArrayBase`  
_L336-563_
- inherits: `FNetBitArrayBase`
- desc: Simple bit array view. Assumes external storage and has very little error checking as it is used in performance critical code. Note: Trailing padding bits in storage will be zeroed unless the view is explicitly constructed to allow it. Certain operations assume the padding bits are cleared.
- L341 _public prototype_ `inline FNetBitArrayView();` — Constructor will produce a valid but empty bitarray.
- L344 _public prototype_ `inline FNetBitArrayView(StorageWordType* StorageIn, uint32 BitCountIn, const ENoResetNoValidateType);` — Construct NetBitArray from external storage. Storage must be large enough to fit given the BitCount. No clearing of storage and no validation that padding bits are cleared.
- L346 _public prototype_ `inline FNetBitArrayView(StorageWordType* StorageIn, uint32 BitCountIn, const EResetOnInitType);` — Construct NetBitArray from external storage. Storage must be large enough to fit given the BitCount. Clears the entire storage.
- L348 _public prototype_ `inline FNetBitArrayView(StorageWordType* StorageIn, uint32 BitCountIn);` — Construct NetBitArray from external storage. Storage must be large enough to fit given the BitCount. Validates that padding bits are cleared.
- L351 _public prototype_ `bool operator==(const FNetBitArrayView& Other) const;` — Return true if equal including BitCount and padding bits
- L354 _public function_ `inline bool IsBitSet(uint32 Index) const` — Return if a specific bit is set or not
- L357 _public prototype_ `inline bool IsAnyBitSet() const;` — Returns true if any bit is set in the bitset Note: Padding bits in storage are expected to be zero.
- L360 _public prototype_ `inline bool IsAnyBitSet(uint32 StartIndex, uint32 Count) const;` — Returns true if any bit is set in the specified range. The range will be clamped if needed. Note: Padding bits in storage are expected to be zero.
- L363 _public prototype_ `inline bool IsNoBitSet() const;` — Returns true if no bit is set in the bitset. Note: Padding bits in storage are expected to be zero.
- L367 _public function_ `inline void Reset()` — `UE_DEPRECATED(5.5, "Use ClearAllBits instead.")` — Reset the storage of the BitArray including any padding bits
- L370 _public prototype_ `inline void ClearAllBits();` — Clear all bits to zero
- L373 _public prototype_ `inline void ClearPaddingBits();` — All padding bits will be set to zero
- L376 _public prototype_ `inline void SetAllBits();` — Set all bits, padding bits will be zeroed
- L379 _public prototype_ `inline void SetBit(uint32 Index);` — Set the bit with the specified index
- L382 _public prototype_ `inline void SetBitValue(uint32 Index, bool bValue);` — Set the bit with the specified index to bValue
- L385 _public prototype_ `inline void SetBits(uint32 StartIndex, uint32 Count);` — Set the bits in the specified range to true
- L388 _public prototype_ `inline void ClearBits(uint32 StartIndex, uint32 Count);` — Clear the bits in the specified range
- L391 _public prototype_ `inline void ClearBit(uint32 Index) const;` — Clear the bit with the specified index
- L394 _public prototype_ `inline bool GetBit(uint32 Index) const;` — Get the bit with the specified index
- L397 _public prototype_ `inline void OrBitValue(uint32 Index, bool bValue);` — Do an Or operation on the specified index
- L400 _public prototype_ `inline void AndBitValue(uint32 Index, bool bValue);` — Do an And operation on the specified index
- L403 _public prototype_ `inline uint32 FindFirstZero() const;` — Find first zero bit. Returns InvalidIndex if no zero bit was found
- L406 _public prototype_ `inline uint32 FindFirstOne() const;` — Find first set bit. Returns InvalidIndex if no zero bit was found
- L409 _public prototype_ `inline uint32 FindFirstZero(uint32 StartIndex) const;` — Find first zero bit starting from StartIndex. Returns InvalidIndex if no zero bit was found.
- L412 _public prototype_ `inline uint32 FindFirstOne(uint32 StartIndex) const;` — Find first set bit starting from StartIndex. Returns InvalidIndex if no set bit was found.
- L415 _public prototype_ `uint32 FindLastZero() const;` — Find last zero bit. Returns InvalidIndex if no zero bit was found.
- L418 _public prototype_ `uint32 FindLastOne() const;` — Find last set bit. Returns InvalidIndex if no set bit was found.
- L421 _public prototype_ `inline uint32 GetNumBits() const;` — Returns the number of bits
- L424 _public prototype_ `inline uint32 GetNumWords() const;` — Returns the number of words in our storage
- L430 _public function_ `inline const StorageWordType* GetDataChecked(uint32 MaxWordIterationCount) const UE_LIFETIMEBOUND` — Returns a pointer to the internal storage but validates that the array buffer is the expected size. Use this before directly iterating over one or multiple buffers and ensure they all support the max iteration index.
- L440 _public function_ `inline StorageWordType* GetDataChecked(uint32 MaxWordIterationCount) UE_LIFETIMEBOUND` — Returns a pointer to the internal storage but validates that the array buffer is the expected size. Use this before directly iterating over one or multiple buffers and ensure they all support the max iteration index.
- L447 _public function_ `inline const StorageWordType* GetData() const UE_LIFETIMEBOUND` — Returns a pointer to the internal storage. It's safer to use GetWord() or GetDataChecked() instead.
- L450 _public function_ `inline StorageWordType* GetData() UE_LIFETIMEBOUND` — Returns a pointer to the internal storage. It's safer to use GetWord() or GetDataChecked() instead.
- L453 _public function_ `inline StorageWordType GetWord(uint32 WordIndex) const UE_LIFETIMEBOUND` — Read an entire word. Useful when you want to read 'WordBitCount(32)' bits at once
- L460 _public function_ `inline StorageWordType& GetWord(uint32 WordIndex) UE_LIFETIMEBOUND` — Access an entire word. Useful when you want to write 'WordBitCount(32)' bits at once
- L467 _public prototype_ `FString ToString() const;` — Only prints the amount of set bits in the array. @see FNetBitArrayPrinter for more print options
- L480 _public prototype_ `uint32 GetSetBitIndices(uint32 StartIndex, uint32 Count, uint32* OutIndices, uint32 OutIndicesCapacity) const;` — Retrieves set bits in the provided range and returns how many indices were written to OutIndices. If OutIndices is filled to its capacity the search for set bits will end. OutIndices may be modified beyond the returned count but within the capacity. @param StartIndex Which bit index to start searching for set bits. @param Count How many bits to check. The count will be clamped to number of bits in the array so you can pass ~0U to check all bits. @param OutIndices Where to store the indices of the set bits. Indices with lower numbers will be stored first. @param OutIndicesCapacity How many indices can be stored in OutIndices. @returns Number of indices OutIndices was populated with.
- L483 _public prototype_ `uint32 CountSetBits(uint32 StartIndex = 0, uint32 Count = ~0U) const;` — Counts the number of set bits in this array in the provided range.
- L486 _public prototype_ `inline void Copy(const FNetBitArrayView& Other);` — Copy bits from other bit array. The other array must have the same bit count.
- L487 _public prototype_ `inline void Copy(const FNetBitArray& Other);`
- L497 _public prototype_ `template<typename WordOpFunctor> void Set(const FNetBitArrayView& First, WordOpFunctor&& WordOp, const FNetBitArrayView& Second);` — Overwrite this bit array with the result of a word operation from two other arrays @param First The first bit array to pass in the word operation @param WordOp The operation to perform on the two bit arrays @param Second The second bit array to pass in the word operation @see FNetBitArrayHelper::AndOp, FNetBitArrayHelper::AndNotOp, FNetBitArrayHelper::OrOp, FNetBitArrayHelper::XorOp
- L506 _public prototype_ `template<typename WordOpFunctor> void Combine(const FNetBitArrayView& Other, WordOpFunctor&& WordOp);` — Combine this array with another array using a word operation functor. Bit counts need to match. @param Other The other array to combine with. @param WordOpFunctor The operation to perform for each word to combine. Signature is StorageWordType(StorageWordType ThisWord, StorageWordType OtherWord). @see FNetBitArrayHelper::AndOp, FNetBitArrayHelper::AndNotOp, FNetBitArrayHelper::OrOp, FNetBitArrayHelper::XorOp
- L518 _public prototype_ `template<typename WordOpFunctor1, typename WordOpFunctor2> void CombineMultiple(WordOpFunctor1&& Op, const FNetBitArrayView& ArrayA, WordOpFunctor2&& Op2, const FNetBitArrayView& ArrayB);` — Combine this array with the result of a bitwise operation of two other arrays. eg: ThisArray = ThisArray Op (ArrayA Op2 ArrayB) @param Op Operation to execute on the word of this array and the result of the operation on the two other arrays @param ArrayA The first bit array to execute the other operation on @param Op2 The operation to execute on the word of the read-only array passed in parameter @param ArrayB The second bit array to execute the other operation on @see FNetBitArrayHelper::AndOp, FNetBitArrayHelper::AndNotOp, FNetBitArrayHelper::OrOp, FNetBitArrayHelper::XorOp
- L522 _public prototype_ `template <typename T> void ForAllSetBits(T&& Functor) const;` — Iterate over all set bits and invoke functor with signature void(uint32 BitIndex).
- L526 _public prototype_ `template <typename T> void ForAllSetBitsInRange(const uint32 StartBit, const uint32 EndBit, T&& Functor) const;` — Iterate over all set bits from StartBit to EndBit (inclusive) and invoke functor with signature void(uint32 BitIndex). EndBit is clamped to the the number of bits in the array minus one.
- L530 _public prototype_ `template<typename T> void ForAllUnsetBits(T&& Functor) const;` — Iterate over all the zero bits and invoke functor with signature void(uint32 BitIndex).
- L534 _public prototype_ `template <typename T, typename V> static void ForAllSetBits(const FNetBitArrayView& A, const FNetBitArrayView& B, T&& WordOpFunctor, V&& Functor);` — Iterate over all words and execute Functor, with signature void(uint32 BitIndex), for all set bits after executing WordOpFunctor
- L538 _public prototype_ `template <typename WordOpFunctor1, typename WordOpFunctor2, typename UserFunctor> static void ForAllSetBitsMultiple(const FNetBitArrayView& A, WordOpFunctor1&& Op1, const FNetBitArrayView& B, WordOpFunctor2&& Op2, const FNetBitArrayView& C, UserFunctor&& Functor);` — Call the functor for every bit still set after the following operation: "A Op1 (B Op2 C)"
- L542 _public prototype_ `template <typename T, typename V> static void ForAllExclusiveBits(const FNetBitArrayView& A, const FNetBitArrayView& B, T&& FunctorA, V&& FunctorB);` — Compare two BitArrays bit by bit and invoke FunctorA(BitIndex) for bits set only in array A and invoke FunctorB(BitIndex) for bits set only in array B.
- L546 _public prototype_ `template<typename T, typename V, typename Predicate> static void ForAllExclusiveBitsByPredicate(const FNetBitArrayView& A, const FNetBitArrayView& B, T&& FunctorA, V&& FunctorB, Predicate&& Pred);` — Compare two BitArrays bit by bit. Where they differ and Predicate(BitIndex) returns true FunctorA(BitIndex) is invoked for bits set only in array A and FunctorB(BitIndex) is invoked for bits set only in array B.
- L548 _public prototype_ `static constexpr inline uint32 CalculateRequiredWordCount(uint32 BitCount);`
- L554 _public prototype_ `Private::FNetBitArrayRangedForConstIterator begin() const;` — DO NOT USE DIRECTLY Range-based for loop support iterating over set bits and returning the index to the set bit.
- L555 _public prototype_ `Private::FNetBitArrayRangedForConstIterator end() const;`
- L558 _private function_ `inline StorageWordType GetLastWordMask() const`
- L560 _private member_ `StorageWordType* Storage;`
- L561 _private member_ `uint32 WordCount;`
- L562 _private member_ `uint32 BitCount;`
- L1398 _function_ `constexpr uint32 FNetBitArrayView::CalculateRequiredWordCount(uint32 BitCount)`
- L1403 _function_ `FNetBitArrayView::FNetBitArrayView() : Storage(&BitCount) , WordCount(0) , BitCount(0)`
- L1410 _function_ `FNetBitArrayView::FNetBitArrayView(StorageWordType* StorageIn, uint32 BitCountIn, const ENoResetNoValidateType) : Storage(StorageIn) , WordCount(CalculateRequiredWordCount(BitCountIn)) , BitCount(BitCountIn)`
- L1421 _function_ `FNetBitArrayView::FNetBitArrayView(StorageWordType* StorageIn, uint32 BitCountIn, const EResetOnInitType) : FNetBitArrayView(StorageIn, BitCountIn, NoResetNoValidate)`
- L1427 _function_ `FNetBitArrayView::FNetBitArrayView(StorageWordType* StorageIn, uint32 BitCountIn) : FNetBitArrayView(StorageIn, BitCountIn, NoResetNoValidate)`
- L1434 _function_ `inline bool FNetBitArrayView::operator==(const FNetBitArrayView& Other) const`
- L1444 _function_ `bool FNetBitArrayView::IsAnyBitSet() const`
- L1449 _function_ `bool FNetBitArrayView::IsAnyBitSet(uint32 StartIndex, uint32 Count) const`
- L1454 _function_ `bool FNetBitArrayView::IsNoBitSet() const`
- L1459 _function_ `void FNetBitArrayView::ClearAllBits()`
- L1464 _function_ `void FNetBitArrayView::ClearPaddingBits()`
- L1472 _function_ `void FNetBitArrayView::SetAllBits()`
- L1478 _function_ `void FNetBitArrayView::Copy(const FNetBitArrayView& Other)`
- L1487 _function_ `void FNetBitArrayView::Copy(const FNetBitArray& Other)`
- L1496 _function_ `void FNetBitArrayView::SetBit(uint32 Index)`
- L1501 _function_ `void FNetBitArrayView::SetBitValue(uint32 Index, bool bValue)`
- L1506 _function_ `void FNetBitArrayView::SetBits(uint32 StartIndex, uint32 Count)`
- L1511 _function_ `void FNetBitArrayView::ClearBits(uint32 StartIndex, uint32 Count)`
- L1516 _function_ `void FNetBitArrayView::ClearBit(uint32 Index) const`
- L1521 _function_ `bool FNetBitArrayView::GetBit(uint32 Index) const`
- L1526 _function_ `void FNetBitArrayView::OrBitValue(uint32 Index, bool bValue)`
- L1531 _function_ `void FNetBitArrayView::AndBitValue(uint32 Index, bool bValue)`
- L1536 _function_ `uint32 FNetBitArrayView::FindFirstZero() const`
- L1541 _function_ `uint32 FNetBitArrayView::FindFirstOne() const`
- L1546 _function_ `uint32 FNetBitArrayView::FindFirstZero(uint32 StartIndex) const`
- L1551 _function_ `uint32 FNetBitArrayView::FindFirstOne(uint32 StartIndex) const`
- L1556 _function_ `inline uint32 FNetBitArrayView::FindLastZero() const`
- L1561 _function_ `inline uint32 FNetBitArrayView::FindLastOne() const`
- L1566 _function_ `uint32 FNetBitArrayView::GetNumWords() const`
- L1571 _function_ `uint32 FNetBitArrayView::GetNumBits() const`
- L1576 _function_ `inline uint32 FNetBitArrayView::GetSetBitIndices(uint32 StartIndex, uint32 Count, uint32* OutIndices, uint32 OutIndicesCapacity) const`
- L1581 _function_ `inline uint32 FNetBitArrayView::CountSetBits(uint32 StartIndex, uint32 Count) const`
- L1586 _function_ `template<typename WordOpFunctor> inline void FNetBitArrayView::Set(const FNetBitArrayView& First, WordOpFunctor&& WordOp, const FNetBitArrayView& Second)`
- L1593 _function_ `template<typename WordOpFunctor> inline void FNetBitArrayView::Combine(const FNetBitArrayView& Other, WordOpFunctor&& WordOp)`
- L1599 _function_ `template<typename WordOpFunctor1, typename WordOpFunctor2> inline void FNetBitArrayView::CombineMultiple(WordOpFunctor1&& Op, const FNetBitArrayView& ArrayA, WordOpFunctor2&& Op2, const FNetBitArrayView& ArrayB)`
- L1606 _function_ `template<typename T> inline void FNetBitArrayView::ForAllSetBits(T&& Functor) const`
- L1611 _function_ `template<typename T> inline void FNetBitArrayView::ForAllSetBitsInRange(const uint32 StartBit, const uint32 EndBit, T&& Functor) const`
- L1616 _function_ `template<typename T> inline void FNetBitArrayView::ForAllUnsetBits(T&& Functor) const`
- L1622 _function_ `template <typename T, typename V> inline void FNetBitArrayView::ForAllSetBits(const FNetBitArrayView& A, const FNetBitArrayView& B, T&& WordOpFunctor, V&& Functor)`
- L1629 _function_ `template <typename WordOpFunctor1, typename WordOpFunctor2, typename UserFunctor> inline void FNetBitArrayView::ForAllSetBitsMultiple(const FNetBitArrayView& A, WordOpFunctor1&& Op1, const FNetBitArrayView& B, WordOpFunctor2&& Op2, const FNetBitArrayView& C, UserFunctor&& Functor)`
- L1637 _function_ `template <typename T, typename V> void FNetBitArrayView::ForAllExclusiveBits(const FNetBitArrayView& A, const FNetBitArrayView& B, T&& FunctorA, V&& FunctorB)`
- L1644 _function_ `template <typename T, typename V, typename Predicate> void FNetBitArrayView::ForAllExclusiveBitsByPredicate(const FNetBitArrayView& A, const FNetBitArrayView& B, T&& FunctorA, V&& FunctorB, Predicate&& Pred)`
- L1650 _function_ `inline Private::FNetBitArrayRangedForConstIterator FNetBitArrayView::begin() const`
- L1655 _function_ `inline Private::FNetBitArrayRangedForConstIterator FNetBitArrayView::end() const`

#### class `UE::Net::FNetBitArrayHelper`  
`class FNetBitArrayHelper final`  
_L570-1051_
- L576 _private typedef_ `typedef FNetBitArray::StorageWordType StorageWordType;`
- L577 _private member_ `static constexpr uint32 WordBitCount = sizeof(StorageWordType) * 8u;`
- L579 _private function_ `static StorageWordType GetLastWordMask(uint32 BitCount)`
- L584 _private function_ `static bool IsAnyBitSet(const StorageWordType* Storage, const uint32 WordCount)`
- L597 _private function_ `static bool IsAnyBitSet(const StorageWordType* Storage, const uint32 BitCount, const uint32 StartIndex, const uint32 Count)`
- L628 _private function_ `static void SetBits(StorageWordType* Storage, const uint32 BitCount, const uint32 StartIndex, const uint32 Count)`
- L650 _private function_ `static void ClearBits(StorageWordType* Storage, const uint32 BitCount, const uint32 StartIndex, const uint32 Count)`
- L672 _private function_ `static void SetBit(StorageWordType* Storage, const uint32 BitCount, const uint32 Index)`
- L682 _private function_ `static void SetBitValue(StorageWordType* Storage, const uint32 BitCount, const uint32 Index, const bool bValue)`
- L693 _private function_ `static void ClearBit(StorageWordType* Storage, const uint32 BitCount, const uint32 Index)`
- L703 _private function_ `static bool GetBit(const StorageWordType* Storage, const uint32 BitCount, const uint32 Index)`
- L713 _private function_ `static void OrBitValue(StorageWordType* Storage, const uint32 BitCount, const uint32 Index, const bool bValue)`
- L724 _private function_ `static void AndBitValue(StorageWordType* Storage, const uint32 BitCount, const uint32 Index, const bool bValue)`
- L735 _private function_ `static uint32 FindFirstZero(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount)`
- L751 _private function_ `static uint32 FindFirstOne(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount)`
- L767 _private function_ `static uint32 FindFirstZero(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount, const uint32 StartIndex)`
- L787 _private function_ `static uint32 FindFirstOne(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount, const uint32 StartIndex)`
- L808 _private function_ `static uint32 FindLastZero(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount)`
- L830 _private function_ `static uint32 FindLastOne(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount)`
- L847 _private prototype_ `static uint32 GetSetBitIndices(const StorageWordType* Storage, const uint32 BitCount, const uint32 StartIndex, const uint32 Count, uint32* const OutIndices, const uint32 OutIndicesCapacity);`
- L849 _private prototype_ `static uint32 CountSetBits(const StorageWordType* Storage, const uint32 BitCount, const uint32 StartIndex, const uint32 Count);`
- L851 _private function_ `template<typename WordOpFunctor> static void Set(StorageWordType* Storage, const StorageWordType* FirstSource, const StorageWordType* SecondSource, const uint32 WordCount, WordOpFunctor&& WordOp)`
- L859 _private function_ `template<typename Functor> static void Combine(StorageWordType* Storage, const StorageWordType* OtherStorage, const uint32 WordCount, Functor&& WordOp)`
- L867 _private function_ `template<typename WordOpFunctor1, typename WordOpFunctor2> static void CombineMultiple(StorageWordType* WriteStorage, const StorageWordType* const ReadStorageA, const StorageWordType* const ReadStorageB, const uint32 WordCount, WordOpFunctor1&& WordOpWrite, WordOpFunctor2&& WordOpRead)`
- L875 _private function_ `static bool IsEqual(const StorageWordType* Storage, const StorageWordType* OtherStorage, const uint32 WordCount)`
- L885 _private function_ `template<typename T> static void ForAllSetBits(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount, T&& Functor)`
- L905 _private function_ `template<typename T> static void ForAllSetBitsInRange(const StorageWordType* Storage, const uint32 TotalWordCount, const uint32 TotalBitCount, const uint32 StartBit, const uint32 InEndBit, T&& Functor)` — Calls Functor for every set bit from StartBit to EndBit (inclusive)
- L936 _private function_ `template<typename T> static void ForAllUnsetBits(const StorageWordType* Storage, const uint32 WordCount, const uint32 BitCount, T&& Functor)`
- L958 _private function_ `template<typename T, typename V> static void ForAllSetBits(const StorageWordType* StorageA, const StorageWordType* StorageB, const uint32 WordCount, const uint32 BitCount, T&& WordOpFunctor, V&& Functor)`
- L980 _private function_ `template <typename WordOpFunctor1, typename WordOpFunctor2, typename UserFunctor> static void ForAllSetBitsMultiple(const StorageWordType* StorageA, const StorageWordType* StorageB, const StorageWordType* StorageC, const uint32 WordCount, const uint32 BitCount, WordOpFunctor1&& WordOp1, WordOpFunctor2&& WordOp2, UserFunctor&& Functor)`
- L1003 _private function_ `template<typename T, typename V, typename Predicate> static void ForAllExclusiveBitsByPredicate(const StorageWordType* StorageA, const StorageWordType* StorageB, const uint32 WordCount, const uint32 BitCount, T&& FunctorA, V&& FunctorB, Predicate&& Pred)`
- L1041 _private function_ `template<typename T, typename V> static void ForAllExclusiveBits(const StorageWordType* StorageA, const StorageWordType* StorageB, const uint32 WordCount, const uint32 BitCount, T&& FunctorA, V&& FunctorB)`

#### class `UE::Net::Private::FNetBitArrayRangedForConstIterator`  
`class FNetBitArrayRangedForConstIterator`  
_L1059-1090_
- L1062 _public prototype_ `FNetBitArrayRangedForConstIterator();`
- L1064 _public prototype_ `FNetBitArrayRangedForConstIterator& operator++();`
- L1066 _public prototype_ `bool operator!=(const FNetBitArrayRangedForConstIterator& It) const;`
- L1069 _public prototype_ `uint32 operator*() const;` — Returns the bit index the iterator is pointing at.
- L1081 _private prototype_ `FNetBitArrayRangedForConstIterator(const FNetBitArrayBase::StorageWordType* InData UE_LIFETIMEBOUND, uint32 BitCount, ERangeStart RangeStart);`
- L1083 _private prototype_ `void AdvanceToNextSetBit();`
- L1085 _private member_ `const FNetBitArrayBase::StorageWordType* Data = nullptr;`
- L1086 _private member_ `uint32 BitCount = 0;`
- L1087 _private member_ `uint32 WordCount = 0;`
- L1088 _private member_ `uint32 CurrentBitIndex = 0;`
- L1089 _private member_ `uint32 CurrentWord = 0;`
- L1695 _function_ `inline FNetBitArrayRangedForConstIterator::FNetBitArrayRangedForConstIterator()`
- L1699 _function_ `inline FNetBitArrayRangedForConstIterator::FNetBitArrayRangedForConstIterator(const FNetBitArrayBase::StorageWordType* InData UE_LIFETIMEBOUND, uint32 InBitCount, FNetBitArrayRangedForConstIterator::ERangeStart RangeStart) : Data(InData) , BitCount(InBitCount) , WordCount(FNetBitArrayView::CalculateRequiredWordCount(BitCount)) , CurrentBitIndex(RangeStart == ERangeStart::Begin ? 0 : BitCount)`
- L1710 _function_ `inline FNetBitArrayRangedForConstIterator& FNetBitArrayRangedForConstIterator::operator++()`
- L1716 _function_ `inline uint32 FNetBitArrayRangedForConstIterator::operator*() const`
- L1721 _function_ `inline bool FNetBitArrayRangedForConstIterator::operator!=(const FNetBitArrayRangedForConstIterator& It) const`
- L1727 _function_ `inline void FNetBitArrayRangedForConstIterator::AdvanceToNextSetBit()`

#### enum `UE::Net::Private::FNetBitArrayRangedForConstIterator::ERangeStart`  
`enum class ERangeStart : unsigned`  
_L1075-1079_
- L1077 _public enumerator_ `Begin`
- L1078 _public enumerator_ `End`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Net` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Net`)
- L27 _macro_ `# define UE_NETBITARRAY_VALIDATE 0`
- L29 _macro_ `# define UE_NETBITARRAY_VALIDATE 1`
- L34 _macro_ `# define UE_NETBITARRAY_CHECK(x) check(x)`
- L36 _macro_ `# define UE_NETBITARRAY_CHECK(...)`
- L39 _macro_ `#define UE_NETBITARRAY_VALIDATE_BOTH_COMPATIBLE(lhs,rhs) UE_NETBITARRAY_CHECK((lhs).GetData() != (rhs).GetData() && (lhs).GetNumBits() == (rhs).GetNumBits())`
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace Net` (scope `UE`)
- L1044 _function_ `` (scope `UE::Net::FNetBitArrayHelper::ForAllExclusiveBits`)
- L1053 _namespace_ `namespace Private` (scope `UE::Net`)
- L1661 _function_ `inline FNetBitArrayView MakeNetBitArrayView(const FNetBitArrayView::StorageWordType* Storage, uint32 BitCount)` (scope `UE::Net`) — Transform any raw buffer into a FNetBitArrayView
- L1666 _function_ `inline FNetBitArrayView MakeNetBitArrayView(const FNetBitArrayView::StorageWordType* Storage, uint32 BitCount, const FNetBitArrayBase::ENoResetNoValidateType)` (scope `UE::Net`)
- L1672 _function_ `inline FNetBitArrayView MakeNetBitArrayView(const FNetBitArray& BitArray)` (scope `UE::Net`) — Transform a FNetBitArray into a FNetBitArrayView
- L1678 _function_ `inline FNetBitArrayView MakeNetBitArrayView(FNetBitArray& BitArray, const FNetBitArrayBase::ENoResetNoValidateType)` (scope `UE::Net`) — Transform a FNetBitArray into a FNetBitArrayView without validating the contents of the bit array received
- L1686 _namespace_ `namespace UE`
- L1686 _namespace_ `namespace Net` (scope `UE`)
- L1686 _namespace_ `namespace Private` (scope `UE::Net`)
- L1729 _typedef_ `using SignedWordType = typename std::make_signed<FNetBitArrayBase::StorageWordType>::type;` (scope `UE::Net::Private::FNetBitArrayRangedForConstIterator::AdvanceToNextSetBit`)

### `Source/Runtime/Net/Core/Public/Net/Core/NetBitArrayPrinter.h` (Public)


#### class `UE::Net::FNetBitArrayPrinter`  
`class FNetBitArrayPrinter`  
_L15-47_
- desc: FNetBitArrayPrinter utility class Collection of helper functions that can describe any given BitArray into a string for logging or debugging purposes
- L21 _public prototype_ `template <class T> static FString PrintSetSummary(const T& BitArray);` — Print the number of set bits in the bitarray
- L25 _public prototype_ `template <class T> static FString PrintZeroSummary(const T& BitArray);` — Print the number of zero bits int he bitarray
- L29 _public prototype_ `template <class T> static FString PrintSetBits(const T& BitArray);` — Print the number of set bits in the bitarray and the value of each word with set bits in them
- L33 _public prototype_ `template <class T> static FString PrintZeroBits(const T& BitArray);` — Print the number of zero bits in the bitarray and the value of each word with zero bits in them
- L37 _public prototype_ `template <class T, class U> static FString PrintDeltaSummary(const T& BitArrayA, const U& BitArrayB);` — Print the number of bits different between each array
- L41 _public prototype_ `template <class T, class U> static FString PrintDeltaBits(const T& BitArrayA, const U& BitArrayB);` — Print the number of bits different between each array and the value of each word with different bits in them
- L45 _private prototype_ `FNetBitArrayPrinter() = delete;`
- L46 _private prototype_ `~FNetBitArrayPrinter() = delete;`
- L56 _function_ `template <class T> FString FNetBitArrayPrinter::PrintSetSummary(const T& BitArray)`
- L62 _function_ `template <class T> FString FNetBitArrayPrinter::PrintZeroSummary(const T& BitArray)`
- L68 _function_ `template <class T> FString FNetBitArrayPrinter::PrintSetBits(const T& BitArray)`
- L108 _function_ `template <class T> FString FNetBitArrayPrinter::PrintZeroBits(const T& BitArray)`
- L149 _function_ `template <class T, class U> FString FNetBitArrayPrinter::PrintDeltaSummary(const T& BitArrayA, const U& BitArrayB)`
- L174 _function_ `template <class T, class U> FString FNetBitArrayPrinter::PrintDeltaBits(const T& BitArrayA, const U& BitArrayB)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Net` (scope `UE`)
- L70 _typedef_ `using WordType = typename T::StorageWordType;` (scope `UE::Net::FNetBitArrayPrinter::PrintSetBits`)
- L110 _typedef_ `using WordType = typename T::StorageWordType;` (scope `UE::Net::FNetBitArrayPrinter::PrintZeroBits`)
- L151 _typedef_ `using WordTypeT = typename T::StorageWordType;` (scope `UE::Net::FNetBitArrayPrinter::PrintDeltaSummary`)
- L152 _typedef_ `using WordTypeU = typename U::StorageWordType;` (scope `UE::Net::FNetBitArrayPrinter::PrintDeltaSummary`)
- L176 _typedef_ `using WordTypeT = typename T::StorageWordType;` (scope `UE::Net::FNetBitArrayPrinter::PrintDeltaBits`)
- L177 _typedef_ `using WordTypeU = typename U::StorageWordType;` (scope `UE::Net::FNetBitArrayPrinter::PrintDeltaBits`)

### `Source/Runtime/Net/Core/Public/Net/Core/NetCoreModule.h` (Public)


#### Free symbols / members of external scopes

- L7 _externvar_ `extern bool GUseDetailedScopeCounters;`

### `Source/Runtime/Net/Core/Public/Net/Core/NetHandle/NetHandle.h` (Public)


#### class `UE::Net::FNetHandle`  
`class FNetHandle`  
_L31-87_
- L35 _public member_ `static constexpr uint64 IdBits = (REMOTE_OBJECT_SERVER_ID_BIT_SIZE + REMOTE_OBJECT_SERIAL_NUMBER_BIT_SIZE);`
- L42 _public prototype_ `FNetHandle();`
- L43 _public prototype_ `FNetHandle(const FNetHandle& Other);`
- L44 _public prototype_ `FNetHandle(FNetHandle&& Other);`
- L46 _public prototype_ `FNetHandle& operator=(const FNetHandle& Other);`
- L47 _public prototype_ `FNetHandle& operator=(FNetHandle&& Other);`
- L49 _public prototype_ `uint64 GetId() const;`
- L50 _public prototype_ `bool IsValid() const;`
- L52 _public prototype_ `bool IsCompleteHandle() const;`
- L54 _public prototype_ `bool operator==(FNetHandle Other) const;`
- L55 _public prototype_ `bool operator<(FNetHandle Other) const;`
- L56 _public prototype_ `bool operator!=(FNetHandle Other) const;`
- L58 _public prototype_ `FString ToString() const;`
- L72 _private prototype_ `FNetHandle(FObjectKey ObjectKey);`
- L73 _private prototype_ `explicit FNetHandle(FInternalValue InInternalValue);`
- L74 _private prototype_ `explicit FNetHandle(uint64 InInternalValue);`
- L76 _private prototype_ `uint64 GetInternalValue() const;`
- L89 _function_ `inline FNetHandle::FNetHandle() : Value()`
- L94 _function_ `inline FNetHandle::FNetHandle(const FNetHandle& Other) : Value(Other.Value)`
- L99 _function_ `inline FNetHandle::FNetHandle(FNetHandle&& Other) : Value(Other.Value)`
- L104 _function_ `inline FNetHandle::FNetHandle(FObjectKey ObjectKey) #if UE_WITH_REMOTE_OBJECT_HANDLE : Value(ObjectKey.GetRemoteId()) #else : Value(ObjectKey) #endif`
- L113 _function_ `inline FNetHandle::FNetHandle(FInternalValue InInternalValue) #if UE_WITH_REMOTE_OBJECT_HANDLE : Value(BitCast<FRemoteObjectId>(InInternalValue)) #else : Value(BitCast<FObjectKey>(InInternalValue)) #endif`
- L122 _function_ `inline FNetHandle::FNetHandle(uint64 InInternalValue) #if UE_WITH_REMOTE_OBJECT_HANDLE : Value(BitCast<FRemoteObjectId>(InInternalValue)) #else : Value(BitCast<FObjectKey>(InInternalValue)) #endif`
- L131 _function_ `inline uint64 FNetHandle::GetInternalValue() const`
- L136 _function_ `inline FNetHandle& FNetHandle::operator=(const FNetHandle& Other)`
- L142 _function_ `inline FNetHandle& FNetHandle::operator=(FNetHandle&& Other)`
- L148 _function_ `inline uint64 FNetHandle::GetId() const`
- L157 _function_ `inline bool FNetHandle::IsValid() const`
- L166 _function_ `inline bool FNetHandle::IsCompleteHandle() const`
- L175 _function_ `inline bool FNetHandle::operator==(FNetHandle Other) const`
- L180 _function_ `inline bool FNetHandle::operator<(FNetHandle Other) const`
- L185 _function_ `inline bool FNetHandle::operator!=(FNetHandle Other) const`

#### struct `UE::Net::FNetHandle::FInternalValue`  
`struct FInternalValue`  
_L66-70_
- L68 _public member_ `uint32 Id;`
- L69 _public member_ `uint32 Epoch;`

#### union `UE::Net::FNetHandle::(anonymous)`  
``  
_L79-86_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Net`)
- L20 _prototype_ `FAnsiStringBuilderBase& operator<<(FAnsiStringBuilderBase& Builder, const UE::Net::FNetHandle& NetHandle);`
- L21 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, const UE::Net::FNetHandle& NetHandle);`
- L22 _prototype_ `FWideStringBuilderBase& operator<<(FWideStringBuilderBase& Builder, const UE::Net::FNetHandle& NetHandle);`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Net` (scope `UE`)
- L81 _member_ `FRemoteObjectId Value;` (scope `UE::Net::FNetHandle::__anon5ec0c49e010a`)
- L85 _member_ `FInternalValue InternalValue;` (scope `UE::Net::FNetHandle::__anon5ec0c49e010a`)
- L190 _function_ `inline uint32 GetTypeHash(FNetHandle Handle)` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/NetHandle/NetHandleManager.h` (Public)


#### class `UE::Net::FNetHandleDestroyer`  
`class FNetHandleDestroyer`  
_L14-23_
- desc: This class restricts access to DestroyNetHandle functionality as early destruction prevents further dirty state tracking.
- L18 _private prototype_ `static void DestroyNetHandle(FNetHandle Handle);` — Calls FNetHandleManager::DestroyNetHandle(Handle).
- L58 _function_ `inline void FNetHandleDestroyer::DestroyNetHandle(FNetHandle Handle)`

#### class `UE::Net::FNetHandleManager`  
`class FNetHandleManager`  
_L26-56_
- desc: Manages the association between a UObject and a FNetHandle, which can be used to uniquely identify a replicated object for the lifetime of the application.
- L30 _public prototype_ `static FNetHandle GetNetHandle(const UObject*);` — Returns the NetHandle for an object if it's present. Assumes Init() has been called.
- L33 _public prototype_ `static FNetHandle GetOrCreateNetHandle(const UObject*);` — Returns an existing NetHandle for an object if it's present or creates one if it's not. Assumes Init() has been called.
- L36 _public prototype_ `static FNetHandle MakeNetHandleFromId(uint32 Id);` — Returns a NetHandle given an Id that has previously been extracted from a valid NetHandle. The behavior is implementation defined if the Id was not extracted from a valid NetHandle.
- L42 _private prototype_ `static void DestroyNetHandle(FNetHandle Handle);` — Destroys a NetHandle and removes the association between it and the object such that GetObject(Handle) will return nullptr. Assumes Init() has been called.
- L48 _protected prototype_ `static void Init();` — Creates a new instance that is used by functions that need it. Checks that no instance exists.
- L51 _protected prototype_ `static void Deinit();` — Destroys the instance if it exists.
- L55 _private member_ `static FPimpl* Instance;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/Net/Core/Public/Net/Core/NetToken/NetToken.h` (Public)


#### class `UE::Net::FNetToken`  
`class FNetToken`  
_L21-108_
- L24 _public typedef_ `typedef uint32 FTypeId;`
- L47 _public function_ `FNetToken() : Value(Invalid)`
- L52 _public function_ `inline bool IsValid() const`
- L57 _public function_ `bool IsAssignedByAuthority() const`
- L62 _public function_ `uint32 GetIndex() const`
- L67 _public function_ `FTypeId GetTypeId() const`
- L72 _public function_ `bool operator==(const FNetToken& Other) const`
- L77 _public prototype_ `FString ToString() const;`
- L87 _private function_ `explicit FNetToken(uint32 InTypeId, uint32 InIndex, ENetTokenAuthority Authority)`
- L118 _function_ `inline FString FNetToken::ToString() const`

#### enum `UE::Net::FNetToken::(anonymous)`  
`enum : uint32`  
_L26-26_

#### enum `UE::Net::FNetToken::(anonymous)`  
`enum : uint32`  
_L28-28_

#### enum `UE::Net::FNetToken::(anonymous)`  
`enum : uint32`  
_L29-29_

#### enum `UE::Net::FNetToken::(anonymous)`  
`enum : uint32`  
_L32-32_
- desc: How many bits we use to express the TypeId for NetTokens, Increasing this value will break network compatibility and might need versioning for replays.

#### enum `UE::Net::FNetToken::(anonymous)`  
`enum : uint32`  
_L35-35_
- desc: How many bits we use to express the index part of NetTokens

#### enum `UE::Net::FNetToken::(anonymous)`  
`enum : uint32`  
_L37-37_

#### enum `UE::Net::FNetToken::(anonymous)`  
`enum : uint32`  
_L38-38_

#### enum `UE::Net::FNetToken::ENetTokenAuthority`  
`enum class ENetTokenAuthority`  
_L40-44_
- L42 _public enumerator_ `None`
- L43 _public enumerator_ `Authority`

#### union `UE::Net::FNetToken::(anonymous)`  
``  
_L98-107_

#### struct `UE::Net::FNetToken::__anon387c22e8080a::(anonymous)`  
``  
_L100-105_

#### class `UE::Net::FNetTokenResolveContext`  
`class FNetTokenResolveContext`  
_L111-116_
- desc: Contains necessary context to resolve NetTokens
- L114 _public member_ `FNetTokenStore* NetTokenStore = nullptr;`
- L115 _public member_ `const FNetTokenStoreState* RemoteNetTokenStoreState = nullptr;`

#### enum `TIsPODType::(anonymous)`  
`template <> struct TIsPODType<UE::Net::FNetToken>`  
_L127-127_

#### struct `TIsPODType`  
`template <> struct TIsPODType<UE::Net::FNetToken>`  
_L127-127_

#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetToken, Log, All);`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Net` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Net` (scope `UE`)
- L26 _enumerator_ `enum : uint32 { Invalid = 0U }; enum : uint32 { InvalidTokenTypeId = ~FTypeId(0) }; enum : uint32 { InvalidTokenIndex = 0U }; enum : uint32 { TokenTypeIdBits = 3U };` (scope `UE::Net::FNetToken::__anon387c22e80103`)
- L28 _enumerator_ `enum : uint32 { InvalidTokenTypeId = ~FTypeId(0) }; enum : uint32 { InvalidTokenIndex = 0U }; enum : uint32 { TokenTypeIdBits = 3U }; enum : uint32 { TokenBits = 20U };` (scope `UE::Net::FNetToken::__anon387c22e80203`)
- L29 _enumerator_ `enum : uint32 { InvalidTokenIndex = 0U }; enum : uint32 { TokenTypeIdBits = 3U }; enum : uint32 { TokenBits = 20U };` (scope `UE::Net::FNetToken::__anon387c22e80303`)
- L32 _enumerator_ `enum : uint32 { TokenTypeIdBits = 3U }; enum : uint32 { TokenBits = 20U }; enum : uint32 { MaxTypeIdCount = 1U << TokenTypeIdBits }; enum : uint32 { MaxNetTokenCount = 1U << TokenBits };` (scope `UE::Net::FNetToken::__anon387c22e80403`) — How many bits we use to express the TypeId for NetTokens, Increasing this value will break network compatibility and might need versioning for replays.
- L35 _enumerator_ `enum : uint32 { TokenBits = 20U }; enum : uint32 { MaxTypeIdCount = 1U << TokenTypeIdBits }; enum : uint32 { MaxNetTokenCount = 1U << TokenBits }; enum class ENetTokenAuthority { None,` (scope `UE::Net::FNetToken::__anon387c22e80503`) — How many bits we use to express the index part of NetTokens
- L37 _enumerator_ `enum : uint32 { MaxTypeIdCount = 1U << TokenTypeIdBits }; enum : uint32 { MaxNetTokenCount = 1U << TokenBits }; enum class ENetTokenAuthority { None, Authority, };` (scope `UE::Net::FNetToken::__anon387c22e80603`)
- L38 _enumerator_ `enum : uint32 { MaxNetTokenCount = 1U << TokenBits }; enum class ENetTokenAuthority { None, Authority, };` (scope `UE::Net::FNetToken::__anon387c22e80703`)
- L79 _function_ `friend uint32 GetTypeHash(const FNetToken& Token)` (scope `UE::Net`)
- L101 _member_ `uint32 Index : TokenBits;` (scope `UE::Net::FNetToken::__anon387c22e8080a::__anon387c22e80908`)
- L102 _member_ `uint32 TypeId : TokenTypeIdBits;` (scope `UE::Net::FNetToken::__anon387c22e8080a::__anon387c22e80908`)
- L103 _member_ `uint32 bIsAssignedByAuthority : 1U;` (scope `UE::Net::FNetToken::__anon387c22e8080a::__anon387c22e80908`)
- L104 _member_ `uint32 Padding : 32 - TokenTypeIdBits - TokenBits - 1U;` (scope `UE::Net::FNetToken::__anon387c22e8080a::__anon387c22e80908`)
- L106 _member_ `uint32 Value;` (scope `UE::Net::FNetToken::__anon387c22e8080a`)
- L127 _enumerator_ `template <> struct TIsPODType<UE::Net::FNetToken> { enum { Value = true }; };` (scope `TIsPODType::__anon387c22e80a03`)

### `Source/Runtime/Net/Core/Public/Net/Core/NetToken/NetTokenExportContext.h` (Public)


#### class `UE::Net::FNetTokenExportContext`  
`class FNetTokenExportContext`  
_L20-41_
- desc: Contains necessary context to export NetTokens
- L23 _public typedef_ `typedef TArray<UE::Net::FNetToken, TInlineAllocator<4>> FNetTokenExports;`
- L25 _public prototype_ `inline FNetTokenStore* GetNetTokenStore();`
- L26 _public prototype_ `void AddNetTokenPendingExport(UE::Net::FNetToken NetToken);`
- L27 _public prototype_ `void AppendNetTokensPendingExport(TArrayView<const UE::Net::FNetToken> NetTokens);`
- L28 _public prototype_ `TArrayView<const UE::Net::FNetToken> GetNetTokensPendingExport() const;`
- L29 _public prototype_ `static FNetTokenExportContext* GetNetTokenExportContext(FArchive& Ar);`
- L34 _private prototype_ `FNetTokenExportContext(FNetTokenStore* InNetTokenStore, FNetTokenExports* InNetTokensPendingExport);`
- L37 _private member_ `FNetTokenStore* NetTokenStore = nullptr;` — We can only export if we have a NetTokenStore
- L40 _private member_ `FNetTokenExports* NetTokensPendingExport = nullptr;` — We also need a target where to store exports.
- L56 _function_ `FNetTokenStore* FNetTokenExportContext::GetNetTokenStore()`

#### class `UE::Net::FNetTokenExportScope`  
`class FNetTokenExportScope`  
_L44-54_
- desc: Simple scope to make sure we set the correct ExportContext and restore the old one when we exit the scope
- L47 _public prototype_ `FNetTokenExportScope(FNetBitWriter& InNetBitWriter, UE::Net::FNetTokenStore* InNetTokenStore, FNetTokenExportContext::FNetTokenExports& TargetExports, const char* InDebugName = "Non`
- L48 _public prototype_ `~FNetTokenExportScope();`
- L50 _public member_ `FNetTokenExportContext ExportContext;`
- L51 _public member_ `FNetBitWriter& NetBitWriter;`
- L52 _public member_ `FNetTokenExportContext* OldExportContext;`
- L53 _public member_ `const char* DebugName;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/Net/Core/Public/Net/Core/PropertyConditions/PropertyConditions.h` (Public)


#### class `UE::Net::Private::FNetPropertyConditionManager`  
`class FNetPropertyConditionManager`  
_L19-59_
- L22 _public prototype_ `FNetPropertyConditionManager();`
- L23 _public prototype_ `~FNetPropertyConditionManager();`
- L25 _public prototype_ `static FNetPropertyConditionManager& Get();`
- L27 _public prototype_ `void SetPropertyActive(const UObject* Object, const uint16 RepIndex, const bool bActive);`
- L28 _public prototype_ `void SetPropertyActiveOverride(const UObject* Object, const uint16 RepIndex, const bool bIsActive);`
- L29 _public prototype_ `void SetPropertyDynamicCondition(const UObject* Object, const uint16 RepIndex, const ELifetimeCondition Condition);`
- L31 _public prototype_ `void NotifyObjectDestroyed(const FObjectKey ObjectKey);`
- L33 _public prototype_ `TSharedPtr<FRepChangedPropertyTracker> FindOrCreatePropertyTracker(const FObjectKey ObjectKey);`
- L34 _public prototype_ `TSharedPtr<FRepChangedPropertyTracker> FindPropertyTracker(const FObjectKey ObjectKey) const;`
- L36 _public prototype_ `void LogMemory(FOutputDevice& Ar);`
- L50 _private prototype_ `void PostGarbageCollect();`
- L52 _private member_ `FDelegateHandle PostGarbageCollectHandle;`
- L54 _private member_ `TMap<FObjectKey, TSharedPtr<FRepChangedPropertyTracker>> PropertyTrackerMap;`
- L56 _private member_ `FObjectKey LastFoundTrackerKey;`
- L57 _private member_ `FRepChangedPropertyTracker* LastFoundTracker = nullptr;`
- L58 _private member_ `bool bAllowCreateTrackerFromSetPropertyActiveOverride = false;`

#### class `UE::Net::Private::FNetPropertyConditionManager::FAllowCreateTrackerFromSetPropertyActiveOverrideScope`  
`class FAllowCreateTrackerFromSetPropertyActiveOverrideScope`  
_L38-45_
- L41 _public function_ `FAllowCreateTrackerFromSetPropertyActiveOverrideScope(FNetPropertyConditionManager& ConditionManager) : GuardValue(ConditionManager.bAllowCreateTrackerFromSetPropertyActiveOverride, true)`
- L44 _private member_ `TGuardValue<bool> GuardValue;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Net` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/PropertyConditions/PropertyConditionsDelegates.h` (Public)


#### class `UE::Net::Private::FPropertyConditionDelegates`  
`class FPropertyConditionDelegates`  
_L12-24_
- L15 _public typedef_ `using FOnPropertyCustomConditionChanged = TMulticastDelegate<void(const UObject* OwningObject, const uint16 RepIndex, const bool bActive)>;`
- L16 _public typedef_ `using FOnPropertyDynamicConditionChanged = TMulticastDelegate<void(const UObject* OwningObject, const uint16 RepIndex, const ELifetimeCondition Condition)>;`
- L18 _public function_ `static FOnPropertyCustomConditionChanged& GetOnPropertyCustomConditionChangedDelegate()`
- L19 _public function_ `static FOnPropertyDynamicConditionChanged& GetOnPropertyDynamicConditionChangedDelegate()`
- L22 _private member_ `static FOnPropertyCustomConditionChanged OnPropertyCustomConditionChangedDelegate;`
- L23 _private member_ `static FOnPropertyDynamicConditionChanged OnPropertyDynamicConditionChangedDelegate;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Net` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/PropertyConditions/RepChangedPropertyTracker.h` (Public)


#### class `FRepChangedPropertyTracker`  
`class FRepChangedPropertyTracker`  
_L22-61_
- desc: This class is used to store meta data about properties that is shared between connections, including whether or not a given property is Conditional, Active, and any external data that may be needed for Replays. TODO: This class (and arguably IRepChangedPropertyTracker) should be renamed to reflect what they actually do now.
- L25 _public prototype_ `FRepChangedPropertyTracker() = delete;`
- L26 _public prototype_ `FRepChangedPropertyTracker(FCustomPropertyConditionState&& InActiveState);`
- L28 _public prototype_ `~FRepChangedPropertyTracker() = default;`
- L30 _public prototype_ `void CountBytes(FArchive& Ar) const;`
- L32 _public function_ `bool IsParentActive(uint16 ParentIndex) const`
- L37 _public function_ `int32 GetParentCount() const`
- L42 _public function_ `ELifetimeCondition GetDynamicCondition(uint16 ParentIndex) const`
- L47 _public function_ `uint32 GetDynamicConditionChangeCounter() const`
- L56 _private prototype_ `void SetDynamicCondition(const UObject* OwningObject, const uint16 RepIndex, const ELifetimeCondition Condition);` — Called from FNetPropertyConditionManager
- L57 _private prototype_ `void SetCustomIsActiveOverride(const UObject* OwningObject, const uint16 RepIndex, const bool bIsActive);`
- L60 _private member_ `FCustomPropertyConditionState ActiveState;` — Activation data for top level Properties on the given Actor / Object.

### `Source/Runtime/Net/Core/Public/Net/Core/PushModel/PushModel.h` (Public)


#### struct `UEPushModelPrivate::FNetPushObjectId`  
`struct FNetPushObjectId`  
_L288-303_
- desc: The ID need to be able to handle both Iris and non-Iris replication.
- L290 _public function_ `FNetPushObjectId() : Value(0xFFFFFFFFFFFFFFFFULL)`
- L291 _public function_ `explicit FNetPushObjectId(FNetLegacyPushObjectId Id)`
- L292 _public function_ `explicit FNetPushObjectId(FNetIrisPushObjectId Id)`
- L294 _public function_ `bool IsValid() const`
- L295 _public function_ `bool IsIrisId() const`
- L296 _public function_ `uint64 GetValue() const`
- L298 _public function_ `FNetLegacyPushObjectId GetLegacyPushObjectId() const`
- L299 _public function_ `FNetIrisPushObjectId GetIrisPushObjectId() const`
- L302 _private member_ `uint64 Value;`

#### struct `UEPushModelPrivate::FPushModelPerNetDriverHandle`  
`struct FPushModelPerNetDriverHandle`  
_L306-334_
- desc: A handle that can be used to refer to a Push Model Object State owned by a specific Net Driver.
- L308 _public function_ `FPushModelPerNetDriverHandle(const FNetPushPerNetDriverId InNetDriverId, const FNetLegacyPushObjectId InObjectId) : NetDriverId(InNetDriverId) , ObjectId(InObjectId)`
- L320 _public member_ `const FNetPushPerNetDriverId NetDriverId;` — Used by Push Model code to find a specific Net Driver state. Note, this **does not** have a global mapping to a given NetDriver. That is, two FPushModelPerNetDriver handles that identify Push Model Object's that are both tracked by the same Net Driver may report different NetDriver IDs.
- L323 _public member_ `const FNetLegacyPushObjectId ObjectId;` — The "globally unique" ID that is used to refer to the Push Model Object.
- L325 _public function_ `const bool IsValid() const`
- L330 _public function_ `static FPushModelPerNetDriverHandle MakeInvalidHandle()`

#### Free symbols / members of external scopes

- L278 _namespace_ `namespace UEPushModelPrivate`
- L283 _typedef_ `using FNetPushPerNetDriverId = int32;` (scope `UEPushModelPrivate`)
- L284 _typedef_ `using FNetLegacyPushObjectId = int32;` (scope `UEPushModelPrivate`)
- L285 _typedef_ `using FNetIrisPushObjectId = uint64;` (scope `UEPushModelPrivate`)
- L336 _externvar_ `extern bool bIsPushModelEnabled;` (scope `UEPushModelPrivate`)
- L337 _externvar_ `extern bool bMakeBpPropertiesPushModel;` (scope `UEPushModelPrivate`)
- L340 _function_ `static const bool IsPushModelEnabled()` (scope `UEPushModelPrivate`) — @return Whether or not PushModel is currently enabled. See "net.IsPushModelEnabled."
- L346 _function_ `static const bool MakeBpPropertiesPushModel()` (scope `UEPushModelPrivate`) — @return Whether or not Blueprint Properties will use Push Model. See "net.MakeBpPropertiesPushModel."
- L352 _prototype_ `bool IsHandleCreationAllowed();` (scope `UEPushModelPrivate`) — Are we allowed to create new push model handles
- L355 _prototype_ `void SetHandleCreationAllowed(bool bAllow);` (scope `UEPushModelPrivate`) — Control if we are allowed to create pushmodel handles
- L357 _function_ `static FString ToString(const FNetPushObjectId Id)` (scope `UEPushModelPrivate`)
- L378 _prototype_ `void MarkPropertyDirty(const UObject* Object, const FNetPushObjectId ObjectId, const int32 RepIndex);` (scope `UEPushModelPrivate`) — Marks a specified property as dirty, causing it to be compared the next time the owner is considered for Replication. Note, C-Style Array Properties (Static Array is the name used everywhere else here), will have a RepIndex equal to UProperty::RepIndex + ArrayIndex. MARK_PROPERTY_DIRTY_FROM_NAME and MARK_PROPERTY_DIRTY_FROM_NAME_STATIC_ARRAY are preferred over MARK_PROPERTY_DIRTY and MARK_PROPERTY_DIRTY_STATIC_ARRAY, because they offer compile time warnings for things like invalid Class, Property, Static Array Index, etc., and they'll use compile time constants instead of relying on UProperty::RepIndex. @param Object	The object we're marking dirty. @param ObjectId	The push ID for the object we're marking dirty. @param RepIndex	The index of the property we're marking dirty. UProperty::RepIndex.
- L395 _prototype_ `void MarkPropertyDirty(const UObject* Object, const FNetPushObjectId ObjectId, const int32 StartRepIndex, const int32 EndRepIndex);` (scope `UEPushModelPrivate`) — Marks a range of properties as dirty, causing it to be compared the next time the owner is considered for Replication. This is primarily used to mark entire Static Arrays MARK_PROPERTY_DIRTY_FROM_NAME and MARK_PROPERTY_DIRTY_FROM_NAME_STATIC_ARRAY are preferred over MARK_PROPERTY_DIRTY and MARK_PROPERTY_DIRTY_STATIC_ARRAY, because they offer compile time warnings for things like invalid Class, Property, Static Array Index, etc., and they'll use compile time constants instead of relying on UProperty::RepIndex. @param Object	The object we're marking dirty. @param ObjectId	The push ID for the object we're marking dirty. @param RepIndex	The index of the property we're marking dirty. UProperty::RepIndex.
- L402 _prototype_ `const FPushModelPerNetDriverHandle AddPushModelObject(const FObjectKey ObjectId, const uint16 NumberOfReplicatedProperties);` (scope `UEPushModelPrivate`)
- L403 _prototype_ `void RemovePushModelObject(const FPushModelPerNetDriverHandle Handle);` (scope `UEPushModelPrivate`)
- L405 _prototype_ `class FPushModelPerNetDriverState* GetPerNetDriverState(const FPushModelPerNetDriverHandle Handle);` (scope `UEPushModelPrivate`)
- L407 _prototype_ `bool DoesHaveDirtyPropertiesOrRecentlyCollectedGarbage(const FPushModelPerNetDriverHandle Handle);` (scope `UEPushModelPrivate`)
- L409 _prototype_ `bool ValidateObjectIdReassignment(FNetLegacyPushObjectId CurrentId, FNetLegacyPushObjectId NewId);` (scope `UEPushModelPrivate`)
- L411 _prototype_ `void LogMemory(FOutputDevice& Ar);` (scope `UEPushModelPrivate`)
- L414 _delegate_ `DECLARE_DELEGATE_ThreeParams(FIrisMarkPropertyDirty, const UObject*, UEPushModelPrivate::FNetIrisPushObjectId, const int32);` — For internal use only.
- L414 _prototype_ `DECLARE_DELEGATE_ThreeParams(FIrisMarkPropertyDirty, const UObject*, UEPushModelPrivate::FNetIrisPushObjectId, const int32);` (scope `UEPushModelPrivate`) — For internal use only.
- L415 _delegate_ `DECLARE_DELEGATE_FourParams(FIrisMarkPropertiesDirty, const UObject*, UEPushModelPrivate::FNetIrisPushObjectId, const int32, const int32);`
- L415 _prototype_ `DECLARE_DELEGATE_FourParams(FIrisMarkPropertiesDirty, const UObject*, UEPushModelPrivate::FNetIrisPushObjectId, const int32, const int32);` (scope `UEPushModelPrivate`)
- L417 _prototype_ `void SetIrisMarkPropertyDirtyDelegate(const FIrisMarkPropertyDirty& Delegate);` (scope `UEPushModelPrivate`)
- L418 _prototype_ `void SetIrisMarkPropertiesDirtyDelegate(const FIrisMarkPropertiesDirty& Delegate);` (scope `UEPushModelPrivate`)
- L422 _macro_ `#define CONDITIONAL_ON_PUSH_MODEL(Work) if (UEPushModelPrivate::IsPushModelEnabled()) { Work; }`
- L423 _macro_ `#define IS_PUSH_MODEL_ENABLED() UEPushModelPrivate::IsPushModelEnabled()`
- L424 _macro_ `#define PUSH_MAKE_BP_PROPERTIES_PUSH_MODEL() (UEPushModelPrivate::IsPushModelEnabled() && UEPushModelPrivate::MakeBpPropertiesPushModel())`
- L426 _macro_ `#define GET_PROPERTY_REP_INDEX(ClassName, PropertyName) (int32)ClassName::ENetFields_Private::PropertyName`
- L427 _macro_ `#define GET_PROPERTY_REP_INDEX_STATIC_ARRAY_START(ClassName, PropertyName) ((int32)ClassName::ENetFields_Private::PropertyName ## _STATIC_ARRAY)`
- L428 _macro_ `#define GET_PROPERTY_REP_INDEX_STATIC_ARRAY_END(ClassName, PropertyName) ((int32)ClassName::ENetFields_Private::PropertyName ## _STATIC_ARRAY_END)`
- L429 _macro_ `#define GET_PROPERTY_REP_INDEX_STATIC_ARRAY_INDEX(ClassName, PropertyName, ArrayIndex) (GET_PROPERTY_REP_INDEX_STATIC_ARRAY_START(ClassName, PropertyName) + ArrayIndex)`
- L431 _macro_ `#define IS_PROPERTY_REPLICATED(Property) (0 != (EPropertyFlags::CPF_Net & Property->PropertyFlags))`
- L433 _macro_ `#define CONDITIONAL_ON_OBJECT_NET_ID(Object, Work) { const UEPushModelPrivate::FNetPushObjectId PrivatePushId(Object->GetNetPushId()); Work; }`
- L434 _macro_ `#define CONDITIONAL_ON_OBJECT_NET_ID_DYNAMIC(Object, Work) { const UEPushModelPrivate::FNetPushObjectId PrivatePushId(Object->GetNetPushIdDynamic()); Work; }`
- L435 _macro_ `#define CONDITIONAL_ON_REP_INDEX_AND_OBJECT_NET_ID(Object, Property, Work) if (IS_PROPERTY_REPLICATED(Property)) { const UEPushModelPrivate::FNetPushObjectId PrivatePushId(Object->GetNetPushIdDynamic()); Work; }`
- L440 _macro_ `#define MARK_PROPERTY_DIRTY_UNSAFE(Object, RepIndex) CONDITIONAL_ON_OBJECT_NET_ID_DYNAMIC(Object, UEPushModelPrivate::MarkPropertyDirty(Object, PrivatePushId, RepIndex))` — Marks a property dirty by RepIndex without doing additional rep index validation.
- L443 _macro_ `#define MARK_PROPERTY_DIRTY(Object, Property) CONDITIONAL_ON_REP_INDEX_AND_OBJECT_NET_ID(Object, Property, UEPushModelPrivate::MarkPropertyDirty(Object, PrivatePushId, Property->RepIndex))` — Marks a property dirty by UProperty*, validating that it's actually a replicated property.
- L447 _macro_ `#define MARK_PROPERTY_DIRTY_STATIC_ARRAY_INDEX(Object, Property, ArrayIndex) CONDITIONAL_ON_REP_INDEX_AND_OBJECT_NET_ID(Object, Property, UEPushModelPrivate::MarkPropertyDirty(Object, PrivatePushId, Property->RepIndex + ArrayIndex))` — Marks a static array property dirty given, the Object, UProperty*, and Index.
- L450 _macro_ `#define MARK_PROPERTY_DIRTY_STATIC_ARRAY(Object, Property) CONDITIONAL_ON_REP_INDEX_AND_OBJECT_NET_ID(Object, Property, UEPushModelPrivate::MarkPropertyDirty(Object, PrivatePushId, Property->RepIndex, Property->RepIndex + Property->ArrayDim` — Marks all elements of a static array property dirty, given the Object and UProperty*
- L454 _macro_ `#define MARK_PROPERTY_DIRTY_FROM_NAME(ClassName, PropertyName, Object) CONDITIONAL_ON_OBJECT_NET_ID(Object, UEPushModelPrivate::MarkPropertyDirty(Object, PrivatePushId, GET_PROPERTY_REP_INDEX(ClassName, PropertyName)))` — Marks a property dirty, given the Class Name, Property Name, and Object. This will fail to compile if the Property or Class aren't valid.
- L457 _macro_ `#define MARK_PROPERTY_DIRTY_FROM_NAME_STATIC_ARRAY_INDEX(ClassName, PropertyName, ArrayIndex, Object) CONDITIONAL_ON_OBJECT_NET_ID(Object, UEPushModelPrivate::MarkPropertyDirty(Object, PrivatePushId, GET_PROPERTY_REP_INDEX_STATIC_ARRAY_INDE` — Marks a static array property dirty, given the Class Name, Property Name, Index, and Object. This will fail to compile if the Property and Class aren't valid. Callers are responsible for validating the index.
- L460 _macro_ `#define MARK_PROPERTY_DIRTY_FROM_NAME_STATIC_ARRAY(ClassName, PropertyName, Object) CONDITIONAL_ON_OBJECT_NET_ID(Object, UEPushModelPrivate::MarkPropertyDirty(Object, PrivatePushId, GET_PROPERTY_REP_INDEX_STATIC_ARRAY_START(ClassName, Prope` — Marks an entire static array property dirty, given the Class Name, Property Name, and Object. This will fail to compile if the Property or Class aren't valid.
- L466 _macro_ `#define COMPARE_ASSIGN_AND_MARK_PROPERTY_DIRTY(ClassName, PropertyName, NewValue, Object, ...) \` — This is used to reduce lines of code (mostly in setters) by doing the comparison check before changing the value and marking dirty only if we have changed the value. This is best if used for things like ints, floats, pointers, but not something like a struct because of the memcmp cost.
- L477 _macro_ `#define UE_NET_SET_IRIS_MARK_PROPERTY_DIRTY_DELEGATE(Delegate) UEPushModelPrivate::SetIrisMarkPropertyDirtyDelegate(Delegate)`
- L478 _macro_ `#define UE_NET_SET_IRIS_MARK_PROPERTIES_DIRTY_DELEGATE(Delegate) UEPushModelPrivate::SetIrisMarkPropertiesDirtyDelegate(Delegate)`
- L482 _macro_ `#define MARK_PROPERTY_DIRTY_UNSAFE(Object, RepIndex)`
- L483 _macro_ `#define MARK_PROPERTY_DIRTY(Object, Property)`
- L484 _macro_ `#define MARK_PROPERTY_DIRTY_STATIC_ARRAY_INDEX(Object, RepIndex, ArrayIndex)`
- L485 _macro_ `#define MARK_PROPERTY_DIRTY_STATIC_ARRAY(Object, RepIndex, ArrayIndex)`
- L487 _macro_ `#define MARK_PROPERTY_DIRTY_FROM_NAME(ClassName, PropertyName, Object)`
- L488 _macro_ `#define MARK_PROPERTY_DIRTY_FROM_NAME_STATIC_ARRAY_INDEX(ClassName, PropertyName, ArrayIndex, Object)`
- L489 _macro_ `#define MARK_PROPERTY_DIRTY_FROM_NAME_STATIC_ARRAY(ClassName, PropertyName, ArrayIndex, Object)`
- L492 _macro_ `#define GET_PROPERTY_REP_INDEX(ClassName, PropertyName) INDEX_NONE`
- L493 _macro_ `#define GET_PROPERTY_REP_INDEX_STATIC_ARRAY(ClassName, PropertyName, ArrayIndex) INDEX_NONE`
- L495 _macro_ `#define IS_PUSH_MODEL_ENABLED() false`
- L496 _macro_ `#define PUSH_MAKE_BP_PROPERTIES_PUSH_MODEL() false`
- L507 _macro_ `#define UE_NET_SET_IRIS_MARK_PROPERTY_DIRTY_DELEGATE(...)`
- L508 _macro_ `#define UE_NET_SET_IRIS_MARK_PROPERTIES_DIRTY_DELEGATE(...)`

### `Source/Runtime/Net/Core/Public/Net/Core/PushModel/PushModelMacros.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define WITH_PUSH_MODEL 0`
- L9 _macro_ `#define DISABLE_PUSH_MODEL_VALIDATION 0`
- L10 _macro_ `#define WITH_PUSH_VALIDATION_SUPPORT (WITH_PUSH_MODEL && !(UE_BUILD_SHIPPING || UE_BUILD_TEST || DISABLE_PUSH_MODEL_VALIDATION))`
- L16 _macro_ `#define REPLICATED_BASE_CLASS(ClassName) \`
- L26 _macro_ `#define REPLICATED_BASE_CLASS(ClassName)`

### `Source/Runtime/Net/Core/Public/Net/Core/Serialization/QuantizedVectorSerialization.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Net` (scope `UE`)
- L19 _prototype_ `bool WriteQuantizedVector(const int32 Scale, const FVector3d& Value, FArchive& Ar);` (scope `UE::Net`) — Scales the supplied vector and then rounds to an integer value which is serialized. If scaling cannot improve the precision of any of the components the value will not be scaled before rounding. If scaling produces a value that would cause any of the components to be clamped then serialization will fallback to send full precision components. N.B. The Vector3f and Vector3d variants are bit compatible with eachother, but it's discouraged to mix types when writing and reading.
- L20 _prototype_ `bool WriteQuantizedVector(const int32 Scale, const FVector3f& Value, FArchive& Ar);` (scope `UE::Net`)
- L23 _prototype_ `bool ReadQuantizedVector(const int32 Scale, FVector3d& Value, FArchive& Ar);` (scope `UE::Net`) — Reads a quantized vector that was written using WriteQuantizedVector with the same scale.
- L24 _prototype_ `bool ReadQuantizedVector(const int32 Scale, FVector3f& Value, FArchive& Ar);` (scope `UE::Net`)
- L27 _prototype_ `FVector3d QuantizeVector(const int32 Scale, const FVector3d& Value);` (scope `UE::Net`) — Quantize a vector using the same quantization as WriteQuantizedVector followed by ReadQuantizedVector.
- L28 _prototype_ `FVector3f QuantizeVector(const int32 Scale, const FVector3f& Value);` (scope `UE::Net`)
- L31 _function_ `template<int32 Scale> bool SerializeQuantizedVector(FVector& Value, FArchive& Ar)` (scope `UE::Net`)

### `Source/Runtime/Net/Core/Public/Net/Core/Trace/NetDebugName.h` (Public)


#### struct `UE::Net::FNetDebugName`  
`struct FNetDebugName`  
_L16-20_
- L18 _public member_ `const TCHAR* Name = nullptr;`
- L19 _public member_ `mutable FNetDebugNameId DebugNameId = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Net` (scope `UE`)
- L14 _typedef_ `typedef uint32 FNetDebugNameId;` (scope `UE::Net`) — NetDebugName, carries both string pointer and a debugname id assigned by the persistent debug storage. DebugNameId is used to be able to avoid hashing already seen NetDebugNames
- L23 _prototype_ `const FNetDebugName* CreatePersistentNetDebugName(const TCHAR* Name, uint32 NameLen);` (scope `UE::Net`)
- L24 _function_ `inline const FNetDebugName* CreatePersistentNetDebugName(const TCHAR* Name)` (scope `UE::Net`)
- L26 _prototype_ `FNetDebugName const* GetReliabilityNetDebugName(bool bIsReliable);` (scope `UE::Net`)
- L30 _function_ `inline const TCHAR* ToCStr(const UE::Net::FNetDebugName* DebugName)`

### `Source/Runtime/Net/Core/Public/Net/Core/Trace/NetTrace.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_NET_TRACE_CREATE_COLLECTOR(Verbosity) UE_NET_TRACE_INTERNAL_CREATE_COLLECTOR(Verbosity)` — Create New Collector
- L13 _macro_ `#define UE_NET_TRACE_DESTROY_COLLECTOR(Collector) FNetTrace::DestroyTraceCollector(Collector)` — Create Destroy Collector
- L20 _macro_ `#define UE_NET_TRACE_SCOPE(Name, Stream, Collector, Verbosity) UE_NET_TRACE_INTERNAL_SCOPE(Name, Stream, Collector, Verbosity)` — Simple NetTraceScope with a static name
- L23 _macro_ `#define UE_NET_TRACE_OBJECT_SCOPE(HandleOrNetGUID, Stream, Collector, Verbosity) UE_NET_TRACE_INTERNAL_OBJECT_SCOPE(HandleOrNetGUID, Stream, Collector, Verbosity)` — NetTraceScope that uses NetHandle or NetGUID to identify the scope
- L26 _macro_ `#define UE_NET_TRACE_DYNAMIC_NAME_SCOPE(Name, Stream, Collector, Verbosity) UE_NET_TRACE_INTERNAL_DYNAMIC_NAME_SCOPE(Name, Stream, Collector, Verbosity)` — NetTraceScope with dynamic name
- L34 _macro_ `#define UE_NET_TRACE_NAMED_SCOPE(ScopeName, EventName, Stream, Collector, Verbosity) UE_NET_TRACE_INTERNAL_NAMED_SCOPE(ScopeName, EventName, Stream, Collector, Verbosity)` — Named NetTraceScope
- L37 _macro_ `#define UE_NET_TRACE_NAMED_OBJECT_SCOPE(ScopeName, HandleOrNetGUID, Stream, Collector, Verbosity) UE_NET_TRACE_INTERNAL_NAMED_OBJECT_SCOPE(ScopeName, HandleOrNetGUID, Stream, Collector, Verbosity)` — Named Object NetTraceScope
- L40 _macro_ `#define UE_NET_TRACE_NAMED_DYNAMIC_NAME_SCOPE(ScopeName, EventName, Stream, Collector, Verbosity) UE_NET_TRACE_INTERNAL_NAMED_DYNAMIC_NAME_SCOPE(ScopeName, EventName, Stream, Collector, Verbosity)` — Named dynamic name NetTraceScope
- L43 _macro_ `#define UE_NET_TRACE_SET_SCOPE_NAME(ScopeName, EventName) UE_NET_TRACE_INTERNAL_SET_SCOPE_NAME(ScopeName, EventName)` — Set the EventName of a named scope
- L46 _macro_ `#define UE_NET_TRACE_SET_SCOPE_OBJECTID(ScopeName, HandleOrNetGUID) UE_NET_TRACE_INTERNAL_SET_SCOPE_OBJECTID(ScopeName, HandleOrNetGUID)` — Set the ObjectId of named scope
- L49 _macro_ `#define UE_NET_TRACE_EXIT_NAMED_SCOPE(ScopeName) UE_NET_TRACE_INTERNAL_EXIT_NAMED_SCOPE(ScopeName)` — Early out of a named scope
- L55 _macro_ `#define UE_NET_TRACE_OFFSET_SCOPE(Offset, Collector) UE_NET_TRACE_INTERNAL_OFFSET_SCOPE(Offset, Collector)` — During the lifetime of an offset scope all reported content events are offset by the provided offset Supports nesting, offsets of nested scopes are accumulated
- L58 _macro_ `#define UE_NET_TRACE(Name, Collector, StartPos, EndPos, Verbosity) UE_NET_TRACE_INTERNAL(Name, Collector, StartPos, EndPos, Verbosity)` — Trace event information for a static name
- L61 _macro_ `#define UE_NET_TRACE_DYNAMIC_NAME(Name, Collector, StartPos, EndPos, Verbosity) UE_NET_TRACE_INTERNAL_DYNAMIC_NAME(Name, Collector, StartPos, EndPos, Verbosity)` — Trace event information with a dynamic name
- L64 _macro_ `#define UE_NET_TRACE_FLUSH_COLLECTOR(Collector, ...) UE_NET_TRACE_INTERNAL_FLUSH_COLLECTOR(Collector, __VA_ARGS__)` — Report collected events for the current packet
- L67 _macro_ `#define UE_NET_TRACE_BEGIN_BUNCH(Collector) UE_NET_TRACE_INTERNAL_BEGIN_BUNCH(Collector)` — Mark the beginning of a new bunch
- L70 _macro_ `#define UE_NET_TRACE_DISCARD_BUNCH(Collector) UE_NET_TRACE_INTERNAL_DISCARD_BUNCH(Collector)` — Discard pending bunch
- L73 _macro_ `#define UE_NET_TRACE_POP_SEND_BUNCH(Collector) UE_NET_TRACE_INTERNAL_POP_SEND_BUNCH(Collector)` — Pop the last send bunch, used by merging bunch logic
- L76 _macro_ `#define UE_NET_TRACE_EVENTS(DstCollector, SrcCollector, Stream) UE_NET_TRACE_INTERNAL_EVENTS(DstCollector, SrcCollector, Stream)` — Append events from SrcCollector to Collector
- L79 _macro_ `#define UE_NET_TRACE_END_BUNCH(Collector, Bunch, ...) UE_NET_TRACE_INTERNAL_END_BUNCH(Collector, Bunch, __VA_ARGS__)` — Mark the end of a bunch
- L82 _macro_ `#define UE_NET_TRACE_BUNCH_SCOPE(Collector, Bunch, ...) UE_NET_TRACE_INTERNAL_BUNCH_SCOPE(Collector, Bunch, __VA_ARGS__)` — Scope to track begin/end bunch
- L85 _macro_ `#define UE_NET_TRACE_ASSIGNED_GUID(GameInstanceId, NetGUID, PathName, OwnerId) UE_NET_TRACE_INTERNAL_ASSIGNED_GUID(GameInstanceId, NetGUID, PathName, OwnerId)` — Trace Assigned NetGUID
- L88 _macro_ `#define UE_NET_TRACE_NETHANDLE_CREATED(Handle, DebugName, ProtocolId, OwnerId) UE_NET_TRACE_INTERNAL_NETHANDLE_CREATED(Handle, DebugName, ProtocolId, OwnerId)` — Trace that we have started to replicate a handle
- L91 _macro_ `#define UE_NET_TRACE_NETHANDLE_DESTROYED(Handle) UE_NET_TRACE_INTERNAL_NETHANDLE_DESTROYED(Handle)` — Trace that we stopped replicating a handle
- L94 _macro_ `#define UE_NET_TRACE_CONNECTION_CREATED(...) UE_NET_TRACE_INTERNAL_CONNECTION_CREATED(__VA_ARGS__)` — Trace that a new connection has been created
- L97 _macro_ `#define UE_NET_TRACE_CONNECTION_STATE_UPDATED(...) UE_NET_TRACE_INTERNAL_CONNECTION_STATE_UPDATED(__VA_ARGS__)` — Trace that the state of this connection has been set
- L100 _macro_ `#define UE_NET_TRACE_CONNECTION_UPDATED(...) UE_NET_TRACE_INTERNAL_CONNECTION_UPDATED(__VA_ARGS__)` — Trace additional information about the given connection
- L103 _macro_ `#define UE_NET_TRACE_PACKET_STATSCOUNTER(GameInstanceId, ConnectionId, Name, StatValue, Verbosity) UE_NET_TRACE_INTERNAL_PACKET_STATSCOUNTER(GameInstanceId, ConnectionId, Name, StatValue, Verbosity)` — Trace StatsCounter associated with next reported packet
- L106 _macro_ `#define UE_NET_TRACE_FRAME_STATSCOUNTER(GameInstanceId, Name, StatValue, Verbosity) UE_NET_TRACE_INTERNAL_FRAME_STATSCOUNTER(GameInstanceId, Name, StatValue, Verbosity)` — Trace StatsCounter associated with current frame
- L109 _macro_ `#define UE_NET_TRACE_CONNECTION_CLOSED(...) UE_NET_TRACE_INTERNAL_CONNECTION_CLOSED(__VA_ARGS__)` — That that a connection has been closed
- L112 _macro_ `#define UE_NET_TRACE_PACKET_DROPPED(...) UE_NET_TRACE_INTERNAL_PACKET_DROPPED(__VA_ARGS__)` — Trace that we have dropped a packet
- L115 _macro_ `#define UE_NET_TRACE_PACKET_SEND(...) UE_NET_TRACE_INTERNAL_PACKET_SEND(__VA_ARGS__)` — Trace that we have sent a packet
- L118 _macro_ `#define UE_NET_TRACE_PACKET_RECV(...) UE_NET_TRACE_INTERNAL_PACKET_RECV(__VA_ARGS__)` — Trace that we have received a packet
- L121 _macro_ `#define UE_NET_TRACE_END_SESSION(GameInstanceId) UE_NET_TRACE_INTERNAL_END_SESSION(GameInstanceId)` — Trace that the session has ended
- L124 _macro_ `#define UE_NET_TRACE_UPDATE_INSTANCE(...) UE_NET_TRACE_INTERNAL_UPDATE_INSTANCE(__VA_ARGS__)` — Trace additional information about the given game instance
- L126 _macro_ `#define UE_NET_TRACE_POLL_OBJECT_SCOPE(...) UE_NET_TRACE_INTERNAL_POLL_OBJECT_SCOPE(__VA_ARGS__)`
- L127 _macro_ `#define UE_NET_TRACE_POLL_OBJECT_IS_WASTE() UE_NET_TRACE_INTERNAL_POLL_OBJECT_IS_WASTE`
- L128 _macro_ `#define UE_NET_TRACE_QUANTIZE_OBJECT_SCOPE(...) UE_NET_TRACE_INTERNAL_QUANTIZE_OBJECT_SCOPE(__VA_ARGS__)`
- L129 _macro_ `#define UE_NET_TRACE_WRITE_OBJECT_SCOPE(...) UE_NET_TRACE_INTERNAL_WRITE_OBJECT_SCOPE(__VA_ARGS__)`
- L131 _macro_ `#define UE_NET_TRACE_SUBOBJECT(ParentHandle, SubObjectHandle) UE_NET_TRACE_INTERNAL_SUBOBJECT(ParentHandle, SubObjectHandle)`
- L135 _macro_ `#define UE_NET_TRACE_SCOPE(...)`
- L136 _macro_ `#define UE_NET_TRACE_OBJECT_SCOPE(...)`
- L137 _macro_ `#define UE_NET_TRACE_DYNAMIC_NAME_SCOPE(...)`
- L138 _macro_ `#define UE_NET_TRACE_NAMED_SCOPE(...)`
- L139 _macro_ `#define UE_NET_TRACE_SET_SCOPE_NAME(...)`
- L140 _macro_ `#define UE_NET_TRACE_SET_SCOPE_OBJECTID(...)`
- L141 _macro_ `#define UE_NET_TRACE_EXIT_NAMED_SCOPE(...)`
- L142 _macro_ `#define UE_NET_TRACE(...)`
- L143 _macro_ `#define UE_NET_TRACE_DYNAMIC_NAME(...)`
- L144 _macro_ `#define UE_NET_TRACE_CREATE_COLLECTOR(...) nullptr`
- L145 _macro_ `#define UE_NET_TRACE_DESTROY_COLLECTOR(...)`
- L147 _macro_ `#define UE_NET_TRACE_FLUSH_COLLECTOR(...)`
- L148 _macro_ `#define UE_NET_TRACE_BEGIN_BUNCH(...)`
- L149 _macro_ `#define UE_NET_TRACE_DISCARD_BUNCH(...)`
- L150 _macro_ `#define UE_NET_TRACE_POP_SEND_BUNCH(...)`
- L151 _macro_ `#define UE_NET_TRACE_EVENTS(...)`
- L152 _macro_ `#define UE_NET_TRACE_END_BUNCH(...)`
- L153 _macro_ `#define UE_NET_TRACE_BUNCH_SCOPE(...)`
- L154 _macro_ `#define UE_NET_TRACE_OFFSET_SCOPE(...)`
- L156 _macro_ `#define UE_NET_TRACE_ASSIGNED_GUID(...)`
- L157 _macro_ `#define UE_NET_TRACE_NETHANDLE_CREATED(...)`
- L158 _macro_ `#define UE_NET_TRACE_NETHANDLE_DESTROYED(...)`
- L159 _macro_ `#define UE_NET_TRACE_CONNECTION_CREATED(...)`
- L160 _macro_ `#define UE_NET_TRACE_CONNECTION_STATE_UPDATED(...)`
- L161 _macro_ `#define UE_NET_TRACE_CONNECTION_UPDATED(...)`
- L162 _macro_ `#define UE_NET_TRACE_CONNECTION_CLOSED(...)`
- L163 _macro_ `#define UE_NET_TRACE_PACKET_DROPPED(...)`
- L164 _macro_ `#define UE_NET_TRACE_NAMED_OBJECT_SCOPE(...)`
- L165 _macro_ `#define UE_NET_TRACE_NAMED_DYNAMIC_NAME_SCOPE(...)`
- L167 _macro_ `#define UE_NET_TRACE_PACKET_STATSCOUNTER(...)`
- L168 _macro_ `#define UE_NET_TRACE_FRAME_STATSCOUNTER(...)`
- L171 _macro_ `#define UE_NET_TRACE_PACKET_SEND(...)`
- L172 _macro_ `#define UE_NET_TRACE_PACKET_RECV(...)`
- L174 _macro_ `#define UE_NET_TRACE_END_SESSION(...)`
- L176 _macro_ `#define UE_NET_TRACE_UPDATE_INSTANCE(...)`
- L178 _macro_ `#define UE_NET_TRACE_POLL_OBJECT_SCOPE(...)`
- L179 _macro_ `#define UE_NET_TRACE_POLL_OBJECT_IS_WASTE()`
- L180 _macro_ `#define UE_NET_TRACE_QUANTIZE_OBJECT_SCOPE(...)`
- L181 _macro_ `#define UE_NET_TRACE_WRITE_OBJECT_SCOPE(...)`
- L183 _macro_ `#define UE_NET_TRACE_SUBOBJECT(...)`

### `Source/Runtime/Net/Core/Public/Net/Core/Trace/NetTraceConfig.h` (Public)


#### enum `ENetTraceVerbosity::Type`  
`enum Type : uint32`  
_L20-26_
- L22 _public enumerator_ `None = 0`
- L23 _public enumerator_ `Trace`
- L24 _public enumerator_ `Verbose`
- L25 _public enumerator_ `VeryVerbose`

#### Free symbols / members of external scopes

- L12 _macro_ `# define UE_NET_TRACE_ENABLED 1`
- L14 _macro_ `# define UE_NET_TRACE_ENABLED 0`
- L18 _namespace_ `namespace ENetTraceVerbosity`
- L29 _variable_ `inline const uint32 NetTraceInvalidGameInstanceId = ~0U;`
- L34 _macro_ `# define UE_NET_TRACE_COMPILETIME_VERBOSITY ENetTraceVerbosity::VeryVerbose`
- L36 _macro_ `# define UE_NET_TRACE_COMPILETIME_VERBOSITY ENetTraceVerbosity::Verbose`
- L39 _macro_ `# define UE_NET_TRACE_COMPILETIME_VERBOSITY ENetTraceVerbosity::None`

### `Source/Runtime/Net/Core/Public/Net/Core/Trace/Private/NetTraceInternal.h` (Public)


#### class `UE::Net::Private::FNetTimer`  
`class FNetTimer`  
_L10-22_
- L13 _public function_ `FNetTimer(bool bEnabled) : StartCycle(bEnabled ? FPlatformTime::Cycles64() : uint64(0))`
- L18 _public function_ `uint64 GetCyclesSinceStart() const`
- L21 _private member_ `uint64 StartCycle;`

#### enum `ENetTracePacketContentEventType`  
`enum class ENetTracePacketContentEventType : uint8`  
_L58-64_
- L60 _public enumerator_ `Object = 0`
- L61 _public enumerator_ `NameId = 1`
- L62 _public enumerator_ `BunchEvent = 2`
- L63 _public enumerator_ `BunchHeaderEvent = 3`

#### enum `ENetTracePacketType`  
`enum class ENetTracePacketType : uint8`  
_L66-70_
- L68 _public enumerator_ `Outgoing = 0`
- L69 _public enumerator_ `Incoming`

#### enum `ENetTraceStatsCounterType`  
`enum class ENetTraceStatsCounterType : uint8`  
_L72-76_
- L74 _public enumerator_ `Packet = 0`
- L75 _public enumerator_ `Frame = 1`

#### struct `FNetTracePacketInfo`  
`struct FNetTracePacketInfo`  
_L78-84_
- L80 _public member_ `uint32 GameInstanceId;`
- L81 _public member_ `uint32 PacketSequenceNumber;`
- L82 _public member_ `uint16 ConnectionId;`
- L83 _public member_ `ENetTracePacketType PacketType;`

#### union `FNetTraceBunchInfo`  
`union FNetTraceBunchInfo`  
_L87-108_
- desc: Any changes to this struct must also be reflected on the NetTraceAnalyzer side and versioned
- L107 _public member_ `uint64 Value;`

#### struct `FNetTraceBunchInfo::(anonymous)`  
``  
_L90-106_

#### struct `FNetTracePacketContentEvent`  
`struct FNetTracePacketContentEvent`  
_L112-127_

#### union `FNetTracePacketContentEvent::(anonymous)`  
``  
_L115-119_

#### struct `FNetTracePacketContentEvent::(anonymous)`  
``  
_L121-126_

#### class `FNetTraceEventScope`  
`template <typename T> class FNetTraceEventScope`  
_L137-161_
- desc: Scope used to track data read from or written to a bitstream, supports nesting In order to support instrumenting different types of bitstreams using the same set of macros, a loose function with the signature below can be provided uint32 GetBitStreamPositionForNetTrace(const T& Stream)
- L142 _public prototype_ `FNetTraceEventScope(uint64 ObjectId, T& InStream, FNetTraceCollector* InCollector, uint32 Verbosity);`
- L147 _public prototype_ `template <typename TraceNameFunctor> FNetTraceEventScope(TraceNameFunctor&& TraceNameFunc, T& InStream, FNetTraceCollector* InCollector, uint32 Verbosity);` — When a scope is disabled due to verbosity we want to deffer the tracing of names We do this by using a lambda, this also allows us to complete eliminate statics if a scope is compiled out due to compile time verbosity
- L149 _public prototype_ `~FNetTraceEventScope();`
- L151 _public prototype_ `void SetEventName(UE::Net::FNetDebugNameId NetTraceNameId);`
- L152 _public prototype_ `void SetEventObjectId(uint64 ObjectId);`
- L153 _public prototype_ `void ExitScope();`
- L154 _public prototype_ `bool IsValid() const;`
- L158 _private member_ `FNetTraceCollector* Collector;`
- L159 _private member_ `T& Stream;`
- L160 _private member_ `uint32 EventIndex;`
- L523 _function_ `template <typename T> FNetTraceEventScope<T>::FNetTraceEventScope(uint64 InObjectId, T& InStream, FNetTraceCollector* InCollector, uint32 Verbosity) : Collector(FNetTrace::GetCollectorAtVerbosity(InCollector, Verbosity)) , Stream(InStream) , EventIndex(FNetTrace::InvalidEventIndex)` — FNetTraceEventScope implementation
- L541 _function_ `template <typename T> template <typename TraceNameFunctor> FNetTraceEventScope<T>::FNetTraceEventScope(TraceNameFunctor&& TraceNameFunc, T& InStream, FNetTraceCollector* InCollector, uint32 Verbosity) : Collector(FNetTrace::GetCollectorAtVerbosity(InCollector, Verbosity)) , Stream(InStream) , EventIndex(FNetTrace::InvalidEventIndex)`
- L554 _function_ `template <typename T> FNetTraceEventScope<T>::~FNetTraceEventScope()`
- L563 _function_ `template <typename T> void FNetTraceEventScope<T>::ExitScope()`
- L573 _function_ `template <typename T> void FNetTraceEventScope<T>::SetEventName(UE::Net::FNetDebugNameId NetTraceNameId)`
- L582 _function_ `template <typename T> void FNetTraceEventScope<T>::SetEventObjectId(uint64 ObjectId)`
- L592 _function_ `template <typename T> bool FNetTraceEventScope<T>::IsValid() const`

#### class `FNetTraceNullEventScope`  
`template <typename T> class FNetTraceNullEventScope`  
_L167-179_
- desc: Null implementation of NetTraceEventScope used for compile-time verbosity
- L172 _public function_ `template <typename SinkT> FNetTraceNullEventScope(SinkT, T& InStream, FNetTraceCollector* InCollector, uint32 Verbosity)`
- L173 _public prototype_ `~FNetTraceNullEventScope() = default;`
- L175 _public function_ `void SetEventName(UE::Net::FNetDebugNameId NetTraceNameId)`
- L176 _public function_ `void SetEventObjectId(uint64 ObjectId)`
- L177 _public function_ `void ExitScope()`
- L178 _public function_ `bool IsValid() const`

#### struct `FNetTrace`  
`struct FNetTrace`  
_L181-322_
- L186 _public function_ `static bool IsEnabled()` — Returns if tracing is enabled or not
- L189 _public prototype_ `static void SetTraceVerbosity(uint32 Verbosity);` — Sets the runtime trace verbosity level, Verbosity == 0 means that it is disabled
- L191 _public prototype_ `static void OnTraceConnected();`
- L193 _public prototype_ `static void OnTraceStopped(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L195 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnNetTraceStarted);`
- L196 _public member_ `static FOnNetTraceStarted OnNetTraceStarted;`
- L199 _public prototype_ `static void TraceEndSession(uint32 GameInstanceId);` — Trace end of session for a GameInstance
- L202 _public prototype_ `static void TraceInstanceUpdated(uint32 GameInstanceId, bool bIsServer, const TCHAR* Name);` — Trace that information about the current GameInstance has been updated
- L205 _public function_ `inline static uint32 GetTraceVerbosity()` — Get the current trace verbosity
- L208 _public prototype_ `static FNetTraceCollector* CreateTraceCollector();` — Create a new trace collector if tracing is enabled
- L211 _public prototype_ `inline static FNetTraceCollector* CreateTraceCollector(uint32 Verbosity);` — Create a new trace collector if tracing is enabled
- L214 _public prototype_ `static void DestroyTraceCollector(FNetTraceCollector* Collector);` — Destroy trace collector without reporting the collected events
- L217 _public prototype_ `static void FoldTraceCollector(FNetTraceCollector* DstCollector, const FNetTraceCollector* SrcCollector, uint32 Offset, uint32 LevelOffset = 0U);` — Folds events into DstCollector
- L220 _public prototype_ `static void FoldBunchCollector(FNetTraceCollector* DstCollector, const FNetTraceCollector* SrcCollector);` — Folds bunch into DstCollector, if the src and dst are the same bunch it is assumed that a bunch already is open and that it will be closed
- L223 _public prototype_ `static void PushStreamOffset(FNetTraceCollector* Collector, uint32 Offset);` — Events will be offset by the provided offset, useful when doing partial reads using separate bitstreams, Does not support nesting
- L224 _public prototype_ `static void PopStreamOffset(FNetTraceCollector* Collector);`
- L227 _public prototype_ `static uint32 BeginPacketContentEvent(FNetTraceCollector& Collector, ENetTracePacketContentEventType EventType, uint32 Pos);` — Begin a new PacketContentEvent
- L230 _public prototype_ `static void EndPacketContentEvent(FNetTraceCollector& Collector, uint32 EventIndex, uint32 Pos);` — End a PacketContent event
- L233 _public prototype_ `static void TracePacketContentEvent(FNetTraceCollector& Collector, UE::Net::FNetDebugNameId InNetTraceNameId, uint32 StartPos, uint32 EndPos, uint32 Verbosity);` — Trace PacketContent event
- L236 _public prototype_ `static void BeginBunch(FNetTraceCollector& Collector);` — Mark the beginning of a new Bunch
- L239 _public prototype_ `static void DiscardBunch(FNetTraceCollector& Collector);` — Discard any events Collected since BeginBunch
- L242 _public prototype_ `static void EndBunch(FNetTraceCollector& DstCollector, UE::Net::FNetDebugNameId BunchName, uint32 StartPos, uint32 HeaderBits, uint32 BunchBits, const FNetTraceBunchInfo& BunchInfo);` — Trace end of a bunch, all events recorded between BeginBunch/EndBunch will be part of the bunch
- L245 _public prototype_ `static void TraceBunch(FNetTraceCollector& DstCollector, const FNetTraceBunchInfo& BunchInfo, FName BunchName, uint32 StartPos, uint32 HeaderBits, uint32 BunchBits, const FNetTraceCollector* BunchCollector);` — TraceBunch, Commits all events in BunchCollector to DstCollector, if DstCollector == BunchCollector it is assumed that we are Ending the bunch
- L248 _public prototype_ `static void TraceBunch(FNetTraceCollector& DstCollector, const FNetTraceBunchInfo& BunchInfo, const TCHAR* BunchName, uint32 StartPos, uint32 HeaderBits, uint32 BunchBits, const FNetTraceCollector* BunchCollector);` — TraceBunch, Commits all events in BunchCollector to DstCollector, if DstCollector == BunchCollector it is assumed that we are Ending the bunch
- L251 _public prototype_ `static void PopSendBunch(FNetTraceCollector& Collector);` — PopSendBunch, last send bunch is considered to be merged with the next one, mark this by zeroing out the BunchHeaderSize
- L254 _public prototype_ `static void TraceCollectedEvents(FNetTraceCollector& Collector, uint32 GameInstanceId, uint32 ConnectionId, ENetTracePacketType PacketType);` — Trace all events in the bunch
- L257 _public prototype_ `static void TracePacketDropped(uint32 GameInstanceId, uint32 ConnectionId, uint32 PacketSequenceNumber, ENetTracePacketType PacketType);` — Trace if the packet was dropped
- L260 _public prototype_ `static void TracePacket(uint32 GameInstanceId, uint32 ConnectionId, uint32 PacketSequenceNumber, uint32 PacketBits, ENetTracePacketType PacketType);` — Trace incoming or outgoing packet
- L263 _public prototype_ `static void TraceObjectCreated(uint32 GameInstanceId, uint64 NetObjectId, const UE::Net::FNetDebugName* Name, uint64 TypeIdentifier, uint32 OwnerId);` — Trace that we have created a new object with the given ObjectId
- L266 _public prototype_ `static void TraceObjectCreated(uint32 GameInstanceId, uint64 NetObjectId, const FName Name, uint64 TypeIdentifier, uint32 OwnerId);` — Trace that we have created a new object with the given ObjectId
- L269 _public prototype_ `static void TraceObjectDestroyed(uint32 GameInstanceId, uint64 NetObjectId);` — Trace that a handle has been destroyed, the handle contains required info
- L272 _public prototype_ `static void TraceConnectionCreated(uint32 GameInstanceId, uint32 ConnectionId);` — Trace that we have added a new connection for the given GameInstanceId
- L275 _public prototype_ `static void TraceConnectionStateUpdated(uint32 GameInstanceId, uint32 ConnectionId, uint8 ConnectionStateValue);` — Trace that the Connection State the given connection has been set
- L278 _public prototype_ `static void TraceConnectionUpdated(uint32 GameInstanceId, uint32 ConnectionId, const TCHAR* AddressString, const TCHAR* OwningActor);` — Trace additional information related to the given connection
- L281 _public prototype_ `static void TraceConnectionClosed(uint32 GameInstanceId, uint32 ConnectionId);` — Trace that we have removed a connection for the given GameInstanceId
- L284 _public prototype_ `static void TracePacketStatsCounter(uint32 GameInstanceId, uint32 ConnectionId, UE::Net::FNetDebugNameId CounterNameId, uint32 StatValue);` — Trace stats counters for networking
- L285 _public prototype_ `static void TracePacketStatsCounter(uint32 GameInstanceId, uint32 ConnectionId, const UE::Net::FNetDebugName* CounterName, uint32 StatValue);`
- L286 _public prototype_ `static void TraceFrameStatsCounter(uint32 GameInstanceId, UE::Net::FNetDebugNameId CounterNameId, uint32 StatValue);`
- L287 _public prototype_ `static void TraceFrameStatsCounter(uint32 GameInstanceId, const UE::Net::FNetDebugName* CounterNameId, uint32 StatValue);`
- L290 _public prototype_ `static UE::Net::FNetDebugNameId TraceName(const TCHAR* Name);` — Trace the name
- L293 _public prototype_ `static UE::Net::FNetDebugNameId TraceName(FName Name);` — Trace the FName
- L296 _public prototype_ `static UE::Net::FNetDebugNameId TraceName(const UE::Net::FNetDebugName* Name);` — Trace the FNetDebugName
- L299 _public function_ `inline static UE::Net::FNetDebugNameId TraceName(const FString& Name)` — Trace
- L301 _public prototype_ `static void TraceObjectPolled(uint32 GameInstanceId, uint64 NetObjectId, uint64 Cycles, bool bIsDirty);`
- L303 _public prototype_ `static void TraceObjectQuantized(uint32 GameInstanceId, uint64 NetObjectId, uint64 Cycles);`
- L305 _public prototype_ `static void TraceObjectWritten(uint32 GameInstanceId, uint64 NetObjectId, uint64 Cycles);`
- L307 _public prototype_ `static void TraceSubObject(uint32 GameInstanceId, uint64 ParentNetObjectId, uint64 SubObjectNetObjectId);`
- L309 _public prototype_ `static void SetupInstanceForNetTraceId(uint32 InNetTraceId);`
- L311 _public prototype_ `static void FinishConnectionTick(const uint32 GameInstanceId);`
- L313 _public function_ `static bool constexpr GetNetTraceVerbosityEnabled(const uint32 V)`
- L315 _public prototype_ `inline static FNetTraceCollector* GetCollectorAtVerbosity(FNetTraceCollector* Collector, uint32 CollectorVerbosity);`
- L497 _function_ `FNetTraceCollector* FNetTrace::CreateTraceCollector(uint32 Verbosity)` — FNetTrace implementation
- L509 _function_ `FNetTraceCollector* FNetTrace::GetCollectorAtVerbosity(FNetTraceCollector* Collector, uint32 CollectorVerbosity)`

#### enum `FNetTrace::(anonymous)`  
`enum`  
_L183-183_

#### struct `FNetTrace::TChooseTraceEventScope`  
`template<uint32 Verbosity, typename StreamType> struct TChooseTraceEventScope`  
_L318-321_
- L320 _public typedef_ `typedef std::conditional_t<FNetTrace::GetNetTraceVerbosityEnabled(Verbosity), FNetTraceEventScope<StreamType>, FNetTraceNullEventScope<StreamType> > Type;`

#### class `FNetTraceCollector`  
`class FNetTraceCollector`  
_L362-402_
- desc: The purpose of a NetTraceCollector is to allow tracing of full packet content data with as low overhead as possible.
- L371 _public function_ `explicit FNetTraceCollector(uint32 InitialEventCount)`
- L372 _public function_ `FNetTraceCollector() : FNetTraceCollector(InlinedEventCount)`
- L374 _public prototype_ `inline void Reset();`
- L376 _public function_ `inline FNetTracePacketContentEvent& EditEvent(uint32 Index)`
- L377 _public function_ `inline FNetTracePacketContentEvent& EditEventNoCheck(uint32 Index)`
- L378 _public function_ `inline void AddReferencedObjectId(uint64 ObjectId)`
- L379 _public function_ `inline bool CanBeginPacketContentEvent() const`
- L385 _private member_ `uint32 NestingStack[MaxNestingLevel];` — Bookkeeping
- L386 _private member_ `uint32 OffsetStack[MaxNestingLevel];`
- L387 _private member_ `uint32 EventCount;`
- L388 _private member_ `uint32 CurrentNestingLevel : 16;`
- L389 _private member_ `uint32 OffsetStackLevel : 16;`
- L392 _private member_ `uint32 LastBunchEventIndex;` — Bunch tracking
- L393 _private member_ `uint32 BunchEventCount;`
- L394 _private member_ `uint32 PendingBunchEventIndex;`
- L397 _private typedef_ `typedef TArray<FNetTracePacketContentEvent, TInlineAllocator<InlinedEventCount> > FEventArray;` — Events
- L398 _private member_ `FEventArray Events;`
- L401 _private member_ `TArray<uint64, TInlineAllocator<InlinedObjectIdCount>> ReferencedObjectIds;` — Object Ids referenced by events
- L640 _function_ `void FNetTraceCollector::Reset()` — FNetTraceCollector implementation

#### enum `FNetTraceCollector::(anonymous)`  
`enum`  
_L367-367_
- desc: constants

#### enum `FNetTraceCollector::(anonymous)`  
`enum`  
_L368-368_

#### enum `FNetTraceCollector::(anonymous)`  
`enum`  
_L369-369_

#### class `FNetTraceBunchScope`  
`template <typename T> class FNetTraceBunchScope`  
_L408-420_
- desc: Used to trace events generated while reading or writing a bunch
- L412 _public prototype_ `FNetTraceBunchScope(T& InBunch, uint32 InStartPos, uint32 InHeaderBits, FNetTraceCollector* InCollector);`
- L413 _public prototype_ `~FNetTraceBunchScope();`
- L416 _private member_ `FNetTraceCollector* Collector;`
- L417 _private member_ `T& Bunch;`
- L418 _private member_ `const uint32 StartPos;`
- L419 _private member_ `const uint32 HeaderBits;`
- L599 _function_ `template <typename T> FNetTraceBunchScope<T>::FNetTraceBunchScope(T& InBunch, uint32 InStartPos, uint32 InHeaderBits, FNetTraceCollector* InCollector) : Collector(InCollector) , Bunch(InBunch) , StartPos(InStartPos) , HeaderBits(InHeaderBits)` — FNetTraceBunchScope implementation
- L612 _function_ `template <typename T> FNetTraceBunchScope<T>::~FNetTraceBunchScope()`

#### class `FNetTraceOffsetScope`  
`class FNetTraceOffsetScope`  
_L425-434_
- desc: Used to apply a offset to events collected when the scope is active, used to avoid instantiate multiple collectors
- L429 _public prototype_ `FNetTraceOffsetScope(uint32 Offset, FNetTraceCollector* InCollector);`
- L430 _public prototype_ `~FNetTraceOffsetScope();`
- L433 _private member_ `FNetTraceCollector* Collector;`
- L622 _function_ `inline FNetTraceOffsetScope::FNetTraceOffsetScope(uint32 Offset, FNetTraceCollector* InCollector) : Collector(InCollector)` — FNetTraceOffsetScope implementation
- L631 _function_ `inline FNetTraceOffsetScope::~FNetTraceOffsetScope()`

#### struct `FNetTraceObjectTimer`  
`struct FNetTraceObjectTimer`  
_L436-447_
- L438 _public function_ `FNetTraceObjectTimer(const UE::Net::Private::FNetTimer& InTimer, uint32 InGameInstanceId, uint64 InNetObjectId) : Timer(InTimer) , NetObjectId(InNetObjectId) , GameInstanceId(InGameInstanceId)`
- L444 _public member_ `const UE::Net::Private::FNetTimer& Timer;`
- L445 _public member_ `uint64 NetObjectId;`
- L446 _public member_ `uint32 GameInstanceId;`

#### struct `FNetTraceObjectPollTimer`  
`struct FNetTraceObjectPollTimer : public FNetTraceObjectTimer`  
_L449-464_
- inherits: `FNetTraceObjectTimer`
- L451 _public function_ `FNetTraceObjectPollTimer(const UE::Net::Private::FNetTimer& InTimer, uint32 InGameInstanceId, uint64 InNetObjectId) : FNetTraceObjectTimer(InTimer, InGameInstanceId, InNetObjectId) , bIsWaste(false)`
- L455 _public function_ `~FNetTraceObjectPollTimer()`
- L463 _public member_ `bool bIsWaste;`

#### struct `FNetTraceObjectQuantizeTimer`  
`struct FNetTraceObjectQuantizeTimer : public FNetTraceObjectTimer`  
_L466-479_
- inherits: `FNetTraceObjectTimer`
- L468 _public function_ `FNetTraceObjectQuantizeTimer(const UE::Net::Private::FNetTimer& InTimer, uint32 InGameInstanceId, uint64 InNetObjectId) : FNetTraceObjectTimer(InTimer, InGameInstanceId, InNetObjectId)`
- L472 _public function_ `~FNetTraceObjectQuantizeTimer()`

#### struct `FNetTraceObjectWriteTimer`  
`struct FNetTraceObjectWriteTimer : public FNetTraceObjectTimer`  
_L481-494_
- inherits: `FNetTraceObjectTimer`
- L483 _public function_ `FNetTraceObjectWriteTimer(const UE::Net::Private::FNetTimer& InTimer, uint32 InGameInstanceId, uint64 InNetObjectId) : FNetTraceObjectTimer(InTimer, InGameInstanceId, InNetObjectId)`
- L487 _public function_ `~FNetTraceObjectWriteTimer()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Net` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Net`)
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Net` (scope `UE`)
- L51 _prototype_ `extern uint32 GetBitStreamPositionForNetTrace(const UE::Net::FNetBitStreamReader& Stream);`
- L52 _prototype_ `extern uint32 GetBitStreamPositionForNetTrace(const UE::Net::FNetBitStreamWriter& Stream);`
- L53 _prototype_ `extern uint32 GetBitStreamPositionForNetTrace(const FBitReader& Stream);`
- L54 _prototype_ `extern uint32 GetBitStreamPositionForNetTrace(const FBitWriter& Stream);`
- L56 _externvar_ `extern uint32 GNetTraceRuntimeVerbosity;`
- L91 _member_ `uint64 ChannelIndex : 20;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L92 _member_ `uint64 Seq : 12;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L93 _member_ `uint64 ChannelCloseReason : 4;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L94 _member_ `uint64 bPartial : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L95 _member_ `uint64 bPartialInitial : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L96 _member_ `uint64 bPartialCustomExportsFinal : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L97 _member_ `uint64 bPartialFinal : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L99 _member_ `uint64 bIsReplicationPaused : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`) — `UE_DEPRECATED(5.3, "Replication pausing is deprecated")`
- L100 _member_ `uint64 bOpen : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L101 _member_ `uint64 bClose : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L102 _member_ `uint64 bReliable : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L103 _member_ `uint64 bHasPackageMapExports : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L104 _member_ `uint64 bHasMustBeMappedGUIDs : 1;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L105 _member_ `uint64 Padding : 18;` (scope `FNetTraceBunchInfo::__anon5574e5c40108`)
- L116 _member_ `UE::Net::FNetDebugNameId DebugNameId;` (scope `FNetTracePacketContentEvent::__anon5574e5c4020a`)
- L117 _member_ `uint64 ObjectId;` (scope `FNetTracePacketContentEvent::__anon5574e5c4020a`)
- L118 _member_ `FNetTraceBunchInfo BunchInfo;` (scope `FNetTracePacketContentEvent::__anon5574e5c4020a`)
- L122 _member_ `uint32 StartPos : 24;` (scope `FNetTracePacketContentEvent::__anon5574e5c40308`)
- L123 _member_ `uint32 EventType : 8;` (scope `FNetTracePacketContentEvent::__anon5574e5c40308`)
- L124 _member_ `uint32 EndPos : 24;` (scope `FNetTracePacketContentEvent::__anon5574e5c40308`)
- L125 _member_ `uint32 NestingLevel : 8;` (scope `FNetTracePacketContentEvent::__anon5574e5c40308`)
- L183 _enumerator_ `enum { InvalidEventIndex = ~0U }; static bool IsEnabled() { return GetTraceVerbosity() > 0U; } NETCORE_API static void SetTraceVerbosity(uint32 Verbosity);` (scope `FNetTrace::__anon5574e5c40403`)
- L195 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnNetTraceStarted);`
- L325 _function_ `template<typename T> uint64 GetObjectIdForNetTrace(const T&)`
- L331 _function_ `inline uint64 GetObjectIdForNetTrace(const FNetworkGUID& NetGUID)`
- L337 _function_ `template<typename T> FNetTraceBunchInfo MakeBunchInfo(const T& Bunch)`
- L367 _enumerator_ `enum { MaxNestingLevel = 32 }; enum { InlinedEventCount = 256 }; enum { InlinedObjectIdCount = 128 }; explicit FNetTraceCollector(uint32 InitialEventCount) { Events.SetNumUninitialized(InitialEventCount); Reset(); } FNetTraceCollector() : FNetTraceCollector(InlinedEventCount) {}; inline void Reset();` (scope `FNetTraceCollector::__anon5574e5c40503`) — constants
- L368 _enumerator_ `enum { InlinedEventCount = 256 }; enum { InlinedObjectIdCount = 128 }; explicit FNetTraceCollector(uint32 InitialEventCount) { Events.SetNumUninitialized(InitialEventCount); Reset(); } FNetTraceCollector() : FNetTraceCollector(InlinedEventCount) {}; inline void Reset();` (scope `FNetTraceCollector::__anon5574e5c40603`)
- L369 _enumerator_ `enum { InlinedObjectIdCount = 128 }; explicit FNetTraceCollector(uint32 InitialEventCount) { Events.SetNumUninitialized(InitialEventCount); Reset(); } FNetTraceCollector() : FNetTraceCollector(InlinedEventCount) {}; inline void Reset(); inline FNetTracePacketContentEvent& EditEvent(uint32 Index) { return Events[Index]; }` (scope `FNetTraceCollector::__anon5574e5c40703`)
- L652 _macro_ `#define UE_NET_TRACE_DO_IF(Cond, x) do { if (Cond) { x; } } while (0)`
- L655 _macro_ `#define UE_NET_TRACE_INTERNAL_CREATE_COLLECTOR(Verbosity) (GNetTraceRuntimeVerbosity ? FNetTrace::CreateTraceCollector(Verbosity) : nullptr)` — Internal macros wrapping all operations
- L656 _macro_ `#define UE_NET_TRACE_INTERNAL_DESTROY_COLLECTOR(Collector) UE_NET_TRACE_DO_IF(Collector, FNetTrace::DestroyTraceCollector(Collector))`
- L657 _macro_ `#define UE_NET_TRACE_INTERNAL_FLUSH_COLLECTOR(Collector, ...) UE_NET_TRACE_DO_IF(Collector, FNetTrace::TraceCollectedEvents(*Collector, __VA_ARGS__))`
- L658 _macro_ `#define UE_NET_TRACE_INTERNAL_BEGIN_BUNCH(Collector) UE_NET_TRACE_DO_IF(Collector, FNetTrace::BeginBunch(*Collector))`
- L659 _macro_ `#define UE_NET_TRACE_INTERNAL_DISCARD_BUNCH(Collector) UE_NET_TRACE_DO_IF(Collector, FNetTrace::DiscardBunch(*Collector))`
- L660 _macro_ `#define UE_NET_TRACE_INTERNAL_POP_SEND_BUNCH(Collector) UE_NET_TRACE_DO_IF(Collector, FNetTrace::PopSendBunch(*Collector))`
- L661 _macro_ `#define UE_NET_TRACE_INTERNAL_EVENTS(Collector, SrcCollector, Stream) UE_NET_TRACE_DO_IF(Collector, FNetTrace::FoldTraceCollector(Collector, SrcCollector, GetBitStreamPositionForNetTrace(Stream)))`
- L662 _macro_ `#define UE_NET_TRACE_INTERNAL_END_BUNCH(Collector, Bunch, ...) UE_NET_TRACE_DO_IF(Collector, FNetTrace::TraceBunch(*Collector, MakeBunchInfo(Bunch), __VA_ARGS__))`
- L663 _macro_ `#define UE_NET_TRACE_INTERNAL_BUNCH_SCOPE(Collector, Bunch, ...) FNetTraceBunchScope<decltype(Bunch)> UE_JOIN(NetTraceBunchScope, __LINE__)(Bunch, __VA_ARGS__, Collector)`
- L665 _macro_ `#define UE_NET_TRACE_INTERNAL_SCOPE(Name, Stream, Collector, Verbosity) \`
- L669 _macro_ `#define UE_NET_TRACE_INTERNAL_OBJECT_SCOPE(HandleOrNetGUID, Stream, Collector, Verbosity) \`
- L672 _macro_ `#define UE_NET_TRACE_INTERNAL_DYNAMIC_NAME_SCOPE(Name, Stream, Collector, Verbosity) \`
- L676 _macro_ `#define UE_NET_TRACE_INTERNAL_NAMED_SCOPE(ScopeName, EventName, Stream, Collector, Verbosity) \`
- L680 _macro_ `#define UE_NET_TRACE_INTERNAL_NAMED_OBJECT_SCOPE(ScopeName, HandleOrNetGUID, Stream, Collector, Verbosity) \`
- L683 _macro_ `#define UE_NET_TRACE_INTERNAL_NAMED_DYNAMIC_NAME_SCOPE(ScopeName, EventName, Stream, Collector, Verbosity) \`
- L687 _macro_ `#define UE_NET_TRACE_INTERNAL_SET_SCOPE_NAME(ScopeName, EventName) UE_NET_TRACE_DO_IF(ScopeName.IsValid(), ScopeName.SetEventName(FNetTrace::TraceName(EventName)))`
- L688 _macro_ `#define UE_NET_TRACE_INTERNAL_SET_SCOPE_OBJECTID(ScopeName, HandleOrNetGUID) UE_NET_TRACE_DO_IF(ScopeName.IsValid(), ScopeName.SetEventObjectId(GetObjectIdForNetTrace(HandleOrNetGUID)))`
- L689 _macro_ `#define UE_NET_TRACE_INTERNAL_EXIT_NAMED_SCOPE(ScopeName) ScopeName.ExitScope()`
- L690 _macro_ `#define UE_NET_TRACE_INTERNAL_OFFSET_SCOPE(Offset, Collector) FNetTraceOffsetScope UE_JOIN(NetTraceOffsetScope, __LINE__)(Offset, Collector);`
- L692 _macro_ `#define UE_NET_TRACE_INTERNAL(Name, Collector, StartPos, EndPos, Verbosity) \`
- L698 _macro_ `#define UE_NET_TRACE_INTERNAL_DYNAMIC_NAME(Name, Collector, StartPos, EndPos, Verbosity) UE_NET_TRACE_DO_IF(FNetTrace::GetCollectorAtVerbosity(Collector, Verbosity), FNetTrace::TracePacketContentEvent(*Collector, FNetTrace::TraceName(Name),`
- L699 _macro_ `#define UE_NET_TRACE_INTERNAL_ASSIGNED_GUID(GameInstanceId, NetGUID, PathName, OwnerId) UE_NET_TRACE_DO_IF(GNetTraceRuntimeVerbosity, FNetTrace::TraceObjectCreated(GameInstanceId, GetObjectIdForNetTrace(NetGUID), PathName, 0U, OwnerId))`
- L700 _macro_ `#define UE_NET_TRACE_INTERNAL_NETHANDLE_CREATED(Handle, DebugName, ProtocolId, OwnerId) FNetTrace::TraceObjectCreated(Handle.GetReplicationSystemId(), GetObjectIdForNetTrace(Handle), DebugName, ProtocolId, OwnerId)`
- L701 _macro_ `#define UE_NET_TRACE_INTERNAL_NETHANDLE_DESTROYED(Handle) FNetTrace::TraceObjectDestroyed(Handle.GetReplicationSystemId(), GetObjectIdForNetTrace(Handle))`
- L702 _macro_ `#define UE_NET_TRACE_INTERNAL_CONNECTION_CREATED(...) FNetTrace::TraceConnectionCreated(__VA_ARGS__)`
- L703 _macro_ `#define UE_NET_TRACE_INTERNAL_CONNECTION_STATE_UPDATED(...) FNetTrace::TraceConnectionStateUpdated(__VA_ARGS__)`
- L704 _macro_ `#define UE_NET_TRACE_INTERNAL_CONNECTION_UPDATED(...) FNetTrace::TraceConnectionUpdated(__VA_ARGS__)`
- L705 _macro_ `#define UE_NET_TRACE_INTERNAL_CONNECTION_CLOSED(...) FNetTrace::TraceConnectionClosed(__VA_ARGS__)`
- L706 _macro_ `#define UE_NET_TRACE_INTERNAL_PACKET_DROPPED(...) UE_NET_TRACE_DO_IF(GNetTraceRuntimeVerbosity, FNetTrace::TracePacketDropped(__VA_ARGS__))`
- L707 _macro_ `#define UE_NET_TRACE_INTERNAL_PACKET_SEND(...) UE_NET_TRACE_DO_IF(GNetTraceRuntimeVerbosity, FNetTrace::TracePacket(__VA_ARGS__, ENetTracePacketType::Outgoing))`
- L708 _macro_ `#define UE_NET_TRACE_INTERNAL_PACKET_RECV(...) UE_NET_TRACE_DO_IF(GNetTraceRuntimeVerbosity, FNetTrace::TracePacket(__VA_ARGS__, ENetTracePacketType::Incoming))`
- L710 _macro_ `#define UE_NET_TRACE_INTERNAL_PACKET_STATSCOUNTER(GameInstanceId, ConnectionId, Name, StatValue, Verbosity) \`
- L716 _macro_ `#define UE_NET_TRACE_INTERNAL_FRAME_STATSCOUNTER(GameInstanceId, Name, StatValue, Verbosity) \`
- L722 _macro_ `#define UE_NET_TRACE_INTERNAL_END_SESSION(GameInstanceId) FNetTrace::TraceEndSession(GameInstanceId);`
- L723 _macro_ `#define UE_NET_TRACE_INTERNAL_UPDATE_INSTANCE(...) FNetTrace::TraceInstanceUpdated(__VA_ARGS__)`
- L725 _macro_ `#define UE_NET_TRACE_INTERNAL_POLL_OBJECT_SCOPE(Handle, Timer) FNetTraceObjectPollTimer __NetTracePollTimer(Timer, (GNetTraceRuntimeVerbosity >= ENetTraceVerbosity::VeryVerbose && Handle.IsValid()) ? Handle.GetReplicationSystemId() : -1, Ha`
- L726 _macro_ `#define UE_NET_TRACE_INTERNAL_POLL_OBJECT_IS_WASTE __NetTracePollTimer.bIsWaste = true;`
- L727 _macro_ `#define UE_NET_TRACE_INTERNAL_QUANTIZE_OBJECT_SCOPE(Handle, Timer) FNetTraceObjectQuantizeTimer UE_JOIN(__NetTraceQuantizeTimer, __LINE__)(Timer, (GNetTraceRuntimeVerbosity >= ENetTraceVerbosity::VeryVerbose && Handle.IsValid()) ? Handle.Ge`
- L728 _macro_ `#define UE_NET_TRACE_INTERNAL_WRITE_OBJECT_SCOPE(Handle, Timer) FNetTraceObjectWriteTimer UE_JOIN(__NetTraceWriteTimer, __LINE__)(Timer, (GNetTraceRuntimeVerbosity >= ENetTraceVerbosity::VeryVerbose && Handle.IsValid()) ? Handle.GetReplicat`
- L730 _macro_ `#define UE_NET_TRACE_INTERNAL_SUBOBJECT(ParentHandle, SubObjectHandle) FNetTrace::TraceSubObject(ParentHandle.GetReplicationSystemId(), GetObjectIdForNetTrace(ParentHandle), GetObjectIdForNetTrace(SubObjectHandle))`
