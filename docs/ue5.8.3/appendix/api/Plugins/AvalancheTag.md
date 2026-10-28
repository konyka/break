# Plugins / AvalancheTag

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag`
- headers: 11; symbols: 130
- symbol kinds: class=2, enum=5, enumerator=7, function=31, macro=1, member=16, prototype=49, struct=15, typedef=4
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTag.h` (Public)


#### struct `FAvaTag`  
`struct FAvaTag`  
_L13-39_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Tag")`
- desc: Struct for a Tag NOTE: Do not use as storage type. Prefer using FAvaTagHandle to then retrieve the FAvaTag it references
- L17 _public function_ `bool IsValid() const`
- L22 _public function_ `bool operator==(const FAvaTag& InTag) const`
- L32 _public function_ `FString ToString() const`
- L38 _public member_ `FName TagName;` — `UPROPERTY(EditAnywhere, Category="Tag")`

#### Free symbols / members of external scopes

- L27 _function_ `friend uint32 GetTypeHash(const FAvaTag& InTag)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagAlias.h` (Public)


#### struct `FAvaTagAlias`  
`struct FAvaTagAlias`  
_L17-43_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Tag Alias")`
- desc: An alias represents multiple other Tag Ids. Unlike Tag Containers which would need to be updated in every place it's used when the set of tags it needs to manipulate is added to or removed from, Aliases are a layer of abstraction that allows the set of tags to be added to or removed from without affecting the places where the alias is used.
- L22 _public prototype_ `void SetOwner(UAvaTagCollection* InOwner);`
- L24 _public prototype_ `UAvaTagCollection* GetOwner() const;`
- L26 _public prototype_ `FString GetTagsAsString() const;`
- L30 _public member_ `FName AliasName;` — `UPROPERTY(EditAnywhere, Category="Tag")`
- L33 _public member_ `TArray<FAvaTagId> TagIds;` — `UPROPERTY(EditAnywhere, Category="Tag")`
- L41 _private member_ `TWeakObjectPtr<UAvaTagCollection> OwnerWeak;` — Tag Collection used to resolve the Tag Ids Set by the Tag Collection that holds the alias map on load/change

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagCollection.h` (Public)


#### class `UAvaTagCollection`  
`class UAvaTagCollection : public UObject`  
_L19-60_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Tag Collection")`
- inherits: `UObject`
- desc: Tag Collection that identifies a tag with an underlying Tag Id Guid and provides Tag reference capabilities
- L28 _public prototype_ `FAvaTagList GetTags(const FAvaTagId& InTagId) const;` — Returns an array of valid pointers to the tags that are under the given TagId Which could be an Alias
- L34 _public prototype_ `FName GetTagName(const FAvaTagId& InTagId) const;` — Returns the name of the Tag mapped to the given TagId. If the TagId is mapped to an Alias, it returns the Alias name instead.
- L37 _public prototype_ `TArray<FAvaTagId> GetTagIds(bool bInIncludeAliases) const;` — Returns the keys of the Tag Map, optionally including aliases
- L40 _public prototype_ `virtual void PostLoad() override;`
- L42 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L46 _public prototype_ `static FName GetTagMapName();`
- L47 _public prototype_ `static FName GetAliasMapName();`
- L52 _private prototype_ `void UpdateAliasOwner();` — Updates the weak ptr to the tag collection for each alias in the alias map
- L56 _private member_ `TMap<FAvaTagId, FAvaTag> Tags;` — `UPROPERTY(EditAnywhere, Category="Tag")`
- L59 _private member_ `TMap<FAvaTagId, FAvaTagAlias> Aliases;` — `UPROPERTY(EditAnywhere, Category="Tag")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagHandle.h` (Public)


