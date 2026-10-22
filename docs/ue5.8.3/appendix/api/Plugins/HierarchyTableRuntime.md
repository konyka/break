# Plugins / HierarchyTableRuntime

- module root: `Plugins/Experimental/Animation/HierarchyTable/Source/Runtime`
- headers: 5; symbols: 62
- symbol kinds: class=2, function=17, macro=1, member=11, prototype=25, struct=6
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/Animation/HierarchyTable/Source/Runtime/Public/DefaultHierarchyTableType.h` (Public)


#### struct `FHierarchyTable_TableType_Default`  
`struct FHierarchyTable_TableType_Default final : public FHierarchyTable_TableType`  
_L10-13_
- reflection: `USTRUCT(DisplayName = "Default")`
- inherits: `FHierarchyTable_TableType`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Runtime/Public/HierarchyTable.h` (Public)


#### struct `FHierarchyTableEntryData`  
`struct FHierarchyTableEntryData`  
_L20-98_
- reflection: `USTRUCT()`
- desc: The data associated with each item in a hierarchy table.
- L25 _public function_ `FHierarchyTableEntryData() : Parent(INDEX_NONE)`
- L34 _public member_ `TObjectPtr<UHierarchyTable> OwnerTable;` — `UPROPERTY()` — The hierarchy table that this entry resides in.
- L42 _public member_ `TOptional<FInstancedStruct> Payload;` — `UPROPERTY()` — The actual user set data this element stores, matches the owner table's element type. If unset, will inherit from the parent. Is always set for entries with no parent.
- L46 _public member_ `FName Identifier;` — `UPROPERTY()` — This entry's display name and unique identifier.
- L50 _public member_ `int32 Parent;` — `UPROPERTY()` — The index of this entry's parent, is INDEX_NONE in the case of a root element.
- L54 _public member_ `FInstancedStruct TablePayload;` — `UPROPERTY()` — A second data payload specific to the table's type and is read-only metadata.
- L57 _public function_ `bool HasParent() const`
- L58 _public function_ `bool IsOverridden() const`
- L59 _public prototype_ `bool HasOverriddenChildren() const;`
- L61 _public prototype_ `void ToggleOverridden();`
- L64 _public prototype_ `const TOptional<FInstancedStruct>& GetPayload() const;` — Assumes payload is set, i.e. is overridden
- L67 _public function_ `template <typename T> const T* GetValue() const`
- L75 _public function_ `template <typename T> const T& GetMetadata() const`
- L81 _public function_ `template <typename T> T* GetMutableValue()`
- L87 _public prototype_ `const FHierarchyTableEntryData* GetClosestAncestor() const;`
- L93 _private prototype_ `const FInstancedStruct* GetActualValue() const;` — TODO: This needs to be cached in some way as it potentially goes up the entire hierarchy until it finds an ancestor with an overridden value This is called each time a widget is ticked so grows exponentially with the height of the hierarchy. This needs addressing at some point but cached value must be updated when any of its direct ancestors' value is updated.
- L95 _private prototype_ `const FInstancedStruct* GetFromClosestAncestor() const;`
- L97 _private prototype_ `bool IsOverriddenOrHasOverriddenChildren(const bool bIncludeSelf) const;`

