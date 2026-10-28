# Plugins / AvalancheSceneTree

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneTree`
- headers: 3; symbols: 56
- symbol kinds: enum=2, enumerator=3, function=15, member=12, prototype=20, struct=4
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneTree/Public/AvaSceneItem.h` (Public)


#### enum `EAvaSceneItemIdType`  
`enum class EAvaSceneItemIdType : uint8`  
_L11-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `ObjectPath` — Id represents a UObject Path
- L16 _public enumerator_ `Other` — Id has no specifics on what it represents

#### struct `FAvaSceneItem`  
`struct FAvaSceneItem`  
_L20-74_
- reflection: `USTRUCT()`
- L24 _public prototype_ `FAvaSceneItem() = default;`
- L26 _public function_ `FAvaSceneItem(const UObject* InObject, const UObject* InStopOuter)`
- L33 _public function_ `FAvaSceneItem(const FString& InString)`
- L46 _public function_ `template<typename InObjectType = UObject, typename = typename TEnableIf<TIsDerivedFrom<InObjectType, UObject>::Value>::Type> InObjectType* Resolve(UObject* InOuter) const` — Resolve an Object against an outer. NOTE: If resolving an Actor/Component or anything in a World, be sure to use the appropriate World passed in. GetWorld() is not the same as GetTypedOuter<UWorld>() for streamed actors E.g. the appropriate way to pass in the outer for a streamed level would be AcquaintedActor->GetTypedOuter<UWorld>()
- L56 _public function_ `bool IsValid() const`
- L63 _public function_ `bool operator==(const FAvaSceneItem& InOther) const`
- L70 _private member_ `FString Id;` — `UPROPERTY()`
- L73 _private member_ `EAvaSceneItemIdType IdType = EAvaSceneItemIdType::ObjectPath;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L58 _function_ `friend uint32 GetTypeHash(const FAvaSceneItem& InItem)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneTree/Public/AvaSceneTree.h` (Public)


#### struct `FAvaSceneTree`  
`struct FAvaSceneTree`  
_L15-93_
- reflection: `USTRUCT()`
- L19 _public prototype_ `FAvaSceneTree();`
- L21 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L23 _public function_ `FAvaSceneTreeNode& GetRootNode()`
- L28 _public function_ `const FAvaSceneTreeNode& GetRootNode() const`
- L33 _public prototype_ `FAvaSceneTreeNode* FindTreeNode(const FAvaSceneItem& InItem);`
- L35 _public function_ `int32 GetSceneItemCount() const`
- L44 _public prototype_ `const FAvaSceneTreeNode* FindObjectTreeNode(const UObject* InObject, const UObject* InOuter) const;` — Finds tree node using the object map to avoid FAvaSceneItem allocation ResolveObjects() must've been called for the tree for the object map to be up-to-date.
- L46 _public prototype_ `const FAvaSceneTreeNode* FindTreeNode(const FAvaSceneItem& InItem) const;`
- L48 _public prototype_ `const FAvaSceneItem* GetItemAtIndex(int32 InIndex) const;`
- L50 _public prototype_ `FAvaSceneTreeNode& GetOrAddTreeNode(const FAvaSceneItem& InItem, const FAvaSceneItem& InParentItem);`
- L52 _public prototype_ `static const FAvaSceneTreeNode* FindLowestCommonAncestor(const TArray<const FAvaSceneTreeNode*>& InItems);`
- L54 _public prototype_ `static bool CompareTreeItemOrder(const FAvaSceneTreeNode* InA, const FAvaSceneTreeNode* InB);`
- L56 _public prototype_ `void Reset();`
- L59 _public prototype_ `TArray<AActor*> GetChildActors(const AActor* InParentActor) const;` — Returns all resolved child actors of a specified parent actor in the scene tree.
- L62 _public prototype_ `TArray<AActor*> GetRootActors(const ULevel* InLevel) const;` — Returns all root actors in this tree
- L64 _public function_ `bool IsSorted() const`
- L70 _public prototype_ `void SortItems();` — Sorts items based on tree item ordering. No-op if the tree is already sorted.
- L73 _public prototype_ `void ResolveObjects(UObject* InOuter);` — Fills the object to node map for faster look up
- L76 _private prototype_ `void UpdateTreeNodes();`
- L79 _private member_ `FAvaSceneTreeNode RootNode;` — `UPROPERTY()`
- L82 _private member_ `TArray<FAvaSceneItem> SceneItems;` — `UPROPERTY()`
- L85 _private member_ `TMap<FAvaSceneItem, FAvaSceneTreeNode> ItemTreeMap;` — `UPROPERTY()`
- L88 _private member_ `mutable TMap<TPair<FObjectKey, FObjectKey>, FAvaSceneTreeNode> ObjectToNodeMap;` — (Object, Outer) pair to their tree node
- L92 _private member_ `bool bSorted = false;` — `UPROPERTY()` — Whether scene items have been sorted to their latest structure

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaSceneTree> : TStructOpsTypeTraitsBase2<FAvaSceneTree>`  
_L96-102_
- inherits: `TStructOpsTypeTraitsBase2<FAvaSceneTree>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L99-101_

#### Free symbols / members of external scopes

- L100 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon9933aaa00103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneTree/Public/AvaSceneTreeNode.h` (Public)


#### struct `FAvaSceneTreeNode`  
`struct FAvaSceneTreeNode`  
_L12-58_
- reflection: `USTRUCT()`
- desc: Struct containing hierarchy index information of the Tree Node
- L18 _public function_ `bool IsValid() const`
- L23 _public function_ `int32 GetLocalIndex() const`
- L25 _public function_ `int32 GetGlobalIndex() const`
- L27 _public function_ `int32 GetParentIndex() const`
- L29 _public function_ `TConstArrayView<int32> GetChildrenIndices() const`
- L31 _public prototype_ `const FAvaSceneTreeNode* GetParentTreeNode() const;`
- L33 _public prototype_ `int32 CalculateHeight() const;`
- L35 _public prototype_ `TArray<const FAvaSceneTreeNode*> FindPath(const TArray<const FAvaSceneTreeNode*>& InItems) const;`
- L37 _public prototype_ `void Reset();`
- L42 _private member_ `int32 LocalIndex = INDEX_NONE;` — `UPROPERTY()` — Index of this Tree Node relative to the Parent Node Children Items. Can be used as means of Ordering
- L46 _private member_ `int32 GlobalIndex = INDEX_NONE;` — `UPROPERTY()` — Index of this Tree Node in the Owning Tree Scene Item List
- L50 _private member_ `int32 ParentIndex = INDEX_NONE;` — `UPROPERTY()` — Absolute Index of the Parent Node in the Owning Tree Scene Item List. If INDEX_NONE, it means Parent is Root
- L54 _private member_ `TArray<int32> ChildrenIndices;` — `UPROPERTY()` — Absolute Indices of the Children in the Owning Tree Scene Item List
- L57 _private member_ `FAvaSceneTree* OwningTree = nullptr;` — Pointer to the Tree that owns this Node