#### struct `FAvaTagHandle`  
`struct FAvaTagHandle`  
_L18-66_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Tag Handle")`
- desc: Handle to a Tag or Alias (set of Tags) in a particular Source. This should be used by the UStructs/UObjects to properly reference a Tag or Alias (set of Tags).
- L22 _public prototype_ `FAvaTagHandle() = default;`
- L24 _public function_ `FAvaTagHandle(const UAvaTagCollection* InSource, const FAvaTagId& InTagId) : Source(InSource) , TagId(InTagId)`
- L35 _public prototype_ `FAvaTagList GetTags() const;` — Returns the resolved tags from the Handle If the Handle is to a particular Tag, it should return the array with a single element. If the Handle is to an alias, it should return the array of tags the alias represents.
- L37 _public prototype_ `FString ToString() const;`
- L39 _public prototype_ `FString ToDebugString() const;`
- L41 _public prototype_ `FName ToName() const;`
- L43 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L46 _public prototype_ `bool Overlaps(const FAvaTagHandle& InOther) const;` — Returns true if the Tag Handles have overlapping FAvaTags, even if the Source or Tag Id is different
- L49 _public prototype_ `bool MatchesExact(const FAvaTagHandle& InOther) const;` — Returns true if the Tag Handles is the exact same as the other (Same Source and Tag Id)
- L51 _public function_ `bool IsValid() const`
- L62 _public member_ `TObjectPtr<const UAvaTagCollection> Source;` — `UPROPERTY(EditAnywhere, Category = "Tag")`
- L65 _public member_ `FAvaTagId TagId;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaTagHandle> : public TStructOpsTypeTraitsBase2<FAvaTagHandle>`  
_L69-75_
- inherits: `TStructOpsTypeTraitsBase2<FAvaTagHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L72-74_

#### Free symbols / members of external scopes

- L56 _function_ `friend uint32 GetTypeHash(const FAvaTagHandle& InHandle)`
- L73 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonbee1c8680103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagHandleContainer.h` (Public)


#### struct `FAvaTagHandleContainer`  
`struct FAvaTagHandleContainer`  
_L18-58_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Tag Handle Container")`
- desc: Handle to a multiple tags in a particular Source. This should be used by the UStructs/UObjects to properly reference a multiple FAvaTags.
- L22 _public prototype_ `FAvaTagHandleContainer() = default;`
- L24 _public prototype_ `explicit FAvaTagHandleContainer(const FAvaTagHandle& InTagHandle);`
- L27 _public prototype_ `bool ContainsTag(const FAvaTagHandle& InTagHandle) const;` — Returns true if the Tag Handles resolve to same valued FAvaTags, even if the Source or Tag Id is different
- L30 _public prototype_ `bool ContainsTagHandle(const FAvaTagHandle& InTagHandle) const;` — Returns true if the Tag Handles is the exact same as the other (Same Source and Tag Id)
- L32 _public prototype_ `FString ToString() const;`
- L34 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L36 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& InPropertyTag, FStructuredArchive::FSlot InSlot);`
- L39 _public prototype_ `bool AddTagHandle(const FAvaTagHandle& InTagHandle);` — Adds the provided Tag Handle to TagIds. Returns true only if it was added as a new entry to TagIds
- L42 _public prototype_ `bool RemoveTagHandle(const FAvaTagHandle& InTagHandle);` — Removes the provided Tag Handle from TagIds. Returns true only if it existed and was removed from TagIds
- L45 _public prototype_ `TArray<FAvaTag> ResolveTags() const;` — Returns an array of resolved tags through this container's tag ids and source tag collection
- L47 _public function_ `TConstArrayView<FAvaTagId> GetTagIds() const`
- L53 _public member_ `TObjectPtr<const UAvaTagCollection> Source;` — `UPROPERTY(EditAnywhere, Category = "Tag")`
- L57 _private member_ `TArray<FAvaTagId> TagIds;` — `UPROPERTY(EditAnywhere, Category = "Tag")`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaTagHandleContainer> : public TStructOpsTypeTraitsBase2<FAvaTagHandleContainer>`  
_L61-68_
- inherits: `TStructOpsTypeTraitsBase2<FAvaTagHandleContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L64-67_

#### Free symbols / members of external scopes

- L65 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon419e1c2b0103`)
- L66 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon419e1c2b0103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagHandleKeyFuncs.h` (Public)


#### struct `TAvaTagHandleMapKeyFuncs`  
`template<typename InValueType, bool bInAllowDuplicateKeys = false> struct TAvaTagHandleMapKeyFuncs : BaseKeyFuncs<TPair<FAvaTagHandle, InValueType>, FAvaTagHandle, bInAllowDuplicateKeys>`  
_L9-28_
- inherits: `BaseKeyFuncs<TPair<FAvaTagHandle,InValueType>,FAvaTagHandle,bInAllowDuplicateKeys>`
- L11 _public typedef_ `using KeyInitType = TTypeTraits<FAvaTagHandle>::ConstPointerType;`
- L12 _public typedef_ `using ElementInitType = const TPairInitializer<TTypeTraits<FAvaTagHandle>::ConstInitType, typename TTypeTraits<InValueType>::ConstInitType>&;`
- L14 _public function_ `static KeyInitType GetSetKey(ElementInitType InElement)`
- L19 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L24 _public function_ `static uint32 GetKeyHash(KeyInitType InKey)`

#### struct `TAvaTagHandleSetKeyFuncs`  
`template<bool bInAllowDuplicateKeys = false> struct TAvaTagHandleSetKeyFuncs : BaseKeyFuncs<FAvaTagHandle, FAvaTagHandle, bInAllowDuplicateKeys>`  
_L31-50_
- inherits: `BaseKeyFuncs<FAvaTagHandle,FAvaTagHandle,bInAllowDuplicateKeys>`
- L33 _public typedef_ `using KeyInitType = TTypeTraits<FAvaTagHandle>::ConstPointerType;`
- L34 _public typedef_ `using ElementInitType = TCallTraits<FAvaTagHandle>::ParamType;`
- L36 _public function_ `static KeyInitType GetSetKey(ElementInitType InElement)`
- L41 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L46 _public function_ `static uint32 GetKeyHash(KeyInitType InKey)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagId.h` (Public)


#### struct `FAvaTagId`  
`struct FAvaTagId`  
_L12-56_
- reflection: `USTRUCT()`
- desc: Struct to identify a Tag. This is used by FAvaTagHandle to reference an FAvaTag
- L17 _public prototype_ `FAvaTagId() = default;` — Id is initialized to a zero
- L23 _public function_ `explicit FAvaTagId(EForceInit) : Id(FGuid::NewGuid())` — Force init where Id is initialized to a new guid. This is used in TCppStructOps::Construct
- L28 _public function_ `explicit FAvaTagId(const FGuid& InId) : Id(InId)`
- L33 _public function_ `bool operator==(const FAvaTagId& InOther) const`
- L38 _public function_ `bool IsValid() const`
- L43 _public function_ `FString ToString() const`
- L55 _private member_ `FGuid Id;` — `UPROPERTY(EditAnywhere, Category="Tag", meta=(IgnoreForMemberInitializationTest))`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaTagId> : TStructOpsTypeTraitsBase2<FAvaTagId>`  
_L59-65_
- inherits: `TStructOpsTypeTraitsBase2<FAvaTagId>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L62-64_

#### Free symbols / members of external scopes

- L48 _function_ `friend uint32 GetTypeHash(const FAvaTagId& InTagId)`
- L63 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anon55a9d3e90103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagLibrary.h` (Public)