#### class `UHierarchyTable`  
`class UHierarchyTable : public UObject`  
_L104-217_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, BlueprintType)`
- inherits: `UObject`
- desc: A general-purpose container asset for storing typed hierarchical data.
- L109 _public prototype_ `UHierarchyTable();`
- L114 _private member_ `FInstancedStruct TableMetadata;` — `UPROPERTY(EditAnywhere, Category = Default)` — The table metadata stores any data dependent on the table type needed to create and maintain the hierarchy.
- L118 _private member_ `TObjectPtr<const UScriptStruct> ElementType;` — `UPROPERTY(VisibleAnywhere, Category = Default)` — The element type is the type that each element is mapped into.
- L122 _private member_ `TArray<FHierarchyTableEntryData> TableData;` — `UPROPERTY()` — The actual table data
- L126 _public function_ `template <typename InTableType> bool IsTableType() const`
- L132 _public function_ `template <typename InTableType> InTableType GetTableMetadata() const`
- L138 _public function_ `const UScriptStruct* GetTableMetadataStruct() const`
- L144 _public function_ `template <typename InElementType> bool IsElementType() const`
- L149 _public prototype_ `FInstancedStruct CreateDefaultValue() const;`
- L151 _public function_ `void Initialize(const FInstancedStruct& InTableMetadata, const TObjectPtr<const UScriptStruct> InElementType)`
- L158 _public function_ `const FInstancedStruct& GetTableMetadata() const`
- L160 _public function_ `const TObjectPtr<const UScriptStruct>& GetElementType() const`
- L162 _public function_ `const TArray<FHierarchyTableEntryData>& GetTableData() const`
- L164 _public prototype_ `void EmptyTable();`
- L167 _public prototype_ `int32 GetTableEntryIndex(const FName EntryIdentifier) const;` — TODO: Remove in the future to avoid API signatures using indices
- L169 _public prototype_ `const FHierarchyTableEntryData* const GetTableEntry(const FName EntryIdentifier) const;`
- L172 _public prototype_ `const FHierarchyTableEntryData* const GetTableEntry(const int32 EntryIndex) const;` — TODO: Remove in the future to avoid API signatures using indices
- L175 _public prototype_ `FHierarchyTableEntryData* const GetMutableTableEntry(const int32 EntryIndex);` — TODO: Remove in the future to avoid API signatures using indices
- L177 _public prototype_ `int32 AddEntry(const FHierarchyTableEntryData& Entry);`
- L179 _public prototype_ `void AddBulkEntries(const TConstArrayView<FHierarchyTableEntryData> Entries);`
- L181 _public prototype_ `void RemoveEntry(const int32 Index);`
- L183 _public prototype_ `TArray<const FHierarchyTableEntryData*> GetChildren(const FHierarchyTableEntryData& Parent) const;`
- L185 _public prototype_ `bool HasIdentifier(const FName Identifier) const;`
- L188 _public function_ `template <typename T> FHierarchyTableEntryData* FindEntry(const FName EntryIdentifier)`
- L196 _public prototype_ `FGuid GetHierarchyGuid();`
- L201 _public prototype_ `FGuid GetEntriesGuid();` — Returns a GUID encoding the state of the values of all entries i.e. this GUID is invalidated when values inside the table are modified
- L204 _public prototype_ `void RegenerateEntriesGuid();` — TODO: Make private in subsequent API changes
- L208 _private prototype_ `void RegenerateHierarchyGuid();`
- L211 _private member_ `FGuid HierarchyGuid;` — `UPROPERTY()`
- L215 _private member_ `FGuid EntriesGuid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HIERARCHYTABLERUNTIME_API`
- L191 _function_ `` (scope `UHierarchyTable::FindEntry`)

### `Plugins/Experimental/Animation/HierarchyTable/Source/Runtime/Public/HierarchyTableDefaultTypes.h` (Public)


#### struct `FHierarchyTable_ElementType_Float`  
`struct FHierarchyTable_ElementType_Float final : public FHierarchyTable_ElementType`  
_L10-21_
- reflection: `USTRUCT(DisplayName = "Float")`
- inherits: `FHierarchyTable_ElementType`
- L14 _public function_ `FHierarchyTable_ElementType_Float() : Value(0.0)`
- L20 _public member_ `float Value;` — `UPROPERTY()`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Runtime/Public/HierarchyTableRuntimeModule.h` (Public)


#### class `FHierarchyTableRuntimeModule`  
`class FHierarchyTableRuntimeModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Runtime/Public/HierarchyTableType.h` (Public)


#### struct `FHierarchyTable_TableType`  
`struct FHierarchyTable_TableType`  
_L8-11_
- reflection: `USTRUCT()`

#### struct `FHierarchyTable_TablePayloadType`  
`struct FHierarchyTable_TablePayloadType`  
_L14-17_
- reflection: `USTRUCT()`

#### struct `FHierarchyTable_ElementType`  
`struct FHierarchyTable_ElementType`  
_L20-23_
- reflection: `USTRUCT()`