#### class `UAvaTagLibrary`  
`class UAvaTagLibrary : public UBlueprintFunctionLibrary`  
_L15-28_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Tag Library", meta=(ScriptName = "MotionDesignTagLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L21 _public prototype_ `static TArray<FAvaTag> ResolveTagHandle(const FAvaTagHandle& InTagHandle);` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Tag", meta=(CompactNodeTitle = "->", BlueprintAutocast))`
- L24 _public prototype_ `static TArray<FAvaTag> ResolveTagHandles(const FAvaTagHandleContainer& InTagHandleContainer);` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Tag", meta=(CompactNodeTitle = "->", BlueprintAutocast))`
- L27 _public prototype_ `static FAvaTagHandle ResolveTagSoftHandle(const FAvaTagSoftHandle& InTagSoftHandle);` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Tag", meta=(CompactNodeTitle = "->", BlueprintAutocast))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagList.h` (Public)


#### struct `FAvaTagList`  
`struct FAvaTagList`  
_L9-24_
- L11 _public member_ `TArray<const FAvaTag*, TInlineAllocator<1>> Tags;`
- L13 _public function_ `decltype(Tags)::RangedForIteratorType begin()`
- L14 _public function_ `decltype(Tags)::RangedForIteratorType end()`
- L16 _public function_ `decltype(Tags)::RangedForConstIteratorType begin() const`
- L17 _public function_ `decltype(Tags)::RangedForConstIteratorType end() const`
- L19 _public function_ `decltype(Tags)::RangedForReverseIteratorType rbegin()`
- L20 _public function_ `decltype(Tags)::RangedForReverseIteratorType rend()`
- L22 _public function_ `decltype(Tags)::RangedForConstReverseIteratorType rbegin() const`
- L23 _public function_ `decltype(Tags)::RangedForConstReverseIteratorType rend() const`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagSoftHandle.h` (Public)


#### struct `FAvaTagSoftHandle`  
`struct FAvaTagSoftHandle`  
_L17-52_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Tag Soft Handle")`
- desc: Soft reference handle to a Tag in a particular Source Tag Collection This should be used when needing to soft reference a particular FAvaTag.
- L21 _public prototype_ `FAvaTagSoftHandle() = default;`
- L23 _public function_ `explicit FAvaTagSoftHandle(const TSoftObjectPtr<UAvaTagCollection>& InSource, const FAvaTagId& InTagId) : Source(InSource) , TagId(InTagId)`
- L29 _public prototype_ `explicit FAvaTagSoftHandle(const FAvaTagHandle& InTagHandle);`
- L35 _public prototype_ `FAvaTagHandle MakeTagHandle() const;` — Creates a Tag Handle from this Soft Handle. Warning: This loads in the Source Tag Collection if not already loaded.
- L38 _public prototype_ `bool MatchesExact(const FAvaTagHandle& InTagHandle) const;` — Returns true if this Soft Tag Handle matches the provided Tag Handle (Same Source and Tag Id)
- L40 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L42 _public function_ `bool IsValid() const`
- L48 _public member_ `TSoftObjectPtr<const UAvaTagCollection> Source;` — `UPROPERTY(EditAnywhere, Category = "Tag")`
- L51 _public member_ `FAvaTagId TagId;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaTagSoftHandle> : public TStructOpsTypeTraitsBase2<FAvaTagSoftHandle>`  
_L55-61_
- inherits: `TStructOpsTypeTraitsBase2<FAvaTagSoftHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L58-60_

#### Free symbols / members of external scopes

- L59 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon26ed00a40103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTag/Public/AvaTagSoftHandleContainer.h` (Public)


#### struct `FAvaTagSoftHandleContainer`  
`struct FAvaTagSoftHandleContainer`  
_L20-63_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Tag Soft Handle Container")`
- desc: Soft handle to multiple tags in a particular Source. This should be used when needing to soft reference multiple FAvaTags.
- L24 _public prototype_ `FAvaTagSoftHandleContainer() = default;`
- L26 _public prototype_ `explicit FAvaTagSoftHandleContainer(const FAvaTagHandle& InTagHandle);`
- L29 _public prototype_ `bool ContainsTag(const FAvaTagHandle& InTagHandle) const;` — Returns true if the Tag Handles resolve to same valued FAvaTags, even if the Source or Tag Id is different
- L32 _public prototype_ `bool ContainsTagHandle(const FAvaTagHandle& InTagHandle) const;` — Returns true if the Tag Handles is the exact same as the other (Same Source and Tag Id)
- L34 _public prototype_ `FString ToString() const;`
- L36 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L38 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& InPropertyTag, FStructuredArchive::FSlot InSlot);`
- L41 _public prototype_ `bool AddTagHandle(const FAvaTagHandle& InTagHandle);` — Adds the provided Tag Handle to TagIds. Returns true only if it was added as a new entry to TagIds
- L44 _public prototype_ `bool RemoveTagHandle(const FAvaTagHandle& InTagHandle);` — Removes the provided Tag Handle from TagIds. Returns true only if it existed and was removed from TagIds
- L47 _public prototype_ `TArray<FAvaTag> ResolveTags() const;` — Returns an array of resolved tags through this container's tag ids and source tag collection
- L50 _public prototype_ `const UAvaTagCollection* ResolveSource() const;` — Resolves the source soft object reference
- L52 _public function_ `TConstArrayView<FAvaTagId> GetTagIds() const`
- L58 _public member_ `TSoftObjectPtr<const UAvaTagCollection> Source;` — `UPROPERTY(EditAnywhere, Category = "Tag")`
- L62 _private member_ `TArray<FAvaTagId> TagIds;` — `UPROPERTY(EditAnywhere, Category = "Tag")`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaTagSoftHandleContainer> : public TStructOpsTypeTraitsBase2<FAvaTagSoftHandleContainer>`  
_L66-73_
- inherits: `TStructOpsTypeTraitsBase2<FAvaTagSoftHandleContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L69-72_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHETAG_API`
- L70 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon284257e70103`)
- L71 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon284257e70103`)
